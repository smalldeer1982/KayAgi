# 「REOI-p1」按摩

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/iojg3sgx.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/5m1v3g37.png)

出题人：LinkyChristian

验题人：Legitimity

文案：小糯米

## 题目描述



无论是勇者还是妖精，在执行任务时，都难免会患上一些特有的“职业病”。其中，在这份“常见勇者职业病名单”上排名第一的，叫作“急性魔力中毒”。虽然魔力中毒在表面上只是类似于发高烧的症状，但倘若没有每次根除，就会变成痼疾，身体马上就会超出负荷极限。魔力中毒的治疗方案，说起来倒是颇为实在：找到魔力淤积的部位，用力按压，利用类似中医按摩的原理，将其淤积点给揉开。具体的治疗原理如下：

人体的魔力脉络，可以视作一个 $n \times n$ 的网格。与中医腧穴中的经穴、经外穴分类类似，魔力的作用“穴位”，亦可以大致上分为阴性和阳性。为了更直观的叙述，我们不妨将阳性的魔力穴位在网格上用黑点表示。而魔力出现淤积，大概率的情形下便是因使用魔力导致肌肉紧绷，从而使得本是阴性的穴位变为阳性，或者阳性变为阴性的结果。所谓的按摩，其实就是将其恢复到其应有的状态，从而疏通魔力。判断按摩是否完成的标志，便是在这个网格中，是否存在一个以黑点作为顶点的所有边均平行于网格的多边形。

现在，经过了一场激烈的战斗，珂朵莉因使用魔力过度，又出现了急性魔力中毒的症状。在给珂朵莉检查身体的时候，威廉发现，在珂朵莉的魔力脉络上，有 $m$ 个魔力穴位呈阳性反应。现在他要进行 $k$ 次按摩，每次的按摩都会给出一个点，如果该点的穴位呈阳性则变为阴性，反之则成为阳性。

威廉想知道，在每一次按摩结束后，他的治疗是否已经完成。

------------

形式化题面：给出一个  $n \times n$ 的网格，其中有 $m$ 个点为黑点。

共有 $k$ 个操作，每次操作使一个点黑白反转。判断在每次操作结束后是否存在一个以黑点作为顶点的所有边均平行于网格的多边形。

## 说明/提示

对于样例1，初始状态为

