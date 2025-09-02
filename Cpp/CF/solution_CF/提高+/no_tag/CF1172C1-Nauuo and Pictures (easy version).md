# Nauuo and Pictures (easy version)

## 题目描述

简单版和困难版的唯一区别在于数据范围。

Nauuo 是一个喜欢随机图片网站的女孩。

有一天，她自己做了一个包含 $n$ 张图片的随机图片网站。

当 Nauuo 访问该网站时，她会看到且只会看到一张图片。网站展示每张图片的概率并不相等。第 $i$ 张图片有一个非负权值 $w_i$，第 $i$ 张图片被展示的概率为 $\frac{w_i}{\sum_{j=1}^n w_j}$。也就是说，图片被展示的概率与其权值成正比。

然而，Nauuo 发现有些她不喜欢的图片被展示得太频繁了。

为了解决这个问题，她想出了一个好办法：每当她看到一张喜欢的图片时，就将其权值加 $1$；否则，将其权值减 $1$。

Nauuo 将访问该网站 $m$ 次。她想知道所有 $m$ 次访问后，每张图片的期望权值是多少（对 $998244353$ 取模）。你能帮帮她吗？

第 $i$ 张图片的期望权值可以表示为 $\frac{q_i}{p_i}$，其中 $\gcd(p_i, q_i) = 1$。你需要输出一个整数 $r_i$，满足 $0 \le r_i < 998244353$ 且 $r_i \cdot p_i \equiv q_i \pmod{998244353}$。可以证明这样的 $r_i$ 存在且唯一。

## 说明/提示

在第一个样例中，如果唯一的一次访问展示了第一张图片，概率为 $\frac{2}{3}$，最终权值为 $(1, 1)$；如果展示了第二张图片，概率为 $\frac{1}{3}$，最终权值为 $(2, 2)$。

所以，两张图片的期望权值都是 $\frac{2}{3} \cdot 1 + \frac{1}{3} \cdot 2 = \frac{4}{3}$。

因为 $332748119 \cdot 3 \equiv 4 \pmod{998244353}$，所以你需要输出 $332748119$，而不是 $\frac{4}{3}$ 或 $1.3333333333$。

在第二个样例中，只有一张图片是 Nauuo 喜欢的，所以每次访问时 $w_1$ 都会加 $1$。

所以期望权值为 $1 + 2 = 3$。

