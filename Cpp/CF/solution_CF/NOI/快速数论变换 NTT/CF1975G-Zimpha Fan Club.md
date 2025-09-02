# Zimpha Fan Club

## 题目描述

有一天，Zimpha 随意想出了一个问题。作为“Zimpha 粉丝俱乐部”的一员，你决定来解决这个问题。

给定两个字符串 $s$ 和 $t$，长度分别为 $n$ 和 $m$。两个字符串只包含小写英文字母、`-` 和 `*`。

你需要按照以下规则替换所有的 `*` 和 `-`：

- 每个 `-` 必须被替换为任意一个小写英文字母。
- 每个 `*` 必须被替换为任意长度（可能为零）的、只包含小写英文字母的字符串。

注意，你可以将两个不同位置的 `-` 替换为不同的字母，也可以将两个不同位置的 `*` 替换为不同的字符串。

假设 $s$ 和 $t$ 被分别替换成 $s'$ 和 $t'$。现在你想知道，是否存在一种替换方式，使得 $s' = t'$。

## 说明/提示

在第二个测试用例中，我们可以将两个字符串都变成 ttklwxx。在 $s$ 中，`-` 被替换为 l。在 $t$ 中，`*` 被替换为空串，第一个和第二个 `-` 被分别替换为 k 和 w。

