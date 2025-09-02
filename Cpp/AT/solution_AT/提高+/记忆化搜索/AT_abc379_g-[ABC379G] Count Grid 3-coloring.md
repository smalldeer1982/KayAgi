# [ABC379G] Count Grid 3-coloring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc379/tasks/abc379_g

`1`,`2`,`3`,`?` からなる $ H $ 行 $ W $ 列のグリッド $ S $ が与えられます。上から $ i $ 行目、左から $ j $ 列目の文字は $ S_{i,j} $ です。

$ S $ の各 `?` を `1`,`2`,`3` のいずれかに置き換えて得られるグリッドは `?` の個数を $ q $ として $ 3^q $ 通りありますが、そのうち以下の条件を満たすものはいくつありますか？ $ 998244353 $ で割った余りを出力してください。

- 隣接する（辺を共有する）どの $ 2 $ つのマスにも異なる数字が書かれている。

## 说明/提示

### 制約

- $ 1\leq\ H,W $
- $ H\times\ W\leq\ 200 $
- $ H,W $ は整数
- $ S $ は `1`,`2`,`3`,`?` からなる $ H $ 行 $ W $ 列のグリッド
 
### Sample Explanation 1

$ S $ の各 `?` を `1`,`2`,`3` のいずれかに置き換えて得られるグリッドのうち、条件を満たすものは以下の $ 6 $ つです。 ``` 12 12 12 13 13 13 21 23 31 21 31 32 ```

### Sample Explanation 2

$ S $ の各 `?` を `1`,`2`,`3` のいずれかに置き換えて得られるグリッドはすべて条件を満たしません。

## 样例 #1

### 输入

```
2 2
1?
??```

### 输出

```
6```

## 样例 #2

### 输入

```
2 3
123
3?1```

### 输出

```
0```

## 样例 #3

### 输入

```
8 8
3?1?????
???1????
??????2?
????????
????????
????13??
??13?1??
????????```

### 输出

```
779135038```

# 题解

## 作者：Chancylaser (赞：14)

想必题面已经描述的很明白了，那么题意我在此也不再赘述。

## $\mathcal{Preface}$

* 你需要会状压DP，并对状态压缩有着深刻理解。

* 算法时间复杂度我会在下面分析。

* 以下我都将 $n,m$ 分别代替题目中的 $H,W$，并且将 $a_{i,j}\gets   \{-1,0,1,2\}$ 分别表示题目输入的 $s_{i,j}$ 的 $\{?,1,2,3\}$。

## $\mathcal{Solution} $

想必暴力大家都是会的，题目也把暴力的方法讲给我们了。显然是不能通过的暴力我们如何优化呢？

注意数据范围 $n \times m\le 200$，那么对于一组数据，$min(n,m)\le \left \lfloor\sqrt{200} \right \rfloor  = 14$，这启发我们使用状压DP，将每一行的状态压下来。不过前提是列数比较少，所以如果说输入的字符矩阵 $n\times m(n<m)$，我们给他倒一下变成 $m\times n$ 即可。所以，以下都视作 $n\ge m$。

简单来说，我们要选择行数或列数的较小值来进行状态压缩。

