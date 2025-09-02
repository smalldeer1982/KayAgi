# 题目信息

# Nastya Is Transposing Matrices

## 题目描述

Nastya came to her informatics lesson, and her teacher who is, by the way, a little bit famous here gave her the following task.

Two matrices $ A $ and $ B $ are given, each of them has size $ n \times m $ . Nastya can perform the following operation to matrix $ A $ unlimited number of times:

- take any square square submatrix of $ A $ and transpose it (i.e. the element of the submatrix which was in the $ i $ -th row and $ j $ -th column of the submatrix will be in the $ j $ -th row and $ i $ -th column after transposing, and the transposed submatrix itself will keep its place in the matrix $ A $ ).

Nastya's task is to check whether it is possible to transform the matrix $ A $ to the matrix $ B $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1136C/7711a999558fa948bea147de25b2bda2e2007e83.png)Example of the operationAs it may require a lot of operations, you are asked to answer this question for Nastya.

A square submatrix of matrix $ M $ is a matrix which consist of all elements which comes from one of the rows with indeces $ x, x+1, \dots, x+k-1 $ of matrix $ M $ and comes from one of the columns with indeces $ y, y+1, \dots, y+k-1 $ of matrix $ M $ . $ k $ is the size of square submatrix. In other words, square submatrix is the set of elements of source matrix which form a solid square (i.e. without holes).

## 说明/提示

Consider the third example. The matrix $ A $ initially looks as follows.

 $ $$$ \begin{bmatrix} 1 & 2 & 3\\ 4 & 5 & 6\\ 7 & 8 & 9 \end{bmatrix}  $ $ </p><p>Then we choose the whole matrix as transposed submatrix and it becomes</p><p> $ $  \begin{bmatrix} 1 & 4 & 7\\ 2 & 5 & 8\\ 3 & 6 & 9 \end{bmatrix}  $ $ </p><p>Then we transpose the submatrix with corners in cells  $ (2, 2) $  and  $ (3, 3) $ . </p><p> $ $  \begin{bmatrix} 1 & 4 & 7\\ 2 & \textbf{5} & \textbf{8}\\ 3 & \textbf{6} & \textbf{9} \end{bmatrix}  $ $ </p><p>So matrix becomes</p><p> $ $  \begin{bmatrix} 1 & 4 & 7\\ 2 & 5 & 6\\ 3 & 8 & 9 \end{bmatrix}  $ $ </p><p>and it is  $ B$$$.

## 样例 #1

### 输入

```
2 2
1 1
6 1
1 6
1 1
```

### 输出

```
YES```

## 样例 #2

### 输入

```
2 2
4 4
4 5
5 4
4 4
```

### 输出

```
NO```

## 样例 #3

### 输入

```
3 3
1 2 3
4 5 6
7 8 9
1 4 7
2 5 6
3 8 9
```

### 输出

```
YES```

# AI分析结果

### 题目内容中文重写
# 娜斯佳转置矩阵

## 题目描述
娜斯佳来上信息学课，她那位在当地有点小名气的老师给了她如下任务。

给定两个矩阵 $A$ 和 $B$，每个矩阵的大小都是 $n \times m$。娜斯佳可以对矩阵 $A$ 进行无限次以下操作：
- 选取矩阵 $A$ 的任意一个正方形子矩阵并对其进行转置（即转置后，子矩阵中原本位于第 $i$ 行第 $j$ 列的元素将位于第 $j$ 行第 $i$ 列，且转置后的子矩阵仍保持在矩阵 $A$ 中的原有位置）。

娜斯佳的任务是检查是否有可能将矩阵 $A$ 变换为矩阵 $B$。

![操作示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1136C/7711a999558fa948bea147de25b2bda2e2007e83.png)

矩阵 $M$ 的正方形子矩阵是指由矩阵 $M$ 中索引为 $x, x + 1, \dots, x + k - 1$ 的行和索引为 $y, y + 1, \dots, y + k - 1$ 的列中的所有元素组成的矩阵。$k$ 是正方形子矩阵的大小。换句话说，正方形子矩阵是源矩阵中形成一个实心正方形（即没有空洞）的元素集合。

