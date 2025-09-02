# Lights

## 题目描述

In the end of the day, Anna needs to turn off the lights in the office. There are $ n $ lights and $ n $ light switches, but their operation scheme is really strange. The switch $ i $ changes the state of light $ i $ , but it also changes the state of some other light $ a_i $ (change the state means that if the light was on, it goes off and vice versa).

Help Anna to turn all the lights off using minimal number of switches, or say it is impossible.

## 样例 #1

### 输入

```
8
5
11101
4 3 4 2 2
2
10
2 1
10
0000000011
9 10 10 7 10 9 9 9 10 2
10
1000111101
9 3 8 9 2 1 3 7 2 7
10
0001101010
5 7 6 10 8 3 6 6 2 2
10
0101100010
8 7 7 9 9 4 1 4 2 7
10
1010111010
7 9 10 7 7 2 8 6 10 4
10
1110000001
3 10 10 1 10 8 6 3 2 1```

### 输出

```
3
1 5 3 
-1
1
9 
5
5 6 10 2 3 
6
4 9 5 10 8 7 
3
5 4 9 
6
1 3 5 9 7 8 
2
2 1```

# 题解

## 作者：jr_inf (赞：12)

每次按一个开关就会改变两盏灯的状态，考虑把这种关系在一张图上表示出来。在图上把所有可能同时改变状态的灯连边，让亮灯的点的值为 $1$，不亮的为 $0$，那么每次按灯就是把连接一条边的两点的值都异或上 $1$，最终要让所有点的值都为 $0$。

由于每个点的度都大于 $1$ 且图上共有 $n$ 个点和 $n$ 条边，发现这是一个基环树森林。对每棵基环树单独考虑，对于不在环上的边组成的若干条链，先贪心地尝试消除链上值为 $1$ 的点，如果还有剩余，就转移到环上消除。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lle1kmyu.png)

其中 $1,2,3,5$ 的值为 $1$。

这里有两种方案：

1. $1-2,3-5$
1. $1-5,2-3$

两种方案的路径在环上交替出现，选择一种更优的即可。

实现方面，由于每次只能同时消两个点，如果值为 $1$ 的点有奇数个，那么无解。对于有解的情况，先用拓扑排序找链，由于点在链上，所以只会遇到一个还未更新的点。如果当前点值为 $1$，就向下一个点转移。然后对于每个环，把两种方案所对应的边和代价都记录下来，选取更优的即可。

时间复杂度 $O(n)$，有些常数。

---

## 作者：_Ink (赞：6)

##  题解

我们把原问题转化为图上问题，第 $i$ 个灯会影响 $a_i$ 灯的状态，于是可以建立一条 $i$ 指向 $a_i$ 的有向边表示关系。

这时候我们发现，对于图中入度为 0 的点，没有其它点能影响它，我们只能选择是否改变这些点的状态，并把其产生的影响传递给下一个点。

遍历过的入度为 0 的点我们势必不会再去考虑它。于是很合理的想法就是用拓扑排序，一步步将能删的点删掉并统计贡献。拓扑到最后，图中就剩下了数个环。

如何处理环呢？不难发现，环上两个颜色为 1 的点可以两两相消，其产生的贡献即是由一个点走到另一个点的距离。显然，我们选择图上相邻的两个颜色为 1 的点相消是最优的，且环上颜色为 1 的点的数目必须为偶数，否则就只能输出 '-1'。

于是对于一个环，我们可以把环上的颜色为 1 的点顺次编号，奇数编号与偶数编号的点可以互消，且有“奇消偶”和“偶消奇”两种方案。我们可以把这两种方案的贡献都统计下来，最后再选择和更小的作为消去方案即可。

实现贡献统计也非常简单。实际上，两种方案所经过的路径在环上是交替出现的，所以我们也只需要顺次统计两个标点间的路径长度，然后将其交替加入两种方案即可。

## $\text{Code:}$

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define maxn 200050
#define maxm 200050 
#define vi vector <int>
#define vvi vector <vi>
#define endl '\n'
#define ll long long
using namespace std;

int n; 
int idg[maxn];
bool tag[maxn];
queue <int> q;

void clean()
{
	memset(idg, 0, sizeof(int)*(n + 5));
	memset(tag, false, sizeof(bool)*(n + 5));
}

