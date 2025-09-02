# Koxia and Permutation

## 题目描述

Reve has two integers $ n $ and $ k $ .

Let $ p $ be a permutation $ ^\dagger $ of length $ n $ . Let $ c $ be an array of length $ n - k + 1 $ such that $ $$$c_i = \max(p_i, \dots, p_{i+k-1}) + \min(p_i, \dots, p_{i+k-1}). $ $  Let the <span class="tex-font-style-it">cost</span> of the permutation  $ p $  be the maximum element of  $ c $ .</p><p>Koxia wants you to construct a permutation with the minimum possible cost.</p><p> $ ^\\dagger $  A permutation of length  $ n $  is an array consisting of  $ n $  distinct integers from  $ 1 $  to  $ n $  in arbitrary order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation ( $ 2 $  appears twice in the array), and  $ \[1,3,4\] $  is also not a permutation ( $ n=3 $  but there is  $ 4$$$ in the array).

## 说明/提示

In the first test case,

- $ c_1 = \max(p_1,p_2,p_3) + \min(p_1,p_2,p_3) = 5 + 1 = 6 $ .
- $ c_2 = \max(p_2,p_3,p_4) + \min(p_2,p_3,p_4) = 3 + 1 = 4 $ .
- $ c_3 = \max(p_3,p_4,p_5) + \min(p_3,p_4,p_5) = 4 + 2 = 6 $ .

Therefore, the cost is $ \max(6,4,6)=6 $ . It can be proven that this is the minimal cost.

## 样例 #1

### 输入

```
3
5 3
5 1
6 6```

### 输出

```
5 1 2 3 4
1 2 3 4 5
3 2 4 1 6 5```

# 题解

## 作者：AllenKING_RED (赞：5)

## 题目大意

给定两个整数 $n$ 和 $k$ ，要求构造一个长度为 $n$ 的排列使得该排列所有长度为 $k$ 的字段的最大值和最小值之和中的最大值最小。

## 具体思路

- 我们首先考虑 $k=2$ 的情况

	此时问题等价于让所以相邻点对的和的最大值最小。
	
	考虑将从 $1$ 到 $n$ 的 $n$ 个整数依次插入一个初始为空的序列。

	不难想到，每次依次插入当前的最大值和最小值，若最后剩余一个则直接插入即可，这样可以使得每个相邻点对的和尽量平均，从而让和的最大值	最小。

	例子：

	```
	input:
	5 2
	output:
	5 1 4 2 3
	```

- 我们接着考虑 $k=3$ 的情况

	此时考虑的情况相当于将之前 $k=2$ 时的每个区间考虑范围向后拓展一	个，并且删去上述情况中的最后一个区间。

	由于每次依次插入最大值和最小值，所以区间向后扩展出的数必然小于原区间最大值，大于原区间最小值,这样向后扩展出的数对原答案没有影		响，所以我们依然可以使用在上一情况中使用过的构造方法。

- 最后我们讨论 $k$ 为其他数的情况

	假设 $k=4$ ，此时的情况仍相当于 $k=3$ 时的区间扩展一步，所以同	述情况的证明可得，原构造方法仍成立，对于其他情况也可以类推证明，**	故所有情况下均可用原构造方法：考虑将从 $1$ 到 $n$ 的 $n$ 个整数依次插入一个初始为空的序列，每次依次插入当前的最大值和最小值，若最后剩余一个则直接插入即可。**

## 代码实现

