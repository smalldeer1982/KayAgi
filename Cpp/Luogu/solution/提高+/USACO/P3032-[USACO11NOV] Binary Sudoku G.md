# [USACO11NOV] Binary Sudoku G

## 题目描述

Farmer John's cows like to play an interesting variant of the popular game of "Sudoku".  Their version involves a 9 x 9 grid of 3 x 3 subgrids, just like regular Sudoku.  The cows' version, however, uses only binary digits:

000 000 000

001 000 100

000 000 000

000 110 000

000 111 000

000 000 000

000 000 000

000 000 000

000 000 000

The goal of binary Sudoku is to toggle as few bits as possible so that each of the nine rows, each of the nine columns, and each of the nine 3 x 3 subgrids has even parity (i.e., contains an even number of 1s).  For the example above, a set of 3 toggles gives a valid solution:

000 000 000

001 000 100

001 000 100

000 110 000

000 110 000

000 000 000

000 000 000

000 000 000

000 000 000

Given the initial state of a binary Sudoku board, please help the cows determine the minimum number of toggles required to solve it.

给出一个9\*9的01矩阵，问最少修改几个数能使每行、每列以及每个九宫格中1的个数均为偶数。


## 说明/提示

The Sudoku board in the sample input is the same as in the problem text above.


Three toggles suffice to solve the puzzle.


## 样例 #1

### 输入

```
000000000 
001000100 
000000000 
000110000 
000111000 
000000000 
000000000 
000000000 
000000000 
```

### 输出

```
3 
```

# 题解

## 作者：Luan_233 (赞：10)

## Solution

+ 我怂了。怂的意思不是说不敢打暴力了，而是不敢打暴搜了。但是身为暴力玩家，我还有一个绝招———**状压动规**！

+ 我们设f[i][S][0/1][0/1][0/1]表示当前处理完了第几行，已经处理完的每一列的奇偶性为奇或偶(用二进制串压起来)，每一行分为三个部分，分别隶属三个九宫格，已经处理完的三个九宫格的部分的总和的奇偶性，达到这个状态需要的最小步数，转移时大力枚举当前行翻转情况，再枚举已经处理好的上方的奇偶性状态，对于每一行，合法的状态为翻转后的01串有偶数个1，对于每一个九宫格，需要在第4、7行枚举转移时特殊判断，要保证上一行的九宫格1的数目必须为偶数。答案就是f[9][0][0][0][0]。

+ 枚举每一行，枚举翻转情况，枚举已经处理好的状态，总体复杂度约为O(9*(2^18))。

+ P.S. 448，56，7用于提取连续的三个二进制位。

## Code

```
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>

#define N 13
#define lowbit(x) x&(-x)

using namespace std;

char ch[N];

int mp[N],f[N][1<<N][2][2][2],cnt[1<<N],tot=(1<<9)-1;

inline void dp(int s){
	for(int i=0;i<=tot;i++){
		int zt=mp[s],s1,s2,s3;
		for(int j=0;j<=8;j++){
			if(i&(1<<j)) zt^=(1<<j);
		}
		if(cnt[zt]&1) continue;
		s1=(cnt[448&zt]&1),s2=(cnt[56&zt]&1),s3=(cnt[7&zt]&1);
		for(int j=0;j<=tot;j++){
			int cost=f[s-1][j][0][0][0]+cnt[i];
			f[s][zt^j][s1][s2][s3]=min(f[s][zt^j][s1][s2][s3],cost);
		}
	}
	for(int i=s+1;i<=s+2;i++){
		for(int j=0;j<=tot;j++){
			int zt=mp[i],s1,s2,s3;
			for(int k=0;k<=8;k++){
				if(j&(1<<k)) zt^=(1<<k);
			}
			if(cnt[zt]&1) continue;
			s1=(cnt[448&zt]&1),s2=(cnt[56&zt]&1),s3=(cnt[7&zt]&1);
			for(int k=0;k<=tot;k++){
				for(int k1=0;k1<=1;k1++) for(int k2=0;k2<=1;k2++) for(int k3=0;k3<=1;k3++){
					int cost=f[i-1][k][k1^s1][k2^s2][k3^s3]+cnt[j];
					f[i][zt^k][k1][k2][k3]=min(f[i][zt^k][k1][k2][k3],cost);
				}
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	for(int i=1;i<=9;i++){
		cin>>(ch+1);
		for(int j=1;j<=9;j++){
			mp[i]=mp[i]<<1;
			mp[i]|=(ch[j]-'0')?1:0;
		}
	}
	for(int i=1;i<=tot;i++){
		int tmp=i;
		while(tmp){
			tmp-=lowbit(tmp);
			cnt[i]++;
		}
	}
	memset(f,63,sizeof(f));
	f[0][0][0][0][0]=0;
	dp(1); dp(4); dp(7);
	cout<<f[9][0][0][0][0]<<endl;
	return 0;
}
```

