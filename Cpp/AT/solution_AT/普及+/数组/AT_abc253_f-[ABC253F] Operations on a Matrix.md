# [ABC253F] Operations on a Matrix

## 题目描述

有一个纵向 $N$ 行、横向 $M$ 列的矩阵，初始时所有元素均为 $0$。

请处理 $Q$ 个查询，每个查询有以下三种形式之一：

- `1 l r x` ：将第 $l$ 列到第 $r$ 列（包括两端）所有元素都加上 $x$。
- `2 i x` ：将第 $i$ 行的所有元素都替换为 $x$。
- `3 i j` ：输出第 $i$ 行第 $j$ 列的元素值。

## 说明/提示

## 限制条件

- $1 \leq N, M, Q \leq 2 \times 10^5$
- 对于 `1 l r x` 形式的查询，$1 \leq l \leq r \leq M$ 且 $1 \leq x \leq 10^9$
- 对于 `2 i x` 形式的查询，$1 \leq i \leq N$ 且 $1 \leq x \leq 10^9$
- 对于 `3 i j` 形式的查询，$1 \leq i \leq N$ 且 $1 \leq j \leq M$
- 至少会有一个 `3 i j` 形式的查询
- 输入均为整数

## 样例说明 1

矩阵的变化如下：

$
\begin{pmatrix}
0 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0 \\
\end{pmatrix}
\rightarrow
\begin{pmatrix}
1 & 1 & 0 \\
1 & 1 & 0 \\
1 & 1 & 0 \\
\end{pmatrix}
\rightarrow
\begin{pmatrix}
1 & 1 & 0 \\
1 & 1 & 0 \\
2 & 2 & 2 \\
\end{pmatrix}
\rightarrow
\begin{pmatrix}
1 & 4 & 3 \\
1 & 4 & 3 \\
2 & 5 & 5 \\
\end{pmatrix}
$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3 9
1 1 2 1
3 2 2
2 3 2
3 3 3
3 3 1
1 2 3 3
3 3 2
3 2 3
3 1 2```

### 输出

```
1
2
2
5
3
4```

## 样例 #2

### 输入

```
1 1 10
1 1 1 1000000000
1 1 1 1000000000
1 1 1 1000000000
1 1 1 1000000000
1 1 1 1000000000
1 1 1 1000000000
1 1 1 1000000000
1 1 1 1000000000
1 1 1 1000000000
3 1 1```

### 输出

```
9000000000```

## 样例 #3

### 输入

```
10 10 10
1 1 8 5
2 2 6
3 2 1
3 4 7
1 5 9 7
3 3 2
3 2 8
2 8 10
3 8 8
3 1 10```

### 输出

```
6
5
5
13
10
0```

# 题解

## 作者：thousands_of_years (赞：5)

不是 $1 \le N, M, Q \le 2 \times 10^5$，真就没人想用根号算法吗？

## Solution

考虑离线，这里采用莫队，将该行覆盖后的第一次加操作为左端点，当前记录到的加操作为右端点，我们再差分一下，将区间加操作变成两个点的加减，这样就可以得到询问点当行不考虑覆盖值的差分数组。
再用分块维护一下前缀和，最后加上覆盖的值就做完了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO {
#define IOSIZE 100000
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
	template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
	template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
	inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
	inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
	inline void print(char x) { putchar(x); }
	inline void print(char *x) { while (*x) putchar(*x++); }
	inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
	inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
	inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
	inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
	inline void print(bool b) { putchar(b+48); }
	template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
	template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
	struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
#define cout io
#define cin io
#define endl '\n'
}using namespace fast_IO;
#define int long long
const int N=1e6+9;
struct node{
	int l,r,y,val,id;
}e[N];
int sum[N],bell[N],ans[N];
int a[N],b[N],cnt,A[N],B[N],C[N],tot,bel[N];
inline bool cmp(node aa,node bb)
{
	if(bel[aa.l]==bel[bb.l])
	{
		if(bel[aa.l]&1)
		return aa.r<bb.r;
		return aa.r>bb.r;
	}
	return bel[aa.l]<bel[bb.l];
}
inline void add(int u)
{
	sum[A[u]]+=C[u];
	bell[bel[A[u]]]+=C[u];
	sum[B[u]+1]-=C[u];
	bell[bel[B[u]+1]]-=C[u];
}
inline void del(int u)
{
	sum[A[u]]-=C[u];
	bell[bel[A[u]]]-=C[u];
	sum[B[u]+1]+=C[u];
	bell[bel[B[u]+1]]+=C[u];
}
inline int findd(int x)
{
	int res=0;
	for(int i=1;i<bel[e[x].y];i++)
	{
		res+=bell[i];
	}
	for(int i=(bel[e[x].y]-1)*400+1;i<=e[x].y;i++)
	{
		res+=sum[i];
	}
	return res+e[x].val;
}
signed main()
{
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++)
	{
		int opt,j,x;
		cin>>opt;
		if(opt==1)
		{
			++cnt;
			cin>>A[cnt]>>B[cnt]>>C[cnt];
		}
		else
		if(opt==2)
		{
			cin>>j>>x;
			a[j]=x;
			b[j]=cnt+1;
		}
		else
		{
			cin>>j>>x;
			e[++tot].l=b[j];
			e[tot].r=cnt;
			e[tot].val=a[j];
			e[tot].y=x;
			e[tot].id=tot;
		}
	}
	for(int i=1;i<=q;i++)
		bel[i]=(i-1)/400+1;
	sort(e+1,e+1+tot,cmp);
	int l=1,r=0;
	for(int i=1;i<=tot;i++)
	{
		while(r<e[i].r) add(++r);
		while(r>e[i].r) del(r--);
		while(l<e[i].l) del(l++);
		while(l>e[i].l) add(--l);
		ans[e[i].id]=findd(i);
	}
	for(int i=1;i<=tot;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：XYQ_102 (赞：3)

首先考虑没有操作 $2$ 的情况，那么很容易地就可以用树状数组实现对列的区间加及单点查询。

当有操作 $2$ 时，对于操作 $3$ 的查询：将该行最后一次操作 $2$ 的行修改值记作 $x$，从最后一次操作 $2$ 到该次操作所有的 $1$ 操作列增加值记作 $sum2$，那么输出的答案就为 $x + sum2$。将从开始到该次操作的所有 $1$ 操作列增加值记作 $sum$，从开始到最后一次操作 $2$ 的列增加值记作 $sum1$，那么有 $sum2 = sum - sum1$，答案就为：$x + sum - sum1$。离线查询即可。
## Code
```cpp
#include <bits/stdc++.h>
#define LL long long
#define lowbit(x) (x & -x)
using namespace std;

