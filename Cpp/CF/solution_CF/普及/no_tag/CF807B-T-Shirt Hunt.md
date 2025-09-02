# T-Shirt Hunt

## 题目描述

Not so long ago the Codecraft-17 contest was held on Codeforces. The top 25 participants, and additionally random 25 participants out of those who got into top 500, will receive a Codeforces T-shirt.

Unfortunately, you didn't manage to get into top 25, but you got into top 500, taking place $ p $ .

Now the elimination round of 8VC Venture Cup 2017 is being held. It has been announced that the Codecraft-17 T-shirt winners will be chosen as follows. Let $ s $ be the number of points of the winner of the elimination round of 8VC Venture Cup 2017. Then the following pseudocode will be executed:

`<br></br>i := (s div 50) mod 475<br></br>repeat 25 times:<br></br>    i := (i * 96 + 42) mod 475<br></br>    print (26 + i)<br></br>`Here "div" is the integer division operator, "mod" is the modulo (the remainder of division) operator.

As the result of pseudocode execution, 25 integers between 26 and 500, inclusive, will be printed. These will be the numbers of places of the participants who get the Codecraft-17 T-shirts. It is guaranteed that the 25 printed integers will be pairwise distinct for any value of $ s $ .

You're in the lead of the elimination round of 8VC Venture Cup 2017, having $ x $ points. You believe that having at least $ y $ points in the current round will be enough for victory.

To change your final score, you can make any number of successful and unsuccessful hacks. A successful hack brings you 100 points, an unsuccessful one takes 50 points from you. It's difficult to do successful hacks, though.

You want to win the current round and, at the same time, ensure getting a Codecraft-17 T-shirt. What is the smallest number of successful hacks you have to do to achieve that?

## 说明/提示

In the first example, there is no need to do any hacks since 10880 points already bring the T-shirt to the 239-th place of Codecraft-17 (that is, you). In this case, according to the pseudocode, the T-shirts will be given to the participants at the following places:

`<br></br>475 422 84 411 453 210 157 294 146 188 420 367 29 356 398 155 102 239 91 133 365 312 449 301 343<br></br>`In the second example, you have to do two successful and one unsuccessful hack to make your score equal to 7408.

In the third example, you need to do as many as 24 successful hacks to make your score equal to 10400.

In the fourth example, it's sufficient to do 6 unsuccessful hacks (and no successful ones) to make your score equal to 6500, which is just enough for winning the current round and also getting the T-shirt.

## 样例 #1

### 输入

```
239 10880 9889
```

### 输出

```
0
```

## 样例 #2

### 输入

```
26 7258 6123
```

### 输出

```
2
```

## 样例 #3

### 输入

```
493 8000 8000
```

### 输出

```
24
```

## 样例 #4

### 输入

```
101 6800 6500
```

### 输出

```
0
```

## 样例 #5

### 输入

```
329 19913 19900
```

### 输出

```
8
```

# 题解

## 作者：封禁用户 (赞：4)

# CF807B T-Shirt Hunt 题解

## 题目简述
你可以将现有的 $x$ 增加 $100$ 或者减少 $50$，求最少增加几次 $100$ 可以使得 $y \le x$ 且伪代码生成的序列中包含 $p$。

## 解题思路
这道题使用的是类似伪随机数生成，所以我们可以直接模拟生成过程。

我们先找到不一定 `伪代码生成的序列中包含 p` 成立，但确保 ` y ≤ x ` 成立的最小 $x$ 值：

因为每一次增减只能增加 $100$ 或者减少 $50$，所以可能的 $x$ 与 $x'$ 的差一定是 $50$ 的倍数。
- 在 $x > y$ 时让 $x$ 一直减少 $50$。
- 在 $x < y$ 时让 $x$ 一直增加 $50$。

然后依次加 $50$，模拟生成，然后判断是否 `伪代码生成的序列中包含 p` 成立。

找出成立的 $x$ 再计算需要加至少几次 $100$ 就行了。

计算至少加几次 $100$ 可以用一个简单的贪心：

- 如果 $x' = \text{目标}$：则不需要计算；
- 如果 $x' > \text{目标}$：则 $x' - 50$；
- 如果 $x' < \text{目标}$：则 $x' + 100$；

思路很简单，纯暴力就行了。

## 参考代码
```
#include<bits\stdc++.h>
using namespace std;
int a[30] , p , x , y , ans = 0 , now;
void prize(int s)//生成此时的得奖名次 
{
	int tmp = (s / 50) % 475;
	for(int i = 0 ; i < 25 ; i++)
	{
		tmp = (tmp * 96 + 42) % 475;
		a[i] = tmp + 26;
	}
	sort(a , a + 25);
	return; 
}
bool search()//查找名次在不在序列中 
{
	int l = 0 , r = 24 , mid;//二分优化复杂度 
	while(l <= r)
	{
		mid = (l + r) / 2;
		if(a[mid] == p)
		{
			return true;
		}
		if(a[mid] > p)
		{
			r = mid - 1;
			continue;
		}
		l = mid + 1;
	}
	return false;
}
int main()
{
	cin >> p >> x >> y;
	now = x;
	while(x >= y)//找到最小可能值
	{
		x -= 50; 
	}
	while(x < y)//覆盖掉 y > x的情况 
	{
		x += 50;
	}
	while(1)
	{
		prize(x);//从小至大逐一枚举 
		if(search())
		{
			break;
		}
		x += 50;
	}
	while(now < x)
	{
		ans++;//检验需要加几次100 
		now += 100;
	}
	cout << ans;//完结撒花 
	return 0;
}
```

---

## 作者：huangjunhan (赞：0)

# 题目大意
告诉你在一个比赛中的排名、你的当前分数和你想要赢得当前回合所需要的最小分数。
在每次操作中，你可以将现有的分数增加 $100$ 或者减少 $50$，求最少操作几次就可以使得能够赢得比赛且获得 Codecraft-17 T恤。

# 解题思路
1. 我们先找出符合题目要求的最小的 $x'$。

2. 直接模拟题目中的操作来生成序列，在生成的序列中用二分查找，看在序列中是否包含 $p$。

3. 计算 $x$ 最少加几个 $100$ 才能成为 $x'$。

明确了这些步骤，接下来直接模拟即可。
# AC code

```
#include<bits\stdc++.h>
using namespace std;
int p,x,y,t,l,r,mid,sum,ans,a[10010];
void f(int s){//题目中的伪代码
	sum=(s/50)%475;
	for(int i=1;i<=25;i++){
		sum=(sum*96+42)%475;
		a[i]=sum+26;
	}
	sort(a+1,a+26);
	return; 
}
bool find(){//二分查找
	l=1,r=25;
	while(l<=r){
		mid=(l+r)/2;
		if(a[mid]==p)return 1;
		else if(a[mid]>p){
			r=mid-1;
			continue;
		}
		else l=mid+1;
	}
	return 0;
}
int main(){
	cin>>p>>x>>y;
	t=x;
	while(x>=y)x-=50; 
	while(x<y)x+=50;
	while(1){
		f(x);
		if(find())break;
		x+=50;
	}
	while(t<x){
		ans++;
		t+=100;
	}
	cout<<ans;
}
```

---

