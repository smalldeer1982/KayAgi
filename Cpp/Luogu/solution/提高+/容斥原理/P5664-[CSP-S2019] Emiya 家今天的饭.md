# [CSP-S2019] Emiya 家今天的饭

## 题目描述

Emiya 是个擅长做菜的高中生，他共掌握 $n$ 种**烹饪方法**，且会使用 $m$ 种**主要食材**做菜。为了方便叙述，我们对烹饪方法从 $1 \sim n$ 编号，对主要食材从 $1 \sim m$ 编号。

Emiya 做的每道菜都将使用**恰好一种**烹饪方法与**恰好一种**主要食材。更具体地，Emiya 会做 $a_{i,j}$ 道不同的使用烹饪方法 $i$ 和主要食材 $j$ 的菜（$1 \leq i \leq n$、$1 \leq j \leq m$），这也意味着 Emiya 总共会做 $\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{m} a_{i,j}$ 道不同的菜。

Emiya 今天要准备一桌饭招待 Yazid 和 Rin 这对好朋友，然而三个人对菜的搭配有不同的要求，更具体地，对于一种包含 $k$ 道菜的搭配方案而言：
- Emiya 不会让大家饿肚子，所以将做**至少一道菜**，即 $k \geq 1$
- Rin 希望品尝不同烹饪方法做出的菜，因此她要求每道菜的**烹饪方法互不相同**
- Yazid 不希望品尝太多同一食材做出的菜，因此他要求每种**主要食材**至多在**一半**的菜（即 $\lfloor \frac{k}{2} \rfloor$ 道菜）中被使用

这里的 $\lfloor x \rfloor$ 为下取整函数，表示不超过 $x$ 的最大整数。

这些要求难不倒 Emiya，但他想知道共有多少种不同的符合要求的搭配方案。两种方案不同，当且仅当存在至少一道菜在一种方案中出现，而不在另一种方案中出现。

Emiya 找到了你，请你帮他计算，你只需要告诉他符合所有要求的搭配方案数对质数 $998,244,353$ 取模的结果。

## 说明/提示

【样例 1 解释】

由于在这个样例中，对于每组 $i, j$，Emiya 都最多只会做一道菜，因此我们直接通过给出烹饪方法、主要食材的编号来描述一道菜。

符合要求的方案包括：
- 做一道用烹饪方法 1、主要食材 1 的菜和一道用烹饪方法 2、主要食材 2 的菜
- 做一道用烹饪方法 1、主要食材 1 的菜和一道用烹饪方法 2、主要食材 3 的菜
- 做一道用烹饪方法 1、主要食材 3 的菜和一道用烹饪方法 2、主要食材 2 的菜

因此输出结果为 $3 \bmod 998,244,353 = 3$。 需要注意的是，所有只包含一道菜的方案都是不符合要求的，因为唯一的主要食材在超过一半的菜中出现，这不满足 Yazid 的要求。

【样例 2 解释】

Emiya 必须至少做 2 道菜。

做 2 道菜的符合要求的方案数为 100。

做 3 道菜的符合要求的方案数为 90。

因此符合要求的方案数为 100 + 90 = 190。

【数据范围】

| 测试点编号 | $n=$ | $m=$ | $a_{i,j}<$ | 测试点编号 | $n=$ |$m=$  |$a_{i,j}<$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $2$ | $2$ | $2$ | $7$ | $10$ | $2$ | $10^3$ |
| $2$ | $2$ | $3$ | $2$ | $8$ | $10$| $3$ | $10^3$ |
| $3$ | $5$ | $2$ | $2$ | $9\sim 12$ | $40$ | $2$ | $10^3$ |
| $4$ | $5$ | $3$ | $2$ | $13\sim 16$ | $40$ | $3$  | $10^3$ |
| $5$ | $10$ | $2$ | $2$ | $17\sim 21$ | $40$ | $500$ | $10^3$ |
| $6$ | $10$ | $3$ | $2$ | $22\sim 25$ | $100$ | $2\times 10^3$ | $998244353$ |

对于所有测试点，保证 $1 \leq n \leq 100$，$1 \leq m \leq 2000$，$0 \leq a_{i,j} \lt 998,244,353$。

## 样例 #1

### 输入

```
2 3 
1 0 1
0 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
1 2 3
4 5 0
6 0 0```

### 输出

```
190```

## 样例 #3

### 输入

```
5 5
1 0 0 1 1
0 1 0 1 0
1 1 1 1 0
1 0 1 0 1
0 1 1 0 1```

### 输出

```
742```

# 题解

## 作者：Caro23333 (赞：950)

#### 给管理员的更新说明：这是一篇广受好评的题解，我近日对选手们提到的代码问题作了修订，并不是故意提出重复解法的题解，希望在重新提交审核的过程中可以通过，为更多的选手带来好的帮助，非常感谢！

又来水题解了~

这个题作为d2t1比往年偏难，但完全在可以接受和预见的范围。

首先考虑列的限制，发现若有不合法的列，则必然有且只有一列是不合法的：因为不可能有不同的两列数量都超过总数的一半。

于是发现列的限制容易容斥计算：每行选不超过一个的方案数 - 每行选不超过一个，且某一列选了超过一半的方案数。

那么考虑枚举不合法的一列。假设我们已经枚举了不合法的列为$col$，接下来会发现我们只关心一个数的位置是否在当前列；如果属于在其他列的情况，那么它具体在哪一列对当前列的合法性并无影响，我们并不需要考虑。

接下来设计状态。$f_{i,j,k}$表示对于$col$这一列，前$i$行在$col$列中选了$j$个，在其他列中选了$k$个，那么令$s_i$为第$i$行的总和，则有转移：
$$f_{i,j,k} = f_{i-1,j,k}\ +\ a_{i,col}* f_{i-1,j-1,k}\ +\ (s_i-a_{i,col})* f_{i-1,j,k-1}$$
状态数$O(n^3)$，转移$O(1)$，算上枚举$col$，这一步复杂度是$O(mn^3)$的。统计如下和式的值并对每一列求和即可得到不合法的方案数：
$$\sum_{j>k} f_{n,j,k}$$

接下来考虑计算总方案数：和之前相似，只需设$g_{i,j}$为前$i$行共选了$j$个数的方案数，则有转移：
$$g_{i,j} = g_{i-1,j}\ +\ s_i*g_{i-1,j-1}$$

那么$\sum\limits_{i=1}^n g_{n,i}$就是总方案数，
这一步是$O(n^2)$的。所以现在可以在$O(mn^3)$的总复杂度内完成这题，获得84分。

考虑进一步优化，剪去无用状态：注意到在不合法情况的计算过程中，也就是$f_{i,j,k}$的转移过程中，我们实际上并不关心$j,k$的具体数值，而只关心相对的大小关系；所以我们可以将状态变为$f_{i,j}$，表示前$i$行，当前列的数比其他列的数多了$j$个，则有转移：
$$f_{i,j} = f_{i-1,j}\ +\ a_{i,col}* f_{i-1,j-1}\ +\ (s_i-a_{i,col})* f_{i-1,j+1}$$

转移仍然是$O(1)$的，但总复杂度降为$O(mn^2)$，可以通过此题。

（考试的时候我好像数组开小了？？？）

（沦为和暴力老哥同分）

代码：

