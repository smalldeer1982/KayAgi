# Construct the Binary Tree

## 题目描述

You are given two integers $ n $ and $ d $ . You need to construct a rooted binary tree consisting of $ n $ vertices with a root at the vertex $ 1 $ and the sum of depths of all vertices equals to $ d $ .

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. A parent of a vertex $ v $ is the last different from $ v $ vertex on the path from the root to the vertex $ v $ . The depth of the vertex $ v $ is the length of the path from the root to the vertex $ v $ . Children of vertex $ v $ are all vertices for which $ v $ is the parent. The binary tree is such a tree that no vertex has more than $ 2 $ children.

You have to answer $ t $ independent test cases.

## 说明/提示

Pictures corresponding to the first and the second test cases of the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/514e626aa001052fb71d69f413a53a8e6f0cb5f0.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/6407c12a699d89084b087667ed6f21f3aeed074d.png)

## 样例 #1

### 输入

```
3
5 7
10 19
10 18```

### 输出

```
YES
1 2 1 3 
YES
1 2 3 3 9 9 2 1 6 
NO```

# 题解

## 作者：万弘 (赞：16)

为啥$n,d\le 5000$啊，我搞了个线性做法

首先最小值是很好求的：构建一棵满二叉树。令$fa(i)=\lfloor\frac{i}{2}\rfloor$即可。  
同时，最大值显然是链的情况。  
对于一般情况，考虑从满二叉树向链调整。每次把编号最大的，不在链上的点挂到链上。假设现在考虑$i$，链的最下端是$pos$。

若需要增加的深度$rest\le dep(pos)+1-dep(i)$，那么$i$需要成为$pos$的第 $dep(pos)+1-dep(i)-rest$个父亲，这里直接暴力跳，因为只会跳这一次；否则直接让$i$成为$pos$的儿子，令$rest$减去$dep(pos)+1-dep(i)$,继续考虑下一个点。（注意如果点在链上就不移动了）

我这里取$1,2,4,8,16...(2^x)$作为初始的链。  
时间复杂度显然$\mathcal O(n)$
```cpp
/**********/
#define MAXN 200011
ll fa[MAXN],dep[MAXN];
void work()
{
    ll n=read(),sum_dep=read(),cur=0,pos;
    dep[0]=-1;
    for(ll i=1;i<=n;++i)
    {
        fa[i]=i>>1;dep[i]=dep[i>>1]+1;cur+=dep[i];
        if((i&(i-1))==0)pos=i;
    }
    sum_dep-=cur;
    if(sum_dep<0){puts("NO");return;}
    if(sum_dep==0)
    {
    	puts("YES");
        for(ll i=2;i<=n;++i)printf("%lld ",fa[i]);
        puts("");
        return;
    }
    for(ll i=n;i;--i)
    {
        if((i&(i-1))==0)continue;
        sum_dep-=dep[pos]+1-dep[i];
        if(sum_dep<=0)
        {
            while(sum_dep)pos=fa[pos],++sum_dep;
            sum_dep=0;
            fa[i]=pos;break;
        }
        fa[i]=pos,dep[i]=dep[pos]+1,pos=i;
    }
    if(sum_dep)puts("NO");
    else
    {
    	puts("YES");
        for(ll i=2;i<=n;++i)printf("%lld ",fa[i]);
        puts("");
    }
    
}
int main()
{
    ll t=read();
    while(t--)work();
}
```

---

## 作者：C　C　A (赞：11)

# $CF1311E\ Construct\ the\ Binary\ Tree's\ Solution$
						
