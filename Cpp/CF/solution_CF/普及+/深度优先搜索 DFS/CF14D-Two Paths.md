# Two Paths

## 题目描述

As you know, Bob's brother lives in Flatland. In Flatland there are $ n $ cities, connected by $ n-1 $ two-way roads. The cities are numbered from 1 to $ n $ . You can get from one city to another moving along the roads.

The «Two Paths» company, where Bob's brother works, has won a tender to repair two paths in Flatland. A path is a sequence of different cities, connected sequentially by roads. The company is allowed to choose by itself the paths to repair. The only condition they have to meet is that the two paths shouldn't cross (i.e. shouldn't have common cities).

It is known that the profit, the «Two Paths» company will get, equals the product of the lengths of the two paths. Let's consider the length of each road equals 1, and the length of a path equals the amount of roads in it. Find the maximum possible profit for the company.

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
1 2
1 3
1 4
1 5
1 6
1 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
1 2
2 3
2 4
5 4
6 4
```

### 输出

```
4
```

# 题解

## 作者：lottle1212 (赞：14)

# [原题传送门](https://www.luogu.com.cn/problem/CF14D)
## Part0：
首先解读一下题目。

- 给出一棵 $n$（$2 \leq n \leq 200$）个节点的树。

- 求出没有公共点的**两条路径长度乘积**的最大值。

输入：

```
6
1 2
2 3
2 4
5 4
6 4
```
输出：

```
4
```
如图：

![](https://stream.lexar.com/downloadService/download/graph2.png?dKey=b53172129051ac02b1b637ab033dfca9&type=2)

两条路径分别为 `1 2 3` 和 `5 4 6` ，答案为 **两条路径长度的乘积** $= 2 \times 2 = 4$。
## Part1：
此题其实是**树的直径**的升级版。

树的直径就是树上的最长路径，如上图，其直径为 $3$，直径路径为 `1 2 4 5` 或 `1 2 4 6`。

但此题要求我们求**两条路径长度乘积**的最大值，且两条路径不能有公共点，即两条路径不相关联，在两个不同的区块内。

因此，看到数据只有 $2 \leq n \leq 200$，就很容易想到 $O(n^2)$ 算法，即枚举每一条边，将边的左右看作两个部分，对两个部分分别求直径，将乘积求最大。

**AC Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mxn = 200;
const ll N = mxn + 10;
ll n, u[N], v[N], head[N], dp[N], cnt, ans, sum, s;
struct Edge { ll nxt, to; } e[N * 2];//邻接表
void add(ll u, ll v) { e[++ cnt] = {head[u], v}, head[u] = cnt; }//邻接表建边
void dfs(ll u, ll pre) {
	dp[u] = 0;
	for(ll i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		if(v == pre) continue;
		dfs(v, u);
		sum = max(sum, dp[u] + dp[v] + 1);
		dp[u] = max(dp[u], dp[v] + 1);
	}
	return ;
}//搜索，求树的直径
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for(ll i = 1; i < n; ++ i) cin >> u[i] >> v[i], add(u[i], v[i]), add(v[i], u[i]);
	for(ll i = 1; i < n; ++ i) {
		s = 1;
		dfs(u[i], v[i]);//对第一个区块进行搜索
		s *= sum, sum = 0;
		dfs(v[i], u[i]);//对第二个区块进行搜索
		s *= sum, sum = 0;
		ans = max(ans, s);//求最大
	}
	cout << ans;
	return 0;
}
```


---

## 作者：lenlen (赞：12)

### Problem

题目大意：给定一棵树，求两条不相交的链长度之积的最大值。

数据范围： $n \leq 200$。

### Solution

树的直径水题。

因为两条链不相交，也就意味着这两条链没有公共点，那么我们就可以保证，一定有一条链（长度不一定为 $1$，但一定 $\geq 1$）连接着这两条链。那么我们就可以考虑这一条连着要求的两条链的链（有点绕）。所以我们如果把这条链断了，那么原树就会被分成两棵树，而我们要求两条链长度之积的最大值，肯定是求分成的两棵树的直径。

所以做法也就很显然了，因为 $n \leq 200$，所以我们可以枚举断开的边 $i$，然后求分成两个树的直径之积，然后求最大值就可以了。

时间复杂度 $O(n^2)$。

至于求树的直径的解析，我放代码里了。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int h[732],cnt=1,dp[732],sum;
struct len{
    int u,v;
}t[732];
struct hl{
    int v,nxt;
}e[1732];
void add(int u,int v)
{
    e[++cnt].v=v,e[cnt].nxt=h[u],h[u]=cnt;
}
int mx(int x,int y){return x>y?x:y;}
void dpp(int x,int fx)//dp求数的直径，还有一种方法是dfs求树的直径
{
    /*
    以i为根的树的直径只可能存在于两种情况之下：
    1.经过i
    2.不经过i
    经过i的最长链显然就是两个离i最远的点之间的链
    不经过i那么肯定在以i的儿子节点为根的子树中，所以遍历子树就可以了
    */
    int mxx=0;dp[x]=0;
    for(int i=h[x],v;i;i=e[i].nxt)
    {
        if((v=e[i].v)==fx) continue;
        dpp(v,x);
        sum=mx(sum,dp[x]+dp[v]+1);//经过x的最长链
        dp[x]=mx(dp[x],dp[v]+1);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;++i) 
    {
        scanf("%d%d",&t[i].u,&t[i].v);
        add(t[i].u,t[i].v),add(t[i].v,t[i].u);
    }
    for(int i=1;i<n;++i)
    {
        int num=0;
        memset(dp,0,sizeof(dp));//记得清0
        dpp(t[i].u,t[i].v);//细节：不用做什么标记，我们把u的父亲设为v，那么u这棵子树就不会遍历到v去了
        num=sum;sum=0;
        dpp(t[i].v,t[i].u);//同上
        ans=mx(ans,num*sum);
        sum=0;
    }
    printf("%d\n",ans);
}
```


---

## 作者：Mistybranch (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF14D)

题目大概意思是：给你一棵有 $n$ 个结点的树，选择两条没有重叠部分的路径，使得长度的乘积最大。

由于这道题数据范围是比较小的（$n \leq 200$），我们考虑枚举，具体解法如下：

- 首先我们要明白，**两条没有重叠部分的路径一定存在于两棵没有重复节点的子树**，进一步转换一下，必定存在第三条路径连接两条路径，**去掉第三条路径上的某条边就可以将原来的树分成两个子树**，两条路径分别为这两个子树的**直径**。

上面这段话有点绕，用一组样例解释一下。

```
6
1 2
2 3
2 4
5 4
6 4
```
这个数据给出的树如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5sh3gugu.png)

在这一组数据下的最优解的两条路径为：$1 - 2 - 3$ 与 $4 - 5 - 6$，去掉的边为：$2 - 4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/1zziu9za.png)

- 根据上面的思考，我们就知道只需要枚举删去的边就可以了。

```
for (int i = 1; i <= n; i++) {
	for (int j = 0; j < g[i].size(); j++) {
		//...
	}
}
```

- 这样我们就找到了两棵子树，在这两棵子树中找到直径，然后相乘求最大值即可。

```cpp
int Search (int u, int fa) {
	int v, l1 = 0, l2 = 0, answ = 0;
	
	for (int i = 0; i < g[u].size(); i++) {
		v = g[u][i];
		
		if (v == fa) {
			continue;
		}
		
		answ = max(answ, Search(v, u));
		
		if (maxL > l1) {
			l2 = l1;
			l1 = maxL;
		} 
		
		else {
			l2 = max(l2, maxL);
		}
	}
	
	answ = max(answ, l1 + l2);
	maxL = l1 + 1;
	
	return answ;
}

d1 = Search(g[i][j], i);
d2 = Search(i, g[i][j]);
ans = max(ans, d1 * d2);
```

完整代码：

```cpp


#include <bits/stdc++.h>

using namespace std;

int n, maxL, ans;
vector<int> g[409];

int Search (int u, int fa) {
	int v, l1 = 0, l2 = 0, answ = 0;
	
	for (int i = 0; i < g[u].size(); i++) {
		v = g[u][i];
		
		if (v == fa) {
			continue;
		}
		
		answ = max(answ, Search(v, u));
		
		if (maxL > l1) {
			l2 = l1;
			l1 = maxL;
		} 
		
		else {
			l2 = max(l2, maxL);
		}
	}
	
	answ = max(answ, l1 + l2);
	maxL = l1 + 1;
	
	return answ;
}

int main () {
	int u, v, d1, d2;
	
	scanf("%d", &n);
	
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < g[i].size(); j++) {
			d1 = Search(g[i][j], i);
			d2 = Search(i, g[i][j]);
			ans = max(ans, d1 * d2);
		}
	}
	
	printf("%d\n", ans);
	
	return 0;
}
```


---

## 作者：Kendrick_Z (赞：4)

这题其实看上非常像一个树形DP？？

确实非常像但是仔细探究下数据范围只有2000

考虑贪心？暴力？

然后我一开始想了个假的贪心算法 就是跑一个树的直径然后把直径上的点标记下不走

再跑个次长

非常假的算法很容易发现是错的

我们考虑下数据范围 发现如果两个链没有交集

那么一定是在两颗独立的子树上

所以我们只要通过枚举每一条边然后删除成两个子树

分别跑一个直径就可以AC了

由于n是2000

所以平方级算法是无压力过的

还有注意一点每次求直径要清空！！！！所有数据！！！

我就这样调了半天qwq

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3000;
struct edge{
    int next,to,w,from;
}e[N<<1];
int head[N],cnt,maxx=0,st,ans1,ans2,ans;
inline int read(){
    int x=0,f=1;
    char ch=getchar(); 
    while(ch>'9'||ch<'0'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void add(int x,int y){
    e[++cnt].next=head[x];
    e[cnt].to=y;
    e[cnt].from=x;
    e[cnt].w=1;
    head[x]=cnt;
} 
bool vis[N];
int dis[N],n;
inline void bfs(int x){
    queue<int >q;
    maxx=0;
    st=x;
    memset(dis,0,sizeof(dis));
    memset(vis,0,sizeof(vis));
    q.push(x);
    vis[x]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].to;
            if(!vis[v]&&e[i].w!=0){
                dis[v]=dis[u]+e[i].w;
                vis[v]=1;
                q.push(v);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(dis[i]>maxx){
            maxx=dis[i];
            st=i;
//			cout<<maxx<<endl;
        }
//		cout<<dis[i]<<" ";
    }
//	cout<<endl;
//	cout<<maxx<<endl;
}
int main(){
//	n=read();
    scanf("%d",&n); 
    for(int i=1;i<n;i++){
        int u,v;
        u=read();
        v=read();
        add(u,v);
        add(v,u);
    } 
    for(int i=1;i<cnt;i+=2){
        e[i].w=0;
//		cout<<i<<" ";
        e[++i].w=0;
//		cout<<i<<" "<<(i)<<endl;
//		cout<<i<<endl;
        i--;
        maxx=0;
        bfs(e[i].from);
//		cout<<endl;
        bfs(st); 
//		cout<<endl;
//		cout<<e[i].from<<" "<<e[i].to<<" "<<e[i].w<<endl;
        ans1=maxx;
//		cout<<ans1<<endl;
//		cout<<endl;
        bfs(e[i].to);
//		cout<<endl;
        bfs(st);
//		cout<<endl;
        ans2=maxx;
//		cout<<ans2<<endl;
        ans=max(ans,ans1*ans2);
        e[i].w=1;
//		cout<<i<<" ";
        e[++i].w=1;
//		cout<<i<<endl;
        i--;
    }
    printf("%d",ans); 
    return 0;
} 
```


