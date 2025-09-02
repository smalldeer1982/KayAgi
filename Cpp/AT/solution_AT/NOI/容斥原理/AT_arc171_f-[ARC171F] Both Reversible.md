# [ARC171F] Both Reversible

## 题目描述

当字符串 $T$ 满足以下条件时，称 $T$ 为**好字符串**。

- 存在一组字符串 $(A, B)$，满足以下所有条件：
  - $A$ 和 $B$ 都非空。
  - $A + B = T$。
  - $A + \mathrm{rev}(B)$ 和 $\mathrm{rev}(A) + B$ 都是回文串。

这里，$A + B$ 表示将字符串 $A$ 和字符串 $B$ 按顺序连接得到的新字符串。  
此外，$\mathrm{rev}(A)$ 表示将字符串 $A$ 的字符顺序反转得到的新字符串。

给定一个由小写英文字母和 `?` 组成、长度为 $N$ 的字符串 $S$。  
将 $S$ 中的每个 `?` 替换为小写英文字母的方法共有 $26^{(\text{? 的个数})}$ 种，其中有多少种替换后得到的字符串是好字符串？请输出方案数对 $998244353$ 取模的结果。

## 说明/提示

### 限制条件

- $2 \leq N \leq 5 \times 10^4$
- $S$ 是由小写英文字母和 `?` 组成的长度为 $N$ 的字符串

### 样例解释 1

