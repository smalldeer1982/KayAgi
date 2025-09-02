# Find The Array

## 题目描述

You are given an array $ [a_1, a_2, \dots, a_n] $ such that $ 1 \le a_i \le 10^9 $ . Let $ S $ be the sum of all elements of the array $ a $ .

Let's call an array $ b $ of $ n $ integers beautiful if:

- $ 1 \le b_i \le 10^9 $ for each $ i $ from $ 1 $ to $ n $ ;
- for every pair of adjacent integers from the array $ (b_i, b_{i + 1}) $ , either $ b_i $ divides $ b_{i + 1} $ , or $ b_{i + 1} $ divides $ b_i $ (or both);
- $ 2 \sum \limits_{i = 1}^{n} |a_i - b_i| \le S $ .

Your task is to find any beautiful array. It can be shown that at least one beautiful array always exists.

## 样例 #1

### 输入

```
4
5
1 2 3 4 5
2
4 6
2
1 1000000000
6
3 4 8 1 2 3```

### 输出

```
3 3 3 3 3
3 6
1 1000000000
4 4 8 1 3 3```

# 题解

## 作者：Eddie08012025 (赞：6)

说明：由于现在洛谷暂不支持对 CF 的提交，所以我在洛谷上没有 AC 这道题。在做这道题时是我在 CF 上提交的，[AC 记录](https://codeforces.com/contest/1463/submission/281431710)。

# 思路
首先，如果序列 $b$ 全是 $1$ 是可以满足第一二个条件的，但不一定能满足第三个条件，众所周知，任何正整数都可以整除 $1$，因此，我们可以考虑将一部分 $1$ 改成 $a_i$，使一些 $|a_i-b_i|=0$，可以大大减少 $2\times\sum_{i=1}^n|a_i-b_i|$。所以，我们可以考虑两种情况：

1. 将所有奇数位的数 $b_i$ 全部改成 $a_i$。
2. 将所有偶数位的数 $b_i$ 全部改成 $a_i$。

还有，可以保证两种情况中总有一种情况可以满足第三个条件。

# 证明
假设考虑第 $1$ 种情况时，$\sum_{i=1}^n|a_i-b_i|=c$，考虑第 $2$ 种情况时，$\sum_{i=1}^n|a_i-b_i|=d$，$S=\sum_{i=1}^n a_i$。

$\ \ \ \ c+d$

$=\sum_{i=1}^{n,i\%2=1}|a_i-1|+0+\sum_{i=1}^{n,i\%2=0}|a_i-1|+0$

$=\sum_{i=1}^{n}|a_i-1|$

$\because 1\le a_i\le 10^9$

$\therefore c+d$

$=\sum_{i=1}^{n}a_i-1$

$=S-n$

假设两种情况中总有一种情况可以满足第三个条件使错误的，那么 $c+d$ 至少为：

$\frac{1}{2}S+1+\frac{1}{2}S+1=S+2$

$\because S+2>S-n$

$\therefore$ 矛盾，假设错误，两种情况中总有一种情况可以满足第三个条件。

证毕，放上代码：
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100001];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		long long sum=0,ans=0;//sum是S 
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];//求和 
		}for(int i=1;i<=n;i++){//当奇数位为1，偶数位为a[i]时 
			if(i%2==1)ans+=a[i]-1;//ans代表|a[i]-b[i]|的和 
		}if(ans<double(sum)/2){//如果满足条件 
			for(int i=1;i<=n;i++){
				if(i%2==1)cout<<"1 ";
				else cout<<a[i]<<" ";
			}
		}else {//反之满足奇数位为a[i]的条件 
			for(int i=1;i<=n;i++){
				if(i%2==0)cout<<"1 ";
				else cout<<a[i]<<" ";
			}
		}cout<<"\n";
	}
	return 0;
}
```

---

## 作者：mot1ve (赞：5)

题解还没我这种方法，感觉这个最巧妙，应该是正解。

一开始想的是由于相邻两项可以整除，1一定是符合要求的，全构造出一个1。但是这样会导致差的绝对值太大，怎么更优呢？还是先构造一个全1序列，然后可以考虑隔一个数就把这个数变为a数组中的数，这样可以保证相邻两项之间还是可以整除的。奇数位放1或者偶数位放1都试一遍，一定有一个是满足题意的。这个也是比较好证明的。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int a[110];
signed main()
{
	cin>>T;
	while(T--)
	{
		int sum1=0,sum2=0,n;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(i%2==1)//奇数位放1的代价 
			sum1+=a[i]-1;
			if(i%2==0)//偶数位放1的代价 
			sum2+=a[i]-1;
		}
		if(sum1<sum2)
		{
			for(int i=1;i<=n;i++)
			{
				if(i%2==1)
				cout<<1<<" ";
				else cout<<a[i]<<" ";
			}
			cout<<endl;
		}
		else 
		{
			for(int i=1;i<=n;i++)
			{
				if(i%2==0)
				cout<<1<<" ";
				else cout<<a[i]<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ThySecret (赞：4)

## 思路

先来看一下构造要求，核心思路是围绕着第三点要求展开的：

$$2 \times \sum\limits_{i=1}^{n} |a_i-b_i| \leq S$$

由于 $S = \sum\limits_{i=1}^{n} a_{i}$，我们可以先不妨设 $b_i \le a_i$ 将绝对值展开，得到：对于每一个 $i$，都满足 $\left \lfloor \frac{a_i}{2} \right \rfloor  \le b_i \le a_i$，同时通过二进制的性质可以得出，在范围 $\left [ \left \lfloor \frac{a_i}{2} \right \rfloor , a_i \right ]$ 当中必然存在一个 $2^k$，因此我们只要让每一个 $b_i$ 都等于 $2^k$ 即可。

那么应该如何找到这个 $k$ 的大小呢？如果假设 $a_i = 15 = (1111)_2$，则 $\left \lfloor \frac{a_i}{2} \right \rfloor = 7 = (111)_2$，可以发现我们只需要保留最高位的 $1$ 就可以得到 $b_i$ 的值，是不是和树状数组中的 $lowbit$ 操作很像？。

## 代码如下

```C++
// Problem: Find The Array
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1463B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
// #define int long long

