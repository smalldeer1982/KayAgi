# Gabriel and Caterpillar

## 题目描述

The $ 9 $ -th grade student Gabriel noticed a caterpillar on a tree when walking around in a forest after the classes. The caterpillar was on the height $ h_{1} $ cm from the ground. On the height $ h_{2} $ cm ( $ h_{2}&gt;h_{1} $ ) on the same tree hung an apple and the caterpillar was crawling to the apple.

Gabriel is interested when the caterpillar gets the apple. He noted that the caterpillar goes up by $ a $ cm per hour by day and slips down by $ b $ cm per hour by night.

In how many days Gabriel should return to the forest to see the caterpillar get the apple. You can consider that the day starts at $ 10 $ am and finishes at $ 10 $ pm. Gabriel's classes finish at $ 2 $ pm. You can consider that Gabriel noticed the caterpillar just after the classes at $ 2 $ pm.

Note that the forest is magic so the caterpillar can slip down under the ground and then lift to the apple.

## 说明/提示

In the first example at $ 10 $ pm of the first day the caterpillar gets the height $ 26 $ . At $ 10 $ am of the next day it slips down to the height $ 14 $ . And finally at $ 6 $ pm of the same day the caterpillar gets the apple.

Note that in the last example the caterpillar was slipping down under the ground and getting the apple on the next day.

## 样例 #1

### 输入

```
10 30
2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 13
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10 19
1 2
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
1 50
5 4
```

### 输出

```
1
```

# 题解

## 作者：欢黎明陌 (赞：8)

这是我的第一篇题解。

第三遍提交本题的题解，对此题解改了几改，望管理通过，管理大大辛苦了。

这是一道可以直接模拟就做出来的题，先看题目；虽然题目中没给输入输出的翻译，但是我们仍然能看出要求输入的值（需要英语基础呀）。

第一行输入初始高度 $h1$ 和终点高度 $h2$。

第二行是昼、夜的虫虫位移速度 $a$ 和 $b$
（这样好的题且做且珍惜吧）。

求的是虫子到达终点的时间 $t$ 。

值得我们注意的是，虫子到达终点就不会在下降。

**粘过来代码如下：**

```cpp
#include <iostream>
#define elif else if	//Python后遗症 
#define int long long	//毕竟是一道蓝题，开个long long吧 
using std::cin;		//建议这样使用，避免定义变量和其他iostream库里的指令装车 
using std::cout;
using std::endl;
signed main()		//备注：用“signed”是为了避免int被long long替换（ 其实头文件不用define用typedef也行） 
{
	int start , end;//定义变量虫虫的出发点和终点 
	int a , b ;	//定义昼夜移动的速度 
	int ans = 1;  	//定义输出，即天数，初始化为1（想一想这是为什么呢） 
	
	cin >> start >> end;//按照题意输入 
	cin >> a  >> b ;
	
	if ( start + a * 8 < end && a <= b ){
		cout << -1 << endl;
		return 0;
	}
	//如果第一天爬不上去，而且上升比下降的少，那就永远上不去了。 
	
	elif(start + 8 * a >= end ){	//其实这个else if和直接if没有什么区别 
		cout << 0 << endl;
		return 0;
	}
	//主人公第一天是14点时去观测虫虫，如果当天22点之前虫虫爬到终点就直接输出0

	start += 8 * a ;		//第一天的判断结束，直接为第二天及其之后做准备 
	start -= 12 * b ;
	
	start += 12 * a;		//第二天的白天这是 
	//如果到达终点，下面的for就不会循环，直接输出2 
	for(;start < end;start+=12*a){	//循环，直到到达终点为止 
		start -= 12 * b;//晚上下滑 
		ans ++;			//最重要的一句千万别忘了（因为这句要输出） 
	}
	cout << ans << endl;		//习惯性换行 
	return 0;			//完美结束 
}
```

该代码已经过测试，可以 AC。

~~说实话我是很希望在 NOIP 的时候遇到类似的题的~~（快跑）。

求管理大大通过。

最后，祝大家 RP++。

---

## 作者：Dodee34 (赞：3)

这是一道比较有思维性的模拟题。
### 思路
这道题的关键就在于特判输出 $-1$ 的情况。特判后，我们就可以一直模拟毛毛虫爬树的过程，是白天就上升，晚上就下降，最后输出天数。
### 特判条件
首先，如果每时上升的厘米数要比每时下降的厘米数低，而且第一天爬不上去，那就一定不可能爬到重点了。