字符串 `abab` 是好字符串。因为当 $A = $ `ab`，$B = $ `ab` 时，$A + B = $ `abab`，且 $A + \mathrm{rev}(B) = $ `abba` 和 $\mathrm{rev}(A) + B = $ `baab` 都是回文串。因此，$S$ 中 `?` 替换后能得到好字符串的方案只有 `abab` 这一种。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
?ba?```

### 输出

```
1```

## 样例 #2

### 输入

```
10
?y?x?x????```

### 输出

```
676```

## 样例 #3

### 输入

```
30
???a?????aab?a???c????c?aab???```

### 输出

```
193994800```

## 样例 #4

### 输入

```
36
????????????????????????????????????```

### 输出

```
363594614```

# 题解

## 作者：zhouhuanyi (赞：4)

首先根据 $rev(A)+B$ 回文，有 $rev(B)+A$ 回文，又因为 $A+rev(B)$ 回文，令 $s=A+rev(B)$，相当于实际上是将 $s$ 拆成 $a+b$ 的形式后再变成 $b+a$，回文的性质没有被破坏。

令 $F(s)$ 为最小的 $k$ 满足存在 $t^k=s$，由于 $s$ 回文，则 $t$ 也回文，不难发现如果 $k\geqslant 2$，则我们只要将 $s$ 拆成 $t^{k-1}$ 与 $t$，则 $t^{k-1}+t$ 与 $t+t^{k-1}$ 均为回文。再将 $t$ 翻转回来之后因为其回文所以不变，所以可以得到所有 $F(s)\geqslant 2$ 的串都是合法的。

直接数 $F(s)\geqslant 2$ 的串可以发现 $n=8$ 时就会出现问题，有 $\text{ababbaab}$ 是一个合法的串，由于 $\text{ab|abbaab}$ 是一个合法的划分方案。观察可以发现如果 $s=a+rev(a)+a+rev(a)$，则 $a+a+rev(a)+a$ 其实是合法的，这个变换相当于令 $s=t^k$，当 $|t|$ 为偶数时令 $t=a+rev(a)$，则可以令 $k=x+y+1$，则 $(a+rev(a))^x+a^2+(rev(a)+a)^y$ 是一个合法的串，仔细想想发现似乎不存在更多的合法串了。

接下来证明这一点，令 $n=|s|,d=|A|$，则有对于 $0\leqslant i\leqslant n-1$ 有 $i$ 与 $n-1-i$ 与 $(n-1-i+2d)\mod n$ 属于同一个等价类，则 $\frac{n}{gcd(2d,n)}|k$，则 $\frac{n}{k}|2d$，那么 $d$ 一定为 $\frac{n}{2k}$ 的倍数，即只能在串的衔接位置和串中点位置断开重连。

$F(s)\geqslant 2$ 的串是容易统计的，令 $f_{i}$ 为 $F(s)=i$ 的串个数，由于 $\sum_{j|i}f_{j}$ 是好计算的，所以容斥一下即可得到 $f$。

关键在于 $F(s)=1$ 的串如何避免算重，首先其可以写为 $(a+rev(a))^x+a^2+(rev(a)+a)^y$ 的形式，当 $a=rev(a)$ 时 $F(s)\geqslant 2$ 这一部分可以简单容斥掉。如果只容斥这个会发现当 $n=12$ 时串 $\text{abbaababbaab}$ 会被算两次，原因是其既是 $(abbaab)^2$ 又是 $ab+ba+(ab)^2+ba+ab$，但注意到此时它们的 $|(a+rev(a))^x+a|$ 是相同的，即中间划分开来的位置。每次我们都在 $k$ 尽量大的地方统计，要求 $a$ 不可以拆成更小的结构。令 $dp_{i,j}$ 表示 $k=i,|(a+rev(a))^x+a|=j$ 的一个方案数，每次当 $a=(b+rev(b))^z+b$，取 $b$ 才是 $k$ 最大的方案，容斥一下即可。

由于有 $k|n$，则复杂度为 $O(nd(n))$。

---

## 作者：kyEEcccccc (赞：2)

> 字符集为小写拉丁字母。给定一个带有通配符 `?` 的字符串 $S$，问有多少种填充方法使得得到的字符串 $T$ 可以划分成 $A, B$，使得 $A, B$ 均非空，且 $A + rev(B), rev(A) + B$ 均为回文串。对 $998244353$ 取模。
>
> $1\le |S|\le 5\times 10^4$。

设 $C = rev(B)$，则 $A+C$ 和 $rev(A) + rev(C)$ 都是回文串，这实际上是在说 $A + C$ 和 $C + A$ 都是回文串。现在我们断言此时只有两种情况：

1. $A$ 和 $C$ 有公共的最小真周期 $P$。不难发现 $P$ 为回文串。
2. $A$ 和 $C$ 有公共周期 $P$，$P$ 为回文串且 $|A| = \frac{2p+1}{2}|P|,|C| = \frac{2q+1}{2}|P|,p,q\in \mathbb N$。也就是 $A+C$ 有偶数长度且回文的最小真周期 $P$，且两个串的切割点恰好将一个周期从正中央切开。

证明如下：

> 不妨设 $|A| > |C|$，$A = rev(C) + D$，不难发现 $D$ 为回文串。此时考虑 $C + A = C+rev(C) + D$，注意到 $C + rev(C)$ 为回文串，且 $D$ 为回文串。由于 $C+A$ 是回文串，所以这两个回文串作为回文串的回文前后缀，都是它的 Border，又由 Border 理论，它们都是原串的周期。根据弱周期引理，它们的 $\gcd$ 也是原串的周期，也就是存在 $2|C|$ 和 $|D|$ 的公约数 $g$ 使得 $g$ 是 $C+A$ 的周期，于是得证。

对于第一种情况，我们知道 $S$ 也必须是由某个回文串不断重复得来。可以枚举 $|S|$ 的约数并用并查集合并相同的字符，计算周期为特定长度的方案数。

对于第二种情况，除了周期长度以外，还需要枚举断开位置。考虑原串的结构：$A(BA)_x(AB)_yA$，其中 $x+y = \frac{|S|}{|P|}$，且 $B = rev(A)$。注意到我们只关心某种划分方式有多少个回文周期中的元素受到非 `?` 元素的限制，以及这些限制是否存在矛盾。通过一些预处理容易求得特定周期长度的方案数。

考虑如何去重，如果 $T$ 既可以表示成 $P_x$ 又可以表示为 $C(DC)_y(CD)_zC$，则 $CD$ 或 $DC$ 与 $P$ 有着公共真周期，且显然这一周期回文。如果 $T$ 既可以表示为 $A(BA)_x(AB)_yA$ 又可以表示为 $C(DC)_p(CD)_qC$，则 $AB, BA$ 与 $CD, DC$ 中的某两个存在公共真周期，这就说明存在 $E, F = rev(E)$ 使得 $A = (EF)_tE$。通过容斥处理掉这些情况即可。

具体实现和一些细节可以看代码。

```cpp
// Author: kyEEcccccc

