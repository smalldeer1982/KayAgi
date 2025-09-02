# [ABC143E] Travel by Car

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc143/tasks/abc143_e

$ 1 $ から $ N $ までの番号がついた $ N $ 個の町と $ M $ 本の道があります。$ i $ 本目の道は町 $ A_i $ と町 $ B_i $ を双方向に結び、その長さは $ C_i $ です。

高橋君はこれらの町の間を、道を車で通行することで移動します。車の燃料タンクの容量は $ L $ リットルであり、距離 $ 1 $ を移動する度に燃料を $ 1 $ リットル消費します。移動中に町を訪れた場合、燃料をタンクが一杯になるまで補給することが出来ます (補給しないという選択も可能です)。道の途中で燃料が尽きるような移動は出来ません。

以下の $ Q $ 個のクエリに答えてください。

- はじめ、車の燃料タンクは一杯です。町 $ s_i $ から町 $ t_i $ へ移動するとき、最小で何回途中で燃料を補給する必要があるかを答えてください。町 $ t_i $ まで移動出来ない場合は $ −1 $ を出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ <\ =\ N\ <\ =\ 300 $
- $ 0\ <\ =\ M\ <\ =\ \frac{N(N-1)}{2} $
- $ 1\ \leq\ L\ \leq\ 10^9 $
- $ 1\ <\ =\ A_i,\ B_i\ <\ =\ N $
- $ A_i\ \neq\ B_i $
- $ \left(A_i,\ B_i\right)\ \neq\ \left(A_j,\ B_j\right) $ ( $ i\ \neq\ j $ のとき)
- $ \left(A_i,\ B_i\right)\ \neq\ \left(B_j,\ A_j\right) $ ( $ i\ \neq\ j $ のとき)
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- $ 1\ <\ =\ Q\ <\ =\ N\left(N-1\right) $
- $ 1\ <\ =\ s_i,\ t_i\ <\ =\ N $
- $ s_i\ \neq\ t_i $
- $ \left(s_i,\ t_i\right)\ \neq\ \left(s_j,\ t_j\right) $ ( $ i\ \neq\ j $ のとき)

### Sample Explanation 1

町 $ 3 $ から町 $ 2 $ へ移動するときは、 $ 2 $ 本目の道を使えば、途中で燃料を補給することなく町 $ 2 $ へ到着することが出来ます。 町 $ 1 $ から町 $ 3 $ へ移動するときは、まず $ 1 $ 本目の道を使って町 $ 2 $ へ移動し、燃料をタンク一杯まで補給し、 $ 2 $ 本目の道を使うことにより、町 $ 3 $ へ到着することが出来ます。

### Sample Explanation 2

道が無いこともあります。

## 样例 #1

### 输入

```
3 2 5
1 2 3
2 3 3
2
3 2
1 3```

### 输出

```
0
1```

## 样例 #2

### 输入

```
4 0 1
1
2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 4 4
1 2 2
2 3 2
3 4 3
4 5 2
20
2 1
3 1
4 1
5 1
1 2
3 2
4 2
5 2
1 3
2 3
4 3
5 3
1 4
2 4
3 4
5 4
1 5
2 5
3 5
4 5```

### 输出

```
0
0
1
2
0
0
1
2
0
0
0
1
1
1
0
0
2
2
1
0```

# 题解

## 作者：Strelitzia_ (赞：3)

## 题目大意

$n$ 个城市，$m$ 条双向边，正边权。一辆车油箱容量为 $t$ 升，每行驶一个单位耗 $1$ 升油。在每一个城市可以选择加油或不加，若在某条边上没油了则不能到达该边连接的城市。

给出 $q$ 组询问，每组一个 $u_i,v_i$，问从 $u_i$ 到 $v_i$ 最少加多少次油。

每组询问互相独立。出发是油箱是满的。

------------
## 思路

注意到 $n\le 300$，我们使用弗洛伊德先求一边全源最短路。

