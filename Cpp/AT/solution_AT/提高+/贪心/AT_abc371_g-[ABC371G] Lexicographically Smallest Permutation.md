# [ABC371G] Lexicographically Smallest Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc371/tasks/abc371_g

$ (1,2,\ldots,N) $ の並べ替え $ P=(P\ _\ 1,P\ _\ 2,\ldots,P\ _\ N),A=(A\ _\ 1,A\ _\ 2,\ldots,A\ _\ N) $ が与えられます。

あなたは、次の操作を $ 0 $ 回以上好きな回数行うことができます。

- $ i=1,2,\ldots,N $ に対して**一斉に** $ A\ _\ i $ を $ A\ _\ {P\ _\ i} $ で置き換える。
 
得られる $ A $ としてありえるもののうち、辞書順で最小のものを出力してください。

 辞書順の大小とは？ 長さ $ N $ の列 $ A=(A\ _\ 1,A\ _\ 2,\ldots,A\ _\ N),B=(B\ _\ 1,B\ _\ 2,\ldots,B\ _\ N) $ について、辞書順で $ A $ が $ B $ より小さいとは、次のことが成り立つことをいいます。

- ある整数 $ i\ (1\leq\ i\leq\ N) $ が存在し、$ A\ _\ i\lt\ B\ _\ i $ が成り立ち、$ 1\leq\ j\lt\ i $ を満たすすべての整数 $ j $ に対して $ A\ _\ j=B\ _\ j $ が成り立つ。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ P\ _\ i\leq\ N\ (1\leq\ i\leq\ N) $
- $ P\ _\ i\neq\ P\ _\ j\ (1\leq\ i\lt\ j\leq\ N) $
- $ 1\leq\ A\ _\ i\leq\ N\ (1\leq\ i\leq\ N) $
- $ A\ _\ i\neq\ A\ _\ j\ (1\leq\ i\lt\ j\leq\ N) $
- 入力はすべて整数
 
### Sample Explanation 1

はじめ、$ A=(4,3,1,6,2,5) $ です。 ここから操作を繰り返すと、以下のようになります。 - $ A=(1,4,2,5,3,6) $ となる。 - $ A=(2,1,3,6,4,5) $ となる。 - $ A=(3,2,4,5,1,6) $ となる。 - $ A=(4,3,1,6,2,5) $ となる。 以降、$ 4 $ 回操作を行うたびにもとの $ A $ に戻ります。 よって、このうち辞書順で最小である `1 4 2 5 3 6` を出力してください。

### Sample Explanation 2

$ 1 $ 度も操作をしなくても構いません。

## 样例 #1

### 输入

```
6
3 1 5 6 2 4
4 3 1 6 2 5```

### 输出

```
1 4 2 5 3 6```

## 样例 #2

### 输入

```
8
3 5 8 7 2 6 1 4
1 2 3 4 5 6 7 8```

### 输出

```
1 2 3 4 5 6 7 8```

## 样例 #3

### 输入

```
26
24 14 4 20 15 19 16 11 23 22 12 18 21 3 6 8 26 2 25 7 13 1 5 9 17 10
15 3 10 1 13 19 22 24 20 4 14 23 7 26 25 18 11 6 9 12 2 21 5 16 8 17```

### 输出

```
4 1 22 18 20 13 14 6 15 11 3 26 2 12 5 23 9 10 25 24 7 17 16 21 19 8```

# 题解

## 作者：rui_er (赞：32)

本题解提供英文版，位于示例代码之后。

English version of this editorial is provided after the sample code.

官方题解竟然用 Python 来算高精度 lcm，我来提供一个可以避免一切大整数运算的方法。

考察 $u\gets P_u$ 这张图的每个置换环。为了使答案字典序最小，显然需要从前往后贪心地取每个位置。

假设贪心地填完了前 $k-1$ 个元素，第 $k$ 个元素尚未确定取值（这意味着它是所在置换环中编号最小的元素）。找出其所在的置换环，设长度为 $len$。设最终操作次数为 $W$，则已经填完的置换环会对 $W$ 的取值做出一些形如 $W\equiv R\pmod{Q}$ 的规定，使用一个数组 $req$ 对所有 $Q$ 记录下对应的 $R$。枚举当前置换环对 $W$ 取值的限制 $W\equiv\Delta\pmod{len}$，判断这一限制与已有限制是否有矛盾，在所有没有矛盾的 $\Delta$ 中取使得 $A_k$ 最小化的一个即可。

直接做的复杂度为 $O(nd(n))$。事实上，我们只需要维护 $Q=p^k$ 的所有限制（其中 $p$ 为质数），可以做到 $O(n\log n)$。

示例代码 / Sample code:

