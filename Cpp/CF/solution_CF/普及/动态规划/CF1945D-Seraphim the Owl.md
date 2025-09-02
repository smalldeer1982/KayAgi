# Seraphim the Owl

## 题目描述

The guys lined up in a queue of $ n $ people, starting with person number $ i = 1 $ , to ask Serafim the Owl about the meaning of life. Unfortunately, Kirill was very busy writing the legend for this problem, so he arrived a little later and stood at the end of the line after the $ n $ -th person. Kirill is completely dissatisfied with this situation, so he decided to bribe some people ahead of him.

For the $ i $ -th person in the queue, Kirill knows two values: $ a_i $ and $ b_i $ . If at the moment Kirill is standing at position $ i $ , then he can choose any position $ j $ such that $ j < i $ and exchange places with the person at position $ j $ . In this case, Kirill will have to pay him $ a_j $ coins. And for each $ k $ such that $ j < k < i $ , Kirill will have to pay $ b_k $ coins to the person at position $ k $ . Kirill can perform this action any number of times.

Kirill is thrifty, so he wants to spend as few coins as possible, but he doesn't want to wait too long, so Kirill believes he should be among the first $ m $ people in line.

Help Kirill determine the minimum number of coins he will have to spend in order to not wait too long.

## 样例 #1

### 输入

```
4
4 2
7 3 6 9
4 3 8 5
6 2
6 9 7 1 8 3
5 8 8 1 4 1
7 7
7 2 9 2 6 5 9
9 1 10 7 1 4 9
2 1
2 3
1 1```

### 输出

```
14
22
9
3```

# 题解

## 作者：spfa_ (赞：6)

