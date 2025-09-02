# [AGC039B] Graph Partition

## 题目描述

给定一张 $N$ 个顶点，$M$ 条边的无向连通图。  
顶点以 $1\ldots N$ 编号，边以仅包含 $\texttt{0/1}$ 的邻接矩阵的形式给出。

请判断是否能够将顶点分为 $k$ 个非空集合 $V_1,\ldots,V_k$，使得其满足以下条件。若可以，则最大化 $k$：
 - 对于每条边 $(i,j)$，存在 $1 \le t \le k-1$ 满足 $i \in V_t, j \in V_{t+1}$ 或 $i \in V_{t+1}, j \in V_t$。

## 说明/提示

### 数据限制
- $N \in [2,200] \bigcap \mathbb Z$。
- 邻接矩阵仅由 $\texttt0$ 与 $\texttt1$ 组成。
- 邻接矩阵关于主对角线对称。
- 邻接矩阵主对角线均为 $\texttt0$（无自环）。
- 图一定连通。

#### 样例解释 #1
可以分别将顶点 $1,2$ 分入 $V_1,V_2$。

## 样例 #1

### 输入

```
2
01
10```

### 输出

```
2```

## 样例 #2

### 输入

```
3
011
101
110```

### 输出

```
-1```

## 样例 #3

### 输入

```
6
010110
101001
010100
101000
100000
010000```

### 输出

```
4```

# 题解

## 作者：Rushroom (赞：1)

先放[传送门](https://www.luogu.com.cn/problem/AT5616)

## 思路

我们可以轻松的想到这个性质：

- 相邻的两个顶点，它们所在的集合编号差的绝对值为 1。

由这个性质，我们可以推出：

- 对于相邻的两个顶点，它们所在的集合编号**奇偶性不同**。

所以我们可以进行二分图染色，如果染色失败则判断无解，输出 ```-1```。

对于有解的情况，我们可以跑一遍 Floyd，然后枚举两个端点找到最短路，由第一条性质可得，这条路上每相邻的两个点所在的集合编号差的绝对值都为 1，所以这条路上点的数量就是我们要求的 $k$。

## Code

```cpp
/*
 * @Description: I want to be the weakest vegetable in the world!
 * @Author: CGBoy
 * @Date: 2022-01-26 18:10:39
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;i++)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T, case_;
int n;
char c;
int col[220];
bool fail = 0;
vector<vector<int>>v;
void dfs(int k) {
    rep(i, v[k].size()) {
        int x = v[k][i];
        if (col[x] == -1) {
            col[x] = 1 - col[k];
            dfs(x);
        }
        else if (col[x] != 1 - col[k])fail = 1;
    }
}
int ans = 0;
int f[255][255][255];
void solve() {
    cin >> n;
    v.resize(n + 1);
    init(f[0], 63);
    repp(i, n)f[0][i][i] = 0;
    repp(i, n) {
        repp(j, n) {
            cin >> c;
            if (c == '1')v[i].pb(j), f[0][i][j] = 1;
        }
    }
    init(col, -1);
    col[1] = 0;
    dfs(1);
    if (fail) {
        printf("-1");
        return;
    }
    repp(k, n) {
        repp(x, n) {
            repp(y, n) {
                f[k][x][y] = min(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y]);
            }
        }
    }
    repp(i, n)repp(j, n)ans = max(ans, f[n][i][j]);
    cout << ans + 1;
}
int main() {
    T = 1;

    for (case_ = 1;case_ <= T;case_++)solve();
    return 0;
}
```


---

## 作者：wowwowwow (赞：0)

之前算错复杂度了，感谢 @JuRuoOIer 巨佬的指正。

首先一开始显然用二分图染色判断可行性，如果能染色那么可以划分，其他题解已经说得很明白了（逃）。

那么接下来找最大划分方案。这里提供一种和其他题解不一样做法。  

循环每个点作为起点 BFS，具体地说，将**点的值记为点所属的集合**，起点的值记为 $1$ ，然后与之相连的点记为 $2$ 中...以此类推，每个点的值为其相邻已知点的 $+1$，然后找到所有方案（即将不同点作为起点）最大值。

那么为什么这样是对的呢？  
我的理解是，这与直接用最短路算法本质类似，因为每条边长度都为 $1$, BFS 得到的点值就是到起点的最短距离。因为要遍历每条边，因此也是 $O(n^3)$ 的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 205;

int n, col[N], t[N], ans;

bool vis[N];

vector<int> g[N];
string str;
queue<int> q;

void color(int x, bool c){
	if(col[x] != -1){
		if(col[x] != c) ans = -1;
		return;
	} 
	if(ans == -1) return;
	col[x] = c;
	for(int v : g[x]){
		color(v, !c);
	} 
}

int BFS(int st){
	for(int i = 1; i <= n; i++) t[i] = 0, vis[i] = 0;
	q.push(st); t[st] = 1; vis[st] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : g[u])
			if(!vis[v]){
				vis[v] = 1;
				t[v] = t[u] + 1;
				q.push(v);
			}
	}
	int maxn = 0;
	for(int i = 1; i <= n; i++){
		maxn = max(maxn, t[i]);
	} 
	return maxn;
}

