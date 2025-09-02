# Similar Arrays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2017-qualc/tasks/code_festival_2017_qualc_b

$ 2 $ つの長さ $ N $ の整数列 $ x_1,\ x_2,\ ...,\ x_N $ と $ y_1,\ y_2,\ ...,\ y_N $ が「似ている」とは、 任意の $ i $ ($ 1\ \leq\ i\ \leq\ N $) に対して $ |x_i\ -\ y_i|\ \leq\ 1 $ が成り立つことをいうものとします。

とくに、どの整数列もその数列自身と似ていると考えます。

整数 $ N $ および長さ $ N $ の整数列 $ A_1,\ A_2,\ ...,\ A_N $ が与えられます。

$ A $ と似ている整数列 $ b_1,\ b_2,\ ...,\ b_N $ であって、すべての項の積 $ b_1\ b_2\ ...\ b_N $ が偶数となるものはいくつあるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10 $
- $ 1\ \leq\ A_i\ \leq\ 100 $

### Sample Explanation 1

条件を満たす整数列は以下の $ 7 $ 個あります。 - $ 1,\ 2 $ - $ 1,\ 4 $ - $ 2,\ 2 $ - $ 2,\ 3 $ - $ 2,\ 4 $ - $ 3,\ 2 $ - $ 3,\ 4 $

## 样例 #1

### 输入

```
2
2 3```

### 输出

```
7```

## 样例 #2

### 输入

```
3
3 3 3```

### 输出

```
26```

## 样例 #3

### 输入

```
1
100```

### 输出

```
1```

## 样例 #4

### 输入

```
10
90 52 56 71 44 8 13 30 57 84```

### 输出

```
58921```

# 题解

## 作者：wuwendongxi (赞：2)

### 题意：
给你一个长为 $N$ 的序列 $A$，求数列 $B$ 的数量满足 $B$ 与 $A$ 相似且 $B$ 的所有元素乘积为偶数。

定义 $abs(A_i-B_i)\leq1$ 为相似。

### 思路：
- 发现 $B_i$ 只可能等于 $A_i$，$A_i -1$，$A_i +1$，即每个数只有三种取值；又因为很难找到乘积是偶数的序列，所以用序列总数减去乘积为奇数的序列数量。

### 代码：
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int n,ans=1,bad=1;
int main()
{
	scanf("%d",&n);
	for(int i=0,x;i<n;++i){
		scanf("%d",&x),ans*=3;
		if(x%2==0) bad*=2;
	}
	cout<<ans-bad<<'\n';
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个长度为 $n$ 的序列 $a$。定义两个序列 $x,y$ 是相似的，当且仅当 $\forall i\in[1,n],|x_i-y_i|\leqslant 1$。请你求出有多少个序列 $b$，使得：

- 序列 $a,b$ 相似。
- 序列 $b$ 的所有数的乘积为偶数。

**数据范围：$1\leqslant n\leqslant 10$，$1\leqslant a_i\leqslant 100$。**
## Solution
根据题意我们不难发现，对于序列 $b$ 每一个位置上面的数，其与对应位置上序列 $a$ 的数的差仅可能为 $-1,0,1$ 这三种。因此，我们不妨设 $c_i=b_i-a_i$，然后直接枚举所有 $c_i$ 可能的值的情况。由于 $n$ 很小，因此我们的 $\mathcal O(3^n)$ 做法可以毫无压力地跑过去。
## Code
```cpp
namespace Solution {
	int n, ans, a[17], b[17];
	
	iv dfs(int x) {
		if(x > n) {
			int fl = 0;
			F(int, i, 1, n) if(!((a[i] + b[i]) & 1)) {fl = 1; break;}
			ans += fl;
			return;
		}
		F(int, i, -1, 1) b[x] = i, dfs(x + 1);
	}
	
	iv Main() {
		read(n); F(int, i, 1, n) read(a[i]);
		dfs(1), println(ans);
		return;
	}
}
```

---

