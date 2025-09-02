# Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_o

$ N $ 人の男性たちと $ N $ 人の女性たちがいます。 男性たちには $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 同様に、女性たちには $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。

各 $ i,\ j $ ($ 1\ \leq\ i,\ j\ \leq\ N $) について、男性 $ i $ と女性 $ j $ の相性の良し悪しが整数 $ a_{i,\ j} $ によって与えられます。 $ a_{i,\ j}\ =\ 1 $ ならば男性 $ i $ と女性 $ j $ は相性が良く、$ a_{i,\ j}\ =\ 0 $ ならば相性が悪いです。

太郎君は、相性が良い男女どうしのペアを $ N $ 組作ろうとしています。 このとき、各男性および各女性はちょうど $ 1 $ つのペアに属さなければなりません。

$ N $ 組のペアを作る方法は何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 21 $
- $ a_{i,\ j} $ は $ 0 $ または $ 1 $ である。

### Sample Explanation 1

ペアを作る方法は次の $ 3 $ 通りです。 男性 $ i $ と女性 $ j $ のペアを $ (i,\ j) $ で表します。 - $ (1,\ 2),\ (2,\ 1),\ (3,\ 3) $ - $ (1,\ 2),\ (2,\ 3),\ (3,\ 1) $ - $ (1,\ 3),\ (2,\ 1),\ (3,\ 2) $

### Sample Explanation 2

ペアを作る方法は次の $ 1 $ 通りです。 - $ (1,\ 2),\ (2,\ 4),\ (3,\ 1),\ (4,\ 3) $

### Sample Explanation 4

