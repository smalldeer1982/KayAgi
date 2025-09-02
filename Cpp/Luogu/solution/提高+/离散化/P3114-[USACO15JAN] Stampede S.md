# [USACO15JAN] Stampede S

## 题目描述

FJ 的 $N$ 头奶牛（$1 \leq N \leq 50,000$）看似在农场前的路上狂奔，实际上它们正在进行一场赛跑。

从上方俯视，每头牛在时间 $t = 0$ 时被表示为一个单位长度的水平线段，其左端点坐标为 $(x, y)$。例如，$(-3, 6)$ 表示一头在 $t = 0$ 时从 $(-3, 6)$ 延伸到 $(-2, 6)$ 的奶牛。每头牛以一定速度向右（$+x$ 方向）移动，该速度由移动 1 单位距离所需的整数时间 $r$ 描述。

FJ 并不满意他的奶牛在外赛跑而不在牛棚产奶。他计划在比赛结束后训斥参赛的奶牛。为了确定哪些奶牛参赛，FJ 站在 $(0, 0)$ 处并沿 $+y$ 方向的射线观察。当一头牛在某个时刻成为这条射线上首个可见的牛时，FJ 就会看到它。如果一头牛在穿过 FJ 视线期间始终被其他牛"挡住"，则她不可见。

请计算 FJ 在整个比赛过程中能看到的奶牛数量。

## 说明/提示

FJ 可以看到牛 1 和 2，但看不到牛 3。

## 样例 #1

### 输入

```
3 
-2 1 3 
-3 2 3 
-5 100 1 
```

### 输出

```
2 
```

# 题解

## 作者：☯☯枫☯☯ (赞：10)

