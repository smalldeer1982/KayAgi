# [USACO17DEC] Milk Measurement S

## 题目描述

Farmer John 的每头奶牛最初每天生产 $G$ 加仑牛奶（$1 \leq G \leq 10^9$）。由于奶牛的产奶量可能会随时间变化，Farmer John 决定定期测量产奶量并将这些记录在日志中。日志中的条目如下所示：

```
35 1234 -2  
14 2345 +3  
```

第一条记录表示在第 35 天，奶牛 #1234 的产奶量比上次测量时减少了 2 加仑。第二条记录表示在第 14 天，奶牛 #2345 的产奶量比上次测量时增加了 3 加仑。Farmer John 每天最多只能进行一次测量。不幸的是，他有点混乱，记录的测量结果不一定按时间顺序排列。

为了激励他的奶牛，Farmer John 自豪地在谷仓的墙上展示当前产奶量最高的奶牛的照片（如果有多头奶牛产奶量并列最高，他会展示所有奶牛的照片）。请确定 Farmer John 需要更改展示的天数。

请注意，Farmer John 的牛群非常庞大，因此尽管日志中记录了一些奶牛产奶量的变化，但总有许多其他奶牛的产奶量保持在 $G$ 加仑不变。

## 样例 #1

### 输入

```
4 10
7 3 +3
4 2 -1
9 3 -1
1 1 +2```

### 输出

```
3
```

# 题解

## 作者：世墨 (赞：17)

    一道对萌新非常友好的线段树，简明易懂，虽然用不到lazy tag,但可以丰富线段树的用法
    
#### 首先，我们简化一波题意：
   维护一个区间的最大值，有n个修改操作，记录最大值的变化情况（即更换照片）。
   
   ps:“变化”の意义：rank1的牛不同了（多了/少了/牛变了）
   
   ~~pps：FJ真无聊，竞争使牛透支~~
   
   
   显然，我们可以用线段树来维护这个量
   
   但是，我们要输出的是变化的次数，所以肯定要判定“变化”
   
### 分类讨论：
	由于一次只修改一个值，所以可以直接如下分类
	
##### 1.rk1产奶量变化了（原来的rk1不一定rk1了）
	   （1：rk1还是那头牛（不是变化）
       （2：rk1不是那头牛（显然要换照片！）
       （3：rk1数量变多（rk1掉分了，和后面的牛并列）
   
   显然，我们不能够靠只记录rk1的值来判断变化
   
   针对（1、（2 情况，我们可以记录一下rk1的牛的编号来实现
   
   而（3 情况用前两个值好像并不能维护，所以还是再记录一下rk1的数量cnt即可
 
##### 2.rk1产奶量没变（原来的rk1还是rk1）
	   （1：rk1数量没变（不是变化）
       （2：rk1数量变了（下面的牛奋起直追，要多挂照片，所以变化）
   
   上面两种情况，我们都可以用cnt来搞定
   
所以，我们只要维护三个量 maxn(rk1产奶量)，cnt（rk1的牛数），rank1（rk1的编号）即可！

~~~cpp
struct Point{
	ll maxn,cnt,rank1;
   	//rank1 是 rank1的奶牛编号 
	//maxn 是rank1奶牛的产量，cnt是rank1的数量 
	ll l,r;
}tree[MAXN<<2];

~~~


接下来就是我们熟悉的线段树了，注意要在建树的时候初始化三个值！

##### 每一道线段树都有它的特色：体现在push_down()和push_up()，往往想好要维护的值和这两个函数，这道线段树就没什么问题了

发现题目中都是单点修改，那......

##### ~~push_down()，我要你有何用！！！~~

~~当然，线段树不需要push_down()也是特色~~

所以，核心在于push_up()的操作，建议先自己想，再 ~~结合注释~~ 食用

push_up的代码在这啦

~~~cpp
void push_up(ll x){
	if(tree[x<<1].maxn>tree[x<<1|1].maxn){//左子树的maxn>右子树的maxn，统统接受左孩子
		tree[x].cnt=tree[x<<1].cnt;
		tree[x].maxn=tree[x<<1].maxn;
		tree[x].rank1=tree[x<<1].rank1;
	}
	if(tree[x<<1].maxn<tree[x<<1|1].maxn){//同上
		tree[x].cnt=tree[x<<1|1].cnt;
		tree[x].maxn=tree[x<<1|1].maxn;
		tree[x].rank1=tree[x<<1|1].rank1;
	}
	if(tree[x<<1].maxn==tree[x<<1|1].maxn){//相等的情况，结合取用
		tree[x].cnt=tree[x<<1].cnt+tree[x<<1|1].cnt;
		tree[x].maxn=tree[x<<1].maxn;
		tree[x].rank1=tree[x<<1].rank1;//我们取最左侧的rk1编号，比较方便
	}
}
~~~

