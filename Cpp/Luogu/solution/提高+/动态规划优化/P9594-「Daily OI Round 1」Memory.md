# 「Daily OI Round 1」Memory

## 题目描述

给定 $m$ 条线段，每条线段由四个正整数参数 $l_i,r_i,c_i,w_i$ 描述，其中 $l_i,r_i$ 是这条线段的端点，$c_i$ 是这条线段的种类，$w_i$ 是这条线段的权值。

你需要选出一些线段，满足以下条件且权值总和最高。

- 对于任意两条不同的线段 $i,j$，满足 $c_i = c_j$ 或 $[l_i,r_i]\cap[l_j,r_j]=\varnothing$。

## 说明/提示

### **样例解释**

对于样例 $1$，选出的线段分别是 $1,2,3$ 号线段，它们种类都相同，且权值和为 $21$，可以证明这是最优的选法。

### **数据范围**

**本题开启捆绑测试。**

|$\text{Subtask}$|分值|$m \le$|$w_i \le$|$c_i \le $|特殊性质|
| :-----------: | :-------------:|:-----------: | :-----------: | :-----------: | :-----------: |
|$0$|$5$|$16$|$10$|$10^9$|无|
|$1$|$20$|$2 \times 10^3$|$10^4$|$10^9$|无|
|$2$|$20$|$10^5$|$10^4$|$2$|无|
|$3$|$20$|$10^5$|$10^4$|$10^9$|A|
|$4$|$35$|$10^5$|$10^4$|$10^9$|无|

- 特殊性质 A：不存在互不相同的正整数 $i,j$ 使得 $l_i<l_j \leq r_j < r_i$。

对于全部数据，保证：$1\leq m\leq10^5$，$1\leq l_i\leq r_i\leq10^9$，$1\leq c_i\leq 10^9$，$1\leq w_i\leq10^4$。

## 样例 #1

### 输入

```
5
2 9 1 1
3 9 1 10
4 8 1 10
5 6 3 1
7 9 3 10```

### 输出

```
21```

## 样例 #2

### 输入

```
10
1 2 2 8
2 4 2 2
6 10 3 5
2 8 2 4
5 9 2 7
1 1 1 10
2 8 2 2
1 7 3 7
8 9 2 4
5 7 3 3```

### 输出

```
29```

# 题解

## 作者：一只绝帆 (赞：7)

线段树优化 dp。

我们一般见到的 dp 优化题如果是更注重优化的话，那数据范围根本想不出来这是一道 dp 题，这个时候就要敢想、敢推，才能摸到正解的边缘。

很多 dp 题都是基于贪心的，例如先按贪心排序，再在这个顺序上转移，亦或是某个转移的值不需要枚举很大的范围，其中都有可能用到了贪心思想。

本题就是前者。

其实遇到那种答案跟顺序没什么关系的题通常都要先排序。

按左端点排完序了之后我们发现可以轻松设出状态：设 $f_{i,c}$ 为考虑所有颜色为 $c$ 的元素、最右端点在 $i$ 的最大权值。

解释就是我们只关心右端点和颜色。

发现左右端点的具体值没什么用，只关心大小关系，于是离散化。

转移也比较好搞：

$$f_{r_i,c}\xleftarrow{\max} w_i+\max_{j=1}^{l_i-1}\max_kf_{j,k}\\f_{r_i,c}\xleftarrow{\max}w_i+\max_{j=1}^{r_i}f_{j,c}\\\forall j>r_i,f_{j,c}\xleftarrow+w_i$$ 

由于我们钦定了转移顺序是左端点由小到大，这三个转移得以成立。

加上优化就比较简单了，线段树区间 $+$ 区间 $\max$ 即可。