const int N = 200010;

int n, m, Q, last[N];
LL tr[N], ans[N];
vector<int> v[N];

struct query {
    int op, a, b, c;
} q[N];

void add(int x, int c)
{
    for(int i = x; i <= m; i += lowbit(i)) tr[i] += c;
}

LL sum(int x)
{
    LL res = 0;
    for(int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main()
{
    cin >> n >> m >> Q;

    for(int i = 1; i <= Q; i++) {
        scanf("%d%d%d", &q[i].op, &q[i].a, &q[i].b);
        if(q[i].op == 1) scanf("%d", &q[i].c);
        else if(q[i].op == 2) last[q[i].a] = i;
        else v[last[q[i].a]].push_back(i);
    }

    for(int i = 1; i <= Q; i++) {
        if(q[i].op == 1) add(q[i].a, q[i].c), add(q[i].b + 1, -q[i].c);
        else if(q[i].op == 2) for(auto item : v[i]) ans[item] = q[i].b - sum(q[item].b);  
        else printf("%lld\n", ans[i] + sum(q[i].b));
    }

    return 0;
}
```

---

## 作者：DengDuck (赞：2)

做法显然有两类，一种是离线，一种是主席树。

对于在操作 $r$ 查询 $(x,y)$ 的值，我们假设上一次行进行替换操作的操作编号 $l$。

则其值为 $[l,r]$ 所有的列操作对 $y$ 列的操作影响加上对 $x$ 替换的值。

右边的很简单，但是左边的东西实时维护需要主席树，可以离线下来。

具体地，问题可以拆成 $[1,r]$ 所有的列操作对 $y$ 列的操作影响减去$[1,l-1]$ 所有的列操作对 $y$ 列的操作影响。

于是保存下来求出后，再用其求出答案即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5;
struct input
{
	LL op,x,y,z;
}in[N];
struct query
{
	LL tim,k;
}que[N*2];
bool cmp(query x,query y)
{
	return x.tim<y.tim;
}
LL n,m,q,a[N],b[N],cnt,t[N],tot=1;
LL lowbit(LL x)
{
	return x&-x;
}
void update(LL x,LL k)
{
	while(x<=m)
	{
		t[x]+=k;
		x+=lowbit(x);
	}
}
LL query(LL x)
{
	LL sum=0;
	while(x)
	{
		sum+=t[x];
		x-=lowbit(x);
	}
	return sum;
}
map<pair<LL,LL>,LL>ma;
int main()
{
	scanf("%lld%lld%lld",&n,&m,&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%lld%lld%lld",&in[i].op,&in[i].x,&in[i].y);
		if(in[i].op==1)
		{
			scanf("%lld",&in[i].z);
		}
		if(in[i].op==2)
		{
			a[in[i].x]=i;
		}
		if(in[i].op==3)
		{
			que[++cnt]={i,in[i].y};
			que[++cnt]={a[in[i].x]-1,in[i].y};
		}
	}
	sort(que+1,que+cnt+1,cmp);
	while(que[tot].tim<=0)tot++;
	for(int i=1;i<=q;i++)
	{
		if(in[i].op==1)
		{
			LL l=in[i].x,r=in[i].y,k=in[i].z;
			update(l,k),update(r+1,-k);
		}
		while(que[tot].tim==i)
		{
			LL gt=query(que[tot].k);
			ma[{que[tot].tim,que[tot].k}]=gt;
			tot++;
		}
	}
	memset(a,0,sizeof(a));
	for(int i=1;i<=q;i++)
	{
		if(in[i].op==2)
		{
			LL x=in[i].x,y=in[i].y;
			a[x]=y,b[x]=i;
		}
		if(in[i].op==3)
		{
			LL x=in[i].x,y=in[i].y;
			LL r=ma[{i,y}],l=ma[{b[x]-1,y}];
			printf("%lld\n",r-l+a[x]);
		}
	}	
}

```

---

## 作者：Tsawke (赞：2)

# [[ABC253F] Operations on a Matrix](https://www.luogu.com.cn/problem/AT_abc253_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC253F)

## 题面

存在 $ n $ 行 $ m $ 列的矩阵，给定 $ q $ 次操作，有 $ 3 $ 种格式。

* `1 l r x`：将 $ [l, r] $ 列的所有元素全部加上 $ x $。
* `2 i x`：将第 $ i $ 行的元素全部变为 $ x $。
* `3 i j`：输出矩阵 $ (i, j) $ 位置的元素值。

## Solution

感觉还算是一道细节不少的题。

首先这道题的做法不少，主流的就是类似二位偏序维护，或者写一个区间修改的主席树。

这里主要说一下用 BIT 维护的方法。

首先不难想到，$ 2 $ 操作会覆盖掉前面所有的对其有影响的 $ 1 $ 操作。然后 $ 1 $ 操作是区间修改列，$ 2 $ 操作是单点推平行。所以考虑离线，然后对于每个查询，令其序号为 $ r $，有行 $ x $ 列 $ y $，我们要找到在其之前的上一个推平 $ x $ 行，令其的操作序号为 $ l $，那么我们就需要对这个答案初始设为那次推平的值，然后加上 $ [l, r] $ 之间的所有的对于 $ y $ 列的操作。

思路就是这样，维护的方式还是有些高妙的。先考虑离线一遍，然后维护对于每个查询的上一次对应的推平，同时维护该查询的初始值，然后在需要减去的位置开个 `basic_string` 插进去需要减的序号。然后我们考虑会有一次区间的查询，用 BIT 和前缀和维护，再遍历一次操作，先将前缀加起来，然后减去的那个前缀就在我们第二次遍历的时候通过遍历对应的 `basic_string` 而减去。然后最后跑一遍输出答案即可。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, M, Q;
int lst[210000], pos[210000];
ll ans[210000];
struct Query{int opt; int a, b, c;}qs[210000];
basic_string < int > del[210000];

class BIT{
private:
    ll tr[210000];
public:
    int lowbit(int x){return x & -x;}
    void Modify(int x, int v){while(x <= M)tr[x] += v, x += lowbit(x);}
    ll Query(int x){ll ret(0); while(x)ret += tr[x], x -= lowbit(x); return ret;}
    void ModifyRange(int l, int r, ll v){Modify(l, v), Modify(r + 1, -v);}
}bit;

int main(){
    // freopen("test_05.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    N = read(), M = read(), Q = read();
    for(int i = 1; i <= Q; ++i){
        int opt = read();
        switch(opt){
            case 1:{
                int l = read(), r = read(), v = read(); qs[i] = Query{opt, l, r, v};
                break;
            }
            case 2:{
                int p = read(), v = read(); qs[i] = Query{opt, p, v};
                pos[p] = i;
                break;
            }
            case 3:{
                int x = read(), y = read(); qs[i] = Query{opt, x, y};
                ans[i] = qs[pos[x]].b;
                del[pos[x]] += i;
                break;
            }
            default: break;
        }
    }
    for(int i = 1; i <= Q; ++i){
        switch(qs[i].opt){
            case 1:{bit.ModifyRange(qs[i].a, qs[i].b, qs[i].c); break;}
            case 2:{for(auto p : del[i])ans[p] -= bit.Query(qs[p].b); break;}
            case 3:{ans[i] += bit.Query(qs[i].b); break;}
            default: break;
        }
    }
    for(int i = 1; i <= Q; ++i)if(qs[i].opt == 3)printf("%lld\n", ans[i]);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_05 初稿

---

## 作者：shinkuu (赞：2)

一个比较需要清晰思路，但是挺巧妙的方法。

首先发现，对于一个点的值 $a_{i,j}$，会对它产生影响的只有上次 $2$ 操作到现在的 $1$ 操作。考虑怎样利用这一点。

每次 $1$ 操作会涉及一个区间，想到类似扫描线的操作。发现操作 $2$ 不太好维护，所以转变一下思路：重新以原来纵坐标为 $x$ 轴，以时间戳为 $y$ 轴，将所有询问和修改按照 $x$ 轴排序，对于每个 $x$，维护当前纵坐标的值为序列 $a$。

对于每个询问，设 $i$ 为上一次影响它的操作 $2$ 的时间戳，$j$ 为改成的值，$t$ 为当前操作的时间戳，则这次询问的答案为 $\sum_{i\le k\le t} a_k+j$。

所以可以用 BIT 维护序列 $a$，利用扫描线的思想，将操作 $1$ 看成 $x$ 轴为 $l$ 时将对应时间戳位置加上 $x$，等于 $r+1$ 时减去 $x$，再用数组记录上述 $i,j$ 即可。

可以结合代码理解，毕竟这种以时间戳为一轴还是太抽象了。

感觉可以下位蓝？

code：

```cpp
int n,m,q,s,pre[N],c[N],id[N];
ll ans[N];
struct node{
	int pos,t,vl,op;
}e[N<<1];

ll tr[N];
#define lowbit(x) (x&(-x))
inline void update(int x,int y){
	while(x<=q){
		tr[x]+=y;
		x+=lowbit(x);
	}
}
inline ll query(int x){
	if(!x)
		return 0;
	ll ret=0;
	while(x){
		ret+=tr[x];
		x-=lowbit(x);
	}
	return ret;
}

inline bool cmp(node x,node y){
	return x.pos!=y.pos?x.pos<y.pos:x.op<y.op;
}
void solve(){
	scanf("%d%d%d",&n,&m,&q);
	int cnt=0;
	for(int i=1,op,x,y,k;i<=q;i++){
		scanf("%d%d%d",&op,&x,&y);
		if(op==1){
			scanf("%d",&k);
			e[++s]={x,i,k,-1};
			e[++s]={y+1,i,-k,-1};
		}
		if(op==2){
			pre[x]=i;
			c[x]=y;
		}
		if(op==3){
			e[++s]={y,i,pre[x],c[x]};
			id[i]=++cnt;
		}
	}
	sort(e+1,e+s+1,cmp);
	for(int i=1;i<=s;i++){
		if(e[i].op==-1)
			update(e[i].t,e[i].vl);
		else 
			ans[id[e[i].t]]=query(e[i].t)-query(e[i].vl)+e[i].op;
	}
	for(int i=1;i<=cnt;i++)
		printf("%lld\n",ans[i]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：Charged_Charge (赞：0)

# AT_abc253_f
## 题目大意：
按照三种操作进行模拟，遇到操作三，输出 $a_{i,j}$。
## 解题思路：
这道题比较复杂，主要是有那个操作二，十分的恶心，会让之前所有的操作一白费，而且，由于数据范围比较大，有 $2\times 10^5$ 所以也不可以建立矩阵直接计算。那么我们就要想一种办法解决这种情况。我们发现，每一次的操作二只会影响前面的操作一，所以，我们可以记录每一次的操作二在什么时候出现。每出现一次操作一，加上即可；出现操作二，记录当前行最后一次出现操作二的时间；遇见操作三，在最后输出答案前，减去当前行最后出现操作二之前的操作一的值，最后输出即可。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+20;
int n, m, q, cnt;
int op[N], ans[N];
int a[N], b[N], c[N];
int tr[N];
pair<int, int> p[N];
vector<int> sb[N];
int lowbit(int x) {
	return x & -x;
}
void add(int x, int y) {
	for (int i = x; i <= m; i += lowbit(i)) {
		tr[i] += y;
	}
}
int ask(int x) {
	int ans = 0;

	for (int i = x; i; i -= lowbit(i)) {
		ans += tr[i];
	}

	return ans;
}
signed main() {
	cin >> n >> m >> q;

	for (int i = 1; i <= n; i++) {
		p[i] = {-1, 0};
	}

	for (int i = 1; i <= q; i++) {
		cin >> op[i];

		if (op[i] == 1) {
			cin >> a[i] >> b[i] >> c[i];
		} else if (op[i] == 2) {
			cin >> a[i] >> c[i];
			p[a[i]] = {i, c[i]};
		} else {
			cin >> a[i] >> b[i];
			auto [j, x] = p[a[i]];
			ans[++cnt] = x;
			c[i] = cnt;

			if (j >= 1) {
				sb[j].push_back(i);
			}
		}
	}

	memset(tr, 0, sizeof tr);

	for (int i = 1; i <= q; i++) {
		if (op[i] == 1) {
			add(a[i], c[i]);
			add(b[i] + 1, -c[i]);
		} else if (op[i] == 2) {
			for (int j : sb[i]) {
				ans[c[j]] -= ask(b[j]);
			}
		} else {
			ans[c[i]] += ask(b[i]);
		}
	}

	for (int i = 1; i <= cnt; i++) {
		cout << ans[i] << endl;
	}

	return 0;
}
```

---

