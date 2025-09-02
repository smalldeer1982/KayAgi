# ULM09 - Dark roads

## 题目描述

Economic times these days are tough, even in Byteland. To reduce the operating costs, the government of Byteland has decided to optimize the road lighting. Till now every road was illuminated all night long, which costs 1 Bytelandian Dollar per meter and day. To save money, they decided to no longer illuminate every road, but to switch off the road lighting of some streets. To make sure that the inhabitants of Byteland still feel safe, they want to optimize the lighting in such a way, that after darkening some streets at night, there will still be at least one illuminated path from every junction in Byteland to every other junction.

What is the maximum daily amount of money the government of Byteland can save, without making their inhabitants feel unsafe?

#### Input Specification

The input file contains several test cases. Each test case starts with two numbers **_m_** and **_n_**, the number of junctions in Byteland and the number of roads in Byteland, respectively. Input is terminated by **_m=n=0_**. Otherwise, **_1_**  and **_m-1_** . Then follow **_n_** integer triples **_x, y, z_** specifying that there will be a bidirectional road between **_x_** and **_y_** with length **_z_** meters (0  and **_x ≠ y_**). The graph specified by each test case is connected. The total length of all roads in each test case is less than 2 $ ^{31} $ .

#### Output Specification

For each test case print one line containing the maximum daily amount the government can save.

#### Sample Input

 ```
7 11
0 1 7
0 3 5
1 2 8
1 3 9
1 4 7
2 4 5
3 4 15
3 5 6
4 5 8
4 6 9
5 6 11
0 0
```
#### Sample Output

51

# 题解

## 作者：szkzyc (赞：2)

这题很显然啊，是最小生成树的板子题。

就是让你求一个图中删去几条边后剩下的边权和最小，且必须连通，输出这个最小值。也就是在普通的最小生成树下统计总边权和再减去最小边权和就行了。

看了一眼题解：嘿，全是 Kruskal，我大 Prim 什么时候才能站起来！！！（貌似但凡是最小生成树的题绝大部分人都喜欢用 Kruskal）

咳咳，言归正传，现在让我们来介绍一下：

### 最小生成树算法——Prim 算法

这个算法跟 Kruskal 算法一样核心都是贪心，思想就是在这个图上取任意一个点当做出发点，然后枚举所有与他相连的边，取这几条边的最小值然后再连边。可以证明，当连边的数量正好为 $n-1$ 的时候是最优解。所以只要连了 $n-1$ 条边就可以退出遍历。不同与 Kruskal 的是，Prim 算法不用判环。

此算法我选择的是使用链式前向星存图，由于重点是算法，我便不再细讲。不知道的同学可以上网搜索一下相关的知识。

```cpp
#include<bits/stdc++.h> //万能头文件 
#define ll long long
#define INF INT_MAX  //INF表示无限，指一个极大值。INT_MAX是一个表示int范围内最大值的常量。 

using namespace std;
const int M = 3005;
const int N = 2005;
int n, m, tot, ans, sum;
int head[N], dist[N], vis[N]; 
struct node{ //链式前向星存图 
	int to, next;
	int w;
}edge[M << 1]; //位运算，同等于M*2 
void addedge(int x, int y, int z){ //链式前向星的加边操作 
	tot++;
	edge[tot].to = y;
	edge[tot].w = z;
	edge[tot].next = head[x];
	head[x] = tot;
	return ;
}
void Prim(){ //Prim算法 
	for(int i = head[1]; i; i = edge[i].next){ //判段是否有重边 
		dist[edge[i].to] = min(dist[edge[i].to], edge[i].w); 
	}
	int u = 1; //u表示当前遍历到的点 
	for(int i = 1; i < n; i++){ //循环n-1次，也就是连n-1条边 
		int minn = INF; //先给最小值附一个极大的初值（我选择的是int的上限，2147483647，其实1e9便足矣） 
		vis[u] = true; //给这个点的访问标记标为真 
		for(int j = 1; j <= n; j++){ //遍历n个点找到权值最小的点 
			if(!vis[j] && dist[j] < minn){ //如果小于当前最小值 且没有被访问过 
				u = j; //记录下标 
				minn = dist[j]; //更新最小值 
			}
		}
		ans += minn; //答案加上这条边的边权 
		for(int k = head[u]; k; k = edge[k].next){ //链式前向星的遍历方式，找到点u所相连的全部点 
			int v = edge[k].to; 
			if(dist[v] > edge[k].w && !vis[v]){ //如果当前点所连的最小权值大于当前的权值且这个点没有被访问过 
				dist[v] = edge[k].w; //更新 
			}
		} 
	}
	return ;
}
void Init(){ //初始化 
	for(int i = 1; i <= n; i++){
		dist[i] = INF; //初始化一个极大值 
	} 
	dist[1] = 0; //但点1要标0 
	return ;
}
int main(){
    while(cin >> n >> m){ //多组数据 
    if(!(n + m)) return 0; //如果n和m都是0，那么结束程序 
    sum = ans = tot = 0;//多测清空！！ 
    memset(vis, 0, sizeof(vis));//多测清空！！ 
    memset(head, 0, sizeof(head));//多测清空！！ 
    while(m--){
    	int x, y, z;
    	cin >> x >> y >> z;
    	addedge(x + 1, y + 1, z); //由于是无向图，所以要存两遍 
    	addedge(y + 1, x + 1, z); //同上，x-->y 与 y-->x 
        sum += z; //统计边权和
	}
	Init(); //初始化 
	Prim(); //Prim算法求解 
	cout << sum - ans << endl; //输出答案 
	}
	return 0;
} 
SP15650 by szkzyc
```


---

## 作者：hswfwkj_ (赞：1)

## 题意简述：
有 $n$ 个点，$m$ 条边，现在要删去一些边，使剩余的点联通的同时保证删去的边的权值和最大。

输出这个最大的权值和。
## 算法：
最小生成树板子，如果没学过请移步模板。

谈到最小生成树，就必谈两大经典算法：
### Kruskal（克鲁斯卡尔） 和 Prim
本题两种方法都可以，这里我用的是克鲁斯卡尔算法，讲一下基本原理：

首先对每条边的权值进行排序，每次选取最小的边，如果这条边连接的两个点本就在同一个集合，不合并，否则，将其合并成一个联通块。以上可以使用并查集维护。当所有点已经联通时，输出结果就行了。

此处就不给正确性证明了（~~因为我不会~~）。

提供代码给大家参考一下：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct edge{
	int x,y,z;
}a[210000];
int f[210000],n,m,ans,k;
int cmp(edge x,edge y){return x.z<y.z;}
int find(int k){return f[k]==k?k:(f[k]=find(f[k]));}
int main(){
	while(cin>>n>>m){
		ans=k=0;
		if(!n&&!m)break;
		for(int i=0;i<=n;i++)f[i]=i;
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);//读入数据
			ans+=a[i].z;//计算总费用
		}
		sort(a+1,a+m+1,cmp);
		for(int i=1;i<=m;i++){
			int fx=find(a[i].x),fy=find(a[i].y);
			if(fx!=fy){//如果它们还没有被合并
				k++;
				f[fx]=fy;
				ans-=a[i].z;//合并并减去花费
				if(k==n-1){
					cout<<ans<<"\n";//输出答案
					break;
				}
			}
		}
	}
	return 0;
}
```
谢谢大家！另外，请管理大大在这道题上加一个生成树标签！

---