$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad \qquad \qquad \qquad \qquad By$ [$CCA$](https://www.luogu.com.cn/user/78645)

## $Problem$

$\qquad$构造一颗$n$个点，个点深度之和为$d$的二叉树。

## $Solution$

$\qquad$首先，我们考虑什么时候无解，显然，当且仅当$\quad sum > d\quad or\quad d > n * (n - 1)\ /\  2$,其中$sum=\sum_{i=1}^n deep(i)_{min}$。

$\qquad$然后，我们从判断不合法的情况中的得到了启发，我们可以先构造一颗$sum$最小的数，再一步一步移动其中的某一结点，最终使$sum=d$。

$\qquad$最后就是本题的难点——代码。我们记一个$tree$数组表示每一层有哪些结点，然后记$Max=max\{deep(i)\}'s\ id$，说人话就是满足可移动条件的深度次大的结点，将它移动到下一层。

$\qquad$输出的话就比较简单了，直接用线段树中的套路，令$LS=now<<1\quad and\quad RS=now<<1|1$即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e3 + 10;

int T , n , d , p[N] , dep[N] , tree[N][N] , cnt[N] , sum , Max;

int main(){
	scanf("%d" , &T); while(T--){
		memset(p , 0 , sizeof(p));
		memset(cnt , 0 , sizeof(cnt));
		dep[1] = sum = Max = 0;
		scanf("%d %d" , &n , &d);
		tree[0][++cnt[0]] = 1;
		for(int i = 1; i <= n; i++){
			int LS = i << 1 , RS = i << 1 | 1;
			if(LS <= n) dep[LS] = dep[i] + 1 , tree[dep[LS]][++cnt[dep[LS]]] = LS , sum += dep[LS] , Max = max(Max , dep[LS]);
			if(RS <= n) dep[RS] = dep[i] + 1 , tree[dep[RS]][++cnt[dep[RS]]] = RS , sum += dep[RS] , Max = max(Max , dep[RS]);
		}
		if(sum > d || d > n * (n - 1) / 2){ puts("NO"); continue; }
		while(sum < d){
			for(int i = Max; i >= 0; i--){
				if(cnt[i] >= 2 && cnt[i + 1] < (cnt[i] - 1) * 2){
					tree[i + 1][++cnt[i + 1]] = tree[i][cnt[i]] , cnt[i]-- , sum++;
					Max = max(Max , i + 1); break;
				}
			}
		}
		for(int k = 0; k < Max; k++)
			for(int i = 1; i <= cnt[k]; i++){
				int LS = 2 * (i - 1) + 1 , RS = 2 * (i - 1) + 2;
				if(LS <= cnt[k + 1]) p[tree[k + 1][LS]] = tree[k][i];
				if(RS <= cnt[k + 1]) p[tree[k + 1][RS]] = tree[k][i];
			}
		puts("YES");
		for(int i = 2; i <= n; i++) printf("%d " , p[i]);
		puts("");
	}
	return 0;
}
```

自认为码风还是比较清奇可看的，大家可以对着$Solution$仔细看一下。

最后，[$This\ is\ my\ blog$](https://www.luogu.com.cn/blog/A66-888/) , 有兴趣的可以逛一下，应该能有所收获。

---

## 作者：Iam1789 (赞：6)

很水的一个入门构造了。

首先判断有无解，发现深度和最大的情况为链，最小的情况为一颗完全二叉树，判断 $d$ 是否在这个范围内就可以了。

然后考虑将某个点的父亲从 $u$ 改接到 $v$ 对答案的贡献，手玩一下，不难发现这个贡献为 $depth_v-depth_u$。

再考虑树的初始状态。~~由于从完全二叉树开始维护太复杂了~~由于 $n \leq 5000$，可以暴力过去，所以我们从一条链开始维护。

接下来开始构造。进行多次操作，每次操作选择深度最大的节点 $u$，不难发现这一定是一个叶子节点，遍历整棵树，找到一个节点 $v$，使得将 $u$ 接到 $v$ 上后满足：

1. 新树依然满足题意（依然是一颗二叉树）。
2. 新树节点的深度和依然大于或等于 $d$。
3. 在满足以上两个条件下使得新树节点的深度和于 $d$ 的差最小。

每次操作显然是可以在 $\text{O}(n)$ 的时间复杂度内完成。由于每次操作可以对答案产生的最大贡献平均为 $ \frac{1}{2}n$，而链的深度和为 $\frac{1}{2}n(n-1)$，因此树的深度和达到 $d$，最多只会进行约 $n$ 次操作。所以整个代码最坏复杂度为 $\text{O}(n^2)$。

代码：
```
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0;
	char c=getchar();
	while(c<'0'||c>'9')
	c=getchar();
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s;
}
int T;
int n,D;
int fa[1000007];
priority_queue <pair<int,int>> q;
int sonum[100007];
int depth[100007];
int main()
{
	T=read();
	while(T--)
	{
		n=read(),D=read();
		int minn=0,k=0,d=1,sum=0;
		while(sum+d<=n)
		{
			minn+=k*d;
			sum+=d;
			d*=2;
			++k;
		}
		minn+=(n-sum)*k;
		int maxn=n*(n-1)/2;
		if(D<minn||D>maxn)
		{
			puts("NO");
			continue;
		}
		puts("YES");
		depth[1]=0;
		for(int i=2;i<=n;++i)
		fa[i]=i-1,sonum[i-1]=1,depth[i]=depth[fa[i]]+1;
		sonum[n]=0;
		int num=maxn-D;
		q.push(make_pair(depth[n],n));
		while(num)
		{
			int u=q.top().second;
			q.pop();
			int maxnn=-5007,maxd;
			for(int i=1;i<=n;++i)
			{
				if(sonum[i]>1)
				continue;
				int c=depth[u]-depth[i]-1;
				if(c>maxnn&&c<=num)
				{
					maxnn=c;
					maxd=i;
				}
			}
			num-=maxnn;
			--sonum[fa[u]];
			if(!sonum[fa[u]])
			q.push(make_pair(depth[fa[u]],fa[u]));
			fa[u]=maxd;
			depth[u]=depth[fa[u]]+1;
			++sonum[fa[u]];
			q.push(make_pair(depth[u],u));
		}
		for(int i=2;i<=n;++i)
		printf("%d ",fa[i]);
		putchar('\n');
		while(!q.empty())
		q.pop();
	}
	return 0;
}
```


---

## 作者：1saunoya (赞：4)

膜这场比赛的 $rk1$ 
[$\color{black}A\color{red}{lex\_Wei}$](https://www.luogu.com.cn/user/123294)


这题应该是这场比赛最难的题了

容易发现，二叉树的下一层不会超过这一层的 $2$ 倍，所以我们先构造出来一颗尽量满的二叉树，然后慢慢向下调整，调整的方法是从最上面一个一个弄下来。

然后你慢慢调整的复杂度最多是 $d$ ，复杂度 $O(d)$ 


```cpp
#include <bits/stdc++.h>
using namespace std ;
const int maxn = 5e3 + 5;
int n , d , p[maxn] , fa[maxn] ;
vector < int > dep[maxn] ;

