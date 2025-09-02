# [ARC138D] Differ by K bits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc138/tasks/arc138_d

整数 $ N,K $ が与えられます． $ (0,1,\cdots,2^N-1) $ の順列 $ P=(P_0,P_1,\cdots,P_{2^N-1}) $ であって，以下の条件を満たすものが存在するか判定し， また存在するなら一つ構成してください．$ P $ の添字が $ 0 $ から始まることに注意してください．

- すべての $ i $ ($ 0\ \leq\ i\ \leq\ 2^N-1 $) について，$ P_i $ と $ P_{i+1\ \mod\ 2^N} $ は $ 2 $ 進表記でちょうど $ K $ 桁だけ異なる． なお，比較の際はどちらも leading $ 0 $'s を補って $ N $ 桁に揃えた上で比較する．

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 18 $
- 入力される値はすべて整数

### Sample Explanation 1

$ P $ を $ 2 $ 進表記で書くと，$ P=(000,001,011,010,110,111,101,100) $ です． 例えば $ P_1=001,P_2=011 $ なので，これらはちょうど $ 1 $ 桁だけ異なっており，$ i=1 $ について条件が成立していることが確認できます． 同様に，すべての $ i $ についても条件を満たしています．

## 样例 #1

### 输入

```
3 1```

### 输出

```
Yes
0 1 3 2 6 7 5 4```

## 样例 #2

### 输入

```
2 2```

### 输出

```
No```

# 题解

## 作者：Phartial (赞：5)

小清新构造题。

首先 $K=1$ 的情况是 trival 的，直接格雷码即可。

对于 $K>1$，我们发现题目的约束相当于 $\operatorname{popcount}(P_i\oplus P_{(i+1)\bmod 2^N})=K$，考虑 $P_i$ 的差分序列 $D_i$，那么 $D_i$ 一定是一个恰好有 $K$ 位 $1$ 的二进制数，记 $S=\{i\mid 0\le i\le 2^N-1\land \operatorname{popcount}(i)=K\}$，则 $D_i\in S$。

题目要求 $P_i$ 不能重复，所以我们得到的 $\bigoplus\limits_{j=0}^i D_j$ 必须不重，因此考虑先用线性基处理掉 $S$ 中能被别的数表示出来的数，那么剩下的数可以保证：只要选数的方案不同，结果就不同。

于是我们只需要让每次选数方案的变化量为 $1$ 即可，直接格雷码即可。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int kN = 18;

int n, k, p[kN];
vector<int> l;

