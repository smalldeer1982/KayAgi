# Reverse and Swap

## 题目描述

You are given an array $ a $ of length $ 2^n $ . You should process $ q $ queries on it. Each query has one of the following $ 4 $ types:

1. $ Replace(x, k) $ — change $ a_x $ to $ k $ ;
2. $ Reverse(k) $ — reverse each subarray $ [(i-1) \cdot         2^k+1, i \cdot 2^k] $ for all $ i $ ( $ i \ge 1 $ );
3. $ Swap(k) $ — swap subarrays $ [(2i-2) \cdot 2^k+1, (2i-1)         \cdot 2^k] $ and $ [(2i-1) \cdot 2^k+1, 2i \cdot 2^k] $ for all $ i $ ( $ i \ge 1 $ );
4. $ Sum(l, r) $ — print the sum of the elements of subarray $ [l, r] $ .

Write a program that can quickly process given queries.

## 说明/提示

In the first sample, initially, the array $ a $ is equal to $ \{7,4,9,9\} $ .

After processing the first query. the array $ a $ becomes $ \{7,8,9,9\} $ .

After processing the second query, the array $ a_i $ becomes $ \{9,9,7,8\} $

Therefore, the answer to the third query is $ 9+7+8=24 $ .

In the second sample, initially, the array $ a $ is equal to $ \{7,0,8,8,7,1,5,2\} $ . What happens next is:

1. $ Sum(3, 7) $ $ \to $ $ 8 + 8 + 7 + 1 + 5 = 29 $ ;
2. $ Reverse(1) $ $ \to $ $ \{0,7,8,8,1,7,2,5\} $ ;
3. $ Swap(2) $ $ \to $ $ \{1,7,2,5,0,7,8,8\} $ ;
4. $ Sum(1, 6) $ $ \to $ $ 1 + 7 + 2 + 5 + 0 + 7 = 22 $ ;
5. $ Reverse(3) $ $ \to $ $ \{8,8,7,0,5,2,7,1\} $ ;
6. $ Replace(5, 16) $ $ \to $ $ \{8,8,7,0,16,2,7,1\} $ ;
7. $ Sum(8, 8) $ $ \to $ $ 1 $ ;
8. $ Swap(0) $ $ \to $ $ \{8,8,0,7,2,16,1,7\} $ .

## 样例 #1

### 输入

```
2 3
7 4 9 9
1 2 8
3 1
4 2 4```

### 输出

```
24```

## 样例 #2

### 输入

```
3 8
7 0 8 8 7 1 5 2
4 3 7
2 1
3 2
4 1 6
2 3
1 5 16
4 8 8
3 0```

### 输出

```
29
22
1```

# 题解

## 作者：syksykCCC (赞：16)

个人认为挺巧妙的一道题，结果在神仙眼里就是：

