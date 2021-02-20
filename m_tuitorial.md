<a name="content"></a>
# Content
1. [Content](#content)
1. [Installation](#installation)
1. [Inference](#inference)
1. [Submit new languge](#submit_new_language)
1. [TEXT DETECTION](#text_detection_header)
    1. [Data preparation](#det_data_preparation)
    1. [Training](#det_training)
    1. [Evaluation](#det_evaluate)
    1. [Test](#det_test)

<a name="installation"></a>
# Installation

    python3 -m pip install paddlepaddle-gpu==2.0.0 -i https://mirror.baidu.com/pypi/simple
    pip3 install -r requirements.txt

<a name="inference_paddle_ocr"></a>
# Inference

    # Predict a single image specified by image_dir
    python3 tools/infer/predict_system.py --image_dir="./doc/imgs/11.jpg" \
                                          --det_model_dir="./inference/ch_ppocr_mobile_v2.0_det_infer/" \
                                          --rec_model_dir="./inference/ch_ppocr_mobile_v2.0_rec_infer/" \
                                          --cls_model_dir="./inference/ch_ppocr_mobile_v2.0_cls_infer/" \
                                          --use_angle_cls=True \
                                          --use_space_char=True \
                                          --use_gpu=True

    # Predict imageset specified by image_dir
    python3 tools/infer/predict_system.py --image_dir="./doc/imgs/" \
                                          --det_model_dir="./inference/ch_ppocr_mobile_v2.0_det_infer/" \
                                          --rec_model_dir="./inference/ch_ppocr_mobile_v2.0_rec_infer/" \
                                          --cls_model_dir="./inference/ch_ppocr_mobile_v2.0_cls_infer/" \
                                          --use_angle_cls=True \
                                          --use_space_char=True \
                                          --use_gpu=True

<a name="submit_new_language"></a>
# Submit new language

1. Submit the dict text to this path and name it with `{language}_dict.txt` that contains a list of all characters in `ppocr/utils/dict`.
1. Submit the dict text to this path and name it with `{language}_corpus.txt` that contains a list of all characters in `ppocr/utils/corpus`.

<a name="text_detection_header"></a>
# TEXT DETECTION

<a name="det_data_preparation"></a>
## Data preparation

The provided annotation file format is as follow, seperated by "\t":

    " Image file name	Image annotation information encoded by json.dumps"

Example

    ch4_test_images/img_61.jpg	[{"transcription": "MASA", "points": [[310, 104], [416, 141], [418, 216], [312, 179]]}, {...}]

Convert ICDAR15 dataset ground truth to Paddle gt format

    from glob import glob
    import os
    import json
    import re
    import sys

    def read(filename):
        with open(filename, mode="r", encoding="utf-8") as f:
            data = f.read().strip().splitlines()
            lines = []
            for i, d in enumerate(data):
                d = d[1:].strip() if d.startswith("\ufeff") else d.strip()
                try:
                    x1_1, y1_1, x2_1, y2_1, x3_1, y3_1, x4_1, y4_1, transcrip = \
                        re.match(r"(\d+)," * 8 + "(.*)", d).groups()
                    lines.append([int(x1_1),
                                int(y1_1),
                                int(x2_1),
                                int(y2_1),
                                int(x3_1),
                                int(y3_1),
                                int(x4_1),
                                int(y4_1),
                                transcrip])
                except AttributeError:
                    print(filename)
                    print(data)
                    sys.exit("Wrong format")
        return lines

    def convert_icdar_to_paddle_ocr_format(label_dir, gt_ext, image_dir, image_ext, label_file):
        with open(label_file, mode="w", encoding="utf-8") as file:
            list_gt = glob(os.path.join(label_dir, f"*.{gt_ext}"))
            print(list_gt)
            if not list_gt:
                print(f"There is no Ground Truth file with .{gt_ext} in directory {label_dir}")
            for gt_file in list_gt:
                gt_content = read(gt_file)
                img_dir = os.path.join(image_dir, os.basename(gt_file).replace(gt_ext, image_ext))
                file.write(img_dir)
                file.write("\t")
                new_gt = []
                for gt in gt_content:
                    x1, y1, x2, y2, x3, y3, x4, y4, transcrip = gt
                    new_gt.append({"transcription":transcrip, "points":[[x1, y1], [x2, y2], [x3, y3], [x4, y4]]})

                file.write(json.dumps(new_gt))
                file.write("\n")

    if __name__ == "__main__":
        convert_icdar_to_paddle_ocr_format("./ch4_test_images_GT", "txt",
                                            "ch4_test_images", "jpg",
                                            "m_test.txt")

        convert_icdar_to_paddle_ocr_format("./ch4_train_images_GT", "txt",
                                            "ch4_train_images", "jpg",
                                            "m_train.txt")

<a name="det_training"></a>
## TRAINING

<a name="det_pretrained_models"></a>
### Pretrained Models

First download the [pretrained](https://github.com/PaddlePaddle/PaddleOCR/blob/release/2.0/doc/doc_en/algorithm_overview_en.md#1-text-detection-algorithm) model. The detection model of PaddleOCR currently supports 3 backbones, namely `MobileNetV3`, `ResNet18_vd` and `ResNet50_vd`. You can use the model in [PaddleClas](https://github.com/PaddlePaddle/PaddleClas/tree/release/static/ppcls/modeling/architectures) to replace backbone according to your needs.

    cd PaddleOCR/pretrain_models/
    # Download the pre-trained model of MobileNetV3
    wget https://paddle-imagenet-models-name.bj.bcebos.com/MobileNetV3_large_x0_5_pretrained.tar
    # or, download the pre-trained model of ResNet18_vd
    wget https://paddle-imagenet-models-name.bj.bcebos.com/ResNet18_vd_pretrained.tar
    # or, download the pre-trained model of ResNet50_vd
    wget https://paddle-imagenet-models-name.bj.bcebos.com/ResNet50_vd_ssld_pretrained.tar

    # decompressing the pre-training model file, take MobileNetV3 as an example
    tar -xf ./MobileNetV3_large_x0_5_pretrained.tar

    # Note: After decompressing the backbone pre-training weight file correctly, the file list in the folder is as follows:
    pretrain_models/                               
    ├── MobileNetV3_large_x0_5_pretrained
    │   ├── conv10_depthwise_bn_mean
    │   ├── conv10_depthwise_bn_offset
    │   ├── conv10_depthwise_bn_scale
    │   ├── ......

<a name="det_custom_configuration"></a>
### Custom configuration
Custom configuration file `configs/{type}/{type}_{model}_{backbone}.yml`

[parameters explanation at](https://github.com/PaddlePaddle/PaddleOCR/blob/release/2.0/doc/doc_en/config_en.md)

<a name="det_start_training"></a>
### Start training

    # For single GPU
    python3 tools/train.py -c configs/det/det_mv3_db.yml
    python3 tools/train.py -c configs/det/det_mv3_db.yml -o Optimizer.base_lr=0.0001

    # For multiple GPUs
    python3 -m paddle.distributed.launch --gpus '0,1,2,3' tools/train.py -c configs/det/det_mv3_db.yml -o Optimizer.base_lr=0.0001

<a name="det_continue_training"></a>
### Load trained model and continue training

    python3 tools/train.py -c configs/det/det_mv3_db.yml -o Global.checkpoints=${your/trained/model}/latest

**Note**: The priority of `Global.checkpoints` is higher than that of `Global.pretrain_weights`, that is, when two parameters are specified at the same time, the model specified by `Global.checkpoints` will be loaded first. If the model path specified by `Global.checkpoints` is wrong, the one specified by `Global.pretrain_weights` will be loaded.

<a name="det_evaluate"></a>
## EVALUATION

PaddleOCR calculates three indicators for evaluating performance of OCR detection task: `Precision`, `Recall`, and `Hmean`.

When evaluating the `DB` model, set post-processing parameters `box_thresh=0.6`, `unclip_ratio=1.5`, and if you use different datasets, these two parameters should be adjusted for better result. When evaluating `EAST` model, these parameters are not need to be set.

    python3 tools/eval.py -c configs/det/m_det_mv3_db.yml  -o Global.checkpoints=./output/db_mv3/best_accuracy PostProcess.box_thresh=0.6 PostProcess.unclip_ratio=1.5

<a name="det_test"></a>
## TEST

Test the detection result on a single image:

    python3 tools/infer_det.py -c configs/det/m_det_mv3_db.yml -o Global.infer_img=./doc/imgs_en/img_10.jpg Global.pretrained_model=./output/east_mv3/best_accuracy Global.load_static_weights=false

When testing the DB model, adjust the post-processing threshold:

    python3 tools/infer_det.py -c configs/det/m_det_mv3_db.yml -o Global.infer_img=./doc/imgs_en/img_10.jpg Global.pretrained_model=./output/db_mv3/best_accuracy Global.load_static_weights=false PostProcess.box_thresh=0.6 PostProcess.unclip_ratio=1.5

Test the detection result on all images in the folder:

    python3 tools/infer_det.py -c configs/det/m_det_mv3_db.yml -o Global.infer_img=./doc/imgs_en/ Global.pretrained_model=./output/east_mv3/best_accuracy Global.load_static_weights=false

<a name="text_angle_classification_header"></a>
# TEXT ANGLE CLASSIFICATION
l