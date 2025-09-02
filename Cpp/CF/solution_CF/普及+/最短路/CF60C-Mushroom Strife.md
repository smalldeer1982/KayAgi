# Mushroom Strife

## 题目描述

$Pasha$ 和 $Akim$ 正在制作一张森林地图：草坪是地图的顶点，连接草坪的道路是地图的边。
 
他们决定通过以下方式对每个草坪上蘑菇的数量进行编码：在两个草坪之间的边上，写下两个数字，即两个草坪蘑菇数量的最大公约数和最小公倍数。

但是有一天， $Pasha$ 和 $Akim$ 争吵了起来，并撕毁了地图。

 $Pasha$ 只剩下其中的一部分，共有 $m$ 条路。请帮助 $Pasha$ 使用他已知的部分地图来恢复每个草坪上的蘑菇数量。

结果不一定是唯一的，请帮助 $Pasha$ 恢复任意一张合法的地图或者判断不存在任何一种合法的地图。

保证初始地图上道路上的数字不小于 $1$ 并且不超过 $10^6$ 。

## 样例 #1

### 输入

```
1 0
```

### 输出

```
YES
1 ```

## 样例 #2

### 输入

```
2 1
1 2 1 3
```

### 输出

```
YES
1 3 ```

## 样例 #3

### 输入

```
3 2
3 2 1 2
3 1 1 10
```

### 输出

```
YES
5 1 2 ```

## 样例 #4

### 输入

```
2 1
1 2 3 7
```

### 输出

```
NO
```

# 题解

## 作者：CarroT1212 (赞：2)

24-07-10 upd：远古题解，应同学要求简化了少量的代码细节。

------------

### 题目大意

有一张 $n$ 个点 $m$ 条边的图。现在分别给定这 $m$ 条边所连接的两点编号，两点权值的最大公约数和最小公倍数。请你分别求出这 $n$ 个点的权值。保证权值都是不大于 $10^6$ 的正整数。

数据范围：$1 \le n \le 100$，$0 \le m \le \frac{n\cdot(n-1)}{2}$，$1 \le \gcd,\operatorname{lcm} \le 10^6$。

------------

### 解法分析

设 $a,b$ 为正整数，不难推出 $b=\dfrac{\gcd\{a,b\}\cdot\operatorname{lcm}\{a,b\}}{a}$。

那么有这个东西，我们就可以在已知连通块内一个点的权值的条件下把整个连通块的点的权值算出来了。

所以我们可以枚举图中每个连通块中任意一点的权值，然后把整个连通块的点的权值都算出来看看有没有满足条件的解，如果枚出一种解就进入到下一个连通块的枚举。

但是有一个问题，如果枚举范围是 $[1,10^6]$ 的话，算一下时间复杂度，感觉不太稳（不过似乎能过），于是我们可以加一个小小的优化：

设与第 $i$ 个点相连的有 $d_i$ 条边，这 $d_i$ 条边所连接两点权值的最大公约数分别为 $g_{i,1},g_{i,2},\cdots,g_{i,d_i}$，最小公倍数分别为 $l_{i,1},l_{i,2},\cdots,l_{i,d_i}$，则不难发现，第 $i$ 个点的权值最小为 $\operatorname{lcm}\{g_{i,1},g_{i,2},\cdots,g_{i,d_i}\}$，最大为 $\gcd\{l_{i,1},l_{i,2},\cdots,l_{i,d_i}\}$。稍微想一下应该就能明白。

于是我们就可以把枚举范围缩减到 $[\operatorname{lcm}\{g_{i,1},g_{i,2},\cdots,g_{i,d_i}\},\gcd\{l_{i,1},l_{i,2},\cdots,l_{i,d_i}\}]$ 了（注意这个区间有可能不存在），而且注意枚举的时候只能枚举 $\operatorname{lcm}\{g_{i,1},g_{i,2},\cdots,g_{i,d_i}\}$ 的倍数，原因显然。

9-7 upd：感谢管理 @dottle 的建议，实际上枚举这一步还能继续优化。这段可以改为枚举每个连通块中任意一点的邻边的 $\operatorname{lcm}$ 的因数。这样可能会更快，因为这些数的因数个数比较小。代码暂时先不改了，可以自己想一下怎么实现这个优化，日后我可能会挑个时间把代码写出来更新。

其它的实现细节见代码。

------------

### 代码

