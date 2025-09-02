# [POI 2014] SUP-Supercomputer

## 题目描述

Byteasar has designed a supercomputer of novel architecture.

```plain
It may comprise of many (identical) processing units.
```
Each processing unit can execute a single instruction per time unit.

The programs for this computer are not sequential but rather have a tree structure.

Each instruction may have zero, one, or multiple subsequent instructions,    for which it is the parent instruction.

The instructions of the program can be executed in parallel on all available    processing units.  Moreover, they can be executed in many orders: the only    restriction is that an instruction cannot be executed unless its parent    instruction has been executed before.  For example, as many subsequent    instructions of an instruction that has been executed already can be    executed in parallel as there are processing units.

Byteasar has a certain program to run.  Since he likes utilizing his resources    optimally, he is wondering how the number of processing units would affect the running time.

He asks you to determine, for a given program and number of processing units,    the minimum execution time of the program on a supercomputer with this many processing units.

给定一棵N个节点的有根树，根节点为1。Q次询问，每次给定一个K，用最少的操作次数遍历完整棵树，输出最少操作次数。每次操作可以选择访问不超过K个未访问的点，且这些点的父亲必须在之前被访问过。


## 样例 #1

### 输入

```
20 1
3
1 1 1 3 4 3 2 8 6 9 10 12 12 13 14 11 11 11 11
```

### 输出

```
8
```

# 题解

## 作者：League丶翎 (赞：26)

# [POI2014]SUP-Supercomputer

## 1 一些思考

之前做这题是因为做了一套 `CSP-S` 模拟题

然后被这道题坑了（惨兮兮）

出那套题的人估计自己也没有想清楚，所有部分分的解法都是错的（各种知世不对的贪心）...

当然满分做法是正确的

但是在目前看到的各种证明中都是各种错误贪心（狗头保命

对于满分做法的解释也是模糊不清（贪心+显然

所以来证明下最优方案的存在性

可能有锅，轻喷

## 2 题意

略

## 3 Solution

### 3.1 最优方案

假设存在一种策略满足下面条件

1. 能够使得前 $x$ 层用 $x$ 步删完 （一）
2. 后面每次都可以删除 $k$ 个节点 （二）

那么这样的策略必然是最优的

证明很显然，前 $x$ 层不可能用少于 $x$ 步删完，后面的节点每次删除 $k$ 个（最大值）次数肯定是最少的

那么现在的问题是是否存在这样一种策略满足上面的条件

### 3.2 最优方案存在的证明

假设足够聪明的你当前已经取完了前 $x$ 层，但是用了 $y$ 步 $(x\leq y)$，并且后面节点可以每次删除 $k$ 个来清空，也就是满足 （二）

这样的方案是很好构造的，因为并没有要求前面 $x$ 层 **最** 优

显然的，上方必然存在另外一个满足已经取完了前 $x'$ 层，使用了 $y'$ 步 $(x'\leq y')$的状态

没错，这里我们不要求后面节点可以每次删除 $k$ 个来清空

我们取最近的一个这样的状态 $x'$ ，对于 $x'$ 层到 $x$ 层进行分析

那么，对于 $(x,y)$ 和 $(x',y')$ 有两种关系：

1. $y-x>y'-x'$
2. $y-x=y'-x'$

#### 3.2.1 第一种情况

对于第一种情况，我们用 $p>x-x'$ 步取完了第 $(x',x]$ 层

对于足够聪明的你，显然会尽量不让这 $x-x'$ 层中的节点 “卡住” 而选择某种方案，那么这 $p$ 步每一步都取到了 $k$ 个节点，那么第 $x'$ 层也满足（二），并且相比第 $x$ 层来说 $y'-x'<y-x$ ，也就是说更接近满足 （一） 了

