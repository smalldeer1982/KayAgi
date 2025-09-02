# Boss, Thirsty

## 题目描述

Pak Chanek的一个朋友在食堂经营一个饮料摊位。他的朋友将在 $n$ 天内出售饮料，从第1天到第 $n$ 天。总共有 $m$ 种饮料，编号从1到 $m$。

在某一天出售某种饮料所能获得的利润会有所不同。在第 $i$ 天，出售第 $j$ 种饮料的预期利润是 $A_{i, j}$。请注意，$A_{i, j}$ 可能是负数，这意味着出售这种饮料实际上会造成亏损。

Pak Chanek想帮助他的朋友规划这 $n$ 天的销售。在第 $i$ 天，Pak Chanek必须选择至少出售一种类型的饮料。此外，在同一天出售的饮料类型必须形成一个子数组。换句话说，在每一天，Pak Chanek将选择 $i$ 和 $j$，满足 $1 \leq i \leq j \leq m$。然后，从第 $i$ 个到第 $j$ 个（包括两端）的所有类型的饮料都将被出售。

但是，为了确保前一天的顾客能继续光顾，第 $i$ 天（$i>1$）出售的饮料类型选择必须满足以下条件：

- 第 $i$ 天至少有一种饮料类型也必须在第$i-1$ 天出售。
- 第 $i$ 天至少有一种饮料类型不能在第 $i-1$ 天出售。

每日利润是当天出售的所有饮料类型利润的总和。销售计划的总利润是 $n$ 天内利润的总和。如果Pak Chanek能够优化销售计划，那么他能获得的最大总利润是多少？

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2021D/7f3c895e123ba63a87bc7e1148e98588d4bb8d72.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2021D/4913b558091cf536ad505f423605a117c6964776.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2021D/1e52a9ae8bab076a8dbab9525e40f8a26b2cd856.png)
以下是Pak Chanek的最优计划：

- 在第1天，Pak Chanek出售第1到3种饮料。获得利润 $79+20+49 = 148$。
- 在第2天，Pak Chanek出售第2到4种饮料。获得利润 $9+109+24 = 142$。
- 在第3天，Pak Chanek出售第1到6种饮料。获得利润 $185$。

因此，Pak Chanek计划的总利润是 $148 + 142 + 185 = 475$。

## 样例 #1

### 输入

```
1
3 6
79 20 49 5 -1000 500
-105 9 109 24 -98 -499
14 47 12 39 23 50```

### 输出

```
475```

# 题解

## 作者：Linge_Zzzz (赞：12)

# Descr

给你一个 $n\times m$ 的矩阵 $a$，表示在第 $i$ 天卖第 $j$ 种饮料可以获得 $a_{i,j}$ 单位的利润。

每一天你可以选择一段连续的饮料来售卖，特别的，对于第 $i(i>1)$ 天售卖的饮料，至少要售卖一种前一天售卖过的饮料，而且要至少售卖一种前一天没有售卖过的饮料。

一共有 $n$ 天，最大化这 $n$ 天的利润之和。

$nm\leq 2\times 10^5,-10^9\leq a_{i,j}\leq 10^9$。

# Sol

考虑 DP，设 $f_{i,l,r}$ 表示第 $i$ 天选择了 $[l,r]$ 内的饮料，转移显然，但是状态数太多过不了。

## 观察性质

可以发现，如果固定第 $i$ 天的左端点，那么只要右端点包括前一天的左端点就行，前一天的右端点实际上对第 $i$ 天的右端点选择没有影响。

## 状态设计

也就是说，我们可以设 $f_{i,j,0/1}$ 表示前 $i$ 天，第 $i$ 天选择的端点为 $j$，$0$ 为左端点，$1$ 为右端点的最大利润，这样能包含所有对答案有可能有贡献的情况。

## 考虑转移

考虑如何转移。设第 $i$ 天选择区间为 $[l,r]$，第 $i-1$ 天选择区间为 $[l',r']$，一共有如下四种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/gruoci03.png)

### 情况一

有 $l<l'$，即已经保证了第 $i$ 天选第 $l$ 种饮料而第 $i-1$ 天不选。

