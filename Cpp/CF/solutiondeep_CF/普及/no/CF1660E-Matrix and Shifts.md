# 题目信息

# Matrix and Shifts

## 题目描述

You are given a binary matrix $ A $ of size $ n \times n $ . Rows are numbered from top to bottom from $ 1 $ to $ n $ , columns are numbered from left to right from $ 1 $ to $ n $ . The element located at the intersection of row $ i $ and column $ j $ is called $ A_{ij} $ . Consider a set of $ 4 $ operations:

1. Cyclically shift all rows up. The row with index $ i $ will be written in place of the row $ i-1 $ ( $ 2 \le i \le n $ ), the row with index $ 1 $ will be written in place of the row $ n $ .
2. Cyclically shift all rows down. The row with index $ i $ will be written in place of the row $ i+1 $ ( $ 1 \le i \le n - 1 $ ), the row with index $ n $ will be written in place of the row $ 1 $ .
3. Cyclically shift all columns to the left. The column with index $ j $ will be written in place of the column $ j-1 $ ( $ 2 \le j \le n $ ), the column with index $ 1 $ will be written in place of the column $ n $ .
4. Cyclically shift all columns to the right. The column with index $ j $ will be written in place of the column $ j+1 $ ( $ 1 \le j \le n - 1 $ ), the column with index $ n $ will be written in place of the column $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1660E/12668e041dd8d5dbd1e7d6bac1040ded6cc9fc28.png)The $ 3 \times 3 $ matrix is shown on the left before the $ 3 $ -rd operation is applied to it, on the right — after.You can perform an arbitrary (possibly zero) number of operations on the matrix; the operations can be performed in any order.

After that, you can perform an arbitrary (possibly zero) number of new xor-operations:

- Select any element $ A_{ij} $ and assign it with new value $ A_{ij} \oplus 1 $ . In other words, the value of $ (A_{ij} + 1) \bmod 2 $ will have to be written into element $ A_{ij} $ .

Each application of this xor-operation costs one burl. Note that the $ 4 $ shift operations — are free. These $ 4 $ operations can only be performed before xor-operations are performed.

Output the minimum number of burles you would have to pay to make the $ A $ matrix unitary. A unitary matrix is a matrix with ones on the main diagonal and the rest of its elements are zeros (that is, $ A_{ij} = 1 $ if $ i = j $ and $ A_{ij} = 0 $ otherwise).

## 说明/提示

In the first test case, you can do the following: first, shift all the rows down cyclically, then the main diagonal of the matrix will contain only "1". Then it will be necessary to apply xor-operation to the only "1" that is not on the main diagonal.

In the second test case, you can make a unitary matrix by applying the operation $ 2 $ — cyclic shift of rows upward twice to the matrix.

## 样例 #1

### 输入

```
4

3
010
011
100

5
00010
00001
10000
01000
00100

2
10
10

4
1111
1011
1111
1111```

### 输出

```
1
0
2
11```

# AI分析结果

### 题目翻译

#### 矩阵与平移

**题目描述**

给定一个大小为 $n \times n$ 的二进制矩阵 $A$。行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $n$。位于第 $i$ 行第 $j$ 列的元素称为 $A_{ij}$。考虑以下四种操作：

1. **循环上移所有行**：第 $i$ 行的内容将移动到第 $i-1$ 行（$2 \le i \le n$），第 $1$ 行的内容将移动到第 $n$ 行。
2. **循环下移所有行**：第 $i$ 行的内容将移动到第 $i+1$ 行（$1 \le i \le n - 1$），第 $n$ 行的内容将移动到第 $1$ 行。
3. **循环左移所有列**：第 $j$ 列的内容将移动到第 $j-1$ 列（$2 \le j \le n$），第 $1$ 列的内容将移动到第 $n$ 列。
4. **循环右移所有列**：第 $j$ 列的内容将移动到第 $j+1$ 列（$1 \le j \le n - 1$），第 $n$ 列的内容将移动到第 $1$ 列。

