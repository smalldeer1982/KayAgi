# Directional Increase

## 题目描述

We have an array of length $ n $ . Initially, each element is equal to $ 0 $ and there is a pointer located on the first element.

We can do the following two kinds of operations any number of times (possibly zero) in any order:

1. If the pointer is not on the last element, increase the element the pointer is currently on by $ 1 $ . Then move it to the next element.
2. If the pointer is not on the first element, decrease the element the pointer is currently on by $ 1 $ . Then move it to the previous element.

But there is one additional rule. After we are done, the pointer has to be on the first element.

You are given an array $ a $ . Determine whether it's possible to obtain $ a $ after some operations or not.

## 说明/提示

In the first test case we can obtain the array after some operations, but the pointer won't be on the first element.

One way of obtaining the array in the second test case is shown below.

 $ \langle \underline{0}, 0, 0, 0\rangle \to \langle 1, \underline{0}, 0, 0 \rangle \to \langle \underline{1}, -1, 0, 0\rangle \to \langle 2, \underline{-1}, 0, 0\rangle \to \langle 2, 0, \underline{0}, 0\rangle \to \langle 2, \underline{0}, -1, 0\rangle \to \langle \underline{2}, -1, -1, 0\rangle $

## 样例 #1

### 输入

```
7
2
1 0
4
2 -1 -1 0
4
1 -4 3 0
4
1 -1 1 -1
5
1 2 3 4 -10
7
2 -1 1 -2 0 0 0
1
0```

### 输出

```
No
Yes
No
No
Yes
Yes
Yes```

# 题解

## 作者：Altwilio (赞：4)

### $1.$ 题意
对于一个初始全部元素为 $0$ 的序列，放置一个指针在第一位，定义如下两种操作：
 1. （当指针不在最后一位时）指针指向的当前元素加一，指针右移一位。
 2. （当指针不在第一位时）指针指向的当前元素减少一，指针左移一位。
 
需要保证操作结束时指针回到第一位。如下面例子：
$\langle\underline{0}, 0,0,0\rangle \rightarrow\langle 1, \underline{0}, 0,0\rangle \rightarrow\langle \underline{1},-1,0,0\rangle \rightarrow\langle 2, \underline{-1}, 0,0\rangle \rightarrow\langle 2,0, \underline{0}, 0\rangle \rightarrow\langle 2, \underline{0},-1,0\rangle \rightarrow\langle\underline{2},-1,-1,0\rangle$

则最后得到的 $\langle\underline{2},-1,-1,0\rangle$ 就是合法的，每次给定一个序列，问给定序列是否合法。
### $2.$ 思路
首先，对于一个合法序列，其元素的和一定等于 $0$，因为指针最终会回到第一位，所以加一与减一的操作次数是相等的。

其次，合法序列末尾的 $0$ 是对序列的合法性没有影响。我们选择直接去掉末尾的 $0$ 后来做前缀和。设 $n$ 为去掉末尾 $0$ 后的长度。

对于前缀和序列，每当前缀和序列出现 $sum[i] = 0$ 时，就意味着指针能够从第一位走到 $i$ 再回到第一位，但是如果存在 $j > i$ 也使得 $sum[j] = 0$，那我们就不能保证指针可以从第一位走到 $j$ 再走回第一位了。


所以对于合法序列的前缀和 $sum[n]$ 一定等于 $0$，并且 $sum[1]$ 到 $sum[n - 1]$ 不会出现 $0$。

最后对于前缀和序列，$sum[1]$ 到 $sum[n - 1]$ 一定大于 $0$。这是由每次操作决定的，加一右移，减一左移，这样的操作性质导致了每一个减一的相对位置都比加一靠右，所以对于一个非结束位置的 $i$，从 $1$ 到 $i$ 的加一操作一定比减一操作多。

根据上述yy思路可以码出代码。下面有证明。

### $3.$ 证明

对于一个元素下标 $i$，设在 $i$ 上进行的第一个操作的次数为 $b[i]$，第二个操作的次数为 $c[i]$ 。

则一定有 $a[i] = b[i] - c[i]$ 和 $c[i] = b[i-1]$，这是因为指针需要回到第一位。

可以得出 $b[i] = b[i - 1] + a[i]$ $(b[1] = a[1])$。

当 $b$ 数组满足以下两个条件时可以够造出一个合法 $a$ 序列：

1. 对于任意 $(1≤i≤n)$，$b[i]≥0$。
1. $b$ 数组中第一次出现 $0$ 后所有的元素都为 $0$。

如何构建一个合法序列：对于 $1≤i<n$，在 $i$ 上做 $b[i] - 1$ 轮操作一和二，再做一次操作一（$i$ 不等于 $n$ 时）。最后一直做操作二，直到指针归位。这与样例给出的操作顺序一致：

$\langle\underline{0}, 0,0,0\rangle \rightarrow\langle 1, \underline{0}, 0,0\rangle \rightarrow\langle \underline{1},-1,0,0\rangle \rightarrow\langle 2, \underline{-1}, 0,0\rangle \rightarrow\langle 2,0, \underline{0}, 0\rangle \rightarrow\langle 2, \underline{0},-1,0\rangle \rightarrow\langle\underline{2},-1,-1,0\rangle$

这样就保证了，在满足条件下一定存在合法序列。

### $4.$ 代码