```cpp
// Problem: G - Lexicographically Smallest Permutation
// Contest: AtCoder - AtCoder Beginner Contest 371
// URL: https://atcoder.jp/contests/abc371/tasks/abc371_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(y < x) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 2e5 + 5;

int n, p[N], a[N], vis[N], req[N], ans[N];
vector<int> divs[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> p[i];
    rep(i, 1, n) cin >> a[i];
    rep(i, 2, n) {
        if(divs[i].empty()) {
            for(ll d = i; d <= n; d *= i) {
                for(int j = d; j <= n; j += d) {
                    divs[j].push_back(d);
                }
            }
        }
    }
    rep(i, 1, n) req[i] = -1;
    rep(i, 1, n) {
        if(!vis[i]) {
            vector<int> cyc;
            for(int u = i; !vis[u]; u = p[u]) {
                cyc.push_back(u);
                vis[u] = 1;
            }
            // for(int u : cyc) cout << u << " "; cout << endl;
            int len = cyc.size(), steps = -1;
            rep(s, 0, len - 1) {
                bool ok = true;
                for(int d : divs[len]) {
                    if(req[d] != -1 && s % d != req[d]) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    if(steps == -1 || a[cyc[s]] < a[cyc[steps]]) {
                        steps = s;
                    }
                }
            }
            rep(i, 0, len - 1) ans[cyc[i]] = a[cyc[(i + steps) % len]];
            for(int d : divs[len]) req[d] = steps % d;
        }
    }
    rep(i, 1, n) cout << ans[i] << " \n"[i == n];
    return 0;
}
```

The official solution surprisingly uses Python to compute LCM of big integers. Let me present an algorithm that avoids all big integer computations.

Consider each cycle in the permutation graph $u\gets P_u$. To make the answer lexicographically smallest, it is obvious that we need to greedily pick each position from left to right.

Suppose the first $k-1$ elements have been greedily filled, and the value of the $k$-th element has yet to be determined (which means it is the smallest-indexed element in its cycle). Find the cycle it belongs to and let its length be $len$. Let the final number of operations be $W$, and the cycles that have already been filled impose some conditions on $W$ in the form of $W\equiv R\pmod{Q}$. Use an array $req$ to record the corresponding $R$ for each $Q$. Enumerate the current cycle's constraint on $W$, i.e., $W\equiv\Delta\pmod{len}$, and check if this constraint conflicts with the existing ones. Among all the $\Delta$ that do not conflict, pick the one that minimizes $A_k$.

The direct approach has a time complexity of $O(nd(n))$. In fact, we only need to maintain all constraints of $Q=p^k$ (where $p$ is a prime number), which can be done in $O(n\log n)$.

---

## 作者：lnw143 (赞：9)

本题解提供英文版，位于中文题解之后。

English version of this editorial is provided after the Chinese version.

考虑 $u \to P_u$ 所形成的若干个置换环，显然从前往后贪心选能选到的 $A_i$ 最小的点。

假设目前已经贪心地选了 $i-1$ 位，且 $i$ 的取值尚未确定，则设 $i$ 所在置换环长为 $M$，并从 $i$ 开始，按 $u \to P_u$ 的顺序为环上每个点从 $0$ 开始标号。这是因为假设 $j$ 是 $i$ 所在置换环上的任意一点，编号为 $\mathrm{num}_j$，那么将 $j$ 置换到 $i$ 的位置上便需要 $\mathrm{num}_j + kM,k \in \mathbb N$ 次置换。

设最优置换次数为 $C$，则如果在第 $i$ 位填 $A_j$，则要求 $C \equiv \mathrm{num}_j \pmod M$。注意到这个方程不一定能成立，因为前面的贪心对 $C$ 已经有了若干个限制。假设前面的限制可以合并为一个同余方程，那我们显然可以通过求 gcd $\mathrm{O}(\log N)$ 判断是否与当前方程冲突。但是这样的话需要求环长的 lcm，会爆 `___int128`。

题解的解决办法是用 python 的自带高精度，但是作为 C++ 选手，我们还有另外的做法。

假设环的个数为 $K$，环长序列为 $Q$，那么不可重集 $\{Q_1,Q_2,\cdots,Q_K\}$ 的大小是 $\mathrm{O}(\sqrt{N})$ 的（这是因为 $\sum_{i=1}^K Q_i = N$）。假设第 $i$ 个环对 $C$ 的限制形如 $C \equiv c_i \pmod{Q_i}$，那么有 $Q_i=Q_j \Rarr c_i = c_j$。于是我们的本质不同方程个数便只有 $\mathrm{O}(\sqrt{N})$ 个，且若新加一个方程，整个方程组解集不为空的充要条件是该方程与方程组中任意方程都有公共解，暴力判断即可。

时间复杂度 $\mathrm{O}(N \sqrt{N} \log N)$，实际跑的非常快。

Consider the permutation cycles formed by $u \to P_u$. It is evident that we should greedily select the smallest possible $A_i$ from front to back.

Assume that we have already greedily selected $i-1$ positions, and the value of $i$ is yet to be determined. Let the length of the permutation cycle containing $i$ be $M$, and label each point in the cycle starting from $i$ in the order of $u \to P_u$, beginning from 0. This is because if $j$ is any point in the permutation cycle containing $i$, with a label $\mathrm{num}_j$, then moving $j$ to the position of $i$ requires $\mathrm{num}_j + kM, k \in \mathbb{N}$ permutations.

Let the optimal number of permutations be $C$. If we fill $A_j$ at position $i$, then $C \equiv \mathrm{num}_j \pmod{M}$. Note that this equation may not always hold, as the previous greedy selections have already imposed several constraints on $C$. If the previous constraints can be combined into a single congruence equation, we can determine if it conflicts with the current equation by calculating the gcd $\mathrm{O}(\log N)$. However, this requires calculating the lcm of the cycle lengths, which can overflow ___int128.

