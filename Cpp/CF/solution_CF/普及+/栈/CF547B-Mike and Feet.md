# Mike and Feet

## 题目描述

给定一个大小为 $n$ 的数列 $a$。  

本题中，我们定义数列 $a$ 的一个连续子序列的区间强度为该子序列中所有元素的最小值。  

比如，对于一个大小为 $5$ 的数列 $1,2,3,4,5$ 来说，其连续子序列 $1,2,3$ 对应的区间强度为 $1$；其连续子序列 $3,4,5$ 对应的区间强度为 $3$。

现在你需要求出对于任意一个 $k(1 \le k \le n)$，所有长度为 $k$ 的连续子序列对应的区间强度的最大值。

## 样例 #1

### 输入

```
10
1 2 3 4 5 4 3 2 1 6
```

### 输出

```
6 4 4 3 3 2 2 1 1 1 
```

# 题解

## 作者：__gcd (赞：9)

因为需要求出每个长度所对应的答案，如果从长度考虑的话，效率不高，我们需要在 $O(1)$ 的时间内求出每个长度的答案，并且答案与答案之间并不互相干涉。

注意到在这道题目中，我们关注的仅仅是“个体”，也就是单个数值（最小值），于是我们可以探究每个个体对于答案做出的**贡献**。一个显然的结论：如果一个数可以为区间长度为 $x$ 的答案，那么他在 $\forall y\in (0,x]$ 的区间长度中，必然可能被取到，只不过不一定是最优的。由此，我们可以考虑找到每个数所对应的最长区间，使得区间内的最小值为这个数，再 $O(n)$ 递推处理即可。

