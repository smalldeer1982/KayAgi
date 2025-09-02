# Santa Claus and Tangerines

## 题目描述

​	圣诞老人有n个橘子，每个橘子的第i个都是由 $a_{i}$片。圣诞老人来到一所有$k$个学生的学校。圣诞老人决定用橘子招待他们。

​	然而，橘子可能太少，不能给每个学生提供至少一个橘子。所以圣诞老人决定把橘子分成几个部分，这样就不会有人生气了。为了做到这一点，他可以把一个橘子或任何现存的部分分成两个更小的相等的部分。如果他想分割的部分的橘子瓣数量是奇数，那么得到的一个部分将比另一个多出一片。只由一片组成的橘子是不允许分割的。

​	圣诞老人想要送给每个人一个完整的橘子或者恰好是其中的一部分(这也意味着每个人都必须得到一个正数片)。一个或几个橘子或他们的部分可能留在圣诞老人那里没有分发。

​	若$b_{i}$为第i个学生最后的切片数,则圣诞老人的快乐值成为 $b_{i}$ 中最小的。

​	你的任务是在圣诞老人用橘子(或其中几瓣)招待每个人之后，求最大的快乐值。

## 样例 #1

### 输入

```
3 2
5 9 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2 4
12 14
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2 3
1 1
```

### 输出

```
-1
```

# 题解

## 作者：Fan_Tuan (赞：3)

## 题意：
将 $n$ 个橘子分给 $k$ 个人，每个橘子有 $a_i$ 片，可以将片数大于 1 的橘子分成若干份，最大化 $k$ 个人所获得的橘子片数的最小值，并输出这个值。

## 思路：
观察题目发现最大的数为 1e7，考虑枚举。

定义一个数组 $a$，$a_i$ 表示 $i$ 这个数的个数，$sum$ 为当前已经分了橘子的人数。

从最大值开始往下枚举 $i$，如果当前 $sum$ 已经大于 $k$，那么此时 $i$ 即为答案，否则那就将有 $i$ 片的橘子对半分开，将 $a_i$ 转移到 $a_{i/2}$ 和 $a_{i/2 + 1}$ 中，继续往下枚举，直到 $sum$ 大于 $k$。

因为是从大到小枚举的，所以可以保证最小值最大。

## 代码：

```c
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#define int long long
using  namespace  std;

inline int read() {
	int f = 0, s = 0;
	char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void print(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 1e7 + 10;
int n, k, a[maxn];

signed main() {
	n = read(), k = read();
	int sum = 0;
	int x;
	for (int i = 1; i <= n; i++) a[x = read()]++, sum += x;
	if (sum < k) print(-1);
	else {
		sum = 0;
		for (int i = 10000000; i >= 1; i--) 
			if (a[i]) {
				sum += a[i];
				if (i * 2 <= 10000000) sum -= a[i * 2] + a[i * 2 - 1];
				if (i == 1) sum += a[i];
				if (sum >= k) {
					print(i);
					return 0;
				}
				a[i / 2] += a[i];
				a[(i + 1) / 2] += a[i];
			}
	}
	return 0;
}
```


---

## 作者：Buried_Dream (赞：1)


### 题外话：

这道题是 @Fan＿Tuan 给我们讲搜索、枚举的时候讲的，学了一下午搞懂了，心血来潮写篇题解，这里主要是对 @Fan_Tuan 的题解进行更加详细的解释。


# 正题

## 题意：
将瓣数大于 $1$ 的橘子尽可能多的平均分给所有人，使分的橘子最小值最小，输出最小值。

## 思路：
观察题目发现最大的数为 $1e7$ 用枚举。

用数组记录这种瓣数的橘子有多少个，也就是所谓的桶排思想，从 $1e7$ 开始枚举，想想为什么从
$1e7$ 开始枚举，你从 $1e7$ 开始枚举，才能保证你可以找到最优解，当橘子没有人多的时候，将橘子分瓣，将一个橘子分成两份，每分一次就判断够不够，但要注意 $2$ 瓣的橘子，想想为什么。
 $2$ 瓣的橘子减完后会多减去一个 $1$ 瓣的橘子，所以最后要加上一个 $1$ 瓣的橘子。

具体解释在代码里。

### 先对变量进行解释：
```cpp
int n,k,x;//n是有几个橘子，k是有几个人，x是橘子的瓣数 
int a[maxn];//a数组用来记录这种瓣数的橘子有多少个 
int sum,ans;//sum记录橘子瓣数，ans记录答案用的 
```
### 输入不做解释：
```cpp
	n = read(), k = read();
	for (int i = 1; i <= n; i++) {
		cin >> x;
		a[x] ++;//桶排思想 
		sum += x;//记录有多少瓣橘子 
	} 
	if(sum < k) {//sum的使命已经完成，所以下面可以进行废物利用 
	cout << "-1" <<endl;
	return 0;	
	}
```
### 枚举：（这里是重点，注意看）

