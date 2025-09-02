# K-th Not Divisible by n

## 题目描述

给定两个正整数 $n$ 和 $k$。求出第 $k$ 个不能被 $n$ 整除的正整数。

例如，如果 $n=3$，$k=7$，那么所有不能被 $3$ 整除的数为：$1,2,4,5,7,8,10,11,13 \ldots$ 在这其中的第 $7$ 个数字为 $10$。

## 样例 #1

### 输入

```
6
3 7
4 12
2 1000000000
7 97
1000000000 1000000000
2 1```

### 输出

```
10
15
1999999999
113
1000000001
1```

# 题解

## 作者：Allen_lml (赞：7)

	对于一个n来说，从1~（n-1）都是不被整除的，那么从（n+1）~（2n-1）同样不被整除，以此类推。
可知，在k不是（n-1）的倍数：
    
    1.如果k在1~n-1之间，则第k个数就是k本身。
    2.如果k在n~2n-2之间，则第k个数就是k+1。
    3.进而，经过m轮（n-1）个数，第k个不被n整除的数就是k+m。
那么，在k是（n-1）的倍数的时候呢:

	1.如果k是n-1，则第k个数还是k，也就是n-1。
    2.如果k是2（n-1），会发现第k个数是2n-1.
    3.归纳发现，当k是m*（n-1）时，第k个数就是mn-1.
现在可以写代码了
    
```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int t,n,k;

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int ans=0;
		scanf("%d%d",&n,&k);
		if(k%(n-1)!=0)//当k不是（n-1）的倍数时
		{
			ans=k/(n-1)+k;//k/(n-1)是第m轮，则第k个数就是k+m 
			printf("%d\n",ans);
			continue;
		}
		else//当k是（n-1）的倍数时
		{
			ans=k/(n-1)*n-1;//第k个数就是mn-1 
			printf("%d\n",ans);
			continue;	
		}
	}
	return 0;
}
```


---

## 作者：ADay (赞：5)

如果Markdown炸了可以来我的[博客](https://aday526.github.io/post/ti-jie-cf1352c-k-th-not-divisible-by-n/)阅读  

注:标题行过长是因为Markdown炸了，可以来我的博客↖阅读

求第$k$个不被$n$整除的数  
### Solution   




首先可以想到暴力枚举，但是看到数据范围，肯定会TLE.  
那么就得换一个思路了。  
我们按每个正整数对$n$除的**商和余**可以得到一个表格:  
| 1 | 2 | $\cdots$ | $n-1$ | $n$ |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $n+1$ | $n+2$ | $\cdots$ | $2n-1$ | $2n$ |
| $\cdots$ | $\cdots$ | $\cdots$ | $\cdots$ | $\cdots$ |
| $xn+1$ | $xn+2$ | $\cdots$ | $(x+1)n-1$ | $(x+1)n$ |
由于我们只要不被$n$整除的，那么就把最后一列去掉:  
| 1 | 2 | $\cdots$ | $n-1$ |
| -----------: | -----------: | -----------: | -----------: |
| $n+1$ | $n+2$ | $\cdots$ | $2n-1$ | 
| $\cdots$ | $\cdots$ | $\cdots$ | $\cdots$ | 
| $xn+1$ | $xn+2$ | $\cdots$ | $(x+1)n-1$ |   
现在就要求表格里的第$k$个数。不难发现，第$k$个数就在第$x=\left\lceil\dfrac{k}{n-1}\right\rceil$行第$y=(k-1) \bmod (n-1)
+1$列，那么这个数就是$n(x-1)+y$，直接计算即可  
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
 
inline void readint(int &x)//快读
{
    int f=1;x=0;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }
    x*=f;
}
 
int t,n,k;
 
inline int myceil(int x,int y){return x%y?x/y+1:x/y;}//x/y的向上取整
 
int main()
{
    readint(t);
    while(t--)
    {
        readint(n),readint(k);
        int x=myceil(k,n-1),y=(k-1)%(n-1)+1;//计算行列
        printf("%d\n",n*(x-1)+y);//输出答案
    }
    return 0;
}
```


---

## 作者：cherish_ (赞：4)

本题等价于有k瓶啤酒，n个啤酒瓶可以换一瓶啤酒，问最多可以喝几瓶啤酒（~~应该不会喝死吧~~）。

分k<n和k≥n讨论即可：第一种情况直接输出k，第二种情况我的思路是递推迭代。

参考代码：
```cpp
#include<bits/stdc++.h>
typedef long long ll;

ll t, n, k;

ll read() {
	char c = getchar();
	ll x = 0, f = 1;
	for (; !isdigit(c); c = getchar())
		if (c == '-')
			f = -1;
	for (; isdigit(c); c = getchar())
		x = x * 10 + c - 48;
	return x * f;
}