（有少量压行，码丑轻喷）

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const ll N=107,M=1e4+7;
struct edge { ll to,gcd,lcm; };
ll n,m,from[M],to[M],gcd[M],lcm[M],ans[N],conn[N],cong[N];
//ans[i]：答案数组
//cong[i]：上文 lcm{g_i}
//conn[i]：上文 gcd{l_i}，同时记录每个点的权值是否已经有解
vector <edge> v[N]; //存边
unordered_map <ll,bool> mp; //枚举时存连通块
bool dfs(ll x) {
	for (edge i:v[x]) if (!mp[i.to]) {
		//只要有一处地方不符合条件就可以直接返回
		if (i.gcd*i.lcm%ans[x]!=0) return 0; //不整除
		ans[i.to]=i.gcd*i.lcm/ans[x],mp[i.to]=1;
		if (__gcd(ans[x],ans[i.to])!=i.gcd) return 0; //不符合数据
		if (!dfs(i.to)) return 0;
	}
	return 1;
}
int main() {
	scanf("%lld%lld",&n,&m);
	for (ll i=1;i<=n;i++) ans[i]=cong[i]=1;
	for (ll i=1;i<=m;i++) {
		scanf("%lld%lld%lld%lld",&from[i],&to[i],&gcd[i],&lcm[i]);
		v[from[i]].pb({to[i],gcd[i],lcm[i]});
		v[to[i]].pb({from[i],gcd[i],lcm[i]});
		conn[from[i]]=__gcd(conn[from[i]],lcm[i]); //gcd{l_i}
		conn[to[i]]=__gcd(conn[to[i]],lcm[i]);
		cong[from[i]]=cong[from[i]]*gcd[i]/__gcd(cong[from[i]],gcd[i]); //lcm{g_i}
		cong[to[i]]=cong[to[i]]*gcd[i]/__gcd(cong[to[i]],gcd[i]);
	}
	for (ll i=1;i<=n;i++) for (ll j=cong[i];j<=conn[i];j+=cong[i]) // 用 conn 归 0 实现了连通块的处理
		if (conn[i]%j==0) { //枚举权值满足条件
			mp.clear();
			mp[i]=1,ans[i]=j;
			if (dfs(i)) { //如果搜出了一种解
				for (pair<ll,ll> i:mp) conn[i.first]=0; //记录有解
				break;
			}
		}
	for (ll i=1;i<=n;i++) if (conn[i]) { printf("NO"); return 0; } //存在点的权值无解
	printf("YES\n");
	for (ll i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：Peaky (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF60C)。
### 题目大意
给定 $n$ 个点，$m$ 条边，和每一条边两端的节点的最大公约数和最小公倍数。
### 思路
题目给出，每一个数均不大于 $10^6$，又有熟知结论，最大公约数和最小公倍数的积等于原数之积。所以我们可以枚举每一个连通块的第一个节点，从而算出连通块内，所有节点代表的数。
### 实现
链式前向新 $+$ bfs 计算连通块内所有节点代表的数。
### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=1e2+10,M=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int n,m,head[M],edge[M],last[M],idx,f;
int LCM[N][N],GCD[N][N],d[N],tot[N];
bool vis[N],book[N];
void add(int u,int v){
	edge[++idx]=v;
	last[idx]=head[u];
	head[u]=idx;
}
int __lcm(int a,int b) {return a*b/__gcd(a,b);}
void bfs(int st,int value){
	memset(tot,0,sizeof(tot));
	memset(book,0,sizeof(book));
	book[st]=1;
	tot[st]=value;
	queue<int> q;
	q.push(st);
	while(!q.empty()){
		int t=q.front(); q.pop();
		for(int i=head[t];i;i=last[i]){
			int v=edge[i],val=LCM[t][v]*GCD[t][v]/tot[t];
			if(tot[v]&&tot[v]!=val) return;
			else if(tot[v]) continue;
			if(!tot[v]&&(__gcd(val,tot[t])!=GCD[v][t]||__lcm(val,tot[t])!=LCM[v][t])) return;
			tot[v]=val;
			book[v]=1;
			q.push(v);
		}
	}
	for(int i=1;i<=n;i++) if(book[i]) d[i]=tot[i],vis[i]=book[i];
	f=1;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,g,l;
		cin>>u>>v>>g>>l;
		add(u,v);
		add(v,u);
		LCM[u][v]=LCM[v][u]=l;
		GCD[u][v]=GCD[v][u]=g;
	}
	for(int j=1;j<=n;j++){
		if(vis[j]) continue;
		f=0;
		vis[j]=1;
		for(int i=1;i<=1e6;i++) if(!f) bfs(j,i);
		if(!f) return cout<<"NO",0;
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++) cout<<d[i]<<" ";
	return 0;
}
 
```

---

