# Impressive Harvesting of The Orchard

## 题目描述

Mr. Chanek has an orchard structured as a rooted ternary tree with $ N $ vertices numbered from $ 1 $ to $ N $ . The root of the tree is vertex $ 1 $ . $ P_i $ denotes the parent of vertex $ i $ , for $ (2 \le i \le N) $ . Interestingly, the height of the tree is not greater than $ 10 $ . Height of a tree is defined to be the largest distance from the root to a vertex in the tree.

There exist a bush on each vertex of the tree. Initially, all bushes have fruits. Fruits will not grow on bushes that currently already have fruits. The bush at vertex $ i $ will grow fruits after $ A_i $ days since its last harvest.

Mr. Chanek will visit his orchard for $ Q $ days. In day $ i $ , he will harvest all bushes that have fruits on the subtree of vertex $ X_i $ . For each day, determine the sum of distances from every harvested bush to $ X_i $ , and the number of harvested bush that day. Harvesting a bush means collecting all fruits on the bush.

For example, if Mr. Chanek harvests all fruits on subtree of vertex $ X $ , and harvested bushes $ [Y_1, Y_2, \dots, Y_M] $ , the sum of distances is $ \sum_{i = 1}^M \text{distance}(X, Y_i) $

 $ \text{distance}(U, V) $ in a tree is defined to be the number of edges on the simple path from $ U $ to $ V $ .

## 说明/提示

For the first example:

