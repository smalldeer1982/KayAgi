# Modular Equations

## 题目描述

Last week, Hamed learned about a new type of equations in his math class called Modular Equations. Lets define $ i $ modulo $ j $ as the remainder of division of $ i $ by $ j $ and denote it by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/57aaef9d4f53d75c7150d35a36ceb219c08ecb8d.png). A Modular Equation, as Hamed's teacher described, is an equation of the form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/bedc8c54f3a5a224f7fdfd3a3301336e4b862b12.png) in which $ a $ and $ b $ are two non-negative integers and $ x $ is a variable. We call a positive integer $ x $ for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/bedc8c54f3a5a224f7fdfd3a3301336e4b862b12.png) a solution of our equation.

Hamed didn't pay much attention to the class since he was watching a movie. He only managed to understand the definitions of these equations.

Now he wants to write his math exercises but since he has no idea how to do that, he asked you for help. He has told you all he knows about Modular Equations and asked you to write a program which given two numbers $ a $ and $ b $ determines how many answers the Modular Equation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/bedc8c54f3a5a224f7fdfd3a3301336e4b862b12.png) has.

## 说明/提示

In the first sample the answers of the Modular Equation are 8 and 16 since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/c013274f5a802f50affb5d5736cfe493bd6c937a.png)

## 样例 #1

### 输入

```
21 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
9435152 272
```

### 输出

```
282
```

## 样例 #3

### 输入

```
10 10
```

### 输出

```
infinity
```

# 题解

## 作者：BLX32M_10 (赞：4)

这很明显是一道数论题。

首先，题目上没有说“无答案”这种情况，所以得出 $a \ge b$。

其次，如果 $a = b$，被除数就等于余数了，有无数种情况（准确来讲没有这种情况）所以要特判。 

```cpp
if (a == b)
{
    printf("infinity");
    return 0;
}
```

然后直接
```cpp
a -= b

```
后面只用从 $1$ 到 $\sqrt{a}$ 判断整除就行了

```cpp
for (int i = 1; i * i <= a; i++)
```

在循环中可得每一次循环中如果 $i > b$ 则答案加一，$\frac{a}{i} > b$ 相同。

值得注意的是，当 $i = \sqrt{a}$ 时只需判断一次就行。