答えを $ 10^9\ +\ 7 $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
3
0 1 1
1 0 1
1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
4
0 1 0 0
0 0 0 1
1 0 0 0
0 0 1 0```

### 输出

```
1```

## 样例 #3

### 输入

```
1
0```

### 输出

```
0```

## 样例 #4

### 输入

```
21
0 0 0 0 0 0 0 1 1 0 1 1 1 1 0 0 0 1 0 0 1
1 1 1 0 0 1 0 0 0 1 0 0 0 0 1 1 1 0 1 1 0
0 0 1 1 1 1 0 1 1 0 0 1 0 0 1 1 0 0 0 1 1
0 1 1 0 1 1 0 1 0 1 0 0 1 0 0 0 0 0 1 1 0
1 1 0 0 1 0 1 0 0 1 1 1 1 0 0 0 0 0 0 0 0
0 1 1 0 1 1 1 0 1 1 1 0 0 0 1 1 1 1 0 0 1
0 1 0 0 0 1 0 1 0 0 0 1 1 1 0 0 1 1 0 1 0
0 0 0 0 1 1 0 0 1 1 0 0 0 0 0 1 1 1 1 1 1
0 0 1 0 0 1 0 0 1 0 1 1 0 0 1 0 1 0 1 1 1
0 0 0 0 1 1 0 0 1 1 1 0 0 0 0 1 1 0 0 0 1
0 1 1 0 1 1 0 0 1 1 0 0 0 1 1 1 1 0 1 1 0
0 0 1 0 0 1 1 1 1 0 1 1 0 1 1 1 0 0 0 0 1
0 1 1 0 0 1 1 1 1 0 0 0 1 0 1 1 0 1 0 1 1
1 1 1 1 1 0 0 0 0 1 0 0 1 1 0 1 1 1 0 0 1
0 0 0 1 1 0 1 1 1 1 0 0 0 0 0 0 1 1 1 1 1
1 0 1 1 0 1 0 1 0 0 1 0 0 1 1 0 1 0 1 1 0
0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 1 1 0 0 1
0 0 0 1 0 0 1 1 0 1 0 1 0 1 1 0 0 1 1 0 1
0 0 0 0 1 1 1 0 1 0 1 1 1 0 1 1 0 0 1 1 0
1 1 0 1 1 0 0 1 1 0 1 1 0 1 1 1 1 1 0 1 0
1 0 0 1 1 0 1 1 1 1 1 0 1 0 1 1 0 0 0 0 0```

### 输出

```
102515160```

# 题解

## 作者：lwx20211103 (赞：24)

## 前言

AtCoder dp 练习题里的状态压缩 dp。

作为一个蒟蒻，不怎么理解洛谷翻译的意思，于是就回到 atc 去看看。

题目的翻译就是：

有 $N$ 名男生和 $N$ 名女生，编号均为 $1,2,\ldots,N$。

对于每一个 $i, j(1 \leq i, j \leq N)$，男人 $i$ 和女人 $j$ 的兼容性都是一个整数 $a_{i, j}$。若 $a_{i, j} = 1$，则男人 $i$ 和女人 $j$ 相容；若 $a_{i, j} = 0$，则不相容。

太郎试图做出 $N$ 对，每对都由相容的一男一女组成。在这里，每个男生和每个女人女生正好属于一对，不能出现~~脚踏两只船~~重复的男生和女生的情况。

求太郎能凑成 $N$ 对的方法的个数，答案对 $10^9 + 7$ 取模。

## 做法

题解里的大佬代码都贴出来了，但是解释的比较少，本篇题解就解释一下这个 dp。

首先看到 $1 \leq n \leq 21$，~~还有题目编号~~就明白这是一个状态压缩型动态规划的题目。

我们每次可以枚举 $i$ 个男生和当前集合 $j$ 中的女生的匹配数量，如果枚举成功，就更新答案和集合，答案要加上上一个集合的数量。

很显然，要满足两个条件，**一个是当前的男生和集合中的女生相容**，**一个是当前的男生和女生都没有被匹配过**。

以下是需要注意的点：

1. 让表示相容性的数组 $a$ 数组编号从 $0$ 开始，因为是状压 dp，并且在后面这回方便些。

2. 动态规划数组初始化为 $0$。

3. `__builtin_popcount(x)` 表示 $x$ 的二进制下 $1$ 的个数，在这里用 $cnt_x$ 表示。

我们设 $f[i][j]$ 为 $i$ 个男生和女生构成的集合 $j$ 的匹配数量，那么 $cnt_j$ 表示集合中已经有的女生，先枚举男生数量 $i$，在枚举集合 $j$，我们需要满足 $cnt_j = i$ 即女生数量等于男生数量才能继续往后更新。

这个时候我们再找一个女生 $k$，要满足当前的男生和这个女生匹配且女生不在集合中，即 $a_{i,k}=1$ 且 $j \cap k=0$。

更新 $f_{i+1,j \cup k}=f_{i+1,j \cup k}+f_{i,j}$。$j \cup k$ 表示更新后的集合，集合里加上了女生 $k$。

在更新完后结果就是 $f_{n,2^n-1}$，后者是子集的个数，因为我们枚举的是集合。

在代码中，集合用一个数字表示，因为是状态压缩。

在上文的 $j \cap k$ 在代码中就是 `j & (1 << k)`。怎么解释呢？`1 << k` 就是把 1 左边移 $k$ 位，和 $j$ 对齐，和 $k$ 进行按位与，根据与运算的性质。就能判断那一位是否为 $1$ 了。并集就把与运算变为或运算。

当前的 AC code：（数组 $a$ 根据我的习惯换成了 $nums$）

```cpp
bool nums[50][50];

ll f[50][1 << 22];

const ll mod = 1e9 + 7;

int main()
{
	int n;
	cin >> n;	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> nums[i][j];
	f[0][0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < (1 << n); j++)
			if (__builtin_popcount(j) == i)
				for (int k = 0; k < n; k++)
					if (nums[i][k] && (j & (1 << k)) == 0)
						f[i + 1][j | (1 << k)] = 
						(f[i + 1][j | (1 << k)] + f[i][j]) % mod;
	cout << f[n][(1 << n) - 1];
	return 0;
}

```

------------

其实事情还没有结束，我们发现 $f_{i+1,j}$ 只跟前面的 $f_{i, j'}$ 有关。就是当前状态之和上一个有关。我们又可以优化成一维数组，时间复杂度也得到降低。

```cpp
// Problem: Matching
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_dp_o
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define p_b push_back
#define ft first
#define nd second
#define pii pair<int, int>
#define pll pair<long long, long long>

using namespace std;

typedef long long ll;

bool nums[50][50];

ll f[50][1 << 22];
ll dp[1 << 22];

const ll mod = 1e9 + 7;

