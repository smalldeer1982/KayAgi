# 题目信息

# Ramesses and Corner Inversion

## 题目描述

Ramesses came to university to algorithms practice, and his professor, who is a fairly known programmer, gave him the following task.

You are given two matrices $ A $ and $ B $ of size $ n \times m $ , each of which consists of $ 0 $ and $ 1 $ only. You can apply the following operation to the matrix $ A $ arbitrary number of times: take any submatrix of the matrix $ A $ that has at least two rows and two columns, and invert the values in its corners (i.e. all corners of the submatrix that contain $ 0 $ , will be replaced by $ 1 $ , and all corners of the submatrix that contain $ 1 $ , will be replaced by $ 0 $ ). You have to answer whether you can obtain the matrix $ B $ from the matrix $ A $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/07e01026afbc60b96857b7392bf73ad937a6aa47.png)An example of the operation. The chosen submatrix is shown in blue and yellow, its corners are shown in yellow.Ramesses don't want to perform these operations by himself, so he asks you to answer this question.

A submatrix of matrix $ M $ is a matrix which consist of all elements which come from one of the rows with indices $ x_1, x_1+1, \ldots, x_2 $ of matrix $ M $ and one of the columns with indices $ y_1, y_1+1, \ldots, y_2 $ of matrix $ M $ , where $ x_1, x_2, y_1, y_2 $ are the edge rows and columns of the submatrix. In other words, a submatrix is a set of elements of source matrix which form a solid rectangle (i.e. without holes) with sides parallel to the sides of the original matrix. The corners of the submatrix are cells $ (x_1, y_1) $ , $ (x_1, y_2) $ , $ (x_2, y_1) $ , $ (x_2, y_2) $ , where the cell $ (i,j) $ denotes the cell on the intersection of the $ i $ -th row and the $ j $ -th column.

## 说明/提示

The examples are explained below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/e8b2b05f1d91acad1dd27cd7e9d641b53a14a9dc.png)Example 1.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/a67a1a76d04df99ed90143acfb49e6763fb445d5.png)Example 2.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/8179b88f909d57a1d5601735cc5b6ce16cfe2cb8.png)Example 3.

## 样例 #1

### 输入

```
3 3
0 1 0
0 1 0
1 0 0
1 0 0
1 0 0
1 0 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
6 7
0 0 1 1 0 0 1
0 1 0 0 1 0 1
0 0 0 1 0 0 1
1 0 1 0 1 0 0
0 1 0 0 1 0 1
0 1 0 1 0 0 1
1 1 0 1 0 1 1
0 1 1 0 1 0 0
1 1 0 1 0 0 1
1 0 1 0 0 1 0
0 1 1 0 1 0 0
0 1 1 1 1 0 1
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
3 4
0 1 0 1
1 0 1 0
0 1 0 1
1 1 1 1
1 1 1 1
1 1 1 1
```

### 输出

```
No
```

# AI分析结果

### 题目内容重写

#### Ramesses and Corner Inversion

**题目描述**

Ramesses来到大学进行算法练习，他的教授（一位知名的程序员）给他布置了以下任务。

给定两个大小为 $n \times m$ 的矩阵 $A$ 和 $B$，每个矩阵仅由 $0$ 和 $1$ 组成。你可以对矩阵 $A$ 进行任意次数的操作：选择矩阵 $A$ 的任意一个至少有两行两列的子矩阵，并将其四个角的值取反（即子矩阵的四个角中，$0$ 变为 $1$，$1$ 变为 $0$）。你需要回答是否可以通过这些操作将矩阵 $A$ 转换为矩阵 $B$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/07e01026afbc60b96857b7392bf73ad937a6aa47.png)  
操作示例。选择的子矩阵用蓝色和黄色标出，其四个角用黄色标出。

Ramesses不想自己执行这些操作，所以他请你来回答这个问题。

矩阵 $M$ 的子矩阵是指由矩阵 $M$ 的某几行和某几列的元素组成的矩阵，且这些行和列是连续的。子矩阵的四个角分别是 $(x_1, y_1)$、$(x_1, y_2)$、$(x_2, y_1)$、$(x_2, y_2)$，其中 $(i,j)$ 表示第 $i$ 行第 $j$ 列的元素。

**说明/提示**

样例解释如下。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/e8b2b05f1d91acad1dd27cd7e9d641b53a14a9dc.png)  
样例1。  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/a67a1a76d04df99ed90143acfb49e6763fb445d5.png)  
样例2。  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/8179b88f909d57a1d5601735cc5b6ce16cfe2cb8.png)  
样例3。

**样例 #1**

**输入**

```
3 3
0 1 0
0 1 0
1 0 0
1 0 0
1 0 0
1 0 0
```

**输出**

```
Yes
```

**样例 #2**

**输入**

```
6 7
0 0 1 1 0 0 1
0 1 0 0 1 0 1
0 0 0 1 0 0 1
1 0 1 0 1 0 0
0 1 0 0 1 0 1
0 1 0 1 0 0 1
1 1 0 1 0 1 1
0 1 1 0 1 0 0
1 1 0 1 0 0 1
1 0 1 0 0 1 0
0 1 1 0 1 0 0
0 1 1 1 1 0 1
```

**输出**

```
Yes
```

**样例 #3**

**输入**

```
3 4
0 1 0 1
1 0 1 0
0 1 0 1
1 1 1 1
1 1 1 1
1 1 1 1
```

**输出**

```
No
```

### 算法分类
**位运算**

### 题解分析与结论

