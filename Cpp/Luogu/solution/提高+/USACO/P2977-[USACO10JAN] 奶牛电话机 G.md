# [USACO10JAN] 奶牛电话机 G

## 题目描述

奶牛们建立了一个电话网络，对于这个题目可以将其视为一个有 $N$（$1 \le N \le 100{,}000$）个结点的无根树，为了方便将其编号为 $1\cdots N$。每个结点代表一个电话交换机，每条边代表用于连接两个交换机的电话线。第 $i$ 条边由该边连接的两个结点 $A_i$ 和 $B_i$ 表示（$1 \le A_i \le N, 1 \le B_i \le N, A_i \ne B_i$）。

有些交换机只有一条电话线连接到另一个交换机，这些是树的叶子结点，每个叶子结点都是一个位于奶牛田中的电话亭。

两只奶牛交流时的对话沿着两个奶牛所在节点之间的唯一的最短路径传递。一个交换机最多可以同时处理 $K$（$1 \le K \le 10$）个对话，并且在任何时候每个电话线上最多只能有一个对话。

假设每个叶子结点上都有一头奶牛，那么最多有多少对奶牛可以同时进行对话？当然，一头奶牛最多只能参与一个对话。

## 说明/提示

```plain
1   5          C1   C5 
|   |          ||   || 
2---4   -->    |2---4| 
|   |          ||   || 
3   6          C3   C6
```

考虑这个有 $6$ 个结点且 $K = 1$ 的电话树：

有四头分别位于节点 $1$、$3$、$5$ 和 $6$ 的奶牛。如果奶牛 $1$ 和奶牛 $3$ 交谈，奶牛 $5$ 和奶牛 $6$ 交谈，那么它们不会超过每个交换机的最大对话数，所以在这个样例中答案是 $2$（即有两对奶牛可以同时进行交谈）。

## 样例 #1

### 输入

```
6 1 
1 2 
2 3 
2 4 
4 5 
4 6 
```

### 输出

```
2 
```

# 题解

## 作者：jiayixuan1205 (赞：8)

## 题解：P2977 [USACO10JAN] Cow Telephones G
### 题意
给出一棵树，每个节点限定一个可通过的最大值 $k$，每条边最大可通过值为 $1$，叶子仅通过最短路连接，求最多多少对叶节点可同时连接。
### 算法
考虑贪心。
### 分析
最简单的贪心想法就是将可连接的最近的节点两两连接，但是如果涉及到跨子树的情况就不正确了，因此我们转变思路。
首先，容易想到，最优秀的情况是在每个子树中节点恰好两两配对且不超过父亲节点的最大承载量。那么，就可以分出下面两种情况：

- 子树内存在可以相连的节点就优先处理。
- 剩余跨子树的节点考虑通过最短可行路径连接。

分别处理即可。
### 代码展示
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e6+10; 
int n,k;
int res[N],val[N];
/*
   res:标记该子树是否有剩余节点未连接   
   val:记录这颗子树对答案的贡献 
*/ 
int ans;
int tot,head[N*2];

struct edge{
	int nex,to;
}e[N*2];

inline void add(int x,int y)//建边 
{
	tot++;
	e[tot].nex=head[x];
	e[tot].to=y;
	head[x]=tot;
}

inline void dfs(int x,int fa)//遍历 
{
	for(int i=head[x];i;i=e[i].nex)
	{
		if(e[i].to!=fa) 
		{
			dfs(e[i].to,x);
			if(res[e[i].to]==1)//子树内有剩余边 
			{
				if(res[x]==1)
				{
					val[x]++;//可贡献值++ 
					res[x]=0;
				}
				else if(val[x]!=k) res[x]=1;//有剩余 
			}
		}
	}
	ans+=val[x];
}

int main()
{
	cin>>n>>k;
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
		res[x]++;
		res[y]++;
	}
	dfs(1,0);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：⚡current⚡ (赞：2)

分享一个我觉得有点像树形dp但又感觉有点不像的做法(本蒟蒻判断不出来啊)

指定一个非叶子节点为树根，将给定的树转化为一棵有根树，对每个节点 $x$，维护两个值 $num[x]$ 和 $res[x]$

$num[x]$ 表示两端的牛都在 $x$ 的子树中且经过 $x$ 的电话线路数量，那么 $ans$ 就显然等于所有节点的 $num[x]$ 之和

