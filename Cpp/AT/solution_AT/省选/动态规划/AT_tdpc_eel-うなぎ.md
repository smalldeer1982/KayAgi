# うなぎ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_eel

给定一棵 $N$ 个点的无根树，第 $i$ 条边为 $(a_i,b_i)$。求出选出 $K$ 条点集不交边数 $\ge 1$ 的路径的方案数对 $(10^9+7)$ 取模后的结果。



## 说明/提示


- $ 2\le N\le 1000 $
- $ 1\le K\le 50 $
- $ 1\le a_i,b_i\le N $
- 输入的是一棵树。

## 样例 #1

### 输入

```
4 1
1 2
2 3
3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
8 3
1 2
4 6
6 7
3 2
2 4
4 5
8 6```

### 输出

```
9```

# 题解

## 作者：Miraik (赞：2)

较简单的树形 DP 题，~~感觉不如建造军营~~。

首先注意到我们需要路径在顶点上无交，这意味着每个点最多被一条链覆盖到。

我们寻找一种计数方式：对于树上满足祖先-后代关系的链，我们将后代看作起点，祖先看作终点。而不满足祖先-后代关系的链即为两条终点为 LCA 的祖先-后代链合并起来。我们将这样的链称之为合并链。

考虑树形 dp。我们设 $f_{u,i,j}(j\in \{0/1/2/3\})$ 表示在 $u$ 的子树内，选出了 $i$ 条链，$j$ 的含义如下时的方案数：

$ \begin{cases}
u \space \text{未被链覆盖} \ (j = 0) \\
u \space \text{作为一条新链的起点} \ (j=1) \\
u \space \text{目前处在一条祖先}-\text{后代链上}\ (j=2) \\
u \space \text{处在一条合并链上} \ (j=3)
\end{cases}$

转移时，我们相当于在当前的 $u$ 之下再挂了一棵 $v$ 的子树，枚举当前 $u$ 子树和 $v$ 子树的 $j$ 状态，考虑合并起来的贡献。

转移的过程是较为繁琐的，在此给出写转移式时的思路：

对于 $j_v=0/3$ 的情况，这棵子树接上去对 $j_u$ 的当前状态不会有任何影响。

对于 $j_v=1$ 的情况，$j_u$ 可以为 $0$ 或 $2$，前者表示从一个点 $v$ 变为链 $v-u$，后者表示 $u$ 子树内一条链和 $v$ 合并。

对于 $j_v=2$ 的情况：

- $j_u=0$

则 $v$ 这条链可以选择以 $v$ 为终点，也可以选择继续延伸到 $u$，对应的新的 $j_u$ 分别为 $0$ 和 $2$。

- $j_u=1/3$

只能以 $v$ 为终点。

- $j_u=2$

则 $v$ 这条链可以选择以 $v$ 为终点，也可以选择与 $u$ 所在链合并。

依照上面的过程写出对应的转移即可，最终答案即为 $f_{1,k,0}+f_{1,k,2}+f_{1,k,3}$。时间复杂度 $O(nk^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
int n,m,f[1001][51][4],tf[51][4],ans;
// 0,1,2,3 : 无 / 向上起点 / 向上非起点 / 子树有合并
struct Edge{ int to,nxt; }e[2001]; int head[1001],tot;
inline void add(int u,int v){ e[++tot]={v,head[u]}; head[u]=tot; }
inline void dfs(int u,int fa){
    f[u][0][0]=f[u][1][1]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,u);
        for(int i=0;i<=m;i++)
            for(int j=0;j<4;j++)
                tf[i][j]=f[u][i][j],f[u][i][j]=0;
        for(int i=0;i<=m;i++)
            for(int j=0;j<=m;j++){
            	if(i+j<=m)
                (f[u][i+j][0]+=1ll*tf[i][0]*f[v][j][3]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][1]+=1ll*tf[i][1]*f[v][j][3]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][2]+=1ll*tf[i][2]*f[v][j][3]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][3]+=1ll*tf[i][3]*f[v][j][3]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][0]+=1ll*tf[i][0]*f[v][j][2]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][2]+=1ll*tf[i][0]*f[v][j][2]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][1]+=1ll*tf[i][1]*f[v][j][2]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][2]+=1ll*tf[i][2]*f[v][j][2]%mod)%=mod;
                if(i && j && i+j-1<=m)
				(f[u][i+j-1][3]+=1ll*tf[i][2]*f[v][j][2]%mod)%=mod;
				if(i+j<=m)
                (f[u][i+j][3]+=1ll*tf[i][3]*f[v][j][2]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][2]+=1ll*tf[i][0]*f[v][j][1]%mod)%=mod;
                if(i && j && i+j-1<=m)
                (f[u][i+j-1][3]+=1ll*tf[i][2]*f[v][j][1]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][0]+=1ll*tf[i][0]*f[v][j][0]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][1]+=1ll*tf[i][1]*f[v][j][0]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][2]+=1ll*tf[i][2]*f[v][j][0]%mod)%=mod;
                if(i+j<=m)
                (f[u][i+j][3]+=1ll*tf[i][3]*f[v][j][0]%mod)%=mod;
            }
    }
}
int main(){
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v); add(v,u);
    }
    dfs(1,-1);
    ans=((f[1][m][0]+f[1][m][2])%mod+f[1][m][3])%mod;
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：shenxinge (赞：0)

感谢 @wind_seeker 的帮助。

### 题意

给定一棵 $n$ 个点的树，求能选出 $k$ 条至少包含两个顶点的链，且任意两条链在顶点上不交的方案数。

