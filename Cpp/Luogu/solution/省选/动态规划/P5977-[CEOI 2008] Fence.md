# [CEOI 2008] Fence

## 题目描述

在一个大小为 $1000\times 1000$ 的区域中，有 $n$ 个固定点, $m$ 棵树 。

现在你要建一个围栏来保护树，建它的费用为你选用的固定点的个数 $\times 20$ +你没有圈进围栏的树 $\times 111$。

现在希望这个值越小越好，求最小值。

## 说明/提示

对于 $100\%$ 的数据，$3\le N,M\le 100$。

----

## 样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/7vebu0t2.png)

## 样例 #1

### 输入

```
4 3
800 300
200 200
200 700
600 700
400 300
600 500
800 900```

### 输出

```
171```

# 题解

## 作者：chlchl (赞：9)

纪念一下，调了整整两周。

本题题意非常清晰，故不提供题意简述。

## Solution
注意到 $20\times 4<111$，所以即使花 $4$ 个点包住一棵树也是值的。所以我们考虑包住最多的树，这样一定是最优的。

所以我们对所有点求个凸包，然后对于每一棵树，如果它凸包所有边的同一侧，则它一定在凸包内，拿一个东西存下所有的树。

但是这样不一定是最优的，有一些点可能是无用的，删去之后仍然可以包住所有树。

我们考虑一个算法：对于凸包上的每相邻两条边（设为 $\overrightarrow{AB},\overrightarrow{BC}$），我都枚举一次。如果这个三角形内部并没有树，那么我们就删掉 $B$ 这个点。

这样复杂度非常优秀，达到了 $O(nm)$。

但是很遗憾，正确性是错的。为什么呢？请看下面这个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p0blpts4.png?x-oss-process=image/resize,m_lfit,h_400,w_500)

最优的选择是保留 $A,C,D$。但是，如果我们从 $B$ 开始扫，你会发现 $\triangle ABE$ 里根本就没有树，所以一开始就把 $A$ 干掉了，怎么弄都得不到最优解。

看到 $n,m\leq 100$，那我们就考虑一个暴力一些的算法。

先有一个结论：如果所有树出现在一个向量的同一侧，那么这个向量是有可能出现在最后的凸包内的。

所以我们暴力枚举任意两个点构成向量，如果合法我们就将这条边的边权赋为 $1$，否则设为正无穷。

然后就是一个 Floyd 求最小环问题了，时间复杂度 $O(n\log n+n^2m+n^3)$，对于 $n,m\leq 100$ 的数据是非常松的。

当然，上面那个错误的做法，如果你对每个点都开始跑一遍，大概率是能得到最优解的，但是估计还是能 hack，这个我不太清楚，有点菜 qwq。

最后是一些阻碍了我很久的坑点：
- 最后的点不一定全是在一开始求的凸包内，所以建图的时候不能只枚举凸包上的点而不枚举凸包内部的点；
- 建图不要建双向边，因为向量带方向，反过来是不对的；
- 如果你 94 分，请注意一个问题：如果所有树都不在凸包内，最小代价显然是不选点，直接输出 $111\times m$。但是我们的 Floyd 是**不允许不选点**的，它会跑出来**选两个点构成一个环**。所以这种情况需要特判。

```cpp
#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const int N = 100 + 10;
int n, m, idx = -1, hd;
int g[N][N];
struct node{
	double x, y;
} p[N], tree[N];
node st[N];
vector<int> inside;

double getcro(node oo, node pp, node qq){
	return (pp.x - oo.x) * (qq.y - oo.y) - (qq.x - oo.x) * (pp.y - oo.y);
}

double dis(node pp, node qq){
	return sqrt((pp.x - qq.x) * (pp.x - qq.x) + (pp.y - qq.y) * (pp.y - qq.y));
}

bool cmp(node a, node b){
	double now = getcro(p[1], a, b);//叉积求面积 
	if(now < 0 || (now == 0 && dis(p[1], a) < dis(p[1], b)))
		return 1;
	return 0;
}

bool isleft(node u, node s, node t){
	double f = getcro(u, s, t);
	return f >= eps;
}

bool possible(node u, node v){
	for(int i=0;i<inside.size();i++){
		node pp = tree[inside[i]];
		if(!isleft(pp, v, u))
			return 0;
	}
	return 1;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf", &p[i].x, &p[i].y);
		if(idx == -1 || p[i].y < p[idx].y)
			idx = i;
	}
	for(int i=1;i<=m;i++)
		scanf("%lf%lf", &tree[i].x, &tree[i].y);
	swap(p[1], p[idx]);
	sort(p + 2, p + 1 + n, cmp);
	st[++hd] = p[1];
	for(int i=2;i<=n;i++){
		while(hd > 1 && !isleft(st[hd - 1], p[i], st[hd]))
			--hd;
		st[++hd] = p[i];
	}
	int cnt = 0, ans = 1e9;
	st[++hd] = p[1];
	for(int i=1;i<=m;i++){
		bool f = 1;
		for(int j=hd;j>1;j--){
			if(!isleft(st[j - 1], tree[i], st[j])){
				f = 0;
				break;
			}
		}
		if(f)
			inside.push_back(i), ++cnt;
	}
	if(!cnt)
		return printf("%d\n", m * 111), 0; 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			node u = p[i], v = p[j];
			if(i != j && possible(u, v))
				g[i][j] = 1;
			else
				g[i][j] = 1e9;
		}
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	for(int i=1;i<=n;i++)
		ans = min(ans, g[i][i]);
	printf("%d\n", (m - cnt) * 111 + ans * 20);
	return 0;
}
```


---