int main()
{
	int n;
	cin >> n;	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> nums[i][j];
	dp[0] = 1;
	for (int j = 0; j < (1 << n); j++)
	{
		int cnt = __builtin_popcount(j);
		for (int i = 0; i < n; i++)
		{
			if (nums[cnt][i] && (j & (1 << i)) == 0)
				dp[j | (1 << i)] = (dp[j | (1 << i)] + dp[j]) % mod;
		}
	}
	cout << dp[(1 << n) - 1];
	return 0;
}

```
我们先枚举集合 $j$，得到 $cnt_j$，因为数组从 $0$ 开始，那么 $nums_{cnt_j,i}$ 因为这个特性枚举的其实是下一个，这样就变得简便了。

在这里我们直接枚举集合，再枚举人数，复杂度得到了降低。

## 结尾

码字不易，谢谢大家的观看，觉得有用可以点赞支持，如果有疑惑之处或者本文错误的地方可以评论说出来。

---

## 作者：zhlzt (赞：15)

### 题目

- 有 $n$ 个男人和 $n$ 个女人。
- 已知每个男人和每个女人是否可以配对。
- 要求配成 $n$ 对，每对一男一女。
- 求方案数 $\bmod~10^9+7$。
- $1\le n\le 21$.

### 状态压缩 DP 做法
	
我们设一个集合 $S$，$t=|S|$ 且里面只包含若干个女人的编号，定义一个数组 $dp_{S}$，表示前 $t$ 个男人与 $S$ 中的女人匹配的方案数，可以枚举第 $t$ 个男人和哪个女人匹配，很明显，状态转移方程为：
$$dp_S=\sum dp_{S-i}(i\in S~\text{and}~a_{t,i}=1)$$
当然，表示一个集合 $S$ 太复杂了，我们可以把它转化为一个 $n$ 位二进制数，从右往左的第 $i$ 位如果为 $1$，表示集合中有编号为 $i$ 的女人，否则表示没有。那么状态转移方程就变为：
$$dp_S=\sum dp_{S-{2^{i-1}}}(\left\lfloor\frac{S}{2^{i-1}}\right\rfloor\bmod 2=1~\text{and}~a_{t,i}=1)$$
枚举所有集合，设集合为 $S$、$t=|S|$，枚举第 $t$ 个男人和哪个女人匹配，复杂度为 $O(n2^n)$，$n$ 只有 $21$，不会 `TLE`。

代码中要用到一些 C++ 常用的位运算符，详见 <https://blog.csdn.net/digitalkee/article/details/117634604>。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,a[22][22],dp[1<<21];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	dp[0]=1;//集合里没有女人，肯定也没有男人，方案数为 1
	for(int S=1;S<1<<n;S++){
		int S2=S,t=0;
		while(S2>0) t+=(S2&1)?1:0,S2>>=1;//求有多少个女人，有多少个女人就有多少个男人
		for(int i=1;i<=n;i++)
			if(a[t][i]==1&&(S>>i-1)&1)//判断第 t 个男人是否能和第 i 个女人匹配且集合中有这个女人
				dp[S]=(dp[S]+dp[S-(1<<i-1)])%mod;
	}
	printf("%d",dp[(1<<n)-1]);
	return 0;
}
```

---

## 作者：DengDuck (赞：5)

这是一道状态压缩 DP。

我们设 $f_{i,j}$ 表示左边部分的前 $i$ 个点匹配右边集合为 $j$ 的点的方案数。

则可得方程：
$$
f_{i,j}=\sum_{k\in j,a_{i,k}=1} f_{i-1,j-k}
$$
也就是我们枚举 $i$ 选择的点 $k$ ,这种选法的贡献就是前 $i-1$ 个点选择右边 $j$ 集合除掉 $k$ 的点的方案数。

注意到这里出现了集合的概念，显然实现时难以表示，我们可以转换为一个二进制数。

这个二进制数可以看作是一个布尔数组，第 $i$ 位表示右边第 $i$ 的点是否被选中。

这样集合除去的操作可以用二进制中的异或完成。

