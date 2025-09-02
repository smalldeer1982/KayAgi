# Unnatural Conditions

## 题目描述

Let $ s(x) $ be sum of digits in decimal representation of positive integer $ x $ . Given two integers $ n $ and $ m $ , find some positive integers $ a $ and $ b $ such that

- $ s(a) \ge n $ ,
- $ s(b) \ge n $ ,
- $ s(a + b) \le m $ .

## 说明/提示

In the first sample, we have $ n = 6 $ and $ m = 5 $ . One valid solution is $ a = 6 $ , $ b = 7 $ . Indeed, we have $ s(a) = 6 \ge n $ and $ s(b) = 7 \ge n $ , and also $ s(a + b) = s(13) = 4 \le m $ .

## 样例 #1

### 输入

```
6 5
```

### 输出

```
6 
7
```

## 样例 #2

### 输入

```
8 16
```

### 输出

```
35 
53
```

# 题解

## 作者：Anguei (赞：10)

先放最短 AC 代码：

```python
print '4' * 300
print '5' * 299 + '6'
```

下面来证明一下正确性。

1. 题目保证了 $n, m \leq 1200$，所以这么输出，可以确保 $300 \times 4 = 1200, 299 \times 5 + 6 = 1505$， 符合了题目中 $1200 \leq s(a), 1200 \leq s(b)$ 的条件。
2. 相同长度的一串 $4$ 和一串 $5$ 相加，得到一串 $9$，再加上 $1$，一定可以得到 $10$ 的幂。一定满足题目中 $s(a+b) \leq m$ 的条件。
3. 输出长度没有超出限制。

~~所以窝为什么比赛的时候写了十多行构造呢？~~

---

## 作者：—维尼— (赞：3)



## 我们先来理解一下题意

我们要找出数 $a$ 和数 $b$
 使 $a$ 和 $b$ 各个数位的和 $=>$ $n$ , $a+b$ $<=$ $m$ 
本题可以花一点时间去构造，但是有更好的作法：

## 解题思路
我们先看一眼范围


**~~n和m都小于等于1129~~** 

但是哈，我们发现输出并没有限定位数（只给了$a，b$范围）
所以我们可以尝试找出一个答案，让他满足所有问题，所以直接把$n$当作$1129$，$m$当作$1$

  - 我们发现第一句很容易就满足了：（使 $a$ 和 $b$ 各个数位的和 $\le$ $n$）我们只需把这个数给到很大很大，超过n就行了
 - 再看第二句，要使两数和的位数和$\le1$，虽然$a$和$b$都很大，但只要它们的和变成10000000……这样的形式，永远也不会超过1了

得到这一结论，我们就可以直接输出
可以用$4444444444……$ 和 $55555555……6$

或$4444444444……5$ 和 $555555555……$
不用输出太多，用比较小的$444444……$算

$4*300$已经大于$1129$了，所以输出$300$位是足够的

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	for(int i=1;i<=300;i++){
		cout<<"4";
	}
	cout<<endl;
	for(int i=1;i<=299;i++){
		cout<<"5";
	}
	cout<<6<<endl;
	return 0;
}
```



---

## 作者：small_moon (赞：2)

## 题意
给定 $n,m$，构造 $a , b$ 使得 $a$ 和 $b$ 的数位和分别 $\ge n $ 且 $a+b$ 数位和 $\le m$。

## 思路
怎么使 $a+b$ 两数的数位和相较于 $a,b$ 的数位和减小呢？进位！

当 $a,b$ 数位相同时，若同一数位相加等于 $9$，且最后一位和为 $10$，进位后数位和就只剩下 $1$ 了。

那么怎么使  $a,b$ 同一数位和为 $9$ 呢？可以令 $a,b$ 的最后一位值为 $5$，其他位 $4,5$ 交叉排列即可。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int na,nb,n,m;
deque <int> a,b; //蒟蒻丑陋的双端队列
void pa() //在a前面加数
{
	int tmp=0;
	if(a.front()==4) tmp=5;
	else tmp=4;
	a.push_front(tmp); na+=tmp;
}
void pb() //在b前面加数
{
	int tmp=0;
	if(b.front()==5) tmp=4;
	else tmp=5;
	b.push_front(tmp); nb+=tmp;
}
int main()
{
	a.push_front(5);
	b.push_front(5);
	a.push_front(4);
	b.push_front(5);
	cin>>n>>m;
	na=9; nb=9; //na表示a的数位和，nb表示b的数位和 
	while(na<n) pa();
	while(nb<n) pb();
	while(a.size()<b.size()) pa();
	while(b.size()<a.size()) pb();
	while(!a.empty())
	{
		printf("%d",a.front());
		a.pop_front();
	}
	cout<<endl;
	while(!b.empty())
	{
		printf("%d",b.front());
		b.pop_front();
	}
	return 0;
}
```