看我的多么长的输出调试就可以看出来...


然后吐槽一下点：

网上的题解为什么出奇相似都是vector存图？？？？？



---

## 作者：king_xbz (赞：3)

隔壁[SP6717](https://www.luogu.com.cn/problem/SP6717)的弱化版.

# 题意分析
给定一棵树，求该树上两条不相交链的最大乘积。

**数据范围**：$n≤200$
# 大致思路
由于数据范围很小，所以我们可以~~乱搞~~。因为我们要求的链是没有相交点的，所以，直接求树的最大直径和次大直径是不可行的。那么该怎么办呢？

我们可以直接将一棵树删去一条边，这样的话这棵树就化为两棵子树，在这两棵树上分别求直径，更新乘积最大值即可。

# 具体实现
枚举每条边，打上标记表示删除，然后分别从两条边处用DFS跑树的直径。中途记得把中间变量清零！

代码：
```cpp
int main()
{
	int n;
	cin>>n;
	int x,y;
	for(fint i=1;i<n;i++)
	cin>>x>>y,adds(x,y),adds(y,x);
	int ans=0,ansa=0,ansb=0;
	for(fint i=1;i<=cnt;i+=2)
	{
		int u=e[i].from,v=e[i].to;
		del[u][v]=1,del[v][u]=1;
		maxxs=0,fars=u;
		dfs(u,0,0);
		maxxs=0;
		dfs(fars,0,0);
		ansa=maxxs;
		maxxs=0,fars=v;
		dfs(v,0,0);
		maxxs=0;
		dfs(fars,0,0);
		ansb=maxxs;
		ans=max(ans,ansa*ansb);
		del[u][v]=0,del[v][u]=0;
	}
	cout<<ans;
	return 0;
}

inline void adds(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].from=u;
	e[cnt].nxt=head[u];
	head[u]=cnt;
	return ;
}

inline void dfs(int x,int fa,int tot)
{
	if(tot>maxxs)
	maxxs=tot,fars=x;
	for(fint i=head[x];i;i=e[i].nxt)
	if(e[i].to!=fa&&!del[e[i].from][e[i].to])
	dfs(e[i].to,x,tot+1);
	return ;
}
```
这样就可以AC了，有兴趣的可以体验一下SPOJ上的加强版哦！

祝大家AC愉快！！！

---

## 作者：syzxzqy (赞：2)

## [原题传送门](https://www.luogu.com.cn/problem/CF14D)  
#### 题目大意：
在一棵树中找出两条没有相同点的路径，求出他们最大的长度乘积。  
#### 题目分析：  
要先编出两条路径之积，就得先编出一条最长路径的方法，很显然是树的直径。  
这时候我们就要想了，如果是两棵树，我们就可求出结果。  
对了，我们可以暴力每一条边，在建树时删去这条边，从而建成两棵树。  
建出两棵树后，我们就可以做两次树的直径，求出两条路径之长，从而算出结果。  
#### 上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000001,M=1001;
int n,i,j,t,cnt,ans,ans2,ma,x[N],y[N],head[N],dp[N];
struct no{int zd,pre;}wz[N];
void add(int u,int v){
	wz[++t]=(no){v,head[u]};head[u]=t;//邻接表建边 
}
void dfs(int x,int fa){//树的直径模板 
    int i,z,tmp,ma1=0,ma2=0;
    for(i=head[x];i;i=wz[i].pre){
        z=wz[i].zd;
        if(z==fa) continue;
        dfs(z,x);
        tmp=dp[z]+1;
        if(tmp>dp[x]) dp[x]=tmp;
        if(tmp>ma1) ma2=ma1,ma1=tmp;
        else if(tmp>ma2) ma2=tmp;//求最大和第二大，合起来就是最长路径 
    }
	if(t==0) ans=max(ans,ma1+ma2);//第一条路径 
	else ans2=max(ans2,ma1+ma2);//第二条路径 
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<n;i++) cin>>x[i]>>y[i];
	for(i=1;i<n;i++){//枚举删除的边 
		t=ans=ans2=0;
		for(j=1;j<=n;j++) head[j]=dp[j]=0;//清零 
		for(j=1;j<n;j++)
			if(i!=j) add(x[j],y[j]),add(y[j],x[j]);
		t=0;dfs(x[i],-1);//第一棵树
		t=1;dfs(y[i],-1);//第二棵树
		ma=max(ma,ans*ans2); 
	}
	cout<<ma;
}
```


---

## 作者：da32s1da (赞：1)

枚举删哪条边，然后对删完边的两部分分别求树的直径，然后相乘取最大值即可。

```
#include<cstdio>
inline int max(int u,int v){return u>v?u:v;}
const int N=205;
int to[N<<1],las[N<<1],fir[N],cnt;
inline void add_edge(int u,int v){
	to[++cnt]=v;las[cnt]=fir[u];fir[u]=cnt;
	to[++cnt]=u;las[cnt]=fir[v];fir[v]=cnt;
}
int dep[N],mxdep,mxi,n,x,y;
void dfs(int u,int v,int a){
	dep[u]=dep[v]+1;
	if(dep[u]>mxdep)mxdep=dep[u],mxi=u;
	for(int i=fir[u];i;i=las[i])
	if(to[i]!=v&&to[i]!=a)dfs(to[i],u,a);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);
	}
	y=0;
	for(int i=1;i<cnt;i+=2){
		mxi=mxdep=dep[to[i]]=0;
		dfs(to[i],to[i],to[i+1]);
		dep[mxi]=0;
		dfs(mxi,mxi,to[i+1]);
		x=mxdep-1;
		mxi=mxdep=dep[to[i+1]]=0;
		dfs(to[i+1],to[i+1],to[i]);
		dep[mxi]=0;
		dfs(mxi,mxi,to[i]);
		y=max(y,x*mxdep-x);
	}
	printf("%d\n",y);
}
```

---

## 作者：xieyikai2333 (赞：1)

# 树的直径~~水~~题

- [题目传送门](https://www.luogu.com.cn/problem/CF14D)

## 关于树的直径

### 什么是树的直径？

- 树的直径，即树上最远两点（可以证明，一定是叶子结点）之间的距离。

### 如何求树的直径？

- 首先，从**任意点**出发，用深搜求出距离该点最远的点，记为点 $x$；

- 接下来，再从**新的点**出发，用深搜求出距离该点最远的点，记为点 $y$；

- 点 $x$ 到点 $y$ 的距离即为树的直径。


## 解题思路

注意：因为题目给出的是一个有 $n$ 个结点，$n-1$ 条边的图，所以当你**去掉其中一条边**时，它会变成两棵无根树。

做法：

1. 枚举每一条边并将其删去；

2. 分别求出删去一条边后两颗树的直径；

3. 将两棵树的直径相乘，并对 $ans$ 取最大值。


---

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> nodes[100005];
int ans,sum,a,b,y,s1[100005],s2[100005];
void dfs(int u,int from,int len)
{
	if(len>=sum)sum=len,y=u;
	int i,v,w,l=nodes[u].size();
	for(i=0;i<l;i++)
	{
		v=nodes[u][i];
		if((u==a&&v==b)||(u==b&&v==a)||v==from)continue;
		dfs(v,u,len+1);
	}
	return;
}
int main()
{
	int n,u,v,i,tmp;
	cin>>n;
	for(i=1;i<n;i++)
	{
		cin>>u>>v;
		nodes[u].push_back(v);
		nodes[v].push_back(u);
		s1[i]=u;
		s2[i]=v;
	}
	for(i=1;i<n;i++)
	{
		a=s1[i],b=s2[i],sum=0;
		dfs(a,0,0);
		sum=0;
		dfs(y,0,0);
		tmp=sum,sum=0;
		dfs(b,0,0);
		sum=0;
		dfs(y,0,0);
		ans=max(ans,tmp*sum);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

为什么 $n\leq 200$ 时限 $2s$ 会想到 $O(n^2)$ 的算法？为什么不是 $O(n^4)$？

从 [P3398 仓鼠找 sugar](https://www.luogu.com.cn/problem/P3398) 来的，发现这题和那题很像，就想着能不能也用那题的结论做一下。

显然对于两条路径 $(a,b),(c,d)$，若两条路径相交，则一定有一条路径的 LCA 在另一条路径上，则有：

1. $dep_{lca_{a,b}}\geq dep_{lca_{c,d}}$ 且满足：$lca_{a,b}=lca_{c,lca_{a,b}}$ 或 $lca_{a,b}=lca_{d,lca_{a,b}}$。
2. $dep_{lca_{c,d}}\geq dep_{lca_{a,b}}$ 且满足：$lca_{c,d}=lca_{a,lca_{c,d}}$ 或 $lca_{c,d}=lca_{b,lca_{c,d}}$。

根据这个结论，我们暴力枚举两条路径，然后就用 $O(n^4)$ 的时间复杂度 AC 了这道题。

有点卡常，开个火车头就过了。

https://codeforces.com/contest/14/submission/287850002

代码：

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
using namespace std;
const int N=201;
int n,u,v,f[N][21],d[N]={0,1},lca[N][N],dis[N][N],ans;
vector<int>G[N];
void dfs(int u){
    for(int i=1;i<=20;i++) f[u][i]=f[f[u][i-1]][i-1];
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==f[u][0]) continue;
        f[v][0]=u;
        d[v]=d[u]+1;
        dfs(v);
    }
}
int getlca(int x,int y){
    if(d[x]<d[y]) swap(x,y);
    for(int i=20;i>=0;i--) if(d[f[x][i]]>=d[y]) x=f[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        lca[i][i]=i;
        for(int j=i+1;j<=n;j++){
            lca[i][j]=lca[j][i]=getlca(i,j);
            dis[i][j]=dis[j][i]=d[i]+d[j]-2*d[lca[i][j]];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=1;k<=n;k++){
                for(int l=k+1;l<=n;l++){
                    int lc=lca[i][j];
                    if(d[lc]>=d[lca[k][l]]&&(lca[k][lc]==lc||lca[l][lc]==lc)) continue;
                    lc=lca[k][l];
                    if(d[lc]>=d[lca[i][j]]&&(lca[i][lc]==lc||lca[j][lc]==lc)) continue;
                    ans=max(ans,dis[i][j]*dis[k][l]);
                }
            }
        }
    }
    cout<<ans;
}
```

