# Nastya Hasn't Written a Legend

## 题目描述

在本题中，Nastya 要求我们写出一个正式的题目描述。

给定一个长度为 $n$ 的数组 $a$ 和一个长度为 $n-1$ 的数组 $k$。需要处理两种类型的操作：

- 将 $a_i$ 增加 $x$。然后，如果 $a_{i+1} < a_i + k_i$，则将 $a_{i+1}$ 变为恰好 $a_i + k_i$；接着，如果 $a_{i+2} < a_{i+1} + k_{i+1}$，则将 $a_{i+2}$ 变为恰好 $a_{i+1} + k_{i+1}$，依此类推，直到 $a_{i+3}$，……，$a_n$；
- 输出数组 $a$ 的第 $l$ 个元素到第 $r$ 个元素组成的连续子数组的和。

保证初始时对于所有 $1 \leq i \leq n-1$，都有 $a_i + k_i \leq a_{i+1}$。

## 说明/提示

在第一个样例中：

- 第一次修改后，$a = [3, 4, 3]$；
- 第二次修改后，$a = [3, 4, 4]$。

在第二个样例中：

- 第一次修改后，$a = [6, 9, 10]$；
- 第二次修改后，$a = [6, 13, 14]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3
1 -1
5
s 2 3
+ 1 2
s 1 2
+ 3 1
s 2 3
```

### 输出

```
5
7
8
```

## 样例 #2

### 输入

```
3
3 6 7
3 1
3
+ 1 3
+ 2 4
s 1 3
```

### 输出

```
33
```

# 题解

## 作者：Parabola (赞：12)

### Part0.题外话

放老婆图片（题解能这么干？）

![](https://i.loli.net/2019/03/21/5c93897b2efe8.jpg)

------------


### Part1.思路

很妙很妙

首先题目有一个修改单点，是单点增加。

$a_i += s$

然后后面的所有值为了保持性质$a_i>=a_{i-1}+k_{i-1}$，如果不满足就把他变成$a_{i -1} + k_{i-1}$。

然后我们来推推式子

令$g_i = \sum^{i}_{j = 1}{k_i}$

则有$a_i >= a_{i-1}+k_{i-1}>=a_{i-2}+k_{i-2}+k_{i-1}>=...>=a_1+g_{i-1}$

令$u_i = a_i - g_{i-1}$

∵ $a_i >= a_{i-1}+k_{i-1}$

∴ $u_i + g_{i-1}>= u_{i-1} + g_{i -2} + k_{i -1}$

∴ $u_i + g_{i-1} >= u_{i-1} + g_{i - 1}$

∴ $u_i >= u_{i-1}$

到这你惊奇的发现$u$竟然是递增的！

然后对于每一个询问操作，我们拿线段树维护$u$的和

回答的时候就是$\sum_{i=l}^{r}u_i - \sum^{r-1}_{i = l-1}g_i$

所以还要预处理一下$g_i$前缀和。

而对于修改操作$(i,x)$，我们应当把$u_i += x$。

依题，维护$u$的有序性，所以我们二分到最后一个小于$u_i$（或小于等于，在这一题没有区别，想想为啥）的位置$j$，然后把$[i,j]$的$u$全部都设置为$u_i$

还有很多小细节，各位可以看看$Code$

------------

### Part2.Code

```cpp
#include<iostream>
#include<cstdio>
#define lc (o << 1)
#define rc (lc | 1)
#define mid ((l + r) >> 1)
using namespace std;

typedef long long ll;

const int MAXN = 100000 + 5;
const ll inf = 9e18;

int n , m , A[MAXN];
ll g[MAXN] , preg[MAXN] , seg[MAXN << 2] , setv[MAXN << 2];

inline void up(int o) {seg[o] = seg[lc] + seg[rc];}
void build(int o , int l , int r) {
	setv[o] = -inf;
	if(l == r) {
		seg[o] = A[l] - g[l - 1];
		return ;
	}
	build(lc , l , mid); build(rc , mid + 1 , r);
	up(o);
}
inline void set(int o , int l , int r , ll x) {
	setv[o] = x;
	seg[o] = (r - l + 1) * x;
}
inline void down(int o , int l , int r) {
	if(setv[o] != -inf) {
		set(lc , l , mid , setv[o]);
		set(rc , mid + 1 , r , setv[o]);
		setv[o] = -inf;
	}	
}
ll query(int o , int l , int r , int ql , int qr) {
	if(r < ql || l > qr) return 0;
	if(ql <= l && r <= qr) return seg[o];
	down(o , l , r);
	return query(lc , l , mid , ql , qr) + query(rc , mid + 1 , r , ql , qr);
}
void modify(int o , int l , int r , int ml , int mr , ll x) {
	if(r < ml || l > mr) return ;
	if(ml <= l && r <= mr) return set(o , l , r , x);
	down(o , l , r);
	modify(lc , l , mid , ml , mr , x); modify(rc , mid + 1 , r , ml , mr , x);
	up(o);
}

