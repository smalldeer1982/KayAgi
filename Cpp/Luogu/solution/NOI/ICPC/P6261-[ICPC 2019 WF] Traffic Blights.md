# [ICPC 2019 WF] Traffic Blights

## 题目描述

Main 街坐落在一条东西向的直线上，上面有若干位置互异的红绿灯。每个红绿灯以某个固定周期在红绿之间循环。更具体地，它会先持续 $r$ 秒的红灯，再持续 $g$ 秒的绿灯，再持续 $r$ 秒的红灯...如此往复。对于不同的红绿灯，$r$ 和 $g$ 的值可能不同。在时刻 $0$，所有的红绿灯都恰好刚变为红灯。

假设此时有一辆“理想”汽车在前 $2019!$ 秒中的一个随机实数时刻神秘地出现在了 Main 街的最西端，向东以 $1~ \rm m/s$ 龟速行驶，直到遇到第一个红灯时停下，那么它有多大的概率通过所有红绿灯？如果它停下来了，那么它在每个红绿灯处停下的概率有多大？

## 样例 #1

### 输入

```
4
1 2 3
6 2 3
10 2 3
16 3 4```

### 输出

```
0.4
0
0.2
0.171428571429
0.228571428571```

## 样例 #2

### 输入

```
6
4 1 5
9 8 7
13 3 5
21 5 7
30 9 1
2019 20 0```

### 输出

```
0.166666666667
0.466666666667
0.150000000000
0.108333333333
0.091666666667
0.016666666667
0.000000000000```

# 题解

## 作者：tzc_wk (赞：8)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P6261)

首先不难发现周期是 $M=\text{lcm}(r_1+g_1,r_2+g_2,r_3+g_3,\cdots,r_n+g_n)$​​​​，也就是说问题等价于求从 $[0,M-1]$​​​​ 任选一个数 $X$​​​​，满足 $\forall i\in[1,n],(X+x_i)\bmod (r_i+g_i)\ge g_i$​​​​ 的概率。

考虑一种特殊情况：$r_i+g_i$ 两两互质，根据 CRT 的知识可以证明，对于 $\forall\{a_n\},0\le a_i<r_i+g_i$，都可以找到一个序列 $X$ 满足 $(X+x_i)\bmod (r_i+g_i)=a_i$，换句话说，对于任意序列 $\{a_n\}$，满足 $\forall i,(X+x_i)\bmod (r_i+g_i)=a_i$ 的概率都是相同的，为 $\prod\limits_{i=1}^n\dfrac{g_i}{r_i+g_i}$。因此总概率就可以直接按 $\prod\limits_{i=1}^n\dfrac{g_i}{r_i+g_i}$ 来计算。

考虑将普遍的情况转化为这种情况，由于 $r_i+g_i\le 100$，因此每个数最多只有一个 $>10$ 的质因子。这样，我们取 $V=2^6·3^4·5^2·7^2=6350400$，然后将每个 $[0,M-1]$ 中的数写成 $kV+b(b<V)$ 的形式。考虑枚举 $b$，这样根据同余论，如果我们把 $k$ 当作变量，那么 $kV+b\bmod (r_i+g_i)$ 的周期为 $\dfrac{r_i+g_i}{\gcd(r_i+g_i,V)}$。显然，由于 $2^7>100,3^5>100,5^3>100,7^3>100$，$\dfrac{r_i+g_i}{\gcd(r_i+g_i,V)}$ 肯定不含质因子 $2,3,5,7$。故这个数要么为 $1$，要么为 $>10$ 的质数。如果我们把大小相同的周期当作一类，那么不同类之间周期长度肯定是两两互质的。这样我们再对于每一类周期长度 $l$，实时维护有多少个 $\bmod l$ 的位置是合法的，设为 $c_l$，那么对于这种情况合法的概率就是 $\prod\limits_{l}\dfrac{c_l}{l}$，实时维护一下即可，时间复杂度 $6350400·n·(r_i+b_i)$，无法通过。

