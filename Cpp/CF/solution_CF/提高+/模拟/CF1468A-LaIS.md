# LaIS

## 题目描述

Let's call a sequence $ b_1, b_2, b_3 \dots, b_{k - 1}, b_k $ almost increasing if $ \min(b_1, b_2) \le \min(b_2, b_3) \le \dots \le \min(b_{k - 1}, b_k).  $  In particular, any sequence with no more than two elements is almost increasing.</p><p>You are given a sequence of integers  $ a\_1, a\_2, \\dots, a\_n $ . Calculate the length of its longest almost increasing subsequence.</p><p>You'll be given  $ t$$$ test cases. Solve each test case independently.

Reminder: a subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

## 说明/提示

In the first test case, one of the optimal answers is subsequence $ 1, 2, 7, 2, 2, 3 $ .

In the second and third test cases, the whole sequence $ a $ is already almost increasing.

## 样例 #1

### 输入

```
3
8
1 2 7 3 2 1 2 3
2
2 1
7
4 1 5 2 6 3 7```

### 输出

```
6
2
7```

# 题解

## 作者：james1BadCreeper (赞：4)

不难发现其大致的形态应该是最长不降子序列，但是在 $a_{i-1},a_i$ 中我们可以插入一个 $a_k\ge a_i$，也就是说，设 $f_i$ 代表以 $i$ 结尾的最长子序列，那么：

$$
f_i=\max\left\{f_j+\left[\max_{k=j+1}^{i-1} a_k\ge a_i\right]\right\}+1,j<i,a_j\le a_i
$$

由于附加的答案最多只有 $1$，我们只需要看最大的 $f_j$ 是否能够变大即可。值域线段树上维护最小的 $j$ 的位置，然后艾弗森括号中的内容用 ST 表判断即可。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n; 
int a[500005], f[500005]; 
int g[19][500005]; 

inline int gmax(int l, int r) {
    if (l > r) return 0; 
    int k = __lg(r - l + 1); 
    return max(g[k][l], g[k][r - (1 << k) + 1]); 
}

int T[2000005]; 
inline void upd(int &x, int k) {
    if (f[x] < f[k] || (f[x] == f[k] && k < x)) x = k; 
}
void build(int o, int l, int r) {
    T[o] = 0; if (l == r) return; 
    int mid = l + r >> 1; 
    build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); 
}
void update(int o, int l, int r, int x, int k) {
    if (l == r) return upd(T[o], k), void(); 
    int mid = l + r >> 1; 
    if (x <= mid) update(o << 1, l, mid, x, k); 
    else update(o << 1 | 1, mid + 1, r, x, k); 
    T[o] = T[o << 1]; upd(T[o], T[o << 1 | 1]); 
}
int query(int o, int l, int r, int x, int y) {
    if (x <= l && r <= y) return T[o]; 
    int mid = l + r >> 1, res = 0; 
    if (x <= mid) res = query(o << 1, l, mid, x, y); 
    if (mid < y) upd(res, query(o << 1 | 1, mid + 1, r, x, y)); 
    return res; 
}

void solve(void) {
    cin >> n; build(1, 1, n); 
    for (int i = 1; i <= n; ++i) cin >> a[i], g[0][i] = a[i]; 
    for (int i = 1; i <= 18; ++i) for (int j = 1; j + (1 << i) - 1 <= n; ++j) g[i][j] = max(g[i - 1][j], g[i - 1][j + (1 << i - 1)]); 
    int ans = 1; 
    for (int i = 1; i <= n; ++i) {
        int j = query(1, 1, n, 1, a[i]); 
        f[i] = f[j] + 1; 
        if (gmax(j + 1, i - 1) >= a[i]) ++f[i]; 
        ans = max(ans, f[i]); 
        update(1, 1, n, a[i], i); 
    }
    cout << ans << "\n"; 
}