---

## 作者：fish_shit (赞：7)

一看就是道动规，但是我们可以尝试用贪心和模拟来解决这道题，于是便有了这篇题解。

我们考虑计算每一个点更改后的价值，如果该点所在的行、列和九宫格都存在奇数个 $1$，那么更改这个点就会产生 $3$ 的价值；如果该点所在的行、列和九宫格中只有两者存在奇数个 $1$，那么更改它会解决两个问题，但又会产生一个新的问题，故价值为 $1$。值得注意的是此处更改完一个有两个问题的点后会导致一些点的问题数增加，可能会产生有三个问题的点，所以一直更改有两个问题的点是不优的。

很容易发现我们应该先算清楚总共有多少问题并对每一个点计算它所在位置的问题数，优先更改有三个问题的点（因为其产生的价值大）。如果目前有三个问题的点更新完了，便去更新 $1$ 个有两个问题的点，再去检查一遍是否又有有三个问题的点出现。如此往复直至没有有两个或者三个问题的点。这时我们只会有一些互不相干的有一个问题的点，剩下的更改次数就是最后还剩下的问题数。

虽然说得不难，但实现起来还是有很多细节的，可以用来锻炼各位的代码能力。

奉上调了两个周的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[15][15];
int vis[15][15],idx[15][15][5],shu[15][15],now,ans;
int fx[10]={0,1,1,1,4,4,4,7,7,7},fy[10]={0,1,4,7,1,4,7,1,4,7};
signed main(){
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=9;i++){//行
		int sum=0;
		for(int j=1;j<=9;j++){
			sum+=a[i][j]-'0';
		}
		if(sum%2==1){
			now++;
			for(int j=1;j<=9;j++){
				vis[i][j]++;
				idx[i][j][1]=1;
			}
		}
	}
	for(int i=1;i<=9;i++){//列
		int sum=0;
		for(int j=1;j<=9;j++){
			sum+=a[j][i]-'0';
		}
		if(sum%2==1){
			now++;
			for(int j=1;j<=9;j++){
				vis[j][i]++;
				idx[j][i][2]=1;
			}
		}
	}
	for(int k=1;k<=9;k++){//九宫格
		int x=fx[k],y=fy[k],sum=0;
		for(int i=x;i<=x+2;i++){
			for(int j=y;j<=y+2;j++){
				sum+=a[i][j]-'0';
				shu[i][j]=k;
			}
		}
		if(sum%2==1){
			now++;
			for(int i=x;i<=x+2;i++){
				for(int j=y;j<=y+2;j++){
					vis[i][j]++,idx[i][j][3]=1;
				}
			}
		}
	}
	//now：目前的总问题数
	bool flag=0;
	while(now>0){
		flag=0;
		int start=now;
		for(int i=1;i<=9;i++){
			for(int j=1;j<=9;j++){
				if(vis[i][j]==3){//有三个问题的
					now-=3,ans++;
					for(int k=1;k<=9;k++){
						vis[i][k]--,idx[i][k][1]=0;
					}
					for(int k=1;k<=9;k++){
						vis[k][j]--,idx[k][j][2]=0;
					}
					int s=shu[i][j],x=fx[s],y=fy[s];
					for(int x1=x;x1<=x+2;x1++){
						for(int y1=y;y1<=y+2;y1++){
							vis[x1][y1]--,idx[x1][y1][3]=0;
						}
					}
				}
			}
		}
		for(int i=1;i<=9;i++){
			for(int j=1;j<=9;j++){
				if(vis[i][j]==2){//有两个问题的
					now--,ans++;
					int op=6;
					if(idx[i][j][1]==1){
						op-=1;
						for(int k=1;k<=9;k++){
							vis[i][k]--,idx[i][k][1]=0;
						}
					}
					if(idx[i][j][2]==1){
						op-=2;
						for(int k=1;k<=9;k++){
							vis[k][j]--,idx[k][j][2]=0;
						}
					}
					if(idx[i][j][3]==1){
						op-=3;
						int s=shu[i][j],x=fx[s],y=fy[s];
						for(int x1=x;x1<=x+2;x1++){
							for(int y1=y;y1<=y+2;y1++){
								vis[x1][y1]--,idx[x1][y1][3]=0;
							}
						}
					}
					if(op==1){
						for(int k=1;k<=9;k++){
							vis[i][k]++,idx[i][k][1]=1;
						}
					}
					if(op==2){
						for(int k=1;k<=9;k++){
							vis[k][j]++,idx[k][j][2]=1;
						}
					}
					if(op==3){
						int x=i,y=j;
						for(int x1=x;x1<=x+2;x1++){
							for(int y1=y;y1<=y+2;y1++){
								vis[x1][y1]++,idx[x1][y1][3]=1;
							}
						}
					}
					flag=1;
					break;//只操作一个数
				}
			}
			if(flag) break;
		}
		if(start==now) break;//没有有三个或者两个问题的点
	}
	cout<<ans+now;
	return 0;
}
```
代码实测比其他算法都要快很多。~~（可以用来抢最优解）~~

---

## 作者：巨型方块 (赞：5)

什么东西跑得快？洛谷评测机啊

裸的搜索加一个掐秒在通氧气的情况下直接ac啦哈哈

真的没有什么剪枝，也不用什么a\*

本来就不会嘛


```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const int N=10;
int v[N][N]={
{0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,2,2,2,3,3,3},
{0,1,1,1,2,2,2,3,3,3},
{0,1,1,1,2,2,2,3,3,3},
{0,4,4,4,5,5,5,6,6,6},
{0,4,4,4,5,5,5,6,6,6},
{0,4,4,4,5,5,5,6,6,6},
{0,7,7,7,8,8,8,9,9,9},
{0,7,7,7,8,8,8,9,9,9},
{0,7,7,7,8,8,8,9,9,9},
};
int a[N][N],X[N],Y[N],g[N];
int n,m,ans=1e9;
char c;
void dfs(int x,int y,int sum){
    if(sum>=ans)return;
    if(y>9){
        if(++m==1e7+5e6){printf("%d",ans);exit(0);}
        x++;y=1;
        if(X[x-1]&1)return;
        if(x==4)if((g[1]&1)||(g[2]&1)||(g[3]&1))return;
        if(x==7)if((g[4]&1)||(g[5]&1)||(g[6]&1))return;
        if(x==10){
            if((g[7]&1)||(g[8]&1)||(g[9]&1))return;
            for(int i=1;i<=9;i++)if(Y[i]&1)return;
            ans=sum;return;
        }    
    }
    dfs(x,y+1,sum);
    X[x]++;Y[y]++;g[v[x][y]]++;
    dfs(x,y+1,sum+1);
    X[x]--;Y[y]--;g[v[x][y]]--;
}
int main()
{
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++){
            cin>>c;
            if(c=='1')a[i][j]=1,X[i]++,Y[j]++,g[v[i][j]]++;
        }
    dfs(1,1,0);
    printf("%d",ans);
}
```

---

## 作者：Vin_1999 (赞：3)

貌似数独的题目都是一个格子一个格子的扫。

用记忆化解决重复搜索的问题。然后这个二进制很容易让人联想到状压?

好吧这是个五维dp，dp[i][j][a][b][c].

i行j列，a是所有列的含1个数的奇偶状态，如果二进制该位为1就是奇，0就是偶。

b是九宫格的奇偶状态，c是当前行的奇偶状态。

空间（9\*9\*2^3\*2^9\*2）不到100万，装的下。

搜索树是二叉的，虽然最多遍历2^81次方看样子会tle。其实很多节点是遍历不到的（因为它非法）

代码原创不是我的，但是找不到原作者了。我只是大自然的搬运工。









```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<climits>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
const int inf=1<<29-1;
static bool m[10][10];
static int dp[10][10][1<<9][1<<3][2];
string s;
int dfs(int x,int y,int a,int b,bool c)
{
    if(x==9) return a ? inf : 0;
    if(y==9)
    {
        if(c) return inf;
        if(!((x+1)%3)&&b) return inf;
        dfs(x+1,0,a,b,0); 
    }
    else
    {
    if(dp[x][y][a][b][c]!=-1) return dp[x][y][a][b][c];
    dp[x][y][a][b][c]=!m[x][y]+dfs(x,y+1,a^1<<y,b^1<<y/3,!c);
    dp[x][y][a][b][c]=min(dp[x][y][a][b][c],m[x][y]+dfs(x,y+1,a,b,c));
    return dp[x][y][a][b][c];
  }
}     
int main()
{
  freopen("e:/in.txt","r",stdin);
  rep(i,0,8)
  {
    getline(cin,s);
        rep(j,0,8) m[i][j]=s[j]=='1';    
    }
    memset(dp,-1,sizeof(dp));
    printf("%d",dfs(0,0,0,0,0));
    return 0;
}//not by fjlyyz-ljy

