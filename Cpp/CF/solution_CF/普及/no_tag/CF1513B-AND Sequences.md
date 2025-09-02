# AND Sequences

## 题目描述

一个 $n$ 个数的非负数组如果 $\forall i\in\left[1,n\right)$ ，有 $a_1$ & $a_2$ & $……$ & $a_i = a_{i+1}$ & $a_{i+2}$ & $……$ & $a_n$ ，那么这个数组叫做 $“$ 好的数组 $”$ 。其中&表示按位与。

给定一个长度为 $n$ 的数组，求这个数组有多少种排列是 $“$ 好的数组 $”$ 。因为这个数字可能很大，所以输出结果模 $10^9+7$ 即可。

两个排列不同，指这个排列有一个位置的数与其他排列的这一位置的数的下表不同。

例如：

如果原数组是 $1,1$ ，那么这个数组有 $2$ 个排列；

如果原数组是 $1,1,1$ ，那么这个数组有 $6$ 个排列。

## 样例 #1

### 输入

```
4
3
1 1 1
5
1 2 3 4 5
5
0 2 0 3 0
4
1 3 5 1```

### 输出

```
6
0
36
4```

# 题解

## 作者：gaozitao1 (赞：4)

**题目大意**：给定一个数组，求有多少种排列是好的数组。

好的数组是指  $\forall i\in\left[1,n-1\right]$，有 $a_1\ \&\ a_2\ \&\ \cdots\ \&\ a_i=a_{i+1}\ \&\ a_{i+2}\ \&\ \cdots\ \&\ a_n$。

我们可以寻找一些规律：

当 $i=1$ 时， $a_1=a_2\ \&\ a_3\ \&\ \cdots\ \&\ a_n$。

如果把左右两边都加上 $\&\ a_1$，那么就变成了：$a_1=a_1\ \&\ a_2\ \&\ a_3\ \&\ \cdots\ \&\ a_n$。

当 $i=n$ 时， $a_n=a_1\ \&\ a_2 \&\ \cdots\ \&\ a_{n-1}$。

如果把左右两边都加上 $\&\ a_n$，那么就变成了：$a_n=a_1\ \&\ a_2\ \&\ a_3\ \&\ \cdots\ \&\ a_n$。

如果设 $a_1\ \&\ a_2\ \&\ a_3\ \&\ \cdots\ \&\ a_n=b$，那么 $a_1$ 和 $a_n$ 一定都等于 $b$。

当 $i=2$ 时， $a_1\ \&a_2=a_3\ \&\ a_4 \&\ \cdots\ \&\ a_n$。

如果把左右两边都加上 $\&\ a_1\ \&\ a_2$，那么就变成了：$a_1\ \&\ a_2=a_1\ \&\ a_2\ \&\ a_3\ \&\ \cdots\ \&\ a_n$。

因为 $a_1=a_1\ \&\ a_2\ \&\ a_3\ \&\ \cdots\ \&\ a_n$，所以不管 $a_2$ 等于多少，上式都成立。

同理，$a_3,a_4,\cdots,a_{n-1}$ 无论等于多少就可以。

所以，就可以找到构造好的数组的方法：将数组的第一个数和最后一个数都是 $b$ ，其他的数随便放就可以。

计算出数组中等于 $a_1\ \&\ a_2\ \&\ a_3\ \&\ \cdots\ \&\ a_n$ 的数的个数为 $c$ ，那么这 $c$ 个数找两个放到数组的开头和结尾，有 $c\times\left(c-1\right)$ 种方法。还剩下 $n-2$ 个数，放到 $n-2$ 个位置，有 $\left(n-2\right)\ !$ 种方法。所以，总共就有 $c\times\left(c-1\right)\times\left(n-2\right)\ !$ 种方法。

**代码：**
```cpp
#include<cstdio>
#include<iostream>
int a[200001];
int main()
{
	int b,c(0),d,i,n,t;
	scanf("%d",&t);
	while(t)
	{
		scanf("%d",&n);
		for(i=1; i<=n; ++i)
			scanf("%d",&a[i]);
		b=a[1];
		for(i=2; i<=n; ++i)
			b&=a[i];//找到数组第一个和最后一个数
		c=0;
		for(i=1; i<=n; ++i)
			if(a[i]==b)
				++c;//统计有多少个数可以放到第一个和最后一个
		d=1ll*c*(c-1)%1000000007;
		for(i=1; i<n-1; ++i)//求(n-2)！
			d=1ll*d*i%1000000007;
		//注意乘1ll，或者开long long
		//注意取模
		printf("%d\n",d);
	}
	return 0;
}
```

---

## 作者：Mophie (赞：4)

首先先思考一下这个 “AND Sequences” 到底是个啥。

先看这两个式子：

$a_1=a_2\&a_3\cdots\&a_n$

$a_n=a_1\&a_2\cdots\&a_{n-1}$

因为左右都相等，我们将右边的数与上左边的数试试。

$a_1=a_1\&a_2\cdots\&a_n$

$a_n=a_1\&a_2\cdots\&a_{n}$

那么左右端点的数就确定了。设$a_1\&a_2\cdots\&a_{n}=k$

然后再发现一个结论：每次往左边减少一个数，往右边加一个数，**因为式子的值已经是所有数的并，并且都包含他们的并**

也就是说因为包含了左右端点，所以每次加上的时候都必然大于等于 $k$ 且小于等于 $k$，所以只要做好了左右端点就必然是一个合法的序列。

设等于 $k$ 的数有 $x$ 个，那么答案就是 $x(x-1)(n-2)!$