inline ll Get(int x) {return x < 0 ? 0 : preg[x];}

int main() {
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; ++i) scanf("%d" , A + i);
	for(int i = 1 , x ; i < n ; ++i) scanf("%d" , &x) , preg[i] = preg[i - 1] + (g[i] = g[i - 1] + x);
	build(1 , 1 , n);
	scanf("%d" , &m);
	for(int i = 1 , l , x; i <= m ; ++i) {
		char type; scanf(" %c %d %d" , &type , &l , &x);
		if(type == '+') {
			int r = n , zj = l;
			ll v = query(1 , 1 , n , l , l);
			v += x;
			while(l <= r) {
				ll k = query(1 , 1 , n , mid , mid);
				if(k == v) break;
				else if(k > v) r = mid - 1;
				else l = mid + 1;
			}
			modify(1 , 1 , n , zj , mid , v);
		}
		else printf("%lld\n" , query(1 , 1 , n , l , x) + Get(x - 1) - Get(l - 2));
	}
	return 0;
}
```


---

## 作者：DPair (赞：5)

提供一种另类的做法，和我看到的所有现有题解+代码都不一样，而且是单 $\log$ 的，目前洛谷最优解 $rank2$ 。

~~当然可能早就有人用这种方法实现了不过我没发现。~~

## 【思路】

首先我们意识到这道题其实就是一个单点修改区间查询，但是与此同时要我们维护整个序列满足一个 $\forall i \in [1, n-1], a_i+k_i\le a_{i+1}$ 的性质。

我们试图找一找这道题的一些性质。

不难发现，整个序列可以被划分成若干个连续段，其中每一个连续段除了开头，后面每一个数都满足 $a_i=a_{i-1}+k_{i-1}$ 。

而且我们惊讶地发现，每一个连续段在一次修改中，若是 **整体被修改** ，那么整一个连续段的增量是相同的。

区间增量区间求和，这启示我们开一棵线段树维护。

而且一个连续段只要知道开头的权值，整个连续段中每一个位置的权值其实都是确定的，所以我们修改某一个连续段中间的一位时可以方便地分裂，这里可以维护一个 $k$ 数组的前缀和，然后就可以 $O(1)$ 根据开头求出中间任意一位的权值了。

然后我们发现，我们每一次从一个连续段开始往后遍历，如果下一个连续段需要被修改即开头不满足条件，那么下一个连续段就一定可以被并到当前的连续段中，因为我们的修改就是赋值为 $a_i+k_i$ ，那么每一次线段树上的修改都意味着有一个连续段被合并，而且每一次修改都最多只会分裂出一个新连续段，所以最终连续段数量和修改次数都是 $O(n+m)$ 的。

我们考虑使用珂朵莉树维护这个东西，那么就可以方便地合并与分裂，并且也可以对连续段进行快速查找和修改，这里每一次的修改都是 $O(\log n)$ 的。

然后线段树修改和查询也是 $O(\log n)$ 的。

所以最终复杂度 $O((n+m)\log n)$ ，显然可以通过本题。

## 【代码】
删去了不重要的快读和头文件部分。
```cpp
/*
    author: DPair
    language: C++
*/
int n, q;
#define MAXN 100005
typedef long long LL;
LL a[MAXN], b[MAXN];
namespace SegTree{
    LL t[MAXN << 2], tag[MAXN << 2];
    inline void pushup(int rt){t[rt] = t[rt << 1] + t[rt << 1 | 1];}
    inline void update(int rt, int l, int r, LL z){
        t[rt] += z * (r - l + 1);
        tag[rt] += z;
    }
    #define RT rt, l, r
    #define LSON rt << 1, l, mid
    #define RSON rt << 1 | 1, mid + 1, r
    inline void pushdown(int rt, int l, int r){
        if(tag[rt]){
            int mid = (l + r) >> 1;
            update(LSON, tag[rt]);update(RSON, tag[rt]);
            tag[rt] = 0;
        }
    }
    void modify(int rt, int l, int r, int x, int y, LL z){
        if(x <= l && r <= y) return update(RT, z);
        pushdown(RT);
        int mid = (l + r) >> 1;
        if(x <= mid) modify(LSON, x, y, z);
        if(y > mid) modify(RSON, x, y, z);
        pushup(rt);
    }
    void build(int rt, int l, int r){
        if(l == r) {t[rt] = a[l];return ;}
        int mid = (l + r) >> 1;
        build(LSON);build(RSON);
        pushup(rt);
    }
    LL query(int rt, int l, int r, int x, int y){
        if(x <= l && r <= y) return t[rt];
        pushdown(RT);
        int mid = (l + r) >> 1;LL ret = 0;
        if(x <= mid) ret = query(LSON, x, y);
        if(y > mid) ret += query(RSON, x, y);
        return ret;
    }
}
namespace ODT{
    struct NODE{
        int l, r;LL x;
        NODE(int l, int r, LL x) : l(l), r(r), x(x) {}
        inline bool operator < (const NODE &tmp)const {return l < tmp.l;}
    };
    typedef set <NODE> :: iterator IT;
    set <NODE> t;
    inline IT split(int x){
        IT it = t.lower_bound(NODE(x, 0, 0));
        if(it != t.end() && it -> l == x) return it;
        -- it;int val = it -> x, l = it -> l, r = it -> r;
        t.erase(it);t.emplace(NODE(l, x - 1, val));
        return t.emplace(NODE(x, r, val + b[x] - b[l])).first;
    }
    inline void work(int p, LL x){
        IT L = split(p);LL val = L -> x;int r = L -> r;
        IT it;
        for (it = L;it != t.end();++ it){
            int l = it -> l;LL v = it -> x;
            if(val + x + b[l] - b[p] <= v) break;
            r = it -> r;
            SegTree :: modify(1, 1, n, l, r, val + x + b[l] - b[p] - v);
        }
        t.erase(L, it);
        t.emplace(NODE(p, r, val + x));
    }
}
int main(){
    read(n);
    for (int i = 1;i <= n;++ i) read(a[i]);
    for (int i = 2;i <= n;++ i) read(b[i]), b[i] += b[i - 1];
    SegTree :: build(1, 1, n);
    for (int i = 1;i <= n;++ i) ODT :: t.emplace(ODT :: NODE(i, i, a[i]));
    read(q);
    while(q --){
        char opt = nxt_char();
        int l, r;read(l, r);
        if(opt == '+') ODT :: work(l, r);
        else print(SegTree :: query(1, 1, n, l, r));
    }
}
```

---

## 作者：Cesare (赞：5)

打 $CF$ 团队赛做到了这道题，口胡出了一个暴力重构每个块的分块做法，写了一半发现修改不可做，开始推式子。

已知

$$a_i + k_i <= a_{i + 1}$$

有

$$a_{i + 1} - k_i >= a_i$$

$$a_{i + 1} - k_i - k_{i - 1} >= a_i - k_{i - 1}$$

$$\ldots$$

$$a_{i + 1} - k_i - \ldots - k_1 >= a_i - k_{i - 1} - \ldots - k_1$$

记 

$$sum_i = \sum_{j = 1}^{i} k_i$$

有

$$a_{i + 1} - sum_i >= a_i - sum_{i - 1}$$

记 

$$d_i = a_i - sum_{i - 1}$$

有

$$d_i >= d_{i - 1}$$

线段树维护 $d_i$ 即可。

修改时，单点修改即可。

查询时，从右往左在线段树上找第一个满足条件的节点即可。

关于线段树找节点的操作，推荐 $51nod$ 一道类似的[题目](http://www.51nod.com/Challenge/Problem.html#!#problemId=1701)

就做完了。

---

## 作者：WaterSun (赞：2)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18468592)

# 思路

首先考虑操作 1 一个点 $i$ 能被操作到的条件。注意到此时 $x \sim i - 1$ 这些位置都是被更新过的，再仔细观察此时 $\forall j \in [x,i),a_j = a_x + \sum_{p = x}^{j - 1}k_p$。

那么对于 $a_i$ 如果会被修改将会变为 $a_x + \sum_{p = x}^{i - 1}k_p$，那么 $a_i$ 被修改，当且仅当，其中 $s$ 为 $k$ 的前缀和：

$$
a_i < a_x + \sum_{p = x}^{i - 1}k_p\\
\Rightarrow a_i < a_x + s_{i - 1} - s_{x - 1}\\
\Rightarrow a_i - s_{i - 1} < a_x - s_{x - 1}
$$

不妨维护 $a_i - s_{i - 1}$ 的值，这样我们可以二分找到最大的 $i$。此时的修改操作变为了区间推平为 $a_x - s_{x - 1}$，直接丢到线段树上即可。

最后考虑操作 2 就简单了，在线段树上查询 $[l,r]$ 维护的 $a_i - s_{i - 1}$ 的和，加上 $s_{l - 1 \sim r - 1}$ 即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define int long long

using namespace std;

const int N = 1e5 + 10;
const int inf = (int)(1e18) + 10;
int n,q;
int arr[N],k[N],s[N],ss[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int Max,sum,tag;
    }tr[N << 2];

    inline void calc(int u,int k){
        tr[u].Max = tr[u].tag = k;
        tr[u].sum = (tr[u].r - tr[u].l + 1) * k;
    }

    inline void pushup(int u){
        tr[u].sum = tr[ls(u)].sum + tr[rs(u)].sum;
        tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
    }

    inline void pushdown(int u){
        if (tr[u].tag != inf){
            calc(ls(u),tr[u].tag); calc(rs(u),tr[u].tag);
            tr[u].tag = inf;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r,inf,0,inf};
        if (l == r) return (tr[u].Max = tr[u].sum = arr[l] - s[l - 1]),void();
        int mid = l + r >> 1;
        build(ls(u),l,mid); build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int x,int k){
        if (tr[u].l == tr[u].r){
            tr[u].Max += k; tr[u].sum += k;
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(ls(u),x,k);
        else modify(rs(u),x,k);
        pushup(u);
    }

    inline void update(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r) return calc(u,k),void();
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) update(ls(u),l,r,k);
        if (r > mid) update(rs(u),l,r,k);
        pushup(u);
    }

    inline int querymax(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].Max;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid && r > mid) return max(querymax(ls(u),l,r),querymax(rs(u),l,r));
        else if (l <= mid) return querymax(ls(u),l,r);
        else return querymax(rs(u),l,r);
    }

    inline int querysum(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid && r > mid) return querysum(ls(u),l,r) + querysum(rs(u),l,r);
        else if (l <= mid) return querysum(ls(u),l,r);
        else return querysum(rs(u),l,r);
    }

    #undef ls
    #undef rs
}T;

signed main(){
    n = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1;i < n;i++) s[i] = s[i - 1] + (k[i] = read());
    for (re int i = 1;i < n;i++) ss[i] = ss[i - 1] + s[i];
    T.build(1,1,n);
    q = read();
    while (q--){
        char op[10]; scanf("%s",op);
        if (op[0] == '+'){
            int x,k;
            x = read(),k = read();
            T.modify(1,x,k);
            int val = T.querysum(1,x,x);
            int l = x + 1,r = n;
            while (l < r){
                int mid = l + r + 1 >> 1;
                if (T.querymax(1,x + 1,mid) < val) l = mid;
                else r = mid - 1;
            }
            if (x < n && T.querymax(1,x + 1,l) < val) T.update(1,x + 1,l,val);
        }
        else{
            int l,r;
            l = read(),r = read();
            int sum = T.querysum(1,l,r) + ss[r - 1];
            if (l - 2 >= 0) sum -= ss[l - 2];
            printf("%lld\n",sum);
        }
    }
    return 0;
}
```