AC 代码：

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	if (a == b)
	{
		printf("infinity");
		return 0;
	}
	a -= b;
	int res = 0;
	for (int i = 1; i * i <= a; i++)
		if (a % i == 0)
			if (i * i == a)
				res += (i > b);
			else
				res += (i > b) + (a / i > b);
	printf("%d", res);
	return 0;
}
```

---

## 作者：ILC_Wei_orz (赞：0)

# 题意：

------------

两个整数 $a$ ，$ b $ ，问有多少个 $x$ ，使得满足等式 $a$ $\bmod$ $ x = b$

------------

## 思路：

------------

$a$ $\bmod$ $x$ = $b$
说明:
1. $b$ 是余数 

2. $x$ 是除数

设商为 $d$ 则 $d\times x+b=a$

这道题首先由题得要分类讨论：$a>b$，$a=b$，$a<b$ 
    
首先考虑 $a<b$ ， 这种情况，因为余数比被除数大 ，没有情况可以满足 ，所以输出0。

如果 $a=b$，让 $x>b$, 情况就会有无数种则输出 "$infinity$"。

如果 $a>b$，从 $1$ 开始遍历，如果 $x$ 是 $a$ 的因数 , 那么 $a/x$ 当然也是 $a$ 的因数，所以我们看因数是否大于 $b$，就行了 。 

------------
## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int x,y,bj=0,s=0;
	cin>>x>>y;
	int pd=sqrt(x);
	if(x==y) 
	{
		cout<<"infinity"<<endl;
		return 0;
	}
	if(x<y)
	{
		cout<<"0"<<endl;
		return 0; 
	}
    bj=x-y;
    for(int i=1;i*i<bj;i++)
    {
        if(bj%i==0){
            if(i>y) s++;
            if(bj/i>y) s++;
        }
    }
    
	if(pow(pd,2)==bj && pd>y) s++;
	cout<<s<<endl;
	return 0;
}


---

## 作者：zsyyyy (赞：0)

# CF495B 数学

## 题意

给定两个整数 $a$，$b$，问有多少个$x$，使得满足等式 $a$ $mod$ $x$ $=$ $b$

如果存在无限个，就输出```infinity```，否则输出满足条件 $x$ 的个数

## 思路

- 情况一：$a=b$

对于任意一个大于 $a$ 的 $x$ 都满足 $a$ $mod$ $x$ $=$ $b$，所以答案有无限个。

- 情况二：$a<b$

显然 $a$ $mod$ $x$ $<=$ $a$ 恒成立，而又知 $a<b$，所以
$a$ $mod$ $x$ $<$ $b$，所以 $x$ 无解。

- 情况三：$a>b$

将 $a$ 减去 $b$，式子就变成了 $a$ $mod$ $x$ $=$ $0$，所以只要找出每一个 $a$ 的因数即可。注意找到的因数 $x$ 必须大于 $b$，因为如果小于 $b$，$a$ $mod$ $x$ 也就小于 $b$ 了。

从 $1$ 枚举到 $\sqrt{a}$ ，如果枚举到了 $a$ 的某一个因数 $x$，那么 $a/x$ 也一定是 $a$ 的因数。分别判断这两个因数是否大于b，如果大于，就是答案的一种。

注意判断 $x$ 是否等于 $a/x$，否则就会在 $a$ 为平方数时将 $\sqrt{a}$ 算两遍。


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,sa,ans;
signed main()
{
	scanf("%lld%lld",&a,&b);
	if(a==b)
	{
		puts("infinity");
		return 0;
	}
	if(a<b)
	{
		puts("0");
		return 0;
	}
	a-=b;
	sa=sqrt(a);
	for(int i=1;i<=sa;i++)
	{
		if(!(a%i))
		{
			if(i>b)  ans++;
			if((a/i)>b&&i!=(a/i))  ans++;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：FanYongchen (赞：0)

可以先了解一下[数论分块](https://blog.csdn.net/sunmaoxiang/article/details/88958124)。

$a\bmod x = b$ 可以转变成 $a-\left\lfloor\dfrac{a}{x}\right\rfloor\times x=b$

移项,得 $a-b=\left\lfloor\dfrac{a}{x}\right\rfloor\times x$

根据数论分块，在一个范围内， $\left\lfloor\dfrac{a}{x}\right\rfloor$ 的值是一定的。

所以如果 $(a-b)\bmod {\left\lfloor\dfrac{a}{x}\right\rfloor}=0$ ，并且此时 $x>b$ ,则 $x$ 满足条件。

当然，无解的情况就是 $a=b$

代码如下：
```cpp
#include <iostream>
using namespace std;
int main()
{
    int a,b;
    cin>>a>>b;
    if(a==b) cout<<"infinity";//无解
    else
    {
        int c=a-b;//求出它们的差
        int l=1,r=0;
        int ans=0;
        while(l<=a)//数论分块
        {
            int k=a/l;
            if(c%k==0&&c/k>b) 
            //此时,c/k的值即为x
            //我们要判断是否整除
            //以及余数是否小于除数
                ans++;
            r=a/(a/l);
            l=r+1;
        }
        cout<<ans;
    }
    return 0;
}
```


---

## 作者：TRZ_2007 (赞：0)

**[题解 CF495B 【Modular Equations】](https://www.luogu.com.cn/problem/CF495B)**  
# Solution  

分类讨论，对于两个数字的大小关系，很容易分成三类： $a>b,a=n,a<b$。

- 1： $ a > b$ ：  
我们考虑题目中给我们的关系式：  
$$ a \% x = b$$  
转化一下，变成：  
$$a = kx + b(k>0)$$  
$$kx = a - b$$  
所以 $x$ 是 $a - b$ 的因数，我们接下来要求的就是 $a - b$ 的因子个数，时间复杂度 $\mathcal{O(\sqrt{n})}$，思路就是从 1 枚举到 $\sqrt{n}$，看看你枚举的数字能否整除于 $a - b$ ，它和 $n$ 的商能不能整除于 $a - b$ 即可，但是不要忘记 $\sqrt{n}$，这个数字智能做多被记录一次。  

**还有一个大前提：x > b!**

- 2： $a = b$：  
对于任意一个 $x > a$，题设均成立，所以有无数多个。  
- 3： $a < b$：  
由于一个数的余数必须小于这个数，所以这种情况不可能。  

讨论完了，放代码。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,ans;
int moder;

int main() {
	scanf("%d %d",&n,&m);
	if(n < m) printf("0\n");
	else if(n == m) {
		printf("infinity\n");
	} else {
		moder = n - m;
		for(int i = 1;i * i <= moder;i++) {
		//	printf("%d\n",i);
			if(moder % i == 0) {
				ans += (i > m);
				if(moder / i > m && moder / i != i) ++ans;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Pkixzx (赞：0)

我们首先考虑存在无限个的情况，发现只有在**a==b**时，才会存在无限个，开头特判即可。

由于这里没说明 a ≥ b ，所以存在 a < b ，但如果是这种情况，**没有一个满足条件的数**，也是开头特判输出0即可。

接下来就是常规的了，要a-x的余数为b，可得式子：**（a-x）%y=b**（y为任意自然数）。

化简式子得x=（a-b）的因数。

接下来就简单了，可得代码：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,t=0,y;
	cin>>n>>m;
	if(n==m) {cout<<"infinity";return 0;}//如果有无限个
	if(n<m) {cout<<0;return 0;}//没有一个
	else
	{
		y=n-m;
		for(int i=1;i*i<y;i++)//求因数个数
		{
			if(y%i==0) 
		    {
			    if(i>m)
			    t++;
			    else if(y/i>m)
			    t++;
		    }
		}
		
		int x=sqrt(y);
		if(x*x==y&&x>m)
		t++;
		cout<<t;//输出
	}
}

```


