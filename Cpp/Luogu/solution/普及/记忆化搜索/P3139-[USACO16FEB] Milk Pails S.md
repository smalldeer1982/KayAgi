# [USACO16FEB] Milk Pails S

## 题目描述

Farmer John 接到了一份需要立即完成的订单，要求他提供恰好 $M$ 单位的牛奶（$1 \leq M \leq 200$）。不幸的是，他先进的挤奶机刚刚坏了，现在他只有两个容量为整数 $X$ 和 $Y$（$1 \leq X, Y \leq 100$）的牛奶桶可以用来量取牛奶。两个桶最初都是空的。使用这两个桶，他可以执行最多 $K$ 次以下类型的操作（$1 \leq K \leq 100$）：

- 他可以将任意一个桶完全装满。

- 他可以将任意一个桶完全倒空。

- 他可以将一个桶中的牛奶倒入另一个桶，直到前者被倒空或后者被装满（以先发生的情况为准）。

尽管 FJ 意识到他可能无法最终在两个桶中得到恰好 $M$ 单位的牛奶，但请帮助他计算 $M$ 与两个桶中牛奶总量之间的最小误差。也就是说，请计算 $|M-M'|$ 的最小值，其中 $M'$ 是 FJ 可以在两个桶中共同构造的牛奶量。

## 说明/提示

在两步操作中，FJ 可以在他的桶中留下以下数量的牛奶：

```
(0, 0) = 0 单位  
(14, 0) = 14 单位  
(0, 50) = 50 单位  
(0, 14) = 14 单位  
(14, 36) = 50 单位  
(14, 50) = 64 单位  
```

最接近 32 单位的是 14 单位，误差为 18。注意，要倒空第一个桶以得到 (0, 36) 需要额外的步骤。

## 样例 #1

### 输入

```
14 50 2 32```

### 输出

```
18```

# 题解

## 作者：NaVi_Awson (赞：10)

可以不用dp，dfs和bfs也是可以的；

首先 dfs：f[i][j]表示两桶量分别为i，j是否出现过，就可以剪枝；

附上dfs代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
 using namespace std;
