# なめらかな木

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ddcc2017-final/tasks/ddcc2017_final_d

$ N $ 頂点の木が与えられます。 頂点には番号 $ 1,\ 2,\ ...,\ N $ がついており、$ i $ 番目の辺は頂点 $ a_i,\ b_i $ をつないでいます。

木の頂点に整数 $ 1,\ 2,\ ...,\ N $ をそれぞれ $ 1 $ 個ずつ書き込むことを考えます。 頂点 $ i $ に書き込んだ値を $ c_i $ とします。

ただし、頂点 $ u,\ v $ が隣り合っている、つまり辺 $ (u,\ v) $ が存在するならば、 $ |c_u\ -\ c_v|\ ≦\ 2 $ を満たしていないといけません。(10:53)変数名を修正しました

このような書き込み方は何通りあるでしょうか、$ 1000000007\ =\ 10^9\ +\ 7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 50 $
- $ 1\ ≦\ a_i,\ b_i\ ≦\ N $
- 入力は木になっている

### Sample Explanation 1

頂点 $ 1 $ に $ 3 $ を書き込む必要があります。

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
1 5```

### 输出

```
24```

## 样例 #2

### 输入

```
6
1 2
1 3
1 4
1 5
1 6```

### 输出

```
0```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
12```

## 样例 #4

### 输入

```
7
1 3
2 3
4 3
5 4
5 6
5 7```

### 输出

```
48```

# 题解

## 作者：luanyanjia (赞：3)

首先考虑暴力 DP，设 $f(i,v_1,v_2,now)$ 为已经将前 $i$ 个数填入，$i$ 填在 $v_1$，$j$ 填在 $v_2$ 点，已经填完点的状态是 $now$（状压一下存在一个 long long 里）的方案数。转移时直接枚举下一个点暴力转移，只需要保证新的点没有被访问过，并且填上新点后，$v_1$ 的所有邻接点都被填上即可。

其实直接暴力转移，复杂度是对的。

我们考虑对于一个状态 $(i,v_1,v_2,now)$，将 $v_1$ 和 $v_2$ 在树中剪掉，剩下的连通块（最多 $7$ 个，因为每个点度数最多为 $4$）中，要么全被填了，要么都没被填。因为一个连通块内被填的点上的数一定小于等于 $n-2$，后面填的点一定和这些点的差一定大于 $2$，因此一定不合法。

状态数最多为 $n^3 \times 2^7$，复杂度 $O(n^3 \times 2^7)$。

**注意特判 $n=1$ 的情况。**

#### 代码

```cpp

#include<bits/stdc++.h>
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int mod=1e9+7;
unordered_map<long long,int> mp[65][65][65];
vector<int> e[65];int n;
signed main(){
	rd(n);
	if(n==1){
		printf("1\n");
		return 0;
	}
	for(int i=1;i<n;i++){
		int x,y;rd(x,y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	for(int v1=1;v1<=n;v1++)
		for(int v2=1;v2<=n;v2++){
			if(v1==v2)continue;
			mp[2][v1][v2][(1ll<<v2)|(1ll<<v1)]+=1;
		}
	for(int i=2;i<n;i++){
		for(int v1=1;v1<=n;v1++){
			for(int v2=1;v2<=n;v2++){
				if(v1==v2)continue;
				long long bas=0;
				for(int x:e[v1])bas|=(1ll<<x);
				for(int x=1;x<=n;x++){
					for(pair<long long,int> p:mp[i][v1][v2]){
						if(p.first&(1ll<<x))continue;
						if(((p.first|(1ll<<x))&bas)==bas){
							(mp[i+1][v2][x][p.first|(1ll<<x)]+=mp[i][v1][v2][p.first])%=mod;
						}
					}
				}
			}
		}
	}
	int ans=0;
	for(int v1=1;v1<=n;v1++)
		for(int v2=1;v2<=n;v2++){
			if(v1==v2)continue;
			for(auto p:mp[n-1][v1][v2])
				(ans+=p.second)%=mod;
		}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Purslane (赞：0)

# Solution

> 好题不难，关键在于发现状态数很少。

--------

大家上来应该就能发现：$\forall 1 \le u \le n$，$\deg_u \le 4$。（显然每个数的合法邻域个数都 $\le 4$）

因此把权值为 $i$ 和 $i-1$ 的点删去之后，**最多剩下 $7$ 个联通块**。而每个联通块里所有点必须**全部 $\le i-2$ 或全部 $\ge i+1$**（使用反证法易得）

因此考虑设状态为 $(i,p_1,p_2,S)$ 表示权值为 $i-1$ 的点是 $p_1$，权值为 $i$ 的点是 $p_2$，权值 $\le i$ 的点的集合为 $S$ 的方案数。

实际上只有 $O(n^2 \times 2^7)$ 种状态，考虑它们的转移即可（直接再填一个点即可）

维护 $p_1$ 和 $p_2$ 的目的是，在将其删去的时候 check 它的邻域中比他大的点的情况（插入点的时候显然只考虑了比他小的点的情况）。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+5,MOD=1e9+7;
int n,nxt[MAXN];
vector<int> G[MAXN];
struct INFO {int p1,p2,S;};
map<INFO,int> dp[MAXN];
bool operator <(INFO A,INFO B) {
	if(A.p1!=B.p1) return A.p1<B.p1;
	if(A.p2!=B.p2) return A.p2<B.p2;
	if(A.S!=B.S) return A.S<B.S;	
}
int vis[MAXN];
int dfs(int u) {
	int ans=1ll<<u;
	vis[u]=1;
	for(auto v:G[u]) if(!vis[v]) ans|=dfs(v);
	return ans;	
}
vector<int> gain_blocks(int p1,int p2) {
	memset(vis,0,sizeof(vis)),vis[p1]=vis[p2]=1;
	vector<int> ans;
	ffor(i,1,n) if(!vis[i]) ans.push_back(dfs(i));
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	if(n<=2) return cout<<n,0;
	ffor(i,1,n-1) {
		int u,v;
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
		nxt[u]|=1ll<<v,nxt[v]|=1ll<<u;
	}
	ffor(i,1,n) if(G[i].size()>4) return cout<<0,0;
	ffor(i,1,n) ffor(j,i+1,n) {
		auto vc=gain_blocks(i,j);
		int S=(1ll<<i)+(1ll<<j);
		ffor(st,0,(1<<vc.size())-1) {
			int s=S;
			ffor(id,0,vc.size()-1) if(st&(1<<id)) s|=vc[id];
			dp[__builtin_popcountll(s)][{i,j,s}]=0,dp[__builtin_popcountll(s)][{j,i,s}]=0;
		}
	}
	ffor(i,1,n) ffor(j,1,n) if(i!=j) dp[2][{i,j,(1ll<<i)+(1ll<<j)}]=1;
	ffor(i,2,n-1) {
		for(auto pr:dp[i]) {
			int p1=pr.first.p1,p2=pr.first.p2,s=pr.first.S;
			ffor(u,1,n) if(!(s&(1ll<<u))) {
				if((nxt[u]&s&((1ll<<p1)+(1ll<<p2)))!=(nxt[u]&s)||((s+(1ll<<u))&nxt[p1])!=nxt[p1]||!dp[i+1].count({p2,u,s+(1ll<<u)})) continue ;
				dp[i+1][{p2,u,s+(1ll<<u)}]=(dp[i+1][{p2,u,s+(1ll<<u)}]+pr.second)%MOD;
			}
		}
	}
	int ans=0;
	for(auto pr:dp[n]) ans=(ans+pr.second)%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

