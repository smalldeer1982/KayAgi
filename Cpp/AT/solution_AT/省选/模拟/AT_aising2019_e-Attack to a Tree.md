# Attack to a Tree

## 题目描述

一棵有 $N$ 个节点的树，节点编号 $1$ 到 $N$。$(N-1)$ 条边中的第 $i$ 条连接节点 $U_i$ 和节点 $V_i$。点 $v$ 有非零点权 $A_v$。

现在要删去一部分边，使得各个连通块均满足以下两个条件之一：

- 连通块内点的点权均为正数；
- 连通块内点的点权和为负数。

请求出删去的边数的最小值。

## 说明/提示

#### 样例 #1 解释

切断第 $1,2$ 条边即可。

#### 数据规模与约定

对于全部测试数据，保证：

- $1\le N\le 5000$；
- 当 $1\le i\le N$ 时，$1\le |A_i|\le 10^9$。
- 当 $1\le i\le N-1$ 时，$1\le U_i,V_i\le N$，$U_i\neq V_i$。

## 样例 #1

### 输入

```
7
-2 7 5 6 -8 3 4
1 2
2 3
2 4
1 5
5 6
5 7```

### 输出

```
1```

## 样例 #2

### 输入

```
4
1 2 3 4
1 2
1 3
1 4```

### 输出

```
0```

## 样例 #3

### 输入

```
6
10 -1 10 -1 10 -1
1 2
2 3
3 4
4 5
5 6```

### 输出

```
5```

## 样例 #4

### 输入

```
8
-2 3 6 -2 -2 -5 3 2
3 4
7 6
6 2
8 2
5 3
1 8
3 7```

### 输出

```
3```

## 样例 #5

### 输入

```
10
3 4 9 6 1 5 -1 10 -10 -10
7 4
5 6
8 1
9 5
7 1
10 3
2 8
4 10
9 2```

### 输出

```
3```

# 题解

## 作者：_edge_ (赞：1)

题意是给定一棵树，要求断开一些边，使得连通块要么是全正数，要么是总和为负数。

数据范围 $n \le 5000$，暗示有 $O(n^2)$ 的做法，树上的话一般都是考虑树形 DP。

挺简单的一个想法是把权值和答案互换，状态设为 $f_{i,j}$ 表示以 $i$ 为根，然后断开了 $j$ 次。

我们思考如何加入一个子树，会发现这东西好像不太好转移呢，由于题目中连通块和全正有关，不妨设 $f_{i,j,0/1}$ 表示以 $i$ 为根，然后断开了 $j$ 次之后是否全正。

然后考虑 $f_{i,j,1}$ 如何转移，发现加入一个子树 $f_{v,k,1}$ 就会变成 $f_{i,j+k,1}$，我们不能加入一个子树 $f_{v,k,0}$，因为这样会导致这个状态变成 $f_{i,j+k,0}$。

然后考虑 $f_{i,j,0}$ 如何转移，这东西就比较宽松了，$f_{v,k,0/1}$ 都可以转移到这里。

以上是比较简单的树形 DP，然后我们考虑断开一个子树，发现需要断开一个子树，必须满足总和小于 $0$ 或者它是全是正数，两种情况稍微判断一下就可以了。

对于 dp 数组初值设为正无穷，同时转移的时候用另外一个辅助数组来做会比较方便。

感谢 @Loser_king 学长帮助。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=5e3+5;
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
// f[x][y][0/1] 表示 x 为根的子树内，断开了 y 次，当前是否是全正  1/0 的总和最小值 
int a[INF],sz[INF],tot,head[INF],f[INF][INF][3],f1[INF][3],n;
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ; 
}
void DFS(int x,int fa) {
	if (a[x]>0) {
		f[x][0][1]=a[x];
		f[x][0][0]=a[x];
	}
	else f[x][0][0]=a[x];
	sz[x]=1;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS(v,x);
		for (int k=0;k<=sz[x]+sz[v];k++) f1[k][0]=f1[k][1]=1e18;
		for (int j=sz[x];~j;j--)
			for (int k=sz[v];~k;k--) {
				f1[j+k][1]=min(f1[j+k][1],f[x][j][1]+f[v][k][1]);
				f1[j+k][0]=min(f1[j+k][0],min(f[x][j][0],f[x][j][1])+min(f[v][k][0],f[v][k][1]));
				if (f[v][k][0]<0 || f[v][k][1]<1e17) {
					f1[j+k+1][0]=min(f1[j+k+1][0],f[x][j][0]);
					f1[j+k+1][1]=min(f1[j+k+1][1],f[x][j][1]);
				}
			}
		
		for (int j=0;j<=sz[x]+sz[v];j++) 
			f[x][j][0]=f1[j][0],f[x][j][1]=f1[j][1];
		sz[x]+=sz[v];
	}
	return ;
}
signed main()
{
	memset(f,63,sizeof f);
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>a[i];
		if (!a[i]) return 1;
	}
	for (int i=1;i<n;i++) {
		int x=0,y=0;cin>>x>>y;
		add_edge(x,y);add_edge(y,x);
	}
	DFS(1,0);
