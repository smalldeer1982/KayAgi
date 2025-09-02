# [USACO07OPEN] City Horizon S

## 题目描述

Farmer John has taken his cows on a trip to the city! As the sun sets, the cows gaze at the city horizon and observe the beautiful silhouettes formed by the rectangular buildings.

The entire horizon is represented by a number line with N (1 ≤ N ≤ 40,000) buildings. Building i's silhouette has a base that spans locations Ai through Bi along the horizon (1 ≤ Ai < Bi ≤ 1,000,000,000) and has height Hi (1 ≤ Hi ≤ 1,000,000,000). Determine the area, in square units, of the aggregate silhouette formed by all N buildings.

有一个数列，初始值均为0，他进行N次操作，每次将数列[ai,bi)这个区间中所有比Hi小的数改为Hi，他想知道N次操作后数列中所有元素的和。


## 说明/提示

N<=40000 , a、b、k<=10^9 。


## 样例 #1

### 输入

```
4
2 5 1
9 10 4
6 8 2
4 6 3```

### 输出

```
16```

# 题解

## 作者：Simon_ (赞：42)

线段树区间修改，维护从l到r的高度

相比坐标的le9，n比较小，所以用数组p离散化，修改的时候二分修改的区间即可

将修改的矩形按高度排序，保证后修改的高度一定覆盖之前的

- 注意右区间和左区间都包括mid

- 以及树的空间要开满2\*4\*40000，部分变量记得用long long【因为这一点贡献了4个提交次数\_(┐「ε:)\_

