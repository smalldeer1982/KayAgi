# [ABC131D] Megalomania

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc131/tasks/abc131_d

AtCoder王国の王立問題工房でABC管理官の座に就いたキザハシ君は、浮かれるあまり仕事を引き受けすぎてしまいました。

現在の時刻は $ 0 $ です。キザハシ君は $ 1 $ から $ N $ までの番号が振られた $ N $ 件の仕事を持っています。

キザハシ君が仕事 $ i $ を終えるには $ A_i $ 単位時間かかります。また、仕事 $ i $ の〆切は時刻 $ B_i $ であり、これまでに仕事を終わらせる必要があります。時刻 $ B_i $ ちょうどに仕事 $ i $ を終わらせてもかまいません。

キザハシ君は $ 2 $ 件以上の仕事を同時にすることはできませんが、ある仕事を終わらせた直後に別の仕事を始めることはできます。

キザハシ君はすべての仕事を〆切までに終わらせることができるでしょうか。可能ならば `Yes`、不可能ならば `No` を出力してください。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 10^9\ (1\ \leq\ i\ \leq\ N) $

### Sample Explanation 1

たとえば以下の順番で仕事を行うことで、すべての仕事を達成できます。 - 時刻 $ 0 $ から $ 1 $ までの間、仕事 $ 2 $ を行う。 - 時刻 $ 1 $ から $ 3 $ までの間、仕事 $ 1 $ を行う。 - 時刻 $ 3 $ から $ 7 $ までの間、仕事 $ 4 $ を行う。 - 時刻 $ 7 $ から $ 8 $ までの間、仕事 $ 3 $ を行う。 - 時刻 $ 8 $ から $ 11 $ までの間、仕事 $ 5 $ を行う。 仕事 $ 3 $ は〆切である時刻 $ 8 $ ちょうどに終えていますが、問題ないことに注意してください。

### Sample Explanation 2

どんな順番で仕事をしても、全ての仕事を間に合わせることはできません。

## 样例 #1

### 输入

```
5
2 4
1 9
1 8
4 9
3 12```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
334 1000
334 1000
334 1000```

### 输出

```
No```

## 样例 #3

### 输入

```
30
384 8895
1725 9791
170 1024
4 11105
2 6
578 1815
702 3352
143 5141
1420 6980
24 1602
849 999
76 7586
85 5570
444 4991
719 11090
470 10708
1137 4547
455 9003
110 9901
15 8578
368 3692
104 1286
3 4
366 12143
7 6649
610 2374
152 7324
4 7042
292 11386
334 5720```

### 输出

```
Yes```

# 题解

## 作者：Anaxagoras (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT4783)

### 0x01 思路

本题我使用的是 STL 的优先队列。输入的时候入队，然后拿个计数器把所需时间加起来，如果**严格**大于限定时间，直接输出 No 结束，如果全部可以，就输出 Yes。

### 0x02 AC Code

```cpp
#include<bits/stdc++.h>
#define int long long 
#define N 10005
using namespace std;
struct project
{
	int a;
	int b;
	friend bool operator<(project x,project y)
	{
		return x.b>y.b;
	}//用 friend 对优先队列自定义排序
};
priority_queue<project>q;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a,b;
		cin>>a>>b;
		q.push(project{a,b});
	}
	for(int i=1;i<=n;i++)
	{
		int a=q.top().a,b=q.top().b;
		q.pop();
		sum+=a;
		if(sum>b)
		{
			cout<<"No\n";
			return 0;
		}
	}
	cout<<"Yes\n";
	return 0;
}
```

---

## 作者：W_fly_K (赞：3)

很明显，这题是一道贪心。

由于我们要完成所有任务，所以要尽可能的让结束时间早的先完成，所以我们先按照结束时间从小到大排序，这样我们就尽可能的完成任务。

什么时候判断无法完成任务呢？我们排序之后，就把完成时间累加，并时刻判读它有没有超过规定时间，若超过，就不可能完成所有任务。


## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, use;
struct task {
	int time, finish ;
} a[200001];
bool cmp(task x,task y) {                 //从小到大排序。
  	if(x.finish == y.finish)
	return x.time < y.time;
	return x.finish < y.finish;
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; ++ i)
		cin >> a[i].time >> a[i].finish;
	sort(a + 1,a + n + 1, cmp);
	for(int i = 1; i <= n; ++ i)
	{
		use += a[i].time;
		if(use > a[i].finish)             //若超时。
		{
			cout << "No" << endl;
			return 0;                     //结束，后面就不用判断了。
		}
	}
	cout << "Yes" << endl;
	return 0;
}
```


