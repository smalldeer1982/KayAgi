# [ABC287G] Balance Update Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc287/tasks/abc287_g

高橋君は $ N $ 種類のカードを $ 10^{100} $ 枚ずつ持っています。はじめ、$ i $ 種類目のカードの得点は $ a_i $ で、使用可能枚数は $ b_i $ です。

以下の形式のクエリが $ Q $ 個与えられるので、順に処理してください。

- `1 x y` : $ x $ 種類目のカードの得点を $ y $ に設定
- `2 x y` : $ x $ 種類目のカードの使用可能枚数を $ y $ に設定
- `3 x` : 次の条件を満たすように $ x $ 枚のカードを選ぶことができるならば選ばれたカードの得点の総和の最大値を、そうでなければ `-1` を出力
  - どの種類のカードもその使用可能枚数を超えて選ばれない

## 说明/提示

### 制約

- $ 1\ \leq\ N,Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ a_i\ \leq\ 10^9 $
- $ 0\ \leq\ b_i\ \leq\ 10^4 $
- $ 1 $ 種類目のクエリにおいて $ 1\ \leq\ x\ \leq\ N,\ 0\ \leq\ y\ \leq\ 10^9 $
- $ 2 $ 種類目のクエリにおいて $ 1\ \leq\ x\ \leq\ N,\ 0\ \leq\ y\ \leq\ 10^4 $
- $ 3 $ 種類目のクエリにおいて $ 1\ \leq\ x\ \leq\ 10^9 $
- $ 3 $ 種類目のクエリが $ 1 $ 個以上含まれる
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 番目の $ 3 $ 種類目のクエリでは、$ 2 $ 種類目のカードを $ 1 $ 枚、$ 3 $ 種類目のカードを $ 3 $ 枚選ぶことで得点の総和が $ 11 $ となり、これが最大です。 $ 2 $ 番目の $ 3 $ 種類目のクエリでは、$ 1 $ 種類目のカードを $ 1 $ 枚、$ 3 $ 種類目のカードを $ 3 $ 枚選ぶことで得点の総和が $ 19 $ となり、これが最大です。 $ 3 $ 番目の $ 3 $ 種類目のクエリでは、$ 4 $ 枚のカードを選ぶことができないため出力は `-1` となります。 $ 4 $ 番目の $ 3 $ 種類目のクエリでは、$ 2 $ 種類目のカードを $ 2 $ 枚選ぶことで得点の総和が $ 4 $ となり、これが最大です。

## 样例 #1

### 输入

```
3
1 1
2 2
3 3
7
3 4
1 1 10
3 4
2 1 0
2 3 0
3 4
3 2```

### 输出

```
11
19
-1
4```

# 题解

## 作者：EuphoricStar (赞：4)

线段树上二分入门题。

考虑一个贪心：每次询问按 $a_i$ 从大到小选。正确性显然。

考虑动态开点值域线段树，每个结点 $[l, r]$ 存 $\sum\limits_{a_i \in [l, r]} b_i$ 和 $\sum\limits_{a_i \in [l, r]} a_i b_i$。线段树上二分找到第一个 $\sum\limits_{i = p}^{\infty} b_i > x$ 的 $p$，那么 $a_i \in [p + 1, \infty]$ 的 $a_i$ 全选，$a_i = p$ 选的数量根据还能选多少数而定。

时间复杂度 $O((n + q) \log V)$。

