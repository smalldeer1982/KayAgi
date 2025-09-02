# [IOI 2018] meetings 会议

## 题目背景

本题为交互题，但在此请提交**完整程序**。

本题因为测试点过多，文件过大，只选择了33个测试点进行测评（涵盖了所有子任务）。剩余11组数据可下载数据自行测评。

https://ioi2018.jp/wp-content/tasks/contest2/meetings.zip

## 题目描述

有 $N$ 座山横着排成一行，从左到右编号为从 $0$ 到 $N-1$。山的高度为 $H_i$（$0\leq i\leq N-1$）。每座山的顶上恰好住着一个人。

你打算举行 $Q$ 个会议，编号为从 $0$ 到 $Q-1$。会议 $j$（$0\leq j\leq Q-1$） 的参加者为住在从山 $L_j$ 到山 $R_j$（包括 $L_j$ 和 $R_j$）上的人（$0\leq L_j\leq R_j\leq N-1$）。对于该会议，你必须选择某个山 $x$ 做为会议举办地（$L_j\leq x\leq R_j$）。举办该会议的成本与你的选择有关，其计算方式如下：

- 来自每座山 $y$（$L_j\leq y\leq R_j$） 的参会者的成本，等于在山 $x$ 和 $y$ 之间（包含 $x$ 和 $y$）的所有山的最大高度。特别地，来自山 $x$ 的参会者的成本是 $H_x$，也就是山 $x$ 的高度。

- 会议的成本等于其所有参会者的成本之和。

你想要用最低的成本来举办每个会议。

注意，所有的参会者将在每次会议后回到他们自己的山；所以一个会议的成本不会受到先前会议的影响。

## 说明/提示

### 样例#1解释

会议$j=0$有$L_j=0$和$R_j=2$，所以将由住在山$0$、$1$和$2$上的人参加。如果山$0$被选做举办地，会议$0$的成本计算如下：

- 住在山$0$上的参会者的成本是$\max\lbrace H_0\rbrace=2$。
- 住在山$1$上的参会者的成本是$\max\lbrace H_0,H_1\rbrace=4$。
- 住在山$2$上的参会者的成本是$\max\lbrace H_0,H_1,H_2\rbrace=4$。
- 因此，会议$0$的成本是$2+4+4=10$。

不可能以更低的成本来举办会议$0$了，因此会议$0$的最低成本是$10$。

会议$j=1$有$L_j=1$和$R_j=3$，因此将由住在山$1$、$2$和$3$上的人参加。如果山$2$被选做举办地，会议$1$的成本计算如下：

- 住在山$1$上的参会者的成本是$\max\lbrace H_1,H_2\rbrace=4$。
- 住在山$2$上的参会者的成本是$\max\lbrace H_2\rbrace=3$。
- 住在山$3$上的参会者的成本是$\max\lbrace H_1,H_2,H_3\rbrace=5$。
- 因此，会议$1$的成本是$4+3+5=12$。

不可能以更低的成本来举办会议$1$了，所以会议$1$的最低成本是$12$。

### 限制条件

- $1\leq N\leq 750\space000$
- $1\leq Q\leq 750\space000$
- $1\leq H_i\leq1\space000\space000\space000$
- $0\leq L_j\leq R_j\leq R-1(0\leq j\leq Q-1)$
- $(L_j,R_j)\neq(L_k,R_k)(0\leq j<k\leq Q-1)$

### 子任务

1. (4分) $N\leq3000,Q\leq10$
2. (15分) $N\leq5000,Q\leq5000$
3. (17分) $N\leq100\space000,Q\leq100\space000,H_i\leq2(0\leq i\leq N-1)$
4. (24分) $N\leq100\space000,Q\leq100\space000,H_i\leq20(0\leq i\leq N-1)$
5. (40分) 没有附加限制

### Author

Riku Kawasaki (Japan)

### Source

IOI 2018 D2T3

## 样例 #1

### 输入

```
4 2
2 4 3 5
0 2
1 3
```

### 输出

```
10
12
```

## 样例 #2

### 输入

```
3 3
2 1 2
0 0
0 1
0 2
```

### 输出

```
2
3
5
```

## 样例 #3

### 输入

```
5 1
1000000000 1000000000 1 1000000000 1000000000
0 4
```

### 输出

```
4000000001
```

## 样例 #4

### 输入

```
15 10
10 71 84 33 6 47 23 25 52 64 70 31 22 31 2
5 10
3 7
0 13
8 12
0 0
1 3
7 13
1 13
10 12
1 1
```

### 输出

```
281
180
828
263
10
201
364
744
123
71
```

# 题解

## 作者：s_r_f (赞：26)

DP。

**19分做法：**

本题的DP方程很显然,就是找到x 为 [L,r] 之间的 MAX,然后

f[L][R] = min( f[L][x-1] + (R-x+1) × a[x] , f[x+1][R] + (x-L+1)  × a[x])。

O(n^2)直接DP,就能拿到前两档部分分了。

**100分做法:**

首先你得知道什么是笛卡尔树。

明确一点: 每个节点mid代表一个区间[L,R],且mid为**RMQ(L,R)即[L,R]之间的最大值**

所以在打好st表的情况下，可以O(n)建出笛卡尔树。

一类与Min/Max有关的动规方程,大多可以用笛卡尔树来优化。

我们把每个询问(利用19分做法的dp方程)拆成两个,这样**区间最左/右端**就有一个**比当前区间所有数字都大**的数,翻转数组后可以转换为**只有区间最左端就有一个比当前区间所有数字都大的数**

建出h[]数组的笛卡尔树，我们只要求出每个点i所代表区间[L,R]的
f[L,L] , f[L,L+1] , ... f[L,R] 就可以回答所有询问。

于是我们只需要找到每个L(L从1到n)最大的R以及对应的节点x,在求出节点x对应的所有dp值之后,就可以回答所有对应的询问了。

**那么问题来了,怎么求每个节点的答案呢？**

考虑**合并mid的左右儿子的答案。**

f[L][L .. mid - 1]已经在左儿子中求出;

f[L][mid] = f[L][mid-1] + a[mid];

f[L][i] **(i > mid)** = min{ **f[L][mid] + (i - mid) * a[mid]**
, **f[mid+1][i] + (mid - L + 1) * a[mid]**
}

这貌似是O(n^2)的？？？怎么办？？？

我们注意到对于第三个方程,选择左边的式子和右边的式子是单调的。

因为f[mid+1][i]随i增加的增加量**不会大于a[mid]**，而f[L][mid] + (i - mid) × a[mid] 随i增加的增加量**等于a[mid]**,所以具有单调性。

所以我们就可以二分啦！

在线段树上二分合并dp数组，每次O(logn)查答案,O(nlogn + qlogn).


~~相信一个切IOI题的人一定会做这种线段树二分,否则还是弃疗吧~~

~~忽略上面**划掉的**鬼话~~

还是讲一下：

我们的线段树只需要支持**赋值/增加一个以下标i为自变量的一次函数ki + b**和**线段树上二分** 的操作

~~是不是很简单呢~~

OK，IOI2018 Day2 T3,完！

****
最后总结一下：

1、拆分询问成2组；    
2、O(nlogn) **打出st表**；  
3、O(n)建笛卡尔树；  
4、笛卡尔树上dp;  
5、翻转数组,对另一组询问做DP;     
6、合并答案并输出。

具体细节还是看代码吧。


```cpp
#include <bits/stdc++.h>
#define LL long long

using namespace std;

inline int read(){
    int x = 0,f = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
    while (c <='9' && c >='0') {x = x * 10 + c - '0';c = getchar();}
    return x * f;
}

inline void write(LL x){
    int k = 0;char put[40];
    if (!x) putchar('0');
    if (x < 0) putchar('-'),x = -x;
    while (x)  put[++k] = (x % 10) + '0',x /= 10;
    while (k)  putchar(put[k]),--k;
    putchar('\n');
}

const LL INF = 1LL << 62,N = 750050,Q = N;
int n,m,a[N],b[N],rk[N];
inline bool cmp(int i,int j){ return a[i] == a[j] ? i > j : a[i] > a[j]; }

int st[N][22],Log[N],Pow[22]; static int tt,xx,yy;
inline int RMQ(int l,int r){
    tt = Log[r-l+1],xx = st[l][tt],yy = st[r-Pow[tt]+1][tt];
    return rk[xx] < rk[yy] ? xx : yy;
}
struct Ask{int l,r,id;}q1[Q],q2[Q]; vector<Ask>q[N];
int L,R,Mid;
LL Ans1[Q],Ans2[Q],Ans[Q];

int root,Lc[N],Rc[N];

const int NN = N<<2;
int tp[NN]; LL val[NN],var[NN],K[NN],B[NN];
void Build(int o,int l,int r){
    tp[o] = K[o] = B[o] = 0,val[o] = var[o] = INF;
    if (l < r){
        int mid = l + r >> 1;
        Build(o<<1,l,mid);
        Build(o<<1|1,mid+1,r);
    }
}
inline void SetT(int o,int l,int r,LL k,LL b){
    tp[o] = 1,K[o] = k,B[o] = b;
    val[o] = l * k + b,var[o] = r * k + b;
}
inline void AddT(int o,int l,int r,LL k,LL b){
    tp[o] = tp[o] ? tp[o] : 2;
    K[o] += k,B[o] += b,val[o] += l * k + b,var[o] += r * k + b;
}
inline void DownT(int o,int l,int r){
    if (tp[o]){
        int mid = l + r >> 1;
        if (tp[o] == 1) SetT(o<<1,l,mid,K[o],B[o]),SetT(o<<1|1,mid+1,r,K[o],B[o]);
        else AddT(o<<1,l,mid,K[o],B[o]),AddT(o<<1|1,mid+1,r,K[o],B[o]);
        tp[o] = K[o] = B[o] = 0;
    }
}

int ll,rr; LL kk,bb;
void Set(int o,int l,int r){
    if (ll <= l && rr >= r) SetT(o,l,r,kk,bb);
    else{
        DownT(o,l,r);
        int mid = l + r >> 1;
        if (ll <= mid) Set(o<<1,l,mid); if (rr > mid) Set(o<<1|1,mid+1,r);
        val[o] = val[o<<1],var[o] = var[o<<1|1];
    }
}
void Add(int o,int l,int r){
    if (ll <= l && rr >= r) AddT(o,l,r,kk,bb);
    else{
        DownT(o,l,r);
        int mid = l + r >> 1;
        if (ll <= mid) Add(o<<1,l,mid); if (rr > mid) Add(o<<1|1,mid+1,r);
        val[o] = val[o<<1],var[o] = var[o<<1|1];
    }
}
LL Ask(int o,int l,int r,int p){
    if (l == r) return val[o];
    DownT(o,l,r);
    int mid = l + r >> 1;
    return p <= mid ? Ask(o<<1,l,mid,p) : Ask(o<<1|1,mid+1,r,p);
}
int _ll,_rr; LL k1,b1,b2;
void Maintain(int o,int l,int r){
    if (_ll <= l && _rr >= r){
        if (l * k1 + b1 >= val[o] + b2){
            AddT(o,l,r,0,b2);
            return;
        }
        if (r * k1 + b1 <= var[o] + b2){
            SetT(o,l,r,k1,b1);
            return;
        }
    }
    DownT(o,l,r);
    int mid = l + r >> 1; 
    if (_ll <= mid) Maintain(o<<1,l,mid);
    if (_rr > mid) Maintain(o<<1|1,mid+1,r);
    val[o] = val[o<<1],var[o] = var[o<<1|1];
}

int tl[N],tr[N];
void dfs1(int &o,int l,int r){ //建树
    if (l > r) { o = 0; return; }
    o = RMQ(l,r);
    tl[o] = l,tr[o] = r;
    dfs1(Lc[o],l,o-1);
    dfs1(Rc[o],o+1,r);
}
void dfs2(int x,bool s){ //DP
    LL now = a[x];
    if (Lc[x]) dfs2(Lc[x],0),now += Ask(1,1,n,x-1);
    if (Rc[x]) dfs2(Rc[x],1);
    ll = rr = x,kk = 0,bb = now,Set(1,1,n);
    if (x < tr[x]){
        _ll = x+1,_rr = tr[x];
        k1 = a[x],b1 = now - 1LL * x * a[x],b2 = a[x] * (x - tl[x] + 1LL);
        Maintain(1,1,n);
    }
    if (s)
    for (int i = 0; i < q[tl[x]].size(); ++i) //回答询问
        Ans[q[tl[x]][i].id] = Ask(1,1,n,q[tl[x]][i].r);
}

int main(){
    register int i,j,x,y;
    n = read(),m = read();
    
    for (i = 0; i <= 21; ++i) Pow[i] = 1 << i;
    for (i = 1; i <= n; ++i){
        Log[i] = Log[i-1] + 1; while (Pow[Log[i]] > i) --Log[i];
    }
    //st表
    for (i = 1; i <= n; ++i) a[i] = read(),b[i] = i;
    sort(b+1,b+n+1,cmp);
    for (i = 1; i <= n; ++i) rk[b[i]] = i,st[i][0] = i;
    for (j = 1; j <= Log[n] + 1; ++j)
        for (i = 1; i <= n; ++i) if (i + Pow[j-1] <= n){
            x = st[i][j-1],y = st[i + Pow[j-1]][j-1];
            st[i][j] = rk[x] < rk[y] ? x : y;
        }
    //拆询问
    for (i = 1; i <= m; ++i){
        L = read() + 1,R = read() + 1,Mid = RMQ(L,R);
        q1[i].id = i,q1[i].l = L,q1[i].r = Mid - 1;
        q2[i].id = i,q2[i].l = Mid + 1,q2[i].r = R;
        Ans1[i] = 1LL * a[Mid] * (R - Mid + 1);
        Ans2[i] = 1LL * a[Mid] * (Mid - L + 1);
    }
    //第一组询问(貌似我是反着做的,不过本质上是一样的)
    for (i = 1; i <= m; ++i) if (q2[i].l <= q2[i].r) q[q2[i].l].push_back(q2[i]);
    Build(1,1,n);
    dfs1(root,1,n);
    dfs2(root,1);
    for (i = 1; i <= m; ++i) Ans2[i] += Ans[i];
    //翻转数组做第二组
    reverse(a+1,a+n+1);
    reverse(rk+1,rk+n+1);
    for (i = 1; i <= n; ++i) st[i][0] = i;
    for (j = 1; j <= Log[n] + 1; ++j)
        for (i = 1; i <= n; ++i) if (i + Pow[j-1] <= n){
            x = st[i][j-1],y = st[i + Pow[j-1]][j-1];
            st[i][j] = rk[x] < rk[y] ? x : y;
        }
    
    for (i = 1; i <= n; ++i) q[i].clear();
    for (i = 1; i <= m; ++i) if (q1[i].l <= q1[i].r){
        swap(q1[i].l,q1[i].r);
        q1[i].l = n - q1[i].l + 1;
        q1[i].r = n - q1[i].r + 1;
        q[q1[i].l].push_back(q1[i]);
    }
    Build(1,1,n);
    dfs1(root,1,n);
    dfs2(root,1);
    for (i = 1; i <= m; ++i) Ans1[i] += Ans[i];//合并答案
    for (i = 1; i <= m; ++i) write(min(Ans1[i],Ans2[i]));
    return 0;
}
```

---

## 作者：zhoukangyang (赞：16)

