# Ice cream coloring

## 题目描述

Isart and Modsart were trying to solve an interesting problem when suddenly Kasra arrived. Breathless, he asked: "Can you solve a problem I'm stuck at all day?"

We have a tree $ T $ with $ n $ vertices and $ m $ types of ice cream numerated from $ 1 $ to $ m $ . Each vertex $ i $ has a set of $ s_{i} $ types of ice cream. Vertices which have the $ i $ -th ( $ 1<=i<=m $ ) type of ice cream form a connected subgraph. We build a new graph $ G $ with $ m $ vertices. We put an edge between the $ v $ -th and the $ u $ -th ( $ 1<=u,v<=m $ , $ u≠v $ ) vertices in $ G $ if and only if there exists a vertex in $ T $ that has both the $ v $ -th and the $ u $ -th types of ice cream in its set. The problem is to paint the vertices of $ G $ with minimum possible number of colors in a way that no adjacent vertices have the same color.

Please note that we consider that empty set of vertices form a connected subgraph in this problem.

As usual, Modsart don't like to abandon the previous problem, so Isart wants you to solve the new problem.

## 说明/提示

In the first example the first type of ice cream is present in the first vertex only, so we can color it in any color. The second and the third ice cream are both presented in the second vertex, so we should paint them in different colors.

In the second example the colors of the second, the fourth and the fifth ice cream should obviously be distinct.

## 样例 #1

### 输入

```
3 3
1 1
2 2 3
1 2
1 2
2 3
```

### 输出

```
2
1 1 2 ```

## 样例 #2

### 输入

```
4 5
0
1 1
1 3
3 2 4 5
2 1
3 2
4 3
```

### 输出

```
3
1 1 1 2 3 ```

# 题解

## 作者：chufuzhe (赞：2)

第 $1$ 步，输入，然后建树。

第 $2$ 步，$dfs$ ，把每个节点染色。第一个点开始，找到和这个节点有相同冰激凌的节点继续拓展，染的颜色就是没有出现过且编号最小的颜色，同样的冰激凌染的颜色也一样。

第 $3$ 步，输出，颜色种类数就是 $max(s_i)$ 。然后输出每个节点的颜色，如果没有就输出 $1$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() //快读
{
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void write(int x) //快出
{
    if(x<0)
	{
    	putchar('-');
		x=-x;
	}
    if(x>9)
		write(x/10);
    putchar(x%10+'0');
}
vector<int> a[300005]; //定义
vector<int> b[300005];
map<int, int> v;
int c[300005];
void dfs(int x, int y) { //染色
	v.clear();
	for(int i = 0; i < a[x].size(); i++){
		if(c[a[x][i]]){ //前面染过同样的冰激凌
			v[c[a[x][i]]] = 1;
		}
	}
	int l = 0;
	for(int i = 0; i < a[x].size(); i++){
		if(!c[a[x][i]]){
			while(1){ //找没有出现过且编号最小的颜色
				if(!v[++l]){
					break;
				}
			}
			c[a[x][i]] = l; //染色
		}
	}
    for(int i = 0; i < b[x].size(); i++)
        if(b[x][i] != y)
        	dfs(b[x][i], x); //继续拓展
    return ;
}
int main() {
	int n, m, s = 1; //s表示颜色种类数
	n = read(); //输入
	m = read();
	for(int i = 1; i <= n; i++){
		int x;
		x = read();
		s = max(s, x);
		for(int j = 1; j <= x; j++){
			a[i].push_back(read());
		}
	}
	for(int i = 1; i < n; i++){
		int x, y;
		x = read();
		y = read();
		b[x].push_back(y);
		b[y].push_back(x);
	}
   dfs(1, -1); //染色
   write(s); //输出
   puts("");
	for(int i = 1; i <= m; i++){
		write(c[i] == 0 ? 1 : c[i]);
		putchar(' ');
	}
	puts("");
	return 0;
} 
```


---

## 作者：Miracle_1024 (赞：1)

### 思路：

首先因该考虑最多需要多少中颜色，然后再考虑怎么染色。对于一种冰激凌，如果确定了其染什么颜色，那么在后面其他顶点中遇到这中冰激凌也直接染成这种颜色即可。

对于一种在其它顶点中用过的颜色，若在当前顶点中没有用过，那么可以将当前顶点中某个冰激凌染成这种颜色。 显然， 限制所需颜色种数的条件为 $\max (k_i)$， 并且最少需要的颜色种数即为：$\max (k_i)$。 至于具体染色方案只需   dfs 一遍即可。dfs 过程为： 在当前顶点中, 对于之前染过色的冰激凌， 先给它染上同种颜色， 对于剩下的冰激凌， 依次选取当前最小的且当前顶点中没用过的颜色染上即可。

### 代码：
```
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 10;
vector<int> vt1[MAXN], vt2[MAXN];
map<int, int> vis;
int sol[MAXN];
void dfs(int x, int pre){
    vis.clear();
    for(int i = 0; i < vt1[x].size(); i++){
        if(sol[vt1[x][i]]) vis[sol[vt1[x][i]]] = 1;
    }
    int cnt = 0;
    for(int i = 0; i < vt1[x].size(); i++){
        if(sol[vt1[x][i]]) continue;
        while(vis[++cnt]){};
        sol[vt1[x][i]] = cnt;
    }
    for(int i = 0; i < vt2[x].size(); i++){
        if(vt2[x][i] != pre) dfs(vt2[x][i], x);
    }
}
int main(){
    int n, m, k, x, y, ans = 1;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &k);
        if(ans < k) ans = k;
        while(k--){
            scanf("%d", &x);
            vt1[i].push_back(x);
        }
    }
    for(int i = 1; i < n; i++){
        scanf("%d%d", &x, &y);
        vt2[x].push_back(y);
        vt2[y].push_back(x);
    }
    dfs(1, -1);
    printf("%d\n", ans);
    for(int i  = 1; i <= m; i++){
        if(sol[i]) printf("%d ", sol[i]);
        else printf("1 ");
    }
    puts("");
    return 0;
}
```


---

