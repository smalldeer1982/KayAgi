# XOR Sequences

## 题目描述

You are given two distinct non-negative integers $ x $ and $ y $ . Consider two infinite sequences $ a_1, a_2, a_3, \ldots $ and $ b_1, b_2, b_3, \ldots $ , where

- $ a_n = n \oplus x $ ;
- $ b_n = n \oplus y $ .

Here, $ x \oplus y $ denotes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operation of integers $ x $ and $ y $ .

For example, with $ x = 6 $ , the first $ 8 $ elements of sequence $ a $ will look as follows: $ [7, 4, 5, 2, 3, 0, 1, 14, \ldots] $ . Note that the indices of elements start with $ 1 $ .

Your task is to find the length of the longest common subsegment $ ^\dagger $ of sequences $ a $ and $ b $ . In other words, find the maximum integer $ m $ such that $ a_i = b_j, a_{i + 1} = b_{j + 1}, \ldots, a_{i + m - 1} = b_{j + m - 1} $ for some $ i, j \ge 1 $ .

 $ ^\dagger $ A subsegment of sequence $ p $ is a sequence $ p_l,p_{l+1},\ldots,p_r $ , where $ 1 \le l \le r $ .

## 说明/提示

In the first test case, the first $ 7 $ elements of sequences $ a $ and $ b $ are as follows:

 $ a = [1, 2, 3, 4, 5, 6, 7,\ldots] $

 $ b = [0, 3, 2, 5, 4, 7, 6,\ldots] $

It can be shown that there isn't a positive integer $ k $ such that the sequence $ [k, k + 1] $ occurs in $ b $ as a subsegment. So the answer is $ 1 $ .

In the third test case, the first $ 20 $ elements of sequences $ a $ and $ b $ are as follows:

 $ a = [56, 59, 58, 61, 60, 63, 62, 49, 48, 51, 50, 53, 52, 55, 54, \textbf{41, 40, 43, 42}, 45, \ldots] $

 $ b = [36, 39, 38, 33, 32, 35, 34, 45, 44, 47, 46, \textbf{41, 40, 43, 42}, 53, 52, 55, 54, 49, \ldots] $

It can be shown that one of the longest common subsegments is the subsegment $ [41, 40, 43, 42] $ with a length of $ 4 $ .

## 样例 #1

### 输入

```
4
0 1
12 4
57 37
316560849 14570961```

### 输出

```
1
8
4
33554432```

# 题解

## 作者：Lu_xZ (赞：7)

**B		\*949**

如果 $[l, r] \oplus x= [l', r'] \oplus y$，则 $[l, r]= [l', r'] \oplus(x\oplus y)$。

令 $v = (x\oplus y)$，即求最长的 $[l, r]$ 使得异或上 $v$ 后依然连续。

如果 $v = abc100000$，任意 $l = a'b'c'100000, r = a'b'c'111111$ 一定是合法且最长的，长度为 $\text{lowbit}(v)$。

---

## 作者：Little_x_starTYJ (赞：6)

### 解题思路
根据异或的性质，$a\oplus b \oplus c = c\oplus b \oplus a = b\oplus a \oplus c$，也就是说异或满足交换律。

那题目要我们求出一个最大的 $m$，使得 $i\oplus x = i \oplus y,1\le i \le m$。

由于异或满足 $1\oplus 1 = 0,1\oplus 0 = 1$，所以我们可以直接计算出答案 $\text{lowbit}(x\oplus y)$。

为什么是这样呢？首先，$\text{lowbit}(k)$ 计算的是在 $(k)_2$ 中最低位的 $1$ 及其后面的所有的 $0$ 所组成的数的值。

那么这道题目中，需要满足 $i \oplus x = i \oplus y,1\le i \le m$，而 $x\neq y$，因为异或运算满足两数相同为 $0$，不同为 $1$，所以我们只需要计算出 $x \oplus y$ 的最低位的 $1$ 是多少即可，这个 $1$ 即 $x,y$ 第一个不相同的地方。

结合式子，如果 $(x)_2,(y)_2$ 的第 $j$ 位不同，那么 $i \oplus x,i \oplus y$ 的第 $j$ 位也不同，因此，我们只需要计算出 $\text{lowbit}(x \oplus y)$ 即可。

CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int lowbit(int x) {
	return x & (-x);
}
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int x, y;
		cin >> x >> y;
		cout << lowbit(x ^ y) << endl;
	}
	return 0;
}

```

---

## 作者：liaoxingrui (赞：3)

## Content

给你两个不同的非负整数 $x$ 和 $y$，有两个数组 $a$ 和 $b$。

其中 $a_i = i \oplus x , b_j = j \oplus y$，求 $a$ 和 $b$ 的最长公共子序列的长度。

## Solution

最长的公共子序列会从 $i = x$ 和 $j = y$ 的这种情况（算出来都为 $0$）下开始，而到在二进制下 $x$ 和 $y$ 第一个位置不相等的时候就会结束。因为异或是相等为 $0$，不等为 $1$，则答案就是 $x \oplus y$ 末尾第一个 $1$ 代表的数字，相当于 $\operatorname{lowbit}(x \oplus y)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
inline int lowbit(int x){
	return (-x)&x;
}
int main(){
	cin>>n;
	while(n--){
		cin>>x>>y;
		cout<<lowbit(x^y)<<endl;
	}
	return 0;
}
```

---

## 作者：Scean_Tong (赞：3)

### 题目

求两个无穷序列 $a$ 和 $b$ 的最长公共子序列的长度，其中 $a_n = n \oplus x$ 和 $b_n = n \oplus y$。

### 思路

观察异或运算的性质：

1. $a \oplus a = 0$，任何数和自己异或结果为 $0$。
2. $0 \oplus a = a$，任何数和 $0$ 异或结果为这个数本身。

考虑两个数 $a$ 和 $b$ 进行异或操作后的结果。根据异或运算的性质，如果 $a \oplus b = c$，那么 $b \oplus c = a$ 以及 $a \oplus c = b$。

直接枚举的话如果存在某个 $i$，使得 $a_i = b_j$，那么我们就找到了一个公共元素。接着可以继续比较 $a_{i+1}$ 和 $b_{j+1}$ 是否相等，以此类推，就能求出最长公共子序列。但是这样做肯定会超时，所以考虑用异或的性质来优化。

先说答案，最长公共子序列的长度为 ``lowbit(x^y)`` 这是什么呢？相信学过树状数组的同学们都知道这玩意是用来找一个数二进制下末尾的 $1$。

接下来，考虑 $x$ 和 $y$ 进行异或操作后的结果 $x \oplus y$。$x \oplus y$ 中的每一位为 $1$，表示 $x$ 和 $y$ 在该位上是不同的。因此，$x \oplus y$中最低位的 $1$，标志着 $x$ 和 $y$ 不同的最低位。