$ 1 \le n \le 10^3 , 1 \le k \le 50$

### 解法

其实数据范围可以开到更大。

考虑树形 dp，定义状态 $f_{u,i,k\in\left[0,2\right]}$ 代表以 $u$ 为根，子树内包含自身有 $i$ 条长度大于等于 $2$ 的链。 

$f_{u,i,0}$ 代表 $u$ 为孤立点（即不被任何链覆盖）的方案数。

$f_{u,i,1}$ 代表 $u$ 为单链上的方案数（即从一个子树往上经过根节点并要往上合并的状态）。

$f_{u,i,2}$ 代表 $u$ 为两条链合并的位置（即从一个子树往上经过根节点并延伸向根的另一个子树）的方案数。

考虑如何转移一对父子 $(u,v)$。

对于 $u$ 为孤立点：

$$f_{u,i+j,0}=\sum_{i=0}^{k}\sum_{i+j \le k} f_{u,i,0} \times (f_{v,j,0}+f_{v,j,1}+f_{v,j,2})$$

其意义为当前 $u$ 为孤立点时，子树怎么接都不改变 $u$ 为孤立点的状态。

对于 $u$ 为向上的链上的点：

仍旧有：

$$f_{u,i+j,1}=\sum_{i=0}^{k}\sum_{i+j \le k} f_{u,i,1} \times (f_{v,j,0}+f_{v,j,1}+f_{v,j,2})$$

其意义为当前 $u$ 为向上的链上的点时，子树怎么接都不改变 $u$ 为向上的点的状态。

附加有：

$$f_{u,i+j+1,1}=\sum_{i=0}^{k}\sum_{i+j+1 \le k} f_{u,i,0} \times f_{v,j,0}$$

其意义为选出两个孤立点连成一条链。

对于 $u$ 的状态为有一条从一个子树延伸出的链经过 $u$ 再到 $u$ 的另一个子树。

仍旧有：

$$f_{u,i+j,1}=\sum_{i=0}^{k}\sum_{i+j \le k} f_{u,i,1} \times (f_{v,j,0}+f_{v,j,1}+f_{v,j,2})$$

其意义为 子树怎么接都不改变 $u$ 为子树内两条链并的点的状态。

附加有：

$$f_{u,i+j-1,2}=\sum_{i=0}^{k}\sum_{i+j-1 \le k} f_{u,i,1} \times f_{v,j,1}$$

其意义为合并两条链。

$$f_{u,i+j,2}=\sum_{i=0}^{k}\sum_{i+j-1 \le k} f_{u,i,1} \times f_{v,j,0}$$

其意义为将一个孤立点和根合并成链后再和另一棵子树内的链合并。

这样就结束了，时间复杂度为 $O(nk^2)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std; constexpr int maxn(1010),maxk(55),mod(1e9+7);
struct mint{
	int x;mint(int o=0){x=o;}mint&operator+=(mint a){return(x+=a.x)%=mod,*this;}mint&operator-=(mint a){return(x+=mod-a.x)%=mod,*this;}
	mint&operator*=(mint a){return(x=1ll*x*a.x%mod),*this;}mint&operator^=( int b){mint a=*this;x=1;while(b)(b&1)&&(*this*=a,1),a*=a,b>>=1;return*this;}
	mint&operator/=(mint a){return*this*=(a^=mod-2);}friend mint operator+(mint a,mint b){return a+=b;}friend mint operator-(mint a,mint b){return a-=b;}
	friend mint operator*(mint a,mint b){return a*=b;}friend mint operator/(mint a,mint b){return a/=b;}friend mint operator^(mint a, int b){return a^=b;}
	mint operator-(){return 0-*this;}bool operator==(const mint b)const{return x==b.x;}
};
int n,k; mint f[maxn][maxk][3],g[maxk][3]; vector<int> vec[maxn];

// f[0] 代表孤立点 f[1] 代表有一条链 f[2] 代表 u 为 lca , 经过 u 的链
inline void dfs(int u,int fa){ f[u][0][0]=1;
	for(int v:vec[u]) if(v^fa){ dfs(v,u);
		for(int i=0;i<=k;i++)
			g[i][0]=f[u][i][0],f[u][i][0]=0,
			g[i][1]=f[u][i][1],f[u][i][1]=0,
			g[i][2]=f[u][i][2],f[u][i][2]=0;
		for(int i=0;i<=k;i++) for(int j=0;j<=k;j++){
			if(i+j<=k){
				f[u][i+j][0]+=g[i][0]*(f[v][j][0]+f[v][j][1]+f[v][j][2]);
				if(i+j!=0) f[u][i+j][1]+=g[i][0]*f[v][j][1]+g[i][1]*(f[v][j][0]+f[v][j][1]+f[v][j][2]);
				if(i+j!=0) f[u][i+j][2]+=g[i][1]*f[v][j][0]+g[i][2]*(f[v][j][0]+f[v][j][1]+f[v][j][2]);
			}
			if(i+j+1<=k) f[u][i+j+1][1]+=g[i][0]*f[v][j][0]; // 选择两个孤立点
			if(i+j-1<=k&&i+j-1>0) f[u][i+j-1][2]+=g[i][1]*f[v][j][1]; // 选择两条链合并
		}
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin >> n >> k; for(int i=1,u,v;i<n;i++) cin >> u >> v,vec[u].push_back(v),vec[v].push_back(u);
	dfs(1,0);
	cout << (f[1][k][0]+f[1][k][1]+f[1][k][2]).x << '\n';
	return 0;
}
```


---

