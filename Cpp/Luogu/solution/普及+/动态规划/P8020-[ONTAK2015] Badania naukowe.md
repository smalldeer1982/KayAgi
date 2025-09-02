# [ONTAK2015] Badania naukowe

## 题目描述

给定三个数字串 $A, B, C$，请找到一个 $A, B$ 的最长公共子序列，满足 $C$ 是该子序列的子串。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n,m \leq 3 \times 10^3$，$0 \leq k \leq 3 \times 10^3$。

## 样例 #1

### 输入

```
7
1 2 2 3 1 1 2
6
1 2 1 3 1 2
2
3 2```

### 输出

```
4```

# 题解

## 作者：Coros_Trusds (赞：14)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15864290.html)

$\rm DP$ 好题。

# 题目大意

给定三个数字串 $A,B,C$，请找到一个 $A,B$ 的最长公共子序列，满足 $C$ 是该子序列的子串。

# 题目分析

**本题解中数组下标均从 $1$ 开始。**

初见此题，我们对答案毫无头绪，不妨考虑答案是由什么构成的。

我们枚举 $C$ 在 $A,B$ 中的位置，再加上前后各自的最长公共子序列长度。

设 $n,m,k$ 分别表示 $A,B,C$ 序列的长度。

令 $dp1[i][j]$ 表示 $a[1\dots i]$ 和 $b[1\dots j]$ 的最长公共子序列长度，$dp2[i][j]$ 表示 $a[i\dots n]$ 和 $b[j\dots m]$ 的最长公共子序列长度。

我们先处理出 $dp1$ 和 $dp2$，处理步骤见 $\verb!P1439!$。

特别地，当 $C$ 序列的长度为 $0$ 时，答案为 $dp1[n][m]$。（$20$ 分到手了）

好了，现在答案中“前后各自的最长公共子序列长度”求出来了。

------

处理出 $ta$ 和 $tb$ 数组，$ta[i]$ 表示 $C$ 是否在 $a[i\dots n]$ 中出现（不一定连续），如果出现了的话 $ta[i]$ 存储 $C$ 的最后一个元素在 $A$ 中的下标，否则为 $0$。

$tb[i]$ 表示 $C$ 是否在 $b[i\dots m]$ 中出现（不一定连续），如果出现了的话 $tb[i]$ 存储 $C$ 的最后一个元素在 $B$ 中的下标，否则为 $0$。

最后答案即为 $\max\{dp1[i-1][j-1]+k+dp2[ta[i]+1][tb[j]+1]\}(1\le i\le n,1\le j\le m)$。

# 代码

```cpp
const int ma=3e3+5;

int a[ma],b[ma],c[ma];

int ta[ma],tb[ma];

int dp1[ma][ma],dp2[ma][ma];
//dp1[i][j]:LCS(a[1...i],b[1...j])
//dp2[i][j]:LCS(a[i...n],b[j...m])

int n,m,k;

inline void work1()
{
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=m;j++)
		{
			if(a[i]==b[j])
			{
				dp1[i][j]=dp1[i-1][j-1]+1;
			}

			else
			{
				dp1[i][j]=max(dp1[i-1][j],dp1[i][j-1]);
			}
		}
	}

	if(k==0)
	{
		printf("%d\n",dp1[n][m]);

		exit(0);
	}
}

inline void work2()
{
	for(register int i=n;i>=1;i--)
	{
		for(register int j=m;j>=1;j--)
		{
			if(a[i]==b[j])
			{
				dp2[i][j]=dp2[i+1][j+1]+1;
			}

			else
			{
				dp2[i][j]=max(dp2[i+1][j],dp2[i][j+1]);
			}
		}
	}
}

int main(void)
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif

	n=read();Input_Int(n,a);

	m=read();Input_Int(m,b);

	k=read();Input_Int(k,c);

	work1(),work2();

	for(register int i=1;i<=n;i++)
	{
		for(register int j=i,t=1;j<=n;j++)
		{
			if(a[j]==c[t])
			{
				t++;
			}

			if(t>k)
			{
				ta[i]=j;

				break;
			}
		}
	}
	
	for(register int i=1;i<=m;i++)
	{
		for(register int j=i,t=1;j<=m;j++)
		{
			if(b[j]==c[t])
			{
				t++;
			}

			if(t>k)
			{
				tb[i]=j;

				break;
			}
		}
	}

	int ans=-1;

	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=m;j++)
		{
			if(ta[i]!=0 && tb[j]!=0)//如果没出现就别考虑了
			{
				ans=max(ans,dp1[i-1][j-1]+k+dp2[ta[i]+1][tb[j]+1]);
			}
		}
	}

	printf("%d\n",ans);

	return 0;
}
```