但是这样还是会超时，注意到方程中的 $i$ 等于 $j$ 的二进制中的 $1$ 的个数，所以直接枚举状态，找出对应的 $i$ 即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=(1<<21); 
const LL mod=1e9+7; 
LL n,a[22][22],f[22][N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	f[0][0]=1;
	for(int j=1;j<N;j++)
	{
		LL cnt=0;
		for(int i=1;i<=n;i++)cnt+=(j>>(i-1))&1;
		for(int i=1;i<=n;i++)
		{
			if((j>>(i-1))&1==0)continue;
			if(a[cnt][i])
			{
				f[cnt][j]=(f[cnt][j]+f[cnt-1][j^(1<<(i-1))])%mod;
			}
		}
	}
	cout<<f[n][(1<<n)-1];
}
```



---

## 作者：Ray662 (赞：5)

[洛谷 传送门](https://www.luogu.com.cn/problem/AT_dp_o) | [AtCoder 传送门](https://atcoder.jp/contests/dp/tasks/dp_o)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-at-dp-o)

题目大意：

- 有 $n$ 个男人和 $n$ 个女人，编号都是 $1 \sim n$。

- 对于每个 $i, j$（$1 \le i, j \le n$），给定男人 $i$ 和女人 $j$ 的相容性 $a_{i, j}$。若 $a_{i, j} = 1$，$i$ 和 $j$ 就是相容的，否则不相容。

- 计算把所有男人和女人分成 $n$ 对，每队包含一个男人和一个女人的方案数（对 $10^9 + 7$ 取模）。

- $n \le 21$。

---

### 分析

- $n$ 只有 $21$，考虑状态压缩。

- 定义 $f(\{st\})$：包含在 $st$ 中的女人和前 $|st|$ 个男人配对的方案数，则有：

$$
f(\{st\}) = \sum f(\{st\} - \{x\})
$$

其中，$|st|$ 表示 $st$ 的二进制表示中 $1$ 的个数，$|st|$ 和 $x$ 相容。

- 初始化：$f(\{\}) = 1$，$\{\}$ 表示空集。

---

总体复杂度：$O(n \times 2^n)$。

说明：`__builtin_popcount(x)` 返回的是 $x$ 的二进制表示中 $1$ 的个数。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 25, P = 1e9 + 7;
int n, a[N][N], f[1 << N];
int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i ++ )
		for (int j = 0; j < n; j ++ )
			cin >> a[i][j];
	f[0] = 1;  // DP 初始化
	for (int st = 0; st < (1 << n); st ++ ) {  /// 枚举每个状态
		int k = __builtin_popcount(st);  // 二进制表示中 1 的个数
		for (int w = 0; w < n; w ++ )
			if (! (st & (1 << w)) && a[k][w])  // 如果 w 不在集合中且相容
				(f[st | (1 << w)] += f[st]) %= P;  // 转移
	}
	cout << f[(1 << n) - 1] << endl;
	return 0;
}
```

---

## 作者：Pozhu (赞：5)

这题竟然没有人写记忆化搜索的题解。

这个做法或许能给这个题降个难度等级（。

考虑转化问题，发现一个完备匹配等价于在邻接矩阵上每行每列恰有一个值为 $1$。

而且 $n$ 很小，于是可以状压来记忆化。

具体而言，一个数 $s$ 的二进制位表示对应的列中有没有出现过 $1$，此时上边的行与行之间并没有区别，我们把这些行的状态压到一起。

然后我们枚举当前行的每一位，如果这一位的邻接矩阵为 $1$ 且在之前的状态中这一列并没有出现过 $1$，我们就把他填成 $1$，累加入当前行的答案。

复杂度和状压做法大致相同，因为涉及到的有效状态集合也几乎相同。


```cpp
#include<bits/stdc++.h>
namespace Pozhu{
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
#define N 30

int n;
int mp[N][N];
int f[N][1 << 22];

int dfs(int pos,int sta);

void main()
{
	ios :: sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)
	for(int j = 1;j <= n;j++)
		cin >> mp[i][j];
	memset(f,-1,sizeof(f));
	cout << dfs(0,0);
	return;
}

int dfs(int pos,int sta)
{
	//个人写dfs的习惯中pos表示已经处理完了前pos行
	if(f[pos][sta] != -1) return f[pos][sta]; // 记忆化数组
	if(pos == n)
	{
		return (sta == (1 << n)-1);
	}
	int ans = 0;
	for(int i = 1;i <= n;i++)
	{
		if(mp[pos+1][i] && !(sta >> (i-1) & 1)) 
        	ans = (ans + dfs(pos+1,sta|(1 << i-1))) % mod;
	}
	return f[pos][sta] = ans;
}

}

signed main()
{
    Pozhu :: main();
    return 0;
}
```