因此，``lowbit(x^y)``表示 $x$ 和 $y$ 不同的最低位的位置，即公共子序列的长度。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int lowbit(int x){
	return x&(-x);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		int x,y;
		cin>>x>>y;
		cout<<lowbit(x^y)<<'\n';		
	} 
	return 0;
}
```

---

## 作者：ny_Dacong (赞：2)

# 思路

~~橙题啊，怎么题解说的都不是人话……~~

这是一篇说人话的题解，也就是说本题解以通俗为主，证明可能不是很严谨，而且语言也比较啰嗦。请大佬轻喷。

题目要求 $a_i = b_j , a_{i+1} = b_{j+1} \dots a_{i+m-1} = b_{j+m-1}$，那我们分析一下什么时候 $a_i = b_j$。

因为 $a_i = i \oplus x,b_i = i \oplus y$，可以发现 $i = i$，那么可能导致 $a_i \not = b_i$ 的因素就是 $x,y$。

我们设 $X[i]$ 表示整数 $X$ 在二进制下从右往左数的第 $i$ 位（从 $1$ 开始）。

首先提一个定理：

>如果 $X = Y$，那么 $X[1] = Y[1],X[2] = Y[2] \dots$。

看回这道题。因为 $a_i = b_i$，所以 $a_i[1] = b_i[1],a_i[2] = b_i[2] \dots a_i[N] = b_i[N]$。又因为 $i = i$，所以 $x[1] = y[1],x[2] = y[2] \dots x[N] = y[N]$ 才可以保证 $a_i = b_i$。

也就是说，我们需要找一个最大的 $N$，满足 $x[1] = y[1],x[2] = y[2] \dots x[N] = y[N]$。而答案就是 $2^N$。

---

还是不懂？举个例子：

以第三组数据为例：

$$x = (57)_2 = 111001$$

$$y = (37)_2 = 100101$$

假如此时 $i = (111)_2$，那么 $i \oplus x$ 的结果 $a_i$ 是 $(110)_2$，$i \oplus y$ 的结果 $b_i$ 是 $(010)_2$。

发现了吗？此时 $a_i[1] = b_i[1],a_i[2] = b_i[2],a_i[3] \not = b_i[3]$。原因就在于 $x[1] = y[1],x[2] = y[2],x[3] \not = y[3]$。这样异或下来就会导致对应的位不同。

---

为什么答案是 $2^N$？因为 $i$ 的取值可以是 $(\begin{matrix}\underbrace{000 \dots 0} \\ \text{共} N \text{个} 0 \end{matrix})_2$ 到 $(\begin{matrix}\underbrace{111 \dots 1} \\ \text{共} N \text{个} 1 \end{matrix})_2$ 这个区间中的所有的数。而在这个区间中的数一共有 $2^N$ 个（每一位都有两种可能的取值）。所以答案是 $2^N$。

---

怎么求 $N$？

其实也可以用异或的性质来解决这个问题。若两数在二进制下某一位相同，则运算后这一位的结果为 $0$，否则为 $1$。

也就是说我们只需要找出 $x \oplus y$ 的结果从右往左看的第一个 $1$ 的位置 $-1$ 即可。这个值就是 $N$ 的值。

那么如何快速求出这个值呢？这就需要用到树状数组常用的 `lowbit` 函数。它的作用跟我们的需求完全符合。

这里就不再推导 `lowbit` 函数了。感兴趣的读者自行查阅 `lowbit`。

`lowbit` 函数传入一个数 $M$，返回 $M \& (-M)$。（此处 $\&$ 表示按位与，根据 [oi-wiki](http://oi-wiki.com/math/bit/#%E4%B8%8E%E6%88%96%E5%BC%82%E6%88%96)，表达按位与的数学符号应该是 `\&`）

# AC 代码

因为 RMJ 死了，所以放上 CF 的 AC 链接：<https://codeforces.com/contest/1979/submission/280559516>。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,y;
int lowbit(int num){
    return num&-num;
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lowbit(x^y));
    }
    return 0;
}
```

码字不易求过。

---

## 作者：_Dynamic_Programming (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1979B)
#### 这道题是一道不难猜出答案的题，根据样例，我们就能推断出来做法。
# 思路
我们可以直接看样例（~~因为我做题时根本没有思路~~），在经过一番尝试后：
> 1. $0 \oplus 1 = (1)_2$，$1 = (1)_2$
> 2. $12 \oplus 4 = (1000)_2$，$8 = (1000)_2$
> 3. $57 \oplus 37 = (11100)_2$，$4 = (100)_2$
> 4. $316560849 \oplus 14570961 = (10010000000000000000000000000)_2$，$33554432 = (10000000000000000000000000)_2$

于是，我们便发现了规律：答案是 $x \oplus y$ 二进制的最后一位 $1$ 及其后面的所有 $0$ 所构成的数。

# lowbit 函数
## 前置芝士
原码、反码、补码
## 概述

lowbit 函数其实就是指 `x & (-x)` 的值。

众所周知，c++ 中，数都是以补码的形式出现的。

而 `x & (-x)` 就是 $x$ 二进制的最后一位 $1$ 及其后面的所有 $0$ 所构成的数。

例如：当 $x = 10$ 时：\
$10 = (1010)_2$\
$-10 = (0110)_2$\
(此处均为补码)

而 `10 & -10` 便会等于 $(0010)_2$，刚好等于 $10$ 二进制的最后一位 $1$ 及其后面的所有 $0$ 所构成的数。

所以我们会这么定义 lowbit 函数：
```cpp
int lowbit(int x) {return (x & -x);}
```

