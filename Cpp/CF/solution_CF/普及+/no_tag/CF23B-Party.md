# Party

## 题目描述

 $ n $ people came to a party. Then those, who had no friends among people at the party, left. Then those, who had exactly 1 friend among those who stayed, left as well. Then those, who had exactly $ 2,3,...,n-1 $ friends among those who stayed by the moment of their leaving, did the same.

What is the maximum amount of people that could stay at the party in the end?

## 样例 #1

### 输入

```
1
3
```

### 输出

```
1
```

# 题解

## 作者：C_Cong (赞：41)

[博客传送门](https://dgsyrc.github.io/2020/03/25/%E6%B4%9B%E8%B0%B7%E9%A2%98%E8%A7%A3%20CF23B%20%E3%80%90Party%E3%80%91/#more)

### 解题思路：

首先这一看就是数学题【应该让雾之湖的Cirno来做(这题明显就很⑨$^*$)】。

*:⑨就是baka的意思。

其次，题目要求你在这$n$个人中找到一种关系图使得剩下的人最多，输出剩下的人数。

题目所说的朋友个数是指在场的，走了的就要减去。

关系是相互的。

（题目翻译有点误导人，没说明白）

当然要先画图模拟找规律啦！

### 规律：

#### 一个人：

一个人就不画图了，明摆着当扫到0个朋友的人离开时他就要走。

#### 两个人：

同上，图可以脑补，因为只存在两种关系（要么两个人是朋友，要么不是）。

同样，没有人可以剩下。

#### 三个人：

咯，你们要的图：

![](https://s1.ax1x.com/2020/03/25/8vqNFS.png)

如图所设的关系：

当0个朋友的人要走时，没有人要走；

当1个朋友的人要走时，`2`、`3`要走；

当2个朋友的人要走时，没有人要走；（此时`1`的朋友个数为`0`，巧妙地绕过了扫描）

这样我们就剩下了1个人。

#### 四个人：

![](https://s1.ax1x.com/2020/03/25/8vL81J.png)

如图所设的关系：

当0个朋友的人要走时，没有人要走；

当1个朋友的人要走时，没有人要走；

当2个朋友的人要走时，`1`、`3`要走；

当3个朋友的人要走时，没有人要走；（此时`2`和`4`的朋友个数为`1`，巧妙地绕过了扫描）

这样我们就剩下了2个人。

#### n个人：

（4人以后的情况就不画了，占的版面太多）

根据上述方法继续推，不难发现剩下的人数总是$n-2$。

所以我们就有以下关系（设答案为$ans$）：

$$ ans= \begin{cases} 0, & 0 \leq n < 2 \\ n-2, & n \geq 2 \end{cases} $$

所以我们就有如下代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int T,n;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		(n<2)?printf("0\n"):printf("%d\n",n-2);//这里就不用解释了吧
	}
	return 0;
} 
```

有帮助留个赞，顶上去才能让更多人看到哦！

---

## 作者：xxzjbd (赞：18)

## 其实是一道数学题
看着dalao们又画图又递推，萌新没有很理解，于是自己随便找规律中找到了最优方案。

共有 $n$ 个人，如果他们两两认识呢？两两相连，总共有 $n$ * $($ $n$ $-$ $1$ $)$ $/$ $2$ 条边，这样每个人都会有 $n$ $-$ $1$ 个朋友，会一起离场。

那么删去一条边。此时有两个人的朋友数变成了 $n$ $-$ $2$ 个，会在其余 $n$ $-$ $2$ 个人之前离场，离场后每个人朋友数又变成了 $n$ $-$ $3$ 已经没有机会离场了，所以最优方案为剩下 $n$ $-$ $2$个人。

记得特判一下 $n$ $<$ $2$ 的情况。
## 代码如下
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		if(n<2)cout<<0<<endl;
		else cout<<n-2<<endl;
	}
	return 0;
}
```
## 谢谢观赏

---

## 作者：rayluo (赞：6)

### description :

- 多组输入。

- 每组输入一个 n，表示派对的人数，人与人之间有朋友关系，关系是相互的，关系由你自己定。

- 如果有人的朋友离开了，那么他的朋友数会减少，首先有0个朋友的人离开，然后在剩余的人中有1个朋友的人离开，以此类推，最后是剩余的人中有 $(n-1)$ 个朋友的人离开。

请你构造出一种关系网，使得最终剩余的人最多，输出最多的人数。

### solution :

首先通过理解题意，我们需要知道：**一个人假如要留下来，那么他的朋友中至少要离开一个** 。为什么，如果他的朋友一个都不离开，那么他的朋友数就不会变，不变的话就迟早会被 $0,1,2...,n-1$ 这样扫到。于是**我们需要牺牲尽量少的部分来保全剩下的** 。 并且**每一个牺牲的人的朋友数都要小于剩下的人的朋友数** ，不然剩下的人就会先离开。

如人数小于等于了2，无论怎么安排，都没法留人，直接输出0，这个自己试一下就知道了。

假如总共有 n 个人，我们牺牲一个人，为使剩下的人全部有可能留下，他需要与其他每一个人都为朋友，这样他就有 $(n-1)$ 个朋友，这样显然是不行的，因为一个人最多只有 $(n-1)$ 个朋友，其他人不可能比他再多了。

假如我们牺牲两个人，1和2。那么我们可以构造这样一种情况：1与 $3 \sim n$ 都为朋友，2与 $3 \sim n$ 也为朋友，$3 \sim n$ 之间互为朋友。

关系如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/7fmb47ed.png)

