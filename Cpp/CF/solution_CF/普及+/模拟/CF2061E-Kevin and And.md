# Kevin and And

## 题目描述

Kevin 有一个长度为 $ n $ 的整数序列 $ a $。同时，Kevin 拥有 $ m $ 种魔法类型，其中第 $ i $ 种魔法可以用整数 $ b_i $ 表示。

Kevin 最多可以执行 $ k $ 次（可能为零）魔法操作。每次操作中，Kevin 可以执行以下步骤：

- 选择两个索引 $ i $（$ 1 \leq i \leq n $）和 $ j $（$ 1 \leq j \leq m $），然后将 $ a_i $ 更新为 $ a_i\ \&\ b_j $。此处 $ \& $ 表示[位与操作](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

请计算在执行最多 $ k $ 次操作后，序列 $ a $ 中所有数的最小可能总和。

## 说明/提示

第一个测试用例中，一种可能的操作方式为：

1. 将 $ a_1 $ 更新为 $ a_1\ \&\ b_1 $，序列变为 $ [5] $。
2. 将 $ a_1 $ 更新为 $ a_1\ \&\ b_3 $，序列变为 $ [1] $。

第二个测试用例中，一种可能的操作方式为：

1. 将 $ a_1 $ 更新为 $ a_1\ \&\ b_3 $，序列变为 $ [1, 6] $。
2. 将 $ a_2 $ 更新为 $ a_2\ \&\ b_3 $，序列变为 $ [1, 2] $。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1 3 2
7
5 6 3
2 3 2
5 6
5 6 3
10 2 5
3 1 4 1 5 9 2 6 5 3
7 8
5 1 0
1073741823 1073741823 1073741823 1073741823 1073741823
1073741823
1 1 0
0
0```

### 输出

```
1
3
11
5368709115
0```

# 题解

## 作者：Imerance1018 (赞：4)

好题。感觉蓝差不多。
### Description

给定长为 $n$ 的序列 $a_1,a_2,...,a_n$，长为 $m$ 的序列 $b_1,b_2,...,b_m$。可以操作 $k$ 次，每次操作选取 $i$ 和 $j$ 满足 $1 \le i \le n$ 且 $1 \le j \le m$，并将 $a_i$ 赋值为 $a_i \And b_j$。要求最小化 $\sum_{i=1}^{n}{a_i}$ 并输出。（$\And$ 指按位与操作）

数据范围为 $1 \le n \le 10^5$，$\color{red}1 \le m \le 10$，$0 \le k \le mn$，$0 \le a_i < 2^{30}$，$0 \le b_i < 2^{30}$。

### Solution

注意到 $m$ 非常小。

所以可以通过状态压缩处理出 $num_{i,j}$ 表示 $a_i$ 经过 $j$ 次操作后可能的最小值。特别地，$num_{i,0}=a_i$。

再不妨定义 $res_{i,j}=num_{i,j}-num_{i,j-1}$ ,表示 $a_i$ 的第 $j$ 次操作使它减小了多少。

显然，对于所有的 $j > 1$，只有选了 $res_{i,j-1}$ 进入答案，才能选 $res_{i,j}$。

那么问题似乎转化成了一个类似树上背包的东西（有依赖性）。

但由于 $k$ 过大，做不了。

关键的地方来了：

由于按位与的性质，$num_{i,j}$ 对于每个 $i$ 都是单调不上升的。

那我们就能进一步发现，$res_{i,j}$ 对于每个 $i$ 单调不上升。（其实 $num_{i,j}$ 是个凸函数，而 $res_{i,j}$ 是它的差分序列，这本质上是凸函数差分序列的性质，但观察也能观察出来）

所以，可以贪心地考虑，直接选取最小的 $k$ 个 $res_{i,j}$ 加入答案即可。

这样也满足了依赖性：对于任意 $j > 1$，如果选了 $res_{i,j}$，那么由于 $res_{i,j-1} \le res_{i,j}$，所以 $res_{i,j-1}$ 一定被选到了。

完结撒花。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,M=15,K=(1ll<<31)-1;
int T,n,m,k,a[N],b[M],val[N],num[N][M],res[N*M],ans;
//代码中将 res 压成一维，便于排序
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			for(int j=1;j<=m;j++)num[i][j]=1e18;
			num[i][0]=a[i];
		}
		for(int i=1;i<=m;i++)cin>>b[i];
		for(int i=0;i<(1<<m);i++)
		{
			val[i]=K;
			for(int j=1;j<=m;j++)
				if(i&(1<<(j-1)))val[i]&=b[j];
		}
		for(int i=1;i<=n;i++)
			for(int j=0;j<(1<<m);j++)
				num[i][__builtin_popcount(j)]=min(num[i][__builtin_popcount(j)],val[j]&a[i]);
                //强烈推荐 __builtin_popcount
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				res[(i-1)*m+j]=num[i][j]-num[i][j-1];
		sort(res+1,res+n*m+1);
		ans=0;
		for(int i=1;i<=n;i++)ans+=a[i];
		for(int i=1;i<=k;i++)ans+=res[i];
		cout<<ans<<endl;
	}
	return 0;
}
``````

---

## 作者：yvbf (赞：3)

![](bilibili:BV1MuwverEdQ?t=1453)

---

## 作者：postpone (赞：3)

从一些特殊的情况入手：

1. 如果只能操作 $1$ 次：排列组合 $a$ 和 $b$ 的元素，计算出收“收益”最大的 $(i, j)$ 组合。此处的收益即，与 $b_j$ 做与运算后，$a_i$ 减小了多少。

2. 如果能操作 $m$ 次，但对 $a$ 中每个元素只能操作 $1$ 次：把上一步应用到 $a$ 中的每个元素。

3. $a$ 中只有一个元素，我想知道操作 $x$ 次的最优情况：可以用状态压缩的方式表示对 $b$ 中哪些元素进行操作，状态二进制数中 $1$ 的个数即为操作的次数。用一个数组维护操作次数到收益的映射，最后该数组中的结果一定是最优的，因为滚过了所有情况。

最后推广开来，对于 $a$ 中每个元素，如上述第三点，我们需要处理出操作次数带来的收益。最后将所有收益排序，取前 $k$ 个，就是想要的结果了。

这个“收益”该怎么表示出来呢？可以用差分的形式。

实现层面，由与运算的结合律，我们能先预处理 $b$ 内部的操作结果，最后合到 $a$ 中元素上，换句话说就是把 $x$ 次操作压成 $1$ 次；使用 $\texttt{std::popcount()}$ 获取状态数中 $1$ 的个数。

总复杂度 $O(n\times 2^m)$。

```cpp
constexpr int inf = (1 << 30) - 1; // inf 设置为值域的上界

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    vector<int> f(1 << m, inf);
    for (int s = 0; s < (1 << m); s++) {
        for (int i = 0; i < m; i++) {
            if (s >> i & 1) {
                f[s] &= b[i];
            }
        }
    }

    vector<int> c;
    c.reserve(n * m);

    for (auto x : a) {
        vector<int> h(m + 1, inf);
        for (unsigned s = 0; s < (1 << m); s++) {
            int t = popcount(s);
            h[t] = min(h[t], x & f[s]);
        }
        for (int i = 0; i < m; i++) {
            c.push_back(h[i] - h[i + 1]);
        }
    }

    ranges::sort(c, greater());

    ll ans = accumulate(a.begin(), a.end(), 0ll) -
             accumulate(c.begin(), c.begin() + k, 0ll);
    cout << ans << "\n";
}
```

---

## 作者：rubbishZZZ (赞：2)

## CF2061E Kevin and And



#### 题意：

- 给定 $a_1\sim a_n,b_1\sim b_m$，一次操作可以选择 $(i,j)$，将 $a_i\leftarrow a_i\&b_j$，最小化 $k$ 次操作后的 $\sum\limits_{i=1}^n a_i$。
- $n\leq 100000,m\leq 10,0\leq V\lt 2^{30}$。



#### 解法：

- 这种题大胆猜测凸性。

  设 $a_{i,j}$ 表示 $a_i$ 经过 $j$ 次操作后比初始时减少的最大值，我们猜测 $a_{i,j}$ 关于 $j$ 是凸的，即 $a_{i,j}-a_{i,j-1}\geq a_{i,j+1}-a_{i,j}$。

  证明：考虑 $a_{i,j}$ 比 $a_{i,j-1}$ 少的最高位 $p$，则 $a_{i,j}-a_{i,j-1}\geq 2^p$ ，若 $a_{i,j+1}-a_{i,j}\gt a_{i,j}-a_{i,j-1}$，则 $a_{i,j+1}-a_{i,j}\gt 2^p$。而 $\sum\limits_{j=0}^{p-1}2^j\lt 2^p$，则一定减少了比 $p$ 更高的位 $q$。而 $\sum\limits_{i=0}^{p}2^i\lt 2^q$，则在第 $j$ 次操作时减掉 $2^q$ 位置使 $a_{i,j}$ 更大，故非最优解，凸性成立。

  对于每个 $a_i$，只有前 $m$ 次操作有效，我们 $O(n2^m)$ 求出每个 $j\leq m$ 的 $a_{i,j}$，做差分得到 $b_{i,j}$。

  那么我们相当于要选择每个 $b_{i,*}$ 的一个前缀，使得总共选择 $k$ 个数，和最大。

  由于 $b_{i,j}\geq b_{i,j+1}$，则直接对于所有 $b_{i,j}$ 选择前 $k$ 大即为正确答案。

  可以直接排序，复杂度 $O(nm\log(nm)+n2^m)$。

  可以用堆维护目前每个 $b_{i,*}$ 中最大的未选值，复杂度 $O((n+k)\log n+n2^m)$。

  由于我们不关心具体顺序，只关心前 $k$ 大，因此可以使用 STL 的 nth_element 做到 $O(nm+n2^m)$。



#### 代码：

```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
//#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

