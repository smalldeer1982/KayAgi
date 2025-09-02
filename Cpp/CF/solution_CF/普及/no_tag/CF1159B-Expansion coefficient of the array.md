# Expansion coefficient of the array

## 题目描述

Let's call an array of non-negative integers $ a_1, a_2, \ldots, a_n $ a $ k $ -extension for some non-negative integer $ k $ if for all possible pairs of indices $ 1 \leq i, j \leq n $ the inequality $ k \cdot |i - j| \leq min(a_i, a_j) $ is satisfied. The expansion coefficient of the array $ a $ is the maximal integer $ k $ such that the array $ a $ is a $ k $ -extension. Any array is a 0-expansion, so the expansion coefficient always exists.

You are given an array of non-negative integers $ a_1, a_2, \ldots, a_n $ . Find its expansion coefficient.

## 说明/提示

In the first test, the expansion coefficient of the array $ [6, 4, 5, 5] $ is equal to $ 1 $ because $ |i-j| \leq min(a_i, a_j) $ , because all elements of the array satisfy $ a_i \geq 3 $ . On the other hand, this array isn't a $ 2 $ -extension, because $ 6 = 2 \cdot |1 - 4| \leq min(a_1, a_4) = 5 $ is false.

In the second test, the expansion coefficient of the array $ [0, 1, 2] $ is equal to $ 0 $ because this array is not a $ 1 $ -extension, but it is $ 0 $ -extension.

## 样例 #1

### 输入

```
4
6 4 5 5
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
0 1 2
```

### 输出

```
0```

## 样例 #3

### 输入

```
4
821 500 479 717
```

### 输出

```
239```

# 题解

## 作者：xu222ux (赞：7)

我的第一个想到的方法就是 $O(n^2)$ 的暴力：

预处理所有 $(i,j)$，算出所有 $(i,j)$ 所对应的 $k$ 值最大，取个 $\min$ 就可以了。

题目范围 $n<300000$，所以必须优化到 $O(n)$ 才行？

我发现，有些情况是可以不用看的。

第 $i$ 个点就只用看 $(i,n)$ 和 $(1,i)$ 这两种。

唯一特殊的就是 $(1,n)$，特判一下就好了。

这样的算法就优化到 $O(n)$ 了！

如果没看懂就看这个公式:

$ans = \left\{ \frac{\min(a_i,a_n)}{n-i},\frac{\min(a_1,a_i)}{i-1},\frac{\min(a_1,a_n)}{n-1}\right\} (1<i<n)$。


# 100 pts code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=min(a[1],a[n])/(n-1);
	for(int i=2;i<n;i++)ans=min(ans,min(min(a[n],a[i])/(n-i),min(a[1],a[i])/(i-1)));
	cout<<ans;
	return 0;
}

```

---

## 作者：QianianXY (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1159B)

## 题目分析

一道思想方法很好的简单题。

首先移项，将题目转换为求 $\dfrac{\min(a_i,a_j)}{|i-j|}$ （式子一）的最小值。

考虑暴力，$O(n^2)$ 枚举 $i,j$，更新答案。

考虑优化，不妨将 $min(a_i,a_j)$ 换成 $a_i$，则式子变为 $\dfrac{a_i}{|i-j|}$ （式子二）。

显然当 $j=1$ 或 $n$ 两者之一时式子二取最小值。（贪心）

因此只需枚举 $i$，总复杂度 $O(n)$ 即可求式子二最小值。

但其实求式子二的最小值，等价于求式子一的最小值，为什么呢？

式子一、二的区别在于，式子二中可能 $a_i >a_j$，此时两式子不等价。

但这没有关系，出现上述情况时，显然式子二的值不可能成为最小值。

而当 $a_i <a_j$ 时，显然上文中的贪心思路依然正确。

于是我们就成功地将 $O(n^2)$ 优化为 $O(n)$了。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 300010
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, ans = 1e9, a[N];

int main()
{
	read(n);
	for (rei i = 1; i <= n; i++) read(a[i]);
	for (rei i = 1; i <= n; i++) ans = min(a[i] / max(i - 1, n - i), ans);
	printf("%d", ans);
	return 0;
}
```


---

## 作者：ACtheQ (赞：4)

### 题意简述

给一个长度为 $n$ 的非负数列 $a_1,a_2,\dots,a_n$，找到最大的整数 $k$ 使对于任意 $1\le i,j\le n$，都有 $k\cdot\left|i-j\right|\le\min(a_i,a_j)$。


### 思路

先提供一种超时的方法，就是 $O(n^2)$ 寻找每一个 $i$,$j$,答案就等于 $\lfloor(\frac{\min(a_i,a_j)}{\left|i-j\right|}) \rfloor$ 中任意每个 $i$,$j$ 的最小值。

其实正解只需要在暴力解上做更改。

我们想求 $\lfloor(\frac{\min(a_i,a_j)}{\left|i-j\right|}) \rfloor$ 的最小值，其实就相当于求 $\left|i-j\right|$ 的最大值。

我们 $O(n)$ 查找 $i$，那么想让$\left|i-j\right|$ 最大，$j$ 就等于 $1$ 或 $n$。