---

## 作者：louhao088 (赞：2)

一道线段树好题。


------------


首先因为 $ a_i+k_i \leq a_{i+1} $​​​​ 所以简单移项发现 $a_i \leq a_{i+1}-k_i$​​​​ 。不难推出 ：$a_i - \sum_{j=1}^{i-1} k_j \leq a_{i+1}-\sum_{j=1}^{i} k_j (i>1)$​​​​。因此我们可以对每个 $a_i$​​​​ 减去 $\sum_{j=1}^{i} k_j$​​​​​。

这样改的话，我们发现一号操作就从区间修改数列变为区间赋值，因为我们已经把相差的 $k_i$ 提前减掉了。判断修改的右端点只要用二分很容易解决。


------------

操作 s 只要在线段树区间查值的基础上再加上 $\sum_{i=l}^{r}\sum_{j=1}^{i-1} k_j$​ 的值，这个值可以用提前处理好的二维​前缀和，注意要特判 $l=1$ 的情况。


------------

维护 tag 的时候不能将其初始值设为 0，因为会有修改回 0 的操作，应设为负数。



------------
代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls (rt<<1ll)
#define rs (rt<<1ll|1ll)
#define mid (l+r>>1ll)
#define int long long
inline int read()
{
	char ch=getchar();int x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
void print(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
const int maxn=2e5+5,inf=-1e18;
int tag[maxn*4],a[maxn],l,r,x,y,sum[maxn*4],n,m,opt,ss[maxn],k[maxn];
char s[5];
void build(int rt,int l,int r)
{
	tag[rt]=inf;
	if(l==r){sum[rt]=a[l];return;}
	build(ls,l,mid),build(rs,mid+1,r);
	sum[rt]=sum[ls]+sum[rs];
}
void push(int rt,int l,int r)
{
	if(tag[rt]!=inf)
	{
		tag[ls]=tag[rt];tag[rs]=tag[rt];
		sum[ls]=tag[rt]*(mid-l+1);sum[rs]=tag[rt]*(r-mid);tag[rt]=inf;
	}
}
void add(int rt,int l,int r,int L,int R,int num)
{
	
	if(l>R||r<L)return;//cout<<sum[rt]<<endl;
	if(l>=L&&r<=R)
	{
		sum[rt]=num*(r-l+1);tag[rt]=num;return;
	}
	push(rt,l,r);add(ls,l,mid,L,R,num),add(rs,mid+1,r,L,R,num);
	sum[rt]=sum[ls]+sum[rs];
}
int query(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)return 0;
	if(l>=L&&r<=R)return sum[rt];
	push(rt,l,r);return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)k[i]=read(),k[i]+=k[i-1],a[i+1]=a[i+1]-k[i],ss[i]=ss[i-1]+k[i];//,cout<<k[i]<<" "<<ss[i]<<endl;
	//for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	build(1,1,n);m=read();
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);
		if(s[0]=='+')
		{
			x=read(),y=read();l=x,r=n;int u=query(1,1,n,x,x)+y;
			while(l<=r)
			{
				int res=query(1,1,n,mid,mid);
				if(res==u)break;
				else if(res>u)r=mid-1;//cout<<"A";
				else l=mid+1;
			}//cout<<res<<endl;
			add(1,1,n,x,mid,u);
		}
		else l=read(),r=read(),print(query(1,1,n,l,r)+ss[r-1]-ss[max(0ll,l-2)]),puts("");
	}
	return 0;
}
```


---

## 作者：Fracture_Dream (赞：0)

# 简述题意
给定长为 $n$ 的数组 $a$，长为 $n-1$ 的数组 $k$。试支持以下 $2$ 种操作：

1. `+ i x`，表示 $a_i \gets a_i + x$，然后重复以下过程：若 $a_{i+1} < a_i + k_i$，则 $a_{i + 1} \gets a_i + k_i,i \gets i + 1$，否则结束本次操作。

2. `s l r`，输出 $\sum\limits_{i = l}^r a_i$。

-  $1 \le n,q \le 10^5$
- $1 \le i \le n,1 \le l \le r \le n$
- $|k| \le 10^6,|a_i| \le 10^9, 0 \le x \le 10^6$
# 思路
考虑修改操作，由于一旦遇到某个 $i$ 不满足 $a_{i+1} < a_i+k_i$，操作就会立即中断。显然，如果我们修改 $a_i \leftarrow a_i+x$，只会影响到 $[i,x](x \in [i , n])$ 这样一个连续的区间。

考虑怎么求出 $x$，以下不妨令 $prek$ 为 $k$ 数组的前缀和。
假设操作进行到 $x$ 中断，那么我们需要保证：

$$\forall j \in [i+1,x]，a_i + prek_{j-1} - prek_{i-1} > a_j$$

考虑将与 $i,j$ 相关的式子分别移至等号两边。

$$\forall j \in [i+1,x]，a_i  - prek_{i-1} > a_j - prek_{j-1}$$

考虑转化为最值。

$$a_i - prek_{i-1} >\max\{a_j - prek_{j-1}\}，j \in [i + 1 , x]$$

不妨假设我们已求出 $i$ 影响的区间 $[i,x]$。那么，对于每一个 $j \in [i,x]$，$a_j \leftarrow a_i + prek_{j-1} - prek_{i-1}$。然而，我们很难直接维护 $a_i$ 的值，因为有一个 $prek_{j-1}$ 很棘手。不妨观察上述式子，发现 $a_i - prek_{i-1}$ 这样的式子出现频率很高，所以试着维护 $a_i - prek_{i-1}$ 而非 $a_i$。

我们发现，一次修改后，某个连续区间 $[i,x]$ 中的元素都被推平成了 $a_i + prek_{j-1} - prek_{i-1}$，而对于每个 $j$，其 $a_j-prek_{j-1}=a_i+prek_{i-1}$，这对于每个修改来说是个定值！直接线段树区间推平即可。巧合的是，如果我们再维护区间 $max$，由于 $max$ 有单调性，结合二分也顺便求出了 $x$。

考虑查询操作，线段树维护区间和可以求出 $\sum\limits_{i = l}^r a_i-prek_{i-1}$，然后再预处理 $prek$ 数组的前缀 $Pre$，便可以求出 $\sum\limits_{i = l}^r prek_{i-1}$，相加即可。

总结一下，线段树维护 $a_i-prek_{i-1}$ 这个序列。
- 对于修改操作，不妨令线段树上点 $i$ 的值为 $val$，那么将区间 $[i , x]$ 推平为 $val+x$。
- 对于查询操作，每个元素减去的 $prek_{i-1}$ 要加回来，所以维护 $prek$ 的前缀和即可。
# 代码
注意线段树的 $lazy$ 标初始不能置为 $-1$！因为 $-1$ 在此题中有实际意义！
还有就是二分的边界！！！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int n , q , a[MAXN] , k[MAXN] , prek[MAXN] , Pre[MAXN];
namespace Segment{
	struct tree{
		int l , r , sum , Max , tag;
	}tree[MAXN << 3];
	void pushup(int p) {
		tree[p].sum = tree[p << 1].sum + tree[p << 1 | 1].sum;
		tree[p].Max = max(tree[p << 1].Max , tree[p << 1 | 1].Max);
	}
	void pushdown(int p) {
		if (tree[p].tag != -0x3f3f3f3f) {
			tree[p << 1].tag = tree[p << 1 | 1].tag = tree[p << 1].Max = tree[p << 1 | 1].Max = tree[p].tag;
			tree[p << 1].sum = (tree[p << 1].r - tree[p << 1].l + 1) * tree[p].tag;
			tree[p << 1 | 1].sum = (tree[p << 1 | 1].r - tree[p << 1 | 1].l + 1) * tree[p].tag;
			tree[p].tag = -0x3f3f3f3f;
		}
	}
	void build(int p , int l , int r) {
		tree[p].tag = -0x3f3f3f3f , tree[p].l = l , tree[p].r = r;
		if (l == r) {
			tree[p].Max = tree[p].sum = a[l] - prek[l - 1];
			return;
		}
		int mid = l + r >> 1;
		build(p << 1 , l , mid) , build(p << 1 | 1 , mid + 1 , r);
		pushup(p);
	}
	void update(int p , int l , int r , int v) {
		if (l > r) return;
		if (tree[p].l >= l && tree[p].r <= r) {
			tree[p].sum = (tree[p].r - tree[p].l + 1) * v;
			tree[p].tag = tree[p].Max = v;
			return;
		}
		pushdown(p);
		int mid = tree[p].l + tree[p].r >> 1;
		if (l <= mid) update(p << 1 , l , r , v);
		if (r > mid) update(p << 1 | 1 , l , r , v);
		pushup(p);
	}
	int QueryMax(int p , int l , int r) {
		if (tree[p].l >= l && tree[p].r <= r) return tree[p].Max;
		pushdown(p);
		int mid = tree[p].l + tree[p].r >> 1 , Max = -1e9;
		if (l <= mid) Max = max(Max , QueryMax(p << 1 , l , r));
		if (r > mid) Max = max(Max , QueryMax(p << 1 | 1 , l , r));
		return Max;
	}
	int QuerySum(int p , int l , int r) {
		if (tree[p].l >= l && tree[p].r <= r) return tree[p].sum;
		pushdown(p);
		int mid = tree[p].l + tree[p].r >> 1 , sum = 0;
		if (l <= mid) sum += QuerySum(p << 1 , l , r);
		if (r > mid) sum += QuerySum(p << 1 | 1 , l , r);
		return sum;
	}
}
using namespace Segment;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	cin >> n;
	for (int i = 1 ; i <= n ; i ++) cin >> a[i];
	for (int i = 1 ; i < n ; i ++) cin >> k[i] , prek[i] = prek[i - 1] + k[i];
	for (int i = 1 ; i <= n ; i ++) Pre[i] = Pre[i - 1] + prek[i];
	build(1 , 1 , n);
	cin >> q;
	while(q --) {
		char type;
		int x , y;
		cin >> type >> x >> y;
		if (type == '+') {
			a[x] += y;
			int val = QuerySum(1 , x , x) + y;
			int l = x + 1 , r = n;
			while(l < r) {
				int mid = l + r + 1 >> 1;
				if (QueryMax(1 , x + 1 , mid) < val) l = mid;
				else r = mid - 1;
			}
			if (x == n || QueryMax(1 , x + 1 , l) >= val) l = x;
			update(1 , x , l , val);
		} else {
			cout << QuerySum(1 , x , y) + Pre[y - 1] - Pre[(x - 2 < 1 ? 0 : x - 2)] << '\n';
		}
	}
	return 0;
}
```

