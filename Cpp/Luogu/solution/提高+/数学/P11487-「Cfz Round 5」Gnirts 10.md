# 「Cfz Round 5」Gnirts 10

## 题目背景

In Memory of $\text{F}\rule{66.8px}{6.8px}$.

## 题目描述

题面还是简单一点好。

- 给定 $n, m$，以及一个长为 $n + m$ 的 $\tt{01}$ 串 $S$。
- 对于 $\tt 01$ 串 $T$，定义 $f(T)$ 为 $S$ 的最长的前缀的长度，使得该前缀是 $T$ 的子序列 $^\dagger$。
- 对于每个 **恰包含 $\bm n$ 个 $\tt 1$ 和 $\bm m$ 个 $\tt 0$ 的** $\tt{01}$ 串 $T$，求 $f(T)$ 的和。答案对 $2933256077^\ddagger$ 取模。

$\dagger$：请注意，子序列可以不连续。换句话说，$a$ 是 $b$ 的子序列，当且仅当在 $b$ 中删去 $\geq 0$ 个字符后，可以得到 $a$。注意，空串总是任何串的子序列。

$\ddagger$：模数为质数。

## 说明/提示

#### 「样例解释 #1」

所有可能的序列有且仅有公共序列 $\texttt{0}$。因为恰有 $3$ 种不同的 $T$（$\tt 110, 101, 011$），所以答案为 $1\times 3 = 3$。

#### 「数据范围」

对于所有测试数据，保证 $1 \leq n, m \leq 3\times 10^6$。

**本题采用捆绑测试。**

- Subtask 0（13 points）：$\max(n, m) \leq 5$。
- Subtask 1（13 points）：$\max(n, m) \leq 100$。
- Subtask 2（34 points）：$\max(n, m) \leq 3 \times 10^3$。
- Subtask 3（40 points）：无特殊限制。

## 样例 #1

### 输入

```
2 1
000```

### 输出

```
3```

## 样例 #2

### 输入

```
5 5
0010111011```

### 输出

```
1391```

# 题解

## 作者：Cx114514 (赞：12)

### 题目链接：[「Cfz Round 5」Gnirts 10](https://www.luogu.com.cn/problem/P11487)

一道组合数学题。

~~场上对着一个错的式子 Debug 了两个小时，这下消愁了。~~

设 $f\left(T\right)=k$ 的 $T$ 的个数为 $g\left(k\right)$。

考虑怎么求 $g\left(k\right)$。

首先，$S$ 的前 $k$ 个元素一定按照顺序固定不变。设其中 $0$ 的个数为 $cnt0$，$1$ 的个数为 $cnt1$。则问题可以看作把剩余的 $\left(m-cnt0\right)$ 个 $0$ 和 $\left(n-cnt1\right)$ 个 $1$ 插入到这 $k$ 个元素组成的序列中。

接下来考虑怎么插使得 $f\left(T\right)$ 不变。

若 $S_{k+1}=0$，则 $0$ 不能放在这 $k$ 个元素后面，否则该元素会和 $S_{k+1}$ 形成新的公共部分。则 $0$ 只能插在这 $k$ 个 $1$ 之前（在插入的位置匹配到的一定是 $1$，$0$ 不会产生影响）。而 $1$ 可以插在原本的每个 $0$ 前面以及整个序列后面。

可以看作把相同的 $\left(m-cnt0\right)$ 个小球放入不同的 $cnt1$ 个盒子里，可以有空盒子的方案数，答案为 $\binom{m - cnt0 + cnt1 - 1}{cnt1 - 1} $。同理，插入 $1$ 的方案数为 $\binom{n - cnt1 + cnt0}{cnt0}$。总方案数即为 $\binom{m - cnt0 + cnt1 - 1}{cnt1 - 1}\times\binom{n - cnt1 + cnt0}{cnt0}$。

若 $S_{k+1}=1$，同理可得方案数为 $\binom{n - cnt1 + cnt0 - 1}{cnt0 - 1}\times\binom{m - cnt0 + cnt1}{cnt1}$。

综上可得:

$g\left(k\right)=\begin{cases}
\binom{m - cnt0 + cnt1 - 1}{cnt1 - 1}\times\binom{n - cnt1 + cnt0}{cnt0} & S_{k+1}=0
 \\
\binom{n - cnt1 + cnt0 - 1}{cnt0 - 1}\times\binom{m - cnt0 + cnt1}{cnt1} & S_{k+1}=1
\end{cases}$

最终答案即为 $\sum\limits_{k=1}^{n+m}k\times g\left(k\right)$。

预处理阶乘及其逆元，时间复杂度 $O\left(n+m\right)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 2933256077;

int n, m, len, ans, cnt0, cnt1, fac[6000005], inv[6000005], facinv[6000005];

char c[6000005];

int C(int x, int y)
{
	if (x == y) return 1;
	if (x < y) return 0;
	if (y < 0) return 0;
	return (fac[x] * facinv[x - y] % mod) * facinv[y] % mod;
}

