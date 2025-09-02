# [蓝桥杯 2025 省 AB/Python B 第二场] 树上寻宝

## 题目描述

小蓝正在一棵含有 $n$ 个结点的树的根结点 $1$ 上，他准备在这棵树上寻宝。结点 $i$ 上有一个物品，价值为 $w_i$。然而，小蓝每次寻宝只能从根节点出发走不超过 $k$ 步，每步只能选择走 $1$ 条边或者 $2$ 条边，之后会自动拾取最终停留的结点上的物品并被传送回根结点。请求出小蓝最终能获得的物品的总价值。

## 说明/提示

### 样例说明

- 走 $0$ 步能到的结点：$1$；
- 走 $1$ 步能到的结点：$2, 3, 4$；
- 走 $2$ 步能到的结点：$3, 4, 5, 6$；

因此能到的结点为：$1, 2, 3, 4, 5, 6$，能获得的总价值为 $22$。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 15$；
- 对于所有评测用例，$0 \leq k < n \leq 10^5$，$1 \leq w_i \leq 10^6$，$1 \leq u_i, v_i \leq n$。

## 样例 #1

### 输入

```
8 2
6 3 3 1 5 4 3 4
1 2
2 3
2 4
4 5
5 6
6 7
7 8```

### 输出

```
22```

# 题解

## 作者：Clare613 (赞：5)

