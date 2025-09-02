# Fox Dividing Cheese

## 题目描述

两头贪心的小熊有 a，b 两块蛋糕，他们都想要大的那一块的那一块。于是狡猾的狐狸提出一个方案：让狐狸吃掉一些蛋糕，最后使得两块蛋糕大小一样。假如这块蛋糕的重量是 2 的倍数，那么狐狸可以吃掉二分之一；假如蛋糕的重量是 3 的倍数，那么狐狸可以吃掉三分之二；假如蛋糕的重量是 5 的倍数，狐狸可以吃掉五分之四。为了不让狐狸吃掉太多，熊要求以最少的次数将两块蛋糕吃的大小一样，求最小次数。

## 样例 #1

### 输入

```
15 20
```

### 输出

```
3
```

## 样例 #2

### 输入

```
14 8
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
6 6
```

### 输出

```
0
```

# 题解

## 作者：Plus_Ultra (赞：6)

#### 解法：

假如有解，最终答案合并成的数为 gcd(a, b) ，判断一下能否从 a, b 只通过除 2,3,5 除到 gcd(a, b)即可. 

#### 具体：
- 记 c = gcd(a, b),

- 那么 a 要除以 a/c 变成 c ，b要除以 b/c 变成 c 

- 所以我们判断一下 a/c 和 b/c 里是否含有不是 2, 3, 5 的因子，有就是无解，否则记录一下除以多少次 2, 3, 5 变成1 ， 相加输出答案即可

下面是代码（~~我相信各位大佬也不需要代码~~）：


```
#include <iostream>

#define LL long long

using namespace std;

LL a, b, c, k2, k3, k5, ac, bc, ans;

LL gcd(LL a, LL b)
{
	if(! b)  return a;
	return gcd(b, a % b);
}

int main()
{
	cin >> a >> b;
    
	c = gcd(a, b);
    
	ac = a / c;  bc = b / c;
    
	while(ac % 2 == 0)  k2++, ac /= 2;
	while(ac % 3 == 0)  k3++, ac /= 3;
	while(ac % 5 == 0)  k5++, ac /= 5;
    
	while(bc % 2 == 0)  k2++,bc /= 2;
	while(bc % 3 == 0)  k3++,bc /= 3;
	while(bc % 5 == 0)  k5++,bc /= 5;
    
	ans = k2 + k3 + k5;
    
	if(bc != ac)  cout << "-1" << endl;
	else  cout << ans << endl;
    
	return 0;
}
```




---

## 作者：HeCao2008 (赞：3)

### 题意

狐狸每次吃掉的操作可以理解为蛋糕变成了原来的**二分之一，或三分之一，或五分之一**。

将两块蛋糕吃到大小一样，而且尽量大一点，就可以理解为求**最大公因数**。

所以现在的任务很简单，就是看这两个数能不能通过只除以 $2$ , $3$ , $5$ 来除到最大公因数。

### 代码

