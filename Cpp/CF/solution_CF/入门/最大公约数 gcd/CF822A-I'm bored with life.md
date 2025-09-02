# I'm bored with life

## 题目描述

Holidays have finished. Thanks to the help of the hacker Leha, Noora managed to enter the university of her dreams which is located in a town Pavlopolis. It's well known that universities provide students with dormitory for the period of university studies. Consequently Noora had to leave Vičkopolis and move to Pavlopolis. Thus Leha was left completely alone in a quiet town Vičkopolis. He almost even fell into a depression from boredom!

Leha came up with a task for himself to relax a little. He chooses two integers $ A $ and $ B $ and then calculates the greatest common divisor of integers " $ A $ factorial" and " $ B $ factorial". Formally the hacker wants to find out GCD $ (A!,B!) $ . It's well known that the factorial of an integer $ x $ is a product of all positive integers less than or equal to $ x $ . Thus $ x!=1·2·3·...·(x-1)·x $ . For example $ 4!=1·2·3·4=24 $ . Recall that GCD $ (x,y) $ is the largest positive integer $ q $ that divides (without a remainder) both $ x $ and $ y $ .

Leha has learned how to solve this task very effective. You are able to cope with it not worse, aren't you?

## 说明/提示

Consider the sample.

 $ 4!=1·2·3·4=24 $ . $ 3!=1·2·3=6 $ . The greatest common divisor of integers $ 24 $ and $ 6 $ is exactly $ 6 $ .

## 样例 #1

### 输入

```
4 3
```

### 输出

```
6
```

# 题解

## 作者：云浅知处 (赞：4)

第一步：审题！
***
题目：给定两个正整数$A$和$B$，求$A!$和$B!$的最大公因数

满足$1\le A,B\le10^9,1\le min(A,B)\le12$
***
这题乍一看似乎挺难，然而，实际上，不知道各位发现没有：

## 只要输出这两个数种较小数的阶乘即可！

证明如下：

设$m,n$为两个任意正整数。不妨设$m\le n$

即证$(m!,n!)=m!$

（注：$(p,q)$指的是$p,q$的最大公因数）

$\because m!=1\times2\times3\times\cdots\times(m-1)\times m,$

$\quad\ n!=1\times2\times3\times\cdots\times(n-1)\times n,$

又$\because m\le n$

$\therefore n!=1\times2\times3\times\cdots\times(m-1)\times m\times(m+1)\times\cdots\times(n-1)\times n$

（注：由于$n!$囊括了从$1$到$n$的一切正整数，而$m\le n$，故$m$也是“从$1$到$n$的所有正整数”中的一个正整数，故$m$也是$n!$的一个因数）

注意到：
$$n!=\begin{matrix}\underbrace{1\times2\times3\times\cdots\times(m-1)\times m}\\m!\end{matrix}\times(m+1)\times(m+2)\times\cdots\times(n-1)\times n$$

$\quad\ =m!\times(m+1)\times(m+2)\times\cdots\times(n-1)\times n$

故$m!\mid n!$

（注：符号'$\mid$'表示"整除"，'$a\mid b$'意为"$a$能整除$b$"，也就是"$a$是$b$的因数"）

又，$m!\mid m!$（这显然成立啊，这里就不赘述了）

故$m!$为$m!,n!$的一个公因数

下证$m!$为$m!,n!$的最大公因数：
***
假设$m!$不是$m!,n!$的最大公因数，而正整数$k$才是$m!,n!$的最大公因数,则$k>m!$。

则由最大公因数的性质可得：$k\mid m!,k\mid n!$

又，$k>m!$，则显然$k\nmid m!$（这个大家应该自己看得出来，这里就不赘述了），矛盾！

故，$k$**不是**$m!,n!$的最大公因数，则假设不成立，即$m!$**就是**$m!,n!$的最大公因数。

证毕。
***
由上面的证明，我们可以知道：

$min(m,n)!=\gcd(m!,n!)$

（注：$\gcd$也是最大公因数的意思）

