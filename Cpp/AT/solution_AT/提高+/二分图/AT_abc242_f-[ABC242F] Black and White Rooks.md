# [ABC242F] Black and White Rooks

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc242/tasks/abc242_f

縦 $ N $ 行、横 $ M $ 列のマス目に、黒い飛車の駒 $ B $ 個と白い飛車の駒 $ W $ 個を設置することを考えましょう。

以下の条件をすべて満たす設置の仕方を *いい配置* と呼びます。

- $ B+W $ 個の駒すべてが設置されている。
- $ 1 $ つのマスに置かれている駒の数は高々 $ 1 $ つである。
- ある白い駒と黒い駒の組であって、互いが互いを攻撃しているようなものが存在しない。すなわち、ある白い駒と黒い駒の組であって、一方が $ 1 $ 手の移動によってもう片方が置かれているマスに到達できるようなものが存在しない。

ここで、飛車の駒は、今いる位置から上、下、右、左のいずれかの方向に伸びる直線上にあり、かつ他の駒を飛び越えずに到達できるマスに $ 1 $ 手で移動することができます。

いい配置としてあり得るものは何通りありますか？答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを出力してください。

同じ色の駒同士は区別しないものとします。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 50 $
- $ 1\ \leq\ B,W\ \leq\ 2500 $
- $ B+W\ \leq\ N\ \times\ M $
- 入力はすべて整数

### Sample Explanation 1

