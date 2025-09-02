# Tournament

## 题目描述

The tournament «Sleepyhead-2010» in the rapid falling asleep has just finished in Berland. $ n $ best participants from the country have participated in it. The tournament consists of games, each of them is a match between two participants. $ n·(n-1)/2 $ games were played during the tournament, and each participant had a match with each other participant.

The rules of the game are quite simple — the participant who falls asleep first wins. The secretary made a record of each game in the form « $ x_{i} $ $ y_{i} $ », where $ x_{i} $ and $ y_{i} $ are the numbers of participants. The first number in each pair is a winner (i.e. $ x_{i} $ is a winner and $ y_{i} $ is a loser). There is no draws.

Recently researches form the «Institute Of Sleep» have found that every person is characterized by a value $ p_{j} $ — the speed of falling asleep. The person who has lower speed wins. Every person has its own value $ p_{j} $ , constant during the life.

It is known that all participants of the tournament have distinct speeds of falling asleep. Also it was found that the secretary made records about all the games except one. You are to find the result of the missing game.

## 样例 #1

### 输入

```
4
4 2
4 1
2 3
2 1
3 1
```

### 输出

```
4 3
```

# 题解

## 作者：Rainbow_qwq (赞：4)

[CF27B Tournament](https://www.luogu.org/problem/CF27B)

# 思路

**图的边数：**

完全图共有$\dfrac {n\times (n-1)}{2}$条边，
去掉一条边就是$\dfrac {n\times (n-1)}{2}-1$条。

使用$e[i][j]$为邻接矩阵表示$i$与$j$比赛过，读入一条边$u\rightarrow v$，就$e[\max (u,v)][\min (u,v)]=1$ (编号大的点在前面)

此时$u$为赢家，设$deg[i]$为$i$赢了多少次，则$deg[u]++$。

最后循环2遍，若$e[i][j]==0$，则$i$与$j$没比赛，把$deg$大的输出在前面，代码如下：
```cpp
if(deg[i]>deg[j])printf("%d %d\n",i,j);//比赛赢的人输出在前面
else printf("%d %d\n",j,i);
```

**AC 代码(附注释)**
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
#define TP long long
inline TP read(){//快读
    char c=getchar();TP x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int n,e[55][55],deg[55];
int main()
{
	n=read();
	int m=n*(n-1)/2-1;//边数
	For(i,1,m){//边数
		int u=read(),v=read();
		e[max(u,v)][min(u,v)]++;//编号大的点在前面
		deg[u]++;//u赢了比赛，出度+1
	}
	For(i,1,n)
		For(j,1,i-1)
			if(!e[i][j]){
				if(deg[i]>deg[j])printf("%d %d\n",i,j);//比赛赢的人输出在前面
				else printf("%d %d\n",j,i);
			}
	return 0;
}
```

---

## 作者：Moon_Lighter (赞：3)

## 题意：
 $n$ 个人， $n*(n-1)/2-1$ 对数，表示比赛，

每个人都和其他 $n-1$ 个人比一场， 第 $1$ 个人胜，找出缺少的一组比赛输出。

---
## 分析&思路：
每个人比 $n-1$ 场，比赛场次不是 $n-1$ 的两个数 $x,y$ 即为答案，

还需确定两人的胜败，有前面的比赛可以记录比每个人的强的对手，

若比 $x$ 强的对手中有 $y$ 或 $x$ 的强手的强手中有 $y$ ,

即 $y$ 比 $x$ 强，否则 $x$ 比 $y$ 强。

---
## 代码:
```cpp
#include<bits/stdc++.h>
#define inf 10000000
#define pi acos(-1.0)
#define eps 1e-8
#define seed 131
#define min(a,b) a<b?a:b
#define max(a,b) a<b?b:a
using namespace std;
typedef pair<int,int> pa;
typedef unsigned long long ULL;
typedef long long LL;
const int maxn=100005;
int d[55];
vector<int>vec[55];
int main()
{
    int n;
    scanf("%d",&n);
    int num=n*(n-1)/2-1;
    memset(d,0,sizeof(d));
    int a,b;
    for(int i=1;i<=num;i++)
    {
        scanf("%d%d",&a,&b);
        vec[b].push_back(a);
        d[a]++;
        d[b]++;
    }
    int u[2];
    int e=0;
    for(int i=1;i<=n;i++)
    {
        if(d[i]!=n-1)
            u[e++]=i;
    }
    bool flag=true;
    for(int i=0;i<vec[u[0]].size();i++)
    {
        if(vec[u[0]][i]==u[1]||find(vec[vec[u[0][i]].begin(),vec[vec[u[0]][i]].end(),u[1])!=vec[vec[u[0]][i]].end())
        {
            flag=false;
            break;
        }
    }
    if(flag)
        printf("%d %d\n",u[0],u[1]);
    else
        printf("%d %d\n",u[1],u[0]);
    return 0;
}
```

---

## 作者：ZVitality (赞：2)

补充一下 [这篇](https://www.luogu.com.cn/blog/zxy-11/solution-cf27b) 的没有讲解清楚的地方。

这个比赛有一个特点，就是他们的排名不会有说爆冷门的这种情况。换而言之，他们的实力**严格满足不等式**。

具体来说，假设 $x>y,y>z$，则 $x>z$。

所以就很好解释了，如果 $x>y,y>z$，那么 $x$ 的排名比 $z$ 高，所以 $z$ 能战胜的，$x$ 也一定能战胜。所以我们可以看 $x$ 战胜的多还是 $z$ 战胜的多来确定他们的排名，从而得出 $x$ 与 $z$ 打谁会赢。

---

## 作者：Milthm (赞：1)

## CF27B 题解

### 题目大意

这题翻译好像不太对，正确翻译应该是：

$n$ 个人比了 $\frac{n(n-1)}{2}-1$ 场比赛，有两个人少比了一次，现在要按照两人的**胜场次数**输出两人的编号（其中每次输入前面的赢了后面的）。

### 题目解法

完全竞赛图，也就是通过在无向完全图中为每个边缘分配方向而获得的有向图。对于这样的一个完全的图，它每个点肯定连接着 $n-1$ 个点（除了它以外所有的点）。所以我们就可以统计每个点的出度入度和，不是 $n-1$ 的两个点就是答案。

至于排名吗，可以统计每个人赢了几次，然后进行判断就可以了。

### AC代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[5000],x,y,q[2],p,b[5000];//其中q[2]是两个没比的元素
int main(){
    cin>>n;
    for(int i=1;i<=n*(n-1)/2-1;i++){
        cin>>x>>y;
        a[x]++;a[y]++;//x和y的出度入度和统计
        b[x]++;//赢了的统计
    }
    for(int i=1;i<=n;i++){
        if(a[i]!=n-1){//判断特殊元素
            q[p++]=i;
        }
    }
    if(b[q[0]]>b[q[1]])cout<<q[0]<<" "<<q[1];//比较两个人谁赢得多谁先输出
    else cout<<q[1]<<" "<<q[0];
    return 0;
}
```




---

## 作者：Mistybranch (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF27B)

题目大概意思是：有 $n$ 个人，比了 $\dfrac{n \times (n - 1)}{2} - 1$ 场比赛（也就是说每个人都与其他 $n - 1$ 个人比一场，现在缺少一组比赛），找出缺少的一组比赛（第一个是胜者，第二个人是败者）。

一道图论的题，思路还是蛮清晰的：

- 首先我们知道，除了两个缺少一组比赛的人以外，其余的人比了 $n - 1$ 场，所以说比赛场次非 $n - 1$ 的两个人（记为 $u$ 和 $v$）即为答案。

```cpp
for (int i = 1; i <= n * (n - 1) / 2 - 1; i++) {
	scanf("%d %d", &u, &v);
	
	e[v].push_back(u);
	cc[u]++;
	cc[v]++;
}

u = -1;

for (int i = 1; i <= n; i++) {
	if (cc[i] != n - 1) {
		if (u == -1) {
			u = i;
		}
		
		else {
				v = i;
			break;
		}
	}
}
```

- 我们还需要确定两个人的胜败，$e_i$ 记录的是打败 $i$ 的所有选手，即为比 $i$ 强的选手，若比 $u$ 强的选手中有 $v$ 或 $u$ 的强手中的强手中有 $v$，则 $v$ 比 $u$ 强，否则 $u$ 比 $v$ 强。

```cpp
bool flag = true;

for (int i = 0; i < e[u].size(); i++) {
	if (e[u][i] == v || find(e[e[u][i]].begin(), e[e[u][i]].end(), v) != e[e[u][i]].end()) {
		flag = false;
		break;
	}
}

if (flag) {
	printf("%d %d\n", u, v);
}

else {
	printf("%d %d\n", v, u);
}
```
完整代码：

```cpp


#include <bits/stdc++.h>
#include <vector>

using namespace std;

int n, m, h[59], cc[59];
vector<int>e[59];

int main () {
	int u, v;
	bool flag = true;
	
	scanf("%d", &n);
	
	for (int i = 1; i <= n * (n - 1) / 2 - 1; i++) {
		scanf("%d %d", &u, &v);
		
		e[v].push_back(u);
		cc[u]++;
		cc[v]++;
	}
	
	u = -1;
	
	for (int i = 1; i <= n; i++) {
		if (cc[i] != n - 1) {
			if (u == -1) {
				u = i;
			}
			
			else {
				v = i;
				break;
			}
		}
	}
	
	for (int i = 0; i < e[u].size(); i++) {
		if (e[u][i] == v || find(e[e[u][i]].begin(), e[e[u][i]].end(), v) != e[e[u][i]].end()) {
			flag = false;
			break;
		}
	}
	
	if (flag) {
		printf("%d %d\n", u, v);
	}
	
	else {
		printf("%d %d\n", v, u);
	}
	
	return 0;
}
```

---

## 作者：ktq_cpp (赞：0)

# [题面](https://www.luogu.com.cn/problem/CF27B)

## 题目大意

给你一个有 $\frac{n\times(n-1)}{2}$ 条边的有向无环图，我们要添加一条边使得这个图完整且没环。

## 思路

提到有向无环图，我们第一时间要想到拓扑排序，我们令 $dep[i]$ 表示第 $i$ 个节点沿着反图走最远能走多远，不难看出，假设这张图中 $x$ 和 $y$ 之间没边的话，我们可以直接比较 $dep[x]$ 和 $dep[y]$ 的大小，然后确定边的方向。

具体细节见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
#define repe(i,l,r) for(int (i)=l;(i)<=r;(i)++)
#define rep(i,n) for(int (i)=1;(i)<=n;(i)++)
#define FOR(i,r,l) for(int (i)=r;(i)>=l;(i)--)
#define INF 0x3f3f3f
#define pii pair<int,int>
#define mpr make_pair
#define pb push_back
#define ALL(v) (v).begin(),(v).end()
#define rsort(v) sort(ALL(v),greater<int>())
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
using namespace std;
int read(){int sum=0,f=1;char c;c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){sum=(sum<<1)+(sum<<3)+(c-'0');c=getchar();}return sum*f;}
void out(int x){if(x<0){x=-x;putchar('-');}if(x>=10)out(x/10);putchar(x%10+'0');}
template <typename T>void die(T s){cout<<s<<endl;exit(0);}
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
template <typename T>void chkmax(T& a,T b){if(a<b)a=b;return;}
template <typename T>void chkmin(T& a,T b){if(a>b)a=b;return;}
int n,in[55],dep[55];
vector<int> G[55];
bool mp[55][55];
void topo(){
	queue<int> q;
	for(int i=1;i<=n;i++)if(!in[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto v:G[u]){
			chkmax(dep[v],dep[u]+1);
			if(!--in[v]){
				q.push(v);
			}
		}
	}
	return;
}
signed main(){
	n=read();
	rep(i,(n-1)*n/2-1){
		int u=read(),v=read();
		in[v]++;
		G[u].pb(v);
		mp[u][v]=mp[v][u]=1;
	}
	topo();
	rep(i,n){
		repe(j,i+1,n){
			if(!mp[i][j]){
				if(dep[i]<dep[j])cout<<i<<' '<<j<<endl;
				else cout<<j<<' '<<i<<endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：_maze (赞：0)

憨批题



------------
首先我们知道，这个图是一个完全图对吧，所以他的边数显然就是 $n * (n - 1) / 2$ ，每一个点连 $n - 1$ 条边。

然后我第一次交的时候就判断，看看哪两个点的度数小于 $n - 1$ 。

但这是错的

嗯其实这个竞赛图呢，就是说给完全图的每一条边标了方向

完全竞赛图呢，网上找不到任何资料。我个人的理解就是完全竞赛图是一个有向完全图，且图中每一个点入度都不一样。

然后就发现这道题可以说是很憨了，建议大家回去再想想，毕竟数据范围 50 。

我们按入度排个序，如果入度相同出度大的往前排（想一想，如果不这么干会会怎么样），每次判断出度加入度（也就是边数）是不是等于 $n - 1$ 。不等于时查看当前点的入度是不是按 $0$ 到 $n - 1$ 排列的。如果是把点加入有向边的起点，否则加入终点。

看起来很麻烦，但复杂度就是排序的复杂度，为 $O(nlog(n))$ 目前 (2021/11/19) 最优解，开 O2 能更快

如果看不明白可以看代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int chu, ru, id;
}p[55];
int n;
bool cmp(node u, node v){
    return u.ru < v.ru || (u.ru == v.ru && (u.ru + u.chu == n - 1));//不会找到终点时将他归到起点的位置
}
int id[55];
int main(){
    scanf("%d", &n);
    int u, v;
    for(int i = 1;i < n * (n - 1) / 2;i ++){
        scanf("%d%d", &u, &v);
        p[u].ru ++;
        p[v].chu ++;
    }
    for(int i = 1;i <= n;i ++)
        p[i].id = i;
    sort(p + 1, p + n + 1, cmp);
    for(int i = 1;i <= n;i ++){
        if(p[i].chu + p[i].ru != n - 1){
            if(p[i].ru != i - 1)
                u = p[i].id;
            else
                v = p[i].id;
        }
    }
    cout << u << ' ' << v << endl;
    return 0;
}
```


---

## 作者：Fool_Fish (赞：0)

首先我们是可以很容易的得到缺失的那条边的两端

但是这道题是有向的，那么我们就需要知道到底是谁赢了谁


引理：如果一个人赢的场次比另一个人多，那么这个人的实力就应该要强一点呀

但是这只是一个很zz的感觉，显然需要一些些可能并不是很严谨但可以理解的证明

如下

假设一张已经完全的图中有两个点 $a,b$，现在 $a$ 的出度是要比 $b$ 多的

设 $b$ 的出度为 $x,x\in \mathbb{Z}$，$a$ 的出度为 $x+k,k>0,k\in \mathbb{Z}$

反证法：假设有一条边从 $b$ 连向 $a$

$ \because a$ 的出度为 $x+k$

$\therefore$ 图中有 $x+k+2$个点被 $a$ 打败

又 $\because b$ 的出度为 $x$

$\therefore$ 图中有 $k+2$个点被 $a$，打败，又打败的 $b$，这与$b$打败了$a$显然不符

矛盾

所以一定有一条边从 $a$ 连向 $b$


那么我们统计出度就行了呀awa

code

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int MAXN=55;
bool g[MAXN][MAXN];
int out[MAXN];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1,u,v;i<=(n*(n-1)/2-1);i++){
		scanf("%d %d",&u,&v);
		g[u][v]=g[v][u]=true;
		out[u]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(g[i][j]==0 && i!=j){
				if(out[i]<out[j]){
					printf("%d %d",j,i);
				}
				else{
					printf("%d %d",i,j);
				}
				return 0;
			}
		}
	}
return 0;
}
``

---

## 作者：封禁用户 (赞：0)

### 前言

这道题目真的是绿的吗。。。

我怎么那么不信呀！

### 分析

这道题目实际上就是问你一个，完全竞赛图是什么？

完全竞赛图是一种有向边完全图，就是说，每个点之间都会有一个有向边。

当然，如果你说这道题目就是问你完全竞赛图少了哪条边，那是不对的！

如果你好好阅读了英文的题面，就会发现，实际上这个图是可以间接比出他们两个的能力值。

举个例子吧！

就比如说：
```
1 <- 2 

2 <- 3

4 -> 3

4 -> 2

3 -> 1
```
箭头后面的那个人是偏弱的人。

我们可以间接的发现 `4 -> 1`。

那么为什么呢？

~~这个自己推一下不就好了吗？~~

我们可以发现某种神奇的规律：

就是说，如果一个点的出度大于另一个点的出度那么一个点就比另一个点要强！

那么这又是为什么呢？

就假设，这个是一张缺了一条边的完全竞赛图，那么如果说点 $a$ 的出度为 $2$ ，点 $b$ 出度为 $1$ 。

那么我们可以发现，必定点 $a$ 是至少存在一个点比点 $b$ 强！

如果说，一个点被点 $b$ 给对掉了，就像下面这种情况：

```
a -> c
b -> c
```

那么点 $a$ ，还是存在着一条边间接的可以大于点 $b$ 的！

因为点 $b$ 不存在着另一条出度可以对掉！

哦，对了，如果说点 $b$ 间接大于了 点 $a$ ，那么就会产生矛盾的形式！

所以规律也就得出了！

**如果说一个点的出度大于另一个点那么这个点就是要先输出，那个点其次输出**。

如果等于呢？

~~那就随便输出呀，反正 CF 有 SPJ！~~

还是从小到大输出吧，保险一点！

### 代码

代码真的没有什么好看的了 。。。。

```
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=55;
int n,vis[INF];
bool Map[INF][INF];
signed main()
{
	scanf("%d",&n);
	int m=n*(n-1)/2-1;//计算边数。
	for (int i=1;i<=m;i++) {
		int x=0,y=0;
		scanf("%d %d",&x,&y);
		Map[x][y]=Map[y][x]=1;//防止有某种玄学的情况出现。
		vis[x]++;//统计出度。
	}
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++) {
			if (!Map[i][j]) {//如果没有比较过。
				if (vis[i]>vis[j]) printf("%d %d\n",i,j);//如果大于那么先输出大于的那个点。
				else printf("%d %d\n",j,i);//否则输出另一个大于的点。
				return 0;
			}
		} 
	return 0;
}//提交同样的代码会 UKE！
```

### 写在后面的话

我这篇题解如果有错误请在评论区指出，我将非常感谢指出的人！

**谢谢观赏！**

---

## 作者：luan341502 (赞：0)

水题，建议橙。

我们找出边数不为 $n-1$ 的两个点，由于是竞赛图，这两个点之间一定没有连边。

考虑输出先后顺序，由于第一个人赢，所以赢的次数多的人输出在前。

判断输赢次数输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d[55],d_[55];
vector<int> ans;
void solve(){
	cin>>n;
	for(int i=1;i<n*(n-1)/2;i++){
		int u,v;cin>>u>>v;
		d[u]++,d[v]++;
		d_[u]++;
	}
	for(int i=1;i<=n;i++) if(d[i]^(n-1)) ans.push_back(i);
	if(d_[ans[0]]>d_[ans[1]]) cout<<ans[0]<<" "<<ans[1]<<"\n";
	else cout<<ans[1]<<" "<<ans[0]<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	/*int tt;cin>>tt;while(tt--)*/solve();
	return 0;
}
```


---