const int N = 1e2 + 9;
const int INF = 0x3f3f3f3f;
int a[N];

int lowbit(int x)	// 熟悉的 lowbit 操作得到最高位的 1
{
	return x & -x;
}

void solve()
{
	int n; cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	
	for (int i = 1; i <= n; i++)
	{
		int x = a[i];
		while (x - lowbit(x)) x -= lowbit(x);	// 不断减去次位的 1
		cout << x << " \n"[i == n];				// 输出剩下的 x，i == n 时候自动换行
	}
}

signed main()
{
	// ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T --)
		solve();	
	return 0;
}
```

---

## 作者：naroanah (赞：2)

注意到式子里有个 $2$，吸引人从 $2$ 的幂考虑。

发现可以对于每个 $a_i$，匹配小于等于它的最大 $2$ 的幂，这样 $\left\vert a_i - b_i\right\vert < \dfrac{a}{2}$，所以 $2\sum_{i = 1}^{n} \left\vert a_i - b_i\right\vert < S$，符合要求。


```cpp
void solve() {
    cin >> n; 
    rep(i, 1, n) {int x; cin >> x; cout << (1 << __lg(x)) << " \n"[i == n];}
}
```

---

## 作者：wmy_goes_to_thu (赞：2)

std 搞的方法是一个 1 一个数。

我搞的方法是 $2^k$。

因为 $\exists k,s.t.(s-2^k) \leq \dfrac{s}{2}$，所以我们可以用二分来查到这个 $k$，然后就可以做了。

究竟这个定理咋证，就如果大了那么除以 $2$，小了就乘 $2$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int b[105];
int main()
{
	b[0]=1;
	for(int i=1;i<=30;i++)b[i]=2*b[i-1];
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			int a;
			scanf("%d",&a);
			int wz=upper_bound(b,b+31,a)-b-1;
			printf("%d ",b[wz]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：二gou子 (赞：1)

## 比较简单的一道构造题

## 思路

首先第一个性质，构造出来的序列必须满足相邻两个数不互素。这个性质一开始看有点懵，接着往下看，第二个性质，与原序列绝对值相减的和的两倍不能比原来的和大。一开始做看得我一头雾水，但是突然灵光一现，发现第二个性质其实才是关键，而且是完成第一个性质的线索：假设就让$b_i$小于等于$a_i$，那么$|a_i-b_i|=a_i-b_i$，总和$\leq S$，那么我们如果让每一对对应的$2*(a_i-b_i) \leq a_i$，那么最后得到的结果必然符合条件。那也就是说，**如果$2*b_i \geq a_i$，那么就一定符合条件**。再加上第一个性质，很容易想到用$2$的幂次方来表示出整个美丽序列。这样就构造出了整个序列。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long int ll;
ll a[1005],sum,two[40],b[1005];
int T,n;
int main()
{
	two[0]=1;
	for(int i=1;i<=35;i++){
		two[i]=two[i-1]*2;//预处理2的i次方
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			int p=upper_bound(two,two+34,a[i])-two-1;二分查找到第一个小于等于a[i]的2的幂次方
			b[i]=two[p];
		}
		for(int i=1;i<=n;i++){
			printf("%lld ",b[i]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：wz20201136 (赞：0)

既然要满足 $2\times\sum|a_i-b_i|\leq\sum a_i$，我们只需满足 $2\times|a_i-b_i|\leq a_i$ 即可。也就是每次在区间 $[\frac{a_i}{2},2a_i]$ 中选一个数。我们发现，这个区间中一定存在一个数形如 $2^a$，而任意 $2^{a1}$ 与 $2^{a2}$ 也必定满足倍数关系。所以对于每个数，找出符合条件的 $2^a$ 即可。

时间复杂度 $O(n\log a_i)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			int ans=1;
			while(abs(x-ans)*2>x) ans*=2;
			cout<<ans<<' ';
		}
		putchar('\n');
	}
	return 0;
}
```

---

