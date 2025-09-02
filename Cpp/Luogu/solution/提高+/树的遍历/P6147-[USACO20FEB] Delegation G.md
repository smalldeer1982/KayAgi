# [USACO20FEB] Delegation G

## 题目描述

Farmer John 有 $N$ 个牧场，这些牧场通过 $N-1$ 条道路连接，形成了一个树形结构。

但在 28 年的经营后（译者注：USACO 创办于 1992 年），FJ 觉得处理树上问题非常辣手，他认为一条链上的问题更加简单。

因此他决定将整棵树划分为若干条链，将每一条链的管理权授予一位工人。为了避免可能的争端，他希望所有链的长度均相同。

FJ 现在想知道，对于每一个满足 $1 \leq K \leq N-1$ 的 $K$，是否存在一种划分方案，使得整棵树被划分成若干条链，且每条链的长度都**恰好**是 $K$。

## 说明/提示

### 样例解释

$K=1,2,3$ 时都存在一种合法的划分方案。

$K=3$ 时的一种划分方案如下：

$13-12-11-8, 10-9-8-6, 7-6-2-3, 5-4-2-1$

### 子任务

- 测试点 $2 \sim 4$ 满足**最多**有一个点的度数大于 $2$。
- 测试点 $5 \sim 8$ 满足 $N \leq 10^3$。
- 测试点 $9 \sim 15$ 没有特殊限制。

## 样例 #1

### 输入

```
13
1 2
2 3
2 4
4 5
2 6
6 7
6 8
8 9
9 10
8 11
11 12
12 13```

### 输出

```
111000000000```

# 题解

## 作者：StudyingFather (赞：15)

原图是一棵无根树，为了方便起见，我们指定 $1$ 号点为根。

接下来我们从 $1$ 号点开始遍历整棵树。

画个图后会发现，一条经过点 $u$ 的链只可能是如下两种情况之一：

- $v_1 \to u \to v_2$，其中 $v_1,v_2$ 是 $u$ 子树内的某个点（特殊情况下，当然可以和 $u$ 重合）；
- $v \to u \to f$，其中 $v$ 是 $u$ 子树内的某个点，$f$ 是 $u$ 的某个祖先节点。

显然，对于某个点 $u$，第二种链最多只有一条。

于是我们可以对每个点 $u$，维护其等待配对的子链列表。每次遍历到 $u$ 的一个子节点 $v$ 时，将经过 $v$ 的子链尝试与列表中已有的子链配对。如果配对失败就加入等待配对列表。

最后如果存在一个 $u$ 满足其等待配对的子链大于等于两条（根据上面的推导，这种情况下肯定存在一条无法配对的孤链），则无解。

这个做法的效率如何呢？对于一个 $K$，进行检验的时间显然是 $O(N)$ 的，我们需要对 $N-1$ 的每个因子都检验一遍，从而时间复杂度是 $O(N\sigma_0(N-1))$ 的。