void solve()
{
	cin >> n;
	vi a(n + 1);
	clean();
	for(int i = 1; i <= n; i ++){
		char ch; cin >> ch;
		tag[i] = ch - '0';
	}
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		idg[a[i]] ++;
	}
	for(int i = 1; i <= n; i ++){
		if(idg[i] == 0) q.push(i);
	}
	vi ans;
   //拓扑排序
	while(q.size()){
		int x = q.front(); q.pop();
		int y = a[x];
		idg[y] --;
		if(tag[x]) tag[y] = !tag[y];
		if(idg[y] == 0) q.push(y);
		if(tag[x]) tag[x] = false, ans.emplace_back(x);
	}
   //以下为处理环
	for(int i = 1; i <= n; i ++){
		if(idg[i] && tag[i]){ //在环上且为 1
			vi ansa, ansb;
			int nw = i;
			bool flag = false; //flag 作为交替统计的标记
			do{
				idg[nw] --;
				if(tag[nw]) flag = !flag;
				if(flag) ansa.emplace_back(nw);
				else ansb.emplace_back(nw);
				nw = a[nw];
			}while(idg[nw]);
			if(flag) {cout << -1 << endl; return;}
			if(ansa.size() < ansb.size()) //选择更小的方案加入答案
				ans.insert(ans.end(), ansa.begin(), ansa.end());
			else 
				ans.insert(ans.end(), ansb.begin(), ansb.end());
		}
	}
	cout << ans.size() << endl;
	for(int e : ans) cout << e << ' ';
	cout << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); //cout.tie(0);
	
	int t = 1;
	cin >> t; 
	while(t --) solve();
	
	return 0;
}
```

---

## 作者：banned_gutongxing (赞：2)

## 思路分析
如果我们把每一个关系都转化为一条无向边，则 $n$ 个点会有 $n$ 条边，并且每一个点的度数至少是 $1$，所以是一颗基环树森林。我们分别看看每一个数。

一棵树一定会有一个环，首先环外树的决策方案是一定的，一定是将每一个权值为 $1$ 的点上传到祖先上面，使得它们被一起消掉，最后上传到环上就行。

紧接着就是处理在环上的点就行。假设环上权值为 $1$ 的点的编号为：$a_1,a_2,\dots,a_n$。
1. 若 $n\nmid2$\
此时在环上的点不管怎样都不可能两两消掉。
2. 若 $n\mid2$\
此时我们有两种选择：
   + $a_1\Leftrightarrow a_2,a_3\Leftrightarrow a_4,\dots,a_{n-1}\Leftrightarrow a_n$。
   + $a_2\Leftrightarrow a_3,a_4\Leftrightarrow a_5,\dots,a_n\Leftrightarrow a_1$。\
我们只需要在这两种取最有情况就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma G++ optimize(1)
#pragma G++ optimize(2)
#pragma G++ optimize(3)
void read(int &x){
	x = 0;int p = 1;char ch;
	do{
		ch = getchar();
		if(ch=='-') p = -1;
	}while(!isdigit(ch));
	while(isdigit(ch)){
		x*=10;
		x+=ch-'0';
		ch = getchar();
	}
	x*=p;
}
void read(char &x){
    x = getchar();
    while(x==' '||x=='\n'||x=='\r') x = getchar();
}
void write(char x){
    putchar(x);
}
void write(int k){
	if(k<0) putchar('-');
	k = abs(k);
	stack<int> num;
	do{
		num.push(k%10);
		k/=10;
	}while(k);
	while(!num.empty()){
		putchar(num.top()+48);
        num.pop();
	}
}
const int MAXN = 2e5+10;
int T,n,loop1[MAXN],loop2[MAXN],floop1[MAXN],floop2[MAXN];
//graph
struct graph{
    struct EDGE{int x,y,nxt,from;}edge[MAXN];
    int h[MAXN],cnt;
    void new_edge(int x,int y,int from){
        edge[++cnt] = {x,y,h[x],from};
        h[x] = cnt;
    }
}v,tree;
//Topo
int inde[MAXN];
bitset<MAXN> loop,is;
void Topo(){
    queue<int> topo;
    for(int i = 1;i<=n;i++) if(!inde[i]) topo.push(i);
    while(!topo.empty()){
		int tmp = topo.front();topo.pop();loop[tmp] = 0;
		for(int pppi=v.h[tmp],i;pppi,i=v.edge[pppi].y;pppi=v.edge[pppi].nxt) 
			if(!(--inde[i])) topo.push(i);
	}
//	cout << loop[1] << " " << loop[2] << " " << loop[3] << " " << loop[4] << " " << loop[5] << endl;
}
void new_graph(){
    for(int i = 1;i<=n;i++){
        for(int pppj = v.h[i];pppj;pppj = v.edge[pppj].nxt){
            int j = v.edge[pppj].y;
            if(!loop[j]) tree.new_edge(i,j,v.edge[pppj].from);
            else if(!loop1[i]) loop1[i]=j,floop1[i]=v.edge[pppj].from;
            else loop2[i] = j,floop2[i]=v.edge[pppj].from;
        }
    }
}
//DP
vector<int> ans;
int dfs(int k,int fath){
    int sum = is[k];
    for(int pppp = tree.h[k];pppp;pppp = tree.edge[pppp].nxt){
        int i = tree.edge[pppp].y;
        if(i==fath) continue;
        int p = dfs(i,k);
        sum += p;
        if(p) ans.push_back(tree.edge[pppp].from);
    }
    return sum%2;
}
bitset<MAXN> vis;
int dfs_loop(int k,int from,int fath,vector<int> &ans){
    int sum = is[k];vis[k] = 1;int q = 0;
	if(k==from) return sum;
    if(loop1[k]!=fath){
		q++;
        int p = dfs_loop(loop1[k],from,k,ans);
        sum += p;
        if(p) ans.push_back(floop1[k]);
    }else if(loop2[k]!=fath){
		q++;
        int p = dfs_loop(loop2[k],from,k,ans);
        sum += p;
        if(p) ans.push_back(floop2[k]);
    }
	if(!q){
		int p = dfs_loop(loop1[k],from,k,ans);
		sum += p;
		if(p) ans.push_back(floop1[k]);
	}
    return sum%2;
}
//Normal
void clear(){
    vis.reset();loop.reset();ans.clear();
    v.cnt = tree.cnt = 0;
    for(int i = 1;i<=n;i++){
		v.h[i] = 0;tree.h[i] = 0;
        inde[i] = 0;
        loop[i] = 1;
        loop1[i] = 0;
        loop2[i] = 0;
		floop1[i] = 0;
		floop2[i] = 0;
    }
}
signed main(){
    read(T);
    while(T--){
//		if(T==9888){
//			cin >> n;cout << n;
//			string x;
//			cin >> x;cout << x << endl;
//			for(int i = 1;i<=n;i++){
//				int x;
//				cin >>x ;
//				cout << x << " ";
//			}
//			return 0;
//		}
		read(n);
		clear();
        for(int i = 1;i<=n;i++){
            char k;
            read(k);
            is.set(i,k-'0');
        }
        for(int i = 1;i<=n;i++){
            int x;
            read(x);
			inde[x]++;
            v.new_edge(i,x,i);
            v.new_edge(x,i,i);
        }
        Topo();new_graph();
//		for(int pppp = tree.h[9],i;pppp,i=tree.edge[pppp].y;pppp=tree.edge[pppp].nxt) cout << i << endl;
        for(int i = 1;i<=n;i++){
            if(loop[i]){
                int sum = is[i];
                for(int pppj=tree.h[i],j;pppj,j=tree.edge[pppj].y;pppj=tree.edge[pppj].nxt){
                    int p = dfs(j,i);
                    sum += p;
                    if(p) ans.push_back(tree.edge[pppj].from);
                }
                is.set(i,sum%2);
            }
        }
		bool fg = 1;
        for(int i = 1;i<=n;i++){
            if(loop[i]&&!vis[i]&&is[i]){
                vector<int> ans1,ans2;
                int k = dfs_loop(loop1[i],i,i,ans1);
                dfs_loop(loop2[i],i,i,ans2);
				if(k&1) fg  = 0;
                if(ans1.size()>ans2.size()) swap(ans1,ans2);
                for(int i:ans1) ans.push_back(i);
            }
        }
		if(fg){
        write((int)ans.size());write('\n');
        for(int i:ans) write(i),write(' ');
        write('\n');
		}else puts("-1");
    }
    return 0;
}
```

---

## 作者：SnowTrace (赞：2)

DIV3G 写了将近两个小时，我自裁。