[CF1945D Seraphim the Owl](https://www.luogu.com.cn/problem/CF1945D)

### 题目翻译

有 $n$ 个人排成一队，每个人有权值 $a_i,b_i$，Kirill 在第 $n+1$ 的位置。若 Kirill 在位置 $i$，与前面的 $j$ 交换位置的代价为 $a_j+\sum_{k=j+1}^{i-1}b_k$，求 Kirill 到 $[1,m]$ 任意位置的最小代价。

### 题目分析

首先可以想到一个显然的 dp：

$$f_i=\min_{i<j}f_j+a_i+\sum_{k=i+1}^{j-1}b_k$$

但是这个 dp 是 $O(n^2)$ 的，考虑优化。

对于一个位置 $i$，我们每次都要求 $[i+1,n]$ 中的最小值，且决策区间只增不减，这令我们联想到单调队列来优化 dp，不会单调队列优化 dp 的可以转到[此题](https://www.luogu.com.cn/problem/P1725)，时间复杂度为 $O(n)$。

当然啦这题也可以用线段树来优化 dp，但是多一个 $\log n$，码量还大，所以能用就用单调队列啦。

[code](https://codeforces.com/contest/1945/submission/252303453)

---

## 作者：ZhaoV1 (赞：4)

# 解析

可以贿赂在你前面的人并且支付给和你换位置的人 $a_i$ 的钱（$i$ 为和你换位置的人的下标），其中你的位置下标是 $j$，那么你还需要分别交 $b_k$ 的钱给夹在下标 $i$ 和 $j$ 中间所有人（$i<k<j$），目标是换到前 $m$ 的位置。

由于可以无限次贿赂他人，所以在 $m$ 到 $n$ 的区间，我们选择对于每个人的最低价格（从 $a_i$ 和 $b_i$ 中选得），而在 $1$ 到 $m$ 的范围，我们维护一个前缀和来存连续区间要上交的 $b_k$ 的价格总和，遍历得到真正要换的位置，上交 $a_i+s_m-s_i$，加上之前算得的价格，于是得到答案。


```cpp
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
const int N = 2e5+5;
int t,m,n;
int a[N], b[N];
int s[N];

void solve(){
	int res = 0;
	cin >> n >> m;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=n;i++) cin >> b[i];
	for(int i=m+1;i<=n;i++) res += min(a[i],b[i]);

	int sum = INF; s[0] = 0;//init
	for(int i=1;i<=m;i++) s[i] = s[i-1] + b[i];
	for(int i=1;i<=m;i++) sum = min(sum,a[i]+s[m]-s[i]);
	res += sum;
	cout << res << '\n';
}
```

---

## 作者：__Floze3__ (赞：4)

## 思路简介

很显然，我们不需要处理在前 $m$ 个位置之外会与哪些位置进行交换，因为我们最终并不会停在那里。因此，在 $m$ 个位置之外的总代价为 $\sum_{k = m + 1}^n \min(a_k, b_k)$。我们只需要考虑选择前 $m$ 个位置中的哪一个位置停留下来即可。

具体而言，我们在统计完第 $m + 1$ 到第 $n$ 个位置的代价之后，我们从 $m$ 开始倒序遍历，计算出在每一个位置停留的最小值，并同时更新不在这个点停留所需的代价即可。

## 代码

```cpp
#include <bits/stdc++.h>
typedef long long ll;
#define read std::cin
#define write std::cout

const int N = 2e5 + 5;

int T, n, m;
ll a[N], b[N];

int main() {
    read >> T;
    while (T--) {
        read >> n >> m;
        for (int i = 1; i <= n; ++i) read >> a[i];
        for (int i = 1; i <= n; ++i) read >> b[i];
        ll res = 0;
        for (int i = n; i > m; --i) res += std::min(a[i], b[i]);
        ll ans = 1e18;
        for (int i = m; i; --i) {
            ans = std::min(ans, res + a[i]);
            res += b[i];
        }
        write << ans << '\n';
    }
    return 0;
}
```

---

## 作者：2huk (赞：3)

有 $n + 1$ 个人站成一排，最开始第 $i$ 个人在位置 $i$ 上。

你是第 $n + 1$ 个人。除你之外，每个人都有两个属性 $a_i, b_i$。

每次操作时，假如你在位置 $i$ 上，那么你需要选择一个位置 $1 \le j < i$ 并和位置 $j$ 的人交换位置。代价为 $a_j + \sum_{k = j + 1}^{i - 1}b_k$。

求若你最终移动到的位置小于等于 $m$，总代价最小是多少。

---

假如我们可以求出 $f_i$ 表示你从 $n + 1$ 到达 $i$ 的最小代价，那么答案即 $\min_{i = 1}^m f_i$。

我们可以画图模拟一下跟前面人交换位置的过程：

![](https://cdn.luogu.com.cn/upload/image_hosting/rdqlhht9.png)

那么答案为蓝色框起的数之和 $3 + 6 + 5 = 14$。

可以发现，若某个人 $j$ 是和你交换过位置的，那么 ta 的贡献为 $a_i$。否则若是被你跨过的，ta 的贡献为 $b_i$。

每个人是否选择和你交换是你可以选择的，所以对于每个人，我们看两种方式的代价 $a_i$ 和 $b_i$ 的大小，并取代价较小的方案即可。

回到我们求解 $f_i$ 的任务。由于我们最终到了位置 $i$ 上，所以我们必定会和第 $i$ 个人交换位置。那么实际上我们一定会消耗代价 $a_i$。但是对于后面的人，就可以用上面的策略进行了。所以 $f_i = a_i + \sum_{j=i+1}^n \min(a_j, b_j)$。

```cpp
int n, m, a[N], b[N], suf[N], f[N];

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i ) cin >> a[i];
	for (int i = 1; i <= n; ++ i ) cin >> b[i];
	a[n + 1] = b[n + 1] = 0;
	suf[n + 1] = f[n + 1] = 0;
	for (int i = n; i; -- i ) {
		suf[i] = suf[i + 1] + min(a[i], b[i]);
		f[i] = suf[i + 1] + a[i];
	}
	cout << *min_element(f + 1, f + m + 1) << '\n';
	return;
}
```

---

## 作者：HasNoName (赞：2)

### 思路

考虑动态规划。设 $f_i$ 表示插队到第 $i$ 个位置所花费的最少硬币。

可以得出： 
$$
f_i=\min_{i<j\le n}f_j+\sum_{k = i+1}^{j-1}b_k+a_i
$$

从 $n$ 到 $1$ 枚举 $f_i$，因为后面的数加上 $b_i$ 最小的数值在变化后还是最小。

使用贪心的方法。复杂度为 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
ll a[N],b[N],f[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T,n,k;
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>a[i];//输入
        for(int i=1;i<=n;i++)cin>>b[i];
        ll minn=0;
        for(int i=n;i>=1;i--)
        {
            f[i]=minn+a[i];//后面的最小值加上a[i]为f[i]的最小值
            minn=min(minn+b[i],f[i]);//更新后面的最小值
        }
        ll ans=1e18;
        for(int i=1;i<=k;i++)//可能插到k位以前更优
            ans=min(ans,f[i]);
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：Otue (赞：2)

定义 $f_i$ 表示从 $n+1$ 到 $i$ 的最小花费，初始化 $dp_{n+1}=0$。

转移 $f_i=\min_{j=i+1}^{j=n+1} \{f_j+a_i+s_{j-1}-s_i\}$。直接转移是 $O(n^2)$ 的。

先化简：$f_i=a_i-s_i+\min_{j=i+1}^{j=n+1} \{f_j+s_{j-1}\}$。前面是确定的，后面那些只需要维护 `min` 就行。

我们只需要维护 $f_i+s_{i-1}$ 的最小值就行了！

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;

int t, n, m, a[N], b[N], sum[N], dp[N];



signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> b[i];
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + b[i];
		dp[n + 1] = 0;
		for (int i = 1; i <= n; i++) dp[i] = 2e18;
		priority_queue<int, vector<int>, greater<int> > q;
		q.push(sum[n]);
		for (int i = n; i; i--) {
			int t = q.top();
			dp[i] = min(dp[i], q.top() - sum[i] + a[i]);
			q.push(dp[i] + sum[i - 1]);
		}
		int res = 2e18;
		for (int i = 1; i <= m; i++) res = min(res, dp[i]);
		cout << res << endl;
	}
}
```

---

## 作者：Linge_Zzzz (赞：2)

# 题意简述

$n$ 个人在排队，每个人有两个属性 $a_i,b_i$。有一个人站在这 $n$ 个人的后面，他想要进到前 $m$ 个位置中的任何一个。他可以进行任意次数的以下操作：

* 假设他在位置 $x$，他可以选择一个 $y<x$，和他交换位置。一次交换的费用是 $b_y+\sum_{k=y+1}^{x-1}a_k$

问他达成目标的最小费用是多少。

# 解法

考虑 dp。

先把 $a_i$ 用前缀和维护到 $s_i$ 数组。

设 $f_i$ 为从队尾换到第 $i$ 个位置的最小花费，显然有：

$$f_i=\min_{j>i}\{f_j+b_i+s_{j-1}-s_{i}\} $$

初始状态是 $f_{n+1}=0$。

这么转移是 $O(n^2)$ 的，肯定过不了，考虑优化。

先把常数项（和 $j$ 无关的项）提出：

$$f_i=\min_{j>i}\{f_j+s_{j-1}\}+b_i-s_i$$

现在问题就转化为：对于每一个 $i$ 求一个 $x=\min\{f_j+s_{j-1}\}$，然后 $f_i=x+b_i-s_i$ 即可。

显然，这个 $x$ 可以用后缀最大值维护。

于是我们就 $O(n)$ 解决了这个问题。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f;
int n,m;
int a[N],b[N];
int f[N];
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)b[i]+=b[i-1];
	f[n+1]=0;
	int mn=b[n];
	for(int i=n;i>=1;i--){
		f[i]=mn+a[i]-b[i];
		mn=min(mn,f[i]+b[i-1]);
	}
	int ans=INF;
	for(int i=1;i<=m;i++)ans=min(ans,f[i]);
	cout<<ans<<'\n';
	memset(f,0,sizeof(int)*n+10);
	memset(b,0,sizeof(int)*n+10);
	memset(a,0,sizeof(int)*n+10);
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

## 作者：Sternenlicht (赞：2)

思路：

注意到 Kirill 最后一定在第 $1$ 个位置到第 $m$ 个位置之间的某一位置，因此第 $m+1$ 个位置到第 $n$ 个位置的代价需要最小。考虑在 $[m+1,n]$ 这个区间内，对于每个位置 $i$，使用代价为 $\min(a_i,b_i)$ 即可。我们记此时最小代价为 $sum$。

接下来考虑区间 $[1,m]$。我们倒序遍历区间，对于每个位置 $i$，插到当前位置的代价为 $a_i$，又因之前位置的代价最小值为 $sum$，则求 $a_i + sum$ 的最小值即可。注意每遍历一个位置 $i$，要更新 $sum$ 的值，让其加上 $\min(a_i,b_i)$，即为 $[i,n]$ 的最小代价。

注意答案可能会爆 ``int``，要开 ``long long``。

```cpp
#include <bits/stdc++.h>
#define il inline
namespace Fast_IO {
	template <typename T> il void read(T &x) {
		x = 0; int f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + (ch - 48), ch = getchar();
		x = f ? -x : x;
	}
	template <typename T, typename ...Args>
	il void read(T &x, Args& ...args) {read(x), read(args...);}
	template <typename T> il void write(T x, char c = '\n') {
		if (x) {
			if (x < 0) x = -x, putchar('-');
			char a[30]; short l;
			for (l = 0; x; x /= 10) a[l++] = x % 10 ^ 48;
			for (l --; l >= 0; l --) putchar(a[l]);
		} else putchar('0');
		putchar(c);
	}
} using namespace Fast_IO;
using namespace std;

#define int long long
const int Maxn = 200005;
int a[Maxn], b[Maxn];
signed main() {
	int T; read(T);
	while (T --) {
		int n, m; read(n, m);
		for (int i = 1; i <= n; i ++) read(a[i]);
		for (int i = 1; i <= n; i ++) read(b[i]);
		int ans = LONG_LONG_MAX, sum = 0;
		for (int i = m + 1; i <= n; i ++) sum += min(a[i], b[i]);
		for (int i = m; i >= 1; i --) ans = min(ans, a[i] + sum), sum += min(a[i], b[i]);
		write(ans);
	}
	return 0;
}
```

---

## 作者：Aderose_yr (赞：1)

看了一遍没有建图的做法，其实这题用图论还挺好做的。

考虑分层图，下标 $1$ 至 $n$ 代表选择换到的点 $(a[i])$，$n + 1$ 至 $2n$ 代表中间经过的点 $(b[i])$，将每个位置的 $i$，$i + n$ 同前一个位置的 $i - 1$，$i + n - 1$ 之间分别连边，权值即为边终点的 $a[i]$ 或 $b[i]$ 值。

最后设起点为 $2n + 1$ ，同样的方法连边，跑一遍 dijstra，求出前 $i$ 个点最小的 $d[i]$ 即可。注意求最小值时不能包括 $n + 1$ 至 $2n$ 的 $d[i]$ 值，因为最后应停止在所交换到的位置 $(a[i])$ 上。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll a[200010],b[200010];
vector<P>v[400010];
ll d[400010];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
    	int n,m;
    	scanf("%d%d",&n,&m);
    	for(int i=1;i<=n;i++){
    		v[i].clear(); 
    		v[i+n].clear();
    		d[i]=1e17;
    		d[i+n]=1e17;
		}
		v[n*2+1].clear();
    	for(int i=1;i<=n;i++){
    		scanf("%lld",&a[i]);
		}
    	for(int i=1;i<=n;i++){
    		scanf("%lld",&b[i]);
		}
		for(int i=2;i<=n;i++){
    		v[i].push_back(P(i-1,a[i-1]));
    		v[i].push_back(P(i+n-1,b[i-1]));
    		v[i+n].push_back(P(i+n-1,b[i-1]));
    		v[i+n].push_back(P(i-1,a[i-1]));
		}
		v[n*2+1].push_back(P(n,a[n]));
		v[n*2+1].push_back(P(n*2,b[n]));
		d[n*2+1]=0;
		priority_queue<P,vector<P>,greater<P> >q;
		q.push(P(0,n*2+1));
		while(!q.empty()){
			ll x=q.top().first,y=q.top().second;
			//printf("when d[%lld]=%lld:\n",y,d[y]);
			q.pop();
			if(d[y]<x)continue;
			for(int i=0;i<v[y].size();i++){
				ll t=v[y][i].first,w=v[y][i].second;
				if(d[t]>d[y]+w){
					d[t]=d[y]+w;
					//printf("d[%d]=%lld\n",t,d[t]);
					q.push(P(d[t],t));
				}
			}
		}
		ll ans=1e18;
		for(int i=1;i<=m;i++){
			ans=min(ans,d[i]);
		}
		printf("%lld\n",ans);
	}
    
	
    return 0;
}
``````

---

## 作者：zcxnb (赞：1)

挺好玩的一道贪心题。

转化一下式子，我们发现 $a[i],b[i]$ 的选择过程类似于一个上下反复横跳的最终的选取停止在 $a$ 数组的一个过程，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/h4sayj5v.png)

注意到对于一个 $j$ 位置，我们只会在 $a[j]$，$b[j]$ 中选一个对答案产生贡献，且在 $m+1,m+2,\cdots, n$ 之间选哪一个数并不会对之后的决策产生影响（无后效性）。

因为在 $m+1,m+2,\cdots, n$ 之间我们每个选择是独立的，所以在 $m+1,m+2,\cdots, n$ 之间直接贪心，对答案的贡献即为 $\sum_{i=m+1}^n \min\{a[i],b[i]\}$。

那么在 $1,2,\cdots,m$ 这一段对答案的贡献就显而易见了，因为在这一段中只要选择了 $a[j]$ 就停止选择了，所以答案的组成既是一段 $b_{j+1},b_{j+2} ,\cdots ,b_m$ 再加上 $a_j$。

所以只需要统计一下 $\min_{i=1}^m\{\sum_{j=i+1}^mb[j]+a[i]\}$ 即可。

最终答案即是这两段贡献的加和。

代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18+5;
int n,m,t;
int a[N],b[N];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&b[i]);
		}
		int cnt=0,ans=inf;
		for(int i=n;i>=1;i--){
			if(i>m){
				if(a[i]>b[i]){
					cnt+=b[i];
				}
				else{
					cnt+=a[i];
				}
			}
			else{
				ans=min(ans,cnt+a[i]);
				cnt+=b[i];
			}
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Double_Light (赞：0)

一种不需要动态规划的做法。

首先对于 $m+1\sim n$ 的序列可以随便取 $a_i,b_i$，因为每一种取法都对应着一种不同的移动方式。所以取最小值。

随后对于 $1\sim m$ 的位置，显然如果已经与其中一个位置交换了，那么就不需要再往下交换了。所以答案就是 $\min(a_i+\sum_{i+1\leq j\leq m}^{m}b_j)$，其中 $1\leq i\leq m$。

最后代码如下：

```cpp
#include<iostream>
#define int long long
using namespace std;
int t,n,m;
int a[200005],b[200005],ans,minn,sum[200005];
signed main(){
	cin>>t;
	while(t--){
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		for(int i=m+1;i<=n;i++){
			ans+=min(a[i],b[i]);
		}
		minn=a[m];
		sum[m]=b[m];
		for(int i=m-1;i>=1;i--){
			sum[i]=sum[i+1]+b[i];
			minn=min(minn,sum[i+1]+a[i]);
		}
		cout<<ans+minn<<endl;
	}
	return 0;
}
```

---

## 作者：L_xcy (赞：0)

[D. Seraphim the Owl](https://codeforces.com/contest/1945/problem/D)

---

### 题目翻译

给你一个 $N$ 和 $M$，一个长度为 $N$ 的 $a$ 数组 和 $b$ 数组。

我们的主人公现在在第 $N+1$ 个位置，他想插到至少前 $M$ 的位置。

若主人公在位置 $i$，与前面的 $j$ 交换位置的代价为 $a_{j}$，对于每个 $k$，使得 $j \leq k \leq i$，主人公将不得不向位置 $k$ 的人支付 $b_{i}$ 硬币。

求主人公必须花费的最低硬币数量。

---

### 解题思路

如果你读题够仔细，或者刷的题够多，就会发现。

设 $f_{i}$ 表示主人公插到第 $i$ 个位置的最小花费。

除了最后主人公要插的那个位置 $( m )$ 一定要付 $a_{m}$ 个硬币之外 $( f_{m} = f_{m+1} + a_{i} )$。

在这个位置之前的 $f_{i} (m + 1 \leq i \leq n) = f_{i+1} + \min (a_{i},b_{i})$。

我们把 1 到 $m$ 所有的 $f_{i}$ 都求出来，再求一个最小值就可以了。

---

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

long long a[200005],b[200005],f[200005];

void solve() {
	long long n = 0,m = 0;
	scanf("%lld%lld",&n,&m);
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(f,0,sizeof(f));
	for(int i = 1;i <= n; i++) {
		scanf("%lld",&a[i]);
	}
	for(int i = 1;i <= n; i++) {
		scanf("%lld",&b[i]);
	}
	for(int i = n;i >= 1; i--) {
		f[i] = f[i+1] + min(a[i],b[i]);
	}
	for(int i = 1;i <= m; i++)
		f[i] = f[i+1] + a[i];
	long long ans = LONG_LONG_MAX;
	for(int i = 1;i <= m;i++)
		ans = min(ans,f[i]);
	printf("%lld\n",ans);
}
int main() {
	long long t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Cute__yhb (赞：0)

## 思路

动态规划。

设 $f_i$ 为到第 $i$ 个人时的费用。

则 $f_{n+1}$ 为 $0$。

有一个很显然的 $O(n^2)$ 做法，从后往前枚举，在每个位置上时找它后面的位置，计算出费用，求最小值。

考虑优化。

找每个位置的过程不好优化，从最小值下手。

设 $sum$ 为从最小值到 $i$ 的 $b_i$ 之和，$min$ 为最小值。

在枚举完每个位置后，$sum$ 就应该加上 $b_i$。然后，如果  $f_i\le min+sum$，应该更改最小值，并让 $sum$ 为 $0$。

这样，时间复杂度为 $O(n)$，可以通过。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define re register
#define ri register int
#define rll register long long
#define ld long double
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define nep(i,a,b) for(int i=(a);i>=(b);i--)
#define popcount __builtin_popcount
#define pb push_back
#define mem(a,x) memset((a),x,sizeof(a))
#define eps 1e-8
#define oper operator
#define mk make_pair
int n,m;
ll a[200005],b[200005],f[200005];
void solve(){
	cin>>n>>m;
	f[n+1]=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i]=0;//多测卡memset
	}
	for(int i=1;i<=n;i++) cin>>b[i];
	ll minn=0,sum=0,ans=2000000000ll*500005;
	for(int i=n;i;i--){
		f[i]=minn+sum+a[i];
		if(f[i]<=minn+sum+b[i]){//更新最小值
			minn=f[i];
			sum=0;
		}
		else{
			sum+=b[i];
		}
		if(i<=m) ans=min(ans,f[i]);//满足要求
	}
	cout<<ans<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}

```

---

## 作者：jubingkun (赞：0)

[洛谷](https://www.luogu.com.cn/problem/CF1945D)

[Codeforces](https://codeforces.com/contest/1945/problem/D)

## 题目大意
小 K 想要从第 $n + 1$ 个位置到达前 $m$ 个位置，如果小 K 从位置 $j$ 走到位置 $i$，那么花费是 $a_i + \sum_{k=i+1}^{j-1}b_k$，最小化此花费。
## 题目分析
很容易想到动态规划。

设 $dp_i$ 表示到第 $i$ 位时的最小花费，那么有转移方程 $dp_i = \min\limits_{i<j\leq n+1}(dp_j + \sum_{k=i+1}^{j-1}b_k+a_i)$。

此时，转移是 $O(n^3)$ 的，因为需要枚举 $i,j$ 和求 $b_i$ 的区间和。

可以使用前缀和来优化掉求 $b_i$ 区间和这一步骤（设 $b_i$ 的前缀和为 $sum_i$），此时转移方程为 $dp_i = \min\limits_{i<j\leq n+1}(dp_j + sum_{j-1}-sum_i+a_i)=a_i-sum_i+\min\limits_{i<j\leq n+1}(dp_j+sum_{j-1})$，此时时间复杂度为 $O(n^2)$。

考虑优化掉枚举 $j$ 的这一层，显然 $a_i-sum_i$ 与 $j$ 无关，只有 $dp_j+sum_{j-1}$ 是不断变化的，那么可以使用数据结构等维护 $dp_j+sum_{j-1}$ 的最小值，用的时候直接查询就行了。
## 细节问题
我们会发现 $dp_i$ 只能由下标比 $i$ 大的 $dp$ 数组转移过来，所以要倒着跑（即从 $n$ 开始跑到 $1$）。

由于这一性质（$dp_i$ 只能由下标比 $i$ 大的 $dp$ 数组转移过来），我们可以用一个变量记录 $dp_j+sum_{j-1}$ 的最小值，记作 $minn$，每计算完一个点就更新一下它（具体实现可以见代码）。

注意开 long long，记得 $minn$ 要初始化为 $1\times10^{18}$（尽量贴紧 long long 的上界）。

## 代码
```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 5;
int T;
int n, m;
ll a[MAXN], b[MAXN], sum[MAXN], dp[MAXN];
ll minn;
int main() {
	cin >> T;
	while (T--) {
		cin >> n >> m;
		minn = 1e18;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			sum[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			cin >> b[i];
			sum[i] = sum[i - 1] + b[i];
		}
		for (int i = n; i >= 1; --i) {
			if (i == n) {
           		dp[n] = a[n];
				minn = min(dp[n] + sum[n - 1], sum[n]);
				continue;
			}
			dp[i] = minn - sum[i] + a[i];
			minn = min(minn, dp[i] + sum[i - 1]);
		}
		minn = 1e18;
		for (int i = 1; i <= m; ++i)
			minn = min(minn, dp[i]);
		cout << minn << '\n';
	}
	return 0;
}
/*
j > i
dp[j] + sum[j - 1] - sum[i] + a[i]
*/
```

---

## 作者：Starrykiller (赞：0)

你起初在位置 $(n+1)$，你想要让自己在位置 $1\sim m$ 中的一个。

当你在下标 $j$ 和下标 $i$ 的人互换的时候，你要付出的代价为

$$a_i+\sum_{k=i+1}^{j-1} b_i$$

求出最小代价。$m\le n\le 2\times 10^5$，$1\le a_i,b_i\le 10^9$。

记 $s_i=\sum_{k=1}^i \min(a_i,b_i)$，我们发现从 $(n+1)$ 换到 $i$ 的最优代价为 

$$a_i+\sum_{k=i+1}^n s_k$$

证明：我们假设要从 $r$ 换到 $l$，则朴素地换代价是 $a_l+\sum_{k=l+1}^r b_k$。但是你会发现，如果对于某个 $i\lt l\lt t$，有 $a_i\lt b_i$，我们完全可以先 $r\to i$，再 $i\to l$，这样做的代价等效于令 $b_i\gets(b_i,a_i)$。而且对于每一个 $l\le l_i\lt r_i\le r$，我们都可以这么做来得到最优方案，于是这样得到的方案肯定是最优的。

直接找到最小值输出就可以了。时间复杂度 $\Theta(n+m)$。

[My Submission](https://codeforces.com/contest/1945/submission/252213241).

---

## 作者：GY程袁浩 (赞：0)

### 题意
对于两个代价数组 $a$ 与 $b$，一开始 $i=n$，每次需要耗费 $a_{i}$ 或 $b_{i}$ 的代价，使得 $i$ 的值减 $1$。当 $i\le k$ 且目前选择为 $a_{i-1}$ 时，可以停下并得到代价总值，求最小代价。
### 思路
考虑状态机动态规划的解法。

状态表示为 $dp_{i,k}$。

集合：考虑目前在 $i$，决策是 $k$ 的集合，$k=0$ 表示选 $a$，$k=1$ 表示选 $b$。

性质：最小值。

状态转移：目前的 $i$ 能由 $i-1$ 选择而来。

- $dp_{i,0}\gets\min(dp_{i+1,0},dp_{i+1,1})+a_{i}$

- $dp_{i,1}\gets\min(dp_{i+1,0},dp_{i+1,1})+b_{i}$

由题可知，最终的答案为 $min\{dp_{i,0}\}$，其中 $1\le i\le k$。
### Code
```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define int unsigned long long
using namespace std;
const int N=1e5*2+10;
int f[N][2];
int a[N],b[N];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(f,0,sizeof f);
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++) {
			cin>>a[i];
		}
		for(int i=1;i<=n;i++) {
			cin>>b[i];
		}
		for(int i=n;i>=1;i--)
		{
			f[i][0]=min(f[i+1][1],f[i+1][0])+a[i]; 
			f[i][1]=min(f[i+1][1],f[i+1][0])+b[i];
		}
		int minn=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=k&&i<=n;i++)
		{
			minn=min(minn,f[i][0]);
		}
		cout<<minn<<endl;
	}
	return 0;
}
```

---