在第五个测试用例中，我们可以将两个字符串都变成 bulijiojioxdibuliduo。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10 10
justmonika
j-stsayori```

### 输出

```
No```

## 样例 #2

### 输入

```
7 8
ttk-wxx
*tt-l-xx```

### 输出

```
Yes```

## 样例 #3

### 输入

```
13 11
asoulwangziji
-soulg*z-y-```

### 输出

```
No```

## 样例 #4

### 输入

```
7 3
abc*cba
a*c```

### 输出

```
No```

## 样例 #5

### 输入

```
20 18
bulijiojio-dibuliduo
*li*ji-*ox*i*-du*-```

### 输出

```
Yes```

# 题解

## 作者：cyffff (赞：8)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1975G)
## 题意
给你两个长度分别为 $n,m$ 的字符串 $s,t$，其中仅包含小写字母、`-` 和 `*`，你需要将 `-` 替换为任意小写字母，`*` 替换为任意小写字母构成的字符串（可以为空串），问是否可以使得 $s'=t'$。

$n,m\le 2\times 10^6$，12s。

## 思路

首先我们有工具：[NTT 优化带通配符的字符串匹配](https://www.luogu.com.cn/problem/P4173)。对于两个不含 `*` 的字符串 $s,t$，我们可以求出 $s$ 能匹配 $t$ 中的哪些子串。具体地，构造序列 $a,b$，如果 $s_i$ 是通配符则 $a_i=0$，否则 $a_i$ 表示 $s_i$ 是第几个字母，$b_i$ 同理。

那么如果 $s$ 能匹配 $t_{i,\dots,i+m-1}$，当且仅当

$$f_i=\sum_{j=0}^{m-1}(t_{i+j}-s_j)^2t_{i+j}s_j=0$$

把括号拆掉后三次差卷积可以计算。

****

回到原问题，我们发现 `*` 比较难处理。

经过手玩，$s,t$ 同时都有 `*` 的情况是简单的：令 $p$ 为最小的数使得 $s_p$ 或 $t_p$ 为 `*`，则 $s_{0,\dots,p-1}$ 要匹配 $t_{0,\dots,p-1}$，后缀同理。而 $s,t$ 同时不含 `*` 的情况更为平凡，直接逐位判断即可。

于是经过平凡的操作，我们将问题转化成了 $s$ 形如 $*s_1*s_2*\cdots*s_k*$，而 $t$ 不含 `*` 的形式。于是就有贪心：$s_1$ 匹配 $t$ 中第一个能匹配的位置，并将其匹配位置及其前所有字符都删去，按同样的方式依次匹配 $s_{2\dots k}$，如果全部成功匹配则有解，否则无解。

但如果每次直接将 $s_i$ 与 $t$ 做 NTT 字符串匹配复杂度不可接受，我们发现时间复杂度的浪费主要为我们只需要找到 $s_i$ 在 $t$ 中第一个匹配的位置，但我们把所有位置是否匹配都求出来了。

如果字符串无通配符，则我们可以在 $O(1)$ 时间内判断 $s_i$ 与 $t$ 中以 $p$ 开头的等长字符串是否匹配，所以我们可以从左向右依次判断，以 $O(1)$ 的代价删去一个字符。而带上通配符，我们可以在 $O((r-l+|s_i|)\log (r-l+|s_i|))$ 的时间复杂度内内判断 $s_i$ 与 $t$ 中以 $[l,r]$ 开头的等长字符串是否匹配，据此，我们可以想到优化的思路：在 $l$ 相关的时间复杂度内删去 $l$ 个字符。

我们每次把 $s_i$ 与 $t$ 的前 $2|s_i|$ 个字符进行匹配，在 $p$ 位置匹配成功则把 $t_{p+|s_i|-1}$ 及以前的字符全部删除，否则删除 $t$ 的前 $l$ 个字符。容易发现这符合我们的需求——在 $O(|s_i|\log |s_i|)$ 的时间复杂度内删去了不少于 $|s_i|$ 个字符。

时间复杂度 $O(n\log n)$。

核心代码：
```cpp
inline Poly MulR(const Poly &a,const Poly &b){
	int n=a.size(),m=b.size();
	Poly F=a,G=b;
	reverse(G.begin(),G.end());
	F=F*G;
	Poly H;
	for(int i=0;i<n-m+1;i++)
		H.push_back(F[i+m-1]);
	return H;
}
int n,m;
short s[M],t[M];
Poly F1,G1,F2,G2,F3,G3,H;
inline int check(int l1,int r1,int l2,int r2){
	F1.clear(),F2.clear(),F3.clear();
	for(int i=l2;i<=r2;i++){
		int v=t[i];
		F1.push_back(v),F2.push_back(v*v),F3.push_back(v*v*v);
	}
	G1.clear(),G2.clear(),G3.clear();
	for(int i=l1;i<=r1;i++){
		int v=s[i];
		G1.push_back(v),G2.push_back(v*v),G3.push_back(v*v*v);
	}
	H=MulR(F3,G1)+MulR(F1,G3)-MulR(F2,G2)*2;
	for(int i=0;i<H.size();i++)
		if(!H[i])
			return l2+i;
	return -1;
}
int main(){
//	freopen("G.in","r",stdin);
	n=read(),m=read();
	bool fls=0,flt=0;
	for(int i=1;i<=n;i++){
		char c=getc();
		if(c=='*') fls=1,s[i]=-1;
		else s[i]=c=='-'?0:c-'a'+1;
	}
	for(int i=1;i<=m;i++){
		char c=getc();
		if(c=='*') flt=1,t[i]=-1;
		else t[i]=c=='-'?0:c-'a'+1;
	}
	if(!fls&&!flt){
		bool fl=n==m;
		for(int i=1;i<=n;i++)
			fl&=!s[i]||!t[i]||s[i]==t[i];
		return puts(fl?"Yes":"No"),0;
	}
	if(fls&&flt){
		for(int i=1;;i++)
			if(s[i]==-1||t[i]==-1) break;
			else if(s[i]&&t[i]&&s[i]!=t[i]) return puts("No"),0;
		for(int i=n,j=m;;i--,j--)
			if(s[i]==-1||t[j]==-1) break;
			else if(s[i]&&t[j]&&s[i]!=t[j]) return puts("No"),0;
		return puts("Yes"),0;
	}
	if(!fls) swap(n,m),swap(s,t);
	Prefix(n+m);
	int sts=0,stt=0,eds=0,edt=0;
	for(int i=1;;i++)
		if(s[i]==-1||t[i]==-1){ sts=stt=i;break; }
		else if(s[i]&&t[i]&&s[i]!=t[i]) return puts("No"),0;
	for(int i=n,j=m;;i--,j--)
		if(s[i]==-1||t[j]==-1){ eds=i,edt=j;break; }
		else if(s[i]&&t[j]&&s[i]!=t[j]) return puts("No"),0;
	while(s[sts]==-1) sts++;
	for(int i=sts,j=stt;i<=eds;){
		int r=i;
		while(r+1<=n&&s[r+1]!=-1) r++;
		int l=r-i+1;
		while(1){
			if(j>edt) return puts("No"),0;
			int jr=min(edt,j+l*2);
			int tmp=check(i,r,j,jr);
			if(tmp==-1) j+=l;
			else{ j=tmp+l;break; }
		}
		while(r+1<=n&&s[r+1]==-1) r++;
		i=r+1;
	}
	puts("Yes");
}
```

---

## 作者：BAKABAKABAKABAKA (赞：4)

![](https://s21.ax1x.com/2025/02/18/pEMgc7Q.png)

### 前置芝士

[NTT 优化通配符字符串匹配](https://www.luogu.com.cn/problem/P4173)，本人属实菜，这里只给一个第二篇题解的[链接](https://www.luogu.com.cn/article/n3zyj7d9)，顺便给一个第二篇题解的评论：

> 简洁明了，比第一篇一堆废话强多了。赞了！

好的，现在我假设您会了。

### 正题

此题比普通通配符多一个 `*`。而 `*` 能干的事情非常多，所以考虑先没有 `*` 的和都有 `*` 的。

没有 `*` 的显然，都有 `*` 的发现只要匹配 `*` 的前缀和后缀，因为珂以用中间的 `*` 匹配中间的字符：

然后就是有一个串有 `*` 的，不妨令 $s$ 有 `*`。首先与上面一样需要匹配前后缀，并顺便删掉，然后考虑将 $s$ 拆成许多个没有 `*` 的字符串 $s_1, s_2, \cdots, s_k$ 与 `*` 组成（我的代码要判 `*` 相邻的情况，就这样交了 $40$ 发 /ll）。

然后因为 $t$ 中是没有 `*` 的，那么 $s_1, s_2, \cdots, s_k$ 一定是 $t$ 中的不相交且按顺序排列的子串，而又因为相邻的 $s$ 中有 `*`，于是条件充分。

因此珂以直接用 NTT 优化通配符匹配找到最左子串，因为显然是越左边条件越松，直接维护一个当前左端点 $L$ 即可。

直接做就是高贵的 $\Theta(nm \log n)$，但是非常浪费。于是考虑 $s_i$ 匹配的时候先找 $2|s_i|-1$ 个位置（即 $|s_i|$ 个开头），失配就让左端点 $L \leftarrow L + |s_i|$，否则与上面一样。

现在时间就为 $\Theta(n \log n)$。然后此题凉心出题人给出了 $n, m \le 2 \times 10^6$ 的好限制，所以不能预处理 $\omega$。而且出题人还顺便贴心的卡了下模数，所以需要 ~~MTT，FTT~~ 随机赋权。

```cpp
#include <bits/stdc++.h>

