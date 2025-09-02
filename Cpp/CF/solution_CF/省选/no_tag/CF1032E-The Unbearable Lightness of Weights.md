# The Unbearable Lightness of Weights

## 题目描述

你有 $n$ 个砝码。你知道它们的质量分别为 $a_1$、$a_2$、…、$a_n$ 克，但你不知道每个砝码具体是哪一个质量。你无法区分这些砝码。

然而，你的朋友知道每个砝码的质量。你可以请求你的朋友给你恰好 $k$ 个砝码，并且这 $k$ 个砝码的总质量为 $m$（$k$ 和 $m$ 都由你选择），如果存在满足条件的子集，你的朋友会指出任意一个有效的子集。

你只允许进行一次这样的询问。请你求出在这次询问后，你最多能确定多少个砝码的具体质量。

## 说明/提示

在第一个样例中，你可以请求一个总质量为 $4$ 的两个砝码的子集，唯一的选择是 $\{2, 2\}$。

另一种方法是请求一个总质量为 $5$ 的两个砝码的子集，得到 $\{1, 4\}$。很容易看出，剩下的两个砝码的质量都是 $2$ 克。

在第二个样例中，你可以请求一个总质量为 $8$ 的两个砝码的子集，唯一的答案是 $\{4, 4\}$。可以证明一次询问无法确定三枚砝码的质量，但这里不做证明。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 4 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
1 2 4 4 4 9
```

### 输出

```
2
```

# 题解

## 作者：shurongwang (赞：7)

考虑只有一种重量时, 明显可以确定每个球分别对应什么重量，毕竟只有一种重量能对应.

只有两种重量时, $w_1$ 位第一种的重量, $w_2$ 是另一种, $t_1$ 为第一种重量的球的个数, $t_2$ 同理, $s_1=t_1\times w_1$, $s_2=t_2\times w_2$.

那么我们只要问 $max\{s_1,s_2\}$, 和其重量 $w$, 就可以确定所有的球的重量了; 因为问完后, 一定可以确定所有是那种重量的球, 剩下的也一定是另外一种重量的球.

故一共只有 $1$ 或 $2$ 种重量的球时, 答案就是 $n$ (球的总数).


------------

再考虑两种以上的情况:

我们不得不问同一种重量, 不然我们不能确定回答的球的集合内的球的重量分别是什么.

而且我们要问的相同的重量的球的数量要越大越好.

设 $w$ 为问的重量, $t$ 为数量, 总质量 $s = w \times t$.
如果整个序列中能组成总质量为 $s$ 的球的所有集合内, 元素有且仅有 $w$, 那么, $t$ 就是一个合法的答案. (当然, 我们要找最大的 $t$)

设 $dp[s][t]$ 为用 $t$ 个球可以组成总重量为 $s$ 的球的集合的方案数.

$dp[s][t]=dp[s][t]+dp[s-a_i][t-1]$, $dp[0][0]=1$; ($a_i$ 为第 $i$ 个的重量)

如果 $dp[w\times t][t] == \binom{cnt_w}{t}$ ($cnt_w$ 为 质量为 $w$ 的球的个数), 也就是说所有组成总质量 $s=w\times t$ 的集合内有且仅有质量为 $w$ 的球;

```cpp

#include <bits/stdc++.h>

#define null               ""
#define endl               '\n'
#define all(dat)           dat.begin(), dat.end()
#define over(msg)          cout << msg << endl, exit(0);
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fr, to)    for (int i = fr; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int n, t, mx, a[105], C[105][105], sum, cnt[105], ans = 1, mod = 1e6 + 7;
map<pair<int, int>, int> dp, pre;

int inline read() {
    int res = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar());
    for (; isdigit(c); res *= 10, res += c ^ 48, c = getchar());
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    n = read();
    cont (i, n) {
        a[i] = read();
        sum += a[i];
        mx = max(mx, a[i]);
        if (++cnt[a[i]] == 1) {
            ++t;
        }
    }
    
    // 预处理组合数 C(n, m).
    circ (i, 0, n) {
        C[i][0] = C[i][i] = 1;
        circ (j, 1, i - 1) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1] % mod;
        }
    }
    
    // dp 求方案数.
    dp[make_pair(0, 0)] = pre[make_pair(0, 0)] = 1;
    cont (i, n) {
        foreach (it, pre) {
            pair<int, int> cur = make_pair(it->first.first + a[i], it->first.second + 1);
            dp[cur] += it->second;
            dp[cur] %= mod;
        }
        pre = dp;
    }
    
    // 处理答案.
    if (t == 2 || t == 1) {
        cout << n << endl;
        return 0;
    }
    cont (w, mx) {
        circ (t, 2, cnt[w]) {
            if (dp[make_pair(w * t, t)] == C[cnt[w]][t]) {
                ans = max(ans, t);
            }
        }
    }
    cout << ans << endl;
}

