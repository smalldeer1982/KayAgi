# [POI 2011] ROT-Tree Rotations

## 题目描述

给定一颗有 $n$ 个**叶节点**的二叉树。每个叶节点都有一个权值 $p_i$（注意，根不是叶节点），所有叶节点的权值构成了一个 $1 \sim n$ 的排列。  
对于这棵二叉树的任何一个结点，保证其要么是叶节点，要么左右两个孩子都存在。  
现在你可以任选一些节点，交换这些节点的左右子树。  
在最终的树上，按照先序遍历遍历整棵树并依次写下遇到的叶结点的权值构成一个长度为 $n$ 的排列，你需要最小化这个排列的逆序对数。

## 说明/提示

### 样例 1 解释

下图中，左图是初始读入的树，右图是操作后的树。

![](https://cdn.luogu.com.cn/upload/image_hosting/r84e2l05.png)

### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n \leq 5 \times 10^3$。
- 对于 $100\%$ 的数据，保证 $2 \leq n \leq 2 \times 10^5$， $0 \leq x \leq n$，所有叶节点的权值是一个 $1 \sim n$ 的排列。

### 提示

请注意，$n$ **不是**树的结点个数。

## 样例 #1

### 输入

```
3
0
0
3
1
2
```

### 输出

```
1```

# 题解

## 作者：IC_QQQ (赞：53)


正如前面大佬们所说的： **权值线段树**和**线段树合并**。

对于任意一个节点，交换左右子树对当前节点和前面的所有节点**没有影响**。

因为这是**前序遍历**：根节点->左子树->右子树。可以看到，交换左右子树**对前面的节点无影响**。

我们要求的是逆序对最小，对于一个节点，逆序对有三种：

+ 在左子树中。
+ 在右子树中。
+ 跨越了左右子树。

我们清楚，交换子树只会对**第三种情况**产生影响。因此，我们只需要在**合并线段树**的过程中统计交换子树的逆序对个数u和不交换子树的逆序对个数v，取 **min(u,v)** 累加到答案中就行了。

现在的问题是如何找**第三种情况下的逆序对**。

上图：

![](https://i.loli.net/2019/05/13/5cd96945b450241844.png)


用p表示左子树，q表示右子树。ls表示左子节点，rs表示右子节点。


很明显，对于除了**叶节点**的每一个节点：

1. 如果不交换： $u+=[p.rs].size*[q.ls].size$ 。
2. 如果交换： $v+=[p.ls].size*[q.rs].size$。

重点：每一次合并线段树时，递归到除了叶节点的所有节点，都要累加逆序对个数**u,v**。

看图模拟一边很容易就明白了。

比如，递归到[1~4]这个节点时，累加u:我们只累加了3、4对1、2行成的 $2*2=4$ 组逆序对。但是继续向下递归到[3~4]时，4对3还有一组逆序对。

**因此，递归到除了叶节点的所有节点时，都要进行累加 u,v 的操作**。

讲完了。

### 补充------空间复杂度：

我们对每个叶节点都需要进行建树操作，该建树操作的值域是 $[1,n]$ ，而我们每次建树都得到一条链，这条链的长度就是 $logn$ ，因为有 $logn$ 层。
考虑极限情况，有大约 n 个叶节点，那么总的空间就是 $nlogn$ 。

注意： **线段树合并不需要新开节点**。

### 通俗易懂的代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
int n,top;//top：创建节点个数 
ll ans,u,v;//u,v：逆序对个数 
struct Tree{
	int ls,rs,size;
}da[22*N];//N*logN的空间 

int in(){//快读 
	int x=0;char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

int update(int l,int r,int val){//创建权值线段树 
	int pos=++top;
	da[pos].size++;
	if(l==r) return pos;
	int mid=(l+r)>>1;
	if(val<=mid) da[pos].ls=update(l,mid,val);
	else da[pos].rs=update(mid+1,r,val);
	return pos;
}

int merge(int p,int q,int l,int r){//合并线段树 
	if(!q||!p) return (!p)?q:p;//如果有节点为空，返回另一个节点 
	if(l==r){ da[p].size+=da[q].size; return p; }//叶节点，合并，返回 
	u+=(ll)da[da[p].rs].size*da[da[q].ls].size;//交换前 
	v+=(ll)da[da[p].ls].size*da[da[q].rs].size;//交换后 
	int mid=(l+r)>>1;
	da[p].ls=merge(da[p].ls,da[q].ls,l,mid);//继续合并左子节点 
	da[p].rs=merge(da[p].rs,da[q].rs,mid+1,r);//右子节点 
	da[p].size=da[da[p].ls].size+da[da[p].rs].size;//重置更新当前节点 
	return p;
} 

int dfs(){
	int pos,val=in();
	if(val==0){//不是叶节点 
		int ls=dfs(),rs=dfs();//ls:左子树的权值线段树的根节点，rs同理 
		u=0;v=0;//记得每次清零 
		pos=merge(ls,rs,1,n);//pos：合并后的权值线段树的根节点 
		ans+=min(u,v);//累加答案 
	}
	else pos=update(1,n,val);//叶节点，建树 
	return pos;//返回这颗权值线段树的根节点 
}

int main(){
	n=in();
	dfs();
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Nero_Claudius (赞：29)

这道题采用权值线段树合并的解法。

------------

首先讲一下解法中出现的两个概念：权值线段树与线段树合并。

所谓权值线段树，可以理解为维护的信息反过来的普通线段树，我个人认为值域线段树这个名字其实要准确一些。

举个例子，我们将序列$1,1,2,3,4,4,4,5,6,6$中的数依次插入，那么插入完成之后的效果图大概是下面这样的：

![](https://i.loli.net/2018/10/21/5bcbf9c356256.png)

（其中红色为节点的值）

也就是说，每一个节点维护的值是这个区间内的数出现的次数。

在实现权值线段树时，我们通常会采用动态开点的方式，也就是不创建无关的节点，当然也可以离散化数据，否则必然会空间超限。

而线段树合并的原理则是基于线段树较为稳定的结构。

在合并的过程中，我们将两颗线段树对应位置的节点的值合在一起，创建一颗新的线段树。

过程大致如下：

![](https://i.loli.net/2018/10/21/5bcbfaafa537c.png)

------------

这道题让我们求出逆序对个数最小值，并且允许我们随意交换一个节点的两棵子树。

考虑一个任意的节点，它的子树先序遍历后的逆序对显然只有三种组成：

1. 左子树中

2. 右子树中

3. 跨越左右子树

对子树的交换显然不会影响第1,2类，因此我们只需要计算出第三类的最小值即可。

至于计算则没有什么难度。由于我们维护的是值域，因此左儿子必定比右儿子大，那么我们就用左儿子大小乘以右儿子大小即可得出交换前逆序对个数。交换后同理之。

这里需要注意，我们能够这样计算是因为无论左右儿子怎么交换，影响的都只有当前部分的逆序对个数，而不会影响深度更浅的节点的值。

另：这道题处理输入十分窒息，可参考楼下写法。

------------

AC代码如下：

`509ms 57236kb`

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace StandardIO {

	template<typename T>inline void read (T &x) {
		x=0;T f=1;char c=getchar();
		for (; c<'0'||c>'9'; c=getchar()) if (c=='-') f=-1;
		for (; c>='0'&&c<='9'; c=getchar()) x=x*10+c-'0';
		x*=f;
	}

	template<typename T>inline void write (T x) {
		if (x<0) putchar('-'),x*=-1;
		if (x>=10) write(x/10);
		putchar(x%10+'0');
	}

}

using namespace StandardIO;

namespace Solve {
	
	const int N=200200;
	
	int n;
	long long ans,ans1,ans2;
	int tot_node;
	struct node {
		int ls,rs;
		long long val;
	} tree[N*20];
	
	void update (int l,int r,int v,int &pos) {
		if (!pos) pos=++tot_node;
		tree[pos].val++;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (v<=mid) update(l,mid,v,tree[pos].ls);
		else update(mid+1,r,v,tree[pos].rs);
	}
	void merge (int &x,int y) {
		if (!x||!y) {
			x=x+y;return;
		}
		tree[x].val+=tree[y].val;
		ans1+=(long long)tree[tree[x].rs].val*tree[tree[y].ls].val;
		ans2+=(long long)tree[tree[x].ls].val*tree[tree[y].rs].val;
		merge(tree[x].ls,tree[y].ls);
		merge(tree[x].rs,tree[y].rs);
	}
	void dfs (int &x) {
		int tmp,ls,rs;x=0;
		read(tmp);
		if (!tmp) {
			dfs(ls),dfs(rs);
			ans1=ans2=0;
			x=ls,merge(x,rs);
			ans+=min(ans1,ans2);
		} else update(1,n,tmp,x);
	}

	inline void solve () {
		read(n);
		int tmp=0;
		dfs(tmp);
		write(ans);
	}
}

using namespace Solve;

int main () {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	solve();
}

```

---

## 作者：ez_lcw (赞：15)

~~输入格式真的毒瘤~~

权值线段树合并。

我们先对每一个叶子建一棵权值线段树，并把它自己的权值插入到里面。然后不断的向上合并。

我们不妨设**原树**中当前节点为 $u$，爸爸 $fa$，左儿子 $lc$，右儿子 $rc$，那么显然这棵树中的逆序对分为 $3$ 个部分：$lc$ 里的逆序对，$rc$ 里的逆序对和跨 $lc$ 和 $rc$ 的逆序对。

而我们现在已经把 $lc$ 里的逆序对和 $rc$ 里的逆序对算好了，现在需要求出跨 $lc$ 和 $rc$ 的逆序对，也就是合并 $lc$ 和 $rc$ 。然后我们发现，无论 $lc$ 内的子树怎么换来换去，$rc$内的子树怎么换来换去，都是对跨 $lc$ 和 $rc$ 的逆序对个数没有影响的。

同理，无论我们交不交换 $lc$ 和 $rc$，对 $fa$ 那一层的合并也是没有影响的。

所以对于跨 $lc$ 和 $rc$ 的逆序对，我们分交换 $lc$、$rc$ 和不交换的情况算出两种情况的逆序对个数，再取较小值就好了。

我们遍历两棵权值线段树来暴力合并两棵权值线段树。

那么对于 $lc$ 和 $rc$ **权值线段树**中同一位置的点 $a$、$b$，若不交换 $lc$ 和 $rc$，显然 $lc$ 中的点的编号（这里的编号是指前序遍历的先后顺序）肯定都在 $rc$ 前，$a$ 右儿子的权值必定大于 $b$ 左儿子的权值，所以 $size[ch[a][1]]*size[ch[b][0]]$ 就是这一位置的答案了。

同理，如果交换 $lc$ 和 $rc$，这一位置的答案就是 $size[ch[a][0]]*size[ch[b][1]]$。

最后合并完统计答案即可。

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 200010
#define int long long

using namespace std;

struct Tree
{
	int ch[2],size;
}t[N<<5];

int n,tot,ans,num1,num2;

int update(int l,int r,int val)
{
	int u=++tot;
	t[u].size=1;
	if(l==r) return u;
	int mid=(l+r)>>1;
	if(val<=mid) t[u].ch[0]=update(l,mid,val);
	else t[u].ch[1]=update(mid+1,r,val);
	return u;
}

int merge(int a,int b,int l,int r)//把b合并至a
{
	if(!a||!b) return a+b;
	if(l==r)
	{
		t[a].size+=t[b].size;
		return a;
	}
	num1+=t[t[a].ch[1]].size*t[t[b].ch[0]].size;//不交换的答案
	num2+=t[t[b].ch[1]].size*t[t[a].ch[0]].size;//交换后的答案
	int mid=(l+r)>>1;
	t[a].ch[0]=merge(t[a].ch[0],t[b].ch[0],l,mid);
	t[a].ch[1]=merge(t[a].ch[1],t[b].ch[1],mid+1,r);
	t[a].size+=t[b].size;
	return a;
}

int dfs()
{
	int u,val;
	scanf("%lld",&val);
	if(!val)
	{
		int lc=dfs(),rc=dfs();
		num1=num2=0;
		u=merge(lc,rc,1,n);
		ans+=min(num1,num2);//ans加上较小值
	}
	else u=update(1,n,val);
	return u;
}

signed main()
{
	scanf("%lld",&n);
	dfs();
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：缙云山车神 (赞：12)

看到大佬们都在说输入毒瘤

但是因为输入是从上往下递归的

合并多颗线段树也是递归的 （先合并下面的再往上）

所以可以输入的时候就求答案了

大概就是
```cpp
int dfs(){
	int x;
	scanf("%d",&x);
	if(x!=0) return new_node(x);//叶子节点就直接加一个点
	return merge(dfs(),dfs());//不然就递归合并两个子树
}
int main(){
	cin>>n;
	cout<<tree[dfs()].ans;
}
```
然后补全new_node()和merge()两个函数 就没了
```cpp
#include <bits/stdc++.h>
#define N 50000100
#define mid ((l+r)>>1)
using namespace std;
int n,nn;
struct node{
	int lson,rson,sum;
	long long ans;
}tree[N];
inline int new_node(int x,int l=1,int r=n){
	int k=++nn;
	tree[nn].sum=1;
	if(l==r) return nn;
	if(x<=mid) tree[nn].lson=new_node(x,l,mid);
	else tree[nn].rson=new_node(x,mid+1,r);
	return k;
}
long long res0,res1;
inline int merge(int x,int y,int l=1,int r=n){
	if(!y||!x){ res0=res1=0; return x|y; }
	tree[x].ans=tree[x].ans+tree[y].ans;
	long long aa=1ll*tree[tree[x].rson].sum*tree[tree[y].lson].sum,bb=1ll*tree[tree[x].lson].sum*tree[tree[y].rson].sum;
	tree[x].lson=merge(tree[x].lson,tree[y].lson,l,mid);//合并左子树 
	aa+=res0; bb+=res1;
	tree[x].rson=merge(tree[x].rson,tree[y].rson,mid+1,r);//合并右子树 
	aa+=res0; bb+=res1;
	tree[x].ans+=min(aa,bb);
	tree[x].sum=tree[tree[x].lson].sum+tree[tree[x].rson].sum; 
	res0=aa,res1=bb;
	return x;
}
inline int dfs(){
	int x;
	scanf("%d",&x);
	if(x!=0) return new_node(x);
	return merge(dfs(),dfs());
}
int main(){
	cin>>n;
	cout<<tree[dfs()].ans;
}
```
卡空间卡了好久（我太菜了不会写内存池

---

## 作者：Limit (赞：7)

# 题目大意

给出一颗有 $n$ 个叶节点的二叉树,且对于所有非叶节点都有两个儿子,每次操作可以交换任意节点的两个儿子,最终要使得先序遍历后叶节点的逆序对最少,输出这个最小值.

# 分析

考虑交换某个节点的两个儿子对最终答案的影响,交换之后对于子树内的逆序对并不会产生影响,对这颗子树树以外的逆序对也不会产生影响,所以产生的影响只有两颗子树.那么只需要考虑哪棵子树放前面更优就好了.

考虑用权值线段树来维护每个数出现的次数,考虑合并的时候同时计算出两种情况所产生的逆序对个数.

那么考虑如何快速计算左右子树的两种摆放方式的逆序对个数.可以发现在合并的时候会遍历两子树中区间内都非空很多区间,那么可以通过乘法原理来计算逆序对.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=2e5+5;
const int MAX_NUM=2e5;
const int INF=1e9;
int n;
long long answer=0;
long long minll(long long a,long long b)
{
	if(a<b)
	{
		return a;
	}
	return b;
}
struct SegmentTree
{
	int lson,rson,sum;
}sgt[MAXN*32];
int sgt_cnt=0;
int rubbish[MAXN*32],rubbish_cnt=0;
#define LSON sgt[now].lson
#define RSON sgt[now].rson
#define MIDDLE ((left+right)>>1)
#define LEFT LSON,left,MIDDLE
#define RIGHT RSON,MIDDLE+1,right
int NewPoint()//防止空间不足,写一个空间回收
{
	if(rubbish_cnt)
	{
		return rubbish[rubbish_cnt--];
	}
	return ++sgt_cnt;
}
void DeletePoint(int &now)
{
	sgt[now].lson=sgt[now].rson=0;
	sgt[now].sum=0;
	rubbish[++rubbish_cnt]=now;
	now=0;
}
void PushUp(int now)//合并标记
{
	sgt[now].sum=sgt[LSON].sum+sgt[RSON].sum;
}
void Updata(int place,int &now,int left=1,int right=MAX_NUM)//单点修改
{
	if(place<left||right<place)
	{
		return;
	}
	if(!now)
	{
		now=NewPoint();
	}
	if(left==right)
	{
		sgt[now].sum++;
		return;
	}
	Updata(place,LEFT);
	Updata(place,RIGHT);
	PushUp(now);
}
long long add_1,add_2;
void Merge(int &tree1,int &tree2,int left=1,int right=MAX_NUM,bool first=1)//线段树合并
{
	if(first)
	{
		add_1=add_2=0;
	}
	if(!tree1||!tree2)
	{
		tree1+=tree2;
		tree2=0;
		return;
	}
	if(left==right)
	{
		sgt[tree1].sum+=sgt[tree2].sum;
		DeletePoint(tree2);
		return;
	}
	add_1+=1ll*sgt[sgt[tree1].rson].sum*sgt[sgt[tree2].lson].sum;//通过乘法原理计算逆序对
	add_2+=1ll*sgt[sgt[tree1].lson].sum*sgt[sgt[tree2].rson].sum;
	Merge(sgt[tree1].lson,sgt[tree2].lson,left,MIDDLE,0);//继续合并左右子树
	Merge(sgt[tree1].rson,sgt[tree2].rson,MIDDLE+1,right,0);
	DeletePoint(tree2);
	PushUp(tree1);
}
#undef LSON
#undef RSON
#undef MIDDLE
#undef LEFT
#undef RIGHT
struct Tree
{
	int lson,rson,now;
}tree[MAXN];
int tree_cnt=0;
#define LSON tree[now].lson
#define RSON tree[now].rson
void DFS(int &root)//遍历全树
{
	int val;
	scanf("%d",&val);
	if(val)
	{
		Updata(val,root);//叶节点只要单点修改就好了
		return;
	}
	int now=++tree_cnt;
	DFS(LSON);
	DFS(RSON);
	Merge(LSON,RSON);//非叶节点需要合并子树
	root=LSON;
	answer+=minll(add_1,add_2);//并且加上逆序对更少的情况
}
#undef LSON
#undef RSON
int main()
{
	scanf("%d",&n);
	int root=0;
	DFS(root);
	printf("%lld",answer);
	return 0;
}
```



---

## 作者：Unordered_OIer (赞：7)

# P3521 题解
## 题意
一棵二叉树，所有非叶子节点都有两个孩子。在每个叶子节点上有一个权值(有 $n$ 个叶子节点，满足这些权值为 $1 ...... n$ 的一个排列)。可以任意交换每个非叶子节点的左右孩子。

要求进行交换使最终所有叶子节点的权值按遍历序写出来逆序对个数最少。

## 建模
很显然内部结构不会影响逆序对个数，因此只需要统计**每个节点左右子树之间的逆序对**即可，于是：

$$ans=\sum\limits_{u=1}^{2n-1}\text{Count}(x,y)|x \in \text{ls}(u),y \in \text{rs}(u),a_x>a_y$$

其中 $\text{ls}(u),\text{rs}(u)$ 分别代表 $u$ 的左儿子和右儿子。  
那么就以输入的 $dfs$ 序计算 $u$ 即可，接下来就是解决 $x,y$ 。

1. 暴力枚举 $x,y$  
复杂度 $\Theta(|\text{ls}(u)||\text{rs}(u)|)=\Theta(n^2)$ 。

2. 归并排序  
复杂度 $\Theta(|\text{ls}(u)|+|\text{rs}(u)|)=\Theta(n \log n)\ /\ \Theta(n^2)$ ，因为树的结构给定，不能保证归并排序不退化。

那么我们就可以从值域的角度考虑，**合并左右子树 $x,y$ 的计数器数组 $C_x,C_y$ 同样也能累计逆序对数**。

此时：

$$ans(u)=\sum\limits_{i=1}^nC_x(i) \times \sum\limits_{j=1}^{i-1}C_y(j)$$

$$C_{x+y}(i)=C_x(i)+C_y(i)$$

$C_y(j)$ 的前缀和可以预计算。

## 优化

但是有一个问题就是这样做复杂度还没变。  
一种解决办法就是启发式合并 $+\texttt{ BIT}$ ，复杂度 $\Theta(n (\log n)^2)$ 。

我们发现，对于一个子树 $u$ ， $C_u$ 只有 $\text{size}(u)$ 个位置非 $0$ ，如果遍历整个计数器就很浪费。  
这种情况下对于每一个 $u$ 都进行标准的离散化显然非常亏。

于是，我们就可以想到**动态开点线段树**。

### 动态开点线段树
大致的说就是一次不把整个线段树建起来，而是根据输入只建一部分节点，剩下的那些用不到的节点就先不建。而需要注意的一个地方就是这样**动态开点**后 $x$ 的**左右儿子编号**不再是 $2x,2x+1$ 了，需要用一个单独的数组进行存储。

于是我们就要在原树的每个 $C_u$ 上建一个**动态开点权值线段树**，父线段树就是合并左右子线段树，即：

$$ans(u)=\sum\limits_{i=1}^nsz_x(\text{rs}(i)) \times sz_y(\text{ls}(i))$$

其中 $i$ 是权值线段树节点编号， $sz$ 是权值线段树的目标函数。

然后就可以快乐地写代码啦~

## Code
```cpp
#include<bits/stdc++.h>
#define N 抄袭差评
using namespace std;
typedef long long ll;
struct node{ll left_son,right_son,siz;}
segment_tree[N*30];
ll n,tot,ans,ans1,ans2;
ll create_Tree(ll l,ll r,ll x)
{
segment_tree[++tot].siz=1;
if(l==r)
  return tot;
  ll mid=(l+r)>>1,now=tot;
if(x<=mid)
  segment_tree[now].left_son=create_Tree(l,mid,x);
  else segment_tree[now].right_son=create_Tree(mid+1,r,x);
  return now;
}
void combine_Tree(ll l,ll r,ll x,ll y)
{
  if(l==r)
  segment_tree[x].siz+=segment_tree[y].siz;
  ll mid=(l+r)>>1;
ans1+=1ll*segment_tree[segment_tree[x].right_son].siz*segment_tree[segment_tree[y].left_son].siz;
ans2+=1ll*segment_tree[segment_tree[x].left_son].siz*segment_tree[segment_tree[y].right_son].siz;
  if(segment_tree[y].left_son)
  {
  if(segment_tree[x].left_son)
  combine_Tree(l,mid,segment_tree[x].left_son,segment_tree[y].left_son);
  else
  segment_tree[x].left_son=segment_tree[y].left_son;
  }
  if(segment_tree[y].right_son)
  {
  if(segment_tree[x].right_son)
  combine_Tree(l,mid,segment_tree[x].right_son,segment_tree[y].right_son);
  else
  segment_tree[x].right_son=segment_tree[y].right_son;
  }
  segment_tree[x].siz=segment_tree[segment_tree[x].left_son].siz
  +segment_tree[segment_tree[x].right_son].siz;
}
ll solve(){
  ll v;v=read();
  if(v)
  return create_Tree(1,n,v);
  ll x=solve(),y=solve();
ans1=ans2=0;
combine_Tree(1,n,x,y);
ans+=min(ans1,ans2);
  return x;
}
int main(){
  scanf("%lld",&n);
  solve();
  return 0;
}//缩进有些奇怪
```


---

## 作者：do_while_true (赞：3)

注意到如果我们用类似 cdq 分治的思想，对于每个节点统计“左子树的叶子和右子树的叶子进行匹配的逆序对数”从而求和得到总体逆序对数，那么对于任意两个不同节点，他们各自的两个子树交不交换位置对答案的影响是互相独立的。

所以只需要求对于每个节点是否交换优即可。

考虑在每个叶节点开权值线段树然后向上合并，合并的过程中我们就能以同样类似 cdq 分治思想的做法，把 逆序对/顺序对 求出来，取最小值加入到答案中即可。

具体求法是，线段树合并的从中间断开递归的时候，算出左区间和右区间匹配出的逆序对，然后再递归下去的时候算左区间和右区间内部的逆序对。

时间复杂度 $\mathcal{O}(n\log n)$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
#define ls(x) tree[x].lson
#define rs(x) tree[x].rson
const int N = 3.8e6;
const int INF = 0x7fffffff;
int n, trnt;
struct SGT {
	int lson, rson, sum;
}tree[N];
void modify(int &x, int tl, int tr, int pos) {
	if(!x)
		x = ++trnt;
	++tree[x].sum;
	if(tl == tr) return ;
	int mid = (tl + tr) >> 1;
	if(pos <= mid) modify(ls(x), tl, mid, pos);
	else modify(rs(x), mid+1, tr, pos);
}
ll s1, s2, ans;
void merge(int &x, int y, int tl, int tr) {
	if(!x || !y) {
		x = x + y;
		return ;
	}
	tree[x].sum += tree[y].sum;
	if(tl == tr) return ;
	s1 += 1ll * tree[rs(x)].sum * tree[ls(y)].sum;
	s2 += 1ll * tree[rs(y)].sum * tree[ls(x)].sum;
	int mid = (tl + tr) >> 1;
	merge(ls(x), ls(y), tl, mid);
	merge(rs(x), rs(y), mid+1, tr);
}
void dfs(int &x) {
	int t; read(t);
	if(!t) {
		int lson = 0, rson = 0;
		dfs(lson);
		dfs(rson);
		s1 = 0; s2 = 0;
		x = lson; merge(x, rson, 1, n);
		ans += Min(s1, s2);
	}
	else modify(x, 1, n, t);
}
#undef ls
#undef rs
signed main() {
//	freopen("in.txt", "r", stdin);
	read(n); int root = 0;
	dfs(root);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Awdrgysxc (赞：3)

## 【$Analysis$】
发现交换两个子树对其他的逆序不影响，只对跨两颗树的逆序对有影响，于是就有一个贪心；

>### 1.权值线段树合并
>从底至上，依次合并线段树，合并的时候可以顺便算一下交换和不交换产生的逆序对数，最后取$min$，时间复杂度$O(nlog_2n)$常数较大的$log_2$

>### 2.Dsu on Tree
>对于跨子树的逆序对暴力算就好了，可以用树状数组；时间复杂度$O(nlog_2^2n)$常数较小的$log_2^2$

## 【$Code1$】
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

inline int read()
{
	int res = 0; bool f = 0; char c = getchar();
	while ((c<'0')|(c>'9')) f ^= !(c^'-'), c = getchar();
	while ((c>='0')&(c<='9')) res = (res<<1)+(res<<3)+(c^'0'),c = getchar();
	return f ? -res : res;
}

typedef long long int64;

const int MaxN = 3e5 + 11;

struct Tree
{
	int ls, rs, val;
} T[MaxN * 55];

int n, t, f;

int64 ans, ans1, ans2;

bool Is[MaxN];

inline void Mo(int& o, int v, int l = 1, int r = n)
{
	T[(!o) ? (o = ++t) : o].val ++;
	if (l == r) return ;
	int mid = l + r >> 1;
	v <= mid ? Mo(T[o].ls, v, l, mid) : Mo(T[o].rs, v, mid + 1, r);
}

inline void Merge(int &u, int v)
{
	if (!u || !v) u = u | v;
	else
	{
		T[u].val += T[v].val, ans1 += (int64)T[T[u].rs].val * T[T[v].ls].val,
		ans2 += (int64)T[T[u].ls].val * T[T[v].rs].val,
		Merge(T[u].ls, T[v].ls), Merge(T[u].rs, T[v].rs);
	}
}

void Find(int& u)
{
	int x = read(), ls, rs; u = 0;
	if (!x)
	{
		Find(ls), Find(rs); ans1 = ans2 = 0;
		Merge(ls, rs), u = ls, ans += ans1 < ans2 ? ans1 : ans2;
	} else Mo(u, x);
}

int main(void) { n = read(), Find(f = 0), printf("%lld\n", ans); return 0; }
```


## 【$Code2$】
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

inline char gc()
{
    static char s[1<<20|1]={0},*p1=s,*p2=s;
    return (p1==p2)&&(p2=(p1=s)+fread(s,1,1<<20,stdin),p1==p2)?EOF:*(p1++);
}

inline int read()
{
	int res = 0; bool f = 0; char c = gc();
	while ((c<'0')|(c>'9')) f ^= !(c^'-'), c = gc();
	while ((c>='0')&(c<='9')) res = (res<<1)+(res<<3)+(c^'0'),c = gc();
	return f ? -res : res;
}

typedef long long int64;

const int MaxN = 4e5 + 11;

int T[MaxN>>1], Size[MaxN], Hs[MaxN], L[MaxN], R[MaxN], Num[MaxN], Dfn[MaxN];

int n, t, son;

int64 ans, ans1, ans2;

inline void Mo(int p, int v) { for (;p <= n;) T[p] += v, p += p & -p; }

inline int Qu(int p) { int v = 0; for (;p;) v += T[p], p -= p & -p; return v; }

inline void Input(int id)
{
	int x = read();
	if (!x)
	{
		Dfn[id] = ++t, Input(L[id] = t + 1), Input(R[id] = t + 1),
		Hs[id] = (Size[L[id]] >= Size[R[id]]) ? L[id] : R[id];
		Size[id] = Size[L[id]] + Size[R[id]] + 1;
	} else Num[id] = x, Size[id] = 1, Dfn[id] = ++t, Hs[id] = -1;
}

inline void Add(int u)
{
	int v = Qu(n); ans1 = ans2 = 0;
	for (int i = Dfn[u];i < Dfn[u] + Size[u]; ++i) if (Num[i])
	{
		int g = Qu(Num[i]);
		ans1 += g, ans2 += v - g;
	} for (int i = Dfn[u];i < Dfn[u] + Size[u]; ++i) if (Num[i]) Mo(Num[i], 1);
}

inline void Del(int u) { for (int i = Dfn[u];i < Dfn[u] + Size[u]; ++i) if (Num[i]) Mo(Num[i], -1); }

inline void Solve(int u, int is)
{	
	if (!~Hs[u]) { if (is) Mo(Num[u], 1); return ; }
	
	if (Hs[u] != L[u])
	{
		Solve(L[u], 0), Solve(R[u], 1), son = R[u], Add(L[u]), ans += (ans1 < ans2) ? ans1 : ans2;
		if (!is) Del(u);
	}
	else
	{
		Solve(R[u], 0), Solve(L[u], 1), son = L[u], Add(R[u]), ans += (ans1 < ans2) ? ans1 : ans2;
		if (!is) Del(u);
	} 
}

int main(void)
{
	n = read();
	Input(1);
	Solve(1, 1);
	printf("%lld\n", ans);
   return 0;
}
```

---

## 作者：_ctz (赞：2)

[更好的阅读体验$QwQ$](https://ctz45562.github.io/2019/03/07/%E9%A2%98%E8%A7%A3-bzoj-2212-%E3%80%90-POI2011-ROT-Tree-Rotations%E3%80%91/)

[传送门](https://www.luogu.org/problemnew/show/P3521)

[能看得懂题面的传送门](https://www.lydsy.com/JudgeOnline/problem.php?id=2212)

前序遍历叶子节点，可以理解为把叶子节点从左到右输出。


那么首先考虑一个性质：**交换某个节点的左右儿子，仅会对这两棵子树之间的逆序对造成影响，而对某棵子树内部、它祖宗十八代之间的逆序对没有影响。**

某个节点的左子树和右子树有哪些数换完之后还是有哪些数，交换后相对位置变化的只有这两棵子树，所以仅对这两棵子树有影响。

这样就有一个贪心的思路：如果某个节点交换左右儿子更优则交换。

怎么叫更优？交换后左、右子树之间逆序对小于交换前的就算更优。（注意这里的逆序对就针对于这两棵子树之间的值，不算上子树内部产生的逆序对）

现在问题转化成了：计算每个节点左、右子树之间的逆序对数。首先可以想到合并。其实平衡树启发式合并和线段树合并都珂以，不过平衡树$O(nlog^2n)$太慢了，这里选择线段树合并。

对树进行$dfs$，使用动态开点权值线段树，从底部将叶子节点的权值一步步合并上来，在任意节点就能得到其左右儿子的线段树。对于求两棵子树间的逆序对，珂以在合并时求出。放图举个栗子：

![](https://cdn.luogu.com.cn/upload/pic/53393.png )

比如现在合并到了蓝色节点，就让计数变量加上**左儿子线段树中该节点的右儿子的值 x 右儿子线段树上该节点的左儿子的值**，也就是上图中红色节点的值乘绿色节点的值。然后在递归的每个节点都执行这个操作。

这个操作可以理解为：不考虑某个节点内部的逆序对情况，**红色节点中的每个值都能与绿色节点中的每个值产生逆序对**，于是有两值相乘为答案。至于节点内部就可以继续递归求出。

交换后的逆序对数：记$sizl$为左子树权值（叶子节点）的个数，$sizr$为右子树权职的个数，交换前有$x$对逆序对。则交换后就有$sizl*sizr-x$对逆序对。

这个容易理解：共有$sizl*sizr$种组合，每个之前不符合逆序对的组合，交换后就符合了。同理之前符合的交换后就不符合了。

答案的统计：珂以$dfs$完之后直接前序遍历用归并排序或树状数组求出。但是在$dfs$中已经求出每个节点左右儿子间逆序对数，就可以把这个值加起来作为答案，效率高很多。

还有注意开$long\ long$

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 200005
#define inf 0x3f3f3f3f
#define pn putchar('\n')
#define px(x) putchar(x)
#define ps putchar(' ')
#define pd puts("======================")
#define pj puts("++++++++++++++++++++++")

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
template<typename T>
inline T read(){
	T x=0;
	int y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
struct Tree{
	int ls,rs,root,d;
    //左儿子、右儿子、线段树的根、权值
}t[maxn<<1];
//节点数要开两倍
int num=1,n;
long long ans,all;
//all是最终答案，ans是中间统计左右子树间逆序对的计数器
struct Segment_Tree{
	int dat[maxn<<5],ls[maxn<<5],rs[maxn<<5],cnt;
#define ls(x) ls[x]
#define rs(x) rs[x]
	void add(int poi,int l,int r,int &node){
		node=++cnt;
		dat[node]=1;
		if(l==r)return;
		int mid=l+r>>1;
		if(poi<=mid)add(poi,l,mid,ls(node));
		else add(poi,mid+1,r,rs(node));
	}
	int merge(int l,int r,int x,int y){
		if(!x||!y)return x|y;//有空节点返回另一个
		dat[x]+=dat[y];//合并两个节点信息
		if(l==r)return x;//递归到底层返回
		int mid=l+r>>1;
		ans+=1ll*dat[rs(x)]*dat[ls(y)];
        //这里x为左儿子的节点，y为右儿子的节点，就有上面提到的统计方法
		ls(x)=merge(l,mid,ls(x),ls(y));
		rs(x)=merge(mid+1,r,rs(x),rs(y));
		return x;
	}//线段树合并
}st;
void dfs(int node=1){
	if(!t[node].ls)return;
	dfs(t[node].ls);
	dfs(t[node].rs);
    //先处理左右儿子，得到左右儿子的情况
	ans=0;
    //计数器清零
	long long siz=1ll*st.dat[t[t[node].ls].root]*st.dat[t[t[node].rs].root];
	t[node].root=st.merge(1,n,t[t[node].ls].root,t[t[node].rs].root);
	if(ans>siz-ans)swap(t[node].ls,t[node].rs),all+=siz-ans;
	else all+=ans;
    //直接用中间过程求的值统计最终答案
}
void Get(int node=1){
	t[node].d=read();
	if(!t[node].d)Get(t[node].ls=++num),Get(t[node].rs=++num);
	else st.add(t[node].d,1,n,t[node].root);
}//递归读入
int main(){
	n=read();
	Get();
	dfs();
	printf("%lld\n",all);
}

```

---

## 作者：lhm_ (赞：2)

给定一棵二叉树，叶子节点有权值，可以进行若干次交换一个节点的左右儿子的操作，使前序遍历叶子的逆序对最少。

考虑一个节点下子树逆序对的产生：

① 只在左子树中产生。

② 只在右子树中产生。

③ 在左子树和右子树中交叉产生。

因为二叉树的性质，所以 ① ② 两种情况只需递归下去求解，只需考虑情况 ③ 。

用权值线段树来记录信息，通过线段树合并来统计答案。

具体实现细节看代码吧。

记得开$long\ long$。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 10000010
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
int n,root,tree_cnt;
ll s1,s2,ans;
bool vis[maxn];
int ls[maxn],rs[maxn],rt[maxn];
ll siz[maxn];
void pushup(int cur)
{
    siz[cur]=siz[ls[cur]]+siz[rs[cur]];
}
void modify(int L,int R,int pos,int &cur)
{
    if(!cur) cur=++tree_cnt;
    if(L==R)
    {
        siz[cur]++;
        return;
    }
    int mid=(L+R)>>1;
    if(pos<=mid) modify(L,mid,pos,ls[cur]);
    if(pos>mid) modify(mid+1,R,pos,rs[cur]);
    pushup(cur);
}
int merge(int x,int y)
{
    if(!x||!y) return x+y;
    s1+=siz[ls[x]]*siz[rs[y]];
    s2+=siz[ls[y]]*siz[rs[x]];
    ls[x]=merge(ls[x],ls[y]);
    rs[x]=merge(rs[x],rs[y]);
    pushup(x);
    return x;
}
void dfs(int &x)
{
    int val;
    read(val);
    x=++tree_cnt;
    if(!val) dfs(ls[x]),dfs(rs[x]);
    else vis[x]=true,modify(1,n,val,rt[x]);
}
void work(int x)
{
    if(vis[x]) return;
    work(ls[x]),work(rs[x]),s1=s2=0;
    rt[x]=merge(rt[ls[x]],rt[rs[x]]);
    ans+=min(s1,s2);
}
int main()
{
	read(n);
    dfs(root);
    work(root);
    printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Vocalise (赞：1)

线段树合并的一种变形应用。

没翻题解做出来了，感动。

本题序列中的结构实际就是多个单点按照次序合并。

而我们求的逆序对，联想 CDQ 分治，正是可以拆分区间解决的问题。

求逆序对最小值，发现对于每一次合并考虑左右两个区间之间的贡献即可。

显然，不解释。

所以我们可以每次贪心取左右两区间之间交换与不交换所得逆序对数的较小值。

求逆序对若朴素 $\mathcal O(n)$ 归并合并，复杂度是 $\mathcal O(n^2)$ 的，会 TLE 80pts。

可以构造每次合并一个单点的数据，这样每个点会合并 $\mathcal O(n)$ 次。

[记录](https://www.luogu.com.cn/record/40348932)

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

typedef long long ll;
const int N = 200001;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

int n,p[N],q1[N],q2[N],t; ll ans;

void Solve() {
	int x = read();
	if(x != 0) return void(p[++t] = x);
	int l = t + 1;
	Solve(); int m = t;
	Solve(); int r = t;

	int i = l, j = m + 1, c = l; ll s1 = 0;
	while(i <= m && j <= r) if(p[i] <= p[j]) q1[c++] = p[i++];
	else q1[c++] = p[j++], s1 += m - i + 1;
	while(i <= m) q1[c++] = p[i++];
	while(j <= r) q1[c++] = p[j++], s1 += m - i + 1;

	i = l, j = m + 1, c = l; ll s2 = 0;
	while(i <= m && j <= r) if(p[j] <= p[i]) q2[c++] = p[j++];
	else q2[c++] = p[i++], s2 += r - j + 1;
	while(j <= r) q2[c++] = p[j++];
	while(i <= m) q2[c++] = p[i++], s2 += r - j + 1;

	if(s1 < s2) {
		ans += s1;
		for(int i = l;i <= r;i++) p[i] = q1[i];
	} else {
		ans += s2;
		for(int i = l;i <= r;i++) p[i] = q2[i];
	}
	return;
}

int main() {
	n = read();
	Solve();
	std::printf("%lld\n",ans);
	return 0;
}
```

于是，问题变成了如何快速维护一定信息，使我们可以快速对于两个序列，求出两个序列分别对于另一个序列的逆序对数。

树上递归地合并和值有关的信息，线段树合并。

那么我们维护了这两个序列的权值线段树。

但是怎么求呢？

在合并的过程中计算。

对于线段树上每个点，维护其大小 $s$，其中左区间节点数量 $s1$，和右区间节点数量 $s2$。

这样我们合并完成一个节点时，将其左儿子中 $s2$ 的值和右儿子中 $s1$ 的值之积加入贡献即可。

这个方法的实质是在权值一维上再将序列分治。

至此，我们在 $\mathcal O(n\log n)$ 时间中解决了这个问题。

---

下面讲讲实现中的问题。

对于线段树上点的 $s1$ 和 $s2$ 值，都只是暂时的。在每一次合并中都一定会被重新计算。

该解法中似乎需要两次按不同顺序合并取小值，但是实际上合并之后的线段树结构是相同的，因此可以一次合并分别维护两个值，并直接使用原来的结点。

这样空间是 $\mathcal O(n\log n)$ 的，但是须稍大。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

typedef long long ll;
const int N = 200001;
const int LOGN = 19;
const int NODE = N * LOGN;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

int n,cnt; ll ans;
int s[NODE],s1[NODE],s2[NODE],lc[NODE],rc[NODE];

void New(int &rt,int x,int l,int r) {
	s[rt = ++cnt] = 1;
	if(l == r) return;
	int m = (l + r) >> 1;
	if(x <= m) New(lc[rt],x,l,m);
	else New(rc[rt],x,m + 1,r);
	return;
}

struct Pair {
	ll x,y;
	Pair(ll _x = 0,ll _y = 0) : x(_x), y(_y) {}
	friend Pair operator +(const Pair &x,const Pair &y) {
		return Pair(x.x + y.x,x.y + y.y);
	}
};

Pair Merge(int &x,int y,int l,int r) {
	if(!x || !y) {
		if(x) s1[x] = s[x], s2[x] = 0;
		else x = y, s2[x] = s[x], s1[x] = 0;
		return Pair();
	}
	if(l == r) return s1[x] += s1[y], s2[x] += s2[y], s[x] += s[y], Pair();
	int m = (l + r) >> 1;
	Pair r1 =  Merge(lc[x],lc[y],l,m);
	Pair r2 = Merge(rc[x],rc[y],m + 1,r);
	s1[x] = s1[lc[x]] + s1[rc[x]];
	s2[x] = s2[lc[x]] + s2[rc[x]];
	s[x] = s[lc[x]] + s[rc[x]];
	return Pair(r1.x + r2.x + 1ll * s2[lc[x]] * s1[rc[x]],r1.y + r2.y + 1ll * s1[lc[x]] * s2[rc[x]]);
}

int Solve() {
	int x = read();
	if(x != 0) {
		int rt = 0; New(rt,x,1,n);
		return rt;
	}
	int lc = Solve(), rc = Solve();
	Pair s = Merge(lc,rc,1,n);
	ans += std::min(s.x,s.y);
	return lc;
}

int main() {
	n = read();
	Solve();
	std::printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：L_M_ (赞：1)

这是一道线段树合并的棵题

每个节点开一个权值线段树，父亲的线段树由儿子的合并而来，在合并的过程中即可计算答案

这样我们递归处理，每一层只考虑跨越两颗子树的答案

考虑合并lx,rx两颗树，在交换之前，答案是
```
sum[rs[lx]] * sum[ls[rx]]
```
在交换之后，答案是
```
sum[ls[lx]] * sum[rs[rx]]
```
可以手推，十分易得

还有一个问题，这题卡内存，那么可以写个内存池
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#include<climits>
#include<algorithm>
using namespace std;
typedef int mainint;
typedef double db;
typedef long long ll;
#define il inline 
#define pii pair<ll,int>
#define mp make_pair
#define B cout << "breakpoint" << endl;
#define O(x) cout << #x << "  " << x << endl;
inline int read()
{
    int ans = 0,op = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') op = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        (ans *= 10) += ch - '0';
        ch = getchar();
    }
    return ans * op;
}
const int maxn = 5e5 + 5;
int ls[maxn],rs[maxn],tot;
int sum[maxn];
int n;
ll ans1,ans2,ans;
int st[maxn],top;
il void trash(int i)
{
	ls[i] = rs[i] = sum[i] = 0; st[++top] = i;
}
il void up(int i)
{
	sum[i] = sum[ls[i]] + sum[rs[i]];
}
void update(int &i,int l,int r,int x,int d)
{
	if(!i) i = !top ? ++tot : st[top--];
	if(l == r && l == x)
	{
		sum[i] += d;
		return;
	}
	int mid = l + r >> 1;
	if(x <= mid) update(ls[i],l,mid,x,d);
	else update(rs[i],mid + 1,r,x,d);
	up(i);
}
void merge(int &lx,int rx)
{
	if(!lx || !rx)  
	{ 
		lx = lx + rx; 
		//if(rx) trash(rx);
		return; 
	}
	sum[lx] = sum[lx] + sum[rx];
	ans1 += 1ll * sum[rs[lx]] * sum[ls[rx]];
	ans2 += 1ll * sum[ls[lx]] * sum[rs[rx]];
	merge(ls[lx],ls[rx]);
	merge(rs[lx],rs[rx]);
	trash(rx);
}
void solve(int &x)
{
	int t = read();
	int leftson,rightson;
	x = 0;
	if(t)
		update(x,1,n,t,1);
	else
	{
		solve(leftson); solve(rightson);
		ans1 = ans2 = 0;
		x = leftson; 
		merge(x,rightson);
		ans += min(ans1,ans2);
	}
}
int main()
{
	n = read();
	int x = 0;
	solve(x);
	cout << ans;
}


```

---

## 作者：mulberror (赞：1)

# 题目链接
[【BZOJ】](https://www.lydsy.com/JudgeOnline/problem.php?id=2212)  
[【洛谷】](https://www.luogu.org/problemnew/show/P3521)  
[【LOJ】](https://loj.ac/problem/2163)  
# 吐槽
~~粗鄙之语~~  
BZOJ的时间限制和空间限制都是洛谷的10倍，洛谷卡空间，LOJ卡时间。  
awsl~~
# 题解
由于是前序遍历，那么讨论一棵树上的逆序对的情况。    
* 两个节点都在左子树上  
* 两个节点都在右子树上  
* 两个节点分别在不同的子树上。  

前两种情况其实也可以归结于第三种情况。  
## 原因
因为两个节点不可能占据一个位置。    
根据容斥原理，为了保证答案的正确性，我们递归求解不能计算两遍相同的答案。   

-----
回到正题  
所以我们只需要讨论跨越两个子树的情况。  
很显然，左子树中的所有点的$dfs$序都比右子树的子树中的小。  
那么如果要交换，就是相反一下。  
比较容易可以想到对于每一个节点都先建立一个权值线段树。  
那么每一次的答案就从线段树的左子树和右子树中取最小值就可以了。  
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IOstream {
	#define gc getchar
	template <typename T> 
	inline void read(T &x) {
		x = 0; T fl = 1; char c = 0; 
		for (; c < '0' || c > '9'; c = gc()) 
			if (c == '-') fl = -1;
		for (; c >= '0' && c <= '9'; c = gc()) 
			x = (x << 1) + (x << 3) + (c ^ 48);
		x *= fl;
	}
	#undef gc
} using namespace IOstream;
typedef long long ll;
const int N = 4000005 + 6;
int n, cnt = 0, tot = 0; 
int rt[N]; 
ll ans, f, g;
struct node {
	int lc, rc, sz;
} tr[N];
int merge(int x, int y) {
	if (!x || !y) return x + y;
	f += 1ll * tr[tr[x].lc].sz * 1ll * tr[tr[y].rc].sz;
	g += 1ll * tr[tr[y].lc].sz * 1ll * tr[tr[x].rc].sz; 
	tr[x].lc = merge(tr[x].lc, tr[y].lc);
	tr[x].rc = merge(tr[x].rc, tr[y].rc);
	tr[x].sz += tr[y].sz; 
	return x; 
}
void ins(int nod, int l, int r, int k) {
	tr[nod].sz ++; 
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (k <= mid) tr[nod].lc = ++ tot, ins(tr[nod].lc, l, mid, k);
	else tr[nod].rc = ++ tot, ins(tr[nod].rc, mid + 1, r, k); 
}
#undef ls
#undef rs 
int dfs() {
	int w; read(w);
	if (w) {
		rt[++ cnt] = ++ tot; 
		ins(rt[cnt], 1, n, w);
		return rt[cnt]; 
	} else {
		int nod = merge(dfs(), dfs());
		ans += min(f, g);
		f = g = 0; 
		return nod; 
	}
}
int main() {
	read(n); ans = 0ll; 
	dfs();
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：iodwad (赞：1)

[欢迎访问我的博客](https://zcdhj.org/)

线段树合并 + 贪心（分治？

因为交换某个结点的左右子树只会改变当前子树中的叶子结点的位置，也就是说此时逆序对数只有子树中的这部分改变了，与其他叶子结点的逆序对都没有发生改变。所以，使得每个子树中的逆序对数最少是一个正确的贪心策略。

那么如何计算交换左右儿子与不交换的逆序对数？考虑对于每个结点维护一个值域线段树，在向上合并的过程中，当前线段树上结点范围 $[l,r]$ 会有左儿子线段树的 $[l,mid]$ 区间与右儿子的 $[mid + 1, r]$ 构成交换左右儿子的逆序对，左儿子 $[mid + 1, r]$ 与右儿子 $[l,mid]$ 会构成不交换情况下的逆序对，那么就可以在合并的过程中计算两种情况的逆序对数。

十分恶心的是这题卡空间，所以要记得垃圾回收和开 `long long`。

```cpp
#include <iostream>
#include <cstdio>

typedef long long LL;
#define int LL

const int MAXN = 2e5;

int n, ans, res1, res2;

struct Segtree {
    int sumv;
    Segtree *ch[2];
    Segtree() : sumv(0) {
        ch[0] = ch[1] = NULL;
    }
    Segtree(Segtree *ch1, Segtree *ch2, int _val) : sumv(_val) {
        ch[0] = ch1;
        ch[1] = ch2;
    }
};

inline int read() {
    register int x = 0;
    register char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

void insert(int pos, Segtree *&o, int l = 1, int r = n) {
    if(o == NULL) o = new Segtree;
    o -> sumv = o -> sumv + 1;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid) insert(pos, o -> ch[0], l, mid);
    else insert(pos, o -> ch[1], mid + 1, r);
}

Segtree *merge(Segtree *x, Segtree *y, int l = 1, int r = n) {
    if(x == NULL) return y;
    if(y == NULL) return x;
    if(l == r) return new Segtree(NULL, NULL, x -> sumv + y -> sumv);
    int mid = (l + r) >> 1;
    if((x -> ch[1] != NULL) && (y -> ch[0] != NULL)) res1 += x -> ch[1] -> sumv * y -> ch[0] -> sumv;
    if((x -> ch[0] != NULL) && (y -> ch[1] != NULL)) res2 += x -> ch[0] -> sumv * y -> ch[1] -> sumv;
    Segtree *res = new Segtree;
    res -> ch[0] = merge(x -> ch[0], y -> ch[0], l, mid);
    res -> ch[1] = merge(x -> ch[1], y -> ch[1], mid + 1, r);
    res -> sumv = x -> sumv + y -> sumv;
    delete x;
    delete y;
    return res;
}

Segtree *dfs() {
    int tmp = read();
    Segtree *t;
    if(tmp != 0) {
        t = new Segtree;
        insert(tmp, t);
    } else {
        t = merge(dfs(), dfs());
        ans += std::min(res1, res2);
        res1 = res2 = 0;
    }
    return t;
}

signed main() {
    n = read();
    dfs();
    printf("%lld\n", ans);
    return 0;	
}
```



---

## 作者：Missa (赞：0)

非线段树合并做法。复杂度多一只 `log`，但是好写。洛谷过得去，loj 过不去。

跳过不重要的部分，直达核心 —— 如何在递归时计算两棵子树互相的贡献？

题解区清一色线段树合并从值域角度考虑。但是显然启发式合并也能做啊。

考虑 dfs 完两个子节点后把小的合并到大的上。对每个节点维护一棵平衡树，从下往上合并时，把小树合并进大树中的同时计算答案，然后**直接让父亲继承大树**。这里我的做法是直接传指针，直接把指向原大树的指针传上去当作该树的指针。这样就做完了，细节看代码。

考虑复杂度。一个节点被从一棵树复制到另一棵树时所在子树大小至少加倍。因此一个节点至多被复制 $\log n$ 次，单次复杂度 $O(\log n)$，因此复杂度 $O(n \log^2 n)$。

注意到你需要在合并时求出某个平衡树有多少数小于给定数。这个用 `set` 不行，要上 `pbds`。

代码不到 `1k`，大部分是 `pb_ds`。

[这篇题解](https://www.luogu.com.cn/blog/vocalise/solution-p3521) 的归并做法和我本质一致。但是必须要保证**合并答案时复杂度仅与小树有关**才能做到 $O(n \log^2 n)$。

[这篇题解](https://www.luogu.com.cn/blog/75093/solution-p3521) 的 `dsu on tree` 是我的做法，写得好丑，但跑得好快。树状数组常数小 `pbds` 太多了。

```cpp
#include <cstdio>
#include <set>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define LL long long
using namespace std;
using namespace __gnu_pbds;
const int M = 5e5 + 5;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> s[M];
int cnt;
LL ans;
int build() {
    int x; scanf("%d", &x);
    int rt = ++cnt;
    if(x != 0) return s[rt].insert(x), rt;
    else {
        int l = build(), r = build();
        if(s[l].size() < s[r].size()) swap(l, r);
        LL tmp = 0, tot = 1ll * s[l].size() * s[r].size();
        for(auto u : s[r]) {
            if(s[l].lower_bound(u) == s[l].end()) tmp += s[l].size();
            else tmp += 1ll * s[l].order_of_key(*s[l].lower_bound(u));
        }
        for(auto u : s[r]) s[l].insert(u);
        ans += min(tmp, tot - tmp);
        return l;
    }
}
int main() {
    int n; scanf("%d", &n); build();
    printf("%lld\n", ans);
}
```

---

