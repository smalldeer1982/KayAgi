# [PA 2012] Tanie linie

## 题目背景

PA 2012 R5.

## 题目描述

给定含 $n$ 个数的序列，求至多 $k$ 个不相交子段的和的最大值。

## 说明/提示

对于 $100\%$ 的数据，$1\le k\le n\le 10^6$。序列内所有数在 $[-10^9,10^9]$ 内。

## 样例 #1

### 输入

```
5 2
7 -3 4 -9 5```

### 输出

```
13```

# 题解

## 作者：bai_tang (赞：20)

只要有信念，就一定能成功！

做法更简单，只用一个堆，[思路来源](https://loj.ac/p/6489)。

### [题意](https://www.luogu.com.cn/problem/P6821)
给一个长为 $n$ 的序列，求选择至多 $k$ 个不交连续子段的最大子段和，$n,k\le 10^6$。

### 分析
此题数据范围如此之大，DP 正常情况下无法设计出合适的状态来解决此问题，考虑贪心。

考虑当 $k$ 极大的时候，答案一定是所有正数的和，考虑从反向考虑，也就是从“很多个段”变成“一个段”。

容易发现，极大的连续非负段和极大连续负段总是同时选或者同时不选比较优秀，考虑把它们合并，问题变成一个正负交替数列，一开始你选了所有正的数，接下来你有两种操作：合并两个段（也就是加入两个段之间的那个为负的元素），删除一个段，而这可以直接用堆实现，[代码](https://www.luogu.com.cn/paste/hkz7zrx1)。

---

## 作者：Arghariza (赞：15)

这里只讲[加强版](https://www.luogu.com.cn/problem/CF280D)，这是严格弱化。

结论是贪心。每次取出最大和连续子段，目前答案加上这个子段和，然后再把这个子段取反（相反数T），然后求整个过程答案的最大值。

考虑费用流模型。对于 $i\le n$，$S\to i$ 连边，$i\to T$ 连边，流量为 $1$ 费用为 $0$；$i\to i+1$ 连边，流量为 $1$ 费用为 $-a_i$。求费用流的时候，取 $S\to i\to j\to T$ 流，代表取了 $[i,j)$ 这个区间。不难发现上面贪心策略对应的就是费用流的贪心，所以这也叫模拟费用流。

所以只用维护 $2$ 种操作：

- 求出区间最大子段和以及其两个端点 $l,r$。
- 支持区间取相反数。

考虑用线段树维护这个东西。

正常的区间最大子段和需要维护 $lmx,rmx,mx$ 三个值嘛，分别表示取左端点的最大子段，取右端点的最大子段和整个区间的最大子段。由于要求端点位置，还需要维护 $lx,rx,llx,rrx$ 表示取右端点的最大子段的左端点、取左端点最大子段的右端点、以及这个区间最大子段的左右端点。合并的时候简单讨论一下就可以了。

现在要区间取反，所以添加一个标记，把最大改成最小，再维护 $lmn,rmn,mn,ln,rn,lln,rrn$ 七个值即可，也是简单讨论一下。

然后询问之间互相独立，要开个栈存下所有取反操作，逐一还原回去。

复杂度 $O(qk\log n)$，这是**加强版**的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace vbzIO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define rd read
	#define wr write
	#define pc putchar
	#define pi pair<int, int>
	#define mp make_pair
	#define fi first
	#define se second
	#define pb push_back
	#define ins insert
	#define era erase
	inline int read () {
		char ch = gh();
		int x = 0;
		bool t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? ~(x - 1) : x;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using vbzIO::read;
using vbzIO::write;

const int N = 1e5 + 100;
bool chkmx(int &x, int y) { return x < y ? (x = y, 1) : 0; }
bool chkmn(int &x, int y) { return x > y ? (x = y, 1) : 0; }
struct seg {
	int sum;
	int lmx, rmx, mx, lx, rx, llx, rrx;
	int lmn, rmn, mn, ln, rn, lln, rrn;
	seg operator + (const seg &rhs) const {
		seg ans;
		ans.sum = sum + rhs.sum;
		
		ans.lmx = lmx, ans.llx = llx, ans.rmx = rhs.rmx, ans.rrx = rhs.rrx;
		if (chkmx(ans.lmx, sum + rhs.lmx)) ans.llx = rhs.llx;
		if (chkmx(ans.rmx, rhs.sum + rmx)) ans.rrx = rrx;
		ans.mx = mx, ans.lx = lx, ans.rx = rx;
		if (chkmx(ans.mx, rhs.mx)) ans.lx = rhs.lx, ans.rx = rhs.rx;
		if (chkmx(ans.mx, rmx + rhs.lmx)) ans.lx = rrx, ans.rx = rhs.llx;
		
		ans.lmn = lmn, ans.lln = lln, ans.rmn = rhs.rmn, ans.rrn = rhs.rrn;
		if (chkmn(ans.lmn, sum + rhs.lmn)) ans.lln = rhs.lln;
		if (chkmn(ans.rmn, rhs.sum + rmn)) ans.rrn = rrn;
		ans.mn = mn, ans.ln = ln, ans.rn = rn;
		if (chkmn(ans.mn, rhs.mn)) ans.ln = rhs.ln, ans.rn = rhs.rn;
		if (chkmn(ans.mn, rmn + rhs.lmn)) ans.ln = rrn, ans.rn = rhs.lln;
	
		return ans;
	}
} tr[N << 2];
int n, m, a[N], tag[N << 2];
stack<pi> opt;

void revt(seg &x) {
	seg ans;
	ans.sum = -x.sum;
	ans.lmx = -x.lmn, ans.llx = x.lln, ans.rmx = -x.rmn, ans.rrx = x.rrn;
	ans.lmn = -x.lmx, ans.lln = x.llx, ans.rmn = -x.rmx, ans.rrn = x.rrx;
	ans.mx = -x.mn, ans.lx = x.ln, ans.rx = x.rn;
	ans.mn = -x.mx, ans.ln = x.lx, ans.rn = x.rx;
	x = ans;
}

void sett(int l, int x) {
	tr[x] = (seg) {
		a[l], 
		a[l], a[l], a[l], l, l, l, l, 
		a[l], a[l], a[l], l, l, l, l
	};
}

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)
void pushup(int x) { tr[x] = tr[ls] + tr[rs]; }
void pushrev(int x) { tag[x] ^= 1, revt(tr[x]); }
void pushdown(int x) {
	if (!tag[x]) return;
	pushrev(ls), pushrev(rs);
	tag[x] = 0;
}

void build(int l, int r, int x) {
	if (l == r) return sett(l, x);
	build(l, mid, ls), build(mid + 1, r, rs), pushup(x);
}

void upd(int l, int r, int p, int x) {
	if (l == r) return sett(l, x);
	pushdown(x);
	if (p <= mid) upd(l, mid, p, ls);
	else upd(mid + 1, r, p, rs);
	pushup(x);
}

void rev(int l, int r, int s, int t, int x) {
	if (s <= l && r <= t) return pushrev(x);
	pushdown(x);
	if (s <= mid) rev(l, mid, s, t, ls);
	if (t > mid) rev(mid + 1, r, s, t, rs);
	pushup(x);
}

seg qry(int l, int r, int s, int t, int x) {
	if (s <= l && r <= t) return tr[x];
	pushdown(x);
	if (s > mid) return qry(mid + 1, r, s, t, rs);
	else if (t <= mid) return qry(l, mid, s, t, ls);
	else return qry(l, mid, s, t, ls) + qry(mid + 1, r, s, t, rs);
}

int main() {
	n = rd();
	for (int i = 1; i <= n; i++) a[i] = rd();
	build(1, n, 1), m = rd();
	while (m--) {
		int op = rd(), l = rd(), r = rd();
		if (!op) a[l] = r, upd(1, n, l, 1);
		else {
			int k = rd(), ans = 0, sum = 0;
			while (k--) {
				seg tp = qry(1, n, l, r, 1);
				chkmx(ans, sum += tp.mx);
				opt.push(mp(tp.lx, tp.rx));
				rev(1, n, tp.lx, tp.rx, 1);
			}
			while (!opt.empty()) 
				rev(1, n, opt.top().fi, opt.top().se, 1), opt.pop();
			wr(ans), puts("");
		}
	}
	return 0;
} 
```

---

## 作者：Fido_Puppy (赞：10)

$$\texttt{Preface}$$

发现有至多选 $k$ 个的限制，不如来一发 wqs 二分。

$$\texttt{Description}$$

[P6821 [PA2012]Tanie linie](https://www.luogu.com.cn/problem/P6821)

$$\texttt{Solution}$$

首先我们设 $g(x)$ 表示恰好选 $x$ 个不相交子段的和的最大值。

由于我们想要用 wqs 二分，所以来感性理解一下这道题中 $g(x)$ 是一个关于 $x$ 的上凸函数。

刚开始我们肯定选择最大的一段，当选择的段数越多，答案增加的量就越小，否则就可以把这段移到前面去，不满足最优性；如果强制选择的段数过大，则必须选择一些负数，会使得答案变劣。

然后去掉了 $k$ 的限制，考虑如何计算选择任意段的和的最大值。

设 $f(i)$ 表示取的最后一段是以 $i$ 结尾的一段，所得到的最大值，$pre(i)$ 表示 $f(i)$ 的前缀最大值，$sum(i)$ 表示 $a_i$ 的前缀和。

枚举最后一段为 $(j, i]$，可以列出状态转移方程：

$$f(i) = \max_{0 \le j < i} sum(i) - sum(j) + pre(j)$$

直接记录 $pre(i) - sum(i)$ 的前缀最大值，时间复杂度 $\Theta(n)$。

总时间复杂度 $\Theta(n \log v)$。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int n, k, a[1000005];
i64 sum[1000005], ans = -1e18;

pair <i64, int> pre[1000005], f[1000005];

pair <i64, int> check(i64 mid) {
    pre[0] = f[0] = make_pair(0, 0);
    int res = 0;

    for (int i = 1; i <= n; ++i) {
        f[i] = make_pair(pre[res].first - sum[res] + sum[i] - mid, pre[res].second + 1);

        if (f[i].first > pre[ i - 1 ].first) {
            pre[i] = f[i];
        }
        else if (f[i].first == pre[ i - 1 ].first && f[i].second < pre[ i - 1 ].second) {
            pre[i] = f[i];
        }
        else pre[i] = pre[ i - 1 ];

        if (pre[res].first - sum[res] < pre[i].first - sum[i]) {
            res = i;
        }
        else if (pre[res].first - sum[res] == pre[i].first - sum[i] && pre[i].second < pre[res].second) {
            res = i;
        }
    }

    pair <i64, int> ans = make_pair(0, 0);

    for (int i = 1; i <= n; ++i) {
        if (f[i].first > ans.first) {
            ans = f[i];
        }
        else if (f[i].first == ans.first && f[i].second < ans.second) {
            ans = f[i];
        }
    }

    return ans;
}

int main() {
    ios :: sync_with_stdio(0), cin.tie(0);

    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[ i - 1 ] + a[i];
    }

    if (check(0).second <= k) {
        return cout << check(0).first << '\n', 0;
    }

    i64 l = -1e15, r = 1e15;

    while (l <= r) {
        i64 mid = (l + r) >> 1;
        pair <i64, int> now = check(mid);

        if (now.second <= k) {
            ans = now.first + mid * k;
            r = mid - 1;
        }
        else l = mid + 1;
    }

    cout << ans << '\n';

    return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：Genius_Star (赞：6)

### 思路：

考虑贪心：

- 对于一段正数，一定一起被选中，可以加起来看成一个数。

- 对于一段负数，也一定一起被选中，因为选它是为了连续选它两端的正数，则也可以加起来看成一个数。

若最左边与最右边是负数，则不必考虑，因为肯定不会选，那么此时序列 $a$ 肯定是下述的形式。

$$+-+-+\cdots +-+-+$$

设里面有 $A$ 个正数：

- 若 $M \ge A$，则正数全选，忽略负数。

- 若 $M < A$，先选出所有正数，然后考虑退款。

对于第二种情况，需要进行 $A-M$ 次退款，有两种情况可以退款：

- 不选某个正数。

- 把两个正数和中间负数一起合并。

需要注意到每次退款可能造成新的情况：

- 不选某个正数之后，可以与该正数两端负数合并出一个新的数，看作负数；可以用情况二加回来。

- 把两个正数和中间负数一起合并后，可以把他们合起来看作一个正数；可以用情况一退款。

先令 $ans$ 为所有正数的和，先将序列中所有数加入堆中，是按照绝对值的小根堆，那么有两种情况：

- 若 $a_x < 0$，那么就相当于与两边的正数合并（因为是当前绝对值最小的，依旧是最优策略）；然后删除 $x-1,x+1$，将 $a_{x-1} + a_{x+1} - a_x$ 放到 $x$ 处。

- 若 $a_x \ge 0$，那么相当于舍弃某个正数，然后也相当于与两端的负数进行合并；然后删除 $x-1,x+1$，将 $a_{x-1} + a_{x+1} - a_x$ 放到 $x$ 处。

- 这里 $x-1,x+1$ 表示的 $x$ 上或下一个未被删除的位置，可以用双向链表维护，记录一个 $l_i,r_i$ 即可。

因为要支持删除操作，标记一下即可，若当前堆顶已被标记，则表示被删除了，重新取出下一个堆顶，直到当前堆顶未被删除。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
using namespace std;
typedef long long ll;
typedef double db;
const ll N=1e6+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll data;
	ll id;
	bool operator<(const Node&rhs)const{
		return abs(data)>abs(rhs.data);
	}
};
ll n,m,k,x,ans,cnt=1;
ll a[N],l[N],r[N];
bool f[N];
priority_queue<Node> Q;
bool check(ll x){
	if((0<l[x]&&r[x]<n+1)||a[x]>0)
	  return 1;
	return 0;
}
void del(ll x){
	f[x]=1;
	l[r[x]]=l[x],r[l[x]]=r[x];
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		x=read();
		if(!x)
		  continue;
		if((x>=0&&a[cnt]>=0)||(x<=0&&a[cnt]<=0))
		  a[cnt]+=x;
		else
		  a[++cnt]=x;
	}
	n=cnt;
	for(int i=1;i<=n;i++){
		l[i]=i-1,r[i]=i+1;
		if(a[i]>0){
			k++;
			ans+=a[i];
		}
		Q.push({a[i],i});
	}
	while(k>m){
	    if(Q.empty())
	      break;
		x=Q.top().id;
		Q.pop();
		if(f[x])
		  continue;
		if(check(x)){
			ans-=abs(a[x]);
			a[x]+=a[l[x]]+a[r[x]];
			del(l[x]),del(r[x]);
			Q.push({a[x],x});
			k--;
		}
	}
	write(ans);
	return 0;
}
```

---

## 作者：reclusive (赞：5)

[my blog](https://www.cnblogs.com/reclusive2007/p/17711339.html)

本来想写 wqs 二分来着，然后推不出状态转移方程，摆烂了。

------------

## 题目描述

给定含 $n$ 个数的序列，求至多 $k$ 个不相交子段的和的最大值。

## 具体思路

由于选 $k$ 堆连续的数，因此一堆连续的符号相同的数，只有可能是同时被选或者同时不被选。

因此我们先对原序列预处理一遍，将相同符号的合并到一起。

现在的序列就是一个正负交替的序列。

要答案最大，那我们肯定先把所有正数都选出来。

若正数个数小于等于 $k$，那我们直接输出就好了，因为再选一些负数只会让我们的答案变得更小。

若正数个数大于 $k$，此时我们有两种操作。

- 操作 1：将选定的正数中删除一部分正数。

- 操作 2：将两堆正数连同它们之间的负数合并成一堆，这样堆数就会减少一堆。

对于操作 1，相当于减少 $a_i$，对于操作 2，相当于减少了 $-a_i$，因此可以看成减少了 $\left | a_i \right |$。

我们要让结果最大，就是要让删除的数最小，因此用一个二叉堆来给 $\left | a_i \right |$ 排序，而合并操作显然是用链表来维护的。

## Code

```
#include<cstdio>
#include<queue>
#include<cmath>
using namespace std;
typedef long long LL;
typedef pair<LL,int>PII;
const int N=1e6+5;
const LL inf=1e18;
int L[N],R[N];
LL a[N];int v[N];
int n,m,len=1;
priority_queue<PII,vector<PII>,greater<PII>>Q;
void ins(int x){
    L[x]=x-1;
    R[x]=x+1;
}
void del(int x){
	R[L[x]]=R[x];
	L[R[x]]=L[x];
	v[x]=1;
}
bool check(int x){
	if((0<L[x]&&R[x]<n+1)||a[x]>0)
		return true;
	return false;
}
bool check1(LL x,LL y){
	if((x>=0&&y>=0)||(x<0&&y<0))
		return true;
	return false;
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%lld",&a[len]);
    for(int i=2;i<=n;i++){
    	LL x;scanf("%lld",&x);
    	if(!x)continue;
    	if(!check1(a[len],x))a[++len]=x;
    	else a[len]=a[len]+x;
	}
	n=len;
	LL ans=0;int cnt=0;
    for(int i=1;i<=n;i++){
    	if(a[i]>0){
    		ans=ans+a[i];
    		cnt++;
		}
        ins(i);
        Q.push({abs(a[i]),i});
    }
    while(cnt>m){
    	while(v[Q.top().second])Q.pop();
    	PII x=Q.top();Q.pop();
    	if(check(x.second)){
    		ans=ans-x.first;cnt--;
    		int l=L[x.second],r=R[x.second];
    		a[x.second]+=a[l]+a[r];
    		Q.push({abs(a[x.second]),x.second});
    		del(l),del(r);
		}
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：钓鱼王子 (赞：5)

模拟费用流/后悔贪心的模板。和 CF280D 一模一样。

具体来说，我们每次找到最大子段和，但我们可能会做出不够优秀的选择，也就是说，我们不一定选最大子段和，比如：

$2~-1~1~1~1~-1~2$ 选 $2$ 次最优可以达到 $4$。

也就是说，我们要支持后悔。

每次选了一个区间之后把他区间取相反数如果再次选到这个位置代表撤回操作。

做法就是这样的，但由于区间取反线段树的标记有点多，但理解了还是很好写的。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define re register
using namespace std;
const int Mxdt=1000000;	//单次大小 
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	re int t=0,f=0;re char v=gc();
	while(v<'0')f|=(v=='-'),v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return f?-t:t;
}
int n,a[1000002],lmxp[3000002],rmxp[3000002],lmnp[3000002],rmnp[3000002],mxl[3000002],mxr[3000002],mnl[3000002],mnr[3000002],q,rev[3000002];
long long lmn[3000002],rmn[3000002],lmx[3000002],rmx[3000002],sum[3000002],mx[3000002],mn[3000002],num,lp,ans,al,ar;
inline void pu(re int p){
	if(lmn[p<<1]<=sum[p<<1]+lmn[p<<1|1])lmn[p]=lmn[p<<1],lmnp[p]=lmnp[p<<1];
	else lmn[p]=sum[p<<1]+lmn[p<<1|1],lmnp[p]=lmnp[p<<1|1];
	if(lmx[p<<1]>=sum[p<<1]+lmx[p<<1|1])lmx[p]=lmx[p<<1],lmxp[p]=lmxp[p<<1];
	else lmx[p]=sum[p<<1]+lmx[p<<1|1],lmxp[p]=lmxp[p<<1|1];
	if(rmx[p<<1|1]>=sum[p<<1|1]+rmx[p<<1])rmx[p]=rmx[p<<1|1],rmxp[p]=rmxp[p<<1|1];
	else rmx[p]=sum[p<<1|1]+rmx[p<<1],rmxp[p]=rmxp[p<<1];
	if(rmn[p<<1|1]<=sum[p<<1|1]+rmn[p<<1])rmn[p]=rmn[p<<1|1],rmnp[p]=rmnp[p<<1|1];
	else rmn[p]=sum[p<<1|1]+rmn[p<<1],rmnp[p]=rmnp[p<<1];
	if(mx[p<<1]>=mx[p<<1|1]&&mx[p<<1]>=rmx[p<<1]+lmx[p<<1|1])mx[p]=mx[p<<1],mxl[p]=mxl[p<<1],mxr[p]=mxr[p<<1];
	else if(mx[p<<1|1]>=mx[p<<1]&&mx[p<<1|1]>=rmx[p<<1]+lmx[p<<1|1])mx[p]=mx[p<<1|1],mxl[p]=mxl[p<<1|1],mxr[p]=mxr[p<<1|1];
	else mx[p]=rmx[p<<1]+lmx[p<<1|1],mxl[p]=rmxp[p<<1],mxr[p]=lmxp[p<<1|1];
	if(mn[p<<1]<=mn[p<<1|1]&&mn[p<<1]<=rmn[p<<1]+lmn[p<<1|1])mn[p]=mn[p<<1],mnl[p]=mnl[p<<1],mnr[p]=mnr[p<<1];
	else if(mn[p<<1|1]<=mn[p<<1]&&mn[p<<1|1]<=rmn[p<<1]+lmn[p<<1|1])mn[p]=mn[p<<1|1],mnl[p]=mnl[p<<1|1],mnr[p]=mnr[p<<1|1];
	else mn[p]=rmn[p<<1]+lmn[p<<1|1],mnl[p]=rmnp[p<<1],mnr[p]=lmnp[p<<1|1];
	sum[p]=sum[p<<1]+sum[p<<1|1];
}
inline void RR(re int p){
	swap(lmx[p],lmn[p]),swap(lmxp[p],lmnp[p]),swap(rmx[p],rmn[p]),swap(rmxp[p],rmnp[p]);
	lmx[p]=-lmx[p],lmn[p]=-lmn[p],rmx[p]=-rmx[p],rmn[p]=-rmn[p];
	swap(mx[p],mn[p]),swap(mxl[p],mnl[p]),swap(mxr[p],mnr[p]);
	mx[p]=-mx[p],mn[p]=-mn[p],sum[p]=-sum[p];
	rev[p]^=1;
}
inline void pd(re int p){if(rev[p])RR(p<<1),RR(p<<1|1),rev[p]=0;}
inline void build(re int p,re int l,re int r){
	if(l==r){
		sum[p]=a[l];
		if(a[l]>0)lmx[p]=rmx[p]=mx[p]=a[l],lmxp[p]=rmxp[p]=mxl[p]=mxr[p]=l;
		else lmn[p]=rmn[p]=mn[p]=a[l],lmnp[p]=rmnp[p]=mnl[p]=mnr[p]=l;
		return;
	}
	re int mid=l+r>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	pu(p);
}
inline void cg(re int p,re int l,re int r,re int x,re int y){
	if(l==r){
		a[l]=y,sum[p]=a[l];
		lmn[p]=rmn[p]=mn[p]=lmx[p]=rmx[p]=mx[p]=lmxp[p]=rmxp[p]=mxl[p]=mxr[p]=lmnp[p]=rmnp[p]=mnl[p]=mnr[p]=0;
		if(a[l]>0)lmx[p]=rmx[p]=mx[p]=a[l],lmxp[p]=rmxp[p]=mxl[p]=mxr[p]=l;
		else lmn[p]=rmn[p]=mn[p]=a[l],lmnp[p]=rmnp[p]=mnl[p]=mnr[p]=l;
		return;
	}
	pd(p);
	re int mid=l+r>>1;
	if(x<=mid)cg(p<<1,l,mid,x,y);
	else cg(p<<1|1,mid+1,r,x,y);
	pu(p);
}
inline void rever(re int p,re int l,re int r,re int x,re int y){
	if(l>=x&&r<=y){RR(p);return;}
	re int mid=l+r>>1;
	pd(p);
	if(x<=mid)rever(p<<1,l,mid,x,y);
	if(y>mid)rever(p<<1|1,mid+1,r,x,y);
	pu(p);
}
inline void query(re int p,re int l,re int r,re int x,re int y){
	if(l>=x&&r<=y){
		if(num+lmx[p]>ans)ans=num+lmx[p],al=lp,ar=lmxp[p];
		if(mx[p]>ans)ans=mx[p],al=mxl[p],ar=mxr[p];
		if(num+sum[p]>=rmx[p])num+=sum[p];
		else if(rmx[p])num=rmx[p],lp=rmxp[p];
		else lp=r+1,num=0;
		return;
	}
	pd(p);
	re int mid=l+r>>1;
	if(x<=mid)query(p<<1,l,mid,x,y);
	if(y>mid)query(p<<1|1,mid+1,r,x,y);
}
signed main(){
	n=read();
re int k=read();
	for(re int i=1;i<=n;++i)a[i]=read();
	build(1,1,n);
			re int l=1,r=n,cnt=0;
			long long kk=0;
			for(re int i=1;i<=k;++i){
				ans=0,num=0,lp=l,al=0,ar=0;
				query(1,1,n,l,r);
				if(ans){
					kk+=ans;
					rever(1,1,n,al,ar);
				}
				else break;
			}
			printf("%lld",kk);
}
```


---

## 作者：__Star_Sky (赞：4)

## Solution

自己手造几个样例，可以发现，一段连续的正数或负数一定同时选或不选。这是因为只选连续的正数段一定是最优的，如果要选负数一定是因为正数段个数太多，要通过选负数将两个正数段合并以减少段数。因此，可以先将连续的正数和连续的负数合并。这样一来，原来的序列变成了正负交替的新序列。

如果新序列正数的个数小于等于 $k$，那么选上所有的正数一定是最优的，直接输出所有的正数的和即可。

如果正数的个数大于 $k$，那么我们可以先将全部正数选出，再删除或合并一些段使段数减少到 $k$。设所有正数的和为 $sum$，一共有 $k_1$ 段。此时我们有两种选择：

1.删除一段正数 $x$，则 $sum$ 会减少 $x$。

2.将两段正数合并，则 $sum$ 会加上中间一段负数 $x$，也就是减少 $|x|$。

两种操作都会使 $k_1$ 减少 $1$，因此一共要进行 $k_1-k$ 次操作。显然我们的目标是让每次操作 $sum$ 减少的值尽量小，可以使用一个小根堆维护最小值。初始时先把每个数的绝对值插入小根堆，每次取出堆顶元素进行操作。但是要注意选完最小值之后原序列会发生合并，要用链表维护原序列，每次操作后将 `a[i]+a[l[i]]+a[r[i]]` 插入二叉堆，并删除 `a[l[i]]` 和 `a[r[i]]`。其中 `a[l[i]]` 表示 `a[i]` 的前驱，`a[r[i]]` 表示 `a[i]` 的后继。

## Code
```
#include<bits/stdc++.h>
#define LL long long
#define PLI pair<LL,int>
using namespace std;
const int N=1e6+10;
int n,m;
struct list{
	int l,r;
	LL x;
}a[N];
priority_queue<PLI,vector<PLI>,greater<PLI>> q;
void del(int x)
{
	a[a[x].l].r=a[x].r;
	a[a[x].r].l=a[x].l;
	a[x].x=0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i].x),a[i].l=i-1,a[i].r=i+1;
	for(int i=2;i<=n;i++)
	{
		if((a[i].x>0&&a[a[i].l].x>0)||(a[i].x<0&&a[a[i].l].x<0)||!a[i].x)
		{
			a[i].x+=a[a[i].l].x;
			del(a[i].l);
		}
	}
	int cnt=0;
	LL ans=0;
	for(int i=1;i<=n;i++)
		if(a[i].x>0) 
		{
			ans+=a[i].x;
			cnt++; 
		}
	if(cnt<=m) printf("%lld\n",ans),exit(0);
	for(int i=1;i<=n;i++)
		if(a[i].x)
			q.push({abs(a[i].x),i});
	while(cnt>m)
	{
		while(!a[q.top().second].x) q.pop();
		LL x=q.top().first;int i=q.top().second;q.pop();
		if(!a[i].x) continue;
		if(a[i].x>0||(a[i].l&&a[i].r!=n+1))
		{
			ans-=x;cnt--;
			a[i].x+=a[a[i].l].x+a[a[i].r].x;
			del(a[i].l),del(a[i].r);
			q.push({abs(a[i].x),i});
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

考虑恰好选 $k$ 个子段怎么做。

设恰好选 $i$ 个子段的和最大值为 $h_k$。可以得到 $h_{i + 1} - h_i \le h_i - h_{i - 1}$，因为 $h_i \to h_{i + 1}$ 的过程就是多选一个子段，贡献肯定不如上一次选即 $h_{i - 1} \to h_i$ 大。如果它不成立，那我们可以交换 $h_{i - 1} \to h_i$ 和 $h_i \to h_{i + 1}$ 选的段从而得到更大的 $h_i$，矛盾。

那么 $(i, h_i)$ 构成一个上凸包。接下来是经典的 wqs 二分，二分直线斜率切这个上凸包，dp 一遍求出最大截距，这样二分即可找到过 $(k, h_k)$ 且与上凸包相切的直线方程，就能得到 $h_k$。

dp 的过程是平凡的。设 $f_i$ 为 $[1, i]$ 个中选了若干个子段，它们的和最大值，设 $g_i$ 为在取到最大值的基础上，**选的段数最小值**。因为当有一些点和 $(k, h_k)$ 共线时，我们希望最后算出来是最左边的点，从而得到这条直线。

$f_i$ 有转移 $f_i = \max(f_{i - 1}, \max\limits_{j = 1}^i (f_{j - 1} + \sum\limits_{p = j}^i a_p))$。令 $b_i = \sum\limits_{j = 1}^i a_j$，维护前缀最大的 $f_i - b_i$ 和在它最大的基础上最小的 $g_i$，dp 即可做到 $O(n)$。

如果只是限制最多选 $k$ 个，那如果 $(k, h_k)$ 在左半边（即最高点的左边），那 $\forall i \in [1, k), h_k \ge h_i$，当作恰好 $k$ 个处理即可；如果它在右半边，二分斜率时下界设置为 $0$，那么它就不能被截到。这种情况，直接求出 $\max\limits_{i = 1}^n h_i$ 即可。这里也可以用上面的 dp 方法。

总时间复杂度 $O(n \log V)$，$V$ 是值域。

```cpp
const int maxn = 1000100;
const ll inf = 0x3f3f3f3f3f3f3f3fLL;

ll n, m, a[maxn], b[maxn], f[maxn], g[maxn];

inline pii calc(ll x) {
	ll mx = 0, cnt = 1;
	for (int i = 1; i <= n; ++i) {
		f[i] = f[i - 1];
		g[i] = g[i - 1];
		ll val = mx + b[i] - x;
		if (val > f[i]) {
			f[i] = val;
			g[i] = cnt;
		} else if (val == f[i]) {
			g[i] = min(g[i], cnt);
		}
		val = f[i] - b[i];
		if (val > mx) {
			mx = val;
			cnt = g[i] + 1;
		} else if (val == mx) {
			cnt = min(cnt, g[i] + 1);
		}
	}
	return make_pair(f[n], g[n]);
}

void solve() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		b[i] = b[i - 1] + a[i];
	}
	ll l = 0, r = 2e9, ans = -inf;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		pii p = calc(mid);
		if (p.scd <= m) {
			ans = p.fst + m * mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	if (ans == -inf) {
		ans = calc(0).fst;
	}
	printf("%lld\n", ans);
}
```


---

## 作者：Lofty (赞：2)

### 题目背景

翰翰 18 岁生日的时候，达达给她看了一个神奇的序列 $ A_1,A_2,\dots ,A_n $ 。她被允许从中选择不超过 $ M $ 个连续的部分作为自己的生日礼物。

翰翰想要知道选择元素之和的最大值。

你能帮助她吗？

### 解题思路

可以先合并序列中连续的同为正或负的值，使原序列变为一个一正一负排列的序列。

先将所有正数相加存入 $ ans $ ,记录目前的段数 $ positive $ ，因为只取 $ M $ 段，我们可以尝试以下方法。
- 减去一个正数。 
- 加上一个负数，并使相邻的正数连成一段。

上述两种操作均会使目前的段数 $ positive-1 $ ，直到 $ positive=M $ 时，最终的 $ ans $ 就是我们想要的结果。

而我们想要 $ ans $ 尽量大，所以减去的正数要尽量小或加上的负数要尽量大，等价于求 $ \left| A_i \right|_ {min} $ 。所以我们可以将所有数取绝对值存入小根堆，每次找堆顶操作。连成一段的操作可以用链表修改前驱和后继，使其连成一段。

**注意：** 若最左边和最右边的值为负的，显然是不用取的，需要特判一下。

### 代码
```
#include<cstdio>
#include<queue>
using namespace std;
typedef long long LL;
constexpr int N=1e6+10;
constexpr LL inf=1e18;
typedef pair<LL,LL> PII;
priority_queue<PII,vector<PII>,greater<PII>>q;
LL n,m,positive,maxn;
LL d[N],l[N],r[N];
bool v[N];
bool check_symbols(LL x,LL y)
{
    if((x>=0&&y>=0)||(x<0&&y<0))return 1;
    return 0;
}
LL abs(LL x){return x>0?x:-x;}
void remove(int x)
{
    l[r[x]]=l[x];
    r[l[x]]=r[x];
    v[x]=true;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    LL dlen=1;
    scanf("%lld",&d[dlen]);
    for(int i=2,x;i<=n;i++)
    {
        scanf("%lld",&x);
        if(!x)continue;
        if(check_symbols(d[dlen],x))
            d[dlen]+=x;
        else 
            d[++dlen]=x;
    }
    LL ans=0;
    for(LL i=1;i<=dlen;i++)
    {
        l[i]=i-1;r[i]=i+1;
        if(d[i]>0)ans+=d[i],positive++;
        q.push({abs(d[i]),i});
    }
    while(positive>m)
    {
        PII con=q.top();
        q.pop();
        int x=con.second;
        if(v[x])continue;
        if(d[x]>0||(l[x]!=0&&r[x]!=dlen+1))
        {
            ans-=con.first;
            d[x]+=d[l[x]]+d[r[x]];
            q.push({abs(d[x]),x});
            remove(r[x]);
            remove(l[x]);
            --positive;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
还是很水的啊。~~我不说是谁做了一天~~

---

## 作者：fish_love_cat (赞：1)

注意到把数列 $A$ 转化为正负交替的形式不影响答案，把 $A$ 中的 $0$ 忽略也不影响答案。设转化后的数列为 $B$，其中有 $c$ 个正数，它们的和是 $s$。显然 $B$ 中没有 $0$。

+ 当 $c\le m$ 时，答案就是 $s$。
+ 当 $c>m$ 时，考虑将 $c$ 变小，也就是把某些正数合并消失。也就是将 $b_{i-1},b_i,b_{i+1}$ 替换成三者之和。我们思考如何计算一次合并的贡献。
  + 当 $b_i>0$ 时，显然不会合并以后加入，最优解是不取，$s$ 会减去 $b_i$。
  + 当 $b_i<0$ 时，显然合掉以后 $s$ 会加上 $b_i$。
+ 可以发现每一步都让 $s$ 减去了 $|b_i|$。

反复执行上述直至 $c\le m$。
 
我们要使结果尽量大，那么就要让每次操作的 $|b_i|$ 尽量小。可以使用优先队列来维护。

至于上下家，我们可以套一个链表维护。

注意特判链头和链尾，以及出队时记得判断是不是已经合掉了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int shang[100005],xia[100005];
int a[100005],b[100005],top,ans,flc;
struct fish{
	int x,id;
	bool operator<(const fish &wssb)const{
		return abs(x)>abs(wssb.x);
	}
};
priority_queue<fish>q;
bool flag[100005];
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    for(int i=1;i<=n;i++){
        if(a[i]){
            if(top){
                if(b[top]<0&&a[i]>0||b[top]>0&&a[i]<0)b[++top]=a[i];
                else b[top]+=a[i];
            }else b[++top]=a[i];
        }
    }
    b[0]=b[top+1]=1e9+7;
    for(int i=1;i<=top;i++)
    if(b[i]>0)ans+=b[i],flc++;
    for(int i=1;i<=top;i++)
    q.push({b[i],i}),shang[i]=i-1,xia[i]=i+1;
    while(flc>m){
        int f=q.top().x,s=q.top().id;
        q.pop();
        if(flag[s])
        continue;
        if(shang[s]!=0&&xia[s]!=top+1||b[s]>0){
            ans-=abs(b[s]),
            flag[shang[s]]=flag[xia[s]]=1,
            b[s]+=b[shang[s]]+b[xia[s]],
            shang[s]=shang[shang[s]],
            xia[shang[s]]=s,
            xia[s]=xia[xia[s]],
            shang[xia[s]]=s;
            q.push({b[s],s}),
            flc--;
        }
    }
    cout<<ans;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/list?pid=P10478&user=754021)。

---

## 作者：luxiaomao (赞：1)

## [P6821](https://www.luogu.com.cn/problem/P6821) 反悔贪心经典例题

写完弱化版双倍经验 P10478 过来被硬控，研究好一会才过，写篇题解祭一下。

## Solution

题意不难理解。

首先可以发现，如果没有 $k$ 这个限制（或者说 $k$ 足够大），那么我们的答案就是序列中所有正数的和。

那么我们可以先求出这样情况下的正区间个数 $cnt$，然后再把这个 $cnt$ 逐步降到 $k$。

怎么降？有两种方式：

- 抛弃一个正区间，这能让 $cnt$ 减掉一。

- 选择一个负区间算入答案，这能让它左右两个正区间合为一，同样使 $cnt$ 减掉一。

那么可以发现，要求这些被抛弃掉的贡献，实质就是求从若干个正负区间中选择互不相邻的 $(cnt-k)$ 个区间，使这些区间的绝对值之和最小。

把区间视作点，那么这道题就被完美转化成了 [P1484](https://www.luogu.com.cn/problem/P1484)，即反悔贪心的模板。

笔者采用优先队列 + 链表来实现。

这里有一个实现上的小问题。

在把初始的 $a$ 序列划分成若干个正负区间的时候，如果这么写（已经开了 `long long`）：
```cpp
for(int i = 1;i <= n;i++)
{
	a[i] = read();
	if(a[i] * b[tot] < 0)b[++tot] = a[i];
	else b[tot] += a[i];
}
```
逻辑上没有问题，但是会 WA #6，因为可能会爆 `long long`。（自己算算，差不多能大到十的二十几次）

所以就别用乘法：
```cpp
for(int i = 1;i <= n;i++)
{
	a[i] = read();
	if(a[i]<0&&b[tot]>0 || a[i]>0&&b[tot]<0)b[++tot] = a[i];
	else b[tot] += a[i];
}
```
这样就行啦。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
using namespace std;

int read()
{
	int ret = 0,k = 1;char c = getchar();
	for(;c < '0' || c > '9';c = getchar())if(c == '-')k = -1;
	for(;c >= '0' && c <= '9';c = getchar())ret = ret*10+c-48;
	return ret*k;
}

int n,m,ans;
int a[N],b[N],tot = 1,cnt;
int l[N],r[N];
bool flag[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;

signed main()
{
	n = read(),m = read();
	for(int i = 1;i <= n;i++)
	{
		a[i] = read();
		if(a[i]<0&&b[tot]>0 || a[i]>0&&b[tot]<0)b[++tot] = a[i];
		else b[tot] += a[i];
	}
	for(int i = 1;i <= tot;i++)
	{
		if(b[i] > 0)cnt++,ans += b[i];
		q.push(make_pair(abs(b[i]),i));
		l[i] = i-1,r[i] = i+1;
	}
	l[0] = 0,r[0] = 1,l[tot+1] = tot,r[tot+1] = tot+1;
	while(cnt > m)
	{
		while(flag[q.top().second])q.pop();
		int u = q.top().second;q.pop();
		if(b[u] < 0 && (l[u] == 0 || r[u] == tot+1))continue;
		ans -= abs(b[u]),cnt--;
		b[u] += b[l[u]] + b[r[u]];
		flag[l[u]] = flag[r[u]] = 1;
		l[u] = l[l[u]],r[u] = r[r[u]];
		r[l[u]] = u,l[r[u]] = u;
		q.push(make_pair(abs(b[u]),u));
	}
	printf("%lld",ans);
	return 0;
}
```

---