我们考虑从 $f_{i-1,l',0}$ 向 $f_{i,l,0}$ 转移，此时必须有 $r\geq l'$，因为至少选一个相同的，那么有：

$$ f_{i,l,0}=\max_{l'=l+1}^m\{f_{i-1,l',0}+val_1(l,l')\} $$

其中 $val_1(l,l')$ 表示固定左端点为 $l$，右端点 $\geq l'$ 所能选的区间中利润和最大的区间，设 $s$ 为 $a_i$ 的前缀和，也就是：

$$
\begin{aligned}
val_1(l,l')&=\max_{j=l'}^m\{s_j-s_{l-1}\}\\
&=\max_{j=l'}^m\{s_j\}-s_{l-1}
\end{aligned}
$$

可以对 $s$ 做一个后缀 $\max$ 来 $O(1)$ 求出，而上面的转移式也可以通过后缀 $\max$ 来做到 $O(1)$ 转移。

### 情况二

有 $l=l'$，即已经满足了第 $i$ 天选第 $l$ 中饮料，第 $i-1$ 天也选。

此时不能再从 $f_{i-1,l',0}$ 来转移，因为我们需要至少包含一个前一天没选的饮料，而固定前一天的左端点使得我们不知道右端点在哪里，所以我们考虑从 $f_{i-1,r',1}$ 来转移。为了包含一个前一天没选的饮料，此时必然有 $r>r'$，则有：

$$f_{i,l,0}=\max_{r'=l}^m\{f_{i-1,r',1}+val_1(l,r'+1)\}$$

同样可以优化到 $O(1)$ 转移。

### 情况三、四

同理于情况一、二，这里列出转移方程。

$$
\begin{aligned}
f_{i,r,1}&=\max_{r'=1}^{r-1}\{f_{i-1,r',1}+val_2(r',r)\}\\
f_{i,r,1}&=\max_{l'=2}^{r}\{f_{i-1,l',0}+val_2(l'-1,r)\}
\end{aligned}
$$

其中 $val_2(l,r)$ 表示固定右端点为 $r$，左端点 $\leq l$ 的所有区间的最大利润，也就是说：

$$
\begin{aligned}
val_2(l,r)&=\max_{j=1}^l\{s_r-s_{j-1}\}\\
&=s_r-\min_{j=1}^l\{s_{j-1}\}
\end{aligned}
$$

可以使用前缀 $\min$ 做到 $O(1)$ 查询，上面的两个式子也能做到 $O(1)$ 转移。

综上所述，我们所有的转移只需要 $O(1)$，所以时间复杂度为 $O(nm)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
void solve(){
	int n,m;
	cin>>n>>m;
	vector<vector<int> >a(n+10,vector<int>(m+10));
	vector<vector<int> >f[2];
	f[0]=f[1]=vector<vector<int> >(n+10,vector<int>(m+10,-INF));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	vector<int> s(m+10,0);
	for(int j=1;j<=m;j++)s[j]=s[j-1]+a[1][j];
	int mx=-INF;
	for(int l=m;l>=1;l--){
		mx=max(mx,s[l]);
		f[0][1][l]=mx-s[l-1];
	}
	int mn=INF;
	for(int r=1;r<=m;r++){
		mn=min(mn,s[r-1]);
		f[1][1][r]=s[r]-mn;
	}
	for(int i=2;i<=n;i++){
		vector<int> s(m+10,0);
		for(int j=1;j<=m;j++)s[j]=s[j-1]+a[i][j];
		int mx,mxs,mns;
		mx=mxs=-INF;
		for(int l=m;l>=1;l--){
			if(l+1<=m)mxs=max(mxs,s[l+1]);
			mx=max(mx,f[0][i-1][l+1]+mxs);
			f[0][i][l]=max(f[0][i][l],mx-s[l-1]);
		}
		mx=mxs=-INF;
		for(int l=m;l>=1;l--){
			if(l+1<=m)mxs=max(mxs,s[l+1]);
			mx=max(mx,mxs+f[1][i-1][l]);
			f[0][i][l]=max(f[0][i][l],mx-s[l-1]);
		}
		mx=-INF,mns=INF;
		for(int r=1;r<=m;r++){
			if(r-2>=0)mns=min(mns,s[r-2]);
			mx=max(mx,f[0][i-1][r]-mns);
			f[1][i][r]=max(f[1][i][r],mx+s[r]);
		}
		mx=-INF,mns=INF;
		for(int r=1;r<=m;r++){
			if(r-2>=0)mns=min(mns,s[r-2]);
			mx=max(mx,f[1][i-1][r-1]-mns);
			f[1][i][r]=max(f[1][i][r],mx+s[r]);
		}
	}
	int ans=-INF;
	for(int i=1;i<=m;i++)ans=max({ans,f[0][n][i],f[1][n][i]});
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：cyc001 (赞：2)

场上并不知道 D < E2，于是没开，错过大好过 D 机会 /ll。

首先有一个非常简单的 DP，定义 $f(i,l,r)$ 表示第 $i$ 行选择了 $[l,r]$ 的饮料，直接枚举下一行的转移，这个 DP 显然复杂度爆炸。

这个状态没有前途，考虑优化状态。

容易发现这一行的区间合法当且仅当上一行的区间至少有 $1$ 个端点被包含在当前区间内（且不含两端）或者仅在端点处有交，这启发我们把状态修改为 $f(i,p,0/1)$ 表示第 $i$ 行的左/右端点在 $p$ 的最大价值。

转移在行内跑一个 DP 就可以了，注意第 $1$ 行要特殊处理，因为第 $1$ 行选的区间长度可以为 $1$。

```cpp
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;
        vector a(n,vector<lint>(m));
        for(auto&x:a) for(auto&i:x) cin>>i;
        vector f(m,vector<lint>(2));
        auto init=[&](int r){
            ranges::fill(f,vector(2,-_infl));
            [&](){
                auto h=0ll;
                cir(i,0,m){
                    h=h+a[r][i];
                    f[i][1]=h;
                    h=max(h,0ll);
                }
            }();
            [&](){
                auto h=0ll;
                for(auto i=m-1;~i;--i){
                    h=h+a[r][i];
                    f[i][0]=h;
                    h=max(h,0ll);
                }
            }();
        };
        auto update=[&](int r){
            const auto g=f;
            ranges::fill(f,vector(2,-_infl));
            [&](){
                vector h(2,-_infl);
                cir(i,0,m){
                    h[0]+=a[r][i];
                    h[1]+=a[r][i];
                    f[i][1]=g[i][0]+h[0];
                    f[i][1]=max(f[i][1],h[1]);
                    h[1]=max({h[1],h[0]+g[i][0],h[0]+g[i][1],g[i][1]+a[r][i]});
                    h[0]=max(h[0],a[r][i]);
                }
            }();
            [&](){
                vector h(2,-_infl);
                for(auto i=m-1;~i;--i){
                    h[0]+=a[r][i];
                    h[1]+=a[r][i];
                    f[i][0]=g[i][1]+h[0];
                    f[i][0]=max(f[i][0],h[1]);
                    h[1]=max({h[1],h[0]+g[i][0],h[0]+g[i][1],g[i][0]+a[r][i]});
                    h[0]=max(h[0],a[r][i]);
                }
            }();
        };
        init(0);
        cir(i,1,n) update(i);
        auto ans=*ranges::max_element(
            *ranges::max_element(f,[&](auto&a,auto&b){
                return *ranges::max_element(a)<*ranges::max_element(b);
            })
        );
        println("{}",ans);
    }();
    return 0;
}

```

---

## 作者：baoyangawa (赞：2)

# part 1. 状态设计


若第 $i-1$ 天选择的区间为 $[L, R]$，则第 $i$ 天的选择 $[l, r]$ 至少满足以下两个条件之一：

- $l < L \le r$
- $l \le R < r$

也就是说，覆盖左端点并至少向左超出一个，或者覆盖右端点并至少向右超出一个。

于是，我们设计一个关于**左右端点**的状态：

- $f_{i, j}$ 为第 $i$ 行，区间**左**端点位于 $j$，前 $i$ 行的最大价值；
- $g_{i, j}$ 为第 $i$ 行，区间**右**端点位于 $j$，前 $i$ 行的最大价值。

对于第一行特殊处理，因为第一行可以选择长度为 $1$ 的区间。

对于第 $i > 1$ 行，我们做如下转移：

- 枚举区间 $[l, r]$，满足 $l < r$；

- 计算 $V = \max \Big((\max\limits_{p=l+1}^{r} f_{i-1,p}), (\max\limits_{p=l}^{r-1}g_{i-1,p})\Big) + \operatorname{sum}(l, r)$，容易证明这样能取遍符合条件的，$i-1$ 行区间的选择。其中 $\operatorname{sum}(l, r)$ 为第 $i$ 行，第 $l$ 到第 $r$ 列的和。

- 用 $V$ 更新 $f_{i,l}$ 和 $g_{i,r}$。

暴力枚举 $p$ 可以做到 $O(nm^3)$，加上一点前缀和优化可以做到 $O(nm^2)$。

# Part2. 优化

我们单拎出来 $f_{i, j}$ 的转移。

$$f_{i,j} = \max_{k=j+1}^{m}\Bigg(s_k - s_{j-1} + \max\Big((\max_{p=j + 1}^{k}f_{i-1,p}), (\max_{p=j}^{k-1}g_{i-1,p})\Big)\Bigg)$$

考虑对这个式子优化。

$$f_{i,j} =- s_{j-1} + \max\Bigg(
\Big(\max_{k=j+1}^{m}(s_k + \max_{p=j + 1}^{k}f_{i-1,p})\Big), 
\Big(\max_{k=j+1}^{m}(s_k + \max_{p=j}^{k-1}g_{i-1,p})\Big)
\Bigg)$$

尝试把关于 $p$ 的枚举，上下标统一：

$$f_{i,j} =- s_{j-1} + \max\Bigg(

{\color{red}\max_{k=j+1}^{m}(s_k + f_{i-1,k})}, 

{\color{blue}\max_{k=j+1}^{m}(s_k + g_{i-1,j})},

{\color{green}\max_{k=j+1}^{m} (s_k + \max_{p=j+1}^{k-1}\max(f_{i-1,p}, g_{i-1,p}))  }

\Bigg)$$

考虑在 $j$ 从右往左扫的过程中，红蓝两部分可以直接维护，问题就在于绿色部分。

实际上绿色部分中内层 $\max$ 还可以往外提：

$$\max_{k=j+1}^{m} \max_{p=j+1}^{k-1}(s_k + \max(f_{i-1,p}, g_{i-1,p}))$$

更换枚举顺序：

$$\max_{p=j+1}^{m-1} \max_{k=p+1}^{m}(s_k + \max(f_{i-1,p}, g_{i-1,p}))$$

然后就可以把 $\max(f_{i-1,p},g_{i-1,p})$ 提出去：

$$\max_{p=j+1}^{m-1} \Big(\max(f_{i-1,p}, g_{i-1,p}) + \max_{k=p+1}^{m}s_k \Big)$$

然后就会发现，$j$ 向左移动到 $j-1$ 时，只会增加如下贡献：

$$\max(f_{i-1,j}+g_{i-1,j}) + \max_{k=j}^{m}s_k$$

这东西只需要维护 $s_k$ 的后缀最大值，就可以 $O(1)$ 计算了。

对于 $g$ 的转移，可以考虑直接把一行翻转，就能和 $f$ 一样转移了。

总时间复杂度 $O(nm)$。

[提交记录](https://codeforces.com/contest/2021/submission/284773803)。代码中使用 `red` 等变量名表示这里转移式中不同颜色的贡献。

---

## 作者：ddxrS_loves_zxr (赞：2)

先考虑一个朴素的 dp，设 $dp_{i,l,r}$ 表示在第 $i$ 行取了第 $l$ 列到第 $r$ 列之间的饮料的最大利润。

令 $sum_i,j$ 表示 $\sum_{k=1}^j a_{i,k}$，有转移 $dp_{i,l,r}=\max(dp_{i-1,L,R}+sum_{r}-sum_{l-1})$ 其中 $L,R$ 满足 $l<L\le r$ 或 $l\le R<r$。

直接转移复杂度直接起飞，考虑优化。可以发现，上面 dp 的转移 $L,R$ 的限制只需要满足其一即可。于是设 $dpL_{i,l}$ 表示在第 $i$ 行固定左端点为 $l$ 而右端点随便的最大利润，同理定义 $dpR_{i,r}$ 为在第 $i$ 行固定右端点为 $r$ 而左端点随便的最大利润。

先考虑 $dpR$ 的转移:

$$
dpR_{i,r}=sum_{i,r}+\max\{\max_{k=1}^i(dpL_{i-1,k}-\min_{p=1}^{k-1}sum_{i,p}),\max_{k=1}^{i-1}(dpR_{i-1,k}-\min_{p=1}^{k}sum_{i,p})\}
$$

转移时通过记录前缀最小值和最大值来转移。

而 $dpL$ 的转移时同理的，可以通过维护后缀最大值来优化。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, m;
int turn(int x, int y) {return x * (m + 1) + y;}
ll a[400005], sum[400005], dpL[400005], dpR[400005];
void solve() {
	ll ans = -inf;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		sum[turn(i, 0)] = 0;
		for(int j = 1; j <= m; j++) scanf("%lld", &a[turn(i, j)]), sum[turn(i, j)] = sum[turn(i, j - 1)] + a[turn(i, j)];
	}
	ll minn = inf; for(int i = 1; i <= m; i++) minn = min(minn, sum[turn(1, i - 1)]), dpR[turn(1, i)] = sum[turn(1, i)] - minn;
	minn = -inf; for(int i = m; i >= 1; i--) minn = max(minn, sum[turn(1, i)]), dpL[turn(1, i)] = minn - sum[turn(1, i - 1)];
	for(int i = 2; i <= n; i++) {
		ll minn = inf, tot = -inf; for(int j = 1; j <= m; j++) {
			tot = max(tot, dpL[turn(i - 1, j)] - minn);
			dpR[turn(i, j)] = tot + sum[turn(i, j)];
			minn = min(minn, sum[turn(i, j - 1)]);
			tot = max(tot, dpR[turn(i - 1, j)] - minn); 
		}
		minn = -inf, tot = -inf; for(int j = m; j >= 1; j--) {
			tot = max(tot, dpR[turn(i - 1, j)] + minn);
			dpL[turn(i, j)] = tot - sum[turn(i, j - 1)];
			minn = max(minn, sum[turn(i, j)]);
			tot = max(tot, dpL[turn(i - 1, j)] + minn); 
		}
	}
	for(int j = 1; j <= m; j++) ans = max(ans, max(dpL[turn(n, j)], dpR[turn(n, j)]));
	printf("%lld\n", ans);
}
int main() {
	int t; cin>>t;
	while(t--) solve(); 
	return 0;
}
```

---

## 作者：Xy_top (赞：1)

少了一个 ``corner case`` 和两个初始化，调了半个小时，不敢想象没有 CF 数据的后果，所以对拍真的很重要。

假设上一次选的区间是 $[a, b]$，什么样的区间 $[c,d]$ 是合法的呢？显然，要么 $c < a$ 并且 $d\geq a$，或者 $c \leq b$ 并且 $d>b$。

两个条件都只与区间的某一个端点有关，这就启发我们分别关心左端点与右端点。

事实也是这样的。可以先枚举上一次的左端点 $a$，还要预处理向左最大子段和的左端点 $l$。（右端点是 $a - 1$），此时本轮所选区间的右端点 $r$ 只要 $\geq a$，$[l,r]$ 就有可能成为这一行以 $r$ 为右端点的最大利润，值为 $sum_{l,r}+ansl_{a}$，其中 $ansl_x$ 表示上一轮以 $x$ 为左端点的最大利润。

同时，也要预处理向右最大子段和的右端点 $r$，（左端点是 $a$），此时对于每个本轮所选区间的左端点 $l$，只要 $<a$，$[l,r]$ 就有可能成为这一行以 $l$ 为左端点的最大利润，值为 $sum_{l,r}+ansl_{a}$。

对于枚举右端点的操作是同理的。

这样直接做就会有 $n^2$ 个区间，但是每一轮的区间拥有相同的左端点，我们可以打标记，然后将区间和转换为前缀和相减，就是一个前后缀最值的问题了。

方法挺难想的，当时先想怎么求只到当前这一行的最大答案，然后发现枚举左右端点将两段最大子段和拼起来的办法。后来考虑以每个位置为端点的答案，才想到截掉一部分的做法。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
/*
流程，预处理最大子段和，通过上一次的答案打标记
然后将标记算出即可。
*/
int n, m;
vector <int> v[200005], sum[200005];
int prel[200005], prer[200005];//前后缀数组，用于打标记
int maxl[200005], maxr[200005], posl[200005], posr[200005];//最大子段和
int ansl[200005], ansr[200005];//以某个点为 左/右 端点的最大答案。（上一行）
void clear () {
	For (i, 1, n) {
		v[i].clear ();
		sum[i].clear ();
	}
	For (i, 1, m) prel[i] = prer[i] = maxl[i] = maxr[i] = posl[i] = posr[i] = ansl[i] = ansr[i] = 0;
}
void solve () {
	cin >> n >> m;
	clear ();
	For (i, 1, n) {
		v[i].push_back (0);
		sum[i].push_back (0);
		For (j, 1, m) {
			int x;
			cin >> x;
			v[i].push_back (x);
			sum[i].push_back (x + sum[i].back () );
		}
	}
	For (i, 1, n) {
		int s = 0, loc = 1;
		For (j, 1, m) {
			s += v[i][j];
			maxr[j] = s;
			posr[j] = loc;
			if (s < 0) {s = 0; loc = j + 1;}
		}
		s = 0;
		loc = m;
		foR (j, m, 1) {
			s += v[i][j];
			maxl[j] = s;
			posl[j] = loc;
			if (s < 0) {s = 0; loc = j - 1;}
		}
		prel[m] = -100000000000000000LL;
		prer[1] = 100000000000000000LL;
		For (a, 2, m) {//由于 c 要小于 a，a 不能取到 1
			//左端点在 a 左侧的，右端点都可以取到最大子段和的右端点
			prel[a - 1] = ansl[a] + sum[i][posl[a] ];
			//右端点在 a 右侧的，左端点都可以取到最大子段和的左端点
			prer[a] = sum[i][posr[a - 1] - 1] - ansl[a];
		}
		For (b, 1, m - 1) {//由于 d 要大于
			prel[b] = max (prel[b], ansr[b] + sum[i][posl[b + 1] ]);//prel 被减数，prer 减数
			prer[b + 1] = min (prer[b + 1], sum[i][posr[b] - 1] - ansr[b]);
		}
		/*pre[l]：1 ... m - 1   pre[r]：2 ... m*/
		foR (i, m - 2, 1) prel[i] = max (prel[i], prel[i + 1]);
		For (i, 3, m) prer[i] = min (prer[i], prer[i - 1]);
		For (j, 1, m) {
			ansl[j] = prel[j] - sum[i][j - 1];
			ansr[j] = sum[i][j] - prer[j];
		}
		ansl[m] = ansr[1] = -100000000000000000LL;
		if (i == 1) For (j, 1, m) {
			ansl[j] = max (ansl[j], v[1][j]);
			ansr[j] = max (ansr[j], v[1][j]);
		}
	}
	int ans = -1000000000000000000LL;
	For (i, 1, m) ans = max (max (ans, ansl[i]), ansr[i]);
	cout << ans << '\n';
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) solve ();
	return 0;
}
/*

c < a   d >= a

c <= b  d > b
注意这里的最大子段和至少取一个
*/
```

---

## 作者：Petit_Souris (赞：1)

感觉有点困难，我怎么一上来不会做了。想了好一会儿才发现可以拆开左右端点。

首先有个很幽默的 $\mathcal O(nm^4)$ 的 dp：设 $dp_{i,l,r}$ 表示选到第 $i$ 层，这层选了 $[l,r]$ 的最大收益。转移枚举上一层选了哪个区间。

但是由于有负数的存在，直观感觉没有什么其他比较好的做法了，只能硬优化这个 dp 了。我们先考虑两个区间 $[l,r],[u,v]$ 在什么情况下可以相邻。一个比较好看的充要条件是 $l<u\le r$ **或** $l\le v<r$。两个条件只要满足一个这件事情就非常美妙，这启发我们干脆把左右端点拆开，记 $f_{i,l}$ 表示第 $i$ 层左端点为 $l$ 的最大价值，$g_{i,r}$ 表示第 $i$ 层右端点为 $r$ 的最大价值。转移的时候是否合法只和上一层用到的端点有关，所以我们这样转移统计到的所有方案都是合法的，且一定包含了最大值。

转移的时候有两种想法。以 $f$ 为例，一种是枚举 $r$，另一种是枚举 $u$。枚举 $r$ 的话需要实时维护一个前缀 $\max$ 状物，应该也能单调栈做，但是非常麻烦。在这里枚举 $u$ 是个更明智的选择：

$$f_{i,l}=\max\limits_{u=l+1}^{n}\{f_{i-1,u}+\max\limits_{r=u}^{n}s(i,l,r)\}$$

其中 $s(l,r)$ 表示目前第 $i$ 层中 $[l,r]$ 的和。这种转移的意思就是满足 $l<u\le r$ 这条条件，那么右端点就可以放任不管了。容易发现拆开之后这个转移式可以用前缀和优化。

$f\to g,g\to f,g\to g$ 的转移也是类似的，在此不表。总时间复杂度为 $\mathcal O(nm)$。注意特殊处理一下第一层的情况。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=2e5+9,INF=1e16;
ll T,n,m,a[N],s[N],F[2][N],G[2][N],cur,mx[N],mx2[N];
void solve(){
    n=read(),m=read();
    rep(j,0,m+1)F[0][j]=G[0][j]=0;
    rep(i,1,m)a[i]=read(),s[i]=s[i-1]+a[i];
    ll tmx=INF;
    rep(i,1,m){
        tmx=min(tmx,s[i-1]);
        G[0][i]=s[i]-tmx;
    }
    tmx=-INF;
    per(i,m,1){
        tmx=max(tmx,s[i]);
        F[0][i]=tmx-s[i-1];
    }
    cur=0;
    rep(i,2,n){
        rep(j,0,m+1)F[cur^1][j]=G[cur^1][j]=-INF;
        rep(j,1,m)a[j]=read(),s[j]=s[j-1]+a[j];
        rep(j,0,m+1)mx[j]=mx2[j]=-INF;
        per(j,m,1)mx[j]=max(mx[j+1],s[j]);
        per(j,m,1)mx2[j]=max(mx2[j+1],F[cur][j]+mx[j]);
        rep(j,1,m)F[cur^1][j]=mx2[j+1]-s[j-1];
        rep(j,0,m+1)mx2[j]=-INF;
        per(j,m,1)mx2[j]=max(mx2[j+1],G[cur][j]+mx[j+1]);
        rep(j,1,m)F[cur^1][j]=max(F[cur^1][j],mx2[j]-s[j-1]);
        rep(j,0,m+1)mx[j]=INF,mx2[j]=-INF;
        rep(j,1,m)mx[j]=min(mx[j-1],s[j-1]);
        rep(j,1,m)mx2[j]=max(mx2[j-1],G[cur][j]-mx[j]);
        rep(j,1,m)G[cur^1][j]=mx2[j-1]+s[j];
        rep(j,0,m+1)mx2[j]=-INF;
        rep(j,1,m)mx2[j]=max(mx2[j-1],F[cur][j]-mx[j-1]);
        rep(j,1,m)G[cur^1][j]=max(G[cur^1][j],mx2[j]+s[j]);
        cur^=1;
    }
    ll ans=-INF;
    rep(i,1,m)ans=max({ans,F[cur][i],G[cur][i]});
    write(ans),putchar('\n');
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：ZnPdCo (赞：1)

没想到，唐完了。

> 题目大意：给定 $n\times m$ 的矩阵，每一行选择一个区间，其中第 $i(2\le i\le n)$ 行选择的区间需满足：
>
> - 不是 $i-1$ 行的子集；
> - 与 $i-1$ 行有交。
>
> 求最大值。

考虑 dp，设 $f_{i,j}$ 表示第 $i$ 行，选择的右端点是 $j$ 的最大值，设 $g_{i,j}$ 表示第 $i$ 行，选择的左端点是 $j$ 的最大值。

那么有四种转移方式：

- $f_{i-1}\to f_{i}$；
- $g_{i-1}\to g_{i}$；
- $f_{i-1}\to g_{i}$；
- $g_{i-1}\to f_{i}$。

这里以 $f_{i-1}\to f_{i}$ 举例。

当我们计算 $f_{i,j}$ 时，我们设这一行选择区间 $[k,j]$，定义 $c(l,r)$ 表示第 $i$ 行选择区间 $[l,r]$ 的价值，那么：

$$
f_{i,j}\gets \max_{k\le x < j}(f_{i-1,x}+c(k,j))
$$

如果直接做就是 $O(nm^3)$ 的，还更劣了，所以考虑怎么优化。

设 $S_{i}$ 表示第 $i$ 行的价值前缀和，那么上式就变为：

$$
f_{i,j}\gets S_j+\max_{k\le x < j}(f_{i-1,x}-S_{k-1})
$$

而后面这个式子也很好做，我们设 $\max_{k\le x}(f_{i-1,x}-S_{k-1})$ 为 $d_{i,x}$，那么：

$$
d_{i,x}=f_{i-1,x}+\max_{k\le x} (-S_{k-1})
$$

这个很好维护，那么原本的式子就是：

$$
f_{i,j}\gets S_j+\max_{x < j}d_{i,x}
$$

这个非常好维护。同理我们可以推导到其它情况，如 $g_{i-1}\to f_{i}$ 的情况：

设这一行选择区间 $[k,j]$，定义 $c(l,r)$ 表示第 $i$ 行选择区间 $[l,r]$ 的价值，那么：

$$
f_{i,j}\gets \max_{k< x \le j}(g_{i-1,x}+c(k,j))
$$

同理可以优化，所以本题时间复杂度 $O(nm)$。

```c++
#include <bits/stdc++.h>
#define ll long long
#define inf 1e18
using namespace std;
ll T, n, m;
int main()
{
    cin >> T;
    while (T--) {
        cin >> n >> m;
        vector<vector<ll>> f(n + 1, vector<ll>(m + 2, -inf));
        vector<vector<ll>> g(n + 1, vector<ll>(m + 2, -inf));
        vector<vector<ll>> S(n + 1, vector<ll>(m + 2, 0));
        vector<vector<ll>> G(n + 1, vector<ll>(m + 2, 0));
        vector<vector<ll>> a(n + 1, vector<ll>(m + 2, 0));
        for (int j = 1; j <= m; j++) {
            f[0][j] = g[0][j] = 0;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
                if (i == 1) {
                    f[i][j] = g[i][j] = a[i][j];
                }
                S[i][j] = S[i][j - 1] + a[i][j];
            }
            for (int j = m; j >= 1; j--) {
                G[i][j] = G[i][j + 1] + a[i][j];
            }

            ll pre, suf, mx;
            pre = -inf, mx = -inf;
            for (int j = 1; j <= m; j++) {
                f[i][j] = max(f[i][j], mx + S[i][j]);
                pre = max(pre, -S[i][j - 1]);
                mx = max(mx, f[i - 1][j] + pre);
            }

            suf = -inf, mx = -inf;
            for (int j = m; j >= 1; j--) {
                g[i][j] = max(g[i][j], mx + G[i][j]);
                suf = max(suf, -G[i][j + 1]);
                mx = max(mx, g[i - 1][j] + suf);
            }

            pre = -inf, mx = -inf;
            for (int j = 1; j <= m; j++) {
                mx = max(mx, g[i - 1][j] + pre);
                pre = max(pre, -S[i][j - 1]);
                f[i][j] = max(f[i][j], mx + S[i][j]);
            }

            suf = -inf, mx = -inf;
            for (int j = m; j >= 1; j--) {
                mx = max(mx, f[i - 1][j] + suf);
                suf = max(suf, -G[i][j + 1]);
                g[i][j] = max(g[i][j], mx + G[i][j]);
            }
        }

        ll ans = -inf;
        for (int i = 1; i <= m; i++) {
            ans = max(ans, f[n][i]);
            ans = max(ans, g[n][i]);
        }
        cout << ans << endl;
    }
}
```

---

## 作者：int_R (赞：0)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18452036/CF2021D)

原来就是直接做啊。

记 $s_{i,j}=\sum\limits_{k\leq j} a_{i,k}$，设 $f_{i,x,y}$ 表示第 $i$ 行选区间 $[x,y]$ 的最大答案，有转移：

$$
f_{i,x,y}=s_{i,y}-s_{i,x-1}+\max(\max\limits_{x<l\leq y,r\geq l} f_{i-1,l,r},\max\limits_{x\leq r<y,l\leq r} f_{i-1,l,r})
$$

设 $L_{i,l},R_{i,r}$ 分别表示 $\max\limits_{r\geq l} f_{i,l,r},\max\limits_{l\leq r} f_{i,l,r}$，转移变为：

$$
f_{i,x,y}=s_{i,y}-s_{i,x-1}+\max(\max\limits_{x<l\leq y} L_{i-1,l},\max\limits_{x\leq r<y} R_{i-1,r})
$$

考虑直接求 $L_{i,x},R_{i,y}$

$$
L_{i,x}=\max\limits_{y\geq x} f_{i,x,y}=-s_{i,x-1}+\max(\max\limits_{l>x} (L_{i-1,l}+\max\limits_{y\geq l} s_{i,y}),\max\limits_{r\geq x} (R_{i-1,r}+\max\limits_{y>r} s_{i,y}))
$$

$$
R_{i,y}=\max\limits_{x\leq y} f_{i,x,y}=s_{i,y}+\max(\max\limits_{l\leq y} (L_{i-1,l}-\min\limits_{x<l} s_{i,x-1}),\max\limits_{r<y} (R_{i-1,r}-\min_{x\leq r} s_{i,x-1}))
$$

计算四个括号里的东西即可，注意能否取等，这意味着一些计算的先后顺序。第一行要特殊处理。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
typedef pair<int,int> P;
const int N=2e5+10,INF=1e18;
int T,n,m,s[N],l[N],r[N],a[N],b[N],c[N],d[N];
inline void work()
{
    cin>>n>>m;int ans=-INF;
    for(int j=1;j<=m;++j)
        cin>>s[j],s[j]+=s[j-1];
    for(int j=m,MAX=-INF;j;--j)
        MAX=max(MAX,s[j]),l[j]=MAX-s[j-1];
    for(int j=1,MIN=INF;j<=m;++j)
        MIN=min(MIN,s[j-1]),r[j]=s[j]-MIN;
    for(int i=1;i<n;++i)
    {
        a[m+1]=b[m+1]=c[0]=d[0]=-INF;
        for(int j=1;j<=m;++j)
            cin>>s[j],s[j]+=s[j-1];
        for(int j=m,MAX=-INF;j;--j)
            MAX=max(MAX,s[j]),a[j]=max(a[j+1],l[j]+MAX);
        for(int j=m,MAX=-INF;j;--j)
            b[j]=max(b[j+1],r[j]+MAX),MAX=max(MAX,s[j]);
        for(int j=1,MIN=INF;j<=m;++j)
            c[j]=max(c[j-1],l[j]-MIN),MIN=min(MIN,s[j-1]);
        for(int j=1,MIN=INF;j<=m;++j)
            MIN=min(MIN,s[j-1]),d[j]=max(d[j-1],r[j]-MIN);
        for(int j=1;j<=m;++j)
            l[j]=-s[j-1]+max(a[j+1],b[j]);
        for(int j=1;j<=m;++j)
            r[j]=s[j]+max(c[j],d[j-1]);
    }
    for(int j=1;j<=m;++j) ans=max(ans,l[j]);
    cout<<ans<<'\n';return ;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>T;while(T--) work();return 0;
}
```

---

## 作者：strcmp (赞：0)

**弱化条件：**

同时考虑四个端点怎么选太困难了。

你发现我们后一个区间的开区间，一定包含前一个区间的一个端点，也就是说：

$l' < l < r'$ **或者** $l' < r < r'$ 则 $[l,\,r]$ 的下一个区间可以是 $[l',\,r']$。

这显然是充要的。

然后你发现从这个充要条件入手，问题就弱了很多。

---

考虑设一个 $f_{i,\,j}$ 代表前 $i$ 行，末尾区间以 $j$ 为左端点的所有方案的最大价值和。再设一个 $g_{i,\,j}$ 类似 $f$，代表前 $i$ 行末尾区间以 $j$ 为右端点的最大价值和。

考虑 $f_{i,\,j}$ 的转移：

设 $h_{i,\,j}$ 代表第 $i$ 行第 $j$ 列开头的最大连续子段和，$q_{i,\,j}$ 类似 $h$ 代表以第 $j$ 列**前一个**位置结尾的**最小**连续子段和。$s_{i,\,j}$ 是前缀和。

有转移：

$$
\begin{aligned}
& f_{i,\,j} \leftarrow \max\{ \max\limits_{x > j} f_{i - 1,\,x} + h_{i,\,x},\, \max\limits_{y \ge j} g_{i - 1,\,y} + h_{i,\,y + 1} \} - s_{i,\,j - 1} \\
& g_{i,\,j} \leftarrow \max\{ \max\limits_{x \le j} f_{i - 1,\,x} - q_{i,\,x - 1},\, \max\limits_{y < j} g_{i - 1,\,y} - q_{i,\,y} \} + s_{i,\,j}
\end{aligned}
$$

预处理一下要用到的信息，按照转移顺序递推做即可。

时间复杂度 $\Theta(Tnm)$，可以通过。

注意第一行的转移比较难复用，还需要一点简单讨论。

```cpp
# include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pil = pair<int, ll>;
using ms = multiset<ll>;
const int maxn = 2e5 + 10, mod = 1e9 + 7; const ll inf = 1e18;
int T, n, m; ll f[maxn], g[maxn], s[maxn], a[maxn], b[maxn], c[maxn], d[maxn];
signed main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m); 
		rep(i, 1, m) scanf("%lld", &s[i]), s[i] += s[i - 1]; 
		ll mx = -inf, mi = inf, ans = -inf;
		rep(i, 1, m) mi = min(mi, s[i - 1]), g[i] = s[i] - mi;
		per(i, m, 1) mx = max(mx, s[i]), f[i] = mx - s[i - 1];
		c[0] = d[0] = a[m + 1] = b[m + 1] = -inf;
		rep(i, 2, n) {
			rep(j, 1, m) scanf("%lld", &s[j]), s[j] += s[j - 1];
			mi = inf; rep(j, 1, m) c[j] = max(c[j - 1], f[j] - mi), mi = min(mi, s[j - 1]);
			mi = inf; rep(j, 1, m) mi = min(mi, s[j - 1]), d[j] = max(d[j - 1], g[j] - mi);
			mx = -inf; per(j, m, 1) mx = max(mx, s[j]), a[j] = max(a[j + 1], f[j] + mx);
			mx = -inf; per(j, m, 1) b[j] = max(b[j + 1], g[j] + mx), mx = max(mx, s[j]);
			rep(j, 1, m) f[j] = max(a[j + 1], b[j]) - s[j - 1], g[j] = max(c[j], d[j - 1]) + s[j];
		}
		rep(i, 1, m) ans = max(ans, f[i]);
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