```cpp
	sum = 0;
	for (int i = 1e7; i >= 1 ; i--) { //从后往前扫才会是最优解 
		if(a[i]!=0) {
		sum += a[i];//当前橘子有几个， 
		if(i <= 5e6 ) sum -= a[i*2] + a[i * 2 - 1];//将现在的橘子看成是由别的橘子分出来的 
		if(i == 1)sum += a[1];	//如果是1的话，1是不可能分出橘子的，所以加上 
		if(sum >= k) {
			cout<<i;
			return 0;
		}
		a[i / 2] += a[i];//将橘子分开 
		a[(i + 1) / 2] += a[i];  
		}
	}
```
#### 最后贴完整代码：

# AC Code：
```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<queue>
#include<stack>
#include<cmath>
#include<cstring>
#define int long long
#define il inline
#define re register
#define inf 0x3f3f3f3f
#define MAXN 1001
using namespace std;
const int maxn = 1e7 + MAXN + 2048 + 1;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-'){w = -1;}ch = getchar();}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s*w;
}
bool cmp(int a,int b) {
	return a > b;
}
int n,k,x;//n是有几个橘子，k是有几个人，x是橘子的瓣数 
int a[maxn];//a数组用来记录这种瓣数的橘子有多少个 
int sum,ans;//sum记录橘子瓣数，ans记录答案用的 
signed main(){
	n = read(), k = read();
	for (int i = 1; i <= n; i++) {
		cin >> x;
		a[x] ++;//桶排思想 
		sum += x;//记录有多少瓣橘子 
	} 
	if(sum < k) {//sum的使命已经完成，所以下面可以进行废物利用 
	cout << "-1" <<endl;
	return 0;	
	}
	sum = 0;
	for (int i = 1e7; i >= 1 ; i--) { //从后往前扫才会是最优解 
		if(a[i]!=0) {
		sum += a[i];//当前橘子有几个， 
		if(i <= 5e6 ) sum -= a[i*2] + a[i * 2 - 1];//将现在的橘子看成是由别的橘子分出来的 
		if(i == 1)sum += a[1];	//如果是1的话，1是不可能分出橘子的，所以加上 
		if(sum >= k) {
			cout<<i;
			return 0;
		}
		a[i / 2] += a[i];//将橘子分开 
		a[(i + 1) / 2] += a[i];  
		}
	}
	return 0;
}
```

---

## 作者：Suzt_ilymtics (赞：0)


[题面传送](https://www.luogu.com.cn/problem/CF748E) | [更好的阅读体验？](https://www.cnblogs.com/Silymtics/p/solution-CF748E.html)

## Solution

通过观察发现，每次操作一定是将最大的一个或多个橘子分成两部分。

而 $a_i \le 10^7$，我们考虑用一个桶记录，然后从大向小遍历，遇到大的就把它分成两部分，在这个过程中求出最优解。

我们设分发的最小的橘子瓣数为 $l$，现在枚举到了 $i$，在 $[l,i]$ 这段区间中有 $n$ 瓣橘子。

对于每一个位置 $i$，我们先考虑能不能让 $l$ 在满足 $n \ge K$ 的情况下变得尽可能大（代码中其实是找到了这个位置后面一个位置）

然后如果 $i$ 分成两部分后的较大一部分比 $l$ 小，那么再分已经没有意义了，$l-1$ 就是我们求的答案，输出完退出即可。

分的时候讨论一下奇偶性暴力分就行。

注意每次分时 $n$ 会增加 $f_i$ 瓣橘子。

注意 $i$ 只能枚举到 $2$。

如果最后 $n \ge K$ 输出 `1`，否则证明无解输出 `-1`。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e7 + 10;

int n, K, ans = MAXN;
int f[MAXN];

signed main() {
	cin >> n >> K;
	for(int i = 1, x; i <= n; ++i) cin >> x, f[x]++;
	int l = 0;
	for(int i = MAXN - 10; i >= 2; --i) {
		while(n >= K) n -= f[l++];
		if((i + (i & 1) >> 1) < l) return printf("%lld\n", l - 1), 0;
		if(i & 1) f[i >> 1] += f[i], f[(i >> 1) + 1] += f[i];
		else f[i >> 1] += 2 * f[i];
		n += f[i];
	}
	if(n >= K) puts("1");
	else puts("-1");
	return 0;
}
```

---

