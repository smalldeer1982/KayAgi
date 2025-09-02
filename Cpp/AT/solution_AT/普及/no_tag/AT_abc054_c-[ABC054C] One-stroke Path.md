# [ABC054C] One-stroke Path

## 题目描述

给定一个没有重边和自环的 $N$ 个点 $M$ 条边的无权无向图，第 $i$ 条边连接顶点 $a _ i$ 和 $b _ i$。

求以顶点 $1$ 为起点，只访问 $1$ 次所有顶点的路径有多少条？特别地，起点和终点也视为被访问。

## 说明/提示

$
2 \le N \le 8 \\
0 \le M \le N(N - 1) \\
1 \le a _ i < b _ i \le N
$

给定的无向图中不包含重边和自环。

## 样例 #1

### 输入

```
3 3
1 2
1 3
2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7 7
1 3
2 7
3 4
4 5
4 6
5 6
6 7```

### 输出

```
1```

# 题解

## 作者：方123456 (赞：4)

题意大概就是从 $1$ 开始走，然后要求遍历到所有的点，求路径有多少条。

这个 …… $n \le 8$ ?那岂不是可以乱搞了？

用一个矩阵存图，然后用一个 int 来代替一个布尔数组。

暴力进行一个 DFS 扫就可以了。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=15;
int Map[INF][INF];
int n,m;
int DFS(int x,int y) {
        // cout<<x<<" "<<y<<endl;
        if (y==(1<<n)-1) return 1;
        int sum=0;
        for (int i=1; i<=n; i++) {
                if (!Map[x][i] || (y>>(i-1))&1) continue;
                sum+=DFS(i,y|(1<<(i-1)));
        }
        return sum;
}
signed main()
{
        scanf("%d %d",&n,&m);
        for (int i=1; i<=m; i++) {
                int x=0,y=0; scanf("%d %d",&x,&y);
                Map[x][y]=Map[y][x]=true;
        }
        cout<<DFS(1,1)<<"\n";//注意一开始 1 已经遍历过了。
        return 0;
}

```


---

## 作者：龙潜月十五 (赞：0)

## 一、题意

有 $n$ 个点和 $m$ 条边，问从点 $1$ 出发 **恰好经过所有点各一次** 的路径有多少条。

## 二、思路

由于 $n \leq 8$，因此我们可以想到用 **链式前向星** 存边，再用 DFS 搜索一遍，将经过的点打上标记，遍历其相邻节点，再取消标记。在 DFS 时传一个参数 $cnt$，若 $cnt=n$ 则答案 $ans++$。

## 三、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
    ll sum = 0, ff = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') {
            ff = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
    	sum = sum * 10 + ch - 48;
        ch = getchar();
    }
    return sum * ff;
}

void write(ll x) {
	 if(x < 0) {
		putchar('-');
		x = -x;
	 }
	 if(x > 9)
		write(x / 10);
	 putchar(x % 10 | 48);
}

const int N = 107;
int n, m, ans;
bool vis[N];
struct edge {
	int to, next;
}e[N];
int cnt, he[N];

void add(int u, int v) {
	e[++cnt].next = he[u];
	e[cnt].to = v;
	he[u] = cnt;
}

void dfs(int u, int tot) {
	if(tot == n) {
		ans++;
		return;
	}
	vis[u] = true;
	for(int i = he[u]; i; i = e[i].next) {
		int v = e[i].to;
		if(vis[v])
			continue;
		dfs(v, tot + 1);
	}
	vis[u] = false;
}

int main() {
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	n = read(), m = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read();
		add(u, v);
		add(v, u);
	} 
	
	dfs(1, 1);

	write(ans);
	puts("");	
    return 0;
}


```


---

