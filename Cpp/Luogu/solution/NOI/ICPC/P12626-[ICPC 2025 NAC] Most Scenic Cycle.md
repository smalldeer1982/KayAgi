# [ICPC 2025 NAC] Most Scenic Cycle

## 题目描述

独立出题者国家（ICPC）政$ $府终于攒够了建设高速铁路系统的资金。新铁路系统包含 $V$ 个车站和 $E$ 条双向直达铁路线，每条线路连接两个车站。ICPC 铁路基础设施规划负责人 Skib E. Dee 深知树形拓扑交通网络的弊端：单条铁路线损坏会导致网络分裂，造成数日交通中断。因此，Dee 决定将 ICPC 铁路网络设计为**强健连通**：任意两个车站 $s_1$ 和 $s_2$ 之间必须存在至少两条路径，这两条路径不共享任何直达铁路线，且除 $s_1$ 和 $s_2$ 外不共享任何车站。

当然，ICPC 无法承担过多冗余铁路线的建设成本。为平衡效率与鲁棒性，Dee 还将网络设计为**区域连通**。一个环是指从某车站出发回到自身且不重复经过任何车站（起始车站仅在开头和结尾各出现一次）的非空路径。要实现区域连通，必须存在由 $E-V+1$ 个**区域环**组成的集合 $\mathcal{F}$，满足以下三个性质：
- 交通网络中每条直达铁路线至少属于一个区域环；
- 若两个区域环共享任何直达铁路线，则它们共享的所有铁路线和车站必须构成一条连通路径；
- 对于 $\mathcal{F}$ 的任意子集 $f$，其中共享铁路线的区域环对数不超过 $|f|-1$。

为宣传新高铁，Dee 需要制作一段火车沿铁路环线行驶的延时视频。每条直达铁路线都有一个（可能为负的）风景值，表示沿线车窗外的景色优美程度。Dee 希望选择风景值总和最大的环线作为拍摄路线（该环线**不必**是区域环）。为确保环线不单调，它必须包含至少两条铁路线，且不重复经过任何车站（起始车站仅在开头和结尾各出现一次）。

## 说明/提示

对于样例输入 2 的铁路网络，集合 $\mathcal{F}$ 的区域环可选为 $1 \rightarrow 2 \rightarrow 5 \rightarrow 1$、$2 \rightarrow 5 \rightarrow 3 \rightarrow 2$ 和 $3 \rightarrow 4 \rightarrow 5 \rightarrow 3$（左图）。风景值总和最大的环线（右图蓝色路径）的风景值总和为 $9+6+3-2=16$。

![](https://cdn.luogu.com.cn/upload/image_hosting/31jr1qj8.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6 9
1 2 9
2 3 9
3 4 9
3 4 -9
4 1 9
1 5 1
5 6 1
6 2 1
3 4 8```

### 输出

```
36```

## 样例 #2

### 输入

```
5 7
1 2 1
2 3 -2
3 4 3
4 5 6
5 1 4
5 3 2
2 5 9```

### 输出

```
16```

# 题解

## 作者：251Sec (赞：23)

大胆猜测：题目给的条件一点用都没有，原图是广义串并联图。写一发交上去发现过了。

---

## 作者：Rainbow_qwq (赞：3)

原题的图的条件是：

- 是点双连通图。
- 对于任意 $n$ 个环，画出它们两两相交的路径，最多有 $n-1$ 条。

第二个条件说明如果取对偶图，对偶图的每个点是一个简单环，那么对偶图是一棵树。

然后不难发现图是广义串并联图（可以每次缩掉对偶图的一个叶子）。要求权值最大环，改一下 compress 和 twist 就好了。

```cpp
#define maxn 1000005
#define inf 0x3f3f3f3f3f3f3f3f

int n,m,res;

struct node{
	int x;
	node(int xx=-inf){x=xx;}
};
node T(node a,node b){
	res=max(res,a.x+b.x);
	return node(max(a.x,b.x));
}
node C(node a,node b){
	return node(a.x+b.x);
}

map<int,node>G[maxn];
int ord[maxn];
void add(int u,int v,node w){
	if(G[u].count(v)) G[u][v]=G[v][u]=T(G[u][v],w);
	else G[u][v]=G[v][u]=w;
}
void dele(int u,int v){
	G[u].erase(v),G[v].erase(u);
}

void build()
{
	queue<int>q; int idx=0;
	For(i,1,n)if(G[i].size()<=2)q.push(i);
	while(q.size()){
		int u=q.front();q.pop();
		if(ord[u])continue;
		ord[u]=++idx;
		if(G[u].size()==1){
			auto [v,w]=*G[u].begin();
			if(G[v].size()<=2)q.push(v);
		}
		if(G[u].size()==2){
			auto [x,w1]=*G[u].begin();
			auto [y,w2]=*G[u].rbegin();
			dele(u,x),dele(u,y);
			add(x,y,C(w1,w2));
			if(G[x].size()<=2)q.push(x);
			if(G[y].size()<=2)q.push(y);
		}
	}
	assert(idx==n);
}

signed main()
{
	n=read(),m=read();
	res=-inf;
	For(i,1,m){
		int u=read(),v=read(),w=read();
		add(u,v,w);
	}
	build();
	cout<<res;
	return 0;
}
/*
6 5
1 2 9
2 3 9
3 4 9
3 4 -9
4 1 9
*/
```

---

