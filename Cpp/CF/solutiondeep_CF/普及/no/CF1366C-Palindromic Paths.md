# 题目信息

# Palindromic Paths

## 题目描述

You are given a matrix with $ n $ rows (numbered from $ 1 $ to $ n $ ) and $ m $ columns (numbered from $ 1 $ to $ m $ ). A number $ a_{i, j} $ is written in the cell belonging to the $ i $ -th row and the $ j $ -th column, each number is either $ 0 $ or $ 1 $ .

A chip is initially in the cell $ (1, 1) $ , and it will be moved to the cell $ (n, m) $ . During each move, it either moves to the next cell in the current row, or in the current column (if the current cell is $ (x, y) $ , then after the move it can be either $ (x + 1, y) $ or $ (x, y + 1) $ ). The chip cannot leave the matrix.

Consider each path of the chip from $ (1, 1) $ to $ (n, m) $ . A path is called palindromic if the number in the first cell is equal to the number in the last cell, the number in the second cell is equal to the number in the second-to-last cell, and so on.

Your goal is to change the values in the minimum number of cells so that every path is palindromic.

## 说明/提示

The resulting matrices in the first three test cases:

 $ \begin{pmatrix} 1 & 1\\ 0 & 1 \end{pmatrix} $  $ \begin{pmatrix} 0 & 0 & 0\\ 0 & 0 & 0 \end{pmatrix} $  $ \begin{pmatrix} 1 & 0 & 1 & 1 & 1 & 1 & 1\\ 0 & 1 & 1 & 0 & 1 & 1 & 0\\ 1 & 1 & 1 & 1 & 1 & 0 & 1 \end{pmatrix} $

## 样例 #1

### 输入

```
4
2 2
1 1
0 1
2 3
1 1 0
1 0 0
3 7
1 0 1 1 1 1 1
0 0 0 0 0 0 0
1 1 1 1 1 0 1
3 5
1 0 1 0 0
1 1 1 1 0
0 0 1 0 0```

### 输出

```
0
3
4
4```

# AI分析结果

### 题目内容重写

#### 回文路径

##### 题目描述

给定一个矩阵，该矩阵有 $n$ 行（编号从 $1$ 到 $n$）和 $m$ 列（编号从 $1$ 到 $m$）。在矩阵的第 $i$ 行第 $j$ 列的单元格中写有一个数字 $a_{i, j}$，每个数字要么是 $0$，要么是 $1$。

一个芯片最初位于单元格 $(1, 1)$，它将移动到单元格 $(n, m)$。在每次移动中，芯片要么移动到当前行的下一个单元格，要么移动到当前列的下一个单元格（如果当前单元格是 $(x, y)$，那么移动后它可以是 $(x + 1, y)$ 或 $(x, y + 1)$）。芯片不能离开矩阵。

考虑芯片从 $(1, 1)$ 到 $(n, m)$ 的每条路径。如果路径中第一个单元格的数字等于最后一个单元格的数字，第二个单元格的数字等于倒数第二个单元格的数字，依此类推，则称该路径为回文路径。

你的目标是改变最少数量的单元格中的值，使得每条路径都是回文路径。

##### 说明/提示

前三个测试用例的结果矩阵如下：

$ \begin{pmatrix} 1 & 1\\ 0 & 1 \end{pmatrix} $  $ \begin{pmatrix} 0 & 0 & 0\\ 0 & 0 & 0 \end{pmatrix} $  $ \begin{pmatrix} 1 & 0 & 1 & 1 & 1 & 1 & 1\\ 0 & 1 & 1 & 0 & 1 & 1 & 0\\ 1 & 1 & 1 & 1 & 1 & 0 & 1 \end{pmatrix} $

##### 样例 #1

###### 输入

```
4
2 2
1 1
0 1
2 3
1 1 0
1 0 0
3 7
1 0 1 1 1 1 1
0 0 0 0 0 0 0
1 1 1 1 1 0 1
3 5
1 0 1 0 0
1 1 1 1 0
0 0 1 0 0
```

###### 输出

```
0
3
4
4
```

### 算法分类
- **组合数学**

### 题解分析与结论

#### 题解对比与总结

1. **Fairicle 的题解**
   - **关键思路**：利用横纵坐标之和相等的点集必须相同的性质，统计每对对称点的0和1的数量，取最小值作为需要更改的单元格数。
   - **难点**：处理回文长度为奇数和偶数时的不同情况。
   - **代码实现**：通过二维数组统计每对对称点的0和1的数量，然后计算需要更改的单元格数。
   - **评分**：4星
   - **关键亮点**：清晰地处理了奇偶长度的回文路径，代码简洁高效。

