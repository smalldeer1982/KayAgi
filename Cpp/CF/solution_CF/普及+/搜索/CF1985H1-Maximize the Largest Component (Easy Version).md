# Maximize the Largest Component (Easy Version)

## 题目描述

Easy and hard versions are actually different problems, so read statements of both problems completely and carefully. The only difference between the two versions is the operation.

Alex has a grid with $ n $ rows and $ m $ columns consisting of '.' and '\#' characters. A set of '\#' cells forms a connected component if from any cell in this set, it is possible to reach any other cell in this set by only moving to another cell in the set that shares a common side. The size of a connected component is the number of cells in the set.

In one operation, Alex selects any row $ r $ ( $ 1 \le r \le n $ ) or any column $ c $ ( $ 1 \le c \le m $ ), then sets every cell in row $ r $ or column $ c $ to be '\#'. Help Alex find the maximum possible size of the largest connected component of '\#' cells that he can achieve after performing the operation at most once.

## 说明/提示

In the second test case, it is optimal for Alex to set all cells in column $ 2 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 6 $ .

In the third test case, it is optimal for Alex to set all cells in row $ 2 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 9 $ .

In the fourth test case, it is optimal for Alex to set all cells in row $ 4 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 11 $ .

## 样例 #1

### 输入

```
6
1 1
.
4 2
..
#.
#.
.#
3 5
.#.#.
..#..
.#.#.
5 5
#...#
....#
#...#
.....
...##
6 6
.#..#.
#..#..
.#...#
#.#.#.
.#.##.
###..#
6 8
..#....#
.####.#.
###.#..#
.##.#.##
.#.##.##
#..##.#.```

### 输出

```
1
6
9
11
15
30```

# 题解

## 作者：BrotherCall (赞：9)

## 题意

给定一个由 `#` 和 `.` 组成的 $n \times m$ 的网格，请进行以下的操作**一次**，使图中由 `#` 构成的连通块最大。

操作：选定一行**或**一列，将其全部变为 `#`。

输出操作后最大连通块点数。

## 思路

很自然地想到枚举每一行/每一列，难点在于怎么计算答案。

我们先考虑填行的情况。

如果我们把一行填满，则相当于桥一样把这条线两边的连通块连起来了。

所以当我们枚举第 $i$ 行时，答案为：第 $i$ 行 `.` 的数量，并将第 $i - 1$ 到 $i + 1$ 这三行的连通块**不重不漏**地加入贡献。

这里选择先 $\text{dfs}$ 给每个连通块标个号，并计算该连通块大小。时间复杂度 $O(nm)$。

然后计算答案的时候，用 $\text{map}$ 对编号去一下重，就能做到不重了。

填列的做法和填行没有任何区别。

## 代码

代码复杂程度远难于思路的一题。

