# Xenia and Bit Operations

## 题目描述

Xenia the beginner programmer has a sequence $ a $ , consisting of $ 2^{n} $ non-negative integers: $ a_{1},a_{2},...,a_{2^{n}} $ . Xenia is currently studying bit operations. To better understand how they work, Xenia decided to calculate some value $ v $ for $ a $ .

Namely, it takes several iterations to calculate value $ v $ . At the first iteration, Xenia writes a new sequence $ a_{1} or a_{2},a_{3} or a_{4},...,a_{2^{n}-1} or a_{2^{n}} $ , consisting of $ 2^{n-1} $ elements. In other words, she writes down the bit-wise OR of adjacent elements of sequence $ a $ . At the second iteration, Xenia writes the bitwise exclusive OR of adjacent elements of the sequence obtained after the first iteration. At the third iteration Xenia writes the bitwise OR of the adjacent elements of the sequence obtained after the second iteration. And so on; the operations of bitwise exclusive OR and bitwise OR alternate. In the end, she obtains a sequence consisting of one element, and that element is $ v $ .

Let's consider an example. Suppose that sequence $ a=(1,2,3,4) $ . Then let's write down all the transformations $ (1,2,3,4) $ $ → $ $ (1 or 2=3,3 or 4=7) $ $ → $ $ (3 xor 7=4) $ . The result is $ v=4 $ .

You are given Xenia's initial sequence. But to calculate value $ v $ for a given sequence would be too easy, so you are given additional $ m $ queries. Each query is a pair of integers $ p,b $ . Query $ p,b $ means that you need to perform the assignment $ a_{p}=b $ . After each query, you need to print the new value $ v $ for the new sequence $ a $ .

## 说明/提示

For more information on the bit operations, you can follow this link: http://en.wikipedia.org/wiki/Bitwise\_operation

## 样例 #1

### 输入

```
2 4
1 6 3 5
1 4
3 4
1 2
1 2
```

### 输出

```
1
3
3
3
```

# 题解

## 作者：Priori_Incantatem (赞：6)

### 题目大意

给出一个长度为 $2^n$ 的序列 $a$，并进行 $n$ 次更新操作  
在第奇数次操作时，将每两个相邻的数 按位或，并将这些得到的值组成的序列代替序列 $a$  
在第偶数数次操作时，将每两个相邻的数 按位异或，并将这些得到的值组成的序列代替序列 $a$

在 $n$ 次操作后，$a$ 序列中只剩下了一个数，我们称这个数为序列 $a$ 的键值  
给出 $m$ 个询问，每次询问包含两个数 $p,b$，表示求当 $a_p=b$ （其他数不变）时序列 $a$ 的键值

### 解题思路
首先，我们要思考如何求出序列 $a$ 的键值（先不考虑多组询问）

方法1：直接模拟  
这个就没什么好说的了，按照题意 异或/按位或 相邻元素就好了。时间复杂度 $\operatorname{O}(2^{n+1}-1)$

方法2：树形DP/dfs  
让 $n$ 次更新操作中出现的所有数组成一个节点数为 $2^{n+1}-1$ 的满二叉树。其中，从下往上数第 $i$ 层的节点代表第 $i$ 次操作前序列 $a$ 的状态，最后的答案就是根节点的值。时间复杂度 $\operatorname{O}(2^{n+1}-1)$

虽然两个方法时间复杂度相同，但方法2在多组询问中更胜一筹

