# Interesting Sum

## 题目描述

You are given an array $ a $ that contains $ n $ integers. You can choose any proper subsegment $ a_l, a_{l + 1}, \ldots, a_r $ of this array, meaning you can choose any two integers $ 1 \le l \le r \le n $ , where $ r - l + 1 < n $ . We define the beauty of a given subsegment as the value of the following expression:

$$\max(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n}) - \min(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n}) + \max(a_{l}, \ldots, a_{r}) - \min(a_{l}, \ldots, a_{r}). $$

Please find the maximum beauty among all proper subsegments.

## 说明/提示

In the first test case, the optimal segment is $ l = 7 $ , $ r = 8 $ . The beauty of this segment equals to $ (6 - 1) + (5 - 1) = 9 $ .

In the second test case, the optimal segment is $ l = 2 $ , $ r = 4 $ . The beauty of this segment equals $ (100 - 2) + (200 - 1) = 297 $ .

## 样例 #1

### 输入

```
4
8
1 2 2 3 1 5 6 1
5
1 2 3 100 200
4
3 3 3 3
6
7 8 3 1 1 8```

### 输出

```
9
297
0
14```

# 题解

## 作者：Hisaishi_Kanade (赞：5)

### 一、题意

英文题面也大致能看懂，翻译也很清楚了，不多赘述。

### 二、思路

纯纯的诈骗题。

首先很显然想到使用线段树、树状数组、ST表之类的维护区间最值，然后暴力找 $l,r$，求最小值。

单次时间复杂度是 $O(n\log n+n^2)$，显然无法通过。 

思考正解，要让原式最大，就要让两个 $\max$ 得到的值最大，$\min$ 得到的值最小。

什么最大？什么最小？当然是最大、次大、最小、次小这四个值！

这时有人要问了：你怎么保证一定能把这四个值分成符合条件的两组呢？

干脆枚举，简洁明了。设最大、次大、最小、次小分别是 $a,b,c,d$。

+ $abcd$，可以变成 $a|bc|d$。
+ $abdc$，可以变成 $a|bd|c$。
+ $adbc$，可以变成 $|ad|bc$。
+ $\cdots$

这说明了我们的猜想是正确的（实际上这就是分割一个环）。

就这样得到最优的 $O(n)$ 做法，输出 $a+b-c-d$ 即可。

---

## 作者：wzmzmhk (赞：4)

题目描述：求出 $\max(\max(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n}) - \min(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n}) + \max(a_{l}, \ldots, a_{r}) - \min(a_{l}, \ldots, a_{r}))$，其中 $l$ 和 $r$ 是满足 $1 \le l \le r \le n$ 的任意整数。

令最大数为 $a$，次大数为 $b$，最小数为 $c$，次小数为 $d$。

我们发现，这四个数不管怎么排列，都至少有一组 $[l, r]$，满足 $a$ 或 $b$ 在该区间内，同时 $c$ 或 $d$ 在该区间内。

那么此时，根据需要求的式子，答案就是 $a + b - c - d$。

每一组数据可以先排序，复杂度 $O(n\log n)$，也可以用打擂法，复杂度 $O(n)$。

```cpp
for (int i = 1; i <= n; i++) {
    if (a[i] >= Max) Max = a[i], I = i;
    if (a[i] <= Min) Min = a[i], J = i;
}
int nMax = -INF, nMin = INF;
for (int i = 1; i <= n; i++) {
    if (i != I && a[i] >= nMax) nMax = a[i];
    if (i != J && a[i] <= nMin) nMin = a[i];
}
cout << Max + nMax - Min - nMin << endl;
```        

---

## 作者：CSP_Sept (赞：3)

可能是生涯最后一场 cf 了，$+47$。

## 大意

给定长度为 $n$ 的数列 $a$，要求出

$$
\max\limits_{1\le l\le r\le n}\left\{\max_{l\le i\le r}\{a_i\}-\min_{l\le i\le r}\{a_i\}+\max_{1\le i<l\lor r<i\le n}\{a_i\}-\min_{1\le i<l\lor r<i\le n}\{a_i\}\right\}
$$

