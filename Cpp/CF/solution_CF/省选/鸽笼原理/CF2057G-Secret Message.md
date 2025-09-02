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

## 作者：Purslane (赞：14)

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

## 作者：R_shuffle (赞：2)

首先由于限制比较逆天，所以考虑转一下。

即如果能找出 $5$ 种方案，且总和为 $s+p$，那么必定有一种是满足条件的。

所以就考虑用 $5$ 种颜色给所有点染色，满足一个点即其四连通的领域的颜色互不相同。然后不难发现这样是可行的，因为边界上需要补几个，但是有了周长的加成，这两个可以认为是能抵消的。

然后染色可以考虑直接填，具体的，不妨存一个 $5\times 4$ 的表格，分别表示当前点的颜色为 $c$ 的时候，这个点四联通的格子分别是什么颜色。然后那个 $5\times 4$ 的表格直接手写一个，注意颜色之间不能有矛盾，最开始给随便一个格子染一种颜色，其他的格子直接用表格内容去平推就行了。

---

## 作者：Amoribus (赞：1)

很容易注意到 $\dfrac{1}{5}$ 这个特别的限制。我们考虑大致呈十字形的密铺，差不多能感觉出来这种密铺的量级就是 $\dfrac{1}{5}$。

如何构造呢？通过打表观察法可知满足这个条件的点 $(i,j)$ 满足 $(i+2j)$ 在模 $5$ 意义下同余。如果这个中心点是不能填的，就暴力的把它相邻的四个格子填上。需要暴力填的格子总数不超过 $p$。

