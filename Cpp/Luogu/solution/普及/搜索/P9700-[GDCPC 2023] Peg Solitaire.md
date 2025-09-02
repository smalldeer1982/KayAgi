# [GDCPC 2023] Peg Solitaire

## 题目描述

``独立钻石``是一种单人桌游。游戏在 $n$ 行 $m$ 列的棋盘上进行，棋盘上的每一格要么是空格，要么有一枚棋子。一开始，棋盘上共有 $k$ 枚棋子。

在游戏中，玩家可以选择一枚棋子，将它跳过相邻棋子到空格上，并移除被跳过的棋子。具体来说，令 $(i, j)$ 表示位于第 $i$ 行第 $j$ 列的格子，玩家可以执行以下四种操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/pgosoztu.png)

给定一个初始的棋盘，求经过任意次操作（包括零次）之后，棋盘上最少能剩余几枚棋子。

## 样例 #1

### 输入

```
3
3 4 5
2 2
1 2
1 4
3 4
1 1
1 3 3
1 1
1 2
1 3
2 1 1
2 1```

### 输出

```
2
3
1```

# 题解

## 作者：ran_qwq (赞：9)

没人写 bfs & 状压的吗。

---
把状态压缩成一个二进制数，$0$ 表示没有棋子，$1$ 表示有，第 $(i-1)\times m+j$ 位表示第 $i$ 行第 $j$ 列的格子。

枚举要移动的棋子 $(x,y)$，再枚举和它相邻的棋子 $(nx,ny)$，棋子 $(x,y)$ 要跳到 $(mx,my)$。如果 $(mx,my)$ 处没有棋子就把 $(x,y)$ 和 $(nx,ny)$ 处的棋子消除掉，在 $(mx,my)$ 处放一颗棋子。

状态最多有 $\sum\limits_{i=0}^kC_{nm}^i$ 个，$n=m=k=6$ 时是 $2.7\times10^6$，实际上可达的只有很少一部分，时间复杂度 $O(\text{能过})$。但是表示状态的二进制数很大，所以要开 map。

```cpp
#include<bits/stdc++.h>
#define ui unsigned int
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define fir first
#define sec second
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f,dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int read() {int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x) {if(x<0) {putchar('-'),Write(-x);return;}if(x<10) {putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s) {Write(x),printf("%s",s);}
int n,m,k,ans;map<ll,int>vis;
void solve()
{
	n=read(),m=read(),k=ans=read();ll stat=0;vis.clear();
	for(int i=1,x,y;i<=k;i++) x=read(),y=read(),stat|=1ll<<((x-1)*m+y-1);
	queue<pair<ll,int>>q;q.push({stat,k}),vis[stat]=1;
	while(!q.empty())
	{
		ll u=q.front().fir;int cnt=q.front().sec;
		q.pop(),ans=min(ans,cnt);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				if(!(u&(1ll<<((i-1)*m+j-1)))) continue;
				for(int p=0;p<4;p++)
				{
					int nx=i+dx[p],ny=j+dy[p],mx=nx+dx[p],my=ny+dy[p];
					if(mx<1||mx>n||my<1||my>m||!(u&(1ll<<((nx-1)*m+ny-1)))||u&(1ll<<((mx-1)*m+my-1))) continue;
					ll v=u^(1ll<<((i-1)*m+j-1))^(1ll<<((nx-1)*m+ny-1))^(1ll<<((mx-1)*m+my-1));
					if(!vis[v]) vis[v]=1,q.push({v,cnt-1});
				}
			}
	}
	write(ans,"\n");
}
signed main()
{
	int T=read();
	while(T--) solve();
}
```

---

## 作者：lyh0217 (赞：6)

###### [题目传送门](https://www.luogu.com.cn/problem/P9700)

## 思路

由于 $n$，$m$，$k$，都 $\leq6$，而 $T$ 也$\leq 20$，可以直接暴力搜索。