---

## 作者：Fracture_Dream (赞：0)

# 简述题意
给定长为 $n$ 的数组 $a$，长为 $n-1$ 的数组 $k$。试支持以下 $2$ 种操作：

1. `+ i x`，表示 $a_i \gets a_i + x$，然后重复以下过程：若 $a_{i+1} < a_i + k_i$，则 $a_{i + 1} \gets a_i + k_i,i \gets i + 1$，否则结束本次操作。

2. `s l r`，输出 $\sum\limits_{i = l}^r a_i$。

-  $1 \le n,q \le 10^5$
- $1 \le i \le n,1 \le l \le r \le n$
- $|k| \le 10^6,|a_i| \le 10^9, 0 \le x \le 10^6$
# 思路
考虑修改操作，由于一旦遇到某个 $i$ 不满足 $a_{i+1} < a_i+k_i$，操作就会立即中断。显然，如果我们修改 $a_i \leftarrow a_i+x$，只会影响到 $[i,x](x \in [i , n])$ 这样一个连续的区间。

考虑怎么求出 $x$，以下不妨令 $prek$ 为 $k$ 数组的前缀和。
假设操作进行到 $x$ 中断，那么我们需要保证：

$$\forall j \in [i+1,x]，a_i + prek_{j-1} - prek_{i-1} > a_j$$