---

## 作者：Chtholly_L (赞：3)

# AT4783 [ABC131D] Megalomania题解

###### 大家好，我是~~奆蒟蒻~~！！！

今天我来写题解了！！！


------------
 看一眼题干 

###### ~~好长啊，都是日文，肯定特别难（一般日文的题都很难啊，更别说题干超长啊！）~~ 

但 _普及-_ 还是让我停下了脚步。

~~看了一眼，十分感谢大神的翻译，非常简练。~~ 

### 但是还有一个地方~~自认为~~让人比较难理解。

### 我来给大家说明一下。

输入一个 $N$ ，然后输入 $N$ 组数据。每组数据包括两个数，一个是 $Ai$ ,一个是 $Bi$ 。 $Ai$ 是完成任务所需时间， $Bi$ 为你应该在 $Bi$ 秒之前完成。


------------

举个非常简单的例子（我自己现编的，不是测试数据）

输入了 $N$ ,数是 $2$。

我输入了$1$ $2$ 。

即我做完任务1需要花1秒，我必须在 $2$ 秒之前完成(**注意，是之前，而不是之内！！！** 这是难理解的地方）。很显然，可以完成。

我又输入了 $2$ $3$。

即我做完任务2需要花2秒，我必须在3秒之前完成，则我**完成时的时间**是 $1+2=3$ 秒,而规定的时间是在 $3$ 秒之前完成，很显然，也可以（题目中说可以压线完成，即完成的是时间正好是 $Bi$ ）。那么程序就可以输出 $Yes$ ,结束了。


------------

那么，明白了原理，就可以来写代码了。

假如你写作业，你的妈妈给你规定了时间，说，数学5点前完成，化学4点前完成，物理6点前完成，你会先写那个？很显然，是化学。

这道题也是同样的原理。输入完时应该先把 $Bi$ 排好序，那么用快排会更好，更快（如果用冒泡排序会 $RE$ 的！）。

但是你又发现，虽然 $Bi$ 排好了，但 $Ai$ 不会也和 $Bi$ 一起动。所以，你应该选择结构体 $Struct$ ，来让 $Ai$ 和 $Bi$ 一起动。

如果两个数的 $Bi$ 相等，按照常识的话，你肯定会选择时间短的做，所以，我在这里又写了一个函数，用来判断。

那么完成了这些复杂的“前奏”，该来到精髓部分了，也是最简单的部分，把 $Ai$ 逐个累加，每累加一次，就判断一次是否超了 $Bi$ 。

以下是完整的AC代码

## $AC$ $Code$

```cpp
#include<algorithm>  //快排的库
#include<iostream>
using namespace std;
struct ss  //结构体
{
    int a,b;
};
ss cc[300000];
bool ddddd(ss c,ss d);  //声明函数
int main()  //主程序
{   
    int n,s=0;
    cin>>n;
    for(register int i=1;i<=n;i++)  //这里用了一个register，可以运行更快。
    {
        cin>>cc[i].a>>cc[i].b;
    }
    sort(cc+1,cc+n+1,ddddd);  //快排+判断
    for(register int i=1;i<=n;i++)
    {
        s+=cc[i].a;  //累加时间
        if(s>cc[i].b)  //判断是否超时
	{
            cout<<"No"<<endl;  //输出
            return 0;  //结束程序
        }
    }
    cout<<"Yes"<<endl;  //输出
    return 0;  //结束程序
}
bool ddddd(ss c,ss d)  //函数主体
{
    if(c.b==d.b)
    {
        return c.a<d.a;
    }
    else
    {
        return c.b<d.b;
    }
}
```
[评测记录](https://www.luogu.com.cn/record/46260535)

[博客使用更佳](https://www.luogu.com.cn/blog/maxsuper/)

这是新版题解 QwQ，求过

---

## 作者：MiddleRed (赞：2)

## Discription  
$N$ 个任务，完成一个任务需要 $A_i$ 秒，需要在 $B_i$ 秒前内完成，问是否能完成全部任务。

## Solution  
本质 [P4053](https://www.luogu.com.cn/problem/P4053) 弱化版  
$\ $  
贪心。先做 $B_i$ 小的，然后在相同 $B_i$ 的任务中选择 $A_i$ 小的（对于这道题其实不需要这步，因为结果并不管你能做的任务的数量）。如果当前时间加上 $A_i$ 大于 $B_i$ ，说明做不完了，直接输出 $No$ 。  
建议做好这道题做 [AT4877](https://www.luogu.com.cn/problem/AT4877)，本质都是差不多的贪心。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cr;
struct job{int t,d;}a[300000];
bool cmp(job a,job b){return a.d!=b.d ? a.d<b.d : a.t<b.t;}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	cin>>a[i].t>>a[i].d;
	sort(a,a+n,cmp);
	for(int i=0;i<n;i++)
	{
		if(cr+a[i].t<=a[i].d)	cr+=a[i].t;
		else
		{
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}
```

---

## 作者：LJKX (赞：0)


## 思路

这道题明摆着就是贪心，要想使每个任务都能完成的话，需要优先考虑结束时间早的，只需将每个任务按结束时间也就是 $B_i$　从小到大排序即可。
同时我们要考虑是否会超时，在每次完成任务后将时间累加，如果超时直接输出 No 结束，最后在循环结束后没有结束的话输出 Yes。

注意 No 和 Yes 不要写成大写！！！
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l;
struct node {
    int a,b;
}op[200010];
bool cmp(node x,node y) {//从小到大排序
    if(x.b!=y.b) return x.b<y.b;
    else return x.a<y.a;
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d",&op[i].a,&op[i].b);
    sort(op+1,op+n+1,cmp);
    for(int i=1;i<=n;i++) {
        l+=op[i].a;//时间累加
        if(l>op[i].b) {//超时返回并输出No
            puts("No");
            return 0;
        }
    }
    puts("Yes");//最后输出Yes
    return 0;
}
```


---

## 作者：Trump__Biden (赞：0)

~~啊嗨嗨嗨，蒟蒻来喽。~~

[传送门](https://www.luogu.com.cn/problem/AT4783)
------------

这显然是一道贪心。

因为它有时间限制，所以要使结束时间结束尽可能的早。为了达到这个效果就要让时间少的完成的时间尽可能的早，因此就需要定义一个函数用来对数据进行一个排序。排序后依次进行遍历，累加上它所需的时间，判断累加完后是否超过时间限制，如果超过则直接输出 No，并结束程序，否则继续累加。最后，如果一直到循环结束都没有输出 No，就输出 Yes。

AC 代码如下：
------------
```
#include<bits/stdc++.h>
using namespace std;
int n,tim;
struct node
{
	int l,r;
}a[200005];
bool cmp(node x,node y)//排序
{
	if(x.r==y.r)
	  return x.l<y.l;
	return x.r<y.r;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; ++ i)
	  scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+1+n,cmp);
	for(int i = 1;i <= n; ++ i)
	{
		tim += a[i].l;//累加
		if(tim > a[i].r)//判断
		{
			printf("No\n");//换行！！！
			return 0;
		}
	}
	printf("Yes\n");//换行！！！
	return 0;
}
```
~~我才不会告诉你我因为大小写问题找了半天错。~~

---

## 作者：Tobiichi_Origami (赞：0)

**思路**

这是一道贪心题，但具体怎么贪呢？

首先，根据题意得知，我们需要一个 $A$ 数组和一个 $B$ 数组，可以合成一个结构体。然后，我们需要尽可能的把 $Bi$ 小的放在前面，这样就可以把结束时间小的先结束，也就是把结构体从大到小来排序，可以实现。可是，如果完成任务的时间加起来超过了 $Bi$ 秒，则超时，所以我们需要再设一个变量 $sum$ 来记录所有完成任务时间长度的总和。

**贴代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int a,b;
}s[200010];
bool cmp(node x,node y){return x.b<y.b;}
int main()
{
    int n,sum=0;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>s[i].a>>s[i].b;
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        sum+=s[i].a;
        if(s[i].b<sum)
        {
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}
```


---

## 作者：kaceqwq (赞：0)

# 题目大意：
有 N 个任务，完成一个任务需要 $A_i$ 秒，需要在 $B_i$ 秒内完成（可以压线完成，即完成的时间正好是 $B_i$ ）。问是否能完成全部任务，如果能，输出 Yes ，否则输出 No 。


# 分析：
首先，可以看出这道题主要是用贪心的思想，接着我们可以定义结构体，分别表示开始时间和结束时间，然后把结束时间进行从小到大排序。最后模拟判断：如果开始时间的总和大于任意一个结束时间的话，直接可以输出 No 。否则输出 Yes 。

# Code:
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
struct jc
{
	int begin,end;
}a[200005];
bool cmp(jc x,jc y)
{
	if(x.end==y.end)
	return x.begin<y.begin;
	return x.end<y.end;
}
signed main()
{
	ios::sync_with_stdio(0);
	int n,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i].begin>>a[i].end;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		sum+=a[i].begin;
		if(sum>a[i].end)
			{
				cout<<"No"<<'\n';
				return 0;
			}	
	}
	cout<<"Yes"<<'\n';
	return 0;
}
```


---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4783)

小学生又双叒叕来写题解啦！

这题的关键就是**贪心**。

看到  _N_  的范围，瞬间明白可能要排序。

所以我们靠着排序来想。

我们来思考一下怎样安排顺序。

对于两个时间限制，时间限制短的那个任务要先做。

为什么呢？

显然，它们所需的总时间是相等的，开始的时间也是相等的。

所以，用时间限制长的来卡总时间更好，即先短后长。

排序的大问题解决了，剩下的可就简单了。

直接按这个最优顺序模拟即可。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct QAQ
{
	int a, b;
};
QAQ t[200005];
bool cmp(QAQ x, QAQ y)
{
	return x.b < y.b;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &t[i].a, &t[i].b);
	sort(t+1, t+n+1, cmp);
	int now = 0;   //记录当前时间。 
	for (int i = 1; i <= n; i++)
	{
		now += t[i].a;
		if (now > t[i].b)
		{
			printf("No\n");  //勿忘祖传换行。 
			return 0;
		}
	}
	printf("Yes\n");   //勿忘祖传换行。 
	return 0;
}
```


---

## 作者：lsj2009 (赞：0)

## 题目大意
<https://www.luogu.com.cn/problem/AT4783>。
## 思路
很明显，这是一道****贪心****。

我们选择以****完成期限为第一关键字，以完成时间为第二关键字进行排序****。

为什么呢？****我们是在保证完成任务的情况尽量选择最优解****，所以我们肯定要保证每一个任务首先要在完成期限内，故以完成期限为第一关键字。

可能还有人觉得这并不严谨，万一有两个任务 $A$ 和 $B$，如果 $A$ 的完成期限早，但时间长；而 $B$ 完成期限晚，但时间长。如果以完成期限为第一关键字，那么先干 $A$，时间较长，虽然 $A$ 完成了任务但也导致了 $B$ 的拖延而没办法完成该怎么办呢？

事实上，是不会出现这样子的事情。我们设 $A$ 任务完成期限为 $a$，时间长 $b$；$B$ 任务完成期限 $c$，时间长 $d$（$a\le c,d\le b$）并当前时间为 $t$。我们需要证明****如果先干 $B$ 能完成任务，那么先干 $A$ 也一定能完成任务****。如果先干 $B$ 能完成任务，那么也就保证 $t+d\le c$ 和 $t+d+b\le a$。有了以上条件，我们容易证明

- $t+b\le a$；
- $t+b+d\le c$。

为什么呢？首先第一点明显成立：$t+d+b\le a$，$d$ 为正整数，则 $a\ge t+d+b>t+b$；第二点，$a\le c$，既然 $t+d+b\le a$ 那么自然也 $t+d+b\le a\le c$。

****同时容易看出，如果 $A$ 和 $B$ 为相邻的任务，那么交换他们，也仅仅影响到 $A$ 和 $B$ 的完成。****

证毕。

综上所述，我们使用****完成期限****为第一关键字进行排序，我们****可以考虑用 ``std::pair`` 将他们保存起来****，使用 ``.first`` 代表完成期限（第一关键字），``.second`` 为第二关键字，由于 ``pair`` 自动使用 ``.first`` 为第一关键字进行排序，所以用起来还是蛮方便的。

接下来模拟即可。

## code
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define LL long long
#define PII pair<int,int>
#define PLL pair<long long,long long>
#define Debug(x) putstr(x);
#define _Debug(x) { Debug(x); getc(); }
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
namespace IO { //请忽略该快读
	const int __SIZE=(1<<21)+1;
	char ibuf[__SIZE],*iS,*iT,obuf[__SIZE],*oS=obuf,*oT=oS+__SIZE-1,__c,qu[55];
	int __f,qr,_eof;
#define Gc() (iS==iT? (iT=(iS=ibuf)+fread(ibuf,1,__SIZE,stdin),(iS==iT? EOF:*iS++)):*iS++)
	inline void flush() { fwrite(obuf,1,oS-obuf,stdout),oS=obuf; }
	inline bool getc(char &x) { x=Gc(); return x!=EOF; }
	inline bool putc(char x) { *oS++=x; if(oS==oT) flush(); return 1; }
	inline bool cinc(char &x) {
		for( ; ; ) {
			getc(x);
			if(x!=' '&&x!='\n'&&x!='\r')
				return x!=EOF;
		}
	}
	template<typename I> inline bool read(I &x) {
		_eof=0;
		for(__f=1,__c=Gc();(__c<'0'|| __c > '9')&&!_eof;__c=Gc()) { if(__c=='-') __f=-1; _eof|=__c==EOF; }
		for(x=0;__c<='9'&&__c>='0'&&!_eof;__c=Gc()) x=(x<<3)+(x<<1)+(__c&15),_eof|=__c==EOF;
		x*=__f;
		return !_eof;
	}
	template<typename T,typename ...Arg> inline bool read(T& x,Arg& ...arg) {
		return read(x)&&read(arg...);
	}
	template<typename I> inline bool write(I x) {
		if(!x) putc('0'); if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		return 1;
	}
	struct Flusher_ {
		~Flusher_() {
			flush();
		}
	}io_flusher_;
}
using IO::putc;
using IO::getc;
using IO::cinc;
using IO::read;
using IO::read;
using IO::write;
const int N=2e5+5;
PII a[N];
int n;
LL ans;
int main() {
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i].second,a[i].first);
	sort(a+1,a+n+1); //排序
	for(int i=1;i<=n;i++) {
		ans+=a[i].second;
		if(ans>a[i].first) //超出期限，不能完成任务
			return 0&puts("No");
	}
	puts("Yes");
	return 1;
}
```

---

