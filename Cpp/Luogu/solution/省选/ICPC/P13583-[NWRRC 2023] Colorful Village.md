# [NWRRC 2023] Colorful Village

## 题目描述

彩色村庄是一个著名的旅游胜地。村里有 $2n$ 座房屋，编号从 $1$ 到 $2n$。每座房屋都有 $n$ 种颜色中的一种，颜色编号从 $1$ 到 $n$。巧合的是，每种颜色恰好有两座房屋被涂成该颜色。

彩色村庄有 $2n-1$ 条双向道路。每条道路连接两座不同的房屋，并且通过这些道路可以从任意一座房屋到达任意另一座房屋。

Catherine 正计划前往彩色村庄旅游。由于时间有限，她希望选择一个包含 $n$ 座房屋的集合 $S$ 进行参观，且每种颜色恰好选一座房屋。然而，由于 Catherine 还需要在房屋之间移动，所选择的房屋集合必须是连通的。换句话说，集合 $S$ 中的任意两座房屋都可以仅通过集合 $S$ 内的房屋和道路互相到达。

请帮助 Catherine 找到一个满足条件的连通房屋集合 $S$，包含 $n$ 座房屋且每种颜色各选一座，或者报告不存在这样的集合。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
4
1 3 1 3 4 4 2 2
1 6
5 3
2 4
7 1
7 5
5 8
2 5
3
1 1 2 2 3 3
1 2
2 3
3 4
4 5
5 6```

### 输出

```
2 3 5 7
-1```

# 题解

## 作者：AnteAntibe (赞：7)

P13583 [NWRRC 2023] Colorful Village 题解
---
集训的课上出现了这道题，我听了思路觉得非常高妙。同样过的人不多，于是决定写题解，殊不知这是噩梦的开始……    
WA 了28发，调+写七个小时，兜兜转转废寝忘食才终于写出这道题目。感慨万千。

## Description

题意很简单：给定一个 $2 \times n$ 个点的图，每个点有一种颜色，总共有 $n$ 种颜色。要求给出一个颜色互不相同，且点数为 $n$ 的联通块或者输出无解。

## Solution

一样的，我们先观察样例。

![样例](https://cdn.luogu.com.cn/upload/image_hosting/p382jtem.png)

发现一件事：模拟出这样一个联通块十分难以找到一个固定的策略！或许这是一个关键？启示**我们可以先钦定一个根结点，然后考虑答案。**

同时，一种颜色只有两个点，不多不少，而且有必须只选一个的限制。就像是把点分成了两部分！    
略有所悟！建二分图吗？时间复杂度飞起来了！  

继续思考：如果钦定了根结点且要求根结点必选，那么对于每一个点：只要我选了，我的父结点必须选上。否则联通块就断掉了。    
两部分的点，而且点和点之间有选或不选的转移关系……

我们是不是可以把一种颜色看作一个布尔类型变量，选第一个点就是赋值为 $0$，选第二个点就是赋值为 $1$……

大彻大悟了！**我们需要使用 2-SAT 解决这个问题！！**

现在考虑怎么具体的建造 2-SAT 的。其他许多人的解法似乎都是对于每一个点建立选 / 不选的两条边，但是我觉得这样完全没有必要啊！   
我们用 $\neg p$ 表示与点 $p$ 颜色相同的另一个点。每个颜色对应一个变量，由于每个变量一定会有赋值，联通块颜色不重复且大小为 $n$ 的限制就自然而然被满足了！    

接下来就只有一种不合法情况：我选了，我的父结点没有选。    
以下条件满足其一即可：
* 不选 $p$
* 选了父结点

构建形如 $a \vee b$ 的若干组条件即可。

还有最后一个问题：如何选择钦定的根节点？有三种方式：    
1. 由于每次选择一半的点，随机选择根节点，选择 $\log_2 n$ 次基本可以获得正确的构造。
2. 一定有一个点颜色为 $1$ ，故分别选择颜色为 $1$ 的两个结点当做根结点跑一遍即可。
3. 因为树的重心子树的大小一定 $\leq n$ ，所以答案一定包含树的重心，直接选择树的重心作为树根。

这里选择第二种写法。

code：
```
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e6 + 10;
/*
各变量的含义：
T 数据组数
n ,l ,r ,thi_col 题目输入
cols 记录每个结点的颜色，第一次出现的颜色记为 i ，第二次记为 n+i
ctoi 通过颜色找到对应的结点
es ,es2 ,hd ,hd2 分别为输入的图和2-SAT建出的图
father 记录原图中的父子关系
is_can 这一组是否出现答案
tarjan 前面那一坨都是 tarjan 板子使用的
*/

