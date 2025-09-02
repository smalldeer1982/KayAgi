# Om Nom and Dark Park

## 题目描述

Om Nom is the main character of a game "Cut the Rope". He is a bright little monster who likes visiting friends living at the other side of the park. However the dark old parks can scare even somebody as fearless as Om Nom, so he asks you to help him.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/131af3f0d0c50854dd04093b7cc403fcf25a1e8b.png)The park consists of $ 2^{n+1}-1 $ squares connected by roads so that the scheme of the park is a full binary tree of depth $ n $ . More formally, the entrance to the park is located at the square $ 1 $ . The exits out of the park are located at squares $ 2^{n},2^{n}+1,...,2^{n+1}-1 $ and these exits lead straight to the Om Nom friends' houses. From each square $ i $ ( $ 2<=i<2^{n+1} $ ) there is a road to the square ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/1a134f5ff0a48756afece69eeb883c670c5ab534.png). Thus, it is possible to go from the park entrance to each of the exits by walking along exactly $ n $ roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/f5acd0d816020c5e5a5f00b96e0b0428cadec703.png) To light the path roads in the evening, the park keeper installed street lights along each road. The road that leads from square $ i $ to square ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/1a134f5ff0a48756afece69eeb883c670c5ab534.png) has $ a_{i} $ lights.Om Nom loves counting lights on the way to his friend. Om Nom is afraid of spiders who live in the park, so he doesn't like to walk along roads that are not enough lit. What he wants is that the way to any of his friends should have in total the same number of lights. That will make him feel safe.

He asked you to help him install additional lights. Determine what minimum number of lights it is needed to additionally place on the park roads so that a path from the entrance to any exit of the park contains the same number of street lights. You may add an arbitrary number of street lights to each of the roads.

## 说明/提示

Picture for the sample test. Green color denotes the additional street lights.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/a991902237b78dc527346d24d4ba436bdc2cc2af.png)

## 样例 #1

### 输入

```
2
1 2 3 4 5 6
```

### 输出

```
5
```

# 题解

## 作者：Priori_Incantatem (赞：4)

### 题目大意
给出一个有 $2^{n+1}-1$ 个节点的满二叉树，边带权  
要求让一些边的边权增加，使得所有叶子节点到跟的路径上的边权之和相等。并让增加的权值最小

### 解题思路
这里讲一个非常贪心的做法

首先，我们找出离根节点最远的叶子节点，并算出他的距。在以后的计算中将不会在该路径上增加边权（不然会出现浪费）

接着，再使用 dfs 求出每个叶子节点到根的路径上，还需要加多少权值，我们用 $dis[]$ 表示

对于非叶子节点的 $dis[]$，我们用来维护以该节点为根的子树中所有叶子节点的 $dis[]$ 最小值

```cpp
void dfs1(int x,int cur)
{
	tot=max(tot,cur); // tot 维护离根节点最远的点的距离
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i].v;
		dfs1(y,cur+e[x][i].len);
	}
}
void dfs2(int x,int cur) // 求出所有叶子和非叶子节点的 dis[]
{
	if(!e[x].size())
	{
		dis[x]=tot-cur; // 注意：叶子节点的 dis 储存的是还需要加多少边权
		return;
	}
	dis[x]=inf;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i].v;
		dfs2(y,cur+e[x][i].len);
		dis[x]=min(dis[x],dis[y]);
	}
}
```

然后，我们开始给边加权：

由于题目要求总共增加的权值最小，我们就要然加上的边权利用率最大  
显然，边权加在离跟越近的地方，就可以让更多叶子节点收益，也就利用率越大。所以我们要尽可能地在离根近的地方给边加权

```cpp
void dfs(int x,int cur) // cur 储存上方跟该子树有关的边已经加了多少权
{
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i].v;
		ans+=dis[y]-cur; // 上方已经加了 cur 的权，所以要减掉
		dfs(y,dis[y]);
	}
}
```

再给边加权是，要考虑到下方子树的所有叶子节点，不能加多（只能加上叶子节点中最小的 $dis[]$）。这时，非叶子节点的 $dis[]$ 就派上用场了

