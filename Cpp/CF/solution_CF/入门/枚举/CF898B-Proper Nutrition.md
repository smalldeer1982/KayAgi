# Proper Nutrition

## 题目描述

Vasya has $ n $ burles. One bottle of Ber-Cola costs $ a $ burles and one Bars bar costs $ b $ burles. He can buy any non-negative integer number of bottles of Ber-Cola and any non-negative integer number of Bars bars.

Find out if it's possible to buy some amount of bottles of Ber-Cola and Bars bars and spend exactly $ n $ burles.

In other words, you should find two non-negative integers $ x $ and $ y $ such that Vasya can buy $ x $ bottles of Ber-Cola and $ y $ Bars bars and $ x·a+y·b=n $ or tell that it's impossible.

## 说明/提示

In first example Vasya can buy two bottles of Ber-Cola and one Bars bar. He will spend exactly $ 2·2+1·3=7 $ burles.

In second example Vasya can spend exactly $ n $ burles multiple ways:

- buy two bottles of Ber-Cola and five Bars bars;
- buy four bottles of Ber-Cola and don't buy Bars bars;
- don't buy Ber-Cola and buy $ 10 $ Bars bars.

In third example it's impossible to but Ber-Cola and Bars bars in order to spend exactly $ n $ burles.

## 样例 #1

### 输入

```
7
2
3
```

### 输出

```
YES
2 1
```

## 样例 #2

### 输入

```
100
25
10
```

### 输出

```
YES
0 10
```

## 样例 #3

### 输入

```
15
4
8
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
9960594
2551
2557
```

### 输出

```
YES
1951 1949
```

# 题解

## 作者：Alex_Wei (赞：11)

#### 看懂题目后看了看数据范围，出题人还是比较良心的，可以暴力枚举AC

### 1.枚举

#### 1.1 思路：$x$从小到大枚举，如果符合题意就输出并退出