```


---

## 作者：baka24 (赞：4)

考虑预处理出 $f_{i,j,k}$ 表示在前 $i$ 个数中选 $j$ 个数和为 $k$ 的方案数。  
有 $f_{i,j,k}=f_{i-1,j,k}+f_{i-1,j-a_i,k-1}$，第一维可以直接压掉。

设 $i,j$ 表示我们希望选出 $j$ 个 $i$。设 $num_i$ 表示 $i$ 的出现次数，发现如果 $f_{n,j,i\times j}=C_{num_i}^{j}$ 那么这样选一定只会选出只有 $i$ 的 $j$ 个数，我们就可以确定这 $j$ 个数是 $i$。  
然后对于符合条件的 $(i,j)$ 求最大的 $i$ 即可。

但这样不完全对，你会发现如果只有两种数，你选了其中一种全部的数，剩下的数是什么你也会知道。  
所以还需要特判一下如果数字种数只有 $2$ 且 $j=num_i$，答案为 $n$。

### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=210,Mod=998244353;
int n,a[MAXN],ans,f[MAXN*MAXN][MAXN],num[MAXN],jc[MAXN],ny[MAXN];
int fl=0;
int C(int x,int y){
	return jc[x]*ny[y]%Mod*ny[x-y]%Mod;
}
int Pow(int x,int y){int rt=1;while(y){if(y&1)rt=rt*x%Mod;x=x*x%Mod;y>>=1;}return rt;}
void slv(){
	scanf("%lld",&n);jc[0]=1;ny[0]=1;
	for(int i=1;i<=100;i++)jc[i]=jc[i-1]*i%Mod,ny[i]=Pow(jc[i],Mod-2);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(!num[a[i]])fl++;
		num[a[i]]++;
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=10000;j>=a[i];j--){
			for(int k=i;k>=1;k--){
				f[j][k]+=f[j-a[i]][k-1];
				f[j][k]%=Mod;
			}
		}
	}
	for(int i=1;i<=100;i++){
		for(int j=num[i];j>=1;j--){
			if(f[i*j][j]==C(num[i],j)){
				ans=max(ans,j);
				if(fl<=2&&j==num[i])ans=n;
				break;
			}
		}
	}
	printf("%lld",ans);
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1032E)

看样例就可以知道，你必须询问一堆一样的数才可能猜中。

那考虑判断选 $i$ 个 $x$ 的方案数，设 $x$ 出现的次数为 $c_x$，如果这个方案数等于 $\dbinom{c_x}{i}$，就说明正好是从 $c_x$ 个相同数里选 $i$ 个，也就是说选的这 $i$ 个数都是相等的。

方案数的计算可以直接 dp，设 $dp_{i,j,k}$ 表示前 $i$ 个数选 $j$ 个总和为 $k$ 的方案数，那么转移就是 $dp_{i,j,k}=dp_{i-1,j,k}+dp_{i-1,j-1,k-a_i}$，滚动数组滚掉一维即可。为了防止溢出可以随便找个模数把 dp 值和方案数同时取模之后再比较。

然后你会发现，如果只有两个数的情况下，你猜到一个数就等于也猜到了另一个，同理只有两种数是一样的。因此如果数的种数 $\le 2$，那就都可以猜到。

做完了。

---

## 作者：adolphshi (赞：1)

## 题意

翻译给的很明确了~~机翻看了半天才看懂~~。

## 思路

~~因为机翻看了半天，所以把样例搞懂了~~\
我们首先观察样例，在样例解释中告诉了第一组样例的选择方法。

我们可以首先发现两件事情：

1. 对于一种可行的选法，选择它的补集也是可以的。这一点样例解释一说过了。
2. 所有可能的选法都是只选同一种数字或者其补集。

对于第二个发现：

我们假设有一个可行的方案，它里面包含了两种数，那么我们在得到这个集合后并不能将这两种数对应的砝码区分开。因此这个方案中只能包含一个数。

我们接下来考虑对于什么样的一组方案，它能成为解。我们发现一个方案能成为解，当且仅当这些数的和 $m$ 和个数 $k$ 相同的只有这一种方案（数值相同的算一种）。

那么好了，我们的约束都已经出来了，发现数据范围都 $\leq 100$ 果断用背包，在多一维当个数 $k$。因为数值相同的算作同一种方案，因此使用分组背包即可。

此外，还需要特判当不同数字的种类数小于两种的时候，我们直接输出 $n$ 即可，因为我们选出一种数，它们的补集我们也就唯一确定了。

## code

```cpp
#include <bits/stdc++.h>
#define _F(x,y,z) for(int x=y;x<=z;x++)
#define F_(x,z,y) for(int x=z;x>=y;x--)
#define TF(x,y,z) for(int x=head[y],z;x;x=nex[x])

