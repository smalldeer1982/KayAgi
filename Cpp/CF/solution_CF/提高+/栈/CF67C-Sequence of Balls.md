# Sequence of Balls

## 题目描述

有两个字符串 $A, B$，每次可以对 $A$ 进行 $4$ 种操作：

1. 插入一个字符，花费 $t_i$ 元；
2. 删除一个字符，花费 $t_d$ 元；
3. 替换一个字符，花费 $t_r$ 元；
4. 交换相邻的两个字符，花费 $t_e$ 元。

保证费用都是 $[1, 100]$ 之间的正整数，且 $2t_e\geq t_i + t_d$。

求将 $A$ 变成 $B$ 最少需要多少元。

## 样例 #1

### 输入

```
1 1 1 1
youshouldnot
thoushaltnot
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2 4 10 3
ab
ba
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 10 20 30
a
za
```

### 输出

```
1
```

# 题解

## 作者：Alex_Wei (赞：11)

*[CF67C Sequence of Balls](https://www.luogu.com.cn/problem/CF67C)

先不考虑交换操作。

容易证明不会对同一个位置替换两次，替换后的字符不会删除。因此，设 DP $f_{i, j}$ 表示用 $A[1, i]$ 匹配 $B[1, j]$ 的最小代价。

- 插入转移 $f_{i, j} + t_i\to f_{i, j + 1}$。
- 删除转移 $f_{i, j} + t_d \to f_{i + 1, j}$。
- 替换转移 $f_{i, j} + t_r[A_{i +1} \neq B_{j + 1}]\to f_{i + 1, j + 1}$。

根据 $2t_e\geq t_i + t_d$，我们探究交换的性质：

- 不会出现两次相同的交换 $xy\to yx\to xy$。
- 不会出现两次相邻的交换 $xyz\to yxz\to yzx$，因为它可以被一次插入和一次删除代替：$xyz\to yzx$。
- 涉及交换的字符不会被删除 $xy\to yx\to x/y$，因为不如直接删除。
- 涉及交换的字符不会被替换 $xz\to zx\to zy$，因为若 $t_r\leq t_e$，不如两次替换；若 $t_r \geq t_e$，则不如先插入再删除：$t_r + t_e\geq 2t_e \geq t_i + t_d$。

以上说明了，**涉及交换的字符不会再被进行其它操作**。

设 $p$ 为从 $B_{j + 2}$ 开始第一个等于 $A_{i + 1}$ 的位置，$q$ 为从 $A_{i + 2}$ 开始第一个等于 $B_{j + 1}$ 的位置，我们交换 $A_{i + 1}$ 和 $A_q$，使得它们分别匹配 $B_{j + 1}$ 和 $B_p$。因为不会出现两次相邻的交换，所以最优操作序列形如删去 $A_{i + 2}\sim A_{q - 1}$，交换，再插入 $B_{j + 2}\sim B_{p - 1}$，这就引出了交换转移 $f_{i, j} + t_e + (p - (j + 2)) t_i + (q - (i + 2)) t_d\to f_{q, p}$。

$p$ 和 $q$ 都容易对每个位置预处理下一个等于某字符的位置快速得到。

时间复杂度 $\mathcal{O}(nm)$。[代码](https://codeforces.com/contest/67/submission/189899717)。

---

## 作者：Alkaid_Star (赞：11)

[可能更好的阅读体验！](https://www.encounter.cool/index.php/2021/08/24/cf67c-solution/)
#### 前面的话

好题。但是找遍全网没有感觉特别深入的题解，对于我发出的一些疑问也很难解答。这里发布详细的题解以及一些跟同学讨论过后 的结论以及思绪，希望能给你帮助，~~更希望你能给我点个赞~~。

### 题目大意

>你有四种操作：
>
>1. 插入任意一个字符，花费 $t_i$ 元。
>2. 删除任意一个位置的字符，花费 $t_d$ 元。
>3. 替换任意一个字符为其他字符，花费 $t_r$ 元。
>4. 交换任意相邻两个位置的字符，花费 $t_e$ 元。
>
>给定两个字符串 $a,b$。对 $a$ 进行任意次以上四种操作，求变成 $b$ 的最小花费。
>
>$|a|,|b| \le 4 \times 10^3$，$1 \le t_i,t_d,t_r,t_e \le 100$。

### 解题思路

dp 的思路是显然的，状态也不难想，与类似的题目相同，都是设 $dp_{i,j}$ 为 $a$ 串的前 $i$ 个字符，$b$ 串的前 $j$ 个字符匹配上的最小花费。

那么我们分别考虑四种操作。 

对于插入操作，我们先给出方程：
$$
dp_{i,j}=\min \{ dp_{i,j} , dp_{i,j-1}+t_i \}
$$


![pic1.png](https://i.loli.net/2021/08/24/TM9azF8toivZq3x.png)

如上图，我们进行的操作，是把 $b_j$ 这个字符插入到 $i$ 的后面。也就是说，原来匹配的字符有 $j-1$ 个，现在有 $j$ 个了。

那么为什么不是从 $dp_{i-1,j-1}$ 转移过来呢？我们考虑本来 $a$ 的前 $i$ 位就已经和 $b$ 的前 $j-1$ 位匹配的情况下，我们现在用的是加的这位去和 $b$ 的第 $j$ 位匹配。

那为什么不是转移去 $dp_{i+1,j}$ 呢？因为我们插入和删除字符，显然不能真的去修改原串。**我们 $dp$ 数组里的 $i$ 和 $j$ 都是指原串中的位置，是不受插入删除的影响的**。换言之，这个**加进来的字符，不可能对答案造成贡献我们在后面处理的时候是不考虑的**。

那为什么可以不考虑呢？这个我们最后说，和交换操作有关。

减法同理，直接给出方程吧：
$$
dp_{i,j}=\min\{dp_{i,j},dp_{i-1,j}+t_d\}
$$
也即，$a$ 的前 $i-1$ 位已经与 $b$ 的前 $j$ 位匹配了，我们现在直接删去 $a$ 的第 $i$ 位，维持这个匹配状态。**这个减去的字符，也不可能对答案造成贡献，我们不考虑**。

替换也很简单，不过这里有一种特殊情况：当 $a_i$等于 $b_j$ 时，我们其实是不用替换的，我们视作替换的代价为 $0$。方程就是这个：
$$
dp_{i,j}=
\begin{cases}
\min\{dp_{i,j},dp_{i-1,j-1}\} \quad , \quad a_i=b_j \\
\min\{dp_{i,j},dp_{i-1,j-1}+t_r\} \quad , \quad a_i \ne b_j
\end{cases}
$$
最后就是交换了。假设当前处理到 $dp_{i,j}$，我们只需要找出位置在 $i$ 左边的 $a_{p_1}$ 以及位置在 $j$ 左边的 $b_{p_2}$，满足 $a_{p_1}=b_j$，且 $b_{p_2}=a_i$，那么我们如果能够交换 $a_{p_1}$ 和 $a_i$（只能对 $a$ 串进行操作），之后就能把这一位匹配上。

显然，$a_{p_1}$，$b_{p_2}$ 是不一定与我们正在操作的这一位相邻的，无法通过简单的一次交换就完成操作。那这个操作的花费是多少呢？

我们考虑两种交换 $a_i$ 与 $a_{p_1}$ 的方法：**要么一直对相邻两位进行交换，直到把 $a_i$ 换到 $a_{p_1}$ 处，之后再通过交换把 $a_{p_1}$ 换到 $a_i$ 处。要么先删除 $a_1$ 与 $a_{p_1}$ 之间的障碍，再交换此时已经相邻的两位，再把中间的部分填充回去**。至于两种方法的缝合体，显然没有单纯的两种方法优秀。

哪种方法更加优秀？我们发现，题目中给了一条奇怪的条件：$2 \times t_e>t_i+t_d$。什么意思呢？

我们考虑第一种方法的操作次数：

![pic2.png](https://i.loli.net/2021/08/24/4ksdRiyxTjZBGMu.png)

如上图，显然对于一半情形次数为 $2\times (i-p_1)-1$ 次，花费为 $(2 \times (i-p_1)-1) \times t_e$。

考虑第二种方法，显然需要 $i-p_1-1$ 次删除和插入，以及 $1$ 次交换，花费为 $(i-p_1-1)\times (t_i+t_d) + t_e$。

前者减一下后者（看起来很麻烦，实际上是小学数学）：
$$
\begin{aligned}
&\quad (2 \times (i-p_1)-1) \times t_e -(i-p_1-1)\times (t_i+t_d) - t_e \\
&=2\times t_e \times (i-p_1-1) - (t_i+t_d) \times (i-p_1-1) \\
&=(2 \times t_e - t_i-t_d) \times (i-p_1-1) \\
&\qquad \qquad \qquad \qquad \because 2 \times t_e > t_i+t_d \\
&\qquad \qquad \qquad \qquad \therefore 原式>0
\end{aligned}
$$
也即，后面的方法一定比前面的方法优。

所以就有了我们的第四个公式：

注意这里是从 $dp_{a_{p_1}-1,a_{p_2}-1}$ 转移过来，因为实际上**第二种操作的过程一次性满足了一整段 $[p_1,i]$ 的需求**。

那么就有了我们的转移方程：
$$
dp_{i,j}=\min\{ dp_{i,j} ,dp_{p_1-1,p_2-1} +(i-p_1-1) \times (t_i+t_d) + t_e\}
$$
至于 $p_1$ 和 $p_2$，我们直接从前往后用 $O(|S| \times n)$ 的时间复杂度扫过两个串，用类似于序列自动机的东西统计一下即可，好想好写。$|S|$ 指字符集大小，本题中为 $26$。

现在我们再回头去看为什么加入和删除操作不需要考虑加进来的和删出去的那一位：

首先，显然加入和删除只可能对交换操作产生影响。也就是，插入的一位在交换操作中造成了额外的删除负担，或者被删去的一位在交换操作中被错误地多计算了一遍。但是实际上这两种情况不可能发生，因为我们的**交换是从 $dp_{p_1-1,p_2-1}$ 转移过来的，跳过了中间的部分**，所以不会产生影响。

思路到这里就结束了，写一个 $O(n^2)$ 的 $dp$ 即可。注意实现细节中有一些要注意的部分，比如注意处理 $dp_{0,i}$ 以及 $dp_{i,0}$ 部分的转移，其他的问题就不大了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4005;

int n,m,c1,c2,c3,c4;
int dp[N][N],pos1[N][26],pos2[N][26];
char s[N],t[N];

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

inline void Prepare(){
	for (int i=1;i<=n+1;++i){
		for (int j=0;j<26;++j)
			pos1[i][j]=pos1[i-1][j];
		if (i>1) pos1[i][s[i-1]-'a']=i-1;
	}
	for (int i=1;i<=m+1;++i){
		for (int j=0;j<26;++j)
			pos2[i][j]=pos2[i-1][j];
		if (i>1) pos2[i][t[i-1]-'a']=i-1;
	}
}

int main(){
	//freopen("CF67C.in","r",stdin);
	//freopen("CF67C.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>c1>>c2>>c3>>c4;
	cin>>s+1; cin>>t+1;
	n=strlen(s+1),m=strlen(t+1);
	Prepare();
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for (int i=0;i<=n;++i)
		for (int j=0;j<=m;++j){
			if (j>0) dp[i][j]=min(dp[i][j],dp[i][j-1]+c1);
			if (i>0) dp[i][j]=min(dp[i][j],dp[i-1][j]+c2);
			if ((i>0) && (j>0)){
				if (s[i]==t[j]) dp[i][j]=min(dp[i][j],dp[i-1][j-1]);
				else dp[i][j]=min(dp[i][j],dp[i-1][j-1]+c3);
				int p1=pos1[i][t[j]-'a'],p2=pos2[j][s[i]-'a'];
				if ((p1>=1) && (p2>=1)) dp[i][j]=min(dp[i][j],dp[p1-1][p2-1]+(i-p1-1)*c2+(j-p2-1)*c1+c4);
			}
		}
	printf("%d\n",dp[n][m]);
	return 0;
}
```



---

## 作者：EchoHua0402 (赞：3)

# CF67C Sequence of Balls 题解

## 题目大意

给定两个字符串 $A,B$，通过对 $A$ 的以下四种操作，使得 $A$ 变为 $B$，并且花费最小。

1. 插入一个字符，花费 $t_i$ 元。
2. 删除一个字符，花费 $t_d$ 元。
3. 替换一个字符，花费 $t_r$ 元。
4. 交换相邻两个字符，花费 $t_e$ 元。

保证 $1 \leq |A|,|B| \leq 4000$ 且 $2 \times t_e \geq t_i + t_d$ 且 $1 \leq t_i,t_d,t_r,t_e \leq 100$。

## 思路

容易想到动态规划。

### 状态

这个不难想，我们设 $dp[i][j]$ 表示 $A$ 的前 $i$ 个字符和 $B$ 的前 $j$ 个字符匹配需要的最小花费。

### 初始状态

根据状态的定义，初始化 $dp[i][0]$ 和 $dp[0][j]$。

$$
dp[i][0]=i \times t_d
$$
$$
dp[0][j]=j \times t_i
$$

其余均初始为 $+\infty$（因为后面要取最小）。
### 转移

首先，对于 $A[i]=B[j]$，有 $dp[i][j]=\min \{dp[i][j],dp[i-1][j-1]\}$。

这是显然的，如果当前的两个字符相同，那么这一次无需做任何操作就能使它们匹配。

对于 $A[i] \neq B[j]$ 呢？

我们先考虑只含前三种操作时怎么做，前三种操作是比较简单的（大家可以先去看看[P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)）。

1. 插入一个字符：$dp[i][j]=\min \{dp[i][j],dp[i][j-1]+t_i\}$。

2. 删除一个字符：$dp[i][j]=\min \{dp[i][j],dp[i-1][j]+t_d\}$。

3. 替换一个字符：$dp[i][j]=\min\{dp[i][j],dp[i-1][j-1]+t_r\}$。

接下来，我们考虑较为复杂的第四种操作。

**我们交换的相邻的两个字符不一定是一开始就相邻。**

我们引入一个 $apre[i][ch]$ 和 $bpre[i][ch]$ 分别表示 $A$ 和 $B$ 中字符 $ch$ 在第 $i$ 位之前出现最晚的位置，这两个数组预处理即可。

我们令 $p_1=apre[i][B[j]],p_2=bpre[j][A[i]]$，如果我们交换 $A_{p_1}$ 和 $A_i$，就可以成功匹配，但是 $i$ 与 $p_1$ 不一定相邻，这就导致我们无法通过一次交换操作完成，所以我们不得不做一些其它操作以达到目的。

方法一：

$A_i$ 通过多次相邻交换，到达 $A_{p_1}$ 处。$A_{p_1}$ 通过多次相邻交换，到达 $A_i$ 处。

方法二：

删除 $A_i$ 与 $A_{p_1}$ 之间的所有字符，交换 $A_i$ 和 $A_{p_1}$，然后在 $A_i$ 与 $A_{p_1}$ 之间插入刚刚删除的所有字符。

那么到底是方法一更优还是方法二更优呢？

方法一的花费：

$$
t_e \times ((i-p_1) \times 2 -1)
$$

方法二的花费：

$$
(i-p_1-1) \times (t_i+t_d)+t_e
$$

我们比较这两个式子的大小，这里我们用第一个式子减第二个式子的方法来比较。

硬算：

$$
\begin{aligned}
t_e \times ((i-p_1) \times 2 -1)-((i-p_1-1) \times (t_i+t_d)+t_e) 
&=2\times t_e \times (i-p_1)-t_e-(i-p_1-1) \times (t_i+t_d)-t_e\\
&=2 \times t_e \times(i-p_1)-2 \times t_e-(i-p_1-1) \times (t_i+t_d)\\
&=2 \times t_e \times (i-p_1-1)-(i-p_1-1) \times (t_i+t_d)\\
&=(2 \times t_e-(t_i+t_d))\times(i-p1-1)\\
\end{aligned}
$$
那怎样判断这个式子的正负呢？

由 $A_{p_1}$ 的定义得，$i-p_1-1 \geq 0$

此时原式的正负与 $2 \times t_e-(t_i+t_d)$ 有关，我们想起了题目中给的很奇怪的条件： $2 \times t_e \geq t_i + t_d$，由这个条件可得原式 $\geq 0$。

所以方法二更优，那么对于操作四的转移为：
$$
dp[i][j]=\min \{dp[i][j],dp[apre[i][B[j]-1][bpre[j][A[i]-1]]+t_e+t_d \times (i-apre[i][B[j]]-1)+t_i \times (j-bpre[j][A[i]]-1)\}
$$
### 答案

显然，$dp[len_A][len_B]$ 即为所求。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4005;
const int INF=2e9;
char s1[N],s2[N];
int dp[N][N];
int f1[N][30],f2[N][30];
int ti,td,tr,te;
int main()
{
	cin>>ti>>td>>tr>>te;
	cin>>(s1+1)>>(s2+1);
	int n=strlen(s1+1),m=strlen(s2+1);
	memset(f1,-1,sizeof(f1));
	memset(f2,-1,sizeof(f2));
	for (int i=1;i<=n;i++)//预处理
	{
		for (int j=i-1;j>=1;j--)
		{
			if (f1[i][s1[j]-'a'+1]==-1) f1[i][s1[j]-'a'+1]=j;
		}
	}
	for (int i=1;i<=m;i++)//预处理
	{
		for (int j=i-1;j>=1;j--)
		{
			if (f2[i][s2[j]-'a'+1]==-1) f2[i][s2[j]-'a'+1]=j;
		}
	}
	for (int i=1;i<=n;i++)//初始化
	{
		for (int j=1;j<=m;j++) dp[i][j]=INF;
	}
	for (int i=0;i<=n;i++) dp[i][0]=i*td;
	for (int j=0;j<=m;j++) dp[0][j]=j*ti;
	int now;
	for (int i=1;i<=n;i++)//转移
	{
		for (int j=1;j<=m;j++)
		{
			if (s1[i]==s2[j]) dp[i][j]=dp[i-1][j-1];
			else
			{
				dp[i][j]=min(dp[i][j],dp[i-1][j]+td);
				dp[i][j]=min(dp[i][j],dp[i][j-1]+ti);
				dp[i][j]=min(dp[i][j],dp[i-1][j-1]+tr);
				if (f2[j][s1[i]-'a'+1]==-1||f1[i][s2[j]-'a'+1]==-1) continue;
				int len1=i-f1[i][s2[j]-'a'+1]-1;
				int len2=j-f2[j][s1[i]-'a'+1]-1;
				now=td*len1+te+ti*len2;
				dp[i][j]=min(dp[i][j],dp[f1[i][s2[j]-'a'+1]-1][f2[j][s1[i]-'a'+1]-1]+now);
			}
		}
	}
	cout<<dp[n][m]<<endl;//输出
	return 0;
}
```

---

## 作者：三点水一个各 (赞：2)

### 题意：

`对A进行若干次操作，求变成B最少需要多少元`


### 思路：

定义 $dp_{i,j}$ 为 $A$ 中前 $i$ 个字符与 $B$ 中前 $j$ 个字符相等时需要的最小代价。

思考得到以下方程：

插入 $b_j$，那么在原先的 $i$ 位置新增了 $b_j$，原先 $B$ 序列中占 $j-1$ 个，现在是 $j$ 个，所以情况与 $dp_{i,j-1}$ 相同，即：

$$dp_{i,j}=\min(dp_{i,j},dp_{i,j-1}+ti)(0<j)$$

删去 $a_i$，情况则与 $dp_{i-1,j}$ 相同，即：

$$dp_{i,j}=\min(dp_{i,j},dp_{i-1,j}+td)(0<i)$$

用 $b_j$ 直接替换 $a_i$，需注意此时原先 $a_i$ 就可能等于 $b_j$，则花费是 $0$，即：

$$dp_{i,j}=\min(dp_{i,j},dp_{i-1,j-1}+(a_i=b_j?0:tr))(0<i,j)$$

将 $a_i$ 与 $A$ 中的某个元素交换使得新的 $a_i$ 与 $b_j$ 相等。

此时的花费 $p$：

设在 $A$ 中 $i$ 位置左侧第一个与 $b_j$ 相等元素的下标为 $x$，在 $B$ 中 $j$ 位置的左侧第一个与 $a_i$ 相等元素的下标为 $y$。

把 $a_x$ 到 $a_i$ 之间的所有元素删掉（不包括 $a_x$ 和 $a_i$），交换 $a_x$ 和 $a_i$ ，再将 $b_y$ 到 $b_j$ 间的元素（不包括 $b_y$ 和 $b_j$）都插入到 $a_x$ 和 $a_i$ 之间。

所以 $p=(i-x-1)\times td+(j-y-1)\times ti+te$

方程为：

$$dp_{i,j}=\min(dp_{i,j},dp_{x-1,y-1}+p)(0<x,y)$$



```
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,p,ti,td,tr,te;
int dp[5050][5050],la[5005][27],lb[5005][27],pos[27];
char a[5050],b[5050];
int main()
{
	memset(dp,0x7f,sizeof(dp));
    memset(pos,0,sizeof(pos));
	dp[0][0]=0;
    scanf("%d%d%d%d",&ti,&td,&tr,&te);
    scanf("%s%s",a+1,b+1);
    n=strlen(a+1); m=strlen(b+1);
    for(int i=1;i<=n;i++)
    {   
        for(int j=0;j<26;j++)
		  la[i][j]=pos[j];
        pos[a[i]-'a']=i;
    }
    memset(pos,0,sizeof(pos));
    for(int i=1;i<=m;i++)
    {   
        for(int j=0;j<26;j++)
		  lb[i][j]=pos[j];
        pos[b[i]-'a']=i;
    }
    for(int i=0;i<=n;i++)
      for(int j=0;j<=m;j++)
      {
          if (i>0) dp[i][j]=min(dp[i][j],dp[i-1][j]+td);
          if (j>0) dp[i][j]=min(dp[i][j],dp[i][j-1]+ti);
          if (i>0&&j>0) dp[i][j]=min(dp[i][j],dp[i-1][j-1]+(a[i]==b[j]?0:tr));
          x=la[i][b[j]-'a']; y=lb[j][a[i]-'a'];
          if(x>0&&y>0)
          {
              p=(j-y-1)*ti+(i-x-1)*td+te;
              dp[i][j]=min(dp[i][j],dp[x-1][y-1]+p); 
          }
      }
    printf("%d\n",dp[n][m]);
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

## 思路

我们先来看到，假设只有插入，删除，替换三种操作，我们应该怎么做。

[www.luogu.com.cn](https://www.luogu.com.cn/problem/P2758)


我们定义 dp 状态 $dp_{i,j}$ 为 $A$ 的前 $i$ 个字符与 $B$ 的前 $j$ 个字符相同的最少操作数。转移，当我们 $i≠j$ 时，若 $i>j$ 说明我们在 $A$ 的前 $i$ 个字符中删去了某些字符后与 $B$ 的前 $j$ 个字符匹配。若 $i<j$ 说明我们在 $A$ 的前 $i$ 个字符中添加了某些字符后与 $B$ 的前 $j$ 个字符匹配。当然混合情况也有。

我们考虑每个操作对应的转移

- 插入 $dp_{i,j}=\min(dp_{i,j},dp_{i,j-1}+1)$

- 删除 $dp_{i,j}=\min(dp_{i,j},dp_{i-1,j}+1)$

- 替换 $dp_{i,j}=\min(dp_{i,j},dp_{i-1,j-1}+[A_i≠B_j])$

```C++

int n,m,la,lb;
int dp[N][N];
string A,B;

void minn(int &a,int b){
	a=min(a,b);
}

signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);

	cin>>A>>B;
	
	la=A.size(),lb=B.size();
	A=' '+A;
	B=' '+B;

	
	memset(dp,0x3f3f,sizeof dp);
	
	dp[0][0]=0;
	
	for(int i=0;i<=la;i++){
		for(int j=0;j<=lb;j++){
			if(j)minn(dp[i][j],dp[i][j-1]+1);//插入
			if(i)minn(dp[i][j],dp[i-1][j]+1);//删除
			if(i&&j){
				minn(dp[i][j],dp[i-1][j-1]+(A[i]!=B[j]));//替换
				
			}
		}
	}
	
	cout<<dp[la][lb]<<endl;
	
	return 0;
}

```

那么要变成本题，我们要解决两个问题：操作的花费和交换操作。

操作的花费很好解决，即：

- 插入 $dp_{i,j}=\min(dp_{i,j},dp_{i,j-1}+t_i)$

- 删除 $dp_{i,j}=\min(dp_{i,j},dp_{i-1,j}+t_d)$

- 替换 $dp_{i,j}=\min(dp_{i,j},dp_{i-1,j-1}+[A_i≠B_j]\times t_r)$，其中如果 $A_i=B_i$，那么 $[A_i≠B_i]=0$，即不需要花费。

那么对应交换操作，我们好像不能再按照这样的 dp 转移来计算了。那么我们来考虑什么时候我们需要交换操作。

如果在交换之后，我们删除了两个数其中的某一个，那么我们都交换就是没有意义的。由于题目给定 $2t_e\geq t_i + t_d$，所以我们知道，如果对同一个数字我们连续交换两次，我们不如先删除然后插入。即假设我们要交换若干个二元组 $i,j$，那么这些二元组组成的集合中不应该有重复项。

同时，假设我们交换只是为了让一个字符匹配到，那么我们不如删除或者插入。即：假设有交换二元组 $i,i+1$，如果我们为了让 $A_i$ 与 $B_j$ 匹配而交换，那么我们不如在 $A_i$ 前插入 $B_{j-1}$。如果我们为了让 $A_{i+1}$ 与 $B_j$ 匹配，那么我们不如删去 $A_i$。除非交换之后恰好两个字符都从不匹配状态变成匹配状态，否则我们不会交换 $i,i+1$。

我们还可以证明，**被交换过的数字一定不会被执行其他操作。**



假设我们想把 $a_{k}$ 这个字符交换到 $a_i$ 处 $(a_k=b_{j},0<k<i)$，注意这里肯定要保证 $k$ 尽可能的大，

如果只是交换相邻的两个字符很难保证相等，因为一交换前面的都会打乱，

所以我们考虑把 $a_k$ 到 $a_{i}$ 之间的字符都删掉，**再去 $B$ 中找 $j$ 位置左侧第一个等于 $a_i$ 的字符 $b_{p}$**，

这个时候我们再交换 $a_{k}$ 与 $a_{i}$（目的是让 $a_k,a_i$ 的相对顺序与 $b_j,b_p$ 相同，这样的话就让两个字符都匹配了，虽然还可能需要一些插入操作，但这些操作都是必要的。），然后把 $b_{p+1}$ 一直到 $b_{j-1}$ 的这些字符都插入进来，这样我们就完成一次交换且满足相等的条件。

所以我们来计算一下花费：

$t'_d=(i-k-1)\times t_d$

$t'_i=(j-p-1)\times t_i$

转移方程为 $dp_{i,j}=\min(dp_{i,j},dp_{k-1,p-1}+t'_d+t'_i+t_e)$。因为我们要快速求出 $k,p$，所以我们要预处理一下对于每个 $a_i$ 在 **$B$ 中 $i$ 位置左侧第一个等于 $a_i$ 的字符 $b_{p}$** 的位置。



现在$4$种操作的转移方程我们都知道了，我们可以开始写代码了。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//
#include<bits/stdc++.h>

//
//#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back
//*/

//
using namespace std;
//
const int N=4e3+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
const db eps=1e-9;
//
int n,m,la,lb;
int dp[N][N];

int ti,td,tr,te,prea[33][N],preb[33][N];
int L;


string A,B;

void minn(int &a,int b){
	a=min(a,b);
}

void init(){//预处理前驱
	for(int i=1;i<=la;i++){
		for(int j=1;j<=26;j++){
			prea[j][i+1]=prea[j][i];
		}
		prea[A[i]-'a'+1][i+1]=i;
	}
	
	for(int i=1;i<=lb;i++){
		for(int j=1;j<=26;j++){
			preb[j][i+1]=preb[j][i];
		}
		preb[B[i]-'a'+1][i+1]=i;
	}
}

signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);

	cin>>ti>>td>>tr>>te>>A>>B;
	
	la=A.size(),lb=B.size();
	A=' '+A;
	B=' '+B;
	
	init();
	
	
	memset(dp,0x3f3f,sizeof dp);
	
	dp[0][0]=0;
	
	for(int i=0;i<=la;i++){
		for(int j=0;j<=lb;j++){
			if(j)minn(dp[i][j],dp[i][j-1]+ti);//插入
			if(i)minn(dp[i][j],dp[i-1][j]+td);//删除
			if(i&&j){
				minn(dp[i][j],dp[i-1][j-1]+tr*(A[i]!=B[j]));//替换
				int s=prea[B[j]-'a'+1][i],t=preb[A[i]-'a'+1][j];
				if(s&&t){
					minn(dp[i][j],dp[s-1][t-1]+(i-s-1)*td+(j-t-1)*ti+te);//交换
				}
			}
		}
	}
	
	cout<<dp[la][lb]<<endl;
	
	return 0;
}

//check your long long and the size of memery!!!

```


[Submission #222670912 - Codeforces](https://codeforces.com/contest/67/submission/222670912)




---

## 作者：LimpidSlirm (赞：1)

## 题意

给定两个字符串 $s,t$ 每次可以进行 $4$ 种操作

1. 插入一个字符，花费为 $a$。
2. 删除一个字符，花费为 $b$。
3. 替换一个字符，花费为 $c$。
4. 交换**相邻**的两个字符，花费为 $d$。

**※保证 $ 2d≥a+b $**。

现在对 $s$ 进行若干次操作，求变成 $t$ 最少需要的代价。

## Solution

定义字符串 $s,t$ 的长度分别为 $n,m$ 。

发现 $n,m\leq 4000$ 容易想到可以 $\mathcal{O}(nm)$ 来 dp。

定义 $ dp_{i,j} $ 为 $s$ 串的前 $i$ 个字符通过操作得到 $t$ 串的前 $j$ 个字符的最小代价。

故容易发现对于操作1有转移方程：
$$
dp_{i,j} \gets dp_{i,j-1}+a
$$
对于操作2有转移方程：
$$
dp_{i,j} \gets dp_{i-1,j}+b
$$
若 $ s_i \neq t_j $ 则对于操作3有转移方程：
$$
dp_{i,j} \gets dp_{i-1,j-1}+c
$$
最后来考虑操作4，由于题目给定 $ 2d≥a+b$，所以容易发现对于同一个字符交换两次一定不如删除后再插入花费少。定义 $pre_{s,t_j}$ 为字符串 $s$ 中 $i$ 之前的第一个 $s_k = t_j $，同理定义 $pre_{t,s_i}$ 为字符串 $t$ 中 $j$ 之前的第一个  $t_k = s_i$。则对于交换操作，最优的选择应该是交换 $s$ 串上第 $i$ 位和第 $pre_{s,t_j}$ 位，交换 $t$ 串上第 $j$ 位和第 $pre_{t,s_i}$ 位，并将中间部分全部删除并重新插入。对于删除操作，代价为 $a \times (i-pre_{s,t_j}-1)$，对于插入操作，代价为 $b \times (j-pre_{t,s_i}-1)$。

所以有转移方程：
$$
\large{dp_{i,j} \gets dp_{pre_{s,t_j}-1,pre_{t,s_i}-1}+a \times (i-pre_{s,t_j}-1)+b \times (j-pre_{t,s_i}-1)+d}
$$
对于 $pre ，\mathcal{O}(n^2+m^2)$ 预处理即可，总时间复杂度为 $\mathcal{O}(nm+n^2+m^2)$ 可以通过本题。 

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
int lass[30][4010],last[30][4010];
int dp[4010][4010];
int main(int argc,const char *argv[])
{
	int a=read(),b=read(),c=read(),d=read();
	string s,t;
	cin>>s>>t;
	int n=s.length(),m=t.length();
	s=' '+s;
	t=' '+t;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=26;j++)
			lass[j][i+1]=lass[j][i];
		lass[s[i]-'a'+1][i+1]=i;
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=26;j++)
			last[j][i+1]=last[j][i];
		last[t[i]-'a'+1][i+1]=i;
	}
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			if(j!=0) dp[i][j]=min(dp[i][j],dp[i][j-1]+a);
			if(i!=0) dp[i][j]=min(dp[i][j],dp[i-1][j]+b);
			if(i==0||j==0)
				continue;
			dp[i][j]=min(dp[i][j],dp[i-1][j-1]+c*(s[i]!=t[j]));
			int lasa=lass[t[j]-'a'+1][i],lasb=last[s[i]-'a'+1][j];
			if(lasa==0||lasb==0)
				continue;
			dp[i][j]=min(dp[i][j],dp[lasa-1][lasb-1]+(i-lasa-1)*b+(j-lasb-1)*a+d);
		}
	}
	printf("%d",dp[n][m]);
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## CF67C

