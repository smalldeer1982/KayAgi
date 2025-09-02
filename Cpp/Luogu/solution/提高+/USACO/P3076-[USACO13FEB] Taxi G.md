# [USACO13FEB] Taxi G

## 题目描述

Bessie is running a taxi service for the other cows on the farm.  The cows have been gathering at different locations along a fence of length M (1 <= M <= 1,000,000,000).  Unfortunately, they have grown bored with their current locations and each wish to go somewhere else along the fence.  Bessie must pick up each of her friends at their starting positions and drive them to their destinations.  Bessie's car is small so she can only transport one cow in her car at a time.  Cows can enter and exit the car instantaneously.

To save gas, Bessie would like to minimize the amount she has to drive.  Given the starting and ending positions of each of the N cows (1 <= N <= 100,000), determine the least amount of driving Bessie has to do.  Bessie realizes that to save the most gas she may need to occasionally drop a cow off at a position other than her destination.

Bessie starts at the leftmost point of the fence, position 0, and must finish her journey at the rightmost point on the fence, position M.

长度为m的栅栏上，有n头牛需要坐车前往别的地方，起点和终点分别为a\_i和b\_i。现在一辆出租车从最左端0出发，要运送完所有牛，最后到达最右端m，求最小路程。出租车只能一次载一只牛。


## 说明/提示

There are two cows waiting to be transported along a fence of length 10. The first cow wants to go from position 0 (where Bessie starts) to position 9.  The second cow wishes to go from position 6 to position 5.


Bessie picks up the first cow at position 0 and drives to position 6. There she drops off the first cow, delivers the second cow to her destination and returns to pick up the first cow.  She drops off the first cow and then drives the remainder of the way to the right side of the fence.


## 样例 #1

### 输入

```
2 10 
0 9 
6 5 
```

### 输出

```
12 
```

# 题解

## 作者：浅色调 (赞：35)

### Solution：

　　本题是一道很值得做的贪心。

　　首先，每一段的出发点到目标点的距离是一定要走的，所以$ans$可以先累加每一段的距离。

　　然后，我们不难想到尽可能的走有用的路（即尽可能的让牛在车上），但是由于最多载一个牛，所以一定有路程是不载牛的。

　　我们画画图，不难发现，每次回头的路程最少的情况，是从上一个点的终点到离他最近的起点的距离。

　　**转换思路（类似于蚂蚁那道题的思路），每头牛都要从它所在起点走到一个终点然后消失同时该终点失效，相遇停下来等同于不停而是继续走到下一个最近的终点。**

　　因为牛都是一样的，我们可以理解为当两头牛相遇在某一起点，另一头牛代替原牛走到最近的终点（然后就消失了，此终点失效），再回头载上个起点的牛往前走。发现每次回头的是当前最小的终点到当前最小的起点的距离，又由于从$0$出发要走到$m$，于是我们**将$0$加入终点中，$m$加入起点中，（当作两段回头的距离）**，从小到大排序，$ans$累加起点减去终点（取绝对值）。
  
$\quad\;\;$贴张图理解一下:

