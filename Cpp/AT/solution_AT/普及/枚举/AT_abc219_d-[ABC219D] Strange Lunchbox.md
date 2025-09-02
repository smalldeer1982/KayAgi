# [ABC219D] Strange Lunchbox

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc219/tasks/abc219_d

$ N $ 種類の弁当が、それぞれ $ 1 $ 個ずつ売られています。  
 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 種類目の弁当には $ A_i $ 個のたこ焼きと $ B_i $ 個のたい焼きが入っています。

高橋君は、 $ X $ 個以上のたこ焼きと $ Y $ 個以上のたい焼きを食べたいです。  
 高橋君がいくつかの弁当を選んで買うことで、 $ X $ 個以上のたこ焼きと $ Y $ 個以上のたい焼きを手に入れることが可能かどうか判定して下さい。また、可能な場合はそのために高橋君が購入しなければならない弁当の個数の最小値を求めて下さい。

各種類の弁当は $ 1 $ 個しか売られていないため、同じ種類の弁当を $ 2 $ 個以上購入することは出来ないことに注意して下さい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300 $
- $ 1\ \leq\ X,\ Y\ \leq\ 300 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 300 $
- 入力はすべて整数

### Sample Explanation 1

高橋君は、$ 5 $ 個以上のたこ焼きと $ 6 $ 個以上のたい焼きを食べたいです。 高橋君は $ 2 $ 種類目の弁当と $ 3 $ 種類目の弁当を買うことで、 たこ焼きを $ 3\ +\ 2\ =\ 5 $ 個、たい焼きを $ 4\ +\ 3\ =\ 7 $ 個手に入れることができます。

### Sample Explanation 2

高橋君がたとえすべての弁当を買ったとしても、高橋君は $ 8 $ 個以上のたこ焼きと $ 8 $ 個以上のたい焼きを手に入れることが出来ません。 よって、$ -1 $ を出力します。

## 样例 #1

### 输入

```
3
5 6
2 1
3 4
2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
3
8 8
3 4
2 3
2 1```

### 输出

```
-1```

# 题解

## 作者：mojoege (赞：3)

## 题意
有 $n$ 份盒饭，每份盒饭有 $a_i$ 个 A 种，$b_i$ 个 B 种。

求至少要多少个盒饭使得 A 种和 B 种的份数分别大于 $x$ 和 $y$。

## 分析

很明显是一个 dp 题。

按照朴素的想法，$dp_{i,j,k}$ 表示前 $i$ 个盒饭中有 $j$ 个 A 种和 $k$ 个 B 种，很明显这样会 RE。

转换一下，令 $dp_{i,j,k}$ 表示前 $i$ 个盒饭中有大于等于 $j$ 个 A 种和大于等于 $k$ 个 B 种，这样子数组只用开到 $300 \times 300 \times 300$ 就够了。

转移分两种，然后取个 $\min$：

- 取 $i - 1$ 个盒饭就已经满足要求，$dp_{i,j,k}=dp_{i-1,j,k}$。
- 取第 $i$ 个盒饭，$dp_{i,j,k}=dp_{i-1,j-a[i],k-b[i]}+1$。

basecase 很好想，肯定就是 $dp_{0,0,0}=0$。ans 就是 $dp_{n,x,y}$。

注意转移的时候要特判一下边界，防 RE。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, x, y;
int a[305], b[305], dp[305][305][305];

