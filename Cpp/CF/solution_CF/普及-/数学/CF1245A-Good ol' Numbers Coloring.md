# Good ol' Numbers Coloring

## 题目描述

对于一个非负整数的数列$0,1,2...$，给定两个整数$a,b(1\le a,b\le10^4)$，我们把每个数从小到大染色

每个数字只能被染成黑白两种颜色，而且对$i$染色的规则如下

- 如果$i=0$，则染为白色
- 如果$i\ge a$且$i-a$是白色的，则染为白色
- 如果$i\ge b$且$i-b$是白色的，则染为白色
- 否则染为黑色

举个例子，如果$a=3,b=5$，那么这个序列的染色情况就是（0代表白色，1代表黑色）
$$0,1,1,0,1,0,0,1,0,0,...$$
注意：

- 有可能无限多个数被染为黑色。举个例子，当$a=10,b=10$的时候，只有$10$的倍数是白色的，其余数都是黑色
- 也有可能有限多个数被染为黑色。再举个例子，当$a=1,b=10$的时候，没有一个数是黑色的。

你的任务是判断对于每个$a,b$，数列的黑色数是不是无限的。

如果有无限个数是黑色的，则输出$Infinite$（不含引号）。否则输出$Finite$（不含引号）。

## 样例 #1

### 输入

```
4
10 10
1 10
6 9
7 3
```

### 输出

```
Infinite
Finite
Infinite
Finite
```

# 题解

## 作者：andyli (赞：4)

观察样例，我们发现当$gcd(a,b)=1$时有有限个黑色的数字，反之则有无限个黑色的数字。  

考虑形如$ax+by (x\geq 0, y \geq 0)$的数字，显然它们都是被染成白色的数字。若有两个白色数字相邻，我们就有$ax+by=ax'+by'+1$，变形得$a(x-x')+b(y-y')=1$，令$p=(x-x'),q=(y-y')$，得$ap+bq=1$。上式当且仅当$\gcd(a,b)=1$时有解且有无限多个解，即黑色数字的数量有限。于是，当$\gcd(a,b)=1$时有有限个黑色的数字，反之则有无限个黑色的数字。  

主要代码如下：  
```cpp
int main()
{
	int T;
	io.read(T);
	while (T--) {
		int a, b;
		io.read(a, b);
		int t = gcd(a, b); // from include 'numeric'
		if (t == 1) writeln("Finite");
		else writeln("Infinite");
	}
    return 0;
}
```

---

## 作者：Soledad_S (赞：2)

显然被染为白色的点是形如$ax+by\;(x,y\ge0)$的数

再显然如果有一段区间连续为白色且长度超过$\min(a,b)$则黑点有限

推一推两个白点相邻的情况
$$ax+by=ax'+by'+1$$
$$a(x-x')+b(y-y')=1$$
设$X=(x-x'),Y=(y-y')$，原式等于
$$aX+bY=1$$
这是一个不定方程，只有但$\gcd(a,b)$是$1$的约数才有解，一旦有解就有无限个解（不懂的左转拓展欧几里得）

所以当$\gcd(a,b)=1$，$X,Y$有无数解，即黑点有限

