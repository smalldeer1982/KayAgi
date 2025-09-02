# [ABC260F] Find 4-cycle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc260/tasks/abc260_f

$ S+T $ 頂点 $ M $ 辺の単純無向グラフ $ G $ があります。頂点には $ 1 $ から $ S+T $ の番号が、辺には $ 1 $ から $ M $ の番号が割り振られています。辺 $ i $ は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。  
 また、頂点集合 $ V_1\ =\ \lbrace\ 1,\ 2,\dots,\ S\rbrace $ および $ V_2\ =\ \lbrace\ S+1,\ S+2,\ \dots,\ S+T\ \rbrace $ はともに独立集合です。

長さ $ 4 $ のサイクルを 4-cycle と呼びます。  
 $ G $ が 4-cycle を含む場合、4-cycle をどれか 1 つ選び、選んだサイクルに含まれる頂点を出力してください。頂点を出力する順番は自由です。  
 $ G $ が 4-cycle を含まない場合、 `-1` を出力してください。

 独立集合とは？ グラフ $ G $ の独立集合とは、$ G $ に含まれるいくつかの頂点からなる集合 $ V' $ であって、$ V' $ に含まれる任意の $ 2 $ つの頂点の間に辺がないものを言います。

## 说明/提示

### 制約

- $ 2\ \leq\ S\ \leq\ 3\ \times\ 10^5 $
- $ 2\ \leq\ T\ \leq\ 3000 $
- $ 4\ \leq\ M\ \leq\ \min(S\ \times\ T,3\ \times\ 10^5) $
- $ 1\ \leq\ u_i\ \leq\ S $
- $ S\ +\ 1\ \leq\ v_i\ \leq\ S\ +\ T $
- $ i\ \neq\ j $ ならば $ (u_i,\ v_i)\ \neq\ (u_j,\ v_j) $
- 入力される値はすべて整数

### Sample Explanation 1

頂点 $ 1 $ と $ 4 $ 、$ 4 $ と $ 2 $、$ 2 $ と $ 5 $、$ 5 $ と $ 1 $ の間に辺があるので 頂点 $ 1,2,4,5 $ は 4-cycle をなします。よって $ 1,\ 2,\ 4,\ 5 $ を出力すればよいです。 頂点を出力する順番は自由で、出力例のほかにも例えば `2 5 1 4` のような出力も正答となります。

### Sample Explanation 2

$ G $ が 4-cycle を含まない入力もあります。

## 样例 #1

### 输入

```
2 3 5
1 3
1 4
1 5
2 4
2 5```

### 输出

```
1 2 4 5```

## 样例 #2

### 输入

```
3 2 4
1 4
1 5
2 5
3 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 5 9
3 5
1 8
3 7
1 9
4 6
2 7
4 8
1 7
2 9```

### 输出

```
1 7 2 9```

# 题解

## 作者：迟暮天复明 (赞：8)

不知道为啥其他题解我都看不懂。可能是我太菜了。

设 $f_{i,j}=k$ 表示左部点 $k$ 与右部点 $i$ 和 $j$ 均有连边。对于每个左部点，$O(n^2)$ 枚举其出边形成的点对 $i,j$。如果 $f_{i,j}$ 不为 0，那么已经找到解。否则更新 $f_{i,j}$。

由于每对点 $i,j$ 只会被做到一次，所以时间复杂度 $O(T^2)$。

---

## 作者：Take_A_Single_6 (赞：2)