数据范围内最坏情况下，$N=83161$ 时 $N-1$ 的因子有 $128$ 个，在星形图（最多只有一个点的度数大于二）的情况下有被卡常数的风险（作者在 USACO 比赛提交时测试点 $3$ 超时（默认开启 `-O2` 优化选项），[在 luogu 上提交时](https://www.luogu.com.cn/record/31235944) 开启 `-O2` 选项测试点 $3$ 用时 1.27s）。

这种情况下可以考虑对星形图特判处理。

下面是作者在比赛时提交的代码：

（UPD 2021/08/10：感谢 @zhaohaikun 指出了我题解中的一处 [实现细节问题](https://www.luogu.com.cn/discuss/show/338901)，代码已经修正）

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
vector<int> e[100005];
int siz[100005], n;
bool dfs(int u, int fa, int k) {
  map<int, int> m;
  for (auto v : e[u])
    if (v != fa) {
      if (!dfs(v, u, k)) return false;
      int tmp = k - siz[v];
      if (m.count(tmp) && m[tmp]) {
        m[tmp]--;
        if (m[tmp] == 0) m.erase(tmp);
        siz[u] -= tmp;
      } else if (k != siz[v])
        siz[u] += siz[v], m[siz[v]]++;
    }
  siz[u]++;
  int rem = 0;
  for (auto p : m) rem += p.second;
  return rem <= 1;
}
int main() {
  freopen("deleg.in", "r", stdin);
  freopen("deleg.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin >> n;
  n--;
  for (int i = 1; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    if (n % i)
      cout << 0;
    else {
      memset(siz, 0, sizeof(siz));
      if (dfs(1, 0, i))
        cout << 1;
      else
        cout << 0;
    }
  }
  cout << endl;
  return 0;
}

```

---

## 作者：CGDGAD (赞：11)

## 题解 P6147 Delegation

----

### 分析

首先钦定 $1$ 为根。

注意到经过点 $u$ 的链一定有两种情况：

- 从点 $u$ 的某个儿子出发，到另一个儿子（1）；
- 从点 $u$ 的某个儿子出发，到 $u$ 的父亲（2）。

注意到第二种情况一定**最多只有一条链**。

那么对于每一个子树，我们要检查，这棵子树是否能被一些长度为 $K$ 的链完全覆盖，或者部分覆盖后，还剩有**一条**长度 $< K$ 通向根结点的链。

这个过程肯定是需要 dfs 操作的。**下面设 $f(u)$ 为遍历点 $u$ 时的返回值。**

如果以 $u$ 为根的子树不满足条件，$f(u) =-1$。否则，输出多余的这条链的长度（可能为 $0$）。

对 $u$ 进行 dfs 的时候，首先对于 $u$ 的所有儿子 $v$，一定要进行 $f(v)$，如果任何一个返回 $-1$，那么 $f(u)$ 就返回 $-1$。否则，我们就会有一条长为 $f(v)+1$ 的链。这时，我们把所有这样的链**两两配对**，成为上面所讲的第一种情况。如果尽可能一一配对后只剩一条短链，那么就返回它的长度；否则返回 $-1$。

----

### 实现

对 $u$ 进行 dfs 的时候，对于所有的 $v$，把所有的 $f(v)+1$ 放入一个 `multiset` $s$ 中维护，如果碰到可以两两配对的情况就从 $s$ 中删去，否则加入 $s$。如果最终 $s$ 的元素个数为 $0$ 或 $1$ 则可以继续，否则就返回 $-1$。

核心部分的实现，评测时建议打开 `-O2` 优化：

```cpp
int n;
std::vector<int> e[100001];

int dfs(int u, int fa, int k) {
	std::multiset<int> s;
	for (int v : e[u])
		if (v != fa) {
			int ans = dfs(v, u, k);
			if (ans == -1) return -1;
			++ans, ans %= k;
			if (ans == 0) continue;
			if (s.count(k - ans))
				s.erase(s.find(k - ans));
			else
				s.insert(ans);
		}
	if (s.size() == 0) return 0;
	if (s.size() == 1) return *s.begin();
	return -1;
}

int main() {
	n = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		e[u].push_back(v),
		e[v].push_back(u);
	}
	for (int i = 1; i < n; ++i)
		if ((n - 1) % i) putchar('0');
		else putchar((dfs(1, 0, i) == 0) + '0');
	putchar('\n');
	return 0;
}
```

---

## 作者：Kazdale (赞：4)

好像都在用 STL，那我来提供一个用数组实现的做法。
- ## 分析
	首先就可以想到，对于点 $u$ 的子树中的链而言，要么两条在子树中的链通过 $u$ 连接在一起形成一条长度为 $K$ 的链（长度为 $K$ 的链可视为与一条长度为 $0$ 的链连接），要么通过 $u$ 与 $u$ 的父节点及其以上的部分连接形成一条长度为 $K$ 的链。
    
   那么我们显然可以发现，$u$ 与它的父节点之间有且只有一条边，所以可以推出：在 $u$ 的子树中，最多只有一条链可以与 $u$ 的父节点及其以上的部分连接。那么就说明：在 $u$ 的子树中，如果使每两条长度和为 $x$ 的链两两互相连接完最多剩下一条链。
   
- ## 代码实现
	我用 $bsk_i$ 来储存一棵子树内长度为 $i$ 的链的数量，那么当我取了一条长度为 $len$ 的链，如果 $bsk_{K - len} \neq 0$，就说明存在一条长度为 $K - len$ 的链，那么我们就可以将这两条链之间相连。反之就说明长度为 $K - len$ 的链不存在，我们只能将这条链向上连，因为向上连的链只能有一条，所以当我们发现已经有一条链只能向上连时，就说明在这个 $K$ 下不能把树分割成若干个长度为 $K$ 的链。

- ## 复杂度分析
	对于每个固定的 $K$，只需要进行一次 DFS 即可，时间复杂度为 $O(n)$，那么如果我们选择枚举 $K$，时间复杂度就会是 $O(n^2)$，肯定会超时，所以我们需要进行剪枝。
    
    可以发现，因为树上的路径总长度为 $n - 1$，所以当 $K$ 不是 $n - 1$ 的因数时，必然无解。
    
    所以只有在 $K$ 为 $n - 1$ 的因数时，我们才会进行 DFS，这样我们就能将时间复杂度降到 $O(n \sqrt{n})$，可以通过本题。

- ## 细节
	当我们枚举 $u$ 的儿子 $v$ 时，因为 $u$ 到 $v$ 中间还有一条边，所以需要将 $f_v + 1$，如果此时 $f_v = K$ 了，那么这时可以直接将这条链单独分出来，所以要使 $f_v = 0$。
    
   如果 $f_i + f_i$ 恰好等于 $K$，那么一次合并就会直接将 $bsk_i - 2$，容易出现负数，所以当 $K$ 是偶数时，我们先将 $bsk_{K / 2}$ 对 $2$ 取模，如果不剩下就说明长度为 $K / 2$ 的边可以全部都两两相连成长度为 $K$ 的链，如果剩下 $1$ 条就直接向上连。
   
   因为 $bsk_i$ 是单独对每一棵子树定义的，所以当我处理 $u$ 节点时，需要先将所有子节点 $v$ 处理完之后再计算 $bsk_i$，如果紧接着 DFS 计算 $bsk_i$ 的话，就会导致处理一棵子树时，它的 $bsk_i$ 中还包括了上一棵的 $bsk_i$，进而导致答案出错。
   
   可以很容易地想到将两条链连接时需要将两条链的 $bsk_i - 1$，当一条链向上连接时，也需要将这条链的 $bsk_i - 1$，因为向上连接也相当于消耗掉这条边，使长度为 $i$ 的边的数量减少了 $1$，所以取出一条边时就要对 $bsk_i - 1$。

- ## 代码

```cpp
#include <iostream>
using namespace std;
constexpr int MAXN = 1000007;
int to[MAXN], nxt[MAXN], head[MAXN], cnt;
int f[MAXN], bsk[MAXN];
int n, K, ans;
inline void add(int u, int v) {
	to[++cnt] = v;
	nxt[cnt] = head[u], head[u] = cnt;
}
inline void dfs(int u, int fa) {
	f[u] = 0;
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v == fa)  continue;
		dfs(v, u);
	}
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v == fa)  continue;
		++f[v];
		if (f[v] == K)  f[v] = 0;
		if (f[v])  ++bsk[f[v]];
	}
	if (K % 2 == 0)  if (bsk[K / 2] % 2 == 1)  f[u] = K / 2, bsk[K / 2] = 0;
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (!bsk[f[v]] || v == fa || !f[v])  continue;
		--bsk[f[v]];
		if (bsk[K - f[v]] == 0) {
			if (!f[u])  f[u] = f[v];
			else  ans = 0;
		}
		else  --bsk[K - f[v]];
	}
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		add(u, v);  add(v, u);
	}
	for (int i = 1; i <= n - 1; ++i) {
		if ((n - 1) % i)  cout << "0";
		else {
			K = i, ans = 1;
			dfs(1, 0);
			cout << ans;
		}
	}
	return 0;
}
```

---

## 作者：7KByte (赞：4)

题目思路和``NOIP2018``某题十分相似。。。


枚举长度$\operatorname{Len}$，``DFS``贪心拼凑长度为$\operatorname{Len}$的链。


如果有多于一条链不能被拼凑起来则说明$\operatorname{Len}$是不满足的。

如果只剩一条链则返回这条链的长度$+1$。

如果不剩链返回$1$。


如何完成拼凑这一过程呢？我们开个``vector``记录每个子节点返回的值，排序然后双指针匹配即可。


更具体的操作可以参考[**这道题**](https://www.luogu.com.cn/problem/P5021)

显然此时的复杂度是$\operatorname{O(N^2)}$。

考虑优化。

经过观察我们可以发现，只有当$\operatorname{Len}|\operatorname{N}$时才有可能为真。


所以我们只用统计$N$的约数即可。

还有一个细微的优化。

当$\operatorname{Len=X}$时为假，那么$\operatorname{Len=k*X}$时亦为假。


理论时间复杂度$\operatorname{O(N\sigma(N)logN)}$，实际复杂度玄学且能过。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#define N 100005
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,h[N],tot;
struct edge{
	int to,nxt;
}e[N<<1];
void add(int x,int y){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;
}
int dfs(int x,int fa,int len){
	vector<int>a;
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=fa){
		int u=dfs(e[i].to,x,len);
		if(u==-1)return -1;
		u++;
		if(u==len)continue;
		a.push_back(u);
	}
	int s=a.size();
	sort(a.begin(),a.end());
	int l=0,r=s-1,ret=0;
	while(l<r){
		if(a[l]+a[r]==len)l++,r--;
		else if(ret)return -1;
		else if(a[l]+a[r]>len)ret=a[r],r--;
		else ret=a[l],l++;
	}
	if(l>r)return ret;
	else if(ret)return -1;
	return a[l];
}
bool check(int len){
	if(!dfs(1,0,len))return true;
	return false;
}
int main(){
	//freopen("IN.in","r",stdin);
	//freopen("deleg.in","r",stdin);
	//freopen("deleg.out","w",stdout);
	scanf("%d",&n);
	if(n==1)return 0;
	rep(i,1,n-1){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	putchar('1');
	rep(i,2,n-1){
		if(((n-1)%i)==0&&check(i))putchar('1');
		else putchar('0');
	}
	return 0;
}
```

