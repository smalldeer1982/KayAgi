# Petya and His Friends

## 题目描述

Little Petya has a birthday soon. Due this wonderful event, Petya's friends decided to give him sweets. The total number of Petya's friends equals to $ n $ .

Let us remind you the definition of the greatest common divisor: $ GCD(a_{1},...,a_{k})=d $ , where $ d $ represents such a maximal positive number that each $ a_{i} $ ( $ 1<=i<=k $ ) is evenly divisible by $ d $ . At that, we assume that all $ a_{i} $ 's are greater than zero.

Knowing that Petya is keen on programming, his friends has agreed beforehand that the $ 1 $ -st friend gives $ a_{1} $ sweets, the $ 2 $ -nd one gives $ a_{2} $ sweets, ..., the $ n $ -th one gives $ a_{n} $ sweets. At the same time, for any $ i $ and $ j $ ( $ 1<=i,j<=n $ ) they want the $ GCD(a_{i},a_{j}) $ not to be equal to $ 1 $ . However, they also want the following condition to be satisfied: $ GCD(a_{1},a_{2},...,a_{n})=1 $ . One more: all the $ a_{i} $ should be distinct.

Help the friends to choose the suitable numbers $ a_{1},...,a_{n} $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
99
55
11115
```

## 样例 #2

### 输入

```
4
```

### 输出

```
385
360
792
8360
```

# 题解

## 作者：封禁用户 (赞：8)

我并没有别人那么巧妙的做法。

先用欧拉筛求出前 $n$ 个素数 $p_i$。

则 $num_x=\tfrac{\prod_{i=1}^np_i}{p_x}$ 即可满足条件。

${\prod_{i=1}^{50}p_i}= 19078266889580195013601891820992757757219839668357012055907516904309700014933909014729740190$。

$len=92$，没有超出限制，加个高精度即可。

参考代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
int p[55],cnt = 0,n;
bitset<300> ip;
inline void oula()
{
	for(int i = 2;cnt < 50;++i)
	{
		if(!ip[i]) p[++cnt] = i;
		for(int j = 1;j <= cnt&&i * p[j] <= 300;++j)
		{
			ip[i * p[j]] = 1;
			if(i % p[j] == 0) break;	
		}	
	}
}
struct Bigint
{
	int len,a[110];
	inline void init()
	{
		len = 1;
		memset(a,0,sizeof(a));
		a[1] = 1;	
	}
	inline Bigint friend operator*(Bigint x,int y)
	{
		x.len += (int)log10(y) + 1;
		for(int i = 1;i <= x.len;++i) x.a[i] *= y;
		for(int i = 1;i <= x.len;++i) 
		{
			x.a[i+1] += x.a[i]/10;
			x.a[i] %= 10;
		}
		while(!x.a[x.len]) --x.len;
		return x;
	}
	inline void print()
	{
		for(int i = len;i;--i) 
			putchar(a[i]+48);
		putchar(' ');
	}
}Num;
int main()
{
	oula();
    scanf("%d",&n);
    if(n <= 2) 
    {
    	printf("-1");
    	return 0;
 	}
    for(int i = 1;i <= n;++i)
    {
    	Num.init();
    	for(int j = 1;j <= n;++j)
    		if(j != i)
    			Num = Num * p[j];
    	Num.print();
	}
    return 0;
}
```




---

## 作者：Fan_Tuan (赞：7)

# 题解 CF66D 
## 题意
给定n，要求给出n个数，使任意两数不互质，但所有数的最大公约数为1
## 思路
所有数的最大公约数为1，只需三个数最大公约数为1，假设a,b,c为素数，设第一个数为ab，第二个数为ac，第三个数为bc，则这三个数最大公约数已经为1，那么剩下的数只要满足与他们不互质即可，不妨令以后的数为 bc*i(i>1), 则问题已解。

## 代码

```
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#include<queue>  
#include<string>
using namespace std;   
 
int main()  
{  
    int n;  
    scanf("%d", &n);  
    if (n <= 2)  
        printf("%d\n", -1);  
    else  
    {  
        printf("%d\n", 6);  
        printf("%d\n", 15);
        for (int i = 1; i <= n-2; i++)  
            printf("%d\n", 10*i);
    }  
    return 0;  
}
```


