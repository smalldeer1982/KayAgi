# [COTS 2025] 观草 / Trava

## 题目描述


给定正整数数列 $a_1\sim a_N$。

有 $Q$ 个操作：

- $\texttt{?}$ $k$：查询 $\displaystyle \sum_{1\le i\le N-k+1} \max(a_i,a_{i+1},\ldots,a_{i+k-1})$；
- $\texttt{+}$ $k$：令 $a_k\gets a_{k}+1$。


## 说明/提示


### 数据范围

- $1\le N\le 5\times 10^5$；
- $0\le Q\le 5\times 10^5$；
- $1\le A_i\le 10^9$；
- $\mathrm{op}_i\in \{\texttt{?},\texttt{+}\}$；
- $1\le k_i\le N$；
- 所有输入的数均为整数。

### 子任务

Subtask 0 为样例。

| 子任务编号 | $N,Q\le$ | 特殊性质 | 得分 |
| :-: | :-: | :-: | :-: |
| $1$ | $7\, 000$ | $-$ | $13$ |
| $2$ | $5\times 10^5$ | $\text{A}$ | $16$ |
| $3$ | $5\times 10^5$ | $\text{B}$ | $23$ |
| $4$ | $5\times 10^5$ | $\text{C}$ | $10$ |
| $5$ | $10^5$ | $-$ | $20$ |
| $6$ | $5\times 10^5$ | $-$ | $18$ |

- 特殊性质 $\text{A}$：$\mathrm{op}_i\neq\texttt{+}$；
- 特殊性质 $\text{B}$：$a_i\le 10$；
- 特殊性质 $\text{C}$：对于所有 $\texttt{?}$ $k_i$ 操作，$k_i$ 均相等。


## 样例 #1

### 输入

```
6 5
1 7 2 3 5 4
+ 1
? 2
? 3
+ 5
? 3```

### 输出

```
27
24
26```

## 样例 #2

### 输入

```
10 4
1 2 2 1 3 2 1 3 2 2
? 4
? 5
+ 5
? 4```

### 输出

```
20
18
24```

# 题解

## 作者：Purslane (赞：2)

# Solution

简单数据结构题。考虑上一些小套路。

将第一问的和式改为：

$$
\sum_{t \ge 1} \sum_{i=1}^{n-k+1} [(\max_{i \le p \le i+k-1} a_p) \ge t]
$$

考虑稍微转化一下，设 $a$ 的上界为 $V$，改为：

$$
(n-k+1)V - \sum_{t = 1}^V \sum_{i=1}^{n-k+1} [(\min_{i \le p \le i+k-1} a_p) < t]
$$

这个怎么看呢，考虑记 $b_i = [a_i \ge t]$，$b$ 中相邻两个 $1$ 的距离分别为 $len_{1,2,\cdots,z}$（特别的认为 $b_0=b_{n+1}=1$），那么 $t$ 固定的时候和式就是 $\sum_{i=1}^z \max\{0,len_i - k + 1\}$。你把 $len$ 扔进一个树状数组中，就可以快速求解。

由于只有 $a_k \leftarrow a_k+1$ 的操作，所以每次只会有 $O(1)$ 个 $len$ 发生改变，直接暴力修改。

有一个小问题，你怎么处理初始的 $len$。有用的观察：存在 $t$ 使得 $b_i = b_j = 1$，$b_{i+1} = b_{i+2} = \cdots = b_{j-1} = 0$ 的 $(i,j)$ 只有 $O(n)$ 对。具体怎么做可以参考 JOISC 的铁道旅行（其实就是一个简单的单调栈）。

复杂度 $O(n \log n)$，足以通过本题。