int main(void) {
    ios::sync_with_stdio(0); 
    int T; cin >> T; 
    while (T--) solve(); 
    return 0; 
}
```

---

## 作者：bellmanford (赞：4)

来一个简单好想的做法。

先考虑满足题目所给的性质的序列还满足什么性质。

发现满足这样性质的序列一定可以从中找到一个非严格单调递增的子序列且子序列中相邻的数在原序列中距离不超过 $1$ ，中间的数大于左边的数。

那么考虑在给出的序列中找到一个非严格单调递增的序列再在相邻数中间插入其他数，显然这个插入的数不能小于被插入的两个数中的前一个的上一个数。

如果要考虑 $dp$ 求解就不得不维护上一个的数值，这样显然不可行，再看看第三段，发现根本无需维护上一个的数值，那么考虑 $dp_i$ 为以第 $i$ 个数为结尾的满足题目要求的序列的最长长度，且第 $i$ 个数是这个序列找出的非严格单调递增的子序列的最后一个。

那么有

$$dp_i=max\{dp_j+[MAX(j+1,i)\ge a_j]\}+1\ (1\le j<i\ ,\ a_j\le a_i)$$ 

其中 $MAX(l,r)$ 代表 $l$ 到 $r$ 之间的最大值。

显然这个 $dp$ 可以用 DS 来维护，由于左端点固定右端点增大的区间的最大值是递增的，考虑使用一个均摊线段树来维护 $[MAX(j+1,i)\ge a_j]$ ，剩下的取前缀 $max$ 可以用一个值域树状数组来维护，总效率为 $\mathcal{O(n\log n)}$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=5e5+5;
 
int read(){
    int x=0,y=1;char ch=getchar();
    while(ch<'0'||ch>'9') y=(ch=='-'?-1:1),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*y;
}
 
int n,w[M],dp[M],tr[M],minn[M<<2];
int lowbit(int x){ return x&(-x); }
void Add(int x,int y){ for(;x<=n;x+=lowbit(x)) tr[x]=max(tr[x],y); }
int Max(int x){ int res=0;for(;x;x-=lowbit(x)) res=max(res,tr[x]);return res; }
void pushup(int u){ minn[u]=min(minn[u<<1],minn[u<<1|1]); }
void Build(int u,int l,int r){
	if(l==r) return (void)(minn[u]=w[l]);
	int mid=(l+r)>>1;
	Build(u<<1,l,mid),Build(u<<1|1,mid+1,r);
	pushup(u);
}
void Change(int u,int l,int r,int L,int R,int x){
	if(minn[u]>=x||l>R||r<L) return ;
	if(l==r) return (void)(minn[u]=1e9,Add(w[l],dp[l]+1));
	int mid=(l+r)>>1;
	Change(u<<1,l,mid,L,R,x),Change(u<<1|1,mid+1,r,L,R,x);
	pushup(u);
}
void solve(){
    n=read();int Ans=1;dp[0]=w[0]=0;
    for(int i=1;i<=n;i++) w[i]=read(),tr[i]=0;
    Build(1,1,n);
    for(int i=1;i<=n;i++){
    	dp[i]=(i==1?1:2);
        dp[i]=max(dp[i],Max(w[i])+1);
        Add(w[i],dp[i]);
        Change(1,1,n,1,i,w[i]);
        Ans=max(Ans,dp[i]);//根据dp式可以发现最后答案的序列的最后一个一定是非严格单调递增子序列的最后一个 
    }
    printf("%d\n",Ans);
}
 
signed main(){
    int T=read();
    while(T--) solve();
}
```


---

## 作者：SunsetGlow95 (赞：2)

# 题解 - CF1468A LaIS

另一个好想好写的做法，看题解区还没有就来一发。

## 简述题意

给定数列 $a_1,\ldots,a_n$，要求找到最长的子序列 $b_1,\ldots,b_m(m\ge 2)$ 满足 $\forall 1\le k\le m-2,\min(b_k,b_{k+1})\le \min(b_{k+1},b_{k+2})$。$1\le a_i\le n$，$\sum n\le 5\times 10^5$。

## 分析

经典思路是考虑动态规划，令 $f_i$ 为以第 $i$ 位为结尾的最大合法子序列长度。

假设 $i$ 的前驱是 $j$：

- $a_j\le a_i$ 则总是满足条件，直接用 $f_j+1$ 向 $f_i$ 贡献，从左往右扫的时候实时维护前缀 $\max$。
- $a_j > a_i$：令 $j$ 的前驱为 $k$，则 $\min(a_k, a_j)\le \min(a_j, a_i)$，即 $a_k\le a_i$。那就让 $j$ 越靠右越优。用单调栈找到每个 $i$ 对应的最靠右的 $j$ 满足 $a_j>a_i$，在 $j$ 处查询前缀 $\max$ 即可。

