# 完美的服务 Perfect Service

## 题目描述

一个网络中有 $N$ 个节点，由 $N-1$ 条边连通，每个节点是服务器或者客户端。如果节点 $u$ 是客户端，就意味着 $u$ 所连接的所有点中有且仅有一台服务器。求最少要多少台服务器才能满足要求。

# 题解

## 作者：CodyTheWolf (赞：37)

## 一道树形DP！
### 这里详细讲一下那3个方程的转移~~（吐槽某篇题解，什么某个是某个是）~~
### ~~有帮助的话希望右上角给个赞让更多需要的朋友看到qwq~~
------------
### 为了能覆盖到所有的情况，我们设三个状态
-	$dp[x][0]$：x是服务器，孩子是不是服务器均可 
-	$dp[x][1]$：x不是服务器，x的父亲是服务器，x的孩子不能是服务器 
-	$dp[x][2]$：x不是服务器且x的父亲不是服务器，x的孩子必须有且仅有一个是服务器。

-	这里借用一下某篇~~被吐槽的~~题解的说明

### 对于$dp[x][0]$：
-	这个状态就是在x处放上一个服务器，那么我们思考一下，从儿子那里转移的话，$dp[v][0]$，$dp[v][1]$是符合我们要求的，而$dp[v][2]$的定义说了，v的父亲，也就是x不能是服务器，是矛盾的。

-	所以我们从$dp[v][0]$，$dp[v][1]$转移过来就好啦，而且在这两个中只能转移一个，我们要最小答案所以每次枚举儿子的时候选最小的一个。$dp[x][0]$对所有的儿子，设某个为v，也就是：

-	### $dp[x][0]=\sum min(dp[v][0],dp[v][1])+1,v \in sons$

### 对于$dp[x][1]$：
-	这个状态就是在x的父亲f上放服务器，因为周围只能存在一台服务器，所以x的孩子不能是服务器。这个转移也非常简单。

-	因为孩子不能是服务器，所以孩子的孩子必须是服务器，不然孩子周围就没有服务器了。孩子的情况刚好符合我们的$dp[v][2]$，所以把他们求和就好啦。

-	### $dp[x][1]=\sum dp[v][2],v \in sons$

### 对于$dp[x][2]$：
-	这个状态是最难想的一个，定义是点x周围存在一台服务器，且是它的儿子，所以父亲肯定不能有服务器。

-	我们再考虑一下其儿子的情况，如果我们选定一个儿子v，让他拥有服务器，那么，设Vi为x的其他儿子，那么很明显：

-	### $dp[x][2]=min(dp[x][2],dp[v][0]+\sum dp[Vi][2])$
-	### $v \in sons,i \in sons,  Vi \neq v$

-	这样的话，我们需要花费$\Theta \left ( n \right )$枚举$v$，$\Theta \left ( n \right )$求和，然而$n \geq 1e4$，复杂度是$\Theta \left ( n^2 \right )$，肯定是会T掉的。这样的话，我们看看能不能去掉一个$\Theta \left ( n \right )$：

-	逆向思维：求和的话，能不能通过一个集合减去掉一个元素得到呢？再观察一下我们的三个状态，我们是可以推出上面的那个$\sum$的

-	因为$\sum$是我们所有非v儿子的集合，而$dp[x][1]$刚好是去掉所有儿子的结果，这个时候加上$dp[v][0]$不就完成嘛~

-	仔细想想，我们的状态有重叠，$dp[x][1]$还含有v不是服务器的情况，我们需要减去这个情况。

-	v不是服务器有两种情况，$dp[v][1]$和$dp[v][2]$，但对于$dp[x][1]$，我们的x是不能有服务器的，这个状态是会包括v的父亲x的。所以只有$dp[v][2]$（父亲和自己都不能是服务器）符合我们的要求，这样我们的思路就清晰了:

-	先算上去掉儿子的全集$dp[x][1]$，因为我们要v儿子含有服务器，加上$dp[v][0]$，又因为v在全集处有重叠状态（即去掉的状态），所以减去$dp[v][2]$

- 	### 即：

-	### $dp[x][2]=min(dp[x][2],dp[x][1]-d[v][2]+d[v][0]),v \in sons$

------------
## 经过上面的推导，我们得出三个转移方程：

-	### 1.$dp[x][0]=\sum min(dp[v][0],dp[v][1])+1,v \in sons$

========

-	### 2.$dp[x][1]=\sum dp[v][2],v \in sons$

========

-	### $3.dp[x][2]=min(dp[x][2],dp[x][1]-d[v][2]+d[v][0]),v \in sons$

### 并且3.由下面优化而来

-	### $dp[x][2]=min(dp[x][2],dp[v][0]+\sum dp[Vi][2])$
-	### $v \in sons,i \in sons,  Vi \neq v$

------------
## 但是要注意！3中是含有2的，所以我们的更新顺序是1->2->3
------------
## 相似题目推荐w
### [P2279 [HNOI2003]消防局的设立（相似但是高级那么点qwq？）](https://www.luogu.org/problemnew/show/P2279)
------------
### DP题主要是想法，而且代码很容易能看懂，就不注释了。（真的不懂可以私信我哒qwq
## CODE:
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 5, maxm = maxn << 1, inf = maxn;
int head[maxm], nxt[maxm], v[maxm], cnt, root;
int dp[maxn][3];
int n, opt;

inline void addline(int x, int y) { v[cnt] = y, nxt[cnt] = head[x], head[x] = cnt++; }

inline void dfs(int x, int f)
{
    dp[x][0] = 1, dp[x][1] = 0, dp[x][2] = inf;
    for (int i = head[x]; ~i; i = nxt[i])
        if (v[i] != f)
        {
            dfs(v[i], x);
            dp[x][0] += min(dp[v[i]][0], dp[v[i]][1]);
            dp[x][1] += dp[v[i]][2];
        }
    for (int i = head[x]; ~i; i = nxt[i])
        if (v[i] != f)
            dp[x][2] = min(dp[x][2], dp[x][1] + dp[v[i]][0] - dp[v[i]][2]);
    return;
}

