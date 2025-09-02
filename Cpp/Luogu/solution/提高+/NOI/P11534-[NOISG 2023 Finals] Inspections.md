# [NOISG 2023 Finals] Inspections

## 题目描述

兔子 Benson 正要造一架飞机！

Benson 的工厂有 $n$ 个机器，由 $1\sim n$ 编号。每台机器会工作一天，且每一天只能有一台机器工作。他需要制造 $m$ 个部件，由 $1\sim m$ 编号。每个部件用两个整数 $l_i, r_i$ 表示，其中 $l_i\leq r_i$。

制造第 $i$ 个部件时，Benson 将依次运行编号为 $l_i, l_i+1,\cdots,r_i$ 的机器。当一台机器结束工作，下一台机器会立即启动。此外，Benson 会依次制造这 $m$ 个部件。当一个部件制造完毕，下一个部件会立即开始制造。

为了保障机器的安全，工厂设有一个检查系数 $s$。若一台机器已经连续 $s$ 或更多天没有启动，那么这次启动前必须对其进行安全检查。特别地，第一次启动某个机器时无需进行安全检查。

Benson 有 $q$ 个询问 $s_1, s_2, \cdots, s_q$。对于每个检查系数 $s_j$，请你帮助他计算完成所有部件所需的检查次数。

## 说明/提示

#### 样例 #1 解释

Benson 会按照如下顺序启动机器：$1,2,3,3,4,5,2,3$。

第 $4$ 天启动的 $3$ 号机器连续 $0$ 天未启动；

第 $7$ 天启动的 $2$ 号机器连续 $4$ 天未启动；

第 $8$ 天启动的 $3$ 号机器连续 $3$ 天未启动。

当检查系数为 $0$ 时，$3$ 号机器会在第 $4$ 天和第 $8$ 天被安全检查，而 $2$ 号机器会在第 $7$ 天被安全检查。

当检查系数为 $2$ 时，$3$ 号机器会在第 $8$ 天被安全检查，而 $2$ 号机器会在第 $7$ 天被安全检查。

#### 数据范围

| Subtask | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $0$ | 样例 |
| $1$ | $11$ | $n,m,q\leq 200$ |
| $2$ | $18$ | $n,m\leq 2000$ |
| $3$ | $22$ | $l_i=1$ |
| $4$ | $26$ | $m\leq2000$ |
| $5$ | $23$ | 无 |

对于 $100\%$ 的数据：

- $1\leq n, m,q\leq 2\times 10^5$
- $1\leq l_i\leq r_i\leq n$
- $0\leq s_j\leq 10^{12}$

注：由于洛谷限制，数据不完全按照原题分配子任务。

## 样例 #1

### 输入

```
5 3 7
1 3
3 5
2 3
0 1 2 3 4 5 6
```

### 输出

```
3 2 2 2 1 0 0 
```

## 样例 #2

### 输入

```
6 6 7
1 6
1 5
1 4
1 3
1 2
1 1
1 2 3 4 5 6 7
```

### 输出

```
15 14 12 9 5 0 0 
```

# 题解

## 作者：c_y_y (赞：1)

# [P11534 [NOISG 2023 Finals] Inspections](https://www.luogu.com.cn/problem/P11534)
维护每个机器最后一次使用的时间，注意到每一次操作**相当于将区间 $[l_{i},r_{i}]$ 修改为一个公差为 $+1$ 的等差数列**。由于公差固定，因此只需维护首项便可知道该区间内所有数的值即可。

修改区间的值考虑 ODT。不断修改区间，维护首项。

最棘手的问题就是如何计算答案。

由于答案只要求修改次数，不难想到在修改操作中，每次不断暴力修改块时顺便计算答案，开个 vector 存放前后两次差值和区间长度。最后将询问离线，从大到小顺序求解，将原来的 vector 中的区间一个个丢到询问中判断是否合法（有点类似于单调栈），如果不合法就调到下一个询问。由于我们将询问变得有序，故所求答案是单调不降的。我们就很顺利地解决了这个问题。