这里的前缀 $\max$ 就是：维护 $g_i$ 为以 $i$ 的值为结尾的最大 $f$ 值，这里的转移就是 $g$ 数组的前缀求 $\max$。不减地单点修改，求前缀 $\max$，可以用树状数组实现。时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

## 代码

实现时重复计入了 $a_j=a_i$ 的贡献，显然没关系。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 500005;
int T, N, arr[MXN], stk[MXN], top, val1[MXN], mxv[MXN], ans;
vector<int> task[MXN];

int query(int p) {
  int v(0);
  while (p) v = max(v, mxv[p]), p -= p & -p;
  return v;
}
void setv(int p, int v) {
  while (p <= N) mxv[p] = max(mxv[p], v), p += p & -p;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> N;
    top = -1;
    for (int i(0); i != N; ++i) {
      cin >> arr[i];
      task[i].clear();
      val1[i] = 0;
      while (~top && arr[stk[top]] < arr[i]) --top;
      if (~top) task[stk[top]].push_back(i);
      stk[++top] = i;
    }
    for (int i(1); i <= N; ++i) mxv[i] = 0;
    ans = 0;
    for (int i(0); i != N; ++i) {
      ans = max(ans, val1[i] = max(val1[i], query(arr[i]) + 1));
      for (int j : task[i]) {
        val1[j] = max(val1[j], query(arr[j]) + 2);
      }
      setv(arr[i], val1[i]);
    }
    cout << ans << endl;
  }
  return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1468A)    
一道经典的线段树优化 dp。       
看到题解里没有我这种做法，就来写题解了。    
## 解法
我们读完题，不难给出一个 dp 式：   
设 $f_i$ 为以 $a_i$ 结束的最长 LaIS，那么有 $f_i=\max\limits^{i-1}_{j=1}[a_j\le a_i](f_j+1+\operatorname{query}(j+1,i-1))$。    
其中，$\operatorname{query}(l,r)$ 表示在 $l$ 到 $r$ 中，是否存在一个 $k$，使得 $a_k\ge a_{r+1}\land a_k\ge a_{l-1}$。    
答案显然为 $\max\limits^n_{i=1}f_i$。    
根据转移式，发现其复杂度为 $O(n^2)$。如何优化呢？   
我们先来看 $\operatorname{query}$ 函数。    
$\operatorname{query}$ 函数里有两个不等式的关系，其中的 $r+1$ 显然就是 $i$，而 $l-1$ 显然就是 $j$。    
又不难发现，这两个不等式的取值范围中，$a_i$ 的被 $a_j$ 的所包含。     
那么 $a_i$ 到 $a_j$ 这一段是什么呢？显然是介于 $a_i$ 和 $a_j$ 之间的数。根据原来的转移式，我们只需要保留 $a_k\ge a_j$ 即可。   
那么，我们就要开始优化了。   
先来考虑一个简单的问题：   
如果说，我们在原式中去除 $\operatorname{query}$ 的答案贡献，那么怎么做呢？   
显然，我们只需要建立一颗线段树维护最大值，每次取左边区间的最大值再加一得到 $f_i$，再以 $a_i$ 为下标以 $f_i$ 为值往里插入即可。    
加入了 $\operatorname{query}$ 也同理，我们预处理出一个 $g$，其中 $g_i$ 表示在 $i$ 以后的第一个大于等于其的数的位置，显然可以用单调栈或 st 表二分求解。   
那么，我们修改一下取最大值，修改成取下标最靠前的一个最大值即可，这里可以写一个 merge 函数来维护结点。   
求出了这些内容，再将下标和 $g_i$ 进行判断即可。     
时间复杂度 $O(n\log n)$。    
[CODE](https://www.luogu.com.cn/paste/4a3fzg5q)

---

## 作者：wangzeqin2008 (赞：0)

# 题面

给长度为 $n$ 的序列 $a_{1\sim n}$，求子序列 $b_{1\sim k}$，满足 $\min(b_{i-1},b_i)\le\min(b_i,b_{i+1})$ 的 $k$ 的最大值。 


$n\le  5\times 10^5$ 

# solution

从这个子序列最终形态入手。

手搓之后可以发现，大致是连续不降 $(j<i,a_j\le a_i)$；但可以出现两个中间插入一个峰值的情况，即 $j<k<i,a_k>a_i\ge a_j$。

设 $f_i$ 表示最后一个数是 $i$ 的最长子序列长度。    
枚举上一个 $\le a_i$ 的数为 $a_j$。     
如果 $i,j$ 之间没有峰值，那么 $f_i=f_j+1$。    
如果 $a_{j+1,\cdots,i-1}$ 中有 $\ge a_i$ 的数存在，即有峰值，那么相当于多插入一个，即 $f_i=f_j+2$。

综合起来，就有：

$$f_i=\max\limits_{1\le j<i,a_j\le a_i}\{f_j+[\max\limits_{k=j+1}^{i-1}a_k\ge a_i]\}+1$$

显然，$f_i$ 的值最多比 $\max f_j+1$ 多 $1$，要么是 $\max f_j+1$，要么是 $\max f_j+2$。    
只要知道 $\max f_j$ 对应的 $j$，就能算 $[\max\limits_{k=j+1}^{i-1}a_k\ge a_i]$，就能知道 $f_i$ 是 $\max f_j+1$ 还是 $\max f_j+2$ 了。

而且，$[\max\limits_{k=j+1}^{i-1}a_k\ge a_i]$ 是有单调性的，$j$ 越小越优，所以只要把 $\max f_j$ 对应的最小的 $j$ 拿来计算。

求 $[\max\limits_{k=j+1}^{i-1}a_k\ge a_i]$ 显然可以 ST 表解决。

考虑用对 $a_i$ 建权值线段树，$tr_i$ 维护两个值，$v$ 表示 $a_i$ 在这个范围内的 $f$ 的最大值，$p$ 表示 $f$ 取最大值的下标中的最小值。

在询问时，用单侧递归线段树的思想。    
由于询问肯定是前缀（$[1,a_i]$），所以对于左儿子不需要往下递归，直接返回。       
这样就只会递归右儿子。

复杂度就是 $\operatorname{O}(\log n)$，线段树细节见代码。

# code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<int,int> PII;

int read() {
	int n=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9') {
		n=(n<<1)+(n<<3)+ch-'0';
		ch=getchar();
	}
	return f==1?n:-n;
}

