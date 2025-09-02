# Intersection of Permutations

## 题目描述

给定整数 $n$ 和两个 $1,\dots,n$ 的排列 $a,b$。

$m$ 个操作，操作有两种：
  - $1\ l_a\ r_a\ l_b\ r_b$，设 $a$ 的 $[l_a;r_a]$ 区间内的元素集合为 $S_a$，设 $b$ 的 $[l_b;r_b]$ 区间内的元素集合为 $S_b$，求 $\lvert S_a \bigcap S_b \rvert$。
  - $2\ x\ y$，交换 $b$ 的第 $x$ 位与第 $y$ 位。

$1 \le n,m \le 2 \cdot 10^5$

## 样例 #1

### 输入

```
6 7
5 1 4 2 3 6
2 5 3 1 4 6
1 1 2 4 5
2 2 4
1 1 2 4 5
1 2 3 3 5
1 1 6 1 2
2 4 1
1 4 4 1 3
```

### 输出

```
1
1
1
2
0
```

# 题解

## 作者：He_Ren (赞：43)

Update:

2020-2-18 勘误

---

### solution

一个显然的想法是，规定一种映射 $f(a_i)=i$，然后分别把 $a_i$ 设为 $f(a_i)$，$b_i$ 设为 $f(b_i)$，容易证明，现在 $a$ 和 $b$ 仍是 $1$ 到 $n$ 的排列。

```cpp
for(int i=1; i<=n; ++i) pos[a[i]]=i;
for(int i=1; i<=n; ++i) b[i]=pos[b[i]];
```

此时，询问就转化为：计算排列 $b$ 的区间 $[l_b,r_b]$ 中，值的范围在区间 $[l_a,r_a]$ 中的数的个数。

#### 1. 分块

将 $b$ 序列分成 $\sqrt n$ 块，块内排序，预处理复杂度 $O(n\log n)$。

查询时对于整块使用二分查找求出 $[l_a,r_a]$ 范围中数的个数，其余部分暴力查找，单次查询复杂度 $O(\sqrt n \log n)$。

修改时直接重构当前块即可，单次修改复杂度 $O(\sqrt n\log n)$。

总复杂度是 $O(m\sqrt n\log n)$，如果常数不大是可以通过本题的。所以在比赛中，如果可以确保常数不大的话，是一种性价比很高的做法。不过在比赛中为了保险还是建议使用一些优化，下文会讲到该做法的一种优化。

```cpp
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 5;
const int MAXM = 2e5 + 5;

inline void chk_max(int &a,int b){ if(a<b) a=b;}

int n,a[MAXN],b[MAXN];

int lB[MAXN],rB[MAXN],pos[MAXN],tot;
int val[MAXN];

void init(void)//初始化
{
	tot=sqrt(n);
	for(int i=1; i<=tot; ++i)
		lB[i]=(i-1)*tot+1,
		rB[i]=lB[i]+tot-1;//每个块的左右边界
	chk_max(rB[tot],n);
	for(int i=1; i<=tot; ++i)
	{
		for(int j=lB[i]; j<=rB[i]; ++j)
			pos[j]=i, val[j]=b[j];//pos[i]表示第i个数属于哪个块
		sort(val+lB[i],val+rB[i]+1);//val是块内排序后的数组
	}
}

void updateBlock(int now)//重构该块
{
	for(int i=lB[now]; i<=rB[now]; ++i)
		val[i]=b[i];
	sort(val+lB[now],val+rB[now]+1);
}

int query(int l,int r,int x,int y)
{
	int res=0;
	if(pos[l]==pos[r])//在同一块内
	{
		for(int i=l; i<=r; ++i)
			if(x<=b[i] && b[i]<=y) ++res;
		return res;
	}
	//零散部分暴力
	int nowl=pos[l];
	for(int i=l; i<=rB[nowl]; ++i)
		if(x<=b[i] && b[i]<=y) ++res;
	int nowr=pos[r];
	for(int i=lB[nowr]; i<=r; ++i)
		if(x<=b[i] && b[i]<=y) ++res;
	//整块中二分查找
	for(int i=nowl+1; i<nowr; ++i)
		res += upper_bound(val+lB[i],val+rB[i]+1,y) - upper_bound(val+lB[i],val+rB[i]+1,x-1);
	return res;
}

int main(void)
{
	int Q;
	scanf("%d%d",&n,&Q);
	for(int i=1; i<=n; ++i)
	{
		int x;
		scanf("%d",&x);
		a[x]=i;
	}
	for(int i=1; i<=n; ++i)
		scanf("%d",&b[i]),
		b[i]=a[b[i]];
	init();
    
	while(Q--)
	{
		int oper,x,y;
		scanf("%d%d%d",&oper,&x,&y);
		if(oper==1)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",query(l,r,x,y));
		}
		else
		{
			swap(b[x],b[y]);
			updateBlock(pos[x]);
			if(pos[x]!=pos[y]) updateBlock(pos[y]);
		}
	}
	return 0;
}
```



#### 2. CDQ 分治

把 $b$ 序列中的数看成点，第 $i$ 个点的坐标是 $(i,b_i)$，权值为 $1$ ，平面中其他点的权值为 $0$，那么问题就变成了，每次可以修改一个点的权值，或查询横坐标在 $[l_b,r_b]$，纵坐标在 $[l_a,r_a]$ 中的点的权值之和，显然可以用 CDQ 分治解决。

CDQ 分治是一种离线算法，支持两种操作：

1. 将点 $(x,y)$ 的权值增加 $k$ 。
2. 查询横坐标在 $[l,r]$范围，纵坐标 $\leq y$ 的点的权值之和。

容易发现，使用该算法可以求出平面内任意矩形的权值之和。注意，一般情况下，所有操作（修改和查询）的横坐标必须是一定范围内的整数，而纵坐标可以是任意支持比较的数据类型，想要扩展横坐标的范围，则需要另外的处理。

CDQ 分治的大体思路如下：将当前的操作序列（包括修改和查询）分成左右两部分，递归处理左右两部分询问的答案，然后计算左半边的每个修改对右半边的每个修改的贡献。

（下面两段意会一下，看代码最好懂）

如何计算贡献？（以下，使用 “ 元素 ” 称呼 “ 操作 ”）可以将左右两边分别按纵坐标从小到大排序，用双指针维护：对于每个右半边的元素（以下称作 $p$ ），最大的、纵坐标小于 $p$ 的纵坐标的、左半边的元素（以下称作 $q$ ）；通过以上处理方式处理方式发现，所有从 当前序列开头 到 $q$ 的修改操作，其纵坐标均小于 $p$ 的纵坐标，所以用树状数组维护从 当前序列开头 到 $q$ 的修改，对于每个横坐标的权值之和。这个和即为左半区间对于 $p$ 的贡献。（使用树状数组也是对横坐标有限制的原因）

如何排序？发现以上方法和归并排序相似，所以可以在处理时就将元素排序，降低复杂度。

递归是 $O(n\log n)$ 的，树状数组 $O(\log n)$，总复杂度 $O(nlog^2n)$。

```cpp
int mid = (l+r)>>1;
solve(l,mid);//递归处理两边的区间
solve(mid+1,r);

int cur=l;
for(int i=l,j=mid+1; i<=mid || j<=r;)
{
    if(j>r || (i<=mid && event[i].y<=event[j].y))
    {
        if(event[i].is_update())
            tree.update(event[i].l, event[i].val);//tree是树状数组   event[i].l是当前修改操作的横坐标
        buffer[cur++] = event[i++];//buffer 是排好序的数组
    }
    else
    {
        if(event[j].is_query())
            res[event[j].id] += event[j].val * tree.query(event[j].l, event[j].r);//res是每个询问的答案   event[j].val是每个询问的权值（下面会讲）
        buffer[cur++] = event[j++];
    }
}

for(int i=l; i<=mid; ++i)
    if(event[i].is_update())
        tree.update(event[i].l,-event[i].val);//清空树状数组

for(int i=l; i<=r; ++i) event[i] = buffer[i];//排好序
```

为什么代码中的查询也有权值？实际上程序中的 “ 查询 ” 操作，是将 ```res[id]``` 的值，加上横坐标在 $[l,r]$范围，纵坐标 $\leq y$ 的点的权值之和，乘以 $val$ 的结果，这么做是为了方便询问的输出，这一点结合代码会更好理解。

注意，为了减小常数，在区间大小到一定范围时可以直接暴力计算，而清空树状数组的操作在区间大小到一定范围时也可暴力解决。

完整代码（初学 CDQ 分治，借鉴了 @neal 大佬的程序）：

```cpp
using namespace std;
const int MAXN = 2e5 + 5;
const int MAXM = 2e5 + 5;

inline void chk_max(int &a,int b){ if(a<b) a=b;}

struct BIT//树状数组
{
	int n,tree[MAXN];
	#define lowbit(x) ((x)&-(x))
	BIT(int n_=0){ init(n_);}
	inline void init(int n_){ n=n_; memset(tree,0,sizeof(tree));}
	inline void clean(void){ memset(tree,0,sizeof(tree));}
	inline void update(int x,int k)
	{
		while(x<=n)
			tree[x]+=k,
			x+=lowbit(x);
	}
	inline int query(int x)
	{
		int res=0;
		while(x)
			res+=tree[x],
			x^=lowbit(x);
		return res;
	}
	inline int query(int l,int r){ return query(r)-query(l-1);}
};

struct CDQ
{
	struct Event//操作
	{
		int l,r,y;//修改操作的 l=r=x
		int val,id;//id是查询操作的编号，修改操作的id=-1
		Event(int l_=0,int r_=0,int y_=0,int val_=0,int id_=0){ l=l_; r=r_; y=y_; val=val_; id=id_;}
		
		inline bool is_update(void){ return id<0;}
		inline bool is_query(void){ return id>=0;}
		
		inline friend operator < (const Event &p,const Event &q){ return p.y<q.y;}
	};
	
	vector<Event> event, buffer;
	vector<int> res;
	BIT tree;
	int maxx,maxid;
	
	CDQ(void){ init();}
	inline void init(void){ maxx=maxid=0;}
	
	inline void add_update(int x,int y,int val)//加入一个修改
	{
		event.push_back((Event){x,x,y,val,-1});
		chk_max(maxx,x);
	}
	
	inline void add_query(int l,int r,int y,int val,int id)//加入一个查询
	{
		event.push_back((Event){l,r,y,val,id});
		chk_max(maxx,r); chk_max(maxid,id);
	}
	
	void solve(int l,int r)
	{
		if(r-l+1<=100)//区间很小时直接暴力
		{
			for(int i=l; i<=r; ++i) if(event[i].is_query())
			{
				Event now = event[i];
				for(int j=l; j<i; ++j) if(event[j].is_update())
					if(event[j].y<=event[i].y && now.l <= event[j].l && event[j].l <= now.r)
						res[now.id] += now.val * event[j].val;
			}
			sort(event.begin()+l, event.begin()+r+1);
			return;
		}
		
		int mid = (l+r)>>1;
		solve(l,mid);
		solve(mid+1,r);
		
		int cur=l;
		for(int i=l,j=mid+1; i<=mid || j<=r;)
		{
			if(j>r || (i<=mid && event[i].y<=event[j].y))
			{
				if(event[i].is_update())
					tree.update(event[i].l, event[i].val);
				buffer[cur++] = event[i++];
			}
			else
			{
				if(event[j].is_query())
					res[event[j].id] += event[j].val * tree.query(event[j].l, event[j].r);
				buffer[cur++] = event[j++];
			}
		}
		
		if(mid-l+1 > (tree.n>>9)) tree.clean();//这里是上文提及的常数优化
		else for(int i=l; i<=mid; ++i)
			if(event[i].is_update())
				tree.update(event[i].l,-event[i].val);
		
		for(int i=l; i<=r; ++i) event[i] = buffer[i];
	}
	
	void solve(void)
	{
		res.assign(maxid+1,0);
		tree.init(maxx);
		buffer.resize(event.size());
		solve(0,event.size()-1);
	}
}solver;

int a[MAXN],b[MAXN],pos[MAXN];

int main(void)
{
	int n,Q;
	scanf("%d%d",&n,&Q);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&b[i]);
	
	for(int i=1; i<=n; ++i) pos[a[i]]=i;
	for(int i=1; i<=n; ++i)
	{
		b[i]=pos[b[i]];
		solver.add_update(i,b[i],1);
	}
	
	int cnt=0;
	while(Q--)
	{
		int oper,x,y;
		scanf("%d%d%d",&oper,&x,&y);
		if(oper==1)
		{
			int l,r;
			scanf("%d%d",&l,&r);
            //cnt是当前询问的编号
			solver.add_query(l,r,y,1,cnt);//val=1，这里是将编号为cnt的询问加上该矩形的和
			solver.add_query(l,r,x-1,-1,cnt);//val=-1，这里是将编号为cnt的询问减去该矩形的和
			++cnt;
		}
		else
		{
			solver.add_update(x,b[x],-1);
			solver.add_update(y,b[y],-1);
			swap(b[x],b[y]);
			solver.add_update(x,b[x],1);
			solver.add_update(y,b[y],1);
		}
	}
	
	solver.solve();
	for(int i=0; i<cnt; ++i)
		printf("%d\n",solver.res[i]);
	return 0;
}
```