[Link.](https://codeforces.com/contest/1985/submission/265391539)

---

## 作者：Eddie08012025 (赞：7)

## 化简题意
给定一个 $n\times m$ 的网格，每个格子上是 `#` 或 `.`，现在将某一行或某一列的所有格子变成 `#`，问能得到的最大 `#` 连通块。
## 思路
暴力肯定是不行的，首先 dfs 处理原来的所有连通块，给所有连通块编号，记录所有 `#` 格子属于的连通块与每个连通块的格子个数。

然后就要处理将某一行或某一列的所有格子变成 `#`。处理行列用同样的方法，下面讲解处理某一行的所有格子变成 `#` 的情况。

假设将第 $x$ 行的所有格子变成 `#`，用一个 set 存储经过 $x-1$ 或 $x$ 或 $x+1$ 行的连通块编号（$x$ 行全部变为 `#`，所以 $x-1,x+1$ 行经过的连通块一定会连上第 $x$ 行），由于 set 自动去重，所以构成的连通块格数就是所有经过的连通块的格子总和加第 $x$ 行的 `.` 个数（每个联通块格数已经预处理了，还要加上第 $x$ 行的所有格子变成 `#` 导致的 `.` 变成 `#` 的 `.` 的个数）。

处理列用类似的方法，这里不再讲解。

下面，放上我的 AC 代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t,m,cnt,shu[1000005],sum,ans,xx[4]={0,0,1,-1},yy[4]={1,-1,0,0};
//shu数组处理每个连通块的格数，cnt是连通块个数，xx与yy是偏移值 
vector<vector<char>>z;//这是输入的网格图 
vector<vector<int>>a,vis;//a存储每个#格子的所属连通块编号，vis数组用于处理连通块 
void dfs(int x,int y){ 
	vis[x][y]=1;//标记为已走过 
	shu[cnt]++;//连通块格数+1 
	a[x][y]=cnt;//标记(x,y)的所属连通块编号 
	for(int i=0;i<4;i++){
		int nx=x+xx[i],ny=y+yy[i];
		if(nx<1||ny<1||nx>n||ny>m||vis[nx][ny]||z[nx][ny]=='.')continue;//超界或走向的地方已去过 
		dfs(nx,ny);
	}
}
set<int>c; 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		ans=cnt=0;
		z.assign(n+1,vector<char>(m+1,0));//初始化（看不懂） 
		vis.assign(n+1,vector<int>(m+1,0));
		a.assign(n+1,vector<int>(m+1,0));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>z[i][j];
			}
		}for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){//处理连通块 
				if(!vis[i][j]&&z[i][j]=='#'){
					shu[++cnt]=0;
					dfs(i,j);
				}
			}
		}for(int j=1;j<=m;j++){//处理行 
			c.clear(); 
			sum=0;
			for(int i=1;i<=n;i++){
				if(z[i][j]=='.'){ 
					sum++;
				}else{
					c.insert(a[i][j]);//(i,j)是#，将所属连通块编号放进set里 
				}if(z[i][max(1,j-1)]=='#')c.insert(a[i][max(1,j-1)]);//如果上一行的i位置是#，将这格所属的连通块编号放入set里 
				if(z[i][min(m,j+1)]=='#')c.insert(a[i][min(m,j+1)]);//下一行同理 
			}for(int i:c)sum+=shu[i];//计算构成的连通块格数	
			ans=max(ans,sum);
		}for(int i=1;i<=n;i++){//处理列 
			c.clear();
			sum=0;
			for(int j=1;j<=m;j++){
				if(z[i][j]=='.'){
					sum++;
				}else{
					c.insert(a[i][j]);//(i,j)是#，将所属连通块编号放进set里 
				}if(z[max(1,i-1)][j]=='#')c.insert(a[max(1,i-1)][j]);//如果上一列的j位置是#，将这格所属的连通块编号放入set里 
				if(z[min(n,i+1)][j]=='#')c.insert(a[min(n,i+1)][j]);//下一列同理 
			}for(int j:c) sum+=shu[j];//计算构成的连通块格数	
			ans=max(ans,sum);
		}    
		cout<<ans<<"\n";//输出答案 
	}
	return 0;
}
```
**感谢观看！！！**

---

## 作者：Rachel_liu (赞：7)

~~蒟蒻第一次写题解（（~~。

来一篇码量友好的并查集。

## 思路
枚举每一行、每一列全部设置成 `'#'` 的情况，取最大值即为答案。

## 实现
先把网格遍历一遍，对于每个网格只需看其右边和下面的格子即可遍历所有边，用并查集得到所有连通块及其大小。

接下来枚举每一行全部设置成 `'#'` 的情况，这一行作为粘合剂，相当于把上面一行和下面一行的所有 `'#'` 所在的并查集都粘合成了一个新的大并查集。当然这里不真的对这些小并查集做 `join` 操作，只需要统计所有被粘到的小并查集的 `size` 之和（这里可以使用 `set` 去重），再加上这一行中本来是 `'.'` 的格子数量，即可得到该行的答案。

枚举列同理，不多赘述。

**注**：由于无法开 $(1\times10^6)^2$ 的二维数组，这里把二维的网格压成一维的数组，按顺序给予每个格子一个新编号。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MAXN = 1e6 + 5;
ll n, m, t, f[MAXN], size[MAXN], dx[2] = {0, 1}, dy[2] = {1, 0};
bool mp[MAXN];
char tmp[MAXN];

ll id(ll x, ll y){ // 二维 --> 一维 
    return (x-1)*m+y;
}

void init(){ // 初始化 
	for (ll i = 1; i <= n*m; i++)
		if (mp[i])
			f[i] = i, size[i] = 1;
		else
			f[i] = 0, size[i] = 0;
}

ll find(ll x){
	if (f[x] == x) return x;
	return (f[x] = find(f[x]));
}

void join(ll x, ll y){
	if (find(y) == find(x)) return; // 已经在一个并查集里就不用累加size了 
	size[find(y)] += size[find(x)];
	f[find(x)] = find(y);
}

int main(){
	scanf("%lld", &t);
	while (t--){
		scanf("%lld%lld", &n, &m);
		for (ll i = 1; i <= n; i++){
			scanf("%s", tmp+1);
			for (ll j = 1; j <= m; j++){
				if (tmp[j] == '#') mp[id(i, j)] = 1;
				else mp[id(i, j)] = 0;
			}
		}
		init();
		ll nx, ny;
		for (ll i = 1; i <= n; i++){
			for (ll j = 1; j <= m; j++){
				if (!mp[id(i, j)]) continue;
				for (ll k = 0; k <= 1; k++){ // 如果当前是 # 就向右向下查看 
					nx = i+dx[k], ny = j+dy[k];
					if (nx<=n && ny<=m && mp[id(nx, ny)]){ // 如果没越界且是 # 就合并 
						join(id(i, j), id(nx, ny));
					}
				}
			}
		}
		ll cnt, sum, ans = 0;
		set<ll> st; // set 去重 
 		for (ll i = 1; i <= n; i++){ // 枚举行 
			cnt = 0;
			st.clear();
			for (ll j = 1; j <= m; j++){
				cnt += mp[id(i, j)];
				st.insert(find(id(i, j)));
				st.insert(find(id(max(i-1, 1ll), j))); // 上面一个，不能小于 1
				st.insert(find(id(min(i+1, n), j))); // 下面一个，不能超过 n 
			}
			sum = m-cnt; // 新增的 # 
			for (auto ss: st)
				sum += size[ss]; // 这一行粘到的所有 # 所在的并查集 
			ans = max(ans, sum);
		}
 		for (ll j = 1; j <= m; j++){ // 枚举列 
			cnt = 0;
			st.clear();
			for (ll i = 1; i <= n; i++){
				cnt += mp[id(i, j)];
				st.insert(find(id(i, j)));
				st.insert(find(id(i, max(j-1, 1ll)))); // 左边一个，不能小于 1
				st.insert(find(id(i, min(j+1, m)))); // 右边一个，不能超过 m 
			}
			sum = n-cnt; // 新增的 # 
			for (auto ss: st)
				sum += size[ss]; // 这一列粘到的所有 # 所在的并查集 
			ans = max(ans, sum);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Louis_lxy (赞：6)

直接暴力出奇迹即可。

我们用 dfs 处理每个联通块的大小和每个点属于什么联通块。然后遍历每一行和每一列，并遍历这一行或这一列的每一个点，如果这个点是 `#` 就先加上这个联通块的大小并将答案减 1，防止重复计数。然后遍历临近这个点的两个不在同一行或同一列的点。如果是 `#` 号那么将这个连通块的答案加上去。