2. **45dinо 的题解**
   - **关键思路**：将矩阵中的点按照横纵坐标之和分组，统计每组中0和1的数量，计算完全匹配的代价。
   - **难点**：理解并实现分组统计的逻辑。
   - **代码实现**：使用一维数组统计每组中0和1的数量，然后计算需要更改的单元格数。
   - **评分**：4星
   - **关键亮点**：通过分组统计简化了问题，代码清晰易懂。

3. **3_14 的题解**
   - **关键思路**：将矩阵中的点按照与起点的距离分组，统计每组中0和1的数量，计算需要更改的单元格数。
   - **难点**：理解并实现分组统计的逻辑。
   - **代码实现**：使用二维数组统计每组中0和1的数量，然后计算需要更改的单元格数。
   - **评分**：4星
   - **关键亮点**：通过分组统计简化了问题，代码清晰易懂。

#### 最优关键思路或技巧
- **分组统计**：将矩阵中的点按照横纵坐标之和或与起点的距离分组，统计每组中0和1的数量，计算需要更改的单元格数。这种方法简化了问题，使得计算更加高效。

#### 可拓展之处
- **类似问题**：在处理矩阵中的路径问题时，可以尝试将点按照某种规则分组，然后统计每组的属性，从而简化问题。

#### 推荐题目
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

### 精选题解

#### Fairicle 的题解
- **星级**：4星
- **关键亮点**：清晰地处理了奇偶长度的回文路径，代码简洁高效。
- **核心代码**：
```cpp
#define ll long long
#define ri register int
#define N 100
int t,n,m,a[40][40],c[65][2];
int main(){
	t=rd();
	while(t--){
		int ans=0;
		n=rd(),m=rd();
		memset(a,0,sizeof(a));
		memset(c,0,sizeof(c));
		for(ri i=1;i<=n;++i) for(ri j=1;j<=m;++j) a[i][j]=rd(),c[i+j][0]+=(a[i][j]==0),c[i+j][1]+=(a[i][j]==1);
		if((n+m)%2==1){
			for(ri i=2;i<=(n+m+2)/2;++i){
				ans+=c[i][0]+c[i][1]+c[n+m+2-i][0]+c[n+m+2-i][1]-max(c[i][0]+c[n+m+2-i][0],c[i][1]+c[n+m+2-i][1]);
			}
		}
		else{
			for(ri i=2;i<(n+m+2)/2;++i){
				ans+=c[i][0]+c[i][1]+c[n+m+2-i][0]+c[n+m+2-i][1]-max(c[i][0]+c[n+m+2-i][0],c[i][1]+c[n+m+2-i][1]);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

#### 45dinо 的题解
- **星级**：4星
- **关键亮点**：通过分组统计简化了问题，代码清晰易懂。
- **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,ans,num0[61],num1[61],a;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		ans=0;
		memset(num0,0,sizeof(num0));
		memset(num1,0,sizeof(num1));
		for(int i=1;i<=n;i++)
			for(int l=1;l<=m;l++)
			{
				scanf("%d",&a);
				if(a&1)
					num0[i+l-1]++;
				else
					num1[i+l-1]++;
			}
		for(int i=1;i*2<n+m;i++)
			ans+=min(num0[i]+num0[n+m-i],num1[i]+num1[n+m-i]);
		cout<<ans<<endl;
	}
	return 0;
}
```

#### 3_14 的题解
- **星级**：4星
- **关键亮点**：通过分组统计简化了问题，代码清晰易懂。
- **核心代码**：
```cpp
#include<bits/stdc++.h>
#define lcm(x,y) x/__gcd(x,y)*y;
#define str to_string
using namespace std;
using ll=long long;
const int MAX=1e5+1;
const double EPS=1e-6;
int n,m,t;
void work(){
	cin>>n>>m;
	vector<vector<int>>a(n,vector<int>(m));
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	vector<vector<int>>cnt(n+m-1,vector<int>(2));
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cnt[i+j][a[i][j]]++;
	int ans=0;
	for(int i=0;i<=n+m-2;i++){
		int j=n+m-2-i;
		if(i<=j)continue;
		ans+=min(cnt[i][0]+cnt[j][0],cnt[i][1]+cnt[j][1]);
	}
	cout<<ans<<'\n';
	return;
}
int main(){
	cin>>t;
	while(t--)work();
	return 0;
}
```

---
处理用时：59.56秒