![image.png](https://i.loli.net/2020/08/23/awjUhYGvAzJsDi1.png)

~~（语言经过删节）~~

------

操作写的不是人话，翻译一下四个操作：

1. $\operatorname{\large{R}\small{PLACE}}\normalsize{(x, k)}$，单点修改 $a_x \gets k$；
2. $\operatorname{\large{R}\small{EVERSE}}\normalsize{(k)}$，从左到右划分为若干个长度为 $2^k$ 的区间，将每个区间翻转；
3. $\operatorname{\large{S}\small{WAP}}\normalsize{(k)}$，从左到右划分为若干个长度为 $2^k$ 的区间，相邻两个区间交换位置；
4. $\operatorname{\large{S}\small{UM}}\normalsize{(l, r)}$，求 $\sum\limits_{i=l}^r a_i$。

~~我会做 1 和 4 ！~~

考虑巧妙利用线段树，因为保证序列的长度为 $2^n$，所以，线段树的形状为：共 $n+1$ 层，令叶子结点为第 $0$ 层，根节点为第 $n$ 层，则第 $k$ 层的每个结点，维护的都是长度为 $2^k$ 的区间。

观察操作 2 和 3，我们发现，线段树第 $k$ 层的所有结点，恰好就是我们所想要修改的区间！

定义一个标记 $\text{rev}_{dep}$，如果为 $1$ 表示第 $dep$ 层的左右结点的左右儿子分别互换，为 $0$ 则不变。

先来看操作 3，如果我们将 $\text{rev}_{k+1}$ 改变，是不是，恰好相邻两个长度为 $2^k$ 的区间都互换了呢？

下图展示 $n = 3$，$\operatorname{\large{S}\small{WAP}}\normalsize{(1)}$：

![image.png](https://i.loli.net/2020/08/23/KlV9ivdQgxZs2tk.png)

再看操作 4，不难发现，它等价于改变所有的 $\text{rev}_0 \sim \text{rev}_k$。这很好理解，$\text{rev}_{k}$ 改变后，相当于是每个长度为 $2^k$ 的区间内部，前 $2^{k-1}$ 和后 $2^{k-1}$ 个调换了位置，但这两部分**内部分别有序**，所以要继续调换下去。

在加入了 $\text{rev}$ 数组后，线段树也不难实现，如果当前处在 $\text{rev}_{dep}=1$ 的一层，就把右儿子当作左儿子，左儿子当作右儿子好了。

时间复杂度 $\mathcal O(qn)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 20, S = 1 << N;
int n, q;
bool rev[N];
struct segment_tree
{
	int o[S << 2];
	void build(int l, int r, int rt)
	{
		if(l == r) { scanf("%lld", &o[rt]); return; }
		int mid = l + r >> 1;
		build(l, mid, rt << 1); build(mid + 1, r, rt << 1 | 1);
		o[rt] = o[rt << 1] + o[rt << 1 | 1];
	}
	void modify(int l, int r, int rt, int dep, int p, int v)
	{
		if(l == r) { o[rt] = v; return; }
		int mid = l + r >> 1;
		if(p <= mid) modify(l, mid, rt << 1 | rev[dep], dep - 1, p, v);
		else modify(mid + 1, r, rt << 1 | rev[dep] ^ 1, dep - 1, p, v);
		o[rt] = o[rt << 1] + o[rt << 1 | 1];
	}
	int query(int l, int r, int rt, int dep, int ql, int qr)
	{
		if(ql <= l && r <= qr) return o[rt];
		int mid = l + r >> 1, res = 0;
		if(ql <= mid) res += query(l, mid, rt << 1 | rev[dep], dep - 1, ql, qr);
		if(qr > mid) res += query(mid + 1, r, rt << 1 | rev[dep] ^ 1, dep - 1, ql, qr);
		return res;
	}
} sgt;
#define Replace(x, k) sgt.modify(1, 1 << n, 1, n, x, k)
#define Sum(l, r) sgt.query(1, 1 << n, 1, n, l, r)
#define Swap(k) rev[k + 1] ^= 1
inline void Reverse(int k) { for(int i = 0; i <= k; i++) rev[i] ^= 1; }
signed main()
{
	scanf("%lld %lld", &n, &q);
	sgt.build(1, 1 << n, 1);
	while(q--)
	{
		int opt, x, y;
		scanf("%lld", &opt);
		switch(opt)
		{
			case 1:
				scanf("%lld %lld", &x, &y); Replace(x, y); break;
			case 2:
				scanf("%lld", &x); Reverse(x); break;
			case 3:
				scanf("%lld", &x); Swap(x); break;
			case 4:
				scanf("%lld %lld", &x, &y); printf("%lld\n", Sum(x, y)); break;
		}
	}
	return 0;
}
```

---

## 作者：漠寒 (赞：4)

## 分析

首先，数组大小为 $2^n$，所以可以确保2和3操作都能覆盖到整个数组，而且我们可以将整个数组分为 $n+1$ 层。

在分层之后，我们该怎么处理2操作和3操作呢？首先理解3操作，将题面简化就是将每个大小为 $2^{k+1}$ 里面的左右两块整体交换，在此基础上，我们就可以进一步理解2操作，相当于 $i 从 $k$ 一直到1，将大小为 $2^i$ 内的左右两部分整体交换，可以自己画个草图理解一下。

对于大小为 $2^i$ 的左右调换如何简化呢，上面已经说了，2和3操作能覆盖整个数组，因此对于这样的一个调换，我们可以对第 $i$ 层打上标记，那我们在修改和查值时，如果询问到这一层，对于线段树就可以理解为它的左儿子和右儿子进行了调换，如果有标记就去本不会去的那一个儿子就可以了。

具体操作可以看代码，目前最优解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls (rt<<1)
#define rs ((rt<<1)^1)

int n,q,rot[20],a[600000],p;

inline void read(int &res){
	res=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
}

void build(int l,int r,int rt){//左端点，右端点，编号 
	if(l==r){
		read(a[rt]);//此处读入易证其正确性，就不证明了 
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls),build(mid+1,r,rs);
	a[rt]=a[ls]+a[rs];//取和 
}

inline void modify(int mb,int L,int R,int rt,int fz,int ccs){//目标位置，左端点，右端点，区间编号，欲修改值，层数 
	if(L==R){//找到目标位置，进行修改 
		a[rt]=fz;
		return;
	}
	int mid=(L+R)>>1;
	if(mid>=mb)modify(mb,L,mid,ls^rot[ccs],fz,ccs-1);//异或即可改变是否去另一个子区间 
	if(mid<mb)modify(mb,mid+1,R,rs^rot[ccs],fz,ccs-1);
	a[rt]=a[ls]+a[rs];
}

int query(int l,int r,int L,int R,int rt,int ccs){//目标左端点，目标右端点，左端点，右端点，区间编号，层数 
	if(L>=l&&r>=R)return a[rt];
	int mid=(L+R)>>1,ll=0,rr=0;
	if(mid>=l)ll=query(l,r,L,mid,ls^rot[ccs],ccs-1);
	if(mid<r)rr=query(l,r,mid+1,R,rs^rot[ccs],ccs-1);
	return ll+rr;
}

signed main()
{
	read(n);read(p);
	int xx=1<<n;
	build(1,xx,1);
	int op,ll,rr;
	for(register int i=1;i<=p;i++){
		read(op);
		if(op==1){
			read(ll);read(rr);
			modify(ll,1,xx,1,rr,n);
		}
		if(op==2){
			read(ll);
			for(int i=0;i<=ll;i++)rot[i]^=1;
		}
		if(op==3){
			read(ll);rot[ll+1]^=1;
		}//2、3操作的含义于题目中已解释过了 
		if(op==4){
			read(ll);read(rr);
			printf("%lld\n",query(ll,rr,1,xx,1,n));
		}
	}
	return 0;
}
```


---

## 作者：奇米 (赞：4)

# 题解 - $\mathrm{CF1401F}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF1401F)

## $\mathrm{Sol}$

一道不难的ds题

我们考虑把序列放到线段树上，$2^n$ 个数相当于线段树的叶子结点上的数。

对于 $1\sim 4$ 的操作也就 $2,3$ 比较难维护，我们考虑对于 $2$ 操作，假设第 $i$ 个节点在线段树上为第 $d$ 层（$1$节点为第 $n$ 层）。那么反转操作相当于把下面所有层的左右儿子分别反转，于是我们对 $0\sim d$ 层打上标记即可。对于 $3$ 操作我们相当于就是在 $d+1$ 层打商标机就可以实现相邻块的交换了。

对于打上标记的层我们反向递归即可，其余的就是线段树区间求和啦，具体可以看代码实现。

时间复杂度 $O(2^{18}\times 18)$

## $\mathrm{Code}$

```cpp
const int mo=998244353;
const int N=1<<18;

int n,m,S,a[N+5],t[N*4+5],flg[21];

inline void Fix(int x,int l,int r,int p,int val,int d)
{
	if(p>r||p<l) return;
	if(l==r)
	{
		t[x]=val;
		return;
	}
	int mid=l+r>>1;
	if(flg[d]) Fix(x<<1|1,l,mid,p,val,d-1),Fix(x<<1,mid+1,r,p,val,d-1);
	else Fix(x<<1,l,mid,p,val,d-1),Fix(x<<1|1,mid+1,r,p,val,d-1);
	t[x]=t[x<<1]+t[x<<1|1];
}

inline int Ask(int x,int l,int r,int ll,int rr,int d)
{
	if(ll>r||rr<l) return 0;
	if(ll<=l&&r<=rr) return t[x];
	int mid=l+r>>1;
	int ans=0;
	if(flg[d]) ans=Ask(x<<1,mid+1,r,ll,rr,d-1)+Ask(x<<1|1,l,mid,ll,rr,d-1);//如果打上标记，那么对于左儿子要在[mid+1,r]里递归下去
	else ans=Ask(x<<1,l,mid,ll,rr,d-1)+Ask(x<<1|1,mid+1,r,ll,rr,d-1); 
	return ans;
}

signed main()
{
	io.read(n),io.read(m);
	S=(1ll<<n);
	For(i,1,S) 
	{
		io.read(a[i]);
		Fix(1,1,S,i,a[i],n);
	}
	for (;m--;)
	{
		int type,x,y;
		io.read(type);
		io.read(x);
		if((type^2)&&(type^3)) io.read(y);
		if(type==1) Fix(1,1,S,x,y,n);
		if(type==3) flg[x+1]^=1;
		if(type==2) For(i,0,x) flg[i]^=1;
		if(type==4) io.write(Ask(1,1,S,x,y,n)),puts("");
	}
	return 0;
}
			
		
	
	
```


---

## 作者：神光qwq (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1401F)
## 思维历程
看到对区间修改和查询以及数据范围 $2^{18}$，想到线段树，考虑如何维护翻转和交换的操作，由于是大部分整体操作，直接交换必然会超时。

观察到题干中所有范围都是和 $2^k$ 有关，而且线段树的第 $k$ 层（根是第 $n$ 层）控制范围都也刚好是 $2^k$，所以可以考虑直接使用懒标记在查询时直接交换访问左右子树时的下标，且由于只是对单层进行访问范围互换，所以对于更下面的儿子节点本身的有序性仍旧能够保证。

这样 Swap 就可以直接对 $k+1$ 层打懒标记（由于是两个 $2^k$ 层交换，所以应当操作他们的父亲节点），后面不论是修改还是求值就相当于进行了翻转。

最后考虑 Reverse 操作如何用已有的懒标记翻转区间进行维护，如果直接对整个区间翻转那么我们可以保证对于两边 $2^{k-1}$ 的范围的数，虽然他们内部仍旧是原本的顺序，但是在进行翻转后**两边的每个数必然都在完全翻转后应当存在的 $2^{k-1}$ 范围内**。

比如操作数列 $7,8,9,10$ 完全翻转，应当得到 $10,9,8,7$，先对第 $2$ 层操作，得到结果为 $9,10,7,8$，可以发现虽然没得到最终结果，但是第 $1$ 层的两个区间中的值不考虑顺序的情况下和答案一样，进而对第 $1$ 层操作，得到最终结果 $10,9,8,7$。

进而考虑每次都对区间直接翻转，维护整体正确性后继续对儿子区间进行翻转，最终达到能够保证所有数的正确性。

**一个小优化**：由于区间翻转两次时相当于没有翻转，所以应当使用异或维护懒标记。

~~本人拙见，如有差错，请赐教。~~

## 代码
##### 有注释。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define void inline void
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const ll N=(1<<18)+10;
ll n,q,x,y,type,a[N],lazy[110];
struct node{
	ll tl,tr,sum;
}t[N<<2];
inline ll read(){
	char ch=getchar();ll res=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}
void push_up(ll rt){
	t[rt].sum=t[ls].sum+t[rs].sum;
}
void build(ll rt,ll l,ll r){
	if(l==r){t[rt].sum=a[l];return ;}
	ll mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	push_up(rt);
}
void Replace(ll rt,ll L,ll R,ll x,ll k,ll depth){
	if(x<L||x>R) return ;
	if(L==R){t[rt].sum=k;return ;}
	ll mid=(L+R)>>1;
	if(lazy[depth]) Replace(ls,mid+1,R,x,k,depth-1),Replace(rs,L,mid,x,k,depth-1);//对调左右儿子访问范围，即区间翻转。 
	else Replace(ls,L,mid,x,k,depth-1),Replace(rs,mid+1,R,x,k,depth-1);
	push_up(rt);
}
void Reverse(ll k){
	for(ll i=0;i<=k;i++)//记得从0开始，叶子节点深度为0 。
		lazy[i]^=1;
}
void Swap(ll k){
	lazy[k+1]^=1;//必须是k+1，因为是对两个2^k交换。
}
inline ll Sum(ll rt,ll L,ll R,ll l,ll r,ll depth){
	if(R<l||r<L) return 0;
	if(l<=L&&R<=r)	return t[rt].sum;
	ll mid=(L+R)>>1;
	if(lazy[depth]) return Sum(ls,mid+1,R,l,r,depth-1)+Sum(rs,L,mid,l,r,depth-1);
	else return Sum(ls,L,mid,l,r,depth-1)+Sum(rs,mid+1,R,l,r,depth-1);
}
int main(){
	n=read(),q=read();
	for(ll i=1;i<=(1<<n);i++) a[i]=read();//数据范围为1<<n，不要错写成n。
	build(1,1,1<<n);
	while(q--){
		type=read();
		if(type==1) x=read(),y=read(),Replace(1,1,1<<n,x,y,n);
		if(type==2) x=read(),Reverse(x);
		if(type==3) x=read(),Swap(x);
		if(type==4) x=read(),y=read(),printf("%lld\n",Sum(1,1,1<<n,x,y,n));
	}
	return 0;
}
```


---

## 作者：ben090302 (赞：0)

数据结构题。

看到 $2^n$ 加上一堆 $2^k$ 的操作基本可以往线段树考虑了。

操作二三分别为：将数列划分成若干个 $2^k$ 的块，每块反转或一二互换三四互换这样的。我们发现二三操作的都是全局，而且都恰好会是线段树同层节点。

建线段树，然后考虑二三操作都是全局的，我们直接按层打标记，如果这层有标记就左右儿子反着走就可以了。

操作二就等价于给储存区间长度为 $2^0$ 到 $2^k$ 的节点标记，三等价于给 $2^{k+1}$ 的区间打标记。

然后就做完了。实现参考代码。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(p) (p<<1)
#define rs(p) ((p<<1)|1)
using namespace std;
const int N=2e6+5;
int n,q;

int a[N];

bool rev[N];

int tr[N];

void pushup(int p){
    tr[p]=tr[ls(p)]+tr[rs(p)];
}

void build(int p,int l,int r){
    if(l==r){
        tr[p]=a[l];
        // cerr<<p<<" ";
        // cerr<<tr[p]<<" ";
        return;
    }
    int mid=(l+r)>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
    pushup(p);
}

void change(int p,int l,int r,int X,int k){
    if(l==r){
        tr[p]=k;
        return;
    }
    int mid=(l+r)>>1;
    int G;
    G=rev[r-l+1];
    if(X<=mid){
        change(ls(p)^G,l,mid,X,k);
    }
    else{
        change(rs(p)^G,mid+1,r,X,k);
    }
    pushup(p);
}

int query(int p,int l,int r,int L,int R){
    if(L<=l and r<=R){
        return tr[p];     
    }
    // if(l>R or r<L) return 0;
	int mid=(l+r)>>1,ll=0,rr=0;
	if(mid>=L)ll=query(ls(p)^rev[r-l+1],l,mid,L,R);
	if(mid<R) rr=query(rs(p)^rev[r-l+1],mid+1,r,L,R);
    return ll+rr;
    // return query(ls(p)^G,l,mid,L,R)+query(rs(p)^G,mid+1,r,L,R);
} 



signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=(1<<n);i++){
        cin>>a[i];
    }
    build(1,1,(1<<n));
    while(q--){
        
        int opt,x,k;
        cin>>opt;
        if(opt==1){
            cin>>x>>k;
            change(1,1,(1<<n),x,k);
        }
        else if(opt==2){
            cin>>k;
            for(int i=0;i<=k;i++)
                rev[(1<<i)]^=1;
        }
        else if(opt==3){
            cin>>k;
            rev[(1<<(k+1))]^=1;
        }
        else{
            cin>>x>>k;
            cout<<query(1,1,(1<<n),x,k)<<"\n";
        }
    }
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

操作 $1,4$ 是很常规的单点修改，区间查询操作，重点是在维护操作 $2,3$ 的旋转。

可以发现对于操作 $2,3$ 都很难在节点上打上标记，如果暴力去打会因为结点数太多而时间复杂度直线上升。又观察到层数不超过 $19$，且建出的线段树是一棵完全二叉树。所以我们可以将标记打到层上。由于同层有多个结点，所以标记用完不能删除，但是不删除有可能会被旋转两次以上。所以我们利用标记永久化的思想：遇到标记反向走（应走左子树去走右子树，应走右子树去走左子树）来模拟线段树结点的旋转。

记得操作 $3$ 的标记要往上打一层，因为需要旋转的是这一层本身。

总时间复杂度 $O(2^n+qn)$。$n\leq 18$，包可过。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 20, M = 1e7 + 10;

struct Node {
  int ls, rs;
  int sum;
} t[M];

int n, q, idx, root, rev[N];

void pushup(int p) {
  t[p].sum = t[t[p].ls].sum + t[t[p].rs].sum;
}

void build(int &p, int l, int r) {
  p = ++idx;
  if(l == r) {
    cin >> t[p].sum;
    return ;
  }
  int mid = l + r >> 1;
  build(t[p].ls, l, mid);
  build(t[p].rs, mid + 1, r);
  pushup(p);
}

void upd(int p, int l, int r, int x, int k, int level) {
  if(l == r) {
    t[p].sum = k;
    return ;
  }
  int ls = t[p].ls, rs = t[p].rs;
  if(rev[level]) swap(ls, rs);
  int mid = l + r >> 1;
  if(x <= mid) upd(ls, l, mid, x, k, level-1);
  else upd(rs, mid + 1, r, x, k, level-1);
  pushup(p);
}

int ask(int p, int l, int r, int L, int R, int level) {
  if(L <= l && r <= R) {
    return t[p].sum;
  }
  int ls = t[p].ls, rs = t[p].rs;
  if(rev[level]) swap(ls, rs);
  int mid = l + r >> 1, ans = 0;
  if(L <= mid) ans += ask(ls, l, mid, L, R, level-1);
  if(R > mid) ans += ask(rs, mid + 1, r, L, R, level-1);
  return ans;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> q;
  build(root, 1, (1<<n));
  while(q--) {
    int op; cin >> op;
    if(op == 1) {
      int x, k;
      cin >> x >> k;
      upd(root, 1, (1<<n), x, k, n);
    } else if(op == 2) {
      int k; cin >> k;
      For(i,0,k) rev[i] ^= 1;
    } else if(op == 3) {
      int k; cin >> k;
      rev[k+1] ^= 1;
    } else {
      int l, r; cin >> l >> r;
      cout << ask(root, 1, (1<<n), l, r, n) << '\n';
    }
  }
  return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

## solution

发现 $2,3$ 操作都是对于全局进行的，所以考虑维护一个 $rev$ 数组，$rev_i$ 表示第 $i$ 层是否交换左右儿子（根节点为第 $1$ 层）。

操作 $2$ 相当于使 $\forall n-k+1\leq i\leq n,rev_i := rev_i \oplus 1$，操作 $3$ 相当于使 $rev_{n-k}$ 异或上 $1$。

操作 $1,4$ 用线段树维护即可，时间复杂度 $O(qn)$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 19;
int a[N], dep[N << 2], rev[30];

struct Node {
	long long s;
} tr[N << 2];

void pushup(int u) {
	tr[u].s = tr[u << 1].s + tr[u << 1 | 1].s;
}

void build(int u, int l, int r, int depth) {
	dep[u] = depth;
	if (l == r) {
		tr[u].s = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid, depth + 1), build(u << 1 | 1, mid + 1, r, depth + 1);
	pushup(u);
}

void modify(int u, int l, int r, int x, int k) {
	if (l == r) return tr[u].s = k, void();
	int mid = l + r >> 1;
	if (x <= mid) modify((u << 1) ^ rev[dep[u]], l, mid, x, k);
	else modify((u << 1 | 1) ^ rev[dep[u]], mid + 1, r, x, k);
	pushup(u);
}

long long query(int u, int l, int r, int s, int t) {
	if (s <= l && r <= t) return tr[u].s;
	int mid = l + r >> 1;
	long long res = 0;
	if (s <= mid) res += query((u << 1) ^ rev[dep[u]], l, mid, s, t);
	if (t > mid) res += query((u << 1 | 1) ^ rev[dep[u]], mid + 1, r, s, t);
	return res;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    int m = 1 << n; 
    for (int i = 1; i <= m; i ++ ) scanf("%d", &a[i]);
    build(1, 1, m, 1);
    while (q -- ) {
    	int op;
    	scanf("%d", &op);
    	if (op == 1) {
    		int x, k;
    		scanf("%d%d", &x, &k);
    		modify(1, 1, m, x, k);
		} else if (op == 2) {
			int k;
			scanf("%d", &k);
			for (int i = n - k + 1; i <= n; i ++ ) rev[i] ^= 1;
		} else if (op == 3) {
			int k;
			scanf("%d", &k);
			rev[n - k] ^= 1;
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%lld\n", query(1, 1, m, l, r));
		}
	}
    return 0;
}
```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路
巧妙的数据结构题，非常巧妙的利用的线段树的奇妙性质。

操作逐条维护：
- `Replace`： 直接线段树上单点修改；
- `Sum`：线段树查询区间和；
- `Reverse`：考虑线段树的形态。线段树第 $i$ 层（除最后一层）有 $2^{i-1}$ 个节点，那么将所有 $i\ge 1$ 的区间 $[(i-1)\times 2^k,i\times 2^k]$ 翻转，可以看作将线段树每一层均翻转一次。考虑用一个标记来表示每一层是否被翻转，因为翻转两次后相当于没有翻转，那么直接使用异或来维护即可，即每一次翻转操作让每一层的标记异或 $1$；
- `Swap`：观察两个被交换的区间，肉眼可见在除以 $2$ 之后就变成了一个 $[(i-1)\times 2^k,i\times 2^k]$ 的区间，而两个区间刚好各占一半。由于题目中唯一的查询操作是查询区间和，那么交换操作和翻转操作是等价的，那么直接修改第 $k+1$ 层的标记即可。

需要注意的是，在这种维护层的顺序下，区间 $[1,2^n]$ 实际上是位于第 $n$ 层的，然后不要忘了开 long long。

### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#define int long long
#define N (1<<18)+5
int n,q,a[N],Mark[N];
int tree[N<<1];
#define l(x) (x<<1)
#define r(x) ((x<<1)|1)
#define mid ((l+r)>>1)
inline void Push_Up(int now){
    tree[now]=
        tree[l(now)]+
        tree[r(now)];
}
inline void Update(int now,int l,int r,int p,int v,int depth){
    if(p>r||p<l) return;
    if(l==r){
        tree[now]=v;
        return;
    }
    if(Mark[depth]){
        Update(l(now),mid+1,r,p,v,depth-1);
        Update(r(now),l,mid,p,v,depth-1);
    }else{
        Update(l(now),l,mid,p,v,depth-1);
        Update(r(now),mid+1,r,p,v,depth-1);
    }Push_Up(now);
}
inline int Query(int now,int l,int r,int L,int R,int depth){
    if(L>r||R<l) return 0;
    if(L<=l&&r<=R)
        return tree[now];
    int Lans,Rans;
    if(Mark[depth]){
        Lans=Query(l(now),mid+1,r,L,R,depth-1);
        Rans=Query(r(now),l,mid,L,R,depth-1);
    }else{
        Lans=Query(l(now),l,mid,L,R,depth-1);
        Rans=Query(r(now),mid+1,r,L,R,depth-1);
    }return Lans+Rans;
}
signed main(){
    scanf("%lld%lld",&n,&q);
    for(register int i=1;i<=1<<n;++i)
        scanf("%lld",&a[i]);
    for(register int i=1;i<=1<<n;++i)
        Update(1,1,1<<n,i,a[i],n);
    int opt,x,k;while(q--){
        scanf("%lld",&opt);
        switch (opt){
            case 1:{
                scanf("%lld",&x);
                scanf("%lld",&k);
                Update(1,1,1<<n,x,k,n);
                break;
            }
            case 2:{
                scanf("%lld",&k);
                for(register int i=0;i<=k;++i)
                    Mark[i]^=1;break;
            }
            case 3:{
                scanf("%lld",&k);
                Mark[k+1]^=1;
                break;
            }
            default:{
                scanf("%lld",&x); scanf("%lld",&k);
                printf("%lld\n",Query(1,1,1<<n,x,k,n));
                break;
            }
        }
    }
}
```

---

## 作者：_Never45_ (赞：0)

一个神奇的线段树运用。

首先对不是人话的题面进行翻译，重点是二三操作。

二操作：分成长为 $2^k$ 的块，每个块进行翻转。

三操作：分成长为 $2^k$ 的块，每两个块交换。

发现整个题目都与 $2^k$ 有关，考虑运用与之对应的数据结构，因为较为复杂，使用线段树。

回忆线段树的形态，发现从下往上第 $n$ 层与之对应的线段长度为 $2^{n-1}$。

为了方便，下面令叶子节点层数为 $0$。

现在要化简修改操作，结合下面线段树形态图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8a5selhz.png)

我们此时要对 $x,y$ 进行交换操作。可以发现，只需将他们的父节点左右儿子指向交换即可。

要对 $x$ 翻转，则交换它的左右儿子，再交换左右儿子的左右儿子，以此类推，直到叶子。

实际实现中，只需记录每一层左右儿子的交换次数，具体运算时临时交换即可。

如：

```C++
void Modify(long long l, long long r, long long idx, long long x, long long y)
{
	if(l == r)
	{
		tree[idx].sum = y;
		return;
	}
	long long mid = (l + r) >> 1;
	if(x <= mid)
	{
		if(sum[tree[idx].c] & 1) Modify(l, mid, idx * 2 + 1, x, y);
		else Modify(l, mid, idx * 2, x, y);
	}else{
		if(sum[tree[idx].c] & 1) Modify(mid + 1, r, idx * 2, x, y);
		else Modify(mid + 1, r, idx * 2 + 1, x, y);
	}
	tree[idx].sum = tree[idx * 2].sum + tree[idx * 2 + 1].sum;
}
```

full code:
```cpp

#include <bits/stdc++.h>

using namespace std;

const int N = (1 << 18) | 5;

long long n, T, a[N];
long long ch[N], sum[N];
struct Node{
	long long sum;
	long long c;
}tree[N * 4];

void Build(long long l, long long r, long long idx, long long x)
{
	if(l == r)
	{
		tree[idx].sum = a[l];
		return;
	}else{
		long long mid = (l + r) >> 1;
		Build(l, mid, idx * 2, x - 1);
		Build(mid + 1, r, idx * 2 + 1, x - 1);
		tree[idx].sum = tree[idx * 2].sum + tree[idx * 2 + 1].sum;
	}
	
	tree[idx].c = x;
}

void Modify(long long l, long long r, long long idx, long long x, long long y)
{
	if(l == r)
	{
		tree[idx].sum = y;
		return;
	}
	long long mid = (l + r) >> 1;
	if(x <= mid)
	{
		if(sum[tree[idx].c] & 1) Modify(l, mid, idx * 2 + 1, x, y);
		else Modify(l, mid, idx * 2, x, y);
	}else{
		if(sum[tree[idx].c] & 1) Modify(mid + 1, r, idx * 2, x, y);
		else Modify(mid + 1, r, idx * 2 + 1, x, y);
	}
	tree[idx].sum = tree[idx * 2].sum + tree[idx * 2 + 1].sum;
}

long long Get(long long l, long long r, long long idx, long long L, long long R)
{
	if(L <= l && r <= R) return tree[idx].sum;
	
	long long mid = (l + r) >> 1, ans = 0;
	if(L <= mid)
	{
		if(sum[tree[idx].c] & 1) ans += Get(l, mid, idx * 2 + 1, L, R);
		else ans += Get(l, mid, idx * 2, L, R);
	}
	if(R > mid)
	{
		if(sum[tree[idx].c] & 1) ans += Get(mid + 1, r, idx * 2, L, R);
		else ans += Get(mid + 1, r, idx * 2 + 1, L, R);
	}
	return ans;
}

int main()
{
	scanf("%lld%lld", &n, &T);
	
	for(int i = 1; i <= (1 << n); ++i) scanf("%lld", &a[i]);
	
	Build(1, (1 << n), 1, n);
	
	while(T--)
	{
		long long op;
		scanf("%lld", &op);
		if(op == 1)
		{
			long long x, y;
			scanf("%lld%lld", &x, &y);
			sum[0] = ch[0]; 
			for(int i = 1; i <= n; ++i) sum[i] = ch[i] + sum[i - 1];
			Modify(1, (1 << n), 1, x, y);
		}
		if(op == 2)
		{
			long long k;
			scanf("%lld", &k);
			ch[0] += 1, ch[k + 1] += 1;
		}
		if(op == 3)
		{
			long long k;
			scanf("%lld", &k);
			ch[k + 1] += 1, ch[k + 2] += 1;
		}
		if(op == 4)
		{
			long long x, y;
			scanf("%lld%lld", &x, &y);
			sum[0] = ch[0];
			for(int i = 1; i <= n; ++i) sum[i] = ch[i] + sum[i - 1];
			printf("%lld\n", Get(1, (1 << n), 1, x, y));
		}
	}
	
	return 0;
}
```


---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

抽象思维题。

全是狠活没有科技。

题意简述：

- 给定长度 $2^n$ 的序列，需要支持以下操作：
- 单点修改；
- 给定 $k$，然后把区间划分成几段，每段长度都是 $2^k$，接下来把每一段内部的元素翻转，例如 ```1 1 4 5 1 4``` 变成 ```4 1 5 4 1 1```；
- 给定 $k$，然后把区间划分成几段，每段长度都是 $2^k$，接下来把区间从 $1$ 开始标号，然后 $1$ 和 $2$ 交换，$3$ 和 $4$ 交换……例如每段长度是 $2$，则 ```1 1 4 5 1 9 1 9``` 变成 ```4 5 1 1 9 1 9 1```。可以证明不会出现一个区间无法交换；
- 区间求和。

~~旋转？Splay！~~

充分发扬人类智慧的题目。看到抽象的题目观察有哪些地方更抽象。很容易发现序列长度和要划分的段的长度都是 $2$ 的次幂。

很容易就能联想到二进制，然后根据操作 $1$ 和 $4$ 看上去很熟悉，我们基本确定这题的解法不是 Splay 而是 **抽象的线段树**。

那么如果您稍微理解过线段树，你就会发现在这题的数据下我们对序列构建的线段树一定是一个标准的 **完全二叉树** 并且如果根节点是第 $n$ 层叶节点是第 $0$ 层的话，**第 $i$ 层的节点维护的区间长度正好是 $2^i$**。

具体的原因请见普通线段树的 ```build``` 操作。每一次往下递归我们的区间大小除以二，而本题序列长度为 $2$ 的次幂所以左右儿子维护的区间大小一定相等。

好，那么旋转操作该如何维护？

我们考虑普通线段树是如何往下递归的。它的左儿子维护的是 $[l,mid]$ 这一段，右儿子维护的是 $[mid+1,r]$ 这一段。

**如果我们把左右儿子交换呢**？此时左右儿子维护的区间仍然不变，但我们向下递归时调用“左儿子”，得到的将会是 $[mid+1,r]$ 这一段！

至此我们大体口胡了操作 $3$，然后操作 $2$ 也就差不多出来了：

对于所有层数小于等于 $k$ 的，我们都执行一次交换左右儿子，此时就会得到顺序相反的序列。

于是问题归到了 **如何进行左右儿子的交换**。

- 能不能像普通线段树一样传 tag？

没试过，但是看上去不可行。增加大码量而且不好下放。~~你以为我在一开始说是抽象题目全是狠活是写普通线段树的？~~

我们对于每一层记录一个 $rv$ 代表这一层交换了几次左右儿子。因为交换两次等于没有交换所以直接用 01 记录是否需要交换。

- 这种思路是错的吧，如果我们递归到这里发现要交换就交换左右儿子，再递归到这里一次不会把左右儿子交换回来吗？

~~差点就被这种错误思想误导了/kk~~

我们没有必要真的交换左右儿子。思考普通线段树左右儿子是如何存储的。

对于左儿子：```p<<1```。

对于右儿子：```p<<1|1```。

发现只有 ```|1``` 的区别。刚好我们的 $rv$ 数组也是 01 类型的，我们可以直接靠 $rv$ 数组来得到左右儿子。

那么就做完了。

```cpp
#include <bits/stdc++.h>
#define ri register int
#define int long long//要开 long long

using namespace std;
const int N=(1<<18);

inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}

inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+48);
	return;
}

