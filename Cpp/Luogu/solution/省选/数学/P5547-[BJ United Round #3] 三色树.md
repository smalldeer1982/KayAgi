# [BJ United Round #3] 三色树

## 题目描述

请你对满足以下要求的 $n$ 个节点的 **无标号无根树** 计数： 
 
- 每个节点是三种颜色之一：红，蓝，黄
- 红色节点度数不超过 $4$，蓝色和黄色节点度数均不超过 $3$  
- 黄色节点不能相邻

注意 **无标号无根树** 的意义是：如果两颗树可以通过重新编号的方法使得对应点颜色相同，对应连边一致，则认为是同一颗树。

答案对输入的质数 $p$ 取模。

## 说明/提示



对于 $100\%$ 的数据，保证：  
$1\le n \le 3000$  
$9\times 10^8 \le p \le 1.01 \times 10^9$   
保证 $p$ 为质数

By：EntropyIncreaser

## 样例 #1

### 输入

```
2 998244353```

### 输出

```
5```

## 样例 #2

### 输入

```
3 998244353```

### 输出

```
15```

## 样例 #3

### 输入

```
20 998244353```

### 输出

```
578067492```

# 题解

## 作者：Elegia (赞：7)


这道题改自 [ProjectEuler#677](https://projecteuler.net/problem=677)。

#### 思路要点

首先考虑无标号有根树，我们只需维护 dp 数组 $R(n), B(n), Y(n)$ 即可。通过更新 dp 数组 $Q(d, n)$ 表示此时不在意节点的根的颜色，且根的度数为 $d$ 即可维护红根和蓝根，$W(d, n)$ 用于维护孩子没有黄根树的，这可以帮助计算黄根。每次 update 会消耗 $\Theta(n)$ 的时间，比如说已经计算完了 $R(n)$ 的值，那么它作为子树有可能出现了 $k$ 次，则选出 $\displaystyle \binom{R(n) + k - 1}{k - 1}$ 种方案，令 $Q(d,N)$ 加上 $\binom{R(n) + k - 1}{k - 1} Q(d - k, N - kn)$。

这一部分的复杂度为 $\Theta(n^2)$。



计算无标号无根树的要点是观察树的一个特殊点：一颗树要么存在唯一一个重心使得任何一个子树的大小均 $< \frac{n}2$，要么存在一个“重边”使得它将树恰好分为大小为 $\frac n2$ 的两部分。

对于前者部分的计数，我们只需将 dp 数组计算到 $\lceil \frac n2 \rceil - 1$ 时，将 $Q,R$ 数组取出。对于后者，若 $n$ 是偶数，当计算完 $\frac n2$ 的 dp 值时，将 $R, B, Y$ 用于计算即可。



#### 如何做到更快

考虑计算 $R,B,Y$ 的生成函数 $G_R(x), G_B(x), G_Y(x)$。

我们记 $S = G_R + G_B + G_Y$，我们使用 Pólya 计数定理表示 $3$ 个孩子的树，通过枚举置换群：
$$
\frac{S(x)^3 + 3S(x^2)S(x) + 2S(x^3)}{3!}
$$

读者可自己尝试推导 $4$ 和 $2$ 个孩子的树。

由此我们可以通过 $G_R, G_B, G_Y$ 自身带入 $x, x^2, x^3$ 这些的多项式来表示。接下来考虑如何求解。

我们让 $G_R, G_B, G_Y$ 放在一起进行迭代，我们考虑倍增，由于已经计算出了前 $\frac n2$ 项，所有带入 $x^2, x^3$ 的部分就已经确定了，我们可以认为是常数。接下来就是一个关于 $G_R, G_B, G_Y$ 的三元三次方程，这依然可以通过牛顿迭代解决，也就是这等价于根据 $G_R, G_B, G_Y$ 的定义式得到了 $3$ 个它们之间的关系式 $E_R/E_B/E_Y(G_R, G_B, G_Y) = 0$，将 $E_R/E_B/E_Y(u, v, w)$ 在 $G_R, G_B, G_Y$ 处泰勒展开就是一次方程，求解一个三元一次方程即可。

本算法的复杂度为 $\Theta(n\log n)$，~~常数显而易见的大，欢迎有兴趣的同学来实现~~。


---

## 作者：bai_tang (赞：4)

只要有信念，就一定能成功！

### [题意](https://www.luogu.com.cn/problem/P5547)
统计满足条件的 $n$ 节点无标号红蓝黄三色无根树，满足：红色点度数不超过 $4$，蓝色黄色点度数不超过 $3$，黄色点不能相邻，$n\le 3000$。

### 分析
无根树不太好考虑，不妨简化一下变成有根树。

无根树树哈希的常用套路是找重心，假设根是一个重心，那么显然，它最大的子树大小不会超过 $\lfloor n/2\rfloor$，实际上，如果直接计算这类有根树的个数，对于最大子树大小恰好为 $n/2$ 的情况，我们会算重复，所以还需要稍加容斥，具体地，我们要减去从大小为 $\lfloor n/2\rfloor$ 的有根树中挑出不同的两个然后根对根组成合法方案的方案数。

设 $f(o,k)$ 为以 $o$ 颜色为根，子树大小为 $k$ 的有根树方案数，考虑如何转移，设 $g(S,i,k)$ 为从考虑颜色集合 $S$ 为根的子树，选出 $i$ 棵子树大小之和为 $k$ 的方案数，枚举子树大小添加入贡献一直加到 $\lfloor n/2\rfloor$，复杂度即为 $O(n^2)$，[代码](https://www.luogu.com.cn/paste/4ofuqlvc)。

---

## 作者：AllenJYL (赞：3)

对于无标号无根树，一个自然的想法是将它对答案的贡献挂到树上的一个节点上计算。

由于一棵树在选择重心作为根时，它的子节点子树大小不超过原树大小的一半（大小定义为节点数量），依据这个性质，可以考虑在重心上计算一棵无标号无根树的贡献，也就将这棵树转化为了一棵以重心为根的有根树。

这样，我们转而考虑求出无标号有根树的数量。

考虑 dp，设计状态 $f_{i,0/1/2}$ 表示一棵大小为 $i$ 的有根树，其根节点的颜色为 $0/1/2$（红、蓝、黄），而且 **钦定根节点会额外延申一条边与它以后的父亲相连** 的方案数。在这里，尽管我们统计的是一棵大小为 $i$ 的有根树，但由于这棵树最终会被接在一棵更大的树下面，所以这棵树的根最终会成为更大的树中某个节点的儿子，也就意味着这棵树的根需要额外考虑一条边连向它以后的父亲。

发现只利用这一个数组无法转移，我们还需要多来点状态。设计状态 $g_{i,j}$ 表示一个包含 $j$ 棵有根树的森林，这些树的节点总数为 $i$ 的方案数。转移的时候我们把这些有根树挂在当前根节点下面，形成了当前根节点的若干棵子树。这样，初步的转移方程就是：
- $f_{i,0}=\sum_{j=0}^3g_{i-1,j}$，表示红色根节点可以选择 $0/1/2/3$ 个儿子，注意不能选择 $4$ 个儿子的原因是根节点已被钦定将与它以后的父亲相连；
- $f_{i,1}=\sum_{j=0}^2g_{i-1,j}$，表示蓝色根节点可以选择 $0/1/2$ 个儿子，注意不能选择 $3$ 个儿子的原因是根节点已被钦定将与它以后的父亲相连。

不幸的是我们仍然无法处理黄色根节点的情况，我们还需要更多状态。设计状态 $h_{i,j}$ 表示表示一个包含 $j$ 棵有根树的森林，这些树的节点总数为 $i$，且这些树的 **根节点的颜色都不为黄色** 的方案数。利用这个状态，我们就能顺利解决黄色根节点的情况了：
- $f_{i,2}=\sum_{j=0}^2h_{i-1,j}$，表示黄色根节点可以选择 $0/1/2$ 个不为黄色的儿子，注意不能选择 $3$ 个儿子的原因是根节点已被钦定将与它以后的父亲相连。

接下来，考虑 $g$ 和 $h$ 如何转移。可以发现当我们处理了 $f_{i,0/1/2}$ 之后，就相当于是为森林添加了许多大小为 $i$ 的备选树。这意味着我们可以利用这些大小为 $i$ 的，刚被转移出来的树更新 $g$ 和 $h$。

具体而言，对于 $g_{x,y}$，枚举 $d$ 表示这 $y$ 棵树中有多少棵大小为 $i$，那么就可以得到 $g_{x,y}\larr g_{x,y}+C\times g_{x-i\times d,y-d}$。$C$ 的实际意义是
> 在 $f_{i,0}+f_{i,1}+f_{i,2}$ 种备选树中，选择 $d$ 个，选出的树可以本质相同，而且它们没有顺序的方案数。

这等价于有 $d$ 个球摆成一排，往其中 $d+1$ 个空位插入 $f_{i,0}+f_{i,1}+f_{i,2}-1$ 个本质相同的板子，板子可以插在同一个缝中的方案数。利用插板法可知，方案数 $C=\binom{d+f_{i,0}+f_{i,1}+f_{i,2}-1}{f_{i,0}+f_{i,1}+f_{i,2}-1}=\binom{d+f_{i,0}+f_{i,1}+f_{i,2}-1}{d}$。

所以总的转移方程是：
- $g_{x,y}\larr g_{x,y}+\sum_{d=1}^{\min(\lfloor\frac{x}{i}\rfloor,y)}\binom{d+f_{i,0}+f_{i,1}+f_{i,2}-1}{d}\times g_{x-i\times d,y-d}$。

对于 $h_{x,y}$，它与 $g$ 的唯一差别是备选树的种类数变成了 $f_{i,0}+f_{i,1}$，去除了根节点为黄色的情况。稍加分析就可以得到：
- $h_{x,y}\larr h_{x,y}+\sum_{d=1}^{\min(\lfloor\frac{x}{i}\rfloor,y)}\binom{d+f_{i,0}+f_{i,1}-1}{d}\times h_{x-i\times d,y-d}$。

初值 $g_{0,0}=h_{0,0}=1$。至此，我们完成了转移。

统计答案时需要注意根节点为重心，也就是说不能存在大小大于 $\lfloor\frac{n}{2}\rfloor$ 的树，所以如上的 dp 只能做到 $i_{\max}=\lfloor\frac{n}{2}\rfloor$，这样就能使得计入 $g$ 和 $h$ 中的树的大小都小于等于 $\lfloor\frac{n}{2}\rfloor$。答案即为：

- $\sum_{i=0}^4g_{n-1,i}$，表示红色根节点可以选择 $0/1/2/3/4$ 个儿子，在这里，由于最终根节点不会再有父亲了，所以可以选择 $4$ 个儿子；
- $\sum_{i=0}^3g_{n-1,i}$，表示蓝色根节点可以选择 $0/1/2/3$ 个儿子，在这里，由于最终根节点不会再有父亲了，所以可以选择 $3$ 个儿子；
- $\sum_{i=0}^3h_{n-1,i}$，表示黄色根节点可以选择 $0/1/2/3$ 个不为黄色的儿子，在这里，由于最终根节点不会再有父亲了，所以可以选择 $3$ 个儿子。

如上三者之和。

假如实现了这个算法会发现只能通过样例 2。问题的本质在于当 $n$ 为偶数时，可能会有树存在两个重心的情况，这会导致这些树被算重。处理办法很简单，去掉它们算重的部分就行了。

具体而言，由于存在两个重心的情况一定满足这两个重心被一条边相连，所以相当于这条边将原树分成了两棵大小为 $\frac{n}{2}$（$n$ 为偶数）的树，这两棵树的根节点就是原树的两个重心，被这条边相连。分析可得，这两棵树如果本质不同，就会导致原树被多算一次。可以发现这两棵树的根节点的颜色有如下情况：
- 不存在黄色根节点，此时方案数为 $\binom{f_{\frac{n}{2},0}+f_{\frac{n}{2},1}}{2}=\frac{(f_{\frac{n}{2},0}+f_{\frac{n}{2},1})(f_{\frac{n}{2},0}+f_{\frac{n}{2},1}-1)}{2}$，这表示从 $f_{\frac{n}{2},0}+f_{\frac{n}{2},1}$ 种红色根或蓝色根的树中选择两棵不同的树的方案数，由于交换两棵树是本质相同的，所以还需要额外除以 $2$；
- 存在一个黄色根节点，此时方案数为 $(f_{\frac{n}{2},0}+f_{\frac{n}{2},1})f_{\frac{n}{2},2}$，这表示从 $f_{\frac{n}{2},0}+f_{\frac{n}{2},1}$ 种红色根或蓝色根的树中选择一棵树，再从 $f_{\frac{n}{2},2}$ 种黄色根的树中选择一棵树的方案数；
- 存在两个黄色根节点，由于这违背了题意，所以方案数是 $0$。

将以上三者求和从答案中减去即可，这只在 $n$ 为偶数时进行。

时间复杂度 $O(n^2)$。

---

## 作者：tuget (赞：2)

写篇题解加深印象。

首先先考虑**无标号有根树**的计数。显然设 $f_{i,0/1/2}$ 表示大小为 $i$ 的根节点颜色分别为红、蓝、黄的方案数，直接用 $f$ 进行转移还需要记录根的度数，所以我们再记 $g_{i,j}$ 表示 $j$ 棵树，总大小为 $i$ 的方案数。为了转移黄色点，我们还需要记 $h_{i,j}$ 为 $j$ 棵树，总大小为 $i$ 且这几棵树的树根颜色**均不为黄色**，那么 $f_{i,1}=\sum\limits_{j=0}^2 g_{i-1,j}$，$f_{i,2}=\sum\limits_{j=0}^2 h_{i-1,j}$，$f_{i,0}=f_{i,1}+g_{i-1,3}$，这里 $\text{度数}-1$ 是因为根还有父亲。

接下来考虑转移 $g_{i,j}$ 与 $h_{i,j}$，这两者转移类似，所以这里只推导 $h_{i,j}$ 的情况。因为对于单次转移而言，比之前的变化是有了单棵子树为 $i$ 的情况，所以我们枚举新增 $k$ 棵大小为 $i$ 的子树，因为无标号，所以只需要考虑从大小为 $i$ 的子树的方案中选出 $k$ 种的**组合**，即 ${f_{i,0}+f_{i,1}} \choose k$，注意，这里可以选重复的方案，故我们通过添加 $k-1$ 种方案刻画，即 ${f_{i,0}+f_{i,1}+k-1} \choose k$，于是 $h_{i,j}=\sum\limits_{k=1}^j h_{i-ki,j-k}{{f_{i,0}+f_{i,1}+k-1} \choose k}$。具体实现上，我们需要把这个组合数拆开，变成 $x_k={{f_{i,0}+f_{i,1}+k-1} \choose k}=\prod \frac{f_{i,0}+f_{i,1}+k}{k}=\frac{f_{i,0}+f_{i,1}+k}{k} x_{k-1}$，在每次计算完 $f_{i,j}$ 后计算一次即可，这样以上部分的总时间复杂度为 $O(n^2)$。

现在我们需要求得是 **无标号无根树**，根据套路我们**钦定重心**为根，因为它的每棵子树大小小于 $\lfloor \frac{n}{2} \rfloor$，这相当于取重心来代表整棵树，这时候我们同 $f_{i,j}$ 的转移方法，先枚举重心的度数，对于每种度数有红点的 $g_{i,j}$，蓝点的 $g_{i,j}$ 和黄点的 $h_{i,j}$ 三种情况，度数为 $4$ 的只有红点的情况，相加就是答案。

但这时也会注意到，重心可能有两个，即有一些方案会被计算两次。存在这样的情况的充要条件是 $2 \mid n$，对于这样的情况，我们取重心之间的那条边，答案减去选出两棵大小为 $\frac{n}{2}$ 的树的方案即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 3005
#define ll long long
#define frp freopen
#define fio(in,out) frp(in,"r",stdin),frp(out,"w",stdout)
inline void bug(){cout<<endl;}
template<typename TS,typename ... T>
inline void bug(TS p,T ... x){cout<<p<<" ";bug(x...);}
template<class T>
inline T Read()
{
	T res=0,f=1;char c;
	for(;(c=getchar())<'0' || c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9')res=(res<<3)+(res<<1)+(c^48),c=getchar();
	return res*f;
}
#define read() Read<int>()
int n,p,f[maxn][3],g[maxn][5],h[maxn][4],inv[6],x[5],ans;
int main()
{
	int i,j,k,m,w;
	n=read(),p=read();inv[1]=1;
	for(i=2;i<=5;++i)inv[i]=1ll*inv[p%i]*(p-p/i)%p;
	g[0][0]=h[0][0]=x[0]=1;
	for(m=1;m<=n/2;++m)
	{
		for(i=0;i<=2;++i)
			f[m][1]=(f[m][1]+g[m-1][i])%p,f[m][2]=(f[m][2]+h[m-1][i])%p;
		f[m][0]=(f[m][1]+g[m-1][3])%p;
		w=(f[m][0]+f[m][1])%p;
		for(i=1;i<=3;++i)x[i]=x[i-1]*(w+i-1ll)%p*inv[i]%p;
		for(j=3;j;--j)for(i=n;i>=m;--i)
			for(k=1;k<=j&&k*m<=i;++k)
				h[i][j]=(h[i][j]+1ll*h[i-k*m][j-k]*x[k]%p)%p;
		w=(w+f[m][2])%p;
		for(i=1;i<=4;++i)x[i]=x[i-1]*(w+i-1ll)%p*inv[i]%p;
		for(j=4;j;--j)for(i=n;i>=m;--i)
			for(k=1;k<=j&&k*m<=i;++k)
				g[i][j]=(g[i][j]+1ll*g[i-k*m][j-k]*x[k]%p)%p;
	}
	for(i=0;i<=3;++i)
		ans=((ans+2ll*g[n-1][i]%p)%p+h[n-1][i])%p;
	ans=(ans+g[n-1][4])%p;
	if(~n&1)
	{
		w=(f[n/2][0]+f[n/2][1])%p;
		w=(w*(w-1ll)/2%p+1ll*w*f[n/2][2]%p)%p;
		ans=(ans-w+p)%p;
	}
	printf("%d",ans);
	return 0;
}
```

我也是看了其他题解才会的，琢磨了挺久的，我把我自己阅读时一些不理解的地方写了下，代码可能和其他题解比较像。

---

## 作者：foreverlasting (赞：2)

[题解放博客了](https://foreverlasting1202.github.io/2019/09/10/BJUnitedRound3%E4%B8%89%E8%89%B2%E6%A0%91/)


一道计数好题。
<!--more-->

首先考虑一件事，无标号无根树怎么处理。

有个经典的做法就是利用重心，可以强制重心为根，然后减去这些多余情况就好了。由于一棵树可能会有两个重心，那就把连接重心的那条边作为根看就好了。

然后回到这道题，把题目变成无标号有根树。

于是考虑枚举根的颜色和根的度数，然后暴力转移。意思就是，设$R[n][d]$为根颜色为$red$，度数为$d$，有$n$个点的方案数。同理有另外两个。然后转移$d$的时候，就是枚举第一棵子树有几个点，第二棵子树有几个这样，这样做是$O(n^3)$的（因为只有当点为整棵树的根时才用枚举到$4$，否则到$3$就好了）。

发现瓶颈在转移，容易发现这个转移可以容斥，于是复杂度就降到了$O(n^2)$。具体容斥以及转移看代码就好了，虽然我也是看了半天别人代码才懂的。。。

code:
```cpp
//2019.9.10 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
//#include<ext/pb_ds/tree_policy.hpp>
//#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
//using namespace __gnu_pbds;
//using namespace __gnu_cxx;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define unl __int128
#define eps 5.6e-8
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
#define ctz(x) __builtin_ctz(x)
//#define pc(x) __builtin_popcountll(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define ull unsigned LL
#define lowbit(x) (x&-x)
#define gc getchar
//template <class T>using Tree=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
inline int read() {
    res s=0,ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline int read() {
//    res s=0,ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
inline LL Read() {
    RG LL s=0;
    res ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline void write(RG unl x){
//    if(x>10)write(x/10);
//    putchar(int(x%10)+'0');
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//clock_t start=clock();
//inline void ck(){
//    if(1.0*(clock()-start)/CLOCKS_PER_SEC>0.1)exit(0);
//}
const int N=3e3+10;
namespace MAIN{
    int kcz;
    inline void add(res &x,const res &y){
        x+=y,x>=kcz?x-=kcz:(x<0?x+=kcz:1);
    }
    inline int Add(const res &x,const res &y){
        return x+y>=kcz?x+y-kcz:(x+y<0?x+y+kcz:x+y);
    }
    inline int mul(const res &x,const res &y){
        return int(1LL*x*y%kcz);
    }
    inline int mul(const res &x,const res &y,const res &d){
        return int(1LL*x*y/d%kcz);
    }
    inline int qpow(res x,res y){
        res ret=1;
        while(y){
            if(y&1)ret=mul(ret,x);
            x=mul(x,x),y>>=1;
        }
        return ret;
    }
    int inv[5];
    int R[N][5],B[N][4],Y[N][4];
    int dp[N],br[N];
    int nn;
    inline int get(const RG LL &x){
        return Add(int(x%kcz),0);
    }
    inline void DP(const res &n){
        if(n==1){
            R[1][0]=B[1][0]=Y[1][0]=1;
            if(nn>2)br[1]=2,dp[1]=3;
            return;
        }
        //R 1
        R[n][1]=dp[n-1];
        //R 2
        for(res i=1;i+i<=n-1;i++)i==n-1-i?add(R[n][2],mul(dp[i],dp[i]+1,2)):add(R[n][2],mul(dp[i],dp[n-1-i]));
        //R 3
        res ret=0,val=(n-1)%3?0:dp[(n-1)/3];
        for(res i=3;i<=n-1;i++)add(R[n][3],mul(R[i][2],dp[n-i]));
        for(res i=1;i+i<n-1;i++)i==n-1-i*2?add(ret,mul(dp[i],dp[i]-1)):add(ret,mul(dp[i],dp[n-1-i*2]));
        R[n][3]=Add(int((1LL*mul(get(1LL*R[n][3]-ret*2-val),inv[3])+ret+val)%kcz),0);
        //B 1
        B[n][1]=dp[n-1];
        //B 2
        B[n][2]=R[n][2];
        //Y 1
        Y[n][1]=br[n-1];
        //Y 2
        for(res i=1;i+i<=n-1;i++)i==n-1-i?add(Y[n][2],mul(br[i],br[i]+1,2)):add(Y[n][2],mul(br[i],br[n-1-i]));
        if(n*2<nn)br[n]=int((1LL*R[n][1]+R[n][2]+R[n][3]+B[n][1]+B[n][2])%kcz),dp[n]=int((1LL*br[n]+Y[n][1]+Y[n][2])%kcz);
    }
    int n;
    inline void MAIN(){
        nn=n=read(),kcz=read(),inv[0]=inv[1]=1;
        if(n==1){puts("3");return;}
        if(n==2){puts("5");return;}
        for(res i=2;i<=4;i++)inv[i]=mul(inv[kcz%i],kcz-kcz/i);
        for(res i=1;i<=n;i++)DP(i);
        //R 4
        res ret=0,Ret=0,REt=0,val=(n-1)%4?0:dp[(n-1)/4];
        for(res i=3;i<n;i++)add(R[n][4],mul(R[i][3],dp[n-i]));
        for(res i=1;i*3<n-1;i++)i==n-1-i*3?add(ret,mul(dp[i],dp[i]-1)):add(ret,mul(dp[i],dp[n-1-i*3]));
        if(n&1)for(res i=1;i+i<=(n-1)/2;i++)i==(n-1)/2-i?add(Ret,mul(dp[i],dp[i]-1,2)):add(Ret,mul(dp[i],dp[(n-1)/2-i]));
        for(res i=1;i+i<=n-3;i++)add(REt,mul(dp[i],R[n-i*2][2]));
        add(REt,kcz-(Add(Add(val,ret),Add(Ret,Ret))));
        R[n][4]=Add(int((1LL*get(1LL*R[n][4]-val-mul(Add(ret,Ret),2)-mul(REt,3))*inv[4]%kcz+val+ret+Ret+REt)%kcz),0);
        //B 3
        B[n][3]=R[n][3];
        //Y 3
        ret=0,val=(n-1)%3?0:br[(n-1)/3];
        for(res i=3;i<=n-1;i++)add(Y[n][3],mul(Y[i][2],br[n-i]));
        for(res i=1;i+i<n-1;i++)i==n-1-i*2?add(ret,mul(br[i],br[i]-1)):add(ret,mul(br[i],br[n-1-i*2]));
        Y[n][3]=Add(int((1LL*get(1LL*Y[n][3]-ret*2-val)*inv[3]%kcz+ret+val)%kcz),0);
        res i=n/2;
        br[i]=int((1LL*R[i][1]+R[i][2]+R[i][3]+B[i][1]+B[i][2])%kcz),dp[i]=int((1LL*br[i]+Y[i][1]+Y[i][2])%kcz);
        dp[n]=int((1LL*R[n][2]+R[n][3]+B[n][2]+Y[n][2])%kcz);
        res ans=Add(Add(dp[n],R[n][4]),Add(B[n][3],Y[n][3]));
        if(n%2==0)add(ans,Add(mul(dp[n/2],br[n/2]),kcz-mul(br[n/2],br[n/2]-1,2)));
        printf("%d\n",ans);
    }
}
int main(){
//    srand(19260817);
//    freopen("signin.in","r",stdin);
//    freopen("signin.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Fzrcy (赞：1)

先考虑有标号无根树计数，设 $f(n,0/1/2)$ 表示根的颜色为红、蓝、黄，且**子树**大小为 $n$ 的方案数，$g(n,i)$ 表示选出 $i$ 个子树且子树大小的总和为 $n$ 的方案数，$h(n,i)$ 表示选出 $i$ 个子树且子树大小的总和为 $n$ 、子树的根的颜色不为的黄色方案数。

显然 $f(n,0)=\sum_{i=0}^{3}g_{n-1,i}$,，$f(n,1)=\sum_{i=0}^{2}g_{n-1,i}$，$f(n,2)=\sum_{i=0}^{2}h_{n-1,i}$，然后用 $f(n,i)$ 来更新 $g$ 和 $h$，这里以 $g$ 为例，根据隔板法，从 $n$ 个数中选出 $k$ 个数的方案数为 $\binom{n+k-1}{k}$，则 $g(a,b)=g(a,b)+\sum g(a-in,b-i)\binom{f(n,0)+f(n,1)+f(n,2)+i-1}{i}$。

然后考虑**无标号无根树**计数：考虑以重心为根，每个子树的大小均小于等于 $n/2$，然后若 $n$ 为偶数，则子树大小为 $n/2$ 的情况会重复计数，再减去即可。

```cpp
// qwq
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N=5002;
int f[N][3],g[N][5],h[N][4],n,mo,inv[6];
inline void suf(int &x,int y){(x+=y)>=mo&&(x-=mo);}
inline void sub(int &x,int y){(x-=y)<0&&(x+=mo);}
int main(){
    cin>>n>>mo,g[0][0]=h[0][0]=1,inv[1]=1;
    for(int i=2;i<6;i++)inv[i]=(ll)inv[mo%i]*(mo-mo/i)%mo;
    for(int m=1;m<=n/2;m++){
        for(int j:{0,1,2})
            suf(f[m][1],g[m-1][j]),
            suf(f[m][2],h[m-1][j]);
        f[m][0]=(f[m][1]+g[m-1][3])%mo;
        //for(int j:{0,1,2})cout<<f[m][j]<<' ';
        int x[5],w=(f[m][0]+f[m][1])%mo; x[0]=1;
        for(int i=0;i<3;i++)x[i+1]=(ll)x[i]*(w+i)%mo*inv[i+1]%mo;//,cout<<x[i+1]<<' ';
        for(int i=3;i;i--)for(int j=n-1;j>=m;j--)
            for(int s=1,k=j/m;s<=i&&s<=k;s++)
                suf(h[j][i],(ll)h[j-s*m][i-s]*x[s]%mo);//,cout<<h[i][j]<<' ';
        w=(w+f[m][2])%mo; x[0]=1;
        for(int i=0;i<4;i++)x[i+1]=(ll)x[i]*(w+i)%mo*inv[i+1]%mo;//,cout<<x[i+1]<<' ';
        for(int i=4;i;i--)for(int j=n-1;j>=m;j--)
            for(int s=1,k=j/m;s<=i&&s<=k;s++)
                suf(g[j][i],(ll)g[j-s*m][i-s]*x[s]%mo);//,cout<<g[i][j]<<' ';
        //cout<<endl;
    }
    int ans=0;
    for(int i=0;i<=3;i++)
        suf(ans,(2ll*g[n-1][i]%mo+h[n-1][i])%mo);
    suf(ans,g[n-1][4]);
    //cout<<ans<<endl;
    if(n%2==0){
        int tmp=(f[n/2][0]+f[n/2][1])%mo;
        tmp=((ll)tmp*(tmp-1)/2ll%mo+(ll)tmp*f[n/2][2]%mo)%mo;
        sub(ans,tmp);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

这个东西看起来就很像烷烃计数，尝试用类似的手段解决它。

~~PS：这一句话有若干个语法错误，但是在 5 秒之内审核通过了……管理员审核金钩题解都不看具体内容的吗~~

首先设，$f_{i,0/1/2}$ 表示大小为 $i$ 的“基”（也就是根节点外面连了一条边），根节点颜色为红、蓝、黄的方案数。

同时维护辅助数组 $g_{i,0/1/2/3}$ 表示用当前求出来的 $f$，做背包得到的数组。红色用 $g$ 转移，蓝黄直接枚举子树大小。$g$ 本身的转移是简单的，因为 $3$ 以内的划分本来就没那么多，可以直接枚举对不对。

再对树的形态分类讨论。

一种是 $2 \mid n$ 时，存在平分边。

另一种是平凡的单重心。

复杂度 $O(n^2)$。代码写成了一坨。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10;
int n,p,f[MAXN][4],g[MAXN][5],s[MAXN],_2,_3;
int qpow(int base,int p,int MOD) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
#define MOD p
void insert(int s) {
	int cnt=(f[s][0]+f[s][1]+f[s][2])%MOD;
	roff(i,n,0) {
		if(i>=s) ffor(j,1,3) g[i][j]=(g[i][j]+g[i-s][j-1]*cnt)%MOD;
		if(i>=s+s) {
			int mul=cnt*(cnt+1)%MOD*_2%MOD;
			ffor(j,2,3) g[i][j]=(g[i][j]+g[i-s*2][j-2]*mul)%MOD;	
		}
		if(i==s+s+s) g[i][3]=(g[i][3]+cnt+cnt*(cnt-1)%MOD+cnt*(cnt-1)%MOD*(cnt-2)%MOD*_2%MOD*_3)%MOD;
	}
	return ;
}
void Insert(int s) {
	
	int cnt=(f[s][0]+f[s][1]+f[s][2])%MOD;
	roff(i,n,0) {
		if(i>=s) ffor(j,1,4) g[i][j]=(g[i][j]+g[i-s][j-1]*cnt)%MOD;
		if(i>=s*2) {
			int mul=cnt*(cnt+1)%MOD*_2%MOD;
			ffor(j,2,4) g[i][j]=(g[i][j]+g[i-s*2][j-2]*mul)%MOD;	
		}
		if(i>=s*3) {
			int mul=(cnt+cnt*(cnt-1)%MOD+cnt*(cnt-1)%MOD*(cnt-2)%MOD*_2%MOD*_3)%MOD;
			ffor(j,3,4) g[i][j]=(g[i][j]+g[i-s*3][j-3]*mul)%MOD;
		}
		if(i==s*4) {
			int mul=_2*_2%MOD*_2%MOD*_3%MOD*cnt%MOD*(cnt-1)%MOD*(cnt-2)%MOD*(cnt-3)%MOD;
			mul=(mul+cnt)%MOD;
			mul=(mul+cnt*(cnt-1)%MOD*(1+_2))%MOD;
			mul=(mul+cnt*(cnt-1)%MOD*(cnt-2)%MOD*_2)%MOD;
			g[i][4]=(g[i][4]+mul)%MOD;
		}
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>p,_2=qpow(2,p-2,p),_3=qpow(3,p-2,p);
	g[0][0]=1,f[1][0]=f[1][1]=f[1][2]=1,s[1]=3;
	insert(1);
	ffor(i,2,n) {
		f[i][0]=(g[i-1][3]+g[i-1][2]+g[i-1][1]+g[i-1][0])%MOD;	
		f[i][1]=(f[i][0]-g[i-1][3])%MOD;
		f[i][2]=(f[i-1][0]+f[i-1][1])%MOD;
		ffor(j,1,i-2) if(i-1-j>j) {
			int s1=(f[j][0]+f[j][1])%MOD,s2=(f[i-1-j][0]+f[i-1-j][1])%MOD;
			f[i][2]=(f[i][2]+s1*s2)%MOD;
		}
		if(i%2==1) {
			int s=(f[i/2][0]+f[i/2][1])%MOD;
			f[i][2]=(f[i][2]+s*(s+1)%MOD*_2)%MOD;
		}
		s[i]=(f[i][0]+f[i][1]+f[i][2])%MOD,insert(i);
	}
	int ans=0;
	if(n%2==0) {
		ans=(ans+f[n/2][0]*f[n/2][1])%MOD;
		ans=(ans+f[n/2][0]*f[n/2][2])%MOD;
		ans=(ans+f[n/2][1]*f[n/2][2])%MOD;
		ans=(ans+f[n/2][0]*(f[n/2][0]+1)%MOD*_2)%MOD;
		ans=(ans+f[n/2][1]*(f[n/2][1]+1)%MOD*_2)%MOD;
	}
	memset(g,0,sizeof(g)),g[0][0]=1;
	ffor(i,1,(n-1)/2) Insert(i);
	ans=(ans+g[n-1][1]*2+g[n-1][2]*2+g[n-1][3]*2+g[n-1][4])%MOD;
	memset(g,0,sizeof(g)),g[0][0]=1;
	ffor(i,1,n) f[i][2]=0;
	ffor(i,1,(n-1)/2) insert(i);
	ans=(ans+g[n-1][1]+g[n-1][2]+g[n-1][3])%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