signed main()
{
	fac[0] = 1;
	for (int i = 1; i <= 6000000; i++)
		fac[i] = (fac[i - 1] * i) % mod;
    inv[1] = 1;
    for (int i = 2; i <= 6000000; i++)
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
    facinv[0] = 1;
    for (int i = 1; i <= 6000000; i++)
        facinv[i] = facinv[i - 1] * inv[i] % mod;
	cin >> n >> m;
	len = n + m;
	for (int i = 1; i <= len; i++)
		cin >> c[i];
	for (int i = 1; i <= len; i++)
	{
		if (c[i] == '0') cnt0++;
		else cnt1++;
		int cur;
		if (c[i + 1] == '0') cur = C(m - cnt0 + cnt1 - 1, cnt1 - 1) * C(n - cnt1 + cnt0, cnt0) % mod;
		else cur = C(n - cnt1 + cnt0 - 1, cnt0 - 1) * C(m - cnt0 + cnt1, cnt1) % mod;
		ans = (ans + i * cur) % mod;
	}
	cout << ans << endl;
	return 0;
} 
```

---

## 作者：A2_Zenith (赞：10)

挺好的题，来写题解了！

首先，我们可以想到，要对答案是 $i$ 的 $01$ 序列 $T$ 计数。不妨设这样的串的数量是 $F(i)$，那么答案是 $\sum\limits_{i=1}^niF(i)$。

令 $Pre_i$ 为 $S$ 的长度为 $i$ 的前缀。

考虑对 $S$ 中长度为 $i$ 的前缀检查一个 $01$ 串 $T$ 是否合法。我们不难想到一个正确的贪心：设当前匹配到 $s_i$，设 $s_i$ 与 $T_p$ 匹配，那么 $s_{i+1}$ 匹配到 $T_p$ 往后第一个等于 $s_{i+1}$ 的位置，没有那么整个前缀就匹配失败了。

那么我们将 $T$ 划成若干个由极长的 $0/1$ 组成的连续段（伏笔 1），不难发现这时的子序列要么在某一段内一点不取，要么就取一段前缀（其实可以合并成一种情况）。

发现若 $T$ 中有 $Pre_i$ 做为前缀，那么其一定是在 $Pre_i$ 中插入若干个 $0/1$ 连续段的方式生成的。怎么不重不漏的插呢？不妨对于相邻的两个字符讨论。

$00$：只能插 $1$。因为伏笔 1 中的连续段可以取完，然后跳过整个 $1$ 段，再继续取。

$01$：只能插 $0$。因为是前缀嘛。

$10$：只能插 $1$，原因同上。

$11$：只能插 $0$，原因同上。

这个限制可以规约成：设相邻两个字符中右边的那个是 $x$，那么中间只能填 $1-x$。

不难发现这个限制能够以一种成功的方式归约到 $1$ 前面的部分与 $Pre_p$ 后面的部分。（这里假设我们在算 $F(p)$。）

原因很简单：对于 $1$ 前面的部分，肯定不能与之相同，正好符合我们的这个条件；

对于 $p$ 后面的部分，其肯定不能与 $p+1$ 相同，不然答案肯定是 $p+1$ 或者更多。$p=n+m$ 的情况另算。

那么我们设现在有 $C_0$ 个可以插 $0$ 的空隙，$C_1$ 个可以插 $1$ 的空隙，已经用掉 $S_0$ 个 $0$，$S_1$ 个 $1$ 了。

那么答案就是 $F(m-S_0,C_0) \times F(n-S_1,C_1)$。其中 $F(n,k)=\dbinom{n+k-1}{k-1}$，但是 $F(0,0) =1$。

直接预处理组合数然后 $O(n+m)$ 算出就好了。

对于 $p=n+m$ 的情况：考虑 $S$ 中是否有 $n$ 个 $1$ 与 $m$ 个 $0$，有的话就给总答案加上 $n+m$。

~~不值得注意的是，这玩意在赛时卡了我快半个小时。~~

就做完了。

~~欢迎大家多多膜拜我的学长/IOIAKer @Sharpsmile，他以 0.01h 的优势拿下了本场比赛的 rk1。~~


```cpp
#include<bits/stdc++.h>
#define int long long
#define doub long double
#define PII pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define PC __builtin_popcountll
using namespace std;
const int maxn=6e6+7;
const int mod=2933256077;
int n,m;
bool Ss[maxn];
int Fac[maxn];
int iFac[maxn];
inline int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=1ull*ans*a%mod;
        a=1ull*a*a%mod;
        b>>=1;
    }   
    return ans; 
}
inline void Init(){
    Fac[0]=1;
    for(int i=1;i<=n+m+5;i++)Fac[i]=1ull*Fac[i-1]*i%mod;
    iFac[n+m]=qpow(Fac[n+m],mod-2);
    for(int i=n+m-1;i>=0;i--)iFac[i]=1ull*iFac[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if(n<0||m<0||n<m)return 0;
    return 1ull*Fac[n]*iFac[m]%mod*iFac[n-m]%mod;
}
inline int F(int n,int m){
    if(n<0||m<0)return 0;
    if(n==0&&m==0)return 1;
    return C(n+m-1,m-1);
}
signed main(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    cin>>n>>m;
    Init();
    for(int i=1;i<=n+m;i++){
        char t;
        cin>>t;
        Ss[i]=t-'0';
    }
    int C0=0,C1=0;
    int S0=0,S1=0;
    int ans=0;
    for(int i=0;i<n+m;i++){
        if(i){
            if(Ss[i]==0)S0++;
            else S1++;
        }
        if(Ss[i+1]==0)C1++;
        else C0++;
        ans=(ans+1ull*i*F(m-S0,C0)%mod*F(n-S1,C1)%mod)%mod;
    }
    if(Ss[n+m]==0)S0++;
    if(Ss[n+m]==1)S1++;
    if((S0==m)&&(S1==n))ans+=(n+m);
    ans%=mod;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：ywli08 (赞：7)

令函数 $f(x)$ 表示恰好能够匹配长度为 $x$ 前缀的串 $T$ 的贡献。则答案可以表示为
$$
\sum_{x = 1}^{n + m} f(x).
$$
考虑对于每一个 $x$ ，我们如何求出 $f(x)$ 。  
对于 $S$ 的一个前缀 $S[k]$，我们要找出恰好与其相匹配的串 $T$。那么，$T$ 一定是形如以下的串：
$$
    \underbrace{\overline{S_0\cdots S_0}}_{length \ge 0} \,S_0\,
    \underbrace{\overline{S_1\cdots S_1}}_{length \ge 0} \,S_1\,
    \cdots\,
    \underbrace{\overline{S_k \cdots S_k}}_{length \ge 0} \,S_k\,\underbrace{\overline{S_{k+1}\cdots S_{k+1}}}_{length \ge 0} \:,
$$
其中 $\overline{s}$ 表示对 $s$ 取反。   
我们发现，这样的串是一定能匹配上 $S[k]$ 的；但是他会在尝试匹配 $S_{k+1}$ 的时候失败。同时，对于这样构造出来的串进行计数可以做到不重不漏，因为我们保证了每一个 $S_i$ 都会尽量早地匹配。   
考虑如何进行计数。对于前缀 $S[k]$，假设里面有 $c_0$ 个 $0$，$c_1$ 个 $1$，那么
$$
    f(k) = \begin{cases}
    k \cdot \sum_{j = 0}^{m - c_0} P(m - c_0 - j, c_1) \cdot P(n - c_1, c_0) & S_{k + 1} = 1 \\  
    k \cdot \sum_{j = 0}^{n - c_1} P(m - c_0, c_1) \cdot P(n - c_1 - j, c_0) & S_{k + 1} = 0
    \end{cases}
$$
其中 $P(x, y)$ 表示将 $x$ 个物品分为 $y$ 份，每份可以为空的方案数，即 $\binom{x + y - 1}{y - 1}$。   
我们将两个式子的求和中相同的部分拎出来，得到
$$
    f(k) = \begin{cases}
    k \cdot P(n - c_1, c_0) \cdot \sum_{j = 0}^{m - c_0} P(m - c_0 - j, c_1) & S_{k + 1} = 1 \\  
    k \cdot P(m - c_0, c_1) \cdot \sum_{j = 0}^{n - c_1} P(n - c_1 - j, c_0) & S_{k + 1} = 0
    \end{cases}
$$
另外由 $\sum_{i = 0}^n \binom{i}{k} = \binom{n + 1}{k + 1}$ 得
$$
    f(k) = \begin{cases}
    k \cdot P(n - c_1, c_0) \cdot \binom{m - c_0 + c_1}{c_1} & S_{k + 1} = 1 \\  
    k \cdot P(m - c_0, c_1) \cdot \binom{n - c_1 + c_0}{c_0} & S_{k + 1} = 0
    \end{cases}
$$
这样这个函数的值就可以被 $O(1)$ 求出来了。   
其实我们还有个问题没有解决，就是 $f(n + m)$ 的取值，因为并不存在 $S_{n + m + 1}$。可以发现，$f(n + m)$ 当且仅当 $c_0 = n \wedge c_1 = m$ 时值不为 $0$，进一步发现其值恰好为 $n + m$，即 $T = S$。  

代码：
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 6e6+5;
const ll mod = 2933256077;

template<typename T>
T powmod(T a, T b, T mod){
    T res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int n, m;
string s;

ll fac[maxn];
ll ifac[maxn];

void init(int n){
    fac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[n] = powmod(fac[n], mod - 2, mod);
    for(int i = n - 1;i >= 0;i--){
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
}

ll C(ll x, ll y){
    if(x < y || x < 0 || y < 0) return 0;
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

ll place(ll x, ll y){
    if(x == 0 && y == 0) return 1;
    return C(x + y - 1, y - 1);
}

ll placesum(ll x, ll y){
    return C(x + y, y);
}

int main(){
    cin >> n >> m;
    cin >> s; s = ' ' + s;
    init(n + m);
    ll c0 = 0, c1 = 0;
    ll ans = 0;
    for(int i = 1;i <= n + m;i++){
        c0 += s[i] == '0';
        c1 += s[i] == '1';
        if(i < n + m){
            if(s[i + 1] == '0'){
                ans = (ans + place(m - c0, c1) * placesum(n - c1, c0) % mod * i) % mod;
            }
            if(s[i + 1] == '1'){
                ans = (ans + placesum(m - c0, c1) * place(n - c1, c0) % mod * i) % mod;
            }
        }
        else{
            if(n - c1 >= 0 && m - c0 >= 0){
                ans = (ans + place(m - c0, c1) * place(n - c1, c0) % mod * i) % mod;
            }
        }
    }
    cout << ans << endl;
}
```

---

## 作者：ccxswl (赞：3)

枚举 $S$ 每个前缀，计算其对答案的贡献。

把枚举出来的前缀 $S[1\dots i]$ 看成已有的串，我们要插入一些字符使得它有 $n$ 个 $0$，$m$ 个 $1$，且 $S[1\dots i]$ 为 $T$ 的子序列，而 $S[1\dots i + 1]$ 不是。问方案数（统计到最后答案的时候要乘长度）。

发现在 $1$ 前插 $0$ 和在 $0$ 前插 $1$ 都不会对合法性造成影响。判断 $S[1\dots i]$ 是否为 $T$ 的子序列可以看成一个匹配的过程，如果 $T$ 当前的字符和 $S$ 当前的字符不同就看 $T$ 中的下一个字符（称匹配失效），如果相同，就都看下一个字符。$T$ 中和 $S$ 当前位不同的都会被略过，其实也就是最初那些“看成已有串”的字符被我们钦定为 $T$ 中组成 $S[1\dots i]$ 的字符，其他新插入的都是匹配失效的字符。

按理说我们在最后匹配完成的时候可以肆意放字符，但我们要求 $S[1\dots i+1]$ 不是 $T$ 的子序列，所以最后的位置只能放与 $S_{i+1}$ 不同的字符。

把 $0$ 和 $1$ 单独考虑，根据乘法原理，最终方案数为两者方案数相乘。知道放的位置，知道放的个数，最后就是经典的不同小盒放同样的球可以为空的问题了。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define IL inline
IL int _R() { int x; cin >> x; return x; }

const int N = 3e6;
const int maxN = N * 2 + 3;

const int mod = 2933256077;

int n, m;

int fc[maxN], ifc[maxN];
IL int ksm(int a, int b = mod - 2) {
  int res = 1;
  while (b) {
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}

string s;

int ans;

IL int C(int n, int m) {
  if (n < 0 || m < 0 || n < m) return 0;
  return fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
IL int F(int n, int m) { // n 个小球放 m 个盒中
  if (!n) return 1; // 注意放 0 个球到任意盒中也可以看做一个方案。
  return C(n + m - 1, m - 1);
}

signed main() {
  n = _R(), m = _R();

  fc[0] = 1;
  for (int i = 1; i <= n + m; i++)
    fc[i] = fc[i - 1] * i % mod;
  ifc[n + m] = ksm(fc[n + m]);
  for (int i = n + m - 1; i >= 0; i--)
    ifc[i] = ifc[i + 1] * (i + 1) % mod;

  cin >> s;
  s = '@' + s + '$';
  int c0 = 0, c1 = 0;
  for (int i = 1; i <= n + m; i++) {
    c0 += s[i] == '0', c1 += s[i] == '1';
    
    auto r1 = F(m - c0, c1 + (s[i + 1] == '0' ? 0 : 1));
    auto r2 = F(n - c1, c0 + (s[i + 1] == '1' ? 0 : 1));

    // cerr << r1 << ' ' << r2 << '\n';

    ans += i * r1 % mod * r2 % mod, ans %= mod;
  }

  cout << ans << '\n';
}
```

---

## 作者：喵仔牛奶 (赞：2)

## Solution

考虑计算包含 $S_1S_2\cdots S_i$ 这个子序列但是不包含 $S_1S_2\cdots S_{i+1}$ 的 $T$ 个数。

直接数容易数重，考虑在 $T$ 中扣出一个 $S$ 使得它在 $T$ 中的下标序列字典序最小。记 $\overline{S_i}$ 表示 $(1-S_i)$，即 $S_i$ 反转后的结果。结论：所有合法的 $T$ 都可以表示为
$$\overline{S_1S_1\cdots S_1}S_1\overline{S_2S_2\cdots S_2}S_2\cdots \overline{S_iS_i\cdots S_i}S_i\overline{S_{i+1}S_{i+1}\cdots S_{i+1}}$$

证明：
- 肉眼可见可以找出 $S_1S_2\cdots S_i$，并且无法找出 $S_1S_2\cdots S_iS_{i+1}$。
- 对于 $x\le i$，如果 $\overline{S_xS_x\cdots S_x}$ 里面有一个不是 $\overline{S_x}$，那么 $S_x$ 变为这个不是的，字典序更小。
- 如果 $\overline{S_{i+1}S_{i+1}\cdots S_{i+1}}$  里面有一个不是 $\overline{S_{i+1}}$，那么可以找出 $S_1S_2\cdots S_iS_{i+1}$。

枚举 $i$，问题就变为无标号的球放入有标号的盒子里，插板法即可。具体地，设 $[1,i]$ 中有 $c_0$ 个 $\tt 0$，$c_1$ 个 $\tt 1$，贡献为
$$\binom{m-c_0+c_1+[a_{i+1}=\tt 1]-1}{c_1+[a_{i+1}=\tt 1]-1}\binom{n-c_1+c_0+[a_{i+1}=\tt 0]-1}{c_0+[a_{i+1}=\tt 0]-1}\times i$$

注意模数超出了 int 的范围。

## Code

```cpp
namespace Milkcat {
	using namespace math;
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const unsigned N = 6e6 + 5, mod = 2933256077;
	typedef mlong<mod> MI;
	int n, m, c0, c1, a[N]; char x; MI rs; Comb<MI> C;
	MI calc(int x, int y) {
		return (x > 0 ? C(x + y - 1, y - 1) : 1);
	}
	int main() {
		cin >> m >> n, C.init(n + m);
		REP(i, 1, n + m) cin >> x, a[i] = x - '0';
		REP(i, 1, n + m) {
			(a[i] ? c1 : c0) ++;
			if (c0 > n || c1 > m) break;
			rs += calc(n - c0, c1 + a[i + 1]) * calc(m - c1, c0 + !a[i + 1]) * i;
		}
		cout << rs << '\n';
		return 0;
	}
}
```

---

## 作者：light_searcher (赞：2)

首先模数是个质数，那么容易想到要求逆元，所以说八成是个组合数。

考虑求出 $f(T)=k$ 的 $T$ 的数量。设 $s$ 表示 $S$ 长度为 $k$ 的前缀，$s$ 中 $0,1$ 的个数分别为 $cnt_{0/1}$，现在就要考虑有多少种方案把 $m-cnt_0$ 个 $0$ 和 $n-cnt_1$ 个 $1$ 插入到 $s$ 中，使得 $S$ 长度为 $k+1$ 的前缀不是插入后得到的字符串的子序列。在 $s_i$ 和 $s_{i+1}$ 之间只有插入与 $s_{i+1}$ 不同的字符才能做到不重不漏。

- 当 $S_{k+1}$ 为 $0$ 时，在 $s$ 的末尾只能插入 $1$，那么这时求方案数就等价于求把 $m-cnt_0$ 个 $0$ 插入 $cnt_1$ 个 $1$ 并把 $n-cnt_1$ 个 $1$ 插入 $cnt_0+1$ 个 $0$，每两个 $0$ 或 $1$ 之间可以不插的方案数。这是一个组合数中插板法的经典问题，前者方案数为 $\begin{pmatrix} m-cnt_0+cnt_1-1 \\ cnt_1-1 \end{pmatrix}$，后者方案数为 $\begin{pmatrix} n-cnt_1+cnt_0 \\ cnt_0 \end{pmatrix}$，那么总方案数为 $ \begin{pmatrix} m-cnt_0+cnt_1-1 \\ cnt_1-1 \end{pmatrix} \times \begin{pmatrix} n-cnt_1+cnt_0 \\ cnt_0 \end{pmatrix}$。
  
- 当 $S_{k+1}$ 为 $1$ 时，同理，方案数为 $ \begin{pmatrix} m-cnt_0+cnt_1 \\ cnt_1 \end{pmatrix} \times \begin{pmatrix} n-cnt_1+cnt_0-1 \\ cnt_0-1 \end{pmatrix}$。

然后这题就做完了，要特别注意当 $cnt_{0/1}$ 为 $0$ 时，会减成负数。预处理阶乘及逆元，时间复杂度为 $\mathcal O(n+m)$。

Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e6+5,M=6e6,mod=2933256077;
int n,m,fac[N],inv[N],facinv[N],ans;
char s[N];
int C(int n,int m){
	if(n==m) return 1;
	return fac[n]*facinv[n-m]%mod*facinv[m]%mod;
}
signed main(){
	scanf("%lld%lld%s",&n,&m,s+1);
	fac[0]=fac[1]=facinv[0]=facinv[1]=inv[1]=1;
	for(int i=2;i<=n+m;i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(-(mod/i)*inv[mod%i]%mod+mod)%mod;
		facinv[i]=facinv[i-1]*inv[i]%mod;
	}
	for(int i=1,cnt0=0,cnt1=0;i<=n+m;i++){
		if(s[i]=='0') cnt0++;
		else cnt1++;
		if(cnt0>m||cnt1>n) break;
		if(s[i+1]=='0') ans=(ans+i*C(m-cnt0+cnt1-1,cnt1-1)%mod*C(n-cnt1+cnt0,cnt0)%mod)%mod;
		else ans=(ans+i*C(m-cnt0+cnt1,cnt1)%mod*C(n-cnt1+cnt0-1,cnt0-1)%mod)%mod;
	}
	printf("%lld",ans);
	return 0;
}

---

## 作者：lsc72 (赞：2)

## 部分分

暴力枚举一下，可以拿 $13$ 分。

考虑设三个状态统计方案数进行 DP，时空复杂度均为 $\mathcal{O}(nm(n+m))$，可以再拿 $13$ 分，这一档应该还是很好想的吧。
写这一档分对我的帮助很大，对题目原理了解更深，后面也用来对拍差错了。所以比赛时尽量还是考虑先写暴力，对心态也有帮助。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN=210;
const ll mod=2933256077;
int n,m,a[MAXN];
ll dp[MAXN][MAXN][MAXN],ans;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>m;
    for (int i=1;i<=n+m;i++){
        char c; cin>>c;
        a[i]=c-'0';
    }
    dp[0][0][0]=1;
    for (int k=0;k<=n+m;k++){
        for (int i=0;i<=n;i++){
            for (int j=0;j<=m;j++){
                if (!dp[k][i][j]) continue;
                if (a[k+1]) {
                    dp[k+1][i+1][j]=(dp[k+1][i+1][j]+dp[k][i][j])%mod;
                    dp[k][i][j+1]=(dp[k][i][j+1]+dp[k][i][j])%mod;
                }
                else{
                    dp[k+1][i][j+1]=(dp[k+1][i][j+1]+dp[k][i][j])%mod;
                    dp[k][i+1][j]=(dp[k][i+1][j]+dp[k][i][j])%mod;
                }
                if (i==n&&j==m){
                    cout<<k<<" "<<dp[k][n][m]<<'\n';
                }
            }
        }
    }
    for (ll i=1;i<=n+m;i++){
        ans=(ans+dp[i][n][m]*i%mod)%mod;
    }
    cout<<ans<<'\n';
    return 0;
}
```

不会 $\mathcal{O}(n^2)$。
没事直接说正解。

## 正解

首先感觉从优化 DP 的角度已经没什么前途了，至少我盯了半天不会优化。考虑到题目给了两个提示：一个是数据范围上的，$n + m \leq 6 \times10^6$，大概率是要线性做法。另一个是模数为**质数**，这就让我们考虑到了逆元。

我们尝试枚举 $S$ 的前缀，这些前缀的字符（后面称之为**前缀符**）在 $T$ 中的相对位置已经固定。只需要统计在它们之前以及前后两部分再插入一些非前缀符且最后要满足 $T$ 的组成条件的方案数即可。

具体一点来说， 假设有一个前缀符 $1$，那么在上一个前缀符与它之前可以插入那些字符？显然只有 $0$，因为如果有 $1$ 那么就会让那个更提前的 $1$ 成为前缀符。这就形成了一个只能放任意多个 $0$ 的**槽**。前缀符是 $0$ 时同理，注意一下末尾插入的也要考虑，详细内容可以见代码。

然后在依次枚举前缀的过程中，先前的前缀符它们中间要放什么已经确定，然后还知道剩下的 $1$ 和 $0$ 的个数。整理成数学形式，就是当前有 $t_0$ 个 $0$ 要分别插到 $k_0$ 个 $0$ 槽中，有 $t_1$ 个 $1$ 要分别插到 $k_1$ 个 $1$ 槽中，问方案数，这时候我们发现这就是个经典问题了。

把 $n$ 个相同物品分到 $m$ 个不同的组可以用**隔板法**解决，答案为 $\binom{n+m-1}{m-1}$。
可以线性处理阶乘和阶乘的逆元，时间复杂度为 $\mathcal{O}(n+m)$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN=6000010;
const ll mod=2933256077;
int n,m,a[MAXN],t1,t0,k1,k0;
ll jc[MAXN],inv[MAXN],inj[MAXN],ans;
ll C(ll n,ll m){
    if (n==m) return 1;
    if (n<0||m<0) return 0;
    ll ans=jc[n]*inj[n-m]%mod*inj[m]%mod;
    return ans;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>m;
    inj[0]=jc[0]=inv[1]=1;
    for (int i=2;i<=n+m;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for (int i=1;i<=n+m;i++) inj[i]=inv[i]*inj[i-1]%mod,jc[i]=jc[i-1]*i%mod;
    for (int i=1;i<=n+m;i++){
        char c; cin>>c;
        a[i]=c-'0';
    }
    t0=m; t1=n;
    for (int i=1;i<=n+m;i++){
        if (a[i]) t1--,k0++;
        else t0--,k1++;
        if (t0<0||t1<0) break;
        if (i==n+m){
            ans=(ans+n+m)%mod;
            break;
        }
        ll t;
        if (a[i+1]) t=C(t1+k1-1,k1-1)*C(t0+k0,k0)%mod;
        else t=C(t1+k1,k1)*C(t0+k0-1,k0-1)%mod;
        ans=(ans+i*t%mod)%mod;
    }
    cout<<ans<<'\n';
    return 0;
}

```

---

## 作者：irris (赞：2)

> Tag：组合计数

### $\bm{\max(n, m) \leq 5}$

枚举每个可能的 $T$，这最多不超过 ${n + m \choose n}$ 个，随后暴力检验。

### $\bm{\max(n, m) \leq 500}$

考虑到 [判定子序列](https://www.luogu.com.cn/problem/P5826) 可以贪心判定，写出一个 dp：设 $f_{i,j,k}$ 表示当前 $T$ 内的前缀填写了 $i$ 个 $\tt 0$，$j$ 个 $\tt 1$，匹配了 $S$ 长度为 $k$ 的前缀。转移显然能做到 $\mathcal O(1)$，因此是 $\mathcal O(nm(n + m))$ 的。

### $\bm{\max(n, m) \leq 5000}$

应当有写假的正解等其它做法。

### No Additional Constraints

枚举 **恰好** 匹配了 $S$ 长度为 $k$ 的前缀。特判一下 $k = n + m$ 的特例，下文中 $1 \leq k \leq n + m - 1$。

设这个前缀里有 $c_0$ 个 $\tt 0$ 和 $c_1$ 个 $\tt 1$。考虑在 $T$ 的子序列自动机上跳的过程，我们总共有 $c_0$ 次「跳到下一个 $\tt 0$ 出现的位置」和 $c_1$ 次「跳到下一个 $\tt 1$ 出现的位置」。而：

- 每一次「跳到下一个 $\tt 0$ 出现的位置」都对应当前 $T$ 一个形如 $\tt 11...10$ 的前缀，其中 $\tt 1$ 出现 $\geq 0$ 次；
- 每一次「跳到下一个 $\tt 1$ 出现的位置」都对应当前 $T$ 一个形如 $\tt 00...01$ 的前缀，其中 $\tt 0$ 出现 $\geq 0$ 次；
- 因为 $S$ 恰好匹配了长度为 $k$ 的前缀，那么最后还有一次失败的「跳到下一个 $C$ 出现的位置」，其中 $C \in \{\tt 0, 1\}$。因为这次匹配失败了，这说明 $T$ 的结尾还可以有若干（$\geq 0$）个 $1 - C$。

换句话说，除去 $T$ 中已经按顺序钦定好的 $c_0$ 个 $\tt 0$ 和 $c_1$ 个 $\tt 1$ 以外，剩下的 $m - c_0$ 个 $\tt 0$ 还有 $c_1 + [S_{k+1} = \tt 1]$ 个空缺段可以插入，剩下的 $n - c_1$ 个 $\tt 1$ 还有 $c_0 + [S_{k+1} = \tt 0]$ 个空缺段可以插入。而如果我们写出每个前缀最长匹配了 $S$ 多少个字符，就能发现每种不同的插入方式一一对应每种不同的 $k$。

如何计算插入方式？我们简化为计算如下的问题：

> 多组询问。每组询问给出 $n, m$，你需要计算将 $n$ 个小球放入 $m$ 个彼此不同的盒子中，每个盒子里有 $\geq 0$ 个小球的方案数。

这是插板法的经典例题，答案是 $\dbinom{n + m - 1}{m - 1}$。于是对于每个 $k$，我们可以在预处理阶乘及逆元后 $\mathcal O(1)$ 回答问题。

本题在 $\mathcal O(n + m)$ 的时间复杂度内被解决。

---

## 作者：cancan123456 (赞：1)

考虑枚举 $i$，计算 $f(T)=i$ 的 $T$ 的数量，考虑到这样的 $T$ 一定是 $S_{1\sim i}$ 通过插入一些 $0/1$ 得到的，为了不重复计算，我们要求插入得到的 $T$ 中每个 $S_j(1\le j\le i)$ 都在尽可能靠前的位置，即，$S_{j-1}$ 到 $S_j$ 的位置中间不能有与 $S_j$ 相同的字符，否则就可以将 $S_j$ 前移，会算重，特别的，注意 $S_i$ 后面只能填与 $S_{i+1}$ 不同的字符，这是为了保证 $S_{i+1}$ 无法匹配，使 $f(T)\le i$。

于是统计一下还剩几个 $0/1$，有几个位置能填 $0/1$，插板法加乘法原理统计即可。

时间复杂度为 $O(n+m)$，可以通过此题。

```cpp
#include <cstdio>
using namespace std;
typedef long long ll;
const ll mod = 2933256077;
const int N = 6000105;
ll pow(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            (ans *= a) %= mod;
        }
        (a *= a) %= mod;
        b /= 2;
    }
    return ans;
}
ll inv(ll x) {
    return pow(x, mod - 2);
}
char S[N];
ll fac[N], invfac[N];
ll C(int n, int m) {
    if (n < 0 || m < 0 || n < m) {
        return 0;
    }
    return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
ll cb(int n, int m) {
    if (m == 0) {
        return n == 0 ? 1 : 0;
    }
    return C(n + m - 1, m - 1);
}
void swap(int & a, int & b) {
    a ^= b ^= a ^= b;
}
void init(int len) {
    fac[0] = 1;
    for (int i = 1; i <= len; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[len] = inv(fac[len]);
    for (int i = len; i >= 1; i--) {
        invfac[i - 1] = invfac[i] * i % mod;
    }
}
bool check(char * S, int n, int m) {
    int cnt0 = 0;
    for (int i = 1; i <= n + m; i++) {
        if (S[i] == '0') {
            cnt0++;
        }
    }
    return cnt0 == m;
}
int main() {
    // freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", S + 1);
    int len = n + m;
    init(len + 100);
    int cnt0 = 0, cnt1 = 0;
    ll ans = 0;
    if (check(S, n, m)) {
        ans += len;
    }
    for (int i = 1; i < len; i++) {
        if (S[i] == '0') {
            cnt0++;
        } else {
            cnt1++;
        }
        int c0 = cnt1, c1 = cnt0;
        if (S[i + 1] == '0') {
            c1++;
        } else {
            c0++;
        }
        ll cur = cb(m - cnt0, c0) * cb(n - cnt1, c1) % mod;
        (ans += cur * i) %= mod;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：ollo (赞：1)

不懂啊，为啥评蓝，感觉和 NOIP2024T2 差不多。

考虑先枚举这个最长的可匹配前缀有多长，再去统计有多少个串满足限制。如果直接做的话一个串可能不止有一个可匹配前缀，所以我们给这个可匹配前缀加上一些特殊的限制。

那么我们定义 $f_i$ 表示下标字典序最小的最长可匹配前缀长度为 $i$，显然这个状态是不重不漏的。考虑什么样的串满足这个限制，可以想到在前缀中的相邻两个数中间去插数，直到整个串长为 $n+m$。

但是我们显然是不能乱插的，考虑相邻两个数之间可以插什么东西，容易发现如果要满足限制，那么对于形如 $s_is_{i+1}$ 这样的空，中间插的数不能为 $s_{i+1}$，因为如果中间插了一个 $s_{j}$ 使得 $s_j=s_{i+1}$ 那么此时我们插的就不是下标字典序最小的前缀了。

所以问题变为了有 $n$ 个白球 $m$ 个黑球以及 $a$ 个只能插白球的洞和 $b$ 个只能插黑球的洞，洞可以不放球，问放球的方案数。组合计数的经典问题，可以算出方案数为 $\binom{n+a-1}{a-1}\binom{m+b-1}{b-1}$，答案则可以表示为 $\sum_{i=1}^{n+m} i\binom{n+a-1}{a-1}\binom{m+b-1}{b-1}$。暴力算这个东西是 $O(n^2)$ 的，但是容易发现枚举的前缀每增加一位，$n,m,a,b$ 的变化量都是 $O(1)$ 的，所以可以动态的维护两个组合数，线性预处理逆元的话复杂度就是 $O(n)$ 的。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return ;
}
template <typename T>
inline void print(T x){write(x);putchar('\n');}

const int N = 6e6 + 10, mod = 2933256077;

int n, m;
string s;
int len;
int f[2], c[2], inv[N];
int C(int n, int m){
	if(n < m || n < 0 || m < 0) return 0;
	int res = 1;
	for(int i = 1; i <= n; i++) res = res * i % mod;
	for(int i = 1; i <= m; i++) res = res * inv[i] % mod;
	for(int i = 1; i <= n - m; i++) res = res * inv[i] % mod;
	return res;
}

int qpow(int a, int b){
	int res = 1;
	while(b){
		if(b & 1) res = res * a % mod;
		b >>= 1;a = a * a % mod;
	}
	return res;
}

int a[N], ans;

void dfs(int x, int l, int r){
	if(x > n + m){
		int lt = 1;
		for(int i = 1; i <= n + m; i++){
			if(a[i] == s[lt] - '0') lt++;
		}
		ans = (ans + lt - 1) % mod;
		return ;
	}
	if(l > 0)a[x] = 0,dfs(x+1,l-1,r);
	if(r > 0) a[x]=1,dfs(x+1,l,r-1);
}

void solve2(int l, int r){
	dfs(1, l, r);print(ans);
}
int w[2];
void solve(){ans = 0;
	read(n);read(m);cin >> s;len = s.size();s = " " + s;
	if(n + m <= 10){solve2(m, n);return ;}
	c[0] = m;c[1] = n;
	bool fl = 0;
	for(int i = 2; i <= len; i++) if(s[i] != s[i - 1]){fl = 1;break;}
	for(int i = 1; i <= n + m; i++) inv[i] = qpow(i, mod - 2);
	if(!fl){
		fl = s[1] - '0';
//		cout<<n+m<<','<<c[fl]<<endl;
		ans = c[fl] * C(n + m, c[fl])% mod;
		print(ans);return ;
	}
	f[(s[1] - '0') ^ 1]++;c[s[1] - '0']--;
	w[0] = w[1] = 0;
	if(f[0] == 1 && w[0] == 0) w[0] = C(c[0] + f[0] - 1, f[0] - 1);
	if(f[1] == 1 && w[1] == 0) w[1] = C(c[1] + f[1] - 1, f[1] - 1);
	for(int i = 2; i <= len; i++){
		int l = -1;
		if(s[i] == s[i - 1]) l = (s[i - 1] - '0') ^ 1;
		else l = s[i - 1] - '0';
		if(f[l] != 0){
//			if(i == 5) cout<<l<<','<<w[l]<<','<<(c[l]+f[l])%mod *inv[f[l]]%mod<<endl;
			w[l] = w[l] * (c[l] + f[l]) % mod * inv[f[l]] % mod;
		}
		f[l]++;
		if(f[0] == 1 && w[0] == 0) w[0] = C(c[0] + f[0] - 1, f[0] - 1);
		if(f[1] == 1 && w[1] == 0) w[1] = C(c[1] + f[1] - 1, f[1] - 1);
//		cout<<i<<','<<w[0]<<','<<w[1]<<endl;
		if(f[0] > 0 && f[1] > 0) ans = (ans + w[0] * w[1] % mod * (i - 1) % mod) % mod;
		l = s[i] - '0';
		w[l] = w[l] * inv[c[l] + f[l] - 1] % mod * c[l] % mod;//n=cl+fl-1,m=fl-1,n-m=cl>n=cl+fl-2,m=fl-1,n-m=cl-1
		c[l]--;
		if(c[0] < 0 || c[1] < 0) break;
	}
	if(c[0] == 0 && c[1] == 0) ans =(ans + len) % mod;
	print(ans);
}

signed main(){int T = 1;
	while(T--) solve();
	return 0;
}
/*
011	
00101
*/
```

---

## 作者：qnqfff (赞：0)

### 思路

考虑枚举最长前缀长度并钦定最长前缀每个字符尽量靠左，考虑对合法的 $T$ 计数。

容易发现每个字符前面只能插和它不同的字符，最后一个字符后面只能插和它后面那个字符不同的字符，于是现在题目转化成有若干个 $0,1$ 有一些空只能给 $0$ 填，其余的只能给 $1$ 填，求填完的方案数，这是个经典问题，插板法即可，设有 $n$ 个 $0$，$m$ 个空，则方案数为 $\binom{n+m-1}{m-1}$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod=2933256077;
using namespace std;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,fac[6000010],inv[6000010];string s;
int qpow(int x,int y){int ans=1;for(;y;y>>=1,x=x*x%mod) if(y&1) ans=ans*x%mod;return ans;}
int c(int n,int m){if(m<0) return n<0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
	n=read();m=read();cin>>s;s=" "+s;fac[0]=1;for(int i=1;i<=n+m;i++) fac[i]=fac[i-1]*i%mod;inv[n+m]=qpow(fac[n+m],mod-2);for(int i=n+m-1;~i;i--) inv[i]=inv[i+1]*(i+1)%mod;
	int ans=0,A=0,B=0,x=(s[1]=='0'),y=(s[1]=='1');for(int i=1;i<n+m;i++){
		if(s[i]=='1') A++;else B++;if(s[i+1]=='0') x++;else y++;
		if(A<=n&&B<=m) (ans+=i*c(n-A+x-1,x-1)%mod*c(m-B+y-1,y-1)%mod)%=mod;
	}if(s[n+m]=='1') A++;else B++;if(A==n) (ans+=n+m)%=mod;cout<<ans;
	return 0;
}
```

---