然后我们枚举每一对点 $(u_i,v_i)$，若 $u_i$ 与 $v_i$ 间的距离小于等于 $t$，那么只要在 $u_i$ 加一次油就可以直接到 $v_i$ 了，距离设为 $1$；若大于 $t$，那么在 $u_i$ 加满油也不能直接到 $v_i$，距离设为无穷大。

特别的，若 $u_i=v_i$，距离设为 $0$。

然后再跑一边弗洛伊德，算出来最短路即可。因为在起点处已经加满了油，所以得到的次数要再减一次。

代码如下：

```cpp
int dis[301][301], n, m, q, t;
signed main() {
	memset(dis, 0x3f, sizeof(dis));
	n = read(), m = read(), t = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		dis[u][v] = dis[v][u] = read();
	}
	for (int i = 1; i <= n; i++) dis[i][i] = 0;
	for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
			if (i == j) dis[i][j] = 0;
			else if (dis[i][j] <= t) dis[i][j] = 1;
			else dis[i][j] = INF;
		}
	for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	q = read();
	for (int i = 1; i <= q; i++) {
		int u = read(), v = read();
		printf(dis[u][v] == INF ? "-1\n" : "%lld\n", dis[u][v] - 1);
	}
	return Strelitzia_;
}
```

---

## 作者：SilverLi (赞：3)

