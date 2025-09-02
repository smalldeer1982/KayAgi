# Rectangular Game

## 题目描述

The Smart Beaver from ABBYY decided to have a day off. But doing nothing the whole day turned out to be too boring, and he decided to play a game with pebbles. Initially, the Beaver has $ n $ pebbles. He arranges them in $ a $ equal rows, each row has $ b $ pebbles ( $ a>1 $ ). Note that the Beaver must use all the pebbles he has, i. e. $ n=a·b $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF177B1/72b3400d0a6aa691e5c49fe273a750815ff16b58.png) 10 pebbles are arranged in two rows, each row has 5 pebbles Once the Smart Beaver has arranged the pebbles, he takes back any of the resulting rows (that is, $ b $ pebbles) and discards all other pebbles. Then he arranges all his pebbles again (possibly choosing other values of $ a $ and $ b $ ) and takes back one row, and so on. The game continues until at some point the Beaver ends up with exactly one pebble.

The game process can be represented as a finite sequence of integers $ c_{1},...,c_{k} $ , where:

- $ c_{1}=n $
- $ c_{i+1} $ is the number of pebbles that the Beaver ends up with after the $ i $ -th move, that is, the number of pebbles in a row after some arrangement of $ c_{i} $ pebbles ( $ 1<=i<k $ ). Note that $ c_{i}>c_{i+1} $ .
- $ c_{k}=1 $

The result of the game is the sum of numbers $ c_{i} $ . You are given $ n $ . Find the maximum possible result of the game.

## 说明/提示

Consider the first example ( $ c_{1}=10 $ ). The possible options for the game development are:

- Arrange the pebbles in 10 rows, one pebble per row. Then $ c_{2}=1 $ , and the game ends after the first move with the result of 11.
- Arrange the pebbles in 5 rows, two pebbles per row. Then $ c_{2}=2 $ , and the game continues. During the second move we have two pebbles which can be arranged in a unique way (remember that you are not allowed to put all the pebbles in the same row!) — 2 rows, one pebble per row. $ c_{3}=1 $ , and the game ends with the result of 13.
- Finally, arrange the pebbles in two rows, five pebbles per row. The same logic leads us to $ c_{2}=5,c_{3}=1 $ , and the game ends with the result of 16 — the maximum possible result.

## 样例 #1

### 输入

```
10
```

### 输出

```
16
```

## 样例 #2

### 输入

```
8
```

### 输出

```
15
```

# 题解

## 作者：zhangyuanxiao (赞：3)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF177B1)

## 题意
- 有 $n$ 颗鹅卵石，每次将 $n$ 颗鹅卵石排成 $a \cdot b$ 的矩形，去掉 $a-1$ 行，在对剩下的 $n/b$ 颗鹅卵石重复此操作。求每次操作后剩下的鹅卵石数的和的最大值（刚开始的 $n$ 算第 $0$ 次操作后剩下的）。
- $2 \le n \le 10^9$。

## 分析
这道题我们可以使用**贪心**算法。每次操作结束后，为了使每次留下的鹅卵石数的和最大，应该让矩形的行数最少，这样每行的鹅卵石个数才会最多，操作后剩下的鹅卵石数才会最多，每次操作剩下的鹅卵石数的和才会最大。

## 代码
```cpp
#include<cmath>
#include<iostream>
#define int long long
using namespace std;
int n,ans,flag;
signed main(){
	cin>>n;
	ans+=n;//ans用来记录鹅卵石数的和
	while(n!=1){
		flag=0;//判断n是否是质数
		for(int i=2;i*i<=n;i++){
			if(n%i==0){
				n=n/i;//用面积除以小的边长，得到大的边长
				ans+=n;
				flag=1;//n可以被除了1和它本身的数整除，是合数
				break;
			}
		}
		if(!flag) n=1,ans+=1;//n是质数，只能排成n行一列的矩形
	}
	cout<<ans;
	return 0;
}
```

如发现错误，欢迎私信指出。

---

## 作者：yanxingyu0910 (赞：1)

**题目链接**

