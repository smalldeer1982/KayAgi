# [PA 2019] Szprotki i szczupaki

## 题目描述

在湖中有 $n$ 条小鱼，第 $i$ 条小鱼的重量为 $w_i$。

共 $q$ 个操作，每个操作是下面 $3$ 种之一：

- `1 s k` 假如现在来了一条重量为 $s$ 的大鲨鱼，它的目标是让自己的重量达到至少 $k$ (包含 $k$)，问它至少需要吃掉多少条小鱼？如果鲨鱼当前的重量严格大于要吃掉的小鱼的重量 $w$，那么它可以吃掉这条小鱼，并使得自己的重量增加 $w$。
- `2 w` 添加一条重量为 $w$ 的小鱼。
- `3 w` 删除一条重量为 $w$ 的小鱼，保证存在至少一条这样的小鱼。

## 说明/提示

对于 $100\%$ 的数据，$1\le w_i\le 10^{12}$，$1\le s,k\le 10^{18}$ ，$1\le w\le 10^{12}$，$1\le n\le 3\times 10^5$，$1\le q\le 10^5$。

## 样例 #1

### 输入

```
4
1 4 8 1
15
1 2 3
1 2 4
1 2 5
1 3 3
1 3 5
1 3 16
1 4 16
1 8 17
1 100 101
1 100 115
1 3 9
2 2
1 3 9
3 4
1 3 9```

### 输出

```
1
2
-1
0
2
4
3
2
1
-1
3
2
-1```

# 题解

## 作者：伟大的王夫子 (赞：8)

先考虑暴力。容易想到贪心：每次吃所有能吃的小鱼中最大的鱼，一个个暴力吃，可以得到正确答案。

我们再考虑一下如何优化贪心的过程。设鲨鱼当前重量为 $s$，所有他吃不了的小鱼的重量最少为 $x$。显然 $x \ge s$。容易看出，在 $s \le x$ 时，这条鲨鱼能吃的小鱼的集合不变，我们直接统一处理即可。

我们可以用一个线段树维护当前所有的鱼，先全部读入，并且将重量离散化，每次求出大于等于当前鲨鱼重量的重量最小的鱼，若其重量为 $x$，那么吃完这一轮后，鲨鱼至少要将重量变为 $\min(k, x +1)$。若无法到达，那么一定无解（因为到达不了 $x+1$，吃不了其它的鱼）。

再证明一下时间复杂度。若当前鲨鱼重量为 $s$，大于等于当前鲨鱼重量的重量最小的鱼重量为 $x$。经过一步操作之后，$s$  的最小值为 $x +1$。那么再下一步，它就一定会吃一条重量 $\ge x$ 的鱼。而刚开始时 $s \le x$，故这会使鲨鱼重量翻倍。因此每一次求答案，这种步骤最多重复 $O(\log k)$ 次。其中 $k$ 为要求达到的重量。

再加上线段树的 $O(n \log n)$，总复杂度为 $O(n \log n \log k)$。较为卡常，原题时间限制 20s，loj 7s，在一秒的时间内过就必须开 O2。