考虑将与 $i,j$ 相关的式子分别移至等号两边。

$$\forall j \in [i+1,x]，a_i  - prek_{i-1} > a_j - prek_{j-1}$$

考虑转化为最值。

$$a_i - prek_{i-1} >\max\{a_j - prek_{j-1}\}，j \in [i + 1 , x]$$

不妨假设我们已求出 $i$ 影响的区间 $[i,x]$。那么，对于每一个 $j \in [i,x]$，$a_j \leftarrow a_i + prek_{j-1} - prek_{i-1}$。然而，我们很难直接维护 $a_i$ 的值，因为有一个 $prek_{j-1}$ 很棘手。不妨观察上述式子，发现 $a_i - prek_{i-1}$ 这样的式子出现频率很高，所以试着维护 $a_i - prek_{i-1}$ 而非 $a_i$。

我们发现，一次修改后，某个连续区间 $[i,x]$ 中的元素都被推平成了 $a_i + prek_{j-1} - prek_{i-1}$，而对于每个 $j$，其 $a_j-prek_{j-1}=a_i+prek_{i-1}$，这对于每个修改来说是个定值！直接线段树区间推平即可。巧合的是，如果我们再维护区间 $max$，由于 $max$ 有单调性，结合二分也顺便求出了 $x$。

