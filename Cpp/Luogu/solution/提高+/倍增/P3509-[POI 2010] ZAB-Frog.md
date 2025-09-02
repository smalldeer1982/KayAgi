# [POI 2010] ZAB-Frog

## 题目描述

在一个特别长且笔直的 Byteotian 小溪的河床上，有 $n$ 块石头露出水面。它们距离小溪源头的距离分别为 $p_1 < p_2 < \cdots < p_n$。一只小青蛙正坐在其中一块石头上，准备开始它的跳跃训练。每次青蛙跳跃到距离它所在石头第 $k$ 近的石头上。具体来说，如果青蛙坐在位置 $p_i$ 的石头上，那么它将跳到这样的 $p_j$ 上，使得：

$$
|\{ p_a : |p _ a - p _ i| < |p_j - p_i| \}| \le k \text{ and } |\{ p_a : |p _ a - p _ i| \le |p_j - p_i| \}| > k
$$

如果 $p_j$ 不是唯一的，那么青蛙在其中选择距离源头最近的石头。对于每一块石头分别计算，若青蛙从这块石头开始跳跃，经过 $m$ 次跳跃后最终会停留在哪一块石头上？

## 说明/提示

### 样例 #1 解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/yyilx2mp.png)

图中展示了青蛙从每块石头跳跃（单次跳跃）到的位置。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 2 4
1 2 4 7 10```

### 输出

```
1 1 3 1 1```

# 题解

## 作者：TonyYin (赞：44)

## 题意

数轴上有 $n$ 个点，坐标分别为 $p_1, p_2, \cdots, p_n$ 在这些点上按照某些规则跳。

规则是：每次向距当前点第 $k$ 小的点跳，如果有相同距离则向下标较小的跳；

求从每个点出发跳了 $m$ 次后在哪里.

$1\leq k < n\leq 10^6, 1\leq m\leq 10^{18}, 1\leq p_i\leq 10^{18}$.

## $\rm{Part}$ $\rm{1}$

首先，注意到 $k$ 是固定的，所以可以先预处理，对于每个点 $i$，跳一次之后的位置$\operatorname{next}_i$.

这部分使用单调队列处理。

我们知道，对于每个点，距离其前 $k$ 小的点分布在其两侧，可以用一段完整区间覆盖。

所以我们想到，当单调队列枚举到 $i$ 时，单调队列中维护的区间，就是覆盖距离 $i$ 前 $k$ 小的点的区间。这样找到区间内距离最大的点就是我们要求的 $\operatorname{next}_i$，下面考虑考虑如何维护。

对于区间 $[l, r]$ 中的一个点 $i$，距离他最远的点一定是 $l$ 和 $r$ 这两个点中的一个。如果 $r+1$ 到 $i$ 的距离小于了 $l$ 到 $i$ 的距离，说明区间应当向右滑动，如下图，$n=7, k=3$ 的例子：

![](https://pic.tonyyin.top/2021/04/07/7f8eb682152e0.png)

绿色区间是距离点 $C$ 前 $k$ 小的点，考虑距离点 $D$ 前 $k$ 小的点。

$\rm{Dis(D, F)<Dis(D, A)}$，所以区间要右移一个单位，变成：

![](https://pic.tonyyin.top/2021/04/07/c2fab34dc4c38.png)

又因为 $\rm{Dis(D, E)<Dis(D, B)}$，所以区间要再右移一个单位，变成：

![](https://pic.tonyyin.top/2021/04/07/e66fbeeb3b4ce.png)

至此，我们能够求出每个点，距离其第 $k$ 小的点的下标。

```cpp
head = 1, tail = k + 1;
for(int i = 1; i <= n; i++) {
	while(tail + 1 <= n && x[tail + 1] - x[i] < x[i] - x[head]) head++, tail++;
	if(x[tail] - x[i] > x[i] - x[head]) nxt[i] = tail;
	else nxt[i] = head;
}
```

## $\rm{Part}$ $\rm{2}$

题目要求跳 $m$ 次之后的答案，我们使用类似快速幂的方法，倍增处理即可。

```cpp
for(int i = 1; i <= n; i++) pos[i] = i;
while(m) {
	if(m & 1) {
		for(int i = 1; i <= n; i++) pos[i] = next[pos[i]];
	}
	m >>= 1;
	for(int i = 1; i <= n; i++) next2[i] = next[i];
	for(int i = 1; i <= n; i++) next[i] = next2[next2[i]];
}
```

## 代码

最终代码在上面两部分的基础上加上 $\rm{I/O}$ 即可。



---

## 作者：卷王 (赞：34)

### 大意 
	
一共 $n$ 个点，将这 $n$ 个点进行 $m$ 次操作，每次同时将 $n$ 个点移动到离这个点距离第 $k$ 小的点，问最后这 $n$ 个点的坐标。

### 思路

根据题目，我们可以想出，用单调队列 + 快速幂就可以解决此问题。我们用 $nxt_i$ 表示距离第 $i$ 个点的第 $k$ 小的点，用 $ans_i$ 去存答案，每次移动用快速幂更新即可。

单调队列显然用于初始化 $nxt$, 也就需要让 $head$ 和 $tail$ 相差 $k$。

其他就没什么了，具体请参见代码。

```cpp
#include <bits/stdc++.h
using namespace std;
typedef long long ll; //！！！ 
ll n, m;
ll k;
ll a[1000001];
int nxt[1000001]; //nxt[i]表示距离第i个点的第k小的点的编号 
int tmp[1000001];
int ans[1000001]; //存答案 
int main()
{
	speed: std::ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); //加速 
	cin >> n >> k >> m;
	for(int i = 1; i <= n; i++) //读入坐标 
		cin >> a[i];
	nxt[1] = k + 1; //注意！是k + 1而不是1！！！ 
	int head = 1, tail = k + 1; //队首，队尾，距离保持k 
	for(int i = 2; i <= n; i++) //进行初始（单调队列） 
	{
		while(tail + 1 <= n && a[i] - a[head] > a[tail + 1] - a[i]) head++, tail++;
		//下面开始记录 
		if(a[i] - a[head] >= a[tail] - a[i]) nxt[i] = head;
		else nxt[i] = tail;
	}
	for(int i = 1; i <= n; i++)
		ans[i] = i; //移动0次就是原先的样子 
	while(m) //快速幂 
	{
		if(m & 1) //相当于m % 2 == 1 
			for(int i = 1; i <= n; i++) //肯定要更新啊！ 
				ans[i] = nxt[ans[i]];
		memcpy(tmp, nxt, sizeof(tmp)); //暂时存一下，方便后面使用 
		for(int i = 1; i <= n; i++)
			nxt[i] = tmp[tmp[i]]; //更新下一个移动到的点 
		m >>= 1; //相当于m /= 2 
	}
	for(int i = 1; i <= n; i++)
		cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：maoyujie (赞：18)

