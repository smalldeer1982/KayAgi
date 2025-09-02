# [JOI Open 2025] 冒泡排序机 / Bubble Sort Machine

## 题目背景

译自 [JOI Open 2025](https://contests.ioi-jp.org/open-2025/index.html) T1「[Bubble Sort Machine](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/cm7aghex)」/ 「[バブルソート機](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/gkrcwais)」。


## 题目描述


JOI 君——一名算法工程师，开发了冒泡排序机。

冒泡排序机操作长为 $N$ 的整数序列 $a=(a_1,a_2,\ldots,a_N)$。为了让机器能工作，给定 $A_i$ 作为 $a_i$（$1\le i\le N$）的初值。每当机器上的**按钮壹**被按下时，机器会按照如下方式修改序列 $a$：

> 对于 $i=1,2,\ldots,N-1$（按此顺序），若 $a_i\gt a_{i+1}$，交换 $a_i,a_{i+1}$ 的值。

为了使冒泡排序机更博人眼球，JOI 君决定加入以下功能：

> 当**按钮贰**被按下时，给定整数 $l,r$ 作为输入（须满足 $1\le l\le r\le N$），机器会输出 $a_{l}+a_{l+1}+\cdots+a_r$ 的值。

给定整数序列的初值和冒泡排序机的操作序列，编程计算按钮贰的输出值。


## 说明/提示


### 样例解释

#### 样例 $1$ 解释

初值为 $a_1=5,a_2=3,a_3=5,a_4=2$，$a=(5,3,5,2)$。接下来在冒泡排序机上操作：

1. 按下按钮贰，输入 $l=1,r=3$。机器输出 $a_1+a_2+a_3=13$。
2. 按下按钮壹。对 $i=1,2,3$，按此顺序进行如下操作：
    - $i=1$：由于 $a_1\gt a_2$，交换二者的值，操作后 $a=(3,5,5,2)$。
    - $i=2$：由于并没有 $a_2\gt a_3$，不操作 $a$。
    - $i=3$：由于 $a_3\gt a_4$，交换二者的值，操作后 $a=(3,5,2,5)$。
3. 按下按钮贰，输入 $l=1,r=1$。机器输出 $a_1=3$。
3. 按下按钮贰，输入 $l=2,r=4$。机器输出 $a_2+a_3+a_4=12$。
5. 按下按钮壹。对 $i=1,2,3$，按此顺序进行如下操作：
    - $i=1$：由于并没有 $a_1\gt a_2$，不操作 $a$。
    - $i=2$：由于 $a_2\gt a_3$，交换二者的值，操作后 $a=(3,2,5,5)$。
    - $i=3$：由于并没有 $a_3\gt a_4$，不操作 $a$。
6. 按下按钮贰，输入 $l=1,r=2$。机器输出 $a_1+a_2=5$。

样例 $1$ 满足子任务 $1,5,6$ 的限制。

#### 样例 $2$ 解释

样例 $2$ 满足子任务 $1,3,5,6$ 的限制。


### 数据范围

- $2\le N\le 500\, 000$；
- $1\le A_i\le 10^9\, (1\le i\le N)$；
- $1\le Q\le 500\, 000$；
- $T_j\in \{1,2\}\, (1\le j\le Q)$；
- 若 $T_j=2$，有 $1\le L_j\le R_j\le N\, (1\le j\le Q)$；
- 输入的值都是整数。

### 子任务

- $\text{Subtask 1 (5 pts)}$：满足 $T_j=1$ 的 $j\,(1\le j\le Q)$ 至多有 $10$ 个；
- $\text{Subtask 2 (11 pts)}$：$N,Q\le 150\, 000$，当 $T_j=2$ 时 $L_j=R_j=1\, (1\le j\le Q)$；
- $\text{Subtask 3 (15 pts)}$：$N,Q\le 150\, 000$，$1\le A_i\le 2\, (1\le i\le N)$；
- $\text{Subtask 4 (23 pts)}$：$N,Q\le 150\, 000$，当 $T_j=2$ 时 $L_j=R_j\, (1\le j\le Q)$；
- $\text{Subtask 5 (29 pts)}$：$N,Q\le 150\, 000$；
- $\text{Subtask 6 (17 pts)}$：无额外限制。



## 样例 #1

### 输入

```
4
5 3 5 2
6
2 1 3
1
2 1 1
2 2 4
1
2 1 2```

### 输出

```
13
3
12
5```

## 样例 #2

### 输入

```
5
1 1 2 1 2
5
2 2 3
1
2 2 4
1
2 2 4```

### 输出

```
3
4
4```

# 题解

## 作者：Mirasycle (赞：4)

## 本题
伟大的 carotrl 在  AH 省集中提出冒泡排序若干轮之后的结果是可以直接刻画的。

具体来说说前缀 $[1,l]$ 在经过 $c$ 轮冒泡排序之后的数字构成是原先区间 $[1,l+c]$ 中的前 $l$ 小的数，这个很好理解，经过 $c$ 轮冒泡排序之后，某个数最多往前平移的位置数就是 $c$，所以范围是 $[1,l+c]$，而小的数会往前走，所以就是前 $l$ 小。

这样子就可以完成本题了，我们直接拿 $[1,r]$ 经过 $c$ 轮冒泡排序之后的数字组成减去 $[1,l-1]$ 的即可。区间 kth 信息可以直接拿主席树在线维护。时间复杂度 $O(n\log n)$。

## 扩展版-区间前 $k$ 小之和

> 改为若干次操作之后区间 $[l,r]$ 的前 $k$ 小值，如何做？

将上述定理扩展一些，前缀 $[1,l]$ 经过冒泡排序 $c$ 轮之后的前 $k$ 小值为原序列中区间 $[1,l+c]$ 的前 $k$ 小值。

区间 $[l,r]$ 经过 $c$ 轮冒泡排序之后的前 $k$ 小值就是前缀 $[1,r+c-1]$ 中去除前缀 $[1,l+c-1]$ 中的前 $l-1$ 小值之后的前 $k$ 小值，注意这里不能单纯拿两个作差，需要巧妙实现。

还是可以通过主席树在线维护的。本质还是对于两个前缀进行差分，需要设置一个阈值，意思是 $[1,l+c-1]$ 这个区间最多贡献 $l-1$。具体可以看看代码。

调用 `solve(rt[min(l+c-1,n)],rt[min(r+c,n)],1,n,l-1,k)` 即可，其中 $\rm query$ 函数就是对于某个版本的主席树区间求和。


```cpp

	ll solve(int p,int q,int l,int r,int up,int cnt){
		if(l==r) return 1ll*cnt*l;
		int z=val[ls[q]]-min(val[ls[p]],up);
		if(z>=cnt) return solve(ls[p],ls[q],l,mid,up,cnt);
		int del=min(up,val[ls[p]]);
		return sum[ls[q]]-query(0,ls[p],l,mid,del)+solve(rs[p],rs[q],mid+1,r,up-del,cnt-z);
	}
```


## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb emplace_back
using namespace std;
typedef long long ll;
const int maxn=5e5+10;
int a[maxn],b[maxn],rt[maxn],n,m,q;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct SegmentTree{
	#define mid ((l+r)>>1)
	int val[maxn<<6],ls[maxn<<6],rs[maxn<<6],tot; ll sum[maxn<<6];
	void pushup(int p){ val[p]=val[ls[p]]+val[rs[p]]; sum[p]=sum[ls[p]]+sum[rs[p]]; }
	void build(int &p,int q,int l,int r,int x){
		p=++tot; ls[p]=ls[q]; rs[p]=rs[q];
		val[p]=val[q]; sum[p]=sum[q]; 
		if(l==r){ val[p]++; sum[p]+=b[x]; return ; }
		if(x<=mid) build(ls[p],ls[q],l,mid,x);
		else build(rs[p],rs[q],mid+1,r,x);
		pushup(p);
	}
	ll query(int p,int q,int l,int r,int k){
		if(l==r) return 1ll*k*b[l]; 
		int z=val[ls[q]]-val[ls[p]];
		if(z>=k) return query(ls[p],ls[q],l,mid,k);
		else return sum[ls[q]]-sum[ls[p]]+query(rs[p],rs[q],mid+1,r,k-z);
	}
}seg;
int main(){
	cin>>n; int c=0;
	for(int i=1;i<=n;i++) a[i]=read(),b[i]=a[i];
	sort(b+1,b+1+n); m=unique(b+1,b+1+n)-(b+1); cin>>q;
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+m,a[i])-b;
	for(int i=1;i<=n;i++) seg.build(rt[i],rt[i-1],1,m,a[i]);
	for(int i=1;i<=q;i++){
		int t,l,r; t=read();
		if(t==1) c++;
		else{
			l=read(); r=read();
			printf("%lld\n",seg.query(rt[0],rt[min(r+c,n)],1,m,r)-seg.query(rt[0],rt[min(l+c-1,n)],1,m,l-1));
		}
	}
	return 0;
}
```

---

## 作者：masterhuang (赞：3)

**事实上，这题很简单。发现这个事实，你就会做了。**

- 考虑区间求和是与前缀和等价的，于是我们做前缀和。

- 同时考虑对于一个询问，我们只关心之前按了多少次冒泡按钮。

- 我们有如下结论：按冒泡按钮 $k$ 次后，$[1,r]$ 这个前缀和的结果为 $[1,\min(r+k,n)]$ 中前 $r$ 小的和。

这是因为按 $k$ 次时，只有 $[1,\min(r+k,n)]$ 这些位置会对前 $r$ 个数影响。

于是我们在 $\min(r+k,n)$ 这个位置截断数组，只关心前面这些位置。

然后由于冒泡一次会让最大值到最后，两次会让次大值到倒二，以此类推，于是就证明了我们的结论。

对询问离线下来，线段树上二分维护前 $k$ 小的数的和即可。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define ls w<<1
#define rs w<<1|1
#define lw l,m,ls
#define rw m+1,r,rs
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
namespace IO
{
	const int _Pu=2e7+5,_d=32;
	char buf[_Pu],obuf[_Pu],*p1=buf+_Pu,*p2=buf+_Pu,*p3=obuf,*p4=obuf+_Pu-_d;
	inline void fin()
	{
		memmove(buf,p1,p2-p1);
		int rlen=fread(buf+(p2-p1),1,p1-buf,stdin);
		if(p1-rlen>buf) buf[p2-p1+rlen]=EOF;p1=buf;
	}
	inline void fout(){fwrite(obuf,p3-obuf,1,stdout),p3=obuf;}
	inline int rd()
	{
		if(p1+_d>p2) fin();int isne=0,x=0;
		for(;!isdigit(*p1);++p1) isne=(*p1=='-');x=(*p1++-'0');
	    for(;isdigit(*p1);++p1) x=x*10+(*p1-'0');
		if(isne) x=-x;return x;
	}
	inline void wr(LL x,char end='\n')
	{
		if(!x) return *p3++='0',*p3++=end,void();
		if(x<0) *p3++='-',x=-x;
		char sta[20],*top=sta;
		do{*top++=(x%10)+'0';x/=10;}while(x);
		do{*p3++=*--top;}while(top!=sta);(*p3++)=end;
	}
}using IO::rd;using IO::wr;
const int N=5e5+5;
int n,m,L,a[N],C,b[N<<2],d[N];LL ans[N],s[N<<2];
struct Q{int k,o,id;};vector<Q>q[N];
inline void add(int r,int c,int o,int id){q[min(r+c,n)].push_back({r,o,id});}
void upd(int p,int l=1,int r=L,int w=1)
{
	if(l==r) return b[w]++,s[w]+=d[p],void();
	int m=(l+r)>>1;p<=m?upd(p,lw):upd(p,rw);
	b[w]=b[ls]+b[rs],s[w]=s[ls]+s[rs];
}
LL qry(int k,int l=1,int r=L,int w=1)
{
	if(l==r) return (LL)k*d[l];int m=(l+r)>>1;
	return (k>b[ls])?qry(k-b[ls],rw)+s[ls]:qry(k,lw);
}
int main()
{
	n=rd();
	for(int i=1;i<=n;i++) a[i]=d[i]=rd();m=rd();
	sort(d+1,d+1+n);L=unique(d+1,d+1+n)-d-1;
	for(int o,l,r,c=0;m--;)
	{
		o=rd();
		if(o==1) c++;
		else
		{
			l=rd(),r=rd();add(r,c,1,++C);
			if(l>1) add(l-1,c,-1,C);
		}
	}
	for(int i=1;i<=n;i++)
	{
		upd(lower_bound(d+1,d+1+L,a[i])-d);
		for(auto [k,o,id]:q[i]) ans[id]+=o*qry(k);
	}
	for(int i=1;i<=C;i++) wr(ans[i]);
	return IO::fout(),0;
}
```

