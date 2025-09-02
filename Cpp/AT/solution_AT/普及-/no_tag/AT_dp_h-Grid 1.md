# Grid 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_h

縦 $ H $ 行、横 $ W $ 列のグリッドがあります。 上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ で表します。

各 $ i,\ j $ ($ 1\ \leq\ i\ \leq\ H $, $ 1\ \leq\ j\ \leq\ W $) について、マス $ (i,\ j) $ の情報が文字 $ a_{i,\ j} $ によって与えられます。 $ a_{i,\ j} $ が `.` ならばマス $ (i,\ j) $ は空マスであり、$ a_{i,\ j} $ が `#` ならばマス $ (i,\ j) $ は壁のマスです。 マス $ (1,\ 1) $ および $ (H,\ W) $ は空マスであることが保証されています。

太郎君は、マス $ (1,\ 1) $ から出発し、右または下に隣り合う空マスへの移動を繰り返すことで、マス $ (H,\ W) $ まで辿り着こうとしています。

マス $ (1,\ 1) $ から $ (H,\ W) $ までの太郎君の経路は何通りでしょうか？ 答えは非常に大きくなりうるので、$ 10^9\ +\ 7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ H $ および $ W $ は整数である。
- $ 2\ \leq\ H,\ W\ \leq\ 1000 $
- $ a_{i,\ j} $ は `.` または `#` である。
- マス $ (1,\ 1) $ および $ (H,\ W) $ は空マスである。

### Sample Explanation 1

経路は次図の $ 3 $ 通りです。 !\[\](https://img.atcoder.jp/dp/grid\_0\_0\_muffet.png)

### Sample Explanation 2

経路が存在しない場合もあります。

### Sample Explanation 4

答えを $ 10^9\ +\ 7 $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
3 4
...#
.#..
....```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2
..
#.
..
.#
..```

### 输出

```
0```

## 样例 #3

### 输入

```
5 5
..#..
.....
#...#
.....
..#..```

### 输出

```
24```

## 样例 #4

### 输入

```
20 20
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................```

### 输出

```
345263555```

# 题解

## 作者：_ZhouYuHan_ (赞：5)

这道题是一道DP的入门题，类似于 [P1002](https://www.luogu.com.cn/problem/P1002) ，可以模拟标数法，如图（样例一）：

![](https://cdn.luogu.com.cn/upload/image_hosting/y9ozzm7l.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么，我们是如何得到这个图的？

很明显，走到一个点，只能从它上面或左边走来。

综上所述，我们可以得到公式：

$ a(i,j)=(a(i-1,j)+a(i,j-1)) $

根据此公式，我们可以写出核心代码：
```cpp
for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(ch[i][j]=='.')
				a[i][j]=(a[i-1][j]+a[i][j-1])%1000000007;
```
最后加上一头一尾即可。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001][1001];
int n,m;
char ch[1001][1001];
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		scanf("%s",ch[i]+1);
	a[0][1]=1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(ch[i][j]=='.')
				a[i][j]=(a[i-1][j]+a[i][j-1])%1000000007;
	cout<<a[n][m]<<endl;
	return 0;
}
```

---

## 作者：Haphyxlos (赞：4)

# AT4529 Grid 1
[题目传送门](https://www.luogu.com.cn/problem/AT4529)

很显然，本题是一道矩阵dp的入门题。

转移方程：$ f[i][j]=(f[i-1][j]+f[i][j-1]) \% (10^{9}+7 )$

此题值得注意的是：若此时$a[i][j]=\#$，则不计数，且$a[1][1]$位置需初始化为1。

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
int n,m,f[1005][1005];
char c[1005][1005];
int main(int argc,char const *argv[]){
	std::ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>c[i]+1;
	f[1][1]=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
		    if(i==1&&j==1)continue;
			if(c[i][j]=='.')f[i][j]=(f[i-1][j]+f[i][j-1])%mod;
		}
	} 
	cout<<f[n][m]<<endl;
	return 0;
}
```

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：WHJ___ (赞：1)

简单递推题。

我们先举个例子：$H=3,W=3$，没有障碍，则过程如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/q2h0v451.png)

其实根据题目，我们只能向**下**和向**右**走，即不能走回头路，那么到达一个点至多只有两种情况：来自上方点和来自左边点。

因此我们可以得出递推式：$dp[i][j]=dp[i-1][j]+dp[i][j-1]$

当然，到达起点的路线数显然是 $1$，到达地图以外的点的路线数是 $0$。有障碍的地方显然**不可达**，所以路线数也是 $0$。