signed main() {
	int t;
	cin >> t ;
	while(t --) {
		memset(p , 0 , sizeof(p)) , memset(fa , 0 , sizeof(fa)) ;
		cin >> n >> d ;
		int sum = 0 , bs = 0 ;
		for(int i = 1 ; i <= n ;) {
			int rem = min(n - i + 1 , 1 << bs) ;
			p[bs] = rem , sum += rem * bs; 
			i += rem , bs ++ ;
		}
		if(sum > d) {
			puts("no") ;
			continue ;
		}
		int pos = bs; 
		while(sum < d) {
			int k = 0 ;
			for(int i = 1 ; i <= n ; i ++) 
				if((p[i] - 1) * 2 >= p[i + 1] + 1) {
					k = i ;
					break ;
				}
			if(! k) 
				break ;
			sum ++ , p[k] -- , p[k + 1] ++ ;
		}
		if(sum < d) {
			puts("no") ;
			continue ;
		}
		puts("yes") ;
		int cnt = 1 ;
		for(int i = 0 ; i <= n ; i ++)
			dep[i].clear() ;
		dep[0].push_back(1);
		dep[0].push_back(1);
		for(int i = 1 ; i <= n ; i ++) {
			while(p[i] --) {
				fa[++ cnt] = dep[i - 1].back() ;
				dep[i].push_back(cnt) ;
				dep[i].push_back(cnt) ;
				dep[i - 1].pop_back() ;
			}
		}
		for(int i = 2 ; i <= n ; i ++) 
			cout << fa[i] << ' ' ;
		cout << '\n' ;
	}	
	return 0 ;
}
```

---

## 作者：ix35 (赞：2)

这题由于 $n,d$ 都比较小，所以暴力即可。

考虑将 $solve(n,d)$ 定义为求一个 $n$ 个点的二叉树，深度之和为 $d$。

那么枚举左右子树的大小和深度和，设左子树大小为 $s$，深度和为 $t$，那么我们要分治 $solve(s,t)$ 和 $solve(n-1-s,d-(n-1)-t)$，这里比较显然就不多说了。

问题是，我们怎么知道这种递归是否可行呢？如果递归到底的话就相当于 DFS，复杂度显然是指数级别的。

因此，我们要考虑 $solve(n,d)$ 是否可能，即求出 $n$ 个点的二叉树的最小和最大深度和，看看 $d$ 是否在这范围中。

最小深度和：即完全二叉树，可以 $O(\log n)$ 计算（实际上也可以 $O(1)$ 计算）。

最大深度和：即链，可以 $O(1)$ 计算。

于是我们枚举 $s$，判断一下 $s$ 和 $n-1-s$ 个结点的左右子树分别取最大或最小，能否使得 $d$ 卡在这个范围中间，即可判定是否可行。

此时不能再枚举 $t$，否则又变成了指数级。

设 $min(n)$ 表示 $n$ 个点的二叉树的最小深度和，$max(n)$ 表示最大深度和，那么：

1. $min(s)+max(n-1-s)\ge d$，那么我们令 $t=min(s)$ 即可，可自行验证正确性；

2. $min(s)+max(n-1-s)<d$，那么我们令 $t=d-(n-1)-max(n-1-s)$ 即可，亦可自行验证。

于是两边递归，最差情况复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=5010;
int t,n,d,f[MAXN];
int getmin (int x) {
	int res=0,i;
	x--;
	for (i=1;(1<<i)<=x;i++) {res+=i*(1<<i),x-=(1<<i);}
	res+=i*x;
	return res;
}
int getmax (int x) {return x*(x-1)/2;}
bool solve (int n,int l,int r,int d) {
	if (getmin(n)>d||getmax(n)<d) {return 0;}
	if (l>=r) {return 1;}
	n--;
	d-=n;
	for (int i=1;i<=n;i++) {
		int n1=getmax(i),n2=getmax(n-i),m1=getmin(i),m2=getmin(n-i);
		if (n1+n2>=d&&m1+m2<=d) {
			f[l+1]=l;
			if (i<n) {f[l+i+1]=l;}
			if (m1+n2>=d) {solve(i,l+1,l+i,m1),solve(n-i,l+i+1,l+n,d-m1);}
			else {solve(i,l+1,l+i,d-n2),solve(n-i,l+i+1,l+n,n2);}
			return 1;
		}
	}
}
int main () {
	scanf("%d",&t);
	for (int ii=1;ii<=t;ii++) {
		memset(f,0,sizeof(f));
		scanf("%d%d",&n,&d);
		if (!solve(n,1,n,d)) {printf("NO\n");}
		else {
			printf("YES\n");
			for (int i=2;i<=n-1;i++) {printf("%d ",f[i]);}
			printf("%d\n",f[n]);
		}
	}
	return 0;
}
```


