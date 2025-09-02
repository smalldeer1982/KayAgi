# Count Binary Strings

## 题目描述

You are given an integer $ n $ . You have to calculate the number of binary (consisting of characters 0 and/or 1) strings $ s $ meeting the following constraints.

For every pair of integers $ (i, j) $ such that $ 1 \le i \le j \le n $ , an integer $ a_{i,j} $ is given. It imposes the following constraint on the string $ s_i s_{i+1} s_{i+2} \dots s_j $ :

- if $ a_{i,j} = 1 $ , all characters in $ s_i s_{i+1} s_{i+2} \dots s_j $ should be the same;
- if $ a_{i,j} = 2 $ , there should be at least two different characters in $ s_i s_{i+1} s_{i+2} \dots s_j $ ;
- if $ a_{i,j} = 0 $ , there are no additional constraints on the string $ s_i s_{i+1} s_{i+2} \dots s_j $ .

Count the number of binary strings $ s $ of length $ n $ meeting the aforementioned constraints. Since the answer can be large, print it modulo $ 998244353 $ .

## 说明/提示

In the first example, the strings meeting the constraints are 001, 010, 011, 100, 101, 110.

In the second example, the strings meeting the constraints are 001, 110.

## 样例 #1

### 输入

```
3
1 0 2
1 0
1```

### 输出

```
6```

## 样例 #2

### 输入

```
3
1 1 2
1 0
1```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 2 1
1 0
1```

### 输出

```
0```

## 样例 #4

### 输入

```
3
2 0 2
0 1
1```

### 输出

```
0```

# 题解

## 作者：Cxny (赞：10)

$a_{i,i}=2$ 的情况显然无解。

设 $dp_{i,j}$ 表示到第 $i$ 个数为止，**最长相同后缀**起点为 $j$ 的方案数。

考虑将 $i\sim j$ 的限制表示为：

- $a_{i,j}=1$：$i+1\sim j$ 取值必须与前一个数相同。打标记。
- $a_{i,j}=2$：前 $j$ 个数的最长相同后缀长度不超过 $j-i$。预处理最大限制 $lim_j$。

若 $s_i=s_{i-1}$，则有 $dp_{i,j}=dp_{i-1,j}$；

若 $s_i\ne s_{i-1}$，则有 $dp_{i,i}=\sum_{j=lim_i}^{i-1}dp_{i-1,j}$。

复杂度瓶颈在于打标记。线段树维护可以做到 $O(n^2\log n)$。或许还可以到 $O(n^2)$？

本人就用朴素的 $O(n^3)$ 实现了。

```cpp
const int maxn = 110, mod = 998244353;
int n, a[maxn][maxn], lim[maxn], pos;
ll dp[maxn][maxn], ans;
bool flag[maxn];
signed main(){
    scanf("%d", &n);
    fill(lim + 1, lim + n + 1, 1);
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            scanf("%d", &a[i][j]);
            if(a[i][j] == 1) fill(flag + i + 1, flag + j + 1, 1);
            else if(a[i][j] == 2) pos = max(pos, i + 1), lim[j] = max(lim[j], i + 1);
        }
        if(a[i][i] == 2) return puts("0"), 0;
    }
    dp[1][1] = 1;
    for(int i = 2; i <= n; i++){
        if(!flag[i]) for(int j = 1; j < i; j++) dp[i][i] = (dp[i - 1][j] + dp[i][i]) % mod;
        for(int j = lim[i]; j < i; j++) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
    }
    for(int i = pos; i <= n; i++) ans = (ans + dp[n][i]) % mod;
    printf("%lld\n", ans * 2 % mod);
    return 0;
}
```

---

## 作者：Ynoel (赞：6)

# CF1767C Count Binary Strings

> OI，无非就是找到信息的性质并加以应用


## 考虑处理每一个限制条件

对于 1 限制，明显具有传递性，可以用并查集维护。

对于 2 限制，对于每一个右端点，左端点的 max 是限制最严格的。

两者都可以预处理。

## 状态设计

考虑 DP，设状态 $f_{i,j}$ 表示以 $i$ 为结尾，最长的连续后缀段的开始位置为 $j$ 的方案数。

## 考虑转移：
有两种情况：

### ①连上之前的最长段（即 $f_{i,[1,i)}$）

这种转移方式的限制是限制 2，必须要不同的位置。

以及必须要相同的位置，即限制 1。

两者之间的段即是可转移的段。

### ②新开一段 （即 $f_{i,i}$）

要保证当前点并未再限制 1 的包含中。

具体公式可以看代码。

综上复杂度 $O(n^2)$。

## 代码
```cpp

