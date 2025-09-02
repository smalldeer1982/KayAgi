# Sum on Subarrays

## 题目描述

For an array $ a = [a_1, a_2, \dots, a_n] $ , let's denote its subarray $ a[l, r] $ as the array $ [a_l, a_{l+1}, \dots, a_r] $ .

For example, the array $ a = [1, -3, 1] $ has $ 6 $ non-empty subarrays:

- $ a[1,1] = [1] $ ;
- $ a[1,2] = [1,-3] $ ;
- $ a[1,3] = [1,-3,1] $ ;
- $ a[2,2] = [-3] $ ;
- $ a[2,3] = [-3,1] $ ;
- $ a[3,3] = [1] $ .

You are given two integers $ n $ and $ k $ . Construct an array $ a $ consisting of $ n $ integers such that:

- all elements of $ a $ are from $ -1000 $ to $ 1000 $ ;
- $ a $ has exactly $ k $ subarrays with positive sums;
- the rest $ \dfrac{(n+1) \cdot n}{2}-k $ subarrays of $ a $ have negative sums.

## 样例 #1

### 输入

```
4
3 2
2 0
2 2
4 6```

### 输出

```
1 -3 1
-13 -42
-13 42
-3 -4 10 -2```

# 题解

## 作者：hy233 (赞：17)

## 题意简述
你需要构造一个长度为 $n$ 的序列 $a_i$，满足下列要求：

- $a_i \in [-1000,1000]$。
- 有恰好 $k$ 个连续子序列和为正数。
- 其余的 $n\times (n+1)/2$ 个连续子序列和为负数。

$2 \le n \le 30\ ;0\le k\le n\times (n+1)/2$。

## 题解
我们可以将一个长度为 $n$ 的序列转为长度为 $n+1$ 的前缀和序列 $s_i$， 一个连续子序列 $[l,r]$ 的和就可以转化为 $s_r-s_{l-1}$。因为 $s_i$ 两两不相等（子序列和非 $0$ ），我们很容易想到：排列。要求有 $k$ 个正数相当于有 $k$ 对 $(i,j)$ 使得 $i<j,s_i<s_j$，即构造一个**正序对**个数为 $k$ 的排列。我们想到冒泡排序的过程中每次将一个逆序对变为正序对，所以我们从排列 $n+1,n,\cdots,1$ 开始，交换 $k$ 次即可。最后输出该排列的差分即为答案。

