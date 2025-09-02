# [JOI 2022 Final] 铁路旅行 2 / Railway Trip 2

## 题目描述

IOI 铁路公司在一条铁轨上运营线路。铁轨为一条直线，该铁轨上有 $N$ 个车站，编号为 $1 \sim N$。车站 $i$ 与车站 $i + 1$ 之间由一条铁轨直接连接。

IOI 铁路公司正在运营 $M$ 条线路，编号为 $1 \sim M$。线路 $j$ 的起点为 $A_j$，终点为 $B_j$，列车在每一站均会停靠，即如果 $A_j < B_j$，一列 $j$ 号线的列车会按顺序在车站 $A_j, A_j + 1, \ldots, B_j$ 停靠。如果 $A_j > B_j$，一列 $j$ 号线的列车会按顺序在车站 $A_j, A_j - 1, \ldots, B_j$ 停靠。

JOI 君是一个旅行者。他有 $Q$ 个旅行计划。在第 $k$ 个旅行计划中他计划从车站 $S_k$ 通过乘坐列车前往车站 $T_k$。

然而，JOI 君因长途跋涉而疲惫不堪。他希望他乘坐的列车均有空座以便休息。因此 JOI 君决定，只有当某条线路的起点站是第 $K$ 个或更早的车站时，他才会在该站乘坐该条线路的列车。换句话说，对于线路 $j$，如果 $A_j < B_j$，那么他只会在车站 $A_j, A_j + 1, \ldots, \min \{ A_j + K - 1, B_j - 1 \}$ 乘上线路 $j$ 的列车。如果 $A_j > B_j$，那么他只会在车站 $A_j, A_j - 1, \ldots, \max \{ A_j - K + 1, B_j + 1 \}$ 乘上线路 $j$ 的列车。

在这些条件下，JOI 君希望尽量减少乘坐火车的次数。

给出 IOI 铁路公司的线路信息和 JOI 君的计划，写一个程序计算对于 JOI 君的每一个计划，他所需的最小乘车次数。

## 说明/提示

**【样例解释 \#1】**

对于第一个计划，JOI 君要从车站 $5$ 前往车站 $3$。具体地，此计划可以通过如下方式实现：JOI 君在车站 $5$ 乘上 $1$ 号线的列车，并在车站 $3$ 下车。JOI 君总共乘坐了一次列车。由于不可能花费比 $1$ 更少的乘车次数实现该计划，在第一行输出 $1$。

对于第二个计划，JOI 君要从车站 $3$ 前往车站 $2$。具体地，此计划可以通过如下方式实现：JOI 君在车站 $3$ 乘上 $2$ 号线的列车，并在车站 $4$ 下车；然后在车站 $4$ 乘上 $1$ 号线的列车，并在车站 $2$ 下车。JOI 君总共乘坐了两次列车。由于不可能花费比 $2$ 更少的乘车次数实现该计划，在第二行输出 $2$。

对于第一个计划，JOI 君要从车站 $2$ 前往车站 $1$。由于无论如何无法实现该计划，在第三行输出 `-1`。

这个样例满足子任务 $1, 2, 6$ 的限制。

**【样例解释 \#2】**

这个样例满足子任务 $1, 2, 6$ 的限制。

**【样例解释 \#3】**

这个样例满足子任务 $1, 2, 4, 6$ 的限制。

**【样例解释 \#4】**

这个样例满足子任务 $1, 2, 5, 6$ 的限制。

----

**【数据范围】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$2 \le N \le {10}^5$，$1 \le K \le N - 1$，$1 \le M \le 2 \times {10}^5$，$1 \le Q \le 5 \times {10}^4$，$1 \le A_j, B_j, S_k, T_k \le N$，$A_j \ne B_j$，$S_k \ne T_k$，$(A_j, B_j) \ne (A_k, B_k)$（$j \ne k$），$(S_k, T_k) \ne (S_l, T_l)$（$k \ne l$）。

- 子任务 $1$（$8$ 分）：$N, M, Q \le 300$。
- 子任务 $2$（$8$ 分）：$N, M, Q \le 2000$。
- 子任务 $3$（$11$ 分）：$Q = 1$。
- 子任务 $4$（$25$ 分）：$K = N - 1$。
- 子任务 $5$（$35$ 分）：$A_j < B_j$，$S_k < T_k$。
- 子任务 $6$（$13$ 分）：无特殊限制。

----

