# Saving Snuuk

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018-summer-qual/tasks/soundhound2018_summer_qual_d

kenkoooo さんはすぬけ国での旅行の計画を立てています。 すぬけ国には $ n $ 個の都市があり、$ m $ 本の電車が走っています。 都市には $ 1 $ から $ n $ の番号がつけられていて、 $ i $ 番目の電車は都市 $ u_i $ と $ v_i $ の間を両方向に走っています。 どの都市からどの都市へも電車を乗り継ぐことで到達できます。

すぬけ国で使える通貨には、円とスヌークの $ 2 $ 種類があります。 どの電車の運賃も円とスヌークのどちらの通貨でも支払え、 $ i $ 番目の電車の運賃は、 円で支払う場合 $ a_i $ 円、 スヌークで払う場合 $ b_i $ スヌークです。

両替所のある都市に行くと、$ 1 $ 円を $ 1 $ スヌークに両替することができます。 ただし、 両替をするときには持っている円すべてをスヌークに両替しなければなりません。 つまり、kenkoooo さんの所持金が $ X $ 円であるときに両替をすると、 kenkoooo さんの所持金は $ X $ スヌークになります。 現在、両替所は $ n $ 個の都市すべてに存在しますが、 $ i $ 番目の都市の両替所は今年から $ i $ 年後に閉鎖されてしまい、 $ i $ 年後とそれ以降は使うことができません。

kenkoooo さんは $ 10^{15} $ 円を持って都市 $ s $ から旅に出て、 都市 $ t $ へ向かおうと思っています。 移動中、kenkoooo さんは両替所のある都市のいずれかで円をスヌークに両替しようと考えています。 ただし、都市 $ s $ または都市 $ t $ の両替所で両替をしてもよいものとします。

kenkoooo さんは移動の経路と両替をする都市を適切に選ぶことで、できるだけ多くのスヌークを持っている状態で 都市 $ t $ に辿り着きたいと考えています。 $ i=0,...,n-1 $ のそれぞれについて、$ i $ 年後に都市 $ s $ から都市 $ t $ へ移動した際に kenkoooo さんが所持しているスヌークの最大額を求めてください。 ただし、旅行中に年をまたぐことは無いとします。

## 说明/提示

### 制約

- $ 2\ \leq\ n\ \leq\ 10^5 $
- $ 1\ \leq\ m\ \leq\ 10^5 $
- $ 1\ \leq\ s,t\ \leq\ n $
- $ s\ \neq\ t $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ n $
- $ 1\ \leq\ a_i,b_i\ \leq\ 10^9 $
- $ i\neq\ j $ のとき $ u_i\ \neq\ u_j $ または $ v_i\ \neq\ v_j $
- どの都市からどの都市へも電車を乗り継ぐことで到達できる
- 入力はすべて整数

### Sample Explanation 1

$ 0 $ 年後には、都市 $ 1 $ で両替をするのが最適です。 $ 1 $ 年後には、都市 $ 2 $ で両替をするのが最適です。 両替所が閉鎖されても都市 $ 1 $ を訪れることは可能であることに注意してください。 また、都市 $ 2 $ で両替をするときに $ 1 $ 円だけ残して残りをスヌークに両替をすると $ 999999999999998 $ スヌークを持った状態で都市 $ 3 $ にたどり着けますが、 このような両替は許されていないことにも注意してください。 $ 2 $ 年後には、都市 $ 3 $ で両替をするのが最適です。 $ 3 $ 年後には、都市 $ 4 $ で両替をするのが最適です。 同じ電車を複数回使っても良いことに注意してください。

## 样例 #1

### 输入

```
4 3 2 3
1 4 1 100
1 2 1 10
1 3 20 1```

### 输出

```
999999999999998
999999999999989
999999999999979
999999999999897```

## 样例 #2

### 输入

```
8 12 3 8
2 8 685087149 857180777
6 7 298270585 209942236
2 4 346080035 234079976
2 5 131857300 22507157
4 8 30723332 173476334
2 6 480845267 448565596
1 4 181424400 548830121
4 5 57429995 195056405
7 8 160277628 479932440
1 6 475692952 203530153
3 5 336869679 160714712
2 7 389775999 199123879```

### 输出

```
999999574976994
999999574976994
999999574976994
999999574976994
999999574976994
999999574976994
999999574976994
999999574976994```

# 题解

## 作者：FFTotoro (赞：2)

注意到我们可以枚举 Kenkoooo 兑换钱币的那个中转点。