Code：
```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##end(b);i<=i##end;i++)
#define gc getchar
#define l(x) ls[x]
#define r(x) rs[x]
#define mid (L+R>>1)
using namespace std;
int read() {
	int s=0;char c=gc(),w=0;
	while(c<'0'||c>'9') w|=c=='-',c=gc();
	while(c>='0'&&c<='9') s=s*10+(c^48),c=gc();
	return w?-s:s;
} const int N=1e5+5,C=2e7+5,X=1e9+5;unordered_map<int,int> mp;
int n,hnt,snt,mx[C],l(C),r(C),tg[C],RT,rt[N],ans,V[N<<1],vnt,pre;vector<int> v[N<<1];
struct S {int l,r,c,w;bool operator<(const S &b) {return l==b.l?r<b.r:l<b.l;}} a[N];
int hsh(int x) {if(!mp.count(x)) mp[x]=++hnt;return mp[x];}
void up(int d) {mx[d]=max(mx[l(d)],mx[r(d)]);}
void pr(int &d,int t) {if(!d) d=++snt;mx[d]+=t;tg[d]+=t;}
void down(int &d) {if(tg[d]) pr(l(d),tg[d]),pr(r(d),tg[d]),tg[d]=0;} 
void add(int l,int r,int b,int L,int R,int &d) {
	if(R<l||r<L) return;if(!d) d=++snt;if(l<=L&&R<=r) return pr(d,b);
	down(d);add(l,r,b,L,mid,l(d));add(l,r,b,mid+1,R,r(d));up(d);
}
void ins(int x,int b,int L,int R,int &d) {
	if(!d) d=++snt;if(L==R) return mx[d]=max(mx[d],b),void();
	down(d);x<=mid?ins(x,b,L,mid,l(d)):ins(x,b,mid+1,R,r(d));up(d);
}
int q(int l,int r,int L,int R,int &d) {
	if(r<L||R<l) return 0;if(l<=L&&R<=r) return mx[d];
	return down(d),max(q(l,r,L,mid,l(d)),q(l,r,mid+1,R,r(d)));
}
int main() {
	F(i,1,n=read()) a[i]={V[++vnt]=read(),V[++vnt]=read(),hsh(read()),read()};
	sort(a+1,a+n+1);sort(V+1,V+vnt+1);vnt=unique(V+1,V+vnt+1)-V-1;
	int p=1;F(i,1,n) {
		a[i].l=lower_bound(V+1,V+vnt+1,a[i].l)-V;a[i].r=lower_bound(V+1,V+vnt+1,a[i].r)-V;
		v[a[i].r].push_back(a[i].c);
		while(p<a[i].l) {for(int c:v[p]) pre=max(pre,q(1,a[i].l-1,1,vnt,rt[c]));p++;}
		int Q=max(pre,q(1,a[i].r,1,vnt,rt[a[i].c]))+a[i].w;
		ins(a[i].r,Q,1,vnt,rt[a[i].c]);ans=max(ans,Q);
		add(a[i].r+1,X,a[i].w,1,vnt,rt[a[i].c]);ans=max(ans,mx[rt[a[i].c]]);
	} cout<<ans<<endl;
	return 0; 
}

```

（在博客页面看 $\LaTeX $ 并没有问题，但是管理审的时候表示 $\LaTeX$ 炸了/kk。）

---

## 作者：teylnol_evteyl (赞：5)

## subtask0
暴力，枚举哪些线段保留，判断是否满足条件。时间复杂度 $O(2^mm^2)$。
## subtask4
主要是给一些看似正确实则错误的算法的部分分。

其中一种思路是：先把线段端点和种类离散化，把线段按左端点为第一关键字、右端点为第二关键字从小到大排序。

设 $f_i$ 表示排序选择的线段中，排序最后的节点的右端点在 $i$ 的最大价值，$g_i$ 表示排序最后的节点的颜色是 $i$ 的最大价值。

由于这里右端点单调不减，所以只考虑前 $i$ 条线段，选择第 $i$ 条线段的最大价值为 $\max_{i=0}^{l_i-1} \{f_i,g_{c_i}\}$，用这个值更新答案和 $f,g$ 数组。

时间复杂度 $O(m\log m)$。
## subtask1
离散化后将线段按左端点由小到大排序。

设 $f_{i,j}$ 表示选出线段中右端点最大线段右端点在 $i$ 种类是 $j$ 的最大价值。

对第 $i$ 条线段，前 $i$ 条线段、选择第 $i$ 条线段且它的右端点在选出的右端点中是最大的价值是 $\max\{\max_{j=0}^{l_i-1}\max_k\{f_{j,k}\},\max_{j=0}^{r_i}\{f_{j,c_i}\}\}$，用它更新 $f_{r_i,c_i}$ 的值。

同时对于右端点最大线段与第 $i$ 条线段种类相同、右端点大于 $r_i$ 的情况，可以加上第 $i$ 条线段且右端点最大的线段不变。