#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using ULL = unsigned long long;

#define F(i, l, r) for (int i = (l); i <= (r); ++i)
#define FF(i, r, l) for (int i = (r); i >= (l); --i)
#define MAX(a, b) ((a) = max(a, b))
#define MIN(a, b) ((a) = min(a, b))
#define SZ(a) ((int)((a).size()) - 1)

constexpr int N = 50005, MOD = 998244353;

int n;
string s;
ULL res1[N];
vector<ULL> res2[N];
int typ[N], typ2[N];

ULL calc1(int l)
{
	memset(typ, -1, sizeof (typ));
	F(i, 0, n - 1)
	{
		if (s[i] == '?') continue;
		int x = min(i % l, l - 1 - i % l);
		if (typ[x] != -1 && typ[x] != s[i] - 'a') return 0;
		else typ[x] = s[i] - 'a';
	}
	ULL ans = 1;
	F(i, 0, (l - 1) / 2) if (typ[i] == -1) (ans *= 26) %= MOD;
	return ans;
}

void calc2(int l)
{
	memset(typ, -1, sizeof (typ));
	memset(typ2, -1, sizeof (typ2));
	F(i, 0, l - 1) if (s[i] != '?') typ[i] = s[i] - 'a';
	F(i, l, n - l - 1)
	{
		int x = i - i % l * 2 - 1;
		typ[i] = typ[x];
		if (s[i] == '?') continue;
		if (typ[i] == -2 || (typ[i] != -1 && typ[i] != s[i] - 'a')) typ[i] = -2;
		else typ[i] = s[i] - 'a';
	}
	F(i, 0, l - 1) if (s[n - 1 - i] != '?') typ2[n - 1 - i] = s[n - 1 - i] - 'a';
	F(i, l, n - l - 1)
	{
		int x = i - i % l * 2 - 1;
		typ2[n - 1 - i] = typ2[n - 1 - x];
		if (s[n - 1 - i] == '?') continue;
		if (typ2[n - 1 - i] == -2 || (typ2[n - 1 - i] != -1
			&& typ2[n - 1 - i] != s[n - 1 - i] - 'a')) typ2[n - 1 - i] = -2;
		else typ2[n - 1 - i] = s[n - 1 - i] - 'a';
	}

	res2[l * 2].assign(n, 0);
	F(i, 0, n / l / 2 - 1)
	{
		int x = l * (2 * i + 1);
		ULL pd = 1;
		F(j, 0, l - 1)
		{
			if (typ[x - l + j] == -2 || typ2[x + j] == -2) pd = 0;
			else if (typ[x - l + j] == -1 && typ2[x + j] == -1) (pd *= 26) %= MOD;
			else if (typ[x - l + j] == -1 || typ2[x + j] == -1) pd *= 1;
			else if (typ[x - l + j] == typ2[x + j]) pd *= 1;
			else pd = 0;
		}
		res2[l * 2][x] = pd;
	}
}

