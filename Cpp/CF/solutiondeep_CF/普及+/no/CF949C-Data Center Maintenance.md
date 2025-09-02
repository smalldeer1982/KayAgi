# 题目信息

# Data Center Maintenance

## 题目描述

给出 $n$ 个数据中心，$m$ 份资料。要把 $m$ 份资料放到其中的两个数据中心备份，需要保证任意时刻都可以至少在一个数据中心进行备份。定义一天有 $h$ 个小时，每个数据中心在一天内有一小时维护时间 $u_i$（$0 \leq u_i < h$），在这一小时内该数据中心无法进行备份。

由于某种原因，需要把一些数据中心的维护时间向后推迟 1 小时（一个数据中心的维护时间的向后推迟可能导致有的资料无法在任意时刻进行备份 且 若推迟前 $u_i = h - 1$ 那么推迟后 $u_i = 0$），请你求出最少需要向后推迟多少个数据中心，并把这些数据中心的编号输出出来。

## 样例 #1

### 输入

```
3 3 5
4 4 0
1 3
3 2
3 1
```

### 输出

```
1
3 ```

## 样例 #2

### 输入

```
4 5 4
2 1 0 3
4 3
3 2
1 2
1 4
1 3
```

### 输出

```
4
1 2 3 4 ```

# AI分析结果

### 题目内容
# 数据中心维护

## 题目描述
给出 $n$ 个数据中心，$m$ 份资料。要把 $m$ 份资料放到其中的两个数据中心备份，需要保证任意时刻都可以至少在一个数据中心进行备份。定义一天有 $h$ 个小时，每个数据中心在一天内有一小时维护时间 $u_i$（$0 \leq u_i < h$），在这一小时内该数据中心无法进行备份。

由于某种原因，需要把一些数据中心的维护时间向后推迟 1 小时（一个数据中心的维护时间的向后推迟可能导致有的资料无法在任意时刻进行备份 且 若推迟前 $u_i = h - 1$ 那么推迟后 $u_i = 0$），请你求出最少需要向后推迟多少个数据中心，并把这些数据中心的编号输出出来。

## 样例 #1
### 输入
```
3 3 5
4 4 0
1 3
3 2
3 1
```
### 输出
```
1
3 
```

## 样例 #2
### 输入
```
4 5 4
2 1 0 3
4 3
3 2
1 2
1 4
1 3
```
### 输出
```
4
1 2 3 4 
```

### 算法分类
图论

### 题解综合分析与结论
所有题解思路核心一致，均将数据中心看作点，依据数据中心维护时间推迟的影响关系构建有向图。若某数据中心 $x$ 推迟会致使数据中心 $y$ 也需推迟（即 $(u_x + 1) \bmod h = u_y$ 或 $(u_y + 1) \bmod h = u_x$），则从 $x$ 向 $y$ 连有向边。因图可能存在环，故利用Tarjan算法缩点，将强连通分量视为一个点，维护每个强连通分量中原始点的个数。最终答案为缩点后新图中出度为0的强连通分量里原始点个数的最小值。各题解主要差异在于代码实现细节，如变量命名、数据结构使用及具体操作步骤顺序等。

### 所选的题解
- **作者：Stars_Traveller (5星)**
    - **关键亮点**：思路阐述清晰，代码结构完整，使用标准库函数简化实现，如`vector`存储邻接表，`stack`实现Tarjan算法。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
vector<int>nbr[maxn], SCC[maxn];
stack<int>stk;
int out[maxn], a[maxn];
int n, m, dfn[maxn], used[maxn], vis[maxn], low[maxn], scc[maxn], cntc, cnt, ans, h, num[maxn];
void tarjan(int cur)
{
    dfn[cur]=low[cur]=++cnt;
    stk.push(cur);
    for(int q:nbr[cur])
    {
        if(!dfn[q])
        {
            tarjan(q);
            low[cur]=min(low[cur],low[q]);
        }
        else if(!scc[q]) 
        {
            low[cur]=min(low[cur],dfn[q]);
        }
    }
    if(low[cur]==dfn[cur])
    {
        cntc++;
        scc[cur]=cntc;
        num[cntc]++;
        SCC[cntc].push_back(cur);
        while(stk.top()!=cur)
        {
            int t=stk.top();
            stk.pop();
            scc[t]=cntc;
            num[cntc]++;
            SCC[cntc].push_back(t);
        }
        stk.pop();
    }
}
 
