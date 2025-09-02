# Bouquet (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version, instead of listing the number of petals for each flower, the number of petals and the quantity of flowers in the store is set for all types of flowers.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ different types of flowers in the store, each of which is characterized by the number of petals and the quantity of this type of flower. A flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use to decorate her cake should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 说明/提示

In the first test case, some valid bouquets are $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the second test case, you can assemble a valid bouquet with $ (206, 206, 207, 207, 207) $ with a sum of $ 1033 $ , which is the maximum number of petals the girl can buy. In the third test case, you can assemble a valid bouquet with $ (5, 5, 5, 4) $ with a sum of $ 19 $ . It can be seen that no valid bouquet can have $ 20 $ petals.

## 样例 #1

### 输入

```
7
3 10
1 2 3
2 2 1
3 1033
206 207 1000
3 4 1
6 20
4 2 7 5 6 1
1 2 1 3 1 7
8 100000
239 30 610 122 24 40 8 2
12 13123 112 1456 124 100 123 10982
6 13
2 4 11 1 3 5
2 2 1 2 2 1
8 10330
206 210 200 201 198 199 222 1000
9 10 11 12 13 14 15 16
2 10000000000
11 12
87312315 753297050```

### 输出

```
7
1033
19
99990
13
10000
9999999999```

# 题解

## 作者：Eraine (赞：11)

编号：CF1995B

tag：双指针 / 贪心

难度：（两个网站均未发布）

B1 双指针做法很显然，这里便不再赘述。

观察 B2 的限制条件，排序后问题变成给定 $a$ 个价值为 $x$ 的物品和 $b$ 个价值为 $x+1$ 的物品，要求从中选出若干个物品使得价值和不超过 $m$ 并最大化价值和。

这种题目记住两种套路，不单是阅览此文的各位读者，包括我自己，切记这种看起来像二元线性规划的题目不是解不等式就是调整！解不等式显然行不通，因为有最大化的条件，那么就调整。显然这里的 $x+1$ 要作为一个重要条件使用。由于在背包问题中显然 $x+1$ 的约束更紧，显然是填满 $x$ 来调整 $x+1$。

以上分析思路尤为重要，希望各位能够谨记。

接下来就是填满 $x$ 再去调整 $x+1$ 了。具体地，先填 $x$，再填 $x+1$，会发现可能会剩余部分空间可以让我们将 $x$ 变成新的 $x+1$，假设当前填了 $sum0$ 个 $x$ 和 $sum1$ 个 $x+1$ 那么约束一下这个上限 $\min(sum0,sum_{x+1}-sum1,m-sum0\times x-sum1\times(x+1))$ 即可。

$\Theta(n\log n)$。

