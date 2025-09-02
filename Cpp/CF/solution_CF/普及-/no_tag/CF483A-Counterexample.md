# Counterexample

## 题目描述

Your friend has recently learned about coprime numbers. A pair of numbers $ {a,b} $ is called coprime if the maximum number that divides both $ a $ and $ b $ is equal to one.

Your friend often comes up with different statements. He has recently supposed that if the pair $ (a,b) $ is coprime and the pair $ (b,c) $ is coprime, then the pair $ (a,c) $ is coprime.

You want to find a counterexample for your friend's statement. Therefore, your task is to find three distinct numbers $ (a,b,c) $ , for which the statement is false, and the numbers meet the condition $ l<=a<b<c<=r $ .

More specifically, you need to find three numbers $ (a,b,c) $ , such that $ l<=a<b<c<=r $ , pairs $ (a,b) $ and $ (b,c) $ are coprime, and pair $ (a,c) $ is not coprime.

## 说明/提示

In the first sample pair $ (2,4) $ is not coprime and pairs $ (2,3) $ and $ (3,4) $ are.

In the second sample you cannot form a group of three distinct integers, so the answer is -1.

In the third sample it is easy to see that numbers $ 900000000000000009 $ and $ 900000000000000021 $ are divisible by three.

## 样例 #1

### 输入

```
2 4
```

### 输出

```
2 3 4
```

## 样例 #2

### 输入

```
10 11
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
900000000000000009 900000000000000029
```

### 输出

```
900000000000000009 900000000000000010 900000000000000021
```

# 题解

## 作者：Chtholly_L (赞：5)

### 题意：

求在 $l$ 到 $r$ 之间满足 $a$ ， $b$ 的最大公约数等于 $b$ ， $c$ 的最大公约数等于 $1$ ，且 $a$ ， $c$ 的最大公约数不等于 $1$ 的数 $a$ ， $b$ ， $c$ 。

---

### 分析：

其实这道题没有那么难（我看题解区好多大佬都在找规律，而我太蒻了，只能纯模拟~），只要在 $l$ 到 $r$ 之间用三个循环来分别枚举 $a$ , $b$ , $c$ 就可以了。

另外，用[欧几里得算法](https://baike.baidu.com/item/欧几里得算法/1647675?fr=aladdin)来计算最大公约数就行了。

---

上代码！

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int gcd(int a,int b)  //求最大公约数
{
	if(b==0)return a;
	return gcd(b,a%b);  //欧几里得算法（即辗转相除法），一个小小的递归
}
int main()
{
	long long l,r;
	cin>>l>>r;
	for(long long i=l;i<=r;i++)  //枚举 a 
	for(long long j=i;j<=r;j++)  //枚举 b
	for(long long k=j;k<=r;k++)  //枚举 c
	{
		if(gcd(i,j)==1&&gcd(j,k)==1&&gcd(i,k)!=1)  //如题意
		{
			cout<<i<<" "<<j<<" "<<k;  //输出
			return 0;  //结束程序
		}
	}
	cout<<-1;  //如果没找到就输出 -1
	return 0;  //结束程序
}
```


---

## 作者：Remake_ (赞：4)

看到题目描述：莫比乌斯反演么？WTF？橙题？感觉还可做。

看到$l$和$r$的范围：对不起，打扰了，换下道题。

看到$l$和$r$的差值：这题你确定不是红题？

注意：

1，要开long long或unsigned long long。

2，$gcd$要用欧几里得算法或是c++自带的__$gcd$函数。

3，找到答案后一定要 $return\,0$ 或者 $exit(0)$。

注意完这几点基本上就能AC辣。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	unsigned long long l,r;
	cin>>l>>r;
	for(unsigned long long i=l;i<=r;i++){
		for(unsigned long long j=i;j<=r;j++){
			for(unsigned long long k=j;k<=r;k++){
				if(__gcd(i,j)==1&&__gcd(j,k)==1&&__gcd(i,k)!=1){
					cout<<i<<" "<<j<<" "<<k;
					return 0;
				}
	        }
	    }
	}
	cout<<"-1";
}
```


---

## 作者：清清老大 (赞：1)

## 题意

输入 $l,r$ ，求满足 $\gcd(a,b)=\gcd(b,c) = 1 ,\gcd(a,c)\ne 1,l\leq a\lt b \lt c\leq r$ 的一个 $a,b,c$ 的值。

## 思路

当 $l - r\lt2$ 时，显然不行

当 $l - r = 2$ 时，有 $l,l+1,l+2$ 三个数。如果 $l$ 是奇数，那么三个数互质，最大公因数就都是1，无解。如果 $l$ 是偶数，$\gcd(l,l+1)=\gcd(l+1,l+2) = 1 ,\gcd(l,l+2)=2\ne 1$ ,答案就是 $l,l+1,l+2$。

当 $l - r\gt2$ 时，和上面的情况相同，输出两个相邻的偶数和中间的奇数即可。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    long long l,r;
    cin >> l >> r;
    if(r - l < 2)
    {
        cout << -1;
        return 0;
    }
    else if(r - l == 2)
    {
        if(l % 2 == 0)
        {
            cout << l << " " << l + 1 << " " << l + 2;
            return 0;
        }
        else
        {
            cout << -1;
            return 0;
        }
    }
    if(l % 2 == 0)
    {
        cout << l << " " << l + 1 << " " << l + 2;
        return 0;
    }
    else
    {
        cout << l + 1 << " " << l + 2 << " " << l + 3;
        return 0;
    }
}
```


---

## 作者：LucasXu80 (赞：1)

继续Python题解~

读题时，我的心路历程：

gcd？嗯，貌似不难。。。

小于等于10的18次方？嗯，Python毫无压力。

输出满足要求的三个数？那不要循环死了。。。

如果这个时候你就放弃，只能说你离AC那么近，又那么远。。。

静下心来分析一下。看样例。

#### 输入 2 4

#### 输出 2 3 4

然后我就突然有了灵感了。请看：

两个连续的自然数，**一定互质**，即最大公约数为1。

两个连续的奇数也是如此。

这两个应该是小学知识了，就不多做介绍了。

那么好了，我们来分情况讨论：

如果区间内整数个数$≤2$，显然是不行的。

如果区间内整数个数恰好$=3$，那么再分情况：

如果头尾两数是偶数，那么不互质，这三个数满足题意。

否则，头尾两数互质，无解。

如果区间内整数个数$≥4$，一定是有解的，只要根据奇偶关系讨论输出$a,a+1,a+2$还是$a+1,a+2,a+3$就可以了。

上[AC](https://www.luogu.com.cn/record/33671705)代码！

```python
import sys #后面提前结束程序要用
a,b=map(int, input().split()) #输入两个数
if b-a<=1: #区间整数个数不足，无解
    print(-1)
    sys.exit() #提前结束程序
