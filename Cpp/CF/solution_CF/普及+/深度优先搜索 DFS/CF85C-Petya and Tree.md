# Petya and Tree

## 题目描述

给定一棵二叉搜索树，包含 $n$ 个节点，保证每个节点只可能有 $0$ 或 $2$ 个子节点。

再给定 $k$ 次询问，每次询问给出一个值   $x_i$ ，
对于第 $i$ 次询问，将 $x_i$ 插入树中，在插入过程中会等概率的“走错”（即在到达某个点时如果该往左子树走，则该往右子树走，反之亦然）恰好一次，输出该节点插入后的父节点的权值的期望值。（询问之间相互独立，即不会真正插进去）

tips：

二叉搜索树的定义：如果一棵二叉树满足其任意一节点中，左子树的所有点的权值均小于该点权值且右子树的所有点的权值均大于该点权值（忽略空子树），则这棵树被称为二叉搜索树。

二叉搜索树的插入操作：最初位于树根，如果当前节点的权值大于要插入的节点的权值，那么移动到该节点的右子节点，否则移动到该节点的左子节点并重复该过程直到该节点为空。

## 样例 #1

### 输入

```
7
-1 8
1 4
1 12
2 2
2 6
3 10
3 14
1
1
```

### 输出

```
8.0000000000
```

## 样例 #2

### 输入

```
3
-1 5
1 3
1 7
6
1
2
4
6
8
9
```

### 输出

```
7.0000000000
7.0000000000
7.0000000000
3.0000000000
3.0000000000
3.0000000000
```

# 题解

## 作者：Resolute_Faith (赞：2)

### 题目大意

给定一棵二叉搜索树，有 $k$ 次询问，每次询问一个数 $x$，问在搜索 $x$ 的时候只走错一条边的所有路径搜索到的数的期望。

### 题解

首先暴力把每一条边都走出来算出答案肯定是不行的，假设 $x$ 在某一个节点的左子树上，如果我因为走错而走到右子树上，那我肯定会尽力往左走（根据二叉搜索树性质可得）。换句话说，**走错一条边后，一定是一直往另一边靠拢的，方向不会改变**。

于是我们设 $L_i$ 和 $R_i$ 表示第 $i$ 个节点一直往左或往右走搜到的值，这是可以 $\mathcal{O}(n)$ 处理的。但我们如果想要求出答案，就必须把到 $x$ 的正确路径走一遍，时间复杂度最高可以达到 $\mathcal{O}(kn)$，对于链的情况会被卡掉。

考虑如何直接求出答案，我们设 $dp_{i}$ 表示到达第 $i$ 个节点走错的总值（我只是给他取名叫 $dp$，实际上这不是一个 $dp$），有转移如下：

$$
dp_i=dp_{fa}+p
$$

其中 $p$ 的意思是，如果 $i$ 是 $fa$ 的左儿子，则 $p$ 为 $fa$ 的右儿子的 $L$ 值，$i$ 是 $fa$ 的右儿子同理。（左儿子和右儿子也是可以 $\mathcal{O}(n)$ 处理的）。这个时候如果我们要求出某一点的期望，只需要求出对于节点 $i$ 的错误路径个数即可，也可以 $\mathcal{O}(n)$ 处理。

即使求出了 $dp_i$ 的值，我们仍然需要知道对于询问的 $x$，他到底归属于哪个节点。这里有两种方法，一种可以用平衡树的方法重构这一棵树，另一种可以直接**拍扁二分求值**，选择第二种比较方便。但是当我们二分出 $x$ 的前驱和后继时，如何才能判断它属于左边节点还是右边节点呢？经过思考可以发现 $x$ 总是会到达深度更深的点，也就是**前驱和后继谁的深度更深就归谁**，深度 $\mathcal{O}(n)$ 处理。

至此我们已经可以求出询问的值了，时间复杂度是 $\mathcal{O}(k\log n)$。

### 细节

1. **题目没说根是哪个，自己找**。
2. 二分的值超过一定范围它会返回一个很奇怪的数，至于什么原因我也不是很清楚，自己测试可以打一些权值为 $10^9$ 的点进去。
3. 拍扁最好用 `vector`，同时存储值和点编号。
4. 根节点的错误路径数应当为 $1$，你也可以特判解决这个问题。

### 代码

关于变量的意义：

- $L,R$：表示一直往左或往右走取到的值；
- $dp$：表示走到这个节点的所有错误路径终点的数的和
- $row$：表示走到这个节点的错误路径数；
- $dep$：表示深度；
- $f$：拍扁后的树；

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,q,head[N],cnt,val[N],L[N],R[N],dp[N],row[N],dep[N],root;
struct edge{int to,nxt;}a[N]; 
struct tree{int l,r;}tr[N];
vector<pair<int,int> > f;
void add(int x,int y){
	a[++cnt].to=y;
	a[cnt].nxt=head[x];
	head[x]=cnt;
}
void dfs1(int x,int fa){
	dep[x]=dep[fa]+1;
	int s=0;
	L[x]=R[x]=val[x];
	for(register int i=head[x];i;i=a[i].nxt){
		int y=a[i].to;
		if(y==fa) continue;
		dfs1(y,x);
		if(val[y]<val[x]) L[x]=L[y],tr[x].l=y;
		else R[x]=R[y],tr[x].r=y;//根据权值判断左右儿子 
	}
}
void dfs2(int x,int fa){
	if(fa!=-1){
		if(x==tr[fa].l){
			dp[x]=dp[fa]+L[tr[fa].r]; 
			row[x]=row[fa]+(tr[fa].r!=0);//求出错误路径数 
		}
		if(x==tr[fa].r){
			dp[x]=dp[fa]+R[tr[fa].l];
			row[x]=row[fa]+(tr[fa].l!=0);
		}
	}else dp[root]=0;
	for(register int i=head[x];i;i=a[i].nxt){
		int y=a[i].to;
		if(y==fa) continue;
		dfs2(y,x);
	}
}
void dfs3(int x,int fa){//中序遍历拍扁 
	if(tr[x].l!=0) dfs3(tr[x].l,x);
	f.push_back(make_pair(val[x],x));
	if(tr[x].r!=0) dfs3(tr[x].r,x);
}
signed main(){
	scanf("%lld",&n);
	for(register int i=1,x,y;i<=n;i++){
		scanf("%lld %lld",&x,&y);
		if(x!=-1) add(x,i);
		else root=i;
		val[i]=y;
	}
	dfs1(root,-1),dfs2(root,-1),dfs3(root,-1);
	f.push_back(make_pair(-1,0ll));
	sort(f.begin(),f.end());
	row[root]=1;
	scanf("%lld",&q);
	while(q--){
		int x;
		scanf("%lld",&x);
		vector<pair<int,int> >::iterator p=lower_bound(f.begin(),f.end(),make_pair(x,0ll));
		int e=f[f.size()-1ll].second;
		if(x>f[f.size()-1ll].first) printf("%.11lf\n",dp[e]*1.0/row[e]); 
		else if(p==f.begin()) printf("%.11lf\n",dp[root]*1.0/row[root]);
		else if(p==f.end()) printf("%.11lf\n",dp[e]*1.0/row[e]);
		else{
			vector<pair<int,int> >::iterator q=p-1;
			int x1=(*p).second;
			int y1=(*q).second;
			if(dep[y1]>dep[x1]) printf("%.11lf\n",dp[y1]*1.0/row[y1]);//选择深度更深的点 
			else printf("%.11lf\n",dp[x1]*1.0/row[x1]);
		}
	}
}
```

---

