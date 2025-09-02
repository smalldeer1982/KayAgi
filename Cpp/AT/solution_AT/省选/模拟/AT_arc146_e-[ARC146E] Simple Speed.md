# [ARC146E] Simple Speed

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc146/tasks/arc146_e

長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。

$ 1 $ 以上 $ N $ 以下の整数からなる整数列 $ B $ のうち、以下の条件を全て満たすものの個数を $ 998244353 $ で割ったあまりを出力してください。

- $ 1\ \le\ i\ \le\ N $ を満たす整数 $ i $ に対し、$ B $ の中に $ i $ はちょうど $ A_i $ 個存在する。
- $ 1\ \le\ i\ \le\ |B|-1 $ を満たす整数 $ i $ に対し、$ |B_i\ -\ B_{i+1}|=1 $ が成り立つ。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 2\ \times\ 10^5 $
- 入力はすべて整数である。

### Sample Explanation 1

$ B $ としてあり得るものは、以下の $ 6 $ 通りがあります。 - $ (1,2,1,2,3,2) $ - $ (1,2,3,2,1,2) $ - $ (2,1,2,1,2,3) $ - $ (2,1,2,3,2,1) $ - $ (2,3,2,1,2,1) $ - $ (3,2,1,2,1,2) $ よって、解は $ 6 $ です。

### Sample Explanation 2

条件を満たす $ B $ が存在しないこともあります。

## 样例 #1

### 输入

```
3
2 3 1```

### 输出

```
6```

## 样例 #2

### 输入

```
1
200000```

### 输出

```
0```

## 样例 #3

### 输入

```
6
12100 31602 41387 41498 31863 12250```

### 输出

```
750337372```

# 题解

## 作者：Phartial (赞：19)

神仙题。

由于 $\sum A_i$ 特别大，所以从序列长度角度 dp 是会寄的。于是考虑从值域角度 dp。

设 $f_{i,j}$ 表示现在填完了 $[1,i]$ 的所有数，一共产生了 $j$ 段的方案数。注意此状态设计只在乎产生了多少段，不在乎每段的具体位置。

显然每一段的左端和右端必须是 $i$，并且必须要接一个 $i+1$。

但是你会发现这样子做不了，原因是最左端和最右端不一定要接一个 $i+1$。所以再加一维 $k=0/1/2$，表示左端和右端不能加数的位置个数。

考虑如何转移：

对于 `... i i+1 i ...` 这种情况，中间的 `i+1` 相当于把左右两段连了起来。

而对于 `... i i+1 i+2 i+1 i ...` 这种情况，左边的 `i+1` 可以看作把左右两段连了起来，而右边的 `i+1` 可以看成新加了一段，这样子是可以的。

由于我们不在乎位置关系，所以我们可以在相邻两段之间强制塞一个 $i+1$，而最左端和最右端可能也要塞一个数。于是不妨设最左端和最右端都不塞，那么方案数相当于把剩下 $A_{i+1}-(j-1)$ 个数塞到 $j-1$ 个缝里面，这是一个经典组合数学问题，方案数为 $A_{i+1}-1\choose j-2$。而对于剩下 $A_{i+1}-(j-1)$ 个数，每塞一个数就会多一个段，所以最终有多少段是能算出来的。其他情况同理。那么我们就解决了转移的问题。

细节：当转移后左右两端只有一端能继续接，但是之前两端都可以接，方案数需要 $\times 2$。

事实上，如果仔细观察一下式子，你会发现 $j$ 的数量和 $k$ 的数量是一个量级的，所以 $f$ 的可行状态数量也是 $O(n)$ 的，直接 dp 即可，具体实现可以使用 `map` 或 `unordered_map`。

```cpp
#include <iostream>
#include <map>

using namespace std;
using LL = long long;
using Pll = pair<LL, LL>;

const int kN = 2e5 + 1;
const LL kM = 998244353;

int n, a[kN], v;
LL l, fc[kN], iv[kN];
map<LL, LL> f[kN][3];

LL P(LL b, int e) {
  LL s = 1;
  for (; e; e >>= 1, b = b * b % kM) {
    (e & 1) && (s = s * b % kM);
  }
  return s;
}
LL C(int n, int m) { return fc[n - 1] * iv[m - 1] % kM * iv[n - m] % kM; }
void T(int i, LL j, int k, int nk, LL v) {
  int nj = j - nk + 1;
  if (a[i + 1] >= nj) {
    LL c = C(a[i + 1], nj) * (1 + (nk == 1 && k != 1));
    LL &_f = f[i + 1][nk][1 + a[i + 1] - nj];
    _f = (_f + c * v % kM) % kM;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (int i = fc[0] = 1; i < kN; ++i) {
    fc[i] = fc[i - 1] * i % kM;
  }
  iv[kN - 1] = P(fc[kN - 1], kM - 2);
  for (int i = kN - 1; i; --i) {
    iv[i - 1] = iv[i] * i % kM;
  }
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    l += a[i];
  }
  T(0, 0, 0, 0, 1);
  for (int i = 1; i < n; ++i) {
    for (int k = 0; k < 3; ++k) {
      for (Pll j : f[i][k]) {
        for (int nk = k; nk < 3; ++nk) {
          T(i, j.first, k, nk, j.second);
        }
      }
    }
  }
  cout << (f[n][0][1] + f[n][1][1] + f[n][2][1]) % kM;
  return 0;
}
```

