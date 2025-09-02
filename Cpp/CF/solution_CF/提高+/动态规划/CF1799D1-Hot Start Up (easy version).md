# Hot Start Up (easy version)

## 题目描述

This is an easy version of the problem. The constraints of $ t $ , $ n $ , $ k $ are the only difference between versions.

You have a device with two CPUs. You also have $ k $ programs, numbered $ 1 $ through $ k $ , that you can run on the CPUs.

The $ i $ -th program ( $ 1 \le i \le k $ ) takes $ cold_i $ seconds to run on some CPU. However, if the last program we ran on this CPU was also program $ i $ , it only takes $ hot_i $ seconds ( $ hot_i \le cold_i $ ). Note that this only applies if we run program $ i $ multiple times consecutively — if we run program $ i $ , then some different program, then program $ i $ again, it will take $ cold_i $ seconds the second time.

You are given a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers from $ 1 $ to $ k $ . You need to use your device to run programs $ a_1, a_2, \ldots, a_n $ in sequence. For all $ 2 \le i \le n $ , you cannot start running program $ a_i $ until program $ a_{i - 1} $ has completed.

Find the minimum amount of time needed to run all programs $ a_1, a_2, \ldots, a_n $ in sequence.

## 说明/提示

In the first test case, we can do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 3 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 2 $ seconds to run.
- Run program $ a_3 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 3 + 2 + 1 = 6 $ seconds to run them all. We can show this is optimal.

In the second test case, we can use do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 5 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 3 $ seconds to run.
- Run program $ a_3 = 1 $ on CPU $ 1 $ . The last program run on this CPU was also program $ 1 $ , so it takes $ hot_1 = 2 $ seconds to run.
- Run program $ a_4 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 5 + 3 + 2 + 1 = 11 $ seconds. We can show this is optimal.

## 样例 #1

### 输入

```
9
3 2
1 2 2
3 2
2 1
4 2
1 2 1 2
5 3
2 1
4 3
1 2 3 1
100 100 100
1 1 1
5 2
2 1 2 1 1
65 45
54 7
5 3
1 3 2 1 2
2 2 2
1 1 1
5 1
1 1 1 1 1
1000000000
999999999
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
1 3
3
4 5 6
1 2 3
8 3
3 3 3 1 2 3 2 1
10 10 8
10 10 5```

### 输出

```
6
11
301
225
8
4999999996
11
6
63```

# 题解

## 作者：SlyCharlotte (赞：7)

## 题目大意

你有两个 CPU，$n$ 个程序要运行，总共 $k$ 种程序需要运行。在不同条件下程序运行的时间不同，但连续运行的时间满足小于等于在不连续状态下运行的时间。

## 简要分析

很容易想到 dp。

最容易想到的状态是 $dp_{i,j,k}$ 表示当前处理到第 $i$ 个程序，CPU1 执行的最后一个程序种类为 $j$，CPU2 执行的最后一个程序种类为 $k$。

显然复杂度炸了。

不难发现，一定会有一个 CPU 执行的最后一个程序的种类为 $a_{i-1}$，于是可以优化掉一维。

转移按照定义转移即可。

## 代码实现

```c++
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll maxn = 5e3 + 7;
const ll INF = 1e9 + 7, MOD = 998244353;

inline ll read() {
    char cCc;
    ll xXx = 0, wWw = 1;
    while (cCc < '0' || cCc > '9')
        (cCc == '-') && (wWw = -wWw), cCc = getchar();
    while (cCc >= '0' && cCc <= '9')
        xXx = (xXx << 1) + (xXx << 3) + (cCc ^ '0'), cCc = getchar();
    xXx *= wWw;
    return xXx;
}

inline void write(ll xXx) {
    if (xXx < 0)
        putchar('-'), xXx = -xXx;
    if (xXx > 9)
        write(xXx / 10);
    putchar(xXx % 10 + '0');
}

ll A[maxn], cold[maxn], hot[maxn], dp[maxn][maxn];

void solve() {
    ll n = read(), k = read();
    for (ll i = 1; i <= n; i++)A[i] = read();
    for (ll i = 1; i <= k; i++)cold[i] = read();
    for (ll i = 1; i <= k; i++)hot[i] = read();
    A[0] = -1;
    for (ll i = 0; i <= n; i++)
        for (ll j = 0; j <= k; j++)
            dp[i][j] = 1e18;
    dp[1][0] = cold[A[1]];
    for (ll i = 2; i <= n; i++) {
        ll first = A[i - 1];
        for (ll j = 0; j <= k; j++) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + (A[i] == first ? hot[A[i]] : cold[A[i]]));
            dp[i][first] = min(dp[i][first], dp[i - 1][j] + (A[i] == j ? hot[A[i]] : cold[A[i]]));
        }
    }
    ll ans = 1e18;
    for (ll i = 0; i <= k; i++)
        ans = min(ans, dp[n][i]);
    cout << ans << '\n';
}

signed main() {
//    freopen("code.in","r",stdin);
//    freopen("code.out","w",stdout);
    ll T = read();
    while (T--)solve();
    return 0;
}
```




