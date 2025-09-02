# Complicated Computations

## 题目描述

In this problem MEX of a certain array is the smallest positive integer not contained in this array.

Everyone knows this definition, including Lesha. But Lesha loves MEX, so he comes up with a new problem involving MEX every day, including today.

You are given an array $ a $ of length $ n $ . Lesha considers all the non-empty subarrays of the initial array and computes MEX for each of them. Then Lesha computes MEX of the obtained numbers.

An array $ b $ is a subarray of an array $ a $ , if $ b $ can be obtained from $ a $ by deletion of several (possible none or all) elements from the beginning and several (possibly none or all) elements from the end. In particular, an array is a subarray of itself.

Lesha understands that the problem is very interesting this time, but he doesn't know how to solve it. Help him and find the MEX of MEXes of all the subarrays!

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 4 3 1 2```

### 输出

```
6```

# 题解

## 作者：Werner_Yin (赞：26)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/-solution-CF-1436E.html)
# Problem

给定一个长度为 $n(n \leq 10^5)$ 的数组，求出它所有子数组 $MEX$  的 $MEX$ 。

这里的$MEX$ 定义为一个数组中第一个没有出现的 **正整数**。

# Solution

考场没有想出来，自闭了。

我们考虑是否存在一个子数组，满足其$MEX=a$ ，首先，这个子数组里面必须要没有 $a$ ，

于是我们首先把数组中所有的 $a$ 找出来，这些 $a$ 把数组分成了若干段，我们要的子数组必须不能跨越这些段。

其次，对于这些段中，如果所有小于$a-1$的数都在里面，那么这一段一定满足$MEX=a$ （因为里面没有$a$）。

可以结合一下图理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/ymw3lx2g.png)


我们可以用线段树维护，具体细节见代码。

# Code

```cpp
const int MAXN = 1e5+10;

int val[MAXN<<2],lst[MAXN],a[MAXN],n;
bool able[MAXN];

//这个线段树维护的是每个数最后出现的位置

void update(int o,int l,int r,int pos,int v){
	if(l == r) return (void)(val[o] = v);
	int mid = l+r>>1;
	if(pos <= mid) update(o<<1,l,mid,pos,v);
	else update(o<<1|1,mid+1,r,pos,v);
	val[o] = min(val[o<<1],val[o<<1|1]);
}//更新区间最小值

int query(int o,int l,int r,int xl,int xr){
	if(l == xl && r == xr) return val[o];
	int mid = l+r>>1;
	if(xr <= mid) return query(o<<1,l,mid,xl,xr);
	else if(xl > mid) return query(o<<1|1,mid+1,r,xl,xr);
	else return min(query(o<<1,l,mid,xl,mid),query(o<<1|1,mid+1,r,mid+1,xr));
}//查询区间最小值