[传送门](https://www.luogu.com.cn/problem/P3114)

这里提供一种比较暴力的做法。

**算法分析：离散化+区间覆盖。**

根据题意，Farmer John 能看到奶牛的时候奶牛恰好经过 $y$ 轴。显然，奶牛身体某部位在 $y$ 轴的时间是一个区间，可以考虑对时间轴进行**区间覆盖**，即将时间轴上 $st_i$ 到 $ed_i$ 这一段区间标记为 $i$，表示这段区间能看见的是第 $i$ 头奶牛。但是题目中数据范围很大，实际上并不能开那么大的数组，因此我们需要对时间点进行**离散化**。

---

**细节提示：**

- 覆盖：当某一时间点已被覆盖，但新来的奶牛的 $y$ 值更小时，需要更新原先的覆盖。

- 离散化：离散化时，不能使用左闭右闭的形式，应当使用左闭右开，否则容易引起冲突（先排序再离散化！）。

比如说：第一只奶牛占据的时间是 \[1,2],$y=1$，第二只是 \[3,4],$y=1$，第三只是 \[2,3]，$y=2$。显然的，前两只奶牛占据了 \[1,4] 这个区间，第三只奶牛所在区间已经被覆盖，并且第三只的 $y$ 值大于前两只（被挡住了）。但实际上，在第二秒结束时，第一只奶牛已经离开，第三只奶牛可以被看到。这样看来，左闭右闭的区间会引起冲突。因此，我们应当设置左闭右开区间，这样在覆盖时就不会引起冲突。

上代码：

```cpp
#include<bits/stdc++.h>
#define rd(n) scanf("%lld",&n);
#define F(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
const int N=4e5+10;
long long n,p,v,x;
long long st[N],ed[N],t[N];
int c[N],d[N],y[N];
int main() {
    rd(n)
    F(i,1,n) {
        rd(x)rd(y[i])rd(v)
        x++;
        x=-x;//将坐标转化为距离 
        st[i]=x*v;
        ed[i]=st[i]+v-1;
        t[++p]=st[i],t[++p]=ed[i];
        t[++p]=ed[i]+1;//左闭右开
    }
    memset(c,0x3f,sizeof(c));
    sort(t+1,t+p+1);//先排序再离散化 
    long long cnt=unique(t+1,t+p+1)-t-1;
    F(i,1,n) {
        st[i]=lower_bound(t+1,t+cnt+1,st[i])-t;//离散化 
        ed[i]=lower_bound(t+1,t+cnt+1,ed[i])-t;
        F(j,st[i],ed[i]){//暴力覆盖 
            if(c[j]>y[i]){//如果覆盖这一段时间的奶牛的 y 值大于现在的奶牛，就更新 
                c[j]=y[i];//c 模拟时间轴上奶牛的 y 值 
                d[j]=i;//d 记录时间轴上的奶牛编号 
            }
        }
    }
    int ans=0;
    F(i,1,n) {
        F(j,st[i],ed[i]) {
            if(d[j]==i){
                ans++;//如果第 i 头奶牛经过 y 轴的时间内能被看到，答案+1 
                break;
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/48306556)

欢迎交流讨论，请点个赞哦~

---

## 作者：Expecto (赞：7)

扫描线大法好啊！

0. 本蒟蒻想了好久。。。这题可以把牛的开始和结束时间算出来，结束时间的y取负的，排序一下，从左往右扫，如果y>0就加入active集合，如果＜0就踢掉。每次取y最小的加入集合seen。

```cpp
0. #include<bits/stdc++.h>
0. using namespace std;
0. int main(){
0. int n;
0. scanf("%d",&n);
0. vector<pair<int,int> > events;
0. for (int i=0;i<n;i++){
0. int x,y,r;
0. scanf("%d%d%d",&x,&y,&r);
0. x*=-r;
0. events.push_back(make_pair(x-r,y));
0. events.push_back(make_pair(x,-y));
0. }
0. sort(events.begin(),events.end());
0. set<int> seen;
0. set<int> active;
0. for (int i=0;i<events.size();){
0. int j;
0. for (j=i;j<events.size() && events[i].first==events[j].first;j++){
0. int y=events[j].second;
0. if (y>0) active.insert(y);
0. else active.erase(-y);
0. }
0. if (!active.empty())
0. seen.insert(*active.begin());
0. i=j;
0. }
0. cout<<seen.size();
0. return 0;
0. }
```

---

## 作者：Na2PtCl6 (赞：5)

## 分析题目
我们可以把奶牛经过原点的时间段理解为一条线段，对线段高度按从低到高进行区间覆盖。但题目中的数值很大，显然不能直接维护区间。

我们考虑对线段的端点数值进行离散化，用线段端点 **在所有端点中的相对的大小** 即排名代替线段端点数值的绝对大小。

下面是重中之重： **不管线段端点的大小是相对的还是绝对的，都不能用闭区间** 。

乍一看，其他题解里的左闭右开区间和闭区间好像也没啥差别啊，下面这组数据就会让你彻底明白。

\# input
```
4
-10 6 1
-6 7 2
-5 6 3
-10 8 4
```

\# output
```
4
```

（以上数据来自 [这篇题解](https://www.luogu.com.cn/blog/ueettttujzzr/p3114-usaco15jan-cai-ta-stampede)）

对线段离散化，然后按高度排序可得以下的线段

$[1,2];$

$[3,4];$

$[2,3];$

$[5,6].$

我们可以发现， $[1,2]$ 和 $[3,4]$ 会被先覆盖，接下来，线段树检测到 $[2,3]$ 已经被覆盖！线段的端点虽然是整数，意义却是实数，只有 $2,3$ 这两个数轴上的点被覆盖了，但中间还有未被覆盖的部分。

所以为了避免这种精度的误差，我们可以用左闭右开区间来解决这个问题。

还有一种方法就是把区间端点全部乘上同一个 $\ge 2$ 的正整数，对于此题而言，乘以 $2$ 就足够了。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100004;
char f,ch,tree[maxn<<3],tag[maxn<<3];
int n,res,x[maxn],s[maxn],r[maxn],sc[maxn<<1];
struct cow{
	int begin,end,y;
	bool operator < (const cow &comp) const{
		return y<comp.y;
	}
}c[maxn];

const int _min(const int &a,const int &b){ return a<b?a:b;}

inline void push_down(int node){
	int t=tag[node],lnode=node<<1,rnode=node<<1|1;
	if(t){
		tag[lnode]=t,tag[rnode]=t;
		tree[lnode]=t,tree[rnode]=t;
		tag[node]=0;
	}
}

void update(int l,int r,int node,int start,int end,int v){
	if(start<=l&&r<=end){
		tag[node]=v;
		tree[node]=v;
		return ;
	}
	push_down(node);
	int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
	if(start<=mid)
		update(l,mid,lnode,start,end,v);
	if(end>mid)
		update(mid+1,r,rnode,start,end,v);
	tree[node]=_min(tree[lnode],tree[rnode]);
}

int query(int l,int r,int node,int start,int end){
	if(start<=l&&r<=end)
		return tree[node];
	push_down(node);
	int mid=(l+r)>>1,lnode=node<<1,rnode=node<<1|1;
	int MIN=2;
	if(start<=mid)
		MIN=_min(MIN,query(l,mid,lnode,start,end));
	if(end>mid)
		MIN=_min(MIN,query(mid+1,r,rnode,start,end));
	return MIN;	
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d %d",&x[i],&c[i].y,&r[i]);
		//离散化的数组随便放
		sc[i]=(-x[i]-1)*r[i];   
		sc[i+n]=-x[i]*r[i];
	}
	sort(sc+1,sc+n*2+1);
	int sz=unique(sc+1,sc+n*2+1)-sc-1;  //去重 
	for(int i=1;i<=n;i++){
		//找出相对值 
		c[i].begin=(lower_bound(sc+1,sc+sz+1,(-x[i]-1)*r[i])-sc)<<1;
		c[i].end=(lower_bound(sc+1,sc+sz+1,-x[i]*r[i])-sc)<<1;
	}
	sort(c+1,c+n+1);  //按高度排序 
	sz<<=1;
	for(int i=1;i<=n;i++){
		//如果区间没有完全被覆盖就继续覆盖,结果加一 
		res+=(!query(1,sz,1,c[i].begin,c[i].end))?1:0;
		update(1,sz,1,c[i].begin,c[i].end,1);
	}
	printf("%d",res);
	return 0;
}
```

---

## 作者：曹老师 (赞：4)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco15jan-stamp.html)

~~难道只有我写线段树吗？？？~~

对于每一头牛，我们能够确定这头牛在哪个时间段内能被看到，而这些时间段又是一个又一个的区间，考虑线段树。首先可以发现，这样求出来的区间可能非常离散，而且我们需要的只是一个相对的大小，所以再考虑离散化，根据离散化后数组的大小来建一棵线段树。建树的时候要用动态开点，因为我们什么信息都还不知道，线段树维护左右端点和是否被访问过就好了。然后我们再把牛按照纵坐标从小到大排序，每一次拿出未拿出来的纵坐标最小的一头牛来，在线段树上执行查询操作，查询完了之后直接要覆盖上去。有一个处理的小细节，就是区间不能像普通的线段树一样是一个闭区间，而是用左闭右开，这样可以处理区间边界。

还要注意一个地方呢，（这个地方困扰了我很长时间），我本来以为，懒标记只是下传，覆盖的时候直接覆盖上，用不上上传吧。其实不是这样的，上传可以省时间，而且不会让你做错哈哈哈。查询的时候有点小细节，不过很小很小，应该都能注意到（毕竟我这个蒟蒻都注意到了）。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cmath> 
#include<algorithm> 
using namespace std;

struct Cow {
    int x , y , val;
    bool operator < (const Cow &a) const {
        return y < a.y;
    }
};
Cow cow[50005];
struct Node {
    int l , r;
};
Node node[50005];
struct SegTree {
    int l , r , vis;
};
SegTree seg[4*100005];
int n , lsh[100005] , top = 0 , cnt , ans;

int myabs(int x) {
    return x<0?(-x):x;
}

void build(int num , int l , int r) {
    seg[num].l = l;
    seg[num].r = r;
    if(l == r)
        return ;
    int mid = (l+r)>>1;
    build(num<<1 , l , mid);
    build(num<<1|1 , mid+1 , r);
}

void pushdown(int num) {
    if(seg[num].vis) {
        seg[num<<1].vis = seg[num<<1|1].vis = seg[num].vis;
        seg[num].vis = 0;
    }
}

int query(int num , int l , int r) {
    if(seg[num].l >= l && seg[num].r <= r) {
        if(seg[num].vis)
            return 1;
        return 0;
    }
    pushdown(num);
    int mid = (seg[num].l+seg[num].r)>>1 , flag = 1;
    if(l <= mid)
        flag = query(num<<1 , l , r);
    if(r > mid)
        flag = min(flag , query(num<<1|1 , l , r));
    return flag;
}

void update(int num , int l , int r) {
    if(seg[num].l >= l && seg[num].r <= r) {
        seg[num].vis = 1;
        return ;
    }
    int mid = (seg[num].l+seg[num].r)>>1;
    if(l <= mid)
        update(num<<1 , l , r);
    if(r > mid)
        update(num<<1|1 , l , r);
    if(seg[num<<1|1].vis && seg[num<<1].vis)
        seg[num].vis = 1;
}

int main() {
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d%d%d",&cow[i].x,&cow[i].y,&cow[i].val);
    sort(cow+1 , cow+n+1);	
    for(int i=1; i<=n; i++) {
        int l = myabs(cow[i].x+1)*cow[i].val , r = l + cow[i].val;
        lsh[++top] = l;
        lsh[++top] = r;
        node[i].l = l , node[i].r = r;
    }
    sort(lsh+1 , lsh+top+1);
    cnt = unique(lsh+1 , lsh+top+1) - lsh - 1; 
    for(int i=1; i<=n; i++) {
        node[i].l = lower_bound(lsh+1 , lsh+cnt+1 , node[i].l) - lsh;
        node[i].r = lower_bound(lsh+1 , lsh+cnt+1 , node[i].r) - lsh;
    }
    build(1 , 1 , cnt);
    for(int i=1; i<=n; i++) {
        if(!query(1 , node[i].l , node[i].r-1))
            ans++;
        update(1 , node[i].l , node[i].r-1);
    }
    printf("%d",ans);
    return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3114

---

## 作者：MSqwq (赞：3)

## 考查内容：线段树+离散化

题解：  
首先，计算出每个线段在 $x$ 坐标 $0$ 处出现的时间开始点和结束点，就转成了时间轴上的线段。  
然后就是看每条线段是否被 $y$ 比它小的线段完全覆盖了。注意求出的时间点要离散化，然后应该使用时间轴上的区间来表示，两线段端点重合并不是有共同部分。  
将所有线段按照 $y$ 从小到大排序之后，使用线段树判断它覆盖的区间是否已经都被前面的线段覆盖了。 
然后将它所覆盖的区间覆盖。   

说人话就是：  
$1.$建立一颗关于时间的线段树  
$2.$把每一只羊驼的首和尾通过$y$轴的时间，同时离散化  
$3.$按羊驼的高度排序，分别把每一只的时间作为区间加入线段树  
$4.$如果这段区间已被覆盖，则返回$0$  
$5.$如果为未覆盖，则返回$1$，同时将区间覆盖   

代码如下：  
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,x,y,z;
ll tot;
ll ans;
struct qwe{
	ll l,r,s;
}a[50010];
map<ll,ll>m;
ll b[100010],cnt;
void add(ll x,ll y,ll z,ll k)
{
	a[k].l=(x-1)*z;
	a[k].r=x*z;
	a[k].s=y;
	
	b[++cnt]=(x-1)*z;
	b[++cnt]=x*z;
}
bool cmp(qwe x,qwe y)
{
	return x.s<y.s;
}

struct asd{
	ll l,r;
	bool v;
}t[8000000];

void build(ll p,ll x,ll y)
{
	t[p].l=x;
	t[p].r=y;
	t[p].v=0;
	if(x==y)return;
	build(p*2,x,(x+y)/2);
	build(p*2+1,(x+y)/2+1,y);
}

ll gs(ll p,ll x,ll y)
{
	if(t[p].v==1)return 0;
	
	if(x<=t[p].l&&y>=t[p].r)
	{
		t[p].v=1;
		return 1;
	}
	
	ll ls=0,rs=0;
	ll mid=(t[p].l+t[p].r)/2;
	
	if(x<=mid)ls=gs(p*2,x,y);
	if(y>mid)rs=gs(p*2+1,x,y);
	
	if(t[p*2].v&&t[p*2+1].v)t[p].v=1;
	else t[p].v=0;
	if(ls==1||rs==1)return 1;
	else return 0;
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&z);
		add(-x,y,z,i);
	}
	sort(b+1,b+1+cnt);
	sort(a+1,a+1+n,cmp);	

	for(int i=1;i<=n*2;i++)
	{
		if(b[i]!=b[i-1]||i==1)m[b[i]]=++tot;
	}
	
	build(1,1,tot);
	
	for(int i=1;i<=n;i++)
	{
		a[i].l=m[a[i].l];
		a[i].r=m[a[i].r];
		a[i].r--;
	}
	
	//for(int i=1;i<=n;i++)cout<<a[i].l<<" "<<a[i].r<<endl;
	for(int i=1;i<=n;i++)
	{
		x=gs(1,a[i].l,a[i].r);
		ans+=x;
		//cout<<x<<" "<<ans<<endl;
	}
	printf("%lld",ans);
}
```


---

## 作者：ueettttuj (赞：2)

[题目](https://www.luogu.org/problem/P3114)

本题可以用线段树写。对于每一头牛，它所覆盖的区间就是它经过$y$轴的时间段。但因为这个时间段可能会很长并且较为分散，所以可以考虑先离散化，再去实现。须要注意的是时间段是左闭右开的。对于每一头奶牛，它能否被看到取决于它经过$y$轴的时间段中是否已经被其他牛(纵坐标比它小的)填充完了。

这里提供一组本人认为的$hack$数据，如果找了很久没找出错，可以试一下。

```cpp
4
-10 6 1
-6 7 2
-5 6 3
-10 8 4
```
正解为$4$

最后贴代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans;
struct node{
	long long ll,rr,h; 
};
node a[50010];
long long aa[1000100];
long long cnt,col;
struct data{
	long long minn,lazy;
};
data tree[1200010];
bool cmp(const node &qw , const node &we){
	if(qw.h!=we.h) return qw.h<we.h;
	else {
		return qw.ll<we.ll;
	}
}
void pushup(long long rt){
	tree[rt].minn=min(tree[rt*2].minn,tree[rt*2+1].minn);
}
void pushdown(long long rt){
	if(tree[rt].lazy!=0){
		tree[rt*2].lazy=tree[rt].lazy;
		tree[rt*2+1].lazy=tree[rt].lazy;
		tree[rt*2].minn=1;
		tree[rt*2+1].minn=1;
		tree[rt].lazy=0;
	}
}
void add(long long rt,long long l,long long r,long long x,long long y){  //将当前时间段填充 
	if(x<=l && y>=r){
		tree[rt].lazy=1;
		tree[rt].minn=1;
		return ;
	}
	pushdown(rt);
	long long mid=(l+r)/2;
	if(x<=mid) add(rt*2,l,mid,x,y);
	if(y>mid) add(rt*2+1,mid+1,r,x,y);
	pushup(rt);
}
bool ask(long long rt,long long l,long long r,long long x,long long y){  //判断时间段是否已被填充 
	if(x<=l && y>=r){
		if(tree[rt].minn==0) return 1;
		else return 0;
	}
	pushdown(rt);
	long long mid=(l+r)/2;
	long long anss=0;
	if(x<=mid) anss=anss|ask(rt*2,l,mid,x,y);
	if(y>mid) anss=anss|ask(rt*2+1,mid+1,r,x,y);
	return anss;
}
int main(){
	//freopen("data.in","r",stdin);
	//freopen("my.out","w",stdout);
	scanf("%lld",&n);
	long long b,c,d;
	aa[1]=-1;
	cnt=2;
	for(long long i=1;i<=n;i++){
		scanf("%lld %lld %lld",&b,&c,&d);
		a[i].ll=abs(b+1)*d;
		a[i].rr=abs(b)*d-1;
		a[i].h=c;
		aa[++cnt]=a[i].ll;
		aa[++cnt]=a[i].rr;
		aa[++cnt]=a[i].rr+1;
	}
	sort(aa+1,aa+cnt+1);      //离散化 
	cnt=unique(aa+1,aa+cnt+1)-aa-1;
	sort(a+1,a+n+1,cmp);   //注意需要排序 
	for(long long i=1;i<=n;i++){
		long long xx,yy;
		xx=lower_bound(aa+1,aa+cnt+1,a[i].ll)-aa;
		yy=lower_bound(aa+1,aa+cnt+1,a[i].rr)-aa;
		if(ask(1,1,cnt,xx,yy)==1) ans++;      //时间段没被全部填充，可以被看见 
		add(1,1,cnt,xx,yy);
	}
	printf("%lld\n",ans);
	return 0;
}
```
$emm...$我认为这道题没有说清楚当两头牛纵坐标相同时可能(相撞???)的情况。所以我也没有去特判之类的~~(反正都过了)~~