### 题意

有两个字符串 $A,B$，每次可以对 $A$ 进行 $4$ 种操作：

+ 插入一个字符，花费 $t_i$ 元；
+ 删除一个字符，花费 $t_d$ 元；
+ 替换一个字符，花费 $t_r$ 元；
+ 交换相邻的两个字符，花费 $t_e$ 元。

保证费用都是 $[1,100]$ 之间的正整数，且 $2t_e \ge t_i + t_d$。

求将 $A$ 变成 $B$ 最少需要多少元。

$|A|, |B| \le 4000$

### 标签

思维，dp

### 做法

设 $f_{i, j}$ 表示字符串 $A$ 匹配到前 $i$ 个字符，字符串 $B$ 匹配到前 $j$ 个字符。那么前三个操作的维护都是显然的：

+ 对于插入操作，有 $f_{i, j} = \min\{f_{i, j}, f_{i, j - 1} + t_i\}$。
+ 对于删除操作，有 $f_{i, j} = \min\{f_{i, j}, f_{i - 1, j} + t_d\}$。
+ 对于替换操作，有 $f_{i, j} = \min\{f_{i, j}, f_{i - 1, j - 1} + t_r\}$。

接下来考虑第四个操作。发现题目给了一个耐人寻味的性质，$2t_e \ge t_i + t_d$，这说明对于连续多个字符的不停进行交换相邻项的操作都不如删除完中间字符后进行 $2$ 次交换，再插入回去。那么交换就可以只使用这种方案了，只需维护上一个可以与当前位置 $(i, j)$ 进行交换的位置 $(x, y)$，$f_{i, j}$ 可以直接从 $f_{x - 1, y - 1}$ 转移过来，因为插入后会再填充所以可以忽视中间的其它字符。