代码非常简单，模拟判断即可，这里我用了 c++ 自带的 求 $\gcd(a,b)$ 的功能。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,ans;
int main(){
	cin>>a>>b;c=__gcd(a,b);
	a/=c,b/=c; //先把最大公因数除掉，然后判断每个数的因数是否只含 2 , 3 , 5
	while(a%2==0)a/=2,ans++;
	while(a%3==0)a/=3,ans++;
	while(a%5==0)a/=5,ans++;
	if(a!=1){cout<<-1;return 0;} //不能除完
	while(b%2==0)b/=2,ans++;
	while(b%3==0)b/=3,ans++;
	while(b%5==0)b/=5,ans++;
	if(b!=1){cout<<-1;return 0;} //不能除完
	cout<<ans<<endl;  //可以除完，输出计数器 ans
	return 0;
}
```

---

## 作者：liangbowen (赞：3)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF371B)

[更好的阅读体验？](https://www.luogu.com.cn/blog/liangbowen/solution-cf371b)

这题显然没有蓝的难度。

其他题解代码不好看，而且没有讲清楚，那我补一发吧。

## 题目简述

有两个数 $a$，$b$，每次操作可以给 $a$ 或 $b$ 除以 $2$，$3$，$5$。

问最少操作数使得 $a = b$。无解输出 $-1$。

## 思路

设最后，两数都需要等于 $x$。

即，$x$ 满足 $x \mid a, b$。

想要得到最少操作数，则 $x$ 要**尽可能大**。

你想到了什么？

对，$x$ 取 $a$ 和 $b$ 的**最大公因数**即可！

我们可以令 $a' = a \div x$，$b' = b \div x$。

所以，答案即为 $a'$ 与 $b'$ 的因数 $2$，$3$，$5$ 的总数。

需要注意，如果 $a'$ 或 $b'$ 不只有这三个因数，说明没法吃完。输出 $-1$ 即可。

## 代码

我们可以利用函数，来是码风美观。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int gcd(int x, int y)
{
	if (y == 0) return x;
	return gcd(y, x%y);
}
int cnt;
void play(int &x, int k)
//将 x 的所有因数 k 约掉。 
//x 前面的 & 符号可以使程序更改 x 的值。
//如果不加，x 就默认不改变。 
{
	while (x != 0 && x % k == 0) x /= k, cnt++;
}
void X()
{
	printf("-1");
	exit(0);
	//怎么在主函数外结束程序？ 
	//使用 exit(0) 而非 return 0 即可。 
}
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	int GCD = gcd(a, b);
	a /= GCD, b /= GCD;
	
	play(a, 2), play(a, 3), play(a, 5);
	if (a != 1) X();
	
	play(b, 2), play(b, 3), play(b, 5);
	if (b != 1) X();
	
	printf("%d", cnt);
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Aya_tt (赞：1)



1，求出输入 $a,b$ 的 $\gcd$，即最大公约数，就像样例中 $\gcd(15,20)=5$。

  ```
  int gcd(int a,int b){
      if(b == 0) {
          return a;
      }
      return gcd(b,a % b);
  }
  ```
  这是最大公约数的函数，用的方法是辗转相除法。
  
  可是为什么要求最大公约数呢？题面上：假如这块蛋糕的重量是 $2$ 的倍数，那么狐狸可以吃掉二分之一；假如蛋糕的重量是 $3$ 的倍数，那么狐狸可以吃掉三分之二；假如蛋糕的重量是 $5$ 的倍数，狐狸可以吃掉五分之四。
  
翻译过来就是：
  
  如果是 $2$ 的倍数，就除以 $2$。
  
  如果是 $3$ 的倍数，就除以 $3$。
  
  如果是 $5$ 的倍数，就除以 $5$。
 
所以蛋糕的数量就会不停除除除除除......直到最后他们一样，这是第一步。


------------

2,如上，不停作除法，可是除的数有限制，只能除 $2$，除 $3$，除 $5$，所以我们不妨设 $\gcd(a,b)=k,a\leftarrow a\div k,b\leftarrow b\div k$ 就是除的数，因为只能除 $2$、$3$、$5$，所以他除以 $2$、$3$、$5$ 一定能得到 $1$，不然就分不了，输出  $-1$。

代码如下：

```
	while(a % 2 == 0) a /= 2;	
	while(a % 3 == 0) a /= 3;
	while(a % 5 == 0) a /= 5;
   if(a != 1){                //如果是倍数，除完肯定是 1。
   		cout<<-1;
      return 0;
   }
  
