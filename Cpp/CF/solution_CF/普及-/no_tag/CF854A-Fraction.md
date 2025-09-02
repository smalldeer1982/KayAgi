# Fraction

## 题目描述

Petya is a big fan of mathematics, especially its part related to fractions. Recently he learned that a fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF854A/9f8335062cbc9ed9ecb9607f5d06d53170cb1e1a.png) is called proper iff its numerator is smaller than its denominator ( $ a<b $ ) and that the fraction is called irreducible if its numerator and its denominator are coprime (they do not have positive common divisors except $ 1 $ ).

During his free time, Petya thinks about proper irreducible fractions and converts them to decimals using the calculator. One day he mistakenly pressed addition button ( $ + $ ) instead of division button ( $ ÷ $ ) and got sum of numerator and denominator that was equal to $ n $ instead of the expected decimal notation.

Petya wanted to restore the original fraction, but soon he realized that it might not be done uniquely. That's why he decided to determine maximum possible proper irreducible fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF854A/9f8335062cbc9ed9ecb9607f5d06d53170cb1e1a.png) such that sum of its numerator and denominator equals $ n $ . Help Petya deal with this problem.

## 样例 #1

### 输入

```
3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
4
```

### 输出

```
1 3
```

## 样例 #3

### 输入

```
12
```

### 输出

```
5 7
```

# 题解

## 作者：brealid (赞：5)

来谈一谈数学做法。