那么如果当前的状态使得你不得不被 “卡住” ，那么被 “卡住” 时，从 $x'$ 层到被卡住的层的所有点必然已经全部被删除，否则你就可以选择这些点中深度最浅的进行删除。到这里你会发现，这与假设 `最近的一个这样的状态 x'` 不符，产生矛盾，故不成立

那么在第一种情况中，可以将 $(x,y)$ 替换为 $(x',y')$ ，使得在满足（二）的条件下更接近满足（一）

#### 3.2.2 第二种情况

对于第二种情况，我们利用 $x-x'$ 步取完了第 $(x',x]$ 层

在这里需要分别讨论：

假设 $x-x'>1$，根据上面的证明，$(x+1,x')$ 层的删除必然可以每次删 $k$ 个，并且每层都恰好是 $k$ 个

假设 $x-x'=1$，那么说明第 $x$ 行 $\leq k$

显然每层 $k$ 个的情况可以直接由 $(x,y)$ 转移到 $(x',y')$ 而忽略掉，而 $<k$ 个的情况可以通过从上面 $[1,x']$ 层选择一些叶子节点 “补” 到当前层来使得当前层到 $k$ 个，显然，这样的方法仅仅会使得 $y'$ 减小

那么，通过 “补” 的方式，也使得 $x'$ 层在满足（二）的情况下更接近（一）

#### 3.2.3 总结

所以说，通过转移到最近的 $(x',y')$ ，必然是满足（二），且更加接近满足（一）的

倘若一直没有找到满足（一）的层，而第一层必然是满足（一）的，我们令第一层为 $x'$ 即可，那么第一层也就满足（二）了

故必然存在这样的层 $x$ 同时满足（一）（二），即存在最优方案

## 4 代码

略

---

## 作者：Querainy (赞：16)

大概翻译了一下[波兰语题解](https://fajnezadania.wordpress.com/2014/04/13/superkomputer/)。

倒过来变成剥叶子。这有一个好处，我们剥一个叶子不会让叶子的数量增加，只会让它不变或减少 $1$。抽象地来说，正着和倒着的区别在于我们希望一些"比较自由的操作"往前塞还是往后塞。

首先我们知道如果现在叶子数 $\leq k$，所需的轮数就是树的高度。如果叶子数 $\geq k$，我们每次必然选满 $k$ 个。

由于叶子的数量不会增加，而到了叶子数 $=k$ 的时候答案就确定了，一个贪心的想法就是先剥最深的叶子使得树高尽可能减小。接下来我们证明它的正确性。

对于一个深度 $h$，设 $c_h$ 是 $\geq h$ 的所有层的点数和，那么我们至少需要 $\lceil\frac{c_{h+1}}{k}\rceil$ 轮才能剥完它们，接下来还需要 $h$ 轮才能剥完上面的，于是 $\lceil\frac{c_{h+1}}{k}\rceil$ 是答案的一个下界。那么 $\max\limits_h h+\lceil\frac{c_{h+1}}{k}\rceil$ 也是一个下界，猜测它就是答案。接下来证明这个贪心达到了这个下界。

考虑现在我们选择了深度最大的 $k$ 个叶子，有深度相同的则任意选。设其中最浅的那个的深度是 $d$，树高是 $H$。先假设 $H$ 减小了 $1$。

- 对于 $h<d$，$h+\lceil\frac{c_{h+1}}{k}\rceil$ 减少了 $1$。

- 对于 $h\geq d$，由于选择了深度为 $d$ 的叶子，$>d$ 的每一层点数都 $<k$。这是因为每一层的点数都不超过下一层点数加上这一层叶子数。在这一轮操作前后都是这样的。于是我们知道对于 $h\geq d$，有 $h+\lceil\frac{c_{h+1}}{k}\rceil\leq h+1+\lceil\frac{c_{h+2}}{k}\rceil$，这是因为 $h+1$ 层的点数 $<k$。于是 $\max\limits_{d\leq h\leq H}h+\lceil\frac{c_{h+1}}{k}\rceil=H$，而 $H$ 减小了 $1$。

于是我们知道 $\max\limits_h h+\lceil\frac{c_{h+1}}{k}\rceil$ 就减小了 $1$。如果 $H$ 不变，根据上面的第一个 case，问题只在于 $h=H$ 的情况，而 $H$ 层点数 $>k$，我们知道 $H<\max\limits_h h+\lceil\frac{c_{h+1}}{k}\rceil$。这就结束了。

剩下的问题是如何对每个 $k$ 求 $\max\limits_h h+\lceil\frac{c_{h+1}}{k}\rceil$。考虑怎么把取整去掉，我们把 $h$ 塞进去，就变成 $\max\limits_h \lceil\frac{hk+c_{h+1}}{k}\rceil=\lceil\max\limits_h \frac{hk+c_{h+1}}{k}\rceil$。也就是有一堆一次函数 $h+c_{h+1}x$ 了。为了使用凸壳，转而考虑有一些点 $(-c_{h+1},h)$，用斜率为 $x$ 的直线去截，截距即为 $h+c_{h+1}x$。要求截距的最大值，求上凸壳然后扫过去即可。复杂度 $O(n)$。

---

## 作者：Gmt丶FFF (赞：13)

首先有一个结论，树中存在一个深度 $dep$，使得深度小于等于 $dep$ 的点只需 $dep$ 次覆盖完，而大于 $dep$ 的除最后一次外其他每次都可以填充 $k$ 次。

证明：在 $dep$ 上面的所有点如果不能连续填充 $k$ 次，说明均摊下来每一层的点数肯定小于 $k$，这样的话一定存在上面的只用取 $dep$ 次的深度，那下面层数均摊大于 $k$，所以每次能填满 $k$ 次，所以就是在找一个层数均摊为 $k$ 的分界点，那么这种层数一定存在。

层数均摊什么意思呢，就是如果一层的节点大于了 $k$，我们就将多余的节点放到下一个一层不足 $k$ 个的深度上去。

现在我们就是对于每一个 $k$，找到这个深度即可。

假设 $i$ 是这个分界点，那么对于其他的深度，答案一定是小于等于它的。

证明上述：若深度小于 $i$，那么会多包含能填满 $k$ 的深度，那么就会多选节点，如果深度大于 $i$，那么层度均摊大于 $k$ 的一层会被一次选完，明显这两种情况都更优。

那么我们就可以列出式子，设 $sum_i$ 为在 $i$ 层及以下的节点个数。

那么 $i+\left\lceil\frac{sum_i}{k}\right\rceil\ge j+\left\lceil\frac{sum_j}{k}\right\rceil$。

相当于我们要求一个 $i$ 使得 $i+\left\lceil\frac{sum_i}{k}\right\rceil$ 最大。

设答案为 $ans$，那么：

$$\begin{aligned}

\\ans&=i+\left\lceil\frac{sum_i}{k}\right\rceil

\\k\times ans&=k\times i+sum_i

\\-sum_i&=k\times i-k\times ans

\end{aligned}$$

上面明显是个斜率式子，考虑维护凸包，由于要求最大值，而截距越大答案越小，所以考虑维护下凸包。

那么每一个点即为 $(i,sum_{i+1})$。

维护凸包后，对于询问，按 $k$ 递减排序，用单调队列去找凸包上的点即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define pii pair<int,int>
using namespace std;
const int N=1e6+5;
int n,m,q[N],dep[N],sum[N],maxn,ans[N];
pii a[N];
int cmp(pii x,pii y)
{
	return x.second<y.second;
}
inline double slope(int x,int y)
{
	if(x==y)return 1e9;
	return (-sum[x+1]+sum[y+1])*1.0/1.0/(x-y);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d",&a[i].second),a[i].first=i;
	sort(a+1,a+1+m,cmp);
	sum[1]=dep[1]=1;
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		dep[i]=dep[x]+1;
		maxn=max(maxn,dep[i]);
		sum[dep[i]]++;
	}
	for(int i=maxn;i>0;i--)sum[i]+=sum[i+1];
	int l=1,r=1;
	for(int i=1;i<=maxn;i++)
	{
		while(l<r&&slope(q[r],q[r-1])>=slope(i,q[r]))r--;
		q[++r]=i;
	}
	for(int i=1;i<=m;i++)
	{
		while(l<r&&slope(q[l],q[l+1])<a[i].second)l++;
		ans[a[i].first]=q[l]+(sum[q[l]+1]+a[i].second-1)/a[i].second;
	}
	for(int i=1;i<=m;i++)printf("%d ",ans[i]);
	return 0;
}
/*
20 3
2 3 1
1 1 1 3 4 3 2 8 6 9 10 12 12 13 14 11 11 11 11
*/
```


---

## 作者：Liveddd (赞：12)

提供一种新的解法

考虑按照 $dep$ 分层。记 $cnt_{dep}$ 表示深度为 $dep$ 的点数。考虑从大到小枚举 $k$，将对于每个 $k$ 的最优解都求出来。

在 $k$ 足够大时，显然一次能且仅能选择同一层的点，即 $ans_k=max\{dep_i\}$。当某一时刻，$cnt_i>k$，那么我们无法在一次内选择完第 $i$ 层的点，需要将其中 $cnt_i-k$ 个点挪到下一层选取。

题目中限制了拥有父子关系的两个点无法同时选择，我们需要证明只需要将剩下的点向下挪动一层就能够得到合法解。

假设此时 $cnt_{i-1}\le k$。  
我们需要在第 $i$ 次和第 $i+1$ 共选取 $2k$ 个点其中第 $i$ 层选取 $cnt_i$ 个，第 $i+1$ 层选取 $2k-cnt_i$ 个点。  
1\. $cnt_{i+1}<2k-cnt_i$：第 $i+1$ 天未取满 $k$ 个点，并不影响结果。  
2\. $cnt_{i+1}>2k-cnt_i$：将第 $i+1$ 层多余的点挪向第 $i+2$ 层，这显然是一个相同的子问题。  
3\. $cnt_i>2k$：将第 $i$ 层多余的点和第 $i+1$ 层所有点挪向第 $i+2$ 层，这显然又是一个相同的子问题。  
而这 $2k$ 个点拥有父子关系的点对数 $<k$，故一定能找到合法方案。

