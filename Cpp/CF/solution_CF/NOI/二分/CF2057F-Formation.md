# Formation

## 题目描述

某天，“T 世代”的老师们为了培养学生的纪律性，让他们排成一列进行计算。这一列共有 $n$ 名学生，第 $i$ 名学生的身高为 $a_i$。

如果满足对于每一个从 $1$ 到 $n-1$ 的 $i$，都有 $a_i \cdot 2 \ge a_{i + 1}$，则称这一列为舒适的。目前，这一列已经是一列舒适的队伍。

老师们希望队列中的最大身高可以更高一些，所以打算让学生们吃比萨。已知每个学生每吃一个比萨，他的身高就会增加 $1$。一份比萨只能让一个学生吃，但每个学生可以无限次吃比萨。在所有学生吃完比萨后，需要确保这一列依然是舒适的。

老师们有 $q$ 个选择计划，决定要订多少个比萨。对于每种方案 $k_i$，你的任务是回答：当学生们最多吃掉 $k_i$ 个比萨时，能达到的最大身高 $\max(a_1, a_2, \ldots, a_n)$ 是多少？

## 说明/提示

在第一组输入数据的第一个查询中，可以给第一个学生吃 $3$ 个比萨，再给第二个学生吃 $6$ 个比萨，那么最终的身高数组会是 $[13, 26]$（满足 $13 \cdot 2 \ge 26$，所以队列是舒适的），此时最大身高是 $26$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 1
10 20
10
6 7
3 1 2 4 5 6
1
2
4
8
16
32
64
10 4
1 2 4 8 16 32 64 128 256 512
10
100
1000
10000```

### 输出

```
26
7 8 10 12 19 35 67
513 560 1011 10001```

# 题解

## 作者：xcyyyyyy (赞：5)

最优策略一定是选择一个柱子，不断的往上面添加，实在添加不了了就往前面的柱子进行添加。通过枚举柱子，二分答案，可以做到 $O(nq\log^2 V)$。

注意到二分答案时，我们相当于拖了一个尾巴 $(x,x/2,x/4,...)$，我们设它为 $c$，对应柱子为 $i$，那么代价就是 $\sum \limits_{j=0}\max(c_j-a_{i-j},0)$。但是从“实在添加不了了就往前面的柱子进行添加”的情况来看，我们只会修改一个后缀，这是由于一开始就满足 $a_i \times 2\geq a_{i+1}$。而这个后缀的长度是 $O(\log V)$ 级别的，那么我们可以通过枚举一个作用长度 $k$，来消除 $\max$。

具体的，若 $(i,k)$ 可以成为 $M$ 的决策，当且仅当：

* $a_{i-j}\leq c_j, \forall 0\leq j\lt k $。
* $a_{i-k}\gt c_{k}$。

此时可以贡献的 $M$ 的范围必然是一个区间，对应的代价就是 $\sum \limits_{j=0}^{k-1}c_j-a_{i-j}$。

观察这个代价，固定 $k$，对于一个 $M$ 来说最优秀的 $i$ 必然是确定的，那么我们只需要对于每个 $k$ 维护 $O(n)$ 个情况的分段函数，就能在 $O(\log V\log n)$ 的时间复杂度下找到指定 $M$ （其中 $O(\log n)$ 是在序列上二分找到 $M$ 的复杂度），结合外层 $O(q\log V)$ 个询问，做到 $O(q\log^2 V\log n )$。

二分答案和枚举 $k$ 的复杂度必然不能省的，考虑在连续段上找到 $M$ 对应位置的这个 $O(\log n)$ 上下手，对每个询问都二分未免有点浪费，我们可以离线后同时对所有询问进行二分，然后将他们查询的 $M$ 排序，在这 $k$ 个分段函数上从左往右扫即可做到 $O(n\log ^2 V)$。



```cpp

