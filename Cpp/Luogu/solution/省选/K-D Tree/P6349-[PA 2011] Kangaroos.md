# [PA 2011] Kangaroos

## 题目描述

给出长为 $n$ 的序列 $a$，第 $i$ 个元素是一个区间 $[l_i,r_i]$。

$m$ 次询问，给出 $A,B$，求出 $a$ 中最长的区间（即这个序列中的一段），使得这个区间内每个区间都与 $[A,B]$ 有交集。输出这个最长区间的长度。

## 说明/提示

$1\le n\le 5\times 10^4$，$1\le m\le 2\times 10^5$，$1\le l_i\le r_i\le 10^9$，$1\le A\le B\le 10^9$

## 样例 #1

### 输入

```
3 3
2 5
1 3
6 6
3 5
1 10
7 9```

### 输出

```
2
3
0```

# 题解

## 作者：feecle6418 (赞：53)

我们对于询问做莫队。一种简单的错误想法是把 $2n$ 个端点离散化之后拿来莫队，但是假如 $l<L$，$r>R$，则询问 $[L,R]$ 是算不到 $[l,r]$ 这个区间的贡献的。也就是，这样无法处理“包含”的情况。

为了能够处理这种情况，我们考虑回滚莫队。把左端点放在所属块上，考虑右端点的位置分类讨论。

- 两端点在同一块（设为 $i$）：
  - 把包含这一块的区间先加到某个数据结构里，然后不管他们（这些一定有贡献）
  - 剩下的可能产生贡献区间（也就是至少有一端在块内的区间）只有 $O(\sqrt n)$ 个，扫一遍，加到某个数据结构里，更新答案就行
  - 这部分复杂度 $O(T(n)q\sqrt n)$
- 否则（左端点属于 $i$，右端点所属 $>i$）从左往右扫左端点在该块的询问的右端点
  - 把横跨了 $i,i+1$ 两块的区间先加到某个数据结构里，然后不管他们（这些一定有贡献）
  - 剩下的区间不可能包含询问区间了，做普通的回滚莫队即可
  - 这部分复杂度 $O(T(n)q\sqrt n)$
  
以上的“某个数据结构”需要在 $T(n)$ 复杂度内支持：

- 加入一个元素
- 询问最大的元素连续段
- 撤销最后几次操作（回滚）

