# XORinacci

## 题目描述

Cengiz recently learned Fibonacci numbers and now he is studying different algorithms to find them. After getting bored of reading them, he came with his own new type of numbers that he named XORinacci numbers. He defined them as follows:

- $ f(0) = a $ ;
- $ f(1) = b $ ;
- $ f(n) = f(n-1) \oplus f(n-2) $ when $ n > 1 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

You are given three integers $ a $ , $ b $ , and $ n $ , calculate $ f(n) $ .

You have to answer for $ T $ independent test cases.

## 说明/提示

In the first example, $ f(2) = f(0) \oplus f(1) = 3 \oplus 4 = 7 $ .

## 样例 #1

### 输入

```
3
3 4 2
4 5 0
325 265 1231232
```

### 输出

```
7
4
76
```

# 题解

## 作者：pzc2004 (赞：7)

[题目传送门](https://www.luogu.org/problem/CF1208A)

题目大意：给出一个数列，令$f_0=a,f_1=b,f_n=f_{n-1}⊕f_{n-2}(n>1)$，给出a，b，n，求$f_n$。

思路：先找规律，因为异或时不同位上的数字不会影响，所以只需要研究一位上的数字。

一开始是0，1：0，1——>1——>0——>1回到了0，1

一开始是0，0：0，0——>0——>0——>0回到了0，0

一开始是1，1：1，1——>0——>1——>1回到了1，1

一开始是1，0：1，0——>1——>1——>0回到了1，0

发现进行3次操作就会回到原来的数，所以只需将n%3，再讨论一下即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,a,b,f[3];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&a,&b,&n);
		n%=3;
		f[0]=a;
		f[1]=b;
		f[2]=a^b;
		printf("%d\n",f[n]);
	}
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：yeaDonaby (赞：2)

## 思路一：

我们发现，$⊕$与$⊕$互为逆运算。

所以：

$a⊕b=c$

$c⊕b=a , c⊕a=b$

## 思路二：

$f[0]=a;$

$f[1]=b;$

$f[2]=a⊕b;$

$f[3]=a⊕b⊕b=a$

其中$b$为$f[1]$ , $(a⊕b)$为$f[2]$
     
$f[4]=a⊕b⊕a=b$

其中$(a⊕b)$为$f[2]$ , $a$为$f[3]$

$f[5]=a⊕b$

$......$

### 所以,异或斐波那契数列每三个一循环节，循环节元素有：$a,b,a⊕b$

### 注意：

1.不用开$longlong$，因为位运算是不会进位的，且$0≤a,b,n≤10^9$

2.多组数据要换行！！！

具体实现就是$n$%$3$做下标，输出$f[n_{mod}^{mod}3];$

$code:$
```
#include<stdio.h>
#define R register
int t,n,a,b;
int main(void)
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&a,&b,&n);
		if(n%3==0)
		{
			printf("%d\n",a);
		}
		else if(n%3==1)
		{
			printf("%d\n",b);
		}
		else
		{
			printf("%d\n",a^b);
		}
	}
	return 0;
}
```

---

## 作者：andyli (赞：2)

我们先按照题目条件进行找规律：  
$$f(0)=a$$  
$$f(1)=b$$
$$f(2)=f(0)\oplus f(1)=a\oplus b$$
$$f(3)=f(1)\oplus f(2)=b\oplus a\oplus b=a (\texttt{because}\  x\oplus x=0)$$  
$$f(4)=f(2)\oplus f(3)=a\oplus b\oplus a=b$$
$$f(5)=f(3)\oplus f(4)=a\oplus b=f(2)$$  

可以发现对于任意一个$f(x)$都有$f(x)=f(x\% 3)$，所以只需计算$f(0)$,$f(1)$及$f(2)$即可。  
代码如下：  
```cpp
#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b, n;
        scanf("%d%d%d", &a, &b, &n);
        if (n % 3 == 0) // f(n)=f(0)
            printf("%d\n", a);
        if (n % 3 == 1) // f(n)=f(1)
            printf("%d\n", b);
        if (n % 3 == 2) // f(n)=f(2)
            printf("%d\n", a ^ b);
    }
    return 0;
}
```

---

## 作者：asasas (赞：1)

这题的数据太大，显然暴力会超时，所以我们来找一下规律。

异或有一个性质：异或自己本身，结果为0（两个相同的数，二进制一定相同，异或一下就只剩0了），所以异或有**奇消偶不消**的特性。

$f(0)=a$,$f(1)=b$

$f(2)$ $=$ $f(0)$⊕$f(1)$ $=$ $a$⊕$b$

