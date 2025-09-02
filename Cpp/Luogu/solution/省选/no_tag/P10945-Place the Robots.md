# Place the Robots

## 题目描述

罗伯特是一位著名的工程师。一天，他的老板给了他一个任务。任务的背景如下：给定一个方格地图。地图上有三种可以放置的方块：墙方块、草方块和空地。老板希望在地图上可以尽可能多地放置机器人。每个机器人都配备了激光武器，可以同时向四个方向（东南西北，可以理解为上下左右）发射激光。机器人必须待在同一位置（也就是一开始放置的位置）且只能放在空地上不断地发射激光。激光束可以穿过草方块，但不能穿过墙方块。显然，老板不希望看到一个机器人伤害另一个机器人。换句话说，两个机器人不能放置在同一行或同一列上，除非它们之间有一堵墙。作为罗伯特的好朋友和聪明的程序员，他请你帮忙解决这个问题。也就是请你根据给定地图的描述，计算在地图上可以放置的最大机器人数量。

## 说明/提示

$T \leq 11$，$1 \leq m , n \leq 50$

## 样例 #1

### 输入

```
2
4 4
o*** 
*### 
oo#o 
***o 
4 4 
#ooo 
o#oo 
oo#o 
***#```

### 输出

```
Case :1 
3
Case :2 
5```

# 题解

## 作者：yuruilin2026 (赞：6)

