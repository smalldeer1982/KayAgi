# 题目信息

# Haar Features

## 题目描述

The first algorithm for detecting a face on the image working in realtime was developed by Paul Viola and Michael Jones in 2001. A part of the algorithm is a procedure that computes Haar features. As part of this task, we consider a simplified model of this concept.

Let's consider a rectangular image that is represented with a table of size $ n×m $ . The table elements are integers that specify the brightness of each pixel in the image.

A feature also is a rectangular table of size $ n×m $ . Each cell of a feature is painted black or white.

To calculate the value of the given feature at the given image, you must perform the following steps. First the table of the feature is put over the table of the image (without rotations or reflections), thus each pixel is entirely covered with either black or white cell. The value of a feature in the image is the value of $ W-B $ , where $ W $ is the total brightness of the pixels in the image, covered with white feature cells, and $ B $ is the total brightness of the pixels covered with black feature cells.

Some examples of the most popular Haar features are given below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/3d348e10da05febca9a35d1c282ccc79140e13d5.png)Your task is to determine the number of operations that are required to calculate the feature by using the so-called prefix rectangles.

A prefix rectangle is any rectangle on the image, the upper left corner of which coincides with the upper left corner of the image.

You have a variable $ value $ , whose value is initially zero. In one operation you can count the sum of pixel values ​​at any prefix rectangle, multiply it by any integer and add to variable $ value $ .

You are given a feature. It is necessary to calculate the minimum number of operations required to calculate the values of this attribute at an arbitrary image. For a better understanding of the statement, read the explanation of the first sample.

## 说明/提示

The first sample corresponds to feature $ B $ , the one shown in the picture. The value of this feature in an image of size $ 6×8 $ equals to the difference of the total brightness of the pixels in the lower and upper half of the image. To calculate its value, perform the following two operations:

1. add the sum of pixels in the prefix rectangle with the lower right corner in the $ 6 $ -th row and $ 8 $ -th column with coefficient $ 1 $ to the variable $ value $ (the rectangle is indicated by a red frame); ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/2a4a67a2e1ced99b2d41037631914ffb613316f1.png)
2. add the number of pixels in the prefix rectangle with the lower right corner in the $ 3 $ -rd row and $ 8 $ -th column with coefficient $ -2 $ and variable $ value $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/f32eba3b14c07c0be2e93f2b2793934534ce56fc.png)

Thus, all the pixels in the lower three rows of the image will be included with factor $ 1 $ , and all pixels in the upper three rows of the image will be included with factor $ 1-2=-1 $ , as required.

## 样例 #1

### 输入

```
6 8
BBBBBBBB
BBBBBBBB
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
WBW
BWW
WWW
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 6
WWBBWW
WWBBWW
WWBBWW
```

### 输出

```
3
```

## 样例 #4

### 输入

```
4 4
BBBB
BBBB
BBBB
BBBW
```

### 输出

```
4
```

# AI分析结果

### 题目内容
#### Haar特征
#### 题目描述
2001年，保罗·维奥拉（Paul Viola）和迈克尔·琼斯（Michael Jones）开发出了首个能实时检测图像中人脸的算法。该算法的一部分是计算Haar特征的过程。作为此任务的一部分，我们考虑这个概念的简化模型。

我们考虑一个矩形图像，用一个 $ n×m $ 的表格来表示。表格中的元素是整数，用于指定图像中每个像素的亮度。

一个特征同样是一个 $ n×m $ 的矩形表格。特征的每个单元格被涂成黑色或白色。

要计算给定特征在给定图像上的值，你必须执行以下步骤。首先，将特征表格覆盖在图像表格上（不进行旋转或翻转），这样每个像素就完全被黑色或白色单元格覆盖。特征在图像中的值为 $ W - B $ ，其中 $ W $ 是图像中被白色特征单元格覆盖的像素的总亮度，$ B $ 是被黑色特征单元格覆盖的像素的总亮度。

下面给出了一些最常见的Haar特征示例。
![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/3d348e10da05febca9a35d1c282ccc79140e13d5.png)
你的任务是确定使用所谓的前缀矩形来计算特征所需的操作次数。

前缀矩形是指图像上的任意矩形，其左上角与图像的左上角重合。

你有一个变量 $ value $ ，其初始值为零。在一次操作中，你可以计算任意前缀矩形中像素值的总和，将其乘以任意整数，然后加到变量 $ value $ 上。

给定一个特征，需要计算在任意图像上计算该特征值所需的最少操作次数。为了更好地理解题意，请阅读第一个样例的解释。
#### 说明/提示
第一个样例对应于图中所示的特征 $ B $ 。在一个 $ 6×8 $ 大小的图像中，该特征的值等于图像下半部分和上半部分像素总亮度的差值。要计算其值，执行以下两个操作：
1. 将右下角位于第 $ 6 $ 行和第 $ 8 $ 列的前缀矩形中的像素总和乘以系数 $ 1 $ 加到变量 $ value $ 上（该矩形用红色框表示）；
![示例图片1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/2a4a67a2e1ced99b2d41037631914ffb613316f1.png)
2. 将右下角位于第 $ 3 $ 行和第 $ 8 $ 列的前缀矩形中的像素总和乘以系数 $ -2 $ 加到变量 $ value $ 上。
![示例图片2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/f32eba3b14c07c0be2e93f2b2793934534ce56fc.png)
这样，图像下三行的所有像素将以系数 $ 1 $ 包含在内，图像上三行的所有像素将以系数 $ 1 - 2 = -1 $ 包含在内，符合要求。
#### 样例 #1
**输入**
```
6 8
BBBBBBBB
BBBBBBBB
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
```
**输出**
```
2
```
#### 样例 #2
**输入**
```
3 3
WBW
BWW
WWW
```
**输出**
```
4
```
#### 样例 #3
**输入**
```
3 6
WWBBWW
WWBBWW
WWBBWW
```
**输出**
```
3
```
#### 样例 #4
**输入**
```
4 4
BBBB
BBBB
BBBB
BBBW
```
**输出**
```
4
```
### 算法分类
模拟
### 题解综合分析与结论
所有题解思路大致相同，均利用数据范围小的特点采用暴力模拟。核心思路是从矩阵右下角向左上角倒序遍历，遇到当前位置值与目标矩阵不同时，对左上角区域进行整体修改并记录操作次数。这样做能避免正序遍历带来的覆盖问题。各题解在代码实现上有些许差异，如变量命名、输入输出优化等，但整体逻辑相似，且都未对暴力算法进行本质优化，所以所有题解均未达到4星。
### 通用建议与扩展思路
- **优化方向**：若数据范围增大，可考虑使用二维线段树或二维树状数组进行区间处理，将时间复杂度从 $ O(n^4) $ 优化到 $ O(nm\log(nm)) $ 。
- **思维拓展**：解决此类问题关键在于理解操作对矩阵元素的影响，通过合理的遍历顺序避免数据覆盖问题。对于类似需要对矩阵进行多次操作并统计次数的题目，都可尝试从操作顺序、数据结构优化等角度思考。
### 相似知识点洛谷题目
- [P3397 地毯](https://www.luogu.com.cn/problem/P3397)：涉及矩阵区间修改与查询，可通过二维前缀和或二维树状数组解决，与本题对矩阵操作有相似之处。
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：同样是对矩阵元素进行处理，通过动态规划思想解决，在处理矩阵问题的思维方式上有相通点。
- [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)：利用前缀和思想解决区间统计问题，与本题利用前缀矩形概念有相似的思维模式。 

---
处理用时：45.00秒