# Meta-universe

## 题目描述

平面上有无限大的网格（可以将其当做一个多重宇宙），其中有一些格子上有行星。

定义**多重宇宙**为一些行星的集合（对应了平面上的一个矩形）。

如果一个**多重宇宙**至少存在一行或一列，使得这一行或一列上没有任何行星，并且行或列两边至少各自有一颗行星（即沿着行/列划分成两个非空的多重宇宙），那么它就可以被分裂开，成为两个更小的**多重宇宙**。

定义**宇宙**为不可继续划分的**多重宇宙**。

现在给你一个**多重宇宙**上所有行星的坐标位置，你需要尽可能地将其划分，并求出最后得到的**宇宙**的数量。

## 说明/提示

$1 \leq N \leq 10^5, -10^9 \leq x_i,y_i \leq 10^9$。

## 样例 #1

### 输入

```
5
0 0
0 2
2 0
2 1
2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8
0 0
1 0
0 2
0 3
3 0
3 1
2 3
3 3
```

### 输出

```
1
```

# 题解

## 作者：ddwqwq (赞：2)

看完universe的定义，我们自然能想到一种朴素的分治做法：暴力找到一条“缝隙”，之后把点集划分成两个部分分别解决。下面的递归式可以描述朴素算法的时间复杂度：$$\text{T}(n)=\text{max}(\text{T}(i)+\text{T}(n-i)+\text{O}(i)),i\in[1,n]$$  
T(n)显然可以退化到O($n^2$)。于是我们想办法优化这个式子。可以发现，如果把上面的式子中$i$的范围控制在$[1,n/2]$中，就可以达到理想的时间复杂度（经过暴力检验，应该是O(nlogn)的）。于是我们想办法实现这个式子。  
其中一种方案是用线段树快速确定某个“缝隙”的位置，接着把“缝隙”一侧（点数较少的一侧）的点从点集中移除并建立一个新的点集，接着递归解决。  
另一种巧妙的方案是，同时从两端开始扫描点集中所有的点，并在第一个发现的“缝隙”处划分点集。如此，找“缝隙”和划分点集的时间复杂度都是O(i),$i\in[1,n/2]$的（忽略点集中的操作的时间复杂度）。  
可以使用优先队列或者平衡树等数据结构维护点集。  
PS：注意常数，我第一次提交用了两个线段树和八个堆，结果......  
代码：
```
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <cstring>
#include <time.h>
#include <complex>
#include <algorithm>
#include <queue>
#include <stack>

#pragma warning(disable:4996)
#define lowbit(a) ((a)&-(a))

template<typename T> T min(T x, T y)
{
    return x < y ? x : y;
}
template<typename T> T max(T x, T y)
{
    return x > y ? x : y;
};

const int MAXN = 300005;
const int INF = 2000000005;

struct pos {
    int x;
    int y;
    pos(int X = 0, int Y = 0)
    {
        x = X;
        y = Y;
    }
};
bool cmp1(pos a, pos b)
{
    if (a.x == b.x)
        return a.y <= b.y;
    return a.x < b.x;
}
bool cmp2(pos a, pos b)
{
    if (a.y == b.y)
        return a.x <= b.x;
    return a.y < b.y;
}

struct tree {
    pos w;
    int size;
    tree *lson;
    tree *rson;
    tree(pos data = pos())
    {
        w = data;
        size = 1;
        lson = rson = NULL;
    }
    void fixup()
    {
        size = (lson ? lson->size : 0) + (rson ? rson->size : 0) + 1;
    }
};
struct pair {
    tree *fir;
    tree *sec;
    pair(tree *F = NULL, tree *S = NULL)
    {
        fir = F;
        sec = S;
    }
};

bool shouldleft(int a, int b)
{
    return (rand() * 10000 + rand()) % (a + b) < a;
}
tree *merge(tree *T1, tree *T2)
{
    if (!T1)
        return T2;
    if (!T2)
        return T1;
    if (shouldleft(T1->size, T2->size))
    {
        T1->rson = merge(T1->rson, T2);
        T1->fixup();
        return T1;
    }
    T2->lson = merge(T1, T2->lson);
    T2->fixup();
    return T2;
}
pair split(tree *T, int k)
{
    if (!T)
        return pair();
    int r = (T->lson ? T->lson->size : 0) + 1;
    if (r <= k)
    {
        pair t = split(T->rson, k - r);
        T->rson = t.fir;
        T->fixup();
        return pair(T, t.sec);
    }
    pair t = split(T->lson, k);
    T->lson = t.sec;
    T->fixup();
    return pair(t.fir, T);
}
int LorE(tree *T, pos p, bool(*cmp)(pos, pos))
{
    if (!T)
        return 0;
    return cmp(T->w, p) ? (T->lson ? T->lson->size : 0) + 1 + LorE(T->rson, p, cmp)
        : LorE(T->lson, p, cmp);
}

tree *insert(tree *T, pos p, bool(*cmp)(pos, pos))
{
    pair t = split(T, LorE(T, p, cmp));
    return merge(t.fir, merge(new tree(p), t.sec));
}
tree *del(tree *T, pos p, bool(*cmp)(pos, pos))
{
    int n = LorE(T, p, cmp);
    pair t = split(T, n);
    pair t2 = split(t.fir, n - 1);
    return merge(t2.fir, t.sec);
}
tree *get(tree *T, int k)
{
    int r = (T->lson ? T->lson->size : 0) + 1;
    if (r == k)
        return T;
    if (k < r)
        return get(T->lson, k);
    return get(T->rson, k - r);
}

int solve(tree *T1, tree *T2)
{
    int n = T1->size;
    for (int i = 1; i <= n - 1; i++)
    {
        if (get(T1, i + 1)->w.x > get(T1, i)->w.x + 1)
        {
            pair t1 = split(T1, i), t2;
            for (int j = 1; j <= i; j++)
            {
                pos p = get(t1.fir, j)->w;
                t2.fir = insert(t2.fir, p, cmp2);
                T2 = del(T2, p, cmp2);
            }
            t2.sec = T2;
            return solve(t1.fir, t2.fir) + solve(t1.sec, t2.sec);
        }
        if (get(T2, i + 1)->w.y > get(T2, i)->w.y + 1)
        {
            pair t1, t2 = split(T2, i);
            for (int j = 1; j <= i; j++)
            {
                pos p = get(t2.fir, j)->w;
                t1.fir = insert(t1.fir, p, cmp1);
                T1 = del(T1, p, cmp1);
            }
            t1.sec = T1;
            return solve(t1.fir, t2.fir) + solve(t1.sec, t2.sec);
        }
        if (get(T1, n - i + 1)->w.x > get(T1, n - i)->w.x + 1)
        {
            pair t1 = split(T1, n - i), t2;
            for (int j = 1; j <= i; j++)
            {
                pos p = get(t1.sec, j)->w;
                t2.sec = insert(t2.sec, p, cmp2);
                T2 = del(T2, p, cmp2);
            }
            t2.fir = T2;
            return solve(t1.fir, t2.fir) + solve(t1.sec, t2.sec);
        }
        if (get(T2, n - i + 1)->w.y > get(T2, n - i)->w.y + 1)
        {
            pair t1, t2 = split(T2, n - i);
            for (int j = 1; j <= i; j++)
            {
                pos p = get(t2.sec, j)->w;
                t1.sec = insert(t1.sec, p, cmp1);
                T1 = del(T1, p, cmp1);
            }
            t1.fir = T1;
            return solve(t1.fir, t2.fir) + solve(t1.sec, t2.sec);
        }
    }
    return 1;
}

int N;
tree *T1, *T2;

int main()
{
    pos p;

    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d %d", &p.x, &p.y);
        T1 = insert(T1, p, cmp1);
        T2 = insert(T2, p, cmp2);
    }

    int ans = solve(T1, T2);
    printf("%d", ans);

    //system("pause");
    return 0;
}
```

