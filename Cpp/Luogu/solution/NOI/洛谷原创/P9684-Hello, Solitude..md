# Hello, Solitude.

## 题目背景

@【数据删除】 : 我【数据删除】了。 || @【数据删除】 : 你投哪个 || @【数据删除】 : 雪乃对美琴（悲）

## 题目描述

有一张很长的桌子，桌子一边摆了 $n+2$ 张椅子，从左到右依次标号为 $0,1,\dots,n+1$，任意两张相邻的椅子的距离相同。

初始 $0$ 号和 $n+1$ 号椅子上各坐着一个人。然后有 $m$ 个人依次按照如下的规则入座：

- 先均匀随机选择一个空着的座位。
- 若移动到相邻的座位，能使其到相邻的人的最小距离增大，则移动到相邻座位。可以证明上述操作进行有限步后一定会停下。

对于 $1\sim n$ 号的每一张椅子，求出其上面有人坐的概率。

## 说明/提示

#### 样例 1 解释

下面是一种可能的落座方法：

0. 初始 $1\sim n$ 都没有人落座。
1. 选定 $x=2$，到最近的人（位于座位 $0$）距离为 $2$；
   1. 向右移动到 $3$ 号椅子后，到最近的人的距离增大至 $3$，所以 $x\gets x+1$；
   2. 再向右移动到 $4$ 的话，到最近的人（位于座位 $6$）的距离依旧为 $3$，所以在 $3$ 号椅子落座。
2. 选定 $x=6$，到最近的人（位于座位 $7$）距离为 $1$；
   1. 向左移动到 $5$ 号椅子后，到最近的人的距离增大至 $2$，所以 $x\gets x-1$；
   2. 再向左/右移动话，到最近的人的距离均会减小，所以在 $5$ 号椅子落座。
3. 选定 $x=4$，由于无法左右移动，所以直接在 $4$ 号椅子落座。

最终，$3,4,5$ 号椅子上有人坐。

### 数据规模与约定

对于所有数据，$1\le n\le 5\times 10^5$，$0\le m\le n$。

### 子任务

| # | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: |
| 0 | 样例 | 0 |
| 1 | $n\le20$ | 9 |
| 2 | $n\le100$ | 10 |
| 3 | $n\le500$ | 12 |
| 4 | $n\le2000$ | 11 |
| 5 | $n\le5000$ | 12 |
| 6 | $\exists k\in \mathbb{N}$ 使得 $n=2^k-1$ | 13 |
| 7 | $n\le 10^5$ | 15 |
| 8 | - | 18 |

## 样例 #1

### 输入

```
6 3```

### 输出

```
324429415
948332136
224604980
224604980
948332136
324429415```

# 题解

## 作者：Kubic (赞：4)

这是一个不需要 NTT 的 $O(n\log n)$ 做法。

令 $f_{n,k,m}$ 表示第 $k$ 个点被覆盖的方案数。考虑其 EGF：

$$
F_{n,k}(x)=\sum\limits f_{n,k,i}\dfrac{x^i}{i!}
$$

令 $n_1=\left\lfloor\dfrac{n-1}{2}\right\rfloor,n_2=\left\lfloor\dfrac{n}{2}\right\rfloor$。

$f_{n,k,m}$ 的转移式容易得到，经过变换可以得到 $F_{n,k}(x)$ 的转移式：

若 $n$ 为奇数，则：

$$
F_{n,k}(x)=1+\int n(F_{n_1,k}(x)\times (1+x)^{n_2}+F_{n_2,k-n_1-1}(x)\times (1+x)^{n_1})
$$

若 $n$ 为偶数，则：

$$
F_{n,k}(x)=1+\int\dfrac{n}{2}(F_{n_1,k}(x)\times (1+x)^{n_2}+F_{n_2,k-n_1-1}(x)\times (1+x)^{n_1}
$$

$$
+F_{n_2,k}(x)\times (1+x)^{n_1}+F_{n_1,k-n_2-1}(x)\times (1+x)^{n_2})
$$