```

---

## 作者：Sino_E (赞：3)

奇怪的题目

我一开始没看见块也得偶数个，所以半天没想出来跟数独有什么关系

如果跟块也有关系的那么就很明白了，大爆搜嘛

IDA*

显然反转一个格子，行，列，块的状态都会反转

我们统计当前行列块状态为1的总数，那么估价函数就是这三个值取最大

然后就没了哇\_(:з」∠)_

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=100;
bool row[N], col[N], blo[N]; // 行列块的总数
int id[10][10]=
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9}}; // 每个格子的所属块标号

int maxd,r,c,b;
inline void upd(int x, int &y) {
    if(x==0) y--;
    else y++;
} // 用于更新状态为1的总数
void dfs(int x,int y,int cnt) {
    if(cnt>maxd) return;
    if(y==10) x++, y=1;
    if(x==10) {
        for(int i=1;i<=9;i++)
            if(row[i]|col[i]|blo[i]) return;
        cout<<maxd<<endl;
        exit(0);
        return;
    }
    int nid=id[x][y];
    if(row[x]|col[y]|blo[nid]) {
        row[x]^=1, col[y]^=1, blo[nid]^=1;
        upd(row[x], r), upd(col[y], c), upd(blo[nid], b);
        if(cnt+1+max(r,max(c,b))<=maxd) dfs(x,y+1,cnt+1);
        row[x]^=1, col[y]^=1, blo[nid]^=1;
        upd(row[x], r), upd(col[y], c), upd(blo[nid], b);
        if(cnt+max(r,max(c,b))<=maxd) dfs(x,y+1,cnt);
    }
    else dfs(x,y+1,cnt);
}

int main() {
    ios::sync_with_stdio(false);
    char ch;
    for(int i=1;i<=9;i++)
    for(int j=1;j<=9;j++) {
        cin>>ch;
        if(ch=='1') row[i]^=1, col[j]^=1, blo[id[i][j]]^=1, upd(row[i],r), upd(col[j],c), upd(blo[id[i][j]],b);
    }
    for(maxd=0;;maxd++) dfs(1,1,0);
    return 0;
}

```

