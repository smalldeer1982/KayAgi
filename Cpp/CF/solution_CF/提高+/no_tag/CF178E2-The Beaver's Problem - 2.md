# The Beaver's Problem - 2

## 题目描述

Offering the ABBYY Cup participants a problem written by the Smart Beaver is becoming a tradition. He proposed the following problem.

You are given a monochrome image, that is, an image that is composed of two colors (black and white). The image is given in raster form, that is, as a matrix of pixels' colors, and the matrix's size coincides with the size of the image.

The white color on the given image corresponds to the background. Also, the image contains several black geometric shapes. It is known that the image can contain only two types of shapes: squares and circles. Your task is to count the number of circles and the number of squares which the given image contains.

The squares on the image can be rotated arbitrarily. In addition, the image can possibly contain some noise arranged as follows: each pixel of the original image can change its color to the opposite with the probability of $ 20 $ %.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E2/575cc300a436bc791f059ed1604954db020e4792.png) An example of an image that has no noise and the sides of the squares are parallel to the coordinate axes (two circles and three squares).   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E2/5a255ee1bca061f5ff62a305107ac74540469a88.png) An example of an image that has no noise and the squares are rotated arbitrarily (two circles and three squares).   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E2/6588309d80aee82245c95133dff3b167b5dbc7e6.png) An example of an image that has noise and the squares are rotated arbitrarily (one circle and three squares).

## 说明/提示

You are given a sample of original data for each difficulty level. The samples are available at http://codeforces.ru/static/materials/contests/178/e-samples.zip .

