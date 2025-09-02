# Perfect Pair

## 题目描述

Let us call a pair of integer numbers  $ m $ -perfect, if at least one number in the pair is greater than or equal to $ m $ . Thus, the pairs (3, 3) and (0, 2) are 2-perfect while the pair (-1, 1) is not.

Two integers $ x $ , $ y $ are written on the blackboard. It is allowed to erase one of them and replace it with the sum of the numbers, $ (x+y) $ .

What is the minimum number of such operations one has to perform in order to make the given pair of integers $ m $ -perfect?

## 说明/提示

In the first sample the following sequence of operations is suitable: (1, 2) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (3, 2) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (5, 2).

In the second sample: (-1, 4) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (3, 4) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (7, 4) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (11, 4) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317A/355fee5161a1808ee95ea5dc6d815d4071657131.png) (15, 4).

Finally, in the third sample $ x $ , $ y $ cannot be made positive, hence there is no proper sequence of operations.

## 样例 #1

### 输入

```
1 2 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
-1 4 15
```

### 输出

```
4
```

## 样例 #3

### 输入

```
0 -1 5
```

### 输出

```
-1
```

# 题解

## 作者：Ggsddu_zzy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF317A)

#### 题目大意

给定一对数 $x$ 和 $y$，允许把其中的一个数换成 $x+y$，问把 $x$ 或  $y$ 变成大于或等于 $m$ 的数，需要几次操作。

#### 解题思路

- 首先可以判断 $x$ 或 $y$ 是否大于 $m$，如果是，就是不用进行任何操作就可以比 $m$ 大，所以可以直接输出 $0$；

- 然后在 $x$ 或 $y$ 是小于 $m$ 的情况下再判断 $x$ 和 $y$ 是否小于或等于零，如果是，那么 $x$ 与 $y$ 的和就永远不可能比 $x$ 或 $y$ 大，所以可以直接输出 $-1$；

- 如果以上情况都不是，可以判断一下 $x$ 或 $y$ 是否有负数，如果有，就一直加 $y$，把它变成正数；之后就可以一直让 $x$ 和 $y$ 之中小的数加上大的数，直到大于 $m$ 为止。

#### 代码

```cpp
#include<bits/stdc++.h>
#define GRET(code) exit(code)
#define ll long long
using namespace std;
ll x,y,m,ans=0;
void maxx(ll x,ll y,ll m){
	if(x>=m||y>=m){
		cout<<0;
		GRET(0);
	}
	else if(x<=0&&y<=0){
		cout<<-1;
		GRET(0);
	}
	else {
		if(x<0){
			ans+=(-x)/y;
			x+=y*((-x)/y);
		} 
		if(y<0){
			ans+=(-y)/x;
			y+=x*((-y)/x);
		}
	}
	while(x<m&&y<m){
		if(x<y) x+=y;
		else y+=x;
		ans++;
	}
}
int main(){
	cin>>x>>y>>m;
	maxx(x,y,m);	
	cout<<ans;
	return 0;
}
```

---

## 作者：hanyuchen2019 (赞：2)

一道简单模拟题，不过有亿点点坑。

### part 0

如果你 WA on #10：

$-10^{18}\le x,y,m\le10^{18}$。 十年OI一场空，不开 `long long` 见祖宗！

### part 1

思路已经很明显了，如果 $x\le y$，就把 $(x,y)$ 改变成 $(x+y,y)$。

一些特殊情况：

1. 如果什么事都没干就已经符合要求了，不考虑任何事，直接输出 $0$。

2. 如果 $x,y$ 皆为负数，且比 $m$ 要小，无论怎么加也无济于事，直接输出 $-1$ 。

### part 2

根据以上所述，我们可以~~快乐的~~写出代码：

```cpp
（头文件，初始化等略）
int main()
{
	cin>>x>>y>>m;
	if(x>=m||y>=m)//特判1
		cout<<0;
	else if(x<=0&&y<=0)//特判2
		cout<<-1;
	else
	{
		while(x<m&&y<m)
		{
			if(x>y)swap(x,y);//保持a比b小
			x+=y;
			ans++;
		}
		cout<<ans;
	}
	return 0;
}
```

