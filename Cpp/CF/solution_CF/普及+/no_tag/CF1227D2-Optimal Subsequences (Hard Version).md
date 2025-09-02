# Optimal Subsequences (Hard Version)

## 题目描述

This is the harder version of the problem. In this version, $ 1 \le n, m \le 2\cdot10^5 $ . You can hack this problem if you locked it. But you can hack the previous problem only if you locked both problems.

You are given a sequence of integers $ a=[a_1,a_2,\dots,a_n] $ of length $ n $ . Its subsequence is obtained by removing zero or more elements from the sequence $ a $ (they do not necessarily go consecutively). For example, for the sequence $ a=[11,20,11,33,11,20,11] $ :

- $ [11,20,11,33,11,20,11] $ , $ [11,20,11,33,11,20] $ , $ [11,11,11,11] $ , $ [20] $ , $ [33,20] $ are subsequences (these are just some of the long list);
- $ [40] $ , $ [33,33] $ , $ [33,20,20] $ , $ [20,20,11,11] $ are not subsequences.

Suppose that an additional non-negative integer $ k $ ( $ 1 \le k \le n $ ) is given, then the subsequence is called optimal if:

- it has a length of $ k $ and the sum of its elements is the maximum possible among all subsequences of length $ k $ ;
- and among all subsequences of length $ k $ that satisfy the previous item, it is lexicographically minimal.

Recall that the sequence $ b=[b_1, b_2, \dots, b_k] $ is lexicographically smaller than the sequence $ c=[c_1, c_2, \dots, c_k] $ if the first element (from the left) in which they differ less in the sequence $ b $ than in $ c $ . Formally: there exists $ t $ ( $ 1 \le t \le k $ ) such that $ b_1=c_1 $ , $ b_2=c_2 $ , ..., $ b_{t-1}=c_{t-1} $ and at the same time $ b_t<c_t $ . For example:

- $ [10, 20, 20] $ lexicographically less than $ [10, 21, 1] $ ,
- $ [7, 99, 99] $ is lexicographically less than $ [10, 21, 1] $ ,
- $ [10, 21, 0] $ is lexicographically less than $ [10, 21, 1] $ .

You are given a sequence of $ a=[a_1,a_2,\dots,a_n] $ and $ m $ requests, each consisting of two numbers $ k_j $ and $ pos_j $ ( $ 1 \le k \le n $ , $ 1 \le pos_j \le k_j $ ). For each query, print the value that is in the index $ pos_j $ of the optimal subsequence of the given sequence $ a $ for $ k=k_j $ .

For example, if $ n=4 $ , $ a=[10,20,30,20] $ , $ k_j=2 $ , then the optimal subsequence is $ [20,30] $ — it is the minimum lexicographically among all subsequences of length $ 2 $ with the maximum total sum of items. Thus, the answer to the request $ k_j=2 $ , $ pos_j=1 $ is the number $ 20 $ , and the answer to the request $ k_j=2 $ , $ pos_j=2 $ is the number $ 30 $ .

## 说明/提示

In the first example, for $ a=[10,20,10] $ the optimal subsequences are:

- for $ k=1 $ : $ [20] $ ,
- for $ k=2 $ : $ [10,20] $ ,
- for $ k=3 $ : $ [10,20,10] $ .

## 样例 #1

### 输入

```
3
10 20 10
6
1 1
2 1
2 2
3 1
3 2
3 3
```

### 输出

```
20
10
20
10
20
10
```

## 样例 #2

### 输入

```
7
1 2 1 3 1 2 1
9
2 1
2 2
3 1
3 2
3 3
1 1
7 1
7 7
7 4
```

### 输出

```
2
3
2
3
2
3
1
1
3
```

# 题解

## 作者：HoshizoraZ (赞：4)

