# [GCJ 2012 #1C] Diamond Inheritance

## 题目描述

你需要帮助诊断类图，以识别菱形继承的实例。下面的类图示例说明了菱形继承的特性。共有四个类：$A, B, C$ 和 $D$。箭头从 $X$ 指向 $Y$ 表示类 $X$ 继承自类 $Y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/g3yse0or.png)

在这个类图中，$D$ 同时继承自 $B$ 和 $C$，$B$ 继承自 $A$，而 $C$ 也继承自 $A$。从 $X$ 到 $Y$ 的继承路径被定义为一个类序列 $X, C_1, C_2, C_3, \dots, C_n, Y$，其中 $X$ 继承自 $C_1$，对于 $1 \leq i \leq n-1$，$C_i$ 继承自 $C_{i+1}$，$C_n$ 继承自 $Y$。在上面的例子中，从 $D$ 到 $A$ 存在两条继承路径。第一条路径为 $D, B, A$，第二条路径为 $D, C, A$。

如果存在一对类 $X$ 和 $Y$，使得从 $X$ 到 $Y$ 存在至少两条不同的继承路径，则称该类图包含菱形继承。上面的类图就是菱形继承的经典示例。你的任务是判断给定的类图是否包含菱形继承。


## 说明/提示

**限制条件**

- $1 \leq T \leq 50$
- $0 \leq M_i \leq 10$

**测试集 1（14 分，结果可见）**

- $1 \leq N \leq 50$

**测试集 2（14 分，结果隐藏）**

- $1 \leq N \leq 1,000$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
3
1 2
1 3
0
5
2 2 3
1 4
1 5
1 5
0
3
2 2 3
1 3
0```

### 输出

```
Case #1: No
Case #2: Yes
Case #3: Yes```

# 题解

## 作者：Temp113 (赞：3)

## Solution

对每个结点进行一次 dfs，如果一个节点被再次访问，输出 ``Yes``，否则枚举完所有节点，输出 ``No``。

存图可用邻接矩阵或 vector，以下代码使用 vector。

注意：每次遍历将标记数组清空。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1005;
int t, n, x, y;
bool flg[N], vis;
vector<int> V[N];
inline void dfs(int u, int fa){
	if(vis) return ;
	for(auto &v : V[u]){
		if(vis) return ;
		if(flg[v]){
			cout << "Yes\n";
			vis = 1;
			return ;
		}
		flg[v] = 1;
		dfs(v, u);
	}
}
inline void solve(){
	cin >> n;
	vis = 0;
	for(int i = 1; i <= n; i++) V[i].clear();
	for(int i = 1; i <= n; i++){
		cin >> x;
		for(int j = 1; j <= x; j++){
			cin >> y;
			V[i].push_back(y);
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++) flg[j] = 0;
		flg[i] = 1;
		dfs(i, 0);
		if(vis) break;
	}
	if(!vis) cout << "No\n";
	return ;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> t;
	for(int kk = 1; kk <= t; kk++){
		cout << "Case #" << kk << ": ";
		solve();
	}
	return 0;
}
```

---

## 作者：IkillDream (赞：3)

# P13321 题解

## 思路

我们首先构建一个邻接矩阵，然后检查多路径：对于每个类，使用 DFS 函数来记录从该类到其他所有类的路径。如果在 DFS 过程中如果发现某个类被访问两次或更多次（即存在多条路径到达该类），则说明存在菱形继承，最后在查询一便，一旦发现任何菱形继承的情况，立即返回结果。

## [AC](https://www.luogu.com.cn/record/225050623) 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,m,p,g[1005][15],v[1005],kkk01,kkk02,kkk03,kkk04;
	cin>>t;
	for(int kkk05=1;kkk05<=t;kkk05++){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>m;
			for(int j=1;j<=m;j++) cin>>g[i][j];
			g[i][0]=m;
		}
		bool flg=0;
		for(int i=1;i<=n&&!flg;i++){
			memset(v,0,sizeof(v));
			queue<int>q;
			q.push(i);
			v[i]=1;
			while(!q.empty()&&!flg){
				int u=q.front();
				q.pop();
				for(int j=1;j<=g[u][0];j++){
					int w=g[u][j];
					if(v[w]==1){flg=1;break;}
					v[w]++;
					q.push(w);
				}
			}
		}
		cout<<"Case #"<<kkk05<<": "<<(flg?"Yes":"No")<<endl;
	}
	return 0;
}
```