Nauuo 很调皮，所以她没有给出第三个样例的提示。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
0 1
2 1
```

### 输出

```
332748119
332748119
```

## 样例 #2

### 输入

```
1 2
1
1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 3
0 1 1
4 3 5
```

### 输出

```
160955686
185138929
974061117
```

# 题解

## 作者：LCuter (赞：3)

考虑 DP，我们发现概率的计算牵涉三个值，一个是不喜欢的图片的权值和，一个是喜欢的图片的权值和，还有一个是本身的权值。

我们记初始时喜欢的权值和是 $W_a$，不喜欢的权值和是 $W_b$，当前的是 $W'_a,W'_b$，一次操作会使得 $W_a'$ 加一或是 $W_b'$ 减一。

对于一张图片，我们在意的并非其编号，而是其初始权值，同时其它图片也可以看作两大类而无需分析，于是令 $F(w,i,a,b)$  表示一个权值为 $w$ 的且被喜欢的图片，经过 $i$ 次操作，$W_a'=a,W_b'=b$ 时的期望权值，为了计算概率，我们选择在操作序列前插入一个操作，而非在操作序列后插入一个操作，那么一共有三种转移来源：

- 选到自己，概率为 $\frac{w}{a+b}$，从 $F(w+1,i-1,a+1,b)$ 转移过来；
- 选到喜欢的图片但不是自己，概率为 $\frac{a-w}{a+b}$，从 $F(w,i-1,a+1,b)$ 转移过来；
- 选到不喜欢的图片，概率为 $\frac{b}{a+b}$，从 $F(w,i-1,a,b-1)$ 转移过来。

所以有：
$$
F(w,i,a,b)=\frac{w}{a+b}F(w+1,i-1,a+1,b)+\frac{a-w}{a+b}F(w,i-1,a+1,b)+\frac{b}{a+b}F(w,i-1,a,b-1)
$$
复杂度过高，需要优化。

发现 $w$ 这一维很恶心，可以去掉它吗？

经过观察，我们惊人地发现 $F(w,i,a,b)=wF(1,i,a,b)$！

证明可以使用归纳法。

那么我们令 $F(i,a,b)$ 表示原来的 $F(1,i,a,b)$，就有：

$$F(i,a,b)=\frac{1}{a+b}((a+1)F(i-1,a+1,b)+bF(i-1,a,b-1))$$

初值 $F(0,a,b)=1$，最后要求的是 $F(m,W_a,W_b)$。

我们观察 $F(m,W_a,W_b)$ 会从哪里转移过来，也就是有效的状态是哪些，可以发现后两维的变化量之和就等于第一维的变化量，而且随着第一维减少一，可能是第二维增加一，或者是第三维减少一。

我们新搞一个 $F^*(a,b)$ 表示第二维和第三维的相较于 $W_a$ 与 $W_b$ 的变化量，那么我们知道 $F^*(a,b)=F(m-a-b,W_a+a,W_b-b)$。

记 $W=W_a+a+W_b-b$，于是有转移：
$$
F^*(a,b)=\frac{1}{W}((W_a'+1)F(a+1,b)+W_b'F(a,b+1))
$$
类似的令 $G^*(a,b)$ 表示不喜欢的图片，有转移：
$$
G^*(a,b)=\frac{1}{W}((W_b'+1)G(a,b+1)+W_a'G(a+1,b))
$$
初值 $\forall a+b=m,F^*(a,b)=G^*(a,b)=1$，最终需要 $F^*(0,0),G^*(0,0)$。

时间复杂度 $O(n+m^2\log P)$，其中 $P=998244353$。

---

## 作者：紊莫 (赞：2)

非常好大便题，所以蒟蒻提供一个复杂度为 $\mathcal{O}(nm^3)$ 的比较好写的做法。

---

首先，遇到概率期望类的问题，考虑 DP 解决，E1 的难点在于状态的定义，因为 $n$ 很小，所以考虑对于每张照片分别计算答案，现在考虑对于一张照片怎么算答案。

首先进行操作的次数是一定要记录的，然后我们要能计算概率，我们需要知道某个数的值和所有数字的和，为了计算某个数的值，我们需要把对于某个数字的操作次数记录下来，所有数字的值你可以选择直接记录和值，但是和值的范围可能是 $nw$ 的，状态有点多，但是我们发现，你只要记录加一的次数即可，减的次数就是总次数减去加的次数，然后就能反推出和值。

为了方便，下文记一个元素所在的块，表示和这个元素 $a_i$ 相同的所有元素。

综上，我们有状态 $f_{i,j,k}$ 表示操作了 $i$ 次，在当前块加了 $j$ 次，在自己身上加了 $k$ 次的概率。

初始状态，$f_{0,0,0} = 1$。

转移有三种，第一种是选到了另一个块，第二个是选到了自己这块（**但不是自己**），第三种是选到了自己，此处采用正向转移，否则每次都要算概率会非常烦。

```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;

