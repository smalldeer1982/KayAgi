# Shuffle Party

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ . Initially, $ a_i=i $ for each $ 1 \le i \le n $ .

The operation $ \texttt{swap}(k) $ for an integer $ k \ge 2 $ is defined as follows:

- Let $ d $ be the largest divisor $ ^\dagger $ of $ k $ which is not equal to $ k $ itself. Then swap the elements $ a_d $ and $ a_k $ .

Suppose you perform $ \texttt{swap}(i) $ for each $ i=2,3,\ldots, n $ in this exact order. Find the position of $ 1 $ in the resulting array. In other words, find such $ j $ that $ a_j = 1 $ after performing these operations.

 $ ^\dagger $ An integer $ x $ is a divisor of $ y $ if there exists an integer $ z $ such that $ y = x \cdot z $ .

## 说明/提示

In the first test case, the array is $ [1] $ and there are no operations performed.

In the second test case, $ a $ changes as follows:

- Initially, $ a $ is $ [1,2,3,4] $ .
- After performing $ \texttt{swap}(2) $ , $ a $ changes to $ [\underline{2},\underline{1},3,4] $ (the elements being swapped are underlined).
- After performing $ \texttt{swap}(3) $ , $ a $ changes to $ [\underline{3},1,\underline{2},4] $ .
- After performing $ \texttt{swap}(4) $ , $ a $ changes to $ [3,\underline{4},2,\underline{1}] $ .

Finally, the element $ 1 $ lies on index $ 4 $ (that is, $ a_4 = 1 $ ). Thus, the answer is $ 4 $ .

## 样例 #1

### 输入

```
4
1
4
5
120240229```

### 输出

```
1
4
4
67108864```

# 题解

## 作者：Alice2012 (赞：3)

我们不妨只观察元素 $1$ 的下标对应情况。

初始时下标为 $1$，然后被下标为第一个大于 $1$ 且是 $1$ 的倍数的元素，也就是下标为 $2$ 的元素换走；接着被下标为 $4,8,\dots,2^k$ 的元素换走。

那么，这个下标最后被换到了哪里呢？当然是小于等于 $n$ 的最大的 $2$ 的次幂。