注意此时可能有重复，我们只需用个 set 存储能到达的联通块的编号进行去重最后计算即可。

AC 记录：https://www.luogu.com.cn/record/168310375

---

## 作者：Austin0116 (赞：4)

# 分析

我们可以直接暴力枚举每一行和每一列被覆盖，若枚举第 $i$ 行，可以先将答案加上 $m$ ，再将第 $i+1$ 与 $i-1$ 的 `#` 的数量加在答案中。枚举第 $j$ 列时同理。

所以我们可以先对每一个为 `#` 的地方进行深搜染色，并把每个颜色块中 `#` 的数量进行计数。在统计答案时，直接把枚举到的颜色块直接放进 set 中去去重，最后再对总和取最大值就是最终的答案。

**注意**：

**由于题目只给了 $n \times m$ 的数据范围，所以我们要用 vector 来存很多东西。**

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t,m,cnt,b[1000005],sum,mx;
char d[1000005];
vector<char> s[1000005];
vector<int> a[1000005],vis[1000005];
const int xx[]={0,0,1,-1};
const int yy[]={1,-1,0,0};
void dfs(int x,int y){//深搜染色
	vis[x][y]=1;
	b[cnt]++;
	a[x][y]=cnt;
	for(int i=0;i<4;i++){
		int xx1=x+xx[i],yy1=y+yy[i];
		if(xx1>0&&yy1>0&&xx1<=n&&yy1<=m&&!vis[xx1][yy1]&&s[xx1][yy1]=='#') dfs(xx1,yy1);
	}
}
set<int> c;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		mx=cnt=0;
		for(int i=1;i<=n;i++){//多测要清空
			s[i].clear();
			a[i].clear();
			vis[i].clear();
		}
		for(int i=1;i<=n;i++){
			scanf("%s",d+1);
			s[i].emplace_back(' ');//vector存字符串
			a[i].emplace_back(0);
			vis[i].emplace_back(0);
			for(int j=1;j<=m;j++){
				s[i].emplace_back(d[j]);
				vis[i].emplace_back(0);
				a[i].emplace_back(0);
			} 
		} 
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(!vis[i][j]&&s[i][j]=='#'){
			b[++cnt]=0;
			dfs(i,j);
		}
		for(int j=1;j<=m;j++){//枚举每一列
			c.clear();
			sum=n;
			for(int i=1;i<=n;i++){
				if(s[i][j]=='#'){
					sum--;
					c.insert(a[i][j]);//放进集合中去重
				} 
				if(s[i][max(1,j-1)]=='#') c.insert(a[i][max(1,j-1)]);//j-1列
				if(s[i][min(m,j+1)]=='#') c.insert(a[i][min(m,j+1)]);//j+1列
			}
			for(int x:c) sum+=b[x];	
			mx=max(mx,sum);//对答案取最大值
		}
		for(int i=1;i<=n;i++){//枚举每一行，与上面同理
			c.clear();
			sum=m;
			for(int j=1;j<=m;j++){
				if(s[i][j]=='#'){
					sum--;
					c.insert(a[i][j]);
				} 
				if(s[max(1,i-1)][j]=='#') c.insert(a[max(1,i-1)][j]);
				if(s[min(n,i+1)][j]=='#') c.insert(a[min(n,i+1)][j]);
			}
			for(int x:c) sum+=b[x];	
			mx=max(mx,sum);
		}    
		printf("%d\n",mx);//输出答案
	}
	return 0;
}
```

---

## 作者：YFF1 (赞：1)

## 思路：
很明显是并查集。注意到数据范围，可以直接枚举加入的那一行或者列的具体下标，然后扫一遍它的上下左右四个方向的井号格子，把没有被统计的原有井号格子连通块加入答案中，并且标记已经统计过的原有连通块。另外就是这道题需要把下标哈希化。更多细节见代码。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,fa[1000005],dx[5]={1,0,-1,0},dy[5]={0,1,0,-1},sz[1000005],ans,sum;
char c[1000005];
map<int,int>mp;
bool check(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void merge(int u,int v){
	u=find(u),v=find(v);
	if(u==v)return ;
	fa[u]=v;
	sz[v]+=sz[u];
}//并查集常规操作 
void init(int i,int j){
	int pos=(i-1)*m+j;
	if(c[pos]=='#'){
		if(mp[find(pos)]!=1)sum+=sz[find(pos)];
		mp[find(pos)]=1;
		return ;
	}//自己就是井号格子的加上自己所在连通块 
	sum++;
	for(int k=0;k<4;k++){
		int nx=i+dx[k];
		int ny=j+dy[k];
		if(check(nx,ny)){
			int pos2=(nx-1)*m+ny;
			if(c[pos2]=='#'){
				if(mp[find(pos2)]!=1){
					sum+=sz[find(pos2)];
					mp[find(pos2)]=1;
				}
			}//自己不是井号格子的加上自己四周的连通块，并且标记为已经使用 
		}
	}
}
signed main () {
	cin>>t;
	while(t--){
		ans=0;
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n*m;i++)fa[i]=i,sz[i]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cin>>c[(i-1)*m+j];
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int pos=(i-1)*m+j;
				if(c[pos]=='#'){
					for(int k=0;k<4;k++){
						int nx=i+dx[k];
						int ny=j+dy[k];
						if(check(nx,ny)){
							int pos2=(nx-1)*m+ny;
							if(c[pos2]=='#')merge(pos,pos2);
						}
					}
				}
			}
		}//预处理出原有的连通块大小和名字 
		for(int i=1;i<=n;i++){
			mp.clear();
			sum=0;
			for(int j=1;j<=m;j++)init(i,j);
			ans=max(ans,sum); 
		}
		for(int j=1;j<=m;j++){
			mp.clear();
			sum=0;
			for(int i=1;i<=n;i++)init(i,j);
			ans=max(ans,sum);
		}//枚举行和列 
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：luqyou (赞：1)

# 思路

很容易想到枚举填哪一行或者哪一列。考虑填完之后，将那些部分联通了起来。

若我们填了列 $x$，那么会将 $x-1$ 列和 $x+1$ 列的连通块全部连起来。

那么我们使用并查集维护连通块，然后将会 $x-1$，$x$ 和 $x+1$ 这三行的连通块全部统计一下（记得去重），最后计算一下填满这一行多出来的 `#` 个数就好了。

