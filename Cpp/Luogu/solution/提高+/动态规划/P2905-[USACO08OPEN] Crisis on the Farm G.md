# [USACO08OPEN] Crisis on the Farm G

## 题目描述

约翰和他的奶牛组建了一只乐队“后街奶牛”，现在他们正在牧场里排练。奶牛们分成一堆一堆，共 $1000$）堆。每一堆里，$30$ 只奶牛一只踩在另一只的背上，叠成一座牛塔。牧场 里还有 $M(1 < M < 1000)$ 个高高的草垛。

作为出色的指挥家，约翰可以通过口哨指挥奶牛们移动。他的口哨有四个音，分别能使所有的牛塔向东南西北四个方向移动一格。

每一次，当一个牛塔到达了一个草垛所在的格子，牛塔最上方的奶牛就会跳到草垛上，而且不再下来，而其他奶牛仍然呈塔状站在草垛所在的格子里.当牛塔只剩一只奶牛时，这只奶牛也会跳到草垛上。

突然，约翰大惊失色：原来邻家的奶缸爆炸了！滚滚而下的牛奶正朝着约翰的牧场冲来，不久就要将牧场淹没。约翰必须马上行动，用口哨声挽救奶牛们的生命。他要指挥奶牛尽量多地跳上草操，草操上的奶牛将不会被淹死.

约翰还有 $K$ 次吹口哨的机会.那他最多还能救多少奶牛呢？请计算最多能挽救的奶牛数，以及达到这个数目约翰需要吹的口哨调子序列。序列用 $\mathtt{E,W,S,N}$ 表示东西南北。如果有多种序列能达到 要求，输出作为字符串最小的。


## 说明/提示

Use the 'east' whistle three times, at which point the milk floods the area.  Each haystack ends up saving 1 cow.

对于 $100\%$ 的数据，$1\le K\le 30$，$1\le N,M,X_i,Y_i\le 1000$。


## 样例 #1

### 输入

```
3 6 3 
3 4 
6 2 
5 7 
8 2 
9 2 
6 4 
5 4 
6 7 
8 7 
```

### 输出

```
6 
EEE 
```

# 题解

## 作者：iwprc (赞：11)

作为此题目前的最优解，我有必要发一个新的题解：

首先，本题的情景是平面直角坐标系，

分析一下可知要用dp,

设f[i][j][k]为前i秒向北移动j步，向东移动k步最多能挽救的奶牛数

则f[i][j][k]=max(f[i-1][j+1][k],f[i-1][j][k+1],f[i-1][j-1][k],f[i-1][j][k-1])+g[j][k]

而g[j][k]表示全体奶牛向北移动j步，向东移动k步时能挽救的奶牛数

给出代码：

```cpp
#include<cstdio>
const int N=1000,T=31;
const int dx[]={1,0,0,-1},dy[]={0,1,-1,0},d[]={69,78,83,87};
//方向增量按字母字典序的顺序给出：E,N,S,W
int n,m,k,i,j,s,t,x[N],y[N],p[N],q[N],g[T*2][T*2],f[T][T*2][T*2],u,v;
//因为下标不能为负，所以向南向西的负数要加上T使之为正
int max(int x,int y){return x>y?x:y;}
int abs(int x){return x>0?x:-x;}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(i=0;i<n;i++)
        scanf("%d%d",x+i,y+i);
    for(i=0;i<m;i++)
        scanf("%d%d",p+i,q+i);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(abs(p[j]-x[i])+abs(q[j]-y[i])<=k)
                g[p[j]-x[i]+T][q[j]-y[i]+T]++;
    //g数组由初始化得到，只要奶牛和草垛的曼哈顿距离<=k,便是可达的
    for(t=k;t>=0;t--)//阶段从大到小枚举是为了输出使字典序最小方便
        for(u=T-t;u<=T+t;u++)
            for(v=T-t;v<=T+t;v++){
                for(i=0;i<4;i++)
                    f[t][u][v]=max(f[t+1][u+dx[i]][v+dy[i]],f[t][u][v]);
                f[t][u][v]+=g[u][v];
            }
    printf("%d\n",f[0][T][T]);
    u=T;v=T;
    for(i=0;i<k;i++){
        for(j=0;j<4;j++)
            if(f[i][u][v]==f[i+1][u+dx[j]][v+dy[j]]+g[u][v])
                break;
        //只要发现本状态是由第j个决策得来的就退出循环，输出
        u+=dx[j];v+=dy[j];
        printf("%c",d[j]);
    }
    return 0;
}
//时间复杂度：O(n*m+k^3)
//空间复杂度：O(n+m+k^3)
```

---

## 作者：沧澜 (赞：4)

思路：重点是整体化的数学思想。

本质是一道恶心的DP，不光预处理恶心，状态转移方程恶心，甚至连输出也很恶心(╯‵□′)╯︵┻━┻