用线段树实现是 $O(\log n)$ 的，其实直接用两个数组 $l,r$ 就可以 $O(1)$ 实现。具体看代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,Q,bel[200005],ass[200005],tmp[200005],st[1005],ed[1005];
struct Seg{
	int l,r,id;
}t[200005];
struct Thing{
	int x,id;
}a[200005];
struct Query{
	int l,r,id;
};
bool operator <(const Thing i,const Thing j){
	return i.x!=j.x?i.x<j.x:i.id<j.id;
}
vector<Query> q[1005];
int l[200005],r[200005],ans=0,top=0;
struct Oper{
	int c,x,ax,ans;
}S[3000005];
inline void Add(int x){
	if(l[x]||r[x])return ;
	if(!l[x-1]&&!r[x+1])S[++top]={0,x,l[x],ans},S[++top]={1,x,r[x],ans},l[x]=r[x]=x,ans=max(ans,1);
	else if(!l[x-1])S[++top]={0,r[x+1],l[r[x+1]],ans},S[++top]={1,x,r[x],ans},l[r[x+1]]=x,r[x]=r[x+1],ans=max(ans,r[x]-x+1);
	else if(!r[x+1])S[++top]={1,l[x-1],r[l[x-1]],ans},S[++top]={0,x,l[x],ans},r[l[x-1]]=x,l[x]=l[x-1],ans=max(ans,x-l[x]+1);
	else S[++top]={1,l[x-1],r[l[x-1]],ans},S[++top]={0,r[x+1],l[r[x+1]],ans},S[++top]={0,x,l[x],ans},
		 l[r[x+1]]=l[x-1],r[l[x-1]]=r[x+1],l[x]=x,ans=max(ans,r[x+1]-l[x-1]+1);
}
void Rollback(int t){
	while(top>t){
		if(!S[top].c)l[S[top].x]=S[top].ax;
		else r[S[top].x]=S[top].ax;
		ans=S[top].ans,top--;
	}
}
void Solve(int id){
	Rollback(0);
	for(int i=1;i<=n;i++)if(t[i].l<st[id]&&t[i].r>ed[id])Add(t[i].id);
	sort(q[id].begin(),q[id].end(),[](Query i,Query j){return i.r<j.r;});
	int tp=top,cur=ed[id];
	for(Query i:q[id]){
		if(i.r>ed[id])continue;
		for(int j=st[id];j<=ed[id];j++)if(i.l<=t[a[j].id].r&&t[a[j].id].l<=i.r)Add(a[j].id);
		ass[i.id]=ans,Rollback(tp);
	}
	Rollback(0);
	for(int i=1;i<=n;i++)if(t[i].l<=ed[id]&&t[i].r>ed[id])Add(t[i].id);
	for(Query i:q[id]){
		if(i.r<=ed[id])continue;
		while(cur<i.r)Add(a[++cur].id);
		tp=top;
		for(int j=ed[id];j>=i.l;j--)Add(a[j].id);
		ass[i.id]=ans,Rollback(tp);
	}
}
int main() {
	scanf("%d%d",&n,&Q);
	for(int i=1,l,r;i<=n;i++)scanf("%d%d",&l,&r),a[i]={l,i},a[i+n]={r,i},t[i]={l,r,i};
	sort(a+1,a+2*n+1);
	for(int i=1;i<=n;i++){
		t[i].l=lower_bound(a+1,a+2*n+1,(Thing){t[i].l,0})-a;
		t[i].r=upper_bound(a+1,a+2*n+1,(Thing){t[i].r,1<<30})-a-1;
	}
	int SQ=sqrt(2*n);
	for(int i=2*n;i>=1;i--)bel[i]=i/SQ+1,st[bel[i]]=i;
	for(int i=1;i<=2*n;i++)ed[bel[i]]=i;
	for(int i=1,l,r;i<=Q;i++){
		scanf("%d%d",&l,&r);
		l=lower_bound(a+1,a+2*n+1,(Thing){l,0})-a;
		r=upper_bound(a+1,a+2*n+1,(Thing){r,1<<30})-a-1;
		q[bel[l]].push_back((Query){l,r,i});
	}
	for(int i=1;i<=bel[2*n];i++)if(q[i].size())Solve(i);
	for(int i=1;i<=Q;i++)printf("%d\n",ass[i]);
	return 0;
}
```

---

## 作者：gyh20 (赞：24)

提供一个全新的分块做法，感谢@时间有泪 多次将算法救活。

令块大小为 $T$ ，时间复杂度 $O(Tn\log n+\dfrac{mn\log T}{T})$，目前的最优解。

首先，我们如何判断一个区间 $[L,R]$ 是否与一个区间所有的 $[l_i,r_i]$ 相交？

两条线段 $[L,R],[l,r]$ 有交，当且仅当 $L\leq r$ 且 $l\leq R$。

那么一条线段与这些线段都有交当且仅当 $L\leq \min(r_i),R\geq \max(l_i)$。

于是，可以预处理每一个块内前缀后缀的 $\max,\min$。

但是，这样会有一类贡献统计不到，就是答案区间在一个块内。

我们可以提前把所有长度小于 $\sqrt n$ 的子区间取出来，看成一个二维点对 $(x,y)$，$x$ 为 $l$ 的最大值， $y$ 为 $r$ 的最小值，用数据结构维护一下即可。

当然，这样做很容易被卡常，一些优化：

$1.$ 如果您用的是树套树维护，您的预处理就多了一个 $\log$，但是，可以开桶优化（可以看下面的代码），优化到一个 $\log$。

$2.$ 可以把所有长度小于 $2\sqrt n$ 的子区间取出来，这样其余的答案一定包含一个整块，那么遇到整块时再二分。

$3.$ 再不可能最优时不二分。

$4.$ 我的写法块大小在 $100$ 时比较优。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
const int Mxdt=100000;	//单次大小 
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline char pc(char ch,bool bj){
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return (bj||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
void print(int x)
{
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
inline void printnum(int x,char ch)
{
	print(x),pc(ch,false);
}
inline int read(){
	re int t=0;re char v=gc();
	while(v<'0')v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return t;
}
const int blk=120,N=50000/blk+10;
int n,m,a[50002],b[50002],p[100002],cnt,rt[100002],prel[N][blk+1],sufl[N][blk+1],prer[N][blk+1],sufr[N][blk+1],tr[400002],ans,st[N],ed[N],bl[100002],L[N],R[N],ls[9000002],rs[9000002],mx[9000002],tot,ll[100002][402];
inline void add(re int &p,re int l,re int r,re int x,re int z){
	if(!p)p=++tot;
	mx[p]=max(mx[p],z);
	if(l==r)return;
	re int mid=l+r>>1;
	if(x<=mid)add(ls[p],l,mid,x,z);
	else add(rs[p],mid+1,r,x,z);
}
inline int ask(re int p,re int l,re int r,re int x,re int y){
	if(l>=x&&r<=y)return mx[p];
	re int mid=l+r>>1,s=0;
	if(x<=mid)s=max(s,ask(ls[p],l,mid,x,y));
	if(y>mid)s=max(s,ask(rs[p],mid+1,r,x,y));
	return s;
}
inline void add(re int x,re int y,re int z){
	for(;x<=cnt;x+=x&(-x)){
		ll[x][z]=max(ll[x][z],y);
	}
}
inline void ask(re int x,re int y){
	for(;x;x-=x&(-x))ans=max(ans,ask(rt[x],1,cnt,y,cnt));
}
inline int finds(re int p,re int x,re int y){
	re int l=1,r=ed[p]-st[p]+1,s=0;
	while(l<=r){
		re int mid=l+r>>1;
		if(sufl[p][mid]<=y&&sufr[p][mid]>=x)s=mid,l=mid+1;
		else r=mid-1;
	}
	return s;
}
inline int findp(re int p,re int x,re int y){
	re int l=1,r=ed[p]-st[p]+1,s=0;
	while(l<=r){
		re int mid=l+r>>1;
		if(prel[p][mid]<=y&&prer[p][mid]>=x)s=mid,l=mid+1;
		else r=mid-1;
	}
	return s;
}
int main(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i){a[i]=read(),b[i]=read(),p[++cnt]=a[i],p[++cnt]=b[i],bl[i]=(i-1)/blk+1,ed[bl[i]]=i;if(!st[bl[i]])st[bl[i]]=i;}p[++cnt]=2e9;
	sort(p+1,p+cnt+1),cnt=unique(p+1,p+cnt+1)-p-1;
	for(re int i=1;i<=n;++i)a[i]=lower_bound(p+1,p+cnt+1,a[i])-p,b[i]=lower_bound(p+1,p+cnt+1,b[i])-p;
	for(re int i=1;i<=n;++i){
		re int tmpx=0,tmpy=cnt;
		for(re int j=i;j<=min(i+blk*2-1,n);++j)tmpx=max(tmpx,a[j]),tmpy=min(tmpy,b[j]),add(tmpx,tmpy,j-i+1);
	}
	for(re int i=1;i<=cnt;++i)for(re int j=1;j<=blk*2;++j)if(ll[i][j])add(rt[i],1,cnt,ll[i][j],j);
	for(re int i=1;i<=bl[n];++i){
		prel[i][0]=L[i]=1,prer[i][0]=R[i]=cnt;
		for(re int j=st[i];j<=ed[i];++j)prel[i][j-st[i]+1]=max(prel[i][j-st[i]],a[j]),prer[i][j-st[i]+1]=min(prer[i][j-st[i]],b[j]),L[i]=max(L[i],a[j]),R[i]=min(R[i],b[j]);
		sufl[i][0]=1,sufr[i][0]=cnt;
		for(re int j=ed[i];j>=st[i];--j)sufl[i][ed[i]-j+1]=max(sufl[i][ed[i]-j],a[j]),sufr[i][ed[i]-j+1]=min(sufr[i][ed[i]-j],b[j]);
	}
	while(m--){
		re int l=read(),r=read();ans=0;
		l=lower_bound(p+1,p+cnt+1,l)-p,r=upper_bound(p+1,p+cnt+1,r)-p-1;
		for(re int i=1,j;i<=bl[n];i=j+1){
			re int sum=0;
			j=i;
			while(L[j]<=r&&R[j]>=l)sum+=ed[j]-st[j]+1,++j;
			--j;
			if(j<i){++j;continue;}
			if(sum+ed[i-1]-st[i-1]+1+ed[j+1]-st[j+1]+1<=ans)continue;
			if(i-1)sum+=finds(i-1,l,r);
			if(j!=bl[n])sum+=findp(j+1,l,r);
			ans=max(ans,sum);
			if(j<i)j=i;
		}
		ask(r,l);
		printnum(ans,'\n');
	}
	return pc('0',1);
}
```


