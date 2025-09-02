# ソリティア

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2016/tasks/joisc2016_c



# 题解

## 作者：Illus1onary_Real1ty (赞：2)

观察一个重要性质：如果第一或第三行出现连续两个空位的结构，或者四角上有空位，那么一定无解，因为这些格子并不能满足条件一或二。

填充的顺序相当于填数的过程，第二行一定是形如一个个单独连通块的情况，所以考虑 dp 每一个连通块的方案数，然后组合计数整合。

考虑朴素的 dp，显然这种求填数方案类的题可以参考 AT_dp_t 的状态定义，但与之不同，我们需要知道第二行上的格子是由于满足条件一被填充还是满足条件二，考虑升维 dp。

于是有状态定义 $dp_{i, j, k}$ 表示 dp 到第 $i$ 列，第二行第 $i$ 列目前编号在已填的格子里排位第 $j$，通过条件一或二被填充。

有一个细节，就是某些格子既可以满足条件一也可以满足条件二，这时候先填上下格，再填当前格的顺序会被重复计算，我们可以钦定它是因满足条件一被填充。

考虑初始化，对于每个连通块的初始格，当其上下皆有棋子时，由于前文的钦定，有 $dp_{i, 1, 0} = 1$，反之可以更新所有相关合法 dp 值。

考虑转移，分类讨论，如果当前格子因为条件一被填充，前一个格子既可以是因条件一填充的，也可以因条件二填充的，注意到如果上一个格子由于条件二被填充，其排位一定比当前格靠后，注意转移时乘上当前格子上下格子被填充顺序的排列数。

如果当前格子是因为条件二被填充的，前一个格子必然是因条件一填充的，可以通过组合算出当前格子上下格子被填充顺序的系数，注意到前文的钦定，一定有当前格子上下格子中的至少一个在当前格之后被填充。

直接转移显然是大常数 $O(n^3)$，考虑前缀和优化做到 $O(n^2)$，轻松通过。

