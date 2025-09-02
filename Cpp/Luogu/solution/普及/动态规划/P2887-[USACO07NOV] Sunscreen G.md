# [USACO07NOV] Sunscreen G

## 题目描述

To avoid unsightly burns while tanning, each of the C (1 ≤ C ≤ 2500) cows must cover her hide with sunscreen when they're at the beach. Cow i has a minimum and maximum SPF rating (1 ≤ minSPFi ≤ 1,000; minSPFi ≤ maxSPFi ≤ 1,000) that will work. If the SPF rating is too low, the cow suffers sunburn; if the SPF rating is too high, the cow doesn't tan at all........

The cows have a picnic basket with L (1 ≤ L ≤ 2500) bottles of sunscreen lotion, each bottle i with an SPF rating SPFi (1 ≤ SPFi ≤ 1,000). Lotion bottle i can cover coveri cows with lotion. A cow may lotion from only one bottle.

What is the maximum number of cows that can protect themselves while tanning given the available lotions?

有C个奶牛去晒太阳 (1 <=C <= 2500)，每个奶牛各自能够忍受的阳光强度有一个最小值和一个最大值，太大就晒伤了，太小奶牛没感觉。

而刚开始的阳光的强度非常大，奶牛都承受不住，然后奶牛就得涂抹防晒霜，防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。

那么为了不让奶牛烫伤，又不会没有效果。

给出了L种防晒霜。每种的数量和固定的阳光强度也给出来了

每个奶牛只能抹一瓶防晒霜，最后问能够享受晒太阳的奶牛有几个。


## 样例 #1

### 输入

```
3 2
3 10
2 5
1 5
6 2
4 1```

### 输出

```
2```

# 题解

## 作者：翼德天尊 (赞：167)

#### 闲话不多说，不太懂这道题的同志们跟我来！跟着我逐步思考，让你秒懂此题！~~这题很水的~~

------------

### STEP 1 审题

经过整理，汇总改编抽象出一下条件：

1.有c条线段，已知它们的端点；

2.有l种点，已知它们的坐标以及每种点的个数；

3.问如果把那些点放入线段中，最多可以放进几个。

**看吧，活脱脱的一个贪心中的线段覆盖问题！**


------------
### STEP 2 规划做题方法

经过审（biao) 题 (qian)，我们了解了这是一道线段覆盖问题，那么，线段覆盖问题怎么做？

**方法：** 按右端点排序。

**理由：** 方便处理防晒霜摸到奶牛身上

但是，为什么不按左端点排序呢

**证明：** 现有三条线段，给出它们的左右端点（按左端点排序后）：

1  6 / / 2  3 / / 3  4

防晒霜两种（只给点的坐标，默认每种一瓶）（按大小排序后）：

3 / / 5

那么按正常的流程，“3”防晒霜给“1 6”线段，则5无法给另外两条线段，ans答案为1.

但如果按右端点排序，则结果为：

2  3 / / 3  4 / / 1  6

那么“3”防晒霜会给“2 3”线段使用，5会给“1 6”，从而有两个结果。

**这个反例证明：右端点才能真正确定一条线段的位置**

线段（奶牛）按右端点排序后，再从小到大将每个点（防晒霜）排序即可。

### STEP 3: AC CODE 及 具体讲解
30行是不是很短（没有压行哦）
```
#include<bits/stdc++.h>//美丽可爱端庄大方的万能头
using namespace std;
int c,l,ans;//分别记录奶牛数量，防晒霜数量以及结果
struct node{//结构体储存方便排序
	int a,b;//两个数据
};
node cow[2501],fss[2501];//分别储存奶牛信息和防晒霜信息
int cmp(node x,node y){//排序1：给奶牛按右端点排序
	return x.b<y.b;
}
int cmp1(node x,node y){//排序2：给防晒霜按左端点排序
	return x.a<y.a;
}
int main(){
	scanf("%d%d",&c,&l);
	for (int i=1;i<=c;i++) scanf("%d%d",&cow[i].a,&cow[i].b);
	for (int i=1;i<=l;i++) scanf("%d%d",&fss[i].a,&fss[i].b);//正常输入输出
	sort(cow+1,cow+c+1,cmp);//奶牛排序
	sort(fss+1,fss+l+1,cmp1);//防晒霜排序
	for (int i=1;i<=c;i++){
		for (int j=1;j<=l;j++){//循环判断
			if (fss[j].b>0&&fss[j].a>=cow[i].a&&fss[j].a<=cow[i].b){//判断是否符合点在线段内且该点还有剩余
				fss[j].b--,ans++;//减去一个相应点，答案+1
				break;//找到合适点选，就换另一个线段
			}
		}
	}
	printf("%d\n",ans);//正常输出
	return 0;//据说有好习惯会被人点赞哦，不知道是不是真的
} 
```
### STEP 4 完结撒花

恭祝各位RP++，有还是不懂的就在评论区留言吧，我会回复的。懂了的大佬们，你看蒟蒻这么辛苦的敲字，**点个赞**鼓励一下吧！



---

## 作者：fanfan (赞：18)

区间覆盖问题，求线段最多覆盖多少点，线段按右端点排序，防晒霜按防护值排序

之后进行贪心即可，注意防晒霜的数量

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int ans;
struct cow{
    int l;
    int r;
} 
ox[5000];
struct sunscreen{
    int n;
    int s;
} 
bb[5000];
bool com(struct cow x,struct cow y)
{
    {
        if(x.r<y.r) return true;
        return false;
        }
}
bool comp(struct sunscreen a,struct sunscreen b)
{
    if(a.n<b.n)
    return true;
    return false;
}
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    scanf("%d %d",&ox[i].l,&ox[i].r);
    for(int i=1;i<=m;i++)
    scanf("%d %d",&bb[i].n,&bb[i].s);
    sort(ox+1,ox+1+n,com);
    sort(bb+1,bb+m+1,comp);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        if(bb[j].n>=ox[i].l&&bb[j].n<=ox[i].r&&bb[j].s)
        {
            bb[j].s--;ans++;
            break;
        }
    }
    printf("%d",ans);
}
```

---

## 作者：陷语 (赞：16)

## 防晒霜

看了一下题解，发现没有人证明这个贪心为什么是正确的，想了想，觉得证明也是挺重要的，就把自己的证明过程发了上来。


------------


### 贪心思路：
按每头奶牛对最小阳光需求度的大小从大到小排序一遍，然后每次在防晒霜选择固定阳光度最大的防晒霜，时间复杂度为**O(C * L)即O(N^2)**

### 证明：

我们将奶牛按最小阳光需求度从大到小排序，也就是说当前奶牛的最小阳光需求度比后面奶牛都大，换句话说就是如果现固定阳光度最大的防晒霜无法满足这头奶牛，那后面的奶牛就更无法满足了。但如果我们选择固定防晒度最大的且能用的防晒霜，那对于后面奶牛的可选择范围就会增大。

**~~考虑到我不太会说人话~~，那我就换一种角度讲：**

设任意两瓶防晒霜为a1, a2，对于固定防晒度大小的关系为，a1 < a2，那对于后面的奶牛来说就有这三种情况：

1.a1和a2均可使用

2.a2能用a1不可用

3.两者均不可用。

很显然，我们先选择固定防晒度较大的a2对问题的整体影响更大。

**附上我的代码：**
```cpp
//今天真的好累…… 
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 3000;