#### 3. 树状数组套权值线段树

这个做法也比较显然。问题可以拆分成，区间 $[l_b,r_b]$ 中小于等于 $r_a$ 的数的个数 减去 小于等于 $l_a-1$ 的数的个数，即，查询区间中小于等于某个数的个数。

如果没有修改，该问题显然可以用主席树解决，而主席树的本质实际上就是对于每个位置建一棵权值线段树，加上查询，如果对每棵线段树进行修改显然耗时又耗空间，所以可以使用树状数组优化这一过程。在树状数组的每个节点上维护一棵权值线段树，维护该节点表示的区间，查询与修改都与普通的树状数组很像。

单次操作，树状数组的复杂度是 $O(\log n)$，权值线段树的复杂度是 $O(\log n)$。总复杂度是 $O(m\log^2 n)$。

注意，不加任何空间的优化，点的个数会很多导致空间不足，所以我们可以 “ 回收 ” 一些不用的点，即，如果一个点的权值为 $0$，我们将这个点删除并将编号存起来，开新点的时候优先使用这些编号即可。

```cpp
using namespace std;
const int MAXN = 2e5 + 5;

struct Segment_Tree//权值线段树
{
	static const int MAXP = MAXN*200;
	int ls[MAXP],rs[MAXP],sum[MAXP],pcnt;
	vector<int> okNodes;
	#define lson(u) ls[u],l,mid
	#define rson(u) rs[u],mid+1,r
	
	inline void newNode(int &u)
	{
		if(okNodes.empty()){ u=++pcnt; return;}
		u = okNodes.back();
		okNodes.pop_back();
	}
	inline void delNode(int &u)
	{
		okNodes.push_back(u);
		u=0;
	}
	
	Segment_Tree(void){ init();}
	void init(void)
	{
		memset(sum,0,sizeof(sum));
		memset(ls,0,sizeof(ls));
		memset(rs,0,sizeof(rs));
		pcnt=0;
		okNodes.clear();
	}
	
	inline void push_up(int u){ sum[u]=sum[ls[u]]+sum[rs[u]];}
	
	void update(int &u,int l,int r,int q,int k)
	{
		if(!u) newNode(u);
		sum[u]+=k;
		if(l<r)
		{
			int mid = (l+r)>>1;
			if(q<=mid) update(lson(u),q,k);
			else update(rson(u),q,k);
		}
		if(!sum[u]) delNode(u);
	}
	
	int query(int u,int l,int r,int ql,int qr)
	{
		if(!u) return 0;
		if(ql<=l && r<=qr) return sum[u];
		int mid = (l+r)>>1, res=0;
		if(ql<=mid) res+=query(lson(u),ql,qr);
		if(mid<qr) res+=query(rson(u),ql,qr);
		return res;
	}
};

struct BIT//树状数组
{
	int n;
	Segment_Tree segTree;
	int root[MAXN];//每个节点权值线段树的树根
	#define lowbit(x) ((x)&-(x))
	
	void init(int n_=0){ n=n_; segTree.init();}
    
	//修改与查询都和普通的树状数组很像
	void update(int x,int q,int k)
	{
		while(x<=n)
			segTree.update(root[x],1,n,q,k),
			x+=lowbit(x);
	}
	int query(int x,int ql,int qr)
	{
		int res=0;
		while(x)
			res += segTree.query(root[x],1,n,ql,qr),
			x^=lowbit(x);
		return res;
	}
	int query(int l,int r,int ql,int qr){ return query(r,ql,qr)-query(l-1,ql,qr);}
}solver;

int a[MAXN],b[MAXN],pos[MAXN];

int main(void)
{
	int n,Q;
	scanf("%d%d",&n,&Q);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&b[i]);
	
	solver.init(n);
	for(int i=1; i<=n; ++i) pos[a[i]]=i;
	for(int i=1; i<=n; ++i)
		b[i]=pos[b[i]],
		solver.update(i,b[i],1);
	
	while(Q--)
	{
		int oper,x,y;
		scanf("%d%d%d",&oper,&x,&y);
		if(oper==1)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",solver.query(l,r,x,y));
		}
		else
		{
			solver.update(x,b[x],-1);
			solver.update(y,b[y],-1);
			swap(b[x],b[y]);
			solver.update(x,b[x],1);
			solver.update(y,b[y],1);
		}
		
	}
	return 0;
}
```

#### 4. 一种神奇的解法

发现静态的维护好像比带修改容易得多，所以不难想到这样的思路：将所有修改操作保存下来，每次查询的时候，在初始序列的答案的基础上，遍历一遍之前出现的所有修改操作，根据这些修改操作更新每个答案。

这是查询操作：

```cpp
int ans = query(...);//ans在这里是初始序列的答案，query中的内容根据算法有所不同
for(int i=0; i<(int)upd.size(); ++i)//upd是之前出现的修改操作
{
    //根据之前修改的内容调整ans
    int xx=upd[i].x, yy=upd[i].y;
    if(l<=xx && xx<=r && x<=b[xx] && b[xx]<=y) --ans;
    if(l<=yy && yy<=r && x<=b[yy] && b[yy]<=y) --ans;
    swap(b[xx],b[yy]);
    if(l<=xx && xx<=r && x<=b[xx] && b[xx]<=y) ++ans;
    if(l<=yy && yy<=r && x<=b[yy] && b[yy]<=y) ++ans;
}
for(int i=upd.size()-1; i>=0; --i)
    swap(b[upd[i].x],b[upd[i].y]);
printf("%d\n",ans);
```

这是修改操作：

```cpp
upd.push_back((Oper){x,y});
```

我们设初始化的复杂度为 $A$，一次查询的复杂度为 $B$，这样做的复杂度是 $O(A + m^2 B)$，这样的复杂度显然太高了。

如何优化？发现查询和修改的操作，时间复杂度相差太大，**于是考虑如何平衡查询和修改的复杂度**。

**多种操作的时间复杂度相差太大，可以考虑如何平衡这些操作的复杂度。**

想到，可以在积累到一定量的修改操作后，直接重新初始化一遍，即：

```cpp
if((int)upd.size()>=k)//修改操作到达一定的数量
{
    for(int i=0; i<(int)upd.size(); ++i)
        swap(b[upd[i].x],b[upd[i].y]);//修改序列
    init(...);//重新初始化，根据算法有所不同
    upd.clear();
}
```

那么这个 $k$ 取多少呢？这种做法的复杂度是 $O(\frac{m}{k}\cdot A + m(B+k) = O(m(\frac{A}{k}+k)+mB)$，即，要使时间复杂度最小，就要使 $\frac{A}{k}+k$ 最小，计算得出，$k=\sqrt A$ 时，复杂度最小。

下面给出一种线段树的解法。线段树的每个节点，存的是该节点表示的区间排序后的序列，查询这个节点的答案使用二分查找即可。初始化复杂度是 $O(n\log n)$，单次查询复杂度是 $O(\log^2 n)$，选取 $k=\sqrt{n\log_2 n}$，复杂度是 $O(m(\sqrt{n\log n}+\log^2 n))$。

```cpp
using namespace std;
const int MAXN = 2e5 + 5;

int n;
int a[MAXN],pos[MAXN],b[MAXN];

vector<int> tree[MAXN<<2];
#define ls(u) ((u)<<1)
#define rs(u) ((u)<<1|1)
#define lson(u) ls(u),l,mid
#define rson(u) rs(u),mid+1,r

inline void push_up(int u)
{
	const vector<int> &v1=tree[ls(u)], &v2=tree[rs(u)];
	
	int i=0,j=0;
	while(i<(int)v1.size() && j<(int)v2.size())
	{
		if(v1[i]<=v2[j]) tree[u].push_back(v1[i++]);
		else tree[u].push_back(v2[j++]);
	}
	while(i<(int)v1.size()) tree[u].push_back(v1[i++]);
	while(j<(int)v2.size()) tree[u].push_back(v2[j++]);
}

void build(int u,int l,int r)
{
	tree[u].clear();
	if(l==r){ tree[u].push_back(b[l]); return;}
	int mid = (l+r)>>1;
	build(lson(u)); build(rson(u));
	push_up(u);
}

int query(int u,int l,int r,int ql,int qr,int k)
{
	if(ql<=l && r<=qr)
		return upper_bound(tree[u].begin(),tree[u].end(),k) - tree[u].begin();
	int mid=(l+r)>>1, res=0;
	if(ql<=mid) res += query(lson(u),ql,qr,k);
	if(mid<qr) res += query(rson(u),ql,qr,k);
	return res;
}

struct Oper
{
	int x,y;
};
vector<Oper> upd; 

int main(void)
{
	int n,Q;
	scanf("%d%d",&n,&Q);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&b[i]);
	
	for(int i=1; i<=n; ++i) pos[a[i]]=i;
	for(int i=1; i<=n; ++i) b[i] = pos[b[i]];
	build(1,1,n);
	
	int sqn = sqrt(n*(log(n)/log(2)));
	while(Q--)
	{
		int oper,x,y;
		scanf("%d%d%d",&oper,&x,&y);
		if(oper==1)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			int ans = query(1,1,n,l,r,y)-query(1,1,n,l,r,x-1);
			for(int i=0; i<(int)upd.size(); ++i)
			{
				int xx=upd[i].x, yy=upd[i].y;
				if(l<=xx && xx<=r && x<=b[xx] && b[xx]<=y) --ans;
				if(l<=yy && yy<=r && x<=b[yy] && b[yy]<=y) --ans;
				swap(b[xx],b[yy]);
				if(l<=xx && xx<=r && x<=b[xx] && b[xx]<=y) ++ans;
				if(l<=yy && yy<=r && x<=b[yy] && b[yy]<=y) ++ans;
			}
			for(int i=upd.size()-1; i>=0; --i)
				swap(b[upd[i].x],b[upd[i].y]);
			printf("%d\n",ans);
		}
		else
		{
			upd.push_back((Oper){x,y});
			if((int)upd.size()>=sqn)
			{
				for(int i=0; i<(int)upd.size(); ++i)
					swap(b[upd[i].x],b[upd[i].y]);
				build(1,1,n);
				upd.clear();
			}
		}
	}
	return 0;
}
```

用同样的方法可以优化分块。初始化复杂度是 $O(n\log n)$，单次查询复杂度是 $O(\sqrt n\log n)$ ，选取 $k=\sqrt{n\log_2 n}$，复杂度是 $O(m(\sqrt{n\log n}+\sqrt n\log n))$，在比赛中是一种比较保险的做法。

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 5;
const int MAXM = 2e5 + 5;
const int MAXB = 1e3 + 5;

inline void chk_max(int &a,int b){ if(a<b) a=b;}

int n,a[MAXN],b[MAXN];

int lB[MAXB],rB[MAXB],bId[MAXN],tot;
int val[MAXN];

void calcAll(void)
{
	static int cur[MAXB];
	static int tmp[MAXN];
	
	for(int i=1; i<=tot; ++i) cur[i]=lB[i];
	for(int i=1; i<=n; ++i) tmp[b[i]]=i;
	
	for(int i=1; i<=n; ++i)
	{
		int now = bId[tmp[i]];
		val[cur[now]] = i;
		++cur[now];
	}
}

void init(void)
{
	tot=sqrt(n);
	for(int i=1; i<=tot; ++i)
		lB[i]=(i-1)*tot+1,
		rB[i]=lB[i]+tot-1;
	chk_max(rB[tot],n);
	for(int i=1; i<=tot; ++i)
		for(int j=lB[i]; j<=rB[i]; ++j)
			bId[j]=i;
	calcAll();
}

int query(int l,int r,int x,int y)
{
	int res=0;
	if(bId[l]==bId[r])
	{
		for(int i=l; i<=r; ++i)
			if(x<=b[i] && b[i]<=y) ++res;
		return res;
	}
	
	int nowl=bId[l];
	for(int i=l; i<=rB[nowl]; ++i)
		if(x<=b[i] && b[i]<=y) ++res;
	int nowr=bId[r];
	for(int i=lB[nowr]; i<=r; ++i)
		if(x<=b[i] && b[i]<=y) ++res;
	
	for(int i=nowl+1; i<nowr; ++i)
		res += upper_bound(val+lB[i],val+rB[i]+1,y) - upper_bound(val+lB[i],val+rB[i]+1,x-1);
	return res;
}

struct Oper
{
	int x,y;
};
vector<Oper> upd; 

int main(void)
{
	int Q;
	scanf("%d%d",&n,&Q);
	for(int i=1; i<=n; ++i)
	{
		int x;
		scanf("%d",&x);
		a[x]=i;
	}
	for(int i=1; i<=n; ++i)
		scanf("%d",&b[i]),
		b[i]=a[b[i]];
	init();
	
	int sqn = sqrt(n*(log(n)/log(2)));
	while(Q--)
	{
		int oper,x,y;
		scanf("%d%d%d",&oper,&x,&y);
		if(oper==1)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			int ans = query(l,r,x,y);
			for(int i=0; i<(int)upd.size(); ++i)
			{
				int xx=upd[i].x, yy=upd[i].y;
				if(l<=xx && xx<=r && x<=b[xx] && b[xx]<=y) --ans;
				if(l<=yy && yy<=r && x<=b[yy] && b[yy]<=y) --ans;
				swap(b[xx],b[yy]);
				if(l<=xx && xx<=r && x<=b[xx] && b[xx]<=y) ++ans;
				if(l<=yy && yy<=r && x<=b[yy] && b[yy]<=y) ++ans;
			}
			for(int i=upd.size()-1; i>=0; --i)
				swap(b[upd[i].x],b[upd[i].y]);
			printf("%d\n",ans);
		}
		else
		{
			upd.push_back((Oper){x,y});
			if((int)upd.size()>=sqn)
			{
				for(int i=0; i<(int)upd.size(); ++i)
					swap(b[upd[i].x],b[upd[i].y]);
				calcAll();
				upd.clear();
			}
		}
	}
	return 0;
}
```

同样的方法也可以应用在主席树上，这里就不多赘述了。

### 差距

学习到的点：

1. 将数据结构封装可以使思路更清晰，有效提高程序的可读性。
2. 学会用不同思路思考同一道题，将题目完全搞懂
3. 发现一种复杂度不可行的做法，不要急于放弃这种思路，而要仔细证明该算法是不是真的不可行，清晰地找出该算法为什么不可行，并尝试改进。

---

## 作者：1saunoya (赞：11)

~~大家好， 我非常喜欢暴力数据结构， 于是就用分块A了此题~~


分块题，考虑前缀和 $b_i$ 表示 bitset 即 $0$ ~ $i
$ 出现过的数字，然后考虑直接暴力复制块然后前缀和，修改也很简单，直接删除完了 swap 一下，再弄回去

时间复杂度 $O(q \sqrt n + q \frac{n}{w})$

```cpp
// by Isaunoya
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <cstdio>
#include <bitset>