### 代码

```cpp
#include <stdio.h>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
typedef long long lld;
using namespace std;
const int N = 4010;
int n, m;
int ti, td, tr, te;
char a[N], b[N];
int f[N][N];
int pos1[N][256];
int pos2[N][256];
int main() {
	scanf("%d%d%d%d", &ti, &td, &tr, &te);
	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1), m = strlen(b + 1);
	for (int i = 1; i <= n; ++ i) {
		memcpy(pos1[i + 1], pos1[i], sizeof(pos1[i + 1]));
		pos1[i + 1][a[i]] = i;
	}
	for (int i = 1; i <= m; ++ i) {
		memcpy(pos2[i + 1], pos2[i], sizeof(pos2[i + 1]));
		pos2[i + 1][b[i]] = i;
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			if (i && j && a[i] == b[j]) f[i][j] = min(f[i][j], f[i - 1][j - 1]);
			if (i && j) f[i][j] = min(f[i][j], f[i - 1][j - 1] + tr);
			if (i) f[i][j] = min(f[i][j], f[i - 1][j] + td);
			if (j) f[i][j] = min(f[i][j], f[i][j - 1] + ti);
			int p1 = pos1[i][b[j]], p2 = pos2[j][a[i]];
			if (p1 && p2) f[i][j] = min(f[i][j], f[p1 - 1][p2 - 1] + (i - p1 - 1) * td + (j - p2 - 1) * ti + te);
		}
	}
	printf("%d\n", f[n][m]);
}
```