实现很简单，赛时代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(void)
{
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			if(i%2==1)cout<<n-(i+1)/2+1<<" ";
			else cout<<i/2<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```





---

## 作者：abensyl (赞：3)

原题：[CF1770B](https://www.luogu.com.cn/problem/CF1770B)

这个题目我比赛时 WA 两次，但是最终还是过了。

## 思路：

本题为构造题。

我们只需要构造，使得每个区间内的最大值与最小值的和最小。

- 那么最小值是多少呢？

首先，我们知道，最好的情况是 $1$ 和 $n$ 放在同一个区间内，将 $2$ 和 $n-1$ 放在同一个区间里，以此类推。

已发现，我们可以把 $1$ 和 $n$ 放在第 $i$ 到第 $k$ 个数字的区间里，把 $2$ 和 $n-1$ 放在第 $k+1$ 到第 $2k$ 个数字的区间里，以此类推，而放到区间内的位置可以任意，但是小数需要在大数之后，我的做法是大值放区间第一个数，小值放区间内的第二个数。

那么，我们还剩下一些数字，这些数字我们随便将他们填在任意位置即可。

## 代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5+5;
int a[N];

int main() {
	int T; cin>>T;
	while(T--) {
		memset(a,0,sizeof a);
        int n,k;
        cin>>n>>k;
        int t=0,s=n;
        for(int i=2;i<=n;i+=k) a[i]=++t; //放置小数
        for(int i=1;i<=n;i+=k) a[i]=s--; //放置大数
        for(int i=1;i<=n;++i) if(!a[i]) a[i]=++t;//剩下数字随便放
        for(int i=1;i<=n;++i) cout<<a[i]<<' '; //输出答案
        cout<<endl;
	}
	return 0;
}
```

我的 [AC记录](https://www.luogu.com.cn/record/98458661)。

---

## 作者：yangyang1000 (赞：2)

### 这个题是一个比较简单的构造题

### 最小值

首先，我们知道 $c_i$ 的值是
$$ c_i  = \max(p_i,…,p_{n+k-1}) + \min(p_i,…,p_{n+k-1})$$ 

其中必有一个 $c_i$，它的 $\max(p_i,…,p_{n+k-1}) = n$，此时它的 $\min(p_i,…,p_{n+k-1})$ 此时最小为 $1$。

所以，这个全排列的总分的**最小值**应为 $n+1$。

### 构造

我们已知总分的最小值为 $n+1$，所以构造时，$n$ 和 $1$ 必须相距 $k$ 以内。

为了避免 $k$ 太小，我们不妨将 $n$ 和 $1$ **相邻**，这时，$n-1$ 项必须和 $1$ 或 $2$ 在 $k$ 内。

一看，这不是**交叉构造吗**？

只要暂未加入序列的最大值后面接上暂未加入序列的最小值后面接上暂未加入序列的最大值，一直这样下去，不就行了吗？

例：$n\hspace{0.25cm}1\hspace{0.25cm}n-1\hspace{0.25cm}2\hspace{0.25cm}n-2\hspace{0.25cm}3… $

### 代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int t,n,k;

int main()
{
	scanf("%d",&t);
	for(int o=1;o<=t;o++)
	{
		scanf("%d %d",&n,&k);
		int l=1,r=n;
		bool flag = 0;
		for(int i=1;i<=n;i++)
		{
			if(flag == 0)
			{
				printf("%d ",r);
				r--;
				flag = 1;
			}
			else
			{
				printf("%d ",l);
				l++;
				flag = 0;
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Night_sea_64 (赞：1)

### 题目大意

给你两个正整数 $n$ 和 $k$。如果有一个长度为 $n$ 的排列 $p_1\sim p_n$，令 $c$ 为一个长度为 $n-k+1$ 的序列，满足 $c_i=\max\{p_i,p_{i+1},\dots,p_{i+k-1}\}+\min\{p_i,p_{i+1},\dots,p_{i+k-1}\}$，则 $p$ 的花费为 $\max\{c_1,c_2,\dots,c_{n-k+1}\}$。

请构造一组 $p_1\sim p_n$ 满足 $p$ 的花费最小。如果有多组解输出任意一组。

---

### 题解

首先，显而易见地，$p$ 中的最大值（也就是 $n$）一定会成为至少一组中的最大值。而我们要让 $c$ 的最大值最小，把 $n$ 跟 $1$ 放在同一组就可以了，不可能有比这更优的方案了。我们可以把 $n$ 放在第一个，$1$ 放在第二个，这样有 $n$ 的组里面一定有 $1$ 了，就可以确保它们在同一组了（$k=1$ 除外，但是 $k=1$ 的话随便构造就行了）。

接下来让 $n-1$ 跟 $2$ 在一组，$n-2$ 跟 $3$ 在一组……以此类推，这样这些两个数的和一定等于 $n+1$，也就是 $c$ 中最大值能达到的最小值了。（所以我们发现：$k$ 根本没用……）

AC 代码如下，短的可怜：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n/2;i++)
            cout<<n-i+1<<" "<<i<<" ";
        if(n%2)cout<<n/2+1;
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：rui_er (赞：1)

$k=1$ 的情况是平凡的。

$k > 1$ 的情况，显然答案至少为 $n+1$，下面给出构造证明 $n+1$ 总可以取到。可以构造 $p=[n,1,n-1,2,n-2,3,\cdots]$，此时以 $n$ 作为最大值的连续段中最小值最大为 $1$，以 $n-1$ 作为最大值的连续段中最小值最大为 $2$，以此类推。我们保证了所有连续段都有 $\max+\min\le n+1$，因此 $n+1$ 总可以取到。

```cpp
// Problem: Koxia and Permutation
// Contest: Codeforces
// URL: https://m2.codeforces.com/contest/1770/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int T, n, k;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	for(scanf("%d", &T); T; T--) {
		scanf("%d%d", &n, &k);
		int L = 1, R = n;
		rep(i, 1, n) {
			if(i & 1) printf("%d%c", R--, " \n"[i==n]);
			else printf("%d%c", L++, " \n"[i==n]);
		}
	}
	return 0;
}
```

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1770B)

[codeforces](https://codeforc.es/contest/1770/problem/B)

### 题目大意

洛谷链接。

### 思路

当 $k=1$ 时，花费一定是 $2n$，随便构造即可。

---
当 $k \ge 2$ 时，先证明花费 $\ge n+1$。

> 对于一个长度为 $n$ 的排列 $p$，一定有一位置 $i$ 使得 $p_i=n$。
>
> 而题面保证 $p_i$ 一定包含在至少一个长度为 $k$ 的区间内。
>
> 又因为 $k \ge 2$，包含 $p_i$ 的任一长度为 $k$ 的区间最大值为 $n$，最小值至少为 $1$。
>
> 所以花费至少为 $n+1$。

按照题意，一定存在一个排列 $p=[n,1,n-1,2,\dots,\lceil \frac{n}{2} \rceil](n \mod 2 = 1)$ 或 $p=[n,1,n-1,2,\dots,\frac{n}{2}+1,\frac{n}{2}](n \mod 2 = 0)$。此时无论 $k$ 为 $[2,n]$ 中的哪一值，整个序列的花费都是 $n+1$。

判断 $n$ 的奇偶性后，直接输出即可。时间复杂度 $O(n)$。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
void solve(){
	cin>>n>>k;
	for(int i=1,j=n;i<j;++i,--j)cout<<j<<' '<<i<<' ';
	if(n&1)cout<<n/2+1;//注意 n 的奇偶性
	cout<<'\n';
	return;
}
int main(){
	int t=1;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Gaode_Sean (赞：0)

这是一道构造题。

我们先考虑答案（即 $\max{c_i}$）的下界是多少，很显然是 $n+1$。

那么我们的目标是：构造出一种排列，使答案的上界尽量靠近答案的下界（即 $n+1$）。

不难得到一种排列：$n ,1,n-1,2,n-2,3......$。这样使得答案一定是 $n+1$。这样的构造方案一定是最优的。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
void solve()
{
	scanf("%d%d",&n,&m);
	if(n%2==1)
	{
		for(int i=n;i>(n+1)/2;i--) printf("%d %d ",i,n+1-i);
		printf("%d",(n+1)>>1);
	}
	else
	{
		for(int i=n;i>n/2;i--) printf("%d %d ",i,n+1-i);
	}
	puts("");
}
int main()
{
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：zajasi (赞：0)

## 解题思路
因为本题要求最大值加上最小值的和要满足最大的最小。首先我们可以得出猜想——在所有最大值加上最小值的和中，最大的那个一定是 $n+1$。

为什么呢？假设这个和为 $n$，也就是 $1+(n-1)$ 或 $2+(n-2)$ 等。那么此时，最大值 $n$ 跟其他某一个数配起来的和就一定会大于 $n$ 了，所以证明结论。

然后我们采用贪心的思想——肯定不可能把最大值放在多个区间内同用，只有可能将最小值这样做。也就是说，大概构造出来的序列是这样的：首先 $k-1$ 个最大值，然后 $k-1$ 个最小值填上。周而复始这样做，就可以构造出最优解啦。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,k;
main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		if(k==1){
			for(int i=1;i<=n;i++){
				cout<<i<<" ";
			}
			cout<<"\n";
			continue;
            		//当时赛中嫌烦，这里就直接判掉也没有问题
		}
		int x=n,y=1,f=0;//用 x 记录此时最大的数用到哪个数；用 y 记录此时最小的数用到哪个数。
		while(1){
			for(int i=x;i>=x-k+2;i--){
				if(i<y){
					f=1;
					break;
				}
				
				cout<<i<<" ";
			}//k-1 个最大数
			x-=k-1;
			for(int i=y;i<=y+k-2;i++){
				if(i>x){
					f=1;
					break;
					
				}
				cout<<i<<" ";
			}//k-1 个最小数
			if(f==1){//数已经用完了
				cout<<"\n";
				break;
			}
			
			y+=k-1;
//			cout<<x<<" "<<y<<"\n";
		}
		
	}
	return 0;
}
```


---

## 作者：郑朝曦zzx (赞：0)

## 题解

- 论证：由于一个序列的权值定义为其最小值 + 其最大值，那么整个排列的权值不可能比 $n + 1$ 还小（把 $1$ 和 $n$）放在一起。

- 构造：

试着构造 $n + 1$ 的解，构造方式如下：

1. 对于位置 $i \bmod k = 0$ 那么这里就填上 $\frac{i}{k}$

2. 否则就从大往小填充

比如第一个样例就填成这个样子：

```cpp
5 4 1 3 2
```
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
int a[200010];
signed main()
{
	int t = read();
	while (t--)
	{
		int n = read(), m = read(), l = 1, r = n;
		for (int i = 1; i <= n; ++i)
		{
			if (i % m == 0) a[i] = l++;
			else a[i] = r--;
			printf("%d ", a[i]);
		}
		printf("\n");
	}
    return 0;
}
```


---

## 作者：aimcf (赞：0)

题目要求让最大的连续 $k$ 个的最大的和最小的的和最小。

考虑最大的数 $n$。为了让最大的连续 $k$ 个的最大的和最小的的和最小，需要让在这连续的 $k$ 个数中满足最小值尽量的小，是 $1$。那么只需要让最大的数放在第一个，最小的数放在第二个即可。

同理。第二大的数的下一个应该是第二小的数，第三大的数后面应该是第三小的数。

最后需要特判 $n\bmod 2 = 1$ 的情况。

---

