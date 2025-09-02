# [ABC032D] ナップサック問題

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc032/tasks/abc032_d

0/1ナップサック問題を解いてください。0/1ナップサック問題とは以下のような問題のことです。

- $ N $ 個の荷物があり、$ i\ (1≦i≦N) $ 番目の荷物には価値 $ v_i $ と重さ $ w_i $ が割り当てられている。
- 許容重量 $ W $ のナップサックが1つある。
- 重さの和が $ W $ 以下となるように荷物の集合を選びナップサックに詰め込むとき、価値の和の最大値を求めよ。ただし、同じ荷物は一度しか選ぶことができない。

## 说明/提示

### 部分点

この問題には部分点が設定されている。満点は $ 100 $ 点である。

- $ N≦30 $ を満たすデータセット $ 1 $ に正解した場合は、$ 34 $ 点が与えられる。
- $ N≦200 $ かつ全ての $ i(1≦i≦N) $ について $ 1≦w_i≦1000 $ を満たすデータセット $ 2 $ に正解した場合は、上記の点数とは別に $ 33 $ 点が与えられる。
- $ N≦200 $ かつ全ての $ i(1≦i≦N) $ について $ 1≦v_i≦1000 $ を満たすデータセット $ 3 $ に正解した場合は、上記の点数とは別に $ 33 $ 点が与えられる。

### Sample Explanation 1

$ 2 $ 番目と $ 3 $ 番目のアイテムを選ぶと、合計の重みが $ 10 $ で価値が $ 16 $ となり、最大価値を達成できます。 この入出力例は、データセット $ 1,2,3 $ の制約を満たしているため、全てのデータセットの採点に用いられます。

### Sample Explanation 2

この入出力例は、データセット $ 1 $ の制約のみ満たしているため、データセット $ 2,3 $ の採点には用いられません。

### Sample Explanation 3

この入出力例は、データセット $ 3 $ の制約を満たしていないため、データセット $ 3 $ の採点には用いられません。

### Sample Explanation 4

この入出力例は、データセット $ 2 $ の制約を満たしていないため、データセット $ 2 $ の採点には用いられません。

## 样例 #1

### 输入

```
3 10
15 9
10 6
6 4```

### 输出

```
16```

## 样例 #2

### 输入

```
30 499887702
128990795 137274936
575374246 989051853
471048785 85168425
640066776 856699603
819841327 611065509
704171581 22345022
536108301 678298936
119980848 616908153
117241527 28801762
325850062 478675378
623319578 706900574
998395208 738510039
475707585 135746508
863910036 599020879
340559411 738084616
122579234 545330137
696368935 86797589
665665204 592749599
958833732 401229830
371084424 523386474
463433600 5310725
210508742 907821957
685281136 565237085
619500108 730556272
88215377 310581512
558193168 136966252
475268130 132739489
303022740 12425915
122379996 137199296
304092766 23505143```

### 输出

```
3673016420```

## 样例 #3

### 输入

```
10 2921
981421680 325
515936168 845
17309336 371
788067075 112
104855562 96
494541604 960
32007355 161
772339969 581
55112800 248
98577050 22```

### 输出

```
3657162058```

## 样例 #4

### 输入

```
10 936447862
854 810169801
691 957981784
294 687140254
333 932608409
832 42367415
642 727293784
139 870916042
101 685539955
853 243593312
369 977358410```

### 输出

```
1686```

# 题解

## 作者：残阳如血 (赞：1)

### $\textbf{Description}$
> 下文 $v_i$ 表示体积，$w_i$ 表示价值，$V$ 表示背包容量。

给定一个 $01$ 背包，有三种数据范围：
- Subtask 1：$1\le n\le30$，$1\le v_i,w_i,V\le10^9$；
- Subtask 2：$1\le n\le200$，$1\le w_i,V\le10^9$，$1\le v_i\le10^3$；
- Subtask 3：$1\le n\le200$，$1\le v_i,V\le10^9$，$1\le w_i\le10^3$。

### $\textbf{Solution}$
三个 Subtask 显然无法统一处理，考虑分类讨论。
#### $\textbf{Subtask 1}$
发现突破口为 $n \le 30$，考虑搜索。

