# Max Plus Min Plus Size

## 题目描述

[EnV - 尘龙酒馆](https://soundcloud.com/envyofficial/env-the-dusty-dragon-tavern)

----------------
给定一个由正整数组成的数组 $a_1, a_2, \ldots, a_n$ 。

你可以将数组中的一些元素涂成红色，但不能有两个相邻的红色元素（即对于 $1 \leq i \leq n-1$ 来说， $a_i$ 和 $a_{i+1}$ 中至少有一个元素不能是红色的）。

您的得分是红色元素的最大值加上红色元素的最小值，再加上红色元素的数量。请找出您能得到的最高分。

## 样例 #1

### 输入

```
4
3
5 4 5
3
4 5 4
10
3 3 3 3 4 1 2 3 5 4
10
17 89 92 42 29 41 92 14 70 45```

### 输出

```
12
11
12
186```

# 题解

## 作者：Lvlinxi2010 (赞：4)

发现题解区的代码都没大看懂，来写一篇题解。

首先可以发现最优子序列必须至少包含一次最大值，不然一定不会更优，因为个数差不超过 $1$。

按降序枚举最小值，不断加入新的数，形成一些连续段，我们先强制每一个连续段都选 $\left\lceil siz/2\right\rceil$ 个，如果没有一个连续段选到最大值则答案减 $1$，复杂度 $\mathcal{O(n\alpha(n))}$。

具体细节见代码。

附上代码：

```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
#define PII pair<int,int>
using namespace std;
const int MAXN = 2e5 + 10;
PII a[MAXN];
int T,n,num=0,tot=0,ans=0;
int fa[MAXN],siz[MAXN];
int l[MAXN],r[MAXN];//联通块的左右端点 
int pos[MAXN];//最大值的位置(奇偶)
bool vis[MAXN];//是否加入 
bool calc(int x){
	/*
	检查一个连通块在选ceil(siz/2)的时候选没选最大值
	当左右端点同奇偶，选的位置固定，eg: (1) 2 (3) 4 (5)，
	&pos[x]是看在这个连通块的奇数位置有没有最大值
	当左右端点不同奇偶，有两种情况，eg：(1) 2 (3) 4 或 1 (2) 3 (4)  
	&pos[x]是看在这个连通块有没有最大值(只要有就有一种情况可以取到)
	*/
	return (((1<<(l[x]&1))|(1<<(r[x]&1)))&pos[x]);
}
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	tot-=calc(x);
	tot-=calc(y);
	l[x]=min(l[x],l[y]);
	r[x]=max(r[x],r[y]);
	pos[x]|=pos[y];
	tot+=calc(x);
	num-=(siz[x]+1)/2;
	num-=(siz[y]+1)/2;
	siz[x]+=siz[y];
	num+=(siz[x]+1)/2; 
	fa[y]=x;
}
int main(){
	scanf("%d",&T);
	while(T--){
		num=tot=ans=0;
		//num是选的数的总数 
		//tot是选了最大值的连通块的个数  
		scanf("%d",&n);
		FL(i,0,n+1) fa[i]=l[i]=r[i]=i,siz[i]=1,pos[i]=vis[i]=0;
		FL(i,1,n) scanf("%d",&a[i].first),a[i].second=i; 
		sort(a+1,a+n+1);
		reverse(a+1,a+n+1);
		FL(i,1,n) if(a[i].first==a[1].first) pos[a[i].second]|=(1<<(a[i].second&1));//在a[i].second这个连通块里在(a[i].second&1)位有最大值 
		FL(i,1,n){
			//从大到小枚举最小值val 
			int val=a[i].first,id=a[i].second;
			vis[id]=1;
			tot+=calc(id);
			num++;
			//id作为一个一个元素的连通块加入，num和tot要更新！ 
			if(vis[id+1]) merge(id,id+1);
			if(vis[id-1]) merge(id,id-1);
			ans=max(ans,a[1].first+val+num-(tot==0));//max+min+num-(tot==0)，如果没有连通块取到最大值答案减1 
		}
//		FL(i,1,n) printf("%d ",a[i].first);
//		puts("");
		printf("%d\n",ans);
	}
}
```

---

## 作者：Xy_top (赞：3)

妙妙题，差一步想到。

首先发现最终答案由三个部分组成，如果直接考虑 DP，那么就有三维，时间复杂度 $O(n^4)$ T 到半人马座去了。

如果直接这么做，再高的科技都是维护不了的，于是我们显然需要考虑有没有可能消掉其中一项。经过一番的推理可得数组 $a$ 中的最大值至少有一个要选，那么就把 $\max$ 这一项去掉了。

接下来考虑如果做 $\min$，有一个简单的想法是枚举 $\min$ 的值，这是可以做的。

从大到小枚举 $\min$ 的值，将符合条件的 $a$ 拿出来，相邻的组成连通块，对于每个连通块，设大小为 $s$，则可以选 $\lceil\frac{s}{2}\rceil$ 个元素。

但是如何确保最大值一定被选到呢？如果最终最大值没有被选到，就把答案减 $1$，于是这道题做完了。

代码实现（超级垃圾）：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, ans, res, siz;
int a[200005], b[200005];
int fa[200005], sz[200005];
int sumji[200005], sumou[200005];
vector <int> v[200005];
map <int, int> m;
int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find (fa[x]);
}
void merge (int x, int y) {
	int fx = find (x), fy = find (y);
	if (fx != fy) {
		fa[fx] = fy;
		sz[fy] += sz[fx];
	}
}
int func (int x) {
	if (sz[x] & 1) {
		if (x & 1) return sumji[x + sz[x] - 1] - sumji[x - 1];
		return sumou[x + sz[x] - 1] - sumou[x - 1];
	}
	return max (sumji[x + sz[x] - 1] - sumji[x - 1], sumou[x + sz[x] - 1] - sumou[x - 1]);
}
void solve () {
	res = 0;
	cin >> n;
	For (i, 1, n) a[i] = b[i] = fa[i] = sz[i] = sumji[i] = sumou[i] = 0;
	For (i, 1, n) fa[i] = i;
	For (i, 1, n) {
		cin >> a[i];
		b[i] = a[i];
	}
	sort (a + 1, a + n + 1);
	a[n + 1] = 0;
	int tmp = 0, cnt = 0;
	foR (i, n, 1) {
		if (a[i] != a[i + 1]) {
			tmp = i;
			++ cnt;
		}
		m[a[i] ] = tmp;
	}
	For (i, 1, n) v[m[b[i] ] ].push_back (i);
	For (i, 1, n) {
		if (b[i] == a[n]) {
			if (i & 1) sumji[i] = 1;
			else sumou[i] = 1;
		}
		sumji[i] += sumji[i - 1];
		sumou[i] += sumou[i - 1];
	}
	ans = siz = res = 0;
	int tail = n + 1;
	while (1) {
		while (a[tail - 1] == a[tail]) -- tail;
		-- tail;
		if (tail == 0) break;
		for (int loc : v[m[a[tail] ] ]) {
			sz[loc] = 1;
			fa[loc] = loc;
			res += func (loc);
			++ siz;
			if (loc != 1 && b[loc - 1] >= a[tail] && find (loc - 1) != find (loc) ) {
				res -= func (loc);
				res -= func (find (loc - 1) );
				-- siz;
				siz -= ceil (sz[find (loc - 1)] * 1.0 / 2);
				merge (loc, loc - 1);
				res += func (find (loc) );
				siz += ceil (sz[find (loc - 1)] * 1.0 / 2);
			}
			if (loc != n && b[loc + 1] >= a[tail] && find (loc) != find (loc + 1) ) {
				res -= func (find (loc) );
				res -= func (find (loc + 1) );
				siz -= ceil (sz[find (loc)] * 1.0 / 2);
				siz -= ceil (sz[find (loc + 1)] * 1.0 / 2);
				merge (loc + 1, loc);
				res += func (find (loc) );
				siz += ceil (sz[find (loc)] * 1.0 / 2);
			}
		}
		if (res) ans = max (ans, siz + a[tail] + a[n]);
		else ans = max (ans, siz - 1 + a[tail] + a[n]);
	}
	For (i, 1, n) v[i].clear ();
	m.clear ();
	cout << ans << '\n';
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) solve ();
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：3)