## 思路
题目说小蓝最多走 $k$ 步，每一步可以跨过 $1$ 条边或 $2$ 条边，翻译成人话就是可以得到深度不大于 $2k + 1$ 的点权，于是我们只要求出每个点的深度，点权加起来输出即可。\
肯定有人不会求树的深度，我们可以用 DFS 来找，建一下边，从一开始跑，不断加就可以求出树的深度了！
## code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
vector<int> g[100005];
int shen[100005],w[100005],ans;
void dfs(int x,int fa){
	for(auto i:g[x]){
		if(i==fa) continue;
		shen[i]=shen[x]+1;
		dfs(i,x);
	}
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	shen[1]=1;
	dfs(1,0);
	for(int i=1;i<=n;i++){
		if(shen[i]<=2*k+1) ans+=w[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：hwh_qwq (赞：3)

因为小蓝每步可以走最多 $2$ 条边，每次可以走最多 $k$ 步，所以他最多只能走到距离根节点不超过 $2 \times k$ 的点，即深度不超过 $2 \times k + 1$ 的点。

对于每个深度 $ \le 2 \times k+1 $ 的点，我们可以先走 $ \lfloor \text{深度}\div2 \rfloor $ 步，每步走两条边，如果深度为偶数，再走一步即可。

通过上面这样的走法，所有深度不超过 $2 \times k + 1$ 的点都可以在 $k$ 步之内到达，又因为寻宝的次数没有限制，所以我们可以获得这些点上的所有物品，答案即为深度不超过 $2 \times k + 1$ 的点 $i$ 的 $w_i$ 之和。

一些需要注意的地方：

- 存图的时候记得双向存边。
- 根节点的价值也要算入答案。
- 答案可能会超过 `int` 的范围，要开 `long long`。

代码：
```
#include<iostream>
#include<vector>
using namespace std;
int n,k;
int w[100005],deep[100005],vis[100005];
vector<int> tr[100005];
void dfs(int id,int fa,int dep){
	if(vis[id]==1) return;
	vis[id]=1;
	deep[id]=dep;
	for(int i=0;i<tr[id].size();i++){
		if(tr[id][i]!=fa) dfs(tr[id][i],id,dep+1);
	}
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<n;i++){
    	int u,v;
    	cin>>u>>v;
    	tr[u].push_back(v);
    	tr[v].push_back(u);
	}
	dfs(1,0,0);
	long long ans=0;
	for(int i=1;i<=n;i++){
		if(deep[i]<=2*k) ans+=w[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：clarinet_pht (赞：2)

# P12343 [蓝桥杯 2025省 AB/Python B 第二场] 树上寻宝

本题思路 dalao 们已经讲的很清楚了，本蒟蒻来给初学者讲一些细节，精通的 dalao 可自行跳过。

## 思路
因为每次只能走 $1$ 或 $2$ 步，所以只需要把深度小于等于 $2k+1$ 的节点的值加起来就可以了。

具体走法：

令节点 $i$ 的深度为 $x_i$。

奇数：需走 $(x_i-1)\div2$ 步长度为 $2$ 即可。

偶数：则先走 $x_i\div2$ 步长度为 $2$，再走 $1$ 步长度为 $1$ 便可。

## 搜索
从节点 $1$ 开始，每次对所有不是它父节点的点进行搜索，所以任意点的深度就是它的父节点的深度加一。

函数中记录 $father$ 是为了防止双向边导致死循环。

具体搜索如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/kl9h0ifv.png)

红色的数字是深度，虚线是假设的点。

时间复杂度为线性，可以通过此题。

## 完整代码如下

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct P{int u,v,nxt;}ed[2000010];
int hd[2000010],dep[2000010],tot;
int sum[200010];
void add(int u,int v)
{
	ed[++tot].u=u;
	ed[tot].v=v;
	ed[tot].nxt=hd[u];
	hd[u]=tot;
}
void creatst(int now,int father)
{
	dep[now]=dep[father]+1;//累加深度
	for(int i=hd[now];i>0;i=ed[i].nxt)
		if(ed[i].v!=father)
			creatst(ed[i].v,now);//不等于来的父节点就向下搜索
}
signed main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>sum[i];
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);//建双向边，不会链式前向星可自行查阅
	}
	creatst(1,0);//深搜确定深度
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(dep[i]<=k*2+1)
			ans+=sum[i];
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Bill_luogu (赞：2)

## 题目思路：
题目要求从根节点 $1$ 出发走不超过 $k$ 步，设根节点的深度为 $1$ ，则走不超过 $k$ 步最多走到深度为 $2\times k+1$ 的点（因为最多是 $k$ 步都走 $2$ 条边，深度为 $2\times k$ ，加上根节点的深度，所以最多走到深度为 $2\times k+1$ 的点）。

从根节点开始遍历，每遍历到一个点 $x$ 答案就累加上 $w_{x}$ ，然后遍历点 $x$ 的所有出边，如果当前 $x$ 的深度加一小于等于 $2\times k+1$ ，那就遍历这条边，最后输出答案。
## AC Code：
C++：
```cpp
#include<iostream>
#include<vector>
using namespace std;
vector<int> v[100010];
long long ans;//一定要开 long long！！！
int n,k,w[100010];
bool vis[100010];
void dfs(int x,int dep)//一定要在 dfs 里计算深度，否则会 WA 两个点。
{
	ans+=w[x];
	for(int i=0;i<v[x].size();i++)
    {
    		if(dep+1<=k*2&&!vis[v[x][i]])//判断是否能走
    		{
    			vis[v[x][i]]=1;//防止重复走
    			dfs(v[x][i],dep+1);
    		}
    }
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>w[i];
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	vis[1]=1;
	dfs(1,0);
	cout<<ans;//输出答案
	return 0;
} 
```

---

## 作者：CJR_Rain (赞：2)

## Solution

对于所有节点，设它的深度为 $x$（根结点深度为 $0$），那么小蓝可以通过走 $\lfloor\frac{x}{2}\rfloor$ 次 $2$ 条边加上 $x\bmod 2$ 次 $1$ 条边来到达这个节点，这是耗费步数最少的走法。

显然，$\forall 0≤x≤2k,\ \lfloor\frac{x}{2}\rfloor+x\bmod 2≤k$.

且，$\forall 2k<x,\ \lfloor\frac{x}{2}\rfloor+x\bmod 2>k$。

因此，小蓝能且仅能走到深度小于等于 $2k$ 的节点。

因为寻宝次数没有限制，因此题目可以理解为求所有深度小于等于 $2k$ 的节点的权值之和。

## Code

### 算法

链式前向星，BFS。

链式前向星存边，然后 BFS 遍历求和，这是显而易见的解法。至于 DFS，其实做这题更为方便，实现就留给读者完成吧。

### 细节

- 因为 $n$ 取最大值时为 $10^5$，$w_i$ 取最大值时为 $10^6$，而本题的数据完全有可能使小蓝能够走到所有节点，所以对于极端数据，答案为 $10^5\times 10^6=10^{11}$。$2^{32}≤10^{11}<2^{63}$，`unsigned int` 也存不下，得开 `long long`。

- 本题输入边时只说 $u_i$ 和 $v_i$ 间有一条边，没说 $u_i$ 是 $v_i$ 的父节点，因此即使耗费步数最少的走法不会出现向上走的情况，存边时也要存双向边。

### 时间复杂度

本题只需要访问所有深度小于等于 $2k$ 的节点，且每个节点只需要访问一次，因此设 $m$ 为深度小于等于 $2k$ 的节点的数量，那么时间复杂度为 $O(m)$。

### 代码

码风奇怪，内含各种 C++ 的奇怪语法和特性，仅供参考：

```cpp
#include <bits/stdc++.h>

#define IS std::cin.tie(nullptr) -> std::ios::sync_with_stdio(false)
#define OS std::cout.tie(nullptr) -> std::ios::sync_with_stdio(false)
#define set_nega1(x) memset(x, -1, sizeof(x))

using namespace std;

struct edge {
    
    int to, nxt;
    
    inline edge(int to = -1, int nxt = -1) {
        
        this -> to = to;
        this -> nxt = nxt;
        
        return;
    }
    
    inline ~edge() {
        
        to = nxt = -1; return;
    }
    
} edges[200005]; int idx = 0, head[100005];

int n, k, value[100005];

inline void add(int u, int v) {
    
    edges[idx] = edge(v, head[u]); head[u] = idx++; return;
}

queue <int> id; bitset <100005> vis;

inline long long bfs(int depth, int len, long long res) {
    
    while(len-- > 0) {
        
        int front = id.front();
        id.pop();
        
        res += value[front];
        
        for(int cur = head[front]; cur != -1; cur = edges[cur].nxt) {
            
            int to = edges[cur].to;
            
            if(vis[to] == false) {
                
                vis[to] = true; id.emplace(to);
            }
        }
    }
    
    if(depth >= k || id.empty() == true) {
        
        return res;
    }
    
    return bfs(depth + 1, id.size(), res);
}

signed main() {
    
    IS;
    OS;
    
    cin >> n >> k; k <<= 1;
    
    for(int i = 1; i <= n; ++i) {
        
        cin >> value[i];
    }
    
    set_nega1(head); for(int i = 1; i < n; ++i) {
        
        int u, v;
        cin >> u >> v;
        
        add(u, v); add(v, u);
    }
    
    id.emplace(1); vis[1] = true;
    
    return void(cout << bfs(0, id.size(), 0)), 0;
}
```

---

## 作者：l15130880055 (赞：2)

## [蓝桥杯 2025 省 AB/Python B 第二场] 树上寻宝 题解

### Problem
给定一棵 $n$ 个节点的树，树有点权，能走 $k$ 步，每步可以走一条边或者两条边，能走到的点的点权之和。

### Solution

因为每步可以走一条边或两条边，所以只要这个点距离根节点不超过 $2 \times k$ 条边，就一定可以走到，随便 dfs 一下求每个点距离根节点多少条边即可，其实就是令根节点深度为 $0$ 求所有点的深度。


最后把满足条件的点的点权加起来即可，时间复杂度线性。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
constexpr int maxn = 1e6 + 7;
int dep[maxn], n, k, v[maxn], ans;
std::vector<int> ve[maxn];

inline void dfs(int u, int fa){
	for(int i = 0; i < ve[u].size(); i++){
		int v = ve[u][i];
		if(v != fa){
			dep[v] = dep[u] + 1;
			dfs(v, u);
		}
	}
}
int32_t main(){
	std::cin.tie(nullptr) -> std::ios::sync_with_stdio(false);
	std::cin >> n >> k;
	for(int i = 1; i <= n; i++){
		std::cin >> v[i];
	}
	for(int i = 1, u, v; i < n; i++){
		std::cin >> u >> v;
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	dfs(1, 0);
//	for(int i = 1; i <= n; i++){
//		std::cout << dep[i] << ' ';
//	}
	for(int i = 1; i <= n; i++){
		if(dep[i] <= 2 * k){
			ans += v[i];
		}
	}
	std::cout << ans << '\n';
	return 0;
} 
```

---

## 作者：ykhk10710o_o (赞：1)

# 题目 
小蓝从根结点出发，每次走一条边或两条边，若能走 $k$ 次，问能收集到节点的最大价值为多少。
# 思路
每次能走一条边或两条边，能走 $k$ 次，说明能走到深度 $\le 2 \times k$ 的节点，所以我们把深度 $\le 2 \times k$ 的节点的价值相加就得到最大价值了。
# Code

```cpp
#include<bits/stdc++.h>
#define int long long //不开long long 见祖宗
using namespace std;
int n,k;
int a[1010101];
vector<int>e[1010101];
int x,y;
int s[1010100];
void dfs(int now,int fa){
	for(auto u:e[now]){
		if(u==fa)continue;
		s[u]=s[now]+1;
		dfs(u,now);
	}
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	} 
	dfs(1,0);
	int ans;
	for(int i=1;i<=n;i++){
		if(s[i]<=2*k){
			ans+=a[i];
		}
	}
	cout<<ans;
}
```

---

## 作者：sdsswyd (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12343)  
# 思路
普通做法：一个点一个点判断下去，若该点能够在 $k$ 次及以内搜到，就将这个点的 $w_i$ 加入答案中，但由于对于所有评测用例，$0 \leq k < n \leq 10^5$。这个时间复杂度太高，容易 TLE。  
**考虑改进算法**：对于每一步，都有最多 $2$ 条边可以走，而现在有 $k$ 步，则最多有 $2 \times k$ 条边可以走。也就是搜到的树的**深度**最多为 $2 \times k + 1$。  
那么，整道题的思路就很简单了，先从 $1$ 开始作为根，进行一次树的遍历，记录各个节点的深度（$1$ 号点的深度可以记作 $0$），在进行整体遍历，判断结点 $i$ 的深度是否小于 $2 \times k + 1$，若条件成立，就将这个点的 $w_i$ 加入答案中。最后输出答案。
# 代码

```cpp
//#pragma G++ optimize(3)
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
long long ans;
vector<int>a[100005];
int e[100005],flag[100005];
long long val[100005];
int n,k;
void dfs(int id,int x){
	e[id]=x;
	flag[id]=1;
	for(int i=0;i<a[id].size();i++){
		if(flag[a[id][i]]==0){
			dfs(a[id][i],x+1);
		}
	}
	return ;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>val[i];
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
        if(e[i]<=k*2)ans+=val[i];
    }
    cout<<ans;
	return 0;
}

```

---

## 作者：wnqnld_llx (赞：1)

## 题目大意
在一棵含有 $n$ 个结点的树的根结点 $1$ 上。结点 $i$ 上有一个物品，价值为 $w_i$。小蓝每次寻宝只能从根节点出发走不超过 $k$ 步，每步只能选择走 $1$ 条边或者 $2$ 条边，之后会自动拾取最终停留的结点上的物品并被传送回根结点。请求出小蓝最终能获得的物品的总价值。

## 问题转换

因为每次可以走一或二步，且最多可以走 $k$ 次，所以对于节点 $x$，如果 $x$ 到根节点的距离 $\le2\times k$ 那么这点就可以走到。我们可以用深搜遍历这棵树。我们用 $dis$ 记录每个节点到根节点的距离。$dis_i=dis_f+1$ 其中 $f$ 是 $i$ 的父亲。  

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
int w[maxn],dis[maxn],ans;
vector <int> tr[maxn];
void dfs(int x,int fa){//dfs，第一个表示正在搜第几个点，第二个表示它的父亲。
	for(auto son:tr[x]){
		if(fa==son) continue;//防止一直在两个点出不去。
		dis[son]=dis[x]+1;
		dfs(son,x);
	}
}
signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		tr[x].push_back(y);//双向边
		tr[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		if(dis[i]<=2*k) ans+=w[i];
		//cout<<dis[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：chenxinran12 (赞：0)

### 题意分析
给定一个 $n$ 个点的树，其中有 $n-1$ 条边，你可以从节点 $1$ 走 $1$ 到 $k$ 步，每一步可以走 $1$ 到 $2$ 条边，问可以走到的所有地方的 $w$ 的和。
### 思路
我们考虑可以到达的点到点 $1$ 的距离：

- 当点 $i$ 到点 $1$ 的距离为 $0$ 时，我们可以走 $0$ 步到达，答案加上 $w_i$。
- 当点 $i$ 到点 $1$ 的距离为 $1$ 时，我们可以走 $1$ 步到达，答案加上 $w_i$。
- 当点 $i$ 到点 $1$ 的距离为 $2$ 时，我们可以走 $1$ 步到达，答案加上 $w_i$。

  以此类推。

- 当点 $i$ 到点 $1$ 的距离为 $x$ 时，我们可以走 $\lceil\frac{x}{2}\rceil$ 步到达，答案加上 $w_i$。

所以我们容易得知：若点 $i$ 到点 $1$ 的距离小于等于 $k$ 的 $2$ 倍，则这个点可以到达，把所有可以到达的点的值加上就行了。
### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,w[100002],u,v,head[200002],tot,dep[100002],ans;
struct edge
{
	int v,nxt;
}eg[400002];
void add(int u,int v)
{
	eg[++tot].v=v;
	eg[tot].nxt=head[u];
	head[u]=tot;
}
void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=eg[i].nxt)
	{
		int v=eg[i].v;
		if(v==fa) continue;
		dfs(v,u);
	}
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<n;i++)
    {
    	cin>>u>>v;
    	add(u,v);
    	add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
		if(dep[i]-1<=k*2) ans+=w[i];
	cout<<ans;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[P12343 [蓝桥杯 2025 省 AB/Python B 第二场] 树上寻宝](https://www.luogu.com.cn/problem/P12343)

## Solution
给定一棵包含 $n$ 个节点的树，根节点为 $1$。每个节点 $i$ 有一个价值 $w_i$。从根节点出发，每次移动可以选择走 $1$ 条边或 $2$ 条边（不能回头），最多进行 $k$ 次移动。求所有可达节点的价值之和。

我们应计算在移动规则下从根节点可达的所有节点的价值总和。

核心是处理每一步可走 $1$ 条边或 $2$ 条边的情况，并避免重复访问节点。

采用广度优先搜索（BFS）的改进算法，同时处理一步和两步移动，确保记录每个节点的最小步数（移动次数）。

### 细节
- 两步移动处理：通过 $w ≠ u$ 确保不走回头路，且两步移动仍记为 $dist[u] + 1$ 步。

- 复杂度控制：每个节点和边最多处理一次，时间复杂度为 $O(n)$。

## Code
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> w(n + 1), dist(n + 1, -1);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                if (dist[v] <= k) {
                    q.push(v);
                }
            }
            
            for (int w : adj[v]) {
                if (w != u && dist[w] == -1) {
                    dist[w] = dist[u] + 1;
                    if (dist[w] <= k) {
                        q.push(w);
                    }
                }
            }
        }
    }
    
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] != -1 && dist[i] <= k) {
            sum += w[i];
        }
    }
    
    cout << sum << "\n";
    return 0;
}
```

---

## 作者：Innate_Joker (赞：0)

# [P12343 [蓝桥杯 2025 省 AB/Python B 第二场] 树上寻宝](https://www.luogu.com.cn/problem/P12343)

> 来个用宽搜做的吧（求

## 思路

### 题目分析

题意简化：遍历一棵树的节点，可以走 $k$ 次，**可以走一条边或两条边**，求最多能获得多少“物品的价值”。

要遍历一棵树，限制层数，很明显用宽度优先搜索来做，比较简单吧。因为一次可以走两条边，所以最大深度应为 $k \times 2$ 。

### 如何宽搜

还是要会到这个最根本的问题，其实就是宽搜模板，只不过多了个计算层数的步骤。用一个队列来保存节点，每搜到一个就把它压进队列。每次循环取出头结点，遍历头结点所有链接的边，如果满足条件（没有遍历过且深度不超过 $k \times 2$），就压进队列，增加答案，重复这些步骤。

## Code

```cpp
#include <vector>
#include <queue>
#include <utility>
#include <iostream>
using namespace std;
int w[100005];
bool vis[100005];
vector <int> map[100005];
int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		map[u].push_back(v);
		map[v].push_back(u);
	}
	queue <pair<int, int> > q; //分别用来存是那个点和深度的
	q.push({1, 0});
	long long ans = 0;
	ans += w[1];
	vis[1] = true;
	do {
		int t = q.front().first, step = q.front().second;  //取出队首
		q.pop(); //弹出队首
		int len = map[t].size();
		for (int i = 0; i < len; i++) { // 遍历连接 t 的每一个节点
			if (vis[map[t][i]] == false && step + 1 <= k * 2) {
				ans += w[map[t][i]];
				vis[map[t][i]] = true;
				q.push({map[t][i], step + 1});
			}
		}
	} while (!q.empty()); // 当节点全部弹出且无法搜到新的节点时搜索结束
	cout << ans;
	return 0;
}
```

---

## 作者：Chengqijun2012 (赞：0)

本道题考察树的遍历，也是一道深搜板子题。

前置芝士：[深度优先搜索（简称深搜）。](https://blog.csdn.net/Huberyxiao/article/details/105017214)

[题目传送门。](https://www.luogu.com.cn/problem/P12343)

### 解题思路：
首先观察题目我们可以发现，小蓝每次最多只能走 $k$。我们考虑走的距离最大的情况，就是能走 $2 \times k$ 条边。我们设根节点的深度为 $0$，那么能走到的最远的节点深度就一定是 $2 \times k$。代码就是深搜模板加上深度的限制，答案用一个变量累加起来即可。

想要更具体的解释请注释。

AC Code：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
#include <cstdio>
#include <cmath>
#define ll long long
#define PU push_back
#define MP make_piar
#define P pair<int, int>
using namespace std;
const int N = 1e5 + 5;
ll n, k, p[N], ans;      //一定要开long long！！！血的教训……
vector<ll> g[N];

inline ll read(){      //快读，可以用cin代替
	ll f = 1, x = 0;
	char c = getchar();
	while(c < '0' || c > '9'){if(c == '-') f = -1; c = getchar();}
	while('0' <= c && c <= '9') x = x * 10 + (ll)(c - '0'), c = getchar();
	return x * f; 
}

void DFS(ll st, ll u, ll fr){      //st为当前节点的深度，u为当前节点的编号，fr为当前节点的父节点
	ans += p[u];
	p[u] = 0;
	if(st + 1 > (k << 1)) return;      //如果当前节点的深度已经到达小蓝能走的步数的极限，就没必要继续遍历了，直接返回
	for(ll v : g[u]) if(v != fr) DFS(st + 1, v, u);      //因为是无向图，所以遍历子节点时要注意不要走回头路
}

int main(){
	n = read(), k = read();
	for(ll i = 1; i <= n; i++) p[i] = read();
	for(ll i = 1, u, v; i < n; i++){
		u = read(), v = read();
		g[u].PU(v);
		g[v].PU(u);      //一定要连无向边！！！
	}
	DFS(0, 1, -1);      //把根节点的父节点设为-1
	cout << ans << "\n";
	return 0;
}
```
完结撒花！！！