接下来考虑这个做法的正确性。由于上述说明的 $5$ 种填法所填的格子总数不超过 $s+p$，可以采用反证法，假设所有的填法超过了 $\dfrac{s+p}{5}$ 个格子，则 $5$ 种填法的格子总数超过了 $s+p$，推出矛盾。因此必然有一种填法能满足要求。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define pii pair<int,int>
#define fir first
#define sec second
const int N=2e6+7;
int n,m,S,P;
string s[N];
map<pii,bool> mp;
vector<pii> a[5];
int T;
void solve(){
	S=P=0;
	cin>>n>>m;
	repn(i) cin>>s[i],s[i]=' '+s[i];
	repn(i){
		repm(j){
			if(s[i][j]=='#'){
				S++;
				if(i==1) P++;
				else if(s[i][j]!=s[i-1][j]) P++;
				if(i==n) P++;
				else if(s[i][j]!=s[i+1][j]) P++;
				if(j==1) P++;
				else if(s[i][j]!=s[i][j-1]) P++;
				if(j==m) P++;
				else if(s[i][j]!=s[i][j+1]) P++;
			}
		}
	}
//	cout<<S<<" "<<P<<endl;
	for(int c=0;c<5;c++){
		a[c].clear();
		mp.clear();
		int cnt=0;
		repn(i){
			repm(j){
				if((i+2*j)%5==c&&s[i][j]=='#'){
					cnt++;
//					cout<<"cnt="<<cnt<<"\n";
					a[c].pb({i,j});
					mp[{i,j}]=mp[{i+1,j}]=mp[{i,j+1}]=mp[{i-1,j}]=mp[{i,j-1}]=1;
				}
			}
		}
		repn(i){
			repm(j){
				if(!mp.count({i,j})&&s[i][j]=='#'){
					cnt++;
//					cout<<"cnt="<<cnt<<"\n";
					a[c].pb({i,j});
					mp[{i,j}]=mp[{i+1,j}]=mp[{i,j+1}]=mp[{i-1,j}]=mp[{i,j-1}]=1;
				}
			}
		}
//		cout<<cnt<<" "<<S+P<<endl;
		if(cnt*5>S+P) continue;
		mp.clear();
		for(auto v:a[c]){
//			cout<<v.fir<<" "<<v.sec<<"\n";
			mp[v]=1;
		}
		repn(i){
			repm(j){
				if(mp[{i,j}]==1&&s[i][j]=='#'){
					putchar('S');
				}
				else if(s[i][j]=='#'&&mp[{i,j}]==0) putchar('#');
				else if(s[i][j]=='.') putchar('.');
			}
			puts("");
		}
		return;
	}	
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen("indian6.in","r",stdin);
//	freopen("indian6.out","w",stdout);
	cin>>T;
	while(T--){
		solve();	
	}

	return 0;
}
```

---

## 作者：Jorisy (赞：0)

这个题目限制给的 $\dfrac 15$ 很奇怪。

考虑如下 trick：如果我们不考虑这个限制的情况下构造出了 $5$ 种合法方案，并且这些方案的 $|S|$ 之和恰为 $s+p$，根据抽屉原理，其中必然存在至少一个方案满足 $|S|\le\dfrac15(s+p)$。

这也太牛了！那我们怎么找到这五个方案呢？

考虑一种十字形的密铺：

$$
\def\sq{\rule{10px}{10px}}
\def\sq{\rule{10px}{10px}}
\red\sq\blue\sq\blue\sq\blue\sq\red\sq\blue\sq\red\sq\red\sq\red\sq\\[-3px]
\red\sq\red\sq\blue\sq\red\sq\blue\sq\blue\sq\blue\sq\red\sq\blue\sq\\[-3px]
\red\sq\blue\sq\red\sq\red\sq\red\sq\blue\sq\red\sq\blue\sq\blue\sq\\[-3px]
\blue\sq\blue\sq\blue\sq\red\sq\blue\sq\red\sq\red\sq\red\sq\blue\sq\\[-3px]
\red\sq\blue\sq\red\sq\blue\sq\blue\sq\blue\sq\red\sq\blue\sq\red\sq\\[-3px]
\blue\sq\red\sq\red\sq\red\sq\blue\sq\red\sq\blue\sq\blue\sq\blue\sq\\[-3px]
\blue\sq\blue\sq\red\sq\blue\sq\red\sq\red\sq\red\sq\blue\sq\red\sq\\[-3px]
\blue\sq\red\sq\blue\sq\blue\sq\blue\sq\red\sq\blue\sq\red\sq\red\sq\\[-3px]
\red\sq\red\sq\red\sq\blue\sq\red\sq\blue\sq\blue\sq\blue\sq\red\sq\\[-3px]
$$

发现，如果我们选择了所有十字形中心，那么剩余未被影响到的格子就会在边上，我们在另外选择这些点即可。

注意到这些十字形中心的坐标 $(i,j)$ 满足 $(i+2j)\bmod5$ 同余，所以我们按照这种方式五染色，就能得到 $5$ 种合法方案了！

```cpp
#include<bits/stdc++.h>
#define N 2000005
#define id(X,Y) ((X-1)*m+(Y))
#define ll long long
#define mod 
using namespace std;

int n,m,a[N],col[N],vis[N];

void sol()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            int id=id(i,j);
            col[id]=(i+j*2)%5;
            char c;
            cin>>c;
            a[id]=c=='#';
            vis[id]=0;
        }
    }
    int lim=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            int id=id(i,j);
            if(!a[id]) continue;
            lim++;
            lim+=i==n||!a[id(i+1,j)];
            lim+=j==m||!a[id(i,j+1)];
            lim+=i==1||!a[id(i-1,j)];
            lim+=j==1||!a[id(i,j-1)];
        }
    }
    lim/=5;
    for(int c=0;c<5;c++)
    {
        vector<int>vec;
        fill(vis+1,vis+n*m+1,0);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                int id=id(i,j);
                if(!a[id]||col[id]!=c) continue;
                vis[id]=1;
                vec.push_back(id);
                if(i<n) vis[id(i+1,j)]=1;
                if(j<m) vis[id(i,j+1)]=1;
                if(i>1) vis[id(i-1,j)]=1;
                if(j>1) vis[id(i,j-1)]=1;
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                int id=id(i,j);
                if(!a[id]||vis[id]) continue;
                vec.push_back(id);
            }
        }
        if(vec.size()>lim) continue;
        fill(vis+1,vis+n*m+1,0);
        for(auto k:vec) vis[k]=1;
        break;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            int id=id(i,j);
            cout<<(vis[id]?'S':a[id]?'#':'.');
        }
        cout<<'\n';
    }
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) sol();
    return 0;
}
```

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