那么好，我们使用经典状压DP的思路，设 $f_{i,t}$ 表示目前扫到第 $i$ 行，且当前行的状态为 $t$ 的方案数。从 $f_{i-1,t'}$ 转移即可（即如果 $t$ 和 $t'$ 不矛盾，我们使 $f_{i,t} += f_{i-1,t'}$）。具体的，我们先**预处理**出每一行可以填什么（存到vector里），并遵循题目所给的限制。


```cpp
vector<int> vec[N];
void dfs(int tmp){
	if(tmp>m){
		int nw=0;
		for(int i=1;i<=m;i++) nw=nw*3+b[i];
		vec[nwi].push_back(nw);
		return;
	}
	if(a[nwi][tmp]!=-1 && a[nwi][tmp]!=b[tmp-1]){
		b[tmp]=a[nwi][tmp];
		dfs(tmp+1);
	}
	else if(a[nwi][tmp]==-1){
		if(b[tmp-1]!=0) b[tmp]=0, dfs(tmp+1);
		if(b[tmp-1]!=1) b[tmp]=1, dfs(tmp+1);
		if(b[tmp-1]!=2) b[tmp]=2, dfs(tmp+1);
	}
}
```


而转移的时候，设当前枚举到第 $i$ 行，我们当然需要从上一行转移，故而先枚举上一行的每一个状态，然后在枚举这一行的每一个状态。容易想到一个**剪枝**，因为上一行的第 $j$ 个数（即上一行状态在三进制下的第 $j$ 位）与本行的第 $j$ 个数不能相同，所以可以剪掉。

下面给出代码，$sum$ 数组即存的是上一行每一个位的值，搜完每一个后进行 $f$ 的转移即可。


```cpp
void dfs2(int tmp){
	if(tmp>m){
		int nw=0;
		for(int i=1;i<=m;i++) nw=nw*3+b[i];
		(f[nwi&1][nw]+=f[(nwi&1)^1][nsum])%=MOD;
		return;
	}
	if(b[tmp-1]!=0 && sum[tmp]!=0) b[tmp]=0, dfs2(tmp+1);
	if(b[tmp-1]!=1 && sum[tmp]!=1) b[tmp]=1, dfs2(tmp+1);
	if(b[tmp-1]!=2 && sum[tmp]!=2) b[tmp]=2, dfs2(tmp+1);
}
```

另外，对于初始值，我们可以使 $f_{1,t}=1$，对于统计答案，即 $\sum f_{n,t}$。

---------------

下面我们分析时间复杂度。

* 预处理的vector最多塞多少个？
> 容易发现，我们按照最坏情况，一行全是 $?$，即 $a$ 数组值全为 $-1$。那么情况数即为 $3\times 2^{m-1}=24576$（上面说了 $m$ 最大为 $14$）。

* 计算过程的时间复杂度怎么算？
> 理论上来说，我们需要枚举：当前行，上一行的每一个状态，本行的每一个状态。这么乘起来大概是 $n\times (3\times 2^{m-1})^2$ 的计算量。可事实真的如此吗？  
> 其实，枚举上一行的每一个状态时，确实枚举了全部的状态，但是枚举本行状态的时候，我们因为剪枝了，实际运行的状态远远低于我们的想象，笔者帮大家跑了一下，只有几百的量级。所以时间上完全过得去。
>
> 故而时间复杂度大致可以分析成 $\mathcal O(nk\times 2^m)$，$k$ 为一个几百量级的数。最劣情况下也跑得过去。
## $\mathcal{Code} $

另外，显然我们的第一维可以使用滚动数组优化，不必多言。滚动数组注意用完后及时清空。


```cpp
int n,m;
char s[N][N];
int a[N][N];

int b[N],nwi;

vector<int> vec[N];
void dfs(int tmp){
	if(tmp>m){
		int nw=0;
		for(int i=1;i<=m;i++) nw=nw*3+b[i];
		vec[nwi].push_back(nw);
		return;
	}
	if(a[nwi][tmp]!=-1 && a[nwi][tmp]!=b[tmp-1]){
		b[tmp]=a[nwi][tmp];
		dfs(tmp+1);
	}
	else if(a[nwi][tmp]==-1){
		if(b[tmp-1]!=0) b[tmp]=0, dfs(tmp+1);
		if(b[tmp-1]!=1) b[tmp]=1, dfs(tmp+1);
		if(b[tmp-1]!=2) b[tmp]=2, dfs(tmp+1);
	}
}

int nsum;
int sum[N];
LL f[2][M];
void dfs2(int tmp){
	if(tmp>m){
		int nw=0;
		for(int i=1;i<=m;i++) nw=nw*3+b[i];
		(f[nwi&1][nw]+=f[(nwi&1)^1][nsum])%=MOD;
		return;
	}
	if(b[tmp-1]!=0 && sum[tmp]!=0) b[tmp]=0, dfs2(tmp+1);
	if(b[tmp-1]!=1 && sum[tmp]!=1) b[tmp]=1, dfs2(tmp+1);
	if(b[tmp-1]!=2 && sum[tmp]!=2) b[tmp]=2, dfs2(tmp+1);
}

signed main(){
	scanf("%lld%lld",&n,&m);
	memset(a,-1,sizeof(a));
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++){
			if(s[i][j]=='1') a[i][j]=0;
			else if(s[i][j]=='2') a[i][j]=1;
			else if(s[i][j]=='3') a[i][j]=2;
		}
	}
	
	if(n<m){ // 这个交换大家可以不用管，只要交换的方法是对的就行。 
        for(int i=1;i<=m;i++)
            for(int j=1;j<i;j++)
                swap(a[i][j],a[j][i]);
        swap(n,m);
	}
	
	for(int i=1;i<=n;i++){
		nwi=i; b[0]=-1;
		dfs(1);
	}
	
	for(auto i:vec[1]) f[1][i]=1;
	for(int i=2;i<=n;i++){
		nwi=i;
		for(int j:vec[i-1]){
			nsum=j;
			for(int k=m;k>=1;k--) sum[k]=nsum%3,nsum/=3;
			nsum=j; 
			b[0]=-1;
			dfs2(1);
		}
		memset(f[(i&1)^1],0,sizeof(f[(i&1)^1]));
	}
	
	LL zans=0;
	for(auto i:vec[n]) (zans+=f[n&1][i])%=MOD;
	printf("%lld",zans);
	return 0;
}
```

---

## 作者：__little__Cabbage__ (赞：3)

众所周知，状压 dp 是最简单的 dp。

## Solution

考虑按照从上到下，从左到右的顺序填数，因为 $m \le 14$（假设 $m \le n$），所以可以状压 dp，这时对 $(i,j)$ 有影响的只有 $(i-1,j)$ 和 $(i,j-1)$，所以可以把 dp 数组滚一下，只留最后 $m$ 个数即可。可以用两个 `unordered_map` 表示上次 `dp` 数组和本次 `dp` 数组，状态数最多 $3^2 \times 2^{m-2}$。

转移是容易的，对于每个状态，判下是否合法，然后加法原理即可。

## Code

稍微卡了一点点常，跑了 $\rm 777ms$（所以似乎不卡常也行）。

为了好写，我先处理了第一行，然后后面再正常计算。

```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#include<unordered_map>
//#define int long long
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rpe(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;

const int MAXN=200+5;
const int mod=998244353;
const int pw[19+5]={1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323,4782969,14348907,43046721,129140163,387420489};
int n,m;
char a[MAXN][MAXN],_a[MAXN][MAXN];
unordered_map <int,int> f,nf;

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);

    cin>>n>>m;
    rep(i,1,n) rep(j,1,m) cin>>a[i][j],_a[i][j]=a[i][j];
    if(m>n)
    {
        rep(i,1,m) rep(j,1,n) a[i][j]=_a[j][i];
        swap(n,m);
    }

    bitset <3> t,t2;

    if(a[1][1]=='?') f[0]=f[1]=f[2]=1;
    else f[a[1][1]-'1']=1;

    rep(j,2,m)
    {
        unordered_map<int,int>().swap(nf);

        a[1][j]=='?' ? (t2=7,1) : (t2=0,t2[a[1][j]-'1']=1);

        for(auto [s,v]:f)
            rep(k,0,2) t2[k] && s%3!=k && ((nf[s*3+k]+=v)%=mod,1);

        f=nf;
    }

    rep(i,2,n) rep(j,1,m)
    {
        unordered_map<int,int>().swap(nf);

        a[i][j]=='?' ? (t2=7,1) : (t2=0,t2[a[i][j]-'1']=1);

        for(auto [s,v]:f)
        {
            t=7;
            i-1>0 && (t[s/pw[m-1]]=0,1);
            j-1>0 && (t[s%3]=0,1);

            rep(k,0,2) (t[k]&t2[k]) && ((nf[s%pw[m-1]*3+k]+=v)%=mod,1);
        }

        f=nf;
    }

    int ans=0;
    for(auto [s,v]:f) (ans+=v)%=mod;
    cout<<ans%mod;

    return 0;
}
```

---

## 作者：Chenyanxi0829 (赞：3)

按照 $a_{1,1},\dots,a_{1,w},a_{2,1},\dots,a_{2,w},\dots,a_{h,w}$ 的顺序来做轮廓线 dp。

设 $dp_{i,j,a_{i,1},\dots,a_{i,j},a_{i-1,j+1},\dots,a_{i-1,w}}$ 表示到了 $(i,j)$ 且 $(i,1),\dots,(i,j),(i-1,j+1),\dots,(i-1,w)$ 的颜色分别为 $a_{i,1},\dots,a_{i,j},a_{i-1,j+1},\dots,a_{i-1,w}$ 的合法方案数，转移时直接枚举 $(i,j)$ 这个格子是什么颜色（不是问号的格子只考虑那一种颜色即可），但为了保证合法需要满足与 $(i,j-1),(i-1,j)$ 的颜色不同。

但是这个做法有个问题是当 $w$ 很大时状态数就爆了，所以我们考虑如果 $h<w$ 就交换 $h,w$ 并把 $S_{i,j}$ 变为原来的 $S_{j,i}$，而题目又保证了 $h\times w\le200$，那么 $w$ 最大就只有 $\lfloor\sqrt{200}\rfloor=14$，并且还需要满足相邻格子不相同，这样状态数就不会炸了。

## 代码
实现时最好是把 $a_{i,1},\dots,a_{i,j},a_{i-1,j+1},\dots,a_{i-1,w}$ 状压成一个数，为了方便位移，在代码中我使用 4 进制，由于交换后 $w\le14$，所以只需要用 `int` 来存。发现有很多非法状态，所以可以用 `unordered_map` 来储存 dp 值。
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kMaxN = 210, mod = 998244353;

int h, w, z[kMaxN], ans;
unordered_map<int, int> dp[kMaxN][kMaxN];
char a[kMaxN][kMaxN], b[kMaxN][kMaxN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> a[i][j];
    }
  }
  if (h < w) {
    swap(h, w);
    for (int i = 1; i <= h; i++) {
      for (int j = 1; j <= w; j++) {
        b[i][j] = a[j][i];
      }
    }
    for (int i = 1; i <= h; i++) {
      for (int j = 1; j <= w; j++) {
        a[i][j] = b[i][j];
      }
    }
  }
  dp[0][w][0] = 1;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      for (auto k : dp[j > 1 ? i : i - 1][j > 1 ? j - 1 : w]) {
        j > 1 && (z[j - 1] = ((k.first >> ((j - 2) << 1)) & 3)), z[j] = ((k.first >> ((j - 1) << 1)) & 3);
        for (int l = 1; l <= 3; l++) {
          if ((a[i][j] == '?' || a[i][j] - '0' == l) && z[j - 1] != l && z[j] != l) {
            dp[i][j][k.first ^ (z[j] << ((j - 1) << 1)) ^ (l << ((j - 1) << 1))] = (dp[i][j][k.first ^ (z[j] << ((j - 1) << 1)) ^ (l << ((j - 1) << 1))] + k.second) % mod;
          }
        }
      }
    }
  }
  for (auto i : dp[h][w]) {
    ans = (ans + i.second) % mod;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：hellolin (赞：3)

如果你从上到下、从左到右地填数，你会发现只有当前待填的数的左边和上边一排至多 $m$ 个数会影响后续转移。所以状压这 $m$ 个数即可。

由于相邻的数必须不同，状态数最多只有 $9\times 2^{m-2}$（至多两个随便填，剩下的两种选择）。暴力 $O(nm^2)$ 转移即可。


``` cpp
namespace hellolin {
static constexpr i64 Mod = 998244353;
void main() {
  int n, m;
  bool flag = false;
  std::cin >> n >> m;
  if (m > n) {
    std::swap(n, m);
    flag = true;
  }

  std::vector<std::string> a(n, std::string(m, 0));
  if (!flag) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cin >> a[i][j];
      }
    }
  } else {
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        std::cin >> a[j][i];
      }
    }
  }

  std::unordered_map<std::string, i64> f;
  f["0"] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::unordered_map<std::string, i64> g;
      for (const auto &[state, x] : f) {
        for (char num = '1'; num < '4'; ++num) {
          if (a[i][j] != num and a[i][j] != '?') continue;
          if (state == "0") {
            (g[std::string{} + num] += x) %= Mod;
            continue;
          }
          if (i != 0 and num == state.front()) continue;
          if (j != 0 and num == state.back()) continue;

          auto nxt_state = state + num;
          if ((int) nxt_state.size() > m) nxt_state = nxt_state.substr(1);
          (g[nxt_state] += x) %= Mod;
        }
      }
      f = std::move(g);
    }
  }

  i64 ans = 0;
  for (const auto &[_, x] : f) {
    (ans += x) %= Mod;
  }
  std::cout << ans << '\n';
}
} // namespace hellolin
```

---

## 作者：chriskx (赞：2)

# 状压dp
观察题意，容易发现暴力做法：对于每个为 $?$ 的格子，枚举填入 $1,2,3$ 的情况。时间复杂度为 $O(3^{h \times w})$。

考虑优化，发现我们填入第 $i$ 行时，只受第 $i-1$ 行影响，与更前面的行无关。即只有**相邻行**对当前行有影响。

**故可以进行记忆化。**

可定义 $dp$ 状态为 $dp_{i,j,mask}$，其中 $mask$ 为$ S_{i-1,j},S_{i-1,j+1},\cdots,S_{i-1,w},S_{i,1},\cdots,S_{i,j-1}$ 的三进制压缩，时间复杂度为 $O(h \times w \times 3^h)$。

题目只给定了 $h \times w≤ 200$，若 $h=200$，$w=1$ 显然时间超限。观察到时间复杂度与 $h$ 强相关，与 $w$ 弱相关，故 $h>w$ 时交换 $h$ 和 $w$ 即可。则 $h≤\sqrt{200}\approx 14$。

$200 \times 3^{14}\approx 10^9$，看上去时间复杂度会超。但因为 $mask$ 压缩的是连续的一行，而相邻格子不能相同，所以远没有这么多。

实际上，合法的 $mask$ 非常稀疏，只有 $2^{14}\approx 20,000$ 种，所以总状态数在 $10^7$ 以下，记忆化时用 unordered_map 离散化即可通过。

献上丑陋的代码：
 
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 998244353;
int h, w;
int a[205][16];
unordered_map<int, int> cache[205];

int decode(int x, int y)
{
    int ret = 0;
    for (int j = y; j <= w; j++)
    {
        ret *= 3;
        ret += a[x - 1][j];
    }
    for (int j = 1; j <= y - 1; j++)
    {
        ret *= 3;
        ret += a[x][j];
    }
    return ret;
}

int dfs(int i, int j)
{
    if (i > h)
    {
        return 1;
    }
    if (j > w)
    {
        return dfs(i + 1, 1);
    }
    if (a[i][j] != 0)
    {
        if (a[i][j] != a[i - 1][j] and a[i][j] != a[i][j - 1])
        {
            return dfs(i, j + 1);
        }
        else
        {
            return 0;
        }
    }
    int cod = decode(i, j);
    if (cache[(i - 1) * w + j].find(cod) != cache[(i - 1) * w + j].end())
    {
        return cache[(i - 1) * w + j][cod];
    }
    int ret = 0;
    if (1 != a[i - 1][j] and 1 != a[i][j - 1])
    {
        a[i][j] = 1;
        ret += dfs(i, j + 1);
        ret %= mod;
        a[i][j] = 0;
    }
    if (2 != a[i - 1][j] and 2 != a[i][j - 1])
    {
        a[i][j] = 2;
        ret += dfs(i, j + 1);
        ret %= mod;
        a[i][j] = 0;
    }
    if (3 != a[i - 1][j] and 3 != a[i][j - 1])
    {
        a[i][j] = 3;
        ret += dfs(i, j + 1);
        ret %= mod;
        a[i][j] = 0;
    }
    cache[(i - 1) * w + j][cod] = ret;
    return ret;
}

signed main()
{
    cin >> h >> w;
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            char c;
            int num;
            cin >> c;
            if (c == '?')
            {
                num = 0;
            }
            else
            {
                num = c - '0';
            }
            if (h >= w)
            {
                a[i][j] = num;
            }
            else
            {
                a[j][i] = num;
            }
        }
    }
    if (h < w)
    {
        swap(h, w);
    }
    cout << dfs(1, 1);
    return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：2)