代码：

```cpp
#include<bits/stdc++.h>
#define I long long
#define RI register int
#define il inline
#define zzh 1000000007
#define rt return
using namespace std;
const int N=1e3+7;

I H,W,dp[N][N];
char mapp[N][N];

il I d(){
	I xt=0,fh=1;
	char cha=0;
	while(!isdigit(cha=getchar()))fh-=(cha=='-')*2;
	while(isdigit(cha)){xt=(xt<<1)+(xt<<3)+fh*(cha-48);cha=getchar();}
	rt xt;
}

signed main()
{
	RI i,j;
	H=d();W=d();
	for(i=1;i<=H;++i)
		for(j=1;j<=W;++j)
			cin>>mapp[i][j];
	dp[1][1]=1;//到达起点有1种方法（显然） 
	for(i=1;i<=H;++i){
		for(j=1;j<=W;++j){
			if(i==1&&j==1) continue;//如果是起点就跳过（不然的话dp[1][1]会变成0） 
			dp[i][j]=mapp[i][j]=='#'?0:(dp[i-1][j]+dp[i][j-1])%zzh;//递推 
		}
	}
	cout<<dp[H][W];
	rt 0;
}

```


---

## 作者：Cambridge (赞：1)


蒟蒻又来发题解了！

来讲讲思路。其实这道题就是一道非常简单的DP题，若当前处于一个格子中，会有两种情况，分别解决方法如下：

1、处于```.```中，那么当前方案数```f[i][j]```为```f[i-1][j]+f[i][j-1]```的和。

2、处于```#```中，只需将```f[i][j]```值赋值为0即可。

知道了思路，是否想自己去尝试一下？--->[传送门](https://www.luogu.com.cn/problem/AT4529)

代码如下~~请勿抄袭~~：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n,m,f[1010][1010];
string st;
char a[1010][1010];//定义变量
int main()
{
	cin>>n>>m;
	f[1][1]=1;
	for(int i=1; i<=n; i++)
	{
		cin>>st;
		for(int j=1; j<=m; j++)
			a[i][j]=st[j-1];//转换
	}
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(a[i][j]!='#')f[i][j]+=(f[i-1][j]+f[i][j-1])%1000000007,f[i][j]%=1000000007;//第一种情况
			else f[i][j]=0;//第二种情况
		}
	}
	cout<<f[n][m]%1000000007<<endl;//输出结果，记得换行
	return 0;
}

```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：_huangyicheng_ (赞：1)

暴力dfs代码：

```cpp
#include<iostream>
using namespace std;
const int mod=1e9+7;
int n,m,dir[3][2]={{0},{0,1},{1,0}},cnt;
char map[1005][1005];
bool vis[1005][1005];
void dfs(int x,int y){
	vis[x][y]=true;
	if(x==n&&y==m){
		cnt++;
		cnt%=mod;
		return ;
	}
	for(int i=1;i<=2;i++){
		int dx=x+dir[i][0],dy=y+dir[i][1];
		if(dx>=1&&dy>=1&&dx<=n&&dy<=m && !vis[dx][dy] &&map[dx][dy]!='#'){
			dfs(dx,dy);
			vis[dx][dy]=false;
		}
	}
	return ;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>map[i][j];
	}
	dfs(1,1);
	cout<<cnt;
	return 0;
}
```
但题目数据达到1000， $TLE$ 妥妥的。

蒟蒻不会dp，就用起了小学奥数标数法qwq

![](https://cdn.luogu.com.cn/upload/image_hosting/uq9ku0tx.png)

图很丑，见谅qwq

这个图要求的问题：起点是左下角，终点时右上角，求从起点到终点的方案数。

最后答案显然是70。

方法：起点的方案数一定为1，第一行或者第一列的方案数都为1。因为每一步只能向右或向上走，所以每一个点的方案数为左下角的方案数加上下面的方案数。

得出结论： 

$a[1][1]=1$ 

$a[i][j]=a[i-1][j]+a[i][j-1]$ 

最后输出的是 $a[n][m]$ 。

但这道题要稍微难一点，有可能走不了，如果走不了那方案数一定是0。

然后就so easy了。

附上AC代码：

```cpp
#include<iostream>
using namespace std;
const int mod=1e9+7;//要取模的数 
int n,m,a[1005][1005];
char c[1005][1005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>c[i][j];
	}
	a[1][1]=1;//起点的方案数为1 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i==1&&j==1) continue;//起点已经设过了，直接跳过 
			if(c[i][j]=='.'){//如果能走 
				a[i][j]=(a[i-1][j]+a[i][j-1])%mod;//每一次算都模一下 
			}
		}
	}
	cout<<a[n][m];
	return 0;
}
```

---

## 作者：Gloaming (赞：0)

## 分析

我们看到这道题，很容易想到一个广为人知的算法`DFS`！！

但是我们悄悄看一眼数据范围，脑子里思考一下，会超时

那我们怎么办呢?

我们来看一看到达一个格子的方案是从哪里来的?

发现一个格子的到达的方案总数是它**上面的格子的方案总数**加上**左边的格子的方案总数**

这不就是一个动态规划的简单题吗?

我们定义$dp_{i,j}$表示坐标为$(i,j)$的格子的到达的方案总数。

于是我们就得到了一个转移公式$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}$。

但值得注意的是，我们的地图中有一些格子是无法到达的，这是要将这个格子的$dp$值赋为$0$，这样就不会对之后的操作有影响了。

最后注意$dp_{1,1}$要赋为$1$，一开始就在$(1,1)$处，算作一种方案

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;
int h, w, dp[1005][1005];
char c[1005][1005];
int main()
{
    cin >> h >> w;
    for(int i = 1; i <= h; i ++)
    {
        for(int j = 1; j <= w; j ++)
        {
            cin >> c[i][j];
        }
    }
    dp[1][1] = 1;//初始值
    for(int i = 1; i <= h; i ++)
    {
        for(int j = 1; j <= w; j ++)
        {
            if(c[i][j] == '#' || (i == 1 && j == 1)) continue;//特殊处理，在上文中有提到。
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % (1000000007);//状态转移(记得取模!!)
        }
    }
    cout << dp[h][w] << endl;//输出
    return 0;
}
```

