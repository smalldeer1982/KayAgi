# CNTPRIME - Counting Primes

## 题目描述

给你一个 $n$ 个数的数组和 $m$ 个操作：

- $0\ x\ y\ v$ 将 $x$ 到 $y$ 之间的所有数改成 $v$。

- $1\ x\ y$ 求 $x$ 到 $y$ 之间的质数个数。

数组下标为 $1$ 到 $n$。

## 说明/提示

- 使用较快的输入输出方式，如 `scanf` 和 `printf`。

- 一个质数是一个除了 $1$ 和它本身意外没有其他正因数的大于 $1$ 的自然数。前几个质数是 $2,3,5,7,11...$

## 样例 #1

### 输入

```
1
5 3
78 2 13 12 3
1 1 2
0 4 4 5
1 1 5```

### 输出

```
Case 1:
1
4```

# 题解

## 作者：Larry76 (赞：7)

## 前言：

不知道为什么大家**都**写 ODT，可能因为珂朵莉太可爱了？

## 题目描述：

给定初始序列 $A$，然后对原序列有以下操作：

1. 操作 $1$： `0 l r v` 将区间 $[l,r]$ 全赋值为 $v$。
2. 操作 $2$：`1 l r` 查询区间 $[l,r]$ 的质数个数。

**注意：多组测试和特殊的输出。**

## 题目分析：

就是一道板子题，首先我们先用欧拉筛筛出值域 $[2,10^6]$ 内的素数并开桶打标记（实际上一个欧拉筛就行了）。

此时，线段树维护的是当前区间内质数的个数，我们可以将操作 $1$ 变成如下操作：
- 若 $v$ 属于质数，则将区间 $[l,r]$ 内的数全赋值成 $1$。
- 若 $v$ 不属于质数，则将区间 $[l,r]$ 内的数全赋值成 $0$。

那么，操作 $2$ 此时显然就变成了一个区间求和。

时间复杂度，$O(n\lg n)$。

## 代码实现：
```cpp
#include <bits/stdc++.h>
#define dbg(x) cerr<<#x<<": "<<x<<endl;
using namespace std;
#define MAX_SIZE (int)2e6
#define MAX_RANGE (int)1.1e6

bool nf[MAX_RANGE];
int primes[MAX_RANGE];
inline void primeshai(int n){
    for(register int i=2;i<=n;i++){
        if(!nf[i])
            primes[++primes[0]] = i;
        for(register int j=1;j<=primes[0]&&primes[j]*i<=n;j++){
            nf[primes[j]*i] = 1;
            if(i%primes[j]==0)
                break;
        }
    }
}

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

struct SegmentTree{
    int sum;
    int lazy;
    int l,r;
    int len;
};
SegmentTree seg[MAX_SIZE<<2];
int a[MAX_SIZE];

void build(int p,int l,int r)
{
    seg[p].l = l;
    seg[p].r = r;
    seg[p].lazy = -1;
    seg[p].len = r-l+1;
    if(l==r){
        seg[p].sum = !nf[a[l]];
        return;
    }
    int mid = (l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    seg[p].sum = seg[p<<1].sum + seg[p<<1|1].sum;
}

inline void spread(int p){
    if(seg[p].lazy!=-1){
        seg[p<<1].sum = seg[p].lazy*seg[p<<1].len;
        seg[p<<1|1].sum = seg[p].lazy*seg[p<<1|1].len;
        seg[p<<1].lazy = seg[p].lazy;
        seg[p<<1|1].lazy = seg[p].lazy;
        seg[p].lazy = -1;
    }
}

inline void modify(int p,int l,int r,int val){
    if(l<=seg[p].l&&r>=seg[p].r){
        seg[p].sum = val * seg[p].len;
        seg[p].lazy = val;
        return;
    }
    if(seg[p].lazy>=0)
        spread(p);
    int mid = (seg[p].l+seg[p].r)>>1;
    if(l<=mid)
        modify(p<<1,l,r,val);
    if(r>mid)
        modify(p<<1|1,l,r,val);
    seg[p].sum = seg[p<<1].sum + seg[p<<1|1].sum;
}

inline int query(int p,int l,int r){
    if(l<=seg[p].l&&r>=seg[p].r)
        return seg[p].sum;
    if(seg[p].lazy>=0)
        spread(p);
    int val = 0;
    int mid = (seg[p].l+seg[p].r)>>1;
    if(l<=mid)
        val += query(p<<1,l,r);
    if(r>mid)
        val += query(p<<1|1,l,r);
    return val;
}

int main(){
    ios::sync_with_stdio(false);
    cout.tie(0);
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    double c1 = clock();
#endif
//============================================
    primeshai(1e6);
    int T;
    T = read();
    for(int x=1;x<=T;x++){
        cout<<"Case "<<x<<':'<<endl;
        int n = read();
        int q = read();
        for(int i=1;i<=n;i++)
            a[i] = read();
        build(1,1,n);
        while(q--){
            switch(read()){
                case 0:{
                    int l = read();
                    int r = read();
                    int y = read();
                    modify(1,l,r,!nf[y]);
                    break;
                }
                case 1:{
                    int l = read();
                    int r = read();
                    cout<<query(1,l,r)<<endl;
                    break;
                }
            }
        }
    }
//============================================
#ifdef LOCAL
    double c2 = clock();
    cerr<<"Used Time: "<<c2-c1<<"ms"<<endl;
    if(c2-c1>1000)
        cerr<<"Warning!! Time Limit Exceeded!!"<<endl;
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
```