这是一篇轮廓线 DP 好题。

在此题中，我们不防假设 $W \le H$。由于 $H\times W\le 200$，容易知道 $W \le \sqrt{200}$，也就是说 $W \le 14$。

---

我们考虑设 $dp_{i,j,\text{mask}}$ 表示已经填满了第 $i$ 行的所有格子，下一行已经填了 $j$ 个格子，并且最下面一整行的状态为 $\text{mask}$，满足这些要求的方案数。  
则根据定义，$dp_{H,0}$ 内所有的值加起来即为答案。  
我们可以通过枚举第一行的所有方式计算出 $dp_{1,0}$ 下面的所有值。因为假设过 $W \le 14$，即使用最朴素的 $O(W3^W)$ 做法也不会爆炸。

接下来考虑如何转移。  
对于 $dp_{i,j}$ 且 $j\ne W-1$，我们自然是从 $dp_{i,j}$ 转移到 $dp_{i,j+1}$，字面意思上来说是把第 $i+1$ 行的第 $j+1$ 个空格填一个数。我们对于 $dp_{i,j}$ 中的每一个状态进行考虑。  
假设当前的状态是 $\text{mask}$。那么，我们需要将该状态的从左往右数第 $j+1$ 位进行修改。为了方便起见，我们使用具体样例进行描述。同时为了方便计算，我们把题目中的 $1,2,3$ 替换成 $0,1,2$。

