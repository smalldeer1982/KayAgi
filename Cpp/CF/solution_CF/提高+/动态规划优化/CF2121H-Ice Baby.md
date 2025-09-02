# Ice Baby

## 题目描述

一个整数数组 $a_1, a_2, \ldots, a_n$ 的最长不下降子序列，指的是满足 $1 \leq i_1 < i_2 < \ldots < i_k \leq n$ 且 $a_{i_1} \leq a_{i_2} \leq \ldots \leq a_{i_k}$ 的最长的索引序列。该序列的长度定义为序列中元素的个数。例如，数组 $a = [3, 1, 4, 1, 2]$ 的最长不下降子序列的长度为 $3$。

现在给定两个整数数组 $l_1, l_2, \ldots, l_n$ 和 $r_1, r_2, \ldots, r_n$。对于每个 $1 \leq k \leq n$，解决如下问题：

- 考虑所有长度为 $k$ 的整数数组 $a$，使得对于每个 $1 \leq i \leq k$，都有 $l_i \leq a_i \leq r_i$。在所有这样的数组中，求最长不下降子序列的最大长度。

## 说明/提示

在第一个测试用例中，唯一可能的数组为 $a = [1]$。该数组的最长不下降子序列长度为 $1$。

在第二个测试用例中，对于 $k = 2$，无论如何选择 $a_1$ 和 $a_2$，总有 $a_1 > a_2$。因此，$k = 2$ 的答案为 $1$。

在第三个测试用例中，对于 $k = 4$，可以选择数组 $a = [5, 3, 3, 3]$。该数组的最长不下降子序列长度为 $3$。

在第四个测试用例中，对于 $k = 8$，可以选择数组 $a = [7, 5, 3, 5, 3, 3, 3, 3]$。该数组的最长不下降子序列长度为 $5$。

在第五个测试用例中，对于 $k = 5$，可以选择数组 $a = [2, 8, 5, 3, 3]$。该数组的最长不下降子序列长度为 $3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
1
1 1
2
3 4
1 2
4
4 5
3 4
1 3
3 3
8
6 8
4 6
3 5
5 5
3 4
1 3
2 4
3 3
5
1 2
6 8
4 5
2 3
3 3
11
35 120
66 229
41 266
98 164
55 153
125 174
139 237
30 72
138 212
109 123
174 196```

### 输出

```
1 
1 1 
1 2 2 3 
1 2 2 3 3 3 4 5 
1 2 2 2 3 
1 2 3 4 5 6 7 7 8 8 9```

# 题解

## 作者：ddxrS_loves_zxr (赞：5)

### 题目大意

给定 $n$ 对数 $(l_i,r_i)$，对于每一个 $1\le k\le n$，求出所有可能的整数数组 $a$ 的最长非递减子序列的最长长度，其中 $a_i\in [l_i,r_i]$。

### 思路

考虑维护一个数组 $dp$，其中 $dp_i$ 表示当最长非递减子序列的长度为 $i$ 时，结尾的数的最小值。

可以发现，$dp$ 数组是不递减的。考虑当前加入 $l_i,r_i$ 对 $dp$ 数组产生的变化。

将其分为三段 $[1,L],(L,R],(R,n]$，满足 $\forall j\in[1,L],dp_j\le l_i$，$\forall j\in(L,R],l_i<dp_j\le r_i$，$\forall j\in(R,n],r_i<dp_j$。

- 第一段中的值不会发生变化。

- 第二段中的 $dp_j$ 可能在 $dp_{j-1}$ 后接一个 $[l_i,r_i]$ 中的数来变得更小。有 $dp_j=\max(dp_{j-1},l_i)$，实际上就是一个区间平移，然后将 $dp_{L+1}$ 变为 $l_i$。

- 第三段中的数，只有 $dp_{R+1}$ 可能会变为 $\max(dp_R,l_i)=dp_R$。

可以使用 multiset 维护上述过程。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
multiset<int> dp;
void solve() {
    cin>>n; 
    dp.insert(0);
    for(int i = 1, l, r; i <= n; i++) {
        cin>>l>>r;
        auto pos = dp.upper_bound(r);
        dp.insert(l);
        if(pos != dp.end()) dp.erase(pos);
        cout<<dp.size() - 1<<" \n"[i == n];
    }
    dp.clear();
}
signed main() {
#ifdef ddxrS
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);         
#endif
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
	cerr<<clock() * 1.0 / CLOCKS_PER_SEC<<'\n'; 
	return 0;
}
```

