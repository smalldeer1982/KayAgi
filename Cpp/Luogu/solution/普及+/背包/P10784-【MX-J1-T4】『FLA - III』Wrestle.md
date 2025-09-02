# 【MX-J1-T4】『FLA - III』Wrestle

## 题目背景

原题链接：<https://oier.team/problems/J1D>。

---

在 2022 年末，疫情将西北某不知名知名学校的大多数学生关在家中上网课，安同学还不知道，他和语文老师的对决已然悄无声息地开始了——他每天早读和语文课都直接睡过去了。

安同学习惯起来穿好衣服、面对摄像头睡觉，摄像头只能拍到他的半个肩膀，就算被强制打开也不会暴露他在睡觉的事实，而且从来没有老师强制打开他的摄像头。而这个不凡的早晨，语文老师打开了他的摄像头，现在是早读时间，他在朦胧中被老师的关爱声叫醒，可惜为时已晚，老师已经愤怒。安同学决定假装网络卡顿，平复老师愤怒的心情。

老师，愤怒了！在安同学醒来后的某些时间段，她要呼叫他的真名，其余时间等他应答。与此同时安同学要打造网卡的假象，他可以在某些时间段内检查设备或者呼叫老师，其余时间静止或随机在画面中闪现，他在这些时间段内的行为称为表演。你的任务是帮助安同学在不激怒老师的情况下最大化表演时间。

因为安同学实在是太抽象了，原始题面受他影响变得也很抽象，这里只有形式化题面给你看。

## 题目描述

给定三个正整数 $n,m,k$ 和两组线段。第一组线段有权值，共 $n$ 条，是**红色**的；第二组线段没有权值，共 $m$ 条，是**蓝色**的。这些线段位于同一个数轴。

- 使用 $l,r,w$ 三个正整数表示一条从数轴上第 $l$ 个整点覆盖到第 $r$ 个整点，权值为 $w$ 的红色线段。**保证数轴上任意一个整点至多被红色线段覆盖一次。**

- 使用 $L,R$ 两个正整数表示一条从数轴上第 $L$ 个整点覆盖到第 $R$ 个整点，没有权值的蓝色线段。**保证数轴上任意一个整点至多被蓝色线段覆盖一次。**

如果一条红色线段从第 $l_0$ 个整点覆盖到第 $r_0$ 个整点，一条蓝色线段从第 $L_0$ 个整点覆盖到第 $R_0$ 个整点且 $\max(l_0,L_0) \leq \min(r_0,R_0)$，就认为这两条线段有交集，交集包含从第 $\max(l_0,L_0)$ 个整点到第 $\min(r_0,R_0)$ 个整点的全部 $\min(r_0,R_0)-\max(l_0,L_0)+1$ 个整点。你可以选择一些蓝色线段，一种合法的选择方案必须符合以下条件：

- 题目给定的每条红色线段至多与你选择的 $1$ 条蓝色线段有交集。

- 所有和**你选择的蓝色线段**有交集的红色线段权值之和不超过 $k$。

选择方案合法时，**你选择的蓝色线段**和**所有红色线段**的交集至多能包含多少个整点？

## 说明/提示

**「样例解释 #1」**

