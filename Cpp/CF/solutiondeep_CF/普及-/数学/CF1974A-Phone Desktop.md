# 题目信息

# Phone Desktop

## 题目描述

Little Rosie has a phone with a desktop (or launcher, as it is also called). The desktop can consist of several screens. Each screen is represented as a grid of size $ 5 \times 3 $ , i.e., five rows and three columns.

There are $ x $ applications with an icon size of $ 1 \times 1 $ cells; such an icon occupies only one cell of the screen. There are also $ y $ applications with an icon size of $ 2 \times 2 $ cells; such an icon occupies a square of $ 4 $ cells on the screen. Each cell of each screen can be occupied by no more than one icon.

Rosie wants to place the application icons on the minimum number of screens. Help her find the minimum number of screens needed.

## 说明/提示

The solution for the first test case can look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/50fee263eb8faff81a1a0ba84255a68bc5871ae1.png) Blue squares represent empty spaces for icons, green squares represent $ 1 \times 1 $ icons, red squares represent $ 2 \times 2 $ iconsThe solution for the third test case can look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/53e483ebe35e12a51af69c31e4cb0b1e5b05aee6.png)

## 样例 #1

### 输入

```
11
1 1
7 2
12 4
0 3
1 0
8 1
0 0
2 0
15 0
8 2
0 9```

### 输出

```
1
1
2
2
1
1
0
1
1
2
5```

# AI分析结果

### 题目内容重写

#### 手机桌面

**题目描述**

小Rosie有一个手机，手机上有一个桌面（也称为启动器）。桌面可以由多个屏幕组成。每个屏幕表示为一个$5 \times 3$的网格，即五行三列。

有$x$个应用程序的图标大小为$1 \times 1$单元格；这样的图标只占据屏幕上的一个单元格。还有$y$个应用程序的图标大小为$2 \times 2$单元格；这样的图标占据屏幕上的$4$个单元格。每个屏幕的每个单元格最多只能被一个图标占据。

Rosie希望将应用程序图标放置在尽可能少的屏幕上。帮助她找到所需的最少屏幕数。

**说明/提示**

第一个测试用例的解决方案可以如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/50fee263eb8faff81a1a0ba84255a68bc5871ae1.png) 蓝色方块表示图标的空位，绿色方块表示$1 \times 1$图标，红色方块表示$2 \times 2$图标。第三个测试用例的解决方案可以如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/53e483ebe35e12a51af69c31e4cb0b1e5b05aee6.png)

**样例 #1**

**输入**

```
11
1 1
7 2
12 4
0 3
1 0
8 1
0 0
2 0
15 0
8 2
0 9```

**输出**

```
1
1
2
2
1
1
0
1
1
2
5```

### 综合分析与结论

由于目前没有提供具体的题解，我将根据题目描述和常见解题思路进行分析。

#### 解题思路

1. **问题分析**：
   - 每个屏幕有$5 \times 3 = 15$个单元格。
   - $2 \times 2$图标占据4个单元格，$1 \times 1$图标占据1个单元格。
   - 需要计算放置所有图标所需的最少屏幕数。

2. **关键点**：
   - 优先放置$2 \times 2$图标，因为它们占据更多空间。
   - 计算每个屏幕能放置的$2 \times 2$图标数量，以及剩余的$1 \times 1$图标数量。

3. **算法步骤**：
   - 计算每个屏幕最多能放置的$2 \times 2$图标数量。
   - 计算剩余空间能放置的$1 \times 1$图标数量。
   - 根据图标数量计算所需的最少屏幕数。

#### 通用建议与扩展思路

- **优化思路**：
  - 优先处理$2 \times 2$图标，因为它们对屏幕空间的占用更大。
  - 考虑屏幕空间的利用率，尽量减少浪费的单元格。

- **扩展思路**：
  - 类似的问题可以扩展到其他尺寸的图标或不同大小的屏幕。
  - 可以考虑动态规划或贪心算法来优化屏幕的利用率。

#### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

这些题目都涉及到空间分配和优化问题，与本题有相似的解题思路。

---
处理用时：27.37秒