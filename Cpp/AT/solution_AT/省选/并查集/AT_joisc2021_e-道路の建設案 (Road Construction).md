# 道路の建設案 (Road Construction)

## 题目描述

JOI 国是一个 $x\times y$ 的二维平面，王国里有 $n$ 个城镇，分别编号为 $1, 2, \cdots, n$，其中第 $i$ 个城镇的 **坐标** 为 $(x_i, y_i)$。

在 JOI 国，正计划修建连接两座城镇的路（下文简称：**「修路的项目」**），路有 $k$ 条。连接两个不同的城镇 $a$ 和 $b$ 将花费 $|x_a − x_b| + |y_a − y_b|$ 元。若有一条连接 $c$，$d$ 的路，则不需要也不可以在建一条连接 $d$，$c$ 的路，因为它们是相同的。

你要管理这个「修路的项目」，为了计算花费情况，你得弄明白连接一些城镇所需的花费。在这 $\dfrac{n\cdot(n-1)}{2}$ 条道路中，你想了解最便宜的 $k$ 条道路的花费。

给你城镇的坐标以及 $k$，请计算最便宜的 $k$ 条路所需要的钱。


接下来的第 $2 \sim n+1$ 行，每行 $2$ 个正整数，分别是 $x_i$ 和 $y_i$，其中 $1\le i \le n$，表示第 $i$ 个城镇的坐标。

## 说明/提示

#### 样例 #1 解释
有 $\dfrac{3 \times 2}{2} = 3$ 种方案。

- 城镇 $1 \to$ 城镇 $2$，$|(-1)-0|+|0-2| = 3$ 日元。
- 城镇 $1 \to$ 城镇 $3$，$|(-1)-0|+|0-0| = 1$ 日元。
- 城镇 $2 \to$ 城镇 $3$，$|0-0|+|2-0| = 2$ 日元。

将其进行排序为 $1,2,3$，所以输出是 $1$ 和 $2$。

本样例满足 Subtask $1, 4, 5, 6$。

#### 样例 #2 解释

有 $\dfrac{5 \times 4}{2} = 10$ 种方案。

将钱数排序后是 $2, 2, 3, 3, 3, 3, 4, 4, 4, 4$。

本样例满足 Subtask $1, 4, 5, 6$。

#### 样例 #3 解释

本样例满足 Subtask $1, 2, 4, 5, 6$。

#### 样例 #4 解释

本样例满足 Subtask $1, 4, 5, 6$。

#### 数据范围与约定

对于 $100\%$ 的数据：
- $2 \le n \le 2.5 \times 10^5$；
- $1 \le k \le \min(2.5\times 10^5,\ \dfrac{n\cdot(n-1)}{2}$)；
- $-10^9 \le x_i, y_i \le 10^9$，且 $1 \le i \le n$；
- $(x_i,y_i)\not = (x_j, y_j)$ 且 $1 \le i < j \le n$。


