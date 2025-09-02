# Babaei and Birthday Cake

## 题目描述

Babaei 打算制作一个特殊的蛋糕。蛋糕由一些已知半径和高度的圆柱体组成，蛋糕的体积等于相应圆柱体的体积之和。

但是，还有一些额外的烹饪限制。编号为 $i$ 的蛋糕只能放在桌子上或编号为 $j$ 的蛋糕上，其中 $j\lt i$。 此外，为了给朋友们留下深刻印象，只有当蛋糕 $i$ 的体积超过蛋糕 $j$ 的体积时，Babaei 才会把蛋糕 $i$ 放在蛋糕 $j$ 上面。

Babaei 想要准备一个总体积最大的生日蛋糕，请你帮助他找到这个最大体积。

## 样例 #1

### 输入

```
2
100 30
40 10
```

### 输出

```
942477.796077000
```

## 样例 #2

### 输入

```
4
1 1
9 7
1 4
10 7
```

### 输出

```
3983.539484752
```

# 题解

## 作者：lotus_grow (赞：3)

### 题目大意
有 $n$ 个**圆柱形**蛋糕，第 $i$ 个蛋糕半径为 $r_i$，高为 $h_i$。

要求把他们按照这样的方式堆起来：
- 下面的编号比上面的小；
- 下面的体积比上面的小。

求把这些蛋糕堆起来能得到的最大体积是多少。

### 思路
一看就是最长上升子序列的题目 ٩(*Ӧ)و

设编号为 $a_i$ ,体积为 $v_i$ .

显然 $dp$ 方程为 $f_i=max${ $f_j$ }$+v_i$ , ($1<=j<i$ , $a_j<a_i$ , $v_j<v_i$)

但如果按**编号**从小到大排序后做这个就$WA$了。

因为题目求的是最大体积，按编号排序后选择并不最优。所以按体积从小到大排序后$dp$.

因为此时编号无序，体积从小到大，对于编号 $a_i$ ，$dp$ 方程为 $f_i=max${ $f_j$ }$+v_i$ , ($1<=j<i$ , $a_j<a_i$ ) 时间复杂度$O(n^2)$

那么就可以用数据结构按编号维护 $f_i$ 的区间最大值，每次转移时用 $[1,a_i)$ 的最大值进行转移，时间复杂度$O(nlogn)$

### 注意
- 排序时，若体积相等，则按编号从大到小排序（想想看为什么∩( ・ω・)∩）
- 因为查询区间是 $[1,a_i)$ ，所以可以用树状数组维护ヾ(Ő∀Ő๑)ﾉ

### 代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;
typedef long long ll;
const double pi=acos(-1.0);

ll f[100001],c[100001];
int n;
struct node
{
	ll v;int id;
	node(ll a,int b){v=a,id=b;}node(){}
	bool operator <(const node &a) const
	{
		return v<a.v || (v==a.v && id>a.id);
	}
}a[100001];

void ins(int x,ll k)
{
	for(;x<=n;x+=x&(-x)) c[x]=max(c[x],k);
}
ll query(int x)
{
	ll res=0;
	for(;x;x-=x&(-x)) res=max(res,c[x]);
	return res;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		ll r,h;scanf("%lld%lld",&r,&h);
		a[i]=node(r*r*h,i);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) 
	{
		f[i]=query(a[i].id-1)+a[i].v;
		ins(a[i].id,f[i]);
	}
	for(int i=1;i<=n;i++) f[0]=max(f[0],f[i]);
	printf("%.9lf\n",f[0]*pi);
	return 0;
}
```

---

## 作者：littlebug (赞：2)

## Solution

比较水的 dp 了。考虑暴力 dp，设 $f_i$ 为前 $i$ 个蛋糕的最大体积，那么考虑把第 $i$ 个蛋糕放在哪个蛋糕上面，则有转移：

$$
f_i = \max _{0 \le j <i \land a_i > a_j} \{ f_j \} + a_i
$$

这是 $O(n^2)$ 的，不过我们发现可以用 BIT 维护前缀最大值（以体积从小到大为关键字）优化掉这个东西，于是就变成 $O(n \log n)$ 的了。

不过……

根据样例 #2，我们可以知道直接用 double 会被卡精度。

但是我们发现，对于代码中需要用到的所有数，都是某某正整数乘上一个 $\pi$，所以考虑先用整数存，在算答案的时候再乘 $\pi$，这样就不会出现精度问题了。

## Code

```cpp
int n;
int a[MAXN],f[MAXN],pre[MAXN];
unordered_map <int,int> id;