**译自 [JOI 2022 Final](https://www.ioi-jp.org/joi/2021/2022-ho/index.html) T4「[鉄道旅行 2 ](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t4.pdf) / [Railway Trip 2](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t4-en.pdf)」**

## 样例 #1

### 输入

```
5 2
2
5 1
3 5
3
5 3
3 2
2 1
```

### 输出

```
1
2
-1
```

## 样例 #2

### 输入

```
6 3
2
1 6
5 1
4
5 1
6 3
3 6
2 1
```

### 输出

```
1
-1
1
2
```

## 样例 #3

### 输入

```
6 5
4
3 1
2 4
5 3
4 6
5
1 5
3 2
2 6
6 3
5 4
```

### 输出

```
-1
1
2
-1
1
```

## 样例 #4

### 输入

```
12 1
5
1 7
10 12
3 5
8 10
5 9
7
2 11
5 8
3 12
4 6
1 9
9 10
1 4
```

### 输出

```
-1
1
4
-1
2
-1
1
```

# 题解

## 作者：jjsnam (赞：18)

## 写在前面

最近在学倍增，被紫题虐哭后又来尝试这个蓝题，没想到实现起来也有一定的难度。
看不懂大佬们的题解和代码，所以打算写一个比较易懂的题解。   

其实思路与第一篇题解类似，但是它讲的太笼统了。就像 "经" 需要 "传" 来解释一样，所以我打算将这种思路写的更详细一些，让有一定倍增基础的同志们可以看懂。

#### 前置知识 
- 线段树
- 单调队列
- 倍增

#### 题目大意（戳这里[查看原题](https://www.luogu.com.cn/problem/P8163)）
- 给定 $n$ 个点，$m$ 条路线。
- 给定一个整数 $K$，表示乘车点离**始发点**的**最远距离**。
- 对于每条路线，给定 $\langle A_{i},B_{i} \rangle$ 表示**路线的**起点和终点。  
**注意：** $A_{i}$，$B_{i}$ 相对大小关系**不确定**，可分别表示**正向**和**反向**。
- 接下来有 $Q$ 次询问。
- 对于每次询问，给定 $\langle S_{i},T_{i} \rangle$ 表示**询问的**起点和终点。求是否能够通过换乘从 $S_{i}$ 到达 $T_{i}$，如果可以输出最少换乘次数。
- 无解输出 $-1$。


## 正文

就我目前的经验来看，凡是需要多次无序询问或者重复多次处理一张图时，大概率是需要用到倍增的。   

简单说一下**原因**：当我们要多次处理（或询问）一张图时（假设 $n$ 个点），那么如果一次次遍历，复杂度很可能是 $O(n^2)$ 或更高，在动不动就  $n >10^5$  的数据下肯定是不行的，而倍增可以将每次遍历降到 $\log{n}$ 级别，显然是一种很有效的优化方法。

然后我们以倍增作为思考切入点，再回到这题。我们可以先把数据(样例 3)~~手~~出来观察一下：
![Sample #3](https://cdn.luogu.com.cn/upload/image_hosting/e5vopmt4.png)

以 $\text{start}=2$，$\text{end}=6$ 为例， 我们要从 $2$ 号点走到 $6$ 号点，则需要在 $2$ 号点坐二号线于 $4$ 号点下车，再从 $4$ 号点坐四号线于 $6$ 号点下车。需要坐 $2$ 条线路。

一看就非常想上倍增。满足多次无序询问，而且这个图很大，但是感觉又不老好实现的，我们继续思考。

接下来从倍增两个基本步骤入手：**预处理、询问**。

#### 预处理

考虑**倍增**。终点可以在起点的左边，也可以在起点的右边。所以左右都要考虑到。我们用 $le(i,k)$、$ri(i,k)$ 分别代表以第 $i$ 个点为起点，乘坐 $2^k$ 条路线所能到达的最远左端点、右端点。 

可以证明：此时第 $i$ 点乘坐 $2^k$ 条路线能到达的所有点均属于区间 $[le_{i,k} , ri_{i,k}]$，且该区间内没有点不能被 $i$ 到达。（可以这么想：既然能到达最远，则一定有一条路线连接起点和最远点，那么中间的这些点只要提前下车就行了。上车有限制，但是下车没有）。

接下来想一下如何递推倍增式。对于 $2^k$ 次换乘，一定保证 $le(i,k-1) ≥ le(i,k)$ 且 $ri(i,k-1) ≤ ri(i,k)$ 才有意义。通过我们刚才的推论，在 $[le_{i,k-1} , ri_{i,k-1}]$ 中的所有点都可以被  $i$ 点到达，则我们可以在 $i$ 乘坐一条路线时选择到达其中的一点 $j$，通过 $j$ 的 $le(j,k-1)$ 和 $ri(j,k-1)$ 来扩展点 $i$ 的情况。式子就很容易得出了：

$le(i,k) = \min(le(i,k),le(j,k-1))$；

$ri(i,k) = \max(ri(i,k),ri(j,k-1))$；

其中 $j \in [ le_{i,k-1} , ri_{i,k-1} ]$。

考虑一般情况: 显然递推要使用一个区间内的最值，这就成为了一个 RMQ 问题，那么一个个枚举显然是很耗时的。 我们可以用**线段树**来优化这个过程。  （之后，我们可以想想是用一颗线段树滚动，还是要建很多颗线段树 ? ）


------------


现在还有一个很~~棘手~~的问题，就是初始的 $le(i,0)$，$ri(i,0)$ 如何得出？ 我是没想出如何用线段树， 但我们可以使用一个稍加修改的**单调队列**求出。（正是别的题解对这块一笔带过才让我下决心写这篇题解）

现在考虑**单调队列**，首先，队列要装**路线**（这样处理出终点最远的路线，计算答案时找到这个终点即可），所以大小应该是 $m$ 个。其次，需要改动的地方就是我们要在枚举路线的同时更新我们的点。 这个想想应该也能明白，我们枚举每个点，同时以这个点为参照逐渐枚举路线。

以求 $ri(i,0)$ 为例，即在队列里的路线满足起点在该点前，终点在该点后，队列中路线的终点要最右，所以这些路线按照其终点的大小在队列中满足单调递减。 

**注意**：我们如果要枚举到满足这个点条件的所有路线，显然要将这些路线**按起点排序**。  


------------


还有两个**小细节**：

1. $ri(i,k)$ 是向右最远的点，所以只有正向路线可能有影响；反之 $le(i,k)$ 则只受逆向路线影响。要**分开枚举**。  

2. 单调队列中，如何判断一条路线是否**合法**？以求 $ri(i,0)$ 为例。对于一个路线的起点 $S$，合法满足 $i≤S+K-1$， 整理得 $S≥i-K+1$，则对于任意 $S≤i-K$ 的路线都不能满足 $i$ 是起点，是**不合法**的，应该**删去**。


------------


则预处理的总复杂度 $O(n\log^2{n}+m)$。

分别是一般情况的**线段树$+$倍增**和起始的**单调队列**。


------------



#### 询问

然后这题的难点就基本解决了。我们再来考虑一下询问如何处理。

对于一对询问  $\langle S_{i} , E_{i}\rangle$，我们尝试从 $S_{i}$ 不断向左右扩展，直到能到达的区间覆盖住了 $E_{i}$。 

同时注意一下如何保证**正确性**： 

可以联想一下倍增求 LCA。首先我们要倒序枚举 $k$ 保证大的先处理。 同时，LCA 在处理的时候不会让两个点跳到一起，只会跳到最近公共祖先的子节点，从而保证不会出现跳到 LCA 上面导致祖先重合的情况。 类比这个方法， 我们也可以使最后的区间 **将要但不包括 $E_{i}$**，从而避免乘坐了过多的线路。

最后我们再来考虑一下**最终的答案：**

对于一次询问，我们为了保证正确性，确保每次更新换乘点都满足**不达到，但尽可能将要到达**终点。那么当我们完成一次完整的循环处理（即从换乘 $2^k$ 次一直到换乘 $2^0$ 次后到达的点），这时记录的答案一定**不能够**使我们到达终点。可以证明，如果这个询问**有解**，**当且仅当终点 $E_{i}$ 位于最后一次到达的换乘点 $j$ 换乘一次可到达的点的范围内（$E_{i}\in [le_{j,0},ri_{j,0}]$）**。若不满足这个条件则**无解**，输出 $-1$。

如果读者不明白为什么是这个条件，我们仍然可以联想倍增求 LCA。这里我通过**反证法**给出一个**不严谨**的简单证明：

假如最后的终点 $E_{i}$ 不满足上面的条件且保证有解，则一定满足 $E_{i}\in [le_{j,k},ri_{j,k}]$，其中 $k \in [1,\lfloor\log{n}\rfloor]$。然而，我们在处理询问的循环中是从大到小枚举 $k$，则一定可以找到一个枚举的 $k$，将最后的换乘点 $j$ 更新，且满足**不达到，但将要到达**终点这个条件。前后**矛盾**。

------------


**注意：** 按照这种方法扩展也**不能只考虑起点**，而是要考虑每次换乘起点所能到达的所有点，取最优。然后又回到了令人~~欣喜~~的 RMQ 环节。我们直接枚举倍增的数组显然也不是最优的，这就突显出我们线段树的好处了，自然我们可以用处理倍增的线段树来在 $\log{n}$ 下得出当前的最优。也就回答了上面的思考，我们要建 $\lfloor\log{n}\rfloor+1$ 颗线段树，不用滚动优化。


------------


询问的复杂度 $O(q\log^2{n})$。


------------

最后的**总复杂度** $O((n+q)\log^2{n}+m)$。

## 代码

##### 对一些变量名的解释（~~我觉得是比较正常的~~）

- $le(i,k)$ 表示向左最远到达点的倍增数组

- $ri(i,k)$ 表示向右最远到达点的倍增数组

- $up(i)$，$cnt\_up$ 用于记录正向路径（取 $\text{up}$ 上行意）

- $down(i)$，$cnt\_down$ 用于记录逆向路径（取 $\text{down}$ 下行意） 

因为要建**多颗**线段树，所以用结构体封装，开 $\text{root}=17$ 个线段树。

------------

```cpp
/* code by jjsnam 2022.4.29 */
/* Using Segment Tree */
#include <iostream>
#include <algorithm>
#include <cstring>

#define ls (id<<1)
#define rs (id<<1|1)
#define mid ((l+r)>>1)
#define u first
#define v second

using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+5;
const int maxm=2e5+5;

int le[maxn][17],ri[maxn][17];
pii up[maxm],down[maxm];
int cnt_up,cnt_down;
int n,m,K,Q;
struct Segment_Tree{
    struct Node{
        int left,right;
    }tr[maxn<<2];
    
    void pushup(int id){
        tr[id].left=min(tr[ls].left,tr[rs].left);
        tr[id].right=max(tr[ls].right,tr[rs].right);
    }

    void build(int id,int l,int r,int k){
        if (l==r){
            tr[id].left=le[l][k];
            tr[id].right=ri[r][k];
            return;
        }
        build(ls,l,mid,k);
        build(rs,mid+1,r,k);
        pushup(id);
    }

    int query_left(int id,int l,int r,int a,int b){
        if (a<=l&&r<=b){
            return tr[id].left;
        }
        int res=1e9;
        if (a<=mid) res=min(res,query_left(ls,l,mid,a,b));
        if (b>mid) res=min(res,query_left(rs,mid+1,r,a,b));
        return res;
    }

    int query_right(int id,int l,int r,int a,int b){
        if (a<=l&&r<=b){
            return tr[id].right;
        }
        int res=-1e9;
        if (a<=mid) res=max(res,query_right(ls,l,mid,a,b));
        if (b>mid) res=max(res,query_right(rs,mid+1,r,a,b));
        return res;
    }
}root[17];

void Get_start(){
    for (int i=1;i<=n;i++) le[i][0]=ri[i][0]=i;
    sort(up+1,up+cnt_up+1);
    sort(down+1,down+cnt_down+1,greater<pii>());
    /* 单调队列 O(m) */
    int q[maxm],hh=1,tt=0;

    /* 处理右 */
    for (int i=1,j=1;i<=n;i++){
        while (j<=cnt_up&&up[j].u<=i){
            int r=up[j].v;
            while (hh<=tt&&up[q[tt]].v<=r) tt--;
            q[++tt]=j;
            j++;
        }
        while (hh<=tt&&up[q[hh]].u<=i-K) hh++;
        if (hh<=tt) ri[i][0]=max(ri[i][0],up[q[hh]].v);
    }

    /* init */
    hh=1,tt=0;

    /* 处理左 */
    for (int i=n,j=1;i>0;i--){
        while (j<=cnt_down&&down[j].u>=i){
            int l=down[j].v;
            while (hh<=tt&&down[q[tt]].v>=l) tt--;
            q[++tt]=j;
            j++;
        }
        while (hh<=tt&&down[q[hh]].u>=i+K) hh++;
        if (hh<=tt) le[i][0]=min(le[i][0],down[q[hh]].v);
    }
}

void init(){
    Get_start();
    root[0].build(1,1,n,0);
    for (int k=1;k<=16;k++){
        for (int i=1;i<=n;i++){
            le[i][k]=root[k-1].query_left(1,1,n,le[i][k-1],ri[i][k-1]);
            ri[i][k]=root[k-1].query_right(1,1,n,le[i][k-1],ri[i][k-1]);
        }
        root[k].build(1,1,n,k);
    }
}

int query(int S,int E){
    int res=0;
    int l=S,r=S;
    for (int k=16;k>=0;k--){
        int L=root[k].query_left(1,1,n,l,r);
        int R=root[k].query_right(1,1,n,l,r);
        if (L<=E&&E<=R) continue;
        l=L,r=R;
        res+=(1<<k);
    }
    int L=root[0].query_left(1,1,n,l,r);
    int R=root[0].query_right(1,1,n,l,r);
    if (L<=E&&E<=R) return res+1;
    else return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin >> n >> K >> m;
    for (int i=1,a,b;i<=m;i++){
        cin >> a >> b;
        if (a<b) up[++cnt_up]=make_pair(a,b);
        else down[++cnt_down]=make_pair(a,b);
    }
    init();
    cin >> Q;
    int s,e;
    while (Q--){
        cin >> s >> e;
        cout << query(s,e) << endl;
    }
    return 0;
}
```


------------


## 总结
此题的这种做法其实是 **RMQ** 问题与**倍增**的结合。

它与其他倍增题做法有一些**不同之处**：

- 最后询问不是直接使用倍增数组，而是用更新倍增数组的线段树更新答案。           
可以这么理解：每一层倍增由**上一层**的线段树区间最值求得，而**这一层**的线段树初始值则是**更新后**的倍增数组。所以广义上说，我们存的**线段树也算一个倍增**。

- 本题更新倍增数组的方法也不是单一的递推，而是通过线段树优化后的区间最值递推。


------------

然后这道题就结束了！好耶（

应该还是有更优的 RMQ 做法的，但是我太弱了想不出来（

第一次写题解，可能我的表述也比较菜，如果有问题欢迎指出！

---

## 作者：Awlgot (赞：12)

## 一个复杂度较小的做法


校模拟赛看到这题已经是最后 $20$min 了 QwQ ，所以是赛后补题。

首先看到这种跳来跳去的题，试着考虑倍增，发现可行。

#### 思考实现：

	
首先发现，能跳到的地方一定是一个区间，然后预处理一步跳到最远的点是哪里，记数组为 $left_{i},right_{i}$。

于是发现一种可能：就是存在一个点在所能跳到最远范围内，但跳此点再进行跳跃更优。那么就要分类讨论，所以预处理储存跳两步所扩展最大范围的数组。

一共四种情况分别为：先左再左，先左再右，先右再左，先右再右。可以发现所有情况都可转移得到。

现在时间复杂度就比一些线段树做法少了一只 $\log$。

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
int n,k,m,q,lim;
int stl[N][25],str[N][25],fl[N][25],fr[N][25],lf[N],rt[N];
int lmn[N],lmx[N],rmn[N],rmx[N];
int Min(int a,int b){return lf[a]<lf[b]?a:b;}
int Max(int a,int b){return rt[a]>rt[b]?a:b;}
int queryl(int l,int r){
	int lg=std::__lg(r-l+1);
	return min(stl[l][lg],stl[r-(1<<lg)+1][lg]);
}
int queryr(int l,int r){
	int lg=std::__lg(r-l+1);
	return max(str[l][lg],str[r-(1<<lg)+1][lg]);
}
int queryL(int l,int r){
	int lg=std::__lg(r-l+1);
	return Min(stl[l][lg],stl[r-(1<<lg)+1][lg]);
}
int queryR(int l,int r){
	int lg=std::__lg(r-l+1);
	return Max(str[l][lg],str[r-(1<<lg)+1][lg]);
}
void query(int s,int t){
	int l=s,r=s,res=1;
	if(lf[s]>t||rt[s]<t){
		for(int j=lim;j>=0;j--){
			int L=Min(Min(fl[lmn[l]][j],fl[rmn[r]][j]),Min(fl[lmx[l]][j],fl[rmx[r]][j]));
			int R=Max(Max(fr[lmn[l]][j],fr[rmn[r]][j]),Max(fr[lmx[l]][j],fr[rmx[r]][j]));
			if(lf[L]>t||rt[R]<t) l=L,r=R,res+=(1<<j);
		}
		res++;
	}
	cout<<(res>n?-1:res)<<"\n";
}
signed main(){
	std::ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k>>m;
	memset(stl,0x3f,sizeof(stl));
	for(int i=1,a,b;i<=m;i++){
		cin>>a>>b;
		if(a>b) stl[a][0]=min(stl[a][0],b);
		else str[a][0]=max(str[a][0],b);
	}
	for(int j=1;(1<<j)<=n;j++)
	for(int i=1;i+(1<<j)-1<=n;i++){
		stl[i][j]=min(stl[i][j-1],stl[i+(1<<(j-1))][j-1]);
		str[i][j]=max(str[i][j-1],str[i+(1<<(j-1))][j-1]);
	}
	for(int i=1;i<=n;i++){
		lf[i]=min(i,queryl(i,min(i+k-1,n)));
		rt[i]=max(i,queryr(max(i-k+1,1),i));
		stl[i][0]=str[i][0]=i;
	}
	for(int j=1;(1<<j)<=n;j++)
	for(int i=1;i+(1<<j)-1<=n;i++){
		stl[i][j]=Min(stl[i][j-1],stl[i+(1<<(j-1))][j-1]);
		str[i][j]=Max(str[i][j-1],str[i+(1<<(j-1))][j-1]);
	}
	for(int i=1;i<=n;i++){
		fl[i][0]=fr[i][0]=i;
		lmn[i]=queryL(lf[i],i);
		lmx[i]=queryR(lf[i],i);
		rmn[i]=queryL(i,rt[i]);
		rmx[i]=queryR(i,rt[i]);
	}
	for(int j=1;(1<<j)<=n;j++,lim++){
		for(int i=1;i<=n;i++){
			int l=fl[i][j-1],r=fr[i][j-1];
			fl[i][j]=Min(Min(fl[lmn[l]][j-1],fl[rmn[r]][j-1]),Min(fl[lmx[l]][j-1],fl[rmx[r]][j-1]));
			fr[i][j]=Max(Max(fr[lmn[l]][j-1],fr[rmn[r]][j-1]),Max(fr[lmx[l]][j-1],fr[rmx[r]][j-1]));
			// cout<<fl[i][j]<<" "<<fr[i][j]<<"\n";
		}
	}
	cin>>q;
	for(int i=1,s,t;i<=q;i++){
		cin>>s>>t;
		query(s,t);
	}
	return 0;
}
//ggghurjv
```


---

## 作者：封禁用户 (赞：4)

### 写在前面：

前置知识：[ST 表](https://oi-wiki.org/ds/sparse-table/)。

这题的弱化版：[Minimal Segment Cover](https://www.luogu.com.cn/problem/CF1175E) ~~这题是蓝题，但弱化版竟然是个紫题~~。

### 暴力

我们可以求出每个点的 $l_i$ 和 $r_i$，询问时暴力地扩展区间。

时间复杂度：$O(n \times (m+q))$。

### 分析

这题时间的瓶颈主要在于一步一步地扩展区间太慢，我们可以使用倍增进行优化。

$l_{j,i}$ 表示 $j$ 这个点跳 $2^i$ 步能到达的最左端。

$r_{j,i}$ 表示 $j$ 这个点跳 $2^i$ 步能到达的最右端。

可以发现，这题的左右端是可以重复贡献的，空间也够，所以我们可以采用 $\log{n}$ 个 ST 表进行维护左右断点跳 $2^i$ 步的最左端和最右端。

```cpp
struct node
{
	int mx[N][20],mn[N][20];
	inline void update(int x)
	{
		F(i,1,n) mx[i][0] = r[i][x],mn[i][0] = l[i][x];
		F(i,1,w)
			F(j,1,n-(1<<i)+1)
				mx[j][i] = max(mx[j][i-1],mx[j+(1<<i-1)][i-1]),mn[j][i] = min(mn[j][i-1],mn[j+(1<<i-1)][i-1]);
	}
	inline int query(int x,int y,bool o)// 1 最大值 0 最小值 
	{
		int t = (int)log2(y-x+1);
		if(o) return max(mx[x][t],mx[y-(1<<t)+1][t]);
		else return min(mn[x][t],mn[y-(1<<t)+1][t]);		
	} 
}st[20];
```
对于预处理部分，也要想出一个更高效的方法。

我们利用一个类似于差分的思想，若对于区间 $[x,y]$ 的端点为 $z$，可以进行这样的操作：

```cpp
inline void update(int l,int r,int x)
{
	u[l].push_back(x);
	d[r+1].push_back(x);	
}
```

统计的时候从左到右枚举，通过 multiset 记录最大值和最小值。

```cpp
F(i,1,n)
{
	for(auto j:u[i]) p.insert(j);	
	for(auto j:d[i])
	{
		it = p.lower_bound(j); 
		p.erase(it);	
		//注意如果直接写 p.erase(j) 会把所有的 j 的删掉 
	}
	l[i][0] = r[i][0] = i;
	if(!p.size()) continue;
	it = p.begin();
	l[i][0] = min(l[i][0],*it);
	it = p.end();
	--it;
	r[i][0] = max(r[i][0],*it);
}
```
时间复杂度：$O((n+q)\times \log_{}^2{n})$。

### 两点注意

-  **应当特判起点和终点相同的情况**。

```cpp
if(x == y)
{
	putchar('0');
	putchar('\n');
	continue;
}
 ```
- 在进行 erase 操作时，只应当 erase 其中一个

```cpp
for(auto j:d[i])
{
	it = p.lower_bound(j); 
	p.erase(it);	
	//注意如果直接写 p.erase(j) 会把所有的 j 的删掉 
}
```
### 完整版代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10^48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define N 100010
int l[N][20],r[N][20],n,m,k,w,q; 
vector<int> u[N],d[N];
inline void update(int l,int r,int x)
{
	u[l].push_back(x);
	d[r+1].push_back(x);	
}
multiset<int> p;
multiset<int>::iterator it;
struct node
{
	int mx[N][20],mn[N][20];
	inline void update(int x)
	{
		F(i,1,n) mx[i][0] = r[i][x],mn[i][0] = l[i][x];
		F(i,1,w)
			F(j,1,n-(1<<i)+1)
				mx[j][i] = max(mx[j][i-1],mx[j+(1<<i-1)][i-1]),mn[j][i] = min(mn[j][i-1],mn[j+(1<<i-1)][i-1]);
	}
	inline int query(int x,int y,bool o)// 1 最大值 0 最小值 
	{
		int t = (int)log2(y-x+1);
		if(o) return max(mx[x][t],mx[y-(1<<t)+1][t]);
		else return min(mn[x][t],mn[y-(1<<t)+1][t]);		
	} 
}st[20];
int main()
{
//	freopen("tour.in","r",stdin);
//	freopen("tour.out","w",stdout);
	read(n),read(k),read(m);
	w = (int)log2(n) + 1;
	while(m--)
	{
		int x,y;
		read(x),read(y);
		if(x < y) update(x,min(y,x+k-1),y);
		else update(max(y,x-k+1),x,y);
	}
	F(i,1,n)
	{
		for(auto j:u[i]) p.insert(j);	
		for(auto j:d[i])
		{
			it = p.lower_bound(j); 
			p.erase(it);	
			//注意如果直接写 p.erase(j) 会把所有的 j 的删掉 
		}
		l[i][0] = r[i][0] = i;
		if(!p.size()) continue;
		it = p.begin();
		l[i][0] = min(l[i][0],*it);
		it = p.end();
		--it;
		r[i][0] = max(r[i][0],*it);
	}
	st[0].update(0); 
	F(i,1,w)
	{
		F(j,1,n) 
		{
			l[j][i] = st[i-1].query(l[j][i-1],r[j][i-1],0);
			r[j][i] = st[i-1].query(l[j][i-1],r[j][i-1],1);
		}
		st[i].update(i);
	}
	read(q);
	while(q--)
	{
		int x,y;
		read(x),read(y);
		if(x == y)
		{
			putchar('0');
			putchar('\n');
			continue;
		}//必须特判 
		int nl = x,nr = x,ans = 0;
		D(i,w,0)
		{
			int tl = st[i].query(nl,nr,0),tr = st[i].query(nl,nr,1);
			if(tl > y||tr < y) 
			{
				ans += 1<<i;
				nl = tl;
				nr = tr;	
			}
		}
		int tl = st[0].query(nl,nr,0),tr = st[0].query(nl,nr,1);
		if(tl > y||tr < y) write(-1);
		else write(ans+1);
		putchar('\n');  
	}
	return 0;
}
```


---

## 作者：RyexAwl (赞：3)

对于 $1\le N,M,Q\le 2000$ 的部分分可以考虑维护出从站点 $i$ 通过 $\le j$ 条路线可以到达的站点集合，可以使用归纳法证明能够到达的站点集合一定是一段区间 $[l,r]$ 满足 $l\le i\le r$。

而对于 $K=N-1$ 与 $A_j<B_j,S_k<T_k$ 的部分分可以使用倍增优化。

因此考虑使用倍增优化 $1\le N,M,Q\le 2000$ 的部分分做法，令 $[left[i][j],right[i][j]]$ 表示从点 $j$ 通过 $\le 2^i$ 条铁路可以到达的站点集合。

有转移方程：

$$
left[i][j]=\min_{k\in [left[i-1][j],right[i-1][j]]}(left[i-1][k])
$$

$$
right[i][j]=\max_{k\in [left[i-1][j],right[i-1][j]]}(right[i-1][k])
$$

使用线段树优化，预处理的复杂度为 $O(N\log ^2 N+M)$ 。

对于每次询问倍增查询即可，复杂度 $O(Q\log^2 N)$。

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

const int N = 1e5 + 50;

int left[20][N],right[20][N];

int n,k,m,q;

struct SegTree {
    struct node {
        int l,r,left,right;
    } t[N<<2];
    void pushup(int u) {
        t[u].left = std::min(t[u<<1].left,t[u<<1|1].left);
        t[u].right = std::max(t[u<<1].right,t[u<<1|1].right);
    }
    void build(int u,int l,int r) {
        t[u].l =  l; t[u].r = r;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(u<<1,l,mid); build(u<<1|1,mid+1,r);
    }
    void modify(int u,int x,int left,int right) {
        if (t[u].l == t[u].r) {
            t[u].left = left,t[u].right = right;
            return;
        }
        int mid = (t[u].l + t[u].r) >> 1;
        if (x <= mid) modify(u<<1,x,left,right);
        else modify(u<<1|1,x,left,right);
        pushup(u);
    }
    int queryLeft(int u,int l,int r) {
        if (l <= t[u].l && t[u].r <= r) return t[u].left;
        int mid = (t[u].l + t[u].r) >> 1,res = 500000;
        if (l <= mid) res = queryLeft(u<<1,l,r);
        if (r > mid) res = std::min(res,queryLeft(u<<1|1,l,r));
        return res;
    }
    int queryRight(int u,int l,int r) {
        if (l <= t[u].l && t[u].r <= r) return t[u].right;
        int mid = (t[u].l + t[u].r) >> 1,res = 0;
        if (l <= mid) res = queryRight(u<<1,l,r);
        if (r > mid) res = std::max(res,queryRight(u<<1|1,l,r));
        return res;
    } 
} seg[20];

std::vector<std::pair<int,int>> segs[2];

int ask(int begin,int end) {
    int l = begin,r = begin,res = 0;
    per(i,19,0) {
        int L = seg[i].queryLeft(1,l,r),R = seg[i].queryRight(1,l,r);
        if (L <= end && end <= R) continue;
        l = L,r = R,res += (1 << i);
    } 
    int L = seg[0].queryLeft(1,l,r),R = seg[0].queryRight(1,l,r);
    if (L <= end && end <= R) return res + 1;
    else return -1;
    
}

void init(){
    seg[0].build(1,1,n);
    std::deque<int> q;
    std::sort(segs[0].begin(),segs[0].end());
    rep(i,1,n) left[0][i] = right[0][i] = i;
    for (int i = 1,j = -1; i <= n; i++) {
        while (j + 1 < segs[0].size() && segs[0][j+1].fi <= i) {
           ++ j; int r = segs[0][j].se;
           while (q.size() && segs[0][q.back()].se <= r) q.pop_back();
           q.push_back(j);
        }
        while (q.size() && segs[0][q.front()].fi <= i - k) q.pop_front();
        if (q.size()) right[0][i] = std::max(right[0][i],segs[0][q.front()].se);
    } q.clear();
    std::sort(segs[1].begin(),segs[1].end()); std::reverse(segs[1].begin(),segs[1].end());
    for (auto &Seg : segs[1]) std::swap(Seg.fi,Seg.se);
   
    for (int i = n,j = -1; i >= 1; i--) {
        while (j + 1 < segs[1].size() && segs[1][j+1].se >= i) {
            ++ j; int l = segs[1][j].fi;
            while (q.size() && segs[1][q.back()].fi >= l) q.pop_back();
            q.push_back(j);
        }
        while (q.size() && segs[1][q.front()].se >= i + k) q.pop_front();
        if (q.size()) left[0][i] = std::min(left[0][i],segs[1][q.front()].fi);
    }
    rep(i,1,n) seg[0].modify(1,i,left[0][i],right[0][i]);
    rep(i,1,19) {
        rep(j,1,n) {
            left[i][j] = std::min(j,seg[i-1].queryLeft(1,left[i-1][j],right[i-1][j]));
            right[i][j] = std::max(j,seg[i-1].queryRight(1,left[i-1][j],right[i-1][j]));
        }
        seg[i].build(1,1,n);
        rep(j,1,n) seg[i].modify(1,j,left[i][j],right[i][j]);
    }
}

inline void main(){
    gin >> n >> k >> m; 
    rep(i,1,m) {
        int l,r; gin >> l >> r;
        if (l < r) segs[0].push_back({l,r});
        else segs[1].push_back({l,r});
    } init(); 
    gin >> q; 
    while (q--) {
        int s,t; gin >> s >> t;
        prt << ask(s,t) << edl;
    }
}

}signed main(){wxy::main(); return 0;}
```



---

## 作者：GGapa (赞：1)

### P8163 [JOI 2022 Final] 铁路旅行 2 (Railway Trip 2)

https://www.luogu.com.cn/problem/P8163 

这个题如果同时思考 $A_j < B_j$ 和 $A_j > B_j$ 脑子是会爆炸的，对于这种有操作会莫名其妙夹在在一起的题，应当考虑**化简问题，只考虑其中一种做法，并尝试推广到全局。**也就是非常有启发性的子任务 $5$。

尝试只考虑 $A_j < B_j$ 的问题该如何处理，我们可以使用 multiset 维护出对于每个点，其只乘坐一次列车能够到达最远的点是哪一个 $ri_i$；那么对于每一次询问，初始时 $[l, r] = [s, s]$，坐一次列车相当都对 $r$ 执行如下操作：$r \gets \max_{i\in[l, r]} ri_i$，需要用到  ST 表，如果暴力更新 $r$ 那么复杂度是 $O(qn\log n)$，考虑优化，有一个很显然的想法是使用倍增 $ri(i, j)$ 代表点 $j$ 走了 $2^i$ 步最远能够到达的右端点，按照平时 $ri(i, j) = ri(i-1,ri(i-1,j))$ 转移是不行的，因为 $[j, ri(i - 1, j)]$ 中所有的值都可能影响 $ri(i, j)$ 的取值，所以需要用到 ST 表进行区间查询最大值时间复杂度 $O(n \log^2 n) - O(n \log n)$。

回到原问题，本质上我们是要依次扩展区间 $[l, r]$，对于 $A_j >B_j$ 的情况和刚才的区别在于倍增中区间查询的左端点不是不变的了，令 $le(i, j)$ 代表点 $j$，最少转 $2^j$ 次车能够到达的最远左端点，转移时查询的区间变为 $[le(i - 1, j), ri(i - 1, j)]$，本质上还是对于一个区间进行倍增转移，与子任务 $5$ 的做法没有本质区别。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using namespace std;
using LL = long long;
using VI = vector<int>;

constexpr int N = 1e5 + 5;

int n, k, m;
vector<pair<int, int>> tpl[N], tpr[N]; 
int le[20][N], ri[20][N], mx[20][20][N], mn[20][20][N];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k >> m;
    for(int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if(u < v) tpr[u].emplace_back(v, 1), tpr[min(u + k, v)].emplace_back(v, -1);
        else      tpl[u].emplace_back(v, 1), tpl[max(u - k, v)].emplace_back(v, -1);
    }

    {
        multiset<int> s;
        rep(i, 1, n) {
            for(auto p : tpr[i]) {
                if(p.second == 1) s.insert(p.first);
                else s.erase(s.find(p.first));
            }
            if(s.size()) ri[0][i] = *s.rbegin();
            else ri[0][i] = i;
        }
        s.clear();

        per(i, n, 1) {
            for(auto p : tpl[i]) {
                if(p.second == 1) s.insert(p.first);
                else s.erase(s.find(p.first));
            }
            if(!s.empty()) le[0][i] = *s.begin();
            else le[0][i] = i;
        }
    }

    auto qmx = [&](int i, int l, int r) {
        int len = __lg(r - l + 1);
        return max(mx[i][len][l], mx[i][len][r - (1 << len) + 1]);
    };
    auto qmn = [&](int i, int l, int r) {
        int len = __lg(r - l + 1);
        return min(mn[i][len][l], mn[i][len][r - (1 << len) + 1]);
    };

    rep(i, 1, 19) {
        rep(j, 1, n) mx[i - 1][0][j] = ri[i - 1][j], mn[i - 1][0][j] = le[i - 1][j];
        rep(x, 1, 18) for(int y = 1; y + (1 << x) - 1 <= n; y++) {
            mx[i - 1][x][y] = max(mx[i - 1][x - 1][y], mx[i - 1][x - 1][y + (1 << x - 1)]);
            mn[i - 1][x][y] = min(mn[i - 1][x - 1][y], mn[i - 1][x - 1][y + (1 << x - 1)]);
        }
        if(i == 19) continue;
        rep(j, 1, n) {
            ri[i][j] = qmx(i - 1, le[i - 1][j], ri[i - 1][j]);
            le[i][j] = qmn(i - 1, le[i - 1][j], ri[i - 1][j]);
        }
    }

    // 以上是预处理。

    int q; cin >> q;
    for(int s, st; q--; ) {
        cin >> s >> st;
        int ans = 0, l = s, r = s;
        bool tag = 0;
        per(i, 18, 0) {
            int t = __lg(r - l + 1);
            int nl = qmn(i, l, r), nr = qmx(i, l, r);
            if(nl <= st && st <= nr) {
                tag = 1;
                continue;
            }
            l = nl, r = nr;
            ans += (1 << i);
        }
        int nl = qmn(0, l, r), nr = qmx(0, l, r);
        if(nl <= st && st <= nr) ans++;
        else ans = -1;
        cout << ans << '\n';
    }
    
    return 0; 
}
```

---

## 作者：happybob (赞：0)

考虑有向线段和询问都是从左往右怎么办。

记 $f_{i,j}$ 表示从点 $i$ 出发，乘至多 $2^j$ 次车能到达的最右位置。倍增，从小到大枚举 $j$ 并维护线段树即可。

询问时，考虑从大到小枚举 $x$，尝试走 $2^x$ 步并判断是否会超过目标位置。最终步数加 $1$ 即为答案。

存在反向的询问与线段时，额外维护 $g_{i,j}$ 表示从点 $i$ 出发至多 $2^j$ 次到达的最左位置。显然转移对于 $j$ 来说是无后效性的，于是套用上述做法即可。总复杂度 $O((n+q) \log^2 n+m \log n)$。

将线段树换为线性 RMQ 可做到 $O((n+q+m)\log n)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <map>
using namespace std;

constexpr int N = 1e5 + 5;
array<int, N> lft, rt;

int n, m, q, k;

array<vector<pair<int, int>>, N> vl, vr;

class SegmentTree
{
public:
	struct Node
	{
		int l, r, maxn;
	};
	array<Node, N << 2> tr;
	void pushup(int u)
	{
		tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, (int)-1e9 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update(int u, int x, int v)
	{
		if (tr[u].l == tr[u].r)
		{
			tr[u].maxn = v;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) update(u << 1, x, v);
		else update(u << 1 | 1, x, v);
		pushup(u);
	}
	int query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].maxn;
		int mid = tr[u].l + tr[u].r >> 1, res = (int)-1e9;
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid) res = max(res, query(u << 1 | 1, l, r));
		return res;
	}
};