本题译自 [第２０回日本情報オリンピック 2020/2021春季トレーニング合宿 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [競技 2 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day2/2021-sp-d2-notice.pdf) [T2 日文题面](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day2/road_construction.pdf)。

# 题解

## 作者：Melo_DDD (赞：2)

好题！坑题！

前置知识：曼哈顿转切比雪夫。很好理解，不再赘述。

转化完之后，考虑使用二分法求出第 $k$ 小的距离 $ans$。操作步骤如下（假设当前二分的值是 $mid$）：

注意到切比雪夫距离 $\max(|x_1-x_2|,|y_1-y_2|)\le mid$ 的充要条件是 $|x_1-x_2|\le mid$ 且 $|y_1-y_2|\le mid$，接下来想办法把两条限制消除一个。

那么可以首先把所有点按照横坐标排序，保证单调不降。接下来扫一遍所有的点，对于当前点 $i$，把它**前面**的满足条件 $|x_i-x_j|\le mid$ 的点 $j$ 加入一个 set 里面，这是横坐标满足条件的。接下来在这个范围内找到纵坐标满足条件的，这个条件等价于 $y_i-mid\le y_j\le y_i+mid$，利用 set 的有序性可以很方便的查找。

为什么只算前面的啊？因为这样可以保证一个点对的答案会且仅会被靠后的点计算到，不重不漏。

这样找到了所有距离小于等于 $mid$ 的点对了，把他们统一存进一个数组里面，如果个数大于等于 $k$，那么合法，将距离向小计算；否则向大。

接下来是踩坑时间。首先放上代码：


```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ; i <= (n) ; i += (x))
using cint = const int ; using ll = long long ;

template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ; char ch = getchar () ;
	while (! isdigit (ch))
	{ flag = ch == '-' ; ch = getchar () ;}
	while (isdigit (ch))
	{ x = (x << 1) + (x << 3) + (ch ^ 48) ; ch = getchar () ;}
	flag ? x = - x : 0 ;
} template < typename T ,typename ...Args > 
inline void read ( T &x ,Args &...tmp ) { read (x) ,read (tmp...) ;}

cint N = 3e5 + 7 ; const ll inf = -8000000007ll ;
int n ,k ,tot ; ll ans[N] ;
struct point {
	ll x ,y ;
	bool operator < (const point &cmp) 
	const { return y < cmp.y ;}
} p[N] ;
using iter = std :: multiset < point > :: iterator ;
inline bool cmp (const point & ,const point &) ;

inline bool check (const ll) ;

int main () {
	read (n ,k) ;
	f (i ,1 ,n ,1) {
		ll x ,y ; read (x ,y) ;
		p[i] = (point) {x - y ,x + y} ; // 转切比雪夫
	} std :: sort (p + 1 ,p + n + 1 ,cmp) ;
	
	ll l = 0ll ,r = - inf ,mid ,res ;
	while (l <= r) {
		mid = l + r >> 1 ;
		if (check (mid)) r = mid - 1 ,res = mid ;
		else l = mid + 1 ;
	} check (res - 1) ;
	std :: sort (ans + 1 ,ans + tot + 1) ;
	int i ;
	for (i = 1 ; i <= tot ; i ++) 
		std :: cout << ans[i] << '\n' ;
	for(; i <= k ; i ++) std :: cout << res << '\n' ;
	return 0 ;
}

inline bool cmp (const point &x ,const point &y) 
{ return x.x < y.x ;}

inline bool check (const ll mid) {
	tot = 0 ;
	static std :: queue < int > q ;
	static std :: multiset < point > se ;
	while (! q.empty ()) q.pop () ; se.clear () ;
	f (i ,1 ,n ,1) {
		while (! q.empty () && p[i].x - p[q.front ()].x > mid) {
			iter it = se.find (p[q.front ()]) ; se.erase (it) ;
			q.pop () ; // 用队列维护有多少的点在集合里面
		} iter it ; 
		if (se.empty ()) goto her ; 
		it = se.lower_bound ((point) {inf ,p[i].y - mid}) ;
		for ( ; it != se.end () && it -> y <= p[i].y + mid ; it ++) {
			ans[++ tot] = std :: max 
			(std :: abs (p[i].x - it -> x) ,std :: abs (p[i].y - it -> y)) ;
			if (tot >= k) return true ;
		} her : ;
		se.insert (p[i]) ;
		q.push (i) ;
	} return false ;
}
```
然后你发现我的二分写的非常繁琐啊，我也这么觉得。然后你可能直接把 ``check (res - 1)`` 和后面的那一坨东西改成 ``check (res)`` 然后直接把 ``ans`` 数组输出了。

然后你错了一些点。

这不显然是不行的，因为我们有 ``if (tot >= k) return true ;`` 的剪枝过程，这就导致你在搜索 $res$ 的时候可能确实搜出来了 $k$ 个距离小于它的点对，但是不是最小的，后面有的更小的没有放进去就直接返回了。

``check (res - 1)`` 的正确性？

注意到因为 ``check (res - 1) < k``，所以此时一定把所有的答案全部搜出来了，且他们是最小的。又因为 ``check (res) >= k``，所以一定可以用 $res$ 这个值把剩下的补完。

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_joisc2021_e )