signed main(void)
{
    while (true)
    {
        memset(head, -1, sizeof head);
        cnt = 0;

        scanf("%d", &n);
        for (int i = 1, x, y; i < n; i++)
            scanf("%d %d", &x, &y), addline(x, y), addline(y, x);

        root = rand() % n + 1, dfs(root, 0);
        printf("%d\n", min(dp[root][0], dp[root][2]));

        scanf("%d", &opt);
        if (opt == -1)
            break;
    }
    return 0;
}
```
------------
[小广告：自己的Luogu博客（因为只有一个模板库，所以只贴这个了w，各种方面的模板都有w~）](https://yu123123.blog.luogu.org/mu-qian-di-mu-ban-ku)

---

## 作者：Nanchtiy (赞：17)

刷紫书DP题ing
### 思路
参考lrj紫书 ~~不喜勿喷~~      
1. d(u,0)：u是服务器，孩子是不是服务器均可 
2. d(u,1)：u不是服务器，u的父亲是服务器，u的孩子不能是服务器 
3. d(u,2)：u不是服务器且u的父亲不是服务器，u的孩子必须有且仅有一个是服务器。

前两个状态方程好写
那么d(u,2)呢？
d(u,2)就会等于 **他儿子全都不是 减去某个不是 再加上某个是** 这是这道树形DP的难点
 
 因此 状态方程：d(u,2) = Min(d(u,1)-d(v,2)+d(v,0)) |v是u的孩子 
 
 详细解释见代码~
 
 ### 代码
 ```
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
#define maxn 10010
vector<int> sons[maxn];
int dp[maxn][3];
int n;
void search(int u,int father)
{
	dp[u][0]=1;//本身算一个 
    dp[u][1]=0;
    dp[u][2]=maxn;//要查找 先定义成最大 
    for(int i=0;i<sons[u].size();i++)
    {
    	if(sons[u][i]!=father)//如果不是父亲 就是儿子 
    	{
    		search(sons[u][i],u);//递归查找 
    		dp[u][0]+=min(dp[sons[u][i]][0],dp[sons[u][i]][1]);//如果他是 儿子可以是或者不是 
    		dp[u][1]+=dp[sons[u][i]][2];//如果他不是 但他父亲是 儿子都不是 
		}
	}
	for(int i=0;i<sons[u].size();i++)
	{
		if(sons[u][i]!=father)
		dp[u][2]=min(dp[u][1]-dp[sons[u][i]][2]+dp[sons[u][i]][0],dp[u][2]);
		//如果他不是 他父亲也不是 那么就是他儿子全都不是减去某个不是再加上某个是 
	}
}
int main()
{
	while(scanf("%d",&n)==1)
	{
		int x,y;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);//存边 
			sons[x].push_back(y);
			sons[y].push_back(x);
		}
		search(1,-1);
		printf("%d\n",min(dp[1][0],dp[1][2]));//答案在第一个是服务器
		                                      //或者第一个不是但是儿子之一是 
		scanf("%d",&x);//数据结束 
		if(x==-1)
		break;
		for(int i=1;i<=n;i++)//初始化 
        sons[i].clear();
        memset(dp,0,sizeof(dp));
	}
}
```

---

## 作者：Otue (赞：3)

状态定义：

* $f_{u,0}$ 表示 $i$ 是服务器，则每个子节点可以是服务器也可以不是。

* $f_{u,1}$ 表示 $i$ 不是服务器，但 $i$ 的父亲是服务器。则 $i$ 的所有子节点都不是服务器。
 
* $f_{u,2}$ 表示 $i$ 不是服务器，但 $i$ 的父亲也不是服务器。则 $i$ 的所有子节点中有且只有一个是服务器。

状态转移（$v$ 是 $u$ 的子节点）：

$$f_{u,0}=\sum \min(f_{v,0},f_{v,1})+1$$

$$f_{u,1}=\sum f_{v,2}$$

$f_{u,2}$ 计算比较复杂，需要枚举那个是服务器的节点 $v$，然后 **把其他所有子节点 $v'$ 的 $f_{v',2}$ 加起来**，再和 $f_{v,0}$ 相加。但是这样做复杂度为多少呢，设 $k$ 为 $u$ 的子节点数量，复杂度显然为 $O(k^2)$，直接超时。

粗体字这个步骤非常消耗时间，但是我们发现 $f_{v,2}$ 的和其实和已经算出来的 $f_{u,1}$ 真的非常相近。所以改进一下就变成：$f_{u,2}=\min(f_{u,1}-f_{v,2}+f_{v,0})$。

这样，计算 $f_{u,0/1/2}$ 的复杂度均为 $O(k)$。因为每个节点只有在计算父亲的时候才被用到，总时间复杂度为 $O(n)$。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 5;
int n, k, dp[N][3];
vector<int> G[N];

void dfs(int u, int fa) {
	dp[u][0] = 1;
	dp[u][2] = 2e9;
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		dp[u][0] += min(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][2];
	}
	for (auto v : G[u]) {
		if (v == fa) continue;
		dp[u][2] = min(dp[u][2], dp[u][1] + dp[v][0] - dp[v][2]);
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	while (1) {
		cin >> n;
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i <= n - 1; i++) {
			int u, v;
			cin >> u >> v;
			G[u].push_back(v), G[v].push_back(u);
		} 
		cin >> k;
		dfs(1, 0);
        cout << min(dp[1][0], dp[1][2]) << endl;
		if (k == -1) break;
	}
}
```

---

## 作者：封禁用户 (赞：3)

## 分析

考虑树形 DP。

对于该题，我们有 $3$ 种不同的情况，定义 $\mathit{f}_{i,j}$ 如下：

1. $\mathit{f}_{i,0}$：将节点 $i$ 设定为服务器时，其所在子树需要的最少服务器数量。
2. $\mathit{f}_{i,1}$：将节点 $i$ 设定为客户端且其父节点是服务器时，所在子树需要的最少服务器数量。
3. $\mathit{f}_{i,2}$：将节点 $i$ 设定为客户端且其父节点不是服务器时，所在子树需要的最少服务器数量。

对于 $\mathit{f}_{i,0}$，其子节点是都可以成为或不成为服务器的，所以我们只需要将每个子节点的两种情况取最小然后累加，最后增加节点 $i$ 的一个代价。

对于 $\mathit{f}_{i,1}$，因为父节点是服务器，所以 $i$ 的子节点都不能是服务器，代价即为所有子节点对于情况 $3$ 的代价之和。

对于 $\mathit{f}_{i,2}$，我们所要考虑的是在所有子节点中选择一个节点成为服务器，其余的都是客服端。不难想到，如果我们将所有子节点都设为服务器，然后把它们的代价都累加起来，那么这就会比实际代价多 $t$（$t$ 为 $i$ 的子节点数量减一）。则只需要将这个累加的和减去 $t$。

最终的最小代价：由于根节点是没有父节点的，所以代价就是情况 $1,3$ 的最小值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<double,int>
#define x first
#define y second
const int N=1e6+10;
int n;
int ne[N],e[N],h[N],idx;
void add(int a,int b){
	ne[idx]=h[a],e[idx]=b,h[a]=idx++;
}
int f[N][3];
void dfs(int now,int fa){
	int sum=0;
	f[now][0]=0,f[now][1]=0,f[now][2]=0;
	for(int i=h[now];~i;i=ne[i]){
		int j=e[i];
		if(j==fa) continue;
		sum++;
		dfs(j,now);
		f[now][0]+=min(f[j][0],f[j][1]);
		f[now][1]+=f[j][2];
		f[now][2]+=f[j][0];
	}
	f[now][2]-=(sum-1),f[now][0]+=1;
}
int k,a,b;
signed main(){
	while(cin>>n){
		memset(h,-1,sizeof(h)),memset(f,0,sizeof(f));
		idx=0;
		for(int i=1;i<n;i++){
			cin>>a>>b;
			add(a,b),add(b,a);
		}
		cin>>k;
		dfs(1,-1);
		cout<<min(f[1][0],f[1][2])<<"\n";
		if(k==-1){
			return 0;		
		}
	}
	return 0;
}
```


---

## 作者：liyancen (赞：2)

考虑树形dp，不难想到我们会用到三个状态，具体如下

- $dp[x][0]$：表示 $x$ 是服务器。
- $dp[x][1]$：表示 $x$ 不是服务器，但是 $x$ 的父亲是。
- $dp[x][2]$：表示 $x$ 不是服务器，$x$ 的父亲也不是。
  
那么我们就不难想到会有以下几个状态转移方程：

注：$v_i$ 表示 $x$ 的孩子。
$$dp[x][0]=\sum \min(dp[v_i][0],dp[v_i][1])$$
$$dp[x][1]=\sum dp[v_i][2]$$

上面的两个状态转移方程非常好想对吧，按照dp的定义即可推导出来，关键就是在于 $dp[x][2]$。

题目中要求了，只能有一个服务器与之相连，所以说我们很容易想出用暴力的思想，暴力枚举所有儿子，看选哪一个作为服务器，所以就有了一下的状态转移方程。（设 $w$ 为选中的儿子）

$$dp[x][2]=\min (dp[w][0]-dp[w][2]+\sum dp[v_i][2])$$

但是这样的话，我们每次都还需要用 $\cal O(n)$ 的时间复杂度来求和，会超时。

但是我们动动脑子，就会发现，$dp[x][1]$ 不就是我们后面所求的那个和吗？那么我们直接用 $dp[x][1]$ 把 $\sum dp[v_i][2]$ 给替换了不就行了？

$$dp[x][2]=\min (dp[w][0]-dp[w][2]+dp[x][1])$$

现在所有的答案都有了，那么我们最终的答案就是 $\min(dp[1][0],dp[1][2])$。

最后提一嘴，清空的时候要小心。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=1e5+10;
int dp[INF][3];
vector<int> mp[INF];

void dfs(int x,int fa){
	dp[x][0]=1,dp[x][1]=0,dp[x][2]=1e8;
	int len=mp[x].size();
	for (int i=0;i<len;i++){
		if (mp[x][i]==fa)continue;
		int t=mp[x][i];
		dfs(t,x);
		dp[x][0]+=min(dp[t][0],dp[t][1]);
		dp[x][1]+=dp[t][2];
	}
	if (len==1&&x!=1)return;
	for (int i=0;i<len;i++){
		if (mp[x][i]==fa)continue;
		int t=mp[x][i];
		dp[x][2]=min(dp[x][2],dp[t][0]+dp[x][1]-dp[t][2]);
	}
}
int main(){
	while (1){
		int n,t;
		cin>>n;
		for (int i=1;i<=n;i++){
			mp[i].clear();
		}
		for (int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			mp[u].push_back(v);
			mp[v].push_back(u);
		}
		dfs(1,-1);
		cout<<min(dp[1][0],dp[1][2])<<endl;
		cin>>t;
		if (t==-1)return 0;
	}
	return 0;
}
```

