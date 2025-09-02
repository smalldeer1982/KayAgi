# Slightly Decreasing Permutations

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

The decreasing coefficient of permutation $ p_{1},p_{2},...,p_{n} $ is the number of such $ i\ (1<=i&lt;n) $ , that $ p_{i}&gt;p_{i+1} $ .

You have numbers $ n $ and $ k $ . Your task is to print the permutation of length $ n $ with decreasing coefficient $ k $ .

## 样例 #1

### 输入

```
5 2
```

### 输出

```
1 5 2 4 3
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
1 2 3
```

## 样例 #3

### 输入

```
3 2
```

### 输出

```
3 2 1
```

# 题解

## 作者：yanxingyu0910 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF285A)

**题意描述**

* 只要让前一个比后一个大的个数等于 $K$ 即可

* 那就很简单了，逆序输出的个数减一就等于 $K$ 的个数咯


**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL read(){//快读 
	register LL x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
int main(){
	LL n,k,i;
	n=read();
	k=read();
	for(i=k+2;i<=n;i++){//正序输出 
		printf("%lld ",i);
	}
	for(i=k+1;i>=1;i--){//逆序输出 
		printf("%lld ",i);
	}
	return 0;//好习惯 
}
```
感谢观看~


---

## 作者：hanyuchen2019 (赞：1)

一道简单构造题。

### part1 大致题意

构造一个长度为 $n$ 的序列，使得序列中有 $k$ 对相邻的数 $(a,b)$ 满足 $a>b$（即逆序对）。

### part2 思路

我们可以先输出 $n-k$ 个递增的数，再输出 $k$ 个递减的数。

比如：
```
input:
5 2
output:
3 4 5 2 1
```

就形成了 $2$ 个逆序对，分别是 $(5,2)$ 和 $(2,1)$。

### part3 Code

要注意一下循环的边界。

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=k+1;i<=n;i++)//递增
		cout<<i<<" ";
	for(int i=k;i>=1;i--)//递减
		cout<<i<<" ";
	return 0;
}
```

也许你会有这样的疑问：

```cpp
for(int i=1;i<=n-k;i++)//递增的部分这样写不好吗？
		cout<<i<<" ";
```

Sorry，这样是错误的。
```
Hack
input:
4 2
wrong_output:
1 2 2 1
```

只有一个逆序对。

码字不易，点个赞再走吧~

---

## 作者：s_c_lmlm_L (赞：0)

题意不难理解，即构造一个长度为 $n$ 的逆序对。

满足： $k$ 对子序列一定存在逆序对 $(x,y),x>y$ 。

我们可以：从 $k+1$ 开始倒序输出到 $1$，再从 $k+2$ 正序输出到 $n$ ，也就是 $n-k$ 个递增数， $k$ 个递减数。

# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k; 
	cin>>n>>k;
	for(int i=k+1;i>=1;--i)
    	    cout<<i; 
	for(int i=k+2;i<=n;++i)
            cout<<i; 
} 
// 抄题解是不好的行为
```



---

## 作者：qscisQJing (赞：0)

# CF285A题解

我们可以先考虑 $ p $ 不是一个排列的时候该怎么办，

很明显，只需要找 $ k+1 $ 个连续下降的数就可以了 。而后面的 $ n-k+1 $ 个数只要不与前面选的数重复， $ p $ 就可以满足题目条件了。

再考虑当 $ p $ 必须是个排列怎么办。因为我们之前构造的数两两不重复，所以离散化一下就可以了。

时间复杂度 $ O(n \log n) $ 可以通过本题

 

---

## 作者：qfpjm (赞：0)

# 题解

可以考虑吧构造 $k-1$ 个逆序对，剩下全为顺序对，就可以构造出题目要求的排列。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = n ; i > n - k ; i --)
	{
		cout << i << " ";
	}
	for (int i = 1 ; i <= n - k ; i ++)
	{
		cout << i << " ";
	}
}
```


---

## 作者：Misaka_Mik0t0 (赞：0)

此题中只用解出一种解法，我们可以让前 $k+1$ 个数下降，之后全部上升。不妨设前 $k+1$ 个数为 $k+1,k,\cdots,1$；之后的数为 $k+2,k+3,\cdots,n$。$\\$
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k; 
int main(){
	scanf("%d%d",&n,&k);
	for(int i=k+1;i>=1;--i)printf("%d ",i);
	for(int i=k+2;i<=n;++i)printf("%d ",i);
	return 0;
} 
```

---

## 作者：Yhlo_Yzj (赞：0)

### CF285A题解

**题意简述**: 给定你两个整数 $n$ 和 $k$($n≤1e5$ , $0≤k<n$，要得到一个长度为 $n$ ( $p1$ , $p2$ , $p3$ ...... $pn$ )，满足有 $k$ 个( $pi$ $>$ $pi+1$ ）。

**注**：有多种情况的话只用输出一种即可

**思路——————循环**

1. 建一个 $a$ 数组， 存储 1 到 $n$。

1. 在数组里交换大数和小数（双指针），使其要求条件的次数等于 $k$

1. 特判 $k$ 是 0 的情况

1. 输出即可

**接下来————上代码**

### $code$：

```cpp
#include<bits/stdc++.h>//万能头节省大小
using namespace std;
const int MAXN=1e5+5;//多用这个，方便
int n,k,a[MAXN];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		a[i]=i;//赋值
	}
	if(k==0){//特判k是0的情况
		for(int i=1;i<=n;i++){
			cout<<i<<" ";//直接输出
		}
		return 0;
	}
	for(int i=1,j=k+1;i<j;i++,j--){//双指针从1和k+1开始
		swap(a[i],a[j]);//交换大数与小数
	}
	for(int i=1;i<=n;i++){//输出即可
		cout<<a[i]<<" ";
	}
	return 0;
}

```


---