# 题外话

各位读者 dalao 如果觉得这篇文章有用不妨点个赞吧qwq。

---

## 作者：forever_nope (赞：2)

注意到我们要求答案一定存在 $C$ 这个子串。

因此，我们考虑枚举 $C$ 是在 $A,B$ 的哪一个位置出现的。

---

我们使用 $P(i)$ 表示从 $A_i$ 开始匹配 $C$，到最后一个字符的下标 $j$，图解：

$$
\begin{aligned}
\begin{aligned}
i\kern{11.5ex}j\kern{1.7ex}
\end{aligned}\\[-1ex]
\begin{array}{l:l}
A&\texttt{x\dots axbxxcdxxxe}\\
C&\kern{4ex}\boxed{\texttt{a\ b\ \ cd\ \ \ e}}
\end{array}
\end{aligned}
$$

同理，使用 $Q(i)$ 表示从 $B_i$ 开始匹配 $C$，最后一个字符的下标 $j$。

---

于是，我们枚举 $i,j$ 分别表示 $C$ 从 $A_i,B_j$ 开始。

那么，如果从 $i,j$ 开始可以匹配到完整的 $C$ 字符串，那么这个状态就是合法的。

考虑如何表示答案？

---

设 $F(i,j)$ 表示 $A[1,i]$ 和 $B[1,j]$ 的 LCS（最长公共子序列）。

设 $G(i,j)$ 表示 $A[i,n]$ 和 $B[j,m]$ 的 LCS（最长公共子序列）。

那么，答案可以表示为，

$$
\max_{i,j}\{
F(i-1,j-1)+G(P(i)+1,Q(j)+1)+\lvert C\rvert,
\text{if $\langle i,j\rangle$ is valid.}
\}
$$

也就是前面的和后面的 LCS 可以直接计入答案，再加上子串 $C$ 的长度。

---

如何求 LCS（最长公共子序列）。

以 $F(i,j)$ 为例，有状态转移方程，

$$
F(i,j)=\begin{cases}
F(i-1,j-1)+1&A_i=B_j\\
\max\{F(i,j-1),F(i-1,j)\}&A_i\neq B_j
\end{cases}
$$

表示如果相同，则加入 LCS，否则删去一个继续匹配。

反过来，

$$
G(i,j)=\begin{cases}
G(i+1,j+1)+1&A_i=B_j\\
\max\{G(i,j+1),G(i+1,j)\}&A_i\neq B_j
\end{cases}
$$

同理的。

---

合起来就行了，核心代码：

```cpp
constexpr int N = 3e3 + 10;

void init_matching(int n, int *A, int k, int *C, int *P) {
	for (int i = 1; i + k - 1 <= n; ++i) {
		int p = i, q = 1;
		while (p <= n && q <= k) {
			q += (A[p] == C[q]);
			++p;
		}
		P[i] = (q > k) ? p - 1 : 0;
	}
}

int n, A[N], P[N];
int m, B[N], Q[N];
int k, C[N];
int F[N][N], G[N][N];

void init_LCS() {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (A[i] == B[j])
				F[i][j] = F[i - 1][j - 1] + 1;
			else
				F[i][j] = max(F[i][j - 1], F[i - 1][j]);
}

void init_rLCS() {
	for (int i = n; i >= 1; --i)
		for (int j = m; j >= 1; --j)
			if (A[i] == B[j])
				G[i][j] = G[i + 1][j + 1] + 1;
			else
				G[i][j] = max(G[i][j + 1], G[i + 1][j]);
}

int get_ans() {
	int Ans = -1;
	for (int i = 1; i + k - 1 <= n; ++i)
		for (int j = 1; j + k - 1 <= m; ++j)
			if (P[i] && Q[j])
				Ans = max(Ans, F[i - 1][j - 1] + G[P[i] + 1][Q[j] + 1] + k);
	return Ans;
}

void Main() {
	cin >> n;
	copy_n(istream_iterator<int>(cin), n, A + 1);
	cin >> m;
	copy_n(istream_iterator<int>(cin), m, B + 1);
	cin >> k;
	copy_n(istream_iterator<int>(cin), k, C + 1);
	init_matching(n, A, k, C, P);
	init_matching(m, B, k, C, Q);
	init_LCS(), init_rLCS();
	cout << get_ans() << endl;
}
```

---

## 作者：_EternalRegrets_ (赞：1)

## P8020 题解

### 题意描述