每一次寻找一个当前存在棋子的格子，往上，下，左，右四个方向，判断合不合法，判断条件为题面中的图，若合法，就按题意走出一步，并继续搜索。

还有，注意回溯和处理边界！

时间复杂度为 $O(T \times 4^k)$，可以通过此题。
## AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans;
bool vis[15][15];
void dfs(int p)
{
	ans=min(ans,p);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			if(vis[i][j])
			{
				if(j>=3&&vis[i][j-1]&&!vis[i][j-2])//往左跳
				{
					vis[i][j-1]=0;
					vis[i][j]=0;
					vis[i][j-2]=1;
					dfs(p-1);
					vis[i][j-1]=1;
					vis[i][j]=1;
					vis[i][j-2]=0;
				}
				if(i>=3&&vis[i-1][j]&&!vis[i-2][j])//往上跳
				{
					vis[i-1][j]=0;
					vis[i][j]=0;
					vis[i-2][j]=1;
					dfs(p-1);
					vis[i-1][j]=1;
					vis[i][j]=1;
					vis[i-2][j]=0;
				}
				if(j<=m-2&&vis[i][j+1]&&!vis[i][j+2])//往右跳
				{
					vis[i][j+1]=0;
					vis[i][j]=0;
					vis[i][j+2]=1;
					dfs(p-1);
					vis[i][j+1]=1;
					vis[i][j]=1;
					vis[i][j+2]=0;
				}
				if(i<=n-2&&vis[i+1][j]&&!vis[i+2][j])//往下跳
				{
					vis[i+1][j]=0;
					vis[i][j]=0;
					vis[i+2][j]=1;
					dfs(p-1);
					vis[i+1][j]=1;
					vis[i][j]=1;
					vis[i+2][j]=0;
				}
			}
		}
	}
}
int main(){
	int t;
	cin>>t;
	while(t--)
	{
		memset(vis,0,sizeof(vis));  //多测不清空，爆零两行泪
		ans=6;          //因为最多有六个棋子，所以初始化为六即可
		cin>>n>>m>>k;
		for(int i=1;i<=k;i++)
		{
        int x,y;
			cin>>x>>y;
			vis[x][y]=1;  //标记在此位置有一个棋子
		}
		dfs(k);
		cout<<ans<<endl;
	}
	return 0;
}
```
[评测记录](https://www.luogu.com.cn/record/127923826)

---

## 作者：封禁用户 (赞：5)

注意到原题题目的范围很小，我们可以直接 dfs 枚举每个棋子往哪里跳，能否消去其他的棋子，然后再回溯，重新统计其他棋子的跳法。

代码实现很简单很暴力，这里就不放了。

---

## 作者：Zaku (赞：2)

[Link.](https://www.luogu.com.cn/problem/P9700)

$\mathrm{Sol:}$

本题是裸的 dfs。

因为每个棋子只能被横向或者纵向跳过，因此当棋盘上存在 $k$ 枚棋子时，共有 $2k$ 种操作可以选择。又因为每一步都将减少 $1$ 枚棋子，因此至多执行 $(k-1)$ 步。

$\mathrm{Code:}$
```cpp
const int N = 10;
int n, m, k;
int ans;
int g[N][N];
void dfs(int k){
	ans = min(ans, k);
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			if (g[i][j]){
				if (i > 1 && i < n){
					//up
					if (!g[i - 1][j] && g[i + 1][j]){
						g[i + 1][j] = g[i][j] = 0;
						g[i - 1][j] = 1;
						dfs(k - 1);
						g[i + 1][j] = g[i][j] = 1;
						g[i - 1][j] = 0;
					}
					//down
					if (g[i - 1][j] && !g[i + 1][j]){
						g[i - 1][j] = g[i][j] = 0;
						g[i + 1][j] = 1;
						dfs(k - 1);
						g[i - 1][j] = g[i][j] = 1;
						g[i + 1][j] = 0;
					}
				}
				if (j > 1 && j< m){
					// right
					if (g[i][j - 1] && !g[i][j + 1]){
						g[i][j - 1] = g[i][j] = 0;
						g[i][j + 1] = 1;
						dfs(k - 1);
						g[i][j - 1] = g[i][j] = 1;
						g[i][j + 1] = 0;
					}
					//left
					if (!g[i][j - 1] && g[i][j + 1]){
						g[i][j + 1] = g[i][j] = 0;
						g[i][j - 1] = 1;
						dfs(k - 1);
						g[i][j + 1] = g[i][j] = 1;
						g[i][j - 1] = 0;
					}
				}
			}
		}
	}
}
void solve(){
	cin >> n >> m >> k;
	memset(g, 0, sizeof g);
	for (int i = 1; i <= k; i ++ ){
		int x, y;
		cin >> x >> y;
		g[x][y] = 1;
	}
	ans = k;
	dfs(k);
	cout << ans << '\n';
}
```

自认写的比较美观。

---

## 作者：Qiu_chen (赞：1)

## 思路

我们发现数据范围很小，可以直接模拟递归。

注意：递归完要回溯！

## 代码

以下为 C++ 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 2e9+9
const int maxn=1e6+10;
const int mod=1e9+7;
int n,m,k,x,y,ans;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int len=4;
int index(int x,int y){
	return x*m+y;
}
bool check(vector<int>& mp,int x,int y,int lx,int ly){
	int x1=x+lx,x2=x+2*lx;
	int y1=y+ly,y2=y+2*ly;
	if(x2>=n or x2<0 or y2>=m or y2<0)
		return false;
	return !mp[index(x2,y2)]&&mp[index(x1,y1)];
}
void dfs(vector<int>& mp,int k){
	ans=min(ans,k);
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			if(!mp[index(i,j)])
				continue;
			int x=i,y=j;
			for(int l=0;l<len;++l){
				if(!check(mp,x,y,dx[l],dy[l]))
					continue;
				int x2=x+2*dx[l],x1=x+dx[l];
				int y2=y+2*dy[l],y1=y+dy[l];
				int idx=index(x,y),idx2=index(x2,y2),idx1=index(x1,y1);
				mp[idx]=0;
				mp[idx2]=1;
				mp[idx1]=0;
				dfs(mp,k-1);
				mp[idx1]=1;
				mp[idx2]=0;
				mp[idx]=1;
			}
		}
	}
}
void solve(){
	cin>>n>>m>>k;
	vector<int> mp(n*m,0);
	for(int i=0;i<k;++i){
		cin>>x>>y;
		--x;
		--y;
		mp[x*m+y]=1;
	}
	ans=k;
	dfs(mp,k);
	cout<<ans<<endl;
}
int main(){
	int t=1,cas=1;
	cin>>t;
	while(t--){
		if(0)  printf("case :%d\n",cas++);
		solve();
	}
	return 0;
}
```

