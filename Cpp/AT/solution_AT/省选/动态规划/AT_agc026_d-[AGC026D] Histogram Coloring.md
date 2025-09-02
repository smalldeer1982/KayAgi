# [AGC026D] Histogram Coloring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc026/tasks/agc026_d

高さ $ 10^9 $ マス，幅 $ N $ マスのグリッドを考え，左から $ i(1\ \leq\ i\ \leq\ N) $ 番目，下から $ j(1\ \leq\ j\ \leq\ 10^9) $ 番目のマス目を $ (i,\ j) $ と表すことにします。

すぬけ君は各 $ i\ =\ 1,\ 2,\ ...,\ N $ について，左から $ i $ 列目のマスたちを，下から $ h_i $ 個を残すように切り取りました。 そして赤，青の絵の具を使い，マス目を絵の具で塗ります。 以下の条件を満たすような塗り分け方は何通りか求めて下さい。ただし答えは非常に大きくなるので，$ 10^9+7 $ で割った余りを出力して下さい。

- 全ての(切り取った後に残された)マスたちは，赤，青のどちらかの色に塗られている。
- 全ての $ 1\ \leq\ i\ \leq\ N-1 $, $ 1\ \leq\ j\ \leq\ min(h_i,\ h_{i+1})-1 $ について，$ (i,\ j),\ (i,\ j+1),\ (i+1,\ j),\ (i+1,\ j+1) $ の4マスのなかにちょうど $ 2 $ 個ずつ赤色と青色のマスが存在する。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ h_i\ \leq\ 10^9 $

### Sample Explanation 1

以下に塗り分け方の一例を示します。 ``` \# \#\# \# \#\#\# \#\#\#\#\# \#\#\#\#\#\#\#\#\#\#\#\#```

### Sample Explanation 2

以下の $ 6 $ 通りの塗り分け方が存在します。 ``` \#\# \#\# \#\# \#\# \#\# \#\#\#\# \#\# \#\# \#\# \#\# \#\#```

### Sample Explanation 3

どのような塗り分け方も条件を満たします。

### Sample Explanation 4

塗り分け方の個数を $ 10^9\ +\ 7 $ で割った余りを出力することに注意して下さい。

## 样例 #1

### 输入

```
9
2 3 5 4 1 2 4 2 1```

### 输出

```
12800```

## 样例 #2

### 输入

```
2
2 2```

### 输出

```
6```

## 样例 #3

### 输入

```
5
2 1 2 1 2```

### 输出

```
256```

## 样例 #4

### 输入

```
9
27 18 28 18 28 45 90 45 23```

### 输出

```
844733013```

# 题解

## 作者：myee (赞：7)

### 思路

考虑相邻两列的相接处，仅有如下几种可能：
* 完全相反。
* 完全相同。此时列方向上必须交替分布两种颜色。

考虑记录当前列状态：已经考虑了前 $n$ 列，第 $n$ 列当前两种颜色交替分布一直到高度 $m$，且更高部分不合法的方案数。

假设这样的方案数为 $f_{n,m}$，其中 $1\le m\le h_n$。

然后转移时直接枚举下一项的状态：是和自己相同，还是相反。

如果 $h_{n+1}\le h_n$，则

$$f_{n+1,m}\leftarrow f_{n,m}\quad(1\le m<h_{n+1})$$

$$f_{n+1,h_{n+1}}\leftarrow2f_{n,m}\quad(h_{n+1}\le m\le h_n)$$

如果 $h_{n+1}>h_n$，则

$$f_{n+1,m}\leftarrow2^{h_{n+1}-h_n}f_{n,m}\quad(1\le m<h_n)$$

$$f_{n+1,m}\leftarrow2^{h_{n+1}-m}f_{n,h_n}\quad(h_n\le m<h_{n+1})$$

$$f_{n+1,h_{m+1}}\leftarrow2f_{n,h_n}$$

初始值 $h_0=1,f_{0,1}=1$ 即可。

直接 dp 的复杂度是 $O(nh)$ 的，无法通过。

考虑本题的特殊性质：$n$ 很小。

考虑直接对值域分段 dp，我们预先排序，记录下每个区间 $[h,H)$ 对应的 dp 值之和即可。

等比数列赋值的部分可以预处理系数。

总复杂度 $O(n^2+n\log v)$。

使用线段树维护即可做到 $O(n\log n)$。

### Code

```cpp
const ullt Mod=1e9+7,inv2=5e8+4;
typedef ConstMod::mod_ullt<Mod>modint;
typedef std::vector<modint>modvec;
uint H[105],S[105];
modint Pow[105],PowInv[105],Dp[105],D[105];
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    uint n,m;scanf("%u",&n),S[n]=1;
    for(uint i=0;i<n;i++)scanf("%u",H+i),S[i]=H[i];
    std::sort(S,S+n+1),m=std::unique(S,S+n+1)-S;
    for(uint i=0;i<m;i++)Pow[i]=modint(2)^S[i],PowInv[i]=modint(inv2)^S[i];
    for(uint i=0;i+1<m;i++)D[i]=2*(PowInv[i]-PowInv[i+1]);
    Dp[0]=1;
    uint tp=0;
    for(uint i=0;i<n;i++){
        uint h=std::lower_bound(S,S+m,H[i])-S;
        if(h<=tp)
        {
            for(uint i=h+1;i<=tp;i++)Dp[h]+=Dp[i];
            Dp[h]*=2;
        }
        else
        {
            modint v=Dp[tp];
            Dp[h]=v*2;
            for(uint i=tp;i<h;i++)Dp[i]=D[i]*Pow[h]*v;
            v=Pow[h]*PowInv[tp];
            for(uint i=0;i<tp;i++)Dp[i]*=v;
        }
        tp=h;
    }
    modint ans;
    for(uint i=0;i<=tp;i++)ans+=Dp[i];
    ans.println();
    return 0;
}
```




