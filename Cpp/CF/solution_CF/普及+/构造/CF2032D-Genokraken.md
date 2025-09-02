# Genokraken

## 题目描述

This is an interactive problem.

Upon clearing the Waterside Area, Gretel has found a monster named Genokraken, and she's keeping it contained for her scientific studies.

The monster's nerve system can be structured as a tree $ ^{\dagger} $ of $ n $ nodes (really, everything should stop resembling trees all the time $ \ldots $ ), numbered from $ 0 $ to $ n-1 $ , with node $ 0 $ as the root.

Gretel's objective is to learn the exact structure of the monster's nerve system — more specifically, she wants to know the values $ p_1, p_2, \ldots, p_{n-1} $ of the tree, where $ p_i $ ( $ 0 \le p_i < i $ ) is the direct parent node of node $ i $ ( $ 1 \le i \le n - 1 $ ).

She doesn't know exactly how the nodes are placed, but she knows a few convenient facts:

- If we remove root node $ 0 $ and all adjacent edges, this tree will turn into a forest consisting of only paths $ ^{\ddagger} $ . Each node that was initially adjacent to the node $ 0 $ will be the end of some path.
- The nodes are indexed in a way that if $ 1 \le x \le y \le n - 1 $ , then $ p_x \le p_y $ .
- Node $ 1 $ has exactly two adjacent nodes (including the node $ 0 $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/e8258012a39acd46c9074838efef9914b6897d4b.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/206bea28ad893e4b88d7080ccd68226695dddca4.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/62f37c6d61a34178ff5087ddf19cef6e4de6bb74.png)The tree in this picture does not satisfy the condition, because if we remove node $ 0 $ , then node $ 2 $ (which was initially adjacent to the node $ 0 $ ) will not be the end of the path $ 4-2-5 $ .The tree in this picture does not satisfy the condition, because $ p_3 \le p_4 $ must hold.The tree in this picture does not satisfy the condition, because node $ 1 $ has only one adjacent node.Gretel can make queries to the containment cell:

- "? a b" ( $ 1 \le a, b < n $ , $ a \ne b $ ) — the cell will check if the simple path between nodes $ a $ and $ b $ contains the node $ 0 $ .

However, to avoid unexpected consequences by overstimulating the creature, Gretel wants to query at most $ 2n - 6 $ times. Though Gretel is gifted, she can't do everything all at once, so can you give her a helping hand?

 $ ^{\dagger} $ A tree is a connected graph where every pair of distinct nodes has exactly one simple path connecting them.

 $ ^{\ddagger} $ A path is a tree whose vertices can be listed in the order $ v_1, v_2, \ldots, v_k $ such that the edges are $ (v_i, v_{i+1}) $ ( $ 1 \le i < k $ ).

## 说明/提示

In the first test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/f881123b596891d36ab778596441f15ad95a02ea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .

In the second test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/33f1d468944f56ba6a97f7e156678062fb607fea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .
- The answer to "? 2 4" is $ 0 $ . This means that the simple path between nodes $ 2 $ and $ 4 $ doesn't contain node $ 0 $ .

In the third test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/80e7fbd696eda68303e33490520aebb364943d67.png)

## 样例 #1

### 输入

```
3
4

1

5

1

0

9```

### 输出

```
? 2 3

! 0 0 1

? 2 3

? 2 4

! 0 0 1 2

! 0 0 0 1 3 5 6 7```

# 题解

## 作者：elpsconr (赞：5)

## 提示1：
我们需要构建一颗除根结点外最多只有两个度的树。即每个树的结点(除叶子结点和根结点外)只有一个直接相连连的子结点,不难发现要我们构建的也就是若干条树链。

## 提示2：
当满足 $x \lt y$ 时, $ px \le py $ ,不难发现想要满足这个条件，就需要构建一颗层序遍历单调不减的树。

## 提示3：
是这题误导我们的地方,因为这句话,导致我赛时一直尝试从 $ 1 $ 出发正向构建这棵树。睡一觉起来重新看这题的时候发现似乎从后往前构建会更加简单。

