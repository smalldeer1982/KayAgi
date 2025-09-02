# 题目信息

# Pyramids

## 题目描述

IT City administration has no rest because of the fame of the Pyramids in Egypt. There is a project of construction of pyramid complex near the city in the place called Emerald Walley. The distinction of the complex is that its pyramids will be not only quadrangular as in Egypt but also triangular and pentagonal. Of course the amount of the city budget funds for the construction depends on the pyramids' volume. Your task is to calculate the volume of the pilot project consisting of three pyramids — one triangular, one quadrangular and one pentagonal.

The first pyramid has equilateral triangle as its base, and all 6 edges of the pyramid have equal length. The second pyramid has a square as its base and all 8 edges of the pyramid have equal length. The third pyramid has a regular pentagon as its base and all 10 edges of the pyramid have equal length.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630Q/112717337cf1125078951016c57ed1b9db5b5a6b.png)

## 样例 #1

### 输入

```
2 5 3
```

### 输出

```
38.546168065709```

# AI分析结果

### 题目内容
# 金字塔

## 题目描述
IT 城的行政部门因为埃及金字塔的声名而不得安宁。在城市附近一个叫做翡翠谷的地方，有一个建造金字塔建筑群的项目。该建筑群的独特之处在于，其金字塔不仅有像埃及那样的四边形底面，还有三角形和五边形底面。当然，城市预算中用于建设的资金数额取决于金字塔的体积。你的任务是计算由三个金字塔组成的试点项目的体积，这三个金字塔分别是一个三角形底面的、一个四边形底面的和一个五边形底面的。

第一个金字塔底面是等边三角形，且金字塔的所有 6 条棱长度相等。第二个金字塔底面是正方形，且金字塔的所有 8 条棱长度相等。第三个金字塔底面是正五边形，且金字塔的所有 10 条棱长度相等。

![金字塔示意图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630Q/112717337cf1125078951016c57ed1b9db5b5a6b.png)

## 样例 #1
### 输入
```
2 5 3
```
### 输出
```
38.546168065709
```

### 算法分类
数学

### 综合分析与结论
这几道题解的核心都是围绕正三棱锥、正四棱锥和正五棱锥体积公式展开。有的题解先推导通用的正\(n\)棱锥体积公式，再代入\(n=3,4,5\)计算；有的题解则直接给出这三种棱锥的体积公式并编码实现。解决难点在于如何由棱长推导出棱锥的高和底面积从而得出体积公式。

### 所选的题解
 - **作者：封禁用户（5星）**
    - **关键亮点**：详细证明了正\(n\)棱锥体积公式，从通用的棱锥体积公式\(V = \frac{1}{3}Sh\)出发，通过对正\(n\)边形底面的分析得出底面积公式，再通过构造直角三角形利用勾股定理得出高的公式，最终推导出完整体积公式，逻辑清晰，推导过程详细。
    - **重点代码**：无代码，但推导过程为：
        - 正\(n\)棱锥底面正\(n\)边形，边长为\(l_n\)，过中心分为\(n\)个等腰三角形，顶角为\(\frac{2\pi}{n}\)，底边为\(l_n\)，可得底面积\(S=\frac{l_n^2}{4\tan\frac{\pi}{n}}\)。
        - 构造三角形，\(A\)为底面顶点，\(H\)为棱锥顶点，\(OH\)为高，由等腰三角形腰长\(OA = \frac{l_n}{\sin\frac{\pi}{n}}\)，\(AH = l_n\)，根据勾股定理得\(OH = l_n\sqrt{1 - \frac{1}{4\sin^2\frac{\pi}{n}}}\)。
        - 所以体积\(V=\frac{l_n^3n}{12\tan\frac{\pi}{n}}\sqrt{1 - \frac{1}{4\sin^2\frac{\pi}{n}}}\)。
 - **作者：__main__（4星）**
    - **关键亮点**：直接采用正\(n\)棱锥体积公式模拟计算，代码简洁明了，同时提醒了\(\pi\)取值要精确。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const double PI = 3.1415926535898;
double f(double l, double n)
{
    return l * l * l * n / (12 * tan(PI / n)) * sqrt(1 - 1 / (4 * sin(PI / n) * sin(PI / n)));
}
int main()
{
    int l3, l4, l5;
    scanf("%d%d%d", &l3, &l4, &l5);
    printf("%.9f\n", f(l3, 3) + f(l4, 4) + f(l5, 5));
    return 0;
}
```
核心实现思想：定义函数\(f\)计算正\(n\)棱锥体积，在\(main\)函数中读入三条棱长，调用\(f\)函数并将结果累加输出。

### 最优关键思路或技巧
推导并利用正\(n\)棱锥体积公式，通过分析底面正多边形和棱锥的几何关系得出底面积和高的表达式，进而得到体积公式。在代码实现中要注意像\(\pi\)等常量取值的精度问题。

### 可拓展之处
此类题目属于立体几何与数学公式推导结合的类型，类似的题目还可能涉及不同底面形状（如六边形、八边形等）的棱锥或棱柱体积计算，或者在已知体积等条件下反推棱长等参数。解题套路通常是先根据几何图形性质推导出相关公式，再进行计算。

### 洛谷相似题目推荐
 - P1009 [阶乘之和](https://www.luogu.com.cn/problem/P1009)：涉及数学运算和高精度计算。
 - P1147 连续自然数和：考查数学推理和枚举技巧。
 - P1307 数字反转：通过数学方法对数字进行处理。 

---
处理用时：52.64秒