考虑钦定最小值。

因为是取 `max`，最大值钦定错了也没事（同时这也是 2A 的解法），但是最小值钦定错了会使答案变大，所以显然钦定最小值更好。

钦定最小值后，你就只能取大于等于这个值的位置，当然我们可以对下标进行一些处理从而让相同值也拥有优先级，这样我们就能做到每一次都是单点修改，便于处理。

考虑进行 dp：

令 $f_{i,0/1,0/1}$ 表示前 $i$ 个第 $i$ 个是否取了，在 $[1,i]$ 是否已经钦定了最大值。

这样不一定能取到钦定的最小值，但是它不取钦定的最小值会在钦定的最小值更大的时候算到，所以如果没有取到钦定的最小值，那么它一定不优，因为值相同最后加上的钦定最小值更小。

这是一个朴素的线性 dp，转移是平凡的，但是你每次都一个 $O(n)$ 来 dp 会 TLE。

上文已经提到过，每次只有一个单点修改，于是我们考虑把这个 dp 放到线段树上维护。

放到线段树上的话，你需要维护线段树上的区间左右端点是否取了，以及是否钦定了最大值，转移（即 `pushup`）仍然是平凡的。

---

## 作者：liugh_ (赞：2)

## [Max Plus Min Plus Size](https://codeforces.com/contest/2019/problem/F)