array<SegmentTree, 19> fs, gs;
array<array<int, 19>, N> f, g;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k >> m;
	for (int i = 1; i <= m; i++)
	{
		int a, b;
		cin >> a >> b;
		if (a < b)
		{
			int r = min(a + k - 1, b - 1);
			vl[a].emplace_back(b, 1);
			vl[r + 1].emplace_back(b, -1);
		}
		else
		{
			swap(a, b);
			int l = max(a + 1, b - k + 1);
			vr[b].emplace_back(a, 1);
			vr[l - 1].emplace_back(a, -1);
		}
	}
	for (int i = 1; i <= n; i++) lft[i] = rt[i] = i;
	multiset<int> st;
	for (int i = 1; i <= n; i++)
	{
		for (auto&& [x, op] : vl[i])
		{
			if (op == 1) st.emplace(x);
			else st.erase(st.find(x));
		}
		if (st.size()) rt[i] = max(rt[i], *st.rbegin());
	}
	st.clear();
	for (int i = n; i >= 1; i--)
	{
		for (auto&& [x, op] : vr[i])
		{
			if (op == 1) st.emplace(x);
			else st.erase(st.find(x));
		}
		if (st.size()) lft[i] = min(lft[i], *st.begin());
	}
	fs[0].build(1, 1, n), gs[0].build(1, 1, n);
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = rt[i], g[i][0] = lft[i];
		fs[0].update(1, i, rt[i]);
		gs[0].update(1, i, -lft[i]);
	}
	for (int j = 1; j < 19; j++)
	{
		fs[j].build(1, 1, n), gs[j].build(1, 1, n);
		for (int i = 1; i <= n; i++) g[i][j] = (int)1e9;
		for (int i = 1; i <= n; i++)
		{
			int l = -gs[j - 1].query(1, i, i), r = fs[j - 1].query(1, i, i);
			f[i][j] = fs[j - 1].query(1, l, r);
			g[i][j] = -gs[j - 1].query(1, l, r);
			fs[j].update(1, i, f[i][j]);
			gs[j].update(1, i, -g[i][j]);
		}
	}
	cin >> q;
	while (q--)
	{
		int s, t;
		cin >> s >> t;
		int l = s, r = s;
		int ans = 0;
		for (int i = 18; i >= 0; i--)
		{
			int y = fs[i].query(1, l, r), x = -gs[i].query(1, l, r);
			if (x <= t && t <= y) continue;
			ans += (1 << i);
			l = x, r = y;
		}
		int y = fs[18].query(1, l, r), x = -gs[18].query(1, l, r);
		if (!(x <= t && t <= y)) cout << "-1\n";
		else cout << ans + 1 << "\n";
	}
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