## 代码
```cpp
int a[N];
int main()
{
	int t=rd();
	while(t--)
	{
		int n=rd(),k=rd();
		for(int i=0;i<=n;i++)
			a[i]=n-i+1;
		for(int i=0;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
				if(k>0)
				{
					k--;
					swap(a[i],a[j]);
				}
			}
		for(int i=1;i<=n;i++)
			cout<<a[i]-a[i-1]<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：igAC (赞：9)

[更好的阅读体验](https://www.luogu.com.cn/blog/780168/solution-cf1809c)

# $\text{Describe}$

[洛谷link](https://www.luogu.com.cn/problem/CF1809C)

[Codeforces link](https://codeforces.com/contest/1809/problem/C)

请构造一个序列，使得这个序列中恰好有 $k$ 个子序列的和为正数且另外 $\dfrac{n(n+1)}{2}-k$ 个子序列的和为负数，要求连续。

# $\text{Solution}$

闲话：赛场上 $5 \text{min}$ 想到了正解，然后因为各种伞兵错误调了半个小时。

对于 $\dfrac{i(i+1)}{2}=k$ 的情况，显然前面 $i$ 项都填 $1$，后面 $n-i$ 项都填 $-1000$ 即可。

那么其余情况呢？

很容易想到，找到最小的 $i$ 使得 $\dfrac{i(i+1)}{2} > k$，在前 $i$ 个格子进行操作，剩下的格子全部填上 $-1000$。

那么前 $i$ 个格子怎么填呢？

先说结论：

对于前面 $i-1$ 项，全部填上 $30$（其他数字也是可以的，但不要超过 $32$）。

在第 $i$ 项填上 $-1-30(\dfrac{i(i+1)}{2}-k-1)$。

接下来证明这样为什么是对的：

前面的 $i-1$ 项正数已经贡献了 $\dfrac{i(i-1)}{2}$ 个正子序列，接下来只用考虑剩下 $k-\dfrac{i(i-1)}{2}$ 个正子序列。

以下令 $d=k-\dfrac{i(i-1)}{2}$。

考虑在序列的末尾加上一个负数对整个序列的贡献，如下例：

```
30 30 30 -1
```

前面 $3$ 项有 $6$ 个正子序列，而加上了一个 $-1$ 就增加了 $3$ 个正子序列。

因为 $-1$ 可以与前面三项结合（连续的），每一次结合都会产生一个正子序列。

也就是说，在末尾加上一个数只需考虑每一个后缀和是否是正数就可以了。

有多少个后缀和是正数就会增加多少个正子序列。

我们知道，第 $i$ 项需要贡献 $d$ 个正子序列。

所以我们需要让 $d$ 个后缀和为正数，也就是让 $i-d-1$ 个后缀和为负数（因为最后一项已经是负数了，所以要减一）。

又因为后缀和是严格单调上升的，所以在第 $i$ 项填

$$

-1-30(i-1-k+ \dfrac{i(i-1)}{2})$$

化简后得

$$-1-30(\dfrac{i(i+1)}{2}-k-1)$$

# $\text{Code}$

赛时代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 35
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,k;
int a[N];
void solve(){
	n=read(),k=read();
	if(!k) for(int i=1;i<=n;++i) printf("%d ",-1000);
	else{
		int cnt=0;
		for(int i=1;i<=n;++i){
			int d=i*(i+1)/2;
			if(d>=k){
				cnt=i;
				break;
			}
		}
		for(int i=1;i<cnt;++i) a[i]=30;
		if(cnt*(cnt+1)/2==k) a[cnt]=30;
		else a[cnt]=-1-30*(cnt*(cnt+1)/2-k-1);
		for(int i=cnt+1;i<=n;++i) a[i]=-1000;
		for(int i=1;i<=n;++i) printf("%d ",a[i]);
	}
	puts("");
}
int main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：8)

简单构造题。

注意不能出现和为 $0$ 的情况。

以下负无穷规定为可以填的最小值。

考虑在一串数后面加一个数的贡献，是所有后缀和（包括空后缀）加这个数大于 $0$ 的个数。

构造方案为，在前面全部填 $2$ 后面填一个数，再后面填负无穷。

设当前填了 $x$ 个 $2$，那么当前数量为 $\frac{x\times (x+1)}{2}$，再填一个 $2$ 贡献为 $\frac{(x+1)\times (x+2)}{2}$。如果 $k$ 不小于填的贡献就继续填 $2$，否则考虑直接结束贡献。设 $k$ 比当前 $x$ 的贡献多 $y$，继续填 $2\times (x-y-1)-1$ 即可满足 $k$ 的限制，后面填负无穷即可。

这样所有的 $k$ 一定都有解。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=40;
int n,k,a[N];
signed main()
{
	int T=read();
	while(T--){
		n=read(),k=read();
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			if(k>=i){
				k-=i;
				a[i]=2;
				continue;
			}
			a[i]=-2*(i-k-1)-1;
			for(int j=i+1;j<=n;j++)
				a[j]=-1000;
			break;
		}
		for(int i=1;i<=n;i++)
			cout<<a[i]<<' ';
		cout<<'\n';
	}
	return 0;
}

```

---

## 作者：w9095 (赞：3)