实现比较长，还是贴一下代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;
vector<int> c[maxn];
int n,m,f[maxn],sz[maxn],res;
int dx[]={0,0,1,0,-1};
int dy[]={0,1,0,-1,0};
int find(int x){ 
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
void merge(int u,int v){
	int fu=find(u),fv=find(v);
	if(fu!=fv) f[fu]=fv,sz[fv]+=sz[fu];
}
int id(int x,int y){
	return (x-1)*m+y;
}
void solve(){
	cin>>n>>m,res=0;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s,s=" "+s,c[i].resize(m+1);
		for(int j=1;j<=m;j++) f[id(i,j)]=id(i,j),sz[id(i,j)]=1,c[i][j]=(s[j]=='#');
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!c[i][j]) continue;
			for(int k=1;k<=4;k++){
				int nx=i+dx[k],ny=j+dy[k];
				if(nx>0&&ny>0&&nx<=n&&ny<=m&&c[nx][ny]) merge(id(i,j),id(nx,ny));
			}
		}
	}
	for(int i=1;i<=n;i++){
		int s=0;
		map<int,int> mp;
		if(i>1){
			for(int j=1;j<=m;j++){
				int idx=id(i-1,j),fa=find(idx);
				if(!mp[fa]&&c[i-1][j]) mp[fa]=1,s+=sz[fa];
			}
		}
		if(i<n){
			for(int j=1;j<=m;j++){
				int idx=id(i+1,j),fa=find(idx);
				if(!mp[fa]&&c[i+1][j]) mp[fa]=1,s+=sz[fa];
			}
		}
		for(int j=1;j<=m;j++){
			int idx=id(i,j),fa=find(idx);
			if(!mp[fa]&&c[i][j]) mp[fa]=1,s+=sz[fa];
		}
		for(int j=1;j<=m;j++) s-=c[i][j];
		res=max(res,s+m);
	}
	for(int i=1;i<=m;i++){
		int s=0;
		map<int,int> mp;
		if(i>1){
			for(int j=1;j<=n;j++){
				int idx=id(j,i-1),fa=find(idx);
				if(!mp[fa]&&c[j][i-1]) mp[fa]=1,s+=sz[fa];
			}
		}
		if(i<m){
			for(int j=1;j<=n;j++){
				int idx=id(j,i+1),fa=find(idx);
				if(!mp[fa]&&c[j][i+1]) mp[fa]=1,s+=sz[fa];
			}
		}
		for(int j=1;j<=n;j++){
			int idx=id(j,i),fa=find(idx);
			if(!mp[fa]&&c[j][i]) mp[fa]=1,s+=sz[fa];
		}
		for(int j=1;j<=n;j++) s-=c[j][i];
		res=max(res,s+n);
	}cout<<res<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=1;
    cin>>t;
    while(t--) solve();
	return 0;
}
```

---

## 作者：imsbNR (赞：0)

# 题解：CF1985H1 Maximize the Largest Component (Easy Version)

## 题意

给定一个由 ```#``` 和 ```.``` 组成的矩阵，可以把任意一行或一列全变成 ```#``` ，问最大的连通块的大小。