1.2 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a, b, n;
int main()
{
	cin>> n>> a>> b;
	for(int x=0; x<=n/a; x++)//x的范围为0~n/a
		if( (n-x*a) %b == 0 )//如果剩余的钱是b的倍数
			cout<< "YES\n"<< x<< " "<< (n-x*a)/b,exit(0);//输出YES和x，y 
	cout<<"NO";//如果没有枚举到答案就输出NO
	return 0;
}
```

1.3 这是比较简单，也比较笨的方法，看到题目就应该能够想出来

但如果 $a$，$b$，$n$的范围变大了怎么办？如果$1≤a$，$b$，$n≤10^{18}$，在极端数据下就会执行很多很多次，TLE在所难免

#### 这时候就要使出必杀技：扩展欧几里得 $(exgcd)$ 了

### 2.$exgcd$ 详解

2.1 扩展欧几里得算法，顾名思义，就是在欧几里得算法的基础上扩展一下

你需要知道：

2.2 欧几里得（ $gcd$ ）算法，又称辗转相除法，用来求最大公约数，一般代码如下

```
int gcd (int x, int y)
{
	if(y == 0) return x;
	else return gcd(y, x%y);
}
```

#### 一般用 $gcd(a,b)$ 表示 $a,b$ 的最大公约数，下文都用 $gcd$ 代替


2.3 裴蜀定理：在 $ax + by = c$ 中，该方程有解当且仅当 $c$ 是 $gcd$ 的倍数



2.4 如何求解 $ax + by = c$ ？

- 只需要求出 $ax + by = gcd$ 这样的线性丢番图方程（又称裴蜀等式），**再把求得的 $x$，$y$ 乘上 $c/gcd$ 就可以了（当c不是gcd的倍数时方程无解）**

- 设 $ax+by = gcd$ 的解为 $x_1$，$y_1$，由裴蜀定理可知，该方程一定有解

- 由欧几里得算法可知，$gcd(a,b) = gcd(b,a$%$b$ )，所以 $bx+(a$%$b)y$ = $gcd$ 也一定有解，设解为 $x_2$，$y_2$

- 我们知道，$a$%$b$可以写成 $a- [ a/b ] *b$，其中 $[]$ 为下取整符号

- 所以$bx_2+(a$%$b)y_2 = gcd$

$bx_2 +( a- [ a/b ] * b )y_2 = gcd$

$bx_2 + ay_2- [ a/b ] * b * y_2 = gcd$

$ay_2 + x_2 * b - [ a/b ]* y_2 *b = gcd$

$ay_2 + b( x_2 - [ a/b ] * y_2 ) = gcd$

- 将这个方程与$ax_1 + by_1$对比一下，就能很清楚的得到

### $x_1 = y_2$ , $y_1 = ( x_2 - [ a/b ] * y_2 )$

特殊的，当 $a = gcd,b = 0$时，取$x_n = 1,y_n = 0$

- 最后再由上面这个式子推出来就行了

#### 再来一遍推导过程，要掌握牢！

![](https://cdn.luogu.com.cn/upload/pic/52973.png)

- 这样我们就能够求出 $ax + by = gcd$，也就是 $ax + by = c$ 的解了

代码：

```cpp
#define ll long long
ll exgcd(ll u, ll v, ll &x, ll &y)
{
	if( v == 0 ){x=1, y=0 ;return u;}
	ll gcd = exgcd (v, u%v), r=x;
	x=y, y= r-u/v*y ;
	return gcd;
}
```


2.5 $x,y$ 的取值

当我们找到 $ax + by = c$ 中的特殊解，我们就可以根据这个特殊解求出通解

$x = x1 + (b/gcd) * t$

$y = y1 - (a/gcd) * t$

### 在实际意义中，对负数取模得到的是正数，但在C++中，对负数取模会得到负数，所以一般用$(x$%$s+s)$%$s$

### exgcd方法求得的是 $x+y$ 绝对值最小的一组解，所以会出现负数，还有，当方程有解但没有非负整数解也是不行的！

分情况讨论：

- 当$x$小于0时，我们求出能够将$x$变为非负数的最小的$t$，即先算出 $x$%$(b$/$gcd)$ 实际的余数$k$：$(x$%$(b/gcd)+b/gcd)$%$(b/gcd)$，再求出最小的$t$：$(k-x)/(b/gcd)$

- 当$y$小于$0$时，步骤同上，有些细节需要改动，自己思考吧！

代码：
```cpp
if( x<0 ){//如果x小于0 
	ll s=b/d, k=(x%s+s)%s, t=(k-x)/s;//为了方便这里就用s代替b/gcd了
	x+= t*s, y-= t*(a/d);//同步骤2.5
}
else if( y<0 ){//同x
	ll s=a/d, k=(y%s+s)%s, t=(k-y)/s; 
	y+= t*s, x-= t*(b/d);
}
```

#### 2.6 $exgcd$本题代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long//十年OI一场空，不开long long见祖宗！ 
ll a, b, n, d, x, y;//d为gcd；x，y为解
ll exgcd(ll u, ll v)
{
	if( v == 0 ){x=1, y=0 ;return u;}//特殊值
	ll gcd = exgcd (v, u%v), r=x;//r：没被覆盖的x
	x=y, y= r-u/v*y ;//根据公式计算出上一组解
	return gcd;
}
int main()
{
	cin>> n>> a>> b;
	d= exgcd(a, b);//求ax+by=gcd的解，和gcd
	if(n%d)cout<<"NO",exit(0);//如果c不是gcd的倍数就输出NO 
	x*= n/d, y*= n/d;//求出真正的解（ax+by=c）
	if( x<0 ){//如果x小于0 
		ll s=b/d, k=(x%s+s)%s, t=(k-x)/s;//为了方便这里就用s代替b/gcd了
		x+= t*s, y-= t*(a/d);//同步骤2.5
	}
	else if( y<0 ){//同x
		ll s=a/d, k=(y%s+s)%s, t=(k-y)/s; 
		y+= t*s, x-= t*(b/d);
	}
	if( x<0 || y<0 ) cout<<"NO", exit(0);
	//当方程有解但没有非负整数解也不行，之前就在这里被坑了
	//例如 5,7,8，应该输出NO，不加这行输出-5,5
	cout<< "YES\n"<< x<< " "<<y;//输出答案
	return 0;
}
```

如果有错误或问题欢迎在右侧——>评论区指正或直接私信给我

码字不易，点个赞再走呗，谢谢！