其中积分运算要求运算后常数项为 $0$。出现积分的原因是我们初始花掉了一次操作，这次操作并不会在合并两棵子树时被统计在内。加入这一次操作在 OGF 的意义下为 $F\leftarrow xF$，在 EGF 的意义下即为 $F\leftarrow\int F$。

可以发现，转移过程中涉及到本质不同的长度相当于线段树上节点长度的种类数，数量为 $O(\log n)$。同时可以得到这些长度总和为 $O(n)$，因此我们只会涉及到 $O(n)$ 个状态。

我们考虑快速地计算出所有可能涉及到的 $F_{n,k}(x)$。

将 $F_{n,k}(x)$ 看作 $\sum a_p(1+x)^p$。我们有：

$$
\int(1+x)^q=\dfrac{1}{q}(1+x)^q-\dfrac{1}{q}
$$

观察转移的特性，可以发现 $a_p\neq 0$ 的 $p$ 只可能为某个 $n-n'$，其中 $n'$ 是某个递归到的长度（积分过程中多出来的 $p=0$ 的一项恰好可以被归入到 $n=n'$ 的情况）。由上面的分析可得只有 $O(\log n)$ 个可能的 $p$！

因此每个 $F_{n,k}(x)$ 在转为上述形式之后均可以被表示为 $O(\log n)$ 项之和。