class __BIT
{
private:
	int n;
	int v[MAXN];
public:
	il void bui(int _n) {n=_n;}
	il void upd(int pos,int k) {for(int i=pos;i<=n;v[i]=max(v[i],k),i+=(i&-i));}
	il int q(int pos) {int res=0.; for(int i=pos;i;res=max(res,v[i]),i-=(i&-i)); return res;}
	il void clear() {memset(v,0,sizeof(v));}
} tr;

signed main()
{
	read(n); {int r,h; rep(i,1,n) read(r,h),a[i]=r*r*h;}
	
	{
		vector <int> b(1,-inf);
		rep(i,1,n) b.pb(a[i]);
		sort(all(b));
		int tot=0;
		rep(i,1,n) b[i]!=b[i-1] && (id[b[i]]=++tot);
		
		tr.bui(tot);
	}
	
	rep(i,1,n)
	{
		f[i]=tr.q(id[a[i]]-1)+a[i];
		tr.upd(id[a[i]],f[i]);
	}
	
	printf("%.20Lf",mxele(f+1,f+n+1)*pi);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：qiutian120529 (赞：1)

# CodeForces 629D 题解

## 题意

给定 $n$ 个圆柱体的半径和高，请求出圆柱体体积的最大上升子序列（严格）的总体积的最大值。

## 思路

可以采取扫描线的做法。

当我们在计算圆柱体的体积时，会发现数值非常大，而且还是浮点数，这无论是对存储还是计算都是非常不便的。所以可以先进行离散化，将小数转换为整数，将大范围变成小范围。考虑动态规划，设计状态 $dp_i$ 表示选到了第 $i$ 个圆柱体的最大总体积，可得到一下转移：

$$dp_i = \max\limits_{1 \le j \lt i}^{a_j \lt a_i}(dp_j) + V_i$$

我们发现这其实是一个区间修改、单点查询的操作，所以可以用树状数组维护 dp 值。我们每次查询树状数组中的最大值，然后计算当前 dp 值并插入树状数组。因为我们是按输入顺序进行查询、计算、插入的，所以保证了出现顺序的单调性，只需查询现有值中小于当前圆柱体体积的 dp 值，这也是使用树状数组和离散化的原因——以圆柱体体积的离散值作为下标存储 dp 值。

## 代码

```  cpp
#include<bits/extc++.h>
using namespace std;
using ld = long double;

const ld pi = acos(-1);
const int N = 1e5 + 10;

ld a[N];
vector<ld> b;

int n, p[N];

struct Fenwick_Tree{
  ld c[N];
  void add(int x, ld v){
    for(; x <= n; x += x & -x){
      c[x] = max(c[x], v);
    }
  }
  ld get(int x){
    ld ans = 0;
    for(; x ; x -= x & -x){
      ans = max(ans, c[x]);
    }
    return ans;
  }
}t;

int main(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    ld r, d;
    cin >> r >> d;
    a[i] = r * r * d;
    b.push_back(a[i]);
  }
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  for(int i = 1; i <= n; i++){
    p[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
  }
  for(int i = 1; i <= n; i++){
    ld ttt = t.get(p[i] - 1);
    t.add(p[i], ttt + a[i]);
  }
  cout << fixed << setprecision(114514) << t.get(n) * pi;
  return 0;
}

```

---

## 作者：yuhong056 (赞：0)

# 题解：CF629D Babaei and Birthday Cake
## 题意
给定 $n$ 个圆柱，当第 $i$ 个圆柱可以叠在第 $j$ 个圆柱上，那么满足 $i < j$ 且第 $i$ 圆柱比第 $j$ 个圆柱的体积大。

求最终叠成的圆柱塔能有多大的体积。
## 思路
很明显，这就是一道经典的 LIS 模型，但是，如果使用原来的 dp 转移，明显会超时。

因此，我们考虑使用数据结构优化。

考虑我们一开始如何转移：
> 枚举上一个圆柱，如果他的体积小于当前圆柱的体积，那么答案就是所有这种答案加上当前圆柱的体积的最大值。

枚举上一个圆柱，可以通过按下标逐个加入。

而要求所有体积小于当前圆柱的圆柱，则可以另开一个数组，以其体积做下标。

最终，我们所求的答案就是这个数组中前缀最大值。

因此，可以发现，这就是一个树状数组的板子。
## 细节
首先，这个 $\pi$ 其实可以最后乘，不然可能出现精度问题。

其次，由于值域太大，需要离散化。
## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e5 + 15;

struct Fenwick{
  #define lb(x) ((x) & (-x))
  ll c[MAXN];
  int n;
  void init(int n) {
    for(int i = 1; i <= n; i++) {
      c[i] = 0;
    }
    this->n = n;
  }
  void add(int u, ll x = 1) {
    for(; u <= n; u += lb(u))c[u] = max(c[u], x);
  }
  ll ask(int u) {
    ll sum = 0;
    for(; u; u -= lb(u))sum = max(c[u], sum);
    return sum;
  }
}T;

struct lsh{
  vector<ll>a;
  void init(const vector<ll>&s) {
    a = s;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
  }
  int ask(ll x) {
    return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
  }
}L;

int n;
ll w[MAXN];
ll dp[MAXN];
int main(){
  vector<ll>W;
  cin >> n;
  for(int i = 1, h, r; i <= n; i++) {
    cin >> r >> h;
    w[i] =  1LL * r * r * h;
    W.push_back(w[i]);
  }
  L.init(W);
  T.init(n);
  for(int i = 1; i <= n; i++) {
    int p = L.ask(w[i]);
    dp[i] = T.ask(p - 1) + w[i];
    T.add(p, dp[i]);
  }
  cout << fixed << setprecision(12) << (*max_element(dp + 1, dp + 1 + n)) * 3.1415926535897;
  return 0;
}
```

---

## 作者：_Chronostatis_ (赞：0)

## 题意
给定 $n$ 个圆柱体的底面半径和高，对于第 $i$ 个圆柱体，可以将其放在桌上，或者堆在另一个圆柱体 $j \lt i$ 的上面，前提是第 $j$ 个圆柱体的体积比第 $i$ 个的小。求最大的圆柱体（或组合体）的体积。

## 思路
容易想到线性 dp。设计状态 $dp_{i}$ 表示考虑前 $i$ 个圆柱体时最大的体积。

那么有以下转移：

$$
dp_{i} = (\max_{j = 1}^{i - 1} dp_j \times [v_j \lt v_i]) + v_i
$$

其中，$v_i$ 表示第 $i$ 个圆柱体的体积。

考虑优化。首先发现，对于体积的计算，可以最后再乘 $\pi$，然后，考虑使用权值线段树优化 dp。

权值线段树其实也不是什么高级的数据结构，就是把值作为下标来操作的线段树。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

const int MAXN = 1e5 + 10;
const double pi = 3.1415926535897;

struct Node {
  ll mx;
};

struct SegTree {
  Node dat[MAXN << 2], E = {0};
  Node comb(const Node &dat1, const Node &dat2) {
    return {max(dat1.mx, dat2.mx)};
  }
  void modify(int root, int l, int r, int pos, ll val) {
    if (l == r) {
      dat[root] = {val};
      return;
    }
    int mid = l + r >> 1;
    pos <= mid ? modify(root << 1, l, mid, pos, val) : modify(root << 1 | 1, mid + 1, r, pos, val);
    dat[root] = comb(dat[root << 1], dat[root << 1 | 1]);
  }
  Node query(int root, int l, int r, int L, int R) {
    if (L <= l && R >= r) return dat[root];
    if (L > r || R < l) return E;
    int mid = l + r >> 1;
    return comb(query(root << 1, l, mid, L, R), query(root << 1 | 1, mid + 1, r, L, R));
  }
} T;

struct Lsh {
  vector<ll> v;
  void build(int n, ll a[]) {
    for (int i = 1; i <= n; i++) {
      v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
  }
  int rnk(ll x) {
    return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
  }
  int len() { return v.size(); }
} L;

int n;
ll vol[MAXN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (ll i = 1, r, h; i <= n; i++) {
    cin >> r >> h;
    vol[i] = r * r * h;
  }
  L.build(n, vol);
  int m = L.len();
  for (int i = 1; i <= n; i++) {
    int k = L.rnk(vol[i]);
    T.modify(1, 1, m, k, T.query(1, 1, m, 1, k - 1).mx + vol[i]);
  }
  cout << fixed << setprecision(8) << T.query(1, 1, m, 1, m).mx * pi;
  return 0;
}
```

---

## 作者：fr_dr (赞：0)

## 题目大意
给定 $n$ 个蛋糕，要求选出几个蛋糕，使得这几个蛋糕满足体积依次增大，求出满足这样条件的蛋糕序列总体积最大值。
## 思路
简化问题，其实就是求最大上升序列的和，那么考虑动态规划。设 $dp_{i}$ 表示第 $i$ 个蛋糕结尾的最大上升子序列的和，$v_i$ 表示第 $i$ 个蛋糕的体积。
$$
dp_i=\max_{j=1}^{i-1}dp_j(v_i > v_j)
$$
发现求最大值很慢，那么考虑使用线段树将蛋糕体积排序，对蛋糕从小到大的体积为索引存储当前以对应体积蛋糕结尾的最大和，构建线段树，支持求区间最大值和单点修改，这样就能迅速的求出体积比 $i$ 小的且序号在 $i$ 前的和的最大值是多少了。那么有个问题，体积太大了，所以要离散化，然后就做完了，复杂度为 $O(n\log n)$。
## 代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<iomanip>
using namespace std;
long long n,dp[100010];
struct CAke{
	long long r,h;
	long long v; 
}cake[100010];
struct segment_tree{//线段树 
	private: 
	long long data[400010];
	void _build(long long n,long long l,long long r){
		if(l==r){
			data[n]=0;
			return;
		}
		long long mid=(l+r)>>1;
		_build(n<<1,l,mid);
		_build(n<<1|1,mid+1,r);
		data[n]=max(data[n<<1],data[n<<1|1]);
	}
	void _modify(long long n,long long l,long long r,long long P,long long p){//单点修改 
		if(l==r){
			data[n]=p;
			return;
		}
		long long mid=(l+r)>>1;
		if(P<=mid)   _modify(n<<1,l,mid,P,p);
		if(P>=mid+1) _modify(n<<1|1,mid+1,r,P,p);
		data[n]=max(data[n<<1],data[n<<1|1]);
		return;
	}
	long long _seek(long long n,long long l,long long r,long long L,long long R){//区间查询 
		if(l>=L&&r<=R){
			return data[n];
		}
		long long mid=(l+r)>>1;
		long long maxn=0;
		if(L<=mid)  maxn=max(maxn,_seek(n<<1,l,mid,L,R));
		if(R>=mid+1)maxn=max(maxn,_seek(n<<1|1,mid+1,r,L,R));
		return maxn;
	} 
	public:
	void modify(long long a,long long b){
		_modify(1,1,n+1,a,b);
	}
	void build(long long a){
		_build(1,1,a);
	}
	long long seek(long long a){
		return _seek(1,1,n+1,1,a); 
	}
}tree;
struct Hash{//离散化 
	long long a[100010],t;
	Hash(){
		memset(a,0,sizeof(a));
	}
	void _main(){
		sort(a+1,a+n+1);
		t=(long long)(unique(a+1,a+n+1)-a);//去重挪位，线段树没有0编号的点（Q-Q） 
		for(int i=t;i>=1;i--){
			a[i+1]=a[i];
		}
		t++;
		return;
	}
	long long check(long long num){//查询离散化对应的值 
		long long l=2,r=t;
		long long ans=0;
		while(l<=r){
			long long mid=(l+r)>>1;
			if(a[mid]>num){
				r=mid-1;
			}
			else{
				l=mid+1;
				if(a[mid]==num){
					ans=mid;
				}
			}
		}
		return ans;
	}
}hash_;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>cake[i].r>>cake[i].h;
		cake[i].v=cake[i].r*cake[i].h*cake[i].r;
		hash_.a[i]=cake[i].v;
	}
	hash_._main();
	tree.build(n+1);
	for(int i=1;i<=n;i++){
		dp[i]=tree.seek(hash_.check(cake[i].v)-1)+cake[i].v;//对应转移这里将无理数提出来保证精度 
		tree.modify(hash_.check(cake[i].v),dp[i]); 
	}
	long double ans=tree.seek(hash_.t);  
	ans=ans*3.1415926;
	cout<<fixed<<setprecision(10)<<ans; 
}
```

---

## 作者：Priestess_SLG (赞：0)

鉴定为：【模板】最长上升子序列。

考虑到问题只和编号、体积两个状态有偏序关系，因此考虑对一个维度排序，然后对另一个维度求最长上升子序列。考虑到编号维的最值相对较小更容易处理，因此对体积从小到大排序，然后对编号维度跑 LIS 即可。直接做时间复杂度为 $O(n^2)$，考虑用 BIT 优化，时间复杂度降为 $O(n\log n)$ 可以通过。

如果 wa on test $37$ 那么检查排序时若体积相等，则是否按照编号降序排序。

代码：

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010;
const long double pi = acosl(-1);
struct Cake {
    int r, h, id;
} cake[N];
int tree[N], f[N];
void add(int x, int v) {
    for (; x < N; x += (x &- x)) tree[x] = max(tree[x], v);
}
int query(int x) {
    int s = 0;
    for (; x; x -= (x &- x)) s = max(s, tree[x]);
    return s;
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> cake[i].r >> cake[i].h, cake[i].id = i;
    sort(cake + 1, cake + n + 1, [&](auto &l, auto &r) {
        return l.r * l.r * l.h < r.r * r.r * r.h || l.r * l.r * l.h == r.r * r.r * r.h && l.id > r.id;
    });
    for (int i = 1; i <= n; ++i) {
        f[i] = query(cake[i].id - 1) + cake[i].r * cake[i].r * cake[i].h;
        add(cake[i].id, f[i]);
    }
    cout << *max_element(f + 1, f + n + 1) * pi << '\n';
    return 0;
}
```

