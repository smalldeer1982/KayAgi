# Looking for Order

## 题目描述

Lena喜欢秩序井然的生活。一天，她要去上大学了。突然，她发现整个房间乱糟糟的——她的手提包里的物品都散落在了地上。她想把所有的物品都放回她的手提包。但是，这里有一点问题：她一次最多只能拿两个物品，她也不能移动她的手提包。并且，因为她爱整洁的习惯，如果她拿起了一个物品，她也不能将它放在其他地方，除非放回她的手提包。

Lena把她的房间划分为了一个平面直角坐标系。现在Lena给你她的手提包和每个散落的物品的坐标（当然，一开始的时候她就和手提包站在一个地方）。她从坐标 $(x1,y1)$  走到坐标 $(x2,y2)$  需要用 $(x1-x2)^2+(y1-y2)^2$  单位的时间。现在，Lena将告诉你她的房间的情况，请你为Lena找到一个拾起每个物品的顺序，使她拾起所有物品所需的总时间最小。当然，Lena最后需要返回她的手提包。

## 样例 #1

### 输入

```
0 0
2
1 1
-1 1
```

### 输出

```
8
0 1 2 0 
```

## 样例 #2

### 输入

```
1 1
3
4 3
3 4
0 0
```

### 输出

```
32
0 1 2 0 3 0 
```

# 题解

## 作者：Prurite (赞：17)

建议一层一层地阅读，只在实在想不出来的时候再看下一层。

## 基本思路
状压DP。以当前已经取了哪些物品作为状态。

## 主要思路
拿到题， $n<=24$ 的数据范围和512MB的空间限制基本上就标志着这道题是一个标准的状压。为了节省空间，我们就 $1<<i-1$ 表示第 $i$ 个物品有无被取过。由于一次可以选择拿一个或者两个物品，考虑在状态转移的时候枚举这次拿的两个物品（如果两个物品相同就处理为这次只拿一个）。由于要输出拿的方法，我们就再用一个数组记录当前状态是从之前的哪个状态转移过来的即可。

需要注意的是，可以证明，若设每次离开手提包捡拾物品为一次，则各次之间的顺序不影响最终答案。如，第一次拿物品1，第二次拿物品2,3与第一次拿物品2,3，第二次拿物品1的所用时间是一样的。这样，我们在转移的时候就从编号小的物品向编号大的物品找寻，只要找到了当前的一种可用方案就可以进入下一个状态了，这样可以节省时间（同时避免重复计算）。

## 代码实现
用dis数组表示两点之间的距离，用dp数组表示当前状态下所需的最小时间，用pre数组表示当前状态的来路（从哪个状态转移过来的）。
状态转移方程：顺推，
$$ dp[m|(1<<i-1)|(1<<j-1)]=min( dp[m|(1<<i-1)|(1<<j-1)], dp[m]+dis[0][i]+dis[i][j]+dis[j][0] ) $$

输出的时候从 $pre[(1<<n-1)-1]$ 往前逆推即可。

