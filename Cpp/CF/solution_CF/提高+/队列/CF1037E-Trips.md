# Trips

## 题目描述

**题目大意：**

一共有$n$个人，他们开始互不认识，而每天早上不认识的两个人会变成朋友。一共有$m$天，每天晚上有的人要去旅行，去旅行的人必须满足ta有至少$k$个朋友也去旅行

求每天去旅行的最大人数

## 样例 #1

### 输入

```
4 4 2
2 3
1 2
1 3
1 4
```

### 输出

```
0
0
3
3
```

## 样例 #2

### 输入

```
5 8 2
2 1
4 2
5 4
5 2
4 3
5 1
4 1
3 2
```

### 输出

```
0
0
0
3
3
4
4
5
```

## 样例 #3

### 输入

```
5 7 2
1 5
3 2
2 5
3 4
1 2
5 3
1 3
```

### 输出

```
0
0
0
0
3
4
4
```

# 题解

## 作者：jdsb (赞：14)

## 题意
- 给出 $n$ 个点，总共有 $m$ 个时刻，每个时刻都会新加入一条边 $(x,y)$，对于每个时刻，求此时的最大点集大小，满足点集的点构成的子图中的点的度数都不小于给定的常数 $k$。
- $2\le n \le 2\times10^5,2\le m \le 1\times10^5,1\le k  \le n$

## 分析
- 首先考虑如果已经给定了一张图该如何求出满足的最大点集大小，可以用类似拓扑的思想，将此时图中度数小于 $k$ 的点的加入队列，每次将队头的点删除，并把相连的点的度数减一，如果相连的点度数减完之后恰好为 $k-1$，则可以将这个点也加入队列中，重复上述操作，直到队列为空，则没加入到队列的点的数量即为答案。

- 上面做法的时间复杂度为 $O(nm)$，即每次加边都要重复一次操作，因为加边的话可能会让出队的点重复进队，所以比较难维护。

- 正难则反，既然正着加边想不通，且不强制在线，那就反着来做，每次将边删除，这样的话每次删边操作，只会让边的度数减少，所以原来不是答案的点就不会加入答案中去，正着处理的麻烦就可以解决，因为每个点最多只会进队一次，所以总的时间复杂度为 $O(n+m)$，可以通过此题。