也可以感性理解，既然当 $k'>k$ 时，被选中的点可以在当层选择，那么挪到下一层就更容易有合法方案了。

由上面的结论我们可以得到，我们始终可以把操作一次多余的点挪向下一层，保证每层的点数 $\le k$，最多有 $n$ 层。  
这个时候暴力维护是不行的，因为我们并不关心多出来的点来自哪一层，我们尝试将多层放在一起合并后维护。  
我们于是就维护的就是一段区间 $[l,r]$，表示连续 $r-l+1$ 天仅选取第 $[l,r]$ 层的点，且一定取完，即 $\sum_{i=l}^r cnt_i\le (r-l+1)\times k$。  
故我们只需要用维护区间，每次将堆顶不合法区间取出，向下合并即可。

时间复杂度 $O(nlogn)$ ,比隔壁斜率优化 $O(n)$ 要慢，但也算提供新的思路吧qwq。

_**Code:**_

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<bitset>
#define ll long long
using namespace std;
const int N=1e6+10;
template<class T>
inline void read(T &x)
{
    x=0;int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=-x;
}
template<class T,class ...T1>
inline void read(T &x,T1&...x1)
{
    read(x),read(x1...);
}
struct Node
{
	int l,r,cnt;
	inline bool operator<(const Node &rhs)const {
		return (ll)cnt*(rhs.r-rhs.l+1)<(ll)rhs.cnt*(r-l+1);
	}
	inline bool check(int k)const {
		return (ll)(r-l+1)*k<cnt;
	}
};
int n,m;
int query[N],ans[N];
int cnt[N],dep[N];
int ed[N];
bool vis[N];
priority_queue<Node>q;
int main()
{
    read(n,m);
    for(int i=1;i<=m;i++)
    	read(query[i]);
    ++cnt[dep[1]=1];
    int res=1;
    for(int i=2;i<=n;i++)
    {
    	int fa;
    	read(fa);
    	++cnt[dep[i]=dep[fa]+1];
    	res=max(res,dep[i]);
	}
	for(int i=1;i<=n;i++)
	{
		ed[i]=i;
		q.push((Node){i,i,cnt[i]});
	}
	for(int k=1e6;k>=1;k--)
	{
		while(q.top().check(k))
		{
			Node x=q.top();
			q.pop();
			if(vis[x.l])
				continue;
			vis[x.r+1]=1;
			res=max(res,ed[x.l]=ed[x.r+1]);
			cnt[x.l]+=cnt[x.r+1];
			q.push((Node){x.l,ed[x.l],cnt[x.l]});
		}
		ans[k]=res;
	}
	for(int i=1;i<=m;i++)
		printf("%d ",ans[query[i]]);
    return 0;
}
```


---

## 作者：Alex_Wei (赞：9)

> *X. [P3571 [POI2014]SUP-Supercomputer](https://www.luogu.com.cn/problem/P3571)
>
> 题意简述：一棵以 $1$ 为根的树。$q$ 次询问，每次给出 $k$，求至少要多少次**同时访问**不超过 $k$ 次父节点已经被访问过的节点，才能访问完整棵树。根节点无限制。
> 
> $n,q\leq 10^6$。
>
> 节选自 [DP 优化方法大杂烩](https://www.cnblogs.com/alex-wei/p/DP_Involution.html) 7. 斜率优化例题 X。

sweet tea.

主要讲一下怎么用斜率优化，取 $\max$ 的正确性别的题解说明得已经很好了。

对于每一个 $k$，一定存在 $i$ 使得深度不大于 $i$ 的节点用 $i$ 次访问，且深度大于 $i$ 的节点每次都能访问 $k$ 个（除了最后一次）。记 $s_i$ 表示深度不小于 $i$ 的节点个数，答案即为 $\max_{i=1}^d\left(i+\lceil\dfrac{s_{i+1}}k\rceil\right)$，其中 $d$ 是最大深度。

若 $i$ 是最优决策，那么对于任意一个 $j\neq i$，有 $i+\lceil\dfrac{s_{i+1}}k\rceil\geq j+ \lceil\dfrac{s_{j+1}}k\rceil$。略作变形得到 $i-j \geq \lceil\dfrac{s_{j+1}-s_{i+1}}k\rceil$。令横坐标为深度，纵坐标为 $s_{x+1}$，再写成斜率的形式，即当 $j<i$ 时，$\dfrac{s_{i+1}-s_{j+1}}{i-j}\geq -k$，当 $j>i$ 时，$\dfrac{s_{i+1}-s_{j+1}}{i-j}\leq -k$。不难看出这是一个**上凸包**的形式，即**斜率递减**。

具体地，我们对 $(i,s_i)$ 建出上凸包，然后当 $k$ 递增时，$-k$ 递减，顶点会向横坐标大的方向移动，用指针维护即可。时间复杂度 $\mathcal{O}(n)$。

经过卡常拿到了最优解。

```cpp
const int N=1e6+5;

int n,q,mxd,mxq,dep[N],f[N],qu[N];
int d[N],hd=1,tl;
ll s[N];