> 从序列中选取若干个互不相邻的数组成子序列 $l$，使得 $l_{\max}+l_{\min}+|l|$ 最大。
>
> $n\le 2\cdot 10^5$。

易证至少要选一个 $a_{\max}$。

于是最大值确定，考虑从大到小枚举最小值，每次将所有当前最小值打上标记，这些标记组成若干个连通块，问题转化为保证选到 $a_{\max}$ 并使得选的数最多。对于一个连通块 $S$，要么选 $\lceil S/2\rceil$ 个，要么选 $\lfloor S/2\rfloor$ 个，于是考虑先强制所有连通块 $S$ 选 $\lceil S/2\rceil$ 个，这种情况下若没有 $a_{\max}$ 被选，则令答案减一。并查集维护连通块及其大小。

时间复杂度 $O(n\alpha(n)\log n)$ 或 $O(n\alpha(n))$，根据实现决定。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map>
#include<set>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
// #define getchar getchar_unlocked
// #define putchar putchar_unlocked
#define de(x) #x":",x
using namespace std;void bug(){cout<<endl;}
template<class T,class...A>constexpr void bug(T x,A...a){cout<<' '<<x;bug(a...);}
template<class T>constexpr void bug1(const char*s,T x,signed r,signed l=1){cout<<' '<<s;for(signed i=l;i<=r;i++)cout<<x[i]<<' ';cout<<endl;}
template<class T>constexpr void bug2(const char*s,T x,signed r,signed b,signed l=1,signed a=1){cout<<' '<<s<<endl;for(signed i=l;i<=r;i++,cout<<' '<<endl)for(signed j=a;j<=b;j++)cout<<x[i][j]<<' ';cout<<endl;}
template<class T>constexpr void fr(T&x){x=0;signed c=0,f=0;do if(c==45)f=1;while(!isdigit(c=getchar()));do x=(x<<1)+(x<<3)+(c^48);while(isdigit(c=getchar()));if(f)x=-x;}
template<class T>constexpr void fw(T x){signed d[40],l=-1;if(x<0)x=-x,putchar(45);do d[++l]=(x%10)^48;while(x/=10);do putchar(d[l]);while(~--l);}
template<class T>constexpr void tomin(T&a,T b){a=min(a,b);}
template<class T>constexpr void tomax(T&a,T b){a=max(a,b);}