## 思路

对于变成 ```#``` 的一行或一列，它会将多个连通块连在一起，整个大连通快的大小即为答案。

问题是，我们要怎么计算大连通块的大小呢？

如果暴力枚举每一行和每一列，之后计算整个大连通块的大小，单次询问复杂度为 $O((m+n)mn)$ ，明显超时。

因为枚举每一行和每一列这个操作是必须的（也有可能是因为我太蒻了），所以考虑优化计算大连通块的大小。我们直接枚举这一行或列，看看经过哪些连通块，然后加上经过的 ```.``` 的数量，就是大连通块的大小了！时间复杂度 $O(nm)$ 。

## 注意

这道题的 $n,m\le 10^6$ ，可是 $nm \le 10^6$ ，我们不能用一个 $10^6 \times 10^6 $ 的二维数组存储矩阵，这样内存爆炸，事实上，我们只用存储 $10^6$ 个格子。

其他大佬用  ```map``` ，这样会比较慢，我们可以使用更快速的映射方法。

比如我们可以把一个二元组 $(i,j)$ （其中 $1 \le i \le n$ 且 $1 \le j \le m$ ）转化成正整数 $(i-1)m+j$ 且不会重复，以一个 $3\times 4$ 的表格为例，这把这个矩阵的每个坐标从这样：

||$1$|$2$|$3$|$4$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$(1,1)$|$(1,2)$|$(1,3)$|$(1,4)$|
|$2$|$(2,1)$|$(2,2)$|$(2,3)$|$(2.4)$|
|$3$|$(3,1)$|$(3,2)$|$(3,3)$|$(3,4)$|

变成这样：

||$1$|$2$|$3$|$4$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$1$|$2$|$3)$|$4$|
|$2$|$5$|$6$|$7$|$8$|
|$3$|$9$|$10$|$11$|$12$|

