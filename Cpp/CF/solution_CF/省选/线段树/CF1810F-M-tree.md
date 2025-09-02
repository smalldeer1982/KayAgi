# M-tree

## 题目描述

A rooted tree is called good if every vertex of the tree either is a leaf (a vertex with no children) or has exactly $ m $ children.

For a good tree, each leaf $ u $ has a positive integer $ c_{u} $ written on it, and we define the value of the leaf as $ c_{u} + \mathrm{dep}_{u} $ , where $ \mathrm{dep}_{u} $ represents the number of edges of the path from vertex $ u $ to the root (also known as the depth of $ u $ ). The value of a good tree is the maximum value of all its leaves.

Now, you are given an array of $ n $ integers $ a_{1}, a_{2}, \ldots, a_{n} $ , which are the integers that should be written on the leaves. You need to construct a good tree with $ n $ leaves and write the integers from the array $ a $ to all the leaves. Formally, you should assign each leaf $ u $ an index $ b_{u} $ , where $ b $ is a permutation of length $ n $ , and represent that the integer written on leaf $ u $ is $ c_u = a_{b_{u}} $ . Under these constraints, you need to minimize the value of the good tree.

You have $ q $ queries. Each query gives you $ x $ , $ y $ and changes $ a_{x} $ to $ y $ , and after that, you should output the minimum value of a good tree based on the current array $ a $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, after the first query, the current array $ a $ is $ [4,3,4,4,5] $ . We can construct such a good tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1810F/88a3cbbc1b6fe16413368f21af94bcc26c8f2029.png)The first number inside a vertex is its index (in this problem, the indices do not matter, but help to understand the figure). If a vertex is a leaf, the second number inside the vertex is the integer written on it.

We can tell that $ \mathrm{dep}_{3}=\mathrm{dep}_{4}=1,\mathrm{dep}_{5}=\mathrm{dep}_{6}=\mathrm{dep}_{7}=2 $ and the value of the tree, which is the maximum value over all leaves, is $ 5+1=6 $ . The value of leaves $ 5 $ , $ 6 $ , $ 7 $ is also equal to $ 6 $ . It can be shown that this tree has the minimum value over all valid trees.

## 样例 #1

### 输入

```
3
5 3 3
3 3 4 4 5
1 4
2 4
3 5
5 2 4
3 3 4 4 5
1 4
2 5
3 5
4 5
7 3 4
1 2 2 3 3 3 4
1 4
2 1
5 5
6 6```

### 输出

```
6 6 6
7 7 7 8
6 6 6 7```

# 题解

## 作者：luanmenglei (赞：4)

注意到，一个答案 $x$ 可行当且仅当 $\sum_{i=1}^n{m^{a_i}} \leq m^x$。

## 证明

考虑贪心，当答案为 $x$ 时，$a_i$ 一定会被放在 $x-a_i$ 层，这样必然是最优的，那么 $m$ 个放在 $k$ 层的数就会占用一个 $k-1$ 层的位置，这正是 $m$ 进制下的加法进位过程，所以说原序列最优排列下的位置占用情况在 $10$ 进制下正是 $\sum_{i=1}^n{m^{a_i}}$，则恰好有 $x$ 层在 $10$ 进制下就代表着 $m^x$，所以结论成立。

那么也就是说 $x$ 的最小值就是 $\lceil \log_m{\sum_{i=1}^n{m^{a_i}}} \rceil$，所以实际上我们要维护一个数并查询其 $\log_m$ 的值，这个东西可以使用线段树或者珂朵莉树维护。

---

## 作者：__Aaaaaaaa (赞：3)

### 题目大意：
定义一颗树的代价为其所有叶子的权值加深度的最大值。
定义序列 $a$ 的价值为，构造一棵 $m$ 叉树 $T$ 使得 $T$ 的叶子节点的权值为 $a$ 的排列，且树 $T$ 的代价最小。
给定序列 $a$ 和 $q$ 次询问，每次询问给定 $x,y$ 并令 $a_x$=y，求每次修改后序列的价值。

### Solution：
如果只有一个询问怎么做？

二分答案。

根据贪心，对于一个数肯定是尽量往深的层数放，这样分支更多（没有后效性，每个数最深放在哪一层是已知的）