```cpp
#define LL long long
#define IT set<node>::iterator
inline long long read() {
	long long x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
const int N = 2e5 + 10; 
struct node {
	int l, r;
	mutable LL v;
	node(int L, int R = -1, LL V = 0):l(L), r(R), v(V) {}
	bool operator <(const node& b) const {
		return l < b.l;
	}
};
struct que {
	LL s;
	int id;
}a[N];
vector<pair<LL, LL> > d;
set<node>s;
IT split(int pos) {
	IT it = s.lower_bound(pos);
	if(it != s.end() && it->l == pos) return it;
	--it;
	int l = it->l, r = it->r;
	LL v = it->v;
	s.erase(it);
	s.insert(node(l, pos - 1, v));
	return s.insert(node(pos, r, v + pos - l)).first;
}
LL ans[N];
void assign(int l, int r, LL val) {
	IT itr = split(r + 1), itl = split(l);
	LL now = val;
	for (IT it = itl; it != itr; it++) {
		d.push_back(make_pair(now - it->v, it->r - it->l + 1));
		now += it->r - it->l + 1; 
	}
	s.erase(itl, itr);
	s.insert(node(l, r, val));
}
bool cmp(que x, que y) {
	return x.s > y.s;
}
void solve() {
	int n = read(), m = read(), q = read();
	s.insert(node(1ll, n, 1e18 + 10));
	LL now = 1;
	while(m--) {
		int l = read(), r = read();
		assign(l, r, now);
		now += (LL)r - l + 1;
	}
	for (int i = 1; i <= q; i++) {
		a[i].s = read(), a[i].id = i;
	}
	sort(a + 1, a + q + 1, cmp);
	sort(d.begin(), d.end());
	
	LL cnt = 0;
	for (int i = 1; i <= q; i++) {
		while(d.size() && d.back().first > a[i].s)
			cnt += d.back().second, d.pop_back();
		ans[a[i].id] = cnt;
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << " ";
}

```

---

## 作者：one_of_the_person (赞：0)

