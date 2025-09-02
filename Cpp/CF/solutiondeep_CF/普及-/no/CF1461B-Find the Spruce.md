# 题目信息

# Find the Spruce

## 题目描述

Holidays are coming up really soon. Rick realized that it's time to think about buying a traditional spruce tree. But Rick doesn't want real trees to get hurt so he decided to find some in an $ n \times m $ matrix consisting of "\*" and ".".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461B/0f830498ab169a471030eeb85fc12c395e76f5ca.png)To find every spruce first let's define what a spruce in the matrix is. A set of matrix cells is called a spruce of height $ k $ with origin at point $ (x, y) $ if:

- All cells in the set contain an "\*".
- For each $ 1 \le i \le k $ all cells with the row number $ x+i-1 $ and columns in range $ [y - i + 1, y + i - 1] $ must be a part of the set. All other cells cannot belong to the set.

Examples of correct and incorrect spruce trees:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461B/2ce2df8e09c4fc74a3e149e5906821e41a5e552f.png)Now Rick wants to know how many spruces his $ n \times m $ matrix contains. Help Rick solve this problem.

## 说明/提示

In the first test case the first spruce of height $ 2 $ has its origin at point $ (1, 2) $ , the second spruce of height $ 1 $ has its origin at point $ (1, 2) $ , the third spruce of height $ 1 $ has its origin at point $ (2, 1) $ , the fourth spruce of height $ 1 $ has its origin at point $ (2, 2) $ , the fifth spruce of height $ 1 $ has its origin at point $ (2, 3) $ .

In the second test case the first spruce of height $ 1 $ has its origin at point $ (1, 2) $ , the second spruce of height $ 1 $ has its origin at point $ (2, 1) $ , the third spruce of height $ 1 $ has its origin at point $ (2, 2) $ .

## 样例 #1

### 输入

```
4
2 3
.*.
***
2 3
.*.
**.
4 5
.***.
*****
*****
*.*.*
5 7
..*.*..
.*****.
*******
.*****.
..*.*..```

### 输出

```
5
3
23
34```

# AI分析结果

### 题目内容
# 寻找云杉树

## 题目描述
假期马上就要到了。里克意识到是时候考虑买一棵传统的云杉树了。但里克不想伤害真正的树木，所以他决定在一个由“*”和“.”组成的 $n \times m$ 矩阵中寻找。

![云杉树示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461B/0f830498ab169a471030eeb85fc12c395e76f5ca.png)为了找到每一棵云杉树，首先让我们定义矩阵中的云杉树是什么。一组矩阵单元格被称为高度为 $k$ 且原点在点 $(x, y)$ 的云杉树，如果：
- 该组中的所有单元格都包含“*”。
- 对于每个 $1 \leq i \leq k$，行号为 $x + i - 1$ 且列号在范围 $[y - i + 1, y + i - 1]$ 内的所有单元格都必须是该组的一部分。其他所有单元格不能属于该组。

正确和不正确的云杉树示例：

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461B/2ce2df8e09c4fc74a3e149e5906821e41a5e552f.png)现在里克想知道他的 $n \times m$ 矩阵中包含多少棵云杉树。帮助里克解决这个问题。

## 说明/提示
在第一个测试用例中，第一棵高度为 $2$ 的云杉树的原点在点 $(1, 2)$ ，第二棵高度为 $1$ 的云杉树的原点在点 $(1, 2)$ ，第三棵高度为 $1$ 的云杉树的原点在点 $(2, 1)$ ，第四棵高度为 $1$ 的云杉树的原点在点 $(2, 2)$ ，第五棵高度为 $1$ 的云杉树的原点在点 $(2, 3)$ 。

在第二个测试用例中，第一棵高度为 $1$ 的云杉树的原点在点 $(1, 2)$ ，第二棵高度为 $1$ 的云杉树的原点在点 $(2, 1)$ ，第三棵高度为 $1$ 的云杉树的原点在点 $(2, 2)$ 。

## 样例 #1
### 输入
```
4
2 3
.*.
***
2 3
.*.
**.
4 5
.***.
*****
*****
*.*.*
5 7
..*.*..
.*****.
*******
.*****.
..*.*..
```
### 输出
```
5
3
23
34
```

### 算法分类
枚举

### 题解综合分析与结论
这些题解的核心思路都是通过不同方式对矩阵中的每个可能作为云杉树顶端的位置进行检查，判断能否构成云杉树，并统计数量。主要区别在于检查方式和优化手段。有的题解采用动态规划的思想来减少重复计算，有的通过前缀和优化判断过程，还有的直接暴力枚举所有可能情况。

### 所选的题解
 - **作者：Lynkcat (5星)**
    - **关键亮点**：使用三维数组 $f_{i,j,k}$ 表示以 $(i, j)$ 为根能否组成高度为 $k$ 的云杉树，通过状态转移方程 $f_{i,j,k}$ 依赖于 $f_{i + 1,j - 1,k - 1}$、$f_{i + 1,j,k - 1}$ 和 $f_{i + 1,j + 1,k - 1}$ 来递推，并用前缀和数组 $s$ 优化判断过程，时间复杂度分析合理，代码简洁高效。
    - **重点代码**：