下面贴代码


    
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
long long ans;
int t;
struct node{
    int left,right;
    int c;
}tree[4*40005*2];
struct edge{
    int left,right,h;
}a[40005];
int p[2*40005];
bool cmp(edge e1,edge e2)
{
    return e1.h<e2.h;
}
int erfen(int l,int r,int x)//二分查找当前所要修改的离散化区间，即对应的矩形顶点的区间，【比如样例里，当,处理第一个矩形时，修改的区间为（1，2），即第一个矩形的两个顶点在p数组中对应的下标为1、2；
{
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(p[mid]==x) return mid;
        else if(p[mid]>x) r=mid-1;
        else l=mid+1;
    }
    return 0;
}
void change(int now,int l,int r,int x)//裸的区间修改
{
    if(tree[now].right<l||tree[now].left>r) return;
    if(tree[now].left>=l&&tree[now].right<=r)
    {
        tree[now].c=x;
        return;
    }    
    int mid=(tree[now].left+tree[now].right)/2;
    if(tree[now].c) {
        tree[now*2].c=tree[now].c;
        tree[now*2+1].c=tree[now].c;
        tree[now].c=0;
    }
    if(mid>=r)     change(now*2,l,r,x);
    else if(mid<=l) change(now*2+1,l,r,x);
    else {
        change(now*2,l,r,x); change(now*2+1,l,r,x);
    }
}
void built(int now,int l,int r)
{
    tree[now].left=l;
    tree[now].right=r;
    tree[now].c=0;
    if(l==r-1) return;
    built(now*2,l,(l+r)/2);
    built(now*2+1,(l+r)/2,r);//*右界要包括mid，因为一个矩形所占的位置肯定大于一个点，如果不包括mid，会漏掉一些矩形； 
}
void quest(int now)
{
    if(tree[now].c) 
    {
        ans+=(p[tree[now].right]-p[tree[now].left])*(long long)tree[now].c;
        return;
    }
    if(tree[now].right==tree[now].left+1) return;
    quest(now*2);
    quest(now*2+1);
}
int main()
{ 
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
    scanf("%d%d%d",&a[i].left,&a[i].right,&a[i].h);
    p[++t]=a[i].left;
    p[++t]=a[i].right;    
```
}//离散化顶点

```cpp
    sort(p+1,p+1+2*n);
    sort(a+1,a+n+1,cmp);
    built(1,1,n*2);
    for(int i=1;i<=n;i++)
    {
        int l=erfen(1,2*n,a[i].left);
        int r=erfen(1,2*n,a[i].right);
        change(1,l,r,a[i].h);
    }
    quest(1);
    printf("%lld",ans);
}
第一次写题解有点丑丑的(｡・`ω´･)，可能表达有点不好，看不太明白的同学可以问我
```

---

## 作者：Rachel_in (赞：19)

**题解里居然都是离散化，相比较而言我觉得动态开点更加好理解。**

我们先把每次修改按照高度从小到大排序，这样可以保证之后的每次操作都是当前最大高度，也就是不会被当前为止其他的操作覆盖。

随着每次修改后的$pushdown$，我们发现只有叶子节点会被标记，这代表着我们已经把高楼分成了若干相等高度的段，每一个叶子节点代表着一段。

那么统计答案就变得简单了，我们找到每个叶子节点，答案+=高度*$(r-l+1)$

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline int read(){
	int res=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
	return res*f;
}
const int N=40005;
const int inf=1e9;
int n,tr[4000005],lc[4000005],rc[4000005],cnt,root,ans=0;
struct node{
	int l,r,h;
}g[N];
inline bool cmp(node x,node y){
	return x.h<y.h;
}
inline void pushdown(int k,int l,int r){
	if(!tr[k]) return ;//如果没有标记，就退出
	if(l==r) return ;//如果l==r，说明这个节点不可能会有叶节点了
	if(!lc[k]) lc[k]=++cnt;//如果左节点没被开创，那就开创它，方便标记下传
	if(!rc[k]) rc[k]=++cnt;//右节点同理
	tr[lc[k]]=tr[k];
	tr[rc[k]]=tr[k];
	tr[k]=0;//标记清空
}
void change(int &k,int l,int r,int x,int y,int val){
	if(!k) k=++cnt;//这个节点还没被开创过，那就开创它
	if(l==x&&r==y){
		tr[k]=val;return ;//找到区间，标记
	}
	pushdown(k,l,r);//向下传递
	int mid=(l+r)>>1;
	if(y<=mid) change(lc[k],l,mid,x,y,val);else
	if(x>mid) change(rc[k],mid+1,r,x,y,val);else{
		change(lc[k],l,mid,x,mid,val);change(rc[k],mid+1,r,mid+1,y,val);	
	}	
}
void query(int k,int l,int r){
	if(tr[k]){//如果这个点有标记，说明它是叶节点，统计答案后退出
		ans+=(r-l+1)*tr[k];
		return ;
	}	
	int mid=(l+r)>>1;
	if(lc[k]) query(lc[k],l,mid);//如果它有左儿子，那就递归它的左儿子
	if(rc[k]) query(rc[k],mid+1,r);//右儿子同理
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		g[i].l=read();g[i].r=read();g[i].h=read();
	}
	sort(g+1,g+n+1,cmp);//按照高度排序
	for(int i=1;i<=n;i++){
		change(root,1,inf,g[i].l,g[i].r-1,g[i].h);//修改，注意是左闭右开区间
	}
	query(root,1,inf);//统计答案
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：秋日私语 (赞：12)

更好的阅读体验点[这里](https://blog.csdn.net/A_Comme_Amour/article/details/79671067)

题目
-

[传送门](https://www.luogu.org/problemnew/show/P2061)

约翰带着奶牛去都市观光。在落日的余晖里，他们看到了一幢接一幢的摩天高楼的轮廓在地平线 上形成美丽的图案。以地平线为 X 轴，每幢高楼的轮廓是一个位于地平线上的矩形，彼此间可能有 重叠的部分。奶牛一共看到了 N 幢高楼，第 i 幢楼的高度是 Hi，两条边界轮廓在地平线上的坐标是 Ai 到 Bi。请帮助奶牛们计算一下，所有摩天高楼的轮廓覆盖的总面积是多少。

另一种理解方式：

有一个数列，初始值均为0，他进行N次操作，每次将数列 [ai,bi) 这个区间中所有比Hi小的数改为Hi，他想知道N次操作后数列中所有元素的和。

题解
-

本题解提供两种解法
第一种就是简化版矩形面积求交，扫描线的经典题；具体讲解可以看[这里](https://blog.csdn.net/a_comme_amour/article/details/79402361)

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define ll long long
using namespace std;
const int maxn=1000001;

ll n;
ll x1,x2,y1,y2;
struct Tree{
    ll l,r,c;
    ll cnt,fl,fr;//cnt 差值 
}tree[maxn<<2];
struct Line{
    ll x,y1,y2;
    ll f;//+-1:矩形左边还是右边的边 
}line[maxn<<1];
ll y[maxn];
bool cmp(Line a,Line b) {return a.x<b.x;}

void build_tree(ll l,ll r,ll rt)
{
    tree[rt].l=l; tree[rt].r=r;
    tree[rt].c=tree[rt].cnt=0;
    tree[rt].fl=y[l];
    tree[rt].fr=y[r];
    if (l+1==r) return;//叶子结点 
    ll mid=(l+r)>>1;
    build_tree(l,mid,rt<<1);
    build_tree(mid,r,rt<<1|1);
}

void calc(ll rt)
{
    if (tree[rt].c>0)
    {
        tree[rt].cnt=tree[rt].fr-tree[rt].fl;
        return;
    }
    if (tree[rt].l+1==tree[rt].r) tree[rt].cnt=0;//叶子节点 
    else tree[rt].cnt=tree[rt<<1].cnt+tree[rt<<1|1].cnt;
}

void update(ll rt,Line e)
{
	if (e.y1==tree[rt].fl && e.y2==tree[rt].fr)
	{
		tree[rt].c+=e.f;
		calc(rt); 
		return;
	}
	if (e.y2<=tree[rt<<1].fr) update(rt<<1,e);
	else if (e.y1>=tree[rt<<1|1].fl) update(rt<<1|1,e);
	else
	{
		Line tmp=e;
		tmp.y2=tree[rt<<1].fr;
		update(rt<<1,tmp);
        tmp=e;
        tmp.y1=tree[rt<<1|1].fl;
        update(rt<<1|1,tmp);
    }
    calc(rt);
}

int main()
{
//	freopen("[USACO07OPEN]城市的地平线.in","r",stdin);
	
    ll ans=0;
    scanf("%lld",&n);
    ll tot=0;
    for (ll i=1; i<=n; i++)
    {
    	y1=0;
        scanf("%lld%lld%lld",&x1,&x2,&y2);
        line[++tot].x=x1;
        line[tot].y1=y1;
        line[tot].y2=y2;
        line[tot].f=1;
        y[tot]=0;
        line[++tot].x=x2;
        line[tot].y1=y1;
        line[tot].y2=y2;
        line[tot].f=-1;
        y[tot]=y2;
	}
    sort(y+1,y+1+tot);
    sort(line+1,line+1+tot,cmp);
    build_tree(1,tot,1);
// 		printf("rt l r c h cnt\n");
//      for (ll rt=1; rt<=(n<<1); rt++) printf("%lld: %lld %lld %lld %.0lf %.0lf\n",rt,tree[rt].l,tree[rt].r,tree[rt].c,tree[rt].fr,tree[rt].cnt);
    update(1,line[1]);
    ll res=0;
    for (ll i=2; i<=tot; i++)
    {
        res+=tree[1].cnt*(line[i].x-line[i-1].x);
        update(1,line[i]);
    }
    printf("%lld",res);
    return 0;
}
```

第二种也是扫描线的思想，具体用优先队列实现，参考了楼下的代码
以区间的左端点为优先级建立优先队列；不在范围内的区间就pop掉；新出现建筑物如果符合范围就入队 ；
最后像扫描线一样，每次取出一小段计算面积

```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int maxn=100001;

int n,m,p[maxn];
struct Node{
	int x,y,v;
	bool operator < (Node a) const {
	return this -> v < a.v;}
}a[maxn];
priority_queue <Node> q;

bool cmp(Node a,Node b) {return a.x<b.x;}
bool cmp1(int a,int b) {return a<b;}

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	{
		int x,y,h; scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v);
		p[i*2]=a[i].y;
		p[i*2-1]=a[i].x;
	}
	sort(a+1,a+1+n,cmp);
	sort(p+1,p+1+2*n,cmp1);
	int tot=0;//已经放置的建筑物 
	long long ans=0;
	for (int i=1; i<n*2; i++)
	{
		while (!q.empty() && q.top().y<=p[i]) q.pop();//不在范围内pop 
		while (p[i]<=a[tot+1].x && a[tot+1].x<p[i+1])//新出现的在范围内的入队 
			q.push(a[++tot]);
		if (!q.empty())
			ans+=(long long)(p[i+1]-p[i])*q.top().v;
	}
	printf("%lld",ans);
	return 0;
}
```

总结
-

有许多细节需要注意。long long之类的；


---

## 作者：Minecraft万岁 (赞：10)

### 相信我 看直接的题目要求就输了  
看一下这题 好眼熟  ~~珂朵莉树~~  
双倍经验 [天际线](https://www.luogu.com.cn/problem/P1904)  
这题不就是把变化的折点换成面积了吗   
所以说先按照高度从小到大排序 然后按顺序一个一个推平 最后扫一边 计算一下面积即可   
~~怎么计算呢~~  
我们发现珂朵莉树的每一个节点保存的三个元素 ${l,r,h}$ 表示从 $l$ 到 $r$ 的一段高度都是 $h$ 那么这个单独的一段不就是一个 高为 $h$ 宽为 $l-r+1$ 的 正方形吗 直接小学数学公式 $S=ab$ 计算单个区间 然后 $ans$ 累加一便就完了  
完了 $?$  ~~完了~~   
$$\text{十年OI一场空 不开long long 见祖宗}$$  
 
高清无码程序 


------------
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<set>
#include<cstdlib>
#include<algorithm>
#define IT set<node>::iterator  //宏定义 懒人必备 
using namespace std;
typedef long long ll;
struct node//珂朵莉树的节点 
{
	ll l,r;
	mutable ll v;
	node(ll L,ll R=-1,ll V=0):l(L),r(R),v(V){}
	bool operator < (const node &t)const{//使用set重载小于号 
		return l<t.l;
	} 
};
set<node> s;//珂朵莉树 
ll n;
struct val//读入的数据 要结构体排序 
{
	ll l;
	ll r;
	ll h;
}a[40005];
ll ans;//最终的答案 
inline void read(ll &x)//快读 
{
	ll f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline bool cmp(val p,val q)//按照 h 从小到大排序 
{
	return p.h<q.h;
}
inline IT split(ll pos)//珂朵莉树的split 
{
	IT it=s.lower_bound(node(pos));
	if(it!=s.end()&&it->l==pos) return it;
	--it;
	ll tl=it->l;
	ll tr=it->r;
	ll tv=it->v;
	s.erase(it);
	s.insert(node(tl,pos-1,tv));
	return s.insert(node(pos,tr,tv)).first;
} 
inline void assign_val(ll l,ll r,ll val)//珂朵莉树的推平 
{
	IT itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,val));
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(a[i].l);
		read(a[i].r);
		a[i].r--;//比较坑的 [l,r) 所以说要减一个 变成 [l,r] 
		read(a[i].h);
	}
	sort(a+1,a+n+1,cmp);//排序 
	s.insert(node(1,a[n].r,0));//标准建树操作 
	s.insert(node(a[n].r+1,a[n].r+1,0));
	for(int i=1;i<=n;i++)
		assign_val(a[i].l,a[i].r,a[i].h);//一个一个推平 
	for(IT it=s.begin();it!=s.end();++it)//加一遍答案 
		ans+=1ll*(it->r-it->l+1)*it->v;
	printf("%lld\n",ans);
	return 0;
}



```


---

## 作者：用户已注销 (赞：10)

一道检测选手**有没有学傻**的 USACO 好题~

~~所以强烈建议将数据范围改成 N = 3e5 ， A、B = 1e17 卡掉线段树~~

提供一种 O(NlogN~~乘以STL巨大常数~~) 的简单做法：

对于每个高度，显然只需要维护当前最大高度就好了。

所以自然想到将操作拆成 insert（左） 和 delete（右），然后按下标 sort 一波。

显然两个相邻被操作的下标之间的数值都是相等的，所以我们需要维护的就是以下操作：单点插入，单点删除，查询全局最值。

~~什么？？？然后你想到用平衡树？？？~~

当然是写一个可删除的堆来维护啊！只要两个 STL 优先队列（priority_queue），再手写一行**惰性删除**就可以实现了！

~~代码莫名其妙发不出来。。。实在有需要请私信 fzszkl ？~~

upd：机房网络修好了（？），反正代码可以发出来了，请管理员通过一下~

```cpp
#include <bits/stdc++.h>
using namespace std ;
inline int Readin() {
	register int K = 0 , F = 1 ; register char C = getchar() ;
	while( C < '0' or C > '9' ) F = C == '-' ? -1 : 1 , C = getchar() ;
	while( C <= '9' and C >= '0' ) K = ( K << 1 ) + ( K << 3 ) + C - '0' , C = getchar() ;
	return F * K ;
}
struct Queue {
	priority_queue<int> Q , D ;
	Queue () {
		while( not Q.empty() ) Q.pop() ;
		while( not D.empty() ) D.pop() ;
	}
	inline void Delete( int X ) {
		D.push( X ) ;
		while( D.top() == Q.top() ) D.pop() , Q.pop() ;
	}
	inline void Push( int X ) {
		Q.push( X ) ;
	}
	inline int Top() {
		return Q.top() ;
	}
} Q ;
int N , M ;
const int MaxM = 80000 + 5 ;
struct Node {
	int A , Num ;
} ;
Node Nod[MaxM] ;
inline bool Cmp( Node A , Node B ) {
	return A.A < B.A ;
}
long long Ans ;
int main() {
	M = ( N = Readin() ) << 1 ;
	for(register int i = 1 ; i <= N ; ++i ) {
		register int A = Readin() , B = Readin() , H = Readin() ;
		Nod[i].A = A ;
		Nod[i].Num = H ;
		Nod[i+N].A = B ;
		Nod[i+N].Num = -H ;
	}
	sort( Nod + 1 , Nod + 1 + M , Cmp ) ;
	Q.Push( 0 ) ;
	for(register int i = 1 ; i <= M ; ++i ) {
		Ans += (long long)Q.Top() * (long long)( Nod[i].A - Nod[i-1].A ) ;
		if( Nod[i].Num > 0 ) Q.Push( Nod[i].Num ) ;
		else Q.Delete( -Nod[i].Num ) ;
	}
	return not printf( "%lld\n" , Ans ) ;
}
```

---

## 作者：Snitro (赞：8)

#[http://blog.csdn.net/Fine\_rose/article/details/78320569](http://blog.csdn.net/Fine\_rose/article/details/78320569)


解题报告


首先我们思考一个特殊情况：

如果在一段区间之内，建筑的最高点是保持不变的那么在这段区间内的面积我们可以通过乘法简单的算出来


由于楼房的个数有很多，所以整个区间被分为了很多个这样的特殊情况。所以我们只需要将分割区域的关键点按照找出来即可。显而易见的是这些关键点一定位于建筑在坐标轴上的起点与终点。


得到了关键点的位置，我们只需要通过一个优先队列维护两个关键点之间最高的建筑物，并有这个最高的建筑物更新答案即可


源代码



















```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
long long ans;
int n;
struct Node {
    int begin;
    int end;
    int value;
    bool operator < (Node a) const {
        return this -> value < a.value;
    }
} nodes[40005];
int pos[80005];
priority_queue <Node> que;
bool cmp(Node a, Node b) {
    return a.begin < b.begin;
}
bool _cmp(int a, int b) {
    return a < b;
}
int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &nodes[i].begin, &nodes[i].end, &nodes[i].value);
        pos[i * 2] = nodes[i].end;
        pos[i * 2 - 1] = nodes[i].begin;
    }
    sort(pos + 1, pos + 1 + n * 2, _cmp);//按照从大到小的顺序排序关键点
    sort(nodes + 1, nodes + 1 + n, cmp);//按照左端点的顺序排序建筑物
    int put = 0;//已经放置的建筑物的个数
    for (int i = 1; i < n * 2; i++) {
        while (que.size() && que.top().end <= pos[i])//判断当前优先队列中最高的建筑物是否在范围之内
            que.pop();//若不在则出队
        while (pos[i] <= nodes[put + 1].begin && nodes[put + 1].begin < pos[i + 1])//将新出现在范围之内的建筑物入队
            que.push(nodes[++put]);
        if (que.size())//更新答案
            ans += (long long)(pos[i + 1] - pos[i]) * que.top().value;
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：2018chenyu (赞：6)

当树状数组遇上了复杂的区间操作表示无能为力，~~当你还在为树状数组常数太小而苦恼~~，不要犹豫，以线段树为武器战斗吧！！  

## 导语
相信OIers对[线段树（Segment Tree）](https://baike.baidu.com/item/%E7%BA%BF%E6%AE%B5%E6%A0%91/10983506?fr=aladdin)这一数据结构都不陌生，秉承着“常数越大责任越大”的设计理念，线段树被赋予了强大的区间操作能力，从 _简单的区间加减、到稍微复杂的区间最大公因数，从分治、Lazy标记到维护差分_ ......一坨坨~~高深莫测~~平易近人的名词逐渐成为刷题路上的常客，尚未领略 _线段树基本操作_ 之魅力的同学不妨先学习一些“入门知识”   
　　**[考古洛谷日报](https://www.luogu.org/blog/pks-LOVING/senior-data-structure-qian-tan-xian-duan-shu-segment-tree)**  
　　**[从入门到进阶](https://www.cnblogs.com/jason2003/p/9676729.html)**  
　　**[线段树详解](https://blog.csdn.net/zearot/article/details/48299459)**  

------------
## 正文
### 生动简明的思路
**本篇文章着重介绍一下“扫描线”的实战应用。**  
扫描线是一个神奇的东西，用来计算平面上多个矩形重叠后形成的“畸形”的面积、周长什么的，比如下面这四个矩形：  
![](https://cdn.luogu.com.cn/upload/image_hosting/6kn10h1p.png)  
他们重叠后的效果如下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/rs35uwt4.png)  
那么我以计算面积距离扫描线的实战应用：  
**想象有一条线从左往右扫，每遇到矩形的一条左、右边就停下来，那么显而易见地，对于任意一个矩形，先扫到其左边，再扫到其右边，即左入右出，那么效果如下：（红色为入边、蓝色为出边）**  
![](https://cdn.luogu.com.cn/upload/image_hosting/sqy8w1nq.png)  
**每扫描到一条入边后投影到总区间内，扫描到一条出边则把这条边的投影去掉，用总区间现在被覆盖的总长度 _乘_ 下一条边与当前边的横坐标差求出一块面积，把每次求得的面积相加就能得到最后的面积**  
PS：这个过程其实一点都不难，只是看文字较难体会，建议纸上画图，一画即可明白，下面献上一图希望有帮助：  
![](https://cdn.luogu.com.cn/upload/image_hosting/0di0mike.png)  
### 具体繁琐的实现
还是以“从左往右扫”进行举例，其实从哪个方向扫的道理都一样。  
**把线段树建起来，维护“总区间”，注意：线段树节点维护的是区间不是点，即：用 y 表示以 y 为下端点的纵线段，维护 [y,y] 区间指维护 [y,y+1] 这一纵线段，然而输入的是两个端点 l,r ，实际上只是 [l,r-1] 这一段纵线段，所以要减一，而在用上端点减下端点计算线段长度时应计算 r+1-l 因为端点 r 是 [r+1,\infty] 的下端点（上面这段话要好好理解）**  
**对于维护纵坐标 [l,r] 区间的线段树节点，定义 cnt,sum 两个变量，cnt 记录能够覆盖整个区间的入边条数，sum 记录这段区间被覆盖的长度，显而易见地，当处理入边时，入边覆盖的纵坐标区间 cnt+1 ,处理出边时，出边覆盖的纵坐标区间 cnt-1，维护起来不难，但是一般数据较大，所以最好打上“离散化+快读”。**  
**此处以[City Horizon](https://www.luogu.org/problem/P2061)为例题放上代码（因为有一条边一定在同一直线上，这题可以用线段并而不必面积并，但是我们还是应该试试扫描线，至于它的纵坐标区间就设为 [0,h] 即可）**  

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40010
using namespace std;
typedef long long ll;
inline ll read()
{
	ll x=0;bool f=false;
	char ch=getchar();
	while(ch<'0' || ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
//纵扫描线从左往右扫过去 
struct node{ll h,p;}e[N<<1];//输入
inline bool cmp1(node a,node b){return a.h<b.h;}
ll cnt,Y[N<<1],ys[N<<1];//离散化纵坐标(去重),映射
inline ll findpos(ll l,ll r,ll val)//找某个未离散纵坐标的排名
{
	ll mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(ys[Y[mid]]>val) r=mid-1;
		else if(ys[Y[mid]]<val) l=mid+1;
		else break;
	}
	return Y[mid];
}
struct edge{ll x,h,l,flag;}a[N<<1];
//x为横坐标,h为上端点,l为下端点,flag标记此边为入边或出边
inline bool cmp2(edge a,edge b){return a.x<b.x;}
struct segment
{//线段树[l,r]维护排名[l,r]的y坐标的区间 
	ll l,r,lc,rc,cnt,sum;
	//cnt表示覆盖[l,r]整段的入边数-出边数
	//sum表示本[l,r]内被覆盖的长度 
}tr[N<<2];ll trlen;
void bt(ll l,ll r)
{
	ll now=++trlen;
	tr[now].l=l;tr[now].r=r;
	if(l==r) tr[now].lc=tr[now].rc=-1;
	else
	{
		ll mid=(l+r)>>1;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
	}
	tr[now].cnt=tr[now].sum=0;
}
void pushUp(ll now)
{
	ll lc=tr[now].lc,rc=tr[now].rc;
    if(tr[now].cnt) tr[now].sum=ys[tr[now].r+1]-ys[tr[now].l];//整段覆盖
	else
	{
		if(tr[now].l==tr[now].r) tr[now].sum=0;//叶子
    	else tr[now].sum=tr[lc].sum+tr[rc].sum;//部分覆盖
	}
}
void update(ll now,ll l,ll r,ll val)
{
    if(l<=tr[now].l && tr[now].r<=r)
    {
        tr[now].cnt+=val;
        pushUp(now);
        return ;
    }
    ll mid=(tr[now].l+tr[now].r)>>1;
    ll lc=tr[now].lc,rc=tr[now].rc;
    if(l<=mid) update(lc,l,r,val);
    if(r>mid) update(rc,l,r,val);
    pushUp(now);//计算该区间被覆盖的总长度
}
int main()
{
	ll n=read();
	for(ll i=1;i<=n;i++)
	{
		ll x1=read(),x2=read(),h=read();
		a[i*2-1].x=x1;a[i*2].x=x2;
		e[i*2-1].h=0;e[i*2].h=h;
		e[i*2-1].p=i*2-1;e[i*2].p=i*2;
		a[i*2-1].l=a[i*2].l=0;
		a[i*2-1].h=a[i*2].h=h;
		a[i*2-1].flag=1;a[i*2].flag=-1;
	}
	sort(e+1,e+n*2+1,cmp1);Y[cnt=1]=1;
	for(ll i=2;i<=n*2;i++) if(e[i].h>e[i-1].h) cnt++,Y[cnt]=Y[cnt-1]+1,ys[Y[cnt]]=e[i].h;
	sort(a+1,a+n*2+1,cmp2);
	bt(1,Y[cnt]);
	ll ans=0;
	for(ll i=1;i<n*2;i++)
	{
		ll l=findpos(1,cnt,a[i].l),r=findpos(1,cnt,a[i].h)-1;
		update(1,l,r,a[i].flag);
		ans+=tr[1].sum*(a[i+1].x-a[i].x);//求面积
	}
	printf("%lld\n",ans);
	return 0;
}
```

------------
**再来看一道 _计算周长_ 的题目吧**  
**[picture，IOI1998](https://www.luogu.org/problem/P1856)**  
只需要想到两点即可：  
1、每个连续的纵向线段的两侧必然有2个对横向周长产生贡献的线段；  
2、纵向线段对纵向周长的贡献即为这一条边加入后（不管出边入边）总区间被线段覆盖的长度的变化。  
PS:要注意一个问题：维护连续的纵向线段时要看左右孩子能不能拼在一起  
```cpp//每个连续的横向线段的两侧必然有2个对纵向周长产生贡献的线段
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5010
#define Max 0x3f3f3f3f
using namespace std;
inline int read()
{
	int x=0;bool f=false;
	char ch=getchar();
	while(ch<'0' || ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
int cnt,Y[N<<1],ys[N<<1];
struct edge{int l,h,x,flag;}e[N<<1];
inline bool cmp(edge a,edge b) {return a.x^b.x?a.x<b.x:a.flag>b.flag;}
inline int findpos(int l,int r,int val)
{
	int mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(ys[mid]<val) l=mid+1;
		else if(ys[mid]>val) r=mid-1;
		else break;
	}
	return mid;
}
struct segment{int l,r,lc,rc,cnt,sum,lin;bool lb,rb;}tr[N<<2];int trlen;
//sum表示区间内覆盖的长度,lin表示连续的线段条数,lmin&rmax表示最左和最右的线段端点是否到达边界 
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;
	tr[now].cnt=tr[now].sum=tr[now].lin=0;
	if(l==r) tr[now].lc=tr[now].rc=-1;
	else
	{
		int mid=(l+r)>>1;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
	}
}
void pushUP(int now)
{
	int lc=tr[now].lc,rc=tr[now].rc;
	if(tr[now].cnt)
	{
		tr[now].sum=ys[tr[now].r+1]-ys[tr[now].l];
		tr[now].lin=1;tr[now].lb=tr[now].rb=true;
	}
	else if(tr[now].l==tr[now].r)
	{
		tr[now].sum=tr[now].lin=0;
		tr[now].lb=tr[now].rb=false;
	}
	else
	{
		tr[now].sum=tr[lc].sum+tr[rc].sum;
		tr[now].lin=tr[lc].lin+tr[rc].lin-(tr[lc].rb && tr[rc].lb);
		tr[now].lb=tr[lc].lb;tr[now].rb=tr[rc].rb;
	}
}
void update(int now,int l,int r,int val)
{
	if(l<=tr[now].l && tr[now].r<=r)
	{
		tr[now].cnt+=val;
		pushUP(now);
		return ;
	}
	int mid=(tr[now].l+tr[now].r)>>1;
	int lc=tr[now].lc,rc=tr[now].rc;
	if(l<=mid) update(lc,l,r,val);
	if(r>mid) update(rc,l,r,val);
	pushUP(now);
}
int main()
{
	int n=read();
	for(int i=1;i<=n;i++)
	{
		int x1=read(),y1=read(),x2=read(),y2=read();
		e[i*2-1].l=e[i*2].l=y1;
		e[i*2-1].h=e[i*2].h=y2;
		e[i*2-1].x=x1;e[i*2].x=x2;
		e[i*2-1].flag=1;e[i*2].flag=-1;
		Y[i]=y1;Y[i+n]=y2;
	}
	sort(Y+1,Y+n*2+1);ys[cnt=1]=Y[1];
	for(int i=2;i<=n*2;i++) if(Y[i]>Y[i-1]) cnt++,ys[cnt]=Y[i];
	bt(1,cnt);
	sort(e+1,e+n*2+1,cmp);
	int ans=0,lastsum=0,lastlin=0;
	for(int i=1;i<=n*2;i++)
	{
		int l=findpos(1,cnt,e[i].l),r=findpos(1,cnt,e[i].h)-1;
		update(1,l,r,e[i].flag);
		ans+=abs(tr[1].sum-lastsum);
		ans+=2*lastlin*(e[i].x-e[i-1].x);
		lastsum=tr[1].sum;
		lastlin=tr[1].lin;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：tuo3288 (赞：6)

蒟蒻题解，水平不高。

由于我不会线段树，所以苦思冥想想出了一个非线段树作法。好像跑的还快了一点。

只要把总区间分成一个个小区间，维护每个小区间的最大值就行啦！

值得注意的是，这里要对每个楼的左、右端点打上不同的记号。

废话不多说，上代码。
```cpp
#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
struct KO{
	LL place,high,sign;
};
struct node
{
    int x,y;
    bool operator < (const node & a) const
    {
        return x<a.x;
    }
}k;
priority_queue <node> q;
bool cmp(KO a,KO b)
{
	return a.place<b.place;
}
int main(int n)
{
	long long ans=0;
	scanf("%d",&n);
	bool u[n+1];
	n*=2;
	KO a[n+1];
	memset(u,true,sizeof(u));
	for(int i=1,j=1;i<=n;j++,i+=2){
		scanf("%lld%lld%lld",&a[i].place,&a[i+1].place,&a[i].high);
		a[i].sign=j;a[i+1].sign=-1*j;a[i+1].high=a[i].high;
	}
	sort(a+1,a+n+1,cmp);
	k.x=a[1].high,k.y=a[1].sign;
	q.push(k);
	for(int i=2;i<=n;i++){
		node p;
		while(q.empty()!=true){
			p=q.top();
			if(u[p.y]==false){
				q.pop();
			}
			else break;
		}
		if(q.empty()==true){
			k.x=a[i].high,k.y=a[i].sign;
			q.push(k);
			continue;
		}
		ans+=(a[i].place-a[i-1].place)*p.x;
		if(a[i].sign>0){
			k.x=a[i].high,k.y=a[i].sign;
			q.push(k);
		}
		else if(a[i].sign<0){
			u[a[i].sign*-1]=false;
		}
	}
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：hgzxwzf (赞：4)

## [P2061](https://www.luogu.com.cn/problem/P2061)

### 解题思路：
发现如果存在两个操作 $i,j$，满足 $h_i<h_j$，那么两个操作区间的并集就只需要被 $i$ 操作修改即可。

我们将所有修改操作按 $h$ 从大到小排序，那么已经被修改后的位置就不需要再进行修改了。

那么现在的问题就是怎么维护已经被修改的位置。

我们记录 $nex_i$ 表示从 $i$ 开始的第一个没有被修改的位置。

当 $i$ 被修改后，让 $nex_i$ 等于 $nex_{i+1}$。

如果直接这样做，肯定是不够的，因为 $nex_{i+1}$ 可能在后面会被修改，$nex_{i+1}$ 被修改后 $nex_i$ 也要随之修改。

考虑将思路转化。

我们可以建出一张图。

初始的，$i$ 和自己之间连一条边，等价于 $nex_i=i$。

当 $i$ 被修改后，我们就在 $i$ 和 $i+1$ 之间连边，等价于 $nex_i=nex_{i+1}$。

那么 $i$ 后面第一个没有被修改的位置就是 $i$ 所在联通块中编号最大的节点。

那么怎么维护联通块中编号最大的节点呢？

并查集！

每次连 $i$ 到 $i+1$ 的边就相当于将 $i$ 和 $i+1$ 所在集合合并，如果我们控制合并的方向，每次都是将 $i$ 所在集合合并到 $i+1$ 所在集合上，那么 $i$ 所在集合的根就是 $i$ 所在联通块编号最大的节点。

具体求答案请看代码，很好理解。

### 代码：
```cpp
const int N=4e4+10;

struct operate
{
	int l,r,x;
}op[N];

bool comp(const operate &P,const operate &Q)
{
	return P.x>Q.x;
}

int lis[N<<1],fa[N<<1],val[N<<1],tot;

int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

int main()
{
	int n;
	scanf("%d",&n);
	rep(i,1,n)
	{
		scanf("%d%d%d",&op[i].l,&op[i].r,&op[i].x);
		lis[++tot]=op[i].l;
		lis[++tot]=op[i].r;
	}
	sort(op+1,op+1+n,comp);
	sort(lis+1,lis+1+tot);
	tot=unique(lis+1,lis+1+tot)-lis-1;
	rep(i,1,tot+1) fa[i]=i;
	LL ans=0;
	rep(i,1,n)
	{
		int u=lower_bound(lis+1,lis+1+tot,op[i].l)-lis,r=lower_bound(lis+1,lis+1+tot,op[i].r)-lis;
		u=find(u);
		while(u<r)
		{
			val[u]=op[i].x;
			ans+=1ll*val[u]*(lis[u+1]-lis[u]);
			fa[u]=find(u+1);
			u=fa[u];
		}
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：Only_My_Whisper (赞：4)

其实不需要用线段树这么高级的数据结构。

可以用一个优先级队列存每一个矩形的起始点，从左到右顺推过去（程序很短）。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct line{
    long long k,h,i;
    bool operator >(line b)const{
        return h>b.h;
    }
    bool operator <(line b)const{
        return h<b.h;
    }
        //重载运算符，方便加进优先级队列中
};
int cmp(line a,line b){
    return a.i<b.i;
}
int main(){
    ios::sync_with_stdio(false);
    int n,i,j;
    cin>>n;
    line p[2*n+1];
    for(i=1;i<=n;i++){
        long long a,b,h;
        cin>>a>>b>>h;
        p[2*i-1].k=b;
        p[2*i-1].h=h;
        p[2*i-1].i=a;
        p[2*i].k=0;
        p[2*i].h=0;
        p[2*i].i=b;
    }
//以点为单位存放矩形，i，k分别代表起始和终止位置。h代表高度。
    sort(p+1,p+2*n+1,cmp);
    priority_queue<line>l1;
    l1.push(p[1]);
    unsigned long long sum=0;
    int c;
    for(i=2;i<=2*n;i++){
        while(!l1.empty()&&l1.top().k<p[i].i){
            l1.pop();
        }
//把不在范围内的矩形去除。
        if(!l1.empty()){
            c=p[i].i-p[i-1].i;
            sum+=c*l1.top().h;
        }
        if(p[i].h!=0){
            l1.push(p[i]);
        }
    }
    cout<<sum;
    return 0;
}
```

---

## 作者：Cesare (赞：4)

$update:$ 修改、增加了部分内容。

给出一种线段树的扫描线实现方法。

## $Solution$

本题运用了扫描线的思想。

什么是扫描线？

看一幅图：

![](https://s2.ax1x.com/2019/06/26/ZezIPI.png)

如果朴素的去做，我们发现需要对于每一条线都覆盖一次，取最终的覆盖结果。

但如果使用扫描线，你只需要将一条一条线扫下去，扫到两条线，一条做起点，一条做终点，将两条线之间构成的面积累加即可。

正如上图，就是按照横坐标排序，然后往后扫，线段树维护坐标 x 的下一个坐标。先将 $A,\ I$ 放入线段树，然后维护出 $A \to I$ 的长度，即线段树中的 $S_1$ ，加上四边形 $AIKO$ 的面积，然后加入点 $C,\ O$ ，继续往后扫，扫到 $B,\ J$ ，计算贡献，注意线段树要维护此时的 $S_1$ 变为 $CO$ 的长度。之后一直做下去即可。

然后考虑如何使用线段树维护长度。

我们发现一个图形面积造成的贡献的高会用到一个读入的四边形的最先读入的边，所以考虑多维护一个 $f$ 数组表示他是先读入的边还是后读入的边，如果是先读入的边就是 $1$ ，否则为 $-1$ 。

考虑维护一颗权值线段树，并在其中维护一个 $T_i$ 数组表示 $i$ 这个节点所拥有的边是先读入的边还是后读入的边，就是在 $Update$ 的时候对于当前节点做 $f_i$ 的修改，然后在 $push\ up$ 的时候判断他是否是先读入的边，是的话将 $S$ 数组更新为 $r - l + 1$ ，否则判断是否是叶子节点，如果是就置为 $0$ ，不然就正常 $push\ up$ 。

由于值域范围较大，有 $1e9$ ，所以实现的时候采用了动态开点线段树。

## $Code:$

```cpp
#include <bits/stdc++.h>
//#include"Bignum/bignum.h"
//#define lll bignum
#define lowbit(x) (x & -x)
#define debug(x) (cout << "#x = " << (x) << endl)
#define Set(x, i) memset (x, i, sizeof(x))
#define R register
#define For(i, j, k) for(R int i = (j), ED = (k); i <= ED; ++i)
#define foR(i, j, k) for(R int i = (j), ED = (k); i >= ED; --i)
#define Cross(i, j, k) for(R int i = (j); i; i = (k))
using namespace std;
typedef long long ll;
const ll N = 100011;
const ll INF = 5e16;

namespace IO {

	inline char gc() {
		static char buf[100000], *p1 = buf, *p2 = buf;
		return (p1 == p2) && (p2 = (p1 = buf) +
			fread (buf, 1, 100000, stdin), p1 == p2)? EOF: *p1++;
	}

	#define dd ch = getchar()
	inline ll read() {
		ll x = 0; bool f = 0; char dd;
		for (; !isdigit (ch); dd) f ^= (ch == '-');
		for (; isdigit (ch); dd)  x = x * 10 + (ch ^ 48);
		return f? -x: x;
	}
	#undef dd

	inline void write( ll x ) {
		if (x < 0) putchar ('-'), x = -x;
		if (x > 9) write (x / 10); putchar (x % 10 | 48);
	}

	inline void wrn ( ll x ) { write (x); putchar (' '); }

	inline void wln ( ll x ) { write (x); putchar ('\n'); }

	inline void wlnn ( ll x, ll y ) { wrn (x), wln (y); }

}

using IO::wln;
using IO::read;

namespace Segment_Tree {
	
	#define mid ((l + r) >> 1)
	
	ll root = 0;
	ll cnt = 0, T[N << 5], S[N << 5], ls[N << 5], rs[N << 5];
	
	inline void pushUp ( ll p, ll l, ll r ) {
		if (T[p]) S[p] = r - l + 1;
		else if (l == r)  S[p] = 0;
		else S[p] = S[ls[p]] + S[rs[p]];
	}
	
	inline void Update ( ll &p, ll l, ll r, ll ul, ll ur, ll k ) {
		if (!p) p = ++cnt;
		if (l >= ul && r <= ur) 
			return (void) (T[p] += k, pushUp (p, l, r));
		if (mid >= ul) Update (ls[p], l, mid, ul, ur, k);
		if (mid < ur)  Update (rs[p], mid + 1, r, ul, ur, k); 
		pushUp (p, l, r);
	}
	
}

using Segment_Tree::S;
using Segment_Tree::root;
using Segment_Tree::Update;

namespace Cesare {
		
	ll n, tot = 0, Ans = 0;
	
	struct Line {
		ll yl, yr, H, f;
		inline bool operator < ( const Line &b ) { return H < b.H; }
	} K[N];
	
	void main() {
		n = read();
		for (R int i = 1, l, r, h; i <= n; ++i) {
			l = read(), r = read(), h = read();
			K[++tot] = (Line) { 1, h, l, 1 };
			K[++tot] = (Line) { 1, h, r, -1 };
		}
		sort (K + 1, K + tot + 1);
		Update (root, 1, 1e9, K[1].yl, K[1].yr, K[1].f);
		For ( i, 2, tot ) {
			Ans += (K[i].H - K[i - 1].H) * S[1];
			Update (root, 1, 1e9, K[i].yl, K[i].yr, K[i].f);
		} wln (Ans), exit (0);
	}
	
} 

int main() 
{
	return Cesare::main(), 0;
}

/*

*/



```

---

## 作者：__hao__ (赞：4)

本弱鸡贡献一个比较垃圾的做法。

其实这题也可以不用线段树，比较”标准”的做法是线段树扫描线求矩形面积并，但这题是简化过了的。

（建议大家学习下线段树扫描线，百度即可，经典例题HDU1542)

简化过是因为在纵坐标上是从0开始的，那么维护一个高度就可以了。

然后就发现我们需要一个数据结构，它应该支持插入，删除，求最大值，于是我们就想到树之类的东西，总之时间复杂度要都是O(log n)。

因为我比较懒，就直接用了STL里面的multiset维护高度。（考虑到可能有重复的高度）

然后把一个矩形拆成两条线段，按横坐标排序，从左到右扫描一遍，遇到左边就把这个高度插入集合，遇到右边就把它踢出去，答案每次加上最大高度乘上两个节点间的x距离。

注意答案要开long long!!做加法的时候也要转一下，要不就是蜜汁60分了。

注意开节点数组要开2n。


以下是代码，仅供参考。




    
    

    
```cpp
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define maxn 80005
typedef multiset<int, greater<int> > msi;
typedef long long LL;
struct seg {
    int x, h, d;
    seg() {}
    seg(int a, int b, int c) : x(a), h(b), d(c) {}
    bool operator < (const seg& rhs) const
    {
        return x < rhs.x;
    }
} s[maxn];
int main()
{
    int n, a, b, k, i, p = 0;
    LL ans = 0;
    msi h;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d%d%d", &a, &b, &k);
        s[p++] = seg(a, k, 1);
        s[p++] = seg(b, k, 0);
    }
    sort(s, s + p);
    h.insert(0);
    for (i = 0; i < p - 1; ++i) {
        if (s[i].d)
            h.insert(s[i].h);
        else {
            msi::iterator it = h.find(s[i].h);
            h.erase(it);
        }
        ans += LL(*h.begin()) * (s[i + 1].x - s[i].x);
    }
    printf("%lld\n", ans);
}
```

---

## 作者：按Ctrl加w会AC (赞：3)

考虑离线做法

因为是将比x小的变成x,所以相当于将操作中的x从小到大排序,然后按排好的顺序对区间修改求和,由于区间比较大,动态开点即可

```cpp
#include <cstdio>
#include <algorithm>

#define MAXM 40005
typedef long long ll;

int WA;

struct TLE{
	int CE,RE,PE;
	bool operator <(const TLE OLE)const{
		return PE<OLE.PE;
	}
} MLE[MAXM];

struct SE{
	ll TAG,SUM;
	SE *lc,*rc;
	SE(){ TAG=0,SUM=0,lc=NULL,rc=NULL; }
};
SE *ROOT;

inline void Running(SE *&u){
	u->SUM=0;
	if (u->lc!=NULL) u->SUM+=u->lc->SUM;
	if (u->rc!=NULL) u->SUM+=u->rc->SUM;
}

inline void Compiling(SE *&u,int SIZE){
	if (u->TAG!=0){
		if (u->lc==NULL) u->lc=new SE();
		u->lc->TAG=u->TAG;
		u->lc->SUM=u->TAG*(SIZE-(SIZE>>1));
		if (u->rc==NULL) u->rc=new SE();
		u->rc->TAG=u->TAG;
		u->rc->SUM=u->TAG*(SIZE>>1);
		u->TAG=0;
	}
}

inline void Judging(int lx,int rx,ll x,SE *&u=ROOT,int l=1,int r=1000000000){
	if (u==NULL) u=new SE();
	if (l==lx && r==rx){
		u->TAG=x;
		u->SUM=x*(r-l+1);
		return;
	}
	Compiling(u,r-l+1);
	int mid=(r-l>>1)+l;
	if (rx<=mid) Judging(lx,rx,x,u->lc,l,mid);
	else if (mid<lx) Judging(lx,rx,x,u->rc,mid+1,r);
	else Judging(lx,mid,x,u->lc,l,mid),Judging(mid+1,rx,x,u->rc,mid+1,r);
	Running(u);
}

int main(){
	scanf("%d",&WA);
	for (int AC=1;AC<=WA;AC++){
		scanf("%d%d%d",&MLE[AC].CE,&MLE[AC].RE,&MLE[AC].PE);
	}
	std::sort(MLE+1,MLE+WA+1);
	for (int AC=1;AC<=WA;AC++){
		Judging(MLE[AC].CE,MLE[AC].RE-1,MLE[AC].PE);
//		printf("%d %d %d\n",MLE[AC].CE,MLE[AC].RE-1,MLE[AC].PE);
	}
	printf("%lld\n",ROOT->SUM);
	return 0;
}
```

---

## 作者：Chthology (赞：3)

### Multiset&离散化

---

### 思路：

把开始和结束节点离散化并排序，扫到一个节点，ans加上这个节点和上一个节点之间距离和目前所扫到建筑高度中的最高值的积（也就是multiset的首元素）（第一个节点除外）。如果这个节点是开始节点，则multiset加入节点对应矩形的高，否则multiset中删除节点对应矩形的高。扫描一遍可得正解。

---

### 程序：

```
//#define CCF
#define OLD

#ifndef CCF
    #pragma comment(linker, "/STACK:102400000,102400000")
    #ifdef OLD
        #pragma GCC diagnostic error "-std=c++11"
    #endif
    #pragma GCC optimize ("O3")
    #pragma GCC -mcmodle=large
#endif

//---------------------分割线以上无视---------------------

#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

int n;
LL ans;

struct node{
    LL h,id;
    char type;
}a[80005];

struct set_cmd{
    bool operator()(const int &x,const int &y){
        return x>y;
    }
};

multiset<LL,set_cmd> s;

inline bool sort_cmp(node x,node y){
    return x.id<y.id;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(register int i=1;i<=n;++i){
        LL x,y,z;
        cin>>x>>y>>z;
        a[2*i-1].id=x,a[2*i-1].h=z,a[2*i-1].type='a';
        a[2*i].id=y,a[2*i].h=z,a[2*i].type='b';
        //cout<<a[2*i-1].h<<' '<<a[2*i].h<<'\n';
    }
    sort(a+1,a+1+2*n,sort_cmp);
    //cout<<*s.begin()<<'\n';
    for(register int i=1;i<=2*n;++i){
        //if(s.empty()) goto P_TAG;
        ans+=(LL)(*s.begin())*(LL)(a[i].id-a[i-1].id);
        //P_TAG:
            if(a[i].type=='a') s.insert(a[i].h);
            else s.erase(s.find(a[i].h)); //multiset删除键值是把和键值相同的所有元素删除QAQ，卡了好长时间
            //cout<<*s.begin()<<'\n';
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

###### ~~以下为废话~~

- ###### 吐槽翻译，硬把题目翻成线段树

- ###### 好多dalao用线段树，然而打了好久没打出来

---

## 作者：Tgotp (赞：3)

没注意到是左闭右开区间...卡了半天。

考虑用线段树可以很好的维护区间信息，那么考虑使用线段树。

对于区间max很明显可以随便维护。

重点在于数据范围1e9，考虑离散化，

若令tru[i]表示把一个数离散成i这个数与他上一个数的差值，

那么只用在统计答案的时候再乘以这个值即可。

但是略微思考可以发现，这样会把其左端点所在位置算错（因为只有单一节点）

解决也很简单，只用把其左端点的左边一个点拉入线段树即可。

c++代码如下：

    
    
        
        
        
    
        
        
    
        
        
    
    
```cpp
    #include<bits/stdc++.h>
    #define eps 1e-9
    #define rep(i,x,y) for(register int i = x ; i <= y; ++ i)
    #define repd(i,x,y) for(register int i = x ; i >= y; -- i)
    #define size(x) ((int)s[x].size())
    #define lowbit(x) (x & - x)
    using namespace std;
    typedef long long ll; 
    template<typename T>inline void read(T&x)
    {
        x = 0;char c;int sign = 1;
        do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
        do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
        x *= sign;
    }
    const int N = 4e4 + 500, M = 2e5+500; 
    int n,tot,cnt,t[M],id[M],tru[M];
    struct Str { int l,r,w; }a[N];
    map<int,int>mp;
    struct Segment_tree
    {
        int tree[M << 2],val[M << 2];
        inline void down(int id)
        {
            val[id << 1] = max(val[id << 1],val[id]);
            val[id << 1|1] = max(val[id << 1|1],val[id]);
        }
        void update(int id,int L,int R,int l,int r,int w)
        {
            if( L == l && R == r) { val[id] = max(val[id],w);return; }
            down(id);
            int mid = L + R >> 1;
            if(r <= mid) update(id << 1,L,mid,l,r,w);
            else if(l > mid) update(id << 1|1,mid + 1,R,l,r,w);
            else update(id<<1,L,mid,l,mid,w),update(id<<1|1,mid + 1,R,mid + 1,r,w);
        }
        ll cal(int id,int L,int R)
        {
            if(L == R) return (ll)val[id] *tru[L];
            down(id);
            int mid = L + R >> 1;
            return cal(id<<1,L,mid) + cal(id<<1|1,mid + 1,R);
        }
    }seg;
    int main()
    {
        read(n);
        rep(i,1,n)
        {
            int l,r,w;
            read(a[i].l);read(a[i].r);read(a[i].w); a[i].r--;
            t[++tot] = a[i].l;t[++tot] = a[i].r;t[++tot] = a[i].l - 1;
        }
        sort(t + 1,t + 1 + tot);
        rep(i,1,tot)
            if(t[i - 1] != t[i]) 
            {
                tru[++cnt] = t[i] - t[i - 1];
                mp[t[i]] = cnt;
            }
        rep(i,1,n)
            seg.update(1,1,cnt,mp[a[i].l],mp[a[i].r],a[i].w);
        cout << seg.cal(1,1,cnt) << endl;
        return 0;
    }

```

---

## 作者：pinkex (赞：3)

让我来贴一个题解~~~我们可以这样来想——从1~2，2~3，3~4这样每个单位长度上都有最高高度，那么ans=minp\*h[minp]+(minp+1)\*h[minp+1]+……+(maxp-1)\*h[maxp-1]+maxp\*h[maxp]。但是我们发现minp和maxp的跨度太大了，高达10^9，完全承受不住。但是我们先不考虑这个问题，我们可以考虑一下上面这个问题可以怎么来解？每一条线段都有自己的最高高度，也就是权值呗。那么不就是线段树中的cover域吗！那么这就好办了：造一棵minp~maxp的线段树，L，R域分别表示其左端点和右端点，c表示当前线段上的最高高度是多少。那么我们接着考虑离散。如何离散呢？我们要想到，左边界和右边界的性质到最后其实是一样的，无非就是一个个分界点。那么，我们就拥有了2\*n个分界点。我们把这些分解点排一趟序后，我们就可以得到每个点离散后的序号了（ST数组里面的L，R就是用序号来标记的）。Build没什么，Alter呢？Alter修改区间。如果(ST[num].L>=lft&&ST[num].R<=rgt)即当前线段被目标线段覆盖，则ST[num].c=max(ST[num].c,hgt)。然后我们就要分情况修改区间。Seek呢？也是查询区间。不过我们要返回谁的cover域呢？当然是单调线段了，这样才能确保线段上的高度唯一，不会参差不齐。那么返回的应该是这段线段的实际长度\*高度，即(a[ST[num].R]-a[ST[num].L])\*ST[num].c。但是我们会发现还是有问题：最后2个点TLE。为什么呢？问题主要出在(ST[num].L>=lft&&ST[num].R<=rgt)身上。我们需要调的次数实在太多了。所以我们需要掌握一个技巧叫做“延迟修改”。所谓延迟修改，就是当前做个标记，先不向下传递，而是在询问时顺便传递下去。标准的是pushdown和pushup。但是对于这题有个更快的方法，思路确实一样的——我们在Alter里面的那一句话改成——if (ST[num].L>=lft&&ST[num].R<=rgt){ST[num].H=max(ST[num].H,hgt);return;}我们这个return很好的加快了效率，即我们只在最上层即最早修改的地方做个标记，暂时不要向下传。在Seek时，如果没有到底层，那么再向下传递信息，即——ST[num\*2].c=max(ST[num\*2].c,ST[num].c); ST[num\*2+1].c=max(ST[num\*2+1].c,ST[num].c);这就具有了pushdown的功能。那么现在，这个效率就变的很高了。还有要注意数据类型哦。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=40005;
int n,len0,len1;
int a[maxn*2],x[maxn],y[maxn],z[maxn];
struct segT{
    int L,R,c;
}ST[maxn*4*2];
inline int read(){
    int x=0; char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x;
}
void Build(int num,int lft,int rgt){
    ST[num].L=lft,ST[num].R=rgt;
    if (lft+1==rgt) ST[num].c=0;
    else{
        int mid=(lft+rgt)>>1;
        Build(num*2,lft,mid);
        Build(num*2+1,mid,rgt);
    }
}
void Alter(int num,int lft,int rgt,int hgt){
    if (ST[num].L>=ST[num].R) return;
    if (ST[num].L>=lft&&ST[num].R<=rgt){ST[num].c=max(ST[num].c,hgt); return;}
    int mid=(ST[num].L+ST[num].R)>>1;
    if (rgt<=mid) Alter(num*2,lft,rgt,hgt);
    else if (lft>=mid) Alter(num*2+1,lft,rgt,hgt);
    else {Alter(num*2,lft,mid,hgt); Alter(num*2+1,mid,rgt,hgt);}
}
long long Seek(int num,int lft,int rgt){
    if (ST[num].L+1==ST[num].R) return (long long)ST[num].c*(a[ST[num].R]-a[ST[num].L]);
    ST[num*2].c=max(ST[num*2].c,ST[num].c); ST[num*2+1].c=max(ST[num*2+1].c,ST[num].c);
    int mid=(ST[num].L+ST[num].R)>>1;
    if (rgt<=mid) return Seek(num*2,lft,rgt);
    else if (lft>=mid) return Seek(num*2+1,lft,rgt);
    else return Seek(num*2,lft,mid)+Seek(num*2+1,mid,rgt);
}
int BinFind(int x){
    int L=1,R=n<<1;
    while (L<=R){
        int mid=(L+R)>>1;
        if (a[mid]==x) return mid;
        if (a[mid]>x) R=mid-1; else if (a[mid]<x) L=mid+1;
    }
}
int main(){
    n=read(); Build(1,1,n<<1);
    for (int i=1; i<=n; i++){
        x[i]=read(),y[i]=read(),z[i]=read();
        a[(i<<1)-1]=x[i],a[i<<1]=y[i];
    }
    sort(a+1,a+1+(n<<1));
    for (int i=1; i<=n; i++) x[i]=BinFind(x[i]),y[i]=BinFind(y[i]);
    for (int i=1; i<=n; i++) Alter(1,x[i],y[i],z[i]);
    printf("%lld",Seek(1,1,n<<1));
    return 0;
}
```

---

## 作者：Setsugesuka (赞：2)

首先，题目可以转化为每次将一段区间 $[l,r]$ 中 $<v$ 的数变成 $v$ 。这是一个很显然的区间推平，我们可以用 $ODT$ 来快速地解决这类问题。

于是我写了一个 $ODT$ 它 $TLE$ 了。

仔细思考，发现每次把一段区间增高并不能保证区间数量不会增加的太多。考虑优化，注意到题目只有增高区间这一操作，并且交换任意两个增高的操作并不会对答案造成影响。很自然地想到将所有操作存起来，从小到大排序，每次取出一个操作，把 $[l,r]$ 区间推平为 $v$ ，很快就能解决了。

遗憾的是因为我的码风太丑常数太大程序只能跑 $76ms$ 。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline void write(T x)
{
    if(x>9)
    {
        write(x/10);
    }
    putchar(x%10+'0');
}

inline char nc()
{
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}

inline void read(int &sum)
{
    char ch=nc();
    int tf=0;
    sum=0;
    while((ch<'0'||ch>'9')&&(ch!='-')) ch=nc();
    tf=((ch=='-')&&(ch=nc()));
    while(ch>='0'&&ch<='9') sum=sum*10+(ch-48),ch=nc();
    (tf)&&(sum=-sum);
}

struct node
{
    int l,r;
    mutable long long v;
    node() {}
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    inline bool operator <(const node &o) const
    {
        return l<o.l;
    }
};

set<node> s;

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos) return it;
    --it;
    int L=it->l,R=it->r;
    long long V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,long long v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

inline void query(int l,int r)
{
    long long ret=0;
    for(set<node>::iterator it=s.begin();it!=s.end();++it)
    {
        ret+=it->v*(it->r-it->l+1);
    }
    write(ret);
}

struct ask
{
    int l,r,v;
    inline bool operator <(const ask &o) const
    {
        return v<o.v;
    }
};

int n;
ask asks[100010];

int main()
{
    s.insert(node(1,1000000000,0));
    read(n);
    for(register int i=1;i<=n;++i)
    {
        read(asks[i].l),read(asks[i].r),read(asks[i].v);
        asks[i].r--;
    }
    sort(asks+1,asks+1+n);
    for(register int i=1;i<=n;++i)
    {
        assignval(asks[i].l,asks[i].r,asks[i].v);
    }
    query(1,1000000000);
    return 0;
}
```


---

## 作者：913887524gsd (赞：2)

一道经典的线段树+离散化。我们可以把每一个操作离散成三个点：a，b，b-1（题目里要求改变的区间为[a_i,b_i)即[a_i,b_i-1]）。然后按照常规的离散化就可以了。b这个点是判断是否在b这个点高度为0，以防加多了。详细的在下面代码处解释。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ls(x) x<<1
#define rs(x) x<<1|1
using namespace std;
typedef long long ll;
const int N=1e5+1;
ll ans[N<<2],tag[N<<2],sum,last,pos;
int m,n,t,size;
struct node{
    int x,y,h;
    bool operator<(const node b)const
    {
        return h<b.h;
    }
}e[N];int a[N<<1];

template<typename T>
inline void re(T &N)
{
    char c; while((c=getchar())< '0'||c> '9');
    N=c-'0';while((c=getchar())>='0'&&c<='9')N=N*10+c-'0';
}
inline void f(int p,int l,int r,int k)
{
    ans[p]=k;tag[p]=k;
}
inline void push_down(int p,int l,int r)
{
    if(tag[p])
    {
        int mid=(l+r)>>1;
        f(ls(p),l,mid,tag[p]);
        f(rs(p),mid+1,r,tag[p]);
        tag[p]=0;
    }
}
void update(int p,int l,int r,int x,int y,int k)
{
    if(x<=l&&r<=y){ans[p]=k;tag[p]=k;return;}
    push_down(p,l,r);
    int mid=(l+r)>>1;
    if(x<=mid)update(ls(p),l,mid,x,y,k);
    if(mid< y)update(rs(p),mid+1,r,x,y,k);
}
ll  query(int p,int l,int r,int x,int y)
{
    ll s=0;
    if(x<=l&&r<=y)return ans[p];
    push_down(p,l,r);
    int mid=(l+r)>>1;
    if(x<=mid)s+=query(ls(p),l,mid,x,y);
    if(mid <y)s+=query(rs(p),mid+1,r,x,y);
    return s;
}
int main()
{
    //freopen("data.txt","r",stdin);
    re(n);
    for(int i=1;i<=n;i++)re(e[i].x),re(e[i].y),re(e[i].h),
    a[++t]=e[i].x,a[++t]=e[i].y-1,a[++t]=e[i].y,e[i].y--;
    sort(a+1,a+3*n+1);sort(e+1,e+n+1);//对高度进行sort方便从小到大更新区间
    size=unique(a+1,a+3*n+1)-a-1;//unique去重函数
    for(int i=1;i<=n;i++)
    {
        int x=lower_bound(a+1,a+size+1,e[i].x)-a;//lower_bound函数找到值
        int y=lower_bound(a+1,a+size+1,e[i].y)-a;
        update(1,1,size,x,y,e[i].h);
    }
    last=query(1,1,size,1,1);pos=1;
    for(int i=2;i<=size;i++)
    {
        ll x=query(1,1,size,i,i);
        if(x!=last)sum+=(a[i]-a[pos])*last,last=x,pos=i;//这里采取贪心做法，如果遇到高度不一样的再更新答案
    }
    printf("%lld\n",sum);
    return 0;
}
```

---

## 作者：aiyougege (赞：2)

#### Solution
　　这个题我用了一个非常暴力但是非常好写的线段树.有多暴力呢?标记根本不下放, 查询是单点查询, 幸好这道题只有一次查询……

　　首先离散化是少不了的, 这部分的代码在这里
```c++
struct Query{
    int L,R,l,r,s;
    void read(){scanf("%d%d%d",&l,&r,&s);}
}f[N];
/*****************/
	for(int i=1;i<=n;++i){
		f[i].read();
        sor[++cnt]=f[i].l,sor[++cnt]=f[i].r;
	}
    sort(sor+1,sor+cnt+1);
    for(int i=1;i<=cnt;++i){
        if(!m.count(sor[i]))
            m[sor[i]]=++tot,Rnk[tot]=sor[i];
    }
```
　　建立线段树, 但是树上的每一个点实际上是代表这离散后的一个最小的区间.

　　然后一个点的标记表示这段区间内的最小值.所以更新一个区间的复杂度只有$O(log_2 N)$.

　　这样非常好实现但是坏处是无法区间查询, 因为查询一个点的值时需要从树根查询到叶子节点才能确定这个点的值, 因此每次查询为$O(log_2 N)$, 有n个点, 一次查询的总复杂度为$O(Nlog_2 N)$.但是发现N的值最大到$80000$（考虑每个区间互相不相交）, 因此也可以接受.
#### Code
```c++
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<map>
#define N 200005
using namespace std;


int sor[N],cnt,tot;
int Rnk[N];
map<int,int>m;

    struct Node{
        int f;Node *ls,*rs;
        Node(){ls=NULL,rs=NULL;}
        void update(){f=ls->f+rs->f;}
    }pool[N<<1];
    Node* new_Node(){
        static int cnt=0;
        return &pool[cnt++];
    }
    void build(int l,int r,Node* now){
        if(l==r)return ;
        int mid=(l+r)>>1;
        now->ls=new_Node();now->rs=new_Node();
        build(l,mid,now->ls);
        build(mid+1,r,now->rs);
        now->update();
    }
  void modify(int l,int r,int L,int R,int s,Node* now){
        int mid=(l+r)>>1;
        if(L<=l&&r<=R){
            now->f=max(now->f,s);return ;
        }
        if(L<=mid)
            modify(l,mid,L,R,s,now->ls);
        if(R>mid)
            modify(mid+1,r,L,R,s,now->rs);
    }
    int query(int l,int r,int k,Node *now){
        if(l==r)return now->f;
        int mid=(l+r)>>1;
        if(k<=mid)return max(now->f,query(l,mid,k,now->ls));
        if(k>mid)return max(now->f,query(mid+1,r,k,now->rs));
    } 

struct Query{
    int L,R,l,r,s;
    void read(){scanf("%d%d%d",&l,&r,&s);}
}f[N];

main(){
    int n,l,r,s;Node* root=new_Node();
    scanf("%d",&n);
    for(int i=1;i<=n;++i){f[i].read();sor[++cnt]=f[i].l,sor[++cnt]=f[i].r;}
    sort(sor+1,sor+cnt+1);
    for(int i=1;i<=cnt;++i){
        if(!m.count(sor[i]))
            m[sor[i]]=++tot,Rnk[tot]=sor[i];
    }
    build(1,tot-1,root);
    map<int,int>::iterator it;
    for(int i=1;i<=n;++i){
        it=m.find(f[i].l),f[i].L=it->second,
        it=m.find(f[i].r),f[i].R=it->second;
    }
    for(int i=1;i<=n;++i)
        modify(1,tot-1,f[i].L,f[i].R-1,f[i].s,root);
    long long ans=0,tm;
    for(int i=1;i<tot;++i){
        tm=(long long)query(1,tot-1,i,root)*(Rnk[i+1]-Rnk[i]);
        ans+=tm;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Mogician (赞：2)

贴一个splay版题解，思路跟线段树扫描线差不多，只是用splay来维护最大值（用线段树的话大多数时候都要访问叶子节点来修改，时间复杂度太高），遇到一栋楼房就把其高度加到splay里，离开一栋楼房就删除其高度，每当做这两次操作时ans+=当前最大高度\*（当前位置-上一次操作位置）。最后记得用long long。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct data
{
    long long wz,key,hi;
}f[100000];
long long i,j,k,t,m,n,p,ans,last;
long long fa[100000],ch[100000][2],key[100000],cnt[100000],siz[100000],sz,root;
bool comp(data a,data b)
{
    return (a.wz<b.wz);
}
void clear(int x)
{
    ch[x][0]=ch[x][1]=fa[x]=cnt[x]=key[x]=siz[x]=0;
}
int getson(int x)
{
    return ch[fa[x]][1]==x;
}
void update(int x)
{
    siz[x]=cnt[x];
    if (ch[x][0]) siz[x]+=siz[ch[x][0]];
    if (ch[x][1]) siz[x]+=siz[ch[x][1]];
}
void create(int x)
{
    sz++;
    ch[sz][0]=ch[sz][1]=fa[sz]=0;
    key[sz]=x;
    cnt[sz]=1;
    siz[sz]=1;
}
void rotate(int x)
{
    int father=fa[x],fafa=fa[father],k=getson(x);
    ch[father][k]=ch[x][k^1]; fa[ch[father][k]]=father;
    ch[x][k^1]=father; fa[father]=x;
    fa[x]=fafa;
    if (fafa)
        ch[fafa][ch[fafa][1]==father]=x;
    update(father); update(x);
}
void splay(int x)
{
    for (int father;father=fa[x];rotate(x))
        if (fa[father])
            rotate(getson(x)==getson(father)?father:x);
    root=x;
}
void insert(int x)
{
    if (!root) create(x),root=sz;
    else
    {
        int now=root,father=0;
        while (1)
        {
            if (key[now]==x)
            {
                cnt[now]++;
                update(now); update(father);
                splay(now);
                break;
            }
            father=now;
            now=ch[father][x>key[father]];
            if (!now)
            {
                create(x);
                fa[sz]=father;
                ch[father][x>key[father]]=sz;
                update(father);
                splay(sz);
                break;
            }
        }
    }
}
int ma()
{
    int now=root;
    while (ch[now][1]) now=ch[now][1];
    return key[now];
}
int findpos(int x)
{
    int now=root,ans=0;
    while (1)
    {
        if (x<key[now])
            now=ch[now][0];
        else
        {
            ans+=ch[now][0]?siz[ch[now][0]]:0;
            if (x==key[now])
            {
                splay(now);
                return ans+1;
            }
            ans+=cnt[now];
            now=ch[now][1];
        }
    }
}
int pre()
{
    int now=ch[root][0];
    while (ch[now][1])
        now=ch[now][1];
    return now;
}
void del(int x)
{
    int t=findpos(x);
    if (cnt[root]>1)
    {
        cnt[root]--;
        update(root);
        return;
    }
    if (!ch[root][0] && !ch[root][1])
    {
        clear(root);
        root=0;
        return;
    }
    if (!ch[root][1])
    {
        int temp=root;
        root=ch[root][0];
        fa[root]=0;
        clear(temp);
        return;
    }
    else
    if (!ch[root][0])
    {
        int temp=root;
        root=ch[root][1];
        fa[root]=0;
        clear(temp);
        return;
    }
    int prel=pre(),temp=root;
    splay(prel);
    fa[ch[temp][1]]=root;
    ch[root][1]=ch[temp][1];
    clear(temp);
    update(root);
}
int main()
{
 //   freopen("1.in","r",stdin);
  //  freopen("1.out","w",stdout);
    scanf("%lld",&n);
    for (i=1;i<=n;i++) {scanf("%lld%lld%lld",&f[2*i-1].wz,&f[2*i].wz,&f[2*i-1].hi); f[2*i-1].key=1; f[2*i].key=-1; f[2*i].hi=f[2*i-1].hi;}
    sort(f+1,f+2*n+1,comp);
    insert(f[1].hi);
    for (i=2;i<=2*n;i++)
    {
        ans+=ma()*(f[i].wz-f[i-1].wz);
        if (f[i].key==-1) del(f[i].hi); else insert(f[i].hi);
    }
    printf("%lld",ans);
  //  fclose(stdin);
  //  fclose(stdout);
    return 0;
}
```

---