无重复无遗漏，不占空间。

对了，每个数组的每个元素在要用的时候再初始化，不然会超时（反正我是这样的）。

## code


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
ll t, n, m, mx, cnt;
ll a[N], v[N], sz[N];
ll ID(ll x, ll y) {return m * (x - 1) + y;}
ll dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
void dfs(ll x, ll y)
{
	v[ID(x, y)] = true;
	a[ID(x, y)] = cnt;
	sz[cnt]++;
	for (int i = 0; i < 4; i++)
	{
		ll xx = x + dx[i], yy = y + dy[i];
		if (xx < 1 or xx > n or yy < 1 or yy > m)
			continue;
		if (a[ID(xx, yy)] != -1 or v[ID(xx, yy)])
			continue;
		dfs(xx, yy);
	}
	return;
}
void solve()
{
	mx = -1, cnt = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char ch;
			cin >> ch;
			a[ID(i, j)] = (ch == '#' ? -1 : 0);
			v[ID(i, j)] = false;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (!v[ID(i, j)] and a[ID(i, j)] == -1)
			{
				sz[++cnt] = 0;
				dfs(i, j);
			}
	set <ll> st;
	ll k = 0;
	for (int i = 1; i <= n; i++)
	{
		st.clear();
		k = 0;
		for (int j = 1; j <= m; j++)
		{
			if (a[ID(i, j)])
				st.insert(a[ID(i, j)]);
			if (i > 1 and a[ID(i - 1, j)])
				st.insert(a[ID(i - 1, j)]);
			if (i < n and a[ID(i + 1, j)])
				st.insert(a[ID(i + 1, j)]);
			if (!a[ID(i, j)])
				k++;
		}
		for (auto s : st)
			k += sz[s];
		mx = max(mx, k);
	}
	for (int j = 1; j <= m; j++)
	{
		st.clear();
		k = 0;
		for (int i = 1; i <= n; i++)
		{
			if (a[ID(i, j)])
				st.insert(a[ID(i, j)]);
			if (j > 1 and a[ID(i, j - 1)])
				st.insert(a[ID(i, j - 1)]);
			if (j < m and a[ID(i, j + 1)])
				st.insert(a[ID(i, j + 1)]);
			if (!a[ID(i, j)])
				k++;
		}
		for (auto s : st)
			k += sz[s];
		mx = max(mx, k);
	}
	cout << mx << '\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

AC 记录 ：[link](https://codeforces.com/contest/1985/submission/277786589) 。

---

## 作者：qian0715 (赞：0)

### 题解：Maximize the Largest Component (Easy Version)
题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF1985H1) / [codeforces](https://codeforces.com/problemset/problem/1985/H1)

[个人博客站观看更佳！](https://moneygpt.site/archives/maximize-the-largest-component-solution)
#### 题目大意

该题目要求在一个由 `.` 和 `#` 组成的网格中，通过选择某一行或某一列，将该行或该列所有字符设置为 `#`，使得整个网格中 `#` 组成的最大连通块的大小最大化。

题目给定了多个测试用例，每个测试用例包含一个 $n \times m$ 的网格，网格中的每个字符是 `.` 或 `#`。要求我们找到执行一次操作后，`#` 组成的最大连通块的最大值。

#### 解题思路

##### 大致解题路线：

1.  BFS 搜索连通块，并记录连通块编号和大小，以备后用。

2.   $n$ 行遍历找最大。

3.   $m$ 列遍历找最大。

整体思路简单，但是码量十足。。。

下面是更具体的思路。

1. **初始化和输入处理**：

   - 首先读取输入的网格，并初始化访问标记数组 `vis`，该数组用于记录每个格子是否被访问过。
   - 使用广度优先搜索 BFS 来计算原始网格中每个连通块的大小，并将这些大小记录在一个字典 `tong` 中。

2. **模拟操作**：

   - 对于每一行，假设将整行设置为 `#`，计算由此形成的最大连通块。
   - 对于每一列，假设将整列设置为 `#`，计算由此形成的最大连通块。
   - 需要特别处理边界情况，确保相邻连通块不会因为重复计入而造成计算错误。

3. **计算最大连通块**：

   - 遍历每一行和每一列，模拟将该行或该列设置为 `#` 后的连通块大小。
   - 最后输出所有可能结果中的最大值。

   

   具体操作请看下方代码。

#### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1005;
int t, n, m;
int fx[5] = {0, 1, 0, -1, 0}; // BFS的方向数组
int fy[5] = {0, 0, 1, 0, -1}; // BFS的方向数组
int flag; // 连通块编号

queue<int> q1, q2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while (t--) { 
        cin >> n >> m;
        vector<vector<char>> a(n + 2, vector<char>(m + 2)); // 定义网格，边界用于处理
        vector<vector<int>> vis(n + 2, vector<int>(m + 2, 0)); // 标记连通块编号
        flag = 0;
        map<int, int> tong; // 存储每个连通块的大小

        // 读取网格数据
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }

        // BFS计算连通块大小
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (vis[i][j] == 0 && a[i][j] == '#') { // 如果当前格子未被访问且是'#'
                    flag++; // 更新连通块编号
                    vis[i][j] = flag; // 标记当前连通块编号
                    q1.push(i);
                    q2.push(j);
                    tong[flag]++; // 初始化连通块大小

                    // BFS扩展连通块
                    while (!q1.empty()) {
                        int nx = q1.front();
                        int ny = q2.front();
                        q1.pop(); 
                        q2.pop(); 

                        for (int i = 1; i <= 4; i++) { // 遍历四个方向
                            int xx = nx + fx[i], yy = ny + fy[i];
                            if (a[xx][yy] == '#' && !vis[xx][yy] && xx <= n && yy <= m && xx >= 1 && yy >= 1) {
                                q1.push(xx);
                                q2.push(yy);
                                vis[xx][yy] = flag; // 标记相邻格子
                                tong[flag]++; // 增加连通块大小
                            }
                        }
                    }
                }
            }
        }

        int ans = 0; // 存储最大连通块大小
        map<int, int> vis2, biaoji; // 辅助标记

        // 处理每一行
        for (int i = 1; i <= n; i++) {
            int cnt = 0; // 当前行形成的连通块大小
            biaoji.clear(); 
            vis2.clear();
            for (int j = 1; j <= m; j++) {
                if (a[i][j] == '#') {
                    vis2[vis[i][j]] = 1; 
                }
                if (a[i][j] == '.') cnt++;
                else if (!biaoji[vis[i][j]]) { // 如果连通块未被标记
                    biaoji[vis[i][j]] = 1; // 标记当前连通块
                    cnt += tong[vis[i][j]]; // 累加连通块大小
                }
                if (!biaoji[vis[i - 1][j]] && a[i - 1][j] == '#' && vis[i - 1][j] != vis[i][j]) {
                    cnt += tong[vis[i - 1][j]]; // 累加上方连通块
                    biaoji[vis[i - 1][j]] = 1; 
                    if (vis2[vis[i - 1][j]] == 1) cnt--; // 避免重复计入
                }
                if (!biaoji[vis[i + 1][j]] && a[i + 1][j] == '#' && vis[i + 1][j] != vis[i][j]) {
                    cnt += tong[vis[i + 1][j]]; // 累加下方连通块
                    biaoji[vis[i + 1][j]] = 1; 
                    if (vis2[vis[i + 1][j]] == 1) cnt--; 
                }
            }
            ans = max(ans, cnt); // 更新最大连通块大小
        }

        // 处理每一列
        for (int j = 1; j <= m; j++) {
            int cnt = 0; // 当前列形成的连通块大小
            biaoji.clear(); 
            vis2.clear(); 
            for (int i = 1; i <= n; i++) {
                if (a[i][j] == '#') {
                    vis2[vis[i][j]] = 1; 
                }
                if (a[i][j] == '.') cnt++;
                else if (!biaoji[vis[i][j]]) { 
                    biaoji[vis[i][j]] = 1; 
                    cnt += tong[vis[i][j]]; 
                }
                if (!biaoji[vis[i][j - 1]] && a[i][j - 1] == '#' && vis[i][j - 1] != vis[i][j]) {
                    cnt += tong[vis[i][j - 1]]; // 累加左侧连通块
                    biaoji[vis[i][j - 1]] = 1; 
                    if (vis2[vis[i][j - 1]] == 1) cnt--; 
                }
                if (!biaoji[vis[i][j + 1]] && a[i][j + 1] == '#' && vis[i][j + 1] != vis[i][j]) {
                    cnt += tong[vis[i][j + 1]]; // 累加右侧连通块
                    biaoji[vis[i][j + 1]] = 1; 
                    if (vis2[vis[i][j + 1]] == 1) cnt--; 
                }
            }
            ans = max(ans, cnt); // 更新最大连通块大小
        }

        cout << ans << endl; // 输出最大连通块的大小
    }
    return 0;
}

