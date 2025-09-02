# [RMI 2024] 选区间 / Choose Interval

## 题目描述

有一个**无限长**的数列 $A$，初始时 $A$ 中元素全为 $0$。

给定 $n$ 个区间 $[l_i,r_i]$，对于 $i=1,2,\ldots,n$，你需要执行以下的**一种**操作恰好一次：

1. $\forall j\in [l_i,r_i]$，令 $A_j\gets A_j+1$。
1. $\forall j \in \mathbb Z \land j\not\in [l_i,r_i]$，令 $A_j\gets A_j+1$。

构造一组方案，使得操作完后数列中最大值最小。




## 说明/提示


#### 样例解释

另一种合法的输出为

```plain
2
11011
```

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le n\le 2\times 10^5$；
- $1\le l_i\le r_i\le 2n$。


| 子任务编号 | $n\le$ | 得分 |
| :-: | :-: | :-: |
| $1$ | $20$ | $7$ |
| $2$ | $150$ | $24$ |
| $3$ | $10^3$ | $21$ |
| $4$ | $5\times 10^4$ | $34$ |
| $5$ | $2\times 10^5$ | $14$ |



## 样例 #1

### 输入

```
5
10 10
6 6
1 7
2 5
2 7```

### 输出

```
2
11110```

# 题解

## 作者：BPG_ning (赞：11)

豪牛鼻的题。

先考虑个做法，先默认所有操作都是区间加，然后将一个区间加变成补集加，等价于全局 $+1$，区间 $-2$。

枚举至多做了 $k$ 次补集加，那么问题被转化为：给定序列，你能选出 $k$ 个区间 $-2$，最后答案 $+k$。这个问题可以二分答案，对序列扫描线，优先队列维护区间最远的右端点，每次贪心取出最远的右端点进行区间 $-2$，可以做到 $O(n^2\log^2n)$。

令序列最大值为 $m$，先二分答案 $mid$，考虑有结论：$k\in[m-mid,m-mid+1]$。

证明：

先证明下界，因为做一次操作最大值至多 $-2$，全局 $+1$，所以一次操作后最大值至多 $-1$，那么希望最大值 $\leq mid$ 就至少要做 $m-mid$ 次操作。

---
证明上界。

另 $k=m-mid$。

定义 $x$ 合法指存在方案选择 $x$ 个区间进行区间 $-2$ 使得全局 $\leq mid-x$。

考虑证明若 $k+d+2$ 合法，则 $k+d$ 合法（$d \geq 0$）。

若这 $k+d+2$ 个区间里存在两个区间不交，那么把这两个区间操作删去，得到 $k+d$ 个区间，其全局最大值至多 $+2$，所以 $k+d$ 合法。

若这 $k+d+2$ 个区间两两有交，设交集内最大值为 $x$。若 $x> mid-(k+d)-4$，意味着区间减之前 $x'=x+2(k+d+2)>mid+k+d=m+d\geq m$，矛盾。所以 $x\leq mid-(k+d)-4$，此时选出两个区间使得这两区间的交为所有区间的交（这两个区间显然一定存在），将这两个区间删去，使得 $k+d$ 合法。

若 $k,k+1$ 不合法，那么就不存在 $k+d+1$ 合法，所以我们只需要在二分时 check $k,k+1$ 的合法性。