char buf[1<<20],*p1,*p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}

const int N=100005;
int n,m,K,a[N],b[1<<11],bpp[1<<11],f[N*10],mx[11],tot;
ll ans;

bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	b[0]=(1<<30)-1;
	rep(S,1,1023)bpp[S]=bpp[S>>1]+(S&1);
	for(int T=read();T--;){
		n=read(),m=read(),K=read(),ans=0;
		rep(i,1,n)ans+=(a[i]=read());
		rep(i,0,m-1)b[1<<i]=read();
		rep(S,1,(1<<m)-1){
			int x=S&-S;
			b[S]=b[S^x]&b[x];
		}
		tot=0;
		rep(i,1,n){
			rep(j,0,m)mx[j]=0;
			rep(S,1,(1<<m)-1){
				chkmax(mx[bpp[S]],a[i]-(a[i]&b[S]));
			}
			per(j,m,1)f[++tot]=(mx[j]-=mx[j-1]);
		}
		int lim=n*m;
		nth_element(f+1,f+lim-K+1,f+lim+1);
		rep(i,lim-K+1,lim)ans-=f[i];
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Yorg (赞：2)

# [CF2061E Kevin and And](https://www.luogu.com.cn/problem/CF2061E)

## 思路
> 有两个集合 $ A $ 和 $ B $。  
你可以做至多 $ k $ 次操作，每次选择 $ a_i \in A, b_j \in B $ 并令 $ a_i \gets a_i \& b_j $。  
问操作结束后 $ A $ 所有数之和的最小值。

因为多操作一定不劣，所以我们直接钦定操作 $ k $ 次。

首先，如果令每次操作的贡献为 $ val_i $，最终答案为

$$
ans = \sum_{i=1}^{n} a_i - \sum_{i=1}^{k} val_i.
$$

进一步地，我们把贡献分类，修改定义，对于数 $ a_i $ 的操作的贡献我们记为 $ val_i $。  
最终答案为

$$
ans = \sum_{i=1}^{n} a_i - \sum_{i=1}^{n} val_i.
$$

再一次修改贡献的定义，我们令 $ val_{i,j} $ 表示对于数 $ i $ 进行 $ j $ 次操作的最优贡献。  
考虑到 $ m $ 很小，直接枚举所有状态即可，$ \mathcal{O}(n 2^m) $ 计算出 $ val $ 数组。

这个时候容易想到 dp，可惜复杂度过高。

考虑一个性质：

$$
\text{记 } \varphi(i, j) = val_{i, j + 1} - val_{i, j} \\
\text{有 } \varphi(i, j) \geq \varphi(i, j + 1)
$$

即 $ val_i $ 这一函数具有凸性。  
给出官方题解对其的证明，接下来用 $ g(x) $ 表示 $ vai_i(x) $。

> **引理**：函数 $ g $ 是凸的，即对于所有 $ i $ （$ 1 \leq i < m $），不等式 $ 2g(i) \leq g(i-1) + g(i+1) $ 成立。
>
> **证明**：设 $ f(S) $ 是与 $ g(i-1) $ 最小值对应的值，$ f(T) $ 是与 $ g(i+1) $ 最小值对应的值。假设第 $ w $ 位是 $ f(S) $ 和 $ f(T) $ 不同的最高位。
>
> 我们总是能找到一个操作 $ y \in T \setminus S $，将 $ g(i-1) $ 中的第 $ w $ 位变为 0。  
> 在这种情况下，我们有：
>
> $$
> g(i - 1) - f(S \cup \{ y \}) \geq 2^w.
> $$
>
> 此外，由于 $ f(S \cup \{ y \}) $ 和 $ g(i+1) $ 不同的最高位不大于 $ w-1 $，我们有：
>
> $$
> f(S \cup \{ y \}) - g(i + 1) \leq 2^w.
> $$
>
> 将这两个不等式结合得到：
>
> $$
> 2 g(i) \leq 2 f(S \cup \{ y \}) \leq g(i - 1) + g(i + 1),
> $$
>
> 从而证明了 $ g $ 的凸性。

由此，你可以知道，如果我们直接对 $ \varphi $ 用大根堆维护最大值，然后贪心地选取最大值即可，因为上面提到的那个性质，这个贪心显然是成立的。

更形象地，我们把 $ \varphi $ 表示出来：

[![pEAKyfs.png](https://s21.ax1x.com/2025/01/21/pEAKyfs.png)](https://imgse.com/i/pEAKyfs)

相当于用堆维护指针所指的位置的最大值，然后如果使用了这一位，就把指针后移。

---

## 作者：aulive (赞：2)

注意到 $m\le10$，联想到对每个 $a_i$ 状压得到经过 $k$ 次操作后得到的最小值，令这个最小值为 $val_{i,j}$。

将 $val_{i,j}$ 与 $val_{i,j-1}$ 作差，表示最优选择下 $a_i$ 选的第j个来的差量。

然后这个问题看起来很像个依赖背包，但细推一下就会发现 $val_{i,j}$ 这玩意是随着 $j$ 单调递减的，证明考虑反证法即可。

直接贪心，答案就是 $\sum a_i$ 减去前 $k$ 大的差量即可。
```cpp
#include<bits/stdc++.h>
#define popcount __builtin_popcount
#define ll long long
using namespace std;
const int maxn=1e5;
int n,m,k,a[maxn+5],b[maxn+5],dp[maxn+5][11],f[1<<10],pre[1<<10];
int val[maxn*10+5],tot;
int cmp(int x,int y){return x>y;}
void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=1;i<=n*m;i++)val[i]=2e9;
	for(int S=1;S<(1<<m);S++){
		pre[S]=(1ll<<31)-1;
		for(int i=1;i<=m;i++)if((S>>i-1)&1)pre[S]&=b[i];
	}
	for(int i=1;i<=n;i++){
		f[0]=a[i];
		for(int S=1;S<(1<<m);S++){
			f[S]=a[i]&pre[S];
			int pos=(i-1)*m+popcount(S);
			val[pos]=min(val[pos],f[S]);
		}
		for(int j=i*m;j>(i-1)*m+1;j--)val[j]=val[j-1]-val[j];
		val[(i-1)*m+1]=a[i]-val[(i-1)*m+1];
	} 
	int tot=n*m;
	sort(val+1,val+1+tot,cmp);
	long long ans=0;
	for(int i=1;i<=n;i++)ans+=a[i];
	for(int i=1;i<=k;i++)ans-=val[i];
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test;
	cin>>test;
	while(test--)solve();
	return 0;
}
//ÏÈÔ¤´¦Àí³öÀ´a[i]²Ù×÷j´Îºó×î¶à¼õÉÙµÄÊýÁ¿O(n*1024) 
//È»ºó±³°ü£¿ 
//·¢ÏÖÎïÆ·ÈÝÁ¿ºÜÉÙ,
```

---

## 作者：Defy_HeavenS (赞：0)

首先求出对于每一个 $a_i$ 它进行 $j$ 次所能得到的最小可能值 $f_{i,j}$，因为 $m\le10$ 所以这个可以用状压求，首先预处理出每个操作集合的集合与（根据结合律可以先算每个操作的与，最后再与给 $a_i$），然后 $\mathcal{O}(n2^m)$ 求。注意，这里不能贪心地 DP。

求出这个之后就可以有一个 naive 的 DP，设 $dp_{i,j}$ 表示考虑 $a_1,a_2,\dots,a_i$，进行 $j$ 次操作的最小可能和，时间复杂度 $\mathcal{O}(n^2m^2)$。

然后是这题的难点，我们需要发现对于每一个 $i\le n,j\le m$ 满足 $f_{i,j+2}-f_{i,j+1}\le f_{i,j+1}-f_{i,j}$。设 $a=f_{i,j+1}-f_{i,j},b=f_{i,j+2}-f_{i,j+1}$，代入式子为 $b\le a$。设 $x$ 为 $a$ 的最高位，$y$ 为 $b$ 的最高位。

感性反证一下，若 $b>a$，则有两种情况：
1. $y>x$，那么在 $f_{i,j+2}$ 中的操作集合中一定有一个数 $u$ 且 $u$ 的第 $y$ 为为 $0$，而在 $f_{i,j+1}$ 中的操作集合中也可以用 $u$ 替换掉一个元素，从而使 $a$ 的最高位 $\ge y$。
2. $y=x$，这种情况实际上是不存在的，因为在 $f_{i,j+1}$ 的操作集合中已经把 $x$ 这位设为 $0$ 了，而差值是有一个为 $1$ 的位减去一个为 $0$ 的位，所以在 $b$ 的最高位不可能等于 $x$。

我们每次进行一次操作都会让值小一点，但是每次变小的值也会越来越小，$a_i$ 第 $j$ 此变小的值为 $f_{i,j}-f_{i,j-1}$。所以设一个元素为所有差值（$f_{i,j}-f_{i,j-1}$）的集合，取前 $k$ 小。

```cpp
#include<bits/stdc++.h>
#define umap unordered_map
#define uset unordered_set
#define mset multiset
#define yes cout<<"Yes\n"
#define no cout<<"No\n"
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define tmax(a,b) (a)=max((a),(b))
#define tmin(a,b) (a)=min((a),(b))

using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;

const LL N=1e5+5,M=10+5,Pw=(1<<10)+5,Inf=1e18+7;
LL n,m,k,a[N],b[N],f[N][M],val[Pw];

void solve(){
	cin>>n>>m>>k;
	for(LL i=1;i<=n;i++){
		for(LL j=1;j<=m;j++){
			f[i][j]=Inf;
		}
	}
	LL ans=0;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
		ans+=a[i];
		f[i][0]=a[i];
	}
	for(LL i=1;i<=m;i++){
		cin>>b[i];
	}
	vector<LL>arr;
//	for(LL i=1;i<=n;i++){    //贪心错误做法
//		f[i][0]=a[i];
//		for(LL j=1;j<=m;j++){
//			LL mi=Inf;
//			for(LL k=1;k<=m;k++){
//				tmin(mi,f[i][j-1]&b[k]);
//			}
//			f[i][j]=mi;
//			arr.pb(f[i][j]-f[i][j-1]);
//		}
//	}
	for(LL S=1;S<(1<<m);S++){
		val[S]=-1;
		for(LL i=0;i<m;i++){
			if(S>>i&1){
				if(~val[S]){
					val[S]&=b[i+1];
				}else{
					val[S]=b[i+1];
				}
			}
		}
	}
	for(LL i=1;i<=n;i++){
		for(LL S=1;S<(1<<m);S++){
			tmin(f[i][__builtin_popcount(S)],val[S]&a[i]);
		}
	}
	for(LL i=1;i<=n;i++){
		for(LL j=1;j<=m;j++){
			arr.pb(f[i][j]-f[i][j-1]);
		}
	}
	sort(all(arr));
	for(LL i=0;i<k;i++){
		ans+=arr[i];
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	LL t=1;cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：ThisIsLu (赞：0)

好题。

注意到 $m$ 只有 $10$，所以可以处理出每一个 $a_i$ 操作 $j$ 次的最大代价，设为 $g_{i,j}$。

然后就转成了背包，然而 $k$ 太大了做不了。

然后考虑拆物品，得到了一个有依赖关系的树形背包，每一个物品的贡献为 $\Delta_{i,j}=g_{i,j}-g_{i,j-1}$。

然后我们猜 $g_{i,j}$ 是凸的，就可以直接无视依赖关系贪心选。因为如果是凸的，$\Delta_{i,j}\ge\Delta_{i,j-1}$，选了 $\Delta_{i,j}$，$\Delta_{i,j-1}$ 必然被选上。

感性理解一下一开始几次操作能造成很大的影响，但后面很多操作被无效化了。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
const int N=1e5;
template<typename T>
T lowbit(const T x){
    return x&(-x);
}
int a[N+5][11],dp[1<<10],b[10],tmp[N*10+5];
string stra,strb;
void solve(){
    cin>>n>>m>>k;
    long long ans=0;
    for(int i=1;i<=n;i++) cin>>a[i][0];
    for(int i=0;i<m;i++) cin>>b[i];
    int cnt=0;
    for(int i=1;i<=n;i++){
        ans+=(dp[0]=a[i][0]);
        for(int j=1;j<=m;j++) a[i][j]=a[i][0];
        for(int j=1;j<(1<<m);j++) a[i][__popcount(j)]=min(a[i][__popcount(j)],dp[j]=dp[j^lowbit(j)]&b[__lg(lowbit(j))]);

        for(int j=m;j>=1;j--){
            tmp[++cnt]=(a[i][j]-=a[i][j-1]);
        }
    }
    sort(tmp+1,tmp+cnt+1);
    for(int i=1;i<=k;i++){
        ans+=tmp[i];
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T=1;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：UniGravity (赞：0)

也是妙妙题，但是因为【】调了好久。

考虑 $m$ 很小能带来什么：由于多个操作作用到一个值上并不好处理，考虑枚举所有 $2^m$ 种可能的操作，算出 $w_{i,j}$ 代表对于 $a_i$ 进行 $j$ 次操作能从和上减去多少。这个需要稍微精细实现一下做到 $O(n2^m)$ 而不是 $O(nm2^m)$。

直接做还是不太好处理，考虑对 $w_i$ 差分一下，变成了多进行一次操作产生的额外贡献。

发现差分出来的 $w_i$ 一定单调不增，因为新操作一次能产生的贡献越来越小。直接对差分出来的所有数排序取前 $k$ 大，则选中了 $i$ 的 $j$ 操作，所有小于 $j$ 的操作已经被选择过了。

时间复杂度 $O(n2^m+nm\log(nm))$。

---

