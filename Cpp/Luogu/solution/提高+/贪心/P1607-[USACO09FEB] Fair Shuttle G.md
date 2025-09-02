# [USACO09FEB] Fair Shuttle G

## 题目描述

Although Farmer John has no problems walking around the fair to collect prizes or see the shows, his cows are not in such good shape; a full day of walking around the fair leaves them exhausted. To help them enjoy the fair, FJ has arranged for a shuttle truck to take the cows from place to place in the fairgrounds.

FJ couldn't afford a really great shuttle, so the shuttle he rented traverses its route only once (!) and makes N (1 <= N <= 20,000) stops (conveniently numbered 1..N) along its path. A total of K (1 <= K <= 50,000) groups of cows conveniently numbered 1..K wish to use the shuttle, each of the M\_i (1 <= M\_i <= N) cows in group i wanting to ride from one stop S\_i (1 <= S\_i < E\_i) to another stop E\_i (S\_i < E\_i <= N) farther along the route.

The shuttle might not be able to pick up an entire group of cows (since it has limited capacity) but can pick up partial groups as appropriate.

Given the capacity C (1 <= C <= 100) of the shuttle truck and the descriptions of the groups of cows that want to visit various sites at the fair, determine the maximum number of cows that can ride the shuttle during the fair.


## 说明/提示

【样例说明】

班车可以把 $2$ 头奶牛从 $1$ 送到 $5$，$3$ 头奶牛从 $5$ 送到 $8$，$2$ 头奶牛从 $8$ 送到 $14$，$1$ 头奶牛从 $9$ 送到 $12$，$1$ 头奶牛从 $13$ 送到 $14$，$1$ 头奶牛从 $14$ 送到 $15$。


## 样例 #1

### 输入

```
8 15 3
1 5 2
13 14 1
5 8 3
8 14 2
14 15 1
9 12 1
12 15 2
4 6 1
```

### 输出

```
10
```

# 题解

## 作者：Cry_For_theMoon (赞：38)

