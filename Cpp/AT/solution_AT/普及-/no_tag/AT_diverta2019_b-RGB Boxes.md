# RGB Boxes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/diverta2019/tasks/diverta2019_b

すぬけ君はボールが入った箱を売っている店に行きました。 売っている箱は以下の $ 3 $ 種類です。

- $ R $ 個のボールが入った赤色の箱
- $ G $ 個のボールが入った緑色の箱
- $ B $ 個のボールが入った青色の箱

すぬけ君は赤色の箱を $ r $ 個、緑色の箱を $ g $ 個、青色の箱を $ b $ 個買うことで合計でちょうど $ N $ 個のボールが手に入るようにしたいです。 これを達成する非負整数の組 $ (r,g,b) $ はいくつありますか？

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ R,G,B,N\ \leq\ 3000 $

### Sample Explanation 1

条件を満たすのは以下の $ 4 $ 通りです。 - $ (4,0,0) $ - $ (2,1,0) $ - $ (1,0,1) $ - $ (0,2,0) $

## 样例 #1

### 输入

```
1 2 3 4```

### 输出

```
4```

## 样例 #2

### 输入

```
13 1 4 3000```

### 输出

```
87058```

# 题解

## 作者：Gokix (赞：1)

[AT5038](https://www.luogu.com.cn/problem/AT5038)

$N \le 3000$ 告诉我们不能暴力直接 $O(n^3)$ 枚举 $r,g,b$，但是我们可以先枚举 $r,g$，再求出 $b$。

考虑枚举 $r,g$ 时我们已经有 $R \times r + G \times g$ 个球，那么剩下的 $N-R \times r + G \times g$ 个球一定是 $B$ 的倍数（不然你也不能把一个盒子拆开）。

从这个思路枚举 $r,g$ 是 $O(n^2)$ 的，$O(1)$ 求出 $b$。总时间复杂度是 $O(n^2)$，可以接受。

于是就有下面这个程序：$( \text{程序中} r,g,b,i,j,u/b \text{分别与题中}R,G,B,r,g,b \text{对应})$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long r,g,b,n,ans;
int main()
{
	long long i,j,u,v;
	cin>>r>>g>>b>>n;
	for(i=0;i<=n;i++)//枚举r
	{
		for(j=0;j<=n;j++)//枚举g
		{
			u=n-(i*r)-(j*g);//剩下的球
			if(u%b==0)
			{
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	return(0);
} 
```

但是这个程序根本连样例1都过不了。

当我们调试一下，发现剩下的球$(u)$可能是负的，导致$u/b$为负，所以答案会多出一部分。

多判断一下，让 $u/b$ 是非负的时候才负合答案就好了：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long r,g,b,n,ans;
int main()
{
	long long i,j,u,v;
	cin>>r>>g>>b>>n;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=n;j++)
		{
			u=n-(i*r)-(j*g);
			if(u%b==0 && u/b>=0)//这里有变化
			{
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	return(0);
} 
```

---

## 作者：caoxuran (赞：0)

### 这道题暴力就能过了。
首先，吐槽一下，为什么at喜欢用 RGB ?其他颜色不行吗？？？

吐槽结束，言归正传。首先看看一般的 $ O(n^3) $做法：暴力枚举三种球的盒数，代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int R,G,B,n;
	cin>>R>>G>>B>>n;
	
	int sum=0;		//记得清零 
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			for(int k=0;k<=n;k++)		//三重循环 
				if(i*R+j*G+k*B==n)		//判断总球数是否满足条件
					sum++;
	
	cout<<sum<<endl;
	return 0;
}
```
但是，$ n<=3000 $ 限制了这种做法，我们可以用 $ O(n^2) $ 做法：枚举其中两种球的盒数，用 $ n $ 减去这两种球数，求出第三种球数，再判断球数是否能整除每盒球数。这里要注意一点，第三种球数不能为负。

AC代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int R,G,B,n;
	cin>>R>>G>>B>>n;
	
	int sum=0;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)		//双重循环 
		{
			int k=n-i*R-j*G; 		//求出k的值 
			if(k%B==0 && k>=0)		//判断k是否满足条件 
				sum++;
		}
	
	cout<<sum<<endl;
	return 0;
}
```
$ The $ $ end $

---

