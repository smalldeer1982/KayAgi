# [ARC088F] Christmas Tree

## 题目描述

给定一棵 $N$ 个节点的树。用如下方法生成一棵与其相同的树：

- 首先生成 $A$ 个边数均不超过 $B$ 的链。
- 重复以下操作直到所有的点连通：
  - 选择两个当前属于不同连通块的点，将这两个点合并为一个点，所有原来与这两个点中的至少一个点有边的点与这个新点有边。
- 将点重新标号。

求出能够生成给定树的最小的 $A$ 值，在最小化 $A$ 的基础上最小化 $B$ 值。

对于 $100 \%$ 的数据，$2\le N\le 10^5$。

## 样例 #1

### 输入

```
7
1 2
2 3
2 4
4 5
4 6
6 7```

### 输出

```
3 2```

## 样例 #2

### 输入

```
8
1 2
2 3
3 4
4 5
5 6
5 7
5 8```

### 输出

```
2 5```

## 样例 #3

### 输入

```
10
1 2
2 3
3 4
2 5
6 5
6 7
7 8
5 9
10 5```

### 输出

```
3 4```

# 题解

## 作者：hater (赞：3)

先考虑A怎么搞 

考虑 dp 

$f_{i}$ 表示组合完以i为根的子树的链个数 并且向i的父亲连了一根链

转移 

$f_{x}=\sum_{y\in son_{x}}f_{y}$ 

之后这样转移显然会有多余的链 

设 $cnt$ 是x的儿子个数 

我们可以在x处把 $cnt/2$ 个链合并 

如果 cnt 是奇数 那么就会剩下一根链连向他的父亲 

如果是偶数 就说明他们配对完了 需要再新出一条链与他的父亲相连 

（ 当然如果x是根节点就不需要和父亲相连 ） 

A 求出后 考虑 B 

这个显然具有单调性 可以二分 

之后怎么判断 .... 就和赛道修建一模一样了 

```cpp
#include<bits/stdc++.h>  
#define rg register 
#define i60 long long 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
using namespace std ; 
const int N = 1e5+10 ; 
const int inf = 1e7 ;  
int ans1 , n , f[N] , f2[N] , nw_x , tot ;    
vector <int> v[N] ; 
multiset <int> g[N] ; 
multiset <int> :: iterator it , it2 ;  
void dfs( int x , int fa )  { 
  int l = v[x].size() , y ; l -- ;  
  fp( i , 0 , l ) { 
    y = v[x][i] ; 
    if( y == fa ) continue ; 
    dfs( y , x ) ; 
    f[x] += f[y] ; 
  } 
  if( x == 1 ) l ++ ;  
  f[x] -= l/2 ; 
  if( l%2== 0 && x!=1 )  
    f[x] ++ ; 
} 
void dfs2( int x , int fa ) { 
  g[x].clear() ; 
  int l = v[x].size() , y ; 
  fp( i , 0 , l-1 ) { 
    y = v[x][i] ; 
    if( y == fa ) continue ; 
    dfs2( y , x ) ; 
	if( f2[y] < nw_x ) g[x].insert( f2[y] ) ;  
  } 
  int up=inf ;  
  while( g[x].size() > 1 ) { 
    it = g[x].end() ; it -- ; 
    int nw = (*it) ; g[x].erase( it ) ;  
    it2 = g[x].upper_bound( nw_x-nw ) ; 
    if( it2 == g[x].begin() ) { up=min(up,nw) ;  continue ;}  
	it2 -- ; g[x].erase( it2 ) ; tot -- ; 
  } 
  if( g[x].size() == 1 ) { it = g[x].begin() ; f2[x] = (*it)+1 ; } 
  else if( x != 1 ) { 
    if( up == inf ) f2[x] = 1 , tot ++ ; 
    else f2[x] = up+1 ; 
  } 
}  
bool chk( int x ) { 
  tot=0 ; nw_x=x ; dfs2( 1 , 0 ) ; 
  return tot <= ans1 ; 
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  cin >> n ; int x , y ; 
  fp( i , 1 , n-1 ) { 
    cin >> x >> y ; 
    v[x].push_back(y) ; 
    v[y].push_back(x) ; 
  } 
  dfs( 1 , 0 ) ; 
  ans1 = f[1] ; 
  int l=1 , r=n , mid , ans2 ; 
  while( l<=r ) { 
    mid=l+r>>1 ; 
    if( chk(mid) ) ans2=mid , r=mid-1 ; 
    else l=mid+1 ; 
  } 
  cout << ans1 << ' ' << ans2 << '\n' ; 
  return 0 ; 
} 
```


似乎官方题解也是两个log
 
但是这道题的特殊性质可以做到一个log

考虑判断的时候 