非常好的 ODT 的练手题。
## 思路
可以维护每台机器最后一次运行的时间，每一次制造部件可以视为将 $\lbrack l_i,r_i\rbrack$ 范围内机器的最后运行时间修改为一个公差为 1 的等差数列，这就相当于一个区间覆盖操作，于是我们就可以使用 ODT 来维护，每一个三元组 $(l,r,v)$ 表示区间 $\lbrack l,r\rbrack$ 的值为一个首项为 $v$ 公差为 1 的等差数列。\
接下来考虑如何统计答案。可以在每次覆盖操作时暴力枚举被覆盖的区间，用一个 vector 记录被覆盖区间与新区间的差和被覆盖区间的长度。在完成所有操作后把所有询问离线下来，按从大到小排序。对于一个被覆盖区间，如果它能对一个询问做出贡献，那它也可以对小于这个询问的所有询问做出贡献，于是我们将 vector 里存储的结果也按照记录的值从小到大排序，然后从后往前扫统计每个询问的答案，最后将询问的顺序还原，直接输出即可。
## AC 代码
这里因为 `set` 的迭代器实在是难以使用，于是手写了一遍平衡树。
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 400000
#define Inf (1ll*N*INT_MAX)
using namespace std;
struct Interval{
    int l,r,v;
    bool friend operator<(Interval const x,Interval const y){return x.l<y.l;}
    bool friend operator>(Interval const x,Interval const y){return x.l>y.l;}
    bool friend operator<=(Interval const x,Interval const y){return x.l<=y.l;}
    bool friend operator>=(Interval const x,Interval const y){return x.l>=y.l;}
    Interval friend operator-(Interval const x,int const y){return {x.l-y,x.r,x.v};}
};//这里定义的是 ODT 维护的区间，重载运算符方便平衡树维护
struct Node{int s[2],size,rnd;Interval v;};
struct Problem{int x,id,ans;};
struct Ans{int v,len;};
int n,m,q,ul,ur,sum=1;
Problem p[N+5];
vector<Ans>ans;
struct FHQ{//平衡树
    int root=0,tot=0,usum;
    Node tree[N+5];
    mt19937 rnd;
    vector<int>mem;
    int ask(){
        if(mem.empty())return ++tot;
        int u=mem.back();
        mem.pop_back();
        return u;
    }
    void remove(int x){mem.push_back(x);return;}
    void init(){
        srand(time(0));
        rnd.seed(rand()^time(0));
        return;
    }
    void pushup(int x){tree[x].size=tree[tree[x].s[0]].size+1+tree[tree[x].s[1]].size;return;}
    int newNode(Interval v){
        int p=ask();
        tree[p].s[0]=tree[p].s[1]=0;
        tree[p].size=1,tree[p].v=v,tree[p].rnd=rnd();
        return p;
    }
    void treeRemove(int x){//再删除节点的同时统计答案
        if(!x)return;
        treeRemove(tree[x].s[0]);
        ans.push_back({usum-tree[x].v.v-1,tree[x].v.r-tree[x].v.l+1});
        usum+=tree[x].v.r-tree[x].v.l+1;
        remove(x);
        treeRemove(tree[x].s[1]);
        return;
    }
    void split(int now,Interval k,int &x,int &y){
        if(!now){x=y=0;return;}
        if(tree[now].v<=k)x=now,split(tree[now].s[1],k,tree[x].s[1],y);
        else y=now,split(tree[now].s[0],k,x,tree[y].s[0]);
        pushup(now);
        return;
    }
    int merge(int u,int v){
        if(!u||!v)return u|v;
        if(tree[u].rnd<tree[v].rnd){
            tree[u].s[1]=merge(tree[u].s[1],v);
            pushup(u);
            return u;
        }
        else{
            tree[v].s[0]=merge(u,tree[v].s[0]);
            pushup(v);
            return v;
        }
        return 0;
    }
    int insert(Interval v){
        int x,y,p;
        split(root,v,x,y);
        p=newNode(v);
        root=merge(merge(x,p),y);
        return p;
    }
    void delet(Interval l,Interval r,bool f){
        int x,y,z;
        split(root,r,x,z);
        split(x,l-1,x,y);
        if(f)treeRemove(y);
        else remove(y);
        root=merge(x,z);
        return;
    }
    int kth(int x,int k){
        while(x){
            if(k<tree[tree[x].s[0]].size+1)x=tree[x].s[0];
            else if(k==tree[tree[x].s[0]].size+1)break;
            else k-=tree[tree[x].s[0]].size+1,x=tree[x].s[1];
        }
        return x;
    }
    int find(Interval v){
        int x,y,k;
        split(root,v,x,y);
        k=kth(x,tree[x].size);
        root=merge(x,y);
        return k;
    }
}tree;
int split(int p){//分裂操作
    int t=tree.find({p,0,0});
    if(tree.tree[t].v.l==p)return t;
    int l=tree.tree[t].v.l,r=tree.tree[t].v.r,v=tree.tree[t].v.v;
    tree.delet(tree.tree[t].v,tree.tree[t].v,0);
    tree.insert({l,p-1,v});
    return tree.insert({p,r,v+p-l});//注意分裂后的右区间的首项与原区间不同
}
void assign(int l,int r,int v){
    int il=split(l),ir=split(r+1);
    tree.usum=v;
    tree.delet(tree.tree[il].v,tree.tree[ir].v-1,1);//在删除的同时统计答案
    tree.insert({l,r,v});
    return;
}
bool cmp1(Problem x,Problem y){return x.x>y.x;}
bool cmp2(Problem x,Problem y){return x.id<y.id;}
bool cmp3(Ans x,Ans y){return x.v<y.v;}
int read(){
    int f=1,g=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9'){
        g=g*10+ch-'0';
        ch=getchar();
    }
    return f*g;
}
void print(int x){
    if(x<0){
        putchar('-');
        x*=-1;
    }
    if(x>9)print(x/10);
    putchar(x%10+'0');
    return;
}
main(){
    tree.init();
    n=read(),m=read(),q=read();
    tree.insert({1,n+1,Inf});//给区间赋初值，注意初值要足够大
    for(int i=1;i<=m;i++){
        ul=read(),ur=read();
        assign(ul,ur,sum);
        sum+=ur-ul+1;
    }
    for(int i=1;i<=q;i++)p[i].x=read(),p[i].id=i;
    sort(p+1,p+1+q,cmp1);//将询问排序
    sort(ans.begin(),ans.end(),cmp3);//将统计的答案排序
    sum=0;
    for(int i=1;i<=q;i++){
        while(ans.size()&&ans.back().v>=p[i].x){
            sum+=ans.back().len;
            ans.pop_back();
        }
        p[i].ans=sum;//统计答案
    }
    sort(p+1,p+1+q,cmp2);//还原
    for(int i=1;i<=q;i++)print(p[i].ans),putchar(' ');
    return 0;
}
```

---

## 作者：Amadeus004 (赞：0)

制造一个部件时，启动的机器编号是连续的，其开始启动的时间也是连续的。所以启动等价于将一个区间内的数赋值为公差为 $1$ 的等差数列。要维护这段区间的信息，我们只需要区间左端点 $L$，等差数列的首项 $T$ 即可。

不难发现，我们要做的事等价于区间推平，求每次操作后区间内每个位置当前值与先前值的差值之和，可以用 ODT 维护。每次修改最多增加两个区间，最少减少一个区间，复杂度正确。

考虑统计答案，对于 $s_i$，只有 $\Delta T\ge s_i$ 的情况才会造成贡献。用二元组 $(\Delta T,l)$ 存下每次修改时等差数列首项的差值与区间长度，丢到 vector 内排序，从大到小累计相加即可得到答案。

第一次启动的情况可以通过将初始区间赋为极大值避免讨论，这种情况下 $\Delta T<0,s_i>0$，必定不会产生贡献。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,t=1;
	char a;
	while(!isdigit(a=getchar()))t=a=='-'?-1:t;
	do{x=(x<<3)+(x<<1)+(a^48);}while(isdigit(a=getchar()));
	return x*t;
}
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10^48);
}
const int N=2e5+5;
ll n,m,k,tim;
struct question{ll x,id,ans;}q[N];
inline bool cmp1(question x,question y){return x.x>y.x;}
inline bool cmp2(question x,question y){return x.id<y.id;}
struct node{
	ll l,r;mutable ll v;
	node(ll l,ll r=0,ll v=0):l(l),r(r),v(v){}
	inline bool operator<(const node &x)const{return l<x.l;}
};
set<node>s;
vector<pair<ll,ll>>G;
#define iter set<node>::iterator
inline iter split(ll pos){
	iter it=s.lower_bound(node(pos));
	if(it!=s.end() and it->l==pos)return it;
	it--;
	if(it->r<pos)return s.end();
	ll l=it->l,r=it->r,v=it->v;
	s.erase(it),s.insert(node(l,pos-1,v));
	return s.insert(node(pos,r,v+pos-l)).first;
}
inline void assign(ll l,ll r,ll x){
	iter itr=split(r+1),itl=split(l);
	ll tmp=x;
	for(iter it=itl;it!=itr;it++)
		G.push_back({tmp-it->v,it->r-it->l+1}),tmp+=it->r-it->l+1;
	s.erase(itl,itr),s.insert(node(l,r,x));
}
int main(){
	n=read(),m=read(),k=read(),s.insert(node(1,n,1e12));
	while(m--){
		ll l=read(),r=read();
		assign(l,r,tim),tim+=r-l+1;
	}
	for(int i=1;i<=k;i++)q[i].x=read(),q[i].id=i;
	sort(q+1,q+k+1,cmp1),sort(G.begin(),G.end()),reverse(G.begin(),G.end());
	for(int i=1,j=0;i<=k;i++){
		while(j<G.size() and G[j].first>q[i].x)
			q[i].ans+=G[j++].second;
		q[i].ans+=q[i-1].ans;
	}
	sort(q+1,q+k+1,cmp2);
	for(int i=1;i<=k;i++)write(q[i].ans),putchar(' ');
	return 0;
}
```