---

## 作者：hello_world_djh (赞：7)

更富有激情的阅读体验：[SP13015 CNTPRIME - Counting Primes 题解](https://www.cnblogs.com/hello-world-djh/p/odt_sol.html)

亲，这是本蒟蒻的第一篇题解，记得多多点赞支持呦。

一道不错的 ODT 练手题，题目传送门： [SP13015 CNTPRIME - Counting Primes](https://www.luogu.com.cn/problem/SP13015)。

~~翻译是我写的~~

接下来将会从零开始学习 ODT，会 ODT 的大爷可以跳转到正文部分。

# ODT

ODT，全名为 Old Driver Tree，又名珂朵莉树，是毒瘤 lxl 发明的暴力数据机构。其本质思想是通过 STL 的 set 维护权值相同的区间，达到优化暴力时间复杂度的目的。其核心函数是 split 和 assign，也就是分裂区间和区间推平。

注意: 因为它的时间复杂度维护区间的数量越少越优，所以只能做有区间推平较多的题目，也就是需要数据随机

接下来会具体讲解 ODT：

## ODT 的建立

定义一个 `struct`，维护每一个权值相同的区间的左端点、右端点和权值。因为要存到 `set` 中， 所以要重载小于号。这里我们按照左端点升序排序。在后面的分裂操作会解释按左端点排序的原因。

代码：

```cpp
struct ODT {
	int l, r, val;
	ODT(int _l = 0, int _r = 0, int _val = 0): l(_l), r(_r), val(_val) {return;}
	bool operator < (const ODT &x) const {
		return l < x.l;
	}
}
std::set<ODT> tree;
```

## 分裂

分裂是 ODT 最重要的操作，ODT 的所有衍生操作都是以分裂操作为基础的。

在定义是我们按照左端点升序排序，就是为了分裂操作方便。我们分裂操作要求支持分裂出一个以 $x$ 为左端点的区间，并传回它的指针。因为我们是按照左端点升序排序，所以可以直接用 `set` 自带的 `lower_bound` 查询。注意不要使用 `algorithm` 的 `lower_bound` 查询，个别题目会 TLE。

如果我们没有找到以 $x$ 为左端点的区间，我们可以将找到的区间的上一个区间分裂。因为 `lower_bound` 的性质，我们分裂的这个区间的左端点一定小于等于 $x$，所以可以进行分裂。

代码：

```cpp
#define It std::set<ODT>:: iterator

It split(int x) {
	It it = tree.lower_bound(x);
	if (it != tree.end() && it->l == x) return it;
	it--; int l = it->l, r = it->r, val = it->val;
	tree.erase(it); tree.insert(ODT(l, x - 1, val));
	return tree.insert(ODT(x, r, val)).first;
}
```

## 区间推平

ODT 维护复杂度正确性的重要操作就是区间推平。这个操作很好写但也很容易错。大佬 [泥土笨笨](https://www.luogu.com.cn/user/43206) 曾在 ODT 博客 [珂朵莉树模板CF896C Willem, Chtholly and Seniorious题解](https://www.luogu.com.cn/blog/nitubenben/solution-cf896c) 指正了该题目题解区一群题解区间推平的错误。

assign 的实现是通过将 $r + 1$ 和 $l$ 的区间分裂出来，再通过 `set` 的 `erase` 操作删除两个区间之间的所有区间，并插入一个大区间就可以了

注意：正如泥土笨笨所说，应该先分裂右端点再分裂左端点。因为如果先分裂左端点，分裂右端点时可能会影响左端点的区间的状态。

如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/kh10a2ll.png)

这是一棵区间推平前的 ODT。现在我们要将 $[2, 4]$ 区间推平。如果我们先分裂左端点：

![](https://cdn.luogu.com.cn/upload/image_hosting/03pylra7.png)

此时左端点分裂出的区间为第二个区间。再分裂右端点：

![](https://cdn.luogu.com.cn/upload/image_hosting/uvsayzv8.png)

此时我们可以看到之前的区间二被分裂了，也就意味着那个指针被删除了。之后对那个区间的调用都是无效调用。如果先分裂左再分裂右就有可能 RE。

代码：

```cpp
#define It std::set<ODT>::iterator

void assign(int l, int r, int val) {
	It itr = split(r + 1), itl = split(l);
	tree.erase(itl, itr); tree.insert(ODT(l, r, val));
	return;
}
```

# 正文

~~啊哈哈哈，正文来喽。~~

这个题算比较好的 ODT 练手题。可以先欧拉筛 $O(\max{a_i})$ 预处理所有的质数。然后只需要维护分裂、区间推平和查询操作即可。

多组数据记得清空呦~~

代码：

```cpp
#include <bits/stdc++.h>
#define It set<ODT>::iterator

using namespace std;

const int N = 2e6 + 10;
int prime[N], pcnt; bool not_prime[N];

void eular() {
	not_prime[0] = not_prime[1] = true;
	for (int i = 2; i <= N; i++) {
		if (!not_prime[i]) {
			prime[++pcnt] = i;
		}
		for (int j = 1; j <= pcnt && i * prime[j] <= N; j++) {
			not_prime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	return;
}

struct ODT {
	int l, r;
	mutable int val;
	bool operator < (const ODT &x) const {
		return l < x.l;
	}
	ODT(int _l = 0, int _r = 0, int _val = 0):l(_l), r(_r), val(_val){return;}
};
set<ODT> tree;

It split(int x) {
	It it = tree.lower_bound(ODT(x));
	if (it != tree.end() && it->l == x) return it;
	it--; int l = it->l, r = it->r, val = it->val;
	tree.erase(it); tree.insert(ODT(l, x - 1, val));
	return tree.insert(ODT(x, r, val)).first;
}

void assign(int l, int r, int val) {
	It itr = split(r + 1), itl = split(l);
	tree.erase(itl, itr);
	tree.insert(ODT(l, r, val));
	return;
}

int query(int l, int r) {
	int ans = 0; It itr = split(r + 1), itl = split(l);
	for (It it = itl; it != itr; it++) {
		if (!not_prime[it->val]) ans += it->r - it->l + 1;
	}
	return ans;
}

int t, n, q;

int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	eular();
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case " << i << ':' << endl;
		cin >> n >> q;
		tree.clear();
		for (int j = 1, x; j <= n; j++)
			cin >> x, tree.insert(ODT(j, j, x));
		for (int j = 1, op, x, y, v; j <= q; j++) {
			cin >> op >> x >> y;
			if (!op) {
				cin >> v;
				assign(x, y, v);
			}
			else {
				cout << query(x, y) << endl;
			}
		}
	}
	return 0;
}
```

完结撒花（超小声

---

## 作者：a2lyaXNhbWUgbWFyaXNh (赞：6)

其实是一道很简单的珂朵莉树啦。

区间推平是 odt 的基本操作，这里不再赘述。

数据范围说了所有的数都小于等于 $10^6$，所以操作二用素数筛筛到 $10^6$ 预处理。SPOJ 空间大，所以我用了欧拉筛。但是 `std::bitset<>` 优化过的埃氏筛应该也能跑。

**唯二的坑点就是多测清空和格式要求。务必牢记。**

题目建议使用 `StdIO` 读入。像我一样的 `IOStream` 人最好关一下同步流加速。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define TIPS "ctjzm"
#define IT set<node>::iterator
typedef long long TYPE;

int prime[1000007];
bool f[1000007];

void sieve(){
    int n=1000000;  
    f[0]=f[1]=1;
    int cnt=1;
    for(int i=2;i<=n;i++){
        if(!f[i])
            prime[cnt++]=i;
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            f[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }   
    }
}//线性筛

struct node{
    unsigned int l,r;
    mutable TYPE v;
    node(unsigned int left,unsigned int right=0,TYPE value=0);
};
bool operator<(node a,node b){
    return a.l<b.l;
}
node::node(unsigned int left,unsigned int right,TYPE value){
    l=left;
    r=right;
    v=value;
}
set<node>odt; 
inline IT split(unsigned int p){
    IT it=odt.lower_bound(node(p));
    if(it!=odt.end()&&it->l==p)
        return it;
    --it;
    unsigned r=it->r,l=it->l;
    TYPE v=it->v;
    odt.erase(it);
    odt.insert(node(l,p-1,v));
    return odt.insert(node(p,r,v)).first;   
}//珂朵莉树核心——分裂操作
inline void assign(int l, int r, int v) {
    IT itr=split(r+1),itl=split(l);//请确保先 split(r+1) 再 split(l)，否则会 RE，适用于所有珂朵莉树
    odt.erase(itl, itr);
    odt.insert(node(l, r, v));
}//操作1+珂朵莉树核心——推平操作
//祖传珂朵莉树模板↑
inline int getcnt(int l,int r){
    long long cnt=0;
    IT itr=split(r+1),itl=split(l);
    for(IT it=itl;it!=itr;++it)
        if(!f[it->v])
            cnt+=it->r-it->l+1;
    return cnt;        
}//操作2，统计素数

int n,m,x,y,z,t;
int ch;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(nullptr);//不关同步流可能会超时
    sieve();//预处理
    cin>>t;
    for(int T=1;T<=t;++T){
        odt.clear();//多测清空！
        cout<<"Case "<<T<<":\n";//严格的格式要求
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            int t;
            cin>>t;
            odt.insert(node(i,i,t));
        }
        for(int i=1;i<=m;++i){
            cin>>ch;
            if(!ch){
                cin>>x>>y>>z;
                assign(x,y,z);
            }
            else{
                cin>>x>>y;
                cout<<getcnt(x,y)<<'\n';
            }
        }
    }
    return 0;//好习惯
}
```

~~有没有神犇尝试手写红黑树实现珂朵莉树的，应该会更快。~~

姊妹题：[SPOJ19568 PRMQUER](https://www.luogu.com.cn/problem/SP19568)

---

## 作者：Unnamed114514 (赞：5)

[另：大道至简，暴力卡常可过](https://www.luogu.com.cn/record/97151544)

紫：难度虚高，顶多评黄

注意到本题只与一个数是否是素数有关，所以本题可以转化为 0/1 序列问题。

我们先用素数筛，记 $P_i$ 为 $i$ 是否为素数，所以我们只需要关注 $P_{a_i}$ 和 $P_v$，操作 $0$ 就是区间赋 $P_v$，操作 $1$ 就是区间求和。

那么我们就将问题转化为了线段树模板，时间复杂度 $O(q\log n)$，空间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
inline char gc(){
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int res=0;
	char ch=gc();
	while(ch<'0'||ch>'9') ch=gc();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=gc();
	}
	return res;
}
const int maxn=1e6+5;
int n,q,tot,a[maxn];
bool P[maxn];
int cnt,prime[maxn];
inline void Prime(int n){
	P[0]=P[1]=1;
	for(int i=2;i<=n;i++){
		if(!P[i]) prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			P[i*prime[j]]=1;
			if(!(i%prime[j])) break;
		}
	}
}
struct ST{
	#define ls p<<1
	#define rs p<<1|1
	struct node{
		int p,l,r,num,tag;
	}T[maxn<<2];
	void Build(int p,int l,int r){
		T[p].p=p,T[p].l=l,T[p].r=r,T[p].tag=-1;
		if(l==r){
			T[p].num=!P[a[l]];
			return;
		}
		int mid=l+r>>1;
		Build(ls,l,mid),Build(rs,mid+1,r);
		T[p].num=T[ls].num+T[rs].num;
	}
	inline void pushdown(int p){
		if(T[p].l!=T[p].r&&~T[p].tag){
			T[ls].tag=T[rs].tag=T[p].tag;
			T[ls].num=(T[ls].r-T[ls].l+1)*T[p].tag;
			T[rs].num=(T[rs].r-T[rs].l+1)*T[p].tag;
			T[p].tag=-1;
		}
	}
	inline void Update(int p,int l,int r,int v){
		if(l<=T[p].l&&T[p].r<=r){
			T[p].tag=v;
			T[p].num=(T[p].r-T[p].l+1)*v;
			return;
		}
		pushdown(p);
		if(l<=T[ls].r) Update(ls,l,r,v);
		if(T[rs].l<=r) Update(rs,l,r,v);
	    T[p].num=T[ls].num+T[rs].num;
	}
	int Query(int p,int l,int r){
		if(l<=T[p].l&&T[p].r<=r) return T[p].num;
		pushdown(p);
		int res=0;
		if(l<=T[ls].r) res+=Query(ls,l,r);
		if(T[rs].l<=r) res+=Query(rs,l,r);
		return res;
	}
}T;
int main(){
	Prime(1e6);
	tot=read();
	for(int i=1;i<=tot;++i){
		n=read(),q=read();
		for(int i=1;i<=n;a[i++]=read());
		printf("Case %d:\n",i);
		T.Build(1,1,n);
		while(q--){
			int op=read(),l=read(),r=read();
			if(op) printf("%d\n",T.Query(1,l,r));
			else T.Update(1,l,r,!P[read()]);
		}
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：2)

题意：区间推平，区间求和。

一次区间赋值操作可以转化为如果赋值的操作是质数则全部赋值上 $ 1 $，否则赋值上 $ 0 $，然后转化为区间求和操作。判断质数的过程可以直接线性筛跑一遍。

不难想到这是珂朵莉树板子题，但是一般的珂朵莉树可能会被卡。

这里介绍一种非原创的黑科技，来自 [霖ux](https://www.luogu.com.cn/user/520914) 发明的 Splay-ODT，[链接](https://www.luogu.com.cn/paste/k74p9xib)，可以做到在时间复杂度正确的情况下使用 ODT 的全部操作。

于是结合这题需要支持的操作，稍微改一改即可通过此题。尊重原模板所以模板部分没有做太大的改动。

抢到了最优解，意外地比线段树跑得还快。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long 
#define exc(a,b) a^=b^=a^=b
using namespace std;
inline int read(){
  int x=0,f=1;char c=getchar();
  while(c<'0'||c>'9')f=(c!='-'),c=getchar();
  while(c>='0'&&c<='9')x=10*x+c-'0',c=getchar();
  if(f)return x;return -x;
}
const int maxn=1e4+10,mod=1e9+7;
int n,m,seed,vmax,a[maxn];
int qpow(int a,int x,int y){
  int ans=1;a%=y;while(x){
    if(x&1)ans=ans*a%y;
    a=a*a%y;x>>=1;
  }return ans;
}
const int N=1e6+20;
int prime[N];
bitset<N>vis;
int tot=0;
void pre(int n)
{
for(int i=2;i<n;i++)
{
    if(!vis[i])
    prime[tot++]=i;
    for(int j=0;j<tot;++j)
    {
    if(i*prime[j]>n)
    break;
    vis[i*prime[j]]=1;
    if(i%prime[j]==0)
    break;
    }
}
}
struct SPLAY{static const int maxsiz=maxn;
  int tr[maxsiz][2],fa[maxsiz],siz[maxsiz],len[maxsiz],val[maxsiz],tot;
  int st[maxsiz],top,root;
  int nt(int v,int l){
    int x=top?st[top--]:++tot;
    tr[x][0]=tr[x][1]=0;fa[x]=0;
    siz[x]=len[x]=l;val[x]=v;
    return x;
  }
  void del(int x){st[++top]=x;}
  void delall(int x){if(!x)return;delall(tr[x][0]);delall(tr[x][1]);del(x);}
  void nodesp(int x,int k,int&l,int&r){
    if(len[x]<=k){l=x,r=tr[x][1];tr[x][1]=fa[r]=0;pushup(x);return;}
    if(k<=0){l=tr[x][0],r=x;tr[x][0]=fa[l]=0;pushup(x);return;}
    l=nt(val[x],k);r=nt(val[x],len[x]-k);
    if(tr[x][0])tr[l][0]=tr[x][0],fa[tr[x][0]]=l;pushup(l);
    if(tr[x][1])tr[r][1]=tr[x][1],fa[tr[x][1]]=r;pushup(r);
    del(x);
  }
	void set(int x,int w,int y){fa[tr[x][w]]=0,fa[y]=x,tr[x][w]=y;pushup(x);}
  int nodemg(int x,int y){
    if(val[x]==val[y]){
      int res=nt(val[x],len[x]+len[y]);
      if(tr[x][0])tr[res][0]=tr[x][0];fa[tr[x][0]]=res;
      if(tr[y][1])tr[res][1]=tr[y][1];fa[tr[y][1]]=res;
      pushup(res);del(x);del(y);
      return res;
    }if(siz[x]>siz[y])return set(x,1,y),x;
	return set(y,0,x),y;
  }
  inline void pushup(int x){siz[x]=siz[tr[x][0]]+siz[tr[x][1]]+len[x];}
  inline int get(int x){return x==tr[fa[x]][1];}
  inline void rotate(int x){
    int y=fa[x],z=fa[y],w=get(x);
    if(z)tr[z][get(y)]=x;
    fa[x]=z,fa[y]=x,fa[tr[x][!w]]=y;
    tr[y][w]=tr[x][!w],tr[x][!w]=y;
    pushup(y);pushup(x);
  }
  inline void splay(int x){while(fa[x]){int y=fa[x];if(fa[y])rotate((get(x)==get(y))?y:x);rotate(x);}}
  inline int find(int x,int k){
    while(1){if(!x)break;
      if(k<=siz[tr[x][0]])x=tr[x][0];
      else if(k<=siz[tr[x][0]]+len[x])return x;
      else k-=siz[tr[x][0]]+len[x],x=tr[x][1];
    }return 0;
  }
  void split(int x,int k,int &l,int &r){
    if(k==0){l=0,r=x;return;}
    if(k==siz[x]){l=x,r=0;return;}
    splay(x=find(x,k));
    nodesp(x,k-siz[tr[x][0]],l,r);
  }
  int merge(int x,int y){
    if(!x||!y)return x|y;
    splay(x=find(x,siz[x]));splay(y=find(y,1));
    return nodemg(x,y);
  }
  void down(int x,int v){
    if(!x)return;
    down(tr[x][0],v);
    down(tr[x][1],v);
    val[x]+=v;pushup(x);
  }
  int sum(int x,int a,int b)
  {return x?(qpow(val[x],a,b)*len[x]%b+sum(tr[x][0],a,b)+sum(tr[x][1],a,b))%b:0;}
  struct num{int v,l;
    int operator<(num x){return v<x.v;}
  }tmp[maxsiz];int cnt=0;
  void collect(int x){
    if(!x)return;
    collect(tr[x][0]);
    collect(tr[x][1]);
    tmp[++cnt]={val[x],len[x]};
  }
  void opt2(){
    int l=read(),r=read(),v=!vis[read()];if(l>r)exc(l,r);
    int x,y,z;split(root,r,y,z);split(y,l-1,x,y);
    int ny=nt(v,siz[y]);delall(y);
    root=merge(x,merge(ny,z));
  }
  void opt4()
  {
    int l=read(),r=read(),v=1,p=1e9;if(l>r)exc(l,r);
    int x,y,z;split(root,r,y,z);split(y,l-1,x,y);
    printf("%lld\n",sum(y,v,p));
    root=merge(x,merge(y,z));
  }
  int build(int l,int r,int fax){
    if(l>r)return 0;
    int nl,nr,mid=nl=nr=(l+r)>>1;
    while(nl>1&&a[nl-1]==a[nl])nl--;
    while(nr<n&&a[nr+1]==a[nr])nr++;
    int x=nt(a[mid],nr-nl+1);fa[x]=fax;
    tr[x][0]=build(l,nl-1,x);
    tr[x][1]=build(nr+1,r,x);
    pushup(x);return x;
  }
}splay;
signed main()
{
    int T=read();
    pre(1e6);
    for(int i=1;i<=T;i++)
    {
    printf("Case %d:\n",i);
  n=read(),m=read();
  for(int i=1;i<=n;i++)
  a[i]=!vis[read()];
  splay.root=splay.build(1,n,0);
  for(int i=1;i<=m;i++)
  switch(read())
  {
    case 0:splay.opt2();break;
    case 1:splay.opt4();break;
  }
  splay.delall(splay.root);
  }
}
```


---

## 作者：Kreado (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/SP13015)

#### 题目大意

给你两个操作，区间推平和区间查询。

#### 思路

这题可以用分块，线段树和珂朵莉树，但对于初学者来说，线段树明显更优。

本题可以使用欧拉筛标记素数。

此时推平操作可以转换为：

- 如果 $v \in prime$，则将区间 $[l,r]$ 的所有数改为 $1$。

- 如果 $v \notin prime$，则将区间 $[l,r]$ 的所有数改为 $0$。

注意：

1. 本题样例未给，可以在代码最后看。

2. 注意本题要输出 `Case X:`，详见代码或样例处。

最后区间查询求和即可。

[CODE](https://www.luogu.com.cn/paste/sphd5q9w)。

当然，也不能少了我们可爱的珂朵莉(树)啦。

考虑到有区间推平，显然可以用珂朵莉树。

如果想要学习珂朵莉树的话，可以参考这个文章：[1](https://studyingfather.blog.luogu.org/odt-note).

[CODE](https://www.luogu.com.cn/paste/3w9cz4ag)。

---

## 作者：Hanx16Kira (赞：2)

# SP13015 CNTPRIME - Counting Primes

[SP13015(Luogu)](https://www.luogu.com.cn/problem/SP13015)

## Solution

首先先要知道题目要求我们做什么。题目给出了一个长为 $n$ 的数列，并且有 $q$ 个操作。有两类操作，一类是区间赋值，另一类是询问区间质数个数。

既然有区间推平的操作，那为什么不用珂朵莉树试试呢？（如果你不会珂朵莉树，可以看我写过的一篇[博客](https://www.cnblogs.com/hanx16msgr/p/16534612.html)，这里面我详细介绍了珂朵莉树这一种数据结构的基础做法）

那么我们先将数列构造成为珂朵莉树，那么区间推平这一操作是珂朵莉树自带的操作，所以只用考虑如何求解区间质数个数这一问题。

珂朵莉树基础操作：

```c++
struct Node{
    int l,r;
    mutable int v;
    Node(int l,int r=0,int v=0) : l(l),r(r),v(v) {}
    bool operator< (const Node &a) const{
        return l<a.l;
    }
};
set<Node> ctlt;
auto split(int pos)//分裂区间
{
    auto it=ctlt.lower_bound(Node(pos));
    if (it!=ctlt.end() && it->l==pos) return it;
    it--;
    if (it->r<pos) return ctlt.end();
    int l=it->l,r=it->r,v=it->v;
    ctlt.erase(it);
    ctlt.insert(Node(l,pos-1,v));
    return ctlt.insert(Node(pos,r,v)).first;
}
void assign(int l,int r,int v)//区间推平
{
    auto itr=split(r+1),itl=split(l);
    ctlt.erase(itl,itr);
    ctlt.insert(Node(l,r,v));
}
```

首先可以用质数筛法预处理出 $[1,10^6]$ 范围内的质数，这个范围用埃筛就够了，用不上线性筛。那么对于询问的区间 $[l,r]$ ，就可以用类似珂朵莉树的 `assign` （区间赋值）进行操作，即扫一遍 $[l,r]$ 间的所有区间，如果区间对应的 $[l,r,v]$ 中 $v$ 是质数，那么这一个区间就会对答案产生 $r-l+1$ （即区间长度）的贡献，具体可以参考代码理解：

```c++
void prework()//埃筛
{
    prime[1]=1;//1不是质数，所以标记上就行
    for (int i=2;i<=MAXN;i++)
        if (!prime[i])//当前是质数
            for (int j=2;j*i<=MAXN;j++) prime[i*j]=1;//当前质数的所有倍数都是合数
}
int query(int l,int r)
{
    auto itr=split(r+1),itl=split(l);//类似assign操作
    int res=0;//记录[l,r]的区间质数个数
    for (auto it=itl;it!=itr;it++)//遍历之间的所有区间
        if (!prime[it->v]) res+=it->r - it->l +1;//如果这个区间的值v是质数，那么将会对答案产生r-l+1的贡献
    return res;
}
```

除开这些操作之外还有一点需要注意，就是在每次输出的时候都要记得先输出一个 `Case i:` （ `i` 表示第 $i$ 组数据），我就是因为这个东西检查了半天都没检查出来问题。

### Code

```c++
#include<bits/stdc++.h>
using namespace std;
template<typename T> void read(T &k)//快读模板
{
    k=0;T flag=1;char b=getchar();
    while (!isdigit(b)) {flag=b=='-'?-1:1;b=getchar();}
    while (isdigit(b)) {k=k*10+b-48;b=getchar();}
    k*=flag;
}
struct Node{
    int l,r;
    mutable int v;
    Node(int l,int r=0,int v=0) : l(l),r(r),v(v) {}
    bool operator< (const Node &a) const{
        return l<a.l;
    }
};
set<Node> ctlt;
auto split(int pos)//分裂区间
{
    auto it=ctlt.lower_bound(Node(pos));
    if (it!=ctlt.end() && it->l==pos) return it;
    it--;
    if (it->r<pos) return ctlt.end();
    int l=it->l,r=it->r,v=it->v;
    ctlt.erase(it);
    ctlt.insert(Node(l,pos-1,v));
    return ctlt.insert(Node(pos,r,v)).first;
}
void assign(int l,int r,int v)//区间推平
{
    auto itr=split(r+1),itl=split(l);
    ctlt.erase(itl,itr);
    ctlt.insert(Node(l,r,v));
}
const int MAXN=1e6;
bool prime[MAXN+5];
int n,q,T;
void prework()//埃筛
{
    prime[1]=1;//1不是质数，所以标记上就行
    for (int i=2;i<=MAXN;i++)
        if (!prime[i])//当前是质数
            for (int j=2;j*i<=MAXN;j++) prime[i*j]=1;//当前质数的所有倍数都是合数
}
int query(int l,int r)
{
    auto itr=split(r+1),itl=split(l);//类似assign操作
    int res=0;//记录[l,r]的区间质数个数
    for (auto it=itl;it!=itr;it++)//遍历之间的所有区间
        if (!prime[it->v]) res+=it->r - it->l +1;//如果这个区间的值v是质数，那么将会对答案产生r-l+1的贡献
    return res;
}
int main()
{
    read(T);
    prework();//筛质数
    for (int t=1;t<=T;t++)
    {
    	printf("Case %d:\n",t);//一定记得要输出这里
        ctlt.clear();//多组数据记得清空珂朵莉树
        read(n),read(q);
        for (int i=1;i<=n;i++)
        {
            int val;read(val);
            ctlt.insert(Node(i,i,val));//每个数看作区间[i,i]的值为val
        }
        for (int i=1;i<=q;i++)
        {
            int op,x,y,v;
            read(op),read(x),read(y);
            if (op==0)
                read(v),assign(x,y,v);//操作0，即推平操作
            else
                printf("%d\n",query(x,y));//操作1，即查询操作
        }
    }
    return 0;
}
```

需要注意珂朵莉树只能在**数据随机**的情况下使用，否则一旦 `assign` 操作过少就会导致区间个数过多，时间就会直接 T 飞。

---

## 作者：wangyibo201026 (赞：1)

## 思路

有区间推平操作，显然可以考虑 ODT。

ODT 维护的是这一段里面的值，查询的时候再判断一下是不是质数就行了，质数的话，用个埃氏筛就行了，或者直接 $\sqrt{x}$ 也能过。

ODT 的博客的话，我推荐[这篇](https://www.luogu.com.cn/blog/_post/152920)。

## 代码

代码：

```cpp
#include<bits/stdc++.h>
#define init auto itr = split(r + 1), itl = split(l);
#define int long long

using namespace std;

const int mod = 1e9 + 7;
const int N = 1e6 + 5;

int t, n, m;
int a[N];

bool vis[10000005];

struct Node{
	int l, r;
	mutable int val;
	
	Node(int L, int R = -1, int v = 0){
		l = L;
		r = R;
		val = v;
	}
	
	bool operator<(const Node &x) const{
		return l < x.l;
	}
};

set<Node> odt;

void E_prime(int x){   //埃氏筛
	vis[1] = vis[0] = true;   //写不写都没问题
	for(int i = 2; i <= sqrt(x); i++){
		if(!vis[i]){
			for(int j = i * i; j <= x; j += i){
				vis[j] = true;
			}
		}
	}
}

auto split(int pos){   //ODT 操作
	auto it = odt.lower_bound(Node(pos));
	if(it != odt.end() && it -> l == pos){
		return it;
	}
	it--;
	int l = it -> l, r = it -> r, val = it -> val;
	odt.erase(it);
	odt.insert(Node(l, pos - 1, val));
	return odt.insert(Node(pos, r, val)).first;
}

void assign(int l, int r, int val){
	init
	odt.erase(itl, itr);
	odt.insert(Node(l, r, val));
}

int query(int l, int r){
	init
	int ans = 0;
	for(auto i = itl; i != itr; i++){
		if(!vis[(i -> val)]){   //如果为质数
			ans += (i -> r) - (i -> l) + 1;
		}
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	cin >> t;
	E_prime(10000000);  //这里筛 1e6 就行了
	for(int T = 1; T <= t; T++){
		odt.clear();
		cin >> n >> m;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			odt.insert(Node(i, i, a[i]));
		}
		cout << "Case " << T << ":\n";   //这里建议复制
		while(m--){
			int op, x, y, v;
			cin >> op >> x >> y;
			if(op == 0){
				cin >> v;
				assign(x, y, v);
			}
			else{
				cout << query(x, y) << '\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：Setsugesuka (赞：1)

阅读题意，发现题目要求我们维护两种操作，区间推平与统计区间素数个数，数据范围很小，用裸的 $ODT$ 就可以解决了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;

struct node
{
    int l,r,v;
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    bool operator <(const node &o) const
    {
        return l<o.l;
    }
};

int prime[MAXN],p[MAXN],tot=0;
set<node> s;

inline void init()
{
    prime[1]=prime[0]=1;
    for(int i=2;i<=MAXN-10;i++)
    {
        if(prime[i]==0)
            p[++tot]=i;
        for(int j=1;j<=tot&&i*p[j]<=MAXN-10;j++)
        {
            prime[i*p[j]]=1;
            if(i%p[j]==0)
                break;
        }
    }
}

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos) return it;
    --it;
    int L=it->l,R=it->r,V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,int v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

inline int query(int l,int r)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    int ret=0;
    for(itl;itl!=itr;++itl)
    {
        if(!prime[itl->v])
            ret+=(itl->r-itl->l+1);
    }
    return ret;
}

int n,m,t;

int main()
{
    init();
    scanf("%d",&t);
    for(int cc=1;cc<=t;cc++)
    {
        printf("Case %d:\n",cc);
        scanf("%d %d",&n,&m);
        s.clear();
        for(int i=1;i<=n;i++)
        {
            int sr;
            scanf("%d",&sr);
            s.insert(node(i,i,sr));
        }
        while(m--)
        {
            int op;
            scanf("%d",&op);
            if(op==0)
            {
                int l,r,v;
                scanf("%d %d %d",&l,&r,&v);
                assignval(l,r,v);
            }
            else
            {
                int l,r;
                scanf("%d %d",&l,&r);
                printf("%d\n",query(l,r));
            }
        }
    }
    return 0;
}
```


---

## 作者：喵仔牛奶 (赞：1)

可以分块写，每个块维护当前块的值和素数个数。

区间推平的话打一下值的标记，素数标记判一下推平的是否是素数即可。散块如果有标记就暴力下传标记，然后暴力修改即可。

求和的话整块取标记，散块暴力。

时间复杂度和空间复杂度都是 $O(\sqrt n)$。



---