---

## 作者：Troubadour (赞：1)

做这道题的时候，我一直忍住没有看题解，最后成功地独立构造出来了，然后一翻题解，大体思路相同，但还是有一些区别。
### 题意
构造一棵以 $1$ 为根，$n$ 个点，节点深度之和为 $d$ 的二叉树。默认根的深度为 $0$。
### 分析
我们首先考虑是否有解。对于一棵二叉树，求它的最大深度和，显然我们就让深度最大的尽量大，最后得到一条链，这就是我们构造出来的最大方案。

简单证明一下：假设上述方案深度和不是最大的，那么最大的方案一定是旁生侧枝的，如图所示：
![](http://r.photo.store.qq.com/psc?/V53Jnu1D3vSo501VoEus464qox1MU2UT/45NBuzDIW489QBoVep5mcZfFwUeDZ4mLy9QUfZwa1yeUZesMcj2Z49E5bAfsdFCd12XkIh0d3ntVXIxxA8YKX1RncozvKVl7kI7O8HxfH0g!/r)

很显然，如果 $5$ 号节点接到 $4$ 的下面会更优，与前面的矛盾，所以一条链的情况一定是深度和最大的。

同理我们可以得到，深度和最小的情况，一定是一棵完全二叉树。这里就不给出证明了。

由此我们可以给出，给 $n$ 个节点所能构造出的二叉树，所有节点深度和的上下界，如何判断是否有解就很显然了。

接下来我们来构造一种方案。其他题解似乎都是先建成完全二叉树再往链靠，我就说一下另一种思路：先把树建成一条链，然后把节点一个一个往根节点方向挪。

我们首先造一条链出来，记录下当前状态。在下面的代码里，我记了**每一层的有空位的节点**、他们的空儿子个数和深度。

我们每次要取一个深度最大的结点，并把它往根节点方向挪。一个方案是，从浅到深遍历每一层，如果当前层有空位且挪过去之后答案小于等于 $d$ ,就把它挪过去并更新相关信息。那么如何保证每次取到的一定是深度最大的呢？我们可以把所有节点扔到一个优先队列里，按照深度排序，每次取堆顶即可。

每次我们挪节点的时候，需要考虑当前这个父亲节点的空儿子数量，如果为 $2$ 我们就减 $1$，否则直接把它移出有空位的节点名单。与此同时，我们也要把当前节点加入这一层的候选列表里。

其实理论上来说，当前节点和原来的父节点脱离关系的时候也需要做类似操作，但是我们可以看出，不会再有节点移到这个位置了，所以不管也无所谓。

#### 注意多组数据。

### Code
```cpp
#include<bits/stdc++.h>
namespace CCCP
{
	const int N = 10005;
	int fa[N], n, d, now;
	struct node
	{
		int id, vacancy;
	}g[N];
	std::basic_string<node>q[N];
	struct _node
	{
		int id, dep;
		bool operator<(const _node x)const { return dep < x.dep; }
	};
	std::priority_queue<_node>f;
	void work()
	{
		memset(g, 0, sizeof(g));
		memset(fa, 0, sizeof(fa));
		for (int i = 0;i < N;i++)q[i].clear();
		while (!f.empty())f.pop();
		std::cin >> n >> d;
		int _max_ = n * (n - 1) / 2, _min_ = 0, tmp = n - 1;
		for (int i = 1, j = 2;;i++, j <<= 1)
		{
			if (j >= tmp)
			{
				_min_ += tmp * i;
				break;
			}
			_min_ += i * j;
			tmp -= j;
		}
		if (_min_ > d || d > _max_)
		{
			puts("NO");
			return;
		}
		puts("YES");
		q[0].push_back({ 1,1 });
		for (int i = 2;i <= n;i++)
		{
			node g;
			fa[i] = i - 1;
			g.id = i;
			if (i != n)g.vacancy = 1;
			else g.vacancy = 2;
			q[i - 1].push_back(g);
			f.push({ i,i - 1 });
		}
		now = _max_;
		while (now != d)
		{
			_node t = f.top();
			f.pop();
			int i;
			for (i = 0;q[i].empty() || now - (t.dep - i - 1) < d;i++);
			now -= t.dep - i - 1;
			node u = q[i].back();
			q[i].pop_back();
			fa[t.id] = u.id, t.dep = i + 1;
			f.push(t);
			if (u.vacancy == 2)
			{
				q[i].push_back({ u.id,u.vacancy - 1 });
			}
			q[i + 1].push_back({ t.id,2 });
		}
		for (int i = 2;i <= n;i++)
		{
			std::cout << fa[i] << ' ';
		}
		puts("");
	}
}
int main()
{
	int t;
	std::cin >> t;
	while (t--)CCCP::work();
	return 0;
}
```

---

## 作者：QQH08 (赞：1)

首先考虑什么时候构造不出来：
- 最小值显然是满二叉树，先把距离和记为 $sum$。
- 最大值先然是链，距离和为 $n*(n-1)/2$。

所以构造不出来的条件就是$d<sum$ 或者 $d>n*(n-1)/2$。

接下来考虑构造符合条件的。

我们先构造出一棵满二叉树，再看多的部分怎么调整。（先把 $d$ 减掉 $sum$，变为多的距离和）

![](https://cdn.luogu.com.cn/upload/image_hosting/disx6cx9.png)

下面，我们要尽可能把点往红色的链上移，使得总距离和变大。

先枚举每一个不在链上的点 $i$ （从大到小），记链最下端的点为 $Max$。如果把 $i$ 移到链的最下端，总距离就会增加 $dep[Max]-dep[i]+1$，（$dep$ 为到根节点的距离，令$dep[1]=0$）。
- 如果 $(dep[Max]-dep[i]+1)<d$，说明把 $i$ 移到链的最下面也不够，所以直接移到最下面，更新父亲，深度和 $d$ 即可。

- 如果 $(dep[Max]-dep[i]+1)=d$，说明移到链的最下端刚好，直接更新，输出答案。

- 否则，说明移到链的最下端深度和偏大了。直接考虑一层一层在链上往上走，直到深度和刚好，直接更新，输出。如果没有使深度和刚好满足要求的位置，就输出 NO。

下面就是代码啦：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5005;
int T,n,d,dep[N],fa[N],lg[N];
bool vis[N];
int main(){
	lg[0]=lg[1]=0;
	for(int i=2;i<N;i++)lg[i]=lg[i/2]+1;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&d);
		int sum=0,Max=0,flag=1;
		memset(vis,0,sizeof(vis));
		memset(fa,0,sizeof(fa));
		dep[1]=0;
		for(int i=2;i<=n;i++){
			fa[i]=i/2;
			dep[i]=lg[i];
			sum+=dep[i];
		}
		for(int i=1;i<=n;i*=2)vis[i]=1,Max=i;
		if(d<sum||d>n*(n-1)/2){
			puts("NO");
			flag=0;
			continue;
		}
		d-=sum;
		if(d==0){
			puts("YES");
			for(int i=2;i<=n;i++)printf("%d ",fa[i]);
			puts("");
			flag=0;
			continue;
		}
		for(int i=n;i>=1;i--){
			if(!vis[i]){
				if(d>dep[Max]-dep[i]+1){
					fa[i]=Max;
					d-=(dep[Max]-dep[i]+1);
					dep[i]=dep[Max]+1;
					Max=i;
				}
				else{
					int p=Max;
					d=dep[Max]-dep[i]+1-d;
					while(d>0&&p!=1)p=fa[p],d--;
					if(d!=0){
						puts("NO");
						flag=0;
						break;
					}
					fa[i]=p;dep[i]=dep[p]+1;break;
				}
			}
		}
		if(flag==1){
			puts("YES");
			for(int i=2;i<=n;i++)printf("%d ",fa[i]);
			puts("");
		}
	}
	return 0;
}
```


---

## 作者：syksykCCC (赞：1)

首先，我们可以先确定可行的 $d$ 的范围。

显然，当二叉树是一条链的时候，$d$ 是最大的，也就是说，$0+1+2+\cdots (n-1) = d_{\max}$，稍微转化一下，就是 $d \le \frac{n(n-1)}{2}$。

而把这颗二叉树给尽量满的构造 $d$ 显然是最小的，也就是说，确保这棵二叉树是完全二叉树，就可以得到 $d_{\min}$，这个不妨递推一下，如果用 $dep_i$ 表示第 $i$ 个结点的深度，那么显然有 $dep_{2i} = dep_i + 1, dep_{2i+1} = dep_i + 1$（类比线段树很容易理解），当然，这个和 $dep_i = dep_{\lfloor\frac i 2 \rfloor}+1$ 是等价的。

那么在 $[d_{\min}, d_{\max}]$ 之间的 $d$ 都是可行的了，观察到 $n, d$ 都很小，可以尝试一步步的转移。先构造出一棵完全二叉树，每次 **找到一个可行的深度最大的点，把它向下移动一层**。

为了实现方便，不妨把 $dep = i$ 的点存到一个 `vector` 中，名字叫做 $\text{node}_i$，现在试图把某一个 $dep = i$ 的点下移，要求显然就是 **去掉这个点后，下面一层还有位置**，可以表现为 $\operatorname{size}(\text{node}_{i+1})<(\operatorname{size}(\text{node}_i) - 1) \times 2$，暴力下移即可。

最后我们得到的是若干个 `vector` 数组，令 $\text{node}_{i,j}$ 的儿子是 $\text{node}_{i+1,2i}$ 和 $\text{node}_{i+1,2i+1}$ 就行了（当然，前提是存在）。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
int n, dep[N], d, mxdep, sumdep, fa[N];
vector<int> node[N];
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n >> d;
		for(int i = 1; i <= n; i++) node[i].clear();
		dep[1] = mxdep = sumdep = 0;
		node[0].push_back(1);
		for(int i = 2; i <= n; i++)
		{
			dep[i] = dep[i >> 1] + 1;
			sumdep += dep[i];
			mxdep = max(mxdep, dep[i]);
			node[dep[i]].push_back(i); 
		}
		if(d < sumdep || d > n * (n - 1) / 2)
		{
			cout << "NO\n";
			continue;
		}
		while(sumdep < d)
		{
			for(int i = mxdep; ~i; i--)
			{
				if(node[i].size() >= 2 && node[i + 1].size() < node[i].size() * 2 - 2)
				{
					sumdep++;
					mxdep = max(mxdep, i + 1);
					node[i + 1].push_back(node[i].back());
					node[i].pop_back();
					break;
				}
			}
		}
		for(int i = 0; i <= mxdep; i++)
		{
			for(int j = 0; j < node[i].size(); j++)
			{
				int ls = j * 2, rs = j * 2 + 1;
				if(ls < node[i + 1].size()) fa[node[i + 1][ls]] = node[i][j];
				if(rs < node[i + 1].size()) fa[node[i + 1][rs]] = node[i][j];
			}
		}
		cout << "YES" << endl;
		for(int i = 2; i <= n; i++) cout << fa[i] << ' ';
		cout << endl;
	}
	
}
```