就是说从最后一个结点开始考虑。$ n - 1 $ 的父结点肯定是小于等于 $ n - 2 $ 的，取 $ f = n - 2 , i = n - 1 $ 倒着枚举，如果出现 $ i $ 和 $ f $ 之间有 $ 0 $ 就去访问更小的 $ f $ 。每个 $ f $ 只有一个直接相连的子结点，故找到直连子结点后也要更新父结点。
## 询问：
根据提示2，可知访问更小的结点时，其父结点只减不增。最多询问 $ n - 2 $ $ \lt $ $ 2 n - 6 $ 。故可通过此题，感觉已经是最少询问次数了，而且也比较容易理解。

## 注意：
父结点最小只能是 $ 0 $。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define tul tuple<int,int,int>
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rep_(i,a,b) for(int i=a;i>=b;--i)
#define all(x) x.begin(),x.end()
#define bp(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctz(x)
#define cy cout<<"YES"<<endl
#define cn cout<<"NO"<<endl
#define lc (rt<<1)
#define rc (rt<<1|1)
mt19937_64 rnd(time(0));
const int N=3e5+5,yyx=1e9+7;
vector<PII> to[N];
int n,k,a[N];
inline int mod(int x){
  return (x%yyx+yyx)%yyx;
}
inline int cmin(int &x,int y){
  return x>y?x=y,1:0;
}
inline int cmax(int &x,int y){
  return x<y?x=y,1:0;
}
int ask(int x,int y){
  cout<<"? "<<x<<" "<<y<<endl;
  int res;cin>>res;
  return res;
}
void show(){
  cout<<"! ";
  rep(i,1,n-1) cout<<a[i]<<" ";
  cout<<endl;
}
inline void solve(){
  cin>>n;
  rep(i,1,n-1) a[i]=0;
  int l=n-2;
  rep_(i,n-1,1){
    while(l>0&&ask(i,l)) l--;
    a[i]=max(l--,0ll);//注意父结点最小只能是0，故取max
  }
  show();
}
signed main(){
  cin.tie(0)->sync_with_stdio(0);
  //freopen("D://321//in.txt","r",stdin);
  //freopen("D://321//out.txt","w",stdout);
  int _=1;
  cin>>_;
  while(_--)
  solve();
  return 0;
}
```

---

## 作者：tai_chi (赞：3)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18523933) 中阅读。

#### 题意

交互题，有一棵 $n$ 个点的树，编号从 $0$ 到 $n-1$，不知道形态，但已知以下性质：

- 如果删除节点 $0$，则树会变成一组链。
- 记 $p_x$ 表示 $x$ 节点的父亲，若 $1 \le x \le y \le n-1$，则 $p_x \le p_y$。
- 节点 $1$ 的度数为 $2$，且节点 $0$ 与节点 $1$ 相连。

每次询问两个点，交互库返回这两个点之间的简单路径是否包含节点 $0$。询问次数不能超过 $2 \times n-6$。

还原树的最终形态。

#### 分析

$1$ 号点被强调了特殊性质，我们从 $1$ 号点入手。

首先依次询问 $(1,2),(1,3), \dotsb ,(1,t)$ 直到答案为 $1$，可以确定这个 $t$ 就是 $1$ 的儿子，且 $[2,t-1]$ 的父亲都是 $0$，这利用了性质二。

之后的点只需要维护一个指针指向当前测试的父亲节点，双指针移动分别确定即可。

第一部分询问次数为 $t-2 \le n-3$，第二部分最坏情况指针从 $2$ 移动到 $n-2$，询问次数为 $n-3$，加起来是 $2n-6$，正好满足题目要求。

```cpp
int ask(int x,int y)
{
	cout<<"? "<<x<<" "<<y<<endl;
	int res; cin>>res;
	assert(res!=-1);
	return res;
}

