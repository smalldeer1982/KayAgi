# Fixed Point Removal

## 题目描述

Let $ a_1, \ldots, a_n $ be an array of $ n $ positive integers. In one operation, you can choose an index $ i $ such that $ a_i = i $ , and remove $ a_i $ from the array (after the removal, the remaining parts are concatenated).

The weight of $ a $ is defined as the maximum number of elements you can remove.

You must answer $ q $ independent queries $ (x, y) $ : after replacing the $ x $ first elements of $ a $ and the $ y $ last elements of $ a $ by $ n+1 $ (making them impossible to remove), what would be the weight of $ a $ ?

## 说明/提示

Explanation of the first query:

After making first $ x = 3 $ and last $ y = 1 $ elements impossible to remove, $ a $ becomes $ [\times, \times, \times, 9, 5, 4, 6, 5, 7, 8, 3, 11, \times] $ (we represent $ 14 $ as $ \times $ for clarity).

Here is a strategy that removes $ 5 $ elements (the element removed is colored in red):

- $ [\times, \times, \times, 9, \color{red}{5}, 4, 6, 5, 7, 8, 3, 11, \times] $
- $ [\times, \times, \times, 9, 4, 6, 5, 7, 8, 3, \color{red}{11}, \times] $
- $ [\times, \times, \times, 9, 4, \color{red}{6}, 5, 7, 8, 3, \times] $
- $ [\times, \times, \times, 9, 4, 5, 7, \color{red}{8}, 3, \times] $
- $ [\times, \times, \times, 9, 4, 5, \color{red}{7}, 3, \times] $
- $ [\times, \times, \times, 9, 4, 5, 3, \times] $ (final state)

It is impossible to remove more than $ 5 $ elements, hence the weight is $ 5 $ .

## 样例 #1

### 输入

```
13 5
2 2 3 9 5 4 6 5 7 8 3 11 13
3 1
0 0
2 4
5 0
0 12```

### 输出

```
5
11
6
1
0```

## 样例 #2

### 输入

```
5 2
1 4 1 2 4
0 0
1 0```

### 输出

```
2
0```

# 题解

## 作者：OMG_wc (赞：20)

第一步很容易想到，把原数与其下标作差，即 $a_i=i-a_i$。

然后可以发现每次可以把值为 $0$ 的数去掉，去掉后其后面所有数都减去 $1$。并且值为负数的数是永远删不掉的。

关于删的顺序问题，尝试几种情况后容易发现：**在 $a_i\ge 0$ 时，若前面被删掉的数的个数 $\ge a_i$，$a_i$ 总能被删掉**。（先删后面不会影响前面，所以一定存在某种顺序能把 $a_i$ 删掉）。举个例子：作差后的序列为 $0,1,2,0,1,3,5$，删除的下标顺序为 $4,5,1,6,2,7,3$。

这样就不需要考虑删的具体顺序了。

对每个询问，前后各有若干位置不能被删，这就让问题变得恶心了。

如果只固定后缀位置，从头开始考虑，那还是容易模拟的。

现在起点不唯一了，一种解决的方法是：对所有询问离线处理（按照右端点排序），每次考虑到一个新的数 $a_r$ 时，用某个数据结构同时维护 $[f_1,f_2,\cdots,f_n]$，其中 $f_i$ 表示以 $i$ 为起点时能删掉的数的个数。

$[f_1,f_2,\cdots,f_n]$ 显然是单调递减的，那么 $a_r$ 只会在某个前缀部分里被删除。说的明白点，设被删除的最右边位置是 $k$，那么满足 $f_1\ge f_2 \ge \ldots \ge f_k \ge a_r > f_{k+1}\ge \ldots \ge f_n$。

我们需要用数据结构找到这个位置 $k$ ，然后把区间 $[1,k]$ 都加 $1$ 。

可以用树状数组来实现，$[1,k]$ 区间加 $1$ ，对应差分数组是 $d_1$ 加 $1$ ，$d_{k+1}$  减 $1$ 。每次都是 $d_1$ 加 $1$ ，那干脆只维护每个位置减 $1$ 的个数好了。那么怎么找 $k+1$ 呢？当前总共加的次数是 $r-1$ ，那么减的总数最多到 $r-1-a_r$ 还是可以满足 $f_i \ge a_r$  的，也就是说这个分界点 $k+1$ 在第 $r-1-a_r+1$ 个减一操作的位置。那么用树状数组求第 $K$ 小来找这个位置即可。

参考代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 300005;
int a[N];