特判代码如下：
```cpp
if(a <= b && (h2 - h1) > a * 8)//即特判条件
{
	cout << -1;
	return 0;//赶快结束
}
```
### 模拟过程
模拟过程就很简单了，直接用循环依次模拟就行了。废话不多说，我们直接看看代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll h1, h2, a, b;
	cin >> h1 >> h2 >> a >> b;
	if(a <= b && (h2 - h1) > a * 8)//就是刚刚说过的特判条件，这里就不再说了
	{
		cout << -1;
		return 0;
	}
	ll  i = h1, t = 14;//$i$ 表示当前毛毛虫所在的高度，而 $t$ 表示毛毛虫需要多少小时爬到终点
	while(i < h2)//这说明毛毛虫还没有从 $h1$ 爬到 $h2$
	{
		ll tt = t % 24;//这里就是计算当时是几时，因为 $t$ 的含义是毛毛虫需要多少小时才能爬到终点，注意是小时。
		if(tt >= 10 && tt < 22)//如果在题目规定的白天
		{
			i += a;//那么，毛毛虫就多爬 $a$ 厘米。
		}
		else//如果在晚上
		{
			i -= b;//同理，毛毛虫就退 $b$ 厘米。
		}
		++t;//每小时过去，计数器累加
	}
	cout << t / 24;//因为 $t$ 是小时数，所以求天数就需要除以 $24$
	return 0;//谢幕
}
```

---

## 作者：Micnation_AFO (赞：3)

- [原题面](https://www.luogu.com.cn/problem/CF652A)
- [更好的阅读体验](https://oierbbs.fun/d/453-cf652a-gabriel-and-caterpillar) 

------------

本题只需要简单地分三种情况讨论即可：
1. 输出 $-1$ 的情况，即永远无法到达（只需判断 $a$ 是否小于等于 $b$ 并且一开始的 $8$ 个小时无法爬到 $h_2$ 即可）。
1. 输出 $0$ 的情况，即不管你的速度怎么样，只要一开始的 $8$ 个小时能吃到苹果就输出 $0$（只需判断 $h_1$ 加上 $8$ 个小时的路程之和与 $h_2$ 的关系即可）。
1. 输出大于 $0$ 的情况，即当上述条件均不满足时，一天一天地模拟直到 $h_1$ 比 $h_2$ 大（用`while`循环模拟简单即可）。

综上，可以直接写出简单的模拟代码（所以这题为什么要评蓝啊？）

$\texttt{AC Code}$：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
int h1, h2;
int a, b, ans;

signed main() {
    cin >> h1 >> h2;
    cin >> a >> b;
    if (a <= b && h1 + a * 8 < h2) cout << -1 << endl;
    else if (h1 + a * 8 >= h2) cout << 0 << endl;
    else {
        h1 += a * 8;
        while (h1 < h2) {
            h1 -= b * 12;
            ans++;
            h1 += a * 12;
        }
        cout << ans << endl;
    }
    return 0;
} 

```

---

## 作者：Novice233 (赞：2)

这道题标着tg+，其实也就pj的难度，主要是需要思考周全一些。

