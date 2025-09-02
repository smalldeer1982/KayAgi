# GGD - Mr Toothless and His GCD Operation

## 题目描述

You are given **N**. You have to find two numbers **a** and **b** such that **GCD (a, b)** is as maximum as possible where **1<=a<b<=N**.

**Input**

Input starts with an integer **T (, denoting the number of test cases.**

Each case contains an integer **N (2 .**

**Output**

For each case, print the case number and then print **a** and **b**. If there exists multiple solutions print the one where **a+b** is maximum.

**Sample Input/Output**

 **Sample Input**

  **Sample Output**

  1

2

  Case 1: 1 2

 **_Problem Setter: Md Abdul Alim, Department of CSE, Bangladesh University of Business & Technology_**

# 题解

## 作者：Halberd_Cease (赞：3)

[SP19786 GGD - Mr Toothless and His GCD Operation](https://www.luogu.com.cn/problem/SP19786)
# 分析与解

~~有手就会做~~

## 分析
题意：给定一个 $N$ 使得 $a<b\le N$ 并且使 $\gcd(a,b)$ 值最大。

一般的：要使 $\gcd(a,b)$ 值最大，且 $a\ne b$ ，就要让其中一个数为另一个数的两倍（在这里是 $2a=b$ ) ，这样的话 $\gcd(a,b)=a$ 。在规定 $N$ 的情况下，满足 $a= \lfloor \dfrac{N}{2} \rfloor $ 可以使 $\gcd(a,b)$ 值最大为 $\lfloor \dfrac{N}{2} \rfloor $。

特殊的：对于 $N=3$ ，满足要求的 $\gcd(1,2)=\gcd(1,3)=\gcd(2,3)=1$ ，取 $a+b$ 最大的，即 $a=2$,$b=3$ 。

## 解
![](https://cdn.luogu.com.cn/upload/image_hosting/8md18xxm.png)

**拒绝抄袭题解，从我做起！**

---

## 作者：billzd (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/SP19786)

本题的答案其实不难想到就是 $\operatorname{floor}$($\dfrac{n}{2}$) 和 $\operatorname{floor}$($\dfrac{n}{2}$)$\times 2$ ($\operatorname{floor}$是向下取整，后面默认 $b$ 为2的倍数)，具体说一下原因。

由于要使 $\gcd(a,b)$ 的值最大，所以要满足 $b$ 是 $a$ 的倍数，并且要尽量大，$a=\dfrac{b}{2}$ 当然是最佳人选。至此，我们就顺利的 $A$ 了这道题了吗？并不是，因为需要特判，当 $N=3$ 时，按照我们的理论，。$a$ 应该等于 1，$b$ 等于2。而由于要 $a+b$ 的值要最大，$a=2,b=3$ 才是正解！加上特判后，我们终于 $A$ 了这道题了(~~祝你们好运！~~)
### 代码：
```c
#include<stdio.h>
int main(){
	int n,t,i;
	scanf("%d",&t);
	for(i=1;i<=n;i++){
		scanf("%d",&n);
		if(n==3) printf("Case %d: 2 3\n",i);//特判。
		else printf("Case %d: %d %d\n",i,n>>1,n>>1<<1);//C语言自动向下取整。
	}
    return 0;//end
}
```


---

## 作者：_cmh (赞：0)

很简单的一道题。

我们在小学时就学过**gcd（最大公因数）**，并且知道，若 $a$ 是 $b$ 的因数时，$gcd(a,b)=a$。那么本题的答案也就很好的出来了。因为 $a,b$ 均不大于 $n$ ，又因为 $a,b$ 要成倍数关系，所以 $b$ 应该是 $a$ 的 $2$ 倍。当 $n$ 为奇数，$b=n-1,a=(n-1)\div 2$。

**注意：这题 $3$ 是个例外。按上面规则，算出来 $a+b=3,a=1,b=2,gcd(1,2)=1$ 。而 $a+b=5,a=2,b=3,gcd(2,3)=1$ 与上面答案的最大公因数相等，并且多解要输出 $a+b$ 最大的解，所以要加特判。**

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int T,n;
int main(){
	cin>>T;
	for(int i=1;i<=T;i++){
		cin>>n;
		if(n==3) printf("Case %d: 2 3\n",i);
		else 
			if(n%2) printf("Case %d: %d %d\n",i,(n-1)/2,n-1);
			else printf("Case %d: %d %d\n",i,n/2,n);
	}
    return 0;
}
```

求赞！

---

## 作者：Into_qwq (赞：0)

# 方法很简单，我来详细解释一下原理

要满足$gcd(a,b)$尽量大，我们就尽量让$a$是$b$的倍数，举个例子：

$30$和$20$的最大公约数是$10$,$30$不是$20$的倍数，所以这样是不是最优的，两者的最大公因数比较小者小

$30$和$15$的最大公约数是$15$,这样就比上面那种情况更优，因为$30$是$15$的倍数，两者的最大公因数是较小者，这就更优了

### 目标明确了：$b$是$a$的倍数时才有可能找到最优解

为了使得 $gcd(a,b)$ 最大，这个倍数肯定要小

因为$a<b$所以$b$不能是$a$的$1$倍（即$a!$=$b$）

大于$1$的最小整数为$2$，所以$b$是$a$的$2$倍时会有最优解

我们可以这样写:
```c++
if(n%2==0) printf("Case %d: %d %d",i,n/2,n);
else printf("Case %d: %d %d",i,(n-1)/2,n-1);
```
# `但这只是大部分情况，有例外`

$n=3$就是这个例外

**如果有多种方案，输出能使$a+b$最大的那一种**

所以需要加特判，核心代码如下：
```c++
if(n!=3)
{
    if(n%2==0) printf("Case %d: %d %d",i,n/2,n);
    else printf("Case %d: %d %d",i,(n-1)/2,n-1);
}
else printf("Case %d: %d %d",i,2,3);
```
完整代码如下：
```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    int n;
    for(int i=1;i<=T;i++)
    {
        cin>>n;
        if(n!=3)
        {
            if(n%2==0) printf("Case %d: %d %d",i,n/2,n);
            else printf("Case %d: %d %d",i,(n-1)/2,n-1);
        }
        else printf("Case %d: %d %d",i,2,3);
        printf("\n");
    }
    return 0;
}
```
希望这对您有所帮助

---

## 作者：james1BadCreeper (赞：0)

首先关于GCD： _当x%y==0，gcd(x,y)=y._ 

所以我们来看题：给你一个数 n ，要求构造一组 a、b 使得 gcd(a,b) 最大，且满足 1<=a<b<=n。

那么根据刚开始说的，使x%y==0，且让y最大，而且ay（也就是x，a为参数）不超过n，那么a就应该是二。

那么a应该是n/2下取整,b是a*2；

所以我们打出了以下代码：
```cpp
#include<cstdio>
using namespace std;
int main(void)//void写不写都无所谓
{
    int s,a,b;
    scanf("%d",&s);//读入数据组数
    int n[s];
    for(int i=0;i<s;i++)//读入每组数据
        scanf("%d",&n[i]);
    for(int i=0;i<s;i++)//对于每组数据
    {
        a=n[i]/2;//a是n/2下取整
        b=n[i]/2*2;//b是a*2
        printf("Case %d: %d %d\n",i+1,a,b)；//打印结果
    }
    return 0;
}
```
不会用scanf/printf的C++选手看这里！
(不要问我为什么数组名和变量名换了，C++是又些了一遍）
```cpp
#include<iostream>
using namespace std;
int main(void)//void写不写都无所谓
{
    int s,a,b;
    cin>>s;//读入数据组数
    int n[s];
    for(int i=0;i<s;i++)//读入每组数据
        cin>>n[i];
    for(int i=0;i<s;i++)//对于每组数据
    {
        a=n[i]/2;//a是n/2下取整
        b=n[i]/2*2;//b是a*2
        cout<<"Case "<<i+1<<": "<<a<<" "<<b<<endl;//打印结果
    }
    return 0;
}
```
但是……
WA？

不对吧？

来细致地想一想：一定是某些特殊数据让程序炸了。那这个特殊数据是什么呢？

本蒟蒻决定一个一个试！

1、2没有问题，但是3……

题目是这么说的，要使a+b尽可能大，结果应是2、3，但程序算出来的是1、2。

（其实2也是要管一管的，因为要求和最大，但管不管结果都一样，就不管了）

4没事，除以2嘛，逃离危险了。

所以正解要加个特判：
```cpp
#include<cstdio>
using namespace std;
int main(void)
{
    int n,a,b;
    scanf("%d",&n);
    int v[n];
    for(int i=0;i<n;i++)
        scanf("%d",&v[i]);
    for(int i=0;i<n;i++)
    {
        a=v[i]/2;
        b=v[i]/2*2;
        if(v[i]!=3) printf("Case %d: %d %d\n",i+1,a,b);
        else printf("Case %d: %d %d\n",i+1,2,3);//特判
    }
    return 0;
}
```

同样，不会scanf/printf的选手看这里！
```cpp
#include<iostream>
using namespace std;
int main(void)
{
    int s,a,b;
    cin>>s;
    int n[s];
    for(int i=0;i<s;i++)
        cin>>n[i];
    for(int i=0;i<s;i++)
    {
        a=n[i]/2;
        b=n[i]/2*2;
        if(n[i]!=3) cout<<"Case "<<i+1<<": "<<a<<" "<<b<<endl;
        else cout<<"Case "<<i+1<<": 2 3"<<endl;//特判
    }
    return 0;
}
```

欢迎大家指出不足。

---

## 作者：Jμdge (赞：0)

好吧其实是道白痴题，但是被坑了好久...

首先是输出格式，我看的原网站上题目，没有留意到输出格式...

其次就是一些特殊情况的考虑智障了...

~~坑点其实不多啊，怎么我哪个都踩中了~~

# noteskey

题意就是构造两个小于 n 的数 $a,b(a<b)$ 使其公约数最大，多个满足条件的构造需要输出和最大的构造

# Max Gcd

首先我们考虑令两个数的 GCD 最大，那么不妨设 这个 gcd  为 x ，那么有 $a=px,b=qx$ 

此时我们很容易发现，当 $p=1,q=2$ 时  x 最大，最能满足需要的构造

然后我们肯定要先让 b 最大，也就是 n 除去 2 下取整再乘回去，那么 a 就是 n 除去二向下取整了...

然后我们写了一发加上去，发现 WA 掉了...于是感觉此题没这么简单~~立马关掉题目~~

我们考虑在大数据情况下，这种构造肯定是最优的，那么问题只能在特殊的小数据上

然后容易发现 3 就是这个特殊的数据，因为 n=3 时按照之前的构造有： $a=1,b=2$，这样的 gcd 为 1

没错，这样的 gcd 已经最大了，是 1 ，但是 a 和 b 的和却不是最大的，这就是最坑的地方了，我们可以让 $a=2,b=3$，然后 $gcd=1$ 不变...这样的构造更满足条件

然后别的数据就没有特别的了，只需要这么一个特判 3 的输出就好了

（一开始我找出了 3 这个特别的数据，但是我居然特判输出 1 3 ...本来以为还有特殊数据，最后还是写了对拍才发现我 3 都特判错了，我果然太菜(Naive)了）

# code

代码很清真...大水题，大佬们连题解都不屑写...

```
//by Judge
#include<cstdio>
#include<iostream>
using namespace std;
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} int n,cnt;
int main(){ int T=read();
	while(T--){ n=read();
		if(n==3) printf("Case %d: 2 3\n",++cnt);
		else printf("Case %d: %d %d\n",++cnt,n/2,n/2*2);
	} return 0;
}
```







---

## 作者：bovine__kebi (赞：0)

这一题让我们求N以内最大的两个数，使它们的gcd也最大。

我们先来考虑，要使它们的gcd最大，就得让他们都有一个很大的公约数，因为它们不能相等，所以我们选择$\lfloor\dfrac{n}{2}\rfloor$和$\lfloor\dfrac{n}{2}\rfloor*2$这两个数，它们的gcd是$\lfloor\dfrac{n}{2}\rfloor$，总和是$\lfloor\dfrac{n}{2}\rfloor*3$,这是最大的，你可以发现没有什么是比这两个满足条件的数大的。  

然后我们就要开始写了，要注意一下这几点：  
1.注意后面那个数，也就是b，不能直接为$n$,因为$n$不一定能被$2$整除，所以要写$n/2*2$  
2.注意特判$3$，当$n=3$的时候，输出的是$1,2$，毕竟是整除下取整，但是你发现$2,3$这一组数的和更大，所以你需要特判。  

直接上代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int N;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        int a;
        scanf("%d",&a);
        if(a!=3)printf("Case %d: %d %d\n",i,a/2,a/2*2);
        else printf("Case %d: %d %d\n",i,2,3);
    }
    return 0;
}
```  
谢谢观看，管理员求过（づ￣3￣）づ╭❤～

---