---

## 作者：zesqwq (赞：1)

暴力就是直接模拟分裂过程，发现找全 $0$ 的行，列可以用线段树代替，但这样时间复杂度仍然炸。

每次既然是把多重宇宙分裂成两个小的，那么就可以启发式分裂，把较小的从原集合中（线段树）删除出去，加入新的集合（线段树），时间复杂度 $O(n \log ^2 n)$，可以通过。

注意实现，不能扫描当前的多重宇宙，否则复杂度会退化。

---

## 作者：NATO (赞：0)

duel 的时候遇到的 trash，狠狠地 downvote 了。

~~没有思路浅析了，做法过于明显。~~

考虑答案上界就是 $n$，而你只要找到任意一行或一列上没有任何行星且两侧有行星的行或列即可使答案 $+1$，然后就能分为两部分进入子问题，线段树暴力维护每一行和列有多少个在当前处理区间中的点，找最前面前面有点的空位置即可，分裂考虑启发式分裂删点即可。

线段树叶节点用 `set` 维护有哪些点方便删除。

维护注意写好空间回收来保证空间是 $O(n\log n)$ 的，注意 `set` 也是要回收的。

时间复杂度 $O(n\log^2n)$，写起来就是一坨。

#### 参考代码：


```cpp
#include<bits/stdc++.h>
#define ll int
#define INF 1000000
using namespace std;
ll n;
struct px
{
	ll x,y;
}s[100005];
ll sx[300005],sy[300005];
ll cotx,coty;
struct SGT
{
	set<ll>s[100005];
	struct tree
	{
		ll sz,son[2],hv;
		ll uid;	
	}tr[3000005];
	#define ls(id) tr[id].son[0]
	#define rs(id) tr[id].son[1]
	queue<ll>use,su;
	ll cot,cs;
	void clear(ll id)
	{
		if(tr[id].uid)
		{
			set<ll>c;
			s[tr[id].uid].swap(c);
			su.emplace(tr[id].uid);
			tr[id].uid=0;
		}
		tr[id].sz=0;
		ls(id)=rs(id)=0;
		tr[id].hv=0;
		use.emplace(id);
	}
	ll new_node()
	{
		ll id;
		if(!use.empty())
		{
			id=use.front();use.pop();
		}
		else id=++cot;
		return id;
	}
	ll new_set()
	{
		ll id;
		if(!su.empty())
		{
			id=su.front();su.pop();
		}
		else id=++cs;
		return id;
	}
	void pushup(ll id)
	{
		tr[id].hv=tr[ls(id)].hv+tr[rs(id)].hv;
		tr[id].sz=tr[ls(id)].sz+tr[rs(id)].sz;
	}
	void insert(ll &id,ll l,ll r,ll ml,ll uid)
	{
		if(!id)id=new_node();
		if(l==r)
		{
			++tr[id].sz;
			if(!tr[id].uid)tr[id].uid=new_set();
			s[tr[id].uid].insert(uid);
			tr[id].hv=(s[tr[id].uid].size()!=0);
			return;
		}
		ll mid=l+r>>1;
		if(ml<=mid)insert(ls(id),l,mid,ml,uid);
		else insert(rs(id),mid+1,r,ml,uid);
		pushup(id);
	}
	void del(ll &id,ll l,ll r,ll ml,ll uid)
	{
		if(!id)return;
		if(l==r)
		{
			--tr[id].sz;
			s[tr[id].uid].erase(uid);
			tr[id].hv=(s[tr[id].uid].size()!=0);
			if(!tr[id].hv)clear(id);
			return;
		}
		ll mid=l+r>>1;
		if(ml<=mid)del(ls(id),l,mid,ml,uid);
		else del(rs(id),mid+1,r,ml,uid);
		if(!tr[ls(id)].hv)ls(id)=0;
		if(!tr[rs(id)].hv)rs(id)=0;
		pushup(id);
		if(!tr[id].hv)clear(id);
	}
	ll find_l(ll id,ll l,ll r,ll ml,ll mr)
	{
		ll mid=l+r>>1;
		if(!tr[id].hv)return INF;
		if(ml<=l&&r<=mr)
		{
			if(l==r)return l;
			if(!tr[ls(id)].hv)return find_l(rs(id),mid+1,r,ml,mr);
			return find_l(ls(id),l,mid,ml,mr);
		}
		if(ml<=mid)
		{
			ll res=find_l(ls(id),l,mid,ml,mr);
			if(res!=INF)return res;
			if(mr>mid)
			return find_l(rs(id),mid+1,r,ml,mr);
			return INF;
		}
		if(mr>mid)return find_l(rs(id),mid+1,r,ml,mr);
	}
	ll find_r(ll id,ll l,ll r,ll ml,ll mr)
	{
		ll mid=l+r>>1;
		if(!tr[id].hv)return 0;
		if(ml<=l&&r<=mr)
		{
			if(l==r)return l;
			if(!tr[rs(id)].hv)return find_r(ls(id),l,mid,ml,mr);
			return find_r(rs(id),mid+1,r,ml,mr);
		}
		if(mr>mid)
		{
			ll res=find_r(rs(id),mid+1,r,ml,mr);
			if(res!=0)return res;
			if(ml<=mid)
			return find_r(ls(id),l,mid,ml,mr);
			return 0;
		}
		if(ml<=mid)return find_r(ls(id),l,mid,ml,mr);
	}
	ll find_lk(ll id,ll l,ll r,ll ml,ll mr)
	{
		ll mid=l+r>>1;
		if(tr[id].hv==r-l+1)return INF;
		if(ml<=l&&r<=mr)
		{
			if(l==r)return l;
			if(tr[ls(id)].hv==mid-l+1)return find_lk(rs(id),mid+1,r,ml,mr);
			return find_lk(ls(id),l,mid,ml,mr);
		}
		if(ml<=mid)
		{
			ll res=find_lk(ls(id),l,mid,ml,mr);
			if(res!=INF)return res;
			if(mr>mid)
			return find_lk(rs(id),mid+1,r,ml,mr);
			return INF;
		}
		if(mr>mid)return find_lk(rs(id),mid+1,r,ml,mr);
	}
	ll query(ll id,ll l,ll r,ll ml,ll mr)
	{
		if(!id)return 0;
		if(ml<=l&&r<=mr)return tr[id].sz;
		ll mid=l+r>>1,res=0;
		if(ml<=mid)res+=query(ls(id),l,mid,ml,mr);
		if(mr>mid)res+=query(rs(id),1+mid,r,ml,mr);
		return res;
	}
}tx,ty;
ll ans=1;
void dx(ll &rt,ll &l,ll &r)
{
	ll nl=tx.find_l(rt,1,cotx,l,r);
	l=nl;
	ll nr=tx.find_r(rt,1,cotx,l,r);
	r=nr;
}
void dy(ll &rt,ll &l,ll &r)
{
	ll nl=ty.find_l(rt,1,coty,l,r);
	l=nl;
	ll nr=ty.find_r(rt,1,coty,l,r);
	r=nr;
}
vector<ll>uid;
void delx(ll id,ll l,ll r,ll ml,ll mr)
{
	if(!id)return;
	if(!tx.tr[id].hv)return;
	if(l==r)
	{
		for(auto it:tx.s[tx.tr[id].uid])uid.emplace_back(it);
		tx.clear(id);
		return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)
	delx(tx.ls(id),l,mid,ml,mr);
	if(mr>mid)
	delx(tx.rs(id),1+mid,r,ml,mr);
	if(!tx.tr[tx.ls(id)].hv)tx.ls(id)=0;
	if(!tx.tr[tx.rs(id)].hv)tx.rs(id)=0;
	tx.pushup(id);
	if(!tx.tr[id].hv)
	tx.clear(id);
}
void dely(ll id,ll l,ll r,ll ml,ll mr)
{
	if(!id)return;
	if(!ty.tr[id].hv)return;
	if(l==r)
	{
		for(auto it:ty.s[ty.tr[id].uid])uid.emplace_back(it);
		ty.clear(id);
		return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)
	dely(ty.ls(id),l,mid,ml,mr);
	if(mr>mid)
	dely(ty.rs(id),1+mid,r,ml,mr);
	if(!ty.tr[ty.ls(id)].hv)ty.ls(id)=0;
	if(!ty.tr[ty.rs(id)].hv)ty.rs(id)=0;
	ty.pushup(id);
	if(!ty.tr[id].hv)
	ty.clear(id);
}
ll cpt[100005];
void solve(ll rtx,ll rty,ll lx,ll rx,ll ly,ll ry)
{	
	dx(rtx,lx,rx);
	dy(rty,ly,ry);
	ll xl=tx.find_lk(rtx,1,cotx,lx,rx);
	if(xl!=INF)
	{
		++ans;
		uid.clear();
		ll szl=tx.query(rtx,1,cotx,lx,xl);
		ll szr=tx.tr[rtx].sz-szl;
		if(szl<szr)
		delx(rtx,1,cotx,lx,xl);
		else 
		delx(rtx,1,cotx,xl+1,rx);
		ll ntx=0,nty=0;
		for(auto it:uid)ty.del(rty,1,coty,s[it].y,it);
		for(auto it:uid)
		{
			tx.insert(ntx,1,cotx,s[it].x,it);
			ty.insert(nty,1,coty,s[it].y,it);
		}
		solve(rtx,rty,lx,rx,ly,ry);
		solve(ntx,nty,lx,rx,ly,ry);
		return;
	}
	ll yl=ty.find_lk(rty,1,coty,ly,ry);
	if(yl!=INF)
	{
		++ans;
		uid.clear();
		ll szl=ty.query(rty,1,coty,ly,yl);
		ll szr=ty.tr[rty].sz-szl;
		if(szl<szr)dely(rty,1,coty,ly,yl);
		else dely(rty,1,coty,yl+1,ry);
		ll ntx=0,nty=0;
		for(auto it:uid)tx.del(rtx,1,cotx,s[it].x,it);
		for(auto it:uid)
		{
			tx.insert(ntx,1,cotx,s[it].x,it);
			ty.insert(nty,1,coty,s[it].y,it);
		}
		solve(rtx,rty,lx,rx,ly,ry);
		solve(ntx,nty,lx,rx,ly,ry);
		return;
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;++i)
	{
		cin>>s[i].x>>s[i].y;
		sx[++cotx]=s[i].x,sy[++coty]=s[i].y;
		sx[++cotx]=s[i].x-1,sy[++coty]=s[i].y-1;
		sx[++cotx]=s[i].x+1,sy[++coty]=s[i].y+1;
	}
	sort(sx+1,sx+1+cotx);
	sort(sy+1,sy+1+coty);
	cotx=unique(sx+1,sx+1+cotx)-sx-1;
	coty=unique(sy+1,sy+1+coty)-sy-1;
	ll rtx=0,rty=0;
	for(ll i=1;i<=n;++i)
	{
		s[i].x=lower_bound(sx+1,sx+1+cotx,s[i].x)-sx;
		s[i].y=lower_bound(sy+1,sy+1+coty,s[i].y)-sy;
		tx.insert(rtx,1,cotx,s[i].x,i);
		ty.insert(rty,1,coty,s[i].y,i);
	}
	solve(rtx,rty,1,cotx,1,coty);
	cout<<ans;
}//顷刻间意志燃起熊熊烈火，看它燎原，恣意盘旋
```

---

