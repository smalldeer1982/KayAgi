# グラフ

## 题目描述

# 图
## 问题描述
有一个由 $ N $ 个结点组成的有向图。当 $ g_{i,j}\ =\ 1 $ 时，从结点 $ i $ 到结点 $ j $ 有一条有向边。最初，所有结点都涂成白色。 Sunuke 君可以执行两次以下操作。
选择一个结点并沿着该结点的有向边访问几个结点。同一个结点可以重复多次。
将所有多次通过的结点涂成黑色。
求出两次操作后，涂成黑色的顶点数的最大值。

# 题解

## 作者：jijidawang (赞：5)

啥，你先别流。

首先缩点变成 DAG 上问题。考虑加虚拟源汇点 $s,t$ 后变成找 $s$ 到 $t$ 的两条路径。

于是令 $dp_{u,v}$ 表示两条路径 $s-u,\,s-v$ 的最大覆盖总点数，枚举出边转移即可。

时间复杂度 $O(n^3)$，可以通过。

[Submission](https://atcoder.jp/contests/tdpc/submissions/41684720)。

---

## 作者：xtx1092515503 (赞：1)

说一种~~虽然不是正解但确实是对的~~的方法吧。

方法来自于[ET2006](https://www.luogu.com.cn/user/115194#main)神仙跟我偶然扯到的神仙算法。

翻译：给定一张有向图，我们在图上找出两条路径$P_1=\{V_1,E_1\},P_2=\{V_2,E_2\}$，路径可以有重复的点或边。求$\max(|V_1\cup V_2|)$。

思路：

路径问题，首选SCC（强连通分量）缩点，因为同一块强连通分量里的所有点肯定是互相可达的。

缩完点后，我们得到一张DAG。

现在问题转换为：给你一张带权DAG，找出两条路径，使得它们并集的权值最大。

正解是DP（毕竟这是DP Contest嘛）

不过我们可以发现，这个模型有点像费用流！我们拆个点限制每个点的权值只会被计入一次，然后建立一个伪源点和伪汇点$s,t$限制流量最多只能为$2$。

具体的说，我们将每个点$x$拆成入点$x$和出点$x'$两个点。定义$(u,v,w,c)$表示一条从$u$到$v$，流量上限为$w$，费用为$c$的边。

对于缩点后的图上每一条边$(u,v)$，连边$(u',v,2,0)$；

对于缩点后的图上每个点$u$，连边$(s,u,2,0)$、$(u,u',1,val_u)$、$(u,u',1,0)$和$(u',t,2,0)$。注意到我们在$u$和$u'$间连了两条边，这样费用只会被计入一次。

最后，连边$(S,s,2,0)$和$(t,T,2,0)$，以限制流量。

答案即为最大费用最大流。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,col[310],c,sz[310],s,t;
namespace SCC{
	int tot,dfn[310],low[310],head[310],cnt;
	struct node{
		int to,next;
	}edge[200100];
	void ae(int u,int v){
	//	cout<<u<<" "<<v<<endl;
		edge[cnt].next=head[u],edge[cnt].to=v,head[u]=cnt++;
	}
	stack<int>stk;
	void Tarjan(int x){
		dfn[x]=low[x]=++tot,stk.push(x);
		for(int i=head[x];i!=-1;i=edge[i].next){
			if(!dfn[edge[i].to])Tarjan(edge[i].to),low[x]=min(low[x],low[edge[i].to]);
			if(!col[edge[i].to])low[x]=min(low[x],dfn[edge[i].to]);
		}
		if(low[x]<dfn[x])return;
		c++;
		while(stk.top()!=x)col[stk.top()]=c,stk.pop(),sz[c]++;
		col[stk.top()]=c,stk.pop(),sz[c]++;
	}
}
namespace MCMF{
	const int N=1000,M=200000;
	int head[N],cnt,dis[N],fr[N],id[N],S,T,cost;
	struct node{
		int to,next,val,cost;
	}edge[M];
	void ae(int u,int v,int w,int c){
//		printf("%d %d %d %d\n",u,v,w,c);
		edge[cnt].cost=c,edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
		edge[cnt].cost=-c,edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=0,head[v]=cnt++;
	}
	queue<int>q;
	bool in[N];
	bool SPFA(){
		memset(dis,0x80,sizeof(dis)),dis[S]=0,q.push(S),in[S]=true;
		while(!q.empty()){
			int x=q.front();q.pop(),in[x]=false;
	//		printf("%d\n",x);
			for(int i=head[x];i!=-1;i=edge[i].next){
				if(!edge[i].val)continue;
				if(dis[edge[i].to]<dis[x]+edge[i].cost){
					dis[edge[i].to]=dis[x]+edge[i].cost,fr[edge[i].to]=x,id[edge[i].to]=i;
					if(!in[edge[i].to])in[edge[i].to]=true,q.push(edge[i].to);
				}
			}
		}
		if(dis[T]==dis[0])return false;
		int x=T,mn=0x3f3f3f3f;
		while(x!=S)mn=min(mn,edge[id[x]].val),x=fr[x];
		cost+=dis[T]*mn,x=T;
		while(x!=S)edge[id[x]].val-=mn,edge[id[x]^1].val+=mn,x=fr[x];
		return true;
	}
}
int main(){
	scanf("%d",&n),memset(SCC::head,-1,sizeof(SCC::head)),memset(MCMF::head,-1,sizeof(MCMF::head));
	for(int i=1;i<=n;i++)for(int j=1,x;j<=n;j++){
		scanf("%d",&x);
		if(x)SCC::ae(i,j);
	}
	for(int i=1;i<=n;i++)if(!SCC::dfn[i])SCC::Tarjan(i);
//	for(int i=1;i<=n;i++)printf("%d\n",col[i]);
	MCMF::S=c*2+1,MCMF::T=c*2+2,s=c*2+3,t=c*2+4;
	for(int i=1;i<=n;i++)for(int j=SCC::head[i];j!=-1;j=SCC::edge[j].next){
		if(col[SCC::edge[j].to]==col[i])continue;
		MCMF::ae(col[i]+c,col[SCC::edge[j].to],2,0);
	}
	for(int i=1;i<=c;i++)MCMF::ae(s,i,2,0);
	for(int i=1;i<=c;i++)MCMF::ae(i+c,t,2,0);
	MCMF::ae(MCMF::S,s,2,0),MCMF::ae(t,MCMF::T,2,0);
	for(int i=1;i<=c;i++)MCMF::ae(i,i+c,1,sz[i]),MCMF::ae(i,i+c,1,0);
	while(MCMF::SPFA());
	printf("%d\n",MCMF::cost);
	return 0;
}
```


---