---

## 作者：穼柗° (赞：2)

没有多难（老师说这题蓝得发绿），直接 DP。

首先设 $dp_{i,j}$ 表示第 $i$ 个程序执行完后，两个 CPU 运行的最后一个程序一个编号为 $i$（也就是第 $i$ 个程序）、另一个类型为 $j$，最短运行完前 $i$ 个程序的时间。那么显然有 $answer=\min\{dp_{n,i}\}$。

稍微思考可得转移方程（箭头左边的数与箭头右的求**最小值**并更新箭头左的数）：\
若 $dp_{i,j}$ 是合法状态，且 $i<n$，则
$$
dp_{i+1,j}\larr\begin{cases}
dp_{i,j}+hot_{a_{i+1}},a_i=a_{i+1}\\
dp_{i,j}+cold_{a_{i+1}},a_i\ne a_{i+1}
\end{cases}\\
dp_{i+1,a_i}\larr\begin{cases}
dp_{i,j}+hot_{a_{i+1}},j=a_{i+1}\\
dp_{i,j}+cold_{a_{i+1}},j\ne a_{i+1}
\end{cases}
$$
转移的次序和我以前学的不一样，是枚举合法状态推出后继状态。边界：在 $dp$ 中 $dp_{0,0}=0$，其它的都是 $\infty$。也就是说 $\infty$ 表示不知道这个位置是否合法，然后通过合法状态推出的数一定合法所以替代掉 $\infty$。

时间复杂度 $O(nk)$，$n,k\le5000$，不会爆。