至于具体的就看代码里的注释吧，按照我们老师的说法：“你这是在这注释，还是写小说啊。”

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 1500
using namespace std;
int n,m,K,ans;
int dx[4]={1,0,0,-1};
int dy[4]={0,1,-1,0};
char step[40][64][64];
char C[4]={'W','S','N','E'};
int cnt[64][64],f[40][64][64]; //f[k][i][j]记录走k步,纵向移动了i-31步,横向移动了j-31步,所能拯救的最多的牛的数量。
int cawx[MAXN],cawy[MAXN],grassx[MAXN],grassy[MAXN];//记录牛和草垛的横纵坐标.
int main(){
    scanf("%d%d%d",&n,&m,&K);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&cawx[i],&cawy[i]);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&grassx[i],&grassy[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int cx=cawx[i]-grassx[j];    //第i头牛移动到第j个草垛,纵向最少所走的距离.    
            int cy=cawy[i]-grassy[j];    //第i头牛移动到第j个草垛,横向最少所走的距离.
            if(abs(cx)<=30&&abs(cy)<=30)//因为k<=30,所以当有一个方向的距离大于30,就不用考虑了,因为一定不可能走到. 
                cnt[cx+31][cy+31]++;    //否则cnt记录走纵向i步横向走j步所能拯救的牛的数量. 
        }
    for(int k=0;k<=K;k++)
        for(int i=0;i<=62;i++)
            for(int j=0;j<=62;j++){
                f[k][i][j]=-0x3f3f3f3f;
                step[k][i][j]='Z';
            }
    f[0][31][31]=0;    //赋初值,最开始时所能拯救的牛的数量为0. 
    //这里要理解,因为他可以向上下左右走,为了防止负坐标的出现,我们把一开始时的原点坐标当做(31,31).
    for(int k=1;k<=K;k++)
        for(int i=1;i<=61;i++)
            for(int j=1;j<=61;j++)
                f[k][i][j]=cnt[i][j]+max(max(f[k-1][i-1][j],f[k-1][i+1][j]),max(f[k-1][i][j-1],f[k-1][i][j+1]));
                //这个状态转移方程就不用解释了,还是很容易理解的. 
    for(int i=1;i<=61;i++)
        for(int j=1;j<=61;j++)
            ans=max(ans,f[K][i][j]);
    for(int i=1;i<=61;i++)
        for(int j=1;j<=61;j++)
            if(ans==f[K][i][j])
                step[K][i][j]='A';    //如果为纵向走i步横向走j步是一种可行的走法,记录以方便求字典序最小. 
    for(int k=K-1;k>=0;k--)
        for(int i=1;i<=61;i++)
            for(int j=1;j<=61;j++)
                for(int l=0;l<4;l++)
                    if(f[k][i][j]+cnt[i+dx[l]][j+dy[l]]==f[k+1][i+dx[l]][j+dy[l]]&&step[k+1][i+dx[l]][j+dy[l]]<'Z')
                        step[k][i][j]=C[l];    //倒序找出所有可能的走法. 
    cout<<ans<<endl;
    int i=31,j=31;
    for(int k=0;k<K;k++){
        cout<<step[k][i][j];
        if(step[k][i][j]=='E')    i--;    //找字典序最小的. 
        else if(step[k][i][j]=='W')    i++;
        else if(step[k][i][j]=='S')    j++;
        else if(step[k][i][j]=='N')    j--;    
    }
}
```

---

## 作者：木木！ (赞：2)

本题做法不是重点，输出最为恶心（捂胸口）。

首先，看到题目，搜索无望，贪心扑街，考虑 DP。然后发现 k 特别小，就可以 $\Theta(k^2n)$ 预处理出向东走 i 步向北走 j 步能拯救的奶牛的数量 `savn[i][j]`，然后直接开一个三维数组 `dp[i][dx][dy]` 表示在第 i 次吹哨后，东西向位移 dx，南北向位移 dy， $\Theta(k^3)$ DP 就好。状态转移方程楼上说得很清楚了。

然后重头戏来了，如何输出。

首先，因为要控制字典序，我们选择 DP 方式为填表 DP。然后，每一步贪心选择字典序最小的一步走。交上去，光荣地 WA 到 67。

分析一下就会发现，保证每一步字典序最小不一定能保证答案的字典序最小。因为我们的决策顺序和字典序的顺序是反的，字典序是先比较前面的字符，而我们是贪心让后面的字符最小。然后就炸了。

一个很显然的方案是记录每一个状态的步骤序列的字典序排名，然后贪心转移。字典序排名的值域空间是 $\Theta(4^k)$，刚好能用 long long 装下。转移的时候顺便维护一下转移过后的字典序排名就好了。时间复杂度 $\Theta(m+k^2n+k^3)$，代码复杂度 2.22KB。

然后还有一种乱搞方案。既然贪心让后面字符最小炸了，那我们贪心让后面字符最大。因为最后统计答案的时候终点固定，如果后面字符大的话，一定意味着前面的字符小。在寻找最优解的时候也一样，贪心地让 `dp[k][dx][dy]` 最大的同时让 dx 和 dy 最大。

于是就过了。这个看起来十分好 Hack 的方案竟然过了。时间复杂度还是 $\Theta(m+k^2n+k^3)$，代码复杂度降到了 1.75KB。

然而题解已经有第二种方案的代码了，于是下面附的是暴力维护字典序排名的 AC 代码：

```cpp
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;

