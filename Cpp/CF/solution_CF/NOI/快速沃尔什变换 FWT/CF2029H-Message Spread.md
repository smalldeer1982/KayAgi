# Message Spread

## 题目描述

给定一个无向图，包含 $n$ 个顶点和 $m$ 条边。每条边连接两个顶点 $(u, v)$，且每天出现的概率为 $\frac{p}{q}$。

初始时，顶点 $1$ 拥有一条消息。每天结束时，某个顶点拥有消息，当且仅当它自己或与其相邻的至少一个顶点在前一天拥有消息。注意，每天每条边是否出现是独立选择的。

请计算所有顶点都拥有消息所需的期望天数，结果对 $998\,244\,353$ 取模。

## 说明/提示

在第一个测试点中，答案等于图中唯一一条边第一次出现所需的期望天数，即 $\frac{1}{0.1}=10$。

在第二个测试点中，答案为 $\frac{20}{9}$，再对 $998\,244\,353$ 取模。

在第三个测试点中，唯一的顶点已经拥有消息，所以答案为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
1 2 1 10```

### 输出

```
10```

## 样例 #2

### 输入

```
3 3
1 2 1 2
1 3 1 2
2 3 1 2```

### 输出

```
887328316```

## 样例 #3

### 输入

```
1 0```

### 输出

```
0```

## 样例 #4

### 输入

```
5 8
1 2 1 11
1 3 2 11
1 4 3 11
1 5 4 11
2 4 5 11
2 5 6 11
3 4 7 11
4 5 8 11```

### 输出

```
469993557```

## 样例 #5

### 输入

```
21 22
1 2 3 4
2 3 4 5
3 4 5 6
5 6 7 8
6 7 8 9
7 8 9 10
8 9 2 3
9 10 3 4
10 11 4 5
11 12 5 6
12 13 6 7
13 14 7 8
14 15 8 9
15 16 9 10
16 17 2 3
17 18 3 4
18 19 4 5
19 20 5 6
20 21 6 7
1 10 100 1001
15 4 147 220
4 11 1 998244352```

### 输出

```
299529765```

# 题解

## 作者：Petit_Souris (赞：12)

闲话：

验题的时候出题人给我看这个题，然后我搁那儿瞎说一通，什么 $3^n$ 什么容斥什么子集卷积的，出题人差点以为我 5min 秒了，让我重新讲一遍，结果发现我在一本正经地胡说八道。

~~官方题解写的连超级大神 `hos_lyric` 和 IOI 金牌 `A_G` 都看不懂，sszcdjr 你好好反思一下！~~

----

很厉害，但是不是想不到的难，只能说是题做少了导致的。

首先肯定得编出点有效的暴力。考虑利用期望的线性性，设 $f_S$ 表示消息恰好传播到点集 $S$ 的概率，$g_S$ 表示目前消息恰好传播到点集 $S$，接下来传出 $S$ 期望需要多少时间。那么如果我们把一个传播过程拆分成若干阶段，即初始一个集合 $S$，每次加入一个与 $S$ 无交的集合 $T$，那么需要的时间就是每次加入的期望时间之和。也就是说，我们所求的答案就是 $\sum f_Sg_S$。

$g_S$ 很好求，算一轮没有传播成功的概率 $p$ 即可，就是 $S$ 向外延申的所有边都断开的概率，那么期望需要 $\frac{1}{1-p}$ 轮。

$f_S$ 有简单的 $\mathcal O(3^n)$ 计算方法：每次枚举一个与 $S$ 无交的集合 $T$，算从 $S$ 扩展到 $S\cup T$ 的概率，即 $T$ 中每个点都和 $S$ 中至少一个点连边，且 $U\backslash(S\cup T)$ 中的点与 $S$ 不连边。这些系数容易预处理出来。场上有若干选手通过对这个做法卡常通过了此题。~~出题人真菜吧。~~

看起来难以优化，因为这个系数和 $S,T$ 都强相关，没法拆开。我们考虑做一步容斥，即设 $h_{S}$ 表示消息完全在 $S$ 内部的概率（即实际传播到的点集是 $S$ 的子集，考虑 $f_{S}\to h_{S\cup T}$ 的转移。

我们把边根据两端的集合分类（用 $(A,B)$ 表示一端在 $A$ 内，一端在 $B$ 内的边）：

- $(S,S),(S,T),(T,T),(T,U\backslash(S\cup T)),(U\backslash(S\cup T),U\backslash(S\cup T))$：这些边都可以任意连或断；

- $(S,U\backslash(S\cup T))$：这些边必须断开。

那么系数即为所有必须断开的边的 $(1-w)$ 之积。发现这个贡献是可以拆开的：设 $P(S)$ 表示 $S$ 集合内部所有边的 $(1-w)$ 之积，那么这个系数实际上就是 $\frac{P(U)P(T)}{P(S\cup T)P(U\backslash S)}$（自己拆一下，看每条边被算了几遍）。现在所有的东西都只关于 $S,T,S\cup T$ 了，没有同时关于两个集合的项。因此可以用子集卷积优化。最后应该还要除掉一个 $1-$ 【没有任何边转移出去的概率】，因为至少要转移出去一条边。这个就是所有 $S$ 和 $U\backslash S$ 之间的连边的乘积，也可以同理拆成关于 $S$ 的系数。 

这里实际上是一个半在线卷积。具体来说，我们按照 popcount 从小到大做卷积。过程大概是：

- 把对应层的 $h$ 做 IFWT；

- 做一遍高维差分（$h$ 是 $f$ 的高维前缀和）得到 $f$；

- 将对应层的 $f$ 做 FWT，做点乘，贡献到对应层的（还未 IFWT 的）$h$ 上。

时间复杂度 $\mathcal O(2^nn^2)$，可以通过。

困爆了，明天再来写代码。我确信我推的是对的。

Upd：代码有了，把 $1$ 那位去掉，用 $n-1$ 位二进制数存状态，常数除掉一半，跑的挺快挺牛的。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline","unroll-loops")
#pragma GCC optimize("-Ofast", "-finline", "-funroll-loops", "-fno-stack-protector")
#pragma GCC target("avx")
#include<bits/stdc++.h>
typedef int ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll Mod=998244353;
ll n,m,w[22][22],iw[22][22];
ll P[(1<<21)+9],iP[(1<<21)+9],f[(1<<20)+9],g[(1<<20)+9],h[(1<<20)+9],tmp[(1<<20)+9],pc[(1<<21)+9];
ll th[22][(1<<20)+9],tp[22][(1<<20)+9],coef1[(1<<20)+9];
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,p>>=1;
    }
    return res;
}
void Add(ll&x,ll y){
    x+=y;
    if(x>=Mod)x-=Mod;
}
void Dec(ll&x,ll y){
    x-=y;
    if(x<0)x+=Mod;
}
void FWT(ll *f,ll n){
    for(ll i=1;i<(1<<n);i<<=1){
        for(ll j=0;j<(1<<n);j+=(i<<1)){
            rep(k,0,i-1)Add(f[j+k+i],f[j+k]);
        }
    }
}
void IFWT(ll *f,ll n){
    for(ll i=1;i<(1<<n);i<<=1){
        for(ll j=0;j<(1<<n);j+=(i<<1)){
            rep(k,0,i-1)Dec(f[j+k+i],f[j+k]);
        }
    }
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read();
    rep(i,0,n-1){
        rep(j,0,n-1)w[i][j]=iw[i][j]=1;
    }
    while(m--){
        ll x=read()-1,y=read()-1,p=read(),q=read();
        p=1ll*p*pw(q,Mod-2)%Mod;
        w[x][y]=w[y][x]=(1-p+Mod)%Mod;
        iw[x][y]=iw[y][x]=pw(1-p+Mod,Mod-2);
    }
    rep(i,1,(1<<n)-1)pc[i]=pc[i^(i&(-i))]+1;
    P[0]=1,iP[0]=1;
    rep(i,1,(1<<n)-1){
        P[i]=P[i^(i&(-i))],iP[i]=iP[i^(i&(-i))];
        ll x=__lg(i&(-i));
        rep(j,0,n-1){
            if(((i>>j)&1))P[i]=1ll*P[i]*w[x][j]%Mod,iP[i]=1ll*iP[i]*iw[x][j]%Mod;
        }
    }
    rep(i,1,(1<<n)-2){
        if(!(i&1))continue;
        ll pb=1ll*P[(1<<n)-1]*iP[i]%Mod*iP[((1<<n)-1)^i]%Mod;
        g[i>>1]=pw(1-pb+Mod,Mod-2);
    }
    n--;
    rep(i,0,(1<<n)-1)coef1[i]=iP[(((1<<n)-1)^i)<<1];
    f[0]=1;
    rep(i,0,n){
        rep(j,0,(1<<n)-1){
            if(pc[j]==i)tp[i][j]=P[(((1<<n)-1)^j)<<1|1];
        }
        FWT(tp[i],n);
    }
    rep(i,0,n-1){
        memset(tmp,0,sizeof(tmp));
        rep(j,0,(1<<n)-1){
            if(pc[j]==i){
                tmp[j]=1ll*iP[j<<1|1]*f[j]%Mod*g[j]%Mod;
                h[j]=(h[j]+1ll*tmp[j]*P[(1<<(n+1))-1])%Mod;
            }
        }
        FWT(tmp,n);
        rep(j,1,n-i){
            rep(k,0,(1<<n)-1){
                th[i+j][k]=(th[i+j][k]+1ll*tmp[k]*tp[j][k])%Mod;
            }
        }
        IFWT(th[i+1],n);
        rep(j,0,(1<<n)-1){
            if(pc[j]==i+1)h[j]=th[i+1][j];
        }
        memcpy(tmp,h,sizeof(h));
        rep(j,0,(1<<n)-1)tmp[j]=1ll*tmp[j]*coef1[j]%Mod;
        rep(j,0,n-1){
            per(k,(1<<n)-1,0){
                if((k>>j)&1)Dec(tmp[k],tmp[k^(1<<j)]);
            }
        }
        rep(j,0,(1<<n)-1){
            if(pc[j]==i+1)f[j]=tmp[j];
        }
    }
    ll ans=0;
    rep(i,0,(1<<n)-1)ans=(ans+1ll*f[i]*g[i])%Mod;
    write(ans),putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：1)

假设 $f_S$ 表示这个过程中经过了 $S$ 的概率。那么期望就是 $\sum f_St_S$。$t_S$ 表示期望在 $S$ 的时间，容易 $O(2^nn^2)$ 计算。

考虑 $f_S$ 转移到其真超集 $T$ 的概率是 $\dfrac{\prod_{i\in T/S}(1-\prod_{j\in S}(1-p_{i,j}))\prod_{i\in [n]/T}\prod_{j\in S}(1-p_{i,j})}{1-\prod_{i\in S}\prod_{j\in[n]/S}(1-p_{i,j})}$。

发现分子的 $i\in T/S$ 的部分过于丑陋。考虑定义一个 $g_S$ 表示这次转移后所有可能点是 $S$ 的子集的概率。$g_S$ 就是 $f_S$ 的高位前缀和。且 $g_S$ 的转移是有好的，我们不需要考虑 $i\in T/S$ 的部分。转移系数即：
$$
\dfrac{\prod_{i\in [n]/T}\prod_{j\in S}(1-p_{i,j})-\prod_{i\in S}\prod_{j\in[n]/S}(1-p_{i,j})}{1-\prod_{i\in S}\prod_{j\in[n]/S}(1-p_{i,j})}
$$
需要注意的是，要把转到自己的贡献扣掉。

分子后面的减号是个常数。直接算就行。考虑怎么简化前面的部分。

假设 $E(S)=\prod_{i\in S}\prod_{j\in S,i<j}(1-w_{i,j})$。那么 $\prod_{i\in [n]/T}\prod_{j\in S}(1-p_{i,j})=\dfrac{E([n]/(S/T))}{E(S)E([n]/T)}$。容易写成 $A(S)B(T)C(S\oplus T)$ 的形式。直接子集卷积即可。

---

## 作者：lalaouye (赞：1)

模拟赛做过类似的题。

首先有个很显然的想法是设 $f(S)$ 表示已经染黑了集合 $S$ 中的点期望还需要多少步全部染黑，可以做到 $\mathcal{O}(3^n)$，貌似没有优化空间。

利用期望的线性性，剖析整个过程，我们设 $f(S)$ 表示所有过程有经过这个状态的概率，$g(S)$ 表示这个状态到第一次染黑别的点的期望步数，于是可以写出另一个答案式子：

$$ans=\sum_S f(S)g(S)$$

容易发现这个式子是对的，$g(S)$ 很好处理，$f(S)$ 也可以做到 $\mathcal{O}(3^n)$ 处理，直接做的式子为 $f(S)w(S,T)\rightarrow f(S\cup T)$。发现这个过程是不好优化的，它与 $S$ 和 $T$ 强相关，既不好一个一个放，又不好子集卷积。

直接做不好做考虑容斥，设 $h(S)$ 表示染黑的点在 $S$ 内的概率，换句话说就是 $h(S)=\sum_{T\subseteq S} f(T)$。考虑 $f$ 如何转移到 $h$。显然我们在整个算概率的过程中是不会考虑图的染色状态不变的情况的，那么不会出现转移出现环的情况，换句话说就是 $f(S)$ 不会转移到 $h(S)$。那么相当于转移形如 $f(S)r(S,T)\rightarrow h(S\cup T)$，考虑 $r(S,T)$ 是否可以变为子集卷积形式。

相当于我们要让 $S$ 到 $U\setminus (S\cup T)$ 的边全部断开，考虑用类似容斥的方式，设 $P(S)=\prod_{e\in S} (1-w_e)$，那么首先我们需要有一个全集 $P(U)$，然后需要除掉 $P(S\cup T)$ 与 $P(U\setminus S)$，但是我们发现 $T$ 中的边被多除了一次，那么再乘个 $P(T)$ 即可。不急，我们得排除状态不变的情况，那么

$$r(S,T)=\frac {\frac {P(U)P(T)}{P(S\cup T)P(U\setminus S)}-r(S,\varnothing)}{1-r(S,\varnothing)}$$

发现这样就可以子集卷积了！后边那个减的有点烦，但是发现这个玩意跟 $T$ 一点关系都没有，就是个高维前缀和，前一半则是子集卷积形式，我们可以把大分母和 $P(U\setminus S)$ 乘到 $f(S)$，然后 $P(T)$ 再交给另一半。

但是我们发现这个子集卷积也是有点棘手的，我们考虑按数二进制下 $1$ 的个数从小到大的顺序处理，每次对于数量 $i$，先更新 $count(S)=i+1$ 的 $h(S)$，然后再更新 $count(S)=i+1$ 的 $f(S)$ 就行了。时间复杂度 $\mathcal{O}(n^22^n)$。

代码感觉写的有点丑，凑合看吧：


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i (l); i <= r; ++ i)
#define rrp(i, l, r) for (int i (r); i >= l; -- i)
#define eb emplace_back
using namespace std;
#define pii pair <int, int>
#define inf 1000000000
constexpr int N = 22, B = 1e8 + 1, P = 998244353;
typedef long long ll;
inline int rd () {
  int x = 0, f = 1;
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
ll qpow (ll x, int y, int p = P) {
  ll ret = 1;
  for (; y; y >>= 1, x = x * x % p) if (y & 1) ret = ret * x % p;
  return ret;
}
void FWT (auto * f, int n, int x) {
  rep (i, 0, n) if (f[i] < 0) f[i] += P;
  if (x == 1) {
    for (int k (1), o (2); k <= n; k <<= 1, o <<= 1) {
      for (int i (0); i <= n; i += o) {
        rep (j, 0, k - 1) {
          if (f[i + j]) {
            f[i + j + k] += f[i + j];
            if (f[i + j + k] >= P) f[i + j + k] -= P;
          }
        }
      }
    }
  }
  else {
    for (int k (1), o (2); k <= n; k <<= 1, o <<= 1) {
      for (int i (0); i <= n; i += o) {
        rep (j, 0, k - 1) {
          if (f[i + j]) {
            f[i + j + k] += P - f[i + j];
            if (f[i + j + k] >= P) f[i + j + k] -= P;
          }
        }
      }
    }
  }
}
int n;
ll e[N][N];
ll w[1 << N], iw[1 << N], g[1 << N];
int f[N][1 << N];
ll bp[1 << N];
ll F[1 << N], G[1 << N];
int h[N][1 << N];
ll nul[1 << N], inul[1 << N];
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd (); 
  for (int m (rd ()); m; -- m) {
    ll u (rd () - 1), v (rd () - 1), p (rd ()), q (rd ());
    e[u][v] = e[v][u] = p * qpow (q, P - 2) % P;
  }
  int m ((1 << n) - 1);
  rep (s, 0, m) {
    w[s] = 1;
    rep (i, 0, n - 1) if (s >> i & 1) rep (j, i + 1, n - 1) if (s >> j & 1) {
      w[s] = w[s] * (1 - e[i][j]) % P;
    }
    iw[s] = qpow (w[s], P - 2);
  }
  rep (s, 0, m) {
    nul[s] = w[m] * iw[s] % P * iw[m ^ s] % P;
    inul[s] = qpow (1 - nul[s], P - 2);
  }
  rep (i, 1, m) bp[i] = bp[i >> 1] + (i & 1);
  rep (i, 0, m) h[bp[i]][i] = w[i];
  rep (i, 1, n) FWT (h[i], m, 1);
  f[0][0] = w[m] * iw[m ^ 1] % P * inul[1] % P;
  FWT (f[0], m, 1);
  F[0] = inul[1] * nul[1] % P;
  FWT (F, m, 1);
  int k ((1 << (n - 1)) - 1);
  rep (i, 0, n - 2) {
    memset (g, 0, sizeof g);
    rep (j, 0, i) {
      rep (s, 0, k) {
        (g[s] += 1ll * f[j][s] * h[i - j + 1][s << 1 | 1]) %= P;
      }
    }
    FWT (g, k, -1);
    rep (s, 0, k) g[s] = g[s] * iw[s << 1 | 1] % P - F[s];
    rep (s, 0, k) if (bp[s] == i + 1) G[s] = g[s];
    FWT (F, k, -1);
    FWT (G, k, -1);
    
    rep (s, 0, k) {
      if (bp[s] == i + 1) F[s] = G[s] * inul[s << 1 | 1] % P * nul[s << 1 | 1] % P, f[i + 1][s] = G[s] * w[m] % P * iw[m ^ (s << 1 | 1)] % P * inul[s << 1 | 1] % P;
    }
    FWT (G, k, 1);
    FWT (f[i + 1], k, 1);
    FWT (F, k, 1);//按顺序来，代码中进行了卡常，因为原本的偶数位显然都是 0，这题卡正解放暴力。。
  }
  FWT (F, k, -1);
  rep (i, 0, k) F[i] = F[i] * qpow (nul[i << 1 | 1], P - 2) % P * (1 - nul[i << 1 | 1]) % P;
  ll ans (0);
  rep (s, 0, k) {
    ll ret (1);
    rep (i, 0, n - 1) {
      if (~ (s << 1 | 1) >> i & 1) continue;
      rep (j, 0, n - 1) {
        if ((s << 1 | 1) >> j & 1) continue;
        ret = ret * (1 - e[i][j]) % P;
      }
    }//ret 是 g(S)
    (ans += F[s] * qpow (1 - ret, P - 2)) %= P;
  } cout << (ans + P) % P; cerr << 1.0 * clock () / CLOCKS_PER_SEC << endl;
}
```