有趣的一道水题。  
题目要求二分图上的一个四元环，观察数据范围，发现 $S$ 很大，$T$ 较小，考虑设计一个 $O(T^2)$ 的做法。  
思考一下，二分图上的四元环一定是一个“八字形”的环，也就是 $s_1 \to t_1 \to s_2 \to t_2 \to s_1$。我们可以把 $s_x$ 看作一个“中转点”连接 $t_1$ 和 $t_2$，如果恰巧两个中转点连接了相同的 $t_1 t_2$，就可以构成一个四元环。  
所以我们直接枚举中转点 $s_i$，如果两个点已经有过中转点了，输出四元环终止程序。  
为什么这样做复杂度是对的？显然 $T$ 中最多只有 $\frac{T(T-1)}{2}$ 个点对，如果遍历了超过 $\frac{T(T-1)}{2}$ 个点对，必然会有重复，这时终止程序，复杂度显然正确。  
代码如下，注意细节：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 998244353
#define fir first
#define sec second
#define pr pair<int,int>
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX% 10 + '0');
}
int n1,n2,m;
vector<int>e[maxn];
int p[3005][3005];
signed main()
{
	int x,y;
	n1=read(),n2=read(),m=read();
	for(int i=1;i<=m;i++)x=read(),y=read(),e[x].push_back(y),e[y].push_back(x);
	for(int i=1;i<=n1;i++)
	{
		for(int j=0;j<e[i].size();j++)
		{
			for(int k=j+1;k<e[i].size();k++)
			{
				int vj=e[i][j]-n1,vk=e[i][k]-n1;//注意编号
				if(vj>vk)swap(vj,vk);//无向边
				if(!p[vj][vk])p[vj][vk]=i;
				else write(vj+n1),putchar(' '),write(vk+n1),putchar(' '),
				write(p[vj][vk]),putchar(' '),write(i),exit(0);//及时终止程序
			}
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：max666dong123 (赞：1)

## 题意

在一个形如下二分图 $G$ 中：![](https://cdn.luogu.com.cn/upload/image_hosting/nx67r9xw.png)

其中顶点集 $U$ 中的顶点数为 $S$，$V$ 的顶点数为 $T$，总边数为 $M$，第 $i$ 条边连接 $u_i$ 和 $v_i$，请找出上图中任意长
为 $4$ 的环。如果没有，输出``-1``。

## 思路

我们定义 $g_{a,b}=i$ 表示点 $a,b$ 中有公共顶点 $i$，我们可以发现 $g_{a,b}=i$ 的时候如果满足 $g_{a,b}=j$，那么 $i,j,a,b$ 一定可以组成一个长度为 $4$ 的环，输出就行了。

## 代码

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
const int N=3e3+10,M=3e5+10;
int n,m,k;
vector<int>s[M];
int g[N][N];
signed main(){
	IOS;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		int a,b;
		cin>>a>>b;
		s[a].push_back(b-n);
	}
	for(int i=1;i<=n;i++){
		for(int x=0;x<s[i].size();x++){
			for(int y=0;y<s[i].size();y++){
				if(x==y)continue;
				int a=s[i][x],b=s[i][y];
				if(g[a][b]!=0){
					cout<<g[a][b]<<" "<<a+n<<" "<<i<<" "<<b+n<<endl;
					return 0;
				}
				g[a][b]=i;
			}
		}
	}
	cout<<"-1"<<endl;
	return 0;
}
```

---

## 作者：Powerless233 (赞：1)

给出一种不同于题解的做法。

## Analysis

显然，可能存在的 $4$ 元环，其中一定有 $2$ 个点在 $V_{1}$ 中，另 $2$ 个点在 $V_{2}$ 中。

那么先来考虑朴素的暴力：先在 $V_{2}$ 中枚举点 $i$ ，再枚举点 $i$ 能连向的点 $j,k$ （在 $V_{1}$ 中），再枚举 $V_{2}$ 中的点 $s$ ，判断 $j,k$ 是否都与点 $s$ 连通。

注意，在第一次枚举 $i,j$ 的时候，由于边的数量有上界，所以复杂度是 $O(m)$ 而非 $O(st)$ ，因此，这个暴力的总复杂度是 $O(mst)$ 。

### Optimize 1
我们考虑优化这个暴力。在判断 $j,k$ 与点 $s$ 连通的时候，我们只需要做 二者共同 是 的判断，考虑使用 bitset 优化。在输入时预处理出 $V_{1}$ 中点与 $V_2$ 中的连通情况，在判断时，只需要将 $j,k$ 的 bitset 作 `&` 即可。

```cpp
bitset<M> b[N];

main(){
	for (int i = 1; i <= m; i++)
	{
		x = read(), y = read();
		e[x].push_back(y);
		e[y].push_back(x);
		b[x][y - s] = 1;//注意，这里要减去 s，否则空间将为 O(s^2)
	}
}
```
时间复杂度 $O(\frac{mst}{w})$，其中 $w = 32$，空间复杂度 $O(st)$。

（关于 bitset 的复杂度说法很多，这里不再赘述）

空间上，$3\times 10^5 \times 3 \times 10^3$ 看上去完全开不下，但 bitset 占用的空间是以 bit 作为单位的，因此，它占用的空间为 $\frac{9 \times 10^8}{8 \times 1024 \times 1024}=107$ MB，而这道题足足给了 1 个 G 的内存。

### Optimize 2
我们继续考虑优化。实际上，$j,k$ 没有必要分开枚举，我们考虑开一个临时 bitset $P$ 表示对于当前已经遍历过的 $j$ ，可以连通的点的集合。

![](https://cdn.luogu.com.cn/upload/image_hosting/suwf2e78.png)

在图中，随着 $j$ 的遍历，$P$ 依次为：

```
{1,2,3} -> {1,2,3}
{1,4} -> {1,2,3,4} （有重复，但是重复的是i）
{1,4} -> {1,2,3,4} （找到答案）
```
当前点集与 $P$ 有 $2$ 个相同的点（因为一定会有 $i$ 相同，再找到一个必须有 $2$ 个），就说明找到了答案。

因此，我们只需要依次遍历 $i$ 连通的点 $j$ ，将 $j$ 连通的集合与 $P$ 比较，若有 $2$ 个及以上的相同点，则说明找到答案，否则将 $j$ 连通的集合加入 $P$。

在找答案的时候，我们已经确定了在 $4$ 个点中，有 $i,j$，通过遍历 $P$ ，可以再找出那个 $V_1$ 中的点，剩下的那个点暴力判断连通即可。

时间复杂度 $O(\frac{mt}{w})$，其中 $w = 32$，空间复杂度 $O(st)$。
## Code
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
inline LL read()
{
	LL res = 0, fl = 1;
	char ch = getchar();
	while (!(ch >= '0' && ch <= '9'))
	{
		if (ch == '-')
			fl = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		res = (res << 3) + (res << 1) + ch - '0', ch = getchar();
	return res * fl;
}
inline LL max(LL a, LL b) { return a > b ? a : b; }
inline LL min(LL a, LL b) { return a < b ? a : b; }
const LL N = 3e5 + 5, M = 3e3 + 5, inf = 0x3f3f3f3f;
int s, t, m;
vector<int> e[N + M];
bitset<M> b[N], p, tp;
inline void Output(int x, int y, int k)
{
	for (int i = 1; i <= s; i++)
	{
		if (i == y)
			continue;
		int cnt = 0;
		for (int j = 0; j < e[i].size(); j++)
		{
			int to = e[i][j];
			if (to == x || to == k)
				cnt++;
		}
		if (cnt == 2)
		{
			cout << i << ' ' << x << ' ' << y << ' ' << k << '\n';
			return;
		}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	int x, y;
	s = read(), t = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		x = read(), y = read();
		e[x].push_back(y);
		e[y].push_back(x);
		b[x][y - s] = 1;
	}
	for (int i = s + 1; i <= s + t; i++)
	{
		p.reset();
		for (int j = 0; j < e[i].size(); j++)
		{
			int y = e[i][j];
			tp = p & b[y];
			if (tp.count() > 1)
			{
				int k;
				for (k = s + 1; k <= s + t; k++)
				{
					if (i != k && tp[k - s])
						break;
				}
				Output(i, y, k);
				return 0;
			}
			p |= b[y];
		}
	}
	cout << "-1\n";
	return 0;
}
```


---

## 作者：_shine_ (赞：0)

### 题目大意
在一个二分图中，请你找到一个任意长度为 $4$ 的四元环。
### 思路分析
显然在一个四元环中，每个都一定存在节点在左右两边，在找环的时候去找个数为四的环即可。

但显然，在此题中，使用 $n^3$ 的做法会超时，显然考虑把代码优化为 $n^2$ 或 $n$ 的级别，排除 $n$ 级别做法（这样显然不可能），若优化为 $n^2$，显然对式子进行等价变形，考虑使用 $a_{i,j}$，表示在点 $i,j$ 中能通过边到达的共同顶点，在边记录的同时查看是否有这个点，若有，则说明找到了四元环，在此时输出答案即可。
### Code
#### [AC 记录](https://www.luogu.com.cn/record/109929418)
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e3+10;
const int maxm=3e5+10;
int n,m,k;
int a[maxn][maxn];
vector<int>e[maxm];

signed main(){
	cin >> n >> m >> k;
	for(int i=1;i<=k;++i){
		int x,y;
		cin >> x >> y;
		e[x].push_back(y-n);
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<e[i].size();++j){
			for(int k=0;k<e[i].size();++k){
				if(j==k)continue;
				else{
					int x=e[i][j],y=e[i][k];
					if(a[x][y]!=0){
						cout << a[x][y] << " " << x+n << " " << y+n << " " << i << endl;
						return 0;
					}else{
						a[x][y]=i;
					}
				}
			}
		}
	}
	puts("-1");
	return 0;
}
```


---

## 作者：CQ_Bab (赞：0)

# 前言
这道题还是十分简单的，考场上没切出来有点可惜。
# 思路
我们可以发现对于一个二分图我们是不是可以把节点分为左右两边，那么我们在找环的时候只用找总个数为四的环，那么我们是不是就能想到一种办法就是既然我们要找总个数为 $4$ 的环那么不就是一边两个点吗，不就有了一种 $n^3$ 的做法吗但是这样会超时，那么我们就去给代码做等价变形，我们发现其实求出两个点能同时到达的点很好求只需要枚举能到达的点然后在看它能走到的另一边的点即可，那么我们是不是可以用一个数组 $g_{i,j}$ 来代表右边的点 $i$ 和 $j$ 能通过一条边共同能到达的点，那么我们在赋值时若 $g_{i,j}$ 已经有值了不就已经构成了一个四个节点组成的环了吗？

听到这里是不是就有一个疑问，就是 $2\leq v_i\leq3\times10^5$ 不是存不下吗？问得好，我们对于两边的点不是拆开来的吗？那么不就不会打搅了吗，所以我们在存边时将前面那些点减掉不就行了吗？对呀，这就是一个离散化呀！

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(ix,x,y) for(int ix=x;ix<=y;ix++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define int long long
#define fire signed
int n,m,k;
vector<int>v[300100];
int x,y;
int g[3010][3010];
fire main() {
	cin>>n>>m>>k;
	rep(i,1,k) {
		cin>>x>>y;
		v[x].push_back(y-n); //存边时离散化 
	}
	rep(x,1,n) {
		int l=v[x].size();
		rep(A,0,l-1) {
			rep(B,A+1,l-1) {//避免重复 
				int a=v[x][A],b=v[x][B];
				if(g[a][b]==0) g[a][b]=x; //若还没有能通过一条边到达的点则记录上 
				else {
					cout<<x<<" "<<a+n<<" "<<g[a][b]<<" "<<b+n<<endl; //有了直接输出，记得要加回来 
					return false;
				}
			}
		}
	}
	cout<<"-1\n";
	return false;
}
```


---

## 作者：loser_seele (赞：0)

感谢 @[霖ux](https://www.luogu.com.cn/user/520914) 的帮助。

题意：找出给定二分图里任意一个四元环。

因为给定的图是二分图，所以四元环必定两个端点在 $ S $ 上，两个端点在 $ T $ 上，观察到 $ T $ 的大小很小，于是可以枚举所有 $ T $ 中的点对 $ (u,v) $，每次将 $ u,v $ 的所有出边染色，当染色时发现待染色的点已经被染色过的时候，不妨设待染色的颜色为 $ w $，已经染的颜色为 $ x $，则 $ (u,v,w,x) $ 即为答案，如果遍历全部点对没找到答案则为无解。

时间复杂度 $ \mathcal{O}(n^2) $，其中 $ n\leq3000 $ 为 $ T $ 的大小，可以通过。

注意点的编号最大可以达到 $ 3.3 \times 10^5 $ 的级别，否则会越界。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=4e5+10;
vector<int>G[maxn];
const int maxm=3e3+10;
int mapp[maxm][maxm];
signed main()
{
int s,t,m;
cin>>s>>t>>m;
for(int i=1;i<=m;i++)
{
int u,v;
cin>>u>>v;
G[u].push_back(v-s);
}
vector<int>p;
for(int k=1;k<=s;k++)
{
p.clear();
for(int j=0;j<G[k].size();j++)
p.push_back(G[k][j]);
for(int i=0;i<p.size();i++)
for(int j=0;j<p.size();j++)
if(i!=j)
{
if(mapp[p[i]][p[j]])
{
cout<<mapp[p[i]][p[j]]<<' '<<p[i]+s<<' '<<p[j]+s<<' '<<k;
return 0;
}
else
mapp[p[i]][p[j]]=k;
}
}
cout<<-1;
}
```


---