于是我们找到这个数并输出就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,x;
int Fpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)
			ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>x;
		int p=log2(x);
		cout<<Fpow(2,p)<<"\n";
		//log2(x)向下取整后的数p再进行2的次幂操作就是小于等于x的最大的2的次幂 
		//总复杂度O(log n),可过 
	}
	return 0;
}
```

---

## 作者：joker_opof_qaq (赞：2)

### 题目大意

给定一个长度为 $n$ 的序列，使得 $a_i=i$，且 $j$ 是 $a_i$ 最大且不等于 $a_i$ 的因数，若交换 $a_i$ 和 $a_j$，求 $a_1$ 换完后的位置。

### 解题做法

不妨先枚举几个试试看：

- 当 $i=2$ 时，$a_1$ 到了 $a_2$ 。
- 当 $i=3$ 时，$a_2$ 不会换。
- 当 $i=4$ 时，$a_2$ 会换到 $a_4$。

……

此时，我们来推理一下，我们知道一个数 $n$ 的最大除本身外的因数最大为 $\frac{n}{p}$ 且 $p$ 为除了 $1$ 最小的因数，发现一直是 $2$，则答案就是小于 $n$ 的 $2$ 的整数次幂。

---

## 作者：lyh0217 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1937A)

### 题意

给定一个长度为 $n$ 的序列 $a$，使 $a_i=i$，从 $2$ 到 $n$ 遍历 $a_i$（注意：不是从 $1$ 开始的），定义 $j$ 为是 $a_i$ 最大且不等于 $a_i$ 的因数，交换 $a_i$，$a_j$，求操作后原 $a_1$ 在哪个位置。

### 思路

先按题意模拟：

+ 当 $i=2$ 时，$a_1$，$a_2$ 交换，原 $a_1$ 位置为 $2$。

+ 当 $i=4$ 时，$a_2$，$a_4$ 交换，原 $a_1$ 位置为 $4$。

+ 当 $i=8$ 时，$a_4$，$a_8$ 交换，原 $a_1$ 位置为 $8$。

+ ……

我们发现，每次会让原 $a_1$ 的位置都会到上一次乘 $2$ 的位置。因为我们发现，每次找到是 $a_i$ 最大且不等于 $ a_i$ 的因数就是除了一个 $a_i$ 比 $1$ 大的能整除 $a_i$ 的最小数，而比 $1$ 大最小数的就是 $2$，所以，每次就会刚好让原 $a_1$ 的位置都会到上一次乘 $2$ 的位置。

所以答案就是比 $n$ 小的最大的 $2$ 的次幂啦！

注意：

1.是多测。

2.要开 long long。

时间复杂度：$O(T\log n)$。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long x,s=1; //10年oi一场空，_____________。
		cin>>x;
		while(2ll*s<=x) 
		{
			s*=2;
		}
		cout<<s<<endl;
	}
	return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题目大意

给你一个长度为 $n$ 的整数序列，$j$ 为 $a_i$ 除本身之外最大的因数。会交换 $a_i$ 和 $a_j$，求最后 $1$ 是在哪一个位置。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1937A)

特别的，如果 $n=1$，直接输出 $1$。

对于接下来的数据，我们可以做一下模拟，模拟 $n=4$：

- 第一次：`1 2 3 4`（初始队列，不换）。
- 第二次：`2 1 3 4`（可发现仅有第 $1$ 和第 $2$ 个元素交换，$1$ 换到了第 $2$ 个位置）。
- 第三次：`3 1 2 4`（位置仍然和上一步的一样，但是其余的元素变换）。
- 第四次：`3 4 2 1`（位置乘以 $2$）。

我们可以看一下，一次 $1$ 的位置为 $1$，之后，只有第 $2$ 次、第 $4$ 次变换了，为什么是这样呢？

由于对于每一次操作时，对于 $a_i$ 而言，$j$ 为 $a_i$ 最大的除本身之外的因数，$j\le \frac{1}{2}a_i$，交换时，交换 $a_i$ 和 $a_j$。所以，用最极端的方法，对于任意整数 $a_i$，直接换到某一个位置上，这个位置就是 $2$ 一直乘上去的一个数字（可以表示为 $2^k$）。那么对于每一组数据，答案得到论证，就是最大的不大于 $n$ 的 $2$ 的整数次幂了。

参考代码：

```
#include <bits/stdc++.h>
#define int long long//注意，数据有可能会爆int，所以一定要用更大的范围。
using namespace std;
int t,a;
int er (int n) {//算出 2^n 的值。
	int ans=1;
	for (int i=1;i<=n;i++) ans*=2;
	return ans;
}
void calc (int n) {
	if (n==1) cout<<"1\n";
	else {
		int k=0;
		while (er (k)<=n) k++;
		cout<<er (k-1)<<"\n";
	}
}
inline int read () {int s=0,w=0;char c=getchar ();while (!isdigit (c)){w|=(c=='-');c=getchar ();}while (isdigit (c)) {s=(s<<1)+(s<<3)+(c^48);c=getchar ();}return w?-s:s;}
inline void write (int x) {if (x<0) putchar ('-'),x=-x;if (x>9) write (x/10);putchar (x%10|48);}
signed main() {
    cin>>t;
    while (t--) {
    	cin>>a;
    	calc (a);
	}
	return 0;
}
```

---

## 作者：xujingyu (赞：0)

非常玄学的题。

首先，题意是对于每个 $a_i$，设 $j$ 是 $a_i$ 最大的且不等于自己的因数，交换 $a_i$ 与 $a_j$。求交换完数字 $1$ 在哪个位置。

那么也就是说，当 $n=4$ 时，交换过程是这样的：

* 第一个数交换完：`1 2 3 4`；
* 第二个数交换完：`2 1 3 4`；
* 第三个数交换完：`3 1 2 4`；
* 第四个数交换完：`3 4 2 1`；

所以答案就是 $4$。

也就是说：

* 第一次交换：对于一个 1，它会被交换当且仅当该数是质数；
* 第二次交换：对于一个 1，它会被交换当且仅当该数最大因数是第一个质数；
* 第三次交换：对于一个 1，它会被交换当且仅当该数的最大因数是最大因数是第一个质数的数；
* ……

看到这题~~首先开始打表~~：

```cpp
//打表代码
#include <bits/stdc++.h>
using namespace std;
int a[65],last,yin;
signed main()
{
	for(int n = 1;n <= 64;n++)
	{
		for(int i = 1;i <= n;i++) a[i] = i;
		last = 1;
		for(int i = 2;i <= n;i++)
		{
			for(int j = i - 1;j >= 1;j--)
			{
				if(i % j == 0)
				{
					yin = j;
					break;
				}
			}
			if(a[yin] == 1) last = i;
			else if(a[i] == 1) last = yin;
			swap(a[yin],a[i]);
		}
		printf("%d ",last);
	}
	return 0;
}
```

得到了当 $n=1$ 到 $64$ 时的答案：

```cpp
1
2 2
4 4 4 4
8 8 8 8 8 8 8 8
16 16 16 16 16 16 16 16 16 16 16 16 16 16 16 16
32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32
64...
```

发现每个答案都是 $2$ 的幂次方，排列状态就是 $1$ 个 $2^0$，$2$ 个 $2^1$，$4$ 个 $2^2$，以此类推。

所以答案就是距离 $n$ 最近的 $2$ 的幂……

所以代码就出来了……

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,mi;
signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		mi = 1;
		while(mi < n) mi *= 2;//枚举2的幂
		printf("%d\n",(mi == n)?mi:mi / 2);//若等于n,则无需除以二
	}
	return 0;
}
```