---

## 作者：子谦。 (赞：2)


我一开始看错题了，看成每秒走$c_i$个单位了，于是样例答案就变成了3。。害我调好久，还以为样例错了

-----

对于每头奶牛，我们求出它经过$y$轴的时间段，然后离散化一下，将奶牛按照从低到高的顺序排序，区间上记录最新经过的奶牛，如果当前奶牛的区间都已经被覆盖过了，那么说明完全被遮挡，反之则可以被看到，这样的话由于已经排过序了，可以很容易看出这是正确的，用线段树实现即可

线段树我是这么实现的，初始值为无限大，$update$时直接覆盖修改的区间，这样查询区间最大值，只要不是无限大，就说明完全被遮挡

下面放代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc getchar
#define maxn 50005
using namespace std;

inline ll read(){
	ll a=0;int f=0;char p=gc();
	while(!isdigit(p)){f|=p=='-';p=gc();}
	while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
	return f?-a:a;
}int n,ans,cnt,x[maxn],c[maxn];ll b[maxn<<1];

struct ahaha{
	int h,l,r;
	inline bool friend operator<(const ahaha x,const ahaha y){
		return x.h<y.h;
	}
}q[maxn];

struct ahaha1{
	int v,lz;
	ahaha1(){
		v=1000001;
		lz=-1;
	}
}t[maxn<<3];
#define lc p<<1
#define rc p<<1|1
inline void pushup(int p){
	t[p].v=max(t[lc].v,t[rc].v);
}
inline void pushdown(int p){
	int &lz=t[p].lz;
	t[lc].v=lz;t[lc].lz=lz;
	t[rc].v=lz;t[rc].lz=lz;
	lz=-1;
}
void update(int p,int l,int r,int L,int R,int z){
	if(l>R||r<L)return;
	if(L<=l&&r<=R){t[p].v=z;t[p].lz=z;return;}
	int m=l+r>>1;if(~t[p].lz)pushdown(p);
	update(lc,l,m,L,R,z);update(rc,m+1,r,L,R,z);
	pushup(p);
}
int query(int p,int l,int r,int L,int R){
	if(l>R||r<L)return -1;
	if(L<=l&&r<=R)return t[p].v;
	int m=l+r>>1;if(~t[p].lz)pushdown(p);
	return max(query(lc,l,m,L,R),query(rc,m+1,r,L,R));
}

