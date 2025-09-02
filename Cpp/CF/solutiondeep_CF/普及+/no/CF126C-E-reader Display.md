# 题目信息

# E-reader Display

## 题目描述

给定一个 $n \times n$ 的正方形，初始时每个点都是 `0`。当接收到 $(x,y)$ 的命令时，$(x,x) \rarr (x,y)$ 和 $(x,y) \rarr (y,y)$ 段（包括两端点）中的每个点均发生反转（`1` 变 `0`，`0` 变 `1`）。 计算使输入的表每个点都变为 0 所需的最少命令数 $s$，并输出。

## 说明/提示

$1 \leq n \leq 2 \times 10^3$，输入的数组只由 ```0``` 或 ```1``` 组成。

## 样例 #1

### 输入

```
5
01110
10010
10001
10011
11110
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# 电子阅读器显示屏

## 题目描述
给定一个 $n \times n$ 的正方形，初始时每个点都是 `0`。当接收到 $(x,y)$ 的命令时，$(x,x) \rarr (x,y)$ 和 $(x,y) \rarr (y,y)$ 段（包括两端点）中的每个点均发生反转（`1` 变 `0`，`0` 变 `1`）。 计算使输入的表每个点都变为 0 所需的最少命令数 $s$，并输出。

## 说明/提示
$1 \leq n \leq 2 \times 10^3$，输入的数组只由 ```0``` 或 ```1``` 组成。

## 样例 #1
### 输入
```
5
01110
10010
10001
10011
11110
```
### 输出
```
4
```
### 算法分类
贪心
### 综合分析与结论
该题解思路清晰，通过将矩阵按对角线、对角线左侧、对角线右侧分开处理，找到一种无后效性的遍历方式来解决问题。算法要点在于根据题目给定的操作特点，设计特定的遍历顺序，利用树状数组维护区间异或和来判断当前点状态。难点在于发现这种无后效性的遍历方式以及如何利用树状数组高效维护状态。
### 所选的题解
 - **星级**：4星
 - **关键亮点**：提出将矩阵按对角线相关区域分开处理，设计独特遍历顺序，利用树状数组维护状态。
 - **个人心得**：作者提到自己用了较为复杂的 $2n^2$ 个树状数组维护区间异或和，可优化。
### 重点代码核心实现思想
通过树状数组来维护区间异或和，以判断每个点是否需要进行操作。在遍历矩阵不同区域时，根据树状数组查询结果决定是否进行操作并更新树状数组，统计操作次数。
### 核心代码片段
```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=2010;
il int read(){
    int x=0;
    char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    return c-'0';
}
int n,ans;
int Tree1[maxn][maxn];
int Tree2[maxn][maxn];
il int Sum1(int t,int k,int sum=0){for(;k;k-=k&-k)sum^=Tree1[t][k];return sum;}
il int Sum2(int t,int k,int sum=0){for(;k;k-=k&-k)sum^=Tree2[t][k];return sum;}
il void Add1(int t,int k,int x){for(;k<=n+1;k+=k&-k) Tree1[t][k]^=x;}
il void Add2(int t,int k,int x){for(;k<=n+1;k+=k&-k) Tree2[t][k]^=x;}
il void Addh(int t,int l,int r){Add1(t,r+1,1),Add1(t,l,1);}
il void Addl(int t,int l,int r){Add2(t,r+1,1),Add2(t,l,1);}
int Query(int x,int y){return Sum1(x,y)^Sum2(y,x);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(read()) Addh(i,j,j);
    for(int i=1;i<=n;i++)
        for(int j=n;j>i;j--)
            if(Query(i,j))
                Addh(i,i,j),Addl(j,i,j),ans++;
    for(int i=n;i;i--)
        for(int j=1;j<i;j++)
            if(Query(i,j))
                Addh(i,j,i),Addl(j,j,i),ans++;
    for(int i=1;i<=n;i++)
        if(Query(i,i)) ans++;
    printf("%d\n",ans);
    return 0;
}
```
### 最优关键思路或技巧
利用对角线将矩阵分区，设计无后效性的遍历顺序，结合树状数组维护状态，减少重复计算，提高效率。
### 可拓展之处
同类型题可考虑更多复杂的矩阵翻转规则及目标状态，类似算法套路是寻找无后效性的遍历方式，利用合适的数据结构维护状态。
### 洛谷相似题目推荐
 - P1094 [NOIP2007 普及组] 纪念品分组
 - P1223 排队接水
 - P1937 [USACO10MAR]Barn Allocation G

---
处理用时：47.58秒