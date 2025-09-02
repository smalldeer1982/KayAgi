# Sequence Transformation

## 题目描述

Let's call the following process a transformation of a sequence of length $ n $ .

If the sequence is empty, the process ends. Otherwise, append the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) (GCD) of all the elements of the sequence to the result and remove one arbitrary element from the sequence. Thus, when the process ends, we have a sequence of $ n $ integers: the greatest common divisors of all the elements in the sequence before each deletion.

You are given an integer sequence $ 1, 2, \dots, n $ . Find the lexicographically maximum result of its transformation.

A sequence $ a_1, a_2, \ldots, a_n $ is lexicographically larger than a sequence $ b_1, b_2, \ldots, b_n $ , if there is an index $ i $ such that $ a_j = b_j $ for all $ j < i $ , and $ a_i > b_i $ .

## 说明/提示

In the first sample the answer may be achieved this way:

- Append GCD $ (1, 2, 3) = 1 $ , remove $ 2 $ .
- Append GCD $ (1, 3) = 1 $ , remove $ 1 $ .
- Append GCD $ (3) = 3 $ , remove $ 3 $ .

We get the sequence $ [1, 1, 3] $ as the result.

## 样例 #1

### 输入

```
3
```

### 输出

```
1 1 3 ```

## 样例 #2

### 输入

```
2
```

### 输出

```
1 2 ```

## 样例 #3

### 输入

```
1
```

### 输出

```
1 ```

# 题解

## 作者：Apojacsleam (赞：7)

# C. Sequence Transformation
	time limit per test: 2 seconds
	memory limit per test: 256 megabytes
	input: standard input
	output: standard output
Let's call the following process a transformation of a sequence of length 
n
.

If the sequence is empty, the process ends. Otherwise, append the greatest common divisor (GCD) of all the elements of the sequence to the result and remove one arbitrary element from the sequence. Thus, when the process ends, we have a sequence of 
n
 integers: the greatest common divisors of all the elements in the sequence before each deletion.

You are given an integer sequence 1,2,...n. Find the lexicographically maximum result of its transformation.

A sequence a[1],a[2],...,a[n] is lexicographically larger than a sequence b[1],b[2],...,b[n], if there is an index i such that a[j]=b[j] for all j < i , and a[i] > b[i].

http://codeforces.com/contest/1059/problem/C

### 【题解】
	首先有一个显而易见的结论：对于任意排列，b序列中的前n/2个数总是1。
    原因是相邻的两个数互质。
    现在我们来考虑一个长度大于3的排列，怎样才能将b序列的字典序最大。
    根据字典序的定义，我们需要最大化每一次进入队列的gcd。
    即，当前最大就是整体最好的选择。
    那么我们对于任意两个相邻的数，都有一个选择：删除其中的奇数或删除其中的偶数。
    我们应该全部删除奇数或者全部删除偶数，不然就会有两个数相邻，从而出现gcd=1使得答案不优。
    如果我们删除偶数，我们就会发现有ai=1使得这个序列的gcd=1而使得答案不优。
    所以我们对于每个序列，都要删除奇数，使得gcd*=2。
    观察操作后的序列
    	a{2,4,...,(n&1)?(n-1):(n)}
    我们可以将它看成
        a{2*1,2*2,2*3,...,2*(n/2)}
    这样我们就把问题转化成了一个长度为n/2的子问题。
    对于1<=n<=3的序列或长度小于等于3的子问题，题目的样例就是我们想要的结果，特判即可。
    复杂度实际上是O(n)的。
    代码并不难写。
### 【AC代码】
```cpp
/*
	Coded by Apojacsleam
*/
#include<cstdio>
int n,t;
int main()
{
	scanf("%d",&n);t=1;
	while(n>3)
	{
		for(register int i=1;i<=((n+1)>>1);i++) printf("%d ",t);
		n>>=1;t<<=1;
	}
	if(n==3)  printf("%d %d %d",t,t,t*3);
	else if(n==2) printf("%d %d",t,t*2);
	else printf("%d",t);
	return 0; 
}
```
    

---

## 作者：ouuan (赞：1)

考虑规模为 $k$ 的一个问题：$1$ ~ $k$ 的一个排列，求字典序最大的答案序列。

当 $k\le 3$ 时，就是样例；当 $k>3$ 时，为了使答案序列的字典序尽量大，需要删尽量少的数使得 $gcd\neq 1$，此时删掉所有奇数一定是最优的，因为对于任意的 $ k>3,x>2$ 有 $\small\left\lfloor\dfrac{k}{x}\right\rfloor<\left\lfloor\dfrac{k}{2}\right\rfloor$。删掉所有奇数后，剩下的数为都为 $2$ 的倍数（废话...），那么如果将所有数除以二，最优的删数方案是不会变的，而此时剩余的问题被转化成了一个规模为 $\small\left\lfloor\dfrac{k}{2}\right\rfloor$ 的原问题，输出答案时将答案乘二即可。

换句话说，令 $T(k)$ 为 $1,2,3,\cdots,k$ 这个序列的字典序最大的答案序列，那么：$\begin{cases}T(k)=\{1\}\quad(k=1)\\T(k)=\{1,2\}\quad(k=2)\\T(k)=\{1,1,3\}\quad(k=3)\\T(k)=\{1,1,\cdots,1\}(\small\text{共}\left\lceil\dfrac{k}{2}\right\rceil\text{个 1})\normalsize+T\left(\small\left\lfloor\dfrac{k}{2}\right\rfloor\right)\text{的每一项乘二}\normalsize\quad(k>3)\end{cases}$

实现时并不需要递归地实现，详见代码：

