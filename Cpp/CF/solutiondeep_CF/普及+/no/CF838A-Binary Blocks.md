# 题目信息

# Binary Blocks

## 题目描述

You are given an image, that can be represented with a $ 2 $ -d $ n $ by $ m $ grid of pixels. Each pixel of the image is either on or off, denoted by the characters "0" or "1", respectively. You would like to compress this image. You want to choose an integer $ k&gt;1 $ and split the image into $ k $ by $ k $ blocks. If $ n $ and $ m $ are not divisible by $ k $ , the image is padded with only zeros on the right and bottom so that they are divisible by $ k $ . Each pixel in each individual block must have the same value. The given image may not be compressible in its current state. Find the minimum number of pixels you need to toggle (after padding) in order for the image to be compressible for some $ k $ . More specifically, the steps are to first choose $ k $ , then the image is padded with zeros, then, we can toggle the pixels so it is compressible for this $ k $ . The image must be compressible in that state.

## 说明/提示

We first choose $ k=2 $ .

The image is padded as follows:

`<br></br>001000<br></br>101100<br></br>110010<br></br>000000<br></br>`We can toggle the image to look as follows:

`<br></br>001100<br></br>001100<br></br>000000<br></br>000000<br></br>`We can see that this image is compressible for $ k=2 $ .

## 样例 #1

### 输入

```
3 5
00100
10110
11001
```

### 输出

```
5
```

# AI分析结果

### 题目内容
# Binary Blocks

## 题目描述
给定一幅图像，可用一个二维的 \(n\times m\) 像素网格表示。图像的每个像素要么是开启状态，要么是关闭状态，分别用字符“0”或“1”表示。你想要压缩这幅图像。你需要选择一个整数 \(k > 1\)，并将图像分割成 \(k\times k\) 的块。如果 \(n\) 和 \(m\) 不能被 \(k\) 整除，则在图像的右侧和底部仅用零填充，使其能被 \(k\) 整除。每个单独块中的每个像素必须具有相同的值。给定的图像在其当前状态下可能不可压缩。求为了使图像对于某个 \(k\) 可压缩，你需要切换的最少像素数（在填充之后）。更具体地说，步骤是先选择 \(k\)，然后用零填充图像，接着，我们可以切换像素，使其对于这个 \(k\) 可压缩。图像在该状态下必须是可压缩的。

## 说明/提示
我们首先选择 \(k = 2\)。
图像填充如下：
```
001000
101100
110010
000000
```
我们可以将图像切换为如下形式：
```
001100
001100
000000
000000
```
我们可以看到，这幅图像对于 \(k = 2\) 是可压缩的。

## 样例 #1
### 输入
```
3 5
00100
10110
11001
```
### 输出
```
5
```

### 算法分类
枚举、前缀和

### 题解综合分析与结论
三道题解思路基本一致，均是通过枚举 \(k\) 的值，并利用二维前缀和来计算每个 \(k\times k\) 块内需要切换的最少像素数，从而得出整个图像需要切换的最少像素数。不同点在于第三道题解对 \(k\) 的取值进行了优化，只选取质数作为 \(k\) 的值，降低了时间复杂度。

### 所选的题解
- **作者：KaguyaH (5星)**
    - **关键亮点**：对 \(k\) 的取值进行优化，指出若 \(d | k \land 1 < d < k\)，则 \(d\) 必然不劣于 \(k\)，所以 \(k\) 选质数即可，将时间复杂度从 \(\mathcal O(n^2 \log n)\) 优化到 \(\mathcal O(n^2)\)。
    - **重点代码**：
```cpp
static inline const bool is_prime(const hu x) {
    if (x < 2) return false;
    for (hu i(2); i < x; ++i) if (not(x % i)) return false;
    return true;
}
//...
for (hu i(2); i <= n or i <= m; ++i) if (is_prime(i)) amin(ans, nt(i));
```
核心实现思想：通过 `is_prime` 函数判断 \(k\) 是否为质数，仅对质数 \(k\) 计算切换像素数并更新最小值。

### 最优关键思路或技巧
利用二维前缀和快速计算每个 \(k\times k\) 块内的 \(1\) 的数量，从而快速得出每个块需要切换的最少像素数。并且通过分析得出 \(k\) 取质数时不会遗漏最优解，优化了枚举 \(k\) 的范围，降低时间复杂度。

### 可拓展思路
此类题目属于图像压缩与矩阵处理结合的问题，类似套路是通过合理的数据结构（如前缀和）优化对矩阵子区域的计算，通过数学分析优化枚举范围。同类型题可能会改变块的形状、改变填充规则或改变压缩条件等。

### 洛谷相似题目推荐
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：同样涉及矩阵处理，通过动态规划和前缀和思想解决在矩阵中寻找最大正方形的问题。
- [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)：在矩阵中寻找满足条件的最小子正方形，可通过二维前缀和优化计算子矩阵的最值。
- [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)：求矩阵中加权和最大的子矩形，同样可以利用前缀和优化计算子矩阵的和。 

---
处理用时：47.06秒