int main (){//lst[i] i 上一次出现的位置
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	for(int i = 1;i <= n;i++){
		if(a[i] != 1) able[1] = 1;//注意对1的特判
		if(a[i] > 1  && query(1,1,n,1,a[i]-1) > lst[a[i]]) able[a[i]] = 1;
      //对段进行分割处理（lst[a[i]] ~ i) ，如果 1~a[i]-1 的数最后出现的位置都 > lst[a[i]] 且 < i(因为后面的还没更新，所以必定 < i) ,那么这一段满足MEX = a[i]
		lst[a[i]] = i;
		update(1,1,n,a[i],i);
	}
	for(int i = 2;i <= n+1;i++) if(query(1,1,n,1,i-1) > lst[i]) able[i] = 1;
  //因为lst[i] 初始为0，所以之前我们处理了 1～i 最先出现的位置的段，但是没有处理 lst[i] ~ 结尾 的段，这里在处理一遍
	int ans = 1;
	for(;able[ans] && ans <= n+1;ans++);
  //查找答案，注意ans 上界实际上为 n+2
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：SSerxhs (赞：12)

考虑依次判断 $i$ 是否出现在子序列 mex 中，显然 $i$ 能出现当且仅当存在两个相邻的 $i$ 使得他们之间的区间 mex 为 $i$

由于相邻的 $i$ 总计只有 $O(n)$ 组，题目可以转化为 $n$ 组询问区间 mex

这是个经典问题，可以离线莫队处理。注意要使用值域分块

---

## 作者：275307894a (赞：5)

[题面传送门](https://www.luogu.com.cn/problem/CF1436E)

首先考虑一个结论:将一个区间中的数去重后这个区间$mex$没有影响。

所以我们只要求出那些$mex$中有几个数。

一个区间$mex=k$的条件是区间没有$k$且区间有$1$到$k-1$。

考虑对于同样的数分段。

那么对于每个段这样查询即可。

即满足两个条件:$[l\leq i \leq r]$和所有不同的$1\sim k-1$种类等于$k-1$。

如果直接像$HH的项链$那样那就要二维树状数组维护要两个$log$。

转化一下，则就是判断$1 \sim k-1$中最小的出现的位置是否小于$l$。

那么就可以复杂度$O(nlogn)$。

代码实现：
```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
int n,m,k,x,y,z,ans[100039],a[100039],pus,maxn;
int last[100039],f[400039],g[100039];
inline void get(int x,int z,int l,int r,int now){
	if(l==r){f[now]=z;return;}
	int m=(l+r)>>1;
	if(x<=m) get(x,z,l,m,now<<1);
	else get(x,z,m+1,r,now<<1|1);
	f[now]=min(f[now<<1],f[now<<1|1]);
}
inline int find(int x,int y,int l,int r,int now){
	if(x<=l&&r<=y) return f[now];
	int m=(l+r)>>1,fs1=1e9,fs2=1e9;
	if(x<=m) fs1=find(x,y,l,m,now<<1);
	if(y>m)fs2=find(x,y,m+1,r,now<<1|1);
	return min(fs1,fs2);
}
int main(){
//	freopen("1.in","r",stdin);
	register int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]),maxn=max(maxn,a[i]),ans[1]|=(a[i]!=1?1:0),ans[2]|=(a[i]==1?1:0);
	for(i=1;i<=n;i++){
		g[i]=last[a[i]];
		last[a[i]]=i;
	}
	for(i=1;i<=n;i++){
		get(a[i],i,1,n+1,1);
		if(a[i]!=1){
			pus=find(1,a[i]-1,1,n+1,1);
			//printf("%d %d\n",a[i],pus);
			if(pus>g[i]) ans[a[i]]=1; 
		}
	}
	for(i=2;i<=maxn+1;i++){
	//	printf("%d %d\n",i,find(1,i-1,1,n+1,1));
		if(find(1,i-1,1,n+1,1)>last[i]) ans[i]=1;
	}
	for(i=1;i<=n+2;i++) if(!ans[i]){printf("%d\n",i);return 0;}
}
```

---

## 作者：_Felix (赞：4)

题意：

n个数，对所有子区间求mex，

把答案组成新的一列数，再求mex。

分析：

先加入数值 $∈[1,i]$ 的数，

然后查询是否存在符合条件的区间有i-1个种数。


条件：“两个为i的数之间”或“到a[i]的前缀”
或“从a[i]到结尾”

（有i-1种，说明有连续[1,i-1]，mex可能是i，不可能是答案）。

---

用线段树解决。

t[x]保存的是x最后一次出现的地方，线段树维护区间最小值。

扫到a[i]的时候，设m为[1,a[i]-1]中，出现最早的数所在的位置。


如果m>上一个a[i]出现的位置，

就说明存在两个为a[i]的数之间有a[i]-1个数，mex可以为a[i]。

这样就解决了。

```
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define rd(x) scanf("%d",&x);
typedef long long LL;
const int N=1e5+10;
int n,a[N],t[N<<2],las[N],f[N]; 
void pushup(int rt){ t[rt]=min(t[rt<<1],t[rt<<1|1]); }
int query(int rt,int l,int r,int L,int R){
//	cout<<rt<<" "<<l<<" "<<r<<" "<<L<<" "<<R<<endl;
	if(l>R||r<L) return 1e9;
	if(L<=l&&r<=R){
	//	cout<<rt<<"*"<<t[rt]<<endl;
		return t[rt];
	}
	int mid=l+r>>1;
	return min(query(rt<<1,l,mid,L,R),query(rt<<1|1,mid+1,r,L,R));
}
void update(int rt,int l,int r,int x,int val){
//	cout<<rt<<"*"<<l<<" "<<r<<" "<<x<<" "<<val<<endl;
	if(x<l||x>r) return;
	if(l==r) { t[rt]=val; return; }
	int mid=l+r>>1;
	update(rt<<1,l,mid,x,val);
	update(rt<<1|1,mid+1,r,x,val);
	pushup(rt);
	return;
}
int main(){
	rd(n);
	rep(i,1,n){
		rd(a[i]);
		int x=0; if(a[i]!=1) x=query(1,1,n,1,a[i]-1);
	//	cout<<a[i]<<" "<<x<<endl;
        //[1,a[i]-1]中最早出现的数(每次维护的都是每个数最晚出现的地点)晚于于lst[a[i]]
		//两个a[i]之间有集齐i-1个
		// 存在mex为a[i]的子区间
		if(x>las[a[i]]) f[a[i]]=1;
		update(1,1,n,a[i],i);las[a[i]]=i;
	}
	rep(i,2,n+1){
		int x=query(1,1,n,1,i-1);
		if(x>las[i]) f[i]=1;
	}//结尾再统计一次 
	rep(i,1,n) if(a[i]!=1) f[1]=1;
	int i=1;
	while(1){
		if(f[i]==0){
			printf("%d\n",i);
			return 0;
		}
		i++;
	}
	return 0;
}

```

---

## 作者：MatrixCascade (赞：3)

求解 mex 是莫队常见套路吧。

考虑到这题没有询问，我们就尝试构造一些询问给他。

于是就可以按照相邻的 i 分段，假设 i 这个数的出现位置是 $p_1,p_2,...,p_k$，于是询问就是这样的:$1\to p_1-1,p_1+1\to p_2-1,...,p_k+1\to n$

对于每个数 i 都这么分段，如果区间不够长就直接舍弃了，不要放进询问中，所有区间最多 $O(n)$ 个。

然后就可以莫队维护了，每次移动完统计 $1\to i-1$ 是否都出现过。偷懒写了个树状数组多一个 log，但是常数挺小可以过。

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define clr(f, n) memset(f, 0, sizeof(int) * (n))
#define cpy(f, g, n) memcpy(f, g, sizeof(int) * (n))
#define rev(f, n) reverse(f, f + n)
#define pir pair<int, int>
#define mkp make_pair
#define fst it->first
#define sec it->second
#define int long long
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define down(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
inline void print(int *f, int len)
{
    for (int i = 0; i < len; i++)
        printf("%lld ", f[i]);
    puts("");
}
const int maxn=2e5+10;
int a[maxn];
vector<int>v[maxn];
int bl[maxn],f[maxn],blo,tot=0;
int w[maxn];
int lowbit(int x){return x&(-x);}
void upt(int x,int y)
{
	for(int i=x;i<=n;i+=lowbit(i))w[i]+=y;
}
int qry(int x)
{
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i))ans+=w[i];
	return ans;
}
struct node
{
	int l,r,id;
	node(int ll=0,int rr=0,int idid=0){l=ll,r=rr,id=idid;}
}q[maxn];
bool cmp(node x,node y)
{
    if(bl[x.l]!=bl[y.l])
        return bl[x.l]<bl[y.l];
    else
        return x.r<y.r;
}int tim[maxn];
void add(int x)
{
	++tim[x];
	if(tim[x]==1)upt(x,1);
}
void del(int x)
{
	--tim[x];
	if(tim[x]==0)upt(x,-1);
}
int query(int x)
{
	int a=qry(x);
	if(a==x-1)return 1;
	return 0;
}
signed main()
{
	n=read();
	blo=sqrt(n);
	up(i,1,n){a[i]=read();v[a[i]].push_back(i);if(a[i]>1)f[1]=1;}
	up(i,1,maxn-10)bl[i]=(i-1)/blo+1;
	up(i,2,n+1)
	{
		int ql=1,qr;
		for(auto x:v[i])
		{
			qr=x-1;
		//	cout<<qr<<endl;
			
			if(qr-ql+1>=i-1)q[++tot]=node(ql,qr,i);
			ql=x+1;
		}
		qr=n;
		if(qr-ql+1>=i-1)q[++tot]=node(ql,qr,i);
	}
	sort(q+1,q+tot+1,cmp);
	reverse(q+1,q+tot+1);
	int l=1,r=0;
	up(i,1,tot)
	{
		if(f[q[i].id])continue;
		while(l>q[i].l)
		{
			add(a[--l]);
		}
		while(l<q[i].l)
		{
			del(a[l++]);
		}
		while(r>q[i].r)
		{
			del(a[r--]);
		}
		while(r<q[i].r)
		{
			add(a[++r]);
		}
		f[q[i].id]=query(q[i].id);
	}
	up(i,1,n+1)
	{
		if(!f[i])
		{
			cout<<i;
			return 0;
		}
	}
	cout<<n+2;
}

```


---

## 作者：Arghariza (赞：2)

没看到有人写树套树做法，个人认为这个做法还是比较自然的。

考虑到一个序列的 $\text{mex}$ 为 $i$，当且仅当出现了 $1\to i-1$ 并且没有 $i$。

我们可以从小到大枚举答案 $i$，那么必须不包含 $\text{mex}$ 为 $i$ 的子段。

一个简单的想法是找出每个 $i$ 出现的位置，这些位置把整个数列分成了若干段。记 $p_i$ 表示 $a_i$ 上次出现位置（如果没有则为 $0$）。对于一段 $[l,r]$（不包含 $a_j$ 为 $i$ 的端点 $j$），如果其 $\text{mex}$ 为 $i$，说明：$\sum\limits_{l\le j\le r}[p_j<l\ \text{and}\ a_j\le i-1]$ 的值为 $i-1$。

乍一看好像是三维数点。但是既然我们是从小到大枚举 $i$，那么也可以从小到大把 $a_j=i$ 的值加入数组，于是我们去掉了第二个限制，于是变成一个二维数点，既然是动态加点，树套树维护即可。

好像分块套树状数组很快，但是这题并不卡常，所以写了树状数组套线段树。复杂度 $O(n\log^2 n)$，需要特判全是 $1$ 的情况。

```cpp
const int maxn = 1e5 + 100;
struct seg { int lc, rc, vl; } tr[maxn * 100];
int n, tot, a[maxn], lst[maxn], pos[maxn], rt[maxn];

#define ls tr[x].lc
#define rs tr[x].rc
#define mid ((l + r) >> 1)
void update(int l, int r, int p, int &x) {
	if (!x) x = ++tot;
	tr[x].vl++;
	if (l == r) return;
	if (p <= mid) update(l, mid, p, ls);
	else update(mid + 1, r, p, rs);
} 

int query(int l, int r, int s, int t, int x) {
	if (!x) return 0;
	if (s <= l && r <= t) return tr[x].vl;
	int res = 0;
	if (s <= mid) res += query(l, mid, s, t, ls);
	if (t > mid) res += query(mid + 1, r, s, t, rs);
	return res;
}

int lb(int x) { return x & (-x); }
void upd(int x, int y) { x++; for (int i = x; i <= n + 1; i += lb(i)) update(1, n, y, rt[i]); }
int qry(int x, int l, int r) { if (r < l) return 0; x++; int res = 0; for (int i = x; i; i -= lb(i)) res += query(1, n, l, r, rt[i]); return res; } 

int main() {
	n = read();
	int flg = 0;
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		if (a[i] != 1) flg = 1;
	}
	if (!flg) return puts("1"), 0;
	for (int i = 1; i <= n; i++) 
		lst[i] = pos[a[i]], pos[a[i]] = i;
	for (int i = 1; i <= n + 1; i++) {
		if (!pos[i]) {
			if (qry(0, 1, n) == i - 1) continue;
			return write(i), 0;
		}
		int fl = 0;
		if (pos[i] < n) 
			if (qry(pos[i], pos[i] + 1, n) == i - 1) fl = 1;
		for (int j = pos[i]; j; j = lst[j]) {
			if (qry(lst[j], lst[j] + 1, j - 1) == i - 1) fl = 1;
			upd(lst[j], j);
		}
		if (!fl) return write(i), 0;
	}
	write(n + 2);
	return 0;
}

