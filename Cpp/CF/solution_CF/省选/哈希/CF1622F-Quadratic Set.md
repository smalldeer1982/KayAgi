# Quadratic Set

## 题目描述

Let's call a set of positive integers $ a_1, a_2, \dots, a_k $ quadratic if the product of the factorials of its elements is a square of an integer, i. e. $ \prod\limits_{i=1}^{k} a_i! = m^2 $ , for some integer $ m $ .

You are given a positive integer $ n $ .

Your task is to find a quadratic subset of a set $ 1, 2, \dots, n $ of maximum size. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
1```

### 输出

```
1
1```

## 样例 #2

### 输入

```
4```

### 输出

```
3
1 3 4```

## 样例 #3

### 输入

```
7```

### 输出

```
4
1 4 5 6```

## 样例 #4

### 输入

```
9```

### 输出

```
7
1 2 4 5 6 7 9```

# 题解

## 作者：I_am_Accepted (赞：8)

发现答案一定不小于 $n-3$。

以下设 $B=A-A'$。

**证明：**

$$
\prod\limits_{i=1}^{2k}i! =
2^kk!
\left(\prod\limits_{i=1}^{k}(2i-1)!\right)^2
$$

$n\equiv0\pmod{4}$ 时，取 $B=\{\frac{n}{2}\}$ 即可。

$n\equiv2\pmod{4}$ 时，取 $B=\{2,\frac{n}{2}\}$ 即可。

$n\equiv1\pmod{2}$ 时，去掉 $n!$ 这项后规模减小 $1$，成为偶数，变为上述两种情况。

注意上面的不一定是最优解。

所以我们先判断 $S=\prod\limits_{i=1}^{n}i!$ 是否为平方数。

若否，则判断是否 $\exists x ,\text{s.t. } \dfrac{S}{x!}$ 是平方数。

若再否，则判断是否 $\exists x,y,\text{s.t. }  \dfrac{S}{x!y!}$ 是平方数。

否则，答案 $=n-3$。

由于前面的判断与素因数个数的奇偶性有关，我们想到将素数赋随机 Hash 值，设 $f(x)$ 为 $x$ 分解素因数后每个素因数 Hash 值的异或和（多个相同素因数重复算）。

由于 $a \operatorname{xor} a=0$，$f(x)=0$ 当且仅当 $x$ 是平方数（在很高概率下）。

我们将 $f(x!)(1\le x\le n)$ 存入 `std::map` 匹配即可。

时间 $O(n\log n)$。

[Code](https://codeforces.com/contest/1622/submission/142751564)

---

## 作者：xcyle (赞：4)

通过如下构造可发现最大集合的大小大于等于 $n-3$：

如果 $n$ 是奇数，则将 $n\gets n-1$

注意到这个时候阶乘可以两两抵消，因而剩下的东西就是 $2,4,...,n$

如果 $n/2$ 是奇数，把 $2!$ 扔了

然后剩下的东西变成了 $1,2,...,n/2$，把 $\frac{n}{2}!$ 扔了即可

因而我们只需要判断最大集合是否大于 $n-3$ 即可，也就是最多扔两个

注意到取到 $n-3$ 的情况 $n$ 肯定是奇数，设 $p$ 是 $1-n$ 中最大的质数，那么扔掉的两个中较大者肯定大于 $p$，这样的组合不会太多。

时间复杂度大概是 $\sum\limits_{i \le n}\sum\limits_{p\in prime, p\times p \le i}1$

---

## 作者：MSqwq (赞：3)

打一下表发现，要舍去的数很少，少到几乎都 $\le3$，但是数大了打不了表了。  
考虑证明：  
因为 $\prod\limits_{i=1}^{n}i!=\prod\limits_{i=1}^{n}i^{n-i+1}$，也就是说当 $i$ 与 $n$ 不同奇偶的时候是一个完全平方数，那么可以考虑一下构造。 

$\prod\limits_{i=1}^{2k}i!=\prod\limits_{i=1}^{k}(2i)!⋅(2i-1)!=\prod\limits_{i=1}^{k}[(2i-1)!]^2⋅(2i)=2^k⋅k!\prod\limits_{i=1}^{k}[(2i-1)!]^2$  

有两个需要说明的地方：  
1.为啥要构造 $2k$，因为发现与 $n$ 同奇偶和不同奇偶有两种情况，不妨让其数量均分，所以构造 $2k$。  
2.为啥第一步不能是 $\prod\limits_{i=1}^{2k}i!=\prod\limits_{i=1}^{k}(i)!⋅(k+i)!$ 我最开始就是这么想的，然后发现推不出来啥，或者说很复杂，还是根据上面说的启发，考虑奇偶性去构造，就不难发现是两个两个一组，然后构造成平方数了。  

那么 $\prod\limits_{i=1}^{k}[(2i-1)!]^2$ 是一个完全平方数，只需要 $2^k⋅k!$ 满足为平方数即可。那么就得到以下结果：  
1. 当 $n\equiv0\pmod{2}$ 的时候，即 $n=2k$ 的情况  
继续讨论 $k$ 的奇偶，当 $k\equiv0\pmod{2}$ 的时候去掉 $k$ 就行，当 $k\equiv1\pmod{2}$ 的时候去掉 $2$ 和 $k$ 就行。  
2. 当 $n\equiv1\pmod{2}$ 的时候，发现只需要先去掉 $n$ 就可以变成上一种情况拉。  

现在我们知道要舍去的数的数量 $\le3$。现在考虑如何筛出来呢。   
发现完全平方数的本质是所有质因数次数为 $0$，数与数相乘本质是次数异或。那不妨考虑异或哈希，设函数为 $f_x$ 表示 $x$ 的异或哈希函数，当 $x$ 为质数的时候随机一个数作为函数值就行，其他的为它的质因数 $f_x$ 异或和。   
设舍去的数字数量为 $num$。  
当 $num=0$ 的时候即为 $1$ 到 $n$ 的所有 $f_x$ 异或值为 $0$。  
当 $num=1$ 的时候即为 $1$ 到 $n$ 的所有 $f_x$ 异或值为 $1$ 到 $n$ 的其中一个 $f_x$。  
当 $num=2$ 的时候用个 map 记一下就行，这个应该都会。  
当 $num=3$ 的时候，那么就是最坏的情况，不需要再枚举，直接不选 $2$ 和 $\left\lfloor\frac{n}{2}\right\rfloor$ 和 $n$ 就好。  
**对了随机的时候记得随大一点，比如 $[1,10^{18}]$ 才行，小了巨容易冲突。**  
代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int mod=1e18+10;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

const int N=2e6+10;
int pr[N],f[N],tot;
bool vis[N];

void genshin()
{
	memset(vis,true,sizeof(vis));
	for(int i=2;i<N;i++)
	{
		if(vis[i])pr[++tot]=i,f[i]=rand()*rand()%mod*rand()%mod;
		for(int j=1;j<=tot&&pr[j]*i<N;j++)
		{
			vis[i*pr[j]]=0,f[i*pr[j]]=f[i]^f[pr[j]];
			if(i%pr[j]==0)break;
		}
	}
}

signed main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	srand(252127643);
	genshin();int n=read();
	for(int i=1;i<=n;i++)f[i]^=f[i-1];
	int x=0;for(int i=1;i<=n;i++)x^=f[i];
	if(x==0)
	{
		cout<<n<<endl;
		for(int i=1;i<=n;i++)cout<<i<<" ";
		cout<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(x==f[i])
		{
			cout<<n-1<<endl;
			for(int j=1;j<=n;j++)if(i!=j)cout<<j<<" ";
			cout<<endl;
			return 0;
		}
	}
	map<int,int>mp;
	for(int i=1;i<=n;i++)mp[f[i]]=i;
	for(int i=1;i<=n;i++)
	{
		if(mp.count(x^f[i])&&mp[x^f[i]]!=i)
		{
			int p=mp[x^f[i]];
			cout<<n-2<<endl;
			for(int j=1;j<=n;j++)if(j!=p&&j!=i)cout<<j<<" ";
			cout<<endl;
			return 0;
		}
	}
	cout<<n-3<<endl;
	for(int i=1;i<=n;i++)if(i!=2&&i!=n&&i!=n/2)cout<<i<<" ";
	cout<<endl;
	return 0;
}
```


