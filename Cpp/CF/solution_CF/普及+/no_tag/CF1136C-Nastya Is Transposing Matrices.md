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

# 题解

## 作者：limuloo (赞：1)

（1）可以发现不论怎么操作，一直都是同一条副对角线的元素在互换。

（2）选择一个2x2的矩阵就能实现一条副对角线上相邻两个元素的互换，同时不影响其他元素的位置。

结论：只要比较A、B两个矩阵的每一条副对角线上的元素一样就可。

技巧：mat[i][j]在第i+j条副对角线上

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


---