非常罕见的不是特别慢。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,q,a[MAXN],t[MAXN<<2],V=2e9;
int tr[MAXN][2];
void Update(int pos,int v1,int v2) {
	pos=n-pos+1;
	while(pos<=n) tr[pos][0]+=v1,tr[pos][1]+=v2,pos+=pos&-pos;
	return ;
}
pair<int,int> Query(int pos) {
	int ans1=0,ans2=0;
	pos=n-pos+1;
	while(pos) ans1+=tr[pos][0],ans2+=tr[pos][1],pos-=pos&-pos;
	return {ans1,ans2};	
}
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void build(int k,int l,int r) {
	if(l==r) return t[k]=a[l],void();
	build(lson,l,mid),build(rson,mid+1,r);
	return t[k]=max(t[lson],t[rson]),void();	
}
int query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return t[k];
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return max(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));	
}
void modify(int k,int l,int r,int pos,int v) {
	if(l==r) return t[k]=v,void();
	if(pos<=mid) modify(lson,l,mid,pos,v);
	else modify(rson,mid+1,r,pos,v);
	return t[k]=max(t[lson],t[rson]),void();	
}
int bfind1(int k,int l,int r,int pos,int v) {
	if(r<pos||t[k]<v) return -1;
	if(l==r) return l;
	int tans=bfind1(lson,l,mid,pos,v);
	if(tans!=-1) return tans;
	return bfind1(rson,mid+1,r,pos,v);	
}
int bfind2(int k,int l,int r,int pos,int v) {
	if(l>pos||t[k]<v) return -1;
	if(l==r) return l;
	int tans=bfind2(rson,mid+1,r,pos,v);
	if(tans!=-1) return tans;
	return bfind2(lson,l,mid,pos,v);
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>a[i];
	a[0]=a[n+1]=V,build(1,0,n+1);
	stack<int> st; st.push(0);
	ffor(i,1,n+1) {
		while(!st.empty()&&a[i]>=a[st.top()]) {
			int l=st.top()+1,r=i-1;
			st.pop();
			if(l<=r) Update(r-l+1,min(a[l-1],a[r+1])-query(1,0,n+1,l,r),(r-l+1)*(min(a[l-1],a[r+1])-query(1,0,n+1,l,r)));
		}
		if(!st.empty()) {
			int l=st.top()+1,r=i-1;	
			if(l<=r) Update(r-l+1,min(a[l-1],a[r+1])-query(1,0,n+1,l,r),(r-l+1)*(min(a[l-1],a[r+1])-query(1,0,n+1,l,r)));
		}
		st.push(i);
	}
	ffor(i,1,q) {
		char op;
		int k;
		cin>>op>>k;
		if(op=='?') {
			auto pr=Query(k);
			cout<<V*(n-k+1)-(pr.second-(k-1)*pr.first)<<'\n';
		}
		else {
			int L=bfind2(1,0,n+1,k,a[k]+1)+1,R=bfind1(1,0,n+1,k,a[k]+1)-1;
			Update(R-L+1,-1,-(R-L+1));
			if(L<=k-1) Update(k-L,1,k-L);
			if(k+1<=R) Update(R-k,1,R-k);
			a[k]++,modify(1,0,n+1,k,a[k]);
		}
	}
	return 0;
}
```

---

## 作者：XZhuRen (赞：2)

简单题。

直接暴力思路：

考虑求出每个点在哪些区间担当最值。

对于元素 $a_p$ 向左右找到最长的严格/非严格小与它的区间 $[l,r]$ 则：

设 $d1=\min(p-l,r-p)+1$，$d2=\max(p-l,r-p)+1$。

这一段对于答案的贡献是：

$[1,d1]$：公差为 $a_p$ 的等差数列；

$(d1,d2]$：常值 $a_p\cdot d1$；

$(d2,r-l+1]$：公差为 $-a_p$ 的等差数列。

这样就可以预处理了。

再考虑修改，每次只增量 $1$，则当前元素 $a_p$ 若在 $[l,r]$ 内担任最值一定要求 $[l,p)<a_p$ 且 $(p,r]<a_p$。

这里取严格小于，否则我们一定可以找出另一个数担任最值。

容易发现现在相当于对答案产生等同于上面预处理的贡献，取所有公差都为 $1$ 即可。

温馨提示：

区间加等差数列——单点查询值线段树
可以用区间加区间查询线段树代替。

---

## 作者：HJY2022 (赞：1)

一个不用动脑子的笨b做法。

考虑先做静态的这个问题。套路的对于每一个 $a_i$ 求出以它为最大值的区间（方便起见这里钦定对于大小相同的 $a_i$，下标更小的 $a_i$ 更小）。

以 $a_i$ 为最大值的区间 $[l,r]$ 一定形如 $L_i \leq l \leq i \leq r \leq R_i$，而对于一个查询 $k$ 就是查询所有满足 $r - l + 1 = k$ 的区间的最大值之和。

将问题放到二维平面上处理，那么被转化为带权矩形加，查询某一个斜率固定的一次函数上的点权和，可以直接扫描线处理（具体来讲就是你按照一次函数的垂直方向扫，在触碰到矩形的四个顶点的时候处理一下贡献）。

考虑有修改的情况。容易发现只会有一些区间的最大值增加 $1$，而这些区间一定是以被修改的那个点作为最大值的区间。

用线段树维护所有的 $a_i$，可以帮我们在 $O(n \log n)$ 的时间内求出所有修改对应的区间，转化成矩形加。而带修改后的查询只需要套一个 cdq分治 即可处理，时间复杂度 $O(n \log n)$，常数略大。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lc x << 1
#define rc x << 1 | 1
const int MX = 5e5 + 7;

int val[MX << 2],a[MX];

void upd(int x){val[x] = max(val[lc],val[rc]);}

void build(int x,int l,int r){
	if(l == r){val[x] = a[l];return;}
	int mid = l + r >> 1;
	build(lc,l,mid);build(rc,mid + 1,r);
	upd(x);
}

void modify(int x,int l,int r,int k){
	if(l == r){val[x]++;a[l]++;return;}
	int mid = l + r >> 1;
	if(k <= mid)modify(lc,l,mid,k);
	else modify(rc,mid + 1,r,k);
	upd(x);
}

int query(int x,int l,int r,int ql,int qr){
	if(ql <= l && r <= qr)return val[x];
	int mid = l + r >> 1,ret = 0;
	if(ql <= mid)ret = max(ret,query(lc,l,mid,ql,qr));
	if(qr > mid)ret = max(ret,query(rc,mid + 1,r,ql,qr));
	upd(x);return ret;
}

struct sq{int x,val,typ,ti;};

char opt[MX];int k[MX];long long ans[MX];

sq vec[MX << 3],tmp[MX << 3];int tot = 0;

void pushback(sq t){vec[++tot] = t;}


void solve(int L,int R,int l,int r){
	if(L >= R || l >= r){
		sort(vec + L,vec + R + 1,[&](sq A,sq B){return A.x != B.x ? A.x < B.x : A.typ > B.typ;});
		return;
	}
	int mid = l + r >> 1,p = L;
	for(int i = L;i <= R;i++)
		if(vec[i].ti <= mid)swap(vec[i],vec[p++]);
	solve(L,p - 1,l,mid);solve(p,R,mid + 1,r);
	merge(vec + L,vec + p,vec + p,vec + R + 1,tmp + L,[&](sq A,sq B){return A.x != B.x ? A.x < B.x : A.typ > B.typ;});
	for(int i = L;i <= R;i++)vec[i] = tmp[i];
	long long numA = 0,numB = 0,sum = 0,las = 0;
	for(int i = L;i <= R;i++){
		if(vec[i].ti <= mid && vec[i].typ != 0){
			if(vec[i].typ == 1){numA += numB * (vec[i].x - las);numA += vec[i].val;numB += vec[i].val;las = vec[i].x;}
			if(vec[i].typ == 2){numA += numB * (vec[i].x - las);numB -= vec[i].val;las = vec[i].x;}
			if(vec[i].typ == 3){numA += numB * (vec[i].x - las);numB -= vec[i].val;las = vec[i].x;}
			if(vec[i].typ == 4){numA += numB * (vec[i].x - las);numB += vec[i].val;las = vec[i].x;}
		}
		if(vec[i].ti > mid && vec[i].typ == 0){
			numA += numB * (vec[i].x - las);ans[vec[i].ti] += numA;las = vec[i].x;
		}
	}
}

int pos;

int findl1(int x,int l,int r,int k,int rmax){
	if(l > k)return 0;
	if(l == r){
		if(max(rmax,a[l]) <= a[k + 1])pos = min(pos,l);
		return val[x];
	}
	int mid = l + r >> 1;
	if(k >= r){
		if(rmax > a[k + 1])return val[x];
		if(max(rmax,val[rc]) <= a[k + 1]){pos = min(pos,mid + 1);findl1(lc,l,mid,k,max(rmax,val[rc]));}
		else findl1(rc,mid + 1,r,k,rmax);
		return val[x];
	}
	else{
		int ret = 0;
		ret = findl1(rc,mid + 1,r,k,rmax);
		ret = max(ret,findl1(lc,l,mid,k,max(rmax,ret)));
		return ret;
	}
}

int findr(int x,int l,int r,int k,int lmax){
	if(r < k)return 0;
	if(l == r){
		if(max(lmax,a[l]) < a[k - 1])pos = max(pos,l);
		return val[x];
	}
	int mid = l + r >> 1;
	if(k <= l){
		if(lmax >= a[k - 1])return val[x];
		if(max(lmax,val[lc]) < a[k - 1]){pos = max(pos,mid);findr(rc,mid + 1,r,k,max(lmax,val[lc]));}
		else findr(lc,l,mid,k,lmax);
		return val[x];
	}
	else{
		int ret = 0;
		ret = findr(lc,l,mid,k,lmax);
		ret = max(ret,findr(rc,mid + 1,r,k,max(lmax,ret)));
		return ret;
	}
}

int findl2(int x,int l,int r,int k,int rmax){
	if(l > k)return 0;
	if(l == r){
		if(max(rmax,a[l]) < a[k + 1])pos = min(pos,l);
		return val[x];
	}
	int mid = l + r >> 1;
	if(k >= r){
		if(rmax > a[k + 1])return val[x];
		if(max(rmax,val[rc]) < a[k + 1]){pos = min(pos,mid + 1);findl2(lc,l,mid,k,max(rmax,val[rc]));}
		else findl2(rc,mid + 1,r,k,rmax);
		return val[x];
	}
	else{
		int ret = 0;
		ret = findl2(rc,mid + 1,r,k,rmax);
		ret = max(ret,findl2(lc,l,mid,k,max(rmax,ret)));
		return ret;
	}
}

int main(){
	int n,q;cin >> n >> q;
	for(int i = 1;i <= n;i++)cin >> a[i];
	build(1,1,n);
	for(int i = 1;i <= n;i++){
		int l,r,L = i,R = i;
		pos = i;
		findl1(1,1,n,i - 1,0);L = pos;
		pos = i;
		findr(1,1,n,i + 1,0);R = pos;
		pushback((sq){0,a[i],1,0});
		//cerr << "cur = " << i << " L = " << L << " R = " << R << '\n';
		int t1 = R - i,t2 = i - L;
		pushback((sq){min(t1,t2),a[i],2,0});
		pushback((sq){max(t1,t2),a[i],3,0});
		pushback((sq){R - L + 1,a[i],4,0});
	}
	for(int i = 1;i <= q;i++){
		cin >> opt[i] >> k[i];
		if(opt[i] == '+'){
			modify(1,1,n,k[i]);
			int l,r,L = k[i],R = k[i];
			pos = k[i];
			findl2(1,1,n,k[i] - 1,0);L = pos;
			pos = k[i];
			findr(1,1,n,k[i] + 1,0);R = pos;
			pushback((sq){0,1,1,i});
			int t1 = R - k[i],t2 = k[i] - L;
			pushback((sq){min(t1,t2),1,2,i});
			pushback((sq){max(t1,t2),1,3,i});
			pushback((sq){R - L + 1,1,4,i});
		}
		else pushback((sq){k[i] - 1,0,0,i});
	}
	solve(1,tot,0,q);
	for(int i = 1;i <= q;i++){
		if(opt[i] == '?')cout << ans[i] << '\n';
	}
	return 0;
}
```