---

## 作者：Vitamin_B (赞：0)

# 思路
不难推出暴力 dp 式子：$dp_i=(\max\limits_{j=1}^{i-1}dp_j)+s_i$，$s_i$ 表示第 $i$ 个蛋糕的体积。考虑优化，可以用树状数组快速求出 $\max\limits_{j=1}^{i-1}dp_j$，但是要离散化。因为我懒，所以我换了种方法。

以体积为第一关键字从小到大排序，然后依次枚举数组，最后还是用树状数组解决（此时树状数组的下标代表原数组下标）。
# 注意事项
必须以下标从大到小作为第二关键字，否则你会和我一样 WA#37。

原因：当你出现两个体积相同的蛋糕时，如果你下标从小到大排序了，那你就可以把前一个蛋糕放到后一个上，但事实上是不可以这么做的。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const double pi = acos (-1); //众所周知 π=acos(-1)
struct node {
	int id;
	ll s;
	bool operator < (const node& x) const {
		return s != x.s ? s < x.s : id > x.id;
	}
} a[100005];
int n, x, y;
ll maxx, s, tr[100005];
void add (int x, ll y) {
	while (x <= n)
		tr[x] = max (tr[x], y), x += x & -x;
	return ;
}
ll find (int x) {
	ll maxx = 0;
	while (x)
		maxx = max (maxx, tr[x]), x ^= x & -x;
	return maxx;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i)
		cin >> x >> y, a[i] = {i, (ll) x * x * y};
	sort (a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++ i) {
		s = find (a[i].id - 1) + a[i].s;
		maxx = max (maxx, s);
		add (a[i].id, s);
	}
	cout << fixed << setprecision (10) << pi*maxx;
	return 0;
}
```

---

## 作者：Drind (赞：0)

### 题目解析

给定 $n$ 个圆柱体，要选出其中几个，保证前一个体积大于后一个，且总体积最大。

我们可以先写出一个很简单的动态规划方程。

$$dp_i=\max_{j=1}^{i-1}dp_j[v_i\ge v_j]$$

我们发现 $dp_i$ 能够由 $dp_j$ 转移当且仅当 $i\gt j$ 且 $v_i \ge v_j$，显然是一个二维数点的问题，用树状数组维护即可，复杂度 $O(n\log n)$

记得离散化一下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

struct node{
	int r,h;
	int v;
}a[N];
int tmp[N];

int tree[N];

inline int lowbit(int x){
	return x&(-x);
}

void modify(int p,int val){
	while(p<N){
		tree[p]=max(tree[p],val);
		p+=lowbit(p); 
	}
}

int query(int p){
	int ans=0;
	while(p){
		ans=max(ans,tree[p]);
		p-=lowbit(p);
	}
	return ans;
}

int dp[N];

inline void fake_main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].r>>a[i].h; a[i].v=a[i].r*a[i].r*a[i].h;
		tmp[i]=a[i].v;
	}
	sort(tmp+1,tmp+n+1); int len=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++){
		a[i].v=lower_bound(tmp+1,tmp+len+1,a[i].v)-tmp;
	}
	
	int ans=0;
	for(int i=1;i<=n;i++){
		dp[i]=query(a[i].v-1)+tmp[a[i].v];//注意不要加成离散化后的值
		modify(a[i].v,dp[i]); ans=max(ans,dp[i]);
	}
	//计算的时候可以先不乘上这个 pi
	cout<<fixed<<setprecision(8)<<1.0*ans*acos(-1)<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF629D)

一道比较明显的二维偏序问题。

选择的蛋糕必须体积递增，树状数组需要预先离散化，可以选择使用动态开点的线段树。

可以发现，由于 $V=\pi r^2h$，所以我们的过程量使用整型变量保留精度，只需要在最后统一 $\times \pi$ 即可。

注意到体积会爆 int，所以应当使用 long long，最后再强制转化成 double 输出即可，注意题目对精度的要求较高，$\pi$ 要多取几位。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define N 100010
int n;
ll dp[N];
struct seg
{
	#define mid (l+r)/2
	ll mx[N*45];
	int L[N*45],R[N*45],times;
	seg()
	{
		times = 1;
	}
	inline void pushup(int u) 
	{
		mx[u] = max(mx[L[u]],mx[R[u]]);	
	} 
	ll query(int u,ll l,ll r,ll x,ll y)
	{
		if(!u) return 0;
		if(x <= l&&r <= y) return mx[u];
		ll ret = 0;
		if(x <= mid) ret = max(ret,query(L[u],l,mid,x,y));
		if(y > mid) ret = max(ret,query(R[u],mid+1,r,x,y));
		return ret;
	}
	int update(int u,ll l,ll r,ll x,ll y)
	{
		if(!u) u = ++times;
		if(l == r) 
		{
			mx[u] = max(mx[u],y);
			return u;	
		}
		if(x <= mid) L[u] = update(L[u],l,mid,x,y);
		else R[u] = update(R[u],mid+1,r,x,y);
		pushup(u);
		return u;	
	}
}tree;
ll ans;
int main()
{
	scanf("%d",&n);
	F(i,1,n)
	{
		ll r,h;
		scanf("%lld%lld",&r,&h);
		ll v = 1.0*r*r*h;
		dp[i] = v + tree.query(1,0,1e12,0,v-1.0);
		tree.update(1,0,1e12,v,dp[i]); 
		ans = max(ans,dp[i]);
	}
	printf("%.15lf",(double)ans * 3.14159265358979323846);
	return 0;
}
```