```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#define mod 998244353

using namespace std;
typedef long long ll;
const int MAXN = 105, MAXM = 2005;
int n,m,a[MAXN][MAXM],sum[MAXN][MAXM];
ll f[MAXN][MAXN*2],g[MAXN][MAXN];

int main()
{
	cin >> n >> m;
	for(int i = 1; i<=n; i++)
	    for(int j = 1; j<=m; j++)
	    {
	        scanf("%d",&a[i][j]);
	        sum[i][0] = (sum[i][0]+a[i][j])%mod;
		}
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=m; j++)
            sum[i][j] = (sum[i][0]-a[i][j]+mod)%mod;
    ll ans = 0;
    for(int col = 1; col<=m; col++)
    {
        memset(f,0,sizeof(f));
        f[0][n] = 1;
        for(int i = 1; i<=n; i++)
            for(int j = n-i; j<=n+i; j++) 
                f[i][j] = (f[i-1][j]+f[i-1][j-1]*a[i][col]%mod+f[i-1][j+1]*sum[i][col]%mod)%mod;
        for(int j = 1; j<=n; j++)
            ans = (ans+f[n][n+j])%mod;
	}
	g[0][0] = 1;
	for(int i = 1; i<=n; i++)
	    for(int j = 0; j<=n; j++) 
		    g[i][j] = (g[i-1][j]+(j>0?g[i-1][j-1]*sum[i][0]%mod:0))%mod;
    for(int j = 1; j<=n; j++)
	    ans = (ans-g[n][j]+mod)%mod;  
	cout << ans*(mod-1)%mod << endl;
	return 0;
}
```


---

## 作者：TEoS (赞：170)

很不错的一题DP，通过这道题学到了很多。

身为一个对DP一窍不通的蒟蒻，在考场上还挣扎了1h来推式子，居然还有几次几乎推出正解，然而最后还是只能打个32分的暴搜滚粗

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/11901386.html)

------

**题意分析**

给出一个矩阵，要求每行只能选一个节点，每列选的节点不能超过所有选的节点的一半，不能不选，给出每个节点的选择方案数，求总方案数

**思路分析**

可以看出，维护每列已选的节点复杂度太大，不太可行；因此很容易想到，先不考虑每列不超过一半的这个限制，求出总方案数，然后再减去考虑这个限制后不合法的方案数。现在问题就变成，求任意列选的节点超过所有选的节点的一半的方案数之和。

显然，在一个方案中，只可能有一列的节点超过所有选的节点的一半。因此可以想到枚举这个超过限制的列，然后对于这个列进行DP求解。

**具体实现**

设$f_{i,j,k}$表示前$i$行选$j$个节点，当前枚举到的列选$k$个节点的方案数。对于每个列，复杂度为$O(n^3)$，总的复杂度为$O(mn^3)$，可以得到84分的高分。

想得到满分还需要进一步优化。考虑将某两个状态合并。观察状态，实际上我们想知道的只是$j,k$的大小关系，对于具体的值并不关心，考虑将它们合并到一维。

考虑我们需要的限制条件$k>\left \lfloor \frac{j}{2} \right \rfloor$，变形一下可以得到$2k+n-j>n$。观察这个式子，可以发现，$n-j$就是这$n$行里没有选的行数。然后一个奇妙的想法就出来了，对于每个节点，选它时当做该列选了两次，而对于某一行不选时，当做所有列选了一次，最终要找的就是当前列被选超过$n$次的方案。这样就成功地优化掉了第二维。

给一下状态转移方程：

```c++
f[j][k]=(f[j][k]+f[j-1][k]*(cnt[j]-w[j][i]))%P;//不选当前列
f[j][k+1]=(f[j][k+1]+f[j-1][k])%P;//不选当前行
f[j][k+2]=(f[j][k+2]+f[j-1][k]*w[j][i])%P;//选当前行当前列对应的节点
```

