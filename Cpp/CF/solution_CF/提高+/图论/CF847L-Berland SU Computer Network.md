# Berland SU Computer Network

## 题目描述

In the computer network of the Berland State University there are $ n $ routers numbered from $ 1 $ to $ n $ . Some pairs of routers are connected by patch cords. Information can be transmitted over patch cords in both direction. The network is arranged in such a way that communication between any two routers (directly or through other routers) is possible. There are no cycles in the network, so there is only one path between each pair of routers over patch cords.

Unfortunately, the exact topology of the network was lost by administrators. In order to restore it, the following auxiliary information was collected.

For each patch cord $ p $ , directly connected to the router $ i $ , list of routers located behind the patch cord $ p $ relatively $ i $ is known. In other words, all routers path from which to the router $ i $ goes through $ p $ are known. So for each router $ i $ there are $ k_{i} $ lists, where $ k_{i} $ is the number of patch cords connected to $ i $ .

For example, let the network consists of three routers connected in chain $ 1-2-3 $ . Then:

- the router $ 1 $ : for the single patch cord connected to the first router there is a single list containing two routers: $ 2 $ and $ 3 $ ;
- the router $ 2 $ : for each of the patch cords connected to the second router there is a list: one list contains the router $ 1 $ and the other — the router $ 3 $ ;
- the router $ 3 $ : for the single patch cord connected to the third router there is a single list containing two routers: $ 1 $ and $ 2 $ .

Your task is to help administrators to restore the network topology, i. e. to identify all pairs of routers directly connected by a patch cord.

## 说明/提示

The first example is analyzed in the statement.

The answer to the second example is shown on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847L/e101c14c7ca1e10d8c7b2619158ff5db62d03be1.png)The first router has one list, which contains all other routers. The second router has three lists: the first — the single router $ 4 $ , the second — the single router $ 1 $ , the third — two routers $ 3 $ and $ 5 $ . The third router has one list, which contains all other routers. The fourth router also has one list, which contains all other routers. The fifth router has two lists: the first — the single router $ 3 $ , the second — three routers $ 1 $ , $ 2 $ and $ 4 $ .

## 样例 #1

### 输入

```
3
2:3,2
1:1-1:3
2:1,2
```

### 输出

```
2
2 1
2 3
```

## 样例 #2

### 输入

```
5
4:2,5,3,4
1:4-1:1-2:5,3
4:4,5,2,1
4:2,1,3,5
1:3-3:4,2,1
```

### 输出

```
4
2 1
2 4
5 2
3 5
```

## 样例 #3

### 输入

```
3
1:2-1:3
1:1-1:3
1:1-1:2
```

### 输出

```
-1
```

# 题解

## 作者：极寒神冰 (赞：1)

在树上$a,b$两点存在边当且仅当包含$b$的$a$集合大小与包含$a$的$b$集合大小之和为$n$。因此直接暴力找出所有的边然后一堆判断是否是一棵树即可。

稍微讲一下怎么判：

1. 首先边数不为$n-1$时显然不是一棵树。

2. `dfs`一遍判断这是否是一棵树，具体为看一个点是否被多次访问到以及最后根节点子树和应该为$n$
3. 最后暴力判断假设某个点为根，那么子树的情况是否与输入时相同。本人是直接每个点开了`vector<vector<int>>`记录子树内的情况，然后每次`sort`一遍方便判断两个集合是否相等。当然这也可以用`hash`做到。