---

## 作者：wcyQwQ (赞：0)

只有前三种操作是编辑距离板子，考虑操作四。

注意题目给了一个奇怪的限制，仔细想想，这保证了每个字符最多只能被交换一次。同时一个显然的事情是，我们只会交换原有的字符，否则新加进来直接放在正确的位置上显然更优。

于是设 $f_{i, j}$ 表示 $A$ 的前 $i$ 位和 $B$ 前 $j$ 位匹配的最小代价。我们考虑将 $i$ 位置和 $k$ 位置进行交换，然后再在他们中间插入若干个字符，我们设最后 $A_i, \ldots, A_k$ 这一段要和 $B_l, \ldots, B_j$ 这一段匹配，所以我们需要 $A_i = B_l$，$A_k = B_j$。此时我们可以得到转移
$$
f_{i, j} = \min_{A_i = B_l, A_k = B_j} f_{k - 1, l - 1} + (i - k - 1)b + (j - l - 1)a + d
$$
这样似乎是 $O(n^4)$ 的，但是我们不难发现每次转移只会取最大的 $k$ 和 $l$，简单证明一下。

设 $k_1, l_1$ 是另外的一组转移，那么我们有
$$
\begin{aligned}
&f_{k - 1, l - 1} + (i - k - 1)b + (j - l - 1)a + d - [f_{k_1 - 1, l_1 - 1} + (i - k_1 - 1)b + (j - l_1 - 1)a + d] \\
&= f_{k - 1, l - 1} - f_{k_1 - 1, l_1 - 1} - (k - k_1)b - (l - l_1)a
\end{aligned}
$$
我们考虑 $f_{k - 1, l - 1} - f_{k_1 - 1, l_1 - 1}$ 的意义，就是已经拼好了前面，要拼到后面还要花费的最小的代价，不难发现 $(k - k_1)b + (l - l_1)a$ 是一种可行的代价，根据 $f$ 的最小性，我们可以判断前者小于后者，所以原式的值 $\le 0$。