### AC Code
```cpp
#include <iostream>
#define int long long
#define inf 1000000000000000000ll
using namespace std;
int n,k,a[5001],h[5001],c[5001],dp[5001][5001];
void solve() {
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=k;i++)
		cin>>c[i];
	for(int i=1;i<=k;i++)
		cin>>h[i];
	for(int i=0;i<=n;i++)
		fill(dp[i],dp[i]+k+1,inf);
	dp[0][0]=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<=k;j++) if(dp[i][j]<inf) {
			dp[i+1][j]=min(dp[i+1][j],dp[i][j]+(a[i+1]==a[i]?h[a[i+1]]:c[a[i+1]]));
			dp[i+1][a[i]]=min(dp[i+1][a[i]],dp[i][j]+(a[i+1]==j?h[a[i+1]]:c[a[i+1]]));
		}
	int ans=inf;
	for(int i=0;i<=k;i++)
		ans=min(ans,dp[n][i]);
	cout<<ans<<'\n';
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false),
	cout.tie(nullptr);
	signed t;
	for(cin>>t;t--;solve());
	return 0;
}
```
如果觉得这题简单可以试试[这题的升级版](https://www.luogu.com.cn/problem/CF1799D2)，我们老师说这个蓝的发紫~~~

---

## 作者：Sun_pirf (赞：2)

# [CF1799D1 Hot Start Up (easy version)](https://www.luogu.com.cn/problem/CF1799D1)

## 题目大意
有两个 CPU 和若干类型的程序，处理第 $ i $ 个程序时，若你选择的 CPU 上一个处理的程序和 $ i $ 不是一个类型，那么会花费 $ cold_i $ ，否则花费 $ hot_i $ 。

求最小花费时间。

## 思路
### 题目类型
观察题面可得，此题为一道 DP 。  
遂考虑状态转移方程
### 状态转移方程
令 $ \operatorname {dp}_{i,j}$ 表示现在处理到了第 $ i $ 个程序，另一个 CPU 最后处理的程序类型为 $ j $ 。

所以可得。 

$$
dp_{i,a_{i-1}}= \min_{j\in[1,k]}{dp_{i-1,j}+val(a_i,j)}
$$

计算同时取最小值即可。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 5005
#define INF 1e18
int t,n,k,a[N],cold[N],hot[N],dp[N][N];
signed main() {
    cin>>t;
    for(int i=1;i<=t;i++){
	    cin>>n>>k;
	    for(int i=1;i<=n;i++){
	    	cin>>a[i];
		}
	    for(int i=1;i<=k;i++){
	    	cin>>cold[i];
		}
	    for(int i=1;i<=k;i++){
	    	cin>>hot[i];
		}
	    a[0]=-1;
	    for(int i=0;i<=n;i++)
	        for(int j=0;j<=k;j++)
	            dp[i][j]=INF;
	    dp[1][0]=cold[a[1]];
	    for(int i=2;i<=n;i++) {
	        for(int j=0;j<=k;j++) {
	            dp[i][j]=min(dp[i][j],dp[i-1][j]+(a[i]==a[i-1]?hot[a[i]]:cold[a[i]]));
	            dp[i][a[i-1]]=min(dp[i][a[i-1]],dp[i-1][j]+(a[i]==j?hot[a[i]]:cold[a[i]]));
	        }
	    }
	    int ans=INF;
	    for(int i=0;i<=k;i++)
	        ans=min(ans,dp[n][i]);
	    cout<<ans<<"\n";
	}
    return 0;
}
```

---

## 作者：ivyjiao (赞：1)

三倍经验：P11233，CF1799D1，CF1799D2。

以下 $b_i=cold_i,c_i=hot_i,m=k$。

---

由于这是 CCF（Codeforces Copying Foundation）的题，所以先看数据范围：$c_i\leq b_i$，记住这条性质，这意味着能选 $c_i$ 一定选 $c_i$。

- D0（$1\leq t\leq 500,1\leq n,m\leq 500,1\leq \sum n,\sum m \leq 500$，自己 yy 出来的东西，大概 CF1600 黄）：

这题一眼看上去，肯定是 dp，对于单组数据，考虑状态的设计：

设 $dp_{i,x,y}$ 为枚举到 $a_i$ 后，第一个 CPU 上一次运行的程序为 $x$，第二个 CPU 上一次运行的程序为 $y$ 时，最小的花费。dp 数组初始值为极大值，$dp_{0,x,y}$ 全是 $0$。

本题 $n,m\leq 500,1\leq \sum n,\sum m \leq 500$，而这个程序的时间复杂度是 $O(tnm^2)$ 的，空间复杂度是 $O(nm^2)$ 的，可以通过。

- D1（CF1900 蓝）：

D0 空间复杂度是 $O(nm^2)$ 的，直接炸飞，考虑优化空间。容易发现第一维 $i$ 可以就地滚动，于是 $dp_{x,y}$ 为枚举到 $a_i$ 后，第一个 CPU 上一次运行的程序为 $x$，第二个 CPU 上一次运行的程序为 $y$ 时，最小的花费，答案为 $\min \{dp_{x,y}\}$，这样空间复杂度就是 $O(m^2)$ 的了。

每次转移只有 $dp_{a_{i-1},y}$ 和 $dp_{x,a_{i-1}}$ 有值，其它的地方都是极大值，且只转移到 $dp_{x,a_i}$ 和 $dp_{a_i,y}$。考虑只转移这些值，其它的忽略掉，时间复杂度 $O(nm)$。

DP 转移式如下：

$$
\begin{cases}
  dp_{x,a_i}=\min\{dp_{x,y}+b_{a_i},dp_{x,a_i}+c_{a_i}\}\\
  dp_{a_i,y}=\min\{dp_{x,y}+b_{a_i},dp_{a_i,y}+c_{a_i}\}
\end{cases}
$$

本题 $n,m\leq 5000,1\leq \sum n,\sum m \leq 5000$，而这个程序的时间复杂度是 $O(tnm)$ 的，空间复杂度是 $O(m^2)$ 的，可以通过。

- D2（CF2100 蓝）：

D1 空间复杂度是 $O(m^2)$ 的，直接炸飞，考虑优化空间。我们之前说到：每次转移只有 $dp_{a_{i-1},y}$ 和 $dp_{x,a_{i-1}}$ 有值，其它的地方都是极大值，且只转移到 $dp_{x,a_i}$ 和 $dp_{a_i,y}$。那能不能以这个为突破口，把其余地方的空间全都优化掉呢？

答案是可以的。显然有 $dp_{x,y}=dp_{y,x}$，我们可以将 dp 状态压缩成一维，优化掉 $x$ 或 $y$（以下以 $x$ 为例）令 $dp_y$ 表示 $dp_{a_i,y}$，则转移变成如下：

$$
\begin{cases}
  dp_{a_i,a_{i-1}}=\min\{dp_{a_{i-1},y}+b_{a_i},dp_{a_{i-1},a_i}+c_{a_i}\}\\
  dp_{a_i,y}=dp_{a_{i-1},y}+b_{a_i}
\end{cases}
$$

再优化到：

$$
\begin{cases}
  dp_{a_{i-1}}=\min\{dp_y+b_{a_i},dp_{a_i}+c_{a_i}\}\\
  dp_{y}=dp_y+b_{a_i}
\end{cases}
$$

看完这个式子突然有一种很显然的的感觉（不然为什么 D1 D2 就差 200），感觉那些注意力惊人的大佬能一眼秒？

发现这个式子转移还是 $O(m)$ 的，怎么办？

~~注意到~~第二个式子在就地滚动，可以直接省略，用一个变量 $ans$ 来记录第二个式子的 $dp_y$ 加了多少，则有：

$$
\begin{cases}
  ans=ans+c_{a_i} & a_i=a_{i-1}\\
  ans=ans+b_{a_i} & a_i\neq a_{i-1}
\end{cases}
$$

此时式子只剩：

$dp_{a_{i-1}}=\min\{dp_y+b_{a_i},dp_{a_i}+c_{a_i}\}-c_{a_i}$

转移还是 $O(m)$？

对于 $dp_y$，我们记一个 $minn=\min\{dp_{a_{i-1}}\}$，式子变为：

$dp_{a_{i-1}}=\min\{minn+b_{a_i},dp_{a_i}+c_{a_i}\}-c_{a_i}$

转移 $O(1)$，总共时间复杂度 $O(tn)$，空间复杂度 $O(n+m)$ 可以通过。

代码（only D2）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+1;
int t,n,m,a[N],b[N],c[N],dp[N],minn,ans;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    memset(dp,0x3f,sizeof dp);
    while(t--){
        minn=0;
        ans=0;
        for(int i=1;i<=n;i++) dp[a[i]]=0x3f3f3f3f;
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=m;i++) cin>>b[i];
        for(int i=1;i<=m;i++) cin>>c[i];
        dp[0]=0;
        for(int i=1;i<=n;i++){
            if(a[i]==a[i-1]) ans+=c[a[i]];
            else{
                ans+=b[a[i]];
                dp[a[i-1]]=min(dp[a[i]]+c[a[i]],minn+b[a[i]])-b[a[i]];
                minn=min(minn,dp[a[i-1]]);
            }
        }
        cout<<minn+ans<<'\n';
    }
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

我唐完了。

记 $cold_i$ 为 $b_i$，$hot_i$ 为 $c_i$。

设 $l_i$ 为从 $i$ 开始往前找到的第一个位置满足数值与 $a_i$ 相等，$dp_i$ 表示考虑到 $i$ 个数时的最大价值。有个很显然的转移：$dp_i=dp_{l_i+1}+f(l_i+2,i-1)+c_{a_i}$，其中 $f(l,r)$ 表示把 $l\sim r$ 涂成同色的总贡献。就是让 $a_i$ 与 $a_{l_i}$ 配对做出贡献，把中间一段涂成与 $a_i$ 异色。答案即为 $dp_n$。好的我考场想到这里就没了，愣是被硬控之后怀疑自己思路有问题就放弃这个做法了，因为这样打过不了样例，我也没想出来这个转移有啥问题。很好笑的是 $i$ 可以不做贡献的，也即转移 $dp_i\gets dp_{i-1}+b_{a_i}$；还有之前那个方程当 $l_i=i-1$ 时，会有越界的问题，于是特判这种情况，改为 $dp_i=dp_{i-1}+c_{a_i}$ 就行了；最后是 $l_i$ 不存在的情况，那就直接 $dp_i=f(1,i)$。

时间复杂度：$O(Tn)$。

# Code

```cpp
#include<bits/stdc++.h>
long long dp[5005];
long long s[5005];
int b[5005],c[5005];
int vis[5005];
int lst[5005];
int a[5005];
int T,n,m;
int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);std::cout.tie(0);
	std::cin>>T;
	while(T--){
		std::cin>>n>>m;
		for(int i=1;i<=n;++i)
			std::cin>>a[i],lst[i]=vis[a[i]],vis[a[i]]=i;
		for(int i=1;i<=m;std::cin>>b[i++]);
		for(int i=1;i<=m;std::cin>>c[i++]);
		for(int i=1;i<=n;++i)
			s[i]=s[i-1]+(a[i]==a[i-1]?c[a[i]]:b[a[i]]);
		for(int i=1;i<=n;++i)
			dp[i]=std::min(dp[i-1]+b[a[i]],lst[i]?lst[i]==i-1?dp[i-1]+c[a[i]]:dp[lst[i]+1]+c[a[i]]+s[i-1]-s[lst[i]+1]:s[i]);
		std::cout<<dp[n]<<'\n';
		for(int i=1;i<=n;++i)vis[a[i]]=0;
	}
	return 0;
}