---

## 作者：_虹_ (赞：16)

## **朴实无华，但快乐的O($n\sqrt{n}$)莫队。**



显然这题的询问需要的信息是很难快速合并的，我们可以考虑使用莫队**优化暴力**。

然后我们可以毫不费力的设计出一个O($n\sqrt{nlogn}$)的莫队，即按照莫队的循序处理询问，同时使用线段树在边界移动时维护最长连续段。

但是log数据结构和根号算法八字不合，我们考虑一下有什么办法搞掉这个log。

~~虽然你写个带log的卡卡常一样能过就是很危险。~~


------------


我们思考，具体什么操作需要依靠线段树维护的信息来处理。

这里操作很显然只有两个，就是添加和删除。

同样很显然的是，添加完全不需要分治操作，因为我们只询问全局最长连续段，而不关心某个位置所属的连续段长度。我们只需要在一个连续段的左右两端记录其长度，合并的时候更新即可。

那我们的问题就来到删除了，显然按照上面的处理方式，删除是困难的，因为我们不知道当前位置所处的连续段两边在哪，也就没法快速分裂一个连续段。

信息**易添加，难删除**。**回滚莫队**的标志特征。

我们使用一个**可回退化数组**处理上面的插入操作即可，每次处理询问先定位右端点r，再把l从所属块右端点移动到询问的位置，记录答案，回滚左端点l即可。

一般的可回退化数据结构允许撤销任意次修改，但这里没必要实现一个通用的可回退化数组。显然我们每次回滚都是回滚到一个特定的版本。我们只需要对于左端点移动产生的操作，记录影响的点和影响前的值，回滚时根据记录的受影响点，直接用影响前的值覆盖回去即可。

------------
### 要注意几点：
1.  回滚莫队**不能**处理**两端点在同一块中**的询问，这些询问要按所属块放到一起处理。显然**包含当前块的区间一定包含其中的询问**，我们扫出这些区间，剩下的区间只会是端点在当前块中的，每个询问扫一下当前块，使用另一个可回退化数组维护即可。
2. 莫队只能处理出**两端点至少一个在询问区间内**的区间，对于包含询问区间的区间，**显然包含当前询问所属块的右端点（注意不一定包含整个块）**（不跨块的我们在上面按块分组一起暴力），同样先预处理再做莫队。
3. 换块处理时候别忘了清空数组和答案，回滚时候别忘了回滚答案。


------------


