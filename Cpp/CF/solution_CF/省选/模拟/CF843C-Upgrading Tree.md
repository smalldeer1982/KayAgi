# Upgrading Tree

## 题目描述

You are given a tree with $ n $ vertices and you are allowed to perform no more than $ 2n $ transformations on it. Transformation is defined by three vertices $ x,y,y' $ and consists of deleting edge $ (x,y) $ and adding edge $ (x,y') $ . Transformation $ x,y,y' $ could be performed if all the following conditions are satisfied:

1. There is an edge $ (x,y) $ in the current tree.
2. After the transformation the graph remains a tree.
3. After the deletion of edge $ (x,y) $ the tree would consist of two connected components. Let's denote the set of nodes in the component containing vertex $ x $ by $ V_{x} $ , and the set of nodes in the component containing vertex $ y $ by $ V_{y} $ . Then condition $ |V_{x}|&gt;|V_{y}| $ should be satisfied, i.e. the size of the component with $ x $ should be strictly larger than the size of the component with $ y $ .

You should minimize the sum of squared distances between all pairs of vertices in a tree, which you could get after no more than $ 2n $ transformations and output any sequence of transformations leading initial tree to such state.

Note that you don't need to minimize the number of operations. It is necessary to minimize only the sum of the squared distances.

## 说明/提示

This is a picture for the second sample. Added edges are dark, deleted edges are dotted.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843C/5905cec6b2c0826d6ba38e3611ad2a2ba852ba57.png)

## 样例 #1

### 输入

```
3
3 2
1 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7
1 2
2 3
3 4
4 5
5 6
6 7
```

### 输出

```
2
4 3 2
4 5 6```

# 题解

## 作者：Twig_K (赞：4)

## 一些思路

要最小化两两距离的平方和，理想状态下肯定是缩成严格的菊花（除了中心点外所有点度数为 $1$），不过这种状态不一定能达到，因为我们的构造收到题面翻译中第三条限制的约束。

由断边子树大小的限制想到重心，我们没有办法改变重心的度数，所以考虑让最终答案尽可能长成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/k1zi9s73.png)

图中菊花的花瓣指下面挂的一圈子节点。重心可能有一个，也可能有两个。

## 构造

树的形态比较乱，先考虑链怎么缩成上图。

![](https://cdn.luogu.com.cn/upload/image_hosting/vvz5yoni.png)

定义根节点为重心（两个重心无所谓，反正左右是独立开来考虑的）。对于左半部分，左端第二个点是 $u=2$，从左端的第三个点开始，每次执行 $(fa_i,i,u)$。右半部分右端第二个点是 $u=9$，同理从右往左更新。容易发现最后两边菊花的花心就是 $u$，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/pxxghuvq.png)

-------------

再来考虑，对于原图，如何把重心的每一个子树连成一条链，目标形态是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/eg8wjtcu.png)

操作数限制是 $2n$，所以先把原树变成上图，再把上图的每一条纵链变成一朵菊花，这样是正确的。

我们已经解决了链变成菊花的问题，现在考虑怎么把原树变成上图。