---

## 作者：ForgotMe (赞：1)

很棒的题目啊！赛时卡了 2h 的 $\mathcal{O}(3^n)$ 没卡过去，直接下班睡觉。

首先提出一个高复杂度的做法是简单的，有两种思路：

下面设收到了消息的点状态为 $1$，否则为 $0$。

- 设 $dp_S$ 表示在**只有**集合 $S$ 中的点状态都是 $1$ 的情况下，期望还要经过多少时间使得所有点的状态都是 $1$。转移时简单的，枚举下一个状态变成 $1$ 的集合 $T$（$S\cap T=\emptyset$），精细实现可以做到 $\mathcal{O}(3^n)$。

- 另外一个做法是设 $f_S$ 表示**只有**集合 $S$ 中的点状态都是 $1$ 的概率，$g_S$ 表示在**只有**集合 $S$ 中的点状态都是 $1$ 的条件下，期望还要经过多少时间使得存在至少一个不在 $S$ 中的点的状态变为 $1$。根据期望的线性性质，答案就是 $\sum_{S} f_Sg_S$。

思路 $1$ 不知道是否有前途，没有仔细想。下面仔细讲讲思路 $2$。$g_S$ 是容易计算的，算出不存在一个不在 $S$ 中的点的状态变为 $1$ 的概率，然后取个倒数就行。主要看看 $f_S$ 的转移。类似的枚举一个集合 $T(S\cap T=\emptyset,T\ne \emptyset)$，然后计算使得只有 $T$ 中的点状态都变成 $1$ 的概率，转移即可。一个问题是：$T$ 可能是 $0$，也就是会有自己向自己的转移。但没有关系，在时间趋于无穷的状态下，转移向自己的概率是趋于 $0$ 的！也就是说，可以直接忽略这部分转移。形式化来讲，设 $Q(S,T)$ 表示 $S$ 转移向 $S\cup T$ 的概率，那么有 $f_S\times \frac{Q(S,T)}{1-Q(S,\emptyset)}\rightarrow f_{S\cup T}$。非常遗憾的是，这个做法依然是 $\mathcal{O}(3^n)$ 的，因为 $Q(S,T)$ 与 $S$ 和 $T$ 都有关系，并不独立（$S$ 对 $Q(S,T)$ 的影响是与 $T$ 有关的，$T$ 同理，也就是无法写成 $val(S)\times val(T)\times val(S\cup T)$ 的形式，导致无法优化）。不过实现的好应该可以跑过去，说句题外话，这里想要减小常数有一个非常关键的技巧：就是少取模，先用 long long/int128 把和存下来，最后取模，差不多就可以卡过去了。不过赛时我死活卡不过去，卡在 15s 卡不动了。