using namespace std;

typedef long long ll;
typedef double dou;
typedef const int ci;
typedef pair<int,int> pii;

ci maxn=2e4+10;

int n,a[maxn],cnt[maxn],sum,dp[maxn][110],ans,tot;
int main()
{
	scanf("%d",&n);
	_F(i,1,n)
		scanf("%d",&a[i]),cnt[a[i]]++,sum+=a[i];
	dp[0][0]=1;
	_F(i,1,100)
	{
		if(!cnt[i]) continue;
		tot++;
		F_(j,10000,1)
		{
			F_(k,n,1)
			{
				_F(l,1,cnt[i])
				{
					if(j<i*l)
						break;
					dp[j][k]+=dp[j-i*l][k-l];
				}
			}
		}
	}
	if(tot==2)
	{
		printf("%d",n);
		return 0;
	}
	_F(i,1,100)
	{
		while(dp[i*cnt[i]][cnt[i]]!=1)
			cnt[i]--;
		ans=max(ans,cnt[i]);
	}
	printf("%d",ans);
	return 0;
}
```

~~建议降蓝（大雾~~

---

## 作者：红黑树 (赞：1)

[可能更好的阅读体验](https://rbtr.ee/CF1032E)

## [题目](https://codeforces.com/problemset/problem/1032/E)

## 题解
这个限制其实很严格，你发现如果只要返回的砝码中有两个不同质量的，那你就完全不可能确定出来任何一个砝码的位置。

那么因此当只可能用质量全部相同的一些砝码称出想要的质量时，你才可能对应出砝码和位置。

设 $f_{i, j, k}$ 表示只用前考虑 $i$ 个砝码，用了 $j$ 个，目前综合为 $k$ 的方案数。

如果 $f_{n, j, a_i} = \binom{cnt_j}j$，那么就说明我们满足了上述要求，其中 $cnt_j$ 表示质量为 $j$ 的砝码个数。取最大的 $j$ 作为答案。

$n = 2$ 时需要特判。

## 代码
```cpp
/* C++17 is required!
 * By Koicy (https://koicy.ly)
 * Email n@rbtr.ee
 * I've reached the end of my fantasy.

         __    __                             __         _
   _____/ /_  / /_________  ___              / /______  (_)______  __
  / ___/ __ \/ __/ ___/ _ \/ _ \   ______   / //_/ __ \/ / ___/ / / /
 / /  / /_/ / /_/ /  /  __/  __/  /_____/  / ,< / /_/ / / /__/ /_/ /
/_/  /_.___/\__/_/   \___/\___/           /_/|_|\____/_/\___/\__, /
                               SIGN                         /___*/
#ifndef XCODE
constexpr bool _CONSOLE = false;
#else
constexpr bool _CONSOLE = true;
#endif
#define __NO_MAIN__ false
#define __ENABLE_RBLIB__ true
constexpr bool _MTS = false, SPC_MTS = false;
constexpr char EFILE[] = "";
#define FULL(arg) arg.begin(), arg.end()

// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  constexpr tp mod = 2021721727;
  tp n = bin;
  vetp a = bin.vcr(n, 1);
  vector f(n + 1, vetp(n * 100 + 1));
  f[0][0] = 1;
  for (tp i = 1; i <= n; ++i) {
    vector g = f;
    for (tp j = 0; j <= i; ++j) {
      for (tp k = 0; k <= n * 100; ++k) {
        g[j][k] = f[j][k];
        if (k >= a[i] && j >= 1) g[j][k] = (g[j][k] + f[j - 1][k - a[i]]) % mod;
      }
    }
    f.swap(g);
  }
  map<tp, tp> cnt;
  for (tp i = 1; i <= n; ++i) ++cnt[a[i]];
  if (cnt.size() <= 2) {
    bin << n << '\n';
    return 0;
  }
  tp tar = 0;
  for (auto& [i, p] : cnt) {
    for (tp j = 1; j <= p; ++j) {
      if (f[j][i * j] == RCAL::binom(p, j, mod)) tar = max(tar, j);
    }
  }
  bin << tar << '\n';
  return 0;
}