三个月前，我曾写过 [**1227D1 的题解**](https://www.luogu.com.cn/problem/solution/CF1227D1)。

当时写完暴力方法后对着 D2 看了半天，想不出什么好的做法，这题也就一直鸽着没写。今天偶然看到，想到了一个方法，就在这里分享一下吧。

---------
### 将问题简单化

假设一开始令一序列 $b$ 与序列 $a$ 完全相同，且之后将序列 $b$ 从大到小排序。

当查询子序列长度为 $k$ 时，序列 $a$ 中**大于** $b_k$ 的数一定会被选中，**等于** $b_k$ 的数**排得越前**，越优先被选入子序列。

这里就不细说了，如果不理解的可以去看 D1 题解。

----------
### 算法的分析

- **对于每个 $i,j$，快速定位序列 $a$ 中第 $i$ 个等于 $a_j$ 的数的位置**

这个不难，因为 $a_i \le 10^9$ 而数字只有 $2 \times 10^5$ 个，所以可以再创建一个序列 $c$ 作为序列 $a$ 的**离散化**数组。

开 $n$ 个 `vector`（命名为 `v`），第 $i$ 个 `vector` 记录**离散化后的值**等于 $i$ 的数，在序列 $a$ 的下标。

**对于同一个 `vector`，里面的元素应满足单调递增。**

查询序列 $a$ 中第 $i$ 个等于 $a_j$ 的数的位置，只要找 `v[c[j]][i - 1]` 就行了。

- **关于询问的顺序**

如果对每个询问独立进行回答，这个问题会变得困难。

不难看出，询问的 $k_i$ 长度如果递增，一共只需要插入 $n$ 次数字，避免了巨量的增删。

因此，我们可以**离线**解决这个问题，将操作以 $k$ 从小到大排序。

- **将长度为 $s$ 的序列扩展到 $s+1$ 的解决办法**

如果 `b[s]` 与 `b[s + 1]` 相等，那么要在子序列中插入一个**之前没被插入过，且在序列 $a$ 中最靠前**且等于 `b[s]` 的数。

否则，只需要插入序列 $a$ 中**第一个**等于 `b[s + 1]` 的数的**位置**。

这步的实现见上文「快速定位」的步骤。

- **将一个数插入序列的某个位置，同时能询问当前序列中第 $pos$ 个数的值**

由于我很菜，没往平衡树和块状链表等算法思考，就在这里提供一个较好理解的做法吧。

首先这题特殊的地方在于，我们知道所有即将插入的数值，以及它在最终序列的**下标**。

那换个表示方法，每插入一个数字，就在序列 $a$ 中该数字**对应的位置**上打一个标记。

如果我们不想让这些没标记的位置添麻烦，我们可以将序列 $a$ 记录**标记**的前缀和。

最后，如果询问到序列第 $pos$ 个位置的话，我们就找**第一个前缀和等于 $pos$ 的位置**就可以了。这可以**二分**解决。

至于前缀和的维护，我们可以操作一个树状数组实现。

---------------

总复杂度：$O(m \log^2 n)$，瓶颈在于**二分 + 树状数组**。

代码：
```cpp
#include <algorithm>
#include <cstdio>
#include <vector>
#define INF 1e9
#define eps 1e-6
#define N 200010
typedef long long ll;
using namespace std;

struct query{
	int k, pos, id;
}q[N];
struct S{
	int id, v;
}s[N];
int n, m, a[N], b[N], cnt;
int ss[N], ans[N], t[N];
vector <int> v[N];

bool cmp(S x, S y){
	if(x.v != y.v) return x.v > y.v;
	return x.id < y.id;
}

bool cmpp(query x, query y){
	if(x.k != y.k) return x.k < y.k;
	return x.pos > y.pos;
}

// 树状数组模板

inline int lowbit(int x){
	return x & (-x);
}

void modify(int x){
	while(x <= n)
		t[x]++, x += lowbit(x);
}

int sum(int x){
	int ss = 0;
	while(x >= 1)
		ss += t[x], x -= lowbit(x);
	return ss;
}

int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), b[i] = a[i];
	scanf("%d", &m);
	// 离散化
	sort(b + 1, b + n + 1);
	cnt = unique(b + 1, b + n + 1) - b - 1;
	for(int i = 1; i <= n; i++){
		a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
		s[i].id = i, s[i].v = a[i];
		v[a[i]].push_back(i);
	}
	// 排序操作
	sort(s + 1, s + n + 1, cmp);
	for(int i = 1, k, pos; i <= m; i++)
		scanf("%d%d", &q[i].k, &q[i].pos), q[i].id = i;
	sort(q + 1, q + m + 1, cmpp);	// 离线解决
	int nowk = 0;
	for(int i = 1, L, R; i <= m; i++){
		while(nowk < q[i].k)	// 树状数组维护
			nowk++, modify(v[s[nowk].v][ss[s[nowk].v]]), ss[s[nowk].v]++;
		L = 1, R = n;
		while(L < R){		// 二分找答案
			int mid = (L + R) >> 1;
			if(sum(mid) < q[i].pos) L = mid + 1;
			else R = mid;
		}
		ans[q[i].id] = b[a[L]];
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);

	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：2)

贪心部分可以见 [D1 题解](https://www.luogu.com.cn/blog/359113/cf1227d1-xie-ti-bao-gao)。

考虑如何快速实现这件事：离线，求一个序列 $b$ 的长为 $k$ 的前缀的第 $pos$ 小。

~~一种做法是主席树，但是不够优美。~~

可以先将询问按 $k$ 递增排序，这样我们只需考虑加数。

考虑：$f_i$ 为 $i$ 是否在所求序列内，那 $g_i=\sum\limits_{j=1}^if_j$ 即为在当前序列中，$i$ 的排名。

上二分即可。

由于 $f_i$ 要支持单点加，所以我们想到用 BITS 维护 $f$，直接在树状数组上二分。

复杂度 $\mathcal{O(n\log n)}$。

```cpp
const int N=2e5+3;
int n,m,ans[N],b[N];
struct wt{int x,y,z;}a[N],q[N];
struct BITS
{
	int c[N];
	#define lb x&-x
	il void Modify(re int x)
	{
		for(;x<=n;x+=lb) ++c[x];
		return;
	}
}f;
void Solve()
{
	rd(n);
	for(re int i=1;i<=n;++i) rd(b[i]),a[i]={b[i],i};
	std::sort(a+1,a+n+1,[](re wt x,re wt y){return x.x==y.x?x.y<y.y:x.x>y.x;});
	rd(m);
	for(re int i=1;i<=m;++i) rd(q[i].x),rd(q[i].y),q[i].z=i;
	std::sort(q+1,q+m+1,[](re wt x,re wt y){return x.x<y.x;});
	for(re int i=1,j=0;i<=m;++i)
	{
		for(;j<q[i].x;f.Modify(a[++j].y));
		re int p=0,s=0;
		for(re int j=19,v;~j;--j)
			v=p|1<<j,v<=n&&s+f.c[v]<q[i].y&&(p=v,s+=f.c[v]);
		ans[q[i].z]=b[p+1];
	}
	for(re int i=1;i<=m;++i) prt(ans[i],'\n');
	return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1227/submission/205776136)。

---

## 作者：bmatrix (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1227D2)

如果我们将 $a$ 数组从大到小排序，那么显然的，前 $k$ 个数就对应着长度为 $k$ 的元素和最大的子序列中各元素的值。

由于要求字典序最小，所以我们将 $a$ 数组中的元素下标进行排序，在排序时以对应的元素值为第一关键字，以元素下标为第二关键字（排序后对应的元素值从大到小，大小相等的元素，下标更小的在前）。我们称排序后得到的数组为 $b$。

那么这时我们就可以发现，$b$ 数组里前 $k$ 个元素对应的就是 $a$ 数组中，长度为 $k$ 的 optimal subsequence 中的各元素下标。

因此，$b$ 数组前 $k$ 个中第 $p$ 小的元素对应的那个元素，就是长度为 $k$ 的 optimal subsequence 中第 $p$ 个元素。

那么这时问题就转化成了“找到 $b$ 数组前 $k$ 个元素中第 $p$ 小的那个”。

这时就可以用主席树解决了，但是我不想码主席树，所以我把询问存下来，按 $k$ 排序，离线回答。

具体的回答方法是，开一棵 `pbds` 的平衡树，遍历询问，如果 $k$ 变大了，就向平衡树中添加 $b$ 中元素直至平衡树大小为 $k$，然后树中第 $p$ 小的元素即是答案元素的下标。

时间复杂度 $O(n\log n)$。

代码：
```cpp
#include<bits/extc++.h>
#define endl '\n'
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
constexpr int N = 2e5 + 5;
int n, m, a[N], b[N], ans[N];
struct query {
    int k, p, id;
    bool operator<(const query& b) const {
        return k < b.k;
    }
}q[N];
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tr; 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    iota(b + 1, b + n + 1, 1);
    sort(b + 1, b + n + 1, [](int i, int j) 
    { return a[i] == a[j] ? i < j : a[i] > a[j]; });
    cin >> m;
    for(int i = 1; i <= m; ++i) cin >> q[i].k >> q[i].p, q[i].id = i;
    sort(q + 1, q + m + 1);
    for(int i = 1, j = 0; i <= m; ++i) {
        while(j < q[i].k) tr.insert(b[++j]);
        ans[q[i].id] = a[*tr.find_by_order(q[i].p - 1)];
    }
    for(int i = 1; i <= m; ++i) cout << ans[i] << endl;
    return 0;
}
```

---

## 作者：lgx57 (赞：0)

非常简单的贪心题。

显然这个子序列肯定是这样的：

1. 先选大的数，再选小的数

2. 每一次会尽量把当前那个数选完

于是我们可以把 $a_i$ 离散化，并把 $a_i$ 出现的位置放在 vector 中。

然后把询问离线下来，按照 $k$ 的大小从小到大排序，方便我们一个一个加数来计算答案。令 $f_i$ 表示 $a_i$ 是否被选到了子序列中。

接下来就是求 $pos$ 位的值，我们考虑二分。记 $sum_i=\displaystyle\sum_{j=1}^i f_j$，我们在二分的时候只需要判断 $sum_{mid}$ 与 $pos$ 的大小关系即可。

至于如何维护，一个支持单点修改的线段树就行了。

时间复杂度：$O(n \log^2 n)$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pii pair<int,int>
#define endl '\n'
#define pb push_back
#define ls(p) ((p)<<1)
#define rs(p) ((p)<<1|1)
#define lowbit(x) ((x)&(-(x)))
#define abs(x) ((x)>0?(x):(-(x)))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define gc getchar
#define pc putchar
#define sz(v) ((int)(v.size()))
using namespace std;
mt19937_64 Rand(chrono::steady_clock::now().time_since_epoch().count());
inline int read(){
	int x=0,f=1;
	char ch=gc();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=gc();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=gc();}
	return x*f;
}
inline void print(int x){
	if (x<0) pc('-'),x*=-1;
	if (x<10) pc(x+'0');
    else print(x/10),pc(x%10+'0');
}
const int N=2e5+5;
int a[N],num[N];
vector<int> v[N];
int sum[N];
struct node{
	int k,pos;
	int id,ans;
}qq[N];
bool cmp(node xx,node yy){
	return xx.k<yy.k;
}
int t[N<<2];
void push_up(int p){
	t[p]=t[ls(p)]+t[rs(p)];
}
void update(int l,int p,int pl,int pr){
	if (pl==pr){
		t[p]=1;
		return ;
	}
	int mid=(pl+pr)>>1;
	if (l<=mid) update(l,ls(p),pl,mid);
	else update(l,rs(p),mid+1,pr);
	push_up(p);
}
int query(int l,int r,int p,int pl,int pr){
	if (l<=pl&&pr<=r) return t[p];
	int mid=(pl+pr)>>1;
	int ans=0;
	if (l<=mid) ans+=query(l,r,ls(p),pl,mid);
	if (r>mid) ans+=query(l,r,rs(p),mid+1,pr);
	return ans;
}
bool cmp2(node xx,node yy){
	return xx.id<yy.id;
}
void sol(){
	int n;
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i],num[i]=a[i];
	sort(num+1,num+n+1);
	int cnt=unique(num+1,num+n+1)-num-1;
	for (int i=1;i<=n;i++) a[i]=lower_bound(num+1,num+cnt+1,a[i])-num;
	for (int i=1;i<=n;i++) v[a[i]].pb(i);
	int q;
	cin>>q;
	for (int i=1;i<=q;i++) cin>>qq[i].k>>qq[i].pos,qq[i].id=i;
	sort(qq+1,qq+q+1,cmp);
	int now=cnt;
	int _=0;
	int __=1;
	for (int i=1;i<=n;i++){
		_++;
		if (_>v[now].size()){
			now--;
			_=1;
		}
		update(v[now][_-1],1,1,n);
		while (qq[__].k==i){
			int L=1,R=n;
			int Ans=0;
			while (L<=R){
				int mid=(L+R)>>1;
				if (query(1,mid,1,1,n)>=qq[__].pos) Ans=mid,R=mid-1;
				else L=mid+1;
			}
			qq[__++].ans=Ans;
		}
	}
	sort(qq+1,qq+q+1,cmp2);
	for (int i=1;i<=q;i++) cout<<num[a[qq[i].ans]]<<endl;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;
	while (t--) sol();
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1227D1 Optimal Subsequences (Hard Version) *1600](https://www.luogu.com.cn/problem/CF1227D1)

[CF1227D2 Optimal Subsequences (Hard Version) *1800](https://www.luogu.com.cn/problem/CF1227D2)

# 解题思路

本篇题解分 D1，D2 两个部分来写。

## D1 sol：

我们容易发现有以下两点性质：

- 要想子序列和**最大**，必须选择前 $k$ 大的数字。

- 比第 $k$ 大的数字还要大的数字是必须取的。

然后容易发现，我们能改变序列的差异只能是改变所有值为第 $k$ 大的数的选取情况。

那么显然，选取最前面的数是最优的。

直接暴力选取即可，时间复杂度 $O(nm + n \log n)$。

## D2 sol：

根据 D1 的思路，我们需要优化掉这个暴力。

考虑将询问离线，并按照查询的序列长度从小到大进行排序。

这样我们就只需要维护加数操作和目前加的数字有几个值为第 $k$ 大的数字即可。

加数操作和查询操作我们可以使用优先队列和树状数组维护。

时间复杂度 $O(m \log^2 n)$。

# 参考代码

## D1 code：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
#define bug cout<<"---------------------------------------\n";
ll _t_;
void _clear(){}
ll n,q;
ll a[100010],b[100010];
ll k;
map<ll,ll>mp,mp2;
bool cmp(ll x,ll y){
	return x>y;
}
void solve()
{
    _clear();
	cin>>n;
	forl(i,1,n)
		cin>>a[i],mp[a[i]]=1;
	for(auto i:mp)
		mp2[i.x]=++k;
	for(auto i:mp2)
		mp[i.y]=i.x;
	forl(i,1,n)
		a[i]=mp2[a[i]],b[i]=a[i];
	sort(b+1,b+1+n,cmp);
	cin>>q;
	while(q--)
	{
		ll x,y;
		cin>>x>>y;
		ll sum=0,num=b[x];
		ll last=0,L=x;
		while(b[L]==num)
			L--,last++;
		forl(i,1,n)
		{
			sum+=a[i]>num;
			if(a[i]==num && last)
				last--,sum++;
			if(sum==y)
			{
				cout<<mp[a[i]]<<endl;
				break;
			}
		}
	}
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
 //   cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

## D2 code：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<pii>
#define minqueue priority_queue<pii,vector<pii>,greater<pii>>
#define bug cout<<"---------------------------------------\n";
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
ll n,Q;
ll a[1000010],b[1000010];
ll k;
map<ll,ll>mp,mp2;
bool cmp(ll x,ll y){
	return x>y;
}
struct node{
	ll x,y,id;
}q[1000010];
bool pmc(node x,node y){
	return x.x<y.x;
}
maxqueue qu;
ll ans[1000010];
ll tree[1000010];
ll qwq[1000010];
void add(ll x,ll y){
	for(;x<=2e5+5;x+=lowbit(x))
		tree[x]+=y;
}
ll query(ll x)
{
	ll sum=0;
	for(;x;x-=lowbit(x))
		sum+=tree[x];
	return sum;
}
void solve()
{
    _clear();
	cin>>n;
	forl(i,1,n)
		cin>>a[i],mp[a[i]]=1;
	for(auto i:mp)
		mp2[i.x]=++k;
	for(auto i:mp2)
		mp[i.y]=i.x;
	forl(i,1,n)
		a[i]=mp2[a[i]],b[i]=a[i];
	sort(b+1,b+1+n,cmp);
	forl(i,1,n)
		qu.push({a[i],-i});
	cin>>Q;
	forl(i,1,Q)
		cin>>q[i].x>>q[i].y,q[i].id=i;
	sort(q+1,q+1+Q,pmc);
	ll sz=0;
	forl(i,1,Q)
	{
		while(sz<q[i].x)
		{
			pii now=qu.top();
			qu.pop();
			add(-now.y,1);
		//	add(-now.y+1,-1);
			sz++;
		}
		ll L=1,R=n;
		while(L<R)
		{
			ll Mid=(L+R)/2;
			if(query(Mid)<q[i].y)
				L=Mid+1;
			else
				R=Mid;
		}
		ans[q[i].id]=mp[a[L]];
		qwq[q[i].id]=L;
	}
	forl(i,1,Q)
//		cout<<qwq[i]<<':',
		cout<<ans[i]<<endl;
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
 //   cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

