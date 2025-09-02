# Points on the line

## 题目描述

We've got no test cases. A big olympiad is coming up. But the problemsetters' number one priority should be adding another problem to the round.

The diameter of a multiset of points on the line is the largest distance between two points from this set. For example, the diameter of the multiset $ {1,3,2,1} $ is 2.

Diameter of multiset consisting of one point is 0.

You are given $ n $ points on the line. What is the minimum number of points you have to remove, so that the diameter of the multiset of the remaining points will not exceed $ d $ ?

## 说明/提示

In the first test case the optimal strategy is to remove the point with coordinate $ 4 $ . The remaining points will have coordinates $ 1 $ and $ 2 $ , so the diameter will be equal to $ 2-1=1 $ .

In the second test case the diameter is equal to $ 0 $ , so its is unnecessary to remove any points.

In the third test case the optimal strategy is to remove points with coordinates $ 1 $ , $ 9 $ and $ 10 $ . The remaining points will have coordinates $ 3 $ , $ 4 $ and $ 6 $ , so the diameter will be equal to $ 6-3=3 $ .

## 样例 #1

### 输入

```
3 1
2 1 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 0
7 7 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 3
1 3 4 6 9 10
```

### 输出

```
3
```

# 题解

## 作者：Tune_ (赞：1)

这其实是一道暴力小题题~

根据题目要求，1~100皆可能是最小值，暴力枚举一下，比i小和比i+d大的都删掉，再看哪个最小值删的数最少。

以下是代码：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,d,a[101];
	cin>>n>>d;
	int ans=1000;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=0;i<=100;i++)//枚举
	{
		int s=0;
		for(int j=1;j<=n;j++)
		{
			if(a[j]<i||a[j]>i+d)s++;//删数咯~
		}
		ans=min(s,ans);//求最小
	}
	cout<<ans;//大功告成!
	return 0;
}
```
~~有时候暴力真的能出奇迹呢~~

---

## 作者：Prurite (赞：1)

### ~~这题数据真的很水~~

## 思路
思路：枚举最小值，然后枚举每一个数检查是否在允许的范围内，如果不在就del++。最后找出所有最小值中最小的del输出即可。

## 代码
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=100+1, MINX=1, MAXX=100;
int a[MAXN];
inline int min( int a, int b ) { return a<b?a:b; }

int main( )
{
	int n, d;
	while ( scanf( "%d %d", &n, &d )!=-1 )
	{
		for ( int i=1; i<=n; i++ )
			scanf( "%d", &a[i] );
		sort( a+1, a+n+1 );
		int ans=n;
		for ( int i=0; i<=100; i++ ) //枚举最小值 
		{
			int del=0;
			for ( int j=1; j<=n; j++ )
				if ( a[j]<i || a[j]>i+d )
					del++;
			ans=min( ans, del );
		}
		printf( "%d\n", ans );
	}
	return 0;
}
```
[提交记录 用时: 346ms / 内存: 3252KB](https://www.luogu.org/record/show?rid=6632309)

---

