# [USACO07JAN] Protecting the Flowers S

## 题目描述

Farmer John went to cut some wood and left N (2 ≤ N ≤ 100,000) cows eating the grass, as usual. When he returned, he found to his horror that the cluster of cows was in his garden eating his beautiful flowers. Wanting to minimize the subsequent damage, FJ decided to take immediate action and transport each cow back to its own barn.

Each cow i is at a location that is Ti minutes (1 ≤ Ti ≤ 2,000,000) away from its own barn. Furthermore, while waiting for transport, she destroys Di (1 ≤ Di ≤ 100) flowers per minute. No matter how hard he tries, FJ can only transport one cow at a time back to her barn. Moving cow i to its barn requires 2 × Ti minutes (Ti to get there and Ti to return). FJ starts at the flower patch, transports the cow to its barn, and then walks back to the flowers, taking no extra time to get to the next cow that needs transport.

Write a program to determine the order in which FJ should pick up the cows so that the total number of flowers destroyed is minimized.

有 $n$ 头奶牛跑到 FJ 的花园里去吃花儿了，它们分别在距离牛圈 $T_i$（这里指 FJ 到那里需要 $T_i$ 分钟) 处吃花，每分钟会吃掉 $D_i$ 朵花，FJ 现在要将它们给弄回牛圈，但是他每次只能弄一头回去，来回用时总共为 $2 \times T_i$ 分钟，在这段时间内，其它的奶牛会继续吃 FJ 的花，速度保持不变，当然正在被赶回牛圈的奶牛不能继续吃了。现在求在最好的方案下奶牛吃掉花的最小朵数。


## 说明/提示

FJ returns the cows in the following order: 6, 2, 3, 4, 1, 5. While he is transporting cow 6 to the barn, the others destroy 24 flowers; next he will take cow 2, losing 28 more of his beautiful flora. For the cows 3, 4, 1 he loses 16, 12, and 6 flowers respectively. When he picks cow 5 there are no more cows damaging the flowers, so the loss for that cow is zero. The total flowers lost this way is 24 + 28 + 16 + 12 + 6 = 86.


## 样例 #1

### 输入

```
6
3 1
2 5
2 3
3 2
4 1
1 6```

### 输出

```
86```

# 题解

## 作者：曦行夜落 (赞：34)

我顺着这道题讲一下贪心策略吧          
# 一、贪心是什么？
贪心就是一种“目光短浅”的算法，之所以目光短浅是因为它只考虑眼下的事情，而不考虑长远，这也使得贪心的时空复杂度普遍偏低           
贪心的优势：速度快，空间少           
贪心的劣势：策略难想且大部分试题只能做骗分工具使用          
当然学好贪心对拿分还是很有好处的        
# 二、简单的贪心  
部分背包问题：P1208       
这种问题就是说：给定n种可任意分割的物品，每种物品有重量w和价值v，按照你选取重量的比例给你价值，但是全部物品的重量不得超过M          
分析：既然可以分割，那就按照性价比v/w排序，然后依次选取直到空间不够为止  
        
不重叠线段选取问题：P1803        
给定n个区间，选取尽量多的不重叠区间        
分析：首先要让区间尽量多，每个区间的右端点就得尽量小（腾出位置），所以按照右端点排序，然后依次选取不相交的区间（从前往后） 

这种题目有很多，主要是顺着题目的想法走，直接或间接地最小化要求的量
# 三、更难一些的贪心（~~我才不会告诉你我不会更难的了~~）
比如本题：        
这类贪心一般通过分析前后两个整体的交换来实现          
本题中，我们讨论牛x与牛y        
先抓x：2×t[x]×d[y]       
先抓y：2×t[y]×d[x]       
此时的优劣取决于t[x]×d[y]与t[y]×d[x]的大小，前者小先抓x，后者小先抓y   
故可以按照此标准排序，下面给出程序：


------------
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#define maxn 100000+500
using namespace std;
long long sum[maxn];

struct cows
{
    long long d,t;
}a[maxn];

int cmp(cows x,cows y)
{
    return x.t*y.d<x.d*y.t;
}