假设 $W=3$，目前我们已经进行到 $dp_{2,1}$，下一个该填第 $3$ 行第 $2$ 列的元素。如下是一种可能的状态。

$$

\begin{matrix}
 \blue{1} & \blue{2} & \blue{0} \\
 \blue{2} & \green{0} & \green{2} \\
 \green{1} & \red{?} & ? \\
 &\vdots&
\end{matrix}
$$

其中，蓝色的元素将永远不会对现在和未来的红色元素（目前正在填写的元素）进行干扰，因此没有必要。

绿色的元素从左到右看成三进制为 $(102)_3=11$，也就是说绿色部分刚好在这些位置是这些值的方案数为 $dp_{2,1,(102)_3}$。也即我们通过三进制状压把一行压缩进一个维度。由于绿色的部分是填过的所有元素

接下来，我们可以类似于二进制中的移位，预处理出 $3$ 的次幂，用简单运算将该状态目前有影响的位计算出来。由于我们填写的是从左往右第 $2$ 列的元素，所以我们把第 $1$ 列和第 $2$ 列的位提取出来，发现一个是 $1$，一个是 $0$。也就是说，现在红色部分只能填 $2$。

故，我们可以从 $dp_{2,1,(102)_3}$ 转移到 $dp_{2,2,(122)_3}$。注意到 $(122)_3$ 看起来像是有相邻的相等元素，但是实际上它们不在同一行，所以不是相邻的。

还有一些细节问题，具体可以看代码注释。

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 205, mod = 998244353;

char a[N][N], b[N][N];
int mi3[N];
unordered_map<int, int> dp[N][N];

