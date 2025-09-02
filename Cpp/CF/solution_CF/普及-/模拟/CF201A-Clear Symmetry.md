# Clear Symmetry

## 题目描述

Consider some square matrix $ A $ with side $ n $ consisting of zeros and ones. There are $ n $ rows numbered from $ 1 $ to $ n $ from top to bottom and $ n $ columns numbered from $ 1 $ to $ n $ from left to right in this matrix. We'll denote the element of the matrix which is located at the intersection of the $ i $ -row and the $ j $ -th column as $ A_{i,j} $ .

Let's call matrix $ A $ clear if no two cells containing ones have a common side.

Let's call matrix $ A $ symmetrical if it matches the matrices formed from it by a horizontal and/or a vertical reflection. Formally, for each pair $ (i,j) $ $ (1<=i,j<=n) $ both of the following conditions must be met: $ A_{i,j}=A_{n-i+1,j} $ and $ A_{i,j}=A_{i,n-j+1} $ .

Let's define the sharpness of matrix $ A $ as the number of ones in it.

Given integer $ x $ , your task is to find the smallest positive integer $ n $ such that there exists a clear symmetrical matrix $ A $ with side $ n $ and sharpness $ x $ .

## 说明/提示

The figure below shows the matrices that correspond to the samples:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF201A/4a353f15397909088e2fcb0cff23c93ecb30c822.png)

## 样例 #1

### 输入

```
4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
9
```

### 输出

```
5
```

# 题解

## 作者：流绪 (赞：4)

楼上的老哥没发代码，我来补一发！

做法是一样的，我来讲讲怎么实现。

首先我们知道了一个 (2*i+1)*(2*i+1) 的对称矩阵，

最多容纳的 1 的数量为 ((2*i+1)*(2*i+1)+1)/2。

那我们设 i，j=i+1，那么以 i，j 算出来的一个范围就是就是如果 x 在这个范围内，那么就可以用一个 j 大小的矩阵来合法的放 x 个 1。然后 x<100，那么我们直接预处理出这个范围放在数组里，然后查询是，从头开始，找到第一个 >=x 的元素，取出其下标乘 2 再加上 1 就是答案啦！

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
int a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	int x;
	cin >> x;
	if(x==3)
		cout << 5;
	else
	{
		int p=0;
		for(int i=0;p<200;i++)
		{ 
			p = ((2*i+1)*(2*i+1)+1)/2;
			a[i]  = p; 
		} 
		for(int i=0;;i++)
			if(a[i]>=x)
			{
				p=i;
				break;
			}
		cout << 2*p+1;
	}
	return 0; 
}  
```


---

## 作者：引领天下 (赞：3)

这个题目其实很简单

一个(2\*i+1)\*(2\*i+1)的对称矩阵最多容纳的1的数量=((2\*i+1)\*(2\*i+1)+1)/2

答案就是2\*i+1

所以暴力即可。

特别的，当i=3时，由于边长为5的矩阵比较神奇，可以有多种排法，所以特判一下i=3时输出5。

代码就不贴了

---