---

## 作者：Doqin07 (赞：0)

#### 很显然本题是一道dpの大水题
##### 我们考虑$dp[i][j]$表示当前到$i$行$j$列有多少种可行的路径，因为只能往右或者往下走，所以我们只需考虑$dp[i-1][j]$&$dp[i][j-1]$，每次加上即可。
##### 注意需对答案取模。
------------
#### AC代码如下：
```cpp 
#include <bits/stdc++.h>
using namespace std;
namespace I_love{
    typedef long long ll;
    #define F(i,l,r) for (int i=l;i<=r;++i)
    #define REP(i,r,l) for (int i=r;i>=l;--i)
    #define mem(a,b) memset(a,b,sizeof(a));
    #define MP make_pair
    #define PB push_back
    #define readI(x) x=RI();
    #define readInm(x,y) readI(x);readI(y);
    #define readIxyz(x,y,z) readInm(x,y);readI(z);
    #define readIa(n,a) F(i,1,n)readI(a[i]);
    #define readIA(n,m,a) F(i,1,n)F(j,1,m)readI(a[i][j]);
    #define readL(x) x=RL();
    #define readLnm(x,y) readL(x);readL(y);
    #define readLxyz(x,y,z) readLnm(x,y);readL(z);
    #define readLa(n,a) F(i,1,n)readL(a[i]);
    #define readLA(n,m,a) F(i,1,n)F(j,1,m)readL(a[i][j]);
    const int maxn=1e5+5;
    const int N=1e3+5;
    const int maxm=1e6+5;
    const int INF=INT_MAX;
    const int mod=1e9+7;
    int RI(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
    ll RL(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
    int n,m,dp[N][N];char a[N][N];
    
    // 上为宏定义 
    
    void input(){
        readInm(n,m);
        F(i,1,n)F(j,1,m)cin>>a[i][j];
    }
    void run(){
        dp[1][1]=1;
        F(i,1,n){
            F(j,1,m){
                if(i==1&&j==1)continue;
                if(a[i][j]=='.'){
                    dp[i][j]=(dp[i-1][j]%mod+dp[i][j-1]%mod)%mod;
                }
            }
        }
        printf("%d\n",dp[n][m]);
    }
    void OI_Akame(){
        input();
        run();
    }
}
int main(){
#ifdef LOCAL
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif
    I_love::OI_Akame();
    return 0;
}
```


---

## 作者：happybob (赞：0)

  _Update：2021.1.4   $\, \, \, \, \, \large \LaTeX$    	 炸了_

~~本题明显可以用 `DFS`，并且不会 `TLE`。~~

但会 $\color{purple} \text{RE}$。

附上 `DFS` 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string a[1005];
int H, W;
const int Mod = 1e9 + 7;
long long cnt = 0;