char di[] = {'E','N','S','W'};
int gox[] = {1,0,0,-1};
int goy[] = {0,1,-1,0};

#define DELTA 32

int gi[1005][1005];
int xi[1005];
int yi[1005];

inline bool inspace(int x,int y)
{
	return x>0 && x<=1000 && y>0 && y<=1000;
}

int savn[65][65];

int dp[35][65][65];
int deci[35][65][65];
long long strn[35][65][65];

int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d%d",xi+i,yi+i);
	}
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		gi[x][y] = 1;
	}

	for(int i=-k; i<=k; ++i)
	{
		for(int j=-k; j<=k; ++j)
		{
			int res = 0;
			for(int cn=1; cn<=n; ++cn)
			{
				if(inspace(xi[cn]+i,yi[cn]+j) && gi[xi[cn]+i][yi[cn]+j])
				{
					++res;
				}
			}
			savn[i+DELTA][j+DELTA] = res;
		}
	}

	memset(dp,0x80,sizeof(dp));
	dp[0][0+DELTA][0+DELTA] = 0;

	for(int i=1; i<=k; ++i)
	{
		for(int dx=-i+DELTA; dx<=i+DELTA; ++dx)
		{
			for(int dy=-i+DELTA; dy<=i+DELTA; ++dy)
			{
				long long lstrn = 0x7f7f7f7f7f7f7f7fLL;
				for(int j=0; j<4; ++j)
				{
					if(dp[i-1][dx-gox[j]][dy-goy[j]]==dp[i][dx][dy] && lstrn>strn[i-1][dx-gox[j]][dy-goy[j]])
					{
						deci[i][dx][dy] = j;
						lstrn = strn[i-1][dx-gox[j]][dy-goy[j]];
					}
					if(dp[i-1][dx-gox[j]][dy-goy[j]] > dp[i][dx][dy])
					{
						deci[i][dx][dy] = j;
						lstrn = strn[i-1][dx-gox[j]][dy-goy[j]];
						dp[i][dx][dy] = dp[i-1][dx-gox[j]][dy-goy[j]];
					}
				}
				dp[i][dx][dy] += savn[dx][dy];
				strn[i][dx][dy] = lstrn*4+deci[i][dx][dy];
			}
		}
	}

	int maxdx = DELTA;
	int maxdy = DELTA;
	for(int dx=DELTA-k; dx<=DELTA+k; ++dx)
	{
		for(int dy=DELTA-k; dy<=DELTA+k; ++dy)
		{
			if(dp[k][dx][dy]==dp[k][maxdx][maxdy] && strn[k][dx][dy]<strn[k][maxdx][maxdy])
			{
				maxdx = dx;
				maxdy = dy;
			}
			if(dp[k][dx][dy]>dp[k][maxdx][maxdy])
			{
				maxdx = dx;
				maxdy = dy;
			}
		}
	}

	printf("%d\n",dp[k][maxdx][maxdy]);

	stack<char> stk;
	for(int i=k; i>=1; --i)
	{
		int g = deci[i][maxdx][maxdy];
		stk.push(di[g]);
		maxdx -= gox[g];
		maxdy -= goy[g];
	}

	while(!stk.empty())
	{
		putchar(stk.top());
		stk.pop();
	}
}
```

---

## 作者：SunsetLake (赞：1)

喜提最劣解。

一开始第四个点一直没过，以为假了，结果这道题可以走到负数，需要注意一下。

## Solution

注意到 $k$ 只有 $30$，而答案又和朝每个方向走的步数有关，于是直接设一个无脑状态：$f_{E,W,S,N}$ 表示朝东西南北各走了 $E,W,S,N$ 步，最多能保活几头牛。转移考虑刷表法，已知状态 $E,W,S,N$，枚举下一步朝哪边走进行更新。这个时候你是可以通过 $E,W,S,N$ 算出每堆牛在哪里的，新增的贡献就是有牛在的草垛数量。

本题还需要输出最小方案，那就再设一个 string 数组 $g_{E,W,S,N}$ 表示字典序最小的方案。转移时若新答案更大，那就把当前的 $g$ 直接赋成上一个的 $g$ 加上这一步的字符；如果两个答案一样，取字典序小的就行了。

时间复杂度看上去是 $O(nk^4)$ 的，但是转移时要加上 $E + W + S + N \le k$ 的限制，这会使状态数大大减少，具体是多少我也没算，不过 1s 还是能轻松过了。

## code


```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N = 1005,M = 35;
int n,m,k;
ll f[M][M][M][M];//E,N,S,W  R,U,D,L
string g[M][M][M][M];
int mp[N][N];
int x[N],y[N],nx[N],ny[N]; 
bool ck(int x,int y){
	return x >= 1 && x <= 1000 && y >= 1 && y <= 1000;
}
int main(){
	cin >> n >> m >> k;
	for(int i = 1;i <= n;++ i) cin >> x[i] >> y[i];
	for(int i = 1;i <= m;++ i){
		int a,b;
		cin >> a >> b;
		mp[a][b] ++;
	}
	for(int r = 0;r <= k;++ r)
		for(int u = 0;u <= k && u + r <= k;++ u)
			for(int d = 0;d <= k && u + r + d <= k;++ d)
				for(int l = 0;l <= k && u + r + d + l <= k;++ l)
					for(int i = 1;i <= k;++ i)
						g[r][u][d][l] += 'Z';
	g[0][0][0][0] = "";
	for(int r = 0;r <= k;++ r)
		for(int u = 0;u <= k && u + r <= k;++ u)
			for(int d = 0;d <= k && u + r + d <= k;++ d)
				for(int l = 0;l <= k && u + r + d + l <= k;++ l){
					for(int i = 1;i <= n;++ i) nx[i] = x[i] + r - l;
					for(int i = 1;i <= n;++ i) ny[i] = y[i] + u - d;
					int res = 0;
					for(int i = 1;i <= n;++ i) 
						if(ck(nx[i] + 1,ny[i])) res += mp[nx[i] + 1][ny[i]];
					if(f[r][u][d][l] + res > f[r + 1][u][d][l])
						f[r + 1][u][d][l] = f[r][u][d][l] + res,g[r + 1][u][d][l] = g[r][u][d][l] + 'E';
					else if(f[r][u][d][l] + res == f[r + 1][u][d][l])
						g[r + 1][u][d][l] = min(g[r + 1][u][d][l],g[r][u][d][l] + 'E');
					res = 0;
					for(int i = 1;i <= n;++ i) 
						if(ck(nx[i],ny[i] + 1)) res += mp[nx[i]][ny[i] + 1];
					if(f[r][u][d][l] + res > f[r][u + 1][d][l])
						f[r][u + 1][d][l] = f[r][u][d][l] + res,g[r][u + 1][d][l] = g[r][u][d][l] + 'N';
					else if(f[r][u][d][l] + res == f[r][u + 1][d][l])
						g[r][u + 1][d][l] = min(g[r][u + 1][d][l],g[r][u][d][l] + 'N');
					res = 0;
					for(int i = 1;i <= n;++ i) 
						if(ck(nx[i],ny[i] - 1)) res += mp[nx[i]][ny[i] - 1];
					if(f[r][u][d][l] + res > f[r][u][d + 1][l])
						f[r][u][d + 1][l] = f[r][u][d][l] + res,g[r][u][d + 1][l] = g[r][u][d][l] + 'S';
					else if(f[r][u][d][l] + res == f[r][u][d + 1][l])
						g[r][u][d + 1][l] = min(g[r][u][d + 1][l],g[r][u][d][l] + 'S');
					res = 0;
					for(int i = 1;i <= n;++ i) 
						if(ck(nx[i] - 1,ny[i])) res += mp[nx[i] - 1][ny[i]];
					if(f[r][u][d][l] + res > f[r][u][d][l + 1])
						f[r][u][d][l + 1] = f[r][u][d][l] + res,g[r][u][d][l + 1] = g[r][u][d][l] + 'W';
					else if(f[r][u][d][l] + res == f[r][u][d][l + 1])
						g[r][u][d][l + 1] = min(g[r][u][d][l + 1],g[r][u][d][l] + 'W');
				}
	ll ans = 0;
	string t = "";
	for(int r = 0;r <= k;++ r)
		for(int u = 0;u <= k && u + r <= k;++ u)
			for(int d = 0;d <= k && u + r + d <= k;++ d)
				for(int l = 0;l <= k && u + r + d + l <= k;++ l)
					if(r + u + d + l == k){
						if(f[r][u][d][l] > ans)
							ans = f[r][u][d][l],t = g[r][u][d][l];
						else if(f[r][u][d][l] == ans)
							t = min(t,g[r][u][d][l]);
					}
	cout << ans << endl;
	cout << t;			
	return 0;
}
```

---