## 后记

新知识：会的都回，不会的可以看一下 ```memset(数组名称,0,sizeof(数组名称));```，使用这个方法，我们可以使用简捷的代码将数组归零，以上代码我也用到 ```memset```，大家可以去借鉴一下哦。

以上代码花费了我将尽 $40$ 分钟的时间，如果决的我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

如果题解有写的不好的地方欢迎 AT 我，我会尽力改善。

---

## 作者：matrixPower (赞：2)

[传送门](https://www.luogu.com.cn/problem/P13321)

简单图论题。

对于题目给出的“菱形继承”，可以发现其性质：从同一个点出发可以抵达一个点两次。且此题数据量较小，直接 `dfs`。我们从一个点开始枚举，当在这次搜索遇到了一个点两次就证明存在“菱形继承”。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define lowbit(x) (x)&(-x)
using namespace std;

typedef double db;
typedef long long ll;
typedef __int128 III;
const db eps=1e-6;
const int inf=1e9;
void ll_cmax(ll &a,ll b){a=a>b?a:b;}
void ll_cmin(ll &a,ll b){a=a<b?a:b;}
void int_cmax(int &a,int b){a=a>b?a:b;}
void int_cmin(int &a,int b){a=a<b?a:b;}
bool db_eq(db a,db b){return fabs(a-b)<eps;}
bool number(char ch){return ch>='0' && ch<='9';}
bool lower(char ch){return ch>='a' && ch<='z';}
int sqlong(int n){int sq=sqrt(n)+1;return min(sq,n);}

const int MAXN=1000+5;
int T,n,b[MAXN],fl;
vector<int>a[MAXN];

void dfs(int x)
{
	b[x]=1;
	for(int i=0;i<a[x].size();i++)
	{
		if(b[a[x][i]]) 
		{
			fl=1;
			return ;
		}
		dfs(a[x][i]);
		if(fl) return ;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	int cnt=0;
	while(T--)
	{
		cin>>n;++cnt;
		cout<<"Case #"<<cnt<<": ";
		int l;
		for(int i=1;i<=n;i++)
		{
			cin>>l;
			a[i].clear();
			int x;
			for(int j=1;j<=l;j++)
			{
				cin>>x;
				a[i].push_back(x);
			}
		}
		for(int i=1;i<=n;i++)
		{
			memset(b,0,sizeof(b));fl=0;
			dfs(i);
			if(fl) break;
		}
		if(fl) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
//by Matrix_Power

```

---

## 作者：_hud (赞：1)

# 题解：[P13321 [GCJ 2012 #1C] Diamond Inheritance](https://www.luogu.com.cn/problem/P13321)

## 思路

一个简单的图论问题。我们用邻接表存图，然后在每个节点上跑一遍 bfs，若有节点被重复遍历则说明存在菱形继承。

那么这道题就迎刃而解了。具体实现可以看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
vector<int> g[N]; // 存图
bitset<N> f; // 记录节点是否被遍历过
int q[N], hh, tt; // bfs 队列
inline bool bfs(int s) {
    f.reset(); hh = 1, tt = 0; q[++tt] = s;
    while(hh <= tt) { // bfs
        int u = q[hh++];
        for(int x : g[u])
            if(f[x]) return 1;
            else q[++tt] = x, f[x] = 1;
    }
    return 0;
}
inline string sol() {
    int n; cin >> n;
    for(int i = 1, m; i <= n; ++i) {
        g[i].clear(); // 多测清空
        cin >> m;
        for(int j = 1, v; j <= m; ++j)
            cin >> v, g[i].push_back(v);
    }
    for(int i = 1; i <= n; ++i)
        if(bfs(i)) return "Yes";
    return "No";
}
signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T; cin >> T;
    for(int _ = 1; _ <= T; ++_)
        cout << "Case #" << _ << ": " << sol() << '\n';
    return 0;
}
```

---

## 作者：Eason_lyx (赞：1)

怎么感觉这题配不上黄题。

## 题目大意
给定你一个图，求对于图上的两点 $u$ 和 $v$，满足从 $u$ 到 $v$ 存在至少两条不同的路径。

你要解决 $T$ 组测试样例。
## 思路
由于每幅图点的数量 $N \le 1000$，所以可以直接搜索。具体来说，我们对于每一个点 $u$，执行搜索，当第一次搜索到点 $v$，记录一次。第二次搜索到时，打上标记，最后输出即可。

代码里有注释。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,x,y,d[N];
bool pd;//标记
vector<int>g[N];//邻接表存图
void dfs(int u){
    if(pd)return;//剪枝（当可行时就不用继续了）
    d[u]++;//记录
    for(int v:g[u]){
        if(d[v]){pd=1;return;}//如果d[v]=1，说明访问过
        dfs(v);//深搜
    }
}
void solve(int caseid){
    cin>>n;
    for(int i=1;i<=n;i++){
        g[i].clear();//记得清零
        cin>>x;
        for(int j=1;j<=x;j++){
            cin>>y;
            g[i].push_back(y);
        }
    }//注意输入格式
    pd=0;
    for(int i=1;i<=n;i++){
        memset(d,0,sizeof d);//初始化
        dfs(i);
        if(pd)break;//找到了，就不用再搜索    
    }//dfs每一个点
    if(pd) printf("Case #%d: Yes\n",caseid);
    else printf("Case #%d: No\n",caseid);
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    for(int i=1;i<=T;i++)
        solve(i);
    return 0;
}
```

---

## 作者：goodfish (赞：1)

# 思路

本题要求我们判断给定的继承关系图中是否存在**菱形继承**。菱形继承指的是在图中是否存在两个类 $X$ 和 $Y$，使得从 $X$ 到 $Y$ 存在至少两条不同的继承路径。

我们可以考虑使用 dfs 来遍历每个类的所有路径。对于每个类，我们需要检查是否存在某个类被通过多条不同路径继承，如果超过一次，即可直接返回输出 `Yes`，反之输出 `No`。

# Code:

```cpp
#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXN = 1010;
vector<int> mp[MAXN];
bool vis[MAXN];
bool flg;

void dfs(int u) {
	if (flg) return;
	vis[u] = true;
	for (int v : mp[u]) {
		if (vis[v]) {flg = 1;return;}
		dfs(v);
	}
}

void solve() {
	int T;cin >> T;
	for (int t = 1; t <= T; ++t) {
		int N; cin >> N;
		for (int i = 1; i <= N; ++i) mp[i].clear();
		
		for (int i = 1; i <= N; ++i) {
			int M;cin >> M;
			for (int j = 0; j < M; ++j) {
				int fat;cin >> fat;
				mp[i].pb(fat);
			}
		}
		
		flg = 0;
		for (int i = 1; i <= N && !flg; ++i) {
			memset(vis, 0, sizeof(vis));
			dfs(i);
		}
		
		cout << "Case #" << t << ": " << (flg ? "Yes" : "No") << endl;
	}
}

int main() {
	solve();
	return 0;
}
```

感谢感谢

---

## 作者：linhanmo (赞：1)

# 题解：[P13321 [GCJ 2012 #1C] Diamond Inheritance](https://www.luogu.com.cn/problem/P13321)

## 思路

见到 $n\le 1000$，考虑单次 $n^2$ 的做法。

对每个节点进行 bfs，如果有一个点被访问多次，输出 `Yes`，否则输出 `No`。

## 算法流程

1. 读入；
2. 对每个节点进行 bfs，在访问时加上判断；
3. 输出。

## [AC](https://www.luogu.com.cn/record/225449959) code

```cpp
#include <queue>
#include <bitset>
#include <stdio.h>
constexpr int N = 1001;
int t, n;
std::vector<int> e[N]; // 邻接表
inline bool bfs(int s) {
    std::bitset<N> vis; // 是否访问过
    std::queue<int> q;
    q.emplace(s), vis.set(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : e[u])
            if (vis[v]) return true; // 如果访问过，则存在菱形继承
            else vis.set(v), q.emplace(v);
    } return false;
}
int main(void) {
    scanf("%d", &t);
    for (int cs = 1; cs <= t; ++cs) {
        printf("Case #%d: ", cs), scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            int m; scanf("%d", &m), e[i].resize(m);
            for (int &j : e[i]) scanf("%d", &j);
        }
        for (int i = 1; i <= n; ++i)
            if (bfs(i)) { puts("Yes"); goto ED; };
        puts("No"); ED:;
    }
    return 0;
}
```

---

## 作者：chenzhuole1 (赞：1)

## 题解：P13288 [GCJ 2013 #1B] Osmos

[题目Link](https://www.luogu.com.cn/problem/P13321)

### 思路

图论题。没接触过图论的出门左转：[图的存储](https://oi-wiki.org/graph/save/)。

首先简化题意：给定一个有向图，判断是否存在两个不同的路径从节点 $X$ 到达节点 $Y$。

考虑图论。首先使用链式前向星建图，然后对每一个节点 $u$ 做深搜，记录能到达的所有节点，并在访问过程中统计是否某个节点被访问了两次。

时间复杂度 $O(N^2)$。

### Code


```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
using namespace std;
int T,n,m,x,y,cnt,head[10005];
struct E{
	int to,nxt;
}e[10005];
int vis[10005],f;
void ad(int u,int v)
{
	e[cnt]={v,head[u]},head[u]=cnt++;//建图
}
void dfs(int u,int tag)//寻找路径
{
	if(f) return;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]==tag){
			f=1;
			return;
		}
		vis[v]=tag;
		dfs(v,tag);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		cnt=0;
		memset(head,-1,sizeof head);
		cin>>n;
		for(int u=1;u<=n;u++)
		{
			cin>>m;
			while(m--){
				cin>>x;
				ad(u,x);//建边
			}
		}
		int ans=0;
		for(int u=1;u<=n&&!ans;u++)
		{
			memset(vis,0,sizeof vis);
			f=0;
			dfs(u,u);
			if(f)ans=1;//存在菱形路径
		}
		cout<<"Case #"<<i<<": "<<(ans?"Yes":"No")<<"\n";
	}
	return 0;
}
```

---

## 作者：ewq321 (赞：1)

## P13321 [GCJ 2012 #1C] Diamond Inheritance

### Problem

$T$ 组数据，每组数据给你一张图，问你存不存在两点间有两条路径。

### Solution

考虑 dfs 的过程，如果以一个点为起点 dfs，那么访问到一个点说明起点到这个点有一条路径，如果访问到一个访问到的点就说明找到了第二条路，那么此时就存在菱形继承。

直接以 $1$ 到 $n$ 每个点为起点 dfs，每次用 $vis_i$ 表示 $i$ 有没有访问过，如果遍历到一个点 v 满足 $vis_v = 0$，就将 $vis_v$ 改为 $1$，如果 $vis_v = 1$，那么说明存在。

### Code
```cpp
#include <bits/stdc++.h>