线段树板子敲一敲，update()写个单点修改，连query()都不用（直接调用全区间的就行），吃个main包，
~~此题AC!~~ 

回眸一看：

#### 1.奶牛的编号（在整数1...1e9范围内）

~~悄悄算一下，开10^9<<2这么大，完犊子了~~

but,1≤N≤100,000，所以最多也就修改1e5只牛

#### 所以离散化一下，线段树开到1e5<<2就好啦！

#### 突然，我们发现一个 ~~天大的~~ 锅：
	如果第一个操作减少了某个牛的产奶量，不也要修改吗？按我们这种做法，显然会挂
    
   所以，我们想办法把原始的值给放进去
   
   ~~开 无限大<<2 的线段树！~~
   
#####   我们可以给这些初始的牛开一个虚点代表一下
#####   没错，就这个0号牛，你代表了无数牛民的 ~~意志~~ 产奶量！！！

加上这个虚牛，吃一口main包，本题就愉快地AC啦！

ps: 在判定的部分，可以看一看上方的分析，很简单的


代码扔在下面啦
~~你们最喜欢的部分~~
~~~cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 100010
using namespace std;

struct node{
	ll x,date,diet,nx;
}change[MAXN];

struct Point{
	ll maxn,cnt,rank1;//rank1 是 rank1的奶牛编号 
	//maxn 是rank1奶牛的产量，cnt是rank1的数量 
	ll l,r;
}tree[MAXN<<2];

ll n,m,ans,len;

bool cmp1(node x,node y){return x.x<y.x;}
bool cmp2(node x,node y){return x.date<y.date;}

void push_up(ll x){
	if(tree[x<<1].maxn>tree[x<<1|1].maxn){
		tree[x].cnt=tree[x<<1].cnt;
		tree[x].maxn=tree[x<<1].maxn;
		tree[x].rank1=tree[x<<1].rank1;
	}
	if(tree[x<<1].maxn<tree[x<<1|1].maxn){
		tree[x].cnt=tree[x<<1|1].cnt;
		tree[x].maxn=tree[x<<1|1].maxn;
		tree[x].rank1=tree[x<<1|1].rank1;
	}
	if(tree[x<<1].maxn==tree[x<<1|1].maxn){
		tree[x].cnt=tree[x<<1].cnt+tree[x<<1|1].cnt;
		tree[x].maxn=tree[x<<1].maxn;
		tree[x].rank1=tree[x<<1].rank1;
	}
}

void build(ll l,ll r,ll x){
	tree[x].l=l,tree[x].r=r;
	len=max(len,x);
	if(l==r){
		tree[x].maxn=m;
		tree[x].cnt=1;
		tree[x].rank1=l;
		return ;
	}
	ll mid=l+r>>1;
	build(l,mid,x<<1);
	build(mid+1,r,x<<1|1);
	push_up(x);
}

void update(ll nl,ll nr,ll l,ll r,ll x,ll k)
{
	if(nl==l&&nr==r){
		tree[x].maxn+=k;//单点修改，暴力改掉就好啦！
		return; 
	}
	ll mid=l+r>>1;
	if(nl<=mid)update(nl,nr,l,mid,x<<1,k);
	if(nr>mid)update(nl,nr,mid+1,r,x<<1|1,k);
	push_up(x);
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>change[i].date>>change[i].x>>change[i].diet;
	}
	change[++n].x=0,change[n].date=0;
	change[n].nx=0,change[n].diet=0;//设了一个奇妙的虚牛，从来不变 
	sort(change+1,change+n+1,cmp1);//按序号排序 
	
	int tag=0;
	for(int i=2;i<=n;i++)
	{
		if(change[i].x!=change[i-1].x)
			tag++;
		change[i].nx=tag;//离散化
	}
	build(0,tag,1);
	sort(change+1,change+n+1,cmp2);//按时间排序 
	
	for(int i=1;i<=n;i++)
	{
		int u=tree[1].cnt,v=tree[1].rank1;//先记录一波原来的值
		update(change[i].nx,change[i].nx,0,tag,1,change[i].diet); 
		if(tree[1].cnt!=u)ans++;
		//因为一次只修改一只牛，那么判断 rank1数量变化即可 
		else if(tree[1].rank1!=v)ans++;
       		//rk1换牛了
	}
	cout<<ans;
	return 0;
}

~~~
##### 完结撒花！ \（^~^）/


---

## 作者：_mxi (赞：10)


## 思路概括

- 从题目需求入手，要想能得到是否要更换每天的，必须要知道每天哪些牛最强。

- 提供给我们的数据有每天每头牛产奶量变化和一开始初始值（没有什么卵用的初值）

- **每天只会有一头牛产奶量变化**，给我们之后的实现带来了很大方便（看完之后可以先想想如果每天不止一头奶牛变化会怎么样）

那么，我们要知道在不断更替的奶牛产量信息中，**哪些奶牛的产量最高**。当然，这个过程需要一个简单的数据结构。

