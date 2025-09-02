# 「RdOI R3.5」RMSQ

## 题目描述

给出一个长度为 $m$ 的**排列** $b$ 和一个长度为 $n$ 的**序列** $a$。

如果一个序列 $S$，满足其按位置从左到右依次匹配 $b$ 的一个区间从左到右的位置，那么我们说 $S$ 是一个「优美序列」。

给出 $q$ 次询问。每次询问给出两个整数 $l$ 和 $r$。你需要找到一个 $a$ 的 $[l,r]$ 子区间中的一个最长的满足「优美序列」条件的子序列长度。注意子序列可以不连续。

## 说明/提示

### 样例解释

$\mathit{lastans}$ 解密后的询问为：

```plain
1 3
1 4
2 4
2 5
2 6
1 6
```

### 数据范围

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|c|} \hline
\textbf{Subtask} & \textbf{分值} & \bm{{n,m\le}} &\bm{{q\le}} & \bm{{T=}} & \textbf{特殊性质} & \textbf{Subtask 依赖}\cr\hline
1 & 10 & 100 & 10^4 & 1 & \textbf{A} & -\cr\hline
2 & 15 & 10^5 & 10^5 & 1 & \textbf{A} & 1\cr\hline
3 & 30 & 3\times 10^5 & 10^6 & 0 & - & -\cr\hline
4 & 45 & 3\times 10^5 & 10^6 & 1 & - & 2,3\cr\hline
\end{array}
$$

- 特殊性质 $\textbf{A}$：保证 $a_i,b_i,l,r$ 在数据范围内均匀随机。

对于 $100\%$ 的数据，$1\le l\le r\le n\le 3\times 10^5$，$1\le a_i\le m\le 3\times 10^5$，$1\le q \le 1\times 10^6$，$T \in \{0,1\}$。


## 样例 #1

### 输入

```
4 6 6 1
1 2 3 4
1 2 3 2 3 4
1 3
2 7
1 7
0 7
0 4
2 5```

### 输出

```
3
3
2
2
3
4```

# 题解

## 作者：minstdfx (赞：9)

~~不要在意我用讲评的稿子来糊题解~~

~~不要吐槽退役选手整出来的非常不专业的讲稿~~

>“那么，跳过中场休息，我们来讲最后一题。”

## 0x00 题意观察
- 给定两个序列，值域在 $[1,m]$。
- $B$ 是一个排列，$A$ 长度为 $n$。
- 多次询问，每次询问 $A$ 的一个子区间，在子区间里找到最长的一个子序列，使得它是 $B$ 的子串。

那么很显然第一下我们要做的就是按照给定的 $B$ 重新编号，使得 $A$ 中任意两个元素在 $B$ 中的**相对位置不变**，同时使得 $B$ 变为**升序**。

换句话说，把 $A$ 中的所有数换成 $B$ 中它的下标。

这样的话，问题转化为在 $A$ 的子区间内找最长子序列，使得它是连续的一段递增整数。

举个例子：  
$\text{\tt\textcolor{blue}{B}:\textcolor{blue}{1 2 5 4 3}}$  
$\text{\tt\textcolor{red}{A}:\textcolor{red}{4 2 5 1 4 2 3}}$  
变换后：  
$\text{\tt\textcolor{purple}{A}:\textcolor{purple}{4 2 3 1 4 2 5}}$

## 0x01 解题思路
前注：下文中 `dp` 代表「动态规划算法」时不使用 $\LaTeX$，代表「代码中的数组」时使用。

考虑暴力每次以 $O(l)$ 复杂度当做 dp 做，其中 $l$ 为当前询问区间长度。

从左往右进行动态规划，记 $ls_i$ 代表 dp 到当前位置的时候**值** $i$ 最后一次出现的**位置**。
```cpp
for(int i = 1; i <= n; ++i){
    dp[i] = dp[ls[a[i] − 1]] + 1;
    ans = max(ans, dp[i]);
    ls[a[i]] = i;
}
```

复杂度 $O(qn)$。可惜~~没有部分分~~现在有了，期望得分 10。

一看题目其实是个莫队板子，只是在线，但是有离线部分分，期望得分 40（加上暴力）。

---

考虑一种特殊的分块，求出每个可能的“完整块区间”（即整块）的答案，对于不在完整块中的部分，类比莫队，向左向右扩展区间，那么向左向右都只会最多扩展一个区间长度。显然如果预处理得当复杂度可以接受 ~~（然而要卡常）~~。

稍稍考虑一下这个过程，首先处理出：
- $bel_i$：每个位置所属的块
- $pans_{l,r}$：两个完整块之间的答案
- $ls_i$：$i$ 左边离它最近的值为 $a_i-1$ 的下标
- $rs_i$：$i$ 右边离它最近的值为 $a_i+1$ 的下标

