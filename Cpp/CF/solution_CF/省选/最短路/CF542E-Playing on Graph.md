# Playing on Graph

## 题目描述

Vova and Marina love offering puzzles to each other. Today Marina offered Vova to cope with the following task.

Vova has a non-directed graph consisting of $ n $ vertices and $ m $ edges without loops and multiple edges. Let's define the operation of contraction two vertices $ a $ and $ b $ that are not connected by an edge. As a result of this operation vertices $ a $ and $ b $ are deleted and instead of them a new vertex $ x $ is added into the graph, and also edges are drawn from it to all vertices that were connected with $ a $ or with $ b $ (specifically, if the vertex was connected with both $ a $ and $ b $ , then also exactly one edge is added from $ x $ to it). Thus, as a result of contraction again a non-directed graph is formed, it contains no loops nor multiple edges, and it contains $ (n-1) $ vertices.

Vova must perform the contraction an arbitrary number of times to transform the given graph into a chain of the maximum length. A chain of length $ k $ ( $ k>=0 $ ) is a connected graph whose vertices can be numbered with integers from $ 1 $ to $ k+1 $ so that the edges of the graph connect all pairs of vertices $ (i,i+1) $ ( $ 1<=i<=k $ ) and only them. Specifically, the graph that consists of one vertex is a chain of length $ 0 $ . The vertices that are formed as a result of the contraction are allowed to be used in the following operations of contraction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542E/af074449ee48bd32c82bb3936d4a12640f3f4852.png)The picture illustrates the contraction of two vertices marked by red.Help Vova cope with his girlfriend's task. Find the maximum length of the chain that can be obtained from the resulting graph or else determine that it is impossible to obtain the chain.

## 说明/提示

In the first sample test you can contract vertices $ 4 $ and $ 5 $ and obtain a chain of length $ 3 $ .

In the second sample test it is initially impossible to contract any pair of vertexes, so it is impossible to achieve the desired result.

In the third sample test you can contract vertices $ 1 $ and $ 2 $ and obtain a chain of length $ 2 $ .

## 样例 #1

### 输入

```
5 4
1 2
2 3
3 4
3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 6
1 2
2 3
1 3
3 4
2 4
1 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 2
1 3
2 4
```

### 输出

```
2
```

# 题解

## 作者：syzf2222 (赞：5)

图论思维好题，值得一做。[更好的阅读体验](https://www.cnblogs.com/syzf2222/p/14045068.html)

考虑怎样的情况是一定不合法的。结论：图不合法当且仅当存在奇环。

充分性证明：（1）三角形不合法；（2）任意缩奇环中的两个点将产生一个更小的奇环。

必要性证明：没有奇环的图为二分图，而二分图一定可以缩成链（*）

因为连接两条链会产生一条长度为两条链的和的一条新链，故考虑在每个二分联通子图中找出最长链即可。

考虑以一个点$x$作为链的起点，建一棵$bfs$树。

由于是二分图，$bfs$树**同一层节点之间没有连边**。

由于是$bfs$树，**每个点的连边只能在相邻一层的范围内，且必定和上一层节点有连边**。

那么我们把同一层节点缩在一起，就可以得到一条链（这也证明了*结论）。

思考为何此链为最长链。考虑若结论错误，则必存在如下回环的结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/lmufdkso.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图中的$1\rightarrow 2\rightarrow 4\rightarrow 6\rightarrow 8$

为了保持这条链的结构，则只能想办法通过缩$1\rightarrow 8$上的点断开$1\rightarrow 8$，然而缩点并不干扰连通性，故不可能。

时间复杂度$\Theta(n^2)$，由于$n\leq 1000$，可以通过本题。

参考了[这篇博客](https://blog.csdn.net/weixin_30793643/article/details/97027790)，他写的很好。

代码如下，仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int N=1005;
const int maxn=2e5+10;
int n,m,dis[N],len[N],ans;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int beg[N],nex[maxn],to[maxn],w[maxn],e;
inline void add(int x,int y){
	e++;nex[e]=beg[x];
	beg[x]=e;to[e]=y;
}
int bel[N],col[N],scc,flag;
inline void dfs(int x){
	bel[x]=scc;
	for(int i=beg[x];i;i=nex[i]){
		int t=to[i];
		if(!bel[t])col[t]=1^col[x],dfs(t);
		else if(col[x]==col[t])flag=1;
	}
}
queue<int>q;
inline void bfs(int x){
	memset(dis,-1,sizeof(dis));
	q.push(x);dis[x]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=beg[x];i;i=nex[i]){
			int t=to[i];
			if(dis[t]==-1){
				dis[t]=dis[x]+1;
				q.push(t);
			}
		}
	}
}
int main(){
	n=read(),m=read();
	int x,y;
	for(int i=1;i<=m;i++){
		x=read(),y=read();
		add(x,y),add(y,x);
	}
	for(int i=1;i<=n;i++)
		if(!bel[i])scc++,dfs(i);
	if(flag)return puts("-1"),0;
	for(int i=1;i<=n;i++){
		bfs(i);
		for(int j=1;j<=n;j++)
			len[bel[j]]=max(len[bel[j]],dis[j]);
	}
	for(int i=1;i<=scc;i++)
		ans+=len[i];
	printf("%d\n",ans);
	return 0;
}
```
深深地感到自己的弱小。

---

## 作者：大菜鸡fks (赞：2)

很显然若原图存在奇环，则输出-1，可以用染色判奇环。

换而言之，只有二分图有解。 接下来，可以发现，最终答案就是所有联通块直径之和。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1005,M=100005;
struct edge{
    int link,next;
}e[M<<1];
int n,m,tot,head[N];
inline void add_edge(int u,int v){
    e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
    add_edge(u,v); add_edge(v,u);
}
inline void init(){
    n=read(); m=read();
    for (int i=1;i<=m;i++){
        insert(read(),read());
    }
}
int belong[N],cnt,col[N],flag;
void dfs(int u){
    belong[u]=cnt;
    for (int i=head[u];i;i=e[i].next){
        int v=e[i].link;
        if (!belong[v]) col[v]=col[u]^1,dfs(v);
            else if (col[u]==col[v]) flag=1;
    }	
}
int h,t,ans[N],sum,dis[N],q[N];
inline void bfs(int S){
    memset(dis,-1,sizeof dis);
    h=t=0; dis[S]=0; q[++t]=S;
    while (h<t){
        int u=q[++h];
        for (int i=head[u];i;i=e[i].next){
            int v=e[i].link;
            if (dis[v]==-1){
                dis[v]=dis[u]+1;
                q[++t]=v;
            }
        }
    }
}
inline void solve(){
    for (int i=1;i<=n;i++){
        if (!belong[i]){
            ++cnt; dfs(i);
            if (flag) {
                writeln(-1); return;
            }
        }
    }
    for (int i=1;i<=n;i++){
        bfs(i);
        for (int j=1;j<=n;j++){
            ans[belong[i]]=max(ans[belong[i]],dis[j]);
        }
    }
    for (int i=1;i<=cnt;i++) sum+=ans[i];
    writeln(sum);
}
int main(){
    init(); solve();
    return 0;
}
```


---

