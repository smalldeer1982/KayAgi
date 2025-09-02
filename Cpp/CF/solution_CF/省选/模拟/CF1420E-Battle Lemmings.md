# Battle Lemmings

## 题目描述

A lighthouse keeper Peter commands an army of $ n $ battle lemmings. He ordered his army to stand in a line and numbered the lemmings from $ 1 $ to $ n $ from left to right. Some of the lemmings hold shields. Each lemming cannot hold more than one shield.

The more protected Peter's army is, the better. To calculate the protection of the army, he finds the number of protected pairs of lemmings, that is such pairs that both lemmings in the pair don't hold a shield, but there is a lemming with a shield between them.

Now it's time to prepare for defence and increase the protection of the army. To do this, Peter can give orders. He chooses a lemming with a shield and gives him one of the two orders:

- give the shield to the left neighbor if it exists and doesn't have a shield;
- give the shield to the right neighbor if it exists and doesn't have a shield.

In one second Peter can give exactly one order.

It's not clear how much time Peter has before the defence. So he decided to determine the maximal value of army protection for each $ k $ from $ 0 $ to $ \frac{n(n-1)}2 $ , if he gives no more that $ k $ orders. Help Peter to calculate it!

## 说明/提示

Consider the first example.

The protection is initially equal to zero, because for each pair of lemmings without shields there is no lemmings with shield.

In one second Peter can order the first lemming give his shield to the right neighbor. In this case, the protection is two, as there are two protected pairs of lemmings, $ (1, 3) $ and $ (1, 4) $ .

In two seconds Peter can act in the following way. First, he orders the fifth lemming to give a shield to the left neighbor. Then, he orders the first lemming to give a shield to the right neighbor. In this case Peter has three protected pairs of lemmings — $ (1, 3) $ , $ (1, 5) $ and $ (3, 5) $ .

You can make sure that it's impossible to give orders in such a way that the protection becomes greater than three.

## 样例 #1

### 输入

```
5
1 0 0 0 1```

### 输出

```
0 2 3 3 3 3 3 3 3 3 3```

## 样例 #2

### 输入

```
12
0 0 0 0 1 1 1 1 0 1 1 0```

### 输出

```
9 12 13 14 14 14 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15```

# 题解

## 作者：duyi (赞：18)