void MIST() {
}

// :\ */
```

---

## 作者：MoyunAllgorithm (赞：0)

新手友好的紫题，思维难度低，但有一些细节。

首先，能够想到 **选出的集合一定每个元素都相同**。假设你知道两个砝码是 $1$ 和 $4$，但你无法知道谁是 $1$ 谁是 $4$。然而，如果你知道两个砝码都是 $4$，你就知道每个砝码的具体数值。

然而根据题面，我们实际是在询问集合的元素和。为了保证我们所询问的集合一定是元素相同的，我们应保证：**所有选出 $k$ 个数且和为 $m$ 的方案均是元素相同的**。

自然会想到 dp。定义 $\text{dp}(i,j,k)$ 表示：在前 $i$ 个砝码中选出 $j$ 个使得和为 $k$ 的方案数。每个砝码可以选择选取或不选，因此：

$\text{dp}(i,j,k)=\text{dp}(i-1,j-1,k-a_i)+\text{dp}(i-1,j,k)$。

时间复杂度是 $O(N \times N \times N \times a_i)=O(N^4)$ 的，可以通过，但空间复杂度也是 $O(N^4)$。可是可以通过滚动数组降维为 $O(N^3)$。

假设有 $c(i)$ 个为 $i$ 的砝码。枚举 $j \in [1,c(i)]$，若 $\text{dp}(N,j,j \times i)= \text{C}_{c(i)}^{j}$，则 $(j,j \times i)$ 是一个可以让我们确定 $j$ 个砝码信息的询问。为什么？等号前者是原序列中选择 $j$ 个数且和为 $j \times i$ 的方案数；后者是在所有 $i$ 中选 $j$ 个的方案数。容易发现后者被前者包含，故若两者相等则说明不存在一个选取非相同元素集合的选取方法，符合条件。

一处细节：不建议给 $\text{dp}$ 和组合数取模。但注意到其值 $\le 2^{100}$，故可以使用 `__int128` 存储（这在正式比赛中也是可以的！）。

交了后发现不对。手捏了一组数据：

```
2
1 2
```

输出为 $1$，但答案为 $2$。当一共只有两种砝码时，确定一种就可以确定另一种，需要特判。

---

## 作者：NoirCube1 (赞：0)

观察样例 $1$ 得到有两种询问方式：

- 询问 $S$ 满足 $\forall i,j\in S, a_i=a_j$。
- 询问 $S$ 满足 $\forall i,j\in \complement_a^S,a_i=a_j$。

但是什么情况下不合法呢？假如有另一个集合 $A$ 满足：

- $|A|=|S|$
- $\sum_{i\in S}a_i=\sum_{i\in A}a_i$
- $\exists i,j\in S, a_i\not=a_j$

就不合法，因为你不知道你的朋友给你的是 $A$ 和 $S$ 里面哪个。

那么只需要考察对于给定 $m,k$ 对应的 $S$ 是否只有 $\binom{cnt_i}{k}$ 个即可。于是构造生成函数：

$$\prod_{i=1}^{n}(y+x^{a_i})$$

然后暴力拆出来得到：

$$\sum c_{x,y}x^ay^b$$

这里有一个问题，$c_{m,k}$ 并不代表之方案数， 而是 $c_{m,n-k}$。

整个质模数暴力算即可，反正用我的 QQ 号是不会被卡的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[205], blo[205], cnt[205];
const int N = 400005, mod = 2933256077;
namespace nt{int pw(int a,int b,int p=mod){int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}int gcd(int x,int y){return!y?x:gcd(y,x%y);}int exgcd(int a,int b,int&x,int&y){if(!b){x=1,y=0;return a;}int res=exgcd(b,a%b,y,x);y-=(a/b*x);return res;}int inv(int x,int p=mod){exgcd(x,p,x,*new int);return(x%p+p)%p;}} using namespace nt;
struct comb{int fac[N],ifac[N]/*,iv[N]*/;void init(){ifac[0]=fac[0]=1;for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%mod;ifac[N-1]=inv(fac[N-1]);for(int i=N-2;i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;/*iv[1]=1;for(int i=2;i<N;i++)iv[i]=(mod-mod/i)*iv[mod%i]%mod;*/}int binom(int n, int m){if(n<0||m<0||n<m)return 0;return fac[n]*ifac[m]%mod*ifac[n-m]%mod;}};
int f[10005][105], newf[10005][105];
int solve() {
    comb X; X.init();
    int n, sum = 0, all = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    sort(a + 1, a + n + 1);
    //polynomial: prod(x^ai + y)
    f[0][0] = newf[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int x = 0; x <= sum; x++) {
            for(int y = 0; y <= n; y++) {
                int res = 0;
                if(x >= a[i]) res += f[x - a[i]][y];
                if(y >= 1) res += f[x][y - 1];
                newf[x][y] = res % mod;
            }
        }
        for(int x = 0; x <= sum; x++) {
            for(int y = 0; y <= n; y++) {
                f[x][y] = newf[x][y];
            }
        }
    }
    blo[1] = 1;
    for(int i = 1; i <= n; i++) cnt[a[i]]++;
    for(int i = 1; i <= 100; i++) if(cnt[i]) all++;
    if(all < 3) {
        cout << n << endl; return 0;
    }
    for(int i = 2; i <= n; i++) {
        if(a[i] == a[i - 1]) blo[i] = blo[i - 1] + 1;
        else blo[i] = 1;
    }
    int maxn = 1;
    for(int i = 1; i <= n; i++) {
        int res = X.binom(cnt[a[i]], blo[i]);
        // cout << blo[i] << " " << cnt[a[i]] << " " << blo[i] * a[i] << endl;
        if(res == f[blo[i] * a[i]][n - blo[i]]) maxn = max(maxn, blo[i]);
    }
    cout << maxn << endl;
    return 0;
}
signed main() { solve(); system("pause"); return 0; }
```