&emsp;&emsp;[传送门](https://www.luogu.com.cn/problem/P1607)

&emsp;&emsp;典型的"线段树只是工具人"题目

&emsp;&emsp;大佬们竟然都没有怎么证明贪心？~~蒟蒻水社区分的机会到了~~

&emsp;&emsp;把 $m$ 个 $s$ 到 $e$ 的奶牛分开看作 $m$ 个 $s$ 到 $e$ 的区间，这样就不用考虑区间的个数问题了。

&emsp;&emsp;设 $F_{i,j}$ 是地点 $i...j$ 所能选择的最大区间数。

&emsp;&emsp;按照区间贪心的套路，先试试右端点排序。我们假设 $a_i$ 是所有在 $i...j$ 这段里的区间中结束最早的那个。假设最优解**没有** $a_i$。那么我们对最优解的所有区间的 **左端点排序**，把此时开始时间最早的区间记作 $a_j$。

- 如果$a_i,a_j$ 不交，一定可以选择 $a_i$，此时不是最优解

- 如果$a_j$ 完全包含 $a_i$，优先选 $a_i$ 显然可以让后面剩下的资源更多，这是因为在原来的方案里 $e_{a_i}...e_{a_j}$ 这一段的空间比优先选择 $a_i$ **少1**，那么必然解不会比选择 $a_i$ 更优。

- 否则 $s_{a_i} < s_{a_j},e_{a_i} < e_{a_j}$，此时选择 $a_i$ ，那么 $e_{a_i}... e_{a_j}$ 这段空间就会**多1**，显然我们可以选择更多的奶牛上车，即至少不会得到更差解。

&emsp;&emsp;综上，$F_i,j$ 的最优解中一定有一个解是包含 **结束时间最早的** 那个活动的。

&emsp;&emsp;不过这只是在最初的时候如此。考虑那个熟的不能再熟的区间调度问题，我们也不是一鼓作气把排完序以后找到最前面的一口气选择，而是找到第一个和上一个选择兼容的区间。这题稍有改动，我们如果要选择区间 $a_i$，那么必须保证 $s_{a_i}...e_{a_i}$ 这一段里面的任何一个时刻值都是小于 $c$ 的，而我们只需要维护最大值即可。

&emsp;&emsp;最后，题目本身一个区间里是有 $m$ 头奶牛的，通过我们上面的推断，如果选了第 $i$ 个区间，那么尽可能多的先把第 $i$ 个区间的奶牛选上，维护区间最大值 $maxn$，$\min(m_i,c-maxn)$ 就是当前选择能选择的个数。选择完了以后把区间整体加上一个选择个数即可。

&emsp;&emsp;本人本着代码能暴力就暴力的原则交了一发暴力代码上去，结果 64 分 TLE 泪目。不过看到"区间加""区间最大值"，这就是一个裸的线段树了。

&emsp;&emsp;与多数线段树的题不同的是，这一题难的不是数据结构，而是贪心的猜测与证明（反正我一开始没想出来），所以题解都没有写证明让我很害怕QwQ

&emsp;&emsp;当然，dalao们做贪心题都是"直觉猜测显然成立"的，只有我这种蒟蒻需要证明。

&emsp;&emsp;献上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=5e4+10;
int n,k,ans,c;
struct Line{
	int m,l,r;
	bool operator<(const Line& l2)const{
		return r < l2.r;
	}
}line[MAXN];
int zt[MAXN];
int tree[MAXN<<2],tag[MAXN<<2];
inline int lc(int x){return x<<1;}
inline int rc(int x){return lc(x)|1;}
void push_up(int);
void push_down(int);
int query(int,int,int,int,int);
void update(int,int,int,int,int,int);
int main(){
	scanf("%d%d%d",&k,&n,&c);
	for(int i=1;i<=k;i++){
		scanf("%d%d%d",&line[i].l,&line[i].r,&line[i].m);
	}
	sort(line+1,line+1+k);
	for(int i=1;i<=k;i++){
		int l = line[i].l,r = line[i].r,m = line[i].m;
		//max [l,r)
		int maxn = query(1,1,n,l,r-1);
		int chose =((c-maxn) < m)?(c-maxn):m;
		ans += chose;
		//[l,r) += chose
		update(1,1,n,l,r-1,chose);
	}
	cout<<ans;
	return 0;
}
void push_up(int x){
	tree[x] = max(tree[lc(x)],tree[rc(x)]);
}
void push_down(int x){
	//只维护max甚至不需要l,r？
	tree[lc(x)] += tag[x];
	tree[rc(x)] += tag[x];
	tag[lc(x)] += tag[x];
	tag[rc(x)] += tag[x]; 
	tag[x] = 0; 
}
int query(int x,int l,int r,int ql,int qr){
	if(ql <= l && qr >= r){
		return tree[x];
	}
	int mid = (l+r)>>1;
	int ans = 0;
	push_down(x);
	if(ql <= mid){
		ans = max(ans,query(lc(x),l,mid,ql,qr));
	}
	if(qr > mid){
		ans = max(ans,query(rc(x),mid+1,r,ql,qr));
	}
	push_up(x);
	return ans;
}
void update(int x,int l,int r,int ql,int qr,int value){
	if(ql <= l && qr >= r){
		tree[x] += value;
		tag[x] += value;
		return;
	}
	int mid = (l+r)>>1;
	push_down(x);
	if(ql <= mid){
		update(lc(x),l,mid,ql,qr,value);
	}
	if(qr > mid){
		update(rc(x),mid+1,r,ql,qr,value);
	}
	push_up(x);
}
```

&emsp;&emsp;END

---

## 作者：租酥雨 (赞：18)

贪心有一道很经典的例题：活动安排。

只有一间教室，要安排尽可能多的活动。

那么我们用一个变量t表示已安排最后一个活动的结束时间，赋初值为-1，按活动结束时间排序，依次接受，接受的时候注意判断，一定要该活动的开始时间>=上一个活动的结束时间。

说了这么多，我们来看这道题。

C的空间可以看作是共C间教室，那么我们就应该用一个数组来存储每一空间位置上奶牛的下车地点（每一间教室活动结束的时间）。贪心策略：同样按照结束时间排好，每一次上尽可能多的奶牛，上了之后，在对应空间位置上存放该奶牛的下车地点，当一只奶牛上车时，优先考虑与上一只奶牛时间点相近的（尽量使车可以坐满）

所以要用到排序，插入排序，在每一组奶牛上车后（可以只上一部分），将每个空间位置的下车地点从小到大排序

具体见代码





        
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
//用一个队列来存储每个单位空间被占用的结束时间 
struct cow{
    int begin,end;
    int num;
}a[50001];
int h[200]={0};//从1开始计数 
int N,K,C,ans=0;
int rd()
{
    int x=0;
    char c=getchar();
    while (c<'0'||c>'9') c=getchar();
    while (c>='0'&&c<='9') 
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}
bool cmp(cow a,cow b)
{
    return a.end<b.end||(a.end==b.end&&a.begin>b.begin);
}
int main()
{
    freopen("cow.in","r",stdin);
    K=rd();N=rd();C=rd();
    for (int i=1;i<=K;i++)
    {
        a[i].begin=rd();
        a[i].end=rd();
        a[i].num=rd();
    }
    sort(a+1,a+K+1,cmp);//按照结束点排序 
    for (int i=1;i<=K;i++)
    {
        if (a[i].begin<h[1]) continue;
        int x=1;//某一组中可以乘车的奶牛数量
        while (x<=a[i].num&&x<=C&&a[i].begin>=h[x]) x++;
        x--;
        //删去数组中比a[i].begin小的最大的x个数 
        int p;
        for (p=1;p<=C;p++) if (h[p]>a[i].begin) break;//p是第一个大于begin的位置 
        p-=x;
        while (h[p+x]<a[i].end&&p+x<=C) h[p]=h[p+x],p++;
        for (int w=1;w<=x;w++) h[p++]=a[i].end;
        ans+=x;
    }
    printf("%d",ans);
    fclose(stdin);
    return 0;
}
```

---

## 作者：King丨帝御威 (赞：8)

题意是给你几堆奶牛，每个奶牛都有想去的地方，给你一个汽车，汽车有一个容量和固定的行走路线，询问最多能搭载的奶牛的数量。

我们来考虑一种贪心的思想，按右端点从小到大排一遍序，为什么呢？后面说，然后对排好序的每堆奶牛依次进行遍历，如果当前有空位，空位大于这堆奶牛的数量，那就全上去，不然的话，就能上去几个就上去几个。这样下来的话，结果一定是最优的，其正确性不难证明，因为刚开始我们对每堆奶牛要到的地方从小到大排了序(即终点)，那么每个位置最多只有一次奶牛上车，而且这些奶牛来自同一群，所以我们对每堆奶牛分别进行考虑即可，这就是为什么要按右端点排序的原因。贪心过程中，要维护最大值。因为要算最少的空位子，下面给出两种代码：

1、纯贪心&贪心：
```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#define maxn 50007
using namespace std;
int ans,n,m,k,w[maxn];
inline int qread() {
  char c=getchar();int num=0,f=1;
  for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
  for(;isdigit(c);c=getchar()) num=num*10+c-'0';
  return num*f;
}
struct node {
  int u,v,c;
}e[maxn];
const int inf=0x7fffffff;
inline bool cmp(node a, node b) {
  if(a.v!=b.v) return a.v<b.v;
  return a.u<b.u;
}
int main() {
  k=qread(),n=qread(),m=qread();
  for(int i=1;i<=k;++i) e[i].u=qread(),e[i].v=qread(),e[i].c=qread();
  sort(e+1,e+1+k,cmp);
  for(int i=1;i<=k;++i) {
    if(w[e[i].u]>=m) continue;
    int minn=inf;
    for(int j=e[i].u;j<=e[i].v;++j) {
      minn=min(m-w[j],minn);
      if(minn<=0) break;
    }
    if(minn>0) {
      if(minn>=e[i].c) { 
        for(int j=e[i].u;j<e[i].v;++j)
          w[j]+=e[i].c;
        ans+=e[i].c;
      }
      else {
        for(int j=e[i].u;j<e[i].v;++j)
          w[j]+=minn;
        ans+=minn;
      }
    }
  }
  printf("%d\n",ans);
  return 0;
}
```

2、线段树&贪心&排序：

``` cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#define maxn 20007
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const int inf=0x7fffffff;
int n,k,m,maxx[maxn<<2],lazy[maxn<<2],zrj,w[50007];
inline int qread() {
  char c=getchar();int num=0,f=1;
  for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
  for(;isdigit(c);c=getchar()) num=num*10+c-'0';
  return num*f;
}
struct node {
  int u,v,c;
}e[50007];
inline bool cmp(node a, node b) {
  if(a.v!=b.v) return a.v<b.v;
  return a.u<b.u;
}
inline void pushup(int rt) {
  maxx[rt]=max(maxx[ls],maxx[rs]);
}
inline void pushdown(int rt) {
  if(lazy[rt]) {
    maxx[ls]+=lazy[rt],lazy[ls]+=lazy[rt];
    maxx[rs]+=lazy[rt],lazy[rs]+=lazy[rt];
    lazy[rt]=0;
  }
}
void modify(int rt, int l, int r, int L, int R, int val) {
  if(L>r||R<l) return;
  if(L<=l&&r<=R) {
    lazy[rt]+=val,maxx[rt]+=val;
    return;
  }
  int mid=(l+r)>>1;
  pushdown(rt);
  modify(ls,l,mid,L,R,val),modify(rs,mid+1,r,L,R,val);
  pushup(rt);
}
int cmax(int rt, int l, int r, int L, int R) {
  if(L>r||R<l) return -inf;
  if(L<=l&&r<=R) return maxx[rt];
  int mid=(l+r)>>1,ans=-inf;
  pushdown(rt);
  if(L<=mid) ans=max(ans,cmax(ls,l,mid,L,R));
  if(R>mid) ans=max(ans,cmax(rs,mid+1,r,L,R));
  return ans;
}
int main() {
  k=qread(),n=qread(),m=qread();
  for(int i=1;i<=k;++i) e[i].u=qread(),e[i].v=qread(),e[i].c=qread();
  sort(e+1,e+1+k,cmp);
  for(int i=1;i<=k;++i) {
    int p=cmax(1,1,n,e[i].u,e[i].v-1);
    int minn=min(m-p,e[i].c);
    zrj+=minn,w[i]+=minn;
    modify(1,1,n,e[i].u,e[i].v-1,w[i]);
  }
  printf("%d\n",zrj);
  return 0;
}
```

希望这篇题解对大家能有所帮助。

---

## 作者：ysner (赞：8)

这道题是一道典型的贪心题，由于此题数据很水，所以可用暴搜解决（有极端数据就要用线段树等高级东西了，而我这种小蒟蒻是不懂的）。

1、注意各组的奶牛可分开；（我在这里被卡了好久。。。）

2、程序开始要对数据进行排序，第一要求是终点靠前，第二要求是起点靠前（就是终点相同时比起点）；

3、这个程序应该比上面的题解简单易懂且来的粗暴。。。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
struct yun
{
  int q;//起点
  int z;//终点
  int sum;//一组奶牛数
} a[50001]={};
bool com1(yun a,yun b)
{
  return (a.z<b.z)||(a.z==b.z&&a.q<b.q);//排序规则
}
int k,n,c,b[20001]={},f,ans=0,ans1=0;
int main()
{
  int i,j,Min;
  cin>>k>>n>>c;//这道题里n好像没什么用
  for(i=0;i<k;i++)
    cin>>a[i].q>>a[i].z>>a[i].sum;
  sort(a,a+k,com1);
    ans=0;
    for(i=0;i<k;i++)
    {
      Min=2147483647;
      if(b[a[i].q]<c)//起点都满了就别上车了吧
      {
          for(j=a[i].q;j<a[i].z;j++) {Min=min(c-b[j],Min);if(Min==0) break;}//寻找一组奶牛乘坐路程中巴士剩下的最少位置，这组奶牛最多能上巴士的个数等于Min（Min等于0时保持原样就行，这是最优情况）
          if(Min!=0)//注意Min为负数也要算，减去多余的奶牛
          {
            if(Min>=a[i].sum)
            {
            for(j=a[i].q;j<a[i].z;j++) {b[j]+=a[i].sum;}
            ans+=a[i].sum;
          }  
          else 
          {
            for(j=a[i].q;j<a[i].z;j++) {b[j]+=Min;}
            ans+=Min;//尽量多的奶牛上车
          }
        }
      }
    }
  cout<<ans<<endl;
  return 0;
}
```

---

## 作者：Hank (赞：8)

**仿佛没有详细的线段树版题解,来一发**:

**首先原则是优先选结束位置最小的,能选就选,然后就是怎么判断是否可以选,那么可以选的条件是这个组的[L,R]之间的最大值加上这个组的人不会超过最大容量C,所以维护一个区间最大值就好,本蒟蒻用的是线段树,然后每一次选完后就在线段树中[L,R-1] 加上这个组的人数即可**

[代码看这里](http://www.cnblogs.com/Yuzao/p/7435869.html)


---

## 作者：_蒟蒻__ (赞：5)

贪心排序的思想很多大佬已经讲了， 这里本蒟蒻就给大家提供一种无脑的multiset做法。

开一个multiset (注意不是set, 因为允许重复)当做车， 记录一下当前车上的每一只奶牛的终点，每访问到一个点， 遍历一下以该点作为起点的所有奶牛分组。 根据贪心的思想——让先下车的上车一定比后下车的更优， 所以我们就把后下车的尽可能多的替换成先下车的， 然后每到一个点时统计一下答案。

怎么样， 是不是非常暴力?

那么问题来了， 这么暴力的东西， 为啥能过呢？？

1.~~数据水~~

2.注意看啦， 题目中有个重要的性质——$c<=100$， 所以呢每个点最多进行100次替换操作， 最坏复杂度也就是 $O(100 * 20000 * log 100)$ ，妥妥的！

生命苦短， 直接上代码。
```cpp
#include <iostream>
#include <vector>
#include <cstdio>
#include <set>
#define pr pair<int, int>
#define mk make_pair
using namespace std;
const int N=20010;
int k, n, c, ans;
vector <pr> v[N];
multiset <int> s;
multiset <int> :: iterator it;
int main()
{
	ios::sync_with_stdio(false);
	cin>>k>>n>>c;
	for(int i=1, S, T, num; i<=k; i++)
	{
		cin>>S>>T>>num;
		v[S].push_back(mk(T, num));
	}
	for(int i=1; i<=n; i++)
	{
		while(*s.begin()==i) 
			s.erase(s.begin()), ans++;

		for(int j=0; j<v[i].size(); j++)
		{
			int t=v[i][j].first, 
				num=v[i][j].second;
			while(s.size()<c && num) 
				s.insert(t), num--;
			it=s.end(), it--;
			while(*it>t && num) 
				s.erase(it), s.insert(t), num--, 
				it=s.end(), it--;
		}
	}
	cout<<ans;
	return ~~ (0 ^ 0) ;
}
```


---

## 作者：KobeWu (赞：5)

### 解题之前
初看这道题，我想起了[P1937 USACO10MAR 仓配置Barn Allocation](https://www.luogu.org/problem/P1937),两者在我看来确实比较相似，因为他们都显然可以用贪心+线段树~~被正在阅读这篇题解的巨佬秒切~~。但是两题的贪心（我的想法）略有不同，而且在$\mathbb{AC}$之前，我$\mathbb{WA}$了。于是我来写这篇题解。
### 题目分析
乍一看此题，应该不难发现可以直接排序+贪心~~秒切~~。~~然而我就想写线段树。~~

由于FJ的班车只能从$1$到$N$跑一次，而且每一组奶牛也只从$s$到$t$跑一次，再加上要用线段树维护，我们考虑做如下转换：

- FJ的班车 $\rightarrow$ 一个端点为1和N的区间
- 一组要从$s$跑到$t$的$m$头奶牛 $\rightarrow$ 一个端点为$s$和$t$的占用空间为$m$的区间

那么，我们得到了一些区间。但是，线段树要维护什么呢？又怎么判断班车在某个位置时还有多少空间呢？

其实非常简单。因为对于一组要从$s$跑到$t$的奶牛，如果在$s$到$t$这个区间内有一个时刻班车装不下这一组所有的奶牛，那么这整组奶牛是不可能全部从$s$跑到$t$的。由此，我们考虑用线段树维护区间最大值（最小值其实也行），然后在处理一组奶牛时，查询区间最大值，就可以得到这组奶牛的上车情况了。

那么，怎样达到题目的要求呢？

> 计划一个尽可能满足更多奶牛愿望的方案。

其实这跟排序+贪心的思路是一样的，即：以$t$从小到大为第一关键字，以$s$从小到大为第二关键字，把奶牛排序。然后按这个顺序进行操作，并记录上车的奶牛的总数即可。

### 容易疏忽的地方
1. 允许一组中的一部分奶牛乘坐班车~~而抛弃剩下的奶牛~~。也就是说，每次查询区间最大值时，应该计算出最多还有多少奶牛可以上车。~~不然连样例都过不了。~~
2. 根据题目描述，FJ的奶牛们被分成了$K(1 \leq K \leq 5 \times 10^4)$小组，第$i$组有$M_i(1 \leq M_i \leq 2 \times 10^4)$头奶牛。$Therefore, theoretically speaking,$ FJ最多有$1 \times 10^8$头奶牛。所以，FJ其实挺有钱。

以下为我的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MXN 20010
#define MXQ 50010
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
int N,M,C;
struct Queries {int l,r,val;}q[MXQ];
struct SegmentTree {int l,r,minval,tag;}tr[MXN<<2];
inline int rd()
{
	int ret=0,f_f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f_f=-1; c=getchar();}
	while(c>='0' && c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ret*f_f;
}
inline bool cmp(Queries x,Queries y) {return x.r == y.r ? (x.l < y.l) : (x.r < y.r);}
inline void PushUp(int u) {tr[u].minval=Min(tr[u<<1].minval,tr[u<<1|1].minval);}
inline void Build(int u,int l,int r)
{
	tr[u].l=l,tr[u].r=r;
	tr[u].tag=0,tr[u].minval=C;
	if (l == r) return;
	int mid=(l+r)>>1;
	Build(u<<1,l,mid);
	Build(u<<1|1,mid+1,r);
	PushUp(u);
}
inline void PushDown(int u)
{
	if (tr[u].tag == 0) return;
	tr[u].minval+=tr[u].tag;
	if (tr[u].l != tr[u].r)
	{
		tr[u<<1].tag+=tr[u].tag;
		tr[u<<1|1].tag+=tr[u].tag;
	}
	tr[u].tag=0;
}
inline void Modify(int u,int l,int r,int dt)
{
	PushDown(u);
	if (tr[u].l >= l && tr[u].r <= r)
	{
		tr[u].tag+=dt;
		return;
	}
	int mid=(tr[u].l+tr[u].r)>>1;
	if (l <= mid) Modify(u<<1,l,r,dt);
	if (r >= mid+1) Modify(u<<1|1,l,r,dt);
	PushDown(u<<1),PushDown(u<<1|1),PushUp(u);
}
inline void Query(int u,int l,int r,int &res)
{
	PushDown(u);
	if (tr[u].l >= l && tr[u].r <= r)
	{
		res=Min(res,tr[u].minval);
		return;
	}
	int mid=(tr[u].l+tr[u].r)>>1;
	if (l <= mid) Query(u<<1,l,r,res);
	if (r >= mid+1) Query(u<<1|1,l,r,res);
	PushDown(u<<1),PushDown(u<<1|1),PushUp(u);
}
int main()
{
	N=rd(),M=rd(),C=rd();
	for (int i=1;i<=N;i++)
		q[i].l=rd(),q[i].r=rd()-1,q[i].val=rd();
	sort(q+1,q+1+N,cmp);
	Build(1,1,M);
	int minv,ans=0;
	for (int i=1;i<=N;i++)
	{
		minv=C+1,Query(1,q[i].l,q[i].r,minv);
		if (minv != 0) Modify(1,q[i].l,q[i].r,-Min(minv,q[i].val)),ans+=Min(minv,q[i].val);
	}
	return printf("%d\n",ans),0;
}
```

---

## 作者：Starria的脑残粉 (赞：2)

想刷一下线段树题然后就写了个线段树。。

排序后贪心思路是显然正确的因为找不出更优解。。

线段树维护区间加区间max

连标记下传都不用，直接永久化好了

可以说很傻了

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,c,ans,ma[1000000],lazy[1000000];
struct lsg{int x,y,z;}a[1000000];
int read(){
    char c=getchar();while (c!='-'&&(c<'0'||c>'9'))c=getchar();
    int kk=1,k=0;if (c=='-')kk=-1,c=getchar();
    while (c>='0'&&c<='9')k=k*10+c-'0',c=getchar();return kk*k;
}int findit(int x,int y,int l,int r,int d){//查询max操作
    if (x<=l&&y>=r)return ma[d];
    int m=(l+r)/2,ans=lazy[d];
    if (x<=m)ans=max(ans,findit(x,y,l,m,d*2)+lazy[d]);
    if (y>m)ans=max(ans,findit(x,y,m+1,r,d*2+1)+lazy[d]);
    return ans;
}void putit(int x,int y,int z,int l,int r,int d){//区间加
    if (x<=l&&y>=r){lazy[d]+=z;ma[d]+=z;return;}
    int m=(l+r)/2;if (x<=m)putit(x,y,z,l,m,d*2);
    if (y>m)putit(x,y,z,m+1,r,d*2+1);
    ma[d]=max(ma[d*2],ma[d*2+1])+lazy[d];
}bool pd(lsg x,lsg y){return x.y<y.y;}//按右端点排序
int main(){
    k=read();n=read();c=read();for (int i=1;i<=k;i++)a[i].x=read(),a[i].y=read()-1,a[i].z=read();
    sort(a+1,a+1+k,pd);for (int i=1;i<=k;i++){
        int x=findit(a[i].x,a[i].y,1,n,1),y=min(c-x,a[i].z);//贪心
        ans+=y;putit(a[i].x,a[i].y,y,1,n,1);
    }cout<<ans<<endl;
}

```

---

## 作者：Saber_Master (赞：1)

[P1607 [USACO09FEB]Fair Shuttle G](https://www.luogu.com.cn/problem/P1607)

#### 贪心

策略：首先对右端点升序排序，右端点相同则按左端点升序排序.排完序后一一枚举，若有空位，则乘车，否则不乘，容易发现这种做法是最优的.

略证：由于我们已经按照右端点排序，所以假设当前车满了的话，我们倘若将先前上车的奶牛踢出，那么无法获得更多代价，且当前奶牛上车后右端点更大，对后面奶牛上车越不利，故此策略成立.

难点在于如何寻找当前段车上的空位.何以维护？线段树永久化标记即可.

$O(nlogn)$

```cpp
ll k, n, c;

struct node{
	ll l, r, v;
	
	node(){}	
	node(ll LL, ll RR, ll VV):l(LL), r(RR), v(VV){}
	
	inline bool operator <(const node &X)const{
		return this->r==X.r?this->l<X.l:this->r<X.r;  //排序
	}
}o[M];

namespace seg{
	ll dat[N<<2], lazy[N<<2]; //永久化标记，查询及上传的时候统计即可
	
	inline void update(ll p, ll l, ll r, ll u, ll v, ll val){
		if (u<=l && r<=v) return (void) (dat[p]+=val, lazy[p]+=val);
		ll mid=l+r>>1;
		if (u<=mid) update(p<<1, l, mid, u, v, val);
		if (v>mid) update(p<<1|1, mid+1, r, u, v, val);
		dat[p]=max(dat[p<<1], dat[p<<1|1])+lazy[p];  
	}
	
	inline ll query(ll p, ll l, ll r, ll u, ll v){
		if (u<=l && r<=v) return dat[p];
		ll mid=l+r>>1, res=0;
		if (u<=mid) chkmax(res, query(p<<1, l, mid, u, v));
		if (v>mid) chkmax(res, query(p<<1|1, mid+1, r, u, v));
		return res+lazy[p];  //勿忘标记
	}
	
}

ll res;
int main(){
	read(k); read(n); read(c);
	for (R ll i=1, l, r, v; i<=k; i++){
		read(l); read(r); read(v); --r;
		o[i]=node(l, r, v);
	}
	sort(o+1, o+k+1);  //结构体排序
	for (R ll i=1, tmp, rem; i<=k; i++){
		rem=seg::query(1, 1, n, o[i].l, o[i].r);
		if (rem<c){   //若有空位
			tmp=min(c-rem, o[i].v);  //寻找能上车的奶牛最大数
			res+=tmp;
			seg::update(1, 1, n, o[i].l, o[i].r, tmp); 
		}
	}
	writeln(res);
}
```


---

## 作者：MorsLin (赞：0)

据说$NOIp$前发题解可以$\mathfrak{RP}$++

---

因为要尽可能满足更多奶牛，所以按照这种区间贪心题的套路，先按右端点排序，然后依次遍历，能坐车的就让它们坐车，这样一定是最优的。  
在贪心的时候，我们要知道在车在当前的时间段中最少有多少空位，可以用线段树维护（也可以不用线段树，但个人感觉用线段树比较好理解）。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
using namespace std;
int read(){
	int k=0; char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	  k=k*10+c-48,c=getchar();
	return k;
}
struct zzz{
	int st,en,num;
}cow[50010];
bool cmp(zzz x,zzz y){ //按右端点排序
	return x.en < y.en;
}
int tree[20010<<2],tag[20010<<2];  //以下为线段树维护区间最大值
inline void down(int l,int r,int p){
	tree[ls]+=tag[p]; tree[rs]+=tag[p];
	tag[ls]+=tag[p]; tag[rs]+=tag[p];
	tag[p]=0;
}
inline void up(int p){
	tree[p]=max(tree[ls],tree[rs]);
}
void update(int l,int r,int p,int nl,int nr,int k){
	if(l>=nl&&r<=nr){
		tree[p]+=k; tag[p]+=k; return ;
	}
	down(l,r,p);
	if(nl<=mid) update(l,mid,ls,nl,nr,k);
	if(nr>mid) update(mid+1,r,rs,nl,nr,k);
	up(p);
}
int query(int l,int r,int p,int nl,int nr){
	int ans=0;
	if(l>=nl&&r<=nr) return tree[p];
	down(l,r,p);
	if(nl<=mid) ans=max(ans,query(l,mid,ls,nl,nr));
	if(nr>mid) ans=max(ans,query(mid+1,r,rs,nl,nr));
	return ans;
}
int main(){
	int k=read(),n=read(),c=read();
	for(int i=1;i<=k;i++)
	  cow[i].st=read(),cow[i].en=read()-1,cow[i].num=read();
	sort(cow+1,cow+k+1,cmp);
	int maxn=0;
	for(int i=1;i<=k;i++){  //遍历区间
		int x=query(1,n,1,cow[i].st,cow[i].en);
		if(x<c){
			int f=min(c-x,cow[i].num);  //当前能有几头奶牛上车
			maxn+=f;
			update(1,n,1,cow[i].st,cow[i].en,f);
		}
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：eternal (赞：0)

贪心，按照结束的时间排序，取最多的，可以用数学归纳法证明其最优性

        
        
        
```cpp
#include <bits/stdc++.h>
#define rep( i , l , r ) for( int i = (l) ; i <= (r) ; ++i )
#define per( i , r , l ) for( int i = (r) ; i >= (l) ; --i )
#define erep( i , u ) for( int i = head[(u)] ; ~i ; i = e[i].nxt )
#define PII pair<int,int> 
#define MP make_pair
#define PB push_back
using namespace std;
inline int _read(){
    register int x = 0 , f = 1;
    register char ch = getchar();
    while( ch > '9' || ch < '0' ) { if( ch == '-' ) f = -1; ch = getchar(); }
    while( ch >= '0' && ch <= '9' ){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int maxn = 20000 + 5;
int t[maxn];
vector<PII> g[maxn];
set<int> s;
#define now g[i][j].first
#define own g[i][j].second
#define head (*s.begin())
#define rear (*s.rbegin())
int main(){
    int M = _read() , N = _read() , c = _read();
    int u , v , w;
    while( M-- ){
        u = _read() , v = _read() , w = _read();
        g[u].PB( MP( v , w ) );
    }
    rep( i , 1 , N ) sort( g[i].begin() , g[i].end() );
    int res = 0 , incar = 0 , _in = 0;
    for( int i = 1 , j ; i <= N ; ++i ){
        while( !s.empty() && head == i ){
            res += t[head] , incar -= t[head];
            s.erase( head );
        }
        for( j = 0 ; j < g[i].size() && incar < c ; ++j ){
            _in = min( c - incar , own );
            t[now] += _in , incar += _in , own -= _in;
            s.insert( now );
            if( incar == c ) break; 
        }
        for( ; j < g[i].size() && rear > now ; ++j ){
            while( !s.empty() && own ){
                _in = min( own , t[rear] );
                t[rear] -= _in , t[now] += _in;
                s.insert( now );
                if( !t[rear] ) s.erase( rear );
                own -= _in;
            }
        }
    } 
    cout << res << endl;
    return 0;
}

```

---

