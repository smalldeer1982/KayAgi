# Range = √Sum

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ distinct integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$\max(a_1, a_2, \dots, a_n) - \min(a_1, a_2, \dots, a_n)= \sqrt{a_1 + a_2 + \dots + a_n}. $ $$$

It can be proven that there exists a sequence of distinct integers that satisfies all the conditions above.

## 说明/提示

In the first test case, the maximum is $ 3 $ , the minimum is $ 1 $ , the sum is $ 4 $ , and $ 3 - 1 = \sqrt{4} $ .

In the second test case, the maximum is $ 29 $ , the minimum is $ 18 $ , the sum is $ 121 $ , and $ 29-18 = \sqrt{121} $ .

For each test case, the integers are all distinct.

## 样例 #1

### 输入

```
3
2
5
4```

### 输出

```
3 1
20 29 18 26 28
25 21 23 31```

# 题解

## 作者：nullqtr_pwp (赞：18)

# CF1758D Solution
### 题目描述
构造一个有 $n$ 个数的序列 $\lbrace a_i\rbrace$，满足 $\max\lbrace a_i\rbrace-\min\lbrace a_i\rbrace=\sqrt{\sum_{i=1}^n a_i}$。

**要求 $a_i$ 互不相同。**

数据范围：$2\leq n\leq 3\times 10^5$，要求 $1\leq a_i\leq 10^9$。

### 思路
钦定这个序列的和为 $4n^2$，那么差值就是 $2n$。（其实随便钦定一个偶数都相当好构造，这里选择 $2n$ 作为差值）

### 构造
考虑一个初始序列 $1,2,3,\cdots,n-1,2n+1$。现在我们要做的就是将这个序列变成合法的。我可以进行整体都 $+1$ 的操作，这样每次操作和会上涨 $n$，那么可以先整体加上某个数，使得这个序列的和尽量逼近 $4n^2$。（这样做的原因是因为题目要求互不相同）

记 $s_1=1+2+3+\cdots+(n-1)+(2n+1)$，显然 $s_1$ 可以 $O(1)$ 求出。记 $s_2=4n^2$，那么应该对整体的每一个数加上 $\left \lfloor d=\dfrac{s_2-s_1}{n}\right \rfloor $。

显然，现在得到的序列是 $d+1,d+2,d+3,\cdots+(d+n-1),d+2n+1$，那么现在的和应该是 $dn+s_1$，和应该逼近 $4n^2$，记剩下还没加进去的和是 $s_3=s_2-(dn+s_1)$。显然 $0\leq s_3\leq n-1$。

把 $s_3$ 加到第 $n-1$ 个数中即可。第 $n-1$ 个数会变成 $d+n-1+s_3$。显然第 $n-1$ 个数严格小于第 $n$ 个数。所以这样做是满足题目要求**互不相同**的。

### 核心代码
```cpp
#define F(i,a,b) for(int i=a;i<=(b);i++)
void solve(){
	int n=read();
	int sum=n*n*4,tot=0;
	F(i,1,n-1) a[i]=i;
	a[n]=1+2*n;
	F(i,1,n) tot+=a[i];
	int add=(sum-tot)/n;
	a[n-1]+=sum-tot-add*n;
	F(i,1,n) printf("%lld ",a[i]+add);
	printf("\n");
}
```


---

## 作者：Binary_Lee (赞：15)

## [题面传送门](https://www.luogu.com.cn/problem/solution/CF1758D)

### 解决思路

通过手算较小的样例，可以得出一种直接的构造方法：

- 若 $n$ 为奇数，则数列为 $\frac {n-1} 2+2,\frac {n-1} 2+3,\dots ,n,n+3,n+4,\dots,n+\frac {n-1} 2+3$。

- 若 $n$ 为偶数，则数列为 $\frac n 2,\frac n 2+1,\dots,n-1,n+1,n+2,\dots,n+\frac n 2$。

---

### 证明

为了方便计算，先把原式左右两边都平方。

- $n$ 为奇数的情况：

左式：

$${\left(\left(n+\frac {n-1} 2+3\right)-\left(\frac {n-1} 2+2\right)\right)}^2=\left( n+1 \right)^2$$

右式：

$$\sum_{i=\frac {n-1} 2+2}^{n}+\sum_{i=n+3}^{n+\frac {n-1} 2+3}=\frac{\left(\frac{3n+3}2\right)\left(\frac{n-3}2+1\right)}2+\frac{\left(\frac{5n+11}2\right)\left(\frac{n-1}2+1\right)}2\\=\frac{3n^2-3}8+\frac{5n^2+16n+11}8\\=n^2+2n+1\\=\left(n+1\right)^2$$