注意取模时出现负数的情况，记得开long long。

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N=200,M=3000,P=998244353;//FFT（雾
int n,m;
ll ans=1;
ll cnt[N],w[N][M],f[N][M];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			scanf("%lld",&w[i][j]),cnt[i]=(cnt[i]+w[i][j])%P;
		ans=(ans*(cnt[i]+1))%P;//计算全部答案
	}
	ans=(ans+P-1)%P;//减去全部不选的情况
	for(int i=1;i<=m;i++)
	{
		memset(f,0,sizeof(f));
		f[0][0]=1;//DP初值
		for(int j=1;j<=n;j++)
			for(int k=0;k<=2*(j-1);k++)
			{
				f[j][k]=(f[j][k]+f[j-1][k]*(cnt[j]-w[j][i]))%P;
				f[j][k+1]=(f[j][k+1]+f[j-1][k])%P;
				f[j][k+2]=(f[j][k+2]+f[j-1][k]*w[j][i])%P;
			}
		for(int j=n+1;j<=2*n;j++)
			ans=(ans+P-f[n][j])%P;//减去当前枚举到的不合法方案
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：KSkun (赞：121)

本文同步发布在我的博客：[[CSP-S2 2019]Emiya 家今天的饭 题解 | KSkun's Blog](https://ksmeow.moe/meal-csps219-sol/)，欢迎来逛~

广告：CSP-J/S2 2019 志愿者的幕后故事：[CSP-JS2 2019 游记 | KSkun's Blog](https://ksmeow.moe/csp-js2-2019/)

## 题意简述

一共有 $n$ 种烹饪方法和 $m$ 种主要食材，一道菜仅对应一种烹饪方法和一种主要食材。使用第 $i$ 种烹饪方法和第 $j$ 种主要食材，Emiya 可以做出 $a_{i,j}$ 道不同的菜。

求满足以下条件的菜的集合数：

- 非空；
- 每道菜的烹饪方法互不相同；
- 集合中每种主要食材的菜数不超过集合大小的一半（向下取整）。

## 题解

居然在 NOIP 级别的比赛中见到了计数 DP，很难想象以后的 NOIP 对于数学知识的考察会变成什么样。那个只有一道很水的数论/组合签到题的时代已经结束了。

首先本题是组合数学/计数类型的问题，这类题通常有两种解决方式：推公式或 DP，本题中可以采用 DP 求解。

接下来考虑如何设计 DP 状态。如果正面解决，就必须对每种主要食材的出现次数做小于集合大小的一半的限制，这需要记录下每种主要食材的出现次数，不是很可行。因此可以采用正难则反的策略，容易发现不合法的情况中只会有一种主要食材超过集合大小的一半，处理这个限制仅需记下一种主要食材的出现次数，问题变得简单了。

### 所有方案数

首先从一个较好解决的问题入手，由于答案=所有方案数-不合法方案数，我们需要知道所有的方案有多少种。

定义 $g(i, j)$ 表示前 $i$ 种烹饪方式中，每种最多选出一道菜的情况下，当前集合中有 $j$ 道菜的方案数，则决策为当前处理的第 $i$ 种烹饪方式是否选出一道菜，记 $s(i)$ 代表第 $i$ 种烹饪方式一共可做出的菜数，即 $s(i) = \sum\limits_{j=1}^m a_{i, j}$ 转移方程如下：

$$ g(i,j) = \underset{\text{choose nothing}}{g(i-1, j)} + \underset{\text{choose 1 dish from } s(i) \text{ dishes in total}}{g(i-1,j-1) \cdot s(i)} $$

初始值为 $g(0, 0)=1$（什么都没做，有 $1$ 种方案），所有的方案数为 $\sum\limits_{i=1}^n g(n, i)$，由于集合不能为空，$g(n, 0)$ 的值不能加入方案数中。

这一部分的复杂度为 $O(n^2)$。

### 不合法方案数

由于不合法的方案中，只有一种主要食材的数量会超过集合大小的一半，可以枚举超限的主要食材，而只记录下其他食材的数量之和，不分开记录。

定义 $f(in, j, k)$ 表示考虑前 $in$ 种烹饪方式，当前要超限的主要食材的出现次数为 $j$，其他主要食材的出现次数之和为 $k$。决策有三种：当前考虑的第 $in$ 种烹饪方式不选、选要超限的那种主要食材的菜或选其他主要食材的菜，记 $s(i)$ 代表第 $i$ 种烹饪方式一共可做出的菜数，且当前要超限的主要食材编号为 $im$，有转移方程：

$$ f(in, j, k) = \underset{\text{choose nothing}}{f(in-1, j, k)} + \underset{\text{choose out-of-range material}}{f(in-1, j-1,k) \cdot a_{in, im}} + \underset{\text{choose other materials}}{f(in-1,j,k-1) \cdot [s(in)-a_{in,im}]} $$

将上述 DP 在以每一种主要食材为超限食材的情况下都计算一遍，对于 $im$ 这种食材为超限食材的情况，不合法的方案数为 $\sum\limits_{k < j} f(n, j, k)$。将这些不合法的方案数加起来就获得了总的不合法方案数了。但这种方式的复杂度是 $O(n^3m)$ 的，无法通过本题。

考虑优化上述方法，将不合法的方案满足的条件 $k < j$ 移项，得到表达式 $j-k > 0$，其实判断一个方案是否合法，仅需要判断 $j-k$ 的符号即可，我们考虑将之前状态中的 $j$ 和 $k$ 两个维度变为一维 $j-k$ 的值，这将会减少一层循环，使复杂度降至 $O(n^2m)$。

接下来考虑上面的改变会对转移方程造成什么样的影响，事实上，仅需将方程中的两维改为一维即可：

$$ f(in, j) = \underset{\text{choose nothing}}{f(in-1, j)} + \underset{\text{choose out-of-range material}}{f(in-1, j-1) \cdot a_{in, im}} + \underset{\text{choose other materials}}{f(in-1,j+1) \cdot [s(in)-a_{in,im}]} $$

由于 $j-k$ 的值可以为负数，而数组下标不能为负数，因此下标应当处理为 $j-k+n$，以让下标的值非负。DP 的初始值为 $f(0, 0)=1$（什么都没做，其中第二维下标应处理为 $n$），对于每一种超限食材的情况，不合法的方案数为$\sum\limits_{j=1}^n f(n, j)$（第二维下标应处理为 $j + n$）。

最后，将所有方案数减去不合法方案数就得到了最终答案，总复杂度为 $O(n^2m)$。

## 代码
```cpp
// Code by KSkun, 2019/12
#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>
#include <utility>

typedef long long LL;
typedef std::pair<int, int> PII;

inline char fgc() {
	static char buf[100000], * p1 = buf, * p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
		? EOF : *p1++;
}

inline LL readint() {
	LL res = 0, neg = 1; char c = fgc();
	for(; !isdigit(c); c = fgc()) if(c == '-') neg = -1;
	for(; isdigit(c); c = fgc()) res = res * 10 + c - '0';
	return res * neg;
}

inline char readsingle() {
	char c;
	while(!isgraph(c = fgc())) {}
	return c;
}

const int MAXN = 105, MAXM = 2005;
const int MO = 998244353;

int n, m;
LL a[MAXN][MAXM], s[MAXN], f[MAXN][MAXN << 1], g[MAXN][MAXN];

inline LL A(int in, int im) { // 让方程不那么长的简化
	return (s[in] - a[in][im] + MO) % MO;
}

int main() {
	n = readint(); m = readint();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			a[i][j] = readint();
			s[i] = (s[i] + a[i][j]) % MO;
		}
	}

	LL sum1 = 0, sum2 = 0;
	for (int im = 1; im <= m; im++) {
		memset(f, 0, sizeof(f));
		f[0][n] = 1;
		for (int in = 1; in <= n; in++) {
			for (int j = n - in; j <= n + in; j++) {
				f[in][j] = (f[in - 1][j] + f[in - 1][j - 1] * a[in][im] % MO + f[in - 1][j + 1] * A(in, im) % MO) % MO;
			}
		}
		for (int i = 1; i <= n; i++) {
			sum1 = (sum1 + f[n][n + i]) % MO;
		}
	}
	g[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			g[i][j] = g[i - 1][j];
			if (j > 0) g[i][j] = (g[i][j] + g[i - 1][j - 1] * s[i] % MO) % MO;
		}
	}
	for (int i = 1; i <= n; i++) {
		sum2 = (sum2 + g[n][i]) % MO;
 	}
	printf("%lld", (sum2 - sum1 + MO) % MO);
	return 0;
}
```

---

## 作者：xht (赞：31)

首先容斥，显然答案为总方案数，减掉有一个 $\ge \lfloor \frac n2 \rfloor$ 的方案数，减掉有两个 $\ge \lfloor \frac n2 \rfloor$ 的方案数。

然后就发现不可能出现多于一个 $\ge \lfloor \frac n2 \rfloor$。

那么可以枚举多于 $\ge \lfloor \frac n2 \rfloor$ 的那个，然后 dp。

设 $f[i][j][k]$ 为考虑到第 $i$ 种，要求多于的那个选了 $j$ 个，其他的选了 $k$ 个的方案数。

时间复杂度 $\mathcal O(n^3m)$。

考虑优化，我们并不关心 $j$ 和 $k$ 的具体值，而是只需要知道它们的差即可。

那么设 $f[i][j]$ 为考虑到第 $i$ 种，要求多于的那个比其他的多选了 $j$ 个的方案数。

时间复杂度 $\mathcal O(n^2m)$。

```cpp
const int N = 107, M = 2e3 + 7;
int n, m;
modint a[N][M], s[N], f[N][N<<1], ans = 1;

inline modint calc(int x) {
	f[0][n+3] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = -i; j <= i; j++) {
			int k = j + n + 3;
			f[i][k] = 0;
			f[i][k] += f[i-1][k-1] * a[i][x];
			f[i][k] += f[i-1][k];
			f[i][k] += f[i-1][k+1] * (s[i] - a[i][x]);
		}
	modint ret = 0;
	for (int i = 1; i <= n; i++) ret += f[n][i+n+3];
	return ret;
}

int main() {
	rd(n), rd(m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			rd(a[i][j]), s[i] += a[i][j];
		ans *= s[i] + 1;
	}
	ans -= 1;
	for (int i = 1; i <= m; i++) ans -= calc(i);
	print(ans);
	return 0;
}
```

---

## 作者：kkkstra (赞：6)

[传送门](https://www.luogu.org/problem/P5664)

## Solution

### 算法1 32pts

爆搜，复杂度$O((m+1)^n)$

### 算法2 84pts

裸的dp，复杂度$O(n^3m)$

首先有一个显然的性质要知道：

最多只有一种主要食材出现在超过一半的主要食材里。

接下来考虑如果只有前两个限制条件的情况，那么答案就是

$$\Pi_{i=1}^{n} (sum_i+1) - 1$$

其中$sum_i = \sum \limits_{j=1}^m a_{i,j}$，$+1$是因为对于每一行只有选一道菜或者不选这些选择，$-1$是因为要去除一道菜都不选的情况。

对于第3个限制条件，发现直接做不太好做，考虑容斥，即用总方案数，也就是上面的式子，减去不合法的方案数。

由最开始的那个性质可以得到一个做法：

枚举不合法的那一种主要食材，然后进行$dp$。发现我们并不需要知道每一种主要食材具体用在了多少道菜上，只需要知道当前枚举的食材用在了多少道菜，其它的并不影响方案。那么设$f_{i,j,k}$表示前$i$中烹饪方式，选了$j$道菜，其中$k$道的主要食材是枚举的不合法食材。转移分三种情况：令$s$表示当前枚举的不合法食材，

1. 不在这一种烹饪方式中进行选择：$f_{i,j,k}=f_{i-1,j,k}$

2. 在这种烹饪方式中选择了合法的食材：$f_{i,j,k}=(sum_i-a_{i,s}) \times f_{i,j-1,k}$

3. 在这种烹饪方式中选择了不合法的食材：$f_{i,j,k}=a_{i,s}\times f_{i,j-1,k-1}$

那么不合法的方案数就是

$$\sum \limits_{k\ge \lfloor \frac{j}{2} \rfloor} f_{n,j,k}$$

**code**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 998244353;
const int _ = 100 + 10;
const int __ = 2000 + 10;
int n, m, A[_][__];
ll sum[_], f[_][_][_], tmp, ans = 1;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &A[i][j]);
			sum[i] = (sum[i] + A[i][j]) % mod;
		}
		ans = ans * (sum[i] + 1) % mod;
	}
	ans = (ans - 1 + mod) % mod;

	for (int l = 1; l <= m; ++l) {
		memset(f, 0, sizeof(f));
		f[0][0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			f[i][0][0] = 1;
			for (int j = 1; j <= i; ++j) {
				for (int k = 0; k <= j; ++k) {
					f[i][j][k] = f[i - 1][j][k];
					if (k > 0) f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k - 1] * A[i][l] % mod) % mod;
					f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k] * (sum[i] - A[i][l]) % mod) % mod;
					if (i == n && k >= j / 2 + 1) tmp = (tmp + f[i][j][k]) % mod;
				}
			}
		}
	}

	ans = (ans - tmp + mod) % mod;
	printf("%lld\n", ans);
	return 0;
}
```

### 算法三 100pts

考虑如何对算法二的$dp$进行优化，减少不必要的状态。对限制三进行转化，限制三即为

$$x\le \lfloor \frac{k}{2} \rfloor$$

$$2x \le k$$

$$2x - k \le 0$$

$$x-(k-x)\le 0$$

发现并不需要关心使用了食材的菜的具体数量，只需要关心合法与不合法的菜的差值即可，即这个差值与原来差值相同的状态的集合是对应的，那么我们就可以以此为状态进行dp，转移与上面是类似的。
唯一要注意的一点是可能出现负数，要加上一个偏移量$n$

1. 不在这一种烹饪方式中进行选择：$f_{i,j}=f_{i-1,j}$

2. 在这种烹饪方式中选择了合法的食材：$f_{i,j}=(sum_i-a_{i,s}) \times f_{i,j+1}$

3. 在这种烹饪方式中选择了不合法的食材：$f_{i,j}=a_{i,s}\times f_{i,j-1}$

**code**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 998244353;
const int _ = 100 + 10;
const int __ = 2000 + 10;
int n, m, A[_][__];
ll sum[_], f[_][_ << 1], tmp, ans = 1;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &A[i][j]);
			sum[i] = (sum[i] + A[i][j]) % mod;
		}
		ans = ans * (sum[i] + 1) % mod;
	}
	ans = (ans - 1 + mod) % mod;

	for (int k = 1; k <= m; ++k) {
		memset(f, 0, sizeof(f));
		f[0][n] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = -i + n; j <= i + n; ++j) {
				f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * A[i][k] % mod + f[i - 1][j + 1] * (sum[i] - A[i][k]) % mod) % mod;
				if (i == n && j > n) tmp = (tmp + f[i][j]) % mod;
			}
		}
	}

	ans = (ans - tmp + mod) % mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Ydoc770 (赞：2)

## Luogu P5664 Emiya 家今天的饭 [Link](https://www.luogu.com.cn/problem/P5664)

### 简要题意：

给定 $n\le10^2,m\le2\times10^3$ 和 $n\times m$ 的矩阵，横行纵列分别表示不同的烹饪方法和主要食材，矩阵上每个数表示会做的不同主菜。对于不同的做菜方案有以下限制：

- 每个方案至少有一道菜；
- 每个烹饪方法互不相同；
- 每个菜品数量为 $k$ 的方案每种主要食材不超过 $\lfloor\frac k2\rfloor$ 个。

求方案数，对 $998244353$ 取模。

### 思路：

先理解题意，菜品数 $k$ 应该不超过 $n$ 且不小于 $2$。对于每个格子的菜，选择了那么同一行的其它菜就不能选了，所以转移时同一行的菜属于同一个过程，根据加法原理可以加起来作为一个整体记为 $sum_i$。发现第三个限制很棘手，菜的数量要分开考虑，每一列的状态也要分开考虑，这样的时间和空间是难以接受的。考虑容斥，拿所有的方案数减去不合法的方案数。

满足限制一二的所有方案：对于每一行的菜品，包括不取一共有 $sum_i+1$ 种情况，根据乘法原理有 $\prod_{i=1}^n(sum_i+1)-1$，其中减去的 $1$ 的是每一行都不取的情况（第一条限制）。

不合法方案：由于要违反第三限制，我们需要某些列选择的菜品数大于 $\lfloor\frac k2\rfloor$。然而这样的列如果存在那么有且仅会只有这一列，因为其它列的菜品数之和小于 $\lfloor\frac k2\rfloor$。不妨枚举单独的一列 $t$ 选择的菜品数为 $k'$。为了转移的方便，我们考虑前 $i$ 行其他列选 $j$ 个。那么我考虑对于 $f_{i,j,k'}$ 的转移方程：首先，对于在 $i$ 行中选一种菜，如果选第 $t$ 列，产生的方案数为 $f_{i-1,j,k'-1}\times a_{i,t}$，接着，对于不选 $t$ 列的情况，产生的方案数为 $f_{i-1,j-1,k'}\times(sum_i-a_{i,t})$，最后，如果不在第 $i$ 行选菜，继承先前的方案数 $f_{i-1,j,k'}$。即有转移方程：

$$
f_{i,j,k'}=f_{i-1,j,k'-1}\times a_{i,t}+f_{i-1,j-1,k'}\times(sum_i-a_{i,t})+f_{i-1,j,k'}
$$

实现时要枚举 $t,i,j,k'$，最后在总方案数中把 $k'>j$ 的 $f_{i,j,k'}$ 减掉就是合法的方案数。

复杂度达到 $O(mn^3)$。这对于大部分测试点来说足够，但是无法通过全部数据。

### 优化：

考虑到 $j,k'$ 是我们为了找到不合法方案数的指标，实际上只与它们的相对大小有关，而与其具体的值无关。不妨令 $j'=k'-j$，再将值域整体向右平移 $n$ 处理掉负指标。一一对应上文的三种情况，产生方案数分别有 $f_{i-1,j'-1}\times a_{i,t}$、$f_{i-1,j'+1}\times(sum_i-a_{i,t})$、$f_{i-1,j'}$。即有新的转移方程：

$$
f_{i,j'}=f_{i-1,j'-1}\times a_{i,t}+f_{i-1,j'+1}\times(sum_i-a_{i,t})+f_{i-1,j'}
$$

现在实现时只需要枚举 $t,i,j'$ 三个指标，总方案数减去 $1\le j'\le n$ 的 $f_{i,j'+n}$ 即为答案。复杂度 $O(mn^2)$。可以通过所有数据。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int maxn = 1e2 + 10, maxm = 2e3 + 10, mo = 998244353;
int n, m, a[maxn][maxm];
ll s = 1, sum[maxn], f[maxn][maxn << 1];

int main() {
	ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> a[i][j]; 
			(sum[i] += a[i][j]) %= mo;
		}
		s = 1ll * s * (sum[i] + 1) % mo;
	}
	(s += mo - 1) %= mo;
	
	for(int t = 1; t <= m; t++) {
		f[0][n] = 1;
		for(int i = 1; i <= n; i++) {
			for(int j = n - i; j <= n + i; j++) {
				f[i][j] = f[i - 1][j];
				(f[i][j] += 1ll * f[i - 1][j - 1] * a[i][t] % mo) %= mo;
				(f[i][j] += 1ll * f[i - 1][j + 1] * (sum[i] - a[i][t]) % mo) %= mo;
			}
		}
		
		for(int j = 1; j <= n; j++) {
			(s += mo - f[n][j + n]) %= mo;
		}
		memset(f, 0, sizeof f);
	}
	
	cout << s;
}

---

## 作者：P2441M (赞：2)

## 题解
[原题链接](https://www.luogu.com.cn/problem/P5664)

题目差不多就是在网格里选位置的方案数。

这题主要的难度在于第三个要求是难以刻画的。所以**正难则反**，我们考虑容斥，用总方案数减去不合法的方案数。不合法的方案意味着有且仅有一列被选择的数量超过了总数量的一半。

令 $s_i=\sum_{j=1}^{m}{a_{i,j}}$，于是总方案数即为
$$
tot=\prod_{i=1}^{n}(s_i+1)-1
$$

容易想到 DP 求不合法的方案数。我们枚举被选择的数量超过了总数量一半的那一列 $c$，然后令 $f_{i,j,k}$ 表示考虑前 $i$ 行，总共选择了 $j$ 个位置，第 $c$ 列选择了 $k$ 个位置的方案数。转移时考虑当前行不选、选第 $c$ 列之外的位置或选第 $c$ 列的位置，即可得到转移方程：
$$
f_{i,j,k}=f_{i-1,j,k}+f_{i-1,j-1,k}\times(s_i-a_{i,c})+f_{i-1,j-1,k-1}\times a_{i,c}
$$

转移时注意 $j$ 和 $k$ 从 0 开始枚举。最终答案就是
$$
ans=tot-\sum_{j=1}^{n}\sum_{k=\lfloor\frac{j}{2}\rfloor +1}^{j}f_{n,j,k}
$$

时间复杂度为 $O(mn^3)$。可以拿下 84 分的高分。

考虑进一步优化。这一步是比较巧妙的：我们注意到我们只关心 $j$ 和 $k$ 的相对大小关系，并且在计算最终答案时
$$
k>\lfloor\frac{j}{2}\rfloor
\Leftrightarrow 2k-j>0
$$
所以我们无需枚举 $j$ 和 $k$ 的具体值，而是转而枚举差值 $d=2k-j$ 即可，状态转移方程只需做轻微改动：
$$
f_{i,d}=f_{i-1,d}+f_{i-1,d+1}\times(s_i-a_{i,c})+f_{i-1,d-1}\times a_{i,c}
$$

其中 $-i\leq d\leq i$。计算最终答案时减去满足 $1\leq d\leq n$ 的对应 DP 值即可。实际实现时记得给 $d$ 加上偏移量。

时间复杂度少了一个 $n$，为 $O(mn^2)$，可以通过本题。

## 代码
```cpp
#include <iostream>
#include <cstring>