```

所以说有三道简单题的 CSP 我是怎么考出这么小丑的成绩的。

---

## 作者：FBW2010 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1799D1)

# 思路

由于每次决定只与上次两个 CPU 的状态有关，我们不妨考虑 **dp**。因为我们知道上一次运行的程序是哪一种，所以只需要考虑另一个 CPU 运行的程序是什么。设 $dp_{i,j}$ 为考虑到第 $i$ 个程序，另一个 CPU 上次运行的程序为 $j$ 的最短时间，便可以分情况转移：

+ 若 $a_i=a_{i-1}$，那么肯定是用上一次运行的 CPU 更优，于是 $dp_{i,j}=dp_{i-1,j}+hot_{a_i}$。

+ 若 $a_i \ne a_{i-1}$，那又得分两种：

	+ 对于 $dp_{i,a_{i-1}}$，那么这次使用的一定不是上次使用的 CPU，如果上次的另一个 CPU 上次运行的程序和这次运行的一样，便加上 $hot_{a_i}$，其他的便是 $cold_{a_i}$。转移方程便是 $dp_{i,a_{i-1}}=\min(dp_{i-1,a_i}+hot_{a_i},\min(dp_{i-1,t}(1 \le t \le k,t \ne a_i))+cold_{a_i})$。
    
   + 对于其他情况，肯定不会有相同的情况，于是 $dp_{i,j}=dp_{i-1,j}+cold_{a_i}$
   
这时，我们便拥有了一个时间复杂度 $O(nk^2)$，空间复杂度为 $O(nk)$ 的~~优秀算法~~。用**滚动数组**可以滚掉一维，而转移就相当于是将滚动数组区间修改，不难想到可以用**线段树**维护，时间复杂度便降为了 $O(n\log k)$，空间复杂度便降为了 $O(n+k)$，可以通过此题。

~~PS：貌似只有全局的修改，直接用变量存就可以了，复杂度还低一些，但本蒟蒻没想到。~~

# 代码

~~接下来便献上我又臭又长的线段树吧！~~

~~不开 long long 见祖宗！~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int t,a[N],c[N],h[N];
struct node{
	int l,r;
	long long min/*区间最小值*/,flag/*懒标记*/;
}tree[N*4];
void pu(int k){ //push_up
	tree[k].min=min(tree[k*2].min,tree[k*2+1].min);
}
void pd(int k){ //push_down
	if(tree[k].flag){
		tree[k*2].min+=tree[k].flag;
		tree[k*2].flag+=tree[k].flag;
		tree[k*2+1].min+=tree[k].flag;
		tree[k*2+1].flag+=tree[k].flag;
		tree[k].flag=0;
	}
}
void bui(int k,int l,int r){ //建树 
	tree[k].l=l;
	tree[k].r=r;
	tree[k].min=tree[k].flag=0;
	if(l==r){
		tree[k].min=1e15;
		return;
	}
	int mid=(l+r)>>1;
	bui(k*2,l,mid);
	bui(k*2+1,mid+1,r);
	pu(k);
}
void cha(int k,int x,int y,int v){ //区间加和 
	if(tree[k].l>y||tree[k].r<x)return;
	if(tree[k].l>=x&&tree[k].r<=y){
		tree[k].min+=v;
		tree[k].flag+=v;
		return;
	}
	pd(k);
	cha(k*2,x,y,v);
	cha(k*2+1,x,y,v);
	pu(k);
}
void cha2(int k,int x,long long v){ //单点赋值 
	if(tree[k].l>x||tree[k].r<x)return;
	if(tree[k].l==tree[k].r){
		tree[k].min=v;
		return;
	}
	pd(k);
	cha2(k*2,x,v);
	cha2(k*2+1,x,v);
	pu(k);
}
long long ask(int k,int x,int y){ //区间查询 
	if(tree[k].l>y||tree[k].r<x)return 1e15;
	if(tree[k].l>=x&&tree[k].r<=y){
		return tree[k].min;
	}
	pd(k);
	return min(ask(k*2,x,y),ask(k*2+1,x,y));
}
int main(){
	scanf("%d",&t);
	while(t--){
		int n,k;
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=k;i++){
			scanf("%d",&c[i]);
		}
		for(int i=1;i<=k;i++){
			scanf("%d",&h[i]);
		}
		bui(1,1,k+1);
		cha2(1,k+1,0);
		for(int i=1;i<=n;i++){
			if(a[i]==a[i-1]){
				cha(1,1,k+1,h[a[i]]);
			}
			else{
				cha2(1,a[i-1],min(ask(1,a[i],a[i])+h[a[i]],ask(1,1,k+1)+c[a[i]]));
				cha(1,1,k+1,c[a[i]]);
				cha(1,a[i-1],a[i-1],-c[a[i]]);
			}
		}
		printf("%lld\n",ask(1,1,k+1));
	}
	return 0;
}
```