#define i16 short
#define i32 signed
#define i64 long long
#define i128 __int128_t

#define u16 unsigned short
#define u32 unsigned
#define u64 unsigned long long
#define u128 __uint128_t

#define f32 float
#define f64 double

template < typename T > inline const T max(const T x, const T y) { return (x > y) ? (x) : (y); }
template < typename T > inline const T min(const T x, const T y) { return (x < y) ? (x) : (y); }
template < typename T > inline const T abs(const T x) { return (x < 0) ? (-x) : x; }

#define ll long long
// #define int long long
// #define int __int128_t

const i32 N = 5e6;
const i32 mod = 998244353, g = 3, inv2 = mod + 1 >> 1;
inline i32 ca(i32 x) { return x + (x >> 31 & mod); }
inline void sw(i32& x, i32& y) { x ^= y ^= x ^= y; }
typedef std::vector < i32 > poly;
i32 R[N];
inline i32 ksm(i32 x, i32 y, i32 res = 1)
{
	while (y)
		if (y & 1) res = 1ll * res * x % mod, y >>= 1, x = 1ll * x * x % mod;
		else y >>= 1, x = 1ll * x * x % mod;
	return res;
}
inline void NTT_init(i32 n)
{
	i32 k = 1; while ((1 << k) < n) k++;
	for (i32 i = 0; i < n; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << k - 1);
}
inline void NTT(i32 n, poly& a, bool type)
{
	a.resize(n);
	for (i32 i = 0; i < n; i++)
		if (i < R[i]) sw(a[i], a[R[i]]);
	i32 tmp = 1;
	for (i32 deep = 1, m = 2, len = 1; m <= n; deep++, m <<= 1, len <<= 1)
	{
		tmp = 1ll * tmp * inv2 % mod;
		i32 w = ksm(g, (mod - 1) >> deep);
		if (!type) w = ksm(w, mod - 2);
		for (i32 pos = 0; pos < n; pos += m)
			for (i32 i = pos, j = pos + len, tmp, wn = 1; i < pos + len; i++, j++, wn = 1ll * wn * w % mod)
				tmp = 1ll * wn * a[j] % mod,
				a[j] = ca(a[i] - tmp),
				a[i] = ca(a[i] + tmp - mod);
	}
	if (!type) for (i32 i = 0; i < n; i++) a[i] = 1ll * a[i] * tmp % mod;
}
i32 pp[26];
inline poly Mat(char* s1, char* s2, i32 n, i32 m, char sp)
{
#define ____calc(x) ((x == sp) ? 0 : (pp[x - 'a']))
	i32 limit = 1;
	while (limit < (n + n)) limit <<= 1;
	poly a(n), b(m), res(limit);
	NTT_init(limit);

	for (i32 i = 0; i < n; i++)
		a[i] = 1ll * ____calc(s1[i]) * ____calc(s1[i]) % mod * ____calc(s1[i]) % mod;
	for (i32 i = 0; i < m; i++)
		b[i] = ____calc(s2[m - i - 1]);
	NTT(limit, a, 1), NTT(limit, b, 1);
	for (i32 i = 0; i < limit; i++) res[i] = 1ll * a[i] * b[i] % mod;

	a.resize(n), b.resize(m);
	for (i32 i = 0; i < n; i++)
		a[i] = ____calc(s1[i]);
	for (i32 i = 0; i < m; i++)
		b[i] = 1ll * ____calc(s2[m - i - 1]) * ____calc(s2[m - i - 1]) % mod * ____calc(s2[m - i - 1]) % mod;
	NTT(limit, a, 1), NTT(limit, b, 1);
	for (i32 i = 0; i < limit; i++) res[i] = ca(res[i] + 1ll * a[i] * b[i] % mod - mod);

	a.resize(n), b.resize(m);
	for (i32 i = 0; i < n; i++)
		a[i] = 1ll * ____calc(s1[i]) * ____calc(s1[i]) % mod;
	for (i32 i = 0; i < m; i++)
		b[i] = 1ll * ____calc(s2[m - i - 1]) * ____calc(s2[m - i - 1]) % mod;
	NTT(limit, a, 1), NTT(limit, b, 1);
	for (i32 i = 0; i < limit; i++) res[i] = ca(res[i] - 2ll * a[i] * b[i] % mod);

	NTT(limit, res, 0); a.clear();
	for (i32 i = m - 1; i < n; i++) if (!res[i]) a.emplace_back(i - m + 1);
	return a;
}
i32 n, m;
char s1[N], s2[N];
inline bool equiv(char a, char b) { return a == '-' || b == '-' || a == b; }
namespace SpecialA
{
	inline bool check()
	{
		for (i32 i = 0; i < n; i++) if (s1[i] == '*') return false;
		for (i32 i = 0; i < m; i++) if (s2[i] == '*') return false;
		return true;
	}
	inline void solov()
	{
		if (n ^ m) return std::cout << "No\n", void();
		for (i32 i = 0; i < n; i++)
			if (!equiv(s1[i], s2[i])) return std::cout << "No\n", void();
		std::cout << "Yes\n";
	}
};
namespace SpecialB
{
	inline bool check()
	{
		i32 cnt = 0; for (i32 i = 0; i < n; i++) if (s1[i] == '*') cnt++; if (!cnt) return false; cnt = 0;
		for (i32 i = 0; i < m; i++) if (s2[i] == '*') cnt++; if (!cnt) return false; return true;
	}
	inline void solov()
	{
		i32 L1 = 0, R1 = n - 1, L2 = 0, R2 = m - 1;
		while (s1[L1] ^ '*') L1++; while (s1[R1] ^ '*') R1--;
		while (s2[L2] ^ '*') L2++; while (s2[R2] ^ '*') R2--;
		L1 = min(L1, L2);
		R1 = (n - R1 > m - R2) ? (R2 - m + n) : (R1);
		for (i32 i = 0; i < L1; i++) if (!equiv(s1[i], s2[i])) return std::cout << "No\n", void();
		for (i32 i = R1 + 1; i < n; i++) if (!equiv(s1[i], s2[i - n + m])) return std::cout << "No\n", void();
		std::cout << "Yes\n";
	}
};
namespace SpecialC
{
	inline bool check()
	{
		i32 cnt = 0; for (i32 i = 0; i < n; i++) if (s1[i] == '*') cnt++;
		if (!cnt)
		{
			for (i32 i = 0; i < max(n, m); i++) s1[i] ^= s2[i] ^= s1[i] ^= s2[i];
			n ^= m ^= n ^= m;
		}
		return true;
	}
	i32 p[N], pi;
	inline void solov()
	{
		for (i32 i = 0; i < n; i++)
			if (s1[i] == '*') p[++pi] = i;
		i32 L = 0, R = n - 1;
		while (s1[L] != '*') L++;
		while (s1[R] != '*') R--;
		if (L + n - 1 - R > m) return std::cout << "No\n", void();	//前后缀比另一个串总长还长
		for (i32 i = 0; i < L; i++) if (!equiv(s1[i], s2[i])) return std::cout << "No\n", void();
		for (i32 i = R + 1; i < n; i++) if (!equiv(s1[i], s2[i - n + m])) return std::cout << "No\n", void();
		m = R - n + m, n = R;
		for (i32 i = 1; i < pi; i++)
		{
			if (p[i] == p[i + 1] - 1) continue;
			while (1)
			{
				poly ans = Mat(s2 + L, s1 + p[i] + 1, min(2 * p[i + 1] - 2 * p[i] - 3, m - L + 1), p[i + 1] - p[i] - 1, '-');
				L += p[i + 1] - p[i] - 1;
				if (!ans.empty()) { L += ans[0]; break; }
				if (L > m) return std::cout << "No\n", void();
			}
		}
		std::cout << "Yes\n";
	}
};
std::mt19937 rnd(time(0));
inline void ___()
{
	for (i32 i = 0; i < 26; i++) pp[i] = (rnd() % (mod - 1) + 1);	//随机赋权
	std::ios::sync_with_stdio(false), std::cin.tie(), std::cout.tie();
	std::cin >> n >> m >> s1 >> s2;
	if (SpecialA::check()) return SpecialA::solov();	//没有*
	if (SpecialB::check()) return SpecialB::solov();	//均有*
	if (SpecialC::check()) return SpecialC::solov();	//otherwise
}
signed main()
{
	i32 T = 1; //std::cin >> T;
	while (T--) ___();
}
```

---

## 作者：Unnamed114514 (赞：2)

upd on 2025.7.13：代码粘错了，改了一下。

### 前置知识

[Problem Link](https://www.luogu.com.cn/problem/P4173)

首先一个字符对应了一个数，我们先把字符串想象成数列，定义差异函数 $f(i,j)=(a_i-b_j)^2$，若 $f(i,j)$ 为 $0$ 则表示没有差异。用平方是因为如果用和的话会把 `ab` 和 `ba` 判成同一个字符串，没有用绝对值是因为绝对值不便于展开。

我们以 $j$ 为起点判断是否可以匹配，相当于求 $\sum\limits_{i=0}^{n-1}f(i,j+i)=(a_i-b_{j+i})^2=a_i^2+b_{j+i}^2-2a_ib_{j+i}$。前两项直接前缀和处理，第三项是个差卷积，使用 NTT 即可。

注意模数为 $998244353$ 可能会出现一些问题，这时可以不更换模数而对字符串随机赋权进行处理。

现在我们加入通配符，注意到如果 $i,j$ 中有一个为通配符，那么 $f(i,j)=0$，对于 $a_i$ 和 $b_j$ 是没有定义的，我们考虑把 $a_i$ 和 $b_j$ 定义为 $0$，$f(i,j)$ 修改为 $f(i,j)=(a_i-b_j)^2a_ib_j$，然后你会发现符合通配符的定义。

仍然是拆式子，拆出来是三个差卷积，注意此时并不需要 $9$ 次 FTT，得到点值之后先操作完再一起 IFFT，总共是 $7$ 次。

### 回归本题

本题最大的难点在于加入了 `*`。

先对 `*` 的出现进行讨论：

- 如果都没出现，暴力匹配即可。

- 如果都出现了，先找到 $s,t$ 最左边的 `*`，它前面这个前缀肯定是要匹配的，后缀同理，对于中间的串，可以先用 $t$ 中一个 `*` 把 $s$ 中的字符搞完，再用 $s$ 中一个 `*` 把 $t$ 中所有字符搞完，显然是可以的。

现在不妨设 $s$ 中含有 `*`，然后仍然类似地，先把两头判了。

如果两头的覆盖范围相交了，显然也是不行的。

然后这个时候我们问题就转化为了给你若干个串 $s_1,s_2,\cdots s_k$，问你它们在 $t$ 中是否先后不重复地出现。

如果每次直接在 $t$ 中暴力匹配的话，是会 $T$ 的。

考虑如下操作：对于每个 $s_i$，我们每次找 $|s_i|$ 个起点进行判断，如果有可行的话，那就选，没有就继续找。

这样的话，我们就做到了 $O(|s|\log|s|)$ 地搞掉了 $t$ 中 $|s|$ 个节点，因此这个算法均摊复杂度是 $O(\log n)$ 的，总时间复杂度 $O(n\log n)$。

直接模 $998244353$ 会被卡，仍然是随机赋权处理一下即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+5,P=469762049,g=3,invg=156587350;
mt19937 rnd(time(0));
int n,m,n_,m_,A[N],B[N],a[N],b[N],c[N],d[N],e[N],up,base,rev[N],mp[26];
string s,t;
void init(int B){ for(int i=0;i<(1<<base);++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(base-1)); } 
int qpow(int a,int b){
	int s=1;
	while(b){
		if(b&1) s=s*a%P;
		a=a*a%P,b>>=1;
	}
	return s;
}
void NTT(const int n,int *a,const int op){
	for(int i=0;i<n;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int mid=1;mid<n;mid<<=1){
		const int Wn=qpow(op==1?g:invg,(P-1)/(mid<<1));
		for(int i=0;i<n;i+=(mid<<1)) for(int j=0,w=1;j<mid;++j,w=w*Wn%P){
			int y=w*a[i+j+mid]%P;
			a[i+j+mid]=(a[i+j]-y+P)%P;
			a[i+j]=(a[i+j]+y)%P;
		}
	}
}
int match(int L,int R,int l,int r){
	n_=R-L+1,m_=r-l+1;
	if(m_<n_) return -1;
	for(int i=0;i<n_;++i) 
		if(s[L+i]=='-') A[m_-1-i]=0;
		else A[m_-1-i]=mp[s[L+i]-'a']; 
	for(int i=0;i<m_;++i) 
		if(t[l+i]=='-') B[i]=0;
		else B[i]=mp[t[l+i]-'a'];
	base=0,up=1;
	while(up<=m_+m_-1) up<<=1,++base;
	init(base);
	for(int i=0;i<up;++i) a[i]=A[i]*A[i]%P*A[i]%P,b[i]=B[i];
	NTT(up,a,1),NTT(up,b,1);
	for(int i=0;i<up;++i) c[i]=a[i]*b[i]%P;
	for(int i=0;i<up;++i) a[i]=A[i],b[i]=B[i]*B[i]%P*B[i]%P;
	NTT(up,a,1),NTT(up,b,1);
	for(int i=0;i<up;++i) c[i]=(c[i]+a[i]*b[i])%P;
	for(int i=0;i<up;++i) a[i]=A[i]*A[i]%P,b[i]=B[i]*B[i]%P;
	NTT(up,a,1),NTT(up,b,1);
	for(int i=0;i<up;++i) c[i]=(c[i]-2*a[i]*b[i]%P+P)%P;
	NTT(up,c,-1);
	for(int i=0;i<n_;++i) A[m_-1-i]=0;
	for(int i=0;i<m_;++i) B[i]=0;
	const int inv=qpow(up,P-2);
	for(int i=0;i+n_-1<m_;++i) if(!(c[m_-1+i]*inv%P)) return l+i;
	return -1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>s>>t;
	for(int i=0;i<26;++i) mp[i]=rnd()%998244352+1;
	bool flg1=0,flg2=0;
	for(int i=0;i<n;++i) if(s[i]=='*'){
		flg1=1;
		break;
	}
	for(int i=0;i<m;++i) if(t[i]=='*'){
		flg2=1;
		break;
	}
	if(!flg1&&!flg2){
		if(n!=m){
			cout<<"No"<<endl;
			return 0;
		}
		for(int i=0;i<n;++i) if(s[i]!='-'&&t[i]!='-'&&s[i]!=t[i]){
			cout<<"No"<<endl;
			return 0;
		}
		cout<<"Yes"<<endl;
		return 0;
	}
	if(flg1&&flg2){
		for(int i=0;i<n;++i){
			if(s[i]=='*'||t[i]=='*') break;
			if(s[i]!='-'&&t[i]!='-'&&s[i]!=t[i]){
				cout<<"No"<<endl;
				return 0;
			}
		}
		for(int i=1;i<=n;++i){
			if(s[n-i]=='*'||t[m-i]=='*') break;
			if(s[i]!='-'&&t[i]!='-'&&s[i]!=t[i]){
				cout<<"No"<<endl;
				return 0;
			}
		}
		cout<<"Yes"<<endl;
		return 0;
	}
	if(flg2) swap(s,t),swap(n,m);
	int l=-1,r=m;
	for(int i=0;i<n;++i){
		if(s[i]=='*') break;
		if(i>=m||(s[i]!='-'&&t[i]!='-'&&s[i]!=t[i])){
			cout<<"No"<<endl;
			return 0;
		}
		l=i;
	}
	++l;
	for(int i=1;i<=n;++i){
		if(s[n-i]=='*') break;
		if(m-i<0||(s[n-i]!='-'&&t[m-i]!='-'&&s[n-i]!=t[m-i])){
			cout<<"No"<<endl;
			return 0;
		}
		r=m-i;
	}
	if(l+(m-r)>m){
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=l,j;i<n-(m-r);i=j+1){
		j=i;
		if(s[i]=='*') continue;
		while(j+1<=n-(m-r)&&s[j+1]!='*') ++j;
		bool flg=1;
		while(l<r){
			int p=match(i,j,l,min(r-1,l+2*(j-i+1)-1));
			if(p==-1) l+=(j-i+1);
			else{
				l=p+(j-i+1);
				flg=0;
				break;
			}
		}
		if(flg){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}
```