int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%lld%lld",&a[i].t,&a[i].d);
    sort(a+1,a+1+n,cmp);
//	for (int i=1;i<=n;++i) printf("%d %d\n",a[i].t,a[i].d);
    
    for (int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i].d;
    long long ans=0;
    for (int i=1;i<=n;++i)
        ans+=2*a[i].t*(sum[n]-sum[i]);
    printf("%lld",ans);
    
    return 0;
}
```        

例如，UVA11729的突击战，有n个任务，每个任务有交代时间a和执行时间b，每时每刻只能交代一个任务，问最少要多少时间完成全部任务        
考虑任务x和y：         
若x在y之前——       
如果y比x先结束，那么交换后y反而延后，此时反而亏         
如果y比x后结束，那么此时交换前总时间是a[x]+a[y]+b[y]，交换后为a[y]+a[x]+b[x]，根据x在y前得出a[x]+a[y]+b[y]<a[y]+a[x]+b[x]        
化简得到b[x]>b[y]，推广到每一个x和y即可得出：         
按照b从大到小的顺序依次交代即可       
## 喵就是这样

---

## 作者：lzqy_ (赞：13)

## 看到没有用前缀和实现贪心的，那就来一篇用前缀和实现的贪心做法吧

 - 首先，如何贪心？贪心算法的核心在于求“目前最优”的行为，还不会的朋友可以[点这里](https://baike.baidu.com/item/%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95/5411800?fr=aladdin)。
 因此，我们选牛的条件就是求性价比最高的。那如何求性价比呢，我们可以拿每分钟吃花数除以路程就，即为$a.D/a.T>b.D/b.T$。（注意，这里要强行类型转换成$double$型）。这一段，我们就用$STL$的$sort$排序来实现。
 
 -----
 
- 排序好了，如何计算被吃掉的花数呢？不用考虑很多，先看题面：
```
在这段时间内，其它的奶牛会继续吃FJ卡哇伊的花儿，
速度保持不变，当然正在被赶回牛圈的奶牛就没口福了！
```
换句话说，在第i只牛被拉回牛棚的时间里（排完序之后），第$(i+1)$~$n$只牛都要吃$Ti*2$分钟的花。这里，我们采用用[前缀和](https://www.cnblogs.com/-Ackerman/p/11162651.html)的方法来计算就好了。

----
- 一个坑点，在$Ti*2$的时间里，第$i$头牛一直都不能吃花（这个坑了我好久）。

---

- 数据很大，所以记得要开$long long$哦。

具体实现方法上代码（有注释）：
```
#include <bits/stdc++.h>
using namespace std;
struct p//结构体
{
  int D,T;
} a[100000];
bool cmp(p a,p b)//sort排序中定义的排序方式
{
  return (double)a.D/a.T*1.0>(double)b.D/b.T*1.0;
}//记得强行类型转换
long long p[100000],ans;
//p数组来实现前缀和，p[i]=1~i头牛每分钟吃的花的数量和
int main()
{
  int n;
  cin>>n;
  for(int i=0; i<n; i++)
    cin>>a[i].T>>a[i].D;
    //读入，由于数据不强，可以直接用cin读入
    
  sort(a,a+n,cmp);//进行排序
  
  p[0]=a[0].D;//先给p[0]赋值
  for(int i=1; i<n; i++)
    p[i]=p[i-1]+a[i].D;//给p数组赋值
    
  for(int i=0; i<n; i++)
    ans+=(p[n-1]-p[i])*a[i].T*2;
    //关键的一步，p[n-1]-p[i]的值
    //即为从n~i号的牛每分钟吃的花的数量和。
    //（此处从零开始计数）
    
  cout<<ans;//最后输出
  return 0;
}