---

## 作者：gyh20 (赞：1)

题意：构造一棵 $n$ 个点的二叉树，使得所有点深度之和为 $d$。

首先，先求出 $n$ 个点的最小答案（完全二叉树）和最大答案（链），排除无解情况。

考虑剩下的怎么做。

先构造一条链，再进行调整。

默认 $dep_i \leq dep_{i+1}$，并令当前所有节点的深度和为 $ans$。

从 $2$ 枚举到 $n$，可以知道，当枚举到一个点时，它下面一定是一条链。

假设当前枚举到 $i$，如果将 $i$ 的深度减少 $1$，那么得到的结果会减少 $n-i$。分成两种情况考虑。

如果 $ans-(n-i) \ge d$，则将 $i$ 的深度减少 $1$。

否则退出，因为在之后一定存在一个满足的点，事实上，将 $n-(ans-d)+1$ 这个点的深度$-1$ 即可。

所以，任何时候，构造出的树都是一棵完全二叉树 $+$ 一条链的形式，特别的，当 $i=2^k(k\in N)$ 时，无法将 $i$ 的深度减少 $1$。（上面已经满了）

输出的时候分成两部分输出。

先输出上面的完全二叉树，第 $i$ 个点的父亲即为 $i/2$ 。

然后输出链，第 $i$ 个点的父亲即为 $i-1$ ，特殊地，为了将第 $n-(ans-d)+1$ 个的深度少 $1$ ，只用将他的父亲设为 $i-2$ 即可。

