# Pentagon

## 题目描述

According to the last order issued by the president of Berland every city of the country must have its own Ministry Defense building (their own Pentagon). A megapolis Berbourg was not an exception. This city has $ n $ junctions, some pairs of which are connected by two-way roads. Overall there are $ m $ roads in the city, no more than one between each pair of junctions.

At the moment choosing a location place for Pentagon in Berbourg is being discussed. It has been decided that Pentagon should cover the territory of five different junctions which are joined into a cycle by roads. In the order to build Pentagon a special wall will be built along the roads (with high-tension razor, high-voltage wire and other attributes). Thus, the number of possible ways of building Pentagon in the city is equal to the number of different cycles at lengths of 5, composed of junctions and roads.

Your task is to prints the number of ways of building Pentagon in Berbourg. Only well-optimized solutions will be accepted. Please, test your code on the maximal testcase.

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 4
4 5
5 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
```

### 输出

```
12
```

# 题解

## 作者：黑影洞人 (赞：7)

这是一道很有趣的图论题。

题意简述：

给定一个无向图，求五元环的个数，相同元素的环只算一个。

假如使用邻接表？

枚举五个点？深度过大，最劣的复杂度为 $O(m^5)=O(n^{10})$ 无法承受。

改成邻接矩阵呢？复杂度为 $O(n^5)$ 也无法承受。

考虑 DP，我们设 $a_{i,j,k}$ 为 $i$ 到 $j$ 之间距离为 $k$ 的路径的个数。

显然，DP 方程为：

$$a_{i,j,k}=\sum_{t=1}^n a_{i,t,1}\times a_{t,j,k-1}$$

根据乘法原理，枚举中间点，路径的个数就是两边的乘积。

因为我们只用求五元环，只用枚举 $2$ 到 $3$ 的情况再拼接。 

这部分的代码长这样。

```cpp
for(int t=2;t<=3;t++){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j][t]+=a[i][k][1]*a[k][j][t-1];
			}
		}
	}
}
```

最后我们统计答案：

一条去路长度为 $2$ 的方案数，回路长度为 $3$ 的方案数。

同样根据乘法原理得到答案。

```cpp
for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
		ans+=a[i][j][2]*a[i][j][3];
	}
}
```
因为是双向边，并且是五元环，每个点来回都会被算一次，所以答案要除以 $10$。

结束了？

没有，因为是无向图，所以很有可能出现一个三元环加上一条无向边连着。

如何解决？

我们只需要枚举任意三元环，然后求出三个点的度，他们之间形成的假五元环的个数，就是他们度数和减去 $3$。

因为每个点和另一个点连接，度数都会增加。于是一个三元环内部会形成三个假五元环。外部再向三元环连接，每连接一个就会将答案增加 $1$，被连接个数即为度数。

```cpp
#include<cstdio>
#include<algorithm>
#define N 1145
using namespace std;
int n,m,a[N][N][4],in[N];
long long ans;
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int aa,b;
		scanf("%d%d",&aa,&b);
		a[aa][b][1]++;a[b][aa][1]++;
		in[aa]++,in[b]++;
	}
	for(int t=2;t<=3;t++){
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					a[i][j][t]+=a[i][k][1]*a[k][j][t-1];
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans+=a[i][j][2]*a[i][j][3];
		}
	}
	ans/=10;
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(!a[i][j][1])continue;
			for(int k=1;k<j;k++){
				if(!a[j][k][1])continue;
				if(!a[i][k][1])continue;	
				ans-=in[i]+in[j]+in[k]-3;
			}		
		}
	}
	printf("%lld",ans);
	return 0;
}
```




---

## 作者：黎明行者 (赞：2)

【分析】

CF官方题解是俄语的，笔者用百度翻译看了一下，大概意思好像是枚举三个点，剩下的交给预处理的东西来解决。然而百度翻译俄语实在太毒瘤了，翻译了也看不太懂，所以来看看我的题解吧。

这是个有点烦人的计数问题，意思是给你一个无向图（无重边，无自环），求五元环的数量。

我的做法是枚举一个顶点 $x$，和边 $e$，设 $e$ 的两端点分别是 $a$ 和 $b$。每次把答案加上 $x$ 到 $a$ 长度为 $2$ 且不经过 $b$ 的路径数乘以 $x$ 到 $b$ 长度为 $2$ 且不经过 $a$ 的路径数。

乍一看这样统计出来的数量除以 $5$ 就是答案了，然而要考虑 $x$ 与另一个点 $y$ 相连，$y$ 又同时连着 $a$ 和 $b$ 的情况。${x,y,a,b,y}$ 不是一个合法的五元环（但会被上述算法统计到），而是一个三元环 ${y,a,b}$ 加一条从 $x$ 到 $y$ 的边 。

所以答案要减掉“三元环加一条边”这种结构的数量。我们还是枚举点 $x$ 和边 $e$（$e$ 连接着 $a$ 和 $b$），如果 $x$ 同时与 $a$ 和 $b$ 相连，则答案减掉 $x$ 的度数减 $2$。最终答案要除以 $5$。

【代码注意事项】

先计算每一对点之间长度为 $2$ 的路径数。这一过程不要用邻接链表，应该用邻接矩阵，否则会超时。

【代码】

```cpp
#include <bits/stdc++.h>