继续优化。事实上，我们其实并不一定要让所有周期都是质数。我们发现如果一个周期是另一个周期的幂，那么我们将小的周期自动与大的周期对齐也可以转化为上一种情况，因此我们也可以取合适的 $V$ 使得 $\dfrac{r_i+g_i}{\gcd(r_i+g_i,V)}$ 都是质数或质数的幂，取 $V=\text{lcm}(1,2,3,\cdots,10)$ 即可。这样复杂度就降到了 $2520·n·(r_i+b_i)$。

```cpp
const int MAXN = 500;
const int MAXV = 100;
int n, x[MAXN + 5], r[MAXN + 5], g[MAXN + 5];
bool able[MAXN + 5][MAXV + 5];
double p[MAXN + 5];
int getmax(int x) {return (x == 2) ? 8 : ((x == 4) ? 8 : ((x == 3) ? 9 : x));}
void calc(int x) {
	p[0] += 1; double prd = 1; static bool die[MAXV + 5][MAXV * 5 + 5];
	memset(die, 0, sizeof(die));
	for (int i = 1; i <= n; i++) {
		int cnt = 0, tot = 0;
		int d = __gcd(2520, r[i] + g[i]), md = (r[i] + g[i]) / d;
		int rst = getmax(md), mul = rst / md;
		for (int j = 0; j < md; j++) for (int k = 0; k < mul; k++) {
			if (!die[rst][j + k * md]) {
				if (able[i][(j * 2520 + x) % (r[i] + g[i])]) cnt++;
				else die[rst][j + k * md] = 1;
				tot++;
			}
		}
		if (!tot) break;
		prd = 1.0 * prd * cnt / tot;
		p[i] += prd;
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &x[i], &r[i], &g[i]);
	for (int i = 1; i <= n; i++) for (int j = r[i]; j < r[i] + g[i]; j++)
		able[i][(j - x[i] % (r[i] + g[i]) + r[i] + g[i]) % (r[i] + g[i])] = 1;
	for (int i = 0; i < 2520; i++) calc(i);
	for (int i = 0; i <= n; i++) p[i] /= 2520;
	for (int i = 1; i <= n + 1; i++) printf("%.10lf\n", p[i - 1] - p[i]);
	return 0;
}
/*
4
0 15 49
0 13 19
0 33 63
0 27 53
*/
```



---

## 作者：zhylj (赞：8)

转化为求通过前 $i$ 个红绿灯的概率，即相当于求满足若干形如 $x \not \equiv a \pmod {r_i+g_i}$ 限制的 $x$ 的方案数。

记 $m_i = r_i + g_i$，则整条街的周期是 $\operatorname{lcm}(m_1,m_2,\cdots, m_n)$。考虑一个简单的问题，若 $m_i$ 两两互质，则任取 $x \equiv a \pmod {m_i}$，$x \equiv b \pmod {m_j}$，总有唯一的 $\bmod \operatorname{lcm}(m_i,m_j)$ 意义下的解，故所有 $m_i$ 的概率互相独立。

考虑假如任取 $m_i,m_j$ 要么互质，要么其中一个是另外一个的倍数，则可以把 $m_i$ 分为若干个互相独立的类，对于一类的 $m_i$，考虑暴力将其变成最大的 $m_i$ 中的若干段区间，然后暴力维护，这样就可以做到 $\mathcal O(n \max m_i)$ 的复杂度。

考虑一般的情况如何转化为以上的情况，我们枚举出发时间 $\bmod$ 某个提前设定好的正整数 $M$ 的值 $c$。之后新的时间 $t$ 对应这原来的时间 $c+t\cdot M$，则原先每个红绿灯的周期 $m_i$ 变为 $\dfrac {\operatorname{lcm}(M,m_i)}{M} = \dfrac {m_i}{\gcd(M,m_i)}$.

假如我们让所有 $\dfrac {m_i}{\gcd(M,m_i)}$ 要么两两互质，要么是倍数关系，我们就可以算了。考虑这样的情况必然除完之后是 $1$ 或质数的次幂。可算得最小的 $M = 2^3\times 3^2\times 5\times 7 = 2520$.

时间复杂度 $\mathcal O(Mn \max m_i)$.

