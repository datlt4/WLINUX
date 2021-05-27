
## [NOTE] Jetson Download Center
**_Reference:_**

    https://developer.nvidia.com/embedded/downloads
    

## [ERROR] `N: Unable to locate package python-pip`
**_Reason:_**

    have to enable universe category which contains python-pip package.

**_Solution:_**

    01. sudo apt-get update
    02. sudo apt-get upgrade
    03. sudo apt install nano -y 
    04. sudo apt-get install htop -y
    05. sudo apt-get install tmux -y
    05. sudo apt install python3-pip -y
    06. sudo -H pip3 install jetson-stats
    07. sudo -H pip3 install --upgrade setuptools
    08. sudo -H pip3 install cython
    09. sudo -H pip3 install -U setuptools
    10. sudo nano /etc/apt/sources.list
    11. add universe at the end of file

```javascript class:"lineNo"
# See http://help.ubuntu.com/community/UpgradeNotes for how to upgrade to
# newer versions of the distribution.
deb http://ports.ubuntu.com/ubuntu-ports/ bionic main restricted universe
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic main restricted

## Major bug fix updates produced after the final release of the
## distribution.
deb http://ports.ubuntu.com/ubuntu-ports/ bionic-updates main restricted universe
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-updates main restricted

## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu
## team. Also, please note that software in universe WILL NOT receive any
## review or updates from the Ubuntu security team.
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic universe
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-updates universe

## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu
## team, and may not be under a free licence. Please satisfy yourself as to
## your rights to use the software. Also, please note that software in
## multiverse WILL NOT receive any review or updates from the Ubuntu
## security team.
deb http://ports.ubuntu.com/ubuntu-ports/ bionic multiverse
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic multiverse
deb http://ports.ubuntu.com/ubuntu-ports/ bionic-updates multiverse
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-updates multiverse

## N.B. software from this repository may not have been tested as
## extensively as that contained in the main release, although it includes
## newer versions of some applications which may provide useful features.
## Also, please note that software in backports WILL NOT receive any review
## or updates from the Ubuntu security team.
deb http://ports.ubuntu.com/ubuntu-ports/ bionic-backports main restricted multiverse universe
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-backports main restricted universe multiverse

## Uncomment the following two lines to add software from Canonical's
## 'partner' repository.##
## This software is not part of Ubuntu, but is offered by Canonical and the
## respective vendors as a service to Ubuntu users.
deb http://archive.canonical.com/ubuntu bionic partner
# deb-src http://archive.canonical.com/ubuntu bionic partner

deb http://ports.ubuntu.com/ubuntu-ports/ bionic-security main restricted universe
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-security main restricted
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-security universe
deb http://ports.ubuntu.com/ubuntu-ports/ bionic-security multiverse
# deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-security multiverse
```

## [ERROR] The repository does not have a Release file
Run `sudo apt update` and get error:

    E: The repository 'http://ppa.launchpad.net/armagetronad-dev/ppa/ubuntu bionic Release' does not have a Release file. 
    N: Updating from such a repository can't be done securely, and is therefore disabled by default. 
    N: See apt-secure(8) manpage for repository creation and user configuration details.

**_Solution_**:

    sudo apt-add-repository -r ppa:armagetronad-dev/ppa
    sudo apt update -q

## [ERROR] `E: Unable to locate package nano`
**_Solution:_**
    
    snap install nano

## [TUITORIAL] Check available camera

    ls -ltrh /dev/video*

## [TUITORIAL] Jetson Nano CSI-Camera

    git clone https://github.com/JetsonHacksNano/CSI-Camera.git
    git checkout v2.0

## [ERROR] `W: GPG error`
**W: GPG error:** http://archive.debian.org/debian jessie-backports InRelease: The following signatures couldn't be verified because the public key is not avail able: **NO_PUBKEY 8B48AD6246925553 NO_PUBKEY 7638D0442B90D010**

**_Reason:_**

    apt is telling us that the following keys are missing: 8B48AD6246925553 and 7638D0442B90D010

**_Solution:_**

    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 8B48AD6246925553
    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 7638D0442B90D010

## [ERROR] `E: Release file for .../InRelease is expired `
E: Release file for http://archive.debian.org/debian/dists/jessie-backports/InRelease is expired (invalid since 357d 12h 49min 26s). Updates for this repository will not be applied.
**_Solution:_**

    add "-o Acquire::Check-Valid-Until=false" into the end of command.
    eg: sudo apt update -o Acquire::Check-Valid-Until=false

