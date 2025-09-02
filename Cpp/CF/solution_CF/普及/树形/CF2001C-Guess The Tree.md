# Guess The Tree

## 题目描述

这是一道交互题。

Misuki 有一棵结构未知，具有 $n$ 个节点的树，节点编号从 $ 1 $ 到 $ n $ ，并要求你写一份代码来猜测它。

你可以询问以下问题：

`? a b`

其中 $a,b$ 为两个节点的编号。

对于一次询问，Misuki 会告诉你哪个节点 $x$ 能最小化 $|d(a,x)-d(b,x)|$ 的值，其中 $d(x,y)$ 是节点 $x$ 和 $y$ 之间的距离。如果存在多个这样的节点，Misuki 会告诉你最小化 $d(a,x)$ 的节点。

现要求你使用不超过 $15n$ 次的询问，来确定这棵树的结构。

## 说明/提示

打印每一行后（即进行一次询问或输出一次答案后），请输出回车并刷新输出缓冲区。可刷新输出缓冲区的有：

- C++ 中的 `fflush(stdout)` 或 `cout.flush()`;
- Java 中的 `System.out.flush()`;
- Pascal 中的 `flush(output)`;
- Python 中的 `stdout.flush()`;
- 对于其他语言，请参阅其他语言的文档。

Translated by @[ARIS2_0](https://www.luogu.com.cn/user/1340759)

## 样例 #1

### 输入

```
1
4
1
1
3```

### 输出

```
? 1 2

? 1 3

? 1 4

! 1 2 1 3 3 4```

# 题解

## 作者：shicj (赞：5)

# CF2001C Guess The Tree 题解

## 0x00 题目翻译

一棵有 $n$ 个节点的秘密树，索引从 $1$ 到 $n$ ，并要求你使用以下类型的查询来猜测它：

- "? a b" - Misuki 会告诉你哪个节点 $x$ 使 $|d(a,x) - d(b,x)|$ 最小，其中 $d(x,y)$ 是节点 $x$ 和 $y$ 之间的距离。如果存在多个这样的节点，那么 Misuki 会告诉你哪个节点能使 $d(a,x)$ 最小化。

用最多 $15n$ 次查询找出秘密树的结构！

## 0x01 解题思路

由距离差最小值，想到中点，由 $15n$ 次查询，想到 $O(n\log n)$，于是自然想到类似二分的思想。

什么时候可以确定一条边呢？当我们查询到两个相邻节点（中间有边）时，答案必定是这两个节点中的一个。反推，如果查询到答案是传入的两个点中的一个，这两个点中间有一条边。

这是只需要以 $(n-1)\times\log n$ 次查询，确定 $n-1$ 条边，即完成此题。

首先钦定一个根节点，因为是树，所以任何一个点都可以作为根节点，于是直接令 $1$ 节点为根，如图为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/a886s43v.png)

容易想到可以尝试遍历除根节点之外的所有点，对于每个点，$\log n$ 次操作确定它和它父亲之间的边。

每次查询得到起点到当前点路上的中点，开始时以根为起点，之后每次以上一次查询的结果为起点，最终当答案为这一次查询的起点时，即可确定当前点与这个点之间有边。（上文中语义可能有点不清，**当前点**指的是当前遍历到的点）。

具体的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/en2cbmox.png)

令根为 $1$，当前点为 $5$。

1. 第一次查询 $1\rightarrow5$，得到这条路上的中点为 $4$，因为 $4\neq1$，所以继续。
2. 第二次查询 $4\rightarrow5$，得到这条路上的中点为 $3$，因为 $3\neq4$，所以继续。
3. 第三次查询 $3\rightarrow5$，得到这条路上的中点为 $3$，因为 $3=3$，所以确定有边 $3\leftrightarrow5$。

这实际上就是二分查询，易证复杂度。