![](http://images2018.cnblogs.com/blog/1240891/201805/1240891-20180518135656822-1418017436.jpg)
  
  $\quad\;\;$欢迎来踩博客：[five20](http://www.cnblogs.com/five20/p/9055809.html)（蒟蒻写题解不易，转载请注明出处，万分感谢！）

### 代码：
```cpp
#include<bits/stdc++.h>
#define il inline
#define ll long long
#define For(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
using namespace std;
const int N=100005;
int gi(){
    int a=0;char x=getchar();
    while(x<'0'||x>'9')x=getchar();
    while(x>='0'&&x<='9')a=a*10+x-48,x=getchar();
    return a;
}
int n,m,x[N],y[N];
ll ans;
int main(){
    n=gi(),m=gi();
    For(i,1,n)x[i]=gi(),y[i]=gi(),ans+=abs(x[i]-y[i]);
    x[++n]=m,y[n]=0;
    sort(x+1,x+n+1),sort(y+1,y+n+1);
    For(i,1,n)ans+=abs(x[i]-y[i]);
    cout<<ans;
    return 0;
}
```

---

## 作者：耶梦加得 (赞：34)

假如你是一个现实生活中的出租车司机，首先容易想到 $\sum|s_i-t_i|$ 是省不了的~~起码你得把路程开一遍~~。

那么除开送乘客的时间，那么剩下的就是要最小化接单时间，也就是从上一个终点到下一个起点的时间。

也许你会想到送完一个乘客去找一个最近的起点。~~然而连样例都过不去。~~

分析样例，我们从 $0$ 开到 $6$， 再从 $6$ 开到 $5$， 又从 $5$ 开到 $9$……

显然，为了不空载，我们只会在有牛的地方把乘客扔下去。这一瞬间，这个地点存在两头牛。

这两头牛有区别吗？

没有，~~众生平等~~。

这时候这两头牛的命运交汇了，你的起点就是我的起点，于是我们在必要的 $11$ 单位路程之外，只需要 $1$ 单位的拉客路程，那就是从牛 $2$ 的终点到牛 $2$ 的起点（现在已经变成了牛 $1$ 的起点）的路程。

综上所述，我们要把数组 $s,t$ 一一对应，让 $\sum|s_i-t_j|$ 最小。

这里，结论是将 $s,t$ 两数组排序后计算 $\sum_{i=1}^n|s_i-t_i|$ 

这里的顺序已经和题目中给定的无关了。

无论是小学奥数的小球碰撞，初中化学的复分解反应，还是这道题。

我管你在题目条件里是多么比目鸳鸯双去双来天长地久海枯石烂，都给我拆了！

我只关心我的油费！

至于为什么这个数值最小，可以通过邻项交换证明。 假定 $a_i < a_j , b_i < b_j$。

那么必然有 $|a_i - b_i| + |a_j - b_j| \leq |a_i - b_j| + |a_j - b_i|$。

~~（这回是真的易证了）~~

另外需要注意的是，由于你从最左端出发，相当于是刚刚拉着你自己到了 $0$ 处，准备接下一个单子，所以要把  $0$ 算作是一个**终点**。

同理，最右端是你将要载着自己开始一段新的历程的地方，$m$ 是**起点**而非终点。

```cpp
#include<algorithm>
#include<cassert>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#define miu 100007
using namespace std;
inline int abs(register int & x) {
    return x > 0 ? x : -x;
}
int n, m;
int s[miu], t[miu];
long long ans = 0;
signed main() {
    scanf("%d %d", &n, &m);
    t[0] = 0; //看作是刚拉完客等在栅栏左端
    s[0] = m; //最后的乘客是你自己，你将驶出栅栏，迈向天涯
    for(int i = 1; i <= n; ++i) {
        scanf("%d %d", s + i, t + i);
        ans += abs(s[i] - t[i]);
    }
    sort(s, s + n + 1); sort(t, t + n + 1);
    for(int i = 0; i <= n; ++i) {
        ans += abs(s[i] - t[i]);
    }
    printf("%lld\n", ans);
}

```


---

## 作者：ADay (赞：14)

[更好的阅读体验](https://www.cnblogs.com/aday526/p/solution-p3076.html)

前天 $\texttt{zwj}$ 老师 在 $\texttt{贪心}$ 专题讲了这道题，特此水一篇题解。

（其实是因为一个多月没写题解了，感觉社区分会掉下70）

先以样例为例子来看看： 

（但为了突出其某些性质，把 $s1$ 改为了 $2$，但其答案不变） 

> $\texttt{Bessie}$ 从 $0$ 号站到 $2$ 号站接第 $1$ 个客户（$2$ 站），从 $2$ 号站出发到 $6$ 号站（$4$ 站），放下第 $1$个客户，接第 $2$ 个客户，送到 $5$ 号站再回来（$2$ 站），再接第 $1$ 个客户，送到 $9$ 号点（$3$ 站），然后自己走到 $10$ 号点（$1$ 站），共 $12$ 站。  

那么画出图来是这样的（$p_1->p_8$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/tompelkw.png)

我们不难发现，$\texttt{Bessie}$ 走的路程，即 $ans$，必然满足 $ans \ge \sum\limits_{i=1}^n |s_i-t_i|$。

那么，思考一下，$ans$ 比 $\sum\limits_{i=1}^n |s_i-t_i|$ 多出来了什么呢？/yiw

来画个图吧~

![](https://cdn.luogu.com.cn/upload/image_hosting/bidjrwf5.png)

如图，红线即为多出的部分，可能你还是看不出什么。那么我们把 $\texttt{Bessie}$ 看成一只从 $M$ 走到 $0$ 的牛，即 $s_0->t_0$ 

![](https://cdn.luogu.com.cn/upload/image_hosting/on2rss2b.png)

可以发现，红线都是一条 $s_i$ 到 $t_j$ 的线，且每个 $s$ 和 $t$ 都被包含了，所以 $ans=\sum\limits_{i=1}^n |s_i-t_i|+\sum |s_i-t_j|$。又因为 $\sum\limits_{i=1}^n |s_i-t_i|$ 是定值，我们的任务就是最小化 $\sum |s_i-t_j|$。

然后把 $s$ 和 $t$ 排序即可。设 $s,t$ 排序后分别为 $a,b$ ，则 $ans=\sum\limits_{i=1}^n |s_i-t_i|+\sum\limits_{i=0}^n |a_i-b_i|$（别忘了 $\texttt{Bessie}$ 的路程）。

那么为什么排序相减就最小呢？因为任意交换同数组（$a,b$）两个数**必然会使结果增大**。

$\texttt{Ugly Code:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define i64 long long//不开ll见祖宗
namespace io{static streambuf *inbuf=cin.rdbuf();static streambuf *outbuf=cout.rdbuf();char buf[1<<21],*p1=buf,*p2=buf;inline char gc(){return (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,1<<21),p1==p2)?EOF:*p1++);}inline void pc(const char x){static streambuf *outbuf=cout.rdbuf();outbuf->sputc(x);}inline void ps(const char *x){unsigned _len=strlen(x);for(unsigned i=0;i<_len;i++)pc(x[i]);}inline i64 read(){register int _s=0,_f=1;register char _ch=gc();for(;!isdigit(_ch);_ch=gc())if(_ch=='-')_f=-1;for(;isdigit(_ch);_ch=gc())_s=_s*10ll+_ch-'0';return _s*_f;}template<typename T>inline void write(T _x1){if(_x1<0)pc('-'),_x1=-_x1;static char _sta[15];int _p=0;do{_sta[_p++]=_x1%10^48;_x1/=10;}while(_x1);while(_p--)pc(_sta[_p]);}string _s;inline string readstr(){_s.clear();register char _ch=gc();while(isspace(_ch))_ch=gc();for(;!isspace(_ch);_ch=gc())_s+=_ch;return _s;}inline void writestr(const string _s){for(unsigned i=0;i<_s.size();++i)pc(_s[i]);}template<typename T>inline void writeln(const T _x){write(_x);pc(10);}}using namespace io;
//IO优化
const int maxn=1e5+5;
int n,m;
i64 ans,s[maxn],t[maxn];
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		s[i]=read();t[i]=read();
		ans+=abs(s[i]-t[i]);//Σ|si-ti|
	}
	s[0]=m;t[0]=0;//Bessie的路程
	sort(s,s+n+1);sort(t,t+n+1);//排序啦
	for(int i=0;i<=n;i++)
		ans+=abs(s[i]-t[i]);//min(Σ|si-tj|)
	writeln(ans);
	return 0;
}
```





---

## 作者：d3NtMDAw (赞：7)

总路程=空载路程+载人（牛）路程

易知载人距离再同道题是个不变的常数

所以总路程最短就可以转化为空载距离最短也就是终点a到起点a+1（1<a<m）的距离之和最短

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
long long n,m;
int a[100010],b[100010];
int main()
{
    cin>>n>>m;
    long long ans=0;
    for(int i=1;i<=n;i++)
     {
         cin>>a[i]>>b[i];
         ans+=abs(a[i]-b[i]);
     }
     a[n+1]=m;
     b[n+1]=0;
     sort(a+1,a+n+2);
     sort(b+1,b+n+2);
     for(int i=1;i<=n+1;i++)
     {
      ans+=abs(a[i]-b[i]);     
     }
     cout<<ans<<endl;
}
```

---

## 作者：dolphin (赞：7)

这道题值得好好想一会

我们通过对一些小数据的手算，以及对于每段路程的拆分，可以发现：

1.每个st对应的ed这段路程无论如何都要算上

2.额外还要计算的一段路程，就是“切换”费用

什么是切换费用呢？

我们知道可能会有这样的位置st，到达该位置时，把已经在车上的牛 i 扔下去，载上该处的牛 j 并将它运到其终点ed再回来把牛 i 载上

那么我们就需要再加上每一对abs(ed-st)的和

具体实现，我们需要在st、ed中再加上终点m，起点0,

但是要注意的是，0加到ed里，m加到st里

原因在于我们需要从起点0走到最近的st，从最远的ed走到m

所以0对应的就是min\_st，0必然在ed里的第一个；m也一样

最后将st，ed排序，枚举累加即可

附上代码：


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=100010;
int n,m,st[N],ed[N];
long long ans=0;
int read(){
    int sum=0;
    char ch=getchar();
    while (ch<'0'||ch>'9')
        ch=getchar();
    while (ch>='0'&&ch<='9'){
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum;
}
int main(){
    n=read();
    m=read();
    for (int i=1;i<=n;i++){
        st[i]=read();
        ed[i]=read();
        ans+=abs(st[i]-ed[i]);
    }
    st[n+1]=m;//最远的ed开到m  
    ed[n+1]=0;//0开到最近的st  
    sort(st+1,st+n+2);
    sort(ed+1,ed+n+2);
    for (int i=1;i<=n+1;i++)
        ans+=abs(ed[i]-st[i]);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：故事和酒 (赞：3)

这题的标签为什么是SPFA.....

完全是快排的节奏啊

其实弄懂方法就很简单

拿样例来说

2 10
0 9
6 5
先把必做的加起来:9-0  +  6-5=10

因为要回到终点

因此
0 9
6 5
10 0（注意！！10放左边当作起点，0当作终点，至于为什么会这样，大家慢慢领悟）

qsort（快排的原因：必走的：0——5，6——9，快排一遍恰好把剩下的5——6，9——10算出来）

0 0
6 5
10 9
因此 6-5+10-9=2（这一段是额外的答案）

最后10+2=12

宾果^\_^


最后贴个代码

```cpp
var
i,n,m:longint;
ans:qword;
a,b:array[0..100000]of longint;
procedure qsort1(l,r: longint);
var
i,j,x,y: longint;
begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           qsort1(l,j);
         if i<r then
           qsort1(i,r);
end;
 procedure qsort2(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=b[(l+r) div 2];
         repeat
           while b[i]<x do
            inc(i);
           while x<b[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=b[i];
                b[i]:=b[j];
                b[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           qsort2(l,j);
         if i<r then
           qsort2(i,r);
      end;
begin
   readln(n,m);
   ans:=0;
   for i:=1 to n do
    begin
     readln(a[i],b[i]);
     ans:=ans+abs(a[i]-b[i]);
    end;
   a[n+1]:=m;
   b[n+1]:=0;
   qsort1(1,n+1);
   qsort2(1,n+1);
   for i:=1 to n+1 do
     begin
       ans:=ans+abs(a[i]-b[i]);
     end;
    writeln(ans);
end.

```

---

## 作者：Canophia (赞：3)

```pascal
type
 arr=array [1..1000000] of longint;
var
 a,b:arr;
 m,n,i:longint;
 ans:int64;//必须要int64
procedure sort(l,r:longint);
var
 p,mid,i,j:longint;
begin
 i:=l;
 j:=r;
 mid:=a[(l+r) div 2];
 repeat
  while a[i]<mid do
   inc(i);
  while a[j]>mid do
   dec(j);
  if i<=j then
  begin
   p:=a[i];
   a[i]:=a[j];
   a[j]:=p;
   inc(i);
   dec(j);
  end;
 until i>j;
 if i<r then
  sort(i,r);
 if l<j then
  sort(l,j);
end;
procedure qsort(l,r:longint);
var
 p,mid,i,j:longint;
begin
 i:=l;
 j:=r;
 mid:=b[(l+r) div 2];
 repeat
  while b[i]<mid do
   inc(i);
  while b[j]>mid do
   dec(j);
  if i<=j then
  begin
   p:=b[i];
   b[i]:=b[j];
   b[j]:=p;
   inc(i);
   dec(j);
  end;
 until i>j;
 if i<r then
  qsort(i,r);
 if l<j then
  qsort(l,j);
end;
begin
 readln(n,m);
 ans:=0;
 for i:=1 to n do
 begin
  readln(a[i],b[i]);
  ans:=ans+abs(b[i]-a[i]);
 end;
 a[n+1]:=m;
 b[n+1]:=0;
 sort(1,n+1);
 qsort(1,n+1);
 for i:=1 to n+1 do
  ans:=ans+abs(b[i]-a[i]);
 writeln(ans);
 readln;
end.
```
···
水题一道，就是把必须要走的算出来，然后再算切换方式最优即可


---

## 作者：⚡current⚡ (赞：1)

我觉得这是一道值得一做的好题

其他题解里说的很清楚了，本题要求的**总路程**由 每头牛必走的路程 和 从终点到起点接牛的额外距离 组成，而**必走路程**对每道题是不变的，而**额外距离**等于每一对 $abs(en-st)$ 之和，这个值在 $en$ 和 $st$ 都从小到大排序时最小(都从大到小或是一些其他排序是等价的)。

但别的题解都没有较清楚地证明这条结论的正确性，以下是我yy出来的一个证明，有错请指出：

**step1:**

$|a-c|+|b-d| <= |a-d|+|b-c|\;(a<b, c<d)$，只要用绝对值的几何意义类讨论一下，很容易就能证出来。

不妨令 $en$ 由小到大排序，由上述性质可知，每次交换满足 $st_i < st_j, i < j$(类似逆序对) 的一对 $st$ 后，**额外距离**不会变小。

**step2:**

将 $st$ 由小到大排序后，进行若干次上述交换后可以得到 $st$ 全排列中的任意一种。

每次找到没有排好的最小的(同时也一定是最前面的)一个 $st$ ，将它与下一个未排好的 $st$ 交换若干次(一定大于它，因为是从小到大排序的)，直到它到达它的目标位置，那么这样之后所有剩下的未排好的 $st$ 的相对位置不变，仍从小到大排序。

下面给一个例子，方便理解:

将 $\{1, 2, 3, 4, 5\}$， 变为 $\{5, 4, 2, 1, 3\}$

$1\leftrightarrow2, 1\leftrightarrow3, 1\leftrightarrow4$，得到 $\{2,3,4,1,5\}$

$2\leftrightarrow3, 2\leftrightarrow4$ ，得到 $\{3,4,2,1,5\}$

$3\leftrightarrow4,3\leftrightarrow5$，得到 $\{4,5,2,1,3\}$

最后，$4\leftrightarrow5$，得到 $\{5, 4, 2, 1, 3\}$

使用这种方法，可以由从小到大排序的 $st$ 经过若干次上述操作得到它的全排列，而由**step1**可知，每一次这样的操作后**额外距离**只会变大或不变，所以 $st$ 由大到小排序时，**额外距离**取到最小值，即**总路程**取到最小值，证毕！

P.S. 记得把 $0$ 加入 $en$，把 $m$ 加入 $st$，别忘开 $long long$，别忘了取绝对值。

$CODE\downarrow$

~~~c++
#include<math.h>
#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 100005;
int st[MAXN], en[MAXN];
ll ans;

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d", st+i, en+i);
		ans += abs(en[i] - st[i]);
	}
	st[0] = m;
	en[0] = 0;
	sort(st, st+n+1);
	sort(en, en+n+1);
	for(int i = 0; i <= n; ++i)
		ans += abs(en[i] - st[i]);
	printf("%lld", ans);
	return 0;
}
~~~

---

## 作者：king_xbz (赞：1)

这是一道不错的贪心题。我们分两步贪心。

step1：我们知道出租车的最短路程一定大于等于所有的起点到终点距离。

step2：走一段额外的距离，即当前最小的起点到终点的距离。

接下来我们就可以求解了。

作为一个C++选手，一直想去了解一下本源C语言，正好借此机会，和大家一起了解一下C语言的一些特性及函数。（这是和已有的3篇C++2篇PASCAL的区别）

C语言评测已过：[点击查看](https://www.luogu.com.cn/record/30176719)

首先我们需要用到C语言的快排函数————qsort，不同于C++的sort，这个函数需要我们自己写比较函数
```cpp
int cmp(const void* aa,const void* bb)
{
    int* a=(int*)aa;
    int* b=(int*)bb;
    return *a-*b;
}
```
然后就是qsort了
```cpp
qsort(a,n+1,sizeof(a[0]),cmp);
qsort(b,n+1,sizeof(b[0]),cmp); 
```
忘了说了，我们需要头文件：
```cpp
#include<stdlib.h>
```
这便是这篇代码跟别的代码最大的区别；
最后上完整代码
```cpp
#include<stdio.h>//啥都需要
#include<stdlib.h>//qsort函数需要
#include<math.h>//abs函数需要
long long n,m,ans;
long long a[1000001],b[1000001];//不开long long40分
int cmp(const void* aa,const void* bb);
int main()
{
    scanf("%lld%lld",&n,&m);
    for(long long i=0;i<n;i++) 
    scanf("%lld%lld",&a[i],&b[i]),ans+=abs(b[i]-a[i]);//所有的起点到终点直接距离。
    a[n]=m,b[n]=0;
    qsort(a,n+1,sizeof(a[0]),cmp);
    qsort(b,n+1,sizeof(b[0]),cmp); //两个排序
    for(long long i=0;i<n+1;i++) 
    ans+=abs(b[i]-a[i]);//记录当前最小的起点到终点的距离。
    printf("%lld\n",ans);//输出后换行好习惯
}

int cmp(const void* aa,const void* bb)
{
    int* a=(int*)aa;
    int* b=(int*)bb;
    return *a-*b;
}
```
看来C语言的确很有意思啊，这也是我第一次去探索，希望管理给过。

祝大家ac愉快

---

## 作者：MikeC (赞：1)

### 分析

设总路程为 $s$，载人路程为 $b$，空载路程为 $e$，易得 $s=b+e$。又由 $s_i$ 和 $t_i$ 的定义可得，$b=abs(s_i-t_i)$，所以 $s=abs(s_i-t_i)+e$。此时我们就将问题转化成了求 $e$ 即空载路程的最小值。

如图1，我们首先向 $ans$ 添加 $b$ 即 $abs(s_i-t_i)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/rrw44px0.png)

然后我们利用贪心的思想来解决 $e$ 的问题，我们首先通过观察得到 $e$ 的最优解为图中的三段距离，然后我们很容易发现这是通过每个终点和离其最近的起点得到的，所以如图2，我们只需要让程序将 $0$ 看作终点，将 $m$ 看作起点，再进行上述匹配即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/5yvsh1te.png)

### 代码

``````cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[100001],b[100001],ans;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		ans+=abs(b[i]-a[i]);
	}
	a[0]=m,b[0]=0;
	sort(a,a+1+n);
	sort(b,b+1+n);
	for(int i=0;i<=n;i++){
		ans+=abs(b[i]-a[i]);
	}
	printf("%lld",ans);
	return 0;
}
``````



---

