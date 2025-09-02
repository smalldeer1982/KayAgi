# [USACO13DEC] Milk Scheduling S

## 题目描述

Farmer John has N cows that need to be milked (1 <= N <= 10,000), each of which takes only one unit of time to milk.

Being impatient animals, some cows will refuse to be milked if Farmer John waits too long to milk them.  More specifically, cow i produces g\_i gallons of milk (1 <= g\_i <= 1000), but only if she is milked before a deadline at time d\_i (1 <= d\_i <= 10,000).  Time starts at t=0, so at most x total cows can be milked prior to a deadline at time t=x.

Please help Farmer John determine the maximum amount of milk that he can obtain if he milks the cows optimally.

FJ有N(1 <= N <= 10,000)头牛要挤牛奶，每头牛需要花费1单位时间。


奶牛很厌烦等待，奶牛i在它的截止时间d\_i (1 <= d\_i <= 10,000)前挤g(1 <= g\_i <= 1000)的奶，否则将不能挤奶。时间t开始时为0，即在时间t=x时，最多可以挤x头奶牛。


请计算FJ的最大挤奶量。


## 说明/提示

There are 4 cows.  The first produces 10 gallons of milk if milked by time 3, and so on.


Farmer John milks cow 3 first, giving up on cow 4 since she cannot be milked by her deadline due to the conflict with cow 3.  Farmer John then milks cows 1 and 2.


## 样例 #1

### 输入

```
4 
10 3 
7 5 
8 1 
2 1 
```

### 输出

```
25 
```

# 题解

## 作者：七夜 (赞：46)

单纯的贪心，考虑到选择的问题，担心的就是前面的选择会不会对后面选择造成影响，所以我们换个方向考虑一下，也就是利用贪心思想了

我们按照加仑牛奶的价值进行一个排序，优先挤价值大的肯定是没错的，然后就是考虑，用哪一时间去挤得问题，这个其实也很好解决，因为每个时间点只能挤一头奶牛的奶，所以我们按照每个奶牛最后的选取时间往前找，尽量找到靠后面的时间不就可以了嘛

有没有觉得问题一下子豁然开朗了？

那么接下来的问题很简单定义结构体，按照牛奶价值给结构体排序。可能有点人还不是太会，我这里提供一个自己写的昂（dalao别笑）：

```
int cmp(love x,love y)
{
	return x.milk>y.milk;
}
```

剩下的就更简单了，循环到每一个奶牛，然后看看能否挤奶，能就加和，不能就跳过。

问题就这么解决了，下面上代码（只提供借鉴，不准复制粘贴）：

```
#include<bits/stdc++.h>//偷懒专用库 
#define ll long long
#define INF 15200
#define MAXN 99999//宏定义 
using namespace std;

inline int read(){
  char c=getchar();int x=0,f=1;
  while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
  while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
  return x*f;
}//这里是快读，可以提供借鉴，忽略掉也无所谓的 

struct love
{
	int milk;
	int time;
}you[INF];//定义一个机构体 

int cmp(love x,love y)
{
	return x.milk>y.milk;
}//结构体排序，按照加仑牛奶的价值从大到小排，先处理价值大的，保证不能挤得越小越好 

int n,ans,tot;
int a[INF];//判断这个时间点挤没有挤过奶 

int main()//主函数部分 
{
    n=read();//读入 
    for(int i=1;i<=n;++i)
	  {
	  	you[i].milk=read();
	  	you[i].time=read();
      } //读入加仑牛奶价值和挤得最后时间 
	sort(you+1,you+1+n,cmp);//排序 
	for(int i=1;i<=n;++i)//判断是否能挤 
	 {
	 	tot=0;//这是一个判断用的东西，待会就明白了 
	 	for(int j=you[i].time;j>=1;--j)//从他的最大时间开始，一直到一，看看有没有一个时间点没挤过 
	 	 {
	 	 	if(a[j]==0)//如果这个点没挤过，就代表当前的牛奶可以被挤 
	 	 	 {
	 	 	 	a[j]=1;//把这个点变成挤过 
	 	 	 	tot=1;//然后标记成挤过 
	 	 	 	break;//跳出循环 
			 }//因为此时找到是最晚能挤的时间，所以不会影响以后的选择 
		 }
		if(tot==1)
		 ans+=you[i].milk;//如果标记过，证明奶挤过，所以答案加上价值 
     }
    cout<<ans;//输出
	return 0;//养成好习惯，从你我做起 
}
```
给蒟蒻一个赞吧，蒟蒻还没有赞呢

