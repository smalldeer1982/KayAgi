# Road of the King

## 题目描述

有一个 $n$ 个点的图，目前一条边都没有。

有一个人在 $1$ 号点要进行 $m$ 次移动，终点不必是 $1$ 号点，假设第 $i$ 次从 $u$ 移动到 $v$，那么在 $u$ 与 $v$ 之间连一条有向边。

问有多少种序列能满足：最终 $n$ 个点组成的图是一个强连通图。答案对 $10^9+7$ 取模。

## 说明/提示

$1 \leq n,m \leq 300$

## 样例 #1

### 输入

```
3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
150 300```

### 输出

```
734286322```

## 样例 #3

### 输入

```
300 150```

### 输出

```
0```

# 题解

## 作者：aoweiyin (赞：9)

~~神仙题不会做.jpg(我才不会告诉你我是参考了[官方题解](https://cf16-final.contest.atcoder.jp/data/other/cf16-final/editorial.pdf)了的QAQ~~，但它是绝对的DP好题！！

~~P.S.DALAO要做好本小蒟蒻给您唠叨的准备啦QAQ~~

#### 分类：计数DP+图论

#### 题目大意：

有一个人在1号点，并按一个长度为m的序列进行移动，且按他的移动建有向边。问有多少种序列能满足：n个点组成的图是一个强连通图

#### 分析：

因为建边的特性，所以下一次移动的终点会影响图的性质，然后我们可以根据这个来转移。

接下来是DP状态设计。因为起点始终是1，所以，我们可以把1号点作为参照，即只要连上1号点，当前图绝对是强连通（收集性质

除此之外，只要从当前点向之前的点建边，绝对会形成强连通子图（收集性质

#### 题解：

整理一下，再运用您强大的**思维能力**，发现可以这样设计状态：

$dp[i][j][k]$:走到第i步，已经扩展了j种点，包含1号点的最大的强连通子图的点数为k时的方案。（是不是有点强？

所以当移动时，就会有三种情况：(起点都在上次的终点那里，所以只考虑终点的情况

1. 终点属于未拓展的点
2. 终点在不包含1的强连通里
3. 终点在包含1的强连通里

好，据此，我们可以得到转移：（刷表
$$dp[i+1][j+1][k]+=dp[i][j][k]*(n-j)$$
$$dp[i+1][j][k]+=dp[i][j][k]*(j-k)$$
$$dp[i+1][j][j]+dp[i][j][k]*k$$

（自己可以再想想细节QAQ


#### 总结：

OI题性质最重要啊！！！

#### 尾声：

也许博主的阐述忽略了一些细节，若读者您发现了，希望提醒一下哟！！欢迎指出✿✿ヽ(°▽°)ノ✿

#### 差点忘放代码了，其实很简单：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define RG register
#define LL long long
using namespace std;
const LL mod=1e9+7;
int n,m;
LL dp[305][305][305];
inline int read(){
	char ch=getchar(); int x=0, f=1;
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1; ch=getchar();	}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0'; ch=getchar();	}
	return x*f;}
int main()
{
//	freopen("Road of the King.in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(); m=read();
	dp[0][1][1]=1;
	for(RG int i=0;i<m;i++)
	 for(RG int j=1;j<=n;j++)
	  for(RG int k=1;k<=j;k++)
	  {
			(dp[i+1][j+1][k]+=dp[i][j][k]*(n-j))%=mod;
			(dp[i+1][j][k]+=dp[i][j][k]*(j-k))%=mod;
			(dp[i+1][j][j]+=dp[i][j][k]*k)%=mod;
	  }
	printf("%lld\n",dp[m][n][n]);
	//fclose(stdin); fclose(stdout);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：2)

## 分析

考虑 DP。

这里有个比较显然的结论：若这 $n$ 个点组成的图为强连通图，则只需满足从 $2 \sim n$ 出发都能够到达 $1$。

证明简单。因为我们是从 $1$ 开始走的，所以 $1$ 与其它所有点联通。那么如果点 $x$ 出发能够到达 $1$，则也能到达其它任意一个点。

定义状态函数 $f_{i,j,k}$ 表示从 $1$ 出发走了 $i$ 步，经过了 $j$ 个点，其中有 $k$ 个点能够到达 $1$。

有 $3$ 种情况：

1. 到达 $1$ 个走过的点，强连通点数没有变化。有 $j-k$ 种选择。
2. 到达 $1$ 个强连通的点，则当前所有走过的点都会与 $1$ 强连通。有 $k$ 种选择。
3. 到达 $1$ 个没走过的点，强连通点数没有变化。有 $n-j$ 种选择。

然后就没了。初始状态 $f_{0,1,1}=1$，答案即为 $f_{m,n,n}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=305,p=1e9+7;
int n,m;
int f[N][N][N];

il void solve(){
    n=rd,m=rd,f[0][1][1]=1;
    for(re int i=0;i<m;++i)
    for(re int j=1;j<=n;++j)
    for(re int k=1;k<=j;++k){
        f[i+1][j][k]=(f[i+1][j][k]+f[i][j][k]*(j-k)%p)%p;
        f[i+1][j][j]=(f[i+1][j][j]+f[i][j][k]*k%p)%p;
        f[i+1][j+1][k]=(f[i+1][j+1][k]+f[i][j][k]*(n-j)%p)%p;
    }
    printf("%lld\n",f[m][n][n]);
    return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

## 作者：rui_er (赞：2)

注意到当前移动到的位置并不重要，重要的是经过的点数和 $1$ 所在强连通分量大小，因此把它们放进状态里：设 $f_{i,j,k}$ 表示进行 $i$ 次移动，经过了 $j$ 个不同的点，此时 $1$ 所在的强连通分量大小为 $k$ 的方案数。

考察下一次移动到的点的情况：

- 没有访问过：共有 $n-j$ 种此类点，且此时不在 $1$ 所在强连通分量，因此有转移 $f_{i+1,j+1,k}\gets f_{i,j,k}\times(n-j)$。
- 访问过，不在 $1$ 所在强连通分量：共有 $j-k$ 种此类点，此时依然不在 $1$ 所在强连通分量，因此有转移 $f_{i+1,j,k}\gets f_{i,j,k}\times(j-k)$。
- 访问过，且在 $1$ 所在强连通分量：共有 $k$ 种此类点，此时所有访问过的点都并入 $1$ 所在强连通分量，因此有转移 $f_{i+1,j,j}\gets f_{i,j,k}\times k$。

时间复杂度 $O(n^2m)$。

```cpp
// Problem: Road of the King
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_codefestival_2016_final_f
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
    return x < mod ? x : x - mod;
}

template<int mod>
struct Modint {
    unsigned int x;
    Modint() = default;
    Modint(int x) : x(x) {}
    friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
    friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
    friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
    friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
    friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
    friend Modint operator^(Modint a, int k) {Modint ans = 1; for(; k; k >>= 1, a *= a) if(k & 1) ans *= a; return ans;}
    friend Modint operator~(Modint a) {return a ^ (mod - 2);}
    friend Modint operator/(Modint a, Modint b) {return a * ~b;}
    friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
    friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
    friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
    friend Modint& operator^=(Modint& a, int k) {return a = a ^ k;}
    friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
    friend Modint& operator++(Modint& a) {return a += 1;}
    friend Modint operator++(Modint& a, int) {Modint b = a; ++a; return b;}
    friend Modint& operator--(Modint& a) {return a -= 1;}
    friend Modint operator--(Modint& a, int) {Modint b = a; --a; return b;}
    friend Modint operator-(Modint a) {return a.x == 0 ? 0 : mod - a.x;}
    friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
    friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

typedef Modint<1000000007> mint;

const int N = 305;

int n, m;
mint dp[N][N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    dp[0][1][1] = 1;
    rep(i, 0, m - 1) {
        rep(j, 1, n) {
            rep(k, 1, j) {
                dp[i + 1][j + 1][k] += dp[i][j][k] * (n - j);
                dp[i + 1][j][k] += dp[i][j][k] * (j - k);
                dp[i + 1][j][j] += dp[i][j][k] * k;
            }
        }
    }
    cout << dp[m][n][n] << endl;
    return 0;
}
```

---

## 作者：wgyhm (赞：2)

先讲讲我的比较愚蠢的做法。

钦定每次遍历到没走过的点的顺序 $1\to 2\to 3\to \dots\to n$，最后乘上 $(n-1)!$ 即可。

记 $f_{i,j}$ 表示当前扩展到前 $i$ 个点，连了 $j$ 条额外边，且前 $i$ 个点都和 $1$ 在一个强联通分量的方案数。枚举跳到 $1$ 的强联通分量中的终点 $l$ 和边数 $t$，然后 $[l+1,i-1]$ 之间随便连 $t-k$ 条边，有转移：
$$
f_{i,j}=\sum _{l=1}^{i-1}\sum _{t=1}^{j}\sum _{k=1}^{t} f_{l,j-t}\times h_{i-l-1,t-k}
\times (i^k-(i-l)^k)
$$
其中 $h_{i,j}$ 表示 $i$ 个点连 $j$ 条额外边的方案数。

发现后面那里都和 $j$ 没关系，于是可以对于每个 $i,l,k$ 预处理出来后面的东西。

复杂度 $O(n^4)$，但是带 $1/32$ 的常数所以可以过。其实可以卷积做到更低的复杂度，但没什么意思。

[Submission](https://atcoder.jp/contests/cf16-final/submissions/49217193)

其他题解的做法就是基于分成三类，包含 $1$ 的强联通分量，走过但不在 $1$ 的强联通分量之中，没走过的个数。然后如果当前的点走到 $1$ 的强联通分量中就所有点都在 $1$ 的强联通分量之中。复杂度就是 $O(n^3)$ 的了。

---

## 作者：Lyrella (赞：1)

# [Road of the King](https://www.luogu.com.cn/problem/AT_codefestival_2016_final_f) 2024.9.6

## 简要题意

有一个 $n$ 个点的图，目前一条边都没有。

有一个人在 $1$ 号点要进行 $m$ 次移动，终点不必是 $1$ 号点，假设第 $i$ 次从 $u$ 移动到 $v$，那么在 $u$ 与 $v$ 之间连一条有向边。

问有多少种序列能满足：最终 $n$ 个点组成的图是一个强连通图。答案对 $10^9+7$ 取模。

## 数据范围

$1\le n,m\le 300$

## 题解

对于这种连通图计数类问题，有一个常见的套路，就是你去考虑 $1$ 号点的连通情况。就比如这一道题我们需要考虑现在一共走到过哪一些点，以及一号点所在的强连通分量大小。根据这个思路可以很容易的写出状态 $f_{i,j,k}$ 表示走了 $i$ 步，一共走到过 $j$ 个点，其中一号点所在的强连通分量大小为 $k$。

我们可以发现一个性质，就是如果现在去走一个**在一号点所在的强连通分量中**的点，那么目前所有点都会变成一个强连通分量（显然）。所以状态的转移也就差不多出来了。

但是如果正常转移你会发现很难写，对于一个状态 $f_{i,j,k}$ 有非常多的转移方法，但是从 $f_{i,j,k}$ 转移到其他地方就要简单很多，外面可以分三种情况讨论：

1. 下一步走之前没走过的点：$f_{i+1,j+1,k}+=f_{i,j,k}\times(n-j)$；
2. 下一步走之前走过但是不在一号点所在强连通分量中的点：$f_{i+1,j,k}=f_{i,j,k}\times(j-k)$；
3. 下一步走一号点所在强连通分量中的点：$f_{i+1,j,j}=f_{i,j,k}\times k$。

最后答案为 $f_{m,n,n}$，此题得解！

## 代码

```cpp
int n, m;
ll f[N][N][N];

int add(ll x, int y){
    return x - p + y >= 0 ? x - p + y : x + y;
}

signed main(){
    // fileio(fil);
    n = rd(), m = rd();
    f[0][1][1] = 1;
    for(int i = 0; i < m; ++i)for(int j = 1; j <= n; ++j)for(int k = 1; k <= j; ++k){
        f[i + 1][j + 1][k] = add(f[i + 1][j + 1][k], f[i][j][k] * (n - j) % p);
        f[i + 1][j][k] = add(f[i + 1][j][k], f[i][j][k] * (j - k) % p);
        f[i + 1][j][j] = add(f[i + 1][j][j], f[i][j][k] * k % p);
    }
    cout << f[m][n][n];
    return 0;
}
```

---

## 作者：kanzaki (赞：0)

## 思路
因为要求最终是一个强连通图，所以 $1$ 号点能够到达任意一个点。

因此，只要做到每个点都能够到 $1$ 号点即可满足强连通图要求。

那么每个方案是否不同实际上只与每一步到达的点是什么和此时有多少点能够到达 $1$ 号点有关。

但是这样定义状态不够明确，判断一个点此时能否到 $1$ 号点的依据是其和 $1$ 号点是否在一个强连通子图中。转化为这样之后我们就能清晰的看出如果一个不在子图中的点向在强连通子图中的点连边，那么连边后它也会在子图中。

设状态为 $f_{i,j,k}$ 表示走到第 $i$ 步，到达过 $j$ 个点，有 $k$ 个点在包含 $1$ 号点的强连通子图中的方案数。

走到没有到达过的点 $f_{i+1,j+1,k} += f_{i,j,k} \times \left ( n - j \right )$。

走到到达过的点且不在包含 $1$ 号点的强连通子图内 $f_{i+1,j,k} += f_{i,j,k} \times \left ( j - k \right )$。

走到到达过的点且在包含 $1$ 号点的强连通子图内 $f_{i+1,j,j} += f_{i,j,k} \times k$。

初始化 $f_{0,1,1} = 1$，答案为 $f_{m,n,n}$。

剩余细节在代码中。


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 305
#define int long long
#define mod 1000000007
int n,m;
int f[maxn][maxn][maxn];
signed main(){
	cin>>n>>m;
	f[0][1][1]=1;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=i+1;j++){//上界为i+1的原因是初始1号点就已经到达了
			for(int k=0;k<=j;k++){
				f[i+1][j+1][k]=(f[i+1][j+1][k]+f[i][j][k]*(n-j))%mod;
				f[i+1][j][k]=(f[i+1][j][k]+f[i][j][k]*(j-k))%mod;
				f[i+1][j][j]=(f[i+1][j][j]+f[i][j][k]*k)%mod;
//				cout<<i<<' '<<j<<' '<<k<<" -> "<<i+1<<' '<<j+1<<' '<<k<<'\n';
			}
		}
	}
	cout<<f[m][n][n]<<'\n';
	return 0;
}
```

---

## 作者：AK_heaven (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_codefestival_2016_final_f)

我们遇到这种图论计数题目，我们可以选择考虑动态规划来统计方案数。

如何设计一个状态呢？

1. 给点 / 边进行分类，看数据范围，如果是支持 $O(n^3)$ 的空间复杂度（例如这道题目），我们可以把点分成两类 / 三类，因为往往这类题目除了某个特殊点以外，其他点都是等价的。

以这道题为例，我们把点分类为了与 $1$ 强连通的点，和遍历过的点。

2. 寻找转移顺序，我们很显然有一个转移顺序是可以被找到的，就是走的步数是单调递增的。根据我们对于点的分类，于是我们可以设计出状态 $f_{i, j, k}$ 来表示前 $i$ 步遍历了 $j$ 个点并且其中 $k$ 个点与 $1$ 强连通。

3. 这个时候我们就可以很好的推出三个转移方程。

①. 我们扩展了一个新的点。

②. 我们扩展了一个扩展过但是与 $1$ 并不强连通的点。

③. 我们扩展了一个与 $1$ 强连通的点。

4. 检查是否有没有讨论到的转移方程，如果在比赛的时候跑不过大样例，那么可以重新回到第三步，第三步如果发现不了问题就回到第二步，反复的思考新的状态设计。

**The code**


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long

using namespace std;

const int N = 305;
const int mod = 1e9 + 7;

ll F[N][N][N], n, m;

int main() {
	cin >> n >> m;
	F[0][1][1] = 1;
	L(i, 0, m-1)
	  L(j, 1, n)
	    L(k, 1, j) {
	    	F[i+1][j+1][k] = (F[i][j][k]*(n-j) + F[i+1][j+1][k]) % mod;
	    	F[i+1][j][k] = (F[i][j][k]*(j-k) + F[i+1][j][k]) % mod;
	    	F[i+1][j][j] = (F[i][j][k]*k + F[i+1][j][j]) % mod;
		}
	cout << F[m][n][n] << '\n'; 
	return 0;
}

```

---

## 作者：zzzyyyyhhhhh (赞：0)

神仙 dp 题，蒟蒻不会做。

首先想到这是一个 $n^3$ 的 dp 。怎么想到的？当然是看数据范围了。显然，按照惯例，第一维大概率是走到了第几步。然后就不会了。不会也不能开摆，还是继续想吧。首先发现每个点都是等价的，且记录每个点的状态是很不现实的，于是我们只能考虑还存在那些状态是可以使用的。思考一圈后，发现只有 有多少点在（包含 $1$ 号点的）强连通分量中 和 走过多少点（重复经过算一次）是有用的，于是把它们加入状态。这样，我们就“凑”出了一个 $n^3$ 的 dp 。

既然状态都有了，那就考虑转移吧。发现这个状态更适合用刷表法（一定不是因为官方题解是这么干的）。先考虑第一种情况，将一个走过但不在包含 $1$ 号点的强连通分量的点加入强连通分量：

$$ f_{i+1,j,k}\gets f_{i,j,k}\times (k-j)  $$
有 $k-j$ 个点不在有 $1$ 的强连通分量

如果没走过下一个点

$$f_{i+1,j,k+1}\gets f_{i,j,k}\times (n-k) $$
剩下 $n-k$ 个点为走过

第三种情况，也是不太好想到的一种，如果下一个点在包含 $1$ 号点的强连通分量中，那么走过的就都可以与 $1$ 号点构成强连通分量

$$f_{i+1,k,k}\gets f_{i,j,k}\times j $$
有 $j$ 个点在含 $1$ 的强连通分量中

附上代码

```球球管理了,感谢管理的指导
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 300+2,mod=1e9+7;
int n,m;
int f[N][N][N];
signed main()
{
	cin>>n>>m;
	f[0][1][1]=1;
	for(int i=0;i<=m;i++)
	{
		for(int k=1;k<=n;k++)
		{
			for(int j=1;j<=k;j++)
			{
				f[i+1][j][k]+=f[i][j][k]*(k-j);
				f[i+1][j][k+1]+=f[i][j][k]*(n-k);
				f[i+1][k][k]+=f[i][j][k]*j;
				f[i+1][j][k]%=mod;
				f[i+1][j][k+1]%=mod;
				f[i+1][k][k]%=mod;
			}
		}
	}
	cout<<f[m][n][n];
}

```

---