但是其实和滚一维 `dp` 完全一致。

---

## 作者：_edge_ (赞：0)

感觉这题，挺好想的？

首先，我们先来思考一下，怎么样的情况我们去询问才能确定这些数？

举个简单的例子，如果询问的是两个数即使我们知道了他们是 `1 9` 也不能确定谁是 `1` 谁是 `9`。

很显然一种想法就是去询问全都相等的数才能得到结果。

那么，如果存在一种情况比如

```
2 2 3 1
```

这种情况下，我们不能询问两个总和是 $4$ 的数，因为方案可能有重复。

我们需要做一个背包为 $f_{i,j}$ 表示选了 $i$ 个数，然后总和是 $j$，这东西是一个经典的背包，读者可以尝试自己推导转移方程。

然后我们会发现样例 $2$ 都过不去！

原因是有 `4 4 4`，我们询问 `2 8`，这样会出现 $3$ 种不同的局面，但是即使出现这样子，我们也依旧可以确定。

所以我们需要的是方案数为 $\dbinom{n}{m}$，意义是有 $n$ 个相同数，选 $m$ 个，我们只需要求出来的方案数是这个即可。

我们会发现，这东西没有模数，可以类比哈希，随便取一个模数比如 $10^9+7$ 来做，一般来说是不会冲突的。

还有一种情况就是序列里只有两个数，这样确定一个就能确定另外一个。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=1e4+5;
const int INFN=105;
const int Mod=1e9+7;
int n,f[INFN][INF],sum,a[INF],fav[INF],ifav[INF];
int num[INFN];
int C(int x,int y) {
	if (x<y) return 0;
	return fav[x]*ifav[x-y]%Mod*ifav[y]%Mod;
}
int ksm(int x,int y) {
	int ba=x%Mod,ans=1;
	while (y) {
		if (y&1) ans=(ans*ba)%Mod;
		ba=(ba*ba)%Mod;y>>=1;
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;f[0][0]=1;int sum11=0;
	for (int i=1;i<=n;i++) {
		cin>>a[i],sum+=a[i],num[a[i]]++;
		if (num[a[i]]==1) sum11++;
	}
	int sum1=0;
	int N=100;fav[0]=1;
	for (int i=1;i<=N;i++) fav[i]=fav[i-1]*i%Mod;
	ifav[N]=ksm(fav[N],Mod-2);
	for (int i=N-1;~i;i--) ifav[i]=ifav[i+1]*(i+1)%Mod;
	for (int i=1;i<=n;i++) {
		sum1+=a[i];
		for (int j=i;j>=1;j--)
			for (int l=sum1;l>=a[i];l--) {
				f[j][l]+=f[j-1][l-a[i]];
				f[j][l]%=Mod;
			}
	}
	for (int i=n;i>=1;i--)
		for (int l=sum1;~l;l--) {
//			if (l==8) cout<<i<<" "<<l<<" "<<f[i][l]<<" yiw\n";
			if (f[i][l]==C(num[l/i],i)) {
				if (num[l/i]>=i && l%i==0) ;
				else continue;
				if (sum11==2) cout<<n<<"\n";
				else cout<<i<<"\n";
				return 0;
			}
		}
	return 0;
}
```


---