---

## 作者：RedreamMer (赞：2)

感觉 G 比 F 简单。

  首先化简问题，如果两个串开头字符都不是 `*` 那么可以同时删掉，尾部也是。

  接着，判掉已经相同的情况，如果两个串此时都有 `*` 那么一定合法，分情况讨论不难证明。

  现在只剩下一个串含有 `*` 的情况，令它为 $s$，另一个串为 $t$，那么将 $s$ 按 `*` 分成若干个子串，相当于每个子串需要按顺序在 $t$ 中找一个位置匹配上。

  考虑贪心，依次找到每个串最早在 $t$ 的什么位置匹配上，看起来没法快速查找，因为有通配符的存在，单次匹配也不太能哈希之类的算法优化到低于 $\log n$。

  但是，联想到一个带通配符多位置匹配的经典做法，类似万径人踪灭那题：

  记

  $$
  f_i = \sum_{j + k = i} (a_j - b_k) ^ 2 a_j b_k
  $$

  假设 $a$ 是模式串，我们将 $a$ reverse 后做多项式乘法，对于所有 $f$ 位置上为 $0$ 的位置就代表了一次 $a$ 在 $b$ 上的合法匹配。

  将这个做法套用到这题上，我们一次花费 $\mathcal O(|A|\log |A|)$ 的代价，找到 $A$ 在 $t$ 上 $[now, now + 2|A|)$，的所有匹配位置，这样无论是否找到匹配位置，都能给 $t$ 的长度减去至少 $|A|$。

  总时间复杂度 $\mathcal O(n \log n)$，低素质出题人开 2e6 很考验你的多项式板子水平。

  注意因为是 $\bmod 998244353$，数值太大所以可能会冲突，带个暴力 check 或者随机带权即可。