[更好的阅读体验](https://www.cnblogs.com/zkyJuruo/p/15666789.html)

萌新瞎想了很直接的 $\Theta(nq)$（在 $\rm Luogu$ 上过了） 和一个 $\Theta(n \log n +q \log^3 n)$ （在 $\rm UOJ$ 上过了）的做法，就写篇题解吧。

在 $\rm UOJ$ 过了的做法在 $\rm Luogu$ 上过不去应该是因为 $\rm Luogu$ 空间开小了。

**upd:** 洛谷空间开大了，过了，谢谢管理员！~~不过空间好像开太大了，是 805MB。~~

## 题意

> 给定长度为 $n$ 的序列 $h$，$q$ 次询问，每次给定区间 $[l,r]$，你要在 $[l,r]$ 中选出一个位置 $x$ 举行会议，使得 $\sum\limits_{l \le i \le r} \max_{j \in [\min(i,x),\max(i,x)]} h_j$ 最小。

> 数据范围：$1 \le n, q \le 7.5 \times 10^5$，$1 \le h_i \le 10^9$。

## 题解

首先考虑暴力怎么做：每次找到区间中的 $\rm max$，然后枚举是把会议丢 $\rm max$ 的左边还是丢右边即可，问题就被分成了两半。

考虑优化，先找到整个区间的最大值，然后把问题切成两半。不妨考虑左边那一半怎么做。

考虑先建出左边那半的单调栈。设栈中元素为 $S_1,S_2,S_3,...,S_k$。

其中 $h_{S_i} \le h_{S_{i+1}}$，$S_1 = l$，$S_k = r$。

枚举我们选择的会议处于栈中哪两个元素之间。假设设在 $[S_x,S_{x+1})$ 中。

那么：

1. $[l,S_x)$ 的贡献均为 $h_{S_x}$。
2. $[S_{x+1},r)$ 中一个元素的贡献只和该元素在栈中哪两个元素之间有关。
3. 由于 $x+1$ 是 $x$ 后面第一个值 $> h_x$ 的元素，因此 $[S_x,S_{x+1})$ 中元素的贡献可以预处理（找到 $(S_x,S_{x+1})$ 中的最大值，然后可以递归成形式相同的子问题）。

于是我们就会 $\Theta(nq)$ 了。

直接写是过不去的。我们预处理出 $fa_i$ 为 $i$ 后第一个 $> h_i$ 的元素。

然后从 $l$ 开始暴力跳 $fa$ 跳到 $r$ 就过了。

[$n^2$ 过百万，暴力碾标算！](https://www.luogu.com.cn/record/64596217)

观察我们的暴力是怎么完成的：其实是求了树上一条链的 $\max(k_ix+b_i)$。

于是可以树剖，转化为序列上区间 $\max(k_ix+b_i)$。建颗线段树，每个线段树上的节点 $[L,R]$ 维护一颗李超树即可。

为了优化复杂度，$[L,R]$ 上的李超树可以用 $[L,mid]$ 和 $(mid+1,R]$ 的李超树合并。

其实可以用 [XJOI4182](https://xjoi.net/contest/1712/problem/2) 的套路优化到 $\Theta(n \log n + q \log^2 n)$~~，不过我懒就没写~~。

[aclink](https://uoj.ac/submission/519892)

感觉这种思路也是可以再优化的，毕竟链上的元素是有单调性的。

**祝大家学习愉快！**

---

## 作者：流水行船CCD (赞：11)

本解法空间消耗奇大，LOJ 无法通过所有数据。

## Solution 

### 19pts

区间问题，考虑区间 DP，后效性很强，似乎不可做，但我们充分发扬人类智慧，发现如果**以区间中的最大值将区间分为两部分时，可以分类讨论开会点在最大值的左边或右边**（而开会点一定不会选择最大值，这会让答案很劣），此时另外一边到该开会点必经最高山，因此代价均为最高山高度，如图（只列举了开会点在左的情况，开会点在右方同理）：

![](https://cdn.luogu.com.cn/upload/image_hosting/aj3ssnnk.png)

设 $f_{l,r}$ 表示区间 $[l,r]$ 中所有人参会的最小代价，且 $[l,r]$ 最高峰在 $x$，则有：

$$f_{l,r} = \min\{f_{l,x-1}\ + (r-x+1) \times h_x\ \ ,\ \ f_{x+1,r} + (x-l+1) \times h_x\}$$

本质上是分讨开会点在左或右子区间，只是注意一下 $l = r$ 时赋初值的问题就行了。

### 100pts

显然，此 DP 优化不下去（状态 $O(n^2)$），但是通过最值来划分区间，不难让我们联想到笛卡尔分治树，考虑将该问题搬到树上设计算法。

对于任意一个询问 $[l,r]$，一定属于其最值 $x$ 的子树，如果按照 $x$ 进行切割，必定会将其拆成笛卡尔树上 $ls_x$ 的一段后缀和 $rs_x$ 的一段前缀的拼接问题，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/15o7o2ea.png)

现在我们将任意一个区间特化为了子树树根上的前后缀查询，考虑重设 DP 状态。我们设 $f_{x,i}$ 表示 $x$ 子树内从最左端到 $i$ 号结点这段区间内所有人开会的最小总代价， $g_{x,i}$ 表示 $x$ 子树内从 $i$ 号结点到最右端这段区间内所有人开会的最小总代价。

这里以 $f$ 的状态转移为例（$g$ 与 $f$ 同理）：

![](https://cdn.luogu.com.cn/upload/image_hosting/fbl5h8td.png)

如果 $i \in [L,x-1]$，即图中 $i_1$ 的情况，此时完全是左区间的子问题。

$$\large f_{x,i} = f_{ls_x,i}$$

如果 $i = x$，即图中 $i_2$ 的情况，多增加了一个点的代价，即从最高峰到左区间，代价恒为 $h_x$。

$$\large f_{x,i} = f_{ls_x,x-1} + h_x$$

如果 $i \in [x+1,R]$，即图中 $i_3$ 的情况，此时需要分讨情况：开会点在左侧或开会点在右侧。

- 开会点在左侧，此时左侧为子问题，右侧所有点前往开会点必经最高峰，每个点贡献为 $h_x$。

$$\large f_{x,i} = f_{ls_x,x-1} + (i-x+1) \times h_x$$

- 开会点在右侧，此时右侧为子问题，左侧所有点前往开会点必经最高峰，每个点贡献为 $h_x$。

$$\large f_{x,i} = f_{rs_x,i} + (x-l+1) \times h_x$$

此时我们不难发现可以把 DP 数组放到线段树上，然后 $i_1,i_2$ 的情况就可以通过继承和单点赋值快速更新，但是 $i_3$ 操作有取最值操作，无法快速更新（吉司机线段树是摊还分析的，很容易写炸，这里暂不考虑）。

但是 $i_3$ 有一个很重要的性质：我们**发现 $i$ 越小，开会点在左侧所需代价一定越来越小，$i$ 越大，开会点在右侧所需代价也一定越来越小，它们形似两条一次函数，拥有单调性**。此时我们可以二分找到这两条一次函数的交点，交点之前使用左侧的 DP 方程更新，交点之后使用右侧的 DP 方程更新，这里只需要一个区间加等差数列和区间拷贝即可维护。

这里使用动态开点线段树，即可支持区间加等差数列，区间拷贝，单点查询。

## Ac Code

```cpp
#include<bits/stdc++.h>

#define TIME_LIMIT 2000
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)

using namespace std;

namespace fast_IO {
//快读，省略。 
}
using namespace fast_IO;

const int N = 7.5e5 + 7;

namespace nogf {
	int n, q;
	int arr[N], st[N][20];
	inline int chk(int x, int y) {return arr[x] > arr[y] ? x : y;}
	inline int ma_(int l, int r) {
		int lg = __lg(r - l + 1);
		return chk(st[l][lg], st[r - (1 << lg) + 1][lg]);
	}
	struct Node {//动态开点线段树，标记永久化。 
		int lc, rc;
		ll k, b;
		Node() {
			lc = rc = 0;
			k = b = 0;
		}
#define ls(x) tr[x].lc
#define rs(x) tr[x].rc
	} tr[N * 40]; int trc = 0, f[N], g[N];
	inline void update(int &x, int l, int r, int L, int R, ll k, ll b) {// 区间加等差数列 
		if (L > R) return;
		if (!x) x = ++trc;
//		if (trc > N * 180) throw runtime_error("limited");
		if (L <= l && r <= R) {
			tr[x].k += k, tr[x].b += b;
			return;
		} int mid = (l + r) >> 1;
		if (L <= mid) update(ls(x), l, mid, L, R, k, b);
		if (mid < R) update(rs(x), mid + 1, r, L, R, k, b + k * max(0, mid - max(l, L) + 1));
	}
	inline ll ask(int x, int l, int r, int now, ll k, ll b) { // 单点查询 
		if (l == r) return b + tr[x].b;
		int mid = (l + r) >> 1;
		if (now <= mid) return ask(ls(x), l, mid, now, k + tr[x].k, b + tr[x].b);
		return ask(rs(x), mid + 1, r, now, k + tr[x].k, b + tr[x].b + (k + tr[x].k) * (mid - l + 1));
	}
	inline void copy(int &x, int y, int l, int r, int L, int R, ll k, ll b) { // 区间拷贝 
		if (L > R) return; 
		if (!x) x = ++trc; 
		if (L <= l && r <= R) {tr[x] = tr[y], tr[x].k += k, tr[x].b += b; return; }
		int mid = (l + r) >> 1;
		if (L <= mid) copy(ls(x), ls(y), l, mid, L, R, k + tr[y].k, b + tr[y].b);
		if (mid < R) copy(rs(x), rs(y), mid + 1, r, L, R, k + tr[y].k, b + tr[y].b + (k + tr[y].k) * (mid - l + 1));
	}
	int lc_[N], rc_[N];
	struct Q {int l, r;}c[N];
	ll Ans[N]; vector<int> qwq[N];
	inline int build(int l, int r) { //笛卡尔分治树 
		if (l > r) return 0;
		if (l == r) {//特判 l == r 的情况 
			update(f[l], 1, n, l, l, 0, arr[l]);
			update(g[l], 1, n, l, l, 0, arr[l]);
			for (auto now : qwq[l]) { //回答询问 
				int pos = l;
				ll Res = 1ll * (c[now].r - l + 1) * arr[pos]; 
				ll Res1 = ask(g[lc_[pos]], 1, n, c[now].l, 0, 0) + 1ll * (c[now].r - pos + 1) * arr[pos];
				ll Res2 = ask(f[rc_[pos]], 1, n, c[now].r, 0, 0) + 1ll * (pos - c[now].l + 1) * arr[pos];
				Ans[now] = min(Res, min(Res1, Res2));
			}
			return l;
		}
		int mid = ma_(l, r);
		int lc = build(l, mid - 1), rc = build(mid + 1, r);
		lc_[mid] = lc, rc_[mid] = rc;
		for (auto now : qwq[mid]) { //回答询问 
			int pos = mid;
			ll Res = 1ll * (c[now].r - l + 1) * arr[pos]; 
			ll Res1 = ask(g[lc_[pos]], 1, n, c[now].l, 0, 0) + 1ll * (c[now].r - pos + 1) * arr[pos];
			ll Res2 = ask(f[rc_[pos]], 1, n, c[now].r, 0, 0) + 1ll * (pos - c[now].l + 1) * arr[pos];
			Ans[now] = min(Res, min(Res1, Res2));
		}
		// update f:
		if (mid == l) { //i1 
			update(f[mid], 1, n, mid, mid, 0, arr[mid]);
		} else { //i2
			f[mid] = f[lc];
			update(f[mid], 1, n, mid, mid, 0, ask(f[lc], 1, n, mid - 1, 0, 0) + arr[mid]);
		}
		if (mid < r) { //i3
			int L = mid + 1, R = r, Res = mid;
			while (L <= R) {//找一次函数交点 
				int middle = (L + R) >> 1;
				if (ask(f[lc], 1, n, mid - 1, 0, 0) + 1ll * (middle - mid + 1) * arr[mid] <= ask(f[rc], 1, n, middle, 0, 0) + 1ll * (mid - l + 1) * arr[mid])
					L = middle + 1, Res = middle;
				else 
					R = middle - 1;
			}
			update(f[mid], 1, n, mid + 1, Res, arr[mid], ask(f[lc], 1, n, mid - 1, 0, 0) + 2ll * arr[mid]);
			copy(f[mid], f[rc], 1, n, Res + 1, r, 0, 0);
			update(f[mid], 1, n, Res + 1, r, 0, 1ll * (mid - l + 1) * arr[mid]); 
		}
		// update g:
		if (mid == r) { //i1
			update(g[mid], 1, n, mid, mid, 0, arr[mid]);
		} else { //i2
			g[mid] = g[rc];
			update(g[mid], 1, n, mid, mid, 0, ask(g[rc], 1, n, mid + 1, 0, 0) + arr[mid]);
		}
		if (l < mid) { //i3
			int L = l, R = mid - 1, Res = mid;
			while (L <= R) {//找一次函数交点 
				int middle = (L + R) >> 1;
				if (ask(g[rc], 1, n, mid + 1, 0, 0) + 1ll * (mid - middle + 1) * arr[mid] <= ask(g[lc], 1, n, middle, 0, 0) + 1ll * (r - mid  + 1) * arr[mid])
					R = middle - 1, Res = middle;
				else 
					L = middle + 1;
			}
			update(g[mid], 1, n, Res, mid - 1, -arr[mid], ask(g[rc], 1, n, mid + 1, 0, 0) + 1ll * (mid - Res + 1) * arr[mid]);
			copy(g[mid], g[lc], 1, n, l, Res - 1, 0, 0);
			update(g[mid], 1, n, l, Res - 1, 0, 1ll * (r - mid + 1) * arr[mid]); 
		}
		return mid;
	}
	signed main() {
		wyy >> n >> q;
		REP(i, 1, n) wyy >> arr[i], st[i][0] = i;
		REP(j, 1, 19)
			REP(i, 1, n - (1 << (j - 1))) {
				if (i + (1 << (j - 1)) > n) break;
				st[i][j] = chk(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		int Rt = 0;
		int l, r;
		REP(i, 1, q) {
			wyy >> l >> r, ++l, ++r;
			if (l == r) {
				Ans[i] = arr[l];
				continue;
			}
			int pos = ma_(l, r);
			c[i].l = l, c[i].r = r;
			qwq[pos].emplace_back(i);
		} build(1, n); 
		REP(i, 1, q) jyt << Ans[i] << '\n';
		return 0;
	}

}

signed main() {
//	freopen("05-08.in", "r", stdin);
//     ios::sync_with_stdio(false);
//     cin.tie(0), cout.tie(0);
    nogf::main();
    return 0;
}
```

---

## 作者：zhiyangfan (赞：11)

> [P5044 [IOI2018] meetings 会议](https://www.luogu.com.cn/problem/P5044)

被搬成了模拟赛题，然而我考场上想到的 $\mathcal{O}(nq)$ 暴力是单调栈计算左右贡献，就没想到继续优化的方法。（但其实单调栈也和笛卡尔树关系很大！）

考虑一个 $\mathcal{O}(n^2)$ 暴力，设 $f_{l,r}$ 表示区间 $[l,r]$ 的答案，我们可以按照区间 $\max$ 分治下两边看看在哪边举办，这样另一边的贡献就已知了：
$$f_{l,r}=\min(f_{l,x-1}+(r-x+1)h_x,f_{x+1,r}+(x-l+1)h_x)$$
其中 $x=\argmax\limits_{i=l}^r\{h_i\}$。

容易发现这种按照区间极值向两边递归的结构类似笛卡尔树，所以我们考虑对于 $h$ 数组建立笛卡尔树。

但你发现建立了之后还是没法直接转移，主要问题在于这个区间实在是太没有规律了。但观察到我们的 $\min$ 的两个参数中的 $f$，一定满足有一个端点是笛卡尔树某个节点的左右端点。由于两边的求解是独立的，我们不妨设均满足左端点在笛卡尔树上。（另一边可以把数组 `reverse` 之后再做）

然后对于一个笛卡尔树上的节点 $[l,r]$，设它对应的 $\max$ 位置为 $mid$，我们需要求解所有的 $f_{l,i},l\le i\le r$。分治之后，所有的 $f_{l,i},l\le i< mid$ 都已经求出。然后我们再向右分治，求出 $f_{mid+1,i},mid<i\le r$。容易发现 $f_{l,mid}=f_{l,mid-1}+h_{mid}$。

然后再来观察 $f_{l,i},i>mid$ 的表达式：
$$f_{l,i}=\min(f_{l,mid}+(i-mid)h_{mid},f_{mid+1,i}+(mid-l+1)h_{mid})$$
和一开始 $\rm dp$ 方程的区别就是我们把 $f_{l,mid-1}+h_{mid}$ 合并了一下，这样出现了一个我们很好算的常数。其中的 $f_{l,mid},f_{mid+1,i}$ 我们都已经求出。但问题是，如果我们还是枚举 $i$ 求解并没有做本质上的优化，时间复杂度仍然是 $\mathcal{O}(n^2)$ 的。不过我们注意到，$\min$ 的两个参数都是随着 $i$ 单调递增的，且前者每次恰好加 $h_{mid}$，而后者至多加 $h_{mid}$。这说明，这个 $\min$ 的取值是单调的！也就是说，我们可以通过二分的方式确定取前者后者的分界点。从而可以快速区间处理 $f_{l,i}$ 的求解。

以上是理论分析，接下来我们来看看具体怎么实现这个过程。首先是存 $f$ 的问题，我们需要对第二维支持较为复杂的区间操作，所以直接对第二维建立一棵线段树。我们递归计算左边右边后，第二维在 $[l,mid)$ 范围内的数表示的是 $f_{l,i}$，在 $(mid,r]$ 范围内的表示的是 $f_{mid+1,i}$。（因为每次计算的都是以这个节点左端点开始的 $f$）而 $f_{l,mid}$ 的计算是简单的。接下来我们考虑在线段树上二分，二分到一个被完全覆盖的区间时，只需要判断 $\min$ 取值的分界点在不在这个区间内，如果不在就直接更新（这里要么是区间加，要么是区间赋值一次函数），如果在就递归下去。容易发现我们只需要维护一个区间内最靠左的 $f$ 和最靠右的 $f$ 即可。而复杂度，显然相当于两次区间修改。然后把每个询问拆分成的其中一个询问挂在它左端点对应节点上即可。

然后这题就做完了，因为线段树需要支持两种不太一样的区间修改，所以 tag 打起来会有点繁琐，不过其实还好，因为区间加也可以看成加 $k=0$ 的一次函数。有一个细节，就是你需要 `reverse` 之后得到的 $mid$ 要和一开始你分询问得到的 $mid$ 相同，不然就对不上了。（如果你是用 `std::pair<int, int>` 的 ST 表来处理的话就会出这个问题）时间复杂度 $\mathcal{O}(n\log n)$。
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
const int N = 1e6 + 10; typedef long long ll; 
int a[N], q1[2][N], q2[2][N]; ll ans1[N], ans2[N], ans[N];
typedef std::pair<int, int> pii; pii mx[21][N];
std::vector<pii> qry[N];
struct SegTree
{
	#define ls(k) (k << 1)
	#define rs(k) (k << 1 | 1)
	struct node{ int l, r, typ; ll tagk, tagb, vall, valr; }h[N << 2];
	void modify(int k, ll tagk, ll tagb)
	{
		h[k].typ = 1; h[k].tagk = tagk; h[k].tagb = tagb;
		h[k].vall = h[k].l * tagk + tagb;
		h[k].valr = h[k].r * tagk + tagb;
	}
	void add(int k, ll tagk, ll tagb)
	{
		h[k].typ = h[k].typ ? h[k].typ : 2;
		h[k].tagk += tagk; h[k].tagb += tagb;
		h[k].vall += h[k].l * tagk + tagb;
		h[k].valr += h[k].r * tagk + tagb;
	}
	void pushup(int k) { h[k].vall = h[ls(k)].vall, h[k].valr = h[rs(k)].valr; }
	void pushdown(int k)
	{
		if (!h[k].typ) return ;
		if (h[k].typ == 1)
		{
			modify(ls(k), h[k].tagk, h[k].tagb);
			modify(rs(k), h[k].tagk, h[k].tagb);
		}
		else
		{
			add(ls(k), h[k].tagk, h[k].tagb);
			add(rs(k), h[k].tagk, h[k].tagb);
		}
		h[k].typ = h[k].tagk = h[k].tagb = 0;
	}
	void build(int k, int l, int r)
	{
		h[k].l = l; h[k].r = r; 
		h[k].tagk = h[k].tagb = h[k].typ = 0; 
		h[k].vall = h[k].valr = 1e15;
		if (l == r) return ;
		int mid = (l + r) >> 1; build(ls(k), l, mid); build(rs(k), mid + 1, r);
	}
	void modify(int k, int x, int y, ll _k, ll _b)
	{
		if (x <= h[k].l && h[k].r <= y) return modify(k, _k, _b);
		int mid = (h[k].l + h[k].r) >> 1; pushdown(k);
		if (x <= mid) modify(ls(k), x, y, _k, _b);
		if (mid < y) modify(rs(k), x, y, _k, _b);
		pushup(k);
	}
	void change(int k, int x, int y, ll k1, ll b1, ll b2)
	{
		if (x <= h[k].l && h[k].r <= y) 
		{
			if (h[k].l * k1 + b1 >= h[k].vall + b2) return add(k, 0, b2);
			if (h[k].r * k1 + b1 <= h[k].valr + b2) return modify(k, k1, b1);
		}	
		int mid = (h[k].l + h[k].r) >> 1; pushdown(k);
		if (x <= mid) change(ls(k), x, y, k1, b1, b2);
		if (mid < y) change(rs(k), x, y, k1, b1, b2);
		pushup(k);
	}
	ll query(int k, int p)
	{
		if (h[k].l == h[k].r) return h[k].vall;
		int mid = (h[k].l + h[k].r) >> 1; pushdown(k);
		return p <= mid ? query(ls(k), p) : query(rs(k), p);
	}
	#undef ls
	#undef rs
}sgt;
auto query = [](int l, int r) -> int
{
	int s = std::__lg(r - l + 1);
	return std::abs(std::max(mx[s][l], mx[s][r - (1 << s) + 1]).second);
};
struct CTree
{
	#define ls(k) (h[k].ls)
	#define rs(k) (h[k].rs)
	struct node{ int ls, rs; }h[N]; int rt;
	int build(int l, int r)
	{
		if (l > r) return 0;
		int mid = query(l, r);
		ls(mid) = build(l, mid - 1);
		rs(mid) = build(mid + 1, r);
		return mid;
	}
	void solve(int mid, int l, int r, bool flg)
	{
		ll now = a[mid];
		if (ls(mid)) solve(ls(mid), l, mid - 1, 0), now += sgt.query(1, mid - 1);
		if (rs(mid)) solve(rs(mid), mid + 1, r, 1);
		sgt.modify(1, mid, mid, 0, now);
		if (mid < r)
			sgt.change(1, mid + 1, r, a[mid], now - (ll)a[mid] * mid, (ll)a[mid] * (mid - l + 1));
		if (flg) for (auto [r, i] : qry[l]) ans[i] = sgt.query(1, r);
	}
	#undef ls
	#undef rs
}ct;
int main()
{
	int n, q; scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), mx[0][i] = pii(a[i], i);
	for (int j = 1; j < 21; ++j)
		for (int i = 1; i + (1 << j) - 1 <= n; ++i)
			mx[j][i] = std::max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
	for (int i = 1, l, r; i <= q; ++i)
	{
		scanf("%d%d", &l, &r); ++l; ++r;
		int x = query(l, r); 
		q1[0][i] = x + 1; q1[1][i] = r;
		q2[0][i] = l; q2[1][i] = x - 1;
		ans1[i] = (ll)a[x] * (x - l + 1);
		ans2[i] = (ll)a[x] * (r - x + 1);
	}
	for (int i = 1; i <= q; ++i) 
		if (q1[0][i] <= q1[1][i]) qry[q1[0][i]].emplace_back(q1[1][i], i);
	sgt.build(1, 1, n); ct.rt = ct.build(1, n); ct.solve(ct.rt, 1, n, 1);
	for (int i = 1; i <= q; ++i) ans1[i] += ans[i], ans[i] = 0;
	std::reverse(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) mx[0][i] = pii(a[i], -i);
	for (int j = 1; j < 21; ++j)
		for (int i = 1; i + (1 << j) - 1 <= n; ++i)
			mx[j][i] = std::max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
	for (int i = 1; i <= n; ++i) qry[i].clear();
	for (int i = 1; i <= q; ++i) 
		if (q2[0][i] <= q2[1][i])
		{
			int l = q2[0][i], r = q2[1][i];
			qry[n - r + 1].emplace_back(n - l + 1, i);
		}
	sgt.build(1, 1, n); ct.rt = ct.build(1, n); ct.solve(ct.rt, 1, n, 1);
	for (int i = 1; i <= q; ++i) ans2[i] += ans[i];
	for (int i = 1; i <= q; ++i) printf("%lld\n", std::min(ans1[i], ans2[i]));
	return 0;
}
```

---

## 作者：Autre (赞：7)

傻逼洛谷题解区，十二篇题解讲的全是同一个做法，都不是最优解法，讲的好的往往还排不到最前面，赶紧似一似。

下面做法来自 zx2003。

## 做法框架

首先区间 $[L,R]$ 的笛卡尔树结构是在区间内最大值处 $m$ 劈开，$[L,m),(m,R]$ 两部分分别作为 $m$ 的左右儿子拼起来的。而 $[L,m),(m,R]$ 分别是 $[L,n]$ 的笛卡尔树上 $m$ 的左儿子、$[1,R]$ 的笛卡尔树上 $m$ 的右儿子。所以正着倒着各做一遍，考察每个前缀和每个后缀的笛卡尔树，对每个询问分别处理将会议地点放在询问区间最大值的右侧和左侧的最小花费。

从左到右依次考察每个山 $i$，维护 $[1,i]$ 的递减单调栈，即大根笛卡尔树上，从根不断走向右儿子，经过的结点**编号**形成的序列。对于 $j\in[1,i]$ 设 $r(j)$ 为单调栈中在 $j$ 右侧的第一个位置，容易发现随着 $i$ 向右移动，如果 $r(j)$ 不变，$[1,i]$ 内的所有人全部去 $j$ 开会的代价就是以 $H_{r(j)}$ 为斜率的关于 $i$ 的同一个一次函数，设为 $f_j(i)$。

设单调栈为 $q$，因为对于所有 $j\in(q_{t-1},q_t]$，都有 $r(j)=t$，即 $f_j(i)$ 的斜率都相等，所以自然地考虑在 $q_t$ 维护这些 $j$ 中 $f_j$ 截距最小者。$i$ 向右移动时，对于每个应当从单调栈中弹出的 $q_t$，$[1,i-1]$ 中所有点都到某个 $j$ 的代价最小值可以通过 $q_t$ 处维护的一次函数直接求出，而 $i$ 到每个 $j$ 的代价均为 $H_i$。

区间 $[L,R]$ 内所有人到 $(m,R]$ 中某个位置开会的最小代价，等于 $i$ 扫描到 $R$ 时，所有 $q_t$（$t\ge r(m+1)$）上维护的一次函数在 $R$ 处的最小值（这是 $[1,R]$ 内所有人到 $(m,R]$ 中某个位置开会的最小代价），减去 $[1,m)$ 内所有人到 $m$ 开会的代价（这个值可以递推求出，且因为 $m$ 在笛卡尔树上是 $[m,R]$ 内所有点的祖先，所以 $[1,m)$ 内所有人到 $[m,R]$ 中任意一个点开会的代价都是相等的），再加上 $[L,m)$ 到 $m$ 开会的代价。

## 维护一次函数

现在需要维护初始为空的一次函数序列，在末尾 $O(n)$ 次加删，查询一段某个后缀中所有函数在 $x$ 处的取值的最小值。保证每次修改后该序列上函数的斜率递减（并非每次插入函数的斜率单调递减），查询的 $x$ 单调递增。

维护原序列的一个子序列 ${s_m}$，对于上一次询问的 $x$，满足 $s_1(x)<s_2(x)<\cdots<s_m(x)$，且若有两个函数 $f$ 在原序列中在 $g$ 之前，$f\not\in s$ 中而 $g\in s$ 中，那么 $f(x)\ge g(x)$。

插入某函数 $t$ 时，不断弹出 $s$ 末尾在 $x$ 处已经大于等于 $t$ 的元素，因为这些函数斜率大于等于 $t$，在 $x$ 处不优将来也不会优；如果 $s$ 没有被弹空，将 $s$ 末尾元素和 $t$ 两个一次函数相交的位置标记在数轴上，称为一次 beat 事件。最后将 $t$ 插入 $s$ 末尾。

查询时扫描上一次查询的 $x$ 到此次查询的 $x$ 间标记的所有 beat 事件，删除被 $t$ beat 的前驱，并将 $t$ beat 其新前驱的时刻标记在数轴上。最后查询 $s$ 中编号在查询的后缀内第一个函数在 $x$ 处的取值即可。正确性显然。

删除时如果被删除元素在 $s$ 中，则将其弹出。注意，这里为什么不会出现 $p$ beat $q$，$p$ 被弹出后查不到 $q$ 的情况呢？这里依赖原问题的性质，如果 $i$ 位置的加入导致单调栈上 $p$ 被弹出，$[1,i]$ 中所有点到新单调栈上 $i$ 处维护的一次函数的决策点，一定不劣于 $[1,i]$ 中所有点到旧单调栈上 $p$ 处维护的一次函数的决策点；而 $p$ 早在 $i$ 之前就不劣于 $q$ 了，之后也不劣于 $q$，所以如果 $q$ 被 beat，以后一定用不到 $p$。

## O(n)-O(1) RMQ

RMQ 即区间查询 $\max$。按照字长 $w=64$ 分块，块内预处理前缀、后缀 `max`，对 $\frac nw$ 个块内最大值预处理 ST 表。查询区间如果包含至少一个块间分界线，若干连续整块用 ST 表查询最大值，散块前后缀直接查询。

对每个块预处理每个前缀的 $\max$ 单调栈（每个单调栈用一个长为 $w$ 的 01 序列描述块内每个位置是否在单调栈里），若询问 $[l,r]$ 被某个块 $[L,R]$ 包含，查询 $l$ 之后第一个在 $[L,r]$ 对应的单调栈中的位置，常数次位运算和一次 `__builtin_clz/ctz` 就可以解决。

时间复杂度 $O(\frac{n\log n}w)-O(1)$，常数很小。

## 序列并查集

维护一次函数时，我们需要快速维护一个初始全 $1$ 的 $01$ 序列，每次单点把 $1$ 改成 $0$，查询某个位置前面最后一个 $1$ 和某个位置后面第一个 $1$ 的位置。**序列长度和修改次数同阶**。

将一个位置和它前面一段极长的 $0$ 对应到并查集上的一个连通块，单点修改形如合并两个相邻的区间对应的连通块，查询后继 $1$ 位置就是并查集查询连通块根。按秩合并+路径压缩复杂度为 $O(n\alpha(n,n))$。

按照字长 $w=64$ 分块，每个块对应并查集的一个元素，将极长连续全 $0$ 段对应到并查集上的一个连通块。如果一个块在某次修改后变为全 $0$ 就进行只多两次连通块合并。查询只需常数次位运算、`__builtin_clz/ctz` 和一次查询连通块根。

根据 Tarjan 的分析，总时间复杂度为

$$O\left(n\alpha\left(n,\frac nw\right)\right)=O(n\min\{i\ge1\mid A(i,w)\ge \log n\})=O(n)$$

注意，这样的并查集必须启发式合并（按秩合并或按照 size 合并）+路径压缩才能做到正确的复杂度。

还有一种不常规的写法，合并两个区间时暴力将较小区间的父亲暴力改成较大区间的父亲的根，时间复杂度为 $O(\frac{n\log n}w)$。

---

至此，我们已经线性解决了这个问题。以下这份代码截止 2024.10.9 仍然是 UOJ 和洛谷的最优解。

```C++
#include<algorithm>
#include<iostream>
#include<cstring>
#include<numeric>
#include<vector>
#include<tuple>
#define ctz __builtin_ctzll
#define clz __builtin_clzll
using ull = unsigned long long;

char bf[20000000], *bp = bf;
void inline rd(auto&x) {
	for (x=0; !isdigit(*bp); bp++);
	for (; isdigit(*bp); bp++) x = x*10+(*bp^48);
}
const int N = 7.5e5, LG = 17;
int n, m, tp, o[N], a[N], l[N], r[N], mx[N], q[N], p[N], bl[N], br[N];
unsigned long long b[N], ms[N+1], pr[N], sf[N+1], st[LG][N/64];
long long ans[N], c[N], f[N];
std::vector<int>rg[N+1];
std::vector<std::tuple<int, int, int>>qr[N];
bool inline ck(int u) { return ms[u>>6]>>(u&63)&1; }
void inline gf(int&u) { while (p[u] != u) u = p[u] = p[p[u]]; }
int tl(int u) {
	if (!~u) return -1;
	if (auto x=ms[u>>6]&-1ull>>(~u&63)) return (u|63)^clz(x);
	if (!(u>>=6)) return -1;
	if (ms[--u]) return u<<6|63^clz(ms[u]);
	return gf(u), ~bl[u] ? bl[u]<<6|63^clz(ms[bl[u]]) : -1;
}
int tr(int u) {
	if (auto x=ms[u>>6]&-1ull<<(u&63)) return u&~63|ctz(x);
	if (ms[u=(u>>6)+1]) return u<<6|ctz(ms[u]);
	return gf(u), br[u]<<6|ctz(ms[br[u]]);
}
void md(int u) {
	if (ms[u>>6]&=~(1ull<<(u&63))) return;
	auto mg = [](int x, int y) {
		if (gf(x), gf(y), br[x]-bl[x] <= br[y]-bl[y])
			p[x] = y, bl[y] = bl[x];
		else p[y] = x, br[x] = br[y];
	};
	u >>= 6, p[u] = u, bl[u] = u-1, br[u] = u+1;
	if (u && !ms[u-1]) mg(u-1, u);
	if (u+1<n>>6 && !ms[u+1]) mg(u, u+1);
}
void sv() {
	for (int i=0, j=0, t; i<n; qr[i].clear(), rg[i].clear(), i++) {
		for (c[i]=1e18; ~tp && b[q[tp]]<=b[i]; tp--)
			if (c[i] = std::min(c[i], (a[q[tp]]-a[i])*(i-1ll)+c[q[tp]]), ck(q[tp])) md(q[tp]);
		auto upd = [&](int x) { int y = x;
			while (~(y=tl(y-1)) && 1ll*(a[x]-a[y])*i+c[x]-c[y]<=0) md(y);
			if (~y && a[x]!=a[y]) rg[std::min((c[y]-c[x])/(a[x]-a[y])+1, 1ll*n)].push_back(x);
		};
		c[i] = std::min(c[i], f[i]=~tp?f[q[tp]]+1ll*q[tp]*a[q[tp]]-1ll*a[i]*q[tp]:a[i]);
		for (upd(q[++tp]=i); int x : rg[i]) if (ck(x)) upd(x);
		for (; j<m && r[o[j]]==i; j++) if (mx[o[j]] < i) t = tr(mx[o[j]]+1),
			ans[o[j]] = std::min(ans[o[j]], 1ll*a[t]*i-a[mx[o[j]]]*(l[o[j]]-1ll)+c[t]-f[mx[o[j]]]);
	}
}
int main() {
	fread(bf, 1, sizeof bf, stdin), rd(n), rd(m);
	for (int i=0; i<n; i++) rd(a[i]), b[i] = 1ull*a[i]<<32|i;
	for (int i=0; i<n; i++) pr[i] = i&63?std::max(pr[i-1], b[i]):b[i];
	for (int i=n; i--; sf[i] = ~i&63?std::max(sf[i+1], b[i]):b[i], ms[i]|=1ull<<(i&63))
		for (ms[i]=~i&63?ms[i+1]:0; ms[i] && a[ctz(ms[i])+(i&~63)]<a[i];) ms[i] -= ms[i]&-ms[i];
	for (int i=0; i<n>>6; i++) st[0][i] = sf[i<<6];
	for (int i=1, j; 1<<i<=n>>6; i++) for (j=0; j+(1<<i)<=n>>6; j++)
		st[i][j] = std::max(st[i-1][j], st[i-1][j+(1<<i-1)]);
	for (int i=0, u, v, t; i<m; i++) if (rd(l[i]), rd(r[i]), (u=l[i]+64>>6)<(v=r[i]>>6))
		t = std::__lg(v-u), mx[i] = std::max({sf[l[i]], st[t][u], st[t][v-(1<<t)], pr[r[i]]});
	else mx[i] = u==v?std::max(sf[l[i]], pr[r[i]]):r[i]-clz(ms[l[i]]<<(~r[i]&63));
	for (int i=0; i<m; i++) ans[i] = a[mx[i]]*(r[i]-l[i]+1ll);
	std::iota(o, o+m, 0), std::sort(o, o+m, [](int i, int j){return r[i]<r[j];});
	memset(ms, -1, n+8>>3), tp = -1, sv(), std::reverse(a, a+n), std::reverse(b, b+n);
	for (int i=0; i<m; i++) l[i] = n-l[i]-1, r[i] = n-r[i]-1, mx[i] = n-mx[i]-1, std::swap(l[i], r[i]);
	std::sort(o, o+m, [](int i, int j){return r[i]<r[j];}), memset(ms, -1, n+8>>3), tp = -1, sv();
	for (int i=0; i<m; i++) std::cout << ans[i] << '\n';
}
```

---

## 作者：JhinLZH (赞：6)

安利一下博客[我的博客](https://www.cnblogs.com/Khada-Jhin/)

还是按照编号都从1开始讲。

可以发现对于一个询问如果确定了开会地址那么答案只和每个点到开会点区间最大值有关。

而题目又没有强制在线，我们可以按区间最大值来分治。

我们设对于区间[l,r]的答案是ans(l,r)，区间中的最大值位于mid处(即h[mid]是区间最大值)。

那么显然答案选定的开会点一定在mid的左侧或右侧，ans(l,r)=min{ans(l,mid-1)+h[mid]*(r-mid+1),ans(mid+1,r)+h[mid]*(mid-l+1)}。

即如果开会点在mid左边那么mid及右边所有点到开会点的代价都是h[mid]，如果开会点在mid右边那么mid及左边所有点到开会点的代价都是h[mid]。

因此，ans(l,r)要由ans(l,mid-1)与ans(mid+1,r)合并而来。

那么我们可以确定一个大致思路：找出当前区间最大值位置然后分治左右区间，在得出左右区间的答案之后再处理询问区间最大值是当前区间最大值的询问，然后再递归回上一些层。

 区间最大值很好求，用ST表维护一下即可，那么对于每个区间的ans怎么维护？

对于左端点为l的区间难道要同时维护出ans(l,l),ans(l,l+1),ans(l,l+2)……吗？

显然并不需要，我们发现对于每一次递归的区间[l,r]，需要用到左端点为l的ans只有ans(l,mid-1)和ans(l,r)。

其中前者对应处理当前层询问前递归合并上来的答案，后者则对应处理完当前层询问后需要递归合并上去的答案。

也就是说对于一个点x，在同一时刻只需要维护它作为一个区间左端点和右端点时这两个答案。

那么我们就可以用线段树来实现，对于线段树上每个叶子结点维护lm和rm两个信息，分别表示这个点是区间左/右端点时的区间答案。

因为我们不知道对于当前递归区间[l,r]递归回上一层时是在上一层最大值的左边还是右边，所以要用两棵线段树分别维护这两种情况。

总结一下大体思路：对于当前区间找到区间最大值位置并递归左右子区间，回溯时处理当前区间需要处理的询问，对于每个ans(x,mid-1)(l<=x<=mid-1)更新为ans(x,r)；对于每个ans(mid+1,x)(mid+1<=x<=r)更新为ans(l,x)。

因为每个点被当做区间最大值一次且每个询问被处理一次，所以时间复杂度是O((n+q)logn)。

如果还是不太明白可以看代码的具体实现。

```
#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<stack>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long 
using namespace std;
int n,q;
int h[750010];
int ql[750010];
int qr[750010];
ll res[750010];
int f[750010][21];
int g[750010][21];
int ln[750010];
vector<int>pos[750010];
struct miku
{
    ll lm[4000010];
    ll rm[4000010];
    ll k[4000010];
    ll b[4000010];
    int a[4000010];
    void cover(int rt)
    {
        a[rt]=1;
        lm[rt]=rm[rt]=k[rt]=b[rt]=0;
    }
    void add(int rt,int l,int r,ll K,ll B)
    {
        k[rt]+=K;
        b[rt]+=B;
        lm[rt]+=K*l+B;
        rm[rt]+=K*r+B;
    }
    void pushup(int rt)
    {
        lm[rt]=lm[rt<<1];
        rm[rt]=rm[rt<<1|1];
    }
    void pushdown(int rt,int l,int r)
    {
        int mid=(l+r)>>1;
        if(a[rt])
        {
            a[rt]=0;
            cover(rt<<1);
            cover(rt<<1|1);
        }
        if(k[rt]||b[rt])
        {
            add(rt<<1,l,mid,k[rt],b[rt]);
            add(rt<<1|1,mid+1,r,k[rt],b[rt]);
            k[rt]=b[rt]=0;
        }
    }
    void change(int rt,int l,int r,int L,int R,ll val)
    {
        if(L<=l&&r<=R)
        {
            add(rt,l,r,0,val);
            return ;
        }
        int mid=(l+r)>>1;
        pushdown(rt,l,r);
        if(L<=mid)
        {
            change(rt<<1,l,mid,L,R,val);
        }
        if(R>mid)
        {
            change(rt<<1|1,mid+1,r,L,R,val);
        }
        pushup(rt);
    }
    void merge(int rt,int l,int r,int L,int R,ll K,ll B)
    {
        if(L<=l&&r<=R)
        {
            ll LV=K*l+B;
            ll RV=K*r+B;
            if(LV>=lm[rt]&&RV>=rm[rt])
            {
                return ;
            }
            if(LV<=lm[rt]&&RV<=rm[rt])
            {
                cover(rt);
                add(rt,l,r,K,B);
                return ;
            }
        }
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(L<=mid)
        {
            merge(rt<<1,l,mid,L,R,K,B);
        }
        if(R>mid)
        {
            merge(rt<<1|1,mid+1,r,L,R,K,B);
        }
        pushup(rt);
    }
    ll query_left(int rt,int l,int r,int x)
    {
        if(l==r)
        {
            return lm[rt];
        }
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(x<=mid)
        {
            return query_left(rt<<1,l,mid,x);
        }
        else
        {
            return query_left(rt<<1|1,mid+1,r,x);
        }
    }
    ll query_right(int rt,int l,int r,int x)
    {
        if(l==r)
        {
            return rm[rt];
        }
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(x<=mid)
        {
            return query_right(rt<<1,l,mid,x);
        }
        else
        {
            return query_right(rt<<1|1,mid+1,r,x);
        }
    }
}s,t;
int cmp(int l,int r)
{
    int len=ln[r-l+1];
    if(f[l][len]>=f[r-(1<<len)+1][len])
    {
        return g[l][len];
    }
    else
    {
        return g[r-(1<<len)+1][len];
    }
}
void solve(int l,int r)
{
    if(l>r)
    {
        return ;
    }
    int mid=cmp(l,r);
    solve(l,mid-1);
    solve(mid+1,r);
    int len=pos[mid].size();
    for(int i=0;i<len;i++)
    {   
        int now=pos[mid][i];
        res[now]=1ll*h[mid]*(qr[now]-ql[now]+1);
        if(ql[now]<mid)
        {
            res[now]=min(res[now],s.query_left(1,1,n,ql[now])+1ll*h[mid]*(qr[now]-mid+1));
        }
        if(qr[now]>mid)
        {
            res[now]=min(res[now],t.query_right(1,1,n,qr[now])+1ll*h[mid]*(mid-ql[now]+1));
        }
    }
    ll sx=h[mid];
    ll tx=h[mid];
    if(l<mid)
    {
        tx+=t.query_right(1,1,n,mid-1);
    }
    if(r>mid)
    {
        sx+=s.query_left(1,1,n,mid+1);
    }
    s.change(1,1,n,mid,mid,sx);
    t.change(1,1,n,mid,mid,tx);
    if(l<mid)
    {
        s.change(1,1,n,l,mid-1,1ll*h[mid]*(r-mid+1));
        s.merge(1,1,n,l,mid-1,-1ll*h[mid],sx+1ll*mid*h[mid]);
    }
    if(r>mid)
    {
        t.change(1,1,n,mid+1,r,1ll*h[mid]*(mid-l+1));
        t.merge(1,1,n,mid+1,r,1ll*h[mid],tx-1ll*mid*h[mid]);
    }
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&h[i]);
        f[i][0]=h[i];
        g[i][0]=i;
    }
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&ql[i],&qr[i]);
        ql[i]++;
        qr[i]++;
    }
    for(int i=2;i<=n;i++)
    {
        ln[i]=ln[i>>1]+1;
    }
    for(int j=1;j<=20;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(i+(1<<j)-1>n)
            {
                break;
            }
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
            if(f[i][j]==f[i][j-1])
            {
                g[i][j]=g[i][j-1];
            }
            else
            {
                g[i][j]=g[i+(1<<(j-1))][j-1];
            }
        }
    }
    for(int i=1;i<=q;i++)
    {
        pos[cmp(ql[i],qr[i])].push_back(i);
    }
    solve(1,n);
    for(int i=1;i<=q;i++)
    {
        printf("%lld\n",res[i]);
    }
}
```


---

## 作者：AzusaCat (赞：5)

给定长为 $n$ 的序列 $h$，有 $q$ 次询问，每次询问在 $[l,r]$ 内找一个点 $x$，使得 $[l,r]$ 内每个点到 $x$ 之间最大值的和（即 $\sum\limits_{i=l}^x\max\limits_{j=i}^xh_j+\sum\limits_{i=x+1}^r\max\limits_{j=x}^ih_j$）最小。$n,q\leqslant 750000,h\leqslant 10^9$ 。

发现这个东西没有什么一般性结论，所以我们考虑dp求解。

设 $f[l,r]$ 为 $[l,r]$ 的答案。首先我们有一个结论，当区间内值不唯一时，区间的最大值的位置一定不为最优解（因为这样每一个元素的贡献都是最大值）。所以我们可以得到转移方程：

$$
f[l,r]=\min(f[l,mid-1]+(r-mid+1)h[mid],f[mid+1,r]+(mid-l+1)h[mid])
$$
其中 $mid$ 是最大值的位置（有多个时任何一个都可以）。即我们枚举最优解的位置在最大值的左边/右边。这样就有一个 $n^2$ 的朴素算法。

我们发现转移方程和区间内的最大值有关系，所以我们尝试用笛卡尔树来优化dp。我们对序列建权值为大根堆的笛卡尔树，并且对每个 $[l,r]$ 的询问暴力展开一次，即求 $f[l,mid-1]$ 和 $f[mid+1,r]$。这时我们发现对于每一个 $f[l,mid-1]$ 的询问，都可以找到一个笛卡尔树中的点 $c$，使得 $c$ 对应的右端点也为 $mid-1$（证明可以考虑 $mid-1$ 和 $mid$ 的位置关系）。同理对于每个 $f[mid+1,r]$ 的询问，都可以找到笛卡尔树中左端点为 $mid+1$ 的点（如果不展开不一定能找到这个点，这就是为什么要展开的原因）。明显这两类询问是类似的，所以我们只考虑处理 $f[mid+1,r]$ 这一类，对于 $f[l,mid-1]$ 这一类可以反转数组和询问以后求得。

根据上面的结论，我们发现对于笛卡尔树中的每一个点，如果它对应的区间是 $[l,r]$，我们只需要求出 $f[l,l],f[l,l+1]\dots f[l,r]$ 的值。具体地，如果这个节点对应的点为 $mid$，我们先递归左子树和右子树求出 $f[l,l]\dots f[l,mid-1]$ 和 $f[mid+1,mid+1]\dots f[mid+1,r]$ 然后考虑推出 $f[l,mid]\dots f[l,r]$。

让我们再看一遍转移方程：
$$
f[l,r]=\min(f[l,mid-1]+(r-mid+1)h[mid],f[mid+1,r]+(mid-l+1)h[mid])
$$
左边部分随着 $r$ 的增加，每次增加 $h[mid]$，右边部分随着 $r$ 的增加每次增加量都小于等于 $h[mid]$（因为 $h[mid]$ 是区间内最大的值了）所以说如果某一刻左边的值大于了右边，那么再往后左边的值都会大于右边。

所以我们可以维护一棵线段树，当我们在笛卡尔树上dfs完某个点的时候，线段树上位置 $r$ 存的东西就是 $f[l,r]$ （$l$ 是dfs到的节点代表区间的左端点）。我们在线段树上二分来找到第一个左边>右边的位置，设为 $pos$。那么对于小于 $pos$ 的位置，相当于先区间覆盖一次再区间加等差数列（换句话说就是用一次函数覆盖）；右边的部分就是一个区间加了。

所以我们的线段树需要支持区间覆盖和区间加等差数列（加一个数也是等差数列啦）。对于询问，找到我们所说的那个点 $c$ 然后把它丢进对应的桶里，dfs完一个点的时候计算所有询问的答案。

至于实现我们并不需要显式地建出笛卡尔树，我们开一个st表然后dfs的时候只需要记录当前区间，递归左右儿子就在st表里查询区间最大值的位置就可以了。至于如何把询问挂到节点上，我们只需要把左端点相同的询问放到一个桶里，当dfs到一个点时，如果它是父亲的右儿子或者是根节点，那么它就是所有与它 $l$ 相同的节点中 $r$ 最大的那个，所以只需要在这类点回答询问就好了。

代码：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
struct query{int l,r;ll ans[2];}c[750005];
vector<int>v[3000005];
int now,n,f[2000005][20],lg[750005];
ll h[750005];
int merge(int x,int y)
{
    if(h[x]!=h[y])return h[x]>h[y]?x:y;
    if(now)return x<y?x:y;
    return x>y?x:y;
}
int ask(int x,int y)
{
    int t=lg[y-x+1];
    return merge(f[x][t],f[y-(1<<t)+1][t]);
}
struct Segment_Tree
{
    ll tree[3000005],cov[3000005],addk[3000005],addb[3000005];
    //加一个(x-a)*c+d的等差数列
    void init()
    {
        memset(tree,0,sizeof(tree));
        memset(cov,0x80,sizeof(cov));
        memset(addk,0,sizeof(addk));
        memset(addb,0,sizeof(addb));
    }
    void pushdown(int l,int r,int x)
    {
        if(cov[x]!=-2139062144)
        {
            tree[x]=cov[x];
            if(l!=r)cov[x*2]=cov[x],cov[x*2+1]=cov[x],addk[x*2]=addb[x*2]=addk[x*2+1]=addb[x*2+1]=0;
            cov[x]=-2139062144;
        }
        if(addk[x]||addb[x])
        {
            tree[x]+=addb[x]+addk[x]*(r-l);
            if(l!=r)
            {
                int mid=(l+r)>>1;
                addk[x*2]+=addk[x],addb[x*2]+=addb[x];
                addk[x*2+1]+=addk[x],addb[x*2+1]+=addb[x]+(mid+1-l)*addk[x];
            }
            addk[x]=addb[x]=0;
        }
    }
    void add(int l,int r,int x,int a,int b,ll c,ll d)//a恰好加上d
    {
        pushdown(l,r,x);
        if(l>=a&&r<=b)
        {
            addk[x]+=c,addb[x]+=(l-a)*c+d;
            return;
        }
        int mid=(l+r)>>1;
        if(a<=mid)add(l,mid,x*2,a,b,c,d);
        if(b>mid)add(mid+1,r,x*2+1,a,b,c,d);
        pushdown(l,mid,x*2),pushdown(mid+1,r,x*2+1);
        tree[x]=tree[x*2+1];
    }
    void modify(int l,int r,int x,int a,int b,ll c)
    {
        pushdown(l,r,x);
        if(l>=a&&r<=b)
        {
            cov[x]=c;
            addk[x]=addb[x]=0;
            return;
        }
        int mid=(l+r)>>1;
        if(a<=mid)modify(l,mid,x*2,a,b,c);
        if(b>mid)modify(mid+1,r,x*2+1,a,b,c);
        pushdown(l,mid,x*2),pushdown(mid+1,r,x*2+1);
        tree[x]=tree[x*2+1];
    }
    ll query(int l,int r,int x,int a)
    {
        pushdown(l,r,x);
        if(l==r)return tree[x];
        int mid=(l+r)>>1;
        if(a<=mid)return query(l,mid,x*2,a);
        else return query(mid+1,r,x*2+1,a);
    }
    int get(int l,int r,int x,int a,int b,ll c,ll d,int e)
    {
        pushdown(l,r,x);
        if(l==r)return l;
        int mid=(l+r)>>1;
        if(a<=mid&&b>mid)
        {
            pushdown(l,mid,x*2);
            if(c+(mid-(a-1)+1)*d>tree[x*2]+((a-1)-e+1)*d)
                return get(l,mid,x*2,a,b,c,d,e);
            return get(mid+1,r,x*2+1,a,b,c,d,e);
        }
        else if(a<=mid)return get(l,mid,x*2,a,b,c,d,e);
        return get(mid+1,r,x*2+1,a,b,c,d,e);
    }
    ll operator [](int x){return query(1,n,1,x);}
}T;
void dfs(int l,int r,bool s)
{
    int mid=ask(l,r);
    if(l<mid)
    {
        dfs(l,mid-1,0);
        T.modify(1,n,1,mid,mid,T[mid-1]+h[mid]);
    }
    else T.modify(1,n,1,mid,mid,h[mid]);
    if(r>mid)
    {
        dfs(mid+1,r,1);
        int t;
        ll tmp=(l<mid)?T[mid-1]:0;
        if(T[r]+(mid-l+1)*h[mid]>=tmp+(r-mid+1)*h[mid])
            t=r+1;
        else t=T.get(1,n,1,mid+1,r,tmp,h[mid],l);
        //t为第一个使得左>右的位置
        if(t!=mid+1)
        {
            T.modify(1,n,1,mid+1,t-1,tmp);
            T.add(1,n,1,mid+1,t-1,h[mid],2*h[mid]);
        }
        if(t!=r+1)T.add(1,n,1,t,r,0,(mid-l+1)*h[mid]);
    }
    if(s)
    {
        for(int i=0;i<v[l].size();i++)
            c[v[l][i]].ans[now]=T[c[v[l][i]].r];
    }
}
int main()
{
    int q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%lld",&h[i]),f[i][0]=i;
    for(int i=1;i<=q;i++)scanf("%d%d",&c[i].l,&c[i].r),c[i].l++,c[i].r++;
    again:
    for(int i=1;i<=n;i++)v[i].clear();
    T.init();
    for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
    for(int k=1;k<=19;k++)
        for(int i=1;i<=n;i++)
            f[i][k]=merge(f[i][k-1],f[i+(1<<(k-1))][k-1]);
    for(int i=1;i<=q;i++)
    {
        int t=ask(c[i].l,c[i].r);
        if(t!=c[i].r)v[t+1].push_back(i);
    }
    
    dfs(1,n,1);
    if(!now)
    {
        now=1;
        reverse(h+1,h+n+1);
        for(int i=1;i<=q;i++)
            c[i].l=n-c[i].l+1,c[i].r=n-c[i].r+1,swap(c[i].l,c[i].r);
        goto again;
    }
    else
        for(int i=1;i<=q;i++)
        {
            int t=ask(c[i].l,c[i].r);
            printf("%lld\n",min(c[i].ans[0]+(c[i].r-t+1)*h[t],c[i].ans[1]+(t-c[i].l+1)*h[t]));
        }
    return 0;
}
```



