# 题目信息

# [WFOI - 01]  刷题 （problem）

## 题目背景

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/ievt77rm)。

## 题目描述

你初始能力为 $0$。

现在有 $n$ 个题库，每个题库的题有同一个难度 $a_i$，并且题目数量可以视为无限多。现在你要刷 $m$ 道题，每道题都是所有题中你选择出来的一道。

假设你目前做到的题目难度是 $x$，则：

当你的能力比这个题大或等于此题时，你将花费你的能力以攻破此题（此时你的能力减去 $x$）；否则，你将认真钻研此题，钻研出此题后能力增加 $x$（此时不会导致能力减少）。

现在你想知道你做 $m$ 题后能力最大值。由于你的小伙伴也要刷题，所以**有多次询问**，询问之间相互独立，也就是说每次询问的能力初值为 $0$。

## 说明/提示

- **样例 $1$ 解释：**
	
    当 $m=1$ 时，依次选择 $6$；

	当 $m=2$ 时，依次选择 $4,6$；
    
    当 $m=3$ 时，依次选择 $1,4,6$；
- **样例 $2$ 解释：** 

    当 $m=1$ 时，依次选择 $1$；

	当 $m=2$ 时，依次选择 $1,1$；

**本题采用 Subtask 捆绑测试。**

  Subtask 编号 | $n\le$ | $m\le$ | $T\le$
  :-: | :-: | :-: | :-: |
  **Subtask #0 ($5\texttt{pts}$)** | $5$ | $5$ | $100$ |
  **Subtask #1 ($10\texttt{pts}$)** | $5$ | $5$ | $10^5$ |
  **Subtask #2 ($10\texttt{pts}$)** | $200$ | $200$ | $100$ |
  **Subtask #3 ($15\texttt{pts}$)** | $200$ | $200$ | $10^5$ |
  **Subtask #4 ($10\texttt{pts}$)** | $200$ | $10^{18}$ | $10^5$ |
  **Subtask #5 ($50\texttt{pts}$)** | $2000$ | $10^{18}$ | $10^5$ |
  
对于 $100\%$ 的数据，$1 \le T \le 10^5$，$1 \le n\le 2000$，$1 \le m \le 10^{18}$，$\forall i,0 \le a_i \le 2000$。

## 样例 #1

### 输入

```
5 3
1 2 3 4 6
1
2
3```

### 输出

```
6
10
11```

## 样例 #2

### 输入

```
1 2
1
1
2```

### 输出

```
1
0```

# AI分析结果

### 综合分析与结论
这些题解主要围绕通过建图和最短路算法解决该问题，核心思路基于两个关键结论：一是最终能力值范围在 $[0, 2 \cdot \max a - 1]$ 之间；二是若能在 $x$ 步到达某能力值，必能在 $x + 2$ 步到达。基于此，将能力值作为节点建图，处理奇偶最短路以应对 $m$ 较大的情况。

### 所选的题解
- **作者：Wf_yjqd (赞：10)  星级：4星**
    - **关键亮点**：思路清晰，详细阐述建图、BFS维护奇偶最短路及处理询问的过程，代码实现完整且有注释辅助理解。
    - **个人心得**：提到说起来简单但写起来容易出错，强调了实现细节的重要性。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,bool> p;