严禁抄袭！

---

## 作者：2011FYCCCTA (赞：1)

### [原题](https://www.luogu.com.cn/problem/P9700)

---
### 思路

注意到数据范围很小，可以直接暴力 dfs，每次枚举符合条件的格子，并更新棋盘和答案。

**注意：**
1. dfs 完要回溯。
2. 不要忘记每次变量的初始化。

---
### 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t , n , m , k , ans , x , y , mp[10][10];

int min(int a , int b) {return (a < b ? a : b);}

void dfs(int mp[10][10] , int k)
{
    ans = min(ans , k);
    //暴力枚举
    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j <= m ; j++)
        {
            if (i >= 3 && mp[i][j] && mp[i - 1][j] && !mp[i - 2][j])
            {
                mp[i][j] = mp[i - 1][j] = 0;
                mp[i - 2][j] = 1;
                dfs(mp , k - 1);
                mp[i][j] = mp[i - 1][j] = 1;
                mp[i - 2][j] = 0;
            }
            else if (i <= n - 2 && mp[i][j] && mp[i + 1][j] && !mp[i + 2][j])
            {
                mp[i][j] = mp[i + 1][j] = 0;
                mp[i + 2][j] = 1;
                dfs(mp , k - 1);
                mp[i][j] = mp[i + 1][j] = 1;
                mp[i + 2][j] = 0;
            }
            else if (j >= 3 && mp[i][j] && mp[i][j - 1] && !mp[i][j - 2])
            {
                mp[i][j] = mp[i][j - 1] = 0;
                mp[i][j - 2] = 1;
                dfs(mp , k - 1);
                mp[i][j] = mp[i][j - 1] = 1;
                mp[i][j - 2] = 0;
            }
            else if (j <= m - 2 && mp[i][j] && mp[i][j + 1] && !mp[i][j + 2])
            {
                mp[i][j] = mp[i][j + 1] = 0;
                mp[i][j + 2] = 1;
                dfs(mp , k - 1);
                mp[i][j] = mp[i][j + 1] = 1;
                mp[i][j + 2] = 0;
            }
        }
    return;
}