**完整代码**

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
const int Maxn=2100,inf=0x3f3f3f3f;
struct edge{
	int v,len;
	edge(int x,int y)
	{
		v=x,len=y;
	}
};
int dis[Maxn];
vector <edge> e[Maxn];
int n,m,tot,ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void dfs1(int x,int cur)
{
	tot=max(tot,cur);
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i].v;
		dfs1(y,cur+e[x][i].len);
	}
}
void dfs2(int x,int cur)
{
	if(!e[x].size())
	{
		dis[x]=tot-cur;
		return;
	}
	dis[x]=inf;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i].v;
		dfs2(y,cur+e[x][i].len);
		dis[x]=min(dis[x],dis[y]);
	}
}
void dfs(int x,int cur)
{
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i].v;
		ans+=dis[y]-cur;
		dfs(y,dis[y]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	m=read()+1,n=(1<<m)-1;
	
	for(int i=2;i<=n;++i)
	{
		int x=(i>>1),y=i,c=read();
		e[x].push_back(edge(y,c));
	}
	
	dfs1(1,0);
	dfs2(1,0);
	dfs(1,0);
	
	printf("%d\n",ans);
	
	return 0;
}
```

对题解有疑问的可以私信我，我经常在线

---

## 作者：rzm120412 (赞：1)

由题意最多有 $(2^{n+1}-2)$ 个数,我们把根节点当做第一个节点。
就可以容易得到一个点 $(i)$ 的左子节点和右子节点的位置，即 $2i$ 和 $(2i+1)$。而左子节点和右子节点的价值就是他本身的价值加他的子树的价值，夫节点的价值就是左子节点和右子节点的差的绝对值。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[114514],ans;
int dfs(int i){
	if(i>sum){//搜完了 
		return 0;
	}
	int l=dfs(i*2)+a[i*2];//左子树的价值 
	int r=dfs(i*2+1)+a[i*2+1];//右子树的价值 
	ans+=max(l,r)-min(l,r);
	return max(l,r);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    cin>>n;
    int sum=1;
    for(int i=1;i<=n+1;i++){
    	sum*=2;//只有2^(n+1)-2个节点 
	}
    for(int i=2;i<=sum-1;i++){
    	cin>>a[i];
	}
	dfs(1);//根开始搜 
	cout<<ans;
	return 0;
}
```

---

## 作者：q779 (赞：1)

# CF526B Om Nom and Dark Park

题目链接：[CF526B Om Nom and Dark Park](https://www.luogu.com.cn/problem/CF526B)

> **题意**：给定 $2^{n+1}-1$ 个结点的满二叉树，求保证根到每一个叶子节点的路径权值和相等的情况下，增加权值的最小值

显然不能从根节点开始修改权值，不然也不知道改成什么才行

因此主要思路是**从叶子结点向上修改权值**，直到根结点为止

方便起见，用 ```a[x]``` 表示结点 $x$ 到它的父结点的那条边的权值

下文中提到的路径长指一个结点到它叶子结点的最终的距离

可以发现，对于一个待修改结点 $x$ ，假设我们已经知道了它的左右子结点的路径长```ls,rs```（已经被修改了的路径长，因为是从叶子结点向上修改的）

则结点 $x$ 到左子结点修改前的路径长为```a[2*x]+ls```，同理右子结点```a[2*x+1]+rs```

保证根到叶子节点路径权值和相等，因此要把上面这两个路径长中较小的那个补成较大的那个，这样花费肯定是最小的，又保证了以这个结点为根的子树满足题目要求

于是从下往上传递，过程中统计答案

时间复杂度 $O(2^n)$

主要代码很短

```cpp
#define MAXN (int)(2e6+5)
int n,ans,a[MAXN],MX;
int dfs(int x)
{
	if(x>MX)return 0;
	int ls=dfs(x<<1),rs=dfs(x<<1|1);
	ans+=abs(ls+a[x<<1]-rs-a[x<<1|1]); // 每次修改的花费
	return max(a[x<<1]+ls,a[x<<1|1]+rs);
}
signed main()
{
	read(n);MX=(1<<(n+1))-1;
	for(int i=2; i<=MX; i++)
		read(a[i]);
	dfs(1);write(ans);
	return 0;
}
```



---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF526B)

以下称节点 $i$ 连向其父亲的边为节点 $i$ 的对应边，节点 $1$（根）没有对应边。

首先可以计算出从根到每个叶子的权值 $dis_i$，可以通过满二叉树的性质来方便地求出 $dis_i = dis_{\lfloor i/2 \rfloor} + w_i$，其中 $w_i$ 表示 $i$ 的对应边的权值。

然后，先考虑让每两个相邻叶子节点的 $dis$ 相同。设现在修改的节点是 $i$ 和 $i + 1$，$i$ 是偶数。

因为如果修改除了 $i$ 和 $i + 1$ 的对应边外的边，$dis_i$ 和 $dis_{i+1}$ 的差是不会变的，所以直接修改 $i$ 或 $i+1$ 的对应边的权值，使答案加上 $|dis_i - dis_{i+1}|$。边的权值可以直接在 $dis$ 上修改。