对于区间没有包含完整块的直接暴力（显然长度最大也就两倍块长）。代码就不放了，和前面的暴力没区别。

包含完整块的，取最接近它的**整块子区间**然后扩展。  
先挪动右端点，考虑右边增加的元素可能的贡献。贡献来自两处:  
- 以完整块中元素为末端点的区间  
- 以右端点挪动经过的元素为末端点的区间  

（有不理解的可以考虑 dp 的过程，本质上是考虑“如果暴力 dp 到这一位了会怎么更新”）

对于第二种，直接在向右扩展时顺便记录一下即可，做起来非常容易，就不细讲了。  

---

```cpp
memset(tmp, 0, sizeof(int) * (m + 1));
for(int i = 1; i <= n; ++i)
    ls[i] = tmp[a[i] − 1], tmp[a[i]] = i;
memset(tmp, 0, sizeof(int) * (m+1));
for(int i = n; i >= 1; −−i)
    rs[i] = tmp[a[i] + 1], tmp[a[i]] = i;
for(int l = 1; l <= n; l += blsize) //prel 的处理 
{
    ans = 0;
    int *const dp = predp[bel[l]];
    memset(dp, 0, sizeof(int) * (n + 1)); //清空
    for(int r = l; r <= n; ++ r)
    {
        dp[r] = dp[ls[r]] + 1;
        ans < dp[r] ? ans = dp[r] : 114514; //（
        if(r == n || bel[r] != bel[r + 1])
        //dp 到末尾了记一下
        blkans[bel[l]][bel[r]] = ans;
    }
}
```
---
那么对于第一种呢？靠现有的东西基本没法维护。  
如果暴力，那么这一段是一个暴力 dp 的收尾工作，考虑能不能直接跳过前面的 dp 阶段直接处理这一小段的贡献。

发现可以。

注意到这一段 dp 过程中的左端点一定是某个块的左端点。  
维护 $prel_{bl,r}$ 代表对从第 $bl$ 个块的左端点到数列末尾这个区间进行 dp 时的 $dp$ 数组。  
即，左端点在第 $bl$ 个块开头或后边，以 $r$ 结尾的最长满足条件序列长度。

同理，维护 $prer_{bl,l}$ 代表左端点为 $l$，右端点在第 $bl$ 个块末尾或前边的最长满足条件序列长度。

方便起见，我们反过来维护 $dp$ 数组。
维护一个 $f_i$ 代表**当前区间内**，**反向**的 $dp$ 数组，即在当前区间内以 $i$ 值开头的最长满足要求的子序列。  
每当在右边插入一个数，考虑它对左边的所有数 $f_i$ 的影响。
根据定义，对于每个 $i$，有：  
$$f(a_i+1-prel_{bel(l),i})=\max\{f(a_i+1-prel_{bel(l),i}),prel_{bel(l),i}\}$$
这个好理解，用预处理出来的信息去维护当前区间的 $f$。

也就是说，向右扩展时，我们发现贡献来自两处：

- 整块到右散块的贡献；
- 右散块中一个元素到另一个元素的贡献。

那么向左移动区间的过程呢？同理。注意要考虑**左边扩张的区间**和右边**已经扩张**的非完整块部分一起造成影响。  
我们发现贡献来自三处：

- 左散块到整块的贡献；
- 左散块中一个元素到另一个元素的贡献。
- 左散块到右散块的贡献。
$$f(a_i)=\max\{f(a_i),f(a_i+1)+1,prer_{bel(r),i}\}$$
分别对应三种贡献，很好理解。
## 0x02 注意事项&复杂度分析
- 注意如果两个 $n\sqrt n$ 长度的预处理数组分开开会 MLE。考虑开在一起，由于 `prel[bl+1]` 与 `prer[bl]` 的第二维下标不重合，可以据此压缩。
- 注意撤销操作不能直接 `memset` 哦，会挂 TLE 的。
- 安排一个快速的 IO，并且不要轻易刷新缓冲区，无论是加速过的 `iostream` 还是带刷新的模板。

复杂度：  
时间 $O((n+q)\sqrt n)$ （块长取 $\sqrt n$）。  
空间 $O(n\sqrt n)$。

## 0x03 引用资料

无。