---

## 作者：SDSXC (赞：3)

~~昨晚想了一个小时没想出来，今天吃早饭的时候突然会了，感觉这个题很牛。~~

此题貌似是并不需要可持久化线段树的，可能是我太菜了没想到。

首先我们看一下题目给的提示，想一下 $1\leq A_i\leq 2$ 怎么做，我们打表观察一下，发现每按一次一号按钮，每一个 $2$ 都会移动到下一个 $2$ 的前面一个位置。这相当于所有的 $2$ 前移一位，然后第一个 $2$ 移动到序列末尾，证明是容易的。

那么接着考虑把这个规律扩展到一般的情况。我们想一下每次向后移动的到底是什么。如果 $a_i$ 的前面存在一个严格大于 $a_i$ 的数，那么在操作完 $1\sim i-2$ 之后，要么是这个数移动到了 $a_{i-1}$ 的位置，要么是一个比这个数更大的数把它挡住了，然后更大的数继续往后移动。所以只要 $a_i$ 之前存在一个严格大于 $a_i$ 的数，那么 $a_i$ 一定只会往前移动一个位置，否则 $a_i$ 就会开始往后移。所以我们发现每次往后移动的其实就是前缀最大值(不一定严格)，然后其他的位置全部前移一位。

那么我们考虑一下怎么利用这个规律来做这个题。我们考虑把前缀最大值和非前缀最大值分开来维护，最后再加起来就好。