这样安排有什么好处呢，对于要牺牲的1和2，他们每人都有 $(n-2)$ 个朋友，而对于 $3 \sim n$ 中的每一个都有 $(n-1)$ 个朋友，当轮到 $(n-2)$ 个朋友的人离开时，1和2离开了，那么接下来 $3 \sim n$ 中的每一个人的朋友数就变成了 $(n-3)$，于是他们就可以留下来了。

于是最少牺牲两个人就可以使得剩下的人留下，直接输出 $(n-2)$ 即可。

代码如下：

代码实现比较简单所以没写注释。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define in inline
#define ll long long

in int read()
{
	int w=0,r=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')r=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		w=(w<<1)+(w<<3)+(ch^48);
		ch=getchar();
	}
	return w*r;
}

int T,n;

int main()
{
	T=read();
	while(T--)
	{
		n=read();
		if(n<=2)
		{
			puts("0");
		}
		else
		{
			cout<<n-2<<endl;
		}
	}
	return 0;
} 
```

构造方法可能不止一种，我这里只是给出了一种可行解。

如有错误或问题，请指出。

---

## 作者：tryrtj (赞：4)

这题题目描述对于我这种语文渣来说太不友好了；

而且题解也太不友好了，大家可以看一看[这位巨佬的思路](https://blog.csdn.net/Tdyh_NY/article/details/71156209?utm_source=blogxgwz3)。我就是看这个写的，思路不看题解实在有点难想。

代码顺便发一下

```
#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int h;
	for(int i=0;i<n;i++){
		cin>>h;
		if(h!=1){
			cout<<h-2<<endl;
		}
		else cout<<0<<endl;
	}
	return 0;
}
```

那篇题解希望可以给各位点帮助QAQ

---

## 作者：哔哩哔哩 (赞：3)

这道题是一个红题……  
刷成绿色一定是恶意的……

其实是一个简单数学题 

因为第一次0个人离开，离开人数递增，并且从1计算到第n-1个人 

因此可以推出剩下的人数就是 n-2 

另外 需要特判n==1 是 0 

程序就呼之欲出了

```cpp
#include<bits/stdc++.h>
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int n;scanf("%d",&n);
		printf("%d\n",n==1?0:n-2);
	}
	return 0;
}
```

---

## 作者：Kobe303 (赞：2)

# 首先，这明显是一道数学题

题目翻译有误，朋友个数指的是在场的（已离开的不算）;

关系是相互的(不可传递，例如A与B是朋友，B与C是朋友，但A与C不是朋友);

### 接下来就是画图找规律啦~~~


#### 一个人：

很明显最多剩下0人

因为有0个朋友的人离开时TA就得走

#### 二个人：

1.若他俩是朋友，则有1个朋友的人离开时，这两人都得走

2.若他俩不是朋友，则有0个朋友的人离开时，这两人都得走

综上所述，最多剩下0人



------------


------------


------------

接下来的图中黑线连接的两点代表这两人是朋友

#### 三个人：


![三个人](https://cdn.luogu.com.cn/upload/image_hosting/phayi496.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 经枚举可发现这是最优情况


有0个朋友的人离开时，没有人会离开；

有1个朋友的人离开时，2、3会离开；

有2个朋友的人离开时，没有人会离开；（此时1剩余的朋友个数为0）

这样就剩下了1个人。

#### 四个人：

![四个人](https://cdn.luogu.com.cn/upload/image_hosting/8v7l2jxi.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 经枚举也可发现这是最优情况


有0个朋友的人离开时，没有人会离开；

有1个朋友的人离开时，没有人会离开；

有2个朋友的人离开时，2、3会离开；

有3个朋友的人离开时，没有人会离开；（此时1、4剩余的朋友个数为1）

这样就剩下了2个人。


## 打住，此时我们是否可以大胆猜测

#### 若有n个人参加聚会， 设最多剩下a人，

#### 则a = $\begin{cases}0 & n == 1\\n - 2 & n  \geq  2     \end{cases}$



## 现证明如下：

假设在场所有人互相都是朋友,现令1与2不是朋友

有0个朋友的人离开时，没有人离开；

有1个朋友的人离开时，没有人离开；

有2个朋友的人离开时，没有人离开；



------------



------------

------------

有n-2个朋友的人离开时，1、2离开

有n-1个朋友的人离开时，没有人离开（在场的人剩余的朋友个数都是n-3）

最终剩下n-2个人

## 证明成功


最后是代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int n;
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		if(n == 1 || n == 2) printf("0\n");
		else printf("%d\n", n - 2);
	}
	return 0;
}

```

