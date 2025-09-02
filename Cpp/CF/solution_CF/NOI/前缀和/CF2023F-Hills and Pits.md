# Hills and Pits

## 题目描述

在一个地势起伏的沙漠城市中，市政府计划购置一辆自卸卡车来平整道路。道路按从左到右的顺序被分为 $ n $ 段，编号为 $ 1 $ 到 $ n $。第 $ i $ 段道路的初始高度是 $ a_i $ 。如果某段道路的高度高于 $ 0 $，则需要自卸卡车从中移走部分沙子；如果低于 $ 0 $，则需要用沙子填平。所有路段在开始时的高度都不为 $ 0 $。

当卡车在第 $ i $ 段时，它可以取走 $ x $ 单位的沙子，使该段高度减少 $ x $，或者可以填入 $ x $ 单位的沙子（前提是车上至少有 $ x $ 单位沙子），使该段高度增加 $ x $。

卡车可以从任一段开始工作。移动到相邻的下一段或上一段需要花费 $ 1 $ 分钟，而装填和卸料的时间则可以忽略不计。卡车有无限容量，最初是空车。

你的任务是计算出将每个路段高度调整为 $ 0 $ 所需的最短时间。注意，完成所有操作后，车上可能仍残留沙子。你需要单独解决每个从 $ l_i $ 到 $ r_i $ 段的沙子调整问题，且只能使用指定段内的沙子。

## 样例 #1

### 输入

```
5
1 1
-179
1 1
5 3
-2 2 -1 3 -1
2 4
1 5
1 3
7 1
1 1 1 -4 1 1 1
1 7
7 2
2 -2 2 -2 1 2 -1
1 7
2 7
4 4
1000000000 1000000000 999999999 -1000000000
2 4
3 4
2 3
1 3```

### 输出

```
-1
2
5
-1
8
6
6
2
-1
1
2```

# 题解

## 作者：ForgotMe (赞：6)

思维难度上感觉比 1E 要简单啊。

首先考虑解决 $l=1,r=n$ 的情况。一个显然的结论是答案不超过 $2\times n$（来回走一遍就行，先取完正的，再取负的），且当 $\sum a_i<0$ 时一定无解。

思考一下发现上面这个策略不优的原因是当前有很多沙子时，可以先解决一些坑，没有必要往回一直走。

设 $x_i$ 表示经过 $i$ 到 $i+1$ 这条边的次数，那么就是要在满足要求的情况下最小化 $\sum x_i$。

不如考虑增加一个限制：强制从 $1$ 出发，在 $n$ 结束，此时如何最小化 $\sum x_i$？首先求出 $s_i=\sum_{j=1}^i a_j$，我们声称：如果 $s_i<0$，那么 $x_i\ge 3$。

证明：因为 $s_i<0$，那么第一次走到 $i$ 时，此时车上的沙子肯定不够，需要从后面拿，那么会经过第一次 $i$ 到 $i+1$，又因为要回来所以又要经过一次，回来填完这个坑又要往前走，所以这条边至少走 $3$ 次。

猜测所有 $x_i$ 都可以取到其下界，即 $\sum x_i$ 的最小值就是 $3\sum_{i=1}^n [s_i<0]+\sum_{i=1}^n [s_i\ge 0]$，实际上这个结论确实成立，如果你明白上面的证明，那么构造出一个合法的过程是容易的。过程如下：如果当前走到了一个 $i$ 有 $s_i<0$，那么往后找到第一个 $s_j\ge 0$ 的 $j$，从 $i$ 走到 $j$ 拿完所有沙子再回去填坑，然后继续往前走。