```

#### 复杂度分析

- **时间复杂度**: 

  - 每个测试用例的时间复杂度主要分为两部分：BFS 用于找到所有的连通块，复杂度为 $O(n \times m)$，而行和列的遍历为 $O(n \times m)$。
  - 因此总体时间复杂度为 $O(t \times n \times m)$，其中 $t$ 是测试用例数。

- **空间复杂度**: 

  - 额外使用了 `vis` 和 `tong` 两个数组，空间复杂度为 $O(n \times m)$。

  ---

  喜欢的话不要忘记点赞哈！

---

## 作者：ST_AS_IS_ZHY (赞：0)

## 题目大意

给定一个由 `.` 和 `#` 组成的网格，可以任选一行或者一列将其全部转变为 `#`，求出使得被更改行或列贡献最大的方案。此处贡献最大指该包含该行的由 `#` 组成的连通块的大小。

## 思路

首先转化一下问题，被更改行所在的连通块也就是原先就有的连通块加上新连上来的连通块，然后再加上本行中原先是 `.` 的格子数量。 

其次观察到 $1 \le n \cdot m \le 10^6$，这意味着必须要把这个网格拍扁来存，也意味着可以暴力 $n \cdot m$ 解决每个点的初始连通块大小。并且可以枚举每一种挑选情况。

