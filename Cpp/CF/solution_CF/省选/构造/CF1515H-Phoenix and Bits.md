# Phoenix and Bits

## 题目描述

Phoenix loves playing with bits — specifically, by using the bitwise operations AND, OR, and XOR. He has $ n $ integers $ a_1, a_2, \dots, a_n $ , and will perform $ q $ of the following queries:

1. replace all numbers $ a_i $ where $ l \le a_i \le r $ with $ a_i $ AND $ x $ ;
2. replace all numbers $ a_i $ where $ l \le a_i \le r $ with $ a_i $ OR $ x $ ;
3. replace all numbers $ a_i $ where $ l \le a_i \le r $ with $ a_i $ XOR $ x $ ;
4. output how many distinct integers $ a_i $ where $ l \le a_i \le r $ .

For each query, Phoenix is given $ l $ , $ r $ , and $ x $ . Note that he is considering the values of the numbers, not their indices.

## 说明/提示

In the first example:

- For the first query, $ 2 $ is replaced by $ 2 $ AND $ 2 = 2 $ and $ 3 $ is replaced with $ 3 $ AND $ 2 = 2 $ . The set of numbers is $ \{1, 2, 4, 5\} $ .
- For the second query, there are $ 3 $ distinct numbers between $ 2 $ and $ 5 $ : $ 2 $ , $ 4 $ , and $ 5 $ .
- For the third query, $ 2 $ is replaced by $ 2 $ XOR $ 3 = 1 $ , $ 4 $ is replaced by $ 4 $ XOR $ 3 = 7 $ , and $ 5 $ is replaced by $ 5 $ XOR $ 3 = 6 $ . The set of numbers is $ \{1, 6, 7\} $ .
- For the fourth query, there are $ 2 $ distinct numbers between $ 1 $ and $ 6 $ : $ 1 $ and $ 6 $ .
- For the fifth query, $ 1 $ is replaced by $ 1 $ OR $ 8 = 9 $ . The set of numbers is $ \{6, 7, 9\} $ .
- For the sixth query, there is one distinct number between $ 8 $ and $ 10 $ : $ 9 $ .

## 样例 #1

### 输入

```
5 6
5 4 3 2 1
1 2 3 2
4 2 5
3 2 5 3
4 1 6
2 1 1 8
4 8 10```

### 输出

```
3
2
1```

## 样例 #2

### 输入

```
6 7
6 0 2 3 2 7
1 0 4 3
2 6 8 4
4 0 7
3 2 5 3
1 0 1 2
4 0 3
4 2 7```

### 输出

```
5
1
2```

# 题解

## 作者：洛苡hh (赞：9)

区间与，或，异或，求区间不同数个数。考虑使用 0-1trie 解决，不妨将其视为一棵动态开点权值线段树，感觉理解和编码都更为容易一点。

观察到 xor 具有很好的性质，进行操作之后对不同元素数量并没有影响，但 and 和 or 都可能改变不同元素数，并且 xor 是相对较好维护的，只需要在对应位上交换左右子树即可。我们考虑尽量把其他操作简化。

为了方便操作，我们把需要操作的区间 split 出来，对这棵子树进行全局操作，之后再 merge 回去。不然后续分讨起来很麻烦。

先说一下 xor 怎么维护，我们可以直接打一个 tag 表示子树对应深度上是否需要交换，这个标记是容易进行合并的。

考虑 and 可以用取反和 or 代替，具体而言 $x \And y = ((x \oplus O) \mid (y \oplus O)) \oplus O$ 其中 $O=2^{20}-1$，那么接下来只需要考虑 or 操作即可。

考虑 or 操作，我们分类讨论：

1. 空结点，直接 return。

2. 只有右子树，没有影响。

3. 只有左子树，把左子树直接放到右子树位置上即可

4. 又有左子树又有右子树。相当于要把左子树合并到右子树上去。

2，3 操作相当于对只有左子树的位上进行了一次 xor ，直接按照上述方法打 tag 即可。4 操作相当于一次线段树合并，复杂度是一只 log 的。那么问题来了，我们如何知道哪些结点进行哪个操作呢？总不能暴力的遍历一遍整棵树吧，那不是炸飞了。

我们维护两个标记 L，R 表示该结点子树内对应深度上有/无左，右儿子。如果该位被 or 操作了且既有左儿子还有右儿子，那么做操作 4 并继续往下递归，否则直接做 2，3 操作并 return。

简单分析一下这样做的复杂度，每次合并操作都会减少一个结点，最初结点总数为 $O(n \log V)$，而定位到一个需要合并的结点最多需要 $O(\log V)$ 的代价（从根一路找下来），那么一共是 $O(n \log^2 V)$ 的复杂度。