![example](https://cdn.luogu.com.cn/upload/image_hosting/0mxbdlcn.png)

如图，选择输入的第 $2$ 条蓝色线段和第 $3$ 条蓝色线段。

第 $2$ 条蓝色线段与第 $1$ 条红色线段有交，交集包含从第 $13$ 个整点到第 $18$ 个整点的所有整点；第 $3$ 条蓝色线段与第 $2$ 条红色线段有交，交集包含从第 $63$ 个整点到第 $71$ 个整点的所有整点。

第 $1$ 条红色线段仅与第 $2$ 条蓝色线段有交，第 $2$ 条红色线段仅与第 $3$ 条蓝色线段有交；和被选择的蓝色线段有交的红色线段权值和为 $9$，方案合法。故答案为 $15$。

**「数据范围」**

**本题采用捆绑测试。**

|Subtask|$n \leq$|$m \leq$|$k \leq$|$l_i,r_i,L_i,R_i \leq$|分值|
|:-:|:-:|:-:|:-:|:-:|:-:|
|**#1**|$10$|$10$|$50$|$100$|$20$|
|**#2**|$200$|$200$|$200$|$10^5$|$30$|
|**#3**|$5000$|$5000$|$5000$|$10^9$|$30$|
|**#4**|$2 \times 10^5$|$5000$|$5000$|$10^9$|$20$|

对于 $100\%$ 的数据，$1 \leq n \leq 2 \times 10^5$，$1 \leq m,k \leq 5000$，$1 \leq l_i,r_i,L_i,R_i \leq 10^9$，$1 \leq w_i \leq k$，$l_i < r_i$，$L_i < R_i$。**保证数轴上任意一个整点至多被红色线段覆盖一次。保证数轴上任意一个整点至多被蓝色线段覆盖一次。**

## 样例 #1

### 输入

```
2 3 23
7 18 7
63 71 2
77 86
13 19
63 71
```

### 输出

```
15
```

## 样例 #2

### 输入

```
4 5 7
59 65 7
39 42 1
43 51 2
19 33 2
14 25
71 81
6 11
59 69
83 92
```

### 输出

```
7
```

## 样例 #3

### 输入

```
4 8 45
80 94 22
60 67 2
35 44 45
7 14 5
82 86
2 3
58 63
48 50
73 80
25 45
11 19
93 94
```

### 输出

```
13
```

# 题解

## 作者：ScaredQiu (赞：23)

### 动态规划、前缀和

我出的第一道题。

------------

#### Subtask #1

枚举选择了哪些蓝色线段，由于 $l_i,r_i,L_i,R_i$ 的值域小，容易判断选择当前选择方案是否合法，如果合法则更新答案。

时间复杂度 $O(n2^m)$。

#### Subtask #2

在权值和上限 $k$ 的限制下计算最优答案，容易发现这是一个背包问题，考虑动态规划。**称与一条蓝色线段有交的所有红色线段权值和为这条蓝色线段的重量，一条蓝色线段与所有红色线段的交集包含的整点数量为这条蓝色线段的价值。**

```cpp
struct Segment{int l,r,w,v;}a[205],b[205];
//a:红色线段 b:蓝色线段 w:权值&重量 v:价值
```

设计 $dp_{i,j}$ 为在前 $i$ 条蓝色线段中选择若干线段，选择了第 $i$ 条线段或者没有选择任何线段、方案合法且被选线段重量之和为 $j$ 时能得到的最大价值。

如何保证选择方案合法？对于每条蓝色线段枚举所有红色线段，如果两条线段有交则将红色线段“拼”在蓝色线段上，把它们交集中的整点计入蓝色线段的价值，把红色线段的权值计入蓝色线段的重量。

```cpp
for(int i=1;i<=m;i++){
    auto it=b[i];//判断是否相交不能用拼接后的线段
    for(int j=1;j<=n;j++){
        if(it.l>a[j].r||it.r<a[j].l) continue;
        b[i].l=min(b[i].l,a[j].l);
        b[i].r=max(b[i].r,a[j].r);
        b[i].w+=a[j].w;
        b[i].v+=min(it.r,a[j].r)-max(it.l,a[j].l)+1;
    }
}
```

这样处理之后，只要拼接后的两个蓝色线段不相交就可以进行状态转移了。在转移之前将蓝色线段按照左端点位置排序可以保证状态根据线段的位置从左到右转移。

```cpp
int dp[205][205];
sort(b+1,b+m+1,[](auto x,auto y){return x.l<y.l;});
for(int i=1;i<=m;i++){
    for(int j=1;j<=i-1;j++) if(b[i].l>b[j].r){
        for(int q=k;q>=b[i].w;q--) dp[i][q]=max(dp[i][q],dp[j][q-b[i].w]+b[i].v);
    }
}
```

答案即为 $dp$ 数组中的最大值，时间复杂度 $O(nm+m^2k)$。

#### Subtask #3

拼接线段部分的时间复杂度为 $O(nm)$，可以接受，考虑优化 $O(m^2k)$ 的状态转移。

容易发现如果排序后线段 $j$ 能转移到线段 $i$，那么所有下标比 $j$ 小的线段都能转移到线段 $i$。预处理右端点最大的能够转移到 $i$ 的线段编号，记为 $pre_i$。

修改状态定义，使得 $dp_{i,j}$ 表示在前 $i$ 条蓝色线段中选择若干线段，方案合法且被选线段重量之和为 $j$ 时能得到的最大价值，找到下标最大的能转移到 $i$ 的线段转移。

```cpp
for(int i=1;i<=m;i++)
    for(int j=1;j<=m-1;j++) if(b[i].l>b[j].r) pre[i]=j;
for(int i=1;i<=m;i++){
    for(int j=1;j<=k;j++) dp[i][j]=dp[i-1][j];//继承上一状态
    for(int j=k;j>=b[i].w;j--) dp[i][j]=max(dp[i][j],dp[pre[i]][j-b[i].w]+b[i].v);
    for(int j=1;j<=k;j++) ans=max(ans,dp[i][j]);
}
```

时间复杂度 $O(nm+mk)$。

#### Subtask #4

可以发现拼线段是为了找到能转移到线段 $i$ 的最大的线段 $j$ 的编号，考虑预处理这个信息。在排序之后使用前缀和加二分快速统计无权值线段的重量和价值。

总体时间复杂度 $O(n \log n +mk)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Segment{int l,r,v;long long w;}a[200005],b[5005];
int n,m,k,ans,cnt,ri[5005],pre[5005],sumv[200005],p[400005],dp[5005][5005];
long long sumw[200005];
bool cmp(const Segment &x,const Segment &y){return x.l<y.l;}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>a[i].l>>a[i].r>>a[i].w;
    for(int i=1;i<=m;i++) cin>>b[i].l>>b[i].r;
    sort(a+1,a+n+1,cmp),sort(b+1,b+m+1,cmp);
    for(int i=1;i<=n;i++){
        a[i].v=a[i].r-a[i].l+1;
        sumw[i]=sumw[i-1]+a[i].w;
        sumv[i]=sumv[i-1]+a[i].v;
        p[i*2-1]=a[i].l,p[i*2]=a[i].r;
    }
    for(int i=1;i<=m;i++){
        if(b[i].l>a[n].r||b[i].r<a[1].l) continue;
        int l=lower_bound(p+1,p+n*2+1,b[i].l)-p;
        int r=upper_bound(p+1,p+n*2+1,b[i].r)-p-1;
        if(l%2==1&&p[l]>b[i].r||r%2==0&&p[r]<b[i].l) continue;
        l=(l+1)/2,r=(r+1)/2,ri[i]=r;
        for(int j=1;j<=i-1;j++) if(ri[j]<l) pre[i]=j;
        b[i].w=sumw[r]-sumw[l-1];
        if(l!=r){
            b[i].v=sumv[r]-sumv[l-1]-a[r].v-a[l].v;
            b[i].v+=min(b[i].r,a[l].r)-max(b[i].l,a[l].l)+1;
            b[i].v+=min(b[i].r,a[r].r)-max(b[i].l,a[r].l)+1;
        }
        else b[i].v=min(b[i].r,a[l].r)-max(b[i].l,a[l].l)+1;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=k;j++) dp[i][j]=dp[i-1][j];
        for(int j=k;j>=b[i].w;j--){
            dp[i][j]=max(dp[i][j],dp[pre[i]][j-b[i].w]+b[i].v);
            ans=max(ans,dp[i][j]);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Resstifnurv (赞：5)

简单 DP 题。

由于题目保证了数轴上任意一个整点至多被红色线段覆盖一次、被蓝色线段覆盖一次，所以我们考虑将红色线段和蓝色线段分别按左端点从小到大排序，则它们的右端点也从小到大排序。

然后我们枚举每个蓝色线段，可以得知与它相交的红色线段成一段下标连续的区间（记为 $[l_i, r_i]$），且对于下标为 $i$，$j$ 的两条线段 $(i < j)$，满足 $l_i \le l_j$，$r_i \le r_j$。预处理出这些区间，可以用二分或者双指针解决。

预处理完所有 $l_i$，$r_i$ 之后，我们考虑维护 $pre_i$ 表示**下标最大的**不与蓝色线段 $i$ 有**相同的相交红色线段**的蓝色线段。这样，下标在 $(pre_i + 1, i)$ 范围内的蓝色线段都不能和 $i$ 一起选，因为这样就会导致有红色线段与多条蓝色线段相交。如果 $[1,i)$ 范围内的线段都不能和 $i$ 同时选，那么我们令 $pre_i = 0$，故初始设 $l_0 = 0$，$r_0 = 0$，便于判断。这一部分预处理也可以二分或双指针解决。

以上是预处理部分，复杂度 $O(n\operatorname{log}n)$。接下来就是 DP 部分。

不难发现，这时题目已经初具背包 DP 的雏形了，我们把每条蓝色线段看成一个物品，**价值** $w_i$ 为它与红色线段的交集的整点数，**重量** $v_i$ 为与它相交的红色线段的权值和。这两个都可以在预处理完 $l_i$，$r_i$ 后使用前缀和解决，具体实现见代码。

于是设 $f_{i,j}$ 表示当前考虑了前 $i$ 个物品并钦定选中第 $i$ 个物品，总重量不超过 $j$ 的最大价值。

于是有如下的 DP 式子：

$$
\large f_{i,j} = \operatorname{max}_{k = 0}^{pre_i} (f_{k,j-v_i} + w_i)
$$

这个 DP 的复杂度是 $O(m^2k)$ 的，但是我们发现这是一个非常经典的前缀 $\text{max}$ 形式，因此我们令 $g_{i,j} =\operatorname{max}_{k = 0}^{i} f_{k,j}$，则 DP 转化为：

$$
\large g_{i,j} = \operatorname{max}(g_{i-1,j},\ g_{pre_i,j-v_i}+w_i)
$$

答案即为 $g_{m,k}$。

总时间复杂度为 $O(n \operatorname{log}n + mk)$，足以通过。

代码：（已省略头文件与快读）

```cpp
int n, m, k;
const int N = 2e5 + 10;
const int M = 5e3 + 10;
struct RED{
    int L, R, val;
} A[N];
int sum[N], len[N];

struct BLUE{
    int L, R;
    int bg, ed, pre;
    int v, w;
} B[M];
int f[M][M];

void solve(){
    auto cmp_RED = [](RED &x, RED &y){
        return x.L < y.L;
    };
    auto cmp_BLUE = [](BLUE &x, BLUE &y){
        return x.L < y.L;
    };
    n = read(), m = read(), k = read();
    for(int i = 1; i <= n; i++){
        A[i].L = read(), A[i].R = read();
        A[i].val = read();
    }
    sort(A + 1, A + 1 + n, cmp_RED);
    for(int i = 1; i <= n; i++){
        sum[i] = sum[i - 1] + A[i].val;
        len[i] = len[i - 1] + A[i].R - A[i].L + 1;
    }
    for(int i = 1; i <= m; i++){
        B[i].L = read(), B[i].R = read();
    }
    sort(B + 1, B + 1 + m, cmp_BLUE);
    for(int i = 1; i <= m; i++){
        int l = 1, r = n, mid;
        while(l < r){
            mid = (l + r) >> 1;
            if(A[mid].R >= B[i].L) r = mid;
            else l = mid + 1;
        }
        B[i].bg = l;
        l = 1, r = n;
        while(l < r){
            mid = (l + r + 1) >> 1;
            if(A[mid].L <= B[i].R) l = mid;
            else r = mid - 1;
        }
        B[i].ed = l;
        if(B[i].bg > B[i].ed){
            B[i].v = 0;
            B[i].w = 0;
            continue;
        }
        B[i].v = sum[B[i].ed] - sum[B[i].bg - 1];
        if(B[i].bg == B[i].ed){
            B[i].w = min(A[B[i].bg].R, B[i].R) - max(A[B[i].bg].L, B[i].L) + 1;
        }
        else{
            B[i].w = len[B[i].ed - 1] - len[B[i].bg];
            B[i].w += min(A[B[i].bg].R, B[i].R) - max(A[B[i].bg].L, B[i].L) + 1;
            B[i].w += min(A[B[i].ed].R, B[i].R) - max(A[B[i].ed].L, B[i].L) + 1;
        }
    }
    B[0].bg = 0, B[0].ed = 0;
    for(int i = 1; i <= m; i++){
        assert(B[i - 1].bg <= B[i].bg);
        assert(B[i - 1].ed <= B[i].ed);
        int l = 0, r = i - 1, mid;
        while(l < r){
            mid = (l + r + 1) >> 1;
            if(B[mid].ed < B[i].bg) l = mid;
            else r = mid - 1;
        }
        B[i].pre = l;
    }
    // DP-part
    f[0][0] = 0;
    for(int i = 1; i <= m; i++){
        for(int j = 0; j <= k; j++){
            f[i][j] = f[i - 1][j];
            if(j >= B[i].v){
                f[i][j] = max(f[i][j], f[B[i].pre][j - B[i].v] + B[i].w);
            }
        }
    }
    printf("%d\n", f[m][k]);
}
```

---

## 作者：Moya_Rao (赞：3)

# 题目大意
在平面上给定 $n$ 条有权值的红色线段（第 $i$ 条线段的权值为 $w_i$）和 $m$ 条没有权值的蓝色线段，还给定一个正整数 $k$。  
其中，第 $i$ 条（满足 $1 \le i \le n$）红色线段的左端点为 $l_i$，右端点为 $r_i$。第 $j$ 条（满足 $1 \le j \le m$）蓝色线段的左端点为 $L_j$，右端点为 $R_j$。  
现在，你要选择出若干条蓝色线段（可以一条都不选），使得选出的蓝色线段满足下面两个条件：
- 给定的每条红色线段**至多**与你选择的 $1$ 条蓝色线段有交集。
- 所有和你选中的蓝色线段有交集的红色线段的权值之和不能超过 $k$。  
现在想知道，在满足这两个条件的前提下，你选择的蓝色线段和所有红色线段的交集长度至多能有多长，请输出这个长度。

注：如果称一条线段 $i$（左端点为 $l$，右端点为 $r$）与一条线段 $j$（左端点为 $L$，右端点为 $R$）有交集，当且仅当 $\max(l,L) \le \min(r,R)$。此时，它们的交集长度为 $\min(r,R)-\max(l,L)+1$。

# 思路
这次，我们边放代码边讲！

## 最开始的操作

在此题中，不难发现，在有权值和限制 $k$ 的情况下去找最优答案，显然是一个背包问题。  
在这里，我们令，**与这条蓝色线段有交集的红色线段的权值之和为这条蓝色线段的重量 $w$，与蓝色线段有交集的所有红色线段的交集长度之和为这条蓝色线段的价值 $v$**。

那么可以定义如下的结构体数组：
```cpp
struct line{int l,r,w,v;}a[200005],b[5005];
```
接下来，我们可以将 $a$ 数组与 $b$ 数组按照从小到大的编号排个序，即可有如下的 `cmp` 函数：
```cpp
bool cmp(line x1,line x2){return x1.l<x2.l;}
```

## 简单的预处理

现在，我们可以预处理一些东西，方便后面计算每条蓝色线段的重量与价值。

要预处理红色线段的：  
$v$ 的前缀和（我们定义一条红色线段的 $v$ 值为它的长度，则 $v$ 的前缀和就是数组 $sumv$），$w$ 的前缀和（即数组 $sumw$），还要拿个 $seg$ 数组把它对应的 $l$ 和 $r$ 挨个儿放进去。为什么呢？可以方便后面进行对应的二分查找求一个非常重要的东西。如果你想知道这个非常重要的东西是什么，就往后接着看吧。

那么，就有了这样的预处理代码：
```cpp
for(int i=1;i<=n;i++){
    a[i].v=a[i].r-a[i].l+1;
    sumv[i]=sumv[i-1]+a[i].v;
    sumw[i]=sumw[i-1]+a[i].w;
    seg[i*2-1]=a[i].l,seg[i*2]=a[i].r;
}
```

## 非常重要的东西

接下来，一个大大方便了背包的东西出现了，这就是我说的那个非常重要的东西——即一个 $pre$ 数组。

什么？这么重要的东西，竟然只是个 $pre$ 数组？别着急，先听 $pre$ 数组的定义：  
定义 $pre_i$ 表示右端点最大能够转移到第 $i$ 条蓝色线段的线段编号。或者可以理解为，最后一个完完全全在第 $i$ 条蓝色线段左边的蓝色线段的编号。也就是说，就算这条线段和所有与它相交的红色线段都拼接完了，第 $i$ 条线段也拼接完了，它还是在第 $i$ 条线段左边，且没有任何交集（哪怕只是一个点）的最大线段的编号。

那么，最后在做背包的时候，第 $i$ 条蓝色线段就可以直接从第 $pre_i$ 条蓝色线段转移过来了。

## 具体该怎么做

注：这一段的内容比较多，篇幅比较长，想学会本题的同学们请认认真真看完。

那么怎么求解这个 $pre$ 数组呢？而且还要求每条蓝线段的重量和价值啊，该怎么办？

没关系，我用一个 `for` 循环给你直接搞定！

首先循环，让 $i$ 从 $1$ 遍历到 $m$。

接着，我们判断一个东西：如果这条蓝色线段超过了所有红色线段的大范围，可以直接跳过。  
也就是这样一句 `if`：
```cpp
if(b[i].l>a[n].r||b[i].r<a[1].l)continue;
```

再来做一件事情：二分查找，就是在之前的 $seg$ 数组中进行二分查找。  
代码长这样，就两行：
```cpp
int L=lower_bound(seg+1,seg+2*n+1,b[i].l)-seg;
int R=upper_bound(seg+1,seg+2*n+1,b[i].r)-seg-1;
```

那如果没有任何红色线段和它有交集呢？那就不用管它了。因此加上这样一句话：
```cpp
if((L%2==1&&seg[L]>b[i].r)||(R%2==0&&seg[R]<b[i].l))continue;
```

接下来，就要进行还原了。  
因为现在的 $L$ 和 $R$ 都是它们在 $seg$ 数组中的位置，要把它们换成真正的线段编号，即这样：
```cpp
L=(L+1)/2,R=(R+1)/2;
```

还要给那个 $anyR$ 数组赋值，就是一个寻找 $pre$ 的东西：
```cpp
anyR[i]=R;
```

再，就是来找 $pre_i$ 啦，像这样就行：
```cpp
for(int j=0;j<i;j++)if(anyR[j]<L)pre[i]=j;
```

接着，统计这条蓝色线段的重量 $w$，这时 $sumw$ 的作用就出来了！
```cpp
b[i].w=sumw[R]-sumw[L-1];
```

最后就是来算这条蓝色线段的价值 $v$ 啦，这个得判断一下：  
如果 $L \ne R$，即这条蓝色线段与多条红色线段相交，那么得先加上完整的（用 $sumv$ 数组），再把不完整的依次加上；  
否则的话 $L = R$，直接搞出交集部分就可以啦。

代码如下：
```cpp
if(L!=R){
    b[i].v=sumv[R]-sumv[L-1]-a[L].v-a[R].v;
    b[i].v+=min(b[i].r,a[L].r)-max(b[i].l,a[L].l)+1;
    b[i].v+=min(b[i].r,a[R].r)-max(b[i].l,a[R].l)+1;
}
else b[i].v=min(b[i].r,a[L].r)-max(b[i].l,a[L].l)+1;
```

搞完这个，$pre$ 数组就被我们弄出来了。

## 最后的背包

最后的最后，就是个简单的背包啦，长这样：
```cpp
for(int i=1;i<=m;i++){
    for(int j=1;j<=k;j++)dp[i][j]=dp[i-1][j];
    for(int j=k;j>=b[i].w;j--){
        dp[i][j]=max(dp[i][j],dp[pre[i]][j-b[i].w]+b[i].v);
        ans=max(ans,dp[i][j]);
        }
    }
```

这样，$ans$ 也被我们求出来啦！

是不是还挺简单？

# 完整代码
刚才在思路部分给出的代码都是部分代码，而且没有注释哇，不好综合着看。  
现在我就把完整的代码给你们粘上吧，里边还有详细的注释呢！
```cpp
#include<bits/stdc++.h>
using namespace std;
struct line{int l,r,w,v;}a[200005],b[5005];
int n,m,k,sumv[200005],seg[400005];
int pre[5005],anyR[5005],dp[5005][5005],ans;
long long sumw[200005];
bool cmp(line x1,line x2){return x1.l<x2.l;}//自定义比较函数
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r>>a[i].w;
    for(int i=1;i<=m;i++)cin>>b[i].l>>b[i].r;
    sort(a+1,a+n+1,cmp);sort(b+1,b+m+1,cmp);//排序
    for(int i=1;i<=n;i++){
        a[i].v=a[i].r-a[i].l+1;//长度，亦称重量
        sumv[i]=sumv[i-1]+a[i].v;//v 的前缀和
        sumw[i]=sumw[i-1]+a[i].w;//w 的前缀和
        seg[i*2-1]=a[i].l,seg[i*2]=a[i].r;//存下来，方便后面二分查找
    }
    for(int i=1;i<=m;i++){
        if(b[i].l>a[n].r||b[i].r<a[1].l)continue;
        //如果这条蓝色线段超过了所有红色线段的大范围，跳过
        int L=lower_bound(seg+1,seg+2*n+1,b[i].l)-seg;//找第一个大于等于左端点的
        int R=upper_bound(seg+1,seg+2*n+1,b[i].r)-seg-1;//找最后一个小于等于左端点的
        if((L%2==1&&seg[L]>b[i].r)||(R%2==0&&seg[R]<b[i].l))continue;
        //如果这条蓝色线段完全没有触碰到任何红色线段，跳过
        L=(L+1)/2,R=(R+1)/2;//还原到真正的红色线段编号
        anyR[i]=R;
        for(int j=0;j<i;j++)if(anyR[j]<L)pre[i]=j;//更新 pre 数组
        b[i].w=sumw[R]-sumw[L-1];//权值之和
        if(L!=R){//碰到不止一条线段
            b[i].v=sumv[R]-sumv[L-1]-a[L].v-a[R].v;//先把完整的加进去
            b[i].v+=min(b[i].r,a[L].r)-max(b[i].l,a[L].l)+1;//左边破碎的
            b[i].v+=min(b[i].r,a[R].r)-max(b[i].l,a[R].l)+1;//右边破碎的
        }
        else b[i].v=min(b[i].r,a[L].r)-max(b[i].l,a[L].l)+1;//否则直接加上总的破碎的
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=k;j++)dp[i][j]=dp[i-1][j];//继承之前的
        for(int j=k;j>=b[i].w;j--){
            dp[i][j]=max(dp[i][j],dp[pre[i]][j-b[i].w]+b[i].v);//迭代更新
            ans=max(ans,dp[i][j]);//不断更新 ans
        }
    }//普通背包 DP
    cout<<ans;
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：2)

看到数据范围，猜测为 $\mathcal{O}(mk)$ dp。

先把蓝色/红色线段按照 $l,r$ 排序，因为不交，所以按照哪个排序没有关系。

可以大概构建一个 dp，$f_{i,j}$ 表示选到第 $i$ 根蓝线，相交红色线段权值之和为 $j$ 的整点数量最大值。

预处理的东西：

- 和蓝色线段 $i$ 相交的红色线段区间为 $[ll_i,rr_i]$。

这个处理是好想的，因为这样有助于统计与之相交的红色线段权值和、整点数量。

这个处理是好做的，需要二分一下即可。

- 和蓝色线段 $i$ 相交的红色线段权值和、整点数量。

这个肯定需要，处理就是利用上面的 $ll_i,rr_i$，以及红色线段的权值前缀和、长度前缀和，并且处理一下边界即可。

然后设计 dp 状态，发现两条蓝色线段可以交于同一条红色线段，这个是可能统计多次的，考虑记录这个事情，$f_{i,j,0/1}$ 表示选到第 $i$ 根蓝线，相交红色线段权值之和为 $j$，最右侧的相交红色线段是否为 $rr_i$ 的最大整点数量。这里只用记最后一根因为红色线段互补相交，而且红蓝线段是拍过序的。

转移是简单的，考虑 $f_{i,j,0/1}$ 的转移。

如果选择蓝线 $i$，可以从 $f_{i-1,j',0}$ 转移过来，或者当 $ll_i\ne rr_{i-1}$ 的时候从 $f_{i-1,j',1}$ 转移。其中 $j'$ 是 $j$ 减掉和 $i$ 相交的红线段权值。此时，第三维显然是 $1$。

如果不选择蓝线 $i$，转移和上面类似推理且几乎是普通背包，在此不再赘述。需要注意的是，即使不选 $i$，选择红色线段的右端点也仍然可能是 $i$ 所接触的最右边的红色线段。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid (l + r >> 1)
using namespace std;
const int N = 2e5 + 5, M = 5005;
int n, m, k, f[M][M][2], sum[N], l, r, pl, pr, ans, now;
int ll[M], rr[M], nod[M], Sum[M];
int cnt[N], nownod;
struct R{
	int l, r, w;
}a[N];
struct B{
	int l, r;
}b[M];
inline bool operator < (R x, R y){
	return x.l < y.l;
}
inline bool operator < (B x, B y){
	return x.l < y.l;
}
inline int findfir(int x){
	l = 1, r = n;
	int res = n + 1;
	while(l <= r){
		if(a[mid].l > x) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}
inline int findlst(int x){
	l = 1, r = n;
	int res = 0;
	while(l <= r){
		if(a[mid].r < x) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}
signed main(){
//	freopen("data.in", "r", stdin);
//	freopen("code.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &k);
	for(int i = 1; i <= n; i++){
		scanf("%lld%lld%lld", &a[i].l, &a[i].r, &a[i].w);
	}
	for(int i = 1; i <= m; i++){
		scanf("%lld%lld", &b[i].l, &b[i].r);
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
//	for(int i = 1; i <= n; i++){
//		printf("%lld %lld %lld\n", a[i].l, a[i].r, a[i].w);
//	}
//	for(int i = 1; i <= m; i++){
//		printf("%lld %lld\n", b[i].l, b[i].r);
//	}
	for(int i = 1; i <= n; i++){
		sum[i] = sum[i - 1] + a[i].w;
		cnt[i] = cnt[i - 1] + a[i].r - a[i].l + 1;
	}
	for(int i = 1; i <= m; i++){
		pl = findfir(b[i].l), pr = findlst(b[i].r);
		ll[i] = pl, rr[i] = pr;
		nod[i] = sum[pr] - sum[pl - 1];
		Sum[i] = cnt[pr] - cnt[pl - 1];
		pl--, pr++;
		if(pl && a[pl].r >= b[i].l){
			Sum[i] += a[pl].r - b[i].l + 1;
			nod[i] += a[pl].w;
			ll[i] = pl;
		}
		if(pr <= n && a[pr].l <= b[i].r){
			Sum[i] += b[i].r - a[pr].l + 1;
			nod[i] += a[pr].w;
			rr[i] = pr;
		}
	}
	for(int i = 1; i <= m; i++){
		for(int j = 0; j <= k; j++) f[i][j][0] = f[i - 1][j][0];
		for(int j = 0; j <= k; j++) f[i][j][rr[i - 1] == rr[i] ? 1 : 0] = max(f[i][j][rr[i - 1] == rr[i] ? 1 : 0], f[i - 1][j][1]);
		nownod = Sum[i], now = nod[i];
		for(int j = now; j <= k; j++) f[i][j][1] = max(f[i][j][1], f[i - 1][j - now][0] + nownod);
		if(ll[i] != rr[i - 1]){
			for(int j = now; j <= k; j++) f[i][j][1] = max(f[i][j][1], f[i - 1][j - now][1] + nownod);
		}
	}
	printf("%lld\n", max(f[m][k][0], f[m][k][1]));
	return 0;
}
```

---

## 作者：Richard_Whr (赞：1)

定位是常规背包类动态规划。

容易发现对于蓝色线段两两不交，红色线段两两不交。

可以想到给他们排序，从左向右动态规划。

观察数据范围复杂度应该是 $O(m \times k)$ 的，很像个背包，往这个方向考虑。

设 $f_{i,j}$ 表示前 $i$ 条蓝色线段，使用了 $j$ 的体积，可以获得的最大交集大小。

转移的时候发现需要解决以下几个问题：

- 每条红色线段仅能被一条蓝色线段覆盖；

- 每条蓝色线段选中后，体积（有交的红色线段权值和），价值（有交的红色线段交集大小）；

为解决以上问题，想到每条蓝色线段对应的红色线段是一个区间，且相邻的最多有一个交点，预处理出以下数组辅助动态规划。

- $p_i,q_i$，表示每条蓝色线段对应的红色线段区间；

- $v_i$，蓝线段“体积”；

- $w_i$，蓝线段“价值”；

由于已经排好了序，因此随着 $i$ 的增加， $p_i,q_i$ 也会单调不降，直接双指针处理以上数组好了。

这里复杂度为 $O(n + m)$。

接着设计 $dp$ 状态和列出转移方程。

为方便转移，向状态加入限制，必须选 $i$。

转移如下：
 
 $$f_{i,j}=\max_{q[k]<p[i]}\{f_{k,j-v_i}+w_i\}$$

是一个前缀 $\max$，开一个辅助数组即可，对于 $k$ 的取值也可以双指针预处理。

难点其实在于处理上面几个辅助数组，双指针注意细节。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,M=5e3+10;
int f[M][M];
int s[M][M];
int B[M];
struct Rseg
{
	int l,r,c;
	bool operator<(const Rseg &t)const
	{
		return l<t.l;
	}
}rs[N];
struct Bseg
{
	int l,r;
	bool operator<(const Bseg &t)const
	{
		return l<t.l;
	}
}bs[N];
int v[M],w[M],p[M],q[M];
int n,m,V;

int calc(int i,int j)
{
	int len=min(bs[i].r,rs[j].r)-max(bs[i].l,rs[j].l)+1;
	return max(len,0);
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m>>V;
	for(int i=1,l,r,c;i<=n;i++) 
	{
		cin>>l>>r>>c;
		rs[i]={l,r,c};
	}
	
	sort(rs+1,rs+1+n);
	
	for(int i=1,L,R;i<=m;i++)
	{
		cin>>L>>R;
		bs[i]={L,R};
	}
	
	sort(bs+1,bs+1+m);
	
	for(int i=1;i<=m;i++)
	{
		int l=bs[i].l,r=bs[i].r;
		p[i]=q[i-1];
		while(p[i]<=n && rs[p[i]].r<l) p[i]++;
		q[i]=p[i];
		while(q[i]<=n && rs[q[i]].l<=r) v[i]+=rs[q[i]].c,w[i]+=calc(i,q[i]),q[i]++;
		q[i]--; 
	}
	
	int j=0;
	for(int i=1;i<=m;i++)
	{
		while(j<=m && q[j+1]<p[i]) j++;
		if(j>m) j--;
		B[i]=j;
	}
	
	int res=0;
	f[0][0]=0;
	for(int i=1;i<=m;i++)
	{
		for(int j=v[i];j<=V;j++)
		{
			f[i][j]=s[B[i]][j-v[i]]+w[i];
			res=max(res,f[i][j]);
		}
		for(int j=0;j<=V;j++) s[i][j]=max(s[i-1][j],f[i][j]);
	}
	cout<<res<<"\n";
	return 0;
}
```

---

## 作者：Rindong (赞：0)

# 题意

有 $n$ 条红色线段和 $m$ 条蓝色线段，并且所有同颜色的线段两两间没有交集。红色线段有权重，蓝色没有。选出若干蓝色线段满足：

 - 在每一条红色线段内至多有一条蓝色线段被选中
 - 与选出的蓝色线段有交集的红色线段权重和不超过 $k$

求满足这样情况下，最多的红蓝线段交集整点数是多少。

# 思路

首先注意到线段值域较大，考虑将所有红蓝线段离散化后重新映射下标。

然后发现蓝色线段的数量 $m \le 5000$ ，权重的限制 $k \le 5000$ ，对于每条蓝色线段来说只有**选或不选**，这就和我们学过的**01背包**非常相似了！我们可以把权重视为限制，设 $dp[i][j][k]$ 表示以第 $i$ 条线段结尾，权重限制为 $j$ ，当 $k = 0$ 时代表不选第 $i$ 条，$k = 1$ 时选择第 $i$ 条的最大交集整点数。于是我们有转移方程：

$$
dp[i][j][k] = 
\begin{cases}
\max(dp[i - 1][j][0], dp[i - 1][j][1]), & k = 0 \\
\max(dp[l][j][0], dp[l][j][1]) + P_i, & k = 1
\end{cases}
$$

其中 $l$ 表示 $< i$ 且不与 $i$ 冲突（也就是和 $i$ 不存在公共的红色线段）的最后一条线段。由于题目给的线段有非常好的性质，那么我们可以将线段按任意端点从小到大排序，就可以使用二分查找了！这样这道题的主要思路就讲完了，具体细节来看代码吧。

# 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define ll long long
const int N = 200010, M = 5005;
struct Red {
	int l, r, w;
	bool operator< (const Red& other) const {
		return l < other.l;
	}
} red[N], blue[M];
ll dp[M][M][2] = { 0 };
int dis[(N + M) << 1], dcnt = 0;
int Kpres[N];
ll Lpres[N];
int get_ind(int val) {
	int l = 1, r = dcnt, mid;
	while (l < r) {
		mid = l + r >> 1;
		if (dis[mid] >= val) r = mid;
		else l = mid + 1;
	}
	return r;
}
int n, m, k;
//找到跟第 i 条线段冲突的第一个下标
int get_rgL(int lef) {
	int l = 0, r = n + 1, mid;
	while (l < r) {
		mid = l + r >> 1;
		if (red[mid].r >= lef) r = mid;
		else l = mid + 1;
	}
	return r;
}
//找到跟第 i 条线段冲突的最后一个下标
int get_rgR(int rig) {
	int l = 0, r = n + 1, mid;
	while (l < r) {
		mid = l + r + 1 >> 1;
		if (red[mid].l <= rig) l = mid;
		else r = mid - 1;
	}
	return l;
}
int unique() {
	int ret = 0, las = -1;
	for (int i = 1; i <= dcnt; i++) {
		if (dis[i] != las)
			dis[++ret] = dis[i];
		las = dis[i];
	}
	return ret;
}
//两条线段的交集整点数
inline int get_inter(int l1, int r1, int l2, int r2) {
	return max(0, min(r1, r2) - max(l1, l2) + 1);
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		int l, r, w;
		scanf("%d%d%d", &l, &r, &w);
		red[i] = { l, r, w };
		dis[++dcnt] = l, dis[++dcnt] = r;
	}
	for (int i = 1; i <= m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		blue[i] = { l, r, 0 };
		dis[++dcnt] = l, dis[++dcnt] = r;
	}
	sort(dis + 1, dis + 1 + dcnt);
	dcnt = unique();
	for (int i = 1; i <= n; i++)
		red[i].l = get_ind(red[i].l), red[i].r = get_ind(red[i].r);
	sort(red + 1, red + 1 + n);
	Kpres[0] = Lpres[0] = 0;
	for (int i = 1; i <= n; i++) {
		// Kpres 是权重的前缀和，Lpres 是长度前缀和
		Kpres[i] = Kpres[i - 1] + red[i].w;
		Lpres[i] = Lpres[i - 1] + (dis[red[i].r] - dis[red[i].l] + 1);
	}
	for (int i = 1; i <= m; i++)
		blue[i].l = get_ind(blue[i].l), blue[i].r = get_ind(blue[i].r);
	sort(blue + 1, blue + 1 + m);
	//放置哨兵，防止二分进行错误的命中
	red[0] = blue[0] = { -2, -1, 0 }, red[n + 1] = blue[m + 1] = { 10000000, 10000000 + 1, 0 };
	ll ans = 0;
	for (int i = 1; i <= m; i++) {
		int l = get_rgL(blue[i].l), r = get_rgR(blue[i].r);
		if (l > r) memcpy(dp[i], dp[i - 1], sizeof dp[i]);
		else {
			// p 是价值，w 是重量
			ll p = 0, w = Kpres[r] - Kpres[l - 1];
			if (l + 1 <= r - 1) p += Lpres[r - 1] - Lpres[l];
			if (l != r) p += get_inter(dis[blue[i].l], dis[blue[i].r],
				dis[red[r].l], dis[red[r].r]);
			p += get_inter(dis[blue[i].l], dis[blue[i].r],
				dis[red[l].l], dis[red[l].r]);
			int L = 0, R = m + 1, mid;
			//右端点大于等于最左边一项的右端点 
			while (L < R) {
				mid = L + R >> 1;
				if (blue[mid].r >= red[l].l) R = mid;
				else L = mid + 1;
			}
			r = R - 1;
			for (int j = 0; j <= k; j++) {
				dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1]);
				dp[i][j][1] = dp[i][j][0];
				if (j >= w)
					dp[i][j][1] = max(dp[i][j][1], max(dp[r][j - w][0], dp[r][j - w][1]) + p);
				ans = max(ans, max(dp[i][j][0], dp[i][j][1]));
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：modfish_ (赞：0)

## 思路
一眼看出这是一个背包。

首先，每条蓝色线段所占的空间和其价值是可以计算的：先把红色、蓝色线段按左端点排序。维护一个红色线段的指针，枚举蓝色线段，指针不停跟着跳跃。容易证明，与当前蓝色线段相交的红色线段的区间的左、右端点均单调不降，所以可以用指针维护，复杂度 $O(n+m)$。

之后，我们对于每一条蓝色线段 $i$，找出他前面最近的一条蓝色线段 $j$，使得 $i,j$ 不与同一条红色线段相交，记 $pre_i=j$。

然后，设 $dp_{i,j}$ 表示当前枚举到第 $i$ 条蓝色线段，已经使用的容量为 $j$ 的最大价值。显然，对于 $i$，只有选或不选两种情况，则：

$$dp_{i,j}=\max(dp_{i-1,j},dp_{pre_i,j-v_i}+w_i)$$

其中 $v_i,w_i$ 是第 $i$ 条蓝色线段占用的空间和价值。时间复杂度 $O(n+mk)$。


```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 2e5 + 5, maxm = 5005;

struct node{
	int l, r;
	ll w;
}rs[maxn], bs[maxm];
ll V[maxm], W[maxm], dp[maxm][maxm];
int frs[maxm], las[maxm], pre[maxm];

bool cmp(node x, node y){
	return x.l < y.l;
}
int inter(node x, node y){
	return max(min(x.r, y.r) - max(x.l, y.l) + 1, 0);
}

int main(){
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i ++) scanf("%d %d %lld", &rs[i].l, &rs[i].r, &rs[i].w);
	for(int i = 1; i <= m; i ++) scanf("%d %d", &bs[i].l, &bs[i].r);
	sort(rs + 1, rs + n + 1, cmp);
	sort(bs + 1, bs + m + 1, cmp);
	int p = 1;
	for(int i = 1; i <= m; i ++){
		while(p <= n && rs[p].r < bs[i].l && !inter(rs[p], bs[i])) p ++;
		if(inter(rs[p], bs[i])) frs[i] = p;
		while(p <= n && inter(rs[p], bs[i])) V[i] += rs[p].w, W[i] += inter(rs[p], bs[i]), p ++;
		p --;
		if(inter(rs[p], bs[i])) las[i] = p;
	}
	for(int i = 1; i <= m; i ++){
		for(int j = i - 1; j >= 0; j --){
			if(max(frs[i], frs[j]) > min(las[i], las[j])){
				pre[i] = j;
				break;
			}
		}
	}
	for(int i = 1; i <= m; i ++){
		for(int j = 0; j <= k; j ++){
			if(j >= V[i]) dp[i][j] = max(dp[i][j], dp[pre[i]][j - V[i]] + W[i]);
			dp[i][j] = max(dp[i][j], dp[i - 1][j]);
		}
	}
	printf("%lld\n", dp[m][k]);
	return 0;
}
```

---

