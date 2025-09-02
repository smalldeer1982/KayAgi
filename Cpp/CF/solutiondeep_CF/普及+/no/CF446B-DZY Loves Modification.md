# 题目信息

# DZY Loves Modification

## 题目描述

As we know, DZY loves playing games. One day DZY decided to play with a $ n×m $ matrix. To be more precise, he decided to modify the matrix with exactly $ k $ operations.

Each modification is one of the following:

1. Pick some row of the matrix and decrease each element of the row by $ p $ . This operation brings to DZY the value of pleasure equal to the sum of elements of the row before the decreasing.
2. Pick some column of the matrix and decrease each element of the column by $ p $ . This operation brings to DZY the value of pleasure equal to the sum of elements of the column before the decreasing.

DZY wants to know: what is the largest total value of pleasure he could get after performing exactly $ k $ modifications? Please, help him to calculate this value.

## 说明/提示

For the first sample test, we can modify: column 2, row 2. After that the matrix becomes:

`<br></br>1 1<br></br>0 0<br></br><br></br>`For the second sample test, we can modify: column 2, row 2, row 1, column 1, column 2. After that the matrix becomes:

`<br></br>-3 -3<br></br>-2 -2<br></br><br></br>`

## 样例 #1

### 输入

```
2 2 2 2
1 3
2 4
```

### 输出

```
11
```

## 样例 #2

### 输入

```
2 2 5 2
1 3
2 4
```

### 输出

```
11
```

# AI分析结果

### 题目内容
# DZY Loves Modification
## 题目描述
如我们所知，DZY 喜欢玩游戏。有一天，DZY 决定玩一个 $n×m$ 的矩阵。更确切地说，他决定用恰好 $k$ 次操作来修改这个矩阵。
每次修改是以下操作之一：
1. 选择矩阵的某一行，将该行的每个元素减 $p$ 。此操作给 DZY 带来的愉悦值等于该行在减少之前元素的总和。
2. 选择矩阵的某一列，将该列的每个元素减 $p$ 。此操作给 DZY 带来的愉悦值等于该列在减少之前元素的总和。
DZY 想知道：在恰好执行 $k$ 次修改后，他能获得的最大总愉悦值是多少？请帮他计算这个值。
## 说明/提示
对于第一个样例测试，我们可以修改：第2列，第2行。之后矩阵变为：
`<br></br>1 1<br></br>0 0<br></br><br></br>`
对于第二个样例测试，我们可以修改：第2列，第2行，第1行，第1列，第2列。之后矩阵变为：
`<br></br>-3 -3<br></br>-2 -2<br></br><br></br>`
## 样例 #1
### 输入
```
2 2 2 2
1 3
2 4
```
### 输出
```
11
```
## 样例 #2
### 输入
```
2 2 5 2
1 3
2 4
```
### 输出
```
11
```

### 算法分类
贪心

### 综合分析与结论
所有题解均采用贪心策略解决该问题，核心思路是先分别预处理行和列的和，然后通过贪心选择行或列操作来获取最大愉悦值。各题解主要围绕以下要点展开：
 - **性质证明**：部分题解证明了操作顺序不影响答案这一关键性质，为贪心算法提供依据。
 - **贪心策略**：利用优先队列或multiset等数据结构，每次选择和最大的行或列进行操作，并动态更新其和。
 - **相交处理**：考虑到行操作和列操作存在相交部分，需减去相交次数与 $p$ 的乘积。

### 所选的题解
#### 交警（5星）
 - **关键亮点**：详细证明了操作顺序无关性、贪心选择和最大行列可获最大分数、需减去行列相交部分这三个关键性质；代码实现规范，使用优先队列维护行和列的和，清晰展示了预处理和查询过程。
 - **个人心得**：无

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