const int N = 55, mod = 998244353;
int n, m, sum, sx, sy, a[N], w[N], f[N][N][N];
int inv(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) res = res * a % mod;
  return res;
}
void add(int &x, int y) {
  if ((x += y) > mod) x -= mod;
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  F(i, 1, n) cin >> a[i];
  F(i, 1, n) cin >> w[i];
  F(i, 1, n) {
    sum += w[i];
    if (a[i]) sx += w[i];
    else sy += w[i];
    if (!a[i]) a[i] = -1;
  }
  F(t, 1, n) {
    f[0][0][0] = 1;
    int res = 0;
    F(i, 0, m - 1) {
      F(j, 0, i) {
        F(k, 0, j) {
          int S = sum + a[t] * (j - (i - j)), I = inv(S), now = w[t] + a[t] * k,
              ka = ((a[t] > 0 ? sx : sy) + j * a[t]), kb = S - ka;
          add(f[i + 1][j][k], f[i][j][k] * kb % mod * I % mod);
          add(f[i + 1][j + 1][k + 1], f[i][j][k] * now % mod * I % mod);
          add(f[i + 1][j + 1][k], f[i][j][k] * (ka - now) % mod * I % mod);
        }
      }
    }
    F(j, 0, m) F(k, 0, j) add(res, (w[t] + a[t] * k) * f[m][j][k] % mod);
    cout << res << endl;
    memset(f, 0, sizeof f);
  }
  return 0;
}
```

代码我一开始实现了 140 多行非常恶心，后来经过反复重构，精细一点可以在 50 行以内通过，因此写篇题解希望造福后人！

---

## 作者：Hoks (赞：1)

## 前言
我真的不会高复杂度的 dp 啊/ll。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
$n,m,V\le50$ 都很小，那我们只需要考虑保证正确性就行了。

直接考虑 dp。

我们的 dp 需要维护的就是当前已经操作次数，喜好的总权值，讨厌的总权值和位置。

具体的，定义 $f_{i,j,l,r}$ 为对于数 $i$，操作了 $j$ 次，讨厌的被选择次数为 $l$，喜欢的被选择次数为 $r$ 的概率。

那么对于边界情况有 $f_{i,0,0,0}=1,i\in[1,n]$。

然后我们考虑 dp 转移。

枚举当前总共操作了 $j$ 次，位置 $p$，操作在位置 $p$ 上 $i$ 次。

此时喜好的和不喜好的总权值已经固定了，枚举一个另一个就可以算出来了。

然后我们用 $f_{p,i,l,r}$ 去转移别的值。

首先定义 $w_p,a_p$ 分别为 $p$ 这张图片的初始权值和是/否喜欢，$s_0$ 是讨厌的总权值，$s_1$ 是喜欢的总权值。

这时分为 $3$ 种情况：
1. 选择了数 $i$。
2. 选择了非 $i$ 的讨厌的图片。
3. 选择了非 $i$ 的喜欢的图片。

写成转移方程就是（$f$ 表示是否喜欢，$s_0$ 是讨厌总权值，$s_1$ 是喜欢总权值，$w$ 为权值 $\Delta$，$t$ 为更新后的权值）：

$$f_{p,i+1,l+!f,r+f}\leftarrow f_{p,i,l,r}\times \frac{t}{s_0+s_1-l+r}$$
$$f_{p,i,l+1,r}\leftarrow f_{p,i,l,r}\times \frac{s_0-l-!f\cdot w}{s_0+s_1-l+r}$$
$$f_{p,i,l,r+1}\leftarrow f_{p,i,l,r}\times\frac{s_1+r-f\cdot t}{s_0+s_1-l+r}$$

最后计算答案对每种照片遍历一下可能的所有操作方案就行了。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=50+10,V=1e6,M=1e6+10,INF=1e9+10,mod=998244353;
int n,m,a[N],w[N],s[N],inv[M],f[N][N][N][N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='('||c==')'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int ksm(int x,int y,int mod)
{
    int res=1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
inline void solve()
{
	n=read();m=read();for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) w[i]=read(),s[a[i]]+=w[i];
	for(int i=1;i<=n;i++) f[i][0][0][0]=1;
	for(int j=0;j<m;j++) for(int p=1;p<=n;p++)
		for(int i=0;i<=j;i++) for(int l=0,r=j;l<=j;l++,r--)
		{
			if(!f[p][i][l][r]) continue;int t=w[p]+(a[p]?i:-i);if(!t&&!a[p]) continue;
			f[p][i+1][l+!a[p]][r+a[p]]=(f[p][i+1][l+!a[p]][r+a[p]]+f[p][i][l][r]*t%mod*inv[s[0]+s[1]-l+r]%mod)%mod;
			f[p][i][l+1][r]=(f[p][i][l+1][r]+f[p][i][l][r]*(s[0]-l-!a[p]*t)%mod*inv[s[0]+s[1]-l+r]%mod)%mod;
			f[p][i][l][r+1]=(f[p][i][l][r+1]+f[p][i][l][r]*(s[1]+r-(a[p]==1)*t)%mod*inv[s[0]+s[1]-l+r]%mod)%mod;
		}
	for(int i=1,ans=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++) for(int l=0,r=m;l<=m;l++,r--)
		{
			int t=w[i]+(a[i]?j:-j);
			ans=(ans+t*f[i][j][l][r]%mod)%mod;
		}print(ans);put('\n');ans=0;
	}
}
signed main()
{
	int T=1;
	for(int i=0;i<=V;i++) inv[i]=ksm(i,mod-2,mod);
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

省队集训时讲的一道题。这里直接给出 Easy 与 Hard 版通用的做法。

多个照片肯定不好做，我们将 $a_i$ 相同的压成一张照片，那么这样子就只有两个照片——喜欢的和不喜欢的。

然后就可以 dp 了，设 $f(i,j)$ 表示 $i$ 张喜欢的照片和 $j$ 张不喜欢的照片的概率。

然后我们可以通过加一张照片，填出 $f(i,j+1)$ 和 $f(i+1,j)$ 的值，也就是：

$$
\begin{aligned}
f(i+1,j)=f(i+1,j)+\frac{i+S_1}{i-j+S}\cdot f(i,j)\\
f(i,j+1)=f(i,j+1)=\frac{S_0-j}{i-j+S}\cdot f(i,j)
\end{aligned}
$$

其中 $S$ 表示 $\sum w_i$，$S_k$ 表示 $\sum [a_i=k]w_i$。

然后考虑如何计算出压缩后一张图片的期望，我们可以枚举最后的照片情况，最后求和：

$$
\begin{aligned}
&E_1 = \sum_{i=0}^{m}(E_1+i-m)f(i,m-i)\\
&E_0=\sum_{i=0}^{m}(E_i+i)f(i,m-i)
\end{aligned}
$$

然后就是魔法，如何求出原本每个照片的期望呢？考虑到所有 $a_i$ 相等的照片本质上是相同的，权重是按照 $w_i$ 大小来选择的，具体选择哪一个照片并不重要。

于是我们可以将压缩后的“大照片”拆成 $S_k$ 个小照片，然后每一个照片的期望就对应 $w_i$ 个小照片，乘上即可，也就是：

$$
\frac{w_iE_{a_i}}{S_{a_i}}
$$

时间复杂度 $O(m^2\log P+n)$，轻微卡常。

[Code](https://vjudge.net/solution/51088712/i0fTQ4fEF5aiznnP6POp)

---

## 作者：冷却心 (赞：0)

人生 二十七で死ねるなら、ロックンロールは仆を救った。补兑这是八月某月明。

概率糖题。

发现每个 $w_i$ 的最终状态和其他 $w_i$ 的具体值关系不大，所以对每个 $w_i$ 单独 dp。设当前做 $w_p$。方便起见，这里把 $a_i=0$ 记作 $a_i=-1$。记初始 $w_i$ 之和为 $s_0$，$w_p$ 以外 $a_i=1$ 的位置的 $w_i$ 之和记为 $s_+$，$w_p$ 以外 $a_i=-1$ 的位置的 $w_i$ 之和为 $s_-$。

记 $f_{i,j,k}$ 表示操作了 $i$ 次，其中 $j$ 次操作 $w_p$，另外还有 $k$ 次操作了其他位置中 $a$ 值为 $1$ 的位置。那么此时 $s=\sum w_i=s_0+k-(i-j-k)+ja_p$。转移：

- $\displaystyle f_{i,j,k} \times \frac{w_p+ja_p}{s} \to f_{i+1,j+1,k}$，表示当前随机选择到 $w_p$。
- $\displaystyle f_{i,j,k} \times \frac{s_+ +k}{s} \to f_{i+1,j,k+1}$，表示选择了其他位置中 $a_i=1$ 的位置。
- $\displaystyle f_{i,j,k} \times \frac{s_--(i-j-k)}{s} \to f_{i+1,j,k}$，表示选择了其他位置中 $a_i=-1$ 的位置。

最终答案 $\displaystyle\mathrm{res}_p=\sum_j\sum_kf_{m,j,k} \times (w_p+ja_p)$。

然后做完了。

[The submission](https://codeforces.com/contest/1172/submission/325632457)。

---