---

## 作者：Calculatelove (赞：2)

[CF1622F](http://codeforces.com/problemset/problem/1622/F)。

## Description

给出一个集合 $A = \{1, 2, ..., n\} = \{x \in \mathbb{Z} \mid 1 \leq x \leq n\}$。

你需要寻找一个非空集合 $A' \subseteq A$，使得 $\prod_{k \in A'} k!$ 是一个完全平方数。  
在此基础上，你需要最大化 $|A'|$，并以任意顺序给出集合 $A'$ 中的所有数。

数据范围：$1 \leq n \leq 10^6$。  
时空限制：$4000 \ \mathrm{ms} / 256 \ \mathrm{MiB}$。

## Solution

#### 结论

至少存在一个方案，使得集合 $A$ 中不选的数的个数 $\leq 3$。

#### 证明

假设现在给出任意一个正整数 $k$，考察下式：
$$
\begin{aligned}
\prod\limits_{i = 1}^{2k} i! & = \prod\limits_{i = 1}^k (2i - 1)! \cdot (2i)! \\
& = \prod\limits_{i = 1}^k \left((2i - 1)!\right)^2	\cdot 2i \\
& = \left( \prod\limits_{i = 1}^k (2i - 1)! \right)^2 \cdot 2^k \cdot k!
\end{aligned}
$$
- 对于 $n \equiv 0 \pmod 4$，可以取 $A' = A \setminus \left\{ \frac{n}{2} \right\}$。  
- 对于 $n \equiv 2 \pmod 4$，可以取 $A' = A \setminus \left\{2, \frac{n}{2}\right\}$。  
- 对于 $n \equiv 1 \pmod 2$，可以先不取 $n$ 这个数，然后转换为上述两种情况之一。