---

## 作者：出言不逊王子 (赞：0)

观察到我们需要两条不相交的路径，考虑什么情况下路径会重合。

很显然只有路径有公共边时路径才会重合。

考虑什么情况下路径没有公共边。

于是我们想到我们要用一种方式删掉路径的公共边。

我们想到把树分成两个部分，这两个部分没法联通。

在这两个部分里面找到一条路径，使得这个路径最长。

也就是说，这个路径是树的直径。

然后我们想到怎么把树分成不连通的两部分。

我们发现符合这个条件的边就是割边。

我们思考怎么找出割边。

我们发现因为树没有环，所以树上的每一条边都是割边。

我们考虑枚举树上的每一条边，把它删掉，再用两次 DFS 求出两棵子树的直径，最后更新答案即可。

以上是我做这题的心路历程，下面是代码。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
struct edge{
	int v,nx,able,u;
	edge(){able=0;}//0能1不能 
}e[N<<1];
int ans[2],hd[N],totm,res,farest,zhijin,n;
void dfs(int u,int fa,int len){
	if(len>farest) farest=len,zhijin=u;
	for(int i=hd[u];i;i=e[i].nx){
		int v=e[i].v;
		if(v==fa) continue;
		if(e[i].able) continue;
		dfs(v,u,len+1);
	}
}
void add(int u,int v){e[++totm].v=v;e[totm].nx=hd[u];hd[u]=totm;e[totm].u=u;}
int main(){
	n=read();
	fs(i,1,n-1,1){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	fs(i,1,n*2-3,2){
		e[i].able=e[i+1].able=1;
		int u=e[i].u;zhijin=0;farest=0;int res1,res2;
		dfs(u,0,0);farest=0;dfs(zhijin,0,0);
		res1=farest;//1号的直径
		u=e[i].v,zhijin=0;farest=0;
		dfs(u,0,0);farest=0;dfs(zhijin,0,0);
		res2=farest;//2号的直径
		res=max(res,res1*res2); 
		e[i].able=e[i+1].able=0;
	}
	printf("%d",res);
	return 0;
}
//题目要2路径，不重复并且乘积最大
//反正在哪都是割点
```

---