[CF1809C Sum on Subarrays](https://www.luogu.com.cn/problem/CF1809C)

一道黄题做了一上午我可以退役了。

构造题。由于直接构造并不是那么容易，所以考虑在一个初始元素全为 $-1$ 的序列上构造。

考虑将一个负数改为正数 $1000$ 对答案造成的贡献（因为取 $1000$ 计算比较方便）。设在放置这个正元素之前已经放置了 $x$ 个正元素，则这个正元素会造成 $n-x$ 的贡献，也就是会创造 $n-x$ 个新的正区间。

原因显然，由于负数均为 $-1$，$n$ 又小于等于 $30$，$1000$ 相当于正无穷，所以从这个元素到序列中的任何一个位置都是正区间。如果某一个位置已经是 $1000$ 了，那么在插入之前的这个 $1000$ 时已经计算了这一段区间，需要减去不计算，所以贡献为 $n-x$。

由于位置无关，我们尽量把 $1000$ 往后放，如果再放一个 $1000$ 就超过了正区间的数量，我们考虑在前面创造一些单独的正区间。设剩下的数为 $s$，则我们将第一个数改为 $200$，很明显，这也相当于一个正无穷。然后，我们要把第 $s+1$ 个位置的数改为 $-400$，消除 $200$ 对后面的数的影响。由于之前放的数是 $1000$，所以 $-400$ 并不会影响其正无穷性质。

第一个数 $200$ 可以把从第一个数开始到 $s+1$ 以前的区间变成正区间，刚好是 $s$ 个正区间，刚好符合要求。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,k,a[40];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
		scanf("%lld%lld",&n,&k);
		long long now=n;
		for(int i=1;i<=n;i++)a[i]=-1;
		for(int i=n;i>=1;i--)
		    if(k>=now)a[i]=1000,k-=now,now--;
		    else break;
		if(k!=0)a[1]=200,a[k+1]=-400;
		for(int i=1;i<=n;i++)printf("%lld ",a[i]);
	    printf("\n");
	   }
	return 0;
}
```

[AC记录](https://codeforces.com/contest/1809/submission/217800658)

---

## 作者：Hooch (赞：3)

### 题意

你被给予两个整数 $n,k$。构造一个有 $n$ 个整数组成的序列 $a$ 满足：

- 所有 $a$ 中的元素值域为 $[-1000,1000]$ ; 
- $a$ 有刚好 $k$ 个子串的和为正数 ; 
- 剩下的 $ \dfrac{(n+1) \cdot n}{2}-k $ 个子串的和均为负数。

### 思路

可以将构造分为以下两种情况：

+ $k\le n$，我们可以将 $a$ 构造成 $[-1,\dots,-1,200,-400,-1,\dots,-1]$，这时 $200$ 是在第 $k$ 个位置，若 $k=0$，则数组中没有 $200$。$[1,k],[2,k],\dots,[k,k]$ 这些子串的和为正数，其它子串的和都为负数。

+ $k>n$，可以在 $a$ 数组的末尾放置一个 $1000$，如果前面的数不够大，则 $[1,n],[2,n],\dots,[n,n]$ 的子串都是正数，这时将构造任务转换为了一个子问题：构造 $n-1,k-n$ 时的序列，于是递归求解这个问题即可。

**将一个问题转换为子问题**是这道题的难点，也是很多构造题都会用到的，用处很大。

---

## 作者：六楼溜刘 (赞：2)

## 题意
- 给定 $n,k$，你要构造一个整数序列，使这个序列恰好有 $k$ 个子串的总和为正数，$\frac{n(n-1)}{2}-k$ 个子串的总和为负数 **（均不包括 $0$）**。
- 多组测试数据，$2 \leq n \leq 30,0\leq k \leq \frac{n(n-1)}{2}$，如果有多个解，输出任意一个。

## 题解

首先，我们看到这题有“子串求和”要素，自然地想到用前缀和将区间问题转化为数对问题，最后输出时输出差分即可。为方便叙述，我们用 $sum_i$ 代表这个前缀和序列的第 $i$ 项。

容易想到，我们必定可以构造一个满足条件的序列，使得：

- 它的某个长度为 $l$ 的前缀（$l$ 可以等于 $0$）的所有子串均为正（即 $sum_0$ 至 $sum_l$ 单调递增）。
- 以 $l+1$ 结尾的子串中恰有 $k-\frac{n(n-1)}{2}$ 个为正，其余为负（即在 $sum_0$ 至 $sum_l$ 中，有 $k-\frac{n(n-1)}{2}$ 个数严格小于 $sum_{l+1}$，其余的严格大于 $sum_{l+1}$）。
- 以大于 $l+1$ 的数结尾的所有子串均为负（即 $sum_{l+2}$ 至 $sum_n$ 单调递减，且所有数严格小于之前的那个前缀中所有数）。

另外，为了避免出现 $0$，我们可以把奇偶分开处理，前半段全用偶数，后半段全用奇数（或者暴力一点全用很小的负数），虽然这里我只提到了这种，但处理方法有很多，请读者自行思考。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=getchar())){if(c=='-')f=-1;}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=40,inf=0x3f3f3f3f;
int n,t,k,a[N];
signed main(){
    t=read();
    while(t--){
        n=read();k=read();
        int p=0;
        for(int i=1;i<=n;i++){
            if(k>=i){
                a[i]=i*2;
                k-=i;
            }else if(k!=0){
                a[i]=k*2-1;
                k=0;
            }else{
                a[i]=--p;
            }
        }
        for(int i=1;i<=n;i++){
            printf("%d ",a[i]-a[i-1]);//前缀和的差分即为原序列
        }
        puts("");
    }
}
```


---