## 观察数据
首先打一个[暴力程序][code#1]，然后就 [AC][sub#1] 了。  
然后考虑数学方法。

然后~~很容易~~想到要把 n 分成奇数与偶数两种情况讨论
### n 为奇数

```data
 n | answer |
-------------
 3 |  1 2   |
 5 |  2 3   |
 7 |  3 4   |
 9 |  4 5   |
```
好了，这还是比较好分析的。  
当 n 为奇数时，答案为 $(n - 1) / 2$ 与 $(n + 1) / 2$

> 数学证明： 

> 可行性
> > 设分子为 $a$，则分母为 $(n + 1) / 2 = (n - 1 + 2) / 2 = (n - 1) / 2 + 2 / 2 = (n - 1) / 2 + 1 = a + 1$  
> > 所以 $a$，$a+1$ 一定为相邻自然数    
> > 所以分子和分母必定互质  

> 最优性
> > 显然这个分数也是最大的

### n 为偶数

```data
 n | answer |
-------------
 4 |  1 3   |
 6 |  1 5   |
 8 |  3 5   |
10 |  3 7   |
12 |  4 7   |
14 |  4 9   |
16 |  6 9   |
```
第一眼看去没有什么规律，然后发现好像又有一点儿……

于是再分成两种情况

#### n 为偶数但不为 4 的倍数

```data
 n | answer |
-------------
 6 |  1 5   |
10 |  3 7   |
14 |  4 9   |
```

易发现，答案为 $n / 2 - 2$ 与 $n / 2 + 2$

> 数学证明：  

> 可行性  
> > 设分子为 $a$，则分母为 $n / 2 - 2 + 4 = a + 4$  
> > 因为 n 为偶数但不为 4 的倍数，所以 $n / 2$ 为奇数，所以 $a$ 为奇数  
> > 因为 $gcd(a, b)(a < b) = gcd(a, b - a)$ ，所以 $gcd(a, a + 4) = gcd(a, 4) $。因为 $a$ 为奇数，所以 $ gcd(a, 4) $ 为 1，所以原分数为最简真分数  

> 最优性
> > 1. $n / 2$ 与 $n / 2$   
> > > 显然不合题意  
> > 2. $n / 2 - 1$ 与 $n / 2 + 1$   
> > > 设分子为 $a$，则分母为 $n / 2 - 1 + 2 = a + 2$  
> > > 同理可证$gcd(a, a + 2) = gcd(a, 2) $   
> > > 又因为 n 为偶数但不为 4 的倍数，所以 $n / 2$ 为奇数，所以 $a$ 为偶数，所以 $ gcd(a, 2) $ 为 2，所以不合题意  
> > 所以 $n / 2 - 2$ 与 $n / 2 + 2$ 最优

#### n 为偶数且为 4 的倍数

```data
 n | answer |
-------------
 4 |  1 3   |
 8 |  3 5   |
12 |  4 7   |
16 |  6 9   |
```

易发现，答案为 $n / 2 - 1$ 与 $n / 2 + 1$

> 数学证明：  

> 可行性  
> > 设分子为 $a$，则分母为 $n / 2 - 1 + 2 = a + 2$  
> > 因为 n 为偶数且为 4 的倍数，所以 $n / 2$ 为偶数，所以 $a$ 为奇数  
> > 因为 $gcd(a, b)(a < b) = gcd(a, b - a)$ ，所以 $gcd(a, a + 2) = gcd(a, 2) $。因为 $a$ 为奇数，所以 $ gcd(a, 2) $ 为 1，所以原分数为最简真分数  

> 最优性
> > $n / 2$ 与 $n / 2$ 显然不合题意  
> > 所以 $n / 2 - 2$ 与 $n / 2 + 2$ 最优

放出代码与评测结果

[![][p#code]][code#2] [![][p#sub]][sub#2]
 

[code#1]:https://paste.ubuntu.com/p/4dj5KkwmXT/
[code#2]:https://paste.ubuntu.com/p/gfg6vDYbWG/
[sub#1]:https://www.luogu.org/recordnew/show/19924430
[sub#2]:https://www.luogu.org/recordnew/show/19924533
[p#code]:https://cdn.luogu.com.cn/upload/pic/61106.png
[p#sub]:https://cdn.luogu.com.cn/upload/pic/61107.png

---

## 作者：Ousmane_Dembele (赞：3)

这道题还是蛮水的，没有特别神的思路，特别长的代码，特别怪的算法

如果不懂gcd戳[这里](https://baike.baidu.com/item/GCD/2104053?fr=aladdin#1)

思路：从2/n开始向下遍历，当i和n-i互质时输出

代码：

```
#include<bits/stdc++.h>
using namespace std;
int gcd(int p, int q) {return q==0?p:gcd(q,p%q);}//gcd算法
long long ans,n;//int也行
int main(){
    cin>>n;
    for(int i=n/2;i>=1;i--){//遍历
        if(gcd(i,n-i)==1){//互质
            cout<<i<<" "<<n-i;//输出
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：清清老大 (赞：2)

## 题目

求一个最简真分数,使得分子与分母的和等于$n(3 \le n \le 1000)$

输入$n$

输出符合条件的最大分数的分子和分母

## 思路

因为$n$的范围小,所以我们可以循环枚举分子,从$\frac n2$开始向下遍历,这样分子就是$i$,分母就是$n - i$，由于题目中说是最简真分数,所以$i,n-i$互质,即$\gcd(n,n-i)=1$.

$\gcd$可以用辗转相除法得出

```cpp
int gcd(int a,int b)
{
    if(a % b)
        return gcd(b,a % b);
    return b;
}
```


## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);//输入n
    for(int i = n / 2;i > 0;i --)//遍历分子
    //因为题目要求输出最大的真分数,所以从n/2开始
    {
        if(__gcd(i,n - i) == 1)//i是分子,n-i是分母
        //用STL中的__gcd求最大公因数,最大公因数等于1就说明分子分母互质
        {
            printf("%d %d",i,n - i);// 输出结果
            return 0;
        }
    }
}
```


---

## 作者：thomas_zjl (赞：2)

先来看一下题目。

我们要求一个小于$n$的最大分数，且分子$+$分母$=n$。

但那个分数一定是最简分数，所以要```if(__gcd(i,b)==1)```才行。

接下来看看代码吧。

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=n/2;i>=1;i--)//要让这个分数是真分数，所以要n/2开始算。
	{
		int b=n-i;//求出另一个数。
		if(__gcd(i,b)==1)//如果他们互质。
		{
			cout<<i<<" "<<b;//直接输出。
			return 0;	
		}	
	} 
    return 0;
}
```



---

## 作者：TLMPEX (赞：1)

思路：暴力枚举a然后看哪种情况符合条件就输出，思路详见代码。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,i;
	cin>>n;
	for(i=n/2;i>=1;i--)
		if(__gcd(i,n-i)==1){//__gcd为c++自带取最大公因数函数
			cout<<i<<" "<<n-i;
			return 0;
		}
}
```

---

## 作者：happybob (赞：1)

这里给两种gcd算法（欧几里得不说了，大家都懂）

# 一、__gcd

这是algorithm中的求最大公约数函数，noip等比赛会判CE，慎用

# 二、 $gcd(x, y) = x * y / lcm(x, y)$

$\large∴$

$\Large lcm(x, y) = x * y / gcd(x, y)$

$\Large∵$

$\Large gcd(x y) = x * y / lcm(x, y)$

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int lcm(int x, int y)
{
    int tmp = x;
    while(x % y != 0)
    {
        x += tmp;
    }
    return x;
}

int gcd(int w, int h)
{
    return w * h / lcm(w, h);
}

int main()
{
    int n, x;
    cin >> n;
    x = n;
    n >>= 1;
    for(int i = n; i >= 1; i--)
    {
        if(gcd(i, x - i) == 1)
        {
            cout << i << " " << x - i << endl;
            return 0;
        }
    }
    return 0;
}
```


---

## 作者：REAL_曼巴 (赞：1)

这题要求一个分数。此题可以用小学的数学知识解决。最简分数的分子母是互质的，也就是分子母的最大公因数为一。

用一个 $gcd$ 函数或辗转相除法来求最大公因数

我们从输入数的一半大开始遍历，当 $i$ 和 $n$ 减 $i$ 互质时，输出并结束。

```
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
    if(a%b==0)
        return b;
    return 
        gcd(b,a%b);
} 
int n;
int main(){
	cin>>n;
    int y=n/2;
	for(int i=y;i>=1;i--){
		if(gcd(i,n-i)==1){
			cout<<i<<" "<<n-i;
			return 0;	
		}	
	} 
    return 0;
}
```


---

## 作者：Insouciant21 (赞：1)

题意：求 $a+b=n$ 时，使最简真分数 $\dfrac{a}{b}$ 最大的 $a,b$ 的值


$3\leq n\leq 1000$ ，直接暴力即可。

最简分数，即 $\gcd(a,b)=1$

因为 $a+b=n$ 且 $\dfrac{a}{b}$ 是真分数，所以 $a<\dfrac{n}{2}$ 。

故从 $\lfloor n/2\rfloor$ 开始枚举即可。

AC代码

```
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, a, b;
    scanf("%d", &n);
    for (int i = n / 2; i >= 1; i--) {
        if (__gcd(i, n - i) == 1) { // 计算 gcd
            a = i, b = n - i;
            break;
        }
    }
    printf("%d %d", a, b);
    return 0;
}
```

---

## 作者：hensier (赞：1)

我们先理清题意——对于输入的整数$n$和最终的两个数$a,b$，必定满足：
- $a,b,n∈N^*$
- $a+b=n$
- $gcd(a,b)=1$

接下来我们可以进行分类讨论。

当$n$为奇数的时候，$\frac{a}{b}$最大的时候（不一定满足$gcd(a,b)=1$），满足：
$$a=\frac{n-1}{2}$$
$$b=n-a=n-\frac{n-1}{2}=\frac{n+1}{2}$$

那么对于两个整数之和等于一个奇数，必定有$\red{\text{奇+偶=奇}}$。所以$a,b$的奇偶性是不同的。而$b-a=\frac{n+1-n+1}{2}=1$，所以这两个数$a,b$必定互质。具体的证明方法可以看这里：[传送门](https://www.luogu.com.cn/paste/w7x6ct3f)。

那么对于偶数呢？最大的两个和为$n$的整数为$a=\frac{n}{2}-1,b=\frac{n}{2}+1$。

那么，如果$\frac{n}{2}$为奇数，即$n\%4=2$，则$a,b$目前均为偶数，因此$a=\frac{n}{2}-1,b=\frac{n}{2}+1$不符合题意。所以退而求其次，即考虑$a=\frac{n}{2}-2,b=\frac{n}{2}+2$。这个时候我们发现$a,b$都为奇数。

此时$b-a=4$。有一个定理，叫做$\red{\text{两个差为4的正奇数互质}}$。具体证明方法：[传送门](https://www.luogu.com.cn/paste/3sw99r2t)。

传送门中介绍了一般情况的证明方法，而$4$是满足条件的，所以这时答案为$a=\frac{n}{2}-2,b=\frac{n}{2}+2$。

那么，对于$n\%4=0$，我们有$a=\frac{n}{2}-1,b=\frac{n}{2}+1$。这时$a,b$均为奇数，且相差$2$，用上述同理的方法可以证明这两个整数互质。

因此，我们可以得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/wer6vd4a.png)

$AC$代码：

```cpp
#include<stdio.h>
int n;
int main()
{
    scanf("%d",&n);
    if(n&1)printf("%d %d",n>>1,(n>>1)+1);
    else if(n%4)printf("%d %d",(n>>1)-2,(n>>1)+2);
    else printf("%d %d",(n>>1)-1,(n>>1)+1);
}
```
（注：$a\&1$可以当做条件来用，即$a$是否为奇数；
$a>>n$表示右移，等同于$a/2^n$（整除），这两个属于位运算，速度更快）

---

## 作者：MilkyCoffee (赞：1)

这道题特别sb，另感谢zjl提供水题（大雾

我们只需要枚举分子求出分母然后判断就珂以了。

注意：Petya thinks about **proper** irreducible fractions
（真分数）

```
// #include <bits/stdc++.h>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

inline int read() {
	int res = 0, f = 1;
	char k;
	while (!isdigit(k = getchar())) if (k == '-') f = -1;
	while (isdigit(k)) {
		res = res * 10 + k - '0';
		k = getchar();
	}
	return res * f;
}

int gcd(int x, int y){
    if (x % y == 0) return b;
    return  gcd(b, a % b);
} 

int n;

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	n = read();
	for (int a = n / 2; a >= 1; a--) { // 大->小
    	int b = n - a;
        if (gcd(a, b) == 1) {
        	cout << a << ' ' << b << endl;
            return 0;
        }
    }
	return 0;
}
```

---

## 作者：zhangyuhan (赞：1)

又是一道关于分数的题$hhh$

根据小学数学的知识可以知道，若使一个**真**(题目中已说$a<b$，即分子小于分母)分数更大，就需要分数值趋于$1$，即分子分母尽可能地接近。

再提一点，题面中没有说到的，$\dfrac{a}{b}$必须是**最简分数**，即$a$和$b$没有公约数，$a$、$b$互质。

$Q:$怎样判定$a$、$b$互质？

$A:$ $gcd(a,b)=1$即可。（$gcd(a,b)$指$a$和$b$的最大公约数）

~~为了展现$STL$的强大~~，我们可以使用$algorithm$库里的__gcd函数，不用手打$gcd$函数啦！

经过上面的分析，我们得到了主算法：从$n/2$向下枚举，令$i$为枚举变量，如果$gcd(i,n-i)=1$，就输出$i$和$n-i$。

$AC$ $Code$

```cpp
#include<iostream>
#include<algorithm>//STL是个好东西
using namespace std;

int n;

int main(){
    cin>>n;//输入
    for(int i=n/2;i>=1;i--){//枚举
        if(__gcd(i,n-i)==1){//如果互质
            cout<<i<<" "<<n-i<<endl;//输出
            break;//因为只求最大的一对，找到后即可跳出循环
        }
    }
    return 0;//完结撒花！
}
```

---

## 作者：YosemiteHe (赞：1)

题面中已经给出 $a<b$，那么就可以从 $\dfrac{n}{2}$ 到 $1$ 枚举 $a$（题面中说了要使 $\dfrac{a}{b}$ 最大，所以$a$ 越大越好），$b$ 即为 $n-a$。

而且 $\dfrac{a}{b}$ 必须是真分数，所以还要判断 $a$ 与 $b$ 是否互质。那如何判断呢？我们可以使用 `C++ STL` 当中的 `__gcd(x, y)` 函数，返回值就是 $\gcd(x, y)$。

所以判断 $a$ 与 $b$ 是否互质的条件即为 `if (__gcd(a, b) == 1)`。

Code :

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main(void) {
    cin >> n;
    for (int a = n / 2; a >= 1; --a) {
        int b = n - a;
        if (__gcd(a, b) == 1) {
            cout << a << " " << b << endl;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

题目传送门：[CF854A Fraction](https://www.luogu.com.cn/problem/CF854A)

**题解：** 从$n/2$开始向下遍历，可得出一个数是$i$，另一个数是$n-i$，如果$\gcd(i,n-i)==1$，说明组成的分数是真分数，输出即可。

$Code:$

```cpp
#include<cstdio>
using namespace std;
inline int read(){
   long long s=0;bool w=1;char ch=getchar();
   while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0' && ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n;
int gcd(int a,int b){
    int mod;
    if((mod=a%b)==0)return b;
    return gcd(b,mod);
}
int main(){
    n=read();
    for(int i=n/2;i>=1;i--)
        if(gcd(i,n-i)==1){
            printf("%d %d",i,n-i);
            return 0;
        }
    return 0;
}
```


---