---

## 作者：yinianxingkong (赞：4)

# [[IOI2018] meetings 会议](https://www.luogu.com.cn/problem/P5044)

# 前言

你要写笛卡尔树，你就不能只写笛卡尔树。你需要先模一遍笛卡尔的老祖宗 [@1234567s](https://www.luogu.com.cn/user/549001) 并祝他儿童节快乐，否则会导致调三个小时以上，所以 orz！

# 解法分析

题意：查询区间内选一个点使得每个点到它的区间的最大值的和最小，求最小值。

问题与最值相关，不难想到按最值分治

令 $x$ 为 $[l,r]$ 间最大值的下标，有：
$$
f_{l,r}=\min(f_{l,x-1}+(r-x+1)\times h_x,f_{x+1,r}+(x-l+1)\times h_x)
$$
预处理出数组，复杂度 $O(n^2)$。

最值分治，容易想到笛卡尔树。复杂的难以拼接的信息让我们放弃了区间笛卡尔树的想法。

难道我们没办法将区间表示在笛卡尔树上了吗？这里我们先将区间按上面的方程拆一层，求 $f_{l,x-1}$ 和 $f_{x+1,r}$，前者翻转后归类为后者。这时我们发现一个性质，每个 $[x+1,r]$ 的区间左边一定是一个比整个区间都大的数，放到笛卡尔树上考虑，也就是 $[x+1,r]$ 一定在 $x$ 为根的右子树内，而且这棵子树的左端点为 $x+1$。

这个时候就比较显然了。对于每个笛卡尔树的子树，我们只需要求出前缀区间的值就可以拼接出答案。这个显然存不下，把询问挂在结点上即可，难点在转移，即计算左子树对右子树的影响。

容易发现随着右端点的增长，一定会是前一段答案从左子树转移，后一段答案从右子树转移。那么左边就是区间覆盖一次函数，右边就是区间加。使用线段树即可。

That's all.

---

## 作者：Logey (赞：4)

首先需要考虑复杂度为 $O(n^2)$ 的暴力动态规划。

设 $f_{l, r}$表示询问 $[l, r]$ 的答案。

转移的时候，需要观察到区间里的最大值作为关键点一定是不优的。所以有转移方程：

$$f_{l, r} = \min \lbrace f_{l, p -1} + a_p \times  (r - p + 1) , f_{p + 1, r} + a_p \times (p - l + 1) \rbrace$$

$p$ 为区间最大值所在的位置。含义就是关键点放在 $p$ 两边取个最优。

进一步优化需要使用到笛卡尔树。因为转移需要用到最值的位置。

先手动把一个询问拆成两半，相当于求 $f_{l, p - 1}, f_{p + 1, r}$，然后可以直接合并起来得到答案。同时 $p-1, p+1$ 一定是笛卡尔树上的端点，所以可以把询问都离线下来挂到笛卡尔树的结点上。

那么问题就变成了对于笛卡尔树上的一个结点 $[l, r]$，求 $f_{l, i}, i \in [l, r]$。

我们可以分治解决这个子问题，先求出两个儿子的信息。

也就是已知 $f_{l, i}, i \in [l, p - 1]$ 和 $f_{p + 1, i}, i \in [p + 1, r]$ 。

再观察一下上面给出的转移方程，左边一项相当于区间对一次函数取最小值，右边相当于直接区间加，考虑用线段树维护，但是问题在于直接维护复杂度是线性的。

那么现在再观察一下性质，$f_{p+1, r}$ 的每移动一位，增量一定不超过 $a_p$，因为 $a_p$ 是区间最大值。所以当右边一项更优的时候，往右走一定都是更优的，那么就可以用线段树维护了，在线段树上二分即可。

再来总结一下：

离线询问，挂到每个笛卡尔树的区间上，用线段树维护区间信息，需要支持**区间加**，**区间对一次函数取最小值**，单点查询。时间复杂度为 $O((n+q)\log n)$。

---

## 作者：Fuyuki (赞：4)

记询问区间 $[l,r]$ 的答案为 $f_{l,r}$，设区间 $[l,r]$ 内的最大值为 $a_p$，考虑如果举办地点在 $p$ 的一侧的话，另一侧的所有位置花费的代价都将是 $a_p$，所以有：

$f_{l,r}=\min\{f_{l,p-1}+(r-p+1)\times a_p,(p-l+1)\times a_p+f_{p+1,r}\}$

可以把这个过程看做是从最值处划分合并两个区间，而最值分治又可以和笛卡尔树联系起来。

通过预处理出笛卡尔树上每个子树的答案，在将询问的两个端点在笛卡尔树上跳 lca 的过程中合并区间的答案，就可以在 $O(\text{笛卡尔树树高})$ 的时间内处理每次的询问，可以得到 $60$ 分。

这个方向没有什么优化的空间，因为合并两个区间的操作并没有结合律，所以也不可能用倍增之类的方法处理。

换一个思路，跳 lca 的暴力过程实际上是在求出每个询问到区间最值处的答案，也就是这个点在笛卡尔树上两个儿子的前缀和后缀的答案。

假设已经求出了 $[l,p-1],[p+1,r]$ 的每个前缀的答案，只需要考虑在每个 $[p+1,i](i\in[p,r])$ 前面加上 $[l,p-1]$ 这一段。

转移方程相同，即：

$f_{l,i}=\min\{f_{l,p-1}+(i-p+1)\times a_p,(p-l+1)\times a_p+f_{p+1,i}\}$

设 $c=(1-p)\times a_p,d=(p-l+1)\times a_p$，就有：

$f_{l,i}=\min\{i\times a_p+c,f_{p+1,i}+d\}$。

相当于转移是一次加法和对一个一次函数取 $\min$。

又因为一定有 $f_{p+1,i+1}-f_{p+1,i}\leq a_p$，所以该一次函数与原函数的交点最多只有一个，所以可以直接用类似李超树的办法在线段树上覆盖线段，复杂度是 $O(nlogn)$ 的。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define I inline int
#define V inline void
#define ll long long int
#define isnum(ch) ('0'<=ch&&ch<='9')
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define gc (_op==_ed&&(_ed=(_op=_buf)+fread(_buf,1,100000,stdin),_op==_ed)?EOF:*_op++)
char _buf[100000],*_op(_buf),*_ed(_buf);
I getint(){
	int _s=0;char _ch=gc;
	while(!isnum(_ch))_ch=gc;
	while(isnum(_ch))_s=_s*10+_ch-48,_ch=gc;
	return _s;
}
const int N=75e4+1;
ll ans[N];
vector<int>q[N];
int n,m,a[N],ql[N],qr[N],lg[N],st[20][N];
#define lc p<<1
#define rc lc|1
#define root 1,1,n
#define lson lc,L,mid
#define rson rc,mid+1,R
struct seg{
	struct node{
		int k;ll b;
		V clear(){k=b=0;}
		I empty()const{return !k;}
		ll val(int x)const{return 1ll*k*x+b;}
	};
	struct ele{
		node tag;
		ll lval,rval,dlt;
		V add(ll x){lval+=x,rval+=x,dlt+=x,tag.b+=x;}
		V cha(const node&x,int L,int R){lval=x.val(L),rval=x.val(R),tag=x,dlt=0;}
	}t[N<<2];
	V upd(int p){t[p].lval=t[lc].lval,t[p].rval=t[rc].rval;}
	V psd(int p,int L,int R){
		t[lc].add(t[p].dlt),t[rc].add(t[p].dlt),t[p].dlt=0;
		if(t[p].tag.empty())return;int mid=L+R>>1;
		t[lc].cha(t[p].tag,L,mid),t[rc].cha(t[p].tag,mid+1,R),t[p].tag.clear();
	}
	V modify(int p,int L,int R,int l,int r,const node&x){
		if(R<l||L>r)return;
		int mid=L+R>>1;
		if(l<=L&&R<=r)
			switch((t[p].lval>x.val(L))+(t[p].rval>x.val(R))){
				case 1:return psd(p,L,R),modify(lson,l,r,x),modify(rson,l,r,x);
				case 2:return t[p].cha(x,L,R);
			}
		else psd(p,L,R),modify(lson,l,r,x),modify(rson,l,r,x),upd(p);
	}
	V modify(int p,int L,int R,int l,int r,ll x){
		if(R<l||L>r)return;
		if(l<=L&&R<=r)return t[p].add(x);
		int mid=L+R>>1;
		modify(lson,l,r,x),modify(rson,l,r,x),upd(p);
	}
	ll ask(int p,int L,int R,int x){
		if(L==R)return t[p].lval;
		int mid=L+R>>1;psd(p,L,R);
		return(x<=mid)?ask(lson,x):ask(rson,x);
	}
	ll operator[](const int&x){return ask(root,x);}
}T1,T2;
V input(){
	n=getint(),m=getint();
	FOR(i,1,n)a[i]=getint(),st[0][i]=i;
	FOR(i,1,m)ql[i]=getint()+1,qr[i]=getint()+1;
}
I low(int x,int y){return a[x]>=a[y]?x:y;}
I ask(int l,int r){
	int p=lg[r-l+1];
	return low(st[p][l],st[p][r-(1<<p)+1]);
}
V init(){
	FOR(i,2,n)lg[i]=lg[i>>1]+1;
	FOR(i,0,18)FOR(j,1,n-(1<<i))
		st[i+1][j]=low(st[i][j],st[i][j+(1<<i)]);
	FOR(i,1,m)q[ask(ql[i],qr[i])].push_back(i);
}
ll dfs(int l,int r){
	if(l>r)return 0ll;
	int p=ask(l,r);
	ll szl,szr,wl,wr,cl,cr;
	cl=dfs(l,p-1),cr=dfs(p+1,r);
	for(int v:q[p]){
		szl=p-ql[v]+1,szr=qr[v]-p+1,wl=T1[ql[v]],wr=T2[qr[v]];
		ans[v]=min(szl*a[p]+wr,wl+szr*a[p]);
	}
	szl=p-l+1,szr=r-p+1;
	T1.modify(root,l,p,szr*a[p]);
	T2.modify(root,p,r,szl*a[p]);
	T1.modify(root,l,p,(seg::node){-a[p],cr+(1ll+p)*a[p]});
	T2.modify(root,p,r,(seg::node){a[p],cl+(1ll-p)*a[p]});
	return min(szl*a[p]+cr,cl+szr*a[p]);
}
V work(){
	dfs(1,n);
	FOR(i,1,m)cout<<ans[i]<<'\n';
}
int main(){
	input();
	init();
	work();
	return 0;
}
```

---

## 作者：Acoipp (赞：3)

## 题意

题目说得很清楚，这里就不过多赘述了。

## 分析

设 $dp_{l,r}$ 表示最终答案，我们就只需要每次询问输出 $dp_{l,r}$ 就可以了。

但是我们不可能把 $dp_{l,r}$ 全部处理出来，所以我们需要考虑转移：

设 $p$ 满足 $a_p = \max_{l \le i \le r} a_i$，则 
$$dp_{l,r}=\min(dp_{l,p-1}+(r-p+1)a_p,dp_{p+1,r}+(p-l+1)a_p,(r-l+1)a_p)$$

容易得知，$dp_{l,p-1}$ 和 $dp_{p+1,r}$ 中 $p-1,p+1$ 一定是笛卡尔树上某个节点代表区间的左右端点之一。

所以我们考虑把所有询问离线下来，在笛卡尔树上处理出每个询问的 $dp_{l,p-1}$ 和 $dp_{p+1,r}$。

考虑 $dp_{l,p-1}$ 怎么求（$dp_{p+1,r}$ 同理）。

- 若这是一个空区间，则答案为 $0$。
- 若这不是一个空区间，在笛卡尔树上考虑。

我们着重处理第二种情况。

首先，我们需要找到哪个顶点代表的区间是右端点为 $p-1$，左端点小于等于 $l$，这很简单，即 $p$ 在笛卡尔树上的左子节点。（如果区间 $[l,p-1]$ 为空，则没有左子节点）。

然后我们对于所有笛卡尔树上的节点，处理出所有 $dp_{i,r}(l \le i \le r)$，$[l,r]$ 表示 $i$ 号节点表示的区间。

因为这是一个树上问题，考虑已知两个子节点的信息，合并出父亲节点的信息。

边界条件，若区间为空，答案为 $0$，若区间长度为 $1$，答案为 $a_i$。

设两个子节点代表的区间是：$[l_1,r_1],[l_2,r_2]$，那么我们已知 $dp_{i,r_1}(l_1 \le i \le r_1),dp_{i,r_2}(l_2 \le i \le r_2)$。

我们需要推导出来 $dp_{i,r_2}(l_1 \le i \le r_2)$。

- 对于 $l_2 \le i \le r_2$，答案就是右子节点的答案。
- 对于 $i=r_1+1=l_2-1$，答案就是 $\min((r_2-l_2+2)a_i,dp_{l_2,r_2}+a_i)$。
- 对于 $l_1 \le i \le r_1$，答案需要推一下式子。

处理第三种情况：

每个 $l_1 \le i \le r_1$，要么在 $p$ 左边汇合，要么在 $p$ 右边汇合，要么在 $p$ 汇合，所以 DP 公式同上：

$dp_{i,r_2}=\min((r_2-i+1)a_p,dp_{i,r_1}+(r_2-p+1)a_p,dp_{l_2,r_2}+(p-i+1)a_p)(l_1 \le i \le r_1)$

对于 $\min$ 函数中的第一项，我们很明确知道它不优，所以我们只需要考虑第二项和第三项的大小。

其中 $dp_{i,r_1}$ 和 $(p-i+1)a_p$ 是变量，而 $(r_2-p+1)a_p$ 与 $dp_{l_2,r_2}$ 是常量。

注意到对于第二个变量，每次 $i$ 左移一位时，会增加 $a_p$，但是 $dp_{i,r_1}$ 最多增加 $\max_{l_1 \le j \le r_1} a_j$，而这个是小于 $a_p$，所以它具有决策单调性，即有一个分界点 $pos$，使得 $dp_{l_1 \sim pos,r_2}$ 选择 $dp_{i,r_1}+(r_2-p+1)a_p$，而 $dp_{pos+1 \sim r_1,r_2}$ 选择 $dp_{l_2,r_2}+(p-i+1)a_p$。

分界点可以二分 $O(n \log n)$ 求得，然后选择左边的直接一个区间加，选择右边的则是区间加一个一次函数（我们可以把选择左边的也看做区间加一次函数，只不过 $y=kx+b$ 中 $b=0$）。

这个看到 [P1438](https://www.luogu.com.cn/problem/P1438) 的做法就可以了，大概就是维护差分，然后按照一次函数的套路来加就可以了。

而且我们也只需要单点询问，不需要区间询问，于是这道题就这么用线段树合并就可以了。

同理，如果强制在线的话可以弄个可持久化线段树就支持了一问一答。

## 代码

码量和常数都有点大，请谨慎观看。

```cpp
#include<bits/stdc++.h>
#define N 750005
#define ll long long
using namespace std;
inline char nc(){
	static char buf[1000000],*p=buf,*q=buf;
	return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++;
}
inline ll read(){
	ll res = 0;
	char c = nc();
	while(c<'0'||c>'9')c=nc();
	while(c<='9'&&c>='0')res=res*10+c-'0',c=nc();
	return res;
}
struct node{ll l,r,s,la,vi;}tr[N<<5];
vector<pair<ll,ll> > que[N];
ll n,q,x,y,a[N],i,j,l[N],r[N],mid[N],ls[N],rs[N],sta[N],top,st1[N][21],st2[N][21],root,rootr[N],temp[N];
ll ans1[N],ans2[N];
ll tot;
ll sl[N],sr[N];
ll build(ll p){
	top = 0;
	for(ll i=1;i<=n;i++){
		ll k = top;
		if(!p) while(k&&a[sta[k]]<a[i]) k--;
		else while(k&&a[sta[k]]<=a[i]) k--;
		if(k) rs[sta[k]] = i;
		if(k<top) ls[i]=sta[k+1];
		sta[++k] = i;
		top=k;
	}
	return sta[1];
}
ll query(ll l,ll r){
	ll c = log2(r-l+1);
	if(st1[l][c]>=st1[r-(1<<c)+1][c]) return st2[l][c];
	else return st2[r-(1<<c)+1][c];
}
void pushtagg(ll p,ll s,ll t,ll c){
	tr[p].la = 0,tr[p].vi = c,tr[p].s = (t-s+1)*c;
	return ;
}
void pushtag(ll p,ll s,ll t,ll c){
	if(tr[p].vi==-1){
		tr[p].la += c;
		tr[p].s += (t-s+1)*c;
	}
	else{
		tr[p].vi += c;
		tr[p].s += (t-s+1)*c;
	}
}
void pushdown(ll p,ll s,ll t){
	if(tr[p].vi!=-1){
		pushtagg(tr[p].l,s,(s+t)/2,tr[p].vi);
		pushtagg(tr[p].r,(s+t)/2+1,t,tr[p].vi);
		tr[p].vi = -1;
	}
	if(tr[p].la){
		pushtag(tr[p].l,s,(s+t)/2,tr[p].la);
		pushtag(tr[p].r,(s+t)/2+1,t,tr[p].la);
		tr[p].la = 0;
	}
}
ll merge(ll s,ll t,ll p1,ll p2){
	if(!p1||!p2) return p1+p2;
	if(s==t){
		tr[p2].s += tr[p1].s;
		return p2;
	}
	tr[p2].l = merge(s,(s+t)/2,tr[p1].l,tr[p2].l);
	tr[p2].r = merge((s+t)/2+1,t,tr[p1].r,tr[p2].r);
	tr[p2].s = tr[tr[p2].l].s + tr[tr[p2].r].s;
	return p2;
}
void add(ll l,ll r,ll s,ll t,ll &p){
	if(!p) p=++tot;
	if(l<=s&&t<=r){
		pushtagg(p,s,t,0);
		return ;
	}
	pushdown(p,s,t);
	if(l<=(s+t)/2) add(l,r,s,(s+t)/2,tr[p].l);
	if(r>(s+t)/2) add(l,r,(s+t)/2+1,t,tr[p].r);
	tr[p].s = tr[tr[p].l].s + tr[tr[p].r].s;
}
void modify(ll l,ll r,ll c,ll s,ll t,ll &p){
	if(!p){
		p = ++tot;
		tr[p].vi = -1;
	}
	if(l<=s&&t<=r){
		pushtag(p,s,t,c);
		return ;
	}
	pushdown(p,s,t);
	if(l<=(s+t)/2) modify(l,r,c,s,(s+t)/2,tr[p].l);
	if(r>(s+t)/2) modify(l,r,c,(s+t)/2+1,t,tr[p].r);
	tr[p].s = tr[tr[p].l].s + tr[tr[p].r].s;
}
ll query(ll l,ll r,ll s,ll t,ll p){
	if(l>r) return 0;
	if(!p) return 0;
	if(l<=s&&t<=r) return tr[p].s;
	pushdown(p,s,t);
	ll ans = 0;
	if(l<=(s+t)/2) ans+=query(l,r,s,(s+t)/2,tr[p].l);
	if(r>(s+t)/2) ans+=query(l,r,(s+t)/2+1,t,tr[p].r);
	return ans;
}
void init(ll x){
	sl[x] = sr[x] = x;
	if(ls[x]) init(ls[x]),sl[x]=min(sl[x],sl[ls[x]]);
	if(rs[x]) init(rs[x]),sr[x]=max(sr[x],sr[rs[x]]);
}
ll binary(ll s1,ll s2,ll c,ll s,ll t,ll p){
	if(s==t){
		if(s1+tr[p].s<=s2+(c-t+1)*a[c]) return c;
		else return s;
	}
	pushdown(p,s,t);
	if((s+t)/2<c&&s1+tr[tr[p].l].s<=s2+(c-(s+t)/2+1)*a[c]) return binary(s1+tr[tr[p].l].s,s2,c,(s+t)/2+1,t,tr[p].r);
	else return binary(s1,s2,c,s,(s+t)/2,tr[p].l);
}
void dfs(ll x){
	if(ls[x]) dfs(ls[x]),rootr[x]=merge(1,n,rootr[ls[x]],rootr[x]);
	if(rs[x]) dfs(rs[x]),rootr[x]=merge(1,n,rootr[rs[x]],rootr[x]);
	ll op = 0;
	if(rs[x]) op=query(1,sl[rs[x]],1,n,rootr[x]);
	modify(x,x,op+a[x],1,n,rootr[x]);
	if(x!=n) modify(x+1,x+1,-op-a[x],1,n,rootr[x]);
	if(ls[x]){
		if(rs[x]){
			ll pos = binary((sr[rs[x]]-x+1)*a[x],op,x,1,n,rootr[x]);
			pos = max(pos,sl[ls[x]]);
			if(pos!=sl[ls[x]]){
				modify(sl[ls[x]],sl[ls[x]],(sr[rs[x]]-x+1)*a[x],1,n,rootr[x]);
				modify(pos,pos,-(sr[rs[x]]-x+1)*a[x],1,n,rootr[x]);
			}
			if(pos!=x){
				ll t1 = query(pos+1,x-1,1,n,rootr[x]),t2 = query(1,pos,1,n,rootr[x]);
				modify(pos,pos,-t2,1,n,rootr[x]);
				if(pos+1<=x-1) add(pos+1,x-1,1,n,rootr[x]);
				modify(x,x,t1+t2,1,n,rootr[x]);
				modify(pos,pos,op,1,n,rootr[x]);
				modify(x,x,-op,1,n,rootr[x]);
				modify(pos,pos,(x-pos+2)*a[x],1,n,rootr[x]);
				modify(pos,x,-a[x],1,n,rootr[x]);
				modify(x,x,-a[x],1,n,rootr[x]);
			}
		}
		else modify(sl[ls[x]],sl[ls[x]],a[x],1,n,rootr[x]),modify(x,x,-a[x],1,n,rootr[x]);
	}
	for(ll i=0;i<que[x].size();i++) temp[que[x][i].second]=query(1,que[x][i].first,1,n,rootr[x]);
}
void maintain(){
	for(ll i=1;i<=tot;i++) tr[i].l=tr[i].r=tr[i].s=tr[i].la=tr[i].vi=0;
	memset(sta,0,sizeof(sta));
	memset(rootr,0,sizeof(rootr));
	memset(sl,0,sizeof(sl));
	memset(sr,0,sizeof(sr));
	memset(ls,0,sizeof(ls));
	memset(rs,0,sizeof(rs));
	for(ll i=1;i<=n;i++) que[i].clear();
	tot = 0,top = 0;
}
void solve(ll x){
	root = build(x);
	for(i=1;i<=q;i++) if(ls[mid[i]]) que[ls[mid[i]]].push_back(make_pair(l[i],i));
	init(root);
	dfs(root);
}
int main(){
	n=read(),q=read();
	for(i=1;i<=n;i++) a[i]=read();
	for(i=n;i>=1;i--){
		st1[i][0] = a[i],st2[i][0] = i;
		for(j=1;i+(1<<j)-1<=n;j++){
			if(st1[i][j-1]>=st1[i+(1<<(j-1))][j-1]){
				st1[i][j] = st1[i][j-1];
				st2[i][j] = st2[i][j-1];
			}
			else{
				st1[i][j] = st1[i+(1<<(j-1))][j-1];
				st2[i][j] = st2[i+(1<<(j-1))][j-1];
			}
		}
	}
	for(i=1;i<=q;i++) l[i]=read(),r[i]=read(),l[i]++,r[i]++,mid[i] = query(l[i],r[i]);
	maintain();
	solve(0);
	for(i=1;i<=q;i++) ans1[i]=temp[i]+(r[i]-mid[i]+1)*a[mid[i]];
	maintain();
	reverse(a+1,a+n+1);
	for(i=1;i<=q;i++) l[i]=n-l[i]+1,r[i]=n-r[i]+1,swap(l[i],r[i]),mid[i]=n-mid[i]+1;
	solve(1);
	for(i=1;i<=q;i++) ans2[i]=temp[i]+(r[i]-mid[i]+1)*a[mid[i]];
	for(i=1;i<=q;i++) printf("%lld\n",min(ans1[i],ans2[i]));
}
```

---

## 作者：forest114514 (赞：3)

## P5044 [IOI2018] meetings 会议

考虑朴素 DP，记 $f(l,r)$ 为 $[l,r]$ 的人去开会的最小代价，$k$ 为 $[l,r]$ 中最高的山的下标。

因为无论在哪里开会，会议点一侧的人都会翻过 $k$ 号山，而且不会正好在 $k$ 号山，不然所有人都会翻过最高的山就不优了，因此直接考虑会议点与 $k$ 号山的大小关系，则有 $f(l,r)=\min\{f(l,k-1)+h_k\times (r-k+1),f(k+1,r)+h_k\times (k-l+1)\}$ 。

直接 DP 是 $O(N^2)$ 的考虑有大量的 $f(l,r)$ 的最大值点 $k$ 都是相同的，而且显然 $k$ 只有 $O(N)$ 个，我们可以建出笛卡尔树来合并以及更新这些值。

考虑对于笛卡尔树的一个子树 $k$ 的有效区间 $[l,r]$，我们要求出 $f(l,l\sim r)$ 和 $f(l\sim r,r)$ 即前后缀的值，才能合并和递推。

考虑求出了两个儿子的前后缀 $f$，计算询问答案就直接按照 DP 方程回答即可，重点在于如何计算现在区间的前后缀 DP 值。

以前缀值为例首先所有的 $i\in[l,r], i< k$ 直接继承即可，然后 $i=k$ 可以直接加上 $h_k$，最后 $i>k$ 我们写出 DP 方程： 
$$
f(l,i)=\min\{f(l,k-1)+h_k\times (i-k+1),f(k+1,i)+h_k\times (k-l+1)\}
$$
首先看着维护这个函数需要支持区间加和区间对一次函数取 $\min$，单独拿开一个都好维护，但加一起就不好玩了，但我们看这个 DP 式子我们改写一下：
$$
f(l,i)=\min\{f(l,k-1)-(k-l)\times h_k,f(k+1,i)-(i-k)\times h_k\}+h_k\times (i-l+1)
$$
注意到此时 $\max$ 左端是一个定值，右边是一个严格单增的函数减去另一个严格单增函数，貌似也无法做的，但我们注意到此题一个特殊的东西：$(i-k)\times h_k\to (i+1-k)\times h_k,\Delta=+h_k$ 并且 $f(k+1,i)\to f(k+1,i+1),\Delta\le +h_k$，这是因为 $[k+1,r]$ 的所有数都是 $\le h_k$ 的，所以 $i+1$ 的人不会爬 $>h_k$ 的山，所以 $\Delta \le +h_k$，故 $f(l,k-1)+h_k\times (i-k+1)-f(k+1,i)+h_k\times (k-l+1)$ 是单调不减的。

因此满足 $f(l,k-1)+h_k\times (i-k+1)<f(k+1,i)+h_k\times (k-l+1)$ 如果有的话一定是连续的一段区间并且左端点是 $k$，我们二分确定这个区间的右端点， 转化为区间覆盖 0 和区间加一次函数即可。

最后我们需要区间覆盖 0，区间加一次函数，单点查询，打标记考虑用线段树维护，每次二分改成线段树上二分，维护区间 $\max$ 即可。

时间复杂度为 $O((N+Q)\log N)$。

[蒟蒻的冗长恶臭代码](https://www.luogu.com.cn/paste/rfng1wp9)

---

## 作者：min_inf (赞：1)

模拟赛场上想出来的神秘做法。

对于单组询问，我们考虑在笛卡尔树上 DP，显然有转移：

$$f_u=\min(f_{ls_u}+a_u(sz_{rs_u}+1),f_{rs_u}+a_u(sz_{ls_u}+1))$$

考虑怎么刻画区间笛卡尔树：找到区间最大值，把从左端点开始的前缀 $\max$ 及其右儿子和从右端点开始的后缀 $\max$ 及其左儿子合并起来。接下来我们只考虑右侧的做法。

从左往右扫，维护一个递减的单调栈并维护当前每个点的 DP 值 $g_i$。考虑加入一个点 $i$ 产生的影响：

- $g_i$ 显然是 $f_{ls_i}+a_i$。$ls_i$ 就是整个序列的笛卡尔树上的左儿子。
- 前面的某个点 $j$ 有 $g_j\gets\min(g_j+a_j,g_{nxt_j}+a_j(sz_{ls_j}+1))$（从右往左依次转移），$nxt_j$ 是单调栈上右边的元素。

看起来第二个不是很好维护，但是我们只需要求 $Q$ 个 $g$，考虑不直接维护每个 DP 值。假如我们要询问的是 $g_x$，可以发现肯定是从询问时存在的某个 $f_{ls_y}+a_y$ 转移过来的，被加上的一定是 $y-x$ 个 $a_y$（显然吃最右边的最优）和他们之间的节点的 $a_i(sz_{ls_i}+1)$ 的和，可以在单调栈上做一个前缀和，就是插入和询问的时候各加一个常数。

这样问题就变成了每个点有 $a_i$ 和 $b_i$，要支持单点修改，全局 $b_i\gets b_i+a_i$，求区间 $\min b_i$。显然可以 KTT 维护，时间复杂度 $O(n\log^2n)$，常数很小。

[code](https://www.luogu.com.cn/paste/qjezxh99)。

---

## 作者：wjyppm1403 (赞：1)

很好的题，能够很好的练习枚举最大值转移 DP。

我们一步一步来，顺着 subtask 来走：

有一个显然的想法，就是暴力选取开会的位置，直接做即可，复杂度 $O(n^2 q)$。

考虑 sub 2 如何做，首先注意到询问的是一个区间的答案，我们可以暴力预处理出来，但时间复杂度要在 $O(n^2)$ 以内，怎么做？注意到我们实际上不用暴力枚举，我们只需要一个区间的最大值出现在哪里，这个最大值将会贡献答案，让后枚举把会议丢在该位置左边还是右边即可。

具体来说，我们设 $f(l,r)$ 表示在 $[l,r]$ 的位置区间选会议的最小代价，转移是显然的：

$$f(l,r)=\min\left\{f(l,p-1)+(r-p+1) \times a_p,f(p+1,r)+(p-l+1) \times a_{p} \right\}$$

$p$ 即为 $[l,r]$ 的最大值，发现这两边形式一致，就可以只考虑一半东西，然后另一半直接将序列翻转再做一遍即可得到，利用 st 表即可做到 19 分。

我们观察这个转移方程，多次涉及区间 $\max$ 来进行转移，我们考虑笛卡尔树，不难发现我们枚举的最大值节点就是笛卡尔树的根节点，转移方程实际上就是在对左右儿子的答案进行统计，注意到原题目标准复杂度为 $O(q \log n)$，启示我们使用一些数据结构优化。

首先因为这是类似于笛卡尔树的 DP，我们可以考虑类似于树形 DP 的方式，从底往上进行 DP，转移如下：

$$f(l,r)=\min\left\{f(l,p-1)+(r-p+1) \times a_p,f(p+1,r)+(p-l+1) \times a_{p} \right\}$$

你骗我这个和上面式子完全一模一样的好吗！不要这么说吗，变量含义不同：$p$ 代表一个子树，而 $l,r$ 是 $p$ 子树内的节点。（~~不对啊那笛卡尔树根节点建出来不还是在枚举最大值吗，还嘴硬！~~）

但是如果直接做仍是 $O(n^2)$ 的，怎么办，自底向上合并答案，而且复杂度要求 $O(n\log n)$？考虑这个东西我们可以用线段树试试？注意到线段树刚好符合上面的转移方程（甜菜的想法），考虑转移，一个区间的转移我们还是要枚举 $p$……不对暴力转移还是 $O(n^2)$ 的啊！

当转移方程没有一些优化套路的时候，我们不妨尝试从转移上下手。

我们根据转移方程，发现 $i$ 越小，在左侧所需代价一定越来越小，而 $i$ 越来越大的时候，在右侧所需代价也一定越来越小。这两个形似一次函数，具有单调性，考虑线段树二分找交点（俗称转移优化），交点左侧为左侧的 DP 更新，右侧即右侧更新。那么我们的线段树需要维护一次函数的形式，支持单点修改和区间拷贝合并覆盖，这个操作很抽象，但是复杂度却很优秀，于是我们就做完了。

这就是我们所说的枚举最大值转移，枚举最大值转移 DP，实际上就是排列在笛卡尔树结构上的 DP（注意不是真正的笛卡尔树），有点类似于分治的思想。我们利用的是一个笛卡尔树的性质：我们设一个区间 $[l,r]$ 最大值的位置为 $pos$，发现可以把区间分成 $[l,pos]$ 和 $[pos,r]$ 两个区间，并且两个区间互不影响，也就是说我左边怎么乱搞放数也不会影响右边的区间。这个时候全局最大值作为区间的端点出现。自底向上类似 “树形 DP” 来合并区间。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=8e5+15;
struct Query{
    int l,r;
}qry[MN];
int n,q,ans[MN],h[MN],st[MN][30],arcst[MN][30],lg[MN];
vector<int> pos[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r,cov,k,b,lmx,rmx;
    }t[MN<<2];

    void docov(int p){
        t[p].cov=1;
        t[p].k=t[p].b=t[p].lmx=t[p].rmx=0;
    }

    void doadd(int p,int k,int b){
        t[p].k+=k;
        t[p].b+=b;
        t[p].lmx+=k*t[p].l+b;
        t[p].rmx+=k*t[p].r+b;
    } 

    void pushdown(int p){
        if(t[p].cov){
            docov(ls);
            docov(rs);
        }
        if(t[p].k||t[p].b){
            doadd(ls,t[p].k,t[p].b);
            doadd(rs,t[p].k,t[p].b);
        }
        t[p].cov=t[p].k=t[p].b=0;
    }

    void pushup(int p){
        t[p].lmx=t[ls].lmx,t[p].rmx=t[rs].rmx;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void update(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,0,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) update(ls,fl,fr,k);
        if(mid<fr) update(rs,fl,fr,k);
        pushup(p);
    }

    void merge(int p,int fl,int fr,int k,int b){
        if(t[p].l>=fl&&t[p].r<=fr){
            int lv=t[p].l*k+b,rv=k*t[p].r+b;
            if(lv>=t[p].lmx&&t[p].rmx<=rv) return;
            if(t[p].lmx>=lv&&rv<=t[p].rmx){
                docov(p);
                doadd(p,k,b);
                return;
            }
        }  
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) merge(ls,fl,fr,k,b);
        if(mid<fr) merge(rs,fl,fr,k,b);
        pushup(p);
    }

    int querylmx(int p,int pos){
        if(t[p].l==t[p].r) return t[p].lmx;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return querylmx(ls,pos);
        return querylmx(rs,pos);
    }

    int queryrmx(int p,int pos){
        if(t[p].l==t[p].r) return t[p].rmx;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return queryrmx(ls,pos);
        else return queryrmx(rs,pos);
    }
#undef ls
#undef rs
}s,t;

void initst(){
    for(int j=1;j<=20;j++){
        for(int i=1;i<=n;i++){
            if(i+(1<<j)-1>n) break;
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            if(st[i][j]==st[i][j-1]) arcst[i][j]=arcst[i][j-1];
            else arcst[i][j]=arcst[i+(1<<(j-1))][j-1];
        }
    }
}

int cmp(int l,int r){
    int len=__lg(r-l+1);
    if(st[l][len]>=st[r-(1<<len)+1][len]){
        return arcst[l][len];
    }else return arcst[r-(1<<len)+1][len];
}

void solve(int l,int r){
    if(l>r) return;
    int mid=cmp(l,r);
    solve(l,mid-1);
    solve(mid+1,r);
    for(auto now:pos[mid]){
        ans[now]=h[mid]*(qry[now].r-qry[now].l+1);
        if(qry[now].l<mid){
            ans[now]=min(ans[now],s.querylmx(1,qry[now].l)+h[mid]*(qry[now].r-mid+1));
        }
        if(qry[now].r>mid){
            ans[now]=min(ans[now],t.queryrmx(1,qry[now].r)+h[mid]*(mid-qry[now].l+1));
        }
    }

    int sx=h[mid],tx=h[mid];
    if(l<mid) tx+=t.queryrmx(1,mid-1);
    if(r>mid) sx+=s.queryrmx(1,mid+1);
    s.update(1,mid,mid,sx);
    t.update(1,mid,mid,tx);
    if(l<mid){
        s.update(1,l,mid-1,h[mid]*(r-mid+1));
        s.merge(1,l,mid-1,-1*h[mid],sx+mid*h[mid]);
    }
    if(r>mid){
        t.update(1,mid+1,r,h[mid]*(mid-l+1));
        t.merge(1,mid+1,r,1ll*h[mid],tx-1ll*mid*h[mid]);
    }

}

signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        st[i][0]=h[i];
        arcst[i][0]=i;
    }
    for(int i=1;i<=q;i++){
        cin>>qry[i].l>>qry[i].r;
        qry[i].l++;
        qry[i].r++;
    }
    initst();
    for(int i=1;i<=q;i++){
        pos[cmp(qry[i].l,qry[i].r)].push_back(i);
    }
    s.build(1,1,n);
    t.build(1,1,n);
    solve(1,n);
    for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
    return 0;
}

```

---

## 作者：tzc_wk (赞：1)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P5044)

一道笛卡尔树的 hot tea。

首先我们考虑一个非常 naive 的区间 DP：$dp_{l,r}$ 表示区间 $[l,r]$ 的答案，那么我们考虑求出 $[l,r]$ 中最大值的位置所在的位置 $p$，那么如果我们选取的 meeting 的位置 $\le p$，那么显然 $[p+1,r]$ 部分的贡献都是 $a_p$，$[l,p]$ 部分的总共先最小是 $dp_{l,p}$，最优代价为 $dp_{l,p}+a_p·(r-p)$，否则 $[l,p]$ 部分的贡献都是 $a_p$，$[p+1,r]$ 部分的总贡献最小是 $dp_{p+1,p}$，最优代价为 $dp_{p+1,p}+a_p·(p-l+1)$，二者取 $\min$ 即可。

直接做最优大概是 $n^2$ 的，可以获得 19 分的好成绩（雾）。考虑优化，注意到这东西有点像笛卡尔树，因此我们考虑将笛卡尔树建出来。对于此题而言，由于数据范围允许 $n\log n$ 通过，我们可以使用 $n\log n$ 的 ST 表建树方法，不必采用那个严格线性的方式。我们考虑对于每组询问 $[L,R]$，找到 $[L,R]$ 区间中最大值所在的位置 $p$，然后将整个询问拆成两个询问：$[L,p-1]$ 和 $[p+1,R]$——为什么要这样干呢？原理与 P3246 [HNOI2016]序列 一致，因为这样我们就造出了两个区间，一个满足区间左边那个数大于等于区间中所有数，另一个则满足区间右边那个数大于等于区间中所有数（方便起见，对于后面的部分，我们可以将整个数组翻转一遍然后对翻转后的数组再做一遍这个操作，这样两部分就等价了，注意在后面一半建树部分有些小细节，所有值相同的最大值中，取下标最大的还是最小的要想清楚，不要想当然）这样一来，对于笛卡尔树上每个点 $x$ 我们如果假设 $x$ 子树内的点表示的区间左端点为 $L_x$，右端点为 $R_x$，那么对于满足“左边的数大于等于区间中所有数的区间 $[L,R]$”，我们必然能够在笛卡尔树上找到某个点 $x$，满足 $L_x=L$，也就是说我们可以将每个询问挂在这个区间中所有点在笛卡尔树的 LCA，也就是 $[L,R]$ 最大值所在的位置表示的点上，然后离线一遍 DFS，DFS 的过程中扫描到点 $x$ 时，用某种方式维护 $[L_x,L_x],[L_x,L_x+1],\cdots,[L_x,R_x]$ 的 DP 值，这样即可查出答案。

那么怎么维护这样些 DP 值呢？我们开一棵线段树，下标为 $r$ 的位置实时维护右端点为 $r$ 的区间的 DP 值。那么假设我们遍历到点 $x$，$[L_x,R_x]$ 最大值所在的位置为 $p$，那么我们先遍历 $[L_x,p-1],[p+1,R_x]$，那么对于 $[L_x,p-1]$ 中的位置，其 DP 值肯定不会发生变化，合并的时候就不用管它，对于 $dp_{L_x,p}$，由于区间 $[L_x,p]$ 最大值就是 $a_p$，因此我们肯定只能令 meeting 的位置 $\le p$，此时 $dp_{L_x,p}=dp_{L_x,p-1}+a_p·(p-L_x+1)$，在线段树上查询 $p-1$ 位置的值然后做出对应修改即可。

比较棘手的是区间 $[p+1,R_x]$。对于区间 $[p+1,R_x]$ 中的某个 $v$，根据上面朴素的 DP 有 $dp_{L_x,v}=\min(dp_{L_x,p}+(v-p)·a_p,dp_{p+1,v}+(p-L_x+1)·a_p)$，不难发现 $\min$ 左右两边都是递增的，并且右边的部分增长速度严格慢于左边，因此我们考虑二分找出最右边的位置 $pos$，满足 $dp_{L_x,p}+(pos-p)·a_p\le dp_{p+1,pos}+(p-L_x+1)·a_p$，然后令 $[p+1,v]$ 位置中的 DP 值先清零，然后对于所有 $i\in[p+1,v]$，DP 值假设 $(dp_{L_x,p}-p·a_p)+i·a_p$，$[v+1,p]$ 位置上的值整体加上 $(p-L_x+1)·a_p$，那么怎么找到这个位置 $pos$ 呢？直接二分是 2log 的，不过注意到如果我们令 $A=dp_{L_x,p}-p·a_p,B=a_p,C=(p-L_x+1)·a_p)$，那么我们等价于找到最右边的位置满足 $A+Bi\le C+f(i)$，其中 $f(i)$ 表示线段树上下标为 $i$​ 的位置上的值，这个一脸线段树二分的样子，线段树上二分一下即可做到 1log。

