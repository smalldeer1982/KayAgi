# Fast Matrix Operations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3143

[PDF](https://uva.onlinejudge.org/external/119/p11992.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11992/9b4b07db5bbb2af0ec8d2e58971ff9ef667aba18.png)

## 样例 #1

### 输入

```
4 4 8
1 1 2 4 4 5
3 2 1 4 4
1 1 1 3 4 2
3 1 2 4 4
3 1 1 3 4
2 2 1 4 4 2
3 1 2 4 4
1 1 1 4 3 3```

### 输出

```
45 0 5
78 5 7
69 2 7
39 2 7```

# 题解

## 作者：轻尘 (赞：5)

## Fast Matrix Operations

~~一点也不~~毒瘤的题目。

由于行数不超过20，用不超过20个线段树存下每一行的数字，同时维护最大最小和区间和。

**赋值的标记优先级比加标记的优先级要高。**

**每次赋值的时候，要把加标记清空。**

相当于加标记只存在于赋值以后。

标记和最大最小维护方法与线段树基本相同pushup()就好了。

注意行列的关系。

------------

由于我个人眼瞎，把行列看反了，

直接导致每次查询时间复杂度从

$O(rlogc)$ 变成了 $O(clogr)(r<=20,c<=1e6)$ 

QAQ请勿效仿。

------

献上一篇巨丑的代码，采用最原始的方法，没有写结构体。

用了dfs序建树同时清空数组。

写了三个询问。。。。（略加卡常，因为我之前实在不知道为什么T了）

## code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e7+9;
int tree[30],r,c,m,T;
int mi[maxn],ma[maxn],sum[maxn],lson[maxn],rson[maxn],tag[maxn],st[maxn];
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
inline void pushup(int rt)
{
    ma[rt]=max(ma[lson[rt]],ma[rson[rt]]);
    mi[rt]=min(mi[lson[rt]],mi[rson[rt]]);
    sum[rt]=sum[lson[rt]]+sum[rson[rt]];
}
inline void pushdown(int rt,int l,int r)
{
    int mid=(l+r)>>1;
    if(st[rt])
    {
        st[lson[rt]]=st[rt];
        st[rson[rt]]=st[rt];
        mi[lson[rt]]=st[rt];
        ma[lson[rt]]=st[rt];
        mi[rson[rt]]=st[rt];
        ma[rson[rt]]=st[rt];
        sum[lson[rt]]=st[rt]*(mid-l+1);
        sum[rson[rt]]=st[rt]*(r-mid);
        tag[lson[rt]]=tag[rson[rt]]=0;
        st[rt]=0;
    }
    if(tag[rt])
    {
	    tag[lson[rt]]+=tag[rt];
	    tag[rson[rt]]+=tag[rt];
	    mi[lson[rt]]+=tag[rt];
	    ma[lson[rt]]+=tag[rt];
	    mi[rson[rt]]+=tag[rt];
	    ma[rson[rt]]+=tag[rt];
	    sum[lson[rt]]+=tag[rt]*(mid-l+1);
	    sum[rson[rt]]+=tag[rt]*(r-mid);
	    tag[rt]=0;
	}
}
inline int build(int l,int r)
{
    int rt=++T;
    tag[rt]=sum[rt]=mi[rt]=ma[rt]=st[rt]=0;
    if(l==r)
    {
        sum[rt]=mi[rt]=ma[rt]=0;
        lson[rt]=rson[rt]=0;
        return rt;
    }
    int mid=(l+r)>>1;
    lson[rt]=build(l,mid);
    rson[rt]=build(mid+1,r);
    pushup(rt);
    return rt;
}
inline void add(int rt,int l,int r,int ll,int rr,int w)
{
    if(ll<=l&&rr>=r)
    {
        tag[rt]+=w;
        sum[rt]+=w*(r-l+1);
        mi[rt]+=w;
        ma[rt]+=w;
        return ;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if(ll<=mid) add(lson[rt],l,mid,ll,rr,w);
    if(mid<rr) add(rson[rt],mid+1,r,ll,rr,w);
    pushup(rt);
}
inline void set(int rt,int l,int r,int ll,int rr,int w)
{
    if(ll<=l&&rr>=r)
    {
        sum[rt]=(r-l+1)*w;
        tag[rt]=0;
        ma[rt]=w;
        mi[rt]=w;
        st[rt]=w;
        return ;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if(ll<=mid) set(lson[rt],l,mid,ll,rr,w);
    if(mid<rr) set(rson[rt],mid+1,r,ll,rr,w);
    pushup(rt);
}
inline int all_query(int rt,int l,int r,int ll,int rr)
{
    if(ll<=l&&rr>=r)
        return sum[rt];
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    int ans=0;
    if(ll<=mid) ans+=all_query(lson[rt],l,mid,ll,rr);
    if(rr>mid) ans+=all_query(rson[rt],mid+1,r,ll,rr);
    return ans;
}
inline int max_query(int rt,int l,int r,int ll,int rr)
{
    if(ll<=l&&rr>=r)
        return ma[rt];
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    int ans=-0x3f3f3f3f;
    if(ll<=mid) ans=max(ans,max_query(lson[rt],l,mid,ll,rr));
    if(rr>mid) ans=max(ans,max_query(rson[rt],mid+1,r,ll,rr));
    return ans;
}
inline int min_query(int rt,int l,int r,int ll,int rr)
{
    if(ll<=l&&rr>=r)
        return mi[rt];
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    int ans=0x3f3f3f3f;
    if(ll<=mid) ans=min(ans,min_query(lson[rt],l,mid,ll,rr));
    if(rr>mid) ans=min(ans,min_query(rson[rt],mid+1,r,ll,rr));
    return ans;
}
int main()
{
    while(~scanf("%d%d%d",&r,&c,&m))
    {
    	T=0;
        for(register int i=1;i<=r;i++)
            tree[i]=build(1,c);
        for(register int i=1;i<=m;i++)
        {
            int opt,x1,x2,y1,y2;
            scanf("%d%d%d%d%d",&opt,&x1,&y1,&x2,&y2);
            if(opt==1)
            {
                int v;scanf("%d",&v);
                for(register int i=x1;i<=x2;i++)
                    add(tree[i],1,c,y1,y2,v);
            }
            if(opt==2)
            {
                int v;scanf("%d",&v);
                for(register int i=x1;i<=x2;i++)
                    set(tree[i],1,c,y1,y2,v);
            }
            if(opt==3)
            {
                int all=0,minn=0x3f3f3f,maxx=-0x3f3f3f;
                for(register int i=x1;i<=x2;i++)
                {
                    all+=all_query(tree[i],1,c,y1,y2);
                    minn=min(minn,min_query(tree[i],1,c,y1,y2));
                    maxx=max(maxx,max_query(tree[i],1,c,y1,y2));
                }
                printf("%d %d %d\n",all,minn,maxx);
            }
        }
    }
    return 0;
}
```

-----------
### Think twice , code once .....



---

## 作者：andyli (赞：3)

矩阵不超过$20$行，矩阵元素却可能多达$10^6$个，可以想到每行建一棵线段树，则本题转化为一维问题。  
本题有两个操作，add与set，因此需要两个标记addv与$setv$。  
注意，对于set操作要清除结点上的addv标记，但对于add操作不清除setv标记，还要在pushdown函数中先考虑setv再考虑addv。  
由于每组数据处理前都必须清空每行的线段树，耗时严重，可在每组数据时按行数用new/delete建树。  
代码如下：  
```cpp
#include <algorithm>
#include <cstdio>
#define lc (o << 1)
#define rc (o << 1 | 1)
using namespace std;
const int maxn = 1000005, INF = -1u / 2; // -1u/2=INT_MAX

struct Tree {
    struct Node {
        int sumv, maxv, minv, addv, setv;
    };
    Node tree[maxn << 2];
    void build(int o, int l, int r)
    {
        if (l == r) {
            tree[o].sumv = tree[o].maxv = tree[o].minv = tree[o].addv = 0;
            tree[o].setv = -1;
            return;
        }
    }
    void maintain(int o)
    {
        tree[o].sumv = tree[lc].sumv + tree[rc].sumv;
        tree[o].maxv = max(tree[lc].maxv, tree[rc].maxv);
        tree[o].minv = min(tree[lc].minv, tree[rc].minv);
    }
    void pushdown(int o, int l, int r)
    { // 若setv与addv同时有效，必然set操作在前，因为在set操作时已将addv置0
        int m = (l + r) >> 1;
        if (tree[o].setv >= 0) {
            tree[lc].setv = tree[rc].setv = tree[o].setv;
			tree[lc].addv = tree[rc].addv = 0; // 处理setv时要将左右儿子addv清零。
            tree[lc].sumv = (m - l + 1) * tree[o].setv;
            tree[rc].sumv = (r - m) * tree[o].setv;
            tree[lc].minv = tree[lc].maxv = tree[rc].minv = tree[rc].maxv = tree[o].setv;
            tree[o].setv = -1; // 标记置0
        } // 先处理setv
        if (tree[o].addv) {
            tree[lc].addv += tree[o].addv;
            tree[rc].addv += tree[o].addv;
            tree[lc].sumv += (m - l + 1) * tree[o].addv;
            tree[rc].sumv += (r - m) * tree[o].addv;
            tree[lc].minv += tree[o].addv;
            tree[lc].maxv += tree[o].addv;
            tree[rc].minv += tree[o].addv;
            tree[rc].maxv += tree[o].addv;
            tree[o].addv = 0; // 标记置0
        }
    }
    void modify1(int o, int l, int r, int x, int y, int v) // add操作
    {
        if (x <= l && r <= y) { // setv不变
            tree[o].addv += v;
            tree[o].sumv += (r - l + 1) * v;
            tree[o].minv += v;
            tree[o].maxv += v;
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if (x <= m)
            modify1(lc, l, m, x, y, v);
        if (y > m)
            modify1(rc, m + 1, r, x, y, v);
        maintain(o);
    }
    void modify2(int o, int l, int r, int x, int y, int v) // set操作
    {
        if (x <= l && r <= y) {
            tree[o].addv = 0; // 将addv置0
			tree[o].setv = v;
            tree[o].sumv = (r - l + 1) * v;
            tree[o].minv = tree[o].maxv = v;
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if (x <= m)
            modify2(lc, l, m, x, y, v);
        if (y > m)
            modify2(rc, m + 1, r, x, y, v);
        maintain(o);
    }
    Node query(int o, int l, int r, int x, int y)
    {
        if (x <= l && r <= y)
            return tree[o];
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if (x > m)
            return query(rc, m + 1, r, x, y);
        if (y <= m)
            return query(lc, l, m, x, y);
        Node ans, ans1 = query(lc, l, m, x, y), ans2 = query(rc, m + 1, r, x, y); // 合并左右儿子返回的信息
        ans.sumv = ans1.sumv + ans2.sumv;
        ans.maxv = max(ans1.maxv, ans2.maxv);
        ans.minv = min(ans1.minv, ans2.minv);
        return ans;
    }
};

int main()
{
    int r, c, m;
    while (~scanf("%d%d%d", &r, &c, &m)) {
        Tree* tree = new Tree[r + 1]; // 动态开内存(tree[0]~tree[r])
        for (int i = 1; i <= c; i++)
            tree[i].build(1, 1, c); // 建树
        while (m--) {
            int opt, x1, y1, x2, y2, v;
            scanf("%d%d%d%d%d", &opt, &x1, &y1, &x2, &y2);
            if (opt == 1) {
                scanf("%d", &v);
                for (int i = x1; i <= x2; i++)
                    tree[i].modify1(1, 1, c, y1, y2, v);
            } else if (opt == 2) {
                scanf("%d", &v);
                for (int i = x1; i <= x2; i++)
                    tree[i].modify2(1, 1, c, y1, y2, v);
            } else {
                int sum = 0, minn = INF, maxx = -INF;
                for (int i = x1; i <= x2; i++) {
                    auto ans = tree[i].query(1, 1, c, y1, y2);
                    sum += ans.sumv;
                    minn = min(minn, ans.minv);
                    maxx = max(maxx, ans.maxv);
                }
                printf("%d %d %d\n", sum, minn, maxx);
            }
        }
        delete[] tree; // 释放内存
    }
    return 0;
}
```

---

## 作者：Tenshi (赞：2)

蓝书（训练指南）的线段树例题。

## 分析
这题在思维上并不复杂，是线段树的常见操作。

需要注意的地方主要是标记优先级：

> 这里我像蓝书一样记增加标记为 $addv$，赋值标记记为 $setv$。

当遇到赋值操作的时候，相应节点的 $addv$ 需要进行清零，因为当你下传 $setv$ 的过程中的子节点的 $addv$ 都会被覆盖掉。

然后查询因为信息比较多，我比较推荐直接返回区间合并得到的全部信息，这样可以少写很多函数。

吐槽：

写的时候看反 `op1, op2` 了，还有把书上的 $m$ 误以为是列数，~~我自裁~~。

不过交一发就到了最优解前列 hh。

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define debug(x) cerr << #x << ": " << x << endl
#define pb push_back
#define eb emplace_back
#define set0(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define INF 0x3f3f3f3f

inline void read(int &x) {
    int s=0;x=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

#define y1 Tenshi

const int N=1e6+10;

struct SegTree{
	struct Node{
		int l, r;
		int sum, v[2];
		
		#define ls(u) u<<1
		#define rs(u) u<<1|1
	}tr[N<<2];
	
	int len[N<<2];
	int addv[N<<2], setv[N<<2];
	
	Node merge(Node a, Node b){
		return {a.l, b.r, a.sum+b.sum, min(a.v[0], b.v[0]), max(a.v[1], b.v[1])};
	}
	
	void F(int u, int op, int v){
		if(op==0){
			addv[u]=0, setv[u]=v;
			tr[u].sum=len[u]*v, tr[u].v[0]=tr[u].v[1]=v;
		}
		else{
			addv[u]+=v;
			tr[u].sum+=len[u]*v, tr[u].v[0]+=v, tr[u].v[1]+=v;
		}
	}
	
	void pushdown(int u){
		if(~setv[u]){
			F(ls(u), 0, setv[u]), F(rs(u), 0, setv[u]);
			setv[u]=-1;
		}
		if(addv[u]){
			F(ls(u), 1, addv[u]), F(rs(u), 1, addv[u]);
			addv[u]=0;
		}
	}
	
	void build(int u, int l, int r){
		len[u]=r-l+1, setv[u]=-1;
		if(l==r) return tr[u]={l, r}, void();
		int mid=l+r>>1;
		build(ls(u), l, mid), build(rs(u), mid+1, r);
		tr[u]=merge(tr[ls(u)], tr[rs(u)]);
	}
	
	Node query(int u, int l, int r){
		if(tr[u].l>=l && tr[u].r<=r) return tr[u];
		int mid=tr[u].l+tr[u].r>>1;
		Node L={-1}, R={-1};
		pushdown(u);
		if(mid>=l) L=query(ls(u), l, r);
		if(mid<r) R=query(rs(u), l, r);
		if(L.l==-1) return R; if(R.l==-1) return L;
		return merge(L, R);
	}
	
	void upd(int u, int l, int r, int v, int op){
		if(tr[u].l>=l && tr[u].r<=r){
			F(u, op, v);
			return;
		}
		pushdown(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(mid>=l) upd(ls(u), l, r, v, op);
		if(mid<r) upd(rs(u), l, r, v, op);
		tr[u]=merge(tr[ls(u)], tr[rs(u)]);
	}
};

int n, m, q;

int main(){
	while(cin>>n>>m>>q){
		SegTree* tree=new SegTree[n+1];
		rep(i,1,n) tree[i].build(1, 1, m);
		
		while(q--){
			int op; read(op);
			int x1, y1, x2, y2; read(x1), read(y1), read(x2), read(y2);
			
			if(op==1){
				int v; read(v);
				rep(i,x1,x2) tree[i].upd(1, y1, y2, v, 1);
			}
			else if(op==2){
				int v; read(v);
				rep(i,x1,x2) tree[i].upd(1, y1, y2, v, 0);
			}
			else if(op==3){
				int sum=0, mn=INF, mx=0;
				rep(i,x1,x2){
					auto res=tree[i].query(1, y1, y2);
					sum+=res.sum, mn=min(mn, res.v[0]), mx=max(mx, res.v[1]);
				}
				cout<<sum<<' '<<mn<<' '<<mx<<endl;
			}
		}
	}
    return 0;
}
```

---

## 作者：risingstar (赞：2)

看到大佬们都用20个线段树A掉了这个题，那蒟蒻我就来发一篇和他们不同的题解。


既然是矩阵，而如果是一维的操作又和线段树相似，那么为什么不尝试用二维线段树（四分树）来做这个题呢？
```c
#include<stdio.h> 
int hl[8000001];//左上子矩阵
int hr[8000001];//右上子矩阵
int ul[8000001];//左下子矩阵
int ur[8000001];//右下子矩阵
int t[8000001],ma[8000001],mi[8000001];//分别存和、最小值，最大值
int lazya[8000001],lazys[8000001];//两种懒惰标记
int L,R,H,U;
int sum=1;//节点个数
void build(int i,int l,int r,int h,int u)//建立矩阵，确定每个父节点的儿子的下标
{
	if(l==r&&h==u)return;
	int tm=l+r>>1,vm=h+u>>1;
	if(tm>=l&&vm>=h){
		hl[i]=++sum;
		build(hl[i],l,tm,h,vm);
	}
	if(r>tm&&vm>=h){
		hr[i]=++sum;
		build(hr[i],tm+1,r,h,vm);
	}
	if(tm>=l&&u>vm){
		ul[i]=++sum;
		build(ul[i],l,tm,vm+1,u);
	}
	if(r>tm&&u>vm){
		ur[i]=++sum;
		build(ur[i],tm+1,r,vm+1,u);
	}
}
int max(int i)//求出子节点最大值
{
	int ans=0;
	if(ans<ma[hl[i]]&&hl[i])ans=ma[hl[i]];
	if(ans<ma[hr[i]]&&hr[i])ans=ma[hr[i]];
	if(ans<ma[ul[i]]&&ul[i])ans=ma[ul[i]];
	if(ans<ma[ur[i]]&&ur[i])ans=ma[ur[i]];
	return ans;
}
int min(int i)//求出子节点最小值
{
	int ans=1e9;
	if(ans>mi[hl[i]]&&hl[i])ans=mi[hl[i]];
	if(ans>mi[hr[i]]&&hr[i])ans=mi[hr[i]];
	if(ans>mi[ul[i]]&&ul[i])ans=mi[ul[i]];
	if(ans>mi[ur[i]]&&ur[i])ans=mi[ur[i]];
	return ans;
}
void pushup(int i)//利用子节点更新父节点
{
	t[i]=t[hl[i]]+t[hr[i]]+t[ul[i]]+t[ur[i]];
	ma[i]=max(i);
	mi[i]=min(i);
}
void pushdown(int i,int l,int r,int h,int u)
{
	int tm=l+r>>1,vm=h+u>>1;
	if(lazys[i]){
		if(hl[i]){
			lazys[hl[i]]=ma[hl[i]]=mi[hl[i]]=lazys[i];
			t[hl[i]]=(tm-l+1)*(vm-h+1)*lazys[i];
			lazya[hl[i]]=0;
		}
		if(hr[i]){
			lazys[hr[i]]=ma[hr[i]]=mi[hr[i]]=lazys[i];
			t[hr[i]]=(r-tm)*(vm-h+1)*lazys[i];
			lazya[hr[i]]=0;
		}
		if(ul[i]){
			lazys[ul[i]]=ma[ul[i]]=mi[ul[i]]=lazys[i];
			t[ul[i]]=(tm-l+1)*(u-vm)*lazys[i];
			lazya[ul[i]]=0;
		}
		if(ur[i]){
			lazys[ur[i]]=ma[ur[i]]=mi[ur[i]]=lazys[i];
			t[ur[i]]=(r-tm)*(u-vm)*lazys[i];
			lazya[ur[i]]=0;
		}
		lazys[i]=0;
	}
	if(lazya[i]){
		if(hl[i]){
            ma[hl[i]]+=lazya[i];
			mi[hl[i]]+=lazya[i];
			t[hl[i]]+=(tm-l+1)*(vm-h+1)*lazya[i];
			lazya[hl[i]]+=lazya[i];
		}
		if(hr[i]){
			ma[hr[i]]+=lazya[i];
			mi[hr[i]]+=lazya[i];
			t[hr[i]]+=(r-tm)*(vm-h+1)*lazya[i];
			lazya[hr[i]]+=lazya[i];
		}
		if(ul[i]){
			ma[ul[i]]+=lazya[i];
			mi[ul[i]]+=lazya[i];
			t[ul[i]]+=(tm-l+1)*(u-vm)*lazya[i];
			lazya[ul[i]]+=lazya[i];
		}
		if(ur[i]){
			ma[ur[i]]+=lazya[i];
			mi[ur[i]]+=lazya[i];
			t[ur[i]]+=(r-tm)*(u-vm)*lazya[i];
			lazya[ur[i]]+=lazya[i];
		}
		lazya[i]=0;
	}
}
void update(int i,int l,int r,int h,int u,int se,int k)//矩阵更新，se是更新方式（add或set）
{
	if(l>=L&&R>=r&&h>=H&&U>=u){
		if(se==1){
			t[i]+=(r-l+1)*(u-h+1)*k;
			ma[i]+=k;
			mi[i]+=k;
			lazya[i]+=k;
		}
		else{
			t[i]=(r-l+1)*(u-h+1)*k;
			ma[i]=k;
			mi[i]=k;
			lazys[i]=k;
			lazya[i]=0;
		}
		return;
	}
	pushdown(i,l,r,h,u);
	int tm=l+r>>1,vm=h+u>>1;
	if(L<=tm&&H<=vm&&hl[i])update(hl[i],l,tm,h,vm,se,k);
	if(tm<R&&H<=vm&&hr[i])update(hr[i],tm+1,r,h,vm,se,k);
	if(L<=tm&&vm<U&&ul[i])update(ul[i],l,tm,vm+1,u,se,k);
	if(tm<R&&vm<U&&ur[i])update(ur[i],tm+1,r,vm+1,u,se,k);
	pushup(i);
}
int ans,ansma,ansmi;
void query(int i,int l,int r,int h,int u)//查询值
{
	if(l>=L&&R>=r&&h>=H&&U>=u){
		ans+=t[i];
		if(ansma<ma[i])ansma=ma[i];
		if(ansmi>mi[i])ansmi=mi[i];
		return;
	}
	pushdown(i,l,r,h,u);
	int tm=l+r>>1,vm=h+u>>1;
	if(L<=tm&&H<=vm&&hl[i])query(hl[i],l,tm,h,vm);
	if(tm<R&&H<=vm&&hr[i])query(hr[i],tm+1,r,h,vm);
	if(L<=tm&&vm<U&&ul[i])query(ul[i],l,tm,vm+1,u);
	if(tm<R&&vm<U&&ur[i])query(ur[i],tm+1,r,vm+1,u);
} 
int main()
{
	int r,c,m,j,v;
	scanf("%d%d%d",&r,&c,&m);
	build(1,1,c,1,r);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d%d",&j,&H,&L,&U,&R);
		if(j<3){
			scanf("%d",&v);
			update(1,1,c,1,r,j,v);
	    }
		else{
			ans=0;
			ansma=0;
			ansmi=1e9;
			query(1,1,c,1,r);
			printf("%d %d %d\n",ans,ansmi,ansma);
		}
	}
}
}
```
总的来说，操作和普通线段树差不多，只不过每次要考虑四个儿子，写得比较麻烦。

可能是因为行数比较少，二维线段树的操作常数比较大，蒟蒻的这个代码用时比较长。。

---

## 作者：云浅知处 (赞：1)

注意到列数不超过 $20$，那对每一列直接开一个线段树，修改的时候就变成不超过 $20$ 次区间操作。

具体来说，如果这个修改的参数是 $x_1,y_1,x_2,y_2$，那我们就对 $[x_1,x_2]$ 之间的这些线段树都做一遍 $[y_1,y_2]$ 上的区间操作即可。

每一行上的线段树只需要支持区间覆盖，区间加，区间查询 min/max/sum，很好写。

复杂度是 $O(qr\log c)$。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define lson(o) (o<<1)
#define rson(o) (o<<1|1)
#define int long long
const int MN=100005;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

int a[MN];

struct SMT{
    int d[MN<<2],mn[MN<<2],mx[MN<<2],plz[MN<<2],mlz[MN<<2];

    inline void pushup(int o){
        d[o]=d[lson(o)]+d[rson(o)];
        mn[o]=min(mn[lson(o)],mn[rson(o)]);
        mx[o]=max(mx[lson(o)],mx[rson(o)]);
    }

    inline void pushdown(int o,int ql,int qr){
        int mid=(ql+qr)>>1;
        if(mlz[o]>=0){
            d[lson(o)]=(mid-ql+1)*mlz[o],d[rson(o)]=(qr-mid)*mlz[o];
            mn[lson(o)]=mn[rson(o)]=mx[lson(o)]=mx[rson(o)]=mlz[o];
            plz[lson(o)]=plz[rson(o)]=0;
            mlz[lson(o)]=mlz[rson(o)]=mlz[o];
            mlz[o]=-1;
        }
        if(plz[o]){
            d[lson(o)]+=(mid-ql+1)*plz[o],d[rson(o)]+=(qr-mid)*plz[o];
            mn[lson(o)]+=plz[o],mn[rson(o)]+=plz[o];
            mx[lson(o)]+=plz[o],mx[rson(o)]+=plz[o];
            plz[lson(o)]+=plz[o],plz[rson(o)]+=plz[o];
            plz[o]=0;
        }
    }

    inline void build(int l,int r,int o){
        plz[o]=0;mlz[o]=-1;
        if(l==r){d[o]=mn[o]=mx[o]=0;return ;}
        int mid=(l+r)>>1;
        build(l,mid,lson(o));
        build(mid+1,r,rson(o));
        pushup(o);
    }

    inline void add(int l,int r,int k,int ql,int qr,int o){
        if(l<=ql&&qr<=r){plz[o]+=k,d[o]+=(qr-ql+1)*k,mn[o]+=k,mx[o]+=k;return ;}
        pushdown(o,ql,qr);
        int mid=(ql+qr)>>1;
        if(l<=mid)add(l,r,k,ql,mid,lson(o));
        if(r>mid)add(l,r,k,mid+1,qr,rson(o));
        pushup(o);
    }

    inline void assign(int l,int r,int k,int ql,int qr,int o){
        if(l<=ql&&qr<=r){plz[o]=0,d[o]=(qr-ql+1)*k,mn[o]=mx[o]=mlz[o]=k;return ;}
        pushdown(o,ql,qr);
        int mid=(ql+qr)>>1;
        if(l<=mid)assign(l,r,k,ql,mid,lson(o));
        if(r>mid)assign(l,r,k,mid+1,qr,rson(o));
        pushup(o);
    }

    inline int querysum(int l,int r,int ql,int qr,int o){
        if(l<=ql&&qr<=r)return d[o];
        pushdown(o,ql,qr);
        int mid=(ql+qr)>>1,ans=0;
        if(l<=mid)ans+=querysum(l,r,ql,mid,lson(o));
        if(r>mid)ans+=querysum(l,r,mid+1,qr,rson(o));
        return ans;
    }

    inline int querymin(int l,int r,int ql,int qr,int o){
        if(l<=ql&&qr<=r)return mn[o];
        pushdown(o,ql,qr);
        int mid=(ql+qr)>>1,ans=2147483647;
        if(l<=mid)ans=min(ans,querymin(l,r,ql,mid,lson(o)));
        if(r>mid)ans=min(ans,querymin(l,r,mid+1,qr,rson(o)));
        return ans;
    }

    inline int querymax(int l,int r,int ql,int qr,int o){
        if(l<=ql&&qr<=r)return mx[o];
        pushdown(o,ql,qr);
        int mid=(ql+qr)>>1,ans=-2147483647;
        if(l<=mid)ans=max(ans,querymax(l,r,ql,mid,lson(o)));
        if(r>mid)ans=max(ans,querymax(l,r,mid+1,qr,rson(o)));
        return ans;
    }
};

SMT tree[25];

int r,c,t,n;

signed main(void){

    while(cin>>r>>c>>t){
        n=c;
        for(int i=1;i<=20;i++)tree[i].build(1,n,1);
        while(t--){
            int op,x,y,xx,yy,v;
            cin>>op>>x>>y>>xx>>yy;
            if(op==1){cin>>v;for(int i=x;i<=xx;i++)tree[i].add(y,yy,v,1,n,1);}
            if(op==2){cin>>v;for(int i=x;i<=xx;i++)tree[i].assign(y,yy,v,1,n,1);}
            if(op==3){
                int summ=0,maxx=-1,minn=2147483647;
                for(int i=x;i<=xx;i++){
                    summ+=tree[i].querysum(y,yy,1,n,1);
                    maxx=max(maxx,tree[i].querymax(y,yy,1,n,1));
                    minn=min(minn,tree[i].querymin(y,yy,1,n,1));
                }
                cout<<summ<<" "<<minn<<" "<<maxx<<endl;
            }
        }
        
    }

    return 0;
}
```

---

## 作者：Legitimity (赞：1)

先吐槽一句，这题数据真是水，在出题人普遍卡 ODT 的情况下，这题 ODT 竟然 130ms 跑完



------------

首先看到这道题，大部分人肯定首先想到二维线段树。

然后又看到 $r\leq 20$，那么连二维线段树都不用，只要开 20 颗线段树，暴力维护每一颗，时间复杂度为 $\Theta(Q \times r \log c)$。

但是，有没有更暴力的方法呢？既然操作中有推平操作，那么就考虑 ODT 的可能性。虽然题目没有保证数据随机，但是考虑到 UVa 的数据一般都很水，并且这题的时限是 5s，那么开 20 颗 ODT 也是可以的。

接下来就是维护 20 颗 ODT 了，三个操作都是 ODT 的经典操作，如果不会 ODT，出门左转 [CF896C](https://www.luogu.com.cn/problemnew/show/CF896C)。

放代码，不吸氧竟然是最优解，跑得比大部分线段树都快：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define inf 0x7f7f7f7f
#define sit set<odt>::iterator
#define mod 1000000007
inline int read(){
	rg int ret=0,f=0;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getchar();}
    return f?-ret:ret;
}
class Odt{
	public:
		struct odt{
			int l,r;
			mutable int val;
			odt(int x,int y,int z){
				l=x; r=y; val=z;
			}
			bool operator < (const odt& x)const{
				return l<x.l;
			}
		};
		set<odt> t;
		inline void newnode(int l,int r,int k){
			t.insert((odt){l,r,k});
		}
		inline sit split(int x){
			sit it=t.lower_bound((odt){x,0,0});
			if(it!=t.end()&&it->l==x) return it;
			--it;
			int sl=it->l,sr=it->r; int sv=it->val;
			t.erase(it);
			t.insert((odt){sl,x-1,sv});
			return t.insert((odt){x,sr,sv}).first;
		}
		inline void assi(int l,int r,int v){
			sit it2=split(r+1),it1=split(l);
			t.erase(it1,it2);
			t.insert((odt){l,r,v});
		}
		inline void add(int l,int r,int v){
			for(sit it2=split(r+1),it1=split(l);it1!=it2;++it1)
				it1->val+=v;
		}
		inline int sum(int l,int r){
			int res=0;
			for(sit it2=split(r+1),it1=split(l);it1!=it2;++it1)
				res+=it1->val*(it1->r-it1->l+1);
			return res;
		}
		inline int mx(int l,int r){
			int res=0;
			for(sit it2=split(r+1),it1=split(l);it1!=it2;++it1)
				res=max(res,it1->val);
			return res;
		}
		inline int mn(int l,int r){
			int res=inf;
			for(sit it2=split(r+1),it1=split(l);it1!=it2;++it1)
				res=min(res,it1->val);
			return res;
		}
}T[25]; //暴力维护 20 颗 ODT 
int r,c,m,opt,x,y,xx,yy,k;
int main(){
	r=read(); c=read(); m=read();
	for(rg int i=1;i<=r;++i){
		T[i].newnode(1,c,0);
	} //初始化，建出 r 颗树。 
	for(rg int i=1;i<=m;++i){
		opt=read(); x=read(); y=read(); xx=read(); yy=read();
		if(opt==1){
			k=read();
			for(rg int j=x;j<=xx;++j){ //维护每一行的 ODT，另外两个操作同理 
				T[j].add(y,yy,k);
			}
		}else if(opt==2){
			k=read();
			for(rg int j=x;j<=xx;++j){
				T[j].assi(y,yy,k);
			}
		}else{
			int mx=0,mn=inf,sum=0;
			for(rg int j=x;j<=xx;++j){
				sum+=T[j].sum(y,yy);
				mx=max(mx,T[j].mx(y,yy));
				mn=min(mn,T[j].mn(y,yy));
			}
			printf("%d %d %d\n",sum,mn,mx);
		}
	}
	return 0;
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/eso5v6nn.png)

---

## 作者：yizimi远欣 (赞：1)

### 题目描述

有一个r行c列的全0矩阵，有以下三种操作。

- 1 X1 Y1 X2 Y2 v 子矩阵（X1,Y1,X2,Y2）的元素加v

- 2 X1 Y1 X2 Y2 v 子矩阵（X1,Y1,X2,Y2）的元素变为v

- 3 X1 Y1 X2 Y2 查询子矩阵（X1,Y1,X2,Y2）的和，最大值，最小值

子矩阵（X1,Y1,X2,Y2）满足X1<=X<=X2 Y1<=Y<=Y2的所有元素（X1,Y2）。

输入保证和不超过10^9

#### 追加翻译：

数据范围：r <= 20！

### 主要思路：线段树 + 暴力枚举 ~~+ 懒人代码~~

我在追加翻译中强调了，r <= 20，也就是说，我们可以通过维护20棵线段树来维护矩阵的信息。也就是说，我们的中心任务放在了写一棵区间加，区间修改，维护区间和，区间最大值，最小值的一棵线段树。

…………

代码冗长……但是如何让自己的线段树更短更好写嘞？

首先，在下放标记时，我会调用这样的两个函数：


    inline void color_add(int l, int r, int rt, int v) {
        z[rt].maxx += v; 
        z[rt].minn += v;
        z[rt].sum += (r - l + 1) * v;
        z[rt].col += v;
    } 
    inline void color_chg(int l, int r, int rt, int v) {
        z[rt].maxx = z[rt].minn = v;
        z[rt].sum = (r - l + 1) * v;
        z[rt].coll = v;
        z[rt].col = 0;
    }

这两个函数分别是用来修改被下放的子节点的信息的。我们这样可以在下放标记时直接调用，甚至可以用来在修改操作时调用，节省大片代码。

然后对于询问操作，我们完全可以直接询问一组数据（一组数据就是一个区间的sum, max, min），我们用结构体实现。对于线段树左右节点的信息合并与询问时的信息合并，我们可以直接通过编写函数来简化代码。（细节就在下文代码里看吧）

我的代码是本题题解截止2019/02/22最短的代码（无注释无过度压行）。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define go(i, j, n, k) for(int i = j; i <= n; i += k)
#define mn 200100
#define inf 1 << 30
#define root 1, n, 1
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define bson l, r, rt
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -f; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
struct tree{
	int col, coll, minn, maxx, sum;
	tree(int _col = 0, int _coll = -1, int _minn = 0, int _maxx = 0, int _sum = 0) 	
		: col(_col), coll(_coll), minn(_minn), maxx(_maxx), sum(_sum) {}
};
// col -> 区间加的懒标记，coll -> 区间修改的懒标记
// 这里要注意，如果在另一个结构体中调用这个结构体，那么这个结构体最好要初始化一下，否则可能会出现问题。
// 我们用结构体的形式封装线段树，我们可以通过定义SegmentTree类型实现多棵线段树的实现
struct SegmentTree{
	tree z[mn << 2];
    // 使用外部的结构体类型
	inline tree op(tree a, tree b) {
		tree res;
		res.maxx = max(a.maxx, b.maxx);
		res.minn = min(a.minn, b.minn);
		res.sum = a.sum + b.sum;
		return res;
	}
    // 这里就是合并信息的懒人函数
	inline void update(int rt) {
		z[rt] = op(z[rt << 1], z[rt << 1 | 1]);
	}
	inline void color_add(int l, int r, int rt, int v) {
		z[rt].maxx += v;
		z[rt].minn += v;
		z[rt].sum += (r - l + 1) * v;
		z[rt].col += v;
	}
	inline void color_chg(int l, int r, int rt, int v) {
		z[rt].maxx = z[rt].minn = v;
		z[rt].sum = (r - l + 1) * v;
		z[rt].coll = v;
		z[rt].col = 0;
	}
	inline void push_col(int l, int r, int rt) {
		if(z[rt].coll != -1) { // 要注意初始时不能是0
			int m = (l + r) >> 1;
			color_chg(lson, z[rt].coll);
			color_chg(rson, z[rt].coll);
			z[rt].coll = -1;
		}
		if(z[rt].col) {
			int m = (l + r) >> 1;
			color_add(lson, z[rt].col);
			color_add(rson, z[rt].col);
			z[rt].col = 0;
		}
	}
	inline void modify(int l, int r, int rt, int nowl, int nowr, int v, int ver) {
		if(nowl <= l && r <= nowr) {
			if(ver == 1) color_add(bson, v);
			else if(ver == 2) color_chg(bson, v);
			return;
		}
		int m = (l + r) >> 1; push_col(bson);
		if(nowl <= m) modify(lson, nowl, nowr, v, ver);
		if(m < nowr)  modify(rson, nowl, nowr, v, ver);
		update(rt);
	}
	inline tree query(int l, int r, int rt, int nowl, int nowr) {
		if(nowl <= l && r <= nowr) return z[rt];
		int m = (l + r) >> 1; push_col(bson);
		if(nowl <= m) {
			if(m < nowr) return op(query(lson, nowl, nowr), query(rson, nowl, nowr));
			else return query(lson, nowl, nowr);
		} else return query(rson, nowl, nowr);
	}
	inline void build(int l, int r, int rt) {
		z[rt].col = 0, z[rt].coll = -1;
		if(l == r) {
			z[rt].minn = z[rt].maxx = z[rt].sum = 0;
			return ;
		}
		int m = (l + r) >> 1;
		build(lson), build(rson), update(rt);
	}
    // 这里建树代码其实是用来初始化的（多组数据嘛）
} tr[21];
int n, nn, m;

inline void solve() {
	go(i, 1, nn, 1) // 每行都要建树
		tr[i].build(root);
	go(i, 1, m, 1) {
		int s = read(), x = read(), y = read(), xx = read(), yy = read(), v;
		if(s == 1) {
			v = read();
			go(j, x, xx, 1) // 对每行的操作
				tr[j].modify(root, y, yy, v, 1);
		} else if(s == 2) {
			v = read();
			go(j, x, xx, 1) // 对每行的操作
				tr[j].modify(root, y, yy, v, 2); 
		} else {
			int maxx = 0, minn = inf, sum = 0;
			go(j, x, xx, 1) { // 对每行的操作
				tree res = tr[j].query(root, y, yy);
				maxx = max(maxx, res.maxx);
				minn = min(minn, res.minn);
				sum += res.sum;
			}
			printf("%d %d %d\n", sum, minn, maxx);
		}
	}
}
int main(){
	while(cin >> nn >> n >> m) {
		solve();
	}
	return 0;
}
```
#### 希望可以帮助到想简化代码的同学

---

## 作者：Mr_cold (赞：1)

暴力解法是直接建20颗线段树，直接每列搞就行了，没有啥说的，这里我用的结构体写线段树，可能会看的舒服一些
~~~
#include<bits/stdc++.h>
#define pts putchar('\n');
#define ptc putchar(' ');
using namespace std;
typedef long long ll;
const int maxm=2e6+9;
const int maxn=2e6+9;
const int N=200+9;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
const double eps=1e-4;
int r,c,m;

int read(){
    int a=1,b=0;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') a=-1;c=getchar();}
    while(c>='0'&&c<='9'){b=(b<<1)+(b<<3)+c-'0';c=getchar();}
    return a*b;
}
void print(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
struct SEG_TREE{
	int seg[maxn],lson[maxn],rson[maxn],minn[maxn],maxx[maxn],setv[maxn],addv[maxn];
	int rt,gen;
	void pre (){
		rt=1;gen=1;
		memset(setv,-1,sizeof(setv));
		memset(maxx,0,sizeof(maxx));
		memset(minn,0,sizeof(minn));
		memset(addv,0,sizeof(addv));
		memset(lson,0,sizeof(lson));
		memset(rson,0,sizeof(rson));
		memset(seg,0,sizeof(seg));
	}
	void pushup(int o){
		seg[o]=seg[lson[o]]+seg[rson[o]];
		minn[o]=min(minn[lson[o]],minn[rson[o]]);
		maxx[o]=max(maxx[lson[o]],maxx[rson[o]]);
	}
	void pushdown(int o,int l,int r){
		if(setv[o]!=-1)
		{
			int mid=(l+r)>>1;
			if(!lson[o]) lson[o]=++rt;
			if(!rson[o]) rson[o]=++rt;
			seg[lson[o]]=setv[o]*(mid-l+1);
			seg[rson[o]]=setv[o]*(r-mid);
			minn[lson[o]]=minn[rson[o]]=maxx[lson[o]]=maxx[rson[o]]=setv[o];
			setv[lson[o]]=setv[rson[o]]=setv[o];
			addv[lson[o]]=addv[rson[o]]=0;
			setv[o]=-1;
		}
		if(addv[o])
		{
			int mid=(l+r)>>1;
			if(!lson[o]) lson[o]=++rt;
			if(!rson[o]) rson[o]=++rt;
			seg[lson[o]]+=addv[o]*(mid-l+1);
			seg[rson[o]]+=addv[o]*(r-mid);
			maxx[rson[o]]+=addv[o];
			maxx[lson[o]]+=addv[o];
			minn[rson[o]]+=addv[o];
			minn[lson[o]]+=addv[o];
			addv[lson[o]]+=addv[o];
			addv[rson[o]]+=addv[o];
			addv[o]=0;
		}
	}
	void update(int &o,int l,int r,int L,int R,int val,int sign){
		if(!o) o=++rt;
		if(l>=L&&r<=R)
		{
			if(sign==1)
			{
				seg[o]+=val*(r-l+1);
				maxx[o]+=val;
				minn[o]+=val;
				addv[o]+=val;
			}
			else
			{
				seg[o]=val*(r-l+1);
				maxx[o]=minn[o]=val;
				setv[o]=val;addv[o]=0;
			}
			return;
		}
		int mid=(l+r)>>1;
		pushdown(o,l,r);
		if(mid>=L) update(lson[o],l,mid,L,R,val,sign);
		if(mid<R) update(rson[o],mid+1,r,L,R,val,sign);
		pushup(o);
	}
	int query(int o,int l,int r,int L,int R){
		if(l>=L&&r<=R) return seg[o];
		pushdown(o,l,r);
		int mid=(l+r)>>1;
		int ret=0;
		if(mid>=L) ret+=query(lson[o],l,mid,L,R);
		if(mid<R) ret+=query(rson[o],mid+1,r,L,R);
		return ret; 
	}
	int MAX(int o,int l,int r,int L,int R){
		if(l>=L&&r<=R) return maxx[o];
		pushdown(o,l,r);
		int mid=(l+r)>>1;
		int ret=-2147483646;
		if(mid>=L) ret=max(ret,MAX(lson[o],l,mid,L,R));
		if(mid<R) ret=max(ret,MAX(rson[o],mid+1,r,L,R));
		return ret; 
	}
	int MIN(int o,int l,int r,int L,int R){
		if(l>=L&&r<=R) return minn[o];
		pushdown(o,l,r);
		int mid=(l+r)>>1;
		int ret=2147483647;
		if(mid>=L) ret=min(ret,MIN(lson[o],l,mid,L,R));
		if(mid<R) ret=min(ret,MIN(rson[o],mid+1,r,L,R));
		return ret; 
	}
}T[21];
int main(){int A,B,C,D,E,flag;int ans1,ans2,ans3;
//	freopen("123.txt","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%d",&r);
	{
		c=read(),m=read();
		for(int i=1;i<=r;++i) T[i].pre();
		while(m--)
		{
			flag=read();A=read();C=read(),B=read(),D=read();
			if(flag==1)
			{
				E=read();
				for(int i=A;i<=B;++i)
				{
					T[i].update(T[i].gen,1,c,C,D,E,1);
				}
			}
			else if(flag==2)
			{
				E=read();
				for(int i=A;i<=B;++i)
				{
					T[i].update(T[i].gen,1,c,C,D,E,0);
				}
			}
			else 
			{
				ans1=0;ans2=-2147483646;ans3=2147483647;
				for(int i=A;i<=B;++i)
				{
					ans1+=T[i].query(T[i].gen,1,c,C,D);
					ans2=max(ans2,T[i].MAX(T[i].gen,1,c,C,D));
					ans3=min(ans3,T[i].MIN(T[i].gen,1,c,C,D));
				}
				print(ans1);ptc;print(ans3);ptc;print(ans2);pts;
			}
		//	for(int i=1;i<=r;++i){for(int j=1;j<=c;++j)	{print(T[i].query(1,1,c,j,j));putchar(' ');}puts("");}
		}
		//pts;
	}
    return 0;
} 
~~~

---

## 作者：Rye_Catcher (赞：1)

- 题目链接：

   https://www.luogu.org/problemnew/show/UVA11992
   
- 题目大意：

   一个r*c的矩阵，一开始元素都是0，然后给你m次三种操作，分别是将一个子矩阵中所有元素加上v，将一个子矩阵元素全部修改成v，询问一个子矩阵中所有元素和，最大值和最小值.
   
- 思路：

  应该说是一道有点毒瘤的数据结构题(然而时限居然给了5s)了，虽然它的主体只是线段树。我们可以把每一行都看作一棵线段树,这样操作就十分方便了。
  
  然后就是修改值的操作，对于初学者可能有点棘手，但实际上并不难，我们同样可以用lazy_tag打标记。但是就有一些要注意的东西了，当我们打add（元素加值）标记时是不会影响set（修改值）标记的，但是我们在打set标记时无论你前面add标记是多少，此时就相当于作废，所以直接将add标记赋为0就好了,然后直接修改sum,mi和mx(分别记录该区间的和，最小值，最大值)。
  
  同时我们可以让query询问函数直接返回一个存了sum,mi,mx的结构体，这样就不用查三次了.
  
  同时还有一个去要注意的地方,正如我们前面分析的那样,每一行开一颗线段树,但是实际上你真的不能搞一个tree[maxn],然后每一个tree中存一个线段树的结构体，这样是绝壁会爆的（我一开始就这么搞）,而是和平常一样搞一个存全部元素的数组，具体怎么做还请看代码,我自认为还是写的比较直观。
  
```
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;
const int maxn=1000005;
const int inf=0xfffffff;
int r,c,m,v;
int L,R;
struct Tmp{
    Tmp() : sum(0), mx(-inf),mi(inf) {}//构造函数，非常方便，强烈推荐
    Tmp(int x,int y,int z) :sum(x),mx(y),mi(z) {}
    int sum;
    int mx,mi;
};//query询问时直接返回这个结构体就好了
int sum[maxn<<2],add[maxn<<2],set[maxn<<2],mx[maxn<<2],mi[maxn<<2];
inline void up(int now){
    sum[now]=sum[now<<1]+sum[now<<1|1];
    mx[now]=max(mx[now<<1],mx[now<<1|1]);
    mi[now]=min(mi[now<<1],mi[now<<1|1]);
    return ;
}
void build(int now,int l,int r){//其实build一点用也没有，请大家忽略
    if(l==r){
        mx[now]=0;//-inf;
        mi[now]=0;//inf;
        return ;
    }
    int mid=(l+r)>>1;
    build(now<<1,l,mid);
    build(now<<1|1,mid+1,r);
    up(now);
    return ;
}
inline void down(int now,int ln,int rn){//注意看这个push_down函数
        if(set[now]){//修改标记
            sum[now<<1]=set[now]*ln;
            sum[now<<1|1]=set[now]*rn;
            set[now<<1]=set[now];
            set[now<<1|1]=set[now];
            add[now<<1]=add[now<<1|1]=0;
            mx[now<<1]=mx[now<<1|1]=set[now];
            mi[now<<1]=mi[now<<1|1]=set[now];
            set[now]=0;
        }
        if(add[now]){//加值标记
            sum[now<<1]+=add[now]*ln;
            sum[now<<1|1]+=add[now]*rn;
            add[now<<1]+=add[now];
            add[now<<1|1]+=add[now];
            mx[now<<1]+=add[now];
            mi[now<<1]+=add[now];
            mx[now<<1|1]+=add[now];
            mi[now<<1|1]+=add[now];
            add[now]=0;
        }
        return ;
}
void update_add(int now,int l,int r){
        if(L<=l&&r<=R){
            add[now]+=v;
            sum[now]+=v*(r-l+1);
            mx[now]+=v;
            mi[now]+=v;
            return ;
        }
        int mid=(l+r)>>1;
        down(now,mid-l+1,r-mid);
        if(L<=mid)update_add(now<<1,l,mid);
        if(mid<R)update_add(now<<1|1,mid+1,r);
        up(now);
        return ;
}
void update_set(int now,int l,int r){
        if(L<=l&&r<=R){
            set[now]=v;
            sum[now]=v*(r-l+1);
            add[now]=0;
            mx[now]=v;
            mi[now]=v;
            return ;
        }
        int mid=(l+r)>>1;
        down(now,mid-l+1,r-mid);
        if(L<=mid)update_set(now<<1,l,mid);
        if(mid<R)update_set(now<<1|1,mid+1,r);
        up(now);
        return ;
}
Tmp query(int now,int l,int r){
        if(L<=l&&r<=R){
            return Tmp(sum[now],mx[now],mi[now]);//十分方便
        }
        int mid=(l+r)>>1;
        down(now,mid-l+1,r-mid);
        Tmp tmp;
        int sum=0,mx=-inf,mi=inf; 
        if(L<=mid){
            tmp=query(now<<1,l,mid);
            sum+=tmp.sum;
            mx=max(mx,tmp.mx);
            mi=min(mi,tmp.mi);
        }
        if(mid<R){
            tmp=query(now<<1|1,mid+1,r);
            sum+=tmp.sum;
            mx=max(mx,tmp.mx);
            mi=min(mi,tmp.mi);
        }
      //  up(now);        //然而并不用up()
        tmp.sum=sum,tmp.mi=mi,tmp.mx=mx;
        return tmp;
}
template <class T>inline void read(T &x){
    x=0;int ne=0;char c;
    while(!isdigit(c=getchar()))ne=c=='-';
    x=c-48;
    while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
    x=ne?-x:x;
    return ;
}
int main()
{
    int op,x1,x2,y1,y2;
    read(r),read(c),read(m);
   // build(1,1,r*c);
    while(m--){
        read(op),read(x1),read(y1),read(x2),read(y2);     
        if(op==1){
            read(v);
            for(register int i=x1;i<=x2;i++){ 
			    L=(i-1)*c+y1,R=(i-1)*c+y2;   //注意处理技巧！！！
                update_add(1,1,r*c);  //r*c是所有元素的范围
            }
        }
        else if(op==2){
            read(v);
            for(register int i=x1;i<=x2;i++){
            	L=(i-1)*c+y1,R=(i-1)*c+y2;   //注意处理技巧！！！
                update_set(1,1,r*c);
            }
        }
        else {
            Tmp tmp;
			int sum=0,mx=-inf,mi=inf;
            for(register int i=x1;i<=x2;i++){
            	L=(i-1)*c+y1,R=(i-1)*c+y2;   //注意处理技巧！！！
                tmp=query(1,1,r*c);
                sum+=tmp.sum;
                mx=max(mx,tmp.mx);
                mi=min(mi,tmp.mi);
            }
            printf("%d %d %d\n",sum,mi,mx);
        }
    }
    return 0;
}
```

---

## 作者：Karry5307 (赞：0)

[安利一波我的博客](https://karry5307.github.io/)
### 题意
给定一个$r\times c$矩阵，支持子矩阵加某一个值，子矩阵覆盖为某一个值，查询某个子矩阵的值。
### 题解
一个暴力的想法是由于$r$不超过$20$，所以可以开$20$棵线段树，修改和覆盖就不难啦qwq。

至于查询，可以处理这一行的时候合并这一行的答案和原来的答案就好了qwq。~~所以我查询了$3$次~~

这个时间复杂度是$O(r\log c)$，绝对不会T掉的
### 代码
代码略丑，$233$行……
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=5e4+51;
struct SegmentTree{
    ll l,r,sum,maxn,minn,tag,cover;
}; 
SegmentTree tree[21][MAXN<<2];
ll length,width,qcnt,lx,rx,ly,ry,op,val,sum,maxn,minn;
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void update(ll dim,ll node)
{
    tree[dim][node].sum=tree[dim][node<<1].sum+tree[dim][(node<<1)|1].sum;
    tree[dim][node].maxn=max(tree[dim][node<<1].maxn,tree[dim][(node<<1)|1].maxn);
    tree[dim][node].minn=min(tree[dim][node<<1].minn,tree[dim][(node<<1)|1].minn);
}
inline void create(ll dim,ll l,ll r,ll node)
{
    tree[dim][node].l=l,tree[dim][node].r=r,tree[dim][node].cover=-1;
    if(l==r)
    {
        tree[dim][node].sum=tree[dim][node].maxn=tree[dim][node].minn=0;
        return;
    }
    ll mid=(l+r)>>1;
    create(dim,l,mid,node<<1);
    create(dim,mid+1,r,(node<<1)|1);
    update(dim,node);
}
inline void spread(ll dim,ll node)
{
    ll ls=node<<1,rs=ls|1;
    ll lx=(tree[dim][ls].r-tree[dim][ls].l+1);
    ll rx=(tree[dim][rs].r-tree[dim][rs].l+1);
    if(tree[dim][node].cover!=-1)
    {
        tree[dim][ls].maxn=tree[dim][node].cover;
        tree[dim][rs].maxn=tree[dim][node].cover;
        tree[dim][ls].minn=tree[dim][node].cover;
        tree[dim][rs].minn=tree[dim][node].cover;
        tree[dim][ls].sum=tree[dim][node].cover*lx;
        tree[dim][rs].sum=tree[dim][node].cover*rx;
        tree[dim][ls].cover=tree[dim][rs].cover=tree[dim][node].cover;
        tree[dim][ls].tag=tree[dim][rs].tag=0;
        tree[dim][node].cover=-1;
    }
    if(tree[dim][node].tag)
    {
        tree[dim][ls].maxn+=tree[dim][node].tag;
        tree[dim][rs].maxn+=tree[dim][node].tag;
        tree[dim][ls].minn+=tree[dim][node].tag;
        tree[dim][rs].minn+=tree[dim][node].tag;
        tree[dim][ls].sum+=tree[dim][node].tag*lx;
        tree[dim][rs].sum+=tree[dim][node].tag*rx;
        tree[dim][ls].tag+=tree[dim][node].tag;
        tree[dim][rs].tag+=tree[dim][node].tag;
        tree[dim][node].tag=0;
    } 
}
inline void add(ll dim,ll l,ll r,ll val,ll node)
{
    if(l<=tree[dim][node].l&&r>=tree[dim][node].r)
    {
        tree[dim][node].sum+=(tree[dim][node].r-tree[dim][node].l+1)*val;
        tree[dim][node].maxn+=val,tree[dim][node].minn+=val;
        tree[dim][node].tag+=val;
        return;
    }
    spread(dim,node);
    ll mid=(tree[dim][node].l+tree[dim][node].r)>>1;
    if(l<=mid)
    {
        add(dim,l,r,val,node<<1);
    }
    if(r>mid)
    {
        add(dim,l,r,val,(node<<1)|1);
    }
    update(dim,node);
}
inline void cover(ll dim,ll l,ll r,ll val,ll node)
{
    if(l<=tree[dim][node].l&&r>=tree[dim][node].r)
    {
        tree[dim][node].sum=(tree[dim][node].r-tree[dim][node].l+1)*val;
        tree[dim][node].maxn=tree[dim][node].minn=val;
        tree[dim][node].cover=val;
        tree[dim][node].tag=0;
        return;
    }
    spread(dim,node);
    ll mid=(tree[dim][node].l+tree[dim][node].r)>>1;
    if(l<=mid)
    {
        cover(dim,l,r,val,node<<1);
    }
    if(r>mid)
    {
        cover(dim,l,r,val,(node<<1)|1);
    }
    update(dim,node);
}
inline ll query(ll dim,ll l,ll r,ll node)
{
    if(l<=tree[dim][node].l&&r>=tree[dim][node].r)
    {
        return tree[dim][node].sum;
    }
    ll mid=(tree[dim][node].l+tree[dim][node].r)>>1,res=0;
    spread(dim,node);
    if(l<=mid)
    {
        res+=query(dim,l,r,node<<1);  
    } 
    if(r>mid)
    {
        res+=query(dim,l,r,(node<<1)|1);
    }
    return res;
}
inline ll queryMax(ll dim,ll l,ll r,ll node)
{
    if(l<=tree[dim][node].l&&r>=tree[dim][node].r)
    {
        return tree[dim][node].maxn;
    }
    ll mid=(tree[dim][node].l+tree[dim][node].r)>>1,res=0;
    spread(dim,node);
    if(l<=mid)
    {
        res=max(res,queryMax(dim,l,r,node<<1));  
    }
    if(r>mid)
    {
        res=max(res,queryMax(dim,l,r,(node<<1)|1));
    }
    return res;
}
inline ll queryMin(ll dim,ll l,ll r,ll node)
{
    if(l<=tree[dim][node].l&&r>=tree[dim][node].r)
    {
        return tree[dim][node].minn;
    }
    ll mid=(tree[dim][node].l+tree[dim][node].r)>>1,res=0x7fffffff;
    spread(dim,node);
    if(l<=mid)
    {
        res=min(res,queryMin(dim,l,r,node<<1));  
    }
    if(r>mid)
    {
        res=min(res,queryMin(dim,l,r,(node<<1)|1));
    }
    return res;
}
inline void solve()
{
    width=read(),qcnt=read();
    for(register int i=1;i<=length;i++)
    {
        create(i,1,width,1);
    }
    for(register int i=1;i<=qcnt;i++)
    {
        op=read(),lx=read(),ly=read(),rx=read(),ry=read();
        if(op==1)
        {
            val=read();
            for(register int j=lx;j<=rx;j++)
            {
                add(j,ly,ry,val,1);
            }
        }
        if(op==2)
        {
            val=read(); 
            for(register int j=lx;j<=rx;j++)
            {
                cover(j,ly,ry,val,1);
            }
        } 
        if(op==3)
        {
            sum=maxn=0,minn=0x7fffffff;
            for(register int j=lx;j<=rx;j++)
            {
                sum+=query(j,ly,ry,1);
				maxn=max(maxn,queryMax(j,ly,ry,1));
				minn=min(minn,queryMin(j,ly,ry,1));
            }
            printf("%d %d %d\n",sum,minn,maxn);
        } 
        if(op==4)
		{
			for(register int j=1;j<=length;j++)	
			{
				for(register int k=1;k<=width;k++)
				{
					printf("%d ",query(j,k,k,1));
				}
				puts("");
			}
		} 
    }
}
int main()
{
	while(scanf("%d",&length)!=EOF)
	{
		solve();
		memset(tree,0,sizeof(tree));
	}
}
```

---