首先 Gabriel第一天是在14点去看的 所以要先判断到22点的过程中，毛毛虫有没有可能爬到h2。如果可以 直接输出0，否则就掉12*b(注意，ans要加上1！）

然后，每次先在h1上加上12*a，判断能否到h2，行就输出ans,不行就减去12*b,且ans++;

最后说下判断-1的条件。如果a<=b(爬的要比掉的慢或一样快），看看是否可能h1+8*a大于等于h2，能的话就输出0，否则就输出-1。

附上一份蒟蒻的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int h1,h2,a,b,ans;
int main(){
	cin>>h1>>h2;
	cin>>a>>b;
	if(a<=b&&h1+a*8<h2){
		cout<<-1;
		return 0;
	}
	if(h1+8*a>=h2){
		cout<<0;
		return 0;
	}
	h1+=8*a;
	h1-=12*b;
	ans++;
	while(h1<h2){
		h1+=12*a;
		if(h1>=h2){
			cout<<ans;
			return 0;
		}
		h1-=12*b;
		ans++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Dark_Sky (赞：1)

理清楚关系的话典型的模拟，注意的点一个是如果下降高度比爬高度还多，则直接判断第一天是否能到达目的地，不能则-1，之后的情况直接判断毛毛虫是否在下午两点以后到达即可。

上代码：

```cpp
#include<iostream>

using namespace std;

int h1,h2,a,b;

int main(){
	cin>>h1>>h2>>a>>b;
	if(a <= b){
		if (h1+8*a < h2){
			puts("-1");
			return 0;
		}
	}
	if(h1+8*a >= h2) {
		puts("0");
		return 0;
	}
	int h = h2-h1-8*a;
	int d = (a-b)*12;
	int ans = h/d;
	if(h%d){ 
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：BlackPanda (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF652A)

------------
### 题意：
有一只毛毛虫，从高度为 $h1$ 的地方爬到高度为 $h2$ 的地方。它在白天每小时上升 $a$ 厘米，晚上每小时下掉 $b$ 厘米。问到第几天的下午 $2$ 点及以前，毛毛虫能到达 $h2$。

------------
### 思路：
这道题就是简单的分类讨论，有以下几种情况：

- 永远无法到达，即下降速度大于等于上升速度并且在第一天白天无法爬到终点，输出 $-1$。
#### code:

```cpp
	if(a<=b && h1+a*8<h2){
		cout<<-1<<endl;
	}
```

- 在第一天白天就可以到达，不用判断晚上，输出 $0$。
#### code:

```cpp
	else if(h1+8*a >= h2){
		cout<<0<<endl;
	} 
```


- 直接模拟每天的情况，直到到达 $h2$ 为止，最后输出爬的天数即可。

#### code:
```cpp
	else{
		long long day=1;
		h1+=a*8-12*b+12*a;
		while(h1<h2){
			h1+=a*12;
			h1-=b*12;
			day++;
		} 
		cout<<day<<endl;
	}
```


---

## 作者：Vscsong (赞：0)

**[CF652A Gabriel and Caterpillar](https://www.luogu.com.cn/problem/CF652A)**

简单的分类讨论，**注意要特判第一天的多种情况**，防止第一天能到达但程序却输出`-1`。再判断一下爬的速度是否比掉的速度快，如果是，则输出`-1`，否则循环模拟爬的过程求解即可。


模拟代码：
```cpp
h1 += clime * 8;
while (h1 < h2) 
    h1 -= down * 12, h1 += clime * 12, ans++;
```

---

## 作者：wzmzmhk (赞：0)

写这题的题解主要是希望管理改一下评分，建议评红或橙而非蓝。

简单的分类讨论，注意一下细节即可：
1. 当第一天无法到达且 $h1$ 比 $h2$ 小时，输出 $-1$。
1. 当第一天可以到达时，输出 $0$。
1. 剩下的情况都要一天一天地模拟爬树的过程。


由于前两种情况过于简单，这里只给出第三种情况的核心代码：
```cpp
h1 += a * 8;
while (h1 < h2) {
    h1 -= b * 12;
    ans++;
    h1 += a * 12;
}
cout << ans << endl;

```

---

## 作者：Fearliciz (赞：0)

一道模拟题。

#### 解题思路：

要判断以下情况：

+ 在头一天 $14$ 时看到毛毛虫吃苹果，则输出 $0$。

+ 如果晚上掉的比白天爬的还多，则永远也不可能，输出 $-1$。

+ 如果爬的和掉的一样多，在头一天到不了苹果位置的情况下输出 $-1$。

注意：如果正好在头一天的 $14$ 时看到毛毛虫在吃苹果，则输出 $0$，而不是输出 $1$，我被这个点坑了好久（题目中没有涉及）。

这是我的第一遍代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int h1,h2,a,b,ans=0;
	cin>>h1>>h2>>a>>b;
	int tmp=h2-h1;
	if(tmp<a*8){
		cout<<"0";
		return 0;
	}else if(tmp==a*8){
		cout<<"1";
		return 0;
	}else if(b>a){
		cout<<"-1";
		return 0;
	}else{
		while(1){
			tmp-=a;
			if(tmp<=0) { cout<<ans;return 0;}
			tmp+=a;
			ans++;
		}
	}
	return 0;
}
```

可是却发现什么都不输出。

检查了以下后，改了一遍：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int h1,h2,a,b,ans=0;
	cin>>h1>>h2>>a>>b;
	int tmp=h2-h1;
	if(tmp<=a*8){
		cout<<"0";
		return 0;
	}else if(b>a){
		cout<<"-1";
		return 0;
	}
	ans=(tmp-(a*8))/((a*12)-(b*12));
	if((tmp-(a*8))%((a*12)-(b*12))!=0) ans++;
	cout<<ans;
	return 0;
}
```

可是这个代码也有问题提交进去第 $10$ 个点 $\texttt{RE}$ 了，而我也没有开数组，所以我觉得我是除 $0$ 或求余 $0$ 了。

所以我又加了一个判重：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int h1,h2,a,b,ans=0;
	cin>>h1>>h2>>a>>b;
	int tmp=h2-h1;
	if(tmp<=a*8){
		cout<<"0";
		return 0;
	}else if(b>a){
		cout<<"-1";
		return 0;
	}
	if((a*12)-(b*12)!=0){
		ans=(tmp-(a*8))/((a*12)-(b*12));
		if((tmp-(a*8))%((a*12)-(b*12))!=0) ans++;
		cout<<ans;
		return 0;
	}else{
		cout<<"-1";
		return 0;
	}
	return 0;
}
```

这样就可以 $\texttt{AC}$ 了。

---

## 作者：斜揽残箫 (赞：0)

## Description

有一只毛毛虫，白天每小时上升 $a$ 米，晚上每小时下降 $b$ 米，给定高度 $h_1,h_2$，问到第几天的下午 2 点及之前，能够从 $h_1$ 到达 $h_2$，特别的，如果到达 $h_2$ 就不会下降了。

$1 \leq h_1 \leq h_2 \leq 10 ^ 5,1 \leq a,b \leq 10 ^ 5$。

## Solution

很显然这就是个模拟题，只要注意细节即可。

+ 加百利是在下课后看到的，所以现在是 14 点。
+ 每次加上白天向上爬的后要判断是否可以退出。
+ 因为每次白天的时候是今天的 8 小时和明天的 4 小时，所以初始时要把计数器赋值为 1。

~~之后就没啥了。~~

代码中有详细注释。

## Code

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int h1,h2,a,b,ans = 1;
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
signed main()
{
  cin >> h1 >> h2 >> a >> b;//输入 h1,h2,a,b 同题目一样 
  if(b >= a) {//如果每天上升的高度小于下降的高度 
    if(a * 8 + h1 >= h2) {//如果第一天夜晚没降临之前到达，输出 0  
      cout << 0 << endl;
    }
    else cout << -1 << endl;//否则以后永远也不可能到达 
    return 0;
  }
  h1 += 8 * a;//加上第一天增加的 
  if(h1 >= h2) {//如果到达直接退出 
    cout << 0 << endl;
    return 0;
  }
  h1 -= 12 * b;//第一天夜晚减少的 
  while(h1 < h2) {//不断循环直到到达 
    h1 += 12 * a;
    if(h1 >= h2) break;//如果白天走到了就可以不用掉了 
    h1 -= 12 * b;
    ans ++;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：PersistentLife (赞：0)

如果 $\LaTeX$ 炸了的话请在我的[博客](https://www.luogu.com.cn/blog/302837/solution-cf652a)里面查看。

其实，这题实现起来细节是挺多的。

首先，因为他是下课后看到的，所以第一天只爬了 $8$ 小时，但是掉了 $12$ 小时，所以我们处理这一块的代码可以这样写，记得答案加一哦！

```cpp
h1=h1+8*a-12*b;
ans++;
```

然后，我们发现，当 $a \le b$ 时是有可能爬上去的，比如说$h_1=10,h_2=20,a=5,b=100$，此时是可以爬上去的，也就是说，$h_2 \le h_1+a \times 8 $，那么输出 $0$ 即可。

如果 $a \le b$ 且第一天的 $8$ 小时爬不上去的话，那么毛毛虫就永远不会爬上去。

我们处理这一部分的代码可以这样写：

```cpp
if(a<=b&&h1+a*8<h2) cout<<-1;
else if(h1+8*a>=h2) cout<<0;
```

接下来就是模拟爬的过程啦，因为 $a \le b \le 10^5$ 且每一次虫子都会往上爬，所以最坏的复杂度是 $\Theta(10^5)$，故可以不用数学计算的方法，上代码！

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int h1,h2,a,b,ans=0;
    cin>>h1>>h2>>a>>b;
    if(a<=b&&h1+a*8<h2) cout<<-1;
    else if(h1+8*a>=h2) cout<<0;
    else
    {
        h1=h1+8*a-12*b;
        ans++;
        while(h1<h2)
        {
            h1+=12*a;//往上爬
            if(h1>=12)//爬到了就结束
            {
                cout<<ans;
                break;
            }
            h1-=12*b;//往下滑
            ans++;//答案加一
        }
    }
    return 0;
}
```

---