void dfs(const int& x, const int& y, long long cnts = 0)
{
    if(a[x][y] == '#' || !(x >= 1 && x <= H && y >= 1 && y <= W)) return ;
    dfs(x, y + 1);
    dfs(x + 1, y);
    cnts++;
    if(x == H && y == W) cnt += cnts;
    cnt %= Mod;
}

int main()
{
    int m = 1, n = 1;
    cin >> H >> W;
    for(register int i = 1; i <= H; i++)
    {
        for(register int j = 1; j <= W; j++) cin >> a[i][j];
    }
    dfs(m, n);
    cout << cnt % Mod << endl;
    return 0;
}
```

递归多次导致栈溢出，$\color{purple} \text{RE}$。

这种题目我们更可以用 `DP` 做。

先给个转移方程：

$\large {dp_{i}}_{j} = 
\begin{cases} 
({dp_i}_{j-1}+{dp_{i-1}}_j) \mod(10^9+7) & {a_i}_j \not = \# \\
0 \,\,\,\,\,\,\, {a_i}_j = \# \\
1 \,\,\,\,\,\,\, \{i = 1, \,\, j = 1\}
\end{cases}$

那么这个转移方程怎么推出来的呢？

因为是往下或往右，所以对于每个 $\large dp_{i_j}$，往下是 $\large {dp_{i-1}}_{j}$，也就是列标不变，而往右是 $\large {dp_i}_j$，行标不变，而我们是逆着推，就是从上面来或从左侧来，因此分别是 $\large {dp_{i-1}}_j$ 和 $\large {dp_i}_{j-1}$。

时间复杂度 $\large O(HW)$。

代码：

```cpp
#include <iostream>
using namespace std;

char a[1005][1005];
long long dp[1005][1005];
int H, W;
const int Mod = 1e9 + 7;
long long cnt = 0;

int main()
{
    cin >> H >> W;
    for(register int i = 1; i <= H; i++)
    {
        for(register int j = 1; j <= W; j++) cin >> a[i][j];
    }
    dp[1][1] = 1;
    for(register int i = 1; i <= H; i++)
    {
        for(register int j = 1; j <= W; j++)
        {
            if(a[i][j] == '.')
            {
                dp[i][j] += dp[i][j - 1];
                dp[i][j] += dp[i - 1][j];
                dp[i][j] %= Mod;
            }
        }
    }
    cout << dp[H][W] << endl;
    return 0;
}
``` 
要注意的是本题不能用 `string` 做，无论是 `DP` 还是 `DFS`，都会 $\color{purple} \text{RE}$，猜测是由于 `string` 内存溢出吧$。


---

## 作者：aloomurphy (赞：0)

$\bullet\ $一道非常简单的dp

## 分析：

首先，因为每一步都只能向下、向右走，所以$(i,j)$只能由$(i-1,j)$ 和 $(i,j-1)$走到

我们用$dp[i][j]$ 表示到第$i$行，第$j$列的走法的数量

那么我们可以易得状态转移方程：

$$dp[i][j]=dp[i-1][j]+dp[i][j-1]$$

因为题目说'#'不能走，所以这时的转移方程为

时间复杂度$O(H\cdot W)$，$2\leq H,W\leq 1000$ ~~所以轻轻松松水掉此题~~

## 代码：
$\bullet$ 附上AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define N 1009

int h,w,dp[N][N];
char s[N][N];

int main(){
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;i++)
		scanf("%s",s[i]+1);
	dp[0][1]=1;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			if(s[i][j]=='.')
				dp[i][j]=(dp[i-1][j]+dp[i][j-1])%MOD;
	printf("%d",dp[h][w]);
	return 0;
}

```


---

## 作者：小豆子范德萨 (赞：0)

解题思路
- dfs做法：
暴力搜索就完事了，类似我们求连通块的模板

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
const int INF = 1e9+7;
char a[maxn][maxn];
bool vis[maxn][maxn];
long long ans = 0,h,w;

bool inside(int i,int j) {
	if(i <= 0 || i > h || j <= 0 || j > w) return false;
	return true;
}

void dfs(int i,int j) {
	if(i == h && j == w) {
		ans = (ans + 1) % (INF);
		return;
	}
	if(inside(i+1,j) && a[i+1][j] != '#') 
 		dfs(i+1,j);
	if(inside(i,j+1) && a[i][j+1] != '#') 
		dfs(i,j+1);
}