typedef long long ll;
const int N=702;
int n,m;

struct Graph
{
	int cnt,deg[N];
	bool am[N][N];
	ll p2c[N][N];
	Graph()
	{memset(p2c,0,sizeof(p2c)); memset(am,0,sizeof(am)); memset(deg,0,sizeof(deg));}
	void addEdge(int x,int y)
	{
		am[x][y]=true;
		deg[x]++;
	}
	void getP2c(int x)
	{
		for (register int y=1;y<=n;y++) if (am[x][y])
			for (register int z=1;z<=n;z++)  if (am[y][z])
				p2c[x][z]++;
	}
	ll solve1()
	{
		ll res=0;
		for (int i=1;i<=n;i++) getP2c(i);
		for (int a=1;a<n;a++)
			for (int b=a+1;b<=n;b++) if (am[a][b])
				for (int j=1;j<=n;j++)
				{
					if (a==j || b==j) continue;
					res+=(p2c[j][a]-am[j][b])*(p2c[j][b]-am[j][a]);
				}
		return res;
	}
	ll solve2()
	{
		ll res=0;
		for (int a=1;a<n;a++)
			for (int b=a+1;b<=n;b++) if (am[a][b])
				for (int j=1;j<=n;j++)
				{
					if (a==j || b==j) continue;
					res+=(am[a][j]&&am[b][j])?deg[j]-2:0;
				}
		return res;
	}
} gra;
int read()
{
	char ch=getchar(); int res=0;
	while (ch<'0'||'9'<ch) ch=getchar();
	while ('0'<=ch&&ch<='9') res*=10,res+=ch-'0',ch=getchar();
	return res;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int a=read(),b=read();
		gra.addEdge(a,b); gra.addEdge(b,a);
	}
	ll ans=(gra.solve1()-gra.solve2())/5;
	std::cout<<ans<<std::endl;
	return 0;
}
```



---

## 作者：Priestess_SLG (赞：1)

考虑类似于 Floyd 的 dp 设计：设 $f_{o,i,j}$ 表示从 $i$ 到 $j$ 走了 $o$ 条边的不同方案数，那么显然有初始条件：对于每一条边 $u\leftrightarrow v$，都有 $f_{1,u,v}=f_{1,v,u}=1$。转移的话枚举中转点 $k$ 然后用 $f_{o,i,k}\times f_{1,k,j}$ 来转移 $f_{o+1,i,j}$ 即可。因为是五元环而且有正反两种绕法，所以每一个环都被计算了 $10$ 次，答案需要除以 $10$。

但是这样是错的，可以出现三元环套二元环的情况。此时直接暴力枚举一个三元环 $(i,j,k)$，每一个点 $i$ 都有 $\deg(i)$ 种往外伸展出二元环的方案数，因此该情况需要容斥减去 $\deg(i)+\deg(j)+\deg(k)-3$，其中 $\deg(i)$ 表示无向图中 $i$ 点的度数。时间复杂度为 $O(\omega n^3)$，其中 $\omega$ 是要找的环的长度，本题中取 $5$，可以通过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 710;
int f[6][N][N], deg[N];
inline void add(int &x, int v) {
    x += v;
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        ++deg[x], ++deg[y];
        f[1][x][y] = f[1][y][x] = 1;
    }
    for (int _ = 1; _ < 5; ++_)
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    add(f[_+1][i][j], f[_][i][k]*f[1][k][j]);
    int s = 0;
    for (int i = 1; i <= n; ++i) add(s, f[5][i][i]);
    s /= 10;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (f[1][i][j])
                for (int k = j + 1; k <= n; ++k)
                    if (f[1][i][k] && f[1][j][k])
                        s -= deg[i] + deg[j] + deg[k] - 3;
    // for (int i = 1; i <= n; ++i) add(s, -f[2][i][i]*f[3][i][i]/12);
    cout << s << '\n';
    return 0;
}
```

---

## 作者：SFlyer (赞：0)

考虑枚举三个点：环上第一个第二个第四个，那么第三个和二，四都有边，第五个和四，一都有边。但是会出现一个三元环伸出一个点的情况。这个我们发现我们对于中心的（度数为 $3$）的点计算的时候减掉即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 707;

int n,m,e[N][N],cnt[N][N],deg[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m;
	for (int i=1; i<=m; i++){
		int a,b;
		cin>>a>>b;
		e[a][b]=e[b][a]=1;
		deg[a]++,deg[b]++;
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			for (int k=1; k<=n; k++){
				if (e[i][k] && e[k][j]) cnt[i][j]++;
			}
		}
	}
	ll ans=0;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			if (i==j) continue;
			for (int k=1; k<=n; k++){
				if (i==k || j==k) continue;
				if (!e[j][k]) continue;
				ans+=(cnt[i][j]-e[i][k])*(cnt[i][k]-e[i][j]);
				if (e[i][j] && e[i][k]) ans-=deg[i]-2;
			}
		}
	}
	cout<<ans/10<<"\n";
	return 0;
}
```

---