// 快读快写部分省略
const int maxn=4084;
struct Node{
    int to,ne;
}e[maxn*maxn/2];
ll m;
int n,T,a[maxn],dis[maxn][2],ans[maxn];
int head[maxn],ecnt=1;
void add(int u,int v){
    e[ecnt]={v,head[u]};
    head[u]=ecnt++;
    return ;
}
queue<p> q;
void bfs(int x){
    memset(dis,0x7f,sizeof(dis));
    dis[x][0]=0;
    q.push({x,0});
    p t;
    while(!q.empty()){
        t=q.front();
        q.pop();
        for(int i=head[t.first];i;i=e[i].ne){
            if(e[i].to!=x&&dis[e[i].to][t.second^1]>1e9){
                dis[e[i].to][t.second^1]=dis[t.first][t.second]+1;
                q.push({e[i].to,t.second^1});
            }
        }
    }
    return ;
}
int main(){
    read(n);
    read(T);
    for(int i=1;i<=n;i++)
        read(a[i]);
    for(int i=0;i<=3999;i++)
        for(int j=1;j<=n;j++)
            if(i>=a[j])
                add(i,i-a[j]);
            else if(i+a[j]<=3999)
                add(i,i+a[j]);
    bfs(0);
    for(int i=1;i<=3999;i++){
        if(dis[i][0]<=3999)
            ans[dis[i][0]]=i;
        if(dis[i][1]<=3999)
            ans[dis[i][1]]=i;
    }
    for(int i=2;i<=3999;i++)
        ans[i]=max(ans[i],ans[i-2]);
    while(T--){
        read(m);
        if(m>3999)
            print(ans[m&1?3999:3998]);
        else
            print(ans[m]);
        putchar('\n');
    }
    fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```
核心实现思想：先通过`add`函数建图，将每个能力值节点与通过做题库题目能到达的能力值节点相连。`bfs`函数从初始能力值0开始，维护奇数步和偶数步到达各节点的最短路`dis`。最后在`main`函数中，根据预处理的最短路结果`ans`，快速回答每次询问。

- **作者：YellowBean_Elsa (赞：10)  星级：4星**
    - **关键亮点**：从DP角度出发，将问题转化为最短路问题，代码简洁明了，注释清晰。
```cpp
//coder: YB-Elsa of Ahtohallan
#include<bits/stdc++.h>
#define fu(i,a,b) for(register int i = a, I = (b) + 1; i < I; ++i)
#define fd(i,a,b) for(register int i = a, I = (b) - 1; i > I; --i)
using namespace std;
typedef long long ll;
const int N=2022;

inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x;
}int n,T,a[N];
ll dp[N<<1][2];
queue<int> q;
ll m;bool flg;
signed main(){
	n=read(),T=read();
	fu(i,1,n)a[i]=read();
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	memset(dp,0x7f,sizeof(dp));
	dp[0][0]=0;
	q.push(0);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		fu(i,1,n){
			if(x<a[i]){
				flg=0;
				if(dp[x+a[i]][0]>dp[x][1]+1){
					dp[x+a[i]][0]=dp[x][1]+1;
					q.push(x+a[i]);flg=1;
				}if(dp[x+a[i]][1]>dp[x][0]+1){
					dp[x+a[i]][1]=dp[x][0]+1;
					if(!flg)q.push(x+a[i]);
				}
			}else{
				flg=0;
				if(dp[x-a[i]][0]>dp[x][1]+1){
					dp[x-a[i]][0]=dp[x][1]+1;
					q.push(x-a[i]);flg=1;
				}if(dp[x-a[i]][1]>dp[x][0]+1){
					dp[x-a[i]][1]=dp[x][0]+1;
					if(!flg)q.push(x-a[i]);
				}
			}
		}
	}
	while(T--){
		scanf("%lld",&m);
		fd(i,a[n]<<1,0)
			if(dp[i][m&1LL]<=m){
				printf("%d\n",i);
				break;
			}
	}
    return 0;
}
```
核心实现思想：用`dp[i][p]`表示达到能力值`i`的最小步数（`p`表示步数奇偶性），通过`q`队列进行类似SPFA的最短路更新。每次从队列中取出一个能力值`x`，根据与各题库难度`a[i]`的大小关系，更新通过一步操作能到达的能力值的最小步数及奇偶性。最后根据询问的`m`，从大到小遍历能力值，找到满足步数要求的最大能力值。

- **作者：伟大的王夫子 (赞：4)  星级：4星**
    - **关键亮点**：指出本题与另一道题思路相似，代码逻辑清晰，通过邻接表建图和队列实现最短路。
```cpp
#include <bits/stdc++.h>
using namespace std;
template <class T>
inline void Rd(T &x) {
    x = 0;
    bool f = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    if (f)
        x = -x;
}
typedef long long ll;
int n, m, Q, a[2005], maxa;
ll f[4005][2];
bool v[4005][2];
vector<int> e[4005];
int main() {
    Rd(n), Rd(Q);
    for (int i = 1; i <= n; ++i) Rd(a[i]), maxa = max(maxa, a[i]);
    for (int i = 0; i <= 2 * maxa - 1; ++i)
    	for (int j = 1; j <= n; ++j) 
    		e[i].push_back(i >= a[j]? i - a[j] : i + a[j]);
	memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    queue<pair<int, bool> > q;
    v[0][0] = 1;
    q.push(make_pair(0, 0));
    while (q.size()) {
    	int x = q.front().first;
    	bool p = q.front().second;
    	q.pop();
    	for (int i = 0; i < e[x].size(); ++i) {
    		int y = e[x][i];
    		if (v[y][p ^ 1]) continue;
    		f[y][p ^ 1] = f[x][p] + 1;
    		v[y][p ^ 1] = 1;
    		q.push(make_pair(y, p ^ 1));
		} 
	}
	while (Q--) {
		ll m;
		Rd(m);
		for (int i = 2 * maxa - 1; i >= 0; --i)
			if (f[i][m & 1] <= m) {
				printf("%d\n", i);
				break;
			}	
	}
    return 0;
}
```
核心实现思想：通过`e`邻接表建图，每个能力值节点与通过做各题库题目能到达的能力值节点相连。`f`数组记录从0出发到达各能力值的奇偶数步的最小步数，利用队列进行BFS更新。最后根据询问的`m`，从大到小遍历能力值，找到满足步数要求的最大能力值。

### 最优关键思路或技巧
1. **利用范围限制**：确定最终能力值范围在 $[0, 2 \cdot \max a - 1]$，减少了需要处理的状态数量。
2. **奇偶性处理**：基于操作步数的奇偶性，通过维护奇数步和偶数步到达各能力值的最短路，巧妙解决 $m$ 较大的问题。
3. **建图与最短路**：将能力值作为节点，根据题目规则建图，然后通过BFS等算法求最短路，从而得到不同步数下能达到的最大能力值。

### 可拓展思路
此类题目属于状态转移与路径规划问题，通常可通过建图转化为图论问题求解。类似套路包括分析状态转移规律、利用奇偶性或周期性简化问题、通过预处理最短路等信息快速回答询问。同类型题可考虑状态转移条件更复杂、节点与边的定义更隐晦的题目。

### 相似知识点洛谷题目
1. [P5663 [CSP - J2019] 加工零件](https://www.luogu.com.cn/problem/P5663)：同样涉及状态转移和奇偶性判断，通过建图和最短路求解。
2. [P1339 热浪](https://www.luogu.com.cn/problem/P1339)：基础的最短路问题，可加深对最短路算法的理解与应用。
3. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：单源最短路模板题，有助于巩固最短路算法的实现。 

---
处理用时：113.75秒