---

## 作者：Sliarae (赞：1)

数据结构学傻警告。

下面 $ans \gets x$ 均表示 `ans += x`。

设 $ans_k = \sum\limits_{i = 1}^{n - k + 1} \max\limits_{j = i}^{i + k - 1} a_j$，先考虑没有修改，但是求所有 $ans_k$ 怎么做。

考察一个数字 $a_i$ 对某个 $ans_k$ 的贡献：

- 设 $L_i$ 表示 $i$ 左边第一个大于 $a_i$ 的数，$R_i$ 表示 $i$ 右边第一个不小于 $a_i$ 的数。

- 显然在开区间 $\big(  \max(L_i, i - k), \min(R_i, i + k) \big) $ 中任选一个长度为 $k$ 的区间，$a_i$ 都是最大值。

- 于是 $ans_k \gets a_i \max \big(0, \min\{k, R_i - L_i - k, i - L_i, R_i - i\} \big)$。

这个看上去可以做，所以我们先放在一边，考虑加入修改操作后怎么做：

假设我们做了 $a_p \gets a_p + 1$，一个区间的 $\max$ 要么不变，要么加 $1$。而且一个区间的 $\max$ 加 $1$ 当且仅当，修改操作后区间中除 $a_p$ 外，没有 $\ge a_p$ 的数。

