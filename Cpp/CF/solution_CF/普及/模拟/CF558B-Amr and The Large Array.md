# Amr and The Large Array

## 题目描述

Amr has got a large array of size $ n $ . Amr doesn't like large arrays so he intends to make it smaller.

Amr doesn't care about anything in the array except the beauty of it. The beauty of the array is defined to be the maximum number of times that some number occurs in this array. He wants to choose the smallest subsegment of this array such that the beauty of it will be the same as the original array.

Help Amr by choosing the smallest subsegment possible.

## 说明/提示

A subsegment $ B $ of an array $ A $ from $ l $ to $ r $ is an array of size $ r-l+1 $ where $ B_{i}=A_{l+i-1} $ for all $ 1<=i<=r-l+1 $

## 样例 #1

### 输入

```
5
1 1 2 2 1
```

### 输出

```
1 5```

## 样例 #2

### 输入

```
5
1 2 2 3 1
```

### 输出

```
2 3```

## 样例 #3

### 输入

```
6
1 2 2 1 1 2
```

### 输出

```
1 5```

# 题解

## 作者：KID2695 (赞：0)

第一步先统计每个数字出现的个数以及第一次与最后一次出现的位置，并计算原数组中出现次数最多的数字出现了几次。

```cpp
FOR(i,1,n){
  a[i]=iread();
  if(!l[a[i]]) l[a[i]]=i;
  r[a[i]]=i;
  ++t[a[i]];
  dmax=max(t[a[i]],dmax);
}
```
接下来对于所有满足出现次数等于原数组中出现次数最多的数字出现的次数的数字，看看将这个数字全部选中的区间（利用第一次与最后一次出现的位置）是否更短，更新答案。
```cpp
int L=1,R=n;
FOR(i,1,n){
  if(t[a[i]]==dmax&&(R-L+1)>(r[a[i]]-l[a[i]]+1)){
    L=l[a[i]];
    R=r[a[i]];
  }
}
printf("%d %d",L,R);
```

---

## 作者：_xiaxii (赞：0)

# [Problem's Link](https://www.luogu.com.cn/problem/CF558B)

~~还没有题解，赶紧水一篇。~~

## 题意

原题意似乎翻译得不是很清楚。这里给出我的翻译：

- 给定一个长度为 $n$ 的数组。
- 求出一个字串，使得字串中**某个数字出现的次数最大值于原数组**和**此数字与原数组的相同**，并最小化最小值。

## 做法

本题不难看出是简单的模拟。首先我们把原数组数字出现的最大值记录下来，并且记录每个数字出现的左右端点及每个数字出现的次数。之后遍历每个可能出现的数字，如果此数字出现的次数等于最大出现数字，记下左右端点于长度，最小化这个长度之后得到的左右端点就是答案了。

## 注意

$l$ 数组需要初始化无穷大。因为下标都是大于 $1$ 的，所以 $r$ 数组不需要初始化。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, cnt, ansl, ansr = 1061109567;
int a[100005], book[1000005], maxint, l[1000005], r[1000005];

int main(){
	cin >> n;
	memset(l, 0x3f, sizeof(l));//初始化l数组为最大值
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		book[a[i]]++;
		l[a[i]] = min(l[a[i]], i);//记录每种数的左右端点
		r[a[i]] = max(r[a[i]], i);
		if(book[a[i]] >= maxint){
			maxint = book[a[i]];//记下最大的次数
		}
	}
	for(int i = 1; i <= 1000000; i++){
		if(maxint == book[i]){//符合的字串
			if(r[i] - l[i] < ansr - ansl){//发现更短的符合的字串
				ansl = l[i];
				ansr = r[i];
			}
		}
	}
	cout << ansl << " " << ansr;
}
```

实测[满分](https://www.luogu.com.cn/record/127031300)。

---