$res[x]$ 表示在 $x$ 的子树中，但并未在 $x$ 的子树中匹配到打电话对象，且有能力与 $x$ 子树外的牛打电话(即保证经过$x$ 的电话数量小于 $k$)的牛的数量，通过一个节点所有儿子的 $res[x]$ 就可以转移得到这个节点的 $num[x]$ 和 $res[x]$

那具体是怎么转移的呢？

首先我们要注意到一个贪心，在最优解中，$res[x]$ 的值只有可能是 $0$ 或 $1$，若 $res[x] = 2$，设 $X$ 的子树中那两个未匹配节点分别为 $A$ 和 $B$，若将 $A,B$ 通过 $X$ 子树内的路径匹配在一起，$A,B$ 对答案做出的贡献不会变小，且对电话线上限的占用也不会变大，所以在 $k$ 的限制内使 $num[x]$ 尽量大一定是最优解

那么给所有叶子节点赋初值:```num[x] = 0, res[x] = 1```，然后从下往上转移，顺便再统计一下答案就好啦！如果还有什么不懂的看下代码吧，$CODE\downarrow$

```c++
#include<stdio.h>
#include<algorithm>
using std::min;

const int MAXN = 100005;
int last[MAXN], ver[MAXN<<1], nxt[MAXN<<1], d[MAXN], num[MAXN], res[MAXN], cnt, ans, k;

inline void add(int x, int y)
{
    nxt[++cnt] = last[x];
    last[x] = cnt;
    ver[cnt] = y;
    ++d[y];
    //统计度数是为了判断是否为叶子节点
}

void dp(int x, int from)
{
    int to;
    if(d[x] == 1)//叶子节点是????，赋初值
    {
        res[x] = 1;
        return;
    }
    for(int i = last[x]; i; i = nxt[i])
    {
        to = ver[i];
        if(to == from) continue;
        dp(to, x);
        res[x] += res[to];
        //用res[x]临时统计一下res[to]之和以便之后转移，想不出好的变量名所以不想再开一个变量
    }
    num[x] = min(k, res[x]>>1);//num[x]越多越好，但不能超出k的限制
    if(num[x] < k && res[x] > (num[x]<<1)) res[x] = 1;
    else res[x] = 0;
    ans += num[x];//统计答案
}

int main()
{
    int n, x, y;
    scanf("%d%d", &n, &k);
    for(int i = 1; i < n; ++i)
    {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    //如果有 n <= 2 的情况的话要特判一下
    if(n == 1) {putchar('0'); return 0;}
    if(n == 2) {putchar('1'); return 0;}
    for(int i = 1; i <= n; ++i)
        if(d[i] > 1)//找到一个非叶子节点为根
        {
            dp(i, 0);
            printf("%d", ans);
            return 0;
        }
}
```

---

## 作者：良月澪二 (赞：2)

每个点有一个容量，每条边有1的容量，问最多能使多少个点连通

显然两个点距离越近答案越优

所以我们从每个子树开始处理

标记每个子树还能不能有贡献

统计答案

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#define A 1000010
#define B 2010

using namespace std;
typedef long long ll;
struct node {
    int next, to;
}e[A];
int head[A], num;
int n, k, a, b, in[A], vis[A], f[A], ans;
void add(int fr, int to) {
    e[++num].next = head[fr];
    e[num].to = to;
    head[fr] = num;
    in[to]++;
}
void dfs(int fr, int fa) {
    if (in[fr] == 1) {
        vis[fr] = 1;
        return;
    }
    for (int i = head[fr]; i; i = e[i].next) {
        int ca = e[i].to;
        if (ca == fa) continue;
        dfs(ca, fr);
        if (!vis[ca]) continue;
        if (vis[fr]) {
            f[fr]++;
            vis[fr] = 0;
        }
        else if (f[fr] < k) vis[fr] = 1;
    }
    ans += f[fr];
}