## 0x02 AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int edu[1001],edv[1001],eds;
void solve(){
	eds=0;
	cin>>n;
	for(int i=2;i<=n;i++){
		cout<<"? "<<1<<" "<<i<<endl;
		cin>>ans;
		int u=1,v=i;
		while(ans!=u&&ans!=v){
			u=ans;
			cout<<"? "<<u<<" "<<v<<endl;
			cin>>ans;
		}
		eds++;
		edu[eds]=u;
		edv[eds]=v;
	}
	cout<<"! ";
	for(int i=1;i<n;i++){
		cout<<edu[i]<<" "<<edv[i]<<" ";
	}
	cout<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Wuming_Shi (赞：1)

# CF2001C 题解
## 题意
交互题。有一颗 $n$ 个节点的树，要确定树的形状。每次可以询问两个点 $a,b$，交互库会返回 $a,b$ 路径上的中点（如果点数为偶数则返回更靠近 $a$ 的）。最多询问 $15n$ 次（$n\le1000$）。
## 思路
函数 `query(int a,int b)` 表示处理点 $a$ 到点 $b$ 的路径。

可以设某个点为树根，每次询问树根与一个未被标记的点 。然后递归处理：

先把询问的 $b$ 点标记，并得到中点 $x$。现在需要处理 $x$ 到 $b$ 的路径和 $a$ 到 $x$ 的路径。

对于前者，直接递归下去即可。

对于后者，分类讨论一下：若 $x$ 已被标记，说明 $x$ 到根上的路径已经被确定，不需要处理；如果未被标记，则递归处理 $a$ 到 $x$ 的路径。

递归的终止条件为询问的点 $a$ 与得到的点 $x$ 相同（因为这时询问的 $a,b$ 两点相邻），此时要把 $a,b$ 连边。

最后输出这些边即可。
## 代码
~~~cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010;
int t, n;
typedef pair<int, int> PII;
vector<PII> ans;
bool vis[MAXN];

void query(int a, int b) {
    vis[b] = 1;
    cout << "? " << a << " " << b << endl;
    cout.flush();
    int mid; cin >> mid; //中点
    if (mid == a) { //中点与a重合，递归终止
        ans.push_back({a, b});
        return;
    }
    if (!vis[mid]) query(a, mid); //处理a到中点的路径
    query(mid, b); //处理中点到b的路径
}

void solve() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) { //选取未被标记的点
            query(1, i);
        }
    }
    cout << "! ";
    for (PII i : ans) { //输出答案
        cout << i.first << " " << i.second << " ";
    }
    cout << endl;
    cout.flush();
}

void init() {
    for (int i = 1; i <= n; i++) {
        vis[i] = 0;
    }
    ans.clear();
}

int main() {
    cin >> t;

    while (t--) {
        solve();
        init();
    }

    return 0;
}
~~~

---

## 作者：JiuZhE66666 (赞：1)

# 题解

易得查询返回两点路径上的中点。

如果查询 $a,b$，返回 $a$，说明 $a,b$ 两节点相邻。

而每个节点（非根节点）只有一个父节点，所以我们可以固定一个节点作为根节点，然后在每个节点和根节点上二分查找父节点。


# code

```
int query(int l,int r)
{
    cout<<"? "<<l<<' '<<r<<'\n';
    cout.flush();
    int x;
    cin>>x;
    return x;
}
void solve()
{
    int n;
    cin>>n;

    vector<pair<int,int> > edge;
    for(int i=2;i<=n;i++)
    {
        int r=1;
        int mid=query(i,r);
        while(mid!=i)
        {
            r=mid;
            mid=query(i,mid);
        }
        edge.push_back({i,r});
    }

    cout<<"! ";
    for(auto it:edge) cout<<it.first<<' '<<it.second<<' ';
    cout.flush();
    cout<<'\n';

}
```

---

## 作者：Zhi_ptb (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Sliver-jiblogs/p/18377713)

# 题意概述

