# [ARC127A] Leading 1s

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc127/tasks/arc127_a

整数 $ x $ を $ 10 $ 進表記した時，先頭に並ぶ $ 1 $ の個数を $ f(x) $ で表すことにします． 例えば，$ f(1)=1,f(2)=0,f(10)=1,f(11)=2,f(101)=1 $ です．

整数 $ N $ が与えられるので，$ f(1)+f(2)+\cdots+f(N) $ の値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{15} $
- 入力される値はすべて整数である

### Sample Explanation 1

$ f(2)=f(3)=\cdots\ =f(9)=0 $ です． 答えは，$ f(1)+f(10)+f(11)=4 $ です．

## 样例 #1

### 输入

```
11```

### 输出

```
4```

## 样例 #2

### 输入

```
120```

### 输出

```
44```

## 样例 #3

### 输入

```
987654321```

### 输出

```
123456789```

# 题解

## 作者：SkyLines (赞：3)

## Solution

### 赛时

设 $\sum_{i=l}^r f(i)$ 为 $g(l,r)$。

很明显可以暴力，枚举每个数字。很明显会 TLE。于是就输出了 $1 \le n \le 10^6$ 的答案：

[Link.](https://www.luogu.com.cn/paste/b1gnf0zo)

可以观察到：

在 $1 \le n \le 9$ 时，答案为 $1$。

在 $19 \le n \le 99$ 时，答案为 $12$。

在 $199 \le n \le 999$ 时，答案为 $123$。

在 $1999 \le n \le 9999$ 时，答案为 $1234$。

结论很显然，满足该条件的 $n$ 可以直接输出答案。

再考虑不满足该条件的 $n$，设 $n$ 有 $m$ 位，答案为 $g(1,10^{n-1}-1)+g(10^{n-1},n)$，$g(1,10^{n-1}-1)$ 可以通过之前的结论求出来。

接下来求 $g(10^{n-1},n)$ 即可。

对于形如 $11\dots$ 的数字，设 $p_1=10^{n-1}-1-8 \times 10^{n-2}$，如果 $n \ge p_1$（即 $n \ge 1199\dots$，其中 $1199\dots$ 的位数等于 $m$，省略号中的数字全为 $9$），则答案加上 $10^{n-2}$，否则加上 $10^{n-2}-(p_1-n)$。

对于形如 $111\dots$ 的数字，设 $p_2=10^{n-1}-1-8 \times 10^{n-2}-8 \times 10^{n-3}$，如果 $n \ge p_2$（即 $n \ge 11199\dots$，其中 $1199\dots$ 的位数等于 $m$，省略号中的数字也全为 $9$），则答案加上 $10^{n-3}$，否则加上 $10^{n-3}-(p_2-n)$。

形如 $1111\dots$，$11111\dots$ 等的数字也同理可得。

时间复杂度：$O(\log n)$。

### 赛时代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
ll n, tot = 1, ans, now, tmp, cc, anss;
int nw;
int main(){
	scanf("%lld", &n);
	for(int i = 1; i <= 18; i++){
		tot *= 10;
		if(tot > n){
			nw = i;
			break;
		}
	}
	cc = 1;
	for(int i = nw; i >= 1; i--){
		anss += cc * i;
		cc *= 10;
	}
	if(n >= 2 * (tot / 10) - 1){
		printf("%lld", anss);
		return 0;
	}
	ans = n - (tot / 10) + 1;
	tmp = tot / 100;
	now = 2 * (tot / 10) - 1;
	for(int i = nw - 2; i >= 0; i--){
		now -= 8 * tmp;
		if(n >= now){
			ans += tmp;
		}
		else{
			if(tmp - (now - n) >= 0) ans += tmp - (now - n);
		}
		tmp /= 10;
	}
	cc = 1;
	for(int i = nw - 1; i >= 1; i--){
		ans += cc * i;
		cc *= 10;
	}
	printf("%lld", ans);
	return 0;
}
```

### 其他分析

枚举前面连续 $1$ 的个数和剩下的位数，算出每个下界闭区间和上界开区间，输出答案即可。

时间复杂度：$O(\log^2 n)$。

---

## 作者：封禁用户 (赞：2)

看见题解区没有数位 dp 的做法，本蒟蒻就来一发。

这种问题几乎都可以用数位 dp 解决。

仿照 P2602 的做法，记 $len$ 为 $n$ 的长度，dfs 函数需要传递的参数有：当前是第几位（从个位向左数），前一位是否与原数的那一位相等，开头出现了几个连续的 $1$，连续的 $1$ 是否已经中断。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,l,num[21],dp[21][21];
ll dfs(int x,int one,int limit,int lx){
	if(!x)return one;
	if(!limit&&dp[x][one]!=-1)return dp[x][one];
	int maxc=limit?num[x]:9;ll ret=0;
	for(int i=0;i<=maxc;i++)ret+=dfs(x-1,one+(lx&&i==1),i==maxc&&limit,lx&&i==1);
	if(!limit)dp[x][one]=ret;
	return ret;
}int main(){
	memset(dp,-1,sizeof dp),cin>>n;
	while(n)num[++l]=n%10,n/=10;
	cout<<dfs(l,0,1,1);
	return 0;
}
```

但是这样有个问题，带前导零的情况无法计入，即只记录数字长度等于 $len$ 的部分的答案。

所以我们要处理数字长度不足 $len$ 的部分的答案。

比较直接的方法是枚举数字的长度，虽然慢一些，但是也能过。

进行下一次 dfs 之前记得清空记忆化数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,l,num[21],dp[21][21];
ll dfs(int x,int one,int limit,int lx){
	if(!x)return one;
	if(!limit&&dp[x][one]!=-1)return dp[x][one];
	int maxc=limit?num[x]:9;ll ret=0;
	for(int i=0;i<=maxc;i++)ret+=dfs(x-1,one+(lx&&i==1),i==maxc&&limit,lx&&i==1);
	if(!limit)dp[x][one]=ret;
	return ret;
}int main(){
	memset(dp,-1,sizeof dp),cin>>n;
	while(n)num[++l]=n%10,n/=10;
    ll ans=dfs(l,0,1,1);
	for(int i=l-1;i;i--)memset(dp,-1,sizeof dp),ans+=dfs(i,0,0,1);
	return cout<<ans,0;
}
```

---

## 作者：yangfengzhao (赞：1)

## 思路
>看到题解里没有这种思路，想来发一波。
---
首先，我们要知道一个函数 `sprintf`（在头文件 `<cstdio>` 中）。[^1]

他的原型是：
```cpp
inline int sprintf(char *_stream,char *format,...);
```
~~不就比 `printf` 多了几个参数吗……~~
1. `_stream` 参数：它是指你需要将**数据发送**的参数。比如一个数组。
2. `format` 和 `...` 参数：和 `printf` 没有区别。

那么就有了以下思路：
1. 输入上限 $N$。
2. 分治：使用 `sprintf` 函数将一个 `unsigned long long` [^2] 压入一个数组中。
3. 循环判断高位 $1$，然后用一个变量保存。
## 拾遗
[^1]:也可以用 `<iostream>` 头文件。
[^2]:使用 `ull` 是有原因的。题目说明 $1 \le N \le 10^{15}$（小于 `ull` 的最大值）。

---

## 作者：Lemon_zqp (赞：1)

### 思路
枚举前面 $1$ 的个数作为下界闭区间，再加上 $1$ 作为上界开区间，一直乘 $10$ 来获得新的上界和下界，需要注意边界条件 $n$ 和当前算的数要取一个最小值。
### 代码
```
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, an = 0, b = 0;
    cin >> n;
    for (int i = 1; i <= 16; i++)
    {
        b = b * 10 + 1;
        long long w = b, t = b + 1;
        for (int j = i; j <= 16 && w <= n; j++)
        {
            an += min(t, n + 1) - w;
            w *= 10;
            t *= 10;
        }
    }
    cout << an;
    return 0;
}
```


---

## 作者：听取MLE声一片 (赞：1)

可以数位 dp 但是没必要。

考虑转化，枚举开头连续 $1$ 的长度进行计算，这样同一个数会被枚举到多次，每次贡献 $1$，恰好和统计最高位开始连续的 $1$ 的个数每个数只贡献一次的结果相同。

枚举连续 $1$ 长度，考虑有多少数以它开头。设连续 $1$ 大小为 $x$，后面还有 $p$ 位，区间 $[x\times 10^p,(x+1)\times 10^p)$ 满足条件，右端点对 $n$ 取最小值计算，左端点比 $n$ 大时退出即可。这个通过枚举 $p$ 计算即可。

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
int n,ans,s;
signed main()
{
    n=read();
    for(int i=1;i<=17;i++){
    	s=s*10+1;
    	int l=s,r=s+1;
        for(int j=i;j<=17;j++){
        	if(l>n)
        		break;
        	int res=min(r-1,n)-l+1;
            ans+=res;
            l*=10;
            r*=10;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：james1BadCreeper (赞：1)

一个数的第一位是 $1$，能对答案产生贡献的数的区间是：

- $[1,2)$，
- $[10, 20)$，
- $[100, 200)$，
- ...


第二位是 $1$ 能对答案产生贡献的是：

- $[11,12)$，
- $[110,120)$,
- ...

枚举前面 $1$ 的个数作为下界闭区间，再加上 $1$ 作为上界开区间，不断乘 $10$ 来获得新的上下界，需要注意边界条件 $n$ 和当前算的数要取一个最小值。时间复杂度 $O(\log^2 n)$。


```cpp
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long i64;