---

## 作者：云浅知处 (赞：14)

考虑按值域从小到大插入数，维护当前空位数。这里空位指的是可以往里面插入 $i+1$ 使得合法的位置数。

假设当前插入了 $\le i$ 的数，且有 $j$ 个 $i,i$ 相邻的空位。

每次要把 $A_{i+1}$ 个 $i+1$ 插入到空位里，且每个空位至少被插入一个。

那么一个空位如果插入了两个 $A_{i+1}$ 就会继承下去一个空位，如果插入了一个 $A_{i+1}$ 则这个空位就会消失。但两端不同，例如左边有一个 $=i$ 的那你插入一个 $=i+1$ 的可以新建空位，同时也可以在左边使劲放 $i+1$ 造出一堆空位。

那为了方便我们认为 $j$ 里面不包含左右的空位，同时额外记录左右是否有空位。

发现首先需要 $A_i\ge j$，然后往中间的 $j$ 个空位各放一各之后，还剩 $A_i-j$ 个，这部分每放一个就多一个空位。

但如果左边可以放的话，那么这里实际上可以放 $i+1$ 但是没有多空位，不过再放的话也是放一个就多一个空位。

也就是说当前的 $j$ 个空位可以变成 $A_i-j,A_i-j-1,A_i-j-2$ 个空位，取决于左右是否为 $i$。但你注意到如果不往左边放，那么左边直接就结束了；同理不往右边放的话也是直接结束，因此如果变成 $A_i-j$ 之后就一直这样被 $A_i$ 减下去了；变成 $A_i-j-1$ 之后后面都顶多再额外 $-1$。画个图就会发现每一层最多只有三个点：

![](https://cdn.luogu.com.cn/upload/image_hosting/rpejsjbg.png)

于是每一层最多 $12$ 个状态，直接转移即可。

具体写一下状态和转移：$f(i,j,0/1,0/1)$ 表示考虑了 $\le i$ 的数，左右是否有空位。

首先如果 $j>A_{i+1}$ 那么这个状态将无法转移。另外还需要 $j\neq 0$ 或者左右有空位，否则 $i+1$ 没地方填。

转移有：

- $f(i,j,p,q)\times\binom{A_{i+1}-1}{j-1}\to f(i+1,A_{i+1}-j,0,0)$，表示左右都不填。
- $f(i,j,1,p)\times \binom{A_{i+1}-1}{j}\to f(i+1,A_{i+1}-j-1,1,0)$，表示填左不填右。
- $f(i,j,p,1)\times \binom{A_{i+1}-1}{j}\to f(i+1,A_{i+1}-j-1,0,1)$，同上。
- $f(i,j,1,1)\times\binom{A_{i+1}-1}{j+1}\to f(i+1,A_{i+1}-j-2,1,1)$：两边都填。

我偷懒写了个 map 来存状态。这样并不会增加复杂度，因为 map 里面存的状态数是 $O(1)$ 的。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}