```

---

## 作者：UperFicial (赞：2)

> [**CF1436E Complicated Computations**](https://www.luogu.com.cn/problem/CF1436E)

> 解题报告。

> [**不一定更好的阅读体验**](https://www.cnblogs.com/UperFicial/p/16733491.html)。

对于一个数 $x$，考虑什么条件 $x$ 可以作为答案。

首先要满足 $\forall y\in [1,x)$，$y$ 都不能作为答案，因为最终我们是取的 mex。

其次，原序列任何一个连续子序列的 mex 都不可能为 $x$。

第一个条件我们只需要顺着枚举 $x$ 即可，考虑如何解决第二个条件限制。

我们把 $x$ 在原序列出现的位置都提出来，这样会把原序列分割成若干不包含 $x$ 的极长子区间。

任何一个包含 $x$ 的子区间的 mex 都不可能为 $x$，所以我们只需要检查分割出来的所有子区间中是否存在一个区间的 mex 是 $x$，只要有就不合法。

对于每一个 $x$ 这些子区间显然是可以暴力处理的出来的，因为区间总数是不超过 $O(n)$ 个的。

于是现在就变成区间求 mex 的问题，可以考虑可持久化权值线段树，

具体的，对于一个询问区间 $[l,r]$，我们提出以 $[1,r]$ 这个序列建出的的权值线段树，维护每一个数最后出现的位置，若一个数最后出现的位置小于 $l$，说明这个数可能作为 mex，而真正的 mex 是这些数的 $\min$。

这就典了啊，线段树上二分乱杀即可。优先走左子树，然后走右子树。

时间复杂度 $\Theta(n\log n)$，比莫队套值域分块快多了。

代码（自认为写得比较好看）：

```cpp
const int MAXN(1e5+10);

int n,m,a[MAXN];
bool flag[MAXN];

vector<int>G[MAXN];
struct node{int l,r,v;};
node q[MAXN<<1];


inline void newquery(int l,int r,int v){if(l>r)return;q[++m].l=l;q[m].r=r,q[m].v=v;return;}
inline bool cmp(node x,node y){return x.r<y.r;}

int rt[MAXN];

struct Segment_Tree
{
	struct T{int ls,rs,val;};
	T tree[MAXN*30];
	int tot;

	inline int lc(int u){return tree[u].ls;}
	inline int rc(int u){return tree[u].rs;}

	inline void push_up(int u)
	{
		tree[u].val=Min(tree[tree[u].ls].val,tree[tree[u].rs].val);
		return;
	}

	inline void update(int&u,int pre,int l,int r,int p,int k)
	{
		u=++tot;
		tree[u]=tree[pre];
		if(l==r)
		{
			tree[u].val=k;
			return;
		}
		int mid=(l+r)>>1;
		if(p<=mid) update(tree[u].ls,tree[pre].ls,l,mid,p,k);
		else update(tree[u].rs,tree[pre].rs,mid+1,r,p,k);
		push_up(u);
		return;
	}

	inline int query(int u,int l,int r,int L)
	{
		if(l==r) return l;
		int mid=(l+r)>>1;
		if(tree[lc(u)].val<L) return query(lc(u),l,mid,L);
		else return query(rc(u),mid+1,r,L);
	}
};
Segment_Tree seg;