int main(){
	n=read();
	for(int i=1;i<=n;++i){
		x[i]=read();q[i].h=read();c[i]=read();
		b[++cnt]=1ll*-x[i]*c[i];
		b[++cnt]=1ll*(-x[i]-1)*c[i];
	}
	sort(b+1,b+cnt+1);cnt=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=n;++i){
		q[i].l=lower_bound(b+1,b+cnt+1,1ll*(-x[i]-1)*c[i])-b;
		q[i].r=lower_bound(b+1,b+cnt+1,1ll*-x[i]*c[i])-b;
	}
	sort(q+1,q+n+1);
	for(int i=1;i<=n;++i){
		int v=query(1,1,cnt,q[i].l,q[i].r-1);
		if(v==1000001)++ans;
		update(1,1,cnt,q[i].l,q[i].r-1,q[i].h);
	}
	printf("%d\n",ans);
	return 0;
}

```



---

## 作者：kuikuidadi (赞：1)

# 思路

离散化一下看每头羊驼跨越 $y$ 轴的时间左端点、右端点。
然后按 $y$ 坐标排序后挨个去线段树里扫看是否被完全覆盖。

# 注意事项

$[3,4]$ 以及 $[4,5]$ 被覆盖不代表 $[4]$ 被覆盖了，所以离散化时的取值略加修改。

WA：```if(i==1||lsh[i].x!=lsh[i-1].x) m++;```

AC：```if(i==1||lsh[i].x!=lsh[i-1].x) m+=2;```

# code


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000001
using namespace std;
int n,m,cnt;
struct node{
	int l,r,x;
	bool operator<(node &a) const{
		return x<a.x;
	}  
}lsh[N<<1],q[N];
struct Edge{
	int l,r,c;
}tree[N];
void pushup(int o){
	tree[o].c=tree[o].c|(tree[o<<1].c&tree[o<<1|1].c);
}
void build(int o,int l,int r){
	tree[o].l=l;
	tree[o].r=r;
	if(l==r) return;
	int mid=l+r>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
}
int query(int o,int l,int r){
	if(tree[o].c) return 0;
	if(tree[o].l==l&&r==tree[o].r){
		tree[o].c=1;
		return 1;
	}
	int mid=tree[o].l+tree[o].r>>1,ans;
	if(r<=mid) ans=query(o<<1,l,r);
	else if(l>mid) ans=query(o<<1|1,l,r);
	else ans=(query(o<<1,l,mid)|query(o<<1|1,mid+1,r));
	pushup(o);
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		q[i].x=v;
		u=(-u-1)*w;
		w+=u;
		lsh[++cnt]={i,0,u};
		lsh[++cnt]={i,1,w};
	}
	sort(lsh+1,lsh+cnt+1);
	for(int i=1;i<=cnt;i++){
		if(i==1||lsh[i].x!=lsh[i-1].x) m+=2;
		if(lsh[i].r==0) q[lsh[i].l].l=m;
		else q[lsh[i].l].r=m;
	}
	sort(q+1,q+n+1);
	build(1,1,m);
	int ans=0;
	for(int i=1;i<=n;i++) ans+=query(1,q[i].l,q[i].r);
	cout<<ans;
}
```