其中要注意除数为 $0$ 的情况。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=300005;
int a[N];
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int ans=INT_MAX;
	ans=min(ans,min(a[1],a[n])/abs(1-n));
	for(int i=2;i<n;i++)
	{
		ans=min({ans,min(a[i],a[n])/abs(i-n),min(a[i],a[1])/abs(i-1)});
	}
	ans=min(ans,min(a[n],a[1])/abs(n-1));
	cout<<ans;
	return 0;
}
```

---

## 作者：szr666 (赞：4)

我这里推荐一下[我的博客](https://www.luogu.org/blog/szr666--blog/)

在博客里观看更美观哦~

[题目](https://www.luogu.org/problem/CF1159B)
------------

------------

华丽的分割线
# 解析

对于$k*\lvert i-j \rvert \le min(a_i,a_j)$,可化为
$k \le \frac{min(a_i,a_j)}{\lvert i-j \rvert}$

也就是说找到使这个值最小的$i,j$,则$k$等于这个值

因为$k$只能小于等于这个值,且$i,j$任意,所以转化为求最小值

对于每个点都可能成为最小值,所以我们枚举第$i$个点的值$a_i$

则一定能枚举到最小的$min(a_i,a_j)$,问题是求$\lvert i-j \rvert $

一个贪心策略是找到距离当前点最远的点即可

如果距离当前点次远,但权值远小于当前点和最远点的点来说

当枚举到那个点时,定会找到比之前距离更远的点

所以贪心策略是正确的

# 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
void read(int &x)
{
	x=0;
	int f;
	f=1;
	char c;
	c=getchar();
	while((c<'0'||c>'9')&&c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x=x*f;
}
int a[301000];
inline int min(int x1,int x2)
{
	return x1<x2 ? x1 : x2;
}
inline int max(int x1,int x2)
{
	return x1>x2 ? x1 : x2;
}
int main()
{
	int n,i,k;
	read(n);
	k=0x3f3f3f3f;
	for(i=1;i<=n;i++)
	{
		read(a[i]);
	}
	for(i=1;i<=n;i++)
	{
		k=min(k,a[i]/max(i-1,n-i));
	}
	printf("%d",k);
}
```




---

## 作者：sunkuangzheng (赞：1)

大型诈骗题，第一眼还感觉是二分 + ds（

考虑转化式子：

$$k \le \dfrac{\min(a_i,a_j)}{|i-j|}$$

我们枚举 $i$ 并假设 $a_i \le a_j$，若 $a_j \le a_i$ 则会在考虑 $j$ 的时候考虑这种情况。那么式子变成：

$$k \le \dfrac{a_i}{|i-j|}$$

然后你发现 $|i-j|$ 取最大时 $j=1$ 或 $n$，然后就做完了。

代码应该不需要放了吧（

---

## 作者：米奇 (赞：1)

## 思维题

首先化一下式子：

$$k \cdot|i-j| \leq \min \left(a_{i}, a_{j}\right)$$


$$k\leq \frac{\min \left(a_{i}, a_{j}\right)}{|i-j|}$$

假设每个数是最小的，那
```cpp
d=max(i-1,n-i);
m=read();
ans=min(ans,m/d);
```

为什么要取min呢，因为我们假设是最小的，其实可能不是最小的，所以要取min。

```cpp
#include<bits/stdc++.h>
using namespace std;
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}*/
#define gc getchar
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
int main()
{
	int n,m,d,ans=1e9;
	n=read();
	for(int i=1;i<=n;i++)
	{
		d=max(i-1,n-i);
		m=read();
		ans=min(ans,m/d);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1159B)  
## 题意简述
> 给定一个长度为 $n$ 的数列 $a$ ，试求出一个整数 $k$ ，使得 $k \cdot | i - j | \le \min(a_i,a_j)$  

## 开始解题！
首先化式子，将题目中式子的两端同时除以 $|i - j|$ ，得出如下式子：
$$k \le \frac{\min(a_i,a_j)}{|i - j|}$$  
然后我们将 $\min(a_i,a_j)$ 分类讨论。
1. $\min(a_i,a_j) = a_i$ ，则得： 
$$k \le \frac{a_i}{|i - j|}$$  
2. $\min(a_i,a_j) = a_j$ ，则得：
$$k \le \frac{a_j}{|i - j|}$$  

然后我们发现这两种情况可以合并。我们假设 $\min(a_i,a_j) = a_i$ ，那么就有： $a_j \ge a_i$ ，可得：
$$k \le \frac{a_i}{|i - j|}$$  
$$k \le \frac{a_j}{|i - j|}$$  

最后考虑化简 $|i - j|$， $|i - j|$ 中 $j = 1$ 或 $j = n$ 时其值最大。代码如下：
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=INT_MAX,a[300010];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        ans=min(ans,a[i]/max(i-1,n-i));
    }
    cout<<ans<<endl;
}
```

---

## 作者：sherry_lover (赞：0)

# CF1159B 题解

本人模拟赛的一道题。

~~个人感觉只有橙吧……~~

$k\left\vert i-j\right\vert \le \min(a_i,a_j)$ 相当于同时满足 $k\left\vert i-j\right\vert \le  a_i$ 和 $k\left\vert i-j\right\vert \le a_j$。所以对于每个 $i$，都有 $k \le \dfrac{a_i}{\max(j,\left\vert i-j\right\vert)}$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300005],x = 0x3f3f3f3f; 
int main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
		x = min(x,a[i]/max(n-i,i-1));
	}
	cout << x;
  	return 0;
}
```

---