首先可以预处理出每个点跳到的下一个点的位置；
因为这是一个比较明显的尺取法模型。相邻两点距离前k小的点集很接近，所以很容易用双指针维护每个点距离前k小的连续区间O(n)求出所有点的距离第k小点。具体实现看代码吧，这个应该不难。

然后可以考虑将m二进制分解着来跳，实现的话用倍增法得到从一个点跳(1<<i)次到的点。
因为倍增过程顺序枚举i所以只有相邻两个倍增数组有用，所以可以开滚动数组解决空间开不下的问题。
总时间复杂度O(n log n),空间复杂度O(n)。
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+ch-48;
    return x*f;
}
const int N=1100000;ll a[N],m;
int n,k,x,y,now,ans[N],b[N][2];
int main(){
    scanf("%lld%d%lld",&n,&k,&m);
    int l=1,r=k+1;b[1][0]=k+1;
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=2;i<=n;i++){
        while(r<n&&a[r+1]-a[i]<a[i]-a[l])l++,r++;
        a[r]-a[i]>a[i]-a[l]?b[i][0]=r:b[i][0]=l;
    }
    for(int i=1;i<=n;i++)ans[i]=i;
    for(int i=0;(1ll<<i)<=m;i++){
        now=i&1;
        if(m&(1ll<<i))for(int j=1;j<=n;j++)ans[j]=b[ans[j]][now];
        for(int j=1;j<=n;j++)b[ans[j]][now^1]=b[b[ans[j]][now]][now];
    }
    for(int i=1;i<=n;i++)printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：子翮 (赞：17)

看到有位大佬是用滚动数组实现的，~~总感觉不够优雅~~，所以~~应老师的要求~~发了这篇题解。