各位可以在月赛[讲评页面](https://class.luogu.com.cn/course/lgr101)下载到讲稿。

验题代码：
```cpp
#include <bits/stdc++.h>
#include "wdoi-fastio.hpp" // 省略头文件
#define cin fio
#define cout fio
#define endl _fios::endl
fast_iostream<> fio;
using namespace std;
const int maxn=3e5+4,maxsqrtn=1304;
int n,m,q;// as given.
int a[maxn],b[maxn],p[maxn];// as above.
// the array p will be used over and over again./tyt
int ans;// lastans
int ql,qr;// l and r for each query
int blsize;// size of blocks
int *const tmp=p;//别名（逃
int ls[maxn],rs[maxn];
int blkans[maxsqrtn][maxsqrtn],bel[maxn];//分块基操
int predp[maxsqrtn][maxn];//prel,prer
inline int max(int a,int b) { return a<b?b:a; } 

int main()
{
    cin>>m>>n>>q;
    blsize=sqrt(n)*0.8;
    for(register int i=1;i<=m;++i) cin>>b[i],p[b[i]]=i;
    for(register int i=1;i<=n;++i) cin>>a[i],a[i]=p[a[i]];
    for(int i=1;i<=n;++i)
        bel[i]=(i-1)/blsize+1;
    // 2nk+2ql, k=Number of blocks, l = length of each block
    memset(tmp,0,sizeof(int)*(m+1));
    for(int i=1;i<=n;++i)
        ls[i]=tmp[a[i]-1],tmp[a[i]]=i;
    memset(tmp,0,sizeof(int)*(m+1));
    for(int i=n;i>=1;--i)
        rs[i]=tmp[a[i]+1],tmp[a[i]]=i;
    for(int l=1;l<=n;l+=blsize)// prel的处理
    {
        ans=0;
        int *const dp=predp[bel[l]];
        memset(dp,0,sizeof(int)*(n+1));//清空
        for(int r=l;r<=n;++r)
        {
            dp[r]=dp[ls[r]]+1;
            ans<dp[r]?ans=dp[r]:114514;//不要在意（
            if(r==n || bel[r]!=bel[r+1]) //dp到末尾了记一下
                blkans[bel[l]][bel[r]]=ans;
        }
    }
    for(int i=1;i+blsize-1<=n;i+=blsize)
    {
        int r=i+blsize-1;//prer
        int *const dp=predp[bel[r]+1];
        //不能简单的直接使用dp数组并清空，否则会影响到前面的prel
        //当然你算好了哪些是prer哪些是prel也行
        //注意一下，本来求的是prer[bl][i]
        //这里存在predp[bl+1][i]的目的是防止重叠
        //当然由于小于两个块长时暴力所以你写predp[bl][i]也没关系
        //但是这样不好（
        //我一开始验题的时候就是这么写的，现在重构还是得改改
        memset(p,0,sizeof(int)*(n+1));
        for(int l=r;l;--l)
            p[l]=p[rs[l]]+1;
        for(int l=r;l;--l)
            dp[l]=p[l];//同理的dp
    }
    ans=0;
    memset(p,0,sizeof(p));//清一清
    int *const dp=p;
    while(q--)
    {
        cin>>ql>>qr;
        ql^=ans,qr^=ans;
        int lbel=bel[ql]+1,rbel=bel[qr]-1;
        if(lbel<=rbel)//扩展答案
        {
            ans=blkans[lbel][rbel];
            for(int i=rbel*blsize+1;i<=qr;++i)//move right bound
                ans=max(ans,dp[a[i]+1-predp[lbel][i]]=max(dp[a[i]+1-predp[lbel][i]],predp[lbel][i])); 
            for(int i=(lbel*blsize-blsize);i>=ql;--i)//move left bound
            {
                ans=max(ans,dp[a[i]]=max(dp[a[i]],
                    max(
                        predp[rbel+1][i],
                        dp[a[i]+1]+1
                    )
                ));
            }
            //注意直接memset清空会T
            for(int i=rbel*blsize+1;i<=qr;++i) dp[a[i]+1-predp[lbel][i]]=0;
            for(int i=(lbel*blsize-blsize);i>=ql;--i) dp[a[i]]=0;
            cout<<ans<<"\n";//别endl
        }
        else //暴力
        {
            ans=0;
            for(int i=ql;i<=qr;++i)
                if(dp[a[i]]<dp[a[i]-1]+1)
                    dp[a[i]]=max(dp[a[i]],dp[a[i]-1]+1),
                    ans=max(ans,dp[a[i]]);
            for(int i=ql;i<=qr;++i) dp[a[i]]=0;
            // 注意撤销操作不能直接memset哦，会挂的
            cout<<ans<<"\n";
        }
    }
    fio.flush();
    return 0;
}
```

---

## 作者：yzy1 (赞：9)

这里是出题人官方题解。

### 超级大暴力

我们先考虑暴力咋做，首先我们可以把 $b$ 序列重编个号，设 $dp(i)$ 代表以下标 $i$ 结尾的最长优美序列长度。则有个很显然的 dp：

$$
dp(i)=\max_{j=1}^{i-1}dp(j)+1\ (a_i=a_j+1).
$$

直接 $O(qn^2)$ 搞就行。

### 大暴力

这东西显然满足单调性，我们记录 $lst(i)$ 代表最后一次出现值 $i$ 的下标：

$$
dp(i)=dp(lst(a_i))+1\\
lst(a_i)=i.
$$

即可优化为 $O(qn)$。

### 暴力

我们发现，假如你当前处理的区间是 $[l,r]$，询问的区间是 $[l,r+1]$，我们可以根据当前的 $dp$ 值和 $lst$ 值很方便地转移到询问区间。但是如果询问的区间是 $[l+1,r]$，处理起来就有点麻烦了。你发现这玩意就是回滚莫队的套路，直接拿回滚莫队做就行，复杂度 $O(n \sqrt n)$。

### 正解

我们可以用类似莫队的思想，写一个支持在线的算法。

考虑分块，我们把序列分成 $\sqrt n$ 个块。预处理出询问第 $l$ 个整块到第 $r$ 个整块的答案 $preans(l,r)$，询问后 $r$ 个整块的 dp 数组 $pref(r,i)$。

同时，我们把那个 dp 反过来，设 $dp'(i)$ 为以下标 $i$ 开头的最长优美序列长度，转移式就会变成这样：
$$
dp'(i)=\max_{j=i+1}^n dp(j)+1\ (a_i=a_j-1).
$$
同样优化一下，用这个反过来的 dp 预处理出询问前 $l$ 个块的反向 dp 数组 $preg(l,i)$。

询问的时候分两种情况，当询问区间长度 $\le 2\sqrt n$ 时直接暴力做。否则我们采用一个最接近的整块 $[bl_l,bl_r]$ 作为初始区间，然后先向右，再向左扩展区间。

向右扩展时，我们发现贡献来自两处：

- 整块到右散块的贡献；
- 右散块中一个元素到另一个元素的贡献。

对于第一种，我们直接用预处理出来的 $pref(bl_l,i)$ 来查询即可。对于第二种，直接在向右扩展时顺便记录一下即可。

向左扩展时，我们发现贡献来自三处：

- 左散块到整块的贡献；
- 左散块中一个元素到另一个元素的贡献。
- 左散块到右散块的贡献。

对于前两种，处理起来和右散块基本一致，麻烦就在于最后一种，这里有一个很方便的解决方法：在移动左右端点的同时，维护一个数组 $f(i)$ 代表以**值** $i$ 开头的最长优美序列长度，则移动右端点至 $i$ 时，有如下转移：
$$
f(a_i-pref(bl_l,i)+1) = \max\{f(a_i-pref(bl_l,i)+1),pref(bl_l,i)\}.
$$
移动左端点至 $i$ 时，有如下转移：
$$
f(a_i)=\max\{f(a_i),preg(bl_r,i),f(a_i+1)+1\}.
$$
这个式子很好理解，大括号里的三个元素分别对应三处不同的贡献位置。

需要强调的一点是，输出答案后，不要用 `memset` 清空 $f$ 数组，要手动记录用过的下标清零。

至此，我们以时间 $O((n+q)\sqrt n)$，空间 $O(n\sqrt n)$ 的复杂度，解决了这个问题。

---

## 作者：vectorwyx (赞：6)

~~怎么你们的空间都是单根号的~~

由于 $b$ 是排列，所以可以对 $a$ 做一个置换，等价于求置换后的形如 $x,x+1,x+2\dots$ 的最长子序列。

如果是对整个序列，有个很简单的 dp 是令 $f_i$ 表示以 $i$ 为结尾的最优子序列长度，则 $f_i=f_{\mathbb{pre}_i}+1$，其中 $\mathbb{pre}_i$ 表示 $i$ 往前第一个值为 $a_i-1$ 的位置，如果没有则为 $0$。默认 $f_0=0$。这样子的复杂度是 $O(n)$ 的。

对于区间询问，强制在线，考虑一手分块。令块长为 $B$，以每个块的左端点为起点向右进行上述 dp，同时预处理出 $F(i,j)$ 表示从第 $i$ 个块到第 $j$ 个块对应的子区间的答案（$i\le j$）。

那么在处理询问 $[l,r]$ 时，如果 $l,r$ 在同一个块内我们直接暴力 dp，否则 $[l,r]$ 一定可以划分为两个散块和若干个整块，由于我们已经预处理出了整块内部的答案，问题就只剩下散块里的点对答案的影响。最直接的思路是，求出以散点为开头/结尾的最优子序列长度，然而左右端点均不固定，我们没法预处理，直接 dp 也很难降低复杂度。

不过我们注意到考虑散块和不考虑散块的答案最多相差 $2B$，于是可以把最优化削弱为判定。即，不去求以某个散点为开头/结尾的最优子序列长度具体是多少，而是退而求其次去判断是否存在一个长度为 $k$ 的子序列。如果能做到快速判断，我们只需要记录当前答案 $ans$，遍历散点，以右边的散点为例，判断以它为结尾是否存在一个长度为 $k$ 的被这个区间包含的子序列，如果是就把答案加一，重复这一过程，否则换下一个散点。

至于如何判定，这里其实隐含着一个树形结构，考虑把 $i$ 向 $\mathbb{pre}_i$ 连边，那么 $0\sim n$ 构成了一棵以 $0$ 为根的树，以 $i$ 为结尾长度为 $k$ 的优美子序列其实就是一条以 $i$ 为底端长度为 $k$ 的链。于是我们只需要看看这条链是否在 $[l,r]$ 内，等价于求 $k$ 级祖先。使用长剖即可做到 $O(n\log n)-O(1)$。左边的散点同理，只需要把 $i$ 向 $\mathbb{suf}_i$ 连边，其中 $\mathbb{suf}_i$ 是 $i$ 向右第一个值为 $a_i+1$ 的位置，若没有则为 $n+1$。

至此，预处理的时间复杂度是 $O(\frac{n^2}{B}+n\log n)$，空间复杂度是 $O(\frac{n^2}{B^2}+n\log n)$；回答询问的时间复杂度是 $O(qB)$。取 $B=\frac{n}{\sqrt{q}}$ 即可，总时间复杂度为 $O(n\sqrt{q}+n\log n)$，空间复杂度为 $O(q+n\log n)$，完美。

（顺带说一句，其实这个手法和线性空间区间众数是一样的，详见 P5048。）


代码如下（打字不易，点个赞再走吧QAQ，非常感谢！）：
```cpp
#include<bits/stdc++.h>
#define vectorwyx maze
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define gtc getchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
template<typename T> void out(T *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=3e5+5,B=200,M=N/B+2;
// const int N=105,B=2,M=N/B+2;
namespace Pool{
int pool[N<<2],id;
int* get(int len){
    id+=len;
    int* ret=&pool[id];
    id+=len;
    re ret;
}
}
int a[N],n,m,q,mp[N];

namespace Tree{
vector<int> e[N];
int fa[N][20],dep[N],mxd[N],top[N],son[N],lg[N];
int* f[N];
void add(int x,int y){
    // printf("add(%d,%d)\n",x,y);
    e[y].pb(x);fa[x][0]=y;
}
void dfs1(int x){
    // printf("dfs1(%d)\n",x);
    fo(i,1,lg[n]){
        if(fa[x][i-1]==-1) fa[x][i]=-1;
        else fa[x][i]=fa[fa[x][i-1]][i-1];
    }
    mxd[x]=dep[x];
    for(int i:e[x]){
        dep[i]=dep[x]+1;
        dfs1(i);
        if(mxd[i]>mxd[x]) son[x]=i,mxd[x]=mxd[i];        
    }
    // printf("son[%d]=%d\n",x,son[x]);
}
void dfs2(int x){
    if(x==top[x]){
        f[x]=Pool::get(mxd[x]-dep[x]+1);
        int y=x;
        fo(i,1,mxd[x]-dep[x]){
            if(y==-1) f[x][-i]=y;
            else f[x][-i]=(y=fa[y][0]);
        }
    }
    f[top[x]][dep[x]-dep[top[x]]]=x;
    for(int i:e[x]){
        if(i==son[x]) top[i]=top[x];
        else top[i]=i;
        dfs2(i);
    }
    // if(x==top[x]) cout<<x<<":",out(f[x],dep[x]-mxd[x],mxd[x]-dep[x]);
}
int ask(int x,int k){
    // printf("ask(%d,%d)\n",x,k);
    if(dep[x]<k) re 0;
    int w=lg[k];
    k-=1<<w,x=fa[x][w];
    // printf("%d,%d\n",x,k);
    k-=dep[x]-dep[top[x]],x=top[x];
    // printf("%d,%d\n",x,k);
    // out(f[x],dep[x]-mxd[x],mxd[x]-dep[x]);
    // printf("ret=%d\n",f[x][-k]);
    re f[x][-k];
}
void play_it(){
    fa[0][0]=-1;
    fo(i,1,n){
        int x=mp[a[i]-1];
        add(i,x),mp[a[i]]=i;
    }
    fo(i,2,n) lg[i]=lg[i>>1]+1;
    dfs1(0);
    dfs2(0);
    fo(i,1,m) mp[i]=0;
}
}

namespace Tree_{
vector<int> e[N];
int fa[N][20],dep[N],mxd[N],top[N],son[N],lg[N];
int* f[N];
void add(int x,int y){
    // printf("__add(%d,%d)\n",x,y);
    e[y].pb(x);fa[x][0]=y;
}
void dfs1(int x){
    // printf("dfs1(%d)\n",x);
    fo(i,1,lg[n]){
        if(fa[x][i-1]==n+1) fa[x][i]=n+1;
        else fa[x][i]=fa[fa[x][i-1]][i-1];
    }
    mxd[x]=dep[x];
    for(int i:e[x]){
        dep[i]=dep[x]+1;
        dfs1(i);
        if(mxd[i]>mxd[x]) son[x]=i,mxd[x]=mxd[i];        
    }
    // printf("son[%d]=%d\n",x,son[x]);
}
void dfs2(int x){
    // printf("dfs2(%d)\n",x);
    if(x==top[x]){
        f[x]=Pool::get(mxd[x]-dep[x]+1);
        int y=x;
        fo(i,1,mxd[x]-dep[x]){
            if(y==n+1) f[x][-i]=y;
            else f[x][-i]=(y=fa[y][0]);
        }
    }
    f[top[x]][dep[x]-dep[top[x]]]=x;
    for(int i:e[x]){
        if(i==son[x]) top[i]=top[x];
        else top[i]=i;
        dfs2(i);
    }
    // if(x==top[x]) cout<<x<<":",out(f[x],dep[x]-mxd[x],mxd[x]-dep[x]);
}
int ask(int x,int k){
    // printf("__ask(%d,%d)\n",x,k);
    if(dep[x]<k) re n+1;
    if(k==0) re x;
    int w=lg[k];
    k-=1<<w,x=fa[x][w];
    // printf("%d,%d\n",x,k);
    k-=dep[x]-dep[top[x]],x=top[x];
    // printf("%d,%d\n",x,k);
    // out(f[x],dep[x]-mxd[x],mxd[x]-dep[x]);
    // printf("ret=%d\n",f[x][-k]);
    re f[x][-k];
}
void play_it(){
    fa[n+1][0]=n+1;
    fo(i,1,m+1) mp[i]=n+1;
    go(i,n,1){
        int x=mp[a[i]+1];
        add(i,x),mp[a[i]]=i;
    }
    fo(i,2,n) lg[i]=lg[i>>1]+1;
    dfs1(n+1);
    top[n+1]=n+1;
    dfs2(n+1);
    fo(i,1,m) mp[i]=0;
}
}

void sweep(int l,int r,int* f){
    // printf("sweep(%d,%d)\n",l,r);cout<<"mp:";out(mp,1,m);
    if(l<=r){
        fo(i,l,r){
            f[i]=f[mp[a[i]-1]]+1;
            mp[a[i]]=i;
        }
        fo(i,l,r) mp[a[i]]=0;
    }else{
        go(i,l,r){
            f[i]=f[mp[a[i]+1]]+1;
            mp[a[i]]=i;            
        }
        go(i,l,r) mp[a[i]]=0;
    }
    // cout<<"f:";out(f,l,r);
}
int T,bel[N],Bl[M],Br[M],mx[M][M],tmp[N];

signed main(){
    cin>>m>>n>>q;int oo=read();
    fo(i,1,m) mp[read()]=i;
    fo(i,1,n) a[i]=mp[read()];
    fo(i,1,m) mp[i]=0;

    Tree::play_it();Tree_::play_it();
    // cout<<"son:";out(Tree::son,0,n);cout<<"top:";out(Tree::top,1,n);
    fo(i,1,n) bel[i]=bel[i-1]+(i%B==1);T=bel[n];
    if(T>=M) puts("nb"); 
    fo(i,1,T) Bl[i]=(i-1)*B+1,Br[i]=min(n,i*B);
    fo(i,1,T){
        sweep(Bl[i],n,tmp);
        if(i>1) sweep(Bl[i]-1,1,tmp);
        fo(j,i,T){
            mx[i][j]=mx[i][j-1];
            fo(k,Bl[j],Br[j]) big(mx[i][j],tmp[k]);
        }
    }

    // puts("mx:");fo(i,1,T) out(mx[i],1,T);
    // re 0;
    int lst=0;
    while(q--){
        int l=read()^lst,r=read()^lst,L=bel[l],R=bel[r];
        if(L==R){
            sweep(l,r,tmp);
            // cout<<"tmp:";out(tmp,0,n);
            int ans=0;fo(i,l,r) big(ans,tmp[i]);
            if(oo) lst=ans;
            cout<<ans<<'\n';
            co;
        }
        int ans=mx[L+1][R-1];
        int lim=ans+r-Bl[R]+1+Br[L]-l+1;
        fo(i,l,Br[L]){
            while(Tree_::ask(i,ans)<=r) ++ans;
            if(ans==lim) goto H;
        }
        fo(i,Bl[R],r){
            while(Tree::ask(i,ans)>=l) ++ans;
            // assert(ans<=lim);
            if(ans==lim) goto H;
        }H:
        if(oo) lst=ans;
        cout<<ans<<'\n';
    }
    return 0;
}
}
/*
4 6 6 0
1 2 3 4
1 2 3 2 3 4

1 3
1 4
2 4
2 5
2 6
1 6
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：比利♂海灵顿 (赞：3)

# 分块 RMSQ

[传送门](https://www.luogu.com.cn/problem/P8120)

题面已经很清楚了，所以就不复述了。

## 转化

我们发现排列不需要存储，只要存储每个元素的位置 $Pos_i$ 即可，读入 $a$ 的时候，我们把输入的第 $i$ 数字在 $b$ 中的位置 $Pos_i$ 存入 $a_i$。这样问题就变成了在新的 $a$ 数组中查询区间的最长连续上升子序列。

## 离线

对于离线算法，我们想到莫队。通过存储当前区间内，以 $a$ 的每个位置结尾和开头的子序列长度 $Len_{i, 0/1}$，可以进行 $O(1)$ 的边界伸长。利用回滚莫队，设置块长为 $\dfrac n{\sqrt q}$ 可以做到 $O(m + n\sqrt q)$ 的总复杂度。

## 在线

同样是分块，设块长为 $B$，块数记为 $A = \lfloor \frac nB \rfloor$。

这个算法和出题人的官方算法不同，我预处理了 $f$，$g$，$Mx$ 三个数组。

$f_{i, j, k}$ 表示从第 $i$ 个到第 $j$ 个整块，外加右边紧挨着的 $k$ 个零散元素组成的区间 $[iB + 1, (j + 1)B + k]$ 内，以 $k$ 为结尾的最长的满足条件的子序列长度。

$g_{i, j, k}$ 表示从第 $i$ 个到第 $j$ 个整块，外加左边紧挨着的 $k$ 个零散元素组成的区间 $[iB + 1 - k, (j + 1)B]$ 内，以 $k$ 为开头的最长的满足条件的子序列长度。

$Mx_{i, j}$ 表示从第 $i$ 个到第 $j$ 个整块组成的区间 $[iB + 1, (j + 1)B]$ 内最长满足条件的子序列的长度。

预处理的过程和莫队区间伸长是一样的。复杂度 $O(\frac {n^2}B)$。

询问的时候把查询的子序列分为 $3$ 种:

- 只存在于整块区间内  
  直接查询 $Mx$ 即可。复杂度 $O(1)$。
- 包含整块右边零散元素
  因为这样的子序列右端一定在右边零散元素中，我们枚举右边的零散元素作为子序列结尾，一开始预处理的 $f$ 便是这些子序列去掉左边零散元素的长度 $TheL$，根据它们的值和它们对应的 $f$ 值算出开头元素 $Le$，把长度插入辅助数组 $Len_{Le}$。表示去掉左边零散元素的区间内以 $Le$ 为开头的最长符合条件的子序列长度为 $TheL$。然后在 $Len$ 中只存在刚刚插入的 $O(B)$ 个元素，当前区间和待查区间右端点相同的情况下，将当前区间左端点伸长到待查的区间的左端点。此时用 $Len$ 中最大值更新答案。最后将 $Len$ 回滚到空数组。复杂度 $O(B)$。
- 不包含整块右边零散元素，包含整块左边零散元素  
  这个时候枚举每个左边的零散元素作为左端点，查询它们对应的 $g$ 值即可。复杂度 $O(B)$。

这样可以在 $O(B)$ 内完成一次查询。块长取 $\dfrac n{\sqrt q}$ 的时候可以得到 $O(m + n\sqrt q)$ 的复杂度。

## 代码实现

这里我把 $n$，$m$ 的意义反过来了，这里提醒一下避免误会。

对于 $f$ 和 $g$，由于空间不够，所以采用了公用空间的手段。发现所有 $i > j$ 的 $f_{i, j, k}$ 和 $g_{i, j, k}$ 都不存在。对于 $f$ 来说，$i$ 的取值为 $[0, A)$。而 $g$ 的 $i$ 取值为 $(1, A)$。所以我们可以把 $g_{i, j, k}$ 的值存到 $f_{A - i, A - j, k}$ 中去。为了防止 $i = j$ 的时候，$f$ 和 $g$ 冲突的情况，我们把原本 $f_{i, j, k}$ 的值存到 $f_{i, j + 1, k}$ 中去。这样第 $i$ 行，$f$ 占用第 $(i, j]$ 列，$g$ 占用第 $(0, i]$ 列。不产生冲突。

但是随着块长的变化，定义全局变量三维数组的行为无法满足灵活变化的块长的需求，频繁的访问寻址也会增加常数，所以我们只开一个内存池，然后灵活地查询我们想要的位置的指针，在连续访问的时候只移动指针而避免了三个下标的寻址。

```cpp
unsigned fPool[300000000], Len[300005], Mx[1005][1005];
unsigned a[300005], Pos[300005], m, n, q;
unsigned Stack[2005], STop(0);
unsigned A, B, C, D, TmpM;
unsigned PrA, PrB;
unsigned Cnt(0), Ans(0), Tmp(0);
char Use(0);
inline unsigned* f(const unsigned x, const unsigned y, const unsigned z) {
  return fPool + x * PrA + y * PrB + z;
}
signed main() {
  n = RD(), m = RD(), q = RD(), Use = RD(), B = min(m, (unsigned)max((double)m * m / 300001000, (m / sqrt(q))) + 1), A = m / B;
  PrB = B + 1, PrA = PrB * (A + 1);
  for (unsigned i(1); i <= n; ++i) Pos[RD()] = i;
  for (unsigned i(1); i <= m; ++i) a[i] = Pos[RD()];
  for (unsigned i(0); i < A; ++i) {
    memset(Len, 0, ((n + 1) << 2)), TmpM = 0;
    for (unsigned j(i), k = (i * B + 1); j < A; ++j) {
      unsigned* CuPo(f(i, j, 1));
      for (unsigned Cou(1); Cou <= B; ++Cou, ++k, ++CuPo) {
        unsigned Cur(a[k]), Pre(Len[Cur - 1] + 1);
        Len[Cur] = max(Pre, Len[Cur]), TmpM = max(TmpM, Len[Cur]);
        if (j > i) (*CuPo) = Len[Cur];
      }
      Mx[i][j] = TmpM;
    }
    unsigned* CuPo(f(i, A, 1));
    for (unsigned k(A* B + 1); k <= m; ++k, ++CuPo) {
      unsigned Cur(a[k]), Pre(Len[Cur - 1] + 1);
      Len[Cur] = max(Pre, Len[Cur]), (*CuPo) = Len[Cur];
    }
  }
  for (unsigned i(A - 1); i; --i) {
    memset(Len, 0, ((n + 1) << 2));
    for (unsigned j(i), k = ((i + 1) * B); ~j; --j) {
      unsigned* CuPo(f(A - j - 1, A - i, 1));
      for (unsigned Cou(1); Cou <= B; ++Cou, --k, ++CuPo) {
        unsigned Cur(a[k]), Pre(Len[Cur + 1] + 1);
        Len[Cur] = max(Pre, Len[Cur]);
        if (j < i) (*CuPo) = Len[Cur];
      }
    }
  }
  memset(Len, 0, ((n + 1) << 2));
  for (unsigned i(1); i <= q; ++i) {
    if (!Use) Ans = 0;
    C = (RD() ^ Ans), D = (RD() ^ Ans), Ans = 0;
    unsigned L((C + B - 2) / B), R(D / B);
    if (L >= R) {
      for (unsigned i(C); i <= D; ++i) {
        unsigned Cur(a[i]), Pre(Len[Cur - 1] + 1);
        Stack[++STop] = Cur, Ans = max(Ans, Len[Cur] = max(Len[Cur], Pre));
      }
      while (STop) Len[Stack[STop--]] = 0;
      printf("%u\n", Ans); continue;
    }
    --R, Ans = max(Ans, Mx[L][R]), C = (L * B) - C + 1, D -= (R + 1) * B;
    unsigned* CuPo(f(L, R + 1, 1));
    for (unsigned j(1), p(((R + 1)* B) + 1); j <= D; ++j, ++p, ++CuPo) {
      unsigned TheL(*CuPo), Le(a[p] - TheL + 1);
      Ans = max(Ans, TheL);
      Stack[++STop] = Le, Len[Le] = max(Len[Le], TheL);
    }
    for (unsigned j(1), p(L* B); j <= C; ++j, --p) {
      unsigned Cur(a[p]), Pre(Len[Cur + 1] + 1);
      Stack[++STop] = Cur, Ans = max(Ans, Len[Cur] = max(Len[Cur], Pre));
    }
    while (STop) Len[Stack[STop--]] = 0;
    CuPo = f(A - L, A - R, 1);
    for (unsigned j(1); j <= C; ++j, ++CuPo) Ans = max(Ans, *CuPo);
    printf("%u\n", Ans);
  }
  return Wild_Donkey;
}
```

---