[超超超超超超超超超超超超爽的阅读体验](https://www.cnblogs.com/dysyn1314/p/13729196.html)

## 题目大意

[题目链接](https://codeforces.com/contest/1420/problem/E)

有一排 $n$ 个[林檎实]，有些[林檎实]拿着盾牌，有些没有。我们称一对[林檎实]是**被保护的**，当且仅当它们都**没有**拿盾牌，且在他们之间有有人拿着盾牌。

你可以进行若干次操作，每次操作是如下两种之一：

- 选择一个拿着盾牌，且他**左边**的人没盾牌的[林檎实] $i$ ($1< i\leq n$)，将第 $i$ 个[林檎实]的盾牌给他左边的人。
- 选择一个拿着盾牌，且他**右边**的人没盾牌的[林檎实] $j$ ($1\leq j<n$)，将第 $j$ 个[林檎实]的盾牌给他右边的人。

现在，给你一个长度为 $n$ 的 $01$ 序列，表示初始时每个[林檎实]是否拿着盾牌。

[林檎实]的妹子随时会过来找他约会，所以他也不知道他还能进行几次操作。因此，对于所有 $k\in[0,\frac{n(n-1)}{2}]$，请算出做**不超过** $k$ 次操作时，最多能有多少对被保护的[林檎实]。也就是说，你需要输出 $\frac{n(n-1)}{2}$ 个数。

数据范围：$1\leq n\leq 80$。

## 本题题解

设没拿盾牌的点数量为 $c_0$，拿着盾牌的点数量为 $c_1$。

初步转化 1：考虑两个 $0$ **不是**被保护的，当且仅当它们之间没有 $1$。也就是说，被保护的对数 = 总对数 - 在同一段里的 $0$ 的对数。具体来说，设有 $k$ 段极长、连续的 $0$，长度分别为 $l_1,l_2,\dots,l_k$，则被保护的对数 $=\frac{c_0(c_0-1)}{2}-\sum_{i=1}^{k}\frac{l_i(l_i-1)}{2}$。于是我们只要最小化 $\sum_{i=1}^{k}\frac{l_i(l_i-1)}{2}$ 即可。

初步转化 2：考虑已知一个目标局面（也就是一个 $01$ 序列），那么从初始局面到这个目标局面的最少操作次数，显然就是两个局面里 第一个 $1$、第二个 $1$、...、第 $c_1$ 个 $1$ 分别的坐标差之和。也就是说，初始局面的每个 $1$ 和目标局面的每个 $1$，按顺序依次对应，可以证明这样操作是最优的（调整法）。记初始局面里每个 $1$ 的位置分别为 $p_1,p_2,\dots,p_{c_1}$。

有了上述两个结论，我们可以通过 DP 来确定目标序列，顺便求出**未被保护的对数**（$\sum_{i=1}^{k}\frac{l_i(l_i-1)}{2}$）和**操作次数**。

设 $dp[i][x][y][z]$ 表示考虑了前 $i$ 位，用了 $x$ 次操作，前 $i$ 位里总共有 $y$ 个 $1$，从最后一个 $1$ 到 $i$ 之间这最后一段 $0$ 的长度为 $z$，这个局面下未被保护的对数的最小值。转移时考虑第 $i+1$ 位是填 $0$ 还是填 $1$ 即可。时间、空间复杂度都是 $O(n^5)$（因为 $x$ 这一维大小是 $\frac{n(n-1)}{2}=O(n^2)$ 的，不要忘了）。可以用滚动数组优化空间，不过这种做法时间、空间常数都较大。

考虑简化状态定义。设 $dp[i][x][y]$ 表示考虑了前 $i$ 位，**第 $i$ 位上填 $1$**，用了 $x$ 次操作，前 $i$ 位里总共有 $y$ 个 $1$，这个局面下未被保护的对数的最小值。转移时枚举下一个 $1$ 在哪里。这样时间复杂度依然是 $O(n^5)$，但空间复杂度优化到了 $O(n^4)$。本做法的 AC 代码请见【参考代码1】。

继续优化。考虑先枚举 $x,y$，再枚举 $i$。此时能转移到 $dp[i][x][y]$ 的，一定是 $x'=x-|p_y -i|$，$y'=y-1$。也就是说 $x'$ 和 $y'$ 都是确定的，我们只需要找到最优的 $j$ ($j<i$)，然后用 $dp[j][x'][y']$ 更新 $dp[i][x][y]$ 即可。$O(n^5)$ 的做法相当于是枚举了 $j$。考虑如何不枚举，快速求出最优的 $j$。

具体来说，我们先观察一下转移式：
$$
dp[i][x][y] = \min_{j<i}\{dp[j][x'][y'] + \frac{(i - j - 1)(i - j - 2)}{2}\}
$$
首先可以去掉“除以 $2$”，在求答案的时候一起除。另外，因为 $x,y,x',y'$ 都是常数，不妨将它们写在前面。于是我们重新定义状态：$f_{x,y}(i) = dp[i][x][y]\times2$。然后把上式中的 $(i - j - 1)\cdot (i - j - 2)$ 拆开，得到：
$$
f_{x,y}(i) = \min_{j<i}\{f_{x',y'}(j)+i^2-3i+j^2+3j-2ij+2\}
$$
其中 $i^2$, $-3i$, $2$ 都是常数，可以提出来。关键的部分是 $-2ij$，可以用**斜率优化**搞定它。具体来说，把每个 $j$ 看成二维平面上一个坐标为 $(j,f_{x',y'}(j)+j^2+3j)$ 的点，转移看成一条斜率为 $2i$ 的直线，我们要最小化直线的**截距**（也就是 $f_{x,y}(i)$ 加上一堆关于 $i$ 的常数）。写成式子就是：
$$
f_{x',y'}(j)+j^2+3j=2ij+f_{x,y}(i)-i^2+3i-2
$$
对每个 $(x',y')$ 分别维护一个**下凸壳**，然后在凸壳上二分出第一段斜率大于 $2i$ 的位置即可。

时间复杂度 $O(n^4\log n)$。空间复杂度 $O(n^4)$。本做法的 AC 代码请见【参考代码2】。

## 参考代码

参考代码1：时间复杂度 $O(n^5)$，空间复杂度 $O(n^4)$。

```cpp
// problem: CF1420E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 80;
const int INF = 0x3f3f3f3f;
int n, a[MAXN + 5], cnt[2], pos[MAXN + 5];
int total, max_op;
int dp[MAXN + 5][MAXN * (MAXN - 1) / 2 + 5][MAXN + 5];
int calc(int len) { return len * (len - 1) / 2; }

int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		cnt[a[i]]++;
		if(a[i] == 1) {
			pos[cnt[1]] = i;
		}
	}
	total = calc(cnt[0]);
	max_op = calc(n);
	if(!cnt[1]) {
		for(int i = 0; i <= max_op; ++i) cout << 0 << " "; cout << endl;
		return 0;
	}
	
	memset(dp, 0x3f, sizeof(dp));
	for(int i = 1; i < n; ++i) {
		dp[i][abs(pos[1] - i)][1] = calc(i - 1);
		for(int j = 0; j <= max_op; ++j) {
			for(int k = 1; k <= i && k < cnt[1]; ++k) if(dp[i][j][k] != INF) {
				int rest = cnt[1] - k;
				for(int l = i + 1; l <= n - rest + 1; ++l) {
					int newj = j + abs(pos[k + 1] - l);
					if(newj <= max_op)
						ckmin(dp[l][newj][k + 1], dp[i][j][k] + calc(l - i - 1));
				}
			}
		}
	}
	int res = total;
	for(int j = 0; j <= max_op; ++j) {
		for(int i = cnt[1]; i <= n; ++i) if(dp[i][j][cnt[1]] != INF) {
			ckmin(res, dp[i][j][cnt[1]] + calc(n - i));
		}
		cout << total - res << " ";
	}
	cout << endl;
	return 0;
}
```

参考代码2：时间复杂度 $O(n^4\log n)$ 斜率优化做法。

```cpp
// problem: CF1420E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 80, MAXOP = MAXN * (MAXN - 1) / 2;
const int INF = 0x3f3f3f3f;
int n, a[MAXN + 5], cnt[2], pos[MAXN + 5];
int total, max_op;
int dp[MAXOP + 5][MAXN + 5][MAXN + 5];
struct Queue {
	int a[MAXN + 5];
	int ql, qr;
	int size() { return qr - ql + 1; }
	bool empty() { return ql > qr; }
	int front() { return a[ql]; }
	int back() { return a[qr]; }
	int back2() { return a[qr - 1]; }
	void push_back(int e) { a[++qr] = e; }
	void pop_back() { --qr; }
	void init() { ql = 1; qr = 0; }
}que[MAXOP + 5][MAXN + 5];

int calc(int len) { return len * (len - 1) / 2; }
int calc2(int len) { return len * (len - 1); }

int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		cnt[a[i]]++;
		if(a[i] == 1) {
			pos[cnt[1]] = i;
		}
	}
	total = calc(cnt[0]);
	max_op = calc(n);
	if(!cnt[1]) {
		for(int i = 0; i <= max_op; ++i) cout << 0 << " "; cout << endl;
		return 0;
	}
	
	memset(dp, 0x3f, sizeof(dp));
	for(int j = 0; j <= max_op; ++j) {
		for(int k = 1; k <= cnt[1]; ++k) {
			que[j][k].init();
		}
	}
	for(int i = 1; i <= n; ++i) {
		#define Q que[abs(pos[1] - i)][1]
		#define F dp[abs(pos[1] - i)][1]
		#define Y(p) (F[(p)] + (p) * (p) + 3 * (p))
		
		F[i] = calc2(i - 1);
		while(Q.size() >= 2 && (Y(Q.back()) - Y(Q.back2())) * (i - Q.back()) > (Y(i) - Y(Q.back())) * (Q.back() - Q.back2()))
			Q.pop_back();
		Q.push_back(i);
		
		#undef Q
		#undef F
		#undef Y
	}
	for(int j = 0; j <= max_op; ++j) {
		for(int k = 2; k <= cnt[1]; ++k) {
			for(int i = k; i <= n - (cnt[1] - k); ++i) {
				if(j < abs(pos[k] - i)) continue;
				int last_j = j - abs(pos[k] - i);
				#define Q que[last_j][k - 1]
				#define F dp[last_j][k - 1]
				#define Y(p) (F[(p)] + (p) * (p) + 3 * (p))
				if(Q.empty()) continue;
				if(Q.front() >= i) continue;
				int l = Q.ql;
				int r = Q.qr;
				while(l < r) {
					int mid = (l + r + 1) >> 1;
					if(Q.a[mid] < i) {
						l = mid;
					} else {
						r = mid - 1;
					}
				}
				l = Q.ql;
				while(l < r) {
					int mid = (l + r) >> 1;
					int p1 = Q.a[mid], p2 = Q.a[mid + 1];
					if(Y(p2) - Y(p1) > 2 * i * (p2 - p1)) {
						r = mid;
					} else {
						l = mid + 1;
					}
				}
				ckmin(dp[j][k][i], F[Q.a[l]] + calc2(i - Q.a[l] - 1));
				#undef Q
				#undef F
				
				#define Q que[j][k]
				#define F dp[j][k]
				while(Q.size() >= 2 && (Y(Q.back()) - Y(Q.back2())) * (i - Q.back()) > (Y(i) - Y(Q.back())) * (Q.back() - Q.back2()))
					Q.pop_back();
				Q.push_back(i);
				
				#undef Q
				#undef F
				#undef Y
			}
		}
	}
	int res = total;
	for(int j = 0; j <= max_op; ++j) {
		for(int i = cnt[1]; i <= n; ++i) if(dp[j][cnt[1]][i] != INF) {
			ckmin(res, (dp[j][cnt[1]][i] + calc2(n - i)) / 2);
		}
		cout << total - res << " ";
	}
	cout << endl;
	return 0;
}
```


# 创作不易，点个赞吧！






---

## 作者：tommymio (赞：7)

#### [可能更好的阅读体验](https://www.cnblogs.com/tommy0103/p/13744726.html)

拿到这道题，考虑先简化问题，我们发现可以把 $0/1$ 串缩成一个数列 $a$ ，$a_i$ 表示第 $i$ 个 $1$ 与第 $i-1$ 个 $1$ 有 $a_i$ 个 $0$，记序列 $a$ 的长度为 $m$。

那么移动盾牌这一操作就变为将 $a_x$ 加 $1$，$a_{x+1}$ 减 $1$ 或是将 $a_x$ 减 $1$ ，$a_{x+1}$ 加 $1$。而 $ans=\sum\limits_{i=1}^m\sum\limits_{j=i+1}^m a_ia_j=\frac{1}{2}\left(\sum\limits_{i=1}^m\sum\limits_{j=1}^ma_ia_j-\sum\limits_{i=1}^ma_i^2\right)$。于是我们只需要求出进行了 $i$ 次操作后，$\min \left\{\sum\limits_{i=1}^ma_i^2\right\}$ 的值即可。

这个值显然无法贪心求出，于是考虑 $\text{DP}$。设 $f_{i,j,k}$ 为序列中前 $i$ 个数，进行了 $k$ 次操作后，当前 $\sum\limits_{x=1}^ia_x=j$，所能够得到的 $\min\left\{\sum\limits_{x=1}^i a_x^2\right\}$。为了方便，我们预处理出 $s_i=\sum\limits_{j=1}^ia_j$。

于是有转移式：

$$
f_{i+1,l,|l-s_{i+1}|+k}=\min\{f_{i,j,k}+(l-j)^2\}
$$

此处转移式的 $|l-s_{i+1}|+k$，其实是一个结论：对于两个长度为 $n$ 的序列 $a,b$，可以对序列 $a$ 的相邻两数 $+1,-1$，经过操作由 $a$ 得到序列 $b$ 的最小操作数为 $\sum_{i=1}^n \left|\sum\limits_{j=1}^i a_j-\sum\limits_{j=1}^i b_j\right|$。前提是序列 $a$ 经过操作能够得到序列 $b$ ，也就是 $\sum_ia_i=\sum_i b_i$。感性理解这个结论是非常容易的，对当前数 $a_i$ 进行操作将它变为 $b_i$，会对以后的数产生影响：如果对 $a_i$ 加，就是对 $a_{i+1}$ 减；如果对 $a_i$ 减，就是对 $a_{i+1}$ 加。而转移式中的 $|l-s_{i+1}|+k$ 其实就是 $\left|\sum\limits_{j=1}^i a_j-\sum\limits_{j=1}^i b_j\right|$ 的体现。

此处附上一段更为严谨的证明：

> 可以看作每个位置有一个东西，初始时 $a_i<b_i$ 这个位置上是负值，$a_i>b_i$ ，这个位置上是正值，每次可以把一个正的移动一下，那就是按顺序匹配一下，考虑每条边的贡献就是前缀和的绝对值之和 ——myh 神仙

这样直接枚举每个量刷表，时间复杂度是 $O(n^5)$ 的，然而由于 $j$ 这一维的特殊性，有效的 $j$ 很少，所以实际时间复杂度远低于 $O(n^5)$。当然，你也可以选择对这个方程进行斜率优化，可以做到稳定的 $O(n^4 \log n)$。

**Show the Code**
```cpp
#include<cstdio>
#include<cstring>
const int inf=0x3f3f3f3f;
int a[85],b[85],s[85],f[85][85][3205];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline int abs(const int &x) {return x<0? -x:x;}
int main() {
	int n=read(),m=1,sum=0;
	for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=1;i<=n;++i) {if(a[i]==0) ++b[m]; else ++m;}
	for(register int i=1;i<=m;++i) {s[i]=s[i-1]+b[i];}
	memset(f,0x3f,sizeof(f)); f[0][0][0]=0;
	for(register int i=0;i<m;++i) {
		for(register int j=0;j<=s[m];++j) {
			for(register int k=0;k<=n*(n-1)/2;++k) {
				if(f[i][j][k]==inf) continue;
				for(register int x=j;x<=s[m];++x) {
					if(k+abs(x-s[i+1])>n*(n-1)/2) continue;
					int &tmp=f[i+1][x][k+abs(x-s[i+1])];
					tmp=min(tmp,f[i][j][k]+(x-j)*(x-j));
				}
			}
		}
	}	
	int mn=inf;
	for(register int i=0;i<=n*(n-1)/2;++i) {mn=min(mn,f[m][s[m]][i]);printf("%d ",(s[m]*s[m]-mn)>>1);}
	return 0;
}
```



---

## 作者：Karry5307 (赞：7)

### 题意

略。

$\texttt{Data Range:}1\leq n\leq 80$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13766422.html)

首先考虑初始状态怎么算答案。很明显直接数满足的不好数，用总的减去不满足的还比较好做。注意到所有不满足的是一段 $0$，所以就没了。

然后考虑怎么算从一个初始状态转移到一个目标状态的步数。考虑邻项交换，发现肯定是贪心匹配最优。

所以说如果有一个目标序列的话那么就可以算出初始序列到这个序列的步数和这个序列的答案，于是就可以直接 DP 目标序列。（这个时候我们 DP 未被保护的对数的最小值）

设 $f_{i,j,k}$ 表示当前考虑到第 $i$ 位并且钦定这一位填 $1$，移动了 $j$ 次并且这一段前缀中有 $k$ 个 $1$ 时未被保护对数的最小值。实际上转移的话考虑枚举下一个 $1$ 在哪里，这个时候可以算出中间一段 $0$ 对答案的贡献和需要移动的步数，就能够转移了。

最后处理的时候枚举一下最终序列中最后一个 $1$ 填的哪里就好了，时间复杂度 $O(n^5)$。由于我比较菜所以不会斜率优化做法。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=85;
ll n,tot,res,m,r,c;
ll x[MAXN],cnt[2],pos[MAXN],f[MAXN][MAXN*MAXN][MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void chkmin(ll &x,ll y)
{
	x=x<y?x:y;
}
inline ll binom(ll n)
{
	return n*(n-1)/2;
}
int main()
{
	m=binom(n=read());
	for(register int i=1;i<=n;i++)
	{
		cnt[x[i]=read()]++;
		x[i]?pos[cnt[1]]=i:1;
	}
	if(!cnt[0])
	{
		for(register int i=0;i<=m;i++)
		{
			printf("%d ",0);
		}
		return 0;
	}
	res=tot=binom(cnt[0]),memset(f,0x3f,sizeof(f));
	for(register int i=1;i<=n;i++)
	{
		f[i][abs(pos[1]-i)][1]=binom(i-1);
		for(register int j=0;j<=m;j++)
		{
			for(register int k=1;k<=i&&k<cnt[1];k++)
			{
				r=cnt[1]-k;
				if(f[i][j][k]!=0x3f3f3f3f)
				{
					for(register int l=i+1;l<=n-r+1;l++)
					{
						c=j+abs(pos[k+1]-l);
						if(c<=m)
						{
							chkmin(f[l][c][k+1],f[i][j][k]+binom(l-i-1));
						}
					}
				}
			}
		}
	}
	for(register int j=0;j<=binom(n);j++)
	{
		for(register int i=cnt[1];i<=n;i++)
		{
			if(f[i][j][cnt[1]]!=0x3f3f3f3f)
			{
				chkmin(res,f[i][j][cnt[1]]+binom(n-i));
			}
		}
		printf("%d ",tot-res);
	}
}
```

---

## 作者：STDLRZ (赞：4)

这道题目我就直接上思路吧，很多大佬已经具体讲了思路了。

### 题意

称一对坐标是满足题目要求的，当且仅当这两个守卫都为 $0$，但他们之间有 $1$。

可以进行相邻数字的交换，求 $0 \sim \frac{n \times (n+1)}{2}$ 区间中时刻中最多有多少对守卫是被保护的。

### 题意转换

因为直接求有多少对满足要求的话，不太好做，所以我们转换成求有多少对不满足要求即可。

那么不满足要求的就是 $\operatorname{C}^2_{cnt_0}-\sum_{i=1}^n \operatorname{C}_{len_i}^2$，其中 $len_i$ 表示每一连续段 $0$ 的长度，这里指的段是极大的。$cnt_0$ 指的是 $0$ 的个数。

可以发现，$\operatorname{C}^2_{cnt_0}$ 是有固定的值的，所以只需要让 $\sum_{i=1}^n \operatorname{C}_{len_i}^2$ 最小即可。

### 解题思路

我们令 $dp_{i,j,k}$ 表示考虑前 $i$ 项，第 $i$ 项为 $1$，移动了 $j$ 步，且在 $1 \sim i$ 的区间里有 $k$ 个 $1$ 的没有被保护的守卫的最小值。

时间复杂度显而易见，$\mathcal O(n^5)$。

空间复杂度也是的，$\mathcal O(n^4)$。

那么，考虑转移。

这里与其他题解不同，将详细的讲解如何转移。

首先，因为这个 DP 的目的是为了求的是**没有**被保护的守卫的**最小值**，所以初始化的时候要初始为极大值。

然后，因为逆推极其的困难，这里我们采用顺推。

如何枚举：

1. 枚举 $i$。
2. 枚举 $j$，其中范围在 $0 \sim \frac{n \times (n-1)}{2}$ 区间中。因为也可以一步都不移，所以下限是 $0$。
3. 枚举在 $1 \sim i$ 的区间中，有多少个 $1$。其中，有以下注意点：

- 不能超过目前枚举的 $i$，这里不做解释，过于简单。
- 不能大于等于题目中的序列中 $1$ 的数量，因为这里能做的操作相当于交换，但是无法改变全局个数，而且后面在枚举 $x$ 的时候还要让一个 $1$ 出来，所以也不能等于题目中给出的序列中 $1$ 的数量。

4. 枚举 $x$，下限为 $i+1$，不做解释。上限为 $n-t_1+k+1$，其中 $1$ 表示所有守卫中有多少个拿着盾牌。为什么是这个上限呢？

变换如下：

$$
n-t_1-k+1=n-(t_1-k)+1
$$

此时，$t_1-k$ 的意义是还剩多少个 $1$ 能填。

这样，就非常的清晰明了了。

如果这一部分还是看不懂，可以看代码注释。

5. 转移方程

注意，移动的次数不能超过 $m$，不然那就没有意义了。

那么，转移方程为：

$$
dp_{x,j+|pos_{k+1}-x|,k+1} \gets \min(dp_{x,j+|pos_{k+1}-x|,k+1},dp_{i,j,k}+\operatorname{C}_{x-i-1}^2)
$$

其中，$pos_{k+1}$ 代表第 $k+1$ 个 $1$ 在原序列中的坐标。

为什么是 $|pos_{k+1}-x|$？

因为我们现在 $x$ 是 $1$，这又是第 $k+1$ 个 $1$，我们自然要把这个 $1$ 移过来，这样就是上面的式子。

为什么是 $\operatorname{C}^2_{x-i-1}$ 呢？

首先，$x$ 和 $k$ 的值都是 $1$，也就是说，$x+1 \sim k-1$ 区间中的所有值都为 $0$。

那么这个区间 $0$ 的个数，就是 $(k-1)-(x+1)+1=x-i-1$，然后再用求方案数的办法算就行了。

6. 求解答案

具体见代码和代码注释，因为~~不方便描述~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[90],t[2],pos[90],ans1,ans2,dp[90][8100][90];
// dp[i][j][k] 表示考虑到第 i 位，第 i 位一定填 1，并且移动了 j 次且这一段前缀中有 k 个 1 时
// 没有被保护的对数最小值 
const int mex=1e9;
template<typename Name> void nread(Name &x){
	x=0;
	bool f=0;
	char ch=getchar();
	while(ch<'0' && ch>'9') f=(ch=='-' ? 1 : f),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	if(f) x=-x;
	return ;
}
int C2(int x){
	return (x*(x-1))>>1;
}
void Fmin(int &x,int y){
	if(x>y) x=y;
	return ;
}
int main(){
	nread(n);
	m=C2(n);
	for(int i=1;i<=n;++i){
		nread(a[i]);
		++t[a[i]];
		if(a[i]==1) pos[t[1]]=i;
	}
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	if(t[0]==0){
		for(int i=0;i<=m;++i) cout<<"0 ";
		cout<<"\n";
		exit(0); 
	}
	ans1=ans2=C2(t[0]);
	for(int i=0;i<90;++i)
		for(int j=0;j<8100;++j)
			for(int k=0;k<90;++k) dp[i][j][k]=mex;
	for(int i=1;i<=n;++i){
		dp[i][abs(i-pos[1])][1]=C2(i-1);
		for(int j=0;j<=m;++j){
			for(int k=1;k<=i && k<t[1];++k){
				if(dp[i][j][k]>=mex) continue; // 类似于剪枝 
				for(int x=i+1;x<=n-t[1]+k+1;++x){
					/*
					为什么是 n-t[1]+k+1 ?
					首先，令 c=t[1]-k
					那么 c 代表的就是剩下的可填的 1 的个数
					可以把式子转换成 n-c+1
					但是，你无论如何也要让最后面的 c 个 1 有位置吧
					不然后面都没有位置了，那这个状态就不合法了。 
					*/
					if(j+abs(pos[k+1]-x)<=m)
						Fmin(dp[x][j+abs(pos[k+1]-x)][k+1],dp[i][j][k]+C2(x-i-1));
						/*
						这里写 C2(x-i-1) 的原因是：
						i 与 x 都是 1
						则 i+1 与 x-1 之间就都是 0
						这样的话，区间就是 x-1-(i+1)+1=x-(i+1)=x-i-1
						这样的话，加起来的方案数就是 C2(x-i-1)
						故为如此。
						这里写 j+abs(pos[k+1]-x) 的原因是：
						因为 1~i 有 k 个 1，但是我们又规定了 x 是 1，其他的便不是 1，则我们需要移动
						abs(pos[k+1]-x) 才行
						这里我们需要将 pos[k+1] 移到 x，但是不知道是左是右，所以采用绝对值。
						这里的第三维 k+1 便不做解释。
						其中，dp[i][j][k] 必须有效才会转移，否则理都不会理。
						其中，k<t[1] 的原因是枚举到 x 的时候，x 也是 1，但是不能出现 t[1]+1 个 1
						所以故为 k<t[1]。
						k<=i 便比较简单了，前面只有 i 个数，你竟然成功的放了 i+1 个 1......
						还有，第 44 行  dp[i][abs(i-pos[1])][1]=C2(i-1);  的解释 
						首先，我们准备在 i 这个地方放下一个 1
						则我们需要把第一个位置移到这个地方来
						第三维是 1 因为初始的时候只有这一个 1。
						C2(i-1) 是因为只有 i 是 1，所以前面都是 0，总的方案数就是 C2(i-1) 
						*/
				}
			}
		}
	}
	for(int j=0;j<=m;++j){ // 有 i 个 1，至少也要都放在前面 
		for(int i=t[1];i<=n;++i){ // 枚举最后一个 1 是谁 
			Fmin(ans2,dp[i][j][t[1]]+C2(n-i)); // 首先，移动了 j 步，有 cnt[1] 个 1（题目要求） 
			/*
			为什么是 C2(n-i)？
			这是一个好问题。
			首先，i 循环到了 t[1]
			那么还有几对没有循环到呢？
			那当然是后面的 i+1~n，因为后面都是 0，没有一个 1 了
			*/
		}
		cout<<ans1-ans2<<" ";
	}
	cout<<"\n";
	return 0; 
}
```

---

## 作者：TernaryTree (赞：4)

老年选手不会写斜率优化。遂 $\Theta(n^5)$ 暴力 dp 通过，记之。

这种题一看就是先用某一个简洁的式子把“有多少对守卫是被保护的”和“一个序列到另一个序列的最小操作次数”形式化地表达出来。类似这样的题目还有 [CF1860D Balanced String](https://www.luogu.com.cn/problem/CF1860D)。

对于前者，考虑“有多少对守卫**不**是被保护的”。显然就是每个极长 $0$ 连续段长度的平方和再除以 $2$。也就是说，设 $1$ 的个数为 $m$，$1$ 的位置分别是 $p_1,p_2,\cdots ,p_m\ (p_1<p_2<\cdots <p_m)$，则被保护的守卫数量就是 $\dfrac{(n-m)^2-\sum\limits_{i=0}^{m}(p_{i+1}-p_i-1)^2}{2}$（其中 $p_0=0,p_{m+1}=n+1$）。又 $m$ 是不变量，所以最大化这个式子，等价于最小化 $\sum\limits_{i=0}^{m}(p_{i+1}-p_i-1)^2$。

再来考虑“一个序列到另一个序列的最小操作次数”。我们仍沿用上一段中关于 $1$ 出现位置的定义。此时的经典结论是，假设一个 $01$ 序列 $1$ 的出现位置是 $p_i$，另一个是 $q$，则通过交换相邻项使这两个序列相同的最少次数是 $\sum\limits_{i=1}^m |p_i-q_i|$。一个简单的证明：假设只操作 $q$，每次交换后 $q$ 的任意一个元素 $+1$ 或 $-1$。而如果 $a,b\ (a<b)$ 要通过这个操作变成 $c,d\ (c<d)$，不可能会让任意两者的移动路径相交（更具体地，我们只会让 $a\to c$，$b\to d$，因为 $a\to d$ 和 $b\to c$ 一定不优，可以结合数轴上任意四点两两匹配的距离和理解）。

到这里我们就可以很轻松地设计出一个 dp：$f_{i,j,k}$ 表示当前在我们自己的出现位置序列上放了 $i$ 个数，其中最后一个数是 $j$，目前这些数通过最少 $k$ 次操作可以变成给定序列中 $1$ 的出现位置序列的前 $i$ 项，前文式子的最小值。转移时，枚举当前位置序列的倒数第二个数。如下：

$$f_{i,j,k}=\min_{l=0}^{j-1} f_{i-1,l,k-|p_i-j|}+(j-l-1)^2$$

其中 $l=0$ 表示如果当前是第一个数，也需要计算 $j-1-l=j-1$ 这一段的贡献。

统计答案时枚举序列中最后一个数 $j$，使用 $f_{m,j,k}+(n-j)^2$ 更新 $ans_k$ 的最小值。

上面的 dp 中，$i,j,l$ 皆为 $\Theta(n)$，$k=\Theta(n^2)$，故时间复杂度为 $\Theta(n^5)$。

~~才不会告诉你我写到这里试着交了一发，结果过了。~~

当然我们要追求更好的复杂度。注意到对于固定的 $i,j,k$，转移方程右边的式子和 $l$ 有关的下标只有一个，并且贡献是一个平方形式。这让我们想起斜率优化的模板题。然后就可以按照斜率优化，维护凸壳的方法做了，复杂度是 $\Theta(n^4\log n)$。

最后嘲讽一下出题人没卡掉 $\Theta(n^5)$。/cf/cf/cf。

---

## 作者：JoaoFelix (赞：2)

比赛的时候切了这道题，但是代码好像写的有点仓促，后来重新修了一下。

讲下做这题的历程吧

拿道这道题最初的思想是感觉花的步数不会太多，然后到最优的时候我们变化的dat会越来越小，感觉可以用个bfs来模拟这个过程，然后我们只需要记录最优的就可以了，然后花了20min写了个bfs，发现跑的很慢，但是这个代码有助于我们后面测试小数据的调试。

于是看到80的范围，觉得还是可以有些其他的做法的，写了个感觉复杂度不对的dp，想着先写个暴力，然后用一些类似于单调性或者斜率优化的方法优化一下，但是后来加了几个剪枝，然后跑了下极限数据，发现飞快，于是就能过这题了，大概一共花了45min。

来讲下怎么dp：

我们就假设v是题目中要求的对数，方便后面的表述。

首先我们记录dp[i][j][k]代表当前dp到第i为，然后选了j个1，当前移动了k步的能使题目中要求的v的max值

然后由于我们发现1是不能交叉移动的，我们很快的算出需要移动的次数，就是我们把tot个1一一对应，然后算一下绝对值。

因为我们已经记录了当前选到第j个1，所以这部分的转移我们可以直接算出，转移了以后我们发现转移之间的v会发生什么的变化?

我们考虑算贡献，就是当前dp到第j个1的贡献，我们算下左右的0个个数相乘就可以，这个因为我们的1的个数已经有了，0的个数减一下也知道了，这样我们就成功处理了转移的方式，以及转移之间的v如何转移。

最后我们更新答案的时候取个前缀的max。

这个dp的状态是O(n^4)的，我们因为前两维i,j是O(n)，然后最后一维的距离是O(n^2)的，但是我们转移还要枚举，所以也是O(n)的，总复杂度理论是O(n^5)，最坏情况下的。

但是我们发现严重跑不满，我们当且仅当这个状态出现才会往下转移，并且本来dp的状态就会有很多距离是不可能出现的，因此我们可以测一下极限数据（全0，全1，一半0一半1），非常快，实际的时间复杂度应该还没有O(n^4)，所以O(~~玄学->能过~~) 

代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=85,S=4e3+5;
int n,a[N],lv[N],tot,dp[N][N][S],ans;
void rel(int &x,int y){x=x>y?x:y;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i])tot++,lv[tot]=i;
	}
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=0,lim;i<n;i++){
		lim=min(i,tot-1);
		for(int j=0;j<=lim;j++)for(int k=0;k<S;k++)if(dp[i][j][k]>=0){
			for(int p=i+1;p<=n;p++)rel(dp[p][j+1][k+abs(p-lv[j+1])],dp[i][j][k]+(i-j)*(p-i-1));
		}
	}
	int len=(n*(n-1))>>1;
	for(int t=0;t<=len;t++){
		for(int i=1;i<=n;i++)rel(ans,dp[i][tot][t]+(i-tot)*(n-i));
		printf("%d%c",ans," \n"[t==len]);
	}
	return 0;
}
```




---

## 作者：daniEl_lElE (赞：1)

考虑 $dp_{i,j,k,0/1}$ 表示看到第 $i$ 位，到目前为止移动了 $j$ 次，前 $i$ 个中有 $k$ 个填了 $1$，最后一段以 $0/1$ 结尾情况下最多多少对守卫受到保护。

转移枚举下一个 $i'$，这一段都是 $0/1$。预处理出第 $1\sim cnt_1$ 个 $1$ 的位置，转移是容易的。复杂度 $5$ 方。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define max(i,j) ((i>j)?i:j)
int dp[81][6401][81][2],p0[81],p1[81],t0,t1;
signed main(){
	int n; cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==0) p0[++t0]=i;
		if(a[i]==1) p1[++t1]=i;
	}
	memset(dp,-1,sizeof(dp));
	dp[0][0][0][1]=dp[0][0][0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i*n;j++){
			for(int k=0;k<=i;k++){
				//dp[i-1][j][k]
				int tot1=0;
				for(int l=i;l<=n;l++){
					tot1+=llabs(l-p1[(k+1)+(l-i)]);
					if(dp[i-1][j][k][1]!=-1) dp[l][j][k][0]=max(dp[l][j][k][0],dp[i-1][j][k][1]+(i-1-k)*(l-i+1));
					if(dp[i-1][j][k][0]!=-1) dp[l][j+tot1][k+(l-i+1)][1]=max(dp[l][j+tot1][k+(l-i+1)][1],dp[i-1][j][k][0]);
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n*(n-1)/2;i++){
		ans=max(ans,max(dp[n][i][t1][0],dp[n][i][t1][1]));
		cout<<ans<<" ";
	}
	return 0;
}
```