## [TUITORIAL] Uninstall OpenCV Completely
**_Reference_**

    https://installlion.com/ubuntu/xenial/universe/p/python-opencv/uninstall/index.html

**_Uninstall just python-opencv_**

    sudo apt-get remove python-opencv

**_Uninstall python-opencv and its dependencies_**

    sudo apt-get remove --auto-remove python-opencv

**_Purging your config/data too_**

    sudo apt-get purge --auto-remove python-opencv

## [TUITORIAL] Install OpenCV 3.4.6
**_[ ] Reference:_**

    https://github.com/jkjung-avt/jetson_nano.git

**_Step `0`: Add Swap Memory_**

    sudo fallocate -l 4G /var/swapfile
    sudo chmod 600 /var/swapfile
    sudo mkswap /var/swapfile
    sudo swapon /var/swapfile
    sudo bash -c 'echo "/var/swapfile swap swap defaults 0 0" >> /etc/fstab'

**_Step `1`: Install OpenCV dependencies on Ubuntu 18.04_**

    sudo apt-get update
    sudo apt-get upgrade -y
    sudo apt-get install build-essential -y
    sudo apt-get install cmake -y
    sudo apt-get install unzip -y
    sudo apt-get install pkg-config -y
    sudo apt-get install libjpeg-dev -y
    sudo apt-get install libpng-dev -y
    sudo apt-get install libtiff-dev -y
    sudo apt-get install libjasper-dev -y
    sudo apt-get install libavcodec-dev -y
    sudo apt-get install libavformat-dev -y
    sudo apt-get install libswscale-dev -y
    sudo apt-get install libv4l-dev -y
    sudo apt-get install libxvidcore-dev -y
    sudo apt-get install libx264-dev -y
    sudo apt-get install libgtk-3-dev -y
    sudo apt-get install libatlas-base-dev -y
    sudo apt-get install gfortran -y
    sudo apt-get install python3.6-dev -y

**_Step `2`: Download the official OpenCV source:_**

    cd ~
    wget -O opencv.zip https://github.com/opencv/opencv/archive/3.4.6.zip
    wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/3.4.6.zip
    unzip opencv.zip
    unzip opencv_contrib.zip
    mv opencv-3.4.6 opencv
    mv opencv_contrib-3.4.6 opencv_contrib
    pip3 install numpy
    cd ~/opencv
    mkdir build
    cd build
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_CUDA=ON -D INSTALL_PYTHON_EXAMPLES=ON -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules -D OPENCV_ENABLE_NONFREE=ON -D BUILD_EXAMPLES=ON -D WITH_GSTREAMER=ON ..

    sudo make -j3
    # sudo make -j$(nproc)

    sudo make install
    sudo ldconfig
    pkg-config --modversion opencv

<a name="set_opencv_pc"></a>
**_Step `3`: Find & Set “opencv.pc” file path:_**

```bash
ls /usr/local/lib/pkgconfig/
sudo cp /usr/local/lib/pkgconfig/opencv.pc  /usr/lib/x86_64-linux-gnu/pkgconfig/opencv.pc
pkg-config --modversion opencv
```

<a name="compile_code"></a>
**_Step `4`: Compile code:_**