反之无限

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
inline int read(){
	char ch;
	int bj=0;
	while(!isdigit(ch=getchar()))
	  bj|=(ch=='-');
	int res=ch^(3<<4);
	while(isdigit(ch=getchar()))
	  res=(res<<1)+(res<<3)+(ch^(3<<4));
	return bj?-res:res;
}
void printnum(int x){
	if(x>9)printnum(x/10);
	putchar(x%10+'0');
}
inline void print(int x,char ch){
	if(x<0){
		putchar('-');
		x=-x;
	}
	printnum(x);
	putchar(ch);
}
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
int n,m;
signed main(){
	int T=read();
	while(T--){
		n=read(),m=read();
		if(gcd(n,m)!=1)puts("Infinite");
		else puts("Finite");
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

`感谢@N_z_ 在7.11帮我改正题解，证明裴蜀定理。`
# 题目大意
对于一个非负整数的数列 $0,1,2...$，给定两个整数 $a,b(1 \le a,b \le 10^{4})$，我们把每个数从小到大染色。

每个数字只能被染成黑白两种颜色，而且对 $i$ 染色的规则如下：

- 如果 $i = 0$，则染为白色。
- 如果 $i \ge a$ 且 $i - a$ 是白色的，则染为白色。
- 如果 $i \ge b$ 且 $i - b$ 是白色的，则染为白色。
- 否则染为黑色。

举个例子，如果 $a=3,b=5$，那么这个序列的染色情况就是（0 代表白色，1 代表黑色）。
$$0,1,1,0,1,0,0,1,0,0,...$$
注意：

- 有可能无限多个数被染为黑色。举个例子，当 $a = 10,b = 10$ 的时候，只有 $10$ 的倍数是白色的，其余数都是黑色。
- 也有可能有限多个数被染为黑色。再举个例子，当 $a = 1,b = 10$ 的时候，没有一个数是黑色的。

判断对于每个 $a,b$，数列的黑色数是不是无限的。

如果有无限个数是黑色的，则输出 `Infinite`。否则输出 `Finite`。

# 题目解析

本体重点是求最大公约数函数和裴蜀定理。

求最大公约数有三种。

### 1.库函数

```cpp
int a,b;
cin>>a>>b;
cout<<__gcd(a,b)<<endl;
```

直接调用库函数，方便快捷。

### 2.辗转相除法

```cpp
int gcd(int x,int y){
	int r;
	while(x%y!=0){
		r=x%y;
		x=y;
		y=r;
	}
	return y;
}
```
或者是:

```cpp
int gcd(int x,int y){
	return y>0?gcd(y,x%y):x;
}
```

[关于辗转相除法的链接在这。](https://zhuanlan.zhihu.com/p/324578532)

还有一种就是递归：

```cpp
int gcd(int x,int y){
	if(x%y==0)
		return y;
	else
		return (gcd(y,x%y));
}
```

此时只需判断一下：如果输入的数据最大公因数不是一，就输出 `Infinite`，否则输出 `Finite`，依据如下：

裴蜀定理（或贝祖定理）得名于法国数学家艾蒂安·裴蜀，说明了对任何整数 $a、b$ 和它们的最大公约数 $d$，关于未知数 $x$ 和 $y$ 的线性不定方程（称为裴蜀等式）：若 $a,b$ 是整数，且 $\gcd(a,b)=d$，那么对于任意的整数 $x,y,ax+by$ 都一定是 $d$ 的倍数，特别地，一定存在整数 $x,y$，使 $ax+by=d$ 成立。
它的一个重要推论是：$a,b$ 互质的充分必要条件是存在整数 $x,y$ 使 $ax+by=1$。 

[具体证明](https://zhuanlan.zhihu.com/p/336264546)。

所以代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int x,int y){
	if(x%y==0)
		return y;
	else
		return (gcd(y,x%y));
}
int main(){
	int t,x,y;
	cin>>t;
	while(t--){
		cin>>x>>y;
		if(gcd(x,y)!=1)printf("Infinite\n");
		else printf("Finite\n");
	}
	return 0;
}
```
都看到这里了，给个赞再走吧。

---

## 作者：Barnett_Ren (赞：2)

~~CF卡了我五分钟才挤进去~~

谈一下这道题的思路：

刚开始读完题发现没什么思路。~~瞎写了一发现样例也过不了。~~

于是我就秉着~~大胆假设，无需证明~~的思路。

是不是有关两个数的最大公约数（据题意得）。

如果两个数的最大公约数不是1，那么就输出**InFinite**。相反，如果两个数

最大公约数为一，那么就输出**Finite**。

下面贴一下代码：

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

int t,a,b;
ll read(){
	ll ans=0;
	char last=' ',ch=getchar();
	while(ch<'0' || ch>'9')last=ch,ch=getchar();
	while(ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
	if(last=='-')ans=-ans;
	return ans;
}
inline int gcd(int a,int b){
	if (b == 0) {
    	return a; 
    } 
	else {
    	return gcd(b, a % b); 
    }
}
int main(){
	t=read();
	while(t--){
		a=read();b=read();
		int ans=gcd(a,b);
		if(ans==1) printf("Finite\n");
		else printf("InFinite\n");
	} 
	return 0;
}


```


---

## 作者：bit_ (赞：2)

~~是的这场CF我好像就A题没挂~~

这题~~观察可得~~因为如果$a,b$不互质，则只能在$x \times\gcd\left(a, b\right)\left(x \in N\right)$涂白色

这个显然啊~~其实是我不会证~~

于是在$\gcd\left(a, b\right) = 1$时无无数黑点

嗯。。。于是这题就完了。。。

~~然后我被降智写了19分钟~~

然后代码好写的一批qwq

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read();

int gcd(int, int);

int main(int argc, char* argv[])
{
	int t = read();
	for(register int i = 1; i <= t; i++)
	{
		int a = read(), b = read();
		puts(gcd(a, b) == 1 ? "Finite" : "Infinite");
	}
	return 0;
}

inline int read()	//带了个快读qwq
{
	int val = 0, op = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-')
		{
			op = 0;
		}
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		val = (val << 1) + (val << 3) + (ch ^ 48);
		ch = getchar();
	}
	return (op ? val : ~val + 1);
}

int gcd(int a, int b)	//gcd标准求法
{
	if(a < b)
	{
		swap(a, b);
	}
	if(a % b == 0)
	{
		return b;
	}
	else
	{
		return gcd(b, a % b);
	}
}
```

~~没错然后它就被A掉了~~

---

## 作者：lrmlrm_ (赞：2)

## 题意

$\qquad$对所有的自然数进行染色，对于其中的 $ i $ ，具体要求如下：
 
 - 当 $i=0$ 时染白色；
 - 当 $i \geq a$ 并且 $i-a$ 为白色时染白色；
 - 当 $i \geq b$ 并且 $i-b$ 为白色时染白色；
 - 否则染为黑色
 
$\qquad$问最后染黑色的数的个数是否为无限个，如是，输出 `Infinite` ，否则输出 `Finite` 。


## 思路

$\qquad$先说结论，如果 a 和 b 互质 $($ 最大公因数为 1 $)$ ，那么就有有限个染了黑色的数，反之就有无限个。 

$\qquad$为什么呢？一个被染白色的数必定能拆分成 $ ax+by(x,y\geq0)$ 的形式。然后很容易想到如果有连续一段的白色长度超过的 $\min(a,b)$ ，后面就没有黑色。满足此情况必须要两个染白色的数相邻。根据以上信息可得出 $ax+by=ax_1+by_1+1$ ，化简得到 $a(x-x_1)+b(y-y_1)=1$ ，设 $s_1=(x-x_1) , s_2=(y-y_1) $ ，则原式变为： $as_1+bs_2=1$ 。 要让黑色有限，这个方程就需要无限个解 。

$\qquad$如果 $a$ 和 $b$ 不互质，则 $a$ 与 $b$ 有最大公因数 $ k(k>1)$ ，设 $a=pk,b=qk$ ，则： $as_1+bs_2=s_1pk+s_2qk=k(s_1p+s_2q)=1$ ，易得 $s_1p+s_2q=\frac{1}{k}$ 。因为 $p,q,s_1,s_2$ 都是整数，因此 $s_1p+s_2q$ 也应是整数，但是 $k$ 是整数， $\frac{1}{k}$ 必定不为整数，互相矛盾。所以得出，如果 $a,b$ 互质，黑色的个数就有限。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&a,&b);
		if(__gcd(a,b)!=1)printf("Infinite\n");
		else printf("Finite\n");
	}
	return 0;
}
```

---

## 作者：awaken1802 (赞：1)

### 题意：
有一个数列，每个格子 $i$ 按照下列规则涂成黑白两色：

如果 $i = 0$，就涂成白色。

如果 $i \geq a$ 且 $i - a$ 是白色，就把 $i$ 也涂成白色。

如果 $i \geq b$ 且 $i - b$ 是白色，就把 $i$ 也涂成白色。

否则涂成黑色。

按上面操作后，如果有无限个黑色格子，则输出 `Infinite`，否则输出 `Finite`。
### 思路：
我们首先看样例，发现 $a = 1 , b = 10$ 和 $a = 7 , b = 3$ 这两组样例中黑色格子是有限的，同时，题面中用于举例的 $a = 3 , b = 5$ 中黑色格子也是有限的。经过观察，我们发现这三组数据的共同点就是每组数据的 $a$ 与  $b$互质。

我们可以先求出 $a$ 与 $b$ 的最大公约数，如果 $a$ 与 $b$ 的最大公约数是 $1$，就说明 $a$ 与 $b$ 互质。
### 代码：
给出一个求最大公约数的代码模板：
```cpp
long long gcd(long long kn,long long km){
	if(kn%km==0)return km;
	return gcd(km,kn%km);
}
```
完整代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long gcd(long long kn,long long km){
	if(kn%km==0)return km;
	return gcd(km,kn%km);
}
long long t,a,b;
int main(){
	scanf("%lld",&t);
	for(long long i=1;i<=t;i++){
		scanf("%lld%lld",&a,&b);
		if(gcd(a,b)==1)printf("Finite\n");
		else printf("Infinite\n");
	}
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：1)

拼凑出一个两个数一定互质  
该结论可用于更多的数  
那么结论显然
```cpp
#include <cstdio>
 
using namespace std;
 
inline int gcd(int a, int b) {
	int t;
	while(b) {
		t = b; b = a % b; a = t;
	}
	return a;
}
 
int main() {
	int t, a, b;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &a, &b);
		if(a == 1 || b == 1 || gcd(a, b) == 1) {
			printf("Finite\n");
		} else {
			printf("Infinite\n");
		}
	} 
	return 0;	
}
```

---

## 作者：arc_suvr (赞：1)

拼凑出一个两个数一定互质

该结论可用于更多的数

那么就可以直接用代码来写了

若两数互质则有有限个数字，反之则有无限个数字

这题建议评橙

上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int hz(int a, int b) // 判断是否互质
{
	if (a == b) // 如果a, b两数相等，说明不互质
		return 0;
	if (a == 1 || b == 1) // 特判a, b都为1时也不互质
	 	return 0;
	for (int i = 2; i <= min(a, b); i++) 
	{
		if (a % i == 0 && b % i == 0) // 如果a, b两数模i相等，说明不互质
		 	return 0;
	}
	return 1; // 否则互质
}
void solve()
{
	int T;
	cin >> T;
	while (T--) // 多组样例
	{
		int n, m;
		scanf("%d%d", &n, &m);
		if (hz(n, m) == 0) // 判断，如果互质输出“Infinte”，否则输出“Finite” 
			cout << "Infinite" << endl;
		else 
			cout << "Finite" << endl;
	}	
}
int main()
{
	solve(); // 调用函数
	return 0;
} 
```

---

