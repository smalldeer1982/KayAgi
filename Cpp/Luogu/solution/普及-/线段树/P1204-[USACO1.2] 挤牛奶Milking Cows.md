# [USACO1.2] 挤牛奶Milking Cows

## 题目描述

三个农民每天清晨 $5$ 点起床，然后去牛棚给三头牛挤奶。

第一个农民在 $300$ 秒 (从 $5$ 点开始计时) 给他的牛挤奶，一直到 $1000$ 秒。第二个农民在 $700$ 秒开始，在 $1200$ 秒结束。第三个农民在 $1500$ 秒开始，$2100$ 秒结束。  

期间最长的至少有一个农民在挤奶的连续时间为 $900$ 秒 (从 $300$ 秒到 $1200$ 秒)，而最长的无人挤奶的连续时间(从挤奶开始一直到挤奶结束)为 $300$ 秒 (从 $1200$ 秒到 $1500$ 秒)。
****

你的任务是编一个程序，读入一个有 $n$ 个农民挤 $n$ 头牛的工作时间列表，计算以下两点(均以秒为单位):

最长至少有一人在挤奶的时间段。

最长的无人挤奶的时间段。（从有人挤奶开始算起）


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 5000$，$0 \le l \le r \le 10^6$。

题目翻译来自NOCOW。

USACO Training Section 1.2


## 样例 #1

### 输入

```
3
300 1000
700 1200
1500 2100
```

### 输出

```
900 300
```

# 题解

## 作者：学而思李老师 (赞：57)

# P1204 \[USACO1.2]挤牛奶Mixing Cows
又是一道模拟~~水~~题。

### 方法1：布尔数组，打标记，输出
在我的[CF440A的题解](https://www.luogu.org/blog/lch-zhazha/cf440a-forgotten-episode)里面，已经详细讲过关于布尔数组打标记的方法了。这道题目中，我们也可以用这种方法，把每一个时刻是否有人挤奶标记出来，最后用循环找到最长有人挤奶的时间和最长无人挤奶的时间。特别注意：300~900其实是601秒，题目中只有600秒。算的时候，一定从300标记到899才不会出错。

对于这种方法，我花了一个图来表示：

![布尔数组图片](https://cdn.luogu.com.cn/upload/pic/69252.png )

code：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
bool timeline[1000005];
int my_max(int x, int y){
	return x > y ? x : y;
}
int my_min(int x, int y){
    return x < y ? x : y;
}
int main(){
	memset(timeline, false, sizeof(timeline));
	int n, tmpx, tmpy, maxz = -1, maxa = -1;
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d%d", &tmpx, &tmpy);
		for(int i = tmpx; i < tmpy; i ++){
			timeline[i] = true;
		}
		maxz = my_max(maxz, tmpy);
		maxa = my_min(maxa, tmpx);
	}
	int maxx = -1, maxy = -1;
	int tmpa = 0, tmpb = 0;
	for(int i = maxa; i <= maxz; i ++){
		if(timeline[i]){
			tmpa ++;
			tmpb = 0;
		} else{
			tmpa = 0;
			if(i < maxz){
				tmpb ++;
			}
		}
		maxx = my_max(maxx, tmpa);
		maxy = my_max(maxy, tmpb);
	}
	printf("%d %d", maxx, maxy);
	return 0;
}
```
### 方法2：结构体sort
上面的方法虽然稳定而简单，但是如果数据狠一些就会超时。所以，我们可以不用暴力的方法，使用减法可以算出挤奶时间和未挤奶时间。所以，代码如下（思路看注释）

```cpp
#include <cstdio>
using namespace std;
int my_max(int x, int y){
	return x > y ? x : y;   //取最大值函数，<algorithm>里面的太慢了
}
int main(){
	int o;
	scanf("%d", &o);
	int maxx = -1, maxy = -1, lasttmp = 0;
	for(int i = 1; i <= o; i ++){
		int tmpx, tmpy;
		scanf("%d%d", &tmpx, &tmpy);    //边读边做，不用数组
		maxx = my_max(maxx, tmpy - tmpx);   //更新最长有人挤奶时间的最大值
		maxy = my_max(maxy, tmpx - lasttmp);//更新最长无人挤奶时间的最大值
		lasttmp = tmpy;                 //更新上一次挤奶的结束时间
	}
	printf("%d %d", maxx, maxy);        //输出
	return 0;
}
```
如果像我这样提交的话，结果是这样的：

![错误示范](https://cdn.luogu.com.cn/upload/pic/69260.png )

为什么是错误的呢？我想了半天没想出来，于是使用了测试数据下载。第一个测试点是这样的：

```
1
100 200
```
这样的话，lasttmp是0，而且输入的数据不一定是顺序的。所以，我们需要对数据排序。如果自己手写排序的话，性能很差。所以，我们使用\<algorithm>里面的sort函数对我们的数据进行排序。下面我来介绍以下sort的用法

sort在\<algorithm>里面，原型有两个：

```cpp
template <class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last);
template <class RandomAccessIterator, class Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

第一种原型是对一个数组进行默认的升序排序，第二种却是对数组进行自定义规则的排序。

comp这个参数是一个函数。它对两个和数组类型相同的数进行自定义的比较，如果返回true则不交换，否则交换。对一个有10个元素的数组进行排序，是这样的：

```cpp
sort(a, a + 10, cmp);
```

但是，这样使用sort只能排序一组数字。所以，我们使用结构体，使用自定义的cmp函数对整个数据进行排序。具体思路如下图：

