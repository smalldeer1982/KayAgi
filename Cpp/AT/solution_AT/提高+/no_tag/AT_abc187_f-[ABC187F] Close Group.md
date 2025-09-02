# [ABC187F] Close Group

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc187/tasks/abc187_f

$ N $ 頂点 $ M $ 辺の単純無向グラフが与えられます。 このグラフの頂点には $ 1,\ 2,\ \dots,\ N $ の番号が付けられており、$ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結びます。

以下の条件を満たすように辺を $ 0 $ 本以上取り除いたときの、グラフの連結成分の個数としてあり得る最小値を求めてください。

**条件**  
 $ 1\ \le\ a\ <\ b\ \le\ N $ を満たす任意の頂点の組 $ (a,\ b) $ について、 頂点 $ a $ と頂点 $ b $ が同じ連結成分に属するならば、頂点 $ a $ と頂点 $ b $ を直接結ぶ辺が存在する。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 18 $
- $ 0\ \le\ M\ \le\ \frac{N(N\ -\ 1)}{2} $
- $ 1\ \le\ A_i\ <\ B_i\ \le\ N $
- $ i\ \neq\ j $ ならば $ (A_i,\ B_i)\ \neq\ (A_j,\ B_j) $

### Sample Explanation 1

辺を取り除かないと、 $ (2,\ 3) $ の組が条件を満たしません。 どちらかの辺を取り除くと、頂点 $ 2 $ と頂点 $ 3 $ が非連結になり、条件を満たします。

## 样例 #1

### 输入

```
3 2
1 2
1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
1```

## 样例 #3

### 输入

```
10 11
9 10
2 10
8 9
3 4
5 8
1 8
5 6
2 5
3 6
6 9
1 9```

### 输出

```
5```

## 样例 #4

### 输入

```
18 0```

### 输出

```
18```

# 题解

## 作者：ZBH_123 (赞：4)

## 题目分析
对于此题，看到数据范围 $1 \le N \le 18$，再加上题目中要求的最少的连通块数量，便可以想到状压 DP。设 $dp_{\mathbb{S}}$ 表示目前考虑到的点所组成的集合为 $\mathbb{S}$ 时，所需要的最小连通块数量，那么最终答案自然就是 $dp_{\mathbb{U}}$（$\mathbb{U}$ 是点组成的全集）。接下来推导初始化和状态转移：
### 1. 初始化
对于我们设计的状态，可以想到初始化的内容：将符合条件的点集合的状态设为 $1$，其他的设为极大值。那么，怎么判断一个点集是否符合条件呢？我们可以选择枚举每一个集合，接着枚举集合中的每一个点，看看他是否和集合内的其他点相连。可是这么做的时间复杂度为 $O(N^2 2^N)$，虽然可以接受，但仍能优化。

我们设 $edge_i$ 表示与 $i$ 相连的所有的组成的集合状态。每当输入一条连接 $x$ 和 $y$ 的边时，就往 $edge_x$ 和 $edge_y$ 中分别加入 $y$ 和 $x$。另外，对于每个点 $i$，都需要在 $edge_i$ 中加入它自己。接下来，我们要做的其实和前面提到的初始化方法大致相同，只不过省去了枚举其他集合内的点的步骤，而是将其换成验证目前枚举的集合是否是当前枚举的点连边集合（$edge$）的子集（想一想为什么）。

这样，我们就把初始化的问题解决了。
### 2. 状态转移
回到题目，题目支持的操作为删边，也就是说，我们在状态转移时只能从当前枚举到的集合的子集中去找。设现在枚举到了 $\mathbb{S}$，我们枚举它的子集 $\mathbb{D}$，那么，$\mathbb{S}$ 就被分为了 $\mathbb{D}$ 和 $\mathbb{S}-\mathbb{D}$ 两部分，接着就对这两部分分别进行操作即可。形式化地讲，就是：
$$dp_{\mathbb{S}}=\min{(dp_{\mathbb{D}}+dp_{\mathbb{S}-\mathbb{D}})}(\mathbb{D} \subset \mathbb{S})$$

