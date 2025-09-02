# [ICPC 2025 NAC] Humans vs AI

## 题目描述

在人工智能崛起的时代，James 害怕失去工作。因此，当老板要求他评估一个新 AI 模型与人类的表现对比时，他想要尽可能让 AI 看起来表现糟糕。

为了测试 AI，James 进行了 $N$ 次试验，每次试验中人类和 AI 执行相同任务并根据表现评分。之后他将选择这些试验结果的某个非空连续子序列发送给老板，并悄悄删除其余部分。

设 $a_i$ 和 $h_i$ 分别表示第 $i$ 次试验中 AI 和人类的表现。老板通过计算两个总分来评估序列：人类总分和 AI 总分，初始均为 $0$。对于每个 $h_i \geq a_i$ 的试验，老板给人类加 $h_i - a_i$ 分；对于每个 $h_i < a_i$ 的试验，AI 获得 $a_i - h_i$ 分。若人类总分大于等于 AI 总分乘以常数 $k$（考虑人类需要食物、水和工位等因素），老板则判定人类优于 AI。

James 计划通过邮件发送选定的试验结果子序列。但有一个问题：无所不知的 AI 会拦截邮件，并可能选择交换某次试验的 $h_i$ 和 $a_i$ 值（最多交换一次，以免 James 察觉）。

计算有多少个非空连续子序列能保证：即使 AI 交换最多一次试验结果，老板仍会判定人类优于 AI。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
10 2
3 5 7 6 8 6 4 5 2 6
2 4 6 5 4 3 3 6 3 4```

### 输出

```
4```

## 样例 #2

### 输入

```
7 1
4 3 2 1 7 6 5
4 2 3 1 7 6 5```

### 输出

```
11```

# 题解

## 作者：Zelensky (赞：3)

[blog](https://www.cnblogs.com/dfgz/p/18962890)

一个序列计数问题，把题意转化一下，发现如果没有 AI 操作，就是要求有多少个区间的 $\sum_{i=l}^r(h_i-a_i)\ge0$，其中负数的权值要乘上 $k$ ，为求简便，之后的区间不加说明则为 $h_i-a_i$ 所构成的序列中的区间。

考虑 AI 的操作，如果区间修改前为人类胜利，发现 AI 的最优决策一定是选中区间中最大的数交换，这样获得的收益最大，否则 AI 不需要修改操作。

这个启发我们根据最值分治，选取当前分治区间的最大值作为分治中心，这样跨越中心的区间 AI 一定会选择分治中心作为操作对象，我们成功地固定了式子中的一项。

容易计算出操作后的变化量 $\Delta=Mx\times(k+1)$ ，问题转化为有多少区间满足 $\sum_{i=l}^r(h_i-a_i)-\Delta\ge0$ ,考虑启发式分治，枚举区间长度较小的一边，当枚举左区间时，问题转化为以下形式，询问有多少 $R$ 满足
$$
R\in(mid,r],S_R\ge\Delta+S_{i-1}
$$
其中 $S$ 为前缀和数组。右区间同理。

显然的一个二维数点问题，可以离线下来扫描线，也可以在线主席树维护，注意一下整形的溢出和边界的处理即可。
```cpp