$Upd:2019.5.4 :$ 把排版弄美观了一点，加了$latex$，求过

---

## 作者：kon_tori (赞：2)

### 题意
$\texttt{Vasya}$有$\texttt{n}$元，
每瓶可乐$\texttt{a}$元，
每瓶酒$\texttt{b}$元，
求是否能购买$\texttt{x}$瓶可乐，$\texttt{y}$瓶酒，使钱刚好够用。(即$\texttt{x*a+y*b=n}$)

### 思路&代码实现
看到题目，首先想到双层循环暴力枚举(~~暴力出奇迹啊~~)。


$\texttt{code:}$
```cpp
/* light_chaser */
  #include<bits/stdc++.h>
  #define ll long long//考虑到数据可能比较大，我开了long long 
  using namespace std;
  ll n;
  ll a,b;
  int main(){
      cin>>n>>a>>b;
      for(ll i=n/a; i>=0; i--){//只用循环n/a次
          for(ll j=n/b; j>=0; j--){//只用循环n/b次
              if(i*a+j*b==n){//存在满足要求的情况
                  puts("YES");
                  cout<<i<<" "<<j<<"\n";
                  goto sp;//跳出循环
              }
          }
      }
      puts("NO");//不存在满足要求的情况
      sp : ;
      return 0;
  } 
```

但众所周知，暴力容易 ``TLE`` ，上面的代码 ``TLE`` 在了 ``#49`` 。

有一种可以去掉一层循环的方法，可以避免 ``TLE`` ：如果买完可乐后(比如$\texttt{p}$瓶)，剩下的钱刚好够买整数瓶酒(即$\texttt{(n-p*a)\%b=0}$)，则满足要求。

$\texttt{code:}$
```cpp
/* light_chaser */
  #include<bits/stdc++.h>
  #define ll long long 
  using namespace std;
  ll n;
  ll a,b;
  int main(){
      cin>>n>>a>>b;
      for(ll i=n/a; i>=0; i--){
          if((n-i*a)%b==0){//改动在此处
              puts("YES");
              cout<<i<<" "<<(n-i*a)/b<<"\n";
              goto sp;
          }
      }
      puts("NO");
      sp : ;
      return 0;
  }
  
```
``AC`` ， ``1.14s``。

### 后记
感谢管理员的辛勤付出！

蒟蒻的第$\texttt{9}$篇题解，望通过。

---

## 作者：yf最qhhh (赞：1)

要求 $X·A + Y·B=n$，那么我们先将原式变个形：

$\qquad\qquad X·A+Y·B=n$

$\qquad\qquad Y·B=n-X·A$

$\qquad\qquad Y=\frac{n-X·A}{B}$

所以我们并不需要两个循环。

现在最容易想到的思路就是，$1\le X\le n/A$，每次判断 $\frac{n-X·A}{B}$ 的余数是否为 $0$。

但这样显然会超时。

所以我们再来给原式变形：

$\qquad\qquad X·A+Y·B=n$

$\qquad\qquad X·A+Y·B≡n\qquad (\mod B)$

$\qquad\qquad X·A≡n\qquad(\mod B)$


所以现在就变成了，$1\le X\le n/A$，每次判断 $X·A\mod B$ 与 $n\mod B$ 是否相同，相同就输出 $X$ 与 $\frac{n-X·A}{B}$。
```cpp
#include<iostream>
using namespace std;

int main(){
    int n,a,b;
	cin>>n>>a>>b;
	for(int i=0;i<=n/a;i++)
		if(i*a%b==n%b)
			return cout<<"YES"<<endl<<i<<' '<<(n-i*a)/b,0;
	cout<<"NO";
}
```


---

## 作者：__Hacheylight__ (赞：1)

我用的是暴力方法。因为不会用扩展欧几里得。。。

暴力枚举x，判断有没有整数y使式子成立。
如果枚举的所有x都不成立，输出“NO”

代码：
```cpp
#include <bits/stdc++.h>
using namespace std ;
int main(){
    int a,b,n ;
    scanf("%d%d%d",&n,&a,&b) ;
    int flag=0 ;   
    for (int i=0;i*a<=n;i++){   
        if ((n-i*a)%b==0){  
            flag=1;  
            printf("YES\n") ;   
            printf("%d %d",i,(n-i*a)/b) ;  
            return 0 ;
        }
    }
    printf("NO\n") ;
}
```

