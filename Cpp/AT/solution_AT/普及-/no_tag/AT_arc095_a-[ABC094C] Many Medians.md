# [ABC094C] Many Medians

## 题目描述

若l是一个奇数，那么l个数的数列的中位数就是数列中第 $\dfrac{l+1}{2}$ 大的数。

输入N个整数，$X$$_{1}$, $X$$_{2}$, ..., $X$$_{N}$ ，保证N为偶数。对于每一个i=1,2, ..., N，输出去掉xi之后数列的中位数$B$$_{i}$。

## 样例 #1

### 输入

```
4
2 4 4 3```

### 输出

```
4
3
3
4```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
2
1```

## 样例 #3

### 输入

```
6
5 5 4 4 3 3```

### 输出

```
4
4
4
4
4
4```

# 题解

## 作者：HyGeoIceFairy (赞：2)

蒟蒻又来写题解力！

分析：这题一开始看着像模拟，但是一看数据范围：

$X$$_{i}$ $\le$ $10$$^{9}$

每次去掉一个数再排序即便是快排也要TLE的。

怎么办呢？

我们想：

N个数，去掉一个，还剩N-1个数，根据题目，中位数即第N/2的数。

例子：（-n-表示去掉n）

```
-1-,2,3,4,5,6,7,8

2,3,4,⑤,6,7,8；

1,-2-,3,4,5,6,7,8

1,3,4,⑤,6,7,8.
```

我们发现，只要不超过第N/2大的数，去掉什么数对中位数并没有影响，都是第N/2+1大的数。

问题来了：如果我们把上例子中的⑤去掉呢？

```
1,2,3,4,-5-,6,7,8

1,2,3,4,6,7,8.
```

中位数变成了4。

超过第N/2大的数，中位数就会变成第N/2大的数。

所以代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[200001],b[200001];//a记录原始数组，b记录排序数组
int n,s,t;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);//排序
	s=b[n/2];
	t=b[n/2+1];//记录第N/2和第N/2+1大的数
	for(register int i=1;i<=n;++i)
	{
		if(a[i]<=s)
		{
			printf("%d\n",t);//若a[i]未超过第N/2大的数，则输出第N/2+1大的数
		}
		else
		{
			printf("%d\n",s);//否则输出第N/2大的数
		}
	}
	return 0;
}
```


------------
后记：这题翻译也是我交的，第一次交翻译有好多错，不知道怎么改，大家帮帮忙-_-||

---

## 作者：activeO (赞：1)

## 题目大意

给你一个数列，让你依次回答如果去掉 $ a_i (i \in [1,n]) $，数列中的中位数是什么。

## 思路

很简单，首先排序，令 $ mid=n>>1 $，玩一下样例，就可以发现其实答案来回就是 $ a_{mid},a_{mid+1} $，然后如果删去比 $ a_{mid} $ 大的，答案就是 $ a_{mid+1} $，就不会有影响，就是 $ a_{mid} $。

## 代码

```
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=2e5+10;
struct node{
	int id,num;
}a[maxn];
int ans[maxn];

bool cmp(node x,node y){
	return x.num>y.num;
}

int main(){
	
	int n;
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].num);
		a[i].id=i;
	}
	
	sort(a+1,a+n+1,cmp);
	
	int mid=n>>1;
	
	for(int i=1;i<=n;i++){
		if(i<=mid) ans[a[i].id]=a[mid+1].num;
		else ans[a[i].id]=a[mid].num;
	}
	
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	
	return 0;
}


```


---