---

## 作者：STDquantum (赞：1)

可以先考虑一下如何简化问题。

---

首先可以简化一下题目中的 01 串。

发现连续的 0 对答案的贡献可以用乘积计算（如`100101`贡献就是 $2\times 1=2$），所以用连续 0 的个数来表示整个序列（如`100101`表示为 $\{0,2,1,0\}$）（新表示法元素个数为原序列 1 的个数加一）。于是整个序列的贡献就可以用 任意两个数乘积 的和来表示。

---

改变了表示法，再考虑在一次操作过后会对新的表示法序列造成什么影响。

如`100101`交换第一个 1 和第一个 0，成为`010101`，表示法变为 $\{1,1,1,0\}$。其改变就是在相邻两个元素做更改，一个加一，一个减一。

设 $S$ 为转化后的序列，元素为 $s_i$，元素个数 $k$，答案 $ans$ 为：
$$
\begin{aligned}
ans&=\sum_{i=1}^k\sum_{j=1}^{i-1}s_is_j \\
&=\frac12\left(\sum_{i=1}^k\sum_{j=1}^ks_is_j[i\neq j]\right)\\
&=\frac12\left(\sum_{i=1}^ks_i\sum_{j=1}^ks_j[i\neq j]\right)\\
&=\frac12\left(\left(\sum_{i=1}^ks_i\right)^2-\sum_{i=1}^ks_i^2\right)
\end{aligned}
$$
观察 $\displaystyle \sum_{i=1}^ks_i$ 这个式子的意义是什么。由 $S$ 的定义不难推出它代表原序列中 0 的数量。所以我们想要最大化答案，就要最小化 $\displaystyle \sum_{i=1}^ks_i^2$。

