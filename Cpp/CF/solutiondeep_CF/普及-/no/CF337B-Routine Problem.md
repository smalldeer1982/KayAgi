# 题目信息

# Routine Problem

## 题目描述

Manao has a monitor. The screen of the monitor has horizontal to vertical length ratio $ a $ : $ b $ . Now he is going to watch a movie. The movie's frame has horizontal to vertical length ratio $ c $ : $ d $ . Manao adjusts the view in such a way that the movie preserves the original frame ratio, but also occupies as much space on the screen as possible and fits within it completely. Thus, he may have to zoom the movie in or out, but Manao will always change the frame proportionally in both dimensions.

Calculate the ratio of empty screen (the part of the screen not occupied by the movie) to the total screen size. Print the answer as an irreducible fraction $ p/q $ .

## 说明/提示

Sample 1. Manao's monitor has a square screen. The movie has 3:2 horizontal to vertical length ratio. Obviously, the movie occupies most of the screen if the width of the picture coincides with the width of the screen. In this case, only 2/3 of the monitor will project the movie in the horizontal dimension: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337B/429cc762b90fac9b9969eeb0bd54bb3278635967.png)

Sample 2. This time the monitor's width is 4/3 times larger than its height and the movie's frame is square. In this case, the picture must take up the whole monitor in the vertical dimension and only 3/4 in the horizontal dimension: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337B/9da098e1ff076f33756d107ad7616fb9b6b441f1.png)

## 样例 #1

### 输入

```
1 1 3 2
```

### 输出

```
1/3
```

## 样例 #2

### 输入

```
4 3 2 2
```

### 输出

```
1/4
```

# AI分析结果

### 题目内容
# 日常问题

## 题目描述
马瑙有一台显示器。显示器屏幕的横纵长度比为 $a$ : $b$ 。现在他打算看一部电影。电影画面的横纵长度比为 $c$ : $d$ 。马瑙进行调整，使得电影保持原始画面比例，同时尽可能多地占据屏幕空间，并且完全适配屏幕。因此，他可能需要对电影进行放大或缩小，但马瑙总是会在两个维度上按比例改变画面。

计算屏幕空白部分（未被电影占据的屏幕部分）与屏幕总面积的比例。将答案表示为最简分数 $p/q$ 。

## 说明/提示
样例1。马瑙的显示器屏幕是正方形的。电影的横纵长度比为3:2。显然，如果画面的宽度与屏幕的宽度一致，电影就能占据屏幕的大部分空间。在这种情况下，在水平方向上，只有2/3的显示器会投射电影画面：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337B/429cc762b90fac9b9969eeb0bd54bb3278635967.png)

样例2。这次显示器的宽度是高度的4/3倍，而电影画面是正方形的。在这种情况下，画面必须在垂直方向上占据整个显示器，而在水平方向上只占据3/4：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337B/9da098e1ff076f33756d107ad7616fb9b6b441f1.png)

## 样例 #1
### 输入
```
1 1 3 2
```
### 输出
```
1/3
```

## 样例 #2
### 输入
```
4 3 2 2
```
### 输出
```
1/4
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路均是通过统一屏幕与电影画面的长或宽，来计算空白部分与屏幕总面积的比例。具体要点为：
 - **思路**：考虑两种情况，一是让电影画面的长与屏幕的长相等，二是让电影画面的宽与屏幕的宽相等，分别计算这两种情况下空白部分占屏幕总面积的比例，然后取较小值输出。
 - **算法要点**：统一比例时，若统一长，则将屏幕比例$a:b$和电影比例$c:d$化为$(a×c):(b×c)$与$(c×a):(d×a)$；若统一宽，则化为$(a×d):(b×d)$与$(c×b):(d×b)$。之后分别计算空白部分与屏幕总面积的比例。
 - **解决难点**：在于理解如何通过统一比例来计算空白部分面积比，以及最后对结果进行约分得到最简分数。

### 通用建议与扩展思路
通用建议：在解决此类问题时，要清晰理解比例关系的转换以及面积比的计算逻辑。代码实现上，注意最大公约数计算函数的正确使用以实现约分。
扩展思路：同类型题可涉及不同形状图形的比例适配问题，类似算法套路是通过统一某一维度的量，来计算相关比例或面积等。例如不同长宽比矩形的嵌套，或圆形与矩形的适配等场景。

### 推荐题目
 - [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：考察对数学中质因数分解概念的理解与实现。
 - [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：需要通过找规律和数学推导来解决问题。
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：涉及数学中的等差数列知识以及枚举思想。 

---
处理用时：38.62秒