int main(int argc, char const *argv[]) {
    // freopen("testdata.in", "r", stdin);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        add(a, b); add(b, a);
    }
    dfs(1, 0);
    cout << ans << endl;
}
```


---

## 作者：kuikuidadi (赞：1)

# 思路

每个非叶子节点有一个容量限制，每两个叶子节点配对要占用这两个点路径上所有点 $1$ 容量且每个叶子节点只能被匹配一次。问最多能匹配多少对？这个题显然是贪心，对于每个叶子节点、要尽量找近的叶子节点匹配（即两个节点的最近公共祖先最深的）。那么对于每棵由叶子节点和它们父亲节点组成的子树（二阶树）进行匹配，有两种情况：

1. 在子树内就能把所有叶子节点匹配完，或容量不足以及匹配完这棵子树中的所有叶子。这种情况就意味着这课子树匹配完了，不会再和别的子树匹配。

  2. 把这棵子树内匹配完还剩叶子没匹配且父亲点还用容量。这种情况可以给这棵子树的根节点（即上述父亲点）打上标记表示这棵子树有节点需要被匹配。

这样每次二阶树匹配完之后把剩下没匹配但能匹配的点再和相对较近的点匹配，就能得到最大匹配数。

# code


```cpp
#include<bits/stdc++.h>
#define N 2000001
using namespace std;
int n,m,ans,cnt,g[N],vis[N],head[N],du[N];
struct node{
	int to,nxt;
}edge[N];
void add(int u,int v){
	edge[++cnt]={v,head[u]};
	head[u]=cnt;	
}
void dfs(int u,int fa){
	if(vis[u]==1){
		g[u]=1;
		if(u!=1) return ;
	}
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		dfs(v,u);
		if(g[v]==1){
			if(g[u]==1){
				du[u]++;
				g[u]=0;
			}else if(du[u]!=m){
				g[u]=1;
			}
		}
	}
	ans+=du[u];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
		vis[u]++;
		vis[v]++;
	}
	dfs(1,0);
	cout<<ans;
}
```

---

## 作者：小手冰凉 (赞：1)

一道贪心


因为牛与牛之间打电话肯定是越近越好（如果牛A与B更近，C与D更近，A和B+C和D使用的节点数肯定少于A和C/D打+B和C/D打，且后者使用的节点中一定包含前者的节点）所以可以从叶节点开始贪心


（PS：个人不会严谨证明，只会XJBYY）


```cpp
//千万注意每条电话线只能同时打一个电话
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int head[N],tail[N*2],nxt[N*2];
int f[N],in[N];
int use[N];
int n,m,ans,t;
void addto(int x,int y)
{
    nxt[++t]=head[x];
    head[x]=t;
    tail[t]=y;
}
int dfs(int k,int fa)
{
    if(in[k]==1)return 1;
    int s=0;
    for(int i=head[k];i;i=nxt[i])
        if(fa!=tail[i]){
            s+=dfs(tail[i],k);
        }
    int x=s>>1;
    ans+=min(x,m);
    if(x>=m)return 0;
    else return s&1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        in[x]++;
        in[y]++;
        addto(x,y);
        addto(y,x);
    }
    for(int i=1;i<=n;i++)
        if(in[i]>1){dfs(i,0);break;}
    printf("%d",ans);
    return 0;
}
```

---

## 作者：TemplateClass (赞：0)

$\gdef \dp{\mathrm{dp}}$
$\gdef \son{\mathrm{son}}$
$\gdef \father{\mathrm{father}}$
$\gdef \res{\mathrm{res}}$
$\gdef \rem{\mathrm{rem}}$
$\gdef \and{\text{ and }}$
$\gdef \root{\mathrm{root}}$

一个感觉像 dp 又有点像贪心的做法。

我们设 $\dp _ {u, 0}$ 表示以 $u$ 为根的子树的通话对数之和，$\dp _ {u, 1}$ 表示这个子树向上传递的通话路径数。

首先如果 $u$ 是一个叶子结点，则 $\dp _ {u, 0} = 0, \dp _ {u, 1} = 1$。否则，记

$$\res _ u = \sum _ {v \in \son(u)} \dp _ {v, 0},\ m _ u = \sum _ {v \in \son(u)} \dp _ {v, 1}$$

然后我们进行本地的配对，显然本地最多形成 $t = \min\!\left(\left\lfloor\dfrac{m _ u}{2}\right\rfloor, K\right)$ 对通话，因为每对要消耗两条路径，那么 $\dp _ {u, 0} = \res _ u + t$。于是我们还剩下 $\rem = m _ u - 2 \times t$ 条路径，因此如果当前结点不是根节点且 $\rem \ge 1$ 且 $K - t \ge 1$ 则可以向上传递一条路径，即此时 $\dp _ {u, 1} = 1$ 否则 $ = 0$。

最后写一下完整的 dp 转移方程，没别的原因，就是看着比较帅而已。

$$\dp _ {u, 0} = \begin{cases} 0 & \son(u) = \varnothing \\ \displaystyle \left(\sum _ {v \in \son(u)} \dp _ {v, 0}\right) + \min\!\left(\left\lfloor\frac{\displaystyle\sum _ {v \in \son(u)} \dp _ {v, 1}}{2}\right\rfloor, K\right) & \text{Otherwise.} \end{cases}$$

$$\dp _ {u, 1} = \begin{cases} 1 & \son(u) = \varnothing \\ 1 & \father(u) \ne \varnothing \and \left( \displaystyle\sum _ {v \in \son(u)} \dp _ {v, 1} \right) - 2 \times \min\!\left(\left\lfloor\frac{\displaystyle\sum _ {v \in \son(u)} \dp _ {v, 1}}{2}\right\rfloor, K\right) \ge 1 \and K - \min\!\left(\left\lfloor\frac{\displaystyle\sum _ {v \in \son(u)} \dp _ {v, 1}}{2}\right\rfloor, K\right) \ge 1 \\ 0 & \text{Otherwise.} \end{cases}$$

最后答案就是 $\dp _ {\root, 0}$。

```cpp
#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

