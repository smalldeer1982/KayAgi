# Mocha and Math

## 题目描述

Mocha is a young girl from high school. She has learned so much interesting knowledge from her teachers, especially her math teacher. Recently, Mocha is learning about binary system and very interested in bitwise operation.

This day, Mocha got a sequence $ a $ of length $ n $ . In each operation, she can select an arbitrary interval $ [l, r] $ and for all values $ i $ ( $ 0\leq i \leq r-l $ ), replace $ a_{l+i} $ with $ a_{l+i} \,\&\, a_{r-i} $ at the same time, where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND). This operation can be performed any number of times.

For example, if $ n=5 $ , the array is $ [a_1,a_2,a_3,a_4,a_5] $ , and Mocha selects the interval $ [2,5] $ , then the new array is $ [a_1,a_2\,\&\, a_5, a_3\,\&\, a_4, a_4\,\&\, a_3, a_5\,\&\, a_2] $ .

Now Mocha wants to minimize the maximum value in the sequence. As her best friend, can you help her to get the answer?

## 说明/提示

In the first test case, Mocha can choose the interval $ [1,2] $ , then the sequence becomes $ [ 0, 0] $ , where the first element is $ 1\,\&\,2 $ , and the second element is $ 2\,\&\,1 $ .

In the second test case, Mocha can choose the interval $ [1,3] $ , then the sequence becomes $ [ 1,1,1] $ , where the first element is $ 1\,\&\,3 $ , the second element is $ 1\,\&\,1 $ , and the third element is $ 3\,\&\,1 $ .

## 样例 #1

### 输入

```
4
2
1 2
3
1 1 3
4
3 11 3 7
5
11 7 15 3 7```

### 输出

```
0
1
3
3```

# 题解

## 作者：qinyihao (赞：2)

假设答案是 $x$。

在 $x$ 的二进制表达式中，只有在所有 $a_i$ 的二进制表示中，该位是 $1$ ，才会有一个位是 $1$ 。 否则，我们可以用一个操作来使 $x$ 中的这个位变成 $0$ ，这是一个较小的答案。

因此，我们可以先设定 $x = a_1$ 。然后，我们对序列进行迭代，使 $x = x \& a_i$ ，最后，$x$ 就是答案。