int main(){
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][0] = 0;//basecase
	for (int i = 1; i <= n; i++){
		for (int j = 0; j <= x; j++){
			for (int k = 0; k <= y; k++){
				if (dp[i - 1][j][k] != 0x3f3f3f3f) dp[i][j][k] = dp[i - 1][j][k];//直接满足条件
				dp[i][j][k] = min(dp[i][j][k], dp[i - 1][max(j - a[i], 0)][max(k - b[i], 0)] + 1);//转移，记得特判一下边界
			}
		}
	}
	cout << (dp[n][x][y] == 0x3f3f3f3f ? -1 : dp[n][x][y]);
	return 0;
}
```

---

## 作者：SkyLines (赞：2)

这道题很明显就是一道 $01$ 背包的题。

设 $dp_{i,j}$ 为 $\sum _ {k = 1} ^ n$ 达到 $i$，$\sum _ {k = 1} ^ n$ 达到 $j$ 的最小套餐数。

则有：

$$dp_{i,j}=\min(dp_{i,j},dp_{x,y}+1)$$

其中，有 $i=\min(x+a_i,X)$，$j=\min(y+b_i,Y)$。

先枚举 $i$，再枚举上述中的 $x$ 和 $y$。根据经验可知，$x$ 和 $y$ 要倒序枚举。

初始化 $dp_{0,0}=0$，$dp$ 数组的其他位置全为极大值。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x, y, a[305], b[305], aa, bb, dp[1005][1005];
int main()
{
	for(int i = 0; i < 1005; i++) for(int j = 0; j < 1005; j++) dp[i][j] = 1e9;
	dp[0][0] = 0;
	scanf("%d %d %d", &n, &x, &y);
	for(int i = 1; i <= n; i++) scanf("%d %d", &a[i], &b[i]);
	for(int i = 1; i <= n; i++)
	{
		for(int j = x; j >= 0; j--)
		{
			for(int k = y; k >= 0; k--)
			{
				aa = min(x, j + a[i]);
				bb = min(y, k + b[i]);
				dp[aa][bb] = min(dp[aa][bb], dp[j][k] + 1);
			}
		}
	}
	if(dp[x][y] != 1e9) printf("%d", dp[x][y]);
	else printf("-1");
	return 0;
}
```

---

## 作者：shAdomOvO (赞：1)

### 思路

因为 $n,x,y$ 非常小，都是 $300$ 考虑直接暴力 $dp$ 。设数组 $f[i][j][k]$ 表示前 $i$ 个盒子，$a$ 的和为 $j$ ，$b$ 的和为 $k$ 时所需的最少的盒子数。然后考虑转移。显然，这个题的转移就是 $f[i][j][k]=min(f[i-1][j][k],f[i-1][j-a_i][k-b_i]+1)$ 最后只要输出 $f[n][x][y]$ 即可。时间复杂度是 $O(n^3)$ 的。

但是，这个题需要注意一些细节。就写在注释中了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=400;
#define int long long
int n,a[N],b[N];
int f[N][N][N];
int x,y;
#define inf 1000000000
int maxn;
signed main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++)
		for(int j=0;j<=320;j++)
			for(int k=0;k<=320;k++)f[i][j][k]=inf;//初始化 
	for(int i=0;i<=a[1];i++)
		for(int j=0;j<=b[1];j++)f[1][i][j]=1;
	f[1][0][0]=0;
	for(int i=2;i<=n;i++)
		for(int j=0;j<=310;j++){
			for(int k=0;k<=310;k++){
				if(j<=a[i]&&k<=b[i])f[i][j][k]=1; 
				if(j==0&&k==0)f[i][j][k]=0;
				f[i][j][k]=min(f[i][j][k],f[i-1][j][k]);
				if(j<=a[i])f[i][j][k]=min(f[i][j][k],f[i-1][0][k-b[i]]+1);//如果小于的话需要特判一下 
				if(k<=b[i])f[i][j][k]=min(f[i][j][k],f[i-1][j-a[i]][0]+1);//
				if(j>=a[i]&&k>=b[i])f[i][j][k]=min(f[i][j][k],f[i-1][j-a[i]][k-b[i]]+1);
				//cout<<f[i][j][k]<<" ";
			}
			for(int k=310-1;k>=0;k--)f[i][j][k]=min(f[i][j][k],f[i][j][k+1]);//小的所需的肯定比大的要少 
			//cout<<endl;
		}
	if(f[n][x][y]==inf)cout<<-1;
	else cout<<f[n][x][y];
}
 
```


---

## 作者：loser_seele (赞：1)

变种 01 背包，但大体思路是相同的。

将 $ dp_{i,j} $ 视为当拿到 $ i $ 个 A 物品和 $ j $ 个 B 物品的时候的最小物品个数，初始时所有 $ dp $ 值都设为无穷大，初始状态 $ dp_{0,0} $ 为 $ 0 $，然后枚举物品种类和价值，每次取 $ dp{i,j} $ 和 $ dp_{i-A_now,j-B_now} $ 中的最小值更新答案，最后 $ dp{X,Y} $ 显然为最后答案，如果是无穷大则无解。

状态数 $ \mathcal{O}(XY) $ 个，每次转移 $ \mathcal{O}(N) $，总时间复杂度 $ \mathcal{O}(NXY) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
#define N 1010
#define INF 0x3f3f3f3f
using namespace std;
int m,n,k,a[N],b[N],c[N],dp[N][N]; 
int main()
{
	cin>>k>>m>>n;
	for(int i=1;i<=k;i++) 
    cin>>a[i]>>b[i],c[i]=1;
	memset(dp,INF,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=k;i++)
    {
		for(int x=m;x>=0;x--)
        {
			for(int y=n;y>=0;y--)
            {
				if(dp[x][y]==INF) 
                continue;
				int u=min(m,x+a[i]);
				int v=min(n,y+b[i]);
				dp[u][v]=min(dp[u][v],dp[x][y]+c[i]);
			}
		}
	}
    if(dp[m][n]!=INF)
	cout<<dp[m][n];
    else
    cout<<-1;
}
```