```
$b$ 也是如此。

这样第二步就做完了。


------------
第三步就是要统计狐狸吃的最小次数了。

首先要建立一个统计的变量  $cnt$ 。

如何统计呢？

把他放到  `while`  循环里面不就完了吗，除一次， $cnt$  就加一，这不就结了吗？


------------
接下来上最终代码

```c++
#include<bits/stdc++.h>
using namespace std;
int cnt,a,b;
int gcd(int a,int b){
	if(b == 0) {
		return a;
	}
	return gcd(b,a % b);
}
int main(){
	cin>>a>>b;
	int k = gcd(a,b);//最最大公约数
	a /= k,b /= k;//求除的数
	while(a % 2 == 0) cnt++,a /= 2;	
	while(a % 3 == 0) cnt++,a /= 3;
	while(a % 5 == 0) cnt++,a /= 5;
	while(b % 2 == 0) cnt++,b /= 2;	
	while(b % 3 == 0) cnt++,b /= 3;
	while(b % 5 == 0) cnt++,b /= 5;  //以上都是在统计cnt，在判断是否都是2,3,5的倍数。
	if(a != 1 || b != 1) {
		cout<<-1;
		return 0;
	}
	cout<<cnt;//输出
} 
```

---

## 作者：L_M_ (赞：1)

题目大意：

两只贪心的熊有重量分别为a,b 的两块蛋糕，他们都想要大的那一块。

狡猾的狐狸提出一个方案：让狐狸吃掉一些蛋糕，最后使得两块蛋糕大小一样。

假如这块蛋糕的重量是 2 的倍数，那么狐狸可以吃掉二分之一；假如蛋糕的重量是 3 的倍数，那么狐狸可以吃掉三分之二；假如蛋糕的重量是 5 的倍数，狐狸可以吃掉五分之四。

为了不让狐狸吃掉太多，熊要求以最少的次数将两块蛋糕吃的大小一样，求最小次数

下面是题解：

恶意评分？顶多黄题

考虑将a，b分解成若干质因数的乘积，那么有这样一个显然的性质：如果这个两个数有除2，3，5以外不同的素因数，那么无解

也就是说，令c = gcd(a,b),如果a能只通过除2,3,5得到c，b同理，那么就有解

明确这个以后，做法就很显然了，在除的过程中顺带计数即可

懒得写乘幂，就挨个除。事实上如果数据大到10^18，要用乘幂的形式

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<climits>
#include<cstdlib>
#include<ctime>
using namespace std;
typedef long long ll;
ll a,b;
ll cnt;
ll gcd(ll x,ll y)
{ return !y ? x : gcd(y,x % y); }
int main()
{
	scanf("%lld%lld",&a,&b);
	ll c = gcd(a,b);
	a /= c,b /= c;
	while(a > 1)
	{
		int flag = 0;
		if(a % 5 == 0) a /= 5,flag++;
		if(a % 3 == 0) a /= 3,flag++;
		if(a % 2 == 0) a /= 2,flag++;
		if(!flag) {printf("-1"); return 0;}
		cnt += flag;
	}
	while(b > 1)
	{
		int flag = 0;
		if(b % 5 == 0) b /= 5,flag += 1;
		if(b % 3 == 0) b /= 3,flag += 1;
		if(b % 2 == 0) b /= 2,flag += 1;
		if(!flag) {printf("-1"); return 0;}
		cnt += flag;
	}
	printf("%lld",cnt);
}
```

---

## 作者：FreedomKing (赞：1)

### 题目大意
给你 $A$ 和 $B$ 两个数，你需要重复对 $A$ 和 $B$ 进行如下操作直到 $A=B$，

- 如果它是 $2$ 的倍数，那么就减去它的 $\dfrac{1}{2}$；

- 如果它是 $3$ 的倍数，那么就减去它的 $\dfrac{2}{3}$；

- 如果它是 $5$ 的倍数，那么就减去它的 $\dfrac{4}{5}$。

求最少的操作次数。
### 思路
在经过若干次操作后得到的就是它们两个的最大公约数 $C$，所以只需要用 $A$ 和 $B$ 除以他们的最大公约数 $C$ 求出 $A^\prime$ 和 $B^\prime$，再分解他们为 $2$、$3$ 或 $5$ 的因数，得出的分解次数便是最小操作次数，总的来说代码一共有一下几部分：