这是一道 [Hootime](https://www.luogu.com.cn/user/1275540) 看到就秒了的水紫。\
本题解默认已经熟练掌握了匈牙利算法。\
若没有，请移步 [P3386](https://www.luogu.com.cn/problem/P3386)。\
话不多说，开始！
1. 题意：\
   在地图内放机器人，只能在空地上放。\
   除非有墙的阻隔，否则不能再同一行列中放机器人。\
   求最多的机器人数量。
2. 思路：\
   ~~二分图秒了~~。\
   用行列作为二分图的子图（应该是叫这个名字吧）。\
   跑一遍匈牙利就行了。
3. 细节：\
   建边的时候怎么办呢？
   
   如果没有墙，那么只需将行看作是二分图的一边，列看作另一边，然后可以放置机器人的地方的行向列连边即可。

   本来一行只能放一个机器人，但墙的出现导致一行被隔开，所以在有墙的情况下，可以把一行看成多行。

   还有！多测要清空！

那么，上代码！\
代码里面有注释。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
char ch[1145][1145];
bool vis[1145][1145];
string str;
int g[114514],match[114514],re[114514],n,m,sum,next1[114514],head[114514],cnt;
int tot1,tot2;//左部点数量和右部点数量 
struct ppp{
	int d,x,y;
}a1[114514],a2[114514];
void add(int u,int p){ 
	++cnt;
	next1[cnt] = head[u],g[cnt] = p,head[u] = cnt;
}
bool dfs(int x){//匈牙利 
	for(register int i = head[x];i;i = next1[i]){//枚举右部点
		if(re[g[i]] == 0){//有边并且没被匹配 
			re[g[i]] = 1;//匹配上 
			if(match[g[i]] == 0){//match[i]存储的是匹配的人 
				match[g[i]] = x;
				return 1;
			}
			else if(dfs(match[g[i]])){
				match[g[i]] = x;
				return 1;
			}
		}
	}
	return 0;
}
void init(){
	for(register int i = 0;i <= 1143;++i) re[i] = 0;//re存储的是有没有被dfs过 
}
void init2(){//初始化(不得不说是真的恶心) 
	memset(vis,0,sizeof(vis));
	memset(g,0,sizeof(g));
	memset(match,0,sizeof(match));
	memset(re,0,sizeof(re));
	memset(next1,0,sizeof(next1));
	memset(head,0,sizeof(head));
	cnt = 0,tot1 = 0,tot2 = 0,sum = 0,n = 0,m = 0;
	for(register int i = 0;i <= 1513;++i){
		a1[i] = ppp{0,0,0};
		a2[i] = ppp{0,0,0};
	}
	for(register int i = 0;i <= 164;++i){
		for(register int j = 0;j <= 164;++j){
			ch[i][j] = ' ';
		}
	}
}
signed main(){
	cin.tie(0),cout.tie(0);
	int t;
	cin >> t;
	for(int ___ = 1;___ <= t;___++){
		init2();
		cin >> n >> m;
		for(register int i = 1;i <= n;i++){
			cin >> str;
			for(register int j = 1;j <= m;j++){
				 ch[i][j] = str[j-1];
			}
		}
		for(register int i = 1;i <= n;i++){
			for(register int j = 1;j <= m;j++){
				if(vis[i][j]) continue;
				if(ch[i][j] != 'o') continue;
				int xx11 = i,xx22 = i,yy11 = j,yy22 = j;
				while(xx11 > 1 && ch[xx11-1][j] != '#'){
					xx11--;//区间左端点 
				}
				while(xx22 < n && ch[xx22+1][j] != '#'){
					xx22++;//区间右端点 
				}
				for(register int k = xx11;k <= xx22;k++){
					vis[k][j] = 1;
				}
				a1[++tot1] = ppp{j,xx11,xx22};
			}
		}
		memset(vis,0,sizeof(vis));
		for(register int i = 1;i <= n;i++){
			for(register int j = 1;j <= m;j++){
				if(vis[i][j]) continue;
				if(ch[i][j] != 'o') continue;
				int xx11 = i,xx22 = i,yy11 = j,yy22 = j;
				while(yy11 > 1 && ch[i][yy11-1] != '#'){
					yy11--;//区间上端点 
				}
				while(yy22 < m && ch[i][yy22+1] != '#'){
					yy22++;//区间下端点 
				}
				for(register int k = yy11;k <= yy22;k++){
					vis[i][k] = 1;
				}
				a2[++tot2] = ppp{i,yy11,yy22};
			}
		}
		for(register int i = 1;i <= tot1;i++){
			for(register int j = 1;j <= tot2;j++){
				if(a1[i].x <= a2[j].d && a1[i].y >= a2[j].d){
					if(a2[j].x <= a1[i].d && a2[j].y >= a1[i].d){
						if(ch[a2[j].d][a1[i].d] == '*') continue;//交点是草不能建边 
						add(i,j);
					}
				}
			}
		}
		
		for(register int i = 1;i <= tot1;i++){
			init();
			if(dfs(i)) sum++;
		}
		cout << "Case :" << ___ << endl;
		cout << sum << endl;
	}
	return 0;
}
```

---

## 作者：Needna (赞：4)

这一道题先考虑没有墙的情况，就是二分图的最大独立集合（因为每一行，列只能有一个点）所以把行连向列，做二分图最大匹配，就是答案。

考虑墙的作用 隔开了一行的左右，一列的上下。所以把墙考虑成开了新的一行和列，处理每个的新行，新列即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int f[N][N],ans,cnt1=1,cnt2=1,vis[N],ma[N],n,m,a[N][N],T;
char c[N][N];
int dfs(int x){
	for(int i=1;i<=cnt1;i++){
		if(vis[i]||!f[x][i]) continue;
		vis[i]=1;
		if(!ma[i]||dfs(ma[i])){
			ma[i]=x;return 1;
		}
	}
	return 0;
}
int main(){
	cin>>T;
	for(int k=1;k<=T;k++){
		cin>>n>>m;ans=0;cnt2=cnt1=1;
		memset(f,0,sizeof(f));
		memset(ma,0,sizeof(ma));
		memset(a,0,sizeof(a));
	    for(int i=1;i<=n;i++){
	    	for(int j=1;j<=m;j++){
	    		cin>>c[i][j];
				if(c[i][j]=='o'){a[i][j]=cnt1;}
				if(c[i][j]=='#'){cnt1++;}}cnt1++;}
		for(int j=1;j<=m;j++){
			for(int i=1;i<=n;i++){
				if(c[i][j]=='o'){f[cnt2][a[i][j]]=1;}
				if(c[i][j]=='#'){cnt2++;}}cnt2++;}
		for(int i=1;i<=cnt2;i++){
			memset(vis,0,sizeof(vis));
			ans+=dfs(i);
		}
		cout<<"Case :"<<k<<'\n'<<ans<<'\n';
	}
    return 0;
}
```

---

## 作者：20111019Yu (赞：4)

### 题意
有 $nm$ 个节点，有若干个点能放机器，每台机器向上下左右方向延伸只能碰到墙或边界，不能碰到机器。
### 思路
对于没有墙的情况，很明显可以用二分图最大匹配，把每个点的行向列连边。

如果有墙的话，相当于这一列又能放一个，这一行也能多放一个。所以给每两堵墙之间的区间编个号然后再跑最大匹配。

~~我是不会告诉你多测要清空的。~~
### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, t, ans, match[2505], visit[2505], r[55][55], c[55][55];
vector<int> vec[2505];
char ch[55][55];

bool solve(int x, int tag){
	if(visit[x] == tag) return 0;
	visit[x] = tag;
	for( auto &i : vec[x] ){
		if(!match[i] || solve(match[i], tag)){
			match[i] = x;
			return 1;
		}
	}
	return 0;
}

signed main(){
	cin >> t;
	for( int q = 1; q <= t; q++ ){
		ans = 0;
		memset(visit, 0, sizeof(visit));
		memset(r, 0, sizeof(r));
		memset(c, 0, sizeof(c));
		memset(match, 0, sizeof(match));
		printf("Case :%d\n", q);
		cin >> n >> m;
		int cnt1 = 0, cnt2 = 0;
		for( int i = 1; i <= n; i++ ){
			for( int j = 1; j <= m; j++ ){
				cin >> ch[i][j];
			}
		}
		for( int i = 1; i <= n; i++ ){
			for( int j = 1; j <= m; j++ ){
				if(ch[i][j] != '#'){
					if(j == 1 || ch[i][j - 1] == '#') cnt1++;
					r[i][j] = cnt1;
					continue;
				}
			}
		}
		for( int j = 1; j <= m; j++ ){
			for( int i = 1; i <= n; i++ ){
				if(ch[i][j] != '#'){
					if(i == 1 || ch[i - 1][j] == '#') cnt2++;
					c[i][j] = cnt2;
				}
			}
		}
		for( int i = 1; i <= cnt1; i++ ) vec[i].clear();
		for( int i = 1; i <= n; i++ ){
			for( int j = 1; j <= m; j++ ){
				if(ch[i][j] != 'o') continue;
				vec[r[i][j]].push_back(c[i][j]);
			}
		}
		for( int i = 1; i <= cnt1; i++ ){
			if(solve(i, i)) ans++;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：NOI_Winner (赞：3)

看到本题，您可能自然而然的想到了[P10937 車的放置](https://www.luogu.com.cn/problem/P10937)一题，但是本题多了一些条件。我们仍可以从二分图最大匹配的方向去考虑。

先不考虑墙方块，只考虑空地与草方块。我们以每一行作为左部节点，设编号为 $1 \sim n$，每一列作为右部节点，设编号为 $1 \sim m$。若第 $i$ 行第 $j$ 列能放，则将左部节点 $i$ 与右部节点 $j$ 连边，否则不连边。

如果这时再加上墙方块，假设输入数据是这样的：`ooo#oo#ooo`，那么我们可以将这一行拆为三个节点，分别代表第一位至第三位、第五位至第六位、第八位至第十位。同理，每一列也同样拆点。`#` 与 `*` 的位置不连边，`o` 的位置连边，跑一遍匈牙利算法就可以了。

参考代码：
```cpp
#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxn = 50, maxn2 = maxn * maxn, maxm = maxn2 * maxn2;
int head[maxn2 + 5], vert[maxm + 5], nxt[maxm + 5], tot;
int id1[maxn + 5][maxn + 5], id2[maxn + 5][maxn + 5], match[maxn2 + 5];
char a[maxn + 5][maxn + 5];
bool v[maxn2 + 5];

inline void add(int x, int y)
{
	vert[++tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}

bool dfs(int x)                           //  匈牙利算法 
{
	for (int i = head[x]; i; i = nxt[i])
	{
		int y = vert[i];
		if (!v[y])
		{
			v[y] = true;
			if (!match[y] || dfs(match[y]))
			{ match[y] = x; return true; }
		}
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t; cin >> t;
	for (int c = 1; c <= t; c++)
	{
		memset(head, 0, sizeof(head)); tot = 0;
		memset(match, 0, sizeof(match));
		
		int n, m; cin >> n >> m;
		for (int i = 1; i <= n; i++)
			cin >> a[i] + 1;
		
		int cnt1 = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if ('#' != a[i][j])
				{
					cnt1++;
					for (; j <= m && '#' != a[i][j]; j++)
						id1[i][j] = cnt1; 
				}
		int cnt2 = 0;
		for (int j = 1; j <= m; j++)
			for (int i = 1; i <= n; i++)
				if ('#' != a[i][j])
				{
					cnt2++;
					for (; i <= n && '#' != a[i][j]; i++)
						id2[i][j] = cnt2;
				}
		
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if ('o' == a[i][j])
					add(id1[i][j], id2[i][j]);     // o 的位置连边 
		
		int ans = 0;
		for (int i = 1; i <= cnt1; i++)
		{
			memset(v, 0, sizeof(v));
			ans += dfs(i);
		}
		cout << "Case :" << c << endl << ans << endl;
	}
	
	return 0;
}
```

---

## 作者：110821zj_hhx (赞：2)

我们可以处理出所有由墙壁隔开的横竖区间。

对于每一个空地，将其所属的横竖区间连边。那么放置机器人的过程就转化为了选择边。又因为显然一个区间内至多有一个机器人，所以一个点（即一个区间）至多只能选取一条边，所以转化为二分图匹配，匹配数量即是答案。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define int long long
using namespace std;
int t,n,m,hbl[55][55],lbl[55][55],cnt,M[5005],ans;
char c[55][55];
vector<int>s[5005];
bool vis[5005];
bool find(int x){
    for(int i=0;i<s[x].size();i++){
        int y=s[x][i];
        if(vis[y]) continue;
        vis[y]=1;
        if(!M[y]||find(M[y])){
            M[y]=x;
            return true;
        }
    }
    return false;
}
signed main(){
	cin>>t;
	for(int f=1;f<=t;f++){
		cnt=ans=0;
		memset(M,0,sizeof(M));
		memset(hbl,0,sizeof(hbl));
		memset(lbl,0,sizeof(lbl));
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>c[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if((c[i][j]=='*'||c[i][j]=='o')&&!hbl[i][j]){
					int id=++cnt,k=j;
					while(k<=m&&(c[i][k]=='*'||c[i][k]=='o')) hbl[i][k]=id,k++;
				}
			}
		}
		int res=cnt;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if((c[i][j]=='*'||c[i][j]=='o')&&!lbl[i][j]){
					int id=++cnt,k=i;
					while(k<=n&&(c[k][j]=='*'||c[k][j]=='o')) lbl[k][j]=id,k++;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(c[i][j]=='o'){
					s[hbl[i][j]].push_back(lbl[i][j]);
				}
			}
		}
		for(int i=1;i<=res;i++){
			memset(vis,0,sizeof(vis));
			ans+=find(i); 
		}
		for(int i=1;i<=res;i++) s[i].clear();
		cout<<"Case :"<<f<<endl<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：M_CI (赞：2)

### Part 1. 题意

在 $N \times M$ 的矩阵中的**空地**放人机，任一人机上下左右走到**边界或墙**之前遇不到另一人机。

~~我已经尽力写得简短了。。~~

---

### Part 2. 思路

我们先思考无墙的情况。

若无墙，则同[車的放置](https://www.luogu.com.cn/problem/P10937)，把草方块当作禁止放車的方块即可，。

贴一下车的放置的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,t,ans,g[210][210],mat[210];
bool vis[210];

bool match (int u) {
	for (int i=1;i<=m;i++)
		if (!g[u][i]&&!vis[i]) {
			vis[i]=1;
			if (!mat[i]||match (mat[i])) {
				mat[i]=u;
				return 1;
			}
		}
	return 0;
}

int main () {
	cin>> n>> m>> t;
	for (int i=1,x,y;i<=t;i++) {
		cin>> x>> y;
		g[x][y]=1;
	}
	for (int i=1;i<=n;i++) {
		memset (vis,0,sizeof (vis));
		if (match (i))
			ans++;
	}
	cout<< ans;
	return 0;
}
```

而此题多了墙这种阻挡方块，怎么办？

显然，对于每一行和每一列，每多一个墙方块，就可以多放一个人机，如下两图（白色为空地，红色为人机，绿色为草地，棕色为墙）：

![](https://cdn.luogu.com.cn/upload/image_hosting/10vdxrip.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/5xnhpgep.png)

上两例均有 $2$ 面墙与 $3$ 个人机。

所以我们可以对于行的可放人机区域和列的可放人机区域分别计数，将每个空地计算出的行区域数作为左部点，列区域数作为右部点，建立二部图，跑最大匹配即可。

### Part3. 本题代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t=-1,s,n,m,lk,ck,ans,mat[2510],ls[60][60],cs[60][60];
bool vis[2510];
char mp[60][60],buf[1024];
vector<int> g[2510];

bool match (int u) {
	for (int v: g[u])
		if (!vis[v]) {
			vis[v]=1;
			if (!mat[v]||match (mat[v])) {
				mat[v]=u;
				return 1;
			}
		}
	return 0;
}

int main () {
	if (!~t) cin>> t;
	if (!t--) return 0;
	cin>> n>> m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			cin>> mp[i][j];
	lk=ck=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			ls[i][j]=(lk+=(j==1||mp[i][j-1]=='#'));
	for (int j=1;j<=m;j++)
		for (int i=1;i<=n;i++)
			cs[i][j]=(ck+=(i==1||mp[i-1][j]=='#'));
	for (int i=1;i<=lk;i++)
		g[i].clear ();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (mp[i][j]=='o')
				g[ls[i][j]].push_back (cs[i][j]);
	ans=0;
	memset (mat,0,sizeof (mat));
	for (int i=1;i<=lk;i++) {
		memset (vis,0,sizeof (vis));
		ans+=match (i);
	}
	sprintf (buf,"Case :%d\n%d",++s,ans);
	puts (buf);
	return main ();
}
```

---

## 作者：SproutPower (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/P10945)

## 前置知识：

二分图上的最大匹配问题。

## 题意：

先吐槽一下题面，题面里没有写清楚**草方块**上不能放机器人，导致我玩了半天样例才把它搞懂。  
所以建议修改题面。

## 思路：

直接按题面模拟显然极其复杂，所以考虑构造图。  
由此我们便可以简化问题，并通过构造所得的图得到一些原本没有的特殊性质。


## 构造：

我们可以：   
把一个横条看作一个点，放在集合 $S$ 里;  
把一个竖条看作一个点，放在集合 $T$ 里。  
（此处的横条、竖条都只有空格）

然后：  
对于每个空格，必定穿过，且仅穿过**一个**横条和**一个**竖条。  
所以可以把每个空格看作一条边，连接对应的集合 $S、T$ 中的点。

最后可以发现：  
由于集合 $S、T$ 自身内部不可能有边存在，所以我们所构造出的就是一张二分图。  
而题目让我们求的，便是二分图上的最大匹配问题。

如果你不会二分图上的最大匹配问题，请移步[至此](https://www.luogu.com.cn/problem/P3386)。

## 最后都最后：

重要的事情说三遍：  
多测要清空！！！  
多测要清空！！！  
**多测要清空！！！**

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,tot1,tot2;

int a[205][205];
char c[205][205];

struct Row{int l=0,r=0,id=0;}row[114514];
struct Col{int u=0,d=0,id=0;}col[114514];
vector<int> g[114514];
int match[114514];
bool vis[114514];

bool dfs(int u){
    for(auto v:g[u]){
        if(!vis[v]){
            vis[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

void ROW(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]!=2){
                int tmp=j;
                while(a[i][j+1]!=2 && j<m)j++;
                Row t;t.l=tmp,t.r=j,t.id=i;
                row[++tot1]=t;
            }
        
    return ;
}

void COL(){
    for(int j=1;j<=m;j++)
        for(int i=1;i<=n;i++)
            if(a[i][j]!=2){
                int tmp=i;
                while(a[i+1][j]!=2 && i<n)i++;
                Col t;t.u=tmp,t.d=i,t.id=j;
                col[++tot2]=t;
            }
        
    return ;
}

void build(){
    for(int i=1;i<=tot1;i++)
        for(int j=1;j<=tot2;j++)
            if(col[j].id<=row[i].r && col[j].id>=row[i].l && row[i].id<=col[j].d && row[i].id>=col[j].u)
                if(a[row[i].id][col[j].id]!=1)g[i].push_back(j);
          
    return ;
}

void init(){
    memset(vis,0,sizeof vis);
    memset(match,0,sizeof match);
    memset(col,0,sizeof col);
    memset(row,0,sizeof row);
    memset(a,0,sizeof a);
    
    for(int i=1;i<=tot1;i++)g[i].clear();
    tot1=0,tot2=0,ans=0;
    return ;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int TT=1;TT<=T;TT++){
        
init();
    
    
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>c[i][j];
            if(c[i][j]=='o')a[i][j]=0;
            if(c[i][j]=='#')a[i][j]=2;
            if(c[i][j]=='*')a[i][j]=1;
        }

    ROW();
    COL();

// for(int i=1;i<=tot1;i++)printf("%d:[%d,%d~%d]\n",i,row[i].id,row[i].l,row[i].r);printf("\n");
// for(int i=1;i<=tot2;i++)printf("%d:[%d,%d~%d]\n",i,col[i].id,col[i].u,col[i].d);printf("\n");

    build();

// for(int i=1;i<=tot1;i++){
//     printf("%d:",i);
//     for(auto j:g[i])printf("%d ",j);
//     printf("\n");
// }             
    printf("Case :%d \n",TT);
    for(int i=1;i<=tot1;i++)memset(vis,0,sizeof vis),ans+=dfs(i);
    printf("%d\n",ans);
    //for(int i=1;i<=tot2;i++)match[i]?printf("%d %d\n",row[match[i]].id,col[i].id):1;

    
    }
    return 0;
}
/*
2
4 4
o*** 
*### 
oo#o 
***o 
4 4 
#ooo 
o#oo 
oo#o 
***#
*/

```

---

## 作者：naroto2022 (赞：1)

# P10945 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P10945)

### 思路

看到这一题，想到二分图。

但是这题的建图还需要仔细思考一下。

发现这道题的墙就和网格的边界一样，阻挡激光，所以不免可以把一行拆成由墙隔开的多行，一列拆成由墙隔开的多列。

于是我们不妨把可以放置激光的位置的属于拆过之后的行和拆过之后的列连边，由于拆过之后的行和列每一行，每一列都只选一个，所以就可以跑二分图最大匹配即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
//#define gc getchar
#define gc()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define ll long long
using namespace std;
const int MN=55,MM=5e5+5;
ll n,m,h[MN][MN],l[MN][MN],mp[MN][MN],tot,head[MM],y[MM],used[MM],tm,l1,l2,ans;
char buf[1<<23],*p1=buf,*p2=buf;
struct edge{ll to,nxt;}e[MM<<1];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=gc();}return x*f;}
char getc(){char ch=gc();while(ch!='*'&&ch!='o'&&ch!='#')ch=gc();return ch;}
void init(){l1=l2=tm=tot=ans=0;for(int i=1; i<=n*m; i++)head[i]=y[i]=used[i]=0;}
void add(ll u, ll v){e[++tot].nxt=head[u];head[u]=tot;e[tot].to=v;}
bool find(ll u){
    for(int i=head[u]; i; i=e[i].nxt){
        ll v=e[i].to;
        if(used[v]!=tm){
            used[v]=tm;
            if(!y[v]||find(y[v])){
                y[v]=u;
                return true;
            }
        }
    }
    return false;
}
void solve(ll cn){
    putchar('C');putchar('a');putchar('s');putchar('e');putchar(' ');putchar(':');write(cn);putchar('\n');
    n=read();m=read();init();
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++){
        char ch=getc();
        mp[i][j]=ch=='*'?2:ch=='#'?0:1;
    }
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) if(!mp[i][j-1]) h[i][j]=++l1;else h[i][j]=l1;
    for(int j=1; j<=m; j++) for(int i=1; i<=n; i++) if(!mp[i-1][j]) l[i][j]=++l2;else l[i][j]=l2;
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) if(mp[i][j]==1) add(h[i][j],l[i][j]);
    for(int i=1; i<=l1; i++){tm++;ans+=find(i);}
    write(ans);putchar('\n');
}
int main(){
    //ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    ll T=read();for(int i=1; i<=T; i++)solve(i);
    return 0;
}//250525
```

---

## 作者：yedalong (赞：1)

这道题目正解为二分图的最大匹配，若不会匈牙利算法请出门[左转](https://www.luogu.com.cn/problem/P3386)。
## Meaning of the title
有一个方格地图。每个位置只有可能是草方块、墙方块和空地。现在有一些机器人，每个机器人都会向四个方向发射激光。机器人只能放在空地，激光遇到墙方块会被阻挡。现在要找到一种方案，使得放置的机器人尽可能的多，但是机器人不能被其他激光碰到。
## Solution
由于墙方块能够阻挡激光，那么如果我们定义一行为一条激光能射到的地方，那么墙方块其实就是把一行分成了两行。那么我们只需根据墙方块把一行分开，列亦是如此，这样后面的操作就方便了许多。  

如果我们将二分图中左边的点设为行，右边的点设为列。那么我们每一次的匹配就是相当于在一个空地防止一个机器人，那么那个机器人所在的那行那列都被占用了。这时候我们惊人的发现，放置的最大机器人数就是二分图的最大匹配数。  

关于二分图的边，我们该怎么建呢？上文说到，匹配相当于放置机器人，那么能放置机器人的地方就是空地。因此，只需对于每一个空地有行向列建一条边即可。  

## AC code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
int T,n,m,cntx=1,cnty=1,ans,match[2505],cnt;
bool pd[2505];
char mp[55][55];
vector<int> edge[2505];
pair<int,int> a[55][55];
bool dfs(int now){
	if(pd[now]) return 0;
	pd[now]=1;
	for(auto to:edge[now]){
		if(!match[to]|dfs(match[to])){
			match[to]=now;
			return 1;
		}
	}
	return 0;
}
int main(){
	cin>>T;
	while(T--){
		++cnt;
		cntx=ans=cnty=0;
		for(int i = 1;i<=2500;i++) edge[i].clear();
		memset(match,0,sizeof(match));
		cin>>n>>m;
		for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) cin>>mp[i][j];
		for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) if(mp[i][j]=='#') cntx++;else if(j==1) a[i][j].x=++cntx;else a[i][j].x=cntx;
		for(int i = 1;i<=m;i++) for(int j = 1;j<=n;j++) if(mp[j][i]=='#') cnty++;else if(j==1) a[j][i].y=++cnty;else a[j][i].y=cnty;
		for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) if(mp[i][j]=='o') edge[a[i][j].x].push_back(a[i][j].y);
		for(int i = 1;i<=cntx;i++) memset(pd,0,sizeof(pd)),ans+=dfs(i); 
		printf("Case :%d\n%d\n",cnt,ans);
	}
}
```

## Postscript
四倍经验。  
[P6062](https://www.luogu.com.cn/problem/P6062)  
[P2825](https://www.luogu.com.cn/problem/P2825)  
[AT_abc274_g](https://www.luogu.com.cn/problem/AT_abc274_g)

---

## 作者：bssmessi (赞：1)

对于本题，我们都可以想到车的放置（即是放置车使得每个车两两不攻击），此题我们的做法是二分图匹配。

因此本题我们自然而然地就有往这个方面想的思路，但是我们必须要处理墙的这个问题，即使一些机器人同时在一列，但是他们中间却有一堵墙，也不会互相伤害。

所以我们可以将有墙分隔的行或列看成两个独立的个体，我们可以先预处理列，将每列先分块，分别给予每个点（非墙）编号，接着把行分好的块也提供编号与当前点预处理好的列的编号连边即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10010;
int T,m,n,tot1,tot2;
int a[N][N],g[N][N],vis[N],ma[N];
char c[N][N];
bool dfs(int u){
	for(int i=1;i<=tot1;i++){
		if(!a[u][i]||vis[i]) continue;
		vis[i]=1;
		if(!ma[i]||dfs(ma[i])){
			ma[i]=u;
			return 1;
		}
	}
	return 0;
}
int main(){
	cin>>T;
	for(int k=1;k<=T;k++){
		cin>>m>>n;
		memset(ma,0,sizeof(ma));
		memset(a,0,sizeof(a));
		tot1=tot2=0;//多测需要清空数据
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++) cin>>c[i][j];
		}
		for(int j=1;j<=n;j++){//先将列预处理
			tot1++;
			for(int i=1;i<=m;i++){
				if(c[i][j]!='#'){
					g[i][j]=tot1;
				}else tot1++;//如果是墙就把块数增加
			}
		}
		for(int i=1;i<=m;i++){
			tot2++;
			for(int j=1;j<=n;j++){
				if(c[i][j]=='o'){
					a[tot2][g[i][j]]=1;//读取预处理的列的块数与他连边
				}else if(c[i][j]=='#') tot2++;
			}
		}
		int ans=0;
		for(int i=1;i<=tot2;i++){
			memset(vis,0,sizeof(vis));
			ans+=dfs(i);
		}
		cout<<"Case :"<<k<<"\n"<<ans<<"\n";
	}
    return 0;
}
```

---

## 作者：jdfz2251533 (赞：1)

# 题解：P10945 Place the Robots

## 题意

给了一个网格图，每个格子可以是墙、草、空地。现在要在空地格子里面放机器人，机器人可以向所在行、列发射激光，墙可以挡住激光，激光区域不能放机器人，问最多的放置机器人数量，多测。

## 分析与解

先进行图论建模：

分别对每一行、每一列进行拆点，拆分依据是只要遇到墙就拆开，理由就是这一段只能放最多一个机器人。我们把每一段抽象成一个节点，拆分的同时给节点编号。以下称从每一行拆出的节点为行节点，列节点同理。

设 $r_{i,j}$ 表示第 $i$ 行，第 $j$ 列的空地属于的行节点编号，$l_{i,j}$ 表示第 $i$ 行，第 $j$ 列的空地属于的列节点编号。

对于每一个空地格子 $(i,j)$，连一条 $l_{i,j}$ 和 $r_{i,j}$ 之间的**单向边** （可以 $l$ 连 $r$，反过来连也可以），理由是如果这两个节点中任意一个对应的区间放了机器人，这个格子就不能放机器人了。连完所有边后，就得到了一个二分图。

为什么**一定**得到的是二分图？

证明：因为我们总是在行节点和列节点之间连边，但是不在行节点集或列节点集内连边，满足二分图的左右两个点集之间连边、内部不连边的要求，所以一定得到的是二分图。

解决：

不难发现，放置机器人等价于在二分图中找到一条边，使得这条边连接的两个节点（一个行节点和一个列节点）都没有被其他机器人占用。这不就是**增广路**嘛！直接跑二分图最大匹配，最大匹配数就是答案。

注意：

1\. 多测要清空！

2\. 要连单向边！

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int T, n, m, ans, h[N], cnt, vis[N], match[N], r[55][55], l[55][55], tot;
char c[55][55];
struct node {
	int to, nxt;
} e[N];

void add(int u, int v) {
	e[++tot].nxt = h[u];
	e[tot].to = v;
	h[u] = tot;
}

bool dfs(int u) {
	for (int i = h[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (!vis[v]) {
			vis[v] = 1;
			if (!match[v] || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main() {
	cin >> T;
	for (int _ = 1; _ <= T; _++) {
		cin >> n >> m;
		memset(e, 0, sizeof(e));
		memset(h, 0, sizeof(h));
		memset(match, 0, sizeof(match));
		memset(vis, 0, sizeof(vis));
		ans = 0;
		tot = 0;
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> c[i][j];
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (c[i][j] != '#') {
					if (j == 1 || c[i][j - 1] == '#') {
						cnt++;
					}
					r[i][j] = cnt;
				}
			}
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (c[j][i] != '#') {
					if (j == 1 || c[j - 1][i] == '#') {
						cnt++;
					}
					l[j][i] = cnt;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (c[i][j] == 'o') {
					add(l[i][j], r[i][j]);
				}
			}
		}
		for (int i = 1; i <= cnt; i++) {
			if (dfs(i)) {
				ans++;
			}
			memset(vis, 0, sizeof(vis));
		}
		cout << "Case :" << _ << endl << ans << endl;
	}
	return 0;
}
```

## 后记 && 双倍经验

其实这道题和 [P2825](https://www.luogu.com.cn/problem/P2825) 几乎一样，唯一的区别在于多测和对“墙” 表示方法不同。

---

## 作者：DrDuck (赞：0)

### 前置芝士：二分图
有点像 [P10937](https://www.luogu.com.cn/problem/P10937) 的升级版。

这道题让我们求地图上最多能放置几个机器人，使它们不会互相攻击。

对于地图上的每一个点，它要么被横向发射的激光所覆盖，要么被纵向发射的激光所覆盖（当然也有可能被同时覆盖）。由于机器人不能互相伤害，对于一个点而言，它不能同时被两条横向激光覆盖，也不能被两条纵向激光覆盖，只能被一条横向激光和一条纵向激光覆盖。我们把点抽象成一条边，把每条连续的空地或草方块看作点，每条边只能和一个横着的点和一个竖着的点发生关系。也就是说，把横向的连续空地或草方块看作左侧点，把纵向的连续空地或草方块看作右侧点，把空地抽象成一条边，构成的是一个二分图，机器人可以放置在边上，想让机器人个数最多，跑二分图最大匹配即可。
# CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1200;
int t, n, m, htot, stot;
int belh[maxn][maxn], bels[maxn][maxn], vis[maxn], mch[maxn];
char ditu[maxn][maxn];
vector<int> v[maxn];
void init()
{
    htot = stot = 0;
    memset(belh, 0, sizeof(belh));
    memset(bels, 0, sizeof(bels));
    memset(vis, 0, sizeof(vis));
    memset(mch, 0, sizeof(mch));
    for (int i = 1; i <= maxn - 5; i++)
    {
        v[i].clear();
    }
}
bool dfs(const int me, int ano)
{
    if (vis[ano] == me)
    {
        return false;
    }
    vis[ano] = me;
    for (int i : v[ano])
    {
        if (!mch[i] || dfs(me, mch[i]))
        {
            mch[i] = ano;
            return true;
        }
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    int man = 0;
    while (t--)
    {
        man++;
        cin >> n >> m;
        init();
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> ditu[i][j];
            }
        }
        for (int i = 1; i <= n; i++)
        {
            bool flag = false;
            for (int j = 1; j <= m; j++)
            {
                if (ditu[i][j] == '#' && flag)
                {
                    flag = false;
                }
                if (ditu[i][j] == 'o')
                {
                    if (!flag)
                    {
                        flag = true;
                        htot++;
                    }
                    belh[i][j] = htot;
                }
            }
        }
        for (int j = 1; j <= m; j++)
        {
            bool flag = false;
            for (int i = 1; i <= n; i++)
            {
                if (ditu[i][j] == '#' && flag)
                {
                    flag = false;
                }
                if (ditu[i][j] == 'o')
                {
                    if (!flag)
                    {
                        flag = true;
                        stot++;
                    }
                    bels[i][j] = stot;
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (ditu[i][j] == 'o')
                {
                    v[belh[i][j]].push_back(bels[i][j]);
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= htot; i++)
        {
            if (dfs(i, i))
            {
                ans++;
            }
        }
        cout << "Case :" << man << '\n';
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：junee (赞：0)

# P10945 Place the Robots 题解

## 前置知识

二分图。

## 题目分析

NOIP 前写题解涨 rp。

猜你想要：[P2825 [HEOI2016/TJOI2016] 游戏](https://www.luogu.com.cn/problem/P2825)。

经典的行列匹配，由于存在墙可以阻断一个行或者列，我们把行和列的一段一段拿出来匹配。

具体的，我们墙会影响行列分布，草方块不会影响行列分布，但是不建边，空地不会影响行列分布。

## Code

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
const int N=100,M=1e5+10;
int T,n,m,cnt;
int a[N][N],id1[N][N],id2[N][N];
int h[M],e[M],ne[M],idx;
int st[M],match[M];
void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
bool dfs(int u){
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(st[j])continue;
		st[j]=1;
		if(!match[j]||dfs(match[j])){
			match[j]=u;
			return 1;
		}
	}
	return 0;
}
void clear(){
	memset(h,-1,sizeof h);idx=cnt=0;
	memset(id1,0,sizeof id1);
	memset(id2,0,sizeof id2);
	memset(match,0,sizeof match);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	for(int t=1;t<=T;t++){
		clear();
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char x;cin>>x;
				if(x=='#')a[i][j]=2;
				else if(x=='*')a[i][j]=1;
				else a[i][j]=0;
			}
		}
		for(int i=1;i<=n;i++){
			cnt++; 
			for(int j=1;j<=m;j++){
				if(a[i][j]==2)cnt++;
				else id1[i][j]=cnt;
			}
		}
		int lcnt=cnt,ans=0;
		for(int i=1;i<=m;i++){
			cnt++; 
			for(int j=1;j<=n;j++){
				if(a[j][i]==2)cnt++;
				else id2[j][i]=cnt;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(!a[i][j])add(id1[i][j],id2[i][j]);
			}
		}
		for(int i=1;i<=lcnt;i++){
			memset(st,0,sizeof st);
			if(dfs(i))ans++;
		}
		cout<<"Case :"<<t<<'\n';
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：Kingna (赞：0)

以 P2825 作为题目和代码参照标准。

如果没有硬石头，那么在 $(i,j)$ 放个炸弹，可以将第 $j$ 列和第 $i$ 行全部炸完。也就可以对于 $(i,j)$，连边 $i$ 和 $j$，跑最大匹配即可。

现在有了硬石头，那么这一列和这一行就不能全部炸完。但是发现，能炸的区域一定是行的一小段，列的一小段。所以我们以 `#` 为分界线，重新把列和行分裂出来即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

const int N = 55 + 5, mod = 998244353;

int n, m, row[N][N], lin[N][N], tot, match[N * N], vis[N * N];
char a[N][N];

vector<int> G[N * N];

int solve(int u, int tag) {
	if (vis[u] == tag) return 0;
	vis[u] = tag;
	for (auto v : G[u]) {
		if (!match[v] || solve(match[v], tag)) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}

signed main() {
	cin >> n >> m;
	_for(i, 1, n) _for(j, 1, m) cin >> a[i][j];
	_for(i, 1, n) {
		_for(j, 1, m) {
			if (a[i][j] == '#') continue;
			if (j == 1 || a[i][j - 1] == '#') tot++;
			row[i][j] = tot;
		}
	}
	_for(i, 1, m) {
		_for(j, 1, n) {
			if (a[j][i] == '#') continue;
			if (j == 1 || a[j - 1][i] == '#') tot++;
			lin[j][i] = tot;
		}
	}
	_for(i, 1, n) _for(j, 1, m) {
		if (a[i][j] == '*') G[row[i][j]].push_back(lin[i][j]);
	}
	int res = 0;
	_for(i, 1, tot) res += solve(i, i);
	cout << res << endl;
}
```

---

## 作者：Genius_Star (赞：0)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18386806)

### 思路：

先说一下没有墙怎么办，那么当一个位置放了机器人之后，这个机器人所在的行和列是不能继续放置的。

那么发现行和列几乎是独立的，考虑建二分图，若 $(i,j)$ 能放一个机器人，那么给 $i \to j$ 建一条边。

那么答案就是这个二分图的最大匹配，这样每个匹配的就代表着一个机器人所放的位置。

现在再考虑有墙的情况，有墙时，机器人所放的激光无法穿透过去，则在墙另外一边依旧可能可以放置机器人。

发现墙就是把行或列分为了几个部分，每个部分互不干扰，则考虑每遇到墙，就新起一行表示当前位置到下一个墙或者这一行的末尾的放块；列同理。

直接跑匈牙利算法即可。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const ll N=2505;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
inline char get(){
    char c;
    while((c=getchar())!='*'&&c!='o'&&c!='#');
    return c;
}
ll T,n,m,cnt,id,ans,s1,s2;
ll a[N],f[N];
ll h[N][N];
char s[N][N];
vector<ll> E[N];
void add(ll u,ll v){
	E[u].push_back(v);
}
bool dfs(ll u){
	for(auto v:E[u]){
		if(f[v]==id)
		  continue;
		f[v]=id;
		if(!a[v]||dfs(a[v])){
			a[v]=u;
			return 1;
		}
	}
	return 0;
}
void Match(){
    memset(f,0,sizeof(f));
    memset(a,0,sizeof(a));
	for(int i=1;i<=s1;i++){
		id=i;
		if(dfs(i))
		  ans++;
	}
}
void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
		s[i][j]=get();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='#')
			  continue;
			if(s[i][j-1]=='#'||j==1)
			  ++s1;
			h[i][j]=s1;
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(s[i][j]=='#')
			  continue;
			if(s[i-1][j]=='#'||i==1)
			  ++s2;
			if(h[i][j]&&s[i][j]=='o')
			  add(h[i][j],s2);	
		}
	}
	Match();
    printf("Case :%lld\n",++cnt);
	write(ans);
    putchar('\n');
    For(i,1,max(s1,s2))
      E[i].clear();
    s1=s2=ans=0;
}
int main(){
    T=read();
    while(T--)
      solve();
	return 0;
}
```

---