于是找 $a_p$ 之前第一个 $\ge a_p$ 的位置，记为 $L$；$a_p$ 之后第一个 $\ge a_p$ 的位置，记为 $R$（找 $L, R$ 可以线段树二分），在 $\big(\max(L, p - k), \min(R, p + k)\big)$ 中任意长度为 $k$ 的区间 $\max$ 都加 $1$。

所以相当于对于所有 $k$，执行 $ans_k \gets \max\big(0, \min\{k, R - L - k, i - L, R - i\}\big)$。

设 $i - L = p, R - i = q$，那么 $ans_k \gets \max\big(0, \min\{p, q, k, p + q - k\} \big)$。

令 $p \le q$，当 $k \in [1, p]$ 时 $ans_k \gets k$；当 $k \in (p, q]$ 时 $ans_k \gets p$，当 $k \in (q, p + q]$ 时 $ans_k \gets p + q - k$，于是可以用线段树维护关于 $k$ 的一次函数。

求初始时 $ans_k$ 的问题是一样的。

时间复杂度 $O(n \log n)$。

```cpp
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;
using LL = long long;
using Pii = pair<LL, LL>;

const int kN = 5e5 + 5; 
const int kT = kN * 4; 

int n, q;
int a[kN];

struct Seg {
  #define lc (k << 1)
  #define rc ((k << 1) | 1)

  int mx[kT];

  void Build (int k, int L = 1, int R = n) {
    if (L == R) {
      mx[k] = a[L];
      return; 
    }
    int mid = (L + R) >> 1;
    Build(lc, L, mid);
    Build(rc, mid + 1, R);
    mx[k] = max(mx[lc], mx[rc]);
  }

  void Add (int k, int x, int L = 1, int R = n) {
    if (L == R) return ++mx[k], void();
    int mid = (L + R) >> 1;
    if (x <= mid) Add(lc, x, L, mid);
    else Add(rc, x, mid + 1, R);
    mx[k] = max(mx[lc], mx[rc]);
  }

  int Subtree_pre (int k, int x, int L, int R) {
    if (L == R) return L;
    int mid = (L + R) >> 1;
    if (mx[rc] >= a[x]) return Subtree_pre(rc, x, mid + 1, R);
    else return Subtree_pre(lc, x, L, mid);
  }

  int Find_pre (int k, int x, int L = 1, int R = n) {
    if (L == R) return -1;
    int mid = (L + R) >> 1;
    if (x <= mid) return Find_pre(lc, x, L, mid);
    int ret = Find_pre(rc, x, mid + 1, R);
    if (ret != -1) return ret;
    if (mx[lc] >= a[x]) return Subtree_pre(lc, x, L, mid); 
    return -1;
  }

  int Subtree_nex (int k, int x, int L, int R) {
    if (L == R) return L; 
    int mid = (L + R) >> 1;
    if (mx[lc] >= a[x]) return Subtree_nex(lc, x, L, mid);
    else return Subtree_nex(rc, x, mid + 1, R);
  }

  int Find_nex (int k, int x, int L = 1, int R = n) {
    if (L == R) return -1;
    int mid = (L + R) >> 1;
    if (x > mid) return Find_nex(rc, x, mid + 1, R);
    int ret = Find_nex(lc, x, L, mid);
    if (ret != -1) return ret;
    if (mx[rc] >= a[x]) return Subtree_nex(rc, x, mid + 1, R);
    return -1;
  }

  #undef lc
  #undef rc
} seg;

Pii operator+ (Pii a, Pii b) {
  return {a.first + b.first, a.second + b.second};
}

struct Seg2 {
  #define lc (k << 1)
  #define rc ((k << 1) | 1)

  Pii tag[kT];

  void Add (int k, int l, int r, Pii a, int L = 1, int R = n) {
    if (l <= L && r >= R) {
      tag[k] = tag[k] + a;
      return;  
    } 
    int mid = (L + R) >> 1;
    if (l <= mid) Add(lc, l, r, a, L, mid);
    if (r > mid) Add(rc, l, r, a, mid + 1, R);
  }

  Pii Query (int k, int x, int L = 1, int R = n) {
    Pii res = tag[k];
    if (L != R) {
      int mid = (L + R) >> 1;
      if (x <= mid) res = res + Query(lc, x, L, mid);
      else res = res + Query(rc, x, mid + 1, R);
    }
    return res;
  }

  #undef lc 
  #undef rc
} seg2;

void Add (int p, int q, int v) {
  int a = min(p, q), b = p + q;
  seg2.Add(1, 1, a, {v, 0});
  if (p != q) seg2.Add(1, a + 1, b - a, {0, 1ll * v * a});
  if (max(p, q) != n) seg2.Add(1, b - a + 1, min(b, n), {-v, 1ll * v * b});
  // for (int k = 1; k <= n; ++k) {
  //   arr[k] += 1ll * v * max(0, min({p, q, k, p + q - k}));
  // }
}

LL Query (int k) {
  Pii line = seg2.Query(1, k);
  return line.first * k + line.second;
}

int main () {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  stack<int> st;
  static int L[kN], R[kN];
  for (int i = 1; i <= n; ++i) {
    while (!st.empty() && a[i] > a[st.top()]) {
      R[st.top()] = i; 
      st.pop();
    }
    L[i] = (st.empty() ? 0 : st.top());
    st.push(i);
  }
  while (!st.empty()) R[st.top()] = n + 1, st.pop();
  for (int i = 1; i <= n; ++i) {
    Add(i - L[i], R[i] - i, a[i]);
  }
  seg.Build(1);
  for (int i = 1; i <= q; ++i) {
    char o;
    int x;
    cin >> o >> x;
    if (o == '?') {
      // cout << arr[x] << '\n';
      cout << Query(x) << '\n';
    }
    else {
      ++a[x], seg.Add(1, x);
      int L = seg.Find_pre(1, x), R = seg.Find_nex(1, x);
      if (L == -1) L = 0; 
      if (R == -1) R = n + 1;
      Add(x - L, R - x, 1);
    }
  }
  return 0; 
}
```