using namespace std;

#define add_mod(x, v) (x) = ((ll)(x) + (v)) % MOD
#define sub_mod(x, v) (x) = (((ll)(x) - (v)) % MOD + MOD) % MOD
#define mul_mod(x, v) (x) = (1ll * (x) * (v)) % MOD
typedef long long ll;
typedef pair<int, int> pii;
const int MOD = 998244353;
const int MAX_N = 105, MAX_M = 2e3 + 5;

int n, m, a[MAX_N][MAX_M];
ll s[MAX_N], tot = 1, f[MAX_N][MAX_N << 1];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            add_mod(s[i], a[i][j]);
        }
        mul_mod(tot, s[i] + 1);
    }
    sub_mod(tot, 1);
    for (int c = 1; c <= m; ++c) {
        memset(f, 0, sizeof(f));
        f[0][n] = 1;
        for (int i = 1; i <= n; ++i)
            for (int d = -i; d <= i; ++d) {
                add_mod(f[i][d + n], f[i - 1][d + n]);
                add_mod(f[i][d + n], f[i - 1][d - 1 + n] * a[i][c] % MOD);
                add_mod(f[i][d + n], f[i - 1][d + 1 + n] * (s[i] - a[i][c]) % MOD);
            }
        for (int d = 1; d <= n; ++d) sub_mod(tot, f[n][d + n]);
    }
    cout << tot << '\n';
    return 0;
}
```

---

## 作者：emmoy (赞：2)

## 题目大意
给你一个 $n\times m$ 的矩阵 $a$，$a_{i,j}$ 表示在第 $i$ 种烹饪方式下用第 $j$ 种原料能做出 $a_{i,j}$ 道菜，然后给你三个条件。

设 Emiya 会做 $k$ 道菜。

- 会做**至少一道菜**，即 $k \geqslant 1$。
- 每道菜的**烹饪方法互不相同**。
- 每种**主要食材**至多在**一半**的菜（即 $\lfloor \frac{k}{2} \rfloor$ 道菜）中被使用。

求出方案数对 $998,244,353$ 取模的结果。

## 解题思路
首先分析条件。

- 会做**至少一道菜**。

这个没啥好说的。

- 每道菜的**烹饪方法互不相同**。

即每行只能选一个菜。

- 每种**主要食材**至多在**一半**的菜中被使用。

即每一列选的菜的个数不超过一半的菜。

这是本题的重点。

我们可以考虑容斥，用总方案数减去任意一列选的菜数大于总菜数的一半的方案数就是答案了，接下来分开考虑。
### 总方案数
设 $$sum_i=\sum^m_{j=1}a_{i,j}$$。

因为每一行只能选一个或不选，所以第 $i$ 行的方案数为 $sum_i+1$，但是必须至少做一道菜，所以 $$ans=(\prod^{n}_{i=1}sum_i)-1$$。

```cpp
long long o=1;
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      cin>>a[i][j];
      sum[i]=(sum[i]+a[i][j])%mod;
    }
    o=o*(sum[i]+1)%mod;
}
o=(o-1+mod)%mod;
```
### 任意一列选的菜数大于总菜数的一半的方案数

有点绕。

设 $k$ 为烹饪的的总菜数。

如果有一个原料选的菜数大于 $\lfloor\frac{k}{2}\rfloor$，那么其他的菜便不可能大于 $\lfloor\frac{k}{2}\rfloor$。

所以我们可以枚举是哪一个原料做的菜大于 $\lfloor\frac{k}{2}\rfloor$ 了。

我们发现我们只关心这个原料做的菜是否大于 $\lfloor\frac{k}{2}\rfloor$，而不关心到底做了多少个。

所以考虑差值 dp，对于食材 $c$ ，设 $f_{i,j}$ 表示考虑了前 $i$ 个烹饪方法，第 $c$ 个食材做了多少个菜与其他食材做了多少个菜的差为 $j$ 的方案数。

由于第 $c$ 个食材的菜数大于 $\lfloor\frac{k}{2}\rfloor$，所以如果 $j>0$，那么就代表第 $c$ 个食材的菜数大于 $\lfloor\frac{k}{2}\rfloor$ 了。~~（感性理解）~~

考虑怎么从 $i-1$ 转移到 $i$。

首先如果第 $i$ 种烹饪方式不选，那么 $j$ 不变，就有 $f_{i-1,j}\Rightarrow f_{i,j}$。

如果选了第 $c$ 种原材料，那么 $j$ 就会加一，但是你就算选第 $c$ 种原材料也有 $a_{i,c}$ 种选法，于是有 $f_{i-1,j-1}\times a_{i,c}\Rightarrow f_{i,j}$。

如果没选第 $c$ 种原材料，那么 $j$ 就会减一，会有 $sum_i-a_{i,c}$ 种选法，于是有 $f_{i-1,j+1}\times (sum_i-a_{i,c})\Rightarrow f_{i,j}$。

所以转移方程为：
$$
f_{i,j}=f_{i-1,j}+f_{i-1,j-1}\times a_{i,c}+f_{i-1,j+1}\times (sum_i-a_{i,c})
$$

但是又由于 $j$ 有可能是负数，所以我们整体加上 $n$ 就不会数组越界了。

### code

```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
long long n,m,ans;
long long f[101][301];
long long sum[101];
long long g[201][201];
long long a[201][2001];
int main()
{
	cin>>n>>m;
	long long o=1;//总方案数
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			sum[i]=(sum[i]+a[i][j])%mod;
		}
		o=o*(sum[i]+1)%mod;
	}
	o=(o-1+mod)%mod;
	for(int ch=1;ch<=m;ch++)
	{
		memset(f,0,sizeof(f));//每一个原材料单独求
		f[0][n]=1;//全体加n
		for(int i=1;i<=n;i++)
		{
			for(int j=n-i;j<=n+i;j++)//在i时最少会到n-i,最多会到n+i
			{
				f[i][j]=(f[i-1][j]+f[i-1][j-1]*a[i][ch]%mod+f[i-1][j+1]*(sum[i]+mod-a[i][ch])%mod)%mod;
			}
		}
		for(int i=1;i<=n;i++)//统计答案
		{
			ans=(ans+f[n][i+n])%mod;
		}
	}
	cout<<(o-ans+mod)%mod;//容斥
	return 0;
}
```

---

## 作者：Michael_114 (赞：2)

这道题很有难度，~~本人卡了3天才做出来~~。

如果只有第一个和第二个限制，怎么做？在每一个烹饪方法中，选择出至多一个菜，也可以不选。因为这些选择是独立的，所以可以用乘法原理叠加。

第 $i$ 个烹饪方法总共可以得到 $\sum_{j = 1}^{m} a_{i,j}$ 个物品，由于可以不选，对乘积贡献为 $1 +\sum_{j = 1}^{m} a_{i,j}$ 。对所有 $i$ 相乘得到 $\prod_{i=1}^n (1 +\sum_{j = 1}^{m} a_{i,j}) $ 。但如果所有烹饪方法都不选，就违反了限制 $1$ ，因此答案需要在此基础上减一，即 $\prod_{i=1}^n (1 +\sum_{j = 1}^{m} a_{i,j})-1$ 。将这些方案设为全集，那么违反限制 $3$ 的方案与满足限制 $3$ 的方案互为补集。要求解后者，只需求出前者即可。

接下来，去除违反限制 $3$ 的方案。发现最多有一个食材出现次数大于 $\lfloor \frac{k}{2} \rfloor$ ，否则菜肴的总数至少为 $(\lfloor \frac{k}{2} \rfloor+1) \times 2 > k$ ，矛盾。于是，可以直接枚举哪个食材被用大于 $\lfloor \frac{k}{2} \rfloor$ 次。考虑动态规划，令该食材为 $x$ ， $dp_{i,k,c}$ 表示前 $i$ 个烹饪方法，总共选出来 $k$ 个菜，其中 $c$ 个菜用食材 $x$ 。枚举所有烹饪方法、菜肴数量和使用食材 $x$ 的菜的数量，尝试转移。由于每一个烹饪方法至多选一个食材，所以要么选一个食材，要么什么都不选。

1. 如果选一个食材，转移为：如果 $j = x$ ，则共 $a_{i,j} \times dp_{i-1,k-1,c-1}$ 种；如果 $j \ne x$ ，则共 $a_{i,j} \times dp_{i-1,k-1,c}$ 种。
2. 如果什么都不选，共 $dp_{i-1,k,c}$ 种。

最后，对所有 ${c,k}$ 的 $dp_{n,k,c}$ 求和，其中 $c > \lfloor \frac{k}{2} \rfloor$ 且 $0<k$ 。这样，时间复杂度为 $O(m \times n^3m)$ （因为 $k$ 和 $c$ 的范围都在 $n$ 以内）不可接受。

考虑 $c>\lfloor \frac{k}{2} \rfloor$ 实际上意味着什么。注意，这条件等价于 $c>\lfloor \frac{k}{2} \rfloor$ ：

1. 如果 $k$ 是偶数，则 $\lfloor \frac{k}{2} \rfloor = \frac{k}{2}$ 。
2. 如果 $k$ 是奇数， $c>\frac{k}{2}-\frac{1}{2}$ ，对于整数 $c$ 这等价于 $c>\frac{k}{2}$ 。

整理表达式，得到 $2c - k > 0$ ，或者 $c-(k-c)>0$ 。这的实际意义是 $j=x$ 的物品数量，减掉 $j \ne x$ 的物品数量，大于 $0$ 。所以只需要关心这两个值的差，而不关心菜肴的数量。动态规划就可以进行以下的修改：

  当烹饪方法为 $i$ ，食材为 $j$ ，转移为：
1.   如果 $j=x$ ，则 $dp_{i,Δc+1} ← a_{i,j} \times dp_{i-1,Δc}$ （代表将 $a_{i,j} \times dp_{i-1,Δc}$ 加到 $dp_{i,Δc+1}$ ）。
2.   如果 $j \ne x$ ，则 $dp_{i,Δc-1} ← a_{i,j} \times dp_{i-1,Δc}$ 。

当不选， $dp_{i,Δc} ← dp_{i-1,Δc}$ 。最后对所有正整 $Δ$ 取 $dp_{n,Δc}$ 之和。

注意优化到这里就可以把很多转移累积到一起。不必枚举所有 $j$ ，而可以直接分 $j=x$ ， $j\ne x$ 与不选这三个方式转移：
1. 对于 $j=x$ ， $dp_{i,Δ+1}← a_{i,x}dp_{i-1,Δ}$ 。
2. 对于 $j\ne x$ ， $dp_{i,Δ-1}←(-a_{i,x}+\sum_{j = 1}^{m} a_{i,j})dp_{i-1,Δ}$ 。
3. 对于不选， $dp_{i,Δ}←dp_{i-1,Δ}$ 。

虽然最终 $Δc$ 只取正的部分，在中途， $Δc$ 为负也可以对答案贡献，所以需要同时维护正和负 $Δc$ 。由于坐标可能为负，因此可以将其加上一个数，以保证坐标为正。在本蒟蒻的代码里，我加的是 $101$ ，大家可以另寻己见，但切记数组一定不要越界。

最终时间复杂度为 $O(n
^2m)$ 。参考代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 105
#define maxm 2005
const int mod = 998244353;
int s[maxn];
int a[maxn][maxm];
int dp[maxn][maxn<<1];
int ops,mats;
int prod = 1;
int main(){
	cin>>ops>>mats;
	for(int i = 1;i<=ops;i++){
		for(int j = 0;j<mats;j++){
			cin>>a[i][j];
			s[i] = (s[i]+a[i][j])%mod;
		}
		prod = 1ll*prod*(s[i]+1)%mod;
	}
	int ans = (prod+mod-1)%mod;
	for(int x = 0;x<mats;x++){
		memset(dp,0,sizeof(dp));
		dp[0][0+101] = 1;
		int no = 0;
		for(int i = 1;i<=ops;i++){
			int re = (s[i]+mod-a[i][x])%mod;
			for(int d = 1;d<=201;d++){
				dp[i][d+1] = (dp[i][d+1]+1ll*a[i][x]*dp[i-1][d])%mod;
				dp[i][d-1] = (dp[i][d-1]+1ll*re*dp[i-1][d])%mod;
				dp[i][d] = (dp[i][d]+dp[i-1][d])%mod;
			}
		}
		for(int d  =1;d<=ops;d++){
			no = (no+dp[ops][d+101])%mod;
		}
		ans = (ans+mod-no)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

管理大大求过，qwq。

---

## 作者：lylcpp (赞：0)

## 16 pts

针对只有两种食材，考虑枚举三进制数，$1$ 代表第一种食材，$2$ 代表第二种食材，$0$ 代表不选。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long

using namespace std;

const int mod = 998244353, maxn = 19;
int n, m, a[maxn][maxn], ans;

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			scanf("%lld", &a[i][j]);
	}
	if (m == 2) {
		int maxx = pow(3, n);
		for (int i = 1; i < maxx; i++) {
			int tmp = i, c0 = 0, c1 = 0, c2 = 0, ff = 0;
			int res1 = 1, res2 = 1;
			while (tmp) {
				ff++;
				if (tmp % 3 == 1) {
					c1++;
					res1 *= a[ff][1], res1 %= mod;
				}
				else if (tmp % 3 == 2) {
					c2++;
					res2 *= a[ff][2], res2 %= mod;
				}
				tmp /= 3;
			}
			if (c1 == c2) 
				ans = (ans + res1 * res2 % mod) % mod;
		}
		printf("%lld\n", ans % mod);
	}
	return 0;
}
``````

`res1 * res2` 的原理是是乘法原理。

## 64 pts

针对 $m \le 3$ 采用 `dp`。设 $f_{i,a,b,c}$ 表示考虑到第 $i$ 种食材，用食材 $1$ 烧 $a$ 道菜，食材 $2$ 烧 $b$ 道菜，食材 $3$ 烧 $c$ 道菜。于是就有转移：

```cpp
int val = f[i-1][a][b][c];
if (a >= 1) val = (val + w[i][1] * f[i-1][a-1][b][c]) % mod;
if (b >= 1) val = (val + w[i][2] * f[i-1][a][b-1][c]) % mod;
if (c >= 1) val = (val + w[i][3] * f[i-1][a][b][c-1]) % mod;
f[i][a][b][c] = val;
``````

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long