constexpr int maxn=2e5+5;

struct _dsu{
	int fa[maxn],siz[maxn];void init(int n){for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;}
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	void merge(int x,int y){x=find(x);y=find(y);if(x<y)swap(x,y);fa[x]=y;siz[y]+=siz[x];}
}dsu;

void solve(){
	int n;
	cin>>n;
	int a[n+5]{};
	map<int,vector<int>> pos;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		pos[a[i]].pb(i);
	}
	dsu.init(n);
	int len=0,cnt=pos.rbegin()->se.size(),ans=0;
	set<int> mxp[2];
	for(auto p:pos.rbegin()->se)mxp[p&1].insert(p);
	auto has=[&](int p){
		auto it=mxp[p&1].lower_bound(p);
		if(it!=mxp[p&1].end()&&*it<=p+dsu.siz[p]-1)return 1;
		if(dsu.siz[p]&1)return 0;
		it=mxp[p&1^1].lower_bound(p);
		if(it!=mxp[p&1^1].end()&&*it<=p+dsu.siz[p]-1)return 1;
		return 0;
	};
	for(auto it=pos.rbegin();it!=pos.rend();it++){
		auto &v=it->se;
		len+=v.size();
		for(auto p:v){
			if(p>1&&a[p]<=a[p-1]){
				len-=(dsu.siz[dsu.find(p)]+1)>>1;
				len-=(dsu.siz[dsu.find(p-1)]+1)>>1;
				if(has(dsu.find(p)))cnt--;
				if(has(dsu.find(p-1)))cnt--;
				dsu.merge(p,p-1);
				len+=(dsu.siz[dsu.find(p)]+1)>>1;
				if(has(dsu.find(p-1)))cnt++;
			}
			if(p<n&&a[p]<a[p+1]){ // 取小于号以避免算重
				len-=(dsu.siz[dsu.find(p)]+1)>>1;
				len-=(dsu.siz[dsu.find(p+1)]+1)>>1;
				if(has(dsu.find(p)))cnt--;
				if(has(dsu.find(p+1)))cnt--;
				dsu.merge(p,p+1);
				len+=(dsu.siz[dsu.find(p)]+1)>>1;
				if(has(dsu.find(p+1)))cnt++;
			}
		}
		tomax(ans,it->fi+pos.rbegin()->fi+len-(cnt==0));
	}
	cout<<ans<<'\n';
}