这个题如果用最暴力的思想，就是使用 bitset 维护可达性。但是首先注意到区间是连续的，也就是说对于每个点只用记录能到达的最左最右端点；然后再注意到求步数可以倍增，于是这个题就只剩下怎样维护倍增了。

考虑一个点的一次转移，要用当前区间扩展到一个不小于它的区间。由于有对于上车位置的限制，这个区间的每一个点都应该被考虑，而不应只用端点更新。这就涉及到区间查询，要使用数据结构实现。

这里用到的线段树里有两种不下传的标记：一种是记录子树中任何一个点能到达的最大最小值，一种记录所有点共同能到达的最大最小值。询问时，对在区间里的树点统计前者，对祖先统计后者。

求解答案时，使用求树上最近公共祖先的思想，求一个最大临界值，再加上一即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
typedef pair < int, int > PII;
int n, k, m, q;
struct subway {int a, b;} s[N];
struct SGT
{
	int rt, idx;
	struct SGTnode
	{
		int ls, rs, lsum, rsum, lval, rval;
		#define ls(x) tree[x].ls
		#define rs(x) tree[x].rs
		#define lsum(x) tree[x].lsum
		#define rsum(x) tree[x].rsum
		#define lval(x) tree[x].lval
		#define rval(x) tree[x].rval
	}tree[N];
	inline void pushup(int now)
	{
		lsum(now) = 1e9, rsum(now) = -1e9;
		if(ls(now)) lval(now) = min(lval(now), lval(ls(now))), rval(now) = max(rval(now), rval(ls(now)));
		if(rs(now)) lval(now) = min(lval(now), lval(rs(now))), rval(now) = max(rval(now), rval(rs(now)));
	}
	inline void build(int &now, int l, int r)
	{
		if(!now) now = ++idx;
		lsum(now) = l, rsum(now) = r;
		lval(now) = 1e9, rval(now) = -1e9;
		if(l == r) {lsum(now) = rsum(now) = lval(now) = rval(now) = l; return ;}
		int mid = l + r >> 1;
		if(l <= mid) build(ls(now), l, mid);
		if(mid < r) build(rs(now), mid + 1, r);
	}
	inline void insert(int now, int l, int r, int L, int R, int ln, int rn)
	{
//		cout << l << " " << r << " " << L << " " << R << endl;
		lsum(now) = min(lsum(now), ln);
		rsum(now) = max(rsum(now), rn);
		if(L > R) return ;
		if(L <= l && r <= R) {lval(now) = min(lval(now), ln); rval(now) = max(rval(now), rn); return ;}
		int mid = l + r >> 1;
		if(L <= mid) insert(ls(now), l, mid, L, R, ln, rn);
		if(mid < R) insert(rs(now), mid + 1, r, L, R, ln, rn);
	}
	inline PII ask(int now, int l, int r, int L, int R)
	{
//		cout << now << " " << l << " " << r << " " << L << " " << R << " " << lsum(now) << " " << rsum(now) << endl;
		if(L > R) return {1e9, -1e9};
		if(L <= l && r <= R) return {lsum(now), rsum(now)};
		int mid = l + r >> 1, lans = 1e9, rans = -1e9;
		if(L <= mid)
		{
			PII cur = ask(ls(now), l, mid, L, R);
			lans = min(lans, cur.first);
			rans = max(rans, cur.second);
		}
		if(mid < R)
		{
			PII cur = ask(rs(now), mid + 1, r, L, R);
			lans = min(lans, cur.first);
			rans = max(rans, cur.second);
		}
//		cout << l << " " << r << " " << lans << " " << rans << endl;
		return {min(lval(now), lans), max(rval(now), rans)};
	}
};
SGT T[30];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k >> m;
	for(int i = 0; i <= 25; ++i) T[i].build(T[i].rt, 1, n);
	for(int i = 1; i <= m; ++i)
	{
		cin >> s[i].a >> s[i].b;
		if(s[i].a <= s[i].b) T[0].insert(T[0].rt, 1, n, s[i].a, min(s[i].a + k - 1, s[i].b - 1), 1e9, s[i].b);
		else T[0].insert(T[0].rt, 1, n, max(s[i].b + 1, s[i].a - k + 1), s[i].a, s[i].b, -1e9);
	}