---

## 作者：wwwwwza (赞：0)

设匹配函数 $P(x)=\sum\limits_{i=0}^m (A_i-B_{x-m+i+1})$。

显然，$A_i-B_{x-m+i+1}$ 并没有正负性，所以要平方一下，$P(x)=\sum\limits_{i=0}^m (A_i-B_{x-m+i+1})^2$。

加入**只能代替一个字符**的通用符号，可以将通用符号的权值设为 $0$，$P(x)=\sum\limits_{i=0}^m (A_i-B_{x-m+i+1})^2A_iB_{x-m+i+1}$。

这个式子不太好处理，将其转化 

$$
P(x)=\sum\limits_{i=0}^m (A_{m-i-1}-B_{x-m+i+1})^2A_{m-i-1}B_{x-m+i+1}=\sum\limits_{i+j=x}(A_i-B_j)^2A_iB_j =\sum\limits_{i+j=x}A_i^3B_j+A_iB_j^3-2A_i^2B_j^2

$$

发现只要将 $A$ 翻转，就能得到一个卷积形式，只要做三次 FFT 或 NTT 即可求出答案。

本题又出现了一个**能代替字符串**的通用符 `*`。

显然，字符串 $S,T$ 都没有 `*` 时直接匹配。

字符串 $S,T$ 都有 `*` 时，将前缀后缀直接匹配，如遇到 `*` 暂停。前后缀能成功匹配即可成功匹配。