signed main(void)
{
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(nullptr);

	cin >> n;
	cin >> s;
	// s = '#' + s;
	F(i, 1, n / 2)
	{
		if (n % i == 0) res1[i] = calc1(i);
		if (n % i == 0 && (n / i) % 2 == 0) calc2(i);
	}
	// cerr << res2[n][n / 2] << '\n';
	ULL ans = 0;
	F(i, 1, n / 2)
	{
		if (n % i != 0) continue;
		(ans += res1[i]) %= MOD;
		F(j, 2, n / i)
		{
			if (n % (i * j) != 0) continue;
			if (i * j < n) (res1[i * j] += MOD - res1[i]) %= MOD;
			if (j % 2 == 0)
			{
				F(k, 0, n / (i * j) - 1)
				{
					int x = (k * 2 + 1) * (i * j / 2);
					(res2[i * j][x] += MOD - res1[i]) %= MOD;
				}
			}
		}
		if (i % 2 != 0) continue;
		F(k, 0, n / i - 1)
		{
			int x = (k * 2 + 1) * (i / 2);
			(ans += res2[i][x]) %= MOD;
		}
		F(j, 2, n / i)
		{
			if (n % (i * j) != 0) continue;
			if (j % 2 == 0) continue;
			F(k, 0, n / (i * j) - 1)
			{
				int x = (k * 2 + 1) * (i * j / 2);
				(res2[i * j][x] += MOD - res2[i][x]) %= MOD;
			}
		}
	}
	if (n % 2 == 0) (ans += res2[n][n / 2]) %= MOD;
	cout << ans % MOD << '\n';
	
	return 0;
}
```

---

## 作者：OptimisticForever (赞：0)

>定义一个串为**好字符串**，当且仅当其有划分 $A,B$，使得 $A,B$ 均非空，且 $A+rev(B),rev(A)+B$ 均为回文串，问替换 `？` 有多少方案使得串 $S$ 为**好字符串**。
>
>$|S|\leq 50000$。

记 $S$ 为一个好字符串。

设 $C=rev(B)$，则题目要求即 $A+C$ 和 $rev(A)+rev(C)$ 都为回文串，把后者翻转，意味着 $A+C$ 和 $C+A$ 都是回文串。

考虑若 $A+C$ 为一个串 $P $ 的若干拼接，那么根据 $A+C$ 回文，我们可以得到 $P$ 为回文串。注意这里必须保证 $\frac{|S|}{|P|}>1$，这是显然的。而且由于 $P$ 为回文串，我们可以得到 $C=rev(C)$， 因此，原串也呈现这样的结构。

注意到 `ababbaab` 也是一个合法的串，因为你考虑可以将其划分为 `ab` 以及 `abbaab`。这类似一个 $\cdots+A+A+\cdots$ 的结构，仔细分析一下，我们可以观察到，$A+C$ 有长度为偶数的最小回文周期 $P$，且 $P$ 恰好把 $A+C$ 的中间线跨过。相当于 $|A|=\frac{2k_1+1}{2}|P|,|C|=\frac{2k_2+1}{2}|P|$。下面考虑证明这个结论：

不妨设 $|A|\ge |C|$，设 $A=rev(C)+D$，那么我们容易发现 $D$ 是回文串。则 $C+A=C+rev(C)+D$，此时式子左边是回文串，并且右边是两个回文串的拼接！根据 Border 理论，我们容易得知，$2|C|,|D|$ 都是 $C+A$ 的周期，根据弱周期引理可得，存在 $g|\gcd(2|C|,|D|)$ 满足 $g$ 是 $C+A$ 的周期，于是得证！

现在我们发掘了 $A+C$ 的性质，考虑转回原串。

对于第一个性质，显然原串也是若干个回文拼接。

对于第二个性质，我们可以得出原串为 $(A+rev(A))+\cdots (A+rev(A))+A+A+(rev(A)+A)+\cdots +(rev(A)+A)$，其中前面和后面的部分可以不存在。

考虑如何计数，首先我们先预处理出 $f_i$ 表示长度为 $i$ 的回文串若干拼接的方案数，这个可以扫一遍解决。

然后处理出 $g_{i,j}$ 表示 $A+rev(A)=i$，并且目前中间的分割线在位置 $j$ 的方案数，维护一个前缀桶和后缀桶可以解决。

然后考虑容斥，首先，如果存在多个 $i$，满足 $i$ 贡献到了串 $S$，我们考虑在最小的 $i$ 上计数。

显然 $f_{i\times j}\leftarrow f_{i\times j}-f_i$。

现在处理 $g,f$ 的算重问题，假设 $S$ 可以表示为 $P+\cdots +P$ 并且可以表示为 $(A+rev(A))+\cdots (A+rev(A))+A+A+(rev(A)+A)+\cdots +(rev(A)+A)$。假设 $|P|<|A+rev(A)|$，那么需要容斥，可以发现，此时必须保证 $\frac{|A+rev(A)|}{|P|}\bmod 2=0$。假设 $S$ 可以表示为 $(A+rev(A))+\cdots (A+rev(A))+A+A+(rev(A)+A)+\cdots +(rev(A)+A)$ 以及 $(B+rev(B))+\cdots (B+rev(B))+B+B+(rev(B)+B)+\cdots +(rev(B)+B)$。假设 $|A|<|B|$。那么需要保证 $\frac{|B|}{|A|}\bmod 2=1$，而且我们还需要求分割线相同。

注意可能会出现 $A+A$ 这种情况，需要特判。

坑：维护前缀桶和后缀桶的时候，一定要注意翻转串之后需要翻回来；注意一些下标问题！！！

参考资料：现有的题解。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005,mod=998244353;
int n,f[N],las[N],ls[N],pw[N];
bool bz1[N],bz2[N];
string S,SS;
vector<int>g[N];
void add(int &x,int y){x+=y,x-=(x>=mod?mod:0);}
void sub(int &x,int y){x-=y,x+=(x<0?mod:0);}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>S;SS=S;reverse(SS.begin(),SS.end());
	pw[0]=1;
	for (int i=1;i<=n;++i)pw[i]=1ll*pw[i-1]*26%mod;
	for (int i=1;i*2<=n;++i){
		if (n%i==0){
			for (int j=0;j<n;++j)las[j]=-1;
			bool ck=1;
			for (int j=0;j<n;++j){
				int k=min(j%i,i-1-j%i);
				if (S[j]=='?')continue;
				if (las[k]==-1){
					las[k]=S[j]-'a';
				}
				else if (las[k]+'a'!=S[j]){
					ck=0;
				}
			}
			if (!ck)continue;
			for (int j=0;j<(i+1)/2;++j)if (las[j]==-1)++f[i];
			f[i]=pw[f[i]];
		}
	}
	for (int i=1;i*2<=n;++i){
		if (n%i==0&&(n/i)%2==0){
			g[i*2].resize(n);
			for (int j=0;j<n;++j)las[j]=-1,bz1[j]=0;
			for (int j=0;j<n;++j)ls[j]=-1,bz2[j]=0;
			for (int j=0;j<n;++j){
				if (j)bz1[j]|=bz1[j-1];
				int k=j-1-(j%i)*2;
				if (j<i)k=j;
				las[j]=las[k];
				if (S[j]=='?'){
					if (j)bz1[j]|=bz1[j-1];
					continue;
				}
				if (las[j]==-1)las[j]=S[j]-'a';
				else if (las[j]+'a'!=S[j])bz1[j]=1;
			}
			for (int j=0;j<n;++j){
				if (j)bz2[j]|=bz2[j-1];
				int k=j-1-(j%i)*2;
				if (j<i)k=j;
				ls[j]=ls[k];
				if (SS[j]=='?'){
					if (j)bz2[j]|=bz2[j-1];
					continue;
				}
				if (ls[j]==-1)ls[j]=SS[j]-'a';
				else if (ls[j]+'a'!=SS[j])bz2[j]=1;
			}
			reverse(ls,ls+n);
			for (int x=0;;++x){//A=(2x+1)i
				int Len=(2*x+1)*i;
				if (Len>n)break;
				if (bz1[Len-1]||bz2[n-Len-1])continue;
				bool ck=0;
				for (int j=0;j<i;++j){
					if (las[Len-i+j]!=-1&&ls[Len+j]!=-1){
						if (ls[Len+j]!=las[Len-i+j])ck=1;
					}
					else if (las[Len-i+j]==-1&&ls[Len+j]==-1){
						++g[i*2][Len-1];
					}
				}
				if (ck){
					g[i*2][Len-1]=0;
					continue;
				}
				g[i*2][Len-1]=pw[g[i*2][Len-1]];
			}
		}
	}
	int ans=0;
	for (int i=1;i*2<=n;++i){
		if (n%i==0){
			for (int j:g[i])add(ans,j);
			add(ans,f[i]);
			for (int j=i+i;j<=n/2;j+=i)sub(f[j],f[i]);
			for (int j=i+i;j<=n;j+=i){
				if (g[j].empty())continue;
				if ((j/i)&1)continue;
				int o=j/2;
				for (int k=o;k<=n;k+=j)sub(g[j][k-1],f[i]);
			}
			if (i%2==0&&(!g[i].empty())){
				for (int j=i+i;j<=n;j+=i){
					if (g[j].empty())continue;
					int o=j/2;
					for (int k=o;k<=n;k+=j)sub(g[j][k-1],g[i][k-1]);
				}
			}
		}
	}
	if (n%2==0)add(ans,g[n][n/2-1]);
	cout<<ans;
}
```

---