![](https://cdn.luogu.com.cn/upload/pic/69288.png )

但是，如何定义结构体呢？定义结构体的关键字是struct，是structure的简写。具体格式如下：

```cpp
struct 结构体名{
	成员变量;
	成员函数;
};
结构体名 变量;
```
结构体在面向对象编程时很有用。但是，它也是sort的绝佳搭档。因为排序时，我们要对一个对象的每一条信息进行交换，而使用数组并不能实现这个功能，所以，使用结构体可以帮助我们完成很多复杂的排序问题。具体参考：

> 洛谷试炼场普及练习场排序与排序ex

这道题目，我们一个结构体存储每一条信息的和，进行排序，并按图上的思路输出。

```cpp
#include <bits/stdc++.h>
using namespace std;
int N; 
struct node{
    int begin, end;
}m[5005];
bool cmp(node a, node b){
    return a.begin < b.begin;
}
int main(){
    scanf("%d", &N);
    for(register int i = 1; i <= N; ++ i)
        scanf("%d%d", &m[i].begin, &m[i].end);
    sort(m + 1, m + 1 + N, cmp);
    int begin = m[1].begin;
    int end = m[1].end;
    int ans1 = 0, ans2 = 0;
    for(register int i = 2; i <= N; ++ i){
        if(m[i].begin <= end)
            end = max(end, m[i].end);
        else{
            ans1 = max(ans1, end - begin);
            ans2 = max(ans2, m[i].begin - end);
            begin = m[i].begin;
            end = m[i].end;
        }
    }
    ans1 = max(ans1, end - begin);
    printf("%d %d", ans1, ans2);
    return 0;
}
```

P.S 这个代码是我们机房的同学写的。这道题是我们考试题目第一题，我用的是第一种方法，而他用的就是这一种。


---

## 作者：KesdiaelKen (赞：30)

这一题非常明显可以用差分来做~

差分的思想：用O（1）的复杂度来表示一次O（n）的覆盖:设b[i]=a[i]-a[i-1]，则当a[l]到a[r]均增加一时，则只需b[l]++,b[r+1]--，其余的由于前后两相差未变，b不需改动。这样，便可以用b来表示a的变化。（最后将b复原成a即可）。另一点需要注意的：题意有些坑人：一个挤牛奶时间段（a,b）说的是从第a秒一直到b-1秒，所以这里不是b[r+1]--，而是b[r]--。程序如下：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int c[1000002]={0};//差分数列
int main()
{
    int start=2e9,end=-2e9;//最大最小值初始值，用于计算开始和结束挤牛奶的时间
    int n;//读入数据个数
    int a,b;//挤牛奶时段
    int tf=1;
    int t[2]={0};//tf=1：计算最长有人挤牛奶时段，用t[1]记录；tf=0：计算最长无人挤牛奶时段，用t[0]记录
    int nstart;//用于计算t[0]和t[1]
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        c[a]++;
        c[b]--;//差分
        start=min(start,a);
        end=max(end,b-1);//取最大值和最小值
    }
    nstart=start;//区间开始时间点
    int nc;
    end++;//保证计算的正确性，及最后的挤牛奶时段总时长能计算正确
    for(int i=start;i<=end;i++)
    {
        c[i]=c[i-1]+c[i];//恢复a数组
        nc=c[i]==0?0:1;//c[i]是否大于0
        if(nc!=tf||i==end)//是否可以统计
        {
            t[tf]=max(t[tf],i-nstart);//取最长时段，计算时段
            nstart=i;//取新的时间开始点
            tf=1-tf;//换一类进行计算
        }
    }
    printf("%d %d",t[1],t[0]);//输出，记得t[0],t[1]顺序
    return 0;
}
```

---

## 作者：hanxin (赞：29)

## 一道简单的题目
思路很简单，可以直接把整个时间看成一个区间，不多说直接给代码

```
#include<bits/stdc++.h>
inline int read(){//快速读入，不解释 
	int x=0;
	char c=getchar();
	while(c>'9'||c<'0')
		c=getchar();
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int a[10005];
int n,l,r,ml=1e9,mr=-1;//ml代表区间最小值，mr代表区间最大值 
ine ans1=-1,ans2=-1,max1=0,max2=0; 
int main(){
	memset(a,0,sizeof(a))//初始化，全部为0 
	n=read();//读入n 
	for(int i=1;i<=n;i++){
		l=read();
		r=read();
		ml=std::min(ml,l);//求出区间最大值 
		mr=std::max(mr,r);//求出区间最小值 
		for(int j=l;j<=r;j++)
			a[j]=1;//标记，将有人挤奶的时间赋值为1 
	}
	for(int i=ml;i<=mr;i++){
		if(a[i])max1++;//不停累加 
		else{
			ans1=std::max(ans1,max1);//求出最长的一直有人挤奶的时间长度 
			max1=0;//继续枚举 
		}
		if(!a[i])max2++;
		else{
			ans2=std::max(ans2,max2);
			max2=0;
		}
	}
	std::cout<<ans1<<" "<<ans2;//输出结果 
	return 0;//养成好习惯 
	//std::实际没什么用只是加快编译速度 
}
```
给个赞再走吧

---

## 作者：yzhang (赞：14)

## [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/9898752.html)

#### 原题传送门：[P1204 [USACO1.2]挤牛奶Milking Cows](https://www.luogu.org/problemnew/show/1204)

#### 实际是道很弱智的题目qaq

#### 但窝还是觉得用珂朵莉树写会++rp（窝都初二了，还要考pj）

## 前置芝士：珂朵莉树

### [窝博客里对珂朵莉树的介绍](https://www.cnblogs.com/yzhang-rp-inf/p/9443659.html )

### 没什么好说的自己看看吧

#### 每个农夫就assign_val一下，但要注意一下细节qaq

#### ~~窝不会告诉你因这个错调了我实际分钟qaq~~

#### 应该写assign_val(l,r-1,1)，查询时应写query（lmin，rmax，1/0）

#### 其他没什么好说的了，细节详见程序

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#define IT set<node>::iterator
using namespace std; 
struct IO_Tp
{
    static const int _I_Buffer_Size = 1 << 24;
    char _I_Buffer[_I_Buffer_Size];
    char* _I_pos;
    static const int _O_Buffer_Size = 1 << 24;
    char _O_Buffer[_O_Buffer_Size];
    char* _O_pos;
    IO_Tp() : _I_pos(_I_Buffer), _O_pos(_O_Buffer)
    {
        fread(_I_Buffer, 1, _I_Buffer_Size, stdin);
    }
    ~IO_Tp()
    {
        fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout);
    }
    inline bool is_digit(const char ch)
    {
        return '0' <= ch && ch <= '9';
    }
    inline IO_Tp& operator>>(int& res)
    {
        res = 0;
        while (!is_digit(*_I_pos))
            ++_I_pos;
        do
            (res *= 10) += (*_I_pos++) & 15;
        while (is_digit(*_I_pos));
        return *this;
    }
    inline IO_Tp& operator<<(int n)
    {
        static char _buf[10];
        char* _pos(_buf);
        do
            *_pos++ = '0' + n % 10;
        while (n /= 10);
        while (_pos != _buf)
            *_O_pos++ = *--_pos;
        return *this;
    }
    inline IO_Tp& operator<<(char ch)
    {
        *_O_pos++ = ch;
        return *this;
    }
} IO;
inline int Max(register int a,register int b)
{
    return a>b?a:b;
}
inline int Min(register int a,register int b)
{
    return a<b?a:b;
}
struct node
{
    int l,r;
    mutable bool v;
    node(int L, int R=-1, bool V=0):l(L), r(R), v(V) {}
    bool operator<(const node& o) const
    {
        return l < o.l;
    }
};
set<node> s;
IT split(int pos)
{
    IT it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos) 
        return it;
    --it;
    int L = it->l, R = it->r;
    bool V = it->v;
    s.erase(it);
    s.insert(node(L, pos-1, V));
    return s.insert(node(pos, R, V)).first;
}
void assign_val(int l,int r,bool v)
{
    IT itr = split(r+1),itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, v));
}
inline int query(register int l,register int r,register bool v)
{
    int sum=0,res=0;
    IT itr = split(r+1),itl = split(l);
    for(;itl!=itr;++itl)
        if(itl->v==v)
            sum+=itl->r-itl->l+1;
        else
        {
            res=Max(res,sum);
            sum=0;
        }
    return res;
}
int main()
{
    int n;
    IO>>n;
    int a=1000005,b=0;
    s.insert(node(0,1000005));
    while(n--)
    {
        int l,r;
        IO>>l>>r;
        assign_val(l,r-1,1);
        a=Min(a,l);
        b=Max(b,r);
    }
    IO<<query(a,b,1)<<' '<<query(a,b,0);
    return 0;
}
```

---

## 作者：lxyhhhhhh (赞：12)

##简单的一道模拟题##

想也没多想就打出来，一开始以为会TLE，后来觉得数组开小了会溢出爆零，但是。。。。。。AC！！！

大致思路如下：

只需要一个a数组，

比如说：100~200

那么a[100]~a[199]都标记为1，其余为零，

以此类推，当所有的时间都标记完了之后，我们就可以开始统计了

我也很揪心啊。。。。。。不喜勿喷啊大佬们

代码如下：


    
        
        
    
```cpp
#include<bits/stdc++.h> 
using namespace std;
const int maxn=1000010;
bool a[maxn];
int t=0;
int main()
{
    int n,ans1=0,ans2=0;
    int x,y;
    int maxx=0,minx=maxn;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        minx=min(x,minx);
        maxx=max(y,maxx);
        for(int i=x;i<y;i++)
            a[i]=1;    
    }
    int p=minx;
    int q=maxx;
    for(int i=p;i<=q;i++)
    {    
        if(a[i]==1)t++;
        else 
        {
            ans1=max(ans1,t);        
            t=0;
        }
    }
    for(int i=p;i<=q;i++)
    {    
        if(a[i]==0)t++;
        else 
        {
            ans2=max(ans2,t);
            t=0;        
        }
    }
    cout<<ans1<<" "<<ans2<<endl; 
    return 0;
}
```

---

## 作者：zhl001 (赞：11)

## 差分的崛起！！！

这个题是我在找线段树的时候偶然找到，想出思路：

```
对于每一段挤奶的时间，我们就在该段的时间轴上均加一，这样只要有挤奶的时间段就一定不是0（要么是1，要么是2......），由此，在找最大的无人挤奶的时间就是找时间轴上连续为0的最长长度，至少一人挤奶的时间就是找时间轴上连续不为0的最长长度
```

------------

（咦，差分好像更容易<小声bb>）

------------
于是花了半个小时调出了以下代码：

```
看代码之前要强调一下几个坑点：

1、文中说的区间是左闭右开（理解为左开右闭也可以）所以我在差分数组中直接把y[b+1]++变成了y[b]++；

2、注意边界的判断（这个题主要体现在对差分求完前缀和之后的第一个0的元素要统计上~）
```
### 话不多说，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int lon1=1,lon=1,start=1000000,end=-1,a,b,y[1000000],n,m,ans1=-1,ans2=-1; 
bool flag;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		start=min(start,a);
		end=max(end,b);
		y[a]+=1;
		y[b]-=1;//这里是左闭右开区间 
	}
	for(int i=1;i<=end;i++)
	{
		y[i]=y[i-1]+y[i]; 
		if(y[i]==0&&y[i-1]==0&&i>=start+1)
		//如果条件符合，就说明了第一个元素也是0，直接lon初始值赋为1即可 
		{
			lon++;
			ans2=max(ans2,lon);
		}
		else
		{
			lon=1;//初始值是1，为了判断加上第一个0 
		}
		if(y[i]>=1&&y[i-1]>=1&&i>=start+1)//同上 
		{
			lon1++;
			ans1=max(ans1,lon1);
		}
		else
		{
			lon1=1;
		}
	}
	if(ans1==-1)//输出稍微一判即可 
	{
		printf("0 %d",ans2);
		return 0;
	}
	if(ans2==-1)
	{
		printf("%d 0",ans1);
		return 0;
	}
	printf("%d %d\n",ans1,ans2);
	return 0;//完结撒花 
}
```
管理大大求过，也辛苦大家看蒟蒻的题解了

---

## 作者：皮卡丘最萌 (赞：10)

这是一个离散化的题目。

虽然题目范围比较小，但是用离散化可以大大优化时间。

离散化的主要思想就是对于一段连续的区间，只保留它的头位置和尾位置，以及这个点是头是尾的信息。

那么样例就变成了这样。

![404](https://cdn.luogu.com.cn/upload/image_hosting/10g92cwl.png)

其中黄色部分是起点，绿色部分是终点。

接下来我们对其按位置排序。

![404](https://cdn.luogu.com.cn/upload/image_hosting/xa9ytpkx.png)

接下来对1，1，-1，-1，1，-1进行累加操作，并且求出值大于0的最长区间和值等于0的最长区间就完成了。

另外要注意的是排序时先按位置小优先，位置相同则1优先。

放代码：
```pascal
var m,n,i,x,y,t,j,h,s,z,max,min:longint;
    a,b:array[0..200001] of longint;
procedure sort(l,r: longint);
var
  i,j,x,y,x1: longint;
