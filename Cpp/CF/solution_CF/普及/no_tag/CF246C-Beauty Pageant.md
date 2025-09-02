# Beauty Pageant

## 题目描述

General Payne has a battalion of $ n $ soldiers. The soldiers' beauty contest is coming up, it will last for $ k $ days. Payne decided that his battalion will participate in the pageant. Now he has choose the participants.

All soldiers in the battalion have different beauty that is represented by a positive integer. The value $ a_{i} $ represents the beauty of the $ i $ -th soldier.

On each of $ k $ days Generals has to send a detachment of soldiers to the pageant. The beauty of the detachment is the sum of the beauties of the soldiers, who are part of this detachment. Payne wants to surprise the jury of the beauty pageant, so each of $ k $ days the beauty of the sent detachment should be unique. In other words, all $ k $ beauties of the sent detachments must be distinct numbers.

Help Payne choose $ k $ detachments of different beauties for the pageant. Please note that Payne cannot just forget to send soldiers on one day, that is, the detachment of soldiers he sends to the pageant should never be empty.

## 样例 #1

### 输入

```
3 3
1 2 3
```

### 输出

```
1 1
1 2
2 3 2
```

## 样例 #2

### 输入

```
2 1
7 12
```

### 输出

```
1 12 
```

# 题解

## 作者：Bai_R_X (赞：1)

## 思路
重点：**美丽值各不相同**

所以，如果我们按美丽值升序排序，当派 $x$ 人时，我们有以下方案：
- $a_1,a_2,\dots,a_{x-1},a_x$
- $a_1,a_2,\dots,a_{x-1},a_{x+1}$
- $a_1,a_2,\dots,a_{x-1},a_{x+2}$
- $\dots$
- $a_1,a_2,\dots,a_{x-1},a_n$

因为美丽值各不相同，所以这些值的和互不相同。

如果 $x$ 不同，因为美丽值各不相同，所以和仍然不相同。

于是，再检查数据范围，因为派 $x$ 个人有 $n-x+1$ 种方案，所以如果按上述方案，总方案数为 $\sum_{i=1}^nn-i+1=\frac{n(n+1)}{2}$。而 $k$ 的最大值正好是这个值，所以可以按这个方案选择。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[55],i,j,kk;
int main()
{
	cin>>n>>k;
	for(i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n-i+1;j++)
		{
			cout<<i<<" ";
			for(kk=n;kk>n-i+1;kk--)cout<<a[kk]<<" ";
			cout<<a[j]<<endl;
			if(!(--k))return 0;
		}
	}
	return 0;
}
```

---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门]()

## 思路
有 $n$ 名士兵，选美比赛持续 $k$ 天。第 $i$ 名士兵的美丽程度为 $a_i$。小队的美丽程度是其成员美丽程度的总和，且每天的小队美丽程度应不同。你的任务是选择 $k$ 支不同美丽程度的小队参赛。
我们需要先将所有士兵的美丽程度进行单调排序，当我们派出 $x$ 人的时候会有 $n-x+1$ 种可能的小队，因为 $x$ 有 $n$ 种可能所以总共就有 $\frac{n(n+1)}{2}$ 种可能，最后只要美丽值不相同就可以选这一种方案。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100; 
int n,k,a[maxn],i,j,x;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);//单调排序 
	for(x=1;x<=n;x++)
	{
		for(j=1;j<=n-x+1;j++)
		{
			cout<<x<<" ";//输出个数 
			for(i=n;i>n-x+1;i--)
			{
				cout<<a[i]<<" ";//输出这个小队的每一个美丽值 
			}
			cout<<a[j]<<endl;
			if(!(--k))
			{
				return 0;//满足个数完结撒花 
			}
		}
	}
	return 0;//完结撒花 
}
```

---

