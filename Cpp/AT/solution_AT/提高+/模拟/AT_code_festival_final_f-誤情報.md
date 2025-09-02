# 誤情報

## 题目描述

高桥君是一位非常厉害的工程师。他最近发明了一款机器人“欧几里得君”，能够计算出两正整数的最大公约数。

为了测试这台机器人的能力，高桥君准备了一列包含 $N$ 个正整数的数组 $A$（从1开始编号）。

高桥君让欧几里得君计算 $A_i$ 和 $A_{i+1}$ 的最大公约数，其中 $1 \leq i \leq N$，并且规定 $A_{N+1} = A_1$。

机器人报告说 $A_i$ 和 $A_{i+1}$ 的最大公约数为 $B_i$。

高桥君发现，报告中似乎存在矛盾，因此他计划根据数组 $A$ 来核对。然而，他意外丢失了数组 $A$ 的数据。

这使他无法准确判断欧几里得君的性能。

尽管如此，作为超级工程师，高桥君不认为欧几里得君会有太多错误的结果。因此，他希望计算出 $B$ 中可能存在的最少错误信息数量，并将其视为测量结果。

请你找出 $B$ 中错误信息数量的最小值。

## 说明/提示

### 示例解释 1

如果假设 $B_1$ 和 $B_3$ 是正确的，那么 $A_2$ 和 $A_3$ 必须都是 $4$ 的倍数，因此 $B_2 \geq 4$，这与给定的 $B_2$ 不符。所以，假设 $B_2$ 是误报的话，矛盾就消除了，答案就是 $1$。

### 示例解释 2

移除 $B_8$ 后，矛盾消失。例如，可能的 $A$ 序列为 $[21, 39, 44, 28, 65, 45, 18, 34, 25, 15]$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
4
2
4```

### 输出

```
1```

## 样例 #2

### 输入

```
10
3
1
4
1
5
9
2
6
5
3```

### 输出

```
1```

## 样例 #3

### 输入

```
10
2
7
1
8
2
8
1
8
2
8```

### 输出

```
2```

# 题解

## 作者：oyoham (赞：0)

### Problem 
题目大意：  
~~想必你们都看得懂，不给翻译了~~  
给定数组 $b$，求至少需要修改多少个值才能构造数组 $a$ 使得 $\forall 1\le i\le n,b_i=\gcd(a_i,a_{i+1})$。其中 $a_{n+1}=a_1$。
### Solution
考虑不合法状态；若对于相连的三个数 $b_{x-1},b_x,b_{x+1}$ 有 $b_x \nmid \gcd(b_{x-1},b_{x+1})$，则状态不合法。于是考虑将扫下去发现有 $b_x \nmid \gcd(b_{x-1},b_{x+1})$ 的一组，将 $b_{x+1} \gets \gcd(b_x,b_{x+2})$。从第 $1,2,3$ 个点都跑一次，取最大值即可。
### code
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
inline char gtch(){
	char c=getchar();
	while(c<33) c=getchar();
	return c;
}
int n=read();
int a[100005];
int b[100005];
signed main(){
	for(int i=1;i<=n;i++) a[i]=read();
	a[n+1]=a[1],a[n+2]=a[2],a[n+3]=a[3],a[n+4]=a[4];
	for(int i=1;i<=n+2;i++) b[i]=a[i];
	int ans,nans=0;
	for(int i=3;i<=n+2;i++){
		if(a[i-1]%__gcd(a[i-2],a[i])) nans++,a[i]=__gcd(a[i-1],a[i+1]);
	}
	ans=nans;
	nans=0;
	for(int i=1;i<=n+4;i++) a[i]=b[i];
	for(int i=4;i<=n+3;i++){
		if(a[i-1]%__gcd(a[i-2],a[i])) nans++,a[i]=__gcd(a[i-1],a[i+1]);
	}
	ans=min(ans,nans);
	nans=0;
	for(int i=5;i<=n+4;i++){
		if(b[i-1]%__gcd(b[i-2],b[i])) nans++,b[i]=__gcd(b[i-1],b[i+1]);
	}
	write(min(ans,nans));putchar(10);
}
```

---