using namespace std;

const int N = 49, maxm = 4, mod = 998244353;
int n, m, w[N][maxm], f[N][N][N][N], ans;

signed main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &w[i][j]);
		}
	}
	if (m > 3) return 0;
	f[0][0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int a = 0; a <= i; a++) {
			for (int b = 0; b <= i; b++) {
				for (int c = 0; c <= i; c++) {
					int val = f[i-1][a][b][c];
					if (a >= 1) val = (val + w[i][1] * f[i-1][a-1][b][c]) % mod;
					if (b >= 1) val = (val + w[i][2] * f[i-1][a][b-1][c]) % mod;
					if (c >= 1) val = (val + w[i][3] * f[i-1][a][b][c-1]) % mod;
					f[i][a][b][c] = val;
				}
			}
		}
	}
	for (int a = 0; a <= n; a++) {
		for (int b = 0; b <= n; b++) {
			for (int c = 0; c <= n; c++) {
				int k = a + b + c;
				if (k >= 1 && a <= k / 2 && b <= k / 2 && c <= k / 2) {
					ans += f[n][a][b][c], ans %= mod;
				}
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
``````

`w[i][1] * f[i-1][a-1][b][c]` 的意思是前 $i-1$ 种烹饪方式，烧 $a-1$ 道食材 $1$ 的菜，乘上 `w[i][1]`，原理依旧是乘法原理。

## 84 pts

假设 $f_{i,j}$ 表示用前 $i$ 种方法，做 $j$ 道菜 (不考虑要求 $3$) 的方案数，$g_{i, j, k}$ 表示用前 $i$ 种方法，某种食材做了 $j$ 道菜，其他食材做了 $k$ 道菜。

枚举这个某种食材，然后枚举 $j$ 和 $k$，接着转移。

```cpp
int val = g[i-1][j][k];
if (j > 0) val = (val + g[i-1][j-1][k] * a[i][x]) % mod;
if (k > 0) val = (val + g[i-1][j][k-1] * (s[i] - a[i][x])) % mod;
g[i][j][k] = val;
``````

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long

using namespace std;

const int N = 49, M = 509, mod = 998244353;
int f[N][M]; // 用前 i 种方法，做 j 道菜 (不考虑要求 3) 的方案数 
int g[N][N][N]; // 用前 i 种方法，某种食材做了 j 道菜，其他食材做了 k 道菜 
int n, m, a[N][M], s[N], ans;

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%lld", &a[i][j]);
			s[i] += a[i][j];
		}
	}
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0) f[i][j] = f[i-1][j];
			f[i][j] = (f[i-1][j] + f[i-1][j-1] * s[i] % mod) % mod;
		}
	}
	for (int j = 1; j <= n; j++)
		ans = (ans + f[n][j]) % mod;
	g[0][0][0] = 1;
	for (int x = 1; x <= m; x++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= i; j++) {
				for (int k = 0; k <= i - j; k++) { // j + k <= i
					int val = g[i-1][j][k];
					if (j > 0) val = (val + g[i-1][j-1][k] * a[i][x]) % mod;
					if (k > 0) val = (val + g[i-1][j][k-1] * (s[i] - a[i][x])) % mod;
					g[i][j][k] = val;
				}
			}
		}
		// j > k 不符合要求 3
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < j; k++)
				ans = (ans - g[n][j][k] + mod) % mod;
		} 
	}
	printf("%lld\n", ans);
	return 0;
}
``````

## 100 pts

```cpp
int f[N][M]; // 用前 i 种方法，做 j 道菜 (不考虑要求 3) 的方案数 
int g[N][N << 1]; // 用前 i 种方法，某种食材做了 j 道菜，其他食材做了 k 道菜 
``````

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long

using namespace std;

const int N = 102, M = 2003, mod = 998244353;
int f[N][M]; // 用前 i 种方法，做 j 道菜 (不考虑要求 3) 的方案数 
int g[N][N << 1]; // 用前 i 种方法，某种食材做了 j 道菜，其他食材做了 k 道菜 
int n, m, a[N][M], s[N], ans;
int t1, t2;

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%lld", &a[i][j]);
			s[i] += a[i][j], s[i] %= mod;
		}
	}
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0) f[i][j] = f[i-1][j];
			f[i][j] = (f[i-1][j] + f[i-1][j-1] * s[i] % mod) % mod;
		}
	}
	for (int j = 1; j <= n; j++)
		t1 = (t1 + f[n][j]) % mod;
	for (int x = 1; x <= m; x++) {
		memset(g, 0, sizeof(g));
		g[0][n] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = n - i; j <= n + i; j++) {
				int val = g[i-1][j];
				val = (val + g[i-1][j-1] * a[i][x]) % mod;
				val = (val + g[i-1][j+1] * (s[i] - a[i][x])) % mod;
				g[i][j] = val;
			}
		}
		for (int j = n + 1; j <= 2 * n; j++) 
			t2 = (t2 + g[n][j]) % mod;
	}
	printf("%lld\n", (t1 - t2 + mod) % mod);
	return 0;
}
``````