首先我们不难证明，一个数只要在某一次操作之后变成了前缀最大值，就再也不会变回非前缀最大值了，假设我们已经知道了每次操作会有哪些数变成前缀最大值。

非前缀最大值的维护是简单的，只需要支持整体向前平移和删除一些数就行了，树状数组简单维护即可。

前缀最大值需要支持每次将所有数移动到它后一个有数的位置，然后整体前移，再删除队首和添加队尾，以及向中间添加一些数。这个东西如何做呢，我们先维护哪些位置是有前缀最大值的，这个是简单的，每次只需要删除第一个，末尾添加一个，整体平移即可，依旧树状数组维护。然后我们查询的时候就可以知道要查前缀最大值中的第几个到第几个的和了。然后我们又不难发现，前缀最大值在原序列中一定是从小到大出现的。我们在每次相当于查询其中前 $k$ 大的和，理论可以用平衡树维护，但是那样难写且常数大，我们直接开两个树状数组，把每个数存储在他在原数组中的数从小到大排名的位置，一个给每一个位置加一用来查询第 $k$ 大在原数组中排名第几，另外一个用来计算前缀和。

最后还有一步就是求出每一个数到底什么时候开始成为前缀最大值，这个也是简单的，我们只根据前面注意到的性质，每一次操作时，每一个非前缀最大值都会有一个严格大于它的数从它前面移动到后面，也就是说只需要统计这个数前面有几个严格大于它的就行了。

