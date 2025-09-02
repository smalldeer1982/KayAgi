# [ARC174F] Final Stage

## 题目描述

Alice 和 Bob 作为玩家，使用长度为 $N$ 的数列 $L,R$ 进行如下游戏。

- 游戏共进行 $N$ 回合。
- 当 $i$ 为奇数时，第 $i$ 回合由 Alice 操作；当 $i$ 为偶数时，第 $i$ 回合由 Bob 操作。
- 最初，准备一堆石子。
- 按照 $i=1,2,\dots,N$ 的顺序，依次进行以下操作（称为第 $i$ 回合）：
  - 在第 $i$ 回合，轮到的玩家必须从石堆中取走不少于 $L_i$ 个且不多于 $R_i$ 个的整数个石子。
  - 如果无法满足上述条件取石子，则当前轮到的玩家失败，另一方获胜。
- 若第 $N$ 回合结束时双方都未失败，则游戏以平局结束。

在游戏开始前，双方都已知数列 $L,R$ 以及初始石子的数量。

此时，可以证明该游戏必然属于以下三种**解析结果**之一：

- `Alice` …… Alice 存在必胜策略。
- `Bob` …… Bob 存在必胜策略。
- `Draw` …… 双方都不存在必胜策略。

对于本游戏，需要回答 $Q$ 个问题。第 $i$ 个问题如下：

- 假设游戏开始时石堆中有 $C_i$ 个石子。请回答该情况下游戏的解析结果，输出 `Alice`、`Bob` 或 `Draw`。

## 说明/提示

### 数据范围

- $N, L_i, R_i, Q, C_i$ 均为整数。
- $1 \leq N \leq 3 \times 10^5$
- $1 \leq L_i \leq R_i \leq 10^9$
- $1 \leq Q \leq 3 \times 10^5$
- $1 \leq C_i \leq \sum_{i=1}^{N} R_i$

### 样例解释 1

本输入包含 $11$ 个问题。
- 当 $C_i \leq 3$ 时，Alice 可以在第 $1$ 回合直接取完所有石子，必胜。
- 当 $4 \leq C_i \leq 5$ 时，Bob 存在必胜策略。
- 当 $6 \leq C_i \leq 8$ 时，Alice 存在必胜策略。
- 当 $9 \leq C_i$ 时，双方都不存在必胜策略。
- 以 $C_i=9$ 为例，游戏过程如下：
  - 第 $1$ 回合 Alice 取 $3$ 个石子，剩 $6$ 个。
  - 第 $2$ 回合 Bob 取 $1$ 个石子，剩 $5$ 个。
  - 第 $3$ 回合 Alice 取 $4$ 个石子，剩 $1$ 个。
  - 第 $4$ 回合 Bob 取 $1$ 个石子，剩 $0$ 个。
  - 第 $4$ 回合结束时双方都未失败，游戏平局。