//	for(int j = 1; j <= n; ++j)
//		cout << T[0].ask(T[0].rt, 1, n, j, j).first << " " << T[0].ask(T[0].rt, 1, n, j, j).second << endl;
//	system("pause");
	for(int i = 1; i <= 25; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			PII now, res;
			now = T[i - 1].ask(T[i - 1].rt, 1, n, j, j);
//			cout << "A " << now.first << " " << now.second << endl;
			res = T[i - 1].ask(T[i - 1].rt, 1, n, now.first, now.second);
//			cout << "B " << res.first << " " << res.second << endl;
			T[i].insert(T[i].rt, 1, n, j, j, res.first, res.second);
		}
	}
	cin >> q;
	for(int i = 1; i <= q; ++i)
	{
		int s, t; cin >> s >> t;
		PII now = T[25].ask(T[25].rt, 1, n, s, s);
		if(!(now.first <= t && t <= now.second))
		{
			cout << -1 << '\n';
			continue;
		}
		int head = s, tail = s, ans = 0;
		for(int i = 25; i >= 0; --i)
		{
			PII cur = T[i].ask(T[i].rt, 1, n, head, tail);
			if(!(cur.first <= t && t <= cur.second))
				head = cur.first, tail = cur.second, ans += (1 << i);
		}
		assert(!(head <= t && t <= tail));
		cout << ans + 1 << '\n';
	}
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