## 说明/提示
考虑第三个样例。矩阵 $A$ 最初如下所示：
$$
\begin{bmatrix}
1 & 2 & 3\\
4 & 5 & 6\\
7 & 8 & 9
\end{bmatrix}
$$
然后我们选择整个矩阵作为转置的子矩阵，它变为：
$$
\begin{bmatrix}
1 & 4 & 7\\
2 & 5 & 8\\
3 & 6 & 9
\end{bmatrix}
$$
接着我们转置以单元格 $(2, 2)$ 和 $(3, 3)$ 为角的子矩阵。
$$
\begin{bmatrix}
1 & 4 & 7\\
2 & \textbf{5} & \textbf{8}\\
3 & \textbf{6} & \textbf{9}
\end{bmatrix}
$$
于是矩阵变为：
$$
\begin{bmatrix}
1 & 4 & 7\\
2 & 5 & 6\\
3 & 8 & 9
\end{bmatrix}
$$
这就是矩阵 $B$。

## 样例 #1
### 输入
```
2 2
1 1
6 1
1 6
1 1
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
2 2
4 4
4 5
5 4
4 4
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
3 3
1 2 3
4 5 6
7 8 9
1 4 7
2 5 6
3 8 9
```
### 输出
```
YES
```

### 算法分类
数学

### 综合分析与结论
本题的核心在于发现矩阵操作的规律，即无论如何对矩阵 $A$ 进行转置操作，始终是同一条副对角线上的元素在互换，且通过选择 2x2 的子矩阵可以实现副对角线上相邻两个元素的互换而不影响其他元素。因此，只要比较矩阵 $A$ 和矩阵 $B$ 的每一条副对角线上的元素是否相同，就可以判断能否将矩阵 $A$ 变换为矩阵 $B$。

### 所选题解
- 作者：limuloo (赞：1)，4星。
  - 关键亮点：思路清晰，准确抓住了矩阵操作的规律，通过将矩阵元素按副对角线分类存储，再对每一条副对角线上的元素排序后比较，代码实现简洁明了。

### 重点代码
```cpp
int n; int m; vector<int>b1[1005],b2[1005];

bool check(vector<int>a,vector<int>b){
	if(a.size()!=b.size()) return false;
	for(int i=0;i<a.size();++i) if(a[i]!=b[i]) return false;
	return true;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j){
		int x; scanf("%d",&x); b1[i+j].push_back(x);
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j){
		int x; scanf("%d",&x); b2[i+j].push_back(x);
	}
	for(int i=1;i<=n+m;++i){
		sort(b1[i].begin(),b1[i].end());
		sort(b2[i].begin(),b2[i].end());
		if(!check(b1[i],b2[i])) return puts("NO"),0;
	}
	puts("YES");
	return 0;
}
```
**核心实现思想**：
1. 定义两个数组 `b1` 和 `b2` 分别存储矩阵 $A$ 和矩阵 $B$ 按副对角线分类的元素。
2. 遍历矩阵 $A$ 和矩阵 $B$，将每个元素根据其所在的副对角线（`i + j`）存储到对应的数组中。
3. 对每一条副对角线上的元素进行排序。
4. 比较矩阵 $A$ 和矩阵 $B$ 对应副对角线上的元素是否相同，如果有不同则输出 `NO`，否则输出 `YES`。

### 扩展思路
同类型题目可能会有不同的矩阵操作规则，关键在于找出操作过程中不变的量，然后根据这些不变量来判断两个矩阵是否可以相互转换。类似的算法套路可以应用于其他矩阵变换问题，通过分析操作的性质，找到问题的关键特征进行求解。

### 推荐洛谷题目
1. P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
2. P1012 [拼数](https://www.luogu.com.cn/problem/P1012)
3. P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)

### 个人心得
本题解中未包含个人心得。

---
处理用时：39.67秒