# [NOISG 2018 Prelim] Knapsack

## 题目背景

翻译自 [NOISG 2018 Prelim B. Knapsack](https://github.com/noisg/sg_noi_archive/tree/master/2018_prelim)。

## 题目描述

你获得了超市的“免费购物”优惠，规则如下：
- 你有一个容量为 $S$ 的购物篮。超市里共有 $n$ 样东西。第 $i$ 样东西的重量 $w_i$，价值为 $v_i$，这样东西共有 $k_i$ 个。
- 你可以向你的购物篮塞入你想买的东西，前提是**这些东西的重量总和不超过购物篮的容量**。

现在，你只想知道，在满足规则的情况下，你最多能带多少价值的东西回去？

**请不要低估本题目的难度，如果你看到这就想写，请查看【数据范围】一栏**。

## 说明/提示

### 【样例 #1 解释】
拿第 $2,3,4,5$ 种东西，每种东西拿一个。

此时价值为 $15$，重量为 $8$。

### 【样例 #2 解释】
拿完第 $1,2$ 种东西后拿一个第 $3$ 种东西。

此时价值为 $5400$，重量为 $20$。

### 【数据范围】
| $\text{Subtask}$ | 分值 | $n\leq$ | $k\leq$ |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $0$ | 样例 | 样例 |
| $1$ | $12$ | $1$ | - |
| $2$ | $17$ | $100$ | $1$ |
| $3$ | $20$ | $100$ | $10$ |
| $4$ | $24$ | $100$ | $10^9$ |
| $5$ | $27$ | $10^5$ | $10^9$ |
| $6$（hack） | $0$ | $10^5$ | $10^9$ |

对于 $100\%$ 的数据：
- $1 \leq w_i \leq S \leq 2000$
- $1 \leq n \leq 10^5$
- $1 \leq v_i \leq 10^6$
- $1 \leq k_i \leq 10^9$

## 样例 #1

### 输入

```
15 5 
4 12 1 
2 1 1 
10 4 1 
1 1 1 
2 2 1```

### 输出

```
15```

## 样例 #2

### 输入

```
20 3 
5000 15 1 
100 1 3 
50 1 4```

### 输出

```
5400```

# 题解

## 作者：ben090302 (赞：6)

题意简单，就是一个多重背包。

但是这题的数据范围实在是反常。

我们发现这题的容量出奇的小，可以接受 $S^2$ 左右的算法，带个 $\log$ 也不算困难。

多重背包的标准复杂度最优是 $nS$ 也就是单调队列优化，如果信仰足够强大也许能过，但是这个时间限制我觉得有点紧张，我们不妨考虑更优秀的做法。

首先看向这个 $k_i$，我们会发现这个 $k$ 的数据范围只是吓人用的，就算每个物品重量都只有 $1$，我们也拿不到 $10^9$ 个数，这是不可能的，最多只能拿 $\lfloor\frac{S}{w} \rfloor$ 个，后面除法默认取整省去不写。

还没完，如果我们只看同种重量的物品，我们也只需要观察价值前 $\frac{S}{w}$ 个，再往后显然是没有意义的。可以注意到重量的数量和 $S$ 是一致的，分析时我们就认为重量正好是 $S$ 种来分析复杂度。

简单分析一下现在物品数量的上界，是 $\sum_{w=1}^n \frac{S}{w}$，这是一个调和级数，大概约等于 $S\log S$。

我们直接对这些剩下的物品做简单的 $01$ 背包，复杂度 $O(S^2\log S+n\log n)$，后面那个 $n\log n$ 来自于排序。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
const int SN=2005;
int n,S;

struct node{
	int v,w,k;
	bool operator<(node x){
		return v<x.v;
	}
}a[N];
struct nd{
	int v,w;
}it[SN*30];
vector<node> item[SN];
int cnt;
int f[SN];
signed main(){
	cin>>S>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].v>>a[i].w>>a[i].k;
		item[a[i].w].push_back(a[i]);
	}
	for(int i=1;i<=S;i++) sort(item[i].begin(),item[i].end());
	for(int i=1;i<=S;i++){
		int j=0;
		while(j<=S/i and !item[i].empty()){
			it[++cnt]={item[i].back().v,item[i].back().w};
			j++;
			item[i].back().k--;
			if(!item[i].back().k) item[i].pop_back();
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=S;j>=it[i].w;j--){
			f[j]=max(f[j],f[j-it[i].w]+it[i].v);
		}
	}
	cout<<f[S];
}
```

---

## 作者：WangYongkai__AFO (赞：3)

## 前置芝士：多重背包的二进制优化或单调队列优化

### 双倍经验：

_https://www.luogu.com.cn/problem/P1776_ 

# Solution：

#### 思路：
首先我们看题意，仔细思考可以看出这是个多重背包 DP ，因为每个物品有多个，所以我们可以考虑多重背包的二进制优化，(其实单调队列的优化也可以，但是相比二进制优化比较难理解而且不是很好写)，想要学习单调队列优化的同学可以去上面双倍经验的题解学习一下。

#### 优化讲解：

什么是二进制优化呢？我们可以举个例子。以 15 为例， $18=1+2+4+8+3$ ，即 $18=1_{2}+10_{2}+100_{2}+1000_{2}+3_{10}$ ，按照这样的二进制拆分后，我们可以用前四个二进制数分别表示 $[1,15]$ 的数，至于 $(15,18]$ 的数我们可以用已经表示的数加上3求得，因此我们可以通过枚举二进制拆分出来的方案得出每一个物品取 $[0,k_{i}]$ 的情况，从而达到优化时间复杂度的目的。优化后的时间复杂度大概是 $O(sn\sum_{i=1}^{n}k_{i})$ 。

_优化后结合背包板子即可，不想挂分的话记得数组开大一点_ 

#### Codes：

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<stack>
#include<queue>
#include<map>
#include<vector>
#include<cstdio>
#include<set>
#include<bitset>
#include<iomanip>
using namespace std;
int s,n;
const int N=1e7+5;
long long v[N],w[N],k[N],dp[N];
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>s>>n;
	long long a,b,c,cnt=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>c;
		long long k=1;
		while(k<=c)
		{
			v[++cnt]=k*a,w[cnt]=k*b;
			c-=k;
			k*=2;
		}
		if(c)
		{
			v[++cnt]=a*c,w[cnt]=b*c;
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		for(int j=s;j>=w[i];j--)
		{
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
		}
	}
	cout<<dp[s];
 	return 0;
}
```