```cpp
const int kN = 5e2 + 5, kM = 8 * 9 * 5 * 7;
const ff kEps = 1e-9;

int Gcd(int a, int b) { return b ? Gcd(b, a % b) : a; }

int n, m[kN]; bool block[kN][kN], vis[kN][kN]; ff p[kN], tp[kN], vp[kN];

int GetkMax(int x) {
	if(x == 2 || x == 4) return 8;
	if(x == 3) return 9;
	return x;
}
void Calc(int r) {
	memset(vis, false, sizeof(vis));
	tp[0] = 1;
	for(int i = 1; i <= n; ++i) tp[i] = 0;
	for(int i = 1; i <= 100; ++i) vp[i] = 1;
	for(int i = 1; i <= n; ++i) {
		int v = GetkMax(m[i] / Gcd(kM, m[i]));
		if(tp[i - 1] < kEps) break;
		tp[i] = tp[i - 1] / vp[v];
		for(int k = 0; k < v; ++k) {
			int cur = r + k * kM;
			if(block[i][cur % m[i]] && !vis[v][k]) {
				vp[v] -= 1.0 / v;
				vis[v][k] = true;
			}
		}
		tp[i] *= vp[v];
	}
	for(int i = 0; i <= n; ++i)
		p[i] += tp[i];
}

int main() { 
	rd(n);
	for(int i = 1; i <= n; ++i) {
		int x, r, g; rd(x, r, g);
		m[i] = r + g;
		for(int j = 0; j < r; ++j)
			block[i][(j - x % m[i] + m[i]) % m[i]] = true;
	}
	for(int i = 0; i < kM; ++i) Calc(i);
	for(int i = 0; i <= n; ++i) p[i] /= kM;
	for(int i = 0; i <= n; ++i) {
		printf("%.9lf\n", p[i] - p[i + 1]);
	}
	return 0;
}
```

---

## 作者：win114514 (赞：5)

### 思路

考虑题目要求的是什么。

假设 $p_i$ 代表通过前 $i$ 个红绿灯的概率。

那么我们的答案即为 $p_i-p_{i-1}$。

不妨设 $w_i=r_i+g_i$。

我们的限制条件类似：

$$t\not \equiv a_i\pmod w_i$$

那么所有红绿灯会形成周期 $\operatorname{lcm}(w_1,w_2,\cdots,w_n)$。

由于 $2019!$ 肯定是这个数的倍数。

所以我们只需要算这个周期内的概率。

考虑一种特殊情况。

假如任意 $\gcd(w_i,w_j)=1$，也就是 $w_i$ 全部互质的情况下。

此时 $\operatorname{lcm}(w_1,w_2,\cdots,w_n)=\prod w_i$。

我们的 $t$ 在每一个模 $w_i$ 都可以取任意的值。

也就是每个红绿灯的概率是独立的。

总概率只需要将每个的概率相乘就可以得到。

当 $w_i$ 不互质怎么办。

我们可以让 $t$ 有一些特殊性质。

我们设定大模数 $I$，令 $t=k\times I + b~(b<I)$。

那么我们的每个红绿灯就不再是每 $w_i$ 一轮了。

添加了 $t$ 的限制后，周期变为了 $\operatorname{lcm}(I,w_i)$。

在我们枚举 $b$ 的时候，周期还会平均分配到每一种上即 $\frac{lcm(I,w_i)}{I}$。

考虑 $\frac{lcm(I,w_i)}{I}=\frac{w_i}{\gcd(I,w_i)}$。

我们可以让变换后的数互质。

想要做到这一点，$I$ 至少得是 $2^6\times 3^4\times 5^2\times 7^2=6350400$。

复杂度为 $O(6350400\times n\times w_i)$。

这肯定是接受不了的。

但是我们还可以做到的条件是什么。

假如一组数中，两两都互为倍数，且组与组之间都互质。

这是的概率在组之间也是相对独立的。

而组内的概率也只需要把小的补大就可以了。

最简单的分组就是把 $w_i$ 保留成质数的幂。

那么 $I$ 就只需要是 $2^3\times 3^2\times 5\times 7=2520$ 即可。

时间复杂度为 $O(2520\times n\times w_i)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int M = 110;
const int I = 2520;