using namespace std;

#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)
//#define int long long

const int _ = 1 << 21;
struct I {
	char fin[_], *p1 = fin, *p2 = fin;
	inline char gc() {
		return (p1 == p2) && (p2 = (p1 = fin) + fread(fin, 1, _, stdin), p1 == p2) ? EOF : *p1++;
	}
	inline I& operator>>(int& x) {
		bool sign = 1;
		char c = 0;
		while (c < 48) ((c = gc()) == 45) && (sign = 0);
		x = (c & 15);
		while ((c = gc()) > 47) x = (x << 1) + (x << 3) + (c & 15);
		x = sign ? x : -x;
		return *this;
	}
	inline I& operator>>(double& x) {
		bool sign = 1;
		char c = 0;
		while (c < 48) ((c = gc()) == 45) && (sign = 0);
		x = (c - 48);
		while ((c = gc()) > 47) x = x * 10 + (c - 48);
		if (c == '.') {
			double d = 1.0;
			while ((c = gc()) > 47) d = d * 0.1, x = x + (d * (c - 48));
		}
		x = sign ? x : -x;
		return *this;
	}
	inline I& operator>>(char& x) {
		do
			x = gc();
		while (isspace(x));
		return *this;
	}
	inline I& operator>>(string& s) {
		s = "";
		char c = gc();
		while (isspace(c)) c = gc();
		while (!isspace(c) && c != EOF) s += c, c = gc();
		return *this;
	}
} in;
struct O {
	char st[100], fout[_];
	signed stk = 0, top = 0;
	inline void flush() {
		fwrite(fout, 1, top, stdout), fflush(stdout), top = 0;
	}
	inline O& operator<<(int x) {
		if (top > (1 << 20)) flush();
		if (x < 0) fout[top++] = 45, x = -x;
		do
			st[++stk] = x % 10 ^ 48, x /= 10;
		while (x);
		while (stk) fout[top++] = st[stk--];
		return *this;
	}
	inline O& operator<<(char x) {
		fout[top++] = x;
		return *this;
	}
	inline O& operator<<(string s) {
		if (top > (1 << 20)) flush();
		for (char x : s) fout[top++] = x;
		return *this;
	}
} out;
#define pb emplace_back
#define fir first
#define sec second

template < class T > inline void cmax(T & x , const T & y) {
	(x < y) && (x = y) ;
}
template < class T > inline void cmin(T & x , const T & y) {
	(x > y) && (x = y) ;
}

int n , m ;
const int maxn = 2e5 + 200 ;
template < int bl > 
struct BLOCK {
	bitset < maxn > b[maxn / bl] ;
	bitset < maxn > temp ;
	int per[maxn] ;
	inline void ins(int x , int v) {
		per[x] = v ;
		for(register int i = x ; i <= n ; i += bl)
			b[i / bl].set(v) ;
	}
	inline void del(int x , int v)  {
		for(register int i = x ; i <= n ; i += bl)
			b[i / bl].reset(v) ;
	}
	inline bitset < maxn > qry(int x) {
		temp = x / bl ? b[x / bl - 1] : 0 ;
		rep(i , max(x / bl * bl , 1) , x) 
			temp.set(per[i]) ;
		return temp ;
	}
	inline bitset < maxn > qry(int l , int r) {
		return qry(r) ^ qry(l - 1) ;
	}
};
int a[maxn] , b[maxn] ;
BLOCK < 256 > A ;
BLOCK < 512 > B ;
signed main() {
#ifdef _WIN64
	freopen("testdata.in" , "r" , stdin) ;
#endif
	in >> n >> m ;
	rep(i , 1 , n) in >> a[i] , A.ins(i , a[i]) ;
	rep(i , 1 , n) in >> b[i] , B.ins(i , b[i]) ;
	while(m --) {
		int opt ;
		in >> opt ;
		if(opt == 1) {
			int l , r , a , b ;
			in >> l >> r >> a >> b ;
			int ans = (A.qry(l , r) & B.qry(a , b)).count() ;
			out << ans << '\n' ;
		}
		else {
			int x , y ;
			in >> x >> y ;
			B.del(x , b[x]) ; B.del(y , b[y]) ;
			swap(b[x] , b[y]) ;
			B.ins(x , b[x]) ; B.ins(y , b[y]) ;
		}
	}
	return out.flush(), 0;
}

```

---

## 作者：LJC00118 (赞：7)

用 $ pa[i] $ 表示 $ i $ 这个数在第一个排列中出现的位置，$ pb[i] $ 表示 $ i $ 这个数在第二个排列中出现的位置

假设查询区间为 $ l1，r1，l2，r2 $

如果 $ i $ 这个点对答案造成了贡献，那么 $ l1 \le pa[i] \le r1 $ && $ l2 \le pb[i] \le r2 $

容易发现问题变成了二维数点问题，$ cdq $ 分治离线统计答案即可

```cpp
#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define F(i,j,n) for(int i=j;i<=n;i++)
#define D(i,j,n) for(int i=j;i>=n;i--)
#define ll long long
#define maxn 1000005
#define maxm 1000005
template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

using namespace std;
int n,cnt,tot;
int ans[maxn],c[maxn];
struct data{int flag,x,y,v,pos,id;}a[maxm],b[maxm];

inline bool cmp(data a,data b)
{
    if (a.x!=b.x) return a.x<b.x;
    return a.pos<b.pos;
}
inline void add(int x,int y)
{
    for(;x<=n;x+=(x&(-x))) c[x]+=y;
}
inline int query(int x)
{
    int ret=0;
    for(;x;x-=(x&(-x))) ret+=c[x];
    return ret;
}
inline void solve(int l,int r)
{
    if (l>=r) return;
    int mid=(l+r)>>1,l1=l,l2=mid+1;
    F(i,l,r)
    {
        if (a[i].flag==1&&a[i].pos<=mid) add(a[i].y,a[i].v);
        if (a[i].flag==2&&a[i].pos>mid) ans[a[i].id]+=a[i].v*query(a[i].y);
    }
    F(i,l,r) if (a[i].flag==1&&a[i].pos<=mid) add(a[i].y,-a[i].v);
    F(i,l,r)
    {
        if (a[i].pos<=mid) b[l1++]=a[i];
        else b[l2++]=a[i];
    }
    F(i,l,r) a[i]=b[i];
    solve(l,mid);solve(mid+1,r);
}
const int N = 1e6 + 5;
int A[N], B[N], pa[N], pb[N], m;

