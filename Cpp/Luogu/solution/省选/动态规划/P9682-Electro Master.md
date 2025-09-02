# Electro Master

## 题目背景

I might be wrong.

## 题目描述

考虑一个由四种微观粒子构成的系统：正负 A 子 $\text{a}^+,\text{a}^-$，正负 B 子 $\text{b}^+,\text{b}^-$。

一开始，一条直线上放置了 $n$ 个 A 子；然后以某种方式给粒子以初速度，使得带正电荷的粒子向左，反之则向右运动。我们忽略粒子之间的相互作用，认为粒子在加速后速率一定，且均沿直线运动。

当两个粒子相撞时，粒子会反弹，沿着相反的方向继续运动。同时满足如下的变换规律：

- 若两种粒子的电荷相同，则无事发生；
- 若两种粒子的电荷不同，则改变成另一种同电荷的粒子。

例如：$\text{a}^-$ 和 $\text{b}^+$ 相撞后，$\text{a}^-$ 会变成 $\text{b}^-$，$\text{b}^+$ 会变成 $\text{a}^+$，并各自沿着相反的方向运动。

定义一种摆放方式的权值为，经过足够长的时间后，在左侧收集到的 B 子个数。

现在已经确定了一些 A 子的正负性，剩下的 A 子可能带正电，也有可能带负电。请求出对于所有可能方案的权值之和。

你需要将答案对 $998\,244\,353$ 取模。

## 说明/提示

#### 样例 1 解释

有两种可能的填法：`+++-` 或 `+-+-`。其权值分别为 $0,1$，所以最终的答案即为 $1$。

### 数据规模与约定

对于所有数据，保证 $1\le n\le 2000$，$s_i\in \{\texttt{+},\texttt{-},\texttt{?}\}$。

| # | $n\le $ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| 0 | - | 样例 | $0$ |
| 1 | $100$ | $s$ 中没有 `?` | $10$ |
| 2 | $100$ | - | $20$ |
| 3 | $300$ | $s$ 中 `?` 不超过 $15$ 个 | $15$ |
| 4 | $300$ | - | $20$ |
| 5 | - | - | $35$ |


## 样例 #1

### 输入

```
+?+-```

### 输出

```
1```

## 样例 #2

### 输入

```
??+-?-+```

### 输出

```
11```

## 样例 #3

### 输入

```
-????-?+?--????```

### 输出

```
2523```

# 题解

## 作者：5ab_juruo (赞：17)

感觉是一个，比较套路的题目？

根据经典结论，向左的粒子个数等于正粒子个数，相邻两个粒子的碰撞次数等于缝隙左侧的负粒子个数。你可以直接 dp 了，但感觉不如算贡献。

枚举 $i-1,i,i+1$ 粒子的正负性，若 $i$ 对答案有贡献，则要求满足以下条件：

- 正粒子至少要有 $i$ 个；
- 左右有效碰撞次数为奇数。

可以进一步分类讨论。若左右粒子正负性相同，则发现当且仅当 `+-+` 情况一定有贡献（左右碰撞一定为奇数次），否则就一定没有贡献。对于两侧不同的情况，枚举左侧正粒子的个数（要满足某个奇偶性），乘上后面选 `+` 可能的情况即可。

要特判开头和 $n=1$ 的情况，不用判结尾是因为一定不会产生贡献。或者在开头加一个 `+` 避免这部分讨论。

预处理组合数后缀和可做到 $O(n^2)$。