int x,y,k,m;
bool f[105][105];
int ans=1e9;
void dfs(int xn,int yn,int kn)
{
    if ((f[xn][yn]==1)||(kn-1>k)) return;
    f[xn][yn]=1;
    ans=min(ans,abs(m-xn-yn));
    dfs(x,yn,kn+1);
    dfs(xn,y,kn+1);
    dfs(0,yn,kn+1);
    dfs(xn,0,kn+1);
    if(x-xn<=yn) dfs(x,yn-(x-xn),kn+1);
    else dfs(xn+yn,0,kn+1);
    if(y-yn<=xn) dfs(xn-(y-yn),y,kn+1);
    else dfs(0,xn+yn,kn+1);
    f[xn][yn]=0;
    return;
}
int main() 
{   
    scanf("%d%d%d%d",&x,&y,&k,&m);
    dfs(0,0,1);
    cout<<ans<<endl;
    return 0;
}
```
其次bfs：思路差不多；c[i][j]表示得到第一个杯子i升，第二个杯子j升，最小的操作次数，也就是在搜索树中层数
初始(0,0)入队，两个杯子中的容量都是0

取出队列首元素：(p,q)

考虑子结点，任意一个杯子倒空，任意一个杯子装满，从一个杯子倒入另一个杯子

bfs代码就不贴了（其实我懒）


---

## 作者：Vic_ (赞：4)

一种半dp的做法，相当于一楼的空间优化。用不着开三维数组，两维即可解决问题。


详细说明请见代码


    

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int x,y,k,m;
int dp[101][101];//用f[i][j]表示一个桶里有i体积牛奶，另一个有j体积牛奶是所需的最少步数
int ans=1 << 30;
int abs(int x)//绝对值
{
    if(x<0)return -x;
    else return x;
}
void add(int a,int b)//状态转移。。。吧，得出新的dp
{
    if(dp[a][b]>=k)return;//超过了就返回
    if(dp[a][b]+1<dp[0][b] || dp[0][b]==-1)
    {
        dp[0][b]=dp[a][b]+1;
        add(0,b);
    }
    if(dp[a][b]+1<dp[a][0] || dp[a][0]==-1)
    {
        dp[a][0]=dp[a][b]+1;
        add(a,0);
    }
    if(dp[a][b]+1<dp[x][b] || dp[x][b]==-1)
    {
        dp[x][b]=dp[a][b]+1;
        add(x,b);
    }
    if(dp[a][b]+1<dp[a][y] || dp[a][y]==-1)
    {
        dp[a][y]=dp[a][b]+1;
        add(a,y);
    }
    if(a+b>=y)
    {
        if(dp[a][b]+1<dp[a+b-y][y] || dp[a+b-y][y]==-1)
        {
            dp[a+b-y][y]=dp[a][b]+1;
            add(a+b-y,y);
        }
    }
    else if(a+b<y)
    {
        if(dp[a][b]+1<dp[0][a+b] || dp[0][a+b]==-1)
        {
            dp[0][a+b]=dp[a][b]+1;
            add(0,a+b);
        }
    }
    if(a+b>=x)
    {
        if(dp[a][b]+1<dp[x][a+b-x] || dp[x][a+b-x]==-1)
        {
            dp[x][a+b-x]=dp[a][b]+1;
            add(x,a+b-x);
        }
    }
    else if(a+b<x)
    {
        if(dp[a][b]+1<dp[a+b][0] || dp[a+b][0]==-1)
        {
            dp[a+b][0]=dp[a][b]+1;
            add(a+b,0);
        }
    }
}
int main()
{
    memset(dp,-1,sizeof(dp));
    cin >> x >> y >> k >> m;
    dp[0][0]=0;
    dp[x][0]=1;
    dp[0][y]=1;
    dp[x][y]=2;//基础状态
    add(0,0);
    add(x,0);
    add(0,y);
    add(x,y);//添加
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
        {
            if(dp[i][j]!=-1&&dp[i][j]<=k&&abs(m-i-j)<ans)ans=abs(m-i-j);//不断求符合情况最小值
        }
    cout << ans;
}
ac
```

---

## 作者：MuYC (赞：3)

#### 前言
这道题目长着就一副**记忆化搜索**/**剪枝**的样子。

于是 DFS 加上记忆化就过掉了这一题。

用时:52ms

占用内存:10.11MB

#### 思路

不难发现，这一题的 $X,Y,K,M$ 都是极其小的，不妨记录一下每个状态:

$D[S][L][R]$ 表示的就是到达总量为 $S$ 的，左边那个桶里面有 $L$ 的牛奶，右边有 $R$ 的牛奶 这个状态的最小操作次数。

那么什么情况下可以直接剪掉不搜了呢？

+ 剪枝$1$ :当前步数如果大于 $K$ 了，那么就不需要搜索下去了(也是终止条件)。
+ 剪枝$2$ :到达当前状态所用的步数大于等于到达当前状态的操作数，剪掉

有了这两个剪枝就可以保证时间复杂度上不会挂了。

那么就是在 DFS 过程中枚举每一个操作。

我们这里假设现在的状态为 $D[S][L][R]$:

#### 操作$1$ :
**在任意一个桶中装满牛奶。**

这个操作执行的条件就是当前有任意一个桶还没有**装满**。

也就是 $L$ != $X$ || $R$ != $Y$

状态就可以转移到($X+R,X,R$) 或者是 ($Y+L,L,Y$)

然后操作数 + 1。

#### 操作$2$:
**倒空任意一个桶**

有一个桶**非空**即可

即 $L$ != $0$ || $R$ != $0$

状态转移为:($R,0,R$) 或者是 ($L,L,0$)

操作数 + 1。

#### 操作$3$ :

**将一个桶里的奶倒入另一个桶中，直到倒空或另一个桶被倒满**

稍微复杂一点点，

$L$ != $X$ || $R$ != $Y$ 同时另外一个桶非空

这时候
```cpp
if(R != 0 && L != X)
    DFS(S , L + min(X - L,R) , R - min(X - L,R), now + 1);
/*这里取min就是模拟R倒空或者倒满的情况*/
```
```cpp
if(L != 0 && R != Y)
    DFS(S , L - min(Y - R,L) , R + min(Y - R,L), now + 1);