---

然后我们还需要考虑从 $A$ 状态转移到 $B$ 状态所需要的最少步数（因为要枚举状态方便转移）。每次操作最多只能让相邻元素一个加一一个减一。设 $g_{A,B}(i)$ 为让 $A$ 中的前 $i$ 个数和 $B$ 中前 $i$ 个相同的最小步数，对 $i=1$ 显然为 $\vert a_1-b_1\vert$，而扩展到 $i$ 更大的情况，就会有 $\displaystyle g_{A,B}(i)=\left\vert\sum_{j=1}^ia_j-\sum_{j=1}^ib_j \right\vert$。而想要将 $A$ 变成 $B$，总的需要的步数为 $\displaystyle \sum_{i=1}^{k-1}g_{A,B}(i)$（$A$ 和 $B$ 均有 $k$ 个元素）。

如果不太理解上式的同学可以看下这里，举个例子说明一下：

比如 $A=\{5,8\},B=\{8,5\}$，想要让 $A$ 变成 $B$，需要的操作次数就是 $\vert5-8\vert=3$；

比如 $A=\{5,9,3\},B=\{8,3,6\}$，首先要把 $A$ 的第一个元素变成 $8$，这样需要的次数是 $\vert5-8\vert=3$，然后这时就相当于 $A^\prime=\{6,3\},B^\prime=\{3,6\}$，需要的次数是 $\vert6-3\vert=3$，为啥不是 $\vert9-3\vert=6$ 呢？因为 $5$ 已经帮忙把 $9$ 减少 $3$ 了，也就是这个 $9$ 还要加上一个 $5-8$，也就是 $a_1-b_1$。那个大求和式就可以用这种方法一步一步分解掉。