int main()
{
	n=read();
	rep(i,1,n) a[i]=read(),G[a[i]].push_back(i);
	rep(i,1,n)
	{
		rep(j,0,(int)G[i].size()-1)
		{
			if(j==0) newquery(1,G[i][j]-1,i);
			else newquery(G[i][j-1]+1,G[i][j]-1,i);
		}
		if(G[i].size()) newquery(G[i][G[i].size()-1]+1,n,i);
	}
	rep(i,1,n)
		seg.update(rt[i],rt[i-1],1,n+1,a[i],i);
	rt[n+1]=rt[n];
	rep(i,1,m)
	{
		int l=q[i].l,r=q[i].r,v=q[i].v;
		if(seg.query(rt[r],1,n+1,l)==v) flag[v]=true; 
	}
	rep(i,1,n+2) if(seg.query(rt[n+1],1,n+1,1)==i) flag[i]=true;
	rep(i,1,n+2) if(!flag[i])
	{
		printf("%d\n",i);
		return 0;
	}
    return 0;
}
/*
Date : 2022/9/27
Author : UperFicial
Start coding at : 7:05
finish debugging at : 9:34
*/
```

---

## 作者：duyi (赞：2)

# 题解 CF1436E Complicated Computations

[题目链接](https://codeforces.com/contest/1436/problem/E)

从小到大依次枚举每个正整数，看能否作为答案。一个数 $x$ 能作为答案的条件是：

1. 比它小的值都不是答案。
2. 不存在一个区间 $[l,r]$，使得 $\text{mex}(a_l,a_{l+1},\dots,a_r) = x$。

因为是从小到大枚举的，所以只要我们一找到答案就退出，那条件 1 就已经解决了。

考虑条件 2。如何判断是否存在一个区间，使得 $\text{mex}(a_l,a_{l+1},\dots,a_r) = x$ 呢？

- 首先，$x$ 不能在这个区间里出现过。记 $x$ 在整个序列里出现的位置分别为 $p_1,p_2,\dots,p_k$，这些点把整个序列划分为了不超过 $k+1$ 个线段。那 $[l,r]$ 一定被完全包含在某个线段中。
- 其次，所有小于 $x$ 的正整数都必须在区间 $[l,r]$ 里出现过。那么我们肯定希望在满足上一条的同时，让区间 $[l,r]$ 尽量长（这样更有可能包含到所有值）。所以如果存在合法的 $[l,r]$，那也一定存在某个完整的线段是合法的。于是我们只需要对这 $k+1$ 个线段进行判断即可。

问题转化为，对这 $k+1$ 个线段，分别判断“所有小于 $x$ 的正整数是否都在里面出现过”。也就是对它们求 $\text{mex}$。

注意到，对于所有 $x$，线段的总数（也就是 $\sum(k+1)$）只有 $O(n)$ 个。

---

求区间 $\text{mex}$ 有一个经典的莫队做法。具体来说，我们先将这 $O(n)$ 个要查询的区间离线下来。然后做莫队。需要支持每次插入 / 删除一个数，求当前集合的 $\text{mex}$。

第一反应是在值域上建一棵线段树。但是这样插入 / 删除操作就是 $O(\log n)$ 的了，总时间复杂度 $O(n\sqrt{n}\log n)$。事实上，发现我们需要的修改次数很多（$O(n\sqrt{n})$ 次），但查询次数较少（$O(n)$ 次）。而线段树恰恰是修改较慢（$O(\log n)$），查询较快（因为是全局查询，直接回答根节点信息，是 $O(1)$ 的）。所以我们在这里用一个“根号平衡”，即用分块，牺牲查询的复杂度，实现较快的修改。具体来说，我们对值域分块，维护每个块内有几个出现次数非零的值。修改是单点修改，可以 $O(1)$ 完成。查询时，从小到大暴力枚举每个块，遇到第一个没有满的块，就在这个块里暴力找到答案。这样查询是 $O(\sqrt{n})$ 的。

总时间复杂度 $O(n\sqrt{n})$。

参考代码：

```cpp
// problem: CF1436E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1e5;
const int MAXM = MAXN * 2; // 考虑妙妙的常数
const int BLOCK_SIZE = 300, BLOCK_NUM = MAXN / BLOCK_SIZE + 10;

int n, a[MAXN + 5];
int st[BLOCK_NUM + 5], ed[BLOCK_NUM + 5], bel[MAXN + 5], cnt_block;
vector<int> vec[MAXN + 5];
vector<int> qid[MAXN + 5];
int ans[MAXM + 5], cntq;
struct Query_t {
	int l, r, id;
	Query_t(int _l, int _r, int _id) { l = _l; r = _r; id = _id; }
	Query_t() {}
}q[MAXM + 5];
bool cmp(Query_t lhs, Query_t rhs) {
	return (bel[lhs.l] == bel[rhs.l]) ? (lhs.r < rhs.r) : (lhs.l < rhs.l);
}

int buc[MAXN + 5], nemp[BLOCK_NUM + 5]; // nemp: not empty 块里非空的桶有几个
void modify(int p, int v) {
	if (buc[p]) nemp[bel[p]]--;
	buc[p] += v;
	if (buc[p]) nemp[bel[p]]++;
}
int get_mex() {
	for (int i = 1; i <= cnt_block; ++i) {
		if (nemp[i] == ed[i] - st[i] + 1)
			continue; // 全满了
		for (int j = st[i]; j <= ed[i]; ++j) {
			if (!buc[j])
				return j;
		}
		assert(0);
	}
	return n + 1;
}