而上述转移中所有操作均可在与项数同阶的时间复杂度内完成。因此一次转移的时间复杂度为 $O(\log n)$。总时间复杂度为 $O(n\log n)$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e5+5,M=45,MOD=998244353,inv2=499122177;
int n,n1,n2,m,c,tmp,a[N],id[N],o[N],fc[N],invFc[N];bool vs[N];
void W(int &x,int y) {x+=y;if(x>=MOD) x-=MOD;}
void W(int &x,ll y) {x=(x+y)%MOD;}
int add(int x,int y) {x+=y;return x<MOD?x:x-MOD;}
struct Node
{
	int z[M];
	void trs(int x)
	{int t=0;for(int i=1;i<x;++i) z[i]=1ll*z[i]*o[i]%MOD,W(t,z[i]);W(z[x],MOD-t);}
	int eval(int x,int y)
	{
		int res=0;
		for(int i=1;i<=x;++i) if(a[x]-a[i]>=y)
			W(res,1ll*z[i]*fc[a[x]-a[i]]%MOD*invFc[a[x]-a[i]-y]);return res;
	}
};vector<Node> dp[M];
Node operator + (const Node& a,const Node& b)
{Node res;for(int i=1;i<=m;++i) res.z[i]=add(a.z[i],b.z[i]);return res;}
int qPow(int x,int y)
{int res=1;for(;y;y/=2,x=1ll*x*x%MOD) if(y&1) res=1ll*res*x%MOD;return res;}
void init(int n)
{
	fc[0]=invFc[0]=1;for(int i=1;i<=n;++i) fc[i]=1ll*fc[i-1]*i%MOD;
	invFc[n]=qPow(fc[n],MOD-2);
	for(int i=n-1;i;--i) invFc[i]=1ll*invFc[i+1]*(i+1)%MOD;
}
int bn(int x,int y) {return x<y?0:1ll*fc[x]*invFc[y]%MOD*invFc[x-y]%MOD;}
void trs(int x,int x1,int x2)
{
	for(int i=1;i<=a[x];++i) if(i<=a[x1]) dp[x][i]=dp[x][i]+dp[x1][i];
		else if(i>a[x1]+1) dp[x][i]=dp[x][i]+dp[x2][i-a[x1]-1];
}
int main()
{
	scanf("%d %d",&n,&c);n1=n2=n;init(n);tmp=1ll*invFc[n]*fc[n-c]%MOD;
	while(n2) {if(!vs[n2]) vs[a[++m]=n2]=1;if(!vs[n1]) vs[a[++m]=n1]=1;n1=(n1-1)/2;n2/=2;}
	reverse(a+1,a+m+1);
	for(int x=1,x1,x2,t;x<=m;++x)
	{
		dp[x].resize(a[x]+1);if(!a[x]) continue;
		x1=0;for(int i=x;i;--i) if(a[i]==(a[x]-1)/2) {x1=i;break;}
		x2=0;for(int i=x;i;--i) if(a[i]==a[x]/2) {x2=i;break;}
		trs(x,x1,x2);trs(x,x2,x1);t=1ll*a[x]*inv2%MOD;
		for(int i=1;i<=x;++i) o[i]=qPow(a[x]-a[i],MOD-2)%MOD;
		for(int i=1;i<=a[x];++i)
		{
			dp[x][i].trs(x);for(int j=1;j<=x;++j) dp[x][i].z[j]=1ll*dp[x][i].z[j]*t%MOD;
			W(dp[x][i].z[x],1);
		}
	}for(int i=1;i<=n;++i) printf("%d\n",add(MOD-(1ll*dp[m][i].eval(m,c)*tmp)%MOD,1));return 0;
}
```

---

## 作者：Sol1 (赞：4)

首先考虑 $n=2^k-1$ 的做法。

第一个一定会选在整条线的最中间，接下来左右两侧独立。选在左侧的第一个一定选在左半边的中间，选在右侧的第一个一定选在右半边的中间，以此类推。

可以观察到整个线段上的 $n$ 个点形成一个完全二叉树的结构。于是我们对每一个点 $u$ 计算这个子树里面选点的个数 $X_u$ 的概率分布。对应的点被选的概率就是 $P(X_u\neq 0)$。

考虑一棵大小为 $2S+1$ 的子树 $u$，那么其两个孩子 $v_1,v_2$ 的子树大小均为 $S$。首先由于根必须选，所以两孩子的子树内选点的个数之和 $X_u'$ 的概率分布满足 $\forall i>0,P(X_u'=i)=P(X_u=i+1)$；同时 $P(X_u'=0)=P(X_u=0)+P(X_u=1)$。

然后对于一个孩子，其对应的概率分布可以如下计算：

$$P(X_{v_1}=i)=\sum_{j=i}^{2S}\dfrac{\binom{S}{i}\binom{S}{j-i}}{\binom{2S}{j}}P(X_u'=j)$$

差卷积形式可以 FFT 优化。由于一棵子树两侧的概率分布是一样的，所以可以只计算一边，另一边直接复制计算的一边的结果。这样，需要进行长度为 $2^{k}-1,2^{k-1}-1,2^{k-2}-1,\cdots,1$ 长度的 FFT 各 $O(1)$ 次，等比数列求和得到时间复杂度为 $O(n\log n)$。

对于任意的 $n$，该方法的问题在于对于偶数长度的区间，根将可能有两个。

但是注意到两个根是对称的，于是我们可以钦定右边的是根，然后计算出子树内所有点的概率之后取每一个位置和它关于中间对称的位置取平均数得到真正的概率。

于是我们也可以确定一个根，并沿用上面的做法。但是还有一个不同的地方：此时会出现两侧子树大小不同的情况，对于这种情况将必须向两侧分别递归计算。

但是我们发现如下性质：

- 不同的「子树大小变化的过程」只有 $\log n$ 种。
- 如果对于其中一种完成了计算，那么对于另一种只需要从它们的第一个不同的地方开始重新计算。由于每次长度大约减半，所以代价只和这个「第一个不同的地方」有关。
- 所有的「第一个不同的地方」的值求和为 $O(n)$。

我们以 $n=32$ 为例说明：

- $n=32$ 时，有 $5$ 种不同的「子树大小变化的过程」：
	1. $32-16-8-4-2-1$;
   1. $32-16-8-4-1$；
   1. $32-16-8-3-1$；
   1. $32-16-7-3-1$；
   1. $32-15-7-3-1$。
- 以 3 与 4 为例，不同的位置在于 $8$，所以从 3 到 4，重新计算的位置包含 $7,3,1$。等比数列求和，和 $8$ 是同一个量级。
- 1 与 2 不同的位置在于 $2$，2 与 3 不同的位置在于 $4$，3 与 4 不同的位置在于 $8$，4 与 5 不同的位置在于 $16$。
- 形成另一个等比数列求和，因此是 $O(n)$ 的。

所以整个算法的复杂度就是 $O(n\log n)$。

实现的时候也不需要将所有变化过程提取出来，可以直接在线段树上面递归并只在奇数的时候只递归一侧并对另一侧进行复制。具体见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

namespace Poly { /* A giant pile of shit for fast formal power series calculations */ }

int n, m;
long long ans[N], tmp[N];

inline void Work(int len1, int len2, const vector <long long> &g, vector <long long> &f) {
    vector <long long> h, gt;
    for (int i = 0;i <= len1;i++) {
        if (i >= len2) h.push_back(ifac[len1 - i] * ifac[i - len2] % mod);
        else h.push_back(0);
        gt.push_back(fac[i] * fac[len1 - i] % mod * g[i] % mod);
    }
    Poly::Mul(h, gt);
    f.resize(len2 + 1, 0);
    for (int i = 0;i <= len2;i++) f[i] = h[len1 + i] * ifac[i] % mod * ifac[len1] % mod * fac[len2] % mod * fac[len1 - len2] % mod * ifac[len2 - i] % mod;
}

inline void Solve(int l, int r, const vector <long long> &f) {
    int mid = l + r >> 1;
    if ((r - l + 1) % 2 == 0) mid++;
    ans[mid] = (mod + 1 - f[0]) % mod;
    if (l == r) return;
    vector <long long> ft;
    ft.resize(r - l + 1, 0);
    for (int i = 1;i <= r - l + 1;i++) ft[i - 1] = f[i];
    ft[0] = (ft[0] + f[0]) % mod;
    vector <long long> ns;
    Work(r - l, mid - l, ft, ns);
    Solve(l, mid - 1, ns);
    if ((r - l + 1) % 2 == 0) {
        if (r != mid) {
            Work(r - l, r - mid, ft, ns);
            Solve(mid + 1, r, ns);
        }
        for (int i = l;i <= r;i++) tmp[i] = (ans[i] + ans[l + r - i]) % mod * (mod + 1 >> 1) % mod;
        for (int i = l;i <= r;i++) ans[i] = tmp[i];
    } else {
        for (int i = l;i < mid;i++) ans[mid + 1 - l + i] = ans[i];
    }
}

int main() {
    std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    Poly::InitFac(n);
    vector <long long> cur;
    cur.resize(n + 1, 0);
    cur[m] = 1;
    Solve(1, n, cur);
    for (int i = 1;i <= n;i++) cout << ans[i] << "\n";
    return 0;
}
```