```
----------------
最后的一点注意：

- 如果您是从一开始计数（我一般习惯从零开始），sort排序要写成 $sort(a+1,a+n+1,cmp)$ 的形式，务必注意此处的 $+1$ ；

----

写题解不易，觉得好的，给个赞再走呗~

---

## 作者：RAYMOND_7 (赞：3)

# an EAZY PROBLEM
简单的贪心，没什么好说

排序时看两头牛的顺序

设有2头牛：1,2

两种顺序

No.1--1,2
No.2--2,1

看哪个损失小，

上代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
void read(int &x){
	char c=getchar();
	int k=1;
	while(c<'0'||c>'9') {if(c=='-') k=-1;c=getchar();}
	for(x=0;c>='0'&&c<='9';c=getchar())
	x=x*10+c-'0';
	x*=k;
}
struct fox{int t,d;}a[100005];
bool cmp(fox x,fox y){
	//int i=x.d+(2*y.t)*y.d,j=y.d+(2*x.t)*x.d;
	int i=x.t*y.d,j=x.d*y.t;
	if(i<j) return true;
	return false;
}
int main(){
	int n,tic=0;
	cin>>n;
	for(int i=1;i<=n;++i){
	cin>>a[i].t>>a[i].d;
	}
	//tic*=2;
	sort(a+1,a+n+1,cmp);
	int s=0,time=0,i=1;long long ans=0;
	while(i<=n){
		ans+=1ll*time*a[i].d;
		time+=a[i].t*2;i++;
	}
	cout<<ans;
	return 0;
}


```
求赞求过

---

## 作者：___new2zy___ (赞：3)

## 题解 P2878 【[USACO07JAN]保护花朵Protecting the Flowers】

题目传送门：：

https://www.luogu.org/problemnew/show/P2878

==================================================

分析：

本题是一个**贪心**问题，主要在于抓牛的过程中只能一个一个抓，不能一次抓多个，所以这需要**贪心策略**

我们假设有两头牛x,y,现在讨论是先赶回x还是y牛使得被吃的花数目更少

**不妨设先赶回x牛使得被吃的花更少**

那么有以下式子成立:

先赶回x牛总共被吃的花sum_1
	
第一次来赶x牛花费时间:t1=x.t
	
赶回x牛:牛x已经吃掉x.t*x.d的花
	
当x牛被赶回再返回赶y牛,中间总用时
	
t2=x.t+y.t,此时共y牛吃掉t2*y.d朵花(自己展开)

整理得总吃掉的花为sum_1== x.t**x.d + y.d*(x.t+y.t) 
	
现在我们不妨反过来再计算先赶回y牛总共吃掉的花sum_2
	
能得到sum_2==  y.t**y.d + x.d*(x.t+y.d)
	
若sum_1<=sum_2则展开整理得:
	
**x.t/x.d<=y.t/y.d**
    
**上式决定了相邻两牛x,y的顺序（get局部最优解）**
    
**那么通过判断每一只牛的x.ti/x.di即可确定赶牛顺序**

**按上式给牛排序使得总体被吃掉的花最少（推广到全局最优解） ** 

本人**姑且把上面的比值叫做效率吧**

贪心思路分析结束= =
    
==================================================    
不多说，直接上代码咯= =



    #include<iostream>
    #include<cstdio>
    #include<cmath>
    #include<algorithm>
    using namespace std;
    typedef long long ll;
    const int inf=1e9+7;
    inline int read()
    {
  	    int p=0,f=1;char c=getchar();
  	    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
  	    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
  	    return f*p;}
    struct Cow
    {
      int Ti,Di;
    }p[100009];
    int n;
    ll T,ans;
    bool cmp(Cow x,Cow y)//重要的排序(注意除法)要转换类型 
    {
        double t1=1.0*x.Ti/x.Di,t2=1.0*y.Ti/y.Di;
        return t1<=t2;
    }
    int main()
    {
	    n=read();
	    for(int i=1;i<=n;i++)
            p[i].Ti=read(),
            p[i].Di=read();
	    sort(p+1,p+1+n,cmp);//开始排序
	    for(int i=1;i<=n;i++)
            {
               ans+=T*p[i].Di;
               //加上累积到该牛i时该牛已经吃的花
               T+=2*p[i].Ti;
               //加上花费的时间
            }
        printf("%lld",ans);
        return 0;
    }


没啦，感谢阅读哦QWQ~~~希望能帮到你= =

最后推广一下我的博客：

https://www.luogu.org/blog/new2zy/