望管理员大大通过QAQ


---

## 作者：fisheep (赞：2)

### 题解：

因为要留下更多的人，也就是走更少的人。所以会出现以下几种情况：

* 1.一个都不走是不可能的。

* 2.牺牲1个，每个人跟别人都是朋友，都有（n-1）个朋友，都要离开。

* 3.牺牲2个，1、2号互相之间不是朋友，与其他人都是朋友，1、2号有（n-2）个朋友，其他人都有（n-1）个朋友，1、2号离开后，剩下的人都有（n-3）个朋友，都可以留下。

* 4.只有1或2个人时，无论怎样都留不下。

**ps:**　除了有一点思维，感觉这真不是一道绿题。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){//快读
  int x=0,f=1;
  char ch=getchar();
  while(ch>'9'||ch<'0'){
    if(ch=='-') f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<1)+(x<<3)+(ch^48);
    ch=getchar();
  }
  return x*f;
}

int main(){
	int t;
	t=read();
	while (t--) {
		int n;
		n=read();
	 printf("%d\n",max(0, n - 2));
	}
	return 0;
}
```


---

## 作者：Andysun06 (赞：2)

### CF23B 题解
这题居然还没有 Pascal 题解，那我就来一篇吧！
#### 题目思路：
有 $n$ 个人要去参加聚会，刚开始所有人都在，然后有零个朋友的人会离开，接着是有一个朋友的人会离开，以此类推直到有 $n-1$ 个朋友的人离开  问你最佳情况下最后会剩余多少人？

这个题目描述看起来似乎有点复杂，但是当我们开始尝试推式子是，立马就可以发现只要输出 $t-1$ 就可以了。但有一种特殊情况，就是 $t=1$ 的时候,，我们只要加上特判，就可以了。

#### 题目难度：
个人认为在 `入门` 左右，思维难度一般。

#### 做法分析：
在 `题目思路` 中已经说了，如果 $t<>1$ 只要输出 $t-2$ 就可以了。 $t=1$ 的时候，只要输出 $0$ 就可以了.

#### 完整代码：
```pas
var i,n,k:longint; //定义
begin
    read(n);  //输入
    for i:=1 to n do //循环 n 次
    begin
        read(k);  //输入
        if k=1 then  //
            writeln('0') //t=1 的时候，输出 0
        else
            writeln(k-2); //如果 t<>1 输出 t-2 
    end;