void solve()
{
	int n; cin>>n;
	vector<int> p(n+5,0);
	p[1]=0;
	int t=0;
	for(int i=2;i<=n-1;i++)
	{
		int r=ask(1,i);
		if(r==0){t=i; break;}
		else p[i]=0;
	}
	p[t]=1;
	int now=2;
	for(int i=t+1;i<=n-1;i++)
	{
		while(ask(now,i)==1) now++;
		p[i]=now;
		now++;
	}
	cout<<"! ";
	for(int i=1;i<=n-1;i++) cout<<p[i]<<" ";
	cout<<endl;
}
```

---

## 作者：arrow_king (赞：2)

询问方式和树结构的特殊性提示性很强，我们分开考虑。

# 询问

查询两个点之间的路径是否经过 $0$，联想树的结构我们不难发现这个东西带来的信息：可以判定两个点是否属于同一条链。因为不属于同一条链的点之间一定经过 $0$。

# 树结构

题目中所说的树以 $0$ 为根，下面挂着若干条链，且 $1$ 子树大小至少为 $1$。这能说明两件事：

1. 如果 $p_i,p_j\neq 0$，那么 $\color{black}p_i\color{red}<\color{black} p_j$。因为除了 $0$ 的节点最多只能有一个儿子。
2. 我们可以用 $n-2$ 次操作**完全还原** $1$ 的子树。只需要查询每个 $p$ 是否和 $1$ 在同一条链即可。因为父亲单增，所以节点编号一定升序。

# 双指针判定剩余节点

利用节点编号与父亲编号**双单调**的性质，不难想到用双指针维护当前点以及可能的父亲，每次查询可能的父亲编号以及当前节点是否在同一条链上，如果是就把它挂在当前链底（需要维护链上最后的节点）。特别的，记 $1$ 的儿子是 $u$，那么 $2\sim u-1$ 的父亲都是 $0$。

考虑总操作次数：儿子指针 $v$ 从 $u+1$ 出发，终结于 $n-1$，且中间节点如果是 $1$ 这条链的点还可以被跳过，因此最多有效移动 $n-4$ 次；父亲指针 $f$ 从 $2$ 出发，终结于 $n-2$（因为要保持 $f<v$），同时一个父亲节点只会被查询一次，因此双指针过程最多查询 $n-3$ 次。考虑 $f$ 和 $v$ 有效次数取最小值，得到上界 $n-4$。

因此我们得到了查询次数的上界是 $2n-6$，可以~~卡线~~通过本题。

## $1$ 下面的节点为啥必须要有

上面的严格单调性只是考虑了不是 $0$ 儿子的节点，因此需要先找出 $0$ 的所有儿子，而 $1$ 下面存在节点 $u$ 就保证可以找到所有 $0$ 的儿子都夹在 $2$ 和 $u-1$ 中间。

# 代码

赛后补题，写的很丑，凑合看吧。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 10005
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
il int ask(int u,int v) {
	printf("? %d %d\n",u,v);fflush(stdout);
	int tmp=read();
	if(tmp==-1) exit(0);
	return tmp;
}
int n;
int fa[N],nxt[N],fst;
il void mian() {
	n=read();
	for(int i=2;i<=n;i++) fa[i]=-1;
	for(int i=2,lst=1;i<=n-1;i++) {
		int res=ask(i,1);
		if(!res) {
			fa[i]=lst,lst=i;
			if(!fst) fst=i;
		}
	} 
	for(int i=2;i<fst;i++) fa[i]=0;
	for(int i=fst+1,f=2;i<=n-1;i++) {
		if(fa[i]!=-1) {f=fa[i];continue;}
		while(f<i-1&&ask(f,i)) f++;
		fa[i]=f;
		f++;
	}
	printf("! ");
	for(int i=1;i<=n-1;i++) printf("%d ",fa[i]);putchar('\n');
	fflush(stdout);
	fst=0;
}
il void clean() {
	for(int i=2;i<=n-1;i++) fa[i]=-1,nxt[i]=0;
	fst=0;
}
int main() {
	int t=read();
	while(t--) {
		mian();
		clean();
	}
	return 0;
}

```