- 其他情况也可以类似分析。对于 $C_i=9$，可以证明双方都不存在必胜策略（即双方都采取最优策略时，游戏以平局结束）。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 3
1 2
3 4
1 2
11
1
2
3
4
5
6
7
8
9
10
11```

### 输出

```
Alice
Alice
Alice
Bob
Bob
Alice
Alice
Alice
Draw
Draw
Draw```

# 题解

## 作者：Lgx_Q (赞：2)

朴素的 dp 是简单的，设 $f[i,j]$ 表示从 $i$ 到 $n$ 游戏，初始石子个数为 $j$，是否能赢。

我们考虑直接维护 $f[i,]$，输和赢一段一段交替出现，最后一段是平局。

考虑维护 $f[i,]$ 的差分，即相邻两段的分界线。

发现每次其实会给输的段的 $[l,r]$ 做加法：$l\gets l+l_i,\space r\gets r+r_i$，然后把所有段的输赢状态取反。

用差分描述：把第奇数个 $1$ 往右平移 $l_i$ 单位，把第偶数个 $1$ 往右平移 $r_i$ 单位，然后给位置 $1$ 赋值成 $1$。

考虑维护这些 $1$ 的位置，我们需要维护奇偶两个全局加标记。

注意到有些平移后输的段可能满足 $l>r$，此时我们需要消去对应的两个 $1$。

使用两个堆 $q_1,q_2$，分别维护奇偶两种，相邻的 $1$ 之间的距离。若距离为 $0$，就可以消去。有个细节：如果下一段是平局，那么只需要消除后面那个 $1$。

每次取出 $q_1$ 或 $q_2$ 进行更新即可。

我们还需要动态支持删除一些 $1$，考虑使用链表维护每个 $1$ 的位置即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pir pair<ll,ll>
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
using namespace std;
const ll maxn=1e6+10;
ll n,m,l[maxn],r[maxn],pre[maxn],nxt[maxn],vis[maxn],pos[maxn],tag0,tag1,tot=2,hd,x[maxn],len,g;
set<pir>st0,st1;
int main(){
//	freopen("p.in","r",stdin);
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%lld%lld",l+i,r+i);
	}
	pre[2]=1, nxt[1]=2;
	pos[1]=0, pos[2]=l[n];
	hd=1; g=0;
	st0.insert(mkp(l[n],1));
	for(ll i=n-1;i;i--){
		if(g==0){
			tag0+=l[i], tag1+=r[i];
			while(!st1.empty()&&st1.begin()->fi+tag0-tag1<=0){
				pir t=*st1.begin(); st1.erase(st1.begin());
				ll x=t.se, y=nxt[x];
				if(!nxt[y]){
					nxt[x]=0;
					continue;
				}
				if(!pre[x]) hd=nxt[y];
				nxt[pre[x]]=nxt[y], pre[nxt[y]]=pre[x];
				if(pre[x]) st0.erase(mkp(pos[x]-pos[pre[x]],pre[x]));
				if(nxt[y]) st0.erase(mkp(pos[nxt[y]]-pos[y],y));
				if(pre[x]&&nxt[y]) st0.insert(mkp(pos[nxt[y]]-pos[pre[x]],pre[x]));
			}
			++tot, pos[tot]=-tag1;
			g^=1;
			nxt[tot]=hd, pre[hd]=tot;
			st1.insert(mkp(pos[hd]-pos[tot],tot)), hd=tot;
		}
		else{
			tag1+=l[i], tag0+=r[i];
			while(!st0.empty()&&st0.begin()->fi+tag1-tag0<=0){
				pir t=*st0.begin(); st0.erase(st0.begin());
				ll x=t.se, y=nxt[x];
				if(!nxt[y]){
					nxt[x]=0;
					continue;
				}
				if(!pre[x]) hd=nxt[y];
				nxt[pre[x]]=nxt[y], pre[nxt[y]]=pre[x];
				if(pre[x]) st1.erase(mkp(pos[x]-pos[pre[x]],pre[x]));
				if(nxt[y]) st1.erase(mkp(pos[nxt[y]]-pos[y],y));
				if(pre[x]&&nxt[y]) st1.insert(mkp(pos[nxt[y]]-pos[pre[x]],pre[x]));
			}
			++tot, pos[tot]=-tag0;
			g^=1;
			nxt[tot]=hd, pre[hd]=tot;
			st0.insert(mkp(pos[hd]-pos[tot],tot)), hd=tot;
		}
	}
	ll u=hd;
	while(u){
		x[++len]=pos[u]+(g&1? tag1:tag0); g^=1;
		u=nxt[u];
	}
	scanf("%lld",&m);
	while(m--){
		ll c; scanf("%lld",&c);
		ll tmp=upper_bound(x+1,x+1+len,c)-x-1;
		if(tmp==len) puts("Draw");
		else puts((tmp^1)&1? "Alice":"Bob");
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc174_f)

**题目大意**

> 有一堆石子，两个人轮流从中取石子，共取 $n$ 次，第 $i$ 次要取 $[l_i,r_i]$ 个石子，无法操作的人输，$q$ 次询问如果初始有 $c$ 个石子，谁会获胜。
>
> 数据范围：$n,q\le 3\times 10^5$。

**思路分析**

如果 $n=1$，那么 $[0,l_i)$ 必败，$[l_i,+\infty)$ 平局。

然后考虑加入 $[l_{n-1},r_{n-1}]$，此时对于每个必败区间 $[x,y]$，其会变成 $[x+l_{n-1},y+r_{n-1}]$ 并取并，然后翻转必胜必败情况，最后设 $[0,0]$ 必败。

我们要动态维护这些操作，可以只维护所有差分位置，即 $c=i-1$ 与 $c=i$ 时结果不同的位置。

那么奇数项差分位置就是必败区间的左端点，偶数项差分位置就是必败区间的右端点。

给不同奇偶的差分位置分别加上 $l_{n-1}/r_{n-1}$，如果两个差分位置相交，说明两个必败区间相交，把这两个差分位置都删除。

用堆维护所有奇偶差分位置的距离，每次把会相遇的差分位置弹出并暴力删除即可，双向链表维护所有差分位置即可。

而翻转必胜必败情况只要在最开头加入一个差分位置 $0$。

从 $n$ 到 $1$ 加入所有线段后处理出每段区间的胜负情况，查询时只需要二分。

时间复杂度 $\mathcal O((n+q)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
using namespace std;
const int MAXN=3e5+5;
ll l[MAXN],r[MAXN],x[MAXN],tl,tr,ans[MAXN];
int n,q,pr[MAXN],sf[MAXN];
set <pair<ll,int>> ql,qr;
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%lld%lld",&l[i],&r[i]);
	int hd=1,tot=2;
	sf[1]=2,pr[2]=1,x[2]=l[n];
	ql.insert({l[n],1});
	for(int o=n-1;o;--o) {
		tl+=l[o],tr+=r[o];
		while(qr.size()&&qr.begin()->fi<=tr-tl) {
			int i=qr.begin()->second,j=sf[i]; qr.erase(qr.begin());
			if(!sf[j]) { sf[i]=0; continue; }
			if(!pr[i]) hd=sf[j];
			sf[pr[i]]=sf[j],pr[sf[j]]=pr[i];
			if(pr[i]) ql.erase({x[i]-x[pr[i]],pr[i]});
			if(sf[j]) ql.erase({x[sf[j]]-x[j],j});
			if(pr[i]&&sf[j]) ql.insert({x[sf[j]]-x[pr[i]],pr[i]});
		}
		swap(tl,tr),swap(ql,qr);
		++tot,pr[hd]=tot,sf[tot]=hd;
		x[tot]=-tl,ql.insert({x[hd]-x[tot],tot}),hd=tot;
	}
	int m=0;
	for(int i=hd;i;i=sf[i]) ++m,ans[m]=x[i]+(m&1?tl:tr);
	for(int i=1;i<=m;++i) cerr<<ans[i]<<" \n"[i==m];
	scanf("%d",&q);
	for(ll z;q--;) {
		scanf("%lld",&z);
		int i=upper_bound(ans+1,ans+m+1,z)-ans-1;
		puts(i==m?"Draw":(i&1?"Bob":"Alice"));
	}
	return 0;
}
```

