# [BalticOI 2015] File Paths

## 题目描述

一个文件 $\tt file$ 都需要在一个包含很多文件 $\tt dir1,dir2,\cdots,dirj$ 的目录中，这个文件的 absolute file path 为 $\tt/dir1/dir2/\cdots/dirj/file$，根目录用 $\tt /$ 表示，每一个放在根目录下的文件的 absolute file path 的形式为 $\tt /file$。

符号链接指向一个已被命名的目录，可以看作一个快捷方式，他可以放置在任意目录下，注意，符号链接不能指向文件。比如，我们在 $\tt /$ 下放一个指向 $\tt /$ 的符号链接 $\tt hello$，那么，$\tt /dir/file$，$\tt /hello/dir/file$，$\tt /hello/hello/dir/dile$ 都指向同一个文件 $\tt file$。另比如，我们在 $\tt /dir$ 下放一个指向 $\tt /$ 的符号链接 $\tt hi$，那么，$\tt /dir/file$，$\tt /dir/hi/dir/file$，$\tt /dir/hi/dir/hi/dir/file$ 都指向同一个文件 $\tt file$。符号链接指向上一层，下一层，甚至同层都可以，但是不允许 $\tt ./$，$\tt ../$，$\tt //$ 之类的操作。

现在想问，是否能通过引入一个长为 $s$ 的符号链接使得找到一个文件的 absolute file path 长度恰好为 $k$？

## 说明/提示

#### 样例 1 解释

假设符号链接名字为 $\tt LL$，目录名字为 $\tt a$，$\tt bbbbb$，文件名字为 $\tt ccccccccccccc$，$\tt dddddddddd$，$\tt eee$，$\tt fffffff$，根目录下包含目录 $\tt a$ 和文件 $\tt fffffff$，目录 $\tt a$ 下包含目录 $\tt bbbbb$ 和文件 $\tt eee$，目录 $\tt bbbbb$ 包含文件 $\tt ccccccccccccc$ 和 $\tt dddddddddd$。下面是形象化的表述：

```plain
/
|-- a
| |-- bbbbb
| | |-- ccccccccccccc
| | +-- dddddddddd
| +-- eeee
+-- fffffff
```

- 对于第 $1$ 个文件，满足条件的路径为 $\tt /a/bbbbb/ccccccccccccc$。
- 对于第 $2$ 个文件，满足条件的路径为 $\tt /a/LL/bbbbb/dddddddddd$。
- 对于第 $3$ 个文件，满足条件的路径为 $\tt /a/LL/a/LL/a/LL/a/eeee$。
- 对于第 $4$ 个文件，无满足条件的路径。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（33 pts）：$n,m \le 500$。
- Subtask 2（33 pts）：$n,m \le 3 \times 10^3$，符号链接最多被调用一次。
- Subtask 3（34 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le k,s \le 10^6$，$1\le m,n\le 3\times 10^3$。

#### 说明

