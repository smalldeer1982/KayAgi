# Tower

## 题目描述

你有 $n$ 个箱子，编号从 $1$ 到 $n$，每个箱子有三个属性，以第 $i$ 个箱子为例，分别是重量 $w_i$，承重能力 $s_i$，价值 $v_i$。

你想建一座塔，因此需要将一些箱子堆叠起来，但是每个箱子必须满足下面的条件：

- 这个箱子上面的所有箱子重量和要小于等于这个箱子的承重能力。

定义一个塔的价值为它所用的所有箱子的价值和。

最大化这个塔的价值并输出它。

## 说明/提示

$n \le 10^3, 1 \le w_i, s_i \le 10^4, 1 \le v_i \le 10^9$。

## 样例 #1

### 输入

```
3
2 2 20
2 1 30
3 1 40```

### 输出

```
50```

## 样例 #2

### 输入

```
4
1 2 10
3 1 10
2 4 10
1 6 10```

### 输出

```
40```

## 样例 #3

### 输入

```
5
1 10000 1000000000
1 10000 1000000000
1 10000 1000000000
1 10000 1000000000
1 10000 1000000000```

### 输出

```
5000000000```

## 样例 #4

### 输入

```
8
9 5 7
6 2 7
5 7 3
7 8 8
1 9 6
3 3 3
4 1 7
4 5 5```

### 输出

```
22```

# 题解

## 作者：RP_INT_MAX (赞：20)

## 前言

这道题是教练给的一道练习题。当时我做了半天大体思路都想出来了然后满江红，现在补一波题解。为保证语言严谨，本篇题解中所有的“重量”都改为“质量”叙述。

在阅读本篇题解之前，请保证你已熟悉以下算法：

- 贪心算法
- 排序算法
- 01 背包问题

[题目传送门，这里不再赘述题面。](https://www.luogu.com.cn/problem/AT_dp_x)

## $\textbf{Solution}$

一眼看出来是 01 背包问题。

由于数据范围的限制，我们不可能硬做 01 背包，~~而欧拉变换也只是针对计数题~~，因此必须考虑优化。

使用贪心的思想。对于两个箱子 $i,j$，第 $i$ 个箱子若要比第 $j$ 个箱子优先考虑，显然应令 $i$ 上方除 $j$ 以外能放的箱子总质量 $s_i-w_j$ 大于 $j$ 上方除 $i$ 以外能放的箱子总质量 $s_j-w_i$。

所以，可以得到比较依据：

$$
s_i-w_j < s_j-w_i
$$

不等式化一下：

$$
s_i+w_i < s_j+w_j
$$

据此，我们先进行排序，再做 01 背包，这样时间复杂度就得以优化，因为对于 $n$ 个箱子可以顺次考虑。我们设 $f_i$ 表示当前质量是 $i$ 时所获得的最大价值，根据 01 背包思路，不难得到转移方程：

$$
f_{j+w_i}=\max\{f_{j+w_i},f_{j}+v_i\}
$$

其中 $1 \le i \le n$，$0 \le j \le s_i$，且 $j$ 倒序枚举（知道 01 背包降维方法的应该都懂为什么）。

注意，应初始化 $f$ 数组为 $-1$，$f_0=0$。

答案 $ans=\max\{f_i\}$。

## $\textbf{Code}$

可以参考，但是不要复制。不加注释了，上文讲得很清楚。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
struct node {
	int w,s,v;
	friend bool operator<(const node&a,const node&b) {
		return a.w+a.s<b.w+b.s;
	}
} a[1010];
int t,n;
ll f[20010];
int main () {
    scanf("%d",&n);
	memset(f,-1,sizeof f);
	for(int i=1;i<=n;++i)
        scanf("%d%d%d",&a[i].w,&a[i].s,&a[i].v);
	sort(a+1,a+1+n),f[0]=0;
	for(int i=1;i<=n;++i)
        for(int j=a[i].s;j>=0;--j)
            f[j+a[i].w]=max(f[j+a[i].w],f[j]+a[i].v);
	ll ans=0;
	for(int i=0;i<=20000;++i) ans=max(ans,f[i]);
    cout<<ans<<endl;
	return 0;
}
```

---

## 作者：MortisM (赞：10)

[题目链接](https://atcoder.jp/contests/dp/tasks/dp_x)

题目大意：有 $n$ 块积木，每块有 3 个属性，$w_i,s_i,v_i$，分别表示这块积木的重量、承受能力和价值。要从中选择一些积木以任意顺序堆成一堆，必须满足一堆中每个积木的承受能力都 $\geq$ 上面所有积木的承受能力，求这一堆的总最大价值。

数据范围：$n\leq 1000,w_i,s_i\leq10^4$。

感觉这题难点在于怎么证明贪心策略？

一眼知道用 `exchange arguments`，考虑怎么贪心。

如果先把 $i$ 放在下面再放 $j$ 还能往上堆 $s_j-w_i$，反之还能堆 $s_i-w_j$。所以若要把 $i$ 放在下面则必须满足 $s_j-w_i<s_i-w_j$，也就是 $w_i+s_i>w_j+s_j$。

下面按 $w_i+s_i$ 从小到大排序完了打个 01 背包跑路。

```cpp
/**
 *	author: Jerry_Jiang
**/

#include <bits/stdc++.h>

#define LOCAL

using namespace std;

const int N = 1e3 + 5, W = 2e4 + 5;

int n;
long long dp[N][W];
struct block {
	int w, s;
	long long v;
	bool operator < (const block &x) const {
		return w + s < x.w + x.s;
	}
} a[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i].w >> a[i].s >> a[i].v;
	}
	sort(a + 1, a + n + 1);
	memset(dp, -0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < W; j++) {
			dp[i][j] = dp[i - 1][j];
			if(j >= a[i].w && j - a[i].w <= a[i].s) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i].w] + a[i].v);
			}
		}
	}
	cout << *max_element(dp[n], dp[n] + W) << '\n';
	return 0;
}
```

---

## 作者：SkyRainWind (赞：5)

做法和其它题解略有不同，来写一发

首先肯定考虑将 $\{w,s,v\}$ 排序，如何排序呢？考虑 $i$ 在 $j$ 上面和下面的时候，还能剩下的空间。

- $i$ 在 $j$ 上：$cap_1=\min(s_i,s_j-w_i)$ 显然就是 $i$ 和 $j$ 的限制都需要满足。
- $i$ 在 $j$ 下：$cap_2=\min(s_j,s_i-w_j)$。

当 $i$ 比 $j$ 更优的时候，$i$ 需要放在 $j$ 前面，也就是在下面，因此此时 $cap_2>cap_1$ 这就是排序的准则。

排完序之后用一个类似背包的写法：$dp_{i,s}$ 表示考虑到前 $i$ 个块，当前剩余容量为 $s$ 的最大价值。转移就考虑是否放当前块：$dp_{i,min(j-w_i,s_i)} \leftarrow dp_{i-1,j}+v_i$。

一个细节：如何判断当前放的块是第一块？首先可以把第二维开大到 20000，这样足够转移的，或者是将一开始不合法的状态都赋成负无穷大，然后每次转移。

这里放第二种写法的代码：

```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define pii pair<int,int>
#define pb push_back

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, maxn=20005;