---

## 作者：qw1234321 (赞：0)

数据范围 $300$，考虑 DP，设 $f_{i,j,k}$ 表示前 $i$ 份套餐中选了大于等于 $j$ 个 $A_i$，大于等于 $k$ 个 $B_i$ 的方案数。

转移有不取套餐 $i$ 和取套餐 $i$ 两种情况，有如下方程：

$$f_{i,j,k} = \min(f_{i,j,k}, f_{i-1,j,k}, f_{i-1,j-a_i,k-b_i}+1)$$

还要注意 $j-a_i$ 和 $k-b_i$ 中的边界问题。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
namespace things{
	il int rd(){
		int f = 1, x = 0;
		char ch = getchar();
		while(ch < '0' || ch > '9'){
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9'){
			x = x * 10 + ch - '0';
			ch = getchar();
		}
		return x * f;
	}
	il int max(int x, int y, int z){
		return std::max(x, std::max(y, z));
	}
	il int min(int a, int b, int c){
		return std::min(a, std::min(b, c));
	}
}
using namespace things;
using namespace std;

const int N = 305, p = 1e9 + 7, INF = LONG_LONG_MAX / 2;
int n, x, y, a[N], b[N], f[N][N][N];

void work(){
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
	for (int i = 0; i <= n; i++) for (int j = 0; j <= x; j++) for (int k = 0; k <= y; k++) f[i][j][k] = INF;
	f[0][0][0] = 0;
	for (int i = 1; i <= n; i++) for (int j = 0; j <= x; j++) for (int k = 0; k <= y; k++) f[i][j][k] = min(f[i][j][k], f[i - 1][j][k], f[i - 1][max(0ll, j - a[i])][max(0ll, k - b[i])] + 1);
	cout << ((f[n][x][y] == INF) ? -1 : f[n][x][y]);
}