```cpp
#include<map>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

template<class T> inline void read(T &x){
    x = 0; register char c = getchar(); register bool f = 0;
    while(!isdigit(c)) f ^= c == '-', c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if(f) x = -x;
} 

template<class T> inline void print(T x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar('0' + x % 10);
}

const int N = 2e5 + 10;
int T, n;
long long a[N];

signed main(){
	read(T);
	while(T --){
		read(n); int flag = 1;
		for(int i = 1; i <= n; i ++) read(a[i]);
		while(!a[n] && n) n --;
		if(!n){ printf("Yes\n"); continue; }
		for(int i = 1; i <= n; i ++) a[i] += a[i - 1];
		if(a[n] != 0){ printf("No\n"); continue; }
		for(int i = 1; i < n; i ++){
			if(a[i] <= 0){ flag = 0; break; }
		}
		if(flag == 0) printf("No\n");
		else printf("Yes\n");
	}
}
```


---

## 作者：良心WA题人 (赞：2)

**谨以此题解纪念长时间停打 CF 后的第一场比赛**

### 思路

这题爆 ```long long``` 吃了 150 罚分，人麻了 qwq

又是结论题。~~结论题专场了属于是~~

先分析一下，假设第一次一直到了位置 $i$。因为最后需要回到 $1$ 号下标，所以除了 $1$ 号下标会加一，$i$ 号下标会减一以外其他的都会抵消掉。

所以，我们可以看出来总和是恒为 $0$ 的，那么对于总和不为 $0$ 的直接输出 ```No``` 即可。

现在，我们可以把问题变成：

> 你可以选择一些长度大于 $1$ 的区间，要求第一个区间左端点为 $1$，现在可以将这些区间的左端点加一，右端点减一，问能否将全是 $0$ 的数组变为目标数组。

那么，我们设选出来的区间分别为 $l_i,r_i$，则这些区间可以对应原操作：

$l_1->r_1->l_2->r_2->l_3->r_3->...->r_k->1$

为了方便，我们可以让 $r_i$ 是单调不增的。因为若 $r_{i+1}>l_{i+1}>r_i$，对应到原操作 $r_i$ 并没有加一，出现了错误，而若 $r_{i+1}>r_i>l_{i+1}$，则原操作与 $l_i->r_{i+1}->l_{i+1}->r_{i}$ 是等价的。所以，每一些操作都可以对应成一组右端点单调不增的区间，而每一组这样的区间也可以对应到一些正确的操作。

因为右端点是单调递减的，所以第一个区间的右端点一定是右边第一个目标不为 $0$ 的数。因为若为 $0$，则该下标作为右端点时会减去 $1$，而因为右端点单调递减，所以左端点不可能为该下标。那么它就再也无法变回目标 $0$ 了。因为第一个操作十分特殊，所以我们可以强行让 $a_1$ 减一，然后 $a_{last}$ 加一。

现在我们可以考虑剩下的区间如何选择。我们从最终状态倒退回初始状态，不难得到有两种会使序列无法达到的情况：

* 左端点不够 对于一个 $a_i$ 小于 $0$ 的数，若它左边 $a_i$ 大于 $0$ 的数的和比它的绝对值小，那么将左边的数都变成小于等于 $0$ 的后，当前数还是小于 $0$ 的，那么此时永远也无法变回全都是 $0$ 的状态。

* 右端点不够 对于一个 $a_i$ 大于 $0$ 的数，若它右边 $a_i$ 小于 $0$ 的数的和的绝对值比它小，那么将右边的数都变成大于等于 $0$ 的后，当前数还是大于 $0$ 的，那么此时永远也无法变回全都是 $0$ 的状态。

这两种情况可以用前缀或后缀和是否大于等于 $0$ 来判断。于是，若上述错误都没发生，原序列一定有办法能够达成。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
int a[NN];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,last=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i])
				last=i;
		}
		if(!last)
		{
			puts("Yes");
			continue;
		}
		a[1]--,a[last]++;
		long long res=0;
		for(int i=1;i<=n;i++)
		{
			res+=a[i];
			if(res<0)
				break;
		}
		if(res>0||res<0)
		{
			puts("No");
			continue;
		}
		for(int i=n;i;i--)
		{
			res+=a[i];
			if(res>0)
				break;
		}
		if(res>0)
			puts("No");
		else
			puts("Yes");
	}
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

神 A 就是结论题，我不活啦 qwq。

首先我们先想想只有**一去一回**，发现是**位置 $1$ 加一，某右边的位置减一**。

接着我们扩展到这道题。发现其实这样的一个回路必然可以分解成几个这样的**一去一回**，只不过左端点可能不是 $1$。

注意这里的分解指的是拥有同样的效果，因为从路径上来看，回路可能在一去一回中途跑去做别的任务然后再回来的。

所以我们得到了条件：

**作 $\{a\}$ 的后缀和，满足 $a_i\le 0(1\le i\le n)$ 且 $a_1=0$。**

然后就做完了……吗？

首先我们把 $\{a\}$ 后缀的极长连续 $0$ 去除。

我们发现如果除 $a_1$ 外有别的 $a_x=0$，则 $[1,x-1]$ 和 $[x,n]$ 形成了两个连通块，也就是说虽然 $[x,n]$ 中正负可抵消，但是我们过不去啊！

所以最终的充要条件：

**作 $\{a\}$（除后缀极长 $0$ 段后）的后缀和，满足 $a_i<0(2\le i\le n)$ 且 $a_1=0$。**

```cpp
int n,a[N];
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i];
	while(n && !a[n]) n--;
	if(!n){
		cout<<"Yes"<<endl;
		return ;
	}
	Rof(i,n-1,1) a[i]+=a[i+1];
	if(a[1]!=0){
		cout<<"No"<<endl;
		return ;
	}
	For(i,2,n){
		if(a[i]>=0){
			cout<<"No"<<endl;
			return ;
		}
	}
	cout<<"Yes"<<endl;
}
```

---

