# XOR = Average

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$a_1 \oplus a_2 \oplus \dots \oplus a_n = \frac{a_1 + a_2 + \dots + a_n}{n}, $ $  where  $ \\oplus$$$ represents the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

It can be proven that there exists a sequence of integers that satisfies all the conditions above.

## 说明/提示

In the first test case, $ 69 = \frac{69}{1} = 69 $ .

In the second test case, $ 13 \oplus 2 \oplus 8 \oplus 1 = \frac{13 + 2 + 8 + 1}{4} = 6 $ .

## 样例 #1

### 输入

```
3
1
4
3```

### 输出

```
69
13 2 8 1
7 7 7```

# 题解

## 作者：aCssen (赞：7)

### 题意
给你一个整数 $n$，需要你构造出一个序列 $a$ ，满足:
+ $1 \le a_i \le 10^9$
+ $a$ 的异或和等于 $a$ 的平均值。
### Solution
本题需要用到异或的性质: $a \oplus a=0$，$a\oplus 0 =a$。

我们对 $n$ 的奇偶性分情况讨论：
+ $n$ 为奇数，我们只需构造一个 $n$ 个数都相同的序列。令这个数为 $x$，显然 $a$ 的平均值为 $x$，而前 $n-1$ 个数的异或和被两两抵消，所以最终整个 $a$ 的异或和也为 $x$。
+ $n$ 为偶数，此时前面的方法不再适用，因为这偶数个相同数的异或和为 $0$，但 $a$ 中的数一定大于 $0$，则平均值也一定大与 $0$，所以这种方法不满足条件。

	我们可以从一些小数据入手，对于 $n=2$，我们找到了一组解 $a=\lbrace1,3\rbrace$。此时 $a$ 的平均值和异或和都为 $2$。

	对于其他 $n$ 为偶数的情况，就相当于再这组解上增加偶数个数，因为异或和会将增加的数都消掉，所以这些数只要能使平均值不变即可，所以我们可以令这 $n-2$ 个数 都为 $2$，则此时 $a$ 的异或和仍然为 $2$，平均值也依然为 $2$。



综上，我们得到了如下构造方法：
+ 当 $n$ 为奇数时，输出 $n$ 个 $1$。
+ 当 $n$ 为偶数时，先输出 $n-2$ 个 $2$，再输出特解 $1,3$。

然后这题就做完了。
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
typedef long long ll;
const int maxn=2*1e5+5;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=~f+1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
int num[maxn],t,n;
int main(){
	t=read();
	while(t--){
		n=read();
		if(n&1){//n为奇数
			for(int i=1;i<=n;i++) printf("1 ");
			printf("\n");
			continue;
		}
      //偶数
		for(int i=1;i<=n-2;i++) printf("2 ");
		printf("1 3\n");
	}
	return 0;
}
```

---

## 作者：Clyfort (赞：3)

## Description
构造一个 $a$ 序列，使 $a_1 \oplus a_2 \oplus a_3 \oplus \cdots \oplus a_n = \dfrac{sum(a)}{n}$。

## Solution
第一眼看到这道题，我想到的是分情况讨论。

首先看 $n$ 是奇数，我们知道 $x \oplus x = 0$，所以可以想到 $1 \oplus 1 \oplus 1 \oplus \cdots \oplus 1 = \dfrac{1 \times n}{n} = 1$。也就是说，假如 $n$ 是奇数，输出 $n$ 个 $1$ 就可以了。

再来看 $n$ 是偶数，在 $n$ 为奇数的解上稍作修改，因为 $1 \oplus 3 = 2$，所以根据 $n$ 是奇数的思维，就可以想到 $1 \oplus 2 \oplus 2 \oplus \cdots \oplus 2 \oplus 3 = \dfrac{1+2+2+\cdots+2+3}{n} = 2$。

这道题很轻松的就解出来啦！

## Code
```c++
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        int n;
        cin >> n;
        if (n % 2)
        {
            for (int i = 1; i <= n; i ++)
                cout << 1 << " ";
            cout << endl;
        }
        else
        {
            cout << 1 << " ";
            for (int i = 2; i <= n - 1; i ++)
                cout << 2 << " ";
            cout << 3;
            cout << endl;
        }
    }
    return 0;
}
```

---

## 作者：Wind_Smiled (赞：1)

## 题意

构造一个数组 $a$，使满足 $a_1 \oplus a_2 \oplus a_3 \oplus ⋯ \oplus a_n  = \dfrac{a_1 + a_2 + a_3 + ⋯ + a_n}{n}$。

### 分析

已知一个数异或它本身等于 $0$，所以我们选择 `2` 为数组的元素，若序列长度为偶数，则全为 `2`，否则，为了使平均数也等于 $2$，则选用 `1 3`  补充序列，并且 $1 \oplus 3=2$，可以满足题意。

先输出 $n-2$ 个 `2`，然后根据奇偶性判断输出的是 `2 2` 或 `1 3`。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n-2;i++){
			printf("2 ");
		}
		if(n&1){
			printf("2 2\n");
		}
		else{
			printf("1 3\n");
		}
	}
	return 0;
}
```

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1758B)