---

## 作者：叶枫 (赞：2)

### 题意

是规定了一种函数$s(x)$的值为$x$的每个位上的数字之和，比如$x=123$，$s(x)=1+2+3=6$.

输入两个数$n$和$m$，然后让你找两个数字$a$和$b$，有$s(a)>=n$,$s(b)>=n$, $s(a+b)<=m$，输出**任意**的符合条件的$a$和$b$的值。

### 题解
  看到题目中有一句话，***长度***  不能超过2230，所以这题暴力肯定是过不了的。
  
但是我们可以想一下，对于大于$0$的数来说，$s(x)$的最小值为1，所以我们就尽可能的让$s(a+b)$等于1，那么我们可以让$a$等于$n$个1，那么$b$就是$n-1$个8加一个9，这样$s(a+b)$算出来就是1了(当然让$a$等于$n$个$5$也行)。

$P.S$虽然答案跟样例不同，但肯定能过，~~应该开了SPJ~~

### $Code$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<queue>
#define re register
#define ll long long
#define maxn 300500
#define inf 2147483647
#define mod 998244353
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
 
signed main(){
	int n=read(),m=read();
	for(int i=0;i<n;i++) cout<<'1';
	cout<<endl;
	for(int i=1;i<n;i++) cout<<'8';
	puts("9");  
	return 0;
}
```

---

## 作者：zhangqiuyanAFOon2024 (赞：1)

一道绿题！

没想到是简单的构造。

我们可以构造两个数，让它们满足题目条件。

我们想道了构造两个很大很大的数，设为 $a,b$。

令 $s ( a ) > 1129$，$s ( b ) > 1129$，$s  (a  + b) = 1$。

我们想到了 $3333\cdots 33$，$6666\cdots 67$，加起来是 $10000\cdots 00$，这样 $s(a+b)=1$。

$3\times 500>1129$，所以我们只用构造 $500$ 位就够了！

完整代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
        int a ,b;
        cin >> a >> b;
        for(int  i= 1; i <= 500; i++) cout << 3;
        cout << endl;
        for(int i = 1; i <= 499; i++) cout << 6;
        cout << 7 << endl;//构造两个数。
        return 0;//好习惯。
}

```

### 不要直接抄袭，共创文明洛谷。

---

## 作者：Sun_wtup (赞：1)