```cpp
const int max_n = 2e3 + 1, mod = 998244353;
using mint = mod_int<mod>;

mint sm[max_n + 1][max_n + 1];
int qc[max_n + 1], pc[max_n + 1], nc[max_n + 1];

const vector<int> S[3] = { {0}, {1}, {0, 1} };
inline const vector<int>& P(int x) { return x == '+' ? S[0] : (x == '-' ? S[1] : S[2]); }

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	string s;
	
	cin >> s;
	s = "+" + s;
	n = ssz(s);
	
	initfac(n);
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
			sm[i][j] = C(i, j);
		for (int j = i; j > 0; j--)
			sm[i][j - 1] += sm[i][j];
	}
	for (int i = 0; i < n; i++)
	{
		qc[i + 1] = qc[i] + (s[i] == '?');
		pc[i + 1] = pc[i] + (s[i] == '+');
		nc[i + 1] = nc[i] + (s[i] == '-');
	}
	
	mint ans = 0;
	for (int i = 1; i < n - 1; i++)
		for (int pr : P(s[i - 1]))
			for (int c : P(s[i]))
				for (int nx : P(s[i + 1]))
				{
					if (pr == nx)
					{
						if (pr == 0 && c == 1)
							ans += sm[qc[n] - qc[i + 2] + qc[i - 1]][max(0, i + 1 - (pc[n] - pc[i + 2] + pc[i - 1] + 2))];
						continue;
					}
					int odd = (pr == 0 || c == 1) ^ (nc[i - 1] & 1), dv = (c == 0) + 1;
					for (int j = odd; j <= qc[i - 1]; j += 2)
						ans += C(qc[i - 1], j) * sm[qc[n] - qc[i + 2]][max(0, i + 1 - (qc[i - 1] - j + pc[i - 1] + dv + pc[n] - pc[i + 2]))];
				}
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：Raymondzll (赞：8)

## P9682 Electro Master

以下为赛时做法。但我赛时出了一个小问题导致大样例怎么也过不去。赛后一发过了。与标程想法不太一样，给大家参考。

### 解题思路

拿到题目知道是思维转化加 DP 题。那我们先来看怎么简化模型。

观察 1：电性是固有的属性，而粒子种类是由过程决定的。

观察 2：一个粒子只会和其左右粒子相撞，换言之，粒子相对位置不变。

观察 3：每发生一次有效（电性不同的粒子）碰撞，两个参与碰撞的粒子种类 switch 一下。

由以上，我们发现，一个粒子最后的种类和两个量有关：它自己电性和左右电性的异同，它和左右的碰撞次数。有效碰撞次数为奇数的会变成 B 粒子。

观察 4：向左运动的粒子总数不变。

观察 5：最后向左运动的粒子都在最左侧。

所以如果每个粒子电性已知，那最后运动方向也已知。但怎么分别计算和左边、右边的碰撞次数呢？我们需要模拟一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/ucoo2xzb.png)

手画图。红色表示碰撞。

## 观察 6：相邻间隙中的碰撞次数最多差 1。

原因：考虑这个弯弯绕绕的 S 形，容易证明这个结论。

观察 7：这个差由初始方向和结束方向决定。

由此我们知道了一个确定电性下的做法：确定了（其实就是数出了）末尾向左的粒子个数，从头开始对比初始方向、结束方向加一减一，然后按照观察 3 后写的判断是 A 还是 B。

**在之后我将以“边”代替两个粒子之间的碰撞数，“格子”代替粒子方向。1 代表向左，0 向右。由于有无贡献只和奇偶性相关，1、0 也代表奇、偶。**

考虑一个 $O(n^2)$ 的 DP。记 $dp_{i,j}$ 为假设总共有 $i$ 个正粒子，并且前 $i$ 个粒子中有 $j$ 个设定为正电的总贡献（左侧收集到的 B 粒子数）

为了转移我想到的是加更多变量辅助转移。由于“贡献”由多个变量决定，我记录了三个量：$p$ 为格子值，$q$ 为边权，$r$ 为半边的有效碰撞数（记录 $r$ 是因为只靠半边没办法确定是否有贡献），三者都是 01 值。

![](https://cdn.luogu.com.cn/upload/image_hosting/xsx73v6n.png)

考虑转移。首先 $q'=p\oplus q\oplus 1$，根据观察 7 及推论，由于有贡献的粒子最后肯定向左，因此如果初始向左对边权没有改变，向右（$p=0$）会边权取反。因此有上式。

有效需要边权为 $1$ 且两边的格子初始方向不同。$r'=q'\&(p\oplus t)$。

我们写出了 $dp_{i,j,t,p',r'}=dp_{i,j-t,p,q,r}+r\oplus r'$ 这个式子。然后我赛时天真地止步于此，大样例测出 2061。人崩溃了。

注意到 dp 数组其实不是一种贡献，而是多种贡献的和。只要是前 $i$ 个里 $j$ 个正的都算进来了。没什么好的解决办法，就加了一个计数的数组 k，每次转移 k 并进来，并且用小的 k 乘上 $r\oplus r'$。

$Ans=\sum\limits_{i,j}(\sum\limits_{p,q,r}dp_{i,j,p,q,r})\times \dbinom{\text{i之后的?数}}{\text{i-1-j-(i之后的+数)}}$

那个组合数我思考了一会儿。由于 $dp_i$ 是没算上 $i$ 这个位置的贡献的，所以这里借 $dp_{i,j,p,q,r}$，来表示前 $i-1$ 个最终为正的贡献。因此有一个减一。请读者仔细思考。

然后不用为 $n$ 个全正担心。这样的话没有碰撞，也就没有贡献。

也不用为全负担心，都往右边动，自然没贡献。

跑的不错，单点150ms。

```cpp
#include <bits/stdc++.h>
#define fr(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long ll;
int n;string s;
ll f[2010][2010][2][2][2],k[2010][2010][2][2][2];
ll sufque[2010],sufplu[2010];
const int M=998244353;
bool tru(int i){return s[i]=='+'||s[i]=='?';}
bool fal(int i){return s[i]=='-'||s[i]=='?';}
ll ksm(ll a,ll b){ll res=1;while(b){if(b&1)(res*=a)%=M;(a*=a)%=M;b>>=1;}return res;}
ll fac[2010],inv[2010];
void init(){
    fac[0]=1;for(int i=1;i<=2000;i++)fac[i]=fac[i-1]*i%M;
    inv[2000]=ksm(fac[2000],M-2);for(int i=2000;i>=1;i--)inv[i-1]=inv[i]*i%M;
}
ll C(ll x,ll y){
    if(y<0||y>x||x<0)return 0;
    if(y==0||y==x)return 1;
    return fac[x]*inv[y]%M*inv[x-y]%M;
}
int main(){
	init();
	cin>>s;n=s.size();s=" "+s;
	for(int i=n;i>=1;i--){
		sufque[i]=sufque[i+1];
		sufplu[i]=sufplu[i+1];
		if(s[i]=='?')sufque[i]++;
		if(s[i]=='+')sufplu[i]++;
	}
	if(tru(1))k[1][1][1][0][0]=1;
	if(fal(1))k[1][0][0][0][0]=1;
	fr(i,2,n)fr(j,0,i)
		fr(p,0,1)fr(q,0,1)fr(r,0,1)
			fr(t,0,1){
				if(t&&(!j||!tru(i)||!k[i-1][j-1][p][q][r]))continue;
				if(!t&&(!fal(i)||!k[i-1][j][p][q][r]))continue;
				int b=p^q^1,g=b&(p^t);
				(f[i][j][t][b][g]+=f[i-1][j-t][p][q][r]+(r^g)*k[i-1][j-t][p][q][r])%=M;
				(k[i][j][t][b][g]+=k[i-1][j-t][p][q][r])%=M;
			}
//	for(int i=1;i<=n;i++){
//		for(int j=0;j<=i;j++){
//			cout<<i<<" "<<j<<" | ";
//			fr(p,0,1)fr(q,0,1)fr(r,0,1)cout<<f[i][j][p][q][r]<<" ";cout<<endl;
//		}
//	}
	ll F=0;
	fr(i,2,n)fr(j,0,i-1){
		ll tmp=0;fr(p,0,1)fr(q,0,1)fr(r,0,1)(tmp+=max(0ll,f[i][j][p][q][r]))%=M;
		(F+=tmp*C(sufque[i+1],i-1-j-sufplu[i+1]))%=M;
	}
	cout<<F;
	return 0;
}
```

---

## 作者：Little_RMQ (赞：5)

赛时基本想出来怎么做了，但是细节很多也没有仔细做就放弃了。

首先考虑怎么 $O(n)$ 处理已知序列。

先引出两个结论:

- #### 向右移动序列的长度为负粒子数。
- #### 相邻两个粒子且其中一个粒子最后产生贡献的碰撞次数等于缝隙左侧的负粒子个数。

下面先证明这两个结论:

- 1.首先我们容易发现，最后肯定是从序列中间分开左边全部向左，右边全部向右，我们考虑模拟这个过程，当一个向右的序列遇到一个向左移动的例子，会使序列的最后一个元素弹出向左运动，而原本向左的粒子加入序列，此时序列长度不变，而若遇到向右的粒子则序列长度增加 1 ，由此可发现所有的正粒子不会影响向右的序列长度，因此向右序列长度为负粒子数，**该命题也等价于向左移动序列长度为正粒子数**。

- 2.由(1)的过程我们容易发现，每一个最后向左的粒子都会在序列中与前后粒子各碰撞自己在序列中的位置次后离开队列(与右边粒子碰撞次数比左边多1)，而其在序列中的位置其实就是左边的负粒子数(因为左边的正粒子不会影响序列长度不影响相对位置)，因此结论2也是对的。

#### 注意：这里只针对于最后向左运动的粒子，如果最后它向右运动则碰撞次数由右侧正粒子决定这里就不讨论了。

在我们知道这两个结论之后，我们就可以通过预处理出前缀的负粒子数和后缀的正粒子数来线性求解答案。

**此时搭配上爆搜可获得 Sub1 和 Sub3 的分数。**

接下来我们考虑如何改成正解，这里介绍我赛时想到的一种拆贡献的做法(好像有DP做法但是我不会)。

我们对于序列中的每个粒子单独考虑，考虑其最后会在哪些序列中对答案造成贡献。

首先由于我们刚才已经会怎么算出其碰撞次数了，因此我们只需要考虑一个粒子前面正，负粒子的个数即可知道它是否会产生贡献了。

对于 $i$ 粒子，它会产生贡献时需要满足的条件如下:

**- 至少有 $i$ 个正粒子 (这是为了保证其最后会向左运动)。**

**- 与不同粒子碰撞次数为奇数 (这是为了保证其最后为B型粒子)。**

同时我们容易发现的时，条件二只于其相邻两个粒子有关，而条件一也可以通过枚举其前方正粒子数从而算出后面至少放多少正粒子而满足。

所以我们要枚举 $S_{i-1}$， $S_i$， $S_{i+1}$ 分别是什么，然后计算哪些序列会对答案造成贡献，即可完成此题。

我们讲8种情况对应需要的奇偶性分别讨论，如下：

|+++|++-|+--|+-+|---|--+|-++|-+-|
|-|-|-|-|-|-|-|-|
|-1|1|2|3|0|1|1|0|

其中 $-1$ 表示永远不会贡献， $1$ 表示前面需要的正粒子个数为奇数，$2$ 表示前面需要的正粒子个数为偶数， $3$ 表示一定会产生贡献。

接下来就可以预处理组合数以及组合数的后缀和，因为最后右边的正粒子数只需要大于一个值而没有上限，因此可以处理后缀和，来做到 $O(n^2)$ 算答案。

由于用这个 $8$ 种情况的表来写代码非常复杂，所以本人代码~~抄袭~~**参考**了一点 5ab_juruo 的写法。

代码如下（温馨提示：别直接复制代码o.O）。

```cpp
#include"bits/stdc++.h"
#define int long long
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pii pair<int,int>
#define fir first
#define sec second
#define bp __builtin_popcount
using namespace std;
ll read() {
	ll x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-10;
const int N = 2e3 + 5;
const int M = 10;
const int V = 3e6;
const int mod = 998244383;
const int bse = 1e9 + 7;
const int inf = 1e18;
const double pi = acos(-1);
string s;

/* init */
int fac[N], ifac[N];
#define C(n,m) (fac[n] * ifac[m] % mod * ifac[m-n] % mod)
int s1[N], s2[N], s3[N];
int sc[N][N];
void init(int n) {
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = pow(fac[n], mod - 2);
	for(int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
	for(int i = 0; i < n; i++) {
		s1[i + 1] = s1[i] + (s[i] == '?');
		s2[i + 1] = s2[i] + (s[i] == '+');
		s3[i + 1] = s3[i] + (s[i] == '-');
	}
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= i; j++) sc[i][j] = C(i, j);
		for(int j = i; j; j--) (sc[i][j - 1] += sc[i][j]) %= mod;
	}
}
/* init */