现在去掉这个限制，怎么求解？实际上把上面的策略与最开始的来回策略结合起来就是该问题的最优贪心策略。形式化的讲，假设车强制从 $s$ 出发， 然后最后回到 $t(s\le t)$，那么其路径可以规划为：从 $s$ 往前走一直走到 $1$ 拿完所有沙子然后回到 $s$ 并在这个回来的过程中填完 $[1,s]$ 的所有坑（这里要保证 $s_{s}\ge 0$），然后对 $[s,t]$ 这段路程执行以上策略，最后到了 $t$ 后一直往后走到 $n$ 拿完所有沙子，然后回到 $t$ 并填坑。枚举所有可能的 $s,t$，然后取最小的次数即为答案。严格证明感觉比较困难，还是写一个比较感性的证明：首先起点确定是 $s$ 了，由于强制了终点为 $t$，那么第一次往右走肯定是不优秀的。由于往左走后肯定是要回来的，那么有 $\forall 1\le i< s$，$x_i\ge 2$，而这一段成功取到了其下界，然后在往右走的过程中，上面的策略肯定是最优秀的，但是注意到上面的策略中 $x_i$ 会取到 $3$ 是因为**假设填完了其坑后还要继续往前走，即前面还有要填的**，那么这个枚举的 $t$ 相当于就是在枚举一段后缀表示回来填完坑后不会再往前走。

那么现在就变成一个数据结构问题了，设 $f(s,t)=2(s-1)+3\sum_{i=s}^{t-1}[s_i<0]+\sum_{i=s}^{t-1}[s_i\ge 0]+2(n-t)$，这个东西比较丑，重新改写一下 $f(s,t)=2(n-1)+\sum_{i=s}^{t-1}[s_i\ge 0]-\sum_{i=s}^{t-1}[s_i<0]$，这是什么啊，后面这一坨不就是最大子段和吗？多次询问的做法就出来了，其唯一的不同就是 $f(s,t)=2(r-l)+\sum_{i=s}^{t-1}[s_i\ge s_{l-1}]-\sum_{i=s}^{t-1}[s_i<s_{l-1}]$，于是将所有询问按照 $s_{l-1}$ 从大到小排序，然后用线段树动态维护一个 $-1/1$ 的序列的区间最大子段和。

最后注意还要把序列翻转一下重新跑一遍。

时间复杂度 $\mathcal{O((n+q)\log n)}$。