---

## 作者：Hadtsti (赞：6)

### 题意简述



### 题目分析

首先我们发现一个明显而有用的性质：当第 $i$ 列的格子是红蓝交替的时，它正右侧的格子有两种染色方式（两种红蓝交替的方式）；否则只有一种确定的染色方式。这样本题的后效性问题就解决了。

接下来考虑设计 DP 状态。如果只设计一维，我们将难以判断第 $i+1$ 列的染色受第 $i$ 列的限制情况。由于我们至少要知道第 $i$ 列能否让第 $i+1$ 列拥有红蓝染色的 $2$ 种方案，我们的状态至少应该能让我们得知第 $i$ 自底端开始的极长红蓝交替段长度情况。

首先将 $h_1\sim h_n$ 离散化（实现时应带上 $1$），得到序列 $b_1\sim b_n$ 和 $c_1\sim c_m$（$m$ 是 $h$ 出现的值个数），其中 $c_{b_i}=a_i$。考虑设计 $f_{i,j}$ 表示考虑了前 $i$ 列，第 $i$ 列底端极长红蓝交替段长度 $l\in[c_j,c_{j+1})$ 的染色方案数。考虑 $f_{i,j}$ 该怎么求，分两种情况：

- $h_{i-1}\le h_i$

当 $j<b_{i-1}$ 时，第 $i$ 列底端极长红蓝交替段长度会和第 $i-1$ 列一样，而第 $i$ 列多出来的部分显然不会和下端的交替段连起来，因此有 $f_{i,j}=2^{h_i-h_{i-1}}\times f_{i-1,j}$。

否则，第 $i$ 列的底端 $h_{i-1}$ 个格子是 $2$ 种红蓝交替的染色方式，上面的格子则有 $2^{h_i-c_j}-2^{h_i-c_{j+1}}$ 种染色方式。

- $h_{i-1}>h_i$

当 $j<b_i$ 时，第 $i$ 列底端极长红蓝交替段长度会和第 $i-1$ 列一样，有 $f_{i,j}=f_{i-1,j}$。