$f(3)$ $=$ $f(1)$⊕$f(2)$ $=$ $a$ ⊕ ($a$⊕$b$)$=$ $a$（原因上面解释过了）

$f(4)$ $=$ $f(2)$⊕$f(3)$ $=$ $b$ ⊕ ($a$⊕$b$) $=$ $b$

$f(5)$ $=$ $f(3)$⊕$f(4)$ $=$ $a$⊕$b$

$f(6)$ $=$ $f(4)$⊕$f(5)$ $=$ $a$ ⊕($a$⊕$b$)=$a$

......

于是我们发现：

**当$n$ % $3==0$** 时，**输出$a$**

**当$n$ % $3==1$** 时,**输出$b$**

**当$n$ % $3==2$** 时,**输出$a$⊕$b$**

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin >> t;
	while(t--){
		int a,b,n,c;
		cin >> a >> b >> n;
		c=a^b;//C++很奇怪，如果你用cout输出a^b，会编译错误，所以要另设一个变量
		if (n%3==0) cout << a << endl;
		else if (n%3==1) cout << b << endl;
		else cout << c << endl; //3种情况
	}
	return 0;
}
```


---

## 作者：Magallan_forever (赞：1)

注意xor的性质：

设有三个数a,b,c，且$ c=a\ xor\ b $，则有$ a=b\ xor\ c,b=a\ xor\ c,c=a\ xor\ b $

也就是说这三个数会无限循环，周期是$ a,b,a\ xor\ b $

所以我们就可以写出AC代码了：
```
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int a,b,t,n;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&a,&b,&n);
        if((n+1)%3==0) printf("%d\n",a^b);
        else if((n+1)%3==1) printf("%d\n",a);
            else printf("%d\n",b);
    }
}
```

---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1208A)

# 前置芝士

斐波那契数列（~~这应该没有人不知道罢~~）：

一个数列$f_0$ , $f_1...f_n$

其中$f_0=1$ , $f_1=1$

$f_2=f_0+f_1=1+1=2$

$f_3=f_1+f_2=1+2=3$

以此类推

# 本题思路

异或运算有一个很重要的性质：某一个数，异或两次同一个数，结果仍是它本身。

~~一起来推个柿子呗~~

$f_0=a$ , $f_1=b$

$f_2=f_0 \oplus f_1=a \oplus b$ 

$f_3=f_1 \oplus f_2=b \oplus ( a \oplus b )= a$ 

因为$b$与$b$异或运算后变为$0$，所以$f_3$为$a$

$f_4=f_2 \oplus f_3=( a \oplus b )\oplus a = b$ 

因为$a$与$a$异或运算后变为$0$，所以$f_4$为$b$

$f_5=f_3 \oplus f_4= a \oplus b $ 

一看，这又变回了$a \oplus b$，说明了这个柿子有个规律：

当$n$ $%$ $3$ $=$ $0$时，答案为$a$

当$n$ $%$ $3$ $=$ $1$时，答案为$b$

当$n$ $%$ $3$ $=$ $2$时，答案为$a \oplus b$

# 废话不多说，上代码：

```cpp
#include<bits/stdc++.h> //懒人专属头文件 
using namespace std;
int n,a,b,t,ans[3];
//a,b,n见题面 
//t为数据组数
//ans数组为存储n%3=0/1/2时的答案 
int main(){
    cin>>t; //输入 
    while(t--){
        cin>>a>>b>>n; //输入 
        n%=3; //求出n%3的结果，n%=3就是n=n%3 
        ans[0]=a; //n%3=0 
        ans[1]=b; //n%3=1
        ans[2]=a^b; //n%3=2
        cout<<ans[n]<<endl; //输出 
    }
    return 0; //好习惯 
}
```

代码看完了，你学废了吗？

---

## 作者：A_Đark_Horcrux (赞：0)

只要手动模拟一下就会发现这个数列是有周期性的：

对于任意 $n \geq 0$ ，第 $3n$ 项为 $a$ ，第 $3n+1$ 项为 $b$ ，第 $3n+2$ 项为 $a \oplus b$ 。

证明：异或运算有一个很重要的性质： __a^b^b=a.__ 也就是某一个数，异或两次同一个数，结果还是它本身。

$f(0)=a,f(1)=b,f(2)=a \oplus b,$

则 $f(3)=f(2)\oplus f(1)=(a \oplus b) \oplus b = a,$

$f(4)=f(3)\oplus f(2)=a \oplus (a \oplus b )= b,$

$f(5)=f(4)\oplus f(3)=a \oplus b ...$

以此类推。

因此将操作数模3以后对应输出即可qwq

```cpp
//部分代码
int main()
{
	T=read();
	while(T--) {a=read(),b=read(),t=read(); printf("%d\n",t%3==0?a:(t%3==1?b:a^b)); }//对应输出
	return 0;
}//完结awa
```


---

## 作者：苏黎世 (赞：0)

[支持一下吧~](https://www.luogu.com.cn/blog/Psycho-520/)

题目大意：

f(0) = a;

f(1) = b;

f(n) = f(n-1)^f(n-2);

对于新手，先介绍下异或：

#### 异或是指将两个数转成二进制，若同一位相同则值为0，不相同则为1。

如：1101^0001 = 1100。

然后我们会发现：

1、一个数异或自己，等于0 。这个很显然，一个数异或自己则每个位都是相同的，那么结果每一位都是0，结果也就是0 了。

2、针对这一题来说，如果一次一次异或肯定会TLE~~亲测~~，那么我们就要去找另一个规律。

我们发现:（以样例2为例）

4的二进制为100,5的二进制为101。

（1）100^101=001。

（2）001^101=100。

（3）100^001=101。

（4）101^001=100。

很明显，规律来了：每3个一循环，剩下0时，结果为a，剩下1时，结果为b，剩下2时，结果为a^b。

这样就避免了TLE的情况，简单高效。

LL的话开不开都可以的，开了保险。

### Code：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int T, n;
long long a, b, c;

void work()
{
  n %= 3;//3个一循环
  if(n == 0)
    printf("%lld\n", a);
  else if(n == 1)
    printf("%lld\n", b);
  else if(n == 2)
    printf("%lld\n", a ^ b);
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
      scanf("%lld%lld%d", &a, &b, &n);
      work();
    }
    return 0;
}
```