![](https://cdn.luogu.com.cn/upload/image_hosting/848hbu5g.png)

$rt$ 是重心，子树 $1$ 是重心的其中一个子树。我们尝试从断开 $(rt,1)$ 并让 $rt$ 连接上某个叶子（因为叶子的度数为 $1$），接着断开这个叶子和它父亲的边，用这个叶子连第二个叶子。同样地，断开第二个叶子和它父亲的边，去连下一个叶子……当一个点的所有儿子都被处理完时，这个点就变成叶子了，这样自下向上连边，可以形成一条链。

![](https://cdn.luogu.com.cn/upload/image_hosting/kegg987d.png)

如图。怎么实现呢？真是太菜了想了很久，其实只需要从重心的该子树的根开始 dfs，类似于树上删点，遍历完儿子自己成为叶子后再“删”自己，每次和上一次删去的叶子连接成链即可，这样一定是对的，我们每次删的都是叶子，因为子树内的点已经断开了和父亲的连边。

## 代码

完整代码见[提交记录](https://codeforces.com/contest/843/submission/298488396)，下面一段是对部分代码的注释。

```cpp
struct node{ int xx,yy,zz; };
vector<node> res;
int x,y;
//对于mdf：x,y 是删去的上一条边，在全局记录
//对于flower：x 是菊花的花心
int h[maxn];//h 记录高度
void mdf(int u,int fa){
    for(auto v:ve[u]) if(v^fa) mdf(v,u);
    res.pb((node){x,y,u}),g[x].pb(u),x=u,y=fa;
//ve 是输入的原树，g 是变成链后的新树
}
void flower(int u){
//flower 函数中用的都是 g
    if((int)g[u].size()==0){ h[u]=1,x=u;return; }
    int v=g[u][0];flower(v);h[u]=h[v]+1;
    if(h[u]==2) x=u;
    else if(h[u]>3) res.pb((node){u,v,x}); //向花心连边
}
signed main()
{
    rd(n);
    For(i,2,n){ int u,v;rd(u,v);ve[u].pb(v),ve[v].pb(u); }
    dfs(1,0);//dfs求重心
    For(C,1,n){ //c[i]==tmp 表示是重心
        if(c[C]!=tmp) continue;
        for(int u:ve[C]) if(c[u]^tmp) x=C,y=u,mdf(u,C);
//mdf: 遍历这个重心的每一个子树，把每个子树变成一条链挂在重心下
        for(int u:g[C]) flower(u),res.pb((node){C,u,x});
//flower: 把每个子树（已经变成链了）变成菊花挂在重心下
    }
    write((int)res.size()),End;
    for(auto v:res) write(v.xx,v.yy,v.zz),End;
    return 0;
}
```

---

## 作者：xzggzh1 (赞：3)

题意：

每次可以对一个树经行最多 $2n$ 次操作  $(x,y,y')$ 表示将 $(x,y)$ 删除，同时加入一条边 $(x,y')$ 。

每次操作要求 ：

1. 每次操作中 $(x,y)$ 存在。

1. 操作后仍然是树。

1. 每次删了 $(x,y)$ 时，必须保证包含 $x$ 的子树中的节点数比包含 $y$ 的节点数大。

最后使得所有点距离的平方和最小。输出一种操作的方案。$n\leq 2\times 10^5$。

---

直接莽：对于一次操作 贡献是： (能想到这种操作的也只有笔者这样的菜逼了)

$$\sum_{u\in V_x}\sum_{v\in V_y} \big( dis\left(u,x\right)+dis\left(y',v\right)\big)^2 -\sum_{u\in V_x}\sum_{v\in V_y} \big(  dis\left(u,x\right)+dis\left(y,v\right))\big)^2$$

$$=V_x \sum_{v\in V_y} \big(dis(y',v)^2-dis(y,v)^2\big)+ \sum_{u \in V_x} \sum_{v\in V_y}{2\times dis(u,x)\times(dis(y',v)-dis(y,v))}$$


$$=…=\text{不会}$$ 


---

考虑操作的特殊性，也就是第三点，对于子树节点的限制可以推出在每一次操作之后树的重心都不会变（根据重心的定义可知，两个重心也不会影响这个结论）。

考虑操作的局限性：无法增加和减少与重心的度数（如果是两个重心，那么这俩个重心的连这的边不会改变，其实两个重心的情况可以把这两个重心缩成一个）。

我们可以根据给我们的 $2n$ 次操作，首先用最多 $n$ 次的操作来把重心连出去的子树变成一条条链。

然后再用最多 $n$ 次把重心连出去的子树变成菊花图（感性思考一下，菊花图的时候显然答案更优）。



----

部分代码：

```cpp

void add(int x,int y){e[++tot]=(edge){y,head[x]};head[x]=tot;}
void dfs(int x,int fa){
	sz[x]=1; mx[x]=0;
	for (int i=head[x];i;i=e[i].next)
		if (e[i].to!=fa){
			dfs(e[i].to,x);
			sz[x]+=sz[e[i].to];
			mx[x]=max(mx[x],sz[e[i].to]);
		}
	if (sz[x]*2>=n&&mx[x]*2<=n) rt[x]=1;
}
void change(int x,int y,int z){ans[++cnt][0]=x;ans[cnt][1]=y;ans[cnt][2]=z;}
void solve(int x){
	for (int i=head[x];i;i=e[i].next)
	if (e[i].to!=fa[x])fa[e[i].to]=x,solve(e[i].to);
	sta[++top]=x;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfs(1,0);
	for (int v=1;v<=n;v++){
		if (!rt[v]) continue;//rt表示是重心 
		for (int i=head[v];i;i=e[i].next) 
		if (!rt[e[i].to]){
			fa[e[i].to]=v; sta[top=1]=v;
			solve(e[i].to);
			change(v,e[i].to,sta[2]);
			for (int i=2;i<top;i++)if (sta[i+1]!=fa[sta[i]])
			change(sta[i],fa[sta[i]],sta[i+1]);
			for (int i=top-3;i>=1;i--) change(sta[i],sta[i+1],sta[top-1]);
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)printf("%d %d %d\n",ans[i][0],ans[i][1],ans[i][2]);
}
```






---