最开始，我们把初始序列 $a$ 对应的满二叉树预处理出来  
在每次询问前修改元素后（假如修改的元素位置为 $x$），我们发现有变化的节点都在 $x$ 到根节点的路径上，并且这些节点的总数不超过 $n$  
这样，每次询问时只需 $\operatorname{O}(n)$ 修改二叉树， $\operatorname{O}(1)$ 查询答案。总时间复杂度 $\operatorname{O}((2^{n+1}-1)+(nm))$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const long long Maxn=3000000+10;
long long a[Maxn],d[Maxn];
long long n,m;
void dfs(long long x) // dfs 预处理
{
	if(x>=(1<<(n+1)))return; // 注意：这种写法一定要判断边界，不然就无限递归了
	d[x]=d[x>>1]+1; // 计算深度，根节点的深度为 1
	dfs(x<<1);
	dfs(x<<1|1);
	if(a[x]!=-1)return; // 如果是叶子节点，就不需要合并子树信息
	if((n-d[x]) & 1)a[x]=(a[x<<1]^a[x<<1|1]); // 判断是异或还是按位或
	else a[x]=(a[x<<1]|a[x<<1|1]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<(1<<(n+1));++i)
	a[i]=-1;
	for(long long i=(1<<(n+1))-(1<<n);i<(1<<(n+1));++i)
	scanf("%lld",a+i); // 给叶子节点赋值
	dfs(1);
	while(m--)
	{
		long long x,val;
		scanf("%lld%lld",&x,&val);
		x=(1<<(n+1))-(1<<n)+x-1; // 找到在树中对应的位置
		a[x]=val;
		while(x>1) // 更新祖先
		{
			x>>=1;
			if((n-d[x]) & 1)a[x]=(a[x<<1]^a[x<<1|1]);
			else a[x]=(a[x<<1]|a[x<<1|1]);
		}
		printf("%lld\n",a[1]);
	}
	return 0;
}
```

---

## 作者：Cylete (赞：4)

读懂题目其实就是一颗线段树而已

第一次运算将$a_1$和$a_2$，$a_3$和$a_4……$，$a_{n - 1}$和$a_n$两两 或 $|$，得到一个新序列从$a_1$到$a_{n/2}$

第二次运算将$a_1$和$a_2$，$a_3$和$a_4……$，$a_{n/2 - 1}$和$a_{n/2}$两两 异或$xor$ ，得到一个新序列从$a_1$到$a_{n/4}$

第三次运算将$a_1$和$a_2$，$a_3$和$a_4……$，$a_{n/4 - 1}$和$a_{n/4}$两两 或 $|$ ，得到一个新序列从$a_1$到$a_{n/8}$

………………

显然这是一个递归向上计算的过程

线段树维护即可

注意深度是倒着的！

```cpp
#define mid ((l+r)>>1)
#define lson (o<<1)
#define rson (o<<1|1)

const int N = 2e5 + 10;

int n, m, a[N];
int tree[N << 2], deep[N << 2];

