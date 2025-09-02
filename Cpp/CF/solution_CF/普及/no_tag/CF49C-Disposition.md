# Disposition

## 题目描述

Vasya bought the collected works of a well-known Berland poet Petya in $ n $ volumes. The volumes are numbered from $ 1 $ to $ n $ . He thinks that it does not do to arrange the book simply according to their order. Vasya wants to minimize the number of the disposition’s divisors — the positive integers $ i $ such that for at least one $ j $ ( $ 1<=j<=n $ ) is true both: $ j $ $ mod $ $ i=0 $ and at the same time $ p(j) $ $ mod $ $ i=0 $ , where $ p(j) $ is the number of the tome that stands on the $ j $ -th place and $ mod $ is the operation of taking the division remainder. Naturally, one volume can occupy exactly one place and in one place can stand exactly one volume.

Help Vasya — find the volume disposition with the minimum number of divisors.

## 样例 #1

### 输入

```
2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3
```

### 输出

```
1 3 2 
```

# 题解

## 作者：Buried_Dream (赞：4)

## 题意：

需要构造一个 $[1,n]$ 的序列满足 $j \bmod i = 0$，同时满足 $P(j)  \bmod i = 0$。

## 思路：

首先第一个条件是一定满足，因为任意一个数都是 $1$ 的倍数。

第二个条件只需要满足从 $[2,n]$  开始输出，最后再输出一即可。

## AC code：

```cpp
/*
work by: TLE_Automation
Time: O(轻轻松松过)
knowledge: 垃圾算法
*/
#include<bits/stdc++.h>
#define int long long
#define Min(x, y)  (x > y ? y : x);
#define Max(x, y)  (x > y ? x : y);
#define orz cout << "szt lps fjh AK IOI";
using namespace std;

const int maxn = 3e6;
const int MAXN = 3e3;
const double down = 0.996;
const double limit = 1e-10;
const int mod = 1e9 + 7;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (!isdigit(ch)) {if(ch == '-') {w = -1;}ch = getchar();}
	while (isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48);ch = getchar();}
	return s * w;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}

signed main() {
	int n = read();
	for(int i = 2; i <= n; i++) cout << i << " ";
	puts("1");
}


```

---

## 作者：xiaozeyu (赞：3)

这道题目有些绕

![](https://cdn.luogu.com.cn/upload/image_hosting/8i6rqts5.png)

但到底说了什么？这是这道题目AC的人少的原因

写出一个全排列，要求在排序前后，同一个数能整除一个数字的前后编号

比如1在排序后在第一位 

当j=1时 j%i=0,j%1=0;

只要符合就行 比如：每次输出的数与位置一样>?

就是: i在第i位，每个j=i

这不就行了嘛？


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin>>n;
	int i;
	while(i++<n-1)//或者 for i i<=n  i++ cout<<i
		printf("%d ",i+1);
	cout<<"1";
}
```


---

## 作者：Terraria (赞：1)

~~这是什么鬼翻译？！一点都没看懂要干嘛。。。~~

~~如果你想要全排列枚举，我也不拦着你。~~

不难发现，如果将一个序列 $a_i=i$ 的所有数列向前移一位，再把$1$放到最后面，就可以得到满足题意的序列。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	for(int i=2;i<=n;i++) cout<<i<<" ";
	cout<<1;
}
```


---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF49C)

一道水题。

从数据范围中能看出，最终输出的答案一定会包含 $1$，而任何数都是 $1$ 的倍数，那第一个条件必定能满足。

对于第 $2$ 个条件，只需要先从 $2$ 输出到 $n$，再在最后输出 $1$ 即可。
#### 最后贴上代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;