考虑查询操作，线段树维护区间和可以求出 $\sum\limits_{i = l}^r a_i-prek_{i-1}$，然后再预处理 $prek$ 数组的前缀 $Pre$，便可以求出 $\sum\limits_{i = l}^r prek_{i-1}$，相加即可。

总结一下，线段树维护 $a_i-prek_{i-1}$ 这个序列。
- 对于修改操作，不妨令线段树上点 $i$ 的值为 $val$，那么将区间 $[i , x]$ 推平为 $val+x$。
- 对于查询操作，每个元素减去的 $prek_{i-1}$ 要加回来，所以维护 $prek$ 的前缀和即可。
# 代码
注意线段树的 $lazy$ 标初始不能置为 $-1$！因为 $-1$ 在此题中有实际意义！
还有就是二分的边界！！！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int n , q , a[MAXN] , k[MAXN] , prek[MAXN] , Pre[MAXN];
namespace Segment{
	struct tree{
		int l , r , sum , Max , tag;
	}tree[MAXN << 3];
	void pushup(int p) {
		tree[p].sum = tree[p << 1].sum + tree[p << 1 | 1].sum;
		tree[p].Max = max(tree[p << 1].Max , tree[p << 1 | 1].Max);
	}
	void pushdown(int p) {
		if (tree[p].tag != -0x3f3f3f3f) {
			tree[p << 1].tag = tree[p << 1 | 1].tag = tree[p << 1].Max = tree[p << 1 | 1].Max = tree[p].tag;
			tree[p << 1].sum = (tree[p << 1].r - tree[p << 1].l + 1) * tree[p].tag;
			tree[p << 1 | 1].sum = (tree[p << 1 | 1].r - tree[p << 1 | 1].l + 1) * tree[p].tag;
			tree[p].tag = -0x3f3f3f3f;
		}
	}
	void build(int p , int l , int r) {
		tree[p].tag = -0x3f3f3f3f , tree[p].l = l , tree[p].r = r;
		if (l == r) {
			tree[p].Max = tree[p].sum = a[l] - prek[l - 1];
			return;
		}
		int mid = l + r >> 1;
		build(p << 1 , l , mid) , build(p << 1 | 1 , mid + 1 , r);
		pushup(p);
	}
	void update(int p , int l , int r , int v) {
		if (l > r) return;
		if (tree[p].l >= l && tree[p].r <= r) {
			tree[p].sum = (tree[p].r - tree[p].l + 1) * v;
			tree[p].tag = tree[p].Max = v;
			return;
		}
		pushdown(p);
		int mid = tree[p].l + tree[p].r >> 1;
		if (l <= mid) update(p << 1 , l , r , v);
		if (r > mid) update(p << 1 | 1 , l , r , v);
		pushup(p);
	}
	int QueryMax(int p , int l , int r) {
		if (tree[p].l >= l && tree[p].r <= r) return tree[p].Max;
		pushdown(p);
		int mid = tree[p].l + tree[p].r >> 1 , Max = -1e9;
		if (l <= mid) Max = max(Max , QueryMax(p << 1 , l , r));
		if (r > mid) Max = max(Max , QueryMax(p << 1 | 1 , l , r));
		return Max;
	}
	int QuerySum(int p , int l , int r) {
		if (tree[p].l >= l && tree[p].r <= r) return tree[p].sum;
		pushdown(p);
		int mid = tree[p].l + tree[p].r >> 1 , sum = 0;
		if (l <= mid) sum += QuerySum(p << 1 , l , r);
		if (r > mid) sum += QuerySum(p << 1 | 1 , l , r);
		return sum;
	}
}
using namespace Segment;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	cin >> n;
	for (int i = 1 ; i <= n ; i ++) cin >> a[i];
	for (int i = 1 ; i < n ; i ++) cin >> k[i] , prek[i] = prek[i - 1] + k[i];
	for (int i = 1 ; i <= n ; i ++) Pre[i] = Pre[i - 1] + prek[i];
	build(1 , 1 , n);
	cin >> q;
	while(q --) {
		char type;
		int x , y;
		cin >> type >> x >> y;
		if (type == '+') {
			a[x] += y;
			int val = QuerySum(1 , x , x) + y;
			int l = x + 1 , r = n;
			while(l < r) {
				int mid = l + r + 1 >> 1;
				if (QueryMax(1 , x + 1 , mid) < val) l = mid;
				else r = mid - 1;
			}
			if (x == n || QueryMax(1 , x + 1 , l) >= val) l = x;
			update(1 , x , l , val);
		} else {
			cout << QuerySum(1 , x , y) + Pre[y - 1] - Pre[(x - 2 < 1 ? 0 : x - 2)] << '\n';
		}
	}
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较有意思的线段树题，但是为什么只有 $2200$ 啊。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
最开始看了两眼没看出来，胡了个巨难做的做法，在此不再赘述。