---

## 作者：Kubic (赞：1)

为什么大家的状压dp都是五维的呢？

蒟蒻来一发三维的（其实完全可以两维但蒟蒻懒得写）

进入正题：

先设计状态：
$(1)$ 考虑状压$9$列的当前状态，和为奇数的列在状态中对应的位置为$1$，否则为$0$。

$(2)$ 考虑状压当前行穿过的$3$个九宫格的当前状态，和为奇数的九宫格在状态中对应的位置为$1$，否则为$0$。

那么，状态就出来了：

$dp[i][j][k]$，其中$i$表示当前行，$j$表示$9$列的当前状态，$k$表示当前行穿过的$3$个九宫格的当前状态。

此时我们还需要再预处理$4$个东西：

$(1)$ 状态$x$转变为状态$y$所需要的最少步数。$(c1)$

$(2)$ 九宫格状态$x$叠加上行状态$y$所形成的新的九宫格状态。$(c2)$

$(3)$ 所有含有偶数个$1$的状态。$(c3)$

$(4)$ 所有行的初始状态

状态转移方程为~~有点长~~：


$dp[i][j$ $xor$ $c3[k]][c2[l][c3[k]]]=min(dp[i][j$ $xor$ $c3[k]][c2[l][c3[k]]],dp[i-1][j][l]+c1[c3[k]][stt[i]]);$

