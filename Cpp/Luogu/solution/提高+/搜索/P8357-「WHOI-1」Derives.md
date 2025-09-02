# 「WHOI-1」Derives

## 题目背景

你的钱里面混进去了一个假币。

## 题目描述

你有 $n$ 枚硬币。经过准确的测量，你发现一定有一枚是假币，假币的质量与其他硬币不同。你想要找出这枚假币。

第 $i$ 轮，假设你当时有 $x_i$ 枚硬币，你会把当前钱堆所有钱分配到若干组，每组 $k_i$ 个，最终剩下的再单独分一组。每个硬币你要拿起来需要 $a$ 秒，那么这将会花费你 $ax_i$ 秒的时间。接下来，你会称量每一组，称量每组需要 $b$ 秒，所以这将会花费你 $b\cdot\lceil\frac{x_i}{k_i}\rceil$ 秒的时间。由于只有一枚假币，那么只会有一堆的质量与正常的质量不同。**在称量所有堆之后**，你将会选出与正常质量不同的那一堆，并进入下一轮，让 $x_{i+1}=k_i$。一直执行，直到 $x_i=1$。假设进行了 $m$ 轮，那么花费时间 $f=\sum\limits_{i=1}^{m}{(ax_i+b\cdot\lceil\frac{x_i}{k_i}\rceil)}$

请问，你在最差情况下（**即每轮选出不正常的都是 $k_i$ 个一堆的**）最少需要多长时间找出那枚假币？

## 说明/提示

**说明**

**你需要尽量使得花费的时间更少。**

本题采用 Special Judge。

首先，你输出的答案一定要合法，也就是你输出的答案要与下面的选择方法符合，否则将获得 $0$ 分。

接下来，评测机会对你的输出进行判断。如果你输出的答案合法且与正确答案的差 $\le9$，那么你将获得 $(10-d)\times100\%$ 的分数。例如，如果你输出的答案与正确答案的差为 $4$，那么你将获得 $60\%$ 的分数。如果你输出的答案等于正确答案，你将获得 $100\%$ 的分数。请不要输出多余的数字或少输出。

**数据范围**

- $\text{subtask 1(10pts)}:$ $1\le n\le2000$。
- $\text{subtask 2(20pts)}:$ $1\le n\le75000$。
- $\text{subtask 3(30pts)}:$ $1\le n\le10^7$。
- $\text{subtask 4(40pts)}:$ $1\le n\le10^9$。

对于所有数据，满足 $0<a,b\le10^9$。

**样例说明**

对于第一个样例，进行两轮。$x_1=20,k_1=4,x_2=4,k_2=1$。答案 $f=20+15+4+12=51$。

## 样例 #1

### 输入

```
20 1 3```

### 输出

```
51 2
4 1```

## 样例 #2

### 输入

```
1000 10 100```

### 输出

```
13570 4
72 12 3 1```

# 题解

## 作者：Exschawasion (赞：3)

理解题意后，不难发现一个事实：可以把硬币分成两堆称，然后合并起来。容易证明这是无后效性的。

所以就能根据题意推出方程。设 $f_i$ 表示 $i$ 个硬币中找假币的最小代价，有：

$$f_x=\operatorname{min}_{i=1}^{x-1}\{f_i+ai+b\lceil\frac{x}{i}\rceil\}$$

根据这个式子算就好了。但是这样 1D/1D 的转移是 $O(n^2)$ 的，过不去。优化？单调队列似乎不适用于这题。

正解是找性质：发现转移的时候出现 $b\lceil \frac{x}{i} \rceil$，熟悉整除分块套路的都知道可以对 $x-1$ 做整除分块。然后就显然了：对于每一块，取最左端点肯定是最优的。所以转移的时候只要转移每一块的左端点即可。

$x$ 范围很大，数组存不了。不过很容易发现，$x$ 是很稀疏的。但用 `map` 会带一个 $\log$ 铁定过不去；赛时出现了 `unordered_map` 通过的提交，但是赛后被出题人卡掉了。官方题解的解决方案是：使用特殊的方式把 $x$ 映射到坐标 $v$：