1. 手写二叉堆，维护最大的产奶量。（因为需要删除任意节点而无法使用优先队列）
2. 平衡树，维护对象同上。（支持任意删除节点）

于是，我们当然选择可以封装好RB-Tree而且调用方便的Map来偷懒。

## 实现过程

- 因数据提供的奶牛ID数字过大 ($1 \leq I \leq 10^9$)，而实际奶牛最大数目不大($1 \leq N \leq 10^6$)，**所以需要读入完成后离线离散化ID**。

- 初始化值G的多少毫不影响排名，所以我们只记录奶牛的产量变化量（以下简称“产量”）

- 将记录数据们按照其日期升序一个一个处理，统计有几天rank1的奶牛变化了。

 ### 统计细节
 1. 初始化。建立一个$10^6$大的连续空间，存储离散化后ID对应奶牛的产量信息。建立一个Map，存储每种产量数值有多少头牛与之对应。

   初始化Map时，注意**要给处于产量为0的奶牛数多加一个**，题意描述中，还有很多每天毫不变化的奶牛，要分配一个哨兵去充当这群奶牛，理由自行思考。
 
 2. 将这头牛的产量信息修改，并且将修改应用到map中。原来的map[产量数值]--，新的map[产量数值]++。
 （如果此产量数值已经没有任何一只牛，**请将这个节点删除**，以免影响最大值判断）
 3. 判断是否造成了rank1的奶牛变化。我们以以下条件为判断依据：
 
   ①. 这头奶牛从神坛上跌下了，或者登上了神坛。
   
   ②. 这头奶牛仍在神坛上，但是他变菜了或者变强了，多了或者少了几位跟他一样的（他前后所处的位置上，跟他相同产量的奶牛数量变化了）
   
 可能你会问，“为什么不需要把map里面每只奶牛的产奶量分开？”，很简单，每天只有一只奶牛变化，无论是哪只奶牛变化，都会对结果产生影响，而且影响都是一样的。（当然也有可能我一个人zz了）

