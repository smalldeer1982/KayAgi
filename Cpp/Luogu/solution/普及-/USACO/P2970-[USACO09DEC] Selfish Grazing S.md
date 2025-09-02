# [USACO09DEC] Selfish Grazing S

## 题目描述

Each of Farmer John's N (1 <= N <= 50,000) cows likes to graze in a certain part of the pasture, which can be thought of as a large one-dimeensional number line. Cow i's favorite grazing range starts at location S\_i and ends at location E\_i (1 <= S\_i < E\_i; S\_i < E\_i <= 100,000,000).

Most folks know the cows are quite selfish; no cow wants to share any of its grazing area with another. Thus, two cows i and j can only graze at the same time if either S\_i >= E\_j or E\_i <= S\_j. FJ would like to know the maximum number of cows that can graze at the same time for a given set of cows and their preferences.

Consider a set of 5 cows with ranges shown below:

```cpp
  ... 1    2    3    4    5    6    7    8    9   10   11   12   13 ...
  ... |----|----|----|----|----|----|----|----|----|----|----|----|----
Cow 1:      <===:===>          :              :              :
Cow 2: <========:==============:==============:=============>:
Cow 3:          :     <====>   :              :              :
Cow 4:          :              :     <========:===>          :
Cow 5:          :              :     <==>     :              :
```
These ranges represent (2, 4), (1, 12), (4, 5), (7, 10), and (7, 8), respectively.

For a solution, the first, third, and fourth (or fifth) cows can all graze at the same time. If the second cow grazed, no other cows could graze. Also, the fourth and fifth cows cannot graze together, so it is impossible for four or more cows to graze.

约翰有N(1≤N≤50000)头牛，约翰的草地可以认为是一条直线．每只牛只喜欢在某个特定的范围内吃草．第i头牛喜欢在区间(Si，Ei)吃草，1≤Si<Ei≤1,000,000,00.

奶牛们都很自私，他们不喜欢和其他奶牛共享自己喜欢吃草的领域，因此约翰要保证任意

两头牛都不会共享他们喜欢吃草昀领域．如果奶牛i和奶牛J想要同时吃草，那么要满足：Si>=Ej或者Ei≤Sj．约翰想知道在同一时刻，最多可以有多少头奶牛同时吃草？


## 样例 #1

### 输入

```
5 
2 4 
1 12 
4 5 
7 10 
7 8 
```

### 输出

```
3 
```

# 题解

## 作者：星尘_星辰 (赞：12)

emmm...这道题是一道比较经典的贪心题，这道贪心需要一点~~运气~~思考。

这道题略加思索能得出肯定需要排序的结果(~~废话~~)那么每头奶牛可以排序的“控制点”如下

1. 长度
2. 左端点
3. 右端点

①的话容易想到，但是结果嘛......

②和③我相信聪明的你**一定**能想~~猜~~到，加油吧！

```
#include<bits/stdc++.h>
using namespace std;

int n,ans,maxx;
struct cow {
	int x,y;
} a[50005];

int cmp(cow a,cow b) {
	return a.QAQ<b.QAQ;
}

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d %d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp);
	for(int i=1; i<=n; i++)
		if(maxx<=a[i].x)
			ans++,maxx=a[i].y;
	printf("%d",QAQ);
	return 0;
}
```

Tips:贪心需要局部最优解，那么也就是需要给后面的奶牛留下足够的位置，所以......Mooo~

---

## 作者：微香玉烛暗 (赞：7)

一道关于区间的简单贪心，但是有些迷惑性。很多人一看到题目就把数据按左端点排序，但是应当按右边端点，因为要求**最多牛吃草**时刻，所以看这头牛的结束时间，每次用开始时间比较，并更新$ans$。（初值为$1$）

没听懂？    
没关系，结合数据一起分析：

```
2 4 
1 12 
4 5 
7 10 
7 8 
```                         
排序后就成了
```
2 4 
4 5 
7 8
7 10 
1 12 
```
$now$初始值为$4$，$ans=1$，从第二个开始枚举。   
① $4>=4$，所以$now=5$，$ans++$        
② $7>=5$，所以$now=8$，$ans++$              
③ $7<8$，不变              
④ $7<8$，不变             
⑤ $1<8$，不变

$ans=3$

