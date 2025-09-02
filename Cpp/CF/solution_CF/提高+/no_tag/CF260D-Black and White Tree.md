# Black and White Tree

## 题目描述

给您一棵 $n$ 个节点的树，树边有边权，每个节点都有颜色，且只可能是黑色或白色（用 $0$ 或 $1$ 表示）。原树不存在树边连接 $2$ 个同色的节点。

现给出每个节点的颜色和与这个节点相连的边的权值和，请您还原这棵树。

## 样例 #1

### 输入

```
3
1 3
1 2
0 5
```

### 输出

```
3 1 3
3 2 2
```

## 样例 #2

### 输入

```
6
1 0
0 3
1 8
0 2
0 3
0 0
```

### 输出

```
2 3 3
5 3 3
4 3 2
1 6 0
2 1 0
```

# 题解

## 作者：activeO (赞：3)

## 题目大意

给定 $ n $ 个点，每个点有一个颜色 $ c $，和一个值 $ s $。满足 $ c \in {0,1} $，现在要构造一棵树使得任意直接连接的两个点颜色不相同，且每个与该点相连的边的权值和为 $ s $。

## 思路

首先这是一棵树，所以我们要构造一个没有环的二分图。容易发现如果存在这样一棵树，**白色顶点的权值总和和黑色顶点的权值总和是相等的。**（题目没说存在构造不出来的情况）

考虑贪心构造，先记录下所有黑、白点，每次取出一个黑点和一个白点，记他们分别为 $ u,v $。

这时我们建一条边 $ (u,v) $，权值为 $ \min{s_u,s_v} $，这里假设 $ s_u > s_v $。这时我们令 $ s_u \leftarrow s_u-s_v $，然后删除节点 $ v $（因为此时 $ v $ 的条件已经达成），换一个与 $ v $ 相同颜色的点继续构造。

容易发现：**当我们删除一种颜色的最后一个顶点时，所有其他顶点可以以任何正确的方式与权重为 $ 0 $ 的边连接。** 所以正确性显然。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=1e5+5;
int a[maxn];
vector<int> vec[5];

int main(){
	
	int n;
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int c;
		scanf("%d %d",&c,&a[i]);
		vec[c].push_back(i);
	}
	
	int i=0,j=0;
	
	for(int _=1;_<n;_++){
		int u=vec[0][i],v=vec[1][j];
		int w=min(a[u],a[v]);
		printf("%d %d %d\n",u,v,w);
		a[u]-=w;
		a[v]-=w;
		if((!a[u])&&i<vec[0].size()-1) i++;
		else j++;
	}
	
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：2)

基于贪心构造答案  
把图分为两部分,染黑点的和染白点的。我们一一比较,将一个黑点和一个白点之间连上数值较小的点的权值为权的边,那么权值较小的点得到满足。将权值较大的点的权值减去新连上的边的边权,然后再和下一个不同颜色的点进行比较。这样结束之后,我们将得到一棵树或者一个森林,如果是森林,从两棵树上选择颜色不同的两个点连上0为边权即可。  
正确性证明(~~伪证~~):按上述方法构造的图显然在数值上符合题意。怎么证明没有环？例如,$l_1,l_2$代表两个白点,$r_1,r_2$代表两个黑点。由于$l_1-l_2,r_1-r_2$这样的边是不存在的,所以存在一个简单环,当且仅当选择了边$l_1-r_1,l_1-r_2,l_2-r_1,l_2-r_2$.然后,按照上面的贪心策略,假设我们先选择了边$l_1-r_1$,那么权值较小的点必然得到满足从而不会连出新的边,即若有边$l_1-r_1$,必然不能同时存在边$l_1-r_2$和$l_2-r_1$。对于原图的任意这样四个点都满足这样的性质,所以没有环。
```cpp
#include <iostream>
#include <vector>
#define pb push_back

using namespace std;

const int maxn = 2e5+10;
int w[maxn],col[maxn],fa[maxn],blk[maxn],wt[maxn],tot;
vector<int> v1,v2,id1,id2;

struct edge{
	int u,v,w;
	edge() {}
	edge(int U, int V, int W): u(U), v(V), w(W) {}
}e[maxn];

int gf(int x) { return x==fa[x]?x:fa[x]=gf(fa[x]); }
void mg(int x, int y) { 
	x=gf(x); y=gf(y); fa[x]=y;
	if(!blk[y]) blk[y]=blk[x];
	if(!wt[y]) wt[y]=wt[x];
}

int main() {
	ios::sync_with_stdio(false);
	int n,c,s;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin>>c>>s;
		w[i]=s; col[i]=c;
		fa[i]=i; c?wt[i]=i:blk[i]=i;
		if(c) v1.pb(s), id1.pb(i);
		else v2.pb(s), id2.pb(i);
	}
	int p1=0,p2=0;
	while(p1<v1.size()&&p2<v2.size()) {
		if(v1[p1]==v2[p2]) {
			e[tot++]=edge(id1[p1],id2[p2],v1[p1]);
			mg(id1[p1],id2[p2]); p1++; p2++;
		}else if(v1[p1]<v2[p2]) {
			e[tot++]=edge(id1[p1],id2[p2],v1[p1]);
			v2[p2]-=v1[p1]; mg(id1[p1],id2[p2]); p1++;	
		} else {
			e[tot++]=edge(id1[p1],id2[p2],v2[p2]);
			v1[p1]-=v2[p2]; mg(id1[p1],id2[p2]); p2++;	
		}
	}
	int f=gf(1);
	for(int i=2; i<=n; i++) {
		int t=gf(i);
		if(t!=f) {
			if(blk[t]&&wt[f])
				e[tot++]=edge(blk[t],wt[f],0);
			else
				e[tot++]=edge(wt[t],blk[f],0);
			mg(t,f);
		}
	}
	for(int i=0; i<tot; i++) cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].w<<endl;
	return 0;
}
```

---

