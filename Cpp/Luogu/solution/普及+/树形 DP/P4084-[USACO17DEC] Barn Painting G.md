# [USACO17DEC] Barn Painting G

## 题目描述

Farmer John 有一个大农场，农场上有 $N$ 个谷仓（$1 \le N \le 10^5$），其中一些已经涂色，另一些尚未涂色。Farmer John 想要为这些剩余的谷仓涂色，使得所有谷仓都被涂色，但他只有三种可用的油漆颜色。此外，他的获奖奶牛 Bessie 如果发现两个直接相连的谷仓颜色相同，会感到困惑，因此他希望确保这种情况不会发生。

保证 $N$ 个谷仓之间的连接不会形成任何“环”。也就是说，任意两个谷仓之间最多只有一条连接路径。

Farmer John 有多少种方式可以为剩余的未涂色谷仓涂色？

## 样例 #1

### 输入

```
4 1
1 2
1 3
1 4
4 3```

### 输出

```
8```

# 题解

## 作者：LlLlCc (赞：23)

经典的**树形DP**，适合入门练手

进入正题：

- f[i][j]表示i这个点上色为j是方案数（**从下往上/从子节点向父节点更新**）
- 即对于所有初始节点，**f[i][1],f[i][2],f[i][3]都为1**
- 当某个节点被指定上色后，那么该节点另外两种颜色的方案数为0。
  
  列如:当点x被指定上色 2 时：f[x][1]=0,f[x][3]=0 (因为无法上色1和3）
- 对于每个节点，因为不能于子节点上色相同,即：

```
   f[x][0]=f[x][0]*(f[son[i]][1]+f[son[i]][2]);
   f[x][1]=f[x][1]*(f[son[i]][0]+f[son[i]][2]);
   f[x][2]=f[x][2]*(f[son[i]][1]+f[son[i]][0]);
```

- 最后，记得**取模和开long long**

代码参考：

```
#include<bits/stdc++.h>
#define maxn 200005
#define ll long long
using namespace std;
const int TT=1e9+7;
int n,x,y,lnk[maxn],nxt[maxn],son[maxn],tot,m;
ll f[maxn][3];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void Dfs(int x,int fa){
	for (int i=0;i<3;i++){
		if (f[x][i]){for (int j=0;j<i;j++) f[x][j]=0;break;}
		f[x][i]=1;
	}
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=fa){
	  	Dfs(son[i],x);
	  	f[x][0]=f[x][0]*((f[son[i]][1]+f[son[i]][2])%TT)%TT;
                f[x][1]=f[x][1]*((f[son[i]][0]+f[son[i]][2])%TT)%TT;
                f[x][2]=f[x][2]*((f[son[i]][1]+f[son[i]][0])%TT)%TT;
	  }
}
int main(){
	n=read(),m=read();
	for (int i=1;i<n;i++) x=read(),y=read(),add(x,y),add(y,x);
	for (int i=1;i<=m;i++) x=read(),y=read()-1,f[x][y]=1;
	Dfs(1,0);
	printf("%lld",(f[1][0]+f[1][1]+f[1][2])%TT);
	return 0;
}
```


---

## 作者：Okarin (赞：12)

又是一道树形dp的题

这道题和[P1352 没有上司的舞会](https://www.luogu.org/problemnew/show/P1352)还是挺像的，这个可能更加复杂一些。不过我觉得难度可能都还属于树形dp的入门题。

树形dp本质上来说就是dfs一遍树然后进行递推，这道题中可以开个二维的数组dp[i][j]表示编号为i的点涂上j颜色的方案数。

显然每个点的方案数和它的子树是有关的，所以我们要先遍历到叶子节点然后一步步往回推。

由于相邻的点颜色不能相同，所以转移的时候只能由颜色不同的转移过来。且当前点的方案数应为其子树方案数的乘积。打个比方，对于点i来说,它有两个子树j,k。那么转移方程应为

```cpp
dp[i][1]*=(dp[j][2]+dp[j][3])*(dp[k][2]+dp[k][3]);

dp[i][2]*=(dp[j][1]+dp[j][3])*(dp[k][1]+dp[k][3]);

dp[i][3]*=(dp[j][1]+dp[j][2])*(dp[k][1]+dp[k][2]);
```

至于为什么是*=，这就涉及到了dp初始值的设立。

对于一个最初没有涂色的点i，很显然刚遍历到的时候我们设置点i的初始值
dp[i][1]=dp[i][2]=dp[i][3]=1;

而如果点i已经被上色了，那么只有~~被上的颜色~~的数组才能为1(dp[i][col[i]]=1)，而其他2个都为0。

所以之前用*=来更新保证了如果当前点已经被上色了的话，上其他颜色的方案数为0。

然后随便选个点i为根跑一遍dfs输出dp[i][1]+dp[i][2]+dp[i][3]就好了

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define p 1000000007
#define LL long long
using namespace std;
inline int read()
{
    int sum=0;
    char ch =getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum;
}
int n,m,tot=0;
int Head[100005],col[100005];//Head用于邻接表  col记录颜色
LL dp[100005][4];
bool visit[100005];//由于存图为无向图，所以要记录下已经走过的点防止死循环
struct tree
{
    int next,node;
}h[200010];
inline void add(int u,int v)//邻接表存图
{
    h[++tot].next=Head[u];
    h[tot].node=v;
    Head[u]=tot;
}
void dfs(int pos)//dfs遍历
{
    visit[pos]=1;
    if(col[pos])//如果已经上过色了，其他两种颜色的方案数为0。
        dp[pos][col[pos]]=1;
    else//三种颜色都可以被♂上
    {
        dp[pos][1]=1;
        dp[pos][2]=1;
        dp[pos][3]=1;
    }
    for(register int i=Head[pos];i;i=h[i].next)//找到当前点所有的子节点
    {
        int v=h[i].node;
        if(!visit[v])
        {
            dfs(v);//一直向下遍历直到叶子节点返回
            dp[pos][1]=dp[pos][1]*((dp[v][2]+dp[v][3])%p)%p;
            dp[pos][2]=dp[pos][2]*((dp[v][1]+dp[v][3])%p)%p;
            dp[pos][3]=dp[pos][3]*((dp[v][2]+dp[v][1])%p)%p;//转移  记得取模！
        }
    }
}
int main()
{
    int x,y;
    n=read();
    m=read();
    for(register int i=1;i<n;++i)
    {
        x=read();
        y=read();
        add(x,y);
        add(y,x);//加边
    }
    for(register int i=1;i<=m;++i)
    {
        x=read();
        y=read();
        col[x]=y;//记录颜色
    }
    dfs(1);//随便把一个点当根就好了
    cout<<(dp[1][1]+dp[1][2]+dp[1][3])%p<<endl;
    return 0;
}
```

---

## 作者：45dino (赞：5)

一道有趣的树型DP。

一看到XXDP，就莫名有种恐惧感，但树形DP看上去并不难——不就是在树上跑DP吗？

可以用DFS确定每个点的可能性，对于每个节点，不能和子节点相同，故推出状态转移方程：
```
  f[x][0]=f[x][0]*(f[son[i]][1]+f[son[i]][2]);
  f[x][1]=f[x][1]*(f[son[i]][0]+f[son[i]][2]);
  f[x][2]=f[x][2]*(f[son[i]][1]+f[son[i]][0]);
```
由于不可能有环，一个点的赋值只有可能有一次，所以当这个点的初始值不为0是，说明已经在条件中被染过色了。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
#define int long long//要用long long的题目这样定义再好不过了
using namespace std;
int n,k,cnt,f[4][1000002],head[1000002];//好像开100001的数组会RE，不知道为什么，调大10倍以后就没问题了。
struct node{
	int next,to;
} road[1000002];
void add(int x,int y)//链式前向星存树
{
	road[++cnt].to=y;
	road[cnt].next=head[x];
	head[x]=cnt;
}
void dfs(int x,int fa)
{
	for(int i=1;i<=3;i++)
	{
		if(f[i][x])//如果已经被赋过初值了，就不能再赋其他值了
		{
			for(int j=1;j<i;j++)
				f[j][x]=0;
			break;
		} 
		f[i][x]=1;
	}
	for(int i=head[x];i;i=road[i].next)
	{
		int v=road[i].to;
		if(v!=fa)//避免死循环
		{
			dfs(v,x);
			f[1][x]=f[1][x]*((f[2][v]+f[3][v])%1000000007)%1000000007;//记得取模
			f[2][x]=f[2][x]*((f[1][v]+f[3][v])%1000000007)%1000000007;
			f[3][x]=f[3][x]*((f[1][v]+f[2][v])%1000000007)%1000000007;
		}
	}
}
signed main()//main函数不能用long long，只能用signed
{
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	for(int i=1;i<=k;i++)
	{
		int a,b;
		cin>>a>>b;
		f[b][a]=1;
	}
	dfs(1,0);
	cout<<(f[1][1]+f[2][1]+f[3][1])%1000000007;//最后再取一次膜
	return 0;
}
```


---

## 作者：FourteenObsidian (赞：3)

这种树上问题显然是树形DP啦

令 $f[i][j]$ 表示 **当 $i$ 号节点 取颜色 $j$ 时其子树总共的状态数**;

$ced[i]$ 表示 **$i$ 号节点最初是否被染色，如已被染色是哪种颜色**。

搜索时分类判断即可（具体看代码）。

时间复杂度 $O(n)$。

代码：


```cpp
#include<bits/stdc++.h>
#define int long long
#define I inline
const int N = 100010; 
using namespace std;
struct Edge
{
	int to,next;
}edge[N * 2];
int n, k, f[N][4], ced[N], cnt = 0, vis[N], head[N], mod = 1000000007;
I void add(int x,int y)
{
	edge[++cnt].to = y;
	edge[cnt].next = head[x];
	head[x] = cnt;
}
I void init()//读入
{
	memset(ced, 0, sizeof(ced));
	scanf("%lld%lld", &n, &k);
	int x,y;
	for(int i = 1; i < n; ++i)
    {
		scanf("%lld%lld", &x, &y);
		add(x, y), add(y, x);
	}
	for(int i = 1; i <= k; ++i)
		scanf("%lld%lld", &x, &y), ced[x] = y;
	return;
}
I void slove(int x)//搜索
{
	vis[x] = 1;//标记为已访问
	if(ced[x]) f[x][ced[x]] = 1; //如已被染色，则对于当前节点只有固定的一种取法
	else f[x][1] = f[x][2] = f[x][3] = 1;//否则三种取法皆可
	for(int i = head[x]; i; i = edge[i].next)
    {
		int y = edge[i].to;
		if(vis[y]) continue;//防止访问父亲造成死循环
		slove(y);
		f[x][1] = f[x][1] * ((f[y][2] + f[y][3]) % mod) % mod;
		f[x][2] = f[x][2] * ((f[y][1] + f[y][3]) % mod) % mod;
		f[x][3] = f[x][3] * ((f[y][1] + f[y][2]) % mod) % mod;//乘法原理，算出这个子节点取其他的两种颜色的贡献
	}
	return;
}
signed main()
{
	init();
	slove(1);
	printf("%lld\n", ced[1] ? f[1][ced[1]] % mod : (f[1][1] + f[1][2] + f[1][3]) % mod);//如果根节点最初已被确定颜色，则只算它颜色的贡献
    //否则三种颜色的贡献都算上
	return 0;
}

```


---

## 作者：eee_hoho (赞：2)

考虑树上dp，设$f_{u,i}$表示以u为根的子树中，u被染成i这个颜色的方案数，于是考虑状态转移方程

如果这个点被指定染色了，那么有

$$f_{u,c_u}=\prod_{v\in son(u)}\sum_{i=1}^3 f_{v,i}\ \ (i\ne c_u)$$

因为假如u选了一个颜色，那么它的每个儿子都只能有两种颜色可选，先用加法原理统计儿子可选的颜色，然后再用乘法原理统计这棵子树的答案

然后可以得出未被指定颜色点的方程

$$\begin{cases}f_{u,1}=\prod_{v\in son(u)}\ \ (f_{v,2}+f_{v,3})& \\f_{u,2}=\prod_{v\in son(u)}\ \ (f_{v,1}+f_{v,3})& \\f_{u,3}=\prod_{v\in son(u)}\ \ (f_{v,1}+f_{v,2})&
\end{cases}$$

这样就做完了QAQ

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
const int N = 1e5;
const int p = 1e9 + 7;
using namespace std;
int n,k,c[N + 5],f[N + 5][4];
vector <int> d[N + 5];
void dfs(int u,int fa)
{
    vector <int>::iterator it;
    int sum[4] = {1,1,1,1};
    for (it = d[u].begin();it != d[u].end();it++)
    {
        int v = (*it);
        if (v == fa)
            continue;
        dfs(v,u);
        if (c[u])
        {
            int s = 0;
            for (int i = 1;i <= 3;i++)
                if (i != c[u])  
                    s = (s + f[v][i]) % p;
            sum[c[u]] = 1ll * sum[c[u]] * s % p;
        }
        else
            for (int i = 1;i <= 3;i++)
            {
                int s = 0;
                for (int j = 1;j <= 3;j++)
                    if (i != j)
                        s = (s + f[v][j]) % p;
                sum[i] = 1ll * sum[i] * s % p;
            }
    }
    if (c[u])
        f[u][c[u]] = sum[c[u]];
    else
        for (int i = 1;i <= 3;i++)
            f[u][i] = sum[i];
}
int main()
{
    scanf("%d%d",&n,&k);
    int u,v;
    for (int i = 1;i < n;i++)
    {
        scanf("%d%d",&u,&v);
        d[u].push_back(v);
        d[v].push_back(u);
    }
    for (int i = 1;i <= k;i++)
    {
        scanf("%d%d",&u,&v);
        c[u] = v;
    }
    dfs(1,0);
    cout<<((f[1][1] + f[1][2]) % p + f[1][3]) % p<<endl;  
    return 0;
}
```

---

## 作者：abandentsky (赞：1)

题意：给出一棵无根树，树上有一部分节点已经涂好了颜色，其他的节点需要你涂上颜色，问最后的方案数。就是一道水题。dp[i][j]表示以i为根的子树，并且i的颜色涂成j。转移方程也好写，就是把i的几个儿子节点的方案数乘起来就好了。
dp[root][1]=(dp[root][1]*(dp[v][2]+dp[v][3])%mod)%mod; 
dp[root][2]=(dp[root][2]*(dp[v][1]+dp[v][3])%mod)%mod;
dp[root][3]=(dp[root][3]*(dp[v][1]+dp[v][2])%mod)%mod;
千万千万别忘了取模，别忘了。
```c
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define MAXN 100005
#define mod 1000000007
#define INF 0x3f3f3f3f
using namespace std;

int n,k;
struct Edge
{
    int from,to;
    Edge(int from=0,int to=0):from(from),to(to){};
};
vector<Edge> edges;
vector<int> G[MAXN];
long long val[MAXN];
long long dp[MAXN][4];

void dfs(int root,int fa)
{
    dp[root][1]=dp[root][2]=dp[root][3]=1;
    if(val[root])                                                 //这个节点已经涂好了颜色
    {
        for(int i=1;i<=3;i++)                            //尝试三种颜色
        {
            if(i!=val[root])                                   //想要涂的颜色不一样就直接置为0
                dp[root][i]=0;
        }
    }
    for(int i=0;i<G[root].size();i++)
    {
        Edge &e=edges[G[root][i]];
        int v=e.to;
        if(v==fa)
            continue;
        dfs(v,root);
        dp[root][1]=(dp[root][1]*(dp[v][2]+dp[v][3])%mod)%mod;
        dp[root][2]=(dp[root][2]*(dp[v][1]+dp[v][3])%mod)%mod;
        dp[root][3]=(dp[root][3]*(dp[v][1]+dp[v][2])%mod)%mod;
    }
}

int main()
{
    scanf("%d %d",&n,&k);
    int u,v;
    for(int i=1;i<n;i++)
    {
        scanf("%d %d",&u,&v);
        edges.push_back({u,v});
        edges.push_back({v,u});
        int mm=edges.size();
        G[u].push_back(mm-2);
        G[v].push_back(mm-1);
    }
    //printf("ok\n");
    for(int i=1;i<=k;i++)
    {
        int kk,op;
        scanf("%d %d",&kk,&op);
        val[kk]=op;
    }
    memset(dp,INF,sizeof(dp));
    dfs(1,-1);
    long long ans=0;
    for(int i=1;i<=3;i++)
        ans+=dp[1][i];
    printf("%lld\n",ans%mod);
    return 0;
}

```


---

## 作者：KillerXu (赞：1)

很基础的一道树形dp。

设$f[i][j]$表示 以染第$j$种颜色的节点为根的子树的染色方案数。

$$f[i][1]= \prod(f[son][2]+f[son][3])$$

$$f[i][2]= \prod(f[son][1]+f[son][3])$$

$$f[i][3]= \prod(f[son][1]+f[son][2])$$

具体实现，把1号节点作为整棵树的根，然后先递归下去赋初值1，合并时转移方程。注意不管是赋初值还是转移方程，都要判断这个点是否是那$K$个已经染过色的节点，如果已经染过色，仅对$j=$这个颜色 的情况进行操作。

## Code
```cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define mod 1000000007
#define N 100005

using namespace std;

long long f[N][4];
int n , k;
int val[N];
struct Edge{
	int to , next;
}edge[N << 1];
int head[N] , tot = 0;

void add(int u , int v){
	edge[++tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
}

void dfs(int x , int fa){
	for(int i = 1; i <= 3; i++) if(val[x] == i || !val[x]) f[x][i] = 1;//赋初值 
	for(int i = head[x]; i; i = edge[i].next){//向下递归 
		int v = edge[i].to;
		if(v == fa) continue;//注意连向父亲的边不能去 
		dfs(v , x);
	}
	for(int i = head[x]; i; i = edge[i].next){//合并答案 
		int v = edge[i].to;
		if(v == fa) continue;
		if(val[x] == 1 || !val[x]) f[x][1] = (f[x][1] * (f[v][2] + f[v][3]) % mod) % mod;//转移 
		if(val[x] == 2 || !val[x]) f[x][2] = (f[x][2] * (f[v][1] + f[v][3]) % mod) % mod;
		if(val[x] == 3 || !val[x]) f[x][3] = (f[x][3] * (f[v][1] + f[v][2]) % mod) % mod;
	}
}
		
int main(){
	scanf("%d%d" , &n , &k);
	for(int i = 1; i < n; i++){
		int u , v;
		scanf("%d%d" , &u , &v);
		add(u , v);
		add(v , u);
	}
	for(int i = 1; i <= k; i++){
		int p , c;
		scanf("%d%d" , &p , &c);
		val[p] = c;
	}
	
	dfs(1 , 0);
	
	printf("%lld" , (f[1][1] + f[1][2] + f[1][3]) % mod);
	
	return 0;
}
```

---

## 作者：曹老师 (赞：1)

~~一篇题解也没有？蒟蒻来写一篇吧~~

很明显 **树形DP**

**main部分**

因为可能有0的情况 所以开始先将dp清为-1

然后根据1 2 3三种情况循环dfs就可以了

**dfs部分**

o为当前节点编号 c为当前颜色 p为上一节点编号

显然 如果c=1 子节点只能染 2，3 ~~同理（三个丑if~~

接下来就是判断是否已经被染过色 如果已经被题目中染过色

就直接清0 如果大于0了（我们设置的初始值为-1

证明已经计算出来了 所以就直接返回

然后就是把每一个节点的方法都加起来相乘 然后 % 即可

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define INF 2147483640
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define init(n) scanf("%d",&n);
#define ans() printf("%d",ans);
#define initt(n,m) scanf("%d%d",&n,&m);
#define scan(a,b) scanf("%d%d",&a,&b);
using namespace std;
const int L=100005;
int n,m,tu[L];
LL int dp[L][5],ans=0;
vector<int>tree[L];
LL int  dfs(int o,int c,int p)
{
	int a,b;
	if(c==1)
		a=2,b=3;
	if(c==2)
		a=1,b=3;
	if(c==3)
		a=1,b=2;
	if(tu[o]&&tu[o]!=c)
		return dp[o][c]=0;
	if(dp[o][c]>=0)
		return dp[o][c];
	dp[o][c]=1;
	for(int i=0;i<tree[o].size();i++)
	{
		if(tree[o][i]==p)
			continue;
		int sum=0;
		sum+=dfs(tree[o][i],a,o);
		sum+=dfs(tree[o][i],b,o);
		sum%=MOD;
		dp[o][c]*=sum;
		dp[o][c]%=MOD;
	}
	return dp[o][c];
}
int main()
{
	memset(dp,-1,sizeof(dp));
	initt(n,m);
	for(int i=1;i<n;i++)
	{
		int t1,t2;
		scanf("%d%d",&t1,&t2);
		tree[t1].push_back(t2);
		tree[t2].push_back(t1);
	}
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scan(a,b);
		tu[a]=b;
	}
	for(int i=1;i<=3;i++)
		dfs(1,i,0);
	ans=(dp[1][1]+dp[1][2]+dp[1][3])%MOD;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Erusel (赞：0)

可以考虑树形dp

我们用$f[i][j]$表示$i$号点涂上$j$颜色的方案数

设$u->v$有一条边,对于三种颜色，因为相邻的颜色不能相同

所以如果$u$节点涂了$1$号颜色，那么$v$节点只能涂$2,3$号颜色

根据乘法原理，dp方程为：

$f[u][1]=f[u][1]*(f[v][2]+f[v][3])$

$f[u][2]=f[u][2]*(f[v][1]+f[v][3])$

$f[u][3]=f[u][3]*(f[v][1]+f[v][2])$

注意多取模,还用记得开long long。

**code:**

```
#include<bits/stdc++.h>

#define N 100005
#define rd(x) x=read()
#define int long long

using namespace std;

int n,m;
int a[N],f[N][5];
int vis[N];
vector<int>e[N];
const int p=1e9+7;

inline void addEdge(int u,int v){e[u].push_back(v);}

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

void dfs(int u)
{
    if(!a[u])f[u][1]=f[u][2]=f[u][3]=1;
    else f[u][a[u]]=1;
    for(int i=0;i<e[u].size();i++)
    {
        int v=e[u][i];
        if(!vis[v])
        {
            vis[v]=1,dfs(v);
            (f[u][1]*=((f[v][2]+f[v][3])%p))%=p;
            (f[u][2]*=((f[v][1]+f[v][3])%p))%=p;
            (f[u][3]*=((f[v][1]+f[v][2])%p))%=p;
        }
    }
}

signed main() 
{
    rd(n),rd(m);
    for(int i=1;i<n;i++){int u,v;rd(u),rd(v);addEdge(u,v),addEdge(v,u);}
    for(int i=1;i<=m;i++){int u,v;rd(u),rd(v),a[u]=v;}

    vis[1]=1,dfs(1),printf("%lld\n",(f[1][1]+f[1][2]+f[1][3])%p);

    return 0;
}

```

---

## 作者：StephenYoung (赞：0)

这题树形dp+加法原理+乘法原理，不错的题。

用f[u][i]表示以u（染成i这种颜色）这个节点为根的子树内的方案总数，sum[u]表示u为根的子树的方案总数。所以根据乘法原理，有$f[u][i]*(sum[v]-f[v][i])$,

根据加法原理有
$sum[u]+=f[u][i]$

初始化除了k个固定节点，其余$f[u][i(1<=i<=3)]=1$

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mod 1000000007

using namespace std;

const int maxn=100000+10;
int head[maxn],f[maxn][5],sum[maxn],x[maxn];
int n,k,cnt;
bool vis[maxn];

struct Edge{
	int v,nxt;
}e[maxn];

void add(int u,int v)
{
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

void dfs(int u,int fa)
{
    for(int i=head[u];i;i=e[i].nxt)
    {
        int to=e[i].v;
        if(to==fa)continue;
        dfs(to,u);
        for(int i=1;i<=3;i++)
        {
            f[u][i]=((long long)f[u][i]*(sum[to]-f[to][i]+mod)%mod)%mod;
        }
    }
    for(int i=1;i<=3;i++)
    sum[u]+=f[u][i],sum[u]%=mod; 
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=k;i++)
	{
		int y;
		scanf("%d%d",&x[i],&y);
		f[x[i]][y]=1;
		vis[x[i]]=1;
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		for(int j=1;j<=3;j++)
		{
			f[i][j]=1;
		}
	}
	
	dfs(1,0);
	printf("%d",sum[1]);
	return 0;
}
```


---

## 作者：Starrydream (赞：0)

# [USACO17DEC]Barn Painting

## 题意翻译

题意：给定一颗N个节点组成的树，3种颜色，其中K个节点已染色，要求任意两相邻节点颜色不同，求合法染色方案数。 翻译贡献者：Il_ItzABC_lI

## 题目描述

Farmer John has a large farm with NN barns (1 \le N \le 10^51≤N≤105), some of which are already painted and some not yet painted. Farmer John wants to paint these remaining barns so that all the barns are painted, but he only has three paint colors available. Moreover, his prize cow Bessie becomes confused if two barns that are directly reachable from one another are the same color, so he wants to make sure this situation does not happen.

It is guaranteed that the connections between the NN barns do not form any 'cycles'. That is, between any two barns, there is at most one sequence of connections that will lead from one to the other.

How many ways can Farmer John paint the remaining yet-uncolored barns?

## 输入输出格式

输入格式：



The first line contains two integers NN and KK (0 \le K \le N0≤K≤N), respectively the number of barns on the farm and the number of barns that have already been painted.

The next N-1N−1 lines each contain two integers xx and yy (1 \le x, y \le N, x \neq y1≤x,y≤N,x≠y) describing a path directly connecting barns xx and yy.

The next KK lines each contain two integers bb and cc (1 \le b \le N1≤b≤N, 1 \le c \le 31≤c≤3) indicating that barn bb is painted with color cc.



输出格式：



Compute the number of valid ways to paint the remaining barns, modulo 10^9 + 7109+7, such that no two barns which are directly connected are the same color.



## 输入输出样例

输入样例#1：



```
4 1
1 2
1 3
1 4
4 3
```

输出样例#1：



```
8
```

## 题解

一道普通组合树形dp，D1T2难度。

所以我又被卡了n次。。唉。注意dp的数组初始值是否合适。

设：
$$
f(u,c)
$$
表示子树u在u染颜色c的时候方案数。

转移原始形式是所有子树每个颜色的卷积，复杂度会爆炸。

然后通过~~严密的证明~~灵敏的眼睛我们发现其实是子树的颜色和相乘，可以自己试着把下面的公式展开就明白了。
$$
f(u,c) = \prod_{v}\sum_{i=1}^{cnum}[i!=c]f(v,i)
$$
时间复杂度
$$
O(nc^2)
$$
实现注意细节问题！！（每次出这种问题我就担心我的联赛）

Code：

```c++
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define maxn 100005
#define mod 1000000007
int head[maxn] , cnt , n , m , vis[maxn];
long long f[maxn][4];
struct edge{
	int next , to;
}e[maxn*2];
//void dfs(int x , int fx)
//{
//	if(vis[x]){
//		f[x][vis[x]] = 1;
//		for(int i = head[x] ; i ; i = e[i].next){
//			if(e[i].to != fx){
//				dfs(e[i].to , x);
//				long long sum = 0;
//				for(int j = 1 ; j <= 3 ; ++j){
//					if(j != vis[x] && f[e[i].to][j] != -1)
//						(sum += f[e[i].to][j]) %= mod;
//					(f[x][vis[x]] *= sum) %= mod;
//				}
//			}
//		}
//	}
//	else{
//		for(int i = 1 ; i <= 3 ; ++i)
//			f[x][i] = 1;
//		for(int i = head[x] ; i ; i = e[i].next){
//			if(e[i].to != fx){
//				dfs(e[i].to , x);
//				for(int j = 1 ; j <= 3 ; ++j){
//					long long sum = 0;
//					for(int k = 1 ; k <= 3 ; ++k)
//						if(k != j && f[e[i].to][k] != -1)	(sum += f[e[i].to][k]) %= mod;
//					(f[x][j] *= sum) %= mod;
//				}
//					
//			}
//		}
//	}
//}
long long dp(int x , int c , int fx)
{
	if(f[x][c] != -1)	return f[x][c];
	f[x][c] = 1;
	if(vis[x] && vis[x] != c) return f[x][c] = 0;
	for(int i = head[x] ; i ; i = e[i].next)	
		if(e[i].to != fx){
			long long sum = 0;
			for(int j = 1 ; j <= 3 ; ++j)
				if(j != vis[x] && j != c)
					sum += dp(e[i].to , j , x) , sum %= mod;
			f[x][c] = (f[x][c] * sum) % mod;
		}
	return f[x][c];
}
inline void add(int x , int y)
{
	e[++cnt].next = head[x];
	e[cnt].to = y;
	head[x] = cnt;
}
int main()
{
//	freopen("colors.in","r",stdin);
	std::memset(f,-1,sizeof(f));
	scanf("%d%d",&n,&m);
	int x , y;
	for(int i = 1 ; i <= n-1 ; ++i)
		scanf("%d%d",&x,&y) , add(x,y) , add(y,x);
	for(int i = 1 ; i <= m ; ++i){
		scanf("%d%d",&x,&y);
		vis[x] = y;
	}
	long long ans = 1ll*(dp(1,1,1)+dp(1,2,1)+dp(1,3,1))%mod;
	printf("%lld",ans);
}
```

上面那个不返回值的dfs我也不知道怎么就挂了。。

---