- 一些细节，删边是要注意不能重复删边，如果一条边相连的点已经被删除过，即这条边已经被删，那就直接继承上一次的答案，详细实现见代码。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') { if(c=='-') f=-1;c=getchar(); }
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return x*f;
}
inline void write(int x){
	if(!x) return puts("0"),void();
	int q[105],t=0;
	while(x) q[++t]=x%10,x/=10;
	while(t) putchar(q[t--]^'0');
	puts("");
}
const int N=2e5+5;
struct edge{
	int y,next;
}e[N<<1];
int cnt=1,first[N];
inline void add(int x,int y) { e[++cnt]={y,first[x]};first[x]=cnt; }
int n,m,k,du[N],g[N],ans,vis[N<<1];
queue<int>q;
inline void solve(){
	while(!q.empty()){
		int x=q.front();q.pop();
		du[x]=0;
		for(int i=first[x];i;i=e[i].next){
			int y=e[i].y;
			if(vis[i]) continue;
			vis[i]=vis[i^1]=1;
			du[y]--;
			if(du[y]==k-1) ans--,q.push(y);
		}
	}
}
struct Edge{
	int x,y;
}E[N];
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		E[i]={x,y};
		add(x,y);
		add(y,x);
		du[x]++,du[y]++;
	}
	ans=n;
	for(int i=1;i<=n;i++) if(du[i]<k) ans--,q.push(i);
	solve();
	g[m]=ans;
	for(int i=m;i>=2;i--){
		if(vis[i<<1]){
			g[i-1]=g[i];
			continue;
		}
		vis[i<<1]=vis[i<<1|1]=1;
		int x=E[i].x,y=E[i].y;
		du[x]--,du[y]--;
		if(du[x]==k-1) ans--,q.push(x);
		if(du[y]==k-1) ans--,q.push(y);
		solve();
		g[i-1]=ans;
	}
	for(int i=1;i<=m;i++) write(g[i]);
	return 0;
}
```


---

## 作者：MinimumSpanningTree (赞：10)

[原题链接](https://www.luogu.com.cn/problem/CF1037E)

图论好题。采用正难则反的思想，先将所有边连接起来。如果连接后存在某些点的度数不足 $k$，则不可能对答案有贡献，删除。删除后剩下的点就是最后一晚的人数。接下来从第 $n-1$ 晚开始往前遍历，每次删除一条边，即可得到每晚的人数，最后倒序输出。

如果像上面那样操作，删除指定点或边后，如何保证剩下的点度数一定不小于 $k$？

很简单。关于删除点，可以将点放入队列中，最后遍历队列，将与遍历到的点直接相连的点度数 $-1$，如果减了之后不足 $k$，则该点需要删除，放入队列中。

关于删除边，将边的两端点度数分别 $-1$，如果度数 $<k$，将点入队，如删除点操作即可。

有一个需要注意的点是可能存在因遍历队列而导致的一条边被减多次，这里的解决方式是使用 $\text{map}$ 来标记每条边是否已经拆散。

```cpp
#include<iostream>
#include<cstdio>
#include<unordered_map>
using namespace std;
const int N=2e5+100;
typedef long long ll;
int n,m,c,k,t[N],ans[N],d[N],cnt,l=1,r;
ll u[N],v[N],q[N];
unordered_map<ll,bool> um;
struct node
{
	int last,id;
}a[N*2];
void add(int a1,int a2)
{
	a[++k].id=a2;
	a[k].last=t[a1];
	t[a1]=k;
}
void del()//删除队列中的点
{
	while(l<=r)
	{
		d[q[l]]=0;
		for(int i=t[q[l]];i;i=a[i].last)//遍历与当前点直接相连的点
		{
			if(um[q[l]*100000+a[i].id]) continue;
			d[a[i].id]--;
			if(d[a[i].id]==c-1) q[++r]=a[i].id,cnt--;//度数<k，需要删除，入队
		}
		l++;
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&c);
	cnt=n;
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&v[i],&u[i]);
		add(u[i],v[i]);
		add(v[i],u[i]);
		d[v[i]]++,d[u[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(d[i]<c)
		{
			cnt--;
			q[++r]=i;
		} 
	}
	del();//删除度数不足k的点
	ans[m]=cnt;
	for(int i=m;i>=2;i--)
	{
		um[u[i]*100000+v[i]]=true;
		um[v[i]*100000+u[i]]=true;
		if(d[u[i]]<=0||d[v[i]]<=0) 
		{
			ans[i-1]=cnt;
			continue;
		}
		//删边
		d[v[i]]--,d[u[i]]--;
		if(d[u[i]]==c-1) q[++r]=u[i],cnt--;
		if(d[v[i]]==c-1) q[++r]=v[i],cnt--;
		del();
		ans[i-1]=cnt;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：风浔凌 (赞：7)

写这篇题解的时候蒟蒻我是ssfd的。。。。。  

比赛的时候根本就没有做到这个题（~~我是真的蒻~~），赛后想了想，以为是求最大环。。。但是这个思路是不是有锅啊，一直WA。。。。。然后然后蒟蒻我走投无路，只好参考了CF上dalao的代码和思路qwq

（~~吐槽一下，CF官方题解太长了啦~~）

做这个题貌似正着做每次都要搜索一遍，时间复杂度不太对，所以。。。。我们要倒着做。。。。

下面是代码和详细注释：

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#include<queue>
using namespace std;
const int N = 200010;
int n,m,k,cnt;
int x[N],y[N],ans[N],size[N],del[N],q[N];
set<int> e[N];
void shanchu(int root) {
	if (size[root] >= k || del[root]) return;
    //如果长度符合，自然是要return掉
	queue<int> q;
	q.push(root);
	del[root] = 1;
    //要删除该节点
	cnt--;
    //因为删除了该节点，所以答案--
	while (!q.empty()) {
    //队列优化
		int u = q.front();
		q.pop();
		for(set<int>::iterator it=e[u].begin();it!=e[u].end();it++)
		{
            int v=*it;
            //遍历集合中的每一个元素
			--size[v];
            //因为要删除他的朋友u，所以size--
			if (size[v] < k && !del[v]) {
            //如果size<k那么意味着有该节点参与的不会再存在去trip的情况，也就是该节点已经不符合要求了，需要删掉
            //判断del是为了防止重复计算
				q.push(v);
				del[v] = 1;
				cnt--;
                //放入队列，答案减一
			}
		}
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; i++) {
		scanf("%d%d",&x[i],&y[i]);
		size[x[i]]++;
		size[y[i]]++;
        //size数组里面记录的是每个节点他的朋友个数
		e[x[i]].insert(y[i]);
		e[y[i]].insert(x[i]);
        //将每个节点的朋友加进来
	}
	cnt=n;
    //最初的答案初始化肯定是n，因为最大也就是全部人都去trip
	for (int i=1;i<=n;i++) shanchu(i);
    //遍历搜索一遍，把不符合长度的都去掉（题目要求如果进行trip的话，至少要叫上k个朋友的）
	ans[m] = cnt;
	for (int i = m - 1; i >= 0; i--) {
		if (!del[y[i]])  --size[x[i]];
		if (!del[x[i]])  --size[y[i]];
		e[x[i]].erase(y[i]);
		e[y[i]].erase(x[i]);
        //set的erase操作，去掉该节点
		shanchu(x[i]);
		shanchu(y[i]);
        //因为去掉了节点，所以要更新合法边
		ans[i] = cnt;
        //更新完之后储存答案
	}
	for (int i = 1; i <= m; i++) 
		printf("%d\n", ans[i]);
}
```

---

## 作者：Dispwnl (赞：5)

正着建边好像不可做啊...换个思路？

可以开始先把所有的边建起来，然后依次拆边

这样如果一个点开始就不满足条件ta就永远不满足条件

如果一个点的度不小于$k$就先不管这个点

如果一个点的度小于$k$，说明这个点不满足条件，可以删掉ta，删掉ta的同时与ta相连的点度也要$-1$

这样可能出现连锁反应，用个队列记录一下，复杂度差不多$O(n+m)$

代码：
```
# include<iostream>
# include<cstring>
# include<cstdio>
# include<vector>
# include<queue> 
# include<algorithm>
using namespace std;
const int MAX=2e5+1;
int n,m,k,ans;
int du[MAX],X[MAX],Y[MAX],Ans[MAX];
vector<int> ve[MAX];
bool use[MAX];
void work(int x)
{
	queue<int> qu;
	qu.push(x),use[x]=1,--ans;
	while(!qu.empty())
	{
		int tt=qu.front();
		qu.pop();
		for(int i=0;i<ve[tt].size();++i)
		  {
		  	int y=ve[tt][i];
			if(use[y]) continue;
			--du[y];
			if(du[y]<k) --ans,use[y]=1,qu.push(y);
		  }
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	ans=n;
	for(int i=1;i<=m;++i)
	  {
	  	scanf("%d%d",&X[i],&Y[i]);
	  	++du[X[i]],++du[Y[i]],ve[X[i]].push_back(Y[i]),ve[Y[i]].push_back(X[i]);
	  }
	for(int i=1;i<=n;++i)
	  if(du[i]<k&&!use[i]) work(i);
	Ans[m]=ans;
	for(int i=m;i>=1;--i)
	  {
	  	if(!use[Y[i]]) --du[X[i]];
		if(!use[X[i]]) --du[Y[i]];
	  	ve[X[i]].pop_back(),ve[Y[i]].pop_back();
	  	if(du[X[i]]<k&&!use[X[i]]) work(X[i]);
	  	if(du[Y[i]]<k&&!use[Y[i]]) work(Y[i]);
	  	Ans[i-1]=ans;
	  }
	for(int i=1;i<=m;++i)
	  printf("%d\n",Ans[i]);
	return 0;
}
```
### [博客QAQ](https://a-failure.github.io/2018/09/04/CF1037-A~E%E9%A2%98%E8%A7%A3)

---

## 作者：jiazhichen844 (赞：1)

# 简要题意
有一个有 $n$ 个节点的无向图，初始没有变，有 $m$ 次加边操作，每次操作后询问使得每个点度数都大于等于 $k$ 的导出子图的最大点数。
# 思路
## step 1
先考虑一个图的情况，首先，可以发现度数小于 $k$ 的点**必须**不选，所以可以在原图中删除，这样，又有一些点的度数变小了，则现在度数小于 $k$ 的点也**必须**不选，也可以删除……，等没点可删时，剩下的图就是答案。

怎么证？

若答案小于正确答案，则还可以再加点，当加点时，又必须加上另一些原来删除的点，以此类推，一定会需要加原度数小于$k$的点，但度数小于 $k$ 的点是必须删的，所以答案一定大于等于正确答案。

若答案大于正确答案，则还**必须**删点，但是若有点度数小于 $k$，他一定会被删掉，所以，剩下的点度数都 $\ge k$，不用删，所以答案一定小于等于正确答案。

综上，答案一定正确。
## step 2
考虑如何实现：

我们可以把要删的点放进一个队列，每次删一个，删除后去更新他周围点的度数，当他周围点度数 $< k$ 时，把那个点放进队列，可以画个图模拟一下，可以发现此过程类似于拓扑排序，只需修改进队条件即可。总复杂度 $O(m(n+m))$
## step 3
加边有可能会使某些被删的点又回来，时间复杂度不对，所以正难则反，考虑从最后的图删边。

在第 $m$ 步后的图中，我们可以求出必须删的点，而在删掉一条边后，边两边的点的度数将减少，于是我们可以重复以上步骤，当度数减少的点度数又小于 $k$ 时，进入队列，继续删点，求出新一轮答案……

图可以用 set 存储，在 $O(\log n)$ 的时间复杂度删除，因为操作相当于一遍拓扑排序，所以时间复杂度为 $O(n+m+m \log n)=O(m \log n)$。
# AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> e[300005];
struct edge
{
	int u,v,ans;
}a[300005];
int d[300005];
bool f[300005];
int main() 
{
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
	 	int u,v;
	 	cin>>u>>v;
		e[u].insert(v);
		e[v].insert(u); 
		a[i].u=u;
		a[i].v=v;
		d[u]++;
		d[v]++;
	}
	int c=n;
	queue<int> q;
	for(int i=1;i<=n;i++)
	{
		if(d[i]<k)
		{
			q.push(i);
			f[i]=1;
			c--;
		}
	}
	for(int i=m;i>=1;i--)
	{
		while(!q.empty())
		{
			for(auto x:e[q.front()])
			{
				d[x]--;
				if(d[x]==k-1)
				{
					q.push(x);
					f[x]=1;
					c--;
				}
			}
			q.pop();
		}
		a[i].ans=c;
		if(f[a[i].u]==0&&f[a[i].v]==0)
		{
			d[a[i].u]--;
			if(d[a[i].u]==k-1)
			{
				q.push(a[i].u);
				f[a[i].u]=1;
				c--;
			}
			d[a[i].v]--;
			if(d[a[i].v]==k-1)
			{
				q.push(a[i].v);
				f[a[i].v]=1;
				c--;
			}
		}
		e[a[i].u].erase(a[i].v);
		e[a[i].v].erase(a[i].u);
	}
	for(int i=1;i<=m;i++)
		cout<<a[i].ans<<endl;
}
```

---

## 作者：Crab_Dave (赞：1)

### 题意

一共有 $n$ 个人，他们开始互不认识，而每天早上不认识的两个人会变成朋友。一共有 $m$ 天，每天晚上有的人要去旅行，去旅行的人必须满足有至少 $k$ 个朋友也去旅行。求每天去旅行的最大人数

### 思路

首先逆时间操作，加边变删边

这样如果一个点不满足条件就永远不满足条件

如果一个点的度小于 $k$，即不满足条件，可以删去，删去之后可能会影响相邻节点所以需要bfs删去。

### 代码
```cpp
void bfs(int s){
	queue<int>q;q.push(s);
	vis[s]=1;num--;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].next){
			if(!e[i].fl)continue;
			int v=e[i].to;
			if(vis[v])continue;
			d[v]--;if(d[v]<k)vis[v]=1,num--,q.push(v);
		}
	}
}

int main(){
	num=n=read();m=read();k=read();
	rep(i,1,m){x[i]=read(),y[i]=read();adde(x[i],y[i]);adde(y[i],x[i]);}
	rep(i,1,n)if(!vis[i]&&d[i]<k)bfs(i);
	ans[m]=num;per(i,m,1){
		if(!vis[y[i]])d[x[i]]--;
		if(!vis[x[i]])d[y[i]]--;
		e[cnt--].fl=0;e[cnt--].fl=0;
		if(!vis[x[i]]&&d[x[i]]<k)bfs(x[i]);
		if(!vis[y[i]]&&d[y[i]]<k)bfs(y[i]);
		ans[i-1]=num;
	}
	rep(i,1,m)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：wyd_forever (赞：1)

## first  
  
题目大意：给一幅图,边从 0 开始每天多一条边,问每天增加边之后能够有多少人去旅游。能去旅游的定义是只有当联通的点的度数都大于等于 k 才能去旅游,否则都不能去旅游。询问每天最多能去旅游的点的数量

## second
很明显正向不太好做，于是离线建边的信息，考虑反向跑：每次都删去度小于$k$的点（对点标记），删去与其相连的边（同样对边进行标号标记即可），将与其相连的还未删去的点的度修改一下，反向统计答案即可。  

## third  
代码里有详注  
(这里使用小根配对堆维护度的取出)：  
```
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
#define in read()
#define fur(i,a,b) for(int i=a;i<=b;++i)
#define fdr(i,a,b) for(int i=a;i>=b;--i)
#define pa pair<int,int>
#define heep __gnu_pbds::priority_queue<pa,greater<pa> >
#define nm make_pair
inline int read()　　//读入优化
{
	int x=0,f=1;char ch=getchar();
	for(;!isalnum(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isalnum(ch);ch=getchar()) x=x*10+ch-'0';
	return x*f;
}
const int xx=2e5+10;
int du[xx],cnt;   //点的度与当前剩余的未被删的点的数量
vector<pa>e[xx];  //存储两个信息：连的点与边的编号
struct edge{int u,v,ans;bool use;}d[xx];  //存储边的两端，该时间的答案与该边是否被删
heep p;　//小根配对堆存度与点编号
heep::point_iterator id[xx];
bool cut[xx];  //点是否被删
int main()
{
	int n=in,m=in,k=in;
	fur(i,1,m)
	{
		int x=in,y=in;
		d[i].u=x,d[i].v=y;
		e[x].push_back(nm(y,i));
		e[y].push_back(nm(x,i));
		++du[x];++du[y];
	}
	fur(i,1,n) id[i]=p.push(nm(du[i],i));　//将度压入堆
	cnt=n;  //初始化为被删的点的数量
	fdr(i,m,1)
	{
		while(!p.empty()&&p.top().first<k)
		{
			int u=p.top().second;p.pop();
			cut[u]=true;du[u]=0;  //删
			--cnt;                           //点
			fur(j,0,(int)e[u].size()-1)
			{
				if(cut[e[u][j].first]) continue;  //连点已被删，跳过
				if(d[e[u][j].second].use) continue;　//连边已被删，跳过
				d[e[u][j].second].use=true; //否则删边
				--du[e[u][j].first];  //修改连点的度
				p.modify(id[e[u][j].first],nm(du[e[u][j].first],e[u][j].first)); //修改ing
			}
		}
		d[i].ans=cnt;　//存储答案
		if(!d[i].use)  //若该边没被删
		{
			if(cut[d[i].u]||cut[d[i].v]) continue;　//若边的两端任何一点被删，跳过
			--du[d[i].u];                     //否则修改点的度
			--du[d[i].v];
			p.modify(id[d[i].u],nm(du[d[i].u],d[i].u));
			p.modify(id[d[i].v],nm(du[d[i].v],d[i].v));
			d[i].use=true;   //且删边
		}
	}
	fur(i,1,m) printf("%d\n",d[i].ans);  //正向输出答案
	return 0;
}
```

---

## 作者：太阳骑士 (赞：1)

考虑对朋友之间建边，这样便将问题转化为动态加边了。然后每天选出一些点，使这些点与其他被选的点有至少$k$条连边。但正着做不好做，于是考虑反着做。

我们先将所有的边都连上，如果这时点的度数小于$k$，那么这个点无论如何也不可能被选，所以我们直接将其删除，同时更新与其相邻的点。此时剩余的点即第$m$天的答案。

最后，倒着删边，统计答案即可。

```cpp
#include<set>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define il inline
#define re register
#define maxn 200005
#define tie0 cin.tie(0),cout.tie(0)
#define fastio ios::sync_with_stdio(false)
using namespace std;
typedef long long ll;

template<typename T>inline void read(T &x){
	T f=1;x=0;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+(c^48);
    x*=f;
}

struct edge{
	int u,v;
}e[maxn];

set<int>st[maxn];

int n,m,k,cnt;
int ans[maxn],du[maxn];
bool del[maxn];

void Delete(int x){
	if(du[x]>=k||del[x]) return;
	del[x]=1;cnt--;
	queue<int>q;
	q.push(x);
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(auto y : st[now]){
			du[y]--;
			if(du[y]<k&&!del[y]){
				q.push(y);
				del[y]=1;cnt--;
			}
		}
	}
}

int main(){
	int x,y;
	read(n),read(m),read(k);
	cnt=n;
	for(int i=1;i<=m;++i){
		read(x),read(y);
		e[i].u=x,e[i].v=y;
		du[x]++,du[y]++;
		st[x].insert(y),st[y].insert(x);
	}
	for(int i=1;i<=n;++i)
		Delete(i);
	ans[m]=cnt;
	for(int i=m;i;--i){
		x=e[i].u,y=e[i].v;
		if(!del[x]) du[y]--;
		if(!del[y]) du[x]--;
		st[x].erase(y),st[y].erase(x);
		Delete(x),Delete(y);
		ans[i-1]=cnt;
	}
	for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：CharlieCai (赞：0)

## 题意

一共有 $n$ 个人，他们开始互不认识，而每天早上不认识的两个人会变成朋友。一共有 $m$ 天，每天晚上有的人要去旅行，去旅行的人必须满足有至少 $k$ 个朋友也去旅行。求每天去旅行的最大人数。

## 思路

- 读题后发现，想要判断一个人能否去旅行，就要知道他的朋友能否旅行。这是一个“套娃”的判断，如果直接考虑有多少人能去旅行较为困难。

- 因此，我们可以考虑有多少人不能去旅行。首先，那些朋友数量不足 $k$ 个的肯定不行，将他删去。删去后我们发现，他的一些朋友此时朋友数量变小后不足 $k$ 个，则将他们也删去，以此类推，就可以统计出一个固定的图中有多少人不能旅行，单次统计时间复杂度 $O(n)$。

- 接下来考虑加边。如果在每个时刻都进行一次上述操作，则总体时间复杂度为 $O(nm)$，会超时。但正难则反，我们可以变加边为删边，从最后一个时刻向前计算，每次删除图中的一条边。删边后，有些人朋友数量小于 $k$，则将他们删去，再考虑他们的朋友，以此类推。总体时间复杂度 $O(n+m)$。

- 实现时有一些细节，如一条边删去后要标记两条边被删去（因为是无向图），防止重复删边。还有只有在某个点的度数减小后恰好等于 $k - 1$ 才能删去，防止重复删点。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 400005
using namespace std;
int n,m,k,ans[MAXN],eu[MAXN],ev[MAXN],d[MAXN],sum;
int cnt,head[MAXN];
queue<int>q;
struct Edge{
	int value,next,w;
}adj[MAXN];
void addedge(int u,int v){
	adj[++cnt].value=v;
	adj[cnt].next=head[u];
	adj[cnt].w=1;		//标记该边未被删除 
	head[u]=cnt;
}
void solve(){
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=adj[i].next){
			if(adj[i].w==1){
				int y=adj[i].value;
				d[y]--;
				if(d[y]==k-1){	//新出现的不符合要求的点入队 
					q.push(y);
					sum--;
				}
				adj[i].w=0;					
				adj[(i%2==0?i-1:i+1)].w=0;//标记该边已被删除 
			}
		}
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&eu[i],&ev[i]);
		addedge(eu[i],ev[i]);
		addedge(ev[i],eu[i]);
		d[eu[i]]++;
		d[ev[i]]++;
	}
	sum=n;
	for(int i=1;i<=n;i++){
		if(d[i]<k){		//本来度数不足k个的点入队 
			q.push(i);
			sum--;
		}
	}
	for(int i=m;i;i--){
		solve();
		ans[i]=sum;
		if(adj[i*2].w==1&&adj[i*2-1].w==1){//若该边还没有被删除 
			d[eu[i]]--;
			if(d[eu[i]]==k-1)q.push(eu[i]),sum--;//删边后若有点不符合要求则加入队列 
			d[ev[i]]--;
			if(d[ev[i]]==k-1)q.push(ev[i]),sum--;
			adj[i*2].w=0;
			adj[i*2-1].w=0;
		}
	}
	for(int i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}

```

---

## 作者：初雪_matt (赞：0)

由于 $a$ 与 $b$ 是朋友，且 $b$ 与 $c$ 是朋友时，$a$ 与 $c$ 并不是朋友，不具备传递性，则不考虑并查集。

考虑建图去维护，如果正向建图会导致图动态更新，新加的一组关系可能关联所有人，并不是很好维护。思考后可以发现，由于朋友组数一直在增加，所以可以去旅游的人数也一定不降，考虑倒着删边。

- 如果一个点的度是大于 $k$ 的，对答案没有影响。

- 如果一个点的度是等于 $k$ 的，对答案有影响。

同样的，如果小于 $k$ 就可以不用管了，因为是倒着去删边，则度数不可能增加。

考虑如何处理连锁反应，标记不用管的点后，dfs 这条边的左右两端看是否有影响即可。

如何删边？可以考虑用 set 建图，继则使用 ``erase`` 函数即可，复杂度严格 $O(\log n)$。dfs 时每个点至多访问一次，总复杂度 $O(n \log n)$。

---