signed main() {
  mi3[0] = 1;
  for(int i = 1; i < N; i++) {
    mi3[i] = mi3[i - 1] * 3;
  }
  int h, w;
  cin >> h >> w;
  for(int i = 1; i <= h; i++) {
    for(int j = 1; j <= w; j++) {
      cin >> a[i][j];
    }
  }
  if(h < w) { // 为了使 w < h，将数组横纵倒转过来。
    swap(h, w);
    for(int i = 1; i <= h; i++) {
      for(int j = 1; j <= w; j++) {
        b[i][j] = a[j][i];
      }
    }
    for(int i = 1; i <= h; i++) {
      for(int j = 1; j <= w; j++) {
        a[i][j] = b[i][j];
      }
    }
  }
  int maxv = 1;
  for(int i = 1; i <= w; i++) {
    maxv *= 3;
  }
  for(int i = 0; i < maxv; i++) {
    int I = i;
    bool ok = 1;
    for(int j = w; j; j--) {
      if(a[1][j] != '?' && I % 3 + '1' != a[1][j] || j > 1 && I % 3 == (I / 3) % 3) {
        ok = 0;
        break;
      }
      I /= 3;
    }
    if(!ok) {
      continue;
    }
    dp[1][0][i] = 1;
  }
  for(int i = 1; i <= h; i++) {
    for(int j = 0; j < w; j++) {
      for(auto k : dp[i][j]) {
        auto x = k.first, y = k.second;
        int p = k.first / mi3[w - j - 1] % 3, q;
        if(j) {
          q = k.first / mi3[w - j] % 3;
        } else {
          q = -1; // 如果 j = 0，则下一个填的是第 1 列，而其左边没有元素。
        }
        for(int l = 0; l <= 2; l++) {
          if(l != p && l != q && (a[i + 1][j + 1] == '?' || a[i + 1][j + 1] == l + '1')) {
            int newfirst = k.first - (k.first / mi3[w - j - 1] % 3) * mi3[w - j - 1] + l * mi3[w - j - 1];
            if(j == w - 1) {
              (dp[i + 1][0][newfirst] += k.second) %= mod; // 第 i + 1 行已经填完了，因此可以转移到下一行了
            } else {
              (dp[i][j + 1][newfirst] += k.second) %= mod;
            }
          }
        }
      }
    }
  }
  int ans = 0;
  for(auto x : dp[h][0]) {
    (ans += x.second) %= mod;
  }
  cout << ans;
}
```

关于需要令 $W<H$ 的原因：这份代码的时间复杂度为 $O(W3^W+HW2^W)$。（前面部分可以用搜索等优化到 $W2^W$，但没必要）

注意到后面的部分是 $2^W$ 种状态而非 $3^W$ 种，是因为相邻元素不能相同，所以大部分元素实际上只有两种可能的取值。在换行处会有 $3$ 种，但是属于小范围事件。

因为状态压缩的时候 $W$ 是作为指数的，所以要让 $W$ 成为更小的那个值。

最后补充：实际上本题可以直接使用二进制压缩，但是由于换行处的处理十分麻烦，并且边界条件难以处理，所以可以使用 `unordered_map<int, int> dp[N][N]` 的方式代替 `int dp[N][N][sth]` 节省大量时间空间复杂度，把枚举状态的时间复杂度降到理论最低，排除冗余。

此致。纪念我在 21:42:50 通过了这个题。

---

## 作者：ran_qwq (赞：2)

首先你得明白 $H\times W\le200$ 是什么意思。不妨当 $H<W$ 就交换 $H,W$，那么 $W\le\sqrt{200}\approx14$。

考虑状压 dp，比较蠢的实现是按行 dp，$dp_{i,s}$ 表示到第 $i$ 行，当前行状态为 $s$ 的方案数。转移是平凡的，枚举上一列状态 $t$。

很遗憾，复杂度是 $O(H6^W)$ 的。有效状态只有 $O(2^W)$ 个，你可以优化到 $O(H4^W)$，但仍无法通过。

相邻阶段之间的变化太大了，考虑增加阶段个数以减少阶段之间的变化。说人话就是不按行 dp 而是按格子 dp，记录最后填的 $W$ 个格子（也就是每列填的最后一个格子）。$dp_{i,j,s}$ 表示填到第 $i$ 行第 $j$ 列，当前状态为 $s$ 方案数。新填一个数就把它上面的数给推掉。

复杂度 $O(HW3^W)$，取模太多被卡常了。考虑优化，有效状态只有 $O(2^W)$ 个。不同的是，这里第 $j$ 列与第 $j+1$ 列填的数可以相同。一种实现是对当前行的状态和上一行的状态分开考虑，对每个状态（没被填看作 `1`）预处理它前 $i$ 位是否合法。

因为用到 fill，复杂度不变仍是 $O(HW3^W)$ 的，但瓶颈处常数极小，时间 800ms。

```cpp
int n,m,rs,pw[M],dp[K],lst[K],fg[K][M]; vi v[K]; char _ch[N][N],ch[N][M];
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) scanf("%s",_ch[i]+1);
	if(n>m) for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ch[i][j]=_ch[i][j];
	else {swap(n,m); for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ch[i][j]=_ch[j][i];}
	pw[0]=1; for(int i=1;i<=m;i++) pw[i]=pw[i-1]*3;
	auto gt=[&](int s,int y) {return s/pw[y]%3;};
	for(int s=0,f;s<pw[m];s++) {
		fg[s][0]=1;
		for(int i=1;i<=m;i++) fg[s][i]=fg[s][i-1]&(i==1||gt(s,i-1)!=gt(s,i-2));
		if(fg[s][m]) {
			f=1; for(int i=1;i<=m;i++) f&=ch[1][i]=='?'||ch[1][i]-'1'==gt(s,i-1);
			lst[s]=f;
		}
	}
	for(int i=1;i<=m;i++) for(int s=0;s<pw[m];s++) if(fg[s%pw[i]][i]&&fg[s/pw[i]][m-i]) v[i].pb(s);
	for(int i=2;i<=n;i++) for(int j=1;j<=m;j++) {
		fill(dp,dp+pw[m],0);
		for(int s:v[j]) {
			int c=gt(s,j-1);
			if(j==1||c!=gt(s,j-2))
				if(!c&&(ch[i][j]=='?'||ch[i][j]=='1')) cadd(dp[s],vadd(lst[s+pw[j-1]],lst[s+2*pw[j-1]]));
				else if(c==1&&(ch[i][j]=='?'||ch[i][j]=='2')) cadd(dp[s],vadd(lst[s-pw[j-1]],lst[s+pw[j-1]]));
				else if(c==2&&(ch[i][j]=='?'||ch[i][j]=='3')) cadd(dp[s],vadd(lst[s-2*pw[j-1]],lst[s-pw[j-1]]));
		}
		fill(lst,lst+pw[m],0); for(int s:v[j]) lst[s]=dp[s];
	}
	for(int s:v[m]) cadd(rs,lst[s]); wr(rs,"\n");
}
```

---

## 作者：封禁用户 (赞：1)

首先，这是计数题，而且很明显是个状态压缩。

$H\times W\le 200$，看起来很不可做，但是继续想想，发现 $\min(H,W)\le 14$。那么我们可以把小的那个长度转到第二维。考虑 $H=W=14$ 的最极端状态。

其次，我们的状态数量好像是 $3^{14}$，看起来也很不可做。

但是继续想想：题目中的限制条件就是相邻两个格子颜色不得相同，那么状态数量实际上是 $3\times 2^{13}$。你不相信这个状态数？首先选择一行第一个格子，共 $3$ 个颜色，其次依次往后选择格子，每次有 $2$ 个可选颜色。这样状态数量就可以计算出来是这么多了。

最后——我们状态数量虽然不多，但是从一行的状态到下一行的状态转移数量好像是 $9\times 4^{13}$ 啊，这更不可做了。

不过，相邻两行之间对应的位置也不一样。我们计算一下两行之间相邻格子不同颜色的方案数——任意选择两行的第一个格子（共 $6$ 种方案），然后依次地同时选择两行的第 $2$ 到 $14$ 个格子（每次有 $3$ 种方案）。这样，转移数是 $6\times 3^{13}=2\times 3^{14}$ 个。

我们只要使用两次 $\text{dfs}$，预处理出所有状态数，并使用 $\text{vector}$ 存储两个状态间的所有转移。在扫到每一行的时候，查看这个状态是否匹配了该行所有已给的格子颜色，接着转移即可。时间复杂度 $O(\max(H,W)3^{\min(H,W)}+HW2^{\min(H,W)})$，稳稳地过。

实现细节以及套路：

- $\text{dfs}$ 前开一个大小为 $3\times 2^{13}$ 的用于**离散化**的数组，将数值值域大小为 $3^{14}$ 的状态存储在对应编号里，这样容易在状态压缩 $\text{dp}$ 时找到 $14$ 个格子的颜色用于检验。

- 不要在 $\text{dp}$ 过程中检查两个状态是否存在相同颜色的位置。如果你不想死，请预处理所有转移。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int h,w,rawgrid[205][205],grid[205][15],lsh[4782969],Nlsh[25005],mi3[15],dp[205][50005],pt1,CnT,ans;
const int modp=998244353;vector<int>canbe[25005];bool enable[205][25005];

void dfs(int now,int cur,int lst){
	if(now==w){
		pt1++;lsh[cur]=pt1;Nlsh[pt1]=cur;return;
	}
	for(int o=0;o<3;o++){
		if(o==lst)continue;
		dfs(now+1,cur+o*mi3[now],o);
	}
}

void dfs2(int now,int ocur,int cur,int lst1,int lst2){
	if(now==w){
		canbe[lsh[ocur]].push_back(lsh[cur]);return;
	}
	for(int o=0;o<3;o++){
		if(o==lst1)continue;
		for(int oo=0;oo<3;oo++){
			if(oo==lst2)continue;
			if(o==oo)continue;
			dfs2(now+1,ocur+o*mi3[now],cur+oo*mi3[now],o,oo);
		}
	}
}

bool bean(int xx,int rw){
	for(int i=1;i<=w;i++){
		if(grid[rw][i]!=0&&xx%3!=grid[rw][i]-1)return 0;
		xx/=3;
	}
	return 1;
}

int main(){
	cin>>h>>w;mi3[0]=1;
	for(int i=1;i<=14;i++)mi3[i]=mi3[i-1]*3;
	for(int i=1;i<=h;i++){
		string s;cin>>s;
		for(int j=1;j<=w;j++){
			if(s[j-1]!='?')rawgrid[i][j]=s[j-1]-'0';
		}
	}
	if(h<w){
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++){
				grid[j][i]=rawgrid[i][j];
			}
		}
		swap(h,w);
	}
	else{
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++){
				grid[i][j]=rawgrid[i][j];
			}
		}
	}
	dfs(0,0,-1);dfs2(0,0,0,-1,-1);//cout<<pt1<<' '<<CnT;
	for(int i=1;i<=h;i++){
		for(int zt=1;zt<=pt1;zt++){
			enable[i][zt]=bean(Nlsh[zt],i);
		}
	}
	for(int zt=1;zt<=pt1;zt++){
		if(enable[1][zt])dp[1][zt]=1;
	}
	for(int i=1;i<h;i++){
		for(int zt=1;zt<=pt1;zt++){
			if(!enable[i][zt])continue;
			for(auto zt2:canbe[zt]){
				if(enable[i+1][zt2])dp[i+1][zt2]=(dp[i+1][zt2]+dp[i][zt])%modp;
			}
		}
	}
	for(int i=1;i<=pt1;i++){
		ans=(ans+dp[h][i])%modp;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：louisliang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc379_g)

前情提要：C 题喜提 $6$ 发罚时，这题没调完了。

发现 $\min(h,w) \leq 14$，可以状压。

很经典的套路，发现枚举点 $(i,j)$ 时，只需记下将所有同一行中在 $(i,j)$ 左边的格子和上一行中在 $(i-1,j)$ 右边的格子，也就是下图的黄色格子。

![](https://cdn.luogu.com.cn/upload/image_hosting/r9q9538c.png)

可以发现有效状态为 $2^n$ 的，但用 $3^n$ 也能过，而且更好写，下面是一些卡常技巧：

- 开 ```-O3```。

- 取模优化。

- 把常数 ```const``` 掉。

- 可以发现枚举时有一些位是固定为一些数的，只枚举其他位。

具体实现看代码。时间复杂度 $O(hw3^{\min(h,w)})$。

Code:

```
#pragma GCC optimize(3)
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cassert>
#include<vector>
#include<cmath>
#include<cstring>
#include<set>
#include<climits>
#include<queue>
#include<stack>
#include<bitset>
#include<map>
#include<algorithm>
using namespace std;
const int N = 205, MOD = 998244353, pw[] = {1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323,4782969};
int h, w, la, f[2][4782969], mp[N][N];
inline int gt(int mask, int k){
	return (mask % pw[k]) / pw[k - 1];
}
inline void upd(int &x, int y){
	((x += y) >= MOD)? (x -= MOD) : x; 
}
inline void dp(int pos, int x){
	int t = x * pw[pos - 1];
	if(pos == 1){
		int a = (x + 1) % 3, b = (a + 1) % 3;
		for(int mask = 0; mask < pw[h]; mask += 3){
			upd(f[la ^ 1][mask + t], f[la][mask + a]);
			upd(f[la ^ 1][mask + t], f[la][mask + b]);
		}
	}
	else{
		int a = (x + 1) % 3 * pw[pos - 2], b = (x + 2) % 3 * pw[pos - 2];
		int aa = 3 * a + a, ab = 3 * a + b, ba = 3 * b + a, bb = 3 * b + b;
		for(int x = 0; x < pw[h - pos]; x++){
			for(int y = 0, z = x * pw[pos]; y < pw[pos - 2]; y++, z++){
				upd(f[la ^ 1][z + t + a], f[la][z + aa]);
				upd(f[la ^ 1][z + t + a], f[la][z + ba]);
				upd(f[la ^ 1][z + t + b], f[la][z + ab]);
				upd(f[la ^ 1][z + t + b], f[la][z + bb]);
			}
		}
	}
}
main(){
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> h >> w;
	for(int i = 1; i <= h; i++){
		for(int j = 1; j <= w; j++){
			char ch;
			cin >> ch;
			mp[i][j] = ((ch == '?')? 0 : (ch - '0'));
		}
	}
	if(h > w){
		swap(h, w);
		for(int i = 1; i <= w; i++)
			for(int j = i + 1; j <= w; j++)
				swap(mp[i][j], mp[j][i]);
	}
	for(int i = 0; i < pw[h]; i++){
		f[la][i] = 1;
		for(int j = 1; j <= h; j++){
			if((mp[j][1] && mp[j][1] != gt(i, j) + 1) || (j > 1 && gt(i, j) == gt(i, j - 1))){
				f[la][i] = 0;
				break;
			}
		}
	}
	for(int i = 2; i <= w; i++){
		for(int j = 1; j <= h; j++){
			memset(f[la ^ 1], 0, sizeof(f[la ^ 1]));
			if(mp[j][i])
				dp(j, mp[j][i] - 1);
			else{
				dp(j, 0);
				dp(j, 1);
				dp(j, 2);
			}
			la ^= 1;
		}
	}
	int sum = 0;
	for(int i = 0; i < pw[h]; i++)
		upd(sum, f[la][i]);
	cout << sum << "\n";
}
```

---

## 作者：Sky_Maths (赞：1)

## 暴力做法/插头 DP
可过。

考虑 $H\times W\le 200$，所以 $\min(H, W)\le 14$，那么可以猜测可行状态数非常少（第一个随便，后面的只有两种可能，$3\cdot 2^{13} = 24576$），可以先把可行状态跑出来，不妨假设 $W\le H$。、

注意 s 在交换的时候是 `s[j][i] = _s[i][j];` 啊啊啊啊啊！！！

再次猜测可行转移也不多，跑一下发现 $\le9565938\approx 1\cdot 10^7$，而此时 $h\le 14$，可以跑完。

注意：可行状态和可行转移都可以提前跑出来。

总结：发现可行状态/转移比较少于是直接暴力 DP 转移。

[submission](https://atcoder.jp/contests/abc379/submissions/59603955)

Update：不是，怎么正解是轮廓线 DP 啊。

## 轮廓线 DP 做法
口胡。

考虑先同样转化为 $H\ge W$，然后设 $f_{i, j, s}$ 为前 $i - 1$ 行的全部和第 $i$ 行的前 $j - 1$ 个确定，当前轮廓上的状态为 $s$ 的方案。

$s$ 中只用记录 $W$ 个值(?)，而最大可行状态数略多于 $3\cdot 2^{13}$，**可能**可以直接枚举下一个是哪个，对于 $\not= 0$ 的 $f_{i, j, s}$ 暴力转移。

---

## 作者：Union_Find (赞：0)

看到数据范围 $H \times W \le 200$，就要考虑短边，即 $\min(H,W) \le 14$。所以就是状压 dp 了。一般的状态比较难，但是我们考虑将所有格子排成一排，然后定义 $f_{i,s}$ 表示从 $i - W + 1$ 到 $i$ 的格子状态是 $s$ 的方案数，这里我们认为 $W$ 是短边，如果不是就进行翻转。

那么我们考虑主动转移，就是如何从 $i$ 转移到 $i + 1$。如果 $a_{i + 1}$ 已经有数字了，就直接转移，否则就考虑 $i + 1$ 填什么数字，单次转移是 $O(1)$ 的，一共有 $O(HW3^{W})$ 的状态，总时间复杂度是 $O(HW3^{W})$。

这样其实会 T，但是因为相邻两位不能相同，所以状态数很少，可以用 map 充当 dp 数组，就可以通过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 205
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
const ll P = 998244353;
ll n = rd(), m = rd(), a[N * N], p[N], ans;
char st[N][N], t[N][N];
unordered_map <ll, ll> f, g;
il ll cal(ll s, ll x){return (s / p[x]) % 3;}
il bool check(ll s, ll x){
	for (int i = 1; i < m; i++) if ((x - m + i + 1) % m != 1 && cal(s, i) == cal(s, i - 1)) return 0;
	for (int i = x - m + 1; i <= x; i++) if (a[i] != -1 && cal(s, i - x + m - 1) != a[i]) return 0;
	return 1;
}il void add(ll &x, ll y){x = (x + y >= P ? x + y - P : x + y);}
int main(){
	p[0] = 1;
	for (int i = 1; i <= 20; i++)
		p[i] = (p[i - 1] + p[i - 1] + p[i - 1]), p[i] = (p[i] >= P + P ? p[i] - P - P : (p[i] >= P ? p[i] - P : p[i]));
	for (int i = 1; i <= n; i++) scanf ("%s", st[i] + 1);
	if (n < m){
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) t[j][i] = st[i][j];
		swap(n, m);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) st[i][j] = t[i][j];
	}for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[(i - 1) * m + j] = st[i][j] == '?' ? -1 : st[i][j] - '0' - 1; 
	for (int s = 0; s < p[m]; s++) if (check(s, m)) g[s] = 1;
	for (int i = m; i < n * m; i++){
		for (auto ttt : g){
			ll s = ttt.first;
			if (!check(s, i)) continue;
			if (i % m){
				ll a1 = cal(s, 0), a2 = cal(s, m - 1);
				if (a1 != 0 && a2 != 0 && (a[i + 1] == 0 || a[i + 1] == -1)) add(f[s / 3 + 0 * p[m - 1]], g[s]);
				if (a1 != 1 && a2 != 1 && (a[i + 1] == 1 || a[i + 1] == -1)) add(f[s / 3 + 1 * p[m - 1]], g[s]);
				if (a1 != 2 && a2 != 2 && (a[i + 1] == 2 || a[i + 1] == -1)) add(f[s / 3 + 2 * p[m - 1]], g[s]);
			}else{
				ll a1 = cal(s, 0);
				if (a1 != 0 && (a[i + 1] == 0 || a[i + 1] == -1)) add(f[s / 3 + 0 * p[m - 1]], g[s]);
				if (a1 != 1 && (a[i + 1] == 1 || a[i + 1] == -1)) add(f[s / 3 + 1 * p[m - 1]], g[s]);
				if (a1 != 2 && (a[i + 1] == 2 || a[i + 1] == -1)) add(f[s / 3 + 2 * p[m - 1]], g[s]);
			}
		}g = f;f.clear();
	}for (int s = 0; s < p[m]; s++) if (check(s, n * m)) add(ans, g[s]);
	printf ("%lld\n", ans);
	return 0;
}

```