---

## 作者：W_C_B_H (赞：0)

观察可得，一个节点可以在 $k$ 步内从根节点到达当且仅当其深度 $dep$（根节点的深度为 $1$）小于等于 $2k+1$（对于深度是奇数的节点，从根节点连续 $(\dfrac{dep-1}{2})$ 次向下走 $2$ 步即可，否则从根节点连续 $(\dfrac{dep}{2}-1)$ 次向下走 $2$ 步，再向下走 $1$ 步即可）。

故可以使用 dfs 对树进行遍历，在遍历到一个节点 $u$ 时将答案加上 $w_u$，如果当前深度小于等于 $2k$ 则继续往下遍历（因为越往下深度越大，所以深度超过 $2k+1$ 的部分无需遍历）。

时间复杂度 $O(n)$，可以通过本题。

Code：

```python
# 初始化
N = 100005
e = [[] for _ in range(N)]
ans = 0

# 深搜
def dfs(u, fa, dep):
    global ans
    ans += w[u - 1]
    if dep <= k * 2:
        for v in e[u]:
            if v != fa:
                dfs(v, u, dep + 1)

# 输入
n, k = map(int, input().split())
w = list(map(int, input().split()))
for i in range(n - 1):
    u, v = map(int, input().split())
    e[u].append(v)
    e[v].append(u)

# 计算
dfs(1, 0, 1)

# 输出
print(ans)
```