---

## 作者：strcmp (赞：0)

这题其实放到今天已经是典题了。

首先每种主要食材最多出现 $\lfloor \frac{k}{2} \rfloor$ 次，这很难不让人想到我们去钦定一道菜它是出现超过 $\lfloor \frac{k}{2} \rfloor$ 次的，然后用总方案减去这个不合法的方案。

一旦我们钦定了一道菜出现超过 $\lfloor \frac{k}{2} \rfloor$ 次（也就是出现了不少于 $\lceil \frac{k}{2} \rceil$ 次），那么剩下的菜自然要出现小于等于 $\lfloor \frac{k}{2} \rfloor$ 次。

于是有一个 naive 的 dp 就是枚举 $x$，设一个 $f_{i,\,j,\,k}$ 代表前 $i$ 行 $x$ 出现了 $j$ 次且其它菜出现了 $k$ 次的方案数。

这是显然可以转移的，但是没做完，因为我们的复杂度是 $\Theta(n^3m)$，过不了。

发现有很多状态可以合并起来，于是考虑差值 dp，设 $f_{i,\,j}$ 代表前 $i$ 行 $x$ 出现次数减去其它菜出现次数等于 $j$ 的方案数。

于是有：

$$
f_{i,\,j} \leftarrow f_{i - 1,\,j} + f_{i - 1,\,j - 1} \times a_{i,\,x} + f_{i - 1,\,j + 1} \times (s_i - a_{i,\,x})
$$