```cpp
# include <cstdio>
# include <iostream>
# include <algorithm>
using namespace std;
const int N=50005;
int n,ans=1,now;

struct node {
	int x,y;
	friend bool operator < (const node &p,const node &q) {
		return p.y<q.y;
	}
}a[N];

/*
另一种写法cmp
bool cmp (node x,node y) {
    return x.y<y.y;
}
*/

int main () {
	scanf ("%d",&n);
	for (int i=1;i<=n;i++)
		scanf ("%d%d",&a[i].x,&a[i].y);
	sort (a+1,a+1+n);
	now=a[1].y;
	for (int i=2;i<=n;i++) {
		if (a[i].x>=now) {
			ans++;
			now=a[i].y;
		}
	}//如上分析代码实现
	printf ("%d\n",ans);
	return 0;
}
//By苍空的蓝耀 
```

---

## 作者：wubaiting2020 (赞：3)

这道题的简易题面:在一个数轴上有n条线段，现要选取其中k条线段使得这k条线段两两没有重合部分，问最大的k为多少。

1.先将每头牛的吃草范围按右端点从小到大排序

2.先将第一个选取，再往后扫描，如果它的做断电比现在的右端点大，那么就选取并更新当前右端点

```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
int n;
struct node{int x,y;}a[50005];
bool cmp(node x,node y){return x.y<y.y;}//按右端点从小到大排 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d %d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp);
	int t=a[1].y,ans=1;//因为已经选取第一个，当前右端点为第一个的右端点ans初值为1 
	for(int i=2;i<=n;i++)if(a[i].x>=t){t=a[i].y;ans++;}//如果这条线段的左端点比当前右端点大，ans+1并更新当前右端点 
	printf("%d",ans);
	return 0;
}


```


---

## 作者：CloudStroll (赞：3)

这是一道比较经典的问题，注意题目所问的是奶牛的个数，如此，就应该联想到贪心的算法。（题外话：如果要求算奶牛的草场总长则应该用dp）

那么应该怎么贪心呢？

一个奶牛的需求是一个区间，左端点l与有端点r，但是对其他奶牛有影响的是右端点。

那么就对右端点进行排序，从1开始枚举，如果奶牛要求区间的左端点满足大于等于最后一次有行动的决策（即奶牛“占领”草场）的右端点，那么加入，且更新占领的状态。
代码如下
```cpp
//begin
#include <cstdio>
#include <algorithm>
using namespace std;
//head
//By CJ

const int MAXN=50005;
//const

long long p,i,j,N,ans,end;
//variable

struct FARM
{
	long long l;
	long long r;
}farm[MAXN];
//struct

int cmp(FARM x,FARM y)
{
	return x.r<y.r;
}



void Read_In()
{
	scanf("%d",&N);
	for(i=1;i<=N;i++)
	{
		scanf("%d%d",&farm[i].l,&farm[i].r);
	}
}



void Solve()
{
	
	sort(farm+1,farm+1+N,cmp);
	for(i=1;i<=N;i++)
	{
		if(farm[i].l>=end)
		{
			ans++;
			end=farm[i].r;
		}
	}
}



void Write_Out()
{
	printf("%d",ans);
}
//function

int main()
{
	Read_In();
	Solve();
	Write_Out();
	return 0;
}
//main
//end
```
要注意快排需要用到结构体来同时更改。
推荐做完本题后尝试P1937

---

## 作者：user48442 (赞：2)

其实看到楼下的题解跟我基本上一样，我本来是不想发的，结果发现楼下的解释特别简略啊，所以我也来贡献一下吧～

在考试的时候看到这道题，我的第一感觉是：这道题好像很难啊...

结果看完了考试的题目，才发现好像这个银组的题目已经是最简单的了...

看着隔壁x\_faraway\_x大佬写了一个DP，但我怎么觉得这道题不用DP啊，我这下估计又要爆零了...

好吧，我们回归一下正题。

废话不多说，习惯性的定义一个结构体变量。

这里的**.e** 是指末尾

这里的**.s**是指开头

一开始我的思路是按照开头排一遍，结果发现好像不行

Eg:
我有1 17| 3 4| 5 9| 15 18 的四头牛。如果按照开头从小到大排序的话很明显选择的是“1 17”这一头牛，发现只能选择一个。 而最优解很明显是“3 4→5 9→15 18”这三头牛。
所以我就放弃了按照开头升序排序的思路，转投按照结尾升序排序。

排完了，突然发现这一道题好像可以用贪心来解？！

为了保险起见，我还是证明一下吧（可能有错啊我是个蒟蒻）：

**我们把n头奶牛看成是n个工作，而每个工作的价值都是1，有s和e，即开始时间和结束时间。**

很明显，我们想要获得最多的价值，就应该选择先结束的工作，以便让其他的工作尽早做。所以我们先按照结束时间升序排序一下，然后从第二个找能选择的工作（奶牛）即可。 ））这里为什么是从第二个开始呢？因为我们这里的第一个很明显是结束时间最早的，而他前面是没有工作的，所以无论如何第一个都是必须选择的。

