# 题目信息

# [USACO07JAN] Protecting the Flowers S

## 题目描述

Farmer John went to cut some wood and left N (2 ≤ N ≤ 100,000) cows eating the grass, as usual. When he returned, he found to his horror that the cluster of cows was in his garden eating his beautiful flowers. Wanting to minimize the subsequent damage, FJ decided to take immediate action and transport each cow back to its own barn.

Each cow i is at a location that is Ti minutes (1 ≤ Ti ≤ 2,000,000) away from its own barn. Furthermore, while waiting for transport, she destroys Di (1 ≤ Di ≤ 100) flowers per minute. No matter how hard he tries, FJ can only transport one cow at a time back to her barn. Moving cow i to its barn requires 2 × Ti minutes (Ti to get there and Ti to return). FJ starts at the flower patch, transports the cow to its barn, and then walks back to the flowers, taking no extra time to get to the next cow that needs transport.

Write a program to determine the order in which FJ should pick up the cows so that the total number of flowers destroyed is minimized.

有 $n$ 头奶牛跑到 FJ 的花园里去吃花儿了，它们分别在距离牛圈 $T_i$（这里指 FJ 到那里需要 $T_i$ 分钟) 处吃花，每分钟会吃掉 $D_i$ 朵花，FJ 现在要将它们给弄回牛圈，但是他每次只能弄一头回去，来回用时总共为 $2 \times T_i$ 分钟，在这段时间内，其它的奶牛会继续吃 FJ 的花，速度保持不变，当然正在被赶回牛圈的奶牛不能继续吃了。现在求在最好的方案下奶牛吃掉花的最小朵数。


## 说明/提示

FJ returns the cows in the following order: 6, 2, 3, 4, 1, 5. While he is transporting cow 6 to the barn, the others destroy 24 flowers; next he will take cow 2, losing 28 more of his beautiful flora. For the cows 3, 4, 1 he loses 16, 12, and 6 flowers respectively. When he picks cow 5 there are no more cows damaging the flowers, so the loss for that cow is zero. The total flowers lost this way is 24 + 28 + 16 + 12 + 6 = 86.


## 样例 #1

### 输入

```
6
3 1
2 5
2 3
3 2
4 1
1 6```

### 输出

```
86```

# AI分析结果

### 综合分析与结论
这些题解均围绕贪心算法解决该问题，核心思路是通过比较不同牛的运输顺序对总吃花量的影响，确定最优排序规则。具体做法是分析两头牛的运输顺序，根据吃花损失大小得出排序条件，再对所有牛排序，最后计算总吃花量。部分题解采用前缀和优化计算过程。

### 所选题解
- **曦行夜落（5星）**
    - **关键亮点**：详细介绍贪心算法概念及常见类型，结合本题给出清晰思路和代码实现，还给出类似题目拓展。
    - **个人心得**：无
- **lzqy_（4星）**
    - **关键亮点**：用前缀和实现贪心，思路清晰，代码有注释，还指出坑点和注意事项。
    - **个人心得**：提到“$Ti*2$的时间里，第$i$头牛一直都不能吃花”这个坑点坑了自己好久。
- **___new2zy___（4星）**
    - **关键亮点**：详细推导贪心策略，代码规范，有输入优化。
    - **个人心得**：无

### 重点代码及核心实现思想
#### 曦行夜落
```cpp
struct cows
{
    long long d,t;
}a[maxn];

int cmp(cows x,cows y)
{
    return x.t*y.d<x.d*y.t;
}

// 核心实现思想：定义结构体存储牛的信息，通过自定义比较函数排序，再用前缀和计算总吃花量
```
#### lzqy_
```cpp
struct p
{
  int D,T;
} a[100000];
bool cmp(p a,p b)
{
  return (double)a.D/a.T*1.0>(double)b.D/b.T*1.0;
}
long long p[100000],ans;

// 核心实现思想：定义结构体存储牛的信息，按性价比排序，用前缀和数组计算总吃花量
```
#### ___new2zy___
```cpp
struct Cow
{
  int Ti,Di;
}p[100009];
bool cmp(Cow x,Cow y)
{
    double t1=1.0*x.Ti/x.Di,t2=1.0*y.Ti/y.Di;
    return t1<=t2;
}

// 核心实现思想：定义结构体存储牛的信息，通过自定义比较函数按效率排序，计算总吃花量
```

### 最优关键思路或技巧
- **贪心策略推导**：通过分析两头牛的运输顺序对总吃花量的影响，得出排序条件，将局部最优推广到全局最优。
- **前缀和优化**：使用前缀和数组记录剩余牛每分钟吃花量，减少重复计算。

### 可拓展之处
同类型题如区间调度问题、任务分配问题等，可采用类似的贪心策略，通过比较相邻元素的交换结果确定最优排序规则。

### 推荐题目
- P1208 混合牛奶：部分背包问题，按性价比排序。
- P1803 凌乱的yyy / 线段覆盖：不重叠线段选取问题，按右端点排序。
- UVA11729 突击战：任务分配问题，按执行时间从大到小排序。 

---
处理用时：19.79秒