你可以对矩阵执行任意次数（包括零次）的上述操作，操作可以以任意顺序进行。

之后，你可以执行任意次数（包括零次）的异或操作：

- 选择任意元素 $A_{ij}$ 并将其赋值为 $A_{ij} \oplus 1$。换句话说，将 $(A_{ij} + 1) \bmod 2$ 写入 $A_{ij}$。

每次应用异或操作的成本为 1 burl。注意，四种平移操作是免费的。这些平移操作只能在执行异或操作之前进行。

输出使矩阵 $A$ 成为单位矩阵所需的最小 burl 数。单位矩阵是指主对角线上的元素为 1，其余元素为 0 的矩阵（即 $A_{ij} = 1$ 如果 $i = j$，否则 $A_{ij} = 0$）。

**说明/提示**

在第一个测试用例中，你可以执行以下操作：首先，循环下移所有行，然后矩阵的主对角线将只包含 "1"。然后需要对不在主对角线上的唯一一个 "1" 应用异或操作。

在第二个测试用例中，你可以通过两次向上循环移位操作使矩阵成为单位矩阵。

**样例 #1**

**输入**

```
4

3
010
011
100

5
00010
00001
10000
01000
00100

2
10
10

4
1111
1011
1111
1111
```

**输出**

```
1
0
2
11
```

### 算法分类

**前缀和**

### 题解分析与结论

1. **XL4453 的题解**
   - **思路**：通过将原矩阵复制三份构成一个 $2n \times 2n$ 的大矩阵，利用前缀和计算每个子矩阵主对角线上的 $1$ 的个数，从而找到最小操作数。
   - **难点**：如何高效计算每个子矩阵主对角线上的 $1$ 的个数。
   - **评分**：4星
   - **关键亮点**：使用前缀和优化计算，思路清晰，代码实现简洁。

2. **jijidawang 的题解**
   - **思路**：将矩阵复制两遍，通过计算每个点 $(x,y)$ 往右下走 $n$ 步的 $0$ 的个数，找到最小操作数。
   - **难点**：如何通过复制矩阵来简化循环移位的计算。
   - **评分**：3星
   - **关键亮点**：复制矩阵的思路较为直观，但代码实现略显复杂。

### 最优关键思路

- **复制矩阵**：通过将原矩阵复制多份，可以简化循环移位的计算，避免复杂的边界处理。
- **前缀和优化**：利用前缀和快速计算每个子矩阵主对角线上的 $1$ 的个数，减少时间复杂度。

### 核心代码实现

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[4005][4005],cnt,sum[4005][4005],ans;
int SUM(int x,int y){
	if(x>2*n||y>2*n)return 0;
	if(x<0||y<0)return 0;
	return sum[x][y];
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		cnt=0;
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			scanf("%1d",&a[i][j]);
			cnt+=a[i][j];
		}
		for(int i=0;i<2*n;i++)
		for(int j=0;j<2*n;j++)
		a[i][j]=a[i%n][j%n];
		for(int i=0;i<2*n;i++)
		for(int j=0;j<2*n;j++)
		sum[i][j]=SUM(i-1,j-1)+a[i][j];
		ans=2147483647;
		for(int i=0;i<n+1;i++)
		for(int j=0;j<n+1;j++)
		ans=min(ans,n+cnt-2*(SUM(i+n-1,j+n-1)-SUM(i-1,j-1)));
		printf("%d\n",ans);
	}
	return 0;
}
```

### 可拓展之处

- **类似题目**：可以扩展到其他需要循环移位的矩阵操作问题，如矩阵旋转、矩阵平移等。
- **优化思路**：在其他需要快速计算子矩阵特征的问题中，可以考虑使用前缀和或其他预处理方法。

### 推荐题目

1. **P1880 [NOI1995] 石子合并** - 考察前缀和与动态规划的结合。
2. **P3374 【模板】树状数组 1** - 考察前缀和的应用。
3. **P3383 【模板】线性筛素数** - 考察数学与筛法的结合。

---
处理用时：37.66秒