时间复杂度 $O(m^2)$。
## subtask2
开 $2$ 棵线段树维护 $f$ 数组进行上面过程。

时间复杂度 $O(m\log m)$。
## subtask5
对每个种类开一棵线段树，需要动态开点。

时间复杂度 $O(m\log m)$，空间复杂度 $O(m\log m)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, sx, sy, x[N], y[N];
vector<int> p[N]; 
struct line{
	int l, r, c, w;
	bool operator <(const line &p) const
	{
		return l < p.l;
	}
}a[N];
int rr, ff, res;
struct node{
	int ls, rs;
	int v, l;
}t[N << 7];
int root[N], pid;

void change(int &u, int d)
{
	if(!u) u = ++ pid;
	t[u].v += d, t[u].l += d;
}
void pushdown(int u)
{
	if(t[u].l)
	{
		change(t[u].ls, t[u].l);
		change(t[u].rs, t[u].l);
		t[u].l = 0;
	}
}
void insert(int &u, int x, int d, int l = 1, int r = sx)
{
	if(!u) u = ++ pid;
	if(l == r)
	{
		t[u].v = max(t[u].v, d);
		return ;
	}
	pushdown(u);
	int mid = l + r >> 1;
	if(x <= mid) insert(t[u].ls, x, d, l, mid);
	else insert(t[u].rs, x, d, mid + 1, r);
	t[u].v = max(t[t[u].ls].v, t[t[u].rs].v);
}
void add(int &u, int x, int d, int l = 1, int r = sx)
{
	if(!u) u = ++ pid;
	if(l == r)
	{
		t[u].v += d;
		return ;
	}
	int mid = l + r >> 1;
	pushdown(u);
	if(mid < x) add(t[u].rs, x, d, mid + 1, r);
	else add(t[u].ls, x, d, l, mid), change(t[u].rs, d);
	t[u].v = max(t[t[u].ls].v, t[t[u].rs].v);
}
int query(int u, int x, int l = 1, int r = sx)
{
	if(!u) return 0;
	if(l == r) return t[u].v;
	pushdown(u);
	int mid = l + r >> 1;
	if(mid >= x) return query(t[u].ls, x, l, mid);
	else return max(query(t[u].rs, x, mid + 1, r), t[t[u].ls].v);
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++ )
	{
		scanf("%d%d%d%d", &a[i].l, &a[i].r, &a[i].c, &a[i].w);
		x[ ++ sx] = a[i].l;
		x[ ++ sx] = a[i].r;
		y[i] = a[i].c;
	}
	
	sort(x + 1, x + sx + 1);
	sx = unique(x + 1, x + sx + 1) - x - 1;
	sort(y + 1, y + n + 1);
	sy = unique(y + 1, y + n + 1) - y - 1;
	
	sort(a + 1, a + n + 1);
	for(int i = 1, j = 1; i <= n; i ++ )
	{
		int l = lower_bound(x + 1, x + sx + 1, a[i].l) - x;
		int r = lower_bound(x + 1, x + sx + 1, a[i].r) - x;
		int c = lower_bound(y + 1, y + sy + 1, a[i].c) - y;
		p[r].push_back(c);
		while(j < l)
		{
			for(auto k : p[j]) ff = max(ff, query(root[k], j));
			j ++ ;
		}
		rr = max(ff, query(root[c], r)) + a[i].w;
		insert(root[c], r, rr);
		if(r != sx) add(root[c], r + 1, a[i].w);
	}
	for(int i = 1; i <= sy; i ++ ) res = max(res, t[root[i]].v);
	
	printf("%d\n", res);
	return 0;
}
```

---

## 作者：by_chance (赞：3)

[Link](https://www.luogu.com.cn/problem/P9594)

考虑设计一个 DP。把所有线段按照某种顺序排序，然后定义 $dp_i$ 表示选择第 $i$ 条线段和前面的某些线段，权值和的最大可能值。

因为要求不同种类的线段不交，所以应该按照右端点递增排序，这样在线段 $i$ 之前，与线段 $i$ 不交的线段是一个前缀，便于维护。

对于与线段 $i$ 同种颜色的线段，假设左端点最左的是线段 $j$，那么显然应该选择所有完全落在区间 $[l_j,r_i]$ 内，与线段 $i$ 同色的线段。如果是暴力，可以直接枚举线段 $j$ 来处理。

考虑用线段树维护这些线段的权值和。我们把同种颜色的线段按照左端点递增排序，这样每次在 DP 中遇到一条线段，就只用对线段树进行一个区间加。另外，再在处理线段 $i$ 的时候，二分上一个满足 $r_k \lt l_i$ 的线段，把 $dp_k$ 加到线段树内线段 $i$ 的位置。最后每个 $dp_i$ 的确定都是线段树上一次区间询问。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,z[N];
struct line{int l,r,c,w;}x[N];
vector<line> a[N];
bool operator <(const line&a,const line&b){return a.l==b.l?a.r<b.r:a.l<b.l;}
bool cmp(line a,line b){return a.r==b.r?a.l>b.l:a.r<b.r;}
int st[N],tot;
map<line,int> mp[N];
namespace seg{
    #define ls p<<1
    #define rs p<<1|1
    #define mid ((l+r)>>1)
    int mx[N<<2],add[N<<2];
    void push_up(int p){mx[p]=max(mx[ls],mx[rs]);}
    void make_tag(int p,int v){add[p]+=v;mx[p]+=v;}
    void push_down(int p){make_tag(ls,add[p]);make_tag(rs,add[p]);add[p]=0;}
    void modify(int p,int l,int r,int L,int R,int v){
        if(l>=L&&r<=R){make_tag(p,v);return;}
        push_down(p);
        if(L<=mid)modify(ls,l,mid,L,R,v);
        if(R>mid)modify(rs,mid+1,r,L,R,v);
        push_up(p);
    }
    int query(int p,int l,int r,int L,int R){
        if(l>=L&&r<=R)return mx[p];;
        push_down(p);int res=0;
        if(L<=mid)res=max(res,query(ls,l,mid,L,R));
        if(R>mid)res=max(res,query(rs,mid+1,r,L,R));
        return res;
    }
    #undef ls 
    #undef rs
    #undef mid
}
int dp[N],mx[N];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d%d",&x[i].l,&x[i].r,&x[i].c,&x[i].w),z[i]=x[i].c;
    sort(z+1,z+n+1);m=unique(z+1,z+n+1)-z-1;
    for(int i=1;i<=n;i++){
        x[i].c=lower_bound(z+1,z+m+1,x[i].c)-z;
        a[x[i].c].push_back(x[i]);
    }
    for(int i=1;i<=m;i++){
        sort(a[i].begin(),a[i].end());st[i]=tot+1;
        for(int j=0;j<a[i].size();j++){
            if(j==0||a[i][j].l!=a[i][j-1].l||a[i][j].r!=a[i][j-1].r)
                mp[i][a[i][j]]=++tot,x[tot]=a[i][j];
            else x[tot].w+=a[i][j].w;
        }//这一步是把l,r,c都相等的线段合并了，其实没有什么必要
    }
    sort(x+1,x+tot+1,cmp);
    for(int i=1;i<=tot;i++){
        int L=1,R=i-1,pos=0;
        while(L<=R){
            int mid=L+R>>1;
            if(x[mid].r<x[i].l)pos=mid,L=mid+1;
            else R=mid-1;
        }
        int id=mp[x[i].c][x[i]];
        seg::modify(1,1,n,st[x[i].c],id,x[i].w);
        seg::modify(1,1,n,id,id,mx[pos]);
        dp[i]=seg::query(1,1,n,st[x[i].c],id);
        mx[i]=max(mx[i-1],dp[i]);
        // printf("%d %d %d %d %d\n",x[i].l,x[i].r,x[i].c,x[i].w,dp[i]);
    }
    printf("%d\n",mx[tot]);
    return 0;
}
```