时间复杂度 $(n+q)\log n$。

```cpp
const int MAXN=7.5e5;
const int LOG_N=20;
int n,qu,a[MAXN+5];
pii qp[MAXN+5];
struct solver{
	pii st[MAXN+5][LOG_N+2];
	pii query(int l,int r){
		int k=31-__builtin_clz(r-l+1);
		return max(st[l][k],st[r-(1<<k)+1][k]);
	}
	int ncnt=0,rt=0,ch[MAXN+5][2],md[MAXN+5];
	void build_cat(int &k,int l,int r){
		if(l>r) return;if(!k) k=++ncnt;md[k]=abs(query(l,r).se);
//		printf("%d %d %d\n",l,r,md[k]);
		build_cat(ch[k][0],l,md[k]-1);build_cat(ch[k][1],md[k]+1,r);
	}
	void init(){
		for(int i=1;i<=LOG_N;i++) for(int j=1;j+(1<<i)-1<=n;j++)
			st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);
		build_cat(rt,1,n);
	}
	vector<pii> qv[MAXN+5];
	void add_query(int l,int r,int id){
		if(l>r) return;int ps=abs(query(l,r).se);
//		printf("+ %d %d %d %d\n",l,r,id,ps);
		qv[ps].pb(mp(r,id));
	}
	struct node{int l,r;ll val,lz0,lz1,t0;} s[MAXN*4+5];
	void pushup(int k){s[k].val=s[k<<1|1].val;}
	void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;if(l==r) return;int mid=l+r>>1;
		build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	}
	void make0(int k){s[k].t0=1;s[k].val=s[k].lz0=s[k].lz1=0;}
	void tag(int k,ll v0,ll v1){
		s[k].val+=v0+1ll*s[k].r*v1;
		s[k].lz0+=v0;s[k].lz1+=v1;
	}
	void pushdown(int k){
		if(s[k].t0){make0(k<<1);make0(k<<1|1);s[k].t0=0;}
		if(s[k].lz0||s[k].lz1){
			tag(k<<1,s[k].lz0,s[k].lz1);
			tag(k<<1|1,s[k].lz0,s[k].lz1);
			s[k].lz0=s[k].lz1=0;
		}
	}
	void addrng(int k,int l,int r,ll v0,ll v1){
		if(l>r) return;
		if(l<=s[k].l&&s[k].r<=r) return tag(k,v0,v1),void();
		pushdown(k);int mid=s[k].l+s[k].r>>1;
		if(r<=mid) addrng(k<<1,l,r,v0,v1);
		else if(l>mid) addrng(k<<1|1,l,r,v0,v1);
		else addrng(k<<1,l,mid,v0,v1),addrng(k<<1|1,mid+1,r,v0,v1);
		pushup(k);
	}
	void modify(int k,int p,ll x){
		if(s[k].l==s[k].r) return s[k].val=x,void();
		pushdown(k);int mid=s[k].l+s[k].r>>1;
		(p<=mid)?modify(k<<1,p,x):modify(k<<1|1,p,x);
		pushup(k);
	}
	int walk(int k,int l,int r,ll lft,int dlt,ll rit){//the rightmost index i satisfying lft+dlt*i<=rit+f(i)
		if(s[k].l==s[k].r) return (lft+1ll*dlt*s[k].l<=rit+s[k].val)?s[k].l:(s[k].l-1);
		pushdown(k);int mid=s[k].l+s[k].r>>1;
		if(r<=mid) return walk(k<<1,l,r,lft,dlt,rit);
		else if(l>mid) return walk(k<<1|1,l,r,lft,dlt,rit);
		else{
			if(lft+1ll*dlt*mid<=rit+s[k<<1].val) return walk(k<<1|1,mid+1,r,lft,dlt,rit);
			else return walk(k<<1,l,mid,lft,dlt,rit);
		}
	}
	void makezero(int k,int l,int r){
		if(l>r) return;
		if(l<=s[k].l&&s[k].r<=r) return make0(k),void();
		pushdown(k);int mid=s[k].l+s[k].r>>1;
		if(r<=mid) makezero(k<<1,l,r);
		else if(l>mid) makezero(k<<1|1,l,r);
		else makezero(k<<1,l,mid),makezero(k<<1|1,mid+1,r);
		pushup(k);
	}
	ll query_pt(int k,int p){
		if(s[k].l==s[k].r) return s[k].val;
		pushdown(k);int mid=s[k].l+s[k].r>>1;
		return (p<=mid)?query_pt(k<<1,p):query_pt(k<<1|1,p);
	}
	ll res[MAXN+5];
	void solve(int k,int l,int r){
//		printf("solving %d %d %d\n",k,l,r);
		if(!k) return;
		if(!ch[k][0]&&!ch[k][1]){
			modify(1,l,st[l][0].fi);
			for(pii p:qv[l]) res[p.se]=st[l][0].fi;
			return;
		} int mid=md[k];
		solve(ch[k][0],l,mid-1);solve(ch[k][1],mid+1,r);
		ll val=(!ch[k][0])?st[mid][0].fi:(query_pt(1,mid-1)+st[mid][0].fi);
		modify(1,mid,val);
//		printf("%d %d %d %lld\n",l,r,mid,val);
		if(mid<r){
			int pos=walk(1,mid+1,r,val-1ll*st[mid][0].fi*mid,st[mid][0].fi,1ll*st[mid][0].fi*(mid-l+1));
			makezero(1,mid+1,pos);addrng(1,mid+1,pos,val-1ll*st[mid][0].fi*mid,st[mid][0].fi);
			addrng(1,pos+1,r,1ll*(mid-l+1)*st[mid][0].fi,0);
		} for(pii p:qv[mid]) res[p.se]=query_pt(1,p.fi);
	}
	void work(){build(1,1,n);solve(rt,1,n);}
} fw,bk;
int main(){
	scanf("%d%d",&n,&qu);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) fw.st[i][0]=mp(a[i],i);
	for(int i=1;i<=n;i++) bk.st[i][0]=mp(a[n-i+1],-i);
	fw.init();bk.init();
	for(int i=1;i<=qu;i++){
		scanf("%d%d",&qp[i].fi,&qp[i].se);++qp[i].fi;++qp[i].se;
		int ps=fw.query(qp[i].fi,qp[i].se).se;
//		printf("ps=%d\n",ps);
		fw.add_query(ps+1,qp[i].se,i);
		bk.add_query(n-ps+2,n-qp[i].fi+1,i);
	} fw.work();bk.work();
//	for(int i=1;i<=qu;i++) printf("%lld %lld\n",fw.res[i],bk.res[i]);
	for(int i=1;i<=qu;i++){
		ll r1=fw.res[i],r2=bk.res[i];
		int ps=fw.query(qp[i].fi,qp[i].se).se;
		printf("%lld\n",min(r1+1ll*a[ps]*(ps-qp[i].fi+1),r2+1ll*a[ps]*(qp[i].se-ps+1)));
	}
	return 0;
}
```