因为 $A_i$ 是 $10^9$ 的，不要忘记离散化。

这样我们开四个树状数组就做完了，总复杂度 $O((n+q)\log n)$，看似难写但是代码并不长。


```cpp
#include<bits/stdc++.h>
#define N 500009
#define ll long long
using namespace std;
struct BIT{
	ll c[N<<1],n;
	void init(int n_){
		n=n_;memset(c,0,sizeof(c));
	}
	void add(int x,ll v){
		for(;x<=n;x+=(x&-x))c[x]+=v;
	}
	ll sum(int x){
		ll ret=0;for(;x;x-=(x&-x))ret+=c[x];return ret;
	}
	int get(ll x){
		ll ret=0;
		for(int i=__lg(n);~i;--i){
			if((ret|(1<<i))<=n&&c[ret|(1<<i)]<=x){
				ret|=(1<<i);x-=c[ret];
			}
		}
		return ret;
	}
} f,g,p,pos;
basic_string<int> h[N];
int n,q,tot,a[N],c[N],rk[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;for(int i=1;i<=n;i++) cin>>a[i],c[i]=a[i];
	sort(c+1,c+n+1);tot=unique(c+1,c+n+1)-c-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(c+1,c+tot+1,a[i])-c,rk[a[i]]++;
	for(int i=1;i<=tot;i++) rk[i]+=rk[i-1];
	cin>>q;
	f.init(tot);g.init(n<<1);
	for(int i=1;i<=n;i++){
		h[i-f.sum(a[i])]+=i;
		f.add(a[i],1);
		g.add(i,c[a[i]]);
	}
	f.init(n);p.init((n<<1));pos.init(n);
	for(int i=1,op,l,r,cnt=0;i<=q;i++){
		cin>>op;
		if(op==1){
			if(cnt>=n)continue;
			++cnt;
			for(int j:h[cnt]){
				g.add(j,-c[a[j]]);
				p.add(j,1);
				f.add(rk[a[j]],c[a[j]]);
				pos.add(rk[a[j]],1);
				--rk[a[j]];
			}
			p.add(cnt,-1);
			p.add(n+cnt,1);
		}
		else{
			cin>>l>>r;
			ll ans=g.sum(cnt+r)-g.sum(cnt+l-1);
			int x=p.sum(cnt+l-1);x=pos.get(x);
			ans-=f.sum(x);
			x=p.sum(cnt+r);x=pos.get(x);
			ans+=f.sum(x);
			cout<<ans<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Rain_chr (赞：2)

本来以为是很有新意的题，结果发现题解里面都用了同一个关于冒泡排序的套路，瞬间感觉自己唐完了。

首先不难想到将区间拆成 $[1,r]$ 和 $[1,l-1]$，于是每次询问只需要求前缀和。

观察可以得到一个数 $a_i$ 的移动轨迹可以分为两个阶段：

1. $a_i$ 不是前缀最大值

    设 $a_i$ 前面恰好有 $d$ 个严格大于 $a_i$ 的数，那么在最开始的 $d$ 轮冒泡排序中 $a_i$ 下标每次减 1
   
2. $a_i$ 是前缀最大值

    每次 $a_i$ 的下标变成下一个前缀最大值的下标减 $1$

由于移动方式不同，于是我们将前缀最大值和非前缀最大值分开维护。

首先来看 $a_i$ 不是前缀最大值的情况，用 BIT 求出 $d$ 即可得到其成为前缀最大值的时刻，也就是进入阶段 2 的时刻。

在阶段一中，如果已经进行了 $k$ 轮冒泡排序，显而易见其下标就应该为 $i-k$。所以如果其在前缀 $[1,r]$ 中，那么就会有 $i\le k+r$，这个可以用 BIT 方便地统计。

其次来看 $a_i$ 是前缀最大值的情况，可以发现每次冒泡排序都是类似循环移位的过程。虽然循环移位我们不好同时维护下标和值，但是考虑到**前缀最大值是单调递增的**，所以我们只需要维护值的集合以及前缀最大值的位置即可，查询 $[1,r]$ 的前缀最大值时，假设其中有 $x$ 个前缀最大值，那么和就对应的所有值中的前 $x$ 小之和。

而前缀最大值的位置是容易维护的，每次冒泡排序只需要将最小的位置变成 $n+2$，然后全局减 1 即可，直接用带标记的 BIT 维护。

对于所有前缀最大值的取值，需要支持的操作仅仅是查询前 $k$ 小，于是拿一颗值域线段树维护即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int a[N];
vector<int> upd[N];
int tot;
int n,q;
struct BIT
{
    int c[2*N];
    int lowbit(int x){return x&-x;}
    void add(int x,int v){while(x<=2*n){c[x]+=v,x+=lowbit(x);}}
    int query(int x){int ans=0;while(x){ans+=c[x],x-=lowbit(x);}return ans;}
}T;
struct node
{
    priority_queue<int,vector<int>,greater<int> > q;
    BIT T;
    int del;
    void push(int x){q.push(x+del),T.add(x+del,1);}
    void pop(){T.add(q.top(),-1),q.pop();}
    int query(int x){return T.query(x+del);}
}S;
struct Seg
{
    int t[N<<5],tot[N<<5],lt[N<<5],rt[N<<5],cnt,root;
    void upd(int &x,int l,int r,int pos)
    {
        if(!x) x=++cnt;
        t[x]+=pos,tot[x]++;
        if(l==r) return ;
        int mid=(l+r)>>1;
        if(pos<=mid) upd(lt[x],l,mid,pos);
        else upd(rt[x],mid+1,r,pos);
    }
    int query(int x,int l,int r,int k)
    {
        if(!x) return 0;
        if(l==r) return min(tot[x],k)*l;
        else
        {
            int mid=(l+r)>>1;
            if(tot[lt[x]]>=k) return query(lt[x],l,mid,k);
            else return t[lt[x]]+query(rt[x],mid+1,r,k-tot[lt[x]]);
        }
    }
    int query(int x,int l,int r,int L,int R)
    {
        if(!x) return 0;
        if(L<=l&&r<=R) return tot[x];
        else
        {
            int mid=(l+r)>>1,k=0;
            if(L<=mid) k+=query(lt[x],l,mid,L,R);
            if(mid+1<=R) k+=query(rt[x],mid+1,r,L,R);
            return k;
        }
    }
}H,C;
int work(int x)
{
    int sum=H.query(H.root,1,1e9,S.query(x));
    // cout<<sum<<'\n';
    sum+=T.query(x+tot);
    return sum;
}
signed main()
{
    // freopen("01-02.in","r",stdin);
    // freopen("1.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    S.push(n+1),H.upd(H.root,1,1e9,1e9);
    for(int i=1;i<=n;i++)
    {
        int cnt=C.query(C.root,1,1e9,a[i]+1,1e9);
        C.upd(C.root,1,1e9,a[i]);
        if(cnt) T.add(i,a[i]),upd[cnt].push_back(i);
        else S.push(i),H.upd(H.root,1,1e9,a[i]);
    }
    // return 0;
    cin>>q;
    while(q--)
    {
        int op,l,r;
        cin>>op;
        if(op==1)
        {
            if(tot==n) continue;
            S.pop(),S.push(n+2),S.del++;
            tot++;
            for(int i:upd[tot]) T.add(i,-a[i]),S.push(i-tot),H.upd(H.root,1,1e9,a[i]);
        }
        else
        {
            cin>>l>>r;
            cout<<work(r)-work(l-1)<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：P2441M (赞：1)

## 题意

给定长度为 $n$ 的序列 $a$。$q$ 次操作，支持：

1. 对 $a$ 进行一轮冒泡。
2. 查询区间和。

$2\leq n\leq 5\times 10^5$，$1\leq q\leq 5\times 10^5$，$1\leq a_i\leq 10^9$。

## 题解

我们首先指出：设经过 $d$ 轮冒泡后得到的序列为 $a'$，则 $a'[1,x]$ 中的元素就是 $a[1,\min(x+d,n)]$ 中的元素从小到大排序后的前 $x$ 小。

**证明**：显然经过 $d$ 轮冒泡后，$a$ 中每个元素至多向前移动 $d$ 个位置，所以，只有 $a[1,\min(x+d,n)]$ 中的元素可能成为 $a'[1,x]$ 中的元素。我们将 $a$ 截断为 $a[1,\min(x+d,n)]$，由冒泡的性质，我们知道，$a[1,\min(x+d,n)]$ 中的最大值会在第 $1$ 次冒泡移动到右数第 $1$ 个位置，次大值会在第 $2$ 次冒泡移动到右数第 $2$ 个位置……因此 $d$ 轮冒泡后，$a[1,\min(x+d,n)]$ 中的前 $d$ 大都移动到了末尾，那么 $a'[1,x]$ 中自然就剩下前 $x$ 小了。$\Box$

我们把区间和差分成前缀和。设当前询问之前共冒泡了 $d$ 轮，询问 $[1,x]$ 的区间和时，转化为求 $a[1,\min(x+d,n)]$ 的前 $x$ 大之和。离线询问，按 $x$ 排序，变成支持插入一个数，查询前 $k$ 大之和。离散化一下，权值 BIT 上倍增即可维护。时间复杂度 $\mathcal{O}(n\log{n})$。

实现时，为了避免边界的讨论，离散化时不必去重。具体的细节可以看代码。

显然这种做法常数比线段树上二分或者主席树小。

## 代码

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e5 + 5, LGN = 19 + 5;

int n, q, d, a[N], p[N];
ll ans[N];
pii b[N];
int sz, szq;
struct Query {
	int id, x, k, tp;
	bool operator<(const Query &qr) const { return x < qr.x; }
} qr[N << 1];

struct BIT {
	int c1[N];
	ll c2[N];
	inline ll query(int x) {
		ll res = 0;
		for (; x; x -= lowbit(x)) res += c2[x];
		return res;
	}
	inline void add(int x, ll v) {
		ll v2 = v * b[x].first;
		for (; x <= n; x += lowbit(x)) c1[x] += v, c2[x] += v2;
	}
	inline ll sum(int k) {
		int x = 0, s = 0;
		ll res = 0;
		for (int i = LGN - 5; i != -1; --i)
			if (x + (1 << i) <= n && s + c1[x + (1 << i)] <= k)
				s += c1[x += 1 << i], res += c2[x];
		return res;
	}
} ft;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], b[i] = {a[i], i};
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; ++i) p[b[i].second] = i;
    cin >> q;
    for (int i = 1; i <= q; ++i) {
    	int op, l, r; cin >> op;
    	if (op == 1) ++d;
    	else {
    		cin >> l >> r;
    		qr[++szq] = {++sz, min(r + d, n), r, 1};
    		qr[++szq] = {sz, min(l - 1 + d, n), l - 1, -1};
    	}
    }
    sort(qr + 1, qr + szq + 1);
    for (int i = 1, j = 1; i <= szq; ++i) {
    	while (j <= qr[i].x) ft.add(p[j++], 1);
    	ans[qr[i].id] += ft.sum(qr[i].k) * qr[i].tp;
    }
    for (int i = 1; i <= sz; ++i) cout << ans[i] << '\n';
    return 0;
}
```

