# Gourmet Cat

## 题目描述

Polycarp has a cat and his cat is a real gourmet! Dependent on a day of the week he eats certain type of food:

- on Mondays, Thursdays and Sundays he eats fish food;
- on Tuesdays and Saturdays he eats rabbit stew;
- on other days of week he eats chicken stake.

Polycarp plans to go on a trip and already packed his backpack. His backpack contains:

- $ a $ daily rations of fish food;
- $ b $ daily rations of rabbit stew;
- $ c $ daily rations of chicken stakes.

Polycarp has to choose such day of the week to start his trip that his cat can eat without additional food purchases as long as possible. Print the maximum number of days the cat can eat in a trip without additional food purchases, if Polycarp chooses the day of the week to start his trip optimally.

## 说明/提示

In the first example the best day for start of the trip is Sunday. In this case, during Sunday and Monday the cat will eat fish food, during Tuesday — rabbit stew and during Wednesday — chicken stake. So, after four days of the trip all food will be eaten.

In the second example Polycarp can start his trip in any day of the week. In any case there are food supplies only for one week in Polycarps backpack.

In the third example Polycarp can start his trip in any day, excluding Wednesday, Saturday and Sunday. In this case, the cat will eat three different dishes in three days. Nevertheless that after three days of a trip there will be $ 99 $ portions of rabbit stew in a backpack, can cannot eat anything in fourth day of a trip.

## 样例 #1

### 输入

```
2 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 2 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
1 100 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
30 20 10
```

### 输出

```
39
```

# 题解

## 作者：yeshubo_qwq (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF1154C)
## 题意
在每周的周一、周四、周日，猫咪会吃一条鱼，

在每周的周二、周六，猫咪会吃一份兔肉，

剩下的时间猫咪会吃一份鸡肉。

问：不限星期几出发，$a$ 条鱼，$b$ 份兔肉，$c$ 份鸡肉最多可以喂饱这只猫几天。
## 思路
这道题数据较大，直接模拟必定超时，所以我们需要利用周期优化。

我们可以先求出 $a$ 条鱼，$b$ 份兔肉，$c$ 份鸡肉可以喂饱猫咪几个周期（一个周期为一整周），减小模拟的数据量，然后枚举从星期几开始，并模拟还能吃几天，从而求出答案。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,A,B,C,i,j,ma;
int main(){
	cin>>a>>b>>c;
	d=min(a/3,min(b/2,c/2));//求出周期数 
	a-=d*3;b-=d*2;c-=d*2; 
	for(i=0;i<=6;i++){//枚举星期几出发，0表示星期日 
		A=a;B=b;C=c;j=i;
		while(1){
			if(j%7==1||j%7==4||j%7==0)A--; 
			else if(j%7==2||j%7==6)B--;
			else C--; 
			if(A<0||B<0||C<0)break;//不够吃退出循环 
			j++;//又吃了一天 
		}
		ma=max(ma,j-i);
	}
	cout<<ma+d*7;//最大值+周期*7即为所求答案 
	return 0;
}
```


---

## 作者：tbdsh (赞：1)

# 题意
[题目传送门](https://www.luogu.com.cn/problem/CF1154C)

[更好的阅读体验](https://www.luogu.com.cn/blog/tianbiandeshenghuo11/solution-cf1154c)

一只猫在一周中的**周一、周四、周日**吃鱼，**周二、周六**吃兔，**周三、周五**吃鸡 ~~（话说猫不是只吃鱼吗）~~。

现在 Polycarp 要带它去旅行，并且分别会带 $a,b,c(1\le a,b,c\le7\times10^8)$ 份鱼、兔、鸡肉。

求他带的食物最多可以喂这只猫几天。

# 分析
本题介绍两种方法。

## 暴力枚举（`TLE on test #5`）
直接暴力枚举周一至周日的每天用餐情况，最后记录即可。


但是很显然会超时。
### 核心代码
```cpp
for (int i = 1; i <= 7; i++){
    long long a = x, b = y, c = z, sum = i, qwq = 0;
    while(a && b && c){
      //这里省略吃食物的代码
      sum++;
      if (a >= 0 && b >= 0 && c >= 0){
        qwq++;
      }
    }
    if (qwq > cnt){
      cnt = qwq;
    }
  }
```
## 正解（`AC`）
因为它的食谱是固定的，那么我们只需要先预处理出相同的部分，再枚举一周的即可。

那么，他相同的部分是多少呢？

因为它每周的食谱相同，所以它可以吃三种食物所供应的周数的最小值，即 $r = \min(\dfrac{a}{3},\dfrac{b}{2},\dfrac{c}{2})$。

计算出之后，$a,b,c$ 需分别减去 $r\times3,r\times2,r\times2$。