---

## 作者：R_shuffle (赞：0)

乘着题解通道还没关，来交一发。

-------
题意非常明确，就是定义两个点之间的代价为这两个点形成的区间最大值，给出一个区间，求区间中一个点到区间中所有点的代价的总和的最小值。

不妨先考虑特殊性质，即 $H_i\leq 2$ 的部分。这一部分很容易能想到一个解法，就是考虑区间内所有全 $1$ 的连续段，取出其中最长的那个，这样这个连续段的代价就都是 $1$，但是显然连续段外的代价都是 $2$。所以不妨考虑这种类似的变化。不难注意到这里和最大值强相关，所以考虑建笛卡尔树。

然后考虑和区间最大值有关的做法，不妨设 $f_{l,r}$ 表示区间 $[l,r]$ 的答案，不妨设区间最大值的位置为 $x$。显然有转移 $f_{l,r}=\min(f_{l,x-1}+(r-x+1)\times H_x,f_{x+1,r,}+(x-l+1)\times H_x)$。然后不难发现 $f_{l,x-1}$ 相当于一个笛卡尔树节点的一段后缀，$f_{x+1,r}$ 相当于一个笛卡尔树节点的一段前缀。所以需要对笛卡尔树的每一个节点维护出后缀和前缀的值。

然后考虑类似分治的过程，然后考虑合并两个区间。