int main(){
	cin>>n>>q,dep[1]=s[1]=1;
	for(int i=1;i<=q;i++)mxq=max(mxq,qu[i]=read());
	for(int i=2,a;i<=n;i++)mxd=max(mxd,dep[i]=dep[read()]+1),s[dep[i]]++;
	for(int i=mxd-1;i;i--)s[i]+=s[i+1];
	for(int i=0;i<=mxd;i++){
		while(hd<tl&&(s[d[tl]+1]-s[d[tl-1]+1])*(i-d[tl])<=(s[i+1]-s[d[tl]+1])*(d[tl]-d[tl-1]))tl--;
		d[++tl]=i;
	}
	for(int i=1;i<=mxq;i++){
		while(hd<tl&&s[d[hd+1]+1]-s[d[hd]+1]>-i*(d[hd+1]-d[hd]))hd++;
		f[i]=d[hd]+(d[hd]==mxd?0:((s[d[hd]+1]-1)/i+1));
	}
	for(int i=1;i<=q;i++)print(f[qu[i]]),pc(' ');
	return flush(),0;
}
```

---

## 作者：lhm_ (赞：9)

由数据范围可得出，不可能一次一次去进行回答询问，只能离线处理，然后$O(1)$解决。

考虑$DP$解决，先给出$DP$方程：

$f_i=max(j+ \lceil \frac{s_{j+1}}{i} \rceil)$ ($f_i$表示为当前一次操作最多访问$i$个未访问的点的最小操作次数，$s_i$表示表示深度$\geqslant i$的节点个数)

式子右边的含义为前$j$次操作访问完前$j$层节点，后面每次都访问$i$个节点，可以发现这样的操作是最优的。若从贪心的角度来看，每次操作一定是尽量访问更多的点，若此时有额外的点可供选择，优先访问有儿子的节点，为以后操作保证最优性提供保障。

先感性地证明这个式子的正确性，也就是这个地方为什么取$max$。

① 若我们无法做到前$j$次操作访问完前$j$层节点，假设存在$k$，可以做到前$k$次操作访问完前$k$层节点。可以发现第$k$层在第$j$层上面，那么在$k$层到$j$层的节点，我们无法做到通过$j-k$次操作全部访问完，可以得出式子：

$\lceil \frac{s_{k+1}-s_{j+1}}{i} \rceil>j-k$

变形得：

$k+\lceil \frac{s_{k+1}}{i} \rceil>j+\lceil \frac{s_{j+1}}{i} \rceil$

发现合法状态$k$比不合法状态$j$操作次数要多，所以通过取$max$可以去除$j$这种不合法情况。

② 若我们无法做到前$j$次操作访问完前$j$层节点时后面每次都访问$i$个节点，假设存在$k$，可以做到前$k$次操作访问完前$k$层节点时后面每次都访问$i$个节点。可以发现第$k$层在第$j$层下面，那么可以做到每次都访问$i$个节点的层数会变小，所以合法状态$k$会比不合法状态$j$操作次数多。

由这两种情况，我们就可以得出，为了保证状态合法，转移时应取$max$。

设合法状态$j,k$，假设状态$j$比状态$k$更优。

即$j+ \lceil \frac{s_{j+1}}{i} \rceil>k+ \lceil \frac{s_{k+1}}{i} \rceil$

$\lceil \frac{s_{j+1}-s_{k+1}}{i} \rceil>k-j$

$\frac{s_{j+1}-s_{k+1}}{j-k}<-i$

发现我们可以用斜率优化来优化复杂度，这里$x$为$j$，$y$为$s_{j+1}$，斜率为$-i$。

其他的一些实现细节就看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 1000010
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
int n,m,h,t;
ll deep_max,query_max;
ll f[maxn],s[maxn],q[maxn],query[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]=(edge){to,head[from]};
    head[from]=edge_cnt;
}
double x(int i)
{
    return i;
}
double y(int i)
{
    return s[i+1];
}
double slope(int j,int k)
{
    return (y(j)-y(k))/(x(j)-x(k));
}
void dfs(int x,ll dep)
{
    s[dep]++;
    deep_max=max(deep_max,dep);
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        dfs(y,dep+1);
    }
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=m;++i) 
        read(query[i]),query_max=max(query_max,query[i]);
    for(int i=2;i<=n;++i)
    {
        int fath;
        read(fath),add(fath,i);
    }
    dfs(1,1);
    for(int i=deep_max;i;--i) s[i]+=s[i+1];
    for(int i=1;i<=deep_max;++i)
    {   
        while(h<t&&slope(q[t],i)>slope(q[t],q[t-1])) t--;
        q[++t]=i;
    }
    for(int i=1;i<=query_max;++i)
    {
        while(h<t&&slope(q[h],q[h+1])>-i) h++;
        int j=q[h];
        f[i]=j+(s[j+1]+i-1)/i;
    }
    for(int i=1;i<=m;++i) printf("%lld ",f[query[i]]);
	return 0;
}
```


---

## 作者：_NightFire666_ (赞：3)

# P3571「POI2014」SUP-Supercomputer 题解

一道 **“较”** 水的黑题 ~~（可一开始苦思冥想还是不会）~~。

~~本蒟蒻的第一篇黑题题解，求赞。~~

### 题意简化
给定一棵 $n$ 个节点、根节点为 $1$ 的有根树。$q$ 次询问中每次给定一个 $k$，输出需要最少用几次操作次数 **删除** 完整棵树。每次操作可以选择 **删除** 不超过 $k$ 个未访问的点，且这些点 **没有父亲**。~~（血腥的味道）~~

### 前置知识
有一个 **小小** 的结论：存在一个 $i$，满足可以用 $i$ 次操作删掉所有深度小于等于 $i$ 的点，剩下的操作每次都删掉 $k$ 个点。

形式化地，设 $f_k$ 为 $k$ 对应的答案，$s_i$ 是深度大于 $i$ 的点数，有：
$$
f_k=\max_i \lceil\frac{s_i}{k}\rceil+i
$$

- Why？

~~显然~~ ，要证明 $f_k=\max_i \lceil\frac{s_i}{k}\rceil+i$，转换为不等式，可分别证明 $f_k\ge\max_i \lceil\frac{s_i}{k}\rceil+i$ 和 $f_k\le\max_i \lceil\frac{s_i}{k}\rceil+i$：
1. 证明 $f_k\ge\max_i \lceil\frac{s_i}{k}\rceil+i$ ：
可以注意到一个性质，要删除至少一个深度为 $i$ 的点，至少需要 $i$ 次操作。那么有 $f_k\ge \max_i \lceil\frac{s_i}{k}\rceil+i$。

2. 证明 $f_k\le\max_i \lceil\frac{s_i}{k}\rceil+i$ ：
设 $f_{k,i}=i+\lceil\frac{s_i}{k}\rceil$，$f_{k,i}$ 在 $i=a$ 时取最大值。我们假设 $b$ 步可以删除完前 $b$ 层的节点，且这是满足条件的最大的 $b$，即证 $a=b$。
    - 先证 $a\ge b$：对于 $c<b$，若 $f_{k,c}>f_{k,b}$，则深度范围在 $(c,b]$ 之间的点数大于 $k(b−c)$，删掉一个第 $c$ 层的点至少要 $c$ 步，删掉 $c+1$ 到 $b$ 层的所有点要大于 $(b−c)$ 步，那么前 $b$ 层肯定 $b$ 次删不完，矛盾。因此 $a\ge b$。

    - 再证 $a\le b$：
        1. 第 $b+1$ 层一定有超过 $k$ 个节点，$f_{k,b+1}\le f_{k,b}$。
        2. 若第 $b+1$，$b+2$ 层点数之和不超过 $2k$，那么第 $b+2$ 层的点数一定不足 $b+1$ 层的，我们可以 $b+2$ 次删除完前 $b+2$ 层，矛盾，因此第 $b+1$，$b+2$ 层点数之和大于 $2k$，$f_{k,b+2}\le f_{k,b}$。

      以此类推 $a\le b$。
所以 $a=b$，即 $f_k\le\max_i \lceil\frac{s_i}{k}\rceil+i$。

根据上面对 $a\le b$ 的证明，可以归纳证明第 $b+1$ 到第 $b+t$ 层的点数之和大于 $kt$，于是我们只需要一层一层删掉，并优先删除有儿子的结点就一定可行。这样 $f_k=\max_i \lceil\frac{s_i}{k}\rceil+i$，证毕。

### 题目解法
嘿嘿，大脑有没有烧了呢？有了以上结论，这道题就可以 ~~秒~~ 切了。