The solution provided in the problem uses Python's built-in high precision, but as C++ programmers, we have another approach.

Assume there are $K$ cycles, with cycle lengths given by $Q$. The size of the unique set ${Q_1, Q_2, \cdots, Q_K}$ is $\mathrm{O}(\sqrt{N})$ (since $\sum_{i=1}^K Q_i = N$). Suppose the constraint on $C$ from the $i$-th cycle is $C \equiv c_i \pmod{Q_i}$, then $Q_i = Q_j \Rightarrow c_i = c_j$. Thus, the number of essentially different equations is only $\mathrm{O}(\sqrt{N})$, and if a new equation is added, the necessary and sufficient condition for the solution set of the entire system to be non-empty is that the new equation has a common solution with every equation in the system, which can be checked by brute force.

The time complexity is $\mathrm{O}(N \sqrt{N} \log N)$, and it runs very fast in practice.

[code](https://atcoder.jp/contests/abc371/submissions/57791657)

---

## 作者：__ryp__ (赞：9)

## 题意

给定两个排列 $A$ 与 $P$，定义一次操作表示对于所有的 $1\le i \le n$，将 $A_i$ 替换为 $A_{P_i}$。要求进行任意非负整数次操作，求能得到的字典序最小的排列。

## 题解

我们由 $i$ 向 $P_i$ 连一条有向边，那么可以得到一张图。考虑到现在一次操作实际上就是每个下标步进一次。

这时我们发现，确定操作次数，最终的排列就确定；换句话说，确定某一个点移动多少步，整个排列就确定。由此，结合要让字典序最小，很自然地考虑到要让每个环上的第一个位置最小。

但是这样可能冲突。考虑有两个大小为 $3$ 和 $6$ 的环，假设第一个环上移动 $2$ 步最优，第二个环上移动 $1$ 步最优。这时无论怎么操作，两个环都无法同时最优。换句话说，这两个同余方程没有公共解。

由于我们还要保证字典序最小，那么显然是尽量满足前面的环，即最小位置在最前面的环。后面的环怎么办？考虑枚举每个环上移动的步数 $k$，使得 $k$ 和前面的同余方程不冲突，在此条件下满足字典序尽可能小（即最小位置放尽可能小的数）。

怎么判断某个 $k$ 是否满足前面的同余方程？考虑到这个同余方程的模数是前面所有环长的 $\text{lcm}$，是阶乘级别的，没法直接做（然而官方题解拿 Python 水了）。考虑到 

$$
x\equiv a \pmod m \Leftrightarrow x\equiv a_i\pmod {m_i^{\alpha_i}}
$$

其中 $m_i, \alpha_i$ 是 $m$ 的标准分解。

那么可以分解出环长的质因子。设 $f(p)$ 表示当前同余方程的解模 $p$ 的值。那么枚举操作次数 $k$ 的同时，要满足对环长的每一个质因子 $p$，$k \bmod p$ 都和 $f(p)$ 相同。满足这个条件的情况下，再让字典序尽可能小。

于是我们做完了。

```c++
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int ps[N], minp[N], res[N], z[N], p[N], w[N], f[N], nr = 0;
bool vis[N];

void sieve (void)
{
	for (int i = 2; i < N; i++) {
		if (!minp[i]) ps[++nr] = i, minp[i] = i;
		for (int j = 1; ps[j] * i < N; j++) {
			minp[i * ps[j]] = ps[j];
			if (i % ps[j] == 0) break;
		}
	}
}

int main (void)
{
	int n;
	
	cin.tie (0)->sync_with_stdio (false);
	cin >> n;
	
	sieve ();
	memset (f, -1, sizeof f);
	
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1; i <= n; i++) cin >> z[i];
	for (int i = 1; i <= n; i++) if (!vis[i]) {
		int j = i;
		vector<int> q, p;
		
		while (!vis[j]) vis[j] = true, q.push_back (j), j = w[j];
		int l = q.size (), t = l;
		while (t > 1) {
			int u = minp[t], w = 1;
			while (t % u == 0) t /= u, p.push_back (w *= u);
		}
		
		int k = -1;
		for (int i = 0; i < l; i++) {
			for (auto j : p) if (f[j] != -1 && i % j != f[j]) goto nxt;
			if (k == -1 || z[q[k]] > z[q[i]]) k = i;
			nxt:;
		}
		
		for (int i = 0; i < l; i++) res[q[i]] = z[q[(i + k) % l]];
		for (auto v : p) f[v] = k % v;
	}
	
	for (int i = 1; i <= n; i++) cout << res[i] << " \n"[i == n];
	return 0;
}

```

---

## 作者：Inui_Sana (赞：4)

场上 20min 过了。感觉现有题解对复杂度分析有点问题，于是写一写。

首先置换的形状显然是若干个环。考虑设操作次数为 $k$，依次对每个环贪心。对于一个长为 $l$ 的环 $i$，在满足限制的情况下，贪心地把 $a$ 中更小的放到前面。设在这种情况下要求 $k\bmod l=f_i$。

考虑这个环的操作对于其他环的操作有什么限制。若后面有另一个长为 $l'$ 的环 $j$。若 $\gcd(l,l')=1$ 则显然没有限制。否则，若存在 $d|l,d|l'$，则会有限制：$f_i\bmod d=f_j\bmod d$。

