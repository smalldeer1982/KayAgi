# [USACO15OPEN] Trapped in the Haybales S

## 题目描述

FJ 收到了 $N$ 捆干草，并将它们放置在连接房屋与谷仓的道路上。第 $j$ 捆干草的大小为 $S_j$，位置为 $P_j$。Bessie 一开始在 $B$ 处，不与任何一捆干草的位置重合。

Bessie 可以在干草捆之间任意移动（也可以到达干草捆所在的位置），但不能越过干草捆。但凡事总有例外：当 Bessie 进行了长度为 $D$ 的冲刺后，她就可以击碎一捆大小严格小于 $D$ 的干草，这意味着这捆干草不复存在。

由于某些原因，FJ 希望把 Bessie 困在最左边与最右边的干草捆之间。为此，他希望将某一捆干草的大小增加一些。如果可能把 Bessie 困住，请输出他最少需要增加多少干草；否则输出 `-1`。

$1 \leqslant N \leqslant 10^5$，$1 \leqslant S_i, P_i, B \leqslant 10^9$。

## 样例 #1

### 输入

```
5 7
8 1
1 4
3 8
12 15
20 20```

### 输出

```
4```

# 题解

## 作者：Schwarzkopf_Henkal (赞：16)

写完金组再来写银组。

两题的尿性都差不多，依然是暴力能够解决的问题。
问题要求我们加固其中一个草堆以避免Bessie逃出草堆。并且当连续跑动的距离大于该草堆的大小就能打破该草堆。那么需要加固该草堆的size就等于跑动的距离减去该草堆的大小。那么我们思考某一个草堆能够被撞击的最大加速值是在不打破该草堆的前提下让Bessie随意倒腾能够开辟出的最大空间。

如果枚举左端点，那么撞击该草堆的最大加速值是Bessie向右跑能够到达的最右草堆位置减去当前草堆位置。反之亦然。

注意在枚举完上一个端点后不需要把另一边的位置极值重置为距Bessie原本最近的那个点，因为如果Bessie在不打破上一个草堆的情况下能够到达那个点，那么打破之后也一定能。

然后是其他需要注意的地方，例如什么时候输出0什么时候输出-1。输出0是指枚举完了左端点或右端点，但是另一边的位置极值始终不能到达0和n+1的情况。会导致ans的值被更新成负数，输出时用max调整一下就行。输出-1只当Bessie向任意一边跑，但是甚至不用撞破另一边的草堆的时候就能逃离的时候输出。这时ans的值不会被更新。
## $Solution$
```
#include<bits/stdc++.h>
using namespace std;
long long n,b,ans=5201314314314,st=1;//这里最大值不能开的小于10^9，之前开5201314把我从前天！卡到！今天！
struct grass {
	long long s,p;/草堆的大小与位置
} gra[100005];
bool cmp(grass a,grass b) {
	return a.p<b.p;
}
int main() {
	cin>>n>>b;
	for(int i=1; i<=n; i++) 
		cin>>gra[i].s>>gra[i].p;
	sort(gra+1,gra+n+1,cmp);
	for(;st<=n;st++)
		if(gra[st+1].p>b)
			break;//之前用二分查找莫名其妙的挂了，至今未解
	int l=st,r=st+1;
	for(; l>=1; l--) {
		while(r<=n&&gra[r].p-gra[l].p>gra[r].s)//在能够向右倒腾的时候就一定要倒腾换取可能的最大的加速值
			r++;
		if(r>n)
			break;
		ans=min(ans,gra[r].p-gra[l].p-gra[l].s);//在该点至少要加固的值和ans取min
	}
	l=st;
	r=st+1;
	for(; r<=n; r++) {
		while(l>=1&&gra[r].p-gra[l].p>gra[l].s)//同上
			l--;
		if(l<1)
			break;
		ans=min(ans,gra[r].p-gra[l].p-gra[r].s);//同上
	}
	if(ans==5201314314314)
		cout<<-1;//有点绕，如果左边和右边都无论加没加固都无法阻止Bessie逃出去，那么输出-1。
	else cout<<max(ans,1ll*0);
}
```
I'm Schwarzkopf Henkal.

---

## 作者：灼眼的夏娜 (赞：13)

所以这道题为啥用到了并查集？

想了半天也没发现它和并查集有半毛钱关系

显然你可以找出来bessie一开始在哪两个草堆之间，并且你发现如果一开始

这两个草堆的$size>$两草堆间的距离$d$那我们完全不用管了，输出0即可，

否则，让她选择一个方向冲破，而另一个方向我们给其加$size$，如果没加

的一方没有能拦住她的草堆，那另一端的加固也就作废了，此时要输出-1

**注意题目上说的，增加某一堆干草堆指的是只增加一堆的size**

开始我还在想为啥会有拦不住的情况QWQ

所以接下来我们只要模拟一下她跑的过程就好啦，这里用了两个$while$

分别枚举左端点与右端点，表示我们要加固哪一个方向的草堆,在枚举过程中

改变一下$d$就好啦

代码如下：

## code