int n;
struct node{int w,s,v;}a[maxn];
int cmp(node i,node j){return min(j.s,i.s-j.w) > min(i.s,j.s-i.w);}
ll dp[1005][20005];
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].w,&a[i].s,&a[i].v);
	sort(a+1,a+n+1,cmp);
	
	for(int i=0;i<=10000;i++)dp[1][i] = -1e18;
	dp[1][a[1].s] = a[1].v;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=10000;j++)dp[i][j] = dp[i-1][j];
		dp[i][a[i].s] = max(dp[i][a[i].s], 1ll*a[i].v);
		for(int j=a[i].w;j<=10000;j++){
			ll &dd = dp[i][min(j-a[i].w, a[i].s)];
			dd = max(dd, dp[i-1][j] + a[i].v);
		}
	}
	ll ans=0;
	for(int i=0;i<=10000;i++)ans = max(ans, dp[n][i]);
	cout<<ans<<'\n';

	return 0;
}
```

---

## 作者：ZillionX (赞：5)

# Description

有 $n$ 个物品，第 $i$ 个物品有重量 $w_i$、承重能力 $s_i$、价值 $v_i$。要将物品堆成一个塔，满足在每个物品上面的 $\sum w$ 小于该物品的承重能力，最大化塔的价值和。

$n \le 10^3, w_i,s_i \le 10^4, v_i \le 10^9$，时限 2s。

# Solution

显然的 01 背包，一个可观的想法是跑 $n$ 次从前到后的 01 背包，但是时间复杂度为 $\mathcal O(n^2s)$，无法通过本题。

考虑寻找可以贪心的性质，确定物品的顺序。

注意到当 $s_x-w_y>s_y-w_x$，即 $s_x+w_x>s_y+w_y$ 时，先放 $x$ 一定优于先放 $y$。

于是我们按 $s+w$ 为关键字排序，然后直接跑一遍背包。时间复杂度 $\mathcal O(n \log n+n(s+w))$，至此本题被解决。

# Code

```cpp
typedef long long LL;
const int N=1e3+5,V=2e4+5;

