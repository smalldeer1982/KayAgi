# 「RdOI R3」闹钟

## 题目描述

你有一个闹钟，闹钟的定时可以用两个变量 $a_1,a_2$ 表示，变量的初始值皆为 $0$。把一个变量从 $x$ 调整至 $y$ 需要 $|x-y|$ 的代价。

接下来给出 $n$ 个数 $k_1,k_2,\cdots,k_n$。对于第 $i$ 天，你都需要通过调整变量的值，使得两个变量中**至少**有一个等于 $k_i$。求最小代价。

## 说明/提示

### 样例解释

样例解释一：  
第一天：$a=\{1,0\}$。  
第二天：$a=\{1,0\}$。  
第三天：$a=\{4,0\}$。  
第四天：$a=\{5,0\}$。  
第五天：$a=\{5,1\}$。  
第六天：$a=\{4,1\}$。  

样例解释二：  
第一天：$a=\{4,0\}$。  
第二天：$a=\{4,1\}$。  
第三天：$a=\{9,1\}$。  
第四天：$a=\{9,2\}$。  
第五天：$a=\{9,3\}$。 

---

### 数据范围

|数据编号|$n\le$|特殊性质|
|:-:|:-:|:-:|
|$1$|$10$|无|
|$2$|$10^3$|$k_i\le100$|
|$3\sim4$|$10^3$|无|
|$5\sim7$|$10^5$|$k_i\le100$|
|$8\sim10$|$10^5$|无|

另外，为了卡掉一些错误做法，本题添加了若干 hack 测试点。hack 测试点的数据满足 $n\le10$ 且 $k_i\le 100$。若你的程序没有通过至少一个 hack 测试点，则此题分数记为 $0$ 分。

对于 $100\%$ 的数据，$1\le n\le10^5,1\le k_i\le10^9$。

## 样例 #1

### 输入

```
6
1 1 4 5 1 4```

### 输出

```
7```

## 样例 #2

### 输入

```
5
4 1 9 2 3```

### 输出

```
12```

# 题解

## 作者：BobL (赞：4)

# P7823题解
这道题还是一个比较好的线段树优化题，思维过程还是很流畅的（只是有点难调）。

## $n^{\smash{3}}$ 做法
令 $f_{i,j,t}$ 为前 $t$ 个时间点，$a_1$ 取 $k_i$ ，$a_2$ 取  $k_j$ 的最小代价，暴力转移即可。

## $n^{\smash{2}}$ 做法
发现当前一种做法在时间点为$t$时，$a_1,a_2$中必有一个取到$k_t$，且两者之间不区分。故而可以压缩掉一维。

令 $f_{i,j}$ 为时间点 $i$ ,其中一个 $a$ 取 $k_i$ ，另一个 $a$ 取 $k_j$ 的最小代价，转移方程：

$f[i][j]=f[i-1][j]+ \lvert k[i]-k[i-1]\rvert \text{ if }(0\leq j\leq i-2)$