---

## 作者：sunkuangzheng (赞：1)

尝试去考察冒泡排序 $k$ 轮后的序列和原序列的关系，根据部分分提示~~和百度搜索结果~~可以发现：

> **观察**
>
> 设冒泡排序 $k$ 轮后的序列是 $a'$，则 $a'_i$ 是 $a_1 \sim a_{\min(n,i+k)}$ 中**未在 $a'_{1 \sim i-1}$ 中出现过的**最小值。

证明大概就是考虑 $k$ 轮后 $[1,i+k]$ 在前缀 $i$ 的交换范围内，而这个范围内所有值都可能被换过来。

于是首先计算出 $u = \min(l-1+k,n),v = \min(r+k,n)$，我们要求 $[1,v]$ 中除去 $[1,u]$ 中前 $l-1$ 小后的前 $len$ 小的和。

考虑先忽略 $k-1$ 的限制，二分出最小的 $mid$ 满足值域 $[1,mid]$ 中前缀 $[1,v]$ 恰好比 $[1,u]$ 多 $len$ 个数。如果此时 $[1,u]$ 中已经出现大于等于 $l$ 个元素，说明 $[1,v]$ 的前 $len$ 小完全包含 $[1,u]$ 的前 $l-1$ 小，直接作差即可。

以上所有步骤都可以通过主席树二分完成，复杂度 $\mathcal O(n \log n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 16.06.2025 16:21:56
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,a[N],rt[N],q,k,op,l,r,fn;
struct nd{int v,l,r; ll s;}t[N*32]; int tot;
int upd(int s,int l,int r,int x){
    int p = ++tot,mid = (l + r) / 2; t[p] = t[s],t[p].v ++,t[p].s += x;
    if(l == r) return p;
    x <= mid ? t[p].l = upd(t[p].l,l,mid,x) : t[p].r = upd(t[p].r,mid+1,r,x);
    return p;
}ll sol(int u,int v,int l,int r,int k){
    if(t[v].v - t[u].v < k) return -1;
    if(l == r) return fn += t[v].v,1ll * l * k;
    int mid = (l + r) / 2,lf = t[t[v].l].v - t[t[u].l].v;
    if(k <= lf) return sol(t[u].l,t[v].l,l,mid,k);
    return fn += t[t[v].l].v,t[t[v].l].s - t[t[u].l].s + sol(t[u].r,t[v].r,mid+1,r,k-lf);
}ll qry(int s,int l,int r,int k){
    if(l == r) return 1ll * l * k;
    int mid = (l + r) / 2,lf = t[t[s].l].v;
    if(k <= lf) return qry(t[s].l,l,mid,k);
    return t[t[s].l].s + qry(t[s].r,mid+1,r,k-lf); 
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> a[i],rt[i] = upd(rt[i-1],1,1e9,a[i]);
    cin >> q;
    for(int i = 1;i <= q;i ++){
        if(cin >> op,op == 1) k ++;
        else{
            cin >> l >> r;
            int u = min(l - 1 + k,n),v = min(r + k,n); fn = -1;
            ll x = sol(rt[u],rt[v],1,1e9,r-l+1);
            if(fn >= r || x == -1)
                cout << qry(rt[v],1,1e9,r) - qry(rt[u],1,1e9,l-1) << "\n";
            else cout << x << "\n";
        }
    }
}
```

---

## 作者：nullqtr_pwp (赞：0)

刻画一轮冒泡排序的过程：取出所有前缀最大值，从前往后考虑每个位置，将其平移到下一个前缀最大值之前，此时有一些非前缀最大值会变成前缀最大值，将其更新（每次把序列平移一位，这样非前缀最大值就不会移动）

注意到如果忽略每次操作的平移，一个位置只会变成前缀最大值所在位置而不会从前缀最大值位置变成非前缀最大值位置。于是可以使用数据结构维护前缀最大值的值与位置，根据单调性其一定按顺序一一匹配。找到新增的前缀最大值可以求出第 $i$ 个位置会在 $t_i$ 时刻变为前缀最大值（每次冒泡排序，每个非前缀最大值前面大于其的数个数恰好减一），由 $t_i$ 求答案是可以树状数组加线段树二分维护的。时间复杂度 $\mathcal O(n\log n)$。

---