完结撒花！

## AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1<<18;
int n,m,edge[20],dp[maxn+5];
int main(){
	memset(dp,0x3f,sizeof dp);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		edge[x]|=1<<(y-1),edge[y]|=1<<(x-1);
	}
	for(int i=1;i<=n;i++){
		edge[i]|=1<<(i-1);
	}
	dp[0]=0;
	int N=(1<<n)-1;
	for(int i=1;i<=N;i++){
		bool flag=true;
		for(int j=1;j<=n;j++){
			if((i&(1<<(j-1)))&&(edge[j]&i)!=i){
				flag=false;
			}
		}
		if(flag){
			dp[i]=1;
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=i;j;j=i&(j-1)){
			dp[i]=min(dp[i],dp[j]+dp[i^j]);
		}
	}
	printf("%d",dp[N]);
	return 0;
}
```

---

## 作者：loser_seele (赞：3)

这题正解是状压，但题解里给出了另一个做法。

本题答案为补图的最小色数。

证明：如果原图中两点有边则可以染上相同颜色，否则一定说明这条边被移除了。否则显然两个点不能涂一样的颜色。

观察到上述问题转化到补图上就是图上任意一条边不能染上一样的颜色，于是变为图的最小色数问题。

暴力建出补图之后枚举颜色数，尝试对每个点用 dfs 进行模拟染色过程，如果不合法则增加颜色数即可。

时间复杂度不会算，但是因为点数很小所以能通过。目前是最优解。

当然最小色数问题能在 $ \mathcal{O}(2^n \times n) $ 的精确复杂度内解决，此处不详述。

代码：

```cpp
#include <iostream>
using namespace std;
int map[110][110]={0};
int v=4;
int color[110]={0};
int result=10000; 
int ok(int depth,int c)
{
	for(int i=1;i<=v;i++)
    {
		if(map[i][depth]==1||map[depth][i]==1)
        {
			if(color[i]==c)
				return 0;
			if(color[i]==0)
				continue;
		}
	}
	return 1;
} 
void  dfs(int depth,int color_s)
{
	if(color_s>=result)
		return ;
	if(depth>v)
    {    
		result=result<color_s?result:color_s;
		return ;
	}
	for(int i=1;i<=color_s;i++)
    {
		if(ok(depth,i)==1)
        {
			color[depth]=i;
			dfs(depth+1,color_s);
			color[depth]=0;
		}	
	}
	color[depth]=color_s+1;
	dfs(depth+1,color_s+1);
	color[depth]=0;	
}
int main()
{
	cin>>v;
    int m;
    cin>>m;
    while(m--)
    {
    int u,v;
    cin>>u>>v;
    map[u][v]=map[v][u]=1;
    }
    for(int i=1;i<=v;i++)
    for(int j=1;j<=v;j++)
    if(i!=j)
    map[i][j]^=1;
	dfs(1,0);
	cout<<result;
}
```


---

## 作者：Glacial_Shine (赞：2)

更好的[阅读体验](https://blog.csdn.net/weixin_46700592/article/details/129416557?spm=1001.2014.3001.5502)。

---

# 题意

给 $n$ 个点（$n\leq18$），$m$ 条边（$m\leq\frac{n\cdot(n-1)}{2}$）你一个简单无向图，删去一些边（可以是 $0$），使得图满足以下性质：

- 任意两点 $a$，$b$，如果 $a$，$b$ 连通，那么 $a$，$b$ 之间有边。

求满足条件最少的连通块数量。
# 思路

题目数据很小，状压走起！

首先我们设 $f_v$ 表示当顶点集合为 $v$ 时，最少的连通块数量。

然后我们先暴力枚举点集 $v$，判断这个点集 $v$ 是否为完全图。

此时我们想怎么转移。

我们可以发现当 $v'$ 为 $v$ 的子集时，$f_v=\min(f_{v'}+f_{v-v'})$。

所以此时我们就要枚举 $v'$。

我们先把 $v'=v$，然后我们接下来每次都把 $v'=(v'-1)\operatorname{and}v$，此时 $(v'-1)\operatorname{and}v$ 肯定是 $v$ 的子集，因为如果 $v'-1$ 中二进制下有一位为 $1$ 且 $v$ 的这一位为 $0$，那么在 $(v'-1)\operatorname{and} v$ 的时候这个 $1$ 就不见了，因为 $1\operatorname{and}0=0$。

接下来我们来算一下时间复杂度。

在枚举 $v'$ 的时候，因为 $v$ 和 $v'$ 的在二进制下每一位的关系只有三种情况，$1/0$，$1/1$，$0/0$，也就是说，把所有枚举的情况乘起来，就是 $3^n$，虽然 $3^n > 3 \times 10^8$，但是因为常数很小，所以还是可以过。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mp[25][25],f[2621445];
int main() {
    int u,v;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&u,&v),mp[u][v]=mp[v][u]=1;
    bool flag;
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=(1<<n)-1;i++) {
        flag=true;
        for(int j=1;j<n;j++)
            if((i>>(j-1))&1)
                for(int l=j+1;l<=n;l++)
                    if((i>>(l-1))&1&&(!mp[j][l])) {
                        flag=false;
                        break;
                    }
        if(flag)
            f[i]=1;
    }
    for(int i=1;i<=(1<<n)-1;i++)
        for(int j=i;j;j=(j-1)&i)
            f[i]=min(f[i],f[j]+f[i^j]);
    printf("%d",f[(1<<n)-1]);
    return 0;
}
```