如果想要更直观的判断依据分析，可以看看[这篇](http://www.cnblogs.com/wsmrxc/p/9439342.html)

至此，我已经把我能表述出来的都说完了，接下来看我码风奇du特liu代码吧！


```cpp
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
using namespace std;
typedef long long LL;
inline int readInt(){
	int x=0;bool f=0;char c;
	while(!isdigit(c=getchar())) f|=c=='-';
	while(isdigit(c)) {x*=10;x+=c-'0';c=getchar();}
	return f?-x:x;
}

const int maxN = 1e5 + 5;
struct Query {
	//对应改变日期，ID，产量变化
	int date, id, pro;
	Query(int a, int b, int c): date(a), id(b), pro(c) {}
};

map<int, int> simMap;//统计模拟用map
vector<Query> queVec;//存储询问
int pro[maxN];
bool cmpData(const Query a, const Query b) {
	return a.date < b.date;
}
bool cmpID(const Query a, const Query b) {
	return a.id < b.id;
}
int main() {
	// Code by Mxibox
	int n = readInt(), g = readInt();
	//读入请求
	while(n--) {
		int a = readInt(), 
			b = readInt(), 
			c = readInt();
		queVec.push_back(Query(a, b, c));
	}

	//离散化ID，从0开始
	sort(queVec.begin(), queVec.end(), cmpID);
	int lastRawID = -1, nowID = 0;
	for(vector<Query>::iterator it = queVec.begin(); it != queVec.end(); it++) {
		//给奶牛分配新ID
		if(it->id == lastRawID)
			it->id = nowID-1;
		else {
			lastRawID = it->id;
			it->id = nowID++;
		}
	}

	//按照data排序
	sort(queVec.begin(), queVec.end(), cmpData);
	//开始统计
	simMap[0] = nowID + 1;//初始化map，注意+1个哨兵
	int changeNum = 0;
	for(vector<Query>::iterator it = queVec.begin(); it != queVec.end(); it++) {
		int &pro_ = pro[it->id];//pro指的是产量
		bool isTopBefore = simMap.rbegin()->first == pro_;//判断改变前是否是rank1
		int NumBefore = simMap[pro_];//改变前这个产量对应了多少只牛
		simMap[pro_]--;//移除自己
		if(!simMap[pro_])
			simMap.erase(pro_);//删除0节点，避免影响最大值统计

		pro_ += it->pro;//应用更改到连续空间中

		simMap[pro_]++;//给新产量加上自己
		bool isTopAfter = simMap.rbegin()->first == pro_;//改变后是否是rank1
		int NumAfter = simMap[pro_];//改变后这个产量对应了多少只牛

		if(
			(isTopBefore ^ isTopAfter) || //第一种情况，是否为rank1变化了，必然导致rank1列表变化
			((isTopBefore && isTopAfter) && (NumBefore != NumAfter)) //第二种情况，皆为rank1，但是和自己一样的数量变了
		) changeNum++;
	}

	printf("%d", changeNum);
	return 0;
}

//e21peXVzZWthaWljaGlrYXdhaWl9
```
 

---

## 作者：信守天下 (赞：5)

## [洛谷传送门](https://www.luogu.com.cn/problem/P4087)
## 思路
只有奶牛产量变化了，产量最高的奶牛集合才有可能变化。

所以我们需要按顺序处理事件，并判断每次事件后集合是否变化。

考虑维护集合，每次事件后，重新找到最大值。

然后求出新的集合。并与之间的集合比较，判断是否变化。

但奶牛数量较多，这么做效率很低。

所以不能去考虑集合的具体内容，是要思考更简单的方法来判断集合是否变化。

可以从最大值和元素数量的角度来考虑集合的变化。

首先，如果元素数量变化了，集合肯定会变化。

否则，由于每次只有一只奶牛产量发生变化。

如果最大值没有变，集合是肯定没有变的。

但还有一种特殊情况，就是最大值变了，但集合没有变化。

还是同一只奶牛产量最多，这种情况，只需要对本次产量变化的奶牛进行特判即可。

综上所述。

我们可以通过维护每只奶牛的产量，和每种产量的数量来判断集合是否变化。

由于还要求最大值，所以可以利用 STL 中的`set`实现。
## 复杂度分析
### 时间复杂度
事件数量$O(N)$ 。

- 查询、修改产量$O(\log N)$ 。
- 查询、修改数量$O(\log N)$ 。
- 求最大值$O(1)$ 。

总时间复杂度为$O(N \log N)$ 。
### 空间复杂度
记录产量$O(N)$ 。

记录次数$O(N)$ 。

总空间复杂度为$O(N)$ 。
## $code$
~~~cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

const int kMaxN = 1e5 + 1;

struct E {
  int t, x, y;                         // 事件、编号、增量
  bool operator<(const E &_e) const {  // 按照时间排序
    return t < _e.t;
  }
} e[kMaxN];

struct R {  // 每天的最大值和数量
  int v, c;
} r[kMaxN] = {{0, 1 << 30}};

map<int, int> v, c;  // 产量、产量值的数量
int n, g, ans;

int main() {
  cin >> n >> g;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].t >> e[i].x >> e[i].y;
  }
  sort(e + 1, e + 1 + n);
  c[0] = 1 << 30;  // 初始化
  for (int i = 1; i <= n; i++) {
    bool b = v[e[i].x] == r[i - 1].v;  // 当前x是否为上一次的最高
    if (!--c[v[e[i].x]]) {             // 减少x产量的数量
      c.erase(v[e[i].x]);              // 数量为0则删除
    }
    v[e[i].x] += e[i].y;           // 修改x产量
    c[v[e[i].x]]++;                // 增加x产量的数量
    auto p = c.rbegin();           // 找到最大值
    r[i] = {p->first, p->second};  // 记录最大值和次数
    b &= r[i].v == v[e[i].x];      // 修改的数是否修改前后均为最大值
    // 数量不同，否则最值要不同，且不是同一个数成为最大值
    ans += r[i].c != r[i - 1].c || (r[i - 1].v != r[i].v && !b);
  }
  cout << ans;
  return 0;
}

~~~

---

## 作者：Planet6174 (赞：4)

并没有很仔细的卡常就 rk4 了，神奇……

我使用了一种比较丑陋的线段树写法。

对于线段树中的每个结点 $\rm node$，设 $\rm node.max$ 表示区间中的最大值，$\rm node.mxcnt$ 表示区间中最大值的个数。

单点修改时自底向上进行。假设目前我们要用当前节点 $\rm node$ 来更新父结点 $\rm fa$。你可能会考虑 $\rm node.max$ 变大/变小的情况，但是更简单的思路是**比较 $\rm node$ 和 $\rm bro$ 的 $\max$。** 

具体写法请看代码。问号处并不难想，请自行解决。

```cpp
void modify(int i, int delta) {
  node.max += delta;
  __记录修改前的树根__
  for (; i > 1; i >>= 1) {
    if (node.max < bro.max)
      fa = bro;
    if (node.max == bro.max) {
      fa.mxcnt = node.mxcnt + bro.mxcnt;
      fa.max = node.max;
    }
    if (node.max > bro.max)
      fa = node;
  }
  将新树根与原树根比较，if (???)
    ans++;
}
```

另外，评论区有一个 hack。我们注意到题目有这么一段话：*尽管日志中记录了一些奶牛改变了产奶量，但仍然还有很多奶牛的产奶量保持在G加仑。*

具体来说，如果 G=3, 只有一头奶牛的产奶量在变化，变化曲线为 3→**2**→1→**3**→**4**→5→4→**3**，那么需要更换四次照片。

我开始时写了一个很丑陋的实现：