$4\le n\le 10^6$，$1\le a_i\le 10^9$。

## 题解

记 $s,t$ 分别表示最小值与次小值，$\mathscr{A,S}$（分别是「最大值」与「次大值」日语罗马音的第二个字符）分别表示最大值与次大值。

大可以观察样例，发现答案都形如 $\mathscr A+\mathscr S-s-t$（可以结合「样例解释」判断）。

不用观察样例也能发现，不考虑**区间**的限制，我们能得到的最大值，当且仅当两部分的最大值为 $\mathscr{A,S}$，最小值为 $s,t$。因为这样得到的两个「差值」是最大的。

注意：这里我们用「差值」刻画了 $[l,r],[1,l)\cup(r,n]$ 两个集合内的最大值与最小值的差。容易发现，题目所求即为两个「差值」和的最大值。

没错，这也就是考虑了区间后的结论，下面我们证明它。

**【结论】** 答案必定为 $\mathscr A+\mathscr S-s-t$，下面记作 $ans$。

**【证明】** 分两种情况讨论：

**$\textbf{1. }$ $\mathscr{A,S}$ 均在 $s,t$ 的一侧，这里以左侧为例。**

考虑以 $M$ 代替 $\mathscr{A,S}$，$m$ 代替 $s,t$。这样的话，只要我们两个「差值」都形如 $M-m$，那么将能得到 $ans$。留作习题。

那么序列将形如：

$$
M\ \ldots\ \underline{M\ \ldots\ m}\ \ldots\ m
$$

显然地，这里我们以下划线部分作为 $[l,r]$，可以使得两个「差值」均形如 $M-m$（因为最小值不可能比 $m$ 小而最大值不可能比 $M$ 大）。

括号里的文字阐述了抽象的原因，留作习题。

**$\textbf{2. }$ $\mathscr{A,S}$ 分布在 $s,t$ 的两侧。**

序列将形如：

$$
\underline{M\ \ldots\ m}\ \ldots\ m\ \ldots\ M
$$

以下划线部分作为 $[l,r]$。

**$\textbf{3. }$ $\mathscr{A,S},s,t$ 中的 $M,m$ 交替排列。**

序列将形如：

$$
\underline{M\ \ldots\ m}\ \ldots\ M\ \ldots\ m
$$

以下划线部分作为 $[l,r]$。

___

以上的所有便是证明的全部过程，我们上面疏漏的情况均可以将上面的 $M,m$ 交换得到。

容易发现这样得到的 $\textbf1',\textbf2',\textbf3'$ 与 $\textbf1,\textbf2,\textbf3$ 正确性一致，留作习题。

___

于是我们证明了答案就是 $ans$。

计算 $ans$ 的过程极为显然，从小到大排序后，输出 $a_n+a_{n-1}-a_1-a_2$ 即可。

## 代码