int n;

bool ok(int x, char c) {
	if(c == '?') return 1;
	if(x == 1 && c != '+') return 0;
	if(x == 2 && c != '-') return 0;
	return 1;
}
signed main() {
	cin >> s;
	s = '+' + s;
	n = s.size();
	init(n);
	int ans = 0;
	for(int i = 1; i < n - 1; i++)
		for(int pr = 1; pr <= 2; pr++)
			if(ok(pr, s[i - 1]))
				for(int nw = 1; nw <= 2; nw++)
					if(ok(nw, s[i]))
						for(int nt = 1; nt <= 2; nt++)
							if(ok(nt, s[i + 1])) {
								if(pr == nt) {
									if(pr == 1 && nw == 2) (ans += sc[s1[n] - s1[i + 2] + s1[i - 1]][max(0ll, i + 1 - (s2[n] - s2[i + 2] + s2[i - 1] + 2))]) %= mod;
									continue;
								}
								int fir = (pr == 1 || nw == 2) ^ (s3[i - 1] & 1), dlt = (nw == 1) + 1;
								for(int j = fir; j <= s1[i - 1]; j += 2) (ans += C(s1[i - 1], j) * sc[s1[n] - s1[i + 2]][max(0ll, i + 1 - (s1[i - 1] - j + s2[i - 1] + dlt + s2[n] - s2[i + 2]))] % mod) %= mod;
							}
	printf("%lld\n", ans % mod);
	return 0;
}
```

---

## 作者：Acoipp (赞：2)

## 分析

万万没想到。

这道题目需要用到两个结论：

- 设初始向左有 $i$ 个粒子，那么从左往右第 $1 \sim i$ 个粒子最终往左；剩下的粒子最终往右。 

证明：任意时刻两个粒子的相对位置不会改变，而如果不考虑粒子的编号，那么相遇后掉头可以看作互相穿过，于是最后一定会分成 $i,n-i$ 两段，一段向左，一段向右，得证。

- $i$ 号粒子和 $i+1$ 号粒子的碰撞次数等于 $1 \sim i$ 号粒子中向右的粒子数量。

证明：设向左的粒子权值为 $1$，向右的粒子权值为 $-1$，考虑任意时刻从左往右粒子的权值形成的序列，那么每一次相遇都会令一个 $-1$ 往右移动一位，考虑每个粒子被经过了多少次，即可得到上述结论。

于是我们可以得到 $i$ 号粒子产生贡献当且仅当正粒子数量大于等于 $i$ 个并且它和相邻且正负不同的粒子碰撞次数不是 $2$ 的倍数就可以了。（撞一次变成 $\texttt{B}$，再撞一次又变回 $\texttt{A}$）

所以设 $f_{i,j,a,b,c}$ 表示前 $i$ 个粒子有 $j$ 个负粒子，并且 $s_{i-1}=a,s_i=b,s_{i+1}=c$ 的方案数量。（$1$ 代表正，$0$ 代表负，$0 \le a,b,c \le 1$）

转移的时候枚举 $s_{i+2}$ 是多少就可以了，这一部分时间复杂度 $O(n^2)$。

考虑统计答案，对于一个状态 $f_{i,j,a,b,c}$ 我们已经知道了 $s_{1 \sim i+1}$ 的信息，不知道的是 $s_{i+2 \sim n}$。对于第二个条件，即 $i$ 号粒子和相邻且正负不同的粒子碰撞次数不是 $2$ 的倍数，这个可以根据 $a,b,c$ 轻松得出，不知道的是整个序列正粒子的数量，于是我们预处理后缀 $\texttt{?}$ 和 $\texttt{+}$ 的个数，然后通过组合数+前缀和计算方案就可以得到 $i$ 号粒子对于整个答案的贡献。

同时，还有一些边界情况需要判断，可以令第 $0$ 个粒子为正粒子，这样的话就不需要分类讨论了。

总的时间复杂度是 $O(n^2)$。

## 代码

实现比较容易，思维难度较高。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2005
#define mod 998244353
using namespace std;
ll n,i,j,a1,a2,a3,a4,f[N][N][2][2][2],suf1[N],suf2[N],C[N][N],sum[N][N],a[N],ans;
char s[N];
inline bool c(ll pos,ll val){return a[pos]==val||a[pos]==-1;}
int main(){
	ios::sync_with_stdio(false);
	cin>>(s+1),n=strlen(s+1);
	if(n==1){
		cout<<0<<endl;
		return 0;
	}
	s[0]='+',s[n+1]='-';
	for(i=0;i<=n+1;i++){
		if(s[i]=='+') a[i]=1;
		if(s[i]=='-') a[i]=0;
		if(s[i]=='?') a[i]=-1;
	}
	for(i=n;i>=1;i--) suf1[i]=(suf1[i+1]+(s[i]=='+'));
	for(i=n;i>=1;i--) suf2[i]=(suf2[i+1]+(s[i]=='?'));
	C[0][0]=1;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			if(i) C[i][j]+=C[i-1][j];
			if(i&&j) C[i][j]+=C[i-1][j-1];
			if(C[i][j]>=mod) C[i][j]-=mod;
		}
		for(j=n;j>=0;j--) sum[i][j]=(sum[i][j+1]+C[i][j])%mod;
	}
	for(a1=0;a1<=1;a1++){
		for(a2=0;a2<=1;a2++){
			for(a3=0;a3<=1;a3++){
				if(c(0,a1)&&c(1,a2)&&c(2,a3)) f[1][(a1==0)+(a2==0)][a1][a2][a3]=1;
			}
		}
	}
	for(i=1;i<n;i++){
		for(j=0;j<=i;j++){
			for(a1=0;a1<=1;a1++){
				for(a2=0;a2<=1;a2++){
					for(a3=0;a3<=1;a3++){
						for(a4=0;a4<=1;a4++){
							if(!c(i-1,a1)||!c(i,a2)||!c(i+1,a3)||!c(i+2,a4)) continue;
							f[i+1][j+(a3==0)][a2][a3][a4] = (f[i+1][j+(a3==0)][a2][a3][a4]+f[i][j][a1][a2][a3])%mod;
						}
						ll sums = (j-(a2==0))*(a2!=a1)+j*(a3!=a2);
						if(sums%2==1){
							ll least = max(0ll,j-(a3==1));
							least = max(0ll,least-suf1[i+2]);
							ans=(ans+sum[suf2[i+2]][least]*f[i][j][a1][a2][a3])%mod;
						}
					}
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：tobie (赞：0)

好题，NOIP考前写个题解涨一波RP（

首先，对于这个问题，我们可以发现如下性质：

1. 两个粒子的**相对位置**不会改变。
2. 最终**左侧收集到的粒子总数量**与**电荷为正的粒子数量**相等。
3. 粒子 $i$ 与粒子 $i+1$ 的**撞击次数**与 $0\sim i$ 中的**电荷为负的粒子数量**相等。

基于如上性质我们便有了一种在 $O(n)$ 内得出单个方案的权值的算法。

这是一道计数问题，考虑 dp 与排列组合，由于每一个粒子的最终左右情况比较难在跑 dp 时直接确定，所以我们考虑**对每一个粒子分别计算贡献**。

不妨令 `s[0]='+',[n+1]='-'`，省去烦人的边界问题。

我们记 $dp_{i,j,x,y,z}$ 表示当前考虑到粒子 $i$，下标在 $[0,i]$ 内的粒子中有 $j$ 个电荷为正，$s_{i-1}=x$，$s_{i}=y$，$s_{i+1}=z$ 的情况数量。

那么对于粒子 $i$，如果它是一个最终会向左运动的 B 粒子，就需要满足如下两个条件：

1. 最终序列中有至少 $i+1$ 个正粒子（我们把第 $0$ 号位置的粒子也算上）。
2. 这个粒子的碰撞次数为奇数。

第二个条件可以用 dp 状态判断，至于第一个条件，我们考虑到如果只把目光聚焦于 $i$ 粒子，则编号在 $[i+2,n]$ 的**未知电荷的粒子**是可以随意设定而不改变贡献，所以可以通过预处理组合数与**未知电荷的粒子**、**电荷为正的粒子**的后缀个数来维护进行计算。

具体细节详见代码。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long
const int N=2009,mod=998244353;
char s[N];
int n,dp[N][N][2][2][2];
int c[N][N],sum[N][N],cnt[N],cnt0[N];
void gx(int &x,int y){x+=y;while(x>=mod) x%=mod;}
bool pd(char x,int y){return x=='?'||((x=='+'&&y==1)||(x=='-'&&y==0));}
int js(int x,int y){return (y>x||x<0)?0:sum[x][max(y,0ll)];}//choose at least y balls in x balls.
signed main()
{
	scanf("%s",s+1);n=strlen(s+1);
	s[0]='+',s[n+1]='-';
	for(int i=0;i<=n;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
		for(int j=i;j>=0;j--) sum[i][j]=(sum[i][j+1]+c[i][j])%mod;
	}
	for(int i=n;i>=1;i--) cnt[i]=cnt[i+1]+(s[i]=='?'),cnt0[i]=cnt0[i+1]+(s[i]=='+');
	for(int x=0;x<=1;x++)
	for(int y=0;y<=1;y++)
	if(pd(s[1],x)&&pd(s[2],y)) dp[1][1][1][x][y]=1;
	for(int i=1;i<n;i++)
	for(int j=1;j<=i;j++)
	for(int x=0;x<=1;x++)
	for(int y=0;y<=1;y++)
	for(int z=0;z<=1;z++)
	for(int w=0;w<=1;w++)
	if(pd(s[i-1],x)&&pd(s[i],y)&&pd(s[i+1],z)&&pd(s[i+2],w)&&dp[i][j][x][y][z])
	gx(dp[i+1][j+y][y][z][w],dp[i][j][x][y][z]);
	int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	for(int x=0;x<=1;x++)
	for(int y=0;y<=1;y++)
	for(int z=0;z<=1;z++)
	if(pd(s[i-1],x)&&pd(s[i],y)&&pd(s[i+1],z)&&dp[i][j][x][y][z])
	{
		int cnt1=i-j,cnt2=i-j+(y^1);
		int qwq=cnt1*(x^y)+cnt2*(y^z);
		if(qwq&1) gx(ans,dp[i][j][x][y][z]*js(cnt[i+2],i-j-cnt0[i+2]-y-z+1)%mod);
	}
	printf("%lld",ans);
}
```