```cpp
//红太阳zhouakngyang txdy!
#include<bits/stdc++.h>
using namespace std;
//#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
const int mod=1e9+7;
int taxi,n,a[200009],res,cnt;
long long ans=1;
int main()
{
	taxi=read();
	for(int ttt=1;ttt<=taxi;ttt++)
	{
		n=read();
		cnt=0;ans=1;
		for(int i=1;i<=n;i++)a[i]=read();res=a[1];
		for(int i=2;i<=n;i++)res=(res&a[i]);
		for(int i=1;i<=n;i++)
			if(a[i]==res)cnt++;
		ans=ans*cnt*(cnt-1)%mod;
		for(int i=1;i<=n-2;i++)ans=ans*i%mod;
		printf("%lld\n",ans);
	}
	return 0;
}


```


---

## 作者：Super_Cube (赞：1)

# Solution

由题知：$a_1=a_2\ \&\cdots\&\ a_n$，$a_n=a_1\ \&\cdots\&\ a_{n-1}$，两边同时进行与运算等式仍然成立，所以有：$a_1=a_n=a_1\ \&\cdots\&\ a_n$。

设 $s=a_1\ \&\cdots\&\ a_n$，统计 $a_i=s$ 的个数为 $c$，只有这些数能放在开头与结尾，方案为 $c(c-1)$。

现在关注 $a_2$ 的取值，有 $a_1\ \&\ a_2=a_3\ \&\cdots\&\ a_n$，两边同时进行与运算等式仍然成立，所以有：$a_1\ \&\ a_2=s$，而又因为 $a_1=s$，且 $s$ 中包含了 $a_2$，于是任意的 $a_2$ 都成立。同理其余位置也一样。

那么剩下的 $n-2$ 个数可以任意排列，方案为 $(n-2)!$。所以最终答案为 $c(c-1)(n-2)!$。

---

## 作者：Jayun (赞：1)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF1513B)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/15575410.html)

# 题目大意：

求 $a$ 有多少排列使得 $\forall i\in\left[1,n\right)$ ，有 $\bigwedge\limits_{j=1}^ia_j=\bigwedge\limits_{j=i+1}^na_j$。

# 思路：

对于 $i=1$ 的情况，即 $a_1=\bigwedge\limits_{j=2}^na_j$，可以看出，每个合法的排列至少有两个数使得它们是整个排列的逻辑和，并且它们都在整个排列的两端，即 $1,n$ 两点。

由此我们可以先找出 $a$ 的逻辑和在 $a$ 中的个数 $m$，答案即 $\dbinom{n}{m}\times (n-2)!$。

# 代码：

```cpp
const int N = 2e5 + 10;
const ll mod = 1e9 + 7;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int t, n;
ll a[N], cnt;

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	for (t = Read(); t--; ) {
		n = Read(); cnt = 0; 
		ll b = (1ll << 32) - 1;
		for (int i = 1; i <= n; i++) a[i] = Read(), b &= a[i];
		for (int i = 1; i <= n; i++)
			if (a[i] == b) cnt++;
		if (cnt <= 1) { puts("0"); continue; }
		ll ans = cnt * (cnt - 1) % mod;
		for (int i = 1; i <= n - 2; i++) ans = ans * i % mod;
		printf ("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：naroto2022 (赞：0)

# CF1513B 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1513B)

### 题意

给定一个数组 $a$，问在 $a$ 中有多少种排列满足对于任意 $i(i\in[1,n))$ 有 $a_1\&a_2\&a_3\&\cdots\&a_i=a_{i+1}\&a_{i+2}\&a_{i+3}\&\cdots\&a_n$。

### 前置知识

1. 位运算，知道与运算是两者都为真则为真，两者有一者为假则为假，并能推出 $a\&a=a(a\in\mathbb{N})$。

### 思路

不妨设 $cnt=a_1\&a_2\&a_3\&\cdots\&a_n$。

依题，$a_1=a_2\&a_3\&a_4\&\cdots\&a_n$；

两边同时与上 $a_1$，则有 $a_1=cnt$。

依题，$a_1\&a_2\&a_3\&\cdots\&a_{n-1}=a_n$；

两边同时与上 $a_n$，则有 $a_n=cnt$。

依题，$a_1\&a_2=a_3\&a_4\&a_5\&\cdots\&a_n$，

两边同时与上 $a_1\&a_2$，则有 $a_1\&a_2=cnt$。

已知 $a_1=cnt$，所以 $a_2$ 可以为任意数。

同理，$a_3,a_4\cdots,a_{n-1}$ 也可以为任意数。

于是，问题就转化为，给定一个数组 $a$，求有多少种排列满足首位均为 $cnt$。

于是再设 $num$ 为 $a$ 数组中等于 $cnt$ 的个数。

于是首位两个是定的，有小学学过的组合知识，首位的方案数为 $num\times(num-1)$，而中间排列的方式为 $(n-2)!$。

故，答案为 $num\times(num-1)\times(n-2)!$。

### 代码

```cpp
#include<iostream>
#include<cstdio> 
#include<algorithm>
#include<cstring>
#include<cmath>
#define mod 1000000007
using namespace std;
long long n,a[200005],T,num,cnt,ans;
//cnt为a1^a2^a3^...^an
//num为a数组中与cnt相同的个数 
int main(){ 
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		cnt=0;num=0;//初始化 
		for(int i=1; i<=n; i++){
			scanf("%lld",&a[i]);
			if(i>1) cnt&=a[i]; 
			else cnt=a[i];
		}
		for(int i=1; i<=n; i++) if(a[i]==cnt) num++;
		ans=(num-1)*num%mod;
		for(int i=1; i<=n-2; i++) ans=ans*i%mod;;//计算(n-2)!
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