#include<bits/stdc++.h>
using namespace std;
#define N 50005
#define ll long long
struct node{int l,r;ll sum;};
ll ans[N];
int t,n,q,a[N],k[N],ql[N],qr[N],d[N],p[N],mi[40];
vector<node> b[40],c[40];
void sol(){
	int mx=0;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),mx=max(mx,a[i]);
	for(int i=1;i<=q;i++)scanf("%d",&k[i]),ql[i]=mx,qr[i]=2e9;
	for(int k=1;k<=30;k++){
		b[k].clear();
		c[k].clear();
		for(int i=k;i<=n;i++){
			int l=0,r=2e9;
			ll sum=0;
			for(int j=0;j<k;j++)l=max(1ll*l,1ll*mi[j]*a[i-j]-mi[j]+1),sum+=a[i-j];//a[i-j]<=M/2^j
			if(i-k!=0)r=min(1ll*r,1ll*mi[k]*a[i-k]-mi[k]);
			// printf("%d %d :%d %d %lld\n",k,i,l,r,sum);
			if(l<=r)b[k].push_back({l,0,sum}),b[k].push_back({r+1,0,-sum});
		}
		b[k].push_back({(ll)2e9+1,0,0});
		sort(b[k].begin(),b[k].end(),[](const node &x,const node &y){return x.l<y.l;});
		int lst=0;
		multiset<ll> s;
		s.insert(-1e18);
		for(auto [l,r,sum]:b[k]){
			if(lst!=l)c[k].push_back({lst,l-1,*prev(s.end())});//fprintf(stderr,"%d %d %d %lld\n",k,lst,l-1,*prev(s.end()));
			if(sum>0)s.insert(sum);
			else if(sum<0) s.erase(s.lower_bound(-sum));
			lst=l;
		}
	}
	for(int t=1;t<=31;t++){
		for(int i=1;i<=q;i++)d[i]=((ll)ql[i]+qr[i]+1)>>1;
		sort(d+1,d+1+q);
		for(int k=1;k<=30;k++)p[k]=0;
		for(int i=1;i<=q;i++){
			ans[i]=1e18;
			int M=d[i];
			ll pr=0;
			for(int k=1;k<=30;k++){
				while(c[k][p[k]].r<M)++p[k];
				pr+=(M+mi[k-1]-1)/mi[k-1];
				ans[i]=min(ans[i],pr-c[k][p[k]].sum);
			}
		}
		for(int i=1;i<=q;i++){
			int mid=lower_bound(d+1,d+1+q,((ll)ql[i]+qr[i]+1)>>1)-d;
			if(ans[mid]<=k[i])ql[i]=((ll)ql[i]+qr[i]+1)>>1;
			else qr[i]=(((ll)ql[i]+qr[i]+1)>>1)-1;
		}
	}
	for(int i=1;i<=q;i++)printf("%d ",ql[i]);puts("");
}
int main(){
	mi[0]=1;for(int i=1;i<=30;i++)mi[i]=mi[i-1]*2;
	scanf("%d",&t);while(t--)sol();	
}
```

---

## 作者：Carotrl (赞：4)

挺好想的。但写了个弱智错误调了一年。打 CF 的时候还是应该开这个题的。

考虑单组询问怎么做。二分答案 $M$ 并枚举在第 $k$ 个数取到。那么我们要将 $a_k$ 加到 $M$，将 $a_{k-1}$ 加到 $\lceil \frac{M}{2} \rceil$，将 $a_{k-2}$ 加到 $\lceil \frac{M}{4} \rceil$，以此类推。从后向前直到当我们发现一个位置 $i$，满足 $a_{i} \ge \lceil \frac{M}{2^{k-i}} \rceil$ 时我们就不需要加了。因为整个序列初始是好的，所以它现在也是好的，并且操作次数最少。于是找到位置 $i$ 后答案就是 $\sum\limits_{j=0}^{k-i-1} \lceil \frac{M}{2^{j}} \rceil - \sum\limits_{j=i+1}^{k}a_j$。

不难发现由于每次 $M$ 都在除以 $2$，所以对于一个 $k$，可能的 $i$ 只有 $O(\log V)$ 种，它们把值域分为了若干段。也就是说，我们可以处理出一段值域区间对应的一个 $i$。

当二分答案时我们会枚举 $k$ 计算。考虑优化一下，把所有 $k$ 产生的值域区间全部拍到一起。这样我们可以把值域划分为 $O(n \log V)$ 段。而 $k-i$ 也是 $O(\log V)$ 级别的。对于每一段，我们可以记录一种 $k-i$ 对应 $\sum\limits_{j=i+1}^{k}a_j$ 的最大值。这样，我们在二分后，只需要定位出 $M$ 在哪一段，枚举 $k-i$ 就可以计算当前答案了。一次查询只要花 $\log V$ 的时间查询。

所以做法的时空复杂度都是 $O(n \log^2 V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define pi pair<int,ll>
#define vec vector<int>
#define pb push_back
#define ll long long
#define inf 2000000000ll
void in(int &x){
    int f=1;x=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-')c=getchar();
    if(c=='-')f=-1,c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    x*=f;
}
int t,n,m,k,T,x,y,a[50005];ll b[50005];
int lim[50005][33],p[50005][33],e[50005];ll q[50005][33];
ll d[1600005];vector<ll>f[1600005];
vector<pi>add[1600005],del[1600005];
multiset<ll>s[33];
ll query(ll x){
	int p=lower_bound(d+1,d+1+m,x)-d;
	ll s=0,w=1,ans=inf;
	for(int i=0;i<f[p].size();i++,w*=2){
		ans=min(ans,s-f[p][i]);
		s+=(x-1)/w+1;
	}return ans;
}
void solve(){
	in(n);in(T);int mx=0;
	for(int i=1;i<=n;i++)in(a[i]),b[i]=b[i-1]+a[i],mx=max(mx,a[i]);
	for(int i=1;i<=n;i++){
		e[i]=0;ll w=1;
		for(int j=i;j>=1&&w<=inf*2;j--,w*=2){
			int x=min(inf,w*a[j]);
			if(!e[i]||x>lim[i][e[i]]){
				e[i]++;lim[i][e[i]]=x;
				p[i][e[i]]=i-j;q[i][e[i]]=b[i]-b[j];
			}
		}
		if(lim[i][e[i]]!=inf){
			e[i]++;lim[i][e[i]]=inf;
			p[i][e[i]]=i;q[i][e[i]]=b[i];
		}
	}
	m=0;for(int i=1;i<=n;i++)for(int j=1;j<=e[i];j++)d[++m]=lim[i][j];
	sort(d+1,d+1+m);m=unique(d+1,d+1+m)-d-1;
	for(int i=1;i<=m;i++)add[i].clear(),del[i].clear(),f[i].clear();
	for(int i=1;i<=n;i++){
		for(int j=1,l=1,r;j<=e[i];j++){
			r=lower_bound(d+1,d+1+m,lim[i][j])-d;
			add[l].pb({p[i][j],q[i][j]});
			del[r+1].pb({p[i][j],q[i][j]});
			l=r+1;
		}
	}
	for(int i=0;i<=32;i++)s[i].clear();
	for(int i=1;i<=m;i++){
		for(auto [x,y]:add[i])s[x].insert(y);
		for(auto [x,y]:del[i])s[x].erase(s[x].find(y));
		int mx=0;for(int j=0;j<=32;j++)if(s[j].size())mx=j;
		f[i].resize(mx+1);
		for(int j=0;j<=mx;j++){
			if(s[j].empty())f[i][j]=-inf;
			else f[i][j]=*(s[j].rbegin());
		}
	}
	while(T--){
		in(x);
		ll l=mx,r=mx+x;
		while(l<r){
			ll mid=(l+r+1)/2;
			if(query(mid)<=x)l=mid;
			else r=mid-1;
		}
		printf("%lld ",l);
	}puts("");
}
signed main(){
	in(t);
	while(t--)solve();
}
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/CF2057F)

**题目大意**

> 给定 $a_1\sim a_n$，其是好的当且仅当所有 $a_i\le 2a_{i-1}$，$q$ 次询问 $k$，求出给所有 $a_i$ 总共增加 $\le k$ 的值，最大化 $\max a_i$。
>
> 数据范围：$n,q\le 5\times 10^4,a_i,k\le 10^9$。

**思路分析**

很显然可以二分，求出 $a_i\ge x$ 的最小代价 $f_i(x)$，判断 $\min_i f_i(x)$ 是否 $\le k$ 即可。

观察 $f_i(x)$ 的形式，发现我们只会修改一个区间 $a(i-j,i]$，如果 $j$ 确定，那么 $a(i-j,i]$ 就是一次函数，并且 $j$ 很显然是 $\mathcal O(\log V)$ 级别。

所以 $f_i(x)$ 实际上是一个 $\mathcal O(\log V)$ 段的一次函数，并且对于相同的 $j$，每个 $f_i(x)$ 这一段的斜率都相等，就是 $\sum_{t=0}^{j-1}\left\lfloor\dfrac x{2^t}\right\rfloor$。

所以我们对于每个 $j$，维护所有 $f_i(x)$ 这一段中常数项的最小值即可。

因此我们先预处理出每个 $a(i-j,i]$ 对应的常数项，以及其定义域，然后把询问离线下来，动态维护每个 $j$ 对应的最小的 $f_i(x)$。

但 $f_i(x)$ 的定义域是基于 $x$ 的，不难发现可以把其定义域修改到关于 $k$ 的范围上，然后就可以扫描线维护了。

时间复杂度 $\mathcal O(n\log V\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5e4+5,mx=2e9;
const ll inf=1e18;
ll a[MAXN],ans[MAXN];
struct Heap {
	priority_queue <ll> qi,qo;
	void ins(ll x) { qi.push(x); }
	void ers(ll x) { qo.push(x); }
	ll top() {
		while(qi.size()&&qo.size()&&qi.top()==qo.top()) qi.pop(),qo.pop();
		return qi.size()?qi.top():-inf;
	}
}	f[32];
ll qry(ll x) {
	ll z=inf,s=0;
	for(int i=1;i<=30;++i) s+=x,x=(x+1)/2,z=min(z,s-f[i].top());
	return z;
}
void solve() {
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a[i];
	vector <array<ll,3>> op;
	for(int i=1;i<=n;++i) {
		ll s=0,l=0;
		for(int j=1;j<=30&&j<=i;++j) {
			s+=a[i-j+1];
			ll r=(i==j?inf:2ll*a[i-j]*((1<<j)-1)-s);
			op.push_back({l,-j,s}),op.push_back({r,j,s}),l=r;
		}
	}
	for(int i=1,k;i<=q;++i) cin>>k,op.push_back({k,0,i});
	sort(op.begin(),op.end());
	for(auto i:op) {
		if(i[1]<0) f[-i[1]].ins(i[2]);
		else if(i[1]>0) f[i[1]].ers(i[2]);
		else {
			ll l=0,r=mx,p=0;
			while(l<=r) {
				ll mid=(l+r)>>1;
				if(qry(mid)<=i[0]) p=mid,l=mid+1;
				else r=mid-1;
			}
			ans[i[2]]=p;
		}
	}
	for(int i=1;i<=q;++i) cout<<ans[i]<<" \n"[i==q];
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

