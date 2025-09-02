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

# 题解

## 作者：XL4453 (赞：6)

### $\text{Difficulty : 1600}$
---
### 解题思路：

算是一个比较经典的 $\text{trick}$。

第一步操作是棋盘的一个平移。可以将整个棋盘复制三份构成一个 $2n\times 2n$ 的大棋盘，大棋盘中的每一个 $n\times n$ 的子棋盘相应地对应不同方式的平移。

第二步操作需要的次数只需要统计在对角线上的 $1$ 的个数，记为 $cnt$，和总共 $1$ 的个数，记为 $sum$，就能直接求出了，式子是：$sum+n-2cnt$。

然后问题就转化为每一个子棋盘上的对角线上有多少 $1$，这个问题可以直接用前缀和求解，$S_{i,j}$ 表示从位置 $(i,j)$        尽可能地向左上方按主对角线方向拓展路径上存在的 $1$ 的个数。那么每一次确定子矩形之后，只需要用右下角的 $S$ 减去左上角左上的 $S$ 就能确定当前子棋盘主对角线上的 $1$ 的个数了。

---
### 代码：

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


---

## 作者：jijidawang (赞：3)

这个翻译好毒瘤啊 .

正常题意：
> 给一个 $01$ 矩阵 $A$，你可以用 $0$ 代价做以下操作：
> - 所有位置循环向上移位 $1$ .
> - 所有位置循环向下移位 $1$ .
> - 所有位置循环向左移位 $1$ .
> - 所有位置循环向右移位 $1$ .
>
> 所有这样的操作 **做完之后**，你可以用 $1$ 代价做以下操作：
> - 选一个位置，然后把它异或 $1$ .
>
> 问要把给定矩阵 $A$ 变成单位矩阵 $I$ 至少需要多少贡献 .
***

题解：

因为这题非常简单于是写了个详细的题解 .

问题可以转化为做移位操作之后与单位矩阵有多少个位置不同 .

显然 $1$ 贡献只在对角线上，假设对角线上有 $a$ 个 $0$，总共有 $b$ 个 $0$ 则答案为 $n(n-1)-(b-a)+a=n^2-n-2a+b$ .

$b$ 可以直接统计，非常容易 .

循环移位的一个常见解法是复制两遍（这个操作你取模也能完成），我们把 $A$ 做如下变换：

$$A'\gets\begin{bmatrix}A&A\\A&A\end{bmatrix}$$

于是我们只需要对于每个点 $(x,y)$ 往右下走 $n$ 步计算 $0$ 的个数 $a$ 即可 .

对于我们每个找到的点 $(x,y)$ 形成的对角线局面，完全可以通过 $x-1$ 次向右移位与 $y-1$ 次向下移位完成 .

做完了 .

---