---

## 作者：Acoipp (赞：1)

## 分析

设 $dp_{i,j}$ 表示用了 $i \sim n$ 中的选项，石头有 $j$ 个，当前的人是否必胜。

转移显然，然后我们可以发现 $dp_{i,x}$ 一定是第一段必败，下一段必胜循环，最后一段必败还是必胜不确定，剩下到无穷大就是平局。

然后考虑维护所有必败的段，转移的时候设一个必败的段的端点是 $[s,t]$，那么它下一个会扩展到 $[s+l_i,t+r_i]$，并且状态取反（必胜）。

这样子会有一些必败的段合并，并且最后一段如果是必胜，那它要么被必败的段吞并，要么自己扩展到 $[s+l_i,t+r_i]$（可能会有一部分被必败的段吞并），然后状态取反（必败）。

平局的边界情况也需要处理一下。

具体地来说，边界情况为 $[0,l_n-1]$ 必败，剩下平局，然后对 $i=n-1 \sim 1$ 依次考虑，每次维护一下所有的 $(l,r]$ 表示这一段是必败的段，由于每次操作之后都要反转状态，所以需要开两个数据结构维护上面的内容。

如何合并两个段呢，就用堆来维护段与段之间的空隙的大小，然后用链表删除元素就可以了。（需要开两个堆，因为需要取反，并且堆是可删堆）

最后处理完了，要把 $(-1,l_i-1]$ 标记为必败，这个链头插入一个元素，同时更新一下堆就可以了。

至于左端点整体 $+l_i$，右端点整体 $+r_i$，拿两个整体偏移量记录就可以了，这个并不困难。