```cpp
int n,m;
vector<vector<int>>t[1111];
vector<pii>ans;
vector<int>e[1111];
int cnt[1111][1111],cnte;
int vis[1111],siz[1111],fa[1111];
void dfs1(int u)
{
    siz[u]=1;
    vis[u]=1;
    for(int v:e[u]) if(v^fa[u])
    {
        if(vis[v]) evil();
        fa[v]=u;
        dfs1(v);
        siz[u]+=siz[v];
    }
}
void dfs2(int u,int f,vector<int>&chi)
{
    chi.pb(u);
    for(int v:e[u]) if(v^f) dfs2(v,u,chi); 
}
void check()
{
    R(u,1,n)
    {
        vector<vector<int>>all;
        for(int v:e[u])
        {
            all.pb(vector<int>());
            dfs2(v,u,all.back());
            sort(all.back().begin(),all.back().end());
        }
        sort(all.begin(),all.end());
        if(t[u]!=all) evil();
    }   
}
signed main()
{
    scanf("%d",&n);
    R(i,1,n)
    {
        int del=n-1;
        while(del)
        {
            t[i].pb(vector<int>());
            scanf("%d:",&m);
            int x;
            R(j,1,m)
            {
                scanf("%d",&x);
                t[i].back().pb(x);
                if(j+1<=m) scanf(",");
                cnt[i][x]=m;
            }
            sort(t[i].back().begin(),t[i].back().end());
            del-=m;
            if(del) scanf("-");
        }
        sort(t[i].begin(),t[i].end());
    }
    R(u,1,n) R(v,u+1,n) if(cnt[u][v]+cnt[v][u]==n) e[u].pb(v),e[v].pb(u),++cnte,ans.pb(mkp(u,v));
    if(cnte^(n-1)) evil();
    dfs1(1);
    if(siz[1]^n) evil();
    check();
    writeln((int)ans.size());
    for(auto v:ans) writesp(v.fi),writeln(v.se);
}

```



---

## 作者：xzggzh1 (赞：1)

题意：

给你一个无根树中每个节点有多少儿子和每个儿子子树中包含那些节点。（用 `-` 来分隔各个儿子）。 

要求你输出这个树，或者指出不存在这样的树。 

$n \leq 10^3$。

---

一道比较简单的构造题。既然给出了每个儿子所在子树的节点。那么我们可以直观考虑从简单处入手。

什么最简单？叶子节点，如果一个节点是叶子节点，那么这个节点只有一个儿子（无根树），这样就可以把一个叶子节点抽出来了。

抽出来之后，自然是找道一个节点与他相连然后连边。这个节点处理好了，信息也没用了之后把这个叶子删掉，这样又会有新的叶子出现，过程类似于拓扑排序，可以用队列实现。

处理结果是否合法也是一个要点，如果少考虑不合法情况容易被卡掉。（这里默认大家都会处理输入）。

---

核心代码：
```cpp
int n,sz[1010][1010],cnt[1010],in[1010][1010],tot=0,used[1010];
queue<int>q;
struct e{
	int from,to,nex;
}r[2333];
int ecnt=1,hea[1010]={0};
void dfs(int x,int fff,int rt){ 
	if (fff!=rt&&in[x][rt]!=in[fff][rt])
	exit(0*puts("-1"));
	for (int i=hea[x],y;i>0;i=r[i].nex){y=r[i].to; if (y==fff) continue;dfs(y,x,rt);}
} 
int main(){
	int las,k,x;
	if (tot!=2*(n-1)) return 0*puts("-1"); 
	for (int fl;!q.empty();){
		x=q.front();q.pop();
		cnt[x]=0;fl=0;
		for (int i=1;i<=n;i++){
			if (!cnt[i]) continue;
			if (sz[i][in[x][i]]==1){
				r[++ecnt]=(e){x,i,hea[x]};hea[x]=ecnt;
				r[++ecnt]=(e){i,x,hea[i]};hea[i]=ecnt;
				fl++;
			}
		}
		for (int i=1;i<=n;i++){
			if (!cnt[i]) continue;
			if (sz[i][in[x][i]]){
				sz[i][in[x][i]]--;
				if (sz[i][in[x][i]]==0){cnt[i]--;if (cnt[i]==1)q.push(i);}
			}
			else return 0*puts("-1");
		}
	}
	//检查是否合法 
	if (ecnt!=(n*2-1)) return 0*puts("-1");
	for (int x=1,y;x<=n;x++){
		memset(used,0,sizeof used);
		for (int i=hea[x];i>0;i=r[i].nex){
			y=r[i].to;
			if(used[in[y][x]]) return 0*puts("-1");
			used[in[y][x]]=1;dfs(y,x,x);
		}
	}
	printf("%d\n",n-1);
	for (int i=1;i<n;i++)
	printf("%d %d\n",r[i<<1].from,r[i<<1].to);
}
```




---