设 $S$ 有 `*`。先将前后缀匹配完成，则 $S$ 会变成形如 $*s_1*s_2*s3*\dots*s_k*$ 的形式。

可以将每一个 $s_i$ 按顺序找在 $T$ 中最前面能匹配的位置，时间复杂度 $O(nk\log n)$。

可以发现，FFT 或 NTT 直接将 $s_i$ 在 $T$ 中所有能匹配的位置都求出来了，但我们只需要最前面的那一个。

可以将 $T$ 中长度为 $2\left | s_i\right |$ 的前缀拿出进行匹配。如果能匹配成功，将匹配的部分即前面的部分从 $T$ 中删去；若果不能匹配，那 $T$ 种长度为 $\left | s_i\right |$ 的前缀就没用了，也删去。

发现一次匹配最少能删去 $T$ 中长度为 $\left | s_i\right |$ 的前缀，时间复杂度为 $O(\left | s_i\right |\log \left | s_i\right |)$。

总时间复杂度为 $O(n\log n)$。

抽象出题人开 $n=2\times 10^6$，所以字符串要先化代价形式，多项式速度也要快。

注意 NTT 模数为 $998244353$ 时会被卡，要换一个。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4194305,P=469762049,G=3,I=156587350;
string s,t;
int ss[N],tt[N],top=0,tot=0;
struct node{
	int n,m,lim=1,rev[N],p[N],a[N],b[N],f[N],g[N];
	int qpow(int a,int b){
		int res=1;
		while(b){
			if(b&1)res=1ll*res*a%P;
			a=1ll*a*a%P,b>>=1;
		}
		return res;
	}
	int inv(int a){
		return qpow(a,P-2);
	}
	void ntt(int *a,int flag){
		for(int i=0;i<lim;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int mid=1;mid<lim;mid<<=1){
			int wn=qpow(flag?G:I,(P-1)/(mid<<1));
			for(int i=mid*2,j=0;j<lim;j+=i){
				int w=1;
				for(int k=0;k<mid;k++,w=1ll*w*wn%P){
					int x=a[j+k],y=1ll*w*a[j+mid+k]%P;
					a[j+k]=(0ll+x+y+P)%P,a[j+mid+k]=(0ll+x-y+P)%P;
				}
			}
		}
	}
	void solve(int opt){
		ntt(a,1),ntt(b,1);
		for(int i=0;i<lim;i++)a[i]=1ll*a[i]*b[i]%P;
		ntt(a,0);
		for(int i=0,s=inv(lim);i<n+m;i++)p[i]+=(1ll*a[i]*s%P)*opt%P,p[i]=(p[i]+P)%P;
		for(int i=0;i<lim;i++)a[i]=b[i]=0;
	}
	int init(int l1,int r1,int l2,int r2){
		m=r1-l1+1,n=r2-l2+1;
		for(int i=0;i<m;i++)f[i]=ss[l1+i];
		for(int i=0;i<n;i++)g[i]=tt[l2+i];
		for(int i=0;i<m/2;i++)swap(f[i],f[m-i-1]);
		int k=0;lim=1;
		while(lim<=n+m)lim<<=1,k++;
		for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
		for(int i=0;i<m;i++)a[i]=f[i]*f[i]*f[i];
		for(int i=0;i<n;i++)b[i]=g[i];
		solve(1);
		for(int i=0;i<m;i++)a[i]=f[i]*f[i];
		for(int i=0;i<n;i++)b[i]=g[i]*g[i];
		solve(-2);
		for(int i=0;i<m;i++)a[i]=f[i];
		for(int i=0;i<n;i++)b[i]=g[i]*g[i]*g[i];
		solve(1);
		for(int i=0;i<lim;i++)f[i]=g[i]=rev[i]=0;
		int res=-1;
		for(int x=m-1;x<=n-1;x++)if(p[x]==0){
			res=x-m+1;
			break;
		}
		for(int i=0;i<lim;i++)p[i]=0;
		return res;
	}
}NTT;
int work(int l,int r){
	int len=r-l+1,res;
	if(tot-top+1<len)return 0;
	if(tot-top+1<=len*2)res=NTT.init(l,r,top,tot);
	else res=NTT.init(l,r,top,top+len*2-1);
	if(res==-1){
		top+=len;
		return -1;
	}
	top+=res+len;
	return 1;
}
int n,m;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >>n>>m>>s>>t;
	int p=0,q=0;
	for(int i=0;i<n;i++)p+=(s[i]=='*');
	for(int i=0;i<m;i++)q+=(t[i]=='*');
	if(p&&q){
		while(s[n-1]!='*'&&t[m-1]!='*'){
			if(s[n-1]!='-'&&t[m-1]!='-'&&s[n-1]!=t[m-1]){
				cout <<"No";
				return 0;
			}
			n--,m--;
		}
		for(int i=0;s[i]!='*'&&t[i]!='*';i++){
			if(s[i]!='-'&&t[i]!='-'&&s[i]!=t[i]){
				cout <<"No";
				return 0;
			}
		}
		cout <<"Yes";
		return 0;
	}
	if((!p)&&(!q)){
		if(n!=m){
			cout <<"No";
			return 0;
		}
		for(int i=0;i<n;i++){
			if(s[i]!='-'&&t[i]!='-'&&s[i]!=t[i]){
				cout <<"No";
				return 0;
			}
		}
		cout <<"Yes";
		return 0;
	}
	if(!p)swap(n,m),swap(s,t);
	while(s[n-1]!='*'&&t[m-1]!='*'&&n&&m){
		if(s[n-1]!='-'&&t[m-1]!='-'&&s[n-1]!=t[m-1]){
			cout <<"No";
			return 0;
		}
		n--,m--;
	}
	while(s[0]!='*'&&t[0]!='*'&&n&&m){
		if(s[0]!='-'&&t[0]!='-'&&s[0]!=t[0]){
			cout <<"No";
			return 0;
		}
		s.erase(0,1),t.erase(0,1);
		n--,m--;
	}
	if(m==0){
		for(int i=0;i<n;i++)if(s[i]!='*'){
			cout <<"No";
			return 0;
		}
		cout <<"Yes";
		return 0;
	}
	s.erase(n),t.erase(m);
	while(s[0]=='*')s.erase(0,1),n--;
	for(int i=0;i<n;i++)ss[i]=(s[i]=='-'?0:s[i]-'a'+1);
	for(int i=0;i<m;i++)tt[i]=(t[i]=='-'?0:t[i]-'a'+1);
	tot=m-1;
	for(int i=0,st=0;i<n;i++){
		if(s[i]=='*'){
			if(s[i+1]!='*')st=i+1;
			continue;
		}
		if(s[i+1]!='*')continue;
		while(true){
			int res=work(st,i);
			if(res==0){
				cout <<"No";
				return 0;
			}else if(res==1)break;
		}
	}
	cout <<"Yes";
	return 0;
}
```

---