拜拜~~~ >=<

---

## 作者：孑彧 (赞：2)

# P2878 保护花朵 解题报告

### 题意描述

有n头奶牛跑到FJ的花园里去吃花儿了，它们分别在距离牛圈T分钟处吃花儿，每分钟会吃掉D朵卡哇伊的花儿，（此处有点拗口，不要在意细节啊！），FJ现在要将它们给弄回牛圈，但是他每次只能弄一头回去，来回用时总共为2*T分钟，在这段时间内，其它的奶牛会继续吃FJ卡哇伊的花儿，速度保持不变，当然正在被赶回牛圈的奶牛就没口福了！现在要求以一种最棒的方法来尽可能的减少花儿的损失数量，求奶牛吃掉花儿的最少朵数！

### 思路

这个题是一个比较明显的贪心，和排队接水感觉上差不了多少，我们要考虑先牵哪一头奶牛才能时吃掉的花朵最小

假设当前只有两头奶牛，他们的位置分别为$t_1,t_2$，每分钟吃掉的花的数量为$d_1,d_2$，假设最优答案是把第一头牛放在前面，则有$2\times t_1\times d2<2\times t_2 \times d_1$，两边约去2，将$t_1$和$d_1$移到一边，其余的移到另外一边，得到式子$\frac {t_1} {d_1}<\frac{t_2}{d_2}$，于是得出结论，先选$\frac t d$小的答案最优，于是可以根据这个排序，然后统计答案

### 注意

在这道题中，当FJ从牛圈出发的时候，他这次要牵的牛已经不再吃草了

### 代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define maxn 110000
#define LL long long
using namespace std;
struct Node{
	LL t,d;
	double v;
	bool operator < (Node a)const{
		return v<a.v;
	} 
}a[maxn];
void c(int x){
	a[x].v=(double)a[x].t/(double)a[x].d;
}
LL n;
LL sum=0;
LL ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].t>>a[i].d;
		sum+=a[i].d;
		c(i);
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		sum-=a[i].d;
		ans+=2*a[i].t*sum;
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：maple_tzc (赞：2)

~~~~ 
其实，这道题是贪心的入门题，，，
	题目大意就是让奶牛吃的花尽量少，因为送一头奶牛回家就相当于你要来回跑两次，所以，后面的注意一下就好了，在这个地方提示一下，代码有一点小问题，真正懂的人一眼就能看出来。
废话不多说了，进入正题：
	考虑这个贪心的决策，首先，考虑，假设A和B两头奶牛交换位置是否会有影响，很显然，是没有的，，每一头奶牛就吃自己的，和你的其他奶牛是没有影响的，然后，就可以愉快的用结构体记录一下他们的距离和每一个单位时间吃多少花，拿一个变量记录一下所有的奶牛在1秒内能吃多少花，
强行sort排序一遍，，，，
	然后，，愉快的进行加减法，，还有乘法，，最后，，输出，，注意一下ans要开long long 数组要100010，没了，，很简单愉快。
上代码，，繁琐难看（jian jie ming liao）
 
                       华丽丽的分割线
------------------------------------------------------------
********************************************
#include<bits/stdc++.h>
using namespace std;
int n,sum;
long long ans;
struct node{
	int t,d;
}cow[100010];
bool cmp(node a,node b){
	return a.t*b.d<a.d*b.t;
}
int main(){
	scanf("%d",&n);
	for (int i=1; i<=n; i++){
		scanf("%d%d",&cow[i].t,&cow[i].d);
		sum+=cow[i].d;
	}
	sort(cow+1,cow+n+1,cmp);
	for (int i=1; i<=n; i++){
		sum-=cow[i].d;//减去你每一次送回去的奶牛每一秒吃的量
        //得到的就是你当前还剩下多少奶牛，每一秒吃的总量。
		ans+=sum*cow[i].t;//拿你的每一秒剩下的奶牛吃的量乘以你送回去的时间。
	}
	printf("%lld\n",ans);//仔细看看，，是不是有一点错？
	return 0;
}
*********************************************
~~~~

---

## 作者：Dawn_Sdy (赞：1)