这是一个交互题。

有一棵有 $n$ 个节点的树，节点编号从 $1$ 到 $n$ ，并要求你使用以下类型的查询来猜测它：

- ```? a b```会告诉你哪个节点 $x$ 在点 $a$ 和 $b$ 之间（$|d(a,x) - d(b,x)|$ 的值最小），其中 $d(x,y)$ 是节点 $x$ 和 $y$ 之间的距离。如果存在不止一个这样的节点，那么会告诉你哪个节点在哪一个 $x$ 使 $d(a,x)$ 最小。

用最多 $15n$ 次查询找出树的结构。

# 思路

对于每一个 $n$ 我们可以递归搜索节点编号 $p$ 的点和 $i$ 之间的节点，得到的值为 $w$ 若 $w$ 和 $p$ 相等就在 $p$ 和 $i$ 之间连一条边，否则就继续递归 $w$ 和 $i$，初始时 $p$ 等于 $1$，$2 \le i \le n$。对于每次输出使用 ```fflush(stdout);``` 清空缓存。输出格式```! a1 b1 a2 b2……```。

# 代码

```
#include <bits/stdc++.h>
#define ll long long
#define N 100001
#define mod 998244353
#define ios std::ios::sync_with_stdio(false)
#define itie std::cin.tie(0)
#define otie std::cout.tie(0)
std::mt19937_64 mrand(std::random_device{}());
 
int Test;
std::vector<int> a, b;
 
inline void solve(int p, int i) {
    std::cout << "? " << p << " " << i << std::endl;
    fflush(stdout);
    int w;
    std::cin >> w;
    if (w == p) {
        a.push_back(p),
        b.push_back(i);
        return;
    }
    solve(w, i);
}
 
int main() {
    std::cin >> Test; 
    for ( ; Test--; ) {
        int n;
        std::cin >> n;
        a.clear();
        b.clear();
        for (int i = n; i >= 2; i--)
            solve(1, i);
        std::cout << "! ";
        for (int i = 0; i < n - 1; i++)
            std::cout << a[i] << " " << b[i] << " ";
        puts("");
        fflush(stdout);
    }
}
```

---

## 作者：Burnling (赞：1)