[结果……](https://www.luogu.com.cn/record/50442227)光荣TLE。

我们来看看TLE的数据：

```
#10 Input:
-1000000000000000000 1 1000000000000000000
```

如果按照此方法，程序要执行 $10^{18}+87$ 次，~~不TLE才怪。~~

### part 3 改进

分析一下这组TLE数据，会发现把 $x$ 变成正数花费了大量时间（一直在把 $x+1$），因为在此过程中一直在做同样的事情，所以我们可以再加上一个优化（在 part 4 中已详细说明）。

### prat 4 AC代码

```cpp
#include<iostream>
#include<algroithm>
using namespace std;
int main()
{
	long long x,y,m,ans=0;
	cin>>x>>y>>m;
	if(x>=m||y>=m)
		cout<<0;
	else if(x<=0&&y<=0)
		cout<<-1;
	else 
	{
		if(x*y<0)//如果这两个数一正一负
		{
			if(x<y)//哪个是负数？
			{
				ans+=(-x)/y;//这个数要加几次
				x=x%y;//等价于 x+=y*((-x)/y)
			} 
		}
		ans+=(-y)/x;
		y=y%x;
	}
	while(x<m&&y<m)
	{
		if(x>y)swap(x,y);
		x+=y;
		ans++;
	}
	cout<<ans;
	return 0;
}
```
感谢您的观看，点个赞再走吧，bye~

---

## 作者：little_rubbish (赞：1)

## 思路
一道模拟题。

先特判，如果 $x$ 和 $y$ 本身就大于 $m$ ，就不用调了，直接输出零。
```cpp
if(x>=m||y>=m){
	cout<<0;
	return 0;
}
```
如果 $x$ 和 $y$ 都比 $m$ 小，且都小于等于零，再怎么加也无济于事，输出 $-1$ 。
```cpp
if(x<=0&&y<=0){
	cout<<-1;
	return 0;
}
```
如果二者都不是的话，依据题目进行枚举。

虽然在目前来说 $x+y$ 大数加小数与小数加大数没区别，可我们要选择小数加大数，这样可以使两个数整体的和加大。

举个例子：

一对数 $(x,y)$ ， $x = 1 , y = 5$ 。

当选择大数加小数时：

第一轮：

$x = 1 , y = 6$ $x$ ， 与 $y$ 的最大值为 $6$ 。

第二轮：

$x = 1 , y = 7$ $x$ ， 与 $y$ 的最大值为 $7$ 。

当选择小数加大数时：

第一轮：

$x = 6 , y = 5$ $x$ ， 与 $y$ 的最大值为 $6$ 。

第二轮：

$x = 6 , y = 11$ $x$ ， 与 $y$ 的最大值为 $11$ 。

通过例子不难看出小数加大数的值是较大的，所以我们要选择小数加大数。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std; 
ll x,y,m,ans;
int main(){
	cin>>x>>y>>m;
	if(x>=m||y>=m){
		cout<<0;
		return 0;
	}
	if(x<=0&&y<=0){
		cout<<-1;
		return 0;
	}
	while(max(x,y)<m){
		if(x>y){
			y+=x;
		}
		else x+=y;
		ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：引领天下 (赞：1)

讲道理，这个题其实真没什么好说的，就是直接模拟

基本思路很简单：每次挑小的换成和。

具体看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long llint;
llint x,y,m,ans;
int main(){
	cin>>x>>y>>m;
	if (x>=m||y>=m){
		puts("0");
		return 0;
	}//如果直接符合，直接输出
	if (x<=0&&y<=0){
		puts("-1");
		return 0;
	}//如果x、y都负，则不可能变成完美
	if (x>y)swap(x,y);//如果x比y大，换一下
	if (x<0){
		ans+=(-x)/y;
		x+=(-x)/y*y;
	}//如果有个负的，想办法把他弄成正的（方法：始终加y）
	while(x<m&&y<m){
		if (x>y) swap(x,y);
		x+=y;
		ans++;
	}//模拟
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF317A)

**简要题意：**

定义一对数 $(x,y)$，若 $x$，$y$ 中至少有一个大于等于 $m$，则称 $(x,y)$ 对 $m$ 完美。

现在给定一对数 $(x,y)$，允许把其中的一个数换成 $x+y$，问把 $(x,y)$ 变成对 $m$ 完美的数对至少需要几次操作，如无解，输出 $-1$。

**解题思路：**

首先需要两个特判：

- 如果 $x$ 和 $y$ 均小于 $m$ 且小于等于 $0$，那么无论怎么加都无法大于等于 $m$，直接输出 $-1$。

- 如果 $x$ 和 $y$ 本身就有至少一个数大于等于 $m$，那么不用加，直接输出 $0$。

此部分代码：

```cpp
if(x>=m || y>=m) {
	cout << 0 << endl;
	return 0;
}
if(x<=0 && y<=0) {//这里因为前面判断 x 或 y 大于等于 m 就 return 0,所以不用判断 x<m && y<m 
	cout << -1 << endl;
	return 0;
}
```

然后易知，两数相加应把大数加到小数上，举例：

样例 $2$：$x=-1$，$y=4$，如果把 $x$ 加到 $y$ 上，$y=-1+4=3$，不大反小，不可行。而如果把 $y$ 加到 $x$ 上，$x=-1+4=3$，将负数 $x$ 变成了正数，使操作次数减小。

样例 $1$：虽然 $x$ 与 $y$ 都是正数，但如果对 $y$ 进行操作，$y=1+2=3$，此时 $x+y=1+3=4$。如对 $x$ 进行操作，$x=1+2=3$，此时 $x+y=3+2=5$，$5>4$，所以对 $x$ 操作更优。

综上所述，易证进行操作时将大数加到小数上为更优解。

然后，`while` 循环，当 $max(x, y) < m$ 时，执行操作，将大数加到小数上，次数计数器加一。

最后输出次数计数器即可。

但是，注意数据范围：$-10^{18} \leq x, y, m \leq 10^{18}$，十年 OI 一场空，不开 `long long` 见祖宗！

**AC Code:**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	long long x, y, m, ans=0;
	cin >> x >> y >> m;
	if(x>=m || y>=m) {
		cout << 0 << endl;
		return 0;
	}
	if(x<=0 && y<=0) {//这里因为前面判断 x 或 y 大于等于 m 就 return 0,所以不用判断 x<m && y<m 
		cout << -1 << endl;
		return 0;
	}
	while(max(x, y)<m) {
		if(x<=y)
			x += y;
		else
			y += x;
		ans++; 
	}
	cout << ans << endl;
	return 0;
}
```

最后的最后，切勿抄袭，棕名两行泪！

---