对于找到每个数所对应的最长区间，可以正序和倒序各做一次。以正序为例，对于 $a_x$，找到一个最小的 $y$，使得 $\forall i\in[y,x],a_i\geq a_x$（等于说，找到 $x$ 之前下标最大的一个数 $a_{y-1}$，满足 $a_{y-1}<a_x$），此为[单调栈](https://www.luogu.com.cn/problem/P5788)的板子，这里就不再赘述。

然后就可以整理答案了，答案的整理方式在代码里会具体呈现。

参考代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
inline int read()
{
	int x = 0; bool op = false;
	char c = getchar();
	while(!isdigit(c))op |= (c == '-'), c = getchar();
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return op ? -x : x;
}
const int N = 200010;
int n;
int a[N], l[N], r[N], sum[N], ans[N];
struct Node
{
	int id, val;
	Node(int id = 0, int val = 0):id(id), val(val){}
};
stack<Node> s;
int main()
{
	n = read();
	for(int i = 1; i <= n; i++){a[i] = read(); sum[i] = sum[i - 1] + a[i];}
	for(int i = 1; i <= n; i++)
	{
		while(s.empty() == false && s.top().val >= a[i])
			s.pop();
		if(s.empty() == false)l[i] = s.top().id + 1;
		else l[i] = 1;
		s.push(Node(i, a[i]));
	}
	while(s.empty() == false)s.pop();
	for(int i = n; i >= 1; i--)
	{
		while(s.empty() == false && s.top().val >= a[i])
			s.pop();
		if(s.empty() == false)r[i] = s.top().id - 1;
		else r[i] = n;
		s.push(Node(i, a[i]));
	}
   //整理答案
	for(int i = 1; i <= n; i++)
		ans[r[i] - l[i] + 1] = max(ans[r[i] - l[i] + 1], a[i]);
	for(int i = n; i >= 1; i--)
		ans[i] = max(ans[i], ans[i + 1]);
   //整理答案，原理如上面的结论
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	return 0;
} 
```

相似题目推荐：

[良好的感觉](https://www.luogu.com.cn/problem/P2422) 同样是贡献的思想。

[Imbalanced Array](https://www.luogu.com.cn/problem/CF817D) 贡献+容斥

---

## 作者：LJC00118 (赞：5)

对于第 $ i $ 个数维护使得它在这段区间作为最小值的左端点 $ l $ 和右端点 $ r $，当长度在 $ 1 $ ~ $ r - l + 1 $ 时 $ a[i] $ 可以作为答案，我们用一个单调栈维护即可

```cpp
#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 2e5 + 5;

int st[N], l[N], r[N], val[N], top;
int a[N], n;

int main() {
    memset(val, -0x7f, sizeof(val));
    read(n);
    for(register int i = 1; i <= n; i++) read(a[i]);
    for(register int i = 1; i <= n; i++) {
        while(top && a[st[top]] > a[i]) {
            r[st[top]] = i - 1;
            --top;
        }
        st[++top] = i;
    }
    while(top) {
        r[st[top]] = n;
        --top;
    }
    for(register int i = n; i >= 1; i--) {
        while(top && a[st[top]] > a[i]) {
            l[st[top]] = i + 1;
            --top;
        }
        st[++top] = i;
    }
    while(top) {
        l[st[top]] = 1;
        --top;
    }
    for(register int i = 1; i <= n; i++) val[r[i] - l[i] + 1] = max(val[r[i] - l[i] + 1], a[i]);
    for(register int i = n - 1; i >= 1; i--) val[i] = max(val[i], val[i + 1]);
    for(register int i = 1; i <= n; i++) print(val[i], i == n ? '\n' : ' ');
    return 0;
}
```

---

## 作者：genshy (赞：4)



### **一句话题意：**

 给你一个序列，求出对于每个长度为 $x$ 的区间最小值 的最大值。

### 分析：

单调栈加线段树。

我们 可以考虑一个元素他做为区间最小值的最大区间长度为 $len$ 

那么他就可能会成为 $1-len$ 的答案。

因此我们只需要求出所有可以作为 $len$ 答案的值，取个 $max$ 就是 长度为 $len$ 的组的最后答案。

求一个元素作为区间最小值的最大长度，搞个单调栈就可以。

求 $max$ 的过程，拿线段树或者树状数组优化一下。

然后这题就做完了。

总的时间复杂度 $O(nlogn)$

**Code**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int inf = 2147483647;
const int N = 2e5+10;
int n,top;
int ls[N],rs[N],len[N],a[N],sta[N],tr[N<<2];
inline int read()
{
	int s = 0,w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
	return s * w;
}
void up(int o)
{
	tr[o] = max(tr[o<<1],tr[o<<1|1]);
}
void chenge(int o,int l,int r,int x,int val)
{
	if(l == r)
	{
		tr[o] = max(tr[o],val);
		return;
	}
	int mid = (l + r)>>1;
	if(x <= mid) chenge(o<<1,l,mid,x,val);
	if(x > mid) chenge(o<<1|1,mid+1,r,x,val);
	up(o);
}
int query(int o,int l,int r,int L,int R)
{
	int res = 0;
	if(L <= l && R >= r) return tr[o];
	int mid = (l + r)>>1;
	if(L <= mid) res = max(res,query(o<<1,l,mid,L,R));
	if(R > mid) res = max(res,query(o<<1|1,mid+1,r,L,R));
	return res;
}
void YYCH()//求每个元素作为区间最小值的最长区间长度
{
	a[0] = a[n+1] = -inf;
	top = 0; sta[++top] = 0;
	for(int i = 1; i <= n; i++)
	{
		while(top && a[sta[top]] >= a[i]) top--;
		ls[i] = sta[top]; sta[++top] = i;
	}
	top = 0; sta[++top] = n+1;
	for(int i = n; i >= 1; i--)
	{
		while(top && a[sta[top]] >= a[i]) top--;
		rs[i] = sta[top]; sta[++top] = i;
	}
	for(int i = 1; i <= n; i++)
	{
		len[i] = rs[i] - ls[i] - 1;
	}
}
signed main()
{
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	YYCH();
	for(int i = 1; i <= n; i++)//线段树优化一下求最值的过程
	{
		chenge(1,1,n,len[i],a[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		printf("%d ",query(1,1,n,i,n));
	}
	return 0;
}
```







---

## 作者：yanghaokun (赞：4)

一个裸单调栈的题

对于点i，查出它的左右第一个比它小的节点，分别记录le和ri的值，那么，ri-1一直到le+1都是合法的区间，所以num[k]=max(a[i]),ri[i]-le[i]+1=k;

最后，只需要num[k]=max(num[k],num[k+1]就可以啦
上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1001001],le[1001001],ri[1001001],sta[1001001],top,num[1001001];
inline void push(int x)
{
    while(a[x]<a[sta[top]]&&top)
    ri[sta[top]]=x-1,top--;
    sta[++top]=x;
}
inline void push2(int x)
{
    while(a[x]<a[sta[top]]&&top)
    le[sta[top]]=x+1,top--;
    sta[++top]=x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);a[n+1]=-1;
    for(int i=1;i<=n;i++)push(i);
    while(top)ri[sta[top--]]=n;
    top=0;
    for(int i=n;i;i--)push2(i);
    while(top)le[sta[top--]]=1;
    for(int i=1;i<=n;i++) num[ri[i]-le[i]+1]=max(a[i],num[ri[i]-le[i]+1]);
    for(int i=n;i;i--) num[i]=max(num[i],num[i+1]);
    for(int i=1;i<=n;i++)printf("%d ",num[i]);
}
```


---

## 作者：一叶知秋。 (赞：3)

来一个并查集做法，时间复杂度 $O(nlogn)$

将高度先从大到小排序，然后一个一个插入到原序列中（位置不能变）

假设我们已经找到了前 $k$ 个答案了，此时插入一个数就将当前位置与两边的合并成一大段，然后此时若该段长度 $>k$ ，则从 $k+1$ 到 $size$ 的答案都是该高度（因为是从大到小排序，所以肯定是最大的）

具体实现看代码：

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>

using namespace std;

#define maxn 202202

inline int read(){
	int r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

inline void swap(int &a,int &b){
	int c=a;
	a=b;
	b=c;
}

struct B{
	int h,num;
	B() {}
	B(int h,int num):h(h),num(num) {}
	bool operator <(const B &b) const{
		return h<b.h;
	}
}b[maxn];

bool in[maxn];

int n,f[maxn],size[maxn];

int find(int x){
	return x^f[x]?f[x]=find(f[x]):x;
}

inline void Union(int u,int v){
	int fu=find(u),fv=find(v);
	if(size[fu]<size[fv])swap(fu,fv);
	size[fu]+=size[fv];
	f[fv]=fu;
}

int main(){
    n=read();
	for(int i=1;i<=n;i++){
		b[i]=B(read(),i);//要保留该高度位置
		f[i]=i,size[i]=1;
	}
	sort(b+1,b+1+n);
	int k=1;
	for(int i=n;i>=1;i--){
		int num=b[i].num;
		in[num]=1;//标记该位置已经插入了
		if(in[num-1])Union(num-1,num);//看左右是否已经插入，
		if(in[num+1])Union(num,num+1);//若插入了，就合并起来
		int s=size[find(num)];
		for(;k<=s;k++)printf("%d ",b[i].h);
	}
	return 0;
}
```


