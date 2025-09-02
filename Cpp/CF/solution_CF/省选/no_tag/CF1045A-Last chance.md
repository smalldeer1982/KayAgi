# Last chance

## 题目描述

公元 2969 年。距离人类首次登月已经过去了 1000 年。在这期间，人类已经殖民了“超空间”，并一直和谐共处。

直到我们发现，我们并不孤单。

距离地球不远处，外星人的庞大舰队正准备进攻地球。人类第一次真正陷入危机。危机与恐慌无处不在。来自太阳系各地的科学家们齐聚一堂，讨论可能的解决方案。然而，始终没有取得进展。

地球最后的希望就是你！

幸运的是，地球装备了由 MDCS 制造的极其强大的防御系统。有 $N$ 艘外星飞船排成一行。防御系统由三种武器组成：

- SQL 火箭 —— 每枚 SQL 火箭可以摧毁给定集合中的至多一艘飞船。
- Cognition 光束 —— 每道 Cognition 光束有一个区间 $[l, r]$，可以摧毁该区间内的至多一艘飞船。
- OMG 火箭筒 —— 每个 OMG 火箭筒有三个可能的目标，但每个火箭筒只能摧毁零艘或恰好两艘飞船。此外，由于智能瞄准系统，任意两个 OMG 火箭筒的三个目标集合互不相交（即每艘飞船至多被一个 OMG 火箭筒瞄准）。

你的任务是制定一份攻击计划，使被摧毁的飞船数量最大。每艘被摧毁的飞船必须且只能被一种武器摧毁。

## 说明/提示

SQL 火箭只能摧毁第 4 号飞船。OMG 火箭筒可以摧毁第 1、4、5 号飞船中的任意两艘。Cognition 光束可以摧毁区间 $[1,4]$ 内的任意一艘飞船。最大可摧毁飞船数为 4，一种可行方案是：SQL 火箭摧毁第 4 号飞船，OMG 火箭筒摧毁第 1 号和第 5 号飞船，Cognition 光束摧毁第 2 号飞船。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 5
0 1 4
2 5 4 1
1 1 4
```

### 输出

```
4
2 1
3 2
1 4
2 5
```

# 题解

## 作者：mrsrz (赞：5)

网络流+线段树优化。

这个东西，显然网络流一遍就可以了。

考虑第3种武器要恰好攻击2个的限制。

如果这个武器只攻击了1个，则另外两个星球一定都被其他武器攻击了（且不是第3种），那么，直接用这个武器替换攻击某个星球的武器，其最多攻击的星球个数不变，因此先不必考虑。

直接对每种武器建一个点，对每个星球建一个点。

对于第1种武器，从源点向这个点连容量为1的边，从这个武器向其所有能攻击到的星球连容量为1的边。

对于第2种武器，从源点向这个点连容量为1的边，然后直接对区间内每个星球连边的话，边为$O(n^2)$级别的，所以线段树优化一下即可。

对于第3种武器，从源点向这个点连容量为2的边，表示最多能攻击2个星球。然后再分别向$a,b,c$星球连容量为1的边即可。

每个星球向汇点连容量为1的边，表示只能攻击一次。

然后跑一遍最大流即可，最大流就是最多能攻击的星球个数。

再考虑求方案，可以从汇点出发，沿着有容量的反向边（说明被走过）流回去即可知道每个星球被哪个武器攻击。流回去的途中要注意减掉1的容量，否则会出现重复走的情况。然后找到答案要及时退出。

然后再考虑第3种武器要恰好攻击2个的限制。如果它只攻击了1个星球，直接把另外两个中的某一个改成用这个武器攻击即可。

## Code：
```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define inf 1234567890
#define T 33333
int n,m,cnt=1,d[200005],node,head[44444],iter[44444],dep[44444],ys[5001],tot[5001];
struct edge{
	int to,nxt,cap;
}e[2333333];
struct wea{
	int op,l,r,a,b,c,k;
}v[5005];
inline void addedge(int u,int v,int cap){
	e[++cnt]=(edge){v,head[u],cap};head[u]=cnt;
	e[++cnt]=(edge){u,head[v],0};head[v]=cnt;
}
void build(int l,int r,int o){
	if(l==r){
		d[o]=l;
		return;
	}
	d[o]=++node;
	const int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	addedge(d[o],d[o<<1],inf);
	addedge(d[o],d[o<<1|1],inf);
}
void add(int l,int r,int o,int id,const int&L,const int&R){
	if(L<=l&&r<=R){
		addedge(id,d[o],1);
		return;
	}
	const int mid=l+r>>1;
	if(L<=mid)add(l,mid,o<<1,id,L,R);
	if(mid<R)add(mid+1,r,o<<1|1,id,L,R);
}
std::queue<int>q;
void bfs(){
	dep[0]=1;
	q.push(0);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt)
		if(e[i].cap&&!dep[e[i].to]){
			dep[e[i].to]=dep[u]+1;
			q.push(e[i].to);
		}
	}
}
int dfs(int u,int f){
	if(!f||u==T)return f;
	for(int&i=iter[u];i;i=e[i].nxt)
	if(e[i].cap&&dep[u]<dep[e[i].to]){
		int d=dfs(e[i].to,std::min(f,e[i].cap));
		if(d){
			e[i].cap-=d;
			e[i^1].cap+=d;
			return d;
		}
	}
	return 0;
}
int dinic(){
	for(int f,flow=0;;){
		memset(dep,0,sizeof dep);
		bfs();
		if(!dep[T])return flow;
		memcpy(iter,head,sizeof iter);
		while(f=dfs(0,inf))flow+=f;
	}
}
void find(int now,int&s,int pre){
	if(s)return;
	if(now>m&&now<=n+m){
		s=now-m;
		return;
	}
	for(int i=head[now];i;i=e[i].nxt)
	if(e[i].to!=pre&&e[i].cap){
		find(e[i].to,s,now);
		--e[i].cap;
		return;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	node=n+m;
	build(1,m,1);
	for(int i=1;i<=n;++i){
		scanf("%d",&v[i].op);
		if(v[i].op==0){
			scanf("%d",&v[i].k);
			addedge(0,i+m,1);
			for(int j=0;j<v[i].k;++j){
				int x;
				scanf("%d",&x);
				addedge(i+m,x,1);
			}
		}else
		if(v[i].op==1){
			addedge(0,i+m,1);
			scanf("%d%d",&v[i].l,&v[i].r);
			add(1,m,1,i+m,v[i].l,v[i].r);
		}else{
			addedge(0,i+m,2);
			scanf("%d%d%d",&v[i].a,&v[i].b,&v[i].c);
			addedge(i+m,v[i].a,1);
			addedge(i+m,v[i].b,1);
			addedge(i+m,v[i].c,1);
		}
	}
	for(int i=1;i<=m;++i)addedge(i,T,1);
	int mx=dinic();
	printf("%d\n",mx);
	for(int i=head[T];i;i=e[i].nxt)
	if(e[i].cap){
		find(e[i].to,ys[e[i].to],T);
	}
	for(int i=1;i<=m;++i)++tot[ys[i]];
	for(int i=1;i<=n;++i)
	if(v[i].op==2&&tot[i]==1){
		if(ys[v[i].a]!=i)ys[v[i].a]=i;else
		ys[v[i].b]=i;
	}
	for(int i=1;i<=m;++i)
	if(ys[i])printf("%d %d\n",ys[i],i);
	return 0;
}
```

---