于是找到 $l$ 的所有因数后，会得到若干个形如 $f_j\bmod x=y$ 的限制。这个理论上可以 excrt，但是不难发现 $f_i<l_i,\sum l_i=n$，所以可以每次暴力地找合法的 $f_i$，精细实现，这一部分的复杂度就是 $O(n)$ 的。处理完当前环的 $f_j$ 后，再枚举 $l'$ 的因数，更新限制即可。

这个复杂度看似是 $O(n\sqrt n+nd(n)\log n)$ 的（中间要进行取 $\operatorname{lcm}$ 的操作），但是发现所有环长之和为 $n$，对于每个环的复杂度又是 $O(\sqrt l+d(l)\log l)$ 的，不难发现 $\forall l,l=1$ 时复杂度最大，为 $O(n)$。

code：

```cpp
int n,m,a[N],p[N],to[N],ans[N],lim[N];
bool vis[N];
vector<int> g,h;
void dfs(int u){
	vis[u]=1;
	g.eb(a[u]);
	h.eb(u);
	if(!vis[to[u]]){
		dfs(to[u]);
	}
}
void Yorushika(){
	read(n);
	rep(i,1,n){
		read(p[i]);
		to[p[i]]=i;
	}
	rep(i,1,n){
		read(a[i]);
	}
	mems(lim,-1);
	rep(i,1,n){
		if(!vis[i]){
			g.clear(),h.clear();
			dfs(i);
			int p=0,d=0,x=1;
			for(int j=1;j*j<=g.size();j++){
				if(g.size()%j==0){
					if(~lim[j]){
						while(d<(int)g.size()&&d%j!=lim[j]){
							d+=x;
						}
						x=lcm(x,j);
					}
					int k=g.size()/j;
					if(~lim[k]){
						while(d<(int)g.size()&&d%k!=lim[k]){
							d+=x;
						}
						x=lcm(x,k);
					}
				}
			}
			p=d;
			for(int j=d;j<(int)g.size();j+=x){
				if(g[j]<g[p]){
					p=j;
				}
			}
			rep(j,0,(int)g.size()-1){
				ans[h[j]]=g[(j+p)%(int)g.size()];
			}
			for(int j=1;j*j<=g.size();j++){
				if(g.size()%j==0){
					int k=g.size()/j;
					lim[j]=p%j,lim[k]=p%k;
				}
			}
		}
	}
	rep(i,1,n){
		printf("%d ",ans[i]);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：YangRuibin (赞：1)

更新：修改了不符合规范的 Latex。
## 题目分析
因为 $a$ 和 $p$ 都是排列，所以这些转移关系会构成一些环。要让字典序最小，就要以环上编号最小点的位置为依据，从前往后**依次保证**环上**能选到的**最小数位于最前端。

## 解法
### 概述
不难发现，对于一个环，操作次数以环的长度为周期，操作结果**周期性循环**。因此，如果求解过程中有两个环 $a$ 和 $b$，第一个环操作 $sta$ 步最优，累加的周期为 $sum$ 则第二个环上能选到的点的下标包括 $(sta+sum\times k) \bmod len_b$，其中 $k$ 为求出的最优步数。多个环，则需要一步步累加。
### 难点讲解
如何计算 $sum$？因为 $sum$ 要满足所有环的周期，所以前 $i$ 个环的 $sum$ 是前 $i$ 个环长的最小公倍数。

如何计算 $sta$？其实 $sta+sum\times k$ 就是了。

然而，在计算期间，无法对这两个值取模，因为模数不固定。于是它们的值就会大到爆炸。所以我们要用**压位高精**来存储它（其实高精度对低精度取模并不难写），到用的时候再取模后（值会足够小）转 int 即可。
## 核心代码
```cpp
bigint sum;sum.init(1);//周期
bigint sta;sta.init(0);//累计
for(int i=1;i<=tot;i++)
{
  //bigint 转 int
  int nowsta=(sta-((sta/g[i].size())*g[i].size())).to_int();
  int nowsum=(sum-((sum/g[i].size())*g[i].size())).to_int();
  int nowmn=0;
  for(int j=0;j<g[i].size();j++)
  {
      if(a[g[i][(nowsta+nowsum*j)%g[i].size()]]<a[g[i][(nowsta+nowsum*nowmn)%g[i].size()]])
      nowmn=j;
  }
  for(int j=0;j<g[i].size();j++)
  {
      ans[g[i][j]]=a[g[i][(nowsta+nowsum*nowmn+j)%g[i].size()]];
  }
  sta=sta+sum*nowmn;
  //tot为环的数量
  if(i<tot)sum=sum/gcd(nowsum,g[i].size())*g[i].size();
}
```

## 附上压位高精代码
```cpp
#define int long long
const int lim=1e10,siz=80;
struct bigint{
	int a[85];
	void init(int x)
		{memset(a,0,sizeof(a));a[0]=x;}
	int to_int()
	{
		int ret=0;
		for(int i=2;i>=0;i--)ret=ret*lim+a[i];
		return ret;
	}
	void print()
	{
		for(int i=siz;i>=0;i--)
		{
			if(i&&!a[i])continue;
			printf("%lld",a[i]);i--;
			while(i>=0)printf("%.10lld",a[i]),i--;
		}
	}
	int &operator[](int x){return a[x];}
};
bigint operator+(bigint a,bigint b)
{
	for(int i=0;i<siz;i++)
	{
		a[i]+=b[i];
		if(a[i]>=lim)a[i+1]+=a[i]/lim,a[i]%=lim;
	}
	return a;
}
bigint operator-(bigint a,bigint b)
{
	for(int i=0;i<=siz;i++)
	{
		if(a[i]<b[i])--a[i+1],a[i]+=lim;
		a[i]-=b[i];
	}
	return a;
}
bigint operator/(bigint a,int b)
{
	int res=0;bigint ret;ret.init(0);
	for(int i=siz;i>=0;i--)
		res=res*lim+a[i],ret[i]=res/b,res%=b;
	return ret;
}
bigint operator*(bigint a,int b)
{
	bigint c;c.init(0);
	for(int i=0;i<siz;i++)c[i]+=a[i]*b;
	for(int i=0;i<siz;i++)c[i+1]+=c[i]/lim,c[i]%=lim;
	return c;
}
```

---

## 作者：g1ove (赞：1)

显然若把序列转换成图，即连一条 $i\to p_i$ 的边，容易发现，根据排列的优良性质，每个点只有一条入边和一条出边。

考虑一个点进行若干次移位等价于它在环上跳若干次。

字典序最小典型的贪心，把每一位的环处理出来，然后不妨令跳的次数为 $x$，会转化成如同 $x\equiv a\pmod m$ 这样的式子，似乎只用 exCRT 合并就可以 $O(n\log n)$ 过掉了？

肯定不是。合并出来的 $\text{lcm}$ 非常非常大，`__int128` 也存不下。

不妨观察，令环长为 $l$，则 $\sum l=n$，这是一个很熟悉的式子，告诉我们**本质不同的 $l$ 只有 $\sqrt n$ 种**。

因此我们可以牺牲 $\sqrt n$ 的复杂度，存下之前的所有方程暴力跑判断就行了，时间复杂度 $O(n\sqrt n\log n)$，还跑挺快。

[Submission](https://atcoder.jp/contests/abc371/submissions/57799356)

```cpp
#include<bits/stdc++.h>
#define N 200005
#define ll long long
using namespace std;
int n,m;
int a[N],p[N];
int vis[N];
int b[N];
struct FC{
	ll a,m;
}f[N];
struct node{
	int x,id;
}c[N];
bool check(FC a)
{
	for(int i=1;i<=m;i++)
		if((a.a-f[i].a)%__gcd(a.m,f[i].m)) return 0;
	f[++m]=a;
	return 1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		int now=i,L=0,tim=0,R=0;
		while(now^i||!L) c[L]=(node){a[now],L},b[L++]=a[now],vis[now]=1,now=p[now];
		sort(c,c+L,[](node a,node b){return a.x<b.x;});
		for(int i=0;i<L;i++)	
			if(check((FC){c[i].id,L})){tim=c[i].id;break;}
		now=i;
		while(now^i||!R) a[now]=b[(R+tim)%L],now=p[now],++R;
	}
	for(int i=1;i<=n;i++) printf("%lld ",a[i]);
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