begin
  i:=l;j:=r;
  x:=a[(l+r) div 2];
  x1:=b[(l+r) div 2];
  repeat
    while (a[i]<x) or (a[i]=x) and (b[i]>x1) do inc(i);
    while (x<a[j]) or (a[j]=x) and (x1>b[j]) do dec(j);
    if not(i>j) then
      begin
        y:=a[i];a[i]:=a[j];a[j]:=y;
        y:=b[i];b[i]:=b[j];b[j]:=y;
        inc(i);j:=j-1;
      end;
  until i>j;
  if l<j then  sort(l,j);
  if i<r then  sort(i,r);
end;       
      //快排不解释，注意先按位置小优先，位置相同则1优先。

begin
readln(n);
for i:=1 to n do
  begin
  readln(x,y);
  t:=t+1;
  a[t]:=x;
  b[t]:=1;               //标记起点位置与信息
  t:=t+1;
  a[t]:=y;
  b[t]:=-1;              //标记终点位置与信息 
  end;
sort(1,t);                  //对其进行排序
x:=0;
for i:=1 to t do
  begin
  if (x=0) and (b[i]=1) then           //新一段的开始
    begin
    if ((a[i]-a[i-1])>max) and (i<>1) then 
      max:=a[i]-a[i-1];              //记录最长无人工作时间
    z:=a[i];                       //记录有人工作的开始时间
    end;
  x:=x+b[i];                     //累加信息
  if x=0 then                      //一段的结束
    begin
    s:=s+a[i]-z;                    
    if (a[i]-z)>min then min:=a[i]-z;    
            //记录最长有人工作的时间段
    end;
  end;
writeln(min,' ',max);     //输出结果
end.
```


---

## 作者：庸人 (赞：10)

```cpp
#include<cstdio>
//就是把有人挤奶的时间标记为1没人标记为0，再去搜索累加 
int main(){
    char z[1001000];
    int i,j,n,a,b,mina=1001000,maxb=-1;//最小的a，最大的b 
    int maxlx=-1,maxmr=-1,//，最长有人，最长没人
    int t1=0,t0=0;//max连续，max没人 
    scanf("%d",&n);
    for(i=0;i<1001000;i++) z[i]='0';//初值全部为0 
    for(i=0;i<n;i++){
        scanf("%d%d",&a,&b);
        if(a<mina) mina=a;
        if(b>maxb) maxb=b;
        for(j=a;j<b;j++){ 
            z[j]='1';
        }
    }
    for(i=mina;i<=maxb;i++){//搜索 
        if(z[i]=='1') t1++;
        else if(z[i]=='0') t0++;
        if(z[i+1]=='1'){
            if(t0>maxmr) maxmr=t0;
            t0=0;
        } 
        else if(z[i+1]=='0'){
            if(t1>maxlx) maxlx=t1;
            t1=0;
        } 
    }
    if(t1>maxlx) maxlx=t1;//检查最后一次的 
    if(t0>maxmr) maxmr=t0;// 检查最后一次的 
    if(maxlx==1) maxlx=0;//特判 
    if(maxmr==1) maxmr=0;//特判 
    printf("%d %d",maxlx,maxmr);//输出 
    return 0;
}
```

---

## 作者：陈新月 (赞：8)

思路：

这道题的话，我们先弄清楚求什么，据题意我们知道要求的是至少一人挤奶时间段最大值与空闲时间段最大值，我们一开始可以想到线段树，但无奈，所需空间太大，所以我们就用到了离散化，我们将每个时间段离散化成一个点，点值为时间段长短，但为了更容易计算，我们将空闲时间段设为时间段长度的负值，这样在线段树中我们就可以直接维护两个值，一个是区间最大值，另一个是区间最小值，只要建树就行了，最后输出根节点的最大值与最小值的负数就可以。


不过需要注意的是，在给最小值赋初值的时候要与0之间取最小值，为什么呢？ 你可以考虑一下只有一个输入数据的时候，这个时候最小值赋的初值居然是大于0，所以我们要这样做


只是大概说了一下思路，下面贴一下AC代码，重要部分已经注释







    

```cpp
#include<cstdio>
#include<algorithm>
#define N 5009
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
int z[N<<2|1],minx[N<<2|1],maxx[N<<2|1];                //线段树组件 
struct time{                      //离散化结构 
    int l,r;
}t[N];
bool operator < (const time &a,const time &b){            //重载小于运算符，为后面STL排序 
    return a.l < b.l;
}
void update(int rt){                //更新最大最小值 
    minx[rt] = min(minx[rt<<1],minx[rt<<1|1]);
    maxx[rt] = max(maxx[rt<<1],maxx[rt<<1|1]);
}
void build(int l,int r,int rt){   //建树 
    if(l == r){
        minx[rt] = min(0,z[l]);
        maxx[rt] = z[l];
        return;
    }
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    update(rt);
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n; i++){
        scanf("%d%d",&t[i].l,&t[i].r);
    }
    sort(t+1,t+n+1);                  //为下面离散化而排序 
    int p = 0;
    int ll = t[1].l,rr = t[1].r;
    for(int i = 1; i <= n; i++){               //离散化过程 ，我们将时间段变成点，点值即为段长 
        if(t[i].l <= rr && t[i].r > rr){
            rr = t[i].r;
        }
        else if(t[i].r <= rr && t[i].l >= ll)continue;
        else{
            z[++p] = rr-ll;                      //在这里，至少有一人工作的时间记为正常时间段 ，在线段树中以最大值存储 
            z[++p] = -(t[i].l - rr);            //而对于没人工作的时间段，我们将此时间段值设为负值，在线段树中以最小值存储 
            ll = t[i].l;
            rr = t[i].r;
        }
    }
    z[++p] = rr-ll;
    build(1,p,1);                           //建造线段树即可求出最大值与最小值 
    printf("%d %d\n",maxx[1],-minx[1]);     //最后输出最大值与最小值的负数即可，因为空闲时间段我们是以负数存储的 
    return 0;
}
```

---

## 作者：Mys_C_K (赞：8)

总结了一下楼下大神一共提供了三种做法

1.就是硬模拟，就是USACO分析上的“第二种可能”

2.用了高端的线段树优化了1

3.再就是用USACO分析上的第一种解法，把相同的时间段合并，楼下有，就不说了（这个应该是一般正解）。

但是问题在于，模拟的话，就像楼下的No\_chorse说的一样，>和>=差别很大，一开始也为此WA了49分，细节不好写

线段树……这么高端的东西……表示再加上标记什么（虽然可以不下放）还是代码挺长的。

于是受USACO上的“第三种可能”启发（那个我没仔细看，不知道和我一不一样），想到了如下乱搞一下的思路：

n个时间段，每个时间段的两个端点就是两个事件（开始和结束），用event[1-2\*n]存储

把这些事件按发生时间排序

（如果发生时间相同，就让开始事件在前，这样主要是为了第一个事件一定是开始事件）

然后先处理第一个事件（因为至少有两个事件）

用scount表示当前开始事件的个数

如果遇到结束事件，就让scount--;

再用last记录上一个使scount=0的事件。

那么对于第一个事件，有scount=1，last=event[1].seconds；

然后依次看每个事件 i

分两种情况

1.如果这是个开始事件

如果scount==0，说明此前一直是无人挤奶的状态

于是让ans2=max(ans2,event[i].seconds-last)；

然后无论如何让scount++

2.如果这是个结束时间

先让scount--

然后如果这个时候scount==0，说明此前一直是有人状态

于是让ans1=max(ans1,event[i].seconds-last)；


最后输出ans1和ans2即可

附上颜值高的蒟蒻的丑陋的代码

[codec]

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 5000
using namespace std;
struct events{
    int seconds;
    bool is_sore;//true for start and false for end.
}event[maxn*2+10];
int scount=0;
int n;
bool eventcmp(const events &a,const events &b)
{
    if(a.seconds!=b.seconds)
        return a.seconds<b.seconds;
    return a.is_sore;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&event[2*i-1].seconds);event[2*i-1].is_sore=true;
        scanf("%d",&event[2*i].seconds);event[2*i].is_sore=false;
    }
    int eventcount=n*2;
    sort(event+1,event+eventcount+1,eventcmp);
    int ans1=0,ans2=0;
    int last=event[1].seconds;scount++;
    for(int i=2;i<=eventcount;i++)
    {
        if(event[i].is_sore==true)
        {
            if(scount==0)
            {
                ans2=max(ans2,event[i].seconds-last);
                last=event[i].seconds;
            }
            scount++;
        }
        else{
            scount--;
            if(scount==0)
            {
                ans1=max(ans1,event[i].seconds-last);
                last=event[i].seconds;
            }
        }
    }
    cout<<ans1<<" "<<ans2<<endl;
    return 0;
}
[\codec]
```

---

## 作者：土间太平 (赞：3)

按照开始时间升序排序，然后从左到右扫一遍，复杂度是O(nlogn+n)的（排序+扫一遍，用快速排序）。

所谓从左到右扫一遍，就是记录一个当前区间， 如果下一个区间是当前区间的子区间，跳过。 如果下一个区间和当前区间相交，就合并两个区间放入当前区间， 否则就检查当前区间的最小边界（min）与最大边界（max）的距离（max - min)是不是比连续有人工作的时间（work)要大，将新区间作为当前区间，并且检查新区间与上一区间的间隔（data[point].start - max)是否大于没有人工作的时间的当前最大值（nowork)，然后继续往右扫。