总复杂度好像只有 $O(d/n+\log n)$，十分优秀。

```cpp
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define re register
#define int long long
inline int read() {
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0') {
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int t,n,k,num,cnt,ia,l,lst,mn,p;
signed main() {
	t=read();
	while(t--) {
		n=read();
		k=read();
		p=n-1;
		mn=0;
		for(re int i=1; i<=n; ++i) {
			if((1ll<<i)<=p) {
				p-=(1ll<<i);
				mn+=i*(1ll<<i);
			} else {
				mn+=p*i;
				break;
			}
		}
		if(mn>k) {
			puts("NO");
			continue;
		}
		k=n*(n-1)/2-k;
		if(k<0) {
			puts("NO");
			continue;
		}
		ia=0;
		cnt=1;
		lst=0;
		puts("YES");
		for(re int i=1; i<=n; ++i) {
			++cnt;
			for(re int j=1; j<(1ll<<i); ++j) {
				if(cnt>=n) {
					ia=1;
					break;
				}
				if((n-cnt)<=k) {

					k=k-(n-cnt);
					++cnt;
				} else {
					ia=1;
					break;
				}
			}
			if(ia)break;
		}
		if(cnt>n)cnt=n;
		for(re int i=2; i<=cnt; ++i) {
			printf("%lld ",i/2);
		}
		lst=cnt;
		for(re int i=lst+1; i<=n; ++i) {
			if(i==n-k+1)printf("%lld ",i-2);
			else printf("%lld ",i-1);
		}
		putchar('\n');

	}
}
```










---

## 作者：傅思维666 (赞：0)


## 题解：

与其说是树题，还不如说是模拟题。