```cpp
int n,m,ans,f[3][N][N],a[N][N],s[N][N],T;
string st;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>T;
	while (T--)
	{
		cin>>n>>m;ans=0;
		memset(f,0,sizeof(f));
		for (int i=1;i<=n;i++)
		{
			cin>>st;
			for (int j=0;j<st.length();j++)
				if (st[j]=='*') a[i][j+1]=1,f[1][i][j+1]=1,ans++; else a[i][j+1]=0;
		}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) s[i][j]=s[i][j-1]+a[i][j];
		for (int k=2;k<=n;k++)
		{
			memset(f[k&1],0,sizeof(f[k&1]));
			for (int i=1;i+k-1<=n;i++)
				for (int j=k;j+k-1<=m;j++)
				if (a[i][j])
				{
					if (s[i+1][j+1]-s[i+1][j-2]==3)
						f[k&1][i][j]=f[(k+1)&1][i+1][j-1]&f[(k+1)&1][i+1][j]&f[(k+1)&1][i+1][j+1],ans+=f[k&1][i][j];
				}
		}
		writeln(ans);
	}
}
```
核心实现思想：先初始化数据，通过前缀和数组 $s$ 记录每行的“*”数量，然后利用状态转移方程递推不同高度的云杉树情况，同时更新答案。

 - **作者：pies_0x (4星)**
    - **关键亮点**：定义状态 $dp_{i,j}$ 表示以 $(i, j)$ 为树顶的树的最高高度，通过状态转移方程 $dp_{i,j}=\min(dp_{i + 1,j - 1},dp_{i + 1,j + 1})+1$ 计算，并且注意到要倒序遍历以保证状态转移时所需数据已计算，思路清晰，代码实现简洁明了。
    - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

#define N 505

int n,m;
char a[N][N];
int dp[N][N];

signed main()
{
	int tt;
	scanf("%d",&tt);
	while(tt--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				a[i][j]=getchar(),
				j-=(a[i][j]!='.'&&a[i][j]!='*');
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(a[i][j]=='*')
					dp[i][j]=1;
		for(int i=n-1;i>=1;--i)  //要倒序
			for(int j=2;j<m;++j)
				if(a[i][j]=='*'&&a[i+1][j-1]=='*'&&a[i+1][j]=='*'&&a[i+1][j+1]=='*')
					dp[i][j]=min(dp[i+1][j-1],dp[i+1][j+1])+1;
		int ans=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(a[i][j]=='*')
					ans+=dp[i][j];
		printf("%d",ans);putchar('\n');
	}
	return 0;
}
```
核心实现思想：先初始化 $dp$ 数组，然后通过倒序遍历利用状态转移方程更新 $dp$ 值，最后累加所有“*”位置的 $dp$ 值得到答案。

 - **作者：过氧化氢_syq0057 (4星)**
    - **关键亮点**：采用暴力枚举从每个“*”开始向下找云杉树，利用前缀和优化判断某一层是否满足云杉树条件，代码逻辑清晰，对时间复杂度分析准确，考虑到题目的数据范围虽然理论时间复杂度较高但实际能通过。
    - **重点代码**：
```cpp
bool check(int x, int l, int r) {
	if (sum[x][r] - sum[x][l - 1]!= (r - l + 1)) return 0;//前缀和优化
	return 1;
}
int main() {
	scanf("%d", &T);
	int I, J;
	while (T--) {
		ans = 0;
		scanf("%d%d", &n, &m);
		getchar();
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				a[i][j] = getchar();
			}
			getchar();
		}//字符串读入不要用scanf
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				sum[i][j] = sum[i][j - 1] + (a[i][j] == '*');//前缀和
			}
		}
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				if (a[i][j] == '*') {
					ans++;
					I = 1, J = 1;//能往下几层
					while (j - J >= 1 && j + J <= m && i + I <= n && check(i + I, j - J, j + J))
						ans++, I++, J++;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```
核心实现思想：先读入数据并计算前缀和，然后对每个“*”位置，通过 `check` 函数利用前缀和判断能否向下扩展云杉树，能则更新答案。

### 最优关键思路或技巧
1. **状态定义与转移**：如 `Lynkcat` 和 `pies_0x` 通过合理定义状态，利用动态规划思想减少重复计算，提高效率。
2. **前缀和优化**：多个题解利用前缀和数组快速判断某行特定区间内“*”的数量，优化判断云杉树每层是否满足条件的过程。

### 可拓展思路
同类型题通常是在矩阵中寻找特定形状的图形，类似算法套路为通过合理定义状态（如本题的树高），利用动态规划递推或者通过前缀和等方式优化暴力枚举过程。

### 相似知识点洛谷题目
1. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：涉及动态规划，通过状态转移解决组合问题。
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：字符串处理结合枚举判断，与本题对矩阵元素的枚举判断有相似之处。
3. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：动态规划经典题目，锻炼状态定义和转移方程推导能力，与本题动态规划思路相关。

### 个人心得摘录与总结
无。 

---
处理用时：98.13秒