[submission](https://codeforces.com/contest/1995/submission/272128318)

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：ANDER_ (赞：5)

~~其实这次比赛的第二与第三题并无区别，出题组良心送分了属于是。~~
#### 考察：分类讨论、模拟、贪心。
## 题意
现在有 $m$ 元钱，$n$ 种花，第 $i$ 种花有 $a_i$ 个花瓣，$c_i$ 朵，买一朵需要 $a_i$ 元钱。构造一种买花方案，设 $w$ 为所买花的花瓣数集合，需要满足 $\sum w$ 最大，且 $\sum w \le m \bigwedge w_{max} - w_{min} \le 1 \equiv T$，输出 $\sum w$。

## 思路
其实此题与 [CF1995B1](https://www.luogu.com.cn/problem/CF1995B1) 做法并无区别。根据题意，我们构造的买花方案只有两种情况：

1. 所买花的花瓣数都相同。
2. 所买花的花瓣数为 $s$ 或 $s + 1$。

首先讨论较为简单的情况一，不妨设所买的花为第 $i$ 种，共买 $q$ 朵，此时所花的钱数就为 $a_i \times q$。最大化 $a_i \times q$，可被转化为最大化 $\lfloor \frac{m}{a_i} \rfloor$。直接计算即可。

再来看情况二，不妨设所买花瓣数为 $s$ 的花有 $p$ 朵，$s + 1$ 的花有 $q$ 朵，当前方案 $w$ 的 $\sum w$ 为 $t$。我们可以贪心的选择花瓣数为 $s$ 的花。若花瓣数为 $s$ 的花已经买空，我们就继续选择花瓣数为 $s + 1$ 的花。若 $m - t < s$，显然可以考虑将花瓣数为 $s$ 的花替换为 $s + 1$，这样就可以使 $t$ 加一。按照上述逻辑，模拟即可。

先排序，后按照上述方法模拟即可得出答案，时间复杂度 $O(\sum n \lg n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
#define CODEFORCES
void solve() {
	int n, m, ave, cnt = 0, res = 0;
	cin>>n>>m;
	vector<pair<int, int>> vec(n);
	for(auto &[x, _] : vec) {
        cin>>x;
    }
	for(auto &[_, x] : vec) {
        cin>>x;
    }
	sort(vec.begin(), vec.end());
	ave = vec[0].first;
	for (auto i : vec) {
		int a = i.first, b = i.second;
		if (a - ave > 1) {
			res = max(res, a * min(b, m / a));
		} else {
            int tmp = min(cnt, m / ave), tmp1, tmp2 = m - min(cnt, m / ave) * ave;
			tmp1 = min(b, tmp2 / a), tmp2 -= tmp1 * a;
			res = max(res, m - tmp2 + min({tmp2, b - tmp1, tmp}));			
		}
		ave = a, cnt = b;
	}
	cout<<res<<endl;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);
#ifdef CODEFORCES
	int T = 1;
	for(cin>>T ; T -- ; ) {
		solve();
	}
#else
	solve();
#endif
	return 0;
}
```

---

## 作者：Leeb (赞：2)

### 题意简述

B1的升级版。相较于B1，没有明确的给出价值序列 $a_i$，而是给出 $a_i$ 表示价值，$c_i$ 表示价值为 $a_i$ 的花的个数，保证对于 $\forall 1\le i,j\le n, i \ne j$ 都有 $a_i \ne a_j$。

### 解题思路

先对 $a_i$ 排个序。 

因为给定的价值不重复，那么只需考虑对 $a_i$ 和 $a_{i+1}$ 且 $a_{i+1}-a_i\le 1$ 的两个价值进行操作。

先尽可能的多去买 $a_i$，然后一个一个用 $a_{i+1}$ 替换掉 $a_i$ 直到无法替换。

有些判断的细节，详见代码。

### 参考代码

```cpp
// Code by Leeb
// Powered by Visual Studio Code
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
#include <bits/stdc++.h>
// #include <cstdio>
// #include <cstring>
// #include <algorithm>
#define N 200005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define PII pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, m, ans;
struct Node {
	int x, c;
	inline bool operator < (const Node &oth) const {
		return x < oth.x;
	}
} a[N];
inline int in() {
	int a = 0; bool f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = 1; ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
	if (f) return ~a + 1;
	return a;
}
inline void print(int x) {
	if (x < 0) putchar('-'), x = ~x + 1;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
	print(x);
	putchar(ch);
}
inline void init() {
	n = in(), m = in(); 
	for (int i = 1; i <= n; ++i) a[i].x = in();
	for (int i = 1; i <= n; ++i) a[i].c = in();
}
inline void work() {
	if (n == 1) {
		int k1 = m / a[1].x;	
		int x1 = a[1].x * min(k1, a[1].c);
		out(x1, endl); return ;
	}
	sort(a + 1, a + 1 + n); ans = 0;
	for (int i = 1; i < n; ++i) {	
		if (a[i + 1].x != a[i].x + 1) {
			int k1 = m / a[i].x, k2 = m / a[i + 1].x;
			int x1 = a[i].x * min(k1, a[i].c), x2 = a[i + 1].x * min(k2, a[i + 1].c);
			ans = max({ ans, x1, x2 }); continue;
		}
		int x = a[i].c * a[i].x + a[i + 1].c * a[i + 1].x;
		if (x <= m) { ans = max(ans, x); continue; }
		int k1 = m / a[i].x; x = a[i].x * min(k1, a[i].c);
		int k2 = (m - x) / a[i + 1].x; x += a[i + 1].x * min(k2, a[i + 1].c);
		if (min(k1, a[i].c) > 0 && min(k2, a[i + 1].c) < a[i + 1].c && x < m) 
			x += min({ min(k1, a[i].c), a[i + 1].c - min(k2, a[i + 1].c), m - x });
		ans = max(ans, x);
	}
	out(ans, endl);
}
signed main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	int t = in();
	while (t--) {
		init();
		work();
	}
	return 0;
}
```

---

## 作者：sad_lin (赞：1)

为什么没人写**二分答案**呢，明明更好想。

先对 $a$ 数组排个序。

买花只有两种买法，只买 $a_i$ 和同时买 $a_i,a_{i+1}$ 且 $a_{i+1}-a_i=1$，对于第一种买法直接二分答案买的数量即可，第二种买法也分别二分答案两个花的购买数量，但是对于买完 $a_{i+1}$ 后，仍有多余的钱和多余的数量，就可以将 $a_i$ 尽可能地转化为 $a_{i+1}$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls p<<1
#define rs p<<1|1 
#define re register 
#define pb push_back
#define pir pair<int,int>
#define f1(x) for(int i=1;i<=x;i++)
#define f0(x) for(int i=0;i<=x;i++)
#define fr1(x) for(int i=x;i>=1;i--)
#define fr0(x) for(int i=x;i>=0;i--) 
const int N=2e5+10,M=25005;
const int mod=1e9+7;
using namespace std;

int n,m;
struct ss{
	int x,y;
}a[N];

bool cmp(ss g,ss h){
	return g.x<h.x;
}

int ans=0;

void check(int midd,int ax,int ay,int bx,int by,int las){
	int l=0,r=by,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(mid*bx<=las){
			ans=max(ans,ax*midd+mid*bx+min(midd,min(las-mid*bx,(by-mid))));
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
}

void find(int i1,int i2){
	int ax=a[i1].x,ay=a[i1].y;
	int bx=a[i2].x,by=a[i2].y;
	
	int l=0,r=ay,mid;
	
	while(l<=r){
		mid=(l+r)>>1;
		if(mid<=m/ax){
			check(mid,ax,ay,bx,by,m-mid*ax);
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
}

void find2(int i1){
	int ax=a[i1].x,ay=a[i1].y;
	
	int l=0,r=ay,mid;
	
	while(l<=r){
		mid=(l+r)>>1;
		if(mid*ax<=m){
			ans=max(ans,mid*ax);
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
}

void solve(){
	ans=0;
	cin>>n>>m;
	
	f1(n){
		cin>>a[i].x;
	}
	f1(n){
		cin>>a[i].y;
	}
	
	sort(a+1,a+n+1,cmp);
	
	f1(n-1){
		find2(i);
		if(a[i].x==a[i+1].x-1){
			find(i,i+1);	
		}
	}
	find2(n);
	cout<<ans<<"\n";
}


signed main(){
//	freopen("xp1.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int t;
    cin>>t;
    while(t--){
    	solve();
    	
	}
	return 0;
}
```

---

## 作者：dengjunhaodejia09 (赞：0)

这道题在比赛中实在想不到，但现在又会了。

首先我们找出其中不寻常的东西，那就是价值与花的钱相同，则我们要尽量多花钱。其次他只有两种物品那么我们考虑一个贪心策略，首先假设此时有两种物品，代价分别为 $x$ 与 $x+1$ 。我们先全选代价为 $x$ 的，再选代价为 $x+1$ 的，最后将所有能将 $x$ 替换为 $x+1$ 的全部替换。这为什么是对的呢，让我们来证明一下。

首先，若是所有都放了还达不到全部的钱，那么显然是对的，最优就是先放 $x$ 再放 $x+1$ 的全放。其次剩下的情况中，若是恰好凑满钱数那也是不存在更优的。所以剩下的情况只会是 $x+1$ 全放，$x$ 有的放不下了，那么若是将一些 $x+1$ 替换为 $x$ 再放一个 $x$ 使更优那么便是只有这种情况，但这也是不可能的，我们是考虑一开始全放了 $x+1$ ，而这种情况的出现便是我们去掉了一个原来放的 $x$ 改成让更多的 $x$ 变成 $x+1$ 这与我们的操作不同，即没有更优的情况，得证。



```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int x,y;
}a[1919810];
bool cmp(node aa,node bb){
	return aa.x<bb.x;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		long long n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i].x;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i].y;
		}
		sort(a+1,a+n+1,cmp);
		int Max=0;
		for(int i=1;i<=n;i++){
			Max=max(Max,min(m/a[i].x,a[i].y)*a[i].x);
			if(i<n && a[i].x==a[i+1].x-1){
				int l=min(m/a[i].x,a[i].y)*a[i].x;
				int ll=min((m-l)/a[i+1].x,a[i+1].y)*a[i+1].x;
				ll+=min(min(m/a[i].x,a[i].y),min(m-l-ll,a[i+1].y-min((m-l)/a[i+1].x,a[i+1].y)));
				Max=max(Max,l+ll);
			}
		}
		cout<<Max<<endl;
	}
	return 0;
} 
```

---

## 作者：shao0320 (赞：0)

显然划分为两种情况，只取一种或者取两种权值差 $1$ 的花。
  
  对于第一种直接依次处理每种花即可，对于第二种，考虑值为 $x$ 和 $x+1$ 的花分别有 $a$ 、$b$ 朵，那么实际上是求最大的 $cx+d(x+1) \leq m ,c\leq a,d \leq b$ 。
  
  考虑先把所有花都取了之后再调整，注意到大小花的值差 $1$ ，那么可以先减少部分大花使得总权值符合要求，再将大花换回小花追求更高收益。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define N 200005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f;
}
int T,n,m,a[N],c[N];
pii p[N];
signed main()
{
    #ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    T=read();
    while(T--)
    {
        n=read();m=read();
        for(int i=1;i<=n;i++)a[i]=read();
        for(int i=1;i<=n;i++)c[i]=read();
        for(int i=1;i<=n;i++)p[i]=mp(a[i],c[i]);
        sort(p+1,p+1+n);
        for(int i=1;i<=n;i++)a[i]=p[i].fi,c[i]=p[i].se;
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            ans=max(ans,a[i]*min(c[i],m/a[i]));
            if(a[i]!=a[i-1]+1)continue;
            if(a[i]*c[i]+a[i-1]*c[i-1]<=m)
            {   
                ans=max(ans,a[i]*c[i]+a[i-1]*c[i-1]);
                continue;
            }
            int ff=a[i]*c[i]+a[i-1]*c[i-1]-m;
            int gg=(ff+a[i]-1)/a[i];
            int tmp=0,nowa=0;
            if(gg>c[i])
            {
                tmp=c[i]*a[i]+a[i-1]*((ff-c[i]*a[i]+a[i-1]-1)/a[i-1]);
                nowa=(ff-c[i]*a[i]+a[i-1]-1)/a[i-1];
                int qq=tmp-ff;
                int pp=min(qq,min(c[i],c[i-1]-nowa));
                ans=max(ans,c[i]*a[i]+c[i-1]*a[i-1]-tmp+pp);
            }
            else 
            {
                tmp=gg*a[i];
                int qq=tmp-ff;
                int pp=min(qq,min(gg,c[i-1]));
                ans=max(ans,c[i]*a[i]+c[i-1]*a[i-1]-tmp+pp);
            }
        }
        printf("%lld\n",ans);
    }
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
首先遍历每一朵花，设当前枚举到的花的花瓣数是 $x$，出现次数是 $y$。那么我们计算当前最多能买几朵有 $x$ 个花瓣的花并且计算花费。如果有 $x+1$ 个花瓣的花那么计算剩余的钱能买多少 $x+1$ 个花瓣的花。

