# Joty and Chocolate

## 题目描述

Little Joty has got a task to do. She has a line of $ n $ tiles indexed from $ 1 $ to $ n $ . She has to paint them in a strange pattern.

An unpainted tile should be painted Red if it's index is divisible by $ a $ and an unpainted tile should be painted Blue if it's index is divisible by $ b $ . So the tile with the number divisible by $ a $ and $ b $ can be either painted Red or Blue.

After her painting is done, she will get $ p $ chocolates for each tile that is painted Red and $ q $ chocolates for each tile that is painted Blue.

Note that she can paint tiles in any order she wants.

Given the required information, find the maximum number of chocolates Joty can get.

## 样例 #1

### 输入

```
5 2 3 12 15
```

### 输出

```
39
```

## 样例 #2

### 输入

```
20 2 3 3 5
```

### 输出

```
51
```

# 题解

## 作者：_tommysun_ (赞：2)

**题目大意**  
感觉这题翻译写得不太清晰，精简了一下：  
有$n$个数，如果这个数为$a$的倍数就可以获得$p$块巧克力，如果是$b$的倍数则获得$q$块巧克力，如果$k$是$a,b$的公约数则可以获得$p$块巧克力或$q$块巧克力（两者二选一

**思路**  
为了要使获得的巧克力**最多**，所以当$k$是$a,b$的公倍数时要选择$p,q$中的较大数，如果p,q一样就随便刷。  
由于本题范围达到了$10^9$，直接暴力模拟一定会T。所以可以事先算出有多少个蓝瓷砖，有多少个红瓷砖，详见下面代码。

**代码**
```
#include<bits/stdc++.h>
using namespace std;
long long gcd(long long x,long long y){ //辗转相除法求最大公因数。 
	if(x%y==0) return y;
	else return gcd(y,x%y);
}
long long lcm(long long x,long long y){
	return x*y/gcd(x,y); //两个数的最小公倍数=两个数的乘积/两个数的最大公因数。 
}
int main(){
	long long a,b,n,p,q;
	cin>>n>>a>>b>>p>>q;
	long long red=n/a;
	long long blue=n/b;
	long long red_and_blue=n/lcm(a,b);
	red-=red_and_blue;  //要减去最小公倍数 。 
	blue-=red_and_blue; 
	cout<<red*p+blue*q+red_and_blue*max(p,q); 
	return 0;
}
```


---

## 作者：HuangBarry (赞：1)