[**168817835**](https://codeforces.com/contest/1720/submission/168817835)

## 习题

如上所述，我们有如下习题留给读者：

1. 求证：当两个「差值」均形如 $M-m$ 时所得答案最大。（提示：考虑枚举所有情况。）
2. 试说明为什么按照 $\textbf1,\textbf2,\textbf3$ 的下划线分配区间可以取得 $ans$，并且说明括号里文字能够解释前一问的原因。
3. 求证：交换命题 $\bm{T}$ 中的 $M,m$ 后得到的命题 $\bm{T'}$ 与 $\bm{T}$ 正确性一致。

---

## 作者：DANIEL_x_ (赞：1)

## 思路
根据并观察样例，我们可以知道，答案应该是最大的两个数减去最小的两个数。

证明：

最大的两个数一定出现在 $[1,n]$ 中，如果这个数列的最大的两个数相邻，那么 $l,r$ 就取这两个数的下标。

对于最小值，最小的那两个数一定在 $[1,n]$ 中。

所以只需要输出最大的两个数减最小的两个数就行了。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
signed main()
{
  int n,a[maxn],T;
  cin>>T;
  while(T--)
  {
  	cin>>n;
  	for(int i=1;i<=n;i++) cin>>a[i];
  	sort(a+1,a+n+1);
  	cout<<a[n]+a[n-1]-a[1]-a[2]<<endl;  
  }
  return 0;
}
```


---

## 作者：GI录像机 (赞：1)

## 思路：

因为这是一道 Div2B，是不可能用什么神奇的 DS 维护的，因此考虑每个数的贡献。

观察样例发现，似乎每个答案都是最大值与次大值之和减去最小值和次小值。但光这样还不够，我们需要证明。

假设能取到这几个值，那么其他数就可以去掉，因为他们对答案毫无贡献。接着就是按题意所说，取一个区间，且这个区间要包含一个最（次）大值与一个最（次）小值。很明显是可以取到的。因为不管怎么排列，总有一个最（次）大值与一个最（次）小值相邻。

所以答案为最大值与次大值之和减去最小值和次小值。

~~要不是知道这是 Div2B 我就被诈骗了~~

## 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int t = read(), n;
signed main() {
	while (t--) {
		n = read();
		int max1 = 0, max2 = 0, min1 = INF, min2 = INF;
		for (int i = 1; i <= n; i++) {
			int tmp = read();
			if (tmp > max2) {
				if (tmp > max1) {
					max2 = max1;
					max1 = tmp;
				} else max2 = tmp;
			}
			if (tmp < min2) {
				if (tmp < min1) {
					min2 = min1;
					min1 = tmp;
				} else min2 = tmp;
			}
		}
		write(max1 + max2 - min1 - min2);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：cachejtt (赞：0)

## 题意
给你一个序列 $a_1,\dots,a_n$，从中选出两个下标 $l,r$，要求 $1\le l \le r\le n$。定义其美丽值为

$$\max\limits_{l\le i\le r}(a_i)-\min\limits_{l\le i \le r}(a_i)+\max(a_1,a_2,\dots,a_{l-1},a_{r+1},\dots,a_n)-\min(a_1,a_2,\dots,a_{l-1},a_{r+1},\dots,a_n)$$

求出它的最大美丽值。

## 思路
### 结论
先上结论。
一个序列的最大美丽值，一定等于**最大值加次大值减最小值减次小值**。

### 证明
不妨设最大值、次大值、次小值、最小值依次为 $a,b,c,d$。

我们只考虑它们在序列中的位置。设四个数依次排列，因此会有四个下标 $i_1,i_2,i_3,i_4$，至于哪个代表哪个数，需要分类讨论。

#### 类型1
```
a,b,c,d  d,c,b,a

b,a,c,d  d,c,a,b

a,b,d,c  c,d,b,a

b,a,d,c  c,d,a,b
```
四种类型，则我们选择 $l=i_2,r=i_3$。则对于这四种，答案分别为 $b-c+a-d,a-c+b-d,b-d+a-c,a-d+b-c$，它们都等于 $a+b-c-d$。
#### 类型2
```
a,c,b,d  d,b,c,a
a,c,d,b  d,b,c,a
a,c,d,b  b,d,c,a
c,a,d,b  b,d,a,c

a,d,b,c  c,b,d,a
a,d,c,b  b,c,d,a
d,a,b,c  c,b,a,d
d,a,c,b  b,c,a,d
```
八种类型，则我们选择 $l=i_1,r=i_2$。则对于前四种，答案为 $a-c+b-d$，对于后四种，答案为 $a_d+b-c$，它们都等于 $a+b-c-d$。

#### 总结
因此，总可以找到一区间 $[l,r]$，使得其美丽值为 $a+b-c-d$。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t=1,n,a[100005];
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    rep(i,1,n){
      cin>>a[i];
    }
    sort(a+1,a+n+1);
    cout<<a[n]-a[1]+a[n-1]-a[2]<<endl;
  }
  return 0;
}
```

---

## 作者：S__X (赞：0)

这么简单的一道题，居然还没有人发题解。本蒟蒻的第 $20$ 篇题解。

## 题意：
给你一个序列，输出其中最大的两个数的和减最小的两个数的和。为什么呢？请看下面的分析。

## 分析：
先看一下题目给出的公式：

$\max(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n}) - \min(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n}) + \max(a_{l}, \ldots, a_{r}) - \min(a_{l}, \ldots, a_{r})$