int curl, curr;
void movel(int t) {
	if (t == 1) {
		// l 右移, 删数
		modify(a[curl], -1);
		++curl;
	} else {
		// l 左移, 加数
		--curl;
		modify(a[curl], 1);
	}
}
void mover(int t) {
	if (t == 1) {
		// r 右移, 加数
		++curr;
		modify(a[curr], 1);
	} else {
		// r 左移, 删数
		modify(a[curr], -1);
		curr--;
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		vec[a[i]].pb(i);
	}
	for (int i = 1; i <= n; i += BLOCK_SIZE) {
		int j = min(n, i + BLOCK_SIZE - 1);
		++cnt_block;
		st[cnt_block] = i;
		ed[cnt_block] = j;
		for (int k = i; k <= j; ++k) {
			bel[k] = cnt_block;
		}
	}
	for (int i = 1; i <= n + 1; ++i) {
		if (!SZ(vec[i])) {
			++cntq;
			q[cntq] = Query_t(1, n, cntq);
			qid[i].pb(cntq);
		} else {
			if (vec[i][0] != 1) {
				++cntq;
				q[cntq] = Query_t(1, vec[i][0] - 1, cntq);
				qid[i].pb(cntq);
			}
			for (int j = 1; j < SZ(vec[i]); ++j) {
				if (vec[i][j] != vec[i][j - 1] + 1) {
					++cntq;
					q[cntq] = Query_t(vec[i][j - 1] + 1, vec[i][j] - 1, cntq);
					qid[i].pb(cntq);
				}
			}
			if (vec[i].back() != n) {
				++cntq;
				q[cntq] = Query_t(vec[i].back() + 1, n, cntq);
				qid[i].pb(cntq);
			}
		}
	}
	sort(q + 1, q + cntq + 1, cmp);
	curl = 1, curr = 0;
	for (int i = 1; i <= cntq; ++i) {
		while (curl > q[i].l) movel(-1);
		while (curr < q[i].r) mover(1);
		while (curl < q[i].l) movel(1);
		while (curr > q[i].r) mover(-1);
		ans[q[i].id] = get_mex();
	}
	for (int i = 1; i <= n + 2; ++i) {
		bool fail = 0;
		for (int j = 0; j < SZ(qid[i]); ++j) {
			if (ans[qid[i][j]] == i) {
				fail = 1;
				break;
			}
		}
		if (!fail) {
			cout << i << endl;
			return 0;
		}
	}
	assert(0);
}
```



---

## 作者：Leeb (赞：1)

### 题意简述

求一个数列的所有子区间的 $\text{mex}$ 的 $\text{mex}$。

某个数组的 $\text{mex}$ 是这个数组中没有包含的最小正整数。

本题翻译好评，难得的好翻译。

### 解题思路

对于一个数 $a$，是否存在一个区间的 $\text{mex}$ 和 $a$ 相等的条件是对于这个 $a$ 到最近的上一个出现 $a$ 的位置，这中间是否满足 $1\sim a-1$ 这 $a-1$ 个数是否都存在。

很好想到用权值线段树来记录 $a_i$ 出现的最后一个位置，对于一个 $a$ 而言，只要满足 $(1,a-1)$ 这个线段树区间的最小值大于 $lst_a$ 即可。（$lst_a$ 即为 $a$ 出现的最后一个位置）

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long 
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, a[N], lst[N], ans[N];
struct Tree {
    int l, r, val;
} tree[N << 2];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline void build(int x, int l, int r) {
    tree[x].l = l, tree[x].r = r;
    if (l == r) return ;
    int mid = l + r >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
}
inline void update(int x, int c, int v) {
    if (tree[x].l == tree[x].r && tree[x].l == c) {
        tree[x].val = v; return ;
    }   
    int mid = tree[x].l + tree[x].r >> 1;
    if (c <= mid) update(ls, c, v);
    else update(rs, c, v);
    tree[x].val = min(tree[ls].val, tree[rs].val);
}
inline int query(int x, int l, int r) {
    if (tree[x].l == l && tree[x].r == r)
        return tree[x].val;
    int mid = tree[x].l + tree[x].r >> 1;
    if (r <= mid) return query(ls, l, r);
    elif (l > mid) return query(rs, l, r);
    else return min(query(ls, l, mid), query(rs, mid + 1, r));
}
int mxx = 0;
inline void init() {
    n = in();
    for (int i = 1; i <= n; ++i) {
        a[i] = in();
        mxx = max(mxx, a[i]);
    }
}
inline void work() {
    build(1, 1, mxx);
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 1) {
            update(1, 1, i);
            lst[a[i]] = i; continue;
        }
        ans[1] = 1;
        int x = query(1, 1, a[i] - 1);
        if (lst[a[i]] < x) ans[a[i]] = 1;
        lst[a[i]] = i, update(1, a[i], i);
    }
    for (int i = 2; i <= mxx + 1; ++i) {
        int x = query(1, 1, i - 1);
        if (lst[i] < x) ans[i] = 1;
    }
    int ans_;
    for (int i = 1; i <= mxx + 2; ++i) 
        if (ans[i] == 0) {
            ans_ = i; break;
        }
    out(ans_, '\n');
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```



---

## 作者：sim_sugar (赞：1)

形如『所有子区间』问题，考虑扫描线，由于是 mex 所以第一想法应该是删除而不是加入，因为删除可以规避维护出现次数，并且能带来单调性。  
（删除一个 $a_r$，设 $pre_r$ 表示上一个 $a_r$ 的位置，$res_l$ 表示 $[l, r]$ 的 mex，则它带来的影响是 $\forall l \in (pre_r, r - 1], res_l \gt a_r$ 的 $res_l$ 设为 $a_r$。注意到 $res_l$ 显然是随 $l$ 减小单调不降的，所以可以线段树二分维护。）  
先求出每个 $l$ 到 $n$ 的 mex，这同样可以通过删除求出，也就是先求 $1 \sim n$，再从左往右移动左端点。把这些值放到一个桶里。  
然后考虑从右往左扫描右端点 $r$，假设当前从 $r \to r - 1$，每次在线段树上二分找出一段后缀将 mex 设为 $a_r$，如果后缀不为空就修改，并且把 $a_r$ 放到桶里就好了。  
最后 $O(n)$ 地用这个桶求出所有答案的 mex。复杂度是 $O(n \log n)$。  

---

## 作者：Demoe (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1436E)

## 题意

- 求一个数列的所有连续子数列的 $\text{mex}$ 值的 $\text{mex}$

翻译好评。

## Sol

### 值域和 $n$ 范围一样诶qaq。

我们考虑如何区间 $\text{mex}$ 会是 $i$。

首先区间中不包括 $i$。

其次区间中 $[1,i-1]$ 都**存在**。

那么可以发现，以两个相邻 $i$ 包括的区间（不包括 $i$），一定比其子区间优秀。

那么就可以对这个区间求一下 $\text{mex}$，判断一下是否为 $i$ 即可。

那这样我们考虑有多少个这样的区间。

由于加上与头尾成段，那么最多会存在 $2n-1$ 个这样的区间。

样例二这个样例好诶，它提醒你**全局**的 $\text{mex}$ 不要落下。

离线区间 $\text{mex}$ 这问题是老题了，莫队+值域分块就行了。

时间复杂度 $O(n\sqrt n)$。

### $\text{Code}$