这个题就很迷惑，虽然只有单点修改，但是还要让后面的数取 $\max$，看上去就很不好做。

既然都取 $\max$ 了，这题总得有单调性吧？

但是因为 $k_i$ 有负的，所以 $a_i$ 并没有单调性，就很难受。

所以考虑自己构造一个具有单调性的东西。

首先根据题目的取 $\max$ 的条件，我们可以得到一个东西：
$$a_i\ge a_{i-1}+k_{i-1}$$
根据上文，这个式子中卡住我们的就是 $k_{i-1}$。

考虑构造 $b_i=a_i-\sum\limits_{j=1}^{i-1}k_j$。

那么式子就可以化为：
$$b_i+\sum\limits_{j=1}^{i-1}k_j\ge b_{i-1}+\sum\limits_{j=1}^{i-2}k_j+k_{i-1}$$
把后面那个部分合并一下，就得到了：
$$b_i\ge b_{i-1}$$
美妙的单调性就出现了。

具体而言，先计算出 $k$ 数组的前缀和 $s$，再处理出 $s$ 数组的前缀和 $ss$ 以及 $b$ 数组。

用线段树维护 $b$ 数组，支持区间覆盖区间和。

因为每一次单点修改之后我们都要往他后面的一段连续的比他小的区间覆盖，因为 $b$ 数组具有单调性，所以我们可以二分出第一个大于修改那个位置的值的位置。