if b-a==2 and a%2==1: #首位都是奇数，互质，无解
    print(-1)
    sys.exit() #提前结束程序
#进入下面的一定是b-a≥3或者b-a=2且a,b都是偶数的了
if a%2==0: #是偶数，输出a,a+1,a+2，这样头尾都是偶数，不互质
    print(a,end=' ')
    print(a+1,end=' ')
    print(a+2)
else: #是奇数，需要从偶数开始输出，即a+1
#这种情况下a+3不会超过b，因为b-a一定≥3
    print(a+1,end=' ')
    print(a+2,end=' ')
    print(a+3)
```
本人Python萌新，是自学的，代码很难看，大佬们原谅~

~~厚脸皮地~~求赞！

---

## 作者：Nt_Tsumiki (赞：1)

## 题意
给定右界限$r$ 和左界限$l$ ,求在这个范围内满足`gcd(a,b)=1` ，`gcd(b,c)=1`，`gcd(a,b)!=1`且$a<b<c$ 的最小一组数。
## 做法
这道题可以根据左右边界直接用三个循环暴力枚举$a$ 、$b$ 、$c$ ，先要判断他们的大小，然后求他们最大公因数，提到最大公约数我们就会想到欧几里得（即辗转相除法），但我们今天不手打欧几里得（~~我不会告诉你是因为我懒得打欧几里得算法的~~），用一个c++库函数：`__gcd`，`__gcd`是STL中求最大公约数的函数，其原理就是欧几里得，我们可以使用这个函数来解决这道题，最后，一大坑点来了：数据范围，很明显超了int ，所以要用long long ，上代码（有两版，一种为STL，一种为欧几里得手打）。
## Code 1
```cpp
//本人码风有所修改
#include<iostream>
#include<algorithm> //__gcd()需要的函数库
#define ll long long //十年OI一场空，不开long long见祖宗

using namespace std;
ll l,r;//定义左右边界

int main() {
	cin>>l>>r;
	for(ll i=l;i<=r;i++) {//枚举a
		for(ll j=i;j<=r;j++) {//枚举b
			for(ll k=j;k<=r;k++) {//枚举c
				if((__gcd(i,j)==1 and __gcd(j,k)==1 and __gcd(i,k)!=1) and (i<j and j<k and i<k)) {//判断
					cout<<i<<" "<<j<<" "<<k;//输出
					return 0;//可以直接在这里结束，节省空间
				}
			}
		}
	}
	cout<<-1;//如果没有，输出-1
	return 0;//结束
}
```
## Code 2

```cpp
#include<iostream>
#define ll long long //十年OI一场空，不开long long见祖宗