需要注意的是，$j=i-1$ 的情况下，$f_{i,j}$ 可能由前面每一个 $f_{i-1,j'}$ 得到（等价于位于 $i-1$ 的 $a$ 不动，位于 $j'$ 的动
），此时转移方程变为：

$f[i][i-1]=\ \min \lbrace f[i-1][j']+ \lvert k[i]-k[j']\rvert \rbrace   \text{ } (0 \leq j'\leq i-2)$

代码：
```cpp
void bf(){
	memset(f,0x3f,sizeof(f));
	ans = 0x3fffffffffffffff;
	f[0][0]=0;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < i; j++){
			f[i][j]=min(f[i][j],f[i-1][j]+abs(a[i]-a[i-1]));
			f[i][i-1]=min(f[i][i-1],f[i-1][j]+abs(a[i]-a[j])); 
		}
	}
	for(int i = 0; i <= n; i++)ans = min(ans,f[n][i]);
	cout << ans;
}
```
## $n\log n$ 做法
注意到转移式一为区间加法，自然想到可以用线段树维护这一段的数据。每次操作到一个数是将值加上即可。

而对于第二个式子，因为在已经做完前 $i$ 个数之后，只存在 $i$ 个状态，对于第 $i+1$ 个数，我们只需要求出这个式子的值，将其作为一个新的点 $i+1$ 插入到线段树中就可以了。

然而，只是单纯的区间最小值用普通线段树可以维护，但式子带可变的绝对值难以用普通的线段树维护。我们需要找到一种方法以去除绝对值。

因此，自然想到可以将每一个 $k_i$ 排序后建树维护。令 $rk_i$ 为其排序后从小到大的排名，则对于比其排名小的部分，绝对值变成了$k_i-k_j$,对于排名比其大的位置，绝对值变成了 $k_j-k_i$ 。而对于一个点来说，$k_i,-k_i$ 不会改变。对于每个点我们可以将这一部分的权值先计算出来。具体的，我们维护三个权值：$val_i  ,lval_i=val_i-k_i,rval_i=val_i+k_i$ 分别代表其初始权值，排名小的时候的权值，排名大的时候的权值。这样操作到第$i$个数时，根据绝对值计算其排名左边区间的最小值$\ \min\lbrace val_j+k_i-k_j=lval_j+k_i\rbrace$ ，右边区间的最小值$\ \min\lbrace val_j+k_j-k_i=rval_j+k_i\rbrace $，两者再取最小值就可以得到这个点的权值了。最后将这个点插入就行了。

实现方面，线段树只需要实现区间加法（这部分可以直接将权值加到根节点的标记上），单点修改，查询区间 $lval,rval$ 的最值就行了。这部分都是$\log n$ 的。

代码见下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long f[1005][1005],a[1000005],rnk[1000005],ans;
struct mai{
	long long val;
	int id;
}b[1000005];
bool cmp(mai a, mai b){
	return a.val == b.val ? a.id < b.id : a.val < b.val;
}
long long inf = 0x33ffffffffffffff;
void bf(){
	memset(f,0x3f,sizeof(f));
	ans = 0x3fffffffffffffff;
	f[0][0]=0;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < i; j++){
			f[i][j]=f[i-1][j]+abs(a[i]-a[i-1]);
			f[i][i-1]=min(f[i][i-1],f[i-1][j]+abs(a[i]-a[j])); 
		}
	}
	for(int i = 0; i <= n; i++)ans = min(ans,f[n][i]);
	cout << ans;
}

int ls(int x){
	return (x << 1);
}

int rs(int x){
	return ((x << 1)|1);
}

struct seg{
	long long lval,rval,lazy,ans;
}t[5000005];
int tot;

void push_up(int x){
	t[x].lval = min(t[ls(x)].lval,t[rs(x)].lval);
	t[x].rval = min(t[ls(x)].rval,t[rs(x)].rval);
	t[x].ans = min(t[ls(x)].ans,t[rs(x)].ans);
}

void push_down(int x){
	if(t[x].lazy){
		t[ls(x)].ans+=t[x].lazy;
		t[rs(x)].ans+=t[x].lazy;
		t[ls(x)].lazy+=t[x].lazy;
		t[ls(x)].lval+=t[x].lazy;
		t[ls(x)].rval+=t[x].lazy;
		t[rs(x)].lazy+=t[x].lazy;
		t[rs(x)].lval+=t[x].lazy;
		t[rs(x)].rval+=t[x].lazy;
		t[x].lazy=0;
	}
}

void build(int l, int r, int x){
	if(l==r){
		t[x].lval = t[x].rval = t[x].ans = inf;
		return;
	}
	int mid = (l+r)>>1;
	build(l,mid,ls(x));
	build(mid+1,r,rs(x));
	push_up(x);
}

void insert(int x, int pos, int id, long long val, int l, int r){
	if(l == r){
		t[x].lazy = 0;
		t[x].lval = val-a[id];
		t[x].rval = val+a[id];
		t[x].ans = val;
		return;
	}
	push_down(x);
	int mid = (l+r)>>1;
	if(pos <= mid) insert(ls(x),pos,id,val,l,mid);
	else insert(rs(x),pos,id,val,mid+1,r);
	push_up(x);
}