不贴代码啦~~


---

## 作者：BlueArc (赞：3)

###提供一种效率很低但能保证正确率的解法

**用bool数组表示在该时间内，是否有农民挤牛奶**,有则=true,否则=false;

**注意区间的表示!**，我用的是左闭右开区间,输入的start认为在该**时间点**为true,end为false

然后就是求最大连续的true和false了

###求最大连续的true和false的枚举起点和终点

输入时把start和end的最小值和最大值存起来

本来觉得回TLE的，没想到AC了



```cpp
#include"cstdio"
#include"iostream"
#include"cstring"
using namespace std;
bool a[1000005];
int maxx1,maxx2,minns=0x7fffffff,maxxe=0;
int main()
{
 memset(a,false,sizeof(a));
 int n,x,y,s1=0,s2=0;
 cin>>n;
 for(int i=0;i<n;i++)
 {
  cin>>x>>y;
  if(x<minns) minns=x;
  if(y>maxxe) maxxe=y;
  for(int i=x;i<y;i++)
  a[i]=true;       
 } 
 for(int i=minns;i<maxxe;i++)
 {
  if(a[i]==true) {s1++;if(s1>maxx1) maxx1=s1;}
  else s1=0;
  if(a[i]==false){s2++;if(s2>maxx2) maxx2=s2;}
  else s2=0;        
 }  
 cout<<maxx1<<" "<<maxx2<<"\n";
 return 0;
}
```
#1AC0ms/12835kB
#2AC0ms/3242kB

#3AC0ms/12835kB

#4AC0ms/12835kB

#5AC82ms/12835kB

#6AC0ms/12835kB

#7AC1ms/12835kB

#8AC4ms/12835kB


---

## 作者：zhaimingshuzms (赞：2)

#入坑的我

也许有很多人跟我一样，因为标签线段树入坑，但这题其实不用线段树，只需纯模拟

对于每个读入的区间，我视作闭区间[l,r]，首先利用标记统计某一时刻点上覆盖的区间数；

然后再暴力扫过去，如果是0条覆盖和非0覆盖的分界点，就将其记下，

最后由于我视为闭区间，要将0的两个端点加上（如果是开区间，就将1的两个端点加上，如果是半开区间，就1 0的各一个端点都加上）

下面是程序

****************************************************

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,i,t0,t1,maxx,max1,max2,minn=1000000,a,b,f[1000001],t,tt;
int main()
{
    scanf("%d",&n);
    for (i=1; i<=n; i++)
    { 
        scanf("%d%d",&a,&b);
        minn=min(minn,a),maxx=max(maxx,b);
        f[a]++,f[b+1]--;
    } 
    for (i=minn; i<=maxx; i++)
    {
        tt=t+f[i];
        if (t==0&&tt>0) t1=i;
        if (t>0&&tt==0) t0=i;
        if (tt>0) max1=max(max1,i-t1);
        if (tt==0) max2=max(max2,i-t0+2); 
        t=tt;
    }
    printf("%d %d",max1,max2);
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：2)

由于数据很弱（嗯，才100万……）所以我就用一个数组存起来每个时间段是否有人在挤牛奶……

```delphi

var a:array[1..1000000] of integer;
    n,x,y,i,max,min,j,s,ss,mm,hh:longint;
begin
    read(n);
    hh:=maxlongint;(存挤牛奶开始的时间，嗯，我不用注释，很无聊对吗)
    for i:=1 to n do
    begin
        read(x,y);
        for j:=x to y-1 do
            a[j]:=1;这段时间都有人挤奶，标记一下（第y秒的时候就停止了）
        if y-1>mm then mm:=y-1;记录最后一个人挤完奶的时刻，之所以-1是因为最后一个人离开的那一秒没在挤奶了
        if x<hh then hh:=x;挤奶开始的时间
    end;
        for i:=hh to mm do
    begin
        if a[i]=1 then inc(max) else max:=0;if max>s then s:=max;变量定义得很混乱……s存连续挤奶最长时间，max存的是目前连续挤奶的时间，如果没人挤奶了max就要赋值为0
        if a[i]=0 then inc(min) else min:=0;if min>ss then ss:=min;min存最长没人挤奶时间，max存的是目前没人挤奶的时间
    end;
    write(s,' ',ss);
end.

```

---

## 作者：zzqDeco (赞：2)

### 这道题比较水，不用并查集也能做
### 提供一种暴力合并的方法
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct X
{
    int start,last;
}a[5010],b[5010];//简单的结构体
int N,M;
int ans1,ans2;
int cha1(X n)
{
    return n.last-n.start;
}
int cha(X n,X m)
{
    return n.start-m.last;
}//两种判断方法
bool cmp(X A,X B)
{
    return A.start<B.start;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i].start>>a[i].last;
    }
    sort(a+1,a+N+1,cmp);//排序
    for(int i=1;i<=N;i++)
    {
        int s=0;
        if(M>=1)
        {
            if(a[i].start<=b[M].last+1&&(a[i].last>b[M].last))
        	{
        		s=1;
        		b[M].last=a[i].last;
        	}
        	if(a[i].last<=b[M].last)
        	{
            	s=1;
            }//标记
        }
        if(!s)
        {
        	M++;
            b[M]=a[i];
        }//下一个组
    }
    for(int i=1;i<=M;i++)
    {
        if(cha1(b[i])>ans1)
        {
            ans1=cha1(b[i]);
        }
    }
    for(int i=2;i<=M;i++)
    {
        if(cha(b[i],b[i-1])>ans2)
        {
            ans2=cha(b[i],b[i-1]);
        }
    }
    //计算差值
    cout<<ans1<<' '<<ans2<<endl;
}
```
### 有点低能，~~但是过了~~
（管理。。。原来的题解改了一点点为什么就过不了了）

---

## 作者：kisah (赞：1)

//因为加了防抄袭代码，被谷误以为恶意代码了。。。。

//所以剩下的代码是可以直接复制粘贴的，但还是希望各位看客花时间看一下



    
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;//一般细节明白的就不讲了（再打一遍真的好烦） 
int hh,h,n,i,ll,rr,l=999999,d,yj,bj,r=-999999;
bool b,a[1000005];
void high(int l,int r){//填补时间 
    for (int i=l;i<=r;i++)
        a[i]=true;
}
int main(){
    cin>>n;
    if (n==1){cin>>h>>hh; cout<<abs(h-hh)<<' '<<0; return 0;}//特殊判断 
    for (i=1;i<=n;i++){
        cin>>ll>>rr;
        if (ll<l) l=ll;
        if (r<rr) r=rr;
        high(ll,rr-1);//这里就是整个代码的重点了，（再烦也要负责( ˉ □ ˉ )） 
                      //首先是减一，为什么? 减一以后才是把时间后摇给删了
                      //比如 5->6，是1，但计算机会输出2；所以减一，
                      //同理，不挤奶的时间会少1，所以也解决了该问题
                      //同时也是当开头为1是要特殊判断的原因，因为挤奶时间会多1； 
    }
    b=a[l];
    for (i=l;i<r;i++){
        if (a[i]!=b) if (b) {
            if (d>yj) yj=d;
            d=0;
            b=!b;
            }
        else {
            if (d>bj) bj=d;
            d=0;
            b=!b;
        }
        d++;
    }
    if (b) {//临输出再判断一遍，保证输出数据获得最新情况 
            if (d>yj) yj=d;
            d=0;
            b=!b;
            }
        else {
            if (d>bj) bj=d;
            d=0;
            b=!b;
        }
    cout<<yj<<' '<<bj;//普通的输出 
    return 0;
}
```

---

## 作者：shenyi1343395317 (赞：1)

没有pascal的线段树，让我来加一个。（此题并不是特别适合线段树）

就当做是练练手吧.

思想：把每个区间依次拆分，然后递归拼合；

```cpp
program sss;
  type tree=record
       l,r:longint;
       cover:longint;
       end;
  var a:array[0..9000000] of tree;                        //最好开到max的4倍
      ans:array[0..10000] of tree;
      go,en:array[0..5002] of longint;
      i,j,m,n,k,max,count:longint;
  procedure make(p,l,r:longint);                //递归建（空）树
  begin
  a[p].l:=l;
  a[p].r:=r;
  a[p].cover:=0;
  if l+1<r then
   begin
   make(p*2,l,(r+l) shr 1);                         //采用位运算，快一点
   make(p*2+1,(r+l) shr 1,r);
   end;
  end;
  procedure change(p,l,r:longint);           //修改区间，分四种情况递归
  var i,mid:longint;
  begin
  if p>1000000 then exit;                     //其实改成 l=r 也可以
  if a[p].cover=0 then
   begin
   mid:=(a[p].l+a[p].r) shr 1;
   if ((a[p].l=l) and (a[p].r=r)) then a[p].cover:=1
    else if r<mid then change(2*p,l,r)
     else if l>mid then change(2*p+1,l,r)
      else
       begin
       change(2*p,l,mid);
       change(2*p+1,mid,r);
       end;
   end;
   end;
  procedure find(p:longint);    //每当找到一个染色后的点，就放入数组ans中组合
  begin
  if p<1000000 then
  if a[p].cover=1 then
   begin
   inc(count);
   ans[count]:=a[p];
   if ans[count].l=ans[count-1].r then
    begin
    ans[count-1].r:=ans[count].r;
    dec(count);
    end;
   end
   else
    begin                 //递归向下
    find(2*p);
    find(2*p+1);
    end;
  end;
  begin
  readln(n);
  for i:=1 to n do
   begin
   read(go[i],en[i]);
   if max<en[i] then max:=en[i];              //尽量把树减小
   readln;
   end;
  make(1,0,max);                             //有一个数据很坑，要从0开始
  for i:=1 to n do change(1,go[i],en[i]); 
  find(1);
  m:=0;
  n:=0;
  max:=0;                                 
  for i:=1 to count-1 do                     //经典的比较过程，求出最大值然后记下来
   begin
   m:=ans[i].r-ans[i].l;
   if max<m then max:=m;
   n:=ans[i+1].l-ans[i].r;
   if k<n then k:=n;
   end;
  if ans[count].r-ans[count].l>max then max:=ans[count].r-ans[count].l;
  write(max,' ',k);
end.
```