Q.E.D.

---

现在有了很优秀的构造解，但注意到该解不一定是最优解，还要处理集合 $A$ 中不选的数恰好为 $0, 1, 2$ 时的解。

考虑完全平方数的本质：在唯一分解形式下，所有质因子的次数均为**偶数**。这时候就可以考虑使用 xor hashing。

定义**完全异或性**哈希函数 $f(x)$，一开始先给 $1 \sim n$ 中的所有质数 $p$ 的 $f(p)$ 赋一个范围较大的随机数，其他的合数的 $f(x)$ 定义为 $x$ 所有**质因子的 $f$ 函数的异或和（多个相同质因子需要重复异或）**，特别地 $f(1) = 0$。在这样的定义下，$x$ 为完全平方数当且仅当 $f(x) = 0$。

$1 \sim n$ 中的 $f$ 函数值显然可以线性筛筛出来，由于其完全异或性，可以递推出 $f(i!)$ 的值。

记 $P = f(1!) \bigoplus f(2!) \bigoplus \cdots \bigoplus f(n!)$。

- 对于所有都选的情况，判断 $P$ 是否为 $0$ 即可。

- 对于不选 $1$ 个数的情况，相当于判断是否存在一个 $i$ 使得 $P \bigoplus f(i!) = 0$，枚举即可。

- 对于不选 $2$ 个数的情况，相当于判断是否存在一对 $i,j$ 使得 $P \bigoplus f(i!) \bigoplus f(j!) = 0$，可以先将所有 $f(j!)$ 的值存入一个哈希表或 `std::map`，再在这个容器中查找 $P \bigoplus f(i!)$ 即可。

实现的较好可以做到 $\mathcal{O}(n)$。

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <random>
#include <unordered_map>

typedef long long s64;

const int N = 1e6 + 10;
const s64 L = 1152921504606846976LL;

int n;

int k, prime[N], fac[N];
s64 f[N], S[N];

std::mt19937_64 rnd(time(0));
std::uniform_int_distribution<long long> dist(0, L - 1);

void sieve(int N) {
	f[1] = 0;
	for (int i = 2; i <= N; i ++) {
		if (!fac[i]) fac[i] = i, prime[++ k] = i, f[i] = dist(rnd);
		for (int j = 1; j <= k; j ++) {
			if (prime[j] > fac[i] || prime[j] > N / i) break;
			fac[i * prime[j]] = prime[j];
			f[i * prime[j]] = f[i] ^ f[prime[j]];
		}
	}

	for (int i = 1; i <= N; i ++)
		S[i] = S[i - 1] ^ f[i];
}

std::unordered_map<s64, int> List;

int cnt;
bool mark[N];

void output() {
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i ++) {
		if (mark[i]) continue;
		printf("%d ", i);
	}
}