---

## 作者：Back_Stuff (赞：3)

很水的一道题，建议降橙。


## 题目大意

找出 $n$ 个数，使得它们每两个数的最大公约数不等于 $1$ 而且所有数的最大公约数等于 $1$。

## 思路

这道题题目短，代码也短，很适合本蒟蒻写。只需要找到正确的规律就可以了。

如果 $n=2$ 的话，第一个数与第二个数既要求互质又要求最大公约数不等于 $1$，矛盾，无解。其余的情况都是有解的。

本蒟蒻将前两个数设为 $6$ 和 $10$，这个地方选其他的也可以。

$6=2\times3$

$10=2\times5$

所以后面的数必须有 $3$ 和 $5$ 这两个因数，但是不能有 $2$ 这个因数，因为 $6$ 和 $10$ 都有 $2$ 这个因数，这样就不满足第 $2$ 个条件了。

根据以上的思路，可以写出代码。

## 代码

代码很丑，不喜勿喷。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k=-15;
int main(){
    cin>>n;
    if(n<=2){
        cout<<-1;
        return 0;
    }
    cout<<"6\n10";
    for(int i=3;i<=n;i++){
        k+=30;
        cout<<"\n"<<k;
    }
    return 0;
}
```

## The End

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF66D)

## 思路

构建一个序列，满足 $1\leq i,j\leq n$ 且 $\gcd(a_i,a_j)\neq 1$ 和 $\gcd(a_1,a_2,a_3,\dots,a_n)=1$。这个意思就是在 $a_1$ 到 $a_n$ 中的所有数互质，且两两不互质。

我们可以想到，当 $n\leq 2$ 时，无法构造。如果 $n\geq 2$，那么可以先输出 $6$ 和 $15$，之后输出 $1$ 到 $(n-2)$ 之间所有数乘以 $10$ 的结果。

- 最后的构造由来：$6$ 的因数有 $1,2,3,6$；$15$ 的因数有 $1,3,5,15$；$10$ 的因数中没有 $3$，不互质。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    if(n<=2){
        cout<<"-1\n";
        return 0;
    }
    cout<<"6\n15\n";
    for(int i=1;i<=n-2;++i)cout<<i*10<<endl;
    return 0;
}
~~~

---

## 作者：youdu666 (赞：0)

### 思路：暴力
有一个简单的想法，若 $a,b,c$ 三个数字的最大公因数为 $1$，则无论后面接上什么数字，整个序列的最大公因数都是 $1$。

因此，可以简单地输出三个最大公因数为 $1$ 的序列，随后输出 $n-3$ 个这三个数字的最小公倍数的倍数即可，根本不用高精度。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
signed main()
{
    scanf("%d",&n);
    if(n==2)
    {
        printf("-1\n");
        return 0;
    }
    printf("6\n10\n15\n");
    //此处使用了6,10,15三个数字，易证其gcd为1
    int ans=0;
    for(int i=4;i<=n;i++)
    {
        ans+=30;
        //最小公倍数为30
        printf("%d\n",ans);
    }
}
```


---

## 作者：_Weslie_ (赞：0)

# [CF66D题目传送门](https://www.luogu.com.cn/problem/CF66D)

## Part.1 思路

首先，一定要输出 $\ n\ $ 个数。

不超过 $\ 100\ $ 位，是不是高精度？

众所周知，$\texttt{long long}\ $ 的容纳范围为 $\ -9223372036854775808\ $ 至 $\ 9223372036854775807$，$100\ $ 位是完全不够的。

众所周知，高精度是万恶之源，我这个懒蛋是肯定不会打的（就是忘了板子了），所以我们必须把范围限制在 $\ 9223372036854775807\ $ 以下。

众所周知，这种题先找特殊条件，所以……我们先来扒一下题目。

如果 $\ n=1$，那么只有一个数，无法求 $\gcd$。

如果 $\ n=2$，题目要求 $\ \forall i,j$，$\gcd(a_i,a_j)\ $ 不为 $\ 1$，且 $\ \gcd(a_1,a_2,a_3,......,a_n)=1$，一定无法满足。