记 $x_i$ 为从起点 $s$ 到中转站 $i$ 使用日元的最少总花费，$y_i$ 为从中转站 $i$ 到终点 $t$ 使用 snuuk 的最少总花费。因为边是双向的，所以从 $s$ 和 $t$ 为源点分别跑最短路（推荐使用 Dijkstra 算法）可以便捷地求出所有的 $x_i$ 和 $y_i$。

然后枚举那个中转点，记第 $i$ 次旅行（即在 $i-1$ 年后的那次旅行）的最小花费为 $f_i$，根据兑换局的关闭时间，有 $f_i=\min\{f_{i+1},x_i+y_i\}$，答案即为 $10^{15}-f_i$。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tpi;
vector<vector<tpi> > g;
void f(int s,bool o,vector<int> &d){
  vector<bool> b(d.size());
  priority_queue<pii,vector<pii>,greater<pii> > q;
  q.emplace(d[s]=0,s);
  while(!q.empty()){
    int u=q.top().second; q.pop();
    if(b[u])continue; b[u]=true;
    for(auto [i,a,b]:g[u])
      if(d[i]>d[u]+(o?a:b))
        q.emplace(d[i]=d[u]+(o?a:b),i);
  }
} // 跑最短路
main(){
  ios::sync_with_stdio(false);
  int n,m,s,t; cin>>n>>m>>s>>t; g.resize(n);
  for(int i=1;i<=m;i++){
    int a,b,c,d; cin>>a>>b>>c>>d;
    g[--a].emplace_back(--b,c,d);
    g[b].emplace_back(a,c,d);
  } // 建图
  vector<int> d1(n,1e15),d2(n,1e15),c(n+1);
  f(s-1,1,d1),f(t-1,0,d2),c[n]=1e15;
  for(int i=n-1;~i;i--)
    c[i]=min(c[i+1],d1[i]+d2[i]); // 枚举
  for(int i=0;i<n;i++)
    cout<<(int)1e15-c[i]<<endl;
  return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

注意到只有一个日元与 snuuk 的转换站，可以考虑枚举它。我们发现，记转换站为 $k$，$s$ 到 $t$ 的最短路径可以表示为 $s$ 到 $k$ 的**使用日元**的最短路加上 $k$ 到 $t$ 的**使用 snuuk** 的最短路。不难想到从 $s$ 开始处理出它到所有点的使用日元的最短路，从 $t$ 开始处理出它到所有点的使用 snuuk 的最短路。记 $dist_i$ 为 $s$ 到 $t$ 的以 $i$ 为转换站的最短路，记 $ans_i$ 为第 $i$ 年旅行的最少花费，于是 $ans_i=\min(ans_{i+1},dist_i)$，也就是我要么用之后那年的转换站（下标大所以还可以转换），要么用 $i$ 这次的转换站。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=100010;
struct node
{
	int u,dist;
	bool operator >(const node& x)const
	{
		return x.dist<dist;
	}
};
struct edge
{
	int v,w1,w2;
};
vector<edge> G[N];
int dist[N],dist2[N],vis[N],vis2[N],ans[N];
priority_queue<node,vector<node>,greater<node>> q;
void dijkstra(int s)
{
	dist[s]=0;
	q.push({s,0});
	while(!q.empty())
	{
		int u=q.top().u;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto e:G[u])
		{
			int v=e.v,w=e.w1;
			if(dist[v]>dist[u]+w)
			{
				dist[v]=dist[u]+w;
				q.push({v,dist[v]});
			} 
		}
	}
}
void dijkstra2(int s)
{
	dist2[s]=0;
	q.push({s,0});
	while(!q.empty())
	{
		int u=q.top().u;
		q.pop();
		if(vis2[u]) continue;
		vis2[u]=1;
		for(auto e:G[u])
		{
			int v=e.v,w=e.w2;
			if(dist2[v]>dist2[u]+w)
			{
				dist2[v]=dist2[u]+w;
				q.push({v,dist2[v]});
			} 
		}
	}
}
signed main()
{
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++)
	{
		int u,v,w1,w2;
		cin>>u>>v>>w1>>w2;
		G[u].push_back({v,w1,w2});
		G[v].push_back({u,w1,w2});
	}
	for(int i=1;i<=n+1;i++) dist[i]=dist2[i]=ans[i]=1e15;
	dijkstra(s);
	dijkstra2(t);
	for(int i=n;i;i--)
	{
		ans[i]=min(ans[i+1],dist[i]+dist2[i]);
	}
	for(int i=1;i<=n;i++) cout<<(int)1e15-ans[i]<<endl;
	return 0;
}
```

---