constexpr int maxn = 1010;
int vis[maxn], ok, n, T;
std::vector<int> G[maxn];
inline void dfs(int u){
	vis[u] = 1;
	for(int v : G[u]){
		if(vis[v]){
			ok = 1;
			return;
		}
		dfs(v);
	}
}
inline void solve(int id){
	ok = 0;
	std::cin >> n;
	for(int i = 1; i <= n; i++) G[i].clear();
	for(int i = 1; i <= n; i++){
		int k;
		std::cin >> k;
		for(int j = 1; j <= k; j++){
			int x;
			std::cin >> x;
			G[i].push_back(x);
		}
	} 
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++) vis[j] = 0;
		dfs(i);
	}
	if(ok){
		std::cout << "Case #" << id << ": Yes" << '\n';
	}
	else std::cout << "Case #" << id << ": No" << '\n';
}
int32_t main(){
	std::cin >> T;
	for(int i = 1; i <= T; i++){
		solve(i);
	}
}
```

---

## 作者：SwiftFlash (赞：0)

### 题意

在一张有向图中，判断任意两点间是否存在两条路径（即“菱形继承”）。

### 分析

判断两点间是否存在两条路径，我们可以从每个点开始dfs。对于遍历到的每个点$x$，如果$vis_x = 1$即点$x$曾被遍历过，则说明存在“菱形继承”。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> mp[1005];
bool vis[1005];
bool flag;
int T, n, m, mm, tmp;

void dfs(int x) {
    if(flag)return;
    vis[x] = 1;
    for(int i = 0;i < mp[x].size();i ++) {
        int y = mp[x][i];
        if(vis[y]) {
            flag = 1;
            return;
        }
        dfs(y);
    }
}

int main() {
    cin >> T;
    for(int t = 1;t <= T;t ++) {
        for(int i = 0;i <= 1000;i ++)mp[i].clear();
        cin >> n;
        for(int i = 1;i <= n;i ++) {
            cin >> mm;
            for(int j = 1;j <= mm;j ++) {
                cin >> tmp;
                mp[i].push_back(tmp);
            }
        }
        flag = 0;
        for(int i = 1;i <= n;i ++) {
            memset(vis, 0, sizeof(vis));
            dfs(i);
        }
        printf("Case #%d: ", t);
        if(flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
```
### 注意