#### 题解思路对比
1. **xht** 和 **tth37** 的题解思路相似，都是通过将矩阵 $A$ 和 $B$ 进行异或操作，得到需要修改的位置。然后检查每一行和每一列的异或和是否为偶数，如果是偶数则输出 "Yes"，否则输出 "No"。
2. **KagurazakaKano** 的题解思路是通过扫描矩阵，每次发现 $A$ 和 $B$ 中对应元素不同时，对 $2 \times 2$ 的子矩阵进行操作，最终检查矩阵是否相等。
3. **Sun_wtup** 和 **Silence_World** 的题解思路也是通过异或操作，检查每行每列的异或和是否为偶数。
4. **MILLOPE** 和 **Zechariah** 的题解思路与前面类似，都是通过异或操作和检查每行每列的异或和来判断是否可以通过操作将 $A$ 转换为 $B$。

#### 难点对比
- **xht** 和 **tth37** 的题解难点在于理解异或操作的性质，以及如何通过异或和判断是否可以通过操作将 $A$ 转换为 $B$。
- **KagurazakaKano** 的题解难点在于如何通过扫描矩阵并操作 $2 \times 2$ 的子矩阵来逐步将 $A$ 转换为 $B$。
- **Sun_wtup** 和 **Silence_World** 的题解难点在于如何高效地检查每行每列的异或和是否为偶数。
- **MILLOPE** 和 **Zechariah** 的题解难点在于如何通过异或操作和检查每行每列的异或和来判断是否可以通过操作将 $A$ 转换为 $B$。

#### 精炼结论
最优的思路是通过将矩阵 $A$ 和 $B$ 进行异或操作，得到需要修改的位置，然后检查每一行和每一列的异或和是否为偶数。如果所有行和列的异或和都是偶数，则可以通过操作将 $A$ 转换为 $B$，否则不能。

### 评分较高的题解

#### 1. xht (5星)
**关键亮点**：思路清晰，代码简洁，通过异或操作和检查每行每列的异或和来判断是否可以通过操作将 $A$ 转换为 $B$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 506;
int n, m, a[N][N], b[N][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &b[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] ^= b[i][j];
    for (int i = 1; i <= n; i++) {
        int o = 0;
        for (int j = 1; j <= m; j++)
            o ^= a[i][j];
        if (o) {
            puts("No");
            return 0;
        }
    }
    for (int j = 1; j <= m; j++) {
        int o = 0;
        for (int i = 1; i <= n; i++)
            o ^= a[i][j];
        if (o) {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}
```

#### 2. tth37 (4星)
**关键亮点**：思路清晰，代码简洁，通过异或操作和检查每行每列的异或和来判断是否可以通过操作将 $A$ 转换为 $B$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int M,N;
bool a[505][505];
bool b[505][505];
bool c[505][505];

int x[505],y[505];

int main(){
    scanf("%d%d",&M,&N);
    for(register int i=1;i<=M;++i){
        for(register int j=1;j<=N;++j){
            cin>>a[i][j];
        }
    }
    for(register int i=1;i<=M;++i){
        for(register int j=1;j<=N;++j){
            cin>>b[i][j];
        }
    }
    for(register int i=1;i<=M;++i){
        for(register int j=1;j<=N;++j){
            c[i][j]=a[i][j]^b[i][j];
            x[i]+=c[i][j];
            y[j]+=c[i][j];
        }
    }
    bool flag=true;
    for(register int i=1;i<=M;++i)
        if(x[i]&1) flag=false;
    for(register int i=1;i<=N;++i)
        if(y[i]&1) flag=false;
    if(flag)
        puts("Yes");
    else
        puts("No");
    return 0;
}
```

#### 3. KagurazakaKano (4星)
**关键亮点**：通过扫描矩阵并操作 $2 \times 2$ 的子矩阵来逐步将 $A$ 转换为 $B$，思路独特。

```cpp
#include <cstdio>
#define rep(i, a, b) for(int i = a; i <= b; ++i)

int a[505][505], b[505][505];

int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	rep(i, 1, m) rep(j, 1, n) scanf("%d", &a[i][j]);
	rep(i, 1, m) rep(j, 1, n) scanf("%d", &b[i][j]);
	rep(i, 1, m - 1) rep(j, 1, n - 1) if(a[i][j] != b[i][j]) {
		a[i][j] = (!a[i][j]);
		a[i + 1][j] = (!a[i + 1][j]);
		a[i + 1][j + 1] = (!a[i + 1][j + 1]);
		a[i][j + 1] = (!a[i][j + 1]);
	}
	rep(i, 1, m) rep(j, 1, n) if(a[i][j] != b[i][j]) return puts("No"), 0;
	return puts("Yes"), 0;
}
```

### 最优关键思路或技巧
通过将矩阵 $A$ 和 $B$ 进行异或操作，得到需要修改的位置，然后检查每一行和每一列的异或和是否为偶数。如果所有行和列的异或和都是偶数，则可以通过操作将 $A$ 转换为 $B$，否则不能。

### 可拓展之处
类似的问题可以通过异或操作和检查每行每列的异或和来判断是否可以通过某种操作将一个矩阵转换为另一个矩阵。

### 推荐题目
1. [CF1119C Ramesses and Corner Inversion](https://www.luogu.org/problemnew/show/CF1119C)
2. [CF1119D Ramesses and Corner Inversion](https://www.luogu.org/problemnew/show/CF1119D)
3. [CF1119E Ramesses and Corner Inversion](https://www.luogu.org/problemnew/show/CF1119E)

---
处理用时：75.71秒