所以我们其实只需要求出来$min(m,n)!$再输出就可以啦^_^～
***
第三步：你们喜欢的代码来啦！

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long a,b,m,ans=1;//a,b如题意，m是a,b中较小的，ans是最终答案，注意ans要赋值成1
	cin>>a>>b;//输入
	m=min(a,b);//给m赋值
	for(int i=1;i<=m;i++)//阶乘循环，其实我本来想写递归的，但考虑到递归可读性较低，本着深入浅出的原则，我仍然写了循环
	{
		ans*=i;//将ans乘上i，这样ans第一次乘1，第二次乘2,...,直到第m次乘m，就成了m!
	}
	cout<<ans<<endl;//输出答案
	return 0;//结束程序
}
```
运行结果看[这里](https://www.luogu.com.cn/record/31582339)
***
最后：

$\huge\color{red}\text{共创文明洛谷，拒绝Ctrl+C!!!}$

---

## 作者：Ousmane_Dembele (赞：4)

这题考验的主要是读题能力

读完后你会发现题意是“给出两个正整数a,b,求a!和b!的最大公约数.”

数据范围“The first and single line contains two integers A A and B B (1<=A,B<=10^9,min(A,B)<=12) ”

如果干算a! 和b!，高精度都有可能做不出来（a,b数据范围太大）

但是仔细一想

假设a>=b

那么b!=
```
1*2*3*4*5*……*b
```
```
a!=1*2*3*4*5*……*b*(b+1)……*a
```

仔细一看前b项一样（这不废话吗），所以a！和b！的公约数中有b！

而一个数的最大公约数是它本身，所以b！是a！和b！的最大公约数

其实题目的暗示很明确了（哪道正常点的题会给min（A,B）的值）

由于太简单，代码就不写注释了

```
#include<bits/stdc++.h>
using namespace std;
long long ans=1;
int main(){
    int n,m;
    cin>>n>>m;
    n=min(n,m);
    for(int i=2;i<=n;i++)
       ans*=i;
    cout<<ans;
    return 0;
}
```

---

## 作者：览遍千秋 (赞：1)

这是一道数论题。

看上去需要求A!和B!的gcd

仔细想想，A!和B!的最大公约数不就是min(A,B)!吗。

---

得到代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,ans=1;
int main()
{
	cin>>a>>b;
	a=min(a,b);
	for(int i=1;i<=a;i++)
		ans=ans*i;
	cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Snow_Dreams (赞：0)

这道题用数学想一想，就发现了其无非有两种情况：

1. a > b
```latex
a! = a(a-1)......1

b! = b(b-1)......1

设a-b=k

则(a-k)!=b!

而a!/b!=b!*gcd(a(a-1)......*(a-k+1),1)=b!

故输出n！即可


2. b < a
考虑交换m，n的位置，转化为第一种情况即可

最后输出min(a,b)!

但是你有可能会担心，会不会爆long long啊？

不会，因为：
min(A,B)<=12



---

## 作者：午尘 (赞：0)

根据题意得，此题为求a!和b!的最大公约数。

推导过程：

```
/* 我们假设a<=b,
   那么a!=1*2*……*a;
       b!=1*2*……*a*……*b;  
   所以两数成倍数关系，
   那么最大公约数就是a!啦~
 */ 
```

然后实际应用还有一个注意点就是：累乘器的初始值为1……



------------

放代码啦~


```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,b,minn,ans,i;
int main(){
	scanf("%lld%lld",&a,&b);
    minn=min(a,b);
    ans=1;
    for (i=1;i<=minn;i++)	ans*=i;
    cout<<ans<<endl;
   return 0;
}
```


---

## 作者：CJHGOD (赞：0)

我们可以试着分析一下：

A！=1 * 2 * 3 *4  *……*a；

B！=1 * 2 * 3 * 4……* a *（a+1）*b

（假设b>=a）

像24,36。

24=2 * 2 * 2 * 3

36=2 * 2 * 3 * 3

它们的共有质因数是2,2,3，所以gcd（24,36）是2 * 2 * 3也就是12

那么呢，A!和B！的gcd就是min（A,B）！

~~其实题目已经提示了一切（看下面）~~

# 1<=A,B<=10e9  ,min(A,B)<=12).

## ~~## 于是代码就是一个极简数论代码~~
```cpp
#pragma GCC optimize(3)//O3好习惯
#include<bits/stdc++.h>//万能头文件
using namespace std;
int jc(int x){//函数
	int s=1;//s=1
	for(int i=1;i<=x;i++){
		s*=i;//阶乘
	}
	return s;//返回撒花
}
int main(){
	ios::sync_with_stdio(0);//输入输出优化
	int n,m;
	cin>>n>>m;
	cout<<jc(min(n,m));//输出min（A，B）！
    return 0;//完结撒花
}

```



---

## 作者：shejian0702 (赞：0)

考虑到数据范围，我们肯定不能硬上，观察发现，假设a<b;把a!和b!都展开,发现b!的有且只有前a项与a!相同；也就是说这道题其实就是让你求a!,又有min(a,b) <= 12；所以此时就可以霸王硬上弓了; 

之前题解都用的C++,我发个pascal的代码。
```pas
var 
  ans : int64;{要留意答案范围;ans用int64}
  n,m,i:longint;
begin
  ans := 1;{注意ans初始化为1}
  read(n,m);
  if n>m then n := m;
  for i:= 2 to n do begin{我们知道1是乘法的恒等元所以就不乘了}
    ans := ans * i;
  end;
  write(ans);
end.
```

---