signed main(){
	#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	#endif
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int cse=1;
	cin>>cse;
	while(cse--)solve();
}
```

---

## 作者：Richard_Whr (赞：2)

考虑枚举最小值。

对于求选的集合最大值，可以弱化为集合中选了某个数贡献为最大值，考虑最优决策一定会选最大值。

然后问题变成了：只能选权 $\ge x$ 的，不能选相邻的，可以让一个作为最大值的贡献。

这个可以用一个 dp 描述，设 $f_{i,0/1,0/1}$ 表示这一位有没有选，有没有选过贡献给最大值的。

我们从小到大扫描值域，这样我们会不断删除某些数，如果直接暴力维护 dp 的话复杂度是 $n^2$ 的。

然后使用矩阵优化快速维护这个 dp 的过程。

上述操作可以简单实用线段树维护矩阵连乘积，单点修改维护。

做完了。

复杂度 $O(n \log n \times 4^3)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define ls u*2
#define rs u*2+1
using namespace std;
const int N=2e5+10,Inf=1e15;
int n;
int a[N];
struct Matrix//(max,+) 矩阵 
{
	int A[4][4];
	void clear()
	{
		memset(A,-0x3f,sizeof A);
	}
	void make_I()
	{
		clear();
		for(int i=0;i<4;i++) A[i][i]=0;	
	} 
	Matrix operator*(const Matrix &B)const
	{
		Matrix res;res.clear();
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=0;k<4;k++)
				{
					res.A[i][j]=max(res.A[i][j],A[i][k]+B.A[k][j]);
				}
			}
		}
		return res;
	}
	void output()
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				printf("%5d ",A[i][j]);
			}
			puts("");
		}
		puts("");
	}
}I;

Matrix get(int w)
{
	Matrix res;res.clear();
	for(int a=0;a<2;a++)
	{
		for(int b=0;b<2;b++)
		{
			for(int c=0;c<2;c++)
			{
				for(int d=0;d<2;d++)
				{
					if(a && c) continue;
					if(b && d) continue;
					if(!c && d) continue;
					if(c && w<0) continue;
					int val=c+d*w;
					res.A[a*2+b][c*2+(d|b)]=val;
				}
			}
		}
	}
//	res.output();
	return res;
}
struct Tree
{
	int l,r;
	Matrix v;
}tr[N*4];

int T;

void pushup(int u)
{
	tr[u].v=tr[ls].v*tr[rs].v;
}

void build(int u,int l,int r)
{
	tr[u].l=l,tr[u].r=r;
	if(l==r) tr[u].v=get(a[l]);
	else
	{
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(u);
	}
}

void modify(int u,int x)
{
	if(tr[u].l==tr[u].r) tr[u].v=get(-Inf);
	else
	{
		int mid=tr[u].l+tr[u].r>>1;
		if(x<=mid) modify(ls,x);
		else modify(rs,x);
		pushup(u); 
	}
}

vector<int> vec[N];
vector<int> nums;

int find(int x)
{
	return lower_bound(nums.begin(),nums.end(),x)-nums.begin()+1;
}

void solve()
{
	nums.clear();
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],nums.push_back(a[i]);
	build(1,1,n);
	
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	
	for(int i=1;i<=n;i++) vec[find(a[i])].push_back(i);
	
	Matrix F;
	F.clear();
	F.A[0][0]=0;
	
	int res=0;
	
	int m=nums.size();
	for(int i=1;i<=m;i++)
	{
		int Min=nums[i-1];
		Matrix G=F*tr[1].v;
		int val=*max_element(G.A[0],G.A[0]+4);
		res=max(res,Min+val);
		for(auto j:vec[i]) modify(1,j);
		vec[i].clear();
	}
	
	cout<<res<<"\n";
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); 
	
	cin>>T;
	while(T--) solve();
	
	return 0;
}


```

---

## 作者：0xyz (赞：1)

一道很妙的题。动态 DP。

首先，一个很显然的想法是令 $f_{i,j,k,0/1}$ 表示考虑前 $i$ 个数，红数最小值为 $j$，红数最大值为 $k$，第 $i$ 个数不涂/涂红时的最大红数数量。枚举前 $i-1$ 个最小值/最大值来转移，时间复杂度 $O(n^4)$。

考虑优化。显然这个状态数就有很大问题，所以我们必须减少状态数量。根据数学直觉，最优解里面一定有一个染色方案染红了至少一个全局最大值。我们取任意一个染色方案，其染红的数下标集合为 $S$，如果它不包含任何一个全局最大值，那么我们假设有一个全局最大值 $a_i$，考虑染色集合 $(S-\{i-1\}-\{i+1\})\cup\{i\}$，它符合不能相邻的条件，且 $\Delta\min\ge 0,\Delta\max\ge 1,\Delta\text{ size}\ge -1$，从而答案不会更小。