いい配置としてあり得るものは以下の $ 4 $ 通りです。 !\[\](https://img.atcoder.jp/ghi/00c6bee30b78604192be9b9f0701fc48.png)

### Sample Explanation 2

いい配置としてあり得るものが存在しない場合もあります。

### Sample Explanation 3

$ 998244353 $ で割ったあまりを出力することに注意してください。

## 样例 #1

### 输入

```
2 2 1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
1 2 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
40 40 30 30```

### 输出

```
467620384```

# 题解

## 作者：CYZZ (赞：13)

这是一个类似容斥原理的做法。
## 题意
有 $B$ 个黑点和 $W$ 个白点要被放进 $n \times m$ 的棋盘上，白点和黑点不能放在同一行或同一列，问放置的方案数。
## 思路分析
如果已经知道：

$b_{i,j}$ 表示把 $B$ 个黑点放进 $i$ 行 $j$ 列的方案数（注意不是答案）。

$w_{p,q}$ 表示把 $W$ 个白点放进 $p$ 行 $q$ 列的方案数。

那么最终答案为:

$$\sum_{i=1}^n\sum_{p=1}^{n-i}\sum_{j=1}^m\sum_{q=1}^{m-j} C_n^i\times C_{n-i}^p\times C_m^j\times C_{m-j}^q\times b_{i,j}\times w_{p,q}$$

再考虑如何求 $b_{i,j}$ 和 $w_{p,q}$，以前者为例。

如果在 $i\times j$ 个格子中随便选 $B$ 个放，方案数为 $C_{i\times j}^B$。

但是如果随便放的话，可能会有某行或某列空着，也就是没有占满 $i$ 行 $j$ 列，所以需要减去这些方案。

假设 $i$ 行 $j$ 列中只有 $p$ 行 $q$ 列派上了用场，那么 $b_{i,j}$ 就需要减去 $C_i^p\times C_j^q\times b_{p,q}$，注意 $i=p,j=q$ 的情况不能减：

$$b_{i,j}=C_{i\times j}^B-\sum_{p=1}^i\sum_{q=1}^jC_i^p\times C_j^q\times b_{p,q},(i,j)\ne (p,q)$$

同理也可求出 $w$ 数组，最后计算 $ans$ 即可。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,B,W,b[55][55],w[55][55],C[2505][2505],mod=998244353,ans;
signed main()
{
    C[0][0]=1;
    scanf("%lld%lld%lld%lld",&n,&m,&B,&W);
    for(int i=1;i<=2500;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<=2500;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;//组合数
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            b[i][j]=C[i*j][B];
            for(int p=1;p<=i;p++)
                for(int q=1;q<=j;q++)
                    if(i!=p||j!=q)
                        b[i][j]=((b[i][j]-C[i][p]*C[j][q]%mod*b[p][q]%mod)%mod+mod)%mod;//要加mod防止出现负数
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            w[i][j]=C[i*j][W];
            for(int p=1;p<=i;p++)
                for(int q=1;q<=j;q++)
                    if(i!=p||j!=q)
                        w[i][j]=((w[i][j]-C[i][p]*C[j][q]%mod*w[p][q]%mod)%mod+mod)%mod;
        }
    for(int i=1;i<=n;i++)
        for(int p=1;p<=n-i;p++)
            for(int j=1;j<=m;j++)
                for(int q=1;q<=m-j;q++)
                    ans=(ans+C[n][i]*C[n-i][p]%mod*C[m][j]%mod*C[m-j][q]%mod*b[i][j]%mod*w[p][q]%mod)%mod;//计算答案
    printf("%lld",ans);
}

```
点个赞再走吧。

---

## 作者：by_chance (赞：7)

[Link](https://www.luogu.com.cn/problem/AT_abc242_f)

先放置黑棋，如果黑车恰好占据了 $a$ 行 $b$ 列，则白车可以放在剩下的 $N-a$ 行和 $M-b$ 列，有 $C((N-a) \times (M-b),W)$ 种放置方法。这里 $C$ 是组合数。

所以只用处理黑车恰好占据 $a$ 行 $b$ 列的方案数。可以使用容斥（参考[官方题解](https://atcoder.jp/contests/abc242/editorial/3538)）,这里提供一种不同的思路。

考虑动态规划，设 $k$ 个黑棋恰好占据 $i$ 行 $j$ 列的有 $dp[k][i][j]$ 种方法。这里把 $k$ 作为阶段进行递推。

状态转移方程是

$$ dp[k][i][j]=\dfrac{1}{k}((dp[k-1][i-1][j-1]+dp[k-1][i-1][j]+dp[k-1][i][j-1]) \times i \times j+dp[k-1][i][j] \times (i \times j-k+1)) $$

这个方程其实有很多需要思考的地方。

$dp[k-1][i][j]$ 一项是新增的一枚棋子不占据新的行列的方案，则新的棋子可以放在这 $i$ 行 $j$ 列未被占据的格，有 $i \times j -k+1$ 个。

另外三种情形请看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/pa0tp7ng.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

蓝色点表示原有的点，三张图分别是加一行，加一列，加一行一列。红色点标出了下一枚棋子可以放的位置，所以在转移方程中要乘 $i \times j$ 的系数。

最后，每一种方式可以由 $k$ 个 $k-1$ 枚棋子的方式得到，所以要除以 $k$。

预处理逆元和组合数，详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,N=55,M=2505;
int n,m,b,w,fac[M],fac_inv[M],inv[M],dp[M][N][N],ans;
int power(int a,int b){
	int c=1;
	for(;b;b>>=1){
		if(b&1)c=1ll*c*a%mod;
		a=1ll*a*a%mod;
	}
	return c;
}
int C(int n,int m){
	if(n<m||n<0||m<0)return 0;
	return 1ll*fac[n]*fac_inv[m]%mod*fac_inv[n-m]%mod;
}
int main(){
	fac[0]=1;
	for(int i=1;i<=M-5;i++)fac[i]=1ll*i*fac[i-1]%mod;
	for(int i=0;i<=M-5;i++)fac_inv[i]=power(fac[i],mod-2);
	for(int i=1;i<=M-5;i++)inv[i]=power(i,mod-2);
	scanf("%d%d%d%d",&n,&m,&b,&w);
	dp[1][1][1]=1;
	for(int k=2;k<=n*m;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				//if(i*j<=k)continue;
				dp[k][i][j]=(1ll*dp[k-1][i-1][j-1]*i*j%mod+1ll*dp[k-1][i-1][j]*i*j%mod+
							1ll*dp[k-1][i][j-1]*i*j%mod+1ll*dp[k-1][i][j]*(i*j-k+1)%mod)*inv[k]%mod;
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ans=(ans+1ll*dp[b][i][j]*C(n,i)%mod*C(m,j)%mod*C((n-i)*(m-j),w)%mod)%mod;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：HYXLE (赞：2)

## [ABC242F] Black and White Rooks

一道计数题。

记黑车数量为 $A$ ，白车数量为 $B$。

设 $f_{i,j}$ 表示黑车恰好占领了 $i$ 行 $j$ 列的方案数。

同时设 $g_{i,j}$ 表示白车恰好占领了 $i$ 行 $j$ 列的方案数。

那么答案就是 $\sum_{i=1}^n\sum_{j=1}^m\sum_{k=1}^{n-i}\sum_{l=1}^{m-j}C(n,i) \times C(m,j) \times C(n-i,k) \times C(m-j,l) \times f_{i,j} \times g_{k,l}$

考虑如何计算 $f$ 数组。

首先发现，如果你占领了恰好 $i$ 行 $j$ 列的话，那么你只有 $i \times j$ 个格子可以放置。

所以如果随便乱排的话方案数是 $C(i\times j,A)$。

但是如果你随便乱排的话可能会有没有占满的情况，所以考虑容斥。

假设你要占领 $i$ 行 $j$ 列的话，且只有 $p$ 行 $q$ 列真正被占领了，那么方案数就要减去 $C(i,p)\times C(j,q)\times f_{p,q}$。

注意当 $p=i$ 且 $q=j$ 时不用减去贡献。

所以 $f_{i,j} = C(i\times j) - \sum_{p=1}^i\sum_{q=1}^j C(i,p) \times C(j,q) \times f_{p,q},(i,j) \ne (p,q)$

$g$ 数组同理，故不赘述了。

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=55,mod=998244353;
inline ll qmul(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=(a*a)%mod;b>>=1;
	}
	return ans;
}
ll fac[N*N],inv[N*N];
inline void init(int x){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(R int i=2;i<=x;++i)fac[i]=fac[i-1]*i%mod;
	inv[x]=qmul(fac[x],mod-2);
	for(R int i=x-1;i>1;--i)inv[i]=inv[i+1]*(i+1)%mod;
}
inline ll C(ll a,ll b){
	if(a<b||b<0||a<0)return 0;
	return fac[a]*inv[b]%mod*inv[a-b]%mod;
}
int n,m,a,b;ll f[N][N],g[N][N],res;
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>m>>a>>b;
	init(n*m);
	for(R int i=1;i<=n;++i){
		for(R int j=1;j<=m;++j){
			f[i][j]=C(i*j,a);
			for(R int k=1;k<=i;++k){
				for(R int l=1;l<=j;++l){
					if(k!=i||l!=j)f[i][j]=(f[i][j]-C(i,k)*C(j,l)%mod*f[k][l]%mod+mod)%mod;
				}
			}
		}
	}
	for(R int i=1;i<=n;++i){
		for(R int j=1;j<=m;++j){
			g[i][j]=C(i*j,b);
			for(R int k=1;k<=i;++k){
				for(R int l=1;l<=j;++l){
					if(k!=i||l!=j)g[i][j]=(g[i][j]-C(i,k)*C(j,l)%mod*g[k][l]%mod+mod)%mod;
				}
			}
		}
	}
	for(R int i=1;i<=n;++i){
		for(R int j=1;j<=m;++j){
			for(R int k=1;k<=n-i;++k){
				for(R int l=1;l<=m-j;++l){
					res=(res+C(n,i)*C(m,j)%mod*C(n-i,k)%mod*C(m-j,l)%mod*f[i][j]%mod*g[k][l]%mod)%mod;
				}
			}
		}
	}
	cout<<res;
	return 0;
}
```

---

## 作者：Monkey_Dog (赞：1)

这是一个比较复杂的组合数学。

枚举白色棋子占了 $i$ 行 $j$ 列，则黑棋就只剩下了 $n\times m-i\times m-j\times n+i\times j$ 个格子可以放。

定义 $f_{i,j}$ 表示占用 $i$ 行 $j$ 列的总方案数，则显然可以得到对于一对 $(i,j)$ 总的方案值为：
$$C_n^i\times C_m^j\times f_{i,j}\times C_{n*m-i*m-j*n+i*j}^B$$

接下来只用计算出 $f_{i,j}$ 就可以得到答案。

先另 $f_{i,j}=C_{i\times j}^W$，意思是在 $i\times j$ 的格子中放 $W$ 个白色棋子的方案数。

但可以发现在这之中有些放置方案是占满不了 $i$ 行 $j$ 列。所以枚举在 $i\times j$ 的格子中有 $x$ 行没有被占用 $y$ 列没有被占用。所以剩下的 $i-x$ 行 $j-y$ 列就是完全占用的。

则对于每个 $f_{i,j}$ 需要减去 $C_i^x\times C_j^y\times f_{i-x,j-y}$。

这里的[组合数](https://oi-wiki.org/math/combinatorics/combination/)可以使用[组合数与杨辉三角](https://blog.csdn.net/bell041030/article/details/88911180)的规律，能够预处理出来直接使用。

因为 $1\le N,M\le 50$ 所以直接用四层循环暴力枚举计算即可。注意要在过程中不断进行取模。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int M=998244353;
int n,m,B,W,f[51][51],c[2505][2505],sum;
signed main(){
    cin>>n>>m>>B>>W;
    c[1][1]=1;
    for(int i=2;i<=2501;i++)
    for(int j=1;j<=i;j++)
        c[i][j]=c[i-1][j]+c[i-1][j-1],c[i][j]%=M;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(i*j>=W){
                f[i][j]=c[i*j+1][W+1];
                for(int x=0;x<i;x++)
                    for(int y=0;y<j;y++){
                        if(!(x||y))continue;
                        int k=((c[i+1][x+1]*c[j+1][y+1])%M*f[i-x][j-y])%M;
                        f[i][j]+=M;f[i][j]-=k;f[i][j]%=M;
                    }
                sum+=(((c[n+1][i+1]*c[m+1][j+1])%M*f[i][j])%M*c[n*m-i*m-j*n+i*j+1][B+1])%M;
                sum%=M;
            }
        }
    cout<<sum;
}
```

---

## 作者：llqqhh (赞：1)

# AT_abc242_f

## 题面

在一个 $n$ 行 $m$ 列的棋盘上放置 $b$ 只黑车和 $w$ 只白车，要使同行同列没有相同颜色的车，输出总放置方案数对 $998244353$ 取模的结果。

### 数据范围

$1 \le n,m \le 50, 1 \le b,w \le 2500$；

## 思路

首先容易想到枚举**预先留给黑车**的行数 $i$ 和列数 $j$ ，留给白车的空间就是 $(n-i)\times(m-j)$ ，在剩余的空间中选择 $W$ 个作为白车的方案数为 $C_{(n-i)\times(m-j)}^{W}$ 。同时枚举黑车**真正占据**的行数 $u$，和列数 $v$，最后的答案就是：
$$
\sum_{i=1}^n \sum_{j=1}^m \sum_{u=1}^{i} \sum_{v=1}^j
	C_{(n-i)\times(m-j)}^{W}\times C_n^i\times C_m^j \times C_i^u \times C_j^v
$$
于是我们得到了一个复杂度为 $O(n^4)$ 的做法，但是我们可以通过容斥原理将算法优化到 $O(n^3)$。

定义 $f_{i, j}$ 表示黑车选择不超过 $i$ 行，刚好选择 $j$ 列的方案数。如果说 $f_{i,j}$ 的初始值是 $C_{i\times j}^b$ 的话，那么我们就多加了预留比真实占用多1列的情况，所以要减去 $C_{i\times (j-1)}^b\times C_j^1$。但是由于预留比真实占用多2列的情况也被我们刚才一顿操作给减掉了，所以要加回 $C_{i\times(j-2)}^b\times C_j^2$，同理还要减去多3列的情况，以此类推。写得官方一些就是：
$$
f_{i, j} = C_{i\times j}^b+ \sum_{k=1}^{j-1}(-1)^k\times C_{i\times (j-k)}^b\times C_j^k
$$
同理定义 $g_{i, j}$ 表示黑车刚好选择 $i$ 行，刚好选择 $j$ 列的方案数，则有：
$$
g_{i, j} = f_{i,j}+\sum_{k=1}^{i-1}(-1)^k\times f_{i-k, j}\times C_{i, k}
$$
最后统计答案：
$$
\sum_{i=1}^n\sum_{j=1}^m C_n^i \times C_m^j \times g_{i, j} \times C_{(n-i)\times(m-j)}^{W}
$$
最终代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1010, mod = 998244353, M = 250010;
ll n, m, b, w, g[N][N], f[N][N];
ll mul[M], inv[M];

ll qpow(ll x, ll y) {
    ll res = 1;
    while(y) {
        if(y & 1) res = res * (x%mod) % mod;
        x = (x%mod) * (x%mod) % mod;
        y >>= 1;
    }
    return res;
}

void init() {
    int tmp = 250000;
    mul[0] = inv[0] = 1;
    for(int i = 1; i <= tmp; i ++) 
        mul[i] = mul[i-1] * i % mod;
    inv[tmp] = qpow(mul[tmp], mod - 2);
    for(int i = tmp - 1; i >= 1; i --) 
        inv[i] = inv[i + 1] * (i + 1) % mod;
}

ll c(ll x, ll y) {
    if(x < y) return 0;
    return mul[x]*inv[y]%mod*i  nv[x-y]%mod;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    init();
    cin >> n >> m >> b >> w;
    for(ll i = 1; i <= n; i ++) 
        for(ll j = 1; j <= m; j ++) {
            f[i][j] = c(i*j, b);
            for(ll k = 1, sgn = -1; k < j; k ++, sgn *= -1) {
                f[i][j] += sgn * c(i*(j-k), b) * c(j, k) % mod;
                f[i][j] = (f[i][j]%mod+mod)%mod;
            }
        }
    for(ll i = 1; i <= n; i ++)
        for(ll j = 1; j <= m; j ++) {
            g[i][j] = f[i][j];
            for(ll k = 1, sgn = -1; k < i; k ++, sgn *= -1) {
                g[i][j] += sgn * c(i, k) * f[i-k][j] % mod;
                g[i][j] = (g[i][j]%mod+mod)%mod;
            }
        }
    ll ans = 0;
    for(ll i = 1; i < n; i ++) {    
        for(ll j = 1; j < m; j ++) {
            ans += c(n, i) * c(m, j)%mod * g[i][j]%mod * c((n-i)*(m-j), w)%mod;
            ans %= mod;
        }
    }
    cout << ans;
}
```

---

## 作者：翼德天尊 (赞：1)

> $n\times m$ 的棋盘，放置 $B$ 只黑车和 $W$ 只白车，需满足：
>
> - 所有车都放在方格内，每个方格只能放一个车。
> - 不同颜色的车不能放在同一行同一列。
>
> $1\le n,m\le 50$，$1\le B,W\le 2500$，$B+W\le n\times m$。

考虑先划定一些行和列给黑车。设 $f(i,j)$ 表示划定恰好前 $i$ 行 $j$ 列给的方案数，则有：
$$
ans=\sum_{i=1}^n\sum_{j=1}^mC_n^iC_m^jf(i,j)\times C_{(n-i)(m-j)}^W
$$
考虑二项式反演，设 $g(i,j)$ 表示划定至多 $i$ 行 $j$ 列给的方案数，则有：
$$
\begin{aligned}f(i,j)&=\sum_{p=0}^i(-1)^{i-p}C_i^p\sum_{q=0}^j(-1)^{j-q}C_j^q g(p,q)\\
&=\sum_{p=0}^i\sum_{q=0}^j(-1)^{i+j-p-q}C_i^pC_j^qg(p,q)\end{aligned}
$$
$g$ 的求解就比较简单了：
$$
g(i,j)=C_{ij}^B
$$
于是 $O(n^4)$ 求解即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=55;
const int V=2500;
const int mod=998244353;
int n,m,b,w;
ll jc[V+5],inv[V+5],g[N][N],f[N][N];
int read(){
    int w=0,f=1;
    char ch=getchar();
    while (ch>'9'||ch<'0') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        w=(w<<3)+(w<<1)+(ch^48);
        ch=getchar();
    }
    return w*f;
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
    for (int i=1;i<=V;i++) jc[i]=1ll*jc[i-1]*i%mod;
    inv[V]=ksm(jc[V],mod-2);
    for (int i=V-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
ll C(ll x,ll y){
    if (x<y) return 0;
    //cout<<x<<" "<<jc[x]<<" "<<y<<" "<<inv[y]<<"\n";
    return 1ll*jc[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
#endif
    init();
    n=read(),m=read(),b=read(),w=read();
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            g[i][j]=C(i*j,b);
            //cout<<i*m-i*j+j*n<<" "<<b<<" "<<g[i][j]<<"\n";
        }
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            for (int p=1;p<=i;p++){
                for (int q=1;q<=j;q++){
                    ll s=((i+j-p-q)&1)?-1:1;
                    f[i][j]=(f[i][j]+s*C(i,p)*C(j,q)%mod*g[p][q]%mod+mod)%mod;
                }
            }
        }
    }
    ll ans=0;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            ans=(ans+C(n,i)*C(m,j)%mod*f[i][j]%mod*C((n-i)*(m-j),w)%mod)%mod;
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：__vector__ (赞：0)

本题解做法比较暴力，容斥过程需要一步步拆解成子问题，每次都通过容斥转化。而能单次完成容斥的方法，别的题解已经写了。    
### 一些分析   
车的攻击范围包括一行和一列。  

每个车均会覆盖某行和某列，要求找到摆放方案数，使得黑方和白方的覆盖范围互不重叠。  

可以考虑枚举黑方，白方分别占据了多少行，多少列。  
### 实际做法  
假设 $f(i,j)$ 代表黑方占据**已经选定的** $i$ 行 $j$ 列的摆放方案数，$g(i,j)$ 代表白方占据**已经选定的** $i$ 行 $j$ 列的方案数。  

那么答案是：  
$$
\sum\limits_{i=1}^n\sum\limits_{j=1}^m\sum\limits_{k=1}^{n-i}\sum\limits_{l=1}^{m-j}\binom{n}{i}\binom{m}{j}\binom{n-i}{k}\binom{m-j}{l} f(i,j)g(k,l)
$$  

考虑怎么求出 $f$，然后 $g$ 的求解方法同理。  

令 $f'(i,j)$ 代表最多选择 $i$ 行，强制选择 $j$ 列的方案数。

根据二项式反演，得 $f(i,j) = \sum\limits_{i'=1}^{i}\binom{i}{i'}(-1)^{i-i'}f'(i',j)$。  

令 $f''(i,j)$ 代表限制最多选择 $i$ 行，最多选择 $j$ 列的方案数。  

显然 $f''(i,j) = \binom{ij}{b}$。  

根据二项式反演，得 $f'(i,j) = \sum\limits_{j'=1}^j\binom{j}{j'}(-1)^{j-j'}f''(i,j')$。  

先求出 $f''$，然后求出 $f'$，最后求出 $f'$ 就完成了。  


```cpp
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(auto i=(a);i<=(b);i++)
#define REP(i,a,b) for(auto i=(a);i>=(b);i--)
#define FORK(i,a,b,k) for(auto i=(a);i<=(b);i+=(k))
#define REPK(i,a,b,k) for(auto i=(a);i>=(b);i-=(k))
#define pb push_back
#define mkpr make_pair
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
template<class T>
void ckmx(T& a,T b){
    a=max(a,b);
}
template<class T>
void ckmn(T& a,T b){
    a=min(a,b);
}
template<class T>
T gcd(T a,T b){
    return !b?a:gcd(b,a%b);
}
template<class T>
T lcm(T a,T b){
    return a/gcd(a,b)*b;
}
#define gc getchar()
#define eb emplace_back
#define pc putchar
#define ep empty()
#define fi first
#define se second
#define pln pc('\n');
#define islower(ch) (ch>='a'&&ch<='z')
#define isupper(ch) (ch>='A'&&ch<='Z')
#define isalpha(ch) (islower(ch)||isupper(ch))
template<class T>
void wrint(T x){
    if(x<0){
        x=-x;
        pc('-');
    }
    if(x>=10){
        wrint(x/10);
    }
    pc(x%10^48);
}
template<class T>
void wrintln(T x){
    wrint(x);
    pln
}
template<class T>
void read(T& x){
    x=0;
    int f=1;
    char ch=gc;
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=gc;
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=gc;
    }
    x*=f;
}
const ll mod=998244353;
ll qpow(ll a,ll b){
    ll ret=1;
    for(;b;a=a*a%mod,b>>=1){
        if(b&1)ret=ret*a%mod;
    }
    return ret;
}
ll inv(ll a){
    return qpow(a,mod-2);
}
const int maxn=55;
ll fact[maxn*maxn],factinv[maxn*maxn];
ll C(int n,int m){
    return n<m?0:fact[n]*factinv[m]%mod*factinv[n-m]%mod;
}
int n,m,b,w;
ll f1[maxn][maxn],f2[maxn][maxn],f3[maxn][maxn],g1[maxn][maxn],g2[maxn][maxn],g3[maxn][maxn];
void solve(int id_of_test){
	read(n);
    read(m);
    read(b);
    read(w);
    FOR(i,1,n){
        FOR(j,1,m){
            // 限制选 i 行，j 列。
            f3[i][j]=C(i*j,b);
        }
    }
    FOR(i,1,n){
        FOR(j,1,m){
            ll ml=1;
            REP(lsti,i,1){
                (f2[i][j]+=f3[lsti][j]*C(i,lsti)%mod*ml%mod)%=mod;
                ml*=-1;
            }
        }
    }
    FOR(i,1,n){
        FOR(j,1,m){
            ll ml=1;
            REP(lstj,j,1){
                (f1[i][j]+=f2[i][lstj]*C(j,lstj)%mod*ml%mod)%=mod;
                ml*=-1;
            }
        }
    }
    // calc g
    FOR(i,1,n){
        FOR(j,1,m){
            // 限制选 i 行，j 列。
            g3[i][j]=C(i*j,w);
        }
    }
    FOR(i,1,n){
        FOR(j,1,m){
            ll ml=1;
            REP(lsti,i,1){
                (g2[i][j]+=g3[lsti][j]*C(i,lsti)%mod*ml%mod)%=mod;
                ml*=-1;
            }
        }
    }
    FOR(i,1,n){
        FOR(j,1,m){
            ll ml=1;
            REP(lstj,j,1){
                (g1[i][j]+=g2[i][lstj]*C(j,lstj)%mod*ml%mod)%=mod;
                ml*=-1;
            }
        }
    }
    ll ans=0;
    FOR(r1,1,n){
        FOR(c1,1,m){
            FOR(r2,1,n){
                FOR(c2,1,m){
                    (ans+=f1[r1][c1]*g1[r2][c2]%mod*C(n,r1)%mod*C(m,c1)%mod*C(n-r1,r2)%mod*C(m-c1,c2)%mod)%=mod;
                }
            }
        }
    }
    printf("%lld\n",(ans+mod)%mod);
}
int main()
{
    fact[0]=1;
    FOR(i,1,maxn*maxn-1)fact[i]=fact[i-1]*i%mod;
    factinv[maxn*maxn-1]=inv(fact[maxn*maxn-1]);
    REP(i,maxn*maxn-1,1)factinv[i-1]=factinv[i]*i%mod;
	int T;
	T=1;
	FOR(_,1,T){
		solve(_);
	}
	return 0;
}

```

---

## 作者：IGpig (赞：0)

## abc242f

### Problem

在 $n$ 行 $m$ 列的棋盘上放 $b$ 只黑车和 $w$ 只白车，要求每对黑车和白车都不在同一行或列上。

### Solution

考虑计数 dp，定义 $f[i][j]$ 表示把所有的车放在前 $i$ 行 $j$ 列里的方案数

以黑车为例，容易想到 $f[i][j]=C^{b}_{i\times j}$，但是这明显有一些方案不合法，因为实际上根本没有填满。

如果只填了 $p$ 行 $q$ 列，那么就有 $C_{i}^{x}\times C_{j}^{q}$ 中选的方法，且有 $f[p][q]$ 种填的方法。

所以不合法的有：
$$
C_{i}^{x}\times C_{j}^{q}\times f[p][q]
$$
然后把两个 $f$ 数组都处理处来之后我们考虑这么求答案。

还是一样的，容易想到答案为 $f[n][m]$，但是实际上我们要考虑两种车之间的限制，即不能同时填一行或一列。

所以如果黑车填了 $i$ 行 $j$ 列，那么白车则会填剩下 $n-i$ 行 $m-j$ 列中的 $p$ 行 $q$ 列。

所以把两个车的方案乘起来就好了：

~~~cpp
	LL tmp1=c[n][i]*c[n-i][p]%mod;
	LL tmp2=c[m][j]*c[m-j][q]%mod;
	ans=(ans+tmp1*tmp2%mod*f1[i][j]%mod*f2[p][q]+mod)%mod;
~~~

### Code

**注意取模！！！**

~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const LL mod=998244353;
LL c[5005][5005]={1},f1[5005][5005],f2[5005][5005],n,m,b,w,ans;
int main(){
    cin>>n>>m>>b>>w;
    for(int i=1;i<=3000;i++){
        c[i][0]=1;
        for(int j=1;j<=3000;j++){
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            f1[i][j]=c[i*j][b];
            f2[i][j]=c[i*j][w];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int p=1;p<=i;p++){
                for(int q=1;q<=j;q++){
                    if(i==p&&j==q) continue;
                    f1[i][j]=(f1[i][j]-f1[p][q]*c[i][p]%mod*c[j][q]%mod)%mod;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int p=1;p<=i;p++){
                for(int q=1;q<=j;q++){
                    if(i==p&&j==q) continue;
                    f2[i][j]=(f2[i][j]-f2[p][q]*c[i][p]%mod*c[j][q]%mod)%mod;
                    //cout<<f2[i][j]<<' '<<endl;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int p=1;p+i<=n;p++){
                for(int q=1;q+j<=m;q++){
                    LL tmp1=c[n][i]*c[n-i][p]%mod;
                    LL tmp2=c[m][j]*c[m-j][q]%mod;
                    ans=(ans+tmp1*tmp2%mod*f1[i][j]%mod*f2[p][q]+mod)%mod;
                }
            }
        }
    }
    cout<<(ans%mod+mod)%mod;
    return 0;
}

~~~

---

## 作者：cwxcplh (赞：0)

一道很具有思维挑战性的题。

题目简化：给你 $B$ 个黑子和 $W$ 个白子，且黑子与白子不能再同一行、同一列，求方案总数（答案对 $998244353$ 取模）。

看到这道题的第一眼，我还没想到用什么算法，只知道求方案总数有两种方法：组合数学与 dp。而这道题则是两种都用了：在组合数学的基础上套了个 dp。

首先我们定义两个 dp：$dpb_{i,j}$ 和 $dpw_{k,l}$，分别表示一共 $i$ 行 $j$ 列时的白子方案总数与 $k$ 行 $l$ 列时的黑子方案数。因此很明显，最终答案就是：

$$\sum^n_i\sum^{n-i}_k\sum^m_j\sum^{m-j}_lC^i_n\times C^j_m\times C^k_{n-i}\times C^l_{m-j}\times dpb_{i,j}\times dpw_{k,l}$$

解释一下：其中枚举的 $i$ 和 $j$ 表示白子有 $i$ 行 $j$ 列，$k$ 和 $l$ 则表示的是黑子，而我们没明确说明 $i$ 行是哪 $i$ 行、$j$ 列是哪 $j$ 列，所以需要一个组合数来算一下，$k$ 和 $l$ 也是一样的，$dpb_{i,j}\times dpw_{k,l}$ 则是乘法原理。

现在我们就要考虑怎么求 $dpb_{i,j}$ 和 $dpw_{k,l}$ 了，因为两者原理一样，我们就说一下前者。

首先肯定要枚举 $i$ 和 $j$，而我们在 $i\times j$ 这么多个格里放 $B$ 个白子则有 $C^B_{i\times j}$ 种。

但随便放的话又有可能没占满 $i$ 行 $j$ 列，所以我们要减去这些方案数。

我们假设 $p$ 行 $q$ 列没有被占，那么总的选择方案数就是 $C^p_i\times C^q_j$，而其中一种 $p$ 行 $q$ 列被占的方案总数为 $dpb_{p,q}$，所以总的要减去的方案数就是 $C^p_i\times C^q_j\times dpb_{p,q}$，所以可以得到：

$$dp_{i,j}=C^B_{i\times j}-C^p_i\times C^q_j\times dpb_{p,q}$$

同理求出 $dpw$，然后算出答案就行了。

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,m,b,w,ans,C[2506][2506],dpb[56][56],dpw[56][56];
signed main()
{
    C[0][0]=1;
    for(int i=1;i<=2500;i++)//预处理
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<=2500;j++)
        {
            C[i][j]=C[i-1][j]+C[i-1][j-1];
            C[i][j]%=mod;
        }
    }
    cin>>n>>m>>b>>w;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dpb[i][j]=C[i*j][b];
            for(int k=1;k<=i;k++)
            {
                for(int l=1;l<=j;l++)
                {
                    if(i!=k||j!=l)
                    {
                        dpb[i][j]=((dpb[i][j]-C[i][k]%mod*C[j][l]%mod*dpb[k][l]%mod)%mod+mod)%mod;
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dpw[i][j]=C[i*j][w];
            for(int k=1;k<=i;k++)
            {
                for(int l=1;l<=j;l++)
                {
                    if(i!=k||j!=l)
                    {
                        dpw[i][j]=((dpw[i][j]-C[i][k]%mod*C[j][l]%mod*dpw[k][l]%mod)%mod+mod)%mod;
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int k=1;k<=n-i;k++)
        {
            for(int j=1;j<=m;j++)
            {
                for(int l=1;l<=m-j;l++)
                {
                    ans=(ans+C[n][i]%mod*C[n-i][k]%mod*C[m][j]%mod*C[m-j][l]%mod*dpb[i][j]%mod*dpw[k][l]%mod)%mod;
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：TruchyR (赞：0)

好牛的计数题。  
下文中 $N$ 与 $M$ 是小写，$B$ 与 $W$ 一般大写。

1. 首先发现每一行或每一列都只能放一类棋子。

    - 如果一行或一列放了两种棋子，无论再放什么都一定会产生攻击关系。  
2. 随后发现一种合法的方案经过排列后都会变成下图的形式：  
    - 黑车占据了 $i$ 行 $j$ 列，白车占据了 $I$ 行 $J$ 列。 
    - 根据 1 容易证出。
3. 考虑在 $i$ 行 $j$ 列中放置全部的黑/白车且**没有空行空列**的方案数，**有顺序**。  
    - 设 $F_b(i,j)$ 和 $F_w(i,j)$ 为对应的方案数，下文以 $F_b$ 为例。  
    - 先不计**没有空行/列**的要求，答案显然是 $P_{ij}^{B}$，其中 $P$ 代表排列数。  
    - 然后枚举只有 $I$ 行 $J$ 列有车，要扣掉的方案就是 $F_b(I,J)\cdot C_i^I\cdot C_j^J$。  
      - 后面的 $C$ 代表组合数，意为从 $i$ 行中选 $I$ 行放黑车，从 $j$ 列中选 $J$ 列放黑车。
    - 于是有 $F_b(i,j)=P_{ij}^{B}-\left(\sum_{I=1}^{i}\sum_{J=1}^{j} F_b(I,J)\cdot C_i^I\cdot C_j^J\cdot[ij≠IJ]\right)$
    - 时间复杂度 $O(n^2m^2)$。  
4. 回到原问题。  
    - 先枚举 $i$ 行 $j$ 列放黑车，$I$ 行 $J$ 列放白车。  
    - 从 $n$ 行中分别选择 $i$ 行和 $I$ 行的方案数即为 $C_n^{i}\cdot C_{n-i}^I$。
    - 从 $m$ 列中分别选择 $j$ 列和 $J$ 列的方案数即为 $C_m^{j}\cdot C_{m-j}^J$。  
    - 在划定的范围里放置黑白车的方案数各为 $F_b(i,j)$ 和 $F_w(I,J)$。  
    - 以上三式相乘即可得到这一种情况的答案，时间复杂度也是 $O(n^2m^2)$。
5. 细节
    - 上文第三问求的是**有顺序**的，所以要在结尾除去 $B!\cdot W!$。
6. 代码

```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
#define int long long
using namespace std;
const int CHECK=0,FIL=0,mod=998244353;int read();
int N,M,B,W,res,Fb[55][55],Fw[55][55];
int P[2505][2505],C[55][55],INV[2505];
void init();
signed main(){
	N=read();M=read();B=read();W=read();
	init();
	for(int i=1;i<=N;i++){
	for(int j=1;j<=M;j++){
		Fb[i][j]=P[i*j][B];
		Fw[i][j]=P[i*j][W];
		for(int I=1;I<=i;I++)
		for(int J=1;J<=j;J++){
			if(I==i && J==j) continue;
			Fb[i][j]=(Fb[i][j]-((C[i][I]*C[j][J]%mod)*Fb[I][J]%mod)+mod)%mod;
			Fw[i][j]=(Fw[i][j]-((C[i][I]*C[j][J]%mod)*Fw[I][J]%mod)+mod)%mod;
		}
	}}
	for(int i=1;i<N;i++){
	for(int j=1;j<M;j++){
	for(int I=1;I+i<=N;I++){
	for(int J=1;J+j<=M;J++){
		int X=(Fb[i][j]*Fw[I][J])%mod; 
		int C1=(C[N][i]*C[N-i][I])%mod; 
		int C2=(C[M][j]*C[M-j][J])%mod; 
		res+=((C1*C2%mod)*X)%mod;
	}}}}
	for(int i=1;i<=B;i++) res=(res*INV[i])%mod;
	for(int i=1;i<=W;i++) res=(res*INV[i])%mod;
	printf("%lld",res);
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
void init(){
	for(int i=1;i<=2500;i++){
		P[i][0]=1;
		for(int j=1;j<=i;j++)
			P[i][j]=(P[i][j-1]*(i-j+1))%mod;
	}
	C[0][0]=1;
	for(int i=1;i<=50;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}INV[0]=INV[1]=1;
	for(int i=2;i<=2500;i++) INV[i]=(INV[i-(mod%i)]*(mod/i+1))%mod;
}
```


---

## 作者：Empty_Dream (赞：0)

## 题意

在 $N$ 行 $M$ 列的棋盘上放 $B$ 只黑车和 $W$ 只白车，要求每对黑车和白车都不在同一行或同一列上。

## 分析

很明显是一道排列组合的题，~~这一场怎么全是这种~~。

硬算肯定是不对的，考虑递推。分别考虑白车和黑车：

- $b_{i,j}$ 表示将 $B$ 辆黑车放入 $i$ 行 $j$ 列的方案数。
- $w_{i,j}$ 表示将 $W$ 辆白车放入 $i$ 行 $j$ 列的方案数。

答案肯定要通过 $b$ 和 $w$ 递推过来，接下来考虑如何求 $b$ 和 $w$。

 $b_{i,j}$ 很容易得到等于 $C_{i \times j} ^ B$。但真的有那么简单吗？果然，这样求得 $b_{i,j}$ 包含了每填满 $i$ 行 $j$ 列的情况，还得逐一减去这些不合法的。设实际上只填满了 $x$ 行 $y$ 列，则要减去 $\sum_{x=1}^{i} \sum_{y=1}^{j}C_{i}^{x} \times C_j^y \times b_{x,y}$（它有 $C_i^x \times C_j^y$ 种不同的选择，每种选择有 $b_{x,y}$ 种方案）。那 $b_{x,y}$ 是哪里来的呢？这是一个递推式，$b_{x,y}$ 在前面已经递推出来了，是一个已知的量。注意不能同时满足 $i=x$ 和 $j=y$，这是要求的答案。

$w$ 数组同理可得。

之后就要去推答案，答案并不是单纯的 $b_{n,m}$，而是考虑所有在 $n$ 行 $m$ 列之中的可能方案。假设黑车填了 $i$ 行 $j$ 列，又考虑到白车和黑车的制约，所以白车肯定实在剩下的行和列中填（行或列都没有填过黑车），但是白车不一定填满了剩下的 $n-i$ 行 $m-j$ 列，所以再来两个变量 $x$ 和 $y$ 表示黑车填了 $x$ 行 $y$ 列，最后把两种车的摆放方式相乘再累加起来就是最终的答案：
$$
\sum_{i=1}^n\sum_{j=1}^m\sum_{x=1}^{n-i}\sum_{y=1}^{m-j}C_n^i \times C_m^j \times C_{n-i}^x \times C_{m-j}^y \times b_{i,j} \times w_{x,y}
$$
组合数记得预处理，在统计答案的时候一定要乘上一个模一个，不然会 WA。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int n, m, B, W, ans;
int C[2505][2505], w[55][55], b[55][55];

signed main(){
	cin >> n >> m >> B >> W;
	C[0][0] = 1;
	for (int i = 1; i <= 2500; i++){//预处理组合数
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j <= 2500; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	for(int i = 1;i <= n;i++){//处理w和b两个数组
		for(int j = 1;j <= m;j++){
			w[i][j] = C[i*j][W];
			b[i][j] = C[i*j][B];
			for(int x = 1; x <= i; x++){
				for(int y = 1; y <= j; y++){
					if (i == x && j == y) continue;
					w[i][j] = (w[i][j] - C[i][x] * C[j][y] % mod * w[x][y] % mod) % mod;
					b[i][j] = (b[i][j] - C[i][x] * C[j][y] % mod * b[x][y] % mod) % mod;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			for (int x = 1; x <= n - i; x++){
				for (int y = 1; y <= m - j; y++){
					ans = (ans + (C[n][i] * C[n - i][x] % mod * C[m][j] % mod * C[m - j][y] % mod * b[i][j] % mod * w[x][y] % mod + mod) % mod) % mod;//最终答案
				}
			}
		}
	}
	cout << (ans % mod + mod) % mod;
	return 0;
}
```



 

---

## 作者：Saint_ying_xtf (赞：0)

[博客园](https://www.cnblogs.com/gsczl71)。

我们先预处理以下 $b$ 数组和 $w$ 数组。

这两个数组的定义如下：

- $b_{i,j}$ 代表将输入的 $B$ 个点放入 $i$ 行 $j$ 列的方案数。
- $w_{i,j}$ 代表将输入的 $W$ 个点放入 $i$ 行 $j$ 列的方案数。

如何求 $b$ 数组？

首先很容易想到，所有的方案数是 $C_{i\times j}^B$。但这不一定填满了 $i$ 行 $j$ 列，所以还需要减去一部分的方案数。

如果这 $i$ 行 $j$ 列是只有 $x$ 行 $y$ 列实际有作用的话，方案数是 $C_i^x \times C_j^y \times b_{x,y}$。于是我们直接枚举 $O(N^2 \times M^2)$ 来进行转移。

但要注意的点是 $i=x$ 和 $j=y$ 同时满足时是不可以减去的。因为这其实就是答案的贡献，减去了，就没有了。

对于 $w$ 数组也是一样的道理。

那我们知道了这两个数组又能干啥呢？

很显然，最后的答案等于：$\sum_{i=1}^n \sum_{j=1}^m \sum_{x=1}^{n-i} \sum_{y=1}^{m-j} C_n^i \times C_m^j \times C_{n-i}^x \times C_{m-j}^y \times b_{i,j} \times w_{x,y}$。

其中 $C$ 是组合数，我们先用递推的方式预处理即可。

[link](https://atcoder.jp/contests/abc242/submissions/49525284)

---