---

## 作者：DemonPlayer (赞：2)

一看到题目，这不是裸分组背包吗？赶紧写了个时间复杂度为 $O(n\times W\times k)$ 的暴力动归，然后就看到了俩 TLE。只好重新思考，$n\times W$ 肯定跑不掉了，$k$ 怎么优化呢？大家都知道 $2$ 的整数次幂的和能表示任何数，我们就可以把 $k$ 打包成 $2$ 的整数次幂，再存下来，不就成了 01 背包了吗？时间复杂度 $O(n\times W \times \log k)$。       
## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=2e7+10;
int n,w[N],v[N],W,f[2005],cnt,t;

signed main(){
	std::ios::sync_with_stdio(0);
	cin>>W>>n;
	for(int i=1;i<=n;i++){
		int a,b,k;
		cin>>a>>b>>k;
		t=1;
		while(t*2-1<=k){
			cnt++;
			w[cnt]=t*b;
			v[cnt]=t*a;
			t<<=1;
		}
		k-=(t-1);
		if(k){
			++cnt;
			w[cnt]=k*b;
			v[cnt]=k*a;
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=W;j>=w[i];j--){
			f[j]=max(f[j],f[j-w[i]]+v[i]);
		}
	}
	cout<<f[W];
	return 0;
}
```

---

## 作者：_iridescent (赞：2)

### 思路

这道题，乍一看其实就是多重背包的板子题 ~~（实际上就是）~~，只需要普通的二进制优化再加上卡亿点点常就可以了。

那么二进制优化是什么呢，简单来说就是通过把本题中的 $k_i$ 通过类似二进制表示的方法拆成几个和为 $k_i$ 的数，从而将其转换为 01 背包。

举个例子，以 12 为例，我们可以将其表示为 $12=1+2+4+5$，或者说是 $12=2^0+2^1+2^2+5$，这样就可以把 12 个单独的物品分成了4 件不同的价值与体积为原来数倍的物品，每个物品仅有一件，这样就能将其转换成 01 背包了。

### 代码


```cpp
#include<stdio.h>
#define ll long long
#define endl '\n'
#define max(a,b) ((a)>(b)?(a):(b))
#define N 10000005
using namespace std;
int n,m;
ll tot;
ll v[N],w[N],dp[N];
inline ll read(){
	ll f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
signed main(){
//	freopen("P11297.in","r",stdin);
//	freopen("mamba.out","w",stdout);
	m=read(),n=read();
	for(register ll i=1;i<=n;i++){
		int a,b;ll c;
		a=read(),b=read(),c=read();
		for(register ll j=1;j<=c;j<<=1){ //倍增拆分物品
			v[++tot]=j*a*1LL;
			w[tot]=j*b*1LL;
			c-=j;
		}
		if(c){ //注意处理剩下的物品
			v[++tot]=c*a;
			w[tot]=c*b;
		}
	}
	for(register ll i=1;i<=tot;i++){
		for(register ll j=m;j>=w[i];j--){
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]); //板子
		}
	}
	write(dp[m]);
	return 0;
}
```

---

## 作者：DDD_et (赞：2)

# P11297 Solution

**做法：多重背包 + 二进制优化**

## 题意分析

$n$ 个物品，第 $i$ 种有 $k_i$ 个，每个体积为 $w_i$，价值为 $v_i$，问在总体积不超过 $S$ 的情况下能获得的最大价值为多少。

## 思路

~~我太菜了不会单调队列优化，想做单调队列的同学请自行度娘。~~

多重背包板子，[什么是背包问题？](https://baike.baidu.com/item/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98/2416931?fr=ge_ala)

多重背包的初步思路就是将每种物品枚举一遍，再依次枚举每种物品取的个数，但这种方法的时间复杂度为 $\mathcal{O}(\prod\limits_{i=1}^nk_i)$，会超时，那么我们需要进行优化：**二进制优化**。

我们知道，任意十进制整数 $x$ 可以表示为二进制形式；设 $x$ 的二进制形式为 $b$ 位的二进制数，第 $i$ 位是 $n_i = 0/1$，那么我们通过将其重新转换为十进制整数的过程可以发现 $x$ 可以表示为如下形式：

$$
x={n_1}2^{p_1}+{n_2}2^{p_2}+{n_3}2^{p_3}+\dots+{n_b}2^{p_b}(\forall i \in [1,b],p_i \in \N)
$$

那么由上可得，对于这个数 $x$，只要有 ${n_1}2^{p_1},{n_2}2^{p_2},{n_3}2^{p_3},\dots,{n_b}2^{p_b}$ 这几个数就可以凑出 $[0,x]$ 之间的任何数，那么可以用一个变量表示 $p_{[1,b]}$，每次将其乘上 $2$ 表示数位上的 $1$，但由于 $x$ 可能不一定是若干个连续的 $2$ 的幂之和，所以如果最后有剩余多做一次，将剩下的补齐即可。

那么可以将题目中的所有 $v_i$ 和 $w_i(\forall i \in [1,n])$ 进行打包，打成 $\lceil \log_2 k_i \rceil$ 个包，让原本的 $k_i$ 个物品变为 $\lceil \log_2 k_i \rceil$ 个，最后进行01背包即可。

时间复杂度 $\mathcal{O}(\prod\limits_{i=1}^n\lceil \log_2 k_i \rceil)$。

## 代码

```c++
#include <iostream>
using namespace std;
constexpr int N = 5e6 + 10;
long long v[N], w[N], f[N], a, b, k, p = 1;
int S, n, idx; char c;