int n,Q,a[N+10],sg[(N<<2)+10];
bool rv[20];

inline void build(int l,int r,int p){
	if(l==r)sg[p]=a[l];
	else{
		int mid=((l+r)>>1);
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		sg[p]=sg[p<<1]+sg[p<<1|1];
	}
	return;
}

inline void chg(int ps,int l,int r,int p,int K,int d){
	if(l==ps&&r==ps)sg[p]=K;
	else{
		int mid=((l+r)>>1),ls=p<<1|rv[d],rs=p<<1|(!rv[d]);
		if(ps<=mid)chg(ps,l,mid,ls,K,d-1);
		else chg(ps,mid+1,r,rs,K,d-1);
		sg[p]=sg[ls]+sg[rs];
	}
	return;
}

inline int qry(int ql,int qr,int l,int r,int p,int d){
	if(ql<=l&&r<=qr)return sg[p];
	int mid=((l+r)>>1),ls=p<<1|rv[d],rs=p<<1|(!rv[d]),ret=0;
	if(ql<=mid)ret+=qry(ql,qr,l,mid,ls,d-1);
	if(qr>mid)ret+=qry(ql,qr,mid+1,r,rs,d-1);
	sg[p]=sg[ls]+sg[rs];
	return ret;
}

signed main(){
	n=read();Q=read();
	for(ri i=1;i<=(1<<n);i++)a[i]=read();
	build(1,1<<n,1); 
	while(Q--){
		int op=read();
		if(op==1){
			int x=read(),K=read();
			chg(x,1,1<<n,1,K,n);
		}else if(op==2){
			int x=read();
			for(ri i=1;i<=x;i++)rv[i]^=1;
		}else if(op==3)rv[read()+1]^=1;
		else{
			int x=read(),y=read();
			write(qry(x,y,1,1<<n,1,n));
			putchar(10);
		}
	}
	return 0;
} 
```

马上就要 csp-j/s 了，在这里祝各位 csp-j/s 全部一等！加油！

$\large\color{white}\text{不要退役}$

---

## 作者：听取MLE声一片 (赞：0)

牛逼题。

二操作是划分出若干个长度为 $2^k$ 的区间，然后每个区间进行区间翻转。 

三操作是划分出若干个长度为 $2^k$ 的区间，交换相邻两个区间。

第一个和第四个操作操作我们是会做的，剩下两个操作都和 $2^k$ 的区间有关，可以想到使用线段树。

因为有区间翻转、交换，考虑平衡树区间翻转的思想。在线段树上，改变左右儿子的顺序即为翻转。区间交换就是直接左右子树交换一次，区间翻转考虑标记永久化，把后续遍历的左右儿子都翻转即可，这样能做二三操作是区间修改的情况。

注意到这是一棵满二叉树，而且二三操作都是全局操作，就有更加简单的处理。

把线段树进行分层，叶子节点为第 $0$ 层，根节点为第 $n$ 层。因为是全局操作，所以每一层的所有点的翻转标记都是相同的，合并在一起维护即可。

当操作的 $k=0$ 就对应第 $0$ 层，$k=1$ 就对应第 $1$ 层，以此类推。

对于第 $k$ 层翻转操作，就是把第 $k$ 层到第 $0$ 层全部翻转。

对于第 $k$ 层交换操作，就是把第 $k+1$ 层翻转即可。

子树左右儿子的翻转，只需要把左右儿子谁加一处理一下即可。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define int long long
#define Ls (p<<1)
#define Rs (p<<1|1)
#define ls (p<<1|rev[dep])
#define rs (p<<1|(rev[dep]^1))
#define mid ((l+r)>>1)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=20;
const int M=3e5+10;
int n,m,q,a[M],sum[M<<1],rev[N];
inline void pushup(int p){
	sum[p]=sum[Ls]+sum[Rs];
}
void build(int p,int l,int r){
	if(l==r){
		sum[p]=a[l];
		return;
	}
	build(Ls,l,mid);
	build(Rs,mid+1,r);
	pushup(p);
}
void update(int x,int p,int l,int r,int dep,int y){
	if(l==r){
		sum[p]=y;
		return;
	}
	if(x<=mid)update(x,ls,l,mid,dep-1,y);
	if(x>mid) update(x,rs,mid+1,r,dep-1,y);
	pushup(p);
}
int query(int L,int R,int p,int l,int r,int dep){
	if(L<=l&&r<=R)
		return sum[p];
	int res=0;
	if(L<=mid)res+=query(L,R,ls,l,mid,dep-1);
	if(R>mid) res+=query(L,R,rs,mid+1,r,dep-1);
	return res;
}
inline void reverse(int x){
	for(int i=0;i<=x;i++)
		rev[i]^=1;
}
inline void Swap(int x){
	rev[x+1]^=1;
}
signed main()
{
	n=read(),q=read();
	m=1<<n;
	for(int i=1;i<=m;i++)
		a[i]=read();
	build(1,1,m);
	while(q--){
		int opt=read();
		if(opt==1){
			int x=read(),y=read();
			update(x,1,1,m,n,y);
		}
		if(opt==2){
			int x=read();
			reverse(x);
		}
		if(opt==3){
			int x=read();
			Swap(x);
		}
		if(opt==4){
			int l=read(),r=read();
			printf("%lld",query(l,r,1,1,m,n));
			putchar('\n');
		}
	}
	return 0;
}

```