注意，如果条件允许的情况下，我们可以少买一个 $x$ 个花瓣的花，多买一个 $x+1$ 个花瓣的花，以实现尽可能多花钱（多花一块也是多花钱）。

最后更新最大值，本题多测。注意本题 $m \leq 10^{18}$。
### 代码
```cpp
#include<iostream>
#include<map>
#define int long long
#define N 200005
int n,m,t,a[N],b[N];
signed main(){
	std::cin>>t;
	while(t--){
		std::cin>>n>>m;
		std::map<int,int>mp;
		for(int i=1;i<=n;i++)std::cin>>a[i];
		for(int i=1;i<=n;i++)std::cin>>b[i];
		for(int i=1;i<=n;i++)mp[a[i]]=b[i];
		int maxn=0;
		for(auto [x,y]:mp){
			/*
			 * std::min(y,m/x):计算剩余的钱最多能买
			 					 多少枝有x个花瓣的花
			 * 整个式子计算买 min(y,m/x) 朵花的花费 
			*/
			int ans=x*std::min(y,m/x);
			if(mp.find(x+1)!=mp.end()){//如果有 (x+1) 个花瓣的花 
				int remain=m-ans;//计算当前还剩多少钱
				//计算剩余的钱能买多少枝有 (x+1) 个花瓣的花
				int cnt=std::min(mp[x+1],
								 remain/(x+1));
				ans+=cnt*(x+1);
				ans+=std::min(std::min(y,m/x),
							 std::min(mp[x+1]-cnt,remain-cnt*(x+1)));
				/*
			 可以多买 x+1 个花瓣的花，少买一个 x 个花瓣的花，看看能搞几次，每一次都能多花一块钱。
				*/
			} 
			maxn=std::max(maxn,ans);
		}
		std::cout<<maxn<<"\n"; 
	}
}
```

---