int main() {
	cin>>h>>w;
	for(int i = 1;i <= h;i++) {
		scanf("%s",a[i]+1);
	}
	dfs(1,1);
	cout<<ans;
	return 0;
} 

```
RE了，很明显搜索行不通，换dp

- dp

本题是二维矩阵下的方案dp

dp数组:dp[i][j]代表从起点1,1到i,j位置的方案数,

dp边界：dp[1][1] = 1（记住方案dp，一般不动也是一个方案）,因为从（1,1）位置只能向右走或者向下走，我们试着把以（1,1）点为中心的横纵左边的初始状态也求出来，记住及时break

状态转移：
递推方向为i从2->h,j从2->w。显然可以得到状态转移方程为

```
dp[i][j] = (dp[i-1][j] + dp[i][j-1]) (a[i][j] == '.')

```

实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1100;
const int INF = 1e9+7;
char a[maxn][maxn];
int dp[maxn][maxn];		//dp[i][j]´ú±íÖÕµãÎªi,jµÄ·½°¸Êý 
bool vis[maxn][maxn];
long long ans = 0,h,w;

int main() {
	cin>>h>>w;
	for(int i = 1;i <= h;i++) {
		scanf("%s",a[i]+1);
	}
	for(int i = 1;i <= w;i++) {
		if(a[1][i] == '.') dp[1][i] = 1;
		else break;
	}
	for(int i = 1;i <= h;i++) {
		if(a[i][1] == '.') dp[i][1] = 1;
		else break;
	}
	
	for(int i = 2;i <= h;i++) {
		for(int j = 2;j <= w;j++) {
			if(a[i][j] == '.') {
				dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % INF;
			}
		}
	}
	cout<<dp[h][w];
	return 0;
}  
```


---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4529) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_h)

>有一个$n\times m$的网格，第$i$行第$j$列有一个字符$a_{i,j}\in\{\texttt.,\texttt\#\}$，分别表示是空格和是障碍物。保证$a_{1,1}=a_{n,m}=\texttt.$。求从$(1,1)$开始，只能往右或往下走，有多少种方法到达$(n,m)$。答案对$10^9+7$取模。

>$n,m\in[1,1000]$。

设$dp_{i,j}$表示从$(1,1)$开始，只能往右或往下走，有多少种方法到达$(i,j)$。边界是$dp_{1,1}=1$，目标是$dp_{n,m}$，状态转移方程是$dp_{i,j}=\begin{cases}dp_{i-1,j}+dp_{i,j-1}&a_{i,j}=\texttt.\\0&a_{i,j}=\texttt\#\end{cases}$。时间复杂度$\mathrm O(nm)$。

~~记得边DP边取模~~

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
const int N=1000,M=1000;
int n,m;
char a[N+1][M+5];
int dp[N+1][M+1];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i]+1;
	dp[1][1]=1;//边界 
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(i!=1||j!=1)//转移 
		if(a[i][j]=='.')dp[i][j]=(dp[i-1][j]+dp[i][j-1])%mod;
	cout<<dp[n][m];//目标 
	return 0;
}
```

---

## 作者：houpingze (赞：0)

一道非常简单的`dp`qwq

当$f_{i,j}$不是`#`（障碍物）的时候：

![image.png](https://i.loli.net/2021/01/03/2V34jDdniyRcwYk.png)

即：
$f_{i,j}=f_{i-1,j}+f_{i,j-1}$

如果是障碍物，$f_{i,j}$自然为$0$

code:

```cpp
#include<bits/stdc++.h>
#define reg register int
#define INF (1<<30)
using namespace std;
int read(){
	int res=0,fs=1; char c=getchar();
	while(!(c>='0' && c<='9')){ if(c=='-')fs=-1; c=getchar(); }
	while(c>='0' && c<='9')res=res*10+c-'0',c=getchar();
	return res*fs;
}
void print(int x){
    if(x<0) { putchar('-'); x=-x;}
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
int n,cnt,m,a[5010],ans,tmp;
char mp[1105][1005];
//mp数组是地图
int f[1005][1005];
//f[i][j]表示走到（i,j）的方案数
int main() {
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j]; 
		}
	}
	f[1][1]=(mp[1][1]!='#');//注意起点
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i==1&&j==1) continue;
			f[i][j]=f[i-1][j]+f[i][j-1];
			f[i][j]%=1000000007;//别忘记取模！
			if(mp[i][j]=='#') f[i][j]=0;//有障碍物，直接设为0
		}
	}
	cout<<f[n][m];
    return 0;
}


```

---