const int N=5e5+5;
map<int,int>f[2][2][2];
int n,a[N],fac[N],ifac[N];
void init(int V){
	fac[0]=1;for(int i=1;i<=V;i++)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[V]=inv(fac[V])%mod;for(int i=V-1;i>=0;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
int C(int x,int y){
	if(x<y)return 0;
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

signed main(void){

	n=read();init(N-5);
	for(int i=1;i<=n;i++)a[i]=read();
	int cur=0;
	f[cur][1][1][a[1]-1]=1;
	auto Add=[&](int x,int y,int j,int v){
		auto it=f[cur^1][x][y].find(j);
		if(it!=f[cur^1][x][y].end())add((*it).second,v);
		else f[cur^1][x][y][j]=v;
	};
	for(int i=1;i<n;i++){
		for(int x=0;x<=1;x++)for(int y=0;y<=1;y++)f[cur^1][x][y].clear();
		for(int x=0;x<=1;x++)for(int y=0;y<=1;y++){
			for(auto [j,v]:f[cur][x][y])if(j!=0||x!=0||y!=0){
				if(j>0&&j<=a[i+1])Add(0,0,a[i+1]-j,1ll*v*C(a[i+1]-1,j-1)%mod);
				if(x==1&&j+1<=a[i+1])Add(1,0,a[i+1]-j-1,1ll*v*C(a[i+1]-1,j)%mod);
				if(y==1&&j+1<=a[i+1])Add(0,1,a[i+1]-j-1,1ll*v*C(a[i+1]-1,j)%mod);
				if(x==1&&y==1&&j+2<=a[i+1])Add(1,1,a[i+1]-j-2,1ll*v*C(a[i+1]-1,j+1)%mod);
			}
		}
		cur^=1;
	}
	int ans=0;
	for(int x=0;x<=1;x++)for(int y=0;y<=1;y++)add(ans,f[cur][x][y][0]);
	cout<<ans<<endl;

	return 0;
}
```

---

## 作者：ღꦿ࿐ (赞：14)

牛逼逼题。


首先发现序列的总长是非常大的，和矩阵快速幂之类的东西也没啥关系，肯定就不能从序列的角度进行 dp 了，于是从值域角度进行 dp 。 

从小到大把每种数放进去。

自己想到了类似连续段 dp 的做法 ， 但是不太会处理快速转移 ， 想到了枚举新建的连续段的数量和合并的连续段的数量，也发现了两者的差是定值，但是完全没有想过不考虑合并这些操作，只是考虑插板的相对位置  。

$f_{i}$ 表示两个端点都没有被钦定，有恰好 $i$  个连续段的方案数。

$g_i$ 表示端点被钦定一个， 有恰好  $i$ 个连续段的方案数。

$h_i$ 表示端点都被钦定了， 有恰好  $i$ 个连续段的方案数。

有转移

$f' , g' , h'$ 表示新的 $f , g,h$

$f'_{A-i} = f_i \times \binom {A-1} i  $

$g'_{A - i + 1} = f_i \times \binom {A-1} {i-1}\times 2 + g_i \times \binom{A-1}{i-1}  $

$h'_{A-i+2}  = f_i \times \binom {A-1} {i-2}+ g_i \times \binom{A-1}{i-2} + h_i \times \binom {A-1}{i-2}  $



大家都说这题神仙在状态数是 $O(n)$ 的，转移很简单。

我反而觉得状态数 $O(n)$ 挺显然的 ， 转移才是妙点。

就拿 $ f \to f'$ 来举例子。

转移到的目标是 $A - i$ 很好理解。

就是你得在每个原来的段两边都得有两个目前的数才行，这样你就有了 $j$ 段 ， 再把其它 $n - 2j$ 个加进去就是 $n - j$ 段 ，这时候合并两个段就是拿一个中间的走 ，由于要把目前的数全部放完，就得新建一个段，所以总段数仍然是 $n - j$ 。

这个系数的来源是这样的。

考虑先放了 $j + 1$ 数进每个段的右边以及最左边段的左边 ， 现在还剩  $A - j - 1$ 个数  ， 要把这些数插到 $j$ 段形成的 $n + 1$ 个集合，所以方案数是 $\binom {A-1} j  $ 。

Q：为什么插板的组合意义和连续段是一一对应的？

A：现在的假设下，所有段都被合并成了一段，在最左、最右插数，实际意义是在最这里新建，在其它位置插板第一次是将这里“断开”成两个连续段 ， 即选择不合并，后面再插板即是新建。

其它式子的组合意义类似。

Q：为啥显然 dp 的状态是 $O(n)$ 的。

A：

考虑归纳

令 $S_i = A_i - S_{i-1}$ ，  

对于每个时刻。

显然 $f$ 的取值只有一种 $S_i$ ， $g$ 从 $f$ 转移过来的值只有$S_i  + 1$ 。 

假设以及证明了之前的取值只有 $S_i ,S_i + 1$ ，那么这一步也只会产生 $S_i , S_i + 1$ ，最开始又只有 $S_i + 1$，所以就只会有这 $O(1)$ 个值。

对 $h$  的证明同理。




---

## 作者：syzf2222 (赞：4)

不是很困难的一道题（至少我自己做出来了而且认为比较简单）。

考虑从小往大放，一些 $i+1$ 只能放在相邻两个 $i$ 中或者放在靠边且有一个相邻的 $i$。设 $dp_{i,j,u,v}$ 表示填到了 $i$，有 $j$ 对相邻的 $i$，左边是不是 $i$，右边是不是 $i$。这样我们就有了一个 $O(nV)$ 的做法。

套路地想到 $j$ 这一维应该很少。考虑如果我一直不放两边，则每次的 $j$ 都是确定的，而放一个放两边会导致 $1$ 的变化，而如果上一个和这一个都放了某一边，则这一个不会产生变化。故 $j$ 的取值不超过 $5$ 个。

直接 $dp$ 即可，复杂度 $O(n)$。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=998244353;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=5e5+5;
int fac[N+5],ifc[N+5],inv[N+5],n,m,a[maxn];
inline int com(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return 1ll*fac[x]*ifc[y]%mod*ifc[x-y]%mod;
}
#define fr(i,lim) for(int i=0;i<=lim;i++)
int dp[maxn][5][2][2],cur[maxn],ans;
inline void add(int &x,int y){x=(x+y>=mod?x+y-mod:x+y);}
int main(){
	n=read();fac[0]=ifc[0]=inv[1]=1;
	for(int i=2;i<=N;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=N;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1;i<=N;i++)ifc[i]=1ll*ifc[i-1]*inv[i]%mod;
	for(int i=1;i<=n;i++)a[i]=read();
	dp[1][2][1][1]=1;cur[1]=a[1]-1;
	for(int i=2;i<=n;i++){
		cur[i]=a[i]-cur[i-1];
		fr(j,4)fr(u,1)fr(v,1)if(dp[i-1][j][u][v]){
			int val=dp[i-1][j][u][v],c=cur[i-1]+j-2;
			fr(p,u)fr(q,v){
				if(!p&&!q)add(dp[i][4-j][p][q],1ll*val*com(a[i]-1,c-1)%mod);
				else if(p&&q)add(dp[i][2-j][p][q],1ll*val*com(a[i]-1,c+1)%mod);
				else if(p)add(dp[i][3-j][p][q],1ll*val*com(a[i]-1,c)%mod);
				else add(dp[i][3-j][p][q],1ll*val*com(a[i]-1,c)%mod);
			}
		}
	}
	fr(i,4)if(cur[n]+i-2==0)
		fr(u,1)fr(v,1)add(ans,dp[n][i][u][v]);
	printf("%d\n",ans);
	return 0;
}
```

深深地感到自己的渺小。

---

## 作者：zac2010 (赞：2)

简单的操作分析题。

## 一些基础想法

首先，注意到直接怼着序列，不好计数。考虑按照值域从小到大计数。

假若不考虑边界（或者我们令 $B_0=B_{N+1}=N+1$），那么每次的段数是固定的。

具体的，元素 $1$ 的所有数形成了 $a_1$ 个不能相交的段，其中每个段两端都需要两个元素 $2$。但是两个段假若相邻，则可以共用一个 $2$ 元素。

容易发现，此时在完成所有元素 $2$ 的插入后，必定是形如一些类似 `212,2121212` 以及单独 `2` 的段。
这些段都满足：每段的元素 $2$ 个数都比元素 $1$ 个数多 $1$。

故而每次容易算出有多少个新的段。而考虑到当前值域的所有元素和段时，我们往往只关心段数，因为这些段在后面计算的时候没有本质区别。

而如何组合拼接这些的段，可以用一个组合数直接完成。

## 正确的做法

但是现在考虑到两端都存在边界。

换句话说，比如当前有 $5$ 个元素 $1$ ，要插入 $7$ 个元素 $2$。

按照上面的想法，一种可行方案是 `21212,2121212`，它现在的段数是 $a_2-a_1=7-5=2$。

当然，实际上还存在其它分配方案，比如 `1212,212,21212`。
但是在这种方案中，第一段它的两端就不全是 $2$ 了，换句话说，它现在只能放在最终序列的左边界。

注意到边界只有左、右两个。

故而我们记 $f_{i,j=0\sim 2,k}$ 表示，考虑了值域为 $1\sim i$ 的所有数，左右边界中已经被占据的边界有 $j$ 个，最终形成了 $k$ 个两端都是元素 $i$ 的段。

这里的 $k$ 只有 $O(1)$ 个，可以轻松通过。

## 代码


```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for (int i = (a); i <= (b); ++i)
#define FR(i, a, b) for (int i = (a); i >= (b); --i)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
constexpr int N = 2e5 + 10, V = 2e5;
constexpr int mod = 998244353;
int n, cnt[N];
int inv[N], fac[N], ifac[N];
unordered_map<int, int> f[N][3];
inline void AddTo(int &x, const int &y) {
    x += y;
    x -= (x >= mod? mod : 0);
}
void Init() {
    fac[0] = ifac[0] = 1;
    FL(i, 1, V) {
        inv[i] = (i == 1? 1 : (ll)inv[mod % i] * (mod - mod / i) % mod);
        fac[i] = (ll)fac[i - 1] * i % mod;
        ifac[i] = (ll)ifac[i - 1] * inv[i] % mod;
    }
}
int C(int n, int m) {
    if (n < m || m < 0) {
        return 0;
    }
    return (ll)fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}
int main() {
    Init();
    scanf("%d", &n);
    FL(i, 1, n) {
        scanf("%d", &cnt[i]);
    }
    f[1][2][cnt[1] - 1] = 1;
    FL(i, 2, n) {
        FL(a, 0, 2) {
            FL(c, a, 2) {
                for (auto x: f[i - 1][c]) {
                    int u = x.fi + a, v = x.se;
                    if (cnt[i] < u) continue;
                    int tmp = (ll)v * C(cnt[i] - 1, u - 1) % mod;
                    if (c == 2 && a == 1) {
                        tmp = tmp * 2 % mod;
                    }
                    AddTo(f[i][a][cnt[i] - u], tmp);
                }
            }
        }
    }
    int ans = 0;
    FL(a, 0, 2) {
        AddTo(ans, f[n][a][0]);
    }
    printf("%d\n", ans);
	return 0;
}
```

---

## 作者：翼德天尊 (赞：1)

无非有两种 dp 方式，一种以序列为阶段，从左到右 dp；一种以值为阶段，从小到大填值。前者复杂度显然爆炸，故考虑后者。

发现若填完值 $i$ 后要填 $i+1$，我们会怎么填呢？首先肯定会在所有相邻位置值 $i$ 之间放上 $i+1$ 将其隔开，然后若不考虑两侧，我们就可以将剩下的 $i+1$ 放在已经填入的 $i+1$ 旁边——值 $i+1$ 在 $i+2$ 填入之前，一定只会与 $i$ 或 $i+1$ 相邻。

那么设之前有 $j$ 对相邻的值 $i$，现在要填入 $a_{i+1}$ 个 $i+1$，根据隔板法，则方案数为 $C^{j-1}_{a_{i+1}-1}$。 

现在考虑两侧，不难想到只有当最左/右端为 $i$ 时，才可能在该端填入 $i+1$；且若不填入，填 $i+2$ 时一定不能再填到两侧。

此时状态已经很明晰了！不妨设 $dp_{i,j,0/1/2}$ 表示填完值 $1\sim i$，当前有 $j$ 对 $i$ 相邻，且两端都为 $i$ / 一端为 $i$ / 两端都不为 $i$ 时的方案数。对于多填一侧或两侧的情况，隔板法算组合数时多分一个段即可。

不过到目前为止我们表面上的复杂度依然为 $O(n|a|)$。

但是注意到上一阶段作为状态的 $j'$ 在转移到当前阶段时，都会被当前阶段的 $j$ 减去，故根据势能分析，若不算最后一维，总状态数至多为 $|a|$。加上最后一维后状态数只会有常数上的变动，总复杂度依旧为 $O(n)$。

故转移时用个 map 之类的东西辅助转移即可，可以再开个 vector 记录当前都有哪些状态，不过需要去重。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
const int V=2e5+2;
const int mod=998244353;
int n,a[N];
ll jc[N],inv[N];
map<int,ll> dp[N][3];
vector<int> ve[N][3];
bool vis[N][3];
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
void init(){
	jc[0]=inv[0]=1;
	for (int i=1;i<=V;i++) jc[i]=jc[i-1]*i%mod;
	inv[V]=ksm(jc[V],mod-2);
	for (int i=V-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
ll C(int x,int y){
	if (x<y) return 0;
	return jc[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
	// freopen("out.out","w",stdout);
#endif
	init();
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	dp[1][0][a[1]-1]=1;
	ve[1][0].push_back(a[1]-1);
	for (int i=1;i<n;i++){
		int len=ve[i][0].size();
		for (int x=0;x<len;x++){
			int j=ve[i][0][x];
			if (a[i+1]<j) continue;
			if (j>=1){
				dp[i+1][2][a[i+1]-j]=(dp[i+1][2][a[i+1]-j]+dp[i][0][j]*C(a[i+1]-1,j-1)%mod)%mod;
				if (!vis[a[i+1]-j][2]) ve[i+1][2].push_back(a[i+1]-j),vis[a[i+1]-j][2]=1;
			}
			if (a[i+1]<j+1) continue;
			dp[i+1][1][a[i+1]-j-1]=(dp[i+1][1][a[i+1]-j-1]+dp[i][0][j]*C(a[i+1]-1,j)*2ll%mod)%mod;
			if (!vis[a[i+1]-j-1][1]) ve[i+1][1].push_back(a[i+1]-j-1),vis[a[i+1]-j-1][1]=1;
			if (a[i+1]<j+2) continue;
			dp[i+1][0][a[i+1]-j-2]=(dp[i+1][0][a[i+1]-j-2]+dp[i][0][j]*C(a[i+1]-1,j+1)%mod)%mod;
			if (!vis[a[i+1]-j-2][0]) ve[i+1][0].push_back(a[i+1]-j-2),vis[a[i+1]-j-2][0]=1;
		}
		len=ve[i][1].size();
		for (int x=0;x<len;x++){
			int j=ve[i][1][x];
			if (a[i+1]<j) continue;
			if (j>=1){
				dp[i+1][2][a[i+1]-j]=(dp[i+1][2][a[i+1]-j]+dp[i][1][j]*C(a[i+1]-1,j-1)%mod)%mod;
				if (!vis[a[i+1]-j][2]) ve[i+1][2].push_back(a[i+1]-j),vis[a[i+1]-j][2]=1;
			}
			if (a[i+1]<j+1) continue;
			dp[i+1][1][a[i+1]-j-1]=(dp[i+1][1][a[i+1]-j-1]+dp[i][1][j]*C(a[i+1]-1,j)%mod)%mod;
			if (!vis[a[i+1]-j-1][1]) ve[i+1][1].push_back(a[i+1]-j-1),vis[a[i+1]-j-1][1]=1;
		}
		len=ve[i][2].size();
		for (int x=0;x<len;x++){
			int j=ve[i][2][x];
			if (a[i+1]<j) continue;
			if (j>=1){
				dp[i+1][2][a[i+1]-j]=(dp[i+1][2][a[i+1]-j]+dp[i][2][j]*C(a[i+1]-1,j-1)%mod)%mod;
				if (!vis[a[i+1]-j][2]) ve[i+1][2].push_back(a[i+1]-j),vis[a[i+1]-j][2]=1;
			}
		}
		len=ve[i+1][0].size();
		for (int x=0;x<len;x++){
			int j=ve[i+1][0][x];
			vis[j][0]=0;
		}
		len=ve[i+1][1].size();
		for (int x=0;x<len;x++){
			int j=ve[i+1][1][x];
			vis[j][1]=0;
		}
		len=ve[i+1][2].size();
		for (int x=0;x<len;x++){
			int j=ve[i+1][2][x];
			vis[j][2]=0;
		}
	}
	cout<<(dp[n][0][0]+dp[n][1][0]+dp[n][2][0])%mod<<'\n';
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

**ARC146E**

模拟赛的 $\text{T3}$，因为被巨大多邪恶混乱 $\text{T1}$ 给阴间到了所以这道题也被日掉了。青蛙。

---------------------------------------------------

考虑暴力，凭感觉很[地精部落](https://www.luogu.com.cn/problem/P2467)。

经过大量的手玩，我们考虑我们答案序列的性质：由若干个单峰拼在一起的序列。

那么任意一个数 $\text x$ 除了在首尾，两边一定是 $\text x - \text 1$，那么状态其实是很好设计的：

令 $\text m$ 为当前的序列长。设 $\text{dp}_{\text i,\text j,\text 0/\text 1,\text 0/\text 1}$ 表示前 $\text i$ 种数里面有 $\text j$ 个位置 $\text p \in [\text 1,\text m]$ 满足 $\text a_{\text p} = \text a_{\text p + \text 1}$ 且 $\text a_{\text p} = \text i$，以及 $\text a_{\text 1}$ 和 $\text a_{\text m}$ 是否为 $\text i$。

这么转移的正确性显然，因为 $\text i$ 的位置本质上是依赖了所有 $\text i - \text 1$ 和 $\text i + \text 1$ 的位置，所以在确定了 $\text i$ 的位置和 $\text i - \text 1$ 的位置是必须确定的（相邻），并且我们保留任意答案的大小在 $\leq \text i$ 以内的数后可以发现除了大小为 $\text i$ 的数以外其它位置都是合法的，并且值为 $\text i$ 的位置都是连续的。

刷个表。显然 $\text{dp}_{\text 0,\text 0} \rightarrow \text{dp}_{\text 0,\text 0},\text {dp}_{0,1} \rightarrow \{\text{dp}_{\text 0,\text 0},\text {dp}_{0,1}\},\text {dp}_{1,0} \rightarrow \{\text{dp}_{\text 0,\text 0},\text {dp}_{1,0}\},\text {dp}_{1,1} \rightarrow \{\text{dp}_{\text 0,\text 0},\text {dp}_{1,0},\text{dp}_{\text 1,\text 0},\text {dp}_{1,1}\}$，转移的时候用插板法算一下就行了，这个不具体展开了。

然后关键点是这个状态很少该怎么理解。你随几个序列来打表是可以尝试观察的，你直观感受会发现当 $\text n$ 大了后对于 $\text A_{\text i}$ 的限制越来越严格，否则答案很有可能为 $\text 0$。

一个比较简单的理解：我们考虑转移时，例如当前为 $\text j$，那么可能像 $\text c_{i + 1} - \text j - \text o$，其中 $\text o \in \{0,1,2\}$。观察连续的三轮，发现如果第一轮，第二轮选择了在两边放等价于第一轮第二轮不在两边放得到的 $\text j$ 的状态，构造极差大致是第一轮两边都不放然后第二轮都不放，可以得到所有状态 $\text j$ 的极差是 $\text 5$，开个 $\text{map}$ 直接转移即可。

时间复杂度 $\text O(\text n \log \text n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 5e5 + 5 , mod = 998244353 , M = 5e5;
int n,m,c[Len],fac[Len],invf[Len];
inline void Mod(int &x){if(x < 0) x += mod;if(x >= mod) x -= mod;}
map<int,int> dp[Len][2][2];
inline int qpow(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		b = b >> 1;
	}
	return res;
}
inline int C(int N,int M){return 1ll * fac[N] * invf[N - M] % mod * invf[M] % mod;}
map<int,int>::iterator it;
int main()
{
	scanf("%d",&n);fac[0] = 1;for(int i = 1 ; i <= M ; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
	invf[M] = qpow(fac[M] , mod - 2);invf[0] = 1;
	for(int i = M - 1 ; i >= 1 ; i --) invf[i] = 1ll * invf[i + 1] * (i + 1) % mod; 
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&c[i]);
	dp[1][1][1][c[1] - 1] = 1;
	for(int i = 1 ; i < n ; i ++)
	{
		//必须保证 i 相邻间隙的情况都被填满 
		//0,0
		int j,w,to;
		for(it = dp[i][0][0].begin() ; it != dp[i][0][0].end() ; it ++) 
		{
			j = it -> first , w = it -> second;
			if(c[i + 1] >= j) 
			{
				to = c[i + 1] - j;
				dp[i + 1][0][0][to] += 1ll * w * C(c[i + 1] - 1 , j - 1) % mod , Mod(dp[i + 1][0][0][to]);
			}
		}
		//0,1
		for(it = dp[i][0][1].begin() ; it != dp[i][0][1].end() ; it ++)
		{
			j = it -> first , w = it -> second;
			if(c[i + 1] >= j)
			{
				to = c[i + 1] - j;
				dp[i + 1][0][0][to] += 1ll * w * C(c[i + 1] - 1 , j - 1) % mod , Mod(dp[i + 1][0][0][to]);			
			}
			if(c[i + 1] >= j + 1)
			{
				to = c[i + 1] - j - 1;
				dp[i + 1][0][1][to] += 1ll * w * C(c[i + 1] - 1 , j) % mod , Mod(dp[i + 1][0][1][to]);
			}
		}
		//1,0
		for(it = dp[i][1][0].begin() ; it != dp[i][1][0].end() ; it ++)
		{
			j = it -> first , w = it -> second;
			if(c[i + 1] >= j)
			{
				to = c[i + 1] - j;
				dp[i + 1][0][0][to] += 1ll * w * C(c[i + 1] - 1 , j - 1) % mod , Mod(dp[i + 1][0][0][to]);			
			}
			if(c[i + 1] >= j + 1)
			{
				to = c[i + 1] - j - 1;
				dp[i + 1][1][0][to] += 1ll * w * C(c[i + 1] - 1 , j) % mod , Mod(dp[i + 1][1][0][to]);
			}
		}
		//1,1
		for(it = dp[i][1][1].begin() ; it != dp[i][1][1].end() ; it ++)
		{
			j = it -> first , w = it -> second;
			if(c[i + 1] >= j)
			{
				to = c[i + 1] - j;
				dp[i + 1][0][0][to] += 1ll * w * C(c[i + 1] - 1 , j - 1) % mod , Mod(dp[i + 1][0][0][to]);			
			}
			if(c[i + 1] >= j + 1)
			{
				to = c[i + 1] - j - 1;
				dp[i + 1][1][0][to] += 1ll * w * C(c[i + 1] - 1 , j) % mod , Mod(dp[i + 1][1][0][to]);
				dp[i + 1][0][1][to] += 1ll * w * C(c[i + 1] - 1 , j) % mod , Mod(dp[i + 1][0][1][to]);
			}
			if(c[i + 1] >= j + 2)
			{
				to = c[i + 1] - j - 2;
				dp[i + 1][1][1][to] += 1ll * w * C(c[i + 1] - 1 , j + 1) % mod , Mod(dp[i + 1][1][1][to]);
			}
		}
	}
	int as = 0;
	as += dp[n][0][0][0] , Mod(as);
	as += dp[n][0][1][0] , Mod(as);
	as += dp[n][1][0][0] , Mod(as);
	as += dp[n][1][1][0] , Mod(as);
	printf("%d\n",as);
	return 0;
}
/*
2
2 1
*/
```

---

## 作者：Purslane (赞：0)

# Solution

唉，连续段 DP。

只保留 $\le i$ 的数，一定形如若干连续段。那么维护连续段个数。

任意两个连续段中间可以且应当能放 $i+1$，而首尾不一定，开两个 $0/1$ 记录，因此得出了状态 $dp_{i,j,0/1,0/1}$。

考虑转移，我们将 $a_{i+1}$ 个 $i+1$ 放入序列中。

发现每两个连通块中都可以放 $1$、$2$、$3$、$\cdots$ 个 $i+1$，让连通块个数 $-1$、$0$、$+1$、$\cdots$。（注意特判首尾。能放却不放、原来就不能放都会导致下一次不能放）而我们只需要对不等方程求解，直接使用插板法即可。

看起来你的状态数都高达 $O(n^2)$，显然过不去。

但是实际上，考虑 $dp_{i-1,j',?,?}$ 转移到 $dp_{i,j,op1,op2}$，应当有 $j'+a_i - 2(j'-1) - op_1 - op_2 = j$，整理一下就是 $a_i - j' + 1 - op_1 - op_2 = j$。

考虑 $op_1+op_2$ 在历史时刻的变化，设这个值在 $i$ 时刻为 $t_i$。那么他们对最终 $j$ 的贡献形如 $\sum (-1)^{i+c} t_i$，$c$ 是一个常数。而 $t_i$ 单调变化，所以这个值也只有 $O(1)$ 种可能，总的状态数就是 $O(n)$ 的了。

而一个状态的后继个数也为 $O(1)$ 所以保留有效状态直接暴力转移复杂度就是对的。

唉感觉这个只保留有效状态非常深刻啊，可能是我太菜了吧。

٩(ŏ﹏ŏ、)۶

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10,MOD=998244353;
int n,t=500000,a[MAXN],frac[MAXN],inv[MAXN]; 
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {if(u>d||u<0) return 0;return frac[d]*inv[u]%MOD*inv[d-u]%MOD;}
const int MAXM=2e5+10;
map<int,int> dp[MAXM][2][2];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i];
	frac[0]=1; ffor(i,1,t) frac[i]=frac[i-1]*i%MOD;
	inv[t]=qpow(frac[t],MOD-2); roff(i,t-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	dp[1][1][1][a[1]]=1;
	ffor(i,1,n-1) {
		ffor(o1,0,1) ffor(o2,0,1) ffor(no1,0,o1) ffor(no2,0,o2) {
			for(auto pr:dp[i][o1][o2]) {
				int j=pr.first,v=pr.second,nj=j+a[i+1]-2*(j-1)-no1-no2,kw=j-1+no1+no2;
				//j-1+no1+no2 个空，减去 2(j-1)+no1+no2
				if(nj>0&&kw<=a[i+1]&&kw>0) dp[i+1][no1][no2][nj]=(dp[i+1][no1][no2][nj]+v*C(kw-1,a[i+1]-1))%MOD;
			}
		}
	}
	int ans=0;
	ffor(i,0,1) ffor(j,0,1) ans=(ans+dp[n][i][j][1])%MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

算是自己想出来的（？）

考虑按 $1,2,3,\cdots,n$ 的顺序将这些数加入序列，显然，我们只关心加完所有值 $\le i$ 的数之后，有多少个相邻的数大小都为 $i$，因为如果存在两个相邻相同的 $<i$ 的数那么在后面的步骤中我们肯定无法将这一对数消掉。因此这个序列必然没法变成合法的序列。

思考一下我们每次加入所有值 $=i$ 的数会发生什么。显然我们需要用 $i$ 来填补上一轮相邻的 $i-1$ 之间的空隙，剩下的 $i$ 有两种选择：要么与已有的 $i$ 相邻形成连续段，如果序列的某一侧是 $i-1$，那么我们这个 $i$ 还可以填在 $i-1$ 的边上。比方说如果上一轮是 $3,2,3,3,2,1,2,3,3$，那么下一轮可以变成 $4,3,2,4,3,2,1,2,4,4,4,3,4,4$。

不难发现后一种转移与开头和结尾中有多少个是 $i-1$ 有关（$0/1/2$），因此我们额外记录下这个变量即可，也就是说我们记 $dp_{i,j,k}$ 表示填入了前 $i$ 个数，目前有 $j$ 对 $i$ 相邻，开头和结尾有 $k$ 个数是 $i$ 的方案数。转移插板法算一下即可。朴素 DP 是 $n^2$ 的，不过注意到一个性质：记 $c_i$ 表示插入值 $\le i$ 的数的时候，每一步都不在边上放 $i$，这样会有多少对 $i$ 相邻——显然这是一个定值，那么所有可能的 $j$ 都在 $c_i$ 附近，大概枚举 $[c_i-7,c_i+7]$ 就可以过了。

---