/*这里取min就是模拟L倒空或者倒满的情况*/
```

#### 操作完成。

然后就可以过掉这道题了。

本人比较菜，如果dalao们嫌讲得不清楚的话就康康代码吧：

### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int D[205][110][110];
int X,Y,K,M;

void DFS(int S,int L,int R,int now)
{
    if(now > K) return ;//剪枝1
    if(now >= D[S][L][R])return ;//上面提到的剪枝2
    D[S][L][R] = now;
    //操作1
    if(L != X)
    DFS(X + R , X , R , now + 1);
    if(R != Y)
    DFS(L + Y , L , Y , now + 1);
    // --------分割线--------
    //操作2
    if(L != 0)
    DFS(R, 0 , R ,now + 1);
    if(R != 0)
    DFS(L, L , 0 , now + 1);
    // --------分割线--------
    //操作3
    if(R != 0 && L != X)
    DFS(S , L + min(X - L,R) , R - min(X - L,R), now + 1);
    if(L != 0 && R != Y)
    DFS(S , L - min(Y - R,L) , R + min(Y - R,L), now + 1);
    //操作就模拟完了
    return ;
}

int main()
{
    cin >> X >> Y >> K >> M;
    memset(D,0x3f,sizeof(D));//初始化一个极大值
    DFS(0,0,0,0);
    int Ans = 100000005;
    for(int i = 0 ; i <= 200 ; i ++)
    {
    	int flag = 1;
      for(int j = 0 ; j <= X && flag; j ++)
         for(int k = 0 ; k <= Y && flag; k ++)
          if(D[i][j][k] <= K)
          {
              Ans = min(Ans,abs(i - M));
              flag = 0;//减少循环次数
           }
    }
    cout << Ans;
    return 0;
}
```

---

## 作者：SUNCHAOYI (赞：2)

- 题外话：`他有三个桶` 是不是应该改成 `两个桶` 啊 emmm。

----

**方法：** 用 $\texttt{BFS}$ 进行搜索枚举。把三个操作分别转成数学语言即可。

接下来为了表示统一，把当前的两个桶中的牛奶设为 $(m,n)$，则应有 $0 \le m \le X,0 \le n \le Y$。

1. 操作①：**装满牛奶**。很简单，只要把 $m = X$ 或 $n = Y$ 即可。两种情况分别变为 $(X,n)$ 与 $(m,Y)$。
2. 操作②：**倒空牛奶**。也十分容易，把 $m = 0$ 或 $n = 0$，对应的两种情况分别变为 $(0,n)$ 与 $(m,0)$。
3. 操作③：**相互倒牛奶**。这里涉及到多种的分类讨论。首先是第一个桶中的牛奶到给第二个桶中，则会出现两种情况：第一个桶倒完与未倒完(未到完即对应第二个桶已倒满)，将两种情况整理可**合并成一个式子**：$(m - \min (m,Y - n),\min (Y,n + m))$。第二大类与第一类相反，所以式子改变一下变成：$(\min (X,n + m),n - \min (n,X - m))$。

