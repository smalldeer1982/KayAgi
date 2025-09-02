# Khayyam's Royal Decree (Easy Version)

## 题目描述

这是本题的简单版本。两个版本的唯一区别在于 $k$ 和 $\sum k$ 的限制。

Khayyam 有一个**宝箱**，**宝箱**里初始有 $n$ 个红宝石和 $m$ 个蓝宝石。一个红宝石的价值为 $2$，一个蓝宝石的价值为 $1$。他还有一个**背包**，初始为空。另外，他还有 $k$ 张卷轴，第 $i$ 张卷轴上有数对 $(r_i,b_i)$。

Khayyam 将进行一个游戏，游戏共 $n+m$ 轮，每轮流程如下：

1. Khayyam 从**宝箱**中等概率随机拿出一个宝石。
2. 他将这个宝石放入**背包**中。
3. 若存在一张卷轴 $i$，使得**宝箱**中恰有 $r_i$ 个红宝石和 $b_i$ 个蓝宝石，将所有**背包**里的宝石的价值翻倍。

一个宝石的价值可以被多次翻倍。

求游戏结束时 Khayyam **背包**里宝石的价值总和的期望值，对 $998244353$ 取模。

## 样例 #1

### 输入

```
5
3 4 0
1 1 1
1 0
3 3 2
1 1
2 2
3 3 2
2 1
1 2
10 4 5
1 0
8 0
6 4
0 2
7 4```

### 输出

```
10
499122180
798595498
149736666
414854846```

# 题解

## 作者：littlebug (赞：4)

## Solution

开始题意理解错了，硬控 30min，不过那就按照错的来吧，就一个转化，即把「宝箱中有 $r_i,b_i$ 个」转化为「背包中有 $n-r_i,m-b_i$」个，下面的 $r_i,b_i$ 都是已经转化过的。

然后发现可以转化为二维格路计数问题，其中 $(x,y)$ 表示背包中有 $x$ 个红宝石，$y$ 个蓝宝石，从 $(0,0)$ 走到 $(n,m)$，走到关键点会使背包中所有价值 $\times 2$，求期望，其实就是求所有方案的价值之和，再除以总方案数 $\binom {n+m} n$。

为了方便，我们设第 $0$ 个关键点为 $(0,0)$，第 $k+1$ 个关键点为 $(n,m)$，同时 $k \gets k+1$。

发现同时处理多个关键点是困难的，于是考虑从一个关键点入手，设 $g_i$ 为以第 $i$ 个关键点结尾的权值和，考虑上一个关键点是谁，假设为 $j$，再算上从 $j$ 到 $i$ 且不经过其它关键点的方案数（设为 $f_{j,i}$），还有 $i,j$ 之间的权值，则有式子：

$$
g_i = \sum _{j=0} ^{i-1} 2 \times f_{j,i} \times \left( g_j + {\rm val}(j,i) \times \binom {r_x + b_x} {r_x} \right)
$$

其中 ${\rm val}(j,i)$ 表示从 $j$ 到 $i$ 的这一部分宝石的权值和，即 $2(r_i-r_j) + (b_i-b_j)$，乘上 $\binom {r_x + b_x} {r_x}$ 是因为在 $j$ 之前的每条路径都要计算一遍，即总共有 $\binom {r_x + b_x} {r_x}$ 种方案由 $(0,0)$ 到达 $(r_j,b_j)$，每个方案后面都要接一个 $j$ 到 $i$ 的路径。

