# Pashmak and Buses

## 题目描述

Recently Pashmak has been employed in a transportation company. The company has $ k $ buses and has a contract with a school which has $ n $ students. The school planned to take the students to $ d $ different places for $ d $ days (each day in one place). Each day the company provides all the buses for the trip. Pashmak has to arrange the students in the buses. He wants to arrange the students in a way that no two students become close friends. In his ridiculous idea, two students will become close friends if and only if they are in the same buses for all $ d $ days.

Please help Pashmak with his weird idea. Assume that each bus has an unlimited capacity.

## 说明/提示

Note that two students become close friends only if they share a bus each day. But the bus they share can differ from day to day.

## 样例 #1

### 输入

```
3 2 2
```

### 输出

```
1 1 2 
1 2 1 
```

## 样例 #2

### 输入

```
3 2 1
```

### 输出

```
-1
```

# 题解

## 作者：_Kimi_ (赞：2)

# CF459C题解

掉绿了，赶紧来水一发题解（。

### 题意

有 $n$ 个学生出去旅游，旅游 $d$ 天，有 $k$ 辆车，他们每天都要坐一次车，要求构造一种坐车方式使得每个人与别人的坐车选择有一次不同。

### 思路

共有 $k^d$ 种方法，如果方法小于 $n$ 就不够，无解。

对于一个学生，我们把他每天坐的车看成一个编号，他 $d$ 天坐车的编号相当于一个 $k$ 进制的数，我们按照这个来构造就可以了。

另：坐车的编号是 $k$ 进制数，每一位上的数只能是 $1,2,\ldots k$，而不是 $0,1,2,\ldots n - 1$ 所以答案要加一。

### 代码 

```cpp
#include<bits/stdc++.h>
#define int long long
#define ex exit(0)
#define WA AC
using namespace std;
const int maxn = 1010;
int n, k, d, a[maxn][maxn];
int check(int a, int b) {
	int res = 1;
	bool flag = 0;
  	for(int i = 1; i <= b; i++){
  		res *= k;
  		if(res > n) res = n;
	}
	if(res < n) return 0;
	return 1;
}
void input(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	cin >> n >> k >> d;
	if(!check(k, d)) cout << -1 << endl, ex;
}
signed main(){
	input();
	for (int i = 1; i <= n; i++) {
		int now = i;
		for (int j = 1; j <= d; j++) a[i][j] = now % k + 1, now /= k;
	}
	for (int j = 1; j <= d; ++j) {
		for (int i = 1; i <= n; ++i) cout << a[i][j] << ' ';
		cout << endl;
	}
	return 0;
}
```


---

## 作者：迟暮天复明 (赞：1)

[题面](https://codeforces.com/contest/459/problem/C)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16155438.html)

题意：
构造长度为 $d$ 的 $n$ 个数列，满足数列中的数在 $[1,k]$ 范围内，且不存在两个数列相同。要求字典序最小。

-----
先判断无解。当数列总个数 $k^d<n$ 时数列个数不够了，无解。 


我们把每个数列抽象作一个 $k$ 进制数。那每个数都不相等，且字典序最小的做法，明显是让每个数列的值为 $0,1,\ldots,n-1$ 。

比如 $k=2$ ，取 $d=3$ ，那数列就是 $\{0,0,0\},\{0,0,1\},\{0,1,0\},\{0,1,1\},\ldots,\{1,1,1\}$ 。

因为数列中的数是 $[1,k]$ 范围而不是 $[0,n-1]$ ，所以输出时每个数都要加上 $1$ 。做完了。

[代码](https://paste.ubuntu.com/p/zjZknCt26f/)

---

## 作者：CarrotMeow (赞：0)

## [CF459C Pashmak and Buses](https://www.luogu.com.cn/problem/CF459C)

> 构造 $n$ 个长度为 $d$，范围在 $[1, k]$ 的序列，使得序列之间两两不等。
>
> 长度都为 $d$ 的序列 $A, B$ 不等指不成立 $\forall i \in [1, d], ~ A_i = B_i$。

由于只有 $k^d$ 种可能的序列，如果 $k^d < n$，根据 [抽屉原理](https://oi-wiki.org/math/combinatorics/drawer-principle/)，无法满足「两两不等」的要求，输出 $-1$。

接下来解决「两两不等」。可以联想到用 $1 \sim k$ 的数码，即 $k$ 进制数来表示状态。那么 $n$ 种状态也就是 $1 \sim n$ 的 $k$ 进制数，转换进制即可。

另外要注意 $k^d \geq n$ 时，不能朴素乘。可以使用循环，当超过 $n$ 时直接输出 $-1$ 并退出；也可以特判一系列会超出数字范围的情况后，直接使用 `pow()` 来判断。

[代码](https://codeforces.com/contest/459/submission/246745454)。

---

