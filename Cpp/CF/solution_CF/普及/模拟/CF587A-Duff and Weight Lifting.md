# Duff and Weight Lifting

## 题目描述

Recently, Duff has been practicing weight lifting. As a hard practice, Malek gave her a task. He gave her a sequence of weights. Weight of $ i $ -th of them is $ 2^{w_{i}} $ pounds. In each step, Duff can lift some of the remaining weights and throw them away. She does this until there's no more weight left. Malek asked her to minimize the number of steps.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587A/ae0bf97f46f744ec67cd3653eed80d2fdb7f3472.png)Duff is a competitive programming fan. That's why in each step, she can only lift and throw away a sequence of weights $ 2^{a_{1}},...,2^{a_{k}} $ if and only if there exists a non-negative integer $ x $ such that $ 2^{a_{1}}+2^{a_{2}}+...+2^{a_{k}}=2^{x} $ , i. e. the sum of those numbers is a power of two.

Duff is a competitive programming fan, but not a programmer. That's why she asked for your help. Help her minimize the number of steps.

## 说明/提示

In the first sample case: One optimal way would be to throw away the first three in the first step and the rest in the second step. Also, it's not possible to do it in one step because their sum is not a power of two.

In the second sample case: The only optimal way is to throw away one weight in each step. It's not possible to do it in less than 4 steps because there's no subset of weights with more than one weight and sum equal to a power of two.

## 样例 #1

### 输入

```
5
1 1 2 3 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0 1 2 3
```

### 输出

```
4
```

# 题解

## 作者：wanggk (赞：3)

这道题让我想起了“2048”，有着异曲同工之妙。

-----

- 没错，我们的目标是“合成”数量尽可能少的 $2$ 的幂。

## 拿样例举栗子：