---

## 作者：qczrz6v4nhp6u (赞：0)

## 题意
操作 1：单点赋值。  
操作 2；区间反转。  
操作 3：区间交换。  
操作 4：区间求和。
## Solution
看到单点修改区间求和，我们会想到线段树；而看到区间反转我们又会想到平衡树。

考虑到数组长度及大部分操作与 $2$ 的次幂直接相关，我们尽量往线段树上面靠。

数组长度是 $2$ 的次幂有什么好处呢？

线段树划分子节点时，子节点的长度会**正好**变为父节点一半。

换句话说，**子节点的长度也会是 $2$ 的次幂**。

于是我们可以发现一个东西：操作 2 和 3 实际上就是对线段树上长度为定值的节点进行操作。

于是我们用平衡树一样处理区间反转的方式，在节点上打标记。

因为操作 2 和 3 涉及的修改都是整层，我们直接在层号上打标记。

### 做法 

以下记**长度为 $2^k$ 的节点为第 $k$ 层节点**。

定义 $rev_k$ 为是否反转第 $k$ 层节点的子节点的标记。

对于操作 2，我们需要将第 $k$ 层及以下的节点反转。  
于是我们将 $0\le i\le k$ 的 $rev_i$ 取反。

对于操作 3，我们需要反转相邻成对的第 $k$ 层节点。  
相当于反转第 $k+1$ 层的两个子节点，于是将 $rev_{k+1}$ 取反。

