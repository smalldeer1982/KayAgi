# GCDDCG

## 题目描述

你正在参加一场名为“最大公约数牌组构建”的卡牌游戏。这款游戏中共有 $N$ 张牌（编号从 $1$ 到 $N$），第 $i$ 张牌的点数为 $A_i$，其中 $A_i$ 是 $1$ 到 $N$ 之间的整数（包括 $1$ 和 $N$）。

游戏由 $N$ 轮组成（从第 $1$ 轮到第 $N$ 轮）。在每一轮中，玩家需要将牌分成两个非空牌组：牌组 $1$ 和牌组 $2$。每一张牌不能同时出现在两个牌组里，并且允许有些牌不用。第 $i$ 轮的要求是，两个牌组中每个牌组的牌值的最大公约数（GCD）都要等于 $i$。

在第 $i$ 轮，你的创造力点数等于 $i$ 乘以可以构建这两个有效牌组的方案数。如果其中一个牌组的组成不同，那么视为不同的方案。

请计算所有 $N$ 轮中创造力点数的总和。因为这个总和可能会非常大，结果需要对 $998\,244\,353$ 取模。

## 说明/提示

在样例输入/输出 #1 中，第 $1$ 轮和第 $2$ 轮的创造力点数均为 $0$。

在第 $3$ 轮，有 $12$ 种构建两个牌组的方法。记 $B$ 和 $C$ 为牌组 $1$ 和牌组 $2$ 中各自的牌号集合。这 $12$ 种方法包括：

- $B = \{ 1 \}, C = \{ 2 \}$
- $B = \{ 1 \}, C = \{ 3 \}$
- $B = \{ 1 \}, C = \{ 2, 3 \}$
- $B = \{ 2 \}, C = \{ 1 \}$
- $B = \{ 2 \}, C = \{ 3 \}$
- $B = \{ 2 \}, C = \{ 1, 3 \}$
- $B = \{ 3 \}, C = \{ 1 \}$
- $B = \{ 3 \}, C = \{ 2 \}$
- $B = \{ 3 \}, C = \{ 1, 2 \}$
- $B = \{ 1, 2 \}, C = \{ 3 \}$
- $B = \{ 2, 3 \}, C = \{ 1 \}$
- $B = \{ 1, 3 \}, C = \{ 2 \}$

在样例输入/输出 #2 中，第 $1$、$2$、$3$ 和 $4$ 轮中的构建方案数分别为 $0$、$18$、$0$ 和 $2$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3 3 3```

### 输出

```
36```

## 样例 #2

### 输入

```
4
2 2 4 4```

### 输出

```
44```

## 样例 #3

### 输入

```
9
4 2 6 9 7 7 7 3 3```

### 输出

```
10858```

# 题解

## 作者：dAniel_lele (赞：4)

比较好题，挺经典。

首先枚举两个集合的 $\gcd$，设为 $x$。对于每个 $x$ 求解。

考虑如果只有一个集合怎么求。预处理出 $f_i$ 表示是 $i$ 倍数的 $a_j$ 的数量。考虑容斥，枚举 $x\mid y$，根据莫反公式可以得到答案是 $\sum_{x\mid y}\mu(\frac yx)(2^{f_y}-1)$。

考虑有两个集合，枚举 $x\mid y$，$x\mid z$，系数容易推得 $\mu(\frac yx)\mu(\frac zx)$。考虑方案数，对于 $\operatorname{lcm}(y,z)$ 的倍数的 $a_j$，显然只能放入其中一个或者不放入任何集合。此时，空集变得很麻烦。

我们先不考虑空集，最后将空集所计算的系数在原答案中扣除即可，这是容易的。

于是，我们的式子变为 $\sum_{x\mid y}\sum_{x\mid z}\mu(\frac yx)\mu(\frac zx)2^{f_y-f_{\operatorname{lcm}(y,z)}}2^{f_z-f_{\operatorname{lcm}(y,z)}}3^{f_{\operatorname{lcm}(y,z)}}$。

直接做显然是不行的，转化一下：$\sum_{x\mid y}\sum_{x\mid z}\mu(\frac yx)\mu(\frac zx)2^{f_y}2^{f_z}(\frac{3}{4})^{f_{\operatorname{lcm}(y,z)}}$。

我们发现后一项仅跟 $\operatorname{lcm}(y,z)$ 有关，且如果 $\operatorname{lcm}(y,z)>n$ 对应的 $f$ 值显然为 $0$。