写了一个比官方题解还复杂的 Python 做法，但是真的很好想 QwQ。

## 简要题意

给定一个长度为 $n$ 的序列 $a$ 和大小为 $n$ 的置换 $p$。

你需要求出一个 $k$，定义 $p^k$ 表示 $p$ 经过 $k$ 次复合得到的置换，构造一个长度为 $n$ 的序列 $b$，有 $b_i=a_{p^k_i}$，使得 $b$ 字典序最小。输出这个 $b$。

$1\leq n\leq 2\times 10^5$。

## 思路

前置知识：ExCRT。

对于字典序最小的问题，我们可以考虑枚举 $b$ 的每一位去贪心，假设我们枚举到第 $1$ 位。

考虑 $b_1$ 可能是哪些值，假设 $1$ 所在的置换环为 $\{1,q_1,q_2,\cdots,q_m\}$，则 $b_1$ 的可能值为 $\{b_1,b_{q_1},b_{q_2},\cdots,b_{q_m}\}$，并且只要去定了第 $1$ 位是什么，第 $q_1,q_2,\cdots,q_m$ 位也是可以确定的。

我们不妨枚举置换环的每一个元素（因为每一个元素只会被枚举一次，所以时间复杂度可以保证），找到 $a_{q_i}$ 最小的 $q_i$，然后让 $b_i=a_{q_i}$，最后遍历置换环完善其他点填哪个数。

然后考虑另一个不和 $1$ 在同一个置换环的元素，唯一的区别是置换环上的有些值是不可达的，具体来说，如果可以到达 $q_i$，则需要满足 $k\equiv i\pmod{m}$，那么相当于验证若干个同余方程是否有解的问题，可以利用 ExCRT 将前面的同余方程合并起来，然后就可以跑一遍 ExGCD 验证这个同余方程和以前的同余方程联立得到的方程组是否有解。

时间复杂度 $O(n\log n)$，忽略高精度带来的时间复杂度开销。

## 代码