接着对这样一个左闭右开的区间进行修改就行了。

查询时注意加上 $b$ 数组与 $a$ 数组的差，用前缀和数组 $ss$ 快速查询。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f3f3f3f3f;
int n,m,a[N],k[N],t[N<<2],lz[N<<2],ss[N];char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='+'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void pushdown(int p,int l,int r){if(lz[p]!=INF) lz[ls]=lz[rs]=lz[p],t[ls]=(mid-l+1)*lz[p],t[rs]=(r-mid)*lz[p],lz[p]=INF;}
inline void build(int p,int l,int r)
{
    lz[p]=INF;if(l==r) return t[p]=a[l],void();
    build(ls,l,mid);build(rs,mid+1,r);t[p]=t[ls]+t[rs];
}
inline void modify(int p,int l,int r,int s,int e,int x)
{
    if(l>=s&&r<=e) return t[p]=(r-l+1)*x,lz[p]=x,void();pushdown(p,l,r);
    if(mid>=s) modify(ls,l,mid,s,e,x);if(mid<e) modify(rs,mid+1,r,s,e,x);t[p]=t[ls]+t[rs];
}
inline int query(int p,int l,int r,int s,int e)
{
    if(l>=s&&r<=e) return t[p];pushdown(p,l,r);int res=0;
    if(mid>=s) res=query(ls,l,mid,s,e);if(mid<e) res+=query(rs,mid+1,r,s,e);return res;
}
signed main()
{
    n=read();for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++) ss[i]=ss[i-1]+(k[i]=read()+k[i-1]);
    for(int i=1;i<=n;i++) a[i]-=k[i-1];build(1,1,n);m=read();
    for(int i=1,l,x,y;i<=m;i++)
    {
        rd(s,l=0);if(s[1]=='s'){x=read(),y=read(),print(query(1,1,n,x,y)-ss[max(0ll,x-2)]+ss[y-1]),put('\n');continue;}
        x=read(),y=read();int w=query(1,1,n,x,x)+y,r=n;l=x;
        while(l<=r)
        {
            int k=query(1,1,n,mid,mid);
            if(k==w) break;if(k>w) r=mid-1;else l=mid+1;
        }modify(1,1,n,x,mid,w);
    }
    genshin:;flush();return 0;
}
```

---