好的如你所见，这道题给了几条**有方向**的线路，然后 $q$ 组询问，每次要求我们必须乘坐最少的不同的线路从 $S$ 到达 $T$，问答案是什么，没有输出 $-1$。

考虑对线路进行分类，大致可以分为从起点至 $n$ 方向的线路和从起点至 $1$ 方向的线路。其中，为了叙述方便，我们称至 $n$ 方向的线路为**正方向线路**，反之称其为**反方向线路**。

然后对于每一个询问 $(st,ed)$，表示从 $st$ 至 $ed$。

当 $st$ 小于 $ed$ 时，说明我们可以只通过走正方向线路来跑到终点，因为如果我换乘了某一个反方向线路后能够到达，还不如不换直接到达，可以证明对于这种情况我们只需要考虑正方向线路。

当 $st$ 大于 $ed$ 时同理，我们只需要考虑反方向线路。

故对于每一询问判断一下其方向然后尝试以最快的速度跳跃即可，具体的可以先对正方向线路按左端点为第一关键字右端点为第二关键字进行排序从小到大，反方向就是右端点第一，左端点第二，从大到小排序，然后通过暴力查找的方法做到每次询问 $O(m)$ 的方式解决。

总的时间复杂度为 $O(qm)$，不足以通过本题。

每次只跳跃一个区间有些浪费，因为答案是 $m$ 量级的，所以没有更好的方法能够加速一个一个跳跃区间的过程了，既然跳跃一次不行，就考虑一次跳跃多个。