[CF177B1](https://www.luogu.com.cn/problem/CF177B1)

本题与[CF177B2](https://www.luogu.com.cn/problem/CF177B2)一样但是数据要更弱一点。

**题意描述**

聪明的海狸有 $n$ 颗鹅卵石，他每次将这 $n$ 颗鹅卵石排列成 $a*b$ 的一个矩形，并拿走 $a-1$ 行，再对剩下的 $n/b$ 颗石子进行同样操作，问每次操作后剩下石子数的和最大是多少？

**分析题意**

从贪心的思路去想，要想使石子数和最多就要让行数最少，每行石子个数最多，因为规定是矩形所以要整除才可以计数。

要注意的一点是 $sum$ 一开始要先赋值个输入的 $n$ 这样就可以解释样例了。

**代码**

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
inline LL read(){//快读 
    register LL x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
LL n,sum,i;
signed main(){
	n=read();
	sum=n;
	while(n>1){
		int x=0;
		for(i=2;i<=sqrt(n);i++){//这里不用sqrt优化会tle 
			if(n%i==0){
				n/=i;
				sum+=n;
				x=1;
				break;
			}
		}
		if(x==0){
			break;
		}
	}
	cout<<sum+1;//还需要加个1 
	return 0;
}
```


---

## 作者：Fr0sTy (赞：1)

### 题意简述
------------

给定一个整数 $n$,请构造一个 $x \times y$ 的矩形，每次只留下最上面一行，并将最上面一行的个数累加进 $ans$。求 $ans$ 的值。

### 解题思路
------------

首先这是一道**贪心**。

我们要让总和最大，就是要让第一行最大。

但是显然，如果 $x$ 为 $1$，答案就为 $n$，显然无法取到最优解，所以我们要稍加改变。

读题可知 $x \in \mathbb{Z} , y \in \mathbb{Z}$ 且 $x \neq 1$，这样就是在求 $n$ 除一以外的最小约数。递归即可。

这里有几点要注意一下：

1. $n$ 可能是个素数，而我们枚举最小约数是到 $\sqrt{n}$。所以在这种情况下只能使 $x = 1$。

2. 最后要将 $ans + 1$，因为最后肯定还剩下一个。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int main() {
	scanf("%d",&n);
	while(n>=1) {
		bool flag=false;
		for(int i=2;i<=sqrt(n);i++) {
			if(n%i==0) {
				ans+=n; n/=i;
				flag=true; break;
			}
		}
		if(!flag) { ans+=n; break;}
	}
	printf("%d",ans+1);
	return 0;
}
//code by TheCedar
```

做完了这道题再看看[这道题](https://www.luogu.com.cn/problem/CF177B2)呦。

---

## 作者：ForeverHYX (赞：1)

# 题解011 CF177B1

## 01 题面说明

在我开始写这道题之前我已经提交了翻译，但是似乎还没有过审，现在的翻译是有误的，真正的题面是这样的：

现有 $n$ 个石子，我们每次把他排成一个 $a*b$ 的矩形，只剩下第一行，并对剩下的 $b$ 个石子进行同样的操作，对每次操作后剩余的石子进行加和，直至只剩一个石子，求这个和的最大值。

## 02 本题思路

### 贪心

因为我们希望每次剩下来的石子总是最多的，因此我们希望我们排出来的矩形的行数应当尽可能的小，但是很显然我们不能制造一个 $a=1$ 的矩阵，因此题意就转化为了求取当前状态下 $n$ 除了 $1$ 以外的最小约数。

## 03 AC代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int n,ans,minn;
int main(){
    scanf("%d",&n);
    while(n>1){
        minn=n;//对于最小行数先初始化
        for(int i=2;i<=sqrt(n);i++){
            if(n%i==0){
                minn=i;
                break;
            }
        }//找最小约数
        ans+=n;//加和操作
        n/=minn;
    }
    printf("%d",ans+1);//最后一次操作后我们还剩下1个加回来
}

```
**抄袭毫无意义哦**


 _本蒟蒻的第11篇题解，求管理员大大通过呢！_ 

---

## 作者：ivyjiao (赞：1)

题意：有 $n$ 个石子， 每次操作都将剩余石子摆成一个矩形并拿走最后一行， 求每次操作剩下石子数和的**最大值**。

注意是最大值，所以我们要尽量构造一个行数最大的矩阵，这样每次拿走的石子数最少。

怎么让行数最大？就是要找到当前剩余石子数的**除 $1$ 以外的**最小约数作为行数（因为如果是 $1$，就直接全拿走了，显然不是最优）。

每次将石子数和加上当前剩余的石子数，最后输出，**记得加上最后剩下的那个石子。**

这题是 [双倍](https://www.luogu.com.cn/problem/CF177B1) [经验](https://www.luogu.com.cn/problem/CF177B2)。

代码：

```cpp
#include<iostream>
using namespace std;
int n,ans;
bool flag;
int main(){
	cin>>n;
	while(n){
		flag=0;
		for(int i=2;i*i<=n;i++){
			if(n%i==0){
				ans+=n;
				n/=i;
				flag=1; 
				break;
			}
		}
		if(flag==0){ 
		    ans+=n;
            break;
		}
	}
	cout<<ans+1;
}
```


---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF177B1)
## 题意
现在有 $n$ 个鹅卵石,每次构造一个 $a \times b$ 的矩形，每次只留下第一行，剩下的 $a - 1$ 行全部取走，在对剩下的鹅卵石进行新一轮操作，问每次操作后剩下石子数的和最大是多少？
## 思路
- 这是一道贪心题
- 要保证每次的行数最少，也就是说让每行的鹅卵石数量最多。

------------

## 注意事项：
- 存答案的变量初始值应该赋为 $n$ 
- 最后的答案要加 $1$ ，因为最后肯定会剩下一个

# AC 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	int n;
	cin >> n;
	int ans = n;
	while(n > 1){
		bool flag = false;
		for(int i = 2; i * i <= n; i++){
		    if(n % i == 0){
			    n /= i;
			    ans += n;
			    flag = true;
			    break;
		    }
	    }
	    if(flag == false)break;
	}
	cout << ans + 1 << endl;
	return 0;
}
```

------------

### [已AC](https://www.luogu.com.cn/record/97630613)

---

## 作者：MoyunAllgorithm (赞：0)

### 题目大意
本题为CF177B2的数据略微削弱版。

给你 $N (2 \le N \le 10^{9})$ 个棋子，将它们排列为 $a$ 行 $b$ 列的矩形，拿走 $a-1$ 行，用剩下的 $b$ 个棋子作为新一轮的 $N$ 循环进行该操作直到无法再分解。输出每轮结束后的剩余棋子数（包括一开始的棋子数）。

### 分析

看这个操作，发现该问题是不断将原问题的规模缩小之后进行循环求解的，符合递归的性质，考虑用递归模拟实现。

我们发现，对于 $N$ 个棋子，想要在操作后保留尽可能多的棋子数，应该让行数尽可能少。因此，从小到大枚举 $N$ 的因数作为行数，模拟操作即可（然而似乎其他题解都没有使用递归求解。。。我认为递归更符合题目操作本身的意图）。

特别地，对于 $N$ 是 $1$ 或者质数，它就只能排列为纵向的 $N$ 行 $1$ 列。

### AC CODE

```c
#include <bits/stdc++.h>
using namespace std;
int N;
int ans;
void Func(int x)
{
//	printf("%d\n",x);
	if(x==1)
	{
		ans++;
		return;
	}//如果只有1个，不能再分解
	for(int i=2;i*i<=x;i++)//枚举因数
	{
		if(x%i==0)//满足条件
		{
			x/=i;//拿掉a-1行棋子
			ans+=x;
	//		printf("%d %d %d\n",x*i,i,ans);
			Func(x);//展开新一轮递归
			return;
		}
	}
	ans++;//如果没有被枚举到因数，那么x是质数
	return;
}
int main()
{
	scanf("%d",&N);
	ans=N;
	Func(N);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：sysong (赞：0)

# 题解CF177B1 Rectangular Game

### 题目描述

共有 $n$ 个点，每次将其排成一个矩形（**注意：行数大于 1 **），最后留下第一行，求每一次最大点数和。（原数算第一次）

~~不知道为什么翻译是错的。。。目前写的是去掉最后一行。~~

### $Solution$

既然是矩形，那么长和宽必然为点数的因数，要长最大，就使宽最小。

如果无法分解出符合要求的因数（当前 $n$ 为质数或 $n \leq 2$），那么结束循环。

**这里包括等于 2，因为长也要大于 1 。**

分解因数函数如下：

```c++
inline int fac(int k){
	if(k<=2)return 0;				// 当前值小于等于 2 
	if((k&1)==0)return 2;			// 值为偶，直接返回 2 
	for(R int i=3;i*i<=k;i+=2)		// 值为奇，那么因数也为奇
		if(k%i==0)return i;
	return 0;						// 值为质数
}
```

~~由于加了个小小的优化，还抢到了最优解。~~

### $AC\ Code$

```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
using namespace std;

inline int rd(){
	R int x=0;R char c=gc();//,f=1
	while(c>'9'||c<'0')c=gc();//{if(c=='-')f=-1;
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x;//*f
}

inline int fac(int k){
	if(k<=2)return 0;
	if((k&1)==0)return 2;
	for(R int i=3;i*i<=k;i+=2)
		if(k%i==0)return i;
	return 0;
}

int main(){
	R int t=rd(),f=1,ans=0;
	do{
		t/=f;
		ans+=t;
	}while(f=fac(t));				// 如果换成 while，ans 应初始化为 t。
	printf("%d\n",ans+1);
	return 0;
}
```





***by jsntsys***

$2020.11.24$



---

## 作者：幻影星坚强 (赞：0)

翻译的有些问题，应该是只留下一行石子。

因为要使每一步剩下的石子都足够大，所以每一次所取行数应为$n$除$1$以外的最小因数，这样能使剩下的列数最大。

代码如下:
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n;
int ans;
int main()
{
	scanf("%d", &n);
	while(n != 1)
	{
		int yn = n;
		for(int i = 2; i * i <= n; ++ i)
		{
			if(n % i == 0)
			{
				yn = i;
				break;
			}
		}
		ans += n;
		n /= yn;
	}
	printf("%d", ans + 1);
}
```


---