int main()
{
    read(n); read(m);
    for(register int i = 1; i <= n; i++) {
    	read(A[i]); pa[A[i]] = i; 
    }
    for(register int i = 1; i <= n; i++) {
    	read(B[i]); pb[B[i]] = i;
    }
    for(register int i = 1; i <= n; i++) {
        cnt++;a[cnt]=(data){1,pa[i],pb[i],1,cnt,0};
    } 
    for(register int i = 1; i <= m; i++) {
    	int opt; read(opt);
    	if(opt == 1) {
    		int aa, b, c, d;
    		read(aa); read(c); read(b); read(d);
    		int x1=aa-1,y1=b-1,x2=c,y2=d;
            tot++;
            cnt++;a[cnt]=(data){2,x1,y1,1,cnt,tot};
            cnt++;a[cnt]=(data){2,x2,y2,1,cnt,tot};
            cnt++;a[cnt]=(data){2,x1,y2,-1,cnt,tot};
            cnt++;a[cnt]=(data){2,x2,y1,-1,cnt,tot};
    	}
    	if(opt == 2) {
    		int aa, b;
    		read(aa); read(b);
    		if(aa == b) continue;
//    		del(root, Point(pa[B[a]], pb[B[a]], 1), 0);
//    		del(root, Point(pa[B[b]], pb[B[b]], 1), 0);
    		cnt++;a[cnt]=(data){1,pa[B[aa]],pb[B[aa]],-1,cnt,0};
    		cnt++;a[cnt]=(data){1,pa[B[b]],pb[B[b]],-1,cnt,0};
    		swap(B[aa], B[b]); pb[B[aa]] = aa; pb[B[b]] = b;
    		cnt++;a[cnt]=(data){1,pa[B[aa]],pb[B[aa]],1,cnt,0};
    		cnt++;a[cnt]=(data){1,pa[B[b]],pb[B[b]],1,cnt,0};
    	}
    }
    sort(a+1,a+cnt+1,cmp);
    solve(1,cnt);
    F(i,1,tot) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：_lfxxx_ (赞：5)

~~大家好，我非常喜欢暴力数据结构，于是我就用分块 A 了此题。~~

题解区分块做法基本都是带 $\log$ 或者说加上 `bitset` 优化暴力，这里介绍一种 $O((n+m) \sqrt n)$ 的分块做法，目前[最优解](https://www.luogu.com.cn/record/list?pid=CF1093E&orderBy=1&status=&page=1)（$826\text{ms}$ $4.61\text{MB}$）。

首先我们定义 $p_i$ 为 $i$ 在 $a$ 中出现的位置，然后把 $b_i$ 和 $p_{b_i}$ 对应起来，这样只需要回答 $[l_b,r_b]$ 中的 $p$ 值在 $[l_a,r_a]$ 的个数。可以这么实现：
```cpp
for(int i=1;i<=n;++i)
	cin>>a[i],p[a[i]]=i;
for(int i=1;i<=n;++i)
	cin>>b[i],a[p[b[i]]]=i;
//此时询问相当于问新的 a 在 [lb,rb] 范围中值在 [la,ra] 的个数。
```
我们对序列和值域分块，设块长为 $s$。

我们预处理一个数组 $f_{i,j}$ 表示**序列**第 $i$ 个块中**数值**落在第 $1$ 到 $j$ 个块的数的个数（即小于等于 $j \times s$ 的个数）。暴力预处理，时间复杂度 $O(\dfrac{n^2}{s})$。

对于询问，零散序列块暴力，整序列块中零散数值暴力，整的数值查 $f$ 数组，因此需要一个辅助数组来存每一个值的位置，时间复杂度 $O(s+\dfrac{n}{s})$。

对于修改，相当于交换序列的两个数，相应更新辅助数组，$f$ 数组只要暴力修改数所在序列块的数值信息即可，时间复杂度 $O(\dfrac{n}{s})$。

因此理论上 $s=\sqrt n$ 时时间复杂度最优，为 $O((n+m) \sqrt n)$，实际可以微调来更快~~我懒得调~~，同时空间复杂度 $O(n)$~~，感觉可以在时间和空间吊打某些数据结构~~。

代码：

不太长，也不是很难写。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=2e5+5,S=sqrt(N)+5;
int n,s,b,a[N],c[N],pos[N],ps[N],in[N],f[S][S];
inline int solve(int l,int r,int x){
	int res=0,m=x/s;
	for(int i=in[l];i<=in[r];++i)
		res+=f[i][m];
	for(int i=m*s+1;i<=x;++i)
		res+=l<=ps[i]&&ps[i]<=r;
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int q,op,l,r,L,R,ans;
	cin>>n>>q;
	s=sqrt(n);
	b=n/s;
	for(int i=1;i<=n;++i)
		cin>>a[i],pos[a[i]]=i,in[i]=(i-1)/s+1;
	in[n+1]=in[n];
	for(int i=1;i<=n;++i)
		cin>>c[i],a[pos[c[i]]]=i;
	for(int i=1;i<=n;++i)
		ps[a[i]]=i;
	for(int i=1;i<=s*b;++i)
		for(int j=b;j;--j){
			if(a[i]>j*s)
				break;
			++f[in[i]][j];
		}
	while(q--){
		cin>>op>>l>>r;
		if(op==1){
			cin>>L>>R;
			ans=0;
			if(in[l]==in[r])
				for(int i=l;i<=r;++i)
					ans+=L<=a[i]&&a[i]<=R;
			else{
				for(;in[l-1]==in[l];++l)
					ans+=L<=a[l]&&a[l]<=R;
				for(;in[r+1]==in[r];--r)
					ans+=L<=a[r]&&a[r]<=R;
				ans+=solve(l,r,R)-solve(l,r,L-1);
			}
			cout<<ans<<'\n';
		}
		else{
			swap(c[l],c[r]);
			l=pos[c[l]],r=pos[c[r]];
			swap(a[l],a[r]);
			ps[a[l]]=l,ps[a[r]]=r;
			for(int i=in[a[l]];i<=b;++i)
				++f[in[l]][i],--f[in[r]][i];
			for(int i=in[a[r]];i<=b;++i)
				--f[in[l]][i],++f[in[r]][i];
		}
	}
	return 0;
}
```

---

## 作者：GKxx (赞：5)

我永远喜欢树套树。

树状数组套权值线段树

注意到$a_i$和$b_i$都是排列，可以设`p[a[i]]=i`，这样的映射一定是一一映射。

那么对于一个询问，集合$\{a[l_a],a[l_a+1],\cdots,a[r_a]\}$与集合$\{b[l_b],b[l_b+1],\cdots,b[r_b]\}$的交集大小一定等于集合$\{p[a[l_a]],p[a[l_a+1]],\cdots,p[a[r_a]]\}$（也就是集合$\{l_a,l_a+1,\cdots,r_a\}$）与集合$\{p[b[l_b]],p[b[l_b+1]],\cdots,p[b[r_b]]\}$的交集大小。

所以我们用数据结构来维护序列$p[b[i]]$，每个询问就是在查询这个序列的第$l_b$个元素到第$r_b$个元素中，值域在$[l_a,r_a]$的元素有多少个，也就是区间上的值域数点。用树状数组维护区间，权值线段树维护值域即可。

修改也就没有任何难度了。

如果不带修改是可以直接用主席树的，时间和空间都更加优秀。

小心卡空间，我用了垃圾回收

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>

template <typename T> inline void read(T& x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkmax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

const int maxn = 2e5 + 7;
int lc[maxn << 7], rc[maxn << 7], sum[maxn << 7], tot;
int root[maxn];
int b[maxn], p[maxn];
int n, m;
std::vector<int> can;

inline int newNode() {
    if (can.empty()) return ++tot;
    else {
        int x = can.back();
        can.pop_back();
        return x;
    }
}
inline void deleteNode(int x) {
    lc[x] = rc[x] = sum[x] = 0;
    can.push_back(x);
}
void modify(int &o, int l, int r, int pos, int d) {
    if (!o) o = newNode();
    sum[o] += d;
    if (l < r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) modify(lc[o], l, mid, pos, d);
        else modify(rc[o], mid + 1, r, pos, d);
    }
    if (!sum[o]) deleteNode(o), o = 0;
}
int query(int o, int lb, int rb, int l, int r) {
    if (!o || l > rb || r < lb) return 0;
    if (l <= lb && r >= rb) return sum[o];
    int mid = (lb + rb) >> 1;
    return query(lc[o], lb, mid, l, r) + query(rc[o], mid + 1, rb, l, r);
}
inline void modify(int x, int v, int d) {
    for (; x <= n; x += x & -x) modify(root[x], 1, n, v, d);
}
inline int query(int l, int r, int x, int y) {
    int ans = 0;
    for (; r; r -= r & -r) ans += query(root[r], 1, n, x, y);
    for (--l; l; l -= l & -l) ans -= query(root[l], 1, n, x, y);
    return ans;
}

int main() {
    read(n, m);
    for (int i = 1, x; i <= n; ++i) read(x), p[x] = i;
    for (int i = 1; i <= n; ++i) read(b[i]), modify(i, p[b[i]], 1);
    while (m--) {
        int q; read(q);
        if (q == 1) {
            int l1, r1, l2, r2;
            read(l1, r1, l2, r2);
            writeln(query(l2, r2, l1, r1));
        } else {
            int x, y; read(x, y);
            modify(x, p[b[x]], -1);
            modify(y, p[b[y]], -1);
            std::swap(b[x], b[y]);
            modify(x, p[b[x]], 1);
            modify(y, p[b[y]], 1);
        }
    }
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：4)

设 $f_i$ 表示 $b_i$ 在 $a$ 中出现的位置，则询问转化为 $f_l \sim f_r$ 中有多少个在区间 $[L, R]$ 中的。这是明显的二维数点问题，树套树以后走人。

考虑更简单的非树套树写法。最简单的思路是将树套树外层树换成分块，内层套 `vector`，每次修改操作直接将交换的两个点所在块推平重构，设块长为 $B$，则修改操作的复杂度为单次 $O(B \log n)$，查询操作复杂度单次 $O(\dfrac{n}{B} \log n)$，根据均值不等式，当 $B = \sqrt{n}$ 时，时间复杂度最优为 $O(m \sqrt{n} \log n)$。

考虑优化算法。这里来点通俗易懂的优化。我们发现每次修改操作的时候都只需要修改其中的一个值，那么就可以先二分出修改位置然后用插入排序。而 `std::vector` 自带插入函数 `emplace`，所以可以做到 $O(\log n + B)$ 的优秀复杂度。

所以现在单次操作复杂度就是 $O(\max\{ \dfrac{n}{B} \log n, \log n + k\})$。我们先抛去这个 $\log n$ 不看，根据均值不等式，当 $B = \sqrt{n \log n}$ 时时间复杂度最小，为 $O(m \sqrt{n \log n})$。

优化效果还是很明显的，从 $5000 ms$ 优化成了 $3000ms$。

据说还可以询问分块。不过我不会。

```cpp
#pragma GCC optimize(2)
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int N = 200010, M = 460;
int len, n, m, a[N], b[N], f[N];
int Map[N];
vector<int> bl[M];

int get(int x) {
	return int(x / len);
}
int solve(int k, int l, int r) {
	if (bl[k].back() < l) return 0;
	if (bl[k].front() > r) return 0;
	int R = upper_bound(bl[k].begin(), bl[k].end(), r) - bl[k].begin() - 1;
	int L = lower_bound(bl[k].begin(), bl[k].end(), l) - bl[k].begin();
	return R - L + 1;
}
int query(int l1, int r1, int l2, int r2) {
	int lc = get(l2), rc = get(r2), ans = 0;
	if (lc == rc) {
		for (int i = l2; i <= r2; i ++ ) {
			ans += (f[i] >= l1 and f[i] <= r1);
		}
		return ans;
	}
	int i = l2, j = r2;
	while (get(i) == lc) ans += (f[i] >= l1 and f[i] <= r1), i ++ ;
	while (get(j) == rc) ans += (f[j] >= l1 and f[j] <= r1), j -- ;
	for (int k = get(i); k <= get(j); k ++ )
		ans += solve(k, l1, r1);
	return ans;
}
void modify(int x, int y) {
	int xc = get(x), yc = get(y);
	if (xc == yc) return void(swap(f[x], f[y]));
	bl[xc].erase(find(bl[xc].begin(), bl[xc].end(), f[x]));
	bl[yc].erase(find(bl[yc].begin(), bl[yc].end(), f[y]));
	swap(f[x], f[y]);
	bl[xc].emplace(lower_bound(bl[xc].begin(), bl[xc].end(), f[x]), f[x]);
	bl[yc].emplace(lower_bound(bl[yc].begin(), bl[yc].end(), f[y]), f[y]);
}

int main() {
	scanf("%d%d", &n, &m);
	len = int(sqrt(n * log2(n)));
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &b[i]);
	for (int i = 1; i <= n; i ++ )
		Map[a[i]] = i;
	for (int i = 1; i <= n; i ++ )
		f[i] = Map[b[i]];
	for (int i = 1; i <= n; i ++ )
		bl[get(i)].emplace_back(f[i]);
	for (int i = get(1); i <= get(n); i ++ )
		sort(bl[i].begin(), bl[i].end());
	
	while (m -- ) {
		int op, x, y, l1, r1, l2, r2;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
			printf("%d\n", query(l1, r1, l2, r2));
		}
		else {
			scanf("%d%d", &x, &y);
			modify(x, y);
		}
	}
	return 0;
}
```

个人认为自己的分块还是很漂亮的喵。

---

## 作者：JWRuixi (赞：4)

~~这个时限给的……，只要不乱搞都能过吧……~~

- 题意

给定排列 $a,b$，实现以下操作：

1. ```1 l r L R```，查询即出现在 $a_{[l,r]}$ 中，又出现在 $b_{[L,R]}$ 中的数。
2. ```2 x y```，交换 $b_x$ 和 $b_y$。

- 分析

首先，如果将数 $i$ 在 $a$ 中的下标设成 $x_i$，将其在 $b$ 中的下标设成 $y_i$，则这题可以转换为带修二维数点。

这里提供两种做法：

1. 分块套树状数组

对 $y$ 轴进行分块，对每个块维护一个树状数组，可以做到 $O(\sqrt n \log n)$ 查询，$O(\log n)$ 修改，会 TLE，
怎么办呢？

考虑可以在分块数组上也套上一种树状数组类的数据结构，设第 $i$ 块上的树状数组表示 $(i-\operatorname{lowbit}(i),i]$ 块的树状数组搞起来。

这样子可以 $O(n \log n \log(\sqrt n))$ 预处理，$O(\sqrt n + \log n \log(\sqrt n))$ 查询，$O(\log n \log(\sqrt n))$ 修改，可过，而且常数很小，直接最优解。

2. 分块加值域分块

这是一种极其暴力的算法，我想快速查询 $y$ 在第 $LL$ 到第 $RR$ 块，且 $x$ 在 $l$ 到 $r$ 中的点的个数，那首先想到差分，让后想到值域分块，值域 $[1,10^5]$，显然可过。

具体的，可以设 $b_{i,j}$ 表示前 $i$ 块，第 $j$ 值域块中的点数；$c_{i,j}$ 表示前 $i$ 块，$x = j$ 的点数。

那么查询的时候对边角块直接暴力，对边角值域块，用 $c$ 查询，整块用 $b$ 查询。修改的时候考虑将 $r$ 移到 $l$，$[l,r - 1]$ 都会增加贡献，将 $r$ 移到 $l$，$[l,r-1]$ 都会减少贡献，暴力即可。


预处理 $O(n\sqrt n)$，查询 $O(\sqrt n)$，常数巨大，修改 $O(\sqrt n)$，常数较小。

- code

分块加树状数组：
```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(2e5 + 500), maxk(450);
int n, m, sqn, len, a[maxn], b[maxn], X[maxn], id[maxn];

struct BIT {
	int tr[maxn];
#define lowbit(x) (x & (-x))
	inline void mdy (int x, int v) {
		for (; x <= n; x += lowbit(x)) tr[x] += v;
	}
	inline int query (int x) {
		int res = 0;
		for (; x; x -= lowbit(x)) res += tr[x];
		return res;
	}
	inline int qry (int l, int r) {
		return query(r) - query(l - 1);
	}
} tr[maxk];

inline int qry (int x, int l, int r) {
	int res = 0;
	for (; x; x -= lowbit(x)) res += tr[x].qry(l, r);
	return res;
}

int main () {
	n = read(), m = read(), sqn = sqrt(n), len = (n - 1) / sqn + 1;
	for (int i = 1; i <= n; i++) a[i] = read(), X[a[i]] = i;
	for (int i = 1; i <= n; i++) b[i] = read();
	for (int i = 1; i <= n; i++) id[i] = (i - 1) / sqn + 1;
	for (int i = 1, now = 1; now <= len; now++) {
		for (; id[i] == now; i++) {
			for (int j = now; j <= len; j += lowbit(j))
				tr[j].mdy(X[b[i]], 1);
		}
	}
	while (m--) {
		int opt = read();
		if (opt == 1) {
			int l = read(), r = read(), L = read(), R = read(), res = 0;
			int ll = id[L], rr = id[R];
			if (ll == rr) {
				for (int i = L; i <= R; i++) if (l <= X[b[i]] && X[b[i]] <= r) res++;
			} else {
				for (int i = L; id[i] == ll; i++) 
					if (l <= X[b[i]] && X[b[i]] <= r) res++;
				for (int i = R; id[i] == rr; i--) 
					if (l <= X[b[i]] && X[b[i]] <= r) res++;
				res += qry(rr - 1, l, r) - qry(ll, l, r);
			}
			write(res), puts("");
		} else {
			int l = read(), r = read(), ll = id[l], rr = id[r];
			for (int x = ll; x <= len; x += lowbit(x)) tr[x].mdy(X[b[l]], -1);
			for (int x = rr; x <= len; x += lowbit(x)) tr[x].mdy(X[b[r]], -1);
			for (int x = ll; x <= len; x += lowbit(x)) tr[x].mdy(X[b[r]], 1);
			for (int x = rr; x <= len; x += lowbit(x)) tr[x].mdy(X[b[l]], 1);
			swap(b[l], b[r]);
		}
	}
}
```

分块加值域分块：
```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(2e5 + 50), maxk(450);
int n, m, sqn, len, x[maxn], y[maxn], pb[maxn], id[maxn], b[maxk][maxk], c[maxk][maxn];