代码如下：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n;

struct Node
{
    int s;
    int e;
}cow[50005]; // 定义一个结构体数组，s代表工作开始的时间，e代表工作结束的时间

bool cmp(Node a, Node b) // 按照结束时间从小到大排序
{
    if(a.e == b.e) return a.s > a.s;
    return a.e < b.e;
}

void init(void) // 输入函数，我想就不用多说了
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d %d", &cow[i].s, &cow[i].e);
    sort(cow + 1, cow + 1 + n, cmp);
    return;
}

void work(void)
{
    int ans = 1, last = cow[1].e; // ans代表能选择的工作（奶牛）的数量，last代表上一次选择的工作的结束时间，ans直接置为1，last直接置为第一个的结束时间，因为第一个必选
    for(int i = 2; i <= n; i++)
    {
        if(cow[i].s >= last) // 只要这个工作（奶牛）能选，就把他加上
        {
            last = cow[i].e;  // 更新上一个的结束时间
            ans++; // 计数器++
        }
    }
    printf("%d", ans); // 输出答案
    return;
}

int main(void)
{
    init();
    work();
    return 0;
}

```
如果大家直接看我的代码而不看我的解释基本上是看不懂为什么我这里说是工作的，所以大家还是先看文字解释比较好


---

## 作者：吉瑞降临 (赞：0)

这道题显而易见是一道贪心题，是一种区间问题

问题就在问：在一个数轴上有 n 条线段，现要选取其中 k 条线段使得这 k 条线段两两没有重合部分，问最大的 k 为多少。

大致思路：
首先排序，用一层 for 循环来枚举，找到出现相交的部分，累加后输出

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct znt{
	long long l,r;  
	bool operator <(znt b) const{
	return (r<b.r)||(r==b.r&&l>b.l);}   // 定义结构体中的小于号，进行排序 
}a[100001];
int main()
{
	long long n,i=1,x,cnt=1;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i].l>>a[i].r;
	}
	sort(a,a+n);  // 排序
	//for(int i=0;i<n;i++)cout<<a[i].l<<" "<<a[i].r<<endl;
	x=a[0].r;
	while(i<n)
	{
		if(a[i].l>=x)
		{cnt++;x=a[i].r;}
		i++;
	}
	cout<<cnt<<endl;  //输出答案
	return 0;
}
```
好了，一题代码就这样结束了。


---

## 作者：king_xbz (赞：0)

很多人这道题做错不是因为不会做，而是因为没看懂题导致贪心策略出错。

题目上的样例解释没有翻译，我来翻译一下
```cpp
样例一：
5 
2 4 
1 12 
4 5 
7 10 
7 8 
解释：
这些牛喜欢吃草的范围分别为（2，4），（1，12），（4，5），（7，10）和（7，8）。
根据牛们的喜好，我们可以进行分析：
第一、第三和第四（或第五）头牛可以同时吃草。
如果第二头牛在吃草，其他牛就不能吃草了。
另外，第四和第五头牛不能一起吃草，所以最多只有三头牛可以一起吃草。
故结果为3.
```
手动翻译，水平有限，请见谅。

那么我们可以制定贪心策略：
1.先将每头牛的吃草范围按右端点（注意不是左端点，不懂就看样例分析）从小到大排序（结构体快排）

2.遍历牛群，如果一头牛的左端比现在的右端点大，那么就选取并更新当前右端点（贪心求解）

具体实现：

预处理：
```cpp
inline void pre()
{
	n=read();
	for(fint i=1;i<=n;i++)
	a[i].l=read(),a[i].r=read();
	sort(a+1,a+n+1,cmp);
}
```
贪心求解：
```cpp
inline int begin_todo()
{
	int tot=1;
	for(fint i=1;i<=n;i++)
	if(i==1)
	now=a[i].r;
	else
	if(now<=a[i].l)
	now=a[i].r,tot++;
	return tot;
}
```
结构体排序
```cpp
struct node
{
	int l;
	int r;
}
a[p];
inline bool cmp(node aa,node bb)
{
	return aa.r<bb.r;
}
```
这样，我们就做出来这道题了，祝大家ac愉快

---

## 作者：hylong (赞：0)

其实这题是个简单的贪心。
这题......~~（没天理了，O2跑的比O3还快，稳定比快排还快）~~

最高50ms，其实还可以在卡一卡常的，写个桶排说不定还可以少一些，或许可以低于48ms。