---

## 作者：CQ_Bab (赞：2)

# 前言
本篇题解是 $O(n\log^2{n})$ 的，其实也能优化只不过作者太懒就不想优化了，反正也能过。
# 思路
首先我们考虑最暴力的 Dp，我们定义 $f_{i,j}$ 表示强制选第 $i$ 个为序列末尾第 $i$ 个的值取的 $j$ 的答案，然后我们有发现因为此序列要求非递减所以每一个值取 $l_i$ 或者 $r_i$ 一定能使答案最优，那么我们就会了 $n^3$ 考虑优化，我们发现 $f_{i,j}$ 中的 $i$ 并没有什么用，那么考虑定义 $f_i$ 表示最后一位的值为 $i$ 的答案，那么更新也很简单 $f_i=\max(f_{1}\sim f_{i})+1$ 那么我们定义 $g_i=\max(f_1\sim f_l)$ 那么其实对于一次操作我们只需要将 $l\sim r$ 加一然后动态维护前缀 max 即可。

这里我们用线段树可以轻松处理这个问题，只用支持区间加，区间覆盖以及单点查询即可，主要是注意一下区间的 tag 的更新顺序。
# 代码
细节见代码。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
const int N=4e5+10;
struct node{
	int l,r;
	int tag,mx,tag1;
}tr[N<<5];
int arr[N],tot;
void up(int x) {
	tr[x].mx=max(tr[x<<1].mx,tr[x<<1|1].mx);
}
void build(int u,int l,int r) {
	tr[u]={l,r,0,0,0};
	if(l==r) return;
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
}
void down(int u) {
	if(tr[u].tag1) {
		tr[u<<1].tag1=max(tr[u<<1].tag1,tr[u].tag1);
		tr[u<<1|1].tag1=max(tr[u<<1|1].tag1,tr[u].tag1);
		tr[u<<1].mx=max(tr[u<<1].mx,tr[u].tag1);
		tr[u<<1|1].mx=max(tr[u<<1|1].mx,tr[u].tag1);
		tr[u<<1].tag=tr[u<<1|1].tag=false;
		tr[u].tag1=0;
	}
	if(tr[u].tag) {
		tr[u<<1].tag+=tr[u].tag;
		tr[u<<1|1].tag+=tr[u].tag;
		tr[u<<1].mx+=tr[u].tag;
		tr[u<<1|1].mx+=tr[u].tag;
		tr[u].tag=false;
	}
}
void modify(int u,int l,int r,int k) {
	if(l>r) return;
	if(tr[u].l>=l&&tr[u].r<=r) {
		tr[u].mx+=k;
		tr[u].tag+=k;
		return;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=l) modify(u<<1,l,r,k);
	if(mid<r) modify(u<<1|1,l,r,k);
	up(u);
}
void modify1(int u,int l,int r,int k) {
	if(l>r) return;
	if(tr[u].l>=l&&tr[u].r<=r) {
		tr[u].mx=max(tr[u].mx,k);
		tr[u].tag1=max(tr[u].tag1,k);
		tr[u].tag=false;
		return;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=l) modify1(u<<1,l,r,k);
	if(mid<r) modify1(u<<1|1,l,r,k);
	up(u);
}
int Ans(int u,int x) {
	if(tr[u].l==tr[u].r) return tr[u].mx;
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=x) return Ans(u<<1,x);
	return Ans(u<<1|1,x);
}
int l[N],r[N],n;
void solve() {
	tot=false;
	in(n);
	rep(i,1,n) in(l[i]),in(r[i]),arr[++tot]=l[i],arr[++tot]=r[i];
	sort(arr+1,arr+1+tot);
	int mm=unique(arr+1,arr+1+tot)-arr-1;
	rep(i,1,n) l[i]=lower_bound(arr+1,arr+1+mm,l[i])-arr,r[i]=lower_bound(arr+1,arr+1+mm,r[i])-arr;
	build(1,1,mm);
	rep(i,1,n) {
		modify(1,l[i],r[i],1);
		int kk=Ans(1,r[i]);
		int ll=r[i]+1,rr=mm,res=0;
		while(ll<=rr) {
			int mid=ll+rr>>1;
			if(Ans(1,mid)<kk) ll=mid+1,res=mid;
			else rr=mid-1;
		}
		modify1(1,r[i]+1,res,kk);
		printf("%lld ",tr[1].mx);
	}
	cout<<endl;
}
fire main() {
	in(T);
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：wjyppm1403 (赞：2)

2025.6.27 感谢 Xpigeon 的指正，我原题解有一部分在狗叫，已修正。

---
转移优化？我可是高贵的 DIV 3 选手耶。

无脑做法，考虑什么时候能取到长度最大值，显然我们可以构造一个序列 $a$ 满足对于每一个 $a_{i}$ 有两个决策，要么就是取下界 $l_{i}$，要么就是延伸上一个末尾的值，就是令当前值为 $a_{j}$，其中 $a_{j}\ge l_{i},j<i$。考虑分类讨论：

- 取 $l_{i}$，那么对于序列中在区间 $[1,i-1]$ 结尾值 $\le l_i$ 的最长不下降子序列长度加 1。
- 不取 $l_{i}$，那么只能取 $[l_{i}+1,r_{i}]$。考虑对于 $l_{i}+1$ 的取值，可以通过 $[1,l_i +1]$ 转移过来，显然这样对于 $[1,l_{i}$ 转移要么比取 $l_i$ 的时候更劣要么等价，同理 $l_{i}+2,l_{i}+3 \dots r_{i}$，那么我们只需要考虑对于序列中在区间 $[1,i-1]$ 结尾值为 $[l_{i}+1,r_{i}]$ 的最长不下降子序列长度加 1。

这是线段树维护 $\max$ 和区间加与单点修改，注意要离散化不然会炸掉。时间复杂度 $O(n \log n)$。

给机房省队大佬做了，认为是蓝，超强教练认为绿，也不知道咋取，感觉是蓝。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int T,n,tot,b[MN],L[MN],R[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct Node{
        int l,r,val,add;
    }t[MN<<2];

    void doadd(int p,int k){
        t[p].val+=k;
        t[p].add+=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void pushup(int p){
        t[p].val=max(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].add=0;
        if(l==r){
            t[p].val=0;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=k;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=-1e9;
        if(mid>=fl) ret=query(ls,fl,fr);
        if(mid<fr) ret=max(ret,query(rs,fl,fr));
        return ret;
    }

#undef ls
#undef rs
}sg;

void clear(){
    tot=0;
}

void solve(){
    cin>>n;
    clear();
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
        b[++tot]=L[i];
        b[++tot]=R[i];
    }
    sort(b+1,b+1+tot);
    tot=unique(b+1,b+1+tot)-b-1;
    for(int i=1;i<=n;i++){
        L[i]=lower_bound(b+1,b+1+tot,L[i])-b;
        R[i]=lower_bound(b+1,b+1+tot,R[i])-b;
    }
    sg.build(1,1,tot);
    for(int i=1;i<=n;i++){
        int c=sg.query(1,1,L[i])+1;
        sg.modify(1,L[i],c);
        if(L[i]!=R[i]) sg.modify(1,L[i]+1,R[i],1); // 因为没判炸缸2.5
        cout<<sg.t[1].val<<" ";
    }
    cout<<'\n';
}

signed main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：WYX1210 (赞：1)

**思路**

设 $dp[i][j]$ 表示前 $i$ 个元素中满足存在长度为 $j$ 的非递减子序列且末尾元素为 $x$ 的最小 $x$ 值。转移规则为：

若 $dp[i][j] \leq l_{i+1}$，则 $dp[i+1][j]=dp[i][j]$。

若 $dp[i][j-1] \leq r_{i+1}$，则 $dp[i+1][j]=\max(l_{i+1},dp[i][j-1])$。

否则 $dp[i+1][j]=dp[i][j]$。

从第二个转移可以看出，我们要找的实际上就是一个断言，而为了让结果最大，我们可以将比新增的 $r$ 大的最小的元素删除。这样我们只需维护动态值多集合 $dp_i$，通过插入 $l_{i+1}$ 和删除大于 $r_{i+1}$ 的最小值实现更新。

时间复杂度 $O(n \log n)$。

**代码**
```cpp
#include<bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<=b;i++)
#define df(i,a,b) for(int i=a;i>=b;i--)
#define multicase() int t;cin>>t;while(t--)
using namespace std;
const int N = 2e5 + 5;
int n,x,y;
multiset<int> p;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	multicase(){
		cin >> n ;
		f(i,1,n) {
			cin >> x >> y;
			auto px = p.upper_bound(y);
			p.insert(x);
			if(px != p.end()) p.erase(px);
			cout << p.size() << " \n"[i==n];
		}
		p.clear();
	}
	return 0;
}


```

---

## 作者：_anll_ (赞：1)

代码好写，但是有个地方死活没理解到，卡了半个上午，菜啊/cf。于是本篇题解是官方题解+着重讲解被卡住地方。

## 思路
连续不降子序列一般有两种思考方向，一种是强制选 $i$ 最长可以取多少，一种是在前 $i$ 个中取 $j$ 个末尾最小值是多少。这道题的方向是后者，令最小值为 $dp_{i,j}$，显然第一维可以省去，有 $O(n^2)$ 转移。

具体而言，是有三种情况：
$$
\begin{cases}
R_i\le dp_{j-1} & dp_{j}=dp_{j}\\
L_i<dp_{j},R_i>dp_{j-1} & dp_{j}=\max(dp_{j-1},L_i)\\
L_i\ge dp_j & dp_{i,j}=dp_{j}
\end{cases}
$$
注意到 $dp$ 是一个不降序列，因此我们可以用 multiset 维护这个序列。到这都很易懂，这里主要解释为什么 $L_i$ 至多会被取一次。

令 $dp_j\le L_i,dp_{j+1}>L$，由于 $dp_j\le L$，因此显然是第三种情况；$dp_{j+1}>L,dp_j\le L_i$，因此会取 $L_i$；$dp_{j+1}>L$，所以 $dp_{j+2}$ 会取 $dp_{j+1}$。于是发现只会取一次 $L_i$，于是每次至多只会对 multiset 进行两次操作。

时间复杂度 $O(n\log n)$。

## 代码
```cpp
#include<set>
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e10;
int t,n,ans,L[N],R[N];
multiset<int> dp;
void solve(){
	cin>>n;dp.clear();ans=0;
	for(int i=1;i<=n;i++) cin>>L[i]>>R[i];
	for(int i=1;i<=n;i++) dp.insert(inf);
	for(int i=1;i<=n;i++){
		auto a=dp.lower_bound(R[i]+1);
		if(a==dp.end()) continue;
		int x=*a;if(x<=L[i]) continue;
		dp.erase(a);dp.insert(L[i]);
		if(x==inf) ans++;cout<<ans<<" ";
	}
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

---

## 作者：StayAlone (赞：1)

官方题解精妙做法的另一种理解。

设 $f_{i, j}$ 表示考虑前缀 $i$，且 $a_i\le j$ 时的最长不下降子序列长度。

显然 $f_i$ 是一个不降序列。每次插入 $[l_i,r_i]$，等价于：

1. 区间 $[l_i,r_i]$ 加 $1$
2. 取前缀 $\max$

第二步等价于用 $f_{i,r_i}$ 往后区间覆盖，直到第一个比 $f_{i, r_i}$ 大的位置。

可以用线段树做，不过有更好的维护方式。

考虑用 multiset 维护 $f_i$ 差分的“断点”，即集合中放 $f_{i, j}-f_{i, j-1}$ 个 $j$。形式化地，此时 $f_{i, j}=|\{v\mid v\le j\land v\in S\}|$。

于是上述操作等价于，将第一个比 $r$ 大的断点删去，并插入 $l$。

时间复杂度 $\mathcal O(n\log n)$。

[AC record](https://codeforces.com/contest/2121/submission/324960483)

```cpp
il void solve() {
    read(n); multiset <int> dp;
    rep1(i, 1, n) {
        int l, r; read(l, r);
        auto it = dp.upper_bound(r);
        if (it != end(dp)) dp.erase(it);
        dp.emplace(l); cout << dp.size() << ' ';
    } puts("");
}

int main() {
    for (int T = read(); T--; ) solve();
    return 0;
}
```

---

## 作者：未来姚班zyl (赞：1)

设 $dp_i$ 表示长度为 $i$ 的子序列结尾的最小值，则对于位置 $x$，对于 $dp_i\le l_x$，有 $dp_{i+1}=\min(dp_{i+1},l_x)$，这条转移只对 $dp_i>l_x$ 的最小的 $i$ 有效。对于 $l_x\le dp_i\le r_i$，有 $dp_{i+1}=\min(dp_{i+1},dp_i)$，由于 $dp$ 数组单调性的存在，这些转移绝对有效，是一个区间平移。

归纳一下可以发现可以直接用 map 维护，支持加点删点，找后继，复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
#define YY puts("Yes"),exit(0)
#define NN puts("No"),exit(0)
#define yy return puts("Yes"),void()
#define nn return puts("No"),void()
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=6e5+30,M=1e6+5,inf=(1LL<<30)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
const int D=2e5+5;
int n,tot;
struct node{
	int l,r;
}a[N];
map<int,int>dp; 
inline int getre(int x){
	auto it=dp.upper_bound(x);
	if(it==dp.end())return -1;
	return (*it).first;
}
inline void Main(){
	n=read();
	dp.clear(),dp[0]=1,tot=0;
	repn(i)a[i].l=read(),a[i].r=read();
	repn(i){
		int C=getre(a[i].r);
		dp[a[i].l]++,tot++;
		if(C!=-1){
			dp[C]--;
			if(!dp[C])dp.erase(C);
			tot--;
		}
		cout <<tot<<' ';
	} 
	puts("");
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```

这道题还是太简单了，CF 上存在一道这道题的加强版，就是把求最长非递减子序列改成最长上升子序列：[CF809D](https://codeforces.com/problemset/problem/809/D)。

---

## 作者：panyanppyy (赞：0)

题解区怎么只有离散化线段树，这里给个动态开点线段树做法，复杂度是 $\mathcal O(n\log w)$ 的。

## Problem

题目很简单，$a_i$ 可以从 $[l_i,r_i]$ 中选择，问你最后最大的最长不降子序列。

## Solution

设状态 $f_i$ 表示当前最后一个数字（最大的数字）为 $i$ ，转移有两种：

1. 能取最小肯定贪心地取最小的 $l_i$ 更优 $f_{l_i}$ 可以从小于 $l_i$ 的地方转移过来，即：
  
   $f_{l_i}\gets \max_{j\in [1,l_i-1]}{f_j}+1$。
2. 从同样的数字转移肯定不增加更优所以：
   
   $f_j\gets f_j+1 ,{j\in [l_i,r_i]}$

于是，就可以~~暴力地~~愉快地线段树了。

我们需要一个区间 $+1$ 操作和一个单点修改操作。

因为懒得离散化，所以直接动态开点了。

**注意**：使用线段树询问 $1\sim l_i-1$ 最大值时可能会越界，需要特判一下，否则会 RE。

## Code
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define all(x) x.begin(),x.end()
using namespace std;
template<typename T_>void Max(T_&x,const T_&y){if(y>x)x=y;}
template<typename T_>void Min(T_&x,const T_&y){if(y<x)x=y;}
template<typename T_>void operator+=(vector<T_>&x,const T_&y){x.push_back(y);}
template<typename T_>void operator--(vector<T_>&x){x.pop_back();}
const int N=2e5+7,_=1e9;
int T,n,mx[N*64],lzy[N*64],ls[N*64],rs[N*64],cnt,rot;//开大点准没错
void f(int rt,int x){mx[rt]+=x,lzy[rt]+=x;}
void push_down(int rt){
	if(!lzy[rt])return;
	if(!ls[rt])ls[rt]=++cnt;//这里要开点，否则信息会丢失
	if(!rs[rt])rs[rt]=++cnt;
	f(ls[rt],lzy[rt]),f(rs[rt],lzy[rt]);
	lzy[rt]=0;
}
void push_up(int rt){mx[rt]=max(mx[ls[rt]],mx[rs[rt]]);}
void update(int x,int l,int r,int k,int&rt){
	if(!rt)rt=++cnt;
	if(l==r)return Max(mx[rt],k);
	int mid=(l+r)>>1;push_down(rt);
	if(x<=mid)update(x,l,mid,k,ls[rt]);
	else update(x,mid+1,r,k,rs[rt]);
	push_up(rt);
}
void add(int L,int R,int l,int r,int k,int&rt){
	if(!rt)rt=++cnt;
	if(L<=l&&r<=R)return f(rt,k);
	int mid=(l+r)>>1;push_down(rt);
	if(L<=mid)add(L,R,l,mid,k,ls[rt]);
	if(R>mid)add(L,R,mid+1,r,k,rs[rt]);
	push_up(rt);
}
int query(int L,int R,int l,int r,int rt){
	if(L>R||!rt)return 0;//特判
	if(L<=l&&r<=R)return mx[rt];
	int mid=(l+r)>>1,res=0;push_down(rt);
	if(L<=mid)Max(res,query(L,R,l,mid,ls[rt]));
	if(R>mid)Max(res,query(L,R,mid+1,r,rs[rt]));
	return res;
}
void work(){
	cin>>n;
	for(int i=1,l,r,x;i<=n;i++){
		cin>>l>>r;
		x=query(1,l-1,1,_,rot);
		add(l,r,1,_,1,rot);//区间加
		update(l,1,_,x+1,rot);//单点修改
		cout<<query(1,_,1,_,rot)<<' ';//询问 max
	}
	cout<<'\n';
	for(int i=0;i<=cnt;i++)ls[i]=rs[i]=lzy[i]=mx[i]=0;
	cnt=rot=0;//清空用过的就行
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：0)

设 $f_i$ 表示答案长度为 $i$ 时，结尾的最小值。因此当 $f_{i - 1} \le r_i$ 时可以进行转移 $f_i = \max (f_{i - 1},l_i)$。于是可以得到 $O(n^2)$ 的代码：

```cpp
for (int i = 1;i <= n;++i)
{
    for (int j = i;j;--j)
    {
        if (dp[j - 1] > r[i]) continue;
        dp[j] = min (dp[j],max (dp[j - 1],l[i]));
        ans = max (ans,j);
    }
    cout<<ans<<" \n"[i == n];
}
```

按照官方题解的思路可以用 multiset 优化到 $O(n \log n)$，在此不赘述。

---

换一种角度，设 $f_i$ 表示最后一个数字为 $i$ 时的最大长度。则在遇到第 $k$ 个区间 $[l_k,r_k]$ 时，有 $f_{l_k} = \max\limits_{j \mid j \le l_k}\{f_j\} + 1$，线段树维护最大值即可。而 $f_{l_k + 1} \sim f_r$ 就可以保持原来的数字不变，相当于区间加一。最后的答案就是全局最大值。

又因为值域较大，需要先进行离散化操作。最后，我们可以得到线段树优化到 $O (n \log n)$ 代码：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 4e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int tree[MAX << 2],tmp[MAX << 2];
void pushup (int cur) {tree[cur] = max (tree[cur << 1],tree[cur << 1 | 1]);}
void pushdown (int cur)
{
    if (!tmp[cur]) return ;
    tree[cur << 1] += tmp[cur];tree[cur << 1 | 1] += tmp[cur];
    tmp[cur << 1] += tmp[cur];tmp[cur << 1 | 1] += tmp[cur];
    tmp[cur] = 0;
}
void build (int cur,int l,int r)
{
    tree[cur] = tmp[cur] = 0;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    build (cur << 1,l,mid);build (cur << 1 | 1,mid + 1,r);
}
void modify1 (int cur,int l,int r,int x,int v)
{
    if (l == r) {tree[cur] = v;return ;}
    int mid = (l + r) >> 1;
    pushdown (cur);
    if (x <= mid) modify1 (cur << 1,l,mid,x,v);
    else modify1 (cur << 1 | 1,mid + 1,r,x,v);
    pushup (cur);
}
void modify2 (int cur,int l,int r,int x,int y)
{
    if (y < l || x > r) return ;
    if (x <= l && y >= r) {++tree[cur];++tmp[cur];return ;}
    int mid = (l + r) >> 1;
    pushdown (cur);
    if (x <= mid) modify2 (cur << 1,l,mid,x,y);
    if (y > mid) modify2 (cur << 1 | 1,mid + 1,r,x,y);
    pushup (cur);
}
int query (int cur,int l,int r,int x,int y)
{
    if (y < l || x > r) return 0;
    if (x <= l && y >= r) return tree[cur];
    int mid = (l + r) >> 1,res = 0;
    pushdown (cur);
    if (x <= mid) res = max (res,query (cur << 1,l,mid,x,y));
    if (y > mid) res = max (res,query (cur << 1 | 1,mid + 1,r,x,y));
    return res;
}
void solve ()
{
    int n = read ();
    vector <int> l (n + 1),r (n + 1),num;
    for (int i = 1;i <= n;++i) l[i] = read (),r[i] = read (),num.push_back (l[i]),num.push_back (r[i]);
    sort (num.begin (),num.end ());
    num.erase (unique (num.begin (),num.end ()),num.end ());
    int tot = num.size ();build (1,1,tot);
    //f[i] 表示最后一个数字为 i 时的最大长度
    for (int i = 1;i <= n;++i)
    {
        l[i] = lower_bound (num.begin (),num.end (),l[i]) - num.begin () + 1;
        r[i] = lower_bound (num.begin (),num.end (),r[i]) - num.begin () + 1;
        modify1 (1,1,tot,l[i],query (1,1,tot,1,l[i]) + 1);
        modify2 (1,1,tot,l[i] + 1,r[i]);
        cout<<tree[1]<<" \n"[i == n];
    }
}
int main ()
{
    int t = read ();
    while (t--) solve ();
    return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
    {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