---

## 作者：学委 (赞：3)

从答案的角度出发。比如样例：

```
10

1 2 3 4 5 4 3 2 1 6
```

* 如果队伍中最小值为 1，那么队伍长度可以达到 10。

* 如果队伍中最小值为 2，那么所有的 “1” 就成了阻隔点，求最长的连续段。

* 如果队伍中最小值为 3，那么所有的 “2” 又成了阻隔点，求最长的连续段。

* ……

题目就变成，随着答案上升，不断在指定位置插入断点，维护整个序列的最长连续段。第一感觉是无脑线段树（~~虽然有单调栈做法~~），更新过程很直观很暴力。一个线段内维护：**左端最长连续段**、**右端最长连续段**、**整个线段内的最长连续段**，以及一个标记：**该段是否已有断点**，如果没有断点，那么它整段都是父亲的左端或右端连续段。

```cpp
#include <cstdio>
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
using std::max;

typedef vector<int>::iterator It;

const int N = 2e5 + 10;

struct Bear {
  int id, h;
  bool operator< (const Bear& g) {
    return h < g.h;
  }
}bear[N];

int n, ans[N], v[N], ref[N], cnt = 0;
vector<int> p[N];


inline int ls(int u) { return u * 2; }
inline int rs(int u) { return u * 2 + 1; }

struct Node {
  int lspace, rspace;
  int maxspace, broken;
  Node(int gl = 0, int gr = 0, int gm = 0, int gb = 0) {
    lspace = gl; rspace = gr; maxspace = gm; broken = gb;
  }
  friend Node operator+ (const Node& lson, const Node& rson) {
    Node tmp;
    int midspace = lson.rspace + rson.lspace;
    tmp.maxspace = max(midspace, max(lson.maxspace, rson.maxspace));
    
    if (not lson.broken)
      tmp.lspace = lson.maxspace + rson.lspace;
    else
      tmp.lspace = lson.lspace;
    
    if (not rson.broken)
      tmp.rspace = lson.rspace + rson.maxspace;
    else
      tmp.rspace = rson.rspace;
    
    tmp.broken = lson.broken or rson.broken;
    return tmp;
  }
}node[N * 4];

void build(int u, int l, int r) {
  if (l == r) {
    node[u].lspace = node[u].rspace = node[u].maxspace = 1;
    return;
  }
  int mid = (l + r) / 2;
  build(ls(u), l, mid);
  build(rs(u), mid + 1, r);
  node[u] = node[ls(u)] + node[rs(u)];
}

void add_point(int u, int l, int r, int x) {
  if (l == r) {
    node[u].broken = true;
    node[u].lspace = node[u].rspace = node[u].maxspace = 0;
    return;
  }
  int mid = (l + r) / 2;
  if (x <= mid)
    add_point(ls(u), l, mid, x);
  else
    add_point(rs(u), mid + 1, r, x);
  node[u] = node[ls(u)] + node[rs(u)];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &bear[i].h), bear[i].id = i;
  sort(bear + 1, bear + n + 1);
  for (int i = 1; i <= n; ++i) {
    if (bear[i].h != bear[i - 1].h)
      ref[++cnt] = bear[i].h;
    v[bear[i].id] = cnt;
  }
  build(1, 1, n);
  for (int i = 1; i <= n; ++i)
    p[v[i]].push_back(i);
  for (int i = 1; i <= cnt; ++i) { // i : processed val
    ans[node[1].maxspace] = i;
    for (It it = p[i].begin(); it < p[i].end(); ++it)
      add_point(1, 1, n, *it);
  }
  for (int i = n; i >= 1; --i)
    ans[i] = max(ans[i], ans[i + 1]);
  for (int i = 1; i <= n; ++i)
    printf("%d\n", ref[ans[i]]);
  return 0;
}
```