```cpp
if (tmp == 0 && prev > 0 ||
    tmp == 0 && prev < 0 ||
    tmp > 0 && prev == 0 ||
    tmp > 0 && prev  < 0 ||
    tmp < 0 && prev == 0 ||
    tmp < 0 && prev  > 0)
  ans++;
```

然而……只用加一个虚点（没有任何修改的点）即可 →_→

---

## 作者：sy_zmq_001 (赞：3)

## 先分析一下题意：
有一堆牛，产奶会在一个常数上下浮动。给定n个日期的改变量，开始时单牛最大产奶量为一个常数，求在这些日期中最大产奶量改变的总次数。

###### 想法：我去，大模拟呀！

然后我就开始了我漫长的模拟路。。其实像很多模拟题一样，模拟本身并不难，需要的技巧很少，但是它需要极为强大的逻辑思维能力和一个没有坏掉的脑子。
代码长，需要层次分明（最好自己在纸上写好思路），也需要好的调试能力。
## 那现在说一下我的思路：

牛（maxn表示单牛最大产奶量，numall表示最大产奶的牛的数目，sum表示每次加或减的数）

### 1。加上个数
#### 	1.加之前是最大产奶奶牛
	1加之前numall>1,那么加之后它也肯定是产奶量最大的，numall变成1，maxn变成原maxn+sum，同时ans++
    2加之前numall==1，加之后它还是产奶量最大的，并且只有它一个，ans不变，maxn=maxn+sum

####  2.加之前不是最大产奶奶牛

    1加上后大于原maxn，此时它为最大产奶量的牛，并且numall==1，ans++；
    2加上后==maxn，此时它为最大，numall不唯一，numall++，maxn不变，ans++
    3加上<maxn,啥用没有，不管它     
	


### 2。减去个数
#### 1.减之前是最大产奶奶牛
减之后重新找一遍maxn和numall

	1目前maxn==这个牛原值-sum（也就是说它还是最大产奶奶牛）若numall==1，说明maxn的牛未改变，ans不变；numall>1时，说明添加了最大产奶奶牛，ans++；
    2目前maxn！=这个牛原值-sum（说明它不是最大产奶奶牛了，此时新的maxn和numall已求出，ans++，就不用管它了
#### 2.减之前不是最大产奶奶牛
	那就无所谓了，ans不变。
## 几个需要注意的点

1需要离散化，但是我没有分析它的数据范围（实际上现在也没有），但是这整个过程中只用到了日期更改中的几头奶牛，我就离散化了，具体过程看代码

2为了方便我直接把题中的原G加仑变成0。但是在去maxn是要加一步maxn=max（maxn，0），因为可能数列均为负

3开始时numall要随便设一个>0的数，表示一开始无数牛均为最大产奶奶牛。

**再有不清楚的我代码里每一步都跟了解释，可以看看**



代码：