inline long long read() {
	register long long f = 1, sum = 0;  register char ch = getchar();
	while (!isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { sum = (sum<<1) + (sum<<3) + (ch^48); ch = getchar(); }
	return f * sum;
}

long long n, m, k, p, ans;
long long a[N][N];
long long row[N*N], column[N*N];

priority_queue < long long > row_q, column_q;  //性质二：用优先队列来维护

signed main() {
	n = read(), m = read(), k = read(), p = read();
	for ( register int i = 1 ; i <= n ; i ++ )
		for ( register int j = 1 ; j <= m ; j ++ )
			a[i][j] = read();
	/*<-------------------↓以下为预处理（体现性质一）↓------------------->*/
	for ( register int i = 1 ; i <= n ; i ++ ) { 
		register long long add = 0;
		for ( register int j = 1 ; j <= m ; j ++ ) {
			add += a[i][j];
		} row_q.push ( add );  //把每一行的和加入行的优先队列(row_q)
	} for ( register int i = 1 ; i <= m ; i ++ ) {
		register long long add = 0;
		for ( register int j = 1 ; j <= n ; j ++ ) {
			add += a[j][i];
		} column_q.push ( add );  //把每一列的和加入列的优先队列(column_q)
	} for ( register int i = 1 ; i <= k ; i ++ ) {  //每次处理和最大的行，并且将处理过后的行加入行的优先队列(row_q)
		register long long xx = row_q.top();
		row_q.pop();
		row[i] = row[i-1] + xx;
		xx -= m * p;
		row_q.push ( xx );
	} for ( register int i = 1 ; i <= k ; i ++ ) {  //每次处理和最大的列，并且将处理过后的列加入列的优先队列(column_q)
		register long long xx = column_q.top();
		column_q.pop();
		column[i] = column[i-1] + xx;
		xx -= n * p;
		column_q.push ( xx );
	}
	/*<-------------------↑以上为预处理（体现性质一）↑------------------->*/
	for ( register int i = 0 ; i <= k ; i ++ )
		ans = max ( ans, column[k-i] + row[i] - i * ( k - i ) * p );
		//每次更新答案时应减去 i * ( k - i ) * p   （体现性质三）
	printf ( "%lld\n", ans );
	return 0;
}
```
核心代码实现思想：先读入矩阵数据，通过循环计算每行和每列的和并分别存入优先队列 `row_q` 和 `column_q`。接着通过循环，每次从优先队列取出最大和，更新行或列的累计和数组 `row` 与 `column`，并将操作后的和重新加入优先队列。最后通过枚举行操作次数 `i`，计算并更新最大愉悦值 `ans`。

#### xiaozeyu（4星）
 - **关键亮点**：先尝试DP思路，发现时间复杂度高后引入multiset优化；详细介绍了multiset的特性及在本题中的应用；代码实现清晰，利用multiset自动排序特性简化操作。
 - **个人心得**：最初采用排序和DP的方法超时，意识到 $k$ 的范围较大后，引入multiset优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b)	for(int i=a;i<=b;i++)
#define Rep(i,a,b)	for(int i=a;i>=b;i--)
inline long long read()
{
	char c=getchar();long long x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;	
}
long long ans,L[1000005],R[1000005];
int N,M,K,P,A[1005][1005];
multiset<long long> G;
int	main()
{
	N=read();M=read();K=read();P=read();
	For(i,1,N)
		For(j,1,M)
			A[i][j]=read();
	G.clear();
	For(i,1,N)
	{
		int t=0;
		For(j,1,M)
		t+=A[i][j];
		G.insert(t);
	}
	For(i,1,K)
	{
		multiset<long long>::iterator x=--(G.end());
		long long t=*x;
		G.erase(x);
		G.insert(t-M*P);
		L[i]=L[i-1]+t;
	}
	G.clear();
	For(j,1,M)
	{
		int t=0;
		For(i,1,N)
			t+=A[i][j];
		G.insert(t);
	}
	For(i,1,K)
	{
		multiset<long long>::iterator x=--(G.end());
		long long t=*x;
		G.erase(x);
		G.insert(t-N*P);
		R[i]=R[i-1]+t;
	}
	ans=-(1ll<<60);
	For(i,0,K)
		ans=max(ans,L[i]+R[K-i]-1ll*i*(K-i)*P);
	printf("%lld\n",ans);
}
```
核心代码实现思想：读入矩阵数据后，先两次使用 `For` 循环分别计算每行和每列的和，并插入 `multiset` 中。之后两次通过循环，每次从 `multiset` 取出最大和，更新累计和数组 `L` 与 `R`，并将操作后的和重新插入 `multiset`。最后通过枚举行操作次数 `i`，计算并更新最大愉悦值 `ans`。

#### Hisaishi_Kanade（4星）
 - **关键亮点**：先分析错误贪心思路，引出正确的分开贪心策略；清晰定义辅助数组和函数，详细阐述贪心转移过程；代码实现简洁明了，利用优先队列实现贪心选择。
 - **个人心得**：无

```cpp
#include <queue>
#include <vector>
#include <algorithm>
int n,m,k,p,i,j;
std::priority_queue<long long> q;
long long f[2][1000005],row[1005],col[1005],a[1005][1005];
int main()
{
	int t=1;
	while(t--)
	{
		long long ret=-(1ll<<60),delta,mid;
		n=read();m=read();
		k=read();p=read();
		for(i=1;i<=k;++i)
			f[0][i]=f[1][i]=0;
		for(i=1;i<=n;++i)
			row[i]=0;
		for(i=1;i<=m;++i)
			col[i]=0;
		for(i=1;i<=n;++i)
			for(j=1;j<=m;++j)
				a[i][j]=read();
		for(i=1;i<=n;++i)
			for(j=1;j<=m;++j)
				row[i]+=a[i][j];
		for(i=1;i<=n;++i)
			for(j=1;j<=m;++j)
				col[j]+=a[i][j];
		while(!q.empty())
			q.pop();
		for(i=1;i<=n;++i)
		{
			q.push(row[i]);
		}
		delta=m*p;
		for(i=1;i<=k;++i)
		{
			f[0][i]=f[0][i-1]+q.top();
			mid=q.top();
			q.pop();
			q.push(mid-delta);
//			printf("%lld\n",q.top());
		}
		while(!q.empty())
			q.pop();
		for(i=1;i<=m;++i)
		{
			q.push(col[i]);
		}
		delta=n*p;
		for(i=1;i<=k;++i)
		{
			f[1][i]=f[1][i-1]+q.top();
			mid=q.top();
			q.pop();
			q.push(mid-delta);
		}
		for(i=0;i<=k;++i)
		{
			ret=std::max(ret,f[0][i]+f[1][k-i]-1ll*i*(k-i)*p);
		}
		printf("%lld\n",ret);
	}
	return 0;
}
```
核心代码实现思想：读入矩阵数据后，通过循环计算每行和每列的和并分别存入数组 `row` 和 `col`。然后两次利用优先队列，每次从优先队列取出最大和，更新 `f[0][i]` 或 `f[1][i]`，并将操作后的和重新加入优先队列。最后通过枚举行操作次数 `i`，计算并更新最大愉悦值 `ret`。

### 最优关键思路或技巧
 - **利用贪心策略**：基于操作顺序不影响答案这一性质，分别对行和列进行贪心选择，每次选取和最大的行或列进行操作。
 - **数据结构选择**：使用优先队列或multiset来高效维护行和列的和，便于快速找到最大值并动态更新。
 - **处理相交部分**：考虑行操作和列操作的相交情况，通过减去相交次数与 $p$ 的乘积来准确计算总愉悦值。

### 拓展思路
此类题目属于矩阵操作与最优值求解结合的问题，常见的拓展方向有：
 - **改变操作类型**：如不仅是行或列的减法操作，可能增加乘法、交换等操作，增加问题复杂度。
 - **增加限制条件**：例如限制操作的顺序、操作的次数上限不同等，需重新分析贪心策略或寻找新的算法。

### 相似知识点题目推荐
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过贪心策略对物品进行分组，以满足一定条件下的最优解，与本题贪心选择思路类似。
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：同样涉及贪心策略，根据题目条件选择最优方案，锻炼贪心思维。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：利用贪心算法对排队顺序进行优化，以达到总等待时间最短的目的，与本题在贪心选择的逻辑上有相似之处。 

---
处理用时：131.69秒