肯定需要能配对的都配对 不然答案不会为A  

将儿子排序之后 除掉那个跟父亲相连的链  

其他的一定是 最长和最短的合并  

我们枚举那个 跟父亲相连的链 就可以做到线性判断 

这个是realskc吊打std的做法 要代码自己可以看他记录   

---

## 作者：_Imaginary_ (赞：1)

## [Problem](https://www.luogu.com.cn/problem/AT3734)

给定一个 $n$ 个节点的树，请你求出：

$A$ 表示最少需要多少条链来覆盖整棵树，链不能重叠。

$B$ 表示在满足链的条数最小的情况下，最长链的最短长度。

要求双 $\log$ 复杂度~~（不过好像没有人三 $\log$ 过的吧）~~

## Solution

从前，有个东西叫一笔画问题。

在树上，画一笔显然只能画一条链。

而一笔画问题的解决方案就是求度数为奇数的点的个数。

所以，我们就是要求奇点的个数，然后链的条数就是个数除以二。

这时，我们发现一个重要的性质：每一条链的起点和终点都是奇点。~~（什么，你不会一笔画？）~~

接下来求 $B$。假如知道了 $B$，我们可以求出需要链的最小数量，所以考虑二分答案。

具体的，我们求出以每个点为根的子树需要链的最小数量。

对于一个点，它的儿子先处理，然后向上传一堆链进行匹配。

我们令 $dp[u]$ 表示 u 的子树内未匹配完的链的长度。

那么，对于某一个 u 的儿子 v，有 $dp[u]=dp[v]+1$。

我们希望除了这个 v 以外，其他儿子互相匹配成长度不超过 $B$ 的链，可以贪心，最长和最短匹配。

枚举这个 v，我们再用二分，具体可以看代码和官方题解。

## Code

~~请忽略掉奇奇怪怪的 debug~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define freopen(a,b,c)
const int N=100005,M=200005;
int hd[N],nxt[M],to[M],tot=0;
int deg[N];
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=hd[x];
	hd[x]=tot;
}
int n;
int A,B,tot_A;
int dp[N];
int c[N],num;
bool check(int r)
{
	int L=1,R=num;
	for(int i=1;i<=num/2;i++)
	{
		if(L==r) L++;
		if(R==r) R--;
		if(c[L]+c[R]>B) return false;
		L++;
		R--;
	}
	return true;
}
bool dfs(int u,int fa)
{
//	printf("DFSing %d\n",u);
	for(int i=hd[u];i;i=nxt[i])
		if(to[i]!=fa) 
			if(!dfs(to[i],u)) return false;
	num=0;
	for(int i=hd[u];i;i=nxt[i])
		if(to[i]!=fa)
			c[++num]=dp[to[i]];
	if(num%2==0) c[++num]=0;
	sort(c+1,c+num+1);
//	printf("u=%d num=%d\n",u,num);
//	for(int i=1;i<=num;i++) printf("%d ",c[i]); printf("\n");
	if(!check(num)) return false;
//	printf("Success!\n");
	int L=1,R=num-1,mid;
	while(L<=R)
	{
		mid=(L+R)>>1;
		if(check(mid)) R=mid-1;
		else L=mid+1;
	}
	tot_A+=num/2;
	dp[u]=c[L]+1;
//	printf("r=%d dp[%d]=%d tot_A=%d\n",L,u,dp[u],tot_A);
//	if(tot_A>A) return false;
	if(u!=1&&dp[u]>=B+1) return false;
//	printf("GOOD!\n");
	return true;
}
bool ok(int bb)
{
//	printf("+++++++++++++++Now B=%d\n",bb);
	B=bb;
	tot_A=0;
	if(dfs(1,0)&&dp[1]<=B+1&&tot_A+(dp[1]>1)<=A) 
	{
//		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		return true;
	}
//	printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n");
	return false;
}
int main()
{
	freopen("tree.in","r",stdin);	
	freopen("tree.out","w",stdout);	
	memset(deg,0,sizeof(deg));
	scanf("%d",&n);
	for(int i=1,ta,tb;i<n;i++)
	{
		scanf("%d%d",&ta,&tb);
		add(ta,tb);
		add(tb,ta);
		deg[ta]++;
		deg[tb]++;
	}
	A=0;
	for(int i=1;i<=n;i++)
		if(deg[i]&1) A++;
	A/=2;
	printf("%d ",A);
	int L=0,R=n,mid;
	while(L<=R)
	{
		mid=(L+R)>>1;
//		printf("---------------L=%d R=%d mid=%d\n-------------------\n",L,R,mid);
		if(ok(mid)) R=mid-1;
		else L=mid+1;
	}
//	if(ok(L+1)) L++;
	printf("%d",L);
	return 0;
}
```

---