不妨以合并区间对前缀的处理为例。转移式和之前的还是一样的，唯一不同的地方在于这次的转移左端点是固定的，右端点是一个区间。我们有 $f_{l,i}=\min(f_{l,x-1}+(i-x+1)\times H_x,f_{x+1,i}+(x-l+1)\times H_x)$。显然前半部分是一个关于 $i$ 的一次函数，后半部分是一个区间的 $f$ 的值加上一个定值。对于后半部分，可以考虑直接加上；对于前半部分，可以考虑用线段树来维护这个东西。由于我们知道 $f_{l,i+1}-f_{l,i}\leq a_x$ 的，所以转移取前半部分的是一个连续区间，转移取后半部分的还是一个连续的区间。所以可以用线段树来维护 $f$，二分出转移取前半部分和转移取后半部分的分界点，然后对一半直接加上定值，对另一半直接用等差数列覆盖。所以可以做到时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

---

## 作者：tobie (赞：0)

考察询问序列中的最大值 $pos$，不妨设会议在最大值的右边举办。

考虑直接计算答案：对于 $pos$ 左边的人，他们对答案的贡献就是 $a_{pos}$，而右边的人需要进一步地往下讨论。注意到左边人的贡献恒定，所以右边的部分相当于一个子问题，可以往下递归去做。