```check``` 函数：
```
bool check(int x){
//x不低于max{a_i},num_i表示i在a中出现的次数
	int d=1;
	for(int i=x;i>=1;--i)
		if(d<num[i])return 0;
		else d=(d-num[i])*m;
	return 1;
}
```
等价于：
```
bool check(int x){
	int d=1;
	for(int i=x;i>=1;--i)
		d=(d-num[i])*m;
	return d>=0;
}
```

于是我们发现，$d=m^x-\sum_{i=1}^x  num_i × m^i$,所以 ```check``` 函数等价于判定 $m^x≥\sum_{i=1}^n  m^{a_i}$。

那么 $ans=\lceil log_m\sum_{i=1}^n m^{a_i} \rceil$，也就是在上式的m进制下的最高位 $+1$。

这时问题变成了使用线段树来维护这样一个 $m$ 进制数。

下面给出详细的代码。

```
#include <iostream>
#include <cstdio>
using namespace std;
const int N=3e5+50,INF=1e9;
struct tree{
	int l,r;
	int Mn,Mx,lazy;//维护：数位在[l,r]的区间内数值的最大和最小值，以及推平用的lazytag 
}tr[N<<2];
void pushup(int u){//pushup操作 
	tr[u].Mn=min(tr[u<<1].Mn,tr[u<<1|1].Mn);
	tr[u].Mx=max(tr[u<<1].Mx,tr[u<<1|1].Mx);
}
void trans(tree &U,int d){//区间推平操作 
	U.lazy=U.Mn=U.Mx=d;
}
void pushdown(int u){//下传lazytag 
	if(~tr[u].lazy){
		trans(tr[u<<1],tr[u].lazy);
		trans(tr[u<<1|1],tr[u].lazy);
		tr[u].lazy=-1;
	}
}
int k,m,num[N];
void build(int u,int l,int r){//用线段树建立k位的m进制数 
	tr[u].l=l,tr[u].r=r,tr[u].lazy=-1;
	if(l==r){
		tr[u].Mn=tr[u].Mx=num[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
int get_nex(int u,int l,int r){//如果第l位的数值+1，求第一个不会进位的数位是哪个，如果超过了r限制则返回-1 
	if(tr[u].Mn==m-1)
		return -1;
	if(tr[u].l==tr[u].r)
		return tr[u].l;
	int mid=tr[u].l+tr[u].r>>1;
	pushdown(u);
	if(mid>=r)return get_nex(u<<1,l,r);
	if(mid<l)return get_nex(u<<1|1,l,r);
	int res=get_nex(u<<1,l,r);
	if(res==-1)
		return get_nex(u<<1|1,l,r);
	return res;
}
int get_las(int u,int l,int r){//如果第l位的数值-1，求第一个不会退位的数位是哪个，如果超过了r限制则返回-1
	if(tr[u].Mx==0)
		return -1;
	if(tr[u].l==tr[u].r)
		return tr[u].l;
	int mid=tr[u].l+tr[u].r>>1;
	pushdown(u);
	if(mid>=r)return get_las(u<<1,l,r);
	if(mid<l)return get_las(u<<1|1,l,r);
	int res=get_las(u<<1,l,r);
	if(res==-1)
		return get_las(u<<1|1,l,r);
	return res;
}
int Max(int u,int l,int r){//数位在[l,r]区间内数值最大的数 
	if(tr[u].l>=l&&tr[u].r<=r)
		return tr[u].Mx;
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1,res=0;
	if(mid>=l)
		res=max(res,Max(u<<1,l,r));
	if(mid<r)
		res=max(res,Max(u<<1|1,l,r));
	return res;
}
int Min(int u,int l,int r){//数位在[l,r]区间内数值最小的数 
	if(tr[u].l>=l&&tr[u].r<=r)
		return tr[u].Mn;
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1,res=0;
	if(mid>=l)
		res=max(res,Min(u<<1,l,r));
	if(mid<r)
		res=max(res,Min(u<<1|1,l,r));
	return res;
}
void modify(int u,int l,int r,int d){
	if(tr[u].l>=l&&tr[u].r<=r){
		trans(tr[u],d);
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	pushdown(u);
	if(mid>=l)modify(u<<1,l,r,d);
	if(mid<r)modify(u<<1|1,l,r,d);
	pushup(u);
}
void del(int x){//当前数-m^x 
	int cnt=Min(1,x,x);
	if(cnt==0){//如果不够减考虑退位 
		int las=get_las(1,x,k);
		modify(1,x,las-1,m-1);
		modify(1,las,las,Min(1,las,las)-1);
	}
	else
		modify(1,x,x,cnt-1);
}
void add(int x){//当前数+m^x
	int cnt=Min(1,x,x);
	if(cnt==m-1){//如果超出则考虑进位 
		int nex=get_nex(1,x,k);
		modify(1,x,nex-1,0);
		modify(1,nex,nex,Min(1,nex,nex)+1);
	}
	else
		modify(1,x,x,cnt+1);
}
int alive(int u){//求最高位 
	if(tr[u].Mx==0)
		return -1;
	if(tr[u].l==tr[u].r)
		return tr[u].l;
	pushdown(u);
	int res=alive(u<<1|1);
	if(res==-1)
		return alive(u<<1);
	return res;
}
int get(){//求log2 的当前数且向上取整 
	int x=alive(1);
	return x+(Max(1,1,x-1)>0);
}
int n,q,w[N];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&q);
		k=n+30;
		for(int i=1;i<=k;i++)
			num[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",w+i);
			num[w[i]]++;
		}
		for(int i=1;i<k;i++)
			num[i+1]+=num[i]/m,num[i]-=num[i]/m*m;//最初的m进制数肯定得考虑进位
		build(1,1,k);//建树
		int x,y;
		while(q--){
			scanf("%d%d",&x,&y);
			del(w[x]),w[x]=y,add(w[x]);//减少m^a[x],加上m^y,并把a[x]的值赋为y 
			printf("%d ",get());
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：i_am_not_feyn (赞：3)

定义根节点为第 $0$ 层，$num_x$ 为 $a$ 中 $x$ 的数量。

贪心可得 $a_i$ 的所在层数为 $x-a_i$，则可知第 $i$ 层的叶子个数为 $num_{x-i}$。

故第 $i$ 层共有 $A_{i}=m(A_{i-1}-num_{x-(i-1)})=m^i-\sum\limits_{j=1}^{i-1}m^{i-j}num_{x-j}$ 个节点，若 $num_{x-i}>A_i$ 则表示该 $x$ 不可行。

故可知当
$$
num_{x-i}\le A_i=m^i-\sum\limits_{j=1}^{i-1}m^{i-j}num_{x-j}
$$
时，$x$ 可行。

对上式进行移项，得：
$$
\sum\limits_{j=0}^{i-1}m^jnum_{x-i+j}\le m^i
$$
再将每个 $a_k$ 的贡献拆开单独算，则有：
$$
\sum\limits_{j=0}^{i-1}\sum_{a_k=x-i+j}m^j=\sum m^{a_k+i-x}\le m^i
$$


两边同乘 $m^{x-i}$ 得 $\sum m^{a_k}\le m^x$，此时 $x$ 可行。

由于 $a_k$ 太大，不能直接二分算，则搬到线段树上做，模拟 $m$ 进制下的加减法即可。

[代码](https://codeforces.com/contest/1810/submission/218010293)。

---

## 作者：Kevin090228 (赞：2)

## M-tree

挺简单一个题，先分析分析怎么求单次询问的答案。

将整棵树补全成满 $m$ 叉树，考察这棵树的叶子个数，就能得出一个充要条件：$\sum m^{a_i}\leq \sum m^{d}$，其中 $d$ 是整棵树的深度，也就是我们要求的答案。

然后用一个支持区间赋值/区间求和操作的线段树维护 $m^{a_i}$ 即可。

时间复杂度 $O(n\log n)$。

---

## 作者：MiniLong (赞：1)

注意到答案应该不会超过 $\max a_i +\log_m{n}$，因为可以构造一个完全 $m$ 叉树。于是考虑枚举答案，然后来验证。设当前答案为 $ans$，显然先搞出来个深度为 $ans$ 的满 $m$ 叉树比较优，然后从后往前枚举值域 $i$，设当前空位为 $x$，每次使得 $x \leftarrow m(x - cnt_i),i\leftarrow i - 1$。若 $x$ 始终 $\ge 0$，那么就可行。考虑线段树维护这个东西，设每个区间要合法初始值最小为 $f_u$，使用最小初始值最后剩下 $g_u$，从 $l$ 到第一个有数值的位置设为 $tr_u$。合并的时候若 $m^{len_{ls} - tr_{ls}}g_{rs} \ge f_{ls}$，那么 $f_u = f_{rs},g_u = g_{ls}+m^{len_{ls}}(g_{rs} - f_{ls})$。否则设 $t=\lceil \dfrac{f_{ls}-m^{len_{ls} - tr_{ls}}g_{rs}}{m^{len_{ls} - tr_{ls}+tr_{rs}}} \rceil$，那么 $f_u = t+f_{rs},g_u = g_{ls} + m^{tr_{ls}}(g_{rs}+t\cdot m^{len_{ls} - tr_{ls}+tr_{rs}}- f_{ls})$。每次单点改即可，复杂度 $\Theta(n\log n)$。

---

## 作者：abruce (赞：1)

考虑在我们已知答案的情况下如何进行贪心。  
设 $\max a_i=mx$，答案为 $mx+D$ 则前 $D-1$ 层我们构造一个满 $k$ 叉树，这样在第 $D$ 层我们就有 $m^D$ 个可用节点。  
对于所有 $a_i=mx$ 的权值，我们必须在这一层将其填入叶子，于是我们消耗了 $mx$ 给叶子节点。  
对于剩下的这些节点，我们可以将其填入没有达到上限的权值也可以将其扩展为非叶子节点。但考虑到所以剩下的权值在下一层都是合法的。所以我们将其扩展可以在下一层得到 $m$ 个可用节点，因此一定更优。  
下一层时，我们必须填入 $a_i=mx-1$ 所有权值，操作方法同上。于是我们按照这个贪心思路进行下去，当有一层可用节点无法满足必须填入的权值时则 $mx+D$ 这个答案一定非法，否则合法。  

考虑如何快速维护这个贪心。若我们在权值的序列上去考虑这件事，那么则是从右往左进行，每次传下去的只有当前可用节点数。  
所以我们考虑开一棵权值线段树，每个点维护两个值 $rv,lv$ 代表能够合法地通过这个权值区间至少要从右边传过来多少可用节点和在此情况下最终剩余多少可用节点。  
叶子节点信息很好求，考虑如何合并信息。对于两个区间，右区间会有 $r_{lv}\times m$ 给节点传到左区间。  
如果它大于左区间 $l_{rv}$ 则右区间无需为左区间补值，大区间 $rv$ 即为 $r_{rv}$，$lv$ 即为 $l_{lv}$ 加上右区间传下来溢出的值造成的可用节点数增加，即 $(r_{lv}\times m-l_{rv})^{l_{len}-1}$。  
如果它小于 $l_{rv}$ 则大区间为满足左区间需要补值，由于从最右端开始添加，所以需要补 $\left\lceil\dfrac{l_{rv}-r_{lv}\times m}{m^{r_{len}}}\right\rceil$ 个可用节点。  
用一棵线段树维护这些信息，最后查询 $[1,mx]$ 区间需要多少可用节点即可。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9') {
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
    return x*f;
}
namespace tokidosaya {
#define lc id<<1
#define rc id<<1|1
    const int maxn=2e5+5;
    const ll inf=2e5+3;
    int n,c[maxn],a[maxn],Q,T,m;
    ll pw[maxn];
    struct node {
        int len;
        ll lv,rv;
        node() {}
        node(int len,ll lv,ll rv) {
            this->len=len,this->lv=lv,this->rv=rv;
        }
        friend node operator+(const node a,const node b) {
            node c;
            c.len=a.len+b.len;
            if(a.rv<=b.lv*m)c.rv=b.rv,c.lv=min(inf,a.lv+min(b.lv*m-a.rv,inf)*pw[a.len-1]);
            else if(pw[b.len]==inf)c.rv=b.rv+1,c.lv=inf;
            else c.rv=b.rv+(a.rv-b.lv*m+pw[b.len]-1)/pw[b.len],c.lv=min(inf,a.lv+min((c.rv-b.rv)*pw[b.len]+b.lv*m-a.rv,inf)*pw[a.len-1]);
            return c;
        }
    };
    struct tree {
        int l,r,mid,sum;
        node d;
    } t[maxn*4];
    void pushup(int id) {
        t[id].sum=t[lc].sum+t[rc].sum,t[id].d=t[lc].d+t[rc].d;
    }
    void build(int id,int l,int r) {
        t[id]=(tree) {
            l,r,l+r>>1,0,node(r-l+1,0,0)
        };
        if(l==r)return t[id].d.rv=t[id].sum=c[l],void();
        int mid=l+r>>1;
        build(lc,l,mid),build(rc,mid+1,r);
        pushup(id);
    }
    void add(int id,int v,int k) {
        if(t[id].l==t[id].r)return c[v]+=k,t[id].d.rv+=k,t[id].sum+=k,void();
        add(v<=t[id].mid?lc:rc,v,k);
        pushup(id);
    }
    node ask(int id) {
        if(t[id].l==t[id].r)return t[id].d;
        if(t[rc].sum)return t[lc].d+ask(rc);
        else return ask(lc);
    }
    int main() {
        int x,y,cas=0;
        T=read();
        while(T--) {
            n=read(),m=read(),Q=read(),pw[0]=1;
            for(int i=1; i<=n; i++)a[i]=read(),c[i]=0,pw[i]=min(inf,pw[i-1]*m);
            for(int i=1; i<=n; i++)c[a[i]]++;
            build(1,1,n);
            while(Q--) {
                x=read(),y=read(),cas++;
                if(n==1) {
                    printf("%d\n",y);
                    continue;
                }
                add(1,a[x],-1),add(1,a[x]=y,1);
                node d=ask(1);
                int ans=1;
                while(pw[ans]<d.rv)ans++;//答案大小只有 logn 级别 
                printf("%d\n",ans+d.len);
            }
        }
        return 0;
    }
}
int main() {
    return tokidosaya::main();
}
```