$$v(x)=\begin{cases}
x & x\leq\lfloor\frac{n-1}{x}\rfloor\\
k+\lfloor\frac{n-1}{x}\rfloor & x>\lfloor\frac{n-1}{x}\rfloor
\end{cases}$$

$k$ 是一个常数，取值范围大约在 $[\sqrt n,\inf)$，官方取的是 $10^5$。

有没有更优美的做法？其实有：C++ pbds 里有一个比 `unordered_map` 效率更高的容器 `hash_table`，用哈希值存储元素，平均下是 $O(1)$ 的。使用方式：

- 头文件（有两个）：

```cpp
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
```
- 命名空间：`using namespace __gnu_pbds;`。

- 声明方式：有两种哈希表：

```cpp
cc_hash_table<int,int> cc;//链表
gp_hash_table<int,int> gp;//开放寻址
```

一般开放寻址会快一点，效率瓶颈主要是在处理哈希冲突的方式上。虽然如此，由于这题的特殊性质，使用链表哈希表会更快一些（最慢测试点比开放寻址法快了约 500ms）。

然后就可以用记忆化搜索通过本题了。略微卡常后最慢的点能跑进 $0.8$ 秒，也算是稳定的了。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
// 省略快读模板
using namespace fastio;
ll n,a,b;
cc_hash_table<ll,ll> gp;//关键
cc_hash_table<ll,ll> pre;//关键
ll dp(ll x){
	auto at=gp.find(x);
	if(at!=gp.end())return at->second;
	ll ans=0x7fffffffffffffffll;
	ll N=x-1,p;
	for(ll L=1,R;L<=N;L=R+1){//整除分块
		R=N/(N/L);
		ll cur=dp(L)+(N/L+1)*b+x*a;
		if(cur<ans)ans=cur,p=L;
	}
	pre[x]=p;
	return gp[x]=ans;
}
const int maxn=10000000+5;
ll path[maxn],loc;
int main(){
	cin>>n>>a>>b;
	gp[1]=0,dp(n);
	int cur=n,v;
	while(v=pre[cur])path[++loc]=v,cur=v;
	wr(gp[n],' '),wr(loc);//wr 是快读输出函数
	for(int i=1;i<=loc;i++)wr(path[i],' ');
	io::flush();//快读刷新缓冲区
	return 0;
}
```


---

## 作者：rui_er (赞：3)

出题人没时间写题解，问了问思路跟我一样，然后我验题的时候也写了题解，因此以这个作为官方题解。

根据题意，发现显然有子问题，且满足最优子结构和无后效性，考虑进行动态规划。

设 $dp_i$ 表示在 $i$ 枚硬币中找一个假币的最小花费，不难写出一个 $\mathcal{O}\left(n^2\right)$ 的转移：

$$
dp_i=\min\limits_{j=1}^{i-1}\left\{dp_j+\left\lceil\dfrac{i}{j}\right\rceil\cdot b+i\cdot a\right\}
$$

我们发现对于一个 $i$，后面这堆东西 $\left\lceil\dfrac{i}{j}\right\rceil\cdot b+i\cdot a$ 的取值只有不超过 $\mathcal{O}\left(i^{\frac{1}{2}}\right)$ 个（证明的话分别看除数不超过根号和商数不超过根号的情况），于是我们可以进行整除分块来求。

还有前面的 $dp_j$ 呢，具体咋转移？发现 $dp$ 的值单调不降，因此对于整除分块过程的一段区间 $[L,R]$，从 $dp_L$ 转移是最优的。

到这里的时间复杂度为 $\mathcal{O}\left(n^{\frac{3}{2}}\right)$，可以跑过 $7.5\times 10^4$ 的数据，出题人的解法就止步于此了，但我又在数据范围后加了几个零！！

发现其实很多的 $dp$ 值是没有机会被转移的，求出它们完全是浪费时间，因此改用记忆化搜索，就可以跑过 $10^9$ 了，甚至 $10^{11}$ 也只需要十秒钟。

那这是个啥复杂度呢？发现递归树长得跟杜教筛一样，可以证明复杂度同样为 $\displaystyle\int_{2}^{\sqrt{n}}\left(\sqrt{x}+\sqrt{\frac{n}{x}}\right)\mathrm{d}x=\mathcal{O}\left(n^{\frac{3}{4}}\right)$。

然后如果用 map 带 $\log$ 或者用巨大常数的 umap 是过不去滴（不过赛时有人过了，喊了出题人赛后加强数据），这时候就需要对数组下标进行一个映射然后存了。

映射方法大概是这样：

$$
\operatorname{hash}(x)=
\begin{cases}
x,&x\le\left\lfloor\frac{n-1}{x}\right\rfloor\\
10^5+\left\lfloor\frac{n-1}{x}\right\rfloor,&\textrm{otherwise}
\end{cases}
$$

每个子任务的最后一个测试点是 hack 数据（[被 hack 的惨案](https://www.luogu.com.cn/record/73838645)），因为是向上取整所以存的时候是 $\left\lfloor\frac{n-1}{x}\right\rfloor$，据出题人本人所说这是他跑了 10min 跑出来的 hack 数据。

参考代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 3e6+5, inf = 0x3f3f3f3f3f3f3f3fll;

ll n, a, b, dp[N], from[N];
vector<ll> path;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
ll id(ll x) {
	if(x <= (n - 1) / x) return x;
	else return 100000 + (n - 1) / x;
}
ll dfs(ll i) {
	ll _ = id(i);
	if(dp[_] < inf) return dp[_];
	for(ll L=1,R=0;L<i;L=R+1) {
		R = (i - 1) / ((i - 1) / L);
		ll now = dfs(L) + ((i - 1) / L + 1) * b + i * a;
		if(now < dp[_]) {
			dp[_] = now;
			from[_] = L;
		}
	}
	return dp[_];
}

int main() {
	memset(dp, 0x3f, sizeof(dp));
	scanf("%lld%lld%lld", &n, &a, &b);
	dp[id(1)] = 0;
	dfs(n);
	for(ll i=n;from[id(i)];i=from[id(i)]) path.push_back(from[id(i)]);
	printf("%lld %lld\n", dp[id(n)], (ll)path.size());
	for(auto i : path) printf("%lld ", i);
	puts("");
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

$f_i$ 表示 $i$ 个硬币里找出假币的最小时间

+ $f_i=\min\{f_j+b\lceil \dfrac i j \rceil\}+ai$。

显然存在：$f_x<f_y \mid x<y$。

发现这个 $\lceil\rceil$ 比较恶心，套不了整除分块的 $\lfloor\rfloor$，就把这个玩意搞掉。

$j\mid i$ 时 $\lceil\dfrac i j\rceil=\lfloor\dfrac {i} j\rfloor$；

$j\nmid i$ 时 $\lceil\dfrac i j\rceil=\lfloor\dfrac {i} j\rfloor+1$。

但是注意到，$j\mid i$ 时 $\lfloor\dfrac {i} j\rfloor=\lfloor\dfrac {i-1} j\rfloor+1$，
$j\not\mid i$ 时 $\lfloor\dfrac i j\rfloor=\lfloor\dfrac {i-1} j\rfloor$。

统一一下得到 $\lceil\dfrac i j\rceil=\lfloor\dfrac {i-1} j\rfloor+1$

对着 $i-1$ 整除分块，块 $[l,r]$ 的 $b\lceil \dfrac i j \rceil$ 相同，只要 $f_j\mid l\le j\le r$ 最小。由于 $f_x<f_y \mid x<y$ 的结论，块 $[l,r]$ 的最小值一定是在 $f_l$ 上。

这样嗯写恭喜你获得了三十分。

```cpp
#include <iostream>
using namespace std;
long long a,b,n;
int frm[1000005],f[1000005];
const int inf=1<<30;
inline long long solve(int x)
{
	int l,r,N,i;
//		printf("%d %d %d\n",x,l,f[n]);
	if(f[x]!=inf)return f[x];
	N=x-1;
	for(l=1;l<=N;l=r+1)
	{
		r=N/(N/l);
		if(f[x]>solve(l)+(N/l+1)*b+a*x)
		{
			f[x]=f[l]+(N/l+1)*b+a*x;
			frm[x]=l;
		}
	}
	return f[x];
}
inline void output(int x,int cnt)
{
	if(frm[x]==0)
		printf(" %d\n",cnt);
	else
		output(frm[x],cnt+1);
	return ;
}
inline void outorder(int x)
{
	if(frm[x]==0)return ;
	printf("%d ",frm[x]);
	outorder(frm[x]);
	return ;
}
int main()
{
	cin>>n>>a>>b;
	for(auto i=2;i<=n;++i)f[i]=inf;
	solve(n);
	printf("%d",f[n]);
	output(n,0);
	outorder(n);
	return 0;
}
```

考虑优化存储 `frm` 和 `f`，容易发现其实被访问 $f_i$ 的不是很多，所以静态数组是不明智的。果断换 `unordered_map`。

```cpp
#include <unordered_map>
#include <iostream> 
using namespace std;
long long a,b,n;
const long long inf=1ll<<60;
long long f[1000005];
int frm[1000005];
int nxt;unordered_map<int,int> q;
inline int rid(int x){return q[x]?q[x]:(q[x]=++nxt);}
inline long long solve(int x)
{
	register int id=rid(x);
	int l,r,i;long long N;
//		printf("%d %d %d\n",x,l,f[n]);
	if(f[id]!=inf)return f[id];
	N=x-1;
	for(l=1;l<=N;l=r+1)
	{
		r=N/(N/l);
		if(f[id]>solve(l)+(N/l+1)*b+a*x)
		{
			f[id]=f[rid(l)]+(N/l+1)*b+a*x;
			frm[id]=l;
		}
	}
	return f[id];
}
inline void output(int x,int cnt)
{
	if(frm[rid(x)]==0)
		printf(" %d\n",cnt);
	else
		output(frm[rid(x)],cnt+1);
	return ;
}
inline void outorder(int x)
{
	if(frm[rid(x)]==0)return ;
	printf("%d ",frm[rid(x)]);
	outorder(frm[rid(x)]);
	return ;
}
signed main()
{
	cin>>n>>a>>b;
	for(auto i=0;i<=100000;++i)f[i]=inf;
	f[rid(1)]=0;
	solve(n);
	printf("%lld",f[rid(n)]);
	output(n,0);
	outorder(n);
	return 0;
}
```

复杂度分析我不是很会，可以参考别的题解。结论是 $O(n^{\frac 3 4})$。虽然 `umap` 常数挺大但是一点六秒还是可以一冲的。

---

## 作者：Cocoly1990 (赞：0)

~~算是对两个长得几乎一摸一样的验题人和出题人题解的补充。~~

# Part Ⅰ

我们一步一步来，先从朴素的动态规划来。我们记 $f_i$ 为选 $i$ 个硬币的方案数，此时官方题解就直接甩了一个柿子上来。

$$f_i=a\times i+\min\limits_{j=1}^{i-1}\{f_j+\lceil \frac{i}{j}\rceil\times b\}$$

我们不妨理解一下他的具体含义，转移过程其实实在枚举 $m_i$，显然，当我们选定一个 $m_i$ 时，问题就缩减为一个 $f_{m_i}$ 的子问题。那么显然加上这次操作的代价就有了最后的答案。

# Part Ⅱ

我们注意到 $\lceil \frac{i}{j}\rceil = \lfloor \frac{i-1}{j}\rfloor + 1$，根据我们学过的数论分块知识，直接对 $\lfloor \frac{i-1}{j}\rfloor$ 数论分块就好了，可以观察到 $\forall i>j,f_i\geq f_j$，又因为显然数论分块值是连续的，所以每次转移必然转移左端点。

# Part Ⅲ

如何构造映射？我们观察到每个需要用到的转移点必然是数论分块的端点，显然这个端点和数论分块的分母无关，因此可以构造类似的映射。


---