```cpp
// wish to get better qwq

#include<bits/stdc++.h>
#define re register int
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define mp make_pair

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

template<class T> inline void rd(T &x){
	int fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
template<class T> inline void wr(T x){
	if(x<0) x=-x,putchar('-');
	if(x<10){putchar(x+'0');return ;}
	int tmp[30]={0},cnt=0;
	while(x) tmp[cnt++]=x%10,x/=10;
	for(re i=cnt-1;i>=0;--i) putchar(tmp[i]+'0');
}

// ---------- IO ---------- //

const int N=1e5+5;
int n,a[N],len=350,lst[N],cnt,ans[N];

inline int block(int x){return (x-1)/len+1;}
inline int L(int x){return (x-1)*len+1;}
inline int R(int x){return x*len;}

struct question{int id,l,r,pos;}q[N<<2];

inline bool cmp(question x,question y){
	if(x.pos!=y.pos) return x.pos<y.pos;
	if(x.pos&1) return x.r<y.r;
	return x.r>y.r;
}

struct block_on_range{
	int a[N],b[N],c[N],d[N];
	inline void insert(int x){
		if(a[x]==0) c[x]=1,d[block(x)]++;
		a[x]++;b[block(x)]++;
	}
	inline void erase(int x){
		a[x]--;b[block(x)]--;
		if(a[x]==0) c[x]=0,d[block(x)]--;
	}
	inline int mex(){
		int tmp=block(n);
		for(re i=1;i<tmp;++i){
			if(len==d[i]) continue;
			for(re j=L(i);j<=R(i);++j) if(!c[j]) return j;
		}
		for(re i=L(tmp);i<=n;++i) if(!c[i]) return i;
		return n+1;
	}
}qaq;

// ----------  ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);
	for(re i=1;i<=n;++i){
		rd(a[i]);
		if(i-lst[a[i]]>1) q[++cnt]=(question){a[i],lst[a[i]]+1,i-1,block(lst[a[i]]+1)};
		lst[a[i]]=i;
	}
	for(re i=1;i<N;++i)
		if(lst[i]&&lst[i]!=n) q[++cnt]=(question){i,lst[i]+1,n,block(lst[i]+1)};
	sort(q+1,q+cnt+1,cmp);
	int l=q[1].l+1,r=q[1].l;
	for(re i=1;i<=cnt;++i){
		while(l>q[i].l) --l,qaq.insert(a[l]);
		while(r<q[i].r) ++r,qaq.insert(a[r]);
		while(l<q[i].l) qaq.erase(a[l]),l++;
		while(r>q[i].r) qaq.erase(a[r]),r--;
		//cout<<q[i].l<<' '<<q[i].r<<' '<<q[i].id<<' '<<qaq.mex()<<endl;
		if(qaq.mex()==q[i].id) ans[q[i].id]=1;
	}
	while(l>1) --l,qaq.insert(a[l]);
	while(r<n) ++r,qaq.insert(a[r]);
	ans[qaq.mex()]=1;
	for(re i=1;i<N;++i)
		if(!ans[i]){
			wr(i);puts("");break;
		}
	return 0;
}

// ---------- Main ---------- //


```

这场只有 F 不会，可惜没时间打/kk

---

## 作者：tommymio (赞：1)

求解 $\mathrm{mex}$ 的 $\mathrm{mex}$，肯定先想到枚举最终的答案，再来判定这个答案是否合法。

根据 $\mathrm{mex}$ 的定义，如果最终答案为值 $x$，则必满足以下两个条件：

- $\forall y<x,\exists 1\leq l\leq r\leq n,\mathrm{mex}(a_l,a_{l+1},...,a_r)=y$
- $\forall 1\leq l\leq r\leq n,\mathrm{mex}(a_l,a_{l+1},...,a_r)\neq x$

第一个条件显然可以通过从小到大枚举 $x$ 来解决，那么第二个条件呢？我们不可能通过 $O(n^2)$ 枚举来判断每一个区间，时间复杂度过高。

这里需要用到 $\mathrm{mex}$ 运算的一个性质，对于（可重/不可重）集合 $S$ 的 $\mathrm{mex}$，一定不会是 $S$ 中的任意一个值。形式化的说，$\mathrm{mex}_{i\in S}(i)\notin S$。

也就是说，如果区间中包含值 $x$，则这样的区间的 $\mathrm{mex}$ 值一定不为 $\mathrm{mex}$。那么我们只需要考虑那些不包含值 $x$ 的区间，对他们求 $\mathrm{mex}$ 并判断即可。对于所有的 $x$，这样的区间数量之和是 $O(n)$ 级别的。

我们使用主席树求区间 $\mathrm{mex}$。具体做法就是建 $n$ 棵线段树，第 $i$ 棵线段树上存储权值 $y$ 在 $a_1,a_2,a_3...a_i$ 中最晚出现的位置，区间查询 $[L,R]$ 的时候在第 $R$ 棵线段树上查询小于 $L$ 的最左节点即可。都是常见套路应该很好理解。

总时间复杂度为 $O(n \log n)$，可以通过本题。

```cpp
#include<cstdio>
#include<vector>
int num=0;
std::vector<int> p[100005];
int rt[100005],sonL[2000005],sonR[2000005],val[2000005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline void assign(int x,int y) {sonL[x]=sonL[y]; sonR[x]=sonR[y]; val[x]=val[y];}
inline void change(int &p,int lst,int l,int r,int x,int pos) {
    assign(p=++num,lst);
    if(l==r) {val[p]=pos;return;}
    int mid=l+r>>1;
    if(x<=mid) change(sonL[p],sonL[lst],l,mid,x,pos);
    else change(sonR[p],sonR[lst],mid+1,r,x,pos);
    val[p]=min(val[sonL[p]],val[sonR[p]]);
}
inline int ask(int p,int l,int r,int L) {
    if(l==r) return l;
    int mid=l+r>>1;
    if(val[sonL[p]]<L) return ask(sonL[p],l,mid,L);
    return ask(sonR[p],mid+1,r,L);
}
int main() {
    int n=read();
    for(register int i=1;i<=n;++i) {
        int x=read();
        p[x].push_back(i);
        change(rt[i],rt[i-1],1,n+1,x,i);
    }
    for(register int i=1;i<=n+1;++i) p[i].push_back(n+1);
    for(register int i=1;i<=n+1;++i) {
        int pre=1,flag=0;
        for(register int j=0;j<p[i].size();++j) {
            if(p[i][j]==1) {pre=2;continue;}
            if(pre>p[i][j]-1) continue;
            if(ask(rt[p[i][j]-1],1,n+1,pre)==i) {flag=1;break;}
            pre=p[i][j]+1;
        }
        if(flag==0) {printf("%d\n",i);return 0;}
    }
    printf("%d\n",n+2);
    return 0;
}

```

---

## 作者：KaisuoShutong (赞：1)

# CF1436E Complicated Computations

## 题意简化

> 给定一个 $n$ 个元素的数列 $a$，求 $a$ 所有非空子序列的 $MEX$ 所构成的数列的 $MEX$。

## 题目分析

首先，考虑枚举 $MEX$ 的 $MEX$。假设当前枚举到了 $x$。

在此之后，取出所有不含 $x$ 的区间，如下图。

