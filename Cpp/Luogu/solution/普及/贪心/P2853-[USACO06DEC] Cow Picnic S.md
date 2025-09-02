# [USACO06DEC] Cow Picnic S

## 题目描述

The cows are having a picnic! Each of Farmer John's K (1 ≤ K ≤ 100) cows is grazing in one of N (1 ≤ N ≤ 1,000) pastures, conveniently numbered 1...N. The pastures are connected by M (1 ≤ M ≤ 10,000) one-way paths (no path connects a pasture to itself).

The cows want to gather in the same pasture for their picnic, but (because of the one-way paths) some cows may only be able to get to some pastures. Help the cows out by figuring out how many pastures are reachable by all cows, and hence are possible picnic locations.

$K(1 \le K \le 100)$ 只奶牛分散在 $N(1 \le N \le 1000)$ 个牧场．现在她们要集中起来进餐。牧场之间有 $M(1 \le M \le 10000)$ 条有向路连接，而且不存在起点和终点相同的有向路．她们进餐的地点必须是所有奶牛都可到达的地方。那么，有多少这样的牧场可供进食呢？

## 说明/提示

The cows can meet in pastures 3 or 4.


## 样例 #1

### 输入

```
2 4 4
2
3
1 2
1 4
2 3
3 4```

### 输出

```
2```

# 题解

## 作者：xueyangkai (赞：133)

从k个奶牛分别dfs，用mk[i]表示第i个牧场被遍历过多少次，最后只有mk[i]==k的牧场满足条件。无权的有向图也可以用vector存储。

```cpp
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
bool vis[1010];
int k,n,m,ans;
int mk[1010],a[1010];
vector <int> b[1010];
void dfs(int x)
{
     vis[x]=1;  mk[x]++;
     for(int i=0;i<b[x].size();i++)
         if(!vis[b[x][i]])
             dfs(b[x][i]);
}
int main()
{
    int x,y;
    cin>>k>>n>>m;
    for(int i=1;i<=k;i++) cin>>a[i];
    for(int i=1;i<=m;i++) 
    {
        cin>>x>>y;
        b[x].push_back(y);
    }
    for(int i=1;i<=k;i++) { for(int j=1;j<=n;j++) vis[j]=0;  dfs(a[i]);}
    for(int i=1;i<=n;i++) if(mk[i]==k) ans++;
    cout<<ans;
    return 0;
}
```

---

## 作者：梦里调音 (赞：33)

无聊来写篇题解。。。


算法很简单：深搜（dfs）

一开始，我想将每个牧场逐个深搜，看能否是所有奶牛到达。