---

做好了准备工作，就可以开始准备 DP 了。我们想要得到答案的话可以考虑 DP，设 $f_{i,sum,op}$ 为考虑到前 $i$ 个 $S$ 中的元素（$i\le k$），已经完成了 $op$ 次操作，经过 $op$ 次操作后 $\displaystyle \sum_{x=1}^{i}s_x=sum$，这时最小的 $\displaystyle \sum_{x=1}^{i}s_x^2$。

最终答案就是 $\displaystyle \frac12\left(cnt_0^2-f_{k,cnt_0,op}\right)$，$cnt_0$ 是原序列中 $0$ 的数量，或者说是 $\displaystyle \sum_{i=1}^ks_i$。

设 $\displaystyle z_i=\sum_{j=1}^is_j$，也就是原序列新表示法的前缀和（用于状态之间的转移）。

那么转移就可以先枚举 $i$ 从 $0$ 到 $k-1$，然后枚举 $sum$ 从 $0$ 到 $z_k$，再枚举 $op$ 从 $0$ 到 $\displaystyle \frac{n\cdot (n-1)}2$，最后一层枚举是 $q$ 介于 $sum$ 和 $z_k$ 之间，表示要转移到的 $sum^\prime$，那么我们转移就相当于在表示法末尾又添加了一个元素 $h=q-sum$。则 $f_{i+1,q,op+\vert q-z_{i+1}\vert}=f_{i,sum,op}+h^2$，默认是和自己取 $\min$。