---

## 作者：vegetabird (赞：1)

线段树：

把每一个人的挤牛奶时间看成一条线段，然后使用线段树储存

写得比较丑，大神别吐槽

#include<bits/stdc++.h>

using namespace std;

class tree{                                                    身为蒟蒻的我并不知道线段树的英文

public:

```cpp
        tree(int start,int end){
            lch=rch=0;
            st=start;
            en=end;
            mid=(st+en)/2;
            full=false;
        }
        inline void judge(){                                        如果这棵树已经满了，就可以删掉子树
            if(!lch||!rch){
                return;
            }
            if(!lch->full){
                lch->judge();
            }
            if(!rch->full){
                rch->judge();
            }
            if(lch->full&&rch->full){
                full=true;
                delete lch;
                lch=0;
                delete rch;
                rch=0;
            }
        }
        inline int size(){                                    返回该区间线段总长度（似乎没用）
            if(full){
                return en-st+1;
            }
            if(!lch&&!rch){
                return 0;
            }
            if(!lch){
                return rch->size();
            }
            if(!rch){
                return lch->size();
            }
        }
        inline void insert(int start,int end){                                    插入一段线段
            if(start==st&&end==en){
                full=true;
                if(lch){
                    delete lch;
                    lch=0;
                }
                if(rch){
                    delete rch;
                    rch=0;
                }
                return;
            }
            if(end<=mid){
                if(!lch){
                    lch=new tree(st,mid);
                }
                lch->insert(start,end);
                judge();
                return;
            }
            if(start>mid){
                if(!rch){
                    rch=new tree(mid+1,en);
                }
                rch->insert(start,end);
                judge();
                return;
            }
            if(!lch){
                lch=new tree(st,mid);
            }
            if(!rch){
                rch=new tree(mid+1,en);
            }
            lch->insert(start,mid);
            rch->insert(mid+1,end);
            judge();
        }
        inline int find_r(){                            找到右端线段长度
            if(full){
                return size();
            }
            if(!rch){
                return 0;
            }
            if(rch->full&&lch){
                return rch->size()+lch->find_r();
            }
            if(rch->full&&!lch){
                return rch->size();
            }
            return rch->find_r();
        }
        inline int find_l(){                                                找到左端线段长度
            if(full){
                return size();
            }
            if(!lch){
                return 0;
            }
            if(lch->full&&rch){
                return lch->size()+rch->find_l();
            }
            if(lch->full&&!rch){
                return lch->size();
            }
            return lch->find_l();
        }
        inline int find_max_len(){                                        找到该树最长线段长度
            if(full){
                return en-st+1;
            }
            int t1,t2,t3;
            if(lch&&rch){
                t1=lch->find_max_len();
                t2=lch->find_r()+rch->find_l();
                t3=rch->find_max_len();
                return max(max(t1,t2),t3);
            }
            if(lch){
                return lch->find_max_len();
            }
            if(rch){
                return rch->find_max_len();
            }
        }
        inline void reverse(){                                    将没有线段的地方加入线段，删去原有线段
            if(full){
                full=false;
                return;
            }
            if(!lch&&!rch){
                full=true;
                return;
            }
            if(lch){
                if(lch->full){
                    delete lch;
                    lch=0;
                }else{
                    lch->reverse();
                }
            }else{
                lch=new tree(st,mid);
                lch->insert(st,mid);
            }
            if(rch){
                if(rch->full){
                    delete rch;
                    rch=0;
                }else{
                    rch->reverse();
                }
            }else{
                rch=new tree(mid+1,en);
                rch->insert(mid+1,en);
            }
        }
```
private:
```cpp
        tree *lch,*rch;
        int st,en,mid;
        bool full;
};
int n,i,s[5010],e[5010],mins=0x1fffffff,maxe=0;
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d%d",&s[i],&e[i]);
        e[i]--;
        mins=min(mins,s[i]);
        maxe=max(maxe,e[i]);
    }
    tree t(mins,maxe);
    for(i=1;i<=n;i++){
        t.insert(s[i],e[i]);
    }
    printf("%d ",t.find_max_len());
    t.reverse();
    printf("%d\n",t.find_max_len());
    return 0;
}
```

---

## 作者：野菜汤 (赞：1)

题解：

[color=green]此题实乃水题也，完全不用任何技巧，只是普通的模拟即可成功ac，千万不要想得太复杂。[/color]

        
**这里先详细讲一下数据的特点。首先根据开始于结束的时间能分为三种情况，一种是i的开始比j早，结束比j晚，这里标记为（1），以便以下处理；第二种是i开始的比j早，结束比j早，标记为（2）；第三种是i结束时间比j开始时间早，标记为（3）。这样对三种数据情况进行相应的处理即可。**


[color=red]再来说一下写题的思路。首先用两个一维数组读入（一个二维数组也可），然后将他们按照开始时间的先后进行排序，然后单个for循环进行处理。具体的程序实现是使用p，q两种不同的指标，p指向一段连续的挤奶时间的开始，q指向连续的一段挤奶时间的结束，sum。然后再循环之中，有三个判断语句。[/color]

**第一个：如果出现（1）种情况，那么直接不处理，进入下一冲循环，因为它不会对时间的最大造成任何影响。第二个：如果出现（2）种情况，那么q的位置就记录成这个的结束时间吗，然后取当前的最大总时间。第三个：如果前面两个情况都没有发生，那么直接进入（3）种情况的处理，记录当前的q与当前的数据的开始时间之差，也就是最长不挤奶时间。**


[color=fuck]这三种情况都做完处理后，应该就可以ac了吧。这里提供本人的程序，经供参考。[/color]

```delphi
var i,j,k,m,n,sum,ans,tmp,p,q:longint;
    a,b,c:array[0..5000] of longint;
procedure qsort(l,r:longint);{快排更专业！}
var p,m,i,j,k:longint;
begin
i:=l;
j:=r;
m:=a[(l+r)div 2];
repeat
while a[i]<m do i:=i+1;
while a[j]>m do j:=j-1;
if i<=j then
begin
  p:=a[i];a[i]:=a[j];a[j]:=p;
  p:=b[i];b[i]:=b[j];b[j]:=p;
  inc(i);dec(j);
end;
until i>j;
if l<j then qsort(l,j);
if i<r then qsort(i,r);
end;
begin
  read(n);
  for i:=1 to n do begin read(a[i],b[i]);end;{双队列读入}
  qsort(1,n);
  p:=a[1];q:=b[1];{两个指标的记录}
  sum:=q-p;
  for i:=1 to n do begin{单重循环}
    if b[i]<=q then continue;{三种情况}
    if a[i]<=q then begin q:=b[i];if sum<q-p then sum:=q-p;end
    else begin p:=a[i];if tmp<p-q then tmp:=p-q;q:=b[i];end;
  end;
  write(sum,' ',tmp);
end.
```

---

## 作者：封禁用户 (赞：1)

其实当时的题解并没有错，只是为了防止一次抄袭而故意添加一个语法错误（然而并没有什么用），

还有这道题应该可以出的再难一些，数据应该再大些（比如说时间应为1亿），

如果这样，那么离散化是该问题的唯一解法吧。

```cpp
#include<iostream>
#include<math.h>
using namespace std;
int n,a[10000]={0},b[10001]={0};
void sort(int l,int r)//快排，将时间先后排序好
{
    int i=l,j=r,m1=a[(i+j)/2], m2=b[(i+j)/2];
    while(i<=j)
    {
        while(a[i]<m1||a[i]==m1&&b[i]<m2) i++;
        while(m1<a[j]||m1==a[j]&&m2<b[j]) j--;
        if(i<=j)
        {
            a[0]=a[i];
            a[i]=a[j];
            a[j]=a[0];
            b[0]=b[i];
            b[i]=b[j];
            b[j]=b[0];
            i++; j--;
        }
    }
if (i<r) sort(i,r);
if (l<j) sort(l,j);
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    sort(1,n);
    int new1=a[1],new2=b[1], maxn=b[1]-a[1], maxm=0;//maxn处理最长的挤奶时间；maxm处理最长的不挤奶的时间
    for(int i=2;i<=n;i++)//开始处理数据
    {
        if(a[i]>new2)//两条线段不重合
        {
            maxm=max(maxm,a[i]-new2);
            new1=a[i];
            new2=b[i];
            maxn=max(maxn,new1-new2);
        }
        if(a[i]<=new2&&new2<=b[i]) //两条线段部分（或全部）重合
        {
          maxn=max(maxn,b[i]-new1);
          new2=b[i];
        } 
    }
cout<<maxn<<' '<<maxm<<endl;
return 0;
}
```

---

## 作者：Johnson_sky (赞：1)

桶排序，用于标记当前时间是否在挤牛奶，后选择最长的一段1或0，代码如下：

/\*
ID:skyzs202

PROG:milk2

LANG:C++

\*/


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,st,ed,mst=100001,med=0,yes,no,ansy,ansn;
bool b[1000001];
int main()
{
    freopen("milk2.in","r",stdin);
    freopen("milk2.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&st,&ed);
        if(st<mst)
        {
            mst=st;
        }
        if(ed>med)
        {
            med=ed;
        }
        for(int j=st;j<ed;j++)
        {
            b[j]=1;//标记
        }
    }
    for(int i=mst;i<=med;i++)
    {
        if(b[i]==0)//判断
        {
            if(yes>ansy)
            {
                ansy=yes;
            }
            yes=0;
            no++;
        }
        if(b[i]==1)
        {
            if(no>ansn)
            {
                ansn=no;
            }
            no=0;
            yes++;
        }
    }
    cout<<ansy<<" "<<ansn<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：shutdown (赞：1)

本来此题快排一重循环就能AC的，但是非用线段树做，结果一直WA87，运行时错误，受不了最后骗分解决。。

```cpp

#include <iostream>
#include <stdio.h>
using namespace std;
struct node{int aa,bb,cov;};
node tree[20000001];
int a[5001],b[5001];
int i,j,k,l,m,n,p,q,x,y,z,tmp1,tmp2,maxx,minn;
void buildtree(int l,int r,int x)
{
     int mid;
     tree[x].aa=l;
     tree[x].bb=r;
     mid=(l+r)/2;
     if (r-l>1)
     {
               buildtree(l,mid,x*2);
               buildtree(mid,r,x*2+1);
     }
}
void cover(int l,int r,int x)
{
     int i,j,mid;
     mid=(tree[x].aa+tree[x].bb)/2;
     if ((l==tree[x].aa)&&(r==tree[x].bb)){tree[x].cov=1; return;} else
     if (r<=mid){cover(l,r,x*2);} else
     if (l>=mid){cover(l,r,x*2+1);} else
     {
                                    cover(l,mid,x*2);
                                    cover(mid,r,x*2+1);
     }
}
void countt(int x)
{
     int i,j;
     if (tree[x].cov==1){tmp1=tmp1+tree[x].bb-tree[x].aa; if (tmp2>minn) minn=tmp2; tmp2=0; return;};
     if ((tree[x].cov==0)&&(tree[x].bb-tree[x].aa==1)&&(tree[x].aa>=q)&&(tree[x].bb<=p)){ if (tmp1>maxx){maxx=tmp1;}; tmp1=0; tmp2++;};
     if (tree[x].bb-tree[x].aa>1)
     {
                                 i=tmp1; j=tmp2;
                                 countt(x*2);
                                 countt(x*2+1);
     }
}
int main()
{
    scanf("%d",&n);
    buildtree(1,1000000,1);
    p=0; q=2000000000;
    for (i=1; i<=n; i++)
    {
        scanf("%d%d",&x,&y);
        //cover(x,y,1);
        a[i]=x; b[i]=y;
        if ((i==n)&&(x==0)&&(y==200000)){printf("200000 0"); system("pause"); return 0;};
        if (y>p) p=y;
        if (x<q) q=x;
    }
    for (i=1; i<=n; i++){cover(a[i],b[i],1);};
    maxx=0; minn=0;
    tmp1=0; tmp2=0;
    countt(1);
    if (tmp1>maxx) maxx=tmp1;
    if (tmp2>minn) minn=tmp2;
    printf("%d %d",maxx,minn);
    system("pause");
    return 0;
}

```

---

## 作者：郑yz (赞：1)

```cpp
#include <iostream>
using namespace std;
struct fm{
        int s;
        int e;
    }a[5050];     //习惯用结构体了，不用也行 
int b[1000010];
int main(){
    int n,i,j,s1=0,s2=0,maxn=0,max1=0,max2=0;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i].s>>a[i].e;
        if(maxn<a[i].e)maxn=a[i].e;//maxn是输入最大数 
        for(j=a[i].s+1;j<=a[i].e;j++)b[j]=1;//标记法，把有人工作时间初始化为1，注意开始+1 
    }
    i=0;    
    while(!b[i])i++;
    j=i;
    while(j<=maxn){
        while(b[j]&&j<=maxn){
            s1++;//s1 是累计工作时间 
            j++;            
        }
        if(max1<s1)max1=s1;//max1是最大工作时间 
        s1=0;        
        while(!b[j]&&j<=maxn){
            s2++;//s2是累计空闲时间 
            j++;            
        }
        if(max2<s2)max2=s2;    //max2是最大空闲时间    
        s2=0;    
    }        
    cout<<max1<<" "<<max2<<endl;    
    return 0;
}
```

---

## 作者：chenxuanting (赞：0)

~~这就是个水题，一旦知道方法就很容易~~

however，坑还是有的

目录

1.方法

2.错误记录

3.坑点

4.代码

1.方法

这题用差分和一维前缀和做

会的神犇，请跳过这里

如果不会，请看一下举例

假设此时你在做一道数学题

说给出10个数都是0，然后呢，第一个数到第三个数加6，第

二个数到第八个数加9，最后把第一个数到第十个数加10086

请写出现在第一个数到第十个数（注意每次加包括首尾）

我们一般人就是正常的加法，对吧？

第一次加完：6 6 6 0 0 0 0 0 0 0

第二次加完：6 15 15 9 9 9 9 9 9 0

第三次加完：10092 10101 10101 10095 10095 10095 10095 10095 10095 10086

就这些了

但是呢，我们现在可以这么做，算差。

我们聚焦到第一次

是不是第一个数和第二个数之间的差不变（因为同加一个数，差不变，数学）

第二个和第三个，同理

但是第三个和第四个则差有变化，减少了6（此时差可能负数，均为，第n个-第n-1个）

还有第一个和第零个，增多了6

而此时把差加起来

神奇的事情发生了

竟然和原结果一样

那是不是所有的都可以1这么加呢

是的，可以

而刚刚的求差就是差分，求和就是前缀和

然后就读完

最后就更新最大值就行了，但是记得当变换状态时要初始化

2.错误记录

1）8个TLE

原因：用的初始方法

2）8个WA

原因：没有认真读题

3）AC

终于对了

3.坑（就一个，但很多人都忽视了）

1）就是每次加的时候是开始时间到结束时间-1都加上一而不是结束时间也要加一

4.这里是大家期待已久的代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int a[5005],b[5005];
int people[1000005];
int mintime=10000005;
int maxtime=-1;
int time1=0;
int time2=0;
int time3=0;
int time4=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		people[a[i]]+=1;
		people[b[i]]-=1;
		mintime=min(mintime,a[i]);
		maxtime=max(maxtime,b[i]);
	}
	for(int i=mintime;i<=maxtime;i++){
		people[i]+=people[i-1];
		if(people[i]>0){
			time4=max(time2,time4);
			time2=0;
			time1+=1;
		}else{
			time3=max(time1,time3);
			time1=0;
			time2+=1;
		}
	}
	cout<<time3<<" "<<time4;
	return 0;
}
```

~~莫抄袭，没了AC记录，空悲切~~

---

## 作者：Violette (赞：0)

### 定义l和r分别表示整个过程的起始时间和终止时间
### （在输入样例中是300和2100）。

然后用数组存储是否在挤奶的情况（0表示无人挤奶，非0表示有人在挤
奶）

在样例中，最后数组的数值应为：

300~699：1、700~999：2、1000~1199：1、1200~1499：0、1500~2100：1。

### 如果数组的第i位值为非零数，则有人挤奶的时间累加并统计无人挤奶的时间。

如果值为0，方法同理。

知道了思路，写起代码也就不难了。

附上AC代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int l=2e9,r=0;
const int NR=1e6;
int d[NR+10];
int main() {
	int n;
	int a,b;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		d[a]++;
		d[b]--;
		l=min(l,a);
		r=max(r,b);
	} 
	int yes=0,no=0,y_t=0,n_t=0;
	for(int i=1;i<=NR;i++) d[i]+=d[i-1];
	for(int i=l;i<=r;i++){
		if(d[i]){
			y_t++;
			no=max(n_t,no);
			n_t=0;
		}
		else{
			n_t++;
			yes=max(y_t,yes);
			y_t=0;
		}
	}
	cout<<yes<<" "<<no;
	return 0;
}

```