#include<bits/stdc++.h>
#define int long long
typedef long long ll; 
using namespace std;
const int M=5e6+10;
long long a[(int)5e6],h[(int)5e6];
int len,rt;
ll b[(int)5e6],tot;
int id(int x){return lower_bound(b+1,b+len+1,x)-b;}
struct ST{
	int f[(int)5e5][30],lg[(int)5e6];
	void build(int n){
		lg[1]=0;
		for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1,f[i][0]=i;
		f[1][0]=1;
		for(int i=1;(1<<i)<=n;i++){
			for(int j=1;j+(1<<i)-1<=n;j++){
				int lp=f[j][i-1],rp=f[j+(1<<(i-1))][i-1];
				f[j][i]=(h[lp]>h[rp]?lp:rp);
			}
		}	
	}
	int query(int l,int r){
		int k=lg[r-l+1],lp=f[l][k],rp=f[r-(1<<k)+1][k];
		return h[lp]>h[rp]?lp:rp;
	}
}s;
struct pre_sum{
	ll s[(int)5e6];
	void build(int n){for(int i=1;i<=n;i++)s[i]=s[i-1]+h[i];}
	int query(int l,int r){return s[r]-s[l-1];}
}t;
struct qry{ll v;int opt;};
vector<qry>q1[(int)5e6],q2[(int)5e6];
int n,k;long long ans;
void solve(int l,int r){
	if(l>r)return ; if(l==r)return ans+=h[l]==0,void();
	int mid=s.query(l,r);
	solve(l,mid-1),solve(mid+1,r);
	if(h[mid]<0)return ;
	if(mid-l+1<=r-mid){
		for(int i=mid;i>=l;i--){
			ll val=h[mid]*(k+1)+t.s[i-1];
			q1[r].push_back({val,1}),q1[mid-1].push_back({val,-1});
			b[++tot]=val;
		}
	}
	else {
		for(int i=mid;i<=r;i++){
			ll val=t.s[i]-h[mid]*(k+1);
			q2[mid].push_back({val,1}),q2[l-1].push_back({val,-1}); 	
			b[++tot]=val;
		}
	}
}
struct SEG{
	int cnt=0;
	int siz[(int)5e6],ls[(int)5e6],rs[(int)5e6];
	void add(int &i,int l,int r,int x){
		if(!i)i=++cnt;siz[i]++;if(l==r)return ;int mid=(l+r)>>1;
		x<=mid?add(ls[i],l,mid,x):add(rs[i],mid+1,r,x);
	}
	int query(int i,int l,int r,int x,int opt){
		if(l==r)return siz[i]*opt;int mid=(l+r)>>1;
		return x<=mid?query(ls[i],l,mid,x,opt):(query(rs[i],mid+1,r,x,opt)+siz[ls[i]]);
	}
}T;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>h[i];
	int cnt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i],h[i]-=a[i];
	}
	for(int i=1;i<=n;i++)if(h[i]<0)h[i]*=k;
	s.build(n),t.build(n);
	solve(1,n);
	for(int i=0;i<=n;i++)b[++tot]=t.s[i];
	sort(b+1,b+tot+1);len=unique(b+1,b+tot+1)-b-1;
	for(int i=0;i<=n;i++){
		for(auto x:q2[i])ans+=T.query(rt,1,M,id(x.v)+1,1)*x.opt;
		T.add(rt,1,M,id(t.s[i])+1);
		for(auto x:q1[i])ans+=(i-T.query(rt,1,M,id(x.v)+1,0))*x.opt;
	}
	cout<<ans<<endl;
}