# Unnatural Conditions 题解
[题目传送](https://www.luogu.com.cn/problem/CF1028B)
## 题意
给出 $n$ 和 $m$，求出两个数，使得每个数的各个数位上的数字之和大于等于 $n$，两个数相加后得到的数的各个数位上的数字之和小于等于 $m$。
## 分析与思路
显然这是一道构造，定义 $s(x)$ 为 $x$ 各个数位上的数字之和。我们先从可以从 $s(a + b)\leq m$ 入手，我们可以直接取这个区间的一个极值，即当 $s(a + b)= m$ 时。然后我们又可以考虑 $a + b$ 这个数只由 $1$ 和 $0$ 构成，且 $1$ 全都在高位 $0$ 在低位，这样 $1$ 的数量就是 $m$。这样就能构成一个数即 $a + b$，我们暂时先让他由 $m$ 个 $1$ 和一个 $0$ 组成。再假设 $a$ 和 $b$ 相等。我们将构造出这个数除以 $2$ 就是 $a$ 和 $b$ 了。如果现在的 $a$ 和 $b$ 大于等于 $n$，就可以直接输出了，如果不满足，就在刚构造出的数的基础上加 $0$，再处理，看如果各个数位上的数字之和大于等于 $n$ 了就可以了，输出即可。
## 实现
我们可以发现在构造出一个由 $m$ 个 $1$ 和一个 $0$ 组成的数后，除以 $2$ 就会得到由 $m$ 个 $5$ 组成的数，如果在这时刚得到的数（就是 $a$ 和 $b$）就大于等于 $n$，就把 $a$ 和 $b$ 输出就行了。如果不行就是另一种情况，在后面加 $0$，然后直接除以 $2$ 你就会发现无论有多少个 $0$，结果都和有一个的时候一样。所以我们要处理，使得 $a$ 和 $b$ 的后半部分不能全为 $0$，又要为了使两个数各个数位上的数字之和相近，那我们就先让他们的最后一位都是 $5$，这样相加这一位才是 $0$。这样就定好了最后一位和前 $m-1$ 位（全是 $5$，减 $1$ 因为在加的时候要进位，进位就进出来了）中间的部分一个数是 $454545\dots$ 一个是 $545454\dots$ 然后记录各个数位上的数字之和，只要大于等于 $n$ 了就可以了。
## Code
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<'='<<x<<std::endl
#define int long long
int cntn;
int cnt=0;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m; 
    cin >> n >> m;
    cntn+=(m*5);
    if(cntn>=n){
    	for(int i=1;i<=m;i++){
    		cout<<5;
		}
		cout<<endl;
		for(int i=1;i<=m;i++){
			cout<<5;
		}
	}
	else{
		cntn=0;
		for(int i=1;i<m;i++){
			cout<<5;
			cntn+=5;
		}
		for(int i=1;;i++){
			if(cntn>=n){
				break;
			}
			cnt++;
			if(i%2==1){
			    cout<<4;
			    cntn+=4;
			}
			else {
				cout<<5;
				cntn+=5;
			}
		}
		cout<<5;
		cout<<endl;
		for(int i=1;i<m;i++){
			cout<<5;
		}
		for(int i=1;i<=cnt;i++){
			if(i%2==0){
			    cout<<4;
			}
			else {
				cout<<5;
			}
		}
		cout<<5;
	}
    return 0;
}

```
本蒟蒻水平有限，如有不周之处，希望能原谅。

---

## 作者：lin134 (赞：1)

题目要求我们要找出数 $a$ 和数 $b$ 使 $a$ 和 $b$ 各个数位的和 $\ge n$，$a+b \le m$。

这其实是一道构造解的题，但最省力的方法其实是**构造一个可以适应所有输入的解**。

先看一眼范围，题目保证 $n$ 和 $m$ 小于等于 $1129$，并且 $n$ 和 $m$ 大于等于 11。

所以只要 $a$ 各个数位上的数字之和加上 $b$ 的各个数位上的数字之和大于等于 $1129$ 并且 $a + b$ 各个数位上的数字之和小于等于 $1$,那么这个解就满足题目所说范围内的所有 $n$ 和 $m$。

显而易见，只要满足

1. $a+b=10 \cdots $。

2. $a$ 各个数位上的数字之和加上 $b$ 的各个数位上的数字之和大于等于 $n$。

就是题目所说范围内的通用解。

所以：

当 $a$ 为 $4444 \cdots $ 且 $b$ 为 $5555 \cdots 6$ 或者 $a$ 为 $1111 \cdots $ 且 $b$ 为 $8888 \cdots 9$时，$a$，$b$ 为题目所说范围内的通用解。

$4 \times 300$ 已经大于 $1129$ 了，所以输出 $300$ 位是足够的。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	for(int i=1;i<=300;i++){
		putchar('4');
	}
	putchar('\n');
	for(int i=1;i<=299;i++){
		putchar('5');
	}
	putchar('6');
	putchar('\n');
	return 0;
}
```


---

## 作者：weihaozhen2010 (赞：0)

# **题目描述：**

设 $s(x)$ 表示正整数 $x$ 的十进制表示中的数字之和。给定两个整数 $n$ 和 $m$，找到一些正整数 $a$ 和 $b$，使得:

- $s(a) \ge n$ 
- $s(b) \ge n$
- $s(a+b) \leq m$ 

# **思路：**

- 本题有构造的方式

因为要使：

- $s(a) \ge n$ 

- $s(b) \ge n$

- $s(a+b) \leq m$ 