[Travel by Car 的 传送门](https://www.luogu.com.cn/problem/AT_abc143_e)

[更费时间的阅读体验](https://www.cnblogs.com/Silver-Wolf/p/ABC143E.html)

> $n\le300$

可~~凭感觉~~进行一遍 Floyd。

然后选两个点 $i,j$，如果 $i,j$ 间的距离小于等于 $l$，则将 $i,j$ 连一条代价为 $1$ 的边（假设 $i,j$ 要用一桶油）。

最后再来一遍 Floyd 即可。

因为**第一次是加满油的**，所以答案要 $-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=305;
int n,m,l,q,s,t,u,v,w;
int d[N][N],dis[N][N];
signed main() {
	cin>>n>>m>>l;
	for(int i=0;i<=n;++i) {
		fill(d[i],d[i]+N,1e16);
		fill(dis[i],dis[i]+N,1e16);
		d[i][i]=dis[i][i]=0;
	}
	for(int i=1;i<=m;++i) {
		cin>>u>>v>>w;
		d[u][v]=d[v][u]=w;
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(d[i][k]!=1e16&&d[k][j]!=1e16)
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(d[i][j]<=l)	dis[i][j]=dis[j][i]=1;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(dis[i][k]!=1e16&&dis[k][j]!=1e16)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	cin>>q;
	while(q--) {
		cin>>u>>v;
		cout<<(dis[u][v]!=1e16?dis[u][v]-1:-1)<<endl;
	}
	return 0;
}
```

---

## 作者：清烛 (赞：2)

## Description

$n$ 个小镇，$m$ 条双向道路。第 $i$ 条道路从 $a_i$ 通向 $b_i$，长度为 $c_i$。车的油箱容量为 $L$ 升，当行驶到一个镇上时可以选择加满油或者什么都不做。行驶单位长度的距离消耗一升油。

现在回答 $Q$ 个问题：

- 油箱现在为满，从 $s_i$ 出发，行驶到 $t_i$，最少需要加油多少次，无法到达则输出 $-1$。

$2\le n\le 300$，$0\le m\le n(n  - 1)/2$，无重边，无自环。$1\le c_i, L\le 10^9$。

## Solution
这个题的建图还是比较神仙的，但是也不是完全想不出来。这里不从结论出发来推一遍。

我们注意到，加一次油之后，最多可以行驶 $L$ 的距离，这与中间具体走了多少个点是没有关系的。

而且 $n\le 300$，所以我们不妨先用 Floyd 求出两两之间的最短路。对于一对点对 $(u,v)$，发现只有当 $d_{u, v}\le L$ 时，其能用在 $u$ 点处（$v$ 点同理）一次加油来搞定。

那么我们既然要求最少加多少次油，又知道了 $(u, v)$ 能否用一次加油搞定，那么就不妨建新图，$d_{u,v}\le L$ 时建新边 $(u, v)$，边权为 $1$。然后在新图上跑最短路。跑出来的结果减 $1$ 即为答案，因为初始油箱为满，要扣除一次“加油”。

那么综上，跑两次 Floyd 就搞定了。时间复杂度为 $O(n^3 +  n^2 + Q)$。

## Implementation
千万别忘记 `long long`。

```cpp
using ll = long long;
const int maxn = 305;
int n, m;
ll f[maxn][maxn], G[maxn][maxn], L;

int main() {
    read(n, m, L);
    memset(f, 0x3f, sizeof f), memset(G, 0x3f, sizeof G);
    FOR(i, 1, m) {
        int a, b, c; read(a, b, c);
        G[a][b] = G[b][a] = c;
    }
    FOR(k, 1, n) FOR(i, 1, n) FOR(j, 1, n) chkmin(G[i][j], G[i][k] + G[k][j]);
    FOR(i, 1, n) FOR(j, 1, n) {
        if (i == j) continue;
        if (G[i][j] <= L) f[i][j] = 1;
    }
    FOR(k, 1, n) FOR(i, 1, n) FOR(j, 1, n) chkmin(f[i][j], f[i][k] + f[k][j]);
    int q; read(q);
    while (q--) {
        int s, t; read(s, t);
        print(f[s][t] >= 0x3f3f3f3f3f3f3f3f ? -1 : f[s][t] - 1);
    }
    return output(), 0;
}
```

---

## 作者：L_zaa_L (赞：2)

## 分析
根据数据（$1 \le n \le 300$），所以很容易想到```floyd```，那么可以先跑一遍，那么的出了每个点对其他地方的最短距离，而每次两个点之间的最短距离不超过 $L$ 时，就可以先让假设他们这两点要用一桶油（所以答案肯定不会超过正确答案），然后再跑一遍，记录最少用油。
然后最后的答案要减去第一次就加满的油。

## Code
```
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define modj(x) ((x)-=((x)>=MOD)?MOD:0)
#define qmin(x,y) ((x)=min((x),(y)))
#define qmax(x,y) ((x)=max((x),(y)))
using namespace std;
inline ll read(){
	ll t=0,f=0;char v=getchar();
	while(!isdigit(v))f|=(v=='-'),v=getchar();
	while(isdigit(v))t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
inline void write(ll x){
	if(x<0){x*=-1; putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
int a[1005][1005],n,m,k,q,mod,x,y,l,dis[1005][10005],ans[1005][1005],sy[1005][1005];
signed main() {
	n=read(),m=read(),l=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=1e16;
			ans[i][j]=1e16;
		}
		dis[i][i]=0;
		ans[i][i]=0;
	}//初始化记录长度的dis和记录油数的ans
	FOR(i,1,m){
		int u,v,w;
		u=read(),v=read(),w=read();
		dis[u][v]=w;
		dis[v][u]=w;
	}
	for(int t=1;t<=n;t++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(dis[i][t]+dis[t][j]<dis[i][j]){
					dis[i][j]=dis[i][t]+dis[t][j];
					dis[j][i]=dis[i][j];
				}
			}
		}
	}//先跑一遍floyd记录最短路
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(dis[i][j]<=l){
				ans[i][j]=1;
			}
		}
	}//将可以只用一桶油的存为1
	for(int t=1;t<=n;t++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(ans[i][t]+ans[t][j]<ans[i][j]){
					ans[i][j]=ans[i][t]+ans[t][j];
					ans[j][i]=ans[i][j];
				}
			}
		}
	}//再跑一遍记录油数
	int q=read();
	FOR(i,1,q){
		int s=read(),t=read();
		if(ans[s][t]!=1e16){
			cout<<ans[s][t]-1<<endl;
		}
		else cout<<-1<<endl;
	}
    return 0;
}