- On day 1, Mr. Chanek starts at vertex $ 2 $ and can harvest the bush at vertex 2.
- On day 2, Mr. Chanek starts at vertex $ 1 $ and only harvest from bush $ 1 $ (bush 2's fruit still has not grown yet).
- On day 3, Mr. Chanek starts at vertex $ 1 $ and harvests the fruits on bush $ 1 $ and $ 2 $ . The sum of distances from every harvested bush to $ 1 $ is $ 1 $ .

For the second example, Mr. Chanek always starts at vertex $ 1 $ . The bushes which Mr. Chanek harvests on day one, two, and three are $ [1, 2, 3, 4, 5], [2, 3], [1, 2, 3, 5] $ , respectively.

## 样例 #1

### 输入

```
2 3
1 2
1
2
1
1```

### 输出

```
0 1
0 1
1 2```

## 样例 #2

### 输入

```
5 3
2 1 1 3 2
1 2 2 1
1
1
1```

### 输出

```
6 5
3 2
4 4```

# 题解

## 作者：QwQcOrZ (赞：6)

对于 $a_i$ 根号分治。

对于 $a_i>B$：把树拍平然后抠出每个 $a_i>B$ 的节点，塞进一个分块里，每次暴力取出所有需要采摘的节点。复杂度 $\mathcal O(\frac{Q}{B}+\sqrt Q)$。

对于 $a_i\leq B$：对每个 $a_i$ 开个 Beats 存储其下次出现果实的时间 $t_i$，每次操作相当于把所有 $t_i\leq now$ 的 $t_i$ 变成 $now+a_i$，然后统计相关信息。复杂度 $\mathcal O(B\log n)$。

平衡一下，复杂度 $\mathcal O(Q\sqrt{Q\log n})$。

实际上，由于树本身是一个类似线段树的结构，可以直接把原树当成一个 Beats 来做。

------------

但是 $n,Q$ 都只有 $5\times 10^4$，时限有 $7s$。

而且暴力做法的常数很小。

于是尝试写了一发 $\mathcal O(nQ)$ 的代码，发现它过了。。。

拉火车头的一部分代码之后极限数据只需要 $1.2s$。

```cpp
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native") 
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e4+5;

ll read(){static ll x;scanf("%lld",&x);return x;}
void write(ll x){printf("%lld",x);}
void print(ll x,char c='\n'){write(x),putchar(c);}

vector<int>e[N];
int a[N],t[N],st[N],ed[N],cntdfn=0,deep[N];
void dfs(int now)
{
	st[now]=++cntdfn;
	for (int to:e[now]) deep[to]=deep[now]+1,dfs(to);
	ed[now]=cntdfn;
}
void shuffle_p(int *a,int *p,int n)
{
	static int b[N];
	memcpy(b,a,sizeof(int)*(n+1));
	for (int i=1;i<=n;i++) a[p[i]]=b[i];
}

signed main()
{
	int n=read(),Q=read();
	for (int i=1;i<=n;i++) a[i]=read(),t[i]=0;
	for (int i=2;i<=n;i++) e[read()].push_back(i);
	dfs(1);
	shuffle_p(a,st,n);
	shuffle_p(deep,st,n);
	for (int T=1;T<=Q;T++)
	{
		int x=read(),ans1=0,ans2=0;
		for (register int L=st[x],R=ed[x],i=L;i<=R;i++)
		if (t[i]<=T)
		{
			ans1++,ans2+=deep[i];
			t[i]=T+a[i];
		}
		ans2-=ans1*deep[st[x]];
		print(ans2,' '),print(ans1);
	}
	
	return 0;
}
```

---

## 作者：Ynoi (赞：2)

树剖姐姐学完文化课发现她的 DS 水平不行了，于是她就写了个暴力过了这个题，并发篇题解祭之。

然而传统的暴力（直接枚举子节点）并不能通过，因此暴力需要换个姿势。

我们将询问离线下来，计算每个节点的贡献。然后我们直接枚举节点。因为树高只有 $10$，所以我们直接标记该节点的祖先，这样对于每个节点在枚举询问的时候就可以直接判断在不在 $x_i$ 的子树里。然后我们每次枚举完就跳过 $a_i$ 个询问（因为这时候果子还没有长出来），这样可以极大减少枚举数量。

```
#include<bits/stdc++.h>
using namespace std;


#define pb push_back
#define MAXN 100005

int n,m;
int fa[MAXN],a[MAXN],s[MAXN],h[MAXN];
vector<int>v[MAXN],w[MAXN];
int cnt = 0;
int b[MAXN];
int d[MAXN],df[MAXN];
int ne[MAXN],t[MAXN],fr[MAXN];
int an1[MAXN],an2[MAXN],c[MAXN];

int read() {
	int x = 0;
	char ch = ' ';
	while(ch < '0' || ch > '9') ch = getchar();
	while('0' <= ch  && ch <= '9') {
		x = x*10 + ch - '0';
		ch = getchar();
	}
	return x;
}

void put(int x) {
	if(x >= 10) put(x/10);
	putchar(x%10+'0');
}

void dfs(int x) {
	for(int i = 0; i < w[x].size(); i ++) {
		int y = w[x][i]; 
		h[y] = h[x]+1;
		dfs(y);
	} 
}

signed main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) {
		a[i] = read();
		a[i] --;
	}
	
		
	for(int i = 2; i <= n; i ++) {
		fa[i] = read();
		w[fa[i]].pb(i);
	}
	dfs(1);
	for(int i = 1; i <= m; i ++) c[i] = read();
	
	for(int i = 1; i <= n; i ++) {
		for(int j = i; j ; j = fa[j])
			fr[j] = i;
		
		for(int j = 1; j <= m; j ++) 
		if(fr[c[j]] == i){
			an1[j] ++;
			an2[j] += h[i];
			j += a[i];
		}
	}
	for(int i = 1; i <= m; i ++)
		an2[i] -= an1[i]*h[c[i]];
	for(int i = 1; i <= m; i ++) {
		put(an2[i]);putchar(' ');
		put(an1[i]);putchar('\n');
		
	}
	return 0;
}

```

---

## 作者：ywy_c_asm (赞：2)

题意：$n$个点的有根树，每个点初始有个果子，第$i$点的果子被摘了后会在$a_i$天后重新长出来，一共有$q$天，每天摘掉$x_i$子树内的所有果子，求每天摘了多少果子以及摘的果子到$x_i$的距离之和。

Solution：

显然我们需要统计子树内果子的个数以及深度之和即可计算答案。但是我们不可能把所有的果子都枚举一遍，因为**有的**点的$a_i$比较小，枚举会炸掉。这样的话我们可以想到对$a_i$按照根号分类讨论：

①对于$a_i>\sqrt q$的点，我们可以$O(\sqrt q)$枚举它长出的所有果子，就是找长出果子后在最早的哪天被摘掉。这个可以离线dfs，维护每个点到祖先的一条链上的所有询问，对于每个果子，在存着祖先询问的线段树或set上二分摘掉日期即可。这是$O(n\sqrt q \log n)$的。

②对于$a_i<=\sqrt q$的点，这大概就需要在每一天$t$，$O(\sqrt q)$枚举$a_i$，然后把这果子“扔到”$t+a_i$之后。我们对每个点维护下一个果子长出的时间$T_i$，那么就是，把所有子树内值为$a_i$且$T_i<=t$的点都加上$a_i$，然后统计它们的信息和。这是啥？这是吉老师线段树能$O(\log n)$干的。大概就是，维护区间内最小值，次小值，最大值，关于整体的信息以及仅关于最小值的信息，每次能直接操作的区间要么是整体全部修改，要么仅修改最小值，讨论一下即可。

官方题解的做法竟然是直接把整棵树当一个“线段树”然后这样做，因为树高很低，点的儿子很少。我的做法是直接用dfs序区间去在$\sqrt q$棵线段树上做，感觉要比前面那个好一点。

上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define blo 200
#define N 50010
#define inf 0x7fffffff
#define upmin(_o, _a) _o = min(_o, _a)
#define ls(_o) (_o << 1)
#define rs(_o) ((_o << 1) | 1)
#define did(_o, _x) \
    minn[_o] += _x; \
    adds[_o] += _x
using namespace std;
namespace ywy {
inline int get() {
    int n = 0;
    char c;
    while ((c = getchar()) || 23333)
        if (c >= '0' && c <= '9')
            break;
    n = c - '0';
    while ((c = getchar()) || 23333) {
        if (c >= '0' && c <= '9')
            n = n * 10 + c - '0';
        else
            return (n);
    }
}
int lef[N * 2], rgh[N * 2], minn[N * 2], sec[N * 2], cmin[N * 2], sig[N * 2], cnt[N * 2], gn = 1, fan[N],
                                                                                          a[N];
vector<int> chs[N];
vector<int> qry[N];
int anscnt[N], anssig[N], deep[N], gdfn = 1;
int pid, now, dx, maxn[N * 2], sigall[N * 2], call[N * 2];
typedef struct _seg {
    int rt;
    vector<int> vec;
    inline void up(int tree) {
        minn[tree] = min(minn[lef[tree]], minn[rgh[tree]]);
        sec[tree] = inf;
        cnt[tree] = sig[tree] = 0;
        if (minn[lef[tree]] != minn[tree])
            upmin(sec[tree], minn[lef[tree]]);
        else
            cnt[tree] += cnt[lef[tree]], sig[tree] += sig[lef[tree]];
        if (minn[rgh[tree]] != minn[tree])
            upmin(sec[tree], minn[rgh[tree]]);
        else
            cnt[tree] += cnt[rgh[tree]], sig[tree] += sig[rgh[tree]];
        upmin(sec[tree], sec[lef[tree]]);
        upmin(sec[tree], sec[rgh[tree]]);
        maxn[tree] = max(maxn[lef[tree]], maxn[rgh[tree]]);
        sigall[tree] = sigall[lef[tree]] + sigall[rgh[tree]];
    }
    int build(int l, int r) {
        int me = gn;
        gn++;
        if (l == r) {
            int pt = fan[vec[l - 1]];
            minn[me] = maxn[me] = 1;
            sec[me] = inf;
            sig[me] = sigall[me] = deep[pt];
            cnt[me] = 1;
            return (me);
        }
        int mid = (l + r) >> 1;
        lef[me] = build(l, mid);
        rgh[me] = build(mid + 1, r);
        up(me);
        return (me);
    }
    inline void down(int tree, int l, int r) {
        if (call[tree]) {
            int mid = (l + r) >> 1;
            cnt[lef[tree]] = mid - l + 1;
            cnt[rgh[tree]] = r - mid;
            sig[lef[tree]] = sigall[lef[tree]];
            sig[rgh[tree]] = sigall[rgh[tree]];
            int x = call[tree];
            call[tree] = 0;
            sec[lef[tree]] = sec[rgh[tree]] = inf;
            maxn[lef[tree]] = maxn[rgh[tree]] = minn[lef[tree]] = minn[rgh[tree]] = x;
            call[lef[tree]] = call[rgh[tree]] = x;
            cmin[lef[tree]] = cmin[rgh[tree]] = 0;
        }
        if (cmin[tree]) {
            int x = cmin[tree];
            cmin[tree] = 0;
            int g = min(minn[lef[tree]], minn[rgh[tree]]);
            if (minn[lef[tree]] == g) {
                minn[lef[tree]] = x;
                if (sec[lef[tree]] == inf)
                    maxn[lef[tree]] = x;
                cmin[lef[tree]] = x;
                call[lef[tree]] = 0;
            }
            if (minn[rgh[tree]] == g) {
                minn[rgh[tree]] = x;
                if (sec[rgh[tree]] == inf)
                    maxn[rgh[tree]] = x;
                cmin[rgh[tree]] = x;
                call[rgh[tree]] = 0;
            }
        }
    }
    void stb(int rl, int rr, int l, int r, int tree) {
        if (minn[tree] > now)
            return;
        int mid = (l + r) >> 1;
        if (l != r)
            down(tree, l, r);
        if (rl == l && rr == r) {
            if (maxn[tree] <= now) {
                cmin[tree] = 0;
                call[tree] = maxn[tree] = minn[tree] = now + dx;
                sec[tree] = inf;
                cnt[tree] = r - l + 1;
                sig[tree] = sigall[tree];
                anscnt[pid] += (r - l + 1);
                anssig[pid] += sigall[tree];
                return;
            }
            if (minn[tree] <= now && sec[tree] > now + dx) {
                cmin[tree] = minn[tree] = now + dx;
                anscnt[pid] += cnt[tree];
                anssig[pid] += sig[tree];
                return;
            }
            stb(l, mid, l, mid, lef[tree]);
            stb(mid + 1, r, mid + 1, r, rgh[tree]);
            up(tree);
            return;
        }
        if (rl > mid)
            stb(rl, rr, mid + 1, r, rgh[tree]);
        else {
            if (rr <= mid)
                stb(rl, rr, l, mid, lef[tree]);
            else {
                stb(rl, mid, l, mid, lef[tree]);
                stb(mid + 1, rr, mid + 1, r, rgh[tree]);
            }
        }
        up(tree);
    }
} Segtree;
int sz[N][blo + 2];
Segtree ts[blo + 2];
int size[N], dfn[N];
void dfs(int pt) {
    dfn[pt] = gdfn;
    fan[gdfn] = pt;
    gdfn++;
    size[pt] = 1;
    if (a[pt] <= blo)
        sz[pt][a[pt]]++;
    for (register int i = 0; i < chs[pt].size(); i++) {
        deep[chs[pt][i]] = deep[pt] + 1;
        dfs(chs[pt][i]);
        size[pt] += size[chs[pt][i]];
        for (register int j = 1; j <= blo; j++) sz[pt][j] += sz[chs[pt][i]][j];
    }
}
namespace sgt {
int data[N * 4];
void addpt(int l, int r, int tree, int pt, int x) {
    data[tree] += x;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pt <= mid)
        addpt(l, mid, ls(tree), pt, x);
    else
        addpt(mid + 1, r, rs(tree), pt, x);
}
int query(int rl, int rr, int l, int r, int tree) {
    if (!data[tree] || rl > rr)
        return (0);
    if (l == r)
        return (l);
    int mid = (l + r) >> 1;
    if (rl == l && rr == r) {
        if (data[ls(tree)])
            return (query(l, mid, l, mid, ls(tree)));
        return (query(mid + 1, r, mid + 1, r, rs(tree)));
    }
    if (rl > mid)
        return (query(rl, rr, mid + 1, r, rs(tree)));
    if (rr <= mid)
        return (query(rl, rr, l, mid, ls(tree)));
    int t = query(rl, mid, l, mid, ls(tree));
    if (t)
        return (t);
    return (query(mid + 1, rr, mid + 1, r, rs(tree)));
}
}  // namespace sgt
int n, q;
void solve(int pt) {
    for (register int i = 0; i < qry[pt].size(); i++) sgt::addpt(1, q, 1, qry[pt][i], 1);
    if (a[pt] > blo) {
        int lst = 1;
        while (1) {
            int dst = sgt::query(lst, q, 1, q, 1);
            if (!dst)
                break;
            lst = dst + a[pt];
            anscnt[dst]++;
            anssig[dst] += deep[pt];
        }
    }
    for (register int i = 0; i < chs[pt].size(); i++) solve(chs[pt][i]);
    for (register int i = 0; i < qry[pt].size(); i++) sgt::addpt(1, q, 1, qry[pt][i], -1);
}
int pts[N];
void ywymain() {
    n = get(), q = get();
    for (register int i = 1; i <= n; i++) a[i] = get();
    for (register int i = 2; i <= n; i++) chs[get()].push_back(i);
    dfs(1);
    for (register int i = 1; i <= n; i++) {
        if (a[i] <= blo)
            ts[a[i]].vec.push_back(dfn[i]);
    }
    for (register int i = 1; i <= blo; i++) {
        if (!sz[1][i])
            continue;
        sort(ts[i].vec.begin(), ts[i].vec.end());
        ts[i].rt = ts[i].build(1, ts[i].vec.size());
    }
    for (register int i = 1; i <= q; i++) {
        int me = get();
        pts[i] = me;
        pid = i;
        now = i;
        int dl = dfn[me], dr = dfn[me] + size[me] - 1;
        for (register int j = 1; j <= blo; j++) {
            if (!sz[me][j])
                continue;
            int ans = -1, l = 0, r = ts[j].vec.size() - 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (ts[j].vec[mid] >= dl)
                    ans = mid, r = mid - 1;
                else
                    l = mid + 1;
            }
            int rl = ans;
            ans = -1;
            l = 0, r = ts[j].vec.size() - 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (ts[j].vec[mid] <= dr)
                    ans = mid, l = mid + 1;
                else
                    r = mid - 1;
            }
            int rr = ans;
            dx = j;
            ts[j].stb(rl + 1, rr + 1, 1, ts[j].vec.size(), ts[j].rt);
        }
        qry[me].push_back(i);
    }
    solve(1);
    for (register int i = 1; i <= q; i++) {
        printf("%d %d\n", anssig[i] - deep[pts[i]] * anscnt[i], anscnt[i]);
    }
}
}  // namespace ywy
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：_edge_ (赞：0)