signed main()
{
    cin>>n>>m>>h;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        int x, y;
        cin>>x>>y;
        if((a[x]+1)%h==a[y])
        {
            nbr[x].push_back(y);
        }
        if((a[y]+1)%h==a[x])
        {
            nbr[y].push_back(x);
        }
    }
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)
    {
        for(auto nxt:nbr[i])
        {
            if(scc[i]!=scc[nxt])
            {
                out[scc[i]]++;
            }
        }
    }   
    int ans=114514191981000, id;
    for(int i=1;i<=cntc;i++)
    {
        if(out[i]==0&&num[i]<ans)
        {
            ans=num[i];
            id=i;
        }
    }
    sort(SCC[id].begin(),SCC[id].end());
    cout<<ans<<"\n";
    for(auto idd:SCC[id])cout<<idd<<" ";
}
```
    - **核心实现思想**：`tarjan`函数实现Tarjan算法寻找强连通分量，在`main`函数中构建图后调用`tarjan`，之后统计各强连通分量出度，找出出度为0且点数最少的强连通分量输出。
- **作者：yuzhechuan (4星)**
    - **关键亮点**：先强调理解题意重要性，对“主动推迟”概念解释清晰，代码中使用模板式写法，适合学习。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

const int N=1e5+5;
int h[N],en,H,n,m,scc[N],dfn[N],low[N],st[N],lim,cnt,du[N],sn,ans,sz[N],a[N];
bool v[N];

struct edge{
	int n,u,v;
}e[N];

void add(int x,int y){
	e[++en]=(edge){h[x],x,y};
	h[x]=en;
}

void tarjan(int x){ //找强联通分量
	low[x]=dfn[x]=++cnt;
	v[x]=1;
	st[++lim]=x;
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else{
			if(v[y]) low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		int top;
		sn++;
		for(;;){
			top=st[lim--];
			scc[top]=sn;
			v[top]=0;
			sz[sn]++;
			if(top==x) return ;
		}
	}
}

signed main(){
	read(n);read(m);read(H);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1,x,y;i<=m;i++){
		read(x);read(y);
		if((a[x]+1)%H==a[y]) add(x,y); //边的添加（关系的判断）
		if((a[y]+1)%H==a[x]) add(y,x);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=en;i++){
		int x=scc[e[i].u],y=scc[e[i].v]; //根据原先加的边判定出度
		if(x^y) du[x]++;
	}
	sz[0]=0x3f3f3f3f;
	for(int i=1;i<=sn;i++) if(!du[i]){
		if(sz[i]<sz[ans]) ans=i; //取无出度节点的最小size
	}
	write(sz[ans]);puts("");
	for(int i=1;i<=n;i++) if(scc[i]==ans) //是这个强联通分量的就输出
		write(i),putchar(' ');
}
```
    - **核心实现思想**：通过`add`函数构建邻接表，`tarjan`函数实现缩点，在`main`函数中完成输入、建图、缩点及寻找出度为0且点数最少的强连通分量并输出。
- **作者：Stone_Xz (4星)**
    - **关键亮点**：分析步骤详细，代码注释丰富，逻辑清晰，便于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, M = 1e5 + 5;

int n, m, h, cnt, tot, mini = 1e9, ans_id;

int t[N], dfn[N], low[N], scc[N], dis[N], sum[N], out[N];

int x[M], y[M];

bool vis[N], onstk[N];

stack<int> stk;

vector<int> nbr[N], have_[N];

void tarjan(int cur)
{
	stk.push(cur);
	onstk[cur] = true;
	dfn[cur] = low[cur] = ++cnt;
	for(auto nxt : nbr[cur])
	{
		if(!dfn[nxt])
		{
			tarjan(nxt);
			low[cur] = min(low[cur], low[nxt]); 
		}
		else if(onstk[nxt])
			low[cur] = min(low[cur], dfn[nxt]);
	}
	if(low[cur] == dfn[cur])
	{
		tot++;
		while(stk.top()!= cur)
		{
			int tmp = stk.top(); stk.pop();
			onstk[tmp] = false;
			sum[tot]++;
			have_[tot].push_back(tmp);
			scc[tmp] = tot;
		}
		stk.pop();
		onstk[cur] = false;
		sum[tot]++;
		have_[tot].push_back(cur);
		scc[cur] = tot;
	}
}

int main()
{
	cin >> n >> m >> h;
	for(int i = 1; i <= n; i++)
		cin >> t[i];
	for(int i = 1; i <= m; i++)                    // 建图 
	{
		cin >> x[i] >> y[i];
		if((t[x[i]] + 1) % h == t[y[i]])
			nbr[x[i]].push_back(y[i]);
		if((t[y[i]] + 1) % h == t[x[i]])
			nbr[y[i]].push_back(x[i]);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i);                     // 求 scc 
	for(int i = 1; i <= n; i++)
		for(auto j : nbr[i]) if(scc[i]!= scc[j])
			out[scc[i]]++;                         // 维护每个 scc 的出度 
	for(int i = 1; i <= tot; i++)
		if(out[i] == 0 && sum[i] < mini)           // 求答案 
		{
			mini = sum[i];
			ans_id = i;
		}
	cout << mini << "\n";
	vector<int> tmp = have_[ans_id];
	sort(tmp.begin(), tmp.end());
	for(auto i : tmp) cout << i << " ";
	return 0; 
}
```
    - **核心实现思想**：`tarjan`函数实现Tarjan缩点过程，`main`函数中先输入数据并建图，调用`tarjan`缩点后统计各强连通分量出度，找出符合条件的强连通分量输出。

### 最优关键思路或技巧
将数据中心维护时间推迟的影响关系转化为有向图的边，利用Tarjan算法处理有环图并缩点，这是解决本题的关键技巧。通过缩点将复杂的有环图转化为有向无环图（DAG），从而在DAG上使用贪心策略，选择出度为0且点数最少的强连通分量，简化问题求解。

### 拓展思路
同类型题常涉及将实际问题抽象为图论模型，特别是与拓扑排序、强连通分量相关的问题。类似套路如分析元素间的依赖或影响关系，构建有向图，若存在环则考虑缩点，之后在DAG上进行操作。例如在任务调度问题中，任务间可能存在先后依赖关系，若形成环需缩点后再安排调度顺序。

### 推荐题目
- [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)：经典的Tarjan缩点模板题，帮助巩固缩点算法。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：可通过构建图并利用图的连通性解决，与本题将实际问题转化为图论问题思路类似。
- [P2341 受欢迎的牛](https://www.luogu.com.cn/problem/P2341)：通过缩点后在DAG上分析出度情况求解，和本题在缩点后处理方式有相似之处。 

---
处理用时：118.46秒