---

## 作者：littlebug (赞：1)

## Solution

因为 $1$ 固定与 $0$ 相连，所以从这里下手，先想到可以用 $n-2$ 次询问求出来每个点是否在 $1$ 的子树中，然后根据性质 $3$ 就得到了 $1$ 的子树（当然是一条链）。

因为性质 $2$ 和 $3$ 很可爱，所以 $(1,son(1))$（显然 $1$ 只有一个子节点）内的点的父亲一定是 $0$。

因为性质 $3$ 很可爱，所以设 $1$ 的子树中相邻两个节点为 $l,r$（$l$ 为父节点），则 $(l,r)$ 内的节点的父节点一定为 **非节点** $\bf 1$ 的 $\bf 0$ **的其它子树**的**上一层的节点**，并且**从左往右**依次排开（但不一定上一层每一个节点都有子节点）。这个很容易证的。于是对于这一层每个节点挨个向上一层匹配即可。

对于询问次数，因为 $0,1,son(1)$ 三个点不用询问，所以最多 $n-3$ 次询问，比要求多了一个，但是可以证明到不了 $n-3$：考虑 $=n-3$ 的情况，因为与 $0$ 相连的点不用询问，所以除 $1$ 以外的所有点都不与 $0$ 相连，于是所有点都在 $1$ 的那一棵子树上了，也就是不需要询问了。所以询问次数必定 $< n-3$。再加上第一步操作的 $n-2$ 次询问，总次数 $< n-5$，刚好卡满（于是确定了这是正解）。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define int long long
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rpe(i,a,b) for(int i=(a);i>=(b);--i)
#define pb emplace_back
using namespace std;

const int MAXN=1e4+5;
int n,p[MAXN];
vector <int> base,v;

il bool q(int a,int b)
{
	cout<<"? "<<a<<' '<<b<<'\n'; cout.flush();
	int res; cin>>res;
	return res==1;
}

il void solve()
{
	cin>>n;
	
	vector<int>().swap(base);
	vector<int>().swap(v);
	rep(i,0,n+1) p[i]=-1;
	
	rep(i,2,n-1) q(i,1) ? v.pb(i) : base.pb(i); //n-2 Q
	
	p[1]=0;
	rep(i,0,(int)(base.size())-1) p[base[i]]=(i ? base[i-1] : 1);
	
	
	vector <int> ps,nps;
	rep(i,2,base[0]-1) p[i]=0,ps.pb(i);
	
	//<n-3 Q
	int l,r,pos;
	rep(i,1,(int)(base.size())-1)
	{
		l=base[i-1]+1,r=base[i]-1;
		
		pos=l;
		rep(j,0,(int)(ps.size())-1)
		{
			if(!q(ps[j],pos)) p[pos]=ps[j],nps.pb(pos),++pos;
			if(pos>r) break;
		}
		
		ps=nps,vector<int>().swap(nps);
	}
	
	int ind=base.back()+1;
	if(ind<=n-1)
	{
		while(ind<=n-1)
		{
			rep(j,0,(int)(ps.size())-1)
			{
				if(!q(ps[j],ind)) p[ind]=ps[j],nps.pb(ind),++ind;
				if(ind>n-1) break;
			}
			
			ps=nps,vector<int>().swap(nps);
		}
	}
	
	cout<<"! "; rep(i,1,n-1) cout<<p[i]<<' '; cout<<'\n'; cout.flush();
}