signed main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> k;
        memset(mp , 0 , sizeof(mp)); ans = 40;
        for (int i = 1 ; i <= k ; i++)
        {
            cin >> x >> y;
            mp[x][y] = 1;
        }
        dfs(mp , k);
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：minVan (赞：1)

注意到 $n,m$ 的范围不大，我们可以将每个棋子的位置在网格中标出来，再进行深度优先搜索。

令 $f_{i,j}=1$ 表示位置 $(i,j)$ 有一枚棋子，$f_{i,j}=0$ 表示位置 $(i,j)$ 没有棋子。

![](https://cdn.luogu.com.cn/upload/image_hosting/pgosoztu.png)

只需要按照要求模拟即可。

dfs 代码如下：

```cpp
inline void dfs(int gs) {
	ans = min(ans, gs);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(f[i][j]) {
				if(i >= 3 && f[i - 1][j] && !f[i - 2][j]) {
					f[i - 1][j] = f[i][j] = 0;
					f[i - 2][j] = 1;
					dfs(gs - 1);
					f[i - 1][j] = f[i][j] = 1;
					f[i - 2][j] = 0;
				}
				if(i <= n - 2 && f[i + 1][j] && !f[i + 2][j]) {
					f[i + 1][j] = f[i][j] = 0;
					f[i + 2][j] = 1;
					dfs(gs - 1);
					f[i + 1][j] = f[i][j] = 1;
					f[i + 2][j] = 0;
				}
				if(j >= 3 && f[i][j - 1] && !f[i][j - 2]) {
					f[i][j - 1] = f[i][j] = 0;
					f[i][j - 2] = 1;
					dfs(gs - 1);
					f[i][j - 1] = f[i][j] = 1;
					f[i][j - 2] = 0;
				}
				if(j <= m - 2 && f[i][j + 1] && !f[i][j + 2]) {
					f[i][j + 1] = f[i][j] = 0;
					f[i][j + 2] = 1;
					dfs(gs - 1);
					f[i][j + 1] = f[i][j] = 1;
					f[i][j + 2] = 0;
				}
			}
		}
	}
}
```

---

## 作者：ICU152_lowa_IS8 (赞：1)

首先上来看到题面有四种移动方式，本质是：

当红色方框和橙色方框有棋子时，可进行操作将红色、其中一个橙色方框清空，与橙色方框相连的那个绿色方框摆上棋子。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ej2qtfc.png)

然后我们会注意到这个题目有一个很友善的数据范围（$1\leq n,m\leq6$），显然直接爆搜就行了。

类似于贪心，能走就走（显然在能走动的时候走比不走更优）。但注意最优解是有走动顺序的，所以才需要用搜索。

注意：

1.回溯；