代码实现时要注意常数，否则开了 O2 仍有很大可能不过。好好想清楚，毕竟这题细节挺多的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
using LL = long long;
int n, m, tt;
LL b[N];
struct {
	int op;
	LL x, w;
} a[N];
struct Seg {
	struct node {
		int l, r, cnt;
		LL sum;//懒标记直接不需要，如果sum = 0则直接返回，类似永久化标记。 
	} t[N << 2];
	node stk[N << 2];
	int po[N << 2], tp;
	bool vis[N << 2];
	inline void Up(int p) {
		t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
		t[p].cnt = t[p << 1].cnt + t[p << 1 | 1].cnt;
	}
	void build(int p, int l, int r) {
		t[p].l = l, t[p].r = r;
		if (l == r) {
			t[p].cnt = l == tt;
			t[p].sum = (l == tt) * b[tt];
			return;
		}
		int mid(l + r >> 1);
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		Up(p);
	}
	void change(int p, int x, int v) {
		if (t[p].l == t[p].r) {
			t[p].sum += v * b[x];
			t[p].cnt += v;
			return;
		}
		int mid(t[p].l + t[p].r >> 1);
		if (x <= mid) change(p << 1, x, v);
		else change(p << 1 | 1, x, v);
		Up(p);
	}
	int ask(int p, int x) {
		if (!t[p].sum) return 0;
		if (x <= t[p].l) {
			if (t[p].l == t[p].r) return t[p].l;
			int t = ask(p << 1, x);
			if (t) return t;
			else return ask(p << 1 | 1, x);
		}
		int mid(t[p].l + t[p].r >> 1);
		if (x <= mid) {
			int t = ask(p << 1, x);
			if (t) return t;
		}
		return ask(p << 1 | 1, x);
	}
	void work(int p) {
		if (!vis[p]) vis[p] = 1, stk[++tp] = t[p], po[tp] = p;
	}
	void modify(int p, int r, LL &foo, int &cnt) {
		if (!t[p].sum || foo <= 0) return;
		work(p);
		if (t[p].r <= r) {
			if (t[p].l == t[p].r) {
				int cc = min((foo - 1) / b[t[p].l] + 1, 1ll * t[p].cnt);
				t[p].cnt -= cc;
				t[p].sum -= cc * b[t[p].l];
				cnt += cc;
				foo -= cc * b[t[p].l];
			} else {
				if (t[p << 1 | 1].sum <= foo) {
					work(p << 1 | 1);
					foo -= t[p << 1 | 1].sum, cnt += t[p << 1 | 1].cnt;
					t[p << 1 | 1].sum = 0, t[p << 1 | 1].cnt = 0;
					modify(p << 1, r, foo, cnt);
				} else modify(p << 1 | 1, r, foo, cnt);
				Up(p);//必须记得更新，否则就会少减去一些 
			}
			return;
		}
		int mid(t[p].l + t[p].r >> 1);
		if (r > mid) modify(p << 1 | 1, r, foo, cnt);
		modify(p << 1, r, foo, cnt);
		Up(p);
	}
	int calc(LL ss, LL kk) {
		if (ss >= kk) return 0;//不用吃 
		if (ss <= b[1]) return -1;//需要吃但是没得吃 
		int ans = 0;
		while (ss < kk) {
			int pos = lower_bound(b + 1, b + tt + 1, ss) - b, vv = pos;
			vv = ask(1, vv);
			LL vvv = min(b[vv] + 1, kk) - ss;//需要吃多少 t.ask(1, vv)
			int mfood = pos - 1;
			LL vvvv = vvv;
			modify(1, mfood, vvvv, ans);
			if (vvvv > 0) {
				ans = -1;
				break;
			}
			ss += vvv - vvvv;
		}
		while (tp) {
			t[po[tp]] = stk[tp], vis[po[tp]] = 0;
			--tp;
		}
		return ans;
	}
} t;
int main() { 
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		a[i].op = 2;
		scanf("%lld", &a[i].x);
		b[++tt] = a[i].x;
	}
	scanf("%d", &m);
	for (int i = n + 1; i <= n + m; ++i) {
		scanf("%d%lld", &a[i].op, &a[i].x);
		if (a[i].op == 1) scanf("%lld", &a[i].w);
		else b[++tt] = a[i].x;
	}
	b[++tt] = 2e18;
	sort(b + 1, b + tt + 1);
	tt = unique(b + 1, b + tt + 1) - b - 1;
	for (int i = 1; i <= n + m; ++i)
		if (a[i].op != 1) a[i].x = lower_bound(b + 1, b + tt + 1, a[i].x) - b;
	t.build(1, 1, tt);
	for (int i = 1; i <= n + m; ++i) {
		if (a[i].op == 1) printf("%d\n", t.calc(a[i].x, a[i].w));
		if (a[i].op == 2) t.change(1, a[i].x, 1);
		if (a[i].op == 3) t.change(1, a[i].x, -1);
	}
}
```

---

## 作者：一只绝帆 (赞：5)

目前洛谷最优解（$2023.8.20$）。

我感觉是常数小的写法导致的。

首先我们肯定希望只关注这条鱼吃若干轮小鱼后吃到比当初的自己大的鱼这个过程，因为这样只需要 $\log$ 轮即可。

所以我们考虑每次求出再吃多少条鱼就可以达到下一个目标（这个目标可以是吃到比自己大的鱼或者达到真正的目标）。

那么贪心的想，在达到这个目标前只能吃比自己小的连续一段鱼，如果比自己小的全吃了也达不到就寄。

但是你发现已经吃过的区间不能再吃了。

所以我们每次在线段树上 `query` 的同时把 `query` 到的区间顺便清空。

（对于多条鱼重合在一个节点的情况，我们需要吃一部分，特判一下。）

注意线段树上二分时如果要取一整段，不能直接把答案加上一整段后递归另一边，还是要装模作样的递归一下这一边（虽然递归一层就会返回），目的是把清空操作执行掉。

注意我们的 `query` 是独立的，所以我们下次 `query` 的时候还得还原回来。

直接采用简洁的时间戳写法，对清空的节点打一个时间戳标记，下次递归过来如果时间戳显示不是本轮清空的就把该节点还原，注意 `pushup()` 需要用到儿子的正确值，所以到一个点的时候要检查时间戳，`pushup()` 的时候也要检查儿子的时间戳。

然后我们还要实现求最近的比 $x$ 大的一条鱼，需要维护每个节点的 $\max$（注意不止需要 $size$）然后线段树上二分。

为什么清空一个节点不需要递归下传懒标记把子节点也清空呢？

因为询问是越来越往右的，即询问的区间总包含上一段询问区间。

Code：
```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##end(b);i<=i##end;i++)
#define gc getchar
#define l(x) (x<<1)
#define r(x) (x<<1|1)
#define mid (L+R>>1)
#define fd(x) (lower_bound(V+1,V+vnt+1,x)-V)
using namespace std;using ll=long long;
ll read() {
	ll s=0;char c=gc(),w=0;
	while(c<'0'||c>'9') w|=c=='-',c=gc();
	while(c>='0'&&c<='9') s=s*10+(c^48),c=gc();
	return w?-s:s;
} const int N=4e5+5,C=N<<2;
int n,vnt,q,op[N],t[C],T,re;
ll V[N],c1[C],s1[C],mx[C],c[C],s[C],w[N],u[N],v[N];
void reb(int d) {if(t[d]^T) t[d]=T,c1[d]=c[d],s1[d]=s[d];}
void up(int d) {reb(l(d));reb(r(d));c1[d]=c1[l(d)]+c1[r(d)];s1[d]=s1[l(d)]+s1[r(d)];}
void clr(int d) {t[d]=T;c1[d]=s1[d]=0;}
void ins(int x,int b,int L=1,int R=vnt,int d=1) {
	c[d]+=b,s[d]+=b*V[x];if(L==R) return mx[d]=c[d]?V[L]:0,void();
	x<=mid?ins(x,b,L,mid,l(d)):ins(x,b,mid+1,R,r(d));mx[d]=max(mx[l(d)],mx[r(d)]); 
}
ll upd(int r,ll ned,int L=1,int R=vnt,int d=1) {
	ll res=0;reb(d);if(R<=r&&s1[d]<=ned) return res=s1[d],re+=c1[d],clr(d),res;
	if(L==R) return re+=(res=(ned+V[L]-1)/V[L]),c1[d]-=res,s1[d]-=res*V[L],res*V[L];
	if(r<mid+1) return res=upd(r,ned,L,mid,l(d)),reb(r(d)),up(d),res;
	return (res=upd(r,ned,mid+1,R,r(d)))<ned&&(res+=upd(r,ned-res,L,mid,l(d))),up(d),res;
}
int qr(ll x,int L=1,int R=vnt,int d=1) {
	if(L==R) return mx[d]>=x?L:vnt+1;
	return mx[l(d)]>=x?qr(x,L,mid,l(d)):qr(x,mid+1,R,r(d));
}
int main() {
	n=read();
	F(i,1,n) V[++vnt]=w[i]=read();
	F(i,1,q=read()) {
		op[i]=read();
		if(op[i]==1) u[i]=read(),v[i]=read();
		else V[++vnt]=u[i]=read();
	} sort(V+1,V+vnt+1);vnt=unique(V+1,V+vnt+1)-V-1;
	F(i,1,n) ins(fd(w[i]),1);
	F(i,1,q) {
		if(op[i]==1) {
			re=0;++T;ll k,ned,num;while(u[i]<v[i]&&(k=qr(u[i]))>1) {
				u[i]+=(num=upd(k-1,ned=min(v[i]-u[i],k<=vnt?V[k]-u[i]+1:(ll)1e18)));
				if(num<ned) break;
			} printf("%d\n",u[i]>=v[i]?re:-1);
		} else if(op[i]==2) ins(fd(u[i]),1);
		else ins(fd(u[i]),-1);
	}
	return 0;
} 
```

---

## 作者：CYZZ (赞：4)

## [P5986](https://www.luogu.com.cn/problem/P5986)

### 思路
每次吃比自己小的鱼中最大的一定是最优的。

称一次升级为：吃完这条鱼后能够吃到**原本吃不到**的鱼。设第 $i$ 次**升级后**吃的第一条鱼为 $x_i$。

不难发现 $W_{x_i}>\sum\limits_{j\in[1,i-2]}W_{x_j}$ ，化简得 $W_{x_i}>W_{x_{i-1}}+W{x_{i-2}}$，也就是鱼的大小的增长速度大于斐波那契数列的增长速度。

容易发现每次升级后吃掉的鱼一定构成以 $x_i$ 为右端点的一段区间。于是离散化后维护一个线段树，然后**线段树二分**暴力找区间。

复杂度 $\mathcal{O}(n\log n+q\log n\times升级次数)$，这玩意严格小于 $\mathcal{O}(n\log n+q\log n\log W)$，$W$ 为值域。

具体地，开一个 `multiset` 维护当前在集合中的鱼，这样就能方便地用 `lower_bound/upper_bound` 查找。

### 实现
由于我个人实现不好调了一天，所以把坑点写出来给大家避雷。

线段树需要维护**区间和**以及**区间推平**。由于吃过的鱼不能再被吃，所以要给已经吃掉的区间推平为 $0$。

但是询问之间互不影响，所以区间推平后需要进行**复原**。具体地，用 `map` 存下所有修改过的地址和原本的值，在询问结束后一个一个撤销回去即可。

离散化也是一大坑点，我们需要使原数组中**相同**的数在离散化后**不相同**（这样才能放在线段树上），还需要保证 3 操作中被删除的鱼**一定已在集合中**。这些只需要精细实现即可，具体参照代码。

代码的核心是 `solve` 和 `LBS` 函数，主要是我其它地方写成一坨史，但是注释还是足够的。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 600005
#define ll long long
#define lwb lower_bound
#define upb upper_bound
#define PLI pair<ll,int>
#define fi first
#define se second
#define inf 1e18+5
int n,q,m;
ll a[N],re[N];
struct Query{int ope;ll x,y;}Q[N];
PLI tmp[N];int bk[N];
namespace SGT
{
    unordered_map<ll*,ll>mp1;//用来撤销区间推平造成的影响
    ll tr[N<<2],cnt[N<<2],tag[N<<2];
    inline void cpy(ll *x){if(!mp1[x]) mp1[x]=*x?*x:-1;}//给线段树节点备份
    inline void push_up(int p,bool flag)
    {
        if(flag) cpy(&tr[p]),cpy(&cnt[p]);
        tr[p]=tr[p<<1]+tr[p<<1|1];
        cnt[p]=cnt[p<<1]+cnt[p<<1|1];
    }
    inline void push_tag(int p,bool flag)//flag 表示是否需要撤销
    {
        if(flag) cpy(&tag[p]),cpy(&tr[p]),cpy(&cnt[p]);
        tag[p]=1;tr[p]=cnt[p]=0;
    }
    inline void push_down(int p,bool flag)//flag 同上
    {
        if(!tag[p]) return ;
        push_tag(p<<1,flag);push_tag(p<<1|1,tag);
        if(flag) cpy(&tag[p]);tag[p]=0;
    }
    inline void build(int p,int l,int r)
    {
        if(l==r) return tr[p]=bk[l]*re[l],cnt[p]=bk[l],void();//bk[l] 表示是否初始时在集合中
        int mid=(l+r)>>1;build(p<<1,l,mid);build(p<<1|1,mid+1,r);push_up(p,0);
    }
    inline void update(int p,int l,int r,int pos,ll val)
    {
        if(l==r) return tr[p]=val,cnt[p]=!!val,void();int mid=(l+r)>>1;push_down(p,0);//修改集合时不用撤销
        if(pos<=mid) update(p<<1,l,mid,pos,val);else update(p<<1|1,mid+1,r,pos,val);push_up(p,0);
    }
    inline ll LBS(int p,int l,int r,int pos,ll &val,ll need,int &use)
    {
        if(r<=pos)
        {
            if(val+tr[p]<need||l==r)//这里把两种情况并在一起写了
            {
                val+=tr[p];use+=cnt[p];push_tag(p,1);
                return val+tr[p]<need?0:l;
            }
        }
        int mid=(l+r)>>1;push_down(p,1);
        if(pos>mid)
        {
            ll ret=LBS(p<<1|1,mid+1,r,pos,val,need,use);
            push_up(p,1);if(ret) return ret;
        }
        ll ret=LBS(p<<1,l,mid,pos,val,need,use);
        push_up(p,1);return ret;
    }
}using namespace SGT;
multiset<PLI>fish;
int solve(ll st,ll ed)
{
    ll siz=st;int ret=0;
    if(siz>=ed) return ret;//特判
    if(fish.lwb({siz,0})==fish.begin()) return -1;//特判
    while(1)
    {
        if(siz>=ed) return ret;
        ll nxt=min(ed,fish.lwb({siz,0})->fi+1);// x_i，目标鱼的大小
        int pnow=prev(fish.lwb({siz,0}))->se;// 现在能吃到的最大的鱼
        if(!LBS(1,1,m,pnow,siz,nxt,ret)) return -1;//在线段树二分的同时处理大小和数量
    }
    return -1;
}
void recover()//撤销修改
{
    for(pair<ll*,ll>i:mp1) *i.fi=i.se==-1?0:i.se;
    mp1.clear();
}
unordered_map<ll,int>mp;int idx;//辅助离散化
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        tmp[++m]={a[i],0};
        if(!mp[a[i]]) mp[a[i]]=++idx;
    }
    sort(a+1,a+n+1);scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%lld",&Q[i].ope,&Q[i].x);
        if(Q[i].ope==1) scanf("%lld",&Q[i].y);
        if(Q[i].ope==2)
        {
            tmp[++m]={Q[i].x,0};
            if(!mp[Q[i].x]) mp[Q[i].x]=++idx;
        }
    }
    sort(tmp+1,tmp+m+1);
    for(int i=1;i<=m;i++) tmp[i].se=i;
    basic_string<int>stk[idx+1];//用来保证“3 操作中被删除的鱼一定已在集合中”
    for(int i=1;i<=n;i++)
    {
        int pos=upb(tmp+1,tmp+m+1,make_pair(a[i],0))-tmp;
        re[pos]=a[i];a[i]=pos;tmp[pos].se=0;bk[pos]=1;
        fish.insert({re[a[i]],a[i]});
        stk[mp[re[a[i]]]]+=a[i];
    }
    for(int i=1;i<=q;i++)
    {
        if(Q[i].ope==2)
        {
            int pos=upb(tmp+1,tmp+m+1,make_pair(Q[i].x,0))-tmp;
            re[pos]=Q[i].x;Q[i].x=pos;tmp[pos].se=0;
            stk[mp[re[Q[i].x]]]+=Q[i].x;
        }
        if(Q[i].ope==3)
        {
            int tt=stk[mp[Q[i].x]].back();
            stk[mp[Q[i].x]].pop_back();Q[i].x=tt;
        }
    }
    build(1,1,m);fish.insert({inf,0});
    for(int i=1;i<=q;i++)
    {
        if(Q[i].ope==1) printf("%d\n",solve(Q[i].x,Q[i].y)),recover();
        else if(Q[i].ope==2) update(1,1,m,Q[i].x,re[Q[i].x]),fish.insert({re[Q[i].x],Q[i].x});
        else update(1,1,m,Q[i].x,0),fish.erase(fish.find({re[Q[i].x],Q[i].x}));
    }
}
```