从而，我们可以钦定红数的 $\max$ 就是全局最大值 $mx$。接下来，我们从大到小枚举红数的 $\min$，然后求出“$mx$ 至少染红一个，所有小于 $\min$ 的数均不能染红，染红的数不能相邻”情况下染红数最大个数。如果暴力做依然是 $O(n^2)$ 的，不行。我们考虑每次减小 $\min$ 之后带来的影响，实际上就是一些原本必定不能染红的变成可染可不染了。我们维护每一个连通块 $i:[l,r]$，令 $f_{i,0/1,0/1,0/1}$ 表示连通块 $i$ 左端点 $l$ 不染/染，右端点 $r$ 不染/染，此连通块内没有/有强制将一个 $mx$ 染红。那么，令 $e_i=\max\{f_{i,*,*,0}\},h_i=\min\{e_i-f_{i,*,*,1}\}$，最大的染色个数就是 $(\sum e_i)-\min\{h_i\}$。$e_i$ 在合并的时候直接维护即可。至于 $h_i$，其实它要么是 $inf$（即这个区间不存在 $mx$），要么是 $0,1$（若这个区间有 $mx$，且所有最大化染色个数的方案都不包括全局最大值 $mx$，那么一定是 $l,r$ 同奇偶，最大化染色个数的方案是将与 $l,r$ 同奇偶的所有点染色，共计 $(r-l+2)/2$ 个，那么我们取原本染色集合的补集就一定染了 $mx$，且染色个数仅减少了 $1$），所以我们开两个桶记录一下 $0,1$ 的个数即可。时间复杂度 $O(n\alpha(n))$。

为了省事，我写的代码是 $O(n\log n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int _=4e5+5,inf=1e9;
multiset<int>d;
int f[_][2][2][2],a[_],b[_],v[_],l[_],r[_],h[_],e[_],c,s,mx,w,n,T;
map<int,vector<int> >p;
int g(int x){
	return b[x]==x?x:b[x]=g(b[x]);
}
inline void del(int x){
	multiset<int>::iterator u=d.lower_bound(x);
	if(u!=d.end()&&(*u)==x)d.erase(u);
}
inline void mer(int x,int y){
	b[x]=b[y]=++c;l[c]=l[x];r[c]=r[y];
	del(h[x]);del(h[y]);s-=e[x];s-=e[y];
	h[c]=inf;e[c]=0;
	for(int i:{0,1})
		for(int j:{0,1})
			for(int k:{0,1})
				for(int I=0;I<2-k;I++)
					for(int J:{0,1})
						for(int K:{0,1})f[c][i][j][J|K]=max(f[c][i][j][J|K],f[x][i][k][J]+f[y][I][j][K]);
	for(int i:{0,1})
		for(int j:{0,1})e[c]=max(e[c],f[c][i][j][0]);
	for(int i:{0,1})
		for(int j:{0,1})h[c]=min(h[c],e[c]-f[c][i][j][1]);
	d.insert(h[c]);s+=e[c];
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;mx=w=s=0;c=n;p.clear();d.clear();
		for(int i=1;i<=n;i++){
			cin>>a[i];v[i]=0;
			e[i]=1;l[i]=r[i]=i;
			mx=max(mx,a[i]);
			p[-a[i]].push_back(i);
		}
		for(int i=1;i<n+n;i++){
			b[i]=i;
			for(int j:{0,1})
				for(int k:{0,1})
					for(int I:{0,1})f[i][j][k][I]=-inf;
		}
		for(int i=1;i<=n;i++)
			if(a[i]==mx){
				h[i]=0;
				for(int j:{0,1})f[i][j][j][j]=j;
				f[i][1][1][0]=1;
			}else{
				h[i]=inf;
				for(int j:{0,1})f[i][j][j][0]=j;
			}
		for(auto i:p){
			for(int j:i.second){
				d.insert(h[j]);s+=e[j];
				if(j>1&&v[j-1])mer(g(j-1),g(j));
				if(j<n&&v[j+1])mer(g(j),g(j+1));
				v[j]=1;
			}
			w=max(w,mx-i.first+s-*d.begin());
		}
		cout<<w<<'\n';
	} 
	return 0;
}
```

---

## 作者：happybob (赞：1)

容易发现全局的 $\max$ 必然会取到。如果不取，那么你肯定希望你取的数量更多。但是数量不会比取最大值多超过 $1$。

于是考虑枚举最小值，问题转化为能否在取的数量最多的情况下取到最大值。将目前大于等于最小值的数分为若干连续段就可以简单维护了。

---