于是我们 $O(n\log^2n)$ 地做完了！

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fir first
#define sec second
#define mp make_pair
void chkmin(int &x,int y){x=min(x,y);}
void chkmax(int &x,int y){x=max(x,y);}
const int N=4e5+10,inf=1e9+10;
int n,q,a[N],f[N],t[N],pid[N];
vector<int> H[N];
struct node{int l,r;} Q[N];
void read(){
    cin>>q;
    n=q*2+1;
    for(int i=1;i<=q;i++){
        cin>>Q[i].l>>Q[i].r;
        H[Q[i].l].push_back(i);
        a[Q[i].l]++,a[Q[i].r+1]--;
    }
    for(int i=1;i<=n;i++) a[i]+=a[i-1];
}
int chk(int m,int V){
    V-=m;
    for(int i=0;i<=n;i++) t[i]=0;
    for(int i=1;i<=q;i++) pid[i]=1;
    priority_queue<pii,vector<pii>,less<pii> >q;
    while(!q.empty()) q.pop();
    int cnt=0,d=0;
    for(int i=1;i<=n;i++){
        d+=t[i];
        for(int p:H[i]){
            q.push(mp(Q[p].r,p));
        }
        while(d+a[i]>V){
            if(q.empty() || q.top().fir<i) return 0;
            pii p=q.top();
            q.pop();
            pid[p.sec]=0;
            t[p.fir+1]+=2;
            d-=2;
            cnt++;
            if(cnt>m) return 0;
        }
    }
    return 1;
}
void work(){
    int Max=0;
    for(int i=1;i<=n;i++) chkmax(Max,a[i]);
    int L=0,R=q;
    while(L<R){
        int mid=(L+R)>>1;
        if(chk(Max-mid,mid) || chk(Max-mid+1,mid)) R=mid;
        else L=mid+1;
    }
    cout<<L<<'\n';
    if(chk(Max-L,L)){
        for(int i=1;i<=q;i++) cout<<pid[i];
        cout<<'\n';
    }else{
        chk(Max-L+1,L);
        for(int i=1;i<=q;i++) cout<<pid[i];
        cout<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    read();
    work();
    cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
    return 0;
}
```

---

## 作者：Purslane (赞：7)

# Solution

单 $\log$ 做法，轻松拿下最优解（我的常数有点大，所以不是很明显）欢迎来叉！！！！

其实我最开始也不太会这个题，看了现有题解，就有了这个思路？？（主要卡在第一步转化上）

先做一个转化：等价于给你一个序列 $a$，允许你进行 $k$ 次给定区间减 $2$ 的操作（不能重复选两次，因为这相当于将一种区间从 $1$ 类型转化为 $2$ 类型），求 $k + \max_{i} a_i$ 的最小值。（注意 $a$ 需要 $2n+1$ 的长度）

一个非常朴素的思想是，对于每个 $s=\max_{i} a_i$ 求出 $k$ 的最小值。

那么你可以直接暴力——从左到右依次考虑每个位置，如果该位置 $a_i > s$，则将**未选择的，能覆盖到 $i$ 的，且 $r$ 最大的线段转化为 $2$ 类型**，不断操作直到 $a_i \le s$。这个贪心，显然正确吧。

那么你就可以 $O(n^2 \log n)$ 做了（因为你每一步不需要暴力找覆盖 $i$ 的线段。将所有现存线段按照 $l$ 排序，这样每次只需要查询前缀中 $r$ 的最大值和位置）。

注意到这个 $-2$ 很烦。所以我们可以将 $s$ 按奇偶性分类。奇偶性相同的 $s$，我们可以把和 $s$ 模 $2$ 不同余的 $a$ 强制加 $1$，不影响答案而且满足：如果我们递减 $s$，那么每次不合法的位置一定值为 $s+2$。

结论：$s$ 选择的变为类型 $2$ 的线段一定是 $s+2$ 选择的线段的子集。（也就是按照上面的贪心的过程，每次只会新增线段）。

所以如果这个结论对，我们可以直接从 $n$ 或 $n-1$ 开始，在 $\ge -n$ 的基础上不断 $s \leftarrow s-2$。每次找到 $a$ 中所有值为 $s+2$ 的位置（从左到右），检查是否有未选择的线段经过他，并且右端点最大的选择。

注意到每遍历一次，现存未选择线段必然减少一个（否则直接退出程序），因此复杂度均摊为 $O(n \log n)$。

而考虑暴力的做 $s$ 和 $s+2$。发现考虑了每一个前缀，$s$ 选择的相较于 $s+2$ 选择的，多的那一部分必然两两不交（或者说，即使有交，一定是在我们考虑的位置之前，对后面的影响最多是 $-2$）。所以考虑到每个位置 $pos$，$a_{s+2,pos} -2 \le a_{s,pos}$（在操作之前）。因此在 $pos$ 处 $s$ 选择的一定不比 $s+2$ 少。那么一定能保证 $s$ 选择的是 $s+2$ 的超集。

我个人认为这里的证明是正确的。如果你觉得有问题，欢迎 hack！！！！！

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=400000+10;
int n,L[MAXN],R[MAXN],ans=INT_MAX,res[MAXN],v[MAXN],output[MAXN],lim[MAXN],op,rnk;
namespace DS {
	struct MAX {int mx,pos;}t[MAXN<<2],cs[MAXN<<2];
	int tag[MAXN<<2];
	MAX operator +(MAX A,MAX B) {if(A.mx==B.mx) return {A.mx,min(A.pos,B.pos)}; if(A.mx>B.mx) return A; return B;}
	MAX operator +(MAX A,int B) {return A.mx+=B,A;}
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid (l+r>>1)
	void push_down(int k,int l,int r) {
		tag[lson]+=tag[k],tag[rson]+=tag[k],t[lson]=t[lson]+tag[k],t[rson]=t[rson]+tag[k];
		return tag[k]=0,void();	
	}
	void build_cs(int k,int l,int r) {
		if(l==r) return cs[k]={R[l],l},void();
		build_cs(lson,l,mid),build_cs(rson,mid+1,r);
		return cs[k]=cs[lson]+cs[rson],void();
	}
	void build_t(int k,int l,int r) {
		tag[k]=0;
		if(l==r) return t[k]={v[l],l},void();
		build_t(lson,l,mid),build_t(rson,mid+1,r);
		return t[k]=t[lson]+t[rson],void();	
	}
	void assign(int k,int l,int r,int pos) {
		if(l==r) return cs[k]={-INT_MAX,-1},void();
		if(pos<=mid) assign(lson,l,mid,pos);
		else assign(rson,mid+1,r,pos);
		return cs[k]=cs[lson]+cs[rson],void();
	}
	MAX query_cs(int k,int l,int r,int x,int y) {
		if(x>y) return {-INT_MAX,-1};
		if(x<=l&&r<=y) return cs[k];
		if(y<=mid) return query_cs(lson,l,mid,x,y);
		if(x>mid) return query_cs(rson,mid+1,r,x,y);
		return query_cs(lson,l,mid,x,y)+query_cs(rson,mid+1,r,x,y);	
	}
	void update(int k,int l,int r,int x,int y,int v) {
		if(x<=l&&r<=y) return t[k]=t[k]+v,tag[k]+=v,void();
		push_down(k,l,r);
		if(x<=mid) update(lson,l,mid,x,y,v);
		if(y>mid) update(rson,mid+1,r,x,y,v);
		return t[k]=t[lson]+t[rson],void();	
	}
};
vector<int> f,g;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	vector<pair<pair<int,int>,int>> seg;
	ffor(i,1,n) {
		cin>>L[i]>>R[i],seg.push_back({{L[i],R[i]},i});
		v[L[i]]++,v[R[i]+1]--;
	}
	sort(seg.begin(),seg.end());
	ffor(i,1,n+n+1) v[i]+=v[i-1];
	ffor(i,1,n+n+1) if((v[i]-n)%2) v[i]++;
	ffor(i,1,n) L[i]=seg[i-1].first.first,R[i]=seg[i-1].first.second,lim[L[i]]=max(lim[L[i]],i);
	ffor(i,1,n+n+1) lim[i]=max(lim[i],lim[i-1]);
	DS::build_cs(1,1,n);
	DS::build_t(1,1,n+n+1);
	int cnt=0;
	for(int i=n;i>=-n;i-=2) {
		int flg=1;
		while(DS::t[1].mx>i) {
			int j=DS::t[1].pos;
			int id=DS::query_cs(1,1,n,1,lim[j]).pos;
			if(id==-1||R[id]<j) {flg=0;break ;}
			cnt++,f.push_back(id);
			DS::assign(1,1,n,id),DS::update(1,1,n+n+1,L[id],R[id],-2);
		}
		if(!flg) break ;
		if(cnt+i<ans) {
			ans=cnt+i;
			op=0,rnk=f.size();
		}
	}
	cnt=0;
	memset(v,0,sizeof(v));
	ffor(i,1,n) v[L[i]]++,v[R[i]+1]--;
	ffor(i,1,n+n+1) v[i]+=v[i-1];
	ffor(i,1,n+n+1) if((v[i]-(n-1))%2) v[i]++;
	DS::build_cs(1,1,n);
	DS::build_t(1,1,n+n+1);
	for(int i=n-1;i>=-n;i-=2) {
		int flg=1;
		while(DS::t[1].mx>i) {
			int j=DS::t[1].pos;
			int id=DS::query_cs(1,1,n,1,lim[j]).pos;
			if(id==-1||R[id]<j) {flg=0;break ;}
			cnt++,g.push_back(id);
			DS::assign(1,1,n,id),DS::update(1,1,n+n+1,L[id],R[id],-2);
		}
		if(!flg) break ;
		if(cnt+i<ans) {
			ans=cnt+i;
			op=1,rnk=g.size();
		}
	}
	cout<<ans<<'\n';
	ffor(i,1,n) res[i]=1;
	if(op==0) ffor(j,0,rnk-1) res[seg[f[j]-1].second]=0;
	else ffor(j,0,rnk-1) res[seg[g[j]-1].second]=0;
	ffor(i,1,n) cout<<res[i];
	return 0;
}
```

---

## 作者：UniGravity (赞：0)

题意：对于每个区间可以选择这个区间内加一或区间外加一，要求最后最大值最小。

考虑二分答案。

对于一个答案 $mid$，先假设所有操作均为区间内加，考虑钦定 $k$ 个为区间外加。此时我们先对整体的值加 $k$，就变成选 $k$ 个区间内减 $2$。

如果确定了 $mid,k$，可以扫描一遍整个序列，假设扫到 $i$，如果值超出限制则找满足 $l\le i$ 且 $r$ 最大的区间 $[l,r]$。用堆维护即可做到单次 check $O(n\log n)$。总体时间复杂度是 $O(n^2\log^2n)$ 的。

考虑找出如果所有操作都为区间内加，此时序列最大的值 $mx$ 和其位置 $mxp$。那么至少需要调整 $k=mx-mid$ 个区间才能使得答案合法。我们大概有个思路：即 $k$ 可能不会离 $mx-mid$ 太远，因为这样子就可能在区间外产生新的最大值。

考虑证明。假设目前选择了 $k\ (k\ge mx-mid+2)$ 个区间变成往外加，考虑能否调整为 $k-2$ 个区间。

首先假设这 $k$ 个区间中有两个不交，则将这两个区间改为内部加，发现序列中所有数的值都不降。因此可以调整。

否则所有区间交非空。发现 $mxp$ 一定在所有区间的交内。原因是区间不交的情况优先调整，则最后剩下来的区间一定属于原来区间最多的那组（即 $mxp$ 所在的位置）。考虑找出 $mxp$ 左边最近的区间左边界对应区间 $i$ 和右边最近的区间右边界对应区间 $j$，则直接选择 $i,j$ 改为内部加，此时影响（值加二）的范围一定最小且包含 $mxp$。由于 $k\ge mx-mid+2$，因此此时 $mxp$ 上的值一定小于等于 $lim-2$。而由于这个区间是最小的，因此这个区间内的所有值都相等（没有区间的边界在之内）。因此选择 $i,j$ 的并加二仍然合法。

所以如果存在一个 $k>mx-mid+2$ 合法，则 $mx-mid$ 和 $mx-mid+1$ 中至少有一个合法。check 一个 $mid$ 时就只有 $O(1)$ 个需要判断的 $k$。时间复杂度变为 $O(n\log^2n)$。

```cpp
const int N=400005;
int n;
pii a[N];
int s[N];
priority_queue<pii>q;
vector<int>id[N];
bool rev[N];
il bool chk(int lim,int cnt){
    lim-=cnt;
    while(!q.empty())q.pop();
    forto(i,0,n*2+1)s[i]=0;
    forto(i,1,n)s[a[i].first]++,s[a[i].second+1]--,rev[i]=0;
    forto(i,1,n*2+1){
        for(int x:id[i])q.push(mkp(a[x].second,x));
        s[i]+=s[i-1];
        while(s[i]>lim){
            if(q.empty()||cnt<=0||q.top().first<i)return 0;
            s[i]-=2,s[q.top().first+1]+=2,rev[q.top().second]=1,q.pop(),cnt--;
        }
    }
    return 1;
}
int mx;

signed main(){
    n=read();
    int l,r,mid,ans;
    forto(i,1,n)l=read(),r=read(),a[i]=mkp(l,r),id[l].eb(i),s[l]++,s[r+1]--;
    forto(i,1,n*2+1)s[i]+=s[i-1],mx=max(mx,s[i]);
    l=0,r=mx,ans=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(chk(mid,mx-mid)||chk(mid,mx-mid+1))ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
    if(!chk(ans,mx-ans))chk(ans,mx-ans+1);
    forto(i,1,n)printf("%d",!rev[i]);
    printf("\n");
    return 0;
}
```

---