$rev$ 朴素修改即可。（~~您可以再建一棵线段树~~

剩下的就是线段树模板了，访问左右节点时考虑 $rev$ 的影响即可。

时间复杂度 $O(qn)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=(1<<18)+5;
int n,q;
ll a[N];
namespace SegTr{
	int tlen;
	bool rev[20];
	struct segtr{int son[2];ll dat;}t[N*2];
	#define lc (t[p].son[rev[dep]])
	#define rc (t[p].son[!rev[dep]])
	void upd(int p){t[p].dat=t[t[p].son[0]].dat+t[t[p].son[1]].dat;}
	int build(int l,int r){
		int p=++tlen;
		if(l==r)t[p].dat=a[l];
		else{
			int mid=(l+r)>>1;
			t[p].son[0]=build(l,mid);
			t[p].son[1]=build(mid+1,r);
			upd(p);
		}
		return p;
	}
	//操作 1 
	void replace(int p,int l,int r,int dep,int x,ll k){
		if(l==r){t[p].dat=k;return;}
		int mid=(l+r)>>1;
		if(x<=mid)replace(lc,l,mid,dep-1,x,k);
		else replace(rc,mid+1,r,dep-1,x,k);
		upd(p);
	}
	//操作 2 
	void reverse(int k){for(int i=k;i>=0;i--)rev[i]^=1;}
	//操作 3 
	void swap(int k){rev[k+1]^=1;}
	//操作 4 
	ll sum(int p,int l,int r,int dep,int x,int y){
		if(l>=x&&r<=y)return t[p].dat;
		int mid=(l+r)>>1;ll res=0;
		if(x<=mid)res+=sum(lc,l,mid,dep-1,x,y);
		if(y>mid)res+=sum(rc,mid+1,r,dep-1,x,y);
		return res;
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=(1<<n);i++)scanf("%lld",&a[i]);
	SegTr::build(1,1<<n);
	while(q--){
		int op;
		scanf("%d",&op);
		if(op==1){
			int x;ll k;
			scanf("%d%lld",&x,&k);
			SegTr::replace(1,1,1<<n,n,x,k);
		}
		if(op==2){
			int k;
			scanf("%d",&k);
			SegTr::reverse(k);
		}
		if(op==3){
			int k;
			scanf("%d",&k);
			SegTr::swap(k);
		}
		if(op==4){
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",SegTr::sum(1,1,1<<n,n,l,r));
		}
	}
}
```


---

## 作者：ListenSnow (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1401F)

## 题意

给定一个长度为 $2^n$ 的数组 $a$，现在需要处理 $q$ 个询问，每个询问是以下 $4$ 种类型之一：

1. $Replace(x, k)$ 把 $a_x$ 修改为 $k$。

2. $Reverse(k)$ 对于每一个 $i(i\ge 1)$ ，把区间 $[(i-1)\cdot 2^k+1, i\cdot 2^k]$ 的元素翻转。

3. $Swap(k)$ 对于每一个  $i(i\ge 1)$ ，交换区间 $[(2i-2)\cdot2^k+1,(2i-1)\cdot2^k]$ 和 $[(2i-1)\cdot2^k+1,2i\cdot2^k]$ 的所有元素。

4. $Sum(l,r)$ 输出区间 $[l,r]$ 中所有元素的和。

#### 数据范围

$0\leq n \leq 18,1\leq n \leq 10^5,0\leq a_i\leq10^9$。

## 思路

注意到数组的长度和操作的区间比较特殊。不难发现建立线段树以后，每次 $2,3$ 操作的区间必然对应到线段树上相应的若干完整的节点。

设线段树的根节点为第 $n$ 层，层数依次往下递减，那么第 $k$ 层自左向右第 $i$ 个节点就对应到原数组的区间 $[(i-1)\cdot 2^k+1, i\cdot 2^k]$。记 $rev_i$ 表示第 $i$ 层节点的左右儿子是否交换。

对于 Replace 和 Sum 操作，直接在线段树上递归修改或查询即可。

对于 Reverse 操作，在线段树上对应到将第 $k$ 层的所有节点对应的区间翻转，实质上就是交换第 $1 \sum k$ 层的所有节点的左右儿子，那么只需要将对应的 $rev_i$ 修改即可。

对于 Swap 操作，不难发现就是交换第 $k+1$ 层所有节点的左右儿子，只需要修改 $rev_{k+1}$ 即可。

## code：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e5+10;
#define LL long long
int n,m;bool rev[N];LL val[N<<2];
void push_up(int p){val[p]=val[p<<1]+val[p<<1|1];}
void build(int p,int l,int r)
{
	if(l==r) return scanf("%lld",&val[p]),void();int mid=l+r>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);push_up(p);
}
void update(int p,int l,int r,int x,int k,int dep)
{
	if(l==r) return val[p]=k,void();int mid=l+r>>1;
	if(x<=mid) update(p<<1|rev[dep],l,mid,x,k,dep-1);
	else update(p<<1|rev[dep]^1,mid+1,r,x,k,dep-1);
	push_up(p);
}
LL query(int p,int l,int r,int L,int R,int dep)
{
	if(L<=l&&r<=R) return val[p];int mid=l+r>>1;LL res=0;
	if(L<=mid) res+=query(p<<1|rev[dep],l,mid,L,R,dep-1);
	if(R>mid) res+=query(p<<1|rev[dep]^1,mid+1,r,L,R,dep-1);
	return res;
}
void Reverse(int k){for(int i=0;i<=k;i++) rev[i]^=1;}
int main()
{
	scanf("%d%d",&n,&m);build(1,1,1<<n);
	while(m--)
	{
		int opt,x,y;scanf("%d",&opt);
		if(opt==1) scanf("%d%d",&x,&y),update(1,1,1<<n,x,y,n);
		if(opt==2) scanf("%d",&x),Reverse(x);
		if(opt==3) scanf("%d",&x),rev[x+1]^=1;
		if(opt==4) scanf("%d%d",&x,&y),printf("%lld\n",query(1,1,1<<n,x,y,n));
	}
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

很久以前就发现的一道~~水~~题，因为第一次看到 $F$ 题是个蓝就觉得很淦，所以把它放进题单里面吃了很久土，今天整理题单时顺便拿出来补了补。    
其实如果你会平衡树，会区间反转就知道这题该怎么做了。      

我们首先手玩一下，发现它的难点操作都在 $2 , 3$ 上，我们尝试突破这两个操作。       

这里为了方便描述，令叶节点为 $0$ 层，根节点为 $n$ 层。

我们先思考操作 $2$ ，发现它其实就是把第 $k$ 层的点执行了一个 $rev$ 操作，而对于我们对 $rev$ 操作的一般做法，就是来个懒标记然后往下面传传传，可是这道题的话这么做岂不是会被卡吗？比如说我全给你一个层数在叶子节点的 $rev$ 操作就妥妥的 $O(mn)$ 吃土。       

发现每层的交换其实是一样的，所以我们直接暴力记录每一层的修改情况。   

记 $Swap_x$ 表示第 $x$ 层的儿子们的交换情况， $0$ 表示不交换， $1$ 表示交换。   

对于 $2$ 操作，我们暴力把 $Swap_0 \sim Swap_k$ 都暴力维护一下。    

对于 $3$ 操作，我们发现它其实就是把 $k + 1$ 层的所有点的儿子们交换一下，$Swap_k + 1$ 改一改直接 $O(1)$ 修改了好吗？       

然后线段树操作一下，只不过在这里为了方便实现，我们不实际交换左右儿子，往下递归时看交换儿子没有即可。       

不得不说没有什么难点，这场CF和最近~~某场CF~~一样应该是送分场。     

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define int long long
const int Len = (1 << 18) + 5;
int N,n,m,a[Len],ls[Len << 2],rs[Len << 2],ans[Len << 2],Swap[23];
void push_up(int x){ans[x] = ans[ls[x]] + ans[rs[x]];}
inline void build(int p,int l,int r)
{
	ls[p] = p << 1;
	rs[p] = p << 1 | 1;
	if(l == r) 
	{
		ans[p] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls[p] , l , mid);
	build(rs[p] , mid + 1 , r);
	push_up(p);
} 
void update(int p,int l,int r,int idx,int w,int dep)
{
	if(l == r)
	{
		ans[p] = w;
		return;
	}
	int mid = (l + r) >> 1;
	int Lson = ls[p] , Rson = rs[p];
	if(Swap[dep]) swap(Lson , Rson);
	if(idx <= mid) update(Lson , l , mid , idx , w , dep - 1);
	else update(Rson , mid + 1 , r , idx , w , dep - 1);
	push_up(p);
}
int query(int p,int l,int r,int nl,int nr,int dep)
{
	if(nl <= l && nr >= r) return ans[p];
	int mid = (l + r) >> 1 , res = 0;
	int Lson = ls[p] , Rson = rs[p];
	if(Swap[dep]) swap(Lson , Rson);
	if(nl <= mid) res = res + query(Lson , l , mid , nl , nr , dep - 1);
	if(nr > mid) res = (res + query(Rson , mid + 1 , r , nl , nr , dep - 1));
	return res;
}
signed main()
{
	scanf("%lld %lld",&N,&m);n = 1 << N;
	for(int i = 1 ; i <= n ; i ++) scanf("%lld",&a[i]);
	build(1 , 1 , n);
	for(int i = 1 ; i <= m ; i ++)
	{
		int opt,x,k;scanf("%lld",&opt);
		if(opt == 1){scanf("%lld %lld",&x,&k);update(1 , 1 , n , x , k , N);}
		if(opt == 2){scanf("%lld",&k);for(int i = 0 ; i <= k ; i ++) Swap[i] ^= 1;}
		if(opt == 3){scanf("%lld",&k);Swap[k + 1] ^= 1;}
		if(opt == 4){scanf("%lld %lld",&x,&k);printf("%lld\n",query(1 , 1 , n , x , k , N));}
	}
	return 0;
}
```