并且 $n$ 和 $m$ 满足：

- $1 \leq n \leq 1200$ 

- $1 \leq m \leq 1200$

所以可以让 $s(a)$ 和 $s(b)$ 巨大，大于 $1200$。

再让 $s(a)$ 和 $s(b)$ 的和为 $1$，一定小于等于 $1$。

如：

- $a=444 \dots 444$，其中有 $300$ 个 $4$。

- $b=555 \dots 556$，其中有 $299$ 个 $5$。

输出通解即可。

# **参考代码：**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=300;i++) 
   	{
    	cout<<"4";
   	}
	cout<<"\n";
	for(int i=1;i<=299;i++) 
  	{
		cout<<"5";
	}
	cout<<"6";
	return 0;
}
```

---

## 作者：watergod (赞：0)

# CF1028B Unnatural Conditions 题解

~~非常水，个人认为没有绿的难度~~

## 题意

规定一种函数 $s(x)$ 的值为每个位上的数字之和，比如 $x$ $=$ $123$，这个时候 $s(x) = 1+2+3 = 6$。输入两个数 $n$ 和 $m$，然后让你找两个数 $a$ 和 $b$，有 $s(a) \ge n$，$s(b) \ge n$，$s(a+b) \leq m$，输出任意符合条件的 $a$ 和 $b$ 的值。

## 分析

题目范围，长度不超过 $2230$，说明了暴力构造大概率过不了。题目中说输出任意符合条件的值，明显找到规律直接输出就可以了。

对于一个大于 $0$ 的数，$s(x)$ 的最小值是 $1$，思路是尽可能的让 $s(a+b)$ 等于 $1$，这个时候我们可以让 $a$ 等于 $n$ 个 $1$，那么可以计算出 $b$ 就是 $n-1$ 个 $8$ 加一个 $9$，这样 $s(a+b)$ 算出来就是 $1$ 了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,m;

int main(){
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		cout << 1;
	}
	cout << endl;
	for(int i=1;i<n;i++){
		cout << 8;
	}
	cout << 9 << endl;
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/138513035)

---

## 作者：hubin1 (赞：0)

# Unnatural Conditions

## 题目大意

令 $s(x)$ 为 $x$ 的各个数位上的数字之和。  
要求找到这样的 $a,b$，使得 $s(a),s(b)\ge n, s(a+b) \le m$  ，其中 $1 \le a,b< 10^{2230},1 \le n, m \le 1129$。

## 思路

1. 对于这道题，有没有一种通用的答案？有。
2. 对于两个数的数位和都大于等于 $n$ 这个条件，较好实现，让它足够长、每位上的数足够大就行。
3. 对于满足两个数的和的数位和小于等于 $m$ 这个条件，最简单的方法就是让他们的数位和为 $1$ 。因为 $m$ 的最小值就是 $1$。
4. 如何让两个很大的数的和所形成的数位和等于 $1$ 呢？我们可以利用进位的方法，让这个数的最高位变成 $1$，其余位变成 $0$。

## Code

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define debug(x) cerr<<#x<<"="<<x<<"\n"

int main()
{
	cout<<string(1500,'8')<<endl<<string(1499,'1')+'2'<<endl;
	return 0;
}
```



---

## 作者：_SkyLine_ (赞：0)

这其实是一道构造解的题，但最省力的方法其实是**构造一个可以适应所有输入的解**。

## 思路分析

因为我们的目的是构造出符合所有输入的解，所以我们应该从极端情况入手考虑问题。

为了方便，我们令 $n=1129$，$m=1$。因为满足该情况的解一定也可满足其他情况，也就可以作为任意输入的输出。为了构造出的 $a+b$ 恒满足 $s(a+b) \le 1$，我们需要使得：

- $a$，$b$ 的位数相等且他们的位数 $\le 2230$。
- $a+b$ 可以被表示成 $10$ 的整次幂的形式。

为了让 $a+b$ 满足上述条件，我们可以：

- 构造位数相等的 $a$，$b$。 ~~（废话）~~
- 为了方便，让 $a$，$b$ **除个位外**自己的其他位相等。
- $a$，$b$ 的**除个位外的**对应位之和等于 $9$。