总结起来，细节比较多，需要耐心实现，时间复杂度是优秀的单 $\log$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1000000000000000000ll
#define N 500005
using namespace std;
namespace IO{
	inline char nc(){
		static char buf[1000000],*p=buf,*q=buf;
		return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++;
	}
	inline ll read(){
		ll res = 0,w = 1;
		char c = nc();
		while(c<'0'||c>'9')w=(c=='-'?-1:w),c=nc();
		while(c<='9'&&c>='0')res=res*10+c-'0',c=nc();
		return res*w;
	}
	char obuf[1<<21],*p3=obuf; 
	inline void pc(char c){ 
		p3-obuf<=(1<<20)?(*p3++=c):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=c); 
	} 
	inline void write(ll x){ 
		if(x<0) pc('-'),x=-x; 
		if(x>9) write(x/10); 
		pc(x%10+'0'); 
	}
}
using namespace IO;
ll n,q,l[N],r[N],i,x,f[N],tot2,ls,rs,xl[N],xr[N],val[N],tot=2,head,tail;
struct node{
	ll l,r;
	bool operator<(const node& a)const{
		if(val[a.r]-val[a.l]==val[r]-val[l]) return a.l<l;
		return val[a.r]-val[a.l]<val[r]-val[l];
	}
	bool operator==(const node& a)const{return l==a.l&&r==a.r;}
};
priority_queue<node> q1,q2,q3,q4;

//ls is add to cnt1 and q1.first,q2.second
//rs is add to cnt2 and q1.second,q2.first
inline void erase(ll x){xr[xl[x]]=xr[x],xl[xr[x]]=xl[x],xl[x]=xr[x]=0;}
inline void insert(ll x){val[++tot] = x,xr[tot] = xr[head],xl[xr[head]] = tot,xr[head] = tot,xl[tot] = head;}
inline void init(){
	ll temp = 0;
	reverse(l+1,l+n+1),reverse(r+1,r+n+1);
	head=1,tail=2,xr[1]=2,xl[1]=1,insert(l[1]-1),insert(-1);
	q1.push((node){4,3});
	for(ll i=2;i<=n;i++){
		if(i%2==0){
			ls+=l[i],rs+=r[i];
			while(q2.size()&&((val[q2.top().r]+ls)<=(val[q2.top().l]+rs)||(q4.size()&&q2.top()==q4.top()))){
				if(q4.size()&&q2.top()==q4.top()){
					q2.pop(),q4.pop();
					continue;
				}
				if(xr[q2.top().r]==tail) erase(q2.top().r);
				else{
					q1.push((node){xl[q2.top().l],xr[q2.top().r]});
					q3.push((node){xl[q2.top().l],q2.top().l});
					q3.push((node){q2.top().r,xr[q2.top().r]});
					erase(q2.top().l),erase(q2.top().r);
				}
				q2.pop(); 
			}
			insert(-1-rs),q2.push((node){tot,xr[tot]}),temp=0;
		}
		else{
			rs+=l[i],ls+=r[i];
			while(q1.size()&&((val[q1.top().r]+rs)<=(val[q1.top().l]+ls)||(q3.size()&&q1.top()==q3.top()))){
				if(q3.size()&&q1.top()==q3.top()){
					q1.pop(),q3.pop();
					continue;
				}
				if(xr[q1.top().r]==tail) erase(q1.top().r);
				else{
					q2.push((node){xl[q1.top().l],xr[q1.top().r]});
					q4.push((node){xl[q1.top().l],q1.top().l});
					q4.push((node){q1.top().r,xr[q1.top().r]});
					erase(q1.top().l),erase(q1.top().r);
				}
				q1.pop(); 
			}
			insert(-1-ls),q1.push((node){tot,xr[tot]}),temp=1;
		}
//		for(ll j=head;j!=tail;j=xr[j]) cout<<j<<" ";
//		cout<<endl; 
	}
	if(temp==0) swap(ls,rs);
	for(ll i=xr[head];i!=tail;i=xr[i]){
		if(val[i]+ls>=0) f[++tot2]=val[i]+ls;
		swap(ls,rs);
	}
//	for(ll i=1;i<=tot;i++) cout<<f[i]<<" ";
//	cout<<endl;
}
inline void solve(ll x){
	if(x>f[tot2]) return pc('D'),pc('r'),pc('a'),pc('w'),pc('\n'),void();
	ll pos = lower_bound(f+1,f+tot2+1,x)-f;
	if(pos&1) return pc('B'),pc('o'),pc('b'),pc('\n'),void();
	else return pc('A'),pc('l'),pc('i'),pc('c'),pc('e'),pc('\n'),void();
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("2.out","w",stdout);
	n=read();
	for(i=1;i<=n;i++) l[i]=read(),r[i]=read();
	init();
	q=read();
	while(q--){
		x=read();
		solve(x);
	}
	return fwrite(obuf,p3-obuf,1,stdout),0;
} 
```

---