---

## 作者：5ab_juruo (赞：3)

转化一下题意：初始有一段长为 $n$ 的极长白色连续段。$m$ 次操作，每次操作有 $\dfrac{\text{连续段长度}}{\text{总白块数}}$ 的概率选中一段极长白色连续段。并随机选择一个这段的中点（偶数有两个），将其标黑。求每个位置最后被标黑的概率。

下文的区间均为极长的白色连续段。

注意到答案的贡献来源于每个区间的中点，且方案总数一定，考虑自上而下计算每个区间的总出现次数。

设 $f(l,r,c)$ 为：若一开始出现区间 $[l,r]$ 时，我们还会对这一段进行 $c$ 次操作，则 $[l,r]$ 的出现次数是多少。设中点为 $mid$，转移为：

$$
f(l,mid-1,t)\gets (r-l+1)\cdot (r-mid)^{\underline{c-t-1}}\cdot \binom{c-1}{t}\cdot f(l,r,c)
$$
	
统计答案时，$[l,r]$ 的中点会贡献（若偶数就把贡献除以二，分别给两个中点加上）：

$$
a_{mid}\gets \sum_{c=1}^{r-l+1} f(l,r,c)\cdot (r-l+1)^{\underline{c}}
$$

转移的部分是一个减法卷积，可以 NTT 优化，此时可以证明直接记搜的复杂度为 $O(n\log^3 n)$。