```cpp
#include<bits/stdc++.h>
#define R register
#define inf 1e18
#define int long long

using namespace std;
const int N = 1e5+5;
int n,b,ans = inf,now;
int l,r,d;
struct node {
	int pos,size;
}g[N];

inline bool cmp(node a,node b) { return a.pos < b.pos; }

signed main() {
	scanf("%lld%lld",&n,&b);
	for(R int i = 1;i <= n;++ i) {
		scanf("%lld%lld",&g[i].size,&g[i].pos);
	}
	sort(g + 1,g + n + 1,cmp);
	for(R int i = 1;i <= n;++ i)
		if(g[i].pos > b) { now = i;break; }
	l = now - 1,r = now,d = g[r].pos - g[l].pos;
	while(l >= 1 && r <= n) {
		if(g[l].size >= d && g[r].size >= d) { printf("0");return 0; }
		if(g[r].size < d) { r ++;d += g[r].pos - g[r - 1].pos;continue; }
		if(g[l].size < d) {	ans = min(d - g[l].size,ans);l --;d += g[l + 1].pos - g[l].pos; }
	}
	l = now - 1,r = now,d = g[r].pos - g[l].pos;
	while(l >= 1 && r <= n) {
		if(g[l].size >= d && g[r].size >= d) { printf("0");return 0; }
		if(g[l].size < d) { l --;d += g[l + 1].pos - g[l].pos;continue; }
		if(g[r].size < d) {	ans = min(d - g[r].size,ans);r ++;d += g[r].pos - g[r - 1].pos; }
	}
	printf("%lld",ans == inf ? -1 : ans);
	return 0;
}
```


---

## 作者：白鲟 (赞：6)

## 题目分析
看到有关坐标的题目，当然第一反应就是把所有草堆按照坐标排序。然后发现奶牛 bessie 也有坐标，这就需要我们找到 bessie 到底是在哪两堆干草中间的空隙中（然而我第一次写的时候忘了……），可以用二分查找来找。  

之后照例看所求的内容。我们看见题目要求的是把 bessie 堵住的最小花费。这个问题可以转化为在每一个草堆把 bessie 堵住的最小花费的最小值。接下来我们要做的是探究什么情况才能把 bessie 堵住。由于 bessie 可以在它所在的两个草堆间隙中反复横跳（大雾），容易知道 bessie 摧毁某一个草堆的条件是当前 bessie 所在的草堆空隙长度大于该草堆的大小。那么如果要把 bessie 堵住，必须要保证当前所在空隙两端草堆大小均大于或等于空隙长度。因此，我们若是要通过加高某一草堆把 bessie 堵住，必须满足堵住它时空隙的另一端的草堆大小大于或等于空隙长度，也就是我们需要找到第一个到此草堆的距离小于其大小的草堆，并把当前草堆的大小修改为这一距离。  

由于 bessie 的冲撞方向对答案有影响，我们将区间分为 bessie 左边与右边两部分进行分别处理。对于每一段区间，我们设立两个指针，一个枚举需要加高的草堆，一个指向另一端，两指针从中间开始背向移动寻找答案即可。这是因为对于我们枚举的草堆，若是上一个草堆都无法与指向另一端的指针之前指向的位置匹配，这一次两者距离进一步增大，之前指向的位置就更无法满足要求，即答案满足一定的单调性。  