其中 $s_i = \sum\limits_{j = 1}^{m} a_{i,\,j}$。

时间复杂度 $\Theta(n^2m)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define X first
#define Y second
#define pb push_back
#define rep(i, a, b) for (int i = a; i <= b; i++)
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
using iter = multiset<ll>::iterator;
constexpr int maxn = 4e5 + 10, mod = 998244353;
int n, m; ll a[105][2005], s[105], g[105][305], f[105][305], sum = 0, ans = 1;
int main() {
	scanf("%d%d", &n, &m); f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) scanf("%lld", &a[i][j]), s[i] = (s[i] + a[i][j]) % mod;
		ans = ans * (s[i] + 1) % mod;
	}
	ans = (ans + mod - 1) % mod;
	//cout << ans << "\n";
	for (int i = 1; i <= m; i++) {
		memset(f, 0, sizeof(f)); f[0][105] = 1;
		for (int j = 1; j <= n; j++) {
			for (int k = -102; k <= 102; k++) {
				f[j][k + 105] = (f[j - 1][k + 105] + f[j - 1][k + 104] * a[j][i] % mod + f[j - 1][k + 106] * (s[j] - a[j][i] + mod) % mod) % mod;
			}
		}
		for (int k = 106; k <= 206; k++) ans = (ans - f[n][k] + mod) % mod;
	}
	printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