考虑对 $a_i$ 进行根号分治，对于大的部分可以直接在树上 dfs，将查询插入到分块内，然后暴力跳，这部分复杂度 $O(q
B+\dfrac{nq} B)$。

对于小的部分由于其 $a_i$ 种类非常小，考虑对每种都进行统计。

我们考虑维护每个时刻有多少个点。

容易发现操作的一定是一段区间，并且一定是将这段区间往后挪动以及将整颗线段树往后挪，形式和线段树分裂模板一样，所以直接上板子就可以了，这部分复杂度 $O(qB \log n)$，平衡复杂度得到 $O(q \sqrt {n \log n})$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back 
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int INF=5e4+5;
const int INFN=2e6+5;
int n,q,a[INF],b[INF],pos[INF],dep[INF],res2[INF],dfn[INF],pre[INF],sz[INF];
int posl[INF],posr[INF],B,R[INF],vis[INF],res[INF];
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int tot,head[INF];
vector <int> id[INF],v3[INF];
void add_edge(int x,int y) {
	edge[++tot]={y,head[x]};
	head[x]=tot;
}
void add(int x,int y,int z) {
	if (z==1) {
		int id=pos[x];
		vis[x]=1;R[x]=x;
		// cerr<<x<<" "<<posl[id]<<" "<<vis[4]<<" "<<" just ?\n";
		for (int i=x-1;i>=posl[id];i--)
			if (vis[i]) break;
			else R[i]=x;
	}
	else {
		int id=pos[x];
		vis[x]=0;int la=0;
		for (int j=posr[id];j>=posl[id];j--) {
			if (vis[j]) la=j;
			R[j]=la;
		}
	}
}
void DFS(int x,int fa) {
	dfn[++dfn[0]]=x;pre[x]=dfn[0];
	dep[x]=dep[fa]+1;sz[x]=1;
	for (int a:id[x]) add(a,x,1);
	if (a[x]>B) {
		int xx=1;
		while (xx<=q) {
			// cerr<<xx<<" "<<x<<" "<<posr[pos[xx]]<<" "<<R[3]<<" aewjroiawjro\n";
			while (xx<=q && !R[xx]) 
				xx=posr[pos[xx]]+1;
			if (xx>q) break;
			xx=R[xx];
			res[xx]++;
			res2[xx]+=dep[x];
			xx+=a[x];
		}
	}
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS(v,x);
		sz[x]+=sz[v];
	}
	for (int a:id[x]) add(a,x,-1);
}
int K;
pii it;
pii mer2(pii a,pii b) {return {a.fi+b.fi,a.se+b.se};}
struct Segment{
	#define ls(x) lson[x]
	#define rs(x) rson[x]
	int lson[INFN],rson[INFN],sum[INFN],sum2[INFN],rt[INF],tot;
	void push_up(int id) {
		sum[id]=sum[ls(id)]+sum[rs(id)];
        sum2[id]=sum2[ls(id)]+sum2[rs(id)];
	}
    void add(int l,int ll,int rr,int x,int y,int &id) {
        if (!id) id=++tot;
        if (ll==rr) {
            sum[id]=x;
            sum2[id]=y;
            return ;
        }
        int Mid=(ll+rr)>>1;
        if (l<=Mid) add(l,ll,Mid,x,y,ls(id));
        else add(l,Mid+1,rr,x,y,rs(id));
        push_up(id);
		// cerr<<ll<<" "<<rr<<" "<<sum[id]<<" ajwoieawirojawoier\n";
    }
    void split(int &x,int &y,int l,int r,int z) {
        if (r<=z) {y=x;x=0;return ;}
        if (!x || z<l) {y=0;return ;}
        int Mid=(l+r)>>1;
        if (Mid<=z) {
            ls(y)=ls(x);ls(x)=0;
			rs(y)=++tot;
            split(rs(x),rs(y),Mid+1,r,z);
        }
        else {
            ls(y)=++tot;
            split(ls(x),ls(y),l,Mid,z);
        }
		if (l!=r) {push_up(x);push_up(y);}
	} 
    void mer(int &x,int y,int l,int r) {
        if (!x || !y) {x=x+y;return ;}
        sum[x]+=sum[y];sum2[x]+=sum2[y];
		int Mid=(l+r)>>1;
        mer(ls(x),ls(y),l,Mid);mer(rs(x),rs(y),Mid+1,r);
        if (l!=r) push_up(x);
    }
    pii query(int l,int r,int ll,int rr,int id) {
        if (!id) return {0,0};
        if (l<=ll && rr<=r) return {sum[id],sum2[id]};
        int Mid=(ll+rr)>>1;
        if (l>Mid) return query(l,r,Mid+1,rr,rs(id));
        else if (r<=Mid) return query(l,r,ll,Mid,ls(id));
        else return mer2(query(l,r,ll,Mid,ls(id)),query(l,r,Mid+1,rr,rs(id)));
    }
}T1;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>q;B=25; memset(posl,63,sizeof posl);
	for (int i=1;i<=q;i++) pos[i]=i/B;
	for (int i=1;i<=q;i++) posl[pos[i]]=min(posl[pos[i]],i);
	for (int i=1;i<=q;i++) posr[pos[i]]=max(posr[pos[i]],i);
	
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=2;i<=n;i++) {
		int x=0;cin>>x;
		add_edge(x,i);
	}
	for (int i=1;i<=q;i++) cin>>b[i],id[b[i]].pb(i);
	DFS(1,0);
    for (int i=1;i<=n;i++) v3[a[i]].pb(i);
	// cerr<<a[3]<<" awjeroawijok\n";
    for (int p=1;p<=B;p++) {
        for (int i=0;i<=T1.tot;i++) T1.sum[i]=T1.sum2[i]=T1.ls(i)=T1.rs(i)=0;
        T1.tot=0;
        for (int i=1;i<=q+1;i++) T1.rt[i]=++T1.tot;
        for (int i:v3[p]) T1.add(pre[i],1,n,1,dep[i],T1.rt[1]);
        for (int i=1;i<=q;i++) {
            // pre[b[i]],pre[b[i]]+sz[b[i]]-1
            pii it=T1.query(pre[b[i]],pre[b[i]]+sz[b[i]]-1,1,n,T1.rt[i]);
            res[i]+=it.fi;res2[i]+=it.se;
            int x=++T1.tot,y=++T1.tot;
            T1.split(T1.rt[i],x,1,n,pre[b[i]]+sz[b[i]]-1);
			// cerr<<x<<" "<<y<<" "<<T1.sum[x]<<" "<<T1.sum[y]<<" "<<T1.sum[T1.rt[i]]<<" "<<pre[b[i]]<<" "<<b[i]<<" endlendl\n";
            if (pre[b[i]]-1>=1) T1.split(x,y,1,n,pre[b[i]]-1);
            if (i+1<=q) T1.mer(T1.rt[i+1],y,1,n);
            if (i+1<=q) T1.mer(T1.rt[i+1],T1.rt[i],1,n);
            if (i+p<=q) T1.mer(T1.rt[i+p],x,1,n);
        }
    }


	for (int i=1;i<=q;i++)
		cout<<res2[i]-res[i]*dep[b[i]]<<" "<<res[i]<<"\n";
	return 0;
}
```

---

