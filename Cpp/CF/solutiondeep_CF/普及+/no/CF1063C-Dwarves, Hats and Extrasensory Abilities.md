# 题目信息

# Dwarves, Hats and Extrasensory Abilities

## 题目描述

This is an interactive problem.

In good old times dwarves tried to develop extrasensory abilities:

- Exactly $ n $ dwarves entered completely dark cave.
- Each dwarf received a hat — white or black. While in cave, none of the dwarves was able to see either his own hat or hats of other Dwarves.
- Dwarves went out of the cave to the meadow and sat at an arbitrary place one after the other. When a dwarf leaves the cave, he sees the colors of all hats of all dwarves that are seating on the meadow (i.e. left the cave before him). However, he is not able to see the color of his own hat and none of the dwarves can give him this information.
- The task for dwarves was to got diverged into two parts — one with dwarves with white hats and one with black hats.

After many centuries, dwarves finally managed to select the right place on the meadow without error. Will you be able to repeat their success?

You are asked to successively name $ n $ different integer points on the plane. After naming each new point you will be given its color — black or white. Your task is to ensure that the named points can be split by a line in such a way that all points of one color lie on the same side from the line and points of different colors lie on different sides. Moreover, no points can belong to the line. Also, you need to report any such line at the end of the process.

In this problem, the interactor is adaptive — the colors of the points in the tests are not fixed beforehand and the jury program can select them arbitrarily, in particular, depending on your program output.

## 说明/提示

In the sample input and output values are aligned only for simplicity of interpreting them chronologically. In real interaction no "extra" line breaks should appear.

The following picture illustrates the first test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1063C/8b02508632dfd30b29a40bae68412cf975775dd4.png)

## 样例 #1

### 输入

```
5

black

black

white

white

black```

### 输出

```

0 0

3 1

2 3

4 4

0 2

1 3 4 1```

# AI分析结果

### 题目翻译
# 矮人、帽子与超感官能力

## 题目描述
这是一道交互题。
在过去的美好时光里，矮人试图开发超感官能力：
- 恰好有 \(n\) 个矮人进入一个完全黑暗的洞穴。
- 每个矮人会得到一顶帽子，帽子颜色为白色或黑色。在洞穴中时，没有一个矮人能够看到自己的帽子或其他矮人的帽子。
- 矮人依次走出洞穴来到草地上，并随意找个位置坐下。当一个矮人离开洞穴时，他能看到所有已经坐在草地上（即比他先离开洞穴）的矮人的帽子颜色。然而，他看不到自己帽子的颜色，并且其他矮人也不能给他提供这个信息。
- 矮人的任务是分成两组，一组是戴白色帽子的矮人，另一组是戴黑色帽子的矮人。

经过数个世纪，矮人终于成功无误地在草地上找到了正确的位置。你能重复他们的成功吗？

要求你依次给出 \(n\) 个不同的平面整点。每次给出一个新点后，你会被告知该点的颜色——黑色或白色。你的任务是确保所给出的点可以被一条直线分割，使得同一种颜色的所有点都在直线的同一侧，不同颜色的点在直线的两侧。此外，没有点可以在直线上。最后，你还需要报告这样的一条直线。

在本题中，交互器是自适应的——测试中的点的颜色不是预先确定的，评测程序可以任意选择，特别是可以根据你的程序输出进行选择。

## 说明/提示
在示例输入和输出中，值的排列仅是为了按时间顺序解释它们时更简单。在实际交互中不应出现“额外”的换行符。

以下图片说明了第一个测试用例。
![图片链接](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1063C/8b02508632dfd30b29a40bae68412cf975775dd4.png)

## 样例 #1
### 输入
```
5

black

black

white

white

black
```
### 输出
```
0 0

3 1

2 3

4 4

0 2

1 3 4 1
```

### 算法分类
二分

### 综合分析与结论
这些题解都采用二分的思路来解决问题，核心是通过二分找到能将黑白点分开的边界，进而确定分隔直线。不同题解的主要差异在于点的放置方式以及确定分隔直线的具体方法。有的题解将点放在一条直线上二分，有的放在对角线上，还有的在点阵中二分，各有优劣。

### 所选的题解
- **作者：封禁用户 (星级：4星)**
  - **关键亮点**：提出将点放在对角线上二分的方法，避免了放在一条直线上可能出现的玄学错误，思路较为独特。
  - **重点代码核心实现思想**：通过不断二分对角线上的点，根据点的颜色调整左右边界，最后根据边界情况输出分隔直线。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double mid, l, r;
string s, sl = "hello";
bool same = 1;
int main()
{
    cin >> n;
    l = 1;
    r = 999999999;
    while(n--)
    {
        mid = (l + r + 1) / 2.0;
        cout << int(mid) << " " << int(mid) << endl;
        cin >> s;
        if(s == "black")
        {
            l = int(mid + 1);
        }
        else
        {
            r = int(mid - 1);
        }
        if(sl!= "hello" && sl!= s)
        {
            same = 0;
        }
        sl = s;
    }
    if(same)
    {
        cout << "0 999999999 1 1000000000";
        return 0;
    }
    mid = (l + r) / 2.0;
    cout << int(mid - 0.5) << ' ' << int(mid + 0.5) << ' ' << int(mid + 0.5) << ' ' << int(mid - 0.5);
    return 0;
}
```
- **作者：KaguyaH (星级：4星)**
  - **关键亮点**：考虑在点阵中对横纵坐标均为奇数的关键点编号后二分，有效避免了直线上二分可能出现的问题，并且详细说明了如何根据边界点确定分隔直线，思路清晰全面。
  - **重点代码核心实现思想**：先对关键点编号，二分确定边界点，再根据边界点坐标和斜率要求确定分隔直线的两个端点并输出。
```cpp
enum { X = (const uint)1e9, Y = (const uint)1e9 };
static const llu N(1ull * (X / 2) * (Y / 2));
static inline const uint hashx(const llu x) { return x / (Y / 2) * 2 + 1; }
static inline const uint hashy(const llu x) { return x % (Y / 2) * 2 + 1; }
static inline const void cut(const llu k) {
    const uint x(hashx(k)), y(hashy(k));
    printf("%u %u %u %u\n", x, y + 1, y < Y / 2? x - 1 : x + 1, y < Y / 2? Y : 0);
}
static inline const void main() {
    scanf("%hu", &n);
    llu l(0), r(N);
    for (hu i(0); i < n; ++i) {
        const llu m((l + r) / 2);
        (check(m)? l : r) = m;
    }
    cut(l);
}
```

### 最优关键思路或技巧
将点放在点阵中编号二分，避免在直线上二分可能出现的错误，同时合理利用点的坐标特性来确定分隔直线，这种方法在解决此类二分交互问题时较为稳健。

### 可拓展之处
此类交互二分问题常见于通过不断询问获取信息并确定边界的场景。类似套路是根据题目条件设计合适的数据结构（如本题中的点阵）来辅助二分，同时注意边界情况和特殊情况的处理。

### 洛谷相似题目推荐
- [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)
- [P2678 [NOIP2015 普及组] 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录与总结
 - **作者：封禁用户**：提到将点放在一条直线上二分可能出现玄学错误，通过将点放在对角线上并调参成功通过，说明在实际做题中要注意一些隐藏的边界或特殊情况，尝试不同方法解决问题。 

---
处理用时：57.89秒