利用**倍增**的思想可以很好的解决这个问题，具体的，类似求最近公共祖先的问题，令 $l(i,j)$ 为从 $i$ 开始沿着 $2^j$ 个反方向路径能够跳跃的最远位置，令 $r(i,j)$ 为从 $i$ 开始沿着 $2^j$ 个正方向路径能够跳跃的最远位置。

其中，如果我们从 $st$ 跳跃了 $2^i$ 个区间那么我们就可以到达 $l(st,i)$ 至 $r(st,i)$ 中的**任意**一个点。因为如果我能够跳到某个点，就说明必然有走法能够从 $i$ 到达该点，而且路径是连续的，所以 $i$ 至该点的所有点都能够到达。

故考虑一直跳跃区间，但是必须满足跳跃后目前能够任意跳跃到的区间 $(l,r)$ 不能够完全包括询问区间 $(st,ed)$。这是显然的，然后最后跳跃一次即可。注意特别判断能否跳跃到，如果在最后跳跃一次后跳跃不到就说明没有可行解。

考虑倍增数组怎么求，可以这样想，假设我们求出了 $l(i,j-1)$ 和 $r(i,j-1)$。那么是不是我们能够到达的点就在 $(i,j-1)$ 与 $r(i,j-1)$ 之间，其他的目前到不了，那我们可以通过在其中的一个点**作为跳板**到达某一个点，故其递推公式为：