end. //最后用句号
```

希望本题解对大家有帮助，也感谢管理员百忙之中帮我审核题解，谢谢！

---

## 作者：_cmh (赞：1)

~~哦原来绿题这么简单~~

一眼数学题，因为每个人都可以是朋友，就可以用假设法来做。

我们来找下规律：

- 当 $1$ 个人参加聚会时，他没有朋友：

广播：“请有0个朋友的人离开”。

他就走了。

- 当 $2$ 个人参加聚会时，设他俩时朋友：

广播：“请有0个朋友的人离开”。

两个人都赖着不走。

广播：“请有1个朋友的人离开”。

两个人都走了。

- 当 $3$ 个人参加聚会时，设 （1,2） 不是朋友，其他的都是：

广播：“请有0个朋友的人离开”。

三个人都赖着不走。

广播：“请有1个朋友的人离开”。

1，2都走了，留下3。

- 当 $4$ 个人参加聚会时，设 (1,3) 不是朋友，其他的都是：

广播：“请有0个朋友的人离开”。

四个人都赖着不走。

广播：“请有1个朋友的人离开”。

四个人都赖着不走。

广播：“请有2个朋友的人离开”。

1，3走了，留下2，4。

- 这样推下去，发现一个规律：如果 $n \le 2$ ，则全部走光，否则只会走 $2$ 人。

**注意多组数据！**

接下来上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int T,n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		cout<<max(0,n-2)<<endl;
	}
    return 0;
}
```

求赞！

---

## 作者：CrTsIr400 (赞：1)

这题 $\color{SpringGreen}\texttt{普及+/提高}$，~~看起来很难$qwq$.png~~

掌握规律就行

$n>=2$的时候

可以发现人数的递减规律

就是$n-2$（滑稽.jpg）

因为第一次$0$个人离开

离开人数递增

并且从$1$计算到第$n-1$个人

然后就$A$了$qwq$（滑稽.gif）

```cpp
#include<bits/stdc++.h>
int flaag,pnt,sz=100;char mid_char=' ',ch,buff[21];
using namespace std;
template<typename t>void in(t&a){a=0;ch=getchar();flaag=1;while((ch<'0')||(ch>'9'))flaag=(ch=='-')?-flaag:flaag,ch=getchar();while((ch>='0')&&(ch<='9'))a=a*10+ch-'0',ch=getchar();a*=flaag;}
template<typename t>void out(t a){if(a<0)putchar('-'),a=-a;if(a==0)putchar('0');while(a)buff[++pnt]=a%10+'0',a/=10;while(pnt)putchar(buff[pnt]),--pnt;putchar(mid_char);}
template<typename t,typename ...ARGS>void in(t&a,ARGS&...args){in(a);in(args...);}
template<typename t,typename ...ARGS>void out(t a,ARGS... args){out(a);out(args...);}
//毒瘤的缺省源，毒瘤的码风（滑稽）
int n,x;
int main()
{
	in(n);//输入n
	while(n--)//循环n次
	{
		in(x);//输入x
		out((x>1)?x-2:0);//上面有讲
	}
	return 0;
}
```

**~~A了这道题~~**

**~~祝你们好运（滑稽）~~**

---