以下仅仅介绍我的思维流程（实际上我翻了翻别人的代码好像和我做法都不一样）。

(后来又看了别人的题解好像是我实现的比较差)

我先考虑了其他点不变，只改变一个点的状态的代价。

然后我发现必然不可能只改变一个点状态。

所以接下来我考虑：其他点不变，让两个不同的点改变状态的代价。

然后发现如果有一步的操作的话就直接做，否则就是多次操作，每次把一个改变的抵消，换成另一个。

发现这个等价于 $i$ 和 $a_i$ 连边后图上的一条路径，也就是说，如果我们想要其他点状态不变，只改变两个点 $i$ 和 $j$ 的状态的代价是图上 $i$ 到 $j$ 的最短路长度。

比较显然的是这一张图是一个基环森林。

于是变成了下面这个问题：

给定 $2n$ 个点，你需要把它们两两配对，设配对后为 $(x_1,y_1),(x_2,y_2),
\dots ,(x_n,y_n)$，需要最小化 $\sum_{i = 1}^{n} dis(x_i,y_i)$ 的值。

我们考虑把基环树拆成几颗树连在环上的形态，考虑里面每一颗树：

显然我们尽量要在树的内部匹配，如果匹配不了再放到环上去匹配。

我们显然想让每个点在尽量深的位置匹配，考虑以下算法：

我们从深到浅考虑，如果在某个位置上有很多个点就两两配对，没配对上的点就跳到它的 $fa$（根节点不跳），同时使答案加一。

正确性证明考虑反证法，显然每个点都能取到它能匹配到的最深的点。

然后最后每颗树根节点位置上可能会剩下一些点，然后看成一个环，在环上匹配一下，只有两种情况，分类取最小值即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<pair<int,int>,int>mp;
//记录边的编号。
int n;
char s[200005];int t;
int a[200005];
vector<int>p[200005];
int cnt[200005],fa[200005],vis[200005],in[200005],ok[200005],dfn[200005];
//cnt是代表这个位置上有没有待匹配的点，in是是否在环上
int nw = 0,nww =0 ;
vector<int>ans;
vector<int>cycle[200005];
//记录的是联通块i内环所在的点的集合。
void dfs1(int now,int f){
//基环树找环的板子。
	dfn[now] = ++nww;
	for(int i = 0;i<p[now].size();i++){
		if(p[now][i] == fa[now])continue;
		if(dfn[p[now][i]]){
			if(dfn[p[now][i]]<dfn[now])continue;
			cycle[nw].push_back(p[now][i]);in[p[now][i]] = 1;
			int v = p[now][i];
			for(;v!=now;v = fa[v])cycle[nw].push_back(fa[v]),in[fa[v]] = 1;
		}else fa[p[now][i]] = now,dfs1(p[now][i],now);
	}
}
void dfs2(int now,int f){
	fa[now] = f;
	for(int i =0;i<p[now].size();i++){
		if(p[now][i]!= f and in[p[now][i]]!=1){
			dfs2(p[now][i],now);
		}
	}cnt[now]%=2;
	if(now!=f and cnt[now]){
		cnt[f]++;ans.push_back({mp[{now,f}]});
	}
	return;
}
void solve(int id){
	cin >> n;
	for(int i = 1;i<=n;i++)cin>> s[i];
	for(int  i= 1;i<=n;i++)cin >> a[i];
	nw = 0;nww = 0;ans.clear();mp.clear();
	for(int i = 1;i<=n;i++){
		p[i].clear();vis[i] =0 ,in[i] = 0;cycle[i].clear();cnt[i] = 0;ok[i] = 0;dfn[i] =0 ;fa[i] = 0;
	}for(int i = 1;i<=n;i++){
		if(s[i] == '1')cnt[i] = 1;
	}for(int i = 1;i<=n;i++){
		p[i].push_back(a[i]),p[a[i]].push_back(i);
		mp[{a[i],i}] = mp[{i,a[i]}] = i;
	}for(int i = 1;i<=n;i++){
		if(vis[i] ==0){
			++nw;dfs1(i,i);
		}//基环树找环。
	}for(int i = 1;i<=n;i++){
		if(in[i] == 1){
			dfs2(i,i);
		}//树上做贪心。
	}for(int i = 1;i<=nw;i++){
		int f = n;
		if(cycle[i].size() == 0)continue;
		int tot =0 ,last =0,sum =0 ;
		for(int j =0;j<cycle[i].size();j++){
			if(cnt[cycle[i][j]]){f = min(f,j);
				if(tot%2 == 0)last = j;
				else sum+=j-last;
				tot++;
			} 
		}if(tot ==0 )continue;
		int sz = cycle[i].size();
		for(int j =0;j<=f;j++)cycle[i].push_back(cycle[i][j]);
		if(tot%2 == 1){
			cout << -1 << endl;return;
		}tot =0 ,last = 0;
		for(int j = (f+1)*((long long)sz-sum<sum);j<cycle[i].size();j+=1){
			if(cnt[cycle[i][j]]){
				if(tot%2 == 0)last = j;
				else{
					for(int k = last;k<j;k++){
						ans.push_back(mp[{cycle[i][k],cycle[i][k+1]}]);
					}
				}tot++;
			}
		}//使用一些小技巧处理了环使得不需要讨论。
	}cout << ans.size() << endl;
	for(int x:ans)cout << x << " ";cout << endl;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(int i = 1;i<=t;i++){
		solve(i);
	}
	return 0;
}
```

希望你能看懂我的思路，不指望你能看懂我的代码。

UPD：我急了啊这题才 2200？？？


---

## 作者：_segmenttree (赞：1)

从 $i$ 到 $a_i$ 建一条有向边，每次按灯就是将一条边连接的两个点异或上一。由于每个点只有一条出边，建出来的图肯定是一棵基环树。先跑拓扑排序将链上的灯全关上，将所有开的灯转移到环上。

因为环上每次只能同时消两个点，如果的未关灯点有奇数个，那么无解。环上的点肯定是跟它相邻的两个点之一连边。如果隔了点关灯的话（图中绿边），会有一段被按了多次，答案肯定比图中橙色一段大。所以我们从两个相邻的点出发各跑一遍 dfs 求出答案，最后再跑一遍统计路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/tjl3ziit.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（打红勾的是开的灯，橙色是一种关灯路径，黄色是另外一种）


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10; 
int n,rd[N],s[N],a[N],cnt,ans[N],jl1[N],jl2[N];
char ch;
queue<int>q;
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) rd[i]=0;
	for(int i=1;i<=cnt;i++) ans[i]=0;
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++) {
		cin>>ch;
		s[i]=ch-'0'; 
	}
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		rd[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	    if(rd[i]==0) q.push(i);
	cnt=0;
	while(!q.empty()) {
		int x=q.front();
		q.pop();
		if(s[x]==1) {
			ans[++cnt]=x;
			s[x]^=1,s[a[x]]^=1;
		}
		rd[a[x]]--;
		if(rd[a[x]]==0) q.push(a[x]);
	}
	for(int i=1;i<=n;i++) {
		if(rd[i]==0||s[i]==0) continue ;
		int x=i,len1=0,len2=0,f=0;
		while(rd[x]) {
			rd[x]--;
			if(s[x]) f^=1;
			if(f) jl1[++len1]=x;//从i开始 
			else jl2[++len2]=x;//不从i开始 
			x=a[x];
		}
		if(f) {//奇数个 
			cout<<"-1\n";
			return ;
		}
		if(len1<len2) for(int i=1;i<=len1;i++) ans[++cnt]=jl1[i];
		else for(int i=1;i<=len2;i++) ans[++cnt]=jl2[i]; 
	} 
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++) cout<<ans[i]<<" ";
	cout<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}

```