这样总时间复杂度是 $\mathcal{O}(n^5)$，空间复杂度 $\mathcal{O}(n^4)$。但由于有很多状态根本不存在，所以很多 $q$ 的枚举是无法进行的。而且 DP 常数较小，可以通过本题。

代码：

```cpp
const int N = 80 + 6, inf = 0x3f3f3f3f;

inline void min(int &x, const int &y) { x = x < y ? x : y; } // 节省代码长度

int n, k, s[N], z[N], f[N][N][N * N];
inline void main() {
    read(n);

    /* 求出新表示法及其前缀和 */
    int a, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        read(a);
        if (a) {
            s[++k] = cnt, cnt = 0;
        } else {
            ++cnt;
        }
    }
    s[++k] = cnt;
    for (int i = 1; i <= k; ++i) z[i] = z[i - 1] + s[i];

    /* DP过程 */
    memset(f, 0x3f, sizeof(f)), f[0][0][0] = 0;
    int top = n * (n - 1) / 2, maxx = z[k];
    for (int i = 0; i < k; ++i) {
        for (int sum = 0; sum <= maxx; ++sum) {
            for (int op = 0; op <= top; ++op) {
                if (f[i][sum][op] == inf) continue; // 状态不存在不需要转移
                for (int q = sum, tmp, h; q <= maxx; ++q) {
                    if ((tmp = op + abs(q - z[i + 1])) > top) continue; // 超过所需次数没必要转移
                    h = q - sum;
                    min(f[i + 1][q][tmp], f[i][sum][op] + h * h);
                }
            }
        }
    }

    int minn = inf;
    for (int i = 0; i <= top; ++i) {
        min(minn, f[k][maxx][i]); // 取最优值
        write((maxx * maxx - minn) / 2), putchar(' ');
    }
}
```

