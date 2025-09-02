# Infinite Sequence

## 题目描述

Vasya likes everything infinite. Now he is studying the properties of a sequence $ s $ , such that its first element is equal to $ a $ ( $ s_{1}=a $ ), and the difference between any two neighbouring elements is equal to $ c $ ( $ s_{i}-s_{i-1}=c $ ). In particular, Vasya wonders if his favourite integer $ b $ appears in this sequence, that is, there exists a positive integer $ i $ , such that $ s_{i}=b $ . Of course, you are the person he asks for a help.

## 说明/提示

In the first sample, the sequence starts from integers $ 1 $ , $ 4 $ , $ 7 $ , so $ 7 $ is its element.

In the second sample, the favorite integer of Vasya is equal to the first element of the sequence.

In the third sample all elements of the sequence are greater than Vasya's favorite integer.

In the fourth sample, the sequence starts from $ 0 $ , $ 50 $ , $ 100 $ , and all the following elements are greater than Vasya's favorite integer.

## 样例 #1

### 输入

```
1 7 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
10 10 0
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1 -4 5
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
0 60 50
```

### 输出

```
NO
```

# 题解

## 作者：TRZ_2007 (赞：3)

[题解 CF675A 【Infinite Sequence】](https://www.luogu.com.cn/problem/CF675A)  
# Description
给出三个整数 $a$ , $b$ ,$c$，求 $b$ 是否在以 $a$ 为第一个数，公差为 $c$ 的等差数列中。  
# Solution  
实际上这道题木不知特别的难，只要你明白**等差数列**是什么。  
等差数列由一组无穷无尽的的数字组成，拥有首项和公差，比如一个首项为 22 ，公差为 2 的等差数列长这个样子： 
$$22,24,26,28,30,\dots$$  
用集合来表示就是这样的：  
$$A={22+2k,k \in Z^+}$$  
（大括号被Latex吃掉了）  
所以说等差数列的项都是 $a+dk$，其中 $a$ 时是首项，$d$ 是公差，$k$ 是大于零的整数。  
对于这道题目，我们来分类讨论：  
- 1：当 $c > 0$ 时  
如果数字 $b$ 在以 $a$ 为第一个数，公差为 $c$ 的等差数列中，那么有 $a+ck=b$，解得 $k=\frac{b-a}{c}$，其中 $k\in Z^+$。  
解个方程判断一下就可以了。  
- 2：当 $c = 0$时  
如果数字 $b$ 在以 $a$ 为第一个数，公差为 $c$ 的等差数列中，那么有 $a = b$。  
判断一下就好了。  
- 3：当 $c < 0$时  
把第一种情况反过来做就好了。  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int a,b,c;
int pos;

int main() {
	scanf("%d %d %d",&a,&b,&c);
	if(c == 0) { // 公差为0
		if(a == b) puts("YES");
		else puts("NO");
	}else {
		if(c > 0) {  //公差大于0
			if(b < a) puts("NO");  //因为k>0，所以如果b小于a，则不可能达到b
			else {
				if((b - a) % c == 0) puts("YES");  //通过我们之前的出来的
				else puts("NO");
			}
		}else { //就是把分类讨论1当中全部反过来
			if(b > a) puts("NO");
			else {
				c = abs(c);
				if((a - b) % c == 0) puts("YES");
				else puts("NO");
			}
		}
	}
	return 0;
}
```

---

## 作者：Laser_Crystal (赞：2)

### QwQ,祖国70华诞发题解~

这道题其实是纯模拟，只不过坑多了一点（~~本宝宝才不告诉你我wa了n次~~）

规律：如果a、b的差可以被c整除，辣么输出YES，否则输出NO（注：有坑！）

边贴代码边讲：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
  int a,b,c;
  cin>>a>>b>>c;//输入
  if(c==0)//如果公差是零，辣么……
  {
    if(a==b) cout<<"YES";//相等就是数列
    else cout<<"NO";//不相等就不是
  }
  else//如果公差84零，辣么……
  {
    if(c>0)//如果公差大于零……
    {
      if(a<=b&&(b-a)%c==0) cout<<"YES";//判断：a小于b且它们的差能被c整除
      else cout<<"NO";
    }
    else//如果公差小于零……
    {
      if(a>=b&&(a-b)%c==0) cout<<"YES";//判断：a大于b且它们的差能被c整除
      else cout<<"NO";
    }
  }
  return 0;
}
```
QwQ，大家886

---

## 作者：Forever1507 (赞：1)

# [传送门](https://www.luogu.com.cn/problem/CF675A)

关于等差数列不必多说，直接模拟即可。

但是有坑：
###  -$10^9$ <= $ a , b , c $ <=$10^9$ 

也就是说要考虑公差(即 $c$ )的正负

辣么就直接上代码吧

```cpp
#include<bits/stdc++.h>
#define ok cout<<"YES";//纯粹为了偷懒QAQ
#define no cout<<"NO";
using namespace std;
int a,b,c;
int main(){
	cin>>a>>b>>c;
	if(c<0)/*公差为负数*/if(a>=b&&abs(b-a)%c==0)ok else no
	else if(c>0)/*公差为正数*/if(a<=b&&abs(b-a)%c==0)ok else no
	else if(c==0){//坑点!!!谁告诉你公差不能为零了???
		if(a==b)ok
		else no
	}
	return 0;
}
```


---

## 作者：bigju (赞：0)

#### 题目大意

现在有一个以 $a$ 打头，公差为 $c$ 的等差数列，问 $b$ 是否在数列中。

显然这是一个简单的题目。很容易想到，如果 $b-a$ 的差模 $c$ 等于 $0$ 的话，那么 $b$ 就在等差数列中。

方法是正确的，但是有很多需要特判的地方：
1. 特殊情况。当 $b<a$ 的时候，显然 $b$ 不在数列中。
2. 当 $c$ 等于 $0$ 时，比如样例 $2$ 所示的情况。此时的等差数列完全由同一个数—— $a$ 组成，也就说我们只需要判断 $a$ 和 $b$ 是否相等即可。
3. 当 $c$ 小于零时。比如$5$ $4$ $3$ $2$ $1$ 这样的数列。那么我们这时 $a$ 和 $b$ 的大小关系就改变了，我们只需要在判断的时候把 $b-a$ 改成 $a-b$ 就行了。同样的，当 $b>a$ 的时候，$b$ 不在数列中。

代码：
```cpp
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
int a,b,c;
int main()
{
    cin>>a>>b>>c;
    if(c==0) 
    {
    	cout<<(a==b?"YES":"NO");
    	return 0;
	}
	if(c>0)
    {
    	if(a<=b&&(b-a)%c==0) cout<<"YES";
    	else cout<<"NO";
    	return 0;
	}
	if(c<0)
	{
		if(a>=b&&(a-b)%c==0) cout<<"YES";
		else cout<<"NO";
		return 0;
	}
}

```


---

## 作者：Arghariza (赞：0)

假设以 $a$ 开头，以 $c$ 为公差的等差数列为 $s_i = a + (i - 1)\, \cdot \, c$ 

显然 $c = 0$ 时满足 $s_i = a$ ，所以说 $a,\,b$ 必须相等才符合条件。

如果 $c > 0$（即 $s_{i+1} > s_i$ ），那么如果 $b<a$ 则明显不符合题意，如果 $b≥a$ 的话只要判断是否满足 $a\equiv b\pmod{c}$ 即可。

如果 $c < 0$（即 $s_{i+1} < s_i$ ），那么如果 $b>a$ 则同样明显不符合题意，如果 $b≤a$ 的话同样只要判断是否满足 $a\equiv b\pmod{c}$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a, b, c;

signed main() {
	cin >> a >> b >> c;
	if (c == 0) {
		if (a == b) cout << "YES";
		else cout << "NO";
	} else if (c > 0) {
		if (b >= a) {
			if ((b - a) % c == 0) cout << "YES";
			else cout << "NO";
		} else cout << "NO";
	} else {
		if (b <= a) {
			if ((a - b) % c == 0) cout << "YES";
			else cout << "NO";
		} else cout << "NO";
	}
	return 0;
}
```

---

## 作者：sinsop90 (赞：0)

这道题是一道需要分类讨论的数学题

我们考虑一下情况:

1.如果 $a = b$ 直接输出 $YES$ 即可

2.建立在$1$不成立的情况下,如果 $c=0$ 则输出 $NO$ 即可

3.建立在前两条的情况下,如果 $a < b$

若 $c < 0$ 直接输出 $NO$ 即可

若 $c > 0$ 判断余数即可

如果 $a > b$

若 $c > 0$ 直接输出 $NO$ 即可

若 $c < 0$ 判断余数即可

因此便有了如下代码:

```
#include<bits/stdc++.h>
using namespace std;
int main() {
	long long a, b, c;
	scanf("%lld%lld%lld", &a, &b, &c);
	if(b == a) {//第一种情况
		cout << "YES" << endl;
		return 0;
	}
	if(c==0) {//第二种情况
		cout << "NO" << endl;
		return 0;
	}
	if(a > b) {//第三种情况
		if(c > 0) {
			cout << "NO" << endl;
			return 0;
		}
		else {
			if((a-b) % abs(c) == 0) {
				cout << "YES" << endl;
				return 0;
			}	
			else {
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	else {
		if(c < 0) {
			cout << "NO" << endl;
			return 0;
		}
		else {
			if((b-a) % c == 0) {
				cout << "YES" << endl;
				return 0;
			}
			else {
				cout << "NO" << endl;
				return 0;
			}
		}
	}
}
```


---

## 作者：Insouciant21 (赞：0)

[关于等差数列](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97)

#### 分析

给出 $b$ ，求其是否在首项为 $a$ ，公差为 $c$ 的等差数列中。

对于首项为 $a$ 公差为 $c$ 的等差数列，第 $n$ 项为 $a+nc$ 。

设 $b=a+nc$ 

得到 $b-a=nc\ \{n\in\mathbb{N}\}$

因为 $n\in\mathbb{N}$ 所以必有 $(b-a)\bmod c=0\ (c\neq0)$ 。

这里注意 $c\neq 0$ ，当公差等于 $0$ 时，每一项都为 $a$，即只需判断 $a$ 与 $b$ 是否相等。

因为限定了首项，所以数列只能向一个方向无限延伸，所以

- 当公差 $c<0$ 时，数列向 $-\infty$ 延伸，此时只能有 $b\leq a$
- 当公差 $c>0$ 时，数列向 $\infty$ 延伸，此时只能有 $b\geq a$

#### 代码
```
#include <bits/stdc++.h>

using namespace std;

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if (c == 0) {
        if (a == b)
            puts("YES");
        else
            puts("NO");
    }
    else {
        int s = b - a;
        if (s % c == 0) {
            if (c > 0 && a <= b)
                puts("YES");
            else if (c < 0 && a >= b)
                puts("YES");
            else
                puts("NO");
        }
        else
            puts("NO");
    }
    return 0;
}

```



---

## 作者：Eason_AC (赞：0)

## Content
给定三个整数 $a,b,c$，问你 $b$ 是否在以 $a$ 为首项，公差为 $c$ 的等差数列中。

**数据范围：$-10^9\leqslant a,b,c\leqslant 10^9$。**
## Solution
给出两个定理：设 $x_n$ 在以 $x_1$ 为首项，公差为 $d(d\neq 0)$ 的等差数列中，那么就有：

$1.$ $d\mid (x_n-x_1)$。  
$2.$ $\dfrac{x_n-x_1}{d}\geqslant 0$。 

证明 $1$：众所周知，一个首项为 $x_1$，公差为 $d$ 的等差数列的第 $n$ 项 $x_n$ 为 $x_1+(n-1)d$，那么必然就有 $\dfrac{x_n-x_1}{d}=n-1$ 为整数，所以就有 $d\mid (x_n-x_1)$。

证明 $2$：由证明 $1$ 我们可以知道，$\dfrac{x_n-x_1}{d}=n-1$。又因为 $n\geqslant 1$，所以 $n-1\geqslant 0$，通过等量代换就有 $\dfrac{x_n-x_1}{d}\geqslant 0$。

证毕。

但问题是，数据范围没有说公差 $c$ 为 $0$！怎么办？

其实很简单，当公差 $c$ 为 $0$ 的时候，那么很显然，等差数列里面的每一项都相等，所以我们只需要判断是否有 $a=b$ 即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int a, b, c;

int main() {
	scanf("%d%d%d", &a, &b, &c);
	if(!c) {
		if(a == b) printf("YES");
		else printf("NO");
	}
	else if(((b - a) / c >= 0 && (b - a) / c * c == b - a)) printf("YES");//这里判断是否是整数
	else printf("NO");
	return 0;
}

```

---

## 作者：UperFicial (赞：0)

# 三年级小朋友都要学的数学题

看到楼下只讲了公式并没有将说明方法，这里给予补充。另外将几个~~差点坑死我的~~坑点。

**题意**

给定三个正整数 $a,b,c$，问 $b$ 是否为以 $a$ 为第一个数并且公差为 $c$ 的等差数列中。

### 暴力做法

其实就是模拟，判断一下 $c$ 的正负和 $a,b$ 的大小，把等差数列挨个模拟一遍就好了。

时间复杂度：$\mathcal{O}(TLE)$。

### 数学做法

假设这个等差数列为 $\{a\},a_1=a$。

先普及一下等差数列的概念：对于数列中的任意一个数 $a_i$，都有 $a_i=a_{i-1}+c$。（$c$ 为公差）

再来看一下什么时候 $b$ 会在 $a$ 数列当中：因为这是一个等差数列，所以在这个数列中的任何一个数都会被一个整数 $x$ 表示出来：$a_1+cx$。 

易得方程：

$$a_1+cx=b$$

移项，把未知数 $x$ 移到方程左边：

$$x=\dfrac{b-a_1}{c}$$

只要判断 $b-a_1$ 是否能整除 $c$ 即可，但这样的话就会 $WA$ 掉，几个坑点这里总结一下：

- $0$ 不可以作除数，所以对于 $c=0$ 的情况要特判 $a,b$ 是否相等，因为在一个公差为 $0$ 的等差数列里只有一个数。

- $a,b,c$ 可能为**负数**，先判断一下 $c$ 是正是负，如果是正，那么必须满足两个条件：

	- $a_1\le b$；
    
    - $(b-a_1)\bmod c=0$；
    
  第一个条件是因为 $c$ 既然是正数，那么整个等差数列肯定按**严格递增**的顺序排列；第二个条件便是刚刚推出的公式。
  
   如果 $c$ 是负数，那么同理必须满足以下两个条件：
   
   - $b\le a_1$；
   
   - $(a_1-b)\bmod c=0$;
   
   与 $c$ 为正数的情况同理，这里就不做更多解释了。
   
- 有些同学可能提前判断一下 $a,b$ 大小，如果 $b<a$ 那么就输出 `NO`。这是一个错误的判断，因为 $c$ 还有可能为负数。

时间复杂度：$\mathcal{O}(1)$。

$AC$ 记录：[$\mathcal{Link}$](https://www.luogu.com.cn/record/37902277)

另外难度建议红，没什么思维难度。

---

## 作者：LucasXu80 (赞：0)

来一篇Python题解~

在代码前，讲一个数学小技巧。

一个等差数列，记为 
$a$(首项), $a+c$, $a+2c...$

注意，这个数列虽然是无限的，但是它其实是单向无限延伸（相当于射线），而不是双向无限延伸（相当与直线）。

好，我们来观察这个数列中任意两项的差：

$(a+c)-a=c$

$(a+2c)-a=2c$

$(a+c)-(a+c)=0$ （可看作$0c$）

你会发现，每一个差（**后面一项-前面一项**）都是公差c的**非负整数**倍，无论这个c是否为非负整数。这一点**非常重要**，在下面的解题中很有用。

为了帮助大家理解，咱们就拿几个样例来举个~~栗子~~例子：

#### 样例1：1 7 3

两项差$=7-1=6=2×3$，$2$是**非负整数**，所以YES；

样例2有点特殊，待会儿再说。

#### 样例3：1 -4 5

两项差$=(-4)-1=-5=(-1)×5$，$-1$**不是非负整数**，所以NO；

#### 样例4：0 60 50

两项差$=60-0=60=1.2×50$，$1.2$不是整数，所以NO。

想到这里我满怀信心地交了一份代码上去，大致思路是这样的：

```cpp
if ((b-a)%c==0&&(b-a)*1.0/c>=0) cout<<"YES";
else cout<<"NO";
```
（没错，我一开始交的是C++）

经过半分钟的焦急等待后，

[快乐WA](https://www.luogu.com.cn/record/33663716)

问题出在哪儿了呢？

这个式子中，$c$是分母。但是题目并没有说$c≠0$啊。。。

#### 比如样例2。

那么我们就要讨论了。如果$c=0$：

如果$a=b$，那么是可以的，否则就不可以。

好了，终于上 [AC](https://www.luogu.com.cn/record/33664189) Python代码了：

```python
import sys #为了后面提前结束程序
a,b,c=map(int, input().split()) #一行内输入三个数
if c==0: #c=0的时候
    if a==b: #a=b的时候可以
        print("YES")
    else: #否则就不可以
        print("NO")
    sys.exit(); #结束程序，这样下面就一定是c≠0的情况了
if (b-a)/c>=0 and (b-a)%c==0: #这个倍数是非负整数
    print("YES") #输出YES
else: #不是非负整数
    print("NO") #输出NO
```
求过求赞！

---

## 作者：AgrumeStly (赞：0)

我用的是：分类讨论+暴力

其中分类讨论中，我用了一种`namespace`名命名空间。如果：

- $c = 0$ ：

    当 $a == b$ 时，输出 $YES$ 否则 $NO$
- $c < 1$  ：

    列举所有的等差数列数字，当列举到 $b$ 时:$YES$, 因为 $c$ 为负数，所以越加数越小，所以当当前列举的数已经 $<$ $b$ 时:$NO$
- $c > 1$  ：

    列举所有的等差数列数字，当列举到 $b$ 时:$YES$, 因为 $c$ 为正数，所以越加数越大，所以当当前列举的数已经 $>$ $b$ 时:$NO$

所以代码自然而然的就写出来啦！~~（我才不告诉你我WA多少次）~~

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring> 
using namespace std;
int a, b, c, flag; 
namespace c0
{
	void sovle()
	{
		if (a == b)//当a = b时，标记
			flag = 1;
		else flag = 0;//否则，标记
	}
}
namespace c1//名命名 ：当c > 1时，进行一波操作
{
	void sovle()
	{
		while (1)
		{
			if (a == b)//当b在这个等差数列里时
			{
				flag = 1;//标记
				return;
			}
			if (a > b)//如果b不存在于这个等差数列
			{
				flag = 0;//如果大于，标记
				return;
			}
			a += c;
		}
	}
}
namespace c_1//名命名 ：当c < 1时，进行另一波操作
{
	void sovle()
	{
		while (1)
		{
			if (a == b)
			{
				flag = 1;
				break;
			}
			if (a < b)//如果小于
			{
				flag = 0;//标记
				break;
			}
			a += c;
		}
	}
}
int main()
{
	cin >> a >> b >> c;//输入
	if (c == 0) c0::sovle();//调用名空间
	if (c > 0) c1::sovle();
	if (c < 0) c_1::sovle();
	if (flag == 1) cout << "YES";//输出
	if (flag == 0) cout << "NO";
	puts("");//换行
	return 0;
}

```


---

## 作者：Lucifer_Bartholomew (赞：0)

# 模拟
数学问题。
如果b是等差数列里的数，那么其满足：
1. b与a的差是c的倍数，即(b-a)|c
2. c是0，则a与b相等

输出YES

否则就不是，输出NO
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	if(!c)//特判差值是0时的情况
	{
		if(a==b)puts("YES");
		else puts("NO");
	}
	else if(a==b||(b-a)%c==0&&(b-a)/c>0)puts("YES");
	else puts("NO");
	return 0;
}
```
~~我是蒟蒻~~

---