---

## 作者：Doqin07 (赞：5)


### 思路: **状压dp**
#### 我们设$dp[i][j]$表示已经考虑了节点 $\{0,1,2,3,....,i \}$,右侧所用的点表示为$mask$.
#### 转移:对于$dp[i][j]$,枚举节点$i$的所有邻居$j$,如果$mask$中含有$j$的话,方案数就加上$dp[i-1][mask-(i<<j]$.
#### 更一步的, $\{0,1,2,3,....,i \}$一共有$i$+1个节点，所以只有$mask$中一的数量等于$i$+1的时候状态才会有意义.于是我们只需要保留$mask$这一堆，另一维可以直设置为 __builtin_popcount(mask)-1,此函数表示为二进制中$1$的数量。
### 最后别忘记对$10^9+7$取模


------------

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 21;
int n, connected[105][105], dp[1 << N];
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n ; ++j)
            cin >> connect[i][j]; //直接拿邻接矩阵存图即可
    dp[0] = 1;
    for (int mask = 1; mask < (1 << n); ++mask)
    {
        int i = __builtin_popcount(mask) - 1;
        for (int j = 0; j < n; ++j)
            if (connected[i][j] && (mask & (1 << j)) != 0)      
                dp[mask] = (dp[mask] % mod + dp[mask - (1 << j)] % mod) % mod;
    }
    cout << dp[(1 << n) - 1] % mod << endl;
    return 0;
}

```


---
## 求过QwQ

---

## 作者：AmamiyaYuuko (赞：3)

考虑状压 DP，设 $f(i, S)$ 为 $A$ 中 $i$ 个人跟 $S$ 匹配的方案数，如果要转移的话，那么必须满足 $S$ 中 $1$ 的数量等于 $i$（满足两两匹配）。

考虑转移：我们找到一个 $j$，使得 $i$ 到 $j$ 有边并且 $j$ 当前没有匹配过，更新 $f(i + 1, S \cup j)$，这样就找到了一组新的匹配。

答案即为 $f(n, 2^n - 1)$，边界 $f(0, 0) = 1$。

一些注意的点：

- 状压时数组不能随便开

- 编号从 $0$ 开始比较方便

- 取模

- 位运算优先级

代码：

```cpp
int main() {
    read(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            read(g[i][j]);
        }
    }
    f[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= (1 << n) - 1; ++j) {
            if (__builtin_popcount(j) == i) {
                for (int k = 0; k < n; ++k) {
                    if (g[i][k] && ((j & (1 << k)) == 0)) {
                        f[i + 1][j | (1 << k)] += f[i][j] % mod;
                        f[i + 1][j | (1 << k)] %= mod;
                    }
                }
            }
        }
    }
    printf("%lld\n", f[n][(1 << n) - 1] % mod);
    return 0;
}
```

---

## 作者：12345678hzx (赞：2)

## 题意
求二分图完备匹配数。
## 思路
首先 $N\le 21$，想到状压。

设 $f_{i,S}$ 表示前 $i$ 个点，集合为 $S$ 的点已被匹配时的方案数，枚举上一个被匹配的点 $j$，转移方程为:

$$f_{i,S}=\sum f_{i-1,S-j}(j\in S \operatorname{and} a_{x,j}=1)$$

容易发现 $i$ 其实就是 $\operatorname{popcount}(S)$，于是就可以压掉一维。

直接转移即可，时间复杂度为 $O(n2^n)$，空间复杂度为 $O(2^n)$。

代码很短，就不给了，如果实在需要可以私信我。

---

## 作者：huangrenheluogu (赞：1)

[题目](https://www.luogu.com.cn/problem/AT_dp_o)。

$n\le21$，一眼状压 dp。

我们可以钦定从前往后选，这样可以避免不同选择方式算重。

第 $i$ 个点，枚举状态，枚举到的下一个点，复杂度 $O(n^22^n)$，听说可以过，理论不可行。

考虑优化，由于第 $i$ 个点选择的时候，状态里必须恰有 $i-1$ 个点，可以预处理。

~~管理要写转移方程，赶紧补救一下：~~

$s$ 转移到 $t$，加入第 $j$ 个点（从 $1$ 开始标号）。

需要满足 `t = s | (1 << j - 1), (s >> j)  == 0`。

转移方程：$f_t=\sum\limits_{s\rightarrow t}f_i$，$s\rightarrow t$ 指 $s$ 可以转移到 $t$。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 22, mod = 1e9 + 7;
int n, f[1 << N - 1], a[N][N];
vector<int>g[N];
inline int calc(int x){
	int res = 0;
	while(x){
		res++;
		x &= x - 1;
	}
	return res;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &a[i][j]);
		}
	}
	f[0] = 1;
	for(int s = 0; s < 1 << n; s++){
		g[calc(s)].push_back(s);
	}
	for(int i = 1; i <= n; i++){
		for(auto s : g[i - 1]){
			for(int j = 1; j <= n; j++){
				if(a[i][j] == 0 || (s & (1 << j - 1))) continue ;
				f[s | (1 << j - 1)] += f[s];
				f[s | (1 << j - 1)] %= mod;
			}
		}
	}
	printf("%d", f[(1 << n) - 1]);
	return 0;
}
```