using namespace std;
int r,l;

int gcd(int x,int y) {//手打欧几里得算法
	if(!y)return x;//递归边界
	int z=x%y;
	x=y;
	y=z;//辗转相除
	return gcd(x,y);//递归
}

int main() {
	cin>>l>>r;
	for(ll i=l;i<=r;i++) {//枚举a
		for(ll j=i;j<=r;j++) {//枚举b
			for(ll k=j;k<=r;k++) {//枚举c
				if((gcd(i,j)==1 and gcd(j,k)==1 and gcd(i,k)!=1) and (i<j and j<k and i<k)) {//判断
					cout<<i<<" "<<j<<" "<<k;//输出
					return 0;//可以直接在这里结束，节省空间
				}
			}
		}
	}
	cout<<-1;//如果没有，输出-1
	return 0;//结束
}
```
## 总结
主要考察对欧几里得的运用（你也可以偷懒用STL）。

---

## 作者：HuZHUNZHUN (赞：0)

~~这道题很㵘诶~~

本题思路：

显然，对于整数 $n$，我们知道 $n$ 和 $n+1$ 必定互质。

同样地，也可以推出 $n+1$ 和 $n+2$ 必定互质。

只需要满足 $n$ 和 $n+2$ 不互质就可以了。

想要 $n$ 和 $n+2$ 不互质，只能是 $n$ 和 $n+2$ 都被 $2$ 整除。

因此只需要判定是否存在 $n$ 满足：

$n\ge l$；

$n\le r-2$；

$2\mid n$。

即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;
int main()
{
	ios::sync_with_stdio(false);
	cin>>l>>r;
	l=l+(l%2);
	if(l+2>r) cout<<"-1";
	else cout<<l<<" "<<l+1<<" "<<l+2<<endl;
	return 0;
}
```

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF483A)

小学生又来写题解啦！

刚看到范围，觉得不能枚举。

仔细想一下，其实可以，因为第一组解应该离左边界较近，很快可以出答案。

所以，我们**可以尝试暴力枚举**。

最大公约数就用[辗转相除法](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95/1647675?fromtitle=%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4%E6%B3%95&fromid=4625352&fr=aladdin)，写成一个函数，大家应该都会。

找到解就结束程序。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#define LL long long
using namespace std;
LL gcd(LL x, LL y)  //辗转相除法。 
{
	if(y == 0) return x;
	return gcd(y, x % y);
}
int main()
{
	LL L, R;
	scanf("%lld%lld", &L, &R);
	for (LL a = L; a <= R; a++)
		for (LL b = a+1; b <= R; b++)
			for (LL c = b+1; c <= R; c++)  //这样枚举可以直接保证三个数的大小关系。 
				if (gcd(a, b) == 1 && gcd(b, c) == 1 && gcd(a, c) != 1)
				{
					printf("%lld %lld %lld", a, b, c);
					return 0;   //记得结束掉，因为只输出一组解。 
				}
	printf("-1");
	return 0;
}
```


---

## 作者：Waaifu_D (赞：0)

研究题意，我们可以发现，

只要L，R差大于等于2时且L为偶数，输出L,L+1,L+2即可

但当L为奇数时，输出L+1,L+2,L+3

还有一种情况就是L,R差等于2

例如3，5显然是无解，可得出这种情况下只需判断L奇偶性即可
```cpp