---

## 作者：Po7ed (赞：3)

线段树优化 dp 好题！

### 思路

题目中的条件是 $c_i=c_j$（颜色相同）**或** $[l_i,r_i]\cap [l_j,r_j]=\varnothing$（不相交）。

可以先将线段按左端点排序，由于我们只关心颜色和相交情况，故可以设 $dp(r_i,c_i)$ 表示满足「选的线段中右端点最大的线段是 $i$，其右端点为 $r_i$ 颜色为 $c_i$」的权值和的最大值。

或是难以直接处理的，考虑拆成两种情况：必需满足颜色相同、必须满足不相交。

分别对应下面转移转移式中 $\max$ 的后两项：

$$
dp(r_i,c_i)\gets\max\left\{dp(r_i,c_i),\,{\color{red}w_i+\max_{j=1}^{r_i}dp(j,c_i)},\,{\color{blue}w_i+\max_k\max_{j=1}^{l_i-1}dp(j,k)}\right\}
\tag{1}
$$

但这样无法解决包含的情况，所以：

$$
\forall j>r_i,\,dp(j,c_i)\gets dp(j,c_i)+w_i
\tag{2}
$$

注意，$(2)$ 是在 $(1)$ 之前就完成了的。

不难发现 dp 的状态数是比较少的，只有 $O(m)$ 个，可以直接动态开点线段树维护。