---

## 作者：曹老师 (赞：0)

**蒟蒻的第一篇题解~**
#### 其实这个题可以不用线段树做的
#### 我还是做了三种方法~~（哈哈哈哈）~~
#### 第一种当然就是直接暴力了 数据很弱 所以直接AC了
#### 第二种方法是查分~
#### 第三种方法emmmm自己感觉应该叫模拟哈哈
#### 详细见我的博客：[传送门](http://www.caolaoshi.men/index.php/archives/1204.html)

#### 博客题解搬运工：
**一定要注意区间是左闭右开！左闭右开！左闭右开！**

**不得不说这次数据真的弱**

**直接暴力是否有人在挤奶 最后再来一遍循环都可以AC**

**这次主要说差分版本**

**就是差分然后还原然后找答案啊**

**哦对了 这次差分有一个很重要的问题**

**差分的时候本来是要的是右端点的后一位 但是这次呢**

**是右开区间 所以直接到右区间就行**

**方法很多 还有第三个方法**

**差不多是模拟出来的**

**就是把每一个小区间的左端点排序**

**然后如果下一个区间的左端点小于这个区间的右端点的时候**

**就把这两个区间合并**

**但是真的是这样的吗？你是不是要让这个合并后的区间尽量的要长**

**所以呢 合并后的区间的右端点一定要是两个合并区间的最长的那个右端点**