---

## 作者：Corzica (赞：0)

首先观察这种粒子碰撞的性质。

我们可以将向右侧的粒子当成一个序列，先后拿向左的粒子去撞击这个序列。

每次这样的撞击之后，原序列最左侧的粒子会向左移动离开这个序列，而新粒子会在原序列的最右侧加入。

我们还可以看到，粒子最终是 A 子还是 B 子，取决于所撞击序列中的电荷，而每一个粒子只会和序列中左侧和右侧的粒子进行若干次撞击，粒子的电荷又无法改变。

于是我们便可以枚举每一个粒子及其左右侧粒子的初始电荷，再预处理以下两个值：

**进序列前有 $x$ 个粒子的方案数**与**进序列后有 $x$ 个粒子前来撞击的方案数**。

于是我们就可以再枚举进序列前的电子个数，根据以上两个值计算出会有贡献的情况个数，即可完成本题。

时间复杂度 $O(n^2)$。

代码如下（很丑，常数很大）。
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
string s;
int n;
ll jie[2005], inv[2005], f[2005][2005], g[2005][2005];//f数组为预处理的第一个值,g数组为预处理的第二个值
const ll mod = 998244353;
ll ksm(ll p, ll q) {
	ll base = 1;
	while (q) {
		if (q & 1) base = base * p % mod;
		q >>= 1;
		p = p * p % mod;
	}
	return base;
}
inline vector<int> gs(char s) {
	if (s == '-') return vector<int> {0};
	if (s == '+') return vector<int> {1};
	return vector<int> {0, 1};
}
inline ll getf(int p, int q, int w) {
	if (p == 0) return f[p][q];
	if (s[p] == '?') {
		if (w == 0) {
			return f[p - 1][q - 1];
		} else {
			return f[p - 1][q];
		}
	} else {
		return f[p][q];
	}
}
inline ll getg(int p, int q, int w) {
	if (p == n + 1) return g[p][q];
	if (s[p] == '?') {
		if (w == 1) {
			return g[p + 1][q - 1];
		} else {
			return g[p + 1][q];
		}
	} else {
		return g[p][q];
	}
}//要注意这两个get处的细节
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	n = s.size();
	s = '+' + s;
	s = s + '+';
	jie[0] = 1;
	for (int i = 1; i <= n; i++) {
		jie[i] = jie[i - 1] * i % mod;
	}
	inv[n] = ksm(jie[n], mod - 2);
	for (int i = n - 1; i >= 0; i--) {
		inv[i] = (inv[i + 1] * (i + 1) % mod);
	}
	f[0][0] = g[n + 1][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			if (s[i] == '?') {
				f[i][j] = f[i - 1][j];
				if (j) f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
			} else if (s[i] == '-') {
				if (j)f[i][j] = f[i - 1][j - 1];
			} else {
				f[i][j] = f[i - 1][j];
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j <= n - i + 1; j++) {
			if (s[i] == '?') {
				g[i][j] = g[i + 1][j];
				if (j) g[i][j] = (g[i][j] + g[i + 1][j - 1]) % mod;
			} else if (s[i] == '+') {
				if (j)g[i][j] = g[i + 1][j - 1];
			} else {
				g[i][j] = g[i + 1][j];
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = n; j >= 0; j--) {
			g[i][j] = (g[i][j] + g[i][j + 1]) % mod;
		}
	}
	ll ans = 0, p, q, x, y;
	for (int i = 1; i <= n; i++) {
		for (auto u : gs(s[i - 1])) {
			for (auto v : gs(s[i])) {
				for (auto w : gs(s[i + 1])) {
					p = (u != v), q = (v != w);
					for (int j = (u == 0); j < i; j++) {
						if ((j * p + (j + (v == 0)) * q) % 2 == 1) {
							ans += getf(i - 1, j, u) * getg(i + 1, j + (v == 0), w) % mod;
							ans %= mod;
						}
					}
				}
			}
		}
	}
	cout << ans;
}
```

---