---

## 作者：szkzyc (赞：0)



给你可乐与啤酒的单价，以及全部饮料的总价。

如果可乐和啤酒的数量为自然数的话，那么就输出 YES 与数量
，否则就输出 NO。





这道题根据数据范围可得只这题应该用 $O(N)$ 的复杂度去解这道题，但是如果纯暴力枚举的话应该为 $O(N^2)$ 的复杂度，所以我们要进行优化。

由于这是一个方程，所以如果求出了可乐的数量，那么啤酒 也肯定出来了，所以可以只枚举可乐的数量，再通过总价 ，再判断啤酒的数量是否为自然数即可。

+ ### $Std$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n, a, b; 
int main(){
    cin >> n >> a >> b; //输入总价，可乐单价与啤酒单价 
    for(int x = 0; x <= n / a; x++){ //枚举可乐数量
    	int y = (n - x * a ) / b; //根据总价推出啤酒数量 
    	if(x * a + y * b == n) puts("YES"), cout << x << " " << y , exit(0); //如果等式成立，输出YES与xy，结束程序 
	}
	puts("NO");//如果没有枚举到正确答案，输出NO 
	return 0;
}
// CF898B题解 
// Accepted in 2020/2/28
// by szkzyc 
```

### $---end---$

---

## 作者：Keep_RAD (赞：0)

这一题很简单，可能很多人第一个念头就是双重循环，直接看总和是不是等于`n`，如果有，输出`YES`。循环到最后还没有就输出`NO`。

显然，是不可以的，为什么呢？因为数据范围是`10^7`，显然不可以进行双重循环。

------------
正解：

思路也是非常好想的，枚举有多少瓶可乐，如果剩下的钱数正好可以全用`b`来凑（也就是剩下的钱数$mod$ $b$），那么直接输出，`return 0` 。如果代码进行到了最后都没有输出，就说明没有方案，输出`NO`。

详细解释在代码里：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b;//n是钱数，a是一瓶可乐的钱数，b是一瓶酒的钱数
int main()
{
    cin>>n>>a>>b;
    if(n%a==0) 
    { 
        cout<<"YES\n"<<n/a<<" 0";
        return 0; 
    } 
    if(n%b==0) 
    {
        cout<<"YES\n"<<"0 "<<n/b;//如果只买可乐或酒就能满足结果，直接输出
        return 0;//记得return 0,不然会输出两次
    }
    for(int i=0;i<=n/a;i++)//枚举x的值
        if((n-i*a)%b==0)//如果剩余的钱只用b就能凑出来，那么可以
        {
            cout<<"YES\n"<<i<<" "<<(n-i*a)/b;
            return 0;//提前终止
        }
    cout<<"NO";//没有方案输出NO
    return 0;
}
```
ヾ(￣▽￣)Bye~Bye~

---

## 作者：Forever1507 (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF898B)
$n\le10000000$的话暴力就行了， $O(n)$ 最多 $1e7$ 还是不会惨遭 $TLE$ 的。

因为题目说了 $X,Y$ 是**非负整数**，所以枚举的时候 $X$ 要从 $0$ 开始~~否则实测#35会凉~~。

一路枚举到 $a \times X \le n$  ,当 $n-(a \times X)$ 能被 $b$ 整除就直接输出，然后结束，如果除了循环就说明找不到，输出 `NO` 即可。


$Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
	cin>>n>>a>>b;
	for(int i=0;i<=n/a;i++){
		if((n-(a*i))%b==0){
			puts("YES");//puts自带换行
			cout<<i<<' '<<(n-(a*i))/b;
			return 0;
		}
	}
	puts("NO");
	return 0;
} 
```


---

## 作者：happybob (赞：0)

本题的确可以用 `exgcd` 做，但对于数论不扎实的而言 `exgcd` 求的是形如 $\large ax+by=n$ 的通解，即 $\large x,\, y \in Z$，本题求的是 $\large x,\, y \ge 0$ 的解，所以直接来个 $\Large O(\frac{a}{n})$ 的暴力就好了。

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int a, b, n;
	cin >> n >> a >> b;
	for (register int i = 0; i <= n / a; i++)
	{
		if ((n - i * a) % b == 0)
		{
			cout << "YES\n";
			cout << i << " " << (n - i * a) / b << endl;
			//system("pause");
			return 0;
		}
	}
	cout << "NO\n";
	//system("pause");
	return 0;
}
```