long long askl(int x, int ql, int qr, int l, int r){
	if(qr < ql)return inf;
	if(ql <= l && r <= qr){
		return t[x].lval;
	}
	int mid = (l+r)>>1;
	long long ret = inf;
	push_down(x);
	if(ql <= mid)ret = min(ret,askl(ls(x),ql,qr,l,mid));
	if(qr > mid )ret = min(ret,askl(rs(x),ql,qr,mid+1,r));
	push_up(x);
	return ret;
}

long long askr(int x, int ql, int qr, int l, int r){
	if(qr < ql)return inf;
	if(ql <= l && r <= qr){
		return t[x].rval;
	}
	int mid = (l+r)>>1;
	long long ret = inf;
	push_down(x);
	if(ql <= mid)ret = min(ret,askr(ls(x),ql,qr,l,mid));
	if(qr > mid )ret = min(ret,askr(rs(x),ql,qr,mid+1,r));
	push_up(x);
	return ret;
}

void sol(){
	for(int i = 1; i <= n; i++) b[i].val=a[i],b[i].id = i;
	sort(b+1,b+1+n,cmp);
	for(int i = 1; i <= n; i++)rnk[b[i].id]=i;
	build(0,n,1);
	insert(1,0,0,0,0,n);
	for(int i = 1; i <= n; i++){
		int rk = rnk[i];
		long long val = min(askl(1,0,rk-1,0,n)+a[i],askr(1,rk+1,n,0,n)-a[i]);
		t[1].lazy += abs(a[i]-a[i-1]);
		t[1].ans += abs(a[i]-a[i-1]);
		t[1].lval += abs(a[i]-a[i-1]);
		t[1].rval += abs(a[i]-a[i-1]);
		insert(1,rnk[i-1],i-1,val,0,n);
		
	}
	cout << t[1].ans;
}