[原题 CF678C Joty and Chocolate](https://www.luogu.com.cn/problem/CF678C)  
## 思路：  
方法：数学思维。  
利用 $n \div \operatorname{lcm}(a,b)^{[1]}$ 算出 $1 \sim n$ 中有多少个既是 $a$ 的倍数也是 $b$ 的倍数。  
再利用 $n \div a$ 和 $n \div b$ 分别算出 $1 \sim n$ 中有多少个 $a$ 的倍数和 $b$ 的倍数。  
然后细分两种可能，一，${p \le q}^{[2]}$ 时，两种颜色都可以涂的瓷砖选择涂蓝色，二，${p \ge q}^{[2]}$ 时，两种颜色都可以涂的瓷砖选择涂红色。  
* $\operatorname{[1]}$：`lcm(a,b)` 表示 $a$ 和 $b$ 的最小公倍数。  
* $\operatorname{[2]}$：两种情况都带有等于的情况是因为当两种报酬等于时，无论选哪个报酬都一样。  
**注意：`lcm` 函数需要 `C++17`。**  
代码如下（不需要吸氧）：  
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a,b,p,q;
ll red;//可以涂成红色的个数(1~n中a的倍数的个数)
ll blue;//可以涂成蓝色的个数(1~n中b的倍数的个数)
ll both;//既可以涂成红色也可以涂成蓝色的个数(1~n中lcm(a,b)的倍数的个数)
int main(){
	cin>>n>>a>>b>>p>>q;
	both=n/(lcm(a,b));
	if(p<q){//分情况
		red=n/a-both;
		blue=n/b;
	}
	else{
		red=n/a;
		blue=n/b-both;
	}
	cout<<red*p+blue*q<<endl;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/164684704)

---

## 作者：hexuchen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF678C)

[更好的阅读体验？](https://www.luogu.com.cn/article/aun7he64)

## 题目大意

有 $n$ 个数，每一个 $a$ 的倍数价值为 $p$，每一个 $b$ 的倍数价值为 $q$，如果是 $a$ 和 $b$ 的最小公倍数，则价值既可以是 $p$ 也可以是 $q$。如果都不是，则价值为 $0$。请问这 $n$ 个数的总价值是多少？

## 思路分析

一道水题。

首先，先求出涂红色的总价值。涂红色的瓷砖数量明显是 $\lfloor n \div a \rfloor$，但是还要注意，因为也涂了蓝色瓷砖，所以这个数还要减去涂色的重复部分，即 $\lfloor n \div \operatorname{lcm (a , b)} \rfloor$。依此方法，再计算出涂蓝色的总价值。最后，记得还要算重复部分的价值。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define int unsigned long long //记得开long long
using namespace std;
int n,a,b,p,q;
int gys(int a,int b){ //最大公因数
	if(a%b==0)
		return b;
	gys(b,a%b);
}
int gbs(int a,int b){
	return a*b/gys(a,b); //公式求最小公倍数
}
signed main(){
	cin>>n>>a>>b>>p>>q;
	int red=(n/a-n/gbs(a,b))*p; //涂红色瓷砖的价值
	int blue=(n/b-n/gbs(a,b))*q; //涂蓝色瓷砖的价值
	int gg=n/gbs(a,b)*max(p,q); //重复部分
	cout<<red+blue+gg; //三者之和
	return 0;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF678C)
## 思路
**ps：题解中未定义的变量都是题目中的变量。**

先不考虑 $a$ 和 $b$ 的公倍数，则对于 $a$ 和 $b$ 的倍数肯定是都会刷上颜色的。之后对于 $a$ 和 $b$ 的公倍数，假设 $a$ 和 $b$ 的公倍数在 $1$ 到 $n$ 中共 $g$ 个，则答案应该加上 $\max(g \times p,g \times q)$。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
LL n,a,b,p,q;//注意开 long long 
I main(){
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&p,&q);
	LL ans = 0,g = n / (a * b / __gcd(a,b));//a 与 b 的公倍数个数 
	ans = max(g * p,g * q);//先把公倍数处理完 
	ans += (n / a - g) * p + (n / b - g) * q;//算上 a 与 b 的其他倍数 
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：2011FYCCCTA (赞：0)

# [原题](https://www.luogu.com.cn/problem/CF678C)
简单有趣的思维题~

---
### 题意

我认为我需要解释题目中的一些细节：

Joty 有编号为 $1$ ~ $n$ 的 $n$ 块瓷砖。她将编号为 $a$ 的倍数的瓷砖涂上红色，**每**涂上一块红色瓷砖就得到 $p$ 块巧克力。她也将编号为 $b$ 的倍数的瓷砖涂上蓝色，**每**涂上一块蓝色瓷砖就得到 $q$ 块巧克力。若一块瓷砖被涂上了 $2$ 种颜色，那么她能得到任意一种颜色的瓷砖所得的巧克力报酬，**并舍弃原本此瓷砖所得的分数**。

---
### 思路

1. 先将所有涂 $a$ 的倍数的瓷砖所得的巧克力和涂 $b$ 的倍数的瓷砖所得的巧克力加起来。

2. 再将每块编号为 $a$ 和 $b$ 的公倍数（公倍数是最小公倍数的倍数，因此只用求出最小公倍数即可）的瓷砖所得的巧克力数（$p + q$）减去 $p$ 和 $q$ 间更小的数（这样保留下来的就是 $p$ 和 $q$ 这之间更大的）即可。

以下是实现如上思路的公式：

$$n \div a \times p + n \div b \times q - n \div \operatorname{lcm}(a , b) \times \min(p , q)$$

#### 注意：卡 `int`，连 `long long` 都卡！用 `unsigned long long`！

---
### 代码：
```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n , a , b , p , q , ans;

int gcd(int x , int y)
{
    if (y == 0) return x;
    return gcd(y , x % y);
}

int lcm(int x , int y)
{
    return x * y / gcd(x , y);
}

signed main()
{
    cin >> n >> a >> b >> p >> q;
    ans = n / a * p + n / b * q - n / lcm(a , b) * min(p , q);
    cout << ans;
	return 0; 
}
```
[评测记录，~~编号挺好玩~~](https://www.luogu.com.cn/record/list?pid=CF678C&user=923403&page=1)

---

## 作者：__LiChangChao__ (赞：0)

## 思路

因为 $1\le n \le 10^9$，显然直接模拟是不行的，但是题目中**公倍数**已经在提示我们这道题的做法了。

由于涂色是带有规律性的（是 $a$ 或 $b$ 的倍数时才涂色），设在 $1\sim n$ 中有 $x$ 块可以涂红的瓷砖，$y$ 块可以涂蓝的瓷砖，$z$ 块又可以涂红又可以涂蓝的的瓷砖，显然有：

$$
x=\lfloor \frac{n}{a}\rfloor,y=\lfloor \frac{n}{b}\rfloor
$$

那么 $z$ 呢？

根据基础数论，有：

$$
\text{lcm}(a,b)=\frac{a\times b}{\gcd(a,b)}
$$

其中 $\text{lcm}$ 代表最小公倍数。

所以有：

$$
z=\frac{n}{\text{lcm}(a,b)}=\frac{n}{\frac{a\times b}{\gcd(a,b)}}
$$

最后，利用贪心思想，对于又可以涂红又可以涂蓝的的瓷砖，涂上获利更多的颜色。

同时，我们还要将 $x,y$ 减去 $z$，避免重复计算。

所以最后答案就为：

$$
(x-z)\times p+(y-z)\times q+z\times \max(p,q)
$$

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,n,a,b,p,q,sum[5];//sum[1]代表z，sum[2]代表x，sum[3]代表y
int main() {
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&p,&q);
	sum[1]=n/((a*b)/__gcd(a,b)),sum[2]=(n/a)-sum[1],sum[3]=(n/b)-sum[1];//计算x，y，z，计算式上已给出
	printf("%lld",sum[2]*p+sum[3]*q+sum[1]*max(p,q));//输出答案
}

```

---

## 作者：无咕_ (赞：0)

## 题解索引
1. **题目大意**
2. **Solution**
3. **AC code**
4. **类似题型**

代码类型： C++（cpp）

是否吸氧：否

不压行代码长度：18

------------

## 题目大意
题面： [<传送门>](https://www.luogu.com.cn/problem/CF678C)

题意：给出 $n,a,b,p,q$ ，已知可以在编号为 $[1,n]$ 的序列中进行以下操作：

1. 对于 $i$，若存在 $i\mid a$，则可以获得 $p$ 的收益。

2. 对于 $i$，若存在 $i\mid b$，则可以获得 $q$ 的收益。

3. 对于 $i$，若存在 $i\mid \operatorname{lcm}(a,b)$，则可以获得 $p$ 或 $q$ 的收益

求最大收益。

~~术语理解： GCD+式子题。~~

## Solution

我们分几个块来讲

### 一、LCM

众所周知，$a\times b=\operatorname{lca}(a,b)\times \gcd(a,b)$，至于证明……可以去找算数基本定理了。

所以，我们只需要求出 $\gcd(a,b)$，就能根据式子得出 $\operatorname{lca}(a,b)$：

$$\operatorname{lca}(a,b)=a\times b\div \gcd(a,b)$$

### 二、涂色（情况讨论）

对于 $i$，存在 $i\mid a$ 的情况，那么我们直接涂色即可；同样，对于 $i$，存在 $i\mid b$ 的情况，那么我们直接涂色即可。当然，前提是 $p,q>0$。

那么对于 $i\mid \operatorname{lca}(a,b)$ 的情况我们怎么处理呢（前面已经求出了 $\operatorname{lca}(a,b)$ ）？

首先，我们要记住，**包括前面说的两种情况，如果 $p>q$，我们是要选 $p$ 的！换句话说，我们在 $\operatorname{lca}(a,b)$ 及其倍数的时候，要选择 $\max(p,q)$！**

**注意！一个点被选一次！**

不开 `long long` 见祖宗！

## AC code

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
long long gcd(long long a,long long b){//欧几里得辗转相除法
    return b==0?a:gcd(b,a%b); 
}long long n,a,b,p,q;
int main(){
    scanf("%I64d %I64d %I64d %I64d %I64d",&n,&a,&b,&p,&q);
    if(p<0)p=0;//这两个if其实并没用，题目里保证了p,q>0
    if(q<0)q=0;
    long long lcm=a*b/gcd(a,b);//求出lcm
    long long nlcm=n/lcm;//求出i|lcm的情况在n中出现的次数
    long long na=n/a-nlcm,nb=n/b-nlcm;//求出i|a,i|b的次数，并将其减去i|lcm的次数（因为不一定选哪个）
    printf("%I64d\n",na*p+nb*q+nlcm*max(p,q));//选a的*p，选b的*q，选lcm的*max(p,q)
    return 0;
}
```

AC 记录 [<传送门>](https://www.luogu.com.cn/record/56994818)

## 类似题目

GCD [CF1342C Yet Another Counting Problem](https://www.luogu.com.cn/problem/CF1342C)

题解入口[CF1342C Yet Another Counting Problem 题解](https://www.luogu.com.cn/blog/wugu-2333/solution-cf1342c)


---

## 作者：HyyypRtf06 (赞：0)

~~翻译已上传，应该能看见翻译了~~

一道数论题，但是要理清楚关系：

首先把编号倍数为 $a$ 的瓷砖刷成红色；  
然后把编号倍数为 $b$ 的瓷砖刷成蓝色；

但是这个时候有个问题：如果它既是 $a$ 的倍数又是 $b$ 的倍数怎么办呢？？

秉承着`利益最大化`的思想理念，如果刷成蓝色比红色的巧克力数目多，刷蓝色；如果少，刷红色。~~如果一样多就看哪个顺眼刷哪个~~

理解上面的话之后此题已经能过了

code:
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;

int main(){
	long long ans=0;
	long long n,a,b,q,w;
	cin>>n>>a>>b>>q>>w;
	long long A=n/a,B=n/b,c=a/__gcd(a,b)*b;//A为刷红，B为刷蓝
	long long C=n/c;//C为两个都可以
	A-=C;
	B-=C;//先减掉两个都可以的
	cout<<A*q+B*w+C*max(q,w)<<endl;
//A*q：刷成红色的报酬；B*w：刷成蓝色的报酬
//max(q,w)*C：哪个报酬多就刷哪个
	return 0;
}
```

---