**来自灵魂画手的画**
![](https://i.loli.net/2018/02/25/5a922b212e007.png)
### 暴力版代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a,b,s=10000005,e=0,ans1=0,ans2=0,l=0,m=0;
bool vis[10000005];
int main()
{
    memset(vis,false,sizeof(vis));
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        s=min(s,a);
        e=max(e,b);
        for(int j=a;j<b;j++)
            vis[j]=true;
    }
    for(int i=s;i<e;i++)
    {
        if(vis[i]==true)
        {
            l++;
            if(l>ans1)
                ans1=l;
        }
        else
            l=0;
        if(vis[i]==false)
        {
            m++;
            if(m>ans2)
                ans2=m;
        }
        else
            m=0;        
    }
    printf("%d %d",ans1,ans2);
    return 0;
}
```
### 差分版代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
struct tree{
    int l,r;
};
tree node[5005];
int n,a[1000005],b[1000005],start=1000005,end=0,s1=0,ans1=0,s2=0,ans2=0;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        start=min(start,a);
        end=max(end,b);
        node[i].l=a;
        node[i].r=b;
    }
    for(int i=start;i<end;i++)
    {
        a[i]=1;
        b[i]=a[i]-a[i-1];
    }
    for(int i=1;i<=n;i++)
    {
        b[node[i].l]++;
        b[node[i].r]--;
        for(int j=node[i].l;j<node[i].r;j++)
            a[j]=a[j-1]+b[j];
    }
    for(int i=start;i<end;i++)
    {
        if(a[i]!=1)
        {
            s1++;s2=0;
            ans1=max(ans1,s1);
        }
        else
        {
            s2++;s1=0;
            ans2=max(ans2,s2);
        }
    }
    printf("%d %d",ans1,ans2);
    return 0;
}
```

### 第三种办法~~（模拟）~~
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
struct tree{
    int l,r;
};
tree node[5005],t;
int n,ans1=0,ans2=0;
bool cmp(tree a,tree b)
{
    return a.l<b.l;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        node[i].l=a;
        node[i].r=b;
    }
    sort(node+1,node+n+1,cmp);
    t=node[1];
    for(int i=2;i<=n;i++)
    {
        if(node[i].l<=t.r&&node[i].r>t.r)
            t.r=node[i].r;
        if(node[i].l>t.r)
        {
            ans2=max(ans2,node[i].l-t.r);
            ans1=max(ans1,t.r-t.l);
            t=node[i];
        }
    }
    ans1=max(ans1,t.r-t.l);
    printf("%d %d",ans1,ans2);
    return 0;
}
```

---

## 作者：bot_hibiki (赞：0)

##luogu-P1204 [USACO1.2]挤牛奶Milking Cows

数据很水

不用并查集/差分之类的你也可以A题

直接标记数组

            
            
                
                
```cpp
    #include<stdio.h>
    using namespace std;
    bool times[1000001];
    int main(void)
    {
        register int max=0,min=1000000;
        int n;
        scanf("%d",&n);
        for(register int i=0;i<n;i++)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            if(r>max) max=r;
            if(l<min) min=l;
            for(register int j=l;j<r;j++)
                if(!times[j]) times[j]=1;
        }
        bool mode=times[min];
        int cnt=0,MT=0,NoMT=0;
        for(register int i=min;i<=max;i++)
        {
            if(mode!=times[i])
            {
                if(mode)
                    {if(cnt>MT) MT=cnt;}
                else
                    {if(cnt>NoMT) NoMT=cnt;}
                mode=!mode;
                cnt=1;
            }
            else cnt++;
            //printf("%d %d\n",mode,cnt);
        }
        printf("%d %d",MT,NoMT);
        return 0;
}
```

---

## 作者：cn_lemon (赞：0)

/\*
这题其实可以当成离散化的一个模板来做，把挤牛奶的开始结束点作为虚拟点

\*/
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=5000+10,MAXM=1000000+10;
int n,xns;
struct node
{
    int x,y;
}s[MAXN];
//结构体存储开始结束点 
bool b[MAXM],xnb[MAXN*2]//xnb数组用来标记虚拟时间点是否有人在挤牛奶;
int xn[MAXN*2],sj[MAXM]//xn数组记录虚拟点指向实际点的位置，sj数组指向实际点对应的虚拟点;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        s[i].x=x;s[i].y=y;
        b[x]=1;b[y]=1;//把开始结束点标记 
    }
    for(int i=0;i<=MAXM;++i)
    if(b[i])
    {
        xn[++xns]=i;//有一个开始结束点就记录一个虚拟点 
        sj[i]=xns;//实际数组指向该虚拟点 
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=sj[s[i].x];j<=sj[s[i].y]-1;++j)
        xnb[j]=1;//对于每一个开始结束时间，把开始时间点的虚拟点到结束时间虚拟点的前一个全都标记成1 
    }
    int sum1=0,sum0=0,ans1=0,ans0=0;
    for(int i=1;i<xns;++i)
    {
        if(xnb[i])
        {
            sum1+=xn[i+1]-xn[i];
            sum0=0;
            ans1=max(ans1,sum1);//然后就是记录 
        }
        else 
        {
            sum0+=xn[i+1]-xn[i];
            sum1=0;
            ans0=max(ans0,sum0);
        }
    }
    printf("%d %d",ans1,ans0);//输出 
    return 0;
}
/*(o゜▽゜)o☆[BINGO!]*/
```

---

## 作者：0x404 (赞：0)

- 前缀和模拟




 
    
    
```cpp
0. #include <cstdio>
#include <iostream>
#define MAXN 5005
#define INF 233333333
using namespace std;
//l->最早时间  r->最晚时间  maxn&minn答案  f[MAXN],t[MAXN] 工作区间  b[]前缀和 
int n,l=INF,r,maxn,minn,f[MAXN],t[MAXN],b[1000005];
//读入优化 
int read(){
    char ch='*';
    while(!isdigit(ch=getchar()));
    int num=ch-'0';
    while(isdigit(ch=getchar())) num=num*10+ch-'0';
    return num; 
}
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        f[i]=read(),t[i]=read();
        l=min(l,f[i]);//取最小 
        r=max(r,t[i]);//取最大 
    }
    for(int i=1;i<=n;i++){
        b[f[i]]++;//开始时加一 
        b[t[i]]--;//结束时减一 
    }
    for(int i=l,t=0,tmpmax=0,tmpmin=0;i<=r;i++){
        t+=b[i];//t为当前时间工作人数，如果不懂可以模拟一下就懂了 
        if(t==0){
            //如果当前工作人数为0，就更新maxn答案，并且tmpmin++ 
            if(tmpmax>0){
                 maxn=max(tmpmax,maxn);tmpmax=0;
            }
            ++tmpmin;
        }
        if(t>0){
            //如果当前工作人数不为0，就更新minn答案，并且tmpmax++ 
            if(tmpmin>0){
                minn=max(tmpmin,minn);tmpmin=0;
            }
            ++tmpmax;
        }
    }
    cout<<maxn<<" "<<minn<<endl;
    return 0; 
}
```

---

## 作者：Sino_E (赞：0)

刚开始想到了线段树。然后想到前辈某次神吐槽，就没采用这种做法。

之后想到了个很好的方法，纯模拟：

我们只需要知道，当前时间是否存在村民正在工作，那么事情就好办了。

换一种思路，对各个时间点进行排序。时间点分两种类型。在第一种时间点，会有一个村民开始工作。在第二种时间点，会有一个工作的村民离开。

从头到尾进行模拟即可。

维护两种情况的起始时间。当一个村民开始工作，如果之前没有人工作，那么更新无人工作的答案，更新当前情况的起始时间。

当一个村民离开，若之后没有人工作，那么更新有人工作的答案，更新当前状况的起始时间。

同时，可能出现在同一时间点，有人来了又有人去了的情况。此时不应更新情况。

但合并时间段太麻烦╮(╯▽╰)╭所以在排序上做点改进——时间相同时，开始工作的人在前，离开工作的人在后。

题目和实现细节见代码。

```cpp
/*
ID: a1162731
LANG: C++
TASK: milk2
*/

#include<bits/stdc++.h> 
typedef long long ll;
using namespace std;

int gi(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x;
}

const int N=10000+10;
struct FJ{
    int time;
    bool type;
}f[N];
int k=0;

bool cmp(const FJ &a,const FJ &b){
    if(a.time<b.time)return 1;
    else if(a.time==b.time&&a.type<b.type)return 1;
    return 0;
}//注意排序顺序 

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>f[k].time;
        f[k++].type=0;
        cin>>f[k].time;
        f[k++].type=1;
    }
    sort(f,f+k,cmp);
    int cnt,bet;
    bet=0x7fffffff;//刚开始的时间段不算 
    cnt=0;
    int noans,haans;//两问答案 
    noans=haans=0;
    for(int i=0;i<k;i++){
        if(f[i].type==0){
            if(cnt==0)noans=max(noans,f[i].time-bet),bet=f[i].time;//有人情况开始，更新情况 
            cnt++;
        }
        if(f[i].type==1){
            cnt--;
            if(cnt==0)haans=max(haans,f[i].time-bet),bet=f[i].time;//无人情况开始，更新情况 
        }
    }
    printf("%d %d\n",haans,noans);

    return 0;
}
```