---

## 作者：OrientDragon (赞：1)

# 题目
[题目传送门](https://www.luogu.com.cn/problem/CF1907G)
# 分析
定义 $st_i$ 表示第 $i$ 盏灯的状态（$st_i=1$ 表示开，$st_i=0$ 表示关）。考虑对第 $i$ 盏灯的单次操作，实质上是改变了 $st_i$ 和 $st_{a_i}$ 的状态。我们不难想到从结点 $i$ 引一条指向 $a_i$ 的边，此时图的边数与点数相等，而对于每一个结点 $i$ 只会从它引一条边，但有可能有多条边引向它，故**原图是一个内向基环树森林。**

此时我们再次考虑原先的操作，就是选择一个结点改变它和它的后继结点的状态。不难发现：

>对于每一棵基环树，一定存在一种方案能使得它所有的不在环上的结点关灯。

~~读者自证不难；~~ 其实就是按照拓扑排序的顺序，将所有不在环上的结点遍历；当发现当前结点亮着的时候，就改变它和它的后继结点的状态，最后~~把所有锅都甩给环~~只剩下环需要处理。

接下来考虑处理每个环。由于每次操作会改变两个结点的状态，所以**某条环不能关灯当且仅当其上有奇数个亮灯结点。**

我们思考若某个结点是亮着的，那么它只能被它自己或它的某个前驱结点关掉，所以：**当现在只剩环时，环上某个结点若仍然亮着，那么它和它的前驱结点中一定有且仅有一个要改变状态** 。

设某个环有 $cnt$ 个结点，我们可以从其上任一结点 $x$ 开始，枚举 $x$ 改变/不改变状态时，关闭环上所有灯的最小次数；发现 $x$ **改变/不改变状态的边集正好将环的边集分成两部分**，所以可以只遍历一回（设 $x$ 改变状态时需要改变 $res$ 个结点关掉所有灯）。最后比较 $res$ 和 $cnt-res$ 的大小，取较小值更新答案。

求 $res$ 的过程一般考虑 dp 求解，但是如果按序遍历环的话，某结点的前驱结点关不关灯已经确定了，所以**遍历到某亮灯结点时，贪心使其改变状态。**

**（注意：这里处理环的时候一定要遍历整张图，因为这张图是一个基环树森林而非一棵基环树！！！~~我因为这个 WA 了 3 次~~）**

# 实现
可以说是 CF-Round $1907$ 里面唯一一道码量有点多的题（


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read(){int x=0,f=1;char ch=getchar();while(ch<48||ch>57){if(ch==45)f=-1;ch=getchar();}while(ch>=48&&ch<=57){x=x*10+(ch^48);ch=getchar();}return x*f;}
void write(int x){if(x<0){putchar(45);write(-x);return;}if(x>9)write(x/10);putchar(x%10^48);}

const int N=200005;
int T,n,i,now,a[N],deg[N];
bool st[N];
queue<int>q;
vector<int>v;

void solve(){
	n=read();
	v.clear();
	memset(deg,0,sizeof deg);
	while(!q.empty())q.pop();
	int i=1,ans=0;
	char ch=getchar();
	while(ch!='0'&&ch!='1')ch=getchar();
	while(ch=='0'||ch=='1'){
		st[i++]=ch^48;
		ch=getchar();
	}
	for(i=1;i<=n;i++){
		a[i]=read();
		deg[a[i]]++;
	}
	for(i=1;i<=n;i++)
		if(!deg[i])q.push(i);
	while(!q.empty()){ // 拓扑排序 
		int u=q.front();
		q.pop();
		if(st[u]){
			v.push_back(u);
			ans++;
			st[u]=0;
			st[a[u]]^=1;
		}
		--deg[a[u]];
		if(!deg[a[u]])q.push(a[u]);
	} // 现在只有环需要处理 
	int flag=0;
	for(int i=1;i<=n;i++) // 遍历整张图（没遍历挂了 3 次） 
        if(deg[i]){ // 选择环上一点 
            q.push(i);
            vector<int>tmp;
            int cnt=0,t=0,res=0;
            while(!q.empty()){
                int u=q.front();
                q.pop();
                tmp.push_back(u);
                deg[u]=0; // 避免重复遍历一个环 
                if(st[u])t^=1;
                res+=t;
                if(deg[a[u]])q.push(a[u]);
            }
            if(t){flag=1;break;} // t 是 cnt 的奇偶 
            if(flag)break;
            cnt=tmp.size(),t=0;
            if(res<cnt-res) // 更新答案 
				for(auto x: tmp){
                    if(st[x])t^=1;
                    if(t)v.push_back(x);
                }
            else
				for(auto x: tmp){
                    if(st[x])t^=1;
                    if(!t)v.push_back(x);
                }
        }
    if(!flag){
        write(v.size()),puts("");
        for(auto x:v)write(x),putchar(' ');
        puts("");
    }else puts("-1");
}
// 码量很大的水题
signed main(){
	T=read();
	while(T--)solve();
}
```

---

## 作者：Fa_Nanf1204 (赞：1)

### 分析：
首先观察到一个开关可以控制两个灯，那么考虑将这两个灯连边，之后形成一张图，我们来讨论图上的情况。

图上如果形成了环，那么亮着的灯是奇数个定然无解，如果不是，我们再分别讨论环的起点（随便选一个环上的点），是选关还是不关，取最优的。

如果没有环，那就正常跑拓扑，亮着的灯定然要关掉，贪心去取就可以。

最后将以上的情况分别处理就是正解了。
```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int T,n,a[N],in[N];
queue<int> q;
int ans[N],len=0;
int ans1[N],len1,ans2[N],len2;
bool vis[N];
int main(){ 
	cin>>T;
	while(T--){
		len=0;
		memset(in,0,sizeof in);
		cin>>n;
		for(int i=1;i<=n;i++){
			char ch;
			cin>>ch;
			vis[i]=ch-'0';
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
			in[a[i]]++;
		}
		for(int i=1;i<=n;i++){
			if(in[i]==0) q.push(i); 
		}
		while(!q.empty()){
			int x=q.front();
			q.pop();
			int y=a[x];
			in[y]--;
			if(in[y]==0) q.push(y);
			if(vis[x]){//拓扑 
				ans[++len]=x;
				vis[y]^=1;
			}
		}
		for(int i=1;i<=n;i++){
			if(in[i]==1 and vis[i]==1){
				int now=i;
				len1=len2=0;
				bool f=0;
				while(in[now]){
					in[now]--;
					if(vis[now]) f^=1;
					if(f) ans1[++len1]=now;
					else ans2[++len2]=now;
					now=a[now];
				}
				if(f){//无解 
					cout<<-1<<'\n';
					goto A;
				}
				if(len1<len2){//两种情况 要么起点不选，要么起点选 取最优的 
					for(int j=1;j<=len1;j++){
						ans[++len]=ans1[j];
					}
				}
				else{
					for(int j=1;j<=len2;j++){
						ans[++len]=ans2[j];
					}
				}
			}
		}
		cout<<len<<'\n';
		for(int i=1;i<=len;i++){
			cout<<ans[i]<<' ';
		}
		cout<<'\n';
		A:;
	} 
	return 0;
} 
```

---

## 作者：TLE_Automat (赞：1)


 **[Read in My Blog](https://tle-automat.top/2023/12/09/CF1907G/)**
 

## 题目链接

[https://codeforces.com/contest/1907/problem/G](https://codeforces.com/contest/1907/problem/G)

## 题目大意

给定一个长度为 $n$ 的 $01$ 串，有 $n$ 个开关，按下第 $i$ 个开关会反转位置 $i$ 和位置 $a_i$ 的状态（$a_i \neq i$），目标是让 $01$ 串的状态变为全 $0$ 。

报告无解，若有解，输出操作次数最少的方案。

## 数据范围

多组测试数据，保证

- $\sum n \le 2\times 10^{5}$
- $1 \le a_i \le n, a_i \neq i$ 


## 解题思路

注意到每个开关控制且仅控制两个位置的状态，所以我们可以把开关抽象成**边**，把每个位置抽象成一个**结点**。

我们发现总共有 $n$ 个节点 $n$ 条边，但是图不保证联通，所以建完图之后是一个基环树森林。

问题变为给定一个基环树森林，选择最小的边集，使得反转边集中所有边连接的两个结点的状态后，所有结点的状态都变为 $0$ 。

其实只需要考虑一个基环树上怎么做。

首先可以注意到这颗基环树上状态为 $1$ 的结点个数必须为偶数个，否则肯定无解。

其次可以注意到一条边只会被选择 $0$ 次或者 $1$ 次，选择 $2$ 次跟 $0$ 次的结果相同，所以我们可以将基环树上的环断掉，比一下选断掉的边和不选断掉的边哪个更优即可。

于是只需要考虑在一颗树上怎么做。

先假设只有两个状态为 $1$ 的结点，显然最小的边集一定是两点简单路径上所有的边。

假设有四个呢？如果我们随便两两配对，发现路径可能有交集，这样是不优的，但是我们发现只要把路径交集去掉不选，剩下的不交的部分又构成两条新的路径，这样一定是最优的。

所以到此为止此题基本结束，我们只需要按照任意顺序给状态为 $1$ 的结点配对，把所有配对的点对的路径上所有边的值加 $1$ ，最后选择值为奇数的边即为最优方案。

用树上差分加上倍增求 lca 实现的话为 $O(n\log n)$ ，瓶颈为倍增求 lca 。

## 参考代码

[https://codeforces.com/contest/1907/submission/236342135](https://codeforces.com/contest/1907/submission/236342135)

---

## 作者：Diaоsi (赞：1)

[Lights](https://www.luogu.com.cn/problem/CF1907G)

难得的一眼出思路的题目。

将所有的 $i$ 对 $a_i$ 连有向边，连完所有边后会得到一个**内向基环树**森林。为方便表述，以下将亮灯的点称为黑点，否则为白点。

首先判断无解，若任意一个基环树内有奇数个黑点，那一定不能把所有的黑点变成白点。

注意到，黑点只能朝着有向边移动，而根据内向基环树的性质，最后一定会移动到环上。

将环上节点看作根，对于每一个环子树将所有黑点同时向根移动，假定某一时刻以 $x$ 为根的子树内的所有黑点都在 $x$ 和其子树的根节点上（后面会解释为什么），考虑黑点在节点 $x$ 交汇的过程：

- 若以 $x$ 为根的子树内有偶数个黑点，则将这些黑点两两匹配，在 $x$ 上消除。

- 若以 $x$ 为根的子树内有奇数个黑点，则将偶数个黑点两两匹配消除后，剩余的一个黑点移动到 $x$。

其实上述过程十分简单，把黑点（除 $x$ 自身）都向前移动一步即可，最后以 $x$ 为根的子树一定最多只有 $x$ 节点为黑，于是我们又可以继续重复这个过程（有点类似一个递归的结构，这也解释了前面的问题）。

不断重复之后，所有的黑点都会集中在环上，不难发现环上只有两种匹配方案，贪心取最小即可。

时间复杂度 $\mathcal{O}(n)$，代码实现较为繁琐。

```Code:```
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,n,cnt,fa[N],size[N],ans[N],nxt[N],col[N],chk[N],v[N],vis[N];
int c[2],cans[2][N];
vector<int> h[N],cir;
char s[N];
void add(int x,int y){
	h[x].push_back(y);
}
int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}
void merge(int u,int v){
	int x=get(u),y=get(v);
	if(x==y)return;
	if(size[x]<size[y])swap(x,y);
	fa[y]=x,size[x]+=size[y];
}
void dfs(int x,int fa){
	for(int y:h[x]){
		if(v[y]==2||y==fa)continue;
		dfs(y,x);
	}
	for(int y:h[x])
		if(y!=fa&&col[y]&&v[y]!=2){
			ans[++cnt]=y;
			col[y]^=1,col[x]^=1;
		}
}
void solve(){
	scanf("%d",&n);
	scanf("%s",s+1);
	cnt=0;
	for(int i=1;i<=n;i++){
		h[i].clear();
		col[i]=s[i]-'0';
		fa[i]=i,size[i]=1;
		chk[i]=v[i]=vis[i]=0;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&nxt[i]);
		merge(i,nxt[i]);
		add(i,nxt[i]);
		add(nxt[i],i);
	}
	for(int i=1;i<=n;i++){
		int x=get(i);
		chk[x]^=col[i];
	}
	for(int i=1;i<=n;i++)
		if(chk[i]&1){puts("-1");return;}
	for(int i=1;i<=n;i++){
		int x=get(i),y=i,st=0,num=0;
		cir.clear();
		if(vis[x])continue;
		vis[x]=1;
		while(1){
			v[y]++;
			if(v[y]==2)cir.push_back(y);
			if(v[nxt[y]]==2)break;
			y=nxt[y];
		}
		for(int t:cir){
			dfs(t,0);
			if(col[t])st=t;
		}
		c[0]=c[1]=0;
		if(st){
			int ed=st;
			while(1){
				cans[num][++c[num]]=ed;
				ed=nxt[ed];
				if(col[ed])num^=1;
				if(ed==st)break;
			}
			if(c[0]<c[1])
				for(int j=1;j<=c[0];j++)ans[++cnt]=cans[0][j];
			else
				for(int j=1;j<=c[1];j++)ans[++cnt]=cans[1][j];
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",ans[i]);
	puts("");
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```





---

## 作者：Priestess_SLG (赞：0)

很赤石的一题，献祭了 $1.5$ 小时。~~写完这题省选就不用赤石了~~

经典套路考虑对于每一个 $i$ 把 $i$ 向 $a_i$ 连边，那么得到一个基环树森林。然后对于森林中每一个连通块（基环树），找到该基环树中心的环，用 tarjan 缩点然后得到一个树，在树上将除根节点外所有点从下往上贪心挪动 $1$ 的位置，此时只剩下基环树中心的环。发现环上要么从第一个 $1$ 要么从第二个 $1$ 贪心，其余情况必然和这两种情况重合，因此直接分两类讨论即可。

时间复杂度为 $O(n)$，但是巨大难写，我写了超过 $10$ KB。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
// #define int long long
using namespace std;
const int N = 500010;
stack<int> stk;
char s[N], bkup[N];
vector<int> adj[N], adj2[N], scc[N];
int to[N], idx, tot, bel[N], low[N], dfn[N], instk[N], siz[N], vis[N], deg[N], use[N], fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void dfs(int u) {
    dfn[u] = low[u] = ++idx;
    instk[u] = 1, stk.emplace(u);
    for (int &v : adj[u])
        if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
        else if (instk[v]) low[u] = min(low[u], dfn[v]);
    if (low[u] == dfn[u]) { ++tot;
        while (stk.top() != u) {
            int t = stk.top(); stk.pop();
            instk[t] = 0, bel[t] = tot;
        }
        int t = stk.top(); stk.pop();
        instk[t] = 0, bel[t] = tot;
    }
}
void rotate(vector<int> &v) {
    vector<int> vv;
    for (int i = 1; i < v.size(); ++i) vv.emplace_back(v[i]);
    vv.emplace_back(v[0]);
    v.swap(vv);
}
signed main() {
    // cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int T, tc, ca = 1;
    cin >> T;
    tc = T;
    while (T--) {
        int n;
        cin >> n;
        idx = tot = 0;
        scanf("%s", s + 1);
        for (int i = 1; i <= n; ++i) cin >> to[i];
        for (int i = 1; i <= n; ++i) fa[i] = i;
        // if (tc > 10) {
        //     if (ca++ == 21) {
        //         cout << n << '\n';
        //         puts(s + 1);
        //         for (int i = 1; i <= n; ++i) cout << to[i] << ' ';
        //         cout << '\n';
        //     }
        //     continue;
        // }
        for (int i = 1; i <= n; ++i) adj[i].clear(), vis[i] = use[i] = 0;
        for (int i = 1; i <= n; ++i) adj[i].emplace_back(to[i]);
        for (int i = 1; i <= n; ++i)
            if (find(i) != find(to[i])) fa[find(i)] = find(to[i]);
        int cut = 0;
        for (int i = 1; i <= n; ++i)
            if (i == find(i)) ++cut;
        if (cut > 1) {
            int wa = 0;
            vector<int> op;
            for (int i = 1; i <= n; ++i) scc[i].clear();
            for (int i = 1; i <= n; ++i) scc[find(i)].emplace_back(i);
            for (int i = 1; i <= n; ++i) dfn[i] = low[i] = instk[i] = bel[i] = siz[i] = 0;
            for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i);
            for (int i = 1; i <= n; ++i) if (bel[i] == bel[to[i]]) ++siz[bel[i]];
            for (int _ = 1; _ <= n; ++_) if (scc[_].size()) { 
                int id = -1; for (int &i : scc[_]) if (siz[i] > 0) id = i;
                int idd = -1; for (int &i : scc[_]) if (bel[i] == id) { idd = i; break; }
                vector<int> circ; while (!vis[id]) circ.emplace_back(id), vis[id] = 1, id = to[id];
                int cnt = 0;
                for (int &i : scc[_])
                    if (s[i] == '1') ++cnt;
                if (cnt & 1) {
                    wa = 1;
                    break;
                }
                else {
                    // 先处理基环树外侧链上的部分
                    for (int &i : scc[_]) deg[i] = 0;
                    for (int &i : scc[_]) ++deg[to[i]];
                    queue<int> q;
                    for (int &i : scc[_])
                        if (!deg[i]) q.emplace(i);
                    while (q.size()) {
                        int t = q.front(); q.pop();
                        for (int &g : adj[t]) {
                            if (s[t] == '1') op.emplace_back(t), s[t] ^= 1, s[g] ^= 1;
                            if (!--deg[g]) q.emplace(g);
                        }
                    }
                    vector<int> ring;
                    int id = -1; for (int &i : scc[_]) if (siz[bel[i]] > 0) id = bel[i];
                    // cout << "wocao: ";
                    // cout << id << '\n';
                    // cout << "nmb: ";
                    // for (int &i : scc[_]) cout << i << ' ';
                    // cout << '\n';
                    int now = -1;
                    for (int &i : scc[_])
                        if (bel[i] == id) {
                            now = i;
                            break;
                        }
                    for (int &i : scc[_]) vis[i] = 0;
                    int cou = 0;
                    while (!vis[now]) {
                        ring.emplace_back(now);
                        vis[now] = 1;
                        if (s[now] == '1') ++cou;
                        now = to[now];
                    }
                    if (cou & 1) {
                        wa = 1;
                        break;
                    }
                    if (cou) {
                        int id = -1, ui = -1;
                        for (int i = 0; i < ring.size(); ++i)
                            if (s[ring[i]] == '1') {
                                id = ring[i];
                                ui = i;
                                break;
                            }
                        for (int &i : scc[_]) bkup[i] = s[i];
                        vector<int> v1, v2;
                        int tcou = cou, ip = id;
                        while (cou) {
                            if (s[id] == '1') {
                                v1.emplace_back(id);
                                if (s[to[id]] == '1') cou -= 2;
                                s[id] ^= 1, s[to[id]] ^= 1;
                            }
                            id = to[id];
                            // puts(s + 1);
                            // _sleep(150);
                        }
                        cou = tcou;
                        id = ip;
                        for (int &i : scc[_]) s[i] = bkup[i];
                        for (int i = ui + 1; i < ring.size(); ++i)
                            if (s[ring[i]] == '1') {
                                id = ring[i];
                                break;
                            }
                        while (cou) {
                            if (s[id] == '1') {
                                v2.emplace_back(id);
                                if (s[to[id]] == '1') cou -= 2;
                                s[id] ^= 1, s[to[id]] ^= 1;
                            }
                            id = to[id];
                            // puts(s + 1);
                            // _sleep(150);
                        }
                        if (v1.size() < v2.size()) {
                            for (int &i : v1) op.emplace_back(i);
                        } else {
                            for (int &i : v2) op.emplace_back(i);
                        }
                    }
                }
                if (wa) break;
            }
            if (wa) {
                cout << "-1\n";
                continue;
            }
            cout << op.size() << '\n';
            for (int &i : op) cout << i << ' ';
            cout << '\n';
            continue;
        }
        for (int i = 1; i <= n; ++i) dfn[i] = low[i] = instk[i] = bel[i] = siz[i] = 0;
        for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i);
        for (int i = 1; i <= n; ++i) if (bel[i] == bel[to[i]]) ++siz[bel[i]];
        int id = -1; for (int i = 1; i <= n; ++i) if (siz[i] > 0) id = i;
        int idd = -1; for (int i = 1; i <= n; ++i) if (bel[i] == id) { idd = i; break; }
        vector<int> circ; while (!vis[id]) circ.emplace_back(id), vis[id] = 1, id = to[id];
        int cnt = count(s + 1, s + n + 1, '1');
        if (cnt & 1) cout << "-1\n";
        else {
            vector<int> v;
            for (int i = 1; i <= tot; ++i) adj2[i].clear();
            for (int i = 1; i <= n; ++i) {
                int x = bel[i], y = bel[to[i]];
                if (x != y) adj2[x].emplace_back(y), adj2[y].emplace_back(x);
            }
            vector<int> op;
            // 先处理基环树外侧链上的部分
            for (int i = 1; i <= n; ++i) deg[i] = 0;
            for (int i = 1; i <= n; ++i) ++deg[to[i]];
            queue<int> q;
            for (int i = 1; i <= n; ++i)
                if (!deg[i]) q.emplace(i);
            while (q.size()) {
                int t = q.front(); q.pop();
                for (int &g : adj[t]) {
                    if (s[t] == '1') op.emplace_back(t), s[t] ^= 1, s[g] ^= 1;
                    if (!--deg[g]) q.emplace(g);
                }
            }
            vector<int> ring;
            int id = -1; for (int i = 1; i <= n; ++i) if (siz[i] > 0) id = i;
            int now = -1;
            for (int i = 1; i <= n; ++i)
                if (bel[i] == id) {
                    now = i;
                    break;
                }
            for (int i = 1; i <= n; ++i) vis[i] = 0;
            int cou = 0;
            while (!vis[now]) {
                ring.emplace_back(now);
                vis[now] = 1;
                if (s[now] == '1') ++cou;
                now = to[now];
            }
            if (cou & 1) {
                cout << "-1\n";
                continue;
            }
            if (cou) {
                int id = -1, ui = -1;
                for (int i = 0; i < ring.size(); ++i)
                    if (s[ring[i]] == '1') {
                        id = ring[i];
                        ui = i;
                        break;
                    }
                for (int i = 1; i <= n; ++i) bkup[i] = s[i];
                vector<int> v1, v2;
                int tcou = cou, ip = id;
                while (cou) {
                    if (s[id] == '1') {
                        v1.emplace_back(id);
                        if (s[to[id]] == '1') cou -= 2;
                        s[id] ^= 1, s[to[id]] ^= 1;
                    }
                    id = to[id];
                }
                cou = tcou;
                id = ip;
                for (int i = 1; i <= n; ++i) s[i] = bkup[i];
                for (int i = ui + 1; i < ring.size(); ++i)
                    if (s[ring[i]] == '1') {
                        id = ring[i];
                        break;
                    }
                while (cou) {
                    if (s[id] == '1') {
                        v2.emplace_back(id);
                        if (s[to[id]] == '1') cou -= 2;
                        s[id] ^= 1, s[to[id]] ^= 1;
                    }
                    id = to[id];
                }
                if (v1.size() < v2.size()) {
                    for (int &i : v1) op.emplace_back(i);
                } else {
                    for (int &i : v2) op.emplace_back(i);
                }
            }
            cout << op.size() << '\n';
            for (int &i : op) cout << i << ' ';
            cout << '\n';
        }
    }
    return 0;
}
```

---

## 作者：TangyixiaoQAQ (赞：0)

# 思路解析
考虑**拓扑排序**。

首先我们可以建 $n$ 个点分别表示 $n$ 个开关，且点 $i$ 向点 $a_i$ 连一条边。

不难发现，若一个点的入度为 $0$，且其状态需要被反转，则开关 $i$ 必须被按下。

同理，若其入度为 $0$ 且不需要被反转，则开关不可被按下。

随后，我们对这张图进行拓扑排序。

所有不在环上点的开关是否被按下都可在拓扑排序的过程中判断。

下面我们来讨论环上的开关。

环上一点只被两个开关控制（因环外开关状态已被确定，忽略其影响），这也就意味着，如果我们已知环上任意一开关是否被按下，即可推出环上所有开关的状态。

环上的灯有偶数个亮着，则会有合法解，否则就输出 $-1$。

所以我们可以枚举环上任意一开关的状态，并分别计算出其按下/不按下的结果。

最后选择其中合法且按下开关个数最少的一种作为最终方案即可。

总时间复杂度为 $O(n)$。

---

## 作者：yangshengyu0719 (赞：0)

## 思路
对于每个 $i$ ，指向 $a_i$。这样，我们就会得到一个所有儿子指向其父亲的**基环树森林**。

对于环外的点，根据拓扑序，若遍历到一点 $i$ 需要关掉，就关掉该灯，并对应修改其父亲 $a_i$ 的开关状态。

然后对于环上的点，我们可以单独存起来，用贪心求得方案。

时间复杂度 $O(n)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a[N],nx[N],ind[N];
int vis[N],huan[N],cnt,ans[N],now;
string s;
void clear(){
	for(int i=1;i<=n;i++) ind[i]=vis[i]=0;
	ans[0]=now=0;
}
void Topo(){
	queue<int> q;
	for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
	while(!q.empty()){
		int t=q.front();q.pop();
		vis[t]=1;
		if(a[t]) a[nx[t]]^=1,ans[++ans[0]]=t;
		if(!--ind[nx[t]]) q.push(nx[t]);
	}
}
void dfs(int x){
	vis[x]=1;huan[++cnt]=x;
	if(!vis[nx[x]]) dfs(nx[x]);
}
int one[N],type[2];
int Cut(){//求环上最优方案，返回最优位置
	int sum=0;type[0]=type[1]=0;
	for(int i=1;i<=cnt;i++)	sum+=a[huan[i]];
	if(sum&1) return -1;
	for(int i=1;i<=cnt;i++){
		one[i]=one[i-1]+a[huan[i]];
		if(!a[huan[i]]) type[one[i]&1]++;
	}
	if(type[0]>type[1]){for(int i=1;i<=cnt;i++) if(one[i]==1) return i;}
	else{for(int i=1;i<=cnt;i++) if(one[i]==2) return i;}
	return 1;
}
void Print(){
	if(now==-1) cout<<-1;
	else{
		cout<<ans[0]<<'\n';
		for(int i=1;i<=ans[0];i++) cout<<ans[i]<<' ';
	}
	cout<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		clear();cin>>n>>s;
		for(int i=1;i<=n;i++) a[i]=s[i-1]-'0';
		for(int i=1;i<=n;i++) cin>>nx[i],ind[nx[i]]++;
		Topo();
		for(int i=1;i<=n;i++)
			if(!vis[i]){
				cnt=0,dfs(i),now=Cut();
				if(now==-1) break;
				for(int j=1;j<=cnt;j++){
					if(a[huan[now]]) a[huan[now%cnt+1]]^=1,ans[++ans[0]]=huan[now];
					now=now%cnt+1;
				}
			}
		Print();
	}
	return 0;
}//代码写得有点复杂了，将就看吧
```