权值线段树写法感觉比直接 0-1trie 好写，[这篇题解](https://www.cnblogs.com/ac-evil/p/14745498.html)码风很不错，注意 trie 是边权不是点权，下面放一个带注释的代码：

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
#define mod 998244353
#define ls t[k].lc
#define rs t[k].rc 
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<'\n'
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
using namespace std;

inline int read(){
    int x=0;
    int f=1;
    char c=getchar();
    while(c<'0' || c>'9'){
    	if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0' && c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}

bool M1;
int n,q;
int a[MAXN];
int rt,nw,tot;
const int O=(1<<20)-1;
const int logV=19;
struct node{
	int lc,rc;
	int L,R,sz,tag;//对应深度是否有左/右儿子，叶子数量（不同数数量），对应深度的xor标记 
}t[MAXN*50];

void pushtag(int k,int dep,int v){
	if(v&(1<<dep)){
		swap(ls,rs);
	}
	int tl=t[k].L,tr=t[k].R;
	t[k].L=(tl&(v^O))|(tr&v);//没有被交换的左儿子和被交换了的右儿子 组成新的左儿子 
	t[k].R=(tl&v)|(tr&(v^O));//同理 
	t[k].tag^=v;
}

void pushup(int k){
	t[k].L=t[ls].L|t[rs].L;
	t[k].R=t[ls].R|t[rs].R;
	t[k].sz=t[ls].sz+t[rs].sz;
}

void pushdown(int k,int dep){
	if(t[k].tag){
		pushtag(ls,dep-1,t[k].tag);
		pushtag(rs,dep-1,t[k].tag);
		t[k].tag=0;
	}
}

void insert(int &k,int dep,int v){
	if(!k) k=++tot;
	if(dep<0){
		t[k].sz=1;
		t[k].L=v^O; 
		t[k].R=v;
		return;
	}
	if(!(v&(1<<dep))) insert(ls,dep-1,v);
	else insert(rs,dep-1,v);
	pushup(k);
}

void split(int k,int &x,int &y,int l,int r,int dep,int L,int R){
	if(!k) return;
	if(l>=L && r<=R){
		y=x;//把要操作的区间从线段树上挖出来 
		x=0;
		return;
	}
	y=++tot;
	pushdown(k,dep);
	int mid=(l+r)>>1;
	if(mid>=L) split(ls,t[x].lc,t[y].lc,l,mid,dep-1,L,R);
	if(mid<R) split(rs,t[x].rc,t[y].rc,mid+1,r,dep-1,L,R);
	pushup(x);
	pushup(y);
}

void merge(int &k,int x,int y,int dep){
	if(!x || !y){
		k=x+y;
		return;
	}
	if(dep<0) return;//一定要判一下深度，调了好久，因为叶子结点储存着结点信息，把它pushup之后这些信息就没了 
	pushdown(x,dep);
	pushdown(y,dep);
	merge(ls,t[x].lc,t[y].lc,dep-1);
	merge(rs,t[x].rc,t[y].rc,dep-1);
	pushup(k);
}

void update_xor(int k,int dep,int v){
	pushtag(k,dep,v);
}

void update_or(int &k,int dep,int v){
	if(!k) return;
	if(dep<0) return; 
	if(!((t[k].L&t[k].R)&v)){//or操作的位上没有左右儿子双全的 
		pushtag(k,dep,t[k].L&v);//对操作位上只有左儿子的结点做xor把他们交换到右儿子上 
		return;
	}
	pushdown(k,dep);
	if(v&(1<<dep)){
		pushtag(ls,dep-1,1<<dep);
		//这个pushtag的作用是修改L，R 把合并后消失的这个左儿子去掉
		//由于tag只会下放，在dep-1层打上一个1<<dep的tag是没有影响的 
		merge(rs,rs,ls,dep-1);
		ls=0;
	}
	update_or(ls,dep-1,v);
	update_or(rs,dep-1,v);
	pushup(k);
}

void update_add(int k,int dep,int v){
	update_xor(k,dep,O);
	update_or(k,dep,v^O);
	update_xor(k,dep,O);
}

bool M2;

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int Time=clock();
	n=read();q=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		insert(rt,logV,a[i]);
	}
	int op,l,r,v;
	while(q--){
		op=read();
		l=read();r=read();
		nw=0;
		split(rt,rt,nw,0,O,logV,l,r);
		if(op==1){
			v=read();
			update_add(nw,logV,v);
		}else if(op==2){
			v=read();
			update_or(nw,logV,v);
		}else if(op==3){
			v=read();
			update_xor(nw,logV,v);
		}else{
			int ans=t[nw].sz;
			printf("%d\n",ans);
		}
		merge(rt,rt,nw,logV);
	}
	look_memory;
	look_time;
	return 0;
}
```

---

## 作者：Butterfly_qwq (赞：5)

前情提要：[以前写的题解](/article/e0r2mr3a)。

两个月后重看这道题。

机房同学说我的题解看着很难受，所以再来写一篇。

---

考虑把每个树建出 0-1 trie。

与操作可以转换为或操作和取反操作，而取反操作是异或 $2^{20}-1$，所以与操作就不用考虑了。

考虑区间做这个东西是困难的，那么可以 split 出来，然后做完操作再 merge 回去。

现在先考虑较为容易的异或操作。

明显的是异或操作是可以合并的，所以我们可以全局打懒标记，需要下传的时候（合并到这个节点时、分裂到这个节点时、查询到这个节点时）就下传标记，下传的时候如果这一位是 $1$ 那么就交换左右儿子。

那么考虑比较难做的或操作。

考虑或操作的本质是将左儿子并入右儿子中，如果是只有左儿子则将左儿子转为右儿子，如果是右儿子则不变（如果该位是 1）。

那么或操作也未尝不可打标记！具体的，我们可以直接对或操作对根节点打一个标记，同样是合并时下传。

下传的时候存在如下五种情况：

1. 该位置是 $1$ 且有两个儿子。此时直接调用 merge 把左儿子合并，然后把标记给右儿子，要去掉最高位。
2. 该位置是 $1$ 且只有左儿子。把左儿子变成右儿子，然后把标记给右儿子，要去掉最高位。
3. 该位置是 $1$ 且只有右儿子。直接把去掉最高位的标记放到右儿子上。
4. 该位置是 $1$ 且没有儿子。不用管。
5. 该位置是 $0$。把标记放到左右儿子上。

然后就做完了。

[评测记录](https://codeforces.com/contest/1515/submission/293812818)。

---

## 作者：Butterfly_qwq (赞：5)

第一次不通过题解做出来 CF *3500，写篇题解纪念一下。

容易看出来是 0-1 trie 的题，于是我们 0-1 trie。

每次对一个区间操作可以把对应区间 split 出来，然后就变成了全局操作。

由于 $a\&b=\sim(a|(\sim b))$，$\sim a=a\oplus (2^{20}-1)$，所以 $\&$ 操作就没了。

$\oplus$ 操作是好做的，因为标记可以合并，直接打上标记就行了。

考虑较为难做的 $|$ 操作。如果一位为 $1$，相当于把这一层的左子树 merge 到右子树上。但是需要将左子树整体异或一个 $2^{dep}$，否则最高位不统一会寄。

为了判断我们什么时候能合并，我们需要额外记录一层是否有左右儿子，因为只有左右儿子全不为空且对应位为 $1$ 才能将左子树合并到右子树。

复杂度是两只老哥的。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+5;
int n,q,rt,idx,lc[N],rc[N],lazy[N],tagl[N],tagr[N],ucnt[N];
void pushup(int u)
{
	ucnt[u]=ucnt[lc[u]]+ucnt[rc[u]];
	tagl[u]=tagl[lc[u]]|tagl[rc[u]];
	tagr[u]=tagr[lc[u]]|tagr[rc[u]];
}
void pushtag(int u,int w,int dep)
{
	if(w&(1<<dep))swap(lc[u],rc[u]);
	int l=tagl[u],r=tagr[u];
	tagl[u]=(l&(w^1048575))|(r&w);
	tagr[u]=(r&(w^1048575))|(l&w);
	lazy[u]^=w;
}
void pushdown(int u,int dep)
{
	if(!lazy[u])return;
	pushtag(lc[u],lazy[u],dep-1);
	pushtag(rc[u],lazy[u],dep-1);
	lazy[u]=0;
}
void split(int &u,int &v,int l,int r,int L,int R,int dep)
{
	if(!u)return;
	if(r<L||l>R)return;
	if(L<=l&&r<=R){v=u;u=0;return;}
	int mid=l+r>>1;
	pushdown(u,dep);v=++idx;
	split(lc[u],lc[v],l,mid  ,L,R,dep-1);
	split(rc[u],rc[v],mid+1,r,L,R,dep-1);
	pushup(u);pushup(v);
}
void merge(int &u,int v,int dep)
{
	if(!u||!v){u|=v;return;}
	if(dep==-1)return;
	pushdown(u,dep);
	pushdown(v,dep);
	merge(lc[u],lc[v],dep-1);
	merge(rc[u],rc[v],dep-1);
	pushup(u);
}
void insert(int &u,int w,int dep)
{
	if(!u)u=++idx;
	if(dep==-1)
	{
		tagl[u]=w^1048575;
		tagr[u]=w;ucnt[u]=1;
		return;
	}
	if(w&(1<<dep))insert(rc[u],w,dep-1);
	else          insert(lc[u],w,dep-1);
	pushup(u);
}
void update(int &u,int w,int dep)
{
	if(dep==-1||!u)return;
	if(!(w&tagl[u]&tagr[u]))
	{
		pushtag(u,w&tagl[u],dep);
		return;
	}
	pushdown(u,dep);
	if(w&(1<<dep))
	{
		pushtag(lc[u],1<<dep,dep-1);
		merge(rc[u],lc[u],dep-1);
		lc[u]=0;
	}
	update(lc[u],w,dep-1);
	update(rc[u],w,dep-1);
	pushup(u);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=1,a;i<=n;i++)
	{
		cin>>a;
		insert(rt,a,19);
	}
	for(int i=1,op,l,r,w,u;i<=q;i++)
	{
		cin>>op>>l>>r;u=0;
		split(rt,u,0,1048575,l,r,19);
		if(op==1)
		{
			cin>>w;
			pushtag(u,1048575,19);
			update(u,w^1048575,19);
			pushtag(u,1048575,19);
		}
		if(op==2)
		{
			cin>>w;
			update(u,w,19);
		}
		if(op==3)
		{
			cin>>w;
			pushtag(u,w,19);
		}
		if(op==4)cout<<ucnt[u]<<'\n';
		merge(rt,u,19);
	}
}
```

---

## 作者：丛雨 (赞：4)

## CF1515H Phoenix and Bits

> 题意:初始有大小$n$的集合$a(a_i\in [0,2^{20}))$.4种操作，分别为将**值**在[x,y]的数按位异或($\oplus$)/按位或($|$)/按位于($\And$)上$x$.每次查询值域内不同的数个数.
>
> $1\leq n\leq 2\times 10^5$,查询和询问总数不超过$10^5$

我们先建出$\tt trie$树，每次$a_i\And x=U\oplus((a_i\oplus U)|(x\oplus U))$,$U$为全集，本题中为$2^{20}-1$

这样就只剩下$\oplus$和$|$了

我们考虑每次操作时暴力提取出$\tt trie$树上的区间进行操作，再合并回去，类似于非旋$\tt Treap$

当然，直接这样肯定是会T的，考虑优化

#### 1.$\oplus$操作进行懒标记

我们可以知道，$\oplus$只会交换$\tt trie$树上的兄弟节点，不会涉及合并，且具有可加性，所以可以加上懒标记，当访问子节点时再下放

#### 2.在递归子树操作过程中，当子树无法被按位或合并节点时则退出

简单地说，就是如果我们要对子树$u$进行按位或$x$时，若$u$的后代中每个节点要么不会被按位或修改，要么没有兄弟，则在此点上打上异或标记，退出

因为会被异或标记修改的位不会有兄弟，所以不涉及合并，此时的按位或和部分位的按位异或是等效的

至于实现则可以记录下子树中所有数的按位或以及其补集的按位或，修改时分类讨论下即可



加了如上优化后，时间复杂度就变成了$O(n\log^2n)$

我们定义势能函数$\Psi$为$\tt trie$树中节点个数，初始时$\Psi=O(n\log n)$

异或只在提取出的树根上操作，势能函数不变，异或花费1，势能函数减少0

设按位或操作在深度为$k$一层退出过$\zeta_k$个节点，则说明其与其兄弟节点会合并，势能函数最少减小$\Delta \Psi=\sum\frac{\zeta_k}{2}$,花费$\sum\zeta_kk=O((\sum\zeta_k)\log n)$，均摊时间复杂度$O(\log n)$ 

每次提取操作新增$O(\log n)$个,故$\Psi_{\max}=O(n\log n)$

所以时间复杂度为$O(n\log^2 n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
int s,q;
const int Depth=19;
struct node;
int size(node*);
int True(node*);
int False(node*);
struct node{
	node *l,*r;
	int _xor,s,k,or_0,or_1;//ORsum of the space of 0/1 
	node(int d){l=r=NULL;_xor=0;s=0;k=d;or_0=0;or_1=0;}
	node(node *l_,node *r_,int d){
		l=l_;r=r_;s=0;or_0=0;or_1=0;k=d;
		if(l_){l_->down();
			s+=l_->s;
			or_0|=1<<k|l->or_0;
			or_1|=l->or_1;
		}if(r_){r_->down();
			s+=r_->s;
			or_0|=r->or_0;
			or_1|=1<<k|r->or_1;
		}if(!~d)s=1;
		_xor=0;
	}
	void down(){
		if(!_xor)return;
		if(_xor>>k&1){
			swap(l,r);
			if((or_0^or_1)&(1<<k))or_0^=1<<k,or_1^=1<<k; 
			_xor^=1<<k;
		}
		if(l)l->_xor^=_xor;
		if(r)r->_xor^=_xor;
		int u=(or_0^or_1)&_xor;
		or_0^=u;or_1^=u;
		_xor=0;
	}
	void up(){
		s=0;or_0=0;or_1=0;
		if(l){l->down();
			s+=l->s;
			or_0|=1<<k|l->or_0;
			or_1|=l->or_1;
		}if(r){r->down();
			s+=r->s;
			or_0|=r->or_0;
			or_1|=1<<k|r->or_1;
		}if(!~k)s=1;
		_xor=0;
	}
}*root;
int size(node *x){return x?x->s:0;}
int True(node *x){return x?x->down(),x->or_1:0;}
int False(node *x){return x?x->down(),x->or_0:0;}
void insert(node *&x,int v,int d=Depth){
	if(!x)x=new node(d),++x->s;
	if(!~d)return;
	if(v>>d&1)insert(x->r,v,d-1);
	else insert(x->l,v,d-1);
	x->up();
}
node* merge(node *x,node *y){
	if(!x||!y)return x?x:y;
	x->down();y->down();
	x->l=merge(x->l,y->l);
	x->r=merge(x->r,y->r);
	x->up();delete y;
	return x; 
}
typedef pair<node*,node*> Homology;
Homology split(node *x,int n){
	if(n<0)return Homology(NULL,x);
	if(!x)return Homology(NULL,NULL);
	if(!~x->k)return Homology(x,NULL);
	Homology y;x->down();
	node *z=NULL;
	if(n>>x->k&1){
		y=split(x->r,n);
		y=Homology(new node(x->l,y.first,x->k),new node(NULL,y.second,x->k));
	}else{
		y=split(x->l,n);
		y=Homology(new node(y.first,NULL,x->k),new node(y.second,x->r,x->k));
	}
	delete x;
	return y;
}
void trie_or(node *&x,int n){
	if(!x)return;
	if(!~x->k)return;
	x->down();
	if(!(n&x->or_0&x->or_1)){
		x->_xor^=n&x->or_0;
		return;
	}
	trie_or(x->l,n&~(1<<x->k));
	trie_or(x->r,n&~(1<<x->k));
	if(n>>x->k&1){
		x->r=merge(x->l,x->r);
		x->l=NULL;
	}
	x->up();
}
void Mtrie_or(node *&x,int n){
	if(!x)return;
	if(!~x->k)return;
	x->down();
	if(n>>x->k&1){
		x->r=merge(x->l,x->r);x->l=NULL;
		Mtrie_or(x->r,n^(1<<x->k));x->up();return;
	}else Mtrie_or(x->l,n),Mtrie_or(x->r,n),x->up();
}
void trie_xor(node *&x,int n){
	if(!x)return;
	x->down();
//	printf("-->%d\n",x->or_0);
	x->_xor^=n;
}
void Mtrie_xor(node *&x,int n){
	if(!x)return;
	if(!~x->k)return;
	x->down();
	if(n>>x->k&1){
		swap(x->l,x->r);
		Mtrie_xor(x->l,n);
		Mtrie_xor(x->r,n);
		x->up();
	}else Mtrie_xor(x->l,n),Mtrie_xor(x->r,n),x->up();
}
int main(){
	s=read;q=read;
	for(int i=1;i<=s;++i)insert(root,read);
	for(int i=1;i<=q;++i){
		int type=read,l=read,r=read,v;
		Homology x=split(root,r),y=split(x.first,l-1);
		if(type==4)printf("%d\n",size(y.second));
		else{v=read;
			switch(type){
				case 1:trie_xor(y.second,(1<<20)-1);trie_or(y.second,(1<<20)-1^v);trie_xor(y.second,(1<<20)-1);break;
				case 2:trie_or(y.second,v);break;
				default:trie_xor(y.second,v);
			}
		}root=merge(merge(y.first,y.second),x.second);
	}
	return 0;
}
```



---

## 作者：luogubot (赞：2)

维护一个值域 $[0,2^{20})$ 的不可重集合，支持值域区间 xor,or,and 以及值域区间求元素个数。

元素初始给定后不再额外插入。

$1\leq n\leq 2\times 10^5$，$1\leq q\leq 10^5$。

前置知识：线段树合并，线段树分裂。

对于位运算，考虑通过一棵 Trie 来维护信息，也就是值域线段树，记全集 $U=2^{20}-1$。

操作区间 $[l,r]$ 时，通过线段树分裂将其独立出来，操作完成后再合并回去，于是值域区间操作都变为了全局操作。

全局 xor 是平凡的，它的本质是交换了某些层的左右儿子，可以通过简单的 tag 来实现。

全局 and 可以用 or 和 xor 两种操作完成，具体地，and $x$ 可以改为 xor $U$，or ($x$ xor $U$)，再 xor $U$，于是问题转为了如何实现 or 操作。

注意到元素只会随着操作不断减少，可以考虑均摊的思想来暴力一点执行 or 操作。

在某一位 or 了 1 等价于将这些层的左儿子合并到对应的右儿子上，总合并次数 $O(n\log V)$。

考虑一个结点什么时候需要递归暴力合并儿子，发现只有其在某个 $x$ 的对应位是 1，且该层同时有左儿子和右儿子时能合并，于是需要额外在每个结点维护标记表示在某层的左右儿子的存在性。注意在实现时，把左儿子合并到右儿子之前还要给左儿子额外 xor 上一个当前位以保证标记的正确。

一次合并除了合并时产生的代价还有递归找需要合并结点的复杂度，这个与深度有关，为 $O(\log V)$，于是最终的复杂度就是 $O(n\log^2 V)$。

代码实现参考了 [这篇博文](https://www.cnblogs.com/ac-evil/p/14745498.html)。

---

## 作者：_fairytale_ (赞：2)

大家好像都觉得这个题很简单/ll

设 $U=2^{20}-1$，则 $x\ \text{and}\ y$ 操作等价于 $(x\ \text{xor} \ U)\ \text{or}\ (y\ \text{xor}\  U)\ \text{xor}\ U$，接下来只需处理 $\text{or}$ 和 $\text{xor}$。

我们用权值线段树替代 01trie。

首先在权值线段树上分裂出操作的对应值域区间，这样就变成了全局操作。

$\text{xor}\ y$ 是简单的，只需要打 tag。

考虑 $\text{or}\ y$，$y$ 为 $0$ 的位不需考虑，$y$ 为 $1$ 的位上，我们分类讨论：

1. 对于没有子树的结点，没有影响。

2. 对于只有左子树的结点，相当于给左子树 $\text{xor}$ 上当前位。

3. 对于只有右子树的结点，没有影响。

4. 对于既有左子树又有右子树的结点，左子树将会合并到右子树。

设势能为结点个数，初始为 $\mathcal O(n\log V)$。注意到合并操作只会让势能减少，所以合并只会进行 $\mathcal O(n\log V)$ 次。如果每次可以在 $\mathcal O(\log V)$ 的时间复杂度内定位到需要合并的结点，那么这部分的总复杂度就是 $\mathcal O(n\log^2V)$。

首先，我们需要快速判断一个结点子树内是否会发生合并。这等价于子树中每一深度是否存在某个结点，既有左子树，也有右子树，容易用一个 `int` 压位维护。

如果不会发生合并，我们直接给子树打一个 $\text{or}$ 的 tag。接下来考虑 $\text{or}$ tag 和 $\text{xor}$ tag 的合并。发现对于某些位 $\text{or}$ 完再 $\text{xor}$ 会变成 $\text{and}$，所以设计标记为 $(a,b,c)$ 表示把子树内的所有数都 $\text{xor}\ a\ \text{or}\ b\ \text{and}\ c$。

$\text{and}$ 操作可以理解为把一些位变成 $0$，不难发现 $a,b,(c\ \text{xor}\ U)$ 之间无交，因为如果有交可以留下后面那个。两标记 $x,y$ 合并时，可以看成把 $x$ 与 $\text{xor},\text{or},\text{and}$ 依次合并，接下来推一下合并式子即可，最后结果是这样的：

```cpp
Tag operator + (Tag x,const Tag &y){
	auto Xor=[&](int d)->void{
		int a=x.a,b=x.b,c=x.c^U;
		x.a=x.a^d^(b&d)^(c&d);
		x.b=(x.b^(b&d))|(c&d);
		x.c=((c^(c&d))|(b&d))^U; 
	};
	auto Or=[&](int d)->void{
		int a=x.a,b=x.b,c=x.c^U;
		x.a=x.a^(a&d);
		x.b=x.b|d;
		x.c=c^(c&d)^U;
	};
	auto And=[&](int d)->void{
		d=U^d;
		int a=x.a,b=x.b,c=x.c^U;
		x.a=x.a^(a&d);
		x.b=x.b^(b&d);
		x.c=(c|d)^U;
	};
	Xor(y.a);
	Or(y.b);
	And(y.c);
	return x;
}
```

当然，设计标记为 $(a,b)$ 表示先 $\text{or}\ a$ 再 $\text{xor}\ b$ 也是可以的，而且更加简洁，但是我当时没有想到/ll

完整代码：
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
using namespace std;
#define maxn 301000
int rt,r2,tot;
int ls[maxn*50],rs[maxn*50];
struct Info{
	int hv,sum;
}info[maxn*50];
const int k=19;
const int U=(1<<(k+1))-1;
struct Tag{
	int a,b,c;//xor a or b and c
	Tag(int _a=0,int _b=0,int _c=U){
		a=_a,b=_b,c=_c;
	}
}tag[maxn*50];
Info operator + (Info x,Info y){
	return {x.hv|y.hv,x.sum+y.sum};
}
Tag operator + (Tag x,const Tag &y){
	auto Xor=[&](int d)->void{
		int a=x.a,b=x.b,c=x.c^U;
		x.a=x.a^d^(b&d)^(c&d);
		x.b=(x.b^(b&d))|(c&d);
		x.c=((c^(c&d))|(b&d))^U; 
	};
	auto Or=[&](int d)->void{
		int a=x.a,b=x.b,c=x.c^U;
		x.a=x.a^(a&d);
		x.b=x.b|d;
		x.c=c^(c&d)^U;
	};
	auto And=[&](int d)->void{
		d=U^d;
		int a=x.a,b=x.b,c=x.c^U;
		x.a=x.a^(a&d);
		x.b=x.b^(b&d);
		x.c=(c|d)^U;
	};
	Xor(y.a);
	Or(y.b);
	And(y.c);
	return x;
}
void pusht(const Tag &y,int p,int d){
	if((y.a>>d)&1)swap(ls[p],rs[p]);
	if((y.b>>d)&1){
		assert(ls[p]==0||rs[p]==0);
		if(rs[p]==0)swap(ls[p],rs[p]);
	}
	if(~(y.c>>d)&1){
		assert(ls[p]==0||rs[p]==0);
		if(ls[p]==0)swap(ls[p],rs[p]);
	}
	tag[p]=tag[p]+y;
}
void pu(int p,int d){
	info[p]=info[ls[p]]+info[rs[p]];
	info[p].hv|=((ls[p]&&rs[p])<<d);
}
void pd(int p,int d){
	if(ls[p])pusht(tag[p],ls[p],d-1);
	if(rs[p])pusht(tag[p],rs[p],d-1);
	tag[p]=Tag();
}
void split(int L,int R,int &x=rt,int &y=r2,int l=0,int r=U,int d=k){
	if(!x)return;
	if(L<=l&&r<=R){
		y=x,x=0;
		return;
	}
	y=++tot;
	pd(x,d);
	if(mid>=L)split(L,R,ls[x],ls[y],l,mid,d-1);
	if(mid<R)split(L,R,rs[x],rs[y],mid+1,r,d-1);
	pu(x,d),pu(y,d);
}
void mrg(int &x,int y,int d=k){
	if(!x||!y)x+=y;
	else if(d==-1){
		info[x].sum|=info[y].sum;
	}
	else{
		info[x]=info[x]+info[y];
		pd(x,d),pd(y,d);
		mrg(ls[x],ls[y],d-1);
		mrg(rs[x],rs[y],d-1);
		pu(x,d);
	}
}
void ins(int v,int &p,int d=k){
	if(!p)p=++tot;
	if(d==-1){
		info[p].sum|=1;
		return;
	}
	if(~(v>>d)&1)ins(v,ls[p],d-1);
	else ins(v,rs[p],d-1);
	pu(p,d);
}
void Xor(int v,int p=r2){
	pusht({v,0,U},p,k);
}
void Or(int v,int p=r2,int d=k){
	if(!p)return;
	if(!(info[p].hv&v)){
		pusht({0,v,U},p,d);
		return;
	}
	pd(p,d);
	if(((v>>d)&1)&&ls[p]){
		pusht({1<<d,0,U},ls[p],d-1);
		mrg(rs[p],ls[p],d-1);
		ls[p]=0;
	}
	Or(v,ls[p],d-1),Or(v,rs[p],d-1);
	pu(p,d);
}
int Q(int L,int R,int p=r2,int l=0,int r=U,int d=k){
	if(!p)return 0;
	if(L<=l&&r<=R)return info[p].sum;
	pd(p,d);
	int res=0;
	if(mid>=L)res+=Q(L,R,ls[p],l,mid,d-1);
	if(mid<R)res+=Q(L,R,rs[p],mid+1,r,d-1);
	return res; 
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1,x;i<=n;++i)cin>>x,ins(x,rt);
	for(int op,x,y,z;q--;){
		cin>>op>>x>>y;
		split(x,y);
		if(op==1){
			cin>>z;
			Xor(U);
			Or(z^U);
			Xor(U);
		}
		else if(op==2){
			cin>>z;
			Or(z); 
		}
		else if(op==3){
			cin>>z;
			Xor(z);
		}
		else {
			cout<<Q(x,y)<<'\n';
		}
		mrg(rt,r2);
	}
	return 0;
}
```

---

## 作者：xie_lzh (赞：1)

感觉是十分有趣的一个题。

给你一些数，维护值域区间与、或、异或、求不同的数的个数。

我们先可以考虑将数插入 $\mathtt{Trie}$ 中，以便进行位运算操作。对于题中所需要的值域区间操作，我们可以将 $\mathtt{Trie}$ 按值域分裂，具体操作与线段树分裂类似，不作赘述。

于是操作变为了全局操作。

同时维护与操作和或操作不太方便，我们可以用异或操作和或操作来表示与操作。

具体的，$x\ \mathtt{and}\ y=!(!x\ \mathtt{or}\ !y)$。取反操作可以用异或 $2^{20}-1$ 来代替。


我们发现，与操作和或操作会将不同的数变为相同的数，并且由于是对值域区间操作，我们的操作不会使一个数分裂成两种数。

由此，我们可以均摊的考虑。

我们发现，多种数合并为一种数至多发生 $n$ 次，所以我们可以暴力的维护数与数的合并。

具体的，对于 $\mathtt{Trie}$ 上的每个节点，维护 $\log V$ 个标记，代表 $\mathtt{Trie}$ 上对应节点子树内对应深度是否存在一个节点满足其既有左儿子，又有右儿子。这样我们就能知道，若我在这个子树内或上 $x$ 有哪些节点会发生合并，暴力地递归下去合并即可。

同时，对于不需要合并的部分，我们也需要维护一个或标记和异或标记分别表示子树内对应深度，将左儿子移动到右儿子和交换左右儿子的操作。

异或标记之间的合并与或标记之间的合并是简单的。

对于异或标记与或标记之间的合并，考虑这样一种情况，
设当前节点存在一异或标记为 $p$，此时我们需要在此节点打上一个或标记 $x$，我们可以考虑除去 $p$ 中的 $p$ 与 $x$ 的公共位，即 $p=p\ \mathtt{xor}\ (p\ \mathtt{and}\ x)$。这样操作后，我们在下传标记时先下传或标记，再下传异或标记，则可以去除标记之间的影响。

至此，我们实现了区间异或、或、与操作的维护。

对于询问，简单的维护子树叶子个数即可，注意细节上合并两个叶子时，我们只能保留一个叶子的贡献，因为我们询问的是区间不同的数的个数。

复杂度 $\Theta(n\log^2 V)$ 瓶颈在于深度相关标记的上传和查询。

[Code](https://codeforces.com/contest/1515/submission/282880771)

---

## 作者：_abcd_ (赞：0)

建立一棵 $[0,2^{20}-1)$ 的值域线段树，每个节点的值为对应区间内不同的数，对于操作 $4$，只需要求区间和就行了。

先用线段树分裂把 $[x,y]$ 的区间提取出来，就能将各种操作变成全局操作。操作完合并即可。

对于操作 $3$，发现就是对将相应层的左右子树交换，并不会影响节点的值,只需要打一个 $\text{tag}$ 就行了。

对于操作 $1$，注意到 $x \text{ and } y= !(!x \text{ or } !y)$，因此可以转化成操作 $2$ 和操作 $3$。

对于操作 $2$，其实就是将对应层的左子树合并到右子树，可以使用线段树合并实现。但是这个操作不太能打 $\text{tag}$，因为不能直接算出操作后节点的值。但是如果遍历整颗线段树显然复杂度会直接炸。注意到当某个节点的子树中的对应层没有任何一个节点同时有左右子树，那么就不存在“合并”的情况，也不会影响节点的值，直接打 $\text{tag}$ 就行了，否则就递归到左右两个区间处理。由于每次递归都会使他的子树大小变小，因此复杂度为 $n \log n$。

由于有两个 $\text{tag}$，我们定义 $(a,b)$ 作用于 $x$ 为 $x \text{ or } a \text{ xor } b$，那么就有 $(a,b)$ 作用于 $(c,d)$ 得到 $(a \text{ or } c,b \text{ and } !a \text{ xor }d)$。

一个小技巧，我们将 $\text{tag}$ 和 $\text{z}$ 翻转，就只需要在下传时右移 $1$，上传哪些层存在节点同时有左右子树的时候右移 $1$ 就行了，不需要记录当前是第几层。

### 附上代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mclear(a) memset(a,0,sizeof a)
#define fls() fflush(stdout)
#define maxn 200005
#define ls(x) smt[x].ls
#define rs(x) smt[x].rs
#define N 1048575
using namespace std;
struct Tree
{
    int n,db,ls,rs,tag1,tag2;
}smt[10000000];
int n,Q,idx,ro;
int re()
{
    int x=0,t=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*t;
}
void update(int pos)
{
    smt[pos].n=smt[ls(pos)].n+smt[rs(pos)].n;
    smt[pos].db=(smt[ls(pos)].db|smt[rs(pos)].db)<<1;
    if(ls(pos)&&rs(pos))
        smt[pos].db|=1;
}
void ins(int &pos,int l,int r,int k)
{
    if(!pos)pos=++idx;
    if(l==r)
    {
        smt[pos].n=1;
        return;
    }
    int mid=l+r>>1;
    if(k<=mid)
        ins(ls(pos),l,mid,k);
    else
        ins(rs(pos),mid+1,r,k);
    update(pos);
}
void huo(int pos,int tag)
{
    if(!pos)return;
    if(tag&1&&ls(pos))
        swap(ls(pos),rs(pos));
    smt[pos].tag1|=tag;
    smt[pos].tag2&=~tag;
}
void fz(int pos,int tag)
{
    if(!pos)return;
    if(tag&1)
        swap(ls(pos),rs(pos));
    smt[pos].tag2^=tag;
}
void pushtag(int pos)
{
    huo(ls(pos),smt[pos].tag1>>1);
    huo(rs(pos),smt[pos].tag1>>1);
    fz(ls(pos),smt[pos].tag2>>1);
    fz(rs(pos),smt[pos].tag2>>1);
    smt[pos].tag1=0;
    smt[pos].tag2=0;
}
int fi(int pos,int l,int r,int L,int R)
{
    if(!pos)
        return 0;
    if(L<=l&&r<=R)
        return smt[pos].n;
    pushtag(pos);
    int mid=l+r>>1,ret=0;
    if(L<=mid)
        ret+=fi(ls(pos),l,mid,L,R);
    if(R>mid)
        ret+=fi(rs(pos),mid+1,r,L,R);
    return ret;
}
void split(int& pos,int& pre,int l,int r,int L,int R)
{
    if(!pre)return;
    if(L<=l&&r<=R)
    {
        pos=pre;
        pre=0;
        return;
    }
    pushtag(pre);
    pos=++idx;
    int mid=l+r>>1;
    if(L<=mid)
        split(ls(pos),ls(pre),l,mid,L,R);
    if(R>mid)
        split(rs(pos),rs(pre),mid+1,r,L,R);
    update(pos);
    update(pre);
    if(!smt[pos].n)
        pos=0;
    if(!smt[pre].n)
        pre=0;
}
void mer(int& pos,int& pre,int l,int r)
{
    if(!pre)
        return;
    if(!pos)
    {
        pos=pre;
        pre=0;
        return;
    }
    if(l==r)
    {
        pre=0;
        return;
    }
    pushtag(pos);
    pushtag(pre);
    int mid=l+r>>1;
    mer(ls(pos),ls(pre),l,mid);
    mer(rs(pos),rs(pre),mid+1,r);
    update(pos);
    pre=0;
}
void cha(int pos,int l,int r,int x)
{
    if(!pos)
        return;
    if(!(x&smt[pos].db))
    {
        huo(pos,x);
        return;
    }
    pushtag(pos);
    int mid=l+r>>1;
    if(x&1)
        mer(rs(pos),ls(pos),mid+1,r);
    cha(ls(pos),l,mid,x>>1);
    cha(rs(pos),mid+1,r,x>>1);
    update(pos);
}
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    scanf("%d%d",&n,&Q);
    while(n--)
        ins(ro,0,N,re());
    while(Q--)
    {
        int op=re(),l=re(),r=re();
        if(op==4)
            printf("%d\n",fi(ro,0,N,l,r));
        else
        {
            int x=0,y=re();
            for(int i=1;i<=20;i++,y>>=1)
                x=x<<1|(y&1);
            int tro;
            split(tro,ro,0,N,l,r);
            if(op==1)
            {
                fz(tro,N);
                cha(tro,0,N,x^N);
                fz(tro,N);
            }
            if(op==2)
                cha(tro,0,N,x);
            if(op==3)
                fz(tro,x);
            mer(ro,tro,0,N);
        }
    }
    return 0;
}
```

---

## 作者：zesqwq (赞：0)

细节题，思维难度 $2500$。

看到位运算，考虑 $\text{01-trie}$。区间操作可以通过字典树合并和分裂来做。

异或是好维护的，打一个标记就行了，考虑或和与。比如或，发现实际上就是把线段树上那几位的左孩子与右孩子合并，考虑势能，可以只考虑既有左孩子又有右孩子的那些与「或」相关的节点，其余的就是把左孩子变成右孩子，不会影响答案（当然在 $\text{01trie}$ 合并之后可能会），直接打标记即可。$\text{trie}$ 的每个节点来维护那些位既有左孩子又有右孩子，作为势能，即可。

---

## 作者：3_14 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1515H)

# 思路

我们将所有数字的二进制表示存储在一个三元组中。要对一个范围执行操作，我们要拆分三元组以提取范围，执行操作，然后将所有内容合并回来。

AND $x$ 等价于序列 XOR $2^{20}-1$，OR $x\oplus(2^{20}-1)$，XOR $2^{20}-1$。XOR 不会影响子序列中的数字个数，因此我们可以简单地传播它。这样就只剩下 OR 运算了。

假设我们要设置子区间的第 $k$ 位。如果子区间的所有数字都设置了第 $k$ 位，我们就什么也不用做；如果子区间的所有数字都没有设置第 $k$ 位，我们就懒得对该位进行 XOR 操作。

因此，我们可以递归地处理 OR 操作，如果要设置的位在当前级别，则合并子代，如果所有要设置的位都满足这两个条件之一，则停止操作。我们可以通过在每个三角形节点中存储某个叶子中已设置位的掩码和某个叶子中未设置位的掩码来检测这些条件。

通过摊销分析，可以证明这种方法是 $O((n+q)\operatorname{log}^2C)$ 。直观地说，昂贵的 OR 运算会使子节点中的比特更加相似。

定义 $\Phi_k$ 为有第 $k$ 位被设置的叶子和第 $k$ 位未被设置的叶子的三角形节点数。定义 $\Phi_*$ 为三叉节点总数的 $1+\operatorname{log} C$ 倍。定义总潜力为 $\sum_{k=0}^{\operatorname{log} C-1}\Phi_k+\Phi_*$。它总是非负的，且最多为 $O(n\operatorname{log}^2 C)$。

拆分操作最多创建 $\operatorname{log} C$ 个节点，每个节点最多增加 $O(\operatorname{log} C)$ 个势垒，因此其摊销时间复杂度为 $O(\operatorname{log} ^ 2 C)$。

单边为空的合并操作耗时为 $O(1)$。递归合并运算将两个根合并，$\Phi_*$ 的减少要为根处 $\Phi_k$ 的可能增加付出代价。(与往常一样，递归调用不包括在成本中，因为它们是由其自身可能的减少所支付的）。

只有当存在某个 $k$，使得子里有一个 $k$ 位被设置的叶子和一个 $k$ 位未被设置的叶子时，OR 运算才会递归。操作完成后，所有叶子的第 $k$ 位都被设置。因此，递归的代价是根部 $\Phi_k$ 的减少。

# 代码

```cpp
#include<bits/stdc++.h>
#define lcm(x,y) x/__gcd(x,y)*y;
#define str to_string
using namespace std;
using ll=long long;
const int MAXLOGX=20;
const double EPS=1e-6;
template<int k>
struct Trie{
    Trie<k-1>* chd[2];
    int cnt;
    int lazy;
    int has[2];
    int get_cnt(){
        assert(this!=NULL);
        return cnt;
    }
    int get_has(int d){
        assert(this!=NULL);
        push();
        assert(has[d]<(1<<(k+1)));
        return has[d];
    }
    Trie(Trie<k-1>* l,Trie<k-1>* r):chd{l,r},cnt(0),lazy(0),has{0,0}{
        if(l){
            cnt+=l->get_cnt();
            has[0]|=l->get_has(0)|(1<<k);
            has[1]|=l->get_has(1);
        }
        if(r){
            cnt+=r->get_cnt();
            has[0]|=r->get_has(0);
            has[1]|=r->get_has(1)|(1<<k);
        }
        assert(has[0]<(1<<(k+1)));
        assert(has[1]<(1<<(k+1)));
    }
    void push(){
        assert(lazy<(1<<(k+1)));
        if(!lazy)return;
        if(lazy&(1<<k)){
            swap(chd[0],chd[1]);
            if((has[0]^has[1])&(1<<k)){
				has[0]^=(1<<k);
				has[1]^=(1<<k);
            }
            lazy^=(1<<k);
		}
        int flip=(has[0]^has[1])&lazy;
        has[0]^=flip;
        has[1]^=flip;
        if(chd[0])chd[0]->lazy^=lazy;
        if(chd[1])chd[1]->lazy^=lazy;
        lazy=0;
        assert(has[0]<(1<<(k+1)));
        assert(has[1]<(1<<(k+1)));
    }
};
template<>
struct Trie<-1>{
    int lazy;
    Trie():lazy(0){
    }
    int get_cnt(){
        assert(this!=NULL);
        return 1;
    }
    int get_has(int d){
        assert(this!=NULL);
        return 0;
    }
};
template<int k>
Trie<k>* create(int x){
    if(x&(1<<k))return new Trie<k>(NULL,create<k-1>(x));
    else return new Trie<k>(create<k-1>(x),NULL);
}
template<>
Trie<-1>* create(int x){
    return new Trie<-1>();
}
template<int k>
pair<Trie<k-1>*,Trie<k-1>*> destruct(Trie<k>* a){
    assert(a!=NULL);
    a->push();
    auto res=make_pair(a->chd[0],a->chd[1]);
    delete a;
    return res;
}
template<int k>
Trie<k>* join(Trie<k-1>* l,Trie<k-1>* r){
    if(l==NULL&&r==NULL) return NULL;
    return new Trie<k>(l,r);
}
template<int k>
Trie<k>* merge(Trie<k>* a,Trie<k>* b){
    if(!a)return b;
    if(!b)return a;
    auto aa=destruct(a);
    auto bb=destruct(b);
    Trie<k-1>* l=merge<k-1>(aa.first,bb.first);
    Trie<k-1>* r=merge<k-1>(aa.second,bb.second);
    return join<k>(l,r);
}
template<>
Trie<-1>* merge<-1>(Trie<-1>* a,Trie<-1>* b){
    if(!a)return b;
    if(!b)return a;
    delete b;
    return a;
}
template<int k>
std::pair<Trie<k>*,Trie<k>*> split(Trie<k>* a,int thres){
    if(a==NULL)return {NULL,NULL};
    if(thres<=0)return {NULL,a};
    if(thres>=(1<<(k+1)))return {a,NULL};
    assert(k>=0);
    auto aa=destruct(a);
    if(thres<(1<<k)){
        Trie<k-1>* l,*r;
        tie(l,r)=split<k-1>(aa.first,thres);
        return make_pair(join<k>(l,NULL),join<k>(r,aa.second));
    }else if(thres>(1<<k)){
        Trie<k-1>* l,*r;
        tie(l,r)=split<k-1>(aa.second,thres-(1<<k));
        return make_pair(join<k>(aa.first,l),join<k>(NULL,r));
    }else{
        return make_pair(join<k>(aa.first,NULL),join<k>(NULL,aa.second));
    }
}
template<>
std::pair<Trie<-1>*,Trie<-1>*> split<-1>(Trie<-1>* a,int thres){
    assert(0);
}
template<int k>
Trie<k>* update(Trie<k>* a,int val){
    if(a==NULL)return NULL;
    a->push();
    assert(val<(1<<(k+1)));
    if((val&a->has[0]&a->has[1])==0){
        a->lazy^=(val&a->has[0]);
        return a;
    }
    Trie<k-1>* l,*r;
    tie(l,r)=destruct(a);
    l=update<k-1>(l,val&~(1<<k));
    r=update<k-1>(r,val&~(1<<k));
    if(val&(1<<k))return join<k>(NULL,merge<k-1>(l,r));
    else return join<k>(l,r);
}
template<>
Trie<-1>* update<-1>(Trie<-1>* a,int val){
    return a;
}
int N,Q;
int main(){
    Trie<MAXLOGX-1>* root=NULL;
    scanf("%d %d",&N,&Q);
    for(int i=0;i<N;i++){
        int A;
        scanf("%d",&A);
        root=merge(root,create<MAXLOGX-1>(A));
    }
    for(int i=0;i<Q;i++){
        int T,L,R;
        scanf("%d %d %d",&T,&L,&R);
        Trie<MAXLOGX-1>* left,*right;
        tie(left,root)=split(root,L);
        tie(root,right)=split(root,R+1);
        if(T==4)printf("%d\n",root?root->cnt:0);
        else{
            int X;
            scanf("%d",&X);
            if(root!=NULL){
				if(T==1){
				    root->lazy^=((1<<MAXLOGX)-1);
				    root=update(root,X^((1<<MAXLOGX)-1));
				    root->lazy^=((1<<MAXLOGX)-1);
				}else if(T==2){
				    root=update(root,X);
				}else if(T==3){
				    assert(X<(1<<MAXLOGX));
				    root->lazy^=X;
				}
            }
        }
        root=merge(root,left);
        root=merge(root,right);
    }
    return 0; 
}
```

## [AC记录](https://codeforces.com/problemset/submission/1515/296300907)

---