# 前置知识

[K-D Tree](https://oi-wiki.org/ds/kdt/)

# 解法

观察到所求是一个邻域查询的形式，尝试使用 KD-Tree，但需注意最坏时间复杂度并不正确（因为本题数据稍弱所以可以通过）。

同 [luogu P2093 [国家集训队] JZPFAR](https://www.luogu.com.cn/problem/P2093)，不妨开一个大小为 $2k$ 的堆加入答案时不断和堆顶比较，在输出答案时跳着取答案。

启发式搜索时估价函数取到子矩形的最近距离即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll inf=0x7f7f7f7f7f7f7f7f;
struct node
{
	int pos[2];
}a[250010];
int cur,cnt=0;
ll ans[250010];
priority_queue<ll>q;
bool cmp(node x,node y)
{
	return x.pos[cur]<y.pos[cur];
}
ll get_dis(int x,int y)
{
	return llabs(a[x].pos[0]-a[y].pos[0])+llabs(a[x].pos[1]-a[y].pos[1]);
}
struct KDT
{
	int root;
	struct kd_tree
	{
		int ls,rs,pos[2],mx[2],mn[2];
	}tree[250010];
	#define lson(rt) (tree[rt].ls)
	#define rson(rt) (tree[rt].rs)
	int build_rt(int id)
	{
		int rt=id;
		lson(rt)=rson(rt)=0;
		for(int i=0;i<=1;i++)
			tree[rt].pos[i]=tree[rt].mx[i]=tree[rt].mn[i]=a[id].pos[i];
		return rt;
	}
	void pushup(int rt)
	{
		for(int i=0;i<=1;i++)
		{
			tree[rt].mx[i]=tree[rt].mn[i]=tree[rt].pos[i];
			if(lson(rt)!=0)
			{
				tree[rt].mx[i]=max(tree[rt].mx[i],tree[lson(rt)].mx[i]);
				tree[rt].mn[i]=min(tree[rt].mn[i],tree[lson(rt)].mn[i]);
			}
			if(rson(rt)!=0)
			{
				tree[rt].mx[i]=max(tree[rt].mx[i],tree[rson(rt)].mx[i]);
				tree[rt].mn[i]=min(tree[rt].mn[i],tree[rson(rt)].mn[i]);
			}
		}
	}
	void build(int &rt,int l,int r,int dir)
	{
		int mid=(l+r)/2;  cur=dir;
		nth_element(a+l,a+mid,a+r+1,cmp);  rt=build_rt(mid);
		if(l<=mid-1)  build(lson(rt),l,mid-1,dir^1);
		if(mid+1<=r)  build(rson(rt),mid+1,r,dir^1);
		pushup(rt);
	}
	ll cost(int rt,int pos)
	{
		ll ans=0;
		for(int i=0;i<=1;i++)
		{
			if(a[pos].pos[i]<tree[rt].mn[i])  ans+=tree[rt].mn[i]-a[pos].pos[i];
			if(a[pos].pos[i]>tree[rt].mx[i])  ans+=a[pos].pos[i]-tree[rt].mx[i];
		}
		return ans;
	}
	void query(int rt,int l,int r,int pos)
	{
		int mid=(l+r)/2;
		if(rt!=pos&&get_dis(rt,pos)<q.top())
		{
			q.pop();  q.push(get_dis(rt,pos));
		}
		ll fl=((l<=mid-1)?cost(lson(rt),pos):inf);
		ll fr=((mid+1<=r)?cost(rson(rt),pos):inf); 
		if(fl<q.top()&&fr<q.top())
		{
			if(fl<fr)
			{
				query(lson(rt),l,mid-1,pos);
				if(fr<q.top())  query(rson(rt),mid+1,r,pos);
			}
			else
			{
				query(rson(rt),mid+1,r,pos);
				if(fl<q.top())  query(lson(rt),l,mid-1,pos);
			}
		}
		else  if(fl<q.top())  query(lson(rt),l,mid-1,pos);
		else  if(fr<q.top())  query(rson(rt),mid+1,r,pos);
	}
}K;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int n,k,i;
	cin>>n>>k;  k*=2;
	for(i=1;i<=n;i++)  cin>>a[i].pos[0]>>a[i].pos[1];
	for(i=1;i<=k;i++)  q.push(inf);
	K.build(K.root,1,n,0);
	for(i=1;i<=n;i++)  K.query(K.root,1,n,i);
	for(i=k;i>=1;i--)
	{
		ans[i]=q.top();  q.pop();
	}
	for(i=1;i<=k;i+=2)  cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：lsj2009 (赞：0)

### Solution

比较暴力的 2log 做法，但是经过各种卡常成功过了。

我们考虑开一个优先队列装一个三元组 $(i,k,val_k)$ 表示距离点 $(x_i,y_i)$ 第 $k$ 远的点距离为 $val_k$，然后每次取出 $val$ 最小的点，然后再把 $(i,k+1,val_{k+1})$ 塞进去即可。

需要注意的一点是，这样子一条线段 $(x_i,y_i)-(x_j,y_j)$ 会被记两遍，但是我们实际上只能输出一遍，解决方案是，我们只输出第奇数次取出的 $val$ 即可。

则现在关键问题是，然后找到距离点 $(x,y)$ 第 $k$ 远的点。

我们考虑曼哈顿转切比雪夫，然后二分，看一下 $[x-mid,x+mid]-[y-mid,y+mid]$ 间是否有 $\ge k$ 个点，主席树显然能做。

然后就做完了，复杂度 $\Theta((n+k)\log{V}\log{n})$。

再说一下如何卡常：

1. 超级快读 & 快输。
2. 查询 $[x-mid,x+mid]-[y-mid,y+mid]$ 点的数量时要把两个历史版本的树同时递归，这样子能少 $\frac{1}{2}$ 的常数。
3. 对于每个节点记一个值 $f$ 表示距离第 $k$ 远的点的距离，下一次二分就从 $l=f$ 开始。
4. 同理记一下距离的 $k+1$ 远的点的上限 $g$，下一次二分从 $r=g$ 开始。
5. 开 C++98。

然后就能过了！

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define uint unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
void file_IO() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N=2.5e5+5;
namespace IO {
	char Is[(1<<21)+10],Os[(1<<21)+10];
	int Ipt,Opt;
	inline char gc() {
		if(Ipt==1<<21)
			Ipt=0;
		if(!Ipt)
			Is[fread(Is,1,1<<21,stdin)]=0;
		return Is[Ipt++];
	}
	inline void flush() {
		fwrite(Os,1,Opt,stdout);
		Opt=0;
	}
	inline void pc(char x) {
		if(Opt==1<<21)
			flush();
		Os[Opt++]=x;
	}
	inline int read() {
		int x=0,f=1;
		char ch=gc();
		while(ch<'0'||ch>'9') {
			if(ch=='-')
				f=-1;			
			ch=gc();
		}
		while(ch<='9'&&ch>='0')
			x=x*10+ch-'0',ch=gc();
		return x*f;
	}
	void write(ll x) {
		if(x>9)
			write(x/10);
		pc(x%10+48);
	}
}
using namespace IO;
PII a[N];
int n,k,t[N],t1[N],p[N],len;
inline int get_id(int x) {
	return lower_bound(t+1,t+len+1,x)-t;
}
struct PSGT {
	struct node {
		int lson,rson,val;
	}; node tree[N*20];
	int p;
	inline int new_node(int k) {
		tree[++p]=tree[k];
		return p;
	}
	void update(int &k,int l,int r,int qx,int val) {
		k=new_node(k);
		tree[k].val+=val;
		if(l==r)
			return;
		int mid=l+((r-l)>>1);
		if(qx<=mid)
			update(tree[k].lson,l,mid,qx,val);
		else
			update(tree[k].rson,mid+1,r,qx,val);
	}
	int query(int kl,int kr,int l,int r,int ql,int qr) {
		if(!(tree[kr].val-tree[kl].val))
			return 0;
		if(ql<=l&&r<=qr)
			return tree[kr].val-tree[kl].val;
		int mid=l+((r-l)>>1),res=0;
		if(ql<=mid)
			res=query(tree[kl].lson,tree[kr].lson,l,mid,ql,qr);
		if(qr>=mid+1)
			res+=query(tree[kl].rson,tree[kr].rson,mid+1,r,ql,qr);
		return res;
	}
	int root[N],cnt;
	inline void ins(int x,int val) {
		++cnt;
		root[cnt]=root[cnt-1];
		update(root[cnt],1,len,x,val);
	}
	inline int query(int _l,int _r,int l,int r) {
		if(_l>_r||l>r)
			return 0;
		l=get_id(l); r=get_id(r+1)-1;
		return query(root[_l-1],root[_r],1,len,l,r);
	}
}; PSGT T;
map<ll,int> used;
inline int get_id(int x,bool op) {
	if(!op)
		return lower_bound(t1+1,t1+n+1,x)-t1;
	else
		return lower_bound(t1+1,t1+n+1,x+1)-t1-1;
}
ll f[N],g[N],h[N];
inline ll calc(int p,int k) {
	if(k>=n)
		return INFLL;
	int x=a[p].first,y=a[p].second;
	ll l=f[p],r=g[p],ans=INFLL;
	g[p]=h[p];
	h[p]=4e9;
	while(l<=r) {
		ll mid=(l+r)>>1;
		int val=T.query(get_id(max(x-mid,(ll)-2e9),0),get_id(min(x+mid,(ll)2e9),1),max(y-mid,(ll)-2e9),min(y+mid,(ll)2e9));
		if(val>=k+1) {
			if(val>k+1) {
				chkmin(g[p],mid);
				if(val>k+2)
					chkmin(h[p],mid);
			} else
				chkmax(f[p],mid);
			ans=mid,r=mid-1;
		} else
			l=mid+1;
	}
	chkmax(f[p],ans);
	return ans;
}
struct node {
	int p,k;
	ll val;
	bool operator > (const node &tmp) const {
		return val>tmp.val;
	}
}; priority_queue<node,vector<node>,greater<node> > heap;
void solve() {
	n=read(); k=read();
	rep(i,1,n) {
		int x=read(),y=read();
		a[i]={x+y,x-y};
		t1[i]=a[i].first;
		t[++len]=a[i].second;
		f[i]=0; g[i]=h[i]=4e9;
	}
	sort(t+1,t+len+1);
	sort(t1+1,t1+n+1);
	len=unique(t+1,t+len+1)-t-1;
	sort(a+1,a+n+1);
	rep(i,1,n)
		T.ins(get_id(a[i].second),1);
	rep(i,1,n)
		heap.push({i,1,calc(i,1)});
	while(true) {
		node t=heap.top(); heap.pop();
		if(!used[t.val]) {
			used[t.val]=true;
			write(t.val);
			pc('\n');
			if(!--k)
				break;
		} else
			used[t.val]=false;
		heap.push({t.p,t.k+1,calc(t.p,t.k+1)});
	}
	flush();
}
signed main() {
	//file_IO();
	int testcase=1;
	//scanf("%d",&testcase);
	while(testcase--)
		solve();
	return 0;
}
```

---