常数不大，甚至用了vector依旧跑的飞快。快乐rk1。~~建议改为：香 港 记 者~~
![提交](https://cdn.luogu.com.cn/upload/image_hosting/k1j7skwa.png)


```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
using namespace std;
const int kmaxn=200000+5;
struct Array
{
	int a[kmaxn];
	int vis[kmaxn];
	int rv[kmaxn];
	int t[kmaxn],st;
	inline const int operator[](const int i)const
	{
		return a[i];
	}
	inline void mod(int x,int v)
	{
		if(vis[x])
			a[x]=v;
		else
		{
			t[++st]=x;
			vis[x]=1;
			rv[x]=a[x];
			a[x]=v;
		}
	}
	inline void set(int x,int v)
	{
		a[x]=v;
	}
	void cancel_all()
	{
		int tp;
		while(st)
		{
			tp=t[st--];
			a[tp]=rv[tp];
			vis[tp]=0;
		}
	}
	void clear(int n)
	{
		for(int i=1;i<=n;++i)
			a[i]=rv[i]=vis[i];
		st=0;
	}
};
typedef pair<int,int> PR;
Array tb1,tb2;
PR a[kmaxn];
PR seg[kmaxn];
vector<PR> ask[kmaxn];
int trs[kmaxn];
int LE[kmaxn];
int n,m,bs;
inline int BK(int i){return (i-1)/bs+1;}
inline int BR(int i){return min(i*bs,n);}
inline int BL(int i){return BR(i-1)+1;}
inline int TL(int x)
{
	return lower_bound(trs+1,trs+1+n,x)-trs;
}
inline int TR(int x)
{
	return upper_bound(trs+1,trs+1+n,x)-trs-1;
}
int res1,res2,ans[kmaxn];
void add1(int x,Array& tb,int &res)
{
	if(tb[x]!=0)return;
	int dl,dr,len;
	dl=tb[x-1];
	dr=tb[x+1];
	len=dl+dr+1;
	tb.set(x-dl,len);
	tb.set(x+dr,len);
	tb.set(x,len);
	res=max(len,res);
}
void add2(int x,Array& tb,int &res)
{
	if(tb[x]!=0)return;
	int dl,dr,len;
	dl=tb[x-1];
	dr=tb[x+1];
	len=dl+dr+1;
	tb.mod(x-dl,len);
	tb.mod(x+dr,len);
	tb.mod(x,len);
	res=max(len,res);
}
int nb;
bool ck(int k,int l,int r)
{
	int tl=seg[k].first,tr=seg[k].second;
	return !(tr<l||tl>r);
}
int brute(int b,int l,int r)
{
	int k=n/2,tl=BL(b),tr=BR(b);
	if(nb!=b)
	{
		nb=b;	
		tb2.clear(n);
		res2=0;
		for(int i=1;i<=k;++i)
		{
			if(seg[i].first<tl&&seg[i].second>tr)
				add1(i,tb2,res2);
		}
	}
	int tres=res2,p=0;
	for(int i=tl;i<=tr;++i)
	{
		p=a[i].second;
		if(ck(p,l,r))
			add2(p,tb2,res2);
	}
	swap(tres,res2);
	tb2.cancel_all();
	return tres;
}
void solve(int b)
{
	int l,r,tl,tr,tres,k;//[l,r),[tl,tr]
	tb1.clear(n/2);
	res1=0;
	l=r=k=BR(b);
	for(int i=n/2;i>0;--i)
	{
		if(ck(i,r,r))
			add1(i,tb1,res1);
	}
	for(auto p:ask[b])
	{
		tl=LE[p.second];
		tr=p.first;
		if(tr<=k)
		{
			ans[p.second]=brute(b,tl,tr);
			continue;
		}
		while(r<=tr)
			add1(a[r++].second,tb1,res1);
		tres=res1;
		while(l>tl)
			add2(a[--l].second,tb1,res1);
		ans[p.second]=res1;
		tb1.cancel_all();
		res1=tres;
		l=k;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		cin>>seg[i].first>>seg[i].second;
		a[i].first=trs[i]=seg[i].first;
		a[i+n].first=trs[i+n]=seg[i].second;
		a[i].second=a[i+n].second=i;
	}
	n*=2;
	bs=sqrt(n);
	sort(trs+1,trs+1+n);
	sort(a+1,a+1+n);
	PR tp;
	for(int i=n/2;i>0;--i)
	{
		seg[i].first=TL(seg[i].first);
		seg[i].second=TR(seg[i].second);
	}
	for(int i=1;i<=m;++i)
	{
		cin>>LE[i]>>tp.first;
		LE[i]=TL(LE[i]);
		tp.first=TR(tp.first);
		tp.second=i;
		ask[BK(LE[i])].push_back(tp);
	}
	for(int i=1;BL(i)<=n;++i)
	{
		if(ask[i].empty())continue;
		sort(ask[i].begin(),ask[i].end());
		solve(i);
	}
	for(int i=1;i<=m;++i)
		cout<<ans[i]<<'\n';
	return 0;
}
```
为什么会有学弟搞出k-d树这种神仙做法？？？？

强的离谱，i了i了。

---

## 作者：lhm_ (赞：12)

先考虑对题目进行转化，我们称两个区间有交集为这两个区间能匹配，每个询问就是在序列中最长能连续匹配的长度。

对序列中的一个区间$[l,r]$和询问的一个区间$[L,R]$，若满足$L \leqslant r$且$l \leqslant R$，那么这两个区间是能匹配的。

可以将一个区间用点来表示，然后用$K-D\ Tree$来维护所有的询问区间，序列区间按顺序一个个去更新每个询问的匹配信息即可。

对$K-D\ Tree$中的维护一个矩形来考虑，比如下图的蓝色矩形为这个矩形。

当一个点落在红色矩形时，那么该点和矩形内的所有点都能匹配，对该矩形打上加法标记，使矩形内所有点的当前匹配数加一。

当一个点落在黄色矩形时，那么该点和矩形内的所有点都不能匹配，对该矩形打上清零标记，使矩形内所有点的当前匹配数清零。

![](https://s1.ax1x.com/2020/04/12/GqtQ0K.png)

同时记录一个点在整个过程中的历史最大匹配数，其即为最终一个点所对应询问的答案。

对一个矩形清空后，还会进行一系列对其匹配数增加的操作，但此时打上加法标记是错误的，所以给它打上一个赋值标记，打标记时增加赋值标记即可，同时记录下这阶段赋值标记的历史最大值，并用其去更新该点的历史最大匹配数。

标记比较多，有很多细节，具体实现看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 400010
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,root,tot,type;
int cov[maxn],his[maxn],add[maxn],tag[maxn];
int ans[maxn],ma[maxn],cnt[maxn];
struct node
{
    int l,r;
}p[maxn];
struct KD_tree
{
    int d[2],mi[2],ma[2],ls,rs,id;
}t[maxn],dat[maxn];
bool cmp(const KD_tree &a,const KD_tree &b)
{
    return a.d[type]<b.d[type];
}
void pushup(int x)
{
    int ls=t[x].ls,rs=t[x].rs;
    for(int i=0;i<=1;++i)
    {
        t[x].ma[i]=t[x].mi[i]=t[x].d[i];
        if(ls)
        {
            t[x].ma[i]=max(t[x].ma[i],t[ls].ma[i]);
            t[x].mi[i]=min(t[x].mi[i],t[ls].mi[i]);
        }
        if(rs)
        {
            t[x].ma[i]=max(t[x].ma[i],t[rs].ma[i]);
            t[x].mi[i]=min(t[x].mi[i],t[rs].mi[i]);
        }
    }
}
void update(int x,int v)
{
    cnt[x]+=v,ma[x]=max(ma[x],cnt[x]);
}
void pushadd(int x,int v)
{
    update(x,v);
    if(cov[x]) tag[x]+=v,his[x]=max(his[x],tag[x]);
    else add[x]+=v;
}
void pushcov(int x)
{
    if(!cov[x]) cov[x]=1,his[x]=0;
    cnt[x]=tag[x]=0;
}
void pushtag(int x,int v1,int v2)
{
    cov[x]=1,his[x]=max(his[x],v2);
    cnt[x]=tag[x]=v1,ma[x]=max(ma[x],his[x]);
}
void pushdown(int x)
{
    int ls=t[x].ls,rs=t[x].rs;
    if(add[x])
    {
        pushadd(ls,add[x]),pushadd(rs,add[x]);
        add[x]=0;
    }
    if(cov[x])
    {
        pushtag(ls,tag[x],his[x]),pushtag(rs,tag[x],his[x]);
        cov[x]=tag[x]=0;
    }
}
void build(int l,int r,int k,int &x)
{
    x=++tot,type=k;
    int mid=(l+r)>>1;
    nth_element(dat+l+1,dat+mid+1,dat+r+1,cmp);
    t[x]=dat[mid];
    if(l<mid) build(l,mid-1,k^1,t[x].ls);
    if(r>mid) build(mid+1,r,k^1,t[x].rs);
    pushup(x);
}
bool in(KD_tree tr,int l,int r)
{
    return tr.ma[0]<=r&&l<=tr.mi[1];
}
bool out(KD_tree tr,int l,int r)
{
    return tr.mi[0]>r||l>tr.ma[1];
}
void modify(int x,int l,int r)
{
    int ls=t[x].ls,rs=t[x].rs;
    if(in(t[x],l,r))
    {
        pushadd(x,1);
        return;
    }
    if(out(t[x],l,r))
    {
        pushcov(x);
        return;
    }
    pushdown(x);
    if(t[x].d[0]<=r&&l<=t[x].d[1]) update(x,1);
    else cnt[x]=0;
    if(ls) modify(ls,l,r);
    if(rs) modify(rs,l,r);
}
void dfs(int x)
{
    int ls=t[x].ls,rs=t[x].rs;
    pushdown(x),ans[t[x].id]=ma[x];
    if(ls) dfs(ls);
    if(rs) dfs(rs);
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i) read(p[i].l),read(p[i].r);
    for(int i=1;i<=m;++i)
        read(dat[i].d[0]),read(dat[i].d[1]),dat[i].id=i;
    build(1,m,0,root);
    for(int i=1;i<=n;++i) modify(root,p[i].l,p[i].r);
    dfs(root);
    for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：tzc_wk (赞：7)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P6349)

KDT 上打标记的 hot tea。

考虑将询问 $A,B$ 看作二维平面直角坐标系上的一个点 $(A,B)$，那么我们这样考虑，我们从左到右扫过全部 $n$ 个区间并开一个变量 $cnt$ 表示当前与 $[l_i,r_i]$ 有交的区间的最大长度，如果当前扫描到的区间 $[l_i,r_i]$ 与区间 $[A,B]$ 有交，那么我们就令 $cnt$ 加 $1$，否则 $cnt$ 清空，答案就是任意时刻最大的 $cnt$。

显然如果我们暴力地对所有区间都重复一遍这个操作那时间复杂度肯定爆炸，考虑如何优化，我们将所有询问离线下来并一遍扫过全部 $n$ 个区间处理所有询问，不难发现对于一个区间 $[l_i,r_i]$ 而言，与其没有交的询问对应的点肯定会落在两个矩形内，因此我们每次需要做的即是：

- 将某两个矩形中所有点的权值清零。
- 将不在这两个矩形中的所有点权值加一

最后要求的即是每个节点权值的历史最大值。

考虑对这 $m$ 个询问点建立 KDT，那么根据 KDT 那一套理论，我们可以将矩形上的操作转化为 $\sqrt{n}$ 个单点操作 $+$ $\sqrt{n}$ 个子树操作。单点操作是容易的，难点在于子树操作，因此我们现在要实现的即为：

- 将子树内所有点权值清零
- 将子树内所有点权值加一

对求解历史最大值线段树比较了解的同学到这一步应该会做了。但是我对理是最大值线段树不是太了解，因此这里会较为详细地讲解一下如何用历史最大值的标记解决这个问题。我们考察一个点上一次标记下推到现在一共经历了哪些过程，有两种可能，要么没有被清空，权值直接被加上了一个数 $v$。要么曾经被清空过，一开始先 $+v_0$，然后清空，又加了 $v_1$，再清空，$+v_2$，清空，……，最后 $+v_m$，值为 $v_m$。不难发现由于我们只关心历史最大值，因此 $v_1,v_2,\cdots,v_m$ 具体是什么不重要，我们只用关心以下几个值：

- 第一次加的值 $v_0$，程序中用 $add\_mx$ 表示。
- 这个值从上一次被标记下推是否被清空，$clr$。
- $\max{v_1,v_2,\cdots,v_m}$，程序中用 $cov\_mx$ 表示。
- 这个位置当前的值 $v_m$，程序中用 $tg$ 表示。

当然除了这四个标记之外，还有每个位置的权值 $v$ 以及历史最大值 $hmx$。

考虑对一个子树清空/整体加值会对标记产生怎样的影响。首先是子树清空，这个比较容易，直接将 $clr$ 设为 $1$，$tg,v$ 设为 $0$ 即可。其次是整体加值，如果 $clr\ne 0$ 那就令 $tg$ 加 $v$，并将 $cov\_mx$ 对 $tg$ 取 $\max$，否则令 $add\_mx$ 加 $v$。

然后是下推标记的问题，如果 $clr=0$ 那么直接对左右儿子进行整体 $+add\_mx$ 操作即可。否则操作等价于先对左右儿子进行 $+add\_mx$，然后 $+v_1$，清空，$+v_2$，清空，……，最后 $+v_m$，这等价于先对左右儿子进行整体 $+add\_mx$ 操作，然后令左右儿子的 $cov\_mx$ 对该节点的 $cov\_mx$ 取 $\max$，然后令左右儿子的 $tg$ 和 $v$ 都等于 $tg$。注意每次操作之后都要实时更新 $hmx$。

时间复杂度 $n\sqrt{m}$。

```cpp
const int MAXN=2e5;
const int K=2;
int n,m,res[MAXN+5];pii a[MAXN+5];
struct point{
	int x[K+2],id;
	point(){memset(x,0,sizeof(x));id=0;}
	int& operator [](int id){return x[id];}
} p[MAXN+5];
struct node{int ch[2],v,hmx,add_mx,cov_mx,tg,clr;point val,mn,mx;} s[MAXN+5];
int ncnt=0,rt=0;
void build(int &k,int l,int r){
	if(l>r) return;k=++ncnt;
	static double avg[K+2],var[K+2];
	fill(avg,avg+K,0);fill(var,var+K,0);
	for(int i=l;i<=r;i++) for(int j=0;j<K;j++) avg[j]+=p[i][j];
	for(int j=0;j<K;j++) avg[j]/=(r-l+1);
	for(int i=l;i<=r;i++) for(int j=0;j<K;j++) var[j]+=(p[i][j]-avg[j])*(p[i][j]-avg[j]);
	double mx=0;int dim=0;
	for(int j=0;j<K;j++) if(mx<var[j]) mx=var[j],dim=j;
	int mid=l+r>>1;
	nth_element(p+l,p+mid,p+r+1,[&](point x,point y){return x[dim]<y[dim];});
	build(s[k].ch[0],l,mid-1);build(s[k].ch[1],mid+1,r);
	s[k].val=s[k].mn=s[k].mx=p[mid];
	for(int i=0;i<K;i++){
		if(s[k].ch[0]) chkmin(s[k].mn[i],s[s[k].ch[0]].mn[i]),chkmax(s[k].mx[i],s[s[k].ch[0]].mx[i]);
		if(s[k].ch[1]) chkmin(s[k].mn[i],s[s[k].ch[1]].mn[i]),chkmax(s[k].mx[i],s[s[k].ch[1]].mx[i]);
	}
}
void tagclr(int k){s[k].clr=1;s[k].tg=0;s[k].v=0;}
void tagadd(int k,int v){
	s[k].v+=v;chkmax(s[k].hmx,s[k].v);s[k].tg+=v;
	if(s[k].clr) chkmax(s[k].cov_mx,s[k].tg);
	else chkmax(s[k].add_mx,s[k].tg);
}
void pushdown(int k){
	if(s[k].add_mx){
		if(s[k].ch[0]) tagadd(s[k].ch[0],s[k].add_mx);
		if(s[k].ch[1]) tagadd(s[k].ch[1],s[k].add_mx);
		s[k].add_mx=0;
	} if(s[k].clr){
		if(s[k].ch[0]){
			s[s[k].ch[0]].clr=1;
			chkmax(s[s[k].ch[0]].cov_mx,s[k].cov_mx);
			chkmax(s[s[k].ch[0]].hmx,s[k].cov_mx);
			s[s[k].ch[0]].tg=s[k].tg;
			s[s[k].ch[0]].v=s[k].tg;
		} if(s[k].ch[1]){
			s[s[k].ch[1]].clr=1;
			chkmax(s[s[k].ch[1]].cov_mx,s[k].cov_mx);
			chkmax(s[s[k].ch[1]].hmx,s[k].cov_mx);
			s[s[k].ch[1]].tg=s[k].tg;
			s[s[k].ch[1]].v=s[k].tg;
		} s[k].cov_mx=s[k].clr=0;
	} s[k].tg=0;
}
void clrpt(int k){pushdown(k);s[k].v=0;}
void addpt(int k,int v){pushdown(k);s[k].v+=v;chkmax(s[k].hmx,s[k].v);}
void modify(int k,int l,int r){
	if(!k) return;
	if(s[k].mn[0]>r||s[k].mx[1]<l) return tagclr(k),void();
	if(l<=s[k].mn[1]&&s[k].mx[0]<=r) return tagadd(k,1),void();
	pushdown(k);
	if(s[k].val[0]>r||s[k].val[1]<l) clrpt(k);
	else addpt(k,1);
	modify(s[k].ch[0],l,r);modify(s[k].ch[1],l,r);
}
void dfs(int k){
	if(!k) return;res[s[k].val.id]=s[k].hmx;
	pushdown(k);dfs(s[k].ch[0]);dfs(s[k].ch[1]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].fi,&a[i].se);
	for(int i=1;i<=m;i++) scanf("%d%d",&p[i][0],&p[i][1]),p[i].id=i;
	build(rt,1,m);
	for(int i=1;i<=n;i++) modify(rt,a[i].fi,a[i].se);
	dfs(rt);
	for(int i=1;i<=m;i++) printf("%d\n",res[i]);
	return 0;
}
/*
8 2
4 5
5 6
2 4
1 3
5 7
6 7
1 6
2 5
4 7
4 5
*/
```



---

## 作者：1234567s (赞：5)

这道题目维护区间交集，二维信息，并且 CDQ 等不能差分，考虑使用 KDT 来实现这一过程。  
将新线段加入，有交的部分当前可行连续段长度 $+1$，如果不行则赋值为 $0$，当前无法继续连续。  
又因为要维护最长的一次，那么就是 KDT 上维护区间，区间覆盖，单点历史最值，比较常见（因为结构类似线段树），例如 [P4314 CPU监控](https://www.luogu.com.cn/problem/P4314)。  
写的时候注意一点就没问题了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500005
namespace lzz
{
	int n,m,k=2;
	struct node
	{
		int x[2],id;
	}p[N];
	int now_k;
	int ans[N];
	bool cmp(node x,node y){return x.x[now_k]<y.x[now_k];}
	struct kkk
	{
		node s;
		int ls,rs,size,L[2],R[2];

		int max;
		int his_max;
		int add,max_add;//加法标记 
		int tag,max_tag;//被覆盖后的最大值 
		//和CPU实现其实一样
		void init(){ls=rs=0,max=0,his_max=0,add=max_add=0,tag=max_tag=-1e9;}
	};
	struct KDT
	{
		kkk tree[N];
		int stk[N],top=0,cnt=0;
		int new_node()
		{
			int u=(top)?stk[top--]:++cnt;
			tree[u].init(); return u;
		}
		void pushup(int u)
		{
			int ls=tree[u].ls,rs=tree[u].rs;
			for(int i=0;i<=k-1;i++)
			{
				tree[u].L[i]=tree[u].R[i]=tree[u].s.x[i];
				if(ls)tree[u].L[i]=min(tree[u].L[i],tree[ls].L[i]),tree[u].R[i]=max(tree[u].R[i],tree[ls].R[i]);
				if(rs)tree[u].L[i]=min(tree[u].L[i],tree[rs].L[i]),tree[u].R[i]=max(tree[u].R[i],tree[rs].R[i]);		
			}tree[u].size=tree[tree[u].ls].size+tree[tree[u].rs].size+1;//维护单点即可 
		}
		int build(int l,int r,int s_k)
		{
			if(l>r)return 0;
			int mid=(l+r)>>1,u=new_node();
			now_k=s_k,nth_element(p+l,p+mid,p+r+1,cmp),tree[u].s=p[mid];
			tree[u].ls=build(l,mid-1,(s_k+1)%k),tree[u].rs=build(mid+1,r,(s_k+1)%k);
			pushup(u);return u;
		}
		void add(int u,int val,int max_val)
		{
			tree[u].his_max=max(tree[u].his_max,tree[u].max+max_val);
			tree[u].max=tree[u].max+val;
			if(tree[u].tag==-1e9)
			{
				
				tree[u].max_add=max(tree[u].max_add,tree[u].add+max_val);//上面最值传下来 
				tree[u].add+=val;
			}
			else
			{
				tree[u].max_tag=max(tree[u].max_tag,tree[u].tag+max_val);//最优覆盖标记
				tree[u].tag+=val; 
			}
		}
		void tag(int u,int val,int max_val)
		{
			tree[u].add=0; 
			tree[u].max=val,tree[u].tag=val;
			tree[u].his_max=max(tree[u].his_max,max_val);
			tree[u].max_tag=max(tree[u].max_tag,max_val);
		}
		void pushdown(int u)
		{
			if(tree[u].add||tree[u].max_add)//有更优选择 
			{
				if(tree[u].ls)add(tree[u].ls,tree[u].add,tree[u].max_add);
				if(tree[u].rs)add(tree[u].rs,tree[u].add,tree[u].max_add);
				tree[u].add=0,tree[u].max_add=0;
			} 
			if(tree[u].tag!=-1e9)//会覆盖 
			{
				if(tree[u].ls)tag(tree[u].ls,tree[u].tag,tree[u].max_tag);
				if(tree[u].rs)tag(tree[u].rs,tree[u].tag,tree[u].max_tag);
				tree[u].tag=-1e9,tree[u].max_tag=-1e9;
			}
		}
		//接下来注意单点修改不能打标记
		void node_tag(int u,int val)
		{
			pushdown(u);
			tree[u].max=val;
			tree[u].his_max=max(tree[u].his_max,val);
		} 
		void node_add(int u,int val)
		{
			pushdown(u);
			tree[u].max+=val;//上面标记传完,这就是真实的值 
			tree[u].his_max=max(tree[u].his_max,tree[u].max);
		} 
		void modify(int u,int l,int r)//这道题只存在修改操作(分别判交区间) 
		{
			if(!u)return ;
			if(l>tree[u].R[1]||r<tree[u].L[0])//比最大的右端点还大(这个区间都不行,tag0) 
			{
				tag(u,0,0);
				return ;
			}
			//但l>R||r<L时无交
			//那么就要使l<=最小的R,r>=最大的l 
			if(l<=tree[u].L[1]&&tree[u].R[0]<=r)
			{
				add(u,1,1);//最大的也只有1 
				return ;
			}
			pushdown(u); 
			if(l>tree[u].s.x[1]||r<tree[u].s.x[0])node_tag(u,0);
			else node_add(u,1);
			modify(tree[u].ls,l,r),modify(tree[u].rs,l,r);
		}
		void dfs(int u)
		{
			if(!u)return ;
			ans[tree[u].s.id]=tree[u].his_max;
			pushdown(u),dfs(tree[u].ls),dfs(tree[u].rs);
		}
	}kdt;
	int rt;
	int L[N],R[N];
	int main()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d%d",&L[i],&R[i]);
		for(int i=1;i<=m;i++)
		{
			int l,r;
			scanf("%d%d",&l,&r),p[i]={l,r,i};
		}rt=kdt.build(1,m,0);
		for(int i=1;i<=n;i++)kdt.modify(rt,L[i],R[i]);
		kdt.dfs(rt);
		for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
		return 0;
	}
}
int main()
{
	return lzz::main();
}
```

---

## 作者：Masterwei (赞：2)

提供一个比较劣的 $O(q\sqrt n\log n)$ 的做法。

首先转化一下题意，直接去算最长的区间长度是困难的，于是对于每个询问，我们可以考虑去找**最长的区间**分别往外**扩展一步**所得的那两个**与当前询问的区间无交**的点，答案就是这两个点的位置差再减 $1$。

思考了一下似乎并没有什么简单的 poly 做法，由于没有询问，那么考虑直接莫队，直接用一个 set 即可做的 $O(q\sqrt n\log n)$，实测 3s 就能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=2e5+5,B=77;
int n,q;
struct node{
	int val,id;
	inline bool operator<(const node&b)const{
		return val<b.val;
	}
}a[Maxn],c[Maxn];
struct Query{
	int l,r,id;
}Q[Maxn];
int ans[Maxn];
int belong[Maxn];
set<int>s;
int val[Maxn],ku[Maxn];
inline void add_(int x,int p){
	if(!x)return;
	val[x]+=p;ku[x/200]+=p;
}
inline int query(){
	int now=0,res=0;
	for(int i=0;i*200<=n;i++)if(ku[i])now=i;
	for(int i=now*200;i<now*200+200;i++)if(val[i])res=i;
	return res;
}
inline void del(int x){
	if(!x)return;
	if(s.find(x)!=s.end())assert(0);
	auto it=s.lower_bound(x);
	int nxt=*it,pre=*prev(it);
	add_(nxt-pre-1,-1);
	add_(x-pre-1,1);add_(nxt-x-1,1);
	s.insert(x);
}
inline void add(int x){
	if(!x)return;
	if(s.find(x)==s.end())assert(0);
	auto it=s.find(x);
	int pre=*prev(it);it++;
	int nxt=*it;s.erase(s.find(x));
	add_(x-pre-1,-1);add_(nxt-x-1,-1);
	add_(nxt-pre-1,1);
}
int main(){
	n=read();q=read();
	s.insert(0);s.insert(n+1);
	for(int i=1;i<=n;i++){
		c[i]={read(),i};a[i]={read(),i};
		belong[i]=i/B;
	}add_(n,1);
	sort(a+1,a+1+n,[&](node i,node j){return i.val<j.val;});
	sort(c+1,c+1+n,[&](node i,node j){return i.val<j.val;});
	int qcnt=0;
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		l=lower_bound(a+1,a+1+n,(node){l,0})-a;
		r=upper_bound(c+1,c+1+n,(node){r,0})-c-1;
		Q[i]={l,r,i};
	}
	sort(Q+1,Q+1+q,[&](Query i,Query j){return belong[i.r]==belong[j.r]?(belong[i.r]&1?i.l<j.l:i.l>j.l):belong[i.r]<belong[j.r];});
	int l=1,r=n;
	for(int i=1;i<=q;i++){
		while(Q[i].l<l)add(a[--l].id);
		while(Q[i].r>r)add(c[++r].id);
		while(Q[i].l>l)del(a[l++].id);
		while(Q[i].r<r)del(c[r--].id);
		ans[Q[i].id]=query();
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}

```

---

## 作者：mRXxy0o0 (赞：2)

神奇的 KDT 分治（主要是因为自己不会历史最大值）。

# 分析

对于询问维护一个 KDT，考虑一个区间与另一个区间有交可以写成一组不等式，据此，对于一个元素可能贡献的范围就可以在 KDT 上打标记。

那么，考虑如何计算答案，发现这本质上就是一个最大子段和问题，这里可以使用按值（即输入顺序）依次插入，维护一个历史最大值。

另一种方法就可以考虑加入所有元素之后一起查询，此时一个点所受的影响就是根到该节点的链上所有元素集合的最大子段和。这一结构形似线段树分治，我们可以仅考虑新增一个元素与回退上一个操作，而这一点可以使用链表维护最大子段和。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=2e5+10,N=5e4+10,K=2;
int b[M],n,m,root,ans[M],cnt[N],l[N],r[N];
struct node{
	int px[2];
}a[N],c[M];
struct tree{
	int ls,rs,mn[2],mx[2];
	vector<int>laz,nw;
}tr[M];
inline void pushup(int u){
	int ls=tr[u].ls,rs=tr[u].rs;
	for(int i=0;i<K;++i){
		tr[u].mn[i]=tr[u].mx[i]=c[u].px[i];
		if(ls){
			tr[u].mn[i]=min(tr[u].mn[i],tr[ls].mn[i]);
			tr[u].mx[i]=max(tr[u].mx[i],tr[ls].mx[i]);
		}
		if(rs){
			tr[u].mn[i]=min(tr[u].mn[i],tr[rs].mn[i]);
			tr[u].mx[i]=max(tr[u].mx[i],tr[rs].mx[i]);
		}
	}
}
inline int build(int l,int r,int d){
	int mid=l+r>>1;
	nth_element(b+l,b+mid,b+r+1,[&](int x,int y){return c[x].px[d]<c[y].px[d];});
	int u=b[mid];
	if(l<mid) tr[u].ls=build(l,mid-1,d^1);
	if(mid<r) tr[u].rs=build(mid+1,r,d^1);
	pushup(u);
	return u;
}
inline void mdf(int u,int lx,int ly,int tm){//1<=l<=lx;ly<=y<=inf
	if(tr[u].mx[0]<=lx&&tr[u].mn[1]>=ly) return (void)tr[u].laz.push_back(tm);
	if(c[u].px[0]<=lx&&c[u].px[1]>=ly) tr[u].nw.push_back(tm);
	int ls=tr[u].ls,rs=tr[u].rs;
	if(ls&&tr[ls].mn[0]<=lx&&ly<=tr[ls].mx[1]) mdf(ls,lx,ly,tm);
	if(rs&&tr[rs].mn[0]<=lx&&ly<=tr[rs].mx[1]) mdf(rs,lx,ly,tm);
}
inline void add(int x,int &res){
	if(!cnt[x]++){
		l[x]=l[x-1],r[x]=r[x+1];
		l[r[x]-1]=l[x],r[l[x]+1]=r[x];
		assert(r[x]>x&&l[x]<x);
		res=max(res,r[x]-l[x]-1);
	}
}
inline void del(int x){
	if(!--cnt[x]){
		int tl=l[x],tr=r[x];
		l[tr-1]=r[tl+1]=x;
		l[x]=r[x]=x;
	}
}
inline void query(int u,int res){
	for(int i:tr[u].laz) add(i,res);
	int tmp=res;
	for(int i:tr[u].nw) add(i,res);
	ans[u]=res;
	for(int i=(int)tr[u].nw.size()-1;~i;--i) del(tr[u].nw[i]);
	if(tr[u].ls) query(tr[u].ls,tmp);
	if(tr[u].rs) query(tr[u].rs,tmp);
	for(int i=(int)tr[u].laz.size()-1;~i;--i) del(tr[u].laz[i]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i].px[0],&a[i].px[1]);
	for(int i=1;i<=m;++i){
		scanf("%d%d",&c[i].px[0],&c[i].px[1]);
		b[i]=i;
	}
	root=build(1,m,0);
	for(int i=1;i<=n;++i){
		mdf(root,a[i].px[1],a[i].px[0],i);
		l[i]=r[i]=i;
	}
	l[n+1]=r[n+1]=n+1;
	query(root,0);
	for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
```


---