这里我们取 $a=666 \cdots 6$，$b=333 \cdots 4$（当然其他满足要求的数也可以）。经计算得知当 $a$ 的位数 $ \ge 189$，$b$ 的位数 $ \ge 377$ 时满足条件。为了保证 $a$ 与 $b$ 的位数相同，我们统一让它们的位数等于 $377$。这样造出的 $s(a+b)$ 一定满足 $s(a+b)=1$，符合题意。

## 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    //根本不用读入
    ios::sync_with_stdio(false);
    for(int i=1;i<=377;i++)
    	cout<<"6";
    cout<<endl;
    for(int i=1;i<377;i++)
    	cout<<"3";
    cout<<"4";
    return 0;
}
```

---

## 作者：LBYYSM_123 (赞：0)

### 题意
令 $s(x)$ 为 $x$ 的各个数位上的数字之和。
要求找到 $a$ 和 $b$，使得 $s(a),s(b)\ge n$，$\ s(a+b)\le m$，$\ 1\le a,b< 10^{2230}$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	for(int i=1;i<=300;i++)
		putchar('4');
	putchar('\n');
	for(int i=1;i<=299;i++)
		putchar('5');
	putchar('6'),putchar('\n');
    return 0;
}
```
### 代码分析 
这是一道**构造题**。  
设： $z(x)$ 为 $x$ 的位数个数。   
$\because$ $1\le n,m\le1129$   
$\therefore$ $n=1129,m=1$ （为满足所有问题。）   
$\therefore$ $a=44444\cdots4,b=55555\cdots6$ （$z(a)=300,z(b)=300$ ） 
    
为什么呢？因为此时 $a+b\le 1$（进位得 $1000...000$），（$300 \times 4 \ge 1129,299 \times 5 +6\ge 1129$）。

---

## 作者：YouJerry (赞：0)

## 题意
找出 $a,b$ 使 $a$ 各个数位上的数字之和加上 $b$ 的各个数位上的数字之和大于等于 $n$ 并且 $a+b$ 各个数位上的数字之和小于等于 $m$：此题可以枚举但有更好的做法。

## 思路
题目说了 $n$ 和 $m$ 小于等于 $1129$，并且 $n$ 和 $m$ 大于等于 $1$。

所以只要 $a$ 各个数位上的数字之和加上 $b$ 的各个数位上的数字之和大于等于 $1129$ 并且 $a+b$ 各个数位上的数字之和小于等于 $1$ 那么这个解满足题目所说范围内的所有 $n$ 和 $m$。

显而易见：

+ 只要 $a+b=10\cdots$。

+ $a$ 各个数位上的数字之和加上 $b$ 的各个数位上的数字之和大于等于 $n$。

就是题目所说范围内的通用解。

所以：

+ 当 $a$ 为 $5555\cdots$ 且 $b$ 为 $444\cdots5$，$a,b$ 为题目所说范围内的通用解。


## 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	for(int i=1;i<=300;i++){
	    cout<<5;
	}
	cout<<endl;
	for(int i=1;i<=299;i++){
	    cout<<4;    
	}
	cout<<5;
	return 0;
} 
```

---

## 作者：WinterRain208 (赞：0)

这是一道关于数位和的构造题。找到方法橙题也不为过。

首先，这题的答案没有唯一解。再看数据,我们可以直接根据最值解出所有可能数据的通用解。

考虑什么情况下$s(a),s(b)$比$s(a+b)$的值大。不难看出$a+b$发生了进位。

$m,n$大于$1$，所以$a+b$可以用$10^n$的形式表现出来。

这时再去考虑$a,b$具体的值，因为$m,n$小于$1129$，所以如楼上苣佬所说，$300$是够的。

这是有很多方法去$AC$这道题了。

比如：

$88888888888.......8889$和
$11111111111.......1111$。

$55555555555.......5556$和
$44444444444.......4444$。

注意这题输出需要高精，各位不要入坑。

如各位所见，没有输入也不影响。

直接用循环输出即可。

$CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=1e5+5;

int main(){
	F(i,1,300)cout<<4;
	cout<<endl;
	F(i,1,299)cout<<5;
	cout<<6<<endl;
    return 0;
}

```

蒟蒻哭泣，欢迎各位大佬批斗。



------------


## wtrl


---