对 $f_k=\max_i \lceil\frac{s_i}{k}\rceil+i$ 进行变形：
$$
f_k=\max_i \lceil\frac{s_i}{k}\rceil+i=f_k= \max_i \lceil\frac{s_i+ki}{k}\rceil
$$
所以，只需求 $g_k=\max s_i+ki$ 。

则：$s_i=-ki+g_k$（$y=kx+b$）。

斜率优化即可，横坐标和斜率都单调，复杂度 $\mathcal{O}(n)$。

### **参考**代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,q[N],dep[N];
int sum[N],maxn,ans[N];
struct __{
    int x,y;
    bool operator<(const __ x)const{
        return y<x.y;
    }
}a[N];
double slp(int x,int y){
	if(x==y)return 1e9;
	return (sum[y+1]-sum[x+1])*1.0/(x-y);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>m;sum[1]=dep[1]=1;
	for(int i=1;i<=m;i++)
        cin>>a[i].y,a[i].x=i;
	stable_sort(a+1,a+m+1);
	for(int i=2,x;i<=n;i++){
		cin>>x; dep[i] = dep[x]+1;
		maxn = max(maxn , dep[i]);
		sum[dep[i]]=sum[dep[i]]+1;
	}
    for(int i=maxn;i>0;i--)
        sum[i]+=sum[i+1];
	int l=1,r=1;
	for(int i=1;i<=maxn;i++){
		while(l<r&&slp(i,q[r])<=slp(q[r],q[r-1]))
            r--;
		q[++r]=i;
	}
	for(int i=1;i<=m;i++){
		while(l<r&&a[i].y>slp(q[l],q[l+1]))
            l++;
        int k=q[l],Y=a[i].y,X=a[i].x;
		ans[X] = k+(sum[k+1]+Y-1)/Y ;
	}
	for(int i=1;i<=m;i++)
        cout<<ans[i]<<" ";
	return 0;
}
```

### 完 结 撒 花 ！ ！ ！
![](https://cdn.luogu.com.cn/upload/image_hosting/jsc0dugr.png)

---

## 作者：0xyz (赞：3)

实现上与已有所有题解不同。这份代码是可以通过测试的。分析部分有参考出题人（也许是吧）的题解。

首先我们发现，正着搞会有很多限制，所以考虑倒着搞，每次去掉一些叶子，至多 $k$ 个，而且没有任何其余限制。

令树高为 $H$，考虑第 $h$ 层，令 $s_h$ 表示整棵树上深度不小于 $h$ 的节点的个数。那么我们至少需要操作 $\left\lceil\dfrac{s_{h+1}}{k}\right\rceil$ 次才可以将深度大于等于 $h+1$ 的所有节点去掉。而对于深度为 $1$ 到 $h$ 的节点，容易知道不存在任何一次操作能同时删光两层，因为每次删完后，树都是连通的，所以这两层中一定存在一个节点是另一个的祖先，而一个还存在的节点的祖先必然不是叶子节点。那么想要删光这 $h$ 层就至少要操作 $h$ 次，所以答案 $ans\ge h+\left\lceil\dfrac{s_{h+1}}{k}\right\rceil$。由于答案对于每个 $h$ 都满足上式，所以 $ans\ge \max\limits_{h\le H}\bigg\{h+\left\lceil\dfrac{s_{h+1}}{k}\right\rceil\bigg\}$。

那么可不可以取等呢？我们设计贪心策略如下：每次去掉深度最大的 $k$ 个叶子节点点，如果有相同深度的就随便去掉，如果叶子节点不足 $k$ 个就全部去掉，这样一定能保证取的是叶子节点，并且尽量取满 $k$ 个，并且在去掉深度大于等于 $h+1$ 的所有节点后才去掉前 $h$ 层的点。

然后进行分类讨论：

1. 假设当前树高为 $H$，如果当前树的宽度不大于 $k$，很明显只需要 $H$ 次删光，并且因为每次至多删光一层，所以也只能至少 $H$ 次删光，此时 $ans$ 必然取等。

2. 如果当前树的宽度不大于 $k$，那么我们可以选择它最深的 $k$ 个叶子，并将它们删除，它们的深度分别为 $d_1\ge d_2\ge...\ge d_k$。同时，最深的一层，即深度为 $H$ 的一层必定删光，所以新树高 $H'=H-1$。

	1. 对于所有 $h<d_k$，在删除这 $k$ 个叶子后，它们对应的 $h+\left\lceil\dfrac{s_{h+1}}{k}\right\rceil$ 刚好减少 $1$。

	2. 对于所有 $h\ge d_k$，我们可以发现 $h>d_k$ 的所有层点数不超过下一层的点数加上这一层的叶子数，都不超过 $k$ 。所以第 $h+1$ 层的点数 $< k$，对于所有 $h\ge d_k$，有 $h+\left\lceil\dfrac{s_{h+1}}{k}\right\rceil\le h+1+\left\lceil\dfrac{s_{h+2}}{k}\right\rceil$，而最后一层，即深度为 $H'=H-1$ 的那一层的值为 $H-1$，所以对于所有 $h\ge d_k$，$h+\left\lceil\dfrac{s_{h+1}}{k}\right\rceil$ 都小于 $H-1$。

综上，在这种贪心策略下，每一次操作都可以使 $\max\limits_{h\le H}\bigg\{h+\left\lceil\dfrac{s_{h+1}}{k}\right\rceil\bigg\}$ 减小 $1$。

所以我们证明了 $ans=\max\limits_{h\le H}\bigg\{h+\left\lceil\dfrac{s_{h+1}}{k}\right\rceil\bigg\}$，要快速求对于每个 $k$，这个式子的最大值。将式子变一下变成 $ans=\max\limits_{h\le H}\bigg\{\left\lceil\dfrac{s_{h+1}+h\times k}{k}\right\rceil\bigg\}$。

容易知道对于固定的 $k$，分子越大，这个值单调不减，所以求分子最大值就行了。

于是题目变为给出 $n$ 条形为 $y=h\times x+s_{h+1}$ 的直线，要求 $x=k$ 时的最大值， 发现就是一个李超线段树的模板。由于没有范围限制，所以至多只需要修改 $\log n$ 级别的区间就可以了，单次修改和查询的复杂度都是 $O(\log n)$，所以总时间复杂度是 $O(n\log n)$，而且常数很小，可以通过此题。

亲测不开 O2 优化时，最慢的一个点 308ms。

```cpp
ll n,qwq,mxq=0,mxd=0,l=1,r=0,a[1000010],f[1000010],t[4000010],d[1000010],s[1000010];
inline ll cal(ll x,ll v){return s[x+1]+x*v;}
void upd(ll x,ll l,ll r,ll u){
	ll &v=t[x],mid=(l+r)>>1;
	if(cal(u,mid)>cal(v,mid))swap(u,v);
	if(cal(u,l)>cal(v,l))upd(x<<1,l,mid,u);
	if(cal(u,r)>cal(v,r))upd(x<<1|1,mid+1,r,u);
}
ll query(ll x,ll l,ll r,ll v){
	if(l==r)return cal(t[x],v);
	ll mid=(l+r)>>1;
	if(v<=mid)return max(cal(t[x],v),query(x<<1,l,mid,v));
	else return max(cal(t[x],v),query(x<<1|1,mid+1,r,v));
}
int main(){
	n=read();qwq=read();d[1]=s[1]=1;
	for(ll i=1;i<=qwq;i++)mxq=max(mxq,a[i]=read());
	for(ll i=2;i<=n;i++){d[i]=d[read()]+1;s[d[i]]++;mxd=max(mxd,d[i]);}
	for(ll i=mxd-1;i;i--){s[i]+=s[i+1];upd(1,1,n,i);}
	for(ll i=1;i<=mxq;i++)f[i]=(query(1,1,n,i)-1)/i+1;
	for(ll i=1;i<=qwq;i++){write(f[a[i]]);putchar(' ');}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/108276919)