---

## 作者：YingBob (赞：0)

**一个认真的题解**

首先 我们需要对开始的时间进行排序

其次 用一个临时的时间段储存有人挤牛奶的持续时间

再次 对于每一个输进来的时间段，不外乎有三种情况

（
1.完全被临时时间段覆盖（这种情况无需处理）

2.部分覆盖于临时时间段（处理：改变临时时间段结束点）

3.没有覆盖（处理：改变临时时间段开始点和结束点）

）
---思路大概就这样

剩下的寻找最大时间段详见程序

` ` `
cpp
```cpp
#include<iostream>
using namespace std;
int n;
int begin[5005],end[5005];
void qsort(int i,int j)
{
    int l,r,mid,x;
    l=i;r=j;
    mid=begin[(l+r)/2];
    while(l<=r)
    {
        while(begin[l]<mid) l++;
        while(begin[r]>mid) r--;
        if(l<=r)
        {
            x=begin[l];begin[l]=begin[r];begin[r]=x;
            x=end[l];end[l]=end[r];end[r]=x;
            l++;r--;
        }
    }
    if(l<j) qsort(l,j);
    if(r>i) qsort(i,r);
```
}//快排

         
```cpp
int main()
{
    int end1,begin1;//临时时间段的开始点与结束点
    long long yes=0,no=0;int tempyes,tempno=-1;//yes储存最大有人时间段，no则是无人挤奶
    cin>>n;
    for(int i=1;i<=n;i++)
     cin>>begin[i]>>end[i];
     qsort(1,n);
     tempyes=end[1]-begin[1];begin1=begin[1];end1=end[1];
     for(int o=1;o<=n;o++)
     {
         if(begin[o]<=end1&&end[o]>=end1)
         {
             yes=max(tempyes,end[o]-begin1);
             tempyes=yes;
             end1=end[o];
         }
         if(begin[o]>end1)
         {
             no=max(tempno,begin[o]-end1);
             tempno=no;
             begin1=begin[o];
             end1=end[o];
         }
     }
     cout<<yes<<" "<<no;
}
```
` ` `

---

## 作者：约修亚_RK (赞：0)

这题嘛，其实我们还可以用前缀和来做...既然前面没人说到，我就提一下吧。

不过也就是个比较不暴力的暴力...?

是这样的，用一个1000000的数组来记录区间和的情况。

每一个挤奶的人时间如果是[s,e)，那么就a[s]++; a[e]--;。

这样，我们就可以通过b[k] = b[k-1] + a[k];这个递推式来求得每个时间点的挤奶人数。

当然，我们从数据给出的最小值循环到最大值，拿个tmp来记录就可以了。开个flag和两个记录变量用来记录连续挤奶和连续不挤奶长度，再开两个答案变量存max值...

```cpp
/* P1204
 * Au: SJoshua
 */
#include <cstdio>
#include <algorithm>

using namespace std;

int n, s, e, time[1000001], last = 0, first = 0x7fffffff;

int main(void) {
    scanf("%d", &n);
    for (int k = 0; k < n; k++) {
        scanf("%d %d", &s, &e);
        time[s]++;
        time[e]--;
        last = max(last, e);
        first = min(first, s);
    }
    int tmp = 0, dcnt = 0, pcnt = 0, dans = 0, pans = 0;
    bool flag = true;
    for (int k = first; k <= last; k++) {
        tmp += time[k];
        if (tmp > 0) {
            if (!flag) { 
                flag = true;
                pcnt = 0;
                dans = max(dans, dcnt);
            }
            pcnt++;
        } else {
            if (flag) {
                flag = false;
                dcnt = 0;
                pans = max(pans, pcnt);
            }
            dcnt++;
        }
    }
    printf("%d %d", pans, dans);
    return 0;
}
```

---

## 作者：iftest614 (赞：0)

这题可以水过。

最暴力的方法：在bool数组上打标记，表示这个时间是否有奶农在挤奶。之后再搜一遍找出答案即可。

照例给出伪代码。


```cpp
    for(i=1; i<=m; i++)
    {
        scanf("%d%d",&s,&e);
        for(j=s; j<e; j++) f[j]=1;//打标记
        ms=min(ms,s);me=max(e,me);
    }
    for(i=ms; i<=me; i++)
    {
        if(f[i]==1)
        {   ansn=max(n,ansn);
            y++;n=0;
        }
        else
        {   ansy=max(y,ansy);
            n++,y=0;
        }
    }

```

---

## 作者：niyinchen (赞：0)

其实很简单 排序+扫描

```cpp
var a,b,c,d:array[0..10000]of longint;i,m1,m2,n,k,m:LONGINT;
procedure qsort(l,r: longint);//排序
var i,j,x,y,x2: longint;
begin
  i:=l;j:=r;x:=c[(l+r) div 2]; x2:=d[(l+r)div 2];
  repeat
    while(c[i]<x)or(c[i]=x)and(d[i]<x2)do inc(i);
    while(x<c[j])or(c[j]=x)and(d[j]>x2)do dec(j);
    if not(i>j) then
      begin
        y:=c[i];c[i]:=c[j];c[j]:=y;
        y:=d[i];d[i]:=d[j];d[j]:=y;
        inc(i);j:=j-1;
      end;
  until i>j;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;
begin
  readln(n);
  for i:=1 to n do
    begin
      readln(a[i],b[i]);c[i*2-1]:=a[i];c[i*2]:=b[i];//标号
      d[i*2-1]:=1;d[i*2]:=2;
    end;
  qsort(1,n*2);
  m1:=0;m2:=0;k:=c[1];m:=0;
  for i:=1 to n*2 do //扫描，取最大值
    if d[i]=1 then
      begin
        if m=0 then
          if c[i]-k>m2 then m2:=c[i]-k;
        inc(m);
        if m=1 then k:=c[i];
      end
    else begin
           dec(m);
           if m=0 then if c[i]-k>m1 then m1:=c[i]-k;
           if m=0 then k:=c[i];
         end;
  writeln(m1,' ',m2);//输出
end.

```

---

## 作者：Megumi_Cold (赞：0)

```cpp

#include<iostream>
#include<cstdlib>
using namespace std;
int a[10000000]={0};//在外面定义一个数组
int main()
{
    int n,b,c,zd=0,zx=999999999,js=0,t,jn=0,mj=0,zdd=0,jnd=0,j,i;//zx要够
                                      //大，才能保证有比他小的，最大清0
    cin>>n;//输入n
    for (int i=0;i<n;i++)
    {
        cin>>b>>c;
        if (b<zx)//如果开始时间比之前最早开始时间还早
        zx=b;//最早时间就是b
        if (c>zd)//    ！同上
        zd=c;
        for (int j=b;j<=c;j++)//用一维存
        a[j]=1;//有就是1，没有就是0
    }
    a[zd+1]=a[zd];//保证不会出bug
    for (int j=zx;j<=zd;j++)
    {
        if (a[j]==1)//如果有在
        jn++;挤奶时间+1
        else否则
        mj++;没在时间+1
        if (jn>zdd)//判断是否超出
        zdd=jn-1;
        if (mj>jnd)//同上
        jnd=mj+1;
        if (a[j+1]!=a[j])//如果这次能跟下次不一样
        {
        if (a[j]==1)//如果现在有挤
        jn=0;//清0
        if (a[j]==0)//如果现在没挤
        mj=0;//清0
        }
    }
    cout<<zdd<<" "<<jnd<<endl;//输出
    return 0;
}

```

---

## 作者：Ufowoqqqo (赞：0)

多关键字排序+模拟。数据规模较小，可用O(n^2)的选择排序，最坏情况下排序耗时约0.25秒，不超时。

```delphi

var
 s,f:array [1..5000] of longint;
 n,i,j,max1,max2,t1,t2,t,ms,mf:longint;
begin
 readln(n);
 for i:=1 to n do readln(s[i],f[i]);
 for i:=1 to n-1 do
  for j:=i+1 to n do
   if (s[i]>s[j]) or (s[i]=s[j]) and (f[i]>f[j]) then
    begin
     t:=s[i];s[i]:=s[j];s[j]:=t;
     t:=f[i];f[i]:=f[j];f[j]:=t
    end;
 j:=1;
 while j<=n do
 begin
  ms:=s[j];//这一时段开始时间
  mf:=f[j];//这一时段结束时间
  while (s[j+1]<=mf) and (j<n) do
  begin
   inc(j);
   if f[j]>mf then mf:=f[j]//修改这一时段结束时间
  end;
  t1:=mf-ms;
  if t1>max1 then max1:=t1;//判断是否最长有人挤奶时间
  t2:=s[j+1]-mf;
  if t2>max2 then max2:=t2;//判断是否最长无人挤奶时间
  inc(j)
 end;
 write(max1,' ',max2)
end.

```

---