### 实现：
1.预处理出每个点跳到离自己第k的点的编号，可以用一个类似滑动窗口的单调队列实现，具体见代码。不会的可以看看这道题  [P1886 滑动窗口](https://www.luogu.org/problem/P1886)。

2.用倍增处理出每个点跳m次达到的点，即为答案。

### 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define R register
#define MAXN 1000010 
typedef long long ll;
using namespace std;
ll n,k,m;
ll p[MAXN];
ll f[MAXN],ff[MAXN],ans[MAXN];
int main()
{
	scanf("%lld%lld%lld",&n,&k,&m);
	for(R ll i=1;i<=n;i++)
	{
		scanf("%lld",&p[i]);
	}
	f[1]=k+1;
	ll l=1,r=k+1;
	for(R ll i=2;i<=n;i++)//滑窗维护左右端点
	{
		while(r+1<=n&&p[i]-p[l]>p[r+1]-p[i]) l++,r++;
		if(p[i]-p[l]>=p[r]-p[i]) f[i]=l;
		else f[i]=r;
	}
	for(R ll i=1;i<=n;i++) ans[i]=i;//初始跳0次
	while(m)//倍增
	{
		if(m&1) for(R ll i=1;i<=n;i++) ans[i]=f[ans[i]];//更新答案
		m>>=1;
		memcpy(ff,f,sizeof(ff));
		for(R ll i=1;i<=n;i++) f[i]=ff[ff[i]];//更新下一个跳到的点
	}
	for(R ll i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;//撒由那拉
}


```



---

## 作者：Martian148 (赞：8)

# 好像没有O(n)的解法，我来补一个吧
## 题目简述
有升序不相等的N个数(N≤1e6)每个数跳一步可以跳到和a[i]的差值第k小的数，如果有两个数和a[i]的差值一样，则跳到较小的那个数上。输出N个数，分别是在第i个位置跳M(M≤1e9)下最后所在的位置。

## Solve
我们肯定要构造出一个nxt[i]表示当前这个数跳到哪里，因为N非常大，我们要O(n)求出，我们就想到滑动区间那道题，如图，距离a[i]前k小的肯定在i周围一段连续的k个数，加上i就是K+1个数，我们可以维护hed和til，til-hed==K，对于每一个i我们只要把hed和til往前推就好了没有必要从1开始推，也就是说，当a[til+1]-a[i]＜a[i]-a[hed]的时候，把区间往前移动，就可以O(n)构造出nxt数组了。

![](https://cdn.luogu.com.cn/upload/image_hosting/mlb021qv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/cekpva7j.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/ubch5gdp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/hjb8ycaa.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

构造出nxt数组之后我们可以构造出一个如下图的关系图，通过观察关系图我们发现有很多环存在，可能不止一个环，一个环中也不止两个数(别太天真了^_^，自己多造几组数据试试)。每个节点最终肯定会掉到环中(如果M足够大的话)，接下来我们把一个数看成一个节点。右图中红色节点就是环中的节点，蓝色节点就是不在环上的节点。把图抽象出来就是最下面那个图。一个环上肯定不会有边出来，肯定是很多边汇到环里面。因为到了环里面就会在环里面转，所以可以拿来mod。在环里面转多少下，就是M-(某个节点到环的距离)。可以用拓扑找出在环上的节点，拿出一个环上的节点，把一个环刷完，你就能得出每个环的周期和每个数在周期中的位置，我们把它存在Q数组和vis数组中，我们反建图，用DFS遍历环内每个节点的儿子，记下遍历时的深度Dep，他的儿子肯定是从他这里进入环的，我们还要记下第i层遍历到的点，计为D[i]因为当M＜当前的深度时，也就是说这个节点跳M下跳不到环内，他的答案就是在当前层数往上M层的那个节点。当M大于遍历到的节点i的深度时，也就是说可以掉进环内时，他在跳进环的过程中跳了Dep下，在环内跳了M-Dep下，在环里面跳M-Dep下和(M-Dep) mod(环的大小)是一样的，我们已经记下了周期和每个环内节点在周期内的位置，最后答案就是vis[D[0]]+(M-Dep)%(环的大小)，因为(M-Dep)%(环的大小)最大为(环的大小)-1，加上vis[D[0]]后可能爆出环的大小，所以我们要构造出环的长度两倍的Q数组。至此，完。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N,M,K,a[1000005],vis[1000005],D[1000005],tot,pre[1000005],hed,til,Q[2000005],ans[1000005],son[1000005],lnk[1000005],hep[1000005],cnt,nxt[1000005],du[1000005];
inline LL read(){
	LL ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline void add_e(LL x,LL y){son[++cnt]=y;nxt[cnt]=lnk[x];lnk[x]=cnt;}
void topo(){
	int hed=0,til=0;
	for(int i=1;i<=N;i++)if(!du[i])hep[++til]=i;
	while(hed!=til){
		++hed;--du[pre[hep[hed]]];
		if(!du[pre[hep[hed]]])hep[++til]=pre[hep[hed]];
	}
	return;
}
void DFS(LL x,LL dep){
	if(!vis[x])vis[x]=-1;
	D[dep]=x;
	if(M<dep)ans[x]=D[dep-M];
	else ans[x]=Q[vis[D[0]]+(M-dep)%(tot)];
	for(int j=lnk[x];j;j=nxt[j]){
		if(vis[son[j]])continue;
		DFS(son[j],dep+1);
	}
	D[dep]=0;
	return;
}
int main(){
	freopen("zab.in","r",stdin);
	freopen("zab.out","w",stdout);
	N=read();K=read();M=read();
	for(int i=1;i<=N;i++)a[i]=read();
	hed=1,til=K+1;
	pre[1]=til;
	for(int i=2;i<=N;i++){
		while(til+1<=N&&a[til+1]-a[i]<a[i]-a[hed])
		til++,hed++;
		if(a[til]-a[i]>a[i]-a[hed])pre[i]=til;
		else pre[i]=hed;
	}
	for(int i=1;i<=N;i++)du[pre[i]]++,add_e(pre[i],i);
	topo();
	for(int i=1;i<=N;i++){
		tot=0;
		if((vis[i])||(!du[i]))continue;
		for(int now_x=i;;){
			if(vis[now_x])break;
			Q[++tot]=now_x;
			vis[now_x]=tot;
			now_x=pre[now_x];
			
		}
		for(int j=tot+1;j<=2*tot;j++)Q[j]=pre[Q[j-1]];
		for(int j=1;j<=tot;j++)DFS(Q[j],0);
	}
	for(int i=1;i<=N;i++)printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：zplqwq (赞：7)

很厉害的题。倍增和单调队列。

这是 zpl 新手向算法第二弹，第一弹可以看[小挖的核燃料填充](https://www.luogu.com.cn/blog/kawaiizpl/solution-p8549) 我会尽量讲的比较细致。

同第一弹，尽量配合代码食用。
___________

这道题的题目描述写的不是特别清楚，这里我写了一个简要题意。


有 $n$ 个点，升序给出每个点到起点的距离。有编号为 $n$ 只青蛙编号分别为$1 \to n$ 个点上，第 $i$ 只青蛙在第 $i$ 个点上。每次它们会跳到距离自己第 $k$ 远的点上。

如果有相同距离的点，就跳到下标更小的点上。求跳 $m$次之后，第 $i$ 只的青蛙在哪个点上。

________

因为 $m\le 10^{18}$ 所以暴力跳肯定是寄的。

首先看到这个跳点的操作可以想到倍增，想到一开始做的倍增典题的描述的跳跃多数都是直接跳到第 $i+k$ 个点上。所以如果我们可以提前预处理出每一个点会跳到哪里，这道题是板子了。

直接预处理第 $k$ 远是不容易的，但是 $x$ 的第 $k$ 远的点一定是在 $x$ 的两侧，且是一个长度为 $k$ 的区间。想到滑动窗口所维护的单调队列是前 $k$ 小，所以考虑使用单调队列解决这个问题。

这里有一个小性质，因为青蛙的一开始的位置和每个点到起点的距离都是升序的，所以 $i$ 的第 $k$ 远一定在 $i-1$ 的第 $k$ 远的右边，也就是说队尾直接每次加一就可以了。所以直接维护一个单调队列，设当前点为 $i$，队首为 $x$ 队尾为 $y$，则若 $a_{y+1}-a_i<a_i-a_{x}$ 则 $a_x$ 肯定不是第 $k$ 小，弹出。而 $y$ 要向后扩展到 $y+1$。




可能理解起来比较复杂，建议模拟一边样例或者看代码。

然后是倍增的部分，这个还是比较板子的，考虑像快速幂一样二进制分解 $m$。但有一个小问题，我们可不可以像求 LCA 那样来做这道题呢？其实是一样的，我们求 LCA 的时候之所以维护一个 $f_{i,j}$ 表示从 $i$ 开始跳 $2^j$ 步可以跳到哪里是因为我们不知道最多能跳多少步，而在这题中我们已经明确了跳 $m$ 步所以跟 LCA 看起来可能不一样。


代码可能跟别的题解长得几乎一样，但因为方法一样所以代码都大同小异。我删除了调试部分。

```cpp
const int N=1e6+10;
int k,n,m;
int tmp[N];
int a[N],nxt[N],pos[N];	
//a题目给的距离原点的距离，nxt是第i个点可以跳到哪里（也就是第k远），pos是存最终位置的
signed main()
{
	n=read();
	k=read();
	m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	int head=1,tail=k+1;//对于第一个点，他的第k远肯定是第k+1个点
	for(int i=1;i<=n;i++)
	{
		while(tail+1<=n and a[tail+1]-a[i]<a[i]-a[head]) head++,tail++;//如果移动之后当前窗口依旧合法且下一个元素距离当前点的距离小于队首距离当前点的距离则队首不合法，并且下一个元素合法
		if(a[tail]-a[i]>a[i]-a[head]) nxt[i]=tail;//答案肯定是队首或者队尾，因为两边才是第k小，中间维护的是前k小。所以判断一下距离大小即可
		else nxt[i]=head;
	}
	for(int i=1;i<=n;i++) pos[i]=i;
	while(m)//倍增
	{
		if(m&1)
		{
			for(int i=1;i<=n;i++) pos[i]=nxt[pos[i]];//跳到他能跳到的点
		}
		m>>=1;
		for(int i=1;i<=n;i++) tmp[i]=nxt[i];
		for(int i=1;i<=n;i++) nxt[i]=tmp[tmp[i]];//改变nxt的值（因为原数组位置有改变）。
	}
	for(int i=1;i<=n;i++) cout<<pos[i]<<" ";
	return 0;
}
```


---

## 作者：Night_Aurora (赞：6)

原数据是$K<N<=100000$,很明显我们可以直接预处理出跳转表后跑倍增

倍增就是差不多DJMP[k][p] 表示从p这个点往后跑$ 2^k$ 步后所在的位置

然后就像RMQ一样处理出倍增然后像快速幂一样跑就行了

时间空间复杂度都是$O(NlogM)$,大概是6E+6,内存和时限都不紧张

对于跳转表的处理我们可以从左往右处理，维护两个指针(实际上一个也行)

一个是lp，一个是rp(=lp+K)，且递推到p这个点时$lp\leq p \leq rp$

刚开始时lp=1，rp=K，每次递推到一个元素时，若H[rp+1]-H[p]<H[p]-H[lp],就把lp和rp都+1

则这个点跳转的点就是lp和rp中的一个(当然lp=p或rp=p时不可以)

找一个绝对值最小且下标最小的就行

然后这样这个题就结束了

## 番外：

本人当时看到这道题数据是 $ N \leq 1000000 $ 时是绝望的

虽然数据是假的但是那时候谁知道

那就讲一讲我想到的处理1E6数据的做法吧

1E6的话用上面那个倍增方法，首先$O(NlogM)$的空间开不下

然后我们发现这个图能一直走下去，所以一定会存在环

考虑到跑入环是一个有去无回的过程

那样我们处理出跳转表后，倍增置倍增19(logN)的就行

因为每个点出度都是1，所以强连通分量一定是一个简单环

用Tarjan处理出所有的点数>1的环以及环的大小后

在处理出每个不在环内的点到环的距离

那样我们在一个点倍增走M步时，若M<点到环的距离，那就直接倍增走M步就行，反正M<N

若M>=点到环的距离时，先倍增刚好走入环，在倍增走(M-点到环的距离)Mod(环的大小)就行

这样处理中就能略去绕圈，从而直接走到终点

因为Mod后面环的大小<=N,所以也最多只要走N步

这就是前面倍增只倍增LogN个的原因

卡常的话可以在倍增那里用Lowbit优化，但是对于原题可有可无

虽然内存有点紧张...

这里就贴原本为1E6的数据准备的代码吧


```cpp
#include <cstdio>
#include <stack>
typedef long long _L;
int N,K;
_L M;
_L Dist[1100000];
_L Abs(_L c)
{return c<0?-c:c;}
#define min(a,b) (a>b?b:a)
void Input()
{
    scanf("%d %d %lld",&N,&K,&M);
    int wi;
    for(wi=1;wi<=N;++wi)
        scanf("%lld",Dist+wi);
}
int DJMP[20][1000100];
int Down[1100000];
void SetJMP()
{
    int wi,fp,lp;
    fp=K+1,lp=1;
    for(wi=1;wi<=N;++wi)
    {
        while(fp<N&&Abs(Dist[fp+1]-Dist[wi])<Abs(Dist[lp]-Dist[wi]))
        {
            ++fp;
            ++lp;
        }
        if(Abs(Dist[lp]-Dist[wi])>=Abs(Dist[fp]-Dist[wi]))
            DJMP[0][wi]=lp;
        else
            DJMP[0][wi]=fp;
    }
    int k;
    for(k=1;k<=19;++k)
        for(wi=1;wi<=N;++wi)
            DJMP[k][wi]=DJMP[k-1][DJMP[k-1][wi]];
    for(k=0;k<20;++k)
        Down[1<<k]=k;
}
int Buf[2100000];
int Bt,Ron;
int*Rot[1100000];
int Rtn[1100000],Bel[1100000];
int Dfn[1100000],Low[1100000],DFN;
std::stack<int> St;
bool Vis[1100000];
int RDist[1001000];
void Trojan(int p)
{
    Dfn[p]=Low[p]=++DFN;
    Vis[p]=1;
    St.push(p);
    if(!Dfn[DJMP[0][p]])
    {
        Trojan(DJMP[0][p]);
        Low[p]=min(Low[p],Low[DJMP[0][p]]);
    }
    else if(Vis[DJMP[0][p]])
        Low[p]=min(Low[p],Low[DJMP[0][p]]);
    if(Dfn[p]==Low[p])
    {
        if(St.top()==p)
        {
            St.pop();
            Vis[p]=0;
            return;
        }
        ++Ron;
        Rot[Ron]=Buf+Bt;
        int cp=0;
        while(cp^p)
        {
            cp=St.top();St.pop();
            Rot[Ron][++Rtn[Ron]]=cp;
            Bel[cp]=Ron;
            Vis[cp]=0;
        }
        Bt+=Rtn[Ron]+1;
    }
}
void DFS_FAR(int p)
{
    Vis[p]=1;
    if(Bel[p])
    {
        RDist[p]=0;
        return;
    }
    if(!Vis[DJMP[0][p]])
        DFS_FAR(DJMP[0][p]);
    RDist[p]=RDist[DJMP[0][p]]+1;
}
int Get(int p,int Len)
{
    int l;
    while(Len)
    {
        l=Len&-Len;
        p=DJMP[Down[l]][p];
        Len-=l;
    }
    return p;
}
int Run(int p)
{
    _L bs=M;
    if(bs<=RDist[p])
        return Get(p,bs);
    bs-=RDist[p];
    p=Get(p,RDist[p]);
    bs%=Rtn[Bel[p]];
    return Get(p,bs);
}
void AC()
{
    int wi;
    SetJMP();
    for(wi=1;wi<=N;++wi)
        if(!Dfn[wi])
            Trojan(wi);
    for(wi=1;wi<=N;++wi)
        if(!Vis[wi])
            DFS_FAR(wi);
    for(wi=1;wi<=N;++wi)
         printf("%d ",Run(wi));
}
int main()
{
//    freopen("1.txt","r",stdin);
    Input();
    AC();
    return 0;
}
```

---

## 作者：AKPC (赞：3)

### 题意
在数轴上原点的右边有 $n$ 块石头（从小到大给出），每块石头上有一个动点。  

它们需要执行如下操作 $m$ 次：

- 移动到距离该点第 $k$ 近的石头，如果有多个，选择那个更小的。

你需要求出最后每个点在第几块石头。
### 思路
先进行预处理，预处理从每块石头上的点操作后的位置。

显然这是个尺取法模型。相邻的两点距离前 $k$ 小的点集很接近，所以可以用双指针维护每个点距离前 $k$ 小的连续区间，并求出所有点距离第 $k$ 小点。

由于 $k$ 固定，可以使用一个类似滑动窗口的单调队列实现，因为离远点距离单调不减所以可以维护一个长为 $k+1$ 的单调队列。

然后用倍增处理每个点进行 $m$ 次操作之后达到的点。

考虑将 $m$ 二进制分解来跳，用倍增得到从一个点跳 $1<<i$ 次到的点实现。因为倍增过程顺序枚举 $i$ 所以只有相邻两个倍增数组有用，所以可以开滚动数组解决空间问题。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,k,m,l,r,a[100001],f[100001],ff[100001],ans[100001];
signed main(){
	cin>>n>>k>>m;
	for (int i=1;i<=n;i++) cin>>a[i];
	f[1]=k+1,l=1,r=k+1;
	for (int i=2;i<=n;i++){
		while (r+1<=n&&a[i]-a[l]>a[r+1]-a[i]) l++,r++;
		a[i]-a[l]>=a[r]-a[i]?f[i]=l:f[i]=r;
	}
	for (int i=1;i<=n;i++) ans[i]=i;
	while (m){
		if (m%2==1) for (int i=1;i<=n;i++) ans[i]=f[ans[i]];
		m/=2;
		for (int i=1;i<=n;i++) ff[i]=f[i];
		for (int i=1;i<=n;i++) f[i]=ff[ff[i]];
	}
	for (int i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
}
```


---

## 作者：安好 (赞：3)

/\*
如何求处离当前点第k近的点呢？

答案是单调队列。因为离远点距离单调不减 所以可以维护一个长度为k+1的单调队列

然后就是跳的问题。模型貌似是置换的快速幂，不会

只会用倍增。空间开不下？滚动数组。

\*/




    
    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 1000007
#define ll long long 
using namespace std;
ll n,m,k,ans,cnt,a[N],p[N];
int f[N][2],g[N];
inline ll read()
{
    ll x=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int main()
{
    n=read();k=read();m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    ll l=1,r=k+1,lim=log2(m)+1;
    for(int i=1;i<=n;i++)
    {
        while(r<n && a[r+1]-a[i]<a[i]-a[l]) l++,r++;
        f[i][0]=(a[r]-a[i]>a[i]-a[l]?r:l);
    }
    if(m&1) for(int i=1;i<=n;i++) g[i]=f[i][0];
    else for(int i=1;i<=n;i++) g[i]=i;
    r=1;p[0]=1;
    for(int i=1;i<=lim;i++) p[i]=p[i-1]<<1;
    for(int j=1;j<=lim;j++)
    {
        for(int i=1;i<=n;i++) f[i][r]=f[f[i][r^1]][r^1];
        if(m&p[j]) for(int i=1;i<=n;i++) g[i]=f[g[i]][r];
        r^=1;
    }
    for(int i=1;i<=n;i++) printf("%d ",g[i]);printf("\n");
    return 0;
}
```

---

## 作者：cenxinyang12 (赞：2)

# 洛谷 P3509
## 题意
对 $1$ 到 $n$ 这 $n$ 个点进行 $m$ 次操作，每次将 $n$ 个点移动到距离它的第 $k$ 远的点上，输出最后这 $n$ 个点的坐标。
## 思路
暴力求出每个点的下一个点时间复杂度过高，可以利用单调队列预处理。可这样只能求出每个点的下一步，再看 $m$ 的范围：$1 \le m \le 10^{18}$ 。模拟是不可能了，于是便想到了倍增处理。
## 总结
1. 用单调队列预处理，求出每个点的距离它的第 $k$ 远的点。
2. 倍增处理，求出移动 $m$ 次后的位置，既是答案。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,i;
int t,w;//t是头，w是尾
long long m,a[1000010];//千万别忘用long long
int f[1000010];//存放答案
int nextw[1000010][60];
//用了一个二维数组存放第i个点的第k小的点的编号，空间很大，但能AC，使用滚动处理更好
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k>>m;
	for(i=1;i<=n;i++)
		cin>>a[i];
	nextw[1][0]=k+1;//点1的下一个点是k+1
	t=1;w=k+1;//头尾保持k的距离
	for(i=2;i<=n;i++){//从二开始做单调队列
		while(w+1<=n&&a[w+1]-a[i]<a[i]-a[t])
			t++,w++;//保持单调和k的距离
		nextw[i][0]=(a[w]-a[i]<=a[i]-a[t]?t:w);
		//三目运算符保存结果
	}
	for(i=1;i<=n;i++)
		f[i]=i;//移动0次的结果
	t=0;
	for(;m>0;m>>=1,t++){//倍增，每次将 m/2，即 m>>1
		if(m&1)//更新答案（m & 1 即 m % 2==1）
			for(i=1;i<=n;i++)
				f[i]=nextw[f[i]][t];
		for(i=1;i<=n;i++)
			nextw[i][t+1]=nextw[nextw[i][t]][t];//更新下一个点
	}
	for(i=1;i<=n;i++)
		cout<<f[i]<<' ';
	return 0;
}
```


---

## 作者：wizardMarshall (赞：2)

[题面](https://www.luogu.com.cn/problem/P3509)

## 前言

~~（无关紧要）~~

倍增数组的想法一开始就有了，没想到预处理才是最令人烦恼的……还因为 $m$ 的数据范围调了半小时。

## $Start$

看到这道题，~~很容易~~就能想到倍增数组的做法，因为 $1 \le m \le 10^{18}$，所以不能用常规的方式去一步步模拟，需要二进制来帮忙。

然后，中间的转移代码都是如出一辙：

```
for (int j = 1; j <= 61; j++) {
	for (int i = 1; i <= n; i++) {
		dp[i][j] = dp[dp[i][j - 1]][j - 1];
	}
}
```

$dp_{i,j}$ 意为从 $i$ 点出发，跳 $2^j$ 步后所在的位置。于是就可以用 $dp_{dp_{i, j-1}, j-1}$ 来更新 $dp_{i,j}$。这点与普通倍增无异，不再详细解释。

难点在于预处理，就是说，如何计算距离 $i$ 点第 $k$ 远的点。这里，大佬们用了很多方法，什么尺取（双指针），单调队列。本蒟蒻不才，脑子一抽写了个二分套二分，后期维护调试还很麻烦……避坑避坑。

## $Process$

枚举当前点 $i$ 后，第一层二分是二分距离，判断条件为当前距离为 $mid1$ 时，与 $i$ 点距离小于等于 $mid1$ 的点有多少个，并且返回**最边缘那一个点的位置**。（不包括 $i$ 点本身）如果点的个数大于等于 $k$，就缩小距离，否则扩大距离，直到找到一个点数正好为 $k$ 的情况。（由于距离的相等，也可能有个数为 $k+1$ 的情况）

而这个判断条件又需要一次二分，这次二分的是位置。找到第一个距离小于等于 $mid1$ 的点的位置，以及最后一个距离小于等于 $mid1$ 点的位置。然后经过各种特判，返回这些点的个数和最边缘那个点的位置。

最后，我们可以得到边缘点的位置，这就是 $dp_{i,0}$ 的值。之后，我们只需要进行倍增常规操作，最后根据倍增数组输出答案就行了。

主要为预处理部分，时间复杂度 $O(n\log_2n)$。

## $Code$

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
	char s = getchar();
	while (s < '0' || s > '9')s = getchar();
	int sum = 0;
	while (s >= '0' && s <= '9') {
		sum = sum * 10 + s - '0';
		s = getchar();
	}return sum;
}
int n, k, m;
int a[1000005];
int dp[1000005][65];//i点跳了2^j次后在哪个点
inline pair <int, int> check2(int s, int x) {//返回离s点的距离小于等于x的点有几个，以及边缘点的位置
	int l = 1, r = s - 1;
	int temp1 = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (abs(a[mid] - a[s]) <= x) {
			temp1 = mid;
			r = mid - 1;
		}else {
			l = mid + 1;
		}
	}l = s + 1, r = n;
	int temp2 = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (abs(a[mid] - a[s]) <= x) {
			temp2 = mid;
			l = mid + 1;
		}else {
			r = mid - 1;
		}
	}
	if (temp1 != -1 && temp2 != -1) {
		if (abs(a[s] - a[temp1]) >= abs(a[temp2] - a[s]))return {temp2 - temp1, temp1};
		return {temp2 - temp1, temp2};
	}if (temp1 != -1) {
		return {s - temp1, temp1};
	}if (temp2 != -1) {
		return {temp2 - s, temp2};
	}return {0, -1};
}
inline int check1(int s) {//找到距离s点第k远的点，不包括s自己
	int l = 1, r = a[n] + 10;//二分距离
	int temp = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		pair <int, int> cnt = check2(s, mid);
		if (cnt.first >= k) {
			r = mid - 1;
			temp = cnt.second;
		}else {
			l = mid + 1;
		}
	}return temp;
}
inline int solve(int m, int s) {
	int temp = m;
	for (int i = 61; i >= 0; i--) {//对m逐位判断，类似于倍增做LCA时的操作
		if (temp >= (1ll << i)) {
			temp -= (1ll << i);
			s = dp[s][i];
		}
	}return s;
}
signed main() {
	cin >> n >> k >> m;
	for (int i = 1; i <= n; i++) {
		a[i] = read();
	}
	//预处理dp[i][0]
	for (int i = 1; i <= n; i++) {
		dp[i][0] = check1(i);
	}for (int j = 1; j <= 61; j++) {
		for (int i = 1; i <= n; i++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}for (int i = 1; i <= n; i++) {
		printf("%lld ", solve(m, i));
	}return 0;
}


```

注：笔者的思路是比较繁琐且效率低下的，适合二分练手，但还不能达到最优解的程度。

## $End.$

---

## 作者：e4fsrc2e4fsrc2 (赞：1)

## [[POI2010] ZAB-Frog](https://www.luogu.com.cn/problem/P3509)
## 思路分析
这题看到 $m$ 很大，如果一次一次跳肯定会超时，所以应该要想到用倍增地方法来跳。

首先先预处理出 $f$ 数组，用 $f_{i,x}$ 表示从 $i$ 跳 $2^x$ 步到达的位置，显然有 $f_{i,x}=f_{f{i,x-1},x-1}$。

此时，如果用朴素地求对于每个点距离其第 $k$ 远的点的话，时间复杂度为 $O(nk)$ 会超时，但可以拿到 $26$ 分。

所以考虑用队列优化，如 [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)。

假设：已经对于 $i$ 号点有了一个区间 $[L,R]$（包含 $i$ 号点）这里面有 $k+1$ 个点。

我们已经求出了对于 $i$ 号点的第 $k$ 远的点，也就是这个区间 $[L,R]$ 的某个点，更进一步，是 $L$ 点或 $R$ 点。

下面找对于 $i+1$ 号点的第 $k$ 远的点，很显然，$i+1$ 号点在 $[L,R]$ 这个区间中，若
$$dis_{R+1}-dis_{i+1}<dis_{i+1}-dis_L$$
即：$R+1$ 号点到 $i+1$ 号点的距离小于 $i+1$ 号点到 $L$ 的距离。

否则，说明 $R+1$ 号点是对于 $i+1$ 的第 $k+1$ 远的点，那么第 $k$ 远的点就是 $L$ 点或者 $R$ 点。

注意到题目的数据很大，开不了这么大的 $f$ 数组，所以可以用滚动数组来优化空间。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=1e6+1;
int n,k,f[N][2],ans[N];ll m,a[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k>>m;
	for(R i=1; i<=n; i++)cin>>a[i];
	f[1][0]=k+1;R l=1;
	for(R i=2; i<=n; i++){
		while(l+k+1<=n&&a[i]-a[l]>a[l+k+1]-a[i])l++;
		if(a[i]-a[l]>=a[l+k]-a[i])f[i][0]=l;
		else f[i][0]=l+k;
	}
	for(R i=1; i<=n; i++)ans[i]=i;
	while(m){
		if(m&1){
			for(R i=1; i<=n; i++)ans[i]=f[ans[i]][0];
		}
		m>>=1;
		for(R i=1; i<=n; i++)
			f[i][1]=f[i][0];
		for(R i=1; i<=n; i++)
			f[i][0]=f[f[i][1]][1];
	}
	for(R i=1; i<=n; i++)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：黑影洞人 (赞：1)

这题我用了一个类似矩阵快速幂套并查集的方法来实现。（实际上本质是快速幂）

首先我们用尺取法预处理处第 $i$ 个位置的第 $k$ 近位置。

```cpp
void set(int k){
	int l=1,r=k+1;
	m[1]=k+1;
	for(int i=2;i<=n;i++){
		while(r+1<=n&&a[i]-a[l]>a[r+1]-a[i])l++,r++;
		if(a[i]-a[l]<a[r]-a[i])m[i]=r;
		else m[i]=l;
	}
}
```
第一个数的目标位置只能是 $k+1$ 。

随后构造一个长度为 $k+1$ 的尺子，其中必定存在一对点对为第 $k$ 近。

然后对于第 $i$ 个节点，就让尺子在序列上移动，因为长度固定，运动方向固定，运动长度固定。只能去一次，于是这时间复杂度是 $O(n)$ 。

然后是重点：

我们把序列保存在结构体里，然后对序列进行类似快速幂的操作。

如何对序列进行快速幂？

首先我们要让序列上的每个点移动到对应位置，这两个序列的操作可以看做序列的一次乘法。

```cpp
LZArray operator *(const LZArray &a)const{
	LZArray ans=*this;
	for(int i=1;i<=n;i++)ans.m[i]=a.m[ans.m[i]];
	return ans;
}
```
对于 $m$ 次操作，我们就仿照矩阵快速幂，写出序列快速幂。

下面是序列的结构体。

注意，当一个序列满足 $\forall a_i=i$ 我们称这个序列为单位序列。

对于长度相等任意序列乘以单位序列，都会得到原序列。

和矩阵乘法一样，序列乘法也不满足交换律。

这是关于序列的结构体

```cpp
struct LZ_Array{
	int m[N];
	void csh(){for(int i=1;i<=n;i++)m[i]=i;}
	void set(int k){
		int l=1,r=k+1;
		m[1]=k+1;
		for(int i=2;i<=n;i++){
			while(r+1<=n&&a[i]-a[l]>a[r+1]-a[i])l++,r++;
			if(a[i]-a[l]>=a[r]-a[i])m[i]=l;
			else m[i]=r;
		}
	}
	LZ_Array operator *(const LZ_Array &a)const{
		LZ_Array ans=*this;
		for(int i=1;i<=n;i++)ans.m[i]=a.m[ans.m[i]];
		return ans;
	}
	LZ_Array operator ^(int b){
		LZ_Array ans,a;ans.csh();
		a=*this;
		while(b){
			if(b&1)ans=ans*a;
			a=a*a;
			b>>=1;
		}
		return ans;
	}
}p;
```
下面是完整代码：

```cpp
#include<cstdio>
#include<algorithm>
#define N 1919810
#define int long long
using namespace std;
int n,k,m,a[N];
struct LZArray{
	int m[N];
	void csh(){for(int i=1;i<=n;i++)m[i]=i;}
	void set(int k){//尺取法求第k近位置
		int l=1,r=k+1;
		m[1]=k+1;
		for(int i=2;i<=n;i++){
			while(r+1<=n&&a[i]-a[l]>a[r+1]-a[i])l++,r++;
			if(a[i]-a[l]>=a[r]-a[i])m[i]=l;
			else m[i]=r;
		}
	}
	LZArray operator *(const LZArray &a)const{//序列乘法（一次跳跃操作）
		LZArray ans=*this;
		for(int i=1;i<=n;i++)ans.m[i]=a.m[ans.m[i]];
		return ans;
	}
	LZArray operator ^(int b){//快速幂
		LZArray ans,a;ans.csh();
		a=*this;
		while(b){
			if(b&1)ans=ans*a;
			a=a*a;
			b>>=1;
		}
		return ans;
	}
}p;
signed main(){
	scanf("%lld%lld%lld",&n,&k,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	p.set(k);
	p=p^m;
	for(int i=1;i<=n;i++)printf("%lld ",p.m[i]);
	return 0;
}



```




---

## 作者：yeshubo_qwq (赞：0)

**P3509 [POI2010] ZAB-Frog**

首先，要处理出每个点会跳到的那个点。

每个点枚举的复杂度是 $O(nk)$，不能接受。

类似滑动窗口的方式维护一段长度为 $k+1$ 的区间，包含 $i$。

此时点 $i$ 会跳到点一定是区间的头或者区间的尾。

然后套路的进行倍增即可。

注意两个坑点：

+ 不要直接令 $lg=60$，会炸空间。

+ 回答询问的枚举范围是 $lg\to0$，不是 $lg\to1$。

```cpp
const int maxn=1e6+5;
ll m,a[maxn];
int n,k,to[61][maxn],x;
ll dis(int x,int y){return abs(a[x]-a[y]);}
signed main(){
	read(n,k,m);
	go(i,1,n) read(a[i]);
	int head=1,tail=k+1;
	go(i,1,n){
		while (tail+1<=n && dis(i,tail+1)<dis(head,i)) head++,tail++;
		to[0][i]=(dis(head,i)>=dis(tail,i) ? head : tail);
	}
	int lg=log2(m)+1;
	go(i,1,m)
		go(j,1,n){
			//j->to[i-1][j]->to[i-1][to[i-1][j]]
			to[i][j]=to[i-1][to[i-1][j]]; 
		}
	go(j,1,n){
		ll step=m;
		x=j;
		down(i,lg,0)
			if (step-(1ll<<i)>=0){
				step-=(1ll<<i);
				x=to[i][x];
			}
		write(x),putchar(' ');
	}
	return 0;
}
```

---

## 作者：WOL_GO (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P3509)

这题的 $m$ 很大，如果一次次跳肯定会超时，所以我们考虑用倍增的方法来跳。我们可以预处理出一个 $step$ 数组 $\mathit{step}_{i,x}$ 表示从 $i$ 跳到 $2^x$ 步到达的位置，那么显然有 $\mathit{step}_{i,x}=\mathit{step}_{\mathit{step}_{i,x-1},x-1}$。但是，注意到这题的数据很大，开不了那么大的 $step$ 数组，所以，我们考虑时间换空间，每次倍增都重新求一遍 $step$ 数组。

然后我们考虑用 $O(n)$ 预处理出从一个点跳一次的位置，这里不会的兄弟可以参考[滑动窗口](https://www.luogu.com.cn/problem/P1886)，用双端队列求出第 $i$ 个点跳一次的位置。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+5;;
int n,k,l=1,r,ans[maxn],f[maxn],dp[maxn];
int m,a[maxn];
void read(int &xx){
    register char ch=getchar();
    register int ans=0;
    char t=0;
    while(!isdigit(ch))t|=ch=='-',ch=getchar/*_unlocked*/();
    while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar/*_unlocked*/();
    xx=t?-ans:ans;
    return ;
}
void write(int x){
    if(x<0){
        putchar('-');
        x*=-1;
    }
    char wr[18];
    int cnt=1;
    if(x==0){
        putchar('0');
        putchar(' ');
        return ;
    }
    while(x){
        wr[cnt++]=x%10+'0';
        x/=10;
    }
    for(cnt--;cnt;cnt--){
        putchar(wr[cnt]);
    }
    putchar(' ');
    return;
}
main(){
    read(n);
    read(k);
    read(m);
    for(int i=1;i<=n;i++)read(a[i]);
    r=k+1;
    f[1]=r;
    for(int i=2;i<=n;i++){
        while((a[i]-a[l])>(a[r+1]-a[i])&&r<n)l++,r++;
        if((a[i]-a[l])>=(a[r]-a[i]))f[i]=l;
        else f[i]=r;
    }
    for(int i=1;i<=n;i++)ans[i]=i;
    while(m){
        if(m%2==1)for(int i=1;i<=n;i++)ans[i]=f[ans[i]];
        for(int i=1;i<=n;i++)dp[i]=f[f[i]];
        for(int i=1;i<=n;i++)f[i]=dp[i];
        m/=2;
    }
    for(int i=1;i<=n;i++)write(ans[i]);
    return 0;
}
```


---

## 作者：喵の耳 (赞：0)

单调队列预处理出距当前第k远的点

双指针维护   倍增跳点

利用滚动数组压缩一维空间，就能开下了

具体操作见代码吧QAQ

## **另注意：$m<=10^{18}$**


------------

$code$

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace gengyf{
#define ll long long
const int maxn=1e6+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x*10)+c-'0';c=getchar();}
    return x*f;
}
ll n,k,m,a[maxn],t[maxn];
int f[maxn][2],g[maxn];
int main(){
    n=read();k=read();m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    ll l=1,r=k+1,lim=log2(m)+1;
    for(int i=1;i<=n;i++){
        while(r<n && a[r+1]-a[i]<a[i]-a[l]){
            l++,r++;
        }
        f[i][0]=(a[r]-a[i]>a[i]-a[l]?r:l);
    }
    if(m&1){
        for(int i=1;i<=n;i++){
            g[i]=f[i][0];
        }
    }
    else {
        for(int i=1;i<=n;i++){
            g[i]=i;
        }
    }
    r=1;t[0]=1;
    for(int i=1;i<=lim;i++) t[i]=t[i-1]<<1;
    for(int j=1;j<=lim;j++){
        for(int i=1;i<=n;i++){
            f[i][r]=f[f[i][r^1]][r^1];
        }
        if(m&t[j]){
            for(int i=1;i<=n;i++){
                g[i]=f[g[i]][r];
            }
        }
        r^=1;
    }
    for(int i=1;i<=n;i++){
        printf("%d ",g[i]);
    }
    return 0;
}
}
signed main(){
  gengyf::main();
  return 0;
}
```


---