[code](https://atcoder.jp/contests/abc287/submissions/41994277)

---

## 作者：Svemit (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Svemit/p/18044955)

[link](https://atcoder.jp/contests/abc287/tasks/abc287_g)

省选前写点简单题攒 rp。

显然每次选择，我们应该将所有物品从大到小排序，每次选择最大的 $x$ 个。

也就是每次要求前 $x$ 大的数的和，随手写个平衡树可以做到这一操作，但是我不会，这里选择权值线段树来存贮每个数的个数，用线段树上二分解决前 $x$ 大的数的和。

注意离散化和数组大小。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 5;

int n, q;
int a[N], b[N];
struct oper {
	int op, x, y;
} Q[N];
vector<int> nums;

struct SegT {
	int l, r, siz;
	ll sum;
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define siz(x) tr[x].siz
	#define sum(x) tr[x].sum 
} tr[N << 2];

void build(int l, int r, int x) {
	tr[x] = {l, r};
	if (l == r) {
		return;
	}
	int mid = (l + r) / 2;
	build(l, mid, x * 2), build(mid + 1, r, x * 2 + 1);
}

void pushup(int x) {
	siz(x) = siz(x * 2) + siz(x * 2 + 1);
	sum(x) = sum(x * 2) + sum(x * 2 + 1);
}

void update(int x, int p, int v) {
	if (l(x) == r(x)) {
		siz(x) += v;
		sum(x) += 1ll * nums[p - 1] * v;
		return;
	}
	int mid = (l(x) + r(x)) / 2;
	if (p <= mid) update(x * 2, p, v);
	else update(x * 2 + 1, p, v);
	pushup(x);
}

ll query(int x, int k) {
	if (!k) return 0;
	if (l(x) == r(x)) {
		return 1ll * k * nums[l(x) - 1];
	}
	int mid = (l(x) + r(x)) / 2;
	if (siz(x * 2 + 1) >= k) return query(x * 2 + 1, k);
	else return sum(x * 2 + 1) + query(x * 2, k - siz(x * 2 + 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i ++) {
    	cin >> a[i] >> b[i];
    	nums.push_back(a[i]);
    }
    cin >> q;
    for (int i = 1; i <= q; i ++) {
    	int op, x, y = 0;
    	cin >> op >> x;
    	if (op == 1) {
    		cin >> y;
    		nums.push_back(y);
    	}
    	else if (op == 2) {
    		cin >> y;
    	}
    	Q[i] = (oper){op, x, y};
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    build(1, (int)nums.size(), 1);

    for (int i = 1; i <= n; i ++) {
    	a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;
    	update(1, a[i], b[i]);
    }
    for (int i = 1; i <= q; i ++) {
    	int op = Q[i].op, x = Q[i].x, y = Q[i].y;
    	if (op == 1) {
    		y = lower_bound(nums.begin(), nums.end(), y) - nums.begin() + 1;
    		update(1, a[x], -b[x]);
    		a[x] = y;
    		update(1, a[x], b[x]);
    	}
    	else if (op == 2) {
    		update(1, a[x], y - b[x]);
    		b[x] = y;
    	}
    	else {
    		if (siz(1) < x) {
    			cout << -1 << '\n';
    		}
    		else {
    			cout << query(1, x) << '\n';
    		}
    	}
    }
    return 0;
}
```

---

## 作者：xzy090626 (赞：1)

来点高复杂度低常数做法。

可以将所有的价值（包括 $A_i$ 和询问中的修改）离散化一下，这一步是 $(n+q)\log (n+q)$ 的。同时要记录离散化后的值所对应的原值。

接着我们考虑如何动态维护。看到单点修改想到树状数组（其实平衡树也可以嘿嘿），我们可以在树状数组上以离散化后的价值为下标、以数量为存储的值来维护。对于前两种操作，我们只需要 $O(\log (n+q))$ 维护一下就行了。

对于第三种操作，考虑树状数组上二分。从后往前走，看什么时候从最大值到当前二分值的区间内的数量 $\ge x$。然后再减掉多余的部分。这一步是 $O(\log^2 (n+q))$ 的。

注意到一个小问题，就是给定的 $A_i$ 有可能为 $0$，树状数组按照正常的存法会出错。我们可以考虑将每个价值都加一，最后输出的时候将答案减去 $x$，就没有问题了。

时间复杂度：$O((n+q)\log^2(n+q))$。常数很小，只跑了 160 毫秒，不比平衡树和线段树慢。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
using namespace std;
const int N = 5e5 + 7;
int n,q;
pii s[N];
int c[N];
int lowbit(int x){return x&(-x);}
void add(int x,int y){
	for(;x<N;x+=lowbit(x)) c[x] += y;
}
int ask(int x){
	int res = 0;
	for(;x;x-=lowbit(x)) res += c[x];
	return res;
}
int qry(int l,int r){
	return ask(r) - ask(l-1);
}
int ft[N];
struct query{
	int op;
	int x,y;
}Q[N];
vector<int>vec;
int cc[N];
void add1(int x,int y){
	for(;x<N;x+=lowbit(x)) cc[x] += y;
}
int ask1(int x){
	int res = 0;
	for(;x;x-=lowbit(x)) res += cc[x];
	return res;
}
int qry1(int l,int r){
	return ask1(r) - ask1(l-1);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>s[i].x>>s[i].y;
		s[i].x++;
		vec.push_back(s[i].x);
	}
	cin>>q;
	for(int i=1;i<=q;++i){
		cin>>Q[i].op>>Q[i].x;
		if(Q[i].op!=3) cin>>Q[i].y;
		if(Q[i].op==1) Q[i].y++,vec.push_back(Q[i].y);
	}
	sort(vec.begin(),vec.end());
	auto rr = unique(vec.begin(),vec.end());
	for(int i=1;i<=n;++i){
		int tmp = lower_bound(vec.begin(),rr,s[i].x) - vec.begin() + 1;
		ft[tmp] = s[i].x;
		s[i].x = tmp;
		add(s[i].x,s[i].y);
		add1(s[i].x,ft[s[i].x]*s[i].y);
	}
	for(int i=1;i<=q;++i){
		if(Q[i].op==1){
			int tmp = lower_bound(vec.begin(),rr,Q[i].y) - vec.begin() + 1;
			ft[tmp] = Q[i].y;
			Q[i].y = tmp;
		}
	}
	for(int i=1;i<=q;++i){
		int x;
		if(Q[i].op==1){
			x = s[Q[i].x].x;
			int tt = s[Q[i].x].y;//num of Q[i].x
			add(x,-tt);add(Q[i].y,tt);
			add1(x,-tt*ft[x]);
			add1(Q[i].y,ft[Q[i].y]*tt);
			s[Q[i].x].x = Q[i].y;
		}
		else if(Q[i].op==2){
			x = s[Q[i].x].x;
			int tt = s[Q[i].x].y;
			add(x,Q[i].y-tt);
			add1(x,ft[x]*(Q[i].y-tt));
			s[Q[i].x].y = Q[i].y;
		}
		else{
			x = Q[i].x;
			//cerr<<qry(1,N-5)<<'\n';
			int l = 1,r = N - 5,cur = -1;
			while(l<=r){
				int mid = (l+r)/2;
				if(qry(mid,N-5)>=x) cur = mid,l = mid + 1;
				else r = mid - 1;
			}
			if(cur==-1) cout<<-1<<'\n';
			else{
				int ans = qry1(cur,N-5);
				int tmp = qry(cur,N-5);
				ans -= (tmp-x) * ft[cur];
				cout<<ans-x<<'\n';
			}
		}
	}
	return 0;
}
```
代码不太好看。

---

## 作者：yqr123YQR (赞：1)

### 题意
维护一个序列，从大到小排序，支持每次删除任意个相同的数及查询前 $k$ 个的和。

### 思路
一眼平衡树。~~为什么会有人写分块或线段树上二分？~~

### 实现
**显然**采用 `FHQ-Treap` 实现。~~赛时用美丽的 `Splay` 你会喜获 $18$ 个 `TLE`……~~

关于“按排名分裂”，需要对模板稍加调整，细节见代码。

### 代码
```cpp
#include<stdio.h>
#include<random>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 200000, bufsize = 220005;
char gtchar()
{
	static char buf[bufsize], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsize, stdin)) == buf? EOF: *p1++;
}
int read()
{
	int ret = 0;
	char ch = gtchar();
	while(ch < '0' || ch > '9') ch = gtchar();
	while(ch >= '0' && ch <= '9') ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
	return ret;
}
mt19937 rnd(rand());
struct fhq_treap
{
	struct node
	{
		int l, r, cnt, size, pri;
		ll sum, value;
	}tr[maxn + 1 << 1];
	int root, size;
	#define l(k) tr[k].l
	#define r(k) tr[k].r
	#define c(k) tr[k].cnt
	#define s(k) tr[k].size
	#define p(k) tr[k].pri
	#define sum(k) tr[k].sum
	#define v(k) tr[k].value
	void pushup(int k)
	{
		sum(k) = sum(l(k)) + sum(r(k)) + v(k) * c(k);
		s(k) = s(l(k)) + s(r(k)) + c(k);
	}
	void split_value(int k, int value, int &l, int &r)
	{
		if(!k) return l = r = 0, void();
		if(v(k) <= value) l = k, split_value(r(k), value, r(k), r);
		else r = k, split_value(l(k), value, l, l(k));
		pushup(k);
	}
	void split_rank(int k, int rank, int &l, int &r)//这里我们指定 l 的子树大小刚好大于等于 rank。
	{
		if(!k) return l = r = 0, void();
		if(rank <= 0) return l = 0, r = k, void();//因为 rank < 0 只可能在 k 为右儿子时成立，此时相当于分裂出的左子树大小已经大于 rank 了，不用再补充，当前子树要全部归到右子树。
		if(rank <= s(l(k))) r = k, split_rank(l(k), rank, l, l(k));
		else l = k, split_rank(r(k), rank - s(l(k)) - c(k), r(k), r);
		pushup(k);
	}
	int merge(int a, int b)
	{
		if(!a || !b) return a + b;
		int ret;
		if(p(a) <= p(b)) ret = a, r(a) = merge(r(a), b);
		else ret = b, l(b) = merge(a, l(b));
		pushup(ret);
		return ret;
	}
	void insert(int value, int cnt)
	{
		if(!cnt) return;
		int l, r, mid;
		split_value(root, value, l, r), split_value(l, value - 1, l, mid);
		if(mid) c(mid) += cnt;
		else mid = ++size, c(mid) = cnt, v(mid) = value, p(mid) = rnd();
		pushup(mid);
		root = merge(merge(l, mid), r);
	}
	void del(int value, int cnt)
	{
		if(!cnt) return;
		int l, r, mid;
		split_value(root, value, l, r), split_value(l, value - 1, l, mid);
		if(c(mid) > cnt) c(mid) -= cnt, pushup(mid);
		else mid = 0;
		root = merge(merge(l, mid), r);
	}
	int qmax(int k)
	{
		while(r(k)) k = r(k);
		return v(k);
	}
	ll query(int rank)
	{
		if(rank > s(root)) return 1;
		int l, r;
		split_rank(root, rank, l, r);
		ll ret = sum(l) - (ll) (s(l) - rank) * qmax(l);//此处因为已经取负了，所以要剔除的应该是最大的（对应原本最小的）。
		root = merge(l, r);
		return ret;
	}
	#undef l
	#undef r
	#undef c
	#undef s
	#undef p
	#undef sum
	#undef v
}treap;
int n, q, a[maxn + 5], b[maxn + 5];
int main()
{
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read(), b[i] = read(), treap.insert(-a[i], b[i]);//因为 FHQ-Treap 原本的中序遍历是从小到大，所以要取负。
	q = read();
	for(int i = 1, op, x, y; i <= q; i++)
	{
		op = read(), x = read();
		if(op != 3) y = read();
		if(op == 1) treap.del(-a[x], b[x]), treap.insert(-(a[x] = y), b[x]);
		else if(op == 2) treap.del(-a[x], b[x]), treap.insert(-a[x], b[x] = y);
		else printf("%lld\n", -treap.query(x));
	}
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

~~考场少写一个加号痛失 AC。~~

首先不难想到值域分块：将询问和 $a$ 数组离线下来进行离散化，然后进行分块，对于每一块维护 $sum$ 表示这一块的和，$cnt$ 表示这个块的数字个数。对于 $1$ 操作和 $2$ 操作，单点修改即可。对于 $3$ 操作，倒着遍历每一个即可。

注意值有可能相同，时间复杂度为 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=4e5+10,M=N<<1;  
int n,m; 
pii a[N]; 
int L[M],R[M]; 
int b[M],num=0; 
int id[M],len=0;
int tot[M],val[M]; 
int cnt[M],sum[M]; 
struct Master{ 
	int opt,x,y; 
}q[N]; 
void modify(int x,int k,int w){ 
	cnt[id[k]]+=w; 
	sum[id[k]]+=val[a[x].x]*w; 
	a[x].y+=w; tot[a[x].x]+=w; 
} 
void modify_w(int x,int k,int w){ 
	int id1=id[k],id2=id[w]; 
	sum[id1]-=val[k]*a[x].y,cnt[id1]-=a[x].y; 
	sum[id2]+=val[w]*a[x].y,cnt[id2]+=a[x].y; 
//	cout<<id1<<" "<<id2<<endl; 
	tot[k]-=a[x].y; a[x].x=w; tot[w]+=a[x].y; 
} 
int query(int x){ 
	int ans=0; 
	for(int i=id[num];i>=1;i--){ 
		if(x>=cnt[i]) x-=cnt[i],ans+=sum[i]; 
		else{ 
			int l=L[i],r=R[i]; 
			for(int j=r;j>=l;j--){ 
//				cout<<val[j]<<" "<<tot[j]<<endl; 
				if(x>=tot[j]) x-=tot[j],ans+=val[j]*tot[j]; 
				else{ ans+=x*val[j],x=0; break; } 
			} break; 
		} 
	} if(x>0) ans=-1; return ans; 
} 
signed main(){ 
	scanf("%lld",&n); memset(L,0x3f,sizeof L); 
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y),b[++num]=a[i].x; 
	scanf("%lld",&m); for(int i=1;i<=m;i++){ 
		scanf("%lld%lld",&q[i].opt,&q[i].x); 
		if(q[i].opt!=3) scanf("%lld",&q[i].y); 
		if(q[i].opt==1) b[++num]=q[i].y; 
	} sort(b+1,b+num+1); num=unique(b+1,b+num+1)-b-1; len=sqrt(num); 
	for(int i=1;i<=num;i++) id[i]=(i-1)/len+1,L[id[i]]=min(L[id[i]],i),R[id[i]]=max(R[id[i]],i); 
	for(int i=1,x;i<=m;i++) if(q[i].opt==1) x=q[i].y,q[i].y=lower_bound(b+1,b+num+1,q[i].y)-b,val[q[i].y]=x; 
	for(int i=1,x;i<=n;i++){ 
		x=a[i].x; 
		a[i].x=lower_bound(b+1,b+num+1,a[i].x)-b; 
		tot[a[i].x]+=a[i].y,val[a[i].x]=x; 
		cnt[id[a[i].x]]+=a[i].y; 
		sum[id[a[i].x]]+=val[a[i].x]*a[i].y; 
	} for(int i=1;i<=m;i++){ 
		if(q[i].opt==1) modify_w(q[i].x,a[q[i].x].x,q[i].y); 
		else if(q[i].opt==2) modify(q[i].x,a[q[i].x].x,q[i].y-a[q[i].x].y); 
		else printf("%lld\n",query(q[i].x)); 
	} return 0; 
} /*
5
1 2
1 3 
1 4 
1 5 
1 6 
2
1 1 0
3 6
*/
```



---

## 作者：CQ_Bob (赞：0)

## 分析

一眼分块。

用值域分块来维护。先把所有的值离散化，使得至于不大于 $n+q$。统计一下每个值的数量，每个块包含值的数量，每个块的价值和。修改值的时候先把原来值的数量，块包含的数量，块的价值剪掉被修改值的贡献，然后在新的值上面更新。修改数量直接改数量的变化贡献即可。

找前 $x$ 大的值之和从值域上限开始枚举，照常暴力散区间、整块。

复杂度 $O(q \sqrt{V})$。

注：离散化之后注意贡献是离散化之前的值，要还原。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=2e5+10;
int n,q;
int a[N],b[N];
struct node{
	int op,x,y;
}Q[N];
int cnt[N<<1],sum[N],val[N],len;
int y[N<<1],c[N<<1],idx;

il int get(int x){return (x-1)/len+1;}
il int query(int x){
	int bl=get(1),br=get(idx);
	int ans=0;
	if(bl==br){
		for(re int i=idx;i>=1;--i){
			if(x<=cnt[i]){ans+=x*y[i];return ans;}
			else{ans+=cnt[i]*y[i],x-=cnt[i];}
		}
		if(x==0) return ans;
		return -1;
	}
	for(re int i=idx;i>=(br-1)*len+1;--i){
		if(x<=cnt[i]){ans+=x*y[i];return ans;}
		else{ans+=cnt[i]*y[i],x-=cnt[i];}
	}
	for(re int bk=br-1;bk>=bl+1;--bk){
		if(x<=sum[bk]){
			for(re int i=bk*len;i>=(bk-1)*len+1;--i){
				if(x<=cnt[i]){ans+=x*y[i];return ans;}
				else{ans+=cnt[i]*y[i],x-=cnt[i];}
			}
			return -1;
		}
		else{ans+=val[bk],x-=sum[bk];}
	}
	for(re int i=bl*len;i>=1;--i){
		if(x<=cnt[i]){ans+=x*y[i];return ans;}
		else{ans+=cnt[i]*y[i],x-=cnt[i];}
	}
	if(x==0) return ans;
	return -1;
}
il void read(){
	cin>>n;
	for(re int i=1;i<=n;++i) cin>>a[i]>>b[i],c[++idx]=a[i];
	cin>>q;
	for(re int i=1;i<=q;++i){
		cin>>Q[i].op;
		if(Q[i].op==3) cin>>Q[i].x;
		else cin>>Q[i].x>>Q[i].y;
		if(Q[i].op==1) c[++idx]=Q[i].y;
	}
	sort(c+1,c+idx+1),idx=unique(c+1,c+idx+1)-(c+1);
	for(re int i=1,x;i<=n;++i) x=a[i],a[i]=lower_bound(c+1,c+idx+1,a[i])-c,y[a[i]]=x;
	for(re int i=1;i<=q;++i){
		if(Q[i].op==1){
			int x=Q[i].y;
			Q[i].y=lower_bound(c+1,c+idx+1,Q[i].y)-c;
			y[Q[i].y]=x;
		}
	}
	return ;
}
il void solve(){
	len=sqrt(idx);
	for(re int i=1;i<=n;++i){
		cnt[a[i]]+=b[i];
		sum[get(a[i])]+=b[i];
		val[get(a[i])]+=b[i]*y[a[i]];
	}
	for(re int i=1;i<=q;++i){
		if(Q[i].op==1){
			cnt[a[Q[i].x]]-=b[Q[i].x];
			sum[get(a[Q[i].x])]-=b[Q[i].x];
			val[get(a[Q[i].x])]-=b[Q[i].x]*y[a[Q[i].x]];
			
			a[Q[i].x]=Q[i].y;
			
			cnt[a[Q[i].x]]+=b[Q[i].x];
			sum[get(a[Q[i].x])]+=b[Q[i].x];
			val[get(a[Q[i].x])]+=b[Q[i].x]*y[a[Q[i].x]];			
		}
		else if(Q[i].op==2){
			cnt[a[Q[i].x]]+=(Q[i].y-b[Q[i].x]);
			sum[get(a[Q[i].x])]+=(Q[i].y-b[Q[i].x]);
			val[get(a[Q[i].x])]+=(Q[i].y-b[Q[i].x])*y[a[Q[i].x]];
			
			b[Q[i].x]=Q[i].y;
		}
		else if(Q[i].op==3){
			cout<<query(Q[i].x)<<"\n";
		}
	}
	return ;
}

signed main(){
	read(),solve();
	return 0;
}
```


---