int main () {
	n = read(), m = read(), sqn = sqrt(n), len = (n - 1) / sqn + 1;
	for (int i = 1; i <= n; i++) id[i] = (i - 1) / sqn + 1;
	for (int i = 1; i <= n; i++) x[i] = read(), pb[x[i]] = i;
	for (int i = 1; i <= n; i++) y[i] = read();
	for (int now = 1, i = 1; now <= len; now++) {
		for (int j = 1; j <= n; j++) c[now][j] = c[now - 1][j];
		for (int j = 1; j <= len; j++) b[now][j] = b[now - 1][j];
		for (; id[i] == now; i++) {
			int v = pb[y[i]];
			b[now][id[v]]++;
			c[now][v]++;
		}
	}
	while (m--) {
		int opt = read(), l = read(), r = read();
		if (opt == 1) {
			int L = read(), R = read(), LL = id[L], RR = id[R], res = 0;
			if (LL == RR) {
				for (int i = L; i <= R; i++) if (l <= pb[y[i]] && pb[y[i]] <= r) res++;
			} else {
				int ll = id[l], rr = id[r];
				for (int i = L; id[i] == LL; i++) if (l <= pb[y[i]] && pb[y[i]] <= r) res++;
				for (int i = R; id[i] == RR; i--) if (l <= pb[y[i]] && pb[y[i]] <= r) res++;
				if (ll == rr) {
					for (int i = l; i <= r; i++) res += c[RR - 1][i] - c[LL][i];
				} else {
					for (int i = l; id[i] == ll; i++) res += c[RR - 1][i] - c[LL][i];
					for (int i = r; id[i] == rr; i--) res += c[RR - 1][i] - c[LL][i];
					for (int i = ll + 1; i < rr; i++) res += b[RR - 1][i] - b[LL][i];
				}
			}
			write(res), puts("");
		} else {
			if (l > r) swap(l, r);
			int ll = id[l], rr = id[r];
			int v = pb[y[r]];
			for (int i = ll; i < rr; i++) b[i][id[v]]++, c[i][v]++;
			v = pb[y[l]];
			for (int i = ll; i < rr; i++) b[i][id[v]]--, c[i][v]--;
			swap(y[l], y[r]);
		}
	}
}
```

---

## 作者：fastle (赞：3)

这里给出一种分块写法
对a,b都进行分块， 预处理b的每个块在a的每个块中的贡献。
然后对于这个贡献数组进行前缀和。
预处理复杂度是O(n)的。
然后查询的时候， 整块之间可以枚举b块， 前缀和统计答案， 零碎部分暴力处理即可。
对于修改， 我们发现只有两个块的前缀和改变了， 对于这两个块暴力重构即可。
```cpp
/*
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<cmath>
#define M 503
#define N 201000
#define ll long long
using namespace std;

int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
ll f[M][M], sum[M][M];
int a[N], b[N];
int belong[N];
int id[N], zd[N];
int n, m, biao;
int main() {
	//freopen(".in", "r", stdin), freopen(".out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read(), id[a[i]] = i;
	for(int i = 1; i <= n; i++) b[i] = read(), zd[b[i]] = i;
	biao = sqrt(n);
	for(int i = 1; i <= n; i++) belong[i] = (i - 1) / biao + 1;
	for(int i = 1; i <= n; i++) {
		int op = id[b[i]];
		int zz = belong[op];
		f[zz][belong[i]]++;
	}
	for(int i = 1; i <= belong[n]; i++) {
		for(int j = 1; j <= belong[n]; j++) {
			sum[i][j] = sum[i - 1][j] + f[i][j];
		}
	}
	while(m--) {
		int op = read();
		int ans = 0;
		if(op == 1) {
			int aa = read(), bb = read(), c = read(), d = read();
			for(int i = aa; i <= min(belong[aa] * biao, bb); i++) {
				if(zd[a[i]] >= c && zd[a[i]] <= d) ans++;
			}
			if(belong[aa] != belong[bb]) {
				for(int i = (belong[bb] - 1) * biao + 1; i <= bb; i++)
					if(zd[a[i]] >= c && zd[a[i]] <= d) ans++;
			}
			int ln = belong[aa], rn = belong[bb] - 1;

			for(int i = c; i <= min(belong[c] * biao, d); i++) if(id[b[i]] >= belong[aa] * biao + 1 && id[b[i]] <= (belong[bb] - 1) * biao) ans++;
			if(belong[c] != belong[d]) {
				for(int i = (belong[d] - 1) * biao + 1; i <= d; i++)
					if(id[b[i]] >= belong[aa] * biao + 1 && id[b[i]] <= (belong[bb] - 1) * biao) ans++;
			}
			if(ln <= rn) for(int i = belong[c] + 1; i <= belong[d] - 1; i++) ans += sum[rn][i] - sum[ln][i];
			cout << ans << "\n";
		} else {
			int aa = read(), bb = read();
			int op = id[b[aa]], zz = belong[op];
			f[zz][belong[aa]]--;
			op = id[b[bb]], zz = belong[op];
			f[zz][belong[bb]]--;
			zd[b[aa]] = bb;
			zd[b[bb]] = aa;
			swap(b[aa], b[bb]);
			op = id[b[aa]], zz = belong[op];
			f[zz][belong[aa]]++;
			op = id[b[bb]], zz = belong[op];
			f[zz][belong[bb]]++;
			aa = belong[aa], bb = belong[bb];
			for(int i = 1; i <= belong[n]; i++) sum[i][aa] = sum[i - 1][aa] + f[i][aa], sum[i][bb] = sum[i - 1][bb] + f[i][bb];
		}
	}
	return 0;
}
```

---

## 作者：litble (赞：2)

思路：时间线段树+扫描线

考虑没有修改操作。假设某个数字在$a$中的位置为$x$，在$b$中的位置为$y$，则看做一个点$(x,y)$。那么一个询问就是查询一个矩形内的点数，这个是个经典问题，可以扫描线解决。

现在有了修改操作，就上一棵时间线段树。将一个点覆盖在它出现的时间区间内，一个询问则在从单独代表这个询问的时间的线段树节点到线段树的根的路径上都放一个，遍历线段树的时候，对于每个节点上放的询问们和点们，都做一遍扫描线。

复杂度$O(n \log^2 n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
const int N=200005;
int n,m,qcnt;
int a[N],X[N],T[N],ans[N],s[N];
struct node{int x,Y1,Y2,id;};
vector<node> tr[N<<2];

void insq(int x,int s,int t,int i,node k) {//将询问放在时间线段树上
	tr[i].push_back(k); if(s==t) return;
	int mid=(s+t)>>1;
	if(x<=mid) insq(x,s,mid,i<<1,k);
	else insq(x,mid+1,t,(i<<1)|1,k);
}
void insp(int l,int r,int s,int t,int i,node k) {//将点放在时间线段树上
	if(l<=s&&t<=r) {tr[i].push_back(k);return;}
	int mid=(s+t)>>1;
	if(l<=mid) insp(l,r,s,mid,i<<1,k);
	if(mid+1<=r) insp(l,r,mid+1,t,(i<<1)|1,k);
}

bool cmp(node A,node B) {return A.x==B.x?A.id==0:A.x<B.x;}
int lowbit(int x) {return x&(-x);}
void add(int x,int v) {while(x<=n) s[x]+=v,x+=lowbit(x);}
int query(int x) {int re=0; while(x) re+=s[x],x-=lowbit(x); return re;}
void work(int s,int t,int i) {
	sort(tr[i].begin(),tr[i].end(),cmp);//扫描线
	int sz=tr[i].size();
	for(RI j=0;j<sz;++j) {
		if(!tr[i][j].id) add(tr[i][j].Y1,1);
		else {
			int kl=query(tr[i][j].Y2)-query(tr[i][j].Y1-1);
			if(tr[i][j].id<0) ans[-tr[i][j].id]-=kl;
			else ans[tr[i][j].id]+=kl;
		}
	}
	for(RI j=0;j<sz;++j) if(!tr[i][j].id) add(tr[i][j].Y1,-1);
	if(s==t) return;
	int mid=(s+t)>>1;
	work(s,mid,i<<1),work(mid+1,t,(i<<1)|1);
}

int main()
{
	int op,X1,Y1,X2,Y2;
	n=read(),m=read();
	for(RI i=1;i<=n;++i) a[read()]=i;
	for(RI i=1;i<=n;++i) X[i]=a[read()],T[i]=0;
	for(RI i=1;i<=m;++i) {
		op=read();
		if(op==1) {
			X1=read(),X2=read(),Y1=read(),Y2=read(),++qcnt;
			insq(i,0,m,1,(node){X1-1,Y1,Y2,-qcnt});
			insq(i,0,m,1,(node){X2,Y1,Y2,qcnt});
		}
		else {
			X1=read(),X2=read();
			insp(T[X1],i-1,0,m,1,(node){X[X1],X1,0,0});
			insp(T[X2],i-1,0,m,1,(node){X[X2],X2,0,0});
			swap(X[X1],X[X2]),T[X1]=T[X2]=i;
		}
	}
	for(RI i=1;i<=n;++i) insp(T[i],m,0,m,1,(node){X[i],i,0,0});
	work(0,m,1);
	for(RI i=1;i<=qcnt;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

来一发 $O(n \sqrt n)$ 时间，$O(n)$ 空间的分块写法。

首先建模，把 **数值** $x$ 在两个数组中出现的位置作为坐标，问题就转化为一个二维动态数点。

考虑用序列分块维护第一维，第二维用 **值域分块** 维护，这样子平衡复杂度玩就得到一个 $O(n \sqrt n)$ 时间的做法，但是空间很大。

考虑到块与块之间并无联系，所以考虑 **逐块处理** 也就是说把每个块的修改与贡献离线下来分开计算，那么空间就被优化到了 $O(n)$。

综上，我们就可以写出代码了。

```cpp
#include<bits/stdc++.h>
#define int long long
//#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 6e5+114;
const int maxsq = 500;
const int warma = 447;
int n,cnt;
struct Node{
    int opt,x,l,r,L,R;
}Q[maxn];
int anser[maxn];
pair<int,int> wyb[maxn],zbz[maxn];//处理时的数组 & 原本的数组
int val(int l1,int r1,int l2,int r2){//计算两个区间的交集大小
    int mxl=max(l1,l2),mir=min(r1,r2);
    if(mxl>mir) return 0;
    else return (mir-mxl+1);
}
class block{//O(\sqrt n) 区间修改 O(1) 区间查询 
	private:
		int bl_pre[maxsq][maxsq];//块内前缀和
		int tag[maxsq];//块内标记 
		int pre[maxsq];//块间前缀和
	public:
		void add(int l,int r,int v);
		int query(int l,int r);
        void init();
}chifan;
void block::init(){
    for(int i=0;i<maxsq;i++)
        for(int j=0;j<maxsq;j++)
            bl_pre[i][j]=tag[i]=pre[i]=0;
}
void block::add(int l,int r,int v){
	int bl=l/warma;
	int lpos=l%warma;
	if(lpos==0){
		lpos=warma;
		bl--;
	}
	int br=r/warma;
	int rpos=r%warma;
	if(rpos==0){
		rpos=warma;
		br--;
	}
	//整块处理 
    if(bl==br){
        for(int i=lpos;i<=rpos;i++){
            bl_pre[bl][i]+=v*(i-lpos+1);
        }
        for(int i=rpos+1;i<=warma;i++){
            bl_pre[bl][i]+=v*(rpos-lpos+1);
        }
        pre[0]=bl_pre[0][warma];
	    for(int i=1;i<=warma;i++){
		    pre[i]=pre[i-1]+bl_pre[i][warma]+tag[i]*warma;
	    }
        return ;
    }
	for(int i=bl+1;i<=br-1;i++){
		tag[i]+=v;
	}
	//头部残块处理
	for(int i=lpos;i<=warma;i++){
		bl_pre[bl][i]+=v*(i-lpos+1); 
	}
	//尾部残块处理
	for(int i=1;i<=rpos;i++){
		bl_pre[br][i]+=v*i;
	}
	for(int i=rpos+1;i<=warma;i++){
		bl_pre[br][i]+=v*rpos;
	}
	//块间处理
	pre[0]=bl_pre[0][warma];
	for(int i=1;i<=warma;i++){
		pre[i]=pre[i-1]+bl_pre[i][warma]+tag[i]*warma;
	} 
    return ;
}
int block::query(int l,int r){
    int bl=l/warma;
	int lpos=l%warma;
	if(lpos==0){
		lpos=warma;
		bl--;
	}
	int br=r/warma;
	int rpos=r%warma;
	if(rpos==0){
		rpos=warma;
		br--;
	}
    if(bl==br){
        return bl_pre[bl][rpos]-bl_pre[bl][lpos-1]+tag[bl]*(rpos-lpos+1);
    }
    int res=0;
    res+=pre[br-1]-pre[bl];
    res+=bl_pre[bl][warma]-bl_pre[bl][lpos-1]+(warma-lpos+1)*tag[bl];
    res+=bl_pre[br][rpos]+tag[br]*rpos;
    return res;
}
void work(int lt,int rt){//逐块处理
    rt=min(rt,n);
    chifan.init();
    for(int i=1;i<=n;i++) wyb[i]=zbz[i];
    for(int i=lt;i<=rt;i++){
        chifan.add(wyb[i].first,wyb[i].second,1);
    }
    for(int i=1;i<=cnt;i++){
        if(Q[i].opt==1){
            int l=Q[i].l,r=Q[i].r,L=Q[i].L,R=Q[i].R;
            if(l<=lt&&rt<=r){//被包含
                anser[i]+=chifan.query(L,R);
            }
            else if(lt<=l&&r<=rt){//另外一种被包含
                int res=0;
                for(int i=l;i<=r;i++){
                    res+=val(wyb[i].first,wyb[i].second,L,R);
                }
                anser[i]+=res;
            }
            else if(rt>=r&&r>=lt){
                int res=0;
                for(int i=lt;i<=r;i++){
                    res+=val(wyb[i].first,wyb[i].second,L,R);
                }
                anser[i]+=res;
            }
            else if(lt<=l&&l<=rt){
                int res=0;
                for(int i=l;i<=rt;i++){
                    res+=val(wyb[i].first,wyb[i].second,L,R);
                }
                anser[i]+=res;
            }
        }
        else{
            int x=Q[i].x,l=Q[i].l,r=Q[i].r;
            if(lt<=x&&x<=rt){
                chifan.add(wyb[x].first,wyb[x].second,-1);
                wyb[x].first=l,wyb[x].second=r;
                chifan.add(wyb[x].first,wyb[x].second,1);
            }
        }
    }
}
int sq;
int q;
int a[maxn],b[maxn];
int A[maxn],B[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	sq=sqrt(n);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		A[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		B[b[i]]=i;
	}
	for(int i=1;i<=n;i++){
		zbz[A[i]].first=B[i];
		zbz[A[i]].second=B[i];
	}
	for(int i=1;i<=q;i++){
		int OPT;
		cin>>OPT;
		if(OPT==1){
			int la,ra,lb,rb;
			cin>>la>>ra>>lb>>rb;
			cnt++;
			Q[cnt].opt=1;
			Q[cnt].l=la;
			Q[cnt].r=ra;
			Q[cnt].L=lb;
			Q[cnt].R=rb;
		}
		else{
			int x,y;
			cin>>x>>y;
			//b[x] - A[b[x]] x -> A[b[x]] y
			//b[y] - A[b[y]] y -> A[b[y]] x
			//b[x] - b[y]
			//B[b[x]]
			cnt++;
			Q[cnt].opt=2;
			Q[cnt].x=A[b[x]];
			Q[cnt].l=y;
			Q[cnt].r=y;
			cnt++;
			Q[cnt].opt=2;
			Q[cnt].x=A[b[y]];
			Q[cnt].l=x;
			Q[cnt].r=x;
			swap(b[x],b[y]);
			swap(B[b[x]],B[b[y]]);
		}
	}
	int L=1,R=sq;
	while(L<=n){
    	work(L,R);
   		L+=sq,R+=sq;
	}
	for(int i=1;i<=cnt;i++){
    	if(Q[i].opt==1) cout<<anser[i]<<'\n';
	}
}
/*
6 2
5 1 4 2 3 6
2 5 3 1 4 6
2 2 4
1 2 3 3 5
*/
```

题外话：这一道题我口胡过一个线段加和一个二维数最大值的加强版（而且写出来了，这题代码就是这么改出来的）。

---

## 作者：lzyqwq (赞：1)

[**更好的阅读体验**](https://www.cnblogs.com/MnZnOIerLzy/articles/17166143.html)

# $\texttt{Description}$

[**Codeforces 题目链接**](https://codeforces.com/problemset/problem/1093/E "Codeforces 题目链接")

[**洛谷题目链接**](https://www.luogu.com.cn/problem/CF1093E "洛谷题目链接")

> - 给定两个 $1\sim n$ 的排列 $a,b$。有 $m$ 次操作：
>
>     - $\texttt{1 }l_a\texttt{ }r_a\texttt{ }l_b\texttt{ }r_b$，查询 $|\{a_i|l_a\le i\le r_a\}\cap\{b_j|l_b\le j\le r_b\}|$。
>
>     - $\texttt{2 }x\texttt{ }y$，交换 $b_x,b_y$。
>
> - $n,m\le 2\times 10^5$。

# $\texttt{Solution}$

首先发现查询的限制不太好处理，又由于两个数组都是排列，可以考虑建立映射：$p_{a_i}=i$。

然后 $\{a_i|l_a\le i\le r_a\}\cap\{b_j|l_b\le j\le r_b\}$ 等价于 $\{p_{a_i}|l_a\le i\le r_a\}\cap \{p_{b_j}|l_b\le j\le r_b\}$，即 $\{a_i|l_a\le i\le r_a\}\cap\{b_j|l_b\le j\le r_b\}$ 等价于 $\{i|l_a\le i\le r_a\}\cap\{p_{b_j}|l_b\le j\le r_b\}$。因为相同值的 $p$ 值肯定相同，交集中还是这些值的贡献。

所以要求的就是 $p_{b_{l_b}}\sim p_{b_{r_b}}$ 之间在 $l_a\sim r_a$ 范围内有几个数。考虑使用树状数组套平衡树维护。一开始先将 $k$ 位置插入 $p_{b_k}$，查询的时候统计前缀个数再差分，个数可以用**两端的排名之差 $+1$** 计算。

对于交换操作，**先删除原位置上的值**，再插入新位置上的值。因为要避免把新插入的给误删掉（我的平衡树去重）。最后要交换 $b_x$ 和 $b_y$。因为下一次交换操作是基于当前状态的。

时间复杂度为 $\mathcal{O}((n+m)\log^2n)$，空间复杂度为 $\mathcal{O}(n\log n)$，可以接受。优点是可以在线以及空间比树状数组套权值线段树小，缺点是常数较大。

# $\texttt{Code}$

代码要点：

- 本蒟蒻很菜不会写平衡树，所以用的是 `pb_ds` 库中的红黑树实现的，优点是现成、码量小且这种平衡树效率较高，缺点是难以可持久化或区间反转（貌似是这样的，因为我还没有实现过）、以及 `STL` 自带的大常数。

- 查询的时候有一些情况要舍去：

    - 当前区间内所有数均 $<l_a$。
	
	- 当前区间内所有数均 $>r_a$。

- 可以用指令集优化代码效率。

[**评测记录**](https://codeforces.com/contest/1093/submission/195268236 "**评测记录**")

  
$1.49\text{KB}$ 较短代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define N 200005
#define pbds __gnu_pbds
using namespace std;
int n,m,a[N],b[N],p[N];
pbds::tree<int,pbds::null_type,less<int>,pbds::rb_tree_tag,pbds::tree_order_statistics_node_update>bit[N];
void bit_insert(int x,int k){
    for(int i=x;i<=n;i+=i&-i){
        bit[i].insert(k);
    }
}
void bit_erase(int x,int k){
    for(int i=x;i<=n;i+=i&-i){
        bit[i].erase(k);
    }
}
int rbt_query(int x,int ql,int qr){
    auto l=bit[x].lower_bound(ql),r=bit[x].upper_bound(qr);
    if(l==bit[x].end()||r==bit[x].begin()){
        return 0;
    }
    return bit[x].order_of_key(*--r)-bit[x].order_of_key(*l)+1;
}
int bit_query(int l,int r,int ql,int qr){
    int ret=0;
    for(int i=r;i;i-=i&-i){
        ret+=rbt_query(i,ql,qr);
    }
    for(int i=l-1;i;i-=i&-i){
        ret-=rbt_query(i,ql,qr);
    }
    return ret;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d",a+i);
        p[a[i]]=i;
    }
    for(int i=1;i<=n;++i){
        scanf("%d",b+i);
        bit_insert(i,p[b[i]]);
    }
    for(int op,la,ra,lb,rb;m--;){
        scanf("%d%d%d",&op,&la,&ra);
        if(op&1){
            scanf("%d%d",&lb,&rb);
            printf("%d\n",bit_query(lb,rb,la,ra));
        }else{
            bit_erase(la,p[b[la]]);
            bit_erase(ra,p[b[ra]]);
            bit_insert(ra,p[b[la]]);
            bit_insert(la,p[b[ra]]);
            swap(b[la],b[ra]);
        }
    }
}
```