```python
import math
from typing import Tuple, Dict

def exgcd(a: int, b: int) -> Tuple[int]:
    if not b:
        return 1, 0
    y, x = exgcd(b, a % b)
    return x, y - (a // b) * x

def excrt(eq1: Tuple[int], eq2: Tuple[int]) -> Tuple[int]:
    a, b = eq1; A, B = eq2
    if eq1 == (1, 0):
        return eq2
    g = math.gcd(a, A)
    if (B - b) % g > 0:
        raise Exception
    d = (B - b) // g
    k1, _ = exgcd(a, A)
    k1 = k1 * d
    x, y = k1 * a + b, (a * A) // g
    x = (x % y + y) % y
    return (y, x)

n = int(input())
p = [0]; p.extend(map(int, input().split()))
a = [0]; a.extend(map(int, input().split()))
ret = [0] * (n + 1)
tag = [False] * (n + 1)
eq = (1, 0)

for i in range(1, n + 1):
    if tag[i]:
        continue
    cur = i; zak: Dict[int, bool] = {}
    while cur not in zak.keys():
        zak[cur] = True
        cur = p[cur]
    cycle = list(zak.keys())
    min_pos = -1
    for j in range(len(cycle)):
        valid = True
        try: excrt(eq, (len(cycle), j))
        except: valid = False
        if valid:
            min_pos = j if (min_pos == -1 or a[cycle[min_pos]] > a[cycle[j]]) else min_pos
    if min_pos == -1:
        raise NotImplementedError()
    cur, ctt = i, min_pos
    eq = excrt(eq, (len(cycle), min_pos))
    while not tag[cur]:
        tag[cur] = True
        ret[cur] = a[cycle[ctt]]
        ctt += 1
        if ctt == len(cycle):
            ctt = 0
        cur = p[cur]

for i in range(1, n + 1):
    print(ret[i], end=" ")
```

---

## 作者：Union_Find (赞：0)

# 题意

给定两个排列 $a_i$ 和 $p_i$，每次轮换将 $a_i$ 移动到 $a_{p_i}$ 的位置上。问在若干次轮换后，$a_i$ 字典序最小的数组。

# 思路

首先考虑字典序是贪心，所以有一个贪心策略，就是优先把最小的数往前放。

我们知道一个知识，就是这样轮换会形成若干个有向的环，所以对于位置 $1$ 所在的环，找到最小的数字并放到最小的位置上。

假设第 $i$ 的环的大小是 $len_i$，将最小的数字移动到最前面至少要 $res_i$ 步，那么这个环最优当且仅当假设最后操作了 $x$ 次，$x = k \times len_i + res_i$。我们可以现预处理求出所有的 $len_i$ 和 $res_i$。

现在的问题变成了求一个 $x$，使得尽量靠前的环 $i$ 满足 $x \equiv res_i\pmod{len_i}$。这同样也是贪心，如果有一个 $x$ 能同时满足当前的 $i$ 和之前所有 $j$，那么就更新 $x$。否则优先保留前面的。

到了这一步，剩下的就是 CRT 的事了。但是有个问题，如果你是用 C++ 的话，模数相乘之后会爆到 $10^{100}$ 左右，所以官方题解用了 Python。但是如果你是 C++ 的话，请继续往下看。

我们不能直接 CRT，但是可以把原式变形。如果 $len = {p_1}^{r_1}{p_2}^{r_2}\dots{p_k}^{r_k}$，那么我们就可以变形为 $x \equiv res\pmod {{p_1}^{r_1}} \dots x \equiv res\pmod {{p_k}^{r_k}}$。所以我们可以把原式拆开算 CRT。当然到了这一步，也不用 CRT 了。我们直接存若干个约束条件修改完之后每个约束条件。然后对于每个环，暴力枚举在这个环上进行几次轮换。我们可以用之前的约束条件在 $O(\sqrt{n})$ 的时间内完成 check。然后在所有可以行的方案中选择字典序最小的，也就是选最靠前的位置最小的方案。这样子枚举 $O(n)$，check $O(\sqrt{n})$，总共 $O(n\sqrt{n})$。

# CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), p[N], a[N], ys[N], mo[N], isp[N], cnt, vis[N], mp[N][35], goo[N], ans[N], np[N];
il bool check(ll a, ll p){//长度为 p 的环上操作 a 次是否可行 
	ll pp = p;
	for (int i = 2; i * i <= p; i++){
		if (p % i) continue;
		ll ress = 0;
		while (p % i == 0){
			p /= i, ress++;
			ll k = mp[i][ress];
			if (ys[k] != -1 && pp % mo[k] == 0 && a % mo[k] != ys[k]) return 0;
		}
	}
	if (p > 1){
		ll k = mp[p][1];
		if (ys[k] != -1 && pp % mo[k] == 0 && a % mo[k] != ys[k]) return 0;
	}
	return 1;
}
int main(){
	for (int i = 1; i <= n; i++) isp[i] = 1;
	isp[1] = 0;
	for (int i = 2; i <= n; i++){
		if (isp[i]){
			for (int j = i, k = 1; j <= n; j *= i, k++) mo[++cnt] = j, mp[i][k] = cnt;
			for (int j = i + i; j <= n; j += i) isp[j] = 0;
		}
	}//预处理出 pi^ri 
	for (int i = 1; i <= n; i++) p[i] = rd(), np[p[i]] = i;
	for (int i = 1; i <= n; i++) a[i] = rd();
	for (int i = 1; i <= cnt; i++) ys[i] = -1;
	for (int i = 1; i <= n; i++){
		if (vis[i]) continue;
		ll tt = 1e18, res = -1, len = 1;
		for (int u = p[i]; u != i; vis[u] = 1, len++, u = p[u]);//这里 i 是位置最小的 
		vis[i] = 1;
		for (int u = i, j = 0; u != i || j == 0; u = np[u], j++) if (check(j, len) && tt > a[u]) tt = a[u], res = j;//res 是这个环上的操作次数 
		for (int j = 2; j * j <= len; j++){
			if (len % j) continue;
			ll ress = 0;
			while (len % j == 0){
				len /= j, ress++;
				ys[mp[j][ress]] = res % mo[mp[j][ress]];
			}
		}if (len > 1) ys[mp[len][1]] = res % mo[mp[len][1]];
		goo[i] = res;//确定下来的这个环的操作次数 
	}memset (vis, 0, sizeof vis);
	for (int i = 1; i <= n; i++){
		if (vis[i]) continue;
		ll v = i;
		for (int j = 1; j <= goo[i]; j++) v = p[v];v = p[v];
		for (int u = p[i]; u != i; u = p[u], v = p[v]) ans[v] = a[u], vis[u] = 1;
		ans[v] = a[i], vis[i] = 1;
	}for (int i = 1; i <= n; i++) printf ("%lld ", ans[i]);
	return 0;
}
/*
6
2 1 6 3 4 5
1 2 6 3 4 5
*/
```

---

## 作者：Federico2903 (赞：0)

## 前言

赛时没调出来，已红温求放过。

## 思路

首先看到这种置换，先想到建图，把他做成一张有向图，会有很多个简单环。

考虑一次操作相当于在环上转一次，然后因为字典序最小，显然可以贪心。

考虑从左往右考虑，每个环**需要在保证前面的环答案不变的情况下让第一个数最小**。

保证前面的环的答案不变是显然的，否则不如不转。

如果要保证前面的环答案不变，就应该保持和前面的环的同余关系。

也就是说，每次应该转的步数应该是前面所有环长的 $\mathrm{lcm}$。但是这个东西显然是无法乘起来维护的。

> Hack：
> 
> 使第 $i$ 个环的环长是第 $i$ 个质数。

考虑分解质因数，记 $p_i$ 表示前面的环长 $\mathrm{lcm}$ 能被质数 $i$ 整除且含有 $p_i$ 个 $i$。

使用这种方法我们可以用 $O(\sqrt n)$ 的时间计算出前面环长的 $\mathrm{lcm}$。

当我们遇到一个新的环时，计算出这个环长 $len$ 和前面环长 $\mathrm{lcm}$ 的 $\gcd$，设为 $g$。

若 $g = 1$，不难发现此时环上每一个点都可以取到（因为两数互质，可以取到所有的余数）。

若 $g > 1$，此时环上会被分隔为 $\frac{len}{g}$ 段，每一段都只能取到第一个数。

此时已经可以直接贪心了。

![image.png](https://s2.loli.net/2024/09/15/OpDGQPoTrbEt34e.png)

但这是个悲伤的故事。

所以到底哪里错了呢。

其实可以发现，我们忽略掉了前面转到最优处所消耗的步数，也就是**后面的部分被强制转动的步数**。

然后你就会发现你卡在了维护 $\mathrm{lcm}$ 模环长上。

分解质因数过后取模是不方便的（但是这道题可以 Python 过）。

但是注意到环长至多有 $\sqrt n$ 种取值。我们暴力维护出来 $\mathrm{lcm}$ 模所有环长的值，再维护偏移量模所有环长的值，这是简单的。

维护的方法很简单，设偏移量模 $i$ 的值为 $s_i$，先将环转 $s_i$ 步。记 $\mathrm{lcm}$ 模 $i$ 的值为 $r_i$，此时转一步保持同余相当于前进 $r_i$ 步。

设最后的最优取值前进了 $k \times r_i$ 步，那么可以对于每一个环长 $j$ 简单更新偏移量：

$$s_j \gets (s_j + k \times r_i) \bmod {j}$$

然后贪心就做完了，时间复杂度 $O(n \sqrt n)$。

## AC 代码

写的很长，见谅：

```cpp
#define int ll

const int MAXN = 2e5 + 5;
int n, p[MAXN], a[MAXN];
vector <int> G[MAXN];
bool vis[MAXN];
int idx[MAXN];

int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

pair <int, vector <pii> > get_gcd(int val) {
	vector <pii> fac;
	rep (i, 2, sqrt(val)) {
		int pw = 0;
		while (val % i == 0) pw++, val /= i;
		if (pw > 0) fac.push_back(dl(i, pw));
	}
	if (val) fac.push_back(dl(val, 1));
	vector <pii> tmp = fac;
	for (auto &p : fac) {
		p.fb = min((ll) p.fb, idx[p.ec]);
	}
	int res = 1;
	for (auto [bs, pw] : fac) {
		res *= qpow(bs, pw);
	}
	rep (i, 0, tmp.size() - 1) {
		tmp[i].fb = tmp[i].fb - fac[i].fb;
	}
	return dl(res, tmp);
}

int rem[MAXN];
vector <int> df;