## 代码
```cpp
#include <stdio.h>

const int MAXN=24, INF=2e9;
struct obj
{
    int x, y;
} things[MAXN+1];
int n;
int dp[1<<MAXN|1], pre[1<<MAXN|1];
int dis[MAXN+1][MAXN+1];

inline void reset( );	//重置数组 
inline void read( );	//读入数据 
inline void init( );	//预处理 
inline void solve( );	//解决 
inline void output( );	//输出 

inline int min( int a, int b ) { return a<b?a:b; }

int main( )
{
    reset( );
    read( );
    init( );
    solve( );
    output( );
    return 0;
} //疯狂的主程序

inline void reset( )
{
    for ( register int i=0; i<=(1<<MAXN); i++ )
        dp[i]=INF, pre[i]=0;
    return;
}

inline void read( )
{
    scanf( "%d %d", &things[0].x, &things[0].y ); //用0表示手提包
    scanf( "%d", &n );
    for ( register int i=1; i<=n; i++ )
        scanf( "%d %d", &things[i].x, &things[i].y );
    return;
}

inline void init( )
{
    for ( register int i=0; i<=n; i++ )
        for ( register int j=0; j<=n; j++ )
            dis[i][j]=dis[j][i]=
            (things[i].x-things[j].x)*(things[i].x-things[j].x)+
            (things[i].y-things[j].y)*(things[i].y-things[j].y);
    return;
}

inline void solve( )
{
    dp[0]=0, pre[0]=0;
    for ( int m=0; m<(1<<n); m++ ) //m为当前处理的状态
    {
        if ( dp[m]==INF )
            continue; //如果当前状态没有被更新过直接continue 
        for ( int i=1; i<=n; i++ )	
        {
            if ( m&1<<i-1 )
                continue;
            for ( int j=1; j<=n; j++ )
            {
                if ( m&1<<j-1 )
                    continue;
                if ( dp[m|(1<<i-1)|(1<<j-1)]>dp[m]+dis[0][i]+dis[i][j]+dis[j][0] )
                    dp[m|(1<<i-1)|(1<<j-1)]=dp[m]+dis[0][i]+dis[i][j]+dis[j][0],
                    pre[m|(1<<i-1)|(1<<j-1)]=m; //状态转移 
            }
            break; //只要找到了一种可行的方案，无论是否转移成功都可以break了 
        }
    }
    return;
}

inline void output( )
{
    printf( "%d\n", dp[(1<<n)-1] );
    int now=(1<<n)-1; //从所有都齐的状态开始逆推
    while ( now!=0 )
    {
        printf( "0 " ); 
        int update=now^pre[now];
        for ( int i=1; i<=n; i++ )
            if ( update&1<<i-1 )
                printf( "%d ", i ); //输出本次拿的哪些物品
        now=pre[now];
    }
    printf( "0\n" );
    return;
}
```
[提交记录 用时: 2346ms / 内存: 134580KB](https://www.luogu.org/record/show?rid=6605980)

---

## 作者：xtx1092515503 (赞：9)

看看这丧 心 病 狂的提交次数……

![](https://cdn.luogu.com.cn/upload/image_hosting/q9zcyip4.png)

不用说，如果你们看到交了整整一整版，应该能猜到用的是什么神奇算法——

# 模 拟 退 火

马上我们将会看到是如何从WA12到WA25再到WA31直到AC的惨痛经历。

初版代码（随机WA10~12左右）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define x first
#define y second
pii a[50];
vector<int>tmp[50];
int n,m,res,ans[50],DIS[50][50],p[50];
int dis(int u,int v){
	return (a[u].x-a[v].x)*(a[u].x-a[v].x)+(a[u].y-a[v].y)*(a[u].y-a[v].y);
}
int calc(int *ip){
	int ret=0;
	for(int i=1;i<=m;i++)tmp[ip[i]].push_back(i);
	for(int i=1;i<=n;i++)ret+=DIS[0][tmp[i][0]]+DIS[tmp[i][0]][tmp[i][1]]+DIS[tmp[i][1]][0],tmp[i].clear();
	return ret;
}
double delta=0.99993;
void SA(){
	memcpy(p,ans,sizeof(ans));
	double T=5000;
	while(T>1e-10){
		T*=delta;
		int x=rand()%m+1,y=rand()%m+1;
		if(p[x]==p[y])continue;
		if(x>n&&y>n)continue;
		swap(p[x],p[y]);
		int now=calc(p);
		int DELTA=now-res;
		if(DELTA<0)res=now,memcpy(ans,p,sizeof(p));
		else if(exp(DELTA/T)*RAND_MAX>rand())swap(p[x],p[y]);
	}
}
void CALC(){
	SA(),SA(),SA(),SA(),SA();
}
int main(){
	scanf("%d%d",&a[0].x,&a[0].y),srand(3423424);
	scanf("%d",&n),m=2*n;
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y),a[i].x-=a[0].x,a[i].y-=a[0].y;
	a[0].x=a[0].y=0;
	for(int i=1;i<=m;i++)ans[i]=(i+1)/2;
//	for(int i=0;i<=m;i++)printf("(%d,%d)\n",a[i].first,a[i].second);
	for(int i=0;i<=m;i++)for(int j=0;j<=m;j++)DIS[i][j]=dis(i,j);
//	for(int i=0;i<=m;i++){for(int j=0;j<=m;j++)printf("%d ",DIS[i][j]);puts("");}
	random_shuffle(ans+1,ans+m+1);
	res=calc(ans);
//	printf("%d\n",res);
	CALC();
//	printf("%d\n",calc(ans));
//	for(int i=1;i<=m;i++)printf("%d ",ans[i]);puts("");
	printf("%d\n",res);
	printf("%d ",0);
	for(int i=1;i<=m;i++)tmp[ans[i]].push_back(i);
	for(int i=1;i<=n;i++){
		if(tmp[i][0]<=n)printf("%d ",tmp[i][0]);
		if(tmp[i][1]<=n)printf("%d ",tmp[i][1]);
		if(tmp[i][0]<=n||tmp[i][1]<=n)printf("%d ",0);
	}
	return 0;
}
```
思路：发现那些一次只拿走一个物品的情况比较麻烦。我们不如再额外加进来$n$个位置就在包包处的物品，这样就可以两两分配位置了。但是，这样一遍计算下来复杂度就是$O(2n)$的，因此算不了多少遍就光荣扑街。

二版代码：（随机WA/TLE20~30，取决于玄学调参）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define x first
#define y second
pii a[50];
vector<int>tmp[50];
int n,m,half,res,ans[50],DIS[50][50],p[50];
inline int dis(int u,int v){
	return (a[u].x-a[v].x)*(a[u].x-a[v].x)+(a[u].y-a[v].y)*(a[u].y-a[v].y);
}
inline int calc(int *ip){
	register int ret=0;
	for(register int i=1;i<=m;i++)tmp[ip[i]].push_back(i);
	for(register int i=1;i<=half;i++)ret+=min(DIS[0][tmp[i][0]]*2+DIS[0][tmp[i][1]]*2,DIS[0][tmp[i][0]]+DIS[tmp[i][0]][tmp[i][1]]+DIS[tmp[i][1]][0]),tmp[i].clear();
	return ret;
}
double delta=0.99996;
inline void SA(){
	memcpy(p,ans,sizeof(ans));
	register double T=1000;
	while(T>1e-14){
		T*=delta;
		register int x=rand()%m+1,y=rand()%m+1;
		if(p[x]==p[y])continue;
		swap(p[x],p[y]);
		register int now=calc(p);
		register int DELTA=now-res;
		if(DELTA<0)res=now,memcpy(ans,p,sizeof(p));
		else if(exp(-DELTA/T)*RAND_MAX<rand())swap(p[x],p[y]);
	}
}
inline void CALC(){
	while ((double)clock()/CLOCKS_PER_SEC<3.9) SA();
}
inline void read(int &x){
	x=0;
	char c=getchar();
	int flag=1;
	while(c>'9'||c<'0')flag=(c=='-'?-1:1),c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x*=flag;
}
inline void print(int x){
	if(x<=9)putchar('0'+x);
	else print(x/10),putchar('0'+x%10);
}
int main(){
	read(a[0].x),read(a[0].y),srand(time(0));
	read(n);
	for(register int i=1;i<=n;i++)read(a[i].x),read(a[i].y),a[i].x-=a[0].x,a[i].y-=a[0].y;
	a[0].x=a[0].y=0;
	m=n;
	if(m&1)m++;
	half=m/2;
	for(register int i=1;i<=m;i++)ans[i]=(i+1)/2;
//	for(int i=0;i<=m;i++)printf("(%d,%d)\n",a[i].first,a[i].second);
	for(register int i=0;i<=m;i++)for(register int j=0;j<=m;j++)DIS[i][j]=dis(i,j);
//	for(int i=0;i<=m;i++){for(int j=0;j<=m;j++)printf("%d ",DIS[i][j]);puts("");}
	random_shuffle(ans+1,ans+m+1);
	res=calc(ans);
	CALC();
//	printf("%d\n",calc(ans));
//	for(int i=1;i<=m;i++)printf("%d ",ans[i]);puts("");
	printf("%d\n",res);
	printf("%d ",0);
	for(register int i=1;i<=m;i++)tmp[ans[i]].push_back(i);
	for(register int i=1;i<=half;i++){
		if(tmp[i][0]<=n&&tmp[i][1]<=n){
			if(DIS[0][tmp[i][0]]*2+DIS[0][tmp[i][1]]*2<DIS[0][tmp[i][0]]+DIS[tmp[i][0]][tmp[i][1]]+DIS[tmp[i][1]][0])printf("%d 0 %d ",tmp[i][0],tmp[i][1]);
			else printf("%d %d ",tmp[i][0],tmp[i][1]);
		}else{
			if(tmp[i][0]<=n)printf("%d ",tmp[i][0]);
			if(tmp[i][1]<=n)printf("%d ",tmp[i][1]);		
		}
		if(tmp[i][0]<=n||tmp[i][1]<=n)printf("%d ",0);
	}
	return 0;
}
```
发现到底需不需要一次只拿一个可以在计算时算出来：如果分在一组内的两个东西合在一起拿更好，就合在一起；分开拿更好，就分开来；这样就不需要加入$n$个物品，只需要在$n$是奇数时加入一个物品即可。同时经历一大堆玄学卡常，最成功的一次是WA31，一共35个点。

最终代码：

实在被搞得头昏脑胀的我决定尝试一些新思路。比如，不模拟退火，纯随机；或是采取爬山法，不接受更劣的答案。

下面的代码是随机10000次，再爬山50000次，然后能模拟退火就模拟退火的代码，结果AC了：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define x first
#define y second
pii a[50];
vector<int>tmp[50];
int n,m,half,res,ans[50],DIS[50][50],p[50];
inline int dis(int u,int v){
	return (a[u].x-a[v].x)*(a[u].x-a[v].x)+(a[u].y-a[v].y)*(a[u].y-a[v].y);
}
inline int calc(int *ip){
	register int ret=0;
	for(register int i=1;i<=m;i++)tmp[ip[i]].push_back(i);
	for(register int i=1;i<=half;i++)ret+=min(DIS[0][tmp[i][0]]*2+DIS[0][tmp[i][1]]*2,DIS[0][tmp[i][0]]+DIS[tmp[i][0]][tmp[i][1]]+DIS[tmp[i][1]][0]),tmp[i].clear();
	return ret;
}
double delta=0.99995;
inline void SA(){
	memcpy(p,ans,sizeof(ans));
	register double T=1000;
	while(T>1e-12){
		T*=delta;
		register int x=rand()%m+1,y=rand()%m+1;
		if(p[x]==p[y])continue;
		swap(p[x],p[y]);
		register int now=calc(p);
		register int DELTA=now-res;
		if(DELTA<0)res=now,memcpy(ans,p,sizeof(p));
		else if(exp(-DELTA/T)*RAND_MAX<rand())swap(p[x],p[y]);
	}
}
inline void CM(){
	memcpy(p,ans,sizeof(ans));
	for(int i=1;i<=50000;i++){
		register int x=rand()%m+1,y=rand()%m+1;
		if(p[x]==p[y])continue;
		swap(p[x],p[y]);
		register int now=calc(p);
		register int DELTA=now-res;
		if(DELTA<0)res=now,memcpy(ans,p,sizeof(p));
		else swap(p[x],p[y]);
	}
}
inline void CALC(){
	memcpy(p,ans,sizeof(ans));
	for(int i=0;i<10000;i++){
		random_shuffle(p+1,p+m+1);
		if(calc(p)<res)memcpy(ans,p,sizeof(p));
	}
	CM();
	while ((double)clock()/CLOCKS_PER_SEC<3.8) SA();
}
inline void read(int &x){
	x=0;
	char c=getchar();
	int flag=1;
	while(c>'9'||c<'0')flag=(c=='-'?-1:1),c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x*=flag;
}
inline void print(int x){
	if(x<=9)putchar('0'+x);
	else print(x/10),putchar('0'+x%10);
}
int main(){
	read(a[0].x),read(a[0].y),srand(time(0)),srand(rand());
	read(n);
	for(register int i=1;i<=n;i++)read(a[i].x),read(a[i].y),a[i].x-=a[0].x,a[i].y-=a[0].y;
	a[0].x=a[0].y=0;
	m=n;
	if(m&1)m++;
	half=m/2;
	for(register int i=1;i<=m;i++)ans[i]=(i+1)/2;
//	for(int i=0;i<=m;i++)printf("(%d,%d)\n",a[i].first,a[i].second);
	for(register int i=0;i<=m;i++)for(register int j=0;j<=m;j++)DIS[i][j]=dis(i,j);
//	for(int i=0;i<=m;i++){for(int j=0;j<=m;j++)printf("%d ",DIS[i][j]);puts("");}
	random_shuffle(ans+1,ans+m+1);
	res=calc(ans);
	CALC();
//	printf("%d\n",calc(ans));
//	for(int i=1;i<=m;i++)printf("%d ",ans[i]);puts("");
	printf("%d\n",res);
	printf("%d ",0);
	for(register int i=1;i<=m;i++)tmp[ans[i]].push_back(i);
	for(register int i=1;i<=half;i++){
		if(tmp[i][0]<=n&&tmp[i][1]<=n){
			if(DIS[0][tmp[i][0]]*2+DIS[0][tmp[i][1]]*2<DIS[0][tmp[i][0]]+DIS[tmp[i][0]][tmp[i][1]]+DIS[tmp[i][1]][0])printf("%d 0 %d ",tmp[i][0],tmp[i][1]);
			else printf("%d %d ",tmp[i][0],tmp[i][1]);
		}else{
			if(tmp[i][0]<=n)printf("%d ",tmp[i][0]);
			if(tmp[i][1]<=n)printf("%d ",tmp[i][1]);		
		}
		if(tmp[i][0]<=n||tmp[i][1]<=n)printf("%d ",0);
	}
	return 0;
}
```
为什么这就能过？

我们不妨口胡一下爬山算法：

很明显，这题的AC顺序有很多很多种。比如第一组样例，```0 1 2 0```是答案，```0 1 0 2 0```是答案，```0 2 0 1 0```还是答案！

这就意味着我们爬山有很大概率能幸运的爬到正确的山上去。

然后我交了一发纯爬山，无模拟退火的代码上去，然后WA了。

**它WA了！它WA了！它WA了！**

这说明爬山法并非完全正确的。还是要加上模拟退火瞎退退才能退出答案来。

不管怎么说，这题确实在模拟退火方面给予了我很大的启发：怎样优化，怎样卡常，怎样与其它玄学算法相结合……

---

## 作者：Rosmarinus (赞：8)

[更好的阅读体验](https://www.cnblogs.com/XJ21/p/14668689.html)

## 思路分析

一看数据 $n\le 24$，啊很快啊，啪的一下，我们就会想到， $2^{24}=16,777,216$，对于 `dfs` 暴力来说有点大，但是我们可以选择用状压。诶状压，把它记在脑子里。

接下来考虑题目的具体要求：

>从起点出发，取走至多两个物品，再回到起点，重复此过程直到物品被取完。

我们令起点为 $0$，用 $dis_{i,j}$ 表示物品 $i$ 到物品 $j$ 之间的距离，则有：

- 若此次只取物品 $a$，则对总路程的贡献为 $dis_{0,a}+dis_{a,0}$；
- 若此次同时取走物品 $a,b$，则对总路程的贡献为 $dis_{0,a}+dis_{a,b}+dis_{b,0}$。

看到这里，相信聪明的你一定可以发现：

无论方案如何，每个物品到起点之间的路径都至少被经过一次。

因此，对于每一件物品，我们不妨先无视其必然会经过的通向起点的路径，只考虑另一条路径。我们会发现，对于每一个物品，它的第二条路径只有两种可能：

- 还是通往起点；
- 通向另一个物品。

考虑到 $n\le 24$ 的良心数据范围，我们大可枚举每一个物品究竟是要连向起点，还是连向其他物品。考虑到文章开头状压的思想，若我们用一个01串表示每一个物品是取还是不取，我们便可以很容易地由一个状态得出另一个状态。那么你们想到了什么方法——状压 `DP`！

但是啊，正经人谁要写 `DP` 啊，因此这题我们还可以用记忆化搜索。

## 方法解析

显然，我们应当预处理出 $dis$ 数组，并且求出 $sum$ 表示每一个物品到起点的距离之和。

接下来考虑 `dfs`

我们在函数 $dfs$ 中定义变量 $u,s$ 分别表示当前的状态。

考虑到本题一个重要的性质：**路径长度与取物顺序无关**。具体的说，我究极是先取 $1,2$ 再取 $3,4$ 还是先取 $3,4$ 还是 $1,2$ 和答案是没有关系的。因此，我们不应该每次枚举要在哪两个物品之间增加一条路径，而是应该顺序枚举每一个物品要连向哪里。

具体地，我们在 $dfs$ 中应当再定义一个变量 $x$，表示当前考虑到哪一个物品。那么在 $dfs$ 中我们仅需要 $O(n)$ 的时间即可完成状态转移。

具体实现请见代码。

------------

接着考虑方案输出。

我们定义 $now_i$ 表示物品 $i$ 的路径连向何处。例如，若我们在物品 $a,b$ 之间选择一条道路，那么则令 $now_a=b,now_b=a$；若我们在物品 $a$ 与起点间选择一条道路，那么则令 $now_a=0$，在每次更新最优答案后将 $now$ 赋值到 $ans$ 中。

在输出时，若 $ans_i=0$，则输出 $i$，否则，我们输出 $i$ 与 $ans_i$。并且，由于每一条路径的两个端点都能通过 $ans$ 表示这条路径的另一个端点，我们可以输出 $ans_i>i$ 的路径以防止重复。然后在每组输出直接用 $0$ 间隔即可。

## 注意点

- 不要忘了 $dfs$ 里的 $x$；
- 输出路径记得判重；
- 别忘了最后加上 $sum$。

## AC 代码

```cpp
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
const int N = 25;
struct Node
{
	int x, y;
}a[N];

map<int, int>M;//用map存储此状态的最小距离
int now[N], ans[N];
int dis[N][N], n, way;

void dfs(int x, int u, int s)
{
	int d = M[u];//更新最小值
	if(d != 0 && d < s) return;
	M[u] = s;

	if(x > n)
	{
		memcpy(ans, now, sizeof(now));
		return;
	}
	if(u & (1 << (x - 1)))//若该物品已被取走，直接考虑下一个物品
	{
		dfs(x + 1, u, s);
		return;
	}

	now[x] = 0;
	dfs(x + 1, u | (1 << (x - 1)), s + dis[0][x]);//连向起点
	for(int i = x + 1; i <= n; i ++)//连向其他物品
	{
		if(u & (1 << (i - 1))) continue;
		now[x] = i, now[i] = x;
		dfs(x + 1, u | (1 << (x - 1) | (1 << (i - 1))), s + dis[x][i]);
	}
}
int main()
{
	int bx, by, sum = 0;
	cin >> bx >> by >> n;
	for(int i = 1; i <= n; i ++)
	{
		cin >> a[i].x >> a[i].y;
		for(int p = 1; p < i; p ++)//预处理dis
		{
			dis[i][p] = dis[p][i] = (a[i].x - a[p].x) * (a[i].x - a[p].x) + (a[i].y - a[p].y) * (a[i].y - a[p].y);
		}
		dis[0][i] = (a[i].x - bx) * (a[i].x - bx) + (a[i].y - by) * (a[i].y - by);
		sum += dis[0][i];//别忘记sum
	}
	dfs(1, 0, 0);
	cout << sum + M[(1 << n) - 1] << endl << "0 ";
	for(int i = 1; i <= n; i ++)
	{
		if(ans[i] == 0) cout << i << " 0 ";
		else if(ans[i] > i) cout << i << " " << ans[i] << " 0 "; 
	}
	cout << endl;
	return 0;
}
```

---

## 作者：myee (赞：4)

### 思路

看到 $n\le 24$，钦定状压。

用 cost 数组转移，同时用 from 与 way 记录来路，暴力枚举每一种情况。

提交。咋[TLE](https://www.luogu.com.cn/record/51966376)了？

这个算法不够快，还有提升空间。

由于方案任意，可以考虑每次枚举第一个物品时都取编号最小者，时间会有很大优化。然而[TLE](https://www.luogu.com.cn/record/52198864)依旧。

开快读！[TLE](https://www.luogu.com.cn/record/52199003)。

再看看哪里挂了？

**涉及到二进制的题，一般不用 math 库中的 log2\(\) 函数（因为其常数贼大），而是手动打 hash 表。**

一般这个 hash 表可以利用费马小定理减小空间，见代码。

终于[过了](https://www.luogu.com.cn/record/52199187)。

### Code

```cpp
#include <math.h>
#include <stdio.h>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
inline bol _min(ullt&a,ullt b){return(b<a)?a=b,true:false;}
inline ullt time(int x1,int y1,int x2,int y2){return(llt)(x1-x2)*(x1-x2)+(llt)(y1-y2)*(y1-y2);}
inline uint hash(uint a,uint b){return a*25+b;}
ullt cost[16777220],T[30][30];uint from[16777220],way[16777220];
uint LOG[37];
int X[30],Y[30];
voi get(uint S)
{
	if(!S){putchar('0');return;}
	get(from[S]);
	if(way[S]/25==way[S]%25)printf(" %d 0",way[S]/25+1);else printf(" %d %d 0",way[S]/25+1,way[S]%25+1);
}
int main()
{
	uint n;register uint p,q;
	scanf("%d%d%u",X,Y,&n);for(uint i=1;i<=n;i++)scanf("%d%d",X+i,Y+i);
	for(uint i=0;i<=n;i++)for(uint j=0;j<=n;j++)T[i][j]=time(X[i],Y[i],X[j],Y[j]);
	for(uint i=1;i<=n;i++)for(uint j=1;j<=n;j++)T[i][j]+=T[0][i]+T[j][0];
	const uint tp=1<<n;
	for(uint i=0;i<=30;i++)LOG[(1u<<i)%37]=i;
	for(register uint S=1;S<tp;S++)
	{
		p=S&-S;cost[S]=1145141919810llu;
		for(uint S2=S;S2;S2-=q)
		{
			q=S2&-S2;
			if(_min(cost[S],cost[S^(p|q)]+T[LOG[p%37]+1][LOG[q%37]+1]))
			    from[S]=S^(p|q),way[S]=hash(LOG[p%37],LOG[q%37]);
		}
	}
	printf("%llu\n",cost[tp-1]),get(tp-1),putchar('\n');
	return 0;
}
```


---

## 作者：ylxmf2005 (赞：4)

### Description

平面坐标系中有 $n$ 个物品 $(x_{1\sim n},y_{1\sim n})$，从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ 所需的时间为 $(x_1 - x_2)^2 + (y_1 - y_2)^2$。起点在 $(sx,sy)$，要把所有的物品带到起点，最多可以捡起两个物品。不允许中途放下，求所需的最短时间。

$1 \leq n \leq 24$

### Solution

捡物品可以分成若干个过程，每个过程包括，从起点出发，捡起一个或两个物品，回到起点。每个过程是相互独立的，所以顺序是随意的。

先考虑状压 dp，预处理两点间所需时间（包括起点）$dis$。令 $f_{mask}$ 为 $mask$ 状态下所需最短时间。枚举 $mask$，$i$ 和 $j$。其中 $i$ 和 $j$ 为选哪两个物品拿，如果 $i = j$ 相当于只拿 $i$，如果 $mask$ 中不包括 $i$ 和 $j$，那可以转移。

$$f = \infty \quad f_0 = 0$$

$$f_{mask | (1 <\!< (i - 1)) | (1 <\!< (j - 1))} = f_{mask} + dis_{0,i} + dis_{i,j} + dis_{j,0}$$

$$ans = f_{(1 <\!< n) - 1}$$

然后会收获 $\text{TLE}$ 的好成绩，因为时间复杂度为 $O(n^2 \times 2^n)$。因为有许多状态是重复的，举个栗子

$$110101 = 000000\ | \begin{cases} 110000 \ | \ 000101  \\ 000101 \ | \ 110000 \\ 100100 \ | \ 010001 \\ 010001 \ | \ 100100 \\ \cdots \end{cases} $$

而之前提到了顺序是随意的，为了避免重复枚举，不如给它**定一个顺序**。所以在第一个合法的 $i$ 跳出循环，枚举下一个状态。

题目还要求存储状态，所以我们记录每个状态是从哪里转移来的即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 5, M = (1 << 24) + 5;
int x[N], y[N], dis[N][N], f[M], n, pre[M];
int main() {
	scanf("%d%d%d", &x[0], &y[0], &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);	
	for (int i = 0; i <= n; i++)
		for (int j = i + 1; j <= n; j++) 
			dis[i][j] = dis[j][i] = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
	memset(f, 0x3f, sizeof(f)); f[0] = 0;
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 1; i <= n; i++) {
			if (mask & (1 << (i - 1))) continue;
			for (int j = 1; j <= n; j++) {
				if (mask & (1 << (j - 1))) continue;
				int nxt = mask | (1 << (i - 1)) | (1 << (j - 1)) ;
				if (f[nxt] <= f[mask] + dis[0][i] + dis[i][j] + dis[j][0]) continue;
				f[nxt] = f[mask] + dis[0][i] + dis[i][j] + dis[j][0];
				pre[nxt] = mask;
			}
			break;
		} 
	} 
	int now = (1 << n) - 1; 
	printf("%d\n", f[now]);
	while (now) {
		printf("0 ");
		for (int i = 1; i <= n; i++)
            if ((now ^ pre[now]) & (1 << (i - 1)))
                printf("%d ", i);
        now = pre[now];
	}
	puts("0");
	return 0;
}
```

---

## 作者：aRenBigFather (赞：3)

## 状态压缩

#### 用 dp[sta] 表示sta状态下走的最小时间
#### 枚举每次走哪两个点(j,k),转移方程如下

$$dp[i | 2^{j-1} | 2^{k-1}] = min(dp[i | 2^{j-1} | 2^{k-1}],dp[i]+ dis[0][j]+dis[j][k]+dis[k][0]);$$

#### 其中dis[i][j]表示i,j两点的距离
#### 记录路径可以用 route[sta] 表示sta状态是由哪个状态转移过来的,然后最后倒回去找就行了

## AC代码(很慢...)
-------------
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef int ll;
const int maxn = 25;
typedef pair<ll,ll> pll;
inline ll getDis(pll a,pll b){
    return (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);
}
pll G[maxn];
ll dp[1 << maxn]; //dp[sta] 状态为sta,最小时间
ll dis[maxn][maxn],route[1 << maxn];
int n;
int main(){
    //cin >> G[0].first >> G[0].second;
    scanf("%d%d",&G[0].first,&G[0].second);
    //cin >> n;
    scanf("%d",&n);
    for(register int i=1;i<=n;i++) scanf("%d%d",&G[i].first,&G[i].second);
    for(register int i=0;i<=n;i++)
        for(register int j=i;j<=n;j++)
            dis[i][j] = dis[j][i] = getDis(G[i],G[j]);
    memset(route,-1,sizeof route);
    for(register int i=0;i<(1<<maxn);i++) dp[i] = 0x3f3f3f3f;
    dp[0] = 0;
    for(register int i=0;i<(1ll << n);i++){
        if(dp[i] == 0x3f3f3f3f) continue;
        for(register int j=1;j<=n;j++){
            if(i & (1ll << (j-1))) continue;
            for(register int k=1;k<=n;k++){
                if(i & (1ll << (k-1))) continue;
                //dp[i | (1ll << (j-1)) | (1ll << (k-1))] = min(dp[i | (1ll << (j-1)) | (1ll << (k-1))],dp[i]+dis[0][j]+dis[j][k]+dis[k][0]);
                if(dp[i]+dis[0][j]+dis[j][k]+dis[k][0] < dp[i | (1ll << (j-1)) | (1ll << (k-1))]){
                    route[i | (1ll << (j-1) | (1ll << (k-1)))] = i;
                    dp[i | (1ll << (j-1)) | (1ll << (k-1))] = min(dp[i | (1ll << (j-1)) | (1ll << (k-1))],dp[i]+dis[0][j]+dis[j][k]+dis[k][0]);
                }
            }
            break;
        }
    }
    //cout << dp[(1 << n)-1] << endl;
    printf("%d\n",dp[(1 << n)-1]);
    ll now = (1 << n) - 1,last = -1;
    //cout << "0 ";
    printf("0 ");
    while(true){
        if(last == -1){
            last = now;
            now = route[now];
            continue;
        }else{
            ll change = now ^ last;
            for(register int i=1;i<=n;i++){
                if(change & (1ll << (i-1))){
                    //cout << i << " ";
                    printf("%d ",i);
                }
            }
            last = now;
            now = route[now];
            if(now == -1){
                for(register int i=1;i<=n;i++){
                    if(last & (1 << (i-1))){
                        //cout << i << " ";
                        printf("%d ",i);
                    }
                }
                break;
            }
        }
        //cout << "0 ";
        printf("0 ");
    }
    //cout << "0";
    printf("0");
    return 0;
}
```
-----------------

---

## 作者：oh_yes (赞：2)

看范围就知道是一个状压

$ mask $ 表示当前所取物品的集合

$ dp[mask] $ 表示当前状态下所需的最小代价

每次转移只需枚举枚举拿的两个物品并额外开一个数组记录路径最后再沿着记录的路径返回就可以了

```cpp
#include<bits/stdc++.h>//looking for order
using namespace std;
const int inf = 0x3f3f3f3f;
typedef long long ll;
const int maxn = 24;

inline int getbit(int x){//取得一个数的二进制位数 
    int res = 0;
    while(x){
        x >>= 1;
        res++;
    }
    return res;
}

int n;
struct node{//存点 
    int x, y;
}item[maxn +1];

int dis[maxn + 1][maxn + 1];

inline int getdis(const node &a, const node &b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

inline void init(){//预处理每个点的距离 
    for(register int i = 1; i <= n; i ++){
        dis[i][i] = 0;
        for(register int j = 0; j < i; j ++){
            dis[j][i] = dis[i][j] = getdis(item[i], item[j]);
        }
    }
}

int dp[1 << maxn ^ 1 | 1];
int pre[1 << maxn ^ 1 | 1];//记录路径 

int main(){
    scanf("%d%d", &item[0].x, &item[0].y);
    scanf("%d", &n);
    for(register int i = 1; i <= n; i ++){
        scanf("%d%d", &item[i].x, &item[i].y);
    }
    
    init();
    memset(dp, 0x3f, sizeof dp);// 
    dp[0] = 0;//初始化 
    
    for(register int mask = 0; mask < 1 << n; mask ++){
        //初态枚举
        for(register int i = 1; i <= n; i ++){//每次选两个物品 
            if(mask & (1 << (i - 1)))continue;//已经被包含在内 
            
            for(register int j = 1; j <= n; j ++){//如果相同就算一个 
                if(mask & (1 << (j - 1)))continue;//已经被包含在内 
                
                if(dp[mask | (1 << (i - 1)) | (1 << (j - 1))] > dp[mask] + dis[0][i] + dis[i][j] + dis[j][0]){ 
                    dp[mask | (1 << (i - 1)) | (1 << (j - 1))] = dp[mask] + dis[0][i] + dis[i][j] + dis[j][0];
                    pre[mask | (1 << (i - 1)) | (1 << (j - 1))] = mask;
                }//!!!一定要写if!!!因为要更新路径 
            }
        }
    }
    
    printf("%d\n", dp[(1 << n) - 1]);
    int dpend = (1 << n) - 1;
    while(dpend){//输出路径 
        printf("0 ");
        int temp1 = dpend ^ pre[dpend];
        int temp2 = temp1 & -temp1;
        temp1 -= temp2;
        printf("%d ", getbit(temp2));
        if(temp1)printf("%d ", getbit(temp1));
        dpend = pre[dpend];
    }
    printf("0\n");
    return 0;
}
```

这样做复杂度为 $ O(2^n * n^2) $的

即使题目给了4000s的时限然而 $1 << 24$ 高达 $ 16777216 $ 乘上两个 $ n $ 肯定是受不了的[23333](https://www.luogu.org/recordnew/show/16248104)

所以我们需要利用题目的特性, 如何优化前面的dalao已经将得很详细了,实在不行可以手摸一下转移的过程

我的转移方程是 $$ dp[mask] = dp[mask \ \hat{} \ (1 << (i - 1))|(1 << (j - 1))] + dis[0][i] + dis[i][j] + dis[j][0]$$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 25;
typedef long long ll;

int getbit(int x){
	int res = 0;
	while(x){
		x >>= 1;
		res++;
	}
	return res;
}

int n;
struct node{
	int x, y;
}item[maxn];

int dis[maxn][maxn];

int getdis(const node &a, const node &b){
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void init(){
	for(int i = 1; i <= n; i ++){
		dis[i][i] = 0;
		for(int j = 0; j < i; j ++){
			dis[j][i] = dis[i][j] = getdis(item[i], item[j]);
		}
	}
}

int dp[1 << (maxn - 1) | 1];
int pre[1 << (maxn - 1) | 1];
//前面不变 
int main(){
	scanf("%d%d", &item[0].x, &item[0].y);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)scanf("%d%d", &item[i].x, &item[i].y);
	init();
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	
	for(int mask = 1; mask < 1 << n; mask ++){
		//采用getbit直接取得当前状态的子集 
		int i = getbit(mask);//当前状态中编号最大的物品的编号 
		//相当于第一重循环 
		int temp = mask;//
		while(temp){// 
			int j = getbit(temp);//相当于第二重循环 
			temp ^= (1 << (j - 1));//每次从temp中去掉已经枚举过的状态 
			if(dp[mask] > dp[mask ^ ((1 << i - 1) | (1 << j - 1))] + dis[0][i] + dis[i][j] + dis[j][0]){
				dp[mask] = dp[mask ^ ((1 << i - 1) | (1 << j - 1))] + dis[0][i] + dis[i][j] + dis[j][0];
				pre[mask] = mask ^ ((1 << i - 1) | (1 << j - 1));
			}
		}
	}
	
	printf("%d\n", dp[(1 << n) - 1]);
	int dpend = (1 << n) - 1;
	while(dpend){
		printf("0 ");
		int temp1 = dpend ^ pre[dpend];
		int temp2 = temp1 & -temp1;
		temp1 -= temp2;
		printf("%d ", getbit(temp2));
		if(temp1)printf("%d ", getbit(temp1));
		dpend = pre[dpend];
	}
	printf("0\n");
	return 0;
}
```

---

## 作者：kczno1 (赞：2)

$dp$，记录哪些点没选，$O(2^n*n)$

```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
	if(x>y)x=y;
}
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define mp make_pair
int sqr(int x)
{
	return x*x;
}
int dis(const pii &a,const pii &b)
{
	return sqr(a.first-b.first)+sqr(a.second-b.second);
}
const int N=24+1,S=1<<24;
int n;pii dp[S];
pii p[N];
int w[N][N];

pii dfs(int s)
{
	if(dp[s].first!=-1)return dp[s];
	rep(i,1,n)
	if(s&(1<<i-1))
	{
		int _s=s-(1<<i-1);
		dp[s]=mp(dfs(_s).first+w[i][i],i);
		rep(j,i+1,n)
		if(_s&(1<<j-1))chmin(dp[s],mp(dfs(_s-(1<<j-1)).first+w[i][j],j));
		return dp[s];
	}
}

int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&p[0].first,&p[0].second);
	cin>>n;
	rep(i,1,n)scanf("%d%d",&p[i].first,&p[i].second);
	rep(i,1,n)
	rep(j,i,n)w[i][j]=dis(p[0],p[i])+dis(p[i],p[j])+dis(p[j],p[0]);
	memset(dp,-1,sizeof(dp));
	dp[0].first=0;
	int s=(1<<n)-1;
	pii p=dfs(s);
	printf("%d\n",p.first);
	printf("%d",0);
	while(s)
	{
		p=dp[s];
		rep(i,1,n)
		if(s&(1<<i-1))
		{
			if(p.second==i)
			{
				printf(" %d",i);
				s-=1<<i-1;
			}
			else
			{
				printf(" %d %d",i,p.second);
				s-=(1<<i-1)+(1<<p.second-1);
			}
			break;
		}
		printf(" %d",0);
	}
}
```

---

## 作者：OIer_ACMer (赞：1)

# 题目解析：

本题，其实，十分毒瘤，由于一次最多只能拿两个物品，且拿完后为了保证代价最小还必须回到出发点，所以，我们就要从动态规划的手段考虑这个题。

由于点数很多，我们就要进行状态压缩，毕竟，这个数据范围加上题目给的空间也就告诉来我们这道题不用状压就过不去，我们用 $0$ 和 $1$ 表示该点是否走过，用一串长度为 $n$ 的序列表示每个状态。

接着，到了定义每个状态的含义了，定义 $dp_i$ 代表遍历的点状态为 $i$ 时候的最短距离和。那么转移只有两种状态，要么是遍历一个点，要么是遍历两个点。不过，这样的话循环太多会超时。

但是注意到，**距离和遍历的顺序无关**，所以对于状态 $i$，不妨将其状态中的第一个点 $x$，作为这个状态一定要考虑的点。因为这个点早晚要遍历，不如就放到这里遍历，结果不会变。简单点说，就是将一个一个点的遍历变为一次打包遍历两个点，大大优化了时间复杂度。


# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
inline int lowbit(int x)
{
	return x & (-x);
}
const int INF = 0x3f3f3f3f;
const long long INFLL = 1e18;

typedef long long ll;

const int N = 24;
int dp[1 << N];
struct node
{
	int x, y;
} dian[1000009];
int path[1 << N];
int dis(int i, int j)
{
	int d1 = abs(dian[i].x - dian[j].x);
	int d2 = abs(dian[i].y - dian[j].y);
	return d1 * d1 + d2 * d2;
}
int main()
{
	cin >> dian[0].x >> dian[0].y;
	int n;
	cin >> n;
	for (int i = 1; i < n + 1; i++)
	{
		cin >> dian[i].x >> dian[i].y;
	}
	memset(dp, INF, sizeof(dp));
	dp[0] = 0;
	for (int S = 0; S < 1 << n; S++)
	{
		if (dp[S] == INF)
		{
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			if (!(S >> i & 1))
			{
				for (int j = i; j < n; j++)
				{
					if (!(S >> j & 1))
					{
						if (dp[S] + dis(0, i + 1) + dis(i + 1, j + 1) + dis(j + 1, 0) < dp[S | 1 << i | 1 << j])
						{
							dp[S | 1 << i | 1 << j] = dp[S] + dis(0, i + 1) + dis(i + 1, j + 1) + dis(j + 1, 0);
							path[S | 1 << i | 1 << j] = S;
						}
					}
				}
				break;
			}
		}
	}
	cout << dp[(1 << n) - 1] << endl;
	int S = (1 << n) - 1;
	cout << 0 << ' ';
	while (S)
	{
		int mv = S ^ path[S]; 
		int i = __lg(lowbit(mv)) + 1;
		cout << i << ' ';
		mv -= lowbit(mv);
		if (mv)
		{
			i = __lg(lowbit(mv)) + 1;
			cout << i << ' ';
		}
		cout << "0 ";
		S = path[S];
	}
	return 0;
}

```

---

## 作者：XL4453 (赞：1)

### 解题思路：

初步转化问题，直接将手提包的位置设置为 $(0,0)$，改变其他物品的坐标使其对应即可。这样计算代价的时候可能会简单一点。

---
本题中物品数量不是很多，也不太容易想到什么巧妙的做法，考虑直接暴力状态压缩。

设 $f_{s}$ 表示取了状态为 $s$ 的物品，回到起点所需要的最小时间，其中 $s$ 二进制下为 $1$ 的表示已经被取，$0$ 则表示尚未被取。

由于所有的物品到最后一定要被取，实际上只关心哪些物品放在了一起拿，不妨强制取第一个未取的，后面随便取或者不取。

最后再用一个数组记录一下这个状态是由那一个转移过来的即可。

----
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int now,nxt,fi,sx,sy,n,x[30],y[30],f[33554432],from[33554432];
int dis(int x1,int y1,int x2,int y2){
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int main(){
	scanf("%d%d",&sx,&sy);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
		x[i]-=sx;y[i]-=sy;
	}
	memset(f,0x3f3f,sizeof(f));
	f[0]=0;
	for(int i=0;i<=(1<<n)-2;i++){
		for(int j=0;j<n;j++)
		if(((i>>j)&1)==0){
			fi=j;
			break;
		}
		now=i+(1<<fi);
		if(f[now]>f[i]+2*dis(x[fi+1],y[fi+1],0,0)){
			f[now]=f[i]+2*dis(x[fi+1],y[fi+1],0,0);
			from[now]=i;
		}
		for(int j=0;j<n;j++)
		if(((now>>j)&1)==0){
			int w=f[i]+dis(x[fi+1],y[fi+1],x[j+1],y[j+1])+dis(x[fi+1],y[fi+1],0,0)+dis(x[j+1],y[j+1],0,0);
			if(f[now+(1<<j)]>w){
				f[now+(1<<j)]=w;
				from[now+(1<<j)]=i;
			}
		}
	}
	printf("%d\n",f[(1<<n)-1]);
	now=(1<<n)-1;
	while(now){
		nxt=from[now];
		printf("0 ");
		for(int i=0;i<n;i++){
			if((((nxt>>i)&1)==0)&&(((now>>i)&1)==1))
			printf("%d ",i+1);
		}
		now=nxt;
	}
	printf("0\n");
	return 0;
}
```


---

## 作者：MY_Lee (赞：1)

### 题意
> 坐标系中给定一个包的位置 $x_0,y_0$，有 $n$ 个物品给定坐标 $x_i,y_i$。从一个点到另一个点的时间花费为两点间欧几里得距离的平方。你从包出发，每次最多拿 $2$ 个物品，求把所有物品放到包里的最小耗时。

- $1\le n\le24,1\le x_i,y_i\le 100$,$i\in[0,n]$。

---
### 思路

看见数据范围立刻想到状压 dp。

考虑设 $dp_{statu}$ 表示当前拿取物品的状态为 $statu$ 时的最小耗时，其中 $statu$ 的第 $i$ 位为 $0(1)$ 表示第 $i$ 个物品没放到包里(放到包里)。

~~肉眼可见~~最终答案为 $dp_{(11\cdots1)_2}$ 即 $dp_{2^n-1}$


---
考虑如何转移。

显然有 $dp_0=0$，表示没开始拿不耗时。

其余的初始化为 inf 即可。

既然可以拿 $2$ 个物品，就可以考虑在转移时枚举手里抓的两个物品 $j,k$，用当前状态加上拿这两个物品的耗时更新拿了这两个物品的状态。~~好吧貌似有点绕~~

具体而言，先枚举当前状态 $i$，再枚举 $j,k$ 表示手里抓的物品，那么拿了 $j,k$ 的状态就应该为 `i|(1<<j-1)|(1<<k-1)`，**注意判断当前状态不包含手里的物品**，即 $i$ 的第 $j,k$ 位为 $0$。

为方便可以先初始化了 $i,j$ 间的耗时，记为 $dist_{i,j}$

```cpp
for(ll i=0;i<ss;i++){
	if(dp[i]<0x3f3f3f3f){
		for(ll j=1;j<=n;j++){
			if(((i>>(j-1))&1)==0){
				for(ll k=1;k<=n;k++){
					if(((i>>(k-1))&1)==0){//j,k 当前状态不能有
						nans=dp[i]+dist[0][j]+dist[j][k]+dist[k][0];
						if(dp[i|(1<<(j-1))|(1<<(k-1))]>nans){
							dp[i|(1<<(j-1))|(1<<(k-1))]=nans;
							pos[i|(1<<(j-1))|(1<<(k-1))]=i;
						}
					}
				}
				break;
			}
		}
	}
}
```
---
考虑如何输出路径。

根据套路，在转移的时候设一个 $pos$ 表示状态转移来源，然后递归处理即可。

```cpp
inline void print(ll now){
	if(now==0){
		return ;
	}
	cout<<"0 ";
	for(ll i=1;i<=n;i++){
		if(((now^pos[now])>>(i-1))&1){
			cout<<i<<" ";
		}//now^pos[now] 即为在这一轮转移过程中被新拿了的物品
	}
	print(pos[now]);
}
```
完整 code 就不放辣。

---
[广告](https://www.cnblogs.com/StarDust-lmy/)

---

## 作者：Bosun (赞：1)

虽然这道题暴力状压很好打，但是2^n*n^2的复杂度根本过不了。

但是你想想，对于所有操作的顺序是可以变的，答案不会变，因为我的状态中有这个东西，这东西不管是在什么时候捡的，它放到最后一次捡肯定没问题.

于是,对于任意在状态中的物品，我都可以用它来转移，所以我们任取一个物品，暴力枚举另外一个和它一起捡的，就可以通过此题了。
   
清蒸code
  
  ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sx,sy,x[30],y[30],f[20000000],z[20000000];
int lowbit(int x){
    return x & -x;
} 
int dis(int u,int v){
    return (x[u]-x[v])*(x[u]-x[v])+(y[u]-y[v])*(y[u]-y[v]);
}
int H(int x){
    int cnt=0;
    while(x){
        cnt++;
        x>>=1;
    }
    return cnt;
} 
int main(){
    int i,j;
    cin>>x[0]>>y[0]>>n;
    for(i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int state=1;state<(1<<n);state++){
        i=lowbit(state); 
        int w=state;
        while(w){
            j=lowbit(w);
            int nw=f[state^(i|j)]+dis(0,H(i))+dis(H(i),H(j))+dis(H(j),0);
            if(nw<f[state]){
                f[state]=nw;
                z[state]=state^(i|j);
            }
            w-=lowbit(w);
        }
    }
    cout<<f[(1<<n)-1]<<endl;
    int pd=(1<<n)-1;
    while(pd){
        printf("0 ");
        int t1=pd^z[pd];
        int t2=lowbit(pd);
        t1-=t2;
        printf("%d ",H(lowbit(t2)));
        if(t1)printf("%d ",H(lowbit(t1)));
        pd=z[pd];
    } 
    printf("0\n");
    return 0;
}
```


---

## 作者：AK_heaven (赞：0)

我来证明一下一次取两个物品一定优于一次取一个物品，分两次取。

首先，我们先把这两种情况表示出来：

① $W_1 = dis_{0, a} + dis_{a, b} + dis_{b, 0}$

② $W_2 = dis_{0, a} \times 2 + dis_{0, b} \times 2$

用 ② 式减去 ① 式：

③ $W_2 - W_1 = dis_{0, a} + dis_{0, b} - dis_{a, b}$

由三角不等式可以得到 

$dis_{a, b} \le dis_{0, a} + dis_{0, b}$ 

等号在三点共线的时候取得。

所以得到 $W_1 \le W_2$。

证毕。

---

## 作者：Cute__yhb (赞：0)

## 思路

状压。

设 $2^{i-1}$ 来表示第 $i$ 个物品有没有选。

那么每一个状态都能看成一个二进制数。

又因为三角形两边之和大于第三边，所以选两个一定比选一个优。

所以，对于每个状态，枚举两个没被选中的物品，拓展一个新状态。

对于输出路径，只需要记录下每个状态的上一个状态，从所有物品全选的状态往前找即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define re register
#define ri register int
#define rll register long long
#define ld long double
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define nep(i,a,b) for(int i=(a);i>=(b);i--)
#define popcount __builtin_popcount
#define pb push_back
#define mem(a,x) memset((a),x,sizeof(a))
#define eps 1e-8
#define oper operator
#define mk make_pair
int x,y,f[(1<<25)],last[1<<25],n,cnt,dis[55][55];
//f为dp数组,last为上一个状态
struct node{
	int x,y;
}a[55];
int main(){
	cin>>x>>y>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	a[0].x=x;
	a[0].y=y;
	for(int i=0;i<=n;i++){//预处理距离
		for(int j=0;j<=n;j++){
			dis[i][j]=(a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y);
		}
	}
	cnt=(1<<n)-1;//总状态数
	memset(f,INF,sizeof f);
	f[0]=0;//初始化
	for(int i=0;i<=cnt;i++){
	    if(f[i]==INF) continue;//该状态没被更新过,就不用更新别的状态了
		for(int j=0;j<n;j++){
			if(((1<<j)&i)!=0) continue;//被选过
			for(int k=0;k<n;k++){
				if(((1<<k)&i)!=0) continue;//被选过
				int sum=f[i]+dis[0][j+1]+dis[j+1][k+1]+dis[k+1][0];//新距离
				if(f[i|(1<<j)|(1<<k)]>sum){//更优
					f[i|(1<<j)|(1<<k)]=sum;//更新dp数组
					last[i|(1<<j)|(1<<k)]=i;//记录上一个状态
				}
			}
			break;//找到一种可行方案即可
		}
	}
	cout<<f[cnt]<<endl;//最小值
	int x=cnt;//全选
	while(x){
		int y=last[x];//上一个
		cout<<0<<" ";//回原点
		for(int j=0;j<n;j++){
			int k=(1<<j);
			if((x&k)!=(y&k)){//有变化
				cout<<j+1<<' ';//输出
			}
		}
		x=y;
	}
	cout<<0;//回原点
    return 0;
}
```

---

## 作者：revolutionary_oier (赞：0)

## 进阶篇 ： CF8C
### 题面及传送门
[传送门洛谷之 CF8C](https://www.luogu.com.cn/problem/CF8C)
### 解析思路
#### 前提补充
**欧氏距离**用~~人话~~ 来说一下：

空间中的 2 点直线距离进行将几何代数化即为**欧氏距离**。

哈哈，远古题目，~~绝对逆天~~ 。

####  思路点拨
##### 题目分析

本题影响状态如下：
- 取完物品的情况
- 本次取的物品 1
- 本次取的物品 2
（物品 2 可能与物品 1 是同一个物品。）

细细思考一下本次取的物品只用来更新距离，并不对后面的状态进行影响，所以将其压缩掉，最终的状态如下：
- 取完物品的情况

记录物品取得顺序只不过是再定义一个前缀数组，最后回溯路径输出即可实现其功能。

##### DP分析
- **状态定义**：定义 $f_s$ 表示在取完这次物品后最终状态为 $s$ 时所要走得**欧氏距离**
- **状态转移方程**：$f_s=\min(f_s,f_{s\land(2^{i-1}\cup 2^{j-1})+dis(i,j)+dis(i,0)+dis(j,0)})$（ $i$ 为取得第 $1$ 件物品, $j$ 为取得的第 $2$ 件物品）不排除 $i=j$
- **状态初始化**： $f_s = \infty$
- **时间复杂度**: $O(n^2 \cdot 2^n)\approx9.6 \cdot 10^9$ ,TLE(即便 register int 火车头，快读)

##### DP瓶颈之优化
首先要明确物品取得顺序并不影响最终答案，但上面明显是属于重复枚举同一种答案，OK 优化方向走起。

若看不懂上面的优化方向，可以更形象的解释一下：先取物品 1 2 再取物品 3 和先取物品 3 再取物品 1 2 所需要的代价是等价的。

所以枚举到第 1 个物品，并遍历其所能连到第 2 个物品所需要的最小距离，之后 break 即可实现其时间复杂度减小（看 TJ 才知道）。
- **最终时间复杂度** : $O(n \cdot 2^n) \approx 4 \cdot 10^8$

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=50;
const int maxm=2e7+10;
const int inf=2e9; 
int n,stx,sty,cnt;
int f[maxm],ans[3*maxn];
int fa[maxm][2];
struct node{
	int x,y;
}a[maxn];
inline int distance(int x1,int y1,int x2,int y2){return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);}//欧氏距离的平方
// 回溯路径函数
inline void find(int x){
	//printf("%d\n",x);
	if(fa[x][0]==0&&fa[x][1]==0)return ;
	ans[++cnt]=fa[x][0];
	if(fa[x][1]!=fa[x][0])ans[++cnt]=fa[x][1];
	ans[++cnt]=0;
	find(x^((1<<(fa[x][0]-1))|(1<<(fa[x][1]-1))));
}
int main(){
	scanf("%d%d%d",&stx,&sty,&n);
	for(register int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
	//状态初始化
	for(register int i=1;i<(1<<n);i++)f[i]=inf;
	//状态转移方程
	for(register int i=1;i<(1<<n);i++){
		for(register int j=1;j<=n;j++){
			if((i>>(j-1)&1)!=1)continue;
			int y=f[i^(1<<(j-1))]+2*distance(stx,sty,a[j].x,a[j].y);
			if(y>f[i])continue; 
			for(register int k=j;k<=n;k++){
				if((i>>(k-1)&1)!=1)continue;
				int x=f[i^((1<<(j-1))|(1<<(k-1)))]+distance(stx,sty,a[j].x,a[j].y)+distance(stx,sty,a[k].x,a[k].y)+distance(a[j].x,a[j].y,a[k].x,a[k].y);
				if(x<f[i]){
					f[i]=x;
					fa[i][0]=j;
					fa[i][1]=k;		
				}	
			}
			break;
		}
	}
	printf("%d\n",f[(1<<n)-1]);
	ans[++cnt]=0;
	find((1<<n)-1);
	reverse(ans+1,ans+cnt+1);//翻转回溯路径
	for(register int i=1;i<=cnt;i++)printf("%d ",ans[i]);
	return 0;
} 
```
恭喜您，秒掉进阶篇


---

## 作者：ncwzdlsd (赞：0)

~~状压DP大法好~~

首先我们考虑贪心，绞尽脑汁地思考之后，然而我们发现贪心的正确性难以被证明，所以我们果断放弃贪心考虑DP。（看了有的大佬说可以用）

看到这道题的数据范围，显然不能用普通的方法做，必须祭出状压DP大法。

经过缜密的分析我们可以发现，任意两次从原点出发、取点、返回原点的过程，互换之后对结果没有影响，所以只需要记录每一个点的两种状态——走了或没走。

于是乎，我们只需要开一个 $2^{24}$ 的数组，同时由于需要存储路径，还需要开一个相同大小的数组。

接下来我们要考虑如何保证一个走法不反复走，在一个转移点时选择第一个点即可避免反复转移。

于是乎我们就可以列出状态转移方程，开一个 `dp` 数组枚举解，开一个 `dis` 数组存储路径距离，枚举 $i$，$j$：
$$
dp_{t|(1<<(i-1))|(1<<(j-1))}=dp_t+dis(0,i)+dis(0,j)+dis(i,j)
$$

代码就不放了，实在不会码的可以参考其他题解，要自己思考哟！

---