---

## 作者：VenusM1nT (赞：0)

规律题。  
一开始以为是什么高端的做法，到 CF 上一看评分 900……当时就惊了  
回来想了一下，$a\ \text{xor}\ b = c,c\ \text{xor}\ b=a,a\ \text{xor}\ c=b$，回到了初始状态……  
打个表应该也可以非常明显地看出来……  
所以直接让 $n$ 对 $3$ 取模即可。

```cpp
#include<bits/stdc++.h>
#define MAXN 
#define reg register
#define inl inline
using namespace std;
int n,a,b;
int main()
{
	reg int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d %d",&a,&b,&n);
		n=(n%3)+1;
		reg int t=a^b;
		printf("%d\n",n==3?t:(n==1?a:b));
	}
	return 0;
}
```

---

## 作者：小小小朋友 (赞：0)

### 题目描述
有一个"异或斐波那契数列"，让你求第$n$项，n很大。

### 思路
因为异或两次就可以异或回去了，所以这个数列是每三项便重复一次的。

下面给出证明：
$$f_0=a$$
$$f_1=b$$
$$f_2= a\odot b $$
$$f_3= f_2 \odot b =b$$
$$……$$
$$\therefore f_n=f_{n\mod3}$$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[4],p,n;
int main(){
	scanf("%d",&p);//多组数据
	while(p--){
		scanf("%d%d%d",&f[0],&f[1],&n);
		f[2]=f[0]^f[1];//这样便计算第3项
		printf("%d\n",f[n%3]);//只需输出第n%3项即可
	}
	return 0;
}
```

---

## 作者：foreverlasting (赞：0)

[推销博客](https://foreverlasting1202.github.io/2019/08/27/CF1208%E9%A2%98%E8%A7%A3/)

### A XORinacci

题意：$f(0)=a,f(1)=b,f(n)=f(n-1)\bigoplus f(n-2)$，求$f(n)$。$0\leq a,b,n\leq 10^9$，$1000$组询问。

做法：$a\bigoplus b\bigoplus a=b$，所以三个一循环，模$3$就完事了。

code:
```cpp
//2019.8.24 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define unl __int128
#define eps 5.6e-8
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define ull unsigned LL
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
inline int read() {
    res s=0,ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline int read() {
//    res s=0,ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline void write(RG unl x){
//    if(x>10)write(x/10);
//    putchar(int(x%10)+'0');
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//clock_t start=clock();
//inline void ck(){
//    if(1.0*(clock()-start)/CLOCKS_PER_SEC>0.1)exit(0);
//}
namespace MAIN{
    int T;
    int a,b,n;
    inline void MAIN(){
        T=read();
        while(T--){
            a=read(),b=read(),n=read();
            if(n%3==0)printf("%d\n",a);
            else if(n%3==1)printf("%d\n",b);
            else printf("%d\n",a^b);
        }
    }
}
int main(){
//    srand(19260817);
//    freopen("signin.in","r",stdin);
//    freopen("signin.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：弦巻こころ (赞：0)

题意就是给你一个序列,让你求序列第n项.

一开始看到题的时候有点慌,$n<=10^9$还以为要用什么高端算法.结果随便打了打表就发现了规律.

$$
f[2]=f[1]xorf[0]
$$
$$
f[3]=f[0]
$$
$$
f[4]=f[1]
$$
然后发现 
$$
f[5]=f[2] ,f[6]=f[0],f[7]=f[1], f[n]=f[nmod3].
$$

直接求出f[2] 然后 n%3 直接输出f[n%3]就好了

如果要证明也是挺简单的

$$ f[3]=f[2] xor f[1] =(f[1]xorf[0])xorf[1]$$
由于异或的性质我们可以知道当我们异或两次同一个数时相当于什么都没干.所以 $f[3]=f[0]$ 其他数也同理


代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long f[4];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		scanf("%lld%lld%lld",&f[0],&f[1],&n);
		f[2]=f[1]^f[0];
		printf("%lld\n",f[n%3]);
	}
	return 0;
}
```


---

## 作者：STILL_ALONE (赞：0)

让你求这么一个诡异的数，显然直接求是不行的，所以，准备从最开始的入手。  
考虑最开始的情况：  
$Xorib\left ( 2 \right ) =  Xorib\left ( 1 \right )  xor  Xorib\left ( 0 \right )$  
$Xorib\left ( 3 \right ) =  Xorib\left ( 2 \right )  xor  Xorib\left ( 1 \right )$
$Xorib\left ( 3 \right ) =  Xorib\left ( 1 \right )  xor  Xorib\left ( 1 \right ) xor Xorib\left ( 0 \right ) = Xorib\left ( 0 \right ) $  
以此类推，可以发现对于任意的$Xorib\left ( n \right )\left ( n\equiv 0\left ( mod 3 \right )  \right )$   
都有  
$Xorib\left ( n \right ) = Xorib\left ( 0 \right )$  
$Xorib\left ( n+1 \right ) = Xorib\left ( 1 \right )$  
$Xorib\left ( n+2 \right ) = Xorib\left ( 2 \right )$  
$\therefore Xorib\left ( n \right ) = Xorib\left ( n\left ( mod3 \right ) \right )$
### 注意要开long long ###  
上代码QAQ

---
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[5];
int n;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>f[0]>>f[1];
        f[2]=f[0]^f[1];
        cin>>n;
        n%=3;
        cout<<f[n]<<endl;
    }
    return 0;
} 
```

---

## 作者：兮水XiShui丶 (赞：0)

定义一种新的斐波那契数列为  
$$fib(i)=fib(i-1)\  xor fib(i -2)$$  

其中 
$$fib(0)=a,fib(1)=b$$  

给你$a$和$b$ ,让你求出此数列的第$n$项.  

显然直接求是不行的,所以我们可以考虑一下   

$$fib(2)=fib(1)\ xor \ fib(0)$$  
$$fib(3)=fib(2)\ xor \ fib(1)$$ 

那么 

$$fib(3)=fib(1) \ xor \ fib(1) \ xor \ fib(0) = fib(0)$$  
$$fib(4)=fib(0) \ xor \ fib(1) \ xor \ fib(0) = fib(1)$$
$$fib(5)=fib(0) \ xor \ fib(1) = fib(2)$$  

那么我们显然可以推广得到(假设$n \ mod \ 3 \ = 0$):  

$$fib(n)=fib(0)$$  
$$fib(n+1)=fib(1)$$  
$$fib(n+2)=fib(2)$$ 

即  
$$fib(n)=fib(n \ mod \ 3)$$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[5];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>f[0]>>f[1];
		f[2]=f[0]^f[1];
		cin>>n;
		n%=3;
		cout<<f[n]<<endl;
	}
	return 0;
} 
```


---

## 作者：引领天下 (赞：0)

这个题其实是很简单的……

看到题面的第一眼：递推求数列？$n\le 10^9$？

~~恩估计是矩阵快速幂~~

但A应该不至于这样吧？

仔细一看，发现自己被出题人骗了

$$f[0]=a$$

$$f[1]=b$$

$$f[2]=axorb$$

$$f[3]=axorbxorb=a$$

$$f[4]=axorb$$

好的那么我们就知道了，$f[3]=f[0],f[4]=f[1],f[5]=f[2]...$读入的$n$是假的，直接%=$3$就好。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,n;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&a,&b,&n);n%=3;//读入，同时取模
        switch(n){
            case 0:printf("%d\n",a);break;
            case 1:printf("%d\n",b);break;
            default:printf("%d\n",a^b);break;//如上文的解法。
        }
    }
}
```

---

