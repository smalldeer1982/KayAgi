# Doors Breaking and Repairing

## 题目描述

You are policeman and you are playing a game with Slavik. The game is turn-based and each turn consists of two phases. During the first phase you make your move and during the second phase Slavik makes his move.

There are $ n $ doors, the $ i $ -th door initially has durability equal to $ a_i $ .

During your move you can try to break one of the doors. If you choose door $ i $ and its current durability is $ b_i $ then you reduce its durability to $ max(0, b_i - x) $ (the value $ x $ is given).

During Slavik's move he tries to repair one of the doors. If he chooses door $ i $ and its current durability is $ b_i $ then he increases its durability to $ b_i + y $ (the value $ y $ is given). Slavik cannot repair doors with current durability equal to $ 0 $ .

The game lasts $ 10^{100} $ turns. If some player cannot make his move then he has to skip it.

Your goal is to maximize the number of doors with durability equal to $ 0 $ at the end of the game. You can assume that Slavik wants to minimize the number of such doors. What is the number of such doors in the end if you both play optimally?

## 说明/提示

Clarifications about the optimal strategy will be ignored.

## 样例 #1

### 输入

```
6 3 2
2 3 1 3 4 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 3 3
1 2 4 2 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 5 6
1 2 6 10 3
```

### 输出

```
2
```

# 题解

## 作者：qqvq (赞：4)

[骗访问量](https://www.cnblogs.com/storz/p/10254127.html)

C.Doors Breaking and Repairing

题意：有n个门以及他们的血量，A的能力值x和B的能力值y，和无限个回合，每回合先由A选择一个门进行攻击，选择的门血量减少x，然后由B选择一个门进行加固,血量增加y（一个门的血量$\leq 0$以后他就不能被加固了，但即使一扇门没有被攻击过，也可以加固）

问最后A最多能打破多少扇门


如果 $x > y$，所有门的总血量每回合都会减少，经过无限个回合，所有的门一定都会被打破。

否则就是 $x \leq y$ 的情况，发现那些血量 $> x$ 的门A永远打不破，因为A打一下，B就可以加固那扇门，血量 $\leq x$ 的门，A打破一扇，B就加固一扇门，A只能打破一半（A先手，要上取整）

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x, y;
  cin >> n >> x >> y;
  if (x > y) return cout << n, 0;
  int cnt = 0;
  for (int i = 1; i <= n; ++i) cin >> y, cnt += y <= x;
  cout << (cnt + 1) / 2 << endl;
  return 0;
}
```

---

## 作者：甄黫陻堙 (赞：3)

此题可分为两种情况也

## 一. x>y 此时ans为n
因为此时砸的力量大于修的，所以说最后可以把所有的门砸坏
## 二. x<=y 
此时不可把所有的门砸坏，所以就要运用到博弈论的思想

从小到大排序一遍，设甲为砸的，乙为修的

甲策略：砸最小的
乙策略：修次小的

这样双方就采用了最优策略

代码如下↓

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,x,y;
long long w[200],ans;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++){
		scanf("%lld",&w[i]);
	}
	if(x>y){//一
		printf("%d",n);
		return 0;
	}
	if(x<=y){//二
		sort(w+1,w+n+1);
		for(int i=1;i<=n;i++){
			if(w[i]<=x){//从最小开始砸
				ans++;
				w[i+1]+=y;//从次小开始修
			}
		}
		printf("%lld",ans);
	}
	return 0;
}

```

蒟蒻第一次发题解，若有问题请指出

---

## 作者：xyf007 (赞：1)

### 1.如果$x>y$，显然能拆完
### 2.否则，只能拆$a_i \leq x$（一次性拆完）的，不然对手给它$+y$，你就拆不掉了。
### 3.所以只需统计$a_i \leq x$的$sum$，答案是$(sum+1)/2$
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,x,y,a[101];
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	if(x>y)
	{
		printf("%d",n);
		return 0;
	}
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]<=x)
		{
			sum++;
		}
	}
	printf("%d",(sum+1)/2);
	return 0;
}
```

---

## 作者：floatery (赞：1)

本题目无需高精（$10^{100}$是吓唬你的）

假如$x<y$，那么所有门的总高度在无限轮中必然减小为0，所以输出n。

假如$x>=y$，那么摧毁门的人首先摧毁自己能一下摧毁的门（要不然就再也没有办法摧毁了），这样可以保证摧毁的门最多。而保护门的人会首先保护最容易被摧毁的门，这样可以保护更多的门。本题是一道策略题，理解策略就不难了。

本题存在恶意评分嫌疑

```cpp
#include <stdio.h>
int a[101];
int main()
{
	int n,x,y,cnt=0;
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]<=x)
		{
			cnt++;
		}
	}
	if(x>y)
	{
		printf("%d\n",n);
	}
	else
	{
		printf("%d\n",(cnt+1)/2);
	}
	return 0;
}
```

---

## 作者：HCl_Frog (赞：0)

###  这题有点水啊！
分两种情况：

1.$x$ < $y$: 全部都可以被打破，输出$n$即可。

2.$x$ >= $y$: 能一次性打破的打破一个对方修一个，因为是你先，所以是 ceil(可打破的 / 2)

代码：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main(){
	int n, x, y;
	cin >> n >> x >> y;
	int k[n];
	for(int i = 0; i < n; i++){
		cin >> k[i];
	}
    int cnt = 0;
	if(x > y){
		cout << n << endl;
		return 0;
	}else{
		for(int i = 0; i < n; i++){
			if(k[i] <= x){
				cnt++;
			}
		}
		cout << ceil(cnt / 2.0) << endl; 
		return 0;
	}
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

看着题面吓死人的，什么1e100局，其实很简单  
对于 拆>修，所有门都能拆除  
其他情况，只需统计可以一次拆掉(耐久<=拆)的门的个数，除2向上取整就是答案
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 5e3 + 10, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
	long long read()
	{
		rg long long num = 0;
		rg char ch;
		rg bool flag = false;
		while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
		if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
		while ((ch = getchar()) >= '0'&&ch <= '9')
			num = (num << 1) + (num << 3) + (ch ^ 48);
		if (flag)return -num; return num;
	}
	ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int ans;

int main()
{
	rg int n = fast_IO::read(), x = fast_IO::read(), y = fast_IO::read();
	if (x > y) { fast_IO::write(n); return 0; }
	for (rg int i = 1; i <= n; ++i)if (fast_IO::read() <= x)++ans;
	fast_IO::write(ans + 1 >> 1);
	return 0;
}
```

---

