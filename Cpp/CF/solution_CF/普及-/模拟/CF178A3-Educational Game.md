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

## 作者：123456zmy (赞：4)

题意：  
给你一个数列，长度为 $n$，每次操作可以把一个数中的一个 $1$ 往后移动 $2^t$ 个位置（$t\geq0$）。问使前 $k$ 个位置都变为 $0$ 至少需要几次操作。对于每个 $1\leq k<n$ 输出一行答案（$n\le10^5$）~~这才是本题真正的数据范围~~。
___
贪心可得，一次尽可能往后移会对全局最优，所以每次询问后把数列和答案存下来，在此基础上进行下一次询问就可以达到单次 $O(\log n)$ 的复杂度。

代码：（$O(n\log n)$）
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long ans,n,a_,a[100001];//csp-s留下的心理阴影
int main()
{
	scanf("%llu",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%llu",&a_);
		a[i]+=a_;
		ans+=a[i];
		printf("%llu\n",ans);
		int i1=n-i;
		while(i1&i1-1)i1&=i1-1;//取最多能移多少
		a[i+i1]+=a[i];
	}
	return 0;
}
```

---

## 作者：大宝和小宝 (赞：3)

题目给定我们 $n$ 个背包，要将其中的东西往后面扔，越往后越好，但是扔的条件是只能扔 $i+2 ^k$ 的位置，$k$ 的大小可以随意变化。但是 $i + 2^k$ 要小于或等于 $n$，他要我们输出 $n-1$ 行。分别表示将前i个背包全都扔掉，即让前 $i$ 个数都为 $0$，该扔几次，记住，一次只能扔一，即例 $2$ 中前两个扔完要扔 $3$ 次。

因此防止TL，直接用位运算来找到在规定范围内他的最大   $2^k$，并且直接扔包
不多说，直接上代码：

---

```cpp
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

long long n,a,ans,A[100010];

int main () {
	cin >> n;
	for(int i = 1;i < n;i++) {
		cin >> a;
		A[i] += a;
		ans += A[i];//将现在的包和前面人过来的包一起扔到后面
		cout << ans << "\n";
		int k = n-i;
		while(k&k-1) //找到在范围内2^n的最大取值
			k &= k-1;
		A[i+k] += A[i];//将包扔给范围内他所能扔的最远位置
	}
	return 0;
}

```

---

## 作者：SXZM_1 (赞：0)

这题就是给你一串数一直把前面的数往后扔。

但是一定要是二的次方。

所以我们使用二进制思想，循环出最小可能值。

```cpp
int check(int k){return k?check(k&k-1)+1:0;}
```

二进制判断代码如上。

所以我们在加上判断：

```cpp

#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
ll n,a[2001],ans[2001][2001],ansn;
ll check(int k){return k?check(k&k-1)+1:0;}
signed main(){
	scanf("%llu",&n);
	for(int i=1;i<n;i++)for(int j=i+1;j<=n;j++)ans[i][j]=check(j-i);
	for(int i=1;i<n;i++){
		for(int j=n;j>1;j--){
			ans[i][j-1]=min(ans[i][j],ans[i][j-1]);
		}
	}
	for(int i=1;i<n;i++){
		ansn=0;
		cin>>a[i];
		for(int j=1;j<=i;j++)ansn+=ans[j][i+1]*a[j];
		cout<<ansn<<endl;
	}
	return 0;
}
```


---

## 作者：Smg18 (赞：0)

[三倍经验](https://www.luogu.com.cn/problem/CF178A1)。

怎么会有三道完全一样的题。

还是暴力思路，使用二进制思想，通过获得二进制一的个数，从 $i+1$ 循环到 $n$ 算出最小。

二进制一的个数用递归来算十分简单。

不会的见代码：

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