---

## 作者：yzy1 (赞：1)

- 记 $i$ 在 $a$ 中的下标为 $P(i)$，则 $1$ 操作转化为：给出 $l,r,L,R$，求满足 $l \le i \le r, L \le P(b_i) \le R$ 的点个数。可以发现是个动态二维数点问题。
- $2$ 操作相当于单点修改，或者说加一个点然后删一个点。

通常来讲我们可以同通过树套树解决，但是听说这题好像卡空间？就写了分块套 `bitset`，分块维护序列维，`bitset` 维护值域维。对于每个块记录第一个块到当前块所有 $a_i$ 以及 $b_i$ 的并集，用 `bitset` 的或运算维护之。直接预处理整块的前缀或，预处理复杂度就是 $O(n\sqrt n)$ 的。

- 对于 $1$ 操作，直接把右端点所在块对应的 `bitset` 和左端点所在对应的 `bitset` 异或差分一下，然后暴力统计散块贡献。时间复杂度 $O(n\sqrt n +\dfrac{n^2} w)$。
- 对于 $2$ 操作，发现最多会让 $O(\sqrt n)$ 个 `bitset` 中的值修改，遍历整块修改即可，每块都只会修改 $O(1)$ 个元素。时间复杂度 $O(n\sqrt n)$。

至此，我们以 $O(n \sqrt n + \dfrac{n^2} w)$ 的时间复杂度通过了该题。