---

## 作者：masterhuang (赞：0)

> 给定正整数数列 $a_1\sim a_N$。有 $Q$ 个操作：
>
> - `? k`：查询 $\displaystyle \sum_{1\le i\le N-k+1} \max(a_i,a_{i+1},\ldots,a_{i+k-1})$。
> - `+ k`：令 $a_k\gets a_{k}+1$。
>
> $1\le N,Q\le 5\times 10^5,1\le a_i\le 10^9$。

这个题绝对配得上**小清新**三个字。

下面设 $a$ 的上界为定值 $V$，实际实现可以设 $V=2\times 10^9$ 啥的都没问题。

第一步就挺难想到的：考虑拆 $\max\to \sum\limits_{i=1}^V [\max\ge i]\to V-\sum\limits_{1=1 }^V [\max<i]$。

这是因为显然 $\max<i$ 比 $\max\ge i$ 好做。此时：
$$
ans=(N-k+1)V-\sum_{i=1}^{N-k+1}\sum_{x=1}^V [\max(a_i,a_{i+1},\ldots,a_{i+k-1})<x]
$$

---

接下来肯定是拆 $\max$，对于每个 $x$ 考虑，考虑记 $b_i = [a_i \geq x]$。

设 $b$ 中相邻两个 $1$ 的距离分别为 $L_1\sim L_z$，特别的我们钦定 $b_0 = b_{n+1} = 1$。（注意下文 $L$ 均表示 $len$）