void A(int v) {
  int _v = v;
  for (int i = n - 1; i >= 0; --i) {
    if (v >> i & 1) {
      if (p[i]) {
        v ^= p[i];
      } else {
        p[i] = v, l.push_back(_v);
        break;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k;
  for (int i = 0; i < (1 << n); ++i) {
    int c = 0;
    for (int j = 0; j < n; ++j) {
      c += i >> j & 1;
    }
    if (c == k) {
      A(i);
    }
  }
  if (l.size() < n) {
    cout << "No";
    return 0;
  }
  cout << "Yes\n";
  for (int i = 0; i < (1 << n); ++i) {
    int p = i ^ (i >> 1), v = 0;
    for (int j = 0; j < n; ++j) {
      if (p >> j & 1) {
        v ^= l[j];
      }
    }
    cout << v << ' ';
  }
  return 0;
}
```


---

## 作者：Rubidium_Chloride (赞：4)

把 [这个题](https://www.luogu.com.cn/problem/P7949) 题解搬过来。

简化版题意：

给定 $n,k$，求将 $0,1,2\dots 2^n-1$ 排成一排，使得对任意两个相邻的数 $a,b$，满足 $\operatorname{popcount}(a\operatorname{xor}b)=k$。

其中 $\operatorname{popcount}(x)$ 的定义为 $x$ 的二进制表示中值为 $1$ 的位数。

首先暴力 dfs 是能过的，原理不明。

然后我们考虑一个类似格雷码的过程。

首先考虑一些特殊的情况。

$n=0$，无论 $k$ 怎样都可以成立。 

$n=1$，当且仅当 $k=1$ 时可以成立，其他都不可以成立。

接下来不妨设 $n\ge 2$。

尝试考虑证明有解等价于 $n\ge k+1$ 且 $k\bmod 2=1$。

首先，显然的，$n\le k$ 时无解。（最多仅能达到 $2$ 个数）

接下来考虑 $k\bmod 2=0$ 时的情况。

引理 $1$：长为 $n$ 的二进制串中 $1$ 个数为奇数/偶数的串的个数相等。

相关证明方法可以自己查询，由于结论比较简单此处不再赘述。

对于任意的 $a$，其下一位数都只会更改偶数个二进制位的值，因此可以得到所有项的二进制位 $1$ 的个数均与首项相同，由引理 $1$ 知矛盾。

接下来证 $n\ge k+1$ 且 $k\bmod 2=1$ 时一定有解。

先考虑 $n=k+1$ 时的情况。

先构造出一组 格雷码 $b_1,b_2\dots b_{2^n}$，可得 $\operatorname{popcount}(b_i\operatorname{xor}b_{i+1})=1(i=1,2\dots 2^n-1)$。

然后我们将 $b_j(j\bmod 2=0)$ 这些项全部反转（即，异或上 $2^n-1$）。

由于 $b_2,b_4\dots b_{2^{n}}$ 的 $\operatorname{popcount}$ 的奇偶性全部相同，且反转之前两两不同，可以得知反转后两两不同，且此时的 $b_i$ 满足：$\operatorname{popcount}(b_i\operatorname{xor}b_{i+1})=k(i=1,2\dots 2^n-1)$。

设这样得到的序列为 $a_1,a_2\dots a_{2^n}$。

接下来考虑如下的序列：$c_1,c_2,c_3\dots c_{2^n}$，满足 $c_i=a_i\operatorname{xor}(2^n+2^{k-1}-1)$。

可以显然地知道 $\operatorname{popcount}(c_i\operatorname{xor}c_{i+1})=k(i=1,2\dots 2^n-1)$。

同时，$c_i$ 和 $a_i$ 不重复，且两个数列一起构成了 $0,1\dots 2^{n+1}-1$ 的排列。

同时，$\operatorname{popcount}(c_{2^n}\operatorname{xor}a_{2^n}=k)$。

因此可以将 $a,c$ 两个序列按照 $a$ 正序，$c$ 倒序的顺序拼接起来，就得到了 $n+1$ 时的解。

综上，原命题得证。

---

## 作者：Schi2oid (赞：3)


题意：构造一个 $0\sim2^N-1$ 的排列，满足相邻两个数的异或值的 $\text{popcount}$ 恰好为 $K$（第一个和最后一个也视为相邻）。

题解：考虑直接构造。下文排列下标从 $0$ 开始。首先容易发现 $N=K(N>1)$ 或 $K$ 为偶数的情况一定无解。$K=1$ 容易给出构造（格雷码）：$p_i=p_{i-1}\oplus\text{lowbit}(i)$。现在尝试通过 $(N-2,K-2)$ 获得 $(N,K)$ 的构造。

设 $p$ 是一个之前的构造，长度为 $n$，~~不难发现~~ $p'=p'_0+p'_1+p'_2+p'_3$ 是一个合法的构造。其中：
$$
p'_{0,i}=
\begin{cases}
\overline{00p_i} & i\equiv 0 \bmod 2\\
\overline{11p_i} & i\equiv 1 \bmod 2
\end{cases}
\\
p'_{1,i}=
\begin{cases}
\overline{10(p_{n-1-i}\oplus(2^{K-1}-1))} & i\equiv 0 \bmod 2\\
\overline{01(p_{n-1-i}\oplus(2^{K-1}-1))} & i\equiv 1 \bmod 2
\end{cases}
\\
p'_{2,i}=
\begin{cases}
\overline{11p_i} & i\equiv 0 \bmod 2\\
\overline{00p_i} & i\equiv 1 \bmod 2
\end{cases}
\\
p'_{3,i}=
\begin{cases}
\overline{01(p_{n-1-i}\oplus(2^{K-1}-1))} & i\equiv 0 \bmod 2\\
\overline{10(p_{n-1-i}\oplus(2^{K-1}-1))} & i\equiv 1 \bmod 2
\end{cases}
$$
上文中横线下表示一个二进制数。直接按照上式输出即可，时间复杂度 $O(2^N)$。是 Atcoder 上的本题最优解。

---

## 作者：tzc_wk (赞：2)

题是挺简单，但是这个构造看上去挺典。

首先无解的条件是 $k$ 是偶数或者 $k=n$，判掉即可。

考虑 $k=1$，就是一个经典的格雷码问题，分治构造一下即可，具体来说考虑求解 $n$ 的答案，我们求出 $n-1$ 的答案，首尾翻转一下并将每一项加上 $2^{n-1}$ 后拼接在原序列后面即可。

$k=n-1$ 的情况也是类似的，构造 $k=1$ 的格雷码序列，将序列中第偶数项全部 flip 一下即可，由于 $n$ 是偶数（否则 $k$ 就是偶数无解了），所以 flip 后序列中所有数仍然两两互不相同。

接下来考虑 $n-1>k$ 的情况，我们还是归纳构造，每次将 $n$ 减一，直到 $k=n-1$，而这个归纳方法也是容易的——求出 $n-1,k$ 时的序列 $a'$，再找到一位 $b$ 满足 $a'$ 开头和结尾元素第 $b$ 位互不相同，然后构造序列 $a''_i=a'_i\oplus 2^b\oplus 2^{n-1}$，取 $a=a'+a''$ 即可。

---

## 作者：WhisperingWillow (赞：1)

这个题直接暴力即可。

考虑存下所有的 $popcount(x)=k$ 的值。

搜索即可。

```
#include <bits/stdc++.h>
#define f(c, a, b) for (c = a; c <= b; c++)
#define fd(c, a, b) for (c = b; c >= a; c--)
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define int long long
#define vpii vector<pi>
#define il inline
#define ri register
#define aint(a) a.begin(), a.end()
#define fr(a) freopen(a, "r", stdin)
#define fo(a) freopen(a, "w", stdout);
#define mod 998244353
#define debug puts("------------------------")
#define lowbit(x) (x & -x)
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define co const
using namespace std;
const int N = 2e5 + 3;
int n, m;//**//
il int read() {
    ri int ans = 0;
    ri char c = getchar();
    ri bool neg = 0;
    while ((c < '0') | (c > '9')) neg ^= !(c ^ '-'), c = getchar();
    while ((c >= '0') & (c <= '9')) ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return neg ? -ans : ans;
}
il void write(ri int x) {
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
il void writes(ri int x) {
    write(x);
    putchar(' ');
}
il void writed(ri int x) {
    write(x);
    putchar('\n');
}
int k;
vector<int>ans,c;
bitset<(1<<20)+2>v;
inline void dfs(const int x){
	ans.push_back(x);
	v[x]=1;
	if(ans.size()==(1<<n)){
		puts("1");
		for(auto x:ans) cout<<x<<" ";
		exit(0); 
	}
	for(register int b:c) if(!v[b^x]) dfs(b^x);
}
signed main() {
	n=read(),k=read();
    int i,j;
    for(register int i=0;i<(1<<n);++i) if(__builtin_popcount(i)==k) c.push_back(i);
    	dfs(0);
    puts("No"); 
    return 0;
}

```

---

## 作者：ZillionX (赞：1)

# Description

给定 $n,k$，构造一个长度为 $2^n$ 的序列 $a$，满足其是一个 $ 0 \sim 2^n-1$ 的排列，且 $\forall i\in[2,2^n]$，$\operatorname{popcount}(a_i \oplus a_{i-1})=k$。

若有解则输出这个序列，否则输出 ```0```。

$n,k \le 20$，时限 0.5s。

# Solution

非常好的构造题。

注意到 $k=1$ 时格雷码即为一组合法的方案。我们考虑 $k>1$ 时怎么做，注意到如果可以把那相差的那一位换成一个 $\operatorname{popcount}=1$ 的二进制数，则可以类似地构造出一组方案。

于是进一步注意到我们可以将 $\operatorname{popcount}=k$ 的数全部插入到线性基中，若成功插入的数个数 $<n$ 则无解。否则我们直接将成功插入的数作为基底（这里不是将插入时一路异或的那个最高位为 $i$ 的数当作基底，而是用原数来作，这样可以既保证异或出所有数，同时保证后文中的相邻数的异或结果 $\operatorname{popcount}=k$）。

这样我们还是基于格雷码来构造，若第 $i$ 个格雷码的第 $j$ 位为 $1$，则给第 $i$ 个数异或上线性基数组中的第 $j$ 个数。这样就可以保证 $\operatorname{popcount}(a_i \oplus a_{i-1})=k$。

时间复杂度 $\mathcal O(n2^n)$。

# Code

```cpp
int n,k,fl;
struct lnb {
	int a[22],t[22];
	void add(int x) {
		int z=x;
		for (int i=n-1;i>=0 && x;i--) {
			if (!(x>>i&1)) continue;
			if (a[i]) x^=a[i];
			else {a[i]=x,t[i]=z,fl++;break;}
		}
	}
}o;
int main() {
	scanf("%d%d",&n,&k);
	for (int i=0;i<(1<<n);i++)
		if (btc(i)==k) o.add(i);
	if (fl<n) {
		printf("No");
		return 0;
	}
	puts("Yes");
	for (int i=0;i<(1<<n);i++) {
		int x=(i^(i>>1)),c=0;
		for (int j=0;j<n;j++)
			if (x>>j&1) c^=o.t[j];
		printf("%d ",c);
	}
	return 0;
}

```


---