[code](https://www.luogu.com.cn/paste/ey5ovk10)

---

## 作者：miao5 (赞：2)

~~这道题算是签到题吧。~~

我们知道 $ \& $ 操作是每次 $ \& $ 都会使答案小于等于两个原数中的最小值。所以我们肯定是 $ \& $ 的操作次数越多越好，我们还知道两个数 $ \& $ 多次答案是一样的，所以我们就把 $a_1,a_2,a_3,\dots,a_n$ 全部 $ \& $ 起来，就是最优答案。

```cpp
#include<iostream>
using namespace std;
int a[105];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int ans=a[1];
		for(int i=2;i<=n;i++){
			ans=ans&a[i];
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：Cocoly1990 (赞：0)

题面不再复述了，很多题解并没有讲清楚为什么最后答案是所有数 $\&$ 之后的值，这里稍微讲一下。

我们需要显然的两个事实：

1. 取和操作对于最小化最大值必然是有益的，也就是说哪怕对两个数取和 $114514^{1919180}$ 次，也不会使最终答案更劣。

2. 经过若干次操作，任意两个数肯定可以被取和。

我们可以将每个数在二进制下思考，对于第 $k$ 位，如果所有数里有一个数该为是 $0$，我们必然可以把他与其他 $n-1$ 个数都取和，使得所有数的该为都变成 $0$.

答案就呼之欲出了，考虑二进制下每位独立思考，对于第 $k$ 位，如果 $n$ 个数全部为 $1$，那么无论如何取和，剩下的仍然是 $1$，否则一定有办法使得所有数的该为变成 $0$.

所以显然的，答案就是 $a_1\&a_2\&...\&a_n$.

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很明显，$a\operatorname{AND}b$ 既不大于 $a$ 也不大于 $b$。

那么，我们可以无限次地将 $2$ 个数取逻辑与结果，直到整个数列是同一个数字。

首先将数列排好序，然后对于所有的 $1\le i<n$，都来一遍：

$$a[i]\gets a[i+1]\gets a[i]\operatorname{AND}a[i+1]$$

再排序……直到 $a[1]=a[n]$ （序列数字相同）为止。

### 2 代码与记录

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define max_n 100
#define inf 0x3f3f3f3f
int t;
int n;
int a[max_n+2];
int ans;
int cnt;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1559A_1.in","r",stdin);
	freopen("CF1559A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	for(int ca=1;ca<=t;++ca){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
		}
		sort(a+1,a+n+1);
		while(a[1]<a[n]){
			for(int i=1;i<n;++i)a[i]=a[i+1]=(a[i]&a[i+1]);
			sort(a+1,a+n+1);
		}
		printf("%d\n",a[1]);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/56080858)

By **dengziyue**

---

## 作者：lin000 (赞：0)

[CF1559A](https://www.luogu.com.cn/problem/CF1559A)

#### 题意
给出一个数组 $a$，可以选取任意区间 $[l,r]$ 使得 $a_{l}$ 到 $a_{r}$ 之间的每个数 $a_i$ 为 $a_{l + i}\& a_{r - i}$ 其中 $0 \leq i \leq r -  i$。操作次数任意。给出最大数最小化的方案，求最大数。

#### 分析
首先，观察可得两数与所得的数一定不大于两数。又因为可以做任意次操作，所以任意两个数都可以做与操作。所以只需要将每两数都进行与操作，让数值尽量小即可。

#### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int N = 110;

int n , m , a[N];
int lowvit(int x){
	return x & (-x);
}
struct note{
	int nm , last;
};
int ans;
int main(){
	cin >> m;
	while(m --){
		ans = 0;
		cin >> n;
		for(int i = 1 ; i <= n ; i++){
			cin >> a[i];
		}

		for(int i = 1 ; i <= n ; i++){
			for(int j = i ; j <= n ; j++){
				//不用担心 i = j 因为相同数与结果不变 
				a[i] &= a[j];
				a[j] &= a[i];				
			} 
		}
		for(int i = 1 ; i <= n ; i++){
			ans = max(ans , a[i]);
		}
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：Refined_heart (赞：0)

题目大意：每次可以使得一个区间中的数，左右两两对应的数取与运算，问使得最大值最小的答案。

显然每一个数都是可以被其他数一起取与运算的。而且与运算越多答案不增，所以答案就是它们的与运算和。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[500];
int main(){
    scanf("%d",&T);while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",&a[i]);
        for(int i=2;i<=n;++i)a[1]&=a[i];
        printf("%d\n",a[1]);
    }
    return 0;
}
```

---

## 作者：Doubeecat (赞：0)

## A

> 给定一个序列，你可以执行以下的操作任意次：
>
> - 选择一个区间 $[l,r]$​，对于所有 $i(0\leq i \leq r-l)$​，将 $a_{l+i}$​ 替换成 $a_{l+i} \operatorname{and} a_{r-i}$
>
>     例如当 $n=5$​ 时， 原数组为 $ [a_1,a_2,a_3,a_4,a_5] $​ , 此时选择 $ [2,5] $​ 这个区间, 新数组就是 $ [a_1,a_2 \operatorname{and} a_5, a_3 \operatorname{and} a_4, a_4 \operatorname{and} a_3, a_5 \operatorname{and} a_2] $
>
> 现在让你最小化序列的最大值。
>
> $T \leq 100,n \leq 100,a_i \leq 10^9$

思维题。

首先考虑我们选择两个数 $\operatorname{and}$ 起来的本质是：两数二进制意义下的每一位取 $\operatorname{min}$。

那么实际上稍加思考，我们可以发现：对于一个数来说，与另一个数 $\operatorname{and}$ 起来并不会变得更优秀。可以用分类讨论来得出结论，若当前为 $1$ 那么不管 $\operatorname{and}$ 上什么数，最终这一位上的答案都是 $\leq 1$ 的。若当前为 $0$，那么不管 $\operatorname{and}$ 上什么数这一位都是为 $0$。

然后这个操作实际上当我们操作 $[i,i+1]$ 时，就是把两个数给 $\operatorname{and}$ 起来，所以我们只需要贪心的把所有数 $\operatorname{and}$ 起来即可。

时间复杂度 $\Theta(n)$

### 代码

```cpp
void solve() {
    int n;read(n);
    int x;read(x);
    for (int i = 2;i <= n;++i)  {
        int now;read(now);x &= now;
    }
    printf("%d\n",x);
}
```



---

## 作者：天才颓废学家 (赞：0)

# CF1559A Mocha and Math 题解

## 一、题意
T组数据。  
每组数据给定一个序列 a，可以执行任意次操作：选择一个任意的闭区间 $\;[l,\;r]$，对于所有值$\;i\;(0\;\leq\;i\;\leq\;r\;-\;l)$，用 $\;a_{\,l\;+\;i}\;\&\;a_{\,r\;-\;i}\;$替换$\;a_{\,l\;+\;i}$，其中$\;\&\;$表示按位与运算。要求最小化最大值，并输出这个最大值。

------------

## 二、前置知识
1.关于位运算。  
本题需要对**计算机的位运算**有较深的了解，具体各个位运算符这里我不展开讲，有兴趣可以参照[这篇文章](https://www.runoob.com/w3cnote/bit-operation.html)。我主要讲讲**与运算**。  
2.何为与运算。  
参加运算的两个数据，按**二进制位**进行“与”进行运算。（~~这不等于没说吗~~）但这里有一个很重要的点：**位运算都是按二进制位进行的**。  
3.其运算规则如下：
$$0\;\&\;0\;=\;0$$
$$0\;\&\;1\;=\;0$$
$$1\;\&\;0\;=\;0$$
$$1\;\&\;1\;=\;1$$
即：**对于两数相同位置上的数，只有两位同时为 1，结果才为 1，否则为 0。**  
4.例如：$3\;\&\;5\;$  
即$\;0000\;0011\;\&\;0000\;0101\;=\;0000\; 0001\;$因此，$3\;\&\;5\;$的值为 1。  
另，负数按**补码**（即“取反加一”）形式参加按位与运算。

----

## 三、本题做法
说了这么多，如果你真的理解了与运算，那么我们~~不难~~发现一个~~妙♂妙~~的性质：**对两数进行与运算，所得值一定小于等于两数。** 可以通俗地理解为 “**越与越小**” 当然，包括等于。   
那么本题的做法就呼之欲出了：反正越与越小，只要**把所有的数和除它自己以外的所有数都进行一次与运算**，把所得值取最大值即可。反观条件，题目中所给的操作方法是可以满足我们的要求的，正确性显然。

----

## 四、代码实现
~~Talk is cheap, show me your code.~~
```c++
#include<bits/stdc++.h>
#define int long long
#define mAK make_pair
#define fi first
#define se second
#define sqr(x) ((x) * (x))
#define inf 114514114514
#define N 114514
#define M 114514
#define pb push_back
#define mod 998244353
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)){
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)){
		x = x * 10 + ch -48;
		ch = getchar();
	}
	return x * f;
}
inline void write(int x){
	if (x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if (x >= 10)
		write(x / 10);
	putchar(x % 10 + 48);
	return;
}
inline void writeln(int x){
	write(x);
	puts("");
	return;
}
inline void writesp(int x){
	write(x);
	puts(" ");
	return;
}
int T, n, Max;
int a[1145140];
signed main(){
	T = read();
	while(T --){
		n = read();
		Max = 0; // 多组数据！清零！
		for (int i = 1; i <= n; ++ i)
			a[i] = read();
		for (int i = 1; i <= n; ++ i){
			int temp = a[i];
			for (int j = 1; j <= n; ++ j)
				if (i != j)
					temp &= a[j]; // 同上所述操作。
//			cout << Max << ' ' << temp << endl;
			Max = max(Max, temp);
		}
		writeln(Max);
	}
} 
```


---

## 作者：Leasier (赞：0)

由于与运算不会把值变得更大，我们可以考虑将一个数不断与上别的数。

比如：对于第一个数，我们可以不断利用 $[1, 1]$、$[1, 2]$、……、$[1, n]$ 来让第一个数变成所有数与起来的值。其他位置上的数字可以通过再做一次上述操作得到所有数与起来的值。

于是答案就是所有数与起来的值。

代码：
```cpp
#include <stdio.h>

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, ans = 0x7fffffff;
		scanf("%d", &n);
		for (int j = 1; j <= n; j++){
			int a;
			scanf("%d", &a);
			ans &= a;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：江户川·萝卜 (赞：0)

### 题意
给定一个序列 $a$，长度为 $n$，你可以进行**无限次**的操作，使得序列的最大值最小，输出最大值。

操作：选定 $l,r$，对于所有的 $i(0\le i\le r-l)$，**同时**将 $a_{l+i}$ 设为 $a_{l+i} \& a_{r-i}$。

---
由于是无限次操作，我们可以对于两个值不同的元素 $a_x,a_y$ 进行 $[x,y]$ 操作。在进行若干次操作之后，容易发现所有值相同，为 $a_1\&a_2\&a_3\&\cdots\&a_n$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[105];
int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int ans=a[1];
		for(int i=2;i<=n;i++) ans&=a[i];
		cout<<ans<<endl;
	}
} 
```

---