2.变量名不要打错。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,ans;
bool mp[10][10];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
void dfs(int v){
	ans=min(ans,v);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]){
				for(int k=0;k<4;k++){
					if(i+dx[k]*2>=1&&i+dx[k]*2<=n&&j+dy[k]*2>=1&&j+dy[k]*2<=m&&mp[i+dx[k]*2][j+dy[k]*2]^1&&mp[i+dx[k]][j+dy[k]]){
						mp[i+dx[k]][j+dy[k]]=mp[i][j]=0;
						mp[i+dx[k]*2][j+dy[k]*2]=1;
//						cout<<k<<" "<<i<<" "<<j<<" "<<i+dx[k]*2<<" "<<y+dy[k]*2<<endl;
						dfs(v-1);
						mp[i+dx[k]][j+dy[k]]=mp[i][j]=1;
						mp[i+dx[k]*2][j+dy[k]*2]=0;
					}
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		memset(mp,0,sizeof(mp));
		cin>>n>>m>>k;
		ans=k;
		for(int i=1;i<=k;i++){
			cin>>x>>y;
			mp[x][y]=1;
		}
		dfs(k);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Super_Builder (赞：1)

## 思路

看数据范围，发现范围很小，直接用**搜索**。   

搜索时枚举每个点，如果有棋子就枚举方向，如果这个方向合法，则将剩余棋子数减一，继续搜索。

搜索时参数只需要传当前棋子数就行了。

有以下几点需要**注意**

- 多组数据每次需要初始化。

- 判断是否合法时要注意。

- 每次记得回溯棋子。

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,dx1[4]={-2,0,2,0},dy1[4]={0,-2,0,2},dx2[4]={-1,0,1,0},dy2[4]={0,-1,0,1};
int minn=1e9;
bool a[10][10];
void dfs(int cnt){
	for(int x=1;x<=n;x++){
		for(int y=1;y<=m;y++){
			if(!a[x][y])continue;
			for(int i=0;i<4;i++){
				int nx=x+dx1[i];
				int ny=y+dy1[i];
				if(nx<1||nx>n||ny<1||ny>m||!a[x+dx2[i]][y+dy2[i]]||a[nx][ny]){
					continue;
				}
				a[x+dx2[i]][y+dy2[i]]=0;
				a[x][y]=0;
				a[nx][ny]=1;
				dfs(cnt-1);
				a[x+dx2[i]][y+dy2[i]]=1;
				a[x][y]=1;
				a[nx][ny]=0;
			}
		}
	}
	minn=min(minn,cnt);

}
int main(){
	int T;
	cin>>T;
	while(T--){
		memset(a,0,sizeof a);
		cin>>n>>m>>k;minn=k;
		for(int i=1;i<=k;i++){
			int x,y;
			cin>>x>>y;
			a[x][y]=1;
		}
		dfs(k);
		cout<<minn<<endl;
	}
    return 0;
}
```


---

## 作者：a1a2a3a4a5 (赞：0)

# P9700 [GDCPC2023] Peg Solitaire 
## 题意
1. 跳大马，被跳过的马都被跳没了，希望最后的马最少。
## 思路
1. 小小的 $ n $ 可以让我们把复杂度拉满，考虑搜索。
2. 我们可以 dfs，然后添加一下跳跃的状态。
3. 怎么回溯？这时候 dfs 的特性就显现出来了：删除记录可以直接把下标减一个，因为最后一个记录肯定是当前走的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool wor[8][8];
int t,n,m,k,si,da,cnt;// si 是死了几个。
struct xxx {int x,y;} qi[1010];
void dfs()
{
	da=min(da,k-si);//记录答案。
	for(int j=1;j<=cnt;j++)//枚举已有状态。
	{
		if(wor[qi[j].x][qi[j].y])//还活着？
		{
			for(int v=1;v<=cnt;v++)
			{
				if(wor[qi[v].x][qi[v].y])//还活着？
				{
					if(abs(qi[v].x-qi[j].x)==1&&qi[j].y==qi[v].y)//上下邻居。
					{
						if(qi[v].x>qi[j].x)//下面邻居。
						{
							if(qi[v].x+1<=n)//判断越界。
								if(!wor[qi[v].x+1][qi[j].y])
								{
									wor[qi[j].x][qi[j].y]=0,wor[qi[v].x][qi[v].y]=0,wor[qi[v].x+1][qi[j].y]=1,
									si++,qi[++cnt].x=qi[v].x+1,qi[cnt].y=qi[j].y,
									//记录。
									dfs(),
									cnt--,si--,wor[qi[j].x][qi[j].y]=1,wor[qi[v].x][qi[v].y]=1,wor[qi[v].x+1][qi[j].y]=0;
									//回溯。
								}
						}
						else//上面邻居。
						{
							if(qi[v].x-1>0)
								if(!wor[qi[v].x-1][qi[j].y])
								{
									wor[qi[j].x][qi[j].y]=0,wor[qi[v].x][qi[v].y]=0,wor[qi[v].x-1][qi[j].y]=1,
									si++,qi[++cnt].x=qi[v].x-1,qi[cnt].y=qi[j].y,
									dfs(),
									cnt--,si--,wor[qi[j].x][qi[j].y]=1,wor[qi[v].x][qi[v].y]=1,wor[qi[v].x-1][qi[j].y]=0;
								}
						}
						
					}
					else if(abs(qi[v].y-qi[j].y)==1&&qi[j].x==qi[v].x)//左右邻居。
					{
						if(qi[v].y>qi[j].y)//右边邻居。
						{
							if(qi[v].y+1<=m)
								if(!wor[qi[v].x][qi[v].y+1])
								{
									wor[qi[j].x][qi[j].y]=0,wor[qi[v].x][qi[v].y]=0,wor[qi[j].x][qi[v].y+1]=1,
									si++,qi[++cnt].x=qi[j].x,qi[cnt].y=qi[v].y+1,
									dfs();
									cnt--,si--,wor[qi[j].x][qi[j].y]=1,wor[qi[v].x][qi[v].y]=1,wor[qi[j].x][qi[v].y+1]=0;
								}
						}
						else//左边邻居。
						{
							if(qi[v].y-1>0)
								if(!wor[qi[v].x][qi[v].y-1])
								{
									wor[qi[j].x][qi[j].y]=0,wor[qi[v].x][qi[v].y]=0,wor[qi[j].x][qi[v].y-1]=1,
									si++,qi[++cnt].x=qi[j].x,qi[cnt].y=qi[v].y-1,
									dfs(),
									cnt--,si--,wor[qi[j].x][qi[j].y]=1,wor[qi[v].x][qi[v].y]=1,wor[qi[j].x][qi[v].y-1]=0;
								}
						}
					}
				}
			}
			
		}
	}
}
int main()
{
	cin>>t;
	for(int i1=1;i1<=t;i1++)
	{
		si=0,da=36;
		cin>>n>>m>>k;cnt=0;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) wor[i][j]=0;
		for(int i=1;i<=k;i++) cin>>qi[i].x>>qi[i].y,wor[qi[i].x][qi[i].y]=1,cnt++;
		dfs();
		cout<<da<<"\n";
	}
	return 0;
}
```

---

## 作者：ccg12345 (赞：0)

签到题。

## 思路

注意到数据范围 $n, m, k \le 6$，考虑直接搜索，枚举可跳过的格子，具体细节见代码。

这里要注意下复杂度的问题，当剩下 $t$ 枚棋子时最多会进行 $2 \times t$ 次递归，每次至少减少一颗棋子，最终至少剩下一颗棋子，故复杂度为 $O(T \times m \times n \times 2^{k-1} \times k!)$，无需加任何剪枝即可通过。

附代码：

```
#include <bits/stdc++.h>
using namespace std;
bool vis[11][11];
int n, m, ans;
void dfs(int k)
{
	ans = min(ans, k);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(vis[i][j])
			{
				if(i > 1 && i < n && vis[i - 1][j] && !vis[i + 1][j]) //向上跳
				{
					vis[i - 1][j] = 0, vis[i][j] = 0, vis[i + 1][j] = 1;
					dfs(k - 1);
					vis[i - 1][j] = 1, vis[i][j] = 1, vis[i + 1][j] = 0; //回溯
				}
				if(i > 1 && i < n && !vis[i - 1][j] && vis[i + 1][j]) //向下跳
				{
					vis[i - 1][j] = 1, vis[i][j] = 0, vis[i + 1][j] = 0;
					dfs(k - 1);
					vis[i - 1][j] = 0, vis[i][j] = 1, vis[i + 1][j] = 1;
				}
				if(j > 1 && j < m && vis[i][j - 1] && !vis[i][j + 1]) //向左跳
				{
					vis[i][j - 1] = 0, vis[i][j] = 0, vis[i][j + 1] = 1;
					dfs(k - 1);
					vis[i][j - 1] = 1, vis[i][j] = 1, vis[i][j + 1] = 0;
				}
				if(j > 1 && j < m && !vis[i][j - 1] && vis[i][j + 1]) //向右跳
				{
					vis[i][j - 1] = 1, vis[i][j] = 0, vis[i][j + 1] = 0;
					dfs(k - 1);
					vis[i][j - 1] = 0, vis[i][j] = 1, vis[i][j + 1] = 1;
				}
			}
}
void slv()
{
	int k;
	ans = 2e9;
	cin >> n >> m >> k;
	memset(vis, 0, sizeof vis);
	for(int i = 1, a, b; i <= k; i++)
		cin >> a >> b, vis[a][b] = 1;
	dfs(k);
	cout << ans << endl;
}
int main()
{
	int t;
	cin >> t;
	while(t--)
		slv();
	return 0;
}
```


---

## 作者：WuMin4 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9700)

# 题意
每次可以选择棋盘上的一个棋子，让这个棋子跳过相邻的一个棋子并且吃掉跳过的棋子，问你棋盘上最少能剩余几枚棋子。

# 思路
$1 \le n,m \le 6$，于是 dfs + 回溯暴力枚举。

具体见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k,ans;
int mv[4][2]={{2,0},{-2,0},{0,2},{0,-2}};//棋子的移动方向
bool c[10][10];
bool canMove(int x,int y,int dx,int dy){
	int nx=x+dx,ny=y+dy;//这个棋子跳过去后的坐标
	int jx=x+dx/2,jy=y+dy/2;//被吃掉的的棋子的坐标
	if(nx<1||ny<1||nx>n||ny>m) return false;//判断越界
	if(c[jx][jy]==false) return false;//没有相邻的棋子
	if(c[nx][ny]==true) return false;//跳过去后的坐标已经有了棋子
	return true;
}
void dfs(int mink){//mink代表剩下的棋子
	ans=min(ans,mink);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){//枚举x,y坐标
			if(c[i][j]==true){//这个位置有棋子
				for(int v=0;v<4;v++){
					int dx=mv[v][0],dy=mv[v][1];
					if(canMove(i,j,dx,dy)){//可以走到这个位置
						c[i][j]=false;//去掉本来位置的棋子
						c[i+dx/2][j+dy/2]=false;//去掉吃掉的棋子
						c[i+dx][j+dy]=true;//加上棋子跳过去的位置
						dfs(mink-1);//总棋子数减1
						c[i][j]=true;
						c[i+dx/2][j+dy/2]=true;
						c[i+dx][j+dy]=false;//回溯
					}
				}
			}
		}
	}
}
int main(){
	cin>>T;
	while(T--){
		memset(c,0,sizeof(c));
		ans=INT_MAX;//初始化
		cin>>n>>m>>k;
		for(int x,y,i=1;i<=k;i++){
			cin>>x>>y;
			c[x][y]=true;
		}
		dfs(k);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