---

## 作者：江户川·萝卜 (赞：0)

## 题解 CF495B 【Modular Equations】
分三种情况。

1. $a<b$
2. $a=b$
3. $a>b$

----
### 1.$a<b$
假设有一个 $m$ ，使得 $a \bmod m=b$。

则如果 $a<m$ , $a\bmod m=a$；

如果 $a=m$，$a\bmod m=0<a$；

如果 $a>m$，$a\bmod m<a$。

所以无论如何都不能使 $a\bmod m>a$，输出`0`。

----
### 2. $a=b$
同上面，如果$a<m$，$a\bmod m=a=b$。

而 $>a$的数有无穷多个，所以输出`infinity`。

----
### 3.$a>b$
首先如果 $a\bmod x=b$，那么有 $a=kx+b$，然后 $a-b=kx$

也即 $x$ 是 $a-b$ 的因数，$O(\sqrt{n})$求出 $x$ 的个数即可。

注意 $x>b$ 这个限制条件。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,ans,x;
int main(){ 
    cin>>a>>b;
    if(a<b) cout<<"0";
    else if(a==b) cout<<"infinity";
    else{
        x=a-b;
        for(int i=1;i*i<x;i++)
            if(x%i==0){
                if(i>b) ans++;
                if(x/i>b) ans++;
            }
        int d=sqrt(x);
        if(d*d==x&&d>b) ans++;
        cout<<ans;
    }
    return 0;
}
```
如有错误，还请评论指正！

---

## 作者：BotDand (赞：0)

# Problems
给出两个整数$a,b$，问有多少个$x$，使得满足等式$a\mod x=b$
如果存在无限个，就输出$"infinity"$，否则输出满足条件$x$的个数
# Answer
分三种情况：
1. $a=b$
2. $a<b$
3. $a>b$

分别处理。

***

当$a=b$时，只要$x$比$b$大，等式就可以成立，有无数种。

***

当$a<b$时，没有一种情况，因为余数比被除数大。

***

当$a>b$时，将$a\mod x=b$化简得$(a-b)\mod x=0$，因此只要求$a-b$中大于$b$的因数的个数。
# Code
```pascal
var
  a,b,s:int64;
  i:longint;
begin
  readln(a,b);
  if a=b then begin writeln('infinity');exit;end;//当a=b时
  if a<b then begin writeln(0);exit;end;//当a<b时
  a:=a-b;//算差
  for i:=1 to trunc(sqrt(a)) do//求因数，因为因数具有成对性，所以只用找到a的平方根即可
    if a mod i=0 then//如果是a的因数
      begin
        if i>b then inc(s);//如果小因数比b大，则多一种情况
        if a div i>b then if i*i<>a then inc(s);//如果小因数比b大，并且不是a的平方根，则又多一种情况
      end;
  writeln(s);//输出情况数
end.
```

---