显然可以看出此题具有很明显的贪心的特征，那么问题就是我们的贪心策略是什么

我们把其中两只奶牛的运输放在一起看，那么对剩下奶牛的影响与这两头奶牛运输的先后顺序无关，所以取决两头奶牛运输顺序的就是这两头奶牛在不同顺序下的损耗。

我们把这两头牛的时间分别设为x1,x2

把他们的每分钟的食草速度设成y1,y2

那么如果先运奶牛1：
造成的损耗是：x.d * y.t

如果先运奶牛2：
造成的损耗是：y.d * x.t

那么我们得到的排序方式的代码段就是：

```cpp
bool cmp(node x,node y)
{
	return x.d*y.t>y.d*x.t;
}
```

然后，记录两个数，sum与time，time用来记录从1到i用的总时间，sum统计答案

AC代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long t,d;
}a[1000005];
bool cmp(node x,node y)//排序方式 
{
	return x.d*y.t>y.d*x.t;
}
int main(){
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>a[i].t>>a[i].d;
	sort(a+1,a+n+1,cmp);//排序 
	long long time=0,sum=0;//time统计时间，sum统计答案 
	for (int i=1;i<=n;i++)
		{
		sum+=a[i].d*time;//注意，一定要先统计答案，再统计时间！ 
		time+=a[i].t*2;
		}
	cout<<sum; 
	return 0;
}

```



---

## 作者：3269224138刘 (赞：1)

将每一头牛的吃花数量和送回时间的比值从大到小排序，每次送回比值最大的牛，再加上送回每一头牛是吃掉的花的数量就行了。



```cpp
var
  a:array[0..100000,1..2]of longint;
  b:array[0..100000]of real;
  i,j,k:longint;
  n:longint;
  ans,sum:int64;
procedure sort(l,r: longint);
var
  i,j,y: longint;
  x,t:real;
begin
  i:=l; j:=r; x:=b[(l+r) div 2];
  repeat
    while b[i]<x do inc(i);
    while b[j]>x do dec(j);
    if not(i>j) then
    begin
      t:=b[i]; b[i]:=b[j]; b[j]:=t;
      y:=a[i,1]; a[i,1]:=a[j,1]; a[j,1]:=y;
      y:=a[i,2]; a[i,2]:=a[j,2]; a[j,2]:=y;
      inc(i); dec(j);
    end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;
begin
  readln(n);
  sum:=0;
  for i:=1 to n do
  begin
    readln(a[i,1],a[i,2]);
    b[i]:=a[i,1]/a[i,2];
    inc(sum,a[i,2]);
  end;
  sort(1,n); ans:=0;
  for i:=1 to n do
  begin
    inc(ans,(sum-a[i,2])*2*a[i,1]);
    dec(sum,a[i,2]);
  end;
  writeln(ans);
end.
```

---

## 作者：cghAndy (赞：1)

此题数据有问题 请管理员尽快更正谢谢~

嗯 这题的话 如果研究一下相邻的两个 看看交换的结果就好 好像是一种很经典的方法啊、、

如果x后拿的多一点 2Tx\*Dy<=2Ty\*Dx 所以当Dy/Ty<=Dx/Tx时 x应该在y前面被拿

排序一下就好了

blog里有代码  http://blog.csdn.net/cgh\_andy/article/details/53169771


---

## 作者：冰桨 (赞：0)

大体思路如下
先用sum将所有牛每分钟吃的花表示出来，然后很容易想到花费时间越短，吃的花越多的牛应先被放回家，即t/dsort一下，然后算最终结果。
注意开long long

~~由于long long导致第一遍70~~

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=1010101;
long long n,sum,ans;
struct node{
	long long t,d;
	double dis;
	bool operator<(const node&a)const{
	return dis<a.dis;
	}
}e[N];
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) {
		scanf("%lld%lld",&e[i].t,&e[i].d);
		sum+=e[i].d;
		e[i].dis=((double)e[i].t/(double)e[i].d);
	}
	sort(e+1,e+n+1);
	for(int i=1;i<=n;i++){
		sum-=e[i].d;
		ans+=sum*e[i].t*2;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