那么是否需要每一次操作后都将这 $8$ 大类加入到队列中去呢？肯定不需要，否则冗余的操作会使程序 $\texttt{TLE}$。看下 $X,Y$ 的数据范围，$1 \le X,Y \le 100$，开个二维数组 `vis[105][105]`，`vis[i][j]` **表示两个桶分别装 $i$ 与 $j$ 的单位的牛奶的情况是否已经出现过**。因此我们只需要将**未出现过的情况**加入到队列中去就行了。

最后就是答案的更新了，不用说，**每次在取出当前队列的队首元素后进行判断更新** $ans = \min(ans,M - |m + n|)$ 就完事了啊！

----

具体实现的代码：
```
#include <iostream>
#include <queue>
#include <cmath> 
#define INF 0x3f3f3f3f
using namespace std; 
const int MAX = 105;
struct _pair
{
	int dx,dy;
};
bool vis[MAX][MAX];
int x,y,k,m,ans = INF;
queue <_pair> q;  
void search (int num);
int main ()
{
	cin>>x>>y>>k>>m;
	q.push ({0,0});vis[0][0] = 1;//一开始的情况 
	search (0);
	cout<<ans<<endl;
	return 0;
}
void search (int num)
{
	queue <_pair> milk;//将最新的情况压入队列 
	if (num == k + 1) return ;//次数已到,注意是k + 1 次 
	while (!q.empty ())//更新所有可能的情况 
	{
		_pair now = q.front ();q.pop ();
		ans = min (ans,abs (m - now.dx - now.dy));//更新最优答案 |m - m'|
		//若此情况没有出现过，则加入队列中
		
		//装满 
		if (!vis[x][now.dy]) milk.push ({x,now.dy}),vis[x][now.dy] = 1;
		if (!vis[now.dx][y]) milk.push ({now.dx,y}),vis[now.dx][y] = 1;
		
		//倒空
		if (!vis[now.dx][0]) milk.push ({now.dx,0}),vis[now.dx][0] = 1;
		if (!vis[0][now.dy]) milk.push ({0,now.dy}),vis[0][now.dy] = 1; 
		
		//互相倒
		if (!vis[now.dx - min (now.dx,y - now.dy)][min (y,now.dy + now.dx)])
			milk.push ({now.dx - min (now.dx,y - now.dy),min (y,now.dy + now.dx)}),vis[now.dx - min (now.dx,y - now.dy)][min (y,now.dy + now.dx)] = 1;
		if (!vis[min (x,now.dx + now.dy)][now.dy - min (now.dy,x - now.dx)])
			milk.push ({min (x,now.dx + now.dy),now.dy - min (now.dy,x - now.dx)}),vis[min (x,now.dx + now.dy)][now.dy - min (now.dy,x - now.dx)] = 1;
	}
	while (!milk.empty ()) q.push (milk.front ()),milk.pop ();//将所有可能放入 q 中
	search (num + 1); 
} 
```

----

$\texttt{end:}$ 注意一下**递归的边界**！！！  
`if (num == k + 1) return ;` 写成 `if (num == k) return ;` 调了我好久啊 $\texttt{qwq}$！

---

## 作者：SIGSEGV (赞：2)

一看到此题就联想到了以前用广搜做的一道类似的题......

广搜做很简单，我还提心吊胆的加了优化，防止TLE