```

### 后记
总所周知，最短路就是两个点之间再插入一个点，使得最短路变小，所以用三重循环枚举三个顶点就可以了，
```
for(int t=1;t<=n;t++){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(dis[i][t]+dis[t][j]<dis[i][j]){
				dis[i][j]=dis[i][t]+dis[t][j];
			}
		}
	}
}
```
而为什么要最先枚举中转点，要是将中转点放在里面那么后面的 $dis_{t,j}$ 可能会更新，所以就得不到最小值。

---

## 作者：small_john (赞：1)

## 思路

好简单的绿题。

看见 $n$ 的范围这么小，所以先用 Floyd 求最短路（记为 $d1$）。

然后可以转化一下问题。可以发现，如果两点最短距离小于等于 $L$ 的时候，加一次油肯定可以过去，而大于 $L$ 时就不一定。

那么就建一个新图，$d2_{i,j}$ 表示 $i,j$ 两点在**初始没有油**的情况下需要加油的最少次数。初始时，对于每一个满足 $d1_{i,j}\le L$ 的 $i,j$，$d2_{i,j}=1$。

再跑一次 Floyd，对 $d2$ 进行一点处理后就可以直接输出：

1. 如果 $d2_{i,j}= \infty$，那么 $d2_{i,j}$ 赋值为 $-1$；
2. 否则，$d2_{i,j}$ 减一，因为初始时油其实是满的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e2+5,inf = 0x3f3f3f3f;
int n,m,q,l,d1[N][N],d2[N][N];
signed main()
{
	cin>>n>>m>>l;
	memset(d1,63,sizeof d1);//记得初始化成inf
	memset(d2,63,sizeof d2);
	for(int i = 1,x,y,z;i<=m;i++)
		cin>>x>>y>>z,d1[x][y] = d1[y][x] = z;
	for(int k = 1;k<=n;k++)
		for(int i = 1;i<=n;i++)
			for(int j = 1;j<=n;j++)
				if(d1[i][j]>d1[i][k]+d1[k][j])
					d1[i][j] = d1[i][k]+d1[j][k];
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=n;j++)
			if(d1[i][j]<=l)
				d2[i][j] = 1;
	for(int k = 1;k<=n;k++)
		for(int i = 1;i<=n;i++)
			for(int j = 1;j<=n;j++)
				if(d2[i][j]>d2[i][k]+d2[k][j])
					d2[i][j] = d2[i][k]+d2[j][k];
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=n;j++)
			if(d2[i][j]==inf)
				d2[i][j] = -1;
			else d2[i][j]--;
	cin>>q;
	while(q--)
	{
		int s,t;
		cin>>s>>t;
		cout<<d2[s][t]<<'\n';
	}
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc143_e)

# 思路

` 300 ` 的数据直接可以跑 Floyd，领接矩阵存边，跑完之后判断当前位置的最短路是否需要加油，用另一个数组存从出发点到当前点的最少加油次数，也就是再跑一遍 Floyd。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 305;
int n,m,l,dis[N][N],ans[N][N];
int q,s,t;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m >> l;
	
	memset(dis,N,sizeof(dis));
	memset(ans,N,sizeof(ans));
	//初始化为较大值
	
	for(int i=1;i<=n;i++)
	{
		dis[i][i] = ans[i][i] = 0;//对角线数据
	}
		
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin >> u >> v >> w;
		dis[u][v] = dis[v][u] = w;//领接矩阵跑Floyd
	}
	
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);//Floyd
			}
		}
	}
				
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) 
		{
			if(dis[i][j] <= l)
			{
				ans[i][j] = 1;//判断油量剩余
			}
		}
	}
							
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				ans[i][j] = min(ans[i][j],ans[i][k]+ans[k][j]);//加油次数
			}
		}
	}
			
	cin >> q;
	
	while(q--)
	{
		cin >> s >> t;
		if(ans[s][t] < N)
		{
			cout << ans[s][t]-1 << endl;//记得减一
		}
		else
		{
			cout << "-1" << endl;
		}
	}
	return 0;
}
```