水。

## 题目描述
给定一个数 $n$，让你随便选用 $n$ 个数构造一个序列 $a$，满足以下条件：
$$a_1 \oplus a_2 \oplus \dots \oplus a_n = \frac{a_1 + a_2 + \dots + a_n}{n}$$
请你输出序列 $a$。

我们可以使用凑 $0$ 法。

如果 $n$ 是奇数，我们就可以输出 $n$ 个 $1$，因为奇数个相同数相异或会等于原来的数，而 $n$ 个 $1$ 相加是 $n$，$n$ 除以 $n$ 等于 $1$，异或和与序列平均值相等。

如果 $n$ 是偶数，那我们就先把 $0$ 给凑出来。这里不能采用全 $1$ 序列，因为如果这样就会出现一个问题：序列平均值不等于序列异或和。所以我们就先采取一下全 $2$ 序列。我们先把 $n-2$ 个 $2$ 输出，那么我们发现这个序列的元素是全 $1$ 序列的两倍，所以平均只应为 $1\times 2=2$。此时我们要用两个数异或等于 $2$，和又要等于 $4$，我们选 $1$ 和 $3$。

总结：    
如果 $n\mod 2=1$，全输出 $1$。    
否则先输出 $n-2$ 个 $2$，再输出 $1$ 和 $3$。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		if(n%2==1) for(register int i=1;i<=n;i++) printf("%d ",1);
		else 
		{
			printf("%d ",1);
			for(register int i=2;i<n;i++) printf("%d ",2);
			printf("%d",3);
		}
		printf("\n");
	}
	return 0;	
}
```

---

## 作者：arrow_king (赞：0)

## 题目大意

构造一个长度为 $n$ 的正整数序列 $a_1,a_2,\dots a_n$，使得 $\dfrac{a_1+a_2+\dots+a_n}{n}=a_1\oplus a_2\oplus\dots\oplus a_n$。

## 思路

$n$ 是奇数的时候很简单，因为 $a\oplus a=0$，所以输出 $n$ 个一样的数就可以了，比如 $1$。

$n$ 是偶数的时候，因为 $a\oplus 0=a$，所以要尽量将奇数个数异或和是 $0$，再接上它们的平均就可以了。最简单的当然是 $1,2,3$，异或和是 $0$，平均数是 $2$。当然可以选用任何满足条件的数对来构造。

时间复杂度 $\mathcal O\left(t\sum n\right)$。

## 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
inline int read() {
	register int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
int t,n;
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		if(n%2==1) {
			for(int i=1;i<=n;i++) printf("1 ");
			putchar('\n');
			continue;
		}
		printf("1 3 ");
		for(int i=1;i<=n-2;i++) printf("2 ");
		putchar('\n');
	}
	return 0;
}

```

---

## 作者：Lyrella (赞：0)

# 题意
给你一个数 $n$，让你构造一个长度为 $n$ 的序列，满足
$$\frac{\sum^n_{i=1}{a_i}}{n}=a_1⊕a_2⊕a_3...⊕a_n$$
请你输出一种构造方案。
# 思路
首先分奇偶讨论。

当 $n$ 为奇数，其实只需要所有数都**一样**就行。为什么呢？因为奇数个相同的数异或就等于**它本身**，而其平均值也为**它本身**。所以随便输出 $n$ 个相同的数就行。

当 $n$ 为偶数，就需要一个 $1$，一个 $3$ 和 $n-2$ 个 $2$即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define Fl(i, l, r) for(int i = l; i <= r; i++)
#define Fr(i, r, l) for(int i = r; i >= l; i--)
using namespace std;
void solve(){
	int n; cin >> n;
	int a[n + 5];
	if(n & 1)Fl(i, 1, n)a[i] = 1;
	else{
		a[1] = 1; a[2] = 3;
		Fl(i, 3, n)a[i] = 2;
	}
	Fl(i, 1, n)cout << a[i] << ' '; cout << '\n';
}
signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T; cin >> T;
	while(T--)solve(); return 0;
}
```

---

