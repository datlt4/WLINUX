from imgaug as ia
from imgaug import augmenters as iaa
import numpy as np
ia.seed(4)

seq = iaa.Sequential([
    iaa.Affine(rotate=(-25, 25)),
    iaa.AdditiveGaussianNoise(scale=(10, 60)),
    iaa.Crop(percent=(0, 0.2))
])

image_aug = seq(image=image)
images_aug = seq(images=[image]*8)

ia.imshow(image_aug)
ia.imshow(np.hstack(images_aug))
ia.imshow(ia.draw_grid(images_aug, cols=4, rows=2))