------------------------------------------以上为闲扯内容--------------------------------------------
#### 思路：
把区间按结束的排个序，在一个一个找（以后遇见不会的贪心先排个序，说不定就有思路了）。
#### 代码：
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
struct cow{
	int b;
	int e;
	bool operator < (const cow &d)const
	{
	 return e<d.e;
	}//重载运算符
    //格式为bool operator 符号 (const 结构体名字 &变量名)const{......}
}a[50005];
int n;
int read()
{
	int x=0;
	char f=getchar();
	while(f>'9' || f<'0')
	 f=getchar();
	while(f<='9' && f>='0')
	{
	 x=x*10+f-'0';
	 f=getchar();
	}
	return x;
}
int main()
{
    int i;
    n=read();
    for(i=1;i<=n;i++)
    {
     a[i].b=read();
	 a[i].e=read();
	}//快读强行缩时间复杂度
    stable_sort(a+1,a+1+n);//稳定排序，在此题时间复杂度貌似比快排低一点？？？
    int c=0,temp=-1;
    for(i=1;i<=n;i++)
     if(a[i].b>=temp)
     {
      c++;
      temp=a[i].e;
     }//贪心核心
    printf("%d\n",c);
    return 0;
}
```

---

## 作者：不存在之人 (赞：0)

### 解题思路：

贪心一下，按$R$从小到大排序，依次加入即可

### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,r,ans;
struct NA
{
	int l,r;
}e[N];
bool cmp(NA i,NA j)
{
	return i.r<j.r;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&e[i].l,&e[i].r);
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++)
		if(e[i].l>=r) ans++,r=e[i].r;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：我没有小白 (赞：0)

这道题贪心思路是

先按右端点排序（因为右端点是时间的终点，只有时间的终点才会对后续的事件有影响），则拍出来枚举一遍的结果一定是最优解。

代码如下
```cpp
#include<bits/stdc++.h>
#define N 100000
using namespace std;
struct edge
{
	int st,en;
} e[N];
int end,n,t,ans;
bool cmp(edge x,edge y)
{
	return x.en<y.en;
}//按时间的终点进行排序 
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>e[i].st>>e[i].en;
	sort(e+1,e+1+n,cmp);
	end=e[1].en;//end代表最后的时间 
	ans++;//因为第一个事件已经算上，所以ans++ 
	for(int i=2; i<=n; i++)
	{
		if(e[i].st>=end)
		{
			ans++;
			end=e[i].en;//如果下一个事件的起点满足题目中给的条件，则就算上，并且ans++ 
		}
	}
	cout<<ans;//输出ans
}
//完结撒花 
```
以上就是思路，愿对你们有帮助（管理大大求过，小妹谢谢啦）

---

## 作者：花千树 (赞：0)

这题题解少，本来想发函数流，看楼下有，算了，惠民吧（主要利于萌新，函数流萌新看不懂）

本题思路：贪心+排序，第一次RE3个点，改了一下数组大小，第二遍AC，不难，读入后先快排，判断的条件题目上都有，聪明的就知道抄，但数组中的第一个不一样，所见以要加一个另外的条件——i==1，不过也可以把ans初值设为1

**详情见代码**

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>//sort必备万能头文件
using namespace std;
int ans;
struct AC{//结构体定义
    int a,b;
}f[1000005];//数组开大点，以免悲剧发生
bool cmp(const AC&x,const AC&y){//sort重要cmp
    return x.b<y.b;
}
int main(){//过程华丽开始
    int n;
    scanf("%d",&n);//读入
    for(int i=0;i<n;i++){
        scanf("%d%d",&f[i].a,&f[i].b);//读入
    }
    sort(f,f+n,cmp);//快排
    int v=0;//小型指针（变量）
    for(int i=0;i<n;i++){//主要处理循环
        if(i==0||f[i].a>=f[v].b){//条件
            ans++;
            v=i;
        }
    }
    printf("%d\n",ans);//完美输出
    return 0;//过程华丽结束
}
```

---

## 作者：lshhhhhh (赞：0)

/\*

这题其实很简单，先按终点由小到大排序，先取第一个，然后用贪心


```cpp
using namespace std;
struct aa{
    int a,b;
}c[50001];
bool cmp(const aa &a1,const aa &a2){
    return(a1.b<a2.b || (a1.b==a2.b && a1.a<a2.a));
}
int n,ans,l;
int main()
{
    cin>>n;
    for(int d=1;d<=n;d++)cin>>c[d].a>>c[d].b;
    sort(c+1,c+1+n,cmp);
    for(int d=1;d<=n;d++)
    {
        if(c[d].a>=c[l].b || d==1)ans++,l=d;
    }
    cout<<ans<<endl;
    return 0;
}*/
```

---

