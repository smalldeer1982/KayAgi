# 题目信息

# Magic Tricks

## 题目描述

Masha is going to participate in a talent show conducted by the university she studies at. She wants to impress the audience with lots of different magic tricks!

For one of her tricks, she uses $ n $ sponge balls, one of which is a special one. First, she arranges the balls in a row in such a way that the special ball is put on position $ k $ (positions are numbered from $ 1 $ to $ n $ from left to right). After that, she performs $ m $ swaps: during the $ i $ -th swap, she chooses the ball on position $ x_i $ and the ball on position $ y_i $ , and swaps them.

Since Masha is a magician, she fakes some of her actions to trick the audience — when she starts performing a swap, she may fake it, so it is not performed (but it looks like it is performed for the audience). There are no constraints on which swaps Masha should fake or should actually perform — for example, she may fake all of the swaps, or even not fake anything at all.

For the trick to work perfectly, the special ball should end up on a specific position — Masha has not decided yet, which position is perfect. Since faking swaps is difficult, for each position she wants to know the minimum number of swaps she has to fake so that the special ball ends up there.

Unfortunately, Masha is a magician, neither a mathematician nor a programmer. So she needs your help in calculating what she wants!

## 样例 #1

### 输入

```
4 5 1
3 4
2 1
4 1
3 1
3 1```

### 输出

```
2 0 3 1```

## 样例 #2

### 输入

```
5 7 4
3 2
3 2
4 2
3 4
4 1
3 2
5 2```

### 输出

```
2 2 0 3 1```

## 样例 #3

### 输入

```
7 15 5
5 3
4 2
6 1
2 4
1 6
3 7
5 6
4 2
6 4
2 6
6 3
6 3
7 6
2 6
7 2```

### 输出

```
-1 1 1 1 2 1 0```

# AI分析结果

### 题目翻译
# 魔术表演

## 题目描述
玛莎即将参加她所在大学举办的才艺表演。她想用许多不同的魔术来惊艳观众！

在她的一个魔术中，她使用了 $n$ 个海绵球，其中有一个是特殊的球。首先，她将这些球排成一排，使得特殊的球位于第 $k$ 个位置（位置从左到右编号为从 $1$ 到 $n$）。之后，她进行 $m$ 次交换操作：在第 $i$ 次交换中，她选择第 $x_i$ 个位置和第 $y_i$ 个位置的球，并将它们交换。

由于玛莎是一名魔术师，她会伪造一些动作来欺骗观众 —— 当她开始进行一次交换时，她可能会伪造这个操作，使其不被执行（但在观众看来是执行了的）。对于玛莎应该伪造哪些交换或者实际执行哪些交换没有限制 —— 例如，她可以伪造所有的交换，或者甚至不伪造任何交换。

为了让魔术完美进行，特殊的球最终需要位于一个特定的位置 —— 玛莎还没有决定哪个位置是完美的。由于伪造交换很困难，对于每个位置，她想知道为了使特殊的球最终位于该位置，她必须伪造的最少交换次数。

不幸的是，玛莎是一名魔术师，而不是数学家或程序员。所以她需要你的帮助来计算她想要的结果！

## 样例 #1
### 输入
```
4 5 1
3 4
2 1
4 1
3 1
3 1
```
### 输出
```
2 0 3 1
```

## 样例 #2
### 输入
```
5 7 4
3 2
3 2
4 2
3 4
4 1
3 2
5 2
```
### 输出
```
2 2 0 3 1
```

## 样例 #3
### 输入
```
7 15 5
5 3
4 2
6 1
2 4
1 6
3 7
5 6
4 2
6 4
2 6
6 3
6 3
7 6
2 6
7 2
```
### 输出
```
-1 1 1 1 2 1 0
```

### 算法分类
动态规划

### 综合分析与结论
题解采用动态规划的方法解决问题。思路是定义状态 $f_{i,j}$ 表示第 $i$ 次操作后，球在 $j$ 的最小花费，通过状态转移方程进行状态更新，并且发现第一维可以去掉来优化空间。算法要点在于状态的定义和状态转移方程的推导，解决的难点是如何通过合理的状态转移来计算出球到达每个位置的最小花费。

### 所选题解
- 4星。关键亮点：思路清晰，通过动态规划解决问题，并且对状态进行了空间优化，代码可读性较高。

### 重点代码
```cpp
#include<bits/stdc++.h>
#define INF 1e9
#define N 200005
using namespace std;
int read(){
    int x=0,f=1,ch=getchar();
    for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
int n,m,k,f[N];
int main(){
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;++i) f[i]=INF;
    f[k]=0;
    for(int i=1;i<=m;++i){
        int x=read(),y=read();
        int f1=f[x],f2=f[y];
        f[x]=min(f1+1,f2);
        f[y]=min(f2+1,f1);
    }
    for(int i=1;i<=n;++i){
        if(f[i]==INF) printf("-1 ");
        else printf("%d ",f[i]);
    }
    return 0;
}
```
**核心实现思想**：首先将所有位置的最小花费初始化为无穷大，将球初始位置的最小花费设为 $0$。然后进行 $m$ 次操作，每次操作根据状态转移方程更新两个交换位置的最小花费。最后输出每个位置的最小花费，如果无法到达则输出 $-1$。

### 扩展思路
同类型题可以是涉及状态转移和最优解计算的动态规划问题，例如背包问题、路径规划问题等。在这些问题中，通常需要定义合适的状态和状态转移方程来解决问题。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)

### 个人心得
题解作者提到自己不会 Kotlin 语言，没有关于调试经历、踩坑教训等方面的内容。 

---
处理用时：35.44秒