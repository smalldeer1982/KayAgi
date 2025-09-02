# Take a Guess

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556D/63568455333cc0a029d6e5fa4f79ae6dd332397f.png)This is an interactive task

William has a certain sequence of integers $ a_1, a_2, \dots, a_n $ in his mind, but due to security concerns, he does not want to reveal it to you completely. William is ready to respond to no more than $ 2 \cdot n $ of the following questions:

- What is the result of a [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of two items with indices $ i $ and $ j $ ( $ i \neq j $ )
- What is the result of a [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of two items with indices $ i $ and $ j $ ( $ i \neq j $ )

You can ask William these questions and you need to find the $ k $ -th smallest number of the sequence.

Formally the $ k $ -th smallest number is equal to the number at the $ k $ -th place in a 1-indexed array sorted in non-decreasing order. For example in array $ [5, 3, 3, 10, 1] $ $ 4 $ th smallest number is equal to $ 5 $ , and $ 2 $ nd and $ 3 $ rd are $ 3 $ .

## 说明/提示

In the example, the hidden sequence is $ [1, 6, 4, 2, 3, 5, 4] $ .

Below is the interaction in the example.

 Query (contestant's program)  Response (interactor)  Notes  and 2 5  2  $ a_2=6 $ , $ a_5=3 $ . Interactor returns bitwise AND of the given numbers.  or 5 6  7  $ a_5=3 $ , $ a_6=5 $ . Interactor returns bitwise OR of the given numbers.  finish 5   $ 5 $ is the correct answer. Note that you must find the value and not the index of the kth smallest number.

## 样例 #1

### 输入

```
7 6

2

7```

### 输出

```
and 2 5

or 5 6

finish 5```

# 题解

## 作者：b6e0_ (赞：20)

[题目链接](https://www.luogu.com.cn/problem/CF1556D)

~~翻译~~介绍官方题解评论区一个询问个数是 $\dfrac{5m}3$ 级别的[解法](https://codeforces.com/blog/entry/94384?#comment-834316)。添加了一些解释。虽然看起来长，但只是写的细，巨佬们完全可以跳过许多东西。

---
引理一：$a\ \text{xor}\ b=(a\ \text{and}\ b)\ \text{xor}\ (a\ \text{or}\ b)$。证明：

拆位，对于每一个 $d$，设 $a$ 中的第 $d$ 位是 $x$，$b$ 中的第 $d$ 位是 $y$。

如果 $x=y$，那么 $a\ \text{xor}\ b$ 的第 $d$ 位为 $0$；另一方面，$a\ \text{and}\ b$ 和 $a\ \text{or}\ b$ 的第 $d$ 位都为 $x$，相等，即 $(a\ \text{and}\ b)\ \text{xor}\ (a\ \text{or}\ b)$ 的第 $d$ 位为 $0$。所以 $a\ \text{xor}\ b$ 与 $(a\ \text{and}\ b)\ \text{xor}\ (a\ \text{or}\ b)$ 的第 $d$ 位相等。

如果 $x\ne y$，那么 $a\ \text{xor}\ b$ 的第 $d$ 位为 $1$；另一方面，$a\ \text{and}\ b$ 的第 $d$ 位为 $0$，$a\ \text{or}\ b$ 的第 $d$ 位为 $1$，不相等，即 $(a\ \text{and}\ b)\ \text{xor}\ (a\ \text{or}\ b)$ 的第 $d$ 位为 $1$，所以 $a\ \text{xor}\ b$ 与 $(a\ \text{and}\ b)\ \text{xor}\ (a\ \text{or}\ b)$ 的第 $d$ 位相等。

这样，$a\ \text{xor}\ b$ 与 $(a\ \text{and}\ b)\ \text{xor}\ (a\ \text{or}\ b)$ 的每一位都相等，所以它们相等。证毕。

---
引理二：$a+b=(a\ \text{xor}\ b)+2(a\ \text{and}\ b)$。

这个其实就是将二进制下的不进位加法和进位拆开：在不考虑进位的情况下，$a+b$ 的值就是 $a\ \text{xor}\ b$（$0+0=0,0+1=1,1+1=0$）；有关进位，只有 $a$ 和 $b$ 的这一位都为 $1$ 才会发生进位，即 $a\ \text{and}\ b$，并且进位是朝下一位产生贡献，所以要乘 $2$。

---
于是，我们通过询问两个位置的 $\text{and}$ 和 $\text{or}$，通过引理一就能获得它们的 $\text{xor}$，再通过引理二就能获得它们的和。

考虑将整个数组求出来，将每三个相邻的数 $a,b,c$ 用 $5$ 次查询求出。首先对于 $a,b$ 和 $a,c$ 分别花 $2$ 次询问获得它们的和。又由于 $b\ \text{xor}\ c=(a\ \text{xor}\ b)\ \text{xor}\ (a\ \text{xor}\ c)$，所以 $b\ \text{xor}\ c$ 不需要额外花询问求出。但想要求出 $b+c$，需要 $b\ \text{and}\ c$，所以再花 $1$ 次询问，总共 $5$ 次。目前我们获得了 $a+b,a+c,b+c$，就可以求出 $a,b,c$ 具体的值了。

另外如果 $n$ 除以 $3$ 余 $1$，再花 $2$ 次询问求出 $a_{n-1}+a_n$，根据已经求出的 $a_{n-1}$ 求出 $a_n$ 即可，可以证明 $n\ge3$ 时 $\dfrac{5(n-1)}3+2\le2n$；如果 $n$ 除以 $3$ 余 $2$，求出 $a_{n-2}+a_{n-1}$ 和 $a_{n-2}+a_n$，用已知的 $a_{n-2}$ 推出 $a_{n-1}$ 和 $a_n$ 即可，可以证明 $n\ge3$ 时 $\dfrac{5(n-2)}3+4\le2n$。

---
唉，为了照顾萌新，还是把询问次数的具体证明写出来吧。首先，$n$ 是 $3$ 的倍数时，$\dfrac{5n}3$ 显然小于 $2n$；当 $n=3k+1$（$k$ 为正整数）时，$\dfrac{5(n-1)}3+2=5k+2$，$2n=6k+2$，显然 $5k+2\le6k+2$；当 $n=3k+2$（$k$ 为正整数）时，$\dfrac{5(n-2)}3+4=5k+4$，$2n=6k+4$，显然 $5k+4\le6k+4$。

---
时间复杂度 $\mathcal O(n\log n)$，瓶颈在排序。代码：
```cpp
#include<bits/stdc++.h>
using namepace std;
#define int long long//我也不知道为什么，不开long long过不了
int n,a[10005];
inline void get(int i)
{
	int aandb,aorb,axorb,aandc,aorc,axorc,bandc,bxorc,x,y,z;//x=a+b,y=a+c,z=b+c,其他变量含义显然
	cout<<"and "<<i-2<<' '<<i-1<<endl;
	cin>>aandb;
	cout<<"or "<<i-2<<' '<<i-1<<endl;
	cin>>aorb;
	axorb=aandb^aorb;
	cout<<"and "<<i-2<<' '<<i<<endl;
	cin>>aandc;
	cout<<"or "<<i-2<<' '<<i<<endl;
	cin>>aorc;
	axorc=aandc^aorc;
	bxorc=axorb^axorc;
	cout<<"and "<<i-1<<' '<<i<<endl;
	cin>>bandc;
	x=axorb+2*aandb;
	y=axorc+2*aandc;
	z=bxorc+2*bandc;
	a[i-2]=(x+y+z)/2-z;
	a[i-1]=(x+y+z)/2-y;
	a[i]=(x+y+z)/2-x;
	if(i+1==n)//n%3=1的情况
	{
		cout<<"and "<<i<<' '<<i+1<<endl;
		cin>>x;
		cout<<"or "<<i<<' '<<i+1<<endl;
		cin>>y;
		a[i+1]=(x^y)+2*x-a[i];
	}
	if(i+2==n)//n%3=2的情况
	{
		cout<<"and "<<i<<' '<<i+1<<endl;
		cin>>x;
		cout<<"or "<<i<<' '<<i+1<<endl;
		cin>>y;
		a[i+1]=(x^y)+2*x-a[i];
		cout<<"and "<<i<<' '<<i+2<<endl;
		cin>>x;
		cout<<"or "<<i<<' '<<i+2<<endl;
		cin>>y;
		a[i+2]=(x^y)+2*x-a[i];
	}
}
signed main()
{
	int k,i;
	cin>>n>>k;
	for(i=3;i<=n;i+=3)
		get(i);
	sort(a+1,a+n+1);
	cout<<"finish "<<a[k]<<endl;
	return 0;
}
```
---
都这么良心了，给个赞再走吧。谢谢。

---

## 作者：约瑟夫用脑玩 (赞：5)

转了一圈看到一个更优做法觉得很秀。

大部分人做这道题用的是结论 $a+b=(a\operatorname{or}b)+(a\operatorname{and}b)$，用 $2(n-1)$ 次询问问出每个数与 $a_1$ 的和，然后再用两次问出除 $a_1$ 任意两数的和即可解出所有数。

当然，上述做法并不是本文的讨论重点。

考虑用另一个众所周知的结论 $a\oplus b=(a\operatorname{or}b)-(a\operatorname{and}b)$ 这样的好处是我们知道了 $a\oplus b$ 和 $b\oplus c$，我们可以不用操作免费得到 $a\oplus c$。

同时再运用一个众所周知的结论是 $a+b=(a\oplus b)+2(a\operatorname{and}b)$，注意到前面我们得到 $a\oplus b$ 和 $b\oplus c$ 时就已经询问过 $a\operatorname{and}b$ 和 $b\operatorname{and}c$，那么我们只需要额外询问一次 $a\operatorname{and}c$ 就可以得到 $a+b,b+c$ 和 $a+c$。

显然可以解出 $a,b,c$ 分别是多少，那么我们可以用 $5$ 次操作解出 $3$ 个数，最后所需操作就是 $5\times\lfloor \frac{n}{3}\rfloor+2\times(n\bmod 3)$。

后面的 $2\times(n\bmod 3)$ 就是剩下不到三个数，对于每个数我们还是使用两次操作得到 $a+b$ 的结论求出。

---

## 作者：Miraik (赞：2)

个人认为比C简单的多。

这道题有一个关键的结论：

$(a$ $or$ $b)$ $+$ $(a$ $and$ $b)$ $= a+b$。

为什么呢？我们不妨举个例：

$a=(10011)_{2} ,b=(11010)_{2}$

我们设 $x=(a$ $or$ $b)= 11011$

$y=(a$ $and$ $b)= 10010$

容易发现，对于每一位而言，$a$ 与 $b$ 均为 $1$ 时，$x$ 与 $y$ 均为 $1$。

$a$ 与 $b$ 有一个 $1$ 时，$x$ 为 $1$，$y$ 为 $0$。

$a$ 与 $b$ 均为 $0$ 时，$x$ 与 $y$ 均为 $0$。

那么显然 $a+b=x+y$。

这样我们就可以通过两次询问求出一对 $a_i+a_j$ 的值了。

题目允许我们询问 $2n$ 次，容易想到先求出每对 $a_i+a_{i+1}$，显然需要操作 $2n-2$ 次。此时我们只需要任意求出任何一个 $a_i$，就可以直接得到所有 $a_i$ 的值了。

我的做法是求出 $a_1+a_3$，设 $a_1+a_2=x,a_2+a_3=y,a_1+a_3=z$。则有：

$a_1=\frac{x-y+z}{2}$。

然后这题就做完了。总询问次数正好为 $2n$。

代码：

```cpp
/*
+   +   +   +    +++     +++++     ++++
 + +     + +      +         +      +   +
  +       +       +        +       +   +
 + +      +       +       +        +   +
+   +     +      +++     +++++     ++++
*/
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int N=100005;
const int inf=1<<30;
const ll inff=1ll<<60;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int s[N],a[N];
//(a or b) + (a and b) =(a+b).
void get_a1(int x,int y,int z){
	//a1+a2=x,a2+a3=y,a1+a3=z
	int a1_a3=x-y;
	a[1]=(a1_a3+z)/2;
}
int main(){int tests=1;//tests=read();
while(tests--){
    int n=read(),k=read();
	for(int i=1;i<n;i++){
		printf("or %d %d\n",i,i+1);
		fflush(stdout);
		s[i+1]=read();
		printf("and %d %d\n",i,i+1);
		fflush(stdout);
		s[i+1]+=read();
	}
	printf("or %d %d\n",1,3);
	fflush(stdout);
	s[1]=read();
	printf("and %d %d\n",1,3);fflush(stdout);
	s[1]+=read();
	//a1+a2 a2+a3 a3+a4 ...
	//a1+a3
	get_a1(s[2],s[3],s[1]);
	for(int i=2;i<=n;i++)a[i]=s[i]-a[i-1];
	sort(a+1,a+n+1);
	printf("finish %d\n",a[k]);
	fflush(stdout);
	//a+b=x b+c=y a+c=z
}	return 0;
}
```



---

## 作者：NXYorz (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1556D)

----
### 题目大意

给定 $n,k$，有一长度为 $n$ 的序列 $a_n$。

可以进行 $2\times n$ 次询问 $a_i$ 与 $a_j$ 进行按位与运算的结果或者进行按位或运算的结果。

输出序列第 $k$ 小。

-------
### 分析

$a + b = a\& b + a|b$

证明：

发现对于二进制下的第 $i$ 位， $a$ 与 $b$ 无非四种可能： $a$ 为 $0$，$b$ 为 $0$。$a$ 为 $0$，$b$ 为 $1$。$a$ 为 $1$，$b$ 为 $0$。$a$ 为 $1$，$b$ 为 $1$。

- 对于第一种情况，$a\&b=1$，$a|b=1$，$a + b = a\& b + a|b = 1+1$。
- 对于第二种与第三种情况，$a\&b=0$，$a|b=1$，$a + b = a\& b + a|b=1+0=0+1$。
- 对于第四种情况，$a\&b=0$，$a|b=0$，$a + b = a\& b + a|b = 0+0$。

发现$a + b$ 恒等于 $a\& b + a|b$，得证。

于是就可以解方程了。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>

using namespace std;
const int N = 1e4 + 10;

int n,k;
int a[N];

int main()
{
    scanf("%d%d",&n,&k);
    
    printf("and 1 2");
    fflush(stdout);
    int x; scanf("%d",&x);
    printf("or 1 2");
    fflush(stdout);
    int x_; scanf("%d",&x_);
    x += x_;//a1 + a2

    printf("and 1 3");
    fflush(stdout);
    int y; scanf("%d",&y);//a1 + a3
    printf("or 1 3");
    fflush(stdout);
    int y_; scanf("%d",&y_);
    y += y_;

    printf("and 3 2");
    fflush(stdout);
    int z; scanf("%d",&z);//a2 + a3
    printf("or 3 2\n");
    fflush(stdout);
    int z_; scanf("%d",&z_);//a2 + a3
    z += z_;

    a[2] = (x + z - y) / 2;
    a[1] = x - a[2];
    a[3] = z - a[2];

    for(int i = 4; i <= n; i++)
    {
        printf("and 1 %d",i);
        fflush(stdout);
        scanf("%d",&x);
        printf("or 1 %d",i);
        fflush(stdout);
        scanf("%d",&x_);
        x += x_;
        a[i] = x - a[1];
    }
    sort(a + 1 , a + 1 + n);
    printf("finish %d",a[k]);
    fflush(stdout);
}
```

---

## 作者：EnofTaiPeople (赞：2)

一般来说，IO 交互猜数总是最简单的，此题大致意思是猜一个数列的第 $k$ 小数。

前置知识：位运算加减。

[例题](https://www.luogu.com.cn/problem/P1001)代码如下：
方法一：
```cpp
#include<cstdio>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d\n",(a^b)+((a&b)<<1));
    return 0;
}
```
正确性证明：
我们可以把异或看做不进位加法，与看做只进位加法。因为与运算是进位加法，所以要左移一位。

方法二：
```cpp
#include<cstdio>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d\n",(a|b)+(a&b));
    return 0;
}
```
正确性证明：
因为 $(a|b)-(a\&b)=a\wedge b$，所以 $(a|b)+(a\&b)=(a\&b)+(a\wedge b)+(a\&b)=a+b$。

于是，我们可以同通过两次询问，得到两个数的和，于是，我们可以一次询问 $a_1$ 和 $a_i$，$1<i\le n$的和。

可是，这里遇到了两个问题：

1. 题目要求是求具体值，但现在只能排序；
2. $a_1$ 没有得到处理。

但是，只要 $a_1$ 得到了，一切都解决了。我们现在还有什么？还有两次询问机会！于是，我想到了小学奥数的三元一次方程组。是啊，只要再询问 $a_2+a_3$，就能列出方程组，解出 $a_1$ 了。

考场 AC 代码如下：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll N=1e4+4;
inline ll read(){
	ll an=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-f;c=getchar();
	}while(c>='0'&&c<='9'){
		an=an*10+c-'0';c=getchar();
	}return an*f;
}
ll ad1[N],n,k,ans[N];
int main(){
	n=read();k=read();
	register ll i,x;ans[1]=1;
	for(i=2;i<=n;++i){
		printf("or 1 %lld\n",i);fflush(stdout);x=read();
		printf("and 1 %lld\n",i);fflush(stdout);
		ad1[i]=x+read();ans[i]=i;
	}
	printf("or 2 3\n");fflush(stdout);x=read();
	printf("and 2 3\n");fflush(stdout);
	ad1[1]=ad1[2]+ad1[3]-x-read();ad1[1]>>=1;
	for(i=2;i<=n;++i)ad1[i]-=ad1[1];
	sort(ad1+1,ad1+n+1);
	printf("finish %lld\n",ad1[k]);
	return 0; 
}
```

---

## 作者：引领天下 (赞：1)

首先要说一句，这个题与 [CF1451E1](https://codeforces.com/contest/1451/problem/E1) 是非常相似的。

而这个题的解法实际非常简单，完全不配放在 div2D 的位置：

只需要注意到 $x|y+x\&y=x+y$（考虑 $x,y$ 的每个二进制位即可完成证明），我们就可以利用 $2(n-1)$ 次操作获取 $a_1+a_2,a_1+a_3,\dots,a_1+a_n$。

此时我们还剩两次操作。我们询问 $a_2+a_3$，则此时相当于拥有了 $a_1+a_2,a_1+a_3,a_2+a_3$，即 $3$ 个元和 $3$ 个方程。按解方程组的思想即可得到 $a_1,a_2,a_3$，进一步可以利用 $a_1$ 和 $a_1+a_i$ 得到 $a_i$，然后排序输出即可。

code 就不给了，相信看懂做法之后码出来并不困难。

---

## 作者：dd_d (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15205548.html)  
  
### Sol  
首先考虑 $n=3$ 的情况。  
记 $a_1$ 与 $a_2$ 的和为 $x_1$，$a_1$ 与 $a_3$ 的和为 $x_2$，$a_2$ 与 $a_3$ 的和为 $x_3$。  
考虑 $x+y=x \ and \ y +x \ or \ y$。
那么我们可以通过操作来得出 $x_1$，$x_2$，$x_3$ 的值，从而得出 $a_1$ 的值。  
$a_2$，$a_3$ 也可以通过这样的方式来得出。  
显然，当 $n$ 更大时，这个办法同样通用。  
我们每求出一个数时，两种操作分别使用了一次。  
所以最终的使用次数即为 $2n$。  
### Code  
``` cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=1e5+1;
int n,k,a[N],b[N];
int work(int u,int v)
{
	int now1,now2;
	cout<<"or "<<u<<" "<<v<<endl;
	fflush(stdout); now1=read();
	cout<<"and "<<u<<" "<<v<<endl;
	fflush(stdout); now2=read();
	return now1+now2;
}
signed main()
{
	n=read(); k=read();
	b[0]=work(1,3); b[1]=work(1,2); b[2]=work(2,3);
	a[1]=(b[1]-b[2]+b[0])/2; a[2]=b[1]-a[1]; a[3]=b[2]-a[2];
	for (int i=3;i<n;i++)
	{
		b[i]=work(i,i+1);
		a[i+1]=b[i]-a[i];
	}
	sort(a+1,a+n+1);
	cout<<"finish "<<a[k]<<endl;
	fflush(stdout);
}



```

---

## 作者：a999999 (赞：0)

### 题目大意

有一个长度为 $n$ 的数组，每次可以询问 $a_i|a_j$ 或者 $a_i\&a_j$。

询问不超过 $2n$ 次，最后求数组中第 $k$ 小。

### 解题思路

比赛想的做法，和 Editorial 的大同小异。

首先应该想到的是两条性质：

$$(a_i|a_j)+(a_i\&a_j)=a_i+a_j$$
$$(a_i|a_j)-(a_i\&a_j)=a_i\ xor\ a_j$$

这样的话我们先询问 $a_1|a_i$ 和 $a_1\&a_i$，相减得到 $a_1\ xor\ a_i$。

剩下两次机会，再询问 $a_2|a_3$ 和 $a_2\&a_3$，这时就有：
$$a_1=\frac{(a_1+a_2)+(a_1+a_3)-(a_2+a_3)}{2}$$

$$a_i=(a_1\ xor\ a_i)\ xor\ a_1$$

排个序输出就好了。

##
### Code:

```cpp
#include<algorithm>
#include<cstdio>
#define N 30010
using namespace std;
typedef long long ll;
int a[N],o[N],x[N];
int n,m;
signed main(int argc,char **argv){
//	freopen("order.in","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=2;i<=n;++i){
		printf("and 1 %d\n",i);
		fflush(stdout);
		scanf("%d",a+i);
		printf("or 1 %d\n",i);
		fflush(stdout);
		scanf("%d",o+i);
		x[i]=o[i]-a[i];
	}
	int ax,ox;
	printf("and 2 3\n");
	fflush(stdout);
	scanf("%d",&ax);
	printf("or 2 3\n");
	fflush(stdout); 
	scanf("%d",&ox);
	x[1]=((a[2]+o[2])+(a[3]+o[3])-(ax+ox))/2;
	for(int i=2;i<=n;++i)x[i]=x[i]^x[1];
	sort(x+1,x+n+1);
	printf("finish %d\n",x[m]);
	return 0;
} 
```

---

## 作者：KSToki (赞：0)

# 题目大意
IO 交互题，给定 $n$ 和 $k$，有一个数组，每次你可以询问两个不同下标 $i$ 和 $j$ 的 $a_i\&a_j$ 或 $a_i|a_j$，最多询问 $2n$ 次，求出第 $k$ 小的**数值**。
# 题目分析
这个第 $k$ 小其实意味着必须把整个数组求出来，不然单纯的与或运算可能无法确定剩下的数的。这里有一个经典的结论就是 $a+b=a\&b+a|b$，这样询问两次就可以知道两个数的和了。又注意到 $n\geq3$，一方面是为了有解，另一方面给出了一个提示，直接对 $1$，$2$，$3$ 轮流进行 $6$ 次询问得出两两的和，解方程就可以直接求出 $a_1$，$a_2$，$a_3$ 的值。从 $4$ 开始每个 $i$ 和 $1$ 询问两次就可以得出 $a_i$，刚好用了 $2n$ 次卡慢。得出全部数后求第 $k$ 小就简单了，可以直接 `sort` 或 `nth_element`。

记得开 `long long` 哦。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,k,c1,c2,c3,x,a[10001];
int main()
{
	cin>>n>>k;
	cout<<"and 1 2"<<endl;
	cin>>c1;
	cout<<"or 1 2"<<endl;
	cin>>x;
	c1+=x;
	cout<<"and 1 3"<<endl;
	cin>>c2;
	cout<<"or 1 3"<<endl;
	cin>>x;
	c2+=x;
	cout<<"and 2 3"<<endl;
	cin>>c3;
	cout<<"or 2 3"<<endl;
	cin>>x;
	c3+=x;
	a[1]=(0ll+c1+c2+c3)/2-c3;
	a[2]=(0ll+c1+c2+c3)/2-c2;
	a[3]=(0ll+c1+c2+c3)/2-c1;
	For(i,4,n)
	{
		cout<<"and 1 "<<i<<endl;
		cin>>c1;
		cout<<"or 1 "<<i<<endl;
		cin>>x;
		c1+=x;
		a[i]=c1-a[1];
	}
	sort(a+1,a+n+1);
	cout<<"finish "<<a[k]<<endl;
	return 0;
}

```

---