signed main(){
	int t = 1;
	//	cin >> t;
	while(t--) work();
	return 0;
}
```

---

## 作者：apiad (赞：0)

考虑 DP，这是一个典型的背包拓展，每一个物品只能选一个。

我们 $dp_{i,j,k}$ 的定义为前 $i$ 个物品，重量 $j$ 的章鱼烧，重量为 $k$ 的太白烧。

因此可以得到转移方程 $dp_{i+1,j+a_{i+1},k+b_{i+1}} = \min(dp_{i+1,j+a_{i+1},k+b_{i+1}},dp_{i,j,k})$ 和 $dp_{i+1,j,k} = dp_{i,j,k}$。

这两个分别为选或者不选。

VP 赛时 WA：[link](https://atcoder.jp/contests/abc219/submissions/50993732)。

思路大体上是对的，挂在了没有初始化，而且还可以有一定的优化，就是我们当这个背包的容量已经大于 $x$ 我们可以直接将此时的容量设为 $x$，可以有效减低空间代价，对于另一个背包也是取 $\min(val,y)$。$val$ 是此刻的背包重量。

因此选的转移方程变成了 $dp_{i+1,\min(j+a_{i+1},x),\min(k+b_{i+1},y)} = \min(dp_{i+1,\min(j+a_{i+1},x),\min(k+b_{i+1},y)},dp_{i,j,k})$

初始化一下，将 $j$ 为 $0$ 和 $k$ 为 $0$ 的状态都设为 $0$。其他的都是无穷大。

最后的答案就是 $dp_{n,x,y}$。

AC 的代码：[link](https://atcoder.jp/contests/abc219/submissions/51012783)。

---

## 作者：Frictional (赞：0)

## 题意
题目翻译说的很清楚，这里就不说了（逃。
## 思路
这道题一看就是一个背包，但和普通的 01 背包题不一样。我们令 $dp_{i,j}$ 为选 $a$ 的总量为 $i$，$b$ 的总量为 $j$ 所需要的最少的套餐数量。

之后，再来思考转移方程怎么推。假设现在考虑到了第 $i$ 个套餐。我们再枚举两个数 $p,q(0\leqslant p \leqslant x,0\leqslant q\leqslant y)$。令 $n=\min(p+a_i,x),m=(q+b_i,y)$ 来计算当前 $dp_{n,m}$ 的值（这里的 $x,y$ 就是题目中的 $x,y$）。

有两种情况，一种是第 $i$ 个物品不选，一种是选，对于不选的情况那么 $dp_{n,m}$ 不变，对于选的情况那么 $dp_{n,m}=dp_{p,q}+1$ 之后给这两种情况取最小值就是 $dp_{n,m}$ 现在的值了。

最后答案就是 $dp_{x,y}$，别忘记判断无解的情况就行了。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(a,b,c) for(int a=b;a<=c;a++)
#define ROF(a,b,c) for(int a=b;a>=c;a--)
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define debug(x) cerr<<#x<<'='<<x<<endl
int rd(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' or ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
int n;
int x,y;
const int N=305;
int a[N],b[N];
int amax,bmax;
int dp[N][N];
int e,f;
signed main(){
    n=rd();
    x=rd(),y=rd();
    FOR(i,1,n){
        a[i]=rd(),b[i]=rd();
        amax+=a[i];
        bmax+=b[i];
    }
    if(amax<x||bmax<y){
        cout<<-1;
        return 0;
    }
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
    FOR(i,1,n){
        ROF(p,x,0){
            ROF(q,y,0){
                e=MIN(p+a[i],x);
                f=MIN(q+b[i],y);
                dp[e][f]=MIN(dp[e][f],dp[p][q]+1);
            }
        }
    }
    cout<<dp[x][y];
    return 0;
}

```


---

## 作者：封禁用户 (赞：0)

数据范围仅 $300$，可以直接暴力 $\operatorname{dp}$。

$f[j][k]$ 表示总和为 $j$，$b[i]$ 总和为 $k$ 的最小套餐数。

则状态转移方程为：
					$dp[i][j]=\max(dp[i][j],dp[x][y]+1)$。
                    
注意：$dp[0][0]$ 要初始化为 $0$。

###  AC code
                    
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,y,a[305],b[305],dp[1005][1005];
bool f;
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=0;i<1005;i++){
		for(int j=0;j<1005;j++){
			dp[i][j]=1e9;
		}
	}
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=x;j>=0;j--){
			for(int k=y;k>=0;k--){
				int sx=min(j+a[i],x);
				int sy=min(k+b[i],y);
				dp[sx][sy]=min(dp[sx][sy],dp[j][k]+1);
			}
		}
	}
	if(dp[x][y]!=1e9)f=1;
	if(!f){
		cout<<-1;
		return 0;
	}
	cout<<dp[x][y];
	return 0;
}
```


---

## 作者：highkj (赞：0)

# 思路
一眼 Dp，我们可以发现这是一个 $01$ 背包，那么我们定义状态 $f_{x,y}$ 为前 $i$ 个食品（被压掉了），吃的的总和 $a_i$ 为 $x$ 且 $b_i$ 的总和为 $y$ 的方案数。然后我们的转移其实就是和 $01$ 背包差不多，只不过因为大于 $x$ 和 $y$ 也行，所以要在枚举值时和 $x$ 与 $y$ 取最小值，最后答案即为 $f_{x,y}$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
int n,x,y;
int f[1010][1010];
int a[1010],b[1010];
signed main() {
	cin>>n>>x>>y;
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	for(int i=1;i<=n;i++) {
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=n;i++) {
		for(int j=a[i]+x;j>=a[i];j--) {
			for(int k=b[i]+y;k>=b[i];k--) {
				f[min(x,j)][min(y,k)]=min(f[min(x,j)][min(y,k)],f[j-a[i]][k-b[i]]+1);
			}
		}
	}
	if(f[x][y]<=n) cout<<f[x][y]<<endl;
	else puts("-1");
	return false;
}
```

---

## 作者：KυρωVixen (赞：0)