很容易判断上下界：上界就是链，下界就是完全二叉树。

构造的话，先构造一棵完全二叉树，然后拎出来一条链（最长链），从后往前（因为是按编号构造的初始树）依次尝试把当前节点链到下一层。这样，深度就会逐一递增。所以一定会有合法解。

只需要模拟这个过程就行。

说着容易，看代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=5005;
int t,n,d,tot;
int fa[maxn],deep[maxn],chain[maxn];
bool v[maxn];
void clear()
{
	tot=0;
	memset(v,0,sizeof(v));
	chain[0]=1;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		clear();
		scanf("%d%d",&n,&d);
		for(int i=2;i<=n;i++)
		{
			fa[i]=i/2;
			deep[i]=deep[fa[i]]+1;
			d-=deep[i];
			tot=max(tot,deep[i]);
		}
		if(d<0)
		{
			puts("NO");
			continue;
		}
		int p=n;
		while(p)
		{
			chain[deep[p]]=p;
			v[p]=1;
			p=fa[p];
		}
		for(int i=n;i>=1;i--)
		{
			if(v[i])
				continue;
			int mx=tot;
			while(deep[fa[i]]<mx && d)
			{
				fa[i]=chain[deep[fa[i]]+1],deep[i]=deep[fa[i]]+1;
				if(deep[i]>tot)
					chain[++tot]=i,v[i]=1;
				d--;
			}
		}
		if(d)
		{
			puts("NO");
			continue;
		}
		puts("YES");
		for(int i=2;i<=n;i++)
			printf("%d ",fa[i]);
		puts("");
	}
	return 0;
}
```



---

## 作者：zhmshitiancai (赞：0)

[door](https://codeforces.ml/contest/1311/problem/E)

题意：要求构造一颗$n$个点的二叉树，使得此二叉树所有深度和为$d$，$n,d\leq5000$。(根的深度为0)

### my idea
对于1颗n个点的二叉树而言，深度和最多的情况是一条链，先钦定它是一条链，然后每次考虑从深度高的向上一层挪一个点，这样深度和减一，总能挪到目标态。

事实证明有些情况无法从深度高的点向上一层挪一个(扑街

### soultion
反过来想。

我们先记录每一层点的个数，之后构造，只要每层点的个数合法，总能找到构造方案。

我们先钦定所有的点都集中在深度尽可能低的地方，即先放第一层，再第二层，etc。如果这样的和就$>d$那么无解。不然每次操作，我们从深度高的地方向前扫描每一层，找到第一个点数$>1$的，这样它的后一层要么没有点，要么有一个点，我们从这一层向后挪一个点，合法且深度和减一。

这样一直做到$s=d$或者无法操作，即所有层都只有一个点，恰对应了深度最深(为一条链的情况)。

之后一层层赋值，构造即可。

**code**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int INF=0x3f3f3f3f,N=5000+5;
int n,m;
int ce[N],lim[N],tot,s;
int fa[N];
bool add()
{
	bool f=0;
	for(int i=tot;i>0;i--)
	{
		if((ce[i]-1)*2>=ce[i+1]+1)
		{
			ce[i]--;
			ce[i+1]++;
			if(i+1>tot)
				tot=i+1;
			s++;
			f=1;
			break;
		}
	}
	return f;
}
void init()
{
	s=0;tot=0;
	memset(ce,0,sizeof(ce));
	memset(fa,0,sizeof(fa));
}
void print()
{
	for(int i=1;i<=tot;i++)
		cout<<ce[i]<<" ";
	cout<<endl;
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i,T,j;
	cin>>T;
	lim[0]=1;
	for(i=1;i<=5000;i++)
	{
		if(i>=20)
			lim[i]=lim[i-1];
		else 
			lim[i]=lim[i-1]*2;
	}
	while(T--)
	{
		cin>>n>>m;
		init();
		n--;
		ce[0]=1;
		int left=n;
		for(i=1;i<=n;i++)
		{
			tot=i;
			if(left-lim[i]>0)
			{
				left-=lim[i];
				ce[i]=lim[i];
				s+=lim[i]*i;
			}
			else 
			{
				ce[i]+=left;
				s+=left*i;
				break;
			}
		}
//		cout<<s<<endl;
//		for(i=1;i<=tot;i++)
//			cout<<ce[i]<<" ";
//		cout<<endl;
		if(s>m) 
		{
			cout<<"NO"<<endl;
			continue;
		}
		bool f=1;
		while(s<m)
		{
			if(!add()){
				f=0;
				break;
			}
		//	print();
		}
		if(!f) 
		{
			printf("NO\n");
			continue;
		}
		printf("YES\n");
//		print();
//		cout<<s<<endl;
		int num=0;
		vector<int> v[2];
		v[0].clear();v[1].clear();
		v[1].pb(1);
		num=1;
		for(i=1;i<=tot;i++)
		{
			//v[i&1],v[(i&1)^1];
			v[(i&1)^1].clear();
			for(j=1;j<=ce[i];j++)
			{
				num++;
				fa[num]=v[i&1][(j-1)/2];
				v[(i&1)^1].pb(num);
			}
		}
		for(i=2;i<=n+1;i++)
			cout<<fa[i]<<" ";
		cout<<endl;
	}
}
```