```
#include <cstdio>
#include <iostream>

using namespace std;

int n;

int main()
{
    int i,qaq=1;
    
    cin>>n;
    
    while (n>=4)
    {
        for (i=0;i<(n+1)/2;++i)
        {
            cout<<qaq<<' ';
        }
        n/=2;
        qaq*=2;
    }
    
    if (n==3)
    {
        printf("%d %d %d",qaq,qaq,qaq*3);
    }
    
    else if (n==2)
    {
        printf("%d %d",qaq,qaq*2);
    }
    
    else
    {
        printf("%d",qaq);
    }
    
    return 0;
}
```

---

## 作者：iPhoneSX (赞：0)

## 题解
相邻的两个数都是互质的，所以刚开始全部是 $1$，后面才有可能出现比 $1$ 的数，为了让 $1$ 的个数尽可能少，我们把所有奇数删掉，这样有 $\frac{n}{2}$ 个 $1$。后面开始出现 $2$，为了让 $2$ 也尽可能的少，我们把所有非 $4$ 的倍数删掉，这样有 $\frac{n}{4}$ 个 $2$，后面就开始出现 $4$ 了。以此类推，我们每次隔一个数删一个，删到最后一定是字典序最大的序列。

但有一个地方需要注意，如果最后剩下三个数 $x \le 2x \le 3x$，此时如果隔一个删一个，序列就会变成 $x,x,2x$，不如直接按顺序删得到的 $x,x,3x$ 更优。特判一下就好啦。

代码如下：
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define int long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f
#define mod 998244353
#define N 10000005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
int n,t,poww[30],b[N]; 
signed main(){
	poww[0]=1;
	for(int i=1;i<=30;i++){
		poww[i]=poww[i-1]*2;
	}
	read(n);
	int tot=0,ans=0,cnt=0;
	while(n){
		if(n==3){
			b[++cnt]=poww[tot];
			b[++cnt]=poww[tot];
			b[++cnt]=poww[tot]*3;
			break;
		}
		if(n%2==0){
			for(int i=1;i<=n/2;i++){
				b[++cnt]=poww[tot];
			}
		}
		else{
			for(int i=1;i<=(n+1)/2;i++){
				b[++cnt]=poww[tot];
			}
		}
		tot++;
		n=n/2;
	}
	for(int i=1;i<=cnt;i++){
		write(b[i]);
		putchar(' ');
	}
	return 0;
}
``````````````````
其实很简洁的，只是头文件和快读比较长。

---

## 作者：离散小波变换° (赞：0)

非常有趣问题。

## 题解

我们要让答案的字典序最大。注意到答案序列最前面应该都是 $1$，为了让字典序最大，容易想到这两点：

- 要让 $1$ 序列的长度尽量小；
- 要让 $1$ 序列后面那个数字尽量大。这里的“最大”是在 $1$ 序列长度最小的前提上的。

可以发现 $1$ 序列后面那个数字就是删除完若干次操作后整个序列的 $\gcd$。记这个 $\gcd$ 的值为 $d$，那么为了让所有数字的最大公约数是 $d$，至少要删除 $n-\left\lfloor\dfrac{n}{d}\right\rfloor$ 个数字，并且删除的数字最少的唯一方案，就是把那些不是 $d$ 的倍数的数删除。同时，需要删除的数的个数就是 $1$ 序列的长度。

容易发现 $n-\left\lfloor\dfrac{n}{d}\right\rfloor$ 关于 $d$ 是单调不减的。进一步发现，$n-\left\lfloor\dfrac{n}{2}\right\rfloor \le n-\left\lfloor\dfrac{n}{3}\right\rfloor$，$n-\left\lfloor\dfrac{n}{2}\right\rfloor \textcolor{red}{<} n-\left\lfloor\dfrac{n}{4}\right\rfloor$（~~其实是我打表发现的~~），所以 $d$ 的候选只有 $2$ 和 $3$。因为我们还要让 $1$ 序列后面那个数字尽量大，所以出现取等的情况时应该取 $d=3$。

接着注意到，我们按照最优策略使得剩下来的所有数字的 $\gcd$ 为 $d$ 后，这些数字应该恰好为 $1\times d,2\times d,\cdots,\left\lfloor\dfrac{n}{d}\right\rfloor \times d$。无论怎么删除这里面的数字，最大公约数都肯定还是 $d$ 的倍数。于是发现整个问题变成 $n\gets \left\lfloor\dfrac{n}{d}\right\rfloor$ 的子问题了。可以递归求解。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int main(){
    int n = qread(), t = 1;
    while(1){
        if(n == 1){
            printf("%d\n", t); return 0;
        }
        int a = n / 2;
        int b = n / 3;
        if(b >= a){
            up(1, n - b, i) printf("%d ", t);
            n = b, t *= 3;
        } else {
            up(1, n - a, i) printf("%d ", t);
            n = a, t *= 2;
        }
    }
    return 0;
}
```

---

## 作者：是个妹子啦 (赞：0)

### CF1059
最优答案肯定会出现一段$1$，然后出现不为$1$的，这个答案一定为$2$，如果让第一个非$1$的是$3$，必须去掉模$3$剩余系下不为$0$的数，显然需要去掉数所构成的数集是远大于由模二剩余系所确定的数集的。

然后考虑将所有奇数去掉以后局面就会变成一个所有的偶数集，显然此时让集合内所有数都除以二有转化为了前一个问题，同样的方法。

具体实现每次只需要输出当前待删除的数字个数个答案，再将答案乘$2$，集合大小除以$2$即可

剩下三个数字时要特判$1,1,3$比$1,1,2$要优，由样例可知

代码还是比较好写的

---