“每次找到最大值”的递归结构让我们想到笛卡尔树。先把笛卡尔树建出来，对于一个节点 $u$，设它代表了区间 $[l,r]$，则我们每次需要求出 $[l,R]$ 的答案，记为 $f(l,R)$。

考虑自底向上合并结果，则我们已经求出了 $f(l,u-1)$ 和 $f(u+1,R)$ 的，考虑继续对决策 $p$ 和 $u$ 的大小关系分类讨论：

> 1. $p=u$ 直接计算即可。
> 2. 对于 $p>u$，则 $[l,u]$ 的所有人的代价都是 $a_u$，所以 $f(u+1,R)+(u-l+1)\times a_u\to f(l,R)$
> 3. 对于 $p<u$，则 $[u,R]$ 的所有人的代价都是 $a_u$，所以 $f(l,u-1)+(R-u+1)\times a_u\to f(l,R)$。

考虑维护出 $g_l(r)$ 表示 $[l,r]$ 的答案，则第二种转移可以表示为函数的上下平移，第三种转移可以表示为对一个一次函数取 $\max$，使用带加法标记的李超线段树合并即可维护。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
#define int long long
bool st_;
namespace io{

inline void gi(int &x)
{
	x=0;char ch=getchar();
	while(ch<'0'||'9'<ch) ch=getchar();
	while('0'<=ch&&ch<='9') x=x*10+ch-'0',ch=getchar();
}
void print(int x)
{
	if(x<=9) return putchar(x+'0'),void();
	print(x/10),putchar(x%10+'0');
}

}using io::gi;using io::print;

