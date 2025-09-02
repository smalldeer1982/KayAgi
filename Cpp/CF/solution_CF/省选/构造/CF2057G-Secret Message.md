# Secret Message

## 题目描述

每个周六晚上，平行班的老师亚历山大 B，总会把一封密码信息写在交互式在线白板上，发送给另一位老师亚历山大 G。这封信相当重要，而亚历山大 G 正在授课，因此在线白板就成了一个理想的秘密传递工具。

这个白板是一个由 $n$ 行 $m$ 列构成的网格。网格中每个单元格大小是 $1 \times 1$。部分单元格已经填满，用符号 "." 表示，不能在其中书写；剩下的未填满的单元格称为自由单元格，用符号 "#" 代表。

我们需要关注白板的两个特性：

- $s$：自由单元格的数量。
- $p$：由这些自由单元格构成的图形的边界周长。

设 $A$ 为当前所有自由单元格的集合。你的任务是从中找到一个子集 $S \subseteq A$，满足以下条件：

- $|S| \le \frac{1}{5} \cdot (s+p)$，即集合 $S$ 的大小不超过 $s$ 和 $p$ 的加和的五分之一。
- 每一个自由单元格，要么已经在 $S$ 中，要么与 $S$ 中的某个单元格相邻（共用一条边）。

可以证明，总有这样的集合 $S$ 存在，你只需找到任意符合条件的一个即可。

## 说明/提示

例如：

- 在第一个例子中，$s=5$ 和 $p=12$，所以 $S$ 的单元格数量不能超过 $\frac{1}{5} \cdot (5+12) = 3.4$，即 $|S| \le 3$。给出的 $S$ 集合包含 1 个单元格，符合条件。

- 在第二个例子中，$s=12$ 和 $p=16$，所以 $S$ 的单元格数量不能超过 $\frac{1}{5} \cdot (12+16)= 5.6$，即 $|S| \le 5$。给出的 $S$ 集合包含 4 个单元格，符合条件。

- 在第三个例子中说明了周长的概念。任何网格图形都有一个由线段组成的边界，边界线段的长度总和即为周长。在示例中，黑色粗线标示的是自由单元格形成图形的边界，其总长度为 $p=24$。同时，$s=11$，故上限为 $|S| \le 7$，给出的 $S$ 集合大小为 6，符合条件。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2057G/7a81d6643999264740192ed7581cb70b4cce9f3c.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3 3
.#.
###
.#.
2 6
######
######
3 7
###....
#.#.###
###....```

### 输出

```
.#.
#S#
.#.
#S##S#
#S##S#
S#S....
#.#.S#S
S#S....```

# 题解

## 作者：Purslane (赞：12)

# Solution

这道题和 2024 年数学高联 T3 的技巧几乎一模一样，为啥我没做出来？

考虑给出 $5$ 组构造方案，他们 $|S|$ 的和为 $s+p$，这样就必存在一种方案的 $|S| \le \dfrac{1}{5} (s+p)$。

如果能将所有点染上五种颜色，使得任何一个点的邻域和自己恰好为这五种颜色，那么对于每种颜色 $i$，取 $S$ 为所有颜色为 $i$ 的 `#` 格子，以及不被上述任何一个格子覆盖或相邻的 `#` 格。后者只会出现在边界上，且边界外对应的格子恰好是颜色 $i$。

显然这五种颜色的 $|S|$ 之和为 $s+p$。

怎么五染色？考虑在模意义下构造：令 $col_{i,j} = (i+2j) \bmod 5$，容易验证符合要求。

