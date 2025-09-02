# The Art of Dealing with ATM

## 题目描述

ATMs of a well-known bank of a small country are arranged so that they can not give any amount of money requested by the user. Due to the limited size of the bill dispenser (the device that is directly giving money from an ATM) and some peculiarities of the ATM structure, you can get at most $ k $ bills from it, and the bills may be of at most two distinct denominations.

For example, if a country uses bills with denominations $ 10 $ , $ 50 $ , $ 100 $ , $ 500 $ , $ 1000 $ and $ 5000 $ burles, then at $ k=20 $ such ATM can give sums $ 100000 $ burles and $ 96000 $ burles, but it cannot give sums $ 99000 $ and $ 101000 $ burles.

Let's suppose that the country uses bills of $ n $ distinct denominations, and the ATM that you are using has an unlimited number of bills of each type. You know that during the day you will need to withdraw a certain amount of cash $ q $ times. You know that when the ATM has multiple ways to give money, it chooses the one which requires the minimum number of bills, or displays an error message if it cannot be done. Determine the result of each of the $ q $ of requests for cash withdrawal.

## 样例 #1

### 输入

```
6 20
10 50 100 500 1000 5000
8
4200
100000
95000
96000
99000
10100
2015
9950
```

### 输出

```
6
20
19
20
-1
3
-1
-1
```

## 样例 #2

### 输入

```
5 2
1 2 3 5 8
8
1
3
5
7
9
11
13
15
```

### 输出

```
1
1
1
2
2
2
2
-1
```

# 题解

## 作者：流绪 (赞：1)

主要思路就是算出每一种钱各种张数时能构成的钱数,然后从小到大枚举张数来查找,刚好就直接输出,超了就退出,找下一个张数,因为已经对钱数从小到大排了,往后肯定超更多,不够就再从小枚举张数,查找能不能够补上,因为此时要找的是个定值,我们直接二分查找来降低复杂度.

PS:一开始用数组写死活整不出来,搜了一下发现用vector写很简单...要好好学STL了...
```cpp
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
using namespace std;
vector<int> v[25];	//第一维表示第 i 张钱 
int main()			//第二维表示 i 张钱的面值和的可能值 
{
	int n,m;
	cin >> n >> m;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin >> x;
		for(int j=1;j<=m;j++)
			v[j].push_back(x*j);//单种面值能构成的钱 
	}	
	for(int i=1;i<=m;i++)
		sort(v[i].begin(),v[i].end());//从小到大排 
	int q;
	cin >> q;
	while(q--)
	{
		int x;
		cin >> x;
		int ans = inf;
		for(int i=1;i<=m;i++)//从小到大枚举用的张数 
			for(int j=0;j<v[i].size();j++)
			{				//从小到大枚举可能构成的钱数 
				int y=x-v[i][j];//看现在的钱数和目标钱数的差 
				if(y<=0)
				{
					if(!y)
						ans = min(ans,i);//刚好构成,更新答案 
					break;//太多了,退出 
				}
				for(int k=1;k<=m-i;k++)	//不够的情况枚举取 m-i 张牌 
				{						//二分找到第一个大于等于这个差值的数	 
					int p=lower_bound(v[k].begin(),v[k].end(),y)-v[k].begin(); 
				//	cout << p << " " << y << endl; 
					if(p<v[k].size()&&v[k][p] == y)//刚好补差值,更新答案 
						ans = min(ans ,i+k);
				}
			}
		if(ans == inf)
			cout << -1;
		else
			cout << ans;
		cout << endl;
	}
} 
```


---