signed main()
{
	ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
	int T; cin>>T; while(T--) solve();
	return 0;
}
```

---

## 作者：xiaoyang222 (赞：0)

询问 $n-2$ 次的做法，$n$ 最小的情况刚好符合。

首先第一个限定可以从跟把树分成很多条链，一条链上从上到下的编号一定是上升的。

可以考虑这个策略。

> 编号从 $n-1$ 开始确定每一位，每次再用一个指针 $fa$，一次询问 $i$ 点，$fa$ 一直减一，知道他们两个不经过 $0$，$fa$ 一定是 $i$ 点的 $fa$，当 $fa$ 是 $0$，停止。

首先证明最后一句，因为只有这个 $fa$ 是最大与 $i$ 在一条链上的。

因为第三个约定，可以知道一直减 $fa$ 是一定可以的，因为 $i$ 也是从大到小确定。

不知道第二个约定干嘛的。

代码。

```cpp
#include <iostream>
using namespace std;
const int N=1e6+5;
int p[N];
int query(int a,int b){
	if (a>b) return query(b,a);
	cout<<"? "<<a<<" "<<b<<endl; 
	int t;cin >> t;
	return t;
}
void solve(){
	int n;
	cin >> n;
	cout.flush(); 
	for (int i=0;i<n;++i) p[i]=0;
	int fa=n-2,t=n-1;
	while (t){
		while (fa>0 && query(t,fa)) --fa;//我们相约在一条链上 
		p[t]=max(fa--,0);//你答应只属于我，对吗？
		--t;
		cout.flush(); 
	}
	cout<<"! ";for (int i=1;i<n;++i) cout<<p[i]<<" ";
	cout<<endl;
	cout.flush(); 
}
int main(){
	int T;
	cin >> T;
	for (int _=0;_<T;++_) solve();
	return 0;
}
```

---

## 作者：gyyyyx (赞：0)

观察题目可知树的结构是 $0$ 节点下面挂着多条链的形式。

由于询问 $0$ 节点没有意义，那么实际上每次询问的是两个节点是否在同一条链上。

而我们最终只需要知道每条链上有哪些节点就行了。

由于 $p$ 数组单调不降，那么对于任意两个点 $x,y$ 若 $p_x=p_y=0$，那么所有编号在 $[x,y]$ 的点 $u$，$p_u=0$。

也就是直接挂在 $0$ 节点下面的节点必然一个前缀。

由于节点 $1$ 必然直接挂在 $0$ 节点下面，并且必然有儿子，那么我们可以从 $u=2$ 开始不断询问 `? 1 u`，直到回答为 $0$ 才停止。

这样就找到了所有直接挂在 $0$ 节点下面的节点（假设有 $k$ 个）。

询问次数为 $n-3$（询问了 $2\sim n-2$）。

对于剩余节点，显然我们可以询问 $k$ 次来知道它属于哪条链。

但询问次数和复杂度都会超标。

这时候 $p$ 数组单调不降的性质再次排上用场。

我们可以弄一个队列，用于存放下一次询问的节点的可能的父亲节点。

对于某个节点 $u$，从队头开始问，`? q[h] u`，若回答为 $1$ 则将队头的点删去（`++h`），然后继续询问，直到回答为 $0$ 才停止。

对于回答为 $1$ 的节点，由于 $u$ 与该节点（假设为 $x$）不同链，那么有 $p_u>x$，因此 $\forall v>u,p_v>x$，因此可删去。

在每次确定完一个节点的父亲后，因为一个节点最多只有一个儿子，那么也要将父亲删去，同时将该节点插入队列。

这里还可以加一个优化：如果队列里只有一个点，说明后面的点都和该点同链，可以不用询问下去。

这样每个 $2$ 之后节点当且仅当出队时询问一次，询问次数是 $n-3$（询问了 $2\sim n-2$）。

总次数刚好为 $2n-6$。

代码：

```cpp
#include<bits/stdc++.h>
#define N 10005
using namespace std;
inline bool Ask(int x,int y){
	cout<<"? "<<x<<" "<<y<<endl;
	bool t;cin>>t;return !t;
}
int T,n,q[N],h,t,f[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n;int u(2);
		for(h=1,t=0;u<n;++u){
			q[++t]=u;
			if(Ask(1,u)){f[u]=1;break;}
			f[u]=0;
		}
		for(++u;u<n;++u){
			while(!Ask(q[h],u)) ++h;
			f[q[++t]=u]=q[h++];
			if(t==h) break;
		}
		for(++u;u<n;++u) f[u]=u-1;
		cout<<"! ";
		for(int i(1);i<n;++i) cout<<f[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：2022dyx (赞：0)

# 简要题意
给定一个树，满足以下性质：
- 性质 $1$：在 $0$ 号节点的下方挂着若干条链。
- 性质 $2$：对于节点编号较大的点，父节点编号也较大。
- 性质 $3$：$1$ 号节点不是叶子。
  
你可以进行 $2n-6$ 次询问，对于每次询问，你可以得到两个点是否在同一个链中。
# 暴力
由性质 $2$ 不难得到，**在同一个链中，节点编号一定递增。** 

因此，对于每一个节点,我们可以依次询问是否与之前的某一个节点在同一个链中。若是则可直接挂在链尾。若均不在同一链中，则单开一条链。时间复杂度 $O(n^2)$，询问量约 $O(n^2)$。
# 正解
考虑将整个过程分成两部分：节点 $1$ 没有儿子时和节点 $1$ 有儿子时。

注：以下内容中 $i$ 指当前节点，$f_i$ 指 $i$ 节点的父节点。
## Part 1
可以直接询问节点 $1$ 和 $i$。若在同一链中，则令 $f_i = 1$，直接进入 `Part 2`；否则令 $f_i = 0$，即单开一条链。

因为若将节点 $i$ 接入原有其他链中，则一定有 $f_i \gt 1$，那么后面的节点都无法再成为节点 $1$ 的儿子了，与性质 $3$ 矛盾。
## Part 2
考虑按链尾节点的编号从小到大排序。设当前链尾编号为 $j$，则可询问 $i$ 和 $j$。若在同一链中，则令 $f_i = j$，否则一定有 $f_i > j$。此时后面的节点都无法再成为节点 $j$ 的儿子了，故可以直接删掉节点 $j$。

易知此过程可用优先队列维护链尾节点，时间复杂度为 $O(n \log{n})$。
## 询问量证明
设在 `Part 1`中操作了 $m$ 个节点，则共出现 $m$ 条链。这 $m$ 条链最多被删去 $m-1$ 条，则最大询问量为 $2m-1$。

除去节点 $0$ 和节点 $1$ 后，共剩余 $n-2$ 个节点。再去除 `Part 1` 中操作的 $m$ 个节点，在 `Part 2` 中共剩余 $n-m-2$ 个节点，忽略掉已经算过的删除结点的代价，共需 $n-m-2$ 次询问确定位置。故最大总询问量为 $(2m-1)+(n-m-2)=n+m-3$。
### Case 1
若 $m$ 取最大值 $n-2$，则意味着所有节点均用于 `Part 1`，那么不会有任何一条链被删除，询问量为 $n-2$。
### Case 2
若 $m \le n-3$，则有最大询问量 $n+m-3 \le n+(n-3)-3=2n-6$，可以通过本题。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int t, n, ans[N];
priority_queue <int, vector <int>, greater <int> > q;
signed main() {
	cin.tie(0) -> sync_with_stdio(false);
	cin >> t;
	memset(ans, 0, sizeof ans);
	while(t--) {
		while(q.size()) q.pop();
		cin >> n;
		bool flg = false, op;
		for (int i = 2; i < n; ++i) {
			if (!flg) { // Part 1
				q.push(i);
				cout << '?' << ' ' << 1 << ' ' << i << endl;
				cin >> op;
				ans[i] = flg = !op;
			}
			else { // Part 2
				while(q.size()) {
					int tp = q.top();
					q.pop();
					cout << '?' << ' ' << tp << ' ' << i << endl;
					cin >> op;
					if (!op) {
						q.push(i);
						ans[i] = tp;
						break;
					}
				}
			}
		}
		cout << '!' << ' ';
		for (int i = 1; i < n; ++i) cout << ans[i] << ' ';
		cout << endl;
	}
}
```

---