好题啊。

为什么一定要选超过一半才叫不合法呢？我们发现不合法的列最多只有一个。

所以答案为总方案除去一列超出限制的方案数。

枚举哪一列超限，然后设计 $F_{i,j,k}$ 表示前 $i$ 行，这一列选了 $j$ 个，其他列选了 $k$ 个方案数。

转移时讨论选择自己这一列还是别人的列，预处理出一行菜式数量的和，然后 $O(1)$ 转移。

时间复杂度 $O(mn^3)$ 无法通过。

考虑优化，我们只关心自己这一列和别人的数量的差。

设计 $F_{i,j}$ 表示前 $i$ 行，这一列比别的列的总数多 $j$ 个方案数。$j$ 可以是负数，所以要加一个偏移量。

时间复杂度 $O(mn^2)$ 足以通过。

再考虑总方案数。这是容易用计数原理计算的。具体的，假设 $i$ 行的总菜式数为 $S_i$ 则方案数为 $\displaystyle \prod_{i=1}^n (S_i+1)$。

总时间复杂度为 $O(mn^2)$。

---

## 作者：Genius_Star (赞：0)

### 题意：

给出一个矩阵，要求每行只能选一个节点，每列选的节点不能超过所有选的节点的一半，不能不选，给出每个节点的选择方案数，求总方案数。

### 思路：

定义：

$$s(i)=\sum_{j=1}^m a_{i,j}$$

首先易得总方案数为：

$$\Big(\prod_{i=1}^n (s(i)+1) \Big)-1$$

即每行选 $s(i)$ 里的一道菜或者不选，最后减去所有行都不选的方案数。

然后我们要减去减去有一列中选了大于 $\lfloor \frac{k}{2} \rfloor$ 道菜的方案数。

考虑动态规划算法，定义 $dp_{i,j,k,l}$ 表示对于前 $i$ 行，共选了 $k$ 道菜，且第 $j$ 道菜选了 $l$ 次，则状态转移方程为：

$$dp_{i,j,k,l} = dp_{i-1,j,k,l} + a_{i,j} \times dp_{i-1,j,k-1,l-1} + (s(i) - a_{i,j} )\times dp_{i-1,j,k-1,l}$$

其中上式的三项分别为第 $i$ 种烹饪方式什么也不选、选第 $j$ 种食材、选除了第 $j$ 种食材的其他食材，时间复杂度为 $O(N^3M)$。

最后贡献为：

$$\sum_{k=1}^n \sum_{i = \lfloor \frac{k}{2} \rfloor +1}^k dp_{n,j,k,i}$$

考虑进行优化，注意到，只要选第 $j$ 道菜的减去选其它所有菜的次数之和 $>0$ 那么就是有贡献的，那么考虑将 $k,l$ 压缩。

定义 $dp_{i,j,k}$ 表示对于前 $i$ 行，第 $j$ 种食材选的次数减去其他食材的次数和为 $k$ 的方案数，那么状态转移方程为：

$$dp_{i,j,k} = dp_{i-1,j,k} + a_{i,j} \times dp_{i-1,j,k-1} + (s(i)-a_{i,j}) \times dp_{i-1,j,k-1}$$

注意到 $k$ 的取值范围在 $[-n,n]$，整体偏移 $n$ 即可。

最后贡献为：

$$\sum_{i=1}^n dp_{n,j,i}$$

时间复杂度为 $O(N^2M)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=105,M=2020,mod=998244353; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,ans=1;
ll a[N][M],s[N];
ll dp[N][N<<1ll];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			s[i]=(s[i]+a[i][j])%mod;
		}
		ans=(ans*(s[i]+1))%mod;
	}
	ans--;
	for(int j=1;j<=m;j++){
		dp[1][n]=1,dp[1][n+1]=a[1][j],dp[1][n-1]=(s[1]-a[1][j]+mod)%mod;
		for(int i=2;i<=n;i++)
		  for(int k=-n;k<=n;k++)
			dp[i][k+n]=(dp[i-1][k+n]+a[i][j]*dp[i-1][k+n-1]%mod+(s[i]-a[i][j]+mod)%mod*dp[i-1][k+n+1]%mod)%mod;
		for(int i=1;i<=n;i++)
		  ans=(ans-dp[n][n+i]+mod)%mod;
		memset(dp,0,sizeof(dp));
	}
	write(ans);
	return 0;
}
```

这是一年前写的 code 了，码风可能有点不好看，见谅。

---

## 作者：tony0530 (赞：0)

## solution

------

#### 题目

给定 $n \le 10^2\; m \le 2 \times 10^3$ 和一个 $n \times m$ 的矩阵，横行纵列分别表示不同的烹饪方法和主要食材，矩阵上每个数表示会做的不同主菜。对于不同的做菜方案，每个方案至少有一道菜，每个烹饪方法互不相同，每个菜品数量为 $k$ 的方案每种主要食材不超过 $ \lfloor \frac{k}{2} \rfloor $ 个，求方案数对 $998244353$ 取模。

-----

#### 做法

考虑**正难则反**！
- 一共：$total = \prod_{i=1}^n(\sum_{j=1}^m a_{i,j} +1) -1$。
- 不合法方案：因为 $k \le 3 \times  \lfloor \frac{k}{2} \rfloor$ 所以至多有两个大于 $\lfloor \frac{k}{2} \rfloor$ 的，进一步发现至多有一个，就只要枚举这个超过 $\lfloor \frac{k}{2} \rfloor$ 的数再进行转移即可。
  
设 $f_{i,j,k}$ 表示考虑前 $i$ 种，多于 $\lfloor \frac{k}{2} \rfloor$ 的选了 $j$ 个，其他的选了 $k$ 个的方案数。

时间复杂度为 $O(n^3m)$，不太能过。。。。

考虑哪两维可以合并，发现我们不关心 $j,k$，只要知道  $j-k$ 即可。

时间复杂度为 $O(n^2m)$，就能过了。

-----

#### 代码

```cpp

#include<bits/stdc++.h>
#define int long long
const int mod = 998244353;
const int maxn = 105;
const int maxm = 2005;
using namespace std;
int n, m, ans = 1;
int sum[maxn], a[maxn][maxm], f[maxn][maxn << 1];
inline int read()
 {
	int x = 0;
	char ch = getchar();
	for( ; ch < '0' || ch > '9' ; ch = getchar());
	for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = x * 10 + ch - '0';
	return x;
}
signed main(){
	n = read();
	m = read();
	for(int i = 1; i <= n ;i ++ )
	{
	    for (int j = 1; j <= m ; j ++ )
	    {
	        a[i][j] = read();
	        sum[i] = (sum[i] + a[i][j]) % mod;
	    }
	}
	for(int i = 1; i <= n ; i ++ )
	{
	    ans *= (sum[i] + 1), ans %= mod;
	}
	 -- ans;
	for (int i = 1 ; i <= m ; i ++ )
	{
		f[0][0] = 1;
		for (int j = 1 ; j <= n ; j ++ )
		{
			for(int k = 0; k <= n << 1 ; k ++ )
			{
				f[j][k] += f[j - 1][k] * ((sum[j] + mod- a[j][i]) % mod), f[j][k] %= mod;
				f[j][k + 1] += f[j - 1][k], f[j][k + 1] %= mod;
				f[j][k + 2] += f[j - 1][k] * a[j][i], f[j][k + 2] %= mod;  
			}
		}
		for(int j = n + 1 ; j <= n << 1 ; j ++ ) ans += (mod - f[n][j] % mod), ans %= mod;
		for(int j = 1 ; j <= n  ; j ++ )
		{
		    for (int k = 0 ; k <= (n << 1) + 2 ; k ++ )
		    {
		        f[j][k] = 0; 
		    }
		}
	}
	printf("%lld", ans % mod);
	return 1;
}
```

---