如何优化呢？考虑容斥，设 $h_S$ 表示至多只有 $S$ 的中的点状态能为 $1$ 的概率，形式化的讲，有 $h_S=\sum_{T\subseteq S}f_T$，$R(S,T)$ 表示在只有 $S$ 中的点状态为 $1$ 的条件下，强制钦定在 $S\cup T$ 之外的点全部不能变为 $1$ 的概率（$S\cap T=\emptyset$，$T\ne \emptyset$），那么可以非常自然的写出转移 $f_S\times \frac{R(S,T)-Q(S,\emptyset)}{1-Q(S,\emptyset)}\rightarrow h_{S\cup T}$。为什么要这么做呢，一个非常好的性质是 $R(S,T)$ 中 $S$ 与 $T$ 造成的影响独立，具体来说，设 $P(S)=\prod_{e\in S}\frac{1}{1-w_e}$，$w_e$ 表示边 $e$ 出现的概率，那么有 $R(S,T)=\frac{P(S\cup T)\times P(U∖S)}{P(U)P(T)}$，其中 $U$ 是全集，即 $U=\{1,2,...,n\}$。现在这个转移形式就非常的好看了，可以写成 $val(S)\times val(T)\times val(S\cup T)\rightarrow h_{S\cup T}$。相信你已经看出来了，这就是一个子集卷积的形式，但不同的是，这是一个半在线子集卷积。$val(S)$ 是与 $f_S$ 相关的。

这种半在线子集卷积怎么做呢？考虑先算出 $\operatorname{popcount}(S)\le k$ 的 $f_S$，然后再去算 $\operatorname{popcount}(S)=k+1$ 的 $h_S$，再做一个高维后缀和，减去子集的 $f_T$ 之和，就得到了 $\operatorname{popcount}(S)=k+1$ 的 $f_S$。

那么这个题就做完了，时间复杂度 $\mathcal{O}(2^nn^2)$。

扔个代码：https://www.luogu.com.cn/paste/7cc1nl4e

---