void write(int x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar((x%10)+'0');
}

//========================================================//

const int N=5e5+7,INF=1e9,K=20;

int n;
int a[N];
int f[N];

//========================================================//

int st[K][N];
int lg[N];

void init() {
	for(int i=1;i<=n;i++) 
		st[0][i]=a[i];
	for(int k=1;k<K;k++) 
		for(int i=1,j=1<<k;j<=n;i++,j++) {
			st[k][i]=max(st[k-1][i],st[k-1][i+(1<<(k-1))]);
		}
	lg[1]=0;
	for(int i=2;i<=n;i++) 
		lg[i]=lg[i>>1]+1;
}

int getmax(int l,int r) {
	if(l>r) return -INF;
	int k=lg[r-l+1];
	return max(st[k][l],st[k][r-(1<<k)+1]);
}

//========================================================//

struct Segment_Tree{
	
	struct Tr{
		int v;
		int p;
	}tr[N<<2];
	
	void pushup(int u) {
		Tr &f=tr[u],&ls=tr[u<<1],&rs=tr[u<<1|1];
		if(ls.v>rs.v) {
			f.v=ls.v;
			f.p=ls.p;
		}else if(ls.v<rs.v) {
			f.v=rs.v;
			f.p=rs.p;
		}else{
			f.v=ls.v;
			f.p=min(ls.p,rs.p);
		}
	}
	
	void build(int u,int l,int r) {
		tr[u].v=-1; tr[u].p=0;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(u<<1,l,mid); build(u<<1|1,mid+1,r);
	}
	
	void modify(int u,int l,int r,int k,int v,int p) {
		if(l==r) {
			if(tr[u].v<v) {
				tr[u].v=v;
				tr[u].p=p;
			}else if(tr[u].v==v) {
				tr[u].p=min(tr[u].p,p);
			}
			return;
		}
		int mid=(l+r)>>1;
		if(k<=mid) modify(u<<1,l,mid,k,v,p);
		else modify(u<<1|1,mid+1,r,k,v,p);
		pushup(u);
	}
	