>给定三个数字串 $A, B, C$，请找到一个 $A, B$ 的最长公共子序列，满足 $C$ 是该子序列的子串。



---
### Solution:

最长公共子序列，自然可以想到动态规划。

因为 $A,B$ 的 $\operatorname{LCS}$ 中需要含有 $C$ 子串，不妨直接从 $A,B$ 中直接去找子序列 $C$。

简单 $O(n^2)$ 预处理。

处理了 $\operatorname{LCS}$ 中需要含有 $C$ 的问题之后，接下来就是两个标准的 $\operatorname{LCS}$ 了：**$A$ 在数组中的 $C$ 之前的部分** 和 **$B$ 在数组中的 $C$ 之前的部分** 做 $\operatorname{LCS}$；**$A$ 在数组中的 $C$ 之后的部分** 和 **$B$ 在数组中的 $C$ 之后的部分** 做 $\operatorname{LCS}$。

直接正序、倒序各做一次 $A$ 和 $B$ 的 $\operatorname{LCS}$ 即可。

具体见代码。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[3005];
int b[3005];
int c[3005];
int dp1[3005][3005];
int dp2[3005][3005];
int aa[3005];
int bb[3005];

int main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}

	int m; cin>>m;
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}

	int k; cin>>k;
	for(int i=1;i<=k;i++){
		cin>>c[i];
	}
	
	for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
	        dp1[i][j]=max(dp1[i-1][j],dp1[i][j-1]);
	        
	        if(a[i]==b[j]){
	        	dp1[i][j]=max(dp1[i][j],dp1[i-1][j-1]+1);
			}
	    }
	}
	
	for(int i=n;i>=1;i--){
    	for(int j=n;j>=1;j--){
	        dp2[i][j]=max(dp2[i+1][j],dp2[i][j+1]);
	        if(a[i]==b[j]){
	        	dp2[i][j]=max(dp2[i][j],dp2[i+1][j+1]+1);
			}
	    }
	}
	
	for(int i=1;i<=n;i++){
        int cnt=1;
		aa[i]=i-1;
        
        while(cnt<=k && aa[i]<n){
            aa[i]++;
            if(a[aa[i]]==c[cnt]){
            	cnt++;
			}
        }
        
        if(cnt<=k){
        	aa[i]=-1;
		}
    }
    
    for(int i=1;i<=m;i++){
        int cnt=1;
		bb[i]=i-1;
        
        while(cnt<=k && bb[i]<m){
            bb[i]++;
            if(b[bb[i]]==c[cnt]){
            	cnt++;
			}
        }
        
        if(cnt<=k){
        	bb[i]=-1;
		}
	}

	int ans; ans=0;
	for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
	    	if(aa[i]!=-1 && bb[j]!=-1){
		        ans=max(ans,k+dp1[i-1][j-1]+dp2[aa[i]+1][bb[j]+1]);
		    }
		}
	}
	
	if(ans==0){
		cout<<-1;
		return 0;
	}
	
	cout<<ans;
	return 0;
}
```

---

## 作者：SolIII (赞：0)

## 前言

[更好的阅读体验](https://www.luogu.com.cn/article/bb2l9d23)

依然是模拟赛的 T3，依然寄了，所以写篇题解……

## 题目分析

### 简化题意

原题面可能给的不太清晰（至少我个人看了好久才看懂）。

有三个数字串 $A$ 和 $B$ 和 $C$，你需要找到一个 $A$ 和 $B$ 的公共子序列 $D$，使得它在满足 $C$ 是 $D$ 的子串的情况下尽可能地长。

### 思路

设所求的公共子序列为 $D$，考虑将 $D$ 分成三个部分：

1. $A$ 与 $B$ 前半部分的公共子序列，这个部分可以用经典的最长公共子序列算法来预处理。
2. 为 $C$ 的子串，这个部分可以遍历匹配。
3. $A$ 与 $B$ 后半部分的公共子序列，与部分 $1$ 相似，这个部分可以用经典的最长公共子序列算法来预处理，但注意为方便枚举，要倒着 dp（即 $dp_{i, j}$ 表示 $A$ 的第 $i$ 位到第 $n$ 位与 $B$ 的第 $j$ 位到第 $m$ 位的最长公共子序列）。

考虑在 $A$ 和 $B$ 中分别枚举其子序列的三个部分的两个分割点，然后求这三个部分长度之和，答案即所有的情况中长度之和的最大值，时间复杂度 $O(n ^ 4)$。

考虑优化，发现若存在分割点的方案 $(l_1, r_1, l_2, r_2)$ 可以使得 $A$ 的 $[l_1, r_1]$ 与 $B$ 的 $[l_2, r_2]$ 的公共子序列为 $C$，另一种满足 $r_1' \ge r_1$ 且 $r_2' \ge r_2$ 的方案 $(l_1, r_1', l_2, r_2')$  的答案一定没有 $(l_1, r_1, l_2, r_2)$ 优。因为相较于第一种方案来说，第二种第 $3$ 部分的长度短了而且第 $1$ 第 $2$ 部分的长度都没有增加。

所以我们可以预处理出两个数组 `nextA` 和 `nextB`。$nextA_i$ 表示在 $A$ 中，使区间 $[i, r]$ 存在为 $C$ 的子序列的最小的 $r$，$nextB_i$ 同理。枚举分割点时，我们就可以只枚举 $A$ 和 $B$ 中第 $1$ 部分与第 $2$ 部分的分割点，从而 $O(1)$ 得到 $A$ 和 $B$ 中最优的第 $2$ 部分与第 $3$ 部分的分割点，时间复杂度 $O(n ^ 2)$，可以通过本题的数据。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR = 3e3;
int dp[2][NR + 10][NR + 10]; // 最长公共子序列 dp 数组
int a[NR + 10];              // A 数列
int b[NR + 10];              // B 数列
int c[NR + 10];              // C 数列
int nxt[2][NR + 10];         // nextA 数组和 nextB 数组
void init(int n, int m, int len){ // 预处理函数
    for(int i = 1;i <= n;i++){    // A 与 B 前半部分的公共子序列, 用经典的最长公共子序列算法来计算
        for(int j = 1;j <= m;j++){
            if(a[i] == b[j]) dp[0][i][j] = max(dp[0][i][j], dp[0][i - 1][j - 1] + 1);
            dp[0][i][j] = max(dp[0][i][j], max(dp[0][i - 1][j], dp[0][i][j - 1]));
        }
    }
    for(int i = n;i >= 1;i--){    // A 与 B 后半部分的公共子序列, 注意要倒着 dp
        for(int j = m;j >= 1;j--){
            if(a[i] == b[j]) dp[1][i][j] = max(dp[1][i][j], dp[1][i + 1][j + 1] + 1);
            dp[1][i][j] = max(dp[1][i][j], max(dp[1][i + 1][j], dp[1][i][j + 1]));
        }
    }
    for(int i = 1;i <= n;i++){                // 预处理上文提到的 nextA 数组
        int pos = 1, j;
        for(j = i;j <= n && pos <= len;j++){  // 遍历匹配
            if(a[j] == c[pos]) pos++;
        }
        if(pos > len) nxt[0][i] = j - 1;      // 存在
        else nxt[0][i] = 0x3f3f3f3f;          // 不存在, 注意要设为无穷大
    }
    for(int i = 1;i <= m;i++){                // 预处理上文提到的 nextB 数组, 原理与 nextA 相同
        int pos = 1, j;
        for(j = i;j <= m && pos <= len;j++){
            if(b[j] == c[pos]) pos++;
        }
        if(pos > len) nxt[1][i] = j - 1;
        else nxt[1][i] = 0x3f3f3f3f;
    }
}

int main(){
    int n, m, len;
    scanf("%d", &n); // 读入
    for(int i = 1;i <= n;i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for(int i = 1;i <= m;i++){
        scanf("%d", &b[i]);
    }
    scanf("%d", &len);
    for(int i = 1;i <= len;i++){
        scanf("%d", &c[i]);
    }
    init(n, m, len); // 预处理上文提到的两段最长公共子序列和 next 数组
    int Max = 0;
    for(int l1 = 1;l1 <= n;l1++){                                                 // 枚举 A 中第 1/第 2 部分的分界线
        for(int l2 = 1;l2 <= m;l2++){                                             // 枚举 B 中第 1/第 2 部分的分界线
            int r1 = nxt[0][l1];                                                  // A 中第 2/第 3 部分最优的的分界线
            int r2 = nxt[1][l2];                                                  // B 中第 2/第 3 部分最优的的分界线
            if(r1 > n || r2 > m) continue;                                        // 若不能使第二部分中的子序列为 C, 不满足要求, 直接跳过
            Max = max(Max, dp[0][l1 - 1][l2 - 1] + len + dp[1][r1 + 1][r2 + 1]);  // 计算答案, 答案 = 第一部分长 + 第二部分长 + 第三部分长
        }
    }
    printf("%d\n", Max == 0 ? -1 : Max); // 注意判断 -1 的情况
    return 0;
}
```

---