---

## 作者：_lfxxx_ (赞：0)

考虑单次解答用二分答案。

设二分答案 $lim$，起始我们有个计数器，表示当前有多少个叶子结点。 

然后从大往小扫，当前叶子个数减去 $cnt_x$ 个，然后乘以 $m$ 为下次做准备。

不合法就是中间计数器为负数了。

可以发现中间出现负数就是结果出现负数，那我们只用看最后结果。

那么实际上我们就是判定 $m^{lim}-\sum_i cnt_i \times m^i$，那么答案就是 $\lceil \log_m \sum_{i=1}^n m^{a_i} \rceil$、

那么我们用线段树模拟 $m$ 进制就可以了，只需要支持区间加，区间 $\max$，查询从某个位置 $p$ 开始最长 $0$ 和 $m-1$段。这个用线段树二分即可。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define i128 __int128
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
bool be;
constexpr int N = 2e5 + 25;
int n, m, q, a[N];
struct seg {
	#define ls k << 1
	#define rs k << 1 | 1
	int mx[N << 2], mn[N << 2], tag[N << 2];
	void clear()
	{
		for (int i = 0; i <= (n + 20) << 2; ++i) tag[i] = mx[i] = mn[i] = 0; 
	}
	void push_up(int k)
	{
		mx[k] = max(mx[ls], mx[rs]), mn[k] = min(mn[ls], mn[rs]);
	}
	void push(int k, int v)
	{
		mx[k] += v, mn[k] += v;
		tag[k] += v;
	}
	void push_down(int k)
	{
		if (tag[k]) {
			push(ls, tag[k]);
			push(rs, tag[k]);
			tag[k] = 0;
		}
	}
	void add(int L, int R, int v, int k = 1, int l = 1, int r = n + 20)
	{
		if (L <= l && r <= R) {
			push(k, v);
			return;
		}
		push_down(k);
		int mid = l + r >> 1;
		if (L <= mid) add(L, R, v, ls, l, mid);
		if (R > mid) add(L, R, v, rs, mid + 1, r);
		push_up(k);
	}
	int qmax(int L, int R, int k = 1, int l = 1, int r = n + 20)
	{
		if (L <= l && r <= R) return mx[k];
		push_down(k);
		int mid = l + r >> 1, ans = 0;
		if (L <= mid) ans = max(ans, qmax(L, R, ls, l, mid));
		if (R > mid) ans = max(ans, qmax(L, R, rs, mid + 1, r));
		return ans;
	}
	int qmin(int L, int R, int k = 1, int l = 1, int r = n + 20)
	{
		if (L <= l && r <= R) return mn[k];
		push_down(k);
		int mid = l + r >> 1, ans = INT_MAX;
		if (L <= mid) ans = min(ans, qmin(L, R, ls, l, mid));
		if (R > mid) ans = min(ans, qmin(L, R, rs, mid + 1, r));
		return ans;
	}
	int getmx(int k = 1, int l = 1, int r = n + 20)
	{
		if (l == r) return l;
		push_down(k);
		int mid = l + r >> 1;
		if (mx[rs]) return getmx(rs, mid + 1, r);
		return getmx(ls, l, mid);
	}
	int qr0(int p, int k = 1, int l = 1, int r = n + 20)
	{
		if (p <= l && mx[k] == 0) return r;
		if (l == r) return -1;
		push_down(k);
		int mid = l + r >> 1;
		if (p <= mid) {
			int ans = qr0(p, ls, l, mid);
			if (ans == mid) {
				return max(ans, qr0(p, rs, mid + 1, r));
			} else {
				return ans;
			}
		}
		return qr0(p, rs, mid + 1, r);
	}
	int qrm(int p, int k = 1, int l = 1, int r = n + 20)
	{
		if (p <= l && mn[k] == m - 1) return r;
		if (l == r) return -1;
		push_down(k);
		int mid = l + r >> 1;
		if (p <= mid) {
			int ans = qrm(p, ls, l, mid);
			if (ans == mid) {
				return max(ans, qrm(p, rs, mid + 1, r));
			} else {
				return ans;
			}
		}
		return qrm(p, rs, mid + 1, r);
	}
}tr;
void add(int x)
{
	int id = tr.qrm(x);
	if (id == -1) {
		tr.add(x, x, 1);
	} else {
		tr.add(x, id, -(m - 1));
		tr.add(id + 1, id + 1, 1);
	}
}
void del(int x)
{
	int id = tr.qr0(x);
	if (id == -1) {
		tr.add(x, x, -1);
	} else {
		tr.add(x, id, m - 1);
		tr.add(id + 1, id + 1, -1);
	}
}
int solve()
{
	int up = tr.getmx();
	return up + (up > 1 ? tr.qmax(1, up - 1) > 0 : 0);
}
bool en;
int main()
{
	cerr << (&be - &en) / 1024.0 / 1024 << " MBs\n--------------------------------" << endl;
#ifdef IAKIOI
	freopen("in.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m >> q;
		tr.clear();
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			add(a[i]);
		}
		while (q--) {
			int x, y;
			cin >> x >> y;
			del(a[x]);
			add(a[x] = y);
			cout << solve() << ' ';
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Richard_Whr (赞：0)

# M-tree

一种不需要线段树的做法

> **题意**：定义一颗树的代价为其所有叶子的权值加深度的最大值。 定义序列 $a$ 的价值为，构造一棵 $m$ 叉树 $T$ 使得 $T$ 的叶子节点的权值为 $a$ 的排列，且树 $T$ 的代价最小。
给定序列 $a$ 和 $q$ 次询问，每次询问给定 $x,y$ 并令 $a_x=y$，求每次修改后序列的价值。

首先不考虑有修改，在给定所有的 $a$ 之后，将 $a$ 分配给叶子，求权值加深度的最小值。

从贪心的角度出发，我们一定是希望比较大的 $a$ 在深度比较小的位置。

设树高为 $d$，根节点深度为 $0$，初始的时候树上就有 $M^d$ 个节点。

假设我们要在从上往下第 $i$ 层安排一个叶子，他下面的节点就都无法使用了，使得树的节点个数 $-M^{dep-i}$

通过二分具体化后抽象建模或者是~~找规律~~都可以发现询问的本质是：

#### 求一个最小的 $x$ 使得 $M^x \ge \sum\limits_{i=1}^{n} M^{a_i}$

使用 Trygub Num 维护这个 $M$ 进制数。

简单介绍一下这种科技：

 - 支持 $+ a\times B^x$
 
 - 支持查询某一位上的数

将 $B$ 进制的每一位值域从原来的 $[0,B)$，扩展到 $(-B,B)$。

这样的好处是我们每次往前进位的时候就只需要将该位置留下除以 $B$ 向 $0$ 取整的数即可，容易发现这样可以在 $log_{B}V$ 的复杂度内将 $a$ 的范围降到 $(-B,B)$，

考虑这个时候的进位情况，不幸的是有的时候会发生连锁反应，就是一直进位。

具体分析这样进位的情形：此时给上一位的进位只有 $1,-1$，那么上一位当且仅当是 $B-1$ 的时候（可以是负的），才会发生连锁反应继续进位。称这样的位置是临界位置，那么发生一次连锁反应会消耗一个临界位置。

临界位置的来源又有那些呢，发现在降低 $a$ 的值域的时候，最多会产生 $log_BV$ 个临界位置，连锁反应的最后一步最多会产生一个临界位置。

临界位置总数并不多！因此是均摊正确的！！

考虑这个题，只会对某一位 $+1$ 或者 $-1$ ，因此产生的临界位置数量是线性级别的。

### 最后如何求答案呢？

分类讨论一下：

取出最高位，设是 $x$ 位，如果 $>1$，那么没什么好说的，只能取 $x+1$ 才行。

否则考虑他的下一个非 $0$ 位置 $y$，如果该位上 $>0$ 则也只能取 $x+1$

否则考虑到后面需要前面退位，如果 $x$ 与 $y$ 不相邻，退位至少两次一定可以将后面所有数都变为正的，取 $x$ 即可。

如果相邻，则不一定可以保证将后面所有数都变为正的，继续退位，发现这个过程如果持续进行的话仍是在消耗临界位置，不改变均摊分析。

持续进行上述的过程，如果说变成最低位了或者是当前数位上的数 $>1$ 了，结束并按照分讨结果输出即可。

参考资料：[https://www.luogu.com.cn/article/2iz5xyfm](https://www.luogu.com.cn/article/2iz5xyfm)，[CF原文](https://codeforces.com/blog/entry/115626)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N];
int B;
struct Trygub_num
{
	map<int,int> Map;
	void add(int a,int b)
	{
		while(true)
		{
			if(!a) break;
			auto &it=Map[b];
			it+=a,a=it/B,it-=a*B;
			if(!it) Map.erase(b);
			b++; 
		}
	}
	void init()
	{
		Map.clear();
	}
	int query()
	{
		auto it=Map.end();it--;
		while(it!=Map.begin()&&it->second<=1)
		{
			auto x=prev(it);
			if(x->second>0) break;
			if(x->first!=it->first-1) return it->first;
			x->second+=B;
			Map.erase(it);
			it=x;
		} 
		if(it==Map.begin()) return it->first;
		return it->first+1;
	}
}Num;
int n,T,q;

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); 
	cin>>T;
	while(T--)
	{
		cin>>n>>B>>q;
		Num.init();
		for(int i=1;i<=n;i++) cin>>a[i],Num.add(1,a[i]);
		while(q--)
		{
			int x,y;
			cin>>x>>y;
			Num.add(-1,a[x]);
			Num.add(1,a[x]=y);
			cout<<Num.query()<<" ";
		} 
		cout<<"\n";
	}
	
	return 0;
}
```

---

## 作者：intel_core (赞：0)

首先不难想到二分答案。

```cpp
bool check(int x){
	int cur=1;
	for(int i=x;i>=0;i--){
		if(cnt[i]>cur)return 0;
   		cur=(cur-cnt[i])*m;
	}
	return 1;
}

```

注意到二分答案时的判句相当于判断 $\sum m^{a_i}$ 与 $m^x$ 的大小关系，于是考虑用线段树维护 $m$ 进制的加减法。

因为加或者减的都是 $m$ 的方幂，当加或者减需要判断进/借位时，相当于就是线段树上二分。

所以只需要实现一个区间赋值，二分查第一个 $\ge 0$ 的数，单点加的线段树即可。

---

## 作者：hgzxwzf (赞：0)

## CF1810F

求最大值的最小值，想到二分答案 $x$，考虑判断 $x$ 是否合法。

需要构造出对于任何一个叶子 $i$，$a_i+dep_i\le x$，即 $dep_i\le x-a_i$。

贪心地，将 $i$ 放在第 $x-a_i$ 层（从 $0$ 开始编号）。设一个在第 $i$ 层的叶子的权值为 $\frac{1}{m^i}$，发现所有叶子的权值之和始终等于 $1$，一个点成为一个叶子就相当于它不能再分了，不妨将总权值减去 $\frac{1}{m^i}$。所以需要满足 $1-\sum_{i=1}^n\frac{1}{m^{x-a_i}}\ge 0$，化简得到 $\sum_{i=1}^nm^{a_i}\le m^x$。

用 $\verb!set<int>!$ 维护 $m$ 进制数，容易去掉二分，时间复杂度 $O(q\log_2m)$。

[代码](https://codeforces.com/contest/1810/submission/208706346)。



---

