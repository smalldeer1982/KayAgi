# Apple Tree

## 题目描述

You are given a rooted tree with $ n $ vertices. In each leaf vertex there's a single integer — the number of apples in this vertex.

The weight of a subtree is the sum of all numbers in this subtree leaves. For instance, the weight of a subtree that corresponds to some leaf is the number written in the leaf.

A tree is balanced if for every vertex $ v $ of the tree all its subtrees, corresponding to the children of vertex $ v $ , are of equal weight.

Count the minimum number of apples that you need to remove from the tree (specifically, from some of its leaves) in order to make the tree balanced. Notice that you can always achieve the goal by just removing all apples.

## 样例 #1

### 输入

```
6
0 0 12 13 5 6
1 2
1 3
1 4
2 5
2 6
```

### 输出

```
6```

# 题解

## 作者：liuyifan (赞：4)

## 带有技巧性和数学性的搜索
设答案为ans，根结点的子节点个数为n，那么根下面的每棵子树的权值为ans/n，每颗子树的占比为1/n
再设根结点的某棵子树的子节点个数为m，那么该根节点子节点的每棵子树的重量占整棵树重量的比重为1/n/m，那么通过~~暴力~~DFS就可以把整棵树的每个叶子节点重量的占比求出来，就可以求出每个叶子节点重量的占比,取最小值记为minn，再求出全部叶子比重的lcm，若lcm>minn，则需删除整棵树，否则搜索一个最接近minn的lcm作为删除后树的重量，即minn+minn%lcm，那么ans=初始重量-删除后重量，还需判断二者的大小关系。

可能不太好推和理解(作者推了很久)，可以试着画一下图
## 坑点:
1.计算权值和时有溢出，minn的初始值要足够大(多个(如7等)测试数据就是坑这个)
建议直接#define inf LLONG_MAX or LONG_LONG_MAX一步到位
2.不知道为什么CF的编译器经常莫名其妙的CE,例如上条语句不能用LONG_LONG_MAX,只能用LLONG_MAX,还有iostream会占用掉abs,y1等奇怪问题

## 完整代码：(NO COPYING)
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//register卡常
#define ll long long//推荐这样定义,直接打long long容易因为中间的空格在STL数据结构引发某些mengbi问题
#define inf LLONG_MAX//long long的最大值,GCC内置定义
#define lcm(a,b) (a*b/__gcd(a,b))//带参数的define格式
//这样用比函数调用快得多
//注意这种定义外面一定要加括号,因为编译器时采取的直接替换文本的方式，如果不加括号就容易造成运算优先级问题
using namespace std;
ll n,x[200005],l=inf,m=1,ans,xx,yy;
vector<ll>g[200005];//相当于二维vector
inline void dfs(reg ll u,reg ll prt,reg ll d)//对树进行DFS遍历
{
    m=lcm(m,d);//调用define定义
    if(d>ans||d<0)
	{
		printf("%lld",ans);//long long输出
		exit(0);
		//ODFS等递归函数常用工具,直接退出整个程序(结束程序运行),而不是结束函数运行并返回值
	}
    if(u&&g[u].size()==1)l=min(l,x[u]*d);
    for(reg ll v:g[u])
	if(v!=prt)dfs(v,u,d*(g[u].size()-(u==1?0:1)));//这一层没有做出决定,进入下一层
}
int main()
{
    scanf("%lld",&n);
    for(reg ll i=1;i<=n;i++)
	{
		scanf("%lld",&x[i]);
		ans+=x[i];//先累加所有点权和
	}
    for(reg ll i=1;i<=n-1;i++)
    {
        scanf("%lld%lld",&xx,&yy);
        g[xx].push_back(yy);
		g[yy].push_back(xx);//交错匹配
    }
    dfs(1,0,1);//开始搜索
    printf("%lld\n",ans-l/m*m);//ans=初始树的重量-删除后树的重量
    //输出结果
    return 0;//这里也可以换成exit(0)，等价
    //在main执行完后也会有系统exit(0)进行资源回收处理
}
```

---

## 作者：Guagua_ (赞：2)

## 题意：
给一棵树，要求除去最少的苹果，以保证每一个结点的子树所含的苹果数相同。

## 分析：
1. 对于一个结点，它的值是它的所有子树的值的和，又由于题目要求子树所含的苹果数相同，所以，结点的值**必须为子树的个数的倍数或者 $0$**。
1. 为了保证这个结点的子树的合法，此结点的值必须保证**为其子结点所需要的倍数的倍数或者 $0$**。
1. 叶子结点所需要的倍数为 $1$。
1. 由于叶子结点的苹果数只能加不能减，所以每一个结点的最大值为**子结点的最小值乘以子结点的个数。**


------------

### 综上所述，我们就可以确定我们需要搜索的东西：
- 结点合法所需要满足的倍数。
- 结点的父亲。
- 子结点最小的合法的值。

------------
##  需要注意的点：
1. 结点合法所需要满足的倍数可能会很大 (大于 $10^8$)，由于 $a_i$ 小于 $10^8$ 所以大于 $10^8$ 的倍数对于我们来说没有用，所以我们得加个特判，当倍数大于 $10^8$ 时，就将它设为 $10^8$。
1. 为了方便搜索，我们将结点深度从小到大排序，按照这个规律搜索。

## 代码：
 _不太懂的可以看注释_ (有点长)。
 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=1e8+7;
const int N=2e6+7;
int g[N];
int head[N],ne[N],to[N],id;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
void add(int x,int y){
	to[++id]=y;
	ne[id]=head[x];
	head[x]=id;
}
int a[N],n;
struct node{
	int trsum,fa,id,dep,real,son;//这一个结点的原有苹果数、结点的父亲、 结点原本的编号、结点的深度、结点最多能保留的苹果数、结点的儿子数 
	int gcds=1;//为了平衡，结点保留的苹果数必须为gcds的倍数    
}tree[N];
void dfs1(int u,int fa){
	tree[u].fa=fa;
	tree[u].dep=tree[fa].dep+1;
	tree[u].gcds=1; 
	tree[u].id=u;//初始赋值 
	for(int i=head[u];i;i=ne[i]){
		int v=to[i];
		if(v==fa)continue;
		dfs1(v,u);
		tree[u].gcds=(tree[u].gcds*tree[v].gcds)/gcd(tree[u].gcds,tree[v].gcds);//最小公倍数 
		tree[u].son++;
		tree[u].trsum+=tree[v].trsum;//结点的原有苹果数为它所有子节点的苹果数的总和 
		
	}
	if(tree[u].son==0){//叶子结点特判 
		tree[u].gcds=1;
		tree[u].trsum=a[u];
		return;
	}
	tree[u].gcds*=tree[u].son;
	tree[u].trsum+=a[u];
	if(tree[u].gcds>INF){//特判：如果倍数比 a[i]还要大(1e8)那就把它赋值为INF，不然会导致RE。 
		tree[u].gcds=INF;
	}
	return;
}
bool cmp(node a,node b){
	return a.dep>b.dep;
}
void dfs2(int u,int fa){
	int minn=INF;
	for(int i=head[u];i;i=ne[i]){
		int v=to[i];
		if(v==fa)continue;
		minn=min(minn,tree[g[v]].real);//寻找子结点中苹果数最少的一个 
	}
	if(minn==INF){
		tree[g[u]].real=tree[g[u]].trsum;//叶子结点特判 
		return;
	}
	int sum=0;
	sum=minn*tree[g[u]].son;
	sum/=tree[g[u]].gcds;
	sum*=tree[g[u]].gcds;
	tree[g[u]].real=sum;
	return;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs1(1,0);
	sort(tree+1,tree+1+n,cmp);//为了让它从更深的结点开始搜。 
	for(int i=1;i<=n;i++){
		g[tree[i].id]=i;//方便找回 
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		dfs2(tree[i].id,tree[i].fa); 
	}
	printf("%lld",(tree[g[1]].trsum-tree[g[1]].real));
    return 0;
}
```