细节很多，给出代码：[CODE。](https://loj.ac/s/2144450)

---

## 作者：lalaouye (赞：1)

赛前写一个久违的 dp 题解吧，感觉这题不是很难，因为性质非常好想，几乎只存在数数上的难点。

首先显然四个角必须得预先放上棋子，并且在边上不允许出现两个格子连起来，然后这题性质就到这了，只需要对着满足性质的图计数就行了。

我们发现这题唯一棘手的地方是中间连续段的处理，问题差不多是在一条链上，每个点要么是两边都放上了棋子自己再放，要么利用自己上面的和下面的棋子放。那么我们可以考虑一个区间 dp，设 $f(l,r)$ 表示该区间的答案，转移枚举最后一个放上棋子的点，再用组合数去合并区间即可。但是这样子是 $\mathcal{O}(n^3)$ 的，并且感觉没啥优化空间，我们考虑修改或者优化一下状态。

既然区间不行我们考虑设计对于前缀的 dp，设 $f(i,0/1)$ 表示 $[1,i]$ 的答案，并且最后一个点是利用上下的还是利用两边的。但是我们发现若要利用两边的棋子则需要满足两边棋子放的比中间的早，那么我们设 $f(i,j,0/1)$ 表示在 $[1,i]$ 中，最后一个点是在前面的第 $j$ 次放入，是利用左右还是上下放的棋子的方案数。如果我们考虑将新操作插入到原来的操作中去，这样一来我们发现转移是在区间中，意味着这个 dp 是有前途的。

仔细分析一下转移，首先考虑从 $0$ 到 $1$ 的转移，我们需要满足放的比前面早，那么 $f(i,j,0)\leftarrow f(i-1,k,1)$ 需要满足 $k\ge j-cnt$，$cnt$ 表示当前点上下有几个空位。$0$ 转移到 $0$ 随便转移。

再考虑 $1$ 到 $0$ 的转移，与刚刚相似，但是得对 $cnt$ 分讨一下。用前缀和优化即可做到 $\mathcal{O}(n^2)$。但是这题不止一条链，得最后把它们组合起来。

代码（含 $\mathcal{O}(n^3)$ 注释转移代码）：


```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
#define rep(i, l, r) for (int i (l); i <= r; ++ i)
#define rrp(i, l, r) for (int i (r); i >= l; -- i)
#define eb emplace_back
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
#define pii pair <int, int>
#define inf 1000000000
#define ls (p << 1)
#define rs (ls | 1)
constexpr int N = 2000 + 5, M = 1e5 + 5, P = 1e9 + 7;
typedef long long ll;
typedef unsigned long long ull;
inline __int128_t rd () {
  __int128_t x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y) {
  int ret (1);
  for (; y; y >>= 1, x = x * x % P) if (y & 1) ret = ret * x % P;
  return ret;
}
int n;
char s[3][N];
int f[N][N << 1][2], g[N][N << 1][2];
pii pa[N << 1];
int fac[M], ifac[M];
int C (int n, int m) {
  if (m > n) return 0;
  return fac[n] * ifac[m] % P * ifac[n - m] % P;
}
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  fac[0] = 1;
  rep (i, 1, M - 1) fac[i] = fac[i - 1] * i % P;
  ifac[M - 1] = qpow (fac[M - 1], P - 2);
  rrp (i, 1, M - 1) ifac[i - 1] = ifac[i] * i % P;
  n = rd ();
  scanf ("%s", s[0] + 1);
  scanf ("%s", s[1] + 1);
  scanf ("%s", s[2] + 1);
  rep (i, 2, n) {
    if (s[0][i] == 'x' && s[0][i - 1] == 'x') return puts ("0") * 0;
    if (s[2][i] == 'x' && s[2][i - 1] == 'x') return puts ("0") * 0;
  }
  if (s[0][1] == 'x' || s[0][n] == 'x' || s[2][1] == 'x' || s[2][n] == 'x') return puts ("0") * 0;
  int tot (0);
  rep (l, 1, n) {
    if (s[1][l] == 'o') {
      if (s[0][l] == 'x') pa[++ tot] = pii (1, 1);
      if (s[2][l] == 'x') pa[++ tot] = pii (1, 1);
      continue;
    }
    int cnt (0);
    int r (l);
    while (r < n && s[1][r + 1] == 'x') ++ r;
    if (s[0][l] == 'x') ++ cnt;
    if (s[2][l] == 'x') ++ cnt;
    f[l][cnt + 1][0] = 1 + (cnt > 1);
    g[l][cnt + 1][0] = f[l][cnt + 1][0];
    if (l != 1) {
      g[l][1][1] = f[l][1][1] = cnt;
      g[l][2][1] = g[l][3][1] = cnt;
      if (cnt > 1) f[l][2][1] = 2, g[l][2][1] += 2, g[l][3][1] += 2;
    }
    int sum (cnt + 1);
    rep (i, l + 1, r) {
      cnt = 0;
      if (s[0][i] == 'x') ++ cnt;
      if (s[2][i] == 'x') ++ cnt;
      rep (j, 1, sum + cnt + 1) {
        if (j >= cnt + 1) {
          int mul = 1;
          if (cnt == 2) mul = 2;
          // rep (k, 1, sum) {
          //   if (k >= j - cnt)
          //   (f[i][j][0] += f[i - 1][k][1] * C (j - 1, cnt) * mul) %= P;
          //   (f[i][j][0] += f[i - 1][k][0] * C (j - 1, cnt) * mul) %= P;
          // }
          f[i][j][0] = (g[i - 1][sum][0] + g[i - 1][sum][1] + P - g[i - 1][j - cnt - 1][1]) * C (j - 1, cnt) * mul % P;
        }
        if (cnt == 1) {
          // rep (k, 1, min (sum, j - 1)) {
          //   (f[i][j][1] += f[i - 1][k][0] * (sum + 2 - j)) %= P;
          // }
          f[i][j][1] = g[i - 1][min (sum, j - 1)][0] * (sum + 2 - j) % P;
        }
        if (cnt == 2) {
          // rep (k, 1, min (sum, j - 2)) {
          //   (f[i][j][1] += 2 * f[i - 1][k][0] * (j - 1) * (sum + 3 - j)) %= P;
          // }
          f[i][j][1] = (2 * g[i - 1][min (sum, j - 2)][0] * (j - 1) * (sum + 3 - j) + 2 * g[i - 1][min (sum, j - 1)][0] * C (sum + 3 - j, 2)) % P;
          // rep (k, 1, min (sum, j - 1)) {
          //   (f[i][j][1] += 2 * f[i - 1][k][0] * C (sum + 3 - j, 2)) %= P;
          // }
        }
        g[i][j][0] = (g[i][j - 1][0] + f[i][j][0]) % P;
        g[i][j][1] = (g[i][j - 1][1] + f[i][j][1]) % P;
      } sum += cnt + 1;
    }
    int ret (0);
    rep (i, 1, sum) ret += f[r][i][0];
    if (r != n) rep (i, 1, sum) ret += f[r][i][1];
    ret %= P;
    pa[++ tot] = pii (ret, sum);
    l = r;
  }
  int ans (1);
  int sum (0);
  rep (i, 1, tot) {
    ans *= pa[i].first;
    ans %= P;
    sum += pa[i].second;
    (ans *= C (sum, pa[i].second)) %= P;
  } cout << ans; puts ("");
}
```

---

## 作者：Purslane (赞：1)

# Solution

~~想了一个星期毫无进展，最后发现只有 $3$ 行~~。

下面是一些基本的分析。

1. 四个角都有棋子，因为他没有同一方向的两个相邻棋子。
2. 第一行和第三行的空格只能由左右相邻的格子生成，因此**不能由长度超过 $1$ 的空格连续段**，因此这些空格子**可以随时加棋子**，
3. 对于中间行的空格，我们有两种覆盖方式：在上下的格子都被覆盖后，通过上下格子生成这个位置；在左右格子都覆盖后，通过左右格子生成这个位置。注意两个通过左右格子覆盖的位置不能相邻。

考虑设计插入 $\rm DP$：设 $f_{i,j,op}$ 为前 $i$ 列，第 $i$ 列的中心格在位置 $j$（如果没有为 $0$），对下一列是否有限制（即必须在这一列中心格之前出现）。

使用前后缀优化很容易进行转移，不做赘述。注意 $j$ 这一维上界是 $3n$（其实更小，但是方便起见），一些东西要开大一点。

最后答案要求第 $n$ 列没有任何限制。

注：本人最开始想用类似概率的方法处理方格之间的限制，但是悲催的发现在多个限制的情况下概率方法是不适用的。比如三阶排列，想要限制 $1$ 在 $2$ 之前且 $2$ 在 $3$ 之前，其概率实际为 $\dfrac{1}{6}$，但是分别成立的概率是 $\dfrac{1}{4}$（他们是相关的）

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e3+10,MOD=1e9+7;
int n,a[4][MAXN],dp[MAXN][MAXN*3][2],C[MAXN*3][5];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,0,6009) {
		C[i][0]=1;
		ffor(j,1,min(4ll,i)) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;	
	}
	ffor(i,1,3) {
		string S;
		cin>>S;
		ffor(j,1,n) if(S[j-1]=='x') a[i][j]=1;
	}
	if(a[1][1]||a[1][n]||a[3][1]||a[3][n]) return cout<<0<<'\n',0;
	ffor(i,1,n-1) if(a[1][i]&&a[1][i+1]||a[3][i]&&a[3][i+1]) return cout<<0<<'\n',0;
	dp[1][a[2][1]][0]=1;
	int s=a[2][1];
	ffor(i,1,n-1) {
		int ss=s+a[1][i+1]+a[2][i+1]+a[3][i+1];
		if(a[2][i+1]==0) {
			int sum=0;
			int ot=a[1][i+1]+a[3][i+1];
			ffor(j,0,s) sum=(sum+dp[i][j][0]+dp[i][j][1])%MOD;
			dp[i+1][0][0]=sum*C[ss][ss-s]%MOD*((ot==2)?2:1)%MOD;
			s=ss;
			continue ;	
		}
		int pre[MAXN*3];
		memset(pre,0,sizeof(pre));
		ffor(j,0,s) pre[j]=dp[i][j][0];
		ffor(j,1,s) pre[j]=(pre[j]+pre[j-1])%MOD;
		if(a[1][i+1]||a[3][i+1]) {
			ffor(j,1,ss) {
				if(a[1][i+1]&&a[3][i+1]) {
					if(j>=2) dp[i+1][j][1]=(dp[i+1][j][1]+pre[j-2]*2%MOD*(j-1)%MOD*(ss-j))%MOD;
					dp[i+1][j][1]=(dp[i+1][j][1]+pre[j-1]*(ss-j)%MOD*(ss-j-1))%MOD;
				} 
				else {
					dp[i+1][j][1]=(dp[i+1][j][1]+pre[j-1]*(ss-j))%MOD;	
				}
			}
		}
		int sum=0;
		ffor(j,0,s) sum=(sum+dp[i][j][0])%MOD;
		int suf[MAXN*3];
		memset(suf,0,sizeof(suf));
		ffor(j,1,s) suf[j]=dp[i][j][1];
		roff(j,s-1,1) suf[j]=(suf[j]+suf[j+1])%MOD;
		int ot=a[1][i+1]+a[3][i+1];
		ffor(j,1+ot,ss) dp[i+1][j][0]=(dp[i+1][j][0]+(sum+suf[j-ot])%MOD*C[j-1][ot]%MOD*((ot==2)?2:1))%MOD;
		s=ss;
	}
	int sum=0;
	ffor(j,0,s) sum=(sum+dp[n][j][0])%MOD;
	cout<<sum<<'\n';
	return 0;
}
```

---