---

## 作者：Iris_Aurora (赞：1)

学了不知道多少次斜率优化终于学会了并通过了这道题...

首先题意可以转化为每次至多可以删去 $k$ 个叶子节点，要求每次只能删去一层叶子节点，问最少多少次操作可以删去整棵树。

我们考虑对于一个询问，给出的 $k$ 为 $K$，我们发现执行一次删除操作有两种情况：

1. 当前叶子结点数量 $\ge K$ 个，那么删除 $K$ 个深度最深的节点，正确性显然。

2. 当前叶子结点数量 $< K$ 个，那么删除所有叶子节点。

我们令 $h_K$ 表示第一次出现情况 2 的时候树的深度，$s_{h_K+1}$ 表示深度 $\ge h_K+1$ 的节点的个数，则答案为 $h_K+\lceil\frac{s_{h_K+1}}{K}\rceil$。

我们可以发现 $h_K$ 满足当 $h=h_K$ 时，上式取到最大值，证明如下：

- 当 $h>h_K$ 时，实际的剩下的一次可以删去的叶子节点点比一次情况 2 的能删去的多，答案偏小。

- 当 $h<h_K$ 时，进行最后几次操作 1 时没有足够的点可供删除，答案偏小。

最后问题变成了求 $f_K=\max\{h+\lceil\frac{s_{h+1}}{K}\rceil\}=\max\{\lceil\frac{hK+s_{h+1}}{K}\rceil\}$。

即求 $hK+s_{h+1}$ 的最大值，发现 $hK$ 与 $h$ 和 $K$ 都有关，转化为 $b_i=y_j-k_ix_j$ 的形式，维护一个上凸壳即可。

附上代码：


```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
#define PII pair<ll,ll>
using namespace std;
const int MAXN = 1e6 + 10;
ll n,m,mxdep=1;
ll dep[MAXN],s[MAXN];
PII a[MAXN];
ll q[MAXN],l=1,r=0;
ll ans[MAXN];
int main(){
	scanf("%lld%lld",&n,&m);
	FL(i,1,m) scanf("%lld",&a[i].first),a[i].second=i;
	sort(a+1,a+m+1);
	s[1]=dep[1]=1;
	FL(i,2,n){
		ll x;
		scanf("%lld",&x);
		dep[i]=dep[x]+1;
		mxdep=max(mxdep,dep[i]);
		s[dep[i]]++;
	}
	FR(i,mxdep,1) s[i]+=s[i+1];
	q[++r]=0;
	FL(i,1,mxdep){
		while(l<r&&(s[q[r]+1]-s[q[r-1]+1])*(i-q[r-1])<=(s[i+1]-s[q[r-1]+1])*(q[r]-q[r-1])) r--;
		q[++r]=i;
	}//上凸壳斜率递减，k[i]=-i斜率递减。
	FL(i,1,m){
		while(l<r&&(s[q[l+1]+1]-s[q[l]+1])>-a[i].first*(q[l+1]-q[l])) l++;
		ans[a[i].second]=q[l]+(s[q[l]+1]+a[i].first-1)/a[i].first;
	}
	FL(i,1,m) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：Rem_CandleFire (赞：1)

有结论：存在一个深度 $d$ 使得小于等于 $d$ 的部分可以用 $d$ 次操作删完，大于 $d$ 的部分每次都可以取满 $k$ 个（除了最后一次）。

证明：首先如果一次操作取不到某个节点的所有儿子，那么将取不到的儿子接到能取到的儿子处对于结果没有影响。所以如果小于等于 $d$ 的部分取不满 $k$，则说明按上述方式重连之后每层不够 $k$ 个。而大于 $d$ 的部分能取到。于是结论成立。

设 $S_i$ 表示深度不小于 $i$ 的节点数。对于一个满足结论的深度 $i$，操作次数为 $i+\lceil \frac{S_{i+1}}{k}\rceil$。而对于一个 $k$，其答案为 $\max_{i=1}^{D}\{i+\lceil \frac{S_{i+1}}{k}\rceil\}$，其中 $D$ 表示树的最大深度。

考虑证明，现在假设 $i$ 不符合条件。如果存在 $j$ 使前 $j$ 层能用 $j$ 次操作取完，那么 $j<i,\lceil \frac{S_{j+1}-S_{i+1}}{k}\rceil > j-i$，即深度为 $j+1\sim i$ 这一段无法用 $j-i$ 次取到。移项得 $j+\lceil \frac{S_{j+1}}{k}\rceil>i+\lceil\frac{S_{i+1}}{k}\rceil$。

如果存在 $j$ 使得深度大于 $j$ 的部分每次能取满 $k$ 个，则 $j>i$，操作次数会增加。综上所述取最大值是正确的。

对于一个深度 $i$ 若其是最优决策点，那么推一下斜率式可以发现斜率是在不断减小的，说明是一个上凸包。先对深度建出凸包，然后指针过一遍即可。时间复杂度 $O(n)$，难度主要在于推 DP 式。

---

## 作者：JustPureH2O (赞：1)

[更好的阅读体验](https://justpureh2o.cn/articles/11186)

集训时讲到了这个题，刚好写篇题解记录一下思路。

题目地址：[P3571](https://www.luogu.com.cn/problem/P3571)

> 给定一棵 $n$ 个节点的有根树，根节点为 $1$。$q$ 次询问，每次给定一个 $k$，用最少的操作次数遍历完整棵树，输出最少操作次数。每次操作可以选择访问不超过 $k$ 个未访问的点，且这些点的父亲必须在这次操作之前被访问过。
>
> $n, q \leq {10^6}$。

这道题其实有一个裸结论可以套：

> 对于一棵树，一定存在一个最优解，满足：恰好用 $i$ 步操作删除完树上深度小于等于 $i$ 的节点，此后一定可以通过每次删除 $k$ 个节点把整棵树的所有节点删除完毕。

形式化地，令 $f(k)$ 为对于给定的 $k$ 所能达到的最小操作数，$s_i$ 为深度大于 $i$ 的节点总数。那么有：

$$
f(k)=\max\limits_{i\in Tree}\{i+\lceil\frac{s_i}{k}\rceil\}
$$

此时把它看作动态规划的转移方程，移项可以得到 $s_i=-ki+kf(k)$，注意到自变量和因变量具有单调性，可以进行斜率优化，能够把时间复杂度降到 $\mathcal O(n)$。

--- 

这道题重点在于如何证明转移方程的正确性。要想证明一个相等关系，可以从 $A\leq B$ 以及 $A\geq B$ 两个方面分别入手证明，只要两个条件均满足，则代表 $A=B$ 成立。

首先来证 $f(k)\geq\max\{i+\lceil\frac{s_i}{k}\rceil\}$：对于一个深度恰等于 $i$ 的节点，至少需要 $i$ 次操作，于是这是正确的。

再来证 $f(k)\leq\max\{i+\lceil\frac{s_i}{k}\rceil\}$：假设上式在 $i=a$ 时取得最大值，并令 $b$，假设前 $b$ 步可删去前 $b$ 层所有点，且它是满足该性质的最大的数。我们需要做的就是证明 $a=b$。

同样的思路，先证 $a\geq b$。考虑反证法，对于 $c<b$，若 $i=c$ 时的 $f(k)$ 大于 $i=b$ 时的 $f(k)$。那么：

$$
\begin{aligned}
c+\frac{s_c}{k}&>b+\frac{s_b}{k}
\\s_c-s_b&>k(b-c)
\end{aligned}
$$

而不等号左侧用两个前缀和相减代表所有深度介于 $c+1\sim b$ 之间的点的总数，删完所有 $c+1\sim b$ 层的节点的操作步数应该大于 $b-c$，又因为删除一个第 $c$ 层的节点需要 $c$ 步，那么前 $b$ 层仅用 $b$ 步无法删除完毕。与假设中 $b$ 的意义矛盾，于是 $a\geq b$ 得证。

接下来证 $a\leq b$：树的第 $b+1$ 层一定有超过 $k$ 个节点，有 $f(k)_{b+1}\leq f(k)_b$；对于 $b+1$ 和 $b+2$ 两层，若这两层的节点总数不超过 ${2k}$，那么 $b+2$ 层的节点数量一定小于 $k$，于是可以用 $b+2$ 次操作删完前 $b+2$ 层的点，与 $b$ 是满足条件的最大的数矛盾，故 $b+1$ 和 $b+2$ 两层节点总数一定大于 ${2k}$……以此类推，$b+1\sim b+n$ 层一共有超过 $nk$ 个节点。此时一定有 $a\leq b$ 成立。

综上所述，$a=b$。因为 $b+1\sim b+n$ 层节点数一定大于 $kn$，于是每次做删除 $k$ 个点的操作，并且优先删有孩子节点的节点即可。至此，整个结论得到证明。

最后就是套斜率优化的模板了：

```cpp
#include <bits/stdc++.h>
#define N 1000010
using namespace std;