int main() {
	freopen("square.in", "r", stdin);
	freopen("square.out", "w", stdout);

	scanf("%d", &n);
	sieve(n);

	s64 P = 0;
	for (int i = 1; i <= n; i ++) P ^= S[i];

	if (P == 0) {
		cnt = n, output();
		return 0;
	}

	for (int i = 1; i <= n; i ++)
		if ((P ^ S[i]) == 0) {
			cnt = n - 1, mark[i] = 1, output();
			return 0;
		}

	for (int i = 1; i <= n; i ++)
		List[S[i]] = i;

	for (int i = 1; i <= n; i ++)
		if (List.count(P ^ S[i])) {
			int j = List[P ^ S[i]];
			cnt = n - 2, mark[i] = 1, mark[j] = 1, output();
			return 0;
		}

	cnt = n - 3, mark[2] = 1, mark[(n - 1) / 2] = 1, mark[n] = 1, output();

	return 0;
}
```

---

## 作者：pomelo_nene (赞：2)

见到构造题……不如先写个[暴力](https://www.luogu.com.cn/paste/5b4j691m)？

猜测答案最小为 $n-3$。那么我们拆开，变成求解能否去掉 $0,1,2,3$ 个数之后使得 $A'$ 是个平方集合。

先确定一个大体的思路。注意到平方集合，乘积在分解之后质因子的幂数都是偶数，那么幂数可以划归到 $0$ 或者 $1$……这个东西有点类似于异或，那么几个阶乘的乘积质因数分解就相当于几个阶乘质因数分解之后幂次进行异或。

Motivation: 快速将几个阶乘质因数分解之后幂次进行异或。

考虑完善这个 Motivation，可以将每个质因子给定一个哈希值，这样一个数的质因数分解可以用其质因数分解后的所有质因子异或值表示。

那么问题就简单了。我们先求出 $\displaystyle \prod_{i=1}^n i!$ 的哈希值，记作 $k$。记 $f_i$ 为 $i!$ 的哈希值。

### 去掉 0 个数

此时 $k=0$。判断即可。

### 去掉 1 个数

此时 $k=f_i$，$O(n)$ 判断即可。

### 去掉 2 个数

考虑开一个 `map` 记下 $f_i \to i$ 的映射，那么当 `map` 中存在 $k \oplus f_p \to q$ 的时候，去掉 $p,q$ 合法。

### 去掉 3 个数

显然去掉 $2!,n!,\left\lfloor\dfrac{n}{2}\right\rfloor!$ 是合法的解（要找 Motivation 可以打表，去掉 3 个数的情况有 $7,11,23$）。

那么拼盘得正解。问题解决。

```cpp
/*
他决定要“格”院子里的竹子。于是他搬了一条凳子坐在院子里，面对着竹子硬想了七天，结果因为头痛而宣告失败。
DONT NEVER AROUND . //
*/
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(int x)
{
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
int cnt,prime[400005];
bool vis[1000005];
LL hsh[1000005],fac[1000005];
int n;
void shai(int up)
{
	uniform_int_distribution<LL> range(1,~(0llu));
	default_random_engine e(rand());
	vis[1]=true;
	for(int i=2;i<=up;++i)
	{
		if(!vis[i])	prime[++cnt]=i,hsh[i]=range(e);
		for(int j=1;j<=up && i*prime[j]<=up;++j)
		{
			vis[i*prime[j]]=true;
			hsh[i*prime[j]]=hsh[i]^hsh[prime[j]];
			if(i%prime[j]==0)	break;
		}
	}
	for(int i=2;i<=up;++i)	fac[i]=hsh[i]^fac[i-1];
}
unordered_map<LL,int> M;
int main(){
	srand(time(NULL));
	n=read();
	shai(n);
	LL val=0;
	for(int i=1;i<=n;++i)	val^=fac[i];
	if(val==0)
	{
		write(n),puts("");
		for(int i=1;i<=n;++i)	write(i),putchar(' ');
		return 0;
	}
	for(int i=1;i<=n;++i)
	{
		if(val==fac[i])
		{
			write(n-1),puts("");
			for(int j=1;j<=n;++j)	if(i!=j)	write(j),putchar(' ');
			return 0;
		}
	}
	for(int i=2;i<=n;++i)
	{
		if(M.find(val^fac[i])!=M.end())
		{
			int p=M[val^fac[i]],q=i;
			write(n-2),puts("");
			for(int j=1;j<=n;++j)	if(j!=p && j!=q)	write(j),putchar(' ');
			return 0;
		}
		M[fac[i]]=i;
	}
	write(n-3),puts("");
	for(int i=1;i<=n;++i)	if(i!=2 && i!=n && i!=n/2)	write(i),putchar(' ');
	return 0;
}
```

---

## 作者：Cx114514 (赞：1)

## 题目链接：[Quadratic Set](https://www.luogu.com.cn/problem/CF1622F)
首先有结论：删去的数不超过 $3$ 个。

证明：

 $$\prod\limits_{i=1}^{2k}i!=2^k k!\left[\prod\limits_{i=1}^{k}\left(2i-1\right)!\right]^2$$ 

$n \equiv 0 \pmod{4}$ 时，删去 $\frac{n}{2}$。

$n \equiv 2 \pmod{4}$ 时，删去 $2$ 和 $\frac{n}{2}$。

$n \equiv 1 \pmod{2}$ 时，删去 $n$ 后就变成了上述两种情况。

接下来只需分别考虑删去一个数、两个数和三个数的情况。

可以使用异或哈希。

将每一个质数用 mt19937_64 转化为一个极大随机值。

令 $i$ 所对应的该极大随机值为 $code\left(i\right)$。

令 $x=p_1p_2\cdots p_k$，$p\in \mathbb{P}$。

令 $f\left(x\right)=code\left(p_1\right)\oplus code\left(p_2\right)\oplus\cdots \oplus code\left(p_k\right)$。

例如 $f\left(36\right) = code\left(2\right)\oplus code\left(2\right)\oplus code\left(3\right)\oplus code\left(3\right)$。

若某些数的乘积为完全平方数，则其 $f$ 值的异或和为 $0$。

$f\left(x\right)$ 可以线性筛，$f\left(x!\right)$ 可以递推求得。

使用 unordered_map，时间复杂度可以做到 $O\left(n\right)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, tot, sum, f[1000005], code[1000005], prime[1000005], vis[1000005]; 

mt19937_64 rnd(time(0));

unordered_map < int, int > m;

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		code[i] = rnd();
	for (int i = 2; i <= n; i++)
	{
		if (!vis[i])
		{
			prime[++tot] = i;
			f[i] = code[i];
		}
		for (int j = 1; j <= tot && i * prime[j] <= n; j++)
		{
			vis[i * prime[j]] = 1;
			f[i * prime[j]] = f[i] ^ code[prime[j]];
			if (i % prime[j] == 0) break;
		}
	}
	for (int i = 1; i <= n; i++)
		f[i] ^= f[i - 1];	
	for (int i = 1; i <= n; i++)
		sum ^= f[i];	
	if (sum == 0)
	{
		cout << n << endl;
		for (int i = 1; i <= n; i++)
			cout << i << " ";
		cout << endl;
		exit(0);
	}
	for (int i = 1; i <= n; i++)
		if ((sum ^ f[i]) == 0)
		{
			cout << n - 1 << endl;
			for (int j = 1; j < i; j++)
				cout << j << " ";
			for (int j = i + 1; j <= n; j++)
				cout << j << " ";
			cout << endl;
			exit(0);
		}
	for (int i = 1; i <= n; i++)
	{
		if (m[sum ^ f[i]])
		{
			cout << n - 2 << endl;
			for (int j = 1; j < m[sum ^ f[i]]; j++)
				cout << j << " ";
			for (int j = m[sum ^ f[i]] + 1; j < i; j++)
				cout << j << " ";
			for (int j = i + 1; j <= n; j++)
				cout << j << " ";
			cout << endl;
			exit(0);
		}
		m[f[i]] = i;
	}
	cout << n - 3 << endl;
	cout << 1 << " ";
	for (int i = 3; i < n / 2; i++)
		cout << i << " ";
	for (int i = n / 2 + 1; i < n; i++)
		cout << i << " ";
	cout << endl;
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

[Codeforces 题面传送门](https://codeforces.ml/contest/1622/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1622F)

一道名副其实的 educational 的 hot tea。

首先看到我们将问题进行初步转化：我们先求出 $\prod\limits_{i=1}^n(i!)$ 的质因数分解形式中，所有出现次数为奇数的质数，这个异常好办——因为 $\prod\limits_{i=1}^n(i!)=\prod\limits_{i=1}^ni^{n-i+1}$，因此 $n-1,n-3,\cdots,n\bmod 2+1$ 在式子中的次数都是偶数我们可以把它们都踢掉，故 $\prod\limits_{i=1}^ni!$ 质因数分解形式中，出现次数为奇数的质因子集合，就等于 $n!!$ 中，出现次数为奇数的质因子的集合，预处理每个数的最小质因子后即可 $n\log n$ 地分解。

于是问题转化为，求一个长度最小的序列 $\{a_m\}$，满足 $1\le a_i\le n$，且 $\prod\limits_{i=1}^ma_i!$ 的质因数分解形式中，出现次数为奇数的质因子的集合等于 $n!!$ 出现次数为奇数的质因子集合。到这里，我们不妨来发觉下性质：如果 $n$ 是偶数，那么 $n!!=2^{n/2}·(\dfrac{n}{2})!$，前者将质数模 $2$ 后要么剩个 $2^0$，要么剩个 $2^1$，因此 $n!!$ 质因子为奇数的集合要么与 $(\dfrac{n}{2})!$ 相同，要么与 $2·(\dfrac{n}{2})!$ 相同；同理，如果 $n$ 是奇数，那么 $n!!=\dfrac{n!}{(n-1)!!}=\dfrac{n!}{2^{(n-1)/2}·(\frac{n-1}{2})!}$，因此 对于奇数 $n$，$n!!$ 出现次数为奇数的集合要么与 $n!·(\dfrac{n-1}{2})!$ 相同，要么与 $2·n!·(\dfrac{n-1}{2})!$ 相同。

也就是说符合条件的长度最小的序列 ${a_m}$ 长度不超过 $3$。故我们考虑对 $0,1,2$ 的情况分别求解，$0$ 的情况直接特判掉即可，$1$ 的情况就考虑哈希，我们给每个质因子赋上一个 $[1,2^{64}-1]$​ 的随机权值，然后定义一个集合的权值为其中所有元素权值的 XOR，这样我们预处理出 $1!,2!,\cdots,n!$​ 的权值后，检验是否存在某个 $i!$ 的权值等于 $n!!$ 的权值，$2$ 的情况也同理，map 预处理下每个权值出现的位置即可。

时间复杂度 $n\log n$。

```cpp
mt19937 rng(20060729 ^ chrono :: steady_clock :: now().time_since_epoch().count());
template<typename T> T rand(T l, T r) {return uniform_int_distribution<T>(l, r)(rng);}
const int MAXN = 1e6;
int n, pr[MAXN / 2 + 5], prcnt = 0, vis[MAXN + 5], mnp[MAXN + 5];
int cnt[MAXN + 5], book[MAXN + 5];
u64 v[MAXN + 5], pre[MAXN + 5];
void sieve(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pr[++prcnt] = i, mnp[i] = i;
		for (int j = 1; j <= prcnt && pr[j] * i <= n; j++) {
			vis[pr[j] * i] = 1; mnp[pr[j] * i] = pr[j];
			if (i % pr[j] == 0) break;
		}
	}
}
int main() {
	scanf("%d", &n); sieve(MAXN);
	for (int i = 1; i <= n; i++) if ((n - i + 1) & 1) {
		int tmp = i;
		while (tmp ^ 1) {
			int p = mnp[tmp];
			while (tmp % p == 0) tmp /= p, cnt[p] ^= 1;
		}
	}
	bool flg = 1;
	for (int i = 1; i <= n; i++) flg &= (!cnt[i]);
	if (flg) {
		printf("%d\n", n);
		for (int i = 1; i <= n; i++) printf("%d%c", i, " \n"[i == n]);
		return 0;
	}
	for (int i = 1; i <= n; i++) v[i] = rand(1ull, ULLONG_MAX);
	u64 hs = 0;
	for (int i = 1; i <= n; i++) if (cnt[i]) hs ^= v[i];
	for (int i = 1; i <= n; i++) {
		pre[i] = pre[i - 1]; int tmp = i;
		while (tmp ^ 1) {
			int p = mnp[tmp];
			while (tmp % p == 0) tmp /= p, pre[i] ^= v[p];
		}
	}
	for (int i = 1; i <= n; i++) if (pre[i] == hs) {
		printf("%d\n", n - 1);
		for (int j = 1; j <= n; j++) if (j != i) printf("%d ", j);
		return 0;
	}
	unordered_map<u64, int> pos;
	for (int i = 1; i <= n; i++) {
		if (pos[pre[i] ^ hs]) {
			int X = i, Y = pos[pre[i] ^ hs];
			printf("%d\n", n - 2);
			for (int i = 1; i <= n; i++) if (i != X && i != Y)
				printf("%d ", i);
			return 0;
		}
		pos[pre[i]] = i;
	}
	printf("%d\n", n - 3);
	for (int i = 1; i <= n; i++) if (i != 2 && i != (n >> 1) && i != n)
		printf("%d ", i);
	return 0;
}
```



---