---

## 作者：白简 (赞：1)

### 题目大意 

给定 $n$ 个男人和 $n$ 个女人，编号分别为 $1 \sim n$。

对于每个 $i,j(1 \leq i,j \leq n)$，给定男人 $i$ 和女人 $j$ 的相容性 $a_{i,j}$，相容性为 $1$ 表示 $i$ 与 $j$ 是相容的，否则不相容。

考虑把男女两两配对，每对有且仅有一个男人和一个女人，当所有人都在一组匹配里，这样的方案是合法的。

求合法匹配方案数，答案对 $10^9 + 7$ 取模。

### 思路

看数据范围考虑状压 DP。

设 $dp_S$ 表示集合 $S$ 中的男人和前 $\left| S \right|$ 个女人配对的方案数。

设 $\operatorname{popcount}(S)$ 表示 $S$ 二进制表示中 $1$ 的个数，那么有

$$dp_S = \sum dp_{\operatorname{popcount}(S) - x}$$ 

### Code

```cpp
dp[0] = 1;
for(int s = 1;s < (1 << n); s++) {
    int t = 0,tmp = s;

    while(tmp > 0) {
        if(tmp & 1)
            t ++;
        tmp >>= 1; 
    }

    for (int i = 1;i <= n; i++)
        if(e[t][i] && (s >> (i - 1)) & 1)
            dp[s] = (dp[s] + dp[s - (1 << (i - 1))]) % Mod;
}
```

---

## 作者：Leowang2009 (赞：1)

# 思路

状压 dp 板子题。

看到数据范围 $1 \leq\ N \leq\ 21$，容易想到用状压 dp。

先是 dp 的过程。

设所选女性集合为 $T$，且 $k=|T|$，记此时答案数为 $f_T$，则有转移方程：

$$f_T = \sum\limits_{i \in\ S \land\ a_{k,i}=1}f_{T-i}$$

接着是状压的部分。

将一个状态对应一个数，对于编号为 $k$ 的女性，若被已选择，则代表该状态的二进制表示中第 $k$ 位为 1，反之则为 0。

由此易得状态总数量为 $2^N$，由于每种状态要进行 $N$ 轮枚举，总体时间复杂度为 $O(N \times\ 2^N)$，由于 $1 \leq\ N \leq\ 21$，故不会超时。

# 代码