---

## 作者：45dino (赞：3)

话说这次月赛金组不难，1绿两蓝，如果我银组再考好点就能做金组了……

题目意思比较绕（语文太烂）所谓“链”指的就是一条线，在本题中可以拐弯（如下）![](https://cdn.luogu.com.cn/upload/image_hosting/db2i4itf.png)
此时k=3；

那么可以想到，如果以点 $d$ 作为“拐弯点”（d=1），那么如果 $d$ 的一边是 $a(a=1)$ 那么另一边必然是 $(k-a)(=2)$ 。

按照这个思路，只要算出任意一点的所有儿子的子树个数，在分别配对就可以了，如果有没有配上的，必然就不行。

主要注释看代码：
```
#include<bits/stdc++.h>
using namespace std;
vector<int> con[100001];//邻接矩阵判断相邻关系
vector<int> son[100001];//son[1]代表1的儿子们分别有多少子树；
int n,sub[100001],cnt,c[100001];//sub数组表示子树的数量，cnt代表单个的数量（见judge函数），c数组见judge函数
void dfs(int so,int fa)//dfs求son[][]
{
	sub[so]=1;
	for(int i=0;i<con[so].size();i++)
		if(con[so][i]!=fa)
		{
			dfs(con[so][i],so);
			sub[so]+=sub[con[so][i]];
			son[so].push_back(sub[con[so][i]]);
		}
	if(sub[so]!=n)
		son[so].push_back(n-sub[so]);
}
bool judge(int k)
{
	if((n-1)%k!=0)//特判，如果不能整除，说明不能均分
		return 0;
	for(int i=1;i<=k;i++)//清0
		c[i]=0;
	for(int i=1;i<=n;i++)
	{
		cnt=0;
		for(int l=0;l<son[i].size();l++)
		{
			int m=son[i][l]%k;
			if(m==0)
				continue;
			if(c[k-m])//如果可以配对，就配
			{
				c[k-m]--;
				cnt--;
			}
			else//如果不能配对，就留
			{
				c[m]++;
				cnt++;
			}
		}
		if(cnt)//如果有落单的说明不行
			return 0;
	}
	return 1;
}
int main()//主程序
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int a,b;
		cin>>a>>b;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	dfs(1,0);
	for(int i=1;i<n;i++)
		cout<<judge(i);
	return 0;
}
```


---

## 作者：weilycoder (赞：1)

**提供一种不加 O2 也能在 1s 内 A 掉本题的优化。**

# 题意简述

给定一棵 $N$ 个节点的树，求对于每一个 $K(1\le K<N)$，是否能将树恰好分成若干条长度均为 $K$ 的链（节点可以重复使用，边不行）。[传送门](https://www.luogu.com.cn/problem/P6147)

# 思路

题目给定一棵无根树，为了方便 DFS，我们认定节点 $1$ 为根节点，存下每个节点的孩子。

容易发现，对于一个以节点 $u$ 为根的子树，所有经过节点 $u$ 的链为下列情况之一：

+ $v_1\to u\to v_2$，其中 $v_1$、$v_2$ 为子树 $u$ 里的两个点；
+ $v\to u\to p$，其中 $v$ 是子树 $u$ 里的点，$p$ 是 $u$ 的祖先节点。

由于 $u$ 只有一条通往其祖先节点的边，故第二种情况显然只能出现一次。

我们现在可以 DFS 了：在回溯时取得当前节点子树中待配对的链长，放入可重集中，若集合中存在能配对的两条链，就将他们取出。最终若存在超过一条链无法配对，则无解；若只有一条链无法配对，就将其记录，等待其父节点配对。（建议配合代码注释食用）

一个显然的优化：$K$ 应能将 $N-1$ 整除；否则不能配对。

```c++
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int n, mk[100010], vis[100010];
vector<int> nodes[100010];
struct nd {
    int fa;
    vector<int> ch;
} tree[100010];

void make(int now, int fa) { // DFS 建树
    mk[now] = -1;
    tree[now].fa = fa;
    for (int c: nodes[now]) {
        if (mk[c]) continue;
        tree[now].ch.push_back(c);
        make(c, now);
    }
}

int dfs(int now, int k) { // 返回非零代表存在超过一条链无法配对
    unordered_multiset<int> mp; // 记录未配对子链的可重集
    for (int c: tree[now].ch) {
        if (dfs(c, k)) return vis[now] = -1; // 递归处理子树
        int tp = (vis[c] + 1) % k; // 获取待配对的子链
        if (tp) {
            auto pt = mp.find(k - tp); // 检查是否存在能配对的链
            if (pt == mp.end()) // 不存在，将当前链放入可重集
                mp.insert(tp);
            else
                mp.erase(pt); // 存在，将能配对的链取出
        }
    }
    switch (mp.size()) {
        default: // 超过一条子链未配对
            return vis[now] = -1;
        case 0:
            return vis[now] = 0;
        case 1: // 保存剩余子链链长
            vis[now] = *mp.begin();
            return 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        nodes[u].push_back(v), nodes[v].push_back(u);
    }
    make(1, 0);
    cout << "1";
    for (int i = 2; i < n; ++i) {
        if ((n - 1) % i) {
            cout << "0";
            continue;
        }
        dfs(1, i);
        // 根节点存在未配对的链，则无解
        cout << (vis[1]? "0" : "1");
    }
}
```

这段代码已经可以[在洛谷上 AC](https://www.luogu.com.cn/record/147801048)，但去掉 `O2` 优化后会 [T 掉第三个点](https://www.luogu.com.cn/record/147801069)。

实际上，在一些较慢的评测机上（我们学校 OJ，然后时限还只有 1s），这段代码是不可能 AC 的（存在星型图）。

# 优化

我们可以发现，假如一个节点只有一个孩子，那么 DFS 时访问它是毫无意义的。换句话说，这个节点不是 **「关键点」**。

我们认为，孩子数不为 $1$ 的节点为关键节点；特别地，认为根节点（节点 $1$）总是关键节点（显然两个关键节点的 LCA 也是关键节点）。在这样的定义下，我们在 DFS 建树时建立**虚树**，即一棵只保留关键节点的树（其实还要包括关键节点 LCA，但在本题中无需考虑），可以对常数进行优化（对存在大量点的度数小于 $2$ 的图效果显著，即数据范围中第一条特殊性质）。

另外，$K=k$ 时匹配成功显然是 $K=nk(n\in\mathbb{N}^{*})$ 匹配成功的必要不充分条件。


```c++
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool fg[100010];
int n, vis[100010], dpth[100010];
vector<int> nodes[100010];
vector<int> tree[100010];

void make(int now, int fa, int gf, int dp) { // DFS 建虚树
    dpth[now] = dp; // 记录深度，方便计算链长
    if (nodes[now].size() != 2 || now == 1) // 若是关键节点
        // 将自己存入上一个关键节点的孩子中，并更新关键节点
        tree[gf].push_back(now), gf = now;
    for (int c: nodes[now]) {
        if (c == fa) continue;
        make(c, now, gf, dp + 1);
    }
}

int dfs(int now, int k) { // 返回非零代表存在超过一条链无法配对
    unordered_map<int, int> mp; // 记录未配对子链
    for (int c: tree[now]) {
        if (dfs(c, k)) return vis[now] = -1; // 递归处理子树
        int tp = (vis[c] + (dpth[c] - dpth[now])) % k; // 获取待配对的子链
        if (tp) {
            if (mp.count(k - tp) == 1) {
            // 检查是否存在能配对的链
                --mp[k - tp]; // 存在，将能配对的链取出
                if (!mp[k - tp]) mp.erase(k - tp);
            } else {
                ++mp[tp]; // 不存在，将当前链放入
            }
        }
    }
    switch (mp.size()) {
        default:
            return vis[now] = -1;
        case 0:
            return vis[now] = 0;
        case 1:
            if (mp.begin()->second == 1)
                vis[now] = mp.begin()->first;
            else return vis[now] = -1;
            return 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        nodes[u].push_back(v), nodes[v].push_back(u);
    }
    make(1, 0, 0, 1);
    cout << "1";
    for (int i = 2; i < n; ++i) {
        if ((n - 1) % i || fg[i]) {
            cout << "0";
            continue;
        }
        dfs(1, i);
        // 根节点存在未配对的链，则无解
        cout << (vis[1]? "0" : "1");
        if (vis[1])
            for (int j = i << 1; j < n; j += i)
                fg[j] = true;
    }
}
```

在洛谷上，这段代码加上输入输出优化后是[当前最优解](https://www.luogu.com.cn/record/list?pid=P6147&orderBy=1&status=&page=1)（[评测记录](https://www.luogu.com.cn/record/160553665)），在关掉 O2 后仍能[在 1s 内通过](https://www.luogu.com.cn/record/160554113)。

---

## 作者：Genius_Star (赞：0)

### 思路：

首先注意到 $k$ 必须是 $n - 1$ 的因子。

故我们需要判断的 $k$ 只有 $\tau(n - 1)$ 级别。

考虑如何判断合法。

注意到对于 $u$ 这个子树，从起子树内传出的链最多只有一条。

设 $s_v$ 表示 $v$ 子树内传上来的链的长度。

故对于 $u$ 的所有儿子都传上来了一条链，我们需要将其合并到为空或者只剩一条。

开一个桶，然后枚举儿子的 $s_v$，查找 $k - s_v$ 是否也在桶中，然后即将这两个链合并。

时间复杂度为 $O(\tau(n - 1)n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
bool F;
int n, u, v, now;
int s[N], f[N];
bool ans[N];
vector<int> E[N];
inline void add(int u, int v){
	E[u].push_back(v);
	E[v].push_back(u);
}
inline void dfs(int u, int fa){
	for(auto v : E[u]){
		if(v == fa)
		  continue;
		dfs(v, u);
		if(!F)
		  return ;
	}
	for(auto v : E[u]){
		if(v == fa || s[v] + 1 == now)
		  continue;
		++f[s[v] + 1];
	}
	int sum = 0;
	for(auto v : E[u]){
		if(v == fa || s[v] + 1 == now || !f[s[v] + 1])
		  continue;
		--f[s[v] + 1];
		if(f[now - s[v] - 1])
		  --f[now - s[v] - 1];
		else{
			++sum;
			s[u] = s[v] + 1;
		}
	}
	if(sum > 1)
	  F = 0;
	for(auto v : E[u]){
		if(v == fa || s[v] + 1 == now)
		  continue;
		f[s[v] + 1] = 0;
	}
}
inline void solve(int k){
	F = 1;
	now = k;
	for(int i = 1; i <= n; ++i)
	  s[i] = 0;
	dfs(1, 1);
	ans[k] = F;
}
int main(){
	n = read();
	for(int i = 1; i < n; ++i){
		u = read(), v = read();
		add(u, v);
	}
	for(int k = 1; k < n; ++k){
		if((n - 1) % k != 0)
		  continue;
		solve(k);
	}
	for(int i = 1; i < n; ++i)
	  putchar('0' + ans[i]);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 题面
给你一棵树，问你可不可以把他分成若干个长度为 $k$ 的链。

### 思路
显然，每个子树只会有一个链延伸到上面，于是记录每颗子树大小模上 $k$ 的值。然后似乎就可以在每个节点处理子树的合法性了，具体的：

在 $x$ 处看儿子们模后值为 $cnt$ 的个数和 $k-cnt$ 的个数是否相等。特殊的，为了处理对于每个伸出去的链，我们需要再加上一个 $n-sz_x$。

所以过程为：枚举 $k$，不是 $n-1$ 因数的直接打印 $0$，否则遍历树，在每个节点判断子树的合法性，时间复杂度 $O(n\sqrt n)$。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 100005 
using namespace std;
vector<int> q[Maxn],can[Maxn];
int sz[Maxn],cur[Maxn],n;
void solve(int x,int fa) {
    sz[x]=1;
    for(int u:q[x]) {
        if(u == fa)continue;
        solve(u,x);
        sz[x]+=sz[u];
        can[x].push_back(sz[u]);
    } if(sz[x]!=n)can[x].push_back(n-sz[x]);
}
bool check(int k) {
    for(int i=1;i<k;i++)
        cur[i]=0;
    for(int i=1;i<=n;i++) {
        int cnt=0;
        for(int u:can[i]) {
            if(u%k==0)continue;
            if(cur[k-u%k])cur[k-u%k]--,cnt--;
            else cur[u%k]++,cnt++;
        } if(cnt)return false;
    } return true;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        q[u].push_back(v);
        q[v].push_back(u);
    } solve(1,0);
    for(int i=1;i<n;i++)
        cout<<check(i);
    return 0;
}
```

---