signed main() {
    ios :: sync_with_stdio(0);
	int n;
    cin >> n;
	for (int i = 2; i <= n; i++) cout << i << " ";
    cout << 1;
	return 0;
}
```


---

## 作者：Morax2022 (赞：0)

# CF49C 题解

**构造题**

构造数组 $a$ 满足题目给出条件。

不难发现在 $a_i = i + 1$ 时满足条件，将一个从 $2$ 至 $n$ 的数组输出后在结尾放个 $1$ 即可。

# AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
main()
{
	int n; cin >> n;
	for (int i = 2; i <= n; i++) cout << i << " ";
	cout << 1;//因为任何数都是1的倍数，设题意中的i=1即可 
}
```
希望本题解能给大家带来帮助！

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF49C)

## 思路

我们要构造一个序列满足 $j\bmod i=0$，且 $p(j)\bmod i=0$。

考虑任意数都是 $1$ 的倍数，所以可以从 $2$ 输出到 $n$，最后输出 $1$ 即可。

时间复杂度 $O(n)$。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    for(int i=2;i<=n;++i)cout<<i<<" ";
    cout<<"1\n";
   return 0;
}
~~~

[AC 记录](https://www.luogu.com.cn/record/96865988)

---

## 作者：szkzyc (赞：0)

题目意思：
要求你对 $1-n$ 这 $n$ 个数进行一种排列，使得任意的 $a_i$ 都会有一个 $j$ ($0<j<n+1)$ 满足以下这两个条件：

 $1. j\mod i = 0$
 
 $2.p(j)\mod i=0$
 
$p(j)$ 是按此规则排列好后的第 $j$ 卷书的编号。
 
对于条件 $1$，可以知道
 
对于任意的 $j$，都有一个 $i=1$ 可以满足。

对于条件 $2$，可以构造出前 $n-1$ 个数为 $2,3...n$，最后一个数为 $1$ 即可满足条件。

这是我的代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF INT_MAX
#define debug puts("qwq")
using namespace std;

int main(){
	int n;
	cin >> n;
	for(int i = 2; i <= n; i++) printf("%d ", i); 
	printf("1\n");
	return 0;
}

```


---

## 作者：XiaoQuQu (赞：0)

## 题意
？这题目我看了好久才看懂。接下来我把我的思路讲一下（虽然看了其他神犇写的题解）.  
  
这题的意思大概是：  
有 $n$ 个数，我们将它存入数组 $a$ 。对于其中一个数 $a_i$ 都必须找到一个 $j$ ，使得：
- $j \mod a_i = 0$
- $a_j \mod a_i =0$
## 解题过程
不难看出，第 $i$ 个数对应的应为 $i+1$。这个序列应该是这样的：  
$2$、$3$、$4$、$5$、$6$ ··· $n$、$1$  
这很好证明，留给读者自己证明（逃  
实际上，你只需自己看看每个数是否符合条件，就可以得出了。事实上，第一篇题解已经讲得很清楚了。这里只是帮忙改正了一下题意。
## 代码
```cpp
#include<cstdio>
int main(void) {
	int n; 
	scanf("%d", &n);
	for (int i = 2; i <= n; ++i) {
		printf("%d ", i);
	}
	printf("1");
	return 0;
}
```


---

## 作者：Fearliciz (赞：0)

简单的数论题。

#### 题目大意：

读入一个整数 $n$。

现在有 $n$ 个整数，将其存入数组 $a$ 。对于其中一个数 $a_i$
都必须找到一个 $j$，使得：

- $j \mod a_i = 0$

- $a_j \mod a_i =0$

求任何一个满足此规律的排列。

#### 解题思路：

显然这是一道 $\texttt{spj}$。

首先，我们先画一个 $2 \times n$ 的表格，下面表示下表，上面表示数值。

其次，我们将 $1$ 到 $n$ 都赋值为 $1$。

然后看每一个点是否能有一个 $j$。

然后发现，每一个点 $a_i$ 的 $j$ 值都为自己，而 $a_j=a_i$ 所以这就是一个解。

#### 代码：

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cout<<i<<" ";
	return 0;
}
```


---