```

---

## 作者：lzyqwq (赞：1)

人类一败涂地。

> - 给出 $[h_1,\dots,h_n],[a_1,\dots,a_n]$ 和 $k$，求满足以下条件的子区间 $[l,r]$ 个数：
>     - $\sum\limits_{j=l}^r[h_j\ge a_j](h_j-a_j)\ge k\sum\limits_{j=l}^r[h_j<a_j](a_j-h_j)$。
>     - 对于任意 $i\in [l,r]$，设交换 $h_i,a_i$ 后得到的数组是 $[h'_l,\dots,h'_r],[a'_l,\dots,a'_r]$，均满足 $\sum\limits_{j=l}^r[h'_j\ge a'_j](h'_j-a'_j)\ge k\sum\limits_{j=l}^r[h'_j<a'_j](a'_j-h'_j)$。
> - $n\le 2\times 10^5$。

令 $h_i\leftarrow h_i-a_i$，交换操作就是一个位置变成相反数，和式的变化量可以看成是一个位置对原来所在和式的贡献消失，变成对另一个和式的贡献。那么两个条件变为：

- $\sum\limits_{j=l}^r[h_i\ge 0]h_j+k \sum\limits_{j=l}^r[h_j<0]h_j\ge 0$。
- 对于任意 $i\in [l,r]$，满足 $\sum\limits_{j=l}^r[h_j\ge 0]h_j+k\sum\limits_{j=l}^r[h_j<0]h_j-(k+1)h_i\ge 0$。

观察到若一个区间内所有 $h_i$ 为负则一定不合法，因此要求 $\max\limits_{i=l}^rh_i\ge 0$。此时对于第二个恒成立的式子，只需要当 $h_i$ 取最大值时满足条件即可，这时其不弱于第一个条件。因此将条件改写成：

- $\max\limits_{j=l}^rh_j\ge 0$。
- $\sum\limits_{j=l}^r[h_j\ge 0]h_j+k\sum\limits_{j=l}^r[h_j<0]h_j-(k+1)\max\limits_{j=l}^rh_j\ge 0$。

进一步令 $c_i=\sum\limits_{j=1}^i[h_j\ge 0]h_j,d_i=\sum\limits_{j=1}^i[h_j<0]h_j$，那么第二个条件变成：

- $c_r-c_{l-1}+k(d_r-d_{l-1})-(k+1)\max\limits_{j=l}^rh_j\ge 0$。

子区间计数不难想到分治。设当前分治区间为 $[L,R]$，中点为 $M$。考虑计算跨过中点的贡献。从右往左扫描左端点 $i$，考虑怎样的右端点 $j$ 会满足条件。

接下来就是套路大作战了。令 $\text{mx}=\max\limits_{u=i}^Mh_u,f_j=\max\limits_{u=M+1}^{j}h_u$。那么 $\max\limits_{u=i}^jh_u=\max\{\text{mx},f_j\}$。考虑一定存在分界点 $p$ 使得当 $j\in(M,p)$ 时 $\text{mx}>f_j$；当 $j\in[p,R]$ 时 $\text{mx}\le f_j$。

对于前者两个条件是：

- $\text{mx}\ge 0$。
- $c_j+kd_j\ge (k+1)\text{mx}+c_{i-1}+kd_{i-1}$。
- $j\in(M,p)$。

对于 $\text{mx}\ge 0$ 的部分二维数点即可。

对于后者两个条件化为：

- $f_j\ge 0$。
- $j\in[p,R]$。
- $c_j+kd_j-(k+1)f_j\ge c_{i-1}+kd_{i-1}$。

别看成三维数点了，注意到第一个限制对于所有 $j$ 都是相同的，所以可以把满足第一个条件的 $j$ 拉出来当作一个点集，并在这个点集里面做关于剩下两维限制的二维数点。

时间复杂度 $\mathcal{O}\left(n\log^2n\right)$，空间复杂度 $\mathcal{O}(n)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std; const int N = 200005, I = -1e9;
int n, h[N], a[N], f[N], c[N], d[N], k;
struct BIT {
	int a[N]; void U(int x, int v) { for (; x <= n; x += x & -x) a[x] += v; }
	int Q(int x) { int r = 0; for (; x; x -= x & -x) r += a[x]; return r; }
	int Q(int l, int r) { return l > r ? 0 : Q(r) - Q(l - 1); }
} t;
struct QR {
	int x, l, r; bool operator<(const QR &o) const { return x > o.x; }
} q1[N], q2[N], u1[N], u2[N];
int F(int l, int r) {
	if (l == r) return !h[l];
	int p = 0, q = 0, z = 0, w = 0, o = 0, m = l + r >> 1; f[m] = I;
	for (int i = m + 1; i <= r; ++i) {
		f[i] = max(f[i - 1], h[i]); u1[++z] = {c[i] + k * d[i], i, 0};
		if (f[i] >= 0) u2[++w] = {c[i] + k * d[i] - (k + 1) * f[i], i, 0};
	}
	for (int i = m, mx = I, j = m + 1; i >= l; --i) {
		mx = max(mx, h[i]); while (j <= r && mx > f[j]) ++j;
		if (mx >= 0)
			q1[++p] = {c[i - 1] + k * d[i - 1] + (k + 1) * mx, m + 1, j - 1};
		if (j <= r) q2[++q] = {c[i - 1] + k * d[i - 1], j, r};
	}
	stable_sort(u1 + 1, u1 + z + 1); stable_sort(u2 + 1, u2 + w + 1);
	stable_sort(q1 + 1, q1 + p + 1); stable_sort(q2 + 1, q2 + q + 1);
	for (int i = 1, j = 1; i <= p; ++i) {
		for (; j <= z && u1[j].x >= q1[i].x; ++j) t.U(u1[j].l, 1);
		o += t.Q(q1[i].l, q1[i].r);
		if (i == p) for (--j; j; --j) t.U(u1[j].l, -1);
	}
	for (int i = 1, j = 1; i <= q; ++i) {
		for (; j <= w && u2[j].x >= q2[i].x; ++j) t.U(u2[j].l, 1);
		o += t.Q(q2[i].l, q2[i].r);
		if (i == q) for (--j; j; --j) t.U(u2[j].l, -1);
	}
	return o + F(l, m) + F(m + 1, r);
}
signed main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin >> n >> k; for (int i = 1; i <= n; ++i) cin >> h[i];
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; h[i] -= a[i];
		if (h[i] > 0) c[i] = c[i - 1] + h[i], d[i] = d[i - 1];
		else c[i] = c[i - 1], d[i] = d[i - 1] + h[i];
	}
	return cout << F(1, n), 0;
}
```

---

## 作者：Masterwei (赞：1)

很板的题。

首先发现 $h,a$ 数组没什么用，一看就可以直接处理为一个数组：我们设 $b_i$ 为第 $i$ 个试验的贡献，当 $h_i>a_i$ 时 $b_i=h_i-a_i$，否则 $b_i=(a_i-h_i)\times k$。

交换操作可以看作是将一个 $b_i>0$ 的地方改为 $-b_i\times k$。

那么现在我们将问题转化为了选择一个子区间，选择最大的大于 $0$ 的 $b$ 改掉（没有就不改）后，子区间 $b$ 的和大于等于 $0$ 的方案数。

直接用单调栈貌似并不好做，所以考虑分治，枚举最大值双指针做，用一个数据结构维护即可。

