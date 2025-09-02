# Balls and Boxes

## 题目描述

Little Vasya had $ n $ boxes with balls in the room. The boxes stood in a row and were numbered with numbers from 1 to $ n $ from left to right.

Once Vasya chose one of the boxes, let's assume that its number is $ i $ , took all balls out from it (it is guaranteed that this box originally had at least one ball), and began putting balls (one at a time) to the boxes with numbers $ i+1 $ , $ i+2 $ , $ i+3 $ and so on. If Vasya puts a ball into the box number $ n $ , then the next ball goes to box $ 1 $ , the next one goes to box $ 2 $ and so on. He did it until he had no balls left in his hands. It is possible that Vasya puts multiple balls to the same box, and it is also possible that one or more balls will go to the box number $ i $ . If $ i=n $ , Vasya puts the first ball into the box number $ 1 $ , then the next ball goes to box $ 2 $ and so on.

For example, let's suppose that initially Vasya had four boxes, and the first box had $ 3 $ balls, the second one had $ 2 $ , the third one had $ 5 $ and the fourth one had $ 4 $ balls. Then, if $ i=3 $ , then Vasya will take all five balls out of the third box and put them in the boxes with numbers: $ 4,1,2,3,4 $ . After all Vasya's actions the balls will lie in the boxes as follows: in the first box there are $ 4 $ balls, $ 3 $ in the second one, $ 1 $ in the third one and $ 6 $ in the fourth one.

At this point Vasya has completely forgotten the original arrangement of the balls in the boxes, but he knows how they are arranged now, and the number $ x $ — the number of the box, where he put the last of the taken out balls.

He asks you to help to find the initial arrangement of the balls in the boxes.

## 样例 #1

### 输入

```
4 4
4 3 1 6
```

### 输出

```
3 2 5 4 ```

## 样例 #2

### 输入

```
5 2
3 2 0 2 7
```

### 输出

```
2 1 4 1 6 ```

## 样例 #3

### 输入

```
3 3
2 3 1
```

### 输出

```
1 2 3 ```

# 题解

## 作者：_louhc (赞：2)

# 题意简述

有$N$个盒子，每个盒子中有若干个球（也可能为空），从某个盒子$i$中取出所有球，依次放到$i+1,i+2...N-1,N,1,2...$中，（每次放一个），直至球放完。注意：盒子中可能会放多次球，$i$号盒子中也有可能放球。现在已知盒子的个数、最后一个放球的位置，求出最开始每个盒子中放的球的个数。（输出任意一组即可）

# 思路

由于一开始盒子$i$被取空，最后盒子$i$中球的个数肯定是最少的（当然也有可能有的盒子球的个数和它一样少，但绝对不可能比它还小）。所以，找出最小值$t$，所有元素先减去$t$。如果不考虑最后一个放的位置$x$，直接任意选一个$0$变成$t\times N$即可，但是若要考虑$x$，我们可以从$x$不断向前枚举，直至找到第一个$0$。具体处理过程请看代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Re register
#define MAXN 100005
#define LL long long

int N, x;
LL a[MAXN], t(0x7f7f7f7f7f7f7f7f);

void pre( int &x ){//找前一个元素
	x--; if ( x == 0 ) x = N;
}

int main(){
	scanf( "%d%d", &N, &x );
	for ( int i = 1; i <= N; ++i ) scanf( "%I64d", &a[i] ), t = min( t, a[i] );//最小值
	for ( int i = 1; i <= N; ++i ) a[i] -= t;//先减去t
	t *= N;
	while( a[x] ) a[x]--, t++, pre(x);//a序列中减去后t要加上
	a[x] = t;
	for ( int i = 1; i <= N; ++i ) printf( "%I64d ", a[i] );
	return 0;
}
```



---

## 作者：xyf007 (赞：2)

# 本质是倒着模拟，遇到0输出
## 如果直接暴力会TLE
### 因此先将最小的减到0再模拟
# 一定要开long long！！！
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
long long n,x,a[100001];
int main(int argc, char const *argv[])
{
	std::cin>>n>>x;
	long long mn=9e18;
	for (long long i = 1; i <= n; ++i)
	{
		std::cin>>a[i];
		if (a[i]<mn)
		{
			mn=a[i];
		}
	}
	for (long long i = 1; i <= n; ++i)
	{
		a[i]-=mn;
	}
	long long now=x,sum=mn*n;
	while(1)
	{
		if (a[now]==0)
		{
			a[now]+=sum;
			for (long long i = 1; i <= n; ++i)
			{
				std::cout<<a[i]<<' ';
			}
			return 0;
		}
		--a[now];
		++sum;
		now=now==1?n:now-1;
	}
	return 0;
}
```

---

## 作者：4526_ (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF260C)

小模拟，注意细节

设从第 $s$ 个盒子中取出全部的 $snum$ 个球，由于是从下一个盒子开始放，在给这个盒子放球前，其他盒子一定都放过了，最后 $s$ 中球最少，记这个最小值为 $mmin$

同理，如果取出的球不足 $n$ 个，那么 $s$ 中球的个数（$mmin$）为 $0$

可是球最少的盒子不一定只有一个，根据初始盒子的位置可以分为三种情况：

1、$s<x$，$snum=mmin*n+x-s$，即放完 $mmin$ 遍后剩下的球给了 $s+1$ 到 $x$，这些盒子需要额外减去 $1$

2、$s=x$，$snum=mmin*n$，即从 $s+1$ 开始恰好放了 $mmin$ 遍，最后一个球给了 $s$

3、$s>x$，$snum=mmin*n+x+n-s$，即放完 $mmin$ 遍后剩下的球给了 $s+1$ 到 $n$ 和 $1$ 到 $x$，这些盒子需要额外减去 $1$

上述思路没有问题，但在查找最小值时记录其位置并直接按照这三种情况判断并不能通过此题，原因还是不能确定 $s$ 的位置，会出现把某个盒子减到 $-1$ 的情况

当存在多个可能的 $s$ 时，强行这样计算需要加入大量的判断语句，导致代码冗长，故舍去

给每个盒子先减去 $mmin$ ，必然会出现球数为 $0$ 的盒子（可能的 $s$），而我们已知最后一个球放在盒子 $x$ 里，所以从 $x$ 往前，遇到的第一个 $0$ 就是一定正确的 $s$，此时 $snum=mmin*n+$经过的盒子数

最后，因为题目只保证剩下的球数在 $int$ 范围内，$snum$ 的最大值为 $10^{14}$，仍然需要开 $long\ long$ 存储

AC代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

long long n,x,arr[100003],mmin=151926081715;

int main(){
	scanf("%lld %lld",&n,&x);
	for(register int i=1;i<=n;++i){
		scanf("%lld",&arr[i]);
		mmin= arr[i]<=mmin ? arr[i] : mmin;
	}
	for(register int i=1;i<=n;++i) arr[i]-=mmin;
	for(register int i=x;;--i){
		if(i==0) i=n;
		if(arr[i]==0){
			arr[i]=arr[0]+mmin*n;
			break;
		}
		--arr[i];
		++arr[0];
	}
	for(register int i=1;i<=n;++i) printf("%lld ",arr[i]);
	return 0;
}

```

欢迎来[我的blog](https://www.luogu.com.cn/blog/138812/#)看看

---