int main(void) {
    i64 n, ans = 0, base = 0;
    scanf("%lld", &n);
    for (int i = 1; i <= 16; ++i) {
        base = base * 10 + 1;
        i64 w = base, t = base + 1;
        for (int j = i; j <= 16 && w <= n; ++j) {
            ans += (min(t, n + 1) - w);
            w *= 10, t *= 10;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：hlb44 (赞：0)

# 题目描述
给定正整数 $N$，需要计算从 $1$ 到 $N$ 的所有整数，在十进制表示下最高位连续 1 的个数之和。例如，对于数字 11 ，最高位连续 1 的个数是 2 ；对于数字 123 ，最高位连续 1 的个数是 1 。

# 解题思路
按数字位数分类讨论，分别计算每一位数中满足条件的数字对结果的贡献。

# 按位数分析
对于  $k$  位数  $k \geq 1$  ，其取值范围是  $ [10^{k-1}, 10^{k}-1] $  。我们重点关注最高位为 1 的子区间 $[10^{k-1}, 2 \times 10^{k-1}-1]$  。

# 具体步骤
· 枚举位数 $k$：从 1 开始，逐步增加位数，直到  $10^{k-1}>N$ 为止。

· 确定最高位为 1 的区间：对于当前位数 k，最高位为  1 的区间为 $10^{k-1}, \min \left(2 \times 10^{k-1}-1, N\right)$。

· 计算连续 1 的个数的贡献：分别计算连续 1 的个数为 1 到 $k$ 的数字个数，将其乘以对应的连续 1 的个数后累加到结果中。

# 代码
```cpp
#include <iostream>
using namespace std;

int main() {
	long long n,count=0,a=1;
	cin>>n;
	while(a<=n) {
		long long b=1;
		while(a*b<=n) {
			long long l=a*b,r=(a+1)*b;
			count+=min(r,n+1)-l;
			b*=10;
		}
		a=a*10+1;
	}
	cout<<count;
}
```

---

## 作者：xk2013 (赞：0)

题目传送门：[AT_arc127_a [ARC127A] Leading 1s](/problem/AT_arc127_a)

## 前置知识
- 拆贡献计算。

## 题意简述
本题给定正整数 $n$ 求 $\sum\limits_{i=1}^nf(i)$，其中 $f(i)$ 表示 $i$ 前导 $1$ 的个数。

## 解题思路
拆贡献，不难发现对于第 $i$ 位数，它的贡献区间为：
$$[11\times10^0, 11\times10^0+10^0),[11\times10^1,11\times10^1+10^1)\dots[11\times10^i,11\times10^i+10^i)$$

然后写代码就好了，注意下细节。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
#include <algorithm>
#include <cstdio>

typedef long long int ll;
ll n, ans, w;
bool flag = false;

int main(void)
{
	scanf("%lld", &n);
	
	for (int i = 1; i <= 16; i++) // 从低到高枚举位数
	{
		w = w * 10 + 1;
		
		ll l = w, r = l + 1;
		
		for (int j = i; j <= 16 && l <= n; j++, l *= 10, r *= 10) // 计算贡献
		{
			ans += std::min(r, n + 1) - l;
		}
	}
	
	printf("%lld", ans);
	return 0;
}

```
----------------------
这是本五年级蒟蒻小学生的第 22 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2025/01/11：初版。

---

## 作者：封禁用户 (赞：0)

大家可以去看看[这位大佬的题解](https://www.luogu.com.cn/article/jab7127y)，通过观察，可以发现其中满足前导 $1$ 的区间有以下 $2$ 个特点：
1. 每一个区间都是左闭右开。
2. 每一类的第一个区间的左端点都是 $1$，右端点比左端点大 $1$。

所以对于一类区间，假设描述的是有 $x$ 个前导 $1$ 的数字，那么第一个区间 $\left [ l,r \right ] $ 左端点 $l=11 \dots 1$（一共 $x$ 个 $1$），$r=l+1$。

枚举前面 $1$ 的个数作为下界闭区间，再加上 $1$  作为上界开区间，不断乘 $10$ 来获得新的上下界，需要注意边界条件 $n$ 和当前算的数要取一个最小值即可。

### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,msk,ans;
int main(){
	cin>>n;
	for(int i=1;i<=16;i++){
		msk=msk*10+1;
		long long s1=msk,s2=s1+1;
		for(int j=i;j<=16&&s1<=n;j++){
			ans=ans+min(s2,n+1)-s1;
			s1*=10,s2*=10;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：TLEWA (赞：0)

题目要求求出 $\sum_{i=1}^{n} f\left ( i \right )$，在 $n \le 10^{16}$ 的数据范围下硬算是不可能的，考虑对每一位数产生的贡献分别计算。对于从低到高第 $1,2$ 位数，它们可以产生贡献的区间分别为：

$$ \left [ 1,2 \right ),\left [ 10,20 \right ),\left [ 100,200 \right ), \cdots  $$

$$ \left [ 11,12 \right ),\left [ 110,120 \right ),\left [ 1100,1200 \right ), \cdots  $$

对于第 $i$ 位数，设 $\sum_{j=0}^{i-1}$ 为 $k$，它可以产生贡献的区间为：

$$\left [ k,k+10^0 \right ),\left [ k \times 10^1 ,k+10^1 \right ),\left [ k \times 10^2,k+10^2 \right ), \cdots$$

我们只需要对于每一位数，分别计算其到 $n$ 时可以产生贡献的区间长度，最后将其累加起来就是答案。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n;
long long ans,start,len;

int main() {
	cin >> n;
	for(int i=1;i<=16;++i) { //枚举16个位的贡献情况 
		start=start*10+1; //各个位可以获得贡献的第一个数字区间的开头(1,11,111,1111,11111.......)
		if(start>n) break;
		long long len=1,start2=start/*这一位的每个数字区间的开头*/;
		for(int j=1;start2<=n;start2*=10,len*=10) {
			ans+=min(start2+len-1,n)/*可以产生贡献的右边界 */-start2+1; //右边界-左边界+1 
		}
	} 
	cout << ans;
	return 0;
}

```


---

## 作者：Piggy343288 (赞：0)

在 HL 群里吃瓜，顺手写一篇题解。  

第一眼必定是数位 dp，可是这会使原题难度反而升高了。相对而言，我们要是枚举前缀 $1$ 的长度，然后寻找对答案有贡献的区间，此问题是很容易的。同时我们不难发现，前缀 $1$ 长度为 $l$ 的所有有贡献的数字即为 $\forall i\in[l,16],(\sum_{i=0}^l10^i)\times10^{16-l}\sim (2+\sum_{i=1}^l10^i)\times10^{16-l}$。枚举计算即可。  

代码没几行，不放了。注意前边那一大堆式子本质上是一堆连续的 $1$，因此可以迭代计算而不用每次重新计算。


---

## 作者：YuYuanPQ (赞：0)

# 洛谷 AT_arc127_a 题解

## 题目大意

当用十进制表示整数 $x$ 时，最高位开始连续的 $1$ 的个数用 $f[x]$ 表示。

给出了整数 $n$，求 $\sum_{n=1}^i f[i]$。

- $n \le 10^{15}$

~~从题面上直接复制的，因为很简练。~~

## 赛时

~~可以跳过不看。~~

看数据范围就知道不是暴力。

但赛时题面出了问题，范围是 $1\ \leq\ N\ \leq\ 10^{5}$。

当时同学说应该是 $1\ \leq\ N\ \leq\ 10^{9}$。

于是开打暴力，为了过 $10^{9}$ 规模的数据，加了点分段打表。

结果改成了 $1\ \leq\ N\ \leq\ 10^{15}$。

好好好，我看看。

一共打了大概 $1$ 个小时之后，我放弃了。

~~太菜了，没想到~~

赛时代码扔在了最后面。

## 分析

思维题。

题面的 “最高位开始连续的 $1$” 启发了我。

枚举两个值 $i$ 和 $j$。

$i$ 表示前面有连续的 $i$ 个 $1$。

$j$ 表示剩下的位数。

再算出左端点和右端点，每次更新。

考完总结，发现：其实在分段打表的时候，我也想过分 $2$ 段枚举什么值来算，可是就是没想出来。

实在不懂请看代码中的注释。

## 注意事项

- 开 `long long`。$k$ 在乘的时候会溢出。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
int n,k;
ll ans;
int qread()
{
	int sum=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){sum=(sum<<1)+(sum<<3)+ch-48;ch=getchar();}
	return sum*f;
}
void qprint(int x)
{
	if(x>9) qprint(x/10);
	putchar(x%10+48);
	return;
}
void qp(int x)
{
	if(x<0) x=-x,putchar('-');
	qprint(x);
	return;
}
void qprintll(ll x)
{
	if(x>9) qprintll(x/10);
	putchar(x%10+48);
	return;
}
void qpll(ll x)
{
	if(x<0) x=-x,putchar('-');
	qprintll(x);
	return;
}
int my_min(int x,int y){return x<y?x:y;}
signed main()
{
    n=qread();
    for(int i=1;i<=17;i++)//其实到15好像也可以，这里是指0的个数（10的i次方）。
    {
    	k=k*10+1;
    	int l=k,r=k+1;
        for(int j=i;j<=17;j++)
        {
        	if(l>n) break;//如果左端点大了，退出。
            int ed=my_min(r-1,n);//右端点
            int st=(l-1);//左端点
        	int sum=ed-st;//贡献
            ans+=sum;
            l*=10;//得到新的左端点
            r*=10;//得到新的右端点
        }
    }
    qp(ans);
    putchar('\n');
    return 0;
}
```
## 赛时代码

```cpp
#include<bits/stdc++.h>
#define INF pow(2,31)-1
#define ll long long
#define MAXN 520
#define int long long
using namespace std;
int n;
ll ans,len;
int nws;
int zj;
int ten[MAXN];
int db[MAXN]={1,2,13,124,1235,12346,123457,1234568,12345679,123456790};
int q[MAXN];
int dy[MAXN]={0,0,123456789,123456789,123456789,123456789,123456789,123456789,123456789,123456789,123456790};
short c[MAXN];
int qread()
{
	int sum=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){sum=(sum<<1)+(sum<<3)+ch-48;ch=getchar();}
	return sum*f;
}
void qprint(int x)
{
	if(x>9) qprint(x/10);
	putchar(x%10+48);
	return;
}
void qp(int x)
{
	if(x<0) x=-x,putchar('-');
	qprint(x);
	return;
}
void qprintll(ll x)
{
	if(x>9) qprintll(x/10);
	putchar(x%10+48);
	return;
}
void qpll(ll x)
{
	if(x<0) x=-x,putchar('-');
	qprintll(x);
	return;
}
void solve()
{
    /*do
    {
        /*int j=n;
        while(j!=0)
        {
            if((j%10)!=1) break;
            else ans++;
            //if(j%10==1) ans++;
            j/=10;
        }
        cout<<n<<" "<<ans<<endl;
        len=0;
        int j=n;
        int k=ans;
        while(j!=0)
        {
            c[++len]=j%10;
            j/=10;
        }
        int t=len;
        while(c[t]==1) ans++,t--;
        //cout<<ans-k<<endl;
    }while(n--);*/
    return;
}
void get_nws()
{
    int p=n;
    while(p)
    {
        p/=10;
        nws++;
    }
    return;
}
void get_zj()
{
    zj=pow(10,(nws-1));
    //cout<<zj<<endl;
    return;
}
int my_min(int x,int y){return x<y?x:y;}
void _add3(int x)
{
    int j=0,k=x;
    while(k<=n)
    {
        j=k;
        len=0;
        while(j!=0)
        {
            c[++len]=j%10;
            j/=10;
        }
        int t=len;
        while(c[t]==1) ans++,t--;
        k++;
    }
    return;
}
void _add2()
{
    int b=2e8,ja=1e8;
    int t=2;
    while(b<=n)
    {
        t++;
        b+=ja;
    }
    t--;
    ans=dy[t];
    int x=t*1e8;//te8;
    _add3(x);
    return;
}
void _add(int x)
{
    int j=0,k=pow(10,x-1)+1;
    //cout<<k<<endl;
    int zz=my_min(n,1e8);
    while(k<=zz)
    {
        j=k;
        len=0;
        while(j!=0)
        {
            c[++len]=j%10;
            j/=10;
        }
        int t=len;
        while(c[t]==1) ans++,t--;
        //cout<<ans-k<<endl;
        k++;
    }
    if(n>1e8)
    {
        _add2();
    }
    return;
}
void get_ans()
{
    if(n>=1e8)
    {
        _add2();
        return;
    }
    int i=0,z=1;
    for(;i<9,z<=zj;i++,z*=10)
    {
        //if(z>zj) break;
        //ans+=db[i];
        //z*=10;
    }
    ans+=db[i-1];
    //cout<<ans<<endl;
    _add(i);
    //cout<<i<<endl;
    //cout<<ans<<endl;
    return;
}
void get_ten()
{
    for(int i=0;i<10;i++) ten[i]=pow(10,i);
    return;
}
void print_ten()
{
    for(int i=0;i<=9;i++) cout<<ten[i]<<" ";
    cout<<endl;
    return;
}
signed main()
{
	//freopen("my.in","r",stdin);
	//freopen("my.out","w",stdout); 
    get_ten();
    //print_ten();
    n=qread();
    //solve();
    get_nws();
    get_zj();
    get_ans();
    qpll(ans);
    putchar('\n');
    return 0;
}
```

## 附

- [题目链接](https://www.luogu.com.cn/problem/AT_arc127_a)
- [我的提交记录](https://www.luogu.com.cn/record/list?pid=AT_arc127_a&user=1029900)

---