那么 $x$ 固定的时候和式就是 $\sum\limits_{i=1}^z \max(L_i - k + 1,0)$​。

维护这东西是经典的，记录 $L_i\le k$ 的个数和此时的 $\sum L_i$，两个树状数组维护即可。

由于只有 $a_k \leftarrow a_k + 1$ 的操作，即使 $\forall x$，每次也仅会改变 $O(1)$ 个 $L$​ 的值，修改是方便的。

---

但是此时有个**十分严重的问题**，你对于所有 $x$，维护初始的 $L$，数量级就至少已经是 $O(n^2)$ 了。

你如果要对值域扫描线降维也不是特别好做。

咋办呢？我们还是观察**支配点对**，合并类似状态。

我们注意到 $b$ 数组中**本质不同**的相邻两个 $1$ 的点对 $(i,j)$ 是 $O(n)$ 级别的。

具体的：对于每个 $a_i$，找到左/右第一个 $>a_i$ 的位置 $l,r$，则只需要考虑所有 $(l,i),(i,r)$ 点对的相邻状态即可。

对于一个点对 $(p,q)$，注意到使得他们为相邻 $1$ 的 $x\in [\min(a_p,a_q),\max(a_{p+1}\sim a_{q-1}))$。

给 $L=r-l+1$ 这个位置贡献 $\max(a_{l+1}\sim a_{r-1})-\min(a_l,a_r)$​ 这么多个即可。

---

修改你就线段树二分找左/右第一个 $\ge a_{k}+1$ 的数，把这个区间贡献删了，在算插入 $k$ 后的 $L$ 的贡献即可。

显然是 $O(1)$ 次的，同时在线段树上也要修改 $a_i\gets a_i+1$，修改后算贡献和初始一样放到树状数组上算。

复杂度 $O((N+Q)\log N)$。