int dp[N];
int dep[N], s[N];
int query[N];
int q[N];
int hh = 0, tt = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    int maxd = 0, maxq = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> query[i];
        maxq = max(maxq, query[i]);
    }
    s[1] = dep[1] = 1;
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        dep[i] = dep[x] + 1; // 其实建单向边用DFS处理节点深度也是可以的，只是这道题并没这个必要？
        s[dep[i]]++;
        maxd = max(maxd, dep[i]);
    }
    for (int i = maxd; i; i--) s[i] += s[i + 1]; // 处理 i 层及更深层的节点总数
    // 单调队列维护凸包
    for (int i = 1; i <= maxd; i++) {
        // 用交叉相乘法以免出题人卡精度
        while (hh < tt && (s[q[tt] + 1] - s[i + 1]) * (q[tt] - q[tt - 1]) < (s[q[tt] + 1] - s[q[tt - 1] + 1]) * (q[tt] - i)) tt--;
        q[++tt] = i;
    }
    for (int i = 1; i <= maxq; i++) {
        while (hh < tt && (s[q[hh] + 1] - s[q[hh + 1] + 1]) < -i * (q[hh] - q[hh + 1])) hh++;
        int j = q[hh];
        dp[i] = j + (s[j + 1] + i - 1) / i; // 套转移方程
    }
    for (int i = 1; i <= m; i++) cout << dp[query[i]] << ' ';
    cout << endl;
    return 0;
}
```

$\texttt{The End}$

---

## 作者：PosVII (赞：1)

### 前言

------------

李超线段树做法。

### 思路

------------
考虑一个伪算：我们对于前 $i$ 层，每一层的点数量都小于 $k$，直到第 $i+1$ 层的点数量大于等于 $k$，我们每次只需要优先取这一排点中非叶子的点，这样下一次操作的点数量仍然大于等于 $k$，如果设第 $i+1$ 层及以后的点数量为 $sum$，那么答案就是 $i + \lfloor \frac{sum}{k} \rfloor$。

但是很显然这是错误的，因为可能第 $i+1$ 行只有一个非叶子的点且它在一条链上，这样后面的操作有可能取不满。只有 $50$ 分。

但是这启发了我们一个新思路，考虑维护一个序列，$a_{i}$ 表示深度为 $i$ 的点的数量，每次 $a_{i}=max(0,a_{i}-k)$，然后 $a_{i+1}=a_{i+1}+a_{i}$，答案就是最后一个 $a_{i}>0$ 的 $i+1$。设最大深度为 $mx$，找到最大的 $a_{i}=0,i \leq mx$ 的 $i$。设深度大于 $i$ 的点数量为 $sum$，答案就是 $i + \lfloor \frac{sum}{k} \rfloor$，此时取答案的点 $i$ 是唯一的。

发现如果 $j<i$ 那么有 $j + \lfloor \frac{sum`}{k} \rfloor < i + \lfloor \frac{sum}{k} \rfloor$，因为 $j$ 之后每次操作都取满了，结果一定优于 $i$。