---

## 作者：EastPorridge (赞：0)

第一遍题解说不能直接按下标序 dp 是不完全正确的，这里提供一个用下标序 dp 的方法。 

### 题目分析：

对于题目，有对于当前位置 $i$，体积为 $a_i$，有转移方程 $f[i]= \max (f[j]) + a[i] (j < i,a_j < a_i)$，显然，直接转移是 $O(n^2)$ 的，所以要进行优化。

考虑一下树状数组优化 LIS 的原因，设当前数字为 $a[i]$，之所以可以直接在 $a[i]-1$ 里面查询前缀 $f[j]$ 的最大值 $(j < i)$，是因为树状数组的下标对应的就是 $a[i]$，天然有序的，那在这里也可以使用相同的方法了，我们将每个物品的体积离散化一下，当成下标，每次对于当前的 $i$，就二分出它的有序下标，即树状数组对应的下标，顺序转移就可以了。

### Code.

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const double pi=3.14159265357;
int n,tr[N],f[N],mx,num[N],a[N];
int lowbit(int x) {return x&-x;}
void modify(int x,int k) {for(int i=x;i<=n;i+=lowbit(i)) tr[i]=max(tr[i],k);}
int query(int x) {int res=0; for(int i=x;i;i-=lowbit(i)) res=max(res,tr[i]); return res; }
signed main()
{
	scanf("%lld",&n);
	for(int i=1,r,h;i<=n;i++) {scanf("%lld%lld",&r,&h); num[i]=a[i]=r*r*h; }
	stable_sort(num+1,num+1+n); int cnt=unique(num+1,num+1+n)-num-1;
	for(int i=1;i<=n;i++)
	{
		int tmp=lower_bound(num+1,num+1+cnt,a[i])-num;
		f[i]=query(tmp-1)+a[i]; modify(tmp,f[i]);
	}
	for(int i=1;i<=n;i++) mx=max(mx,f[i]);
	printf("%.7lf",1.0*pi*mx);
	return 0;
}
```


---

## 作者：stntn (赞：0)

## 简要题意

$n$ 个物品，每个物品有一个序号和体积 $v$。求一个体积和最大的子序列满足对于所有 $i<j$ 有 $v_i<v_j$。

**先说在前面，如果你始终 WA 却无法解决，试试算体积时先不算 $\pi$，最后答案再乘上 $\pi$。**

## DP

显然可以 DP，我们设 $f_{i}$ 表示当前以 $i$ 为最大体积结尾的子序列体积和的最大值，有转移方程：

$$
	f_{v_i}=\max_{j<v_i}  f_j+v_i
$$

但有几个问题：

1. 体积为小数，不方便作为状态。

1. 复杂度 $O(n^2)$，过不了。

对于第一个问题，我们发现最多只有 $n$ 个体积作为状态，于是可以用离散化解决。

对于第二个问题，我们发现每次转移就是从所有比它早出现，体积比它小的状态转移过来，这启发我们可以用线段树优化。

我们先对体积进行离散化，线段树维护 $f$ 数组（即按状态体积由低到高，不是编号！）。

转移的时候查询 $t=\max_{j<v_i} f_j$ ，将 $f_{v_i}$ 更新为 $t+v_i$。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 100010
#define int long long
#define ULL unsigned long long
#define DB long double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(i,u) for(int i=head[u];~i;i=e[i].nxt)
#define INF 0x3f3f3f3f3f3f3f
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
const DB pi=3.1415926535897932384626433832795;
struct LT
{
	#define mid ((l+r)>>1)
	#define lc rt<<1
	#define rc rt<<1|1
	DB f[N<<2];
	inline void build(int rt,int l,int r)
	{
		f[rt]=-INF;if(l==r) return;
		build(lc,l,mid);build(rc,mid+1,r);
	}
	inline void update(int rt,int l,int r,int pos,DB val)
	{
		if(l==r){f[rt]=max(f[rt],val);return;}
		if(pos<=mid) update(lc,l,mid,pos,val);
		else update(rc,mid+1,r,pos,val);
		f[rt]=max(f[lc],f[rc]);
	}
	inline DB query(int rt,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return f[rt];
		DB res=-INF;
		if(L<=mid) res=query(lc,l,mid,L,R);
		if(mid<R) res=max(res,query(rc,mid+1,r,L,R));
		return res;
	}
	#undef mid
	#undef lc
	#undef rc
}t;
int n,id[N];
DB a[N];
struct NODE
{
	DB val;int id;
	bool operator < (const NODE &b) const {return val!=b.val ? val<b.val : id>b.id;}
}b[N];
signed main()
{
	read(n);
	rep(i,1,n)
	{
		DB r,h;read(r,h);
		a[i]=b[i].val=r*r*h;
		b[i].id=i;
	}
	sort(b+1,b+1+n);
	rep(i,1,n) id[b[i].id]=i;
	t.build(1,1,n);t.update(1,1,n,id[1],a[1]);
	rep(i,2,n)
	{
		DB f= id[i]>1 ? t.query(1,1,n,1,id[i]-1) : -INF;
		t.update(1,1,n,id[i],max(f+a[i],a[i]));
	}
	printf("%.7Lf\n",t.query(1,1,n,1,n)*pi);
	return 0;
}
```

---

