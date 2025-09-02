# Educational Game

## 题目描述

The Smart Beaver from ABBYY began to develop a new educational game for children. The rules of the game are fairly simple and are described below.

The playing field is a sequence of $ n $ non-negative integers $ a_{i} $ numbered from $ 1 $ to $ n $ . The goal of the game is to make numbers $ a_{1},a_{2},...,a_{k} $ (i.e. some prefix of the sequence) equal to zero for some fixed $ k $ $ (k<n) $ , and this should be done in the smallest possible number of moves.

One move is choosing an integer $ i $ ( $ 1<=i<=n $ ) such that $ a_{i}>0 $ and an integer $ t $ $ (t>=0) $ such that $ i+2^{t}<=n $ . After the values of $ i $ and $ t $ have been selected, the value of $ a_{i} $ is decreased by $ 1 $ , and the value of $ a_{i+2^{t}} $ is increased by $ 1 $ . For example, let $ n=4 $ and $ a=(1,0,1,2) $ , then it is possible to make move $ i=3 $ , $ t=0 $ and get $ a=(1,0,0,3) $ or to make move $ i=1 $ , $ t=1 $ and get $ a=(0,0,2,2) $ (the only possible other move is $ i=1 $ , $ t=0 $ ).

You are given $ n $ and the initial sequence $ a_{i} $ . The task is to calculate the minimum number of moves needed to make the first $ k $ elements of the original sequence equal to zero for each possible $ k $ $ (1<=k<n) $ .

## 样例 #1

### 输入

```
4
1 0 1 2
```

### 输出

```
1
1
3
```

## 样例 #2

### 输入

```
8
1 2 3 4 5 6 7 8
```

### 输出

```
1
3
6
10
16
24
40
```

# 题解

## 作者：123456zmy (赞：2)

题意：  
给你一个数列，长度为 $n$，每次操作可以把一个数中的一个 $1$ 往后移动 $2^t$ 个位置（$t\geq0$）。问使前 $k$ 个位置都变为 $0$ 至少需要几次操作。对于每个 $1\leq k<n$ 输出一行答案（$n\le2000$）~~这是 A2，更大的数据范围请看 A3~~。
___
由于移到 $k$ 后面对答案都是一样的，所以可以在 $n^2logn$ 的时间内预处理出可以 $O(1)$ 查询的代价数组（~~写数据结构维护区间最小值我也没意见~~）。

代码：（$O(n^2\log n)$）
```cpp

#include<bits/stdc++.h>
#define int unsigned long long//csp-s留下的心理阴影
using namespace std;
int n,a[2001],ans[2001][2001],ansn;
int bitn(int k){return k?bitn(k&k-1)+1:0;}
signed main()
{
	scanf("%llu",&n);
	for(int i=1;i<n;i++)for(int j=i+1;j<=n;j++)ans[i][j]=bitn(j-i);
	for(int i=1;i<n;i++)for(int j=n;j>1;j--)ans[i][j-1]=min(ans[i][j],ans[i][j-1]);
	for(int i=1;i<n;i++)
	{
		ansn=0;
		scanf("%llu",&a[i]);
		for(int j=1;j<=i;j++)ansn+=ans[j][i+1]*a[j];
		printf("%llu\n",ansn);
	}
	return 0;
}
```

---

## 作者：Smg18 (赞：0)

这题就是比[这题](https://www.luogu.com.cn/problem/CF178A1)数据大了点。

所以我们可以使用那题的暴力思路，使用二进制思想，通过获得二进制一的个数，从 $i+1$ 循环到 $n$ 算出最小。

时间完全够！

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e5+10,NN=1e4+10;
ll n,m,k,len,ans,T;
ll minn=INT_MAX,maxn=0;
char c[N];
ll arr[N];
int check(int k){return k?check(k&k-1)+1:0;}
int main(){
	cin>>n;
	for(int i = 1;i<n;i++){
		ans=0;
		cin>>arr[i];
		for(int j = 1;j<=i;j++){
			int m = INT_MAX;
			for(int k = i+1;k<=n;k++){
				m=min(m,check(k-j));
			}
			ans+=m*arr[j];
		}
		cout<<ans<<endl;
	}

	return 0;
}
```


---