[code](https://github.com/long-senpai/Manual_for_deeplearning/blob/master/Install_OpenCV4_CUDA10.md#example)

```
.
├── build
├── CMakeLists.txt
├── main.cpp
└── makefile
```

>**Makefile**

```Makefile
GCC ?= g++

CCFLAGS := -std=c++11

LDFLAGS += $(shell pkg-config --libs opencv)
INCLUDES += $(shell pkg-config --cflags opencv)

SRCS=main.cpp
OBJS=main.o
RM=rm -f
EXEC=app

# Target rules
all: build

build: ${EXEC}

%.o: %.cpp %.h
    $(GCC) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

${EXEC}: ${OBJS}
    $(GCC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

clean:
    ${RM} ${EXEC} *.o 

dist-clean:
    $(RM) $(EXEC)
```

>**CMakeLists.txt**

```Cmake
cmake_minimum_required(VERSION 2.8)
project( HNIW )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( app main.cpp )
target_link_libraries( app ${OpenCV_LIBS} )
```

## [TUITORIAL] Install OpenCV 4

**_Add Swap Memory_**

``` bash
sudo fallocate -l 4G /var/swapfile
sudo chmod 600 /var/swapfile
sudo mkswap /var/swapfile
sudo swapon /var/swapfile
sudo bash -c 'echo "/var/swapfile swap swap defaults 0 0" >> /etc/fstab'
```
**_Updating the packages_**

[link to Long_senpai](https://github.com/long-senpai/Manual_for_deeplearning/blob/master/Install_OpenCV4_CUDA10.md#how-to-install-opencv-410-with-cuda-100-in-ubuntu-distro-1804)

**_Download OpenCV & Contribs Modules_**

``` bash
pushd ~/
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```

**_Create directory_**

mkdir build
cd build/

**_Build Opencv using Cmake_**

```bash
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_C_COMPILER=/usr/bin/gcc \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=OFF \
    -D WITH_TBB=ON \
    -D WITH_CUDA=ON \
    -D WITH_CUDNN=ON \
    -D OPENCV_DNN_CUDA=ON \
    -D BUILD_opencv_cudacodec=ON \
    -D ENABLE_FAST_MATH=1 \
    -D CUDA_FAST_MATH=1 \
    -D WITH_CUBLAS=1 \
    -D WITH_V4L=ON \
    -D WITH_QT=OFF \
    -D WITH_OPENGL=ON \
    -D WITH_GSTREAMER=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_PC_FILE_NAME=opencv.pc \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D BUILD_SHARED_LIBS=ON \
    -D WITH_FFMPEG=OFF \
    -D BUILD_EXAMPLES=ON \
    -D BUILD_TESTS=OFF \
    -D BUILD_PERF_TESTS=OFF .. 
```

**_Compile the OpenCV with Contribs Modules_**

```bash
make -j${nproc}
sudo make install
```

<a name="set_opencv_pc"></a>
**_[Find & Set “opencv.pc” file path](#set_opencv_pc)_**

<a name="compile_code"></a>
**_[Compile code](#compile_code)_**

## [TUITORIAL] Install Tensorflow-gpu==1.15.0
**_[ ]Reference:_**

    https://github.com/karaage0703/jetson-nano-tools

**_..._**

    sudo apt-get update

**_Install HDF5_**

    sudo apt-get -y install libhdf5-serial-dev
    sudo apt-get -y install hdf5-tools

**_Install pip_**

    sudo apt-get -y install python3-pip

**_Install required packages_**

    sudo apt-get -y install zlib1g-dev
    sudo apt-get -y install zip
    sudo apt-get -y install libjpeg8-dev
    sudo apt-get -y install libhdf5-dev
    sudo -H pip3 install -U numpy==1.16.1
    sudo -H pip3 install -U grpcio
    sudo -H pip3 install -U absl-py
    sudo -H pip3 install -U py-cpuinfo
    sudo -H pip3 install -U psutil
    sudo -H pip3 install -U portpicker
    sudo -H pip3 install -U six
    sudo -H pip3 install -U mock
    sudo -H pip3 install -U requests
    sudo -H pip3 install -U gast
    sudo -H pip3 install -U h5py
    sudo -H pip3 install -U astor
    sudo -H pip3 install -U termcolor
    sudo -H pip3 install -U cython

**_Install TensorFlow_**

(check version at: https://developer.download.nvidia.com/compute/redist/jp/v43/tensorflow-gpu/)

    pip3 install --no-cache-dir --extra-index-url https://developer.download.nvidia.com/compute/redist/jp/v43 tensorflow-gpu==1.15.0+nv20.1 --user

**_Upgrade Numpy_**

    sudo pip3 install numpy==1.18


## [TUITORIAL] Pytorch v1.4.0 for Jetson Nano
#### Pytorch v1.4.0 for Jetson Nano
**_[ ] Reference:_**

    https://forums.developer.nvidia.com/t/pytorch-for-jetson-nano-version-1-4-0-now-available/72048

`1`

    wget https://nvidia.box.com/shared/static/ncgzus5o23uck9i5oth2n8n06k340l6k.whl -O torch-1.4.0-cp36-cp36m-linux_aarch64.whl

`2`

    sudo apt-get install python3-pip libopenblas-base

`3`

    pip3 install Cython

`4`
    
    pip3 install numpy torch-1.4.0-cp36-cp36m-linux_aarch64.whl

#### Pytorch v1.4.0 for Jetson Nano
**_[ ] Reference:_**

    https://medium.com/hackers-terminal/installing-pytorch-torchvision-on-nvidias-jetson-tx2-81591d03ce32

`1`

    sudo apt-get install libjpeg-dev zlib1g-dev

`2`
    git clone -b v0.5.0 https://github.com/pytorch/vision torchvision

`3`
    
    cd torchvision

`4`

    sudo python3 setup.py install


#### Version of torchvision to download depending on the version of PyTorch
|Pytorch|torchvision|
|:-:|:-:|
|v1.0|v0.2.2|
|v1.1|v0.3.0|
|v1.2|v0.4.0|
|v1.3|v0.4.2|
|v1.4|v0.5.0|


## [TUITORIAL] Generating TensorRT Engines from TensorFlow
**_[ ] Reference:_**
    https://docs.nvidia.com/deeplearning/sdk/tensorrt-archived/tensorrt_401/tensorrt-api/python_api/index.html

`1.` Check TensorRT version (the current TensorRT version is 6.0.1)
        dpkg -l | grep nvinfer

    https://blog.csdn.net/ctwy291314/article/details/103507846

`2` Check CUDA version

    cat /usr/local/cuda/version.txt

`3` Check CUDNN version
    
    cat /usr/include/aarch64-linux-gnu/cudnn_v7.h | grep CUDNN_MAJOR -A 2

`4` Installing the Python APIs:
    
    pip3 install tensorrt-*_16.04-cp35-cp35m-linux_x86_64.whl

## [TUITORIAL] Install Jupiter Lab

    sudo apt install python3-pip
    sudo pip3 install wheel
    sudo pip3 install jupyter jupyterlab
    sudo jupyter labextension install @jupyter-widgets/jupyterlab-manager
    jupyter lab --generate-config

jupyter notebook remote

    jupyter notebook --no-browser --port=8889
    ssh -N -f -L 8888:8889 jetson@192.168.137.189
    http://localhost:8888/?token=a9dca23be19c7a142c5d593d9c717c81354fd1062ab90fad

Add Conda environment to jupyter notebook
    
    python -m ipykernel install --user --name M --display-name "MINH"

## [TUITORIAL] Setup Anaconda
**_[ ] Reference:_**

    https://www.digitalocean.com/community/tutorials/how-to-install-anaconda-on-ubuntu-18-04-quickstart

## [TUITORIAL] Install Scipy

    sudo apt-get install python3-scipy

## [NOTE] nvcc not found - darknet

which nvcc
    
    ->  /usr/local/cuda/bin/nvcc

    export PATH=${PATH}:/usr/local/cuda/bin/nvcc

===========

## [TUITORIAL] Build DeepStream SDK
    sudo apt install \
        libssl1.0.0 \
        libgstreamer1.0-0 \
        gstreamer1.0-tools \
        gstreamer1.0-plugins-good \
        gstreamer1.0-plugins-bad \
        gstreamer1.0-plugins-ugly \
        gstreamer1.0-libav \
        libgstrtspserver-1.0-0 \
        libjansson4=2.11-1
    
    sudo apt-get install librdkafka1=0.11.3-1build1
    tar -xpvf deepstream_sdk_v4.0.2_jetson.tbz2
    cd deepstream_sdk_v4.0_jetson
    sudo tar -xvpf binaries.tbz2 -C /
    sudo ./install.sh
    sudo nvpmodel -m 0
    sudo jetson_clocks
    deepstream-app -c ./samples/configs/deepstream-app/source8_1080p_dec_infer-resnet_tracker_tiled_display_fp16_nano.txt

**_[ ] Reference:_**

    https://docs.nvidia.com/metropolis/deepstream/4.0/dev-guide/index.html

## [TUITORIAL] Setup TensorRT
**_[ ] Reference:_**
    
    https://blog.csdn.net/ctwy291314/article/details/103507846
    https://github.com/BouweCeunen/computer-vision-jetson-nano/blob/master/README.md

Tải các file deb sau được đề cập trong link trên:

    libnvinfer5_5.1.6-1+cuda10.0_arm64.deb
    libnvinfer-dev_5.1.6-1+cuda10.0_arm64.deb
    libnvinfer-samples_5.1.6-1+cuda10.0_all.deb
    tensorrt_5.1.6.1-1+cuda10.0_arm64.deb
    python3-libnvinfer_5.1.6-1+cuda10.0_arm64.deb
    python3-libnvinfer-dev_5.1.6-1+cuda10.0_arm64.deb
    graphsurgeon-tf_5.1.6-1+cuda10.0_arm64.deb
    uff-converter-tf_5.1.6-1+cuda10.0_arm64.deb

## [TUITORIAL] Install PyQt5 for jetson nano
Install PyQt5

    sudo apt-get install python3-pyqt5

Install QtCreator

    sudo apt-get install qtcreator

## [TUITORIAL] Torch model 2 ONNX

    import torch
    import torchvision

    MODEL_FACE_RECOGNIZE_PATH = 'BEST_checkpoint_r101.tar'
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    checkpoint = torch.load(MODEL_FACE_RECOGNIZE_PATH)
    faceReg = checkpoint['model'].module
    faceReg = faceReg.to(device)
    faceReg.eval()

    dummy_input = torch.randn(2, 3, 112, 112, device='cuda')

    input_names = [ "actual_input_1" ] + [ "learned_%d" % i for i in range(16) ]
    output_names = [ "output" ]

    torch.onnx.export(faceReg, dummy_input, "insightfaceV2.onnx", verbose=True, input_names=input_names, output_names=output_names)

## [TUITORIAL] ONNX to TensorRT

    import os
    import tensorrt as trt

    batch_size = 2
    TRT_LOGGER = trt.Logger()

    def build_engine_onnx(model_file):
        with trt.Builder(TRT_LOGGER) as builder, builder.create_network() as network, trt.OnnxParser(network, TRT_LOGGER) as parser:
            builder.max_workspace_size = 1 << 30
            builder.max_batch_size = batch_size
            last_layer = network.get_layer(network.num_layers - 1)
            if not last_layer.get_output(0):
                network.mark_output(last_layer.get_output(0))
            with open(model_file, 'rb') as model:
                parser.parse(model.read())
            return builder.build_cuda_engine(network)

    if __name__ == '__main__':
        onnx_file_path = './insightfaceV2.onnx'
        engine = build_engine_onnx(onnx_file_path)
        engine_file_path = './insightfaceV2.engine'
        with open(engine_file_path, "wb") as f:
            f.write(engine.serialize())

## [TUITORIAL] .pb to TensorRT
**_[ ] Reference:_**

    https://iwannatechcom.sharepoint.com/:w:/r/sites/iwanna-face/_layouts/15/Doc.aspx?sourcedoc=%7BA5AA2F4C-B3B8-4854-98CA-0913AF8227C1%7D&file=Speed%20up%20TensorFlow%20Inference%20on%20GPUs%20with%20TensorRT.doc&action=default&mobileredirect=true

**_code_**

```python
from tensorflow.python import ops
import tensorflow.contrib.tensorrt as trt
import tensorflow as tf
import argparse

ap = argparse.ArgumentParser()
ap.add_argument("-m", "--model", type=str, help="path to pb file")
args = ap.parse_args()

def get_graph_def_from_file(graph_filepath):
    tf.compat.v1.reset_default_graph()
    with ops.Graph().as_default():
        with tf.io.gfile.GFile(graph_filepath, 'rb') as f:
            graph_def = tf.compat.v1.GraphDef()
            graph_def.ParseFromString(f.read())
        return graph_def

frozen_graph = get_graph_def_from_file(args.model)

output_names = ["boxes", "scores", "num_boxes"]
trt_graph = trt.create_inference_graph(input_graph_def=frozen_graph,
                                        outputs=output_names,
                                        max_batch_size=1,
                                        max_workspace_size_bytes=1 << 25,
                                        precision_mode='FP16',
                                        minimum_segment_size=3)

with open(args.model.replace(".pb", ".trt"), 'wb') as f:
    f.write(trt_graph.SerializeToString())
```

**_load TensorRT model_**

``` python
from tensorflow.python import ops
import tensorflow as tf
import argparse
import cv2

ap = argparse.ArgumentParser()
ap.add_argument("-m", "--model", type=str, help="path to pb file")
ap.add_argument("-i", "--image", type=str, help="image path")
args = ap.parse_args()

def get_graph_def_from_file(graph_filepath):
    tf.compat.v1.reset_default_graph()
    with ops.Graph().as_default():
        with tf.io.gfile.GFile(graph_filepath, 'rb') as f:
            graph_def = tf.compat.v1.GraphDef()
            graph_def.ParseFromString(f.read())
        return graph_def

if __name__=="__main__":
    graph_def = get_graph_def_from_file(args.model)
    graph = tf.Graph()
    with graph.as_default():
        tf.import_graph_def(graph_def, name='import')


    input_image = graph.get_tensor_by_name('import/image_tensor:0')
    output_ops = [
        graph.get_tensor_by_name('import/boxes:0'),
        graph.get_tensor_by_name('import/scores:0'),
        graph.get_tensor_by_name('import/num_boxes:0'),
    ]

    gpu_options = tf.compat.v1.GPUOptions(
        per_process_gpu_memory_fraction=0.5,
        visible_device_list="0"
    )
    config_proto = tf.compat.v1.ConfigProto(gpu_options=gpu_options, log_device_placement=False)
    sess = tf.compat.v1.Session(graph=graph, config=config_proto)

    img = cv2.imread(args.image)
    img_batch = img[None]
    boxes, scores, num_boxes = sess.run(output_ops, feed_dict={input_image: img_batch})
    
    to_keep = scores > score_threshold
    boxes = boxes[to_keep]
    scores = scores[to_keep]

    print(boxes, scores)
```

## [ERROR] Extremely long model loading time problem of TF-TRT

**_Reference_**

    https://jkjung-avt.github.io/tf-trt-revisited/

**_Reason_**

    The default `python implementation` of python3 `protobuf` module runs too slowly on the Jetson platforms.

**_Solution_**

    Replace it with `cpp implementaion` of that same module.

**_Install protobuf-3.6.1_**

    wget https://raw.githubusercontent.com/jkjung-avt/jetson_nano/master/install_protobuf-3.6.1.sh
    ./install_protobuf-3.6.1.sh


## [TUITORIAL] Object Detection in 10 lines code

    sudo apt-get update
    sudo apt-get install git cmake libpython3-dev python3-numpy
    git clone --recursive http://github.com/dusty-nv/jetson-inference
    cd jetson-inference/
    mkdir build
    cd build
    cmake ../
    make
    sudo make install
    sudo ldconfig

## [NOTE] RTSP link
    https://www.unifore.net/ip-video-surveillance/network-camera-rtsp-url-address-and-port-number.html

    [RTSP] rtsp://admin:abcd1234@192.168.1.8:554/h265/ch1/main/av_stream

    [Configure & Preview] http://192.168.1.8/doc/page/login.asp

    [SADP Tool] https://www.hikvision.com/en/support/tools/destop-tools/sadp-for-windows/


## [NOTE] GSTREAMER vs OpenCV
[v] - stream video, use NVDEC

    gst-launch-1.0 filesrc location=~/Documents/your_name.mp4 ! qtdemux name=demux demux.video_0 ! queue ! h264parse ! omxh264dec ! nveglglessink -e

    cap = cv2.VideoCapture("filesrc location=~/Documents/your_name.mp4 ! qtdemux name=demux demux.video_0 ! queue ! h264parse ! omxh264dec ! nveglglessink -e", cv2.CAP_GSTREAMER)

[v] - stream RTSP, use NVDEC

    gst-launch-1.0 rtspsrc location=rtsp://admin:abcd1234@192.168.1.8:554/h265/ch1/main/av_stream ! decodebin ! nvvidconv ! video/x-raw,format=I420,width=1920,height=1080 ! videoconvert ! nveglglessink -e

    cap = cv2.VideoCapture("rtspsrc location=rtsp://admin:abcd1234@192.168.1.8:554/h265/ch1/main/av_stream ! decodebin ! nvvidconv ! video/x-raw, format=I420, width=1920, height=1080 ! videoconvert ! appsink", cv2.CAP_GSTREAMER)

===========

## [REFERENCE]

#### Use NVIDIA DeepStream to Accelerate H.264 Video Stream Decoding

    [ ] https://medium.com/@fanzongshaoxing/use-nvidia-deepstream-to-accelerate-h-264-video-stream-decoding-8f0fec764778
    [ ] https://docs.nvidia.com/metropolis/deepstream/4.0/dev-guide/
    [ ] https://medium.com/tensorflow/high-performance-inference-with-tensorrt-integration-c4d78795fbfe

#### NVIDIA Jetson Nano courses 

    [ ] https://courses.nvidia.com/courses/course-v1:DLI+C-IV-02+V1/courseware/b2e02e999d9247eb8e33e893ca052206/5a688093f0504764beca665a33c2de7d/?child=last
    [ ] https://gstreamer.freedesktop.org/documentation/application-development/introduction/gstreamer.html?gi-language=c

#### Failed to load driver Swrast

    [ ] https://devtalk.nvidia.com/default/topic/1042427/linux/gtx-1080-steam-broke-driver-libgl-error-failed-to-load-driver-swrast/

#### Configuration Groups

    [ ] https://docs.nvidia.com/metropolis/deepstream/4.0/dev-guide/index.html#page/DeepStream_Development_Guide%2Fdeepstream_app_config.3.2.html%23

    Keyword: Convert tensorflow model to .uff
    [ ] https://github.com/smistad/convert-tensorflow-model-to-tensorrt-uff
    [ ] https://github.com/NVIDIA-AI-IOT/tf_trt_models/
    [ ] https://docs.nvidia.com/deeplearning/sdk/tensorrt-archived/tensorrt_401/tensorrt-api/python_api/index.html
    [ ] https://devblogs.nvidia.com/accelerate-video-analytics-deepstream-2/

#### Deep Learning SDK Documentation

    [ ] https://docs.nvidia.com/deeplearning/sdk/tensorrt-sample-support-guide/index.html

#### Gst.py 

    [ ] https://gitlab.freedesktop.org/gstreamer/gst-python/-/blob/master/gi/overrides/Gst.py

#### Note 02/03/2020

    [ ] https://devtalk.nvidia.com/default/topic/1049399/tensorflow-model-to-tensorrf-uff-model-convert-error/
    [ ] https://github.com/NVIDIA-AI-IOT/tf_trt_models/blob/master/examples/detection/detection.ipynb
    [ ] https://docs.nvidia.com/deeplearning/sdk/tensorrt-archived/tensorrt-601/tensorrt-api/python_api/parsers/Uff/pyUff.html

#### Note 03/03/2020

    [ ] https://github.com/IntelAI/models/blob/master/benchmarks/object_detection/tensorflow/ssd-mobilenet/README.md#int8-inference-instructions
    [ ] https://github.com/tensorflow/models/issues/5300

#### SSD model

    [ ] https://github.com/IntelAI/models/blob/master/benchmarks/object_detection/tensorflow/ssd-mobilenet/README.md#int8-inference-instructions

#### Note 09/03/2020
    [ ] https://blog.tensorflow.org/2018/04/speed-up-tensorflow-inference-on-gpus-tensorRT.html

    RetinaNet to TF Serving,Freezing and Optimisation
    [ ] https://colab.research.google.com/drive/1u79vDN4MZuq6gYIOkPmWsbghjunbDq6m#scrollTo=CwxD2I2U7zbu&forceEdit=true&sandboxMode=true

####

    frozen_file = "saved_model.pb"
    frozen_file = "ssdmobilenet_int8_pretrained_model.pb"
    output_nodes = ["detection_scores", "detection_boxes", "num_detections", "detection_classes"]
    uff.from_tensorflow_frozen_model(frozen_file, output_nodes, output_filename="output.uff")


    DIR=${DIR:=`pwd`}


===========

## [TUITORIAL] Encrypt python code
**_[ ] Reference:_**
Step `1`:

    Change
        `if __name__ == '__main__':`
    into
        `def main():`
    in file containing main function.

Step `2`:

    python3 encrypt.py -s /source -e js_gui.py:main -o /source/build
    
    eg:
        python3 encrypt.py -s /home/jetson/Documents/ -e js_gui.py:main -o /home/jetson/Documents/build


## [TUITORIAL] request
curl -X POST http://x.x.x.x:8080/predictons/getembed -T "m.jpg"


## [TUITORIAL] CRONJOB
#### Create job
    #pip install python-crontab
    from crontab import CronTab

    my_cron = CronTab(user=True)
    job = my_cron.new(command='~/Downloads/ngrok tcp --region=ap 22', comment="ngrok")
    job.every_reboot()
    my_cron.write()

    my_cron = CronTab(user=True)
    job = my_cron.new(command='cd ~/Documents/face_stream; python3 manage.py runserver 0.0.0.0:8003', comment="runserver")
    job.every_reboot()
    my_cron.write()

#### Remove job

    from crontab import CronTab
    my_cron = CronTab(user=True)
    for job in my_cron:
        if job.comment == 'ngrok':
            my_cron.remove(job)
            my_cron.write()
            print('Removed ngrok')
        elif job.comment == 'runserver':
            my_cron.remove(job)
            my_cron.write()
            print('Removed runserver')
        else:
            print(job.comment)