int n;
LL f[V],Ans;

struct Data {
	int w,s;
	LL v;
	bool operator<(const Data &x) const {
		return w+s<x.w+x.s;
	}
}p[N];

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d%lld",&p[i].w,&p[i].s,&p[i].v);
	sort(p+1,p+n+1);
	for (int i=1;i<=n;i++)
		for (int j=min(p[i].w+p[i].s,V-5);j>=p[i].w;j--)
			f[j]=max(f[j],f[j-p[i].w]+p[i].v);
	for (int i=V-5;i>=0;i--)
		Ans=max(Ans,f[i]);
	printf("%lld",Ans);
	return 0;
}
```


---

## 作者：activeO (赞：4)

## 题目大意

有 n 个物品，每个物品三个属性：重量 $ w_i $，承重能力 $ s_i $，价值 $ v_i $。现在把他堆成一个塔，堆在上面的箱子的重量和一定得小于下面的承重能力，求这个塔的最大价值。

## 思路

一看到都会想到跑 n 次 01 背包，$ O(n^2s) $，但是很可惜，会 TLE。

所以挖掘一个性质：$ s_i - w_j > s_j - w_i $ 第 i 个箱子放在第 j 个箱子下面就显然更优。所以我们按照这个排序，再跑 1 此背包就行了。

时间复杂度：$ O(n \log n + n \cdot s+n \cdot w) $


## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

typedef long long ll;

const int maxn=2e4+5;
struct node{
	int w,s;
	ll v;
}a[maxn];
ll dp[maxn];

bool cmp(node x,node y){
	return x.w+x.s<y.w+y.s;
}

int main(){
	
	int n;
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d %d %lld",&a[i].w,&a[i].s,&a[i].v);
	
	sort(a+1,a+n+1,cmp);
	
	for(int i=1;i<=n;i++){
		for(int j=min(a[i].s+a[i].w,maxn-5);j>=a[i].w;j--) dp[j]=max(dp[j],dp[j-a[i].w]+a[i].v);
	}
	
	ll ans=0;
	
	for(int i=maxn-5;i>=0;i--) ans=max(ans,dp[i]);
	
	printf("%lld\n",ans);
	
	return 0;
}
```


---

## 作者：happy_zero (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_x)。

这题可以想到用 `01` 背包，但是如果是 `01` 背包的话无法保证方案最优因为加入某一个元素是不能知道放在已有箱子的哪里是最优的。那么我们就可以先找出最优的从上往下顺序后再 `01` 背包。

因为交换相邻两个箱子只有对自身产生影响，所以可以贪心地考虑这两个箱子如何摆最优，而又因为本身上面的总重量不变，所以只用考虑这两个箱子的限制：一上一下的 $x,y$，$x$ 在上面还可放 $s_y-w_x$，$y$ 在上可放 $s_x-w_y$，显然若 $s_y-w_x>s_x-w_y$ 则 $x$ 在上，否则 $y$ 在上，移项一下得 $s_y+w_y>s_x+w_x$ 则 $x$ 在上，于是按 $s+w$ 升序排序，然后每次都把箱子放在最下方即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1005;
const int M = 1e5 + 5;
struct node {
	int w, v, s;
}a[N];
//s[x] - w[y] < s[y] - w[x]
//s[x] + w[x] < s[y] + w[y]
bool cmp(node x, node y) {
	return x.s + x.w < y.s + y.w;
}
int dp[M];
signed main() {
	int n, cnt = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i].w >> a[i].s >> a[i].v;
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; i++)
		for (int j = a[i].w + a[i].s; j >= a[i].w; j--)
			dp[j] = max(dp[j], dp[j - a[i].w] + a[i].v);
	int ans = 0;
	for (int i = 0; i < M; i++)
		ans = max(ans, dp[i]);
	cout << ans;
	return 0;
}
``

---

## 作者：yyz1005 (赞：2)

箱子 $x$ 放在箱子 $y$ 下面时：

若 $S_x-W_y<S_y-W_x$ 则交换必然使得能放置更多箱子。

因此按照 $S_x+W_x$ 从大到小排序，让后就一个 01 背包则可以解决。

因为压缩空间后代码不易理解，所以用的是二维数组。