$(1)$ 中红色转移、$(2)$ 中的转移都不困难，分别区间查最大值和区间加即可。但是 $(1)$ 中蓝色转移需要两层 $\max$，无法遍历所有颜色，需要记录新增哪些颜色，一一取 $\max$。具体可以看代码。

问：为什么是按左端点排序？能按右端点排序吗？

答：因为左端点排序才能在可接受复杂度内完成蓝色转移，按右端点排序无法实现。

### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
typedef long long ll;
constexpr int N=114514,M=N<<2;
int n;
struct inr{int l,r,c,w;};
inline bool operator < (inr u,inr v){return u.l==v.l?u.r<v.r:u.l<v.l;}
// inline bool cmp(inr x,inr y){return x.c==y.c?x.r<y.r:x.c<y.c;}
inr a[N];

template<typename T>
void get_max(T &x,T y){x=std::max(x,y);}

struct node{int ls,rs,max,tag;};
node t[int(2e7)];
int nodecnt;
int new_node(){return ++nodecnt;}
struct sgt // to dp
{
#define now (t[pos])
#define mid ((l+r)>>1)
	int rt;
	// void init(){rt=new_node();}
	void mktag(int pos,int mv){pos&&(now.tag+=mv,now.max+=mv);}
	void pdtag(int pos){(pos&&now.tag)&&(mktag(now.ls,now.tag),mktag(now.rs,now.tag),now.tag=0);}
	void modify(int mp,int mv,int l,int r,int &pos)
	{
		if(!pos)pos=new_node();
		if(l==r)return void(get_max(now.max,mv));
		pdtag(pos);
		if(mp<=mid)modify(mp,mv,l,mid,now.ls);
		else modify(mp,mv,mid+1,r,now.rs);
		now.max=std::max(t[now.ls].max,t[now.rs].max);
	}
	int query(int ql,int qr,int l,int r,int &pos)
	{
		if(qr<ql)return 0;
		if(!pos)pos=new_node();
		if(ql<=l&&r<=qr)return now.max;
		pdtag(pos);
		if(qr<=mid)return query(ql,qr,l,mid,now.ls);
		if(mid<ql)return query(ql,qr,mid+1,r,now.rs);
		return std::max(query(ql,qr,l,mid,now.ls),query(ql,qr,mid+1,r,now.rs));
	}
	void modify(int ml,int mr,int mv,int l,int r,int &pos)
	{
		if(mr<ml)return;
		if(!pos)pos=new_node();
		if(ml<=l&&r<=mr)return mktag(pos,mv);
		pdtag(pos);
		if(ml<=mid)modify(ml,mr,mv,l,mid,now.ls);
		if(mid<mr)modify(ml,mr,mv,mid+1,r,now.rs);
		now.max=std::max(t[now.ls].max,t[now.rs].max);
	}
#undef now
#undef l
#undef r
};
sgt dp[M];
std::vector<int> cs,es,ep[M];

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].l>>a[i].r>>a[i].c>>a[i].w;
		cs.push_back(a[i].c);
		es.push_back(a[i].l);
		es.push_back(a[i].r);
	}
	std::sort(cs.begin(),cs.end());
	cs.resize(std::unique(cs.begin(),cs.end())-cs.begin());
	std::sort(es.begin(),es.end());
	es.resize(std::unique(es.begin(),es.end())-es.begin());
	for(int i=1;i<=n;i++)
	{
		a[i].l=std::lower_bound(es.begin(),es.end(),a[i].l)-es.begin()+1;
		a[i].r=std::lower_bound(es.begin(),es.end(),a[i].r)-es.begin()+1;
		a[i].c=std::lower_bound(cs.begin(),cs.end(),a[i].c)-cs.begin()+1;
		// if(!dp[a[i].c].rt)dp[a[i].c].init();
	}
	std::sort(a+1,a+n+1);
	int ans=0;
	for(int i=1,j=1,pre=0,tmp;i<=n;i++)
	{
		ep[a[i].r].push_back(a[i].c); // 缓存颜色
		for(;j<a[i].l;j++) // 取 max（蓝色）
		{
			for(int c:ep[j])
			{
				get_max(pre,dp[c].query(1,a[i].l-1,1,es.size(),dp[c].rt));
			}
		}
		tmp=std::max(pre,dp[a[i].c].query(1,a[i].r,1,es.size(),dp[a[i].c].rt))+a[i].w;
		get_max(ans,tmp);
		dp[a[i].c].modify(a[i].r,tmp,1,es.size(),dp[a[i].c].rt);
		dp[a[i].c].modify(a[i].r+1,es.size(),a[i].w,1,es.size(),dp[a[i].c].rt);
		get_max(ans,t[dp[a[i].c].rt].max);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：dengjunhaodejia09 (赞：1)

这道题我想了一堆伪算，下面是思路与代码。

首先，这道题类似于动态规划，因为很多类似的都可以用数据结构优化动态规划解决。而这道题对顺序无要求，我们就要自己排序规定顺序。

首先看以右端点排序，此时若是当前区间包含另两区间，且这两区间颜色不同且无交，当前区间与后一区间颜色相同，就会出现问题。可自己画图理解。

发现包含且颜色相同不好处理，但由题目可得，颜色相同且包含是肯定会选的，可从这里入手。

我们考虑按右端点排序，对于不相交的区间，当然是直接转移即可，注意此时要加上完全包含且颜色相同的区间。对于相交颜色相同但不包含的区间，加上中间部分颜色相同且包含的区间便是正确的转移。完美考虑了包含的情况。

并，建议升紫。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,c,w,lsh[200005],tot,res,dp[200005];
map<int,int>id;
struct node{
    int l,r,c,w;
}a[100005];
inline bool cmp(node x,node y){
    if(x.r==y.r){
        return x.l>y.l;
    }
    return x.r<y.r;
}
int cnt,tree[10000007],lson[10000007],rson[10000007],vis[10000007],root1[200005],root2[200005];
void push_down(int id){
    if(lson[id]==0){
        lson[id]=++cnt;
    }
    if(rson[id]==0){
        rson[id]=++cnt;
    }
    tree[lson[id]]+=vis[id];
    tree[rson[id]]+=vis[id];
    vis[lson[id]]+=vis[id];
    vis[rson[id]]+=vis[id];
    vis[id]=0;
}
void insertt(int id,int l,int r,int W,int Ans){
    if(l==r){
        tree[id]=max(tree[id],Ans);
        return;
    }
    int mid=(l+r)/2;
    push_down(id);
    if(W<=mid){
        if(lson[id]==0){
            lson[id]=++cnt;
        }
        insertt(lson[id],l,mid,W,Ans);
    }else{
        if(rson[id]==0){
            rson[id]=++cnt;
        }
        insertt(rson[id],mid+1,r,W,Ans);
    }
    tree[id]=tree[lson[id]]+tree[rson[id]];
}
void insert(int id,int l,int r,int W,int Ans){
    if(l==r){
        tree[id]=max(tree[id],Ans);
        return;
    }
    int mid=(l+r)/2;
    push_down(id);
    if(W<=mid){
        if(lson[id]==0){
            lson[id]=++cnt;
        }
        insert(lson[id],l,mid,W,Ans);
    }else{
        if(rson[id]==0){
            rson[id]=++cnt;
        }
        insert(rson[id],mid+1,r,W,Ans);
    }
    tree[id]=max(tree[lson[id]],tree[rson[id]]);
}
void change(int id,int l,int r,int L,int R,int W){
    if(L<=l && r<=R){
        vis[id]+=W;
        tree[id]+=W;
        return;
    }
    push_down(id);
    int mid=(l+r)/2;
    if(R<=mid){
        if(lson[id]==0){
            lson[id]=++cnt;
        }
        change(lson[id],l,mid,L,R,W);
    }else if(L>mid){
        if(rson[id]==0){
            rson[id]=++cnt;
        }
        change(rson[id],mid+1,r,L,R,W);
    }else{
        if(lson[id]==0){
            lson[id]=++cnt;
        }
        change(lson[id],l,mid,L,R,W);
        if(rson[id]==0){
            rson[id]=++cnt;
        }
        change(rson[id],mid+1,r,L,R,W);
    }
    tree[id]=max(tree[lson[id]],tree[rson[id]]);
}
int queryy(int id,int l,int r,int L,int R){
    if(id==0){
        return 0;
    }
    if(L<=l && r<=R){
        return tree[id];
    }
    push_down(id);
    int mid=(l+r)/2;
    if(R<=mid){
        return queryy(lson[id],l,mid,L,R);
    }else if(L>mid){
        return queryy(rson[id],mid+1,r,L,R);
    }else{
        return queryy(lson[id],l,mid,L,R)+queryy(rson[id],mid+1,r,L,R);
    }
}
int query(int id,int l,int r,int L,int R){
    if(id==0){
        return 0;
    }
    if(L<=l && r<=R){
        return tree[id];
    }
    push_down(id);
    int mid=(l+r)/2;
    if(R<=mid){
        return query(lson[id],l,mid,L,R);
    }else if(L>mid){
        return query(rson[id],mid+1,r,L,R);
    }else{
        return max(query(lson[id],l,mid,L,R),query(rson[id],mid+1,r,L,R));
    }
}
int xds[100005];
int Max=0;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>l>>r>>c>>w;
        if(!id[c])id[c]=++cnt;
        c=id[c];
        a[i]={l,r,c,w};
        lsh[++tot]=l,lsh[++tot]=r;
    }
    sort(lsh+1,lsh+1+tot);
    tot=unique(lsh+1,lsh+1+tot)-lsh-1;
    for(int i=1;i<=n;i++){
        a[i].l=lower_bound(lsh+1,lsh+1+tot,a[i].l)-lsh;
        a[i].r=lower_bound(lsh+1,lsh+1+tot,a[i].r)-lsh;
        Max=max(Max,a[i].r);
    }
    sort(a+1,a+1+n,cmp);
    cnt=0;
    // for(rint i=1;i<=n;i++)cerr<<a[i].l<<" "<<a[i].r<<" "<<a[i].c<<" "<<a[i].w<<"\n";
    for(int i=1;i<=n;i++){
        int Ans=queryy(root1[a[i].c],1,Max,a[i].l,a[i].r);
        // int Ans=0;
        // for(int j=1;j<i;j++){
        //     if(a[i].l<=a[j].l && a[j].r<=a[i].r && a[j].c==a[i].c){
        //         Ans+=a[j].w;
        //     }
        // }
        dp[i]=a[i].w+Ans;
        if(a[i].l-1>=1){
            dp[i]=max(dp[i],query(root2[a[i].c],1,Max,1,a[i].l-1)+a[i].w);
            dp[i]=max(dp[i],query(root2[0],1,Max,1,a[i].l-1)+Ans+a[i].w);
        }
        if(root2[a[i].c]==0){
            root2[a[i].c]=++cnt;
        }
        change(root2[a[i].c],1,Max,1,a[i].l,a[i].w);
        insert(root2[a[i].c],1,Max,a[i].l,dp[i]);
        if(root2[0]==0){
            root2[0]=++cnt;
        }
        insert(root2[0],1,Max,a[i].r,dp[i]);
        // for(int j=1;j<i;j++){
        //     if(a[i].c==a[j].c && a[i].l>a[j].l){
        //         dp[i]=max(xds[j]+a[i].w,dp[i]);
        //     }
        //     if(a[j].r<a[i].l){
        //         dp[i]=max(dp[j]+a[i].w+Ans,dp[i]);
        //     }
        // }
        // xds[i]=dp[i];
        // for(int j=1;j<i;j++){
        //     if(a[j].l<=a[i].l && a[j].c==a[i].c){
        //         xds[j]+=a[i].w;
        //     }
        // }
        res=max(res,dp[i]);
        if(root1[a[i].c]==0){
            root1[a[i].c]=++cnt;
        }
        int Num=queryy(root1[a[i].c],1,Max,a[i].l,a[i].l);
        insertt(root1[a[i].c],1,Max,a[i].l,Num+a[i].w);
    }
    cout<<res<<"\n";

    return 0;
}
```

---