#include<bits/stdc++.h>
using namespace std;
long long l,r,sum;
int main()
{
	cin>>l>>r;
	if(r-l<=1)//如果两数差小于2，肯定是无解的 
	{
		cout<<-1;
		return 0;
	}
	if(r-l==2)//如果两数差等于2 
	{
		if(l%2==0)//如果l为偶数 ，说明下一个（b）是奇数，则c为偶数，符合题意输出 
		{
			cout<<l<<" "<<l+1<<" "<<l+2;//
		}
		else//不符合就输出无解-1 
		{
			cout<<-1;
		}
	}
	if(r-l>2)//当两数差大于2时 
	{
		if(l%2==0) //如果l为偶数，则正常输出A,B,C 
		{
			cout<<l<<" "<<l+1<<" "<<l+2;
		}
		else//要么加个1在输出 
		{
			cout<<l+1<<" "<<l+2<<" "<<l+3;
		}
	}
	return 0;
}
```


---

## 作者：BMTXLRC (赞：0)

[可能会更好的博客阅读体验（](https://www.luogu.com.cn/blog/BMTX/CF483A)

$\texttt{Upd 2021/07/15}$ 修改了部分公式

# [CF483A] Counterexample 题解

### 题意：

给定 $l$ 和 $r$，求一组 $\{a,b,c\}\in[l,r]$，使得 $\gcd(a,b)=1$，$\gcd(b,c)=1$ 且 $\gcd(a,c)\neq 1$。如果不存在一组这样的解，输出 $-1$。~~（表述应该没问题吧）~~

------------

### 分析：

看到这题感觉要用什么高深的算法，但是一看到数据范围就知道这题很简单了，$r-l\leqslant 50$。

#### 解法一：

定义一个循环变量 $i$，枚举左端点，一个循环变量 $j$，枚举中间的数，一个循环变量 $k$，枚举右端点。

$\gcd$ 不用自己打一个函数，我们有 `__gcd(x,y)`，可以很方便地求出最大公约数。

时间复杂度看作 $O((r-l)^3)$。

#### 解法二：

首先分类讨论：

1，如果 $r-l<2$，无解。

若 $a=l$，$b=r$，则一定不存在一个 $c\in[l,r]$，使 $a\neq c$ 且 $b\neq c$。

因此无解。

2，如果 $r-l=2$，可能有解。

当 $l\equiv 0(\operatorname{mod}\,2)$ 时，$a=l$，$b=l+1$，$c=r$。此时 $\gcd(a,b)=1$，$\gcd(b,c)=1$，$\gcd(a,c)=2$。满足题意，为一组解。

当 $l\equiv 1(\operatorname{mod}\,2)$ 时，$a-l$，$b=l+1$，$c=r$。此时 $\gcd(a,b)=1$，$\gcd(b,c)=1$，但 $\gcd(a,c)=1$。

为什么 $\gcd(l,r)=1$ 呢，显然一个奇数的奇数倍才能是一个奇数，又因为选取的数必须不相同，于是我们必须得使 $r=3l$ 且 $r=l+2$，这样才能是仅次于一倍最小的。只有 $l=1$，$r=3$ 才能满足刚刚那个方程的解，但是 $\gcd(1,3)=1$，不满足题意。

故只有 $l\equiv 0(\operatorname{mod}\,2)$ 时，才有解。

3，如果 $r-l>2$，必定存在解。

考虑 $a$ 的奇偶性：

如果 $a\equiv 0(\operatorname{mod}\,2)$，像刚刚说的必定有解 $\{a,a+1,a+2\}$，满足题意。

如果 $a\equiv 1(\operatorname{mod}\,2)$，把 $a$ 加上 $1$ 即可，可以转化为 $a$ 为偶数的情况。

时间复杂度看作 $O(1)$。

------------

### 坑：

记得开 $\texttt{long long}$；

记得输出 $-1$。

------------

### 代码：

爆枚解法（即解法 $1$）：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ll l,r;
	cin>>l>>r;
	for(ll i=l;i<=r;i++){
		for(ll j=i+1;j<=r;j++){
			for(ll k=j+1;k<=r;k++){
				if(__gcd(i,j)==1&&__gcd(j,k)==1&&__gcd(i,k)!=1){
					printf("%lld %lld %lld",i,j,k);
					return 0;
				}
	        }
	    }
	}
	printf("-1");
}
```

不知道是不是数论的解法（即解法 $2$）：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll l,r;
int main(){
	cin>>l>>r;
	if(r-l<=1){cout<<-1;return 0;}
	if(r-l==2){
		if(l%2==0) cout<<l<<" "<<l+1<<" "<<l+2;
		else cout<<-1;
	}
	if(r-l>2){
		if(l%2==0) cout<<l<<" "<<l+1<<" "<<l+2;
		else cout<<l+1<<" "<<l+2<<" "<<l+3;
	}
}
```


---

## 作者：CobaltChloride (赞：0)

```
//本题只要在范围内有两个偶数,就输出它们和中间的奇数,否则r与l的差必<=2,不可能有>2的公因子,输出-1
#include<bits/stdc++.h>
using namespace std;
#define int long long
int l,r;
int main(){
	cin>>l>>r;
	if(r-l>=3){
		if(l%2==0) cout<<l<<' '<<l+1<<' '<<l+2;
		else cout<<l+1<<' '<<l+2<<' '<<l+3;
	}
	if(r-l==2){
		if(l%2==0) cout<<l<<' '<<l+1<<' '<<l+2;
		else cout<<-1;
	}
	if(r-l<=1) cout<<-1;
    return 0;
}
```

---

