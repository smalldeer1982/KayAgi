# [ABC270C] Simple path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc270/tasks/abc270_c

$ N $ 頂点の木 $ T $ があり、 $ i $ $ (1\leq\ i\leq\ N-1) $ 番目の辺は頂点 $ U_i $ と頂点 $ V_i $ を結んでいます。

$ T $ 上の相異なる $ 2 $ 頂点 $ X,Y $ が与えられるので、 頂点 $ X $ から頂点 $ Y $ への単純パス上の頂点（端点含む）を順に列挙してください。

ただし、木上の任意の相異なる $ 2 $ 頂点 $ a,b $ について、$ a $ から $ b $ への単純パスがただ一つ存在することが証明できます。

単純パスとは？グラフ $ G $ 上の頂点 $ X,Y $ に対して、頂点列 $ v_1,v_2,\ \ldots,\ v_k $ であって、 $ v_1=X $, $ v_k=Y $ かつ、$ 1\leq\ i\leq\ k-1 $ に対して $ v_i $ と $ v_{i+1} $ が辺で結ばれているようなものを頂点 $ X $ から頂点 $ Y $ への **パス** と呼びます。 さらに、$ v_1,v_2,\ \ldots,\ v_k $ がすべて異なるようなものを頂点 $ X $ から頂点 $ Y $ への **単純パス** と呼びます。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ X,Y\leq\ N $
- $ X\neq\ Y $
- $ 1\leq\ U_i,V_i\leq\ N $
- 入力はすべて整数
- 与えられるグラフは木

### Sample Explanation 1

木 $ T $ は以下のような形であり、頂点 $ 2 $ から頂点 $ 5 $への単純パスは 頂点 $ 2 $ $ \to $ 頂点 $ 1 $ $ \to $ 頂点 $ 3 $ $ \to $ 頂点 $ 5 $ となります。 よって、$ 2,1,3,5 $ をこの順に空白区切りで出力します。 !\[\](https://img.atcoder.jp/abc270/4f4278d90219acdbf32e838353b7a55a.png)

### Sample Explanation 2

木 $ T $ は以下のような形です。 !\[\](https://img.atcoder.jp/abc270/3766cc7963f74e28fa0de6ff660b1998.png)

## 样例 #1

### 输入

```
5 2 5
1 2
1 3
3 4
3 5```

### 输出

```
2 1 3 5```

## 样例 #2

### 输入

```
6 1 2
3 1
2 5
1 2
4 1
2 6```

### 输出

```
1 2```

# 题解

## 作者：SuperCowHorse (赞：1)

### 题目大意
求树上两点简单路径。
### 题目分析
由于数据范围较小，可以采用 dfs 深搜暴力。

从起点开始，对每个邻接点进行访问，直到到终点，输出答案即可。

在这里使用了链式前向星存图，可能快一些。

Code:
``` cpp
//chenye3
#include<bits/stdc++.h>
#define ll long long
#define do double
using namespace std;
int n,x,y;
const int maxn=2e5+5;
struct edge{
	int v,next;
}e[maxn<<1];int head[maxn],cnt;
int ans[maxn],tot;
void add(int u,int v){
	e[++cnt]=(edge){v,head[u]};
	head[u]=cnt;
}
void dfs(int u,int fa){
	if(u==y){
		for(int i=1;i<tot;++i)
			printf("%d ",ans[i]);
		printf("%d",ans[tot]);
		exit(0);//结束
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa) continue;
		ans[++tot]=v;//统计
		dfs(v,u);
		ans[tot--]=0;
	}
}
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1,u,v;i<n;++i){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);//建图
	}
	ans[++tot]=x;
	dfs(x,0);
	return 0;
}
```

---