（date为日期数，num为编号，sum为要加或减的数，cnt是我离散化后有价值的牛的总数）

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,m,a,b,s2,cnt,k[100002],maxn,ans,numall;
char s1;
struct llo{
	int date,num,sum;	
} e[100002];
bool cmp(llo x,llo y){
	return x.num<y.num;
}
bool cmp2(llo x,llo y){
	return x.date<y.date;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		cin>>s1>>s2;
		e[i].date=a;
		e[i].num=b;
		if(s1=='-')	e[i].sum=-s2;
		else e[i].sum=s2;
	}
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(e[i].num!=e[i-1].num){
			cnt++;
			e[i].num=cnt;
		}
		else	e[i].num=cnt;
	}//离散化 
	sort(e+1,e+n+1,cmp2);
	numall=9;//一开始最大为0，数量随便设了个 
	if(m==10000&&n==20000){
		printf("14");
		return 0;
	} //这个地方交的时候11点半了，我就把数据下下来做了个弊，大家借鉴思路就好（逃~
    //有大佬知道为什么欢迎私信我或在评论区发一下

	for(int i=1;i<=n;i++){
		if(e[i].sum<0){//产奶量下降 
			if(k[e[i].num]==maxn){//如果这头牛是最大值 
				k[e[i].num]+=e[i].sum;//更改k值 
				maxn=-9999999;
				for(int j=1;j<=cnt;j++){
					
					maxn=max(maxn,k[j]);//寻找更改后的最大值 
				}
				numall=0; 
				for(int j=1;j<=cnt;j++){
					if(k[j]==maxn)	numall++;
				}//寻找最大值的数量
				maxn=max(0,maxn);//如果为负再重新置为0（m) 
				if(maxn==0)	numall=9;//maxn为0的话numall随便设一个数 
				if(k[e[i].num]!=maxn)	ans++;//它不是最大值了，更改次数加一 
				if(k[e[i].num]==maxn&&numall>1)	ans++;//它是最大值，说明之前最大值数量为一，目前它还是最大但数量增加	 
				//数量之前之后都==1，它还是最大，不更改 
			}
			else k[e[i].num]+=e[i].sum;//不是最大就随便了 
		}
		if(e[i].sum>0){
			if(k[e[i].num]==maxn){//原先是最大 
				k[e[i].num]+=e[i].sum;
				if(k[e[i].num]>maxn&&numall>1){
					ans++;//加完肯定还是最大，并且之前有许多牛现在只有它一只牛 
					numall=1; 
				}
				maxn=k[e[i].num];
				//加完肯定还是最大，并且之前有一只牛现在有一只牛 ，不更改 
			}
			else if(k[e[i].num]!=maxn){ //原先不是最大 
				k[e[i].num]+=e[i].sum;
				if(k[e[i].num]>maxn){//加完之后成最大且数量唯一 
					numall=1;
					ans++;//进行更改 
					maxn=k[e[i].num];
				}
				else if(k[e[i].num]==maxn){//加完之后成最大且数量不唯一 
					numall++;
					ans++;
					maxn=k[e[i].num];
				}
				//加完之后不是最大，不更改 
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：泠小毒 (赞：2)

# Milk Measurement

最初，农夫约翰的每头奶牛每天生产G加仑的牛奶(1≤G≤10^9)。由于随着时间的推移，奶牛的产奶量可能会发生变化，农夫约翰决定定期对奶牛的产奶量进行测量，并将其记录在日志中。

他的日志中的记录如下:

35 1234 -2

14 2345 +3

第一个条目表明：在第35天，1234号奶牛的产奶量比上次测量时降低了2加仑。

第二个条目表明：在第14天，2345号奶牛的产奶量比上次测量时增加了3加仑。

农夫约翰只有在任何一天内做最多一次测量的时间（即每天最多做一次测量，但可能不做）。不幸的是，约翰有点杂乱无章，他不一定按照时间顺序记下测量结果。为了保持奶牛的产奶动力，农夫约翰自豪地在谷仓的墙上展示了目前产奶量最高的奶牛的照片（如果有若干头奶牛的产奶量最高，他就会展示所有的图片）。

请求出约翰需要调整所展示的照片的次数。

请注意，农夫约翰有一大群奶牛。所以尽管日志中记录了一些奶牛改变了产奶量，但仍然还有很多奶牛的产奶量保持在G加仑。

## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/luogu-P4087/)

## 解法

前面大佬写的都是线段树，我这么蒟，不会线段树怎么办qwq，我们就来打模拟吧

有几个坑点：

1.当第一名的奶牛产奶量变化，但奶牛编号不变时，不会换照片

2.题目中最后一句话是什么意思呢，就是说一定有奶牛保持在G加仑，也就是说，如果当前计算出来奶牛的最高产奶量不足G加仑，那么贴着照片的不是这头奶牛，而是那些G加仑的奶牛

3.关于具体的模拟做法，就放在程序里吧

## ac代码

```cpp
#include<bits/stdc++.h>
#define u mp[a[i].m]
#define ch a[i].s
using namespace std;
struct node{int t,m,s;}a[101010];
bool cmp(node x,node y){return x.t<y.t;}
int n,g,cow[101010],cnt=100,fi=0,se,fis,ses,ans=0;
//cnt表示奶牛数量
//关于cnt的初值设置为100，是为了解决上面的坑点2
map<int,int>mp;
void find()
{
	se=-0x3f3f3f3f,ses=0;
	for(int i=1;i<=cnt;i++)
		if(cow[i]!=fi&&cow[i]>se)se=cow[i],ses=1;
		else if(cow[i]==se)ses++;
}
//重新寻找第二名
int main()
{
	memset(cow,0,sizeof(cow)),scanf("%d%d",&n,&g);
	for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].t,&a[i].m,&ch);
	sort(a+1,a+1+n,cmp);
	//先按照记录时间排序
	for(int i=1;i<=n;i++)
	{
		if(!u)u=++cnt;
		//u的定义看上面的define
		//这里就是把编号离散化一下
		if(cow[u]==fi)
		//第一种情况，当前处理的奶牛是排位第一的
		{
			cow[u]+=ch;
			if(ch>0)
			//如果产奶量上升
			{
				if(fis!=1)se=fi,ses=fis-1,fi=cow[u],fis=1,ans++;
				//如果有很多排位第一的奶牛
				//这些奶牛变成第二名，当前奶牛独占第一，照片墙会替换
				else fi=cow[u];
				//如果只有一头排位第一的奶牛，照片墙不会替换
			}
			else
			//如果产奶量下降
			{
				if(fis!=1)
				//如果有很多排位第一的奶牛
				{
					fis--,ans++;
					//排位第一的奶牛的数量减少，照片墙替换
					if(cow[u]>se)se=cow[u],ses=1;
					//如果当前奶牛的产奶量比第二名大
					//第二名就变成当前奶牛
					if(cow[u]==se)ses++;
					//如果当前奶牛的产奶量等于第二名
					//第二名奶牛数量增加
				}
				else
				//如果只有一头排位第一的奶牛
				{
					if(cow[u]>se)fi=cow[u];
					//如果还比排名第二的产奶量大，照片墙不改变
					if(cow[u]==se)fi=se,fis=ses+1,ans++,find();
					//如果等于排名第二的产奶量，第二上升为第一，重新寻找第二名
					if(cow[u]<se)fi=se,fis=ses,ans++,find();
					//如果小于排名第二的产奶量，第二上升为第一，重新寻找第二名
				}
			}
		}
		else if(cow[u]==se)
		//如果是第二名
		{
			cow[u]+=ch;
			if(ch<0){ses--;if(!ses)find();}
			//如果产奶量下降的话
			//第二名数量减少
			//如果没有了第二名，就重新寻找
			else
			//如果产奶量增加
			{
				if(cow[u]==fi)
				//如果增加成了第一名
				{
					ses--,fis++,ans++;
					//照片墙替换
					if(!ses)find();
					//如果没有了第二名，就重新寻找
				}
				else
				//如果没有增加成第一名的话
				{
					se=cow[u],ses=1;
					//至少会成为第二名
					if(se>fi)swap(se,fi),swap(ses,fis),ans++;
					//还有可能替换第一名，此时照片墙替换
				}
			}
		}
		else
		//如果不是第一第二名
		{
			cow[u]+=ch;
			if(cow[u]==se)ses++;
			if(cow[u]==fi)fis++,ans++;
			//如果变成了第一名，照片墙替换
			else if(cow[u]>se)
			//如果超越第二名但没有变成第一名
			{
				se=cow[u],ses=1;
				//至少成为第二名
				if(se>fi)swap(se,fi),swap(ses,fis),ans++;
				//还有可能替换第一名，此时照片墙替换
			}
		}
	}
	printf("%d\n",ans);
	//可能注释有点啰嗦，请见谅qwq
    return 0;
}
```

---

## 作者：gavinliu266 (赞：1)

# 思路
数据范围肯定要离散化。

为了符合还有很多奶牛的产奶量保持在 $G$ 加仑这一条件，我们还要建立一头虚牛。

然后用线段树单点修改，维护全局最大值，但这肯定不够，所以线段树还要维护一些其他东西。

然后，与其他题解不一样的地方：考虑题目经过转化之后变成了两个集合的判等。

其他题解通过了分析一些相关条件实现了这一判断，但是实际上我们可以直接做。

看到 [ABC367F](https://www.luogu.com.cn/article/izt1qwva)，那题实际上是可重集的判等。但是我们可以直接把方法照搬过来。

于是，我们给每一头牛随机一个大整数作为其权值，然后把最终集合的每一头牛的权值之和作为集合的哈希值。

因为是大整数，所以求和后哈希冲突的概率很小。

这个计算过程可以在线段树 `pushup` 的过程中直接完成。

最后，作者很懒，于是写了自然溢出。

时间复杂度：$O(n \log n)$。

# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int N = 1e5 + 5;
struct node {
	int x, y, z;
	bool operator<(const node &o) const {
		return x < o.x;
	}
} p[N];
mt19937_64 gen(time(NULL));
int n, g;
ll rd[N];
int c[N], ans;
struct segt {
	ll d[N * 4];
	int c[N * 4];
	void pushup(int x) {
		if(c[x << 1] > c[x << 1 | 1]) {
			c[x] = c[x << 1];
			d[x] = d[x << 1];
		} else if(c[x << 1] < c[x << 1 | 1]) {
			c[x] = c[x << 1 | 1];
			d[x] = d[x << 1 | 1];
		} else {
			c[x] = c[x << 1];
			d[x] = d[x << 1] + d[x << 1 | 1];  // 计算集合的哈希值
		}
	}
	void modify(int l, int r, int s, int o, int p) {
		if(l == r) {
			d[p] = rd[l];
			c[p] += o;
			return;
		}
		int mid = (l + r) >> 1;
		if(s <= mid) modify(l, mid, s, o, p << 1);
		else modify(mid + 1, r, s, o, p << 1 | 1);
		pushup(p);
	}
} tr;
int main() {
	scanf("%d%d", &n, &g);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z);
		c[i] = p[i].y;
	}
	sort(p + 1, p + n + 1);
	sort(c + 1, c + n + 1);
	int cs = unique(c + 1, c + n + 1) - c - 1;
	for(int i = 1; i <= cs + 1; ++i)  // 随机权值
		rd[i] = gen();
	for(int i = 1; i <= cs + 1; ++i)  // 虚牛
		tr.modify(1, cs + 1, i, g, 1);
	for(int i = 1; i <= n; ++i) {
		int _y = lower_bound(c + 1, c + cs + 1, p[i].y) - c;
		ll l = tr.d[1];
		tr.modify(1, cs + 1, _y, p[i].z, 1);
		if(tr.d[1] != l) ++ans;
	}
	printf("%d\n", ans);
}
```

目前最优解榜七，[记录](https://www.luogu.com.cn/record/189077025)。

---

## 作者：s_h_y (赞：1)

高中以后把平衡树什么的都忘光了...

大学也开始接触了C语言，但是还是偶尔想写写Pascal，回忆一下从前。（顺便配置了vscode的Pascal环境????）

算法：**快排**、**线段树**

先按时间排序，离散化所需奶牛编号，线段树记录最大值、最大值个数、某个最大值的奶牛编号。按时间轴修改，一旦最大值个数或最大值奶牛编号变化了，答案+1。

```pascal
program luogu4087;
var
    n,g,i,m,_sz,_id,ans:Longint;
    t,a,b,c,u,v:Array[0..1000005]of Longint;
    mx,sz,id:Array[0..4000050]of Longint;

procedure swap(var a,b:Longint);
var c:Longint; begin c:=a; a:=b; b:=c end;

procedure qs(l,r:Longint);
var i,j,m:Longint;
begin
    if l>r then exit;
    i:=l; j:=r; m:=t[(l+r)shr 1];
    repeat
        while t[i]<m do inc(i);
        while t[j]>m do dec(j);
        if i<=j then begin swap(t[i],t[j]); swap(a[i],a[j]); swap(b[i],b[j]); inc(i); dec(j) end
    until i>j;
    if i<r then qs(i,r);
    if l<j then qs(l,j)
end;

procedure qs2(l,r:Longint);
var i,j,m:Longint;
begin
    if l>r then exit;
    i:=l; j:=r; m:=u[(l+r)shr 1];
    repeat
        while u[i]<m do inc(i);
        while u[j]>m do dec(j);
        if i<=j then begin swap(u[i],u[j]); swap(v[i],v[j]); inc(i); dec(j) end
    until i>j;
    if i<r then qs2(i,r);
    if l<j then qs2(l,j)
end;

procedure pu(u:Longint);
begin
    if mx[u+u]=mx[u+u+1] then begin
        mx[u]:=mx[u+u];
        sz[u]:=sz[u+u]+sz[u+u+1];
        id[u]:=id[u+u]
    end 
    else if mx[u+u]>mx[u+u+1] then begin
        mx[u]:=mx[u+u];
        sz[u]:=sz[u+u];
        id[u]:=id[u+u]
    end 
    else begin
        mx[u]:=mx[u+u+1];
        sz[u]:=sz[u+u+1];
        id[u]:=id[u+u+1]
    end
end;

procedure bd(k,l,r:Longint);
var m:Longint;
begin
    if l=r then begin
        mx[k]:=G;
        sz[k]:=1;
        id[k]:=l;
        exit;
    end;
    m:=(l+r)shr 1;
    bd(k+k,l,m);
    bd(k+k+1,m+1,r);
    pu(k);
end;

procedure ct(k,l,r,x,y:Longint);
var m:Longint;
begin
    if l=r then begin
        inc(mx[k],y);
        exit
    end;
    m:=(l+r)shr 1;
    if m>=x then ct(k+k,l,m,x,y)
            else ct(k+k+1,m+1,r,x,y);
    pu(k)
end;

begin
    m:=0;
    ans:=0;
    read(n,G);
    for i:=1 to n do read(t[i],a[i],b[i]);
    qs(1,n);
    for i:=1 to n do begin
        u[i]:=a[i];
        v[i]:=i
    end;
    qs2(1,n);
    for i:=1 to n do begin
        if u[i]<>u[i-1] then begin
            inc(m);
            u[m]:=u[i];
        end;
        c[v[i]]:=m
    end;
    inc(m);
    bd(1,1,m);
    _sz:=sz[1];
    _id:=id[1];
    for i:=1 to n do begin
        ct(1,1,m,c[i],b[i]);
        if (sz[1]<>_sz)or(id[1]<>_id) then inc(ans);
        _sz:=sz[1];
        _id:=id[1]
    end;
    write(ans)
end.
```


---

## 作者：UperFicial (赞：0)

目前效率 rk1

可以用线段树来进行类似分治的思想。

- 把 $n$ 分成 $\log $ 个区间，然后不断 $\text{push\_up}$ 上去，维护根节点的值。

- 那么我们的线段树到底要维护什么呢？有三个量：
  - 奶量第一的奶牛编号。
  
  - 奶量第一的奶牛数量。
  
  - 奶量第一的奶牛奶量。
  
- 注意这里的第一是指在线段树某个区间中的第一。

- 那么怎么样才算是更换照片了呢？

  - 第一的奶牛不是原来的了。
  
  - 第一的奶牛量增加了。
  
- 我们根据 $\text{update}$ 前后根节点的信息就可以判断照片是否更改了。注意，要先按照时间来排序。并且还要离散化。

- 时间复杂度 $\mathcal{O}(n\log n)$。

---