$l(i,j)=\min(l(i,j),l(id,j−1))$。

$r(i,j)=\max(r(i,j),r(id,j−1))$。

其中 $id \in [l(i,j-1),r(i,j-1)]$。但是显然这样时间复杂度过不去，挂个数据结构维护即可，建议使用线段树。

但是有个问题，就是如何求 $l(i,0)$ 与 $r(i,0)$，~~这个你总不能从负数转移过来吧~~。我们可以考虑运用单调队列的方式分别求解。

对于反方向的线路 $(l,r)$，都满足 $l > r$，把它看做一个区间。故以 $l$ 为第一关键字，以 $r$ 为第二关键字从大到小排序，然后倒序求解 $l(i,0)$。排序后，相当于我们把 $l$ 对其的影响消掉，然后考虑 $r$ 的问题。根据其性质，如果一个区间的 $l$ 大于了另一个区间的 $l$，且另一个区间也包括了位置 $i$，那么当前区间就没有必要存在了，因为它一定不会更新答案，直接弹出队列即可。对了，加入区间的时候记得利用指针**把合法的区间都加入其中**，因为它一次性可能不止加入一个，而每次加入一个都需要**弹出**队列尾部不优秀的答案。然后也要把非法答案弹出，如果目前位置 $i$ 加上题目给定的值 $k$ 的位置没有被区间所包含就直接弹出。

对于正方向的线路同理，以 $l$ 为第一关键字，以 $r$ 为第二关键字从小排序，然后正序求解即可。

时间复杂度为 $O(n \log n^2)$。

```cpp
void init(){
	for(int i = 1;i <= n;i++)f[i][0]=g[i][0]=i;
	sort(up+1,up+1+upl);
	sort(down+1,down+1+downl,greater<pair<int,int> >());
	head=1,tail=0;
	for(int i = 1,r = 1;i <= n;i++){
		while(r<=upl&&up[r].fi<=i){
			int tmpr=up[r].se;
			while(head<=tail&&up[q[tail]].se<=tmpr)tail--;
			q[++tail]=r;
			r++;
		}
		while(head<=tail&&up[q[head]].fi<=i-k)head++;
		if(head<=tail)f[i][0]=max(f[i][0],up[q[head]].se);
	}
	head=1,tail=0;
	for(int i = n,r = 1;i >= 1;i--){
		while(r<=downl&&down[r].fi>=i){
			int tmpl=down[r].se;
			while(head<=tail&&down[q[tail]].se>=tmpl)tail--;
			q[++tail]=r;
			r++;
		}
		while(head<=tail&&down[q[head]].fi>=i+k)head++;
		if(head<=tail)g[i][0]=min(g[i][0],down[q[head]].se);
	}

}
```

然后利用线段树加速求解。

```cpp
	rt[0].build(1,1,n,0);
	for(int j = 1;j <= 16;j++){
		for(int i = 1;i <= n;i++){
			tree tmp=rt[j-1].query(1,1,n,g[i][j-1],f[i][j-1]);
			f[i][j]=tmp.maxr,g[i][j]=tmp.minl;
		}
		rt[j].build(1,1,n,j);
	}
```

最后，倍增的求取答案。

```cpp
int getans(int st,int ed){
	int l = st,r = st,ans=0;
	for(int i = 16;i >= 0;i--){
		tree tmp=rt[i].query(1,1,n,l,r);
		if(tmp.minl<=ed&&ed<=tmp.maxr)continue;
		l=tmp.minl,r=tmp.maxr,ans+=(1<<i);
	}
	tree tmp=rt[0].query(1,1,n,l,r);
	if(tmp.minl<=ed&&ed<=tmp.maxr)return ans+1;
	return -1; 
}
```

总体的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
const int N=1e5+5,M=2e5+5;
pair <int,int> up[M],down[M];
int n,k,m,l,r,upl,downl,f[N][17],g[N][17],head,tail,q[M];
struct tree{
	int minl,maxr;
};
tree merge(tree x,tree y){
	tree ans;
	ans.minl=min(x.minl,y.minl);
	ans.maxr=max(x.maxr,y.maxr);
	return ans;
}
struct Point{
	tree c[N<<2];
	void updata(int x){	
		c[x]=merge(c[x<<1],c[x<<1|1]);
	}
	void build(int x,int l,int r,int dep){
		if(l==r){
			c[x].minl=g[l][dep],c[x].maxr=f[l][dep];
			return;
		}
		int mid=(l+r)>>1;
		build(x<<1,l,mid,dep);
		build(x<<1|1,mid+1,r,dep);
		updata(x);
	}
	tree query(int x,int l,int r,int s,int t){
		if(l>=s&&r<=t)return c[x];
		int mid=(l+r)>>1;
		if(s>mid)return query(x<<1|1,mid+1,r,s,t);
		else{
			if(t<=mid)return query(x<<1,l,mid,s,t);
			return merge(query(x<<1,l,mid,s,t),query(x<<1|1,mid+1,r,s,t));
		}
	}
}rt[17];
void init(){
	for(int i = 1;i <= n;i++)f[i][0]=g[i][0]=i;
	sort(up+1,up+1+upl);
	sort(down+1,down+1+downl,greater<pair<int,int> >());
	head=1,tail=0;
	for(int i = 1,r = 1;i <= n;i++){
		while(r<=upl&&up[r].fi<=i){
			int tmpr=up[r].se;
			while(head<=tail&&up[q[tail]].se<=tmpr)tail--;
			q[++tail]=r;
			r++;
		}
		while(head<=tail&&up[q[head]].fi<=i-k)head++;
		if(head<=tail)f[i][0]=max(f[i][0],up[q[head]].se);
	}
	head=1,tail=0;
	for(int i = n,r = 1;i >= 1;i--){
		while(r<=downl&&down[r].fi>=i){
			int tmpl=down[r].se;
			while(head<=tail&&down[q[tail]].se>=tmpl)tail--;
			q[++tail]=r;
			r++;
		}
		while(head<=tail&&down[q[head]].fi>=i+k)head++;
		if(head<=tail)g[i][0]=min(g[i][0],down[q[head]].se);
	}
	rt[0].build(1,1,n,0);
	for(int j = 1;j <= 16;j++){
		for(int i = 1;i <= n;i++){
			tree tmp=rt[j-1].query(1,1,n,g[i][j-1],f[i][j-1]);
			f[i][j]=tmp.maxr,g[i][j]=tmp.minl;
		}
		rt[j].build(1,1,n,j);
	}
}
int getans(int st,int ed){
	int l = st,r = st,ans=0;
	for(int i = 16;i >= 0;i--){
		tree tmp=rt[i].query(1,1,n,l,r);
		if(tmp.minl<=ed&&ed<=tmp.maxr)continue;
		l=tmp.minl,r=tmp.maxr,ans+=(1<<i);
	}
	tree tmp=rt[0].query(1,1,n,l,r);
	if(tmp.minl<=ed&&ed<=tmp.maxr)return ans+1;
	return -1; 
}
int qt;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k >> m;
	for(int i = 1;i <= m;i++){
		cin >> l >> r;
		if(l<r)up[++upl]=make_pair(l,r);
		else down[++downl]=make_pair(l,r);
	}
	init();   
 /*for(int i = 0;i <= 2;i++){
    	for(int j = 1;j <= n;j++)cout << "{" << g[j][i] << "," << f[j][i] << "}  ";
    	cout << "\n";
	}*/
	cin >> qt;
	for(int i = 1;i <= qt;i++){
		cin >> l >> r;
		cout << getans(l,r) << "\n";
	}
	return 0;
}

```

---

