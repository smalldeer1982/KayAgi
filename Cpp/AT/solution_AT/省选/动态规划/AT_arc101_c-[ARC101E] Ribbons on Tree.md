# [ARC101E] Ribbons on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc101/tasks/arc101_c

$ N $ を偶数とします。

$ N $ 頂点の木があります。 頂点には $ 1,\ 2,\ ...,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N\ -\ 1 $) について、$ i $ 番目の辺は頂点 $ x_i $ と $ y_i $ を結んでいます。

すぬけ君は、次のようにして木をリボンで飾りつけようと思っています。

まず、$ N $ 個の頂点を $ N\ /\ 2 $ 組のペアに分けます。 このとき、各頂点はちょうど $ 1 $ つのペアに属さなければなりません。 次に、各ペア $ (u,\ v) $ について、$ 1 $ 本のリボンを $ u $-$ v $ 間の最短パスに含まれるすべての辺を通るように張ります。

すぬけ君はペアの分け方を工夫し、「どの辺にも少なくとも $ 1 $ 本のリボンが張られている」という条件が成り立つようにしようとしています。 条件が成り立つようなペアの分け方は何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。 ただし、$ 2 $ 通りのペアの分け方が異なるとは、あるペアが一方には含まれるが他方には含まれないことを言います。

## 说明/提示

### 制約

- $ N $ は偶数である。
- $ 2\ \leq\ N\ \leq\ 5000 $
- $ 1\ \leq\ x_i,\ y_i\ \leq\ N $
- 与えられるグラフは木である。

### Sample Explanation 1