---

## 作者：daitangchen2008 (赞：0)

## 分析：
因为题目中说只有两个 CPU，故设 $dp_{i,j}$ 为第一个 CPU 最后处理 $i$ 任务，第二个 CPU 最后处理 $j$ 任务。枚举时分类讨论即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+10;
int T,n,k;
int hot[N];
int cold[N];
int a[N];
int dp[N][N];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=k;i++)
			cin>>cold[i];
		for(int i=1;i<=k;i++)
			cin>>hot[i];
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				dp[i][j]=1e15;
		dp[1][0]=cold[a[1]];
		dp[0][1]=cold[a[1]];
		for(int i=2;i<=n;i++)
		{
			for(int j=0;j<i-1;j++)
			{
				int x=cold[a[i]];
				if(a[j]==a[i])
					x=hot[a[i]];
				dp[i][i-1]=min(dp[i][i-1],dp[j][i-1]+x);
			}
			for(int j=0;j<i-1;j++)
			{
				int x=cold[a[i]];
				if(a[j]==a[i])
					x=hot[a[i]];
				dp[i-1][i]=min(dp[i-1][i],dp[i-1][j]+x);
			}
			for(int j=0;j<i-1;j++)
			{
				int x=cold[a[i]];
				if(a[i]==a[i-1])
					x=hot[a[i]];
				dp[i][j]=min(dp[i][j],dp[i-1][j]+x);
			}
			for(int j=0;j<i-1;j++)
			{
				int x=cold[a[i]];
				if(a[i]==a[i-1])
					x=hot[a[i]];
				dp[j][i]=min(dp[j][i],dp[j][i-1]+x);
			}
		}
		int ans=1e15;
		for(int i=0;i<n;i++)
			ans=min(ans,min(dp[i][n],dp[n][i]));
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：TTpandaS (赞：0)