---

## 作者：Dawn_cx (赞：0)

题意：你有 $n$ 个灯，有开有闭，想把这些灯全关了，但是灯有个性质是每按一次灯 $i$ 开关，灯 $a_i$ 的开关也会被按一次，问你最少多少次能把这些灯全关了，不能全关输出 $-1$。

把 $i$ 和 $a_i$ 连出一条边，就会获得一个 $n$ 个点 $n$ 条边的一张图，这个图会由若干棵基环树组成，对于每棵树我们先处理他的叶子节点，随后删掉叶子节点，最后剩下一个环，在这个环上我们每次操作都是动偶数个灯，因此如果环上有奇数个灯开着那么就无法全部关闭，输出 $-1$。对于环上有两种情况，一种是从起点开始关，一种是从起点的下一个点开始关，这个起点可以随意设置，因为环上是等价的，选出这两种情况关闭数量最少的一个进行关灯即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &x){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch&15);ch=getchar();}
    x=s*w;
}
const int N = 2e5 + 100;
int T,n,cd[N],e[N],a[N],cc[N];
void solve(){
    read(n);
    for(int i=1;i<=n;i++){
        char chr=getchar();
        while(chr!='0'&&chr!='1')chr=getchar();
        cc[i]=cd[i]=chr&15;
    }
    vector<set<int> > s(n+1);
    queue<int> p;
    int ans=0;
    for(int i=1,x;i<=n;i++){
        read(x);e[i]=x;
        s[x].insert(i);
    }
    for(int i=1;i<=n;i++)if(s[i].size()==0)p.push(i);
    while(!p.empty()){
        int i=p.front();p.pop();
        if(cd[i]==1){
            s[e[i]].erase(i);
            cd[i]^=1,cd[e[i]]^=1;
            a[++ans]=i;
            if(s[e[i]].size()==0)p.push(e[i]);
        }
        else{
            s[e[i]].erase(i);
            if(s[e[i]].size()==0)p.push(e[i]);
        }
    }
    for(int now=1;now<=n;now++){
        if(cd[now]){
            vector<int> c;
            int sum=1;
            if(cd[now])c.push_back(1);
            for(int i=e[now];i!=now;i=e[i]){
                sum++;
                if(cd[i])c.push_back(sum);
            }
            if(c.size()&1){
                puts("-1");
                return ;
            }
            int s1=0,s2=c[0]+sum-c[c.size()-1];
            for(int i=1;i<c.size();i++){
                if(i&1)s1+=c[i]-c[i-1];
                else s2+=c[i]-c[i-1];
            }
            int st=now;
            if(s2<=s1)st=e[now];
            for(int i=st;;i=e[i]){
                if(cd[i]){
                    a[++ans]=i;
                    cd[i]^=1,cd[e[i]]^=1;
                }
                if(e[i]==st)break;
            }
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<=ans;i++)printf("%d ",a[i]);
    puts("");
    return ;
}
int main(){
    read(T);
    while(T--)solve();
    return 0;
}
```

---