我们可以发现，这并不是最简形式。

其中 $\max(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n})+ \max(a_{l}, \ldots, a_{r})$ 就等于 $a_{1}, a_{2}, \ldots, a_{n}$ 中最大的两个数之和。

同样 $\min(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n})+ \min(a_{l}, \ldots, a_{r})$ 就等于 $a_{1}, a_{2}, \ldots, a_{n}$ 就等于 $a_{1}, a_{2}, \ldots, a_{n}$ 中最小的两个数之和。

因此，我们只要求出序列中最大的两个数的和减去最小的两个数的和就可以了。

我们可以先把序列排序。这样，最小的两个数就是最前面的两个数；最大的两个数就是最后的两个数。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        cout<<a[n]+a[n-1]-a[1]-a[2]<<endl;
    }
    return 0;
}
```

---

## 作者：RoyWu1207 (赞：0)

~~真的这道题很简单的！！！~~

是啊，这道题 CodeForces 系统评测完以后还要比 A 题过得多呢。

~~不排除有一堆蒙正确答案的。~~

进入正题。

~~最理想~~情况下，这四个数分别是：最大值，次大值，次小值，最小值。

我们将最大值和最小值看做一个区间，次大值和次小值看做一个区间。

接着分类讨论。

- 区间不重合：答案为 $max  + premax - premin - min$。

- 一个区间完全被包含在另一个区间：无影响，答案同上。

- 两区间交叉重叠：
	
    - 重叠部分分别为最小值、次小值或最大值、次大值，拆分一下区间你会发现还是原来的答案。
    
    - 重叠部分分别为最大值、次小值或次大值，最小值，将两个重叠值进行计算，外面的进行计算，答案还是不变。
    
所以，通过这些分析，之前被否定的猜测，居然成了事实！

~~感觉题目似乎有些提示：$4 \leq n$。~~

#### **AC Code：**

```cpp
#include <iostream>

using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int a, maxn = 0, minn = 1e9, premax = 0, premin = 1e9;
		for (int i = 1; i <= n; i++) {
			cin >> a;
			if (a > maxn)
				premax = maxn, maxn = a;
			else if (a > premax)
				premax = a;
			if (a < minn)
				premin = minn, minn = a;
			else if (a < premin)
				premin = a;
		} cout << maxn + premax - minn - premin << endl;
	} return 0;
}
```

蒟蒻的题解，写的不好请见谅！欢迎提出建议！谢谢！

---

## 作者：sandwave114514 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1720B)

题目大意

给你一个数列包含 $n$ 个数，你可以选择一个 $l$ 和 $r$ ，我们要让 $\left[ 1 , l - 1 \right]$ 和 $\left[ r + 1 , n \right]$ 这个区间的最大值减去最小值然后加上 $\left[ l , r \right]$ 这个区间的最大值减去最小值的和 最大，这个最大值是多少。


解题思路

我们可以先排序，再把两个最大值减去两个最小值，输出就行了

代码如下


```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
void write(long long n,bool p){
	if(n<0){putchar('-');n=-n;}
	if(n==0){if(p)putchar('0');return;}
	write(n/10,0);putchar(n%10+'0');
}//快写 
long long t,n,a[100010];
int main(){
	t=read();
	while(t--){//多组数据 
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+n+1);//排序 (sort默认是从小到大) 
		cout<<(a[n]+a[n-1])-(a[1]+a[2])<<endl; 
	}
	return 0;//完结撒花 
}

```


---