# Code
懂了之后，代码便好写了，代码如下：
```c++
#include <bits/stdc++.h>
using namespace std;
int lowbit(int x) {return (x & -x);} //定义lowbit函数
int t, x, y;
int main()
{
    cin >> t; 
    while(t--)
    {
	    scanf("%d%d", &x, &y);
	    int ans = lowbit(x ^ y); //使用lowbit函数计算
	    cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：abc1234shi (赞：0)

看到本题的数据范围，可以猜想这是一道结论题。

题目大意：给定 $a$ 序列和 $b$ 序列，求最长公共子序列。

再看看输出样例，都是 $2^n$。

于是我们可以猜想，所有数据的结果都是 $2^n$ 。

看 $ 0 ⊕ 1 = 1,12 ⊕ 4 = 8,57⊕ 37 = 28$。

而输出分别为 $1,8,4$，满足我们的猜想。

通过观察，可以发现输出：为两个输入的异或和的二进制最右边的 $1$ 的大小。

所以结果只需要将 $x$ 和 $y$ 按位异或，再将结果按位取反，不就是我们刚刚找的：结果等于 $x$ 和 $y$ 异或和的二进制最右边的 $1$ 的大小吗？所以结果其实就等于 `(x ^ y) & (-(x ^ y))`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4;
int t,x,y,a[N+100];
int lowbit(int x){
	int ans=1;
	while(!(x&1)){
		x>>=1;
		ans<<=1;
	}
	return ans;
}
void solve(){
	cin>>x>>y;
	int z=x^y;
	cout<<lowbit(z)<<endl;
}
signed main(){
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：floodfill (赞：0)

## CF1979B XOR Sequences 题解
### 题目大意
给两个不等的非负整数 $x,y$，构造序列
$$a_1,a_2,a_3,…,a_\infin (a_n=n \operatorname{xor} x)$$
和
$$b_1,b_2,b_3,…,b_\infin (b_n=n \operatorname{xor} y)$$
求出 $a$ 和 $b$ 的最长公共子序列的长度。形式化地，你应当找出一个最大的 $m$ 使得 
$$a_i=b_j,a_{i+1}=b_{j+1},…,a_{i+m-1}=b_{j+m-1}$$
对于某个 $i,j≥1$ 存在。
### 大致思路
做题先仔细审题面和样例。
在二进制下来看数据，不难注意到答案是 $(x\operatorname{xor} y)_2$ 的最后一位 $1$ 和后面所有的 $0$ 构成的数。我们引入一个函数 $\operatorname{lowbit}(x)$，一般地，
$$\operatorname{lowbit}(x)\Leftrightarrow x \operatorname{xor} -x$$
所以，事实上
$$\operatorname{lowbit}(x \operatorname{xor} y)\Leftrightarrow (x \operatorname{xor} y)\operatorname{and}\space -(x \operatorname{xor} y) $$
代码不长。
###  _code_

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T;
int Lowbit(int X){
	return X&-X;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		int x,y;
		cin>>x>>y;
		cout<<Lowbit(x^y)<<endl;
	}
	return 0;
}
```

---

## 作者：zhoujunchen (赞：0)

做题思路
----

这道题很容易猜出答案，首先看样例。
   
>  $0\oplus1=(1)_2,1=(1)_2$        
> $57 \oplus 37= (0001 1100)_2,4=(100)_2$    
> $316560849 \oplus 14570961=(0001 0010 0000 0000 0000 0000 0000 0000)_2,33554432=(0010 0000 0000 0000 0000 0000 0000)_2$

不难发现结果就是  $\operatorname{lowbit(x \oplus y)}$。

证明：

异或运算满足结合律和交换律，即 $a\oplus b \oplus c=a\oplus c \oplus b=b\oplus c\oplus a$。

若 $x\oplus y$ 每一位是 $1$，那就表示 $x$ 和 $y$ 在二进制下每一位都不同。所以 $x\oplus y$ 的最低位的 $1$ 代表着 $x$ 和 $y$ 不同的最低位。

所以结果就是 $\operatorname{lowbit(x \oplus y)}$。

code:


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int lowbit(int x){
    return x&-x;
}
signed main(){
    int n;
    cin>>n;
    while(n--){
        int x,y;
        cin>>x>>y;
        cout<<lowbit(x^y)<<"\n";
    }
    return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1979B)

# 思路：
考虑公共子序列如何形成。

假设现在满足 $x \oplus n = y \oplus m$。如果想要 $n$，$m$ 自增之后仍然满足条件，那么在自增过程中，$n$，$m$ 的每一个二进制位要么同时改变，要么同时不变。