typedef std::pair<int, int> Res;
constexpr int N = 1e5 + 5;

int n, k, root = 0; std::vector<int> G[N];
#define chkroot(u) (!root && G[u].size() > 1 ? (u) : root)

Res solve_dfs(int u, int fa) {
	bool f = false; int sum = 0, m = 0;
	for(const auto& v : G[u]) {
		if(v == fa) continue;
		f = true; Res res_v = solve_dfs(v, u);
		sum += res_v.first, m += res_v.second;
	}
	if(!f) return {0, 1};
	int t = std::min(m >> 1, k), rem = m - (t << 1);
	return {sum + t, (int)(fa && rem >= 1 && k - t >= 1)};
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n >> k;
	for(int i = 1; i <= n - 1; ++i) {
		int u, v; std::cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
		root = chkroot(u), root = chkroot(v);
	}
	std::cout << solve_dfs(root, 0).first << "\n";
	
	return 0;
}
```

---

## 作者：qiliu (赞：0)

目前还没有 vector 存图的题解呢，那就交一发吧。

------

### 思路

考虑贪心。

首先，对于同深度的牛牛们，先让他们两两通话，这个时候我们就会有三种情况：

1. 所有牛牛刚好两两配成一对。

2. 他们父节点的通话机会满了。

3. 最终剩下了几头牛没有通话，且父节点通话机会没满。

对于第一种和第二种情况，显然不需要做过多讨论。而对于第三种，我们需要帮剩下的牛安排通话。

由于这个图是一棵树，而每一条边只能通过一个通话，所以在第三种情况只能通过父节点上传一头牛。由于通话无距离限制，所以通过不断的上传，这头牛可以成为其任意祖先节点的叶子结点。

所以我们用一个数组 $ cow $ 来记录此层有多少头牛牛需要匹配，于是其值就是他所有子节点的 $ cow $ 相加。此时此层的最大通话数显然是 $ \frac{cow}{2} $，在配完对后，我们要将配过对的牛减去，以便上传，这一部分结合上面的论证和代码应该很好理解。

### Code

有注释，请放心食用。

```cpp
#include<bits/stdc++.h>
#define int long long
#define DEBUG(x) cerr<<#x<<'='<<x<<endl
using namespace std;
const int N=100005;
int n,k; 
vector<int>a[N];//vector存图
int ans=0;//这就是最终结果
int cow[N];
void dfs(int s,int fa)
{
	if(a[s].size()==1)//判断叶子结点
	{
		cow[s]=1;//叶子结点显然只有一只待匹配的牛牛
		return;
	}
	for(int i=0;i<a[s].size();i++)
	{
		int to=a[s][i];
		if(to==fa)continue;
		dfs(to,s);
		cow[s]+=cow[to];\\把所有子节点的待处理的牛相加
	}
	int num;//当前节点最多通过的通话数
	num=min(k,cow[s]/2);
	if(num<k&&cow[s]>num*2)//即第三种情况
	cow[s]=1;//根据上面的推理知只可能为1或0
	else
	cow[s]=0;
	ans+=num;
	return;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>k;
    if(n==1)
    {
    	cout<<0;
    	return 0;
	}
	if(n==2)
	{
		cout<<1;
		return 0;
	}
    for(int i=1;i<n;i++)
    {
    	int u,v;
    	cin>>u>>v;
    	a[u].push_back(v);
    	a[v].push_back(u);
	}
	int hed;
	for(int i=1;i<=n;i++)
	{
		if(a[i].size()>1)
		{
			hed=i;//选取任意非叶子结点为根
			break;
		}
	}
	dfs(hed,0);
	cout<<ans;
    //fclose(stdin);
    //fclose(stdout);
	return 0;
}

```
由衷感谢每一位阅读此题解的人~

---