long long qread ()
{
	int f = 1, x = 0; c = getchar ();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar (); }
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + c - 48, c = getchar ();
	return x * f;
}

void qwrite (long long a)
{
    if (a / 10) qwrite (a / 10);
    else putchar ('a');
}

int main ()
{
    S = qread (), n = qread ();
	for (int i = 1; i <= n; i ++)
	{
		a = qread (), b = qread (), k = qread (), p = 1;
		while (k >= p)
		{
			w[++ idx] = (long long)p * a, v[idx] = (long long)p * b;
			k -= p, p <<= 1;
			//p就是每次增加的物品个数，k(物品总个数)每次就去掉p个 
		}
		//如果还有剩余就再打一包 
		if (k > 0) w[++ idx] = (long long)k * a, v[idx] = (long long)k * b;
	}
	
	//01背包部分 
	n = idx;
	for (int i = 1; i <= n; i ++)
		for (int j = S; j >= w[i]; j --)
			f[j] = max (f[j], f[j - w[i]] + v[i]);
	cout << f[S];
	return 0; 
}
```

### 写在最后

我这个代码里的 `qwrite`（快写）没用，但是把这个函数删掉就会 TLE 最后一个点，注意灵异事件。

**谢谢观看！**

---

## 作者：ycy1124 (赞：1)

### 题意
你有一个能装重量为 $m$ 的背包。一共有 $n$ 种物品，每个物品有三个值 $w_i,v_i,k_i$ 分别表示这种物品的重量，价值和个数。试求最多能装下价值为多少的物品。
### 思路
第一眼感觉很想二进制拆分，写上去之后 T 了。观察数据范围，发现 $m\le2000$ 非常的反常，极有可能是突破口。我们发现，由于 $m\le2000$，所以每种物品最多选择 $2000$ 个，并且单个物品最多只有 $2000$ 种不同的重量。我们可以考虑将每种物品按他的重量分开来算。对于重量为 $w_i$ 的所有物品，我们显然最多只会选择其中价值最大的 $\lfloor\frac{m}{w_i}\rfloor$ 个。因为如果选择了其他的，这些里面肯定有没选完的，我们拿这些去替换肯定不劣。

根据上面的思路，首先我们将所有的物品按价值从大到小排个序，然后从前往后枚举每种物品，如果它是同重量物品中前 $\lfloor\frac{m}{w_i}\rfloor$ 个，我们就将它加入最终需要被 dp 的物品当中，否则就不管了。期间可以用二进制拆分优化。最后对于选出来的这些物品做一个背包 dp 即可。我们令选出来的物品重量为 $v_i$，价值为 $w_i$ 转移方程：
$$
dp_i=\max(dp_{i-v_i}+w_i,dp_i)
$$
即拿不拿这个物品的两种可能的最大值。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,dp[2005],sum[2005],tot;
struct Node{
	int a,b,c;
}w[100005];
struct node{
	int w,v;
}s[100005];
inline bool cmp(Node x1,Node x2){//自定义排序 
	return x1.a>x2.a;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>w[i].a>>w[i].b>>w[i].c;
	}
	sort(w+1,w+n+1,cmp);
	for(int i=1;i<=n;i++){
		int qwq=min(m/w[i].b-sum[w[i].b],w[i].c);//求出最多还能选多少个第 i 种物品 
		sum[w[i].b]+=qwq;//累加个数 
		int base=1;
		while(qwq>=base){//二进制拆分优化 
			s[++tot]={w[i].a*base,w[i].b*base};
			qwq-=base;
			base<<=1;
		}
		if(qwq){
			s[++tot]={w[i].a*qwq,w[i].b*qwq};
		}
	}
	int mi=0;
	for(int i=1;i<=tot;i++){//背包 
		mi+=s[i].v;
		for(int j=min(mi,m);j>=s[i].v;j--){
			dp[j]=max(dp[j-s[i].v]+s[i].w,dp[j]);
		}
	}
	int ans=0;
	for(int i=m;i>=0;i--){
		ans=max(ans,dp[i]);
	}
	cout<<ans;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/216648877)。

---

## 作者：kuaiCreator (赞：1)

## 题目大意
就是多重背包，不过数据范围较大。
## 解题思路
### 做法一：朴素多重背包
自行搜索。  
### 做法二：二进制优化
基本思想是将第 $i$ 组的 $num_i$ 个物品进行二进制分组，例如：某组有 $10$ 个物品可以被拆分为 $1$ 个一组 $2$ 个一组 $4$ 个一组 $3$ 个一组，四个新物品。 这四个新物品任意组合可以实现，原来物品按照 $0$ 至 $10$ 个的任意组合。再把问题转为基础 $01$ 背包解决。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll w[15000005], v[15000005], dp[2005];
ll m, n, x, y, z, cnt;
ll read() {
	ll x = 0;
	char ch = getchar_unlocked();
	while (ch<'0'||ch>'9') ch = getchar_unlocked();
	while (ch>='0'&&ch<='9') x = (x<<3)+(x<<1) + ch - '0', ch = getchar_unlocked();
	return x;
}
int main() {
	m = read();
	n = read();
	for (ll i = 1; i <= n; ++i) {
		x = read(), y = read(), z = read();
		for (ll j = 1; j <= z; j <<= 1) {
			v[++cnt] = j*x;
			w[cnt] = j*y;
			z -= j;
		}
		if (z) {
			v[++cnt] = z*x;
			w[cnt] = z*y;
		}
	}
	for (ll i = 1; i <= cnt; ++i)
		for (ll j = m; j >= w[i]; --j)
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
	cout << dp[m];
	return 0;
}
```
### 做法三：单调队列优化
本题我尝试了二进制优化，会超时几个测试点。不知道其他题解的二进制优化怎么过的。