注意到其实我们不关心区间具体的位置，如果有两种方法转移到一个区间，这两种情况必然是无交的，可以分开考虑而没有影响。

若区间长度为奇数，则只需要递归一侧即可；否则，只需要对每种长度分别求一遍即可。计算出一半的答案后，将贡献复制到另一边即可。

这种做法的复杂度很好分析：把递归树画出来，注意到每个区间往下递归的长度和是递减的，即每一层有效区间长度之和 $\le n$。

upd：其实是 1log 的，因为最坏情况 $n$ 为偶数时，往下递归两层必然能减少 $1/4$，所以总的区间长度和是线性的。

为了避免 3log 做法过可能略微卡常（但怎么还是给过了！非常火大！），std 最慢点只跑了 1.01s。

```cpp
const int mod = 998244353, max_n = 500000, max_lgn = 20, max_l = 1 << max_lgn, g = 3;
using mint = mod_int<mod>;
const mint inv2 = mint(2).inv();

mint fac[max_n + 1], ifac[max_n + 1], dinv[max_n + 1];
void initfac(int _lim)
{
	fac[0] = 1;
	for (int i = 0; i < _lim; i++)
		fac[i + 1] = fac[i] * (i + 1);
	ifac[_lim] = fac[_lim].inv();
	for (int i = _lim; i > 0; i--)
	{
		ifac[i - 1] = ifac[i] * i;
		dinv[i] = ifac[i] * fac[i - 1];
	}
}
inline mint C(int n, int m) { return fac[n] * ifac[m] * ifac[n - m]; }

vector<mint> calc(const vector<mint>& RT, int L, int R)
{
	vector<mint> S(R + 1), T(RT.begin() + 1, RT.end());
	for (int i = 0; i <= R; i++)
		S[i] = C(R, i);
	for (int i = 0; i < ssz(T); i++)
		T[i] *= dinv[i + 1];
	
	int l = 1, gsz = ssz(S) + ssz(T) - 1;
	while (l < gsz)
		l <<= 1;
	S.resize(l), T.resize(l);
	
	init(l);
	NTT(S, l, 1), NTT(T, l, 1);
	for (int i = 0; i < l; i++)
		S[i] *= T[i];
	NTT(S, l, 0);
	
	S.resize(R + L + 1);
	S.erase(S.begin(), S.begin() + R);
	for (auto& x : S)
		x *= (L + R + 1);
	return S;
};

vector<mint> dfs(int n, vector<mint> dp)
{
	if (n == 0)
		return vector<mint>();
	vector<mint> ans(n);
	
	int mid = (n - 1) / 2;
	
	auto tans = dfs(mid, calc(dp, mid, n - mid - 1));
	for (int i = 0; i < ssz(tans); i++)
		ans[i] += tans[i];
	for (int j = 1; j <= n; j++)
		ans[mid] += dp[j] * C(n, j);
	if (n % 2 == 0)
	{
		tans = dfs(mid + 1, calc(dp, mid + 1, n - mid - 2));
		for (int i = 0; i < ssz(tans); i++)
			ans[i] = (ans[i] + tans[i]) * inv2;
	}
	for (int i = 0; i < n / 2; i++)
		ans[n - i - 1] = ans[i];
	return ans;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	
	cin >> n >> m;
	initfac(n);
	
	vector<mint> dp(n + 1);
	dp[m] = fac[m];
	auto ans = dfs(n, dp);
	
	mint bs = ifac[n] * fac[n - m];
	for (int i = 0; i < n; i++)
		cout << ans[i] * bs << "\n";
	
	return 0;
}
```

---