然后分开看看每一部分该如何计算。

1. 行内点的个数点的个数是容易处理的，只需要挑选行的时候暴力扫一遍统计下来。
2. 新连的连通块大小：新连的连通块只会出现在被更改行或列的两侧，也就是直接加上相邻两侧的贡献再减去重复计算的，也就是被更改行原先就有的部分。

最后就是如何去重，这部分可以用 `set` 将所有连通块的编号都塞进去，塞完了再遍历一遍加回来，就不用考虑重复的问题了。（有没有佬说一下为什么 `unordered_set` 会被卡）

## code


```cpp
// Problem: Maximize the Largest Component (Easy Version)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1985H1
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define PII pair<int, int>
#define rint register int

using namespace std;

const int N = 2e5 + 10, M = 4e6 + 10, INF = 0x3f3f3f3f;

int dx[6] = {0, 1, -1, 0, 0};
int dy[6] = {0, 0, 0, 1, -1};
int n, m, ans, cnt, sum[M], id[M];
bool vis[M], mp[M];

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

inline int get(int x, int y) {return (x - 1) * m + y;}

void dfs(int x, int y, int idx)
{
	sum[idx] ++, id[get(x, y)] = idx; 
	for(int i = 1; i <= 4; i ++)
	{
		int xx = dx[i] + x, yy = dy[i] + y;
		if(xx > n || xx < 1 || yy > m || yy < 1 || id[get(xx, yy)] || !mp[get(xx, yy)]) continue;
		dfs(xx, yy, idx);
	}
}

inline void get_ans()
{
	set<int> st; int res = 0;
	for(int i = 1; i <= n; i ++)
	{
		st.clear(); res = 0;
		for(int j = 1; j <= m; j ++)
		{
			res += (!id[get(i, j)]);
			st.insert(id[get(i, j)]);
			st.insert(id[get(max(i - 1, 1ll), j)]);
			st.insert(id[get(min(i + 1, n), j)]);
		}
		for(auto j : st) res += sum[j];
		ans = max(res, ans);
	}
	for(int j = 1; j <= m; j ++)
	{
		st.clear(); res = 0;
		for(int i = 1; i <= n; i ++)
		{
			res += (!id[get(i, j)]);
			st.insert(id[get(i, j)]);
			st.insert(id[get(i, max(j - 1, 1ll))]);
			st.insert(id[get(i, min(j + 1, m))]);
		}
		for(auto j : st) res += sum[j];
		ans = max(res, ans);
	}
}

void clear()
{
	for(int i = 1; i <= n; i ++) for(int j = 1; j <= m; j ++) mp[get(i, j)] = id[get(i, j)] = 0;
	for(int i = 1; i <= cnt; i ++) sum[i] = 0;
	cnt = 0, ans = 0;	
}

signed main()
{
	int T = read();
	while(T --)
	{
		n = read(), m = read(); 
		for(int i = 1; i <= n; i ++)
		{
			for(int j = 1; j <= m; j ++) mp[get(i, j)] = (getchar() == '#');
			getchar();
		}
		for(int i = 1; i <= n; i ++) 
			for(int j = 1; j <= m; j ++) if(!id[get(i, j)] && mp[get(i, j)]) dfs(i, j, ++ cnt);
		get_ans(); printf("%lld \n", ans); clear();
	}	
	return 0;
}
```

---