时间复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define rnd() abs((int)_rnd())
#define int long long
using namespace std;
inline int read(){
  int x=0;bool f=0;char ch=getchar();
  while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
  while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
  return f?-x:x;
}
mt19937 _rnd(time(0));
const int Maxn=2e5+5;
int n,k;
int a[Maxn],h[Maxn];
struct tree{
	int ls,rs,key,val,tag,si;
}t[Maxn];
int rt,cnt;
inline void add_(int x,int p){
	if(!x)return;
	t[x].val+=p;t[x].tag+=p;
}
inline void spread(int x){
	if(!x)return;
	add_(t[x].ls,t[x].tag);add_(t[x].rs,t[x].tag);
}
inline void update(int x){
	t[x].si=t[t[x].ls].si+t[t[x].rs].si+1;
}
void split(int root,int&x,int&y,int val){
	if(!root)return void(x=y=0);
	spread(root);
	if(t[root].val<=val){
		x=root;split(t[x].rs,t[x].rs,y,val);
	}else{
		y=root;split(t[y].ls,x,t[y].ls,val);
	}update(root);
}
int merge(int x,int y){
	if(!x||!y)return x^y;
	spread(x);
	if(t[x].key>t[y].key){t[x].rs=merge(t[x].rs,y);update(x);return x;}
	t[y].ls=merge(x,t[y].ls);update(y);return y;
}
inline void ins(int val){
	int x,y;split(rt,x,y,val);
	t[++cnt]={0,0,rnd(),val,0,1};
	rt=merge(merge(x,cnt),y);
}
inline int query(int val){
	int x,y;split(rt,x,y,val-1);
	int res=t[y].si;
	rt=merge(x,y);return res;
}
inline void clear(){rt=0;while(cnt)t[cnt--]={0,0,0,0,0,0};}
int ans;
int ma[Maxn],sum[Maxn];
void solve(int l,int r){
	if(l==r)return void(ans+=(a[l]==0));
	int mid=l+r>>1;
	clear();
	ma[mid]=max(0ll,a[mid]);sum[mid]=a[mid];
	for(int i=mid-1;i>=l;i--)ma[i]=max(ma[i+1],a[i]),sum[i]=sum[i+1]+a[i];
	ma[mid+1]=max(0ll,a[mid+1]);sum[mid+1]=a[mid+1];
	for(int i=mid+2;i<=r;i++)ma[i]=max(ma[i-1],a[i]),sum[i]=sum[i-1]+a[i];
	int p=mid;
	for(int i=mid+1;i<=r;i++){
		while(p>=l&&ma[p]<=ma[i])ins(sum[p--]);
		ans+=query(ma[i]*(k+1)-sum[i]);
	}
	
	clear();p=mid+1;
	for(int i=mid;i>=l;i--){
		while(p<=r&&ma[p]<ma[i])ins(sum[p++]);
		ans+=query(ma[i]*(k+1)-sum[i]);
	}
	solve(l,mid);solve(mid+1,r);
}
signed main(){
	n=read();k=read();
	for(int i=1;i<=n;i++)h[i]=read();
	for(int i=1;i<=n;i++){
		a[i]=h[i]-read();
		if(a[i]<0)a[i]*=k;
	}
	solve(1,n);printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：Purslane (赞：0)

# Solution

如果没有 AI 动手脚，是相当好算的：记 $s_i$ 表示实验 $i$ 之后人类和 AI 的分差。如果 $h_i \ge a_i$ 那么 $s_i=h_i-a_i$，否则 $s_i = k(h_i-a_i)$。记 $pre_i = \sum_{j \le i} s_j$。那么我们求的就是 $0 \le i < j$ 且 $pre_j - pre_i \ge 0$ 那么人类获胜。否则 AI 获胜。

现在 AI 会动手脚。发现如果区间内所有均有 $h_i < a_i$，人类一定输，都不需要 AI 动手脚。所以合法的区间一定存在 $l \le i \le r$ 使得 $h_i \ge a_i$。

AI 一定会将其中 $h_i - a_i$ 最大的那个 $i$ 给干掉。所以考虑建出 $h_i-a_i$ 的笛卡尔树。（不建出来也无所谓。只需要用单调栈求出整体结构就行。）

这样我们会得到分差的变化 $\Delta \le 0$，要求 $pre_j - pre_i + \Delta \ge 0$。其中 $j$ 属于右子树，$i+1$ 属于左子树（可能包含根，不过没太大用处）。

我不清楚能不能做到单 $\log$。不过扫描较小的那棵子树，比如是 $pre_j$，那么发现只用对区间满足某一要求的 $pre_i$ 进行计数。那这就是二维数点，离线之后怎么做都行。

而我们会进行 $O(n \log n)$ 次数点（启发式合并），所以总复杂度是 $O(n \log^2 n)$。

代码没写。我觉得假不了。

---