对于 $f_{j,i}$，众所周知这是个经典容斥，可以用 [AT_dp_y](https://atcoder.jp/contests/dp/tasks/dp_y) 的方法 $O(k^3)$ 求出来。

## Code

```cpp
namespace math
{
    int inv[V],fac[V],finv[V];
    il void init_inv(int n) {inv[0]=inv[1]=finv[0]=finv[1]=fac[0]=fac[1]=1; rep(i,2,n) inv[i]=(mod-mod/i)*inv[mod%i]%mod,finv[i]=inv[i]; rep(i,2,n) fac[i]=fac[i-1]*i%mod,finv[i]=finv[i-1]*finv[i]%mod;}
    il void init_inv() {init_inv(V-1);}
    template <typename T> il T fact(T n) {T ans=1; rep(i,1,n) (ans*=i)%=mod; return ans;}
    template <typename T> il T A(T n,T m) {!finv[0] && (init_inv(),1); return n<m ? 0 : fac[n]*finv[n-m]%mod;}
    template <typename T> il T C(T n,T m) {!finv[0] && (init_inv(),1); return n<m ? 0 : fac[n]*finv[m]%mod*finv[n-m]%mod;}
    template <typename T> il T fpow(T a,T b) {if(a==-1) return b&1?-1:1; if(b<0) return 0; T ans=1; while(b){if(b&1) ans=ans*a%mod; b>>=1,a=a*a%mod;} return ans;}
    template <typename T> il void exgcd(T a,T b,T &x,T &y) {if(!(a%b)) x=0,y=1; else exgcd(b,a%b,y,x),y-=a/b*x;}
    template <typename T> il T ginv(T a) {if(a<V && inv[a]) return inv[a]; int x,k; exgcd((int)a,mod,x,k); return (x%mod+mod)%mod;}
}
using namespace math;

int n,m,k,f[MAXN][MAXN],g[MAXN];
pii a[MAXN];

il void solve(int __Ti)
{
    read(n,m,k);
    {int qwq,qaq; rep(i,1,k) read(qwq,qaq),a[i]={n-qwq,m-qaq};}
    sort(a+1,a+k+1);
    a[++k]={n,m};

    auto calc=[](pii a,pii b){a>b && (swap(a,b),1); return C(b.st-a.st+b.nd-a.nd,b.st-a.st);};
    auto check=[](pii a,pii b){return a.st<=b.st && a.nd<=b.nd;};

    rep(i,0,k+1) rep(j,0,k+1) f[i][j]=0;
    rep(i,0,k) rep(j,i+1,k) if(check(a[i],a[j]))
    {
        f[i][j]=calc(a[i],a[j]);
        rep(_k,i+1,j-1) check(a[i],a[_k]) && check(a[_k],a[j]) && (f[i][j]-=f[i][_k]*calc(a[_k],a[j])%mod);
        f[i][j]=(f[i][j]%mod+mod)%mod;
    }

    auto val=[](pii a,pii b){a>b && (swap(a,b),1); return (b.st-a.st)*2+b.nd-a.nd;};

    g[0]=0;
    rep(i,1,k)
    {
        g[i]=0;
        rep(j,0,i-1) check(a[j],a[i]) && (g[i]+=2*f[j][i]%mod*(g[j]+val(a[j],a[i])*calc({0,0},a[j])%mod)%mod);
        g[i]=(g[i]%mod+mod)%mod;
    }
    
    int ans=g[k]*ginv(2)%mod*ginv(calc({0,0},{n,m}))%mod;
    write((ans%mod+mod)%mod,'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：sunkuangzheng (赞：1)

DP 少乘了一个组合数，没能在赛时拿下这个题呜呜。

感谢 @gxy001 学长赛后在 LA 群里帮我找到了这个少乘的组合数！orz。

---

这个问题显然可以描述成格路计数问题：有一个 $n\times m$ 的网格，上面有 $k(k \le 500)$ 个关键点。每次向下走一步会让权值加 $2$，向右走一步会让权值加 $1$，走到一个关键点会让权值翻倍。问所有 $(0,0) \to (n,m)$ 的路径权值和。

同时考虑多次翻倍很困难。考虑我们想要统计以 $i$ 结尾的路径信息时，我们可以枚举其上一个经过的关键点 $j$，这样 $j \to i$ 途中不会发生任何翻倍。预处理 $f_{j,i}$ 表示关键点 $j$ 到关键点 $i$ 不经过任何障碍物的方案数，这是经典问题，可以简单容斥完成，详见 [AP_DP_Y](https://www.luogu.com.cn/problem/AT_dp_y) 的题解区。

于是设 $dp_i$ 表示以 $i$ 结尾的路径权值和，枚举最后经过的 $j$，有转移 $dp_i \gets 2f_{j,i}(dp_j+val(j\to i) \cdot \color{blue}\binom{x_j + y_j}{x_j}\color{black})$。这里不要忘记那个蓝色的组合数，因为 $j \to i$ 路径的贡献是贡献到所有 $(0,0) \to i$ 的路径上的，所以要补上 $(0,0) \to j$ 的路径数。

时间复杂度 $\mathcal O(n+k^3)$，可以通过。

---