typedef pair<int,int> pii;
const int N = 5010,INF = 0x3f3f3f3f3f3f3f3f,mod = 998244353;

int lim[N],p[N];
int f[N][N];

int find(int x)
{
	if(p[x] != x) p[x] = find(p[x]);
	return p[x];
}

void merge(int l,int r)
{
	for(int i=find(r);i>l;i=find(i)) p[i] = p[i-1];
}

signed main()
{
	int n;
	rd(n);
	for(int i=1;i<=n;i++) p[i] = i;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			int op;
			rd(op);
			if(op == 1)	merge(i,j);
			if(op == 2) lim[j] = max(lim[j],i+1);
			if(i==j && op == 2)
			{
				cout << 0;
				return 0;
			}
		}
	f[1][1] = 1;
	for(int i=2;i<=n;i++)
	{
		for(int j=lim[i];j<=find(i);j++)
			f[i][j] = f[i-1][j];
		if(find(i) == i)
			for(int j=1;j<n;j++) 
				f[i][i] = (f[i][i] + f[i-1][j]) % mod;
	}
	int ans = 0;
	for(int i=find(i);i<=n;i++)
		ans = (ans+f[n][i]) % mod;
	cout << ans*2 % mod << endl;
	return 0;
}
```
宏定义就不放进来了


---

## 作者：Leasier (赞：4)

首先判掉 $a_{i, i} = 2$ 的情况，此时显然无解。

由于题目中提到的两种条件都与每个极大 01 连续段的开头位置有关，考虑如下的 dp：设 $dp_{i, j}$ 表示 $[j, i]$ 为一个极大连续段时，$[1, i]$ 的方案数。

初值：$dp_{1, 1} = 1$。

转移：首先看一下 $[j, i]$ 是否满足题目条件，即看一下是否满足 $\forall 1 \leq k \leq i$，$a_{k, i} = 0$ 或 $a_{k, i} = 1 \operatorname{and} j \leq k$ 或 $a_{k, i} = 2 \operatorname{and} j > k$。

若满足条件，则分两种情况讨论：

- $j < i$：此时令 $dp_{i, j} \leftarrow dp_{i - 1, j}$。
- $j = i$：此时令 $dp_{i, j} \leftarrow \displaystyle\sum_{k = 1}^{i - 1} dp_{i - 1, k}$。

答案：$2 \displaystyle\sum_{i = 1}^n dp_{n, i}$。这里乘 $2$ 是因为第一个连续段到底是 $0$ 还是 $1$ 无影响。

时间复杂度为 $O(n^3)$。

代码：
```cpp
#include <stdio.h>
#include <stdbool.h>