所以我么可以预处理处每个位置的转移点，然后就可以做到 $O(n^2)$ 了。

[Code](https://codeforces.com/contest/67/submission/217399413)

---

## 作者：Dehydration (赞：0)

### 前言：

一眼：编辑距离！

两眼：唉？怎么又交换？

三眼：交换也很水捏。

[problem](https://www.luogu.com.cn/problem/CF67C)。

### 思路：


如果你想些没有代价没有交换的弱化版，来[这里](https://www.luogu.com.cn/problem/P2758)。

和编辑距离一样，是动态规划，$dp_{i,j}$ 表示 $A$ 的前 $i$ 个字符匹配 $B$ 的前 $j$ 项的最小代价。

操作 1：$dp_{i,j+1}=\min\{dp_{i,j+1},dp_{i,j}+t_i\}$。

操作 2：$dp_{i+1,j}=\min\{dp_{i+1,j},dp_{i,j}+t_d\}$。

操作 3：$dp_{i+1,j+1}=\min\{dp_{i+1,j+1},dp_{i,j}+[A_i\neq B_i]\times t_r\}$。

操作 4：考虑交换，容易发现被交换的字符不会再被其他操作，则最优操作为删除交换两数所有数字，再交换最优，一开始特判即可。


复杂度 $\Theta (nm)$。


### 代码：

DP，给出部分代码：


```cpp
for(int i = 0; i < 26; i++) A[n + 1][i] = B[m + 1][i] = -1;
    for(int i = n; i >= 1; i--) {
        for(int j = 0; j < 26; j++) A[i][j] = A[i + 1][j];
        A[i][a[i] - 'a'] = i;
    }
    for(int i = m; i >= 1; i--) {
        for(int j = 0; j < 26; j++) B[i][j] = B[i + 1][j];
        B[i][b[i] - 'a'] = i;
    }
    memset(f, 0x3f, sizeof(f)), f[0][0] = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            cmin(f[i][j + 1], f[i][j] + ti);
            cmin(f[i + 1][j], f[i][j] + td);
            cmin(f[i + 1][j + 1], f[i][j] + (a[i + 1] != b[j + 1]) * tr);
            if(i + 2 <= n && j + 2 <= m) {
                int p = B[j + 2][a[i + 1] - 'a'], q = A[i + 2][b[j + 1] - 'a'];
                if(p != -1 && q != -1) cmin(f[q][p], f[i][j] + (q - i - 2) * td + (p - j - 2) * ti + te);
            }
        }
    }
```

---

## 作者：marTixx (赞：0)

## 题意

[Link](https://www.luogu.com.cn/problem/CF67C)

两个字符串 $A$，$B$，对 $A$ 支持四种操作：

1. 插入一个字符，花 $t_{i}$ 元，
2. 删除一个字符，花 $t_{d}$ 元，
3. 替换一个字符，花 $t_{r}$ 元，
4. 交换相邻的两个字符，花 $t_{e}$ 元。

求 $A$ 变成 $B$ 最少需多少元。

## Sol

设 $dp_{i,j}$ 表示 $A$ 前 $i$ 个字符变成与 $B$ 的前 $j$ 个字符相等最少需多少元。

### 操作一：插入一个字符

考虑在 $i$ 位置插入 $b_{j}$，则有：
$$
dp_{i,j} = min\left\{dp_{i,j},dp_{i,j-1} + t_i\right\}
$$

###  操作二：删除一个字符

考虑删除 $a_i$，则有：
$$
dp_{i,j} = min\left\{dp_{i,j},dp_{i-1,j} + t_{d}\right\}
$$

### 操作三：替换一个字符

如果当前位置 $a_{i}\neq b_{j}$，考虑把 $a_{i}$ 替换成 $b_j$，则有：

$$
dp_{i,j} = min\left\{dp_{i,j},dp_{i-1,j-1} + t_{r}\right\}
$$

### 操作四：交换相邻的两个字符

#### 思考

由题目中条件 $2 \times t_e\geq t_i+t_d$ 得到启发，反复交换还不如删一个再插一个，得到以下思路：

假设我们想把 $a_{k}$ 这个字符交换到 $a_i$ 处 $(a_k=b_{j},0<k<i)$，注意这里肯定要保证 $k$ 尽可能的大，

如果只是交换相邻的两个字符很难保证相等，因为一交换前面的都会打乱，

所以我们考虑把 $a_k$ 到 $a_{i}$ 之间的字符都删掉，**再去 $B$ 中找 $j$ 位置左侧第一个等于 $a_i$ 的字符 $b_{p}$**，

这个时候我们再交换 $a_{k}$ 与 $a_{i}$，然后把 $b_{p}$ 一直到 $b_{j}$ 的这些字符都插入进来，这样我们就完成一次交换且满足相等的条件。

#### 转移

删除的花费为：
$$
del = (i - k - 1) \times t_{d}
$$
插入的花费为：
$$
ins = (j - p - 1) \times t_{i}
$$
故转移方程为：
$$
dp_{i,j} = min\left\{ dp_{i,j},dp_{k-1,p-1} + del + ins + t_{e} \right\}
$$

### 复杂度

预处理出操作四所需的 $k$ 和 $p$ 后再进行 dp，时间复杂度 $\mathcal{O(n^2)}$。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 4e3 + 30;
const int INF = 0x3f3f3f3f;

int ti, td, tr, te, lena, lenb, del, ins, k, p;
char a[N], b[N];
int dp[N][N], posa[30][N], posb[30][N], pos[30];

int main()
{
    scanf ("%d%d%d%d%s%s", &ti, &td, &tr, &te, a + 1, b + 1);
    std::memset(dp, INF, sizeof(dp));
    lena = strlen(a + 1), lenb = strlen(b + 1);
    for (int i = 1; i <= lena; ++ i)
    {
        for (int j = 0; j < 26; ++ j) posa[j][i] = pos[j];
        pos[a[i] - 'a'] = i;
    }
    std::memset(pos, 0, sizeof(pos));
    for (int i = 1; i <= lenb; ++ i)
    {
        for (int j = 0; j < 26; ++ j) posb[j][i] = pos[j];
        pos[b[i] - 'a'] = i;
    }
    dp[0][0] = 0;
    for (int i = 0; i <= lena; ++ i)
    {
        for (int j = 0; j <= lenb; ++ j)
        {
            if (j) dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + ti);
            if (i) dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + td);
            if (i && j) 
            {
                if (a[i] != b[j]) dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1] + tr);
                else dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1]);
            }
            if (i && j)
            {
                k = posa[b[j] - 'a'][i], p = posb[a[i] - 'a'][j];
                if (k && p)
                {
                    del = (i - k - 1) * td, ins = (j - p - 1) * ti;
                    dp[i][j] = std::min(dp[i][j], dp[k - 1][p - 1] + del + ins + te);
                }
            }
        }
    }
    printf ("%d\n", dp[lena][lenb]);
    return 0;
}
```



---

## 作者：Mint_Flipped (赞：0)

对于我这种DP新手很好的题目。

题意：用四种操作完成a->b，求最小代价。

看到题目想了很久，终于写出4个转移式：

匹配问题，2维DP，i为a的匹配情况，j为b的匹配情况。

//insert

f [ i ] [ j ] = min ( f [ i ] [ j ] , f [ i ] [ j - 1 ] + t1 )
            
//delete

f [ i ] [ j ] = min ( f [ i ] [ j ] , f [ i - 1 ] [ j ] + t2 )
            
//replace 
 
f [ i ] [ j ] = min ( f [ i ] [ j ] , f [ i - 1 ] [ j - 1 ] + ( a [ i ] == b [ j ] ? 0 : t3 ) )

//exchange

f [ i + 1 ] [ j + 1 ] = min ( f [ i + 1] [ j + 1 ] , f [ i - 1 ] [ j - 1 ] + ( a [ i ] == a [ i + 1 ] ? 0 : t4 ) ) 

提交wa11，很明显第4个式子有问题。问题在哪里？

4个式子都是在考虑当前匹不匹配，那么无可厚非这是对的，但每个式子都是取自上一个相邻的状态就错了。

第4个操作没有那么简单，我们其实还是可以复合操作，便可以实现不相邻的元素交换。（其实之前的4也实现了这个东西，但是忽略一个条件：
2te ≥ ti + td ，反复交换，不如删除插入来的实在 ~~题目居然给提示了 我还没发现 QWQ~~）

那么式4上一个状态就为可以交换后完成匹配的两个元素的前一位。在 a 里 i 的前面找一个b [ j ]，在 b 里 j 的前面找一个a [ i ]，删去，前者之间的元素，相邻交换，插入后者之间的元素，即可。

我们只要先预处理并记录下每个i前面的元素的位置和每个j前面元素的位置，就可以很快的完成上面的操作(我们不知道前面元素有哪些，就开个二维数组，记录下每个字母的出现情况即可)

正确式4：f [ i ] [ j ] = min ( f [ i ] [ j ] , f [ ta - 1] [ tb - 1 ] + t4 + ( j - tb - 1 ) * t1 + ( i - ta - 1 ) * t2 ) （ta，tb就是上一个状态）

代码如下：QAQ
```c
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first 
#define sec(a) a->second 
const int inf=0x3f3f3f3f;
const int maxn=4e3+5;
const int mod=1e9+7;
const double eps=1e-6;
int n,m,k,t,p[maxn];
int t1,t2,t3,t4,la,lb,pa[maxn][30],pb[maxn][30],pos[maxn],f[maxn][maxn];
char a[maxn],b[maxn];
void init(){
    fo2(i,la){
        fo1(j,26)
        pa[i][j]=pos[j];
    pos[a[i]-'a']=i;
    }
    mem(pos,0);
    fo2(i,lb){
        fo1(j,26)
        pb[i][j]=pos[j];
    pos[b[i]-'a']=i;
    }
    mem(f,inf);
    f[0][0]=0;
}
int main()
{
    scanf("%d%d%d%d%s%s",&t1,&t2,&t3,&t4,a+1,b+1);
    la=strlen(a+1),lb=strlen(b+1);
    init();
    fo1(i,la+1){
        fo1(j,lb+1){
            //insert
            if(j) f[i][j]=min(f[i][j],f[i][j-1]+t1);
            //delete
            if(i) f[i][j]=min(f[i][j],f[i-1][j]+t2);
            //replace 
            if(i&&j)
                f[i][j]=min(f[i][j],f[i-1][j-1]+(a[i]==b[j]?0:t3));
            //exchange
            int ta=pa[i][b[j]-'a'],tb=pb[j][a[i]-'a'];
            if(ta&&tb) f[i][j]=min(f[i][j],f[ta-1][tb-1]+t4+(j-tb-1)*t1+(i-ta-1)*t2);
        }
    }
    printf("%d\n",f[la][lb]);
    return 0;
}
```






---