---

## 作者：luo_shen (赞：1)

**题意**  
将奶牛经过 $y$ 轴的时间看为数轴上一条线段（或区间），每个线段（或区间）有一个颜色，按照颜色从大到小进行线段覆盖，求完成线段覆盖后，数轴上有多少种不同的颜色。  
**解析**  
我看题解里大多是 **离散化+线段覆盖** 和 **扫描线** ，那我换个思路吧。  
将时间看成一个左右都闭合的区间，每次进行添加区间时都考虑这个区间与其它区间的关系，如果是被其它区间所包含，则该区间不计入答案。否则将该区间放入区间序列中。  
但如果这就结束了，那你就会死得很惨（实测 $6pts$ 1AC，3WA，11TLE ）。那么为什么会这样呢？首先我们考虑 WA 的问题：因为很多时候一个区间会被不止一个区间并起来的区间包含，会导致答案增多。而TLE的问题则是因为不合并区间，要考虑的区间就会增多，会跑满 $n^2$的时间复杂度。所以若两个区间有交集，直接合并成一个区间。  
**代码实现**  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
struct node{
    int y,l,r;
}a[50010];//待处理的区间
struct Node{
    int l,r;
    friend bool operator<(const Node &x,const Node &y){
        return x.l>y.l;//按l排序，方便后续合并操作
    }
};//已处理的区间
int read(){
    int s=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+(ch-'0');
        ch=getchar();
    }
    return s*f;
}
bool cmp(node x,node y){
    return x.y<y.y;
}
priority_queue<Node>q;//利用优先队列给已处理的区间排序
queue<Node>p;//存储暂时没什么用的区间，即缓存区
signed main(){
    int x,y,r;
    n=read();
    for(int i=1;i<=n;i++){
        x=read(),y=read(),r=read();
        a[i].y=y;
        a[i].l=(-x-1)*r;//右端触碰到y轴的时间为该区间的左端点
        a[i].r=-x*r;//左端离开y轴的时间为该区间右端点
    }
    sort(a+1,a+n+1,cmp);//按照y值从小到大排序
    for(int i=1;i<=n;i++){
        int f=0,l=a[i].l,r=a[i].r;
        while(!q.empty()){
            Node x=q.top();
            if(x.l<=l&&r<=x.r){//该区间被包含
                f=-1;
                break;
            }
            else if(r>=x.l&&x.r>=l){//该区间与序列里某个区间有交集
                x.l=min(l,x.l),x.r=max(r,x.r);//合并这两个区间
                f=1;
                ans++;//统计答案
                q.pop();
                while(!q.empty()){//考虑合并后的区间与其它区间是否有交集，有就直接合并
                    Node y=q.top();
                    if(y.l<=x.r){
                        x.r=max(x.r,y.r);
                        q.pop();
                    }
                    else{
                        break;
                    }
                }
                q.push(x);
                break;
            }
            p.push(x);
            q.pop();
        }
        while(!p.empty()){
            q.push(p.front());
            p.pop();
        }//将缓存区中的区间放回序列中
        if(f==0){//若与任何一个区间均没有交集，直接放入序列中
            q.push(Node{l,r});
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：qwer6 (赞：0)

我们很容易可以得到某一只牛经过 $y$ 半轴的时间区间。

对于一只牛，它经过 $y$ 半轴的时间为 $[-(x+1)*v,(-x*v)-1]$。

那这道题其实就已经退化成贴海报了。

我们将所有牛对应的区间按照 $y$ 从大到小排序，然后使用线段树维护区间覆盖，对于每只牛，我们将他对应的区间覆盖为它的编号，最后线段树中有几种编号就可以看到几只牛。

不过需要注意的是，这道题需要离散化，不然数组开不下，并且在离散化时要注意的是，我们需要在离散化数组中加入每个区间的上界加一之后的值，不然会导致一些奇奇怪怪的问题。

```c++
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
#define Line cout<<"______________________________"<<endl
namespace FastIO{
	char c;
	int f;
	int num[30];
	inline void read(int &a){
		c=getchar();
		f=1,a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		a*=f;
		return ;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		num[0]=0;
		do{
		   num[++num[0]]=x%10;
		   x/=10;
		}while(x);
		for(int i=num[0];i;i--)putchar(num[i]+'0');
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=1e5+5,inf=0x3f3f3f3f;
int n,tot,ans;
int tmp[N*3];
bool vis[N<<1];
struct Node{
	int l,r,y;
	bool operator <(const Node &a){return y<a.y;}
}a[N];
struct Segment_tree{
	int c[N<<3],tag[N<<3];
	#define ls p<<1
	#define rs (p<<1)+1
	void Tag(int p,int v){
		c[p]=v;
		tag[p]=v;
	}
	void pushdown(int p){
		if(tag[p]!=inf){
			Tag(ls,tag[p]);
			Tag(rs,tag[p]);	
		}
		tag[p]=inf;
	}
	void build(int p,int l,int r){
		tag[p]=inf;
		if(l==r)return ;
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void change(int p,int l,int r,int L,int R,int v){
		if(L<=l&&r<=R){
			Tag(p,v);
			return ;
		}
		pushdown(p);
		int mid=l+r>>1;
		if(mid>=L)change(ls,l,mid,L,R,v);
		if(mid<R)change(rs,mid+1,r,L,R,v);
	}
	int query(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return c[p];
		pushdown(p);
		int mid=l+r>>1,res=0;
		if(mid>=L)res=query(ls,l,mid,L,R);
		if(mid<R)res=query(rs,mid+1,r,L,R);
		return res;
	}
}Set;
signed main(){
	read(n);
	for(int i=1,x,y,c;i<=n;i++){
		read(x),read(y),read(c);
		a[i].l=-(x+1)*c;
		a[i].r=(-x*c)-1;
		a[i].y=y;
		tmp[++tot]=a[i].l;
		tmp[++tot]=a[i].r;
		tmp[++tot]=a[i].r+1;
	}
	sort(tmp+1,tmp+tot+1);
	sort(a+1,a+n+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	Set.build(1,1,tot);
	for(int i=1;i<=n;i++){
		a[i].l=lower_bound(tmp+1,tmp+tot+1,a[i].l)-tmp;
		a[i].r=lower_bound(tmp+1,tmp+tot+1,a[i].r)-tmp;
	}
	for(int i=n;i>=1;i--)Set.change(1,1,tot,a[i].l,a[i].r,i);//区间覆盖
	for(int i=1,x;i<=tot;i++){
		x=Set.query(1,1,tot,i,i);
		if(!x)continue;//0 不算编号
		if(!vis[x]){
			ans++;
			vis[x]=1;
		}
	}
	write(ans);
}
```

---

## 作者：编程小贝壳 (赞：0)

[原题](https://www.luogu.com.cn/problem/P3114)

一眼顶针，鉴定为纯纯的线段树模板。

### 分析

首先将题意中牛在运动替换一下，代换为其在 Farmer John 视线中停留的时间，那么我们只需要在每个时刻检查一下能看到的是那个牛并给这头牛打上标记，最后统计有几头牛身上有标记即可。

### 一些细节

想到这个思路之后显然可以发现要对时间进行离散化，因为我们只关心时间的相对大小，而不关心其绝对大小。

例如，如果 $[l,r]$ 这段时间内都只能看到同样的一头牛，那么 $[l,r]$ 与 $[l,l+1]$ 是等效的。因此离散化的正确性是显然的。

接着就是要注意进行线段树的区间覆盖时，要从 $x$ 值大的奶牛开始覆盖。原因很显然，如果两头牛同时在视线之内，那么只能看到 $x$ 值更小的那一个。

最后注意处理好边界问题即可。

---

## 作者：哈士奇憨憨 (赞：0)

## 题意
给定一些水平单位线段的初始位置和向右移动的速度，求有一条线段可能成为朝 y 轴正方向的射线遇到的第一条线段。
## 思路
线段的数量比较多，模拟线段的移动比较低效，应当对线段与射线之间的关系进行分析。

通过线段的初始点和右移速度，可以求出射线穿过线段的时间段，任意时刻，射线穿过的线段中 y 坐标最小的就是射线第一个遇到的线段。

考虑到时间段的连续性，我们可以用扫描线的方式来维护当前与射线相交的线段。将每个时间段分成入点和出点，然后对所有的时间点排序，按顺序处理。如果遇到了入点，就将对应的线段加入，否则将对应的线段删除，此外，还要能够求出 y 坐标最小的线段，可以用 STL 中的 `map` 进行维护。

值得注意的是，不能对时刻进行处理，因为一条线段可能在两个相邻时刻都被其他线段挡住了，但是在这两个时刻之间是射线遇到的第一个线段。所以我们应当将时刻对应到时段，然后对时段进行处理。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 5e4 + 1;
struct E {                                                // 事件
  int i, t, y, o;                                         // 编号、时段编号、y坐标、类型
  bool operator<(const E &_e) const { return t < _e.t; }  // 按照时段排序
} e[kMaxN * 2];
map<int, int> m;
bool b[kMaxN];
int n, r, ans;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].t >> e[i].y >> r;
    e[i + n] = {i, -(e[i].t + 1) * r, e[i].y, 1};  // 时段左边界
    e[i] = {i, e[i].t * -r, e[i].y, 0};            // 时段右边界外
  }
  sort(e + 1, e + 1 + 2 * n);
  for (int i = 1, j; i <= 2 * n; i = j) {  // 枚举每个时段
    for (j = i; e[j].t == e[i].t; j++) {   // 相同时段合并处理
      if (e[j].o) {                        // 开始时段
        m[e[j].y] = e[j].i;                // 记录y坐标
      } else {                             // 结束时段
        m.erase(e[j].y);                   // 删除y坐标
      }
    }
    if (!m.empty()) {            // 当前时段有线段
      b[m.begin()->second] = 1;  // 标记最低线段
    }
  }
  for (int i = 1; i <= n; i++) {  // 枚举线段
    ans += b[i];                  // 累加答案
  }
  cout << ans;
  return 0;
}

```

---

