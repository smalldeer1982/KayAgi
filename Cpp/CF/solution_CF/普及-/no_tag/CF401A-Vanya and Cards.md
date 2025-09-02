# Vanya and Cards

## 题目描述

Vanya loves playing. He even has a special set of cards to play with. Each card has a single integer. The number on the card can be positive, negative and can even be equal to zero. The only limit is, the number on each card doesn't exceed $ x $ in the absolute value.

Natasha doesn't like when Vanya spends a long time playing, so she hid all of his cards. Vanya became sad and started looking for the cards but he only found $ n $ of them. Vanya loves the balance, so he wants the sum of all numbers on found cards equal to zero. On the other hand, he got very tired of looking for cards. Help the boy and say what is the minimum number of cards does he need to find to make the sum equal to zero?

You can assume that initially Vanya had infinitely many cards with each integer number from $ -x $ to $ x $ .

## 说明/提示

In the first sample, Vanya needs to find a single card with number -2.

In the second sample, Vanya needs to find two cards with number 2. He can't find a single card with the required number as the numbers on the lost cards do not exceed 3 in their absolute value.

## 样例 #1

### 输入

```
3 2
-1 1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3
-2 -2
```

### 输出

```
2
```

# 题解

## 作者：Ninelife_Cat (赞：3)

设 $sum$ 为当前所有牌的点数之和。

显然答案就是 $\lceil \frac{\lvert sum \rvert}{x} \rceil$。

$Code$：

```cpp
#include<bits/stdc++.h>
#define int long long//个人习惯
using namespace std;
int n,x,a[1001],sum;
signed main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	sum=abs(sum);
	cout<<ceil(sum*1.0/x);
	return 0;
}

---

## 作者：Z_M__ (赞：1)

设$sum=n$张牌点数相加的值，现在所求的即为，至少要用几个绝对值小于x的数，使这几个数的和+sum=0，可以分为以下情况：

1. $|sum| \le x$时，只需要一个数。

2. $x\le |sum|$时，需要用$\lceil {\frac{|sum|}{x}}\rceil$个数即可。


情况1也可以表示为$\lceil {\frac{|sum|}{x}}\rceil$，所以答案即为$\lceil {\frac{|sum|}{x}}\rceil$.


$ACcode:$
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, x, a, sum;
int main ()
{
	cin >> n >> x;
	for (int i = 1; i <= n; i++)
	{
		cin >> a;
		sum += a;
	}
	cout << ceil (abs (sum * 1.0 / x * 1.0));
	return 0;
}

```

---

## 作者：开始新的记忆 (赞：0)

题目大意：给你n堆牌，每堆牌的数量给出，求把这所有牌平均分到x堆中最大牌数是多少

较水……

```cpp
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{   int n,x,a[1001],sum=0;
    cin>>n>>x;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        sum+=a[i];
	}
	if(abs(sum)%x==0)
	    cout<<abs(sum)/x;
	else 
	    cout<<abs(sum)/x+1;
	return 0;
}
```


---