于是，我们先求出 $\sum_{x\mid y}\sum_{x\mid z}\mu(\frac yx)\mu(\frac zx)2^{f_y}2^{f_z}$ 即 $(\sum_{x\mid y}\mu(\frac yx)2^{f_y})^2$，然后跑一遍 $f_yg_z\to h_{\operatorname{lcm}(y,z)}$ 的卷积（其实就是狄利克雷前缀和一遍再差分一遍，暴力做是 $O(\frac n x\ln\frac n x)$ 的，使用狄利克雷前缀和即可做到 $O(\frac n x\log\log\frac n x)$），对于所有 $(\frac{3}{4})^{f_{\operatorname{lcm}(y,z)}}$ 产生贡献的二元组 $(y,z)$ 补上一个 $((\frac{3}{4})^{f_{\operatorname{lcm}(y,z)}}-1)$ 的贡献系数即可。

总复杂度 $O(\sum_{x=1}^n\frac n x\ln\frac n x)$ 或 $O(\sum_{x=1}^n\frac n x\log\log\frac n x)$，分别为 $O(n\ln^2n)$ 及 $O(n\ln n\log\log n)$。

注意对空集的特殊讨论。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
const int mod=998244353;
inline void add(int &i,int j){
	i+=j;
	if(i>=mod) i-=mod;
}
int a[200005],f[200005];
int g[200005],pw2[200005],pw34[200005],h[200005];
int mu[200005],isp[200005],prm[200005],cnt;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	for(int i=2;i<=200000;i++) isp[i]=1; mu[1]=1;
	for(int i=2;i<=200000;i++){
		if(isp[i]) prm[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&prm[j]*i<=200000;j++){
			isp[i*prm[j]]=0;
			if(i%prm[j]==0){
				mu[i*prm[j]]=0;
				break;
			}
			mu[i*prm[j]]=mu[i]*-1;
		}
	}
	int n,ans=0; cin>>n;
	pw2[0]=1; for(int i=1;i<=n;i++) pw2[i]=pw2[i-1]*2%mod;
	pw34[0]=1; for(int i=1;i<=n;i++) pw34[i]=pw34[i-1]*249561089%mod;
	for(int i=1;i<=n;i++) cin>>a[i],f[a[i]]++;
	for(int i=1;i<=n;i++) for(int j=i*2;j<=n;j+=i) f[i]+=f[j];
	for(int i=1;i<=n;i++){
		int m=n/i;
		for(int j=1;j<=m;j++) g[j]=f[j*i];
		int tans=0,tmp=0,coef0=0;
		for(int j=1;j<=m;j++) h[j]=(mod+pw2[g[j]]*mu[j])%mod,add(tmp,h[j]),add(coef0,mu[j]);
		coef0=(mod+coef0)%mod;
		tans=tmp*tmp%mod;
		(tans+=mod-2*coef0*tmp%mod)%=mod;
		(tans+=coef0*coef0)%=mod;
		for(int j=m;j>=1;j--) for(int k=j*2;k<=m;k+=j) add(h[k],h[j]);
		for(int j=1;j<=m;j++) (h[j]*=h[j])%=mod;
		for(int j=1;j<=m;j++) for(int k=j*2;k<=m;k+=j) add(h[k],mod-h[j]);
		for(int j=1;j<=m;j++) (tans+=h[j]*(pw34[g[j]]-1))%=mod; 
		(ans+=tans*i)%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

一眼莫反。假设 $c_i=\sum_{j=1}^n[i|a_j]$。

枚举 $\gcd(A,B)=g$。答案即 $\sum_{g=1}^V g\sum_{x=1}^{\frac ng}\sum_{y=1}^{\frac ng}\mu(x)\mu(y)F(xg,yg)$。

其中 $F(x,y)$ 表示钦定 $x|\gcd(A),y|\gcd(B)$ 的方案数。假设 $l=\operatorname{lcm}(x,y)$。式子为则有 $F(x,y)=3^{c_l}2^{c_x+c_y-2c_l}-2^{c_x}-2^{c_y}+1$。

注意到 $l\leq V$ 的 $(x,y)$ 比较少，可以特殊处理。而 $l>V$ 时 $c_l=0$，则 $F(x,y)=(2^{c_x}-1)(2^{c_y}-1)$。

那么上面的式子转化为 $\sum_{g=1}^V g\sum_{x=1}^{\frac ng}\sum_{y=1}^{\frac ng}\mu(x)(2^{c_{xg}}-1)\mu(y)(2^{c_{yg}}-1)$。关于 $x,y$ 独立。

只需要计算 $\sum_{x=1}^{\frac ng}\mu(x)(2^{c_{xg}}-1)$ 即可。

---

## 作者：Erine (赞：0)

首先形式上显然只能对每个 $x$ 求出答案了，不然做不了。记 $b_x$ 为是 $x$ 倍数的数个数。

考虑容斥，钦定第一个集合的 $\gcd$ 是 $y$ 的倍数，第二个集合 $\gcd$ 是 $z$ 的倍数 ，那么根据经典反演有

$$ans_x=\sum_{x|y}\sum_{x | z}\mu\left(\dfrac yx\right)\mu\left(\dfrac zx\right)W(y,z)$$

考虑 $W(y,z)$ 如何计算。我们把数分成三类：

1. 是 $y$ 的倍数，且不是 $\operatorname{lcm}(y,z)$ 倍数，有 $b_y-b_{\operatorname{lcm}(y,z)}$ 个。这样的数可以选进第一个集合或者不选。
2. 是 $z$ 的倍数，且不是 $\operatorname{lcm}(y,z)$ 倍数，有 $b_z-b_{\operatorname{lcm}(y,z)}$ 个。这样的数可以选进第二个集合或者不选。
3. 同时是 $y,z$ 的倍数，有 $b_{\operatorname{lcm}(y,z)}$ 个。这样的数可以选进第一个集合，选进第二个集合，或者不选。

朴素计算应该会得到 $W(y,z)=2^{b_y-b_{\operatorname{lcm}(y,z)}}2^{b_z-b_{\operatorname{lcm}(y,z)}}3^{b_{\operatorname{lcm}(y,z)}}$，然而这是错的，因为我们并没有保证集合非空，我们实际上要求第一个和第二个集合都必须非空。

考虑暴力容斥掉，发现第一个集合为空的方案数是 $2^{b_z}$，第二个集合为空同理是 $2^{b_y}$，两个集合都为空的方案数是 $1$。所以我们可以得到：

$$
\begin{aligned}
W(y,z)&=2^{b_y-b_{\operatorname{lcm}(y,z)}}2^{b_z-b_{\operatorname{lcm}(y,z)}}3^{b_{\operatorname{lcm}(y,z)}}-2^{b_y}-2^{b_z}+1 \\
&=2^{b_y}2^{b_z}\left(\dfrac34\right)^{b_{\operatorname{lcm}(y,z)}}-2^{b_y}-2^{b_z}+1 
\end{aligned}
$$

拆成四个式子分别代入。$-2^{b_y}-2^{b_z}+1 $ 完全是好处理的，这个随便做。瓶颈在于 $2^{b_y}2^{b_z}\left(\dfrac34\right)^{b_{\operatorname{lcm}(y,z)}}$ 这一块东西。考虑计算出 $h_n=\sum_{x|y}\sum_{x|z}2^{b_y}2^{b_z}[\operatorname{lcm}(y,z)=n]$。显然，这是一个 $\operatorname{lcm}$ 卷积。先把卷积怎么做放放，考虑一些别的可能出现的问题。

我们发现 $\operatorname{lcm}(y,z)$ 的量级是平方，并且 $\operatorname{lcm}(y,z)>n$ 最后乘上的贡献是 $\left(\dfrac34\right)^0=1$，这不好！！！那么我们把整个贡献全部减去 $1$，也就是拆掉；在一开始计算出一倍 $2^{b_y}2^{b_z}$ 的贡献，这是好计算的；然后接下来 $\operatorname{lcm}(y,z)>n$ 的贡献就都是 $0$ 了，此时不必计算，也就是有效项数又变成了我们可以接受的范围。

接下来考虑卷积怎么做。假设我们要求 $h(x)=f(x)\times g(x)$，卷积是 $\operatorname{lcm}$ 卷积；我们构造 $F(n)=\sum_{d|n}f(d)$。有结论：

$$H(x)=F(x)\cdot G(x)$$

这里是点值对应相乘。然后我们根据莫比乌斯反演有 $f(n)=\sum_{d|n}\mu\left(\dfrac nd\right)F(n)$ 可以反演出 $h(x)$。单次卷积朴素调和级数是 $\Theta(n\ln n)$，使用狄利克雷前缀和是 $\Theta(n\ln\ln n)$。

我们对每个 $x$ 的问题规模是 $\dfrac nx$，所以总复杂度是 $\Theta(n\ln^2 n)$ 或者 $\Theta(n\ln n\ln\ln n)$，因为常数相当小所以两者都能通过。

```cpp
void fake_main() {
	n = read();
	rep(i, 1, n) ++a[read()];
	sieve();
	rep(i, 1, n) smu[i] = (smu[i - 1] + mu[i]) % mod;
	rep(i, 1, n) rep(j, 1, n / i) b[i] += a[i * j];
	pw1[0] = pw2[0] = 1;
	rep(i, 1, n) pw1[i] = pw1[i - 1] * 2 % mod, pw2[i] = (ll) pw2[i - 1] * base % mod;
	rep(x, 1, n) {
		int ans = (ll) smu[n / x] * smu[n / x] % mod;
		for (int y = x; y <= n; y += x) (ans += (mod - (ll) smu[n / x] * pw1[b[y]] % mod * mu[y / x] % mod) * 2 % mod) %= mod;
		int sum = 0;
		for (int y = x; y <= n; y += x) f[y] = (ll) mu[y / x] * pw1[b[y]] % mod, (sum += f[y]) %= mod;
		(ans += (ll) sum * sum % mod) %= mod;
		for (int y = x; y <= n; y += x) {
			for (int z = y; z <= n; z += y) (g[z] += f[y]) %= mod;
		}
		for (int y = x; y <= n; y += x) g[y] = (ll) g[y] * g[y] % mod;
		for (int y = x; y <= n; y += x) {
			for (int z = y; z <= n; z += y) (h[z] += (ll) mu[z / y] * g[y] % mod) %= mod;
		}
		for (int y = x; y <= n; y += x) (ans += (ll) h[y] * (pw2[b[y]] - 1) % mod) %= mod;
		for (int y = x; y <= n; y += x) f[y] = g[y] = h[y] = 0;
		(tot += (ll) ans * x % mod) %= mod;
	}
	write(tot);
}
```

---

## 作者：spdarkle (赞：0)

首先直接做 $\gcd$ 为定值的情况是不容易的，所以我们考虑容斥。

又因为，你钦定一个组的 $\gcd$ 是某个数的约数是容易的，但是同时钦定两组的 $\gcd$ 是某个相同数的约数，其容斥也会涉及到两组实际的 $\gcd$ 不同的状态，因此需要两组分别容斥。

设 $f(i,j)$ 表示钦定第一组的 $\gcd$ 是 $i$ 的约数，第二组的 $\gcd$ 是 $j$ 的约数的方案数之和。

根据莫比乌斯反演，$ans_i=\sum_{x=1}^{ix\le n}\sum_{y=1}^{iy\le n}f(ix,iy)\mu(x)\mu(y)$。

首先我们考虑 $f(i,j)$ 如何计算。

设 $cnt_i=\sum_{j=1}^n[i|a_j],t=\operatorname{lcm}(i,j)$，这些数字是可以公用于两组的，那么可以将条件容斥然后暴力计算：
$$
\begin{aligned}
f(i,j)&=\sum_{x=0}^{cnt_i-cnt_t}\sum_{y=0}^{cnt_j-cnt_t}\sum_{p=0}^{cnt_t}\sum_{q=0}^{cnt_t-p}[x+p>0\wedge y+q>0]{cnt_i-cnt_t\choose x}{cnt_j-cnt_t\choose y}{cnt_{t}\choose p+q}{p+q\choose q}\\
&=\sum_{x=0}^{cnt_i-cnt_t}\sum_{y=0}^{cnt_j-cnt_t}\sum_{p=0}^{cnt_t}\sum_{q=0}^{cnt_t-p}{cnt_i-cnt_t\choose x}{cnt_j-cnt_t\choose y}{cnt_{t}\choose p+q}{p+q\choose q}\\
&-\sum_{y=0}^{cnt_j-cnt_t}\sum_{q=0}^{cnt_t}{cnt_j-cnt_t\choose y}{cnt_t\choose p}\\
&-\sum_{x=0}^{cnt_i-cnt_t}\sum_{p=0}^{cnt_t}{cnt_i-cnt_t\choose x}{cnt_t\choose p}\\
&+1\\
&=3^{cnt_t}2^{cnt_i-cnt_t+cnt_j-cnt_t}-2^{cnt_t+cnt_j-cnt_t}-2^{cnt_t+cnt_i-cnt_t}+1\\
&=3^{cnt_t}2^{cnt_i+cnt_j-2cnt_t}-2^{cnt_i}-2^{cnt_j}+1
\end{aligned}
$$
然后考虑如何还原得到答案。

注意到值域与 $n$ 同级，那么 $\operatorname{lcm}(i,j)\le n$ 的对 $(i,j)$ 不超过 $O(n\ln^2 n)$ 个。

> 证明：
>
> 考虑枚举  $t$，统计  $\operatorname{lcm}(i,j)=t$ 的数对个数。
>
> 然后枚举  $t$ 的因子 $d$，将其作为 $\gcd(i,j)$，再枚举 $d$ 的倍数同时是 $t$ 的约数（本质上枚举 $\frac{t}{d}$ 的约数），根据 $\operatorname{lcm}(i,j)\gcd(i,j)=ij$，可以直接得到 $j$。
>
> 因此这里实质是在枚举约数的约数个数，也等价于枚举有多少个三元正整数组 $(x,y,z)$ 满足 $xyz\le n$，下面我们证明它不高于 $O(n\ln^2 n)$。
> $$
> \begin{aligned}
> &\sum_{x=1}^n\sum_{y=1}^{\lfloor\frac{n}{x}\rfloor}\sum_{z=1}^{\lfloor\frac{n}{xy}\rfloor}1\\
> =&\sum_{x=1}^n\sum_{y=1}^{\lfloor\frac{n}{x}\rfloor}\lfloor\frac{n}{xy}\rfloor\\
> \le &\sum_{x=1}^n\sum_{y=1}^{\lfloor\frac{n}{x}\rfloor}{ \frac{n}{xy}}\\
> \le &\left(\sum_{x=1}^{n}\frac{n}{x}\right)\left(\sum_{y=1}^{n}\frac{1}{y}\right)\\
> =&O(n\ln^2 n)
> \end{aligned}
> $$
> 这里仅仅保证了 $d|\gcd(i,j)$，因此多于所求，即证。
>
> 事实上从上述证明可以轻易推广到 $m$ 元正整数组 $(a_1,a_2\dots a_m),\prod_{i=1}^ma_i\le n$ 的正整数组不会超过 $O(n\ln^{m-1} n)$。

而 $t>n\implies cnt_t=0$。

且可以发现 $cnt_{\operatorname{lcm}(i,j)}=0$ 时，$f(i,j)=(2^{cnt_i}-1)(2^{cnt_j}-1)$，因此可以先 $O(n\ln n)$ 算出 $g_i=\left(\sum_{x=1}^{\lfloor\frac{n}{i}\rfloor}\mu(x)(2^{cnt_{ix}}-1)\right)^2$，然后想办法容斥掉非法贡献即可。

根据这样计算，非法的 $f(i,j)$ 共有不超过 $O(n\ln^2 n)$ 组，且 $f(i,j)$ 会被计算 $d(\gcd(i,j))$ 次，其中 $d$ 表示约数个数。

这等价于我们枚举四元组 $(a,b,c,d)$，来计算 $f(acd,bcd)$ 对 $ans_{c}$ 产生的贡献，同时要求 $\operatorname{lcm(acd,bcd)}=abcd\le n$，因此要求 $a,b$ 互质。

由于判断互质需要辗转相除法，因此可以先枚举 $a,b$ 并判断，再枚举 $c,d$ 进行计算。

根据上面的证明，这一步时间复杂度是 $O(n\ln^3 n)$。

[submission](https://codeforces.com/contest/2045/submission/300382867)

---

## 作者：Petit_Souris (赞：0)

起手拿到题目一看，欸这不是我们 [黎明前的巧克力](https://uoj.ac/problem/310) 吗！那我们改编一下集合幂级数，改成约数关系上的高位前缀和 / 差分一样做不就行了！手模一下发现爆了，原因是显然的，你会漏掉一些两边 $\gcd$ 不同的没有容斥掉。

既然如此，我们干脆对着这个限制容斥！比如我们现在统计两堆 $\gcd=g$ 的方案数。容斥，枚举两堆的 gcd 为 $xg$ 和 $yg$ 的倍数（注意这里不要求 $\gcd(x,y)=1$），系数为 $(3^{c_{g\operatorname{lcm}(x,y)}}2^{c_{xg}+c_{yg}-2c_{g\operatorname{lcm}(x,y)}}-2^{c_{xg}}-2^{c_{yg}}+1)\mu(x)\mu(y)$，其中 $c_i$ 表示 $a$ 序列中 $i$ 的倍数数量。里面那个式子表示 lcm 的倍数随便放，剩下随便一边或扔掉，还要减去空的情况。

现在直接枚举 $x,y$ 的复杂度为 $\mathcal O(\frac{n^2}{g^2})$，无法接受。但是我们观察到，当 $g\operatorname{lcm}(x,y)>n$ 时，其 $c$ 必为 $0$，因此贡献为 $2^{c_{xg}+c_{yg}}-2^{c_{xg}}-2^{c_{yg}}+1)\mu(x)\mu(y)$，这时候 $x,y$ 竟然独立了，可以化简成 $(2^{c_{xg}}-1)\mu (x)\cdot (2^{c_{yg}}-1)\mu(y)$，容易 $\mathcal O(\frac{n}{g})$ 计算了。

对于 $g\operatorname{lcm}(x,y)<n$ 的情况，熟知符合要求的 $(x,y)$ 数对只有 $\mathcal O(\frac{n}{g}\log ^2 \frac{n}{g})$ 个（实际上相当于枚举三个数乘积不超过 $\frac{n}{g}$），因此暴力枚举即可。时间复杂度 $\mathcal O(n\log^3 n)$ 或 $\mathcal O(n\log ^4 n)$（如果检验时多花了一次 gcd）。总之把 $\mu=0$ 的跳掉之后完全不满，可以稳稳通过。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline","unroll-loops")
#include<bits/stdc++.h>
#define debug(x) cerr<<(#x)<<": "<<x<<endl
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
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
const ll N=2e5+9,Mod=998244353;
ll n,a[N],pr[N],prc,mu[N];
ll f[N],g[N],h[N];
ll pw2[N],pw3[N];
bool vis[N];
int mygcd(int a,int b){
	int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=az>bz?bz:az,diff;
	b>>=bz;
	while(a){
		a>>=az,diff=b-a;
		az=__builtin_ctz(diff);
		if(a<b)b=a;
		a=diff<0?-diff:diff;
	}
	return b<<z;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    mu[1]=1;
    rep(i,2,n){
        if(!vis[i])pr[++prc]=i,mu[i]=-1;
        rep(j,1,prc){
            if(pr[j]*i>n)break;
            vis[pr[j]*i]=1;
            if(i%pr[j]==0){
                mu[pr[j]*i]=0;
                break;
            }
            mu[pr[j]*i]=-mu[i];
        }
    }
    rep(i,1,n)a[i]=read(),f[a[i]]++;
    rep(i,1,prc){
        per(j,n/pr[i],1){
            if(f[j*pr[i]])f[j]+=f[j*pr[i]];
        }
    }
    pw2[0]=pw3[0]=1;
    rep(i,1,n+1)pw2[i]=pw2[i-1]*2%Mod,pw3[i]=pw3[i-1]*3%Mod;
    rep(i,1,n){
        ll sm=0;
        for(ll j=i;j<=n;j+=i){
            if(!mu[j/i])continue;
            sm=(sm+(pw2[f[j]]-1)*mu[j/i]);
        }
        sm=(sm%Mod+Mod)%Mod;
        g[i]=sm*sm%Mod;
    }
    rep(g,1,n){
        rep(cg,1,n/g){
            rep(x,1,n/g/cg){
                if(!mu[x*cg])continue;
                rep(y,1,n/g/cg/x){
                    if(!mu[y*cg])continue;
                    if(mygcd(x,y)>1)continue;
                    ll L=x*y*cg*g,X=x*g*cg,Y=y*g*cg;
                    ll coef=((pw3[f[L]]*pw2[f[X]+f[Y]-2*f[L]]-pw2[f[X]]-pw2[f[Y]]+1)*mu[x*cg]*mu[y*cg]-(pw2[f[X]]-1)*(pw2[f[Y]]-1)*mu[x*cg]*mu[y*cg]);
                    h[g]=(h[g]+coef)%Mod;
                }
            }
        }
    }
    ll ans=0;
    rep(i,1,n){
        ll wys=(g[i]+h[i])%Mod;
        ans=(ans+wys*i)%Mod;
    }
    write((ans+Mod)%Mod),putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