- $n$ 为偶数的情况：

左式：

$$\left(n+\frac n 2-\frac n 2\right)^2=n^2$$

右式：

$$\sum_{i=\frac n 2}^{n-1}+\sum_{i=n+1}^{n+\frac n 2}=\frac{\left(\frac{3n-2}2\right)\times\frac n 2}2+\frac{\left(\frac{5n+2}2\right)\times\frac n 2}2\\=\frac{3n^2-2n}8+\frac{5n^2+2n}8\\=n^2$$

---

所以两种情况下均满足题目要求，故构造方法合法。

### AC Code

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
using namespace std;
int T,n;
void solve(){
	cin>>n;
	if(n&1){
		for(int i=n/2+2;i<=n;i++) cout<<i<<' ';
		for(int i=n+3;i<=n+n/2+3;i++) cout<<i<<' ';
		cout<<endl;
	}
	else{
		for(int i=n/2;i<n;i++) cout<<i<<' ';
		for(int i=n+1;i<=n+n/2;i++) cout<<i<<' ';
		cout<<endl;
	}
}
signed main(){
	IOS;TIE;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Svemit (赞：9)

### [题目传送门](https://www.luogu.com.cn/problem/CF1758D)

（第一次CF场切绿欸）

## 题意

![](https://cdn.luogu.com.cn/upload/image_hosting/d5p4gyx2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


考虑将这段序列的平均数设为 $4n$ ,那么总和就会是 $4n^2$ ，这时候就需要让最值差等于 $2n$ ，直接让他等于 $3n$ 和 $5n$ 就可以拉， $3n$ 和 $5n$ 的平均数也正好是 $4n$ ，简单分单复数讨论一下就可以了。

AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int T,n; 
int a[N];
signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    cin>>T;
    while(T--)
    {
    	cin>>n;
    	a[1]=3*n;
    	a[n]=5*n;
    	if(n==2)
		{
			cout<<3<<' '<<1<<endl;
			continue;
		} 
    	if(n%2==0)
    	{
    		a[n/2]=4*n-1;
    		a[n/2+1]=4*n+1;
    		for(int i=n/2-1;i>1;i--)
    		  a[i]=a[i+1]-1;
			for(int i=n/2+2;i<n;i++)
			  a[i]=a[i-1]+1;
		}
		else
		{
			a[n/2+1]=4*n;
			for(int i=n/2;i>1;i--)
			  a[i]=a[i+1]-1;
			for(int i=n/2+2;i<n;i++)
			  a[i]=a[i-1]+1;
		}
		for(int i=1;i<=n;i++)
		  cout<<a[i]<<' ';
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：yeshubo_qwq (赞：4)

## 前言

膜拜 [orange_dream](https://www.luogu.com.cn/user/305013) 和 [panhongxuanyyds](https://www.luogu.com.cn/user/677124) 两位巨佬教会了我此题。

## Solution

让我们考虑奇数数列。

前 $n$ 个奇数之和为 $n^2$，最大值为 $2n-1$，最小值为 $1$，两者的差为 $2n-2$。

因为 $(2n-2)^2=4n^2-8n+4$，

所以我们将所有数加上 $3n-8$，$a_2,a_3,a_4,a_5$ 额外加 $1$。

整理一下，第 $i$ 项答案就是 $2i-1+3n-8=2i+3n-9$，记得给第二项至第五项加上 $1$。

注意：此做法仅适合 $n\ge6$ 的情况，$n<6$ 需要手算出结果。

## Code

```cpp
// 膜拜 orange_dream 和 panhongxuanyyds 两位巨佬！！
#include <bits/stdc++.h>
using namespace std;
int T,n,i;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1;
	cin>>T;
	while (T--){
	    cin>>n;
    	if (n==2) cout<<"3 1\n";
    	else if (n==3) cout<<"3 7 6\n";
    	else if (n==4) cout<<"25 21 23 31\n";
    	else if (n==5) cout<<"20 29 18 26 28\n";
    	else for (i=1;i<=n;i++) cout<<(i<<1)+3*n-9+(i>=2 && i<=5)<<(i==n?'\n':' ');
	}
	return 0;
}

```


---

## 作者：lsj2009 (赞：3)

### Preface

想到了一个超级优美的做法！！题解区里好像还没有。

### Description

构造长度为 $n$ 的数组 $a_{1\sim n}$ 满足：

$$
\max\limits_{i=1}^n{a_i}-\min\limits_{i=1}^n{a_i}=\sqrt{\sum\limits_{i=1}^n a_i}
$$

且不存在 $a_i=a_j(i\ne j)$。

$1\le n\le 3\times 10^5$。

### Solution

注意到前 $n$ 个奇数之和恰好等于 $n^2$，则我们得到了一个等式左侧等于 $2n-2$，右侧等于 $n$ 的方案。

考虑将 $n$ 改为 $2n$，只需要令和加上 $3n^2$，即令每个位置加上 $3n$。则获得一个左侧为 $2n-2$，右侧为 $2n$ 的方案。

我们再令第一个位置 $-1$，最后一个位置 $+1$ 即可。

综上得构造：
- $a_1=3n$。
- $a_i=3n+2i-1(i\ne 1,n)$。
- $a_n=5n$。

---

## 作者：Skykguj (赞：3)

一种简单的构造方法，不用分奇偶讨论。

显然，对一个定值来构造区间比凭空编造简单。

设我们选的定值是 $x$，为了方便，我们在 $a=\{1, 2, 3, 4, 5, 6, \dots, 1+x\}$ 区间上构造答案。

考虑 $max-min=n$，所有偶数都符合这种情况。设 $n=5$，假设当前构造的 $a$ 序列是 $\{1, 2, 3, 4, 6\}$，我们要让 $\sum a[i] = 25$。

可以发现，无论怎样操作，都无法让 $\sum a[i] = 25$，因此在 $n$ 为奇数无法构造出 $max-min=n$ 的序列。

由于当 $max-min=n$ 时，能构造出的区间和与答案的差值一定 $< n$，考虑扩大元素增加范围，我们直接让 $max-min=2n$，这样的话每次可以让区间和增加 $n$，我们可以这样增加 $\lfloor \frac{4n^2-\frac{(n-1)n}{2}-2n-1}{n} \rfloor$ 次，其中 $\frac{(n-1)n}{2}-2n-1$ 为初始构造序列的区间和，设当前已经增加完毕，因为 $2n+1-n>n$ 且 $4n^2-\sum a[i]<n$，我们惊奇的发现缺失的数可以一股脑加到 $a[n-1]$ 上去，然后这道题就做完了。

最后就是别忘了开 `long long`。

单次询问时间复杂度 $O(n)$。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <stack>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

using namespace std;

#define int long long

typedef long long ll;
typedef unsigned long long ull;

typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

inline int read() {
	int x = 0, f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
	for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

const int N = 300010;

int a[N];

signed main() {
	int _ = read();
	while (_ -- ) {
		int n = read(), sum = 0;
		for (int i = 1; i <= n - 1; i ++ ) a[i] = i, sum += a[i];
		a[n] = 2 * n + a[1], sum += a[n];
		int add = (4 * n * n - sum) / n;
		for (int i = 1; i <= n; i ++ ) a[i] += add;
		a[n - 1] += 4 * n * n - add * n - sum;
		for (int i = 1; i <= n; i ++ ) printf("%d ", a[i]);
		puts("");
	}
    return 0;
}
```

---

## 作者：_Fancy_ (赞：2)

## CF1758D Solution

VP 的时候发现的一道好题，但是实际上还是很难缠的

#### 我们先分两种情况看

##### 1. $n$ 为偶数的情况

主要思想就是等差数列，设这个序列为 $n-(n/2)\times x,\dots,n-x,n+x,\dots,n+(n/2)\times x$。

所以 $\sqrt{n^2}=n\times x$ 显然 $x=1$。

题目还有一个条件就是每一项小于等于 $10^9$ 所以还要满足 $\frac{3}{2}n\le 10^9$。将 $n$ 的范围代入检查无误就可以构造出一个合法答案 $ \frac{n}{2},\frac{n}{2}+1, \dots,n-2,n-1,n+1,n+2,\dots,\frac{3}{2}n$。

##### 2. $n$ 为奇数的情况

还是等差数列，

设这个序列可以转化成 $n-(n/2)\times x,\dots,n-x,n,n+x,\dots,n+(n/2)\times x$。

所以 $\sqrt{n^2}=n\times x$ 显然 $x=1$。

造出一个合法答案 $ \frac{n}{2},\frac{n}{2}+1, \dots,n-2,n-1,n,n+1,n+2,\dots,\frac{3}{2}n$。

### 小结

这道题的思维难度还是比较简单的，但是还是得注意范围，构造是小心范围，不要超过 $10^9$。

---

## 作者：MarchKid_J0e (赞：2)

# [CF1758D](https://www.luogu.com.cn/problem/CF1758D)

## 题目

构造含有 $n$ 不同元素的序列 $\{a\}$ 满足：

$$
(\max\{a\}-\min\{a\})^2=\displaystyle\sum_{i=1}^{n}a_i
$$

## 构造方案

$$
\begin{aligned}
a_i&=
\begin{cases}
i+x&i\in[1,n-2]\\
n-1+x+y&i=n-1\\
2n+1+x&i=n
\end{cases}\\
S&=4n^2-\frac{n(n-1)}{2}-(2n+1)\\
x&=\lfloor\frac{S}{n}\rfloor\\
y&=S\bmod n
\end{aligned}
$$

## 证明

考虑构造这样一个含有 $n$ 个元素的序列 $\{a\}$：

$$
a_i=
\begin{cases}
i+x&i\in[1,n-2]\\
n-1+x+y&i=n-1\\
2n+1+x&i=n
\end{cases}
$$

其中 $x,y$ 为未知的**非负整数**；通过观察上式发现上面的元素一定**互不相同**，且前 $n-1$ 个元素一定**严格单调递增**，满足一个条件；所以若使 $\max\{a\}-\min\{a\}=a_n-a_1=2n$ 这个限制成立，就是使其满足：

$$
\begin{aligned}
a_{n-1}\lt a_n\iff y\lt n+2\\
\displaystyle\sum_{i=1}^{n}a_i=(\max\{a\}-\min\{a\})^2=4n^2\\
\end{aligned}
$$

将 $a_i$ 代入式子得到：

$$
\displaystyle\sum_{i=1}^{n}a_i=(\displaystyle\sum_{i=1}^{n-1}i)+(2n+1)+nx+y
$$

设：

$$
\begin{aligned}
S
&=\sum_{i=1}^{n}a_i-(\sum_{i=1}^{n-1}i)-(2n+1)\\
&=4n^2-\frac{n(n-1)}{2}-(2n+1)
\end{aligned}
$$

为构造合法序列，设 $x=\lfloor\frac{S}{n}\rfloor$，通过移项得到 $y$ 就是剩下的一部分，$y=S-nx=S-n\lfloor\frac{S}{n}\rfloor=S\bmod n$，所以得到 $y\lt n$，所以 $y\lt n+2$ 成立，所以上述构造成立。

## Code

```cpp
/*Code by MarchKid_Joe*/
#include <bits/stdc++.h>
using namespace std;
signed main()
{
	long long n, T;
	cin >> T;
	while (T --> 0)
	{
		cin >> n;
		/*把题解的 S 通分就得到代码里的这个式子*/
		long long S = (7 * n * n - 3 * n - 2) / 2;
		long long x = S / n;
		long long y = S % n;
		for (int i = 1; i <= n - 2; i++) cout << i + x << ' ';
		cout << n - 1 + x + y << ' ' << 2 * n + 1 + x << '\n';
	}
	return 0; 
}
```

---

## 作者：Exschawasion (赞：2)

属于 Div.2 场的 D 题里比较简单的了。

***

首先考虑 $n$ 为偶数的情况。显然可以构造一个等差的数列，项数为 $n+1$，公差为 $1$，此时极差即为 $n$。它的和就是 $m \times (n+1)$，其中 $m$ 是**最中间**的那个数。$m$ 取 $n$ 就能最接近答案，但是它的和为 $n(n+1)$。这提示把最中间的那个 $n$ 去掉。这样一来项数是 $n$，和为 $n(n+1)-n=n^2$，正好符合要求。

```cpp
for(int i=n/2;i<=n+n/2;i++)if(i!=n)cout<<i<<' ';
```

难点在于 $n$ 为奇数。如果仍旧构造一个以 $n$ 为正中心的数列，它的和为 $n^2$，但极差是 $n-1$。需要调整。有什么办法对数列进行修改，并且**只影响这两个值中的一个**呢？

- 如果将数列中的每个数都加上 $d$，和将变为 $n^2+nd$，极差仍保持 $n-1$。
- 如果令 $a_1 \leftarrow a_1-c$，让 $a_n\leftarrow a_n+c$，和仍保持 $n^2$，极差将变为 $n-1+2c$。

我们将基于这两种操作来调整数组。

直接令 $d=-2$ 是不行的，因为这样会出现负数（可自行验证）。所以应当**先让极差变大**，再增大总和。

根据完全平方公式，最小的非 $n^2$ 的平方形式为 $n^2+2d+1=(n+1)^2$，所以要让极差变为 $n+1$。之后把和从 $n^2$ 变为 $n^2+2n+1$。

- 极差变为 $n+1$：最大值 $+1$，最小值 $-1$；
- 和变为 $n^2+2n$：整体所有数 $+2$；
- 和变为 $n^2+2n+1$：将次大值 $+1$。因为最大值已经加一了，次大值加一并不会产生重复数字。

代码自行处理。

---

## 作者：EBeason (赞：1)

这是一道构造题，要使得
 $$\max(a_1,a_2,\dots,a_n) - \min(a_1,a_2,\dots,a_n) = \sqrt{a_1+a_2+\dots+a_n}$$  

为了方便表示设 $maxn=\max(a_1,a_2,\dots,a_n)$  
 $minn=min(a_1,a_2,\dots,a_n)$   
我们先分奇偶讨论：  
### 偶数
我们不妨设 $a_1+a_2+\dots+a_n=N^2$   
 $maxn=n+\frac{n}{2}$ , $minn=n-\frac{n}{2}$   
那么我分别令 $N-x,N+x$ 为一对，让这些数都在      $[minn,maxn]$ 之间，正好构造出一组合法的 。
### 奇数
奇数可以按照偶数的思想，令 $a_1+a_2+\dots+a_n=(N+N)^2$  
就转化为偶数的方案，就可以简单构造出来了。
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    #define ll long long 
    #define int ll
    const int MaxN=1e6+100;
    int N,M,T;
    template<class T>
    inline void qread(T &sum)
    {
        sum=0;int boo=1;
        char x=getchar();
        while(x<'0'||x>'9'){if(x=='-')boo=-1;x=getchar();}
        while(x>='0'&&x<='9'){sum=(sum<<1)+(sum<<3)+x-'0';x=getchar();}
        sum*=boo;
    }
    template<class T>
    void qput(T x)
    {
        if(x<0) {x=-x;putchar('-');}
        if(x>9){qput(x/10);}
        putchar(x%10+48);
    }
    inline void Solve()
    {
        qread(N);
        if(N%2==0)
        {
            int ts=N/2;
            for(int i=N-ts;i<N;i++)
            qput(i),putchar(' ');
            for(int i=N+1;i<=N+ts;i++)
            qput(i),putchar(' ');
            putchar('\n');
        }
        else
        {
            int mid=4*N;
            qput(mid-N);putchar(' ');
            qput(mid+N);putchar(' ');
            qput(mid);putchar(' ');
            int tot=1;
            for(int i=4;i<=N;i++)
            {
                if(i%2==0)
                {
                    qput(mid-tot);putchar(' ');
                }
                else
                {
                    qput(mid+tot);putchar(' ');
                    tot++;
                }
            }
            putchar('\n');
        }
    }
    signed main()
    {
        qread(T);
        while(T--) Solve();
    }
```cpp

---

## 作者：Infinity_G (赞：0)

容易发现 $n$ 为偶数的情况是很简单的，直接从 $n$ 往两边加减 $1$ 即可。

考虑奇数，观察样例可以得到一种构造方法，即令最大值与最小值的差为 $2n+1$。这时候，我们让中间的数为 $\lfloor\dfrac{(2n+1)^2}{n}\rfloor$，然后往两边加减 $2$，最后对边界进行调整即可。

---

## 作者：huangrenheluogu (赞：0)

这道绿题想了比较久，毕竟我是一个比较菜的选手，给大家分享一下我的思路。

# CF1758D 构造

~~感觉做法写了和没写一样，显然是构造。~~

我们需要让机器知道一种万能的方法进行构造。

我最开始想的是 $\sum a_i=n^2$ 的方法。

但是，我们发现如果是连续 $n$ 个数，它们的差值为 $n-1$，它们的和我们需要取中间的数再乘上 $n$。

对于偶数的情况显然是很好处理的，只需要将前面的 $\dfrac{n}{2}$ 的数往前移动一位，然后保证中间项是 $n$ 即可。

偶数部分的代码如下：

```cpp
for(int i = n / 2; i < n; i++) printf("%lld ", i);
for(int i = n + 1; i <= n * 3 / 2; i++) printf("%lld ", i);
putchar('\n');
```

接下来考虑奇数的部分。

同样，从 $n^2$ 开始想。

很容易发现让最中间的一项是 $n$，然后两边等差，就可以构造出总和为 $n^2$ 的数列。

但是，它的最大值最小值之差为 $n-1$……

那么，我们可以借鉴上次的思路，把最大的数往右移动一下，最大最小值的差就变成 $n$ 了。

但是，它的总和变成了 $n^2+1$……

我们可以继续考虑移位，再往右移动，最大最小值的差就变成了 $(n+1)^2=n^2+2n+1$。

现在是总和偏小。那么我们可以把总和往右移动，由于为了保证最大值，**左边的值是不可以移动的**，所以我们总共可以在 $n^2$ 的基础上把所有的数（第一个除外）向右移动 $2$ 格，可以得到总和最大是 $n^2+2(n-1)<(n+1)^2$。不够。

我本来考虑是再移动一格的，但是我发现我傻了，毕竟右边移动一格总和还是只会多 $n-1$，但是最大最小值只差会以平方增长。

上一行删除。

但是，如果我们把右移一格的数列**整体**右移一格，就可以增加 $n$，弥补了我们的差距，但是不增加最大最小值的差值。

算一下。

总和（最大值）：$n^2+2(n-1)+n=n^2+3n-2$。

最大最小值之差：$(n+1)^2=n^2+2n+1$。

由于 $n\ge3$，所以我们发现总和（最大值）是大于等于最大最小值之差的。

所以，我们可以在 $n$ 为中心的前提下**整体右移一格**之后把最右端的值右移两格，然后一个一个往右边移动，调整一下就可以了。

### Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5;
int T, n, a[N], sum;
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld", &n);
		if(n & 1){
			for(int i = 1; i <= n; i++) a[i] = (n + 1) / 2 + i;
			a[n] += 2;
			sum = (a[n] - a[1]) * (a[n] - a[1]);
			for(int i = 1; i <= n; i++) sum -= a[i];
			for(int i = n - 1; i >= 2 && sum; i--){
				a[i]++, sum--;
				if(sum) a[i]++, sum--;
			}
			for(int i = 1; i <= n; i++) printf("%lld ", a[i]);
			putchar('\n');
		}
		else{
			for(int i = n / 2; i < n; i++) printf("%lld ", i);
			for(int i = n + 1; i <= n * 3 / 2; i++) printf("%lld ", i);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：Aegleseeker_ (赞：0)

# 题意
[题目传送门](https://www.luogu.com.cn/problem/CF1758D)

给定一个整数 $n$，构造一个 $n$ 个正整数的序列 $a_1,a_2,a_3,...a_n$，使序列的极差（最大值与最小值的差）等于序列元素之和的算术平方根，即
$$\max_{i=1}^{n}{a_i}-\min_{i=1}^{n}{a_i}=\sqrt{\sum_{i=1}^{n}a_i}=n$$
**注意序列中的每个元素必须互不相同。**

# 思路
当 $n$ 为偶数时，我们可以直接按照 $n-1,n+1,n-2,n+2...n-n\div 2,n+n\div 2$ 构造。这样 $n$ 个数中的最大值减最小值就等于 $n$，而且 $n$ 个数的和就是 $n\times n$，刚好满足题意。如果当 $n$ 是奇数时我们依旧可以在偶数构造的方式上做出改变，先将 $n$ 自增变为偶数，然后去掉 $n-1$ 这个数，这个时候就剩了奇数个数，然后将其余 $n-1$ 个数都加上 $1$，这样就可以保证极差不变而且总和也不变，也是满足题意的。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        if(n%2==0){	//分别处理偶数与奇数的情况
			for(int i=n-n/2;i<=n+n/2;i++){	//从n-n/2到n+n/2
				if(i!=n){
					cout<<i<<" ";
				}
			}
			cout<<endl;		
		}else{
			for(int i=1;i<=n/2;i++){
				cout<<n+i<<" "<<n-i<<" ";	//多补少
			}
			cout<<endl;
		}
    }
}
```
~~蒟蒻的第一篇题解，求通过~~

---

## 作者：liangbowen (赞：0)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1758D)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17315955.html)

一种比较麻烦的做法，比较莽，和题解区不一样，但是方法困难很多。 ![](//图.tk/0)

## 思路

很自然的想法是让 $a_n-a_1=n$，这样整个序列会相对比较连续，好处理。

首先可以尝试 $x+1, x+2, \cdots, x+n$ 的填法。发现不能完美填充（也就是还需要额外地补），但是为了保持 $a_n-a_1=n$，无法操作。

所以考虑 $x, x+2, x+3, \cdots, x+n$ 的填法，这样子 $2 \sim n$ 都可以往前补，容错更大（可以自行模拟）。

然后计算一下合适的 $x$：

$\because n = \sqrt{x + \dfrac{(2x+n+2)(n-1)}{2}}$

$
\begin{aligned}
\therefore n^2
& = x + \dfrac{(2x+n+2)(n-1)}{2} \\
& = x + \dfrac{2xn-2x+n^2-n+2n-2}{2} \\
& = xn + \dfrac{n^2}{2} + \dfrac{n}{2} - 1 \\
\end{aligned}
$

$\therefore xn= n^2 - \dfrac{n^2}{2} - \dfrac{n}{2} + 1 = \dfrac{n^2-n+2}{2}$

$\therefore x = \dfrac{n^2-n+2}{2n} = \dfrac{n}{2}-\dfrac{1}{2}+\dfrac{1}{n}$

这个就是理论上刚刚好的 $x$，由于它要是整数，采取向上取整。

然后就可以写出一个看起来没有问题的代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, ans[300005];
long long calc()
{
	long long sum = 0;
	for (int i = 1; i <= n; i++) sum += ans[i];
	return sum - 1ll * (ans[1] - ans[n]) * (ans[1] - ans[n]);
}
void solve()
{
	scanf("%d", &n);
	if (n == 3) {puts("3 6 7"); return;}
	int x = ceil(n / 2.0 - 1 / 2.0 + 1.0 / n);
	ans[1] = x; for (int i = 2; i <= n; i++) ans[i] = x + i;
	long long sum = calc();
	for (int i = 2; i < n; i++) //顺着填补
		if (sum != 0) sum--, ans[i]--;
		else break;


	if (sum != 0) printf("Emmmm...... n = %d false, sum = %d\n", n, sum); //check


	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```

然后发现 $\operatorname{check}()$ 标记的位置，在 $n$ 为奇数时，总是会显示答案差了个 $1$，但是已经没有位置补了。

（好像所有 $n$ 为奇数时，$sum$ 都是 $1$，没有去证明，有没有老哥帮忙填一下这个坑？）

这个时候会有点崩溃，所以开始乱搞。我们对整个数组的所有元素翻倍。

这个时候 $(a_1-a_n)^2$ 总是要大于 $\sum\limits_{i=1}^n a_i$ 的，所以通过整体补的方式，让差值小于 $n$。

此时数组的相邻元素差控制在 $2$ 左右（边界可能比较特殊），所以直接按照上面代码的方式填就行，只不过是倒着填，以及 $ans_i$ 要增加而已。

这样子的容错大约是 $2n$（应该要小一点），但是容下 $n$ 是绰绰有余的，所以就做完了。

## 代码

重构了代码，应该很好理解！

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, ans[300005];
long long calc()
{
	long long sum = 0;
	for (int i = 1; i <= n; i++) sum += ans[i];
	return sum - 1ll * (ans[1] - ans[n]) * (ans[1] - ans[n]);
}
void solve()
{
	scanf("%d", &n);
	if (n == 2) {puts("1 3"); return;} //特判
	if (n == 3) {puts("3 6 7"); return;}
	int x = ceil(n / 2.0 - 1 / 2.0 + 1.0 / n);
	ans[1] = x; for (int i = 2; i <= n; i++) ans[i] = x + i; //这里就是按照上面的方法乱搞
	for (int i = 1; i <= n; i++) ans[i] <<= 1;
	long long sum = -calc();
	for (int i = 1; i <= n; i++) ans[i] += (sum / n);
	sum %= n;
	
	for (int i = n - 1; i >= 2; i--)
		while (ans[i + 1] != ans[i] + 1) //倒着填补
		{
			if (sum != 0) ans[i]++, sum--;
			else break;
		}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：cats142857 (赞：0)

序列 $a$ 满足 $a$ 中的最大值减最小值等于 $a$ 的所有项的和的平方根。

可以发现，这是一个很弱的条件。最大值和最小值固定以后，中间的所有项都只影响等式右侧，固定最大最小值后只需要调整中间的值使等式成立即可。

但由于 $a$ 中所有项均不能相同，若最小值固定为 $s$ ，最大值固定为 $t(t\ge s+n-1)$ ，则 $s+t+(s+1)+(s+2)+…+(s+n-2)\le sum\le s+t+(t-1)+(t-2)+…+(t-n+2)$ 。

为了让 $max-min$ 尽可能处在上述范围内，固定 $t=10^9$ ，并二分第二个不等式得到最大可能满足条件的 $s$ ，检测是否满足第一个等式，最后通过微调其他项使等式成立。

最后，发现只有在 $2\le n\le 3$ 时，不存在满足条件的 $s$ 使两个不等式同时成立。特判并输出 $1,3$ 与 $3,6,7$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[300000];
int main(int argc, char** argv) {
	ios::sync_with_stdio(false),cin.tie(0);
	int T;
	long long s,t,n,i,sum,k,l,r,mid;
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		if(n==2)
		{
			cout<<"1 3\n";
			continue;
		}
		if(n==3)
		{
			cout<<"3 6 7\n";
			continue;
		}
		t=1000000000;
		l=0;
		r=999999999;
		while(r-l>1)
		{
			mid=(l+r)/2;
			if(((t*2-n+2)*(n-1)/2+mid)>=(t-mid)*(t-mid))r=mid;
			else l=mid;
		}
		s=r;
		a[0]=s;
		for(i=1;i<n;i++)a[i]=t-i+1;
		sum=0;
		for(i=0;i<n;i++)sum+=a[i];
		sum-=(t-s)*(t-s);
		for(i=n-1;sum>0;i--)
		{
			k=min(sum,t-n+1-s);
			a[i]-=k;
			sum-=k;
		}
		for(i=0;i<n;i++)cout<<a[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：Siteyava_145 (赞：0)

构造题。

### 转化题意：

构造一个长度为 $n$ 的数组，使最大值和最小值的差的平方等于数组的总和。

---
一想到平方，数组总和，就应该想到数列

$1,3,5,...,(2n-1)$

其总和为 $n^2$。

这样我们只要将这个数列的两端的差缩减到 $n$，且保证总和不变即可。

缩减方法：首尾配对，首部数加 $1$，尾部数减 $1$。

$n$ 为偶数时，可以把数列缩减成

$\dfrac{n}{2},\dfrac{n}{2}+1,...,n-1,n+1,...,\dfrac{3n}{2}$

最大值和最小值的差为 $n$，总和 $\dfrac{n}{2}\times 2=n^2$ 符合要求。

---

$n$ 为奇数时，数列为

$\dfrac{n+3}{2},\dfrac{n+3}{2}+1,...,n,n+3,n+4,...,\dfrac{(3n+5)}{2}$

求总和：

$\begin{aligned}\text{原式} & =(\dfrac{n+3}{2}+\dfrac{n+3}{2}+1+...+n)+(n+3+n+4+...+\dfrac{(3n+5)}{2})\\ & = \dfrac{3n+3}{2}\cdot \dfrac{n-1}{2}\cdot\dfrac{1}{2}+\dfrac{(5n+11)}{2}\cdot\dfrac{(n+1)}{2}\cdot\dfrac{1}{2}\\ & = \dfrac{3n^2+3}{8}+\dfrac{5n^2+16n+11}{8}\\ & = \dfrac{8n^2+16n+8}{8}\\ & =(n+1)^2\end{aligned}$

最大值和最小值的差：$\dfrac{3n+5}{2}-\dfrac{n+3}{2}=n+1$。

$(n+1)^2=(n+1)^2$

所以此数列满足要求。

---

综上：

$n\bmod 2=0$ 时，数列为 $\dfrac{n}{2},\dfrac{n}{2}+1,...,n-1,n+1,...,\dfrac{3n}{2}$；

$n\bmod 2=1$ 时，数列为 $\dfrac{n+3}{2},\dfrac{n+3}{2}+1,...,n,n+3,n+4,...,\dfrac{(3n+5)}{2}$

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        if(n%2==0){
            for(int i=n/2;i<=n-1;i++){
                printf("%d ",i);
            }
            for(int i=n+1;i<=n*3/2;i++){
                printf("%d ",i);
            }
            puts("");
        }else{
            for(int i=(n+3)/2;i<=n;i++){
            	printf("%d ",i);
			}
			for(int i=n+3;i<=n+(n+5)/2;i++){
            	printf("%d ",i);
			}
			puts("");
        }
    }
}
```


---