---

## 作者：fanfansann (赞：0)

${\ }{\ }{\ }{\ }{\ }{\ }{\ }$首先一共有四个操作，第一个和第四个都是线段树的基本操作，直接用线段树实现。
  
  
${\ }{\ }{\ }{\ }{\ }{\ }{\ }$第二个和第三个操作都是在分成 $2 ^ k$ 长度区间操作，并且题目中的序列一共有 $2^n$ 个节点，如果放到线段树里正好是 $n+1$ 层，每层都由 $2 ^ k$ 长度区间构成。第 $0$ 层为叶子节点，第 $n$ 层为根节点
  
  
${\ }{\ }{\ }{\ }{\ }{\ }{\ }$对于第三个操作 $swap$ ：相当于交换线段树两个相邻且长度为 $2^k$ 的区间，由于本题一共有 $p = 1e5$ 个修改查询操作，所以如果每次修改都修改的话哪怕是线段树也一定会超时。因此我们可以取巧，不真正地进行修改，而是每次查询或者修改单点操作的时候，根据修改标记来访问到相邻的区间。也就是相当于想要访问该节点的左（右）子树时候，由于区间翻转了，我们直接访问另一个右（左）子树区间即可。可以用一个变量来记录以下是否需要改变访问的左右结点。比如当前$swap$的是第 $k$ 层 ，那么只需要标记第 $k + 1$ 层，这样我们访问到该节点的第 $k + 1$层的时候，根据标记的指引就会跳转到第$k$层的相邻区间，满足题意。
  
  
  