---

## 作者：llzzxx712 (赞：18)

# P3093

[（可能）更好的阅读体验](https://www.luogu.com.cn/blog/llzzxx712/solution-p3093)

[传送门](https://www.luogu.com.cn/problem/P3093)
## 题目描述
- 给你N个任务，每个任务 $i$ 都有截止日期  $d_{i}$ 和报酬$g_{i}$。
- 完成每个任务时间相同，都为一个单位。
- 你需要使所得报酬最大并输出。
- $1<=d_{i},n<=10^5,1<=g_{i}<=10^4$
## 题目分析
这是一道**贪心**题是肯定的，我使用了**二叉堆/优先队列**来解决。

**那具体怎么贪心呢？**

先是一个**错误的贪心思路**(注意是错的）——在每个时间点都选择当前报酬最高的任务进行完成。

这很容易举出反例，比如这里有两个工作，一个报酬为5，截止日期为3 。另一个报酬为4，截止日期为1 。按照此贪心思路我们先选第一个工作得到5点报酬然后第二个工作因截止而放弃。但很显然我们应该先选第二个工作再做第一个，这样可以获得9点报酬。

那么我们修改我们的思路——把任务按照时间排序，按照时间选择任务。

但仍可以举出反例，这里有三个任务，第一个任务截止时间为1，报酬为1，后两个任务截止时间都为2，报酬分别为8和9，按照此思路我们会先选择任务1，但很显然我们应该选择任务2、3而不选1.

这需要我们进一步改进，我们注意到每个任务完成的时间都为1，这意味着我们在一个时间可以做任意一个任务。当我们遇到一个报酬更大的任务且时间不够时，我们应该放弃前面选择的报酬最小（且比当前任务报酬小）的任务进行替换——这就是贪心中的**退流思想**。我们可以建立一个小根堆，将每次选择的任务报酬放入堆中，每次时间不够时取出堆顶，与当前任务进行比较。

## 思路总结
1. 读入每个工作并用结构体储存，按时间从小到大排序。
1. 建立小根堆与每次任务比较，保证结果最优。

## 易错点
- 替换任务时不需要增加时间

## 代码（带注释）

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define N 10002
using namespace std;
void read(int &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
struct cow{
	int g,d;//g为奶，d为截止时间 
}a[N];
int cmp(cow aa,cow bb){
	return aa.d<bb.d;//按照时间排序 
}
priority_queue < int > q;
int n,ans,t;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		read(a[i].g),read(a[i].d);
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1,t=1;i<=n;i++){//i表示现在扫描到第几个任务，t表示当前花费了多少时间
		if(a[i].d<t){//时间不够了 
			int x=-q.top();//取负存入、取出（使它为小根堆） 
			if(x<a[i].g){//如果取出的任务报酬比当前小，替换 
				q.pop();q.push(-a[i].g);
				ans+=a[i].g-x; 
			}
		}
		if(a[i].d>=t){//时间充足，将当前任务放入 
			q.push(-a[i].g); 
			ans+=a[i].g;t++;
		}
	}
	cout<<ans;
}

```



**最后**：令人喜爱的双倍经验（有一点改动哦）

[P2949 双倍经验](https://www.luogu.com.cn/problem/P2949)

**写题解不易，给个赞呗**

---

## 作者：YANG_XIAO (赞：12)

#蒟蒻题解

实际就是贪心，主要就是把数据按第一要素**milk**来按降序排列or第二要素**Time**按升序排列

然后一遍循环，每加一个就把当前位置记为已用，这样就能保证每一遍都是当前最优解...

下面附代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct MILK
{
    int milk,Time;
    bool operator < (const MILK & x) const
    {
        return x.milk!=milk ? x.milk < milk : x.Time > Time;
    }
} a[10005];

bool been_milked[10005];//记录当前位置是否已被占用 

int main()
{
    int n;
    cin >> n;
    for (int i=1; i<=n; i++)
        cin >> a[i].milk >> a[i].Time;
    sort(a+1,a+n+1);
    int ans=0;
    for (int i=1; i<=n; i++)
    {
        int can_milk=0;
        for (int j=a[i].Time;j>=1;j--)
            if (!been_milked[j])
            {
                can_milk=j;
                break;
            }//找到向前最近的空位 
        if (can_milk)
        {
            been_milked[can_milk] = true;
            ans+=a[i].milk;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：空气树 (赞：11)

这题贪心是肯定的，但不优化时间会很勉强，所以大佬们用了优化：小根堆 

在此，提出新的优化方法——并查集
```cpp
#include<bits/stdc++.h>
using namespace std;
inline void in(int &x){
    int ff=1;x=0;char c=getchar();x=0;
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    x*=ff;
}
struct tt{
    int x,u;
}a[10005];
bool cmp(tt xx,tt yy){
    return xx.u>yy.u;
}
//贪心，按价值排序
int f[10005],ss,mx;
inline int find(int x){
    if(f[x]==x)return x;
    return f[x]=find(f[x]);
}
//并查集模板
int main(){
    int n,r;in(n);
    for(int i=1;i<=n;i++){
        in(a[i].u);in(a[i].x);mx=max(mx,a[i].x);
    }
    for(int i=0;i<=mx;i++)f[i]=i;
    //并查集初始化
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        r=find(a[i].x);
        //首先贪心思路：记录找最迟时间，用并查集找到最近的位占用时间
        if(r<1&&r<=a[i].x)continue;
        //不符合要求或无时间了，直接退出
        ss+=a[i].u;f[r]=find(r-1);
        //可以的话就加上价值，比与之前的时间连接，表示此时间已占，以后只能往前找时间
    }
    cout<<ss<<endl;
    return 0;
} 

```
只要不被卡，这样的时间复杂度可以降到O(n)，当然也没那么好的数据，不过优化了不少。

---

## 作者：lizongru (赞：9)

看到楼上神犇们写的方法感觉自愧不如,OrzOrz。

但本蒟蒻还是想分享一下我突发奇想想出来的做法，因为有n头奶牛，所以就是从后往前枚举n个时间，再从1到n搜最优解输出（好吧，说了这么久就是贪心）。但是不需要高级数据结构，也不用dp，本蒟蒻还是觉得很巧妙的。。。

下面贴AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,maxn=1,No=0,ans=0,g[10005],d[10005];
    //maxn:存储当前循环搜到的最大的挤奶量；No:当前搜到的答案的编号； 
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>g[i]>>d[i];//输入
    for(int i=n;i>=1;--i)
        {
            for(int j=1;j<=n;++j)
              if(d[j]>=i&&g[j]>=maxn)
              {
                  No=j;
                  maxn=g[j];
              }
            if(No!=0){g[No]=0;d[No]=10005;ans+=maxn;}//这样处理后就不会重复搜索当前答案；
            maxn=0;
            No=0;//还原；
        }
    cout<<ans;
    return 0;
}
\\自己感觉还是很简洁的，蒟蒻求过
```

---

## 作者：翼德天尊 (赞：6)

**经典的贪心题目**


------------
### STEP 1 主要思路

~~根据经典的丛林法则~~ ，我们肯定是要奶多者优先被选中啦！但是还有时间的限制，为了保证最优，我们要把想选的奶牛尽量的往后放，所以，当当当，代码就出现了！


------------
### STEP 2 大致流程

1.输入数据

2.根据价值排序

3.从价值高的奶牛开始做第一层循环，第二层循环则为从该奶牛的最终期限向1循环，如果该时间点没有奶牛占用，就将他占用，并总答案++（所以我们要在设一个数组记录该时间占用情况，一个变量记录答案）

4.输出总答案


------------

### STEP 3 AC代码及注释
```
#include<bits/stdc++.h>//万能头文件最棒
using namespace std;
int n,ans,t[10001];//分别记录奶牛数，
struct node{
	int d,g;
}cow[10001];//结构体方便排序
int cmp(node x,node y){
	return x.g>y.g;
}//结构体自带排序函数
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d %d",&cow[i].g,&cow[i].d);
	}//输入流
	sort(cow+1,cow+1+n,cmp);//排序
	for (int i=1;i<=n;i++){
		for (int j=cow[i].d;j>=1;j--){//做循环
			if (!t[j]){//如果该时间点为空
				t[j]=1;
				ans+=cow[i].g;
				break;
			}
		}
		
	}
	printf("%d\n",ans);//输入答案
	return 0;//好习惯人人养
}
```


------------
### STEP 4 完结撒花！

这篇题解就这么的告一段落了，如果还有不懂的问题，欢迎在评论区留言，我会第一时间解答哒！

如果全部都搞懂了，点个赞纪念一下你的成长吧！


---

## 作者：Expecto (赞：3)

直接dp啊，之前要按deadline排序下


设F[j]表示到时间j得到最大值，


```cpp
f[j]=max(f[j],f[j-1]+g[i]);
#include<bits/stdc++.h>
using namespace std;
pair<int,int> g[10010];
int f[10110]={0};
int main(){
    int n;
    scanf("%d",&n);
    int ans=0;
    for (int i=1;i<=n;i++) scanf("%d%d",&g[i].second,&g[i].first);
    sort(g+1,g+1+n);
    for (int i=1;i<=n;i++) {
        for (int j=g[i].first;j;j--){
            f[j]=max(f[j],f[j-1]+g[i].second);
            ans=max(f[j],ans);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：AOTO (赞：2)

## 显然，这道题用小根堆方法做较优，非常省时间
### 将奶牛按时间从小到大排序。再进行堆排序，如果当前堆中的奶牛数比奶牛结束时间小的话就说明这头奶牛可以挤奶（入堆），反之将挤奶量与当前堆中最小值比较，如果比最小值大，将当前奶牛的挤奶量放到最小的那个位置，再更新堆。直到所有牛做完为止
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ll{
	int x,y;
}g[1000001];
int w,a[1000001],n,x,y,s;
bool cmp(ll a,ll b)
{
	return a.y<b.y;
}
void down(int r)
{
	int x=r*2;
	while(x<=w)
	{
		if((x+1<=w)&&(a[x+1]<a[x]))x+=1;
		if(a[x]>=a[r])break;
		int t=a[x];a[x]=a[r];a[r]=t;
		r=x;x=r*2;
	}
}
void up(int w1)
{
	while((w1>1)&&(a[w1/2]>a[w1]))
	{
		int t=a[w1/2];a[w1/2]=a[w1];a[w1]=t;
		w1=w1/2;
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>g[i].x>>g[i].y;
	sort(g+1,g+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		x=g[i].x;y=g[i].y;
		if(w<y)
		{
			w++;a[w]=x;s+=x;up(w);
            //如果能放入就入堆，加上当前奶牛的挤奶量
		}
		else
		if(x>a[1])
		{
			s=s-a[1]+x;a[1]=x;down(1);
            //不能放入就与最小的数判断，如果打，就先减去最小的再加上当前挤奶量，再更新堆
		}
	}
	cout<<s;
	return 0;
}
```


---

## 作者：吃瓜群众syc (赞：1)

蒟蒻贪心的核心思想就是决策当前奶牛的选与不选。

首先，将奶牛们挤奶的deadline从小到大排个序，然后正着循环进行决策。

我们可以开一个小根堆（堆里面存的是当前所选的每一头奶牛的挤奶量的集合）和一个记录当前所选的奶牛总数now（这个now本质上就是当前已经过的时间）。当决策到奶牛i时：

（1）如果他的deadline>now，那么直接选上他，累加一下答案。

（2）反之，则拿他的挤奶量和之前所选的奶牛中挤奶量最少的比较一下。若>之前所选的奶牛中挤奶量最少的，那我们就优先挤当前的这头奶牛。（别忘了把他的挤奶量压入堆中）

AC代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

priority_queue<int>q;
const int MAXN=10001;
int n,ans,tot;
struct node{
	int num,tim;
}a[MAXN];

bool cmp(node a,node b)
{
	return a.tim<b.tim;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d%d",&a[i].num,&a[i].tim);
	sort(a+1,a+n+1,cmp);
	q.push(a[1].num*(-1)),tot=1,ans=a[1].num;
	for(int i=2;i<=n;i++)
	{
		if(a[i].tim>tot)
		{
			tot++,ans+=a[i].num;
			q.push(a[i].num*(-1));
		}	
		else
		{
			int now=(-1)*(q.top());
			if(a[i].num>now)
			{
				ans+=a[i].num-now;
				q.pop();
				q.push(a[i].num*(-1));
			}
		}
	}
	printf("%d",ans);
}
```

---

## 作者：Mogician (赞：1)

#pascal版题解

一看要求最优解十有八九是dp，先按d[i]从小到大排序再dp。状态转移方程：dg[j]:=max{dg[j],dg[j-1]+g[i]}(1<=i<=n,d[i]>=j>=1)**注意j要从d[i]到1循环**

```cpp
var d,g,dg:array[0..10000] of longint;
    i,j,k,t,m,n,p:longint;
procedure qsort(l,r: longint);
      var
         i,j,x,x1,y: longint;
      begin
         i:=l;
         j:=r;
         x:=d[(l+r)>>1];
         x1:=g[(l+r)>>1];
         repeat
           while (d[i]<x)or(d[i]=x)and(g[i]<x1) do
            inc(i);
           while (x<d[j])or(d[j]=x)and(x1<g[j]) do
            dec(j);
           if not(i>j) then
             begin
                y:=d[i];
                d[i]:=d[j];
                d[j]:=y;
                y:=g[i];
                g[i]:=g[j];
                g[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           qsort(l,j);
         if i<r then
           qsort(i,r);
      end;
function max(a,b:longint):longint;
begin
 if a>b then exit(a);
 exit(b);
end;
begin
 assign(input,'233.in');
 reset(input);  //关联文件便于调试
 readln(n);
 for i:=1 to n do readln(g[i],d[i]);
 qsort(1,n);//快排
 for i:=1 to n do
  for j:=d[i] downto 1 do
   begin
    dg[j]:=max(dg[j],dg[j-1]+g[i]);
    t:=max(dg[j],t);
   end;//dp
 writeln(t);
end.
```

---

## 作者：CK666 (赞：1)

呃，本蒟蒻并没有想到dp，只是想到一个算是模拟的堆吧……

记录时间的最大值，先按时间从小到大sort一遍，然后来一个从最大时间到1的逆循环，用堆维护当前时间可以取的最大价值

然后，就好了啊……




```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct note
{
    int t,w;
    bool operator < (const note lyf) const {return t<lyf.t;}
}a[10001];
struct cmp
{
    bool operator () (const note p,const note q) {return p.w<q.w;}
};
priority_queue <note,vector<note>,cmp> que;
int n,max_t,g,ans;
int main(void)
{
    scanf("%d",&n);
    for (int i=1; i<=n; i++)
    {
        scanf("%d%d",&a[i].w,&a[i].t);
        max_t<a[i].t?max_t=a[i].t:0; 
    }
    sort(a+1,a+1+n);
    g=n;
    for (int i=max_t; i>=1; i--)
    {
        while (a[g].t==i) que.push(a[g--]);
        if (!que.empty())
        {
            ans+=que.top().w;
            que.pop();
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Starria的脑残粉 (赞：1)

肛道理这题是不是和今年noid2t2的80分暴力有点异曲同工之处啊。。

异曲同工个p啊这完全就是一样的做法好么

不会用stl的蒟蒻手写了个堆冷静了下

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,f[1000000],ans,k,d;
struct lsg{int x,y;}a[1000000];
void putit(int x){//在堆中插入
    f[++d]=x;int kk=d;while (kk!=1&&f[kk/2]<f[kk])
        swap(f[kk],f[kk/2]),kk/=2;
}void outit(){//在堆顶删除
    f[1]=f[d--];int x=0,y=1;while (x!=y){
        x=y;if (x*2<=d&&f[x*2]>f[y])y=x*2;
        if (x*2+1<=d&&f[x*2+1]>f[y])y=x*2+1;swap(f[y],f[x]);
    }
}bool pd(lsg x,lsg y){return x.x>y.x;}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;for (int i=1;i<=n;i++)cin>>a[i].y>>a[i].x;
    sort(a+1,a+1+n,pd);k=1;for (int i=10000;i>=1;i--){//将时间逆序枚举
        while (a[k].x==i&&k<=n)putit(a[k].y),k++;
        if (d)ans+=f[1],outit();//就那样吧，能取就贪心取最大的
    } cout<<ans<<endl;
}
```

---