---

## 作者：qusia_MC (赞：0)

这题代码难度入门级别，主要是思路。

为了方便讲述，以下称“因数”为最大不等于本身的因数

## 思路

分析就不打了，看翻译去。

首先，如果 $n=1$ 那么输出 $1$ 就行了。

我们先看第一次 $1$ 会被换到哪里。

容易发现，第一个 $\ge 1$ 的质数（只有质数 $≠$ 本身的最大因数为 $1$）为 $2$，则第一次交换后就是：

$2,1,3,4,5…n$。

然后，我们去找第一个有 $2$ 这个因数的数。发现是 $4$，则交换。

……

------

我们会发现，每次交换的时候的 $j$ 都是 $2$ 的整数幂。

怎么证明呢？

对于第 $k$ 次交换的 $i=2^k$，我们可以找到下一个因数为 $2^k$ 的数就是 $2^k\times 2$。（$\times 1$ 就是本身了）

所以，对于任意整数 $n$，其题目中的答案为最后一个 $k$ 满足：

- $k\in N^+$

- $2^k\le n$ 且 $2^{k+1}>n$。

答案就是 $2^k$。

最后输出就行了，时间复杂度 $O(\log n)$，总体时间复杂度 $O(T\log n)$。能通过。
 ## CODE
 ```
 #include<bits/stdc++.h>
using namespace std;
int main()
{
    int T,n,a[114514],ans=0,i;
    cin>>T;
    while(T--)
    {
        cin>>n;
        i=1;
        if(n==1)cout<<"1\n";
        else
        {
        while(pow(2,i)<=n)i++;//找到第一个2^i＞n的i
        cout<<(long long)pow(2,i-1)<<"\n";//输出
        }
    }
    return 0;
}
```

---