![CF587A-01-栗子](https://cdn.luogu.com.cn/upload/image_hosting/if0rhyas.png)

- 我们发现：**（偶数个） $m$ 个 $2$ 的 $x$ 次幂可以合成 $m/2$ 个 $2$ 的 $x+1$ 次幂**。

- 因此，可以**从小到大一层层地“合成”**，逐步合为奇数个、

- 好，现在来看奇数个，如果是 $3$ 个 $2$ 的  $x$ 次幂，还可以取出两个，合成 $x+1$ 次幂。结论进阶：**每个幂合成奇数个 -> 每个幂保留一个**

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ans=0;
int cnt[1000050];
int main()
{
	int w,mx=-1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w);
		cnt[w]++; mx=max(mx,w);
	}
	for(int i=0;i<=mx||cnt[i];i++)
	{
		if(!cnt[i]) continue;
		cnt[i+1]+=cnt[i]/2; cnt[i]%=2;//类似于进位
		if(cnt[i]) ans++;//已经往上面进位了但是还有遗留
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：hanzhongtlx (赞：1)

## [更好的阅读体验点这里](https://www.cnblogs.com/tlx-blog/p/12600747.html)
题目链接：[CF587A Duff and Weight Lifting](https://www.luogu.com.cn/problem/CF587A)           
~~我又来做$CF$水题刷咕值了~~   
我们可以考虑贪心，将尽可能多的$w$值合成一个，     
很容易发现，可以用$b_i$来代表值为$i$的$w$有多少个，然后从$1$开始扫，对$b_i$取$\log$。       
具体实现：      
容易发现若$\log b_i=x$，那么我们将$b_i$减去$x$，同时将$b_{i+x}$的值加$1$，如此循环，直至$b_i$为$1$或$0$，这样可以保证利益最大化。      
最后从$0$到最大值扫一遍，如果有取值就将答案$+1$。      
这样的复杂度是$\mathcal O(n)$，可以通过本题。            
毕竟是$A$题，实现起来就十分$naive$了，不过我码风有点毒瘤啊。 
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define MAXN 1000035
int n;
int b[MAXN]={0},a,maxn=0;
int g[30];
int log2(int x){return floor(log(x)/log(2));}
int main()
{
	#define read(x) scanf("%d",&x)
	read(n);
	g[0]=1;
	for(int i=1;g[i-1]<1000000;i++) g[i]=g[i-1]*2;
	for(int i=1;i<=n;i++) read(a),b[a]++,maxn=max(maxn,a);
	for(int i=0;i<=maxn;i++)
	{
		if(!b[i]) continue;
		int x;
		while(b[i]>1)
		{
			x=log2(b[i]);
			b[i+x]++;
			maxn=max(maxn,i+x);//有可能会出现新的最值，要注意
			b[i]-=g[x];
		}
	}
	for(int i=0;i<=maxn;i++) if(b[i]) b[maxn+1]++;
	return printf("%d\n",b[maxn+1]),0;
}
```
给个赞呗~

---

## 作者：ridewind2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF587A)

## 前言

这是一种一维的合成游戏。

## 题目大意

有一个共有 $n$ 个数的序列 $w$，若有 $k$ 个 $w$ 值满足存在一个数 $x$ 使得 $2_{}^{x}$ 为这 $k$ 个 $2_{}^{w}$ 的和，则这一组合是合法的，我们希望找到最小的组数 $m$，使这 $n$ 个 $w$ 组成 $m$个合法组合。

给出 $n$ 和 $w_{i}$，输出最小的 $m$。

## 思路
其实题目就是要求我们尽可能合成多次。

我们来举个例子：


```5 5 8 3 1 1 1 1```

然后会变成：

```6 8 3 2 2```

再合成：

```6 8 3 3```

最后一次：

```6 8 4```

所以答案是 $3$。

我们发现 $a$ 个 $2_{}^{x}$ 可以合成 $a \div 2$ 个 $2_{}^{x+1}$。

所以我们可以用一个 map 存每个数出现的次数。

$2_{}^{x}$ 合成时，$2_{}^{x+1}$ 会加上 $2_{}^{x}$ 出现的次数除以 $2$。所以，我们写出以下代码：

```cpp
int ans=0; 
	for(int i=0;i<=ma+1;i++){
		mp[i+1]+=mp[i]/2;
		ans+=mp[i]%2;
	}
```

## AC Code

```cpp

#include<bits/stdc++.h>
using namespace std;
map<int,int>mp;
int main(){
    int n,ma=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		mp[x]++;
		ma=max(ma,x);
	}
	int ans=0; 
	for(int i=0;i<=ma+1;i++){
		mp[i+1]+=mp[i]/2;
		ans+=mp[i]%2;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Graph_Theory (赞：0)

题意：一种横向的合成游戏。

思路：用一个桶存储每个数的数量，将每一对合成的新值放到对应的桶里，计算剩余的无法合成的。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a,bg[1005000],ans=0;
inline int read(){
	register int x = 0, t = 1;
	register char ch=getchar(); 
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			t=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48); 
		ch=getchar();
	}
	return x*t;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int a=read();
		bg[a]++;
	}
	for(int i=0;i<=1005000;i++)
	{
		bg[i+1]+=(bg[i]/2);//两两合成
		bg[i]%=2;//计算剩余的加到答案里
		ans+=bg[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
二进制裸题，正好用来练练手。

题意概述：给定 $n$ 个数 $w_i$ 令其每个数代表 $2^{w_i}$ 的重量，如果存在一个 $x$ 使得 $2^x$ 为某个区间内所有 $2^{w_i}$ 的和，则称其为合法的。请找出最小的 $m$ 来分割出 $m$ 个区间。
## 分析。
都是 $2$ 的正整数次幂，我们不妨从二进制入手。我们直接模拟二进制即可。因为每一个都是 $2$ 的整数次幂，所以直接相加减，去找到这个区间。两个比较低的位数可以合并成为一个比较高的位数，此时我们对于划分区间的问题就转换成了去判断每个二进制位是 $1$ 还是 $0$ 的问题了。显然，当位数为 $1$ 时说明一个区间已经满了，所以统计 $1$ 的个数就是答案。那么如何处理每一个 $w_i$ 呢？因为我们统计的是一个区间，所以直接进行桶计数即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
const int N=1e6+1000;
int n,w,a[N];
int ans;
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
int main(){
    read(n);
    for(int i=0;i<n;i++){
    	read(w);
        a[w]++;
    }
    for(int i=0;i<N-1;i++){
        ans+=a[i]&1;
        a[i]-=a[i]&1;
        a[i+1]+=a[i]>>1;
    }
    write(ans);
    return 0;
}
```
## 后记。
数组开的挺玄学的，为这个还吃了两发。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15769323.html)

较为简单，但还是因为细节问题挂了几发。![](//图.tk/o)

# 题目大意

有 $n$ 个数 $w_1,w_2,\cdots,w_{n-1},w_n$，若有 $k$ 个 $w$ 值满足存在一个数 $x$ 使得 $2^x$ 为这 $k$ 个 $2^w$ 的和，则这一组合是合法的，我们希望找到最小的组数 $m$，使这 $n$ 个 $w$ 组成 $m$ 个合法组合。     

给出 $n$ 和 $w_i$，输出最小的 $m$。

# 题目分析

我们可以一步一步从低次幂向高次幂合并，$k(k=2r \texttt{且 r 为整数})$ 个 $2^x$ 可以合并为 $\dfrac{k}{2}$ 个 $2^{x+1}$。

思路就出来了：

我们用一个桶 $t_x$ 来记录每个数值 $x$ 的个数。

但是如何记录答案呢？

我们发现上面只讨论了 $k$ 为偶数的情况，所以若 $k$ 为奇数，则取出 $\left\lfloor\dfrac{k}{2}\right\rfloor$ 个 $2^x$，剩下的 $1$ 个则保留。

---

坑点：

+ 因为更新是 $t[i+1]\gets t[i+1]+\dfrac{t[i]}{2}$，所以可能会一直向上迭代更新，边界不一定是 $i\le \max_w$。

+ 桶的大小要开到 $10^6+50$，我最初习惯性开成了 $10^6+5$，会 $\frak{Wrong~Answer~On~Test~36}$。

这是因为我们在向上时迭代时可能会不停向上更新，开到这儿就合适了。

# 代码

```cpp
//2022/1/5const int ma=1e6+50;

int t[ma]; 

int n;

int ans,maxx;

int main(void)
{
	n=read();
	
	for(register int i=1;i<=n;i++)
	{
		int x=read();
		
		t[x]++;
		
		maxx=max(maxx,x);
	}
	
	for(register int i=0;i<=maxx || t[i]!=0;i++)
	{
		if(t[i]!=0)
		{
			t[i+1]+=t[i]/2;
			
			if(t[i]%2==1)
			{
				ans++;
			}
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
```

---

