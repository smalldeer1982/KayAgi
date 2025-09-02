# One Node is Gone

## 题目描述

给定一个正整数$n(2\le n\le17)$

我们将会先生成一个大小为$2^n-1$的完全二叉树，其有一个根

现在以某种规则删去了其中的一个非根节点，具体规则如下：

设删去点为$u$

那么我们会删去所有$u$的出边，然后将其所有直系儿子与$u$的父亲连一条边，特别的，如果$u$是一个叶子节点，则不会连边.

现在给定一棵树，希望你求出其能否以上述规则通过删除完全二叉树的一个点后得到，如果可以，求出方案数并输出所有方案中$u$的父亲，你需要升序输出

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
2 5
3 6
3 13
3 14
4 7
4 8
5 9
5 10
6 11
6 12
```

### 输出

```
1
3
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
2
1 2
```

## 样例 #3

### 输入

```
3
1 2
2 3
3 4
4 5
5 6
```

### 输出

```
0
```

# 题解

## 作者：Miraik (赞：3)

$n=2$ 特判一下。

对于其他情况，根显然只会为重心，而定完根之后对应的答案也最多只有一种，而重心所以答案最多只有两种。

直接考虑枚举可能的重心为根，考虑定好根怎么求解。

记 $soncnt_u$ 表示 $u$ 的儿子个数，你发现答案 $u$ 只会是这两种情况：

+ $soncnt_u=3$，此时被删的点不是叶子

+ $soncnt_u=1$，此时被删的点不是叶子

那你大力还原不就完了？不过会有一些细节。我具体实现的方法是预处理一下子树内最长链 $d_u$，若 $u$ 的儿子 $v$ 满足 $d_v+2=d_u$，则说明 $v$ 是被删的点的儿子。

总时间复杂度为线性。

[code](https://codeforces.com/contest/1228/submission/212188168)

---

## 作者：hgckythgcfhk (赞：2)

考虑满二叉树的性质，每个点的孩子个数有两种情况，是叶子节点就没有孩子，否则必有两个孩子，同时，满二叉树的每个子树（包括自身）是对称的。

假设我们现在知道树根是哪个节点，我们可以暴力的还原整课树，题目中直接告诉了我们被删掉的节点编号是 $2^n-1$，我们把这个节点强行加进去就可以，假设我们现在已经加好，那么如果**还原后的树不是满二叉树**则有以某个把节点为根的子树不对称，或者有某个非叶节点的孩子个数不为 $2$，这个结论是显然成立的，那么合理的猜测我们可以用所有子树对称和所有非叶节点的孩子个数为 $2$ 来判定还原后的数是满二叉树，这个结论看起来是很对的，但不好给出形式化的证明，其实不重要，这样能过。

接下来要解决的问题是怎么判定对称，当然可以写一些奇奇怪怪的 dfs 去暴力判定，但这样回超时，~~主要是我不会写~~，所以想到哈希，实测数据太水直接把 $size$ 作为哈希值就能过。

接下来要解决的问题是怎么还原，前面提到了孩子个数，我们考虑从满二叉树上删一个点：

1. 删的是叶子，此时会有一个节点只有一个孩子，直接把删掉的节点加在这个节点上即可。

2. 否则，会有一个节点用一个孩子换来两个孩子，则有 $3$ 个孩子，我们把换来的两个孩子接到被删掉的节点上，然后把被删掉的节点接到这个节点上。

现在有一个问题，怎么确定哪两个孩子是换来的呢？

考虑到删除这个操作，会使换来的孩子的 $size$ 和 $deep$ 都比原有的孩子小，但我猜测这样可能会导致更多的特判和边界情况，所以我直接暴力枚举哪个孩子是原有的孩子，然后每种情况都操作一遍，反正只是多判了两次，不过这个做法如果扩展到满 $k$ 叉数上时间复杂度就不对了，所以感兴趣的可以试着写写怎么不暴力的判，不过不影响做这个题。

最后的问题是我们一开始假设了已知根节点，~~主要是我读错题了默认 $1$ 是根~~，所以我们需要找根，我们发现，删一个节点后的树会很接近满二叉树，所以根到叶子的最长链的长度差不多，而且会有很多叶子能使得这条链的长度等于其在没删的时候的长度，所以发现整课树的直径不会随删一个节点而改变太多，而根一定是直径的中点，我们只需要随便找一条直径，把中点当作根判一遍就可以了，特别的，当直径长度是偶数时，靠中间的两个点都得判，这个做法同时告诉我们答案的个数是 $O(1)$ 的，上面对于一个已知的根需要用 $O(n)$ 的时间求，所以整体上时间复杂度是 $O(n)$ 的，于是我们顺带着证明了时间复杂度。

由于宏定义可能用到的比较多，但没全用上，同时直接放程序会因火车头导致题解被打回，我直接放 CF 上的[提交记录](https://codeforces.com/contest/1228/submission/263097392)。

---

## 作者：WLHW (赞：2)

考虑生成树的直径上的点的个数 $（ans）$
-  如果 $ans$ 为偶数，则删去的点一定为根节点的某个子节点，而且此直径中间的两个节点可以构成新的高度为 $ans/2$ 的两棵完全二叉树
   
&#160;&#160;&#160;&#160;&#160;&#160;所以，只要判断这两个结点下的二叉树是否为  高 $=ans/2$ 的满二叉树即可。如果是，则答案为 $2$ 个（这两个节点）；否则，为 $0$ 
![](https://img-blog.csdnimg.cn/20191001155400337.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQwMDMyMjc4,size_16,color_FFFFFF,t_70)

- 如果ans为奇数，则删去的点不为根节点的某个子节点，所以直径上中间的点为根节点，然后判断这个树（高度为n）是不是只有一个结点的容错量即可。如果是，答案只有一个，即出错的结点；否则，为 $0$。

&#160;&#160;&#160;&#160;&#160;&#160;**如何判断出错**：（为了方便在判断前我们给根节点的度+1）
		
		1. 如果该节点的度为1，它是叶子结点
		2. 如果该节点的度为2，它是叶子结点的父亲	
		3. 如果该节点的度为4：记它的三个儿子到叶子结点（叶子结点高度=1）的高度为h，它的深度为dep（根节点深度为1）。dep+h1，dep+h2，dep+h3，等于 n，n-1，n-1。而且这三个儿子下面应该为三棵高度为 h1，h2，h3 的完全二叉树。.
&#160;&#160;&#160;&#160;&#160;&#160;**如果违背以上3条，则判为出错**



```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int next,to;
} a[1000010];
int head[1000010],cnt=0,pre[1000010],in[1000010],ans;
int tot=0,tot_1=0,h[1000010],vis[1000010],d[1000010];
int high[1000010];
void add(int u,int v)
{
	a[++cnt].next=head[u];
	a[cnt].to=v;
	head[u]=cnt;
}
int dfs(int x) // 获得直径 
{
	int s;
	memset(vis,0,sizeof(vis));
	queue<int>q;
	q.push(x);
	d[x]=0,vis[x]=1;
	ans=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u]; i!=-1; i=a[i].next)
		{
			int v=a[i].to;
			if(vis[v]) continue;
			vis[v]=1;
			d[v]=d[u]+1;
			pre[v]=u;
			if(ans<d[v]) ans=d[v],s=v,pre[v]=u;
			q.push(v);
		}
	}
	return s;
}
void check_1(int u,int fa,int dep,int n)  // 判断树是否为 完全二叉树 （ 高度=n ） 
{
	if((dep==n&&in[u]==1)||(dep<n&&in[u]==3));
	else
	{
		tot_1++;
		return;
	}
	for(int i=head[u]; i!=-1; i=a[i].next)
	{
		int v=a[i].to;
		if(v==fa) continue;
		check_1(v,u,dep+1,n);
	}
}
void get(int u,int fa)  // 获得结点的高度 
{
	high[u]=0;
	for(int i=head[u]; i!=-1; i=a[i].next)
	{
		int v=a[i].to;
		if(v==fa) continue;
		get(v,u);
		high[u]=max(high[v],high[u]);
	}
	high[u]++;
}
void check_2(int u,int fa,int dep,int n) // 判断容错是否只为 1 
{
	if(in[u]==1&&dep!=n) tot=10;
	else if(in[u]==2)
	{
		if(dep==n-1) h[++tot]=u;
		else tot=10;
	}
	else if(in[u]==4)
	{
		int son[10],s=0;
		for(int i=head[u]; i!=-1; i=a[i].next)
		{
			int v=a[i].to;
			if(v==fa) continue;
			son[++s]=v;
		}
		int x=high[son[1]]+dep,y=high[son[2]]+dep,z=high[son[3]]+dep;
		if((x==n&&y==n-1&&z==n-1)||(x==n-1&&y==n&&z==n-1)||(x==n-1&&y==n-1&&z==n))
		{
			// 判断这三个儿子下是否为完全二叉树 
			check_1(son[1],u,dep+1,x);
			check_1(son[2],u,dep+1,y);
			check_1(son[3],u,dep+1,z);
			if(tot_1) tot=10;
			else h[++tot]=u;
		}
		else tot=10;
		return ;
	}
	for(int i=head[u]; i!=-1; i=a[i].next)
	{
		int v=a[i].to;
		if(v==fa) continue;
		check_2(v,u,dep+1,n);
	}
}
int main()
{
	int n,i,x,y,s,t;
	scanf("%d",&n);
	memset(head,-1,sizeof(head));
	for(i=1; i<=pow(2,n)-3; i++)
	{
		scanf("%d%d",&x,&y);
		in[x]++,in[y]++;
		add(x,y),add(y,x);
	}
	s=dfs(1);
	t=dfs(s);
	ans++;
	if(ans%2)
	{
		ans=(ans+1)/2;
		int ok=0;
		for(i=t; i!=s; i=pre[i])  // 获得根 
		{
			ok++;
			if(ok==ans)
			{
				x=i;
				break;
			}
		}
		get(x,0);
		in[x]++;
		check_2(x,0,1,n);
		if(tot!=1) return puts("0"),0;
		printf("1\n%d",h[1]);
	}
	else
	{
		ans=ans/2;
		int ok=0;
		for(i=t; i!=s; i=pre[i]) // 获得中间的两个节点 
		{
			ok++;
			if(ok==ans)
			{
				x=i;
				y=pre[i];
				break;
			}
		}
		check_1(x,y,1,ans);
		check_1(y,x,1,ans);
		if(tot_1) return puts("0"),0;
		printf("2\n%d %d",min(x,y),max(x,y));
	}
	return 0;
}
```


---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF1228F) & [CodeForces题目页面传送门](https://codeforces.com/contest/1228/problem/F)

>给定一棵树$T=(V,E),|V|=2^n-2,|E|=2^n-3$，输出所有的$x$，使得存在一棵满二叉树$T'$，将$T'$中节点$x$的一个儿子删除并把这个儿子的所有儿子接到$x$下后等于$T$。升序输出。

>$n\le17$。

题目没有说以哪个点为根，也就是每个点都有可能是根，很自然地想到可以二次扫描与换根。先考虑选一个点作为根，那显然满足条件的改补的节点的父结点最多有$1$个。这个父结点可以DP出来。

我们将一个子树分类讨论：

1. 是一棵满二叉树。设它的深度为$d$，则记这颗子树的特征为有序对$(0,d)$。这种情况发生当且仅当它有$2$棵子树并且都是矮$1$层的满二叉树。特殊地，如果它的大小为$1$，则它的特征为$(0,1)$；
2. 还原一个节点之后为满二叉树。设还原之后的深度为$d$，补的节点的父结点为$x$，则记这棵子树的特征为有序对$(x,d)$。这种情况发生当且仅当以下任意一个条件为真：

   1. 它的根为$x$，有$1$棵子树并且这棵子树大小为$1$，此时应将改补的节点直接补在$x$下；
   2. 它的根为$x$，有$3$棵子树并且其中$1$棵为矮$1$层的满二叉树，另$2$棵为矮$2$层的满二叉树，此时应将改补的节点补在$x$下并将$2$棵矮$2$层的字树接在改补的节点下；
   3. 它有$2$棵子树并且一棵为矮$1$层的满二叉树，另一颗补一个父结点为$x$的节点之后为矮$1$层的满二叉树；
3. 不管补不补节点都不能成为满二叉树。记它的特征为有序对$(-1,-1)$。显然，不满足$1,2$则为此种情况。

设$dp_i$为以$1$为根时以$i$为根的子树的特征，则状态转移方程是（太♂难写已隐藏）。这样一遍$\mathrm O(2^n)$DFS则可求出所有节点的DP值。而我们希望找到所有节点为根时的根节点DP值，这个可以二次扫描与换根，即再一遍DFS。每到达一个节点$x$时，目前所有节点的DP值均是以$x$为整棵树的根的，所以若$dp_x=(y,n)(y>0)$，就将$y$加入答案序列。那么此时若要将它的某个儿子$s$改为根，那么改变的只有$dp_x$和$dp_s$。我们可以改一下它们的儿子集合（涉及添加和删除，用`set`较为方便），重新算DP值，然后再DFS到$s$，此时整棵树的根为$s$了。从$s$回溯时，再还原$x$和$s$的儿子集合和DP值，去找别的儿子即可。由于换根操作只需要改变$2$个节点的信息，所以复杂度是有保证的，一共$\mathrm O(2^n\log_22^n)=\mathrm O(2^nn)$（$\log$是`set`）。

下面贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=17;
int n;
vector<int> nei[1<<N];//邻接表 
set<int> son[1<<N];//儿子集合
void dfs(int x=1,int fa=0){//求出所有节点的儿子集合 
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		son[x].insert(y);
		dfs(y,x);
	}
}
pair<int,int> f[1<<N];//DP值，即以[1]为根的子树的特征 
void calc_f(int x){//通过儿子集合计算DP值，即那个难写的状态转移方程 
	if(son[x].size()==0)f[x]=mp(0,1);
	else if(son[x].size()==1)f[x]=f[*son[x].begin()]==mp(0,1)?mp(x,2):mp(-1,-1);
	else if(son[x].size()==2){
		pair<int,int> x1=f[*son[x].begin()],x2=f[*++son[x].begin()];
		if(x1>x2)swap(x1,x2);
		if(!x1.X&&!x2.X)f[x]=x1.Y==x2.Y?mp(0,x1.Y+1):mp(-1,-1);
		else if(!x1.X&&x2.X>0)f[x]=x1.Y==x2.Y?mp(x2.X,x1.Y+1):mp(-1,-1);
		else f[x]=mp(-1,-1);
	}
	else if(son[x].size()==3){
		pair<int,int> x1=f[*son[x].begin()],x2=f[*++son[x].begin()],x3=f[*++ ++son[x].begin()];
		if(x1>x2)swap(x1,x2);if(x2>x3)swap(x2,x3);if(x1>x2)swap(x1,x2);
		if(!x1.X&&!x2.X&&!x3.X)f[x]=x1.Y==x2.Y&&x2.Y+1==x3.Y?mp(x,x3.Y+1):mp(-1,-1);
		else f[x]=mp(-1,-1);
	}
	else f[x]=mp(-1,-1);
//	printf("f[%d]=(%d,%d)\n",x,f[x].X,f[x].Y);
}
void dp(int x=1,int fa=0){//一遍DFS求出以1为整棵树的根时的DP数组 
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dp(y,x);
	}
	calc_f(x);
}
vector<int> ans;//答案序列 
void dfs0(int x=1,int fa=0){//二次扫描 
	if(f[x].X>0)ans.pb(f[x].X);//加入答案序列 
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		son[x].erase(y);son[y].insert(x);calc_f(x);calc_f(y);//改变儿子集合，重新算DP值 
		dfs0(y,x);
		son[x].insert(y);son[y].erase(x);calc_f(y);calc_f(x);//还原 
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=(1<<n)-3;i++){
		int x,y;
		cin>>x>>y;
		nei[x].pb(y);nei[y].pb(x);
	}
	dfs(); 
	dp();
	dfs0();
	cout<<ans.size()<<"\n";
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：ReseeCher (赞：0)

首先，注意到n>=3时，只有树的重心有可能作为原树的根

因为树的重心最多有两个，所以可以枚举根

接下来就可以方便地找到哪些点有可能是被删点的父节点，具体有以下3种情况：

1.根的度数为3（删的是根的子节点）

2.节点度数为4（删的是非根非叶节点）

3.节点度数为1（删的是叶节点）

找到这个"可能节点后"，我的做法是通过暴力模拟出填上一个节点后树的形态判断是否合法

当n=2时，因为数据只有一种，特判即可

比赛时胡乱写的代码码风比较烂，请见谅

```cpp
//ios::sync_with_stdio(false);
#include<bits/stdc++.h>
#define LL long long
#define F(x,y,z) for(int x=y;x<=z;++x)
#define D(x,y,z) for(int x=y;x>=z;--x)
using namespace std;
const int N=151000;
LL Min(LL x,LL y){return x<y?x:y;}
LL Max(LL x,LL y){return x>y?x:y;}
LL R(){
    LL ans=0,f=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if (c=='-') f=-1;
    for(;c>='0'&&c<='9';c=getchar()) ans=ans*10+c-'0';
    return ans*f;
}
int n,m,siz[N],ms[N],mi,dep[N],nn;
int ok[N],fa[N],siz2[N];
vector<int> v[N],vv,v2[N];
void dfs(int u,int ff){
	siz[u]=1;
	for(auto to:v[u])
		if(to!=ff){
		dfs(to,u);
		ms[u]=max(ms[u],siz[to]);
		siz[u]+=siz[to];
	}
	ms[u]=max(ms[u],nn-siz[u]);
}
void dfs2(int u,int ff){
	fa[u]=ff;
	siz2[u]=1;
	for(auto to:v[u])if(to!=ff){
		dep[to]=dep[u]+1;
		dfs2(to,u);
		siz2[u]+=siz2[to];
	}
}
void dfs3(int u,int ff){
	dep[u]++;
	for(auto to:v[u])if(to!=ff){
		dfs3(to,u);
	}
}
void Sol(int rt){
	if(v[rt].size()!=2&&v[rt].size()!=3)return;
	memset(dep,0,sizeof(dep));
	memset(fa,0,sizeof(fa));
	memset(siz2,0,sizeof(siz2));
	dep[rt]=1;
	dfs2(rt,0);
	int cnt=0,now=-1;
	if(v[rt].size()==3)cnt=1,now=rt;
	F(i,1,nn){
		if(i==rt)continue;
		if(v[i].size()==1)continue;
		if(v[i].size()==2)++cnt,now=i;
		if(v[i].size()==4)++cnt,now=i;
	}
	if(cnt!=1)return;
	int cc=0;
	for(auto to:v[now]){
		if(to==fa[now])continue;
		if(siz2[to]==ok[dep[to]])continue;
		++cc;
		dfs3(to,now);
	}
	int u=now;
	while(u)siz2[u]++,u=fa[u];
	if(cc!=0&&cc!=2)return;
	F(i,1,nn)if(ok[dep[i]]!=siz2[i])return;
	vv.push_back(now);
}
int main(){
	
	n=R();m=(1<<n)-3;nn=(1<<n)-2;
	F(i,1,n)ok[i]=(1<<(n-i+1))-1;
	if(n==2){
		printf("2\n1 2\n");
		return 0;
	}
	F(i,1,m){
		int x=R(),y=R();
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	mi=nn+1;
	F(i,1,nn)mi=min(mi,ms[i]);
	F(i,1,nn)if(mi==ms[i])Sol(i);
	cout<<vv.size()<<'\n';
	sort(vv.begin(),vv.end());
	for(auto i:vv)cout<<i<<' ';
	cout<<'\n';
    return 0;
}
```

---