const int N=8e5+9;
const int inf=1e16;
int n,Q,a[N],ans[N];
struct Quer{
	int l,r,id;
	Quer(){}
	Quer(int l_,int r_,int id_){l=l_,r=r_,id=id_;}
};
vector<Quer> vec[N];

int son[N][2],sta[N],tp=0;
int fa[N],dep[N],mxson[N],siz[N],top[N];
void dfs0(int u,int f)
{
	if(!u) return;
	fa[u]=f;
	dep[u]=dep[f]+1;
	siz[u]=1;
	for(int i=0,v;i<=1;i++)
	if(v=son[u][i])
	{
		dfs0(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[mxson[u]]) mxson[u]=v;
	}
}
void dfs1(int u,int tp_)
{
	top[u]=tp_;
	if(mxson[u]) dfs1(mxson[u],tp_);
	for(int i=0;i<=1;i++)
	{
		int v=son[u][i];
		if(v==0||v==mxson[u]) continue;
		dfs1(v,v);
	}
}
inline int getlca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}

struct Line{
	int k,b;
	Line(){}
	inline Line(int k_,int b_){k=k_,b=b_;}
	inline int f(int x){return k*x+b;}
};
Line val[N<<4];
int tr[N<<4][2],tag[N<<4],ncnt=0;
void Add(int u,int x){if(u) tag[u]+=x,val[u].b+=x;}
void pushdown(int u)
{
	if(tag[u]) Add(tr[u][0],tag[u]),Add(tr[u][1],tag[u]),tag[u]=0;
}
void Ins(int &u,int l,int r,int L,int R,Line x)
{
	if(L<=l&&r<=R)
	{
		if(!u) return val[u=++ncnt]=x,tr[u][0]=tr[u][1]=0,void();
		int fl=val[u].f(l),fr=val[u].f(r);
		int fl2=x.f(l),fr2=x.f(r);
		if(fl<=fl2&&fr<=fr2) return;
		if(fl>=fl2&&fr>=fr2) return val[u]=x,void();
		int mid=(l+r)/2;
		if(val[u].f(mid)>x.f(mid)) swap(x,val[u]),swap(fl,fl2),swap(fr,fr2);
		pushdown(u);
		if(fl>=fl2) Ins(tr[u][0],l,mid,L,R,x);
		else Ins(tr[u][1],mid+1,r,L,R,x);
	}
	else
	{
		if(!u) val[u=++ncnt]=Line(0,inf),tr[u][0]=tr[u][1]=0;
		int mid=(l+r)/2;
		pushdown(u);
		if(L<=mid) Ins(tr[u][0],l,mid,L,R,x);
		if(mid<R) Ins(tr[u][1],mid+1,r,L,R,x);
	}
}
int Merge(int u,int v,int l,int r)
{
	if(!u||!v) return u+v;
	pushdown(u),pushdown(v);
	int mid=(l+r)/2;
	tr[u][0]=Merge(tr[u][0],tr[v][0],l,mid);
	tr[u][1]=Merge(tr[u][1],tr[v][1],mid+1,r);
	return u;
}
int Query(int u,int l,int r,int x)
{
	if(!u) return inf;
	if(l==r) return val[u].f(l);
	int ans=val[u].f(x),mid=(l+r)/2;
	pushdown(u);
	if(x<=mid) return min(ans,Query(tr[u][0],l,mid,x));
	else return min(ans,Query(tr[u][1],mid+1,r,x));
}
int rt[N];
void dfs2(int u,int l,int r)
{
	if(!u) return;
	rt[u]=0;
	dfs2(son[u][0],l,u-1);
	dfs2(son[u][1],u+1,r);
	for(auto q:vec[u])
	{
		int id=q.id,L=q.l,R=q.r;
		ans[id]=min(ans[id],(u-L+1)*a[u]+Query(rt[son[u][1]],1,n,R));
	}
	int tmp=min(Query(rt[son[u][0]],1,n,u-1),a[u]*(u-l));
	if(son[u][1]) Add(rt[son[u][1]],a[u]*(u-l+1));
	rt[u]=Merge(rt[son[u][0]],rt[son[u][1]],1,n);
	Ins(rt[u],1,n,u,r,Line(a[u],tmp-a[u]*(u-1)));
}
void dfs3(int u,int l,int r)
{
	if(!u) return;
	rt[u]=0;
	dfs3(son[u][0],l,u-1);
	dfs3(son[u][1],u+1,r);
	for(auto q:vec[u])
	{
		int id=q.id,L=q.l,R=q.r;
		ans[id]=min(ans[id],(R-u+1)*a[u]+Query(rt[son[u][0]],1,n,L));
	}
	int tmp=min(Query(rt[son[u][1]],1,n,u+1),a[u]*(r-u));
	if(son[u][0]) Add(rt[son[u][0]],a[u]*(r-u+1));
	rt[u]=Merge(rt[son[u][0]],rt[son[u][1]],1,n);
	Ins(rt[u],1,n,l,u,Line(-a[u],tmp+a[u]*(u+1)));
}
bool ed_;
signed main()
{
	//cerr<<(&ed_-&st_)/1048576.0<<"Mib\n";
	gi(n),gi(Q);
	for(int i=1;i<=n;i++) gi(a[i]);
	for(int i=1;i<=n;i++)
	{
		while(tp&&a[sta[tp]]<=a[i]) son[i][0]=sta[tp--];
		if(sta[tp]) son[sta[tp]][1]=i;
		sta[++tp]=i;
	}
	int st=sta[1];
	dfs0(st,0);dfs1(st,st);
	for(int i=1;i<=Q;i++)
	{
		int l,r;
		gi(l),gi(r);
		l++,r++;
		int tmp=getlca(l,r);
		vec[tmp].push_back(Quer(l,r,i));
		ans[i]=(r-l+1)*a[tmp];
	}
	ncnt=0;
	dfs2(st,1,n);
	ncnt=0;
	dfs3(st,1,n);
	for(int i=1;i<=Q;i++) print(ans[i]),putchar('\n');
}
```

---