---

## 作者：_Kenma_ (赞：0)

# AT_abc187_f 解题报告

## 前言

CSP 2024 前的最后一道 DP 题。

## 思路分析

看到数据范围想到状压。

设 $f_s$ 表示点集为 $s$ 的最少联通块数量。

然后可以枚举子集转移：

$$f_s=\min_{t}^{t\subseteq s} f_t+f_{s\oplus t}$$

考虑初始化。当 $s$ 点集构成一个完全图时，$f_s=1$，否则 $f_s=+\infty$。

做完了。

总体复杂度 $O(2^nn^2+3^n)$。

因为常数小，时限松，所以能跑过去。

## 代码实现
```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,vis[19][19];
vector<int> v;
bool check(){
	if(v.size()==1) return true;
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v.size();j++){
			if(i==j) continue;
			if(!vis[v[i]][v[j]]) return false;
		}
	}
	return true;
}
int f[1000005],g[1000005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		vis[x][y]=1;
		vis[y][x]=1;
	}
	for(int s=1;s<(1<<n);s++){
		v.clear();
		for(int i=1;i<=n;i++){
			if(s&(1<<(i-1))) v.push_back(i);
		}
		if(check()) g[s]=1;
	}
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int s=1;s<(1<<n);s++){
		if(g[s]){
			f[s]=1;
			continue;
		}
		for(int t=s;t;t=(t-1)&s){
			f[s]=min(f[s],f[s^t]+f[t]); 
		} 
	}
	cout<<f[(1<<n)-1];
	return 0;
}

```

## 后记

CSP rp++

---

## 作者：Meickol (赞：0)

看一眼数据范围，发现 $1 \le N \le 18$，考虑状压 DP。

设 $f_j$ 表示状态为 $j$ 时，最少分成的连通块的数量。



首先预处理 $f$ 数组，根据题意给出的连边关系，将原本就能构成一个连通块的状态的 $f$ 值赋值为 $1$。

处理代码如下：