[代码参考](https://codeforces.com/contest/1093/submission/148106655)。

---

## 作者：watermonster (赞：1)

翻译很清晰，就不再重复题意了。

 $a$ 和 $b$ 都是 $1$ 到 $n$ 的一个排列，所以我们可以记$ A_i$ 为 $i$ 在 $a$ 中的位置，  $B_i$ 为 $i$ 在 $b$ 中的位置，每次询问就是求有多少个 $i$ 满足 $la \le A_i \le ra$ 且 $lb \le B_i \le rb$ 。那么问题就变为一个很裸的二维数点了，直接用树状数组来维护$A$，套线段树维护$B$可以很轻松地解决这个问题。

由于题目修改操作只要求了交换两个数在 $b$ 排列中的位置，我们可以先在两个数原来的位置 $-1$ ，交换 $B$ 的值再在新的位置 $+1$ 。

注意修改操作很多，会产生大量无用节点，**一定要回收**！！（不然会RE/MLE）

代码（部分细节有出入）：

```cpp
#include <cstdio>

using namespace std;

#define il inline
#define re register

const int N=2e5+10;

namespace FastIO
{
char buf[1<<21],buf2[1<<21],*p1=buf,*p2=buf;
int p,p3=-1;
il int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
il void flush(){fwrite(buf2,1,p3+1,stdout),p3=-1;}
#define isdigit(ch) (ch>=48&&ch<=57)
template <typename T>
il void read(T &x)
{
	re bool f=0;x=0;
	re char ch=getc();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getc();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getc();
	x=f?-x:x;
}
template <typename T>
il void print(T x)
{
	if(p3>(1<<20)) flush();
	if(x<0) buf2[++p3]=45,x=-x;
	re int a[50]={};
	do{a[++p]=x%10+48;}while(x/=10);
	do{buf2[++p3]=a[p];}while(--p);
	buf2[++p3]='\n';
}
}
using namespace FastIO;
//IO优化

il void swap(int &a,int &b){a^=b^=a^=b;return;}

int rt[N],pool;
int bin[N<<7],top;
//废弃节点回收
il int newnode(){return top?bin[top--]:++pool;}
int ls[N<<7],rs[N<<7];
int cnt[N<<7];
il void deletnode(int &p){bin[++top]=p;p=0;return;}
il void insert(int &p,int l,int r,int pos,int x)
{
	if(!p) p=newnode();
	cnt[p]+=x;
	if(l==r) return;
	re int mid=(l+r)>>1;
	if(pos>mid) insert(rs[p],mid+1,r,pos,x);
	else insert(ls[p],l,mid,pos,x);
	if(!cnt[p]) deletnode(p);
	return;
}
il int query(int p,int l,int r,int L,int R)
{
	if(!p||l>R||r<L) return 0;
	if(l>=L&&r<=R) return cnt[p];
	re int mid=(l+r)>>1;
	return query(ls[p],l,mid,L,R)+query(rs[p],mid+1,r,L,R);
}

int n,m;
int a[N],b[N],B[N];

#define lowbit(x) (x&-x)
il void add(int x,int y,int z)
{
	for(re int i=x;i<=n;i+=lowbit(i))
		insert(rt[i],1,n,y,z);
	return;
}
il int ask(int xa,int xb,int ya,int yb)
{
	re int res=0;
	for(re int i=xb;i;i-=lowbit(i))
		res+=query(rt[i],1,n,ya,yb);
	for(re int i=xa-1;i;i-=lowbit(i))
		res-=query(rt[i],1,n,ya,yb);
    //减掉多加的
	return res;
}
il void Swap(int x,int y)
{
	add(a[B[x]],b[B[x]],-1);add(a[B[y]],b[B[y]],-1);
    //减掉原来的
	swap(B[x],B[y]);b[B[x]]=x;b[B[y]]=y;
	add(a[B[x]],b[B[x]],1);add(a[B[y]],b[B[y]],1);
    //加上新的
	return;
}

int main()
{
	read(n);read(m);
	for(re int i=1,x;i<=n;++i) read(x),a[x]=i;
	for(re int i=1;i<=n;++i) read(B[i]),b[B[i]]=i;
	for(re int i=1;i<=n;++i) add(a[i],b[i],1);
	re int opt,x,y,la,ra,lb,rb;
	while(m--)
	{
		read(opt);
		if(opt==1) read(la),read(ra),read(lb),read(rb),print(ask(la,ra,lb,rb));
		else read(x),read(y),Swap(x,y);
	}
	flush();return 0;
}
```



---

## 作者：XG_Zepto (赞：1)

文章首发于 [个人博客](https://zepto.page/post/codeforces-1093e)。

### 思路

看到这道题我第一个想法就是：带修改主席树。

令 $p_i$ 代表 $b_i$ 在 $a$ 中出现的位置，每次询问就是求区间 $[l_b,r_b]$ 中，权值在 $[l_a,r_a]$ 之间的数字个数，修改就是简单的单点修改。

静态主席树的写法大家非常清楚，我把它理解为前缀权值线段树。如何动态维护一个前缀数组呢？采用树状数组即可。我写的带修改主席树本质就是树状数组套主席树，树状数组上每个节点对应储存了相应区间信息的主席树。

这样写实测过不了。原因很简单，空间不够。但是这个东西还是很有用的（~~我写的也很好看~~），代码放在文章末尾了。

如何在 Codeforces 上通过此题？把主席树换成 $\text{pbds}$ 里的 红黑树 即可。

### 代码

以下是在 Codeforces 上可以通过的代码。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
#define maxn 2000100
#define pi pair<int,int>
#define mp make_pair
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <class T> using Tree=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
int read(){
	int x=0,flag=1;char ch=getchar();
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if (ch=='-') flag=-1,ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch-'0'),ch=getchar();
	return x*flag;
}
template <int size> struct rbtree{
	Tree<int> val[size+1];
	void update(int pos,int tag,int op){
		while(pos<=size){
			if (op) val[pos].insert(tag);
			else val[pos].erase(tag);
			pos+=(pos&-pos);
		}
	}
	int query(int pos,int tag){
		int res=0;
		while(pos){
			res+=val[pos].order_of_key(tag+1);
			pos-=(pos&-pos);
		}
		return res;
	}
	int query(int l,int r,int L,int R){
		return query(r,R)-query(r,L)-query(l,R)+query(l,L);
	}
};
rbtree<maxn>T;
int n,m,a[maxn],b[maxn],p[maxn];
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;++i)
		a[i]=read(),p[a[i]]=i;
	for (int i=1;i<=n;++i)
		b[i]=read(),b[i]=p[b[i]],T.update(i,b[i],1);
	for (int i=1,op,l,r,L,R;i<=m;++i){
		op=read();
		if (op==1){
			l=read(),r=read(),L=read(),R=read();
			printf("%d\n",T.query(L-1,R,l-1,r));
		}
		if (op==2){
			l=read(),r=read();
			T.update(l,b[l],0);T.update(r,b[r],0);
			swap(b[l],b[r]);
			T.update(l,b[l],1);T.update(r,b[r],1);
		}
	}
} 
```

以下是带修改主席树，在极限数据下爆空间了。

```cpp
#include <bits/stdc++.h>
#define maxn 200100
#define mid ((l+r)>>1)
#define logn 100
int rt[maxn],ts[maxn*135],ls[maxn*135],rs[maxn*135];
int a[maxn],b[maxn],A[maxn],B[maxn],C[maxn],la,lb,cnt,n,m;
void update(int &p,int f,int l,int r,int x,int v){
	if (!p) p=++cnt;ts[p]+=v;
	if (l>=r) return;
	if (mid>=x) update(ls[p],p,l,mid,x,v);
	else update(rs[p],p,mid+1,r,x,v);
}
int query(int p,int l,int r,int L,int R){
	if (L<=l&&r<=R) return ts[p];
	if (mid>=R) return query(ls[p],l,mid,L,R);
	if (mid<L) return query(rs[p],mid+1,r,L,R);
	return query(ls[p],l,mid,L,R)+query(rs[p],mid+1,r,L,R);
}
void change(int x,int y){
	int fx=B[x],fy=B[y];
	for (int i=fx;i<=n;i+=(i&-i)) update(rt[i],0,1,n,x,-1);
	for (int i=fy;i<=n;i+=(i&-i)) update(rt[i],0,1,n,y,-1);
	for (int i=fx;i<=n;i+=(i&-i)) update(rt[i],0,1,n,y,1);
	for (int i=fy;i<=n;i+=(i&-i)) update(rt[i],0,1,n,x,1);
	std::swap(B[x],B[y]);
}
void get(int l,int r,int L,int R){
	int sum=0;l--;
	for (int i=l;i;i-=(i&-i)) sum-=query(rt[i],1,n,L,R);
	for (int i=r;i;i-=(i&-i)) sum+=query(rt[i],1,n,L,R);
	printf("%d\n",sum);
}
int main(){
	freopen("test.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",a+i);
	for (int i=1;i<=n;++i) scanf("%d",b+i);
	for (int i=1;i<=n;++i) B[b[i]]=i;
	for (int i=1;i<=n;++i) A[i]=B[a[i]];
	for (int i=1;i<=n;++i) C[a[i]]=i;
	for (int i=1;i<=n;++i) B[i]=C[b[i]];
	for (int i=1;i<=n;++i)
		for (int j=i;j<=n;j+=(j&-j))
			update(rt[j],0,1,n,A[i],1);
	for (int i=1,op,a,b,c,d;i<=m;++i){
		scanf("%d",&op);
		if (op==2) scanf("%d%d",&a,&b),change(a,b);
		if (op==1) scanf("%d%d%d%d",&a,&b,&c,&d),get(a,b,c,d);
	}
}
```

---

## 作者：Aleph1022 (赞：1)

本文同步发表于我的博客：https://demo.alpha1022.me/articles/fa5a1270.htm

打完比赛之后在比赛公告的评论区发现了一种分块思路。

我一看，数据结构题诶。  
但是不会做。  
写了个分块 + bitset 上去成功 TLE 飞。

如前文所说，在评论区发现了这样一种思路：  
设 $sum_{i,j}$ 表示 $b$ 的第 $i$ 块与 $a$ 的**前** $j$ 块有多少个数相同。  
设 $place_{a,i}$ 表示 $i$ 在 $a$ 中的编号，设 $place_{b,i}$ 表示 $i$ 在 $b$ 中的编号。

然后查询我们先处理 $b$ 的完整块，  
我们用 $sum$ 数组计算 $a$ 的完整块对 $b$ 的完整块的答案贡献，  
再用 $place_b$ 计算 $a$ 的角块对 $b$ 的完整块的答案贡献。

接着处理 $b$ 的角块，这个就用 $place_a$ 计算答案的贡献。

由于 $sum$ 数组第二维是前缀和，所以我们能以修改从 $O(1)$ 退化成 $O(\sqrt{n})$ 的代价，保证查询的复杂度为 $O(\sqrt{n})$ 而没有退化成 $O(n)$。

代码：
```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int BUFF_SIZE = 1 << 20;
char BUFF[BUFF_SIZE],*BB,*BE;
#define gc() (BB == BE ? (BE = (BB = BUFF) + fread(BUFF,1,BUFF_SIZE,stdin),BB == BE ? EOF : *BB++) : *BB++)
template<class T>
inline void read(T &x)
{
	x = 0;
	char ch = 0,w = 0;
	while(ch < '0' || ch > '9')
		w |= ch == '-',ch = gc();
	while(ch >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch ^ '0'),ch = gc();
	w ? x = -x : x;
}