而 $j>i$ 那么也有 $j + \lfloor \frac{sum`}{k} \rfloor < i + \lfloor \frac{sum}{k} \rfloor$，因为 $j$ 一定会取 $>k$ 的点数，所以一定优于 $i$。

懒得写斜率优化，写了个丑陋李超树，就不放了。

---

## 作者：__O_v_O__ (赞：0)

有一个贪心的直觉：最优方案形如前 $x$ 层 $x$ 步删完，后面每次删 $k$ 个。证明太复杂，这不是这篇文章的重点。

于是预处理出 $c_i$ 表示深度大于 $i$ 的节点个数，那么答案为 $\max\limits_{i}\{i+\left\lceil\frac{c_i}{k}\right\rceil\}$，变形得到 $\max\limits_{i}\{\left\lceil\frac{c_i+ki}{k}\right\rceil\}$。

于是转化为求 $f_k=c_i+ki$ 的最大值。观察到这个式子就是斜率优化的形式（$b=y-tx$，其中截距 $b=f_k$ 是待求答案，斜率 $t=-k$ 是定值，$x$ 和 $y$ 都只与 $i$ 有关）。这里我们细讲一下斜率优化。

我们把所有 $(x,y)$ 的可能值 $(i,c_i)$ 看作平面上的点，我们要求的就是对于一条斜率为 $-k$ 且穿过至少一个点的直线，它的截距 $b$ 最大是多少。

我们考虑拿一条斜率为 $-k$ 的直线从平面的右上角扫下来，容易发现，它第一个碰到平面上的点时，此时的 $b$ 一定是最大的。这样做复杂度很高，但手模一下我们发现，很多点是永远不会被用到的，具体来说，只有"最外面一层"的点才有用。

研究一下这些点的性质，显然它们形成了一个上凸壳（的右半部分），满足对于任意 $i$，$i$ 和 $i-1$ 组成直线的斜率大于 $i$ 和 $i+1$ 的斜率（因为斜率都是负数）。这个凸壳可以简单维护，我们使用一个队列，每次想要把一个点加入凸壳时，我们判断队列最后两个点加上它之后是否满足上面斜率的性质，不满足则弹出队尾。直到条件满足，把这个点加入即可。

于是我们现在就是拿一根直线去切凸壳。考虑人为给 $k$ 离线排序，那么每次直线斜率减小，只会"越来越斜"，显然切到的点也会有单调性。于是依次处理询问，每次找切点，答案就是这根直线切到这个点时的截距。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5;
int n,m,q[N],de[N],l=1;
int s[N],mx,an[N],r;
struct A{
	int x,y;
	bool operator<(const A&x)const{return y<x.y;}
}a[N];
double sl(int x,int y){
	if(x==y)return -1e9;
	return (s[x+1]-s[y+1])*1.0/(x-y);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m,s[1]=de[1]=1;
	for(int i=1;i<=m;i++)
		cin>>a[i].y,a[i].x=i;
	sort(a+1,a+m+1);
	for(int i=2,x;i<=n;i++){
		cin>>x,de[i]=de[x]+1;
		mx=max(mx,de[i]),s[de[i]]++;
	}
	for(int i=mx;i>0;i--)s[i]+=s[i+1];
	for(int i=1;i<=mx;i++){
		while(l<=r&&sl(i,q[r])>=sl(q[r],q[r-1]))r--;
		q[++r]=i;
	}
	for(int i=1;i<=m;i++){
		while(l<r&&-a[i].y<sl(q[l],q[l+1]))l++;
		an[a[i].x]=q[l]+ceil(s[q[l]+1]*1.0/a[i].y);
	}
	for(int i=1;i<=m;i++)cout<<an[i]<<" ";
	return 0;
}
```

---

## 作者：WilliamFranklin (赞：0)

### Solution

我们反向考虑，考虑转化成一次操作为删除树上不超过 $k$ 个叶子节点。我们将一次操作若删除了 $k$ 个叶子节点则称为操作 $1$，若小于 $k$ 个则称为操作 $2$，同时我们发现执行操作 $2$ 时就相当于删掉了树上最底下一层的节点。

考虑一个贪心策略，就是每次删都删深度前 $k$ 大的叶子节点，若小于 $k$ 个，那就这几个叶子节点都删掉，那么将整棵树删光且用最小次数，一定是先执行 $x$ 次操作 $1$，然后再执行 $y$ 次操作 $2$。

我们设 $sup$ 为最大深度，$s_{i}$ 表示深度大于等于 $i$ 的节点个数，$f_{i}$ 表示当 $k = i$ 时的答案。

则当 $k = i$ 时，我们按照上面策略得到共需 $h$ 次操作 $2$，那么 $f_{i} = h + \lceil\frac{s_{h + 1}}{i}\rceil$。但问题是我们怎么找这个 $h$。

我们很容易发现无论是 $h' < h$ 或者 $h' > h$ 时，都是不合法的，且 $h' + \lceil\frac{s_{h' + 1}}{i}\rceil$ 一定是要小于等于 $h + \lceil\frac{s_{h + 1}}{i}\rceil$ 的，所以我们可以将 $f{i}$ 写成这样：

$$
f_{i} = \max_{0 \le h \le sup}\{h + \lceil\frac{s_{h + 1}}{i}\rceil\}
$$

变下形：

$$
f_{i} = \max_{0 \le h \le sup}\{\lceil\frac{ih + s_{h + 1}}{i}\rceil\}
$$

也就是我们对于每个 $i$，维护 $ih + s_{h + 1}$ 的最大值即可。这个东西可以用好多种东西维护，比如李超树或者普通的线段树也可以，但是最好写的是斜率优化，也很显然，直接看看代码吧。

还有一点需要注意，题目中未说明 $k_i \le n$，所以我们还要特判一下。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
#define int long long
const int N = 1e6 + 5;
int n, q, k[N], fa[N];
int h[N], e[N * 2], ne[N * 2], idx;
void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dep[N];
int s[N];
int sup;
void dfs(int x, int fa) {
	dep[x] = dep[fa] + 1;
	sup = max(dep[x], sup);
	s[dep[x]]++;
	for (int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if (j == fa) continue;
		dfs(j, x);
	} 
}
long long val[N];
int st[N], tail;
long long f[N];
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	memset(h, -1, sizeof(h));
	cin >> n >> q;
	For(i, 1, q) cin >> k[i];
	For(i, 2, n) cin >> fa[i];
	For(i, 2, n) add(fa[i], i), add(i, fa[i]);
	dep[0] = 0; 
	dfs(1, 0);
	Dec(i, n, 0) s[i] += s[i + 1];
	For(i, 0, n) val[i] = s[i + 1];
//	For(i, 0, n) cout << val[i] << ' ';
//	cout << '\n';
	st[++tail] = 0;
	For(i, 1, sup) {
		while (tail > 1 && (-val[st[tail]] + val[st[tail - 1]]) * (i - st[tail - 1]) >= (-val[i] + val[st[tail - 1]]) * (st[tail] - st[tail - 1])) tail--;
		st[++tail] = i;
	}
	int w = 1;
	For(i, 1, n) {
		while (w < tail && -val[st[w + 1]] + val[st[w]] < 1ll * i * (st[w + 1] - st[w])) w++;
		f[i] = 1ll * i * st[w] + val[st[w]]; 
		//cout << st[w] << ' ';
	}
	//cout << '\n';
	For(i, 1, q) {
		if (k[i] > n) cout << sup << ' ';
		else cout << (f[k[i]] + k[i] - 1) / k[i] << ' ';
	}
	return 0;
}
```

---