```c++
map<int,int> mp[N];
cin>>n>>m;
rep(i,1,m){
    int a,b;
    cin>>a>>b;
    mp[a][b]++,mp[b][a]++;
}
int maxj=(1<<n)-1;
memset(f,INF,sizeof f);
f[0]=0;
rep(j,0,maxj){
    bool flag=1;
    rep(i,1,n){
        if(!(j&(1<<(i-1)))) continue;
        rep(k,1,n){
            if(i==k) continue;
            if(!(j&(1<<(k-1)))) continue;
            if(!mp[i][k]){
                flag=false;
                break;
            }
        }
    }
    if(flag) f[j]=1;
}
```



接下来，假如当前状态为 $j$，显然可以通过枚举其子状态 $jj$，状态 $j$ 可由其子状态 $jj$ 和 $j-jj$ 凑出，即 `f[j]=min(f[j],f[jj]+f[j-jj]);`

于是 DP 转移可写成

```c++
for(int j=0;j<=maxj;j++){
    for(int jj=0;jj<j;jj++){
        if(j&jj) f[j]=min(f[j],f[jj]+f[j-jj]);
    }
}
```



然而这样写完交上去会 TLE，因为上面这份代码时间复杂度为 $\mathcal{O}(2^{2n})$。

思考一下会发现，这样写其实会 $jj$ 会枚举到很多无效状态，于是可以改写成下面这份代码，优化子状态的枚举。时间复杂度为 $\mathcal{O}(3^n)$。

```c++
for(int j=0;j<=maxj;j++){
    for(int jj=j;jj;jj=(jj-1)&j){
        f[j]=min(f[j],f[jj]+f[j-jj]);
    }
}
```



**最终代码**

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=19,INF=0x3f3f3f3f;
int n,m;
int f[1<<N];
void solve(){
	map<int,int> mp[N];
	cin>>n>>m;
	rep(i,1,m){
		int a,b;
		cin>>a>>b;
		mp[a][b]++,mp[b][a]++;
	}
	int maxj=(1<<n)-1;
	memset(f,INF,sizeof f);
	f[0]=0;
	rep(j,0,maxj){
		bool flag=1;
		rep(i,1,n){
			if(!(j&(1<<(i-1)))) continue;
			rep(k,1,n){
				if(i==k) continue;
				if(!(j&(1<<(k-1)))) continue;
				if(!mp[i][k]){
					flag=false;
					break;
				}
			}
		}
		if(flag) f[j]=1;
	}
	rep(j,0,maxj){
		for(int jj=j;jj;jj=(jj-1)&j){
			f[j]=min(f[j],f[jj]+f[j-jj]);
		}
	}
	cout<<f[maxj];
}
```

---

## 作者：迟暮天复明 (赞：0)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/15430402.html)

状压 DP。

看到这个 $n\leq18$ ，立刻想到状压 DP。

考虑转移方程，一个状态可以由两个子状态转移而来，所以 $f_i=f_{i-j}+f_j$。

如果 $i-j$ 和 $j$ 这两个状态可以合并，那么等于说是 $i$ 这个状态本身是个完全图。那么我们判断一下这个 $i$ 是不是完全图，是的话 $f_i=1$。

再去看如何判断完全图。显然，对于 $i$ 中出现的每个点，都与 $i$ 中所有点有连边。那我们存图的时候，对于每个点用状态压缩的方式存储他和哪些点有边相连。判断的时候只需要判断 $e_u \operatorname{and} i=i$ 是否成立即可。时间复杂度 $O(n\times 2^n)$。

[代码](https://paste.ubuntu.com/p/7gk5JHs36F/)

---

## 作者：Unnamed114514 (赞：0)

条件转化成完全图。

$n\le 18$，所以可以考虑状压 dp。

于是可以先处理出每个状态是否可行，时间复杂度 $O(2^n)$。

记忆化搜索，$dfs(state)$ 表示的是当前加入的点的状态是 $state$ 的答案。

容易想到枚举补集，时间复杂度 $O(3^n)$。

---