# 

---

## 作者：RainWetPeopleStart (赞：0)

考虑最终状态的答案如何算，就是所有可能的对减掉 `0` 连续段之间的对。

如何移动 `1` 呢，把移动当成交换 `0` 和 `1`，记初始状态的 `1` 的位置分别为 $p_1,p_2,\dots,p_k$，终末状态的位置为 $t_1,t_2,\dots,t_k$（要求 $p,t$ 递增），则把 $p_i$ 移到 $t_i$ 一定最优。

记 $sp_1,sp_2,\dots,sp_k$ 表示初始状态第 $i$ 个 `1` 前面有多少个 `0`，$st_1,st_2,\dots,st_k$ 表示终末状态第 $i$ 个 `1` 前面有多少个 `0`，需要的时间为 $\sum\limits_{i=1}^k|sp_i-st_i|$。

然后就可以 DP 了，记 $f_{i,j,k}$ 表示考虑前 $i$ 个 `1`，前 $j$ 个 `0`，当前用的时间为 `k` 的答案。

当然，第一维可以压掉。

初始 $f_{*,0}=0$，其余为 $-\infty$。（因为压掉了第一维）

从小到大枚举 $i$，考虑 $f$ 的变化。

1. 加入一个 `1`，即 $f_{j,k}=f_{j,k-|sp_i-j|}$（越界当 $-\infty$ 处理）。