1. 求出 $A$ 和 $B$ 的最大公因数 $C$；

2. 分别用 $A$ 和 $B$ 除以 $C$ 得出 $A^\prime$ 和 $B^\prime$；

3. 分解 $A^\prime$ 和 $B^\prime$ 为 $2$、$3$ 和 $5$ 的因数，并统计分解次数；

4. 如果 $A^\prime$ 和 $B^\prime$ 分解后其中任意一个不为 $1$，输出 $-1$；否则输出统计的次数。

------------
[CF371B Fox Dividing Cheese](https://www.luogu.com.cn/problem/CF371B)
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int cake[4]={0,2,3,5};//存下要分解的因数
int a,b,c,ans;
int gcd(int x,int y){return (x%y==0)?y:gcd(y,x%y);}
int main(){
	scanf("%d%d",&a,&b);
	c=gcd(a,b);
	a/=c,b/=c;
	for(int i=1;i<=3;i++){//分解因数并记录次数
		while(a%cake[i]==0) ans++,a/=cake[i];
		while(b%cake[i]==0) ans++,b/=cake[i];
	}
	if(a==b) printf("%d",ans);
	else printf("-1");
	return 0;
}
```

---

## 作者：lilong (赞：0)

这题十分简单，化简一下题意为：一次操作定义为对一个数乘 $\frac{1}{2}$，$\frac{1}{3}$ 或 $\frac{1}{5}$，求使用最少的操作次数，使得两个数 $a$ 和 $b$ 相等。

不难发现，每一次都是倍数变换，所以最终的 $a$ 和 $b$ 是 $\gcd(a,b)$。
当然，由于题目的限制（即指定的数），所以我们要分别对
$\dfrac{a}{\gcd(a,b)}$ 和 $\dfrac{b}{\gcd(a,b)}$ 进行质因数分解（即变换过程），检验这两个数是否只由 $2$，$3$ 和 $5$ 构成，并在分解过程中统计质因数的个数。

代码实现十分简单，详细见下：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int ans;
int gcd(int x,int y)
{
	if(y==0) return x;
	return gcd(y,x%y);
}
bool fj(int x)
{
	int y=x;
	for(int i=2;i<=5;i++)
		while(y%i==0)
			y/=i,ans++;
	if(y>1) return false;
	return true;
}
int main()
{
	int a,b;
	cin>>a>>b;
	int c=gcd(a,b);
	a/=c;
	b/=c;
	if(fj(a)&&fj(b)) cout<<ans;
	else cout<<-1;
	return 0;
}
```


---

## 作者：_lzy_ (赞：0)

## 思路
1. 第一步我们可以用一个函数 $\gcd$ 求出来两块蛋糕的最大公因数，就可以知道我们究竟要减去多少的蛋糕才能使两块蛋糕相等。
1. 当我们求出第一步时就可以进行下一步了，将 $a,b$ 这两个数分别除以 $2,3,5$ 这三个数，再去判断两个数是否等于 $1$ 就行了。

有可能你没有弄懂第二步思路，那请看我下面的解释。

因为如果我们得到答案后直接输出就会出现有可能有个数既不是 $2$ 的倍数也不是 $3$ 和 $5$ 的倍数，就导致程序不会输出 $-1$ 了。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,k,s=0;
int x[3]={2,3,5};
int __gcd(int a,int b){//辗转相除法，最快求出最大公因数。
    if(b==0)return a;
    return __gcd(b,a%b);
}
bool js(int a,int b){
	if(a==1&&b==1)return true;
	return false;
}
int main()
{
    cin>>a>>b;
    k=__gcd(a,b); 
    a/=k,b/=k; 
    while(a%x[0]==0)s++,a/=x[0]; 
    while(a%x[1]==0)s++,a/=x[1];
    while(a%x[2]==0)s++,a/=x[2];
    while(b%x[0]==0)s++,b/=x[0]; 
    while(b%x[1]==0)s++,b/=x[1];
    while(b%x[2]==0)s++,b/=x[2];
    if(js(a,b)){//特判不等于一的情况。
        cout<<s;
		return 0;
	}
	cout<<-1;
   return 0;
} 
```


---

## 作者：ShineEternal (赞：0)

[更佳阅读](https://blog.csdn.net/kkkksc03/article/details/101117693)


## Description：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190921202816488.png)

## Solution：

$idea1:$

直接bfs搜索，因为一个数的约数个数还真不多。

但是有些麻烦？

$idea2:$

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190921202953991.png)

然后在分别试除$2,3,5$这几个数的时候也有点技巧，可以看一下

```cpp
#include<cstdio>
using namespace std;
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int main()
{
	int a,b,c;
	scanf("%d%d",&a,&b);
	c=gcd(a,b);
	a=a/c;
	int cnt=0;
	b=b/c;
	for(int i=2;i<=5;i+=(i-1))
	{
		while(a%i==0)
		{
			cnt++;
			a=a/i;
		}
		while(b%i==0)
		{
			cnt++;
			b=b/i;
		}
	}
	if(a!=b)printf("-1\n");
	else printf("%d\n",cnt);
	return 0;
}
```

---

## 作者：Code_AC (赞：0)

## 题目翻译：


给你两个数 $a,b$，每次操作可选择删除其中任意一个数的一部分，规则如下：

- 若改变的数为 $2$ 的倍数，则可删去此数的 $\frac{1}{2}$。

- 若改变的数为 $3$ 的倍数，则可删去此数的 $\frac{2}{3}$。

- 若改变的数为 $5$ 的倍数，则可删去此数的 $\frac{4}{5}$。

现问你将两数化为相同需要的最少操作次数。


## 题目分析：

显然，删去 $\frac{1}{2}$ 相当于乘 $\frac{1}{2}$，删去 $\frac{2}{3}$ 相当于乘 $\frac{1}{3}$，删去 $\frac{4}{5}$ 相当于乘 $\frac{1}{5}$。 

那么很显然，若要操作次数最少，那么最后化成的相同的数必定是 $a,b$ 两数的 gcd，即最大公因数。

那么思路就出来了：

**1.** 将 $a,b$ 两数的 gcd 求出；

**2.** 计算将两数各自变为这个 gcd 需要多少次操作；

**3.** 将两数所要的操作求和得答案。

（思路正确性可保证）

**注：**

看到 $1 \leqslant a,b \leqslant 10^9$，就知道要开 long long。

且这里还需要特判两种情况：

**1.** 若开始两数就相同，那么输出 $0$。

**2.** 若在变为 gcd 的过程中，无法通过除以 $2,3,5$ 来得到，即出现了非 $2,3,5$ 的因数，那么输出 $-1$。

这里给出核心部分代码：

```cpp
signed main()
{
    a=read(),b=read();
    if(a==b)
    {
        printf("0\n");
        return 0;
    }
    int c=gcd(a,b);
    int d=a/c,f=b/c;
    while(d%2==0)
    {
        d/=2;
        ans1++;
    }
    while(d%3==0)
    {
        d/=3;
        ans1++;
    }
    while(d%5==0)
    {
        d/=5;
        ans1++;
    }
    while(f%2==0)
    {
        f/=2;
        ans2++;
    }
    while(f%3==0)
    {
        f/=3;
        ans2++;
    }
    while(f%5==0)
    {
        f/=5;
        ans2++;
    }
    if(d!=1 || f!=1)
    {
        printf("-1\n");
        return 0;
    }
    ans=ans1+ans2;
    printf("%lld\n",ans);
	return 0;
}
```

---