${\ }{\ }{\ }{\ }{\ }{\ }{\ }$第二个同理，区间翻转我们参考[文艺平衡树](https://www.luogu.com.cn/problem/P3391)这道题，想要实现区间翻转，只需要把区间里的所有左右子树全部交换即可。而左右子树正好都是相邻的区间，那么我们对整个区间都做一次类似操作三的标记即可。假如当前需要$reverse$第 $k$ 层，因为线段树是一颗满二叉树，在我们寻找该区间的时候如果到达第$k$层的时候，该点的左右子树就表示整个要找的区间，我们需要将第 $k$ 层以下的层全部翻转，也就是将$0$ ~ $k$ 层的节点都打赏标记即可。
  
  
  
${\ }{\ }{\ }{\ }{\ }{\ }{\ }$具体细节看代码，是在线段树模板的基础之上进行改进得到的。
  
  

**这里有两个易错点：**


  
- 因为线段树翻转问题的解决办法是在翻转半区间打上标号，有标记的节点左右子树互换（实际体现就是查找的时候交换即可，整棵树实际上是不用动的），因此所有操作在寻找预定区间的时候就不能在根据当前根节点寻找预定区间，因为这里的p已经可能变了，就不能用 $tr[p].l$ 和 $tr[p].r$ 所以我们应该再传入参数 $l$ 和 $r$ 来辅助寻找预定区间。
- 凡是涉及到位运算的都要疯狂加括号！！！位运算的优先级实在是太糟糕了

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

typedef long long ll;
using namespace std;
const int N = 2000005;

int n, m;
int a[N];
int rev[N], cnt;
struct tree{
    int l, r;
    ll sum;
}tr[N << 2];

void pushup(int p)
{
    tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}

void build(int p, int l, int r)
{
    tr[p] = {l, r, 0};
    if(l == r){
        tr[p].sum = a[r];
        return ;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void modify(int l, int r, int p, int x, int val, int depth)
{
    if(l == r){
        tr[p].sum = val;
        return ;
    }
    int mid = l + r >> 1;
    if(x <= mid)modify(l, mid, (p << 1) + (rev[depth] == 1), x, val, depth - 1);
    else modify(mid + 1, r, (p << 1 | 1) - (rev[depth] == 1), x, val, depth - 1);
    pushup(p);
}

ll query(int rl, int rr, int p, int l, int r, int depth)
{

    if(rl >= l && rr <= r)
        return tr[p].sum;
    int mid = rl +rr >> 1;
    ll ans = 0;
    if(l <= mid)ans += query(rl, mid, (p << 1) + (rev[depth] == 1), l, r, depth - 1);
    if(r > mid)ans += query(mid + 1, rr, (p << 1 | 1) - (rev[depth] == 1), l, r, depth - 1);
    return ans ;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= (1 << n); ++ i)
        scanf("%d", &a[i]);
    build(1, 1, 1 << n);
    while(m -- ){
        int op, x, y;
        scanf("%d%d", &op, &x);
        if(op == 1){
            scanf("%d", &y);
            modify(1, 1 << n, 1, x, y, n);// 2^n 个节点, 线段树一共会有n+1层第0层为叶子节点,第n层为根节点
        }
        else if(op == 2)for(int i = 0; i <= x; ++ i)rev[i] ^= 1;
        else if(op == 3)rev[x + 1] ^= 1;
        else {
            scanf("%d", &y);
            printf("%lld\n", query(1, 1 << n, 1, x, y, n));
        }
    }
    return 0;
}

```


---

## 作者：lucifer1004 (赞：0)

### 题目描述

有一个总长度为$2^n$的数组，要求支持以下四种操作：

- $replace(x,k)$，将位置$x$处的数设为$k$
- $reverse(k)$，将每一段长度为$2^k$的子区间倒序
- $swap(k)$，交换每两段相邻的长度为$2^k$的子区间
- $sum(l,r)$，求$[l,r]$范围内所有数的和

### 题解

整个数组可以用一个线段树维护（并且这个线段树是一个完全二叉树），麻烦的是如何处理倒序和交换这两种操作。

无论倒序还是交换，相同的操作连续进行两次，等价于没有进行操作；另一方面，对于任意一层，它的两个孩子的分组关系是恒定不变的，会改变的只有它们的左右位置和内部顺序。以$[1,2,3,4,5,6,7,8]$为例，无论是进行倒序，还是交换，都不会改变$\{1,2,3,4\}$和$\{5,6,7,8\}$这样的分组关系；同样，向下一层，$\{1,2\}$和$\{3,4\}$的分组，$\{5,6\}$和$\{7,8\}$的分组也是始终保持的。

因此，我们可以用两个二进制数，一个记录当前的倒序操作，另一个记录当前的交换操作。每次有新的操作，就与当前的状态进行异或即可。

对于倒序和交换这两种操作，我们并不需要对线段树进行任何操作，直接修改对应的状态即可。实际需要实现的线段树操作就是单点赋值和区间查询。这里的难点在于，操作中给出的位置，并不一定对应实际的位置，而需要我们根据当前的倒序和交换状态，将其进行变换，以得到最终的实际位置。

赋值的情况相对简单，因为我们只需要处理一个点。如果当前层有倒序操作，我们就把这个点翻转到对称点上；如果还有交换操作，我们就再将这个点进行一个循环平移。

查询时我们需要处理一个区间，这时我们不能简单地只处理两个端点，因为对于两个端点跨越了当前区间中点的情形，这段连续区间实际上会对应两个不连续的区间。比如，数组$[1,2,3,4,5,6,7,8]$经过$swap(2)$和$reverse(3)$操作后，变为了$[4,3,2,1,8,7,6,5]$。这时，假设我们查询$[3,7]$，因为在最上层有倒序操作，所以我们翻转区间，将其变为$[2,6]$；然后，因为有交换操作，两个端点会变为$6$和$2$，但此时，如果我们继续按照$[2,6]$来进行操作，显然会发生错误，因为我们可以看到这段区间对应的值是$[2,1,8,7,6]$，实际上是$[1,2]$和$[6,8]$这两段不连续的区间。因此，我们要把倒序后得到的$[2,6]$首先拆分为$[2,4]$和$[5,6]$，然后对这两段区间分别进行平移，就可以得到$[1,2]$和$[6,8]$了。而如果两个端点在当前区间中点的同一侧，则不需要进行这一额外处理。

### 参考代码

```cpp
#include <cstdio>
#include <iostream>
#define MAXN 300005
#define lson (idx << 1)
#define rson (idx << 1 | 1)

using namespace std;
typedef long long ll;

template <typename T> void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-')
      sig = -1;
  for (; isdigit(c); c = getchar())
    x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

int a[MAXN], ss = 0, rr = 0;
ll s[MAXN << 2];

void calc(int idx) { s[idx] = s[lson] + s[rson]; }

void build(int idx, int l, int r) {
  if (l == r) {
    s[idx] = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(lson, l, mid);
  build(rson, mid + 1, r);
  calc(idx);
}

void move(int &idx, int level) { idx = ((idx - 1) ^ (1 << (level - 1))) + 1; }

void update(int idx, int pos, int val, int level, int cl, int cr) {
  if (level == 0) {
    s[idx] = val;
    return;
  }
  bool fr = (rr & (1 << level));
  bool fs = (ss & (1 << level));
  int mid = (cl + cr) >> 1;
  if (fr)
    pos = cl + cr - pos;
  if (fs)
    move(pos, level);
  if (pos <= mid)
    update(lson, pos, val, level - 1, cl, mid);
  else
    update(rson, pos, val, level - 1, mid + 1, cr);
  calc(idx);
}

ll query(int idx, int l, int r, int level, int cl, int cr) {
  if (cl >= l && cr <= r)
    return s[idx];
  ll ans = 0;
  bool fr = (rr & (1 << level));
  bool fs = (ss & (1 << level));
  int mid = (cl + cr) >> 1;
  if (fr)
    l = cl + cr - l, r = cl + cr - r, swap(l, r);
  if (r <= mid || l >= mid + 1) {
    if (fs)
      move(l, level), move(r, level);
    if (l <= mid)
      ans += query(lson, l, r, level - 1, cl, mid);
    else
      ans += query(rson, l, r, level - 1, mid + 1, cr);
  } else {
    int le = mid, rs = mid + 1;
    if (fs)
      move(l, level), move(le, level), move(rs, level), move(r, level);
    if (l > rs)
      swap(l, rs), swap(le, r);
    ans += query(lson, l, le, level - 1, cl, mid);
    ans += query(rson, rs, r, level - 1, mid + 1, cr);
  }
  return ans;
}

class Solution {
public:
  void solve() {
    int n, q;
    read(n), read(q);
    int R = 1 << n;
    for (int i = 1; i <= R; ++i)
      read(a[i]);
    build(1, 1, R);
    while (q--) {
      int t, x, k, l, r;
      read(t);
      switch (t) {
      case 1:
        read(x), read(k);
        update(1, x, k, n, 1, R);
        break;
      case 2:
        read(k);
        rr ^= (1 << k);
        break;
      case 3:
        read(k);
        ss ^= (1 << (k + 1));
        break;
      default:
        read(l), read(r);
        printf("%lld\n", query(1, l, r, n, 1, R));
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
```

---

## 作者：feecle6418 (赞：0)

E 没调出来竟然还有 rnk 16 /jk

---

比较简单的 Div2 F，有两种做法。**以下解法中下标从 $0$ 开始，不同于题目描述！**

## $O(qn^2)$ 做法

**引理 1**：一次 $swap(x)$ 操作相当于 $rev(x)$ 再 $rev(x+1)$。

**引理 2**：$rev$ 操作的顺序不影响答案。

以上两条引理是显然的，证明略去。

根据以上引理，我们可以维护一个 rev 标记代表每一位是否有 rev 过，每次 rev 操作的时候就让 `rev[x]^=1`，那么查询时 rev 有值即相当于这一位需要 rev 一下。

**引理 3**：对区间 $[i2^k,(i+1)2^k-1]$ 执行的 $rev(x)$ 操作，仅在 $x>k$ 时有效。

**引理 4**：区间 $[i2^k,(i+1)2^k-1]$ 执行 $rev(x)$ 操作（$x>k$）去到的新区间，相当于把两个端点交换，再分别 rev，得到的两个新端点组成的区间。

证明：因为 $x>k$，所以 $rev(x)$ 操作所翻转的区间中一定存在一个恰好包含 $[i2^k,(i+1)2^k-1]$，因此两个端点 rev 后仍然还在这个大区间内。

由引理 $3,4$ 就可以得到查询和的方法：把 $[l,r]$ 拆分成若干个形如 $[i2^k,(i+1)2^k-1]$ 的区间（发现了什么？这就是**线段树**做的事情啊！），然后对每个区间枚举每个有 rev 标记的位分别处理左右端点，最终就能得到另外若干个形如 $[i2^k,(i+1)2^k-1]$ 的区间，对这些区间内的数求和即可。

单点修改就很简单了，先把要改的位置 $x$ rev 回去，单点修改即可。由于需要查询区间和，用树状数组维护即可。

代码：<https://codeforces.ml/contest/1401/submission/90594866>。这里我把 $[l,r]$ 拆成了 $[0,l-1]$ 和 $[0,r]$，再按照二进制位拆分，略不同于上面所说的用线段树拆分。

## $O(qn)$ 做法

拆分出区间后用位运算直接 $O(1)$ 得到新区间。发现查询的和在树状数组上恰好就是 $[i-lowbit(i)+1,i]$ 的形式，因此直接 $O(1)$ 查询即可。

---