之后再枚举一周的即可。

时间复杂度：$O(1)$。
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
long long x, y, z, cnt = -1;
int main(){
  cin >> x >> y >> z;
  for (int i = 1; i <= 7; i++){
    long long a = x, b = y, c = z, sum = i, qwq = 0;//重定义
    long long q = a / 3, p = b / 2, o = c / 2, r = min(min(q, p), o);//同上方相同的天数计算
    qwq += r * 7, a -= r * 3, b -= r * 2, c -= r * 2;//同上减去的过程
    while(a >= 0 && b >= 0 && c >= 0){
      if (sum % 7 == 1 || sum % 7 == 4 || sum % 7 == 0){
        a--;
      }else if (sum % 7 == 2 || sum % 7 == 6){
        b--;
      }else {
        c--;
      }//猫吃食物的代码
      sum++;
      qwq += a >= 0 && b >= 0 && c >= 0;
    }
    cnt = max(cnt, qwq);//计算最大值
  }
  cout << cnt;
  return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# [题面传送门](https://www.luogu.com.cn/problem/CF1154C)

## Description
Polycarp 有一只小猫，这只猫饮食上有如下规律：

在每周的周一、周四、周日，猫咪会吃一条鱼

在每周的周二、周六，猫咪会吃一份兔肉(兔兔这么可爱QAQ)

剩下的时间猫咪会吃一份鸡肉

现在 Polycarp 要带这猫出去旅行，他会带 $a$ 条鱼， $b$ 份兔肉，$c$ 份鸡肉。

加入他采取最优的策略来决定在一周的哪一天出发，请问他带的这些食物最多可以喂饱这只猫几天。

## Solution

  题目中说，Polycarp带 $a$ 条鱼， $b$ 份兔肉，$c$ 份鸡肉。
  
  周一，四，日小猫会吃一条鱼。
  
  周二，六小猫会吃一份兔肉。
  
  剩下的周三和五会吃一份鸡肉。
  
  所以，猫一周吃 $3$ 条鱼，$2$ 份兔肉，$2$ 份鸡肉。
  
  也就是说，猫可以吃 $\min( a/3 , b/2 , c/2 )$个整周。
  
  剩下的，暴力死做就行了。
  
##  AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,dd,aa,cc,bb,flag,rq,i,ma,ans;
int main(){
	scanf("%d%d%d",&a,&b,&c);//输入 
	aa=a/3;bb=b/2;cc=c/2;
	dd=min(aa,min(bb,cc));//dd代表整周数量 
	ans=dd*7;//一定可以吃完的 
	a-=dd*3;b-=dd*2;c-=dd*2;//剩下的 
	aa=a;bb=b;cc=c;//保存 
	for(i=0;i<=6;i++){//  暴力 
		rq=i;a=aa;b=bb;c=cc;flag=1;
		while(flag){//如果吃完了，退出 
			if(rq%7==0||rq%7==1||rq%7==4)a--;
			else if(rq%7==2||rq%7==6)b--;
			else c--;
			if(a<0||b<0||c<0){
				rq-=2;flag=0;// 因为后面还有rq++,所以-=2 
			}
			rq++;
		}
		ma=max(ma,rq-i+1);//求最大 
	}
	cout<<ans+ma;//愉快输出 
	return 0;//！！！完结撒花！！！ 
}

```


---

## 作者：一扶苏一 (赞：1)

[本场题解博客](https://www.cnblogs.com/yifusuyi/p/10727303.html)

# C

## Description

Polycarp 有一只小猫，这只猫饮食上有如下规律：

> 在每周的周一、周四、周日，猫咪会吃一条鱼
>
> 在每周的周二、周六，猫咪会吃一份兔肉(兔兔这么可爱QAQ)
>
> 剩下的时间猫咪会吃一份鸡肉

现在 Polycarp 要带这猫出去旅行，他会带 $a$ 条鱼， $b$ 份兔肉，$c$ 份鸡肉。

假如他采取最优的策略来决定在一周的哪一天出发，请问他带的这些食物最多可以喂饱这只猫几天。

## Limitation

$1~\leq~a,~b,~c~\leq~7~\times~10^8$

## Solution

考虑中间的整周，显然每周消耗 $3$ 条鱼，$2$ 份兔肉，$2$ 份鸡肉。于是整周的个数是 $\min(a/ 3,~b / 2,~c / 2)$

然后将整周去掉，考虑枚举从哪一天出发，然后向后枚举能喂几天。当一种食物减成负数则停止。考虑到把 $a,~b,~c$ 分别除掉整周消耗后，一定有一种食物是小于等于 $3$ 的。于是这样的枚举是常数级别的，可以通过。

## Code

```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif

typedef long long int ll;

namespace IPT {
  const int L = 1000000;
  char buf[L], *front=buf, *end=buf;
  char GetChar() {
    if (front == end) {
      end = buf + fread(front = buf, 1, L, stdin);
      if (front == end) return -1;
    }
    return *(front++);
  }
}

template <typename T>
inline void qr(T &x) {
  char ch = IPT::GetChar(), lst = ' ';
  while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
  while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
  if (lst == '-') x = -x;
}

namespace OPT {
  char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
  if (x < 0) {x = -x, putchar('-');}
  int top=0;
  do {OPT::buf[++top] = static_cast<char>(x % 10 + '0');} while (x /= 10);
  while (top) putchar(OPT::buf[top--]);
  if (pt) putchar(aft);
}

ll a, b, c, ans;

int main() {
  freopen("1.in", "r", stdin);
  qr(a); qr(b); qr(c);
  ans = std::min(a / 3, std::min(b / 2, c / 2));
  a -= 3 * ans; b -= ans << 1; c -= ans << 1;
  ans *= 7;
  ll tt = 0;
  for (int i = 1; i <= 7; ++i) {
    ll ta = a, tb = b, tc = c;
    ll ts = 0;
    int day = i;
    while (true) {
      if ((day == 1) || (day == 4) || (day == 7)) {
        if (ta-- == 0) break;
      } else if ((day == 2) || (day == 6)) {
        if (tb-- == 0) break;
      } else if (tc-- == 0) break;
      ++day; ++ts;
      if (day == 8) day = 1;
    }
    tt = std::max(tt, ts);
  }
  qw(ans + tt, '\n', true);
  return 0;
}
```

---

## 作者：xiangshengtao (赞：0)

## 题意
[Gourmet Cat](https://www.luogu.com.cn/problem/CF1154C)
## 思路
直接枚举星期并模拟肯定超时，所以我们可以用周期做。首先，枚举从星期几开始吃，将这一星期吃完，再用周期求出可以吃几星期，但有些食物吃完还有剩下的，最后再枚举剩下的还能吃几天，将可以吃的最多天数求个最大，就是答案。
## 程序
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,i,j,ans,x,ma,aa,bb,cc;
void eat(int x){//星期几吃什么
	switch(x){
		case 1:aa--;break;
		case 2:bb--;break;
		case 3:cc--;break;
		case 4:aa--;break;
		case 5:cc--;break;
		case 6:bb--;break;
		case 7:aa--;break;
	}
}
int main(){
	scanf("%d%d%d",&a,&b,&c);
	aa=a;bb=b;cc=c;//为了让它还原
	for (i=1;i<=7;i++){
		ans=0;
		for (j=i;j<=7;j++){//将这一星期吃完
			eat(j);
			if (aa<0||bb<0||cc<0) break;
			ans++;
		}
		x=min(aa/3,min(bb/2,cc/2));ans+=x*7;//x表示能吃几星期
		aa-=x*3;bb-=x*2;cc-=x*2;
		for (j=1;j<=7;j++){//剩下的还能吃几天
			eat(j);
			if (aa<0||bb<0||cc<0) break;
			ans++;
		}
		ma=max(ma,ans);//求最大
		aa=a;bb=b;cc=c;
	}
	printf("%d\n",ma);
	return 0;
}

```


---

## 作者：InversionShadow (赞：0)

### 题意：

在周一、周四、周日，猫会吃一条鱼，

在周二、周六，猫会吃一份兔肉，

剩下的时间猫会吃一份鸡肉。

不限星期几出发，有 $a$ 条鱼，$b$ 份兔肉，$c$ 份鸡肉最多可以喂饱这只猫几天。

### 思路：

我们可以先求出三个数供应猫多少周，即 $\min(\min(\dfrac{a}{3}, \dfrac{b}{2}), \dfrac{c}{2})$，然后再暴力枚举周一到周天判断那一天可以供应最多，记录一下连续天数，最后输出最大连续天数加上原先算出来的周数乘 $7$ 即可。

上 $AC$ 代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

long long a, b, c, sum, ans, o, a1, b1, c1, s, s1, s2;  // 注意开 long long

int main() {
  cin >> a >> b >> c;
  o = min(a / 3, min(b / 2, c / 2)); // 求最少周数
  a1 = a - o * 3;   // 过了 o 周后三样菜品各有多少
  b1 = b - o * 2;
  c1 = c - o * 2;
  for (long long i = 1; i <= 7; i++) {
    sum = 0; // 初始化
    s = a1;
    s1 = b1;
    s2 = c1;   // 临时变量
    for (int j = i; ; j = j % 7 + 1) {
      if (j == 1 || j == 4 || j == 7) { // 如果 j = 1 或者 j = 4 或者 j = 7, 表示吃鱼肉
        if (s > 0) {  // 如果还可以吃
          s--;     // 吃一次
        } else {     // 否则跳出，表示已经轮完
          break;
        }
      } else if (j == 2 || j == 6) { // 如果 j = 2 或者 j = 6, 表示吃兔肉
        if (s1 > 0) {   // 同上
          s1--;
        } else {
          break;
        }
      } else if (j == 3 || j == 5) { // = 3 或者  5, 表示吃鸡肉
        if (s2 > 0) {  // 同上
          s2--;
        } else {
          break;
        }
      }
      sum++;   // 记录步数
    }
    ans = max(sum, ans); // 求最大值
  }
  cout << ans + o * 7;  // 因为题目要求的单位为天，而 o 的单位为周。
  return 0;
}

```


---

## 作者：Drystynt (赞：0)

首先我们可以算出猫咪可以吃多少整周：$wholeweeks=\min{\{[\dfrac{a}{3}}],[\dfrac{b}{2}],[\dfrac{c}{2}]\}$

这是因为猫咪每周吃掉 $3$条鱼，$2$ 份兔肉，$2$ 份鸡肉的缘故。

【原题描述】

> 假若他采取最优的策略来决定在一周的哪一天出发，请问他带的这些食物最多可以喂饱这只猫几天。

只有$7$种情况，我们可以一一枚举。枚举导致code很长，但是枚举很大一部分是重复的，我们直接复制粘贴枚举的一部分再稍稍修改即可。

Code见下：

```cpp
#include <bits/stdc++.h>
#define elif else if
using namespace std;
int minn(int x,int y,int z)
{
	if(x<=y)if(x<=z)return x;else return z;
	elif(y>=z)	return z;else return y;
}
int maxn(int x,int y,int z)
{
	return max(x,max(y,z));
}
int main()
{
	int a,b,c;//a代表鱼，b代表兔，c代表鸡
	scanf("%d%d%d",&a,&b,&c);
	int ans=minn(a/3,b/2,c/2);//现在，ans代表可以喂饱多少整周。
	a=a-ans*3,b=b-ans*2,c=c-ans*2;
	int x=a,y=b,z=c;
	int d;
	for(d=1;d<=7;d++)
	{
		switch(d%7)
		{
			case 1:case 4:case 0:a--;break;
			case 2:case 6:b--;break;
			default:c--;break;//习惯加break了
		}
		if(a<0 || c<0 || b<0)	break;
	}int d1=d-1;a=x,b=y,c=z;//初始化
	for(d=2;d<=8;d++)
	{
		switch(d%7)
		{
			case 1:case 4:case 0:a--;break;
			case 2:case 6:b--;break;
			default:c--;break;//习惯加break了
		}
		if(a<0 || c<0 || b<0)	break;
	}int d2=d-2;a=x,b=y,c=z;
	for(d=3;d<=9;d++)
	{
		switch(d%7)
		{
			case 1:case 4:case 0:a--;break;
			case 2:case 6:b--;break;
			default:c--;break;//习惯加break了
		}
		if(a<0 || c<0 || b<0)	break;
	}int d3=d-3;a=x,b=y,c=z;
	for(d=4;d<=10;d++)
	{
		switch(d%7)
		{
			case 1:case 4:case 0:a--;break;
			case 2:case 6:b--;break;
			default:c--;break;//习惯加break了
		}
		if(a<0 || c<0 || b<0)	break;
	}int d4=d-4;a=x,b=y,c=z;
	for(d=5;d<=11;d++)
	{
		switch(d%7)
		{
			case 1:case 4:case 0:a--;break;
			case 2:case 6:b--;break;
			default:c--;break;//习惯加break了
		}
		if(a<0 || c<0 || b<0)	break;
	}int d5=d-5;a=x,b=y,c=z;
	for(d=6;d<=12;d++)
	{
		switch(d%7)
		{
			case 1:case 4:case 0:a--;break;
			case 2:case 6:b--;break;
			default:c--;break;//习惯加break了
		}
		if(a<0 || c<0 || b<0)	break;
	}int d6=d-6;a=x,b=y,c=z;
	for(d=7;d<=13;d++)
	{
		switch(d%7)
		{
			case 1:case 4:case 0:a--;break;
			case 2:case 6:b--;break;
			default:c--;break;//习惯加break了
		}
		if(a<0 || c<0 || b<0)	break;
	}int d7=d-7;a=x,b=y,c=z;
	d=maxn(maxn(d1,d2,d3),maxn(d4,d5,d6),d7);
	printf("%d\n",ans*7+d);
	return 0;
}
```

---