ll n ,T;
ll cols[N] ,ctoi[N];
struct zxm {
    ll to ,nxt;
}es[N] ,es2[N];
ll hd[N] ,idx;
void add(ll u ,ll v) {
    es[++idx].to = v;
    es[idx].nxt = hd[u];
    hd[u] = idx;
}

ll hd2[N] ,iidx;
void add2(ll u ,ll v) {
    es2[++iidx].to = v;
    es2[iidx].nxt = hd2[u];
    hd2[u] = iidx;
}

ll is_can = 0 ,father[N];

void dfs(ll u ,ll fa) { //找父节点
    father[u] = fa;
    for (int i=hd[u] ;i ;i = es[i].nxt) {
        ll v = es[i].to;
        if (v == fa) {
            continue;
        }
        dfs(v ,u);
    }
}

ll dfn[N] ,low[N] ,idx_dfn ,st[N] ,top ,in_st[N];
ll bel[N] ,idx_b;
void tarjan(ll u) {
    dfn[u] = low[u] = ++idx_dfn;
    st[++top] = u;
    in_st[u] = 1;
    for (int i = hd2[u] ;i ;i = es2[i].nxt) {
        ll v = es2[i].to;
        if (dfn[v] == 0 ) {
            tarjan(v);
            low[u] = min(low[u] ,low[v]);
        }
        else if (in_st[v] == 1) {
            low[u] = min(low[u] ,dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ll thi = u;
        bel[thi] = ++idx_b;
        for (;;) {
            thi = st[top];
            top--;
            in_st[thi] = 0;
            bel[thi] = idx_b;
            if (thi == u) {
                break;
            }
        }
    }

}
             
void work (ll rt) { //跑2-SAT
    // init
    iidx = 0;
    for (int i=1 ;i<=2*n+2 ;i++) {
        hd2[i] = 0;
        father[i] = 0;
    }

    // 建新图
    dfs(ctoi[rt] ,0);
    for (int i=1 ;i<=n*2 ;i++) {
        if (father[i] == 0) { //我是电棍，我没有滚木
            continue;
        }
        ll anti_i ,anti_fa ,fa;
        fa = father[i];
        anti_i = ctoi[( (cols[i] > n) ? -1 : 1 ) * n + cols[i]];
        anti_fa = ctoi[( (cols[fa] > n) ? -1 : 1 ) * n + cols[fa]];
        //我没选 / 我爹选了 => choose anti_i or choose fa
        add2(i ,fa);
        add2(anti_fa ,anti_i);
    }

    //2-SAT part
    for (int i=1 ;i<=2*n+2 ;i++) {
        dfn[i] = low[i] = st[i] = in_st[i] = bel[i] = 0;
        idx_dfn = idx_b = top = 0;
    }

    for (int i=1 ;i<=n*2 ;i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    int flag = 1;
    for (int i=1 ;i<=n ;i++) {
        if (bel[ctoi[i]] == bel[ctoi[i+n]]) {
            flag = 0;
            break;
        }
    }
    if (flag == 0) {
        return;
    }
    is_can = 1;
    for (int i=1 ;i<=n ;i++) {
        if (bel[ctoi[i]] < bel[ctoi[i+n]]) {
            printf("%lld " ,ctoi[i]);
        }
        else {
            printf("%lld " ,ctoi[i+n]);
        }
    }
    printf("\n");
}

int main() {
    scanf("%lld" ,&T);
    for (;T--;) {
        //init
        idx = 0;
        is_can = 0;
        scanf("%lld" ,&n);
        for (int i=1 ;i<=2*n ;i++) {
            cols[i] = 0;
            ctoi[i] = 0;
        }

        for (int i=1 ;i<=2*n ;i++) {
            hd[i] = 0; // init
            ll thi_col;
            scanf("%lld" ,&thi_col);
            if (ctoi[thi_col] == 0) {
                cols[i] = thi_col;
                ctoi[thi_col] = i;
            }
            else {
                cols[i] = n + thi_col;
                ctoi[thi_col + n] = i;
            }
        }
        for (int i=1 ;i<2*n ;i++) {
            ll l ,r;
            scanf("%lld %lld" ,&l ,&r);
            add(l ,r);
            add(r ,l);
        }
        work(1);
        if (is_can == 1) {
            //cout<<"Sycamore_TY"<<endl;
            continue;
        } 
        work(1+n);
        if (is_can == 0) {
            printf("-1\n");
            continue; // 虽然不用写这一行但是仪式感这一块
        }
    }
    return 0;
}
```
有关为什么我写了七个小时，可以观看我发的帖子。。。

---

## 作者：Mzk2333 (赞：3)

发现我们实际需要求的是一个大小为 $n$，且包含每种颜色恰一个点的连通块。

这个东西并不好直接刻画，我们考虑把一个节点作为根，并钦定这个点必选，则一个点 $u$ 的限制可以描述为：若 $u$ 被选，则其父亲一定被选；若 $u$ 不被选，则其孩子一定不被选；若 $u$ 被选，则与其同色的另一个点一定不被选；若 $u$ 不被选，则与其同色的另一个点一定被选。

这就变成了一个典型的 2-SAT 问题。

接下来考虑如何选根节点，这里做法就比较多了。若存在方案，则合法的根节点数量必定 $\ge n$，所以可以随机选点，或者找重心作为根。同时由于一种颜色中两个节点必定至少有一个在方案中被选，所以也可以随便找一个颜色，让其对应的两个节点作为根，分别算一次。

以下代码采用最后一种方法，时间复杂度 $O(n)$。
```
#include<bits/stdc++.h>
using namespace std;
#define INF (int)(1e9)
#define int long long

inline int read(){
   char ch=getchar(); int f=1;
   while(ch>'9'||ch<'0'){ if(ch=='-') f=-1; ch=getchar();}
   int sum=ch-'0';
   while((ch=getchar())>='0'&&ch<='9') sum=(sum<<3)+(sum<<1)+ch-'0';
   return sum*f;
}
inline void write(int x){
   if(x<0)putchar('-'),x=-x;
   if(x>9)write(x/10);
   putchar(x%10+'0');
}

const int N=1e5+9,M=1e5+9;
const int mod=1e9+7;
#define fir first
#define sec second

int n,col[N][2];
vector<int> G[N<<2],F[N<<2];
int dfn[N<<2],low[N<<2],idx;
int bel[N<<2],scc,d;
int s[N<<2],top;
bool in[N<<2];
void tarjan(int u){
    dfn[u]=low[u]=++idx;
    s[++top]=u; in[u]=1;
    for(auto v:G[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(in[v]) low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        ++scc;
        while(s[top+1]!=u){
            int now=s[top]; top--;
            in[now]=0;
            bel[now]=scc;
        }
    }
}
void dfs(int u,int fa){
    if(fa){
    	G[u].push_back(fa);
    	G[fa+d].push_back(u+d);
	}
    for(auto v:F[u]){
        if(v!=fa) dfs(v,u);
    }
}
bool calc(int rt){
    for(int i=1;i<=(n<<2);++i) G[i].clear();
    G[d+rt].push_back(rt);
    for(int i=1;i<=n;++i){
        G[col[i][0]+d].push_back(col[i][1]);
        G[col[i][1]+d].push_back(col[i][0]);
     	G[col[i][0]].push_back(col[i][1]+d);
     	G[col[i][1]].push_back(col[i][0]+d);
    }
    dfs(rt,0);
    
    for(int i=1;i<=(n<<2);++i) s[i]=0; 
    top=0; scc=0; idx=0;
    for(int i=1;i<=(n<<2);++i) dfn[i]=low[i]=0;
    for(int i=1;i<=(n<<2);++i) in[i]=0,bel[i]=0;
    for(int i=1;i<=(n<<2);++i)
        if(!dfn[i]) tarjan(i);
    
    for(int i=1;i<=(n<<1);++i){
        if(bel[i]==bel[i+d])
            return 0;
    }
    return 1;
}
void solve(){
    for(int i=1;i<=(n<<1);++i) F[i].clear();

    n=read();
    for(int i=1;i<=n;++i) col[i][0]=0;
    for(int i=1;i<=(n<<1);++i){
        int x=read();
        if(!col[x][0]) col[x][0]=i;
        else col[x][1]=i;
    }
    for(int i=1;i<(n<<1);++i){
        int u=read(),v=read();
        F[u].push_back(v);
        F[v].push_back(u);
    }
    d=(n<<1);
    if(calc(col[1][0])){
        for(int i=1;i<=(n<<1);++i){
          	if(bel[i]<bel[i+d]) cout<<i<<' '; 
        }
        cout<<'\n';
        return ;
    }
    if(calc(col[1][1])){
        for(int i=1;i<=(n<<1);++i){
            if(bel[i]<bel[i+d]) cout<<i<<' '; 
        }
        cout<<'\n';
        return ;
    }
    cout<<-1<<'\n';
}
signed main(){ 
    int T; cin>>T;
    while(T--) solve();
}
```

---

## 作者：180700553dd (赞：1)

# 题目大意：

给定一个节点数为 $2n$ 的树，每一个点有一种颜色且每一种颜色对应两个点，求一个连通块使得每种颜色的点各出现一次。

# 解题思路：

考虑选点的限制有哪些：每种颜色有且只有一个，选的点必须连通。如果一个点想要加入答案，必须满足以上条件，其中颜色的限制是两个点之间的限制，我们需要将连通的限制也变成两个点之间的限制。

若在答案中挑选一个点将其变为根，那么一个点被选择必须要他的父亲节点被选择。此时问题转化成一个 $0/1$ 的问题（对应着选与不选），并且有一些两两之间的限制，可以用 2-SAT 来解决。

现在的问题来到了如何钦定一个点被选且为根，我们不可能将所有点都枚举一遍，否则复杂度为 $O(n^2)$ 的。我们有以下三种方法：

- ### 法一：
  随机挑选 $m$ 个点来跑。随机一个点不包含在答案中的概率为 $\frac{1}{2}$，那么 $m$ 个点都不在答案中的概率为 $(\frac{1}{2})^m$。让 $m$ 在 $20$ 左右，可以使得不在答案中的概率极小，可以忽略不计。

- ### 法二：
  发现同一个颜色的两个点必定有一个在答案中，用这两个点跑即可。

- ### 法三：
  树的问题通常可以考虑重心来解答。下面大致感性说明一下本题答案有解的话必定包含重心：设中心为 $u$，重心性质可得任意一个 $u$ 的子节点 $v$ 都满足子树大小 $\le n$，若任意答案不包含 $u$，那么子树大小 $< n$ 的 $v$ 必定不可能选出 $n$ 个点，故他们不在答案中。对于子树大小为 $n$ 的节点，在答案中当且仅当每种颜色的点都在其子树内，而如果这样剩下的 $n$ 个点必定也满足条件且包含 $u$，与任意答案不含 $u$ 矛盾。综上，我们只需要跑中心即可，若重心不可行则无解。

# 代码部分：

我的代码是用重心跑的，在注释中解释了步骤。
代码如下：

```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
int t;
const int N = 2e5 + 5;
int col[N];
int other[N], v[N];
//dfs
vector<int> ve[N];//原树 
int fa[N], si[N], mx[N];
int n;
int root;
void dfs1(int x, int f){
	si[x] = 1;
	for(int i = 0;i < ve[x].size();i++){
		int v = ve[x][i];
		if(v == f) continue;
		dfs1(v, x);
		si[x] += si[v];
		mx[x] = max(mx[x], si[v]);
	}
	if(mx[x] <= n && 2 * n - si[x] <= n) root = x;
}
void dfs2(int x, int f){
	for(int i = 0;i < ve[x].size();i++){
		int v = ve[x][i];
		if(v == f) continue;
		fa[v] = x;
		dfs2(v, x);
	}
}
//2-SAT 
vector<int> ve2[2 * N];//2-SAT的图 
int dfn[2 * N], low[2 * N], tot;
stack<int> st;
int in[2 * N];
int scc, belong[2 * N];
void tarjan(int x){
	dfn[x] = low[x] = ++tot;
	in[x] = 1;
	st.push(x);
	for(int i = 0;i < ve2[x].size();i++){
		int v = ve2[x][i];
		if(dfn[v] == 0){
			tarjan(v);
			low[x] = min(low[x], low[v]);
		}else if(in[v]){
			low[x] = min(low[x], dfn[v]);
		}
	}
	if(dfn[x] == low[x]){
		scc++;
		while(st.top() != x){
			int v = st.top();
			st.pop();
			in[v] = 0;
			belong[v] = scc;
		}
		st.pop();
		in[x] = 0;
		belong[x] = scc;
	}
}
void solve(){
	for(int i = 1;i <= 2 * n;i++){
		if(fa[i]){
			ve2[i].push_back(fa[i]);
			ve2[fa[i] + 2 * n].push_back(i + 2 * n);//父亲与本节点的限制 
		}
	}
	for(int i = 1;i <= 2 * n;i++){
		ve2[i].push_back(other[i] + 2 * n);
		ve2[i + 2 * n].push_back(other[i]);//相同颜色之间必须选一个的限制 
	}
	for(int i = 1;i <= 4 * n;i++){
		if(dfn[i] == 0) tarjan(i);
	}
	for(int i = 1;i <= 2 * n;i++){
		if(belong[i] == belong[i + 2 * n]){
			cout << "-1\n";
			return;
		}
	}
	for(int i = 1;i <= 2 * n;i++){
		if(belong[i] <= belong[i + 2 * n]){//1代表选择，直接输出 
			cout << i << ' ';
		}
	}
	cout << '\n';
} 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1;i <= 2 * n;i++) other[i] = 0;
		for(int i = 1;i <= 2 * n;i++) v[i] = 0;
		for(int i = 1;i <= 2 * n;i++) mx[i] = 0;
		for(int i = 1;i <= 2 * n;i++) fa[i] = 0;
		for(int i = 1;i <= 4 * n;i++) dfn[i] = 0;
		for(int i = 1;i <= 2 * n;i++){
			ve[i].clear();
		} 
		for(int i = 1;i <= 4 * n;i++){
			ve2[i].clear();
		}
		tot = scc = 0;
		for(int i = 1;i <= 2 * n;i++){
			cin >> col[i];
			if(v[col[i]]){
				other[i] = v[col[i]];
				other[v[col[i]]] = i;
			}
			v[col[i]] = i;
		}
		for(int i = 1;i < 2 * n;i++){
			int u, v;
			cin >> u >> v;
			ve[u].push_back(v);
			ve[v].push_back(u);
		}
		root = 1;
		dfs1(1, -1);//寻找重心赋给root 
		dfs2(root, -1);//找到fa 
		solve();
	} 
	return 0;
} 
```

# 后记（一些闲话）：

此乃本蒟蒻的第一篇题解，有问题欢迎随时指出，求管理员大大通过。如果觉得对你有帮助，请支持一下吧。

---

## 作者：UNVRS (赞：0)

## 题意

给出 $2n$ 个点的树，结点上有 $1\sim n$ 的颜色，每种颜色恰好两个点，找出一个大小为 $n$ 且恰好包含 $1\sim n$ 的所有颜色连通块，或输出无解。多测。

$t\le10^5,\sum n\le10^5$

## 官方题解翻译

（感觉比 B 简单）

[官方题解原文](https://nerc.icpc.global/archive/2023/northern/tutorial.pdf)。

设 $b_u = \texttt{true}$ 表示 结点 $u$ 被选，同理 $b_u = \texttt{false}$ 表示结点 $u$ 未选。假设我们已经选出一个结点 $r$，我们可以以其为根考虑其他结点。选点有连通块的限制与两个相同颜色点必须恰好选择一个的限制，可以被形式化成以下两个充要条件：

- 对于连通块的父子关系 $u,fa_u$，有 $\lnot b_u \lor b_{fa_u}$。

- 对于同色结点 $u,v$，有 $(b_u\lor b_v)\land(\lnot b_u \lor b_v)$。

于是我们得到了一个 2-SAT 问题，可以在 $O(n)$ 复杂度内求解。

接下来唯一的问题是考虑找到一个必选的结点 $r$，有两种选法：

- 对于颜色相同的结点，其中必有一个被选，分别判断答案即可。

- 找出重心，若去除重心之后连通块大小都小于 $n$ 则其必选。若有不含重心的大小为 $n$ 且恰好为解的连通块，那么另外包含重心的 $n$ 个点也会是一个合法解，故重心一定可以选择。

## 译者补充

具体的建图是四种边：

$$u\to fa_u\\ \lnot fa_u \to \lnot u\\ u\to\lnot v\\ v\to\lnot u$$

（写的时候忘了第二种罚了两发 QAQ）

---

## 作者：littleKtian (赞：0)

### 题意
有一个节点数为 $2n$ 的树。每个节点有一个颜色，一共 $n$ 种颜色，每种颜色各有 $2$ 个对应节点。在树上找一个大小为 $n$ 的连通块，要求其中恰好包含每种颜色的节点各 $1$ 个。

### 思路
记 $a_i$ 表示第 $i$ 个节点是否被选入集合内，$1$ 代表选入。

任意位置的连通块并不好做，所以我们考虑枚举第 $1$ 种颜色所选的节点 $u$ 强制加入集合内。令 $u$ 为根，则连通块可以看作到根节点的连通性。

此时所有的要求条件可以看作如下集中限制：

+ 强制 $u$ 加入集合，即强制 $a_u=1$；
+ 连通性：设 $p$ 为 $q(q\neq u)$ 在树上的父亲节点，则有 $a_q=1\longrightarrow a_p=1$ 和 $a_p=0\longrightarrow a_q=0$；
+ 每种颜色各 $1$ 个节点：设 $x$ 和 $y$ 为颜色相同的两个节点，则有 $a_x \oplus a_y=1$。

上述限制都可以用 2-SAT 解决。

做两次 2-SAT 即可，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,c[200005],w[100005][2],ans[100005],tot;
vector<int> edget[200005];
void addt(int u,int v){edget[u].push_back(v);}
vector<int> edge[400005];
void add(int u,int v){edge[u].push_back(v);}
void dfst(int u,int fa){
	for(int i=0,in=edget[u].size();i<in;i++){
		int v=edget[u][i];
		if(v!=fa)add(2*n+u,2*n+v),add(v,u),dfst(v,u);
	}
}
int lo[400005],xh[400005],dfn,h[400005],toth;
int z[400005],zd,us[400005];
void dfs(int u){
	lo[u]=xh[u]=++dfn,z[++zd]=u,us[u]=1;
	for(int i=0,in=edge[u].size();i<in;i++){
		int v=edge[u][i];
		if(!xh[v])dfs(v),lo[u]=min(lo[u],lo[v]);
		else if(us[v])lo[u]=min(lo[u],xh[v]);
	}
	if(lo[u]==xh[u]){
		++toth;
		while(z[zd]!=u)h[z[zd]]=toth,us[z[zd]]=0,--zd;
		h[z[zd]]=toth,us[z[zd]]=0,--zd;
	}
}
bool sat(int x){
	for(int i=1;i<=4*n;i++)edge[i].clear();
	add(2*n+x,x);
	dfst(x,0);
	for(int i=1;i<=n;i++){
		int u=w[i][0],v=w[i][1];
		add(u,2*n+v),add(2*n+u,v);
		add(v,2*n+u),add(2*n+v,u);
	}
	for(int i=1;i<=4*n;i++)lo[i]=xh[i]=0;
	dfn=toth=0;
	for(int i=1;i<=4*n;i++)if(!xh[i])dfs(i);
	for(int i=1;i<=2*n;i++)if(h[i]==h[i+2*n])return false;
	tot=0;
	for(int i=1;i<=2*n;i++)if(h[i]<h[i+2*n])cout<<i<<' ';
	cout<<'\n';
	return true;
}
void work(){
	cin>>n;
	for(int i=1;i<=n;i++)w[i][0]=w[i][1]=0;
	for(int i=1;i<=2*n;i++){
		cin>>c[i];
		if(w[c[i]][0]==0)w[c[i]][0]=i;else w[c[i]][1]=i;
	}
	for(int i=1;i<=2*n;i++)edget[i].clear();
	for(int i=1;i<2*n;i++){
		int u,v;cin>>u>>v;
		addt(u,v),addt(v,u);
	}
	bool check;
	check=sat(w[1][0]);
	if(check)return;
	check=sat(w[1][1]);
	if(check)return;
	cout<<-1<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;cin>>T;
	while(T--)work();
}
```

---