ペアの分け方は次図の $ 3 $ 通りであり、右側の $ 2 $ 通りが条件を満たします。 !\[\](https://img.atcoder.jp/arc101/2d7584d2e0736f746aa9d54e1bf31e28.png)

### Sample Explanation 2

ペアの分け方は次図の $ 3 $ 通りであり、すべて条件を満たします。 !\[\](https://img.atcoder.jp/arc101/2de530ed2e64d0161ee6b989d1946261.png)

## 样例 #1

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4```

### 输出

```
3```

## 样例 #3

### 输入

```
6
1 2
1 3
3 4
1 5
5 6```

### 输出

```
10```

## 样例 #4

### 输入

```
10
8 5
10 8
6 5
1 5
4 8
2 10
3 6
9 2
1 7```

### 输出

```
672```

# 题解

## 作者：Miraik (赞：22)

先考虑一个 $O(n^3)$ 的简单做法：

设 $f_{u,i}$ 表示 $u$ 的子树内还有 $i$ 个点要向上匹配的方案数。我们发现如果 $(u,v)$ 这条边要被覆盖到，那么 $v$ 的子树内必然有点要向上匹配。

因此合并转移的时候枚举 $u$ 子树内的点数 $i$，$v$ 子树内的点数 $j$（注意 $j\ge1$），以及匹配的对数 $k$，有转移：

$ f_{u,i} \times f_{v,j} \times {i \choose k} \times {j \choose k} \times k! \to newf_{u,i+j-2k} $

答案即为 $f_{1,0}$。但是这样做系数很复杂，感觉完全没有优化的空间。

正难则反，考虑容斥求不合法方案。

对于不合法方案，我们可以看作断开一个边集 $S$，然后给每个联通块内两两配对，得到方案数 $T(S)$，对答案的贡献即为 $(-1)^k \times T(S)$。

容易发现的是，大小为 $2t$ 的联通块两两配对，方案数 $g(t)=\prod_{i=1}^{t} (2i-1)$（注意并不一定是联通的，只是没钦定它们之间被断）

重新设状态 $f_{u,i}$ 表示在 $u$ 子树内，$u$ 所在联通块大小为 $i$ 的方案数。

考虑边的钦定情况，有转移方程：

$f_{u,i} \times f_{v,j} \times (-g(j)) \to newf_{u,i}$ 钦定该边被断

$f_{u,i} \times f_{v,j} \to newf_{u,i+j} $ 该边没被断

答案为 $ \sum_{i=1}^n f_{1,i} \times g(i)$。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
const int mod=1000000007;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
int n,siz[N],g[N],f[N][N],ff[N],ans;
struct Edge{
    int to,nxt;
}e[N<<1];
int head[N],tot;
inline void add(int u,int v){
    e[++tot]={v,head[u]};
    head[u]=tot;
}
inline void dfs(int u,int fa){
    siz[u]=1; f[u][1]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,u);
        for(int j=1;j<=siz[u];j++) ff[j]=f[u][j],f[u][j]=0;
        for(int j=1;j<=siz[u];j++)
            for(int k=1;k<=siz[v];k++){
                (f[u][j]+=mod-1ll*ff[j]*f[v][k]%mod*g[k]%mod)%=mod;
                (f[u][j+k]+=1ll*ff[j]*f[v][k]%mod)%=mod;
            }
        siz[u]+=siz[v];
    }
}
int main(){
    n=read();
    g[0]=1; for(int i=2;i<=n;i+=2) g[i]=1ll*g[i-2]*(i-1)%mod;
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v); add(v,u);
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++) (ans+=1ll*f[1][i]*g[i]%mod)%=mod;
    printf("%d\n",ans);
    return
```


---

## 作者：小粉兔 (赞：18)

### 2019-02-06 补档

直接 DP 的话大概是 $\mathcal O (N^3)$ 的，使用容斥原理：

要计算的就是 $\displaystyle \sum_{S \subseteq E} {(-1)}^{|S|} f(S)$，其中 $f(S)$ 表示强制不能覆盖到 $S$ 中的边的方案数。

也就是把 $S$ 内的边都删掉，原树被分割成了若干连通块，每个连通块内部连线的方案数。

显然一个大小为 $n$ 的连通块，任意连线的方案数为 $1 \cdot 3 \cdot 5 \cdot \cdots \cdot (n - 1)$（如果 $n$ 是偶数，$n$ 是奇数的话显然没有方案）。

那么设状态 $dp(i, j)$ 表示考虑 $i$ 的子树，割掉若干条边，$i$ 所在的连通块大小为 $j$，的贡献总和（不算 $i$ 所在连通块的贡献）。

转移也是显然的。

时间复杂度为 $\mathcal O (N^2)$，[评测链接](https://atcoder.jp/contests/arc101/submissions/9924940)。

---

## 作者：SunsetLake (赞：16)

## 思路

直接正着考虑合法的方案数不是很好做，那么正难则反，可以用总方案数减去不合法方案数，这样容斥一下就能得到答案了。

设 $F(S)$ 表示集合 $S$ 中的边不被覆盖的方案数。那么最后的答案就是 $\displaystyle\sum_{S \subseteq E} (-1)^{|S|}F(S)$。再思考 $F(S)$ 怎么求。不难发现一些边不被覆盖相当于把整棵树分成了若干个连通块，根据 $F$ 的定义，只要求了 $S$ 中的边不被覆盖，其他边状态随意，因此每个连通块中都可以没有限制的配对。对于一个大小为 $m$ 的连通块，记 $sum_m$ 表示它的方案数，若 $m$ 是奇数，那么任意配对的方案数就是 $0$，否则对于第 $1$ 个点，有 $m-1$ 个点能与其配对，第 $2$ 个点就要除去 $1$ 号点配对的两个点，就有 $m-3$ 个点能与其配对。这样类推下去，$sum_m$ 便为 $(m-1)\times (m-3)\times\cdots \times 3 \times 1$。那么 $F(S)$ 就是每个连通块的方案数乘起来。

快速求解这个 $F$，于是设 $f_{u,i}$ 表示以 $u$ 为根的子树内，$u$ 所在的连通块大小为 $i$ 对答案的贡献（不算 $u$ 的连通块的贡献，带上容斥系数）。转移枚举 $u$ 的儿子 $v$ 和他们的连通块大小，分两种：

- $f_{u,i+j} \gets f_{u,i}\times f_{v,j}$ 表示不把 $u,v$ 分成两个连通块，而是合并起来。
- $f_{u,i} \gets f_{u,i} \times f_{v,j} \times (-sum_j)$ 表示把 $u,v$ 分成两个连通块，这时不被覆盖的边就会增加一条，容斥系数 $\times (-1)$，同时会让当前的 $F(S)$ 乘上新增的连通块的方案数 $sum_j$，故转移时要 $\times (-sum_j)$。

最后的答案便是 $\sum\limits_{i=1}^{n}f_{1,i}\times sum_i$，把自己所在的连通块的贡献乘上（因为状态的定义是不算自己的）。

关于时间复杂度：虽然在转移时要枚举一层 $sz_u$ 还要枚举一层 $sz_v$，但是每次都是先转移再累加 $sz_v$，也就是从 $v$ 的子树中选点和 $v$ 旁边的子树选点进行匹配。每一对选出的点都只会在他们的 lca 处被计算一次，故总的复杂度是 $O(n^2)$。  

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=5e3+5,mod=1e9+7;
int n,sz[N];
ll f[N][N],sum[N],tmp[N];
vector<int>e[N];
void dfs(int u,int fa){
	sz[u]=1;
	f[u][1]=1;
	for(auto v:e[u]){
		if(v==fa)continue;
		dfs(v,u);
		for(int i=1;i<=sz[u]+sz[v];++i)tmp[i]=0;
		for(int i=1;i<=sz[u];++i){
			for(int j=1;j<=sz[v];++j){
				tmp[i]=(tmp[i]+mod-f[u][i]*f[v][j]%mod*sum[j]%mod)%mod;
				tmp[i+j]=(tmp[i+j]+f[u][i]*f[v][j]%mod)%mod;
			}
		}
		for(int i=1;i<=sz[u]+sz[v];++i)f[u][i]=tmp[i];
		sz[u]+=sz[v];
	}
}
int main(){
	cin>>n;
	for(int i=1;i<n;++i){
		int a,b;
		cin>>a>>b;
		e[a].pb(b);
		e[b].pb(a);
	}
	sum[0]=1;
	for(int i=2;i<=n;i+=2)sum[i]=sum[i-2]*(i-1)%mod;
	dfs(1,0);
	ll ans=0;
	for(int i=1;i<=n;++i)ans=(ans+f[1][i]*sum[i]%mod)%mod;
	cout<<ans;
}
```


---

## 作者：Gordon_Song (赞：12)

直接进行 dp 是简单的，但是复杂度达到了不可接受的 $O(n^3)$。具体就是设 $dp_{i,j}$　表示以 $i$ 为根的子树内，还剩 $j$ 个点没有匹配的方案数。子树之间合并的转移过于复杂，貌似不可以直接优化。

考虑容斥，强制钦定其中若干条边断开（即这条边一定不染色，从而把整棵树分成若干个联通块），其它边没有限制的匹配数。

首先思考如何在知道断掉边的集合时求出对应的方案数。设 $f_i$ 表示联通块大小为 $i$ 时， 块内点两两匹配的方案数，那么可以得出 $f_i$ 简单的递推形式 $f_i = 1 \times 3 \times \dots (i-1)$（需要保证 $i$ 为偶数）。所以如果固定了断掉的边的集合 $E$，分成的 $|E|+1$ 个联通块大小集合是 $S$，那么方案数就是 $(-1)^{|E|+1}\prod_{x \in S} f_x$，还可以把 $-1$ 乘进去方便后面的计算。


解决了上面的问题后，就把原问题转化为：一个大小为 $x$ 的联通块权值为 $-f_x$，现在要把一棵树划分成若干个联通块，定义一种划分的价值为所有联通块的权值的乘积。求所有划分的价值之和。

这个问题可以用树形 dp 解决。设 $f_{i,j}$ 表示以 $i$ 为根的子树内，与 $i$ 联通的联通块大小为 $j$ 的价值之和（不把当前与 $i$ 的联通块算在内，否则难以转移）。

转移是显然的。 
1. $f_{x,j} \times -f_j \times f_{father_x,k} \to f_{father_x,k}$（断掉连向父亲的边。）
2. $f_{x,j} \times f_{father_x,k} \to f_{father_x,j+k}$（不断，把两个联通块合并。）

---

## 作者：Kinandra (赞：10)

标签: 容斥, 树形DP.

#### Part 1

设 $F(S)(S\subseteq E)$ 表示集合内 $S$ 集合内的边没有被染色的方案数, $g(i)$ 表示 $i$ 个点任意配对的方案数. 

显然 $g(i)$ 在 $i$ 为奇数时为 $0$ , 否则 $g(i)=\prod_{i=1}^{\frac i2}(2i-1)$ , 这个公式很好推: 每次选出为匹配标号最小的点, 任选另一个点匹配即可.

$F(S)$ 也很好计算, 显然 $S$ 将原树分割成了若干个连通块, 我们只要把联通块大小对应的 $g$ 值相乘就可以得到了.

经过简单的容斥后可以得到 $ans=\sum_{S\subseteq E}(-1)^{|S|}F(S)$ , 后文中的方案数均指带上容斥系数的方案数.

#### Part 2

接下来考虑树形 DP .

设 $f(i,j)$ 表示在子树 $i$ 内有 $j$ 个点与 $i$ 在同一个连通块的子树内匹配的方案数, 特别的, 令 $f(i,0)$ 表示子树 $i$ 的点全部匹配的方案数.

$f(i,j)(j\neq0)$ 用经典的树形DP即可计算, $f(i,0)$ 也可以通过定义计算: $f(i,0)=-\sum_jf(i,j)\times g(j)$ , 这里要带上 `-` 号是因为 $i$ 到父亲的边没有被覆盖, 使得 $|S|$ 增加 $1$ , 注意当 $i$ 为根节点时不存在这条边, 故不需要带 `-` 号.

时间复杂度 $\mathcal O(n^2)$.

```cpp
#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int read();

vector<int> e[5003];
void add(int f, int t) { e[f].push_back(t), e[t].push_back(f); }
int f[5003][5003], g[5003], tmp[5003];
int n, sz[5003];

void dfs(int u, int fa) {
    f[u][sz[u] = 1] = 1;
    for (int i = 0, v; i < e[u].size(); ++i) {
        if ((v = e[u][i]) == fa) continue;
        dfs(v, u);
        for (int i = 1; i <= sz[u] + sz[v]; ++i) tmp[i] = 0;
        for (int i = 1; i <= sz[u]; ++i)
            for (int j = 0; j <= sz[v]; ++j)
                (tmp[i + j] += 1ll * f[u][i] * f[v][j] % mod) %= mod;
        for (int i = 1; i <= sz[u] + sz[v]; ++i) f[u][i] = tmp[i];
        sz[u] += sz[v];
    }
    for (int i = 2; i <= sz[u]; i += 2)
        (f[u][0] += mod - 1ll * f[u][i] * g[i] % mod) %= mod;
}

int main() {
    g[0] = 1, n = read();
    for (int i = 2; i <= n; i += 2) g[i] = 1ll * g[i - 2] * (i - 1) % mod;
    for (int i = 1; i < n; ++i) add(read(), read());
    dfs(1, 0);
    printf("%d\n", mod - f[1][0]);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```

---

## 作者：Nightingale_OI (赞：6)

## 思路

提供一种不同的思路。不保证比主流思路好写。

设 $f_{x,i}$ 表示 $x$ 的子树内还有 $i$ 个点要向上匹配的方案数。

合并转移的时候枚举 $x$ 的儿子 $y$、$x$ 子树内点数 $i$，$y$ 子树内点数 $j$，匹配的对数 $k$，转移为：

$$
f_{x,i}\binom{i}{k}f_{y,j}\binom{j}{k}k!\to f'_{x,i+j-2k}
$$

当 $x$ 子树内所有转移结束后，如果 $x$ 是根，则答案为 $f_{x,0}$，否则我们须令 $f_{x,0}=0$。

上述的 DP 应该是大家都能想到的。复杂度 $O(n^3)$，瓶颈在转移。

---

大家都说这没有优化空间。~~听不懂，我玩维什戴尔的。~~ 但事实上可以强行优化。

$n$ 个点里选 $k$ 对点，点对内无序，点对间无序。方案数可以写成 $\frac{n!}{(n-2k)!k!2^k}$。

形式化地来说，我们有 $f_{0\sim n},g_{0\sim m}$，需要求出 $h_{0\sim n+m}$ 满足：

$$
h_p=\sum_{i+j=p}\sum_{k=0}^{\min(n-i,m-j)}f_{i+k}\binom{i+k}{k}g_{j+k}\binom{j+k}{k}k!
$$

考虑对**不合法的点对**数进行容斥。

先直接将 $f,g$ 卷起来得到 $h$，然后枚举选了 $k$ 对，即：

$$
h'_x=\sum\limits_{i+j=x}f_ig_j\\
h_x=\sum\limits_{k=0}^{\lfloor\frac{n+m-x}2\rfloor}\frac{(x+2k)!}{x!k!2^k}h'_{x+2k}
$$

这样 $h_x$ 会统计到一些不合法的情况，我们直接枚举 $f$ 中至少有 $p$ 对点不合法，$g$ 中至少有 $q$ 对点不合法。每对不合法的有 $-1$ 的系数。正确的转移如下：

$$
h_x=\sum\limits_{k=0}^{\lfloor\frac{n+m-x}2\rfloor}\frac{(x+2k)!}{x!k!2^k}\sum_{i+j=x}(\sum_{p=0}^{\lfloor\frac{n-i}2\rfloor}\frac{(i+2p)!}{i!p!2^p}(-1)^pf_{i+2p})(\sum_{q=0}^{\lfloor\frac{m-j}2\rfloor}\frac{(j+2q)!}{j!q!2^q}(-1)^qg_{j+2q})
$$

枚举这么多当然是不好的。但是我们 $f,g$ 的贡献是独立的。

定义 Temporary Talent Transformation（TTT），对于给定的 $f_{0\sim n}$，将其变换为：

$$
f'_{i}=\sum_{k=0}^{\lfloor\frac{n-i}2\rfloor}\frac{(i+2k)!}{i!k!2^k}(-1)^kf_{i+2k}
$$

同时定义 TTT 的逆变换 ITTT，对于给定的 $f'_{0\sim n}$，将其变换为：

$$
f_{i}=\sum_{k=0}^{\lfloor\frac{n-i}2\rfloor}\frac{(i+2k)!}{i!k!2^k}f'_{i+2k}
$$

用组合意义不难证明一个序列先 TTT 再 ITTT 后不变。

将 $f_{0\sim n},g_{0\sim m}$ 分别进行 TTT 后乘起来（卷积），最后 ITTT 一下，得到的就是 $h_{0\sim n+m}$。

单次复杂度是 $O((n+m)^2)$，放到原问题大致是子树大小平方和（$O(n^3)$）。

经典套路，我们对所有东西先都 TTT 一次，全部乘起来，最后 ITTT，就可以了——吗？

注意到我们有 $f_{x,0}\leftarrow 0$ 的赋值操作。需要特殊处理。这是好办的。$f_{x,0}$ 的修改只会影响 $f'_{x,0}$。已知 ITTT 后的 $f'_{x,i}$ 可以 $O(n)$ 把 $f_{x,0}$ 算出来，然后令 $f'_{x,0}-=f_{x,0}$ 即可。这一步是 $O(n^2)$ 的。

卷积的复杂度是树形背包，总复杂度 $O(n^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int N=5555,mo=1e9+7;
inline void Add(int&x,int y){x=(x+y)%mo;}
inline int ksm(int x,int p=mo-2,int y=1){for(;p;p/=2,x=x*x%mo)if(p&1)y=x*y%mo;return y;}
int jc[N],ny[N],o[N][2];
inline int C(int n,int m){return(n<m||m<0)?0:jc[n]*ny[m]%mo*ny[n-m]%mo;}
inline int D(int n,int m,int t){return(n<m+m||m<0)?0:jc[n]*ny[m]%mo*ny[n-m-m]%mo*o[m][t]%mo;}
inline void ycl(int n){
	f(i,0,n)f(t,0,1)o[i][t]=ksm(ksm(t?2:mo-2,i));
	jc[0]=1;
	f(i,1,n)jc[i]=jc[i-1]*i%mo;
	ny[n]=ksm(jc[n]);
	g(i,n,1)ny[i-1]=ny[i]*i%mo;
}
vector<int>q[N];
int f[N][N],c[N],h[N];
inline void TTT(int*f,int n,int t){f(i,0,n)f(k,1,i/2)Add(f[i-k-k],f[i]*D(i,k,t));}
inline void kil(int*f,int n){
	f(i,0,n/2)Add(f[0],mo-f[i*2]*D(i*2,i,1)%mo);
	// TTT(f,n,1);f[0]=0;TTT(f,n,0);
}
inline void mul(int*f,int&n,int*g,int&m){
	f(i,0,n)f(j,0,m)Add(h[i+j],f[i]*g[j]);n+=m;
	f(i,0,n)f[i]=h[i],h[i]=0;
}
void dfs(int x,int fa){
	f[x][1]=c[x]=1;
	for(int y:q[x])if(y!=fa){
		dfs(y,x);
		mul(f[x],c[x],f[y],c[y]);
	}
	if(fa)kil(f[x],c[x]);
}
signed main(){
	cin>>n;ycl(n);
	f(i,2,n){
		cin>>s>>l;
		q[s].push_back(l);
		q[l].push_back(s); 
	}
	dfs(1,0);TTT(f[1],n,1);cout<<f[1][0];
	return 0;
}
```

---

## 作者：bai_tang (赞：5)

只要有信念，就一定能成功！

### [题意](https://www.luogu.com.cn/problem/AT4352)
给定一棵 $n$ 个节点的树，你要给节点两两配对，满足配对之后的路径覆盖整树，$n\le 5000$。

### 分析
利用组合数学可以算出总方案是 $\prod_{i=1}^{n/2}(2i-1)$ 的非常巨大，考虑用容斥原理转化一下，钦定哪个集合的边不存在来容斥，可以得到 $O(2^nn)$ 复杂度的方法，[代码](https://www.luogu.com.cn/paste/zslk83za)。

为了方便，我们设定函数 $\gamma(n)$ 满足:
$$\gamma(n)=-\prod_{i=0}^{\lfloor n/2\rfloor}(n-2i-1)$$

那么形式化表述，就是对于任何一种断边方案 $S$，形成的极大连通块大小 $c_{1},c_2,\cdots ,c_m$，都对答案有贡献（显然最后答案需要取负）：
$$\prod_{i=1}^m\gamma(c_i)$$
我们知道著名的乘法分配律满足：
$$(\sum_{i}a_i)(\sum_{j}b_j)=\sum_{i,j}a_ib_j$$

设 $f(u,i)$ 表示考虑子树 $u$ 的，不考虑包含 $u$ 的某个大小为 $i$ 的连通块，其它部分的贡献之和，那么容易发现，在子树贡献时：
$$f(v,i)f(u,j)\to f(u,i+j)$$
而在子树贡献完成时，还有：
$$f(u,0)=\sum_{i=1}f(u,i)\gamma(i)$$
而直接暴力这样做，根据经典的树上背包的结论，复杂度即为 $O(n^2)$，[代码](https://www.luogu.com.cn/paste/gn7xfwjm)。

---

## 作者：Masterwei (赞：5)

$O(n^3)$ 的做法很简单，直接设 $f_{u,i}$ 表示在 $u$ 点，有 $i$ 个点要向上匹配的方案数，转移好写。

但是上述做法的转移不好优化，所以考虑换做法。

题目要求的是边被覆盖的方案数，于是我们尝试算出钦定至少有几条边没被覆盖的方案数后容斥。

设 $f_{u,i}$ 表示在 $u$ 点，包含 $u$ 的联通块大小为 $i$ 的方案数。转移分为两种：

$u,y$ 之间的边要选：$f_{u,i}\times f_{y,j}\to f_{u,i+j}$。

不选：$f_{u,i}\times f_{y,j} \times -g_j$。其中 $g_j$ 表示大小为 $j$ 的联通块的覆盖方案数。

然后自己手玩一下，推一下，得到 $g_i=g_{i-2}\times (i-1)$。

然后就做完了。

[代码](https://atcoder.jp/contests/arc101/submissions/60885636)。

---

## 作者：Rubyonly (赞：4)

首先可以很容易想到一个 $\mathcal{O}(n^3)$ 的 $dp$，在子树归并的同时枚举这次匹配的点对数，然后转移

发现这个 $dp$ 不太好进行优化，考虑换一个思路去做

题目中要求的是恰好所有边都被经过，即恰好有 $0$ 条边不被经过，不妨考虑子集反演，钦定集合 $S\in E$，$F(S)$ 表示集合 $S$ 中的边都不被经过的方案数，那我们最后要求的答案就变成了

$$\sum(-1)^{|S|}F(S)$$

考虑如何求 $F(S)$，我们将这些边都断掉，会形成 $|S|-1$ 个联通块，因为定义中并没有钦定剩下的边一定被经过，所以直接在同一个联通块里随便选两个点连就行了，要求的就是是这 $|S|-1$ 个联通块中，每个联通块里的每两个点匹配且要完全匹配的方案数，显然这 $|S|-1$ 个联通块是独立的，可以分开求

定义 $g(n)$ 表示一个联通块里有 $n$ 个点，两两随便匹配的方案数，因为点对是无序的，点对与点对之间也是无序的，所以我们直接钦定它有序，对每个点选个点匹配就行，直接可以得出式子

$$g(n)=[n\equiv 0\pmod2](n-1)(n-3)......3\times 1$$

所以对于一个 $F(S)$，其实就是它分成的若干个联通块的 $g(n)$ 乘起来

接下来我们可以考虑继续在树上 $dp$ 来解决这个问题

定义 $f[i][j]$ 表示以 $i$ 为根的子树，$i$ 所在的联通块大小为 $j$ 的方案数

然后子树归并，转移是决策 $u$ 所在的联通块是否与 $v$ 所在的联通块合并就行了

特别的，根据定义和转移，我们发现 $f[i][0]$ 其实就是不与上面的联通块合并，即断掉了 $fa[i]$ 与 $i$ 之间的边，因为断边集合 $S$ 大小增加了 $1$，需要乘上个 $-1$，而且现在一个联通块考虑完了，同时在乘上一个 $g(j)$ 即可，即

$$f[u][0]=-1\times \sum_{j=1}^{size[u]}f[u][j]\times g(j)$$

最后特殊考虑一下根节点，因为它没有 $fa$，所以无边可断，不需要乘 $-1$，最后答案即为 $-1\times f[1][0]$

因为只剩下了子树归并，所以复杂度是 $\mathcal{O}(n^2)$ 的


$\mathcal{Code}$

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

using namespace std;

const int maxn = 5e3 + 50, INF = 0x3f3f3f3f, mod = 1e9 + 7;

inline int read () {
	register int x = 0, w = 1;
	register char ch = getchar ();
	for (; ch < '0' || ch > '9'; ch = getchar ()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar ()) x = x * 10 + ch - '0';
	return x * w;
}

inline int addmod (register int a, register int b) {
	return a += b, a >= mod ? a - mod : a;
}

inline ll mulmod (register ll a, register int b) {
	return a *= b, a >= mod ? a % mod : a;
}

int n;

struct Edge {
	int to, next;
} e[maxn << 1];

int tot, head[maxn];

inline void Add (register int u, register int v) {
	e[++ tot].to = v;
	e[tot].next = head[u];
	head[u] = tot;
}

int siz[maxn], f[maxn][maxn], g[maxn], p[maxn];

inline void Init () {
	g[0] = 1;
	for (register int i = 2; i <= n; i += 2) 
		g[i] = mulmod (g[i - 2], i - 1);
}

inline void DFS (register int u, register int fa) {
	siz[u] = 1, f[u][1] = 1;
	for (register int i = head[u]; i; i = e[i].next) {
		register int v = e[i].to;
		if (v == fa) continue;
		DFS (v, u);
		for (register int j = 1; j <= siz[u] + siz[v]; j ++) p[j] = 0;
		for (register int j = 1; j <= siz[u]; j ++) 
			for (register int k = 0; k <= siz[v]; k ++) 
				p[j + k] = addmod (p[j + k], mulmod (f[u][j], f[v][k]));
		for (register int j = 1; j <= siz[u] + siz[v]; j ++) f[u][j] = p[j];
		siz[u] += siz[v];
	}
	for (register int j = 1; j <= siz[u]; j ++) 
		f[u][0] = addmod (f[u][0], mulmod (f[u][j], g[j]));
	f[u][0] = mod - f[u][0];
}

int main () {
	n = read(), Init ();
	for (register int i = 1, u, v; i < n; i ++)
		u = read(), v = read(), Add (u, v), Add (v, u);
	DFS (1, 0), printf ("%d\n", mod - f[1][0]);
	return 0;
}
```

---

## 作者：Thaumaturge (赞：4)

简单地考虑一个子集容斥：若在一个覆盖方案中，钦定有 $i$ 条边没有被覆盖到，则它的贡献系数将会为 $(-1)^i$ 。

然后，记录 $f_{i,j,k}$ 表示 $dp$ 到了子树 $i$ ，当前联通块大小为 $j$ ，切掉了 $k$ 条边，背包转移即可。

注意到容斥系数这一维可以每次乘以一个 $-1$ 转移，所以 $dp$ 的状态就只用记 $i,j$ 就好了。这是个树上背包，复杂度 $O(n^2)$ 。

---

## 作者：ty_mxzhn (赞：3)

容斥。假设有 $p$ 条边未被覆盖则容斥系数为 $(-1)^p$。

假设一个大小为 $x$ 联通块随意匹配，则方案数为 $(x-1)!!$。不过要求 $x$ 是偶数。

考虑树上动态规划解决。定义 $F_{i,j}$ 表示 $i$ 子树内，$i$ 所在的联通块大小为 $j$，暂时不算 $i$ 这个联通块内的贡献的答案。

转移时，联通块加入一个子树则对其做一个卷积形式。否则断掉一条通向儿子的边，需要乘上 $-1$。

时间复杂度和树上背包一样，为 $O(n^2)$。

---

## 作者：keywet06 (赞：3)

### [Hexo博客食用更香awa](https://keywet06.blog.wekw.cf/post/solutionARC101C/)

### 题目大意

- 选择 $\frac{n}{2}$ 对点，要求每条边必被至少一个点对的树上路径经过

### 思路

#### 转化模型

- 根据容斥原理，答案为：**强制选择若干条不被路径经过**的方案乘容斥系数求和。

- 将这些边删去，将整棵树分为若干连通块，方案即为每个连通块任意匹配的方案数乘积。

- 而 $2N$ 个点自由匹配的方案数为 $f(2N) = (2N - 1)!!$。

- 设 $dp_{x, s}$ 为 $x$ 子树中，$x$ 所在连通块大小为 $s$ 时的所有方案的权值和。

#### $dp$ 转移

- 初始 $dp_{x, 1} = 1$ ，对 $x$ 所有儿子 $c$ ， $dp_{x, i + j}' \leftarrow dp_{x, i} \times dp_{c, j}$ （即做一次多项式乘法）；

- 将 x 与父亲的边切断， $dp_{x, 0} \leftarrow -(2i - 1)!! \times dp_{x, 2i}$ 。

答案即为 $-dp_{root, 0}$。

### 代码

```cpp
#include <bits/stdc++.h>
const int N = 5005;
const long long mod = 1000000007;
int n, x, y;
int size[N];
long long tmp[N], df[N];
long long f[N][N];
std::vector<int> to[N];
inline void dfs(int u, int fa) {
    f[u][1] = 1;
    size[u] = 1;
    for (auto v: to[u]) {
        if (v == fa) continue;
        dfs(v, u);
        for (int i = 0; i <= size[u]; ++i) tmp[i] = f[u][i], f[u][i] = 0;
        for (int i = 0; i <= size[u]; ++i) {
            for (int j = 0; j <= size[v]; ++j) {
                f[u][i + j] += tmp[i] * f[v][j] % mod;
            }
        }
        size[u] += size[v];
        for (int i = 0; i <= size[u]; ++i) ((f[u][i] %= mod) += mod) %= mod;
    }
    for (int i = 2; i <= size[u]; i += 2) f[u][0] += -df[i - 1] * f[u][i] % mod;
    ((f[u][0] %= mod) += mod) %= mod;
}
int main() {
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    df[0] = df[1] = 1;
    for (int i = 2; i <= n; ++i) df[i] = df[i - 2] * i % mod;
    dfs(1, 1);
    std::cout << mod - f[1][0] << std::endl;
    return 0;
}
```

---

## 作者：Lyrella (赞：2)

# 前言

此片题解大致按照笔者做题思路进行讲解。

# 简要题意

有一棵树，树上有偶数个节点。你需要给这些点两两配对，一组已经配对的点会将两点之间的树边进行一次覆盖。一组合法方案需要满足树上所有边都被覆盖至少一次，求合法方案数。

**数据范围**：$n\le5000$。

# 思路

首先我们去观察题目性质，~~发现没有什么特殊的地方~~。我最开始只想到一个非常暴力的 $dp$，设 $f_{u,i}$ 表示以 $u$ 为根的子树内有 $i$ 个点已经匹配好的方案数。但是当我去考虑转移时，我发现他有很多种情况：

1. $u$ 一个儿子的子树内互相匹配，但是需要有一个点与外面的点匹配（不然这个子树与 $u$ 之间的边就无法被覆盖）；
2. 一个子树内的点向 $u$ 的其他子树匹配；
3. 一个子树的点向 $u$ 子树以外的点匹配。

或许还有一些没有罗列出来，但反正就是不可做。于是我们正难则反，考虑先求出不合法的情况，然后容斥做。

# 题解

如何求不合法的情况呢？我们可以通过钦定一些边不覆盖来容斥。比如当我计算到以 $u$ 为根的子树时，我就去枚举 $u$ 所在的连通块的大小，对于一个 $u$ 的儿子 $v$，分讨一下连通块是否包括 $v$。

具体的，我们设 $f_{u,i}$ 表示以 $u$ 为根的子树，$u$ 所在连通块大小为 $i$ 的方案数。对于 $v$ 在连通块的时候，有转移：
$$
f_{u,i-j}\times f_{v,j}\rightarrow f_{u,i},v\in{\operatorname{son}_u,j<i}
$$
若 $v$ 与 $u$ 之间的边不覆盖，则有：
$$
f_{u,i}\times f_{v,j}\rightarrow f_{u,i+j}
$$
你乍一看这不就是树上背包吗？时间复杂度 $O(n^2)$，可以通过此题！

现在我们已经基本找出状态转移的方程，但现在我们还需要思考一个问题：

> 一个点数为 $k$ 的连通块，将里面的点不重不漏两两匹配的方案数

首先对于 $k$ 为奇数的时候是无贡献的；所以只用考虑 $k$ 为偶数的情况。考虑递推求解答案，设 $s_k$ 表示点数为 $k$ 的贡献。对于一个点，我有 $k - 1$ 种选择方案，而剩下的 $k-2$ 个点的方案是 $s_{k-2}$，固可得递推式：$s_{k}=(k-1)\times s_{k-2}$。

但考虑到我们只是没有考虑这些方案中会有的不合法情况，所以需要稍微容斥一下，在转移的时候还需要给一个 $(-1)^k$。

然后看到之前的 $dp$，我们发现对于第一种情况合并两个连通块似乎不好计算方案，于是我们改写状态，设 $f_{u,i}$ 表示以 $u$ 为根的子树，$u$ 所在连通块大小为 $i$ 时不考虑 $u$ 所在连通块中匹配情况的方案数，这样在合并两个连通块时我们就直接把系数乘上就行，所以最后第一种情况的转移式为：
$$
f_{u,i}\leftarrow f_{u,i-j}\times f_{v,j}\times(-s_i)
$$
最后答案就是 $\sum\limits_{i}f_{1, i}\times s_i$。

# 代码

```cpp
void dfs(int u, int fa){
    sz[u] = f[u][1] = 1;
    for(int i = hd[u]; i; i = e[i].nxt){
        int v = e[i].to; if(v == fa)continue;
        dfs(v, u); copy(f[u], f[u] + 1 + sz[u], g);
        fill(f[u], f[u] + 1 + sz[u], 0);
        for(int j = 1; j <= sz[u]; ++j)for(int k = 1; k <= sz[v]; ++k)
            f[u][j] = del(f[u][j], mul(mul(f[v][k], s[k]), g[j])),
            f[u][j + k] = add(f[u][j + k], mul(g[j], f[v][k]));
        sz[u] += sz[v];
    }
}
```

---

## 作者：Hanx16Kira (赞：2)

# [ARC101E] Ribbons on Tree

[Luogu ARC101E](https://www.luogu.com.cn/problem/AT_arc101_c)

## Solution

直接 DP 做是 $\mathcal O(n^3)$ 的，所以考虑容斥。

考虑不合法的方案数。如果一条边没有被任何配对点覆盖，那么就将这条边删除。对于一个大小为 $2k$ 不一定连通的块，总共的方案数为 $g(k)=\displaystyle\prod\limits_{i=1}^k(2i-1)$。设 $f(i,j)$ 表示在 $i$ 子树中，$i$ 所在连通块的大小为 $j$ 的方案数（带上容斥系数），这明显是一个书上背包的转移方式。考虑枚举当前儿子到 $i$ 的这条边是否被断开，那么有：

- 若断开这条边，那么 $f(i,j)\gets f(i,j)\cdot f(v,k)\cdot (-g(k))$。
- 若不断开这条边，那么 $f(i,j+k)\gets f(i,j)\cdot f(v,k)$。

对于答案，考虑枚举根节点所在连通块的大小，得到答案为 $\displaystyle\sum\limits_{i=1}^nf(1,i)\cdot g(i)$。

时间复杂度 $\mathcal O(n^2)$。

```cpp
mint f[_N][_N], g[_N], h[_N];
int N, siz[_N];
vector<int> e[_N];
void init(int n) {
    g[0] = 1;
    For(i, 1, n) g[i*2] = g[i*2-2] * (2 * i - 1);
}
void dfs(int x, int fa) {
    siz[x] = 1, f[x][1] = 1;
    for (int v: e[x]) if (v ^ fa) {
        dfs(v, x);
        For(i, 1, siz[x]) h[i] = f[x][i], f[x][i] = 0;
        Rof(i, siz[x], 1) Rof(j, siz[v], 1) {
            f[x][i] -= h[i] * f[v][j] * g[j];
            f[x][i+j] += h[i] * f[v][j];
        }
        siz[x] += siz[v];
    }
}
void _() {
    cin >> N;
    For(i, 2, N) {
        int x, y; cin >> x >> y;
        e[x].epb(y), e[y].epb(x);
    }
    init(N / 2), dfs(1, 0);
    mint ans = 0;
    For(i, 1, N) ans += f[1][i] * g[i];
    fmtout("{}\n", ans.val());
}
```

---

## 作者：封禁用户 (赞：1)

> 我说他语文是渣，没说他数学称霸。——容斥

题目要求将所有点两两配对，使得配对的点之间的路径覆盖所有树边的总方案数。由于配对点之间路径可能**重叠**，导致不好计算总数。所以考虑容斥。

设有一边集 $S$，记 $f_S$ 为将所有点配对后路径覆盖不包括边集里的所有边的方案数。注意条件**只有**边集内所有边不被覆盖，**没有**说除边集外的所有边均被覆盖。与条件等价的命题是，将边集内的所有边删除，树的剩余连通块之间进行两两配对的方案数。

一个大小为**奇数**的连通块不存在两两配对的方案数。一个大小为**偶数** $k$ 的连通块中点两两配对的方案数（记为 $g_k$）为：

$$\prod_{i=1}^{\frac{k}{2}}(2i-1)$$

而 $f_S$ 即为删除 $S$ 中所有边之后所有连通块配对方案数之积。

根据容斥原理，答案即为：

$$\sum_{S}(-1)^{|S|}f_S$$

我们从树上动态规划的角度入手。设树以 $1$ 为根，$d_{i,j}$ 表示在以 $i$ 为根的子树内的所有包含 $i$ 的大小为 $j$ 的块，不考虑这个块时其他的 $\sum\limits_{S}(-1)^Sf_S$ 之和。特别地，如果 $j=0$，说明 $i$ 与 $i$ 的父亲之间的边被删除，点 $i$ 计入答案内。

初始边界 $d_{i,j}=[j=1]$。在已求包括前面的儿子的子树的贡献时，我们要把下一个儿子 $s$ 的贡献合并到 $j>0$ 的情况。转移方程很显然：$d_{i,j}^{'}=\sum\limits_{k}d_{i,j-k}d_{s,k}$。

在统计完所有儿子的贡献之后，我们要计算删除 $i$ 与 $i$ 父亲之间的边的贡献。参考上面的答案式，可以得到此时 $d_{i,0}=\sum\limits_{2|j}(-g_jd_{i,j})$。

由于我们在处理 $1$ 的贡献时多删了一条边，所以对应 $|S|$ 要减 $1$，答案 $d_{1,0}$ 要乘 $-1$。完结撒花。

## 有关时间复杂度的严重问题

如果你转移每个儿子时是过去式转移的：

```
size[i]+=size[s]
for j reverse in [1,size[i]]:
    d[i][j]=d[i][j]*d[s][0]
    for k in [1,min(size[s],j)]:
        d[i][j]+=d[i][j-k]*d[s][k]
```

那么恭喜你，喜提 $O(n^3)$ 的炸裂时间复杂度。

但是如果你使用未来式转移：

```
for j reverse in [1,size[i]]:
    for k in [1,size[s]]:
        d[i][j+k]+=d[i][j]*d[s][k]
    d[i][j]=d[i][j]*d[s][0]
size[i]+=size[s]
```

那么恭喜你，时间复杂度 $O(n^2)$ 通过此题。

对时间复杂度问题有兴趣的人可以自行研究一下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,gene[5005],amt[5005],dp[5005][5005];
vector<int>mp[5005];
const int modp=1000000007;

void dfs(int now,int fa){
	amt[now]=1;dp[now][1]=1;
	for(int o=0;o<mp[now].size();o++){
		if(mp[now][o]==fa)continue;
		dfs(mp[now][o],now);
		for(int j=amt[now];j>=0;j--){
			for(int k=1;k<=amt[mp[now][o]];k++){
				dp[now][j+k]=(dp[now][j+k]+dp[now][j]*dp[mp[now][o]][k]%modp)%modp;
			}
			dp[now][j]=dp[now][j]*dp[mp[now][o]][0]%modp;
		}
		amt[now]+=amt[mp[now][o]];
	}
	for(int j=2;j<=amt[now];j+=2){
		dp[now][0]=(modp+dp[now][0]-dp[now][j]*gene[j]%modp)%modp;
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int a,b;cin>>a>>b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	gene[0]=1;
	for(int i=2;i<=n;i+=2){
		gene[i]=gene[i-2]*(i-1)%modp;
	}
	dfs(1,1);cout<<(modp-dp[1][0])%modp;return 0;
}
```

---

## 作者：xht (赞：0)

> [ARC101E Ribbons on Tree](https://atcoder.jp/contests/arc101/tasks/arc101_c)

## 题意

- 给定一棵 $n$ 个点的树，保证 $n$ 为偶数。
- 将 $n$ 个点分成 $\frac n2$ 个无序点对。
- 对于每个点对，将树上两点之间的最短路径上的边染色。
- 问有多少种方案使得每条边都被染色。
- $n \le 5 \times 10^3$，答案对 $10^9+7$ 取模。

## 题解

考虑容斥，设 $f(S)$ 表示强制不覆盖边集 $S$ 中的边的方案数，则答案为 $\sum_{S \subseteq E} (-1)^{|S|} f(S)$。

考虑 $f(S)$ 如何计算，设 $S$ 中的边割掉后将树分成了大小为 $a_{1},a_2,\cdots,a_t$ 这 $t$ 个连通块，则 $f(S) = \prod_{t=1}^t \left[2 | a_i\right]\left(a_i-1\right)!!$，其中 $x!!$ 表示 $x(x-2)(x-4)\cdots$。

考虑树形 DP，设 $f_{i,j}$ 表示考虑 $i$ 的子树，割掉若干条边后 $i$ 所在的连通块大小为 $j$，不包含 $i$ 所在的连通块的贡献总和。

转移就是树上背包，时间复杂度 $\mathcal O(n^2)$。

## 代码

```cpp
const int N = 5e3 + 7;
int n, s[N];
vi e[N];
modint p[N], f[N][N], ans;

void dfs(int x, int fa) {
	f[x][1] = s[x] = 1;
	for (int y : e[x])
		if (y != fa) {
			dfs(y, x);
			for (int i = s[x]; i; i--) {
				modint w = 0;
				for (int j = s[y]; j; j--)
					f[x][i+j] += f[x][i] * f[y][j], w -= p[j] * f[y][j];
				f[x][i] *= w;
			}
			s[x] += s[y];
		}
}

int main() {
	rd(n);
	p[2] = 1;
	for (int i = 4; i <= n; i += 2) p[i] = p[i-2] * (i - 1);
	for (int i = 1, x, y; i < n; i++) rd(x, y), e[x].pb(y), e[y].pb(x);
	dfs(1, 0);
	for (int i = 1; i <= n; i++) ans += p[i] * f[1][i];
	print(ans);
	return 0;
}
```

---

## 作者：phil071128 (赞：0)

### [ARC101E] Ribbons on Tree

> 给定大小为 $n$ 的树，给树上的点两两配对，对于每一组配对 $(u,v)$ 将其路径上的边全部覆盖，定义一个配对方案合法，当且仅当每一条边都被覆盖。$n\le 5000$ 且是偶数。

套路的，有 $O(n^3)$ 的 DP：

设 $f_{u,i}$ 表示 $u$ 为根的子树内有 $i$ 个点未匹配的方案数，转移有 $f_{u,i}\times f_{v,j}\times \binom{i}{k}\binom{j}{k}k!\to f_{u,i+j-2k}$ 。根据题目要求的合法条件，其实就等价于每个子树都留至少一个未配对的，才能保证 $(u,v)$ 都被覆盖，因此有 $i,j\ge 1$。

这样没有优化的空间了，考虑子集反演，设 $F(S)$ 表示至少 $S$ 边集是被断开的。
$$
ans=\sum_{T\sub E}(-1)^{|T|} F(S)
$$

断边相关，转换为连通块大小设计。设 $f_{u,i}$ 表示以 $u$ 为根的子树，$u$ 的连通块大小是 $i$，**且根所在连通块未考虑匹配**，考虑这条边是否被强制断掉：

- 强制断掉：$f_{u,i}\times f_{v,j}\times g_{j}\times (-1)\to f_{u,i}$；
- 不强制：$f_{u,i}\times f_{v,j}\to f_{u,i+j}$。

其中 $g_j$ 表示大小为 $j$ 的集合两两配对的方案数，即双阶乘 $(2j-1)!!=1\times 3\times 5\times \cdots \times (2j-1)$。

容斥系数存在的原因是每次会将 $|T|$ 的大小增加 $1$。

最终答案即为 $\sum f(1,j)\times g(j)$。

行不通的时候适当考虑容斥？很多题目很难有一瞬间的容斥感觉呀，本题中容斥的作用是：将限制变宽松。但实际上并没有减少状态的维度。更常见的一类指数级容斥是直接枚举集合的，例如 [FJOI2017] 矩阵填数，[SHOI2016] 黑暗前的幻想乡。

补充：子集反演证明。

> ### 定理内容
>
> 若
> $$
> g[S]=\sum_{T\sub S} f[T]
> $$
> 则有：
> $$
> f[S]=\sum _{T\sub S}(-1)^{|S|-|T|}g[T]
> $$
>
> ### 证明
>
> 我们可以反演艾佛森括号：
> $$
> \sum_{T\sub S} (-1)^{|T|}=[|S|=0]
> $$
> 等价于二项式反演，因为元素大小为 $|T|$ 的元素有 $\binom{|S|}{|T|}$ 个。
> $$
> f[S]=\sum_{T\sub S}[|S|=|T|] f[T]
> \\
> f[S]=\sum_{T\sub S}\sum _{P\sub S-T}(-1)^{|P|}f[T]
> \\
> f[S]=\sum _{P\sub S}(-1)^{|P|}\sum _{T\sub S-P} f[T]
> \\f[S]=\sum_{P\sub S}(-1)^{|P|}g[S-P]
> \\
> f[S]=\sum_{P\sub S}(-1)^{|S|-|P|}g[P]
> $$

---

## 作者：_Clown_ (赞：0)

编号：$AT4352$
算法：容斥原理、树形 $\mathcal{DP}$

时间复杂度：$\mathcal O(N^2)$

------------

好难的容斥题目啊！

结合了树形 $\mathcal{DP}$ ！

我们来推一下式子...

设 $F_X$ 表示 $X$ 中的边全部未被覆盖的方案数。

由容斥原理：
$$
Ans=\sum_X(-1)^{|X|}\times F_X
$$
考虑一下怎么推出$F_X$。

如果把 $X$ 中所有的边都去掉，那么每次选择加进来的点，都要在一个连通块内。

设剩下的连通块大小分别为$Size_1,Size_2,Size_3...Size_K$

设 $Factorial_i$ 表示 $i$ 个点中两两一组的方案数。

当 $i$ 为奇数时 $Factorial_i=0$

当 $i$ 为偶数时 $Factorial_i=(i-1)!!=(i-1)*(i-3)...*1$

因此：
$$
F_X=\prod Factorial_{Size_i}
$$
那么如何快速地求出 $F_X$。

设 $Dp[Now][i]$ 表示子树 $Now$ 中有 $i$ 个点未匹配的方案数。

简单地转移一下即可，这里就不写了。

------------

```cpp
#include<bits/stdc++.h>
#define MOD 1000000007
#define MAX 5001
using namespace std;
int Total;
int Ans;
vector<int>Edge[MAX];
int Factorial[MAX];
int Dp[MAX][MAX];
int Size[MAX];
inline void Dfs(int Now,int Father)
{
	register int i;
	Size[Now]=1;
	Dp[Now][1]=1;
	for(i=0;i<Edge[Now].size();i++)
	{
		register int Next;
		Next=Edge[Now][i];
		if(Next!=Father)
		{
			Dfs(Next,Now);
			register int Tmp[MAX];
			register int j,k;
			for(j=1;j<=Size[Now]+Size[Next];j++)
			{
				Tmp[j]=0;
			}
			for(j=1;j<=Size[Now];j++)
			{
				for(k=1;k<=Size[Next];k++)
				{
					Tmp[j]=(Tmp[j]-(long long)Dp[Now][j]*Dp[Next][k]%MOD*Factorial[k])%MOD;
					Tmp[j+k]=(Tmp[j+k]+(long long)Dp[Now][j]*Dp[Next][k])%MOD;
				}
			}
			Size[Now]+=Size[Next];
			for(j=1;j<=Size[Now];j++)
			{
				Dp[Now][j]=Tmp[j];
			}
		}
	}
}
int main(void)
{
	register int i;
	cin>>Total;
	for(i=1;i<Total;i++)
	{
		register int U,V;
		cin>>U>>V;
		Edge[U].push_back(V);
		Edge[V].push_back(U);
	}
	Factorial[0]=1;
	for(i=2;i<=Total;i+=2)
	{
		Factorial[i]=(long long)Factorial[i-2]*(i-1)%MOD;
	}
	Dfs(1,0);
	for(i=2;i<=Total;i+=2)
	{
		Ans=(Ans+(long long)Dp[1][i]*Factorial[i])%MOD;
	}
	cout<<(Ans+MOD)%MOD<<endl;
	return 0;
}
```


---