int c, l, ans;

struct cow {
	int a, b;
} a[N];

struct spf {
	int a, b;
} b[N];

inline bool cmp(cow x, cow y) {return x.a > y.a;}
inline bool cmp_s(spf x, spf y) {return x.a > y.a;}

int main() {
//	freopen("in.txt", "r", stdin);
	
	scanf("%d %d", &c, &l);
	for(int i = 1; i <= c; ++i) scanf("%d %d", &a[i].a, &a[i].b);
	for(int i = 1; i <= l; ++i) scanf("%d %d", &b[i].a, &b[i].b);
	
	sort(a + 1, a + 1 + c, cmp);//按minspf递减的顺序排序 
	sort(b + 1, b + 1 + l, cmp_s);//按固定防晒度从大到小排序 
	
	for(int i = 1; i <= c; ++i)
		for(int j = 1; j <= l; ++j) {
			if(b[j].a >= a[i].a && b[j].a <= a[i].b && b[j].b) {
				ans++;
				b[j].b--;
				break;//找到了就直接找下一头奶牛可用的防晒霜 
			}
		}
		
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：14)











这题我选择使用网络流。做题之前没看题解感觉很像网络流，就试着做了一下，主要是内存原因限制了这题的解法。
1.通过原点向防晒霜建边，边权为cover
2.防晒霜向适合的奶牛建边，复杂度为n²，边权为1
3.奶牛向汇点建边，边权为1,
跑一遍dinic就可以了，实现的时候可以通过开小数组来ac（128mb作者按照建边的规模开貌似会mle）

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=5005;
int spf[maxn],cover[maxn],C,L,c[maxn],l[maxn],r[maxn];
inline void init(){
	scanf("%d%d",&C,&L);
	for (int i=1;i<=C;i++){
		scanf("%d%d",&l[i],&r[i]);
	}
	for (int i=1;i<=L;i++){
		scanf("%d%d",&spf[i],&cover[i]);
	}
}
const int maxm=2000000;
struct edge{
	int link,next,val,opp;
}e[maxm];
int tot,S,T,head[maxn];
inline int get(int x){
	return x+L;
}
inline void add(int u,int v,int w){
	e[++tot]=(edge){v,head[u],w,0}; head[u]=tot;
}
inline void insert(int u,int v,int w){
	add(u,v,w); e[tot].opp=tot+1; add(v,u,0); e[tot].opp=tot-1;
}
inline void build(){
	S=0;
	for (int i=1;i<=L;i++){
		for (int j=1;j<=C;j++){
			if (spf[i]>=l[j]&&spf[i]<=r[j]){
				insert(i,get(j),1);
			}
		}
		insert(S,i,cover[i]);
	}
	T=C+L+1;
	for (int i=1;i<=C;i++){
		insert(get(i),T,1);
	}
}
int h,t,q[maxn],dis[maxn];
inline bool bfs(){
	memset(dis,-1,sizeof(dis));
	h=0; t=1; dis[S]=0; q[1]=S;
	while (h<t){
		int u=q[++h];
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link;
			if (dis[v]==-1&&e[i].val){
				dis[v]=dis[u]+1;
				q[++t]=v;
				if (v==T) return 1;
			}
		}
	}
	return 0;
}
const int inf=1e9;
int cur[maxn],ans;
inline void clean(){
	memcpy(cur,head,sizeof(cur));
}
inline void backflow(int i,int w){
	e[i].val-=w; 
	e[e[i].opp].val+=w;
}
int dinic(int u,int flow){
	if (!flow||u==T) return flow;
	int used=0;
	for (int i=cur[u];i;i=e[i].next){
		int w,v=e[i].link;
		if (dis[u]+1==dis[v]&&e[i].val){
			w=dinic(v,min(flow-used,e[i].val));
			used+=w;
			backflow(i,w);
			if (w) cur[u]=i;
			if (used==flow) return flow;
		}
	}
	if (!used) dis[u]=-1;
	return used;
}
inline void solve(){
	build();
	while (bfs()){
		clean();
		ans+=dinic(S,inf);
	}
	printf("%d\n",ans);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：追梦_Chen (赞：8)

#### 这是一道比较明显的贪心题，首先我们要先明白：固定太阳强度越大的防晒霜（即防晒霜的值越大），其可以作用的牛就越少（因为牛都有一个最大承受阳光的强度）。所以，固定太阳强度越小的防晒霜能适用的牛就越多。因此，我们要尽可能的先把固定太阳强度越大的防晒霜用掉去，这样就能保证更多的牛能够享受阳光。嗯！保护动物，人人有责！明白这一点后，我们就可以用贪心码代码啦~~~
```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;
int n,l,sum;
struct node{
	int minn;
	int maxn;
}cow[3000];
struct node1{
	int spf;
	int total;
}sun[3000];
bool cmp(node a,node b){
	return a.minn>b.minn;    //能承受阳光更强的牛也先用掉 
}
bool cmp1(node1 a, node1 b){
	return a.spf>b.spf;  //先把固定太阳强度大的先用掉 
}
int main(){
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++)	scanf("%d %d",&cow[i].minn,&cow[i].maxn);
	sort(cow+1,cow+n+1,cmp);
	for(int i=1;i<=l;i++)	scanf("%d %d",&sun[i].spf,&sun[i].total);
	sort(sun+1,sun+l+1,cmp1);
	for(int i=1;i<=l;i++){       			 //表示防晒霜的种类 
		for(int j=1;j<=sun[i].total;i++){   //表示第i种防晒霜第j瓶 
			int ans=0;   				   //表示第i种防晒霜的使用次数 
			for(int k=1;k<=n;k++){        //表示第几头牛 
				if(sun[i].spf>=cow[k].minn&&sun[i].spf<=cow[k].maxn){
					sum++;
					cow[k].minn=1<<30;
					cow[k].maxn=1<<30; //说明该头牛已经涂了防晒霜，以后就不能用这头牛了，给一个很大的值让他永远不能参加判断 
					ans++;
					if(ans==sun[i].total){   
									 //若使用次数达到了瓶数，给k一个很大的值，跳出该层循环 
						k=200000;
					}		
				}
			}	
		} 
	}
	printf("%d",sum);
	return 0;
}

```


---

## 作者：gudingning666 (赞：6)

这道题，对于我们这种只有普及水平的人，当然先用贪心啦。
来看看题目：有minSPFi 和maxSPFi，然后还有SPFi 和 coveri。
我这里给出一个贪心：按照minSPFi从大到小排序，先满足minSPFi的奶牛（用SPFi最大的能满足的）。贪心的过程是假设，但是要证明太难了。我来解释一下：假设第I头牛用上述规律用第J瓶防晒霜，假设这瓶防晒霜给下面一头牛用，有可能都用不了，假设能用，按照这个规律还不如给第I头牛。
代码如下：
```CPP
#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdio>
using namespace std;
    int n,m,i,tot,t,j;
    struct lol{
    	int x,y;
    };
    lol a[100000],b[100000];
    bool cmp(lol i,lol j){
    	return i.x>j.x;
    }//关键词快排，两个都是一样的
int main(){
    cin>>n>>m;
    for(i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
    for(i=1;i<=m;i++) cin>>b[i].x>>b[i].y;
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+m+1,cmp);//快排
    for(i=1;i<=n;i++)
      for(j=1;j<=m;j++)
        if (b[j].y>0&&a[i].x<=b[j].x&&a[i].y>=b[j].x){//这个判断是判断这瓶防晒霜能用且能使牛晒阳光
        	tot++;
        	b[j].y--;
        	break;//找到了就退出
        }
    cout<<tot<<endl;
    return 0;
}
```

---

## 作者：Kacho (赞：4)

本蒟蒻的第一篇题解

其实我看到这道题的难度的时候是挺害怕的。

但是当我利用百度翻译翻译出一些~~人看不懂鬼也看不懂的东西~~题意之后，我似乎明白了这道题要怎么做。


这道题目我会使用2个结构体第一个是名为 $cow$ 的结构体，用于存储每一头牛的 $max$ 和 $min$ 。第二个是名为 $fss$ 的结构体用于存储每一个防晒霜的固定光度和数量。


首先我们知道有 $C$ 头牛，并且每一头牛都有一个
$max$ $min$ 的光照强度的忍受值，而根据题意我们可以知道每一头奶牛都不能忍受一开始的太阳光照射所以才会需要防晒霜，那让我们来观察一防晒的工作原理。


我们需要输入的是防晒霜的固定太阳光照值和数量。


**当一个防晒霜所固定的太阳照射的阳光强度，在每一头 $cow$ 可以忍受的最大值和最小值之间时，我们将这个防晒霜的数量减一，将保全的牛的数量增多。**
```cpp
for(int i=1;i<=n;i++){//枚举每一头牛
		for(int j=1;j<=l;j++){//枚举每一管防晒霜
			if(f[j].SPF>=c[i].minn && f[j].SPF<=c[i].maxx && f[j].num!=0){//这里的意思就是当固定的光照强度在最大值和最小值之间并且防晒霜的数量大于0，我们就把牛的数量增加且退出循环，枚举下一头牛。
				f[j].num--;//防晒霜数量减一。
				ans++;//答案加一。
				break;//枚举下一头牛。
			}
		}
	}
```

什么时候我们才能得到最优的结果呢？所以这里我们就要用到贪心思想了。**至于贪心的思想，我们应该用最大值进行排序并且让防晒霜的 $SPF$ 的值小的在前，这样子才能够得到最优解。**

**因为要先把 $max$ 的值小的牛先用掉，并且让 $SPF$ 小的防晒霜尽量用于 $max$ 小的牛身上这样子就能够得到最优解了。**

至于排序这一块我们可以用自带的 $stl$ 函数 $sort$ 所以排序的代码如下:


```cpp
bool cmpc(cow x,cow y){
	return x.maxx<y.maxx;
}

bool cmpf(fss x,fss y){
	return x.SPF<y.SPF;
}
```

好的，重点都结束了，现在输出 $ans$ 就可以 $AC$ 此题啦！

下面附赠 $AC$ 代码:

```cpp
#include<bits/stdc++.h>//朴实无华的万能头。
using namespace std;

int n,l,ans;//n代表题中的C，l即L，ans即答案。

struct cow{
	int maxx,minn;
}c[2505];

struct fss{
	int SPF;
	int num;
}f[2505];

bool cmpc(cow x,cow y){
	return x.maxx<y.maxx;
}

bool cmpf(fss x,fss y){
	return x.SPF<y.SPF;
}


int main (){
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++) cin>>c[i].minn>>c[i].maxx;
	for(int i=1;i<=l;i++) cin>>f[i].SPF>>f[i].num;
	sort(c+1,c+1+n,cmpc);
	sort(f+1,f+1+l,cmpf);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=l;j++){
			if(f[j].SPF>=c[i].minn && f[j].SPF<=c[i].maxx && f[j].num!=0){
				f[j].num--;
				ans++;
				break;
			}
		}
	}//上面都是在前面分析过的内容，于是又是一道水题的诞生。
	cout<<ans<<endl;
	
	return 0;
}
```

---

## 作者：一只萌新 (赞：4)

[$\color {teal}{Blog}$](https://blog.csdn.net/qq_43653202/article/details/100061215)

区间问题 

**常见题型：线段覆盖等**

**常用策略：贪心**

遇到这样的题时，考虑三种情况 

1. **相交（策略相关）** 结合题目分析 

```cpp
------
    -------  
```
2. **相离（常不考虑）** 

```cpp
----   ----
```
3. **包含（顺序相关）** 考虑先处理哪个  

```cpp
    ---   
----------
```

例题
[P2887 【USACO07NOV】防晒霜Sunscreen](https://www.luogu.org/problem/P2887)

$Solution$

把每只奶牛可忍受的光照强度看作区间（或线段）

对于这道题,排序函数可分**按左端点排序,按右端点排序两种情况** 

以按右端点排为例 

**1.相交**
```cpp
----      1
  -----   2
```
此时若先处理1，则选防晒霜时应从小到大选；反之从大到小，按个人习惯选择 

**2.包含** 
```cpp
    ---  1
-------  2
```
选择多的2显然应该放下面 

$so$ 排序函数为  
```cpp
il bool cmp(node x,node y){	
	return (x.r==y.r&&x.l<y.l)||(x.r<y.r);
}
```

$Code$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define re register
#define il inline
#define ll long long
using namespace std;

inline int read(){
    int s=0,f=0;char c=getchar();
    while(c<'0'||c>'9') f=(c=='-'),c=getchar();
    while(c>='0'&&c<='9') s=(s<<3)+(s<<1)+(c^'0'),c=getchar();
    return f?-s:s;
}

const int N=2505,M=1005;
int n,m,b[M],ans,now;
struct node{
	int l,r;
}a[N];
/*
排序顺序 
il bool cmp(node x,node y){		//左端点排序 
	return (x.l==y.l&&x.r<y.r)||(x.l>y.l);
}*/
il bool cmp(node x,node y){		//右端点排序(要分清左右端点!) 
	return (x.r==y.r&&x.l<y.l)||(x.r<y.r);
}

int main(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i) a[i].l=read(),a[i].r=read();
	for(re int i=1,x,y;i<=m;++i) x=read(),y=read(),b[x]+=y; //+= 可能重复  
	sort(a+1,a+n+1,cmp);
    for(re int i=1;i<=n;++i)
    /*	for(re int j=a[i].r;j>=a[i].l;--j) */
    	for(re int j=a[i].l;j<=a[i].r;++j)
			if(b[j]){ans++,b[j]--;break;}
	printf("%d\n",ans);
	return 0;
}
```

很少的一点个人理解 

没有对贪心的证明，只想说一说排序的顺序

~~有点水~~

---

## 作者：姬小路秋子 (赞：3)

我一开始想到的是优先队列（即“从最小的防晒霜枚举，将所有符合  最小值小于等于该防晒霜的 奶牛的 最大值 放入优先队列之中。”）。

但那么晚了，我感觉写写挺麻烦的，就写了个贪心。。

显然按右端点排序，然后贪心选择满足该只奶牛范围的最小防晒霜值。正确性显然。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct aaa{
	int l,r;
}a[100001],b[100001];
int n,m,i,j,ans;
bool cmp(aaa a,aaa b){
	return a.r<b.r||a.r==b.r&&a.l<b.l;
}
bool Cmp(aaa a,aaa b){
	return a.l<b.l;
}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d%d",&a[i].l,&a[i].r);
	for(i=1;i<=m;i++)scanf("%d%d",&b[i].l,&b[i].r);
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+m+1,Cmp);
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++)
		 if(b[j].r&&b[j].l<=a[i].r&&b[j].l>=a[i].l){
		 	b[j].r--;
		 	ans++;
		 	break;
		 }
	}
	printf("%d",ans);
}
```

---

## 作者：_wkjzyc (赞：3)

**分析**   每只奶牛的可接受范围是一个闭区间

按照每只奶牛minSPF**逐渐递减排序**，然后给他用范围内**SPF值最大**的防晒霜。
即 **贪心两次**。
对于在范围内的几种防晒霜，它们的SPF值：

一、要么可以满足这一个，不能满足下一个；
二、要么可以满足这一个，也能满足下一个。

所以选最大的，能够尽量**多**选到一的情况。
这样就可以尽量少使用  **能满足下一只奶牛的防晒霜**。

标程：
```cpp
#include<iostream>
using namespace std;


int c,l,spf[2501][2],ss[2501][2],ans=0,k1,k2;
//c->C  l->L spf[i][0]->minSPFi spf[i][1]->maxSPFi  ans答案
//k1 k2临时变量  ss[i][0]->SPFi   ss[i][1]->coveri 


void qsort(int l,int r)//简单的快排 
{
    int i=l,j=r,k;
    int mid=spf[(l+r)/2][0];
    do
    {
        while(spf[i][0]>mid)i++;
        while(spf[j][0]<mid)j--;
        if(i<=j)
        {
            k=spf[i][0];spf[i][0]=spf[j][0];spf[j][0]=k;
            k=spf[i][1];spf[i][1]=spf[j][1];spf[j][1]=k;
            i++;j--;
        }
    }
    while(i<=j);
    if(l<j)qsort(l,j);
    if(i<r)qsort(i,r);
}
//ctrl+c   ctrl+v
//手打？不存在的


int main()
{
    cin>>c>>l;
    for(int i=1;i<=c;++i)
    {
        cin>>spf[i][0]>>spf[i][1];
    }
    for(int i=1;i<=l;++i)
    {
        cin>>ss[i][0]>>ss[i][1];
    }//输入…
     
    qsort(1,c);//懒人法 
    
    for(int i=1;i<=c;++i)
    {
        
        k1=0;//存值 
        k2=0;//存址 
        for(int j=1;j<=l;j++)
        {
            if(ss[j][1]>0&&ss[j][0]>=spf[i][0]&&ss[j][0]<=spf[i][1]&&ss[j][0]>=k1)
            {
                k1=ss[j][0];
                k2=j;
            }//求SPF最大 
        }
        
        if(k2!=0)
        {
            ans++;//多一只能晒太阳的奶牛 
            ss[k2][1]--;//用掉一个ss 
        }
        
    }
    
    cout<<ans;
    return 0;
}
```

---

## 作者：flifli (赞：3)

    
    
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAX 2600
int sc[MAX][5],cowmi[MAX][3];
void qs(int left,int right);
void qss(int l,int r);
int main()
{
    int tc,ts,i,j,cnt=0;
    scanf("%d%d",&tc,&ts);
    for(i=1;i<=tc;++i)
    scanf("%d%d",&cowmi[i][1],&cowmi[i][2]);
    qs(1,tc);//对牛的最小防晒值进行排序。注意维护最大防晒值和最小防晒值 
//    for(i=1;i<=tc;++i)
//    printf("<min=%d max=%d >\n",cowmi[i][1],cowmi[i][2]);
    for(i=1;i<=ts;++i)
    scanf("%d%d",&sc[i][1],&sc[i][2]);//注意：第一个是spf，第二个是瓶数。如果反了可以过一个点 
    qss(1,ts);//对防晒霜的spf值进行排序，注意维护瓶数
    for(i=tc;i>=1;--i)//贪心，如果正序得38分 
    {
        for(j=ts;j>=1;--j)
        {
            if(cowmi[i][1]<=sc[j][1]&&cowmi[i][2]>=sc[j][1]&&sc[j][2]>0)
            {
                sc[j][2]--;          
                cnt++;
                //printf("<cma=%d,cmi=%d,spf=%d,ps=%d>\n",cowmi[i][2],cowmi[i][1],sc[j][1],sc[j][2]);
                break;
            } 
        }
    }
    printf("%d",cnt);
    return 0;
}
void qs(int left,int right)
{
    int i,j,base,t,temp;
    i=left; 
    j=right;
    base=cowmi[(i+j)/2][1];
    while (i<=j)
    {
        while (cowmi[i][1]<base) i++;
        while (cowmi[j][1]>base) j--;
        if (i<=j)
        {
            t=cowmi[i][1];
            temp=cowmi[i][2];
            cowmi[i][2]=cowmi[j][2]; 
            cowmi[i][1]=cowmi[j][1];
            cowmi[j][1]=t;
            cowmi[j][2]=temp;//维护 
            i++;
            j--;
        }
    }
    if(left<j) qs(left,j);
    if(i<right) qs(i,right);
}
void qss(int l,int r)
{
    int i,j,base,t,temp;
    i=l; 
    j=r;
    base=sc[(i+j)/2][1];
    while (i<=j)
    {
        while (sc[i][1]<base) i++;
        while (sc[j][1]>base) j--;
        if (i<=j)
        {
            t=sc[i][1];
            temp=sc[i][2]; 
            sc[i][1]=sc[j][1];
            sc[i][2]=sc[j][2];
            sc[j][1]=t;
            sc[j][2]=temp;//维护 
            i++;
            j--;
        }
    }
    if (l<j) qss(l,j);
    if (i<r) qss(i,r);
}
```

---

## 作者：Werner_Yin (赞：2)

# 前言
题解区众多大佬的解法令本蒟蒻佩服，但本人过于蒟蒻，开始时把贪心写错，因此我主要讲讲我的错误的贪心是错在哪的（附图例）

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/13280348.html)
# 思路
## 声明
```
minSPFi : 奶牛忍受的阳光强度最小值
maxSPFi : 奶牛忍受的阳光强度最大值
coveri : 防晒霜数量
SPFi ： 防晒霜阳光强度
```
## 初始的思路(38 pts)
这是一道贪心题,但我开始时还是想错了。

我先将每头牛按照最小忍受阳光强度从小到大排序，防晒霜按照强度从小到大排序。

然后开始枚举，对于第 $i$ 个奶牛 ，假设当前枚举到第 $l$ 个 防晒霜 , 当其 $SPFi < minSPFi$ , $l++$ ,直到满足 $SPFi \ge minSPFi$ ，而当 $SPFi > maxSPFi$ , 则 ```continue``` ,最后判断一下防晒霜剩余个数即可判断答案
## 初始代码（38 pts)
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2510;
int C,L,ans,l = 0;

struct cow{//奶牛
	int l,r;
	bool operator < (const cow &b) const{
		if(l == b.l) return r < b.r;
		return l < b.l;
	}
}a[MAXN];

struct sunscreen{//防晒霜
	int SP,num;
	bool operator < (const sunscreen &b) const{
		return SP < b.SP;
	}
}lotion[MAXN];

int main (){
	scanf("%d %d",&C,&L);
	for(int i = 0 ;i < C;i++) scanf("%d %d",&a[i].l,&a[i].r);
	for(int i = 0 ;i < L;i++) scanf("%d %d",&lotion[i].SP,&lotion[i].num);
	sort( a , a+C );
	sort( lotion , lotion+L);
	for(int i = 0 ;i < C;i++){
		if(lotion[l].num == 0) l++; //判断个数
		while ( a[i].l > lotion[l].SP && l < L-1) l++;//查找左端点是否符合条件
		if( a[i].r < lotion[l].SP) continue;//右端点不符合直接跳过
		lotion[l].num--;
		ans++;//答案处理
	}
	printf("%d",ans);
	return 0;
}
```
## 正解思路
然鹅，这种贪心错了。

举个例子：
![](https://cdn.luogu.com.cn/upload/image_hosting/hreks9kl.png)
按照这种算法，我们会让 1 区间使用 I ，2区间使用 J，3 区间使用 K ，答案为 3。
但是答案为4。

正确解法应该为：

先将每头牛按照最小忍受阳光强度从大到小排序，然后开始枚举，对于第 $i$ 个奶牛 ，我们要找到它能用的防晒霜里面```SPFi```最大的，然后计算答案。

### 关于正确性
```SPFi```更小的显然其他没枚举到的牛很可能会被用到，于是我们拿掉```SPFi```最大的，具体可以见上面的图。
# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2510;
int C,L,ans;

struct cow{
	int l,r;
	bool operator < (const cow &b) const{
		return l > b.l;
	}
}a[MAXN];

struct sunscreen{
	int SP,num;
}lotion[MAXN];

int main (){
	scanf("%d %d",&C,&L);
	for(int i = 0 ;i < C;i++) scanf("%d %d",&a[i].l,&a[i].r);
	for(int i = 0 ;i < L;i++) scanf("%d %d",&lotion[i].SP,&lotion[i].num);
	sort( a , a+C );
	for(int i = 0 ;i < C;i++){
		int l = -1,choose = -1;
		for(int j = 0;j < L;j++)//暴力枚举
			if ( lotion[j].num > 0 && lotion[j].SP >= a[i].l && lotion[j].SP <= a[i].r)
				if(lotion[j].SP > choose){
					choose = lotion[j].SP;
					l = j;
				}
		if( l != -1 ){
			ans++;
			lotion[l].num--;
		}//答案处理
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：shuiyuhan (赞：2)

关于这题，我一开始~~人工智障~~了，一不小心把i和j弄反了，害得我调了20min

所以才写了这篇题解

这是一道贪心的题，我们把奶牛能承受的最大阳光从大到小排序，再把防晒霜从大到小排序，之后用把每瓶防晒霜从1到n在每头牛上试一遍，求出最大值，累加sum即可

看这题没有p的，所以来水一发p的题解

```pascal
var
  n,i,j,k,m,ans,t:longint;
  a,b,c,d,e:array[0..1000005] of longint;
  f,g:array[0..1000005] of boolean;
  procedure sort(l,r: longint);
  //对每瓶防晒霜排序
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=e[(l+r) div 2];
         repeat
           while e[i]>x do
            inc(i);
           while x>e[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=e[i];
                e[i]:=e[j];
                e[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
    procedure sort1(l,r: longint);
    //别忘了多关键字排序交换要同时交换好多个
      var
         i,j,x,y,xx: longint;
      begin
         i:=l;
         j:=r;
         x:=c[(l+r) div 2];
         xx:=d[(l+r) div 2];
         repeat
           while (c[i]>x)or(x=c[i])and(d[i]>xx) do
            inc(i);
           while (x>c[j])or(x=c[j])and(xx>d[j]) do
            dec(j);
           if not(i>j) then
             begin
                y:=c[i];
                c[i]:=c[j];
                c[j]:=y;
                y:=d[i];
                d[i]:=d[j];
                d[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort1(l,j);
         if i<r then
           sort1(i,r);
      end;
begin
  readln(m,n);
  t:=0;
  for i:=1 to m do readln(c[i],d[i]);
  for i:=1 to n do
  begin
    readln(a[i],b[i]);
    for j:=1 to b[i] do
    begin
      inc(t);
      e[t]:=a[i];
    end;
  end;//这里与别的dalao不同，
  蒟蒻用e数组存下每瓶防晒霜质量，所以e数组要开大点(~~反正不会爆~~）
  
  n:=t;
  sort(1,n);//对防晒霜质量排序
  sort1(1,m);//对每只牛能承受的阳光值排序
  for i:=1 to n do 
  begin 
    f[i]:=true; 
    g[i]:=true; 
   end;//初始化，f表示第i瓶防晒霜是否被用掉，
  g表示第i头牛是否涂过防晒霜
  ans:=0;
  for i:=1 to n do
  begin
    if not f[i] then continue;
    for j:=1 to m do
    begin
      if (e[i]<=d[j])and(e[i]>=c[j])and(f[i])and(g[j]) then
      //这边我一开始把代码写成了 
      //if (e[i]<=d[i])and(e[i]>=c[i])and(f[i])and(g[j]) then
      //导致只过了一个点
      begin
        f[i]:=false;//标记第i瓶防晒霜被用掉了
        g[j]:=false;//标记第j头牛用了防晒霜
        inc(ans);
        break;
      end;//如果防晒霜质量在牛承受范围之内就用它
    end;
  end;
  writeln(ans);//输出答案
end.
```

---

## 作者：NuoCarter (赞：1)

## P2887 【[USACO07NOV]Sunscreen G】题解

考虑转化题目条件：

给定的奶牛的$min,max$

相当于给定了一条线段的 左端点 l 和右端点 r

而给的防晒霜就相当于给了若干个点

答案就是线段能覆盖的点的数量

## 贪心证明：

每一个点有两个值：$spa_i,many_i$

每条线段有一个 $l,r$

如果将所有点按照$spa_i$降序排列

将所有线段按照 $l$ 降序排列

对于所有的线段匹配到的一定是当前最差的一个点，因为只有这样才能保证覆盖到更多的点。

那么什么样的点才是最差的呢。。

一定是在线段范围中值最大的点，因为更小的点珂以匹配更多的线段。

所以排完序后一波模拟匹配即可。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int C,L,ans;
const int N=2505;
struct node{int l,r;}a[N];
struct sipa{int sp,ma;}spa[N];
inline bool cmp1(node x,node y){return x.l>y.l;}
inline bool cmp2(sipa x,sipa y){return x.sp>y.sp;}
int main(){
  scanf("%d%d",&C,&L);
  for(int i=1;i<=C;++i){scanf("%d%d",&a[i].l,&a[i].r);}
  for(int i=1;i<=L;++i){scanf("%d%d",&spa[i].sp,&spa[i].ma);}
  sort(a+1,a+C+1,cmp1);
  sort(spa+1,spa+L+1,cmp2);
  for(int i=1;i<=C;++i)
		for(int j=1;j<=L;++j) {
			if(spa[j].sp>=a[i].l&&spa[j].sp<=a[i].r&&spa[j].ma>0) {
				ans++;
				spa[j].ma--;
				break;
			}
		}

	printf("%d\n", ans);
  return 0;
}

```

---

## 作者：RoRoyyy (赞：1)


~~什么叫标题过长....我可能是滥用标题了~~


------------

加入了平衡树优化复杂度降为$O(nlogn)$。

### 贪心思路： 
这里按照左端点排序， 之后每次取小于等于当前右端点的第一个区间就行了。
这里证明可以参考匈牙利定理。


------------

本质是一个二分图匹配问题， 有若干的区间和若干的点，每个点选取所在区间之一， 求最大匹配。

这里可以如下证明：

### 首先一个定理：
	
    一个二分图匹配不存在增广路就可判定是最大匹配。
 ### 什么叫增广路：
 
 ~~我的理解：~~
 对于一个二分图的匹配， 如果从一个没有进入匹配的点出发， 先沿着非匹
 配边走， 走到一个进入匹配的点， 之后沿着匹配边继续走到一个点$s$再沿着
 非匹配边$s2$..若在这种循环中找到了存在一点$s$使得$s2$是非匹配点， 那么
 就存在增广路
 ### 怎么证明对于这个贪心策略不存在增广路？
  用$ci$ 代表 第 $i$ 头牛， $ si $ 代表第 $i$ 个防晒霜假如存在增广路径， 那么看最短的一条， 显然如果存在某一点$si$ ， 它一定会向着之前的牛找增广路， 而找到最上面的节点时没有与之匹配的点， 但是在贪心的过程中最上面的点一定是最先匹配， 所以假设不成立
 
 
 
####   代码：
```cpp
//RoRoyyy
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
const int N = 2505;
typedef pair<int, int> PII;
int c, l;
PII cows[N];
map<int, int> spfs;
int main() {
    cin >> c >> l;
    for(int i = 1; i <= c; i++) cin >> cows[i].first >>cows[i].second;
    sort(cows + 1, cows + 1 + c);
    for(int i = 1; i <= l; i++) {
        int spf, cover;
        cin >> spf >> cover; 
        spfs[spf] += cover;
    } 
    int res = 0; 
    for(int i = c; i >= 1; i--) {
        auto cow = cows[i];
        auto it = --spfs.upper_bound(cow.second);
        if(it -> first >= cow.first && it -> first <= cow.second) {
            res++;
            it -> second--;
            if(it -> second == 0) {
                spfs.erase(it); 
            }
        }
    }
    cout << res << endl;
    return 0;
}
```


---

## 作者：Lily_White (赞：1)



## 题意概述

To avoid unsightly burns while tanning, each of the $C (1 ≤ C≤ 2500)$ cows must cover her hide with sunscreen when they're at the beach. Cow *i* has a minimum and maximum $SPF$ rating $(1 ≤ minSPF_i ≤ 1,000; minSPF_i ≤ maxSPF_i ≤ 1,000) $that will work. If the $SPF$ rating is too low, the cow suffers sunburn; if the *SPF* rating is too high, the cow doesn't tan at all........

The cows have a picnic basket with $L(1 ≤ L ≤ 2500)$ bottles of sunscreen lotion, each bottle $i$ with an *SPF* rating $SPF_i$ $(1 ≤ SPF_i ≤ 1,000)$. Lotion bottle $i$ can cover $cover_i$ cows with lotion. A cow may lotion from only one bottle.

What is the maximum number of cows that can protect themselves while tanning given the available lotions?

## 贪心思路

 将所有牛按照$minSPF$递减的顺序排序，理由如下。

首先我们需要明确一点：**就算让一头牛放弃日光浴，让另一头牛来，答案也不会变得更优。**这个结论的正确性是显然的，因为我们只关心牛的数量。因此，我们一定要尽量满足当前的牛。

假设我们现在正在处理一头需求为$[x,y]$的牛，我们有两瓶符合要求的，SPF分别为$m,n$，其中$x\leq m \leq n \leq y$，那么我们选择哪一瓶更好呢？

显然，如果我们选择$m$的那一瓶，那么有可能出现一头牛，它的需求恰好在$q,n(q\leq m)$之间，那么这时这头牛就无法使用$n$这一瓶。如果只有​$2$头牛，那么它就被浪费了，我们白白失去了一个解。

而现在我们排序后，这头牛用不了的，后面的不一定用不了，这头牛能用的，后面的有可能能用，也有可能不能用，如果是后者，我们此时就需要选择这一瓶，才不会浪费掉。

因此，对于一头牛，如果有多种选择，我们应当选择对后面影响最小的。也就是这头牛可能使用的最大$SPF$的防晒霜，才是最合算的。

综上，先排序$O(n\text{log}n)$,再扫一遍序列，每次选能用的$SPF$最大的，时间复杂度最坏是$O(n^2)$，但是实际上很难达到这个上界，可以通过测试。

## 伪代码

这里给出贪心策略的伪代码供参考

```
begin
	read n,m
	for i from 0 to n do
    	read cow[i].minspf, cow[i].maxspf
    for i from 0 to m do
        read lotion[i].spf,lotion[i].cover
    sort(cow,cow+n) '按照minspf递减的顺序
    for i from 0 to n do
    	for j from 0 to m do
    		if lotion[j].spf >= cow[i].minspf and lotion[j].spf <= cow[i].maxspf and
    			lotion[j].cover > 0 then
    			lotion[j].cover--
    			ans++
    			break
    		end if
    	next j
    next i
    print ans
end.
```



## 实际实现(C++11)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2560;
struct Cow
{
	int minSPF;
	int maxSPF;
}cows[MAXN];
struct SunScreen
{
	int SPF;
	int cover;
}lotion[MAXN];
int main()
{
	freopen("sunscreen.in","r",stdin);
	freopen("sunscreen.out","w",stdout);
	int c,l,ans=0;
	scanf("%d%d",&c,&l);
	for (int i=0;i<c;i++)scanf("%d%d",&cows[i].minSPF,&cows[i].maxSPF);
	for (int i=0;i<l;i++)scanf("%d%d",&lotion[i].SPF,&lotion[i].cover);	
	sort(cows,cows+c,[](const Cow a, const Cow b){return a.minSPF>b.minSPF;});
	sort(lotion,lotion+l,[](const SunScreen a,const SunScreen b){return a.SPF > b.SPF;});
	for (int i=0;i<c;i++)
		for (int j=0;j<l;j++)
			if (lotion[j].SPF <= cows[i].maxSPF && lotion[j].SPF >= cows[i].minSPF && lotion[j].cover )
			{
				lotion[j].cover--;
				ans++;
				break;
			}
	printf("%d\n",ans);
	return 0;
}
```





---

## 作者：maike8shi (赞：1)

# 优先队列题解

开一个“mins越大越优先”的优先队列，先将防晒霜的值从大到小排序，然后依次考虑：

1. 将maxs大于当前防晒霜值的牛放入优先队列
2. 将mins大于当前防晒霜值的牛弹出队列
3. 现在优先队列里剩下的牛都可以用这个防晒霜，那么有多少个防晒霜就pop多少次，并ans++

写代码的时候~~写着写着就~~想到一个桶排的思想，替代了对防晒霜的排序。另外也可以先将牛按maxs排序，“将maxs大于当前防晒霜值的牛放入优先队列”这一步就不需要枚举了。

因为每个牛都会入队、出队一次，所以时间复杂度为O（L+NlogN）

code：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

const int N=2505,L=2505;
const int INF=0x3f3f3f3f;

struct node{
	int mx,mn;
	friend bool operator < (node a,node b){
		return a.mn<b.mn;//重载运算符，mn大的优先级大
	}
};

int n,m,ans=0,maxl=0,minr=INF;
int res[L];
node a[N];
priority_queue<node> q;

void rd(int &x){
    x=0;
    char c=getchar();
    while (c<'0'||c>'9') c=getchar();
    while (c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar(); 
    } 
} 

void print(int x){
    if (x>9) print(x/10);
    putchar(x%10+'0');
}

bool cmp(node x,node y){
	return x.mx>y.mx;
}

int main(){
	rd(n),rd(m);
	memset(res,0,sizeof(res));//桶排思想，顺便还能记录个数
	for (int i=1;i<=n;i++){
		rd(a[i].mn),rd(a[i].mx);
		maxl=max(a[i].mx,maxl);
		minr=min(a[i].mn,minr);
	}
	for (int i=1;i<=m;i++){
		int cd,z;
		rd(cd),rd(z);
		res[cd]+=z;
	}
	sort(a+1,a+1+n,cmp);
	int p=1;
	for (int i=maxl;i>=minr;i--){
		while (a[p].mx==i){
			q.push(a[p]);//将maxs大于当前防晒霜值的牛放入优先队列
			p++;
		}
		while (!q.empty()&&q.top().mn>i) q.pop();//将mins大于当前防晒霜值的牛弹出队列
		while (res[i]&&!q.empty()){
			ans++;
			q.pop();
			res[i]--;//用防晒霜
		}
	}
	print(ans);
	return 0;
}
```

---

## 作者：yanghe__20050825 (赞：1)

其实这道题蛮简单的

~~我也不知道为什么是蓝题~~

其实就是把狗按上限排一下序，把防晒霜按能保持的最大排一下序

如果防晒霜的最小保持的温度是小于最小狗的上限但大于狗的下限

那么这个防晒霜的个数减一，再继续循环

见代码
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int ma;int mi;int sl;
}a[2501],b[2501];
inline bool cmp(const node &x,const node &y)
{
	return x.ma<y.ma;
}
inline bool cmmp(const node &x,const node &y)
{
	return x.mi<y.mi;
}
int main()
{
	//freopen("dog.in","r",stdin);
	//freopen("dog.out","w",stdout);
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].mi>>a[i].ma;//输入
	}
	for(int i=1;i<=m;i++)
		cin>>b[i].mi>>b[i].sl;
	sort(a+1,a+1+n,cmp);
	/*for(int i=1;i<=n;i++)
		cout<<a[i].ma<<" "<<a[i].mi<<endl;*/
	sort(b+1,b+1+m,cmmp);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i].mi<=b[j].mi&&a[i].ma>=b[j].mi&&b[j].sl!=0)//条件判断
			{
				b[j].sl--;//如果可以就减一
				ans++;
				break;
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：Logey (赞：0)

我先来简单地整理下题意。  
就给你若干线段和点，每个点可以与包含这个点的线段匹配，求最大匹配数。 
（题解里还有神仙貌似真的写了个网络流或者二分图匹配，算了不管了）  
一个很显然的贪心就是对于一个点，肯定是与覆盖这个点的线段中，右端点最靠左的匹配，那就拿堆维护一下就好了。  

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <climits>
#include <algorithm>
#include <queue>

const int MAXN = 1e4 + 7;

std::vector<int> v[MAXN];
int n, m, p[MAXN];

int main(int argc, char *argv[]) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        v[l].push_back(r);
    }
    for (int i = 1; i <= m; i++) {
        int pos, num;
        scanf("%d %d", &pos, &num);
        p[pos] += num;
    }
    std::priority_queue<int, std::vector<int>, std::greater<int> > q;
    int ans = 0;
    for (int i = 1; i <= 1000; i++) {
        while (!q.empty() && q.top() < i) q.pop();
        for (auto j : v[i]) {
            q.push(j);
        }
        while (!q.empty() && p[i]) q.pop(), ans++, p[i]--;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：chest_dick (赞：0)

# **首先呢这道题is a very easy 的贪心 and 排序 problem.**
## ~~然而有超级多的坑~~
1. 细读题目可以发现，“而刚开始的阳光的强度非常大，奶牛都承受不住，然后奶牛就得涂抹防晒霜，防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。”这句话和“给出了L种防晒霜。每种的数量和固定的阳光强度也给出来了” 仿佛是在告诉你：“他告诉了你那个太阳的初始强度”。然而······！！你**给我好好看看数据去！！，你觉得谁会是太阳的强度呢？？嗯？？其实没有太阳的强度
2. 你看看这句话“而刚开始的阳光的强度非常大，奶牛都承受不住，然后奶牛就得涂抹防晒霜，防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。”！！他难道不是在告诉你说：“每个**奶牛都要涂那该死的防晒霜吗？？”嗯？？确定有好好读题吗？？
3. 还有这句：“每种的数量和固定的阳光强度也给出来了。”难道不是说他穷，防晒霜数量有限吗？？
4. 再看看这个：“每个奶牛只能抹一瓶防晒霜，最后问能够享受晒太阳的奶牛有几个。”，你还能涂很多瓶吗？？
5. 还有一个隐藏的条件，他涂了防晒霜之后，他的最小值加了，他的最大值不加吗？？你还可以反向防晒啊？？
### ~~所以此题坑巨多，并不好做~~
#### 好了，当你成功在本帅（智）逼（障）的带领下避开了所有的坑之后，就该开始愉快的写代码了吧？？
看见这个最值问题就想着贪心吧，所以开结构体咯！！O(∩_∩)O~~

上菜！！
上代码！！
```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
struct cow
{
    ll minSPF,maxSPF;
}a[2505];
struct sunscreen
{
    ll SPF,num;
}b[2505];
ll l,c,ls[2505],ans;
bool cmpa(cow x, cow y)
{
    if(x.maxSPF == y.maxSPF)
        return x.minSPF < y.minSPF;
    return x.maxSPF < y.maxSPF;
}
bool cmpb(sunscreen x, sunscreen y)
{
    return x.SPF < y.SPF;
}
int main()
{
    scanf("%lld %lld", &c, &l);
    for (ll i=1 ; i<=c ; i++)
    {
        scanf("%lld %lld", &a[i].minSPF, &a[i].maxSPF);
    }
    for (ll i=1 ; i<=l ; i++)
    {
        scanf("%lld %lld", &b[i].SPF, &b[i].num);
    }
    sort(a+1 , a+c+1 , cmpa);
    sort(b+1 , b+l+1 , cmpb);
    for(ll i=1 ; i<=c ; i++)
    {
        for(int j=1 ; j<=l ; j++)
        {
            if(b[j].SPF <= a[i].maxSPF && b[j].SPF >= a[i].minSPF && b[j].num > 0)
            {
                b[j].num --;
                ans ++;
                break;
            }
        }
    }
    printf("%lld", ans);
}
```

---

## 作者：AndyMo (赞：0)

大部分题解都从牛的角度考虑，当然也可以考虑防晒霜给谁用。
把防晒霜按照spf值升序排序并依次考虑。

想要让当前防晒霜对之后的影响最小,就优先给能接受它的牛里面maxspf值最小的 。

把牛按minspf值升序排序。
枚举防晒霜的spf，把minspf<=防晒霜的spf的牛的maxspf值丢进小根堆里。
分配当前防晒霜的时候，先丢掉maxspf<spf的堆顶的牛(它们以后也没救了)，然后再弹出cover次。

调半天，还得标记牛有没有用过防晒霜，!q.empty()还得先判不然会re,菜死。
不懂看代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
namespace io{
    #define ll long long
    #define inf 0x3f3f3f3f
    #define il inline 
    #define in1(a) read(a)
    #define in2(a,b) in1(a),in1(b)
    #define in3(a,b,c) in2(a,b),in1(c)
    #define in4(a,b,c,d) in2(a,b),in2(c,d)
    il void readl(ll &x){
        x=0;ll f=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
        while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
        x*=f;
    }
    il void read(int &x){
        x=0;int f=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
        while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
        x*=f;
    }
}using namespace io;
#define N 2505
int c,l;
struct cow{
	int l,r,id;
	bool operator <(const cow &rhs) const{
		return r>rhs.r;
	}
}a[N];
bool cmp1(cow a,cow b){
	return a.l<b.l;
}
struct sunscreen_lotion{
	int spf,cover;
}s[N];
bool cmp2(sunscreen_lotion a,sunscreen_lotion b){
	return a.spf<b.spf;
}
priority_queue <cow> q;
bool vis[N];
int main(){
	int ans=0;
	in2(c,l);
	for(int i=1;i<=c;i++) in2(a[i].l,a[i].r),a[i].id=i;
	sort(a+1,a+c+1,cmp1);
	for(int i=1;i<=l;i++) in2(s[i].spf,s[i].cover);
	sort(s+1,s+l+1,cmp2);
	for(int i=1;i<=l;i++){
		for(int j=1;j<=c;j++){
			if(a[j].l<=s[i].spf&&!vis[a[j].id]) q.push(a[j]);
		}
		while(!q.empty()&&q.top().r<s[i].spf) q.pop();
		while(!q.empty()&&s[i].cover--){
			vis[q.top().id]=1;
			ans++;
			q.pop();
		}
		while(!q.empty()) q.pop();
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：小黑AWM (赞：0)

没有看到过用set的，贪心策略证明就不讲了，其他题解中有一位神仙详细的证明了，主要就是分类讨论当前是否采取贪心对后续过程的影响。

我的策略是：

**首先将线段按照左端点从大到小排序，然后从大到小地选择可用的防晒霜给奶牛上霜。就是尽量选择右边的点。**

那么我采用的是一个set来维护这个事情，每次在set中查找最后一个不大于他的数，总复杂度还是严格的O(nlogl)

~~不要问我为什么不用Priority_queue我只是想玩一下~~

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
const int maxn = 2505;
int c, l, SPF, cover[10000], ans;
pair<int, int> cow[maxn];
set<int> spf; 
bool cmp(pair<int,int> a, pair<int,int> b){
	return a.first > b.first;
}
int main(){
	cin >> c >> l;
	for(int i = 1; i <= c; i++)
		cin >> cow[i].first >> cow[i].second;
	sort(cow+1, cow+1+c, cmp);
	int temp;
	for(int i = 1; i <= l; i++){
		cin >> SPF >> temp;
		spf.insert(SPF);
		cover[SPF] += temp;
	}

	for(int i = 1; i <= c; i++){
		set<int>::iterator p = spf.lower_bound(cow[i].second);
		if(p == spf.end())
			p--;
		while(*p > cow[i].second){
			if(p == spf.begin())
				goto nxt;
			p--;
		}
		if(*p < cow[i].first)
			continue;
		ans++;
		cover[*p]--;
		if(cover[*p] == 0)
			spf.erase(p);
		nxt : cerr << cow[i].second << "-" << *p << endl;
		
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：苏景曦 (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,spfn,ssln;
struct sssl{int num,spf;}ssl[2510];struct sspf{int min,max;}spf[2510];
bool cmp(sssl a,sssl b){return a.spf>b.spf;}bool cmp1(sspf a,sspf b){return a.min>b.min;}
int main(){
	scanf("%d%d",&spfn,&ssln);
	for(int i=1;i<=spfn;i++)scanf("%d%d",&spf[i].min,&spf[i].max);
	for(int i=1;i<=ssln;i++)scanf("%d%d",&ssl[i].spf,&ssl[i].num);
	sort(ssl+1,ssl+1+ssln,cmp);/*很明显，数值越大的防晒霜越不容易被使用*/ 
	sort(spf+1,spf+1+spfn,cmp1);/*主要影响奶牛能否涂抹的因素在于其MIN*/
	for(int i=1;i<=ssln;i++){//每瓶防晒霜
		for(int k=1;k<=ssl[i].num;k++){//瓶子数量 
			for(int j=1;j<=spfn;j++){//每头奶牛 
				if(ssl[i].spf<=spf[j].max&&ssl[i].spf>=spf[j].min){//如果符合条件 
					ans++/*奶牛数量加一*/,ssl[i].num--/*瓶子数减一*/;
					spf[j].max=2147483647,spf[j].min=2147483647;/*赋值为一个极大值，表示奶牛已经涂过*/
				}
				if(ssl[i].num==0)break;/*显然的剪枝，如果防晒霜数目为零，结束本次循环*/
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Energy_Making (赞：0)

## First 你需要知道这道题要你干啥
先读题，题目微微有一点长，我的心中充满了慌张，难道这道题也不能留下我的迹象，这真让人感到悲凉。但其实这个题面简化下来是这样的：

·这里有C个点。（防晒霜）

·这里有L条线段，左端点为Left，右端点为Right。（奶牛）

·把点放进线段中，问可以放几个。

**思路顿时清晰了起来。**
## Second 思路
所以我们只需要将点由小到大排序，线段以右端点的位置由小到大排序，最后扫一次即可。

**你已经是一道水题了**

# 能让xxsAC此题的东西
```cpp
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
int C,L,ans;
struct cow
{
	int mins,maxs;
	bool mark;
};
cow cows[2505];
struct fss//防晒霜，原谅蒟蒻忘了防晒霜的单词。
{
	int SPF,cover;
};
fss fssm[2505];//防晒霜们 
bool cmpc(cow a,cow b)
{
	return a.maxs<b.maxs;//
}
bool cmpf(fss a,fss b)
{
	return a.SPF<b.SPF;
}
int main()
{
	scanf("%d %d",&C,&L);
	for(int i=1;i<=C;i++)scanf("%d %d",&cows[i].mins,&cows[i].maxs);
	sort(cows+1,cows+1+C,cmpc);右端点由小到大排序
	for(int i=1;i<=L;i++)scanf("%d %d",&fssm[i].SPF,&fssm[i].cover);
	sort(fssm+1,fssm+1+L,cmpf);点由小到大排序
	for(int i=1;i<=C;i++)
		for(int j=1;j<=L;j++)
		{
			if(fssm[j].SPF>=cows[i].mins&&fssm[j].SPF<=cows[i].maxs&&fssm[j].cover>0)//如果第i个点能放到第j条线段中。
			{
				fssm[j].cover--;
				ans++;
				break;
			}
		}
	printf("%d",ans);
	return 0;
}
```

---