## 代码
注意若当前草堆的大小本就高于空隙长度，答案为 $0$ 而不是负数。
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
int n,b,ans=0x7fffffff,x1,x2;
struct grass
{
	int s,j;
}a[100001];
inline bool cmp(const grass &t1,const grass &t2)
{
	return t1.j<t2.j;
}
int main()
{
	scanf("%d%d",&n,&b);
	a[0].j=b;
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].s,&a[i].j);
	sort(a+1,a+n+1,cmp);
	x1=upper_bound(a+1,a+n+1,a[0],cmp)-a;
	x2=x1-1;
	for(int i=x1,j=x2;i<=n&&j>0;++i)
	{
		while(j>0&&a[j].s<a[i].j-a[j].j)
			--j;
		if(j>0)
			ans=min(ans,max(0,a[i].j-a[j].j-a[i].s));
	}
	for(int i=x1,j=x2;i<=n&&j>0;--j)
	{
		while(i<=n&&a[i].s<a[i].j-a[j].j)
			++i;
		if(i<=n)
			ans=min(ans,max(0,a[i].j-a[j].j-a[j].s));
	}
	printf("%d",ans==0x7fffffff?-1:ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：redegg (赞：6)

思路和 tony1312 差不多。

除了其它题解说的坑点，我还一直纠结于无法到达最左边和最右边的两个干草堆是1和n还是0和n+1（事实上是后者）。

~~我觉得longlong也是个坑~~

是这样的，从奶牛b旁边的干草堆开始，先确定一个无法被突破的左边的干草堆，然后去找右边的可以被突破的干草堆，如果找到了就ans和用来堆上去的新的干草数量取min，没找到的话说明不用保护干草堆，直接输出0；

当然，**找干草堆的时候l和r是不会重复出现的，也就说l和r的区间是不断扩大的**，缩小是无意义的，具体看代码或自己理解。

同上，我们确定右边的干草堆，然后去找左边的，然后取min。

如果ans没变，那么就说明没找到。

这样复杂度就从o(n^2)下降到o(n)了

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

struct ha
{
    long long h,x;
} a[6000000];

long long n,b;

bool cmp(const ha &aa,const ha &bb)
{
    return aa.x<bb.x;
}

long long ans=1e18;

int main()
{
    scanf("%lld%lld",&n,&b);
    for(int i=1; i<=n; i++)
    {
        scanf("%lld%lld",&a[i].h,&a[i].x);
    }
    long long r,l,z,y;
    sort(a+1,a+1+n,cmp);
    for(int i=1; i<=n; i++)
    {
        if(a[i].x>b)
        {
            y=i;
            z=i-1;
            break;
        }
    }
    l=z;
    r=y;
    while(1)
    {
        if(l<=0||r>=n+1)
            break;
        if((a[r].x-a[l].x<=a[r].h)&&(a[r].x-a[l].x<=a[l].h))
        {
            printf("0\n");
            return 0;
        }
        if(a[r].x-a[l].x>a[r].h)
        {
            r++;
            continue;
        }
        if(a[r].x-a[l].x>a[l].h)
        {
            ans=min(a[r].x-a[l].x-a[l].h,ans);
            l--;
        }

    }
    r=y;
    l=z;
    while(1)
    {
        if(l<=0||r>=n+1)
            break;
        if((a[r].x-a[l].x<=a[r].h)&&(a[r].x-a[l].x<=a[l].h))
        {
            printf("0\n");
            return 0;
        }
        if(a[r].x-a[l].x>a[l].h)
        {
            l--;
            continue;
        }
        if(a[r].x-a[l].x>a[r].h)
        {
            ans=min(a[r].x-a[l].x-a[r].h,ans);
            r++;
        }

    }
    if(ans==1e18)
        printf("-1\n");
    else
        printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：bobble (赞：6)

## Solution


这是一道题意迷之hentai的奶牛题


看了一个多小时才看懂题意【放弃治疗


题目翻译真是跪了，各种错误，下次英文题还是自己翻译好。。。



这道题的一个思路是枚举bessie能到达的区间，


先进行$O(n log n)$的排序，然后找到离Bessie最近的右边的干草堆的编号$nearright$


每次寻找$(l,r)$为bessie可以突破$l$但是无法突破$r$时需要给$l$加上多少干草，每次对$ans$取$min$



这个做到$O(N)$，因为当$l$循环完了，在循环$l-1$时，$r$已经不一定要从最初的$nearright$开始，**顺延上次更新的r值就可以**


因为如果还是从最初的$nearright$开始，


当$place[r]-place[l]>height[l]$就不会进行while，


而当$place[r]-place[l]<=height[l]$时候，


$height[r]$还是不变的,


$r$不变，$l$减小，所以$place[r]-place[l]$增大，于是$place[r]-place[l]-height[r]$增大，所以就算进行了也不会更新$ans$


同理，在每次寻找$(l,r)$为bessie可以突破$r$但是无法突破$l$时需要给$r$加上多少干草



若$ans$没有改变则说明每个$(l,r)$都是两边都可以突破的，于是只给一个干草堆加肯定是不可以的（即输出$-1$）


否则输出答案就可以了


## Code


```cpp
program test;
uses math;
const  
  init = maxlongint;
  maxn = 100002;
  
type
  arr=array[0..maxn] of longint;

var
  n,t,i,ans,l,r,nearright:longint;
  place,size:arr;

procedure qsort(l,r: longint);
var
   i,j,x,y: longint;
begin

  i:=l;  j:=r;  x:=place[(l+r) div 2];

  repeat
   while place[i]<x do inc(i);
   while x<place[j] do dec(j);
   if not(i>j) then
   begin
    y:=place[i];   place[i]:=place[j]; place[j]:=y;
    y:=size[i];    size[i]:=size[j];   size[j]:=y;
    inc(i);    j:=j-1;
   end;
 until i>j;

 if l<j then qsort(l,j);
 if i<r then qsort(i,r);

end;

begin
    
    readln(n,t);
    for i:= 1 to n Do
      readln(size[i],place[i]);
    qsort(1,n);

    ans:=init;

    for i:= 1 to n Do 
      if place[i]>t then 
        begin 
           nearright:=i;
           break;
        end;

    r:=nearright;
      
    for l:= nearright-1 downto 0 do 
      while (r<=n) and (not(place[r]-place[l]>size[l])) do
        begin
          ans:=min(ans,place[r]-place[l]-size[r]);
          inc(r);
        end;

    l:=nearright-1;
    for r:= nearright to n do 
      while (l>=1) and (not(place[r]-place[l]>size[r])) do
        begin
          ans:=min(ans,place[r]-place[l]-size[l]);
          dec(l);
        end;

    if ans = init then writeln(-1)
      else writeln(max(0,ans));

end.
```

---

## 作者：legend_cn (赞：2)

这道题可以用双指针解。

双指针就是使用两个位置进行操作，操作完毕后，移动这两个位置的算法，典型的应用：计算两数之和。

此题思路：使用结构体进行存贮每一捆草，然后使用坐标进行排序。再计算第一个坐标小于 $b$ 的坐标，进行两次双指针，并更新答案，最后输出答案。

代码中关键易错的地方加了少量注释。

最后是 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct cao//结构体，存贮每一捆草
{
	ll s;
	ll p;
}grass[100005];

bool cmp(cao a, cao b)//使用右指针排序
{
	return a.p < b.p;
}

int main() 
{
	ll n, b;
	cin >> n >> b;
	
	for (int i = 1; i <= n; i ++ )
	{
		cin >> grass[i].s >> grass[i].p;
	}
	
	sort(grass + 1, grass + n + 1, cmp);//排序
	
	ll st;
	for (st = 1; st <= n; st ++ )//寻找第一个坐标小于b的编号
	{
		if (grass[st + 1].p > b)
		{
			break;
		}
	}
	
	int r = st + 1;
	ll ans = 0x7fffffffffffffff;//int范围内的最大值（2147483647）
	
	for(int l = st; l >= 1; l -- )//第一次双指针
	{
		while (r <= n && grass[r].p - grass[l].p > grass[r].s)
		{
			r ++ ;//移动右指针
		}
		
		if (r > n)
		{
			break;
		}
		
		ans = min(ans, grass[r].p - grass[l].p - grass[l].s);//更新答案
	}
	
	int l = st;
	
	for(int r = st + 1; r <= n; r ++ )第二次双指针
	{
		while (l >= 1 && grass[r].p - grass[l].p > grass[l].s)
		{
			l -- ;//移动左指针
		}
		
		if (l < 1)
		{
			break;
		}
		
		ans = min(ans, grass[r].p - grass[l].p - grass[r].s);.//更新答案
	}
	
	if(ans == 0x7fffffffffffffff)//不符合条件的情况
	{
		cout << -1;
	}
	else
	{
		cout << max(ans, 0ll);//输出（可能ans是负数，需要与long long 中的0进行比较）
	}
	
	return 0;
}
```


---

## 作者：KSToki (赞：2)

闲话：这是我们的考试题，可能数组用得不太一样，请忽略蒟蒻奇怪的数组命名。

# 题目大意

增大一个$s_i$（$1 \le s_i \le n$），使存在一个$i,j$（$ p_i \le b \le p_j$），使得$p_j-p_i \le min(s_i,s_j)$，即将其困住，如果不能做到则输出-1。

显然应该先对$p_i$作为关键字排个序。因为只能增加一个位置，我们可以假定每一个$s_i$不变，去计算所有在b的另一侧的点最小需要增加多少。但这种~~暴力~~的算法时间复杂度是$O(n^2)$，而$1 \le n \le 100000$，是会TLE的。循环使每一个点不变是不能优化的，于是蒟蒻就想到了对第二层循环优化。

找min，你想到了什么？~~没错，就是线段树~~（静态）

这样我们程序大体的结构就出来了，细节的地方会在代码中注释。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//快读
{
	char ch=getchar();
	while(ch<'0'||ch>'9')
	    ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9')
	{
		res=(res<<1)+(res<<3)+ch-'0';
		ch=getchar();
	}
	return res;
}
struct stu
{
	int siz;//就是题目中的s，表示干草堆的大小
	int loc;//就是题目中的p，表示干草堆的位置
}x[100001];
int n,b,Siz[100001],Loc[100001],a[100001],loc_b,Tree1[400001],Tree2[400001],ans=0x7fffffff;
bool cmp1(stu x1,stu x2)
{
	return x1.loc<x2.loc;//排序，以位置为关键字
}
/////////以下是线段树模板////////////
void build(int k,int l,int r)//建树
{
	if(l==r)//到达叶节点
	{
		Tree1[k]=Tree2[k]=a[l];//Tree1存最小值，Tree2存最大值，为什么要这么做在主函数中会讲
		return;
	}
	int mid=(l+r)>>1;//位运算嘛，>>1就是/2，<<1就是*2
	build(k<<1,l,mid);//建左子树
	build((k<<1)|1,mid+1,r);//建右子树
	Tree1[k]=min(Tree1[k<<1],Tree1[(k<<1)|1]);//更新
	Tree2[k]=max(Tree2[k<<1],Tree2[(k<<1)|1]);
}
int query_min(int k,int l,int r,int ask_l,int ask_r)//查找区间最小值
{
	if(l>ask_r||r<ask_l)
	    return 0x7fffffff;
	if(l>=ask_l&&r<=ask_r)
	    return Tree1[k];
	int mid=(l+r)>>1;
	return min(query_min(k<<1,l,mid,ask_l,ask_r),query_min((k<<1)|1,mid+1,r,ask_l,ask_r));
}
int query_max(int k,int l,int r,int ask_l,int ask_r)//查找区间最大值
{
	if(l>ask_r||r<ask_l)
	    return -0x7fffffff;
	if(l>=ask_l&&r<=ask_r)
	    return Tree2[k];
	int mid=(l+r)>>1;
	return max(query_max(k<<1,l,mid,ask_l,ask_r),query_max((k<<1)|1,mid+1,r,ask_l,ask_r));
}
////////////以上是线段树模板////////////
int main()
{
	n=read();
	b=read();
	for(register int i=1;i<=n;++i)
	{
		x[i].siz=read();
		x[i].loc=read();
	}
	sort(x+1,x+n+1,cmp1);//排序
	for(register int i=1;i<=n;++i)//排完序再弄回来，便于二分
	{
		Siz[i]=x[i].siz;
		Loc[i]=x[i].loc;
	}
	loc_b=upper_bound(Loc+1,Loc+n+1,b)-Loc;//找出临界点，1~loc_b-1为左边，loc_b~n为右边
    for(register int i=1;i<=n;++i)
    {
    	if(i<loc_b)//在左边，因为循环到这个点时默认不增加它的大小，a[i]就表示它向右最多能够到的点，超过的话显然能够向左冲破
		    a[i]=Siz[i]+Loc[i];
		else//否则在左边，同理
		    a[i]=Loc[i]-Siz[i];
    }
	build(1,1,n);//建树
	for(register int i=1;i<loc_b;++i)//处理左边
	{
		int R=upper_bound(Loc+loc_b,Loc+n+1,a[i])-Loc-1;//算出右端点，保证其不能向左突破
		if(R<loc_b) continue;右端点还没过b，肯定没戏
		ans=min(ans,max(query_min(1,1,n,loc_b,R)-Loc[i],0));//找出最小值，在右减去Loc[i]是最小值，同时要防止减成负数
	}
	for(register int i=loc_b;i<=n;++i)//同理
	{
		int L=lower_bound(Loc+1,Loc+loc_b,a[i])-Loc;
		if(L>=loc_b) continue;
		ans=min(ans,max(Loc[i]-query_max(1,1,n,L,loc_b-1),0));//找出最大值，用Loc[i]减后是最小值
	}
	if(ans==0x7fffffff)//ans自始至终没有被更改过，说明所有情况都被continue了，即无法困住
	    printf("-1\n");
	else
    	printf("%d\n",ans);
	return 0;
}
```

完

---

## 作者：Cure_Wing (赞：1)

* 首先发现若冲击波左右防守的端点在 $[l,r]$，则它可获得最大的冲刺长度就是 $r-l$。   

* 如果直接模拟可以在两种情况时计算出当前需要加固的值。在冲不掉左端点时，加固右端点；在冲不掉右端点时，加固左端点。当两个点都冲不掉，可以直接得出答案为 $0$，但是当两个点都能冲就不太好做了。  

* 不妨换种角度思考，在加固某一端点 $A$ 时，只要模拟出在另一端一直撞，最远能撞到哪个点停下，就可以知道此时这个点A 具体要加固多少才能破防。所以分两次算，第一次枚举要加固哪个左端点，让牛一直只撞右边的；第二次则枚举要加固的右端点，同理。最后只要把枚举每个点时的答案打擂台比较最小值就行了。无解的特判就不多讲了。时间复杂度为 $O(n)$ 。
* --选自模拟赛题解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b,l1,l2,ans=0x1fffffff;
struct node{int a,p;void scan(){scanf("%d%d",&a,&p);}}t[111111];
bool cmp(node a,node b){return a.p<b.p;}
int main(){
	scanf("%d%d",&n,&b);for(int i=1;i<=n;++i) t[i].scan();
	sort(t+1,t+n+1,cmp);t[0].p=b;
	l2=upper_bound(t+1,t+n+1,t[0],cmp)-t;l1=l2-1;
	for(int i=l1,j=l2;i>0&&j<=n;--i){
		while(j<=n&&t[j].a<t[j].p-t[i].p) ++j;
		if(j<=n) ans=min(ans,max(0,t[j].p-t[i].p-t[i].a));
	}
	for(int i=l1,j=l2;i>0&&j<=n;++j){
		while(i>0&&t[i].a<t[j].p-t[i].p) --i;
		if(i>0) ans=min(ans,max(0,t[j].p-t[i].p-t[j].a));
	}
	printf("%d\n",ans==0x1fffffff?-1:ans);
	return 0;
}
```


---

## 作者：SASUKE__ (赞：1)

身为蒟蒻的我没想出模拟，想出来线段树，我真是个~~毒瘤~~  
~~我觉得模拟很玄~~，如果跟我一样的可以看看我这篇~~毒瘤数学~~题解

以下分析不考虑无法困住贝茜和不需要增加干草堆高度的情况，等同于

可以困住贝茜且需要增加干草堆高度的情况

------------

题目大意：在贝茜的左边位置选取一个干草堆，在右边选取一个干草堆，只能增加左边或右边一堆的高度，求最小增加量。

考虑暴力：  

按照干草堆的位置从小到大排序  

$for$ 左边的干草堆 $i$  
$for$ 右边的干草堆 $j$  
$minval = min( minval,cost(i,j) )$ 

可以困住贝茜且需要增加干草堆高度的情况 <——> 增加第 $i$ 堆或者增加第j堆（只增加其一） 

设第 $x$ 堆草的位置为 $pos_x$,高度为 $h_x$，$cost$ 函数应该这样写  
```cpp
int cost(int i,int j) {//只考虑需要增加i或者j的情况，不考虑都不增加或者无法困住贝茜的情况
	if ( h[i] < pos[j] - pos[i] ) return pos[j] - pos[i] - h[i];//i堆干草需要增加;
	else return pos[j] - pos[i] - h[j];
}
```
时间复杂度 $O(n^2)$

考虑去掉一维 $for$，只枚举左端点 $i$  

问题变为：已知 $pos_i$,$h_i$, 求 $cost(i,j)$ 的最小值

因为枚举的是 $i$，所以 $pos_i$ 和 $h_i$ 都是常数，$j$ 是自变量，设 $g(j)=cost(i,j)$,因为 $cost$ 分了两种情况，所以 $g(j)$ 是一个分段函数，求分段函数的最小值我们分类讨论。

先明确如何预处理的  

$struct$ 干草堆 { $pos,h$ }  
$sort$(按照 $pos$ 从小到大)  
找出一个 $mid_id$，下标小于 $mid_id$ 的为贝茜左边的干草堆，下标大于等于 $mid_id$ 的为贝茜右边的干草堆。

分类讨论：

1.第 $i$ 堆干草需要增加：  

自变量 $j$ 的限制条件：$pos_j$ > $pos_i$ + $h_i$ (由 $cost$ 函数的第一个 $if$ )  且 $j$ 属于 [$mid_id$ , $n$]

$g(j)$ = $pos_j$ - $pos_i$ - $h_i$  
求 $g(j)$ 最小，就是求 $pos_j$ 最小，又因为已经以 $pos$ 为关键字从小到大排序了，所以 $pos_j$ 与 $j$ 单调性一致。所以 $g(j)$ 最小就是要 $j$ 最小。  

因为关于 $i$ 的项都是常数，令 $key$ = $pos_i$ + $h_i$，问题就很清晰了： 在一个 $pos$ 单调上升的序列中，$j$ 属于 $[mid_id , n]$,求最小的 $j$，使 $pos_j$ > $key$  
解决方法：二分查找 （我用线段树 $AC$ 的，因为反正第二种情况要用线段树，可以看看我写的~~鬼畜的~~ $queryMinPos$ 成员函数，$public$ 里面有注释）

2.第 $i$ 堆干草不需要增加(看上面的黑体加粗放大字体，可以推出第 $j$ 堆干草需要增加)：

自变量 $j$ 的限制条件：$pos_j$ <= $pos_i$ + $h_i$(分类讨论中情况1的补集)  且 $j$ 属于 $[mid_id , n]$  
同理：  
$g(j)$ = $pos_j$ - $h_j$ - $pos_i$  
分析单调性，$g(j)$ ...... ~~震惊了没有单调性wc这题不能优化~~  
换个思路，依然找 $j$，但是不是 $j$ 而是关于 $j$ 的项。当 $g(j)$ 最小时，$pos_j$ - $h_j$ 最小，再看看 $j$ 的限制条件：  
$pos_j$ <= $pos_i$ + $h_i$ 且 $j$ 属于 $[mid_id , n]$  
显然我们可以二分查找出 $j$ 的区间（$pos_j$ 关于 $j$ 单调递增，不等号右边是常数）  
 $j$ 属于某个已经确定的区间，找 $pos_j$ - $h_j$ 最小，用线段树，维护区间 $[l,r]$，$x$ 属于 $[l,r]$，$pos_x$ - $h_x$ 的最小值

可以困住贝茜且需要增加干草堆高度的情况分析结束

------------

1.如果不可以困住贝茜，充要条件为：任意 $i$ ，找不到 变量 $j$ 满足 限制条件，代码可以这样写：  
$for$ $i$ ...    
$if$ 二分查找,找不到满足条件的 $j$  
$minval = min( minval,INF );$  
......  
......  
//输出答案  
$if(minval==INF)$...... 

2.如果不需要增加高度，充要条件为：存在 $i$ ，找到 变量 $j$ 满足  
$pos_j$ <= $pos_i$ + $h_i$ 且 $j$ 属于 $[mid_id , n]$（情况2） 且 $h_j$ >= $pos_j$ - $pos_i$  
情况2的返回值：$g(j)$ = $pos_j$ - $h_j$ - $pos_i$  
由 $h_j$ >= $pos_j$ - $pos_i$  
可得 $g(j) <= 0$  
综上，如果不需要增加高度，存在 $i$，$j$，使 $g(j)$ 函数返回值小于等于0  
代码可以这样写：
$for$ $i$ ...    
$if$ 二分查找,找到满足条件的 $j$  
$minval$ = $min$( $minval$, 二分查找或者线段树求 $g(j)$ 最小值 );  
......  
......  
//输出答案  
$if(minval<=0) printf("0");$

讨论完所有情况，可以附上~~线段树函数名巨长的、手打二分不用STL巨毒瘤的~~代码啦。（看懂了前面的分析~~毒瘤数学~~，自己打代码也完全可以） 时间复杂度$O(nlogn)$

------------
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<fstream>
#define increase(x,l,r) for(register int x=l;x<=r;++x)
#define decrease(x,r,l) for(register int x=r;x>=l;--x)
#define N 100005
#define INF 0x7fffffff
using namespace std;

inline void read(int &x) {
	x=0;
	short op=1;
	char ch;
	while(ch=getchar(),!('0'<=ch&&ch<='9'||ch=='-'));
	if(ch=='-') op=-1,ch=getchar();
	while('0'<=ch&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=op;
}

inline int min(int x,int y,int z) {
	if(x>y) x=y;
	if(x>z) x=z;
	return x;
}

class seg{//毒瘤用类写
	
	private:
		
		struct NODE{
			int l,r,min;
			NODE(){l=r=min=0;}
		}node[4*N];
		int p_node,n;
		
		inline int min(int x,int y) {return x<y?x:y;}
		
		inline void pushup(int now) {node[now].min=min(node[node[now].l].min,node[node[now].r].min);}
		
		inline int build(int l,int r,int *val) {
			int now=++p_node;
			if(l==r) {
				node[now].min=val[l];
				return now;
			}
			int mid=(l+r)>>1;
			node[now].l=build(l,mid,val);
			node[now].r=build(mid+1,r,val);
			pushup(now);
			return now;
		}
		
		inline int queryMin(int now,int l,int r,int L,int R) {
			if(l>R||r<L) return INF;
			if(L<=l&&r<=R) return node[now].min;
			int mid=(l+r)>>1;
			return min(queryMin(node[now].l,l,mid,L,R),queryMin(node[now].r,mid+1,r,L,R));
		}
		
		inline int queryMinPos(int now,int l,int r,int L,int R,int key) {
			if(l>R||r<L) return INF;
			if(node[now].min>key) return INF;
			if(l==r) return l;
			int mid=(l+r)>>1;
			int v=queryMinPos(node[now].l,l,mid,L,R,key);
			if(v!=INF) return v;
			return queryMinPos(node[now].r,mid+1,r,L,R,key);
		}
		
	public:
		
		inline seg() {p_node=0;}
		
		inline void setSize(int size) {n=size;}
		
		inline void build(int *val) {
			build(1,n,val);
		}
		
		inline int queryMin(int l,int r) {
			return queryMin(1,1,n,l,r);
		}
		
		inline int queryMinPos(int l,int r,int key) { //在区间内找小于等于key的最小位置 
			return queryMinPos(1,1,n,l,r,key); 
		}
		
}tree;

struct grass{
	int h,pos;
}a[N];
inline bool cmp(grass x,grass y) {return x.pos<y.pos;}
int val[N];

int main() {
	int n,midpos;
	read(n);read(midpos);
	increase(i,1,n) read(a[i].h),read(a[i].pos);
	sort(a+1,a+n+1,cmp);
	increase(i,1,n) val[i]=a[i].pos-a[i].h;
	tree.setSize(n);
	tree.build(val);
	int ans=INF;
	int l=1,r=n,mid,mid_id=0;
	while(l<=r) {
		mid=(l+r)>>1;
		if(a[mid].pos<midpos) mid_id=mid,l=mid+1;
		else r=mid-1;
	}
	if(!mid_id) {
		printf("-1");
		return 0;
	}
	if(mid_id==n) {
		printf("-1");
		return 0;
	}
	++mid_id;//预处理加找mid_id到此完成
	for(register int i=1;a[i].pos<midpos;++i) {
		l=mid_id,r=n;
		int find=0;//找满足条件的j
		int t1,t2;
		while(l<=r) {
			mid=(l+r)>>1;
			if(a[mid].pos<a[i].pos+a[i].h) find=mid,l=mid+1;
			else r=mid-1;
		}
		if(!find) {
			if(a[mid_id].pos==a[i].pos+a[i].h) find=mid_id,t1=tree.queryMin(mid_id,find),t1-=a[i].pos;
			else t1=INF;
		}
		else {
			if(a[find+1].pos==a[i].pos+a[i].h) ++find;
			t1=tree.queryMin(mid_id,find),t1-=a[i].pos;
		}//t1保存分类讨论中第一种情况的结果
		if(!find) find=mid_id;
		else ++find;
		if(find>n) t2=INF;
		else {
			t2=tree.queryMinPos(find,n,a[i].pos);
			(t2!=INF)&&(t2=a[t2].pos,t2-=a[i].h+a[i].pos);
		}//t2保存分类讨论中第二种情况的结果
		ans=min(ans,t1,t2);
	}
	if(ans==INF) printf("-1");
	else printf("%d",ans>0?ans:0);
	return 0;
}
```






---

## 作者：ZZQF5677 (赞：0)

### 解题思路
模拟题：模拟奶牛冲干草捆的时候，FJ 对奶牛进行的防守。

+ 首先模拟奶牛向左边优先冲干草捆:
> + 奶牛能往左边就往左边走。
> + 奶牛越界了就退出。
> + 如果奶牛被左边的某一个干草捆挡下来了，那么 FJ 就尝试防守右边的干草捆。
> + 然后如果右边根本不用防守，那就退出。
> + 否则，模拟不防守右边。

+ 然后模拟奶牛向右边优先冲干草捆:
> + 奶牛能往右边就往右边走。
> + 奶牛越界了就退出。
> + 如果奶牛被右边的某一个干草捆挡下来了，那么 FJ 就尝试防守左边的干草捆。
> + 然后如果左边根本不用防守，那就退出。
> + 否则，模拟不防守左边。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 1e9;
int n, b, ans = INF;
struct Node {
  int s, p;  //大小，距离。
} cow[200005];
int cowl, cowr;
bool cmp(Node a, Node b) {
  return a.p < b.p;
}
int main() {
  // freopen("trapped.in", "r", stdin);
  // freopen("trapped.out", "w", stdout);
  scanf("%d%d", &n, &b);
  cowl = 1;
  cowr = n;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &cow[i].s, &cow[i].p);
    // cin >> cow[i].s >> cow[i].p;
  }
  stable_sort(cow + 1, cow + 1 + n, cmp);
  int x = 0, y = 0;
  for (int i = 1; i < n; i++) {
    if (cow[i].p <= b && b <= cow[i + 1].p) {
      cowl = x = i;
      cowr = y = i + 1;
      break;
    }
  }
  /*
  左边优先:
  能往左边就往左边走。
  越界了就退出。
  如果被左边的某一个干草捆挡下来了，那么 FJ 就尝试防守右边的干草捆。
  然后如果右边根本不用防守，那就退出。
  否则，模拟不防守右边。
  */
  while (cowr <= n) {  //左边优先。
    while (0 < cowl && cow[cowl].s < cow[cowr].p - cow[cowl].p) {
      cowl--;
    }
    if (cowl < 1) {
      break;
    }
    ans = max(0 /*有时候不用防守，所以会减出负数。*/, min(ans, cow[cowr].p - cow[cowl].p - cow[cowr].s));  //防守。
    if (cow[cowr].s >= cow[cowr].p - cow[cowl].p) {                                                        //不用防守左边。
      break;
    } else {
      cowr++;
    }
  }
  // puts("114514");
  cowl = x;
  cowr = y;
  /*
  右边优先:
  与左边差不多。
  */

  while (1 <= cowl) {  //右边优先。
    while (cowr <= n && cow[cowr].s < cow[cowr].p - cow[cowl].p) {
      cowr++;
    }
    if (cowr > n) {
      break;
    }
    ans = max(0, min(ans, cow[cowr].p - cow[cowl].p - cow[cowl].s));
    if (cow[cowl].s >= cow[cowr].p - cow[cowl].p) {
      break;
    } else {
      cowl--;
    }
  }
  if (ans == INF) {
    puts("-1");
  } else {
    printf("%d\n", ans);
  }
  return 0;
}
```

---

## 作者：哈士奇憨憨 (赞：0)

## 题意
一维数轴上有一些带值障碍点，障碍点将数轴划成一些区间。如果当前区间的长度大于左边界障碍点的值，就可以将该障碍点删除，右边界同理。

给定初始点，以包含该点的区间作为初始区间，现在可以任选一个障碍点并增加该点的值，求最少的增量，使得无法删除最左和最右的障碍点。
## 思路
首先，根据初始点找到初始区间，然后从初始区间开始，不断按照规则删除边界障碍点并扩大区间。如果最终无法删除最左和最右障碍点，必然得到了一个无法再扩大的区间 $[i,j]$，此时必然有 $p_j-p_i<\min(s_i,s_j)$。

由于只能增加一个障碍点的值，所以可以尝试对该障碍点进行枚举，并让该障碍点作为最终区间的边界。障碍点在初始点的左边和右边是两种不同情况，我们先分析在左边的情况。

考虑枚举最终区间 $[i,j]$ 的左边界 $i$ 作为可修改障碍点，此时可行的右边界需要满足 $p_j-p_i<s_j$,调整一下不等式得到 $p_j-s_j<p_i$，可见随着 $p_i$ 的增大，右边界按照 $p_j-s_j$ 的顺序变成可行。所以我们可以按照 $p_j-s_j$ 对右边界排序，然后由小到大枚举 $p_i$，这样可行的右边界就是连续的一段前缀。

然后考虑答案，$i$ 需要的增量为 $\max(0,p_j-p_i-s_i)$，其中 $p_i+s_i$ 与 $j$ 无关，所以我们只需要找到 $p_j$ 的最小值即可，这个可以在维护可行的右边界时顺便求出。

障碍点在初始点右边的情况是相似的，可以用同样的方法分析，最终就能求出最优解了。

## 复杂度
### 时间
障碍点排序 $O(N \log N)$。

枚举障碍点 $O(N)$，调整另一个点均摊 $O(1)$，计算 $O(1)$， 总共 $O(N)$。

总时间复杂度为 $O(N \log N)$。
### 空间
记录点 $O(N)$。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;

const int kMaxN = 501, kInf = 1e9;

Pii e[kMaxN];
int f[kMaxN][kMaxN], n, k, ans = kInf;

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].first >> e[i].second;
  }
  fill(f[0], f[n + 1], kInf);  // 初始化
  f[1][0] = 0;                 // 边界
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= k; j++) {                                                                                      // 枚举状态
      for (int l = max(1, i - j - 1); l < i; l++) {                                                                     // 枚举转移
        f[i][j] = min(f[i][j], f[l][j - (i - l - 1)] + abs(e[l].first - e[i].first) + abs(e[l].second - e[i].second));  // 更新最值
      }
    }
  }
  for (int i = 0; i <= k; i++) {  // 枚举目标状态
    ans = min(ans, f[n][i]);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：dzysc (赞：0)

大体思路是这样的：

其实是个好玩的模拟啊

先找到b点在数轴上所对应的I值，也就是b位于哪两堆干草之间

然后分别从b点向左向右线性扫描

分别判断如果当前扫到这一堆的加干草的值，并打擂台就可以了

值得注意的一点是：如果我发现加干草并不能组织Bessie，要输出-1

一开始我还以为没有这种可能呢。。。

上代码！！！

@wjcwinmt 大神犇







```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 1000000001
#define index first
#define w second
int main()
{
    int n,b;
      cin>>n>>b;
      vector<pair<int, int> >a(n);
      for(int i=0;i<n;i++)
    {
        cin>>a[i].w>>a[i].index;
      }
      sort(a.begin(),a.end());
      int ans=MAXN;
      int startpos=lower_bound(a.begin(),a.end(),make_pair(b,0))-a.begin();
      int j=startpos;
      for(int i=startpos-1;i>=0;i--)
      {
        while(j<n&&a[j].index-a[i].index<=a[i].w)
        {
              ans=min(ans,a[j].index-a[i].index-a[j].w);
              j++;
        }
      }
      j=startpos-1;
      for(int i=startpos;i<n;i++)
    {
        while(j>=0&&a[i].index-a[j].index<=a[i].w)
        {
              ans=min(ans,a[i].index-a[j].index-a[j].w);
              j--;
        }
      }
      if(ans==MAXN)
      {
        cout<<-1<<endl;
      }
    else
    {
        cout<<max(ans,0)<<endl;
      }
      return 0;
}

```

---