**PS**：支配点对好多都是取和这题一样的 $pre_i$ 和 $suf_i$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define ls w<<1
#define rs w<<1|1
#define lw l,m,ls
#define rw m+1,r,rs
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=5e5+5,V=2e9;
int n,m,a[N],A[N<<2],t,b[N];
struct Bit
{
	LL a[N],b[N];
	inline void add(int w,LL x){
		for(LL y=w*x;w;w&=(w-1)) a[w]+=x,b[w]+=y;
	}
	inline LL ask(int w){
		LL s=0,S=0;
		for(int i=w;i<=n;i+=i&-i) s+=a[i],S+=b[i];
		return S-(w-1)*s;
	}
}B;
void bd(int l=0,int r=n+1,int w=1)
{
	if(l==r) return A[w]=a[l],void();
	int m=(l+r)>>1;bd(lw),bd(rw);
	A[w]=max(A[ls],A[rs]);
}
void upd(int p,int x,int l=0,int r=n+1,int w=1)
{
	if(l==r) return A[w]=x,void();
	int m=(l+r)>>1;p<=m?upd(p,x,lw):upd(p,x,rw);
	A[w]=max(A[ls],A[rs]);
}
int qry(int L,int R,int l=0,int r=n+1,int w=1)
{
	if(L<=l&&r<=R) return A[w];
	int m=(l+r)>>1,s=0;
	if(L<=m) s=max(s,qry(L,R,lw));
	if(m<R) s=max(s,qry(L,R,rw));
	return s;
}
int gl(int p,int x,int l=0,int r=n+1,int w=1)
{
	if(l>p||A[w]<x) return -1;
	if(l==r) return l;int m=(l+r)>>1;
	int t=gl(p,x,rw);return t==-1?gl(p,x,lw):t;
}
int gr(int p,int x,int l=0,int r=n+1,int w=1)
{
	if(r<p||A[w]<x) return -1;
	if(l==r) return l;int m=(l+r)>>1;
	int t=gr(p,x,lw);return t==-1?gr(p,x,rw):t;
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];a[0]=a[n+1]=V;bd();
	b[t=1]=0;
	for(int i=1;i<=n+1;i++)
	{
		auto UPD=[&](){
			int l=b[t]+1,r=i-1;
			if(l<=r) B.add(r-l+1,min(a[l-1],a[r+1])-qry(l,r));
		};
		while(t&&a[i]>=a[b[t]]) UPD(),t--;
		if(t) UPD();b[++t]=i;
	}char op;
	for(int k;m--;)
	{
		cin>>op>>k;
		if(op=='?') cout<<(LL)V*(n-k+1)-B.ask(k)<<'\n';
		else
		{
			a[k]++;int L=gl(k,a[k])+1,R=gr(k,a[k])-1;
			upd(k,a[k]);B.add(R-L+1,-1);
			if(L<=k-1) B.add(k-L,1);
			if(k+1<=R) B.add(R-k,1);
		}
	}
	return 0;
}
```

---

## 作者：gcx12012 (赞：0)

### 前言
和 @dadaaa 讨论了一晚上才意识到这是个简单题。
### Solution
这里给一个线段树二分的做法。

首先把 $\max$ 换成 $\min$，$+$ 换成 $-$，然后初始化把每个 $a_i$ 变成 $mx-a_i$，这里 $mx$ 是一个足够大的数。答案就是 $mx\times (n-k+1)$ 减去连续 1 段对答案的贡献和。

设 $f_{i,j}=[a_i\ge j]$，然后这就变成了一个维护连续 1 段的问题，假设当前查询的长度为 $k$，有一个长度为 $x$ 的段，那么这个段对答案的贡献为 $\max(0,x-k+1)$。

我们考虑用扫描线和并查集来维护初始的答案，并求出每个长度的段的个数，然后每次修改只会断掉一个连续段。这就相当于找到一个最长段 $[l,r]$ 使得其包含 $x$ 且该区间的最小值为 $a_x$，线段树二分维护即可。

时间复杂度是 $O(n\log n)$ 的，常数略大，但是能过。
```
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define ld long double
#define ull unsigned long long
#define lll __int128
#define N 500010
#define For(i,a,b) for(int i=a;i<=b;++i)
#define Rof(i,a,b) for(int i=a;i>=b;--i)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define pque priority_queue
#define fi first
#define se second