## 题意：
有 $n$ 份套餐，每份套餐都有两个价值 $a_i$ 和 $b_i$。我们称一个选择方法是合法的，仅当选择的所有套餐的 $\sum a_i\ge x$，$\sum b_i\ge y$，每份套餐只能选择一次。求所有合法方案中最少需要买多少份套餐。

$n,a_i,b_i\le300$。
## 解法：
可以看做有两个维度作为费用的 01 背包，因为是求最小值，所以我们将 dp 数组除了 $dp_{0,0}$ 以外的部分初始化为无穷大，$dp_{0,0}=0$。

为了防止时空爆炸所以我们要滚动数组并且对方程做点小改变。
## 代码：

```cpp
#include<bits/stdc++.h>
#define INF 0X3F3F3F3F
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define repr(i,a,b) for(int i=a;i>=b;i--)
#define Puts(x) cout<<x<<'\n'
using namespace std;
int n,x,y,f[305][305];
signed main(){
	cin>>n>>x>>y; memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	rep(i,1,n){
		int a,b; cin>>a>>b;
		repr(j,x,0) repr(k,y,0){
			if(f[j][k]==INF) continue;
			int v1=min(x,j+a),v2=min(y,k+b); //这里注意
			f[v1][v2]=min(f[v1][v2],f[j][k]+1);
		}
	}
	if(f[x][y]==INF) puts("-1");
	else Puts(f[x][y]);
}
```

---

## 作者：ChenYanlin_20 (赞：0)

$f_{j,k}$：$a_i$ 总和为 $j$，$b_i$ 总和为 $k$ 的最小套餐数。

外层循环从 $1$ 到 $n$ 模拟套餐，内两层模拟 $j$ 与 $k$。

状态转移：

设 $t1$ 为 $\min(j+a_i,x)$，$t2$ 为 $\min(k+b_i,y)$，$f_{t1,t2}=\min(f_{t1,t2},f_{j,k}+1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[310],b[310],f[510][510];
int main(){
	int n,x,y;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	memset(f,0x3f3f3f3f,sizeof f);
    //0x3f3f3f3f　表　int　范围最大值
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=x;j>=0;j--){
			for(int k=y;k>=0;k--){
				int f1=min(j+a[i],x),f2=min(k+b[i],y);//状态转移
                
				f[f1][f2]=min(f[f1][f2],f[j][k]+1);
			}
		}
	}
	if(f[x][y]==0x3f3f3f3f)
		cout<<-1;
	else
		cout<<f[x][y];
	return 0;
}
```


---

## 作者：ZBH_123 (赞：0)

## 题目分析
本题可以看作是一个 $01$ 背包的变体。原本的 $01$ 背包只有一个费用，而本题有两个费用。所以，我们可以仿照 $01$ 背包的做法，设 $dp_{j,k}$ 为 $\sum a_i$ 达到 $j$，$\sum b_i$ 达到 $k$，所需的最小物品数。那么，对于第 $i$ 件物品，我们可以分两种情况：选或不选。在选第 $i$ 件物品的情况下，$dp_{j,k}$ 可以等于 $dp_{j-a_i,k-b_i}+1$。所以，我们可以得出下面这个状态转移方程：
$$dp_{j,k}=\min(dp_{j,k},dp_{j-a_i,k-b_i}+1)$$
其中 $a_i \le j$，$b_i \le k$。
## 代码实现
由于本题不需要 $\sum a_i$ 刚好等于 $x$，$\sum b_i$ 等于 $y$。所以我们可以将状态转移方程稍微变化一下，变成这个样子：
$$dp_{j+a_i,k+b_i}=\min(dp_{j+a_i,k+b_i},dp_{j,k}+1)$$
最后，当 $j+a_i$ 大于 $x$，或是 $k+b_i$ 大于 $y$，将它们分别用需求量代替就行了。

**AC code：**
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,x,y,a[305],b[305],suma,sumb,dp[305][305];
int main(){
	memset(dp,0x3f,sizeof dp);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		suma+=a[i],sumb+=b[i];
	}
	if(suma<x||sumb<y){
		cout<<-1;
		return 0;
	}
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=x;j>=0;j--){
			for(int k=y;k>=0;k--){
				int t1=j+a[i],t2=k+b[i];
				t1=min(t1,x),t2=min(t2,y);
				dp[t1][t2]=min(dp[t1][t2],dp[j][k]+1);
			}
		}
	}
	cout<<dp[x][y];
	return 0;
}
```

---