signed main(){
	//二分图染色判断yes/no
	//以每个点为起点，bfs找最大值 
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		cin >> str; str = '$' + str;
		for(int j = 1; j <= n; j++){
			if(str[j] == '1') g[i].push_back(j);
		}
	} 
	for(int i = 1; i <= n; i++) col[i] = -1;
	color(1, 0);
	if(ans == -1){
		printf("%d", -1);
		return 0; 
	}
	for(int i = 1; i <= n; i++){
		ans = max(ans, BFS(i) );
	}
	printf("%d", ans);
	return 0;
} 
```

---

## 作者：GTAyin (赞：0)

# **分析题目:**
    
读了题目之后，简单理解就是对图进行染色，当图不能染色时，就输出 -1.

能染色的话，就看能最多染出多少颜色。我放一张图以便理解
    ![](https://cdn.luogu.com.cn/upload/image_hosting/ot8h86we.png)
图上的红色路径就是我们能找到的最长的染色路径。我们可以看出，可以将图上的环挂在一条链上。我们的任务就转变成了在图上找到这个不会绕着环走的最长链。

方法就是对每个点求它在整个图中的最短路，然后取最大值。这样就可以避免出现绕着环走的路径，因为在求最短路时，我们是不会走环的最长路径的。

数据很小，暴力求解完全没有问题。

# **code:**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
const int MAXN=2e4+10;
const int inf=1e9+10;
using namespace std;
int n,ans;
char s[300];
int a[300][300];
struct node{
	int Next,To;
}e[MAXN*2];
int head[MAXN*2],tot;
void add(int u,int v){
	e[++tot].Next=head[u];
	e[tot].To=v;
	head[u]=tot;
}
int col[MAXN],viz[MAXN],bk[MAXN],dis[MAXN];
bool flag;
void dfs(int now,int c,int fa){
	col[now]=c;
	viz[now]=true;
	int t=3-c;
	for(int i=head[now];i;i=e[i].Next){
		int v=e[i].To;
		if(col[v]==col[now]){
			flag=true;
			return;
		}//图上染色，当搜到的点已经染了颜色，但是与相邻的点颜色相同，就是不行的。直接退出搜索。
		if(!viz[v]) dfs(v,t,now);
	}
}
void spfa(int s){
	queue<int> p;
	for(int i=1;i<=n;i++){
		dis[i]=inf;
		bk[i]=false;
	}
	p.push(s);
	dis[s]=0;
	bk[s]=true;
	while(!p.empty()){
		int k=p.front();
		p.pop();
		bk[k]=false;
		for(int i=head[k];i;i=e[i].Next){
			int v=e[i].To;
			if(dis[v]>dis[k]+1){
				dis[v]=dis[k]+1;
				if(!bk[v]){
					p.push(v);
					bk[v]=true;
				}
			}
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s+1;
		for(int j=1;j<=n;j++)
		    if(s[j]=='1') add(i,j);
	}
	dfs(1,1,-1);
	if(flag==true){
		cout<<"-1";
		return 0;
	}
	for(int i=1;i<=n;i++){
		bfs(i);
		int tmp=0;
		for(int j=1;j<=n;j++){
			tmp=max(tmp,dis[j]);
		}
		ans=max(ans,tmp);
	}
	cout<<ans+1;//我们求的是链的长度，所以要加一得到点数。
          //点数才是我们要找的最多染色数量。
	return 0;
}
```
对于在图里对每个点求最短路的应用还有，
如[AT838 直径](https://www.luogu.com.cn/problem/AT838)。
谢谢阅读。

---