---

## 作者：Leap_Frog (赞：1)

### P.S.
我就是个大傻逼，一道简单的单调队列题目要用 ODT。  

### Problem.
让你求区间长度为 $i$ $(i\in[1,n])$ 的区间最小值的最大值。  

### Solution.
我们对所有元素从小到大排序。  
那么我们当前扫到的这个元素肯定是目前的“瓶颈”，是最小值。  
然后我们对于每个元素，我们以它为中心，把它所在的区间割开。  
这样，每个元素所在的区间都是它区间的最小值。  
那么我们在每次割区间时更新一下长度为当前区间长度内的最小值就好了。  
而当前区间内最小值就是我们扫描到的元素。  
具体实现可以类似 ODT 那样实现。  
完结撒花，~~Chtholly~~ 不可爱，~~Nephren~~ 可爱。  

### Coding.
```cpp
//愿你有一天能和你重要的人重逢。
//大切な人といつかまた巡り会えますように
#include<bits/stdc++.h>
using namespace std;const int INF=1e9+9;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
struct node{int w,v;bool operator<(node b) const {return v<b.v;}}a[200005];
//每个节点的位置，按照节点权值排序
struct seg{mutable int l,r;bool operator<(seg b) const {return l<b.l;}};
//ODT 的区间
int n,rs[200005];typedef set<seg>::iterator IT;set<seg>s;
inline void split(int w,int vl)
{
	// for(IT i=s.begin();i!=s.end();i++) printf("[ %d , %d ]\n",i->l,i->r);
	IT i=s.lower_bound((seg){w,0});//找
	// putchar('\n');cerr<<"split : "<<w<<" ( "<<i->l<<" , "<<i->r<<endl;
	if(i!=s.end()&&i->l==w)
	{//如果当前区间左端点刚好是目标，不需要割开
		rs[i->r-i->l+1]=max(rs[i->r-i->l+1],vl);//更新答案
		if(i->l==i->r) return(void)(s.erase(i));else return (void)(i->l++);
		//割开操作
	}else --i;//ODT 基本操作
	rs[i->r-i->l+1]=max(rs[i->r-i->l+1],vl);//更新答案
	// cerr<<i->l<<" ~ "<<i->r<<" -> "<<vl<<endl;
	int l=i->l,r=i->r;s.erase(i),s.insert((seg){l,w-1});
	if(w!=r) s.insert((seg){w+1,r}).first;
	//ODT 基本操作
}
int main()
{
	read(n);for(int i=1;i<=n;i++) read(a[i].v),a[i].w=i;
	sort(a+1,a+n+1),memset(rs,0,sizeof(rs)),s.insert((seg){1,n});//初始化
	for(int i=1;i<=n;i++) split(a[i].w,a[i].v);//扫描
	for(int i=n;i>=1;i--) rs[i]=max(rs[i],rs[i+1]);
	for(int i=1;i<=n;i++) printf("%d%c",rs[i],i==n?'\n':' ');
	return 0;
}
```