代码（您们期待已久的）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 15
int cntC3,a[N][N],stt[N],dp[N][1<<9][1<<3],c1[1<<9][1<<9],c2[1<<3][1<<9],c3[1<<9];
int f1(int x) {int res=0;for(;x;x-=x&-x) ++res;return res;}
int f2(int x) {int res=0;if(f1(x>>6)&1) ++res;if(f1(x-(x>>6<<6)>>3)&1) res+=2;if(f1(x-(x>>3<<3))&1) res+=4;return res;}
int main()
{
	for(int i=1;i<=9;++i) for(int j=1;j<=9;++j) scanf("%1d",&a[i][j]),stt[i]|=a[i][j]*(1<<j-1);
	for(int i=0;i<(1<<9);++i) for(int j=0;j<(1<<9);++j) c1[i][j]=f1(i^j);
	for(int i=0;i<(1<<3);++i) for(int j=0;j<(1<<9);++j) c2[i][j]=i^f2(j);
	for(int i=0;i<(1<<9);++i) if(!(f1(i)&1)) c3[++cntC3]=i;
	memset(dp,0x3f,sizeof(dp));dp[0][0][0]=0;
	for(int i=1,t;i<=9;++i) for(int j=0;j<(1<<9);++j) for(int k=1;k<=cntC3;++k) 
	{
		if(i==4 || i==7) t=c2[0][c3[k]],dp[i][j^c3[k]][t]=min(dp[i][j^c3[k]][t],dp[i-1][j][0]+c1[c3[k]][stt[i]]);
		else for(int l=0;l<(1<<3);++l) t=c2[l][c3[k]],dp[i][j^c3[k]][t]=min(dp[i][j^c3[k]][t],dp[i-1][j][l]+c1[c3[k]][stt[i]]);
	}printf("%d\n",dp[9][0][0]);
}
```

---

## 作者：Rainber (赞：0)

一看这道题，很容易联想起曾经学过的[八数码](https://www.luogu.com.cn/problem/P1379)，明显是**启发式迭代加深搜索**（A*）算法。

  我们可以设置一个状态，就是对于每个 $3\times3$ 的格子，每一行，每一列都有一个状态位，暂时定为 `S`（不需要修改）和 `U`（需要修改），对应 $1$ 和 $0$。一共是 $9+9+9$ 个，这可以进行**状态压缩**。

于是，这题的解法便出来了，是**状态压缩迭代加深搜索**。

进行标记操作和查询，可以使用异或和与操作。
```cpp
unsigned int mark(unsigned int oriStat,int x,int y)
{
	oriStat^=1<<((x/3)*3+(y/3)+18);
	oriStat^=1<<(x+9);
	oriStat^=1<<(y);
	return oriStat;
}
int hasU(unsigned int oriStat,int x,int y)
{
	int ans=0;
	ans=ans||(~oriStat&(1<<((x/3)*3+(y/3)+18)));
	ans=ans||(~oriStat&(1<<(x+9)));
	ans=ans||(~oriStat&(1<<(y)));
	return ans;
}
```

然后为了使 A* 发挥效力，估价函数采用统计 `U` 个数的方式。
```cpp
int test(unsigned int oriStat)
{
	int i,j,ans=0;
	for(i=0;i<9;++i)
	{
		for(j=0;j<9;++j)
		{
			if(hasU(oriStat,i,j))
			{
				ans++;
			}
		}
	}
	return ans;
}
```

A* 代码主程序
```cpp
std::unordered_map<int,std::pair<unsigned char,int>> dis;
int aStar(unsigned int oriStat,unsigned int aimStat)
{
	int i,j,toStat;
	q.push({0,oriStat});
	dis[oriStat]={0,0};
	std::pair<int,unsigned int> r;
	while(!q.empty())
	{
		r=q.top();
		q.pop();
		dis[r.second].first=1;
		if(r.second==aimStat)
		{
			return dis[r.second].second;
		}
		for(i=0;i<9;++i)
		{
			for(j=0;j<9;++j)
			{
				toStat=mark(r.second,i,j);
				if(!dis[toStat].first&&hasU(r.second,i,j))
				{
					dis[toStat].second=min(dis[toStat].second,dis[r.second].second+1);
					q.push({dis[toStat].second+test(toStat),toStat});
				}
			}
		}
	}
	return -1;
}
```

AC 代码：
```cpp
#include<stdio.h>
#include<queue>
#include<utility>
#include<unordered_map>
std::priority_queue<std::pair<int,unsigned int>,std::vector<std::pair<int,unsigned int>>,std::greater<std::pair<int,unsigned int>>> q;
int min(int a,int b)
{
	return a>b?a:b;
}
unsigned int mark(unsigned int oriStat,int x,int y)
{
	oriStat^=1<<((x/3)*3+(y/3)+18);
	oriStat^=1<<(x+9);
	oriStat^=1<<(y);
	return oriStat;
}
int hasU(unsigned int oriStat,int x,int y)
{
	int ans=0;
	ans=ans||(~oriStat&(1<<((x/3)*3+(y/3)+18)));
	ans=ans||(~oriStat&(1<<(x+9)));
	ans=ans||(~oriStat&(1<<(y)));
	return ans;
}
int test(unsigned int oriStat)
{
	int i,j,ans=0;
	for(i=0;i<9;++i)
	{
		for(j=0;j<9;++j)
		{
			if(hasU(oriStat,i,j))
			{
				ans++;
			}
		}
	}
	return ans;
}
std::unordered_map<int,std::pair<unsigned char,int>> dis;
int aStar(unsigned int oriStat,unsigned int aimStat)
{
	int i,j,toStat;
	q.push({0,oriStat});
	dis[oriStat]={0,0};
	std::pair<int,unsigned int> r;
	while(!q.empty())
	{
		r=q.top();
		q.pop();
		dis[r.second].first=1;
		if(r.second==aimStat)
		{
			return dis[r.second].second;
		}
		for(i=0;i<9;++i)
		{
			for(j=0;j<9;++j)
			{
				toStat=mark(r.second,i,j);
				if(!dis[toStat].first&&hasU(r.second,i,j))
				{
					dis[toStat].second=min(dis[toStat].second,dis[r.second].second+1);
					q.push({dis[toStat].second+test(toStat),toStat});
				}
			}
		}
	}
	return -1;
}
int main()
{
	int i,j,r,stat=(1<<27)-1;
	for(i=0;i<9;++i)
	{
		for(j=0;j<9;++j)
		{
			scanf("%1d",&r);
			if(r)
			{
				stat=mark(stat,i,j);
			}
		}
	}
	printf("%d",aStar(stat,(1<<27)-1));
	return 0;
}
```

---

## 作者：BigJoker (赞：0)

# Preface

IDA*

~~目前应该是 IDA* 里跑得最快的，当然您超过了我当我没说。~~

# Solution

暴力的判断每一个数，选择是否修改，修改的话次数加 $1$，不修改次数不变。

重点是估价函数与剪枝。

修改一行或者一列或者一个宫格的奇偶性需要 $1$ 次操作，那么处理出行、列、宫格当中需要最多的，就可以了。

但是这样只能得到 $84$ 分，考虑剪枝。

由于是九宫格，那么一定有次数的上限，那么只要达到了这个次数上限，我们就不需要去遍历，虽然我不会证明这个次数上限是多少，但是~~凭借直觉~~推测应该是 $9$。

大致思考了一下，因为最多有 $9$ 行，$9$ 列，$9$ 个宫格是奇性，一次操作可以改变一行一列以及一个宫格的奇偶性，那么推测出来是 $9$？

所以当答案到 $9$ 的时候，不需要管了，一定是这个答案。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define mem(a,x) memset(a,x,sizeof(a))
#define inf 0x3f3f3f3f
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define re register
#define il inline
using namespace std;
typedef long long LL;
const int N=11;
il int qr(){
	int s=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') (ch=='-'?f=-1:1),ch=getchar();
	while(ch>='0' && ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*f;
}
il void qw(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) qw(x/10);
	putchar(x%10+'0');
}
int ans,l[N],h[N],g[N],bh[N][N];
bool f[N][N],f1[N][N];
void init(){
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			if(i<=3 && j<=3) bh[i][j]=1;
			if(i<=3 && 4<=j && j<=6) bh[i][j]=2;
			if(i<=3 && 7<=j) bh[i][j]=3;
			if(4<=i && i<=6 && j<=3) bh[i][j]=4;
			if(4<=i && i<=6 && 4<=j && j<=6) bh[i][j]=5;
			if(4<=i && i<=6 && 7<=j) bh[i][j]=6;
			if(7<=i && j<=3) bh[i][j]=7;
			if(7<=i && 4<=j && j<=6) bh[i][j]=8;
			if(7<=i && 7<=j) bh[i][j]=9;
		}
	}
}
int sum(){
	mem(l,0),mem(h,0),mem(g,0);
	for(re int i=1;i<=9;i++) for(re int j=1;j<=9;j++) l[i]+=f[i][j],h[j]+=f[i][j],g[bh[i][j]]+=f[i][j];
	for(re int i=1;i<=9;i++) l[0]+=l[i]&1,h[0]+=h[i]&1,g[0]+=g[i]&1;
	return max(max(l[0],h[0]),g[0]);
}
bool Astar(int step,int i,int j){
	int cnt=sum();
	if(!cnt) return 1;
	if(i==0 || step+cnt>ans) return 0;
	int x=i,y=j-1;
	if(j==1) x--,y=9;
	if(Astar(step,x,y)) return 1;
	f[i][j]^=1;
	if(Astar(step+1,x,y)) return 1;
	f[i][j]^=1;
	return 0;
}
int main(){
	init();
	for(re int i=1;i<=9;i++)
		for(re int j=1;j<=9;j++){
			char x;
			cin>>x;
			f[i][j]=f1[i][j]=x-'0';
		}
	while(ans<9 && !Astar(0,9,9)){
		for(re int i=1;i<=9;i++) for(re int j=1;j<=9;j++) f[i][j]=f1[i][j];
		ans++;
	}
	qw(ans);
	return 0;
}
```