然后考虑 $n$，$m$ 的一个满足条件的解：$n=x$，$m=y$。我们将 $n$，$m$ 所有相同的位全部变为 $0$，得到 $n$，$m$ 的最小解。

此时 $n$，$m$ 能够自增的次数显然是最多的。如果此时 $n$，$m$ 的二进制低位连续的 $0$ 的个数为 $t_1$，$t_2$，那么答案就是 $2^{\min\{t_1,t_2\}}$。

也就是说，令 $x$，$y$ 从最低位开始的连续相同二进制位的个数为 $t$，那么答案即为 $2^t$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,m,k,ans,a[N],b[N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		ans=0;
		while(((n>>ans)&1)==((m>>ans)&1)){
			ans++;
		}
		cout<<(1ll<<ans)<<endl;
	}
	return 0;
}
```
完结撒花~

---

## 作者：_Tatsu_ (赞：0)

### 思路

观察样例 `12 4`，$12 \oplus 4=(1100)_2 \oplus (100)_2=(1000)_2=8$，毫无头绪。

而 `57 37` 中，$57 \oplus 37=(111001)_2\oplus(100101)_2=(011101)_2=4$。

这么一看，好像有点规律了。

异或后的结果进行 $\text {lowbit}$ 函数的处理，返回值不就对上了吗？

所以我们输入 $x$，$y$，输出 $(x \oplus y)\land(-(x \oplus y))$ 即可。

### 关于 $\text {lowbit}$ 的简要说明

$\text {lowbit} (n)$ 的定义为非负整数 $n$ 在二进制表示下“最低位的 $1$ 及其后面的所有的 $0$”的二进制构成的数值。

我们假设 $n > 0$，设 $n$ 的二进制表示中，第 $k$ 位为 $1$，第 $0$ 至第 $k-1$ 位都为 $0$。

现在我们对 $n$ 的二进制进行取反操作，可以得到 $\neg {n}$ 的二进制中第 $k$ 位为 $0$，第 $0$ 至第 $k-1$ 位都为 $1$，然后我们再将 $n$ 进行加 $1$ 操作，可以得到一个结果为 $\neg n+1$ 的第 $k+1$ 位至其最高位都为 $n$ 的二进制表示中相反的数字，然后我们再将 $\neg n+1$ 与 $n$ 进行与运算，就可以得到我们想要的结果了。又因为 $\neg n=-1-n$，所以 $-n = \neg {n+1}$。

### AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define fro for//防手滑
using namespace std;
signed main()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
    int t;
    cin>>t;
    while (t--)
	{
        int x,y;
        cin>>x>>y;
        int xorr=(x^y)&-(x^y);//先异或，再lowbit函数。
        cout<<xorr<<endl;
    }
	return 0;
}
```

---

## 作者：lym12 (赞：0)

可以先枚举是否存在一个 $i$ 使得 $a_i = b_j$，之后再寻找 $a_{i+1} = b_{j+1}$，这样可以找到最长公共子序列。

考虑使用异或的性质优化。不难发现，可以查找再 $x \oplus y$ 中最低位的 $1$，答案也就是这个 $1$ 对应的值，故答案为 $\operatorname{lowbit}(x, y)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    long long T;
    cin >> T;
    while (T --){
        long long a, b;
        cin >> a >> b;
        cout << (a ^ b) & (-(a ^ b)) << '\n';
    }
}
```

---

## 作者：z_yq (赞：0)

### 题目
给定 $a$ 序列和 $b$ 序列，求最长公共子序列

### 思路
翻译一下，发现题目其实就是求 $[l,r] \oplus x = [l',r'] \oplus y$ 则可以演变成 $[l,r] = [l',r'] \oplus {(x \oplus y)}$ 所以就是求 $[l,r] \oplus {(x \oplus y)} = [l,r]$，则我们就是求 ${(x \oplus y)}$ 的最低位往下的所有数的总数，则答案就是 ${(x \oplus y)}$ 的二进制位的最低位，这里来解释一下为什么：我们假设这个 ${(x \oplus y)}$ 的二进制形式为：${(A10000)_2}$（注意，这里的 $A$ 是指得一个由 $0$ 和 $1$ 构成的二进制串），所以我们取 ${(x \oplus y)}$ 的二进制位为1的最低位作为答案时，我们可以构造 $[l,r] = [0,{(x \oplus y)}-A-1]$ 且 $[l',r'] = [{(A10000)_2},{(A10000)_2}+{(10000)_2}]$ 即可，因为 $[l',r'] \oplus {(x \oplus y)}$ 高位的 $A$ 就被消掉了，故满足要求。

### Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) x&(-x)
using namespace std;
int main()
{
    ll T;
    cin>>T;
    while(T--)
    {
        ll a,b;
        cin>>a>>b;
        cout<<(lowbit((a^b)))<<endl;
    }
    return 0;
}
```