	PII find(int u,int l,int r,int ql,int qr) {
		if(ql<=l && qr>=r) {
			return (PII){tr[u].v,tr[u].p};
		}
		int mid=(l+r)>>1;
		Tr &f=tr[u],&ls=tr[u<<1],&rs=tr[u<<1|1];
		if(qr<=mid) {
			return find(u<<1,l,mid,ql,qr);
		}
		if(rs.v<ls.v) return (PII){ls.v,ls.p};
		PII t=find(u<<1|1,mid+1,r,ql,qr);
		if(t.x<ls.v) return (PII){ls.v,ls.p};
		if(t.x>ls.v) return t;
		return (PII){ls.v,min(ls.p,t.y)};
	}
	
}tr;

//========================================================//

void input() {
	n=read();
	for(int i=1;i<=n;i++) 
		a[i]=read();
}

void work() {
	init();
	tr.build(1,1,n);
	int ans=0;
	for(int i=1;i<=n;i++) {
		f[i]=1;
		int j=tr.find(1,1,n,1,a[i]).y;
		if(getmax(j+1,i-1)>=a[i]) 
			f[i]=max(f[i],f[j]+2);
		else
			f[i]=max(f[i],f[j]+1);
		tr.modify(1,1,n,a[i],f[i],i);
		ans=max(ans,f[i]);
	}
	write(ans),putchar('\n');
}

int main() {
	int T=read();
	while(T--) {
		input();
		work();
	}
	return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

我们可以发现实际上选出来的就是两部分，第一部分是上升子序列，另一部分就是第一部分的头尾与两个数之间可以塞一个比两端都大的数。换句话说就是先选出所有 $\min(b_i,b_{i+1})$ 再往里面塞一些不会成为 $\min$ 的数。

那我们直接按普通 LIS 做，设 $f_i$ 为以 $i$ 为结尾的最长 LaIS 长度，并且要求 $a_i$ 属于上升子序列（第一部分）。这个时候我们选择离当前位置最远的最优转移位置 $j$，然后如果区间 $(j,i)$ 里面有比 $a_i$ 还大的数那很显然我们也可以塞一个数到 $a_j$ 和 $a_i$ 中间，这样长度可以再加一。

简单来说，

$$f_i=\max_{0\leq j<i,a_j\leq a_i}\left\{f_j+\left[\max_{k=j+1}^{i-1} a_k\geq a_i\right]\right\}+1$$

但是我们不用线段树，具体来说我们可以发现后面那个方括号最多也就 $1$，也就是说我们完全不用让 $f_j$ 变得更小来取到后面的方括号；其次我们肯定选的 $j$ 离 $i$ 越远越好。所以我们要选的 $j$ 是可以唯一确定的，那检验方括号是不是 $1$ 就很简单了，直接维护离这个数最近的比它大的数在哪就行了，只需要两个树状数组。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <array>

using namespace std;

struct lstpos
{
    int val,pos;
    bool operator<(const lstpos& that)const
    {
        return val<that.val||val==that.val&&pos>that.pos;
    }
};

array<lstpos,500001> biddp;
array<int,500001> bidpos;

template<typename type>
bool maxeq(type& a,const type& b)
{
    return a<b?a=b,true:false;
}

template<typename type,size_t cntb>
void update(int idx,type val,int cnt,array<type,cntb>& bidtree)
{
    while(idx<=cnt)
        maxeq(bidtree[idx],val),idx+=idx&-idx;
}
template<typename type,size_t cntb>
type query(int idx,array<type,cntb>& bidtree)
{
    type result=type();
    while(idx)
        maxeq(result,bidtree[idx]),idx-=idx&-idx;
    return result;
}

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testcnt;
    cin>>testcnt;
    while(testcnt--)
    {
        int cnt;
        cin>>cnt;
        int answer=0;
        for(int i=0;i<=cnt;i++)
            biddp[i]=lstpos(),bidpos[i]=0;
        for(int i=1;i<=cnt;i++)
        {
            int tmp;
            cin>>tmp;
            lstpos curans=query(tmp,biddp);
            ++curans.val+=query(cnt-tmp+1,bidpos)>curans.pos;
            update(tmp,(lstpos){curans.val,i},cnt,biddp),update(cnt-tmp+1,i,cnt,bidpos);
            maxeq(answer,curans.val);
            //cerr<<curans.val<<' ';
        }
        //endl(cerr);
        cout<<answer<<'\n';
    }
    return 0;
}
```

---