inline void build(int o, int l, int r)
{
	if(l == r)
	{
		tree[o] = a[l];
		return;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
	deep[o] = deep[lson] + 1;
	if(deep[o] & 1) tree[o] = tree[lson] | tree[rson];
	else tree[o] = tree[lson] ^ tree[rson];
}

inline void update(int o, int l, int r, int pos, int k)
{
	if(l == r)
	{
		tree[o] = k;
		return;
	}
	if(pos <= mid) update(lson, l, mid, pos, k);
	else update(rson, mid + 1, r, pos, k);
	if(deep[o] & 1) tree[o] = tree[lson] | tree[rson];
	else tree[o] = tree[lson] ^ tree[rson];
}

int x, y;

signed main()
{
	into();
	read(n); read(m);
	n = (1 << n);
	for(R int i = 1; i <= n; i++) read(a[i]);
	build(1, 1, n);
	while(m--)
	{
		read(x); read(y);
		update(1, 1, n, x, y);
		writeln(tree[1]);
	}
	return 0;
}
```

---

## 作者：MVP_Harry (赞：3)

~~这题居然是紫题，好爽~~

其实还是比较简单的，只有两个需要注意的地方：1. 线段树的单点修改操作 2.如何对题目条件进行转换

如果想不出来的话，可以画个图理解一下。这个图长得跟二叉树一样，所以我们每次就利用两个儿子来跟新父节点。设目前这个节点为$p$,并解得它二进制的位数$k$,不难发现，如果$N + 1 - k$为奇数，就用$|$更新，否则用^ 更新。

根据线段树的一些基本操作，我们可以得到一下的代码：

```
#include<bits/stdc++.h>
using namespace std;

const int maxn = 19;

int d[1 << maxn], a[(1 << (maxn - 2)) + 5], N, M;

int convert(int x) { //如前面所述，找出p的二进制位数
	int digit = 0;
	for (digit = 0; x > 0; x >>= 1) digit++;
	return digit;
}

void build(int s, int t, int p) { //建立线段树
	if (s == t) { 
		d[p] = a[s];
		return ;
	}
	int m = (s + t) >> 1;
	build(s, m, p << 1), build(m + 1, t, p << 1 | 1);
	int num = convert(p);
	if ((N + 1 - num) & 1) d[p] = d[p << 1] | d[p << 1 | 1];
	else d[p] = d[p << 1] ^ d[p << 1 | 1]; //根据我们前面所观察到的性质，回溯更新节点
}

void update(int c, int x, int s, int t, int p) { //同理，只是换成了更新
	if (s == t) {
		d[p] = x;
		return ;
	}
	int m = (s + t) >> 1;
	if (c <= m) update(c, x, s, m, p << 1);
	else update(c, x, m + 1, t, p << 1 | 1);
	int num = convert(p);
	if ((N + 1 - num) & 1) d[p] = d[p << 1] | d[p << 1 | 1];
	else d[p] = d[p << 1] ^ d[p << 1 | 1];
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= (1 << N); i++) 
    	cin >> a[i];
    build(1, 1 << N, 1);
    int c, k;
    while (M--) {
    	cin >> c >> k;
    	update(c, k, 1, 1 << N, 1);
    	cout << d[1] << endl; //输出d[1]即可
    }
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

考虑线段数，保存节点深度（如果节点对应区间覆盖恰好一个元素，定义深度为0，否则深度为左孩子深度加1）

更新一个值的时候，从小区间开始更新。如果深度为0，则设区间值为更行值。否则：

 1. 如果深度为偶数，区间值等于左孩子区间值异或右孩子区间值；
 2. 如果深度为奇数，区间值等于左孩子区间值二进制或右孩子区间值。

递归形式更新，先判断更新位置在左孩子区间里还是在右孩子区间里，更新那个区间，然后更新此区间。

我用了一个动态开点深度18的线段数。

```c++
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

class SST {
public:
    int d, v;
    SST* ch[2];
    SST(int d) : d(d), v(0) {
        if(d) {
            ch[0] = new SST(d-1);
            ch[1] = new SST(d-1);
        }
    }
    void inc(int i, int v0) {
        if(!d) {
            v = v0;
            return;
        }
        bool cv = i&(1<<(d-1));
        ch[cv]->inc(i, v0);
        if(d%2) v = ch[0]->v | ch[1]->v;
        else v = ch[0]->v ^ ch[1]->v;
    }
};


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    int sz = 1<<n; SST* s = new SST(18);
    rep(i, sz) {
        int v; cin >> v;
        s->inc(i, v);
    }
    while(m--) {
        int i, v; cin >> i >> v;
        s->inc(i-1, v);
        cout << s->v << endl;
    }
}
```

---

## 作者：Zekrom (赞：2)

~~不开ll见祖宗~~      
思路很简单，线段树维护深度d，d%2==1时或，$0$时亦或      
上代码       
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define inf 0x3f3f3f3f
#define ll long long 
#define N 1<<17+2
using namespace std;
ll n,m,a[N]; 
struct STree{
	ll v,l,r,d;
	#define v(x) tree[x].v
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define d(x) tree[x].d
}tree[N<<2];
inline ll read(){
	ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
inline void upd(int p){d(p)=d(p<<1)+1;if(d(p)%2)v(p)=v(p<<1)|v(p<<1|1);else v(p)=v(p<<1)^v(p<<1|1);}
void build(int p,int l,int r){
	l(p)=l,r(p)=r;if(l==r){v(p)=a[l];return;
	}int mid=(l+r)>>1;build(p<<1,l,mid);build(p<<1|1,mid+1,r);upd(p);
}
void change(int p,int x,ll y){
	if(l(p)==r(p)){v(p)=y;return;
	}int mid=(l(p)+r(p))>>1;if(x<=mid)change(p<<1,x,y);else change(p<<1|1,x,y);upd(p);
}
int main(){
	n=read();m=read();
	for(int i=1;i<=(1<<n);i++)a[i]=read();
	build(1,1,1<<n);
	for(int i=1;i<=m;i++){
		ll x=read();
		ll y=read();
		change(1,x,y);
		printf("%lld\n",v(1));
	} 
	return 0;
}

```


---

## 作者：Sober_Clever (赞：1)

[题目](https://www.luogu.org/problemnew/show/CF339D)

线段树单点修改

t[p].step记录log2( len )( len=t[p].r-t[p].l+1 )

若step为奇数则push_up时运算符为或

反之为异或

```cpp
#include<cstdio>
using namespace std;
const int MAXN=(1<<17) + 3;

int read()
{
    int x=0,w=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}
    return x*w;
}

struct Segment_Tree
{
    int l,r;
    int step,sum;
}t[MAXN<<2];
int a[MAXN];

inline void Push_up(int p)
{
    if(t[p].step%2) t[p].sum=t[p<<1|1].sum|t[p<<1].sum;
    else t[p].sum=t[p<<1].sum^t[p<<1|1].sum;
}

void Build(int p,int l,int r,int step)
{
    t[p].l=l,t[p].r=r,t[p].step=step;
    if(l==r)
    {
        t[p].sum=a[l];
        return ;
    }
    int mid=(l+r)>>1;
    Build(p<<1,l,mid,step-1);
    Build(p<<1|1,mid+1,r,step-1);
    Push_up(p);
}

void Upd(int p,int l,int r,int x,int y)
{
    if(l==r)
    {
        t[p].sum=y;
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid) Upd(p<<1,l,mid,x,y);
    else Upd(p<<1|1,mid+1,r,x,y);
    Push_up(p);
}
int main()
{
    int len,n=read(),m=read();
    len=1<<n;
    for(int i=1;i<=len;i++) a[i]=read();
    Build(1,1,len,n);
    while(m--)
    {
        int x=read(),y=read();
        Upd(1,1,len,x,y);
        printf("%d\n",t[1].sum);
    }
    return 0;
}

```
~~其实long long 是不必开的（手动@Zerom大佬）~~

---

## 作者：da32s1da (赞：1)

我们发现线段树可以完美解决这个问题。

因为保证有$2^n$个数字。。。

```
#include<cstdio>
const int N=1050000;
int n,m,x,y,q;
int tre[N];
void jia(int now,int ls,int rs,int mb,int val,int t){
	//t为当前在第几层
	if(ls>mb||rs<mb)return;
	if(ls==rs){
    	//此时t=0
		tre[now]=val;
		return;
	}
	int noww=now<<1,nrs=ls+rs>>1;
	jia(noww,ls,nrs,mb,val,t-1);
	jia(noww|1,nrs+1,rs,mb,val,t-1);
	if(t&1)tre[now]=tre[noww]|tre[noww|1];
	else tre[now]=tre[noww]^tre[noww|1];
    //第1层为|，然后交替
    //故t为奇数时or，偶数时xor
}
int main(){
	scanf("%d%d",&n,&m);
	q=n;n=1<<n;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		jia(1,1,n,i,x,q);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		jia(1,1,n,x,y,q);
		printf("%d\n",tre[1]);
	}
}
```

---

## 作者：Saber_Master (赞：0)

[CF339D Xenia and Bit Operations](https://www.luogu.com.cn/problem/CF339D)

有意思.

有$2^n$个数，然后要维护那个长长的，复杂的，一层一层套下去的式子.我们可以观察到除最内层外每个括号内的两个括号所括住的数字个数相等，于是可以想到分治.

分治+单点修改+整体查询，这能想到什么？没错，线段树.

开一棵线段树，对每一层我们维护一个$tag$表示该层进行何种运算，然后就很简单啦.

$O(n \log n)$

```cpp
ll v[N];
namespace seg{
	ll dat[N<<2];
	bool tag[N<<2];
	//tag为true表示该层进行按位或，false表示进行按位异或.
	inline void build(ll p, ll l, ll r){
		if (l==r) return (void)(dat[p]=v[l], tag[p]=false);
		ll mid=l+r>>1;
		build(p<<1, l, mid); build(p<<1|1, mid+1, r);
		tag[p]=tag[p<<1]^1;
		if (tag[p]) dat[p]=(dat[p<<1]|dat[p<<1|1]);
		else dat[p]=(dat[p<<1]^dat[p<<1|1]);
	}
	