int c[N];
int sum(int x) {
    int res = 0;
    while (x) {
        res += c[x];
        x -= x & -x;
    }
    return res;
}
void add(int x, int d, int n) {
    while (x <= n) {
        c[x] += d;
        x += x & -x;
    }
}
int kth(int k, int n) {
    int x = 0;
    for (int i = 1 << 18; i; i >>= 1) {
        if (x + i <= n && k - c[x + i] > 0) {
            x += i;
            k -= c[x];
        }
    }
    return x + 1;
}
struct Node {
    int x, y, id;
} b[N];
bool cmp(Node p1, Node p2) {
    return p1.y < p2.y;
}
int ans[N];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] = i - a[i];
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &b[i].x, &b[i].y);
        b[i].x = 1 + b[i].x;
        b[i].y = n - b[i].y;
        b[i].id = i;
    }
    sort(b, b + m, cmp);
    int pos = 1;
    for (int i = 0; i < m; i++) {
        while (pos <= b[i].y) {
            int k = a[pos] < 0 ? 1 : min(kth(pos - a[pos], n), pos + 1);
            add(k, 1, n);
            pos++;
        }
        ans[b[i].id] = b[i].y - sum(b[i].x);
    }
    for (int i = 0; i < m; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
```









---

## 作者：Alex_Wei (赞：13)

> [题面传送门](https://www.luogu.com.cn/problem/CF1404C)。

> 题意简述：给定序列 $a$，你可以删除 $a_i$ 当且仅当 $a_i=i$。多次询问 $x,y$，求出如果固定前 $x$ 个数和后 $y$ 个数，那么最多能删除多少个数。

---

单次询问无限制（$x=y=0$）。

不难发现，一旦 $a_i>i$，那么这个数永远也无法被删除，而**删除最右边的能被删除的数不会影响答案**。所以我们维护一个序列 $b_i$ 表示如果要删除 $a_i$，那么至少要删除 $b_i$ 个 $a_i$ 前面的数，显然：

$$b_i=\begin{cases}\infty\quad&(a_i>i)\\i-a_i&(a_i\leq i)\end{cases}$$

每次找到序列 $b$ 中最大的 $i$ 满足 $b_i=0$，将其删除，设置 $b_i=\infty$ 并将 $b_{i+1},b_{i+2},\cdots,b_n$ 减去 $1$，直到 $\max b_i>0$，则删除的数的个数即为答案。这一操作可以用支持单点修改，区间加减，区间求最小值的 lazytag 线段树完成。

---

单次询问有限制。

对于每一个删除的 $a_i$，考虑 $i$ 是否不大于 $y$ 即可。

或者再维护一个序列 $c_i$，表示 $a_i$ 能否被删除，则答案为

$$\sum_{i=x+1}^{y} c_i$$

---

多次询问有限制。

不妨先将所有数固定，然后从后往前添加可以操作的数，每添加一个数都进行不断找到最右边的 $0$ 的操作，并更新 $c_i$。

方法 1：因为每次添加可以操作的数都要用一个线段树维护 $c$，且每个版本的线段树是直接在前一版本的线段树上修改，所以使用主席树即可。

方法 2：将询问离线后按照 $x$ 从大到小排序并一一回答，这样直接用支持单点修改，区间查询的树状数组维护 $c$ 即可。

```cpp
const int N=3e5+5;

int n,q,a[N],val[N<<2],tag[N<<2],ans[N];

struct query{
	int x,y,id;
	bool operator < (const query &v) const {
		return x>v.x;
	}
}c[N];

void push(int x){
	if(tag[x]){
		val[x<<1]-=tag[x];
		val[x<<1|1]-=tag[x];
		tag[x<<1]+=tag[x];
		tag[x<<1|1]+=tag[x];
		tag[x]=0;
	}
}

void add(int l,int r,int pos,int x,int v){
	if(l==r){
		val[x]=v;
		return;
	} int m=l+r>>1; push(x);
	if(pos<=m)add(l,m,pos,x<<1,v);
	else add(m+1,r,pos,x<<1|1,v);
	val[x]=min(val[x<<1],val[x<<1|1]);
}

int querypos(int l,int r,int p,int x){
	if(l==r&&val[x]>0)return 1e9;
	if(l==r&&val[x]==0)return l;
	int m=l+r>>1,ans; push(x);
	if(m<p)ans=querypos(m+1,r,p,x<<1|1);
	else if(val[x<<1|1]==0)ans=querypos(m+1,r,p,x<<1|1);
	else ans=querypos(l,m,p,x<<1);
	val[x]=min(val[x<<1],val[x<<1|1]);
	return ans;
}

void modify(int l,int r,int ql,int qr,int x){
	if(ql>qr)return;
	if(ql<=l&&r<=qr){
		val[x]--,tag[x]++;
		return;
	} int m=l+r>>1; push(x);
	if(ql<=m)modify(l,m,ql,qr,x<<1);
	if(m<qr)modify(m+1,r,ql,qr,x<<1|1);
	val[x]=min(val[x<<1],val[x<<1|1]);
}

int d[N];
void add(int x){while(x<=n)d[x]++,x+=x&-x;}
int query(int x){int ans=0; while(x)ans+=d[x],x-=x&-x; return ans;}

void solve(){
	cin>>n>>q; mem(val,0x3f);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=q;i++)cin>>c[i].x>>c[i].y,c[i].id=i;
	sort(c+1,c+q+1);
	int p=1; 
	for(int i=n;i;i--){
		add(1,n,i,1,a[i]>i?1e9:i-a[i]);
		while(val[1]==0){
			int pos=querypos(1,n,i,1);
			add(pos),add(1,n,pos,1,1e9),modify(1,n,pos+1,n,1);
		}
		while(p<=q&&c[p].x==i-1){
			ans[c[p].id]=query(n-c[p].y);
			p++;
		}
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<endl;
}
```

---

## 作者：onglu (赞：7)

# Codeforces Round #668 (Div. 1)  
## C. Fixed Point Removal
***
## update  

之前代码有误现在已经更正  
***
### 题目大意  
给定一个长度为$n$的序列，一次删除操作可以进行当且仅当$a[i] = i$,$i$为这个元素到这个序列头的距离。  

注意进行删除操作后序列会重新拼接起来。  

定义一个序列的权重为最多删除的元素个数。  

$q$次询问，每次询问为一个子段。  

每个询问输出子段的权重。  

### 思路  
由于每个位置删除的条件不同，可以想到我们要统一删除条件，即$a[i]\ -\ i\ = 0$  
这样只要我们每个位置$a[i]$变为$i\ -\ a[i]$只需要看当前位置是否为$0$即可。  
假如我们删除一个数，对后面数的影响显然是所有的$a[k](k > qi)$都减去$1$。  
  
可以记$f[i,j]$为序列$(i,j)$的答案，显然可以从$f(i,j)$递推到$f(i, j + 1)$。假如之前删除的数大于$a(i)$那么必然可以构造一种方法使$a(i)$先被删除，并且不影响前面的数的删除，于是就有  
$$f(i,j + 1) = f(i,j) + 1 \ \ \ (if\ f(i,j) \geq a(j+1))$$  
  
这样子就发现起点相同的时候终点可以递推，我们的想法是确定终点$r$，然后维护所有的$f(i,r)$，显然序列越长答案越大，那么$f(1,r)$到$f(r,r)$是单调递减的，可以二分找到第一个$f(j,r) \geq a(r+1)$的位置。  

接下来要处理的就是单点查询以及区间修改，用差分树状数组就可以处理。  
时间复杂度为$O((n + q)log^2n)$

### 代码  
```cpp
#include <bits/stdc++.h>
#define Mid ((l + r) >> 1)

using namespace std;

const int N = 3e5 + 1009;
int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}
int n, q, ans[N], a[N], t[N];
vector<int>GET[N], id[N];
void modify(int x, int f){
	for(;x <= n; x += x & -x)
		t[x] += f;
}
int query(int x){
	int ans = 0;
	for(;x; x -= x & -x)
		ans += t[x];
	return ans;
}
int main()
{
	n = read(); q = read();
	for(int i = 1; i <= n; i++)
		a[i] = i - read();
	for(int i = 1; i <= q; i++){
		int l = read() + 1, r = n - read();
		GET[r].push_back(l);
		id[r].push_back(i);
	}
	for(int i = 1; i <= n; i++){
		if(a[i] > 0){
			int l = 1, r = i - 1;
			while(l <= r){
				if(query(Mid) < a[i])r = Mid - 1;
				else l = Mid + 1;
			}
			if(r >= 1){
				modify(1, 1); modify(r + 1, -1);
			}
		}
		if(!a[i]){
			modify(1, 1), modify(i + 1, -1);
		}
		for(int j = 0; j < GET[i].size(); j++)
			ans[id[i][j]] = query(GET[i][j]);
	}
	for(int i = 1; i <= q; i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：feecle6418 (赞：6)

不难发现最优策略是每次选择能删的中最右边的那一个删，可以保证所有能删的全部删完。

记 $c_i$ 为 $i-a_i$（若小于 $0$ 则视为 $10^9$），$s_i$ 为 $i$ 左边能删的个数，则 $s_i=s_{i-1}+[s_{i-1}\ge c_i]$。这样，我们就得到了一个 $O(qn)$ 的做法：每次对区间内求一遍 $s$ 即可。

考虑优化这个做法。离线询问，按左端点从右到左扫描。假如某个数（设为 $a_w$）原来不能删，现在可以删，那么会对 $[w+1,n]$ 的所有 $s$ 造成 $1$ 的贡献。而这时又可能会有新的 $w$ 产生，需要重复这一过程。不难发现，每次取最左边的可行的 $w$ 总是最优。

“可以删”的条件 $s_{i-1}\ge c_i$ 可以转化为 $i$ 的 $s$ 被更新的次数 $\ge c_i$。相当于，在更新 $s$ 时顺便让 $c$ 减一，假如小于等于 $0$ 则说明可以作为新的 $w$。每个数至多只会被用来更新一次，因此假如用线段树上二分来实现的话，复杂度是 $O((n+q)\log n)$。代码中使用的是二分再加上线段树，复杂度是 $O(n\log ^2n+q\log n)$，仍然能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[300005],ans[300005],tag[1200005];
struct P{
	int mx,sum,len;
}t[1200005];
P operator +(P a,P b){
	return {max(a.mx,b.mx),a.sum+b.sum,a.len+b.len};
}
struct Query{
	int r,id;
};
vector<Query> q[300005];
void Build(int p,int l,int r){
	if(l==r)return t[p]={(a[l]>=0?-a[l]:-(1<<30)),0,1},void();
	int mid=(l+r)/2;
	Build(p*2,l,mid),Build(p*2+1,mid+1,r);
	t[p]=t[p*2]+t[p*2+1];
}
void Tag(int p,int x){
	tag[p]+=x,t[p].sum+=t[p].len*x,t[p].mx+=x;
}
void Pushdown(int p){
	if(tag[p])Tag(p*2,tag[p]),Tag(p*2+1,tag[p]),tag[p]=0;
}
void Add(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return Tag(p,1),void();
	Pushdown(p);
	int mid=(l+r)/2;
	if(x<=mid)Add(p*2,l,mid,x,y);
	if(mid<y)Add(p*2+1,mid+1,r,x,y);
	t[p]=t[p*2]+t[p*2+1];
}
void Upd(int p,int l,int r,int x){
	if(l==r)return t[p]={-(1<<30),t[p].sum,1},void();
	Pushdown(p);
	int mid=(l+r)/2;
	if(x<=mid)Upd(p*2,l,mid,x);
	else Upd(p*2+1,mid+1,r,x);
	t[p]=t[p*2]+t[p*2+1];
}
int Que(int p,int l,int r,int x){
	if(l==r)return t[p].sum;
	Pushdown(p);
	int mid=(l+r)/2;
	if(x<=mid)return Que(p*2,l,mid,x);
	else return Que(p*2+1,mid+1,r,x);
}
P Que2(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return t[p];
	Pushdown(p);
	int mid=(l+r)/2;
	if(x>mid)return Que2(p*2+1,mid+1,r,x,y);
	if(y<=mid)return Que2(p*2,l,mid,x,y);
	return Que2(p*2,l,mid,x,y)+Que2(p*2+1,mid+1,r,x,y);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]=i-a[i];
	//for(int i=1;i<=n;i++)cout<<a[i]<<'\n';
	for(int i=1,x,y;i<=m;i++)scanf("%d%d",&x,&y),q[1+x].push_back({n-y,i});
	Build(1,1,n);
	for(int i=n;i>=1;i--){
		while(1){
			int l=i,r=n,ans=n+1;
			while(l<=r){
				int mid=(l+r)/2;
				if(Que2(1,1,n,i,mid).mx>=0)ans=mid,r=mid-1;
				else l=mid+1;
			}
			if(ans==n+1)break;
			Add(1,1,n,ans,n);
			Upd(1,1,n,ans);
			//cout<<i<<' '<<ans<<endl;
		}
		for(Query j:q[i])ans[j.id]=Que(1,1,n,j.r);
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：gyh20 (赞：4)

~~快去把Fee_cle6418的两只 log hack了~~

首先，因为后面的数不会对前面产生影响，我们可以离线询问，然后从后往前处理。

对于每一个 $a_i$，变为 $i-a_i$，若 $a_i\geq 0$，则说明 若 $i$ 被删了 $a_i$ 个数，则这个数可以被删。

于是就变得很明确了。

用一个树状数组记录被删的位置，处理询问，用一棵线段树记录初始值 $\geq0$ 的 $a_i$，每次删掉一个数（$a_i=0$）相当于在之后的 $a_i$ 都减一，然后如果存在小于等于 $0$ 的数直接连锁反应即可。可以用最小值和位置标记解决。

时间 $O(n\log n)$，具体可以见代码吧。

```
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t; 
}
int t,n,m,a[1000002],ans[1000002],c[1000002];
inline void add(re int x){
	for(;x<=n;x+=x&(-x))++c[x];
}
inline int ask(re int x){
	int sum=0;
	for(;x;x-=x&(-x))sum+=c[x];
	return sum;
}
vector<int>qry[1000002],b[1000002],id[1000002];
bool vis[300002];
int mn[1200002],mnp[1200002],pos,sans,tg[1200002];
inline void del(re int p,re int x){
	tg[p]+=x;mn[p]-=x;
}
inline void pd(re int p){
	if(tg[p]){
		del(p<<1,tg[p]),del(p<<1|1,tg[p]);
		tg[p]=0; 
	}
}
inline void ins(re int p,re int l,re int r,re int x,re int y){
	if(l==r){
		mn[p]=y;mnp[p]=l;
		return;
	}pd(p);
	re int mid=l+r>>1;
	if(x<=mid)ins(p<<1,l,mid,x,y);
	else ins(p<<1|1,mid+1,r,x,y);
	if(mn[p<<1]<mn[p<<1|1])mn[p]=mn[p<<1],mnp[p]=mnp[p<<1];
	else mn[p]=mn[p<<1|1],mnp[p]=mnp[p<<1|1];
}
inline void query(re int p,re int l,re int r,re int x,re int y){
	if(l>=x&&r<=y){
		if(mn[p]<sans)sans=mn[p],pos=mnp[p];
		return;
	}
	pd(p);
	re int mid=l+r>>1;
	if(x<=mid)query(p<<1,l,mid,x,y);
	if(y>mid)query(p<<1|1,mid+1,r,x,y);
}
inline void del(re int p,re int l,re int r,re int x,re int y){
	if(l>=x&&r<=y){
		del(p,1);
		return;
	}
	pd(p);
	re int mid=l+r>>1;
	if(x<=mid)del(p<<1,l,mid,x,y);
	if(y>mid)del(p<<1|1,mid+1,r,x,y);
	if(mn[p<<1]<mn[p<<1|1])mn[p]=mn[p<<1],mnp[p]=mnp[p<<1];
	else mn[p]=mn[p<<1|1],mnp[p]=mnp[p<<1|1];
}
int main(){
	re int bs=0;
	memset(mn,0x3f,sizeof(mn));
	n=read(),m=read();
	for(re int i=1;i<=n;++i)a[i]=i-read();
	for(re int i=1,x,y;i<=m;++i){
		x=read(),y=read();
		qry[x+1].push_back(n-y);
		id[x+1].push_back(i);
	}
	for(re int i=n;i;--i){
		if(!a[i])add(i),del(1,1,n,i+1,n);
		else if(a[i]>0)ins(1,1,n,i,a[i]);
		while(1){
			sans=1e9;
			query(1,1,n,1,n);
			if(sans<=0){
				add(pos);
				ins(1,1,n,pos,1e9);
				del(1,1,n,pos+1,n);
			}
			else break;
		}
		//for(re int j=i+1;j<=n;++j)if((!vis[j]))&&a[j]>0&&a[j]<=ask(j))add(j); 
		for(re int j=0;j<qry[i].size();++j)ans[id[i][j]]=ask(qry[i][j]);
	}
	for(re int i=1;i<=m;++i)printf("%d\n",ans[i]);
}
```


---

## 作者：FReQuenter (赞：2)

好难想啊（

先来几个 $\text{Hints}$。

1. 删除时优先删靠后的，因为不会对前面产生影响。

2. 每一个数需要前面删除 $a_i-i$ 个数才能被删掉。

3. 一个数前面被锁定的数越少，越容易被删掉。

怎样简单地、容易想出解法地表示我们想知道的东西？

换一个角度想，我们要求的也就是每一个数要被删掉前面至多被锁定了几个，设为 $\lim_i$。

$\lim$ 满足单调性，可以二分。

对于每一个 $i$，二分一个 $\text{mid}$，使得 $\lim_{mid+1}>a_i>\lim_{mid}$。

其实这个本质上是一个二位数点，用树状数组维护。直接二分的话是 $n\log^2n$ 的。我们可以树状数组上二分把复杂度降到 $n\log n$。不过前一种写法同样可过。

接下来就是统计答案。把询问离线下来排个序就行。

[Code](https://www.luogu.com.cn/paste/fx0ikqa0)。

---

## 作者：chenxia25 (赞：2)

这是我所做不出来的题目。我什么时候才能 GM 啊？让我回个 IM 也好嘛！

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/CF1404C ) & [CF 题目页面传送门]( https://codeforces.com/contest/1404/problem/C )
>
> 题意见洛谷。

首先探索一个下标序列能够全部被删除的充要条件。我们设 $b_i=i-a_i$，那么任意时刻，显然 $a_i$ 能被删掉当且仅当 $b_i=0$。于是我们盯着这个 $b$ 看：一开始肯定要有一个先驱者 $b_i=0$ 对不对，然后删除之后就可以让后面的 $b$ 值都减去 $1$。一个 $b_i$，如果它 $<0$ 那显然没救了；如果 $\geq 0$ 那么只需要将它减去 $b_i$ 次 $1$ 就变成 $0$ 可以被删掉了。也就是说一个 $b_i\geq 0$ 的位置 $i$ 要被删掉必须满足前面有 $b_i$ 个已经被删掉了。于是我们得到了一个必要条件：下标序列 $c$ 能被全部删掉仅当 $c_i\leq i-1$。

然后随便 van van 发现这个也满足充分性的，只需要构造出一个方案即可证明。那么方案很好构造，就每次删掉 $c$ 中最右边满足 $b_{c_i}=0$ 的 $c_i$ 即可。

然后再对询问进行一番显然的转化：每组询问 $x,y$ 相当于求 $b$ 上的区间 $[l=x+1,r=n-y]$ 的最长能被 $[0,1,2,3,\cdots]$ 所「覆盖」的子序列长度。就变成了一个看上去很清新的 DS 题。

如何求呢？？

暂时想不到直接对区间维护的，不妨假设区间左端点固定，来求（这个其实是老套路了）。那么可以维护以每个位置为最后一位的最长子序列长度 $-1$，这是一个 $\mathrm O(n)$ 的数列对吧。如何求这个数列很容易，类似 DP 的，当前位置 $i$ 答案为 $x$ 要满足两个条件：

1. 前面有 $x-1$ 长度的，即 $\max\limits_{j=1}^{i-1}\{dp_j\}\geq x-1$；
2. 当前这位要满足，即 $x\geq a_i$。

综合起来就是 $x\in\left[a_i,\max\limits_{j=1}^{i-1}\{dp_j\}+1\right]$。要取最长的，于是如果区间不为空就取右端点，如果为空就设一个错误值，比如 $-\infty$ 吧。然后如果光是左端点固定的话，这个很显然是可以 $\mathrm O(n)$ 的。可惜固定不得。

于是考虑从右往左枚举左端点，相当于依次 push_front 然后维护整个 DP 数组（跟上面套路配套的套路）。考虑如何维护。

显然任意时刻 DP 数组是在 $[0,1,2,3,\cdots]$ 里面插若干个 $-\infty$ 这个形式。然后发现在往前面 push 的过程中，push 的是 $0$，所以这个自然数序列要往后顺移，即全体加 $1$。然后所有 $-\infty$ 当年所对应的区间也在加 $1$，慢慢加的话可能有朝一日能使那个区间不为空，重获新生。又显然最多会有 $n$ 次重获新生的说，所以这个就暴力修改就可以了（每个时刻从前往后依次修改，每次修改还要附带后缀加 $1$）。那么如何每次快速找到复活的人们呢？而且不仅要找到，还要每次找到的是最前面的？维护一个线段树，然后线段树二分即可。

最后，这个「老套路」离线 + 线段树实现是比较方便的，但是注意到每次是在前一个历史版本上直接修改，也可以用主席树预处理来实现回答询问的在线，不过我不会，而且也很简单的样子，不管了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int inf=0x3f3f3f3f;
const int N=300000,QU=N;
int n,qu;
int a[N+1];
struct query{int l,r;}qry[QU+1];
vector<int> pos[N+1];
int ans[QU+1];
struct segtree{
	struct node{int l,r,dif,rl,lz;}nd[N<<2];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define dif(p) nd[p].dif
	#define rl(p) nd[p].rl
	#define lz(p) nd[p].lz
	void bld(int l=1,int r=n,int p=1){
		l(p)=l;r(p)=r;dif(p)=rl(p)=-inf;lz(p)=0;
		if(l==r)return;
		int mid=l+r>>1;
		bld(l,mid,p<<1);bld(mid+1,r,p<<1|1);
	}
	void init(){bld();}
	void sprup(int p){dif(p)=max(dif(p<<1),dif(p<<1|1));rl(p)=max(rl(p<<1),rl(p<<1|1));}
	void sprdwn(int p){
		if(lz(p)){
			dif(p<<1)+=lz(p);rl(p<<1)+=lz(p);lz(p<<1)+=lz(p);
			dif(p<<1|1)+=lz(p);rl(p<<1|1)+=lz(p);lz(p<<1|1)+=lz(p);
			lz(p)=0;
		}
	}
	void chg(int x,int v1,int v2,int p=1){
		if(l(p)==r(p))return dif(p)=v1,rl(p)=v2,void();
		sprdwn(p);
		int mid=l(p)+r(p)>>1;
		chg(x,v1,v2,p<<1|(x>mid));
		sprup(p);
	}
	void add(int l,int r,int v,int p=1){
		if(l>r)return;
		if(l<=l(p)&&r>=r(p))return dif(p)+=v,rl(p)+=v,lz(p)+=v,void();
		sprdwn(p);
		int mid=l(p)+r(p)>>1;
		if(l<=mid)add(l,r,v,p<<1);
		if(r>mid)add(l,r,v,p<<1|1);
		sprup(p);
	}
	int mx(int l,int r,int p=1){
		if(l<=l(p)&&r>=r(p))return rl(p);
		sprdwn(p);
		int mid=l(p)+r(p)>>1,res=-inf;
		if(l<=mid)res=max(res,mx(l,r,p<<1));
		if(r>mid)res=max(res,mx(l,r,p<<1|1));
		return res;
	}
	int fst(){
		int p=1;
		if(dif(p)<0)return 0;
		while(l(p)<r(p)){
			sprdwn(p);
			if(dif(p<<1)>=0)p=p<<1;
			else p=p<<1|1;
		}
		return l(p);
	}
}segt;
int main(){
	cin>>n>>qu;
	for(int i=1;i<=n;i++)scanf("%d",a+i),a[i]=i-a[i];
	for(int i=1;i<=qu;i++)scanf("%d%d",&qry[i].l,&qry[i].r),qry[i].l++,qry[i].r=n-qry[i].r,pos[qry[i].l].pb(i);
	segt.init();
	for(int i=n;i;i--){
		if(a[i]==0){
			segt.chg(i,-inf,0);segt.add(i+1,n,1);
			int fd;
			while(fd=segt.fst()){
				segt.chg(fd,-inf,segt.mx(1,fd-1)+1);segt.add(fd+1,n,1);
			}
		}
		else if(a[i]>0)segt.chg(i,-a[i],-inf);
		for(int j=0;j<pos[i].size();j++)ans[pos[i][j]]=max(0,segt.mx(1,qry[pos[i][j]].r)+1);
	}
	for(int i=1;i<=qu;i++)printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：AFOier (赞：1)

注：下文中的$l,r$指可以移除数字的区间，而非输入格式中的$l,r$

移除一个数可以使序列集体左移，但不可能右移，于是$a_i>i$一定不会被移除。

考虑暴力，令$num_i$表示$i$之前(含)能被移除的数的个数，

则如果$i-num_{i-1}(num_i) \leq a_i \leq i$,则这个数能被删除，$num_i=num_{i-1}+1$,否则$num_i=num_{i-1}$

答案为$num_r$，这样我们就有$O(n^2)$的做法了。

```
//这不是AC代码!
#include <bits/stdc++.h>
using namespace std;
int n, q, l, r, a[300011], num[300011];
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= q; i++) {
		scanf("%d%d", &l, &r);
		r = n - r; l++;
		num[l-1] = 0;
		for(int j = l; j <= r; j++) {
			num[j] = num[j-1];
			if(j >= a[j] && j - num[j-1] <= a[j]) num[j]++;
		}
		printf("%d\n", num[r]);
	}
	return 0;
} //TLE on test 6
```

如何优化这个做法呢？我们发现对于一个数，它只能被移除一次。

于是我们想到了离线，将$l$端点按从大到小排序，依次加入处理。

一个数被移除，会使它后面的数的$num \gets num+1$

上文中的$i-num[i] \leq a[i]$移项得到$i-a[i]-num[i] \leq 0$，我们用线段树维护这个值。

每当一个数能被移除，就对后面的值全部$-1$，并查找是否有$\leq 0$的数（最靠左），如果有就重复这个操作。

查询时可以再开一个树状数组/线段树，把移除值的位置赋为$1$,再做区间求和即可。

因为每个数只会被移除一次，所以复杂度为$O(n \log n)$。

```
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e6;
int n, m, a[300011], num[300011];
struct ques {
	int l, r, id, ans;
} q[300011];
bool cmp1(const ques p1, const ques p2) {return p1.l > p2.l;}
bool cmp2(const ques p1, const ques p2) {return p1.id < p2.id;}
struct segment_tree {
	int minn[1200011], tag[1200011]; 
	void build(int k, int l, int r) {
		minn[k] = inf; tag[k] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(k*2, l, mid); build(k*2+1, mid+1, r);
	}
	void pushdown(int k) {
		if(tag[k]) {
			minn[k*2] += tag[k];
			minn[k*2+1] += tag[k];
			tag[k*2] += tag[k];
			tag[k*2+1] += tag[k];
			tag[k] = 0;
		}
	}
	void modify(int k, int l, int r, int w, int s) {
		if(l == r) {
			minn[k] = s;
			return;
		}
		pushdown(k);
		int mid = (l + r) >> 1;
		if(w <= mid) modify(k*2, l, mid, w, s);
		else modify(k*2+1, mid+1, r, w, s);
		minn[k] = min(minn[k*2], minn[k*2+1]);
	} //单点赋值
	void Modify(int k, int l, int r, int L, int R) {
		if(l > R || r < L) return;
		if(l >= L && r <= R) {
			tag[k]--; minn[k]--;
			return;
		}
		pushdown(k);
		int mid = (l + r) >> 1;
		Modify(k*2, l, mid, L, R);
		Modify(k*2+1, mid+1, r, L, R);
		minn[k] = min(minn[k*2], minn[k*2+1]);
	} //区间-1 
	int find(int k, int l, int r) {
		if(l == r) {
			if(minn[k] <= 0) return l;
			return 0;
		}
		pushdown(k);
		int mid = (l + r) >> 1;
		if(minn[k*2] <= 0) return find(k*2, l, mid);
		else if(minn[k*2+1] <= 0) return find(k*2+1, mid+1, r);
		return 0;
	}
} t;
struct TA {
	int s[300011];
	int lowbit(int sum) {
		return sum & -sum;
	}
	void add(int w) {
		for(int i = w; i <= n; i += lowbit(i)) 
			s[i]++;
	}
	int query(int w) {
		int ret = 0;
		for(int i = w; i; i -= lowbit(i))
			ret += s[i];
		return ret;
	}
} T;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].r = n-q[i].r; q[i].l++; q[i].id = i;
		q[i].ans = 0;
	}
	sort(q+1, q+m+1, cmp1); int w = n+1;
	t.build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		while(w > q[i].l) {
			-- w; if(w < a[w]) continue;
			t.modify(1, 1, n, w, w - a[w]);
		}
		int pos;
		while(pos = t.find(1, 1, n)) {
			T.add(pos); 
			t.modify(1, 1, n, pos, inf); //移除后就不能再移除，赋值inf
			t.Modify(1, 1, n, pos+1, n); 
		}
		q[i].ans = T.query(q[i].r);
	}
	sort(q+1, q+m+1, cmp2);
	for(int i = 1; i <= m; i++)
		printf("%d\n", q[i].ans);
	return 0;
}
```

---

## 作者：眠ㅤㅤㅤ (赞：1)


提供一个在线做法。

显然$\ ($，对于区间 $[l,r]$ 的 $a_i$ $(l\leq i \leq r)$ 有以下结论$:$   
①$.\ a_i>i$，$a_i$ 一定不能移除  
②$.\ a_i=i$，$a_i$ 一定能移除  
③$.\ a_i<i$，若 $[l,i)$ 存在至少 $i-a_i$ 个可移除的数，则 $a_i$ 一定能移除  
④$.\ $定义 $p_i$ 为最后一个使得 $a_i$ 可移除的的下标，则一个区间 $[l,r]$ 可移除的下标集为 $\{\ i\ |\ p_i\geq l\ \}$，区间可移除的个数为该集合大小 。

$\ a_i>i \ \Rightarrow\ p_i=0$  
$\ a_i=i \ \Rightarrow\ p_i=i$  
$\ a_i<i$，根据 $③$ 二分一个最大的 $m$, 使得 $[m,i)$ 存在至少 $i-a_i$ 个 可以移除的数，即满足 $p_j \geq m$ $(m\leq j<i)$ 的数，若存在这个 $m$，则 $p_i=m$，否则 $p_i=0$。

主席树维护 $p_i$ 即可。

时间复杂度$O(nlognlogn+qlogn)$。


```cpp
constexpr auto Inf = 0X3F3F3F3F;
#ifndef LOCAL
	#include <bits/stdc++.h>
#endif

typedef long long LL;
using namespace std;

namespace IO {
	inline LL read() {
		LL o = 0, f = 1; char c = getchar();
		while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
		while (c > '/' && c < ':') { o = o * 10 + c - '0'; c = getchar(); }
		return o * f;
	}
	inline char recd() {
		char o; while ((o = getchar()) < '0' || o > '9'); return o;
	}
	inline double reod() {
		double o = read(), f = 1; char c;
		while ((c = getchar()) > '/' && c < ':') o += (c - '0') / (f *= 10);
		return o;
	}
}
using namespace IO;

const int SIZE = 3E5 + 7, Mod = 1E9 + 7;

struct Node {
	int L, R, w;
} Node[SIZE << 6]; int Root[SIZE], Ind;

void Ins(int pRoot, int& sRoot, int L, int R, int pos) {
	sRoot = ++Ind, Node[sRoot] = Node[pRoot], Node[sRoot].w++;
	if (L == R) return;
	int M = (L + R) >> 1;
	if (pos > M) Ins(Node[pRoot].R, Node[sRoot].R, M + 1, R, pos);
	else Ins(Node[pRoot].L, Node[sRoot].L, L, M, pos);
}

int Ask(int pRoot, int sRoot, int L, int R, int w) {
	if (L >= w) return Node[sRoot].w - Node[pRoot].w;
	int M = (L + R) >> 1;
	if (w > M) return Ask(Node[pRoot].R, Node[sRoot].R, M + 1, R, w);
	else return Ask(Node[pRoot].L, Node[sRoot].L, L, M, w) + Ask(Node[pRoot].R, Node[sRoot].R, M + 1, R, w);
}

int main() {
	int N = read(), M = read();
	for (int pos = 1; pos <= N; pos++) {
		int w = read();
		if (w > pos) Ins(Root[pos - 1], Root[pos], 0, N, 0);
		else if (w == pos) Ins(Root[pos - 1], Root[pos], 0, N, pos);
		else {
			int L = 1, R = pos - 1, M, res = 0;
			while (L <= R) {
				M = (L + R) >> 1;
				if (Ask(Root[M - 1], Root[pos - 1], 0, N, M) >= pos - w)
					res = M, L = M + 1;
				else 
					R = M - 1;
			} Ins(Root[pos - 1], Root[pos], 0, N, res);
		}
	}

	int L, R;
	while (M--) {
		L = read(), R = read();
		printf("%d\n", Ask(Root[L], Root[N - R], 0, N, L + 1));
	}
}
```


---

## 作者：whiteqwq (赞：1)

[CF1404C Fixed Point Removal](https://www.luogu.com.cn/problem/CF1404C)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1812332)

## 题意

给定长为 $n$ 的序列 $a$，一次操作可以删除一个满足 $a_i=i$ 的位置 $i$，同时之后的数向前移动一位。
$q$ 次询问，每次给定 $x,y$，求不能删去前 $x$ 个元素与后 $y$ 个元素的情况下最多能删除多少元素。（$1\leqslant n\leqslant 3\times 10^5$）

## 分析

套路题。

观察数据范围可知算法复杂度差不多是单 $\log$，根据套路，我们将询问挂在右端点上，并从左往右扫，用数据结构维护左端点为 $i$ 时的答案。

具体地，我们记 $v_i$ 为可以删除的区间左端点为 $i$ 时，有多少个点无法删除，可以发现加入一个点后我们只需要计算其对一段后缀的贡献。

扫描到 $i$ 时，若 $i<a_i$，不难发现其一定无法删除，于是直接全局加一。否则，我们二分一个位置使得其前面已经有 $a_i$ 个无法删除的位置，将这个位置对应的后缀与 $i+1$ 对应的后缀取并并直接更新。

这种操作用树状数组可以轻松维护，二分的时候在树状数组上二分就可以了，时间复杂度 $O(n\log n)$。

## 代码

```
#include<stdio.h>
#include<vector>
#define lowbit(x) x&-x
using namespace std;
const int maxn=300005;
int n,m;
int a[maxn],ans[maxn],t[maxn];
vector< pair<int,int> >v[maxn];
void update(int x,int v){
	for(int i=x;i<=n;i+=lowbit(i))
		t[i]+=v;
}
int query(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=t[i];
	return res;
}
int getkth(int k){
	int res=0;
	for(int i=18;i>=0;i--)
		if(res+(1<<i)<=n&&k>t[res+(1<<i)])
			k-=t[res+(1<<i)],res+=(1<<i);
	return res+1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		x++,y=n-y;
		if(x<=y)
			v[y].push_back(make_pair(x,i));
	}
	for(int i=1,tot=0;i<=n;i++){
		if(i-a[i]>=0){
			tot++;
			int pos=getkth(a[i]);
			if(pos<=i)
				update(pos,1);
			else update(i+1,1);
		}
		for(int j=0;j<v[i].size();j++)
			ans[v[i][j].second]=tot-query(v[i][j].first);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

本场全部题解可见：[Codeforces Round 1404考试总结](https://zybuluo.com/xiaoziyao/note/1812279)

---

## 作者：Fading (赞：1)

好久没写博客了，瞎写一下：

VP 了这场，结果这题一开始写了一个假算法，导致排名只有 240+ /kk ...

但是我的做法比其他人简单很多？不过转化比较多有点烧脑就是了。

首先考虑怎么单次查询。

设$i$前面已经删了$j$个，那么$i$能删当且仅当$i-j=a_i$。

发现这个东西有后效性，仿佛连 $O(n^2)$ dp 都做不了...那怎么办？

注意到一个性质，最后一个数删除对后面没有任何影响。

所以可以很自然的想到：开一个堆，每一次删除最后面的，再更新一下那些可以重新加入。这样就可以$O(n\log_2 n)$，强行优化可以$O(n)$。

多组询问？显然这个询问可以转化成$[l,r]$的区间查询。然后怎么方便维护？

~~发现最前面那个数可以最后删除，然后我就灵感爆发，写了莫队，一看时间限制 4s 马上开写，写着写着发现假了，当场去世。~~

单词查询这个做法启示了我们可以考虑最后一个数。考虑扫描线，维护$[l,r]$最多能删除多少次，如果次数$\geq i-a_i$，那么一定有一种方法可以删掉它。

接下来等价于需要维护一个数据结构，支持：

- 把大于 x 的数全部加上 1。

- 单点查询。

一看就很不正常，冷静一下发现这个答案是关于$l$单调递减的。那么每一次“把大于 x 的数全部加上 1”只需要区间加法即可。

那么使用线段树（区间加单点查询）+二分就做完了。时间复杂度$O(n\log_2^2 n)$，如果使用线段树上二分可以做到$O(n\log_2 n)$。当然时限 4s，随便过。

如果把每一个$r$的信息用主席树记录下来就可以做到强制在线了，时空复杂度都是$O(n\log_2 n)$。

---

## 作者：xzy090626 (赞：0)

树状数组做法。我们首先把所有询问按照右端点离线，从前往后处理，这样可以自然地忽略后面部分的影响，因为后面的删除不会影响前面。

然后就是考虑当前这个位置 $i$ 的 $a_i$ 能不能被移到 $a_i$ 的位置。
- 如果 $a_i>i$，显然不可能，因为不会向后移位；

- 如果 $a_i=i$，那显然就可以。

- 如果 $a_i<i$，那么要考虑前面可以删掉的数的个数是否 $\geq i-a_i$。

考虑如何快速处理一个位置前面可以删掉的数的个数，可以用树状数组维护可以删的位置，要处理的显然是单点加、区间和。事实上，我们需要的是二分一个位置使得刚好删掉它前面的某些数会提供给 $a_i$ 移到对应位置的机会。可以使用树状数组上二分，当然直接套一个二分的 $O(\log ^2n)$ 的查询也完全可以接受。

现在考虑怎么处理询问。既然已经固定了右端点，只需要对不同的左端点考虑即可。由于对于每个询问，前 $i$ 个数不可以动，所以查询 $[x+1,i]$ 的贡献即可。

---

## 作者：MuYC (赞：0)

#### 前言

提供一种小常数线段树 / 树状数组的做法。

你仅仅只需要会线段树区间 $+ 1$，区间取 $min$，单点查值，没了。

+ #### 暴力

题目每次相当于查询区间 $[x + 1, n - y]$ 的答案，不妨用 $L$ 代替 $x + 1$, $R$ 代替 $n - y$，即为求 $[L, R]$ 的答案。

套路性的设 $b_i = a_i - i$，删除第 $i$ 个数相当于使得 $j > i, b_j + 1$，可以删除一个数即其对应的 $b_i = 0$。所以说，对于一开始 $b_i > 0$ 的那些根本不需要考虑。

下面只考虑区间 $\forall i ∈[L,R], b_i \leq 0$ 的数。

假设区间 $[L,R]$ 中一开始有多个 $b_i = 0$，每次删除最右边的一定是最优的。关于这点，读者自证不难。

相当于说每次都选择最靠近右端点的 $b_i = 0$ 的数，倘若删掉一些数后出现了一些可以删除的数，那么下一次肯定优先删除出现的最右边的 $b_i = 0$ 的数。按照这种策略删除的话，对于每一个 $-b_i \leq s$ 都可以被删除，$s$ 是 $i$ 前面可以被删除的数的个数。

答案可以抽象为这样一个程序：

```cpp
ans = 0;
for(int i = L ; i <= R ; i ++)
ans += (-b[i] <= ans && b[i] <= 0);
```

但是这个程序的复杂度是 $O(n^2)$ 的，无法通过 $n \leq 2 \times 10^5$ 的数据范围，你会 $TLE$ $on$ $test$ $6$。考虑优化。

+ #### 优化

看题目猜复杂度 : $O(n \log n)$。

将询问离线下来，按照 $R$ 从小到大的顺序排序，我们每次向右移动当前右指针 $nowr$

考虑建立一棵线段树，我们每次移动区间的右端点，假设是 $nowr$ 其叶子节点 $[L,L]$ 存的值的表示的意义就是区间 $[L,nowr]$ 的答案，也就是相当于:

```cpp
ans = 0;
for(int i = L ; i <= nowr ; i ++)
ans += (-b[i] <= ans && b[i] <= 0);
```
得到的 $ans$ 。

考虑假如我们现在需要右移右端点，将 $nowr$ 变成 $nowr + 1$。

只要对于 $[L,nowr]$ 的答案大于等于 $-b[i]$ 的所有叶子节点的答案就会 $+ 1$。

首先我们可以发现这个 $ans$ 是具有单调性的，**对于同一个右端点，左端点越靠前的答案大于等于左端点靠后的**，所以可以二分。

当然了，直接二分的话，复杂度是 $O(q \log^2n)$ 的。但是我们可以在线段树上二分，倘若左儿子的最小值大于等于 $-b[i]$ ，就直接整个左儿子的权值 $+ 1$，同时往右儿子走。否则先不加，就往左儿子方向递归。这样下来复杂度就变成 $O(q \log n)$ 了。

对于询问的答案，假设当前问题的右端点 $R_i$ 恰好等于现在的右指针 $nowr$ ，就循环询问，单点求 $L_i$ 的值就是这个询问的答案了。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define mid ((T[x].l + T[x].r) >> 1)
inline int read() {
	int x = 0, flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}
const int MAXN = 3e5 + 50;
int n, m, b[MAXN], Ans[MAXN];
 
struct SegmentTree {
	int l, r, Min, laz;
} T[MAXN << 2];
 
struct Ques {
	int l, r, id;
} Q[MAXN];
void ad(int x, int k) { T[x].Min += k, T[x].laz += k; }
void update(int x) { T[x].Min = min(T[x << 1].Min, T[x << 1 | 1].Min); } 
bool cmp(Ques A, Ques B) { return A.r < B.r; }
void pushdown(int x) { ad(x << 1, T[x].laz), ad(x << 1 | 1, T[x].laz); T[x].laz = 0; }
 
void build(int x, int l, int r) {
	T[x].l = l, T[x].r = r, T[x].laz = 0;
	if(l == r) return ;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	return ;
}
 
void change(int x, int l, int r) { // 区间加法
	if(T[x].l >= l && T[x].r <= r) { ad(x, 1); return ; }
	pushdown(x);
	if(l <= mid) change(x << 1, l, r);
	if(r  > mid) change(x << 1 | 1, l, r);
	update(x);
	return ;
}
 
void modify(int x, int v) {
	if(T[x].l == T[x].r) { if(T[x].Min >= v) ad(x, 1); return ; }
	pushdown(x);
	if(T[x << 1].Min >= v) ad(x << 1, 1), modify(x << 1 | 1, v); // 线段树上二分
	else modify(x << 1, v);
	update(x);
	return ;
}
 
int GetAns(int x, int pos) { // 单点求值
	if(T[x].l == pos && T[x].r == pos) return T[x].Min;
	pushdown(x);
	if(pos <= mid) return GetAns(x << 1, pos);
	else return GetAns(x << 1 | 1, pos);
}
 
int main() {
	n = read(), m = read();
	for(int i = 1 ; i <= n ; i ++) b[i] = read() - i;
	for(int i = 1 ; i <= n ; i ++) if(b[i] > 0) b[i] = -1e9; // 直接忽略 > 0 的存在
	build(1, 1, n);
	for(int i = 1 ; i <= m ; i ++) 
		Q[i].l = read() + 1, Q[i].r = n - read(), Q[i].id = i;
	sort(Q + 1, Q + 1 + m, cmp);
	int now = 1;
	for(int i = 1 ; i <= n ; i ++) {
		int v = -b[i];
		if(v == 0 || v == 1e9) { if(v == 0) change(1, 1, i); } // 前缀加就完事了
		else modify(1, v);
		while(Q[now].r == i) Ans[Q[now].id] = GetAns(1, Q[now].l), now ++;
	}
	for(int i = 1 ; i <= m ; i ++) printf("%d\n", Ans[i]);
	return 0;
}
```

目前效率 $rk1$ ($2021 / 5 / 9$)

---

## 作者：tommymio (赞：0)

考虑先把问题转化。设 $b_i=i-a_i$，$c_i$ 为原数列中 $i$ 位置上的数是否被删除。则原数列中 $i$ 位置上的数能被删去的充要条件是 $\sum\limits_{j=1}^{i-1} c_j\geq b_i$。

不妨想想单个询问且无限制的情况，我们每次会取出一个当前位置上 $b_i=0$ 的 $i$，为了让方案最优我们自然希望让这个 $i$ 最靠近右边。然后，$i$ 位置上的数被删掉，$i+1\sim n$ 位置上的数向前移一位，对应的就是 $k\in(i+1,n],b_k=b_k-1$。使用线段树维护 $1\sim n$ 的最右边的 $b_i=0$ 的 $i$ 即可，时间复杂度为 $O(n \log n)$。

现在来考虑加入多个询问及限制的情况。注意到后缀限制影响的那一部分值可以直接删去，而前缀限制影响的那一部分值会影响之后的值，不能直接删去。所以我们离线统计每个询问。倒着加入每个点，仿照单个询问的做法，这样就可以得到 $[i,n]$ 内 $c_i$ 的值。时间复杂度的正确性基于，每个点的 $b$ 值只会达到一次 $0$，所以这一部分的时间复杂度仍为 $O(n \log n)$。

也可以使用主席树，第 $i$ 棵主席树维护 $i\sim n$ 内的 $c_i$ ，询问 $(x,y)$ 时即在第 $x+1$ 棵主席树上查询 $[x+1,n-y]$ 的值。对于 $c_i$，仍使用离线时处理的方法即可。

时间复杂度均为 $O((Q+n) \log n)$，可以通过本题。

---

## 作者：_Felix (赞：0)

转化问题：

用$i-a_i$ 代替 $a_i$

新的操作变为：去掉一个0，然后将之后的元素-1。

对于每个提问，记录$l=1+x,r=n-y$ 

将提问按照 $r$ 再按照 $l$ 排序以便于查询。

---

$f(l,r)$ 维护子序列 $a[l...r]$ 中可以移除的元素的最大数量。

$r$ 从 $1$ 变化到 $n$ ，始终维护每个 $l$ 的答案：
$f(1,r),f(2,r)...f(n,r)$

设$s_i=f(i,r)$

出现一个新元素 $a_r$ 时，如果 $a_r\ge 0$ 且 $s_l\le a_r,s_l$增加 $1$

（显然，当且仅当$a_r\ge 0$ 且 $s_l\le a_r,s_l$ 可以增加 $1$ ，

否则要么就是$a_r<0$显然不可能 或者之前的0个数不够,$a_r$ 还没有来得及减到 $0$ ）

---

设 $lmax$ 是最大的 $l$ 使得 $l\le r$ 且 $s_{lmax}\ge a_r$,将以 $lmax$ 结尾的前缀 $+1$。

由定义可得，$s_1≥…≥s_{lmax}≥a_r>s_{lmax+1}≥…≥s_n$ s单调递减。

二分寻找 $lmax$ ( $s$ 单调递减)。

使用 差分+树状数组 维护 $s$ 数组。

---

时间复杂度：$O(n\log^2 n+q\log n)$

空间复杂度：$O(n)$

可以通过本题。

---

## 作者：SSerxhs (赞：0)

当 $a_i>i$ 时不可能被删去（以下不讨论）

每组询问直接当询问 $[l,r]$ 来看，前面的预处理不再提及

设 $b_i=i-a_i$ 显然 $a_i$ 能被删去当且仅当左侧可被删去数个数大于等于 $b_i$，可以考虑设 $pre_i$ 表示 $[pre_i,i-1]$ 恰好可被删去数个数大于等于 $b_i$

考虑如何计算 $pre_i$，有一个最简单的思路是二分 $pre_i=mid$，则 $[mid,i-1]$ 中 $a_j$ 可被删去当且仅当 $pre_j\ge mid(j<i)$，其中后面的条件只需要按顺序加入就可以解决，考虑记录点 $i$ 是 $c_i$ 个数的 $pre$ ，则只需要维护 $c$ 单点修改区间求和即可，可以用树状数组实现，复杂度 $O(nlog^2n)$

树状数组是一个和二分很不搭配的结构，而线段树和二分更搭配，可以考虑用线段树维护再在线段树上二分，使复杂度降低为 $O(nlogn)$

计算出 $pre$ 后，把 $(pre_i,i)$ 看做二维平面的点 $(x,y)$，则每组询问 $[l,r]$ 相当于询问 $l\le pre_i\le i\le r$ 的点数，即标准的二维数点问题，可以用 cdq 分治或树状数组解决

总复杂度 $O(nlogn)$

```
#include <bits/stdc++.h>
#include <math.h>
using namespace std;
typedef long long ll;
const int N=3e5+2,M=1.2e6+2;
int bel[N],a[N],l[M],r[M],ys[N],pre[N],s[M],ans[N],b[N];
int n,m,c,fh,i,x,j,y;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
void build(int x)
{
	if (l[x]==r[x]) {ys[l[x]]=x;return;}
	l[c=x<<1]=l[x];r[c]=l[x]+r[x]>>1;
	l[c|1]=r[c]+1;r[c|1]=r[x];
	build(c);build(x<<1|1);
}
inline void add(register int x)
{
	for (register int i=x;i;i^=(i&(-i))) ++b[i]; 
}
inline int sum(register int x)
{
	register int r=0;
	for (register int i=x;i<=n;i+=(i&(-i))) r+=b[i];
	return r;
}
struct Q
{
	int z,y,wz;
	bool operator<(const Q& x) const {return y<x.y;}
};
Q q[N];
int main()
{
	read(n);read(m);
	for (i=1;i<=n;i++) {read(a[i]);if (a[i]<=i) a[i]=i-a[i]; else a[i]=n+1;}
	r[l[1]=1]=n;build(1);
	for (i=1;i<=n;i++) if (a[i]<=s[1])
	{
		x=1;c=a[i];
		while (l[x]!=r[x]) if (s[y=x<<1|1]>=c) x=y; else {c-=s[y];x<<=1;}
		if (l[x]>i) x=ys[i];
		pre[i]=l[x];++s[x];
		while (x=x>>1) ++s[x];
	}
	for (i=1;i<=m;i++) {read(q[i].z);read(q[q[i].wz=i].y);++q[i].z;q[i].y=n-q[i].y;}
	sort(q+1,q+m+1);
	for (i=j=1;i<=m;i++)
	{
		while (j<=q[i].y) 
		{
			if (pre[j]) add(pre[j]);
			++j;
		}
		ans[q[i].wz]=sum(q[i].z);
	}
	for (i=1;i<=m;i++) printf("%d\n",ans[i]);
}
```

---

## 作者：Anita_Hailey (赞：0)

## 题意

一个长度为 $n$ 序列 $a[]$，每次可以进行一个操作，当且仅当 $a[i]=i$ 的时候，你可以去掉这个数，然后后边每个数的下标减1。

有 $m$ 次询问，每次去掉前 $x$ 个，和后 $y$ 个，问如何操作可以去掉最多的数，输出去掉的数最多的个数。

## Solution

巧妙的解法，我们重写 $a[]$ 序列即可，具体的操作是：用 $i-a[i]$ 替换 $a[i]$，（若$i-a[i]$ 为负数，那么令其为 $INF$）这样一次操作就变成了：去掉一个0，将后边的数全部减1。

不妨设询问的 $l=1$，这样便于思考。使用动态规划的思想，我们之前最多取 $f(i-1)$ 个数，那么，只要 $a[i]\le f(i-1)$，那么我们就有 $f(i)=f(i-1)+1$, 否则 $f(i)=f(i-1)$。

这样子我们做了全部 $l=1$ 的情况，对于询问，我们按照 $r$ 排序，对于一个 $r$，维护每个 $l$ 的答案。每次从末尾添加一个数的情况，我们可以二分出来刚好 $\ge a[i]$ 的下标，而后树状数组修改即可。

考虑要完成区间加，单点查询，那么我们只要把维护的值差分即可。

如果强制在线，可以考虑使用主席树来完成。关于主席树的区间操作，由于没有复杂的 `tag` 维护，所以可以采用不下放 `tag` 的写法，即每个 $sum(k) = sum(ls(k))+sum(rs(k))+tag(k)*(R-L+1)$，查询的时候注意下就好了。

这样子你就可以切了他了，代码就不放了。

---

## 作者：引领天下 (赞：0)

毒瘤 ds 题。

首先考虑 $a_i$ 什么条件下能删掉。

显然只能是当 $a_i\le i$ 时。

于是我们维护想删掉 $a_i$ 需要在他之前删多少个数（$f_i$），当 $f_i=0$ 的时候 $a_i$ 就可以删除了。

离线保存所有询问，按左端点从右往左处理。

这样当我们加入一个 $j$ 的时候，有以下两种情况：

- $f_j=0$：$j$ 可以删掉，于是从 $j+1$ 到 $n$ 的所有 $f_k$ 全部 $-1$。

- $f_j>0$：$j$ 暂时不能删掉，于是将 $f_j$ 添加进来维护。

最后统计一下，有多少个 $f_j=0$ 答案就是多少了。

使用线段树维护 $f$，树状数组查询答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300005],ans[300005],n,q;
struct Tree_Array{
    int k[300005];
    inline int lowbit(int x){return x&-x;}
    void change(int p){while(p<=n)k[p]++,p+=lowbit(p);}
    int ask(int p){
        int ans=0;
        while(p)ans+=k[p],p-=lowbit(p);
        return ans;
    }
    int ask(int x,int y){return x<=y?ask(y)-ask(x-1):0;}
}t;
struct Segment_Tree{
    int tag[300005<<2],tree[300005<<2];
    int lson(int p){return p<<1;}
    int rson(int p){return (p<<1)|1;}
    void push_up(int p){tree[p]=min(tree[lson(p)],tree[rson(p)]);}
    void build(int p,int l,int r){
        if(l==r){tree[p]=a[l];return;}
        int m=(l+r)>>1;
        build(lson(p),l,m);
        build(rson(p),m+1,r);
        push_up(p);
    }
    void lazy_tag(int p,int v){tree[p]+=v,tag[p]+=v;}
    void push_down(int p){
        if(tag[p]){
            lazy_tag(lson(p),tag[p]);
            lazy_tag(rson(p),tag[p]);
            tag[p]=0;
        }
    }
    void change(int p,int l,int r,int x,int y,int v){
        if(x<=l&&r<=y){lazy_tag(p,v);return;}
        push_down(p);
        int m=(l+r)>>1;
        if(x<=m)change(lson(p),l,m,x,y,v);
        if(y>m)change(rson(p),m+1,r,x,y,v);
    }
    void ask(int p,int l,int r,int x,int y){
        if(tree[p]>0)return;
        if(l==r){
            t.change(l);//可以删除，则从l~n全部-1
            if(r+1<=n)change(1,1,n,r+1,n,-1);
            tree[p]=n;
            return;
        }
        int m=(l+r)>>1;
        push_down(p);
        if(x<=m)ask(lson(p),l,m,x,y);
        if(y>m)ask(rson(p),m+1,r,x,y);
        push_up(p);
    }
}f;
struct Ask{
    int x,y,id;
    inline bool operator<(const Ask&p)const{return x>p.x;}
}que[300005];
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        a[i]=i-a[i];
        if(a[i]<0)a[i]=n+1;//预处理，将ai变为i-ai
        //若i-ai<0，则ai永远删不掉
    }
    for(int i=1;i<=q;i++)cin>>que[i].x>>que[i].y,que[i].id=i;
    sort(que+1,que+q+1);
    f.build(1,1,n);//建树
    for(int i=1,z=n;i<=q;i++){
        while(z>que[i].x){//加入j
            f.ask(1,1,n,z,n);
            z--;
        }
        ans[que[i].id]=t.ask(que[i].x+1,n-que[i].y);//查询答案
    }
    for(int i=1;i<=q;i++)cout<<ans[i]<<endl;
    return 0;
}
```

---