![break.png](https://s1.ax1x.com/2020/10/26/BuM0dx.png)

黑色线段表示的是需要取出的区间。

现在，问题转换为快速（$log$）求区间 $MEX$。

以权值为下标，数组位置为时间轴（$rt$）建一颗主席树。

每次单点修改，区间查询，维护当前区间中每个权值最后一个出现位置的最小值。

查询区间 $[l,r]$ 的 $MEX$ 时，在主席树上 `ask(rt[r],1,n+1,l)`，其中，如果左区间的最小值小于 $l$ 就向左走，不然就向右走。

时间复杂度最坏 $O(n\times log\space n)$。

---

## 作者：Unnamed114514 (赞：0)

考虑到答案最多也就 $n+2$，所以考虑直接爆枚。

对于 $i$ 的存在性，我们存储所有 $i$ 出现的位置，然后我们得到了一堆分割点，把这个序列分成了一堆区间。

注意到我们此时考虑的是 $i$ 是否存在，那么实际上就是问是否存在一个区间 $\operatorname{MEX}$ 为 $i$。

贪心，因为对于一个不含 $x$ 的区间，显然区间越长越优。

那么思路就很显然了：对于每个分割出来的区间，求解每个区间的 $\operatorname{MEX}$，这里的 $\operatorname{MEX}$ 其实不需要直接求，对于 $[l,r]$ 的 $\operatorname{MEX}$ 是否为 $x$，我们只需要知道 $[1,x-1]$ 在 $[1,r]$ 中最后一次出现的位置是否 $\ge l$，那么就是 $[1,x-1]$ 中最小值是否 $\ge l$。

但是注意到线段上如果存在 $[1,0]$ 的查询会寄，所以我们从 $2$ 开始枚举 $i$，然后把 $1$ 特判掉，显然当且仅当序列中全为 $1$ 时，答案为 $1$。

对于 check 每个值部分，显然有个可行性剪枝：如果区间长度 $<x-1$，那么这个区间的 $\operatorname{MEX}$ 显然不可能是 $x$。

~~那么我们的查询区间最多就是：$\sum\limits_{i=2}^{n+2}\lfloor\dfrac{n}{i-1}\rfloor$，根据数论分数论分块的知识，可以发现其实这个玩意就是 $n\sqrt{n}$ 级别的。而且由于一个位置跑不满所以最后复杂度显然优于 $n\sqrt{n}$。最后复杂度 $O(n\sqrt{n}\log n)$，但是众所周知 CF 机子跑 $10^9$ 轻轻松松。~~

上面这个东起上界显然过于宽泛，考虑算每个点作为区间的贡献，不难想到，其实每个点只会和它前面离他最近的和它权值相等的位置进行匹配，所以本质上查询的区间只有 $n$ 个，所以最后的复杂度其实是 $O(n\log n)$。

[code](https://codeforces.com/contest/1436/submission/232803789)

---

## 作者：OIer_ACMer (赞：0)

~~一道模板题卡了我一晚上！~~

------------
## 警钟敲烂：
本以为是个水题，没想到是个毒瘤！！！提醒各位：做这道题时，切记切记初始化！！

------------
## 大致思路：
这道题很显然是一道关于权值线段树的题目，再看看题面：

首先，某个数组的 $MEX$ 数是这个数组中没有包含的最小正整数，要使 $MEX$ 值等于 $x$，则要满足：

1. $1$ 到 $n - 1$ 都在序列中出现过。

2. 唯独 $x$ 没出现过。

想要满足这些条件，就要枚举右端点 $i$ ~~说实话有些暴力~~，考虑是否存在区间使得 $MEX$ 的值为 $x$ ，那么**利用权值线段树维护每个值的最近出现的位置**，接着，求出 $1$ 到 $n - 1$ 的最小值 $p$，如果 $p$ 的值在最后一次出现最小值 $x$ 的后面，则可以直接得到 $x$，因为题目要求 $MEX$ 的值**既没有在序列中出现过也要尽量小**。然而直接向前遍历。怎么优化这种方法它也是个暴力算法，因此我们就要像一个更优秀的算法。

既然这样不行，就要换一种思路：我们再观察一下，下一个 $x$ 出现的位置肯定在 $i$ 之后。那么我们对 $x$ 枚举下一个出现的位置，然后考虑上一个出现的位置是否小于 $p$。通俗的讲，就是**枚举数组的每个位置，看上一个** $a[i]$ **出现的位置是否在** $p$ **的位置之前即可**。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int mod = 1e9 + 7;
const int MAXN = 2e5 + 5;
const int inf = 0x3f3f3f3f;
int a[MAXN];
int vis[MAXN], pre[MAXN];
struct node
{
    int l, r;
    int minn;
} tree[MAXN << 2];
void build(int l, int r, int num)
{
    tree[num].l = l;
    tree[num].r = r;
    if (l == r)
    {
        tree[num].minn = 0;
        return;
    }
    int minnd = (l + r) >> 1;
    build(l, minnd, num << 1);
    build(minnd + 1, r, num << 1 | 1);
    tree[num].minn = min(tree[num << 1].minn, tree[num << 1 | 1].minn);
}
void updata(int pos, int val, int num)
{
    if (tree[num].l == tree[num].r)
    {
        tree[num].minn = val;
        return;
    }
    int minnd = (tree[num].l + tree[num].r) >> 1;
    if (pos <= minnd)
    {
        updata(pos, val, num << 1);
    }
    else
    {
        updata(pos, val, num << 1 | 1);
    }
    tree[num].minn = min(tree[num << 1].minn, tree[num << 1 | 1].minn);
}
int query(int l, int r, int num)
{
    if (tree[num].l >= l && tree[num].r <= r)
    {
        return tree[num].minn;
    }
    int minnd = (tree[num].l + tree[num].r) >> 1;
    int minn = 1e9;
    if (l <= minnd)
    {
        minn = min(minn, query(l, r, num << 1));
    }
    if (r > minnd)
    {
        minn = min(minn, query(l, r, num << 1 | 1));
    }
    return minn;
}
int n;
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    for (int i = 1; i <= n + 2; i++)
    {
        pre[i] = 0;
    }
    build(1, n + 2, 1);
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > 1)
        {
            vis[1] = 1;
            int pos = query(1, a[i] - 1, 1);
            if (pos > pre[a[i]])
            {
                vis[a[i]] = 1;
            }
            // cout << "pre[" << "a[" << i << "]]=" << pre[a[i]] << endl;
        }
        updata(a[i], i, 1);
        pre[a[i]] = i;
    }
    for (int i = 2; i <= n + 2; i++)
    {
        if (query(1, i - 1, 1) > pre[i])
        {
            vis[i] = 1;
        }
    }
    for (int i = 1; i <= n + 2; i++)
    {
        if (!vis[i])
        {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121496964)

---

## 作者：happybob (赞：0)

首先可以发现答案小于等于 $n+2$.于是可以考虑枚举 $x$，判断 $x$ 是否为一个子段的 $\operatorname{mex}$。

考虑如果 $x$ 为 $\operatorname{mex}$ 的条件是什么？区间内没有 $x$，但包含 $1 \sim x-1$。我们不需要关心 $x+1$ 或以上的数是否有出现。

所以我们可以将序列分成若干段，每一段都不含 $x$，但其两边的数要么是 $x$，要么这个区间的左端为 $1$ 或右端为 $n$。我们只需要判断这些区间的 $\operatorname{mex}$ 是否为 $x$。

当然可以离线莫队加值域分块做，但我们也可以从前往后扫每个数，记录 $lst_i$ 为 $i$ 这个数在当前扫描到的前缀中最后的出现位置。当我们扫到 $a_i=x$，判断 $lst_x+1 \sim i-1$ 这个区间是否出现了 $1 \sim x-1$ 每个数，即 $\min \limits_{j=1}^{x-1} lst_j > lst_x$。然后更新 $lst_x$。

权值线段树维护单点修改区间最小值即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 1e5 + 10;
int n, a[N];
int lstpos[N];
bool vis[N];

class SegmentTree
{
public:
	struct Node
	{
		int l, r, minn;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 0 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update(int u, int x, int v)
	{
		if (tr[u].l == tr[u].r)
		{
			tr[u].minn = v;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) update(u << 1, x, v);
		else update(u << 1 | 1, x, v);
		pushup(u);
	}
	int query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].minn;
		int res = 2e9, mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid) res = min(res, query(u << 1 | 1, l, r));
		return res;
	}
}sgt;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sgt.build(1, 1, n);
	for (int i = 1; i <= n; i++)
	{
		if (a[i] ^ 1)
		{
			vis[1] = 1;
		}
		else
		{
			lstpos[a[i]] = i;
			sgt.update(1, a[i], i);
			continue;
		}
		int p = sgt.query(1, 1, a[i] - 1);
		if (p > lstpos[a[i]])
		{
			vis[a[i]] = 1;
		}
		lstpos[a[i]] = i;
		sgt.update(1, a[i], i);
	}
	for (int i = 2; i <= n + 1; i++)
	{
		if (sgt.query(1, 1, min(n, i - 1)) > lstpos[i])
		{
			vis[i] = 1;
		}
	}
	for (int i = 1; i <= n + 2; i++)
	{
		if (!vis[i])
		{
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}
```




---

## 作者：Fzrcy (赞：0)

直接求出所有连续子数列的 $\operatorname{mex}$ 值是 $O(n^2)$ 的，无法通过此题，考虑换一个方式计算。明显的，一个连续子数列 $[l,r]$ 的 $\operatorname{mex}$ 值为 $x$ 当且仅当 $[1,x-1]$ 的值均出现且 $x$ 未出现，从小到大考虑 $x$ 是否是一个连续子数列的 $\operatorname{mex}$ 值，将数对 $(val, pos)$（$pos$ 为位置，$val=a_{pos}$）从小到大排序（$val$ 为第一关键字，$pos$ 为第二关键字），然后依次加入权值线段树中（检查后再插入），权值线段树维护每个值最后出现的位置，若 $val$ 可以为连续子数列的 $\operatorname{mex}$ 值，当且仅当 $[1,val-1]$ 最后出现的位置大于上一个值为 $val$ 的位置 $pos'$，最后一个值为 $val$ 的位置用一个数组维护即可，注意对 $1$ 的特判。

[代码](https://codeforces.com/contest/1436/submission/205316977)。


---

## 作者：JWRuixi (赞：0)

~~为什么这题会被 OI-Wiki 评为分块套树状数组的板题……~~

- 题意

定义 $\operatorname{MEX}(a)$ 为序列 $a$ 中第一个没有出现的正整数，形式化的即最下的 $x$ 满足 $x \notin a,\forall y \in [1,x-1],y\in a$。

求给定序列 $a$ 的子段的 $\operatorname{MEX}$ 组成的序列的 $\operatorname{MEX}$。

- 分析

这题的思路非常的巧妙，你考虑一下一个数能否成为答案，比如说考虑 $x$ 能否成为答案。

那就是说找不到子段的 $\operatorname{MEX}$ 为 $x$，怎么判断一个子段的 $\operatorname{MEX}$ 呢？这里有一个经典套路，用主席树维护，表示值为 $x$ 的数最后一次出现的位置，答案就是第一个出现位置在左端点之前的数，具体参见 [P4137 Rmq Problem / mex](https://www.luogu.com.cn/problem/P4137)/。

那我们可以用每个数 $x$ 将数组分隔成若干段，判断其中是否有一段的 $\operatorname{MEX}$ 为 $x$。

复杂度 $O(n\log n)$。

- code

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

const int maxn(1e5 + 50);
int n, a[maxn], cnt, rt[maxn];
vector <int> G[maxn];

struct SGTNode {
	int mn, ls, rs;
} tr[maxn * 24];

inline void mdy (int s, int l, int r, int &p, int q, int v) {
	p = ++cnt;
	tr[p] = tr[q];
	if (l == r) {
		tr[p].mn = v;
		return;
	}
	const int mid = (l + r) >> 1;
	if (s <= mid) mdy(s, l, mid, tr[p].ls, tr[q].ls, v);
	else mdy(s, mid + 1, r, tr[p].rs, tr[q].rs, v);
	tr[p].mn = min(tr[tr[p].ls].mn, tr[tr[p].rs].mn);
}

inline int qry (int s, int l, int r, int p) {
	if (l == r) return l;
	const int mid = (l + r) >> 1;
	if (s >= tr[tr[p].ls].mn) return qry(s, l, mid, tr[p].ls);
	else return qry(s, mid + 1, r, tr[p].rs);
}

inline bool check (int mex) {
	int lst = 0;
	for (int &pos : G[mex]) {
		if (pos - 1 != lst && qry(lst, 1, n + 1, rt[pos - 1]) == mex) return 1;
		lst = pos;
	}
	return 0;
}

int main () {
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) G[a[i]].push_back(i);
	for (int i = 1; i <= n; i++) mdy(a[i], 1, n + 1, rt[i], rt[i - 1], i);
	for (int i = 1; i <= n + 1; i++) G[i].push_back(n + 1);
	int MEX = 1;
	while (check(MEX)) MEX++;
	write(MEX);
}
```

---