但是如果直接爆搜，时间复杂度会达到 $O(2^n)$，虽然可以剪枝，但是对于 $n=30$ 的数据范围可能会 TLE（？）

~~好吧别人直接爆搜都过了。~~

但是，$\left\lfloor\dfrac{n}{2}\right\rfloor\le15$，$2^{15}$ 次操作是我们可以接受的，所以考虑 [Meet in the Middle](https://oi-wiki.org/search/bidirectional/#meet-in-the-middle)。

令 $x=\left\lfloor\dfrac{n}{2}\right\rfloor$。

对于 $[1,x]$，爆搜出全部方案，统计在 `std::map` 中，键为体积，值为当前体积的最大价值。

对于 $(x,n]$，同样爆搜出全部方案，假设当前方案体积为 $v_s$，价值为 $w_s$。

那么我们可以在 $[1,x]$ 中选取一个体积 $\le V-v_s$ 的方案。这些方案可以通过 `upper_bound` 求得，但是还是需要遍历全部方案，时间复杂度较劣。

故考虑在第一次搜索结束后，统计前缀最大值，在 `std::map` 的值中存储小于等于当前体积的所有方案中，价值的最大值，这样就可以在 `upper_bound` 后 $O(1)$ 求得最大价值。
#### $\textbf{Subtask 2}$
发现体积较小，故令 $f_{i,j}$ 表示从前 $i$ 个物品中选，总体积**恰好**为 $j$ 的最大价值。

转移即为：
$$
f_{i,j}=\max\{f_{i-1,j},f_{i-1,j-v_i}+w_i\}
$$

显然可以压维。

故初始化 $f_0=0$，其它值为 $-\infty$。

最终结果为：
$$
\max\limits_{i=0}^{V}\{f_i\}
$$
#### $\textbf{Subtask 3}$
发现价值较小，故令 $f_{i,j}$ 表示从前 $i$ 个物品中选，总价值**恰好**为 $j$ 的最小体积。

转移即为：
$$
f_{i,j}=\min\{f_{i-1,j},f_{i-w_i}+v_i\}
$$

同样可以压维。

故初始化 $f_0=0$，其它值为 $+\infty$，

最终结果为：
$$
\max\limits_{{i\in[0,\sum_{p=1}^{n}w_p]\land f_i\le V}}i
$$

~~好丑啊。~~
### $\textbf{Code}$

[record](https://atcoder.jp/contests/abc032/submissions/62482683)。

```cpp
// Subtask 1：Meet in the middle
// Subtask 2：令 f[i][j] 从前 i 个中，总体积为 j 的最大价值
// Subtask 3：令 f[i][j] 从前 i 个中，总价值为 j 的最小体积

#include <bits/stdc++.h>
using lint = long long;
const int N = 210, M = 1e3 + 10;

lint ans, s_w, f[N * M];
int n, x, V, mx_v, mx_w, v[N], w[N];
std::map<lint, lint> mp;

void dfs1(int i, lint sv, lint sw) {
	if (i > x) {
		mp[sv] = std::max(mp[sv], sw);
		return ;
	}
	dfs1(i + 1, sv, sw);
	if (sv + v[i] <= V) dfs1(i + 1, sv + v[i], sw + w[i]);
}

void dfs2(int i, lint sv, lint sw) {
	if (i > n) {
		ans = std::max(ans, (--mp.upper_bound(V - sv))->second + sw);
		return ;
	}
	dfs2(i + 1, sv, sw);
	if (sv + v[i] <= V) dfs2(i + 1, sv + v[i], sw + w[i]);
}

void work1() {
	x = n / 2;
	dfs1(1, 0, 0);
	for (auto it = mp.begin(); it != mp.end(); ++it)
		it->second = std::max(it->second, std::prev(it)->second);
	dfs2(x + 1, 0, 0);
	std::cout << ans << std::endl;
}

void work2() {
	memset(f, -0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = V; j >= v[i]; --j)
			f[j] = std::max(f[j], f[j - v[i]] + w[i]);
	lint ans = 0;
	for (int i = 0; i <= V; ++i)
		ans = std::max(ans, f[i]);
	std::cout << ans << std::endl;
}

void work3() {
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; ++i)
		for (lint j = s_w; j >= w[i]; --j)
			f[j] = std::min(f[j], f[j - w[i]] + v[i]);
	lint ans = 0;
	for (lint i = 0; i <= s_w; ++i)
		if (f[i] <= V) ans = std::max(ans, i);
	std::cout << ans << std::endl;
}

int main() {
	std::cin >> n >> V;
	for (int i = 1; i <= n; ++i) {
		std::cin >> w[i] >> v[i];
		mx_v = std::max(mx_v, v[i]);
		mx_w = std::max(mx_w, w[i]);
		s_w += w[i];
	}
	if (n <= 30) work1(); // Subtask1
	else if (mx_v < M) work2(); // Subtask2
	else work3(); // subtask 3
	return 0;
}
```

---

## 作者：jinhangdong (赞：1)

# Subtask 1 
$n\le30$ 直接搜索。
# Subtask 2
$w_i\le1000$ 我们可以用 $01$ 背包，但是 $01$ 背包的时间复杂度是 $O(nW)$，而这里的 $W$ 很大怎么办呢？

我们发现如果把所有的物品都放进背包最大的体积也就是$\displaystyle\sum_{i=1}^{n}w_i$，所以我们背包的容量在 $W$ 和 $\displaystyle\sum_{i=1}^{n}w_i$ 取最小值即可，现在就成普通的 $01$ 背包了。
# Subtask 3
$v_i\le1000$ 这个时候我们就要换一个方法了，定义 $dp_i$ 表示价值为 $i$ 时至少需要多少的背包容量，答案就是能满足 $dp_i\le W$ 的最大的 $i$。

最后附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,v,ans,sum;
int c[205],w[205],dp[200005];
bool flag1,flag2;
void dfs(int x,int s,int t)
{
	if(s>v) return;//当前的重量超出背包容量 
	if(x==n+1)
	{
		ans=max(ans,t);
		return;
	}
	dfs(x+1,s,t);//不选这个物品 
	dfs(x+1,s+w[x],t+c[x]);//选这个物品 
}
signed main()
{
	cin>>n>>v;
	for(int i=1;i<=n;++i)
	{
		cin>>c[i]>>w[i];
		if(w[i]>1000) flag1=1;//不是Subtask 2  
		if(c[i]>1000) flag2=1;//不是Subtask 3 
	}
	if(flag1&&flag2)//不是 Subtask 2也不是Subtask 3，那就只能是Subtask 1了 
	{
		dfs(1,0,0);
		cout<<ans<<endl;
		return 0;
	}
	if(!flag1)//是Subtask 2 
	{
		for(int i=1;i<=n;++i) sum+=w[i];//计算w[i]的总和 
		for(int i=1;i<=n;++i)
		for(int j=min(v,sum);j>=w[i];--j) dp[j]=max(dp[j],dp[j-w[i]]+c[i]);//普通的01背包 
		cout<<dp[min(v,sum)]<<endl;
		return 0;
	}
	if(!flag2)//是Subtask 3
	{
		memset(dp,0x3f,sizeof(dp));//因为要求最小值，所以要初始化最大值 
		dp[0]=0;
		for(int i=1;i<=n;++i) sum+=c[i];//计算c[i]的总和 
		for(int i=1;i<=n;++i)
		for(int j=sum;j>=c[i];--j) dp[j]=min(dp[j],dp[j-c[i]]+w[i]);
		for(int i=sum;i>=0;--i)//找到最大的价值 
		if(dp[i]<=v)
		{
			cout<<i<<endl;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：_AyachiNene (赞：1)

# 思路：
直接分类讨论。

对于 $n\leq30$ 的，显然直接爆搜就行了。

对于 $v_i\leq1000$ 的，显然就是普通的零一背包。

对于 $w_i\leq1000$ 的部分就不是那么简单了，普通零一背包的状态定义显然不行，需要重新定义状态。因为装的价值相同时，当前的体积越小肯定是更优的，这也才能装更多的东西。所以定状态 $dp_i$ 就表示当前价值为 $i$，最小的体积是多少，最后在合法解中取最小值就行了。
# Code：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int res=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		res=(res<<1)+(res<<3)+(c^48);
		c=getchar();
	}
	return res*f;
}
ll n,m,w[114514],v[114514];
int flagv=1,flagw=1;
ll ans;
ll dp[1145141];
void dfs(int x,ll sumw,ll sumv)
{
	if(x>n)
	{
		ans=max(ans,sumw);
		return;
	}
	if(v[x]<=sumv)
		dfs(x+1,sumw+w[x],sumv-v[x]);
	dfs(x+1,sumw,sumv);
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		w[i]=read(),v[i]=read();
		if(v[i]>1000)
			flagv=0;
		if(w[i]>1000)
			flagw=0;
	}
	if(!flagv&&!flagw)  //subtask1
		dfs(1,0,m);
	else if(flagv)   //subtask3
	{
		for(int i=1;i<=n;i++)
			for(int j=m;j>=v[i];j--)
				dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
		for(int i=1;i<=m;i++)
			ans=max(ans,dp[i]);
	}
	else  //subtask2
	{
		memset(dp,0x3f,sizeof dp);
		dp[0]=0;
		for(int i=1;i<=n;i++)
			for(int j=200000;j>=w[i];j--)
				dp[j]=min(dp[j],dp[j-w[i]]+v[i]);
		for(int i=1;i<=200000;i++)
			if(dp[i]<=m)
				ans=i;
	}
	cout<<ans<<endl;//记得换行
}
```


---

## 作者：lylcpp (赞：0)

## 思路

### subtask1

直接暴力搜索即可。

### subtask2

普通的 01 背包，直接 $dp$ 即可。

### subtask3

改变 $dp$ 的状态，设 $dp_i$ 表示价值为 $i$ 时用的最小体积，那么就直接在里面找最小值就行。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

typedef long long ll;
const int N = 200005;
ll n, W, v[N], w[N];
bool A = 1, B = 1;
ll dp[N];
ll ans;

void dfs(int x, ll sp, ll sum) {
	if (x > n) {
		ans = max(ans, sum);
		return ;
	}
	if (w[x] <= sp) 
		dfs(x + 1, sp - w[x], sum + v[x]);
	dfs(x + 1, sp, sum);
}

int main() {
	scanf("%lld%lld", &n, &W);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld", &v[i], &w[i]);
		if (w[i] > 1000) A = 0;
		if (v[i] > 1000) B = 0;
	}	
	if (!A && !B) {
		dfs(1, W, 0);
		printf("%lld\n", ans);
	}
	else if (A) {
		for (int i = 1; i <= n; i++) {
			for (int j = W; j >= w[i]; j--) 
				dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
		for (int i = 1; i <= W; i++)
			ans = max(ans, dp[i]);
		printf("%lld\n", ans);
	}
	else {
		memset(dp, 0x3f, sizeof(dp));
		dp[0] = 0;
		long long sumv = 0;
		for (int i = 1; i <= n; i++)
			sumv += v[i];
		for (int i = 1; i <= n; i++) {
			for (int j = 200000; j >= v[i]; j--) {
				dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
			}
		}
		for (int i = 1; i <= 200000; i++)
			if (dp[i] <= W)
				ans = i;
		printf("%lld\n", ans);
	}
	return 0;
}
``````

---

## 作者：cjh_trailblazer (赞：0)

## 前言：
练 dp 时刷到了这道题，码篇题解，
## 题目分析：
很有意思一道题，因为它要根据不同数据范围选择不同算法。

前两档不用多说，一个暴搜，一个普通 01 背包。

最后 $w_i\le 1000$ 这一档需要优化背包，有一个经典套路，就是说将体积变为价值，用 $f_i$ 表示体积为 $i$ 时的最大价值换成价值为 $i$ 时的最小体积即可。
## [Code](https://atcoder.jp/contests/abc032/submissions/60427565)

---

## 作者：_Kenma_ (赞：0)

# abc032d 解题报告

## 前言

三合一题。

很好地考察了选手的背包 DP 基本功。

## 思路分析

### Subtask 1

注意到 $n$ 很小，暴搜剪剪就能过。

一些剪枝策略：

- 按 $w_{i}$ 由大到小排序，如果大的在之前无法满足，现在就不用考虑了；

- 体积大于背包容量的不用考虑；

- 如果背包容量很大，考虑能不能全选。

复杂度 $O(\text 能过)$。

跑的飞快。

### Subtask 2

发现背包容量上界为 $\sum_{i=1}^{n} w_{i}$，再大就可以全选。

所以可以直接 01 背包。

复杂度最劣 $O(n^{2}w)$。

### Subtask 3

经典 trick。

发现体积无法记录进状态里，考虑状态记录价值。

设 $f_i$ 表示装价值为 $i$ 的物品，所需的最小容量为多少。

转移也是直接 01 背包。

答案为 $\max_{i=0} i,f_{i}\le m$。

复杂度 $O(n^{2}v)$。

## 代码实现

数据点分治。

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,w[205],v[205],f[200005];
int dfn[205];
bool cmp(int x,int y){
	return w[x]>w[y];
} 
bool flag;
int ans;
void dfs(int sumw,int sumv,int lst){
	if(sumw>m) return;
	ans=max(ans,sumv);
	if(sumw==m || lst==n) return;
	for(int i=lst+1;i<=n;i++){
		dfs(sumw+w[dfn[i]],sumv+v[dfn[i]],i);
	} 
}
void solve1(){
	int sum=0,tot=0;
	for(int i=1;i<=n;i++){
		dfn[i]=i;
	} 
	sort(dfn+1,dfn+1+n,cmp);
	for(int i=1;i<=n;i++){
		sum+=w[i];
		tot+=v[i];
	}
	if(sum<=m){
		cout<<tot<<endl;
		exit(0);
	}
	while(w[dfn[n]]>m) n--;
	dfs(0,0,0);
	cout<<ans<<endl;
}
void solve2(){
	int sum=0,ans=0;
	for(int i=1;i<=n;i++){
		sum+=w[i];
		ans+=v[i];
	}
	if(sum<=m){
		cout<<ans<<endl;
		exit(0);
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=w[i];j--){
			f[j]=max(f[j],f[j-w[i]]+v[i]);
		}
	}
	cout<<f[m]<<endl; 
}
void solve3(){
	int sum=0,ans=0;
	for(int i=1;i<=n;i++){
		sum+=v[i];
	}
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=sum;j>=v[i];j--){
			f[j]=min(f[j],f[j-v[i]]+w[i]);
		}
	}
	for(int i=0;i<=sum;i++){
		if(f[i]<=m) ans=max(ans,i);
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	flag=true;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w[i];
		if(w[i]>1000) flag=false;
	}
	if(n<=30) solve1();
	else if(flag) solve2();
	else solve3();
}

```

## 后记

写一写可以锻炼基本功。

---

## 作者：HyB_Capricornus (赞：0)

### Subtask 1:

暴力 dfs。

### Subtask 2:

经典 01 不说了。

### Subtask 3:

$dp_{i,j}$ 前 $i$ 个价值 $j$ 的最小代价，转移如下：

$$
dp_{i,j}=dp_{i-1,j-v_i} + w_i
$$

最后找到：

$$
\max_{dp_{n,i} \le T} i
$$

~~所以说又是一个板子题~~

code:

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
int n,m,w[310],v[310];
int dp[200005],maxx;
void dfs(int u,int size,int value) {
	if (size>m) return;
	if (u==n+1) {
		maxx=max(maxx,value);
		return;
	}
	dfs(u+1,size,value);
	dfs(u+1,size+w[u],value+=v[u]);
}
void solve1(void) {
	dfs(1,0,0);
	cout << maxx;
	return;
}
void solve2(void) {
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for (int i=1;i<=n;i++)
		for (int j=200000;j>=v[i];j--)
			dp[j]=min(dp[j],dp[j-v[i]]+w[i]);
	for (int j=200000;j>=1;j--) {
		if (dp[j]<=m) {
			cout << j;
			return;
		}
	}
}
void solve3(void) {
	dp[0]=0;
	for (int i=1;i<=n;i++) {
		for (int j=m;j>=w[i];j--) {
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
		} 
	}
	cout << dp[m];
	return;
}
signed main(void) {
	cin >> n >> m;
	int maxw=-1e5,maxv=-1e5;
	for (int i=1;i<=n;i++) cin >> v[i] >> w[i],maxw=max(maxw,w[i]),maxv=max(maxv,v[i]);
	if (maxw<=1000) solve3();
	else if (maxv<=1000) solve2();
	else solve1(); 
	cout << endl;
	return 0;
}
```

---