---

## 作者：ZhongYuLin (赞：0)

一道注意力题。

注意到样例答案形式均为 $2^n$，猜想答案形式必为 $2^n$。

注意到题目中存在异或和，考虑将两个值异或起来（以下二进制省略高位 $0$）：

1. $0 \operatorname{xor} 1=\texttt{(1)}_2$，答案：$1=\texttt{(1)}_2$。

2. $12 \operatorname{xor} 4=\texttt{(1000)}_2$，答案：$8=\texttt{(1000)}_2$。

3. $57 \operatorname{xor} 37=\texttt{(11100)}_2$，答案：$4=\texttt{(100)}_2$。

4. $316560849 \operatorname{xor} 14570961=\texttt{(10010000000000000000000000000)}_2$，答案：$33554432=\texttt{(10000000000000000000000000)}_2$。

注意到答案实际就是异或值的最低位 $1$，对应到代码为 ：

```cpp
x^=y
1<<__lg(x&-x)
```

考虑它为什么是对的。题目要求出最长公共子区间。令两个序列的子区间都从为 $0$ 的项开始，接下来的、上述所求出的数的这么多项必然相等，因为低位的改变相等，而高位不产生变化。于是答案成立。那为什么最优呢？因为假使不从 $0$ 开始，必然答案不优，因为低位的变化上界不会比从 $0$ 开始更大。

---

## 作者：zengziqvan (赞：0)

考虑性质，发现对于给定的数 $a,b$，设一个数 $cnt$ 表示其二进制下后 $k$ 位（从第 $0$ 位开始）全部相同的最大的 $k$，则答案为 $2^{cnt}$。

比如对于样例 $57\;37$：

$57:111001$

$37:100101$

其后的 $2$ 位 $01$ 相等且第 $2$ 位不相等，则答案为 $2^2=4$。

>证明：
>
>设 $a\oplus x=b\oplus y$ 且 $a\oplus (x-1)\ne b\oplus (y-1)$。
>
>则这样的 $x$ 与 $y$ 一定是后面 $cnt$ 位全为 $0$、其余位单独构造使其满足上述条件的数字。
>
> 那么根据定义，$a,b$ 的第 $cnt$ 位一定不相等，这等价于如果加上大于等于 $2^{cnt}$ 的数字则会发生进位，影响前面构造的结果。
>
>所以加上的数字属于闭区间 $[0,2^{cnt}-1]$，一共 $2^{cnt}$ 个，即长度为 $2^{cnt}$。
>
>证毕。

所以我们直接扫描二进制位找 $cnt$ 即可，时间复杂度 $\operatorname{O}(\log V)$，其中 $V$ 为值域。

```c++
void solve() {
	ll a,b,ans=0;
	cin>>a>>b;
	for(int i=0;i<32;++i) {
		if((a>>i&1)!=(b>>i&1)) break;
		ans++;
	} 
	ans=(1<<ans);
	cout<<ans<<"\n";
}
```

---

## 作者：ttq012 (赞：0)

考虑打表猜结论。从低到高枚举 $x$ 和 $y$ 在二进制下每一位的值，设当前枚举到的是第 $i$ 位。若 $x$ 的第 $i$ 为位和 $y$ 的第 $i$ 位不同，那么答案就是 $2^i$。

因为 $x\neq y$，所以肯定至少存在一个 $i$ 使得 $x$ 的第 $i$ 位和 $y$ 的第 $i$ 位的值不同。

时间复杂度为 $O(\log n)$。

```cpp
auto main() [[O3]] -> signed {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int x, y;
        cin >> x >> y;
        F(i, 0, inf) {
            if ((x >> i & 1) != (y >> i & 1)) {
                cout << (1ll << i) << '\n';
                break;
            }
        }
    }
}
```

---