```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<LL,LL>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
	//	return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
		return getchar();
	}
	template<class T> void gi(T& x){
		x=0; int f=1;char c=gc();
		if(c=='-')f=-1;
		for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x=x*f;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0)pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=998244353;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[2000005],inv[2000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
//	Invn[0]=Invn[1]=1;
//	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
int T,n,q,a[300005],len,res[300005];
LL s[300005],tmp[300005];
const int INF=1e9;
struct node2{
	int l,r,id;
}Q[300005];
struct node{
	int sum,lmax,rmax,tmax;
}t[1200005];
bool cmp(node2 A,node2 B){
	return s[A.l-1]>s[B.l-1];
}
vector<int>G[300005];
#define ls(p) p<<1
#define rs(p) p<<1|1
inline node merge(node t1,node t2){
	node t;
	t.sum=t1.sum+t2.sum;
	t.lmax=max(t1.lmax,t1.sum+t2.lmax);
	t.rmax=max(t2.rmax,t1.rmax+t2.sum);
	t.tmax=max(t1.tmax,t2.tmax);
	t.tmax=max(t.tmax,t1.rmax+t2.lmax);
	return t;
}
inline void build(int p,int l,int r){
	if(l==r){
		t[p].lmax=t[p].rmax=t[p].sum=-1;
		t[p].tmax=0;
		return ;
	}
	int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	t[p]=merge(t[ls(p)],t[rs(p)]);
}
inline void updata(int p,int l,int r,int x){
	if(l==r){
		t[p].lmax=t[p].rmax=t[p].tmax=t[p].sum=1;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid)updata(ls(p),l,mid,x);
	else updata(rs(p),mid+1,r,x);
	t[p]=merge(t[ls(p)],t[rs(p)]);
}
inline node query(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[p];
	int mid=(l+r)>>1;
	if(L<=mid&&mid+1<=R)return merge(query(ls(p),l,mid,L,R),query(rs(p),mid+1,r,L,R));
	if(L<=mid)return query(ls(p),l,mid,L,R);
	else if(mid+1<=R)return query(rs(p),mid+1,r,L,R); 
}
inline void solve2(){
	for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i],tmp[i]=s[i];
	len=n;tmp[++len]=0;
	sort(tmp+1,tmp+len+1);
	len=unique(tmp+1,tmp+len+1)-tmp-1;
	for(int i=1;i<=len;i++)G[i].clear(); 
	for(int i=1;i<n;i++){
		int pos=lower_bound(tmp+1,tmp+len+1,s[i])-tmp;
		G[pos].push_back(i);
	}
	if(n>=2)build(1,1,n-1);
	sort(Q+1,Q+q+1,cmp);
	int p=1;
	for(int i=len;i>=1;i--){
		if(n>=2){
			for(auto x:G[i])updata(1,1,n-1,x);
			
		}
		while(p<=q&&s[Q[p].l-1]==tmp[i]){
			if(Q[p].l==Q[p].r){
				if(a[Q[p].l]>=0)res[Q[p].id]=0;
				else res[Q[p].id]=-1;
			}else{
				if(s[Q[p].r]-s[Q[p].l-1]<0)res[Q[p].id]=-1;
				else res[Q[p].id]=min(res[Q[p].id],2*(Q[p].r-Q[p].l)-query(1,1,n-1,Q[p].l,Q[p].r-1).tmax);
				
			}
			p++;
		}
	}
}
inline void solve(){
	gi(n),gi(q);
	for(int i=1;i<=q;i++)res[i]=INF;
	for(int i=1;i<=n;i++)gi(a[i]);
	for(int i=1;i<=q;i++){
		gi(Q[i].l),gi(Q[i].r);
		Q[i].id=i;
	}
	solve2();
	reverse(a+1,a+n+1);
	for(int i=1;i<=q;i++){
		Q[i].l=n-Q[i].l+1;
		Q[i].r=n-Q[i].r+1;
		swap(Q[i].l,Q[i].r); 
	}
	solve2();
	for(int i=1;i<=q;i++)pi(res[i]);
}
signed main(){
	srand(time(0));
	gi(T);
	while(T--)solve();
	return 0;
} 
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2023F)

**题目大意**

> 给定 $n$ 个沙坑，高度为 $a_1\sim a_n$，有正有负。
>
> 你可以在 $[1,n]$ 数轴上左右游走，你手中初始没有沙子，经过 $a_i>0$ 的沙坑可以取走 $[0,a_i]$ 个沙子，经过 $a_i<0$ 的沙坑可以放入 $[0,-a_i]$ 个沙子，要求每个沙坑上恰好有 $0$ 个沙子，求最小步数。
>
> $q$ 次询问，对 $a_l\sim a_r$ 求答案。
>
> 数据范围：$n,q\le 3\times 10^5$。

**思路分析**

首先分析答案下界，如果 $\sum a_i<0$ 显然不可能，否则答案肯定不超过 $2n$，因为我们可以从左往右取走所有正数，然后从右往左填平所有负数。

如果想要答案更小，我们就要避免每个位置都经过两次，不妨假设路径是从 $s\to t$ 且 $s<t$，由于 $[l,s)$ 与 $(t,r]$ 都已经走过了，那么我们的目标就是不在 $[s,t]$ 中走回头路。

此时我们对路径是 $s\to l\to r\to t$，因此一个 $[s,t]$ 中的 $a_i<0$ 的位置，如果 $\sum _{j=l}^i a_j\ge 0$ 时，我们能直接填完 $a_i$，否则需要找到 $>i$ 的第一个前缀和 $\ge 0$ 的位置，然后把这一段负的前缀和全部填成正的。

因此此时的权值是 $\sum_{i=s}^{t-1}[v_i\ge0]-[v_i<0]$，其中 $v_i$ 表示 $a[l,i]$ 的前缀和。

所以答案就是最大子段和，但 $v$ 的计算和 $l$ 有关，故不能直接线段树维护。

设 $S_i$ 为全局前缀和，注意到 $v_i\ge 0\iff S_i\ge S_{l-1}$，因此我们把询问按 $S_{l-1}$ 从小到大排序后扫描线，就只需要 $\mathcal O(n)$ 次修改，线段树维护最大子段和即可。

$t>s$ 的情况是对称的，翻转 $a$ 重复上述过程。

时间复杂度 $\mathcal O((n+q)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5; 
struct info {
	int su,mx,lx,rx;
	inline friend info operator +(const info &u,const info &v) {
		return {u.su+v.su,max({u.mx,v.mx,u.rx+v.lx}),max(u.lx,u.su+v.lx),max(v.rx,v.su+u.rx)};
	}
};
struct zKyGt1 {
	info tr[1<<20];
	int N;
	void init(int n) {
		for(N=1;N<=n;N<<=1);
		for(int i=1;i<2*N;++i) tr[i]={0,0,0,0};
		for(int i=1;i<=n;++i) tr[i+N]={-1,0,-1,-1};
		for(int i=N-1;i;--i) tr[i]=tr[i<<1]+tr[i<<1|1];
	}
	void upd(int x) {
		for(tr[x+=N]={1,1,1,1},x>>=1;x;x>>=1) tr[x]=tr[x<<1]+tr[x<<1|1];
	}
	int qry(int l,int r) {
		info sl={0,0,0,0},sr={0,0,0,0};
		for(l+=N-1,r+=N+1;l^r^1;l>>=1,r>>=1) {
			if(~l&1) sl=sl+tr[l^1];
			if(r&1) sr=tr[r^1]+sr;
		}
		return (sl+sr).mx;
	}
}	T;
ll a[MAXN],s[MAXN];
int n,m,l[MAXN],r[MAXN],ans[MAXN];
vector <int> qy[MAXN];
void sol() {
	T.init(n);
	vector <int> id;
	for(int i=1;i<=n;++i) qy[i].clear(),s[i]=s[i-1]+a[i];
	for(int i=1;i<=m;++i) if(l[i]<r[i]) qy[l[i]].push_back(i);
	for(int i=0;i<=n;++i) id.push_back(i);
	sort(id.begin(),id.end(),[&](int i,int j){ return s[i]^s[j]?s[i]>s[j]:i>j; });
	for(int i:id) {
		if(i>0) T.upd(i);
		for(auto q:qy[i+1]) {
			ans[q]=min(ans[q],2*(r[q]-l[q])-T.qry(l[q],r[q]-1));
		}
	}
}
void solve() {
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=m;++i) cin>>l[i]>>r[i],ans[i]=2*(r[i]-l[i]);
	sol();
	reverse(a+1,a+n+1);
	for(int i=1;i<=m;++i) swap(l[i],r[i]),l[i]=n-l[i]+1,r[i]=n-r[i]+1;
	sol();
	for(int i=1;i<=m;++i) cout<<(s[r[i]]<s[l[i]-1]?-1:ans[i])<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：Mysterious_Cat (赞：0)

无解当且仅当 $\sum\limits_{l \le i < r} a_i < 0$。

注意到，钦定起点为 $s$，终点为 $t$，不妨设 $s < t$。记从 $l$ 开始的 $i$ 的前缀和为 $pre_i$，答案为 $(s - l) + (r - l) + \sum\limits_{s \le i < t} 2 \cdot [pre_i < 0] + (r - t)$。

考虑证明。先考虑 $s = l, t = r$，至少需要 $r - l$ 次移动，而且对于 $pre_i < 0$ 的 $i$，我们需要用 $i + 1$ 以后的数补足 $i$ 以前的数，产生一次额外的从 $i + 1$ 到 $i$ 的移动。因为终点是 $r$，从 $i + 1$ 移动到 $i$ 后，还需要一次额外的从 $i + 1$ 到 $i$ 的移动。所以上式是下界。考虑对于 $pre_i < 0$，我们先移动到第一个 $j > i$ 且 $pre_j \ge 0$ 的 $j$，从 $j$ 移动到 $i$ 再移动回到 $j$。就可以取等。

对于一般情况，我们一定从 $s$ 走到 $l$，再从 $l$ 走到 $r$，最后从 $r$ 走回 $t$。我们折返次数与 $s = l, t = r$ 情况相同。

注意到，如果 $pre_s < 0$ 上式可能无法取等。但是我们将 $s$ 调整为第一个 $j > s$ 且 $pre_j \ge 0$ 的 $j$，得到的上式取值更小，且可以取等。

把上式变形可以得到 $2(r - l) - \sum\limits_{s \le i < t} ([pre_i \ge 0] - [pre_i < 0])$。即求解最大子段和。

每次回答询问时的 $pre_i$ 不同，记 $pre'_i$ 为全局前缀和。$[pre_i \ge 0]$ 等于 $[pre'_i \ge pre'_{l - 1}]$。我们离线并按照 $pre'$ 从小到大扫描线解决。

注意，上文只解决了 $s < t$ 的情况，$s > t$ 情况类似，只需要把 $pre'$ 改为全局后缀和 $suf'$ 即可。

---