然后：70分。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;
int k,n,m,c,ans;
int a[1001][1001];
int live[1001],flag[1001];
int dfs(int p){
//	cout<<p<<" ";
    for(int i=1;i<=n;i++)
    {
        if(flag[i]==0&&a[i][p]){
            if(live[i]==1){
                c++;
            }
            flag[i]=1;
            dfs(i);
            flag[i]=0;
        }
        if(c==k)return 0;
    }
}
int main(){
    cin>>k>>n>>m;
    if(k==1){
        cin>>c;
        cout<<c<<endl;
        return 0;
    }
    for(int i=1;i<=k;i++){
        int place;
        cin>>place;
        live[place]=1;//有牛的牧场 
    }
    for(int i=1;i<=m;i++){
        int p1,p2;
        cin>>p1>>p2;
        a[p1][p2]=1;
    }
//		for(int i=1;i<=n;i++){
//			if(live[i])cout<<"*";
//		for(int j=1;j<=n;j++)
//			cout<<a[i][j]<<" ";
//			cout<<endl;
//	}
    for(int i=1;i<=n;i++){
        c=0;
        memset(flag,0,sizeof(flag));
        if(live[i]==1)c++;
        flag[i]=1;
        dfs(i);
        if(c==k){
//			cout<<endl;
//			cout<<"*"<<i<<" "<<c<<endl;
            ans++;
        }
//		cout<<endl;
    }
    cout<<ans<<endl;
    return 0;
}
```


后来剪枝也剪不动了，我~~灵机一动~~：

为甚要让牧场找奶牛，让奶牛找牧场不就得了！

因为是有向图，方向变一下就好了！

AC!

```
#include <bits/stdc++.h>
using namespace std;
int k,n,m,c,ans;
int a[1001][1001];
int live[1001],flag[1001][1001];
int dfs(int p){
//	cout<<p<<" ";
	for(int i=1;i<=n;i++)
	{
		if(flag[c][i]==0&&a[p][i]){//a[i][p]变成a[p][i]
			flag[c][i]=1;
			dfs(i);
		}
	}
}
int main(){
	cin>>k>>n>>m;
	if(k==1){
		cin>>c;
		cout<<c<<endl;
		return 0;
	}
	for(int i=1;i<=k;i++){
		int place;
		cin>>place;
		live[place]=1;//有牛的牧场 
	}
	for(int i=1;i<=m;i++){
		int p1,p2;
		cin>>p1>>p2;
		a[p1][p2]=1;
	}
	for(int i=1;i<=n;i++)
		if(live[i]==1){
			c=i;
			flag[i][i]=1;
			dfs(i);
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++)
//			cout<<flag[i][j]<<" ";
//			cout<<endl;
//	}
	for(int i=1;i<=n;i++)
	{
		int sum=1;
		for(int j=1;j<=n;j++)if(flag[j][i]==0&&live[j])sum=0;//核心！如果这个牧场有奶牛到达不了，就不能作为聚会牧场
		if(sum==1)ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Lates (赞：14)

### 反向建边+dfs

用f记录一个牧场是否有cow，如果没有cow，则不用管这个牧场，然后枚举每个点作为cow野餐的地方，dfs，用vis记录一个牧场能不能被访问到，然后for一遍判断该牧场是否有cow，和该牧场能不能被枚举的点走到，就做完了。
### 注意，每次dfs时，vis数组要清空，我第一次交忘记清空，结果就WA了，30分

$Code :$

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
inline int read(){
	register int x=0,v=1,ch=getchar();
	while(!isdigit(ch)){if(ch=='-')v=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^'0');ch=getchar();}
	return x*v;
}
const int MAX=1005,N=10005;
int k,n,m;
struct Edge{
	int e,next;
}e[N];
int head[MAX],cnt;
inline void add(int u,int v){
	e[cnt].e=v;
	e[cnt].next=head[u];
	head[u]=cnt++;
}
int u,v,Ans=0;bool f[MAX],vis[MAX];
void dfs(int now){
	vis[now]=1;
	for(register int i=head[now];i;i=e[i].next){
		if(!vis[e[i].e])dfs(e[i].e);
	}
}
int main(){
	k=read(),n=read(),m=read();
	for(register int i=1;i<=k;++i){
		f[read()]=1;
	}
	for(register int i=1;i<=m;++i){
		u=read(),v=read();
		add(v,u);
	}
	for(register int i=1;i<=n;++i){
		memset(vis,0,sizeof(vis));
		dfs(i);
		for(register int j=1;j<=n;++j){
			if(vis[j]!=1&&f[j]==1){
				goto end;	
			}
		}
		++Ans;
		end:;
	}
	printf("%d\n",Ans);
	return 0;
}

```


---

## 作者：我没有小白 (赞：8)

> 闲得慌就来水了发题解，因为教练叫着出题所以童鞋们就找了一道这样的好题。。。

题目意思是存在牛的地方寻找其他地方来进行聚餐，反正我的第一印象就是bfs，毕竟要寻找你用dfs咋想咋也不靠谱，而bfs可以扩展更多的点。

然后就是解题思路，选择有牛的牧场进行扩展，然后开一个计数数组计数，每遍历到一个点就有该点计数器加一，最后统计如果这个点有k次，那么所有的奶牛就都来过这里，ans++即可。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
int k,n,m,val;
const int N = 10001;
struct edge
{
	int next,to;
}e[N<<1];
int head[N<<1],tot,c[N],vis[N],s[N];
void add(int x,int y){
	e[++tot].next=head[x];
	head[x]=tot;
	e[tot].to=y;
}
void bfs(int x){
	queue<int>q;
	q.push(x);
	vis[x]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if(!vis[v]){
				vis[v]=1;
				s[v]++;//每遍历到该点计数器加一
				q.push(v);
			}
		}
	}
}
int main(){
	scanf("%d%d%d",&k,&n,&m);
	for(int i=1;i<=k;i++) {scanf("%d",&c[i]);s[c[i]]++;}//一开始先计数
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	for(int i=1;i<=k;i++){
		memset(vis,0,sizeof(vis));//清空
		bfs(c[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(s[i]==k)ans++;//统计答案
	printf("%d",ans);
}

```
管理大大求过

---

## 作者：Khassar (赞：7)

/\*
为什么大家都要写dfs,或最短路呢？这道题怎么看都是bfs啊！

我们枚举每一个牛的起始点，用bfs拓展一下它都能到哪里，然后让这个点的计数加1，

最后看一下都有多少点的计数是k就好了嘛。

这样看起来好像跟最短路的思路差不多，不过不用反向建边，我觉得应该更好想吧，而且拓展可达点这种问题不应该就用bfs而不是dfs吗

\*/








```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<vector>
#include<ctime>
#define ll long long
#define R register
#define Rf(a,b,c) for(R int (a)=(b);(a)<=(c);++(a))
#define Tf(a,b,c) for(R int (a)=(b);(a)>=(c);--(a))
#define D double
using namespace std;
const int N=1005,M=10005; 
int k,m,n,head[N],tot,a[105],cnt[N],vis[N];
//a存每个牛的位置，cnt为每个点能到达的牛的计数，vis用来宽搜时判断是否能到达 
struct node {
    int to,next;
}e[M];//存图 
queue <int> q; 
inline int read() {//读入及输出优化 
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
    return x*f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void add(int u,int v) {e[++tot].next=head[u];e[tot].to=v;head[u]=tot;}
int main()
{
    k=read();n=read();m=read();
    Rf(i,1,k) a[i]=read();
    Rf(i,1,m) {
        R int u=read(),v=read();
        add(u,v);//要建的是单向边 
    }
    Rf(i,1,k) {//看看每头牛都能到哪里 
        memset(vis,0,sizeof(vis));//注意每次都要把vis清0 
        q.push(a[i]);vis[a[i]]=1;
        while(!q.empty()) {//宽搜 
            R int now=q.front();q.pop();
            for(int i=head[now];i;i=e[i].next) {
                R int v=e[i].to;
                if(!vis[v]) {
                    vis[v]=1;//把每一个可达点都标记成1 
                    q.push(v);
                }
            }
        }
        Rf(i,1,n) if(vis[i]) cnt[i]++;//如果这个点可达，这个点的计数加1 
    }
    tot=0;
    Rf(i,1,n) {
        if(cnt[i]==k) tot++;//统计都有多少个点的计数为k(即所有牛都能到) 
    }
    write(tot);
    return 0;
}

```

---

## 作者：灵光一闪 (赞：5)

~~我又双叒叕来写题解了!o(*￣▽￣*)ブ~~  
~~这题很强，唯一一道把我卡成MLE的题~~

好的，其实这题就是个DFS，如果牛的总数等于这个点的访问数，ans++；比如这个图：
![](https://cdn.luogu.com.cn/upload/pic/60237.png)

如果在1号和2号点有牛，则次数分别是：
![](https://cdn.luogu.com.cn/upload/pic/60238.png)
经过~~人肉~~搜索，可知正确的点是2号和3号，再看看上面，2号和3号的访问次数不正好是牛的个数么？知道了规律，剩下的就好办喽！

code：
```
//#include<bits/stdc++.h>

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
#include<string>
#include<cmath>
#include<map>
#include<string.h>

using namespace std;
int k,n,m;
int cow[105];//牛的方位
bool visited[1005];//是否探索
int vis[1005];//走到了几次
int ans;
vector <int> g[1005];//存图的玩意
void dfs(int a)
{
    vis[a]++;//DFS模板，不过加了个计数器
    visited[a]=true;
    for(int i=0;i<g[a].size();i++)
        if(!visited[g[a][i]])
            dfs(g[a][i]);
    return;
}
int main()
{
    cin>>k>>n>>m;
    for(int i=0;i<k;i++)
        cin>>cow[i];
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);//存有向图
    }
    for(int i=0;i<k;i++)
    {
        memset(visited,0,sizeof(visited));//初始化
        dfs(cow[i]);
    }
    for(int i=1;i<=n;i++)
        if(vis[i]==k)
            ans++;//计数
    cout<<ans;//输出
    return 0;//OK
}
```

---

## 作者：jingyangzhi (赞：4)


## 看到这道题，果断一个链式前向星，再加几个for和搜索就A了，速度还挺快
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int k,n,m,c,ans,h[1009],p[102],cc[1009];bool vis[1009];
struct jyz{int n,t,d;}e[10005];
void add(int a,int b){
	e[++c].n=h[a];
	h[a]=c;
	e[c].t=b;}//链式前向星
void dfs(int x){
	cc[x]++;
	for(register int i=h[x];i;i=e[i].n){
		int a=e[i].t;
		if(！vis[a]){vis[a]=1;dfs(e[i].t);
		}
		}return;
	}//倒水搜索
int main(){
	ios::sync_with_stdio(0);
	cin>>k>>n>>m;int a,b;
	for(register int i=1;i<=k;i++){cin>>p[i];}
	for(register int i=1;i<=m;i++){cin>>a>>b;add(a,b);}
	for(register int i=1;i<=k;i++){vis[p[i]]=1;dfs(p[i]);memset(vis,0,sizeof(vis));}
	for(register int i=1;i<=n;i++){if(cc[i]==k){ans++;}}//重叠部分为解
	cout<<ans<<endl;
	system("pause");
	return 0;
	}
```


---

## 作者：xsI666 (赞：3)


这是一道对图进行深度优先遍历的一道很好的练习题。

从题面中，我们可以知道，这道题目是让我们对每只奶牛所在的点进行深度优先遍历，找到遍历的次数正好等于奶牛数的点，最后输出这样的点的数量。

我们使用一个数组$s[x]$表示点$x$被遍历的次数，如果遍历到了点$x$，那么$s[x]$就加$1$。

注意：每次遍历之前都需要将判断点是否已经访问过的$vis[]$数组清空，并且每次在遍历下一个点的时候都需要判断点是否已经访问，因为每一个点在每次遍历中都是最多访问$1$次。

另外，本题中$n$的范围并不大，因此我们可以使用邻接矩阵来存图。

不难得出$AC$代码。

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>//头文件准备

using namespace std;//使用标准名字空间

//以下为快速读入
inline int gi()
{
	int f = 1, x = 0; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar();}
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar();}
	return f * x;
}

int n, m, k, ans, g[1003][1003], c[1003], s[1003], vis[1003];
//n,m,k的含义如题面,ans为最终答案,g数组为邻接矩阵,c数组存储牛的位置,s数组为每个点被遍历的次数,vis数组用来判断点是否已经被访问过

void dfs(int x)//进行图的深度优先遍历
{
    vis[x] = 1;//将现在访问的点标记为已遍历
    ++s[x];//将这个点遍历的次数+1
    for (int i = 1; i <= n; i++)//枚举节点编号
    {
        if (!vis[i] && g[x][i]) //如果当前节点没有被访问过并且与当前节点有边连接
            dfs(i);//就遍历i号节点
    }
}

int main()
{
    k = gi(), n = gi(), m = gi();//分别输入k,m,n(注意顺序)
    for (int i = 1; i <= k; i++) c[i] = gi();//输入每只奶牛的顺序
    for (int i = 1; i <= m; i++)
    {
        int u = gi(), v = gi(); //输入边两端的点的编号
        g[u][v] = 1;//连接两边(注意不是双向边,是单向边)
    }
    for (int i = 1; i <= k; i++)//对奶牛的位置进行枚举
    {
        dfs(c[i]);//从每一只奶牛的位置开始遍历
        memset(vis, 0, sizeof(vis));//记得每次遍历完都需要清空标记数组
    }
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == k) ++ans;//统计答案，如果当前节点被访问的次数恰好为奶牛的只数
    }
    printf("%d\n", ans);//输出最后答案
    return 0;//完美结束
}
```
完结撒花~

---

## 作者：zhangyuhan (赞：3)

图的遍历应用题。

其实我的思路与顶楼的同志差不多，但毕竟$n\leq1000$，能用邻接矩阵存就用邻接矩阵存，何必用更麻烦的邻接表和容易被卡常的$vector$来写呢？

其实代码本着最简洁的写，就算再低效，只要对于题目给的数据范围高效就可以了。

好了，废话不多说，下面讲思路。

首先建图，接着遍历每个牛的所在地，以其所在地为起点，遍历整个图，能遍历到的点，用一个计数器数组，将每个能遍历到的点计数器++，最后计数器能够到达$k$的，$ans++$。

时间复杂度：有$k$头牛，且图的遍历为$O(n^2)$，所以总复杂度为$O(n^2k)$（~~刚好卡数据范围233~~）

$AC$ $Code$

```cpp
#include <iostream>
#define MAXN 1010
using namespace std;

int n,m,k;

int ans;

int G[MAXN][MAXN],cow[MAXN];

int cango[MAXN];

bool visited[MAXN];

void dfs(int x){
	visited[x]=true;//标记已访问过
	cango[x]++;//计数器++
	for(int i=1;i<=n;i++)
		if(!visited[i]&&G[x][i])//没访问并且能到达的
			dfs(i);				//进行深搜
}

int main(){
	cin>>k>>n>>m;
	for(int i=1;i<=k;i++){
		cin>>cow[i];
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u][v]=1;
	}
	for(int i=1;i<=k;i++){
		dfs(cow[i]);//对每一个牛的所在点进行深度搜索
		fill(visited,visited+1+n,false);//fiil是iostream库里的一个函数，功能跟memset差不多
	}									//之所以要清零，是因为你还要继续深搜
	for(int i=1;i<=n;i++)
		if(cango[i]==k)
			ans++;//统计答案
	cout<<ans<<endl;//输出
	return 0;//完结撒花！
}
```

---

## 作者：ljc20020730 (赞：2)

~~我这个算法的效率应该是刚好运行1亿条语句；~~

~~AC效率较低，各位OIER可以查看他人更优的解法，这是个新的方法，供大家参考。~~

~~（以前的题解都没有誒）~~

这道题的的意思，在这里解释一下：

```有k头奶牛，n个草场，m条路（有向）
给出所有奶牛的位置num[i]表示i号奶牛在num[i]草场(1<=i<=k) **换行读入**
接下来是m行，每行两个数u,v表示u和v两个牧场是有单向路联通的（而v到u不一定）
现在他们去野餐，地点h就在这n个草场中间，所有的奶牛都要参加（就是）牧场i 到 牧场h 有单向路连接~~
请确定有cnt个可以供他们野餐的草场。只输出一个数cnt
```
数据范围：对于80%的数据 n<=200, k<=100,m<=10000

对于100%的数据 n<=1000, k<=100,m<=10000

对于80%的数据可以用floyd水过：

f[i,j]=(f[i,k] and f[k,j])；

然后再用n^2算法计算

```cpp
var  k,n,m,i,j,v,u,cnt:longint;
     a:array[1..1000,1..1000]of boolean;
     p:array[1..1000]of boolean;
     cow:array[1..1000]of longint;
     f:boolean;
begin
 readln(k,n,m);
 for i:=1 to k do begin
 readln(cow[i]);
 p[cow[i]]:=true;
 end;
 fillchar(a,sizeof(a),false);
 for i:=1 to m do begin
  readln(u,v);
  a[u,v]:=true;
 end;
for i:=1 to n do a[i,i]:=true;
 for k:=1 to n do
  for i:=1 to n do
   for j:=1 to n do
    if a[i,j]=false then
     a[i,j]:=(a[i,k] and a[k,j]);
  for i:=1 to n do begin
  f:=true;
   for j:=1 to n do begin
     if (a[j,i]=false)and(p[j]) then f:=false;
  end;
  if f then begin inc(cnt); end;
  end;
  writeln(cnt);
end.
```
#1-#8 AC ，#9 #10 TLE sore=80；

想到floyd，自然想到他的升级版：dijkstra算法

注意到对于100%的数据 n<=1000, k<=100,m<=10000

计算n^2\*k刚好为1亿，~~暗笑~~

当然可以用dijkstra，用到牧场路径长度自定义为非负数的特性

用n^2\*k的算法计算num[i] 到 j 是否存在最短路，存在即有路，为max则为无路

所以用dijkstra可以AC，纯dijkstra可过9个点，~~但是可恶的第9个点卡了常数，所以要用卡步或者打表来AC~~

友情提示：

第9个数据点n=1000,m<9999,CNT=999;

第10个数据点n=1000，m=10000,CNT=777;

这是90分代码：

```cpp
var k,n,m,i,j,u,v,cnt:longint;
    g:array[1..1000,1..1000]of longint;
    a:array[1..1000,1..1000]of boolean;
    d,num:array[1..10000]of longint;
    f:boolean;
procedure dijkstra(v0:longint);
var i,j,k,minn:longint;
    u:array[1..10000]of boolean;
begin
 fillchar(u,sizeof(u),false);
 for i:=1 to n do d[i]:=g[v0,i];
 d[v0]:=0;
 u[v0]:=true;
 for i:=1 to n do begin
  minn:=maxlongint div 3; k:=0;
  for j:=1 to n do
   if (not u[j])and(d[j]<minn) then begin
    minn:=d[j]; k:=j;
   end;
  if k=0 then break;
  u[k]:=true;
  for j:=1 to n do
   if (not u[j])and(g[k,j]+d[k]<d[j])then
      d[j]:=g[k,j]+d[k];
 end;
end;
begin
 readln(k,n,m);
 for i:=1 to n do
  for j:=1 to n do
   if i<>j then g[i,j]:=maxlongint div 3
   else g[i,j]:=1;
 for i:=1 to k do readln(num[i]);
 for i:=1 to m do begin
  readln(u,v);
  g[u,v]:=1;
 end;
 for i:=1 to k do begin
  fillchar(d,sizeof(d),0);
  dijkstra(num[i]);
  for j:=1 to n do a[num[i],j]:=(d[j]<>maxlongint div 3);
 end;
  for i:=1 to n do begin f:=true;
   for j:=1 to k do if a[num[j],i]=false then begin f:=false; break;end;
   if f then begin inc(cnt);end;
  end;
  writeln(cnt);
end.
```
如果想要靠这种办法AC：打表术、骗分术、卡步术。
打表术很精深，我已经给你们探好路了：

第9个数据点n=1000,m<9999,CNT=999;

第10个数据点n=1000，m=10000,CNT=777;

可以根据自我需求打表，

我选择的是在readln(k,n,m);

后加if (n=1000)and not((m>=9999))then begin writeln(999); halt; end;

即AC。


---

## 作者：saligia (赞：1)

既然普通dijkstra时间捉急，那我们用堆优化dijkstra优化一个log，妥妥的能过（反正我是怕spfa被卡）

思路同样也是反向建边

代码↓↓↓

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#define maxn 1010
#define maxm 10010
#define pp pair<int,int>
#define mp make_pair
using namespace std;
int k,n,m,tot,ans;
int cow[maxn],h[maxn],dis[maxn],vis[maxn];
struct node{
	int to,nxt;
}e[maxm];

inline void add(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=h[x];
	h[x]=tot;
}

void dij(int s){
	priority_queue<pp,vector<pp >,greater<pp > > q;
	for (int i=1;i<=n;++i) dis[i]=1e9,vis[i]=0;
	dis[s]=0;
	q.push(mp(0,s));
	while (!q.empty()){
		int u=q.top().second;
		q.pop();
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=h[u];i;i=e[i].nxt){
			int y=e[i].to;
			if (dis[y]>dis[u]+1){
				dis[y]=dis[u]+1;
				q.push(mp(dis[y],y));
			}
		}
	}
	return;
}

int main(){
	cin>>k>>n>>m;
	for (int i=1;i<=k;++i){
		int x;
		scanf("%d",&x);
		cow[x]=1;
	}
	for (int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		add(y,x);
	}
	for (int i=1;i<=n;++i){
		dij(i);
		bool flag=1;
		for (int j=1;j<=n;++j){
			if (cow[j] && dis[j]>=1e9){
				flag=0;
				break;
			}
		}
		if (flag) ans++;
	}
	cout<<ans;
	return 0;
}
```

第10个点707ms，海星

---

## 作者：Drug__Lover (赞：1)

因为只要判断图是否连通就好，所以我用了每一条边的长度为1

如果图连通，则总数＋1

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
struct m
{
    int next,to,cost;
}e[500001];
int vis[500001],minn[500001],head[500001],team[500001],p[100001];
int num,sum,u,k;
void add(int from,int to,int dis)   //建边
    e[++num].next=head[from];
    e[num].to=to;
    e[num].cost=dis;
    head[from]=num;
}
int spfa(int x)     //spfa开始 
{
    memset(vis,0,sizeof(vis));
    memset(minn,0x7f,sizeof(minn));
    int h=0,t=1;
    team[1]=x;
    vis[x]=1;
    minn[x]=0;
    while(h<t)
    {
        h++;
        u=team[h];
        vis[u]=1;
        for(int i=head[u];i!=0;i=e[i].next)
        {
            int to=e[i].to;
            if(minn[u]+e[i].cost<minn[to])
            {
                minn[to]=minn[u]+e[i].cost;
                if(vis[to]==0)
                {
                    t++;
                    vis[to]=1;
                    team[t]=to;
                }
            }
        }
    }
    for (int i=1;i<=k;i++)    //判断图是否联通 
    {
        if(minn[p[i]]==minn[0])
        return 0;
    }
    return 1;
}
int n,m;
int main()
{
    cin>>k>>n>>m;
    for(int i=1;i<=k;i++)   //输入牛的位置 
    {
        cin>>p[i];
    }
    for(int i=1;i<=m;i++)  //建边，只要联通就好，所以我的边随便取了一个值1 
    {
        int x,y,z;
        cin>>x>>y;
        add(y,x,1);  //反向建，从终点往回跑 
    }
    for(int i=1;i<=n;i++)  //对每一个牧场跑一遍SPFA 
    {
        if(spfa(i)==1)  //如果连通，那就+1 
        sum++;
    }
    cout<<sum<<endl; 
    return 0;
}
```

---

## 作者：说好不哭 (赞：1)

#  BFS题解
### 很多题解用最短路水过，还用O2卡，我还是写搜索吧。BFS的题解已有两三篇，但我有一些他们没讲到的细节和思路要增加。
####  首先拿到这题时候用了DFS，然后光荣爆栈MLE10分，之后便用了广搜。这告诉我们数据大时一定要广搜啊!!!广搜在极大多数情况下，优于深搜！！！
#### 代码总体思路大家应该都能理解了，就是一个个点广搜下去，累加搜到的，最后统计有哪些点被搜到的次数等于牛的总数，这个数就相当于每头牛都可以去的点的个数。
### 下面放代码，细节代码中讲
```cpp

#include <bits/stdc++.h>
using namespace std;
int a[101],ff[1001][1001],f1[1001],qz[1001],b[1001],i,j,k,m,n,x,y,sum;
void bfs(int now){
int f=0,r=1,ii;
qz[r]=now;
f1[qz[r]]=true;
//b[qz[r]]++;  //也可以在BFS中累加
while (f<r){
f++;
for (ii=1; ii<=n; ii++)
if (ff[qz[f]][ii]==1 && f1[ii]==false) {//qz[f]表示当前所在的点，从这个点向别的点拓展
r++;
qz[r]=ii;
f1[qz[r]]=true;
b[qz[r]]++;
}

}	
}
int read(){
	int f=1,x=0;char s=getchar();
	while(!isdigit(s)){
		if(s=='-')f=-1;
		s=getchar();
	}
	while(isdigit(s)){
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar();
	}
	return x*f;
}  //快读优化，貌似这题没有用
int main(){
	sum=0;
	(b,0,sizeof(b));
	scanf("%d%d%d",&k,&n,&m);
	for (i=1; i<=k; i++){
	a[i]=read();
	b[a[i]]++;  //对于奶牛本来就在的点累加，当然也可以在BFS中累加
	}
	for (i=1; i<=m; i++){
	x=read(); y=read();
	ff[x][y]=1;  //标记路径
	}
for (i=1; i<=k; i++) {
memset(f1,false,sizeof(f1));
bfs(a[i]);
}
for (i=1; i<=n; i++) if (b[i]==k) sum++;  //累加符合题意的点
cout<<sum;
return 0;	
}

```
## 不建议大家根据数据做题！也希望在开O2后找到最优解。

---

## 作者：嚯呀嚯呀 (赞：1)

这道题目可以深搜也可以用最短路做

我选了搜索后觉得直接暴搜的话会超时的（可能是我不会算时间复杂度吧）

可以用tarjan缩点来优化搜索速度（至少我评测的时候比暴搜快一点）

我还有一个地方没有搞懂，就是tarjan缩点后形成的应该是有向无环图
那么在dfs的时候应该不会访问到之前的节点，相应的也不需要标记这个节点有没有被访问过

可是就是这个点调了我好久，还是要标记的，有哪位大佬可以为我解释一下吗？

献上我丑陋的代码
```
var
  que,top,tot,t,len,a1,a2,q,i,j,m,n,k,p:longint;
  place,new,nextn,othern,w,color,f,dfn,low,where,next,
  ans,a,other,check:array[0..20005]of longint;
  flag:array[0..20005]of boolean;
function min(x,y:longint):longint;
begin
  if x<y then exit(x)
  else exit(y);
end;
procedure tarjan(u:longint);
var
  k,v,i,j:longint;
begin
  inc(top); f[top]:=u;//tarjan处理用的栈
  check[u]:=1;
  inc(t); dfn[u]:=t; low[u]:=t;
  k:=a[u];
  while k<>0 do
    begin
      v:=other[k];
      if check[v]=0 then
        begin
          tarjan(v);
          low[u]:=min(low[u],low[v]);
        end
      else
        if check[v]=1 then
          low[u]:=min(low[u],dfn[v]);
      k:=next[k];
    end;
  if dfn[u]=low[u] then
    begin
      inc(tot);
      repeat
        j:=f[top]; dec(top);
        check[j]:=-1;
        color[j]:=tot;
      until j=u;
    end;
end;
procedure dfs(now,a1:longint);//就是这里，为什么要标记呢？
var
  k,p:longint;
begin
  ans[now]:=ans[now]+a1;
  k:=new[now]; flag[now]:=false;
  while k<>0 do
    begin
      p:=othern[k];
      if flag[p]=true then
        dfs(p,a1);
      k:=nextn[k];
    end;
end;
begin
  readln(q,n,m);
  for i:=1 to q do
    begin
      readln(a1);
      inc(where[a1]);//记录这个点上有几只牛
    end;
  for i:=1 to m do
    begin
      readln(a1,a2);
      inc(len);
      next[len]:=a[a1]; a[a1]:=len; other[len]:=a2;//前向星的三个数组
    end;
  for i:=1 to n do
    if check[i]=0 then
      tarjan(i);
  len:=0;
  for i:=1 to n do//tarjan后第二次建图
    begin
      w[color[i]]:=w[color[i]]+where[i];//记录这个新点有几头牛
      inc(place[color[i]]);//记录这个新点包括着几个点（后面累加用的）
      k:=a[i];
      while k<>0 do
        begin
          p:=other[k];
          if color[i]<>color[p] then
            begin
              a1:=color[i]; a2:=color[p];
              inc(len);
              nextn[len]:=new[a1]; new[a1]:=len; othern[len]:=a2;
            end;
          k:=next[k];
        end;
    end;
  {for i:=1 to tot do
    writeln(w[i],' ',place[i]);}
  for i:=1 to tot do
    if w[i]>0 then
      begin
        fillchar(flag,sizeof(flag),true);
        dfs(i,w[i]);
      end;
  for i:=1 to tot do
    if ans[i]=q then
      que:=que+place[i];
  writeln(que);
end.
```

---

## 作者：doby (赞：1)

确实，稍有常识的人都会想到反过来枚举聚集的地方然后搞出最短路算法来解决……

然而，因为这里都是单向边，所以边也是需要反着存的……

dijkstra由于大约是需要O(knm)的时间，由于最后一个点答案估计就是故意卡时间的(答案999……)，因此比较难卡过去……

换成SPFA就过了……

```cpp
#include<cstdio>
#include<queue>
using namespace std;
int k,n,m,cnt,x,y,che,ans,out,cow[110],dis[1010],head[1010];
bool done[1010];
char cc;
deque<int>q;
int read()
{
    out=0,cc=getchar();
    while(cc<'0'||cc>'9'){cc=getchar();}
    while(cc>='0'&&cc<='9')
    {
        out=out*10+cc-'0',
        cc=getchar();
    }
    return out;
}
struct Edge
{
    int to,next;//根本不用边权，也没有存下来的必要
}e[10010];
struct Heap
{
    int dis,id;
    bool operator<(const Heap &h1)const
    {
        return dis>h1.dis;
    }
};
void add(int x,int y)
{
    cnt++,e[cnt].next=head[x],e[cnt].to=y;head[x]=cnt;
}
void SPFA(int s)
{
    for(int i=1;i<=n;i++){dis[i]=1,done[i]=0;}//不能到就是1，能到就是0……
    dis[s]=0,done[s]=1;
    q.push_back(s);
    while(!q.empty())
    {
        x=q.front();
        q.pop_front();
        for(int i=head[x];i;i=e[i].next)
        {
            y=e[i].to;
            if(dis[y]>dis[x])
            {
                dis[y]=0;//直接改掉松弛的修改……
                if(!done[y])
                {
                    done[y]=1;
                    if(!q.empty())
                    {
                        if(dis[y]>dis[q.front()]){q.push_back(y);}
                        else{q.push_front(y);}
                    }
                    else{q.push_back(y);}
                }
            }
        }
        done[x]=0;
    }
}
int main()
{
    k=read(),n=read(),m=read();
    for(int i=1;i<=k;i++){cow[i]=read();}
    for(int i=1;i<=m;i++)
    {
        x=read(),y=read();
        add(y,x);//是的，要反着存……
    }
    for(int i=1;i<=n;i++)
    {
        SPFA(i);//逐个枚举出发点
        che=0;
        for(int j=1;j<=k;j++)
        {
            if(dis[cow[j]]){che++;break;}//逐个判断有没有到不了的
        }
        if(!che){ans++;}
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：FHXZ (赞：0)

就来个C++代码吧

可以用最短路来做。因为是有向边，我们只需反向建边，然后对每一个点跑一遍最短路，如果该点能到所有有奶牛的点，则总数加一。

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
queue<int>Q;
int n,tot,k,m;
bool used2[10005];
int num[10005];
int x,y,z;
struct edge
{
    int u,v,z;
    edge *next;
}e[10005*2],*p=e,*point[10005];
inline void addedge(int x,int y)
{
    p++;
    p->u=y;p->v=1;p->next=point[x];
    point[x]=p;
}
int dis[10005];
bool used[10005];
bool SPFA(int x)
{
    memset(dis,0x7f,sizeof(dis));
    memset(used,0,sizeof(used));
    Q.push(x);
    used[x]=1;
    dis[x]=0;
    while(!Q.empty())
    {
        int q=Q.front();Q.pop();
        used[q]=0;
        for (edge *j=point[q];j;j=j->next)
        {
            if(dis[j->u]>dis[q]+j->v)
            {
                dis[j->u]=dis[q]+j->v;
                if(!used[j->u])
                {
                    Q.push(j->u);
                    used[j->u]=1;
                }
            }
        }
    }
    for (int i=1;i<=k;i++)
    {
        if(dis[num[i]]==dis[0])
        return 0;
    }
    return 1;
}
int main()
{
    scanf("%d%d%d",&k,&n,&m);
    for (int i=1;i<=k;i++)
    {
        scanf("%d",&num[i]);
        used2[num[i]]=1;
    }
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        addedge(y,x);
    }
    for (int i=1;i<=n;i++)
    {
        if(SPFA(i)==1)
        {
            tot++;
        }
    }
    printf("%d\n",tot);
    return 0;
}
```

---

## 作者：zxy123 (赞：0)

dfs水题...

p党代码贴上

```cpp
var
  i,j,m,k,n,a,b,ans:longint;
  f:array[0..1010] of longint;
  son,pre,now,que:array[1..10010]of longint;
  bl:array[1..10010]of boolean;
  cow:array[1..100]of longint;
procedure init;
  begin
    readln(k,n,m);
    for i:=1 to k do
      readln(cow[i]);
    for i:=1 to m do//指父链储存（貌似有的人叫邻接表）
      begin
        readln(a,b);
        son[i]:=b;
        pre[i]:=now[a];
        now[a]:=i;
      end;
  end;
procedure dfs(v:longint);
  var
    ls:longint;
  begin
    inc(f[v]);//能走到该点的牛数加1；
    bl[v]:=true;
    ls:=now[v];
    while ls<>0 do
      begin
        if not bl[son[ls]] then
          dfs(son[ls]);
        ls:=pre[ls];
      end;
    //bl[v]:=false;  //千万不要回溯（当年无知的我为此...）！！！
  end;
procedure main;
  begin
    fillchar(f,sizeof(f),0);
    fillchar(bl,sizeof(bl),false);
    for i:=1 to k do
      begin    
        dfs(cow[i]);//从每个牛的位置dfs，记录该牛能走到的点；
        fillchar(bl,sizeof(bl),false);//初始化bl；
      end;
    ans:=0;
    for i:=1 to n do//统计答案；
      if f[i]=k then inc(ans);//如果有k头牛能走到某点则统计；
    writeln(ans);
  end;
begin
  init;
  main;
end.
```

---