void insert(vector <pii> &v) {
	vector <int> val;
	for (auto [bs, pw] : v) {
		val.push_back(qpow(bs, pw));
		idx[bs] += pw;
	}
	for (auto v : val) {
		for (auto ps : df) {
			rem[ps] = rem[ps] * v % ps;
		}
	}
}

int len;
vector <int> cir;
int dis[MAXN];

void dfs(int u) {
	++len;
	vis[u] = 1;
	cir.push_back(u);
	for (auto v : G[u]) if (!vis[v]) dfs(v);
}

void getdis(int u) {
	dis[u] = 1;
	for (auto v : G[u]) if (!dis[v]) getdis(v), dis[u] = dis[v] + 1;
}

int ans[MAXN], mk[MAXN];
int steps[MAXN];

void update_step(int a) {
	for (auto ps : df) {
		steps[ps] = (steps[ps] + rem[ps] * a) % ps;
	}
}

signed main() {
	n = read();
	rep (i, 1, n) p[i] = read();
	rep (i, 1, n) a[i] = read();
	rep (i, 1, n) G[p[i]].push_back(i);
	rep (i, 1, n) {
		if (vis[i]) continue;
		len = 0;
		vector <int>().swap(cir);
		dfs(i);
		df.push_back(len);
	}
	sort(df.begin(), df.end());
	df.erase(unique(df.begin(), df.end()), df.end());
	memset(vis, 0, sizeof vis);
	rep (i, 0, n) rem[i] = 1;
	rep (i, 1, n) {
		if (vis[i]) continue;
		len = 0;
		vector <int>().swap(cir);
		dfs(i);
		auto val = get_gcd(len);
		vector <pii> ins;
		ins.swap(val.fb);
		int gval = val.ec;
		vector <int> ccir;
		int r = steps[len];
		rep (i, r, cir.size() - 1) ccir.push_back(cir[i]);
		for (auto val : cir) ccir.push_back(val);
		rep (i, 0, r - 1) ccir.push_back(cir[i]);
		getdis(ccir[0]);
		dis[ccir[0]] = 0;
		int ps = 0, mxval = 1e9;
		for (auto i = 0; i < len; i += gval) {
			if (a[ccir[i]] < mxval) ps = i, mxval = a[ccir[i]];
		}
		int pos = 0, cnt = 0;
		do {
			pos = (pos + rem[len]) % len;
			if (pos == 0) break;
			mk[pos] = ++cnt;
		} while (pos != 0);
		update_step(mk[ps]);
		insert(ins);
		rep (i, ps, ps + len - 1) {
			ans[cir[i - ps]] = a[ccir[i]];
		}
	}
	rep (i, 1, n) print(ans[i]), putchar(32);
	puts("");
	return 0;
}
```

---

## 作者：mango2011 (赞：0)

比较有趣的题目，~~但是场上因为网卡被爆了，赛后六分钟通过~~。

首先，一看到这种题目，就会想到将 $i$ 向 $P_i$ 连边。由于 $P$ 是一个排列，所以最终会形成若干个不相交的有向环。$A$ 也是一个排列，因此我们可以采用按照位置从小到大贪心的策略：

对于每一个环，其实一次操作就是将其进行一次循环位移。我们可以按照环中的最小位置对环进行排序。然后，我们依次处理每一个环：

设当前的环为 $l_1,l_2,l_3,\dots,l_{sz}$（$l_i$ 表示环上第 $i$ 个点所对应的位置，$l_n$ 也连向 $l_1$），不妨设 $l_1=\min\{l_i\}$。这样，我们再按照 $a_{l_1},a_{l_2},a_{l_3},\dots,a_{l_{sz}}$ 从小到大对 $l_i$ 排序得到 $r_1,r_2,r_3,\dots,r_{sz}$。这个时候，我们肯定希望 $a_{l_1}$ 最终能够变成尽量小的 $a_{r_i}$。因此，我们可以令 $i=1,2,3,\dots,sz$，依次进行检查当前的方案是否可行。

下面具体来讲一下如何检查：

对于一个环 $h_i$，如果其大小为 $sz_i$，$l_1$ 匹配的位置在环上与 $l_1$ 的距离为 $d_i$，那么就相当于总的操作数 $N\equiv d_i\pmod {sz_i}$。设当前已经处理了 $t-1$ 个环，要尝试插入第 $t$ 个环，那么：

$N\equiv d_i\pmod {sz_i}$。由于 $sz_i$ 可能不互质，所以考虑扩展中国剩余定理的结论：

这个同余方程组有解的充分必要条件是任意的 $d_i-d_j$ 都是 $\gcd(sz_i,sz_j)$ 的倍数。这样子的话，我们就可以设计下面的方法进行检查：

可以枚举 $j=\gcd(sz_i,sz_t)$，然后会发现无解的条件就是：

存在 $k$，使得 $k-d_t\not=0\pmod j$，于是问题就变得非常容易了。

容易发现检查部分枚举最大公约数后是 $O(1)$ 操作的，因此单次检查的复杂度为 $O(\sqrt {sz_t})$，而一个大小为 $k$ 的环又最多只能被检查 $k$ 次，因此总复杂度为 $O(\sum sz_i\sqrt{sz_i})=O(n\sqrt{n})$，可以通过，并且实际上完全跑不满。

[提交记录](https://atcoder.jp/contests/abc371/submissions/57788532)

---