---

## 作者：wmrqwq (赞：0)

很典的题啊。

你发现条件等价于一个子树权值直接平分到儿子上，那么这东西是 LCM 的，你发现问题等价于对于一个长度为 $n$ 的序列 $a_i$，有一个初始值为 $m$，将 $m$ 每次减去 $a$ 序列中的一个数使得 $m \bmod k = 0$，这是一个裴蜀定理，于是做完了。

---

## 作者：Crazyouth (赞：0)

## 分析

考虑对于一个点 $u$，为了让它的儿子的权值一致，我们记 $lc_u$ 为一个最小的值，使最终（这里最终指让 $u$ 的子树平衡后，下同） $u$ 的权值必然是它的倍数。由于儿子会很多次分叉，而 $lc_u$ 又必然是所有分叉数量的倍数，我们可以考虑 $lc$ 的递推式：

$$lc_u=(\operatorname{lcm}_{v\in \operatorname{son}_u}lc_v)\times |\operatorname{son}_u|$$

其中 $\operatorname{son}_u$ 表示所有 $u$ 的儿子组成的集合。再令 $sum_u$ 表示 $u$ 最终的权值，$mn_u=\min_{v\in\operatorname{son}_u} sum_v$，则 $sum_u\le mn_u\times |\operatorname{son}_u|$，又由上面可得 $lc_u | sum_u$，所以我们就可以知道具体的 $sum_u$ 了。

最终答案则为 $(\displaystyle\sum_{i=1}^n a_i)-sum_1$，总复杂度 $O(n\log V)$，$V$ 为值域（用于求最小公倍数）。

有一些细节需要注意，因为 $lc_u$ 可能很大，所以计算过程中一旦 $lc_u>mn_u\times |\operatorname{son}_u|$，我们可以直接输出 $\displaystyle\sum_{i=1}^n a_i$ 并结束程序。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int a[N],cnt[N],sum[N],tot,lc[N];
vector<int> G[N];
void dfs(int u,int fa)
{
	int mn=1e18,l=1;
	for(auto v:G[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		mn=min(mn,sum[v]);
		cnt[u]++;
	}
	if(!cnt[u])
	{
		sum[u]=a[u];
		cnt[u]=1;
		lc[u]=1;
		return;
	}
	for(auto v:G[u])
	{
		if(v==fa) continue;
		l=l*lc[v]/__gcd(l,lc[v]);
		if(l>mn*cnt[u])
		{
			cout<<tot;
			exit(0);
		}
	}
	l*=cnt[u];
	lc[u]=l;
	sum[u]=mn*cnt[u];
	sum[u]=sum[u]/l*l;
	if(!sum[u])
	{
		cout<<tot;
		exit(0);
	}
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) tot+=a[i];
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	cout<<tot-sum[1];
}

---

