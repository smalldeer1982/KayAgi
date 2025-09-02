# [AGC045A] Xor Battle

## 题目描述

有 $2$ 个人，编号分别为 $0$ 和 $1$。还有一个初始值为 $0$ 的变量 $x$。接下来这两个人要进行一个游戏。游戏共进行 $N$ 轮，在第 $i$ 轮（$1 \leq i \leq N$）中，将进行如下操作：

- 编号为 $S_i$ 的人可以选择以下两种操作之一：
  - 用 $x \oplus A_i$ 替换 $x$。这里 $\oplus$ 表示按位异或运算。
  - 什么都不做。

编号为 $0$ 的人的目标是让最终 $x=0$，而编号为 $1$ 的人的目标是让最终 $x \neq 0$。

请判断当两个人都采取最优策略时，最终 $x$ 是否等于 $0$。

对于每组输入，请回答 $T$ 个测试用例。

## 说明/提示

### 限制

- $1 \leq T \leq 100$
- $1 \leq N \leq 200$
- $1 \leq A_i \leq 10^{18}$
- $S$ 是仅由 `0` 和 `1` 组成的长度为 $N$ 的字符串
- 输入的所有数均为整数

### 样例解释 1

对于第 $1$ 个测试用例，如果编号为 $1$ 的人将 $x$ 替换为 $0 \oplus 1=1$，无论编号为 $0$ 的人怎么操作，最终 $x \neq 0$。对于第 $2$ 个测试用例，无论编号为 $1$ 的人做哪种操作，只要编号为 $0$ 的人采取合适的操作，都可以让 $x=0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2
1 2
10
2
1 1
10
6
2 3 4 5 6 7
111000```

### 输出

```
1
0
0```

# 题解

## 作者：E_M_T (赞：7)

考虑最后一个决策点的必胜状态。

设经过 $n-1$ 次操作后的数为 $x$，则有：

* 若 $s_n$ 为 $1$，则编号 $1$ 必胜。

即此时若 $x=0$，则 $x\gets x\oplus a_i$，因为有 $a_i\not = 0$。

否则不操作即可。

* 若 $s_n$ 为 $0$，则满足 $x=0$ 或 $x=a_n$ 时编号 $0$ 必胜。

考虑往前推 $n-1$ 处的必胜状态，设经过 $n-2$ 次操作后数为 $x'$。

以下情况默认 $s_n=0$，否则无讨论意义。

* 若 $s_{n-1}$ 为 $0$，则满足 $x'=0$ 或 $x'=a_n$ 或 $x'=a_{n-1}\oplus a_n$ 或 $x'=a_{n-1}$ 时编号 $0$ 必胜。
* 若 $s_{n-1}$ 为 $1$，则满足 $x'\not =0$ 或 $x'\not =a_n$ 或 $x'\not =a_n\oplus a_{n-1}$ 或 $x'\not =a_{n-1}$ 时编号 $1$ 必胜。

维护编号 $0$ 的必胜状态显然比维护编号 $1$ 的要容易。

于是令 $S_i$ 表示进行 $i-1$ 次操作后编号 $0$ 必胜的 $x$ 取值的集合。

则有：

$$S_i=\left\{\begin{matrix}
\{x\mid x\in S_{i+1} \vee x\oplus a_i \in S_{i+1} \}  & s_i=0, \\
\{x\mid x\in S_{i+1} \wedge x\oplus a_i   \in S_{i+1} \} & s_i=1.
\end{matrix}\right.$$

初始值 $S_n=\left\{\begin{matrix}
\{0,a_n\}  & s_n=0, \\
\varnothing & s_n=1.
\end{matrix}\right.$

于是暴力做法是使用 $n$ 个 `set` 来维护 $S$，[代码](https://www.luogu.com.cn/paste/q34fyc2n)。



T 了，考虑优化。

发现如果仅考虑 $s_i=0$， $S_i$ 其实就是 $a_i\sim a_n$ 这一段元素选择若干个之后异或和的取值集合。

第一反应应该是建线性基。

然后考虑 $s_i=1$ 对这个线性基的影响：

* 若 $a_i\in S_{i+1}$，则一定有 $\forall x\in S_{i+1},x\oplus a_i\in S_{i+1}$。线性基没有受到影响。

* 若 $a_i\not \in S_{i+1}$，则一定有 $\not \exists x\in S_{i+1},x\oplus a_i \in S_{i+1}$。此时有 $S_i=\varnothing$。

仅用线性基的定义证明是容易的。

因为第二个情况下可以直接输出答案了，所以 $s_i=1$ 的情况不会影响线性基。

于是维护一个线性基，支持插入和查询一个元素是否能被线性基组成出来。

```cpp
#include<bits/stdc++.h>
#define sd std::
#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=1e5+10;
int n;
int d[66];
void insert(int x)
{
	f(i,62,0)
	{
		if(!(x&(1ll<<i))) continue;
		if(d[i]) x^=d[i];
		else
		{
			d[i]=x;
			break;
		}
	}
}
int find(int x)
{
	f(i,62,0)
	{
		if(!(x&(1ll<<i))) continue;
		if(d[i]) x^=d[i];
		else return 0;
	}
	return 1;
}
int a[N];
char s[N];
il void solve()
{
	n=read();
	F(i,1,n) a[i]=read();
	F(i,0,65) d[i]=0;
	scanf("%s",s+1);
	f(i,n,1)
	{
		if(s[i]=='0') insert(a[i]);
		else if(!find(a[i])) return puts("1"),void();
	}
	puts("0");
}
signed main()
{
	int T=1;
	T=read();
	while(T--) solve();
    return 0;
}