欢迎前往 [我的博客](https://blog.burnling.asia/posts/60927.html) 获取~~并不会~~更好的观看体验。

## 题意简述

交互题。

Misuki 选择了一棵有 $n$ 个节点的秘密树，节点编号为 $1$ 到 $n$，并要求你通过以下类型的查询来猜出这棵树：

“? a b” — Misuki 会告诉你哪个节点 $x$ 最小化了 $|d(a,x) - d(b,x)|$，其中 $d(x,y)$ 是节点 $x$ 和节点 $y$ 之间的距离。如果有多个这样的节点，Misuki 会告诉你其中使 $d(a,x)$ 最小的那个节点。

使用最多 $15n$ 次查询来找出 Misuki 的秘密树的结构！

## 思路分析

首先，通过分析题目我们容易知道，返回的 $x$ 实际上是 $a$ 与 $b$ 的中间节点。

如果查询 `? a b` 的返回值为 `a`，那么表明 $a$ 与 `b` 之间通过一条边直接相连。

否则再次查询 `? a x` 以及 `? x+1 b`直到找到相邻的边。

如果设在此树上 $a$ 与 $b$ 之间的距离为 $l$，那么此次操作至多询问 $l-1$ 次。

为了减少查询次数，引入并查集来维护已经连通的节点。

每次查询的两个节点应处于两个不同的连通块，查询后将它们合并起来。

对每一个节点都查一遍与节点 $1$ 之间的通路即可。

---

对于这种解法，操作次数最多的树的结构为链状，且节点编号依次为 $1,2,\cdots,i,\cdots,n$。

我们首先需要 $n-1$ 次的查询 `? 1 i` 。

对于这其中的每一次 `? 1 i`，前 $i-1$ 个节点已经处于同一个连通块中，所以会花费 $\lfloor\log_2(i-1)\rfloor +1$ 次的二分操作来不断逼近右边界。

所以总的操作次数为 $\sum\limits_{i=2}^{n} (\lfloor\log_2(i-1)\rfloor +1)=\sum\limits_{i=2}^{n} \lfloor\log_2(i-1)\rfloor + (n-1)$。

操作次数的上限不会超过 $\displaystyle\sum\limits_{i=1}^{\lfloor\log_2(n-1)\rfloor} i\cdot2^{i-1}$。

这个式子吧，我们稍微放缩一下来找一下上界。

$$
\begin{align}
\displaystyle\sum\limits_{i=1}^{\lfloor\log_2(n-1)\rfloor} i\cdot2^{i-1} &\leq \displaystyle\sum\limits_{i=1}^{\lfloor\log_2(n-1)\rfloor} \lfloor\log_2(n-1)\rfloor\cdot2^{i-1} \\
 & = \lfloor\log_2(n-1)\rfloor\cdot\displaystyle\sum\limits_{i=1}^{\lfloor\log_2(n-1)\rfloor} 2^{i-1}\\
 &= \lfloor\log_2(n-1)\rfloor\cdot (2 ^ {\lfloor\log_2(n-1)\rfloor}-1)\\
 &\leq \lfloor\log_2(n-1)\rfloor\cdot 2 ^ {\lfloor\log_2(n-1)\rfloor} \\
 &\leq (n-1) \cdot \log_2(n-1) \\
 &\leq n \cdot \log_2 n 
\end{align}

$$



所以操作次数最多也不会超过 $n\log_2 n$ 次。

对于 $n \leq 1000$，不会超过 $10n$ 次。

绰绰有余！

## 代码展示

 ```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1000 + 10;

vector<int> G[maxN];
int N;

int fa[maxN];
int find(int x){
    return x == fa[x] ? fa[x] : (fa[x] = find(fa[x]));
}

void dfs(int lp,int rp){

    int a = find(lp);
    int b = find(rp);
    if(a == b) return;

    cout << "? " << lp << " " << rp << endl;
    cout.flush();

    int x;
    cin >> x;
    if(x == lp){
        fa[lp] = b;
        G[lp].push_back(rp);
        return;
    }
    dfs(lp,x);
    dfs(x,rp);
}

inline void solve(){
    
    cin >> N;
    for(int i = 1;i<=N;i++) G[i].clear();
    for(int i = 1;i<=N;i++) fa[i] = i;

    for(int i = 2;i<=N;i++) dfs(i,1);

    cout << "! ";
    cout.flush();

    for(int i = 1;i<=N;i++){
        for(auto p : G[i]){
            cout << i << " " << p << " ";
            cout.flush();
        }
    }
    cout << endl;
    cout.flush();
}

int main(){
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
 ```

---

## 作者：wfc284 (赞：0)

过的第一道交互题，纪念一下。

我们注意到询问次数不得超过 $15n$，而 $15$ 是 $\log$ 级别的，~而这题只是个 C 题~，故联想到二分。  

我们弄一个数组，标记已经确定的点（已确定，即该点集内的边都确定），不妨让 $1$ 号点一开始就已确定。  
我们进行 $n-1$ 轮查询，尝试每轮确定一条边，即每轮将已确定点集扩展一个点。  

随便指定一个未确定的点（$a$），与 $1$ 号结点（$b$）进行询问。我们观察到每次询问给出的 $x$ 一定是 $a$ 到 $b$ 链上的（靠近 $a$ 的）中点，符合二分大致规范（每轮将 $\operatorname {d}(a,b)$ 折半）。  
以下有三种情况：
- 如果 $x=a$，那么 $a,b$ 之间必有连边，达到了确定边的目的，并将 $a$ 标为已确定。
- 否则，如果这个 $x$ 为已确定的点，那么我们令 $a'\gets a, b' \gets x$，将 $a',b'$ 递归处理。
- 否则，$x$ 为未确定的点，我们令 $a' \gets x, b' \gets b$，将 $a',b'$ 递归处理。

这样递归可以保证每轮 $a$ 已确定，$b$ 未确定，有【扩展】的效果，可以不重复地确定所有边。  
同时，每确定一条边就像二分，只会问 $\log$ 次，可以通过 $15$ 这个宽松的限制。

至于时间复杂度，用 set 写得精致一点就 $O(n \log n)$，粗糙一点就 $O(n^2)$。  

[submission.](https://codeforces.com/problemset/submission/2001/305927485)

---

## 作者：Vitamin_B (赞：0)

# 思路
看到 $15n\ge n\log n$，一眼鉴定为某种奇妙的二分。

类似 prim，初始时默认 $1$ 节点已被确认，每次确定一个新点，使得它未被确认但和任意一个已被选中的点连接。

我们发现，任意一个已确认的点和任意一个未确认的点的路径上一定有一个满足条件（即满足它未被确认但和任意一个已被选中的点链接）的点。于是，我们则找到任意一个已确认的点 $l$（例如 $1$）和任意一个未确认的点 $r$ 进行“交互二分”。每次判断就询问 $l,r$，设交互库给出的答案是 $x$，接下来分讨：
1. 若 $x=l$，说明 $l,r$ 就是直接相连的一条边（因为 $d(x,l)=0$，所以 $d(x,r)\le1$，而因为 $l,r$ 一个确认一个未确认，所以 $l\ne r$，得出 $d(x,r)=d(l,r)=1$），那就把 $r$ 确认了，并将 $l,r$ 连上一条边；
2. 若 $x$ 已经被标记，那就在 $x,r$ 里继续找。
3. 若 $x$ 未被标记，那就在 $l,x$ 里找。

重复上述过程 $n-1$ 次（不是 $n$ 次，因为 $1$ 节点本来就被确认了）后就选完了所有的点。

[代码](https://codeforces.com/contest/2001/submission/277388039)。

---

## 作者：EricWan (赞：0)

正解还是不难想到的，我们进行二分。

维护两个集合：树点集合、非树点集合。

每次在非树点集合中选择一个点 $X$，进行二分，找到 $1$ 到 $X$ 路径上的与数点有边的点，连边后，将这个点弹出非树点集合，加入树点集合。

重复到非树点集合为空即可。

多测记得循环清空，否则千古恨。

---

## 作者：I_will_AKIOI (赞：0)

观察查询操作，每次他会告诉你最小化 $|\operatorname{dis}(a,x) - \operatorname{dis}(b,x)|$ 的点，我们把这个点记作 $\operatorname{query}(a,b)$。那么 $\operatorname{query}(a,b)$ 一定是路径 $(a,b)$ 的中点，并且还在该路径上。同时如果 $\operatorname{query}(a,b)=a$，说明点 $a,b$ 之间有一条边。

因此我们可以考虑分治，设函数 $\operatorname{solve}(a,b)$ 表示当前正在查找路径 $(a,b)$ 上的所有边，接着我们查询一下 $(a,b)$，如果 $\operatorname{query}(a,b)=a$，说明两点之间有边，并且到达了边界情况。否则接着我们以 $\operatorname{query}(a,b)$ 为这条路径的中点，调用 $\operatorname{solve}(a,\operatorname{query}(a,b))$ 和 $\operatorname{solve}(\operatorname{query}(a,b),b)$，然后继续解决这两个子问题。

但是容易发现得到路径 $(a,b)$ 上的所有边需要的查询次数太多了，每个函数都要调用两个子函数，每个子函数都需要一个查询，所以一共要查询 $\operatorname{dis}(a,b)$ 次，我们每次需要枚举 $i\in[2,n]$，然后调用 $\operatorname{solve}(1,i)$ 来解决问题，这样查询次数为 $n^2$ 会寄。

原因是因为我们浪费了很多询问次数在一条所有边都已经知道的路径。所以我们可以开个并查集，到达边界清况给两个集合合并，在调用 $\operatorname{solve}(a,b)$ 时如果 $a,b$ 在一个集合，就可以直接跳出询问。由于每条路径 $(a,b)$ 只会被调用一次 $\operatorname{solve}(a,b)$，每个 $\operatorname{solve}(a,b)$ 会查询 $\operatorname{dis}(a,b)$ 次，所以查询次数是 $n$ 级别的，通过[提交记录](https://codeforces.com/contest/2001/submission/277383767)可知这种解法的查询次数比 CF 的 std 还优。

```cpp
#include<bits/stdc++.h>
#define N 1005
#pragma GCC optimize("O3")
using namespace std;
int n,a[N][N],f[N];
int fa(int x)
{
  if(x==f[x]) return x;
  return f[x]=fa(f[x]);
}
int query(int x,int y)
{
  int res;
  cout<<"? "<<x<<" "<<y<<endl;
  cin>>res;
  return res;
}
void dfs(int x,int y)
{
  int u=fa(x),v=fa(y);
  if(u==v) return;
  int z=query(x,y);
  if(x==z) a[x][y]=1,f[u]=v;
  else dfs(x,z),dfs(z,y);
  return;
}
void solve()
{
	cin>>n;
  for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=0;
  for(int i=1;i<=n;i++) f[i]=i;
  for(int i=2;i<=n;i++) dfs(1,i);
  cout<<"! ";
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      if(a[i][j])
        cout<<i<<" "<<j<<" ";
  cout<<endl;
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

~~耶，终于有一次打 CF 爆标了~~。
### 题意
一棵点数为 $n$ 的树，形态未知，每次可以询问两个点 $u$，$v$，返回一个点 $x$ 使得 $|dis(u,x)-dis(v,x)|$ 最小，如有多个 $x$ 满足则返回 $dis(u,x)$ 最小的那个，要求在 $15n$ 次询问内还原出整棵树的形态。
### 分析
先画一下图感受一下发现是返回 $u$，$v$ 路径中点，于是显然如果返回 $u$ 则 $u$ 与 $v$ 之间有边。

在考虑一下链的情况，发现找到两个端点直接分治就好了，整个分治过程类似线段树建树，所以询问数在 $4n$ 级别。

但是我们发不现两端点，于是不管了，先直接扔到树上想，钦定一个根为一个端点，直接暴力枚举另一个端点全部做一遍就好了，然后询问数炸了。

然后我们又可以发现处理过的链可以直接返回不用递归下去了，所以弄个并查集，维护一下连通性，如果当前递归到的两端点连通了就直接跑路。然后你发现这样做非常对啊，还是 $4n$ 级别的，交上去实测确实没有询问次数超过 $5000$ 次的数据，~~爆标了非常牛~~。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e3+5;
int T;
int n;
vector<pii> e;
int fa[maxn];
int fd(int x){
	if(fa[x]==x) return x;
	return fa[x]=fd(fa[x]);
}
void solve(int u,int v){
	if(fd(u)==fd(v)) return;
	cout<<"? "<<u<<" "<<v<<"\n";
	fflush(stdout);
	int m=read();
	if(m==u){
		int x=fd(u),y=fd(v);
		fa[x]=y;
		e.eb(mkpr(u,v));
		return;
	}
	solve(u,m);solve(m,v);
}
signed main(){
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read();e.clear();
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=2;i<=n;i++) solve(1,i);
		cout<<"! ";
		for(pii x:e) cout<<x.fir<<" "<<x.sec<<" ";
		cout<<"\n";
		fflush(stdout);
	}
	return 0;
}
```

---