---

## 作者：Arghariza (赞：0)

显然的贪心策略，每次选能吃范围内的最大的吃掉。如果不能达到 $k$ 就寄了。

所以记目前鲨鱼大小为 $s$，找到 $s$ 的后继 $t$（比 $s$ 大的鱼中最小的）。定义吃“一轮”表示在大小为 $s$ 时吃掉某些**目前**能吃的大小 $<s$ 的鱼以达到 $t+1$。不妨假设 $t<k$，如果 $s$ 这一轮无法到达 $t+1$ 就显然无解（目前能吃的鱼的集合不变）；否则下一轮结束后 $s$ 至少翻倍（因为接下来能吃掉 $t$）。

所以我们只关心从 $s$ 开始吃一轮的过程，而过程数是 $O(\log w)$ 的，直接模拟每次过程即可。需要查询 $s$ 的后继以及大小在某个范围之内所有鱼的大小之和，还要快速找到最小的满足条件的后缀，可以线段树上二分解决，但由于鱼的大小可以重复，平衡树会好写很多。

复杂度 $O(n\log n\log w)$。

```cpp
// Problem: P5986 [PA2019] Szprotki i szczupaki
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5986
// Memory Limit: 125 MB
// Time Limit: 7000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Med;

mt19937 rnd(time(0));
const int N = 3e5 + 300;
const ll inf = 1e18;

int n, q, rt, tot;
vector<int> op;

struct fhq {
	ll vl, su;
	int sz, id, lc, rc;
	fhq () { }
	fhq (int _sz, ll _su, ll _v, int _i, int _l, int _r) : 
		sz(_sz), su(_su), vl(_v), id(_i), lc(_l), rc(_r) { }
} tr[N << 1];

#define ls tr[x].lc
#define rs tr[x].rc

int mk(ll c) { return tr[++tot] = fhq(1, c, c, rnd(), 0, 0), tot; }
void pup(int x) { tr[x].sz = tr[ls].sz + tr[rs].sz + 1, tr[x].su = tr[ls].su + tr[rs].su + tr[x].vl; }

int mrg(int x, int y) {
	if (!x || !y) return x | y;
	if (tr[x].id < tr[y].id) return rs = mrg(rs, y), pup(x), x;
	else return tr[y].lc = mrg(x, tr[y].lc), pup(y), y;
}

void splv(int x, ll v, int &l, int &r) {
	if (!x) return l = r = 0, void();
	if (tr[x].vl <= v) l = x, splv(rs, v, rs, r);
	else r = x, splv(ls, v, l, ls);
	pup(x);
}

void spls(int x, ll v, int &l, int &r) {
	if (!x) return l = r = 0, void();
	if (tr[rs].su < v) r = x, spls(ls, v - tr[rs].su - tr[x].vl, l, ls);
	else l = x, spls(rs, v, rs, r);
	pup(x);
}

ll gmn(int x) {
	if (!x) return inf;
	if (!ls) return tr[x].vl;
	return gmn(ls);
}

void ins(ll v) { int x, y; splv(rt, v, x, y), rt = mrg(mrg(x, mk(v)), y); }
void del(ll v) { int x, y, z; splv(rt, v, y, z), splv(y, v - 1, x, y), y = mrg(tr[y].lc, tr[y].rc), rt = mrg(mrg(x, y), z); }

int qry(ll l, ll r) {
	int res = 0;
	while (l < r) {
		int x, y, z;
		splv(rt, l - 1, x, y);
		if (!x) break;
		ll k = min(r, gmn(y) + 1) - l;
		spls(x, k, x, z), op.pb(z), rt = mrg(x, y);
		if (tr[z].su < k) break;
		res += tr[z].sz, l += tr[z].su;
	}
	while (!op.empty()) {
		int x = op.back(), y, z; op.pop_back();
		if (!x) continue;
		splv(rt, tr[x].vl, y, z);
		rt = mrg(mrg(y, x), z);
	}
	if (l < r) return -1;
	return res;
}

void solve() {
	cin >> n; ll w;
	for (int i = 1; i <= n; i++) 
		cin >> w, ins(w);
	cin >> q;
	while (q--) {
		int o; ll x, y; cin >> o >> x;
		if (o == 1) cin >> y, cout << qry(x, y) << '\n';
		else if (o == 2) ins(x);
		else del(x);
	}
}

bool Mbe;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Med - &Mbe) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