## 作者：lxgw (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/CF23B)
### 题意
$n$ 个人要去参加聚会，刚开始所有人都在聚会上，后来0个朋友的人会离开，接着是只有1个朋友的人也会离开……最终有 $n - 1$ 个朋友的人离开，求这个聚会最后最多有多少人？
### 思路
因为要求出最多的人数，所以尽量让先离开的人让后面的人的朋友数减一，从而不会离开，因为朋友是双向的（即不会只有一个有 $x$ 个朋友的人），所以最少要离开两人，即最多留下 $n-2$ 个人。可构造：有 $n-2$ 个 $(n-1)$ 个朋友的人, $2$ 个 $(n-2)$ 个朋友的人，当那两个 $n-2$ 个朋友的人走后，其余 $n-2$ 个人的朋友数减一为 $n-2$ ，不用离开。

要判断一下 $n\leq 2$ 时的情况，这时不会有人留下。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main() {
	cin>>t;
	times:if(!t) return 0;;//t组数据
	cin>>n;
	cout<<max(n-2,0)<<endl;//输出
	t--;
	goto times;
	return 0;
}
```



---

## 作者：Mine_King (赞：0)

在我的[博客](https://www.cnblogs.com/mk-oi/p/14082983.html)观看效果更佳。

## Problem

[CF23B Party](https://www.luogu.com.cn/problem/CF23B)  

题目大意：  
有 $n$ 个人参加聚会，第一次没有在场朋友的人离场；第二次有一个在场朋友的人离场；第三次有两个在场朋友的人离场，以此类推……  
请你构造一种朋友关系（朋友关系是双向的），使得最后剩下来的人最多，求最后剩下多少人。

## Solution

先把题目转化一下，人相当于点，朋友关系相当于双向边。  
根据题意，显然需要牺牲某些人，使得他们离场后剩下的人都不会离场。再仔细思考一下，就会发现我们要满足以下条件：

- 牺牲的人不可能为0
- 牺牲所有人加起来一定与剩下的所有人有关系
- 剩下的人的朋友数应该都一样（这样可以保证不会出现意外QAQ）

然后我们来看，牺牲的人数可不可能为 $1$？  
答案是不可能。因为如果牺牲这个人后剩下的人数为 $x$，这个人牺牲后所有人的度都会减一。那么要使其他人都留下来，就要求初始时剩下的人每个人都 $x+1$ 的度，而总人数才 $x+1$，显然这是不可能的。  

那牺牲两个人呢？  
如果这两个人牺牲后仍然使每个人的度减一，显然是没用的。所以我们应该让这两个人每人都与剩下的人有关系。设剩下的人有 $y$ 人。剩下的人可以在初始时有 $y+1$ 的度，这是可以完成的。  
再尝试画一个实际的图，可以发现我们只要让所有剩下的人连成完全图，让牺牲的两个人与每个点都连边即可。  
注意当 $n=1$ 或 $n=2$ 时没人留下。  

## Code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		printf("%d\n",max(n-2,0));
	}
	return 0;
}
```

---

## 作者：Mars_Dingdang (赞：0)

双倍经验：P1416 攻击火星（用户名叫 Mars 的我有被冒犯额）。因此，本题显然恶评了。

## 题目大意
现在聚会上有 $n$ 个人参加，然后依次按照规律离开，第一次是有 $0$ 个朋友的人离开，第二次是有 $1$ 个朋友的人离开，第三次是有 $2$ 个朋友的人离开，之后依次是有 $3,4,5,6\cdots n-1$ 个朋友的一次离开，求最后聚会最多将会剩下多少人。

可以抽象为：一个 $n$ 个点的无向图, 先攻击度为 $0$ 的点（相当于从图中删除掉它），然后是度为 $1$ 的点，依此类推直到度为 $n-1$ 的点。

所有的点度统计是动态统计的。（一个点删掉后，与之相连的点的点度都会 $-1$）。攻击度为某个数的点时是同时攻击的。

你需要设计这个图的边的方案来使得未被攻击的点最多。

## 大体思路
首先观察到 P1416 数据范围 $n\le 50000$，无法直接用邻接表，意味着这可能是一道结论题。

那么我们来找规律 + 构造。

- 当 $n=1,2$ 时，显然所有点均会被删去，$ans=0$。