---

## 作者：StayAlone (赞：0)

简单题。

考虑一次询问怎么做。对于每台机器，维护其最后一次启动的时间。则修改形如区间赋值成公差为 $1$ 的等差数列。

用 ODT 维护，修改 $[l, r]$ 时，暴力检查修改前 $[l, r]$ 内的每段等差数列（由于公差相同，首项的差就是每一项的差），判断差是否大于 $s$ 累加答案即可。考虑颜色段均摊，总线段数量 $\mathcal O(m)$，每次暴力都会减少一个线段，复杂度就对了。

那么多次询问显然离线。按照 $s$ 降序，检查的机器数量始终不降。先做一次上面的暴力，不同之处在于记录等差数列每次修改与修改前的差，很好判断这些等差数列何时贡献答案。

时间复杂度 $\mathcal O(m\log m+q\log q)$。

[AC record](https://www.luogu.com.cn/record/197489078)

```cpp
int n, m, q; ll ans, opt[MAXN];
vector <pll> now, qur;

struct node {
	int l, r;
	mutable ll v;
	
	il bool operator < (const node &p) const {
		return l < p.l;
	}
};
set <node> odt;

il auto split(int x) {
	if (x > n) return odt.end();
	auto it = --odt.upper_bound(node{x, -1, -1});
	if (it -> l == x) return it;
	int l = it -> l, r = it -> r; ll v = it -> v;
	odt.erase(it); odt.insert(node{l, x - 1, v});
	return odt.insert(node{x, r, v + (x - l)}).fst;
}

il void upd(int l, int r, ll x) {
	auto itr = split(r + 1), itl = split(l); ll g = x;
	for (auto it = itl; it != itr; ++it) {
		auto [l, r, v] = *it;
		now.eb(g - v, r - l + 1); g += r - l + 1;
	} odt.erase(itl, itr); odt.insert(node{l, r, x});
}

int main() {
	read(n, m, q); odt.insert({1, n, 10000000000000});
	int l, r; ll sum = 1;
	while (m--) read(l, r), upd(l, r, sum), sum += r - l + 1;
	rep1(i, 1, q) read(sum), qur.eb(sum, i);
	sort(begin(qur), end(qur), greater<>());
	sort(begin(now), end(now));
	for (auto [v, id] : qur) {
		while (now.size() && now.back().fst > v) ans += now.back().snd, now.pop_back();
		opt[id] = ans;
	}
	rep1(i, 1, q) printf("%lld ", opt[i]);
	return 0;
}
```

---