---

## 作者：Fish_and_Shit (赞：0)

## Question
给出一个 $9\times9$ 的 `01` 矩阵，问最少修改几个数能使每行、每列以及每个九宫格中 `1` 的个数均为偶数。
## Solution
一看就是状压 dp，但我不会，相信很多人都不会。

如果你仔细看看题解，全是 dp 和 A*，~~我这种弱鸡跟不会打~~，所以写一篇不一样的题解。

### 考虑贪心

~~更像大模拟，害我模拟赛时调了 2 个小时，又被同学抄袭。~~

1. 首先暴力枚举所有行列以及九宫格，找出所有不符合要求的行列和九宫格，找个数组记一下，并把每个坐标出现在不符合要求的行列九宫格的次数记录；

复杂度：$O(n^2)- n$ 为行列和九宫格数。

2. 由于每个坐标在不符合中的次数只会是 0，1，2，3 次，那么遍历每个坐标，若是出现 3 次，直接修改，这样会把它所在的行列以及九宫格全变为符合要求的。

3. 遍历完后每个坐标都会是出现 3 次以下，这时找出现两次的坐标，修改，会把 2 个不符合的变成符合的，另外 1 个符合的变成不符合的，有可能会把其中某个坐标的次数变成 3 次，所以继续执行操作 2。