//	cout<<f[1][0][0]<<" "<<f[1][0][1]<<" endl\n";
	for (int i=0;i<=n;i++)
		if (f[1][i][0]<0 || f[1][i][1]<1e17) {cout<<i<<"\n";return 0;}
	return 0;
}
```


---

## 作者：win114514 (赞：0)

挺有意思的树型 dp。

### 思路

发现直接求解很难对限制下手。

但我们可以注意到答案最多为 $n$。

考虑将答案记录 dp 状态。

我们可以记 $dp_{i,j}$ 为子树 $i$ 合法并且断了 $j$ 条边的状态。

由于合法状态有两种，并且不好一起考虑，所以可以再在 dp 状态中加一维。

令 $dp_{i,j,0/1}$ 为子树 $i$ 内共断了 $j$ 条边，不是/是全部都为正数的最小和。

转移是简单的，自行推导即可。

时间复杂度：$O(n^2)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
int s[5010];
int a[5010];
int g[5010][5010][2];
int t[5010][2];
vector<int> to[5010];

inline void dfs(int x, int f) {
  s[x] = 1;
  if (a[x] < 0) g[x][0][0] = a[x];
  if (a[x] > 0) g[x][0][1] = a[x];
  for (auto i : to[x]) {
    if (i == f) continue;
    dfs(i, x);
    memset(t, 0x3f, sizeof t);
    for (int j = 0; j <= s[i]; j++)
      for (int k = 0; k <= s[x]; k++) {
        t[j + k][0] = min(t[j + k][0], g[i][j][0] + g[x][k][0]);
        t[j + k][0] = min(t[j + k][0], g[i][j][1] + g[x][k][0]);
        t[j + k][0] = min(t[j + k][0], g[i][j][0] + g[x][k][1]);
        t[j + k][1] = min(t[j + k][1], g[i][j][1] + g[x][k][1]);
        if (g[i][j][0] < 0 || g[i][j][1] < 1e17) t[j + k + 1][0] = min(t[j + k + 1][0], g[x][k][0]);
        if (g[i][j][0] < 0 || g[i][j][1] < 1e17) t[j + k + 1][1] = min(t[j + k + 1][1], g[x][k][1]);
      }
    s[x] += s[i];
    memcpy(g[x], t, sizeof t);
  }
}

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 2; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    to[u].push_back(v);
    to[v].push_back(u);
  }
  memset(g, 0x3f, sizeof g);
  dfs(1, 0);
  for (int i = 0; i <= n; i++) {
    if (g[1][i][0] < 0 || g[1][i][1] < 1e17) {
      cout << i << "\n";
      return 0;
    }
  }
}
```

---

## 作者：0x3F (赞：0)

神秘树形 dp。

我们把要算的东西放到状态里，记 $dp_{i,j,0/1}$ 表示以 $i$ 为根的子树，里面断了 $j$ 条边，根所在的连通块的权值是否全部为正，此时根所在的连通块的权值和最少是多少。

若一个连通块内有负数，则必须权值和为负数才能断开这个连通块，若全为正数则无限制。

时间复杂度为 $\mathcal{O}(n^2)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 5e3 + 10;
const int __ = 1e4 + 10;
const long long M = 11451419260817LL;
int n, e, hd[_], nx[__], to[__], val[_];
int siz[_], ans;
long long dp[_][_][2], tmp[_][2];
inline void add(int u, int v) {
    e++;
    nx[e] = hd[u];
    to[e] = v;
    hd[u] = e;
}
void dfs(int x, int f) {
    siz[x] = 0;
    if (val[x] > 0) {
        dp[x][0][1] = val[x];
    } else {
        dp[x][0][0] = val[x];
    }
    for (int i = hd[x]; i; i = nx[i]) {
        int y = to[i];
        if (y != f) {
            dfs(y, x);
            memset(tmp, 0x3F, sizeof(tmp));
            for (int a = 0; a <= siz[x]; a++) {
                for (int b = 0; b <= siz[y]; b++) {
                    tmp[a+b][0] = min(tmp[a+b][0], dp[x][a][0] + dp[y][b][0]);
                    tmp[a+b][0] = min(tmp[a+b][0], dp[x][a][0] + dp[y][b][1]);
                    tmp[a+b][0] = min(tmp[a+b][0], dp[x][a][1] + dp[y][b][0]);
                    tmp[a+b][1] = min(tmp[a+b][1], dp[x][a][1] + dp[y][b][1]);
                }
            }
            for (int a = 0; a <= siz[x] + siz[y]; a++) {
                dp[x][a][0] = tmp[a][0];
                dp[x][a][1] = tmp[a][1];
            }
            siz[x] += siz[y];
        }
    }
    if (x != 1) {
        memset(tmp, 0x3F, sizeof(tmp));
        for (int a = 0; a <= siz[x]; a++) {
            tmp[a][0] = min(tmp[a][0], dp[x][a][0]);
            tmp[a][1] = min(tmp[a][1], dp[x][a][1]);
            if ((dp[x][a][0] < 0) || (dp[x][a][1] < M)) {
                tmp[a+1][1] = min(tmp[a+1][1], 0LL);
            }
        }
        for (int a = 0; a <= siz[x] + 1; a++) {
            dp[x][a][0] = tmp[a][0];
            dp[x][a][1] = tmp[a][1];
        }
        siz[x]++;
    }
}
int main() {
    memset(dp, 0x3F, sizeof(dp));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    for (int a = 0; a <= siz[1]; a++) {
        if ((dp[1][a][0] < 0) || (dp[1][a][1] < M)) {
            ans = a;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