---

## 作者：Yi_chen123 (赞：0)

## 思路

题目的意思大概是这样的：小蓝可以从树的根节点向下走 $k$ 次，每一次可以走 $1$ 或 $2$ 条边，求所有可以走到地方物品的总价值。\
走 $k$ 次，每次最多走 $2$ 条边，说明什么？只能在深度 $\le 2k$ 的地方玩呀，~~再深就走不动了。~~\
因此呢，我们使用 DFS（深度优先搜索）算法，求出每个节点的深度（根节点的深度为 $0$），再统计所有深度 $\le 2k$ 的所有节点的总价值即可。

## 正解

```cpp
#include<bits/stdc++.h>
#define int long long //记得开 long long
using namespace std;

vector<int> G[114514]; //存树
int depth[114514]; //存深度
int w[114514]; //存价值
inline int rd(){
    int f = 1, k = 0;
    char c = getchar();
    while(!isdigit(c)){
    	if(c == '-') f = -1;
        c = getchar();
	}
	while(isdigit(c)){
        k = k * 10 + c - '0';
        c = getchar();
	}
	return k * f;
}

void dfs(int now, int fath){ //参数 now 为当前节点，fath 为其父节点
	for(int i = 0; i < G[now].size(); ++i){
		int u = G[now][i];
		if(u != fath){
			depth[u] = depth[now] + 1; //子节点深度 = 父节点深度 + 1
			dfs(u, now);
		}
	}
}
signed main(){
	int n = rd(), k = rd();
	for(int i = 1; i <= n; ++i) w[i] = rd();
	for(int i = 1; i < n; ++i){
		int u = rd(), v = rd();
		G[u].push_back(v); //存双向边哦
		G[v].push_back(u);
	}
	dfs(1, 0);
	
	int ans = 0;
	for(int i = 1; i <= n; ++i){
        // cout << depth[i] << endl;
		if(depth[i] <= 2 * k) ans += w[i];
	}
	cout << ans;
	return 0;
}
```

---