- 当 $n=3,4$ 时，可以保留一个点。P1416 的样例使用的是类似链的构造 ①-②-③。

- 当 $n=5$ 时，按链构造会出现问题：即删去两端结点后，中间结点度为 $2$，仍会被删去。因此，构造法变为：选出两个末端节点，把两个末端节点与所有非末端节点相连，再把非末端节点与所有非末端节点相连。

![](https://cdn.luogu.com.cn/upload/image_hosting/ma64npnu.png)

因此，特判 $n=1$ 时 $ans=0$，否则 $ans=n-2$。

## 完整代码
```cpp
#include<bits/stdc++.h>//cpp
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n;
		cin>>n;
		if(n==1) cout<<0;//特判
		else cout<<n-2;
		puts("");
	}
	return 0;
} 
```
相比之下，python 就短了很多：

```python
t=int(input())//python
while t>0:
	a=int(input())
	if a == 1: print(0)//特判
	else print(a-2)
	t -= 1
```
## 后记
1. python 中 `input()` 函数默认输入字符串，因此需要强制类型转换 `int(input())`；

2. python 缩进相当于大括号；
3. t-=1 不能写成 t--。

更多技巧详见 LucasXu80 [博客](https://www.luogu.com.cn/blog/HuayuLucas/python-kuai-su-shang-shou)。

---

## 作者：BotDand (赞：0)

# Problems
现在聚会上有$n$个人参加，然后依次按照规律离开，第一次是有$0$个朋友的人离开，第二次是有$1$个朋友的人离开，第三次是有$2$个朋友的人离开，之后依次是有$3,4,5,6……n-1$个朋友的一次离开，求最后聚会最多将会剩下多少人

输入:第一行一个整数$t$，表示数据组数，之后t行每行一个整数$n$

输出:对于每组数据，输出一个答案

$1 \le t \le 100000$

$1 \le n \le 100000$
# Answer
找规律的题。（先说一句啊：[C_Cong大佬别生气啊QWQ](https://www.luogu.com.cn/user/89910)）

* ## 一个人：直接走；
* ## 两个人：也没有人剩下；
* ## 三个人：可以画出如下的图（~~盗了别人的图~~
![](https://s1.ax1x.com/2020/03/25/8vqNFS.png)

0. 当没有朋友的人要走时，没有人离开；
1. 当有一个朋友的人要走时，2、3离开，1和2、3的朋友关系消失。

### 所以只剩下一人
* ## 四个人：~~同样借鉴别人的图~~
![](https://s1.ax1x.com/2020/03/25/8vL81J.png)

0. 当没有朋友的人要走时，没有人离开；
1. 当有一个朋友的人要走时，没有人离开；
2. 当有两个朋友的人要走时，1、3离开，2和1、3的朋友关系消失，4和1、3的朋友关系消失；

### 剩下两人

## $所以不难发现剩下的人数是n-2，但这里要注意一个点：n=1时输出0。$
# Code
```pascal
var
  n,i,x:longint;
begin
  readln(n);//读入n
  for i:=1 to n do
    begin
      readln(x);//读入x
      if x=1 then writeln(0)//特判
        else writeln(x-2);//x-2
    end;
end.
```

---

## 作者：tobie (赞：0)

一道非常不错的结论题

首先，我们随便画几个稠密图，会发现至少会有两个人离开。

所以理想状态就是只让两个人离开。

首先，我们可以让1号和2号的联系断开（毕竟如果是完全图的话就是全部人一起走）。

然后我们再把其他所有人两两相连，那么所有人（出了1号和2号）就有 $n-1$ 个朋友，1号和2号有 $n-2$ 个朋友。

所以1号和2号肯定是最先离开的，然后其他人的朋友数全部也变成 $n-2$ 了，游戏结束。

所以答案就是 $\max(0,n-2)$ 。

于是程序就非常简单地就出来了。
```cpp
#include<iostream>
using namespace std;
int main()
{
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<max(n-2,0)<<endl;
    }
}
```


---