---

## 作者：KokiNiwa (赞：0)

# E-Construct Binary Tree

实现繁琐的题目。[题目链接](https://codeforces.ml/contest/1311/problem/E)

## 题目叙述

要求你构造一棵树使得他有$n$个节点并且所有结点的深度值和位$d$。

## 题解

其实都是调整法。

### A

大众写法。

题解是先搞一条链，然后对于这条链再调整。每次选择最下面的点，看挂在哪里合适。每次调整的一定是连续的（这样就可以保证填成满二叉树和填成一条链这段区间内的深度和都可以）。

### B

我的写法。

我们发现作终和答案有关系的就是每一层有多少个节点；父子关系之类的不重要。所以最开始填成满二叉树的形式，然后每次把最靠下的一层节点个数不为1的最后一个节点放到下一层去。唯一可能不行的就是对于相邻两层，下面一层的节点数比上面一层的两倍大，所以不行。但是每次选择的是那一层节点个数不为1的，而这一层的下一层节点个数一定为1，于是向下放一定可行。

## 代码

我的写法：

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxNode = 5e3 + 5;
int T, nbNode, deepSum, dep[maxNode], fa[maxNode];
vector<int> layer[maxNode];
int main() {
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		for (int i = 1; i <= nbNode; ++i) layer[i].clear(), fa[i] = 0;
		scanf("%d%d", &nbNode, &deepSum);
		int maxd = 0;
		layer[0].push_back(1);
		for (int i = 2; i <= nbNode; ++i)
			dep[i] = dep[i>>1] + 1, layer[dep[i]].push_back(i), 
			maxd = max(maxd, dep[i]), deepSum -= dep[i];
		if (deepSum < 0) {
			printf("NO\n");
			continue ;
		}
		bool flag = 1;
		while (deepSum) {
			int change = maxd;
			while (change >= 0 && layer[change].size() == 1) --change;
			if (change == 0) {
				printf("NO\n");
				flag = 0;
				break ;
			}
			int node = layer[change][layer[change].size() - 1];
			layer[change].pop_back();
			layer[change + 1].push_back(node);
			maxd = max(maxd, change + 1);
			--deepSum;
		}
		if (flag) {
			printf("YES\n");
			for (int i = 1; i <= nbNode; ++i) {
				for (int pos = 0; pos < layer[i].size(); ++pos) {
					fa[layer[i][pos]] = layer[i - 1][pos / 2];
				}
			}
			for (int i = 2; i <= nbNode; ++i)
				printf("%d ", fa[i]);
			printf("\n");
		}
	}
	return 0;
}
```



大众写法（直接抄的[Tutorial](https://codeforces.ml/blog/entry/74224)）：

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	
	int t;
	cin >> t;
	while (t--) {
		int n, d;
		cin >> n >> d;
		int ld = 0, rd = n * (n - 1) / 2;
		for (int i = 1, cd = 0; i <= n; ++i) {
			if (!(i & (i - 1))) ++cd;
			ld += cd - 1;
		}
		if (!(ld <= d && d <= rd)) {
			cout << "NO" << endl;
			continue;
		}
	
		vector<int> par(n);
		iota(par.begin(), par.end(), -1);
		
		vector<int> cnt(n, 1);
		cnt[n - 1] = 0;
		
		vector<int> bad(n);
		
		vector<int> dep(n);
		iota(dep.begin(), dep.end(), 0);
		
		int cur = n * (n - 1) / 2;
		while (cur > d) {
			int v = -1;
			for (int i = 0; i < n; ++i) {
				if (!bad[i] && cnt[i] == 0 && (v == -1 || dep[v] > dep[i])) {
					v = i;
				}
			}
			assert(v != -1);
			int p = -1;
			for (int i = 0; i < n; ++i) {
				if (cnt[i] < 2 && dep[i] < dep[v] - 1 && (p == -1 || dep[p] < dep[i])) {
					p = i;
				}
			}
			if (p == -1) {
				bad[v] = 1;
				continue;
			}
			assert(dep[v] - dep[p] == 2);
			--cnt[par[v]];
			--dep[v];
			++cnt[p];
			par[v] = p;
			--cur;
		}
	
		cout << "YES" << endl;
		for (int i = 1; i < n; ++i) cout << par[i] + 1 << " ";
		cout << endl;
	}
		
	return 0;
}
```



## 知识点

+ 构造题，有一种思路就是构造一个不符合条件的然后不断调整。
+ 可以考虑简化问题（比如这道题父子关系会给你带来麻烦。。。）。
+ 多用封装好的东西这样可以让你的思路变得清晰...（先写出来，别在乎效率，用了个`vector`其实也就常数大点嘛）

---

