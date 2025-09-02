# Subtractions

## 题目描述

You've got two numbers. As long as they are both larger than zero, they go through the same operation: subtract the lesser number from the larger one. If they equal substract one number from the another. For example, one operation transforms pair (4,17) to pair (4,13), it transforms (5,5) to (0,5).

You've got some number of pairs ( $ a_{i},b_{i} $ ). How many operations will be performed for each of them?

## 样例 #1

### 输入

```
2
4 17
7 987654321
```

### 输出

```
8
141093479
```

# 题解

## 作者：添哥 (赞：1)

由于$1≤n≤1000,1≤a_i,b_i≤10^9$，所以显然不可以直接模拟。
## 剪枝一：
让我们来看一下这个样例↓↓↓
```
1
1 1000
```
看到这个样例，相信大家都珂以一秒出答案，为什么？因为$1000$ $÷$ $1=1000$啊！

所以当$a$ $mod$ $b=0$时，我们就直接返回$a÷b$。
## 剪枝二
让我们再来看一下这个样例↓↓↓
```
1
2 999
```
这个样例的答案也显而易见，是$501$。我们先计算$f(2,998)$，显然是499；再计算$f(2,1)$，为$2$，所以答案为$499+2=501$

所以，对于任意$a<b$，我们都珂以把$f(a,b)$分解为$a÷b+f(b,a\%b)$

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int f(int a,int b)
{
    if(a%b==0)//剪枝一
    {
        return a/b;
    }
    return (a/b)+f(b,a%b);//剪枝二
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b;
        cin>>a>>b;
        if(a<b)
        {
            a+=b;
            b=a-b;
            a-=b;
        }
        cout<<f(a,b)<<endl;
    }
    return 0;
}
```


---

## 作者：H6_6Q (赞：1)

### 题目大意：
给你两个数 $a$ , $b$ ( $a$ , $b$ $\le$ $10^9$ )，每次用大的减去小的，问当某个数为 $0$ 时，一共减了多少次。
### 思路：     
假设 $a$ 为大的数，$b$ 为小的数，且两数相差很大     
那么 $a$ 最后可能会变成 $a-b-b-...-b$     
将 $-b-b-...-b$ 合并，就可以得到 $- k \times b(k\times b \le a$ 且 $a-k\times b < b)$     
这个 $k$ 其实就是 $a$ 整除 $b$ 的结果 。        
所以     
$a-b-b-...-b = a-k \times b = a-(\lfloor \frac{a}{b} \rfloor)\times b = a\mod b$              
所以每次 $a$ 最终都会变成 $a\mod b$，变化次数即 $\lfloor \frac{a}{b} \rfloor$          
可以用类似 $\gcd$ 的辗转相除法来完成。      
复杂度和 $\gcd$ 一样，都是 $O(\log n)$ 的。
### Code：
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#define LL long long

using namespace std;

LL read()
{
	LL ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

int n,a,b;

inline int get(int x,int y);

int main()
{
	n=read();
	while(n--)
	{
		a=read();b=read();
		printf("%d\n",get(a,b));
	}
	return 0;
}

//用类似 gcd 的辗转相除法
//x 为大数，y 为小数
//如果刚开始 x < y ，那么在一次操作后，x 与 y 将互换
inline int get(int x,int y)
{
	if(!y)  如果小的数为 0 ，那么操作已经完成，返回 0
		return 0;
	// 否则将大数设为 y ，小数设为 x % y ( y > x % y )
	// 并把变化次数 x / y 加入答案
	return get(y,x%y)+x/y;
}
```


---

## 作者：WanderingTrader (赞：0)

$\mathrm{update\ on\ 2020-07-10}$ 根据审核反馈对优化分析部分做了修改，添加了一些内容。

洛谷CF爆了，到官网上提交，然后A了这题。  
### 题目分析
如果乍一看没思路的话，不妨手算样例。  
|步数|二元组
|:--:|:-:
|0|$4,17$
|1|$4,13$
|2|$4,9$
|3|$4,5$
|4|$4,1$
|5|$3,1$
|6|$2,1$
|7|$1,1$
|8|$1,0$

有没有想起什么熟悉的东西？  
没错，这不是 **GCD** 嘛！
### 代码
 
如果按照题意模拟，一遍一遍做减法，代码即为：
```cpp
void gcd(int a,int b)
{
	if(a < b) 
		swap(a,b);
	if(!b)
		return;
	++ans;
	gcd(b,a-b);
}
```
看起来不错，但样例输出里有一个：
```
141093479
```
它约等于$1.4\times10^8$，执行了这么多次gcd，肯定会超时，需要再优化。

我们观察表格 $0$~$4$行可以发现，当 $a>b$ 的时候，它会一直做减法，实际上浪费了大量的时间（因为最终结果和取模是一样的）。那么可以采用辗转相除法的优化方式，把减法改成取模运算。  

那答案该怎么处理呢？
实际上，每次加上 $\left\lfloor\dfrac{a}{b}\right\rfloor$即可。  
比如$(4,17)$，答案加上$\left\lfloor\dfrac{17}{4}\right\rfloor=4$，在表格中恰好占了4行(1~4行)。

修改后的代码如下：
```cpp
void gcd(int a,int b)
{
	if(a < b) 
		swap(a,b);
	if(!b)
		return;
	ans += a / b;
	gcd(b,a%b);
}
```
加入输入输出的框架，即为全部代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define ll long long 
ll ans;
void gcd(int a,int b)
{
	if(a < b) 
		swap(a,b);
	if(!b)
		return;
	ans += a / b;
	gcd(b,a%b);
}
int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		int a,b;
		ans = 0;
		scanf("%d%d",&a,&b);
		gcd(a,b);
		printf("%lld\n",ans);
	}
	return 0;
}
```
代码还是很简单的，就是别忘了清空ans。  

$$\mathrm{The\ End.}$$

---

## 作者：zoobidubi (赞：0)

这题不禁让人联想到高中的某个叫更相减损术的东西

不过重点是，更相减损术是用来求最小公约数和最大公倍数的

## 这题要你求的是减到某个数为0要减几次！！！

用for循环暴力减吗？NO！请看看数据范围

## 10^9！

这下就要用数学技巧了

我们看看每次往下减能减几次，是不是要一直减到另外一个数字比自己原来的大？

那么

我们可以用一个ans存每回减多少次才能使一个数个另外一个数的大小关系发生改变

设两个数分别为n, m && n > m

这个减的次数就是(n - (n % m)) / m

就是减去取余后的，刚好能整除得多少就是多少次

这样无疑减去了很多枚举的步骤

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans, n, m;
int main()
{
    int T;
    cin >> T;//T组数据
    while (T --)
    {
       cin >> n >> m;
       ans = 0;//ans一定要清为0！不然数字会累加！
       while (n != 0 && m != 0)//减到有一个为0
       {
    	    long long x = max (n, m), y = min (n, m);
            //这样就保证了x>y
    	    ans += (x-(x%y))/y;//ans加上每次减少的次数
    	    m = x % y;//m更新等于减少后的数
    	    n = y;//n等于原来用来减的数
       }
       cout << ans << endl;//输出和换行即可
    }
    return 0;
}

```



---