---

## 作者：老嘿 (赞：1)

单调栈+离散化
sz[i]表示以i为最小值的区间的最大长度，排序后输出即可
```cpp
#include<cstdio>
#include<ctype.h>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<stdlib.h>
using namespace std;
#define ll long long
#define ull unsigned long long
inline ll rd()
{
    ll x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-f;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
const int N=2e5+7;
int a[N],num[N],b[N],s[N],sz[N],l[N];
bool cmp(int c,int d){return a[c]<a[d];}
int main()
{
	int n=rd(),cnt=0,top=0;
	for(int i=1;i<=n;i++) a[i]=rd(),num[i]=i;
	sort(num+1,num+1+n,cmp);
	for(int i=1;i<=n;i++) {if(a[num[i]]!=a[num[i-1]]) cnt++;b[num[i]]=cnt;}
	for(int i=1;i<=n;i++)
	{
		while(top>0&&b[i]<=b[s[top]]) top--;
		l[i]=s[top];s[++top]=i;
	}
	top=0;s[top]=n+1;
	for(int i=n;i>0;i--)
	{
		while(top>0&&b[i]<=b[s[top]]) top--;
		sz[b[i]]=max(sz[b[i]],s[top]-l[i]-1);s[++top]=i;
	}
	int j=n;
	for(int i=1;i<=n;i++)
	{
		while(j>0&&sz[b[num[j]]]<i) j--;
		printf("%d ",a[num[j]]);
	}
	return 0;
}
```


---

## 作者：Forever1507 (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF547B)
其实题目翻译有点诡异，提供一下正确翻译：

翻译来源：[$\green{apple365}$](https://www.luogu.com.cn/user/123216)

输入 $n$ 个整数代表 $n$ 个熊的高度，对于长度为 $x$ 的区间 定义力量值为这个区间中熊的最小的身高值。

对于每个 $x(1<=x<=n)$ 求出最大的力量值。

言归正传，这题大致就是要求出每一个点为最小值的区间，然后把每个长度的值的所有可能取 $\max$ 。这里的单调栈大家应该都会（[不会就接受一下我的安利吧](https://www.luogu.com.cn/blog/359614/dan-diao-dui-lie-dan-diao-zhan-xue-xi-bi-ji)），难点就是怎么输出，如果笼统地把每一个长度和比他长度小的答案取 $\max$ 一定会 $TLE$ ，那么怎么办？

我们可以先 $O(n)$ 处理下每个长度的最小值，然后倒序循环，直接
```
ans[i]=max(ans[i],ans[i+1]);
```
就行了，因为倒序循环上一次比较出来的值也会参与下一次比较，实现了 $O(n)$ 的时间复杂度。

$Code:$
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,r[200005],l[200005],a[200005],ans[200005];
stack<int>stk1,stk2;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];	
	}
	for(int i=1;i<=n;i++){
		while(!stk1.empty()&&a[i]<a[stk1.top()]){
            r[stk1.top()]=i-1;
            stk1.pop();
        }
        stk1.push(i);
	}
	while(!stk1.empty()){
		r[stk1.top()]=n;
		stk1.pop();//找不到就设为边界
	}
	for(int i=n;i>=1;i--){
		while(!stk2.empty()&&a[i]<a[stk2.top()]){
            l[stk2.top()]=i+1;//左右两边要维护两次单调栈
            stk2.pop();
        }
        stk2.push(i);
	}
	while(!stk2.empty()){
		l[stk2.top()]=1;
		stk2.pop();
	}
	for(int i=1;i<=n;i++){
		ans[r[i]-l[i]+1]=max(a[i],ans[r[i]-l[i]+1]);
	}
	for(int i=n;i>=1;i--){
		ans[i]=max(ans[i],ans[i+1]);//如上操作
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	return 0;
}
```


---