一定要记得取模。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,g[25][25],f[1<<21],opt;
int main(){
	scanf("%d",&n);
	const int s=(1<<n)-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",g[i]+j);//输入
	f[0]=1;//初始化
	for(int i=1,cnt=1;i<=s;i++,cnt=__builtin_popcount(i))//枚举每一种状态
		for(int j=1;j<=n;j++)//枚举每一位
			if(i&(1<<(j-1))&&g[cnt][j])//判断是否可以转移
				f[i]=(f[i]+f[i^(1<<(j-1))])%mod;//一定要取模
	printf("%d",f[s]);//输出最终状态
	return 0;
}
```
完结撒花！

---

## 作者：Moeebius (赞：1)

## Analysis
对于这种~~一眼看过去不可做~~ $n\le23$ 的题目，我们有一个相似的思路：状压 $\mathtt{DP}$
。

考虑设计状态。定义 $f_{i,S}$ 为 左侧点已经考虑到了第 $i$ 个，右侧点选了集合的**二进制表示**为 $S$ 的方案数。为了方便起见，我们可以将编号设置为从 $0$ 开始。

> 例如，右边选 $0,1,3$ 三个点，$S$ 就为 $(1011)_2$，即 $11$。

考虑转移。显然，$f_{i,S}=\displaystyle\sum_{j\in S \And (i,j)\in E} f_{i-1,S\oplus j}$

此时空间复杂度是 $O(n2^n)$ 的，考虑优化。

发现只有当 $i=|S|$ 时转移才有意义。于是我们就可以压掉第一维，直接枚举 $S$，并将 $i\leftarrow \mathtt{\_\_builtin\_popcount(S)}-1$。

> ```__builtin_popcount(x)``` 是一个 GNU 自带的函数，返回值为 $x$ 二进制中 $1$ 的个数。**之所以要减 $1$ 是因为编号从 $0$ 开始。**

边界值：$f_{0}=1$。

最后答案即为 $f_{2^n-1}$。

## Code

```cpp
int f[1<<21],n;
int con[22][22];//矩阵式存图已经足够。
const int mod = 1e9+7;

signed main()
{
	read(n);
	For(i,0,n-1)
	For(j,0,n-1)
		read(con[i][j]);
	f[0]=1;
	For(S,1,(1<<n)-1)
	{
		int i = __builtin_popcount(S);
		For(j,0,n-1)
			if(con[i][j] && (S & (1<<j))!=0)
				f[S]=(f[S]+f[S-(1<<j)])%mod;
	}
	cout<<f[(1<<n)-1]<<endl;
	return 0;
}
```

---

## 作者：云浅知处 (赞：1)

[题目 Link](https://atcoder.jp/contests/dp/tasks/dp_o)

考虑状压：设 $f(i,S)$ 为选前 $i$ 个少年以及集合 $S$ 中的妹子的匹配个数。

这里我们只考虑 $|S|=i$，因为其他的显然都是 $0$。

转移时枚举 $i$ 和 $S$ 中的哪个妹子匹配了，那么转移方程就是：

$$
f(i,S)=\sum_{x\in S}[a_{i,x}==1]\cdot f\big(i-1,S\setminus\{x\}\big)
$$

时间复杂度看上去是 $O(n^22^n)$，不过实际地复杂度其实是这样的一个东西：

$$
\sum_{S\subseteq \{1,2,\cdots,n\}}|S|=\sum_{i=0}^n i\cdot C_{n}^i=n2^{n-1}
$$

这是因为大部分状态是无用的，转移也只需要 $O(|S|)$ 的时间。

所以我们的时间复杂度实际为 $O(n2^n)$，对于 $n\le 21$ 随便就过了。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>

#define int long long
const int mod=1e9+7;
const int MN=(1ll<<22);

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

int dp[25][MN],n,a[25][MN];

int lowbit(int x){return x&(-x);}
int popcnt(int x){
    int cnt=0;
    while(x)x=(x&(x-1)),cnt++;
    return cnt;
}

signed main(void){

    n=read();
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>a[i][1<<j];
    for(int i=0;i<n;i++)dp[0][1<<i]=a[0][1<<i];
    for(int i=1;i<n;i++){
        for(int S=(1<<(i+1))-1;S<(1<<n);S+=lowbit(S)){
            S+=(1<<(i+1-popcnt(S)))-1;
            for(int S0=S;S0;S0=(S0&(S0-1))){
                dp[i][S]=(dp[i][S]+dp[i-1][S^lowbit(S0)]*a[i][lowbit(S0)])%mod;
            }
        }
    }
    cout<<dp[n-1][(1<<n)-1]%mod<<endl;

    return 0;
}
```

---