2. 加入 `0` 的连续段，$f_{j,k}=\max\limits_{x=0}^jf_{x,k}+x(j-x)$。

记 `0` 个数为 $c0$，`1` 的个数为 $c1$，有 $ans_i=\max\limits_{x=0}^if_{c0,x}$。

这样时间 $O(n^5)$，空间 $O(n^4)$，因为常数极小，可以过。

具体的，考虑循环执行次数，第一部分是 $c1\cdot c0\cdot \frac{n(n-1)}{2}$，第二部分为 $c1\cdot \frac{(c0+1)c0}{2}\cdot \frac{n(n-1)}{2}$，显然瓶颈在后一部分。

把 $n(n-1)$ 看作 $n^2$，$c0(c0+1)$ 看作 $c0^2$，有：

$$\begin{aligned}c1\cdot \frac{c0^2}{2}\cdot \frac{n^2}{2}= & \frac{n^2}{4}\cdot(c0^2\cdot c1)
\\= & \frac{n^2}{8}\cdot(c0^2\cdot 2c1)
\\ \le & \frac{n^2}{8}\cdot(\frac{c0+c0+2c1}{3})^3
\\= & \frac{n^2}{8}\cdot(\frac{2n}{3})^3
\\= & \frac{n^5}{27}
\end{aligned}$$

量级大概在 $10^8$ 左右。

---

## 作者：紊莫 (赞：0)

感觉是一个不太难的贪心思维和动态规划。

直接按时刻作为主要状态递推不太可行，所以考虑先求出一个总的状态，再从中找需要的状态。  

定义 $f_{i,j,k}$ 表示考虑到前 $i$ 位，第 $i$ 位上填了 $1$，前面总共填了 $j$ 个 $1$，当前时刻是 $k$ 时的**不可被保护的人的对数**最小值。

为什么呢，考虑对于一块 $0$，这样的贡献是独立的，否则会牵扯到后面的答案。

因为状态比较复杂，建议从已有状态推到其他状态，考虑 $f_{i,j,k}\rightarrow f_{x,y,z}$。显然我们肯定是向后找一段连续的位置放上 $0$，那么就枚举之后那个 $1$ 的位置（枚举 $x$），然后显然 $y = j+1$，考虑计算 $k$，显然 $k$ 越小越好（贪心），我们考虑两个状态之间如何最快的转移，可得每一个 $1$ 的位置“对齐”是最优的，那么就可以记录下一开始的每个 $1$ 的位置，直接转移即可。

代码短的可怜（轻微压行）。

```cpp
const int N=85,M=(N<<1),inf=1e16,mod=1e9+7;
int n,m,ans,r,a[N],f[N][N][N*N],p[N],c0,c1;
void solve(){
	n=rd();m=n*(n-1)/2;F(i,1,n){if(a[i]=rd())p[++c1]=i;else c0++;}
	r=ans=c0*(c0-1)/2; F(i,1,n-1) f[i][1][abs(p[1]-i)] = (i-2)*(i-1)/2; 
	F(i,1,n-1)F(j,1,min(i,c1-1))F(k,0,m)if(f[i][j][k]<inf)F(q,i+1,n-c1+j+1){
		int x=k+abs(p[j+1]-q); if(x>m) continue;
		f[q][j+1][x]=min(f[q][j+1][x],f[i][j][k]+(q-i-1)*(q-i-2)/2);
	}
	F(i,0,m){F(j,c1,n)r=min(r,f[j][c1][i]+(n-j)*(n-j-1)/2);cout<<ans-r<<' ';}
}
signed main() {
	memset(f,0x3f,sizeof f) ; solve(); return 0;
}
```


---