const int mod = 998244353;
int a[107][107], dp[107][107];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		for (int j = i; j <= n; j++){
			scanf("%d", &a[i][j]);
		}
		if (a[i][i] == 2){
			printf("0");
			return 0;
		}
	}
	int ans = 0;
	dp[1][1] = 1;
	for (int i = 2; i <= n; i++){
		for (int j = 1; j <= i; j++){
			bool flag = true;
			for (int k = 1; k <= i; k++){
				if ((a[k][i] == 1 && j > k) || (a[k][i] == 2 && j <= k)){
					flag = false;
					break;
				}
			}
			if (flag){
				if (j < i){
					dp[i][j] = dp[i - 1][j];
				} else {
					for (int k = 1; k < i; k++){
						dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i++){
		ans = (ans + dp[n][i]) % mod;
	}
	printf("%d", ans * 2 % mod);
	return 0;
}
```

---

## 作者：035966_L3 (赞：3)

**UPD：区间包含区间应用 $\subseteq$，之前用成 $\in$ 了。**

------------

首先：

- 若有一个 $1$ 出现在 $2$ 后面，则无解（代码中为 `no` 函数）。
  > **证明：**
  >
  > 设 $a_{i,j}=2,a_{i,k}=1(j<k)$，则 $[i,j] \subseteq [i,k]$。
  >
  > 因为 $s_{[i,j]}$ 中有两种不同字符，所以 $s_{[i,k]}$ 中有两种不同字符。
  >
  > 即 $a_{i,k} \neq 1$，矛盾，因此无解。**原命题得证。**
- 若 $a_{i,i}=2$，则无解（代码中为 `no` 函数）。
  > **证明：**
  >
  > $s_{[i,i]}$ 中只有一个字符，不可能有两种不同字符。**原命题得证。**

接下来，由所有 $a_{i,j}=1$ 的信息，可以知道 $s$ 中某些相邻的字符相同，这时可以把它们「合并」。（代码中为 `fill` 函数）

设合并后的字符串为 $r$（显然它与 $s$ 一一对应），长度为 $t$（代码中为 `tp`）。

由所有 $a_{i,j}=2$ 的信息，设已知 $r_{[i,e_i]}$ （$e$ 数组在代码中为 `fl2s`；**初始化时，$e_i=+\infty$**）中有两种不同字符（即存在 $q \in [i,e_i]$ 使 $r_i \neq r_q$）。

当然了，若 $e_i=i$，则无解（代码中为 `no` 函数），证明类似。

**接下来是 DP 部分。**

设 $f_{i,j}$（$1 \le i \le t + 1,j \in \{0,1\}$；$f$ 数组在代码中为 `dp`；**初始化时，$f_{i,j}=0$**）为满足下面条件的 $r$ 的个数：

1. 只确定了 $r_{[1,i]}$；
2. $r_i=j$；
3. 当 $i \ge 1$ 时，$r_{i-1} \neq r_i$；
4. 当 $i \ge 1$ 时，$r$ 满足 $e_{[1,i-1]}$ 的要求。

**显然，初始状态是 $f_{1,0}=f_{1,1}=1$。**

然而，$f_{t,0}+f_{t,1}$ **不是答案**，它只算了 $r_t \neq r_{t-1}$ 的情况。

有一种解决方案：在 $r$ 后加一个字符 $r_{t+1}$，保证 $r_{t+1} \neq r_t$（显然它与原来的 $r$ 一一对应，即与 $s$ 一一对应）。

代码中的处理方式是，把 $e$ 数组中所有的 $+\infty$ 改为 $t+1$。

**此时，答案即为 $f_{t+1,0}+f_{t+1,1}$。**

接下来，看如何从 $f_{i,j}$ 中转移。（**顺序：$i$ 升序，$j$ 随意**）

我们试着从 $f_{i,j}$ 转移到 $f_{k,1-j}(k \in [i+1,e_i])$。（代码中 $e_i$ 为 `k`，$k$ 为 `ii`）

此时，填入 $r_{[i+1,k-1]}=j$（如果 $k=i+1$ 就不填入 $j$），$r_k=1-j$。

填入后的 $r$（显然它与填入前的 $r$ 一一对应）此时只剩下第 $4$ 点要求没有满足了。

接着，检查填入后的 $r$ 是否满足第 $4$ 点要求（代码中为 `check` 函数）。

只需检查是否有 $q \in [i+1,k-1]$ 满足 $e_q<k$ 即可。如果**有**，则**不满足**第 $4$ 点要求；如果**没有**，则**满足**第 $4$ 点要求。

满足的话，$f_{k,1-j}$ 加上 $f_{i,j}$；不满足的话，就不加了。

综上，该算法的复杂度（**下面采用「时间 - 空间」的计法**）由 `check` 函数的算法而定：

- 暴力（我用的）：$O(n^3) - O(n)$
- 线段树：$O(n^2 \log n) - O(n)$
- ST 表：$O(n^2) - O(n \log n)$
- ~~Four Russians（选自 OI Wiki，仅供参考）：$\sout{O(n^2) - O(n \log \log n)}$~~
- ~~笛卡尔树（选自 OI Wiki，仅供参考）：$\sout{O(n^2) - O(n)}$~~

**最后，记得随时取模！**

**AC Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=998244353,N=112;
int p[N];
int l1s[N],l2s[N],fl2s[N];
int dp[N][2];
void no()
{
	puts("0");
	exit(0);
}
int fill(int n)
{
	int alr=0,p1=0,p2=0;
	while(1)
	{
		if(p1==n) return alr;
		p2++,alr++;
		p[p2]=alr;
		while(p1!=p2)
		{
			p1++;
			for(int i=p1;i<=l1s[p1];i++)
				p[i]=p[p1],p2=max(i,p2);
		}
	}
}
int check(int from,int to)
{
	for(int i=from+1;i<=to-1;i++)
		if(fl2s[i]<to) return 0;
	return 1;
}
int main()
{
	memset(fl2s,0x7f,sizeof fl2s);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int l1=0,l2=n+1;
		int tmp;
		cin>>tmp;
		if(tmp==2) no();
		l1=i;
		for(int j=i+1;j<=n;j++)
		{
			cin>>tmp;
			if(tmp==1)
			{
				if(l2!=n+1) no();
				l1=j;
			}
			if(tmp==2&&l2>n) l2=j;
		}
		l1s[i]=l1,l2s[i]=l2;
	}
	int tp=fill(n)+1;
	p[n+1]=tp;
	for(int i=1;i<=n;i++)
	    fl2s[p[i]]=min(fl2s[p[i]],p[l2s[i]]);
	for(int i=1;i<=tp;i++)
		if(fl2s[i]==i) no();
	dp[1][0]=dp[1][1]=1;
	for(int i=1;i<=tp-1;i++)
		for(int j=0;j<=1;j++)
		{
			int k=fl2s[i];
			for(int ii=i+1;ii<=k;ii++)
				dp[ii][1-j]+=(check(i,ii)*dp[i][j]),dp[ii][1-j]%=P;
		}
	cout<<(dp[tp][0]+dp[tp][1])%P;
    return 0;
}
```

---

## 作者：氧少Kevin (赞：3)


# CF1767C - Count Binary Strings

## 题意

有一个长度为 $n$ 的 01 串 $s$ 和一些限制 $a_{i,j}(1 \le i \le j \le n)$。

$a_{i,j}$ 的含义如下：

| $a_{i,j}$ | 含义 |
| :----------: | :----------: |
| $0$ | 没有限制 |
| $1$ | 该区间里的数字完全相同 |
| $2$ | 该区间里的数字不能完全相同 |

求可能的 $s$ 的个数。

## 思路（区间DP）

为了计数不重不漏，我们令 $dp[l][r][0/1/2/3]$ 分别代表在区间 $[i,j]$ 中，整个区间都是 $0$，整个区间都是 $1$，整个区间 $01$ 都有但最左边放的是 $0$，整个区间 $01$ 都有但最左边放的是 $1$ 的方案数。

如果一个区间 $01$ 都有，那么可以这样计数：

- 枚举中间端点 $k$，使得区间 $[l,k]$ 全是 $0$，但 $k$ 处一定是 $1$，并且 $[k+1,r]$ 随便放。
- 枚举中间端点 $k$，使得区间 $[l,k]$ 全是 $1$，但 $k$ 处一定是 $0$，并且 $[k+1,r]$ 随便放。

同时注意检查区间限制的合法性。

- 枚举中间端点 $k$ 后，那么对于所有跨越该端点的区间 $[l,r]$，都不能有 $a_{l,r}=1$。
- 若某区间的限制为 $1$，那么对于所有完全包含于该端点的区间 $[l,r]$，都不能有 $a_{l,r}=2$。



转移时，枚举中间端点 $k$，在检查区间限制的合法性后，计数即可。

---

## 作者：封禁用户 (赞：3)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1767C)

[CF](https://codeforces.com/contest/1767/problem/C)

### 分析

**题解区目前唯一一篇时间复杂度明确 $O(n^2)$ 的题解。**

题目要求方案数，明显是一篇 DP 的题目。

根据题目“相同”、“不同”的限制，设状态 $dp_{i,j}$ 为前 $i$ 个数中最长相同后缀从 $j$ 开始的方案数量。

首先，对于 $a_{i,i} = 2$ 必然是不合法的，排除。

对于要求相同的一个区间，只处理第一个数字即可，其它的标记掉。

对于要求不同的一个区间，记录右端点的限制左端点，记为 $a$ 数组，初始为 $0$。

列出状态转移方程：

+ $dp_{i,i} = \sum_{j=1}^{i-1} dp_{i-1,j}$

+ $dp_{i,j} = dp_{i-1,j}$ 其中 $j > a_i$

+ $dp_{i,j} = 0$ 其中 $1 \le j \le a_i$

注意到可以滚动，省去第一个维度，状态转移方程为：

+ $dp_i = \sum_{j=1}^{i-1} dp_j$

+ $dp_j = 0$ 其中 $1 \le j \le a_i$

注意最终的答案，还有初始值为 $dp_1 = 2$，因为有 $0$ 和 $1$ 两种。

为了实现时间复杂度为 $O(n^2)$，这里的标记应当使用差分。

同时，空间复杂度也达到了优秀的 $O(n)$。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define N 110
const int mod = 998244353;
int f[N],a[N],dp[N],n,t = 0,x,ans = 0;
inline void add(int &x,int y) {(x += y) >= mod && (x -= mod);}
int main()
{
	scanf("%d",&n);
	F(i,1,n)
		F(j,i,n)
		{
			scanf("%d",&x);
			if(i == j&&x == 2) 
			{
				putchar('0');
				return 0;	
			}	
			if(x == 1) ++f[i+1],--f[j+1];
			else if(x == 2) t = max(t,i),a[j] = max(a[j],i);
		}
	dp[1] = 2;
	F(i,2,n)
	{
		f[i] += f[i-1];
		if(!f[i]) 
			F(j,1,i-1)
				add(dp[i],dp[j]);
		F(j,1,a[i]) dp[j] = 0;	
	}	
	F(i,t+1,n) add(ans,dp[i]);
	printf("%d",ans);
	return 0;
}

```


---

## 作者：Shunpower (赞：2)

upd on 2024.11.1：之前的表述有一些事实性错误，所以重构了一下题解。

这是一个使用区间 dp 的非常自然的另解。

------------

下面我们把 $0/1$ 称为颜色。

首先，因为 $1$ 限制要求连续的一段颜色必须相同，所以可以先用并查集把所有 $1$ 限制下的区间合并在一起，最终每个连通块里的颜色必须是一样的。我们把一个连通块缩成一个位置组成一个长度为 $m$ 的新序列继续考虑。

这样做完之后 $1$ 限制就自然存在，后面无需再考虑了。

再把 $2$ 限制中的端点改为端点所在连通块编号，转化为要求新序列上一个区间存在两种颜色。显然如果两个端点在同一个连通块输出 $0$，表示无解。

直接考虑区间 dp，设 $f_{l,r}$ 表示区间 $[l,r]$ 符合 $[l,r]$ 中所有要求的染色方案总数。

可以发现，如果 $[l,r]$ 包含有一个受 $2$ 限制的区间，那么它肯定由至少 $2$ 个极长同色连续段拼在一起；而如果 $[l,r]$ 不包含受 $2$ 限制的区间，那么先可以看作是有一个 $2$ 限制在 $[l,r]$ 这个区间上，再加上两种全部是一个颜色的就行了。所以我们直接考虑前者怎么做。

多个极长同色连续段拼在一起的方案如果在每个段之间的断点处都统计一次肯定会算重（比如 [[CSP-S 2021] 括号序列](https://www.luogu.com.cn/problem/P7914)），于是我们考虑用类似这个题的 trick 让它只在第一个断点位置被数到。

我们钦定一个方案被数到的断点是第一个极长同色连续段的末尾处。这个断点显然满足：断点及其左侧的颜色是一样的，断点右侧为第一个与前面反色的位置。因此我们必须要给 dp 数组增加一维记录下每个区间最左侧的颜色，不然我们无法识别是否反色。

现在 $f_{l,r,0/1}$ 表示区间 $[l,r]$ 符合 $[l,r]$ 中所有要求的染色方案总数，且 $l$ 处是 $0/1$。

考虑转移。当然需要枚举断点 $k$，再枚举一下 $l$ 处的颜色情况 $p$，那么因为 $[l,k]$ 都需要是一个颜色，$k+1$ 需要与 $k$ 反色，那么 $(k,r]$ 区间的最左侧颜色就是 $1-p$。于是得到转移：

$$
f_{l,r,p}\gets \sum\limits_{k=l}^{r-1}B_{l,k}\times f_{k+1,r,1-p}
$$

这里我们引入了一个新的记号 $B_{l,r}$，它表示 $[l,r]$ 中是否完整包含了一个受 $2$ 限制的区间，取值为 $0,1$。因为我们的转移钦定了 $[l,k]$ 是颜色相同的，所以只有不完整包含 $2$ 限制的区间有做到全部同色的可能。所有的 $B$ 值都可以 $\mathcal O(n^3)$ 提前全部预处理出来。

这个 dp 的精妙之处在于，我们的钦定恰好也考虑到了横穿断点的 $2$ 限制：断点左右两侧的颜色一定是相反的，因此所有横穿断点的 $2$ 限制一定可以满足，而断点左右两侧的 $2$ 限制已经在它们用于转移的状态里面（左边的 $B$ 和右边的 $f$）被考虑过了。

如果 $[l,r]$ 区间里面没有包含受 $2$ 限制的区间，我们刚才已经讨论过，需要加上两种全都同色的方案，也就是 $f_{l,r,0/1}$ 都需要加上 $1$。

最终答案就是 $f_{1,m,0}+f_{1,m,1}$。

精细实现一下整个东西复杂度应该可以做到 $\mathcal O(n^3)$。

## 代码

```cpp
const ll M=998244353;
int f[N];
int finder(int x){
    if(f[x]!=x) f[x]=finder(f[x]);
    return f[x];
}
int a[N][N];
bool noc[N][N];
ll dp[N][N][2];
int n,m;
int idx[N],lmin[N];
int nocons(int l,int r){
    fr1(i,l,r)
        if(lmin[i]<=r) return 0;
    return 1;
}
int main(){
#ifdef Griffin
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n;
    fr1(i,1,n) f[i]=i;
    fr1(i,1,n)
        fr1(j,i,n) cin>>a[i][j];
    fr1(i,1,n){
        fr1(j,i,n){
            if(a[i][j]==1){
                fr1(k,i+1,j) f[finder(k)]=finder(k-1);
            }
        }
    }
    fr1(i,1,n){
        if(finder(i)!=finder(i-1)){
            m++;
            idx[finder(i)]=m;
        }
    }
    fr1(i,1,m) lmin[i]=inf;
    fr1(i,1,n){
        fr1(j,i,n){
            if(a[i][j]==2){
                if(finder(i)==finder(j)){
                    cout<<"0\n";
                    return 0;
                }
                int fi=idx[finder(i)],fj=idx[finder(j)];
                lmin[fi]=min(lmin[fi],fj);
            }
        }
    }
    fr1(i,1,m)
        fr1(j,i,m) noc[i][j]=nocons(i,j);
    fr1(i,1,m){
        dp[i][i][0]=dp[i][i][1]=1;
        if(noc[i][i+1]) dp[i][i+1][0]=dp[i][i+1][1]=2;
        else dp[i][i+1][0]=dp[i][i+1][1]=1;
    }
    fr1(len,3,m){
        fr1(l,1,m-len+1){
            int r=l+len-1;
            fr1(k,l,r-1)
                fr1(p,0,1) (dp[l][r][p]+=noc[l][k]*dp[k+1][r][!p])%=M;
            fr1(p,0,1) dp[l][r][p]+=noc[l][r];
        }
    }
    cout<<(dp[1][m][0]+dp[1][m][1])%M<<'\n';
    ET;
}
//ETERNAL LOVE FOR Zhang Junhao, Mu Zhicheng and Zuo Hang.
//ALL FOR Zhang Junhao.
```

[AC 记录](https://codeforces.com/contest/1767/submission/289078244)。

---

## 作者：Comentropy (赞：1)

emmm，说实话有点不是很理解前面题解说的关于优化的问题，感觉大家的做法都比较奇怪。这个 DP 做到 $O(n^2)$ 应当是容易的。

以下是一些对这个问题的分析。一眼看过去感觉像是一个区间 DP，但是计数该怎么做？合并两个区间的答案显然是困难的，加上限制就显得更不可做。

我们像平时一样考虑对一个序列追加一个数，这样容易计数，并分析两类限制的影响：

1. 这个位置在某一段要求相同的部分，由于我们考虑的是追加，就可以把这样的限制转化为：“必须与前一个位置的数相等”，这样与我们的需求更相符。
2. 这个位置在某一段要求存在不同的部分。这种限制可以转化成什么呢？对于 $a_{i,j}=2$ 的 $(i,j)$，我们有：如果当前考虑到第 $j$ 个位置了，那么若其不与前面的数相同，则该条件天然满足；否则，与他组成连续段的最前的位置不会超过 $i+1$。

知道了现在的需求我们就可以设计 DP 来计数——上述的限制只会与后缀相同连续段有关，所以我们设计 $f_{i,j}$ 表示考虑到第 $i$ 个数，后缀连续段从 $j$ 开始的方案数（事实上类似的能表达相同信息的，比如说”长度“也可以）。

考虑转移：

1. 若当前位置可以与前一个位置不同，则可以使 $s_i\neq s_{i-1}$，那么 $\forall{j},f_{i,i}\leftarrow ,f_{i-1,j}$

2. 若要决定与前一个位置相同：$s_i=s_{i-1}$，则对于所有 $j<i$ 都有转移 $f_{i,j}\leftarrow f_{i-1,j}$。

对于预处理部分，限制 $1$ 的需求是：区间赋值 $1$，改为区间加和差分一下就可以处理；限制 $2$ 的需求是：对于 $a_{i,j}=2$，使 $lim_j=\max(lim_j,i+1)$，随便做做即可。这样时间复杂度自然可以做到 $O(n^2)$，无需刻意优化。

我感觉如果摆脱输入限制，改为散点输入，时间复杂度还能压。

(被打回了原因竟然是不让用中括号表示下标，我感觉改完之后是难看的。)

---

## 作者：江户川·萝卜 (赞：0)

拜谢 bp。

---

记 $f_{i,j}\{j<i\}$ 表示最右边与第 $i$ 位不同的是第 $j$ 位的方案数。

则若忽略限制，有$f_{i+1,j}=\begin{cases}j=i&\sum^{i-1}_{k=0}f_{i,k}\\\text{otherwise}&f_{i,j}\end{cases}$。

边界值 $f_{1,0}=2$。

具体写法是递推算贡献法，判一下是否符合限制即可。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define MOD 1000000007
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define N 500005
#define ls p<<1
#define rs p<<1|1
typedef long long ll;
using namespace std;
int a[105][105];
ll f[105][105];
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) cin>>a[i][j];
    if(a[1][1]!=2)f[1][0]=2;
    for(int i=1;i<=n;i++)
    for(int j=0;j<i;j++){
        bool ff=1;
        for(int k=1;k<=j;k++) if(a[k][i]==1) ff=0;
        for(int k=j+1;k<=i;k++) if(a[k][i]==2) ff=0;
        if(!ff) f[i][j]=0;
        f[i+1][j]=f[i][j];
        f[i+1][i]=(f[i+1][i]+f[i][j])%mod;
    }
    ll ans=0;
    for(int i=0;i<n;i++) ans=(ans+f[n][i])%mod;
    cout<<ans<<'\n';
}
int main(){
    std::ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    //int Case;cin>>Case;while(Case--)
    solve();
}
```

---

