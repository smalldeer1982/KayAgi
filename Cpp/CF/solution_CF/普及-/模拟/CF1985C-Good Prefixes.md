# Good Prefixes

## 题目描述

Alex thinks some array is good if there exists some element that can be represented as the sum of all other elements (the sum of all other elements is $ 0 $ if there are no other elements). For example, the array $ [1,6,3,2] $ is good since $ 1+3+2=6 $ . Furthermore, the array $ [0] $ is also good. However, the arrays $ [1,2,3,4] $ and $ [1] $ are not good.

Alex has an array $ a_1,a_2,\ldots,a_n $ . Help him count the number of good non-empty prefixes of the array $ a $ . In other words, count the number of integers $ i $ ( $ 1 \le i \le n $ ) such that the length $ i $ prefix (i.e. $ a_1,a_2,\ldots,a_i $ ) is good.

## 说明/提示

In the fourth test case, the array has five prefixes:

- prefix $ [0] $ is a good array, as mentioned in the statement;
- prefix $ [0, 1] $ is not a good array, since $ 0 \ne 1 $ ;
- prefix $ [0, 1, 2] $ is not a good array, since $ 0 \ne 1 + 2 $ , $ 1 \ne 0 + 2 $ and $ 2 \ne 0 + 1 $ ;
- prefix $ [0, 1, 2, 1] $ is a good array, since $ 2 = 0 + 1 + 1 $ ;
- prefix $ [0, 1, 2, 1, 4] $ is a good array, since $ 4 = 0 + 1 + 2 + 1 $ .

As you can see, three of them are good, so the answer is $ 3 $ .

## 样例 #1

### 输入

```
7
1
0
1
1
4
1 1 2 0
5
0 1 2 1 4
7
1 1 0 3 5 2 12
7
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 294967296
10
0 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 589934592```

### 输出

```
1
0
3
3
4
1
2```

# 题解

## 作者：ZnHF (赞：3)

# 题意简述

称一个数组是“好数组”，当且仅当这个数组里存在某个元素可以表示为其他所有元素之和。

给定一个长度为 $n$ 的 $a$ 数组，求这个数组的所有非空前缀中有多少个是“好”的。

# 题目分析

观察到每个 $a_{i}$ 都是非负数，所以如果一个 $a$ 数组的非空前缀是“好”的，那么这个非空前缀中的最大值一定是其他所有元素之和。

将数组 $a$ 从左到右遍历一遍，记 $x$ 为已经遍历过的元素中，值最大的元素的值，$y$ 为**除 $x$ 外**，已经遍历过的元素的值的总和。当遍历到一个数 $a_{i}$ 时，若 $a_{i}>x$，则将 $y$ 加上 $x$，并且将 $x$ 赋值为 $a_{i}$。接着比较 $x$ 与 $y$ 的值是否相等，如果相等，则答案加 $1$。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){register int t1=0,t2=0;register char x=getchar();while(x<'0' || x>'9'){if(x=='-') t1|=1;x=getchar();}while(x>='0' && x<='9'){t2=(t2<<1)+(t2<<3)+(x^48);x=getchar();}return t1?-t2:t2;}
inline void write(int x){if(x<0){putchar('-');x=-x;}int sta[100],top=0;do{sta[top++]=x%10;x/=10;}while(x);while(top) putchar(sta[--top]+48);}
int T,n,a[200005],sum,maxx,ans;
signed main(){
	T=read();
	while(T--){
		ans=0;
		sum=0;
		maxx=0;
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		for(int i=1;i<=n;i++){
			if(a[i]>maxx){
				sum+=maxx;
				maxx=a[i];
			}
			else sum+=a[i];
			if(sum==maxx) ans++;
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：BrotherCall (赞：3)

## 题意

一个序列中若存在一个数等于序列中其他所有数的和，则该序列为好序列。

问有多少个 $k(1\leq k \leq n)$，满足 $(a_1,a_2,\cdots,a_k)$ 是好序列。

## 思路

如果存在一个数等于其他数的和，那么这个数必然是序列中最大的。

设最大的数为 $s_0$，序列和为 $sum$，则对于每个 $k$ 只需判断是否满足 $s_0 = sum - s_0$ 即可。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;

const int N = 1e6 + 100; 
int t , n , a[N];

signed main() {
	cin >> t;
	while(t --) {
		cin >> n;
		int maxx = 0 , sum = 0 , ans = 0;
		for(int i = 1;i <= n;i ++) {
			cin >> a[i];
			sum += a[i];
			maxx = max(maxx , a[i]);
			if(maxx * 2 == sum) ans ++;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：OPEC (赞：0)

# [CF1985C Good Prefixes](https://www.luogu.com.cn/problem/CF1985C)

这道题可以枚举每一段前缀，但到了判断它是不是好的要怎么做呢？会发现将最大值作为一个数一组的，剩下的和它比较。因为如果一个数一组的不是最大值，剩下的数有最大的数，和也就比它大了。

所以需要一个累加和变量和一个最大值变量，每次进行更新，用最大值和累加和减最大值比较就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t,n;
int a[N];
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int mx=0;
	int sum=0;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		mx=max(mx,a[i]);
		sum+=a[i];
		if(mx==sum-mx)
		{
			ans++;
		}
	}
	cout<<ans<<'\n';
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：ZhaoV1 (赞：0)

## CF1985C Good Prefixes

### 题目分析
由题意可得，每个子序列只需取**一个数**并令他等于其余数的和，所以如果存在这个数，那么它一定是该子序列中最大数。所以在循环中维护一个最大值 $\max$ 每一轮输入后都判断 $\max$ 是否等同于其他所有数的和（即 $sum-\max$），最后输出合理个数 $res$ 即可。

Code
------------

```cpp
int t,n;
int a[200005];
void solve(){
	int res = 0;
	cin >> n;
	cin >> a[1];
	int sum = a[1];
	int Max = a[1];
	if(!a[1]) res++;
	for(int i=2;i<=n;i++){
		cin >> a[i];
		sum += a[i];
		if(a[i] > Max) Max = a[i];
		if(sum-Max == Max) res++;
	}
	cout << res << '\n';
}
```

---