至于 $j=b_i$ 时，有两种红蓝交替的染色方式，并且可以由 $f_{i-1,b_i}\sim f_{i-1,b_{i-1}}$ 转移过来，求个和乘一下 $2$ 就好了。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int n,m,a[110],b[110],f[110],ans;
inline int S(int x,int y) 
{
	return x+y>=mod?x+y-mod:x+y;
}
inline void A(int &x,int y)
{
	x=S(x,y);
}
inline int power(int r,int l)
{
	if(l>r)
		return 0;
	int a=2,B=b[r]-b[l],res=1;
	for(;B;B>>=1)
	{
		if(B&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod;
	}
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),b[++m]=a[i];
	b[++m]=1;
	sort(b+1,b+m+1);
	m=unique(b+1,b+m+1)-b-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+m+1,a[i])-b;
	for(int i=1;i<=a[1];i++)
		f[i]=2ll*S(power(a[1],i),mod-power(a[1],i+1))%mod;
	for(int i=2;i<=n;i++)
	{
		if(a[i]>=a[i-1])
		{
			int tmp=f[a[i-1]];
			for(int j=1;j<a[i-1];j++)
				f[j]=1ll*f[j]*power(a[i],a[i-1])%mod;
			for(int j=a[i-1];j<=a[i];j++)
				f[j]=2ll*tmp*(power(a[i],j)+mod-power(a[i],j+1))%mod;
		}
		else
		{
			f[a[i]]=S(f[a[i]],f[a[i]]);
			for(int j=a[i]+1;j<=a[i-1];j++)
				A(f[a[i]],S(f[j],f[j])),f[j]=0;
		}
	}
	for(int i=1;i<=a[n];i++)
		A(ans,f[i]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Purslane (赞：5)

# Solution

简单 DP 题。

按理说，我们确定了最下面那一行的情况，其他行几乎就是确定的了。

但是很容易发现，只考虑相邻两数的和，序列 `010101` 和 `101010` 是不做区分的。

因此我们需要设两个量，分别表示最底端是 $01$ 交错的方案数和不是 $01$ 交错的方案数。（方便起见，$01$ 交错的方案数只算一半）。用二元组 $(x,y)$ 表示。

考虑每次找到最矮的数（可能有多个）他们将序列划分成若干个连续段。

我们有两种操作：

1. 将一段区间下面扩展一行。$(x,y) \to (2x,y)$。
2. 将若干段区间合并。$\to (\prod x,\prod (2x+y) - 2 \prod x)$。

直接暴力可以做到 $O(n^2)$。使用笛卡尔树优化可以做到 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10,MOD=1e9+7;
int n,h[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
pair<int,int> solve(int l,int r,int ot) {
	int mn=*min_element(h+l,h+r+1),lst=l-1;
	vector<pair<int,int>> vc;
	ffor(i,l,r) if(h[i]==mn) {
		if(lst+1<=i-1) {
			auto pr=solve(lst+1,i-1,mn);
			vc.push_back({pr.first*2%MOD,pr.second});
		}
		lst=i,vc.push_back({1,0});
	}
	if(lst+1<=r) {
		auto pr=solve(lst+1,r,mn);
		vc.push_back({pr.first*2%MOD,pr.second});	
	}
	int al=1,fst=1;
	for(auto pr:vc) al=(2*pr.first+pr.second)%MOD*al%MOD,fst=fst*pr.first%MOD;
	return {fst*qpow(2,mn-(ot+1))%MOD,(al-2*fst)%MOD};
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>h[i];
	auto pr=solve(1,n,0);
	cout<<((pr.first*2+pr.second)%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Jsxts_ (赞：4)

首先容易发现，如果从下往上一行一行填，那么在没有断开前，一行若有两个相邻相同的颜色，则上一行的染色法方案唯一确定，否则上一行有两种填法，都满足和这一行一样也是红蓝交替。

接下来考虑 dp，设 $f_{l,r,0/1,d}$ 表示区间 $[l,r]$ 已经填了从下往上的 $d$ 行，并且钦定当前是/不是有唯一填法（是/不是红蓝交替）的方案数。

那么，首先找到区间的最小值位置 $p$，那么填到这个高度后会分成两端区间。

是红蓝交替的较容易转移：

$$f_{l,r,0,d}=f_{l,p-1,0,h_p}\times f_{p + 1,r,0,h_p}\times 2^{h_p-d}$$

因为每行都有 $2$ 种填法。

不是红蓝交替，那么从 $d$ 填到 $h_p$ 是唯一确定的，只需要对第 $h_p$ 行的状况分类讨论（称 $[l,p-1]$ 为左侧，$[p+1,r]$ 为右侧）：

首先若一侧在断开后仍为不交替，那么下方的填法会在更上面的决策中完成，所以不需要计算方案。若为交替，则对应的下方填法有两种：以红或蓝开始交替。同时 $p$ 位置填什么数还没有确定。

- 左侧交替，右侧交替：这时一定满足 $p$ 的位置要与 $p-1$ 或 $p+1$ 相同（否则违反不是红蓝交替的条件），枚举两边下方的填法共有 $6$ 种。

- 剩下的情况 $p$ 位置都没有限制，填任何数都行。

所以转移如下：

$$\begin{aligned}
f_{l,r,1,d}=6\times f_{l,p-1,0,d} \times f_{p+1,r,0,d}\\
+4\times f_{l,p-1,0,d} \times f_{p+1,r,1,d}\\
+4\times f_{l,p-1,1,d} \times f_{p+1,r,0,d}\\
+2\times f_{l,p-1,1,d} \times f_{p+1,r,1,d}
\end{aligned}$$

可能要处理一下 $p=l,r$ 的情况。

虽然数组开不下，但是状态数显然是 $O(n^3)$ 的，直接记搜即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 1e2;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,h[N + 10],mn[N + 10][N + 10];
const int mod = 1e9 + 7,inv2 = mod + 1 >> 1;
map<ll,int> mp;
ll hsh(int l,int r,int f,int d) {
	return 1ll * d * n * n * 2 + 1ll * l * n * 2 + 1ll * r * 2 + f;
}
int qpow(int a,int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		b >>= 1, a = 1ll * a * a % mod;
	}
	return res;
}
int dfs(int l,int r,int f,int d) {//f:当前为/不为01交替 
	if (l > r) return 1;
	if (l == r) return f ? 0 : qpow(2,h[l] - d);
	ll hs = hsh(l,r,f,d);
	if (mp.count(hs)) return mp[hs];
	int p = mn[l][r];
	if (!f) return mp[hs] = 1ll * dfs(l,p - 1,f,h[p]) * dfs(p + 1,r,f,h[p]) % mod * qpow(2,h[p] - d) % mod;
	if (p == l) return mp[hs] = 2ll * (dfs(p + 1,r,0,h[p]) + dfs(p + 1,r,1,h[p])) % mod;
	if (p == r) return mp[hs] = 2ll * (dfs(l,p - 1,0,h[p]) + dfs(l,p - 1,1,h[p])) % mod;
	int t00 = 6ll * dfs(l,p - 1,0,h[p]) % mod * dfs(p + 1,r,0,h[p]) % mod;
	int t10 = 4ll * dfs(l,p - 1,1,h[p]) % mod * dfs(p + 1,r,0,h[p]) % mod;
	int t01 = 4ll * dfs(l,p - 1,0,h[p]) % mod * dfs(p + 1,r,1,h[p]) % mod;
	int t11 = 2ll * dfs(l,p - 1,1,h[p]) % mod * dfs(p + 1,r,1,h[p]) % mod;
	return mp[hs] = ((ll)t00 + t10 + t01 + t11) % mod;
}
int main() {
	n = read();
	for (int i = 1;i <= n;i ++ ) h[i] = read();
	for (int i = 1;i <= n;i ++ ) {
		mn[i][i] = i;
		for (int j = i + 1;j <= n;j ++ )
			mn[i][j] = h[j] < h[mn[i][j - 1]] ? j : mn[i][j - 1];
	}
	cout << (dfs(1,n,1,0) + dfs(1,n,0,0)) % mod;
	return 0;
}
```


---

## 作者：Graphcity (赞：3)

首先考虑一个 $n\times m$ 的矩形有多少种填法。假设我们已经填了一行，考虑下一行该怎么填。

通过观察可以发现，如果第一行是 `RBRBRB...` 或者 `BRBRBR...` 交替出现的，第二行也一定是交替出现，有两种交替方式。否则，第二行只有一种填法，也就是第一行取反。

所以，如果第一行不是全部交替，方案数为 1。否则，方案数为 $2^{m-1}$。

接下来回到原题中的情况。首先建出笛卡尔树，考虑笛卡尔树中每个结点所代表的矩形。如果这个矩形有 $2$ 的宽度次方种填法，那么这个结点对应的区间第一行就应该交替出现，否则就只有一种填法。

也就是说，对于一个结点，可以用三元组 $(l,r,k)$ 体现它的信息：如果第一行在 $[l,r]$ 范围内交替，方案数乘上 $2^k$。

设 $f_{i,j}$ 为第一行中考虑到第 $i$ 个位置，最长的交替后缀从位置 $j$ 开始的方案数。转移很简单，枚举下一个位置是否跟当前位置相同即可。初始值 $f_{1,1}=2$。

时间复杂度 $O(n^3)$。

线段树优化可以达到 $O(n\log n)$，但是没必要。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=100,Mod=1e9+7;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,h[Maxn+5],vis[Maxn+5],lw[Maxn+5];
int f[Maxn+5][Maxn+5];
vector<pair<int,int>> v[Maxn+5];
inline int Check() {For(i,1,n) if(!vis[i]) return 0; return 1;}

int main()
{
    n=read();
    For(i,1,n) h[i]=read(),lw[i]=1;
    while(!Check())
    {
        for(int l=1,r;l<=n;l=r+1)
        {
            r=l; if(vis[l]) continue;
            for(;r<n && !vis[r+1];r++);
            int mn=Mod; For(i,l,r) mn=min(mn,h[i]);
            if(mn-lw[l]) v[r].emplace_back(l,mn-lw[l]);
            For(i,l,r) {if(h[i]==mn) vis[i]=1; lw[i]=mn;}
        }
    }
    For(i,1,n)
    {
        if(i==1) f[1][1]=2;
        else
        {
            For(j,1,i-1) f[i][j]=f[i-1][j];
            For(j,1,i-1) f[i][i]=(f[i][i]+f[i-1][j])%Mod;
        }
        for(auto [l,p]:v[i])
        {
            int k=Pow(2,p);
            For(j,1,l) f[i][j]=1ll*f[i][j]*k%Mod;
        }
    }
    int ans=0; For(i,1,n) ans=(ans+f[n][i])%Mod;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：FZzzz (赞：3)

这个限制实际上就是，两个挨着的列，如果在公共的高度下左边的列有两个挨着的同色格子，那两边在公共的高度下必然全部反色，否则可以同色或反色。

设计一个 dp，设 $f_{i,j}$ 为涂完前 $i$ 列，第 $i$ 列最低的两个相邻同色格子是 $j$ 和 $j+1$，$j=h_i$ 表示不存在。考虑怎么样转移。

如果 $h_i<h_{i+1}$，那下面的部分全都不变，上面的部分是累加到 $h_i$ 上然后乘以二，因为这意味着下面是红蓝相间，那可以同色或反色。还要把上面清空。

否则，下面的部分要乘上一个 $2^{h_i-h_{i-1}}$，上面的部分是 $f_{i-1,h_{i-1}}$ 乘上一个二的次幂，再乘上一个 $2^{-j}$。

这样有一个 $O(nh)$ 的做法。如果我们离散化一下，维护每一段里面所有 dp 值的和，发现这样只需要算一个等比求和，于是就 $O(n^2)$ 了。优化到 $O(n\log n)$ 也是可以的。

~~所以说根本不需要搞什么笛卡尔树啊？~~
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=100+5;
int n,h[maxn],m,ord[maxn*2],h2[maxn];
const ll mod=1e9+7,inv2=5e8+4;
ll ksm(ll a,ll b){
	ll ans=1;
	while(b){
		if(b%2==1) ans=ans*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return ans;
}
ll f[maxn*2],s[maxn*2];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	for(int i=1;i<=n;i++) h[i]=readint();
	for(int i=1;i<=n;i++){
		ord[i]=h[i];
		ord[i+n]=h[i]+1;
	}
	ord[0]=1;
	sort(ord,ord+n*2+1);
	m=unique(ord,ord+n*2+1)-ord-1;
	for(int i=1;i<=n;i++) h2[i]=lower_bound(ord,ord+m,h[i])-ord;
	for(int i=0;i<m;i++)
		s[i]=(ksm(inv2,ord[i]-1)-ksm(inv2,ord[i+1]-1)+mod)%mod;
	for(int i=0;i<h2[1];i++){
		ll pw=ksm(2,h[1]);
		f[i]=pw*s[i]%mod;
	}
	f[h2[1]]=2;
	for(int i=2;i<=n;i++)
		if(h[i]<=h[i-1]){
			for(int j=h2[i]+1;j<=h2[i-1];j++){
				f[h2[i]]=(f[h2[i]]+f[j])%mod;
				f[j]=0;
			}
			f[h2[i]]=f[h2[i]]*2%mod;
		}
		else{
			ll pw=ksm(2,h[i]-h[i-1]);
			for(int j=0;j<h2[i-1];j++) f[j]=f[j]*pw%mod;
			pw=ksm(2,h[i]);
			f[h2[i]]=f[h2[i-1]]*2%mod;
			for(int j=h2[i]-1;j>=h2[i-1];j--) f[j]=f[h2[i-1]]*pw%mod*s[j]%mod;
		}
	ll ans=0;
	for(int i=0;i<=h2[n];i++) ans=(ans+f[i])%mod;
	printf("%lld\n",ans);
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
```

---

## 作者：SalN (赞：2)

考虑一个类似笛卡尔树的 dp 顺序，先确定下面那个公有的大矩形然后递归处理问题。$[l,r]$ 中 $\Delta$ 以下的部分已经被钦定了（$\Delta$ 是 $h_{fa(p)}$ 这种东西）且对上面的染色没有影响，设这个方案数为 $f(l,r,\Delta)$，假设 $p$ 是区间 $[l,r]$ 中严格最矮的且 $\Delta<h_p$（如果没有就递归到有）。我们先钦定 $p$ 这一列高度为 $(\Delta,h_p]$ 的格子的颜色，然后考虑 $[l,r]$ 中除了 $p$ 别的列高度为 $(\Delta,h_p]$ 这部分（下文称之为染色地方）的染色，分类讨论：

+ 如果存在 $h_p[i]=h_p[i+1](\Delta<i<i+1\leq h_p)$，$p$ 的钦定方案数为 $2^{h_p-\Delta}-2$，$h_{p\pm 1}[i],h_{p\pm 1}[i+1]$ 颜色固定，推下去要染色的地方都被确定了，且相邻两位顶的颜色相异（$h_x[h_p]\neq h_{x+1}[h_p]$），设 $g(l,r,\Delta)$ 表示 $[l,r]$  $\Delta$ 以上的部分在钦定了 $h_i[\Delta+1]$ 的颜色且保证钦定方式为相邻两列的钦定不同的情况下的方案数，还要乘子问题 $g(l,p-1,h_p)$ 和 $g(p+1,r,h_p)$。

+ 如果不存在 $h_p[i]=h_p[i+1](\Delta<i<i+1\leq h_p)$，$p$ 的钦定方案数为 $2$，此时可以随便钦定 $h_x[h_p]$，剩下的部分推下去可以被确定，发现是子问题 $f(l,p-1,h_p-1)$ 和 $f(p+1,r,h_p-1)$。

现在问题只剩 $g(l,r,\Delta)$ 怎么求了，设 $p$ 是 $[l,r]$ 中 $h$ 最小的，满足 $h_p>\Delta$ 不然递归到满足，任意钦定 $(\Delta,h_p]$ 的颜色别的可以推出，得到子问题 $g(l,p-1,h_p)$ 和 $g(p+1,r,h_p)$。哦 $f$ 和 $g$ 的边界是 $f(l,r,)=1,g(l,r,)=1(l>r)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define up(i,l,r) for(int i=l; i<=r; ++i)
#define dn(i,r,l) for(int i=r; i>=l; --i)

using namespace std;

const int N=105, P=1e9+7;

int ksm(int a,int b) {
	int ret=1;
	for( ; b; b>>=1) {
		if(b&1) ret=ret*a%P;
		a=a*a%P;
	}
	return ret;
} 

int n, h[N];

int ask(int l,int r) {
	int ret=0;
	up(i,l,r) if(!ret||h[i]<h[ret]) ret=i;
	return ret;
}

int g(int l,int r,int delta) {
	if(l>r) return 1;
	int p=ask(l,r), ret=g(l,p-1,h[p])*g(p+1,r,h[p])%P;
	if(h[p]-delta>0) ret=ksm(2,h[p]-delta)*ret%P;
	return ret;
}

int f(int l,int r,int delta) {
	if(l>r) return 1;
	int p=ask(l,r), ret=f(l,p-1,h[p]-1)*f(p+1,r,h[p]-1)%P;
	if(h[p]-delta>0) ret=2*ret%P;
	if(h[p]-delta>1) {
		int bur=(ksm(2,h[p]-delta)-2)%P; 
		bur=g(l,p-1,h[p])*g(p+1,r,h[p])%P*bur%P;
		ret=(ret+bur)%P;
	}
	return ret;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	up(i,1,n) cin >> h[i];
	cout << (f(1,n,0)%P+P)%P;
	return 0;
}
```

---

## 作者：xht (赞：2)

## [Histogram Coloring](https://atcoder.jp/contests/agc026/tasks/agc026_d)

### 题意

- 有 $n$ 列格子排成一排，第 $i$ 列的高度为 $h_i$。
- 每个格子都可以被染成红色或蓝色，但要求所有 $2 \times 2$ 的四个格子中恰好两红两蓝。
- 求方案数。
- $n \le 100$，$h_i \le 10^9$，答案对 $10^9+7$ 取模。

### 题解

定义第 $i$ 列第 $j$ 行的颜色为 $a_{i,j}$。

对于 $i,i+1$ 两列中 $j \le \min(h_i,h_{i+1})$ 的部分，染色情况有两种：

- $a_{i,j} \ne a_{i+1,j}$，即两列颜色相反。
- $a_{i,j} \ne a_{i,j-1}$，即同列两色交替。

设 $f_{i,j}$ 表示考虑前 $i$ 列，第 $i$ 列从下往上有 $j$ 个位置满足两色交替且第 $j+1$ 个位置不满足。

第二维可以只保留所有 $h$ 值的位置，时间复杂度可以做到 $\mathcal O(n^2)$。

然而还可以更优。

建出根为最小值的笛卡尔树，设 $f_{l,r,i,j,0/1}$ 表示笛卡尔树上的节点 $[l,r]$ 在高度 $\ge h = \min h_{l\dots r}$ 的部分，其中 $a_{l,h} = i$，$a_{r,h} = j$，是否在同一列为两色交替的方案数。

实现时可以将 $h$ 从大到小排序之后，每次相当于对于一列 $t$ 合并 $[l,t-1]$ 和 $[t+1,r]$ 两个状态，时间复杂度 $\mathcal O(n \log n)$。

### 代码

```cpp
const int N = 1e5 + 7;
int n, h[N], p[N], pl[N], pr[N], w[N];

struct DP {
	modint a[2][2][2];
	inline DP() {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					a[i][j][k] = 0;
	}
	inline modint (* operator [] (int i)) [2] {
		return a[i];
	}
	inline friend DP operator + (DP a, DP b) {
		DP c;
		for (int li = 0; li < 2; ++li)
			for (int ri = 0; ri < 2; ++ri)
				for (int lj = 0; lj < 2; ++lj)
					for (int rj = 0; rj < 2; ++rj)
						for (int lk = 0; lk < 2; ++lk)
							for (int rk = 0; rk < 2; ++rk)
								c[li][rj][lk|rk|(lj==ri)] += a[li][lj][lk] * b[ri][rj][rk];
		return c;
	}
} f[N];

void work(int o, int x) {
	if (w[o] == x) return;
	DP now;
	int t = (w[o] ^ x) & 1;
	modint k = (modint)2 ^ (w[o] - x - 1);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			now[i][j][0] = (f[o][i][j][0] + f[o][i^1][j^1][0]) * k,
			now[i][j][1] = f[o][i^t][j^t][1];
	f[o] = now;
}

int main() {
	rd(n), rda(h, n), iota(p + 1, p + n + 1, 1);
	sort(p + 1, p + n + 1, [&](int i, int j) { return h[i] > h[j]; });
	for (int o = 1; o <= n; o++) {
		int i = p[o], L = i, R = i;
		DP now;
		now[0][0][0] = now[1][1][0] = 1;
		if (pl[i-1]) L = pl[i-1], pr[L] = pl[i-1] = 0, work(L, h[i]), now = f[L] + now;
		if (pr[i+1]) R = pr[i+1], pr[i+1] = pl[R] = 0, work(i + 1, h[i]), now = f[i+1] + now;
		f[L] = now, pr[L] = R, pl[R] = L, w[L] = h[i];
	}
	work(1, 1);
	modint ans;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				ans += f[1][i][j][k];
	print(ans);
	return 0;
}
```

---

## 作者：翼德天尊 (赞：2)

考虑从前往后做线性 dp。

手玩一下会发现，当第 $i-1$ 列已经填完，该填第 $i$ 列时：

- 若 $h_i\le h_{i-1}$，若第 $i-1$ 列的前 $h_{i}$ 个色块没有存在相邻两格同颜色的情况，则存在两种填写方式；若存在相邻两格同颜色的情况，则只存在一种填色方式。
- 若 $h_i>h_{i-1}$，则对于第 $i$ 列的前 $h_{i-1}$ 个方格同理，对于后 $h_i-h_{i-1}$ 个方格，可以随意填写颜色。

综上，除了阶段之外，我们还会关注有哪些行对之间颜色相同，但这种状态的记录是复杂的。再深入思考，我们发现我们只关注相同颜色对是否存在——只要存在一对就好了。而较高的颜色对更可能会被后面高度较小的列削掉，所以其实我们只需要关注最低的相同颜色对位置即可。

那么到目前为止，我们就可以设 $dp_{i,j}$ 表示计数前 $i$ 列后，第 $i$ 列最低相同颜色对为 $(i,j)$ 和 $(i,j+1)$ 的方案数。 

但是 $h_i$ 范围太大了！进一步地，由于 $dp_{i,j}$ 的第二维只是为了判断当前是否会被削掉，所以不妨直接一步到位，将第二维 $j$ 的含义变成，最低相同颜色对会在第 $j$ 列被削掉。此时总状态数就是 $O(n^2)$ 了。

转移时类似于我们分析的过程，根据 $h$ 的大小关系分类转移即可。

转移方程很好写，就不再赘述。具体细节见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=105;
const int mod=1e9+7;
int n,a[N];
ll dp[N][N];
int read(){
	int w=0,fh=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') fh=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*fh;
}
ll ksm(ll x,ll y){
    ll ans=1;
    while (y){
        if (y&1) ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
ll work(int l,int r){
    return (ksm(2,r+1)-ksm(2,l)+mod)%mod;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	n=read();
    for (int i=1;i<=n;i++) a[i]=read();
    for (int i=2,minn=a[1];i<=n;i++){
        if (a[i]<minn){
            // for (int j=a[i];j<minn;j++){
            //     dp[1][i]=(dp[1][i]+ksm(2,a[1]-j))%mod;
            // }
            dp[1][i]=(dp[1][i]+work(a[1]-minn+1,a[1]-a[i]))%mod;
            minn=a[i];            
        }
        if (i==n){
            // for (int j=1;j<minn;j++)
            //     dp[1][n+1]=(dp[1][n+1]+ksm(2,a[1]-j))%mod;
            dp[1][n+1]=(dp[1][n+1]+work(a[1]-minn+1,a[1]-1))%mod;
        }
    }
    dp[1][0]=2;
    for (int i=2;i<=n;i++){
        if (a[i]<=a[i-1]){
            dp[i][0]=(dp[i-1][0]*2+dp[i-1][i]*2)%mod;
            for (int j=i+1;j<=n+1;j++) dp[i][j]=dp[i-1][j]%mod;
        }else{
            dp[i][0]=dp[i-1][0]*2%mod;
            for (int j=i+1,minn=a[i];j<=n+1;j++){
                if (j<=n){
                    if (a[j]>=minn) continue;
                    // for (int k=max(a[i-1],a[j]);k<minn;k++){
                    //     dp[i][j]=(dp[i][j]+dp[i-1][0]*ksm(2,a[i]-k)%mod)%mod;
                    // }
                    dp[i][j]=(dp[i][j]+dp[i-1][0]*work(a[i]-minn+1,a[i]-max(a[i-1],a[j])%mod)%mod);
                    minn=max(a[i-1],a[j]);                    
                }else{
                    // for (int k=a[i-1];k<minn;k++)
                    //     dp[i][n+1]=(dp[i][n+1]+dp[i-1][0]*ksm(2,a[i]-k)%mod)%mod;
                    dp[i][n+1]=(dp[i][n+1]+dp[i-1][0]*work(a[i]-minn+1,a[i]-a[i-1])%mod)%mod;
                }
            }
            for (int j=i+1;j<=n+1;j++) dp[i][j]=(dp[i][j]+dp[i-1][j]*ksm(2,a[i]-a[i-1])%mod)%mod;
        }
    }
    cout<<(dp[n][n+1]+dp[n][0])%mod<<"\n";
	return 0;
}
```



---

## 作者：_lfxxx_ (赞：1)

令红色为 $0$，蓝色为 $1$。

考虑一行一行填这个网格。

注意到大部分的 $01$ 序列想继续填下去每一位都要翻转，只有 $01$ 交错序列除了可以翻转，还可以不变化。

因此我们建出笛卡尔树后，考虑 dp。

记 $len_u$ 表示 $u$ 这一段的长度，$he_u$ 表示 $u$ 这一段的高度，$son(u)$ 为 $u$ 的儿子集合。

设 $f_u$ 表示 $u$ 这一段的总方案数，$g_u$ 表示 $u$ 这一段非 $01$ 交错方案数，$h_u$ 表示 $u$ 这一段 $01$ 交错方案数。

先不考虑高度的影响：

$$
f_u = \prod_{v\in son(u)}(g_v+2h_v) \times 2^{len_u - \sum_{v\in son(u)}len_v}\\
h_u = 2 \times \prod_{v \in son(u)} h_v\\
g_u=f_u - h_u
$$

再考虑高度的影响：

$$
h'_u=h_u \times 2^{he_u-1}\\
f_u = g_u + h'_u
$$

$f_1$ 即为答案。

复杂度取决于建笛卡尔树的复杂度，$O(n \log n)$ 或 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define i128 __int128
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
bool be;
constexpr int N = 205, mod = 1e9 + 7;
int n, len[N], a[N], he[N], f[N], g[N], h[N], tmp[N], cnt, tot;
vector<int>e[N];
inline int qpow(int b, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = (ll) res * b % mod;
		b = (ll) b * b % mod;
		k >>= 1;
	}
	return res;
}
inline int findpos(int x, int y)
{
	for (int i = x; i < n; ++i) {
		if (!(y <= a[i + 1])) {
			return i;
		}
	}
	return n;
}
void dfs(int u)
{
	f[u] = 1, h[u] = 2;
	int l = len[u];
	for (int v : e[u]) {
		dfs(v);
		l -= len[v];
		f[u] = f[u] * (((ll) g[v] + (ll) 2 * h[v]) % mod) % mod;
		h[u] = (ll) h[u] * h[v] % mod;
	}
	f[u] = (ll) f[u] * qpow(2, l) % mod;
	g[u] = (f[u] - h[u]) % mod;
	h[u] = (ll) h[u] * qpow(2, he[u] - 1) % mod;
	f[u] = (g[u] + (ll) h[u]) % mod;
}
bool en;
int main()
{
	cerr << (&be - &en) / 1024.0 / 1024 << " MB\n--------------------------------" << endl;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		tmp[++tot] = a[i];
	}
	sort(tmp + 1, tmp + 1 + tot), tot = unique(tmp + 1, tmp + 1 + tot) - tmp - 1;
	map<int, int>mp;
	mp[1] = 0;
	for (int i = 1; i <= tot; ++i) {
		vector<pii>v;
		for (int j = 1; j <= n; ++j) {
			if (tmp[i] <= a[j]) {
				int p = findpos(j, tmp[i]), fa = prev(mp.upper_bound(j)) -> second;
				len[++cnt] = p - j + 1, he[cnt] = tmp[i] - tmp[i - 1];
				if (len[fa] == len[cnt]) {
					he[fa] += he[cnt];
					--cnt;
					j = p;
					continue;
				}
				if (fa) {
					e[fa].emplace_back(cnt);
				}
				v.emplace_back(j, cnt);
				j = p;
			}
		}
		for (auto [x, y] : v) {
			mp[x] = y;
		}
	}
	dfs(1);
	cout << (f[1] + mod) % mod << endl;
	return 0;
}
```

---

## 作者：Lyrella (赞：0)

# 简要题意

就是给每个格子染成黑色或白色，需要保证每个 $2\times2$ 的区域都有两黑两白。问方案数。

数据范围：$n\le100$。

# 思路

我们先从最简单的情况入手。比如现在所有格子构成一个矩形，若我确定了第一列后，下一列会出现什么情况？

不难发现我们一直可以对上一列的颜色全部取反得到下一列；特殊情况就是上一列黑白交替出现时我们还可以直接继承上一列状态。

也就是说我们关心的其实是每一列上黑白交替的结束点，于是就可以用一个 $\text {dp}$ 记录。具体的，我们设 $f_{i,j}$ 表示考虑了前 $i$ 列，黑白交替结束点是第 $j$ 行的合法方案数。

考虑如何转移，仔细一想你会发现需要分类讨论一下。

对于前一列的行高度大于当前高度时，不看最上面的点，你会发现其实你当前列的染色方案其实已经唯一确定。
所以有 $f_{i,j}=f_{i-1,j}$。对于最上面的点，我们不知道前一列的结束点在哪里，只知道一个大概范围，于是就可以枚举进行转移。这时因为对于当前行是全交替的所以有两种染色方案，转移方程为 $f_{i,h_i}=2\times f_{i-1,j},h_i\le j\le h_{i-1}$。

对于前一列的行高度小于当前高度时，对于第一行到第 $h_{i-1}$ 行都是唯一确定的，但是更高的地方就没有任何限制，所以就乘上一个二的次幂。$f_{i,j}=f_{i-1,j}\times2^{h_i-k},k=\max\{h_{i-1},j\}$。

但是醒醒，你的行高有 $10^9$，这不炸钢了？还真不，因为你直接离散化过后记录一横行的方案和即可。

# 代码

```cpp
signed main(){
    n = rd();
    for(int i = 1; i <= n; ++i)a[i] = b[i] = rd();
    b[m = n + 1] = 1;
    sort(b + 1, b + 1 + m); m = unique(b + 1, b + 1 + m) - b - 1;
    for(int i = 1; i <= n; ++i)a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b; b[m + 1] = p;
    for(int i = 1; i <= a[1]; ++i)f[i] = 2ll * del(qmi(2, b[a[1]] - b[i]), qmi(2, b[a[1]] - b[i + 1])) % p;
    for(int i = 2; i <= n; ++i)if(a[i] >= a[i - 1]){
        int t = f[a[i - 1]];
        for(int j = 1; j < a[i - 1]; ++j)f[j] = 1ll * f[j] * qmi(2, b[a[i]] - b[a[i - 1]]) % p;
        for(int j = a[i - 1]; j <= a[i]; ++j)f[j] = 2ll * t * del(qmi(2, b[a[i]] - b[j]), qmi(2, b[a[i]] - b[j + 1])) % p;
    }
    else{
        f[a[i]] = 2ll * f[a[i]] % p;
        for(int j = a[i] + 1; j <= a[i - 1]; ++j)f[a[i]] = add(f[a[i]], add(f[j], f[j])), f[j] = 0;
    }
    for(int i = 1; i <= a[n]; ++i)ans = add(ans, f[i]);
    cout << ans;
    return 0;
}
```

---