---

## 作者：DANNY0926 (赞：0)

**不定方程！**

对于入门题来说，似乎有点太高级了?



```cpp
#include<bits/stdc++.h>
//using namespace std;
int a,b,n;
int main(){
    cin>>n>>a>>b;//输入
    for(int i=0;i*a<=n;i++)
        if((n-i*a)%b==0){//判断y是否为整数  
            cout<<"YES"<<endl;
            cout<<i<<(n-i*a)/b<<endl;//输出
            return 0 ;//结束程序
        }
    cout<<"NO"<<endl;
    //return 0;
}
//不要复制！后果自负！


---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF898B)
# 前置芝士
不定方程：
是指方程的解的范围为整数、正整数、有理数或代数整数等的方程或方程组，且未知数的数量大于方程个数

解法：
~~暴力枚举~~

举个栗子：
$3x-2y=10$ 这个方程有$2$个未知数，而只有一个方程，所以它的解不是唯一的

# 思路

可以将本题看作一个不定方程：$a\times x+b\times y=n$（其中a,b,n为常数）
所以只需暴力枚举x，找到符合要求的y即可

# 废话不多说，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int cola,wine,money;
int main(){
    cin>>money>>cola>>wine;
    for(int i=0;i*cola<=money;i++){//i*cola表示买i瓶可乐所需的钱（枚举可乐） 
        if((money-i*cola)%wine==0){//判断剩下的钱能不能买整数瓶酒 
            cout<<"Yes"<<endl<<i<<" "<<(money-i*cola)/wine<<endl;//输出能 
            return 0;
        }
    }
    cout<<"No"<<endl;//否则输出不能 
    return 0;
}
```
代码看完了，你学废了吗？

---

## 作者：RBI_GL (赞：0)

**一道循环枚举的题目。**

先看式子：X·A + Y·B=n 

自然会想到枚举X，Y。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull a,b,n;
int main()
{
	cin>>n>>a>>b;
	for (int x=0;x<=n;x++)
	   for (int y=0;y<=n;y++)
	   {
	   	    if (x*a+y*b == n) 
	   	    {
	   	    	cout<<"YES"<<endl;
	   	    	cout<<x<<" "<<y<<endl,exit(0); 
			}
	   }
	cout<<"NO";
	return 0;
}
```

**很明显，数字大了就不行。**

优化：
-

将式子变形：
 Y·B=n -X·A 

推出：**（n -X·A ）mod B = 0**

这时候用一重循环枚举x就可以了

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull a,b,n;
int main()
{
	cin>>n>>a>>b; //读入
	for (int x=0;x<=n;x++) //枚举x
	{
		if( (n-x*a)%b == 0 )//如果剩余的钱是b的倍数 
		{
			cout<<"YES"<<endl<<x<< " "<<(n-x*a)/b,exit(0); //输出YES和x，y
		}	
	}
	cout<<"NO"; //找不到符合要求的就输出No 
	return 0;
}
```
**但是还是不能过**


**原因：循环的上限还可以缩小道x/a。**

AC Code：
-
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull a,b,n;
int main()
{
	cin>>n>>a>>b; 读入
	for (int x=0;x<=n/a;x++)
	{
		if( (n-x*a)%b == 0 )//如果剩余的钱是b的倍数
		{
			cout<<"YES"<<endl<<x<< " "<<(n-x*a)/b,exit(0); //输出YES和x，y 
		}	
	}
	cout<<"NO"; //找不到符合要求的就输出No 
	return 0;
}
```
无注释版：
-
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull a,b,n;
int main()
{
	cin>>n>>a>>b;
	for (int x=0;x<=n/a;x++)
	{
		if( (n-x*a)%b == 0)
		{
			cout<<"YES"<<endl<<x<< " "<<(n-x*a)/b,exit(0);
		}	
	}
	cout<<"NO"; 
	return 0;
}
```



---