如果 $\ n=3$，有解 $\ (99,55,11115)$。

如果 $\ n=4$，有解 $\ (385,360,392,8360)$。

如果 $\ n=5$，解更多，不列了。

所以，这段代码我们可以确定：

```
if(n<=2)cout<<-1;
```

接下来，讨论 $\ n\geq3\ $ 的情况。

首先，我们要保证前两个数的最大公约数不为 $\ 1$。

这样的数对有很多，比如：

$(2,4),(3,9),(6,15),(14,35),......$

还要保证第三个数和第一、二个数的最大公约数都不为 $\ 1$。

这样的数对依然有很多，比如：

$(2,4,6),(3,9,12),(6,10,15),(14,10,35),......$

继续淘汰，要求三个数的最大公约数为 $\ 1$：

$\gcd(6,10,15)=1,\gcd(14,10,35)=1,......$

那如果再加上一个数呢？

$\gcd(6,10,15,20)=1,\gcd(14,10,35,20)=1,......$

继续……

$\gcd(6,10,15,20,30)=1,\gcd(14,10,35,20,30)=1,......$

$\gcd(6,10,15,20,30,40)=1,\gcd(14,10,35,20,30,40)=1,......$

也就是前两个数是 $\ (6,15),(14,35),(26,65),(34,85)\ $ 且第 $\ m(m\geq3)\ $ 个数的值为 $\ (m-2)×10\ $ 就可以满足要求。

那何不打一下呢？

因为 $\ n\leq50$，最大值只会是 $\ 480\ $，别说高精度了，$\texttt{long long}\ $ 都用不上。

所以直接输出即可。

## AC Code1:
```
#include<iostream>
using namespace std;
int n;
int main() {
	cin>>n;
	if(n<=2)cout<<-1;
	else {
		cout<<14<<endl<<35<<endl;
		for(int i=1; i<n-1; i++)cout<<i*10<<endl;
	}
	return 0;
}
```
## Part.2

你以为就这么简单？

上面代码的时间复杂度为 $\ \operatorname{O}(n)$，众所周知这个时间复杂度可以在 $\ 210\operatorname{ms}\ $ 内的时间解决。

然而，我们这道题完全可以求最优解……

我这次盯上了数据范围……$2\leq n\leq50$，打表好题……

于是通过上面的代码，我打出了一个表：

## AC Code 2:
```
#include<iostream>
using namespace std;
int n;
int main(){
	cin>>n;
	switch(n){
		case 1:cout<<"-1";break;
		case 2:cout<<"-1";break;
		case 3:cout<<"14\n35\n10";break;
		case 4:cout<<"14\n35\n10\n20";break;
		case 5:cout<<"14\n35\n10\n20\n30";break;
		case 6:cout<<"14\n35\n10\n20\n30\n40";break;
		case 7:cout<<"14\n35\n10\n20\n30\n40\n50";break;
		case 8:cout<<"14\n35\n10\n20\n30\n40\n50\n60";break;
		case 9:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70";break;
		case 10:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80";break;
		case 11:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90";break;
		case 12:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100";break;
		case 13:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110";break;
		case 14:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120";break;
		case 15:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130";break;
		case 16:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140";break;
		case 17:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150";break;
		case 18:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160";break;
		case 19:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170";break;
		case 20:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180";break;
		case 21:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190";break;
		case 22:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200";break;
		case 23:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210";break;
		case 24:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220";break;
		case 25:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230";break;
		case 26:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240";break;
		case 27:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250";break;
		case 28:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260";break;
		case 29:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270";break;
		case 30:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280";break;
		case 31:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290";break;
		case 32:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300";break;
		case 33:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310";break;
		case 34:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320";break;
		case 35:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330";break;
		case 36:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340";break;
		case 37:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350";break;
		case 38:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360";break;
		case 39:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370";break;
		case 40:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380";break;
		case 41:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390";break;
		case 42:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400";break;
		case 43:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400\n410";break;
		case 44:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400\n410\n420";break;
		case 45:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400\n410\n420\n430";break;
		case 46:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400\n410\n420\n430\n440";break;
		case 47:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400\n410\n420\n430\n440\n450";break;
		case 48:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400\n410\n420\n430\n440\n450\n460";break;
		case 49:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400\n410\n420\n430\n440\n450\n460\n470";break;
		case 50:cout<<"14\n35\n10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n110\n120\n130\n140\n150\n160\n170\n180\n190\n200\n210\n220\n230\n240\n250\n260\n270\n280\n290\n300\n310\n320\n330\n340\n350\n360\n370\n380\n390\n400\n410\n420\n430\n440\n450\n460\n470\n480";break;
	}
} 
```
时间复杂度 $\ \operatorname{O}(1)$。