翻译自 [BalticOI 2015 Day2 A File Paths](https://boi.cses.fi/files/boi2015_day2.pdf)。

## 样例 #1

### 输入

```
2 4 22
2
0 1
1 5
2 13
2 10
1 4
0 7```

### 输出

```
YES
YES
YES
NO```

# 题解

## 作者：AK_Dream (赞：5)

### 题解
题目实际在求这样一个东西：给定一棵树和边权，你可以在树中加上一条长为 $S$ 的有向边

对于每个叶子节点问：是否能构造出一条从根节点出发以该节点为终点的长为 $K$ 的路径

设有一个叶子节点 $x$

#### 情况1
根到 $x$ 的路径长等于 $K$

那显然答案就是 `Yes`

#### 情况2
走了一次附加的有向边使得路径长为 $K$

考虑这条有向边的终点在哪里：由于走过这条有向边之后还要从它的终点走到 $x$，所以有向边的终点一定要是 $x$ 的一个祖先

记点 $p$ 的深度是 $d_p$，那么假设走了一条 $p\rightarrow q$ 的有向边，总长度就是 $d_p+S+(d_x-d_q)$

其中，$p$ 是树上的任意一个非叶子节点，$q$ 必须是 $x$ 的祖先

要判断是否有 $p,q$ 满足 $d_p+S+(d_x-d_q)=K$，可以考虑枚举 $q$，这样就确定了 $d_x-d_q$，预处理出 $d_p+S$ 可以取哪些值(存在一个 `bool` 数组里)，如果存在某个 $p$ 使得 $d_p+S=K-(d_x-d_q)$ 那么 $x$ 的答案就是 `Yes`

一个例子

![1.png](https://i.loli.net/2020/11/30/cK1j5sPYlGWkXOy.png)

#### 情况3
当然，可能可以走很多次附加的有向边(在一个环上一直绕)

如果一条有向边可以走很多次，那么必须满足它的终点是起点的祖先

又因为终点要是 $x$ 的祖先，所以现在需要找到这样一条路径 $p\rightarrow q$：

满足 $d_x+t*(d_p-d_q+S)=K$ ($t$ 为一个正整数)

其中 $q$ 是 $x$ 的祖先，$p$ 是 $q$ 子树中一个非叶子节点

在dfs时，每到一个非叶子节点就再把以它为根的子树遍历一遍，把所有合法的 $d_p-d_q+S$ 存在 `bool` 数组里，并在回溯时清除贡献

枚举 $K-d_x$ 的所有约数，判断是否有满足条件的 $d_p-d_q+S$ 即可

![](https://i.loli.net/2020/11/30/T7J5kcrFIPLzmQR.png)

时间复杂度 $O((n+m)^2+m\sqrt{K})$

```cpp
#include <bits/stdc++.h>
#define N 20005
using namespace std;
typedef long long ll;

template <typename T>
inline void read(T &num) {
	T x = 0, ff = 1; char ch = getchar();
	for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') ff = -1;
	for (; ch <= '9' && ch >= '0'; ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	num = x * ff;
}

int n, ccf, K, S, a[N], d[N];
int head[N], pre[N<<1], to[N<<1], sz;
int ok[1000005], ok2[1000005], ans[N];

inline void addedge(int u, int v) {
	pre[++sz] = head[u]; head[u] = sz; to[sz] = v;
	pre[++sz] = head[v]; head[v] = sz; to[sz] = u;
}

void dfs1(int x, int fa) {
	if (d[x]+S <= 1000000 && x <= ccf) ok[d[x]+S]++;
	for (int i = head[x]; i; i = pre[i]) {
		int y = to[i];
		if (y == fa) continue;
		d[y] = d[x] + a[y];
		dfs1(y, x);
	}
} 

void dfs3(int x, int fa, int rt, int v) {
	if (x > ccf) return;
	int now = d[x] - d[rt] + S;
	if (now <= 1000000) ok2[now] += v;
	for (int i = head[x]; i; i = pre[i]) {
		int y = to[i];
		if (y != fa) dfs3(y, x, rt, v);
	}
}

int stk[N], top;

void solve(int x) {
	if (d[x] == K) {
		ans[x] = 1; return;
	}
	for (int i = 1; i <= top; i++) {
		int y = stk[i];
		int v = d[x] - d[y];
		if (v <= K && ok[K-v]) ans[x] = 1;
	}
	if (d[x] < K) {
		int v = K - d[x];
		for (int i = 1; i * i <= v; i++) {
			if (v % i == 0) {
				if (ok2[i] || ok2[v/i]) ans[x] = 1;
			}
		}
	}
}

void dfs2(int x, int fa) {
	if (x > ccf) {
		solve(x);
		return;
	}
	stk[++top] = x;
	dfs3(x, fa, x, 1);
	for (int i = head[x]; i; i = pre[i]) {
		int y = to[i];
		if (y != fa) dfs2(y, x);
	}
	dfs3(x, fa, x, -1);
	top--;
}

int main() {
	read(n); read(ccf); read(K); read(S); S++;
	swap(ccf, n); n += ccf;
	for (int i = 1, p; i <= n; i++) {
		read(p); read(a[i]); a[i]++;
		addedge(p, i);
	}
	dfs1(0, 0);
	dfs2(0, 0);
	for (int i = ccf + 1; i <= n; i++) puts(ans[i]?"YES":"NO");
	return 0;
}
```

---

## 作者：qiuqiu1231 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6843)

~~简简单单的 DFS 操作~~

### 有两种情况：

#### 情况1：
走到任意一个点，然后运用链接跳到 $o$ 的某个祖先 $y$ 再走到 $o$。枚举所有 $y$ 看看是否存在 $x$ 即可。时间复杂度 $O(nm)$。

#### 情况2：
走到 $o$ 的某个祖先 $x$，然后走到 $x$ 子树内某个点 $y$，在 $x$ 和 $y$ 之间不断通过用链接来回走，最后再从 $x$ 走到 $o$。枚举 $x$ 和 $y$ 维护出每个长度是否可能存在，然后枚举约数判断是否存在对应的 $x$ 和 $y$ 即可。

AC 代码：
 ```cpp
#include<iostream>
using namespace std;
#define N 3010
int n,m,K,S,i,x,a[N],len[N],g[N],G[N],v[N<<1],nxt[N<<1],ed;
int q[N],t,st[N],en[N],dfn,seq[N],f[2000010];
bool ans[N];
void add(int&x,int y){v[++ed]=y;nxt[ed]=x;x=ed;}
void dfs1(int x){
  q[++t]=a[x];
  seq[st[x]=++dfn]=a[x];
  for(int i=G[x];i;i=nxt[i]){
    int o=v[i];
    for(int j=1;j<=t;j++){
      int k=K-S-a[x]-len[o]+q[j];
      if(k>=0&&k<=K)if(f[k]){ans[o]=1;break;}
    }
  }
  for(int i=g[x];i;i=nxt[i])dfs1(v[i]);
  t--;
  en[x]=dfn;
}
void dfs2(int x){
  for(int i=st[x];i<=en[x];i++)f[seq[i]-a[x]+S]++;
  for(int i=G[x];i;i=nxt[i]){
    int o=v[i];
    if(ans[o])continue;
    int k=K-a[x]-len[o];
    for(int j=1;j*j<=k;j++)if(k%j==0)if(f[j]||f[k/j]){ans[o]=1;break;}
  }
  for(int i=g[x];i;i=nxt[i])dfs2(v[i]);
  for(int i=st[x];i<=en[x];i++)f[seq[i]-a[x]+S]--;
}
int main(){
  scanf("%d%d%d%d",&n,&m,&K,&S);S++;
  for(i=1;i<=n;i++){
    scanf("%d%d",&x,&a[i]);
    a[i]+=a[x]+1;
    add(g[x],i);
  }
  for(i=1;i<=m;i++){
    scanf("%d%d",&x,&len[i]);
    len[i]++;
    ans[i]=a[x]+len[i]==K;
    if(!ans[i])
      	add(G[x],i);
  }
  for(i=0;i<=n;i++)
    f[a[i]]=1;
  dfs1(0);
  for(i=0;i<=n;i++)
    f[a[i]]=0;
  dfs2(0);
  for(i=1;i<=m;i++)
    puts(ans[i]?"YES":"NO");
  return 0;
}
```

[引用](https://blog.csdn.net/weixin_34248487/article/details/85851521)

---