```

---

## 作者：Jsxts_ (赞：1)

线性基好题。

考虑从后往前枚举，设 $S_i$ 表示前 $i$ 步做完后 $0$ 必胜的 $x$ 集合。

那么当 $p_i=0$ 时， $S_i$ 相当于 $S_{i+1}$ 并上 $S_{i+1}$ 中所有数与 $a_i$ 的异或值，即 $S_i=S_{i+1}\cup \{x\oplus a_i|x\in S_{i+1}\}$。而当 $p_i=1$ 时，$S_i=\{x|x\in S_{i+1}$ 且 $x \oplus a_i\in S_{i+1}\}$。

根据 $S$ 的性质，发现 $S$ 是所有 $p_i=0$ 的 $a_i$ 取若干个异或得到的数的集合，并且若 $x\in S_i,y\in S_i$，则 $x\oplus y\in S_i$，所以当 $p_i=1$ 时，如果 $a_i\in S_{i+1}$，则所有 $x\oplus a_i\in S_{i+1}$，即 $S_i=S_{i+1}$。而当 $a_i\notin S_{i+1}$ 时，对于任意的 $x$，$x$ 和 $x\oplus a_i$ 不可能同时在集合里（由上面性质），所以 $S_i=\emptyset$，即 $1$ 获胜。

我们可以维护集合 $S$ 的线性基，这样插入和查询是否 $a_i\notin S_{i+1}$ 都很方便。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 2e9;
inline ll read() {
	ll s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
ll a[210];
struct Linear_Basis {
	ll p[65];
	bool ins(ll x) {
		for (int i = 62;~i;i -- ) {
			if (!(x >> i & 1)) continue;
			if (!p[i]) {
				p[i] = x;
				return 1;
			}
			x ^= p[i];
		}
		return 0;
	}
}L;
char s[210];
int main() {
	int T = read();
	while (T -- ) {
		int n = read();
		for (int i = 1;i <= n;i ++ ) a[i] = read();
		scanf("%s",s+1);
		for (int i = 0;i <= 62;i ++ ) L.p[i] = 0; 
		for (int i = n;i;i -- ) {
			if (L.ins(a[i]) && s[i] == '1') {
				puts("1");
				goto bre;
			}
		}
		puts("0");
		bre:;
	}
	return 0;
}
```


---