const int N = 2e5;
const int BLOCK_NUM = 500;
int n,m;
int ind[2][N + 10];
int a[2][N + 10];
int block,pos[N + 10];
int cnt[BLOCK_NUM + 10][BLOCK_NUM + 10];
int sum[BLOCK_NUM + 10][BLOCK_NUM + 10];
int main()
{
	read(n),read(m);
	block = sqrt(n);
	for(register int i = 1;i <= n;++i)
		read(a[0][i]),pos[i] = (i - 1) / block + 1,ind[0][a[0][i]] = i;
	for(register int i = 1;i <= n;++i)
		read(a[1][i]),ind[1][a[1][i]] = i,++cnt[pos[i]][pos[ind[0][a[1][i]]]];
	for(register int i = 1;i <= pos[n];++i)
		for(register int j = 1;j <= pos[n];++j)
			sum[i][j] = sum[i][j - 1] + cnt[i][j];
	int op,l1,r1,l2,r2;
	while(m--)
	{
		read(op),read(l1),read(r1);
		if(op == 1)
		{
			int ans = 0;
			read(l2),read(r2);
			if(pos[l1] + 1 < pos[r1])
				for(register int i = pos[l2] + 1;i < pos[r2];++i)
					ans += sum[i][pos[r1] - 1] - sum[i][pos[l1]];
			for(register int i = l1;i <= min(pos[l1] * block,r1);++i)
				ans += pos[l2] + 1 <= pos[ind[1][a[0][i]]] && pos[ind[1][a[0][i]]] <= pos[r2] - 1;
			if(pos[l1] ^ pos[r1])
				for(register int i = (pos[r1] - 1) * block + 1;i <= r1;++i)
					ans += pos[l2] + 1 <= pos[ind[1][a[0][i]]] && pos[ind[1][a[0][i]]] <= pos[r2] - 1;

			for(register int i = l2;i <= min(pos[l2] * block,r2);++i)
				ans += l1 <= ind[0][a[1][i]] && ind[0][a[1][i]] <= r1;
			if(pos[l2] ^ pos[r2])
				for(register int i = (pos[r2] - 1) * block + 1;i <= r2;++i)
					ans += l1 <= ind[0][a[1][i]] && ind[0][a[1][i]] <= r1;
			printf("%d\n",ans);
		}
		else
		{
			--cnt[pos[l1]][pos[ind[0][a[1][l1]]]],--cnt[pos[r1]][pos[ind[0][a[1][r1]]]];
			swap(a[1][l1],a[1][r1]);
			ind[1][a[1][l1]] = l1,ind[1][a[1][r1]] = r1;
			++cnt[pos[l1]][pos[ind[0][a[1][l1]]]],++cnt[pos[r1]][pos[ind[0][a[1][r1]]]];
			for(register int i = 1;i <= pos[n];++i)
				sum[pos[l1]][i] = sum[pos[l1]][i - 1] + cnt[pos[l1]][i],sum[pos[r1]][i] = sum[pos[r1]][i - 1] + cnt[pos[r1]][i];
		}
	}
}
```



---

## 作者：Fzrcy (赞：0)

首先将将 $b_i$ 的定义改为 $b_i$ 在 $a$ 中出现的位置 $pos$，那么询问操作就是询问 $b_{[l_b,r_b]}$ 中有几个数的值在 $[l_a,r_a]$ 中。

因为时间有 $\texttt{6.00 S}$ 且 $n,m\le 2\times 10^5$，所以~~考虑分块~~。

根据套路，进行块内排序，对于询问操作，散块直接暴力统计，整块直接二分求出值在 $[l_a,r_a]$ 的个数。对于修改操作，直接暴力重构该块，总时间复杂度 $O(n\log n + m\sqrt{n}\log n)$。

[代码](https://codeforces.com/contest/1093/submission/204582814)。

---

## 作者：allenchoi (赞：0)

### 前言：  
考完期中码力下滑严重，调了 $114514$ 天。  
### 科技：  
CDQ 分治   
### 思路：  
我们先令 $p_x$ 表示元素 $x$ 在 $a$ 中的位置，再把 $b_i$ 赋值为 $p_{b_i}$。  
这样，原排列 $b$ 的第 $i$ 个元素在 $a,b$ 的位置就分别是 $b_i,i$，交换 $b$ 的第 $A,B$ 为也就等价于交换 $b_A,b_B$。

我们再把题目抽象化一下：    
第一，平面上有 $n$ 个点 $(b_i,i)$，与原来的 $n$ 个元素一一对应；  
第二，查询操作：求有多少个点的横坐标在 $[l1,r1]$ 之间且纵坐标在 $[l2,r2]$ 之间（求的方法类似二位前缀和，见代码）；  
第三，交换操作：将点 $(b_x,x)$ 与 $(b_y,y)$ 删去，加入 $(b_y,x),(b_x,y)$ 两点。  

进一步地，删点可视为将其权值减一，加点可视为将其权值加一，查询也就变为了求区间内的权值和。  
接着我们发现，我们发现还要考虑时间顺序，也就是要做三维偏序，于是也就自然而然地想到 CDQ 分治了。   
### 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n,m,tot,cnt,op,A,B,C,D,b[N],p[N],ans[N],tr[N * 5],rk[N * 5];
struct node{int op,x,y,w;} s[N * 5];
//各种操作加起来最大会是5n
int lowbit(int x){return x & (-x);}
void update(int p,int v){for(int i = p;i <= tot;i += lowbit(i)) tr[i] += v;}
int query(int p)
{
	int ret = 0;
	for(int i = p;i;i -= lowbit(i)) ret += tr[i];
	return ret;
}
bool cmp(int x,int y){return s[x].x != s[y].x ? s[x].x < s[y].x : x < y;}
void gb_sort(int l,int r)
{
	if(l == r) return ;
	int mid = (l + r) / 2;
	gb_sort(l,mid);
	gb_sort(mid + 1,r);
	for(int i = l;i <= r;i++) rk[i] = i;
	sort(rk + l,rk + r + 1,cmp);
	for(int i = l;i <= r;i++)
	{
		if(rk[i] <= mid && s[rk[i]].op == -1) update(s[rk[i]].y,s[rk[i]].w);
		if(rk[i] > mid && s[rk[i]].op != -1) ans[s[rk[i]].op] += query(s[rk[i]].y) * s[rk[i]].w;
	}
	for(int i = l;i <= mid;i++) if(s[i].op == -1) update(s[i].y,-s[i].w);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&A);
		p[A] = i;
	}
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&b[i]);
		b[i] = p[b[i]];
	}
	tot = n;
	for(int i = 1;i <= n;i++) s[i] = (node){-1,b[i],i,1};
	for(int i = 1;i <= m;i++)
	{
		scanf("%d",&op);
		if(op == 1)
		{
			scanf("%d%d%d%d",&A,&B,&C,&D);
			cnt++; 
			s[++tot] = (node){cnt,B,D,1};
			s[++tot] = (node){cnt,A - 1,D,-1};
			s[++tot] = (node){cnt,B,C - 1,-1};
			s[++tot] = (node){cnt,A - 1,C - 1,1};
        //以原点为左下角，(x,y)为右上角构成的矩形内的权值和
		}
		else
		{
			scanf("%d%d",&A,&B);
			s[++tot] = (node){-1,b[A],A,-1};
			s[++tot] = (node){-1,b[B],B,-1};
			swap(b[A],b[B]);
			s[++tot] = (node){-1,b[A],A,1};
			s[++tot] = (node){-1,b[B],B,1};
		}
	}
	gb_sort(1,tot);
	for(int i = 1;i <= cnt;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

经典动态二维数点。

考虑令 $f_{a_i}=i$，则询问 $l_a\ r_a\ l_b\ r_b$ 相当于询问 $l_a\le f_{b_i}\le r_a,l_b\le i\le r_b$ 的 $i$ 的个数。

树套树维护 $f_{b_i}$，交换相当于单点修改。

平板电视真的很好写。
```cpp
#include <cstdio>
#include <algorithm>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
using namespace std;
using namespace __gnu_pbds;
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
inline int R()
{
    int r = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        r = r * 10 + c - '0', c = getchar();
    return r;
}
void P(int x)
{
    if (x >= 10)
        P(x / 10);
    *O++ = x % 10 + '0';
}
int n, m, a[200001], b[200001], k[200001];
struct T
{
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> c;
    inline void C(int x, int k)
    {
        if (k == 1)
            c.insert(x);
        else
            c.erase(x);
    }
    inline int Q(int x, int y) { return c.order_of_key(y + 1) - c.order_of_key(x); }
} c[200001];
inline void C(int x, int y, int k)
{
    for (; x <= n; x += x & -x)
        c[x].C(y, k);
}
inline int Q(int x, int y, int s, int t)
{
    int q = 0;
    for (--x; y > x; y &= y - 1)
        q += c[y].Q(s, t);
    for (; x > y; x &= x - 1)
        q -= c[x].Q(s, t);
    return q;
}
int main()
{
    n = R();
    m = R();
    for (int i = 1; i <= n; ++i)
        k[a[i] = R()] = i;
    for (int i = 1; i <= n; ++i)
        C(i, k[b[i] = R()], 1);
    for (int i = 0, o, x, y, p, q; i < m; ++i)
    {
        o = R();
        x = R();
        y = R();
        if (o & 1)
            p = R(), q = R(), P(Q(p, q, x, y)), *O++ = '\n';
        else
            C(x, k[b[x]], -1), C(y, k[b[y]], -1), swap(b[x], b[y]), C(x, k[b[x]], 1), C(y, k[b[y]], 1);
    }
    fwrite(obuf, O - obuf, 1, stdout);
    return 0;
}
```


---

## 作者：ghj1222 (赞：0)

我们构造出一个新数组c[i]，使得若a[j]==b[i]则c[i]=j，那么我们容易发现查询相当于查询c数组下标bl..br范围内元素在al..ar的数字个数，每次交换b[x]和b[y]就相当于交换c[x]和c[y]

然后显然这可以用树套树维护，首先发现线段树套set过不了，我先写了个线段树套平衡树，卡了卡常，本机刚好卡进去，交CF上T了。。。（我是平衡树绝症患者，写平衡树要写一小时）

然后我又把线段树改为树状数组，由于树状数组不好卡常，都没线段树快

由于我写的是高常数的Treap，所以我把Treap换成了动态开点权值线段树。。然而空间复杂度由$O(n\log n)$卡成$O(n\log^2n)$了，必须得写内存回收然后才A

权值线段树内存回收和平衡树内存回收差不多就是当某一个节点所有儿子的权值都是0，就把这个节点删除（地址扔垃圾桶），动态开点优先从垃圾桶取内存

下面是乱七八糟的代码，代码里直接把b数组当成上面说得c了，id存储的是a数组的反函数


```cpp
#include <bits/stdc++.h>
using namespace std;

int a[200010], b[200010], n, m;
int id[200010], root[200010];
int tree[35000010], l[35000010], r[35000010], tot;
int laji[20000010], top;

void add(int &x, int cl, int cr, int pos, int val)
{
	if (x == 0)
	{
		if (top > 0)
			x = laji[top--];
		else
			x = ++tot;
	}
	if (cl == cr)
	{
		tree[x] += val;
		if (tree[x] == 0)
		{
			laji[++top] = x;
			x = 0;
		}
		return;
	}
	int mid = (cl + cr) / 2;
	if (pos > mid)
		add(r[x], mid + 1, cr, pos, val);
	else
		add(l[x], cl, mid, pos, val);
	tree[x] = tree[l[x]] + tree[r[x]];
	if (l[x] == 0 && r[x] == 0)
	{
		laji[++top] = x;
		x = 0;
	}
}

int get(int x, int cl, int cr, int pos)
{
	if (x == 0)
		return 0;
	if (cl == cr)
		return cl <= pos ? tree[x] : 0;
	int mid = (cl + cr) / 2;
	if (pos > mid)
		return tree[l[x]] + get(r[x], mid + 1, cr, pos);
	else
		return get(l[x], cl, mid, pos);
}

void chenge(int x, int val, int key)
{
	for (int i = x; i <= n; i += i & -i)
		add(root[i], 1, n, val, key);
}

int query(int x, int val)
{
	int res = 0;
	for (int i = x; i > 0; i -= i & -i)
		res += get(root[i], 1, n, val);
	return res;
}

inline void read(int &x)
{
	static char ch;
	x = 0;
	ch = getchar();
	while (!isdigit(ch))
		ch = getchar();
	while (isdigit(ch))
		x = x * 10 + ch - 48, ch = getchar();
}

int main()
{
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		read(a[i]), id[a[i]] = i;
	for (int i = 1; i <= n; i++)
		read(b[i]), b[i] = id[b[i]];
	for (int i = 1; i <= n; i++)
		chenge(i, b[i], 1);
	for (int la, ra, lb, rb, x, y, opd, i = 1; i <= m; i++)
	{
		read(opd);
		if (opd == 1)
		{
			read(la), read(ra), read(lb), read(rb);
			printf("%d\n", query(rb, ra) + query(lb - 1, la - 1) - query(rb, la - 1) - query(lb - 1, ra));
		}
		else
		{
			read(x), read(y);
			chenge(x, b[x], -1);
			chenge(y, b[y], -1);
			swap(b[x], b[y]);
			chenge(x, b[x], 1);
			chenge(y, b[y], 1);
		}
	}
	return 0;
}
```

---

## 作者：Owen_codeisking (赞：0)

我居然一发最优解？~~可能 $CF$ 做的人比较少~~

我瞎 $yy$ 了一个既不是整体二分又不是 $CDQ$ 分治的东西，居然过了。。。

首先，这是一个排列！说明我们可以计算贡献，转换为二维数点问题，询问 $l_1\leq pos_a\leq r_1,l_2\leq pos_b\leq r_2$ 的个数，差分一下就好了。

那么我们考虑 $[l,mid]$ 的操作对 $[mid+1,r]$ 的操作的贡献，中间用树状数组维护就行了。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=200000+10;
int n,m,a[maxn],b[maxn],posa[maxn],posb[maxn],c[maxn],ans[maxn],cnt,tot;

struct Query{
	int op,x,y,v,id;
}q[maxn*5],q1[maxn*5],q2[maxn*5];

inline void read(int &x){
	x=0;int f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	if(f==-1) x=-x;
}

inline void add(int x,int y){
	for(;x<=n;x+=lowbit(x)) c[x]+=y;
}
inline int sum(int x){
	int ans=0;
	for(;x;x-=lowbit(x)) ans+=c[x];
	return ans;
}

void solve(int L,int R,int l,int r){
	if(L>R) return ;
	if(l==r){
		for(int i=L;i<=R;i++){
			if(q[i].op==1) add(q[i].y,q[i].v);
			if(q[i].op==2) ans[q[i].id]+=q[i].v*sum(q[i].y);
		}
		for(int i=L;i<=R;i++)
			if(q[i].op==1) add(q[i].y,-q[i].v);
		return ;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
	for(int i=L;i<=R;i++){
		if(q[i].x<=mid){
			if(q[i].op==1) add(q[i].y,q[i].v);
			q1[++cnt1]=q[i];
		}
		else {
			if(q[i].op==2) ans[q[i].id]+=q[i].v*sum(q[i].y);
			q2[++cnt2]=q[i];
		}
	}
	for(int i=L;i<=R;i++)
		if(q[i].x<=mid&&q[i].op==1) add(q[i].y,-q[i].v);
	for(int i=1;i<=cnt1;i++) q[L+i-1]=q1[i];
	for(int i=1;i<=cnt2;i++) q[L+i+cnt1-1]=q2[i];
	solve(L,L+cnt1-1,l,mid);solve(L+cnt1,R,mid+1,r);
}

int main()
{
	read(n),read(m);
	int op,x,y,l,r;
	for(int i=1;i<=n;i++) read(a[i]),posa[a[i]]=i;
	for(int i=1;i<=n;i++) read(b[i]),posb[b[i]]=i;
	for(int i=1;i<=n;i++) q[++cnt]=(Query){1,posa[i],posb[i],1,0};
	for(int i=1;i<=m;i++){
		read(op),read(x),read(y);
		if(op==1){
			read(l),read(r);
			q[++cnt]=(Query){2,y,r,1,++tot};
			if(x>1) q[++cnt]=(Query){2,x-1,r,-1,tot};
			if(l>1) q[++cnt]=(Query){2,y,l-1,-1,tot};
			if(x>1&&l>1) q[++cnt]=(Query){2,x-1,l-1,1,tot};
		}
		else {
			q[++cnt]=(Query){1,posa[b[x]],x,-1,0};
			q[++cnt]=(Query){1,posa[b[y]],y,-1,0};
			swap(posb[b[x]],posb[b[y]]);swap(b[x],b[y]);
			q[++cnt]=(Query){1,posa[b[x]],x,1,0};
			q[++cnt]=(Query){1,posa[b[y]],y,1,0};
		}
	}
	solve(1,cnt,1,n);
	for(int i=1;i<=tot;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