int main() {
	t = read();
	while (t--) {
		n = read(); k = read();
		if (k < n)//特判k<n的情况
			printf("%lld\n", k);
		else {
			ll a= k / n, mid=0;
			//mid表示喝掉a*n瓶后，还剩多少瓶
			mid = k - a * n + a;
			k += a;
			//循环，直到mid个瓶子不够换一瓶啤酒
			while (mid >= n) {
				a = mid / n;
				k += a;
				mid = mid - a * n + a;
			}
			printf("%lld\n", k);//输出
		}
	}
	return 0;
}
```


---

## 作者：do_while_true (赞：3)

每 $n$ 个数就会对 $k$ 造成 $n-1$ 的贡献，则我们看 $k$ 需要有多少组 $n$ 个数即可。

$$ans=k/(n-1)*n+k \bmod (n-1)$$

特别注意的是如果 $k$ 恰好为 $n-1$ 的倍数则还需要 $-1$。

另外特判两个情况:

1. $ans=k\ \ (k<n)$

1. $ans=k+1\ \ (k==n)$

[$\mathcal{Code}$](https://codeforces.com/contest/1352/submission/79520327)

---

## 作者：b6e0_ (赞：3)

打完CF又来写题解啦~求兹磁qwq（第一次AK CF比赛）

[CF题面传送门](https://codeforces.com/contest/1352/problem/C) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1352C) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1352C)

~~这题看标题就能看懂题意。~~

公式题。设第$k$个不能被$n$整除的数（即答案）为$x$。在$1$~$x$中，包含$k$个不能被$n$整除的数 和 若干个能被$n$整除的数。那么只需要求出有多少个能被$n$整除的数，再加上$k$，就能得到$x$。

不能被$n$整除的数中，每$n-1$个数就会出现一个能被$n$整除的数。所以我们设计出一个式子$k+k/(n-1)$。但是这个式子有些问题：如果$k$ $\bmod$ $(n-1)=0$，比如$n=3,k=4$。这时$x$为$5$而不是$6$。所以需要判断$k$ $\bmod$ $(n-1)$是否为$0$，为$0$时$-1$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,k;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		if(k%(n-1))//判断
			cout<<k+k/(n-1)<<endl;
		else
			cout<<k+k/(n-1)-1<<endl;
	}
	return 0;
}
```
时间复杂度为$O(t)$。

---

## 作者：H6_6Q (赞：2)

比赛的时候脑子糊了，简单结论题没想出来，最后乱搞了个二分过的（（          

### 思路：      
- 每次二分一个答案 $x$ 。

- 那么 $x$ 之前无法算进答案的数的个数显然是 $\lfloor  \frac{x}{n} \rfloor$

- 所以若答案是 $x$ ，则在它之前符合条件的数就是 $x -\lfloor  \frac{x}{n} \rfloor$ 

- 每次判断一下在它之前符合条件的数是否大于等于 $k$ 即可。

### Code：
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#define LL long long

using namespace std;

LL read()
{
	LL ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

LL t,n,k,ans,l,r;

int main()
{
	t=read();
	while(t--)
	{
		n=read();k=read();
		if(k<n)
			printf("%lld\n",k);
		else
		{
			l=1,r=1e18;
			while(l<=r)
			{
				LL mid=l+r>>1;
				if(mid-mid/n>=k)
				{
					ans=mid;
					r=mid-1;
				}
				else
					l=mid+1;
			}
			printf("%lld\n",ans);	
		}
		
	}
	return 0;
}
```


---

## 作者：Scrutiny (赞：1)

题意：求第$k$个不能被$n$整除的正整数。

显然，每连续$n$个正整数中有$n-1$个正整数不能被$n$整除。

于是我们分类讨论：

情况一：$n-1|k$

则有$\dfrac{k}{n-1}$个周期，每个周期长度为$n$，最后一个周期长度为$n-1$，答案为$\dfrac{k*n}{n-1}-1$。

情况二：$k\ mod\ (n-1)≠0$

则有$[\frac{k}{n-1}]$个周期，最后剩下$k\ mod\ (n-1)$个数，因此最后答案为$[\frac{k}{n-1}]*n+k\ mod\ (n-1)$

CODE:


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y;
int main(){
	std::ios::sync_with_stdio(0);
	cin>>n;
	for(register int i=1;i<=n;++i){
		cin>>y>>x;
		if(x%(y-1)){
			printf("%lld\n",x/(y-1)*y+x%(y-1));
		} 
		else{
			printf("%lld\n",x/(y-1)*y-1);
		}
	}
	return 0;
}

```


---

## 作者：novax (赞：1)

#### 题意

找第 $k$ 个不能被 $n$ 整除的数

#### 思路

这是一道数学题，每 $n$ 个数，就会有 $n-1$ 个不能被 $n$ 整除的数，则第 $k$ 个就是先计算前面有多少个 $n-1$，乘上 $n$，再加上 $k\%(n-1)$，也就是 $ k/(n-1) * n + k \% (n-1) $，就得到了答案。

需要注意的是，当 $k$ 恰好能被 $n-1$ 整除时，上面计算出来的答案还要再减1，因为此时 $k\%(n-1)$ 的结果是0，此时第n个不能被整除的数比 $k/(n-1) * n$ 还要小1

#### 代码如下
```cpp
#include <cstdio>
int main()
{
	long long N,t,k,c;
	scanf("%lld",&N);
	while(N--)
	{
		scanf("%lld%lld",&t,&k);
		c=k/(t-1)*t+k%(t-1);
		if(k%(t-1)==0) c--;
		printf("%lld\n",c);
	}
} 
```


---

