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

## 作者：chenyuchenghsefz (赞：3)

题目大意：
给你一个长度为 $n$ 的数列，每次操作可以把一个数中的一个 $1$ 往后移动 $2^t$ 位。问使前 $k$ 个位置都变为 $0$ 至少需要几次操作。对于每个 $k$ 输出一行答案。

------------

用最暴力的方法。定义一个函数返回二进制中 $1$ 的个数。从 $i+1$ 循环到 $n$，算出最小的。

我用了一个递归算法：

```n?b(n&n-1)+1:0```

复杂度 $\Theta(n^3 \log n )$ 
```cpp
#include <bits/stdc++.h>
using namespace std;
int b(int n)
{
	return n?b(n&(n-1))+1:0;
}
int main()
{
	int n,a[100100];
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		int s=0;
		cin>>a[i];
		for(int j=1;j<=i;j++)
		{
			int m=301;
			for(int k=i+1;k<=n;k++)
			m=min(m,b(k-j));
			s+=m*a[j];
		}
		cout<<s<<endl;
	}
    return 0;
}
```


---

## 作者：123456zmy (赞：1)

题意：  
给你一个数列，长度为 $n$，每次操作可以把一个数中的一个 $1$ 往后移动 $2^t$ 个位置（$t\geq0$）。问使前 $k$ 个位置都变为 $0$ 至少需要几次操作。对于每个 $1\leq k<n$ 输出一行答案（$n\le300$）~~这是 A1，更大的数据范围请看 A2 及 A3~~。
___
非常暴力的方法，枚举要移到哪去再暴力计算花费即可。
至于怎么计算，就只要求出需要移动的路径长度转二进制后统计 $1$ 的个数即可，因为每移动一步，就相当于把剩余距离的第 $t$ 位减一，所以 $1$ 的个数就是最少需要的次数，这里用的是 $x\ or\ x-1$ 一次去除一位来计算，所以带个 $log n$。

代码：（$O(n^3\log n)$）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[301],ansn[301],ans;
int bitn(int k){return k?bitn(k&k-1)+1:0;}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
	{
		ans=0;
		memset(ansn,0x3f,sizeof(ansn));
		scanf("%lld",&a[i]);
		for(int j=1;j<=i;j++)for(int k=i+1;k<=n;k++)ansn[j]=min(ansn[j],bitn(k-j));
		for(int j=1;j<=i;j++)ans+=a[j]*ansn[j];
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Smg18 (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/CF178A2)。

这是一很小型的暴力。

我们可以试试使用二进制思想，通过获得二进制一的个数，从 $i+1$ 循环到 $n$ 算出最小。

得到二进制一的个数可以使用如下代码：

```cpp
int check(int k){return k?check(k&k-1)+1:0;}
```

所以核心代码：

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

## 作者：_Clown_ (赞：0)

# 解析
这是一道简单题，题意不难理解。

我们考虑暴力，不用开 long long 啦！

最暴力的办法，枚举一下每个数要移到哪里去。

用二进制的方法计算代价，不难算出最小答案。

那么具体怎么算出代价呢？大家可以想一想。

这里提供一种递归算法：

```cpp
X?Cut(X&(X-1))+1:0;
```

优点是码量少。

因为数据小，所以我们打了一个 $\mathcal{O(n^3logn)}$，AC 了。
# 代码
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N;
int Dp[1001];
int Array[1001];
inline int Cut(int X)
{
	return X?Cut(X&(X-1))+1:0;
}
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("SampleIN.in","r",stdin);
	#else
	#endif
	register int i,j,k;
	cin>>N;
	for(i=1;i<=N;i++)cin>>Array[i];
	for(i=1;i<N;i++)
	{
		register int Ans;
		Ans=0;
		for(j=1;j<=N;j++)Dp[j]=2147483647;
		for(j=1;j<=i;j++)for(k=i+1;k<=N;k++)Dp[j]=min(Dp[j],Cut(k-j));
		for(j=1;j<=i;j++)Ans+=Dp[j]*Array[j];
		cout<<Ans<<endl;
	}
	return 0;
}
```

---

## 作者：Andysun06 (赞：0)

## CF178A1 题解
### 题目意思：
给你一个长度为 $n$ 的数列，如果前 $k$ 个位置并不是都为 $0$，你就要把一个数中的一个 1 往后移动 $2^t$ 个位置，直到前 $k$ 个位置都为 $0$，问一共需要几次操作，每个 $1 \le k \le (n-1)$ 输出一行答案

### 题目难度：
大概在 `入门~普及-`，思维难度一般

### 做法分析
很容易发现，这题数据较小，时限较大，可以使用暴力算法，所以一个个步数枚举即可，但是如果你想代码跑的更快，可以加上预处理。

### 核心代码：
```cpp
for(j=1;j<=i;++j)
    for(ii=i+1;ii<=n;++ii)
        f[j]=min(f[j],qwq(ii-j));//qwq为函数，求出ii-j转二进制后 1 的个数
for(j=1;j<=i;++j)
    ans+=a[j]*f[j];
```

---