现在 $i$ 和 $i + 1$ 的 $dis$ 相等了，我们以后也不会再修改他们对应边的权值了，所以把 $i$ 和 $i+1$ 看作一个整体，编号为 $i$。

考虑完每两个节点后，要让每相邻四个节点 $dis$ 相等。因为执行完上一步操作后每两个相邻节点合并了，所以只需要比较 $i$ 和 $i+2$ 的 $dis$。注意此时其实修改的是 $i/2$ 和 $i/2+1$ 的对应边的权值。

接下来是每 $8$ 个节点、$16$ 个节点，直到 $2^n$ 个节点，即全部叶子节点 $dis$ 相等。

最后输出过程中记录的答案即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k, dis[5001], pow2[15], ans;
signed main(){
	pow2[0] = 1;
	for (int i = 1; i < 15; i++) pow2[i] = pow2[i - 1] * 2;//预处理2^n
	scanf("%lld", &n); m = pow2[n + 1] - 1;
	for (int i = 2; i <= m; i++){scanf("%lld", &dis[i]); dis[i] += dis[i / 2];}//dis_i=dis_i/2+w_i
	for (int i = 1; i <= n; i++){
		for (int j = pow2[n]; j <= pow2[n + 1] - 1; j += pow2[i]){
			ans += abs(dis[j] - dis[j + pow2[i - 1]]);//记录答案
			dis[j] = max(dis[j], dis[j + pow2[i - 1]]);
			dis[j + pow2[i - 1]] = max(dis[j], dis[j + pow2[i - 1]]);//直接修改权值
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Hooch (赞：0)

### 题目大意

某某公园有 $2^{n+1}-1$ 个正方形，每个正方形往下有 $2$ 条路分别连接着 $2$ 个正方形，公园一共有 $n$ 层（第一层层数为 $0$），正方形编号分别为 $1,2,3,\cdots,2^{n+1}-1$。也就是说，公园是一棵最大深度为 $n$ 的**满二叉树**。

为了能在夜晚看得清路，公园管理员会放置一些路灯在每一条路上，每一条路上的路灯数量可能不同。

Om Nom 在晚上会路过这个公园，他要从深度为 $0$ 的正方形走到深度为 $n$ 的正方形，也就是**从根节点走到叶子节点**。他非常怕黑，所以他想让从根节点到每一个叶子节点中遇到的路灯数量相等。公园管理员被整不会了，求助你，让你求出最少要多修几个路灯。

### 思路

题目很长，但转化过来就是：一棵深度为 $n$ 的满二叉树，每条有边权，让某些边权增加，使得根节点到叶子节点的路径边权和相等，让增加的最少。

我们发现从根节点开始**从上到下**修改边权很难决定增加几，于是我们递归，**从下到上**开始修改边权。

我们看这种情况：

```
    1
 3 / \ 4
  2   3
```

这就是一颗简单的满二叉树，我们发现要求两个路径边权和相等，就要让边权小的增加（边权小指的是相比于另一个儿子节点与父节点的边权小，比如在上述的图中，$1\to 2$ 的边算是边权小的边）。

然后再举一个例子：

```
       1
     1/ \2
     /   \
    2     3
  3/ \4 5/ \ 6
  /   \ /   \
 4    5 6    7
```

我们要用递归处理，处理节点 $2$ 和 $3$ 的子问题。

现在变成了：

```
       1
     1/ \2
     /   \
    2     3
  4/ \4 6/ \ 6
  /   \ /   \
 4    5 6    7
```

可是这个时候，我们发现不能像上次一样处理，因为现在如果统一左右儿子与父结点边权，结果仍然不对，因为节点 $2$ 与子节点的边权与节点 $3$ 与子节点的边权不相等。

那么这时我们增加节点 $1$ 到节点 $2$ 的边权即可。

而其余深度的节点处理仍是相同。

### 代码

很短。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int M = 12, N = 1 << M;
int n, m, a[N], ans;
inline int dfs(int d, int x) {
	if (d > m) return 0; //不在二叉树中
	int lson = dfs(d + 1, x << 1), rson = dfs(d + 1, x << 1 | 1);
    //左右儿子的边权和
	ans += abs((lson - rson) + (a[x << 1] - a[x << 1 | 1]));
    //更新答案
	return max(lson + a[x << 1], rson + a[x << 1 | 1]);
}
signed main(void) {
	cin >> m; ++m; n = (1 << m) - 1; //n 为节点个数
	for (int i = 2; i <= n; ++i) cin >> a[i];
	dfs(1, 1);
	cout << ans;
}
```

---