多测数组要记得清空。特别地，每次dfs前都要清空vis数组。

---

## 作者：Soviet_Onion (赞：0)

## P13321 [GCJ 2012 #1C] Diamond Inheritance 题解
### Solution
虽然说题目中说是“类图”，但是我们还是以图的方式来做。由题意我们可以知道，当从一个点 $u$ 出发开始走，如果存在一个点 $v$，使得有两条路径 $L_1=(u,V_1,V_2,\dots,V_{l_1},v)(u \neq V_1 \neq \dots \neq V_{l_1} \neq v)$ 和 $L_2=(u,H_1,H_2,\dots,H_{l_2},v)(u \neq H_1 \neq \dots \neq H_{l_2} \neq v)$，使得 $L_1 \neq L_2$，那么就存在继承关系。这一点可以使用 BFS 或 DFS 实现。具体操作时在标记数组 $vis$ 中，如果再次访问到一个点 $x$，即 $vis_x=1$，就可以判断 `Yes` 了。如果 $n$ 个点全部不符合要求，那么输出 `No`。

**注意输出格式（Presentation Error）！**

时间复杂度 $\mathcal{O(n^2)}$。

### AC Code
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#define pb push_back
#define endl '\n'
using namespace std;
const int N=1e3+10;
vector<int>G[N];
bool vis[N],f;
int T,n,m,x,u;
void dfs(int x,int frm){
	if(vis[x]){
		f=1;
		return;
	}
	vis[x]=1;
	for(auto i:G[x]) if(i!=frm) dfs(i,x);
	return;
} 
void solve(int num){
	f=0;
	cin>>n;
	for(int i=1;i<=n;i++) if(!G[i].empty()) G[i].clear(); 
	for(int i=1;i<=n;i++){
		cin>>x;
		for(int j=1;j<=x;j++){
			cin>>u;
			G[i].pb(u);
		} 
	}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		dfs(i,0);
	}
	cout<<"Case #"<<num<<": ";
	if(f) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
    freopen("P13321.out","w",stdout);
	for(int i=1;i<=T;i++) solve(i);
	return 0;
}
```

---

## 作者：_aszxqw_ (赞：0)

这道题表达的意思就是：   
如果如果某个父类被访问超过一次，则存在菱形继承，就输出 ```Yes```。否则输出 ```No```。知道了这题让我们干什么就可以写代码了，数据范围 $n \leq 1000$ 那么就可以直接暴力搜索解决这题。     
# BFS 解法：   
```
#include <bits/stdc++.h>
using namespace std;
const int MN = 1000;
int g[MN + 5][15]; 
int a[MN + 5];
bool bfs(int N) {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; j++)
            a[j] = 0;
        queue<int> q;
        q.push(i);
        a[i] = 1;
        while (!q.empty()) {
            int cnt = q.front();
            q.pop();
            int M = g[cnt][0];
            for (int j = 1; j <= M; j++) {
                int k = g[cnt][j];
                a[k] += a[cnt];
                if (a[k] > 1)
                    return 1;
                q.push(k);
            }
        }
    }
    return 0;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int N;
        cin >> N;
        for (int j = 1; j <= N; j++) {
            cin >> g[j][0]; 
            for (int k = 1; k <= g[j][0]; k++) {
                cin >> g[j][k]; 
            }
        }
        if (bfs(N))
            cout << "Case #" << i << ": Yes" << '\n';
        else
            cout << "Case #" << i << ": No" << '\n';
    }
    return 0;
}
```

---