可为什么实际跑起来却比 $\ \operatorname{O}(n)\ $ 慢呢？好玄学。

感谢各位在评论区 $\ hack\ $ 的大佬们~

---

## 作者：Binary_Search_Tree (赞：0)

[题目传送门](https://www.luogu.org/problem/CF66D)

题意:构造$n$个数，使任意两个数的$gcd$不为$1$，但$n$个数的$gcd$为$1$

设$a_i=p_1^{s_1}p_2^{s_2}p_3^{s_3}....$

因为$gcd(a_1,a_2,a_3,...,a_n)=\prod\limits_{p\in prime}p^{min(s_1,s_2,s_3,...,s_n)}$

所以只要让每个$min(s_1,s_2,s_3,...,s_n)=0$即可。

对于每个质数$p_i$，可以让$a_1$到$a_n$中除了$a_i$全部乘上$p_i$

这样可以保证$min(s_1,s_2,s_3,...,s_n)=0$

则$gcd(a_i,a_j)=\prod\limits_{1<=k<=n,k\neq i,k\neq j}p_k$

当$n>2$时显然$gcd(a_i,a_j)\neq 1$

当$n=2$时，因为$gcd(a_1,a_2)=1$且$gcd(a_1,a_2)\neq 2$不成立，所以无解

当然要写一个高精度（否则会爆long long)

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define M 5005
using namespace std;
int S[1005];
int n,P[100]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229};//前50个质数
int read(){//快读（其实并不需要)
	char c=getchar();int ans=0;
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9') ans=ans*10+c-'0',c=getchar();
	return ans;
}
int main(){
	n=read();
	if (n==2){printf("-1");return 0;}//特判
	for (register int i=1;i<=n;i++){
		S[0]=S[1]=1;
		for (register int j=1;j<=n;j++){
			if (i==j) continue;int s=0;
			for (register int k=1;k<=S[0];k++)
				S[k]=S[k]*P[j]+s,s=S[k]/10,S[k]%=10;
			while (s) S[++S[0]]=s%10,s/=10;//高精乘
		}
		for (register int i=S[0];i>=1;i--) putchar(S[i]^48);//输出
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：梧桐灯 (赞：0)

~~据说ＣＳＰＳ前发题解可以RP++~~

这题让我们构造一个数列使得两两不互质，整个数列gcd为1.

我的构造方法：

$6,6^2,6^3 ……, 3*5, 2*5$

然后因为$n<=50,6^{48}$不超过$100$位但要写高精度

最后特判一下$n=2$时输出$0$即可

代码:
```
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct stu {
	int x[41];
	stu () {memset (x, 0, sizeof (x)); return ;}
	inline stu operator * (const int p) const {
		stu r;
		for (register int i = 1; i < 40; ++i) r.x[i] = x[i] * p;
		for (register int i = 1; i < 40; ++i) {
			r.x[i + 1] += r.x[i] / 10;
			r.x[i] %= 10;
		}
		return r;
	}
	inline void out () {
		int i = 40;
		while (i && !x[i]) --i;
		while (i) putchar (x[i--] ^ 48);
		return ;
	}
}k;

int main () {
	int n; scanf ("%d", &n);
	if (n == 2) {
		puts ("-1");
		return 0;
	}
	k.x[1] = 1;
	for (int i = 1; i < n - 1; ++i) {
		k = k * 6;
		k.out (), putchar ('\n');
	}
	puts ("10");
	puts ("15");
	return 0;
}
```


---