---

## 作者：Need_No_Name (赞：2)

# Solution For UVA1218

## 题意：

现有 $n$ 台计算机， $n - 1$ 条边组成的网络（很显然，这是一棵树）。现在要在这些计算机中设置一些服务器，使得其他普通电脑每台都能收到一台服务器的服务。我们称其为“完美服务”。求至少设置多少台服务器让其他电脑都收到“完美服务”。

## 分析：

看见这道题，我想了想，看样子，这道题就像是[UVA1292](https://www.luogu.com.cn/problem/UVA1292)这道题目一样，设置几个特殊的点为相邻的边服务。不过仔细想想，如果将计算机看做节点的话，那么这道题中服务器是为相邻的点服务的，那还和那道题不一样了。再想一想，这道题还可以用树形dp做，不过，讨论的方案就更多了。

## 转移方程：

我们现设 $u$ 为当前节点， $v$ 为当前节点的子节点，而 $w$ 为当前节点的父节点。

无妨设三种状态：

1.自己设为服务器，而子节点 $v$ 是或不是服务器，也就是 $dp[u][0]$

![](https://cdn.luogu.com.cn/upload/image_hosting/6b6x8c6m.png)



2.$dp[u][1]$ ：当 $u$ 不是服务器，但 $w$ 是服务器，而所有的子节点都不是服务器。

![](https://cdn.luogu.com.cn/upload/image_hosting/1s2b6scm.png)

(当然图片中 $v$ 的下面也是还有子节点的)


3.$dp[u][2]$ 当 $u$ 不是服务器，且 $w$ 也不是服务器，则至少有一个 $v$ 恰好是服务器。


![](https://cdn.luogu.com.cn/upload/image_hosting/slw83wtn.png)

则综上，转移方程为

$dp[u][0] = ∑{min}(dp[v][0], dp[v][1]) + 1$

$dp[u][1] = ∑dp[v][2]$

$dp[u][2] = {min}(dp[u][2], dp[u][1] - dp[v][2] + dp[v][0])$

~~（奇怪的转移方程）~~

重点说一下第三个转移方程：

可能看了思路后会认为转移方程为

$dp[u][2] = {min}(dp[u][2], dp[v_1][2] + dp[v_2][2]  + ··· +  dp[v][0])$

也就是去枚举为服务器的 $v$ ，不断取 $min$ ，但是，这样的复杂度 $O(k^2)$ (设 $u$ 有 $k$ 个子节点)，那么这种作法可能会炸。

那么我们得想到一种比较快捷的方法。我们可以试着利用 $dp[u][0]$ 和 $dp[u][1]$ 的运算结果。既然 $dp[u][1]$ 存储的是 $u$ 的所有子节点都不为服务器的情况

![](https://cdn.luogu.com.cn/upload/image_hosting/gvrtflwd.png)

再去强制去掉三个中是或不是的最小值，再加上一个子节点是的值。这样就得到了至少有一个取的最小值。

知道了转移方程后，我们就可以快乐的码代码了

## 代码：

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 10005;
int n;
vector<int> tre[N];
int dp[N][5];
void dfs(int u, int f)
{
	dp[u][0] = 1;
	dp[u][1] = 0;
	dp[u][2] = N;
	if(tre[u].size() == 1 && f != -1)
	{
		return ;
	}
	for(int i = 0; i < tre[u].size(); i++)
	{
		int v = tre[u][i];
		if(v == f)
		{
			continue;
		}
		dfs(v, u);
		dp[u][0] += min(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][2];
	}
	for(int i = 0; i < tre[u].size(); i++)
	{
		int v = tre[u][i];
		if(v == f)
		{
			continue;
		}
		dp[u][2] = min(dp[u][2], dp[u][1] - dp[v][2] + dp[v][0]);
	}
}
signed main()
{
	bool flag = true;
	while(flag == true)
	{
		scanf("%lld", &n);
		int tmp = 0;
		memset(dp, 0, sizeof(dp));
		for(int i = 0; i <= n; i++)
		{
			tre[i].clear(); 
		}
		int a, b;
		for(int i = 1; i < n; i++)
		{
			scanf("%lld%lld", &a, &b);
			tre[b].push_back(a);
			tre[a].push_back(b);
		} 
		int root = 1;
		dfs(root, -1);
		printf("%lld\n", min(dp[root][0], dp[root][2]));
		scanf("%lld", &tmp);
		if(tmp == 0)
		{
			continue;
		}
		else if (tmp == -1)
		{
			flag = false;
			break;
		}
	}
	return 0;
 } 
 //请勿抄袭
```
在代码中，说几个问题：

1.建图的问题中，由于任意节点都可以为根，所以最好去添加两遍变为双向的边。

2.说到了建图了，就说一下根。一开始我对着这道题的建图想了半天，其实这种树图叫[无根树](https://baike.baidu.com/item/%E6%97%A0%E6%A0%B9%E6%A0%91/10017543?fr=aladdin)，是一种没有明确指定根，却又可以以任意节点为根的一种树，非常奇妙，我也就默认用 $1$ 作为根了（看见题解中有个大佬用 $rand$ 函数时我整个人都惊呆了）



3.在dfs中，社里有个人就问为什么不将 $dp[u][2]$ 的情况与 $dp[u][1]$ 和 $dp[u][0]$ 搁在一起。~~那还不废话搁一起WA了而分开就A了。~~其实是因为在 $dp[u][2]$ 中要调用 $dp[u][1]$ 和 $dp[v][0]$ 的值。为了保险保证它们都被处理过，我们就分开来。



4.在输出时，也有社里的同学问我为什么不将 $dp[u][1]$ 搁一起取 $min$ 值。其实是在输出时， $dp[root][1]$ 牵扯到 $root$ 的根，而 $root$ 已经为整体的根了，也就不去讨论了。

---

## 作者：xixiup (赞：2)

## 思路分享

一道非常不错的树形 $DP$ 题。

我们思考，由于每个`客户端`必须与**恰好**一个`服务器`相邻，故我们可以考虑设 $3$ 个 $dp$。

- $dp_{x,0}$ 表示 $x$ 本身是一个`服务器`，由于没有规定两个`服务器`不能相邻，所以点 $x$ 的父亲节点与儿子节点是不是`服务器`都无所谓。

- $dp_{x,1}$ 表示 $x$ 的父亲是一个`服务器`，$x$ 是一个`客户端`，因为每个`客户端`只能**恰好**与一个`服务器`相连，所以 $x$ 的儿子节点全部不是`服务器`。

- $dp_{x,2}$ 表示 $x$ 的父亲与 $x$ 都不是`服务器`，而 $x$ 的儿子节点中恰好有一个是`服务器`。

然后我们考虑如何转移。

为了方便阐述，下文中的 $y$ 为 $x$ 的儿子节点，定义集合 $S$ 为 $x$ 的所有子节点的集合。

首先对于 $dp_{x,0}$，那么从定义本身出发，我们可以发现，$dp_{y,0}$ 和 $dp_{y,1}$ 与 $dp_{x,0}$ 是不矛盾的，而 $dp_{y,2}$ 要求了 $y$ 的父亲也就是 $x$ 不能为`服务器`，所以矛盾。所以得到如下公式：
$$
\boxed{dp_{x,0}=\sum\limits_{y\in S} \min(dp_{y,0},dp_{y,1})}
$$
然后对于 $dp_{x,1}$，要求 $x$ 与 $x$ 儿子(也就是 $y$)都不是`服务器`，所以只有 $dp_{y,2}$ 满足要求。所以得到如下公式：
$$
\boxed{dp_{x,1}=\sum\limits_{y\in S}dp_{y,2}}
$$
最后对于 $dp_{x,2}$，我们可以发现，对于节点 $y$，它需要是一个`服务器`，所以需要加上 $dp_{y,0}$，对于其他的节点 $z\in S-\{y\}$，这个点与其父亲节点（也就是 $x$）都是`客户端`，所以我们需要加上 $dp_{z,2}$。所以得到如下公式：
$$
\boxed{dp_{x,2}=\sum\limits_{y\in S}(dp_{y,0}+\sum\limits_{z\in S-y} dp_{z,2})}
$$
然后就可以了吗？不。不行，为什么呢？

因为这个 $dp_{x,2}$ 的转移是 $\Theta\left( n^2 \right)$ 的，会妥妥地 $\color{white}\colorbox{darkblue}{TLE}$ 掉。

然后我们就可以考虑如何优化。

我们可以发现，上文中的 $dp_{x,1}$ 就是 $\sum\limits_{y\in S} dp_{y,2}$，所以我们其实只需要处理以下，就可以得到如下式子：
$$
\boxed{dp_{x,2}=\sum\limits_{y\in S} dp_{x,1}-dp_{y,2}+dp_{y,0}}
$$
考虑最后的答案，由于根结点并没有父亲节点，所以答案就是 $\boxed{\min(dp_{root,0},dp_{root,2})}$。

于是我们就可以过这道题了。

## 代码展示

这里仅展示 $DFS$ 部分代码。

```cpp
void dfs(int x,int fa){
	dp[x][0]=1;dp[x][1]=0;dp[x][2]=maxn;
    //答案最大为n，所以dp[x][2]赋为maxn就可以了。
	for(int i=bg[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa){
			continue;
		}
		dfs(y,x);
		dp[x][0]+=min(dp[y][0],dp[y][1]);
		dp[x][1]+=dp[y][2];//更新dp[x][0]和dp[x][1]
	}
	for(int i=bg[x];i;i=ne[i]){//由于更新dp[x][2]需要用到dp[x][1]，所以我们需要重新循环
		int y=to[i];
		if(y==fa){
			continue;
		}
		dp[x][2]=min(dp[x][2],dp[x][1]-dp[y][2]+dp[y][0]);
	}
}
```


---

## 作者：guoshengyu1231 (赞：1)

# 前言
别看这是一道蓝题，其实就是个纸老虎，明白了思路真的就非常简单。有时候千万不能被外表吓到，要脚踏实地的做题，说不定就是吓吓你的。比如这题，真的就非常水，个人认为只配评黄。那么话不多说，直接上思路。
# 思路
千万不要被这题~~乱写~~的标签误导，其实这就是一道裸的树形 dp。我们可以将题目中提到的网络看作一棵树，而题目要求在这棵树中选择若干个节点，使得这棵树中所有的边都至上有一个端点是被选上的。问至少需要选择多少个点。

 $\\$ 

既然是 dp，那三要素可不能少。
## 1.状态
设函数 $\operatorname{dfs}(u)$ 的作用为求解状态 $u$。在这我们需要明白一点，那就是每一条边的责任要么由父亲承担，要么由儿子承担。因为一条边至少要由一个端点是被选择到的。故函数 $\operatorname{dfs}(u)$ 会返回以下三种状态之一。
- 自己不承担，依赖父亲（~~即坑爹~~）。此时返回 $-1$。
- 自己不承担，不过也不用依赖父亲，因为已经有儿子承担了。此时返回 $0$。
- 自己承担了一切，此时返回 $1$。

特别的，如果根节点选择依赖父亲，但自己却没有父亲，那他也只能自己承担。
## 2.边界
当递归求解至叶子结点时，就直接返回 $-1$，为什么我会这么说。首先，叶子结点没有儿子，所以他不可能依赖儿子。其次，如果他选择自己承担的话，由于他没有儿子，所以他只能为自己的父亲带来好处。但如果是让他的父亲承担的话，他的父亲也至少能为他这一个儿子遮风挡雨。如果他不是更节点或者有更多儿子的话，那他带来的好处会更多。
## 3.转移
要想知道某个点的状态，总得先知道他儿子的状态。先是遍历他所有的儿子，如果其中有**一个**儿子需要依赖父亲，那他也没有选择了，只能为儿子承担这一切。如果**所有**儿子都选择承担责任，那他就可以放飞自我了，因为此时他再承担责任，那他也只能为自己的父亲带来好处，跟没有儿子的叶子结点差不多。如果有其中**一个**儿子不能帮助自己承担，那就只能依赖自己的父亲了。注意这里和第一种情况不一样，其中儿子不需要依赖父亲，只是不帮父亲承担责任罢了。拿自己也就没必要没事找事了。综上所述，我们可以归纳出状态转移方程：
 $$\operatorname{dfs}(u)=\begin{cases}
 1,&\exists\operatorname{dfs}(v)=-1\\
 0,&\forall\operatorname{dfs}(v)=1\\
 -1,&\text{otherwise.}
 \end{cases}$$ 
其中 $v$ 是 $u$ 的其中一个儿子。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+5;
int n,x,y,endit,ans;
vector<int> g[maxn];//邻接表
int dfs(int u,int f)
{
	int ch_u=-1;//初始状态
	for(int i=0;i<g[u].size();i++)//遍历所有儿子&父亲
	 {
		int v=g[u][i];//得到儿子
		if(v==f) continue;//如果这是他的父亲，跳过
		int ch_v=dfs(v,u);//查询儿子的状态
		if(ch_v==-1) ch_u=1;
		if(ch_v==1&&ch_u!=1) ch_u=0;
	 }
	if(ch_u==1) ans++;
	return ch_u;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);//加速
	while(1)
	 {
		cin>>n;ans=0;
		for(int i=1;i<=n;i++) g[i].clear();//多测，不要忘记初始化！
		for(int i=1;i<n;i++)
		 {
			cin>>x>>y;
			g[x].push_back(y);
			g[y].push_back(x);
		 }
    //由于题目没有说清楚谁是谁的父亲，所以要建立双向边
		cin>>endit;
		if(dfs(1,0)==-1) ans++;//没爹可坑，只能坑自己。
		cout<<ans<<"\n";
		if(endit) break;//非0即为真
	 }
	return 0;
}
```

---

## 作者：Y_QWQ_Y (赞：1)

蒟蒻调了很久，不喜勿喷。

### 定义状态
我们可以根据服务器设置 3 个状态。

1. $f_{i,0}$ 表示 $i$ 是服务器。

2. $f_{i,1}$ 表示 $i$ 的父节点是服务器，$i$ 和 $i$ 的子节点都不是服务器。

3. $f_{i,2}$ 表示 $i$ 和 $i$ 的父节点都不是服务器，则 $i$ 的子节点中有一个服务器。

### 状态转移
$v$ 是 $u$ 的子节点。

$f_{u,0}=1+\sum\min {f_{v,0},f_{v,1}}$。

$f_{u,1}=\sum f_{v,2}$。

关于 $f_{u,2}$，我们需要枚举 $v$ 的子节点 $v'$，即枚举服务器，把 $\sum f_{v',2}$ 减去服务器 $vs$ 的 $f_{vs,2}$ 再加上 $f_{v,0}$。通过观察状态转移方程可知，$f_{u,1}=\sum f_{v,2}$，那么：

$f_{u,2}=\min {(f_{u,1}-f_{v,2})+f_{v,0}}$。

### 注意事项
重中之重的部分来了！本题还是有很多细节是需要注意的！

1. 双向边。

2. 数组清干净（数组没清干净的我，挂了）。

3. 先算完 $f_{u,0}$ 和 $f_{u,1}$，再算 $f_{u,2}$（三个状态一起算的我， 挂了）。

4. 不要像某些人一样在最后一个测试点不换行，这道题的最后一个测试点是需要多出一个换行符的（我是不会告诉你某些人就是我的）。

希望大家能一遍过。~~（此处跳过代码部分）~~。

### 代码部分
这里怎么可以跳过呢？
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, ff, f[N][3], h[N], c, u, v;
struct Edge{int v, nxt;}e[N << 2];推销一下链式前向星
void add (int u, int v)
{
	e[++ c].nxt = h[u];
	h[u] = c;
	e[c].v = v;
}
void dfs (int d, int fa)
{
	f[d][0] = 1, f[d][2] = 2e9;
	for (int i = h[d]; i; i = e[i].nxt)if (e[i].v != fa)避免走环路
	{
		int uv = e[i].v;
		dfs (uv, d);
		f[d][0] += min (f[uv][1], f[uv][0]);
		f[d][1] += f[uv][2];
	}
	for (int i = h[d]; i; i = e[i].nxt)if (e[i].v != fa)f[d][2] = min (f[d][2], f[d][1] + f[e[i].v][0] - f[e[i].v][2]);
}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	while (cin >> n)
	{
		memset (f, 0, sizeof (f));
		memset (e, 0, sizeof (e));
		memset (h, 0, sizeof (h));
		c = 0;
		for (int i = 1; i < n; ++ i)
		{
			cin >> u >> v;
			add (u, v), add (v, u);
		}
		cin >> ff;标识符不能忘
		dfs (1, 0);
		cout << min (f[1][0], f[1][2]) << '\n';
		if (ff < 0)return 0;
	}
	return 0;
}
```

---

## 作者：Konnyaku_LXZ (赞：1)

看完题肯定就知道是一道树形dp了。

不妨令1号点为树根。每个点有两种状态：是服务器或者是客户端。所以我们用0表示一个点是客户端，1表示一个点是服务器。

对于每个是客户端的点，与它直接相连的所有点中，**有且仅有**一个点是服务器，然而我们不知道这个点是它的父亲还是它的儿子。

所以我们考虑再加一维： $f[u][0/1][0/1]$ 表示 $u$ 为客户端/服务器，$u$ 的父亲为客户端/服务器时，以 $u$ 为根的子树中最少要放的服务器的数量。第二维表示 $u$ 的状态，第三维表示 $u$ 的父亲的状态。

### 初始值：
$f[u][0][0]=INF,f[u][0][1]=0,f[u][1][0]=1,f[u][1][1]=1(u \in leaves)$

### 转移：

①如果 $u$ 为客户端且 $u$ 的父亲为服务器，则 $u$ 的**所有儿子都必须为客户端**。

即 $f[u][0][1]= \sum \limits _{v \in son_u} f[v][0][0]$。

②如果 $u$ 为服务器且 $u$ 的父亲为客户端，则 $u$ 的儿子**可以是客户端也可以是服务器**。

即 $f[u][1][0]= 1+ \sum \limits _{v \in son_u} min(f[v][0][1],f[v][1][1])$。

③如果 $u$ 为服务器且 $u$ 的父亲为服务器，则 $u$ 的儿子**可以是客户端也可以是服务器**。

即 $f[u][1][1]= 1+ \sum \limits _{v \in son_u} min(f[v][0][1],f[v][1][1])$。

④如果 $u$ 为客户端且 $u$ 的父亲为客户端。

这种状态的转移比较麻烦。我们不妨先让所有的儿子都为客户端，那么接下来要做的就是把其中一个客户端改为服务器，并且要使得需要的总服务器数量最少。我们应该改哪个客户端呢？**自然是该点为客户端时需要的最少服务器数量与该点为服务器时需要的最少服务器数量差值最大的那个**。

即 $f[u][0][0]= f[x][1][0] + \sum \limits _{v \in son_u,v \not =x} f[v][0][0]$，其中 $x$ 是令 $f[v][0][0]-f[v][1][0](v \in son_u)$ 最大的 $v$。

最终答案为 $min(f[1][0][0],f[1][1][0])$。

Code:

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

const int MAXN=1e5+50,INF=0x3f3f3f3f;
typedef long long LL;

struct edge{
	LL next;
	LL to;
};

LL N,flag,f[MAXN][2][2],Ans=0;
LL head[MAXN],Cnte=0;
edge e[MAXN<<1];

void adde(LL u,LL v){
	++Cnte;
	e[Cnte].to=v;
	e[Cnte].next=head[u];
	head[u]=Cnte;
}

void dfs(LL u,LL father){
	f[u][0][0]=f[u][0][1]=f[u][1][0]=f[u][1][1]=0;//初始化f数组 
	LL maxx=-INF,maxi=0;//maxx记录为客户端和服务器时答案的最大差值，maxi即为题解中说的x 
	bool flag=false;//判断该节点是否为叶子节点 
	for(int i=head[u];i;i=e[i].next){
		LL v=e[i].to;
		if(v==father) continue;
		flag=true;
		dfs(v,u);
		f[u][0][1]+=f[v][0][0];//转移 
		f[u][1][0]+=min(f[v][0][1],f[v][1][1]);
		f[u][1][1]+=min(f[v][0][1],f[v][1][1]);
		if(f[v][0][0]-f[v][1][0]>maxx){//找到最大差值 
			maxx=f[v][0][0]-f[v][1][0];
			maxi=v;
		}
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==father) continue;
		if(v!=maxi) f[u][0][0]+=f[v][0][0];//转移 
		else f[u][0][0]+=f[v][1][0];
	}
	++f[u][1][0];++f[u][1][1];//记得加一 
	if(!flag){
		f[u][0][0]=INF;//叶子节点的初始值 
		f[u][0][1]=0;
		f[u][1][0]=1;
		f[u][1][1]=1;
	}
}

void Init(){
	Cnte=0;Ans=0;//记得清空 
	memset(head,0,sizeof(head));
	memset(e,0,sizeof(e));
	scanf("%lld",&N);
	for(int i=1;i<N;++i){
		LL u,v;
		scanf("%lld%lld",&u,&v);
		adde(u,v);adde(v,u);
	}
	scanf("%lld",&flag);
}

void Solve(){
	dfs(1,0);
	Ans=min(f[1][0][0],f[1][1][0]);//取最小值作为答案 
}

void Print(){
	cout<<Ans<<endl;
}

int main()
{
	while(1){
		Init();
		Solve();
		Print();
		if(flag==-1) break;	
	}
	return 0;
}
```

---

## 作者：pyqpyq (赞：1)

和之前题解做法有点不一样，分享一下。

这题首先显然是一个树形 DP。不会树形 DP 的请自行左转 [P1352](https://www.luogu.com.cn/problem/P1352)。~~贪心？我不会做。~~

但是转移的时候，由于每个非服务器节点相邻的节点中有**有且仅有**一个服务器的限制，所以一个节点的某个孙子节点设为服务器，则它自己就不能设为服务器了。

换而言之，一个节点的孙子节点的状态会影响到当前的转移，~~按照套路，~~ 这时每个节点的状态就应该把儿子的也记录下来了。

所以，我们设 dp 数组 $dp_{i,0/1/2}$，其中

$dp_{i,0}$ 表示 i 号节点和它的子节点都不放服务器时以 i 号节点为根子树并**枚举到当前儿子**的答案。

$dp_{i,1}$ 表示 i 号节点不放服务器但它的子节点中有且仅有1 个服务器时以 i 号节点为根子树并枚举到当前儿子时的答案。

$dp_{i,2}$ 表示 i 号节点放服务器时以 i 号节点为根子树并枚举到当前儿子时的答案。

我们发现这个 $dp_{i,1}$ 和其他的树形 DP 不太一样，要小心处理。

下面分析转移方程（$at$ 为当前节点，$so$ 为子节点）：

$dp_{at,0}=dp_{at,0}+dp_{so,1}$

因为它的儿子自己不是服务器，且它的儿子的父亲（即它自己）不是服务器，那么它的儿子的儿子一定有服务器。

$dp_{at,1}=\min(dp_{at,1}+dp_{so,1},dp_{at,0}+dp_{so,2})$

第一个式子表示前面的儿子已经有了服务器，那么这个儿子就不能是服务器了。第二个式子表示前面的儿子中没有服务器，那么这个儿子就是服务器。

$dp_{at,2}=\min(dp_{at,2}+dp_{at,0},dp_{at,2}+dp_{at,2})$

当前节点有服务器是儿子节点就没有限制了，不过儿子节点没有服务器时，孙子节点也不能有服务器。

最后以随便哪个节点为根 dfs 一遍，答案就是 $\min(dp_{ro,1},dp_{ro,2})$（ $ro$ 是根节点编号）

注意事项：

1. n 为 1 时特判一下。


2. $dp_{at,1}$ 要在 $dp_{at,0}$ 之前算，否则 $dp_{so,1}$ 更新两遍 $dp_{at,1}$。

3. $dp_{at,1}$ 的初值设为 inf，因为开始是没有子节点被遍历过，更没有子节点有服务器。

4. 得出最后答案时不能加上 $dp_{ro,0}$，这样根节点周围会没有服务器。

5. ~~交题时别忘删 freopen。~~

参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int _maxn=10011,_zinf=40011;
int n,u,v,firs[_maxn],neig[_maxn<<1],arri[_maxn<<1],dpot[_maxn][3];
void dfs(int at,int fa){
    dpot[at][0]=0;
    dpot[at][1]=_zinf;
    dpot[at][2]=1;
    for(int i=firs[at];i;i=neig[i])
        if(arri[i]!=fa){
            dfs(arri[i],at);
            dpot[at][1]=min(dpot[at][1]+dpot[arri[i]][1],dpot[at][0]+dpot[arri[i]][2]);
            dpot[at][0]=dpot[at][0]+dpot[arri[i]][1];
            dpot[at][2]=min(dpot[at][2]+dpot[arri[i]][0],dpot[at][2]+dpot[arri[i]][2]);
        }
}
int main(){
    while(1){
        scanf("%d",&n);
        if(n==1){
            printf("1\n");
            scanf("%d",&n);
            if(n==-1)
                break;
            else
                continue;
        }
        for(int i=1;i<=n;++i)
            firs[i]=0;
        for(int i=1;i<n;++i){
            scanf("%d%d",&u,&v);
            neig[i<<1]=firs[u];
            firs[u]=i<<1;
            arri[i<<1]=v;
            neig[i<<1|1]=firs[v];
            firs[v]=i<<1|1;
            arri[i<<1|1]=u;
        }
        dfs(1,0);
        printf("%d\n",min(dpot[1][1],dpot[1][2]));
        scanf("%d",&n);
        if(n==-1)
            break;
    }
    return 0;
}
```

---

## 作者：xiaoxiaoxia (赞：0)

一道不错的树形 dp。
# 定义状态
- $dp[x][0]$：$x$ 自己是服务器。
- $dp[x][1]$：$x$ 不是服务器，$x$ 的父亲是服务器。
- $dp[x][2]$：$x$ 不是服务器且 $x$ 的父亲不是服务器。
# 状态转移
## $dp[x][0]$
这个状态就是在 $x$ 处放上一个服务器，那我们不难得到可以从儿子得过来，$dp[v][0]$，$dp[v][1]$ 是符合我们要求的，而 $dp[v][2]$ 的上文说了，父亲已经是服务器了，所以儿子就不可以是服务器了，所以不可以。

所以我们从 $dp[v][0]$，$dp[v][1]$ 转移过来，而且我们要最小答案，所以每次选最小的一个。
$dp[x][0]$=$\sum_{}\min(dp[v][0],dp[v][1])+1,v\in son $
## $dp[x][1]$
这个状态就是在 $x$ 的父亲上放服务器，因为只能连接一台服务器，所以 $x$ 的孩子不能是服务器。因为孩子自己不能是服务器，所以孙子必须是服务器，不然孩子就没有服务器联通了。孩子的情况就是自己不放，孩子放，刚好符合我们的$dp[v][2]$，所以把他们求和就好啦。
$dp[x][1]=\sum_{}dp[v][2],v\in son $
## $dp[x][2]$
这个状态是最难想的一个，定义是点 $x$ 周围存在一台服务器，且是它的儿子，所以父亲肯定不能有服务器。我们再考虑一下他的孩子的情况，如果我们选定一个儿子v，让他拥有服务器，那么，设 $V_i$ 为 $x$ 的其他儿子，那么很明显你会TLE。我们考虑逆向思维：通过一个集合减去掉一个元素得到，再观察一下我们的三个状态，我们是可以推出来的。因为 $\sum_{}$ 是我们所有非v儿子的集合，而 $dp[x][1]$ 刚好是去掉所有儿子的结果，这个时候加上 $dp[v][0]$ 就完成了。但是，我们的状态有重叠，$dp[x][1]$ 还含有 $v$ 不是服务器的情况，我们需要减去这个情况。$v$ 不是服务器有两种情况，$dp[v][1]$ 和 $dp[v][2]$，但对于 $dp[x][1]$，我们的 $x$ 是不能有服务器的，这个状态是会包括 $v$ 的父亲 $x$ 的。所以只有 $dp[v][2]$（父亲和自己都不能是服务器）符合我们的要求，这样我们就可以得到：先算上去掉儿子的全集 $dp[x][1]$，因为我们要 $v$ 儿子含有服务器，加上 $dp[v][0]$，再减去 $dp[v][2]$。
$dp[x][2]$=$\sum_{}\min(dp[x][2],dp[x][1]-dp[v][2]+dp[v][0]),v\in son $
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e4+10;
const int maxn=1e4+100;
int n,x,y;
vector<int>e[maxn];
int f[maxn][3];
void dfs(int u,int fa)
{
	f[u][0]=1;
	f[u][2]=inf;
	f[u][1]=0;
	int m=e[u].size();
	for(int i=0;i<=m-1;i++)
	{
		int v=e[u][i];
		if(v!=fa)
		{
			dfs(v,u);
			f[u][0]+=min(f[v][1],f[v][0]);
		}
	} 
	for(int i=0;i<=m-1;i++)
	{
		int v=e[u][i];
		if(v!=fa)
			f[u][1]+=f[v][2];
	}
	for(int i=0;i<=m-1;i++)
	{
		int v=e[u][i];
		if(v!=fa)
			f[u][2]=min(f[u][2],f[u][1]+f[v][0]-f[v][2]);
	}
} 
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		if(n==-1) 
			break;
		for(int i=1;i<=n;i++) 
			e[i].clear();
		for(int i=1;i<=n-1;i++)
		{
			scanf("%d%d",&x,&y);
			e[x].push_back(y);
			e[y].push_back(x);
		} 
		scanf("%d",&x);
		dfs(1,0);
		printf("%d\n",min(f[1][0],f[1][2]));
	}
}
```

---

## 作者：Dehydration (赞：0)

### 前言：

树形 dp 入门题目。

所需知识：~~dfs~~，树形 dp 基础知识。

### 思路：

树形 dp。

首先很简单冒出来思路：

1. $dp[i][0]$ 代表自己是服务器。

2. $dp[i][1]$ 代表自己不是服务器。

考虑正确性。

显然错误，因为这种普通树形 dp 想法只适合一个点的值只受子树影响，但这道题目这个点仍受父亲节点影响，考虑将父亲节点考虑进去。

对于自己是服务器的情况，父亲没有影响。

对于自己不是服务器的情况，服务器有可能是在子树，也有可能是父亲，分为父亲是服务器和父亲不是服务器两个情况，则改进方案为：

1. $dp[i][0]$ 代表自己是服务器。

2. $dp[i][1]$ 代表自己不是服务器，**但父亲是服务器**。

3. $dp[i][2]$ 代表自己不是服务器，**父亲也不是服务器**。

$dp$ 都是最小服务器数量值。

考虑状态转移。

定义此节点为 $u$，子节点为 $v$，$s$ 为除 $v$ 外其他子节点。

1. 考虑 $dp[u][0]$，因为自己是服务器，所以子节点去任何值都可以，但因为 $dp[v][2]$ 表示父节点也不是服务器，所以 $dp[u][0]=\Sigma \min(dp[v][0],dp[v][1])$。

2. 考虑 $dp[u][1]$，因为自己不是服务器，但父亲式服务器，所以这个点已经有一个服务器了，子节点不能有服务器，又因为自己不是服务器，$dp[v][1]$ 表示父亲是服务器，所以 $dp[u][1]=\Sigma dp[v][2]$。

3. 考虑 $dp[u][2]$，因为自己和服务器都不是服务器，所以子节点中恰好有一个服务器。显然是选一个 $dp[v][0]$ 和其他所有的 $dp[s][2]$。，则 $dp[u][2]=min(dp[u][2],\Sigma dp[s][2]+dp[v][0])$。对于这个，可以先求出总和 $sum$，则 $\Sigma dp[s][2]+dp[v][0]=sum-dp[v][2]+dp[v][0]$，$\Theta(n)$ 轻松解决。

### 代码实现：

```cpp
#include<bits/stdc++.h>
#define inf 2e4
using namespace std;
int dp[10005][3],n;
vector<int> a[10005];
//dp题目建议写上dp的含义
//dp[i][0]-->自己是服务器
//dp[i][1]-->自己不是服务器，父亲是服务器
//dp[i][2]-->自己和父亲都不是服务器
void dfs(int x,int fa){
	dp[x][0]=1,dp[x][1]=0,dp[x][2]=inf;
	int m=a[x].size(),sum=0;
	for(int i=0;i<m;i++){
		int u=a[x][i];
		if(u==fa)continue;
		dfs(u,x);
		sum+=dp[u][2];
	}
	for(int i=0;i<m;i++){
		int u=a[x][i];
		if(u==fa)continue;
		dp[x][0]+=min(dp[u][0],dp[u][1]);
	}
	for(int i=0;i<m;i++){
		int u=a[x][i];
		if(u==fa)continue;
		dp[x][1]+=dp[u][2];
	}
	for(int i=0;i<m;i++){
		int u=a[x][i];
		if(u==fa)continue;
		dp[x][2]=min(dp[x][2],sum-dp[u][2]+dp[u][0]);
	}
//	不对可以调试
//	cout<<x<<' '<<dp[x][0]<<' '<<dp[x][1]<<' '<<dp[x][2]<<'\n';
	return;
}
int main(){
	while(cin>>n)//可以这样
	{
		for(int i=1;i<n;i++){
			int x,y;cin>>x>>y;
			a[x].push_back(y);
			a[y].push_back(x);
		}
		dfs(1,0);
		cout<<min(dp[1][0],dp[1][2])<<'\n';
		int jcsy;cin>>jcsy;
		if(jcsy==-1)break;
		for(int i=1;i<=n;i++)a[i].clear();
	}
	return 0;
}
/*
6
1 3
2 3
3 4
4 5
4 6
0
2
1 2
-1
*/
```
建议用 `vector` 存图，比链式前向星好用的多。

**完结撒花！**


---

## 作者：chihik (赞：0)

一道很不错的树形dp。

令 $dp[u][f]$ 为以$u$为根的子树。

$f=0$，表示$u$为服务器，那么$u$的儿子和父亲既可以是服务器，也可以不是。

$f=1$，表示$u$的父亲为服务器，那么$u$的儿子一定不为服务器。

$f=2$，表示$u$和$u$的父亲均不为服务器，那么$u$的儿子中一定有一个是服务器。

那么转移式为:

$$
dp[u][0]=\sum_{v \in son_u}min(dp[v][0],dp[v][1])
$$

$$
dp[u][1]=\sum_{v \in son_u}dp[v][2]
$$

$$
dp[u][2]=min(dp[v_1][2]+dp[v_2][2]+...+dp[v_k][0]+...+dp[v_s][2])
$$

其中 $s$ 为 $u$ 的子结点个数 ， $k$ 是枚举的为服务器的那个子节点。

这样转移需要$\Theta(n)$ ， 经过观察发现，求和的部分与 $dp[u][1]$ 除了枚举的 $dp[v_k][0]$ 是一致的 ， 于是就可以化简为：

$$
dp[u][2]=min(dp[ u ][ 2 ] , dp[ u ][ 1 ] - dp[ v ][ 2 ] + dp[ v ][ 0 ])
$$

最后注意$\text{dp}$的极大值,用 $inf$ 可能会爆 $int$ , 开成 $n+5$ 即可。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 10000;
int n , u , v , dp[ MAXN + 5 ][ 3 ];


vector< int > Graph[ MAXN + 5 ];

void dfs( int u , int fa ) {
    dp[ u ][ 0 ] = 1; dp[ u ][ 1 ] = 0;
    for( int i = 0 ; i < Graph[ u ].size( ) ; i ++ ) {
        int v = Graph[ u ][ i ];
        if( v == fa ) continue;
        dfs( v , u );

        dp[ u ][ 0 ] += min( dp[ v ][ 0 ] , dp[ v ][ 1 ] );
        dp[ u ][ 1 ] += dp[ v ][ 2 ];
        dp[ u ][ 2 ] = min( dp[ u ][ 2 ] , dp[ u ][ 1 ] - dp[ v ][ 2 ] + dp[ v ][ 0 ] ); 
    }
}

int main( ) {
    while( scanf("%d",&n) ) {
        for( int i = 1 ; i <= n ; i ++ ) {
            Graph[ i ].clear( );
            dp[ i ][ 0 ] = dp[ i ][ 1 ] = dp[ i ][ 2 ] = MAXN;
        }

        for( int i = 1 ; i <= n - 1 ; i ++ ) {
            scanf("%d %d",&u,&v);
            Graph[ u ].push_back( v );
            Graph[ v ].push_back( u );
        }
        
        dfs( 1 , 0 );
        printf("%d\n", min( dp[ 1 ][ 0 ] , dp[ 1 ][ 2 ] ) );

        scanf("%d",&n);
        if( n == -1 ) break;
    }
    return 0;
}
```


---

## 作者：uhgariej (赞：0)

紫书上的一道题. 

下面重点说一下解题的思路, 以及介绍一种**全新的求d(u,2)** 的方式.

对于这题, 大家是不是有疑问为什么要这样定义状态?当然如果你dp做了上百道的话, 那么这个状态的定义也是很显然的. 这里仅以初学者的角度思考.

一般来说,读完这题**第一眼**的想法是: 

定义dp[u]为以结点u为根的子树最少的服务器数量. 

然后按结点u是否是服务器**进一步**定义:

dp[u][0]为以结点u为根的子树且结点u是服务器时, 最少的服务器数量. 

dp[u][1]为以结点u为根的子树且结点u不是服务器时, 最少的服务器数量. 

--- 

然后按照dp[u][0], dp[u][1]的状态推的时候, 发现不能完整描述题目所说的要求. 因为这样定义的状态都是以某个结点为根, 缺少了结点的父亲的信息. 而这是本题所需要的. 本题每个客户端结点相邻的只能有一个服务器结点, 而服务器结点可能来自它的儿子, 也可能来自它的父亲.

所以我们**再进一步**想到：

* dfs(u, fa): 记录dp[u][0], dp[u][1], dp[u][2]三者的状态

* dp[u][0]: 以结点u为根的子树, 当u为服务器时, 最少的服务器数量. 此时u的儿子结点和父亲结点可以是服务器也可以是client

* dp[u][1]: 以结点u为根的子树, 当u不是服务器时, 它的父亲(如果有)是服务器时, 最少的服务器数量. 此时u的儿子结点都不能是服务器

* dp[u][2]: 以结点u为根的子树, 当u不是服务器时, 它的父亲(如果有)也不是服务器时, 最少的服务器数量. 此时u的儿子结点有且只有一个是服务器.

---

上面是基本的思路, 然后我们计算dp[u][0], dp[u][2]都是很显然的.

对于dp[u][2], 我们可以这样算:

也就是@ Nanchtiy所说的: **d(u,2)就会等于 他儿子全都不是(即代码中的sum) 减去某个不是(dp[son][2]) 再加上某个是(dp[son][0])**

```cpp
// 枚举其中有且只有一个是服务器

dp[rt][2] = std::min(dp[rt][2], sum - dp[son][2] + dp[son][0]);

```
--- 

这样本题基本就做完了. 顺便说一下, 在算dfs(rt, fa)时, 在回溯回到(rt, fa)的状态的时候, 结点rt的所有的儿子结点的信息都是已经算完了的, 即dp[son][0], dp[son][1], dp[son][2]都是已知量. 当然理解了递归的朋友肯定都是非常清楚这一点的, 我这里只是显示的说明一下. 当然如果你不能理解, 说明你还是没有理解递归, 建议再思考一下或想同学请教.

最后答案为什么没有dp[root][1], 因为这种状态不合法. 

```cpp
int ans = std::min(dp[root][0], dp[root][2]);
```
---

下面是我的参考代码：

build_tree是无根树转有根树, 其实是没必要的, 任选一个结点当做根, 记录它的父亲结点是谁即可(这是一种常见的写法)

```cpp
/*
 * Created by xxxx on 2019-10-24
 *
 */

#include <bits/stdc++.h>

const int INF = 1e9;
const int maxn = 1e4 + 5;
std::vector<int> G[maxn];
bool vis[maxn];

int n;
std::vector<int> sons[maxn];

void build_tree(int rt) {
    vis[rt] = true;
    for (int i = 0; i < G[rt].size(); ++i) {
        int son = G[rt][i];
        if (!vis[son]) {
            sons[rt].push_back(son);
            build_tree(son);
        }
    }
}

/*
 * dfs(u, fa): 记录dp[u][0], dp[u][1], dp[u][2]三者的状态
 * dp[u][0]: 以结点u为根的子树, 当u为服务器时, 最少的服务器数量. 此时u的儿子结点和父亲结点可以是服务器也可以是client
 * dp[u][1]: 以结点u为根的子树, 当u不是服务器时, 它的父亲(如果有)是服务器时, 最少的服务器数量. 此时u的儿子结点都不能是服务器
 * dp[u][2]: 以结点u为根的子树, 当u不是服务器时, 它的父亲(如果有)也不是服务器时, 最少的服务器数量. 此时u的儿子结点有且只有一个是服务器.
 */
int dp[maxn][3];
void dfs(int rt, int fa) {
    dp[rt][0] = 1;
    dp[rt][1] = 0;
    dp[rt][2] = INF;
    int sum = 0;
    for (int i = 0; i < sons[rt].size(); ++i) {
        int son = sons[rt][i];
        if (son != fa) {
            dfs(son, rt);
            sum += dp[son][2];
        }
    }
    for (int i = 0; i < sons[rt].size(); ++i) {
        int son = sons[rt][i];
        if (son != fa) {
            dp[rt][0] += std::min(dp[son][0], dp[son][1]);
            dp[rt][1] += dp[son][2];
            // 枚举其中有且只有一个是服务器
            dp[rt][2] = std::min(dp[rt][2], sum - dp[son][2] + dp[son][0]);
        }
    }
}

int main() {
#ifdef Acui
    freopen("datain.txt", "r", stdin);
    freopen("dataout.txt", "w", stdout);
#endif
    while (scanf("%d", &n) && n != -1) {
        // 初始化
        for (int i = 1; i <= n; ++i) {
            G[i].clear();
            sons[i].clear();
            vis[i] = false;
        }
        for (int i = 1; i < n; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        int root = 1;
        build_tree(root);
        dfs(root, 0);
        int ans = std::min(dp[root][0], dp[root][2]);
        printf("%d\n", ans);
        int tmp;
        scanf("%d", &tmp);
        if (tmp == -1)
            break;
    }
    return 0;
}

```
---
如果你觉得讲的还行, 欢迎Star我的项目[dp](https://github.com/OFShare/Algorithm-challenger/blob/master/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/README.md), 并推荐给需要的朋友, 谢谢.

---