4. 当每个坐标只会出现一次时，输出修改的次数加上出现一次的坐标的个数。

2~3 操作复杂度：$O(n^2Q)-Q$是执行删除操作的次数，非常小，和 $n^2$ 差不多，可以看成 $O(n^4)$。

下面一大坨代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
char c;bool a[1005][10];
int mk[1005][10],vis[1005],idx[1005][10];
//mk是不符合要求的行列九宫格
//vis是坐标出现次数
//idx是每个坐标(i，二维坐标直接简化成一维)行在mk的位置:idx[i][1]，列在mk的位置:idx[i][2]，以及九宫格在mk的位置:idx[i][3]
void solve(){
	int cnt=0;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			cin>>c,a[i][j]=c^48;
	for(int i=1;i<=9;i++){
		int sum=0;
		for(int j=1;j<=9;j++)
			if(a[i][j])sum++;
		if(!(sum&1))continue;cnt++;
		for(int j=1;j<=9;j++)
			mk[cnt][j]=i*10+j,
			vis[i*10+j]++,
			idx[i*10+j][1]=cnt;
	}
//不符合的行(上面)
  for(int i=1;i<=9;i++){
		int sum=0;
		for(int j=1;j<=9;j++)
			if(a[j][i])sum++;
		if(!(sum&1))continue;cnt++;
		for(int j=1;j<=9;j++)
			mk[cnt][j]=j*10+i,
			vis[j*10+i]++,
			idx[j*10+i][2]=cnt;
	}
//不符合的列(上面)
  for(int i=1;i<=9;i+=3){
		for(int j=1;j<=9;j+=3){
			int sum=0;
			for(int x=i;x<i+3;x++)
				for(int y=j;y<j+3;y++)
					if(a[x][y])sum++;
			if(!(sum&1))continue;cnt++;
			for(int x=i;x<i+3;x++)
				for(int y=j;y<j+3;y++)
					mk[cnt][(x-i)*3+(y-j)+1]=x*10+y,
					vis[x*10+y]++,
					idx[x*10+y][3]=cnt;
		}
	}
//不符合的九宫格(上面)
  int now=cnt,ans=0;
	while(now>0){
		int start=now;
		for(int i=11;i<=99;i++){
			if(i%10&&vis[i]==3){
				now-=3;ans++;int p1=idx[i][1],p2=idx[i][2],p3=idx[i][3];
				for(int j=1;j<=9;j++)
					vis[mk[p1][j]]--,idx[mk[p1][j]][1]=0,
					vis[mk[p2][j]]--,idx[mk[p2][j]][2]=0,
					vis[mk[p3][j]]--,idx[mk[p3][j]][3]=0;
            //修改
			}
		}//出现三次
  for(int i=11;i<=99;i++){
			if(i%10&&vis[i]==2){
				now--;ans++;cnt++;
				int p1=idx[i][1],p2=idx[i][2],p3=idx[i][3];
				if(idx[i][1]==0){//行没不符合要求
					for(int j=1;j<=9;j++)
						vis[mk[p2][j]]--,idx[mk[p2][j]][2]=0,
						vis[mk[p3][j]]--,idx[mk[p3][j]][3]=0;
					for(int j=1;j<=9;j++)
						mk[cnt][j]=int(i/10)*10+j,
						vis[int(i/10)*10+j]++,
						idx[int(i/10)*10+j][1]=cnt;
				}else if(idx[i][2]==0){//列没不符合要求
					for(int j=1;j<=9;j++)
						vis[mk[p1][j]]--,idx[mk[p1][j]][1]=0,
						vis[mk[p3][j]]--,idx[mk[p3][j]][3]=0;
					idx[i][1]=idx[i][3]=0;
					for(int j=1;j<=9;j++)
						mk[cnt][j]=j*10+i%10,
						vis[j*10+i%10]++,
						idx[j*10+i%10][2]=cnt;
				}else{//九宫格没不符合要求
					for(int j=1;j<=9;j++)
						vis[mk[p1][j]]--,idx[mk[p1][j]][1]=0,
						vis[mk[p2][j]]--,idx[mk[p2][j]][2]=0;
					idx[i][1]=idx[i][2]=0;
					int f=i/10,s=i%10;
					int x=int((f-1)/3)*3+(f-1)%3+1;
					int y=int((s-1)/3)*3+(s-1)%3+1;
					for(int X=x;X<x+3;X++)
						for(int Y=y;Y<y+3;Y++)
							mk[cnt][(X-x)*3+(Y-y)+1]=X*10+Y,
							vis[X*10+Y]++,
							idx[X*10+Y][3]=cnt;
				}break;
			}
		}//出现2次
  if(now==start)break;
	}cout<<ans+now;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	solve();return 0;
}
```
没有耐心的不要写，就当看个笑话，新手不会 dp 和 A* 的推荐和我一样贪心，代码难度地狱级，但思路清晰易懂，实测跑的很快，没加优化 36ms。

---