![](https://cdn.luogu.com.cn/upload/image_hosting/ykf02pm6.png)

之后每次操作后状态依次为

![](https://cdn.luogu.com.cn/upload/image_hosting/lilddgfo.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/ml2qqt5d.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/lilddgfo.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/altczbf0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/uqvq4u0j.png)

对于 $5\%$ 的数据，$n\le 10,m\le 5,k\le 100$。  
对于 $10\%$ 的数据，$n,k\le 100$。  
对于 $20\%$ 的数据，$n,k\le 1000$。  
对于 $80\%$ 的数据，$n,k\le 5\times10^4$。   
对于另外 $10\%$ 的数据，$k=1$。  
对于 $100\%$ 的数据，$m\le n \le 10^5,k\le 10^5$。  

## 样例 #1

### 输入

```
100 3
1 1
2 2
1 2
5
5 5
2 1
2 1
5 1
2 5```

### 输出

```
No
Yes
No
No
Yes```

# 题解

## 作者：LinkyChristian (赞：16)

简略版：

将每个点 $(i,j)$ 看做连接行 $i$ 与列 $j$ 的边，当边构成环时则符合条件。

将修改操作丢到线段树上，使用并查集判断图是否成环即可。

---

## 作者：bsTiat (赞：12)

首先考虑静态时，是否存在一个以黑点作为顶点的所有边均平行于网格的多边形如何判断，注意到，条件其实就是存在一个边平行于网格的环，那么我们将每个点看做连接行 $ i $ 与列 $ j $ 的边，当存在环时满足条件。

然后考虑动态的，我们只要将修改操作丢到线段树上，线段树分治一下，用可撤销的并查集来判环，就可以了。

```cpp
#include<bits/stdc++.h>
# define N (500005)
# define mid (l+r>>1)
using namespace std;
inline int rd(){
	char c=getchar();int sum=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){sum=(sum<<3)+(sum<<1)+(c^48);c=getchar();}
	return sum*f;
}
int u[N],v[N],n,m,k,f[N],d[N];
struct node{
	int l,r;
	vector<pair<int,int> >v;
}t[N];
map<pair<int,int>,int>mp;
stack< pair<int,int> >cl;
int find(int x){
	while(x^f[x])x=f[x];
	return x;
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r)return;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
	return;
}
void update(int p,int l,int r,pair<int,int> x){
	if(t[p].l>r||t[p].r<l)return;
	if(t[p].l>=l&&t[p].r<=r){
		t[p].v.push_back(x);
		return;
	}
	update(p<<1,l,r,x);
	update(p<<1|1,l,r,x);
	return;
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(d[x]>d[y])swap(x,y);
	cl.push(make_pair(x,d[x]==d[y]));
	f[x]=y;d[y]+=(d[x]==d[y]);
}
void dfs(int p,int l,int r){
	bool flag=1;
	int st=cl.size(),x,y;
	for(int i=0;i<t[p].v.size();++i){
		pair<int,int> s=t[p].v[i];
		x=find(s.first);y=find(s.second);
		if(x==y){
			flag=0;
			for(int j=l;j<=r;++j)
				printf("Yes\n");
			break;
		}
		merge(s.first,s.second);
	}
	if(flag){
		if(l==r)printf("No\n");
		else {
			dfs(p<<1,l,mid);
			dfs(p<<1|1,mid+1,r);
		}
	}
	while(cl.size()>st){
		x=cl.top().first;
		y=cl.top().second;
		f[x]=x;d[x]-=y;
		cl.pop();
	}
}
signed main(){
	int x,y;
	n=rd();m=rd();
	for(int i=1;i<=2*n;++i)f[i]=i;
	for(int i=1;i<=m;++i){
		x=rd();y=rd()+n;
		mp[make_pair(x,y)]=1;
	}
	k=rd();
	build(1,1,k);
	for(int i=1;i<=k;++i){
		x=rd();y=rd()+n;
		if(mp[make_pair(x,y)]){
			update(1,mp[make_pair(x,y)],i-1,make_pair(x,y));
			mp.erase(make_pair(x,y));
		}else mp[make_pair(x,y)]=i;
	}
	for(auto i=mp.begin();i!=mp.end();++i)
		update(1,i->second,k,i->first);
	dfs(1,1,k);
	return 0;
}
```


---

## 作者：tjtdrxxz (赞：8)

我们发现一个符合要求的图形是一个环，所以考虑用并查集。

好，那现在怎么处理点修改呢？其实很简单，我们想个事，如果一个点的状态被改变，肯定会有一些边被断开或者连上。这是就能发现好像和线段树分治的模板题很像，一个点如果出现，就连上与他同一行或同一列的点，反之亦然，而且一个点的出现或者消失是有时间段的（当然也可能出现到最后还在的情况）。

所以我们还是用线段树对时间进行分治，用并查集维护环就好了。

当然，因为 $ n $ 有亿点点大，所以读入的时候还需要离散化一下捏~

code：
```cpp
# include <bits/stdc++.h>
# define endl '\n'
using namespace std;
const int N = 2e6 + 5;
int fa[N], siz[N], n;
stack <int> q;
using size_s = unsigned int;
struct que
{
	int u, v, l, r;
}a[N];
int find (int x)
{
	return x == fa[x] ? x : find (fa[x]);
}
bool merge (int x, int y)
{
	x = find (x), y = find (y);
	if (x == y) return 0;
	if (siz[x] < siz[y])
	{
		swap (x, y);
	}
	fa[y] = x;
	siz[x] += siz[y];
	q.push (y);
	return 1;
}
void cut ()
{
	int x = q.top();
	q.pop();
	int y = fa[x];
	fa[x] = x;
	siz[y] -= siz[x];
}
struct node
{
	int x, y;
	node (int x, int y) :
		x (x), y (y) {}
	bool operator < (const node &b) const
	{
		return x == b.x ? y < b.y : x < b.x;
	}
};
struct SegTree
{
	size_s l, r, mid;
	SegTree *ls, *rs;
	vector <node> stk;
	SegTree () {}
	SegTree (size_s s, size_s t) :
	l {s}, r {t}, mid { (l + r) >> 1 },
	ls {nullptr}, rs {nullptr}
	{
		if (l == r)
		{
			return;
		}
		ls = new SegTree (l, mid + 0);
		rs = new SegTree (mid + 1, r);
	}
	void modify (size_s s, size_s t, node x)
	{
		if (s > t) return;//如果一个点同时出现以及被删，就忽略这次操作。
//		cout << l << ' ' << r << endl;
		if (s <= l and r <= t)
		{
			stk.push_back (x);
			return;
		}
		if (mid >= s) ls -> modify (s, t, x);
		if (mid <  t) rs -> modify (s, t, x);
	}
	void solve (bool check)
	{
//		cout << l << ' ' << r << endl;
		int cnt = 0;
		for (auto now : stk)
		{
			int u = now.x;
			int v = now.y;
			if (find (u) == find (v))
			{
				check = 0;
				for (int i = l; i <= r; i ++)
				{
					cout << "Yes" << endl;
				}
				goto home;
			}
			else
			{
				if (merge (u, v)) cnt ++;
			}
		}
		if (l == r)
		{
			cout << (check ? "No" : "Yes") << endl;
		}
		else
		{
			ls -> solve (true);
			rs -> solve (true);
		}
		home : ;
		while (cnt --)
		{
			cut ();
		}
	}
};//线段树分治模板。
map <node, int> mp;
int m, t;
int main ()
{
	ios :: sync_with_stdio (0);
	cin.tie (0), cout.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= m; i ++)
	{
		int x, y;
		cin >> x >> y;
		y += n;
		mp[node (x, y)] = 1;
	}
	cin >> t;
	SegTree tr = SegTree (1, t);
	for (int i = 1; i <= n * 2; i ++) fa[i] = i, siz[i] = 1;
	for (int i = 1; i <= t; i ++)
	{
		int x, y;
		cin >> x >> y;
		y += n;
		if (mp[node (x, y)])
		{
			tr.modify (mp[node (x, y)], i - 1, node (x, y));//因为要和与他同一行以及同一列的连边，所以给每行每列一个超级源点，每次就连源点就好了，免得暴力连边坠机。
			mp.erase (node (x, y));
		}
		else
		{
			mp[node (x, y)] = i;
		}
	}
	for (auto it : mp)
	{
		tr.modify (it.second, t, it.first);//把最后还没加的点加进去。
	}
	tr.solve (true);//求答案。
}
```

---

## 作者：irris (赞：4)

网格图可以套路式的转化为二分图，共有 $n$ 行和 $n$ 列。这样一个点的加入和删除可以用带修并查集轻松地维护。于是，没有环转化为有环是容易判定的，而有环转化为无环则很难感受。

所以就可以变成 [线段树分治](https://www.luogu.com.cn/problem/P5787) 的形式，把每条边的出现时间扔到线段树上，在进入每个时间段节点的时候只有加边，这个很好维护，如果有环就输出 $r - l + 1$ 个 `Yes` 即可，最后及时撤销；到了叶子节点就输出 `No` 停止递归。

注意，MLE 70 的可能原因是第一次操作为删点，这样你就会试图插入一个出现时间段为 $[1, 0]$ 的边，递归下去就寄了。

## Code

```cpp
#include <bits/stdc++.h>

#define MAXN 100001
int det[MAXN << 1], fa[MAXN << 1];
inline int find(int x) {
	while (x != fa[x]) x = fa[x];
	return x;
}

std::stack<std::pair<int, int>> s;
inline void merge(int x, int y) {
	x = find(x), y = find(y);
	if (det[x] > det[y]) std::swap(x, y);
	fa[x] = y, det[y] += (det[x] == det[y]);
	s.push({x, y});
}
inline void split(int x, int y) { fa[x] = x, det[y] -= (det[x] == det[y]); }

int N, M, K;
std::vector<std::pair<int, int>> e[MAXN << 2];
void add(int x, int y, int l, int r, int ql = 1, int qr = K, int pos = 1) {
	if (l > r) return;
	if (l <= ql && qr <= r) return (void)(e[pos].push_back({x, y}));
	int mid = ql + qr >> 1, lc = pos << 1, rc = lc | 1;
	if (l <= mid) add(x, y, l, r, ql, mid, lc);
	if (mid < r) add(x, y, l, r, mid + 1, qr, rc);
}
void dfs(int l = 1, int r = K, int pos = 1) {
//	std::cout << pos << '\n';
//	for (auto i : e[pos]) std::cout << i.first << ' ' << i.second << '\n';
	bool flag = false;
	int o = s.size();
	for (auto i : e[pos]) {
		if ((flag = find(i.first) == find(i.second))) break;
		merge(i.first, i.second);
	}
	if (flag) {
		for (int i = l; i <= r; ++i) puts("Yes");
	} else if (l == r) {
		puts("No");
	} else {
		int mid = l + r >> 1, lc = pos << 1, rc = lc | 1;
		dfs(l, mid, lc), dfs(mid + 1, r, rc);
	}
	while (s.size() > o) split(s.top().first, s.top().second), s.pop();
}

std::map<std::pair<int, int>, int> mp;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	std::cin >> N >> M;
	for (int i = 1; i <= N * 2; ++i) fa[i] = i, det[i] = 1;
	for (int i = 1, x, y; i <= M; ++i) 
		std::cin >> x >> y, mp[{x, y + N}] = 1;
	std::cin >> K;
	for (int i = 1, x, y; i <= K; ++i) {
		std::cin >> x >> y;
		if (mp[{x, y + N}]) {
			add(x, y + N, mp[{x, y + N}], i - 1), mp.erase({x, y + N});
		} else mp[{x, y + N}] = i;
	}
	for (auto i : mp) add(i.first.first, i.first.second, i.second, K);
	return dfs(), 0;
}
```

---

## 作者：thh_loser (赞：1)

# P8460 「REOI-p1」按摩 题解



[题目链接](https://www.luogu.com.cn/problem/P8460)



## 题意

给出一个 $n\times n$ 的网格，初始时有 $m$ 个黑色点，其它的为白色点。

给出 $k$ 次操作，每次操作使一个点黑白反转。求每次操作结束后是否存在一个以黑点作为顶点的所有边均平行于网格的多边形。



## 思路

这道题每次询问的内容是一个经典问题，具体的，对于每一个点，相当于它与它处在的行、列上的每一个其它点连一条边，这个我们可以用并查集维护，对于一次合并，如果两个点属于同一个集合，则会形成一个环。同时我们发现一个点存在的时间就是从白点变成黑点开始，直到又变回白点，这个我们可以用线段树分治维护。

在实现上，我们使用经典的线段树分治 $+$ 可撤销并查集，对于每一行、列，建一个超级源点，减少合并次数，一个点的合并只用将它所处的行和列合并即可。



## code 

```c++
#include<bits/stdc++.h>
#define N 200010
#define int long long
using namespace std;
const int base=100000;
int t(1),n,m,k;
unordered_map<int,int>las;
unordered_map<int,bool>flag;
vector<int>dot;
struct edg{
	int u,v;
};
struct node{
	int l,r;
	vector<edg>e;
}tr[N<<2];
struct V_DSU{//可撤销并查集板子 
	int fa[N<<1],siz[N<<1],sta[N<<1],top;
	int gf(int x){return fa[x]==x?x:gf(fa[x]);}	
	void merge(int x,int y){
		int fx=gf(x),fy=gf(y);
		if(fx==fy)return;
		if(siz[fx]>siz[fy])swap(fx,fy);
		sta[++top]=fx;
		fa[fx]=fy;
		siz[fy]+=siz[fx];
	}
	void del(int res=0){
		while(top>res){
			siz[fa[sta[top]]]-=siz[sta[top]];
			fa[sta[top]]=sta[top];
			--top;
		}
	}
	bool together(int x,int y){return gf(x)==gf(y);}
}dsu;
void build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(l==r)return void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void modi(int x,int l,int r,int u,int v){
	if(tr[x].l>r||tr[x].r<l)return void();
	if(tr[x].l>=l&&tr[x].r<=r){
		return tr[x].e.emplace_back((edg){u,v}),void();
	}
	modi(x<<1,l,r,u,v);
	modi(x<<1|1,l,r,u,v);
}
void dfs(int x){
	int rec=dsu.top,el=tr[x].e.size();
//	cout<<"		"<<x<<"("<<tr[x].l<<" "<<tr[x].r<<")"<<" "<<el<<"\n";
	for(int i=0;i<el;++i){
//		cout<<tr[x].e[i].u<<" "<<tr[x].e[i].v+n<<"\n";
		if(dsu.together(tr[x].e[i].u,tr[x].e[i].v+n)){
		//如果当前这些边已经形成环，则往下就算不再加边也存在环，直接全部输出 
			for(int j=tr[x].l;j<=tr[x].r;++j){
				cout<<"Yes\n";
			}
//			cout<<"back "<<x<<'\n';
			return dsu.del(rec),void();
		}
		dsu.merge(tr[x].e[i].u,tr[x].e[i].v+n);//我将列编号加了n,便于区分 
	}
	if(tr[x].l==tr[x].r){
		cout<<"No\n";
//		cout<<"back :"<<x<<"\n";
		return dsu.del(rec),void();//叶节点记得也要弹边 
	}
	dfs(x<<1);
	dfs(x<<1|1);
//	cout<<"back "<<x<<'\n';
	return dsu.del(rec),void();
}
signed main(){
	//cin>>t;
	while(t--){
		scanf("%lld%lld",&n,&m);
		for(int i=1,x,y;i<=m;++i){
			scanf("%lld%lld",&x,&y);
			if(flag.find(x*base+y)!=flag.end())continue; //抽象数据，初始包含重复点，需要特判 
			las[x*base+y]=1;
			flag[x*base+y]=true;
			dot.emplace_back(x*base+y);
		}
		for(int i=1;i<=n<<1;++i)dsu.fa[i]=i,dsu.siz[i]=1;
		scanf("%lld",&k);
		build(1,1,k);//时间轴是1~k 
		for(int i=1,x,y;i<=k;++i){
			scanf("%lld%lld",&x,&y);
			int id=x*base+y;
			if(flag.find(id)==flag.end()){
				flag[id]=true;
				las[id]=i;
				dot.emplace_back(id);
			}
			else{
				if(flag[id]){//flag为true说明当前是黑点 
					modi(1,las[id],i-1,x,y);
					flag[id]=false;
				}
				else{//否则为白点 
					flag[id]=true;
					las[id]=i;
				}
			}
		}
		for(auto x:dot){
		//没有配对的点相当于它从开始到结束一直存在 
			if(flag[x]){
				modi(1,las[x],k,x/base,x%base);
			}
		}
		dfs(1);
	}
	return 0;
}
```

---

## 作者：CuFeO4 (赞：1)

考虑如何判断是否存在一个多边形，就是判断是否存在一个边平行于网络的环，很显然可以用并查集维护。

考虑将 $(i,j)$ 当成将行 $i$ 和列 $j$ 连一条边，然后就可以用并查集判环了。

多组询问，那么点为黑点的时间为时间段，这很线段树分治，那么直接套线段树分治和可撤销并查集即可。

时间复杂度 $O(k\log k\log n)$。

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
// using namespace __gnu_pbds;
// using namespace __gnu_cxx;
using namespace std;
#define rep(i,s,t,p) for(int i = s;i <= t; i += p)
#define drep(i,s,t,p) for(int i = s;i >= t; i -= p)
#define Infile(x) freopen(#x".in","r",stdin)
#define Outfile(x) freopen(#x".out","w",stdout)
#define Ansfile(x) freopen(#x".ans","w",stdout)
#define Errfile(x) freopen(#x".err","w",stderr)
#ifdef LOCAL
    FILE *InFile = Infile(in),*OutFile = Outfile(out);
    // FILE *ErrFile = Errfile(err);
#else
    FILE *InFile = stdin,*OutFile = stdout;
#endif
using ll=long long;using ull=unsigned long long;
using db = double;using ldb = long double;
const int N = 1e5 + 1;
#define pii pair<int,int>
#define mk make_pair
#define eb emplace_back
int n,m,k;
map<pii,int> mp;
struct DSU{
    vector<int> fa,siz;
	stack<int> sta;
    inline void init(int n){
        fa.resize(n+1);siz.resize(n+1);
        rep(i,1,n,1) fa[i] = i,siz[i] = 1;
    }
    inline int get_fa(int x){while(x ^ fa[x]) x = fa[x];return x;}
    inline bool merge(int x,int y){
        x = get_fa(x),y = get_fa(y);
        if(x == y) return false;
        if(siz[x] > siz[y]) swap(x,y);
        fa[x] = y,siz[y] += siz[x],sta.push(x);
        return true;
    }
    inline void undo(){
        int x = sta.top();sta.pop();
        siz[fa[x]] -= siz[x],fa[x] = x;
    }
    inline void undo(int res){while(sta.size() > res) undo();}
}D;
struct Segment_Tree_Divide{
	struct node{
		int l,r;
    	vector<pii> v;
	}t[N<<2];
	void B(int k,int l,int r){
		t[k].l = l,t[k].r = r;
		vector<pii> ().swap(t[k].v);
		if(l == r) return;
		int mid = (l + r) >> 1;
		B(k<<1,l,mid);B(k<<1|1,mid+1,r);
	}
    void I(int k,int ql,int qr,int x,int y){
        if(ql <= t[k].l && t[k].r <= qr) return t[k].v.eb(mk(x,y));
        int mid = (t[k].l + t[k].r) >> 1;
        if(ql <= mid) I(k<<1,ql,qr,x,y);
        if(qr > mid) I(k<<1|1,ql,qr,x,y);
    }
    void Q(int k){
        int bk = D.sta.size();
        bool flag = false;
        for(auto i:t[k].v){
            bool pd = !D.merge(i.first,i.second);
            flag |= pd;
            if(flag){
                rep(i,t[k].l,t[k].r,1) cout<<"Yes\n";
                break;
            }
        }
        if(!flag){
            if(t[k].l == t[k].r) cout<<"No\n";
            else Q(k<<1),Q(k<<1|1);
        }
        D.undo(bk);
    }
}T;
inline void solve(){
    cin>>n>>m;D.init(n+n);
    rep(i,1,m,1){
        int x,y;cin>>x>>y;
        mp[mk(x,y)] = 1;
    }
    cin>>k;T.B(1,1,k);
    rep(i,1,k,1){
        int x,y;cin>>x>>y;
        if(mp.find(mk(x,y)) != mp.end()){
            T.I(1,mp[mk(x,y)],i-1,x,y+n);
            mp.erase(mk(x,y));
        }
        else mp[mk(x,y)] = i;
    }
    for(auto i:mp) T.I(1,i.second,k,i.first.first,i.first.second+n);
    T.Q(1);
}
signed main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
```

---

## 作者：Nygglatho (赞：1)

注意到，一个点 $(x,y)$ 成为「顶点」，那么连接这个多边形的边就会在这个点转 $90^\circ$。

那么，这个点 $(x,y)$ 就可以连接第 $x$ 行的**任意一点**，以及第 $y$ 列的任意一点。

不妨构建一个无向图，将第 $i$ 行抽象为无向图中第 $i$ 个点，第 $i$ 列抽象为无向图中第 $i+n$ 个点。

那么，原来网格中的 $(x,y)$ 可以连接第 $x$ 行以及第 $y$ 列，即构建的无向图中点 $x$ 以及点 $y+n$。

考虑连接多边形的性质，可以发现，这个多边形的顶点是类似于这样的：$[(a_1,b_1),(a_1,b_2),(a_2,b_2),\cdots,(a_1,b_1)]$。换句话说，**相邻两个点横纵坐标仅有一个发生了改变。**

由于这个性质，这个多边形的点 $a_1$ 可以连接 $b_1+n,b_2+n$，而 $a_2$ 又可以连接 $b_2+n,\cdots$，最后通过 $b_1+n$ 回到 $a_1$。这显然是一个**环**的形状。

接下来可以将原问题转化一下：

- 加入一条边 $(x,y+n)$；
- 删除一条边 $(x,y+n)$；
- 在每次操作之后，输出图中是否有环。

这是一个非常经典的 Trick：[线段树分治](https://oi-wiki.org/topic/segment-tree-offline/)。使用线段树分治解决。

具体地，将询问离线下来，那么第 $i$ 时刻加入操作产生的边会持续至删除操作时刻 $j$ 前面一时刻（即 $j-1$），特别地，如果一开始就存在且不是第 $1$ 时刻就被删除，那么为加入时间为 $1$，如果没有被删除，那么持续至 $k$。

然后维护一个记录每个时刻含有的边的线段树，具体地，整体维护一个可撤销并查集，对于在 $[l,r]$ 区间内存在的边 $(x,y+n)$，将这条边加入至可撤销并查集中。并且并查集判断有没有环，有环则 $[l,r]$ 区间直接输出 $\tt Yes$。最后在遍历别的时刻的时候将操作撤销，直到线段树中没有仅存在于上一时刻的边即可。由于线段树的结构，使用栈可以高效地维护。

```cpp
#include "bits/stdc++.h"
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
#define ull unsigned long long

#define OPEN freopen (".in", "r", stdin); freopen (".out", "w", stdout);
#define DATA freopen (".in", "w", stdout);

#define pc __builtin_popcount
#define db double
#define pii pair<int, int>
#define fi first
#define se second

#define F(i,x,y) for (int i = (x); i <= (y); ++i)
#define D(i,x,y) for (int i = (x); i >= (y); --i)

#define lttm iterator
#define fp iterator
#define srs rterator
#define moon iterator

namespace Maths {
	ll fac[560000];

	void init() {

		fac[0] = 1ll;

		F(i, 1, 500000) fac[i] = fac[i - 1] * i % mod;
	}

	ll qpow(ll x, ll y) {
		if (y == 0ll) return 1ll;

		ll w = qpow(x, y / 2ll);

		if (y % 2ll) return (w * w % mod) * x % mod;
		else return w * w % mod;
	}

	inline ll C(ll x, ll y) {
		return (fac[x] * qpow(fac[y], mod - 2ll) % mod) * qpow(fac[x - y], mod - 2ll) % mod;
	}

	inline ll div(ll x) {
		return qpow(x, mod - 2ll);
	}
}

int n, m, k;

struct Dsu {
	int fa[680000], siz[680000];
	
	void Init () {
		F(i, 1, n << 1) fa[i] = i, siz[i] = 1;
	}
	
	int Find (int x) {
		if (x == fa[x]) return x;
		return Find(fa[x]);
	}
	
	stack <tuple <int, int, int, int> > opt;
	
	int Merge (int x, int y, int l, int r) {
		int tx = Find(x), ty = Find(y);
		if (tx == ty) {
			return 1;//判断是否已经连通
		}
		
		if (siz[tx] > siz[ty]) {
			fa[ty] = tx;
			siz[tx] += siz[ty];
			
			opt.push({tx, ty, l, r});
		} else {
			fa[tx] = ty;
			siz[ty] += siz[tx];
			
			opt.push({ty, tx, l, r});
		}
		return 0;
	}
	
	void Del (int x, int y) {
		fa[y] = y;
		siz[x] -= siz[y];
	}
	
	void Remove (int l, int r) {
		while (! opt.empty()) {
			if (get<3> (opt.top()) >= l) break ;
			
			Del (get<0> (opt.top()), get<1> (opt.top()));
			
			opt.pop();
		}
	}
};//可撤销并查集

map <pii, int> mp;

pii pt[310000];

int ans[680000];

namespace Sgt{
	vector <pii > d[680000];
	
	Dsu Hoshino;
	
	void Add (int l, int r, int s, int t, int p, pii v) {
		if (l <= s && t <= r) {
			d[p].push_back(v);
			return ;
		}
		
		int m = (s + t) >> 1;
		if (l <= m) Add (l, r, s, m, p << 1, v);
		if (m < r) Add (l, r, m + 1, t, p << 1 | 1, v);
	}
	
	void Dfs (int l, int r, int p) {
		Hoshino.Remove(l, r);//撤销
		int flg = 0;
		for (auto i : d[p]) {
			int ct = Hoshino.Merge (i.first, i.second + n, l, r);//已经连通，再加一条边之后一定会产生环
			flg |= ct;
			if (flg) break ;
		}
		if (flg) {
			F(i, l, r) ans[i] = 1;
			return ;
		}
		if (l == r) return ;
		int m = (l + r) >> 1;
		Dfs (l, m, p << 1);
		Dfs (m + 1, r, p << 1 | 1);
	}
}//线段树分治

int main() {
	IOS
	
	cin >> n >> m;
	Sgt::Hoshino.Init();
	
	F(i, 1, m) cin >> pt[i].first >> pt[i].second, mp[pt[i]] = 1;
	cin >> k;
	F(i, 1, k) {
		int x, y;
		cin >> x >> y;
		if (mp[{x, y}] != 0) {
			if (i != 1) Sgt::Add(mp[{x, y}], i - 1, 1, k, 1, {x, y});
			mp[{x, y}] = 0;
		} else {
			mp[{x, y}] = i;//转换操作
		}
	}
	for (map <pii, int> :: fp five_pebbles = mp.begin(); five_pebbles != mp.end(); ++ five_pebbles) {
		if (five_pebbles -> second != 0) {
			Sgt::Add (five_pebbles -> second, k, 1, k, 1, five_pebbles -> first);
		}
	}
	Sgt::Dfs (1, k, 1);
	
	F(i, 1, k) {
		if (ans[i]) cout << "Yes\n";
		else cout << "No\n";
	}
}
```

---

## 作者：DengDuck (赞：1)

线段树分治的板子题，把每个行每个列看作是一个点，每个表格点相当于行向列连边，多边形就是一个环。

所以我们就求出所有的边，然后存在线段树上，遍历过程中维护并查集即可。

注意并查集不要路径压缩，要写按秩合并。

然后你会发现喜提 $80$ 分。

我找到了之前也拿过 $80$ 的 $\color{red}{\text{z}}\color{black}{\text{ltqwq}}$ 问了一下。

然后两个人都口吐芬芳了。

![](https://cdn.luogu.com.cn/upload/image_hosting/odcj3y4q.png)

判掉就行了。

时间复杂度为 $\mathcal O(n\log n)$，因为调试 $80$ 分所以代码有一些艺术成分很高的调试代码。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define fir first
#define sec second
#define pb push_back
using namespace std;
LL Ecnt=0,dkcnt;
const LL N=3e5+5;
LL n,m,q,fa[N],sz[N];
struct node
{
	LL l,r;
	vector<LL>v;
}t[N*8];
struct edge
{
	LL u,v,l,r;
}E[N*3];
map<pLL,LL>Ma;
LL find(LL x)
{
	if(fa[x]==x)return x;
	return find(fa[x]);
}
void build(LL rt,LL l,LL r)
{
	t[rt].l=l,t[rt].r=r;
	if(l==r)return;
	LL mid=l+r>>1;
	build(rt*2,l,mid),build(rt*2+1,mid+1,r);
	
}
void ins(LL rt,LL x)
{
	if(t[rt].r<E[x].l||E[x].r<t[rt].l)return;
	if(E[x].l<=t[rt].l&&t[rt].r<=E[x].r)
	{
		t[rt].v.pb(x);
		//cout<<t[rt].l<<' '<<t[rt].r<<' '<<x<<endl;
		return;
	}
	ins(rt*2,x),ins(rt*2+1,x);
}
void work(LL rt,LL flg)
{
//	if(rt<=3)
//	{
//		cout<<rt<<endl;
//		for(int i=1;i<=n;i++)	//	for(int i=1;i<=5;i++)
//		{
//			cout<<find(i)<<' ';
//		}
//		cout<<endl;
//		for(int i=n+1;i<=2*n;i++)
//		{
//			cout<<find(i)<<' ';
//		}
//		cout<<endl<<endl;		
//	}

	vector<LL>v;
	for(LL i:t[rt].v)
	{
		LL fx=find(E[i].u),fy=find(E[i].v);
		if(fx==fy||flg)
		{
			flg=1;
			break;
		}
		if(sz[fx]>sz[fy])swap(fx,fy);
		fa[fx]=fy,sz[fy]+=sz[fx];
		v.pb(fx);
	}
	if(t[rt].l==t[rt].r)
	{
		if(t[rt].l)
		{
			dkcnt++;
			if(!flg)puts("No");
			else puts("Yes");
		}
	}
	else work(rt*2,flg),work(rt*2+1,flg);
	reverse(v.begin(),v.end());
	for(LL i:v)
	{
		sz[fa[i]]-=sz[i];
	//	assert(sz[fa[i]]>=sz[i]);
		fa[i]=i;
	
	}	
//	if(rt==1)	cout<<rt<<' '<<t[rt].v<<endl;
}
int main()
{
//	freopen("point8.in","r",stdin);
//	freopen("point8.ans2","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		y+=n;
		if(Ma.count({x,y}))continue;
		E[++Ecnt]={x,y,0,-1};
		Ma[{x,y}]=Ecnt;
	}
	scanf("%lld",&q);
	for(int i=1;i<=q;i++)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		y+=n;
		if(Ma.count({x,y}))E[Ma[{x,y}]].r=i-1,Ma.erase({x,y});
		else
		{
			E[++Ecnt]={x,y,i,-1};
			Ma[{x,y}]=Ecnt;	
		}
	}
	build(1,0,q);
	for(int i=1;i<=2*n;i++)fa[i]=i;
	for(int i=1;i<=Ecnt;i++)
	{
		if(E[i].r==-1)E[i].r=q;
	//	cout<<E[i].l<<' '<<E[i].r<<endl;
		assert(E[i].l<=E[i].r);
		ins(1,i);
	}
	work(1,0);
//	assert(dkcnt==q);
}
```

---

## 作者：james1BadCreeper (赞：1)

考虑如果没有修改操作该怎么做。将行和列都抽象成点，如果一个点是黑点，那么可以将这个点所在的行和列连到同一个集合内。如果在加入一个点时，它的行和列已经在同一个集合，说明这个点就是矩形的最后一个点。

用可撤销并查集加线段树分治离线维护这个过程即可。

```cpp
#include <bits/stdc++.h>
#define pii pair<int, int> 
#define fi first
#define se second
using namespace std; 

int n, m; 
map<pii, int> mp; 
vector<pii> T[400005]; 
int fa[200005], siz[200005]; 
struct item {
	int x, y, siz; 
} st[200005];
int tot; 
int find(int x) { return fa[x] == x ? x : find(fa[x]); }
void merge(int x, int y) {
	x = find(x); y = find(y); 
	if (siz[x] > siz[y]) swap(x, y); 
	st[++tot] = {x, y, siz[x]}; 
	fa[x] = y; siz[y] += siz[x]; 
}

void update(int o, int l, int r, int x, int y, pii v) {
	if (x <= l && r <= y) return T[o].push_back(v), void(); 
	int mid = l + r >> 1; 
	if (x <= mid) update(o << 1, l, mid, x, y, v); 
	if (mid < y) update(o << 1 | 1, mid + 1, r, x, y, v); 
}
void solve(int o, int l, int r) {
	bool flag = 1; int lst = tot; 
	for (pii it : T[o]) {
		int x = find(it.fi), y = find(it.se + n); 
		if (x == y) {
			for (int i = l; i <= r; ++i) puts("Yes"); 
			flag = 0; break; 
		}
		merge(it.fi, it.se + n); 
	}
	if (flag) {
		if (l == r) puts("No"); 
		else {
			int mid = l + r >> 1; 
			solve(o << 1, l, mid); solve(o << 1 | 1, mid + 1, r); 
		}
	}
	while (tot > lst) {
		fa[st[tot].x] = st[tot].x; siz[st[tot].y] -= st[tot].siz; 
		--tot; 
	}
}

int main(void) {
	scanf("%d%d", &n, &m); 
	for (int i = 1; i <= n * 2; ++i) fa[i] = i, siz[i] = 1; 
	while (m--) {
		int x, y; scanf("%d%d", &x, &y); 
		mp[{x, y}] = 0; 
	}
	scanf("%d", &m); 
	for (int i = 1; i <= m; ++i) {
		int x, y; scanf("%d%d", &x, &y); 
		if (mp.find({x, y}) == mp.end()) mp[{x, y}] = i; 
		else {
			if (i > 1) update(1, 1, m, mp[{x, y}], i - 1, {x, y}); 
			mp.erase({x, y}); 
		}
	}
	for (auto it : mp) update(1, 1, m, it.se, m, it.fi); 
	solve(1, 1, m); 
	return 0; 
}
```

---

## 作者：Arghariza (赞：1)

和[这道题](https://codeforces.com/problemset/problem/1140/F)差不多，都是网格图转二分图的套路，这题更板一些。

我们可以把一个点 $(x,y)$ 看成二分图中一条连接左部 $L_x$，右部 $R_y$ 的边。符合条件的格点多边形可以看成一个环。

如果只有加边操作，可以直接使用并查集判环。但是现在有了删边的操作。

由于取反次数有限，每条边 $(L_{x},R_{y})$ 在时间轴上的出现是若干个区间的形式，总的区间个数不超过 $O(k)$。

这就相当于区间修改，可以使用标记永久化的思想，对于每个长度 $O(k)$ 的区间，在线段树上打 $\log k$ 个标记。

最后遍历整棵线段树，跨子树之间没有贡献，直接使用可撤销并查集即可。

这种借助线段树的分治结构，把删除变成增加撤销操作的技巧叫做线段树分治。时间复杂度 $O(k\log k\log n)$。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

#define pi pair<int, int>
#define mp make_pair
#define fi first
#define se second

const int maxn = 1e5 + 100;
int n, m, k, pr[maxn << 1], sz[maxn << 1];
map<pi, int> lst;
vector<pi> tr[maxn << 2];
stack<int> op;
pi q[maxn];

int getf(int x) { return x == pr[x] ? x : getf(pr[x]); }
void merge(int x, int y) {
	x = getf(x), y = getf(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	pr[y] = x, op.push(y), sz[x] += sz[y];
}

void del(int tp) {
	while (op.size() > tp) {
		int x = op.top(); op.pop();
		sz[pr[x]] -= sz[x], pr[x] = x;
	}
}

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)

void update(int l, int r, int s, int t, pi c, int x) {
	if (s > t) return;
	if (s <= l && r <= t) return tr[x].push_back(c);
	if (s <= mid) update(l, mid, s, t, c, ls);
	if (t > mid) update(mid + 1, r, s, t, c, rs);
}

void calc(int l, int r, int x) {
	int tp = op.size();
	int fl = 0;
	for (pi p : tr[x]) {
		if (getf(p.fi) == getf(p.se + n)) { fl = 1; break; }
		merge(p.fi, p.se + n);
	}
	if (fl) {
		for (int i = l; i <= r; i++) puts("Yes");
		return del(tp);
	}
	if (l == r) puts("No");
	else calc(l, mid, ls), calc(mid + 1, r, rs);
	del(tp);
}

int main() {
	n = read(), m = read();
	for (int i = 1; i <= (n << 1); i++) pr[i] = i;
	for (int i = 1, x, y; i <= m; i++) {
		x = read(), y = read();
		lst[mp(x, y)] = 1;
	}
	k = read();
	for (int i = 1, x, y; i <= k; i++) {
		x = read(), y = read();
		q[i] = mp(x, y);
		if (lst.count(mp(x, y))) update(1, k, lst[mp(x, y)], i - 1, mp(x, y), 1), lst.erase(mp(x, y));
		else lst[mp(x, y)] = i;
	}
	for (auto p : lst) update(1, k, p.se, k, p.fi, 1); 
	calc(1, k, 1);
	return 0;
}

```

---

