# TOF

## 题目描述

今天，Pari 给 Arya 出了一个有趣的图论题目。Arya 编写了一个性能不佳的解决方案，因为他相信自己能够优化这些非最佳方案。不仅如此，代码中还存在不少错误，他尝试了多次进行优化，结果代码变得非常杂乱！他不断遇到“超出时间限制”的问题，这让他感到很失望。不过突然之间，他灵光一现！

下列是他的杂乱代码：

```cpp
dfs(v) {
    count[v] = count[v] + 1;
    if (count[v] < 1000) {
        foreach u in neighbors[v] {
            if (visited[u] == false) {
                dfs(u);
            }
            break;
        }
    }
    visited[v] = true;
}

main() {
    输入有向图();
    TOF();
    for 1 <= i <= n {
        count[i] = 0;
        visited[i] = false;
    }
    for 1 <= v <= n {
        if (visited[v] == false) {
            dfs(v);
        }
    }
    // 之后会做一些很酷而神奇的事情，但我们不能告诉你具体是什么！
}
```

Arya 请求你帮助编写 `TOF` 函数，以优化代码运行时间，并尽量减少 `dfs` 函数的调用次数。输入是一个有向图，你需要在 `TOF` 函数中重新排列每个顶点的邻接表。`dfs` 函数的调用次数与每个顶点的邻接顺序有关。

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
2998
```

## 样例 #2

### 输入

```
6 7
1 2
2 3
3 1
3 4
4 5
5 6
6 4
```

### 输出

```
3001
```

# 题解

## 作者：9AC8E2 (赞：0)

1. 事实上是选一条出边,所以是一个基环内向树与树森林.
2. 已经回溯的点永远不会被访问.
3. 环的次数为点数$\times 999+1$.
4. 答案为环上的总点数$\times 998+n+$环数.
5. $1\rightarrow n$的访问顺序并没有什么关系,因为无论按什么顺序访问,最后的`count`数组都是一样的.
6. 我们称不在环中的点为好点.
7. 若一个点没有出边,那么所有能到达它的点都为好点.
8. 将强连通分量缩点之后,若一个强连通分量没有出边,那么它只能自立更生解决这个强连通分量中所有的点.方法是选择最小环,剩余所有点都一定有一条到达最小环上点的有向路径,所以除了最小环上的点都为好点.
9. 若一个强连通分量有出边,那么这个强连通分量中的所有点也一定存在一条到达其他强连通分量中最小环的有向路径,所以没必要再构造一个环.
10. 对于找最小环,可以暴力 $\mathcal{BFS}$ 实现.

```
int n,m;
int head[5005],to[5005],ne[5005],total=1;
inline void add(int a,int b)
{
	total++;
	to[total]=b;
	ne[total]=head[a];
	head[a]=total;
}
int dfn[5005],dfn_top;
int low[5005];
bool inq[5005];
int st[5005],st_top;
vector<int>scc[5005];
int scc_top;
int bel[5005];
void tarjan(int now)
{
	dfn[now]=low[now]=++dfn_top;
	inq[now]=1;st[++st_top]=now; 
	for(int i=head[now];i;i=ne[i])
		if(!dfn[to[i]])
			tarjan(to[i]),low[now]=min(low[now],low[to[i]]);
		else
			if(inq[to[i]])low[now]=min(low[now],dfn[to[i]]);
	if(dfn[now]==low[now])
	{
		scc_top++;
		while(1)
		{
			int y=st[st_top];
			st_top--;inq[y]=0;
			scc[scc_top].push_back(y);
			bel[y]=scc_top;
			if(y==now)break;
		}
	}
}
int dis[5005];
int find(int x)
{
	for(int i:scc[bel[x]])dis[i]=1e9;
	dis[x]=0;
	queue<int>q;q.push(x);
	while(q.size())
	{
		int now=q.front();q.pop();
		for(int i=head[now];i;i=ne[i])
			if(bel[to[i]]==bel[x]&&dis[to[i]]>dis[now]+1)
				dis[to[i]]=dis[now]+1,q.push(to[i]);
	}
	int ans=1e9;
	for(int now:scc[bel[x]])
		for(int i=head[now];i;i=ne[i])
			if(to[i]==x)
				ans=min(ans,dis[now]+1);
	return ans;
}
int main()
{
	read(n,m);
	for(int i=1,x,y;i<=m;i++)
		read(x,y),
		add(x,y);
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i);
	int ans=n;
	for(int i=1;i<=scc_top;i++)
	{
		int num=0;
		for(int now:scc[i])
			for(int j=head[now];j;j=ne[j])
				if(bel[to[j]]!=i)
					num++;
		if(num)continue;
		if(scc[i].size()==1)continue;
		int sum=1e9;
		for(int j:scc[i])sum=min(sum,find(j));
//		printf("sum=%d\n",sum);
		ans+=sum*998+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