首先如果一个机器贡献是 $hot$，那么一定是与上一个和它类型相同的匹配，所以转移只需要考虑 $lst_{a_i}$ 即可。现在需要算出 $[lst_{a_i}+1,i]$ 全部为另一种颜色的贡献，发现 $[lst_{a_i}+2,i]$ 是好算的，$lst_{a_i}+1$ 的贡献是不知道的，但是此时 $lst_{a_i}$ 和 $lst_{a_i}+1$ 颜色是确定的，所以用 $lst_{a_i}+1$ 的 DP 值转移即可，DP 只需要记录这一位和上一位的颜色即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int T;
int n,k,a[N],cold[N],hot[N];
int sum[N],dp[N][2][2],lst[N];
void solve(){
	scanf("%lld %lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		lst[a[i]]=0;
	}
	for(int i=1;i<=k;i++){
		scanf("%lld",&cold[i]);
	}
	for(int i=1;i<=k;i++){
		scanf("%lld",&hot[i]);
	}	
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1];
		if(a[i]==a[i-1]){
			sum[i]+=hot[a[i]];
		}
		else{
			sum[i]+=cold[a[i]];
		}
	}
	if(n==1){
		printf("%lld\n",cold[a[1]]);
		return;
	}
	dp[2][1][0]=dp[2][0][1]=cold[a[1]]+cold[a[2]];
	if(a[1]==a[2]){
		dp[2][1][1]=dp[2][0][0]=cold[a[1]]+hot[a[2]];
	}
	else{
		dp[2][1][1]=dp[2][0][0]=cold[a[1]]+cold[a[2]];
	}
	lst[a[1]]=1;
	lst[a[2]]=2;
	for(int i=3;i<=n;i++){
		dp[i][0][0]=min(dp[i-1][0][0],dp[i-1][0][1])+cold[a[i]];
		dp[i][1][0]=min(dp[i-1][0][0],dp[i-1][0][1])+cold[a[i]];
		dp[i][0][1]=min(dp[i-1][1][0],dp[i-1][1][1])+cold[a[i]];
		dp[i][1][1]=min(dp[i-1][1][0],dp[i-1][1][1])+cold[a[i]];
		if(lst[a[i]]!=0){
			if(lst[a[i]]==i-1){
				dp[i][1][1]=min(dp[i][1][1],min(dp[i-1][1][0],dp[i-1][1][1])+hot[a[i]]);
				dp[i][0][0]=min(dp[i][0][0],min(dp[i-1][0][0],dp[i-1][0][1])+hot[a[i]]);
			}
			else{
				dp[i][0][1]=min(dp[i][0][1],dp[lst[a[i]]+1][1][0]+(sum[i-1]-sum[lst[a[i]]+1])+hot[a[i]]);
				dp[i][1][0]=min(dp[i][1][0],dp[lst[a[i]]+1][0][1]+(sum[i-1]-sum[lst[a[i]]+1])+hot[a[i]]);
			}
		}
		lst[a[i]]=i;
	}
	printf("%lld\n",min(min(dp[n][0][0],dp[n][0][1]),min(dp[n][1][0],dp[n][1][1])));
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		solve();
	} 
	return 0;
} 
```

---

## 作者：banned_gutongxing (赞：0)

一道特别简单的 DP 题。

定义：$f_{i,j}$ 表示现在已经处理了第 $i$ 个程序，另外一个 CPU 最后一个处理的程序类型为 $j$。

状态转移：
1. 首先每一个类型 $j$ 都可以将现在的程序放在前一个程序上方来得到，那么此时方程为 $f_{i,j}=f_{i,j}+val(i,i-1)$，其中 $val(x,y)$ 表示在第 $y$ 个程序放在第 $x$ 个程序上的代价。
2. 如果将第 $i$ 个程序放在另外一个 CPU 上运行，那么此时 $f_{i,a_{i-1}}=\min_{j\in[1,k]}\{ f_{i-1,j}+val(a_{i},j)\}$。

时间复杂度为 $O(nk^2)$。

此时在转移时记录一个最小值就行了。

---

## 作者：SamHJD (赞：0)

## [CF1799D Hot Start Up](https://www.luogu.com.cn/problem/CF1799D2)


### 题意

你有两个 CPU 和若干类型的程序，处理第 $i$ 个程序时，若你选择的 CPU 上一个处理的程序和 $i$ 是一个类型，那么会花费 $hot_i$，否则花费 $cold_i$。

求处理完所有程序的最小花费。

$n\le 3\times 10^5$。

### 解法

我们现在处理到了第 $k$ 个程序，其类型为 $t_k$。设 $f_{i,j}$ 表示当前 CPU 状态为一个处理完 $i$，一个处理完 $j$。

于是我们可以得到下列转移方程：

$$\begin{cases}f_{i,j}+cold_i\to f_{i,t_k},f_{t_k,j}\\f_{i,t_k}+hot_i\to f_{i,t_k}\\f_{t_k,j}+hot_i\to f_{t_k,j}\end{cases}$$

当 $t_k=t_{k-1}$ 时，我们肯定用 $hot_i$ 的花费放入同一个 CPU 处理。于是考虑 $t_k\ne t_{k-1}$ 的情况。

显然每次转移中 $i,j$ 里必有一个为 $t_{k-1}$，于是将方程转换：

$$\begin{cases}f_{i,t_{k-1}}+cold_i\to f_{t_k,t_{k-1}}\\f_{i,t_k-1}+cold_i\to f_{i,t_k}\\f_{t_{k-1},t_k}+hot_i\to f_{t_{k-1},t_k}\end{cases}$$

尝试再压一维，我们设 $f_i$ 表示 $f_{i,t_k}$，注意 $f_{i,t_k}$ 和 $f_{t_k,i}$ 是等价的。

于是再将方程转换：

$$\begin{cases}f_{i}(pre)+cold_i\to f_{t_{k-1}}\\f_i(pre)+cold_i\to f_i\\f_{t_k}(pre)+hot_i\to f_{t_{k-1}}\end{cases}$$

这里 $(pre)$ 指上一层的 $f$，即 $f_i$ 表示 $f_{i,t_{k-1}}$。

由于无法同时转移所有状态，我们不能直接转移。

* 对于第二条方程，我们给所有 $f$ 增加了 $cold_i$，但我们只需记录一个 $s$ 表示所有 $f$ 增加的和，而无需真正修改 $f_i$。

* 对于第一条方程，我们可以找出 $f$ 的最小值 $mn$，直接转移。

* 第三条方程两边下标已知，可以直接转移。

最终我们输出 $mn+s$ 即可。

### [代码](https://www.luogu.com.cn/paste/qkmyamx7)


---

## 作者：sjr3065335594 (赞：0)

一道很奇妙的 dp。

令 $f[i]$ 表示做完第 $i$ 个任务的最小花费。我们在定义以下内容：$las(x,y)$ 表示如果这个 CPU 上一个做的是 $x$ 的时候做 $y$ 所花费的时间，当且仅当 $a[x]$ 与 $a[y]$ 相等的时候取得 $hot[a[y]]$，否则为 $cold[a[y]]$；$cal(x,y)$ 表示一个 CPU 已经做完第 $x$ 个任务且依次从第 $x+1$ 个任务做到第 $y$ 个任务所花费的时间，$pre(x)$ 表示做到第 $i$ 个任务时做这个任务的 CPU 的上一个任务是什么。

那么此时，我们就可以进行转移了。

$$f[i]=\min\limits_{j<i}\{f[j]+cal(j+1,i)+las(pre(j),j+1)\}$$

可以理解为枚举是从哪一个地方分割，$j+1$ 是因为 $j$ 被 $f[j]$ 计算且 $j+1$ 被 $las()$ 计算。

到这里这题已经被解决掉了，只需要多增加一维记录一下 $pre(j)$ 就可以了，但是这题还有强化版，不可以通过，接下来思考对于更大的数据应该怎么做。

首先考虑如何计算 $cal()$。

令 $g(i)$ 表示 $las(i,i+1)$，则

$$cal(x,y)=\sum\limits_{i=x}^{y-1}g(i)$$

于是维护 $g$ 的前缀和。令

$$s(i)=\sum\limits_{i=0}^{i}g(i)$$

可得

$$cal(x,y)=s(y-1)-s(x-1)$$

所以原来的式子就可以化简了

$$f[i]=\min\limits_{j<i}\{f[j]+s(i-1)-s(j)+las(pre(j),j+1)\}$$

接下来想如何计算 $pre()$，$pre()$ 这个东西不好后边由前边转移，于是可以在转移 $j$ 的时候计算出来，将其替换为 $las(j,i+1)$。

所以

$$f[i]=\min\limits_{j<i}\{f[j]+s(i-1)-s(j)+las(j,i+1)\}$$

由于这个 $\min$ 只和 $j$ 有关，所以可以把没有 $j$ 的放外边。

$$f[i]=\min\limits_{j<i}\{f[j]-s(j)+las(j,i+1)\}+s(i-1)$$

这一个式子里边，$f[j]-s(j)$ 是可以边做边处理的，关键在于 $las(j,i+1)$，可以将其按照题目中意思更换。

$$las(j,i+1)=\min\begin{cases}hot_{i+1}&a[j]=a[i+1]\\cold_{i+1}&\text{otherwise}\end{cases}$$

带回原式子

$$f[i]=s(i-1)+\min\begin{cases}f[j]-s(j)+hot_{i+1}&a[j]=a[i+1]\\f[j]-s(j)+cold_{i+1}&\text{otherwise}\end{cases}$$

于是边做边处理出 $hot$ 和 $cold$ 两种情况的最小值即可，时间复杂度 $O(n)$，可以通过本题。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp(x,y) make_pair(x,y)
#define CLR(a,x) memset(a,x,sizeof(a))
#define int long long
//#define int __int128
using namespace std;
const int N=3e5+5;
const int M=1e6+5;
const int INF=2e9+5;
int t,n,k,a[N],hot[N],cold[N];
ll sum[N],f[N],minn[N];
ll calc(int x,int y) {
    if(a[x]==a[y])return hot[a[y]];
    return cold[a[y]];
}
signed main() {
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
    scanf("%lld",&t);
    while(t--) {
        scanf("%lld%lld",&n,&k);
        a[n+1]=hot[n+1]=cold[n+1]=0;
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]),sum[i]=f[i]=0;
        for(int i=1;i<=k;i++)
            scanf("%lld",&cold[i]),minn[i]=1e17;
        for(int i=1;i<=k;i++)
            scanf("%lld",&hot[i]);
        sum[0]=calc(0,1);
        for(int i=1;i<=n;i++)
            sum[i]=sum[i-1]+calc(i,i+1);
        ll res=0;
        for(int i=1;i<=n;i++) {
            f[i]=sum[i-1]+res+cold[a[i+1]];
            f[i]=min(f[i],minn[a[i+1]]+hot[a[i+1]]+sum[i-1]);
            minn[a[i]]=min(minn[a[i]],f[i]-sum[i]);
            res=min(res,f[i]-sum[i]);
        }
        printf("%lld\n",f[n]);
    }
    return 0;
}
/*
1
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
*/
```


---