附上评测结果 用时: 0ms / 内存: 3246KB的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int b1,b2,need,ans = INT_MAX,kk;
struct Node{int x,y,cnt;};
//x为1桶的单位数，y为2桶的单位数
void bfs()
{
    bool vis[101][101][101] = {};memset(vis,0,sizeof(vis));//状态记录数组
    queue<Node> q;//防止MLE
    q.push({0,0,0});vis[0][0][0] = 1;
    while (!q.empty())
    {
        Node n = q.front();q.pop();
        if(n.cnt == kk || n.x == 0 || n.y == 0)//判断 如两个桶里有任意一个为0，也做一次检查（之后可以一直倒空这个桶）
        {
        	ans = min(ans,abs(n.x + n.y - need));//cout << n.x + n.y << endl;
        	if (n.cnt == kk) continue;//防止不必要状态扩展
        }
        int x = n.x,y = n.y,cnt = n.cnt + 1;//扩展
        if(!vis[b1][y][cnt]) q.push({b1,y,cnt});
        vis[b1][y][cnt] = 1;
        if(!vis[x][b2][cnt]) q.push({x,b2,cnt});
        vis[x][b2][cnt] = 1;
        if(!vis[0][y][cnt]) q.push({0,y,cnt});
        vis[0][y][cnt] = 1;
        if(!vis[x][0][cnt]) q.push({x,0,cnt});
        vis[x][0][cnt] = 1;
        int Y = x + y,X = 0;
        if(Y > b2) X = Y - b2,Y = b2;
        if(!vis[X][Y][cnt]) q.push({X,Y,cnt});
        vis[X][Y][cnt] = 1;
        X = x + y,Y = 0;
        if(X > b1) Y = X - b1,X = b1;
        if(!vis[X][Y][cnt]) q.push({X,Y,cnt});
        vis[X][Y][cnt] = 1;
    }
    printf("%d",ans);
}
int main ()
{
    scanf("%d%d%d%d",&b1,&b2,&kk,&need);
    bfs();
    return 0;
} 
```

---

## 作者：Vin_1999 (赞：1)

这翻译也是······

题意就是三种决策，倒空a或b，充满a或b,把a倒到b里（或者反过来）。

求最接近m的a+b。

死于没看清楚样例解释······






```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<cmath>
#include<climits>
#include<cstring>
#include<string>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
const int maxn=210;
static int x,y,m,k,ans;
static bool dp[maxn][maxn][maxn];
int main()
{
        freopen("e:/in.txt","r",stdin);
    scanf("%d%d%d%d",&x,&y,&k,&m);
    dp[0][0][0]=1;
    rep(i,1,k) for(int j1=0;j1<=x;j1++) for(int j2=0;j2<=y;j2++)
    if(dp[i-1][j1][j2])
    {
          dp[i][0][j2]=dp[i][j1][0]=1;
              dp[i][j1][j2]=1;
        dp[i][x][j2]=dp[i][j1][y]=1;
        int a1=min(j1,y-j2),a2=min(j2,x-j1);
        dp[i][j1-a1][j2+a1]=1;dp[i][j1+a2][j2-a2]=1;
    }
    ans=m;
    rep(j1,0,x) rep(j2,0,y) if(dp[k][j1][j2])
    ans=min(abs(j1+j2-m),ans);
    printf("%d",ans);
    return 0;    
}by-fjlyyz ljy
```

---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候，都已经对题目有了深刻的了解

这里希望大家多看看数据范围,$ (1 \leq X, Y \leq 100) $

这这这这这么小的数据，显然可以用$DFS$解决

我们每次搜索到一个状态的时候，我们可以用记忆化来解决时间的
问题

我们可以在一个状态的时候暴力枚举通过他可以转移到的状态

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int x,y,k,m;
int ans=1000000;
bool vis[310][310];
inline void dfs(int xx,int yy,int kk){
	if(vis[xx][yy]==1)
		return;
	if((kk-1)>k)
		return;
	vis[xx][yy]=1;
	ans=min(ans,abs(xx+yy-m));
	dfs(x,yy,kk+1);
	dfs(xx,y,kk+1);
	dfs(0,yy,kk+1);
	dfs(xx,0,kk+1);
	if(x-xx<=yy)
		dfs(x,yy-(x-xx),kk+1);
	else
		dfs(xx+yy,0,kk+1);
	if(y-yy<=xx)
		dfs(xx-(y-yy),y,kk+1);
	else
		dfs(0,xx+yy,kk+1);
	vis[xx][yy]=0;
	return;
} 
signed main(){
	x=read();
	y=read();
	k=read();
	m=read();
	dfs(0,0,1);
	write(ans);
	return 0;
}
```


---