int n, x[N], r[N], g[N], w[N];
int v[N][M];
int f[M][M << 3];
double p[N];

inline auto mod(int x, int y) { return (x % y + y) % y; }
inline void sol(int x) {
  p[0] += 1;
  double res = 1;
  memset(f, 0, sizeof f);
  for (int i = 1; i <= n; i++) {
    int up = 0, dw = 0, d = g[i], t = r[i];
    for (int j = 0; j < d; j++)
      for (int k = 0; k < t / d; k++) {
        if (!f[t][j + k * d]) {
          dw++;
          if (v[i][(j * I + x) % w[i]] == 1) up++;
          if (v[i][(j * I + x) % w[i]] == 0) f[t][j + k * d] = 1;
        }
      }
    if (!dw) break;
    p[i] += (res = res * up / dw);
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> x[i] >> r[i] >> g[i], w[i] = r[i] + g[i];
  for (int i = 1; i <= n; i++)
    for (int j = r[i]; j < w[i]; j++) v[i][mod(j - x[i], w[i])] = 1;
  for (int i = 1; i <= n; i++) g[i] = w[i] / __gcd(I, w[i]);
  for (int i = 1; i <= n; i++) r[i] = (g[i] == 2 || g[i] == 4) ? 8 : g[i] == 3 ? 9 : g[i];
  for (int i = 0; i <  I; i++) sol(i);
  for (int i = 0; i <= n; i++) p[i] /= I;
  for (int i = 1; i <= n + 1; i++) printf("%.9lf\n", p[i - 1] - p[i]);
  return 0;
}
```

---

## 作者：Acoipp (赞：2)

题意可以转化为求通过前 $i$ 个红绿灯的概率，设其为 $p_i$，在第 $i$ 个红绿灯停下的概率就是 $p_{i-1}-p_i$。

再思考一下发现题意可以转化为随机一个变量 $x$，其中 $x$ 的范围为 $1 \sim \operatorname{lcm}(1,2,\dots,100)$，满足若干方程 $x \not\equiv r_i \pmod {c_i}$，其中 $1 \le c_i \le 100$。

如果 $c_i$ 互质，那么对于每个方程其不合法的概率是可以分开算然后乘起来的，比如 $x \not\equiv 3,5 \pmod 6$，那么 $x$ 满足上述式子的概率就是 $\frac 46=\frac 23$，最后把所有 $c_i$ 的概率乘起来即可。

但是不巧，$c_i = 1 \sim 100$，并不互质，考虑让它变得互质，发现一个小于等于 $100$ 的数中，最多含有一个大于 $10$ 的质数因子，于是我们考虑把小于等于 $10$ 的质数因子都消掉，这样就转化为了 $c_i$ 互质的情况。

具体的，设 $V=2^63^45^27^2$，随机变量 $x$ 等于 $pv+q(0 \le q<v)$，当我们枚举 $q$ 的时候，把 $p$ 看作变量，对于一个红绿灯，它的周期就不是 $r_i+g_i$ 而是 $\frac{r_i+g_i}{\gcd(r_i+g_i,V)}$ 了，因为 $V$ 包含了 $1 \sim 100$ 内所有非 $10$ 以上质数因子，所以周期一定是大于 $10$ 的质数，对相同的周期合并计算就可以转化为 $c_i$ 互质的情况。

这么做有一个不好，就是时间复杂度无法保障，但是我们可以发现，除了互质，如果互相整除似乎也可以处理，只需要将小的循环节复制若干份跟大的循环节贴合即可。

于是我们需要找到一个 $S$ 使得对于 $x \in [1,100]$ 都满足 $\frac{x}{\gcd(S,x)}$ 是质数的若干次幂即可，取 $S=2520$ 就是最小的满足条件的数，时间复杂度为 $O(SVn)$，其中 $V = \max(r_i+g_i)$。

> $S$ 可以看作 $2^3 \times 3^2 \times 5 \times 7$，如果存在一个 $p$，$p$ 含有大于 $10$ 的质因子，那么 $\frac p{\gcd(p,S)}$ 一定是一个大于 $10$ 的质数；否则设 $p=2^a3^b5^c7^d$，有一种情况，就是当 $a>3$ 并且 $b>2$ 的时候 $\frac p{\gcd(p,S)}$ 才有可能含有多个质因子，但是 $2^{a+1}>10,3^{b+1}>10$，$p$ 显然不合法，其他情况同理。
>
> 上述是 $S$ 的寻找过程。

代码如下，仅供参考：

```cpp
#include<bits/stdc++.h>
#define ll int
#define db double
#define N 505
using namespace std;
ll n,i,j,k,x[N],r[N],g[N],len[N],len2[N],maps[N][N],cnt[N][N],cntt[N],vis[N];
db ans[N],temp[N];
inline void solve(ll id){
	for(ll i=1;i<=100;i++){
		vis[i] = 0;
		for(ll j=0;j<i;j++) cnt[i][j]=1;
		cntt[i]=i;
	}
	temp[0] = 1;
	for(ll i=1;i<=n;i++) len[i] = (r[i]+g[i])/__gcd(r[i]+g[i],2520),vis[len[i]] = len[i];
	for(ll i=100;i>=1;i--) for(ll j=i;j<=100;j+=i) vis[i]=max(vis[i],vis[j]);
	for(ll i=1;i<=n;i++) len2[i] = vis[len[i]];
	for(ll i=1;i<=n;i++){
		temp[i] = temp[i-1],len[i] = len2[i];
		for(ll j=0;j<len[i];j++){
			if(!maps[i][(j*2520+id)%(r[i]+g[i])]){
				if(cnt[len[i]][j]){
					cnt[len[i]][j]=0,temp[i]/=cntt[len[i]];
					cntt[len[i]]--,temp[i]*=cntt[len[i]];
				}
			}
		}
	}
	for(ll i=0;i<=n;i++) ans[i]+=temp[i];
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(i=1;i<=n;i++) cin>>x[i]>>r[i]>>g[i];
	for(i=1;i<=n;i++) for(j=0;j<r[i]+g[i];j++) if((x[i]+j)%(r[i]+g[i])>=r[i]) maps[i][j]=1;
	for(i=0;i<2520;i++) solve(i);
	cout<<fixed<<setprecision(12);
	for(i=0;i<=n;i++) ans[i]/=2520;
	for(i=1;i<=n+1;i++) cout<<ans[i-1]-ans[i]<<endl;
	return 0;
}
```

---

## 作者：Starlight237 (赞：1)

> (**2021集训队作业 P6261 【[ICPC2019 WF]Traffic Blights】**)有 n 个红绿灯，第 i 个灯在位置 $x_i$，$r_i$ 秒红灯和 $g_i$ 秒绿灯交替变换，0 时刻所有灯都处于绿灯到红灯的交界点。现在随机选择一个时间点从位置 0 开始以 1 的速度前进，求每个灯是第一个遇到的红灯的概率以及一个红灯都没遇到的概率。$n\le500,r_i+g_i\le100$。

首先，"第一次遇到第 i 个红灯" 的概率等于 "通过前 i−1 个信号灯" 的概率减去 "通过前 i 个信号灯" 的概率

然后一个灯的周期显然就是 $r_i+g_i$，考虑所有灯的 LCM $M$，若两辆车出现的时间模 M 相同，则这两辆车遇到的每个信号灯状态都相同。从而可以考虑枚举 $0,1,...,M-1$ 作为出发时间模 M 的余数。但 M 过大，显然会 `TLE`。

考虑寿司晚宴那道题的技巧，对于 100 以内的任何一个数，至多含有一个大素数因子（大素数定义为超过 10 的素数）。重新令 $M=2^6\times3^4\times5^2\times7^2=6350400$，考虑枚举出发时间模 M 的余数。我们定义 $f_{i,j,k}$ 表示第 i 个灯在 $kM+j(k<\dfrac T{\gcd(T,M)})$ 时间是否为绿灯，考虑到 k 较小（不超过 100），可以用一个 `__int128` 压缩起来。若 $T|M$，这个灯所有的情况都是固定的，容易处理。否则设一个灯的周期为 $T=2^a3^b5^c7^ds$，$\gcd(s,M)=1$，或者说 $s=\dfrac T{\gcd(T,M)}$，易见 $j,j+M,j+2M,...,j+(s-1)M$ 构成了模 s 的完全剩余系，故枚举了 j 后，可以将一个灯等效地看作周期为 s （一个大素数）的灯。下面的讨论都基于 j 固定的情况（最外层枚举 j）。

此时若两个灯的周期互素，则它们的概率互不影响，可以直接相乘作为同时通过的概率。而等效后周期全为素数，故两个周期要么互素，要么相同。

我们首先将 $f_{i,j}$ 视为一个集合 $\{k|f_{i,j,k}=1\}$，下面考虑如何求出等效周期都相同且为 p 的一组灯。设全集为 $U$。设这组灯按照出现顺序依次为 $l_1,...,l_t$，那么 $l_i$ 被通过的概率即为 $P(l_1)P(l_2)...P(l_{j-1})\dfrac{|f_{l_i,j}|}{|U\cap f_{l_1,j}\cap...\cap f_{l_i,j-1}|}$（条件概率公式）。

但是这样做依然会 `TLE`。

我们注意到一个关键的性质，如果一个灯在周期内并不是红红红……绿绿绿，而是红红绿绿……红红绿绿……这样，其实上面的算法也是可以处理的。因此若一个灯周期为 $T$，我们将它的周期延伸为 $kT$ 后，依然能够处理。因此为了满足条件“两个灯的周期要么互素要么相同”，不需要上面如此苛刻的条件（全为素数），是素数的幂也可以（若 $T_1=p^u,T_2=p^v$，我们将 $T_1$ 和 $T_2$ 中较小者延伸成较大者即可。否则 $T_1$ 和 $T_2$ 互素。）

于是为了使 $\dfrac T{\gcd(T,M)}$ 为素数的幂，我们只需要取 $M$ 为不超过 10 的所有数的 LCM 即可，即 $M=2520$。这样一来，容易证明 100 以内所有可能的周期代入后算得的新周期都是素数的幂。这样一来，枚举量已经降低到可以快速 AC 的程度了。

```cpp
#define ull unsigned long long
#define u128 unsigned __int128
const int N = 510, P = 2520, pri[] = {1, 5, 7, 8, 9, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
const u128 al = -1ull, all = (u128)-1;
int popcnt(u128 x) {return __builtin_popcountll(*(ull*)&x) + __builtin_popcountll(((ull*)&x)[1]);}
vector<int> vec[101];
int n, x[N], T[N];
u128 f[N][101];
double p[N], ans[N];
int main() {
	n = rd();
	for (int i = 1; i <= n; ++i) {
		int _x = rd(), r = rd(), g = rd();
		x[i] = _x, T[i] = r + g;
		int _T = T[i] / __gcd(T[i], P);
		if (!(_T & 1)) _T = 8; if (_T % 3 == 0) _T = 9;
		vec[_T].push_back(i);
		for (int j = 0, tmp = P % T[i] - T[i]; j < T[i]; ++j)
			for (int k = j, l = 0; l < _T; k += tmp, k += k >> 31 & T[i], ++l)
				f[i][j] |= (u128)(k >= r) << l;
	}
	for (int i = 0; i < P; ++i) {
		for (int j = 0; j <= n; ++j) p[j] = 1.;
		for (int j = 0; j < 26; ++j) {
			int pr = pri[j], tot = pr, c;
			u128 sta = ~(all << pr);
			for (int lmp : vec[pr]) {
				c = popcnt(sta &= f[lmp][(i + x[lmp]) % T[lmp]]);
				p[lmp] *= (double)c / tot, tot = c;
				if (!tot) break;
			}
		}
		ans[0] += p[0];
		for (int i = 1; i <= n; ++i) ans[i] += p[i] *= p[i - 1];
	}
	double div = 1. / P;
	for (int i = 0; i <= n; ++i) ans[i] *= div;
	for (int i = 0; i <= n; ++i)
		printf("%lf\n", ans[i] - ans[i + 1]);
	return 0;
}
```

---