![](https://cdn.luogu.com.cn/upload/image_hosting/t1gvdpe2.png)

观察上图，如果物品 $2$ 有 $3$ 个，那么状态转移就是从所有的黄色虚线圈转移到红色虚线圈。即对于容量为 $9$ 的背包 $dp[2][9]$ 得从 $dp[1][9]$、$dp[1][6]$、$dp[1][3]$、$dp[1][0]$ 四个状态转移过来。同理如果是容量为 $12$ 的背包 $dp[2][12]$ 得从 $dp[1][12]$、$dp[1][9]$、$dp[1][6]$、$dp[1][3]$ 四个状态转移过来。把对转移状态无用的去掉观察 $dp[1][0]$ 至 $dp[1][12]$ 发现这几个状态对于物品 $2$ 的重量的余数相同，即除以重量是 $3$ 都余数为 $0$。显然转移时可以利用单调队列快速找到最大最值进行转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M = 2005, N = 10005;
long long n, m;
long long dp[M], qval[M], que[M];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> m >> n ;
	for (int i = 1; i <= n; i ++) {
		long long c, w,  s;
		cin >> c >> w  >> s;
		memcpy(qval, dp, sizeof dp);
		for (int r = 0; r < w; r ++) {		//按照余数分组
			int head = 0, tail = -1;
			for (int k = 0; r + k * w <= m; k ++) {
				while (head <= tail && k - que[head] > s) head++;
				while (head <= tail && qval[r + k * w] - k * c >= qval[r + que[tail] * w] - que[tail] * c)
					tail --;
				que[++ tail] = k;
				dp[r + k * w] = qval[r + que[head] * w] + (k - que[head]) * c;
			}
		}
	}
	cout << dp[m] << endl;
	return 0;
}
```

---