---

## 作者：zhangjiting (赞：1)

## 题意

$n$ 个小镇，$m$ 条双向道路。第 $i$ 条道路从 $a_i$ 通向 $b_i$，长度为 $c_i$。车的油箱容量为 $L$，当行驶到一个镇上时可以选择加满油或者什么都不做。行驶单位长度的距离消耗一单位的油。

现在回答 $Q$ 个问题：

- 油箱现在为满，从 $s_i$ 到 $t_i$，最少需要加油多少次，或者输出无解。

## 思路

一眼 Floyd。

首先，先对题目给出的图求一次全源最短路。我们知道 $Floyd_{i,j}$ 表示从点 $i$ 到点 $j$ 最短的距离。如果 $Floyd_{i,j} \le L$ 就说明可以在 $i$ 点加一次油就可以到达 $j$ 点。

因为题目要求的是最少加油次数，所以再建一张图。

$ans_{i,j}=1$ 表示可以用一桶油的代价从 $i$ 点到 $j$ 点。当 $Floyd_{i,j} \le L$ 时，$ans_{i,j}=1$，否则 $ans_{i,j}= \inf$。

最后输出的时候，如果 $ans_{x,y}= \inf$ 就输出 `-1`，否则，输出 $ans_{x,y}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[305][305],ans[305][305];
int main(){
	int n,m,l;
	cin>>n>>m>>l;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=ans[i][j]=INT_MAX;
		}
	}
	for(int i=1;i<=n;i++){
		f[i][i]=ans[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		f[u][v]=f[v][u]=w;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(f[i][j]>f[i][k]+f[k][j]){
					f[i][j]=f[i][k]+f[k][j];
					f[j][i]=f[i][j];
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(f[i][j]<=l) ans[i][j]=1;
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(ans[i][j]>ans[i][k]+ans[k][j]){
					ans[i][j]=ans[i][k]+ans[k][j];
					ans[j][i]=ans[i][j];
				}
			}
		}
	}
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		if(ans[x][y]!=INT_MAX){
			cout<<ans[x][y]-1<<endl;
		}
		else{
			cout<<-1<<endl;
		}
	}
	return 0;
}

```


---

## 作者：whx2009 (赞：1)

## 本题思路：
这道题目我们可以发现它的数据范围其实并不大，那么我们就可以想到用弗洛伊德算法了。

我们只需要先跑一遍弗洛伊德，把每个点间的最短路径先用一张二维的图表现出来，然后我们可以再开一张图，把所有小于等于 $L$ 的路径都标记为一，因为这些路径不论如何都可以以耗费一次油箱的代价跑完。接着我们就可以在为这张图跑一遍弗洛伊德，这样就可以直接得出两点之间的耗油了。

那么如何判定两点之间是否可以到达呢？我选择用并查集的方式，如果两个节点的祖先一样就可到，不一样就不行。当然，直接用第二张图的数据进行判定也是可以的。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[301][301],b[301][301],f[301];
int find(int x)
{
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
int main()
{
	int n,m,l;
	cin>>n>>m>>l;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=INT_MAX;
		}
	}
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		if(z<=l) a[x][y]=z,a[y][x]=z,f[find(x)]=find(y);
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			b[i][j]=INT_MAX;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]<=l)
			b[i][j]=1;
		}
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				b[i][j]=min(b[i][j],b[i][k]+b[k][j]);
			}
		}		
	}
	int q;
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int x,y;
		cin>>x>>y;
		if(find(x)!=find(y)) cout<<-1<<endl;
		else
		{
			cout<<b[x][y]-1<<endl;
		}
	}
	return 0;
}
```


---