int main(){
	freopen("P7823.in","r",stdin);
	freopen("P7823.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)scanf("%lld",&a[i]);
	sol();
	return 0;
}
```


---

## 作者：enucai (赞：3)

## Analysis

非常朴素的线段树优化 dp。

令 $f_{i,j}$ 表示处理完前 $i$ 个任务，不处理上一个任务的闹钟的时间是 $j$ 的最少代价。

转移分为两部分：用上一次做任务的闹钟完成这一次任务，或用上一次不做任务的闹钟完成这一次任务。则有 dp 方程：

$$f_{i,j}=f_{i-1,j}+|k_i-k_{i-1}|$$

这表示用上一次做任务的闹钟直接做这一次任务，代价是 $|k_i-k_{i-1}|$。

$$f_{i,k_{i-1}}=\min_{j} f_{i-1,j}+|k_i-j|$$

这表示用上一次没有做任务的闹钟完成这一次任务，枚举那个闹钟之前的时间，取 $\min$ 转移即可。

考虑将第二位用线段树维护，那么第一个转移就是线段树上的全局加法，第二个操作则是单点修改。考虑查询，将第二个 dp 方程的绝对值打开，得到两部分：$f_{i-1,j}-j+k$ 与 $f_{i-1,j}+j-k$。在线段树上分别维护每个位置的 dp 值 $\pm$ 位置的最小值即可。由于坐标范围较大，需要离散化。复杂度 $O(n\log n)$。

## Code

人傻代码丑，将就看看吧。

```cpp
#define int long long
const int N=100010;
int n,a[N],pos[N];
struct node{
  int amn,smn,lz;
  friend node operator+(node x,node y){
    node res; res.lz=0;
    res.amn=min(x.amn,y.amn);
    res.smn=min(x.smn,y.smn);
    return res;
  }
}t[N<<2];
#define mid ((l+r)>>1)
void down(int c,int l,int r){
  if(!t[c].lz) return;
  t[c<<1].amn+=t[c].lz,t[c<<1|1].amn+=t[c].lz;
  t[c<<1].smn+=t[c].lz,t[c<<1|1].smn+=t[c].lz;
  t[c<<1].lz+=t[c].lz,t[c<<1|1].lz+=t[c].lz;
  t[c].lz=0;
}
void add(int c,int l,int r,int x,int y,int v){
  if(l==x&&r==y){
    t[c].amn+=v,t[c].smn+=v,t[c].lz+=v;
    return;
  }
  down(c,l,r);
  if(y<=mid) add(c<<1,l,mid,x,y,v);
  else if(x>mid) add(c<<1|1,mid+1,r,x,y,v);
  else add(c<<1,l,mid,x,mid,v),add(c<<1|1,mid+1,r,mid+1,y,v);
  t[c]=t[c<<1]+t[c<<1|1];
}
void upd(int c,int l,int r,int x,int v){
  if(l==r){
    t[c].amn=min(t[c].amn,v+pos[l]);
    t[c].smn=min(t[c].smn,v-pos[l]);
    return;
  }
  down(c,l,r);
  if(x<=mid) upd(c<<1,l,mid,x,v);
  else upd(c<<1|1,mid+1,r,x,v);
  t[c]=t[c<<1]+t[c<<1|1];
}
node qry(int c,int l,int r,int x,int y){
  if(l==x&&r==y) return t[c];
  down(c,l,r);
  if(y<=mid) return qry(c<<1,l,mid,x,y);
  else if(x>mid) return qry(c<<1|1,mid+1,r,x,y);
  else return qry(c<<1,l,mid,x,mid)+qry(c<<1|1,mid+1,r,mid+1,y);
}
int solve(int c,int l,int r){
  if(l==r) return t[c].smn+pos[l];
  down(c,l,r);
  return min(solve(c<<1,l,mid),solve(c<<1|1,mid+1,r));
}
signed main(){IOS;
  cin>>n;
  rep(i,1,n) cin>>a[i],pos[i]=a[i];
  sort(pos+1,pos+n+1);
  rep(i,1,n) a[i]=lower_bound(pos+1,pos+n+1,a[i])-pos;
  rep(i,1,4*n+4) t[i]={(int)1e16,(int)1e16,0};
  upd(1,0,n,0,0);
  rep(i,1,n){
    int smn=qry(1,0,n,0,a[i]).smn,amn=qry(1,0,n,a[i],n).amn;
    add(1,0,n,0,n,llabs(pos[a[i]]-pos[a[i-1]]));
    upd(1,0,n,a[i-1],min(pos[a[i]]+smn,amn-pos[a[i]]));
  }
  cout<<solve(1,0,n);
}
```

---

## 作者：ykzzldz (赞：2)

由于一共只有两个变量，而在第 $i$ 天，一定有一个变量的值为 $k_i$，所以可以简单地列出 $f_{i,j}$ 表示第 $i$ 天，另一个变量的值为 $j$ 的答案。

转移的话，分两类讨论：

1. 第 $i$ 天与第 $i-1$ 天用同一个变量：$f_{i,j}=f_{i-1,j}+|k_i-k_{i-1}|$，此时另一个变量 $j$ 不动是最优的。

2. 第 $i$ 天不与第 $i-1$ 天用同一个变量：$f_{i,k_{i-1}}=\min (f_{i,k_{i-1}},f_{i-1,j}+|j-k_i|)$，这说明另一个变量一定在 $k_{i-1}$ 的位置，而上一次的位置是任意选的。

第二种转移可以套路地使用线段树维护，考虑到值域较大，所以需要离散化。线段树的下标即为 $f$ 数组第二维，第一维可以滚动数组优化掉，复杂度为 $O(n\log n)$。

---

## 作者：xiezheyuan (赞：2)

## 简要题意

有两个变量 $x,y$，初始时有 $x=y=0$。

每个时刻开始时你可以进行一次调整，一次调整可令一个变量增加或减少任意一个值，花费等量代价。

有 $n$ 个时刻，每个时刻有一个整数 $k_i$，表示这个时刻结束时需要有至少一个变量等于 $k_i$。

求花费的最小的代价和。

$1\leq n\leq 10^5,1\leq k_i\leq 10^9$。

## 思路

设 $f(i,j)$ 表示在第 $i$ 个时刻，两个变量的值为 $k_i,j$ 的最小代价。

则不难有两种转移：

$$
f(i,j)=\begin{cases}
f(i-1,j)+|k_i-k_{i-1}|& j\neq k_{i-1}\\
\min\limits_{t=0}^{+\infty} f(i-1,t)+|k_i-t|& j=k_{i-1}
\end{cases}
$$

简单解释一下转移的含义。第一种转移是让以前为 $k_{i-1}$ 的变量的值变成 $k_i$，而第二种转移是让以前不为 $k_{i-1}$ 的变量（或者两者均为 $k_{i-1}$ 的情况下其中的一个变量）的值变为 $k_i$。

我们发现第二种情况下，$j$ 的取值一定在 $k$ 中更优秀（我们不会无缘无故将 $j$ 变成一个毫不相干的数），我们将 $k$ 离散化作为 $j$ 这一维下标，这样可以做到 $O(n^2)$。难以通过本题，我们需要优化。

不难发现除了 $j=k_{i-1}$ 的位置外，其余的位置都是增加了一个定值 $|k_i-k_{i-1}|$。

而对于 $j=k_{i-1}$ 的情况，则是每个位置加上一个绝对值之后求全局最小值。

考虑绝对值我们应当怎么处理。可以将满足 $t\leq k_{i-1}$ 的所有位置加上 $k_i$ 减去 $t$。$t>k_{i-1}$ 同理。

加上 $k_{i-1}$ 相对好处理，不过减去 $t$ 就有难度。我们可以维护 $f'(i,j)=f(i,j)-j,f''(i,j)=f(i,j)+j$，这样子求最小值的时候可以拆成两个部分求最小值。

现在，我们需要找一个数据结构来维护 dp，需要支持区间加区间查询最小值，线段树可以胜任。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int N = 1e5 + 5, inf = 1e18;
int n, a[N], b[N], trs[N], rev[N];

struct sgt{
    int t[N << 2], tag[N << 2];
    void build(int i, int l, int r){
        if(l == r) return t[i] = ((l == 1) ? 0 : inf), void();
        build(ls, l, mid);
        build(rs, mid+1, r);
        t[i] = min(t[ls], t[rs]);
    }
    void mktag(int i, int v){ t[i] += v, tag[i] += v; }
    void pushdown(int i){ mktag(ls, tag[i]), mktag(rs, tag[i]), tag[i] = 0; }
    void update(int ql, int qr, int v, int i, int l, int r){
        if(ql <= l && r <= qr) return mktag(i, v);
        pushdown(i);
        if(ql <= mid) update(ql, qr, v, ls, l, mid);
        if(mid < qr) update(ql, qr, v, rs, mid+1, r);
        t[i] = min(t[ls], t[rs]);
    }
    int query(int ql, int qr, int i, int l, int r){
        if(ql > qr) return inf;
        if(ql <= l && r <= qr) return t[i];
        pushdown(i);
        int res = inf;
        if(ql <= mid) res = min(res, query(ql, qr, ls, l, mid));
        if(mid < qr) res = min(res, query(ql, qr, rs, mid+1, r));
        return res;
    }
    void assign(int p, int v, int i, int l, int r){
        if(l == r) return t[i] = v, void();
        pushdown(i);
        if(p <= mid) assign(p, v, ls, l, mid);
        else assign(p, v, rs, mid+1, r);
        t[i] = min(t[ls], t[rs]);
    }
} t, tp, tn;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i], b[i] = a[i];
    int tot = n; b[++tot] = 0;
    sort(b+1, b+tot+1);
    tot = unique(b+1, b+n+1) - b;
    for(int i=1;i<=n;i++){
        trs[i] = lower_bound(b+1, b+tot+1, a[i]) - b;
        rev[trs[i]] = i;
    }
    // cerr << tot << '\n';
    // for(int i=1;i<=tot;i++) cerr << a[rev[i]] << ' ';
    // cerr << '\n';
    trs[0] = 1, rev[1] = 0;
    t.build(1, 1, tot);
    tp.build(1, 1, tot);
    tn.build(1, 1, tot);
    for(int i=1;i<=n;i++){
        int rt = min(tn.query(1, trs[i], 1, 1, tot) + a[i], tp.query(trs[i] + 1, tot, 1, 1, tot) - a[i]);
        t.update(1, tot, abs(a[i] - a[i - 1]), 1, 1, tot);
        tp.update(1, tot, abs(a[i] - a[i - 1]), 1, 1, tot);
        tn.update(1, tot, abs(a[i] - a[i - 1]), 1, 1, tot);
        t.assign(trs[i - 1], rt, 1, 1, tot);
        tp.assign(trs[i - 1], a[i - 1] + rt, 1, 1, tot);
        tn.assign(trs[i - 1], -a[i - 1] + rt, 1, 1, tot);
        // for(int j=1;j<=tot;j++) cerr << t.query(j, j, 1, 1, tot) << ' ';
        // cerr << '\n';
    }
    cout << t.query(1, tot, 1, 1, tot) << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：lkjlkjlkj2012 (赞：0)

### 思路
首先我们可以设 $f_{i,j,k}$ 表示第 $i$ 天，两个变量分别为 $j,k$ 时的最小代价。由于此时一定有一个变量等于 $a_i$，所以可以去掉一维。
此时的转移为：

1. $f_{i-1,j}+|a_i-a_{i-1}| \to f_{i,j}$
2. $f_{i-1,j}+|j-a_{i-1}| \to f_{i,a_{i-1}}$

注意到第一个转移是区间加，第二个则是单点更新，可以用线段树维护第二维。由于 $a_i,a_{i-1}$ 在转移时都已知，所以线段树只需维护 $\min(f_{i,j}+j)$ 和 $\min(f_{i,j}-j)$ 即可。又由于 $j$ 显然只能是 $0$ 或 $a_k$，所以可以离散化 $a$，减小常数（听说动态开点很难通过）。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100005],b[100005];
struct Tree
{
    int a,b,f;
}t[400005];
Tree operator + (Tree a,Tree b)
{
    Tree c;
    c.f=0;
    c.a=min(a.a,b.a);
    c.b=min(a.b,b.b);
    return c;
}
void down(int x,int l,int r)
{
    t[x*2].a+=t[x].f;
    t[x*2+1].a+=t[x].f;
    t[x*2].b+=t[x].f;
    t[x*2+1].b+=t[x].f;
    t[x*2].f+=t[x].f;
    t[x*2+1].f+=t[x].f;
    t[x].f=0;
}
void modifya(int x,int l,int r,int ml,int mr,int k)
{
    if(ml<=l&&r<=mr)
    {
        t[x].a+=k;
        t[x].b+=k;
        t[x].f+=k;
        return;
    }
    int mid=(l+r)/2;
    down(x,l,r);
    if(ml<=mid)
        modifya(x*2,l,mid,ml,mr,k);
    if(mr>mid)
        modifya(x*2+1,mid+1,r,ml,mr,k);
    t[x]=t[x*2]+t[x*2+1];
}
void modifym(int x,int l,int r,int p,int k)
{
    if(l==r)
    {
        t[x].a=min(t[x].a,k+b[l]);
        t[x].b=min(t[x].b,k-b[l]);
        return;
    }
    int mid=(l+r)/2;
    down(x,l,r);
    if(p<=mid)
        modifym(x*2,l,mid,p,k);
    else
        modifym(x*2+1,mid+1,r,p,k);
    t[x]=t[x*2]+t[x*2+1];
}
Tree query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)
        return t[x];
    int mid=(l+r)/2;
    Tree ans={(int)1e16,(int)1e16,0};
    down(x,l,r);
    if(ql<=mid)
        ans=ans+query(x*2,l,mid,ql,qr);
    if(qr>mid)
        ans=ans+query(x*2+1,mid+1,r,ql,qr);
    return ans;
}
int getans(int x,int l,int r)
{
    if(l==r)
        return t[x].b+b[l];
    int mid=(l+r)/2;
    down(x,l,r);
    return min(getans(x*2,l,mid),getans(x*2+1,mid+1,r));
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i],b[i]=a[i];
    sort(b+1,b+n+1);
    int m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+m+1,a[i])-b;
    for(int i=1;i<=4*n+4;i++)
        t[i]={(int)1e16,(int)1e16,0};
    modifym(1,0,n,0,0);
    for(int i=1;i<=n;i++)
    {
        int bmn=query(1,0,n,0,a[i]).b;
        int amn=query(1,0,n,a[i],n).a;
        modifya(1,0,n,0,n,llabs(b[a[i]]-b[a[i-1]]));
        modifym(1,0,n,a[i-1],min(b[a[i]]+bmn,amn-b[a[i]]));
    }
    cout<<getans(1,0,n);
}
```

---

