# 题目信息

# Parallelogram is Back

## 题目描述

Long time ago Alex created an interesting problem about parallelogram. The input data for this problem contained four integer points on the Cartesian plane, that defined the set of vertices of some non-degenerate (positive area) parallelogram. Points not necessary were given in the order of clockwise or counterclockwise traversal.

Alex had very nice test for this problem, but is somehow happened that the last line of the input was lost and now he has only three out of four points of the original parallelogram. He remembers that test was so good that he asks you to restore it given only these three points.

## 说明/提示

If you need clarification of what parallelogram is, please check Wikipedia page:

https://en.wikipedia.org/wiki/Parallelogram

## 样例 #1

### 输入

```
0 0
1 0
0 1
```

### 输出

```
3
1 -1
-1 1
1 1
```

# AI分析结果

### 题目中文重写
# 平行四边形回归

## 题目描述
很久以前，亚历克斯（Alex）想出了一个关于平行四边形的有趣问题。这个问题的输入数据包含笛卡尔平面上的四个整数点，这些点定义了某个非退化（面积为正）平行四边形的顶点集。点的输入顺序不一定是顺时针或逆时针遍历的顺序。

亚历克斯原本有一个非常好的测试用例，但不知怎么的，输入的最后一行丢失了，现在他只有原始平行四边形四个点中的三个点。他记得这个测试用例非常好，所以他要求你仅根据这三个点来还原第四个点。

## 说明/提示
如果你需要明确平行四边形的定义，请查看维基百科页面：
https://en.wikipedia.org/wiki/Parallelogram

## 样例 #1
### 输入
```
0 0
1 0
0 1
```
### 输出
```
3
1 -1
-1 1
1 1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用平行四边形对角线互相平分这一数学性质来求解第四个顶点的坐标。各题解的思路基本一致，只是在代码实现和表述方式上略有不同。

### 题解评分与选择
- **Mickey_jj（5星）**：关键亮点在于思路清晰，通过图形直观展示了答案的由来，代码简洁明了。
- **泠小毒（4星）**：思路简洁，直接指出是简单数学推导，代码实现也较为简洁。
- **Eason_AC（4星）**：详细推导了利用平行四边形对角线互相平分得出的坐标计算公式，逻辑严谨。

### 重点代码及核心实现思想
#### Mickey_jj的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[5],y[5];
int main()
{
    for(int i=1;i<4;i++){
        cin>>x[i]>>y[i];
    }
    printf("%d\n",3);
    printf("%d %d\n",x[1]+x[2]-x[3],y[1]+y[2]-y[3]);
    printf("%d %d\n",x[1]+x[3]-x[2],y[1]+y[3]-y[2]);
    printf("%d %d\n",x[3]+x[2]-x[1],y[3]+y[2]-y[1]);
    return 0;
}
```
核心实现思想：利用平行四边形对角线互相平分，即若平行四边形四个顶点坐标为 \(A(x_A,y_A)\)、\(B(x_B,y_B)\)、\(C(x_C,y_C)\)、\(D(x_D,y_D)\)，且 \(AC\)、\(BD\) 为对角线，则 \(x_A + x_C = x_B + x_D\)，\(y_A + y_C = y_B + y_D\)，通过已知的三个点坐标计算出第四个点的三种可能坐标。

#### 泠小毒的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],b[5],suma,sumb;
int main()
{
    for(int i=1;i<=3;i++)scanf("%d%d",&a[i],&b[i]),suma+=a[i],sumb+=b[i];
    puts("3");
    for(int i=1;i<=3;i++)printf("%d %d\n",suma-2*a[i],sumb-2*b[i]);
    return 0;
}
```
核心实现思想：先计算出三个已知点的 \(x\) 坐标和 \(suma\) 以及 \(y\) 坐标和 \(sumb\)，根据平行四边形对角线互相平分的性质，第四个点的坐标可以通过 \(suma - 2\times\) 当前点的 \(x\) 坐标和 \(sumb - 2\times\) 当前点的 \(y\) 坐标得到。

#### Eason_AC的代码
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int x1, y1, x2, y2, x3, y3;

int main() {
    scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
    printf("3\n%d %d\n%d %d\n%d %d", x2 + x3 - x1, y2 + y3 - y1, x1 + x3 - x2, y1 + y3 - y2, x1 + x2 - x3, y1 + y2 - y3);
}
```
核心实现思想：同样基于平行四边形对角线互相平分的性质，推导出第四个点的三种可能坐标公式并直接输出。

### 最优关键思路或技巧
利用平行四边形对角线互相平分的性质，将几何问题转化为代数问题，通过坐标运算求解第四个顶点的坐标。

### 可拓展之处
同类型题目可能会涉及到在不同几何图形中，根据部分顶点坐标求解其他顶点坐标，或者在三维空间中求解平行六面体等类似图形的顶点坐标，解题思路依然是利用图形的几何性质建立坐标之间的关系。

### 推荐洛谷题目
- P1355 神秘大三角：考察三角形相关的几何计算。
- P1888 三角函数：涉及三角函数的数学计算。
- P2670 扫雷游戏：需要运用一定的逻辑推理和数学思维。

### 个人心得摘录与总结
- **FCB_Yiyang2006✈**：因看到自己题解的一些评价不爽，从而想通过写这篇题解展示实力，并且提到该题的思路来源于函数课上学到的知识。总结：他人的评价可能会激发创作者的动力，同时学习新知识后要善于运用到解题中。
- **Mickey_jj**：提到楼下有人在题解里骂自己，不爽之下发了这篇暴力解法的题解。总结：网络交流中可能会遇到不友好的评价，但应专注于分享自己的解题思路。 

---
处理用时：35.88秒