---

## 作者：Hide_In_The_Shadow (赞：0)

题意：对于一个 $H\times W$ 二维平面，每个点要么有初始值，要么 $1,2,3$ 任取，每两个上下左右相邻的点不可以取一样的，求方案数。

据说是轮廓线 $DP$？蒟蒻不是很懂，当状压 $DP$ 做了。

从上往下，从左往右填数，发现只有上左两个值会对当前填的数造成影响。我们定义 $dp[i][j][k]$ 表示目前位于第 $i$ 行第 $j$ 列，序列 $s_{i,1},……,s_{i,j},s_{i-1,j+1},……,s_{i-1,w}$ 表示为四进制数后转化为十进制的值为 $k$ 的方案数，即用 $k$ 进行状态压缩，由于 $H\times W\leq200$，所以当 $W$ 取两者中较小值时，$W\leq \sqrt {200}$ 即 $W\leq14$，所以总状态数 $\leq H\times W\times3\times 2^{13}=4,915,200$，实际上远远达不到这个值，因为非法状态数太多了。

具体的，在转移时，我们遍历前一位的所有合法序列并枚举当前位置的可选数字进行暴力转移。时间复杂度为 $O(HW2^W)$，同理，由于非法状态太多，实际远远达不到该上界。

Code:
```c++
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
template<typename T>void read(T &x){
    x=0;
    char c=getchar();
    T ret=0;
    while(!isdigit(c))ret|=!(c^'-'),c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(ret)x=(~x)+1;
}
template<typename T,typename ...Args>
void read(T &x,Args &...xs){
    read(x);read(xs...);
}
template<typename T>void print(T x){
    if(x<0)putchar('-'),x=(~x)+1;
    if(x>9)print(x/10);
    putchar((x-x/10*10)^48);
}
template<typename T>void wr1(T x){
    print(x);putchar(' ');
}
template<typename T>void wr2(T x){
    print(x);putchar('\n');
}
const int N=2e2+5;
const ll P=998244353;
int h,w;
char s[N][N];
unordered_map<int,ll>dp[N][N];//使用umap减少枚举次数，优化时空复杂度
ll ans;
int main(){
    fio;
    cin>>h>>w;
    if(h>w){
        for(int i=1;i<=h;++i){
            for(int j=1;j<=w;++j){
                cin>>s[i][j];
            }
        }
    }
    else{
        for(int i=1;i<=h;++i){
            for(int j=1;j<=w;++j){
                cin>>s[j][i];
            }
        }
        swap(h,w);
    }
    dp[0][w][0]=1;
    for(int i=1;i<=h;++i){
        for(int j=1;j<=w;++j){
            int prei=i,prej=j-1;
            if(j==1)prei--,prej=w;//行首从上一行末尾转移
            for(auto [state,x]:dp[prei][prej]){
                int up=(state>>2*(w-j))&3,l=(state>>2*(w-j+1))&3;//上左数值
                for(int now=1;now<=3;++now){
                    if(s[i][j]!=now+'0'&&s[i][j]!='?')continue;
                    if(now!=up&&now!=l){
                        int nex=state^(up<<2*(w-j))^(now<<2*(w-j));
                        (dp[i][j][nex]+=x)%=P;
                    }
                }
            }
        }
    }
    for(auto i:dp[h][w]){
        (ans+=i.second)%=P;
    }
    cout<<ans;
    return 0;
}
```

---