	inline void update(ll p, ll l, ll r, ll k, ll val){
		if(l==r) return (void)(dat[p]=val);
		ll mid=l+r>>1;
		if(k<=mid) update(p<<1, l, mid, k, val);
		else update(p<<1|1, mid+1, r, k, val);
		if (tag[p]) dat[p]=(dat[p<<1]|dat[p<<1|1]);
		else dat[p]=(dat[p<<1]^dat[p<<1|1]);		
	}
	
	inline ll query(){
		return dat[1];
	}
}

ll n, m;
int main(){
	read(n); read(m);
	n=(1ull<<n);
	for (R ll i=1; i<=n; i++) read(v[i]);
	seg::build(1, 1, n);
	ll x, y;
	while(m--){
		read(x); read(y);
		seg::update(1, 1, n, x, y);
		writeln(seg::query());
	}
} 

```


---

## 作者：青鸟_Blue_Bird (赞：0)

题目大意：

给定一个序列，每次选择一个点修改权值，然后求出全序列的值。

不难想到，直接用线段树维护就好了：

#### 就一个单点修改

同时，在建树的时候，我们求出每一段的深度。pushup时，根据单双数来判断是按位或还是亦或运算。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000010
#define QAQ 0

inline int read(){
	int x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-')s = -1;
		c = getchar();
	}
	while(isdigit(c)){
		x = x * 10 + (c ^ '0');
		c = getchar();
	}
	return x * s;
}

int a[N];
struct tree{
	int w, deth;
} t[N];

inline void pushup(int o){   /*更新*/
	if(t[o].deth % 2) t[o].w = t[o << 1].w | t[o << 1 | 1].w;
	else t[o].w = t[o << 1].w ^ t[o << 1 | 1].w;
	return ;
}

void build(int o, int l, int r){
	if(l == r){
		t[o].w = a[r];
		return ;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	t[o].deth = t[o << 1].deth + 1;  /*记录深度*/
	pushup(o);
	return ;
}

void update(int o, int l, int r, int x, int k){ /*经典操作： 单点修改*/
	if(l > x || r < x) return ;
	if(l == x && r == x){
		t[o].w = k;  
		return ;
	}
	int mid = l + r >> 1;
	update(o << 1, l, mid, x, k);
	update(o << 1 | 1, mid + 1, r, x, k);
	pushup(o);
	return ;
}

int main(){
	int n = read(), m = read();
	for(int i = 1;i <= (1 << n); i++){
		a[i] = read();
	}
	build(1, 1, 1 << n);  /*千万不要忘了先建树啊！！  QAQ*/
	while(m--){
		int x = read(), y = read();
		update(1, 1, 1 << n, x, y);
		printf("%d\n", t[1].w);
	}
	return QAQ;
}
```


---