using namespace std;
ll a[N],b[N];
ll n,q,mx1;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll cnt[N<<2],sum[N<<2];
void add(int x,int l,int r,int u,ll v){
	if(!u) return;
	if(l==r){
		cnt[x]+=v;
		sum[x]+=v*l;
		return;
	}
	int mid=(l+r)>>1;
	if(u<=mid) add(lson,u,v);
	else add(rson,u,v);
	cnt[x]=cnt[ls]+cnt[rs];
	sum[x]=sum[ls]+sum[rs];
}
ll qry(int x,int l,int r,int L,int R,int op){
	if(L<=l && r<=R) return op==1?cnt[x]:sum[x];
	int mid=(l+r)>>1;
	ll p=0;
	if(L<=mid) p+=qry(lson,L,R,op);
	if(R>mid) p+=qry(rson,L,R,op);
	return p;
}
int f[N],sz[N],lst[N],vis[N];
int gf(int x){
	if(f[x]==x) return x;
	return f[x]=gf(f[x]);
}
void add1(int x,ll now){
	vis[x]=1;
	if(!vis[x-1] && !vis[x+1]) lst[x]=now;
	else if(vis[x-1] && !vis[x+1]){
		add(1,1,n,sz[gf(x-1)],lst[gf(x-1)]-now);
		f[x]=gf(x-1);
		sz[gf(x-1)]+=sz[x];
		lst[gf(x-1)]=now;
	}else if(!vis[x-1] && vis[x+1]){
		add(1,1,n,sz[x+1],lst[x+1]-now);
		f[x+1]=x;
		sz[x]+=sz[x+1];
		lst[x]=now;
	}else{
		add(1,1,n,sz[gf(x-1)],lst[gf(x-1)]-now);
		add(1,1,n,sz[x+1],lst[x+1]-now);
		f[x]=f[x+1]=gf(x-1);
		sz[gf(x-1)]+=sz[x]+sz[x+1];
		lst[gf(x-1)]=now;
	}
}
int mx[N<<2];
void change(int x,int l,int r,int u,int v){
	if(l==r){
		mx[x]=v;
		return;
	}
	int mid=(l+r)>>1;
	if(u<=mid) change(lson,u,v);
	else change(rson,u,v);
	mx[x]=min(mx[ls],mx[rs]);
}
int ef1(int x,int l,int r,int p,ll val){
	if(r<=p && mx[x]>=val) return -1;
	if(l==r) return l;
	int mid=(l+r)>>1,pp=(mid<p?ef1(rson,p,val):-1);
	if(pp!=-1) return pp;
	pp=ef1(lson,p,val);
	return pp;
}
int ef2(int x,int l,int r,int p,ll val){
	if(l>=p && mx[x]>=val) return -1;
	if(l==r) return l;
	int mid=(l+r)>>1,pp=(p<=mid?ef2(lson,p,val):-1);
	if(pp!=-1) return pp;
	pp=ef2(rson,p,val);
	return pp;
}

int main()
{
    //freopen("gcx.in","r",stdin);
    //freopen("gcx.out","w",stdout);
    n=read(),q=read();
    For(i,1,n) a[i]=read(),mx1=max(mx1,a[i]+600000);
    For(i,1,n) a[i]=mx1-a[i],lst[i]=mx1,f[i]=b[i]=i,sz[i]=1;
    sort(b+1,b+n+1,[&](int x,int y){return a[x]>a[y];});
    For(i,1,n) add1(b[i],a[b[i]]);
    fill(vis+1,vis+n+1,0);
    For(i,1,n) if(!vis[gf(i)]) add(1,1,n,sz[gf(i)],lst[gf(i)]),vis[gf(i)]=1;
    //For(i,1,n) cout<<qry(1,1,n,i,i,1)<<' ';
    a[0]=a[n+1]=-2e8;
    For(i,0,n+1) change(1,0,n+1,i,a[i]);
    while(q--){
    	char c;
    	cin>>c;
    	ll x=read();
    	if(c=='?'){
    		ll ans=qry(1,1,n,x,n,2)-qry(1,1,n,x,n,1)*(x-1);
    		cout<<(n-x+1)*mx1-ans<<endl;
    	}else{
    		int l=ef1(1,0,n+1,x,a[x]),r=ef2(1,0,n+1,x,a[x]);
    		l++,r--;
    		//cout<<l<<' '<<r<<endl;
    		add(1,1,n,r-l+1,-1);
    		add(1,1,n,x-l,1);
    		add(1,1,n,r-x,1);
    		a[x]--;
    		change(1,0,n+1,x,a[x]);
    	}
    }
   	return 0;
}
/*

*/
```

---