直接 `vector` 套 `vector` 存储一些东西会 MLE，建议映射成线性序列。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=6e6+10,dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int T,n,m,mp[MAXN];
inline int gid(const int i,const int j) {return i*(m+2)+j;}
vector<pair<int,int>> gpos(int col) {
	vector<pair<int,int>> ans;
	ffor(i,1,n) ffor(j,1,m) if(mp[gid(i,j)]==1) {
		if((i+2*j)%5==col) ans.push_back({i,j});
		else ffor(d,0,3) {
			int ii=i+dx[d],jj=j+dy[d];
			if((ii+2*jj)%5==col&&mp[gid(ii,jj)]==0) ans.push_back({i,j});
		}
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m;
		ffor(i,0,(n+2)*(m+2)) mp[i]=0;
		ffor(i,1,n) {
			string S;
			cin>>S,S="&"+S;
			ffor(j,1,m) if(S[j]=='#') mp[gid(i,j)]=1;
		}
		vector<pair<int,int>> ans=gpos(0);
		ffor(i,1,4) {
			vector<pair<int,int>> nw=gpos(i);
			if(nw.size()<ans.size()) ans=nw;
		}
		for(auto id:ans) mp[gid(id.first,id.second)]=2;
		ffor(i,1,n) {
			ffor(j,1,m) if(mp[gid(i,j)]==1) cout<<'#';
			else if(mp[gid(i,j)]) cout<<'S';
			else cout<<'.';
			cout<<'\n';	
		}
	}
	return 0;
}
```

---

## 作者：int08 (赞：5)

## 前言
神仙题目。

如果场上我放弃 E2 来做这个，我估计我也做不出来。

# Solution

先考虑一种简单情况：$A$ 是一个大矩形，由于矩形很大，周长忽略不计，就是要用 $\frac{s}{5}$ 量级来完成任务。

这似乎是个经典问题，因为每个可以覆盖形如一个十字形的 $5$ 块，所以不同块直接不能重叠，容易完成密铺：

![](https://cdn.luogu.com.cn/upload/image_hosting/m8uhkk8m.png)

中心点满足 $2i+j$ 模 $5$ 意义下同余。

但是有一个问题：边界上那些怎么办？

而且还有一个问题：实际的图可不是规则的矩形，中间很可能抠掉一些，万一正好抠掉了中心点，旁边需要多选四个，直接爆炸了。

我感觉接下来一步是难点，也是妙点。

注意到我们其实有五种中心点的集合可选，我们假设选择了某种中心点集合 k 之后，某个在 $A$ 中的非中心点 $(i,j)$ 相邻的中心点恰好不在 $A$ 中，就称 $(i,j,k)$ 是一个坏点组。

发现每个坏点组意味着存在相邻两个元素一个在 $A$ 中一个不在，它们的共边必然是 $A$ 的一条边框，换句话说，坏点组总数为 $p$。

所以我们只需要选择某个 $k$ 对应的中心点和坏点，并在 $k\in [0,4]$ 中用最优的那个 $k$，由于总共选择了不超过 $(s+p)$ 个点，最优的必然不超过 $\frac{s+p}{5}$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,i,j,k;
int dir[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
#define N 2000500
string s[N];
vector<pair<int,int> > e[5];
int main()
{
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(i=1;i<=n;i++) cin>>s[i],s[i]=' '+s[i]+' ';
		s[0].resize(m+2),s[n+1].resize(m+2);
		for(k=0;k<5;k++)
		{
			for(i=1;i<=n;i++)
				for(j=1;j<=m;j++) if(s[i][j]=='#')
				{
					if((i+2*j)%5==k) e[k].push_back({i,j});
					else for(int d=0;d<4;d++) if((i+dir[d][0]+2*j+2*dir[d][1])%5==k&&s[i+dir[d][0]][j+dir[d][1]]!='#') e[k].push_back({i,j});
				}
		}
		pair<int,int> mn={1e9,5};
		for(i=0;i<=4;i++) mn=min(mn,{int(e[i].size()),i});
		for(auto x:e[mn.second]) s[x.first][x.second]='S';
		for(i=0;i<=4;i++) e[i].clear();
		for(i=1;i<=n;i++,puts(""))
			for(j=1;j<=m;j++) putchar(s[i][j]);
	}
}
```
# The End.

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2057G)

**题目大意**

> 在 $n\times m$ 网格上给出若干个格子，选择其中的若干个，使得每个未被选择格子与某个选择的格子四联通。
>
> 给出一种选择格子数 $\le \dfrac{s+p}5$ 的方案，其中 $s$ 是格子个数，$p$ 是格子构成图形的周长。
>
> 数据范围：$n\times m\le 10^6$。

**思路分析**

这种问题可以考虑鸽巢原理，即构造 $5$ 个方案，选出格子数总和为 $s+p$，取出最小的一种肯定满足题意。

当网格为无穷大网格时，我们要恰好选出 $\dfrac 15$ 的格子，即任意两个选出的格子不四联通，可以按 $(i+2j)\bmod 5$ 分类，选出某类的所有格子一定能覆盖整个网格。

回到原问题，对于每个 $r\in[0,5)$，取出所有 $(i+2j)\bmod 5=r$ 的格子，如果该格子可以选就直接选择。

此时还会剩下一些格子未被覆盖，那么这个格子一定在边界上，这条边界外的格子一定满足 $(i+2j)\bmod 5=r$。

此时每条边界只会在恰某个 $r$ 中产生一次贡献，直接选择这些未覆盖的格子，此时五种方案的总代价恰好为 $s+p$，直接取最小值。

时间复杂度 $\mathcal O(nm)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e6+5;
string s[MAXN];
vector <int> id[MAXN];
int G[MAXN][7];
bool vis[MAXN];
int n,m,q;
void link(int u,int v) { G[u][++G[u][0]]=v,G[v][++G[v][0]]=u; }
void upd(vector<int>&f) {
	memset(vis,0,q+1);
	for(int i:f) for(int j=1;j<=G[i][0];++j) vis[G[i][j]]=true;
	for(int i=1;i<=q;++i) if(!vis[i]) f.push_back(i);
}
vector <int> f[5];
void solve() {
	cin>>n>>m,q=0;
	for(int i=0;i<n;++i) {
		cin>>s[i],id[i].resize(m,0);
		for(int j=0;j<m;++j) if(s[i][j]=='#') {
			id[i][j]=++q,G[q][G[q][0]=1]=q;
			if(i>0&&s[i-1][j]=='#') link(q,id[i-1][j]);
			if(j>0&&s[i][j-1]=='#') link(q,id[i][j-1]);
			f[(i+2*j)%5].push_back(q);
		}
	}
	int x=0;
	for(int r:{0,1,2,3,4}) {
		upd(f[r]);
		if(f[r].size()<f[x].size()) x=r;
	}
	memset(vis,0,q+1);
	for(int i:f[x]) vis[i]=true;
	for(int i=0;i<n;++i) {
		for(int j=0;j<m;++j) if(vis[id[i][j]]) s[i][j]='S';
		cout<<s[i]<<"\n";
		string().swap(s[i]),vector<int>().swap(id[i]);
	}
	for(int r:{0,1,2,3,4}) f[r].clear();
}
signed main() {
	for(int r:{0,1,2,3,4}) f[r].reserve(MAXN);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