具体的写法参考注释即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1010;
const ll S = 10010;
//时间复杂度是 O(nS) 的，S 为每个盒子 s 的最大值
ll n,W;
struct box{
	ll w,s,v;
	bool operator <(const box &x) const{
		return s+w>x.s+x.w;//符号不要写错
	}
} r[N];
ll dp[N][S],ans = 0;
/*
dp[i][j]:用排序后前 i 个盒子摆出最上面还可以放上重量 j 的方案最大价值和
*/
int main(){
	scanf("%lld",&n);
	W = 0;
	for(ll i = 1; i <= n; i++){
		scanf("%lld%lld%lld",&r[i].w,&r[i].s,&r[i].v);
		W = max(W,r[i].s);
	}
	sort(r+1,r+n+1);
	for(ll i = 1; i <= n; i++){
		for(ll j = 0; j <= W; j++) dp[i][j] = dp[i-1][j];//先把前一行的拷贝过来，不然会漏情况
		dp[i][r[i].s] = max(dp[i][r[i].s],r[i].v);//只放这一个箱子
		if(i==1) continue;
		for(ll j = W; j >= r[i].w; j--){
			if(dp[i-1][j]==0) continue;
            //存在一种使用排序后前 i-1 个箱子的方案，并且这个方案上面还能放盒子 i
			dp[i][min(r[i].s,j-r[i].w)] = max(dp[i][min(r[i].s,j-r[i].w)],dp[i-1][j]+r[i].v);//放完之后的承重要取最小值
		}
	}
	for(ll i = 1; i <= n; i++){
		for(ll j = 0; j <= W; j++){
			ans = max(ans,dp[i][j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_dp_x)
# 题目描述
存在 $n$ 个箱子，每一个箱子三个参数，质量 $w_{i}$，承受能力 $s_{i}$ 和价值 $v_{i}$。对于每一种放置方法，求其中价值的最大值。
# 题目分析
对于两个箱子 $i$ 和 $j$，如果 $i$ 放在下面，$j$ 放在上面，则 $i$ 上面的重量最多为 $s_{i}-w_{j}$。反之为 $s_{j}-w_{i}$。

如果 $i$ 比 $j$ 优先考虑，则需要满足：$s_{i}-w_{j}<s_{j}-w{i}$。

也就是 $s_{i}+w_{i}<s_{j}+w_{j}$。

根据这个式子，就可以将 `01` 背包计算有序化，时间复杂度就成为 $O(n\log n+n\cdot s+n\cdot w)$。

# 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e3+5;
const int MAXW_S=1e4+1e4+5;
const int inf=1e17+5;
int n,w_s,ans;
int dp[MAXN][MAXW_S];//前 n 个总和为 s
struct node{
    int w;
    int s;
    int v;
}e[MAXN];
bool cmp(node a,node b){return (a.w+a.s)<(b.w+b.s);}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>e[i].w>>e[i].s>>e[i].v,w_s=max(w_s,e[i].w+e[i].s);
    sort(e+1,e+n+1,cmp);
    for(int i=0;i<MAXN;i++)for(int j=0;j<MAXN;j++)
        dp[i][j]=-inf;
    dp[0][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=w_s;j++){
            dp[i][j]=dp[i-1][j];
            if(j>=e[i].w&&e[i].s>=j-e[i].w)
                dp[i][j]=max(dp[i][j],dp[i-1][j-e[i].w]+e[i].v);
        }
    for(int i=1;i<=n;i++)
        for(int j=0;j<=w_s;j++)
            ans=max(ans,dp[i][j]);
    cout<<ans;
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17415541.html)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_x)

## 题目分析

好水的题，秒了。

看到题面就知道是背包，唯一的问题是怎么优化其复杂度。

如果将 $x$ 放于 $y$ 上，那么上面还能堆 $x_s-y_w$ 的东西，反之则能堆 $y_s-x_w$ 的东西，所以若有 $x_s-y_w<y_s-x_w$，则将第 $x$ 个箱子放在第 $y$ 个箱子上更优。

排序完再跑背包即可。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define ok printf("1")
#define no printf("0")
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=2e4+5;
int n;
int ans;
int dp[maxn];
struct node{
	int w,s,v;
}a[maxn];
bool cmp(node x,node y){
	return (x.w+x.s)<(y.w+y.s);
}
inline void init(){
	n=read();
	for(register int i=1;i<=n;++i){
		a[i].w=read();a[i].s=read();a[i].v=read();
	}
	sort(a+1,a+n+1,cmp);
}
signed main(){
	init();
	for(register int i=1;i<=n;++i){
		for(register int j=min(a[i].w+a[i].s,20000LL);j>=a[i].w;--j) dp[j]=max(dp[j],dp[j-a[i].w]+a[i].v);
	}
	for(register int i=1;i<=maxn;++i) ans=max(ans,dp[i]);
	printf("%lld",ans);
}
```

---

