# Decreasing Heights

## 题目描述

You are playing one famous sandbox game with the three-dimensional world. The map of the world can be represented as a matrix of size $ n \times m $ , where the height of the cell $ (i, j) $ is $ a_{i, j} $ .

You are in the cell $ (1, 1) $ right now and want to get in the cell $ (n, m) $ . You can move only down (from the cell $ (i,       j) $ to the cell $ (i + 1, j) $ ) or right (from the cell $ (i,       j) $ to the cell $ (i, j + 1) $ ). There is an additional restriction: if the height of the current cell is $ x $ then you can move only to the cell with height $ x+1 $ .

 Before the first move you can perform several operations. During one operation, you can decrease the height of any cell by one. I.e. you choose some cell $ (i, j) $ and assign (set) $ a_{i, j} := a_{i, j} - 1 $ . Note that you can make heights less than or equal to zero. Also note that you can decrease the height of the cell $ (1, 1) $ .

Your task is to find the minimum number of operations you have to perform to obtain at least one suitable path from the cell $ (1, 1) $ to the cell $ (n, m) $ . It is guaranteed that the answer exists.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
3 4
1 2 3 4
5 6 7 8
9 10 11 12
5 5
2 5 4 8 3
9 10 11 5 1
12 8 4 2 5
2 2 5 4 1
6 8 2 4 2
2 2
100 10
10 1
1 2
123456789876543 987654321234567
1 1
42```

### 输出

```
9
49
111
864197531358023
0```

# 题解

## 作者：_Album_ (赞：9)

更好的阅读：[传送门](https://payphone-x.top/2020/05/26/CF1353F/)

------------------

## 分析

很套路的$\text{dp}$题，但也有一定难度，放在$\text{Div 3}$的$\text{F}$题完全可以接受

读完题后，很容易想到此题的一个**弱化版本：给定一个矩阵，每次只可以向下或向右移动，如何行走才能使得经过点的点权之和最大**？

思考如何把这个题转化过去。不难发现，如果知道了这个点的起点高度$h$，则走到坐标为$(i , j)$的点上高度应该为$h + i + j$。

所以就有了以下两点推论：
1. 设一个点坐标为$(i , j)$，若$a[i][j] > h + i + j$，则该点不可能被经过。
   
2. 若$a[i][j] \leq h + i + j$，则经过该点所需要的操作次数为$(h + i + j) - a[i][j]$。

也就是说，我们只需要把$a[i][j] \leq h$的点的点权设为$(h + i + j) - a[i][j]$即可。

然后考虑如何解决上面的弱化版问题。

设$f[i][j]$表示从$(1 , 1)$走到$(i , j)$所需要的最少次数，则$f[1][1] = 0$。

之后考虑如何转移。首先，对于点$(i , j)$，有

$$f[i][j] = f[i][j] + (h + i + j - a[i][j])$$

之后考虑向外拓展。若$i + 1 \leq n$，则

$$f[i + 1][j] = min(f[i + 1][j] , f[i][j])$$

$j$也同理，若$j + 1 \leq m$，则

$$f[i][j + 1] = min(f[i][j + 1] , f[i][j])$$

最后在外面套一层$O(n^2)$的枚举，枚举矩阵元素并倒推初始点的权值，即$h = a[i][j] - i - j$。

每一次$\text{dp}$的时间复杂度为$O(n^2)$，加上外层的枚举，时间复杂度为$O(n^4)$。足以跑过$100\%$的数据。

剩下的见代码即可。

--------------------------------------

## Code[Accepted]

```Cpp
#include <bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define clean(a , b) memset(a , b , sizeof(a))
#define rep(i , l , r) for (int i = (l); i <= (r); i ++)
#define per(i , r , l) for (int i = (r); i >= (l); i --)

using namespace std;

const int N = 10001;
const int M = 100001;
const int HA = 998244353;
const int INF = 2147483647;
const long long INFL = 9023372036854775801;

ll a[101][101] , f[101][101];

ll solve(ll n , ll m , ll sta){
    rep(i , 1 , n){
        rep(j , 1 , m){
            f[i][j] = INFL;
        }
    }
    f[1][1] = 0;
    rep(i , 1 , n){
        rep(j , 1 , m){
            ll val = i + j + sta;
            if(val > a[i][j]){
                f[i][j] = INFL;
                continue;
            }
            f[i][j] += a[i][j] - val;
            if(i + 1 <= n){
                f[i + 1][j] = min(f[i + 1][j] , f[i][j]);
            }
            if(j + 1 <= m){
                f[i][j + 1] = min(f[i][j + 1] , f[i][j]);
            }
        }
    }
    return f[n][m];
}

int main() {
    #ifdef LOCAL
        freopen("try.in" , "r" , stdin);
        freopen("try1.out" , "w" , stdout);
    #endif
    ll t , n , m;
    scanf("%lld" , &t);
    while(t --){
        clean(a , 0);
        scanf("%lld%lld" , &n , &m);
        rep(i , 1 , n){
            rep(j , 1 , m){
                scanf("%lld" , &a[i][j]);
            }
        }
        ll ans = INFL;
        rep(i , 1 , n){
            rep(j , 1 , m){
                ans = min(ans , solve(n , m , a[i][j] - i - j));
            }
        }
        printf("%lld\n" , ans);
    }

    return 0;
}
```

------------------------------------

# THE END



---

## 作者：徐天乾 (赞：7)

# 思路
题目中要求只能从高度为 $x$ 的格子到高度为 $x+1$ 的格子，不妨令 $(1,1)$ 的高度为 $a$，易知从 $(1,1)$ 到 $(n,m)$ 的高度依次为 $a$，$a+1$，...，$a+n+m-2$。同时，对于一个只能向右或向下的矩阵来说有一个特殊的性质：从 $(1,1)$ 到 $(i,j)$ 的距离恒定。于是我们可以想到先把读入的 $a_{i,j}$ 变为 $a_{i,j}-i-j$，使题目条件更加简单。

现在题目要求的路径只要 $a_{i,j}$ 相同即可。由 $n≤100$；$m≤100$ 可以想到时间复杂度应当在 $O((nm)^2)$ 以内，于是我们可以先枚举路径中相同的 $a_{i,j}$，之后在进行 dp 遍历就可以求出最小值。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int i,j,n,m,T,Min,a[110][110],dp[110][110];
int read(){    
	int x=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
	return x;
}
int solve(int x){
	for (int i=0;i<=n;i++)
		for (int j=0;j<=m;j++)
			dp[i][j]=1e18;
	dp[1][1]=a[1][1]-x;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]>=x&&(i!=1||j!=1))
				dp[i][j]=min(dp[i-1][j],dp[i][j-1])+a[i][j]-x;
	return dp[n][m];
}
signed main(){
	T=read();
	while (T--){
		n=read();m=read();Min=1e18;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				a[i][j]=read()-i-j;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				if (a[1][1]>=a[i][j])
					Min=min(Min,solve(a[i][j])); 
		printf("%lld\n",Min);
	}
	return 0;
}
```
# 后记
这一类的题目只要多多积累，就可以轻易想出思路了。~~所以说大家多多卷题~~

---

## 作者：Kketchup (赞：3)

### [CF1353F Decreasing Heights](https://codeforces.com/problemset/problem/1353/F)

- DP

**Sol:** 一开始想到设 $f_{i,j,k}$ 表示到达点 $(i,j)$，此点高度改成 $k$ 的最小代价。优化状态，发现如果已知初始高度是 $x$，点 $(i,j)$ 的高度一定是 $x+i+j-2$。于是直接设 $f_{i,j}$ 表示到达点 $(i,j)$ 的最小代价。朴素枚举复杂度是 $O(nmV)$ 的，值域 $10^{15}$ 的情况下肯定不行。

我们需要与值域无关的解法。将合法路径上的高度画图后发现，更改高度后变成的 $x,x+1,\cdots,x+n+m-2$ 所连成的直线在最优情况下一定与初始高度序列折线至少有一个交点（当然值域一定要在初始序列下面），否则 $x$ 向上一个单位答案只会更优。

于是我们直接枚举那个交点，也就是保留高度为 $a_{i,j}$ 的点，那根据之前的分析，起点的高度就是 $a_{i,j}-(i+j-2)$。这时候做第一部分的 DP 即可。枚举点复杂度 $O(n^2)$，DP 复杂度 $O(n^2)$，总复杂度 $O(n^4)$，可以通过。

**Trick:** 在发现一旦确定一个点最终高度，整张图高度都确定的情况下，找到一定有高度不变点的性质，想到转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define Fo(i,x,y) for(int i=(x);i>=(y);--i)
const int N=105;
#define int ll
int n,m;
int a[N][N];
ll f[N][N],ans=1e18;
void solve(){
    cin>>n>>m;
    F(i,1,n) F(j,1,m) cin>>a[i][j];
    ans=1e18;
    F(x,1,n){
        F(y,1,m){
            int p=a[x][y]-x-y+2;
            if(a[1][1]<p) continue;
            F(i,1,n) F(j,1,m) f[i][j]=1e18;
            f[1][1]=a[1][1]-p;
            F(i,1,n){
                F(j,1,m){
                    if(!(i==1&&j==1)&&a[i][j]>=p+(i+j-2)){
                        f[i][j]=min(f[i-1][j],f[i][j-1])+a[i][j]-(p+(i+j-2));
                    }
                }
            }
            ans=min(ans,f[n][m]);
        }
    }
    cout<<ans<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    memset(f,0x3f,sizeof(f));
    while(T--) solve();
    return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：3)

由题意可以有两个观察：

+ 若 $(1,1)$ 确定为 $p$，则对于最终路径上的 $(x,y)$，其高度最终将确定为 $p+x+y-2$。
+ 最终的路径上一定有至少一个点没有改。反证法，如果都改了可以少改几次这条路依然能走。

那么，考虑先钦定某个点的权值是不变的为 $a(i,j)$。

则 $a^\prime(1,1)=a(i,j)-i-j+2$，那么可以发现对于其他的 $a(x,y)$，走这个点的花费将是 $a(x,y)+x+y+2-a(i,j)+i+j-2$，直接设 $b(i,j)=a(i,j)-i-j$，则花费为 $w(x,y)=b(x,y)-b(i,j)$。

那么接下来的问题就是已知每个点的花费为 $w$，求左上到右下的最短路径。这个是非常简单的 dp 了。复杂度 $O(n^4)$。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static ll _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline ll read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=105;
const ll inf=1e18;
ll f[N][N], a[N][N], b[N][N], w[N][N];
int qt, n, i, j, k, m;
ll res;
inline ll solve(ll x)
{
	int i, j;
	rep(i, 1, n) rep(j, 1, m) w[i][j]=b[i][j]-x;
	rep(i, 0, n) rep(j, 0, m) f[i][j]=inf; f[1][0]=0;
	rep(i, 1, n) rep(j, 1, m)
	{
		if(w[i][j]<0) continue;
		f[i][j]=min(f[i-1][j], f[i][j-1])+w[i][j];
	}
	return f[n][m];
}
int main()
{
	scanf("%d", &qt);
	while(qt--)
	{
		scanf("%d %d", &n, &m);
		rep(i, 1, n) rep(j, 1, m) scanf("%lld", a[i]+j);
		rep(i, 1, n) rep(j, 1, m) b[i][j]=a[i][j]-i-j;
		res=inf; rep(i, 1, n) rep(j, 1, m) res=min(res, solve(b[i][j]));
		printf("%lld\n", res);
	}
}
```

---

## 作者：lalaji2010 (赞：1)

# CF1353F Decreasing Heights

显然我不能一眼看出结论。

于是讲一下我的考场思路。

## 分析

设输入的点 $i,j$ 高度为 $mp_{i,j}$。

首先，对于坐标 $(x,y)$，当且仅当 $mp_{x,y}=mp_{1,1}+x+y-2$ 时，这个坐标才有可能被走到。

进一步地，我们如果知道在 $(1,1)$ 向下挖了 $k$ 格，那么 $(1,1)$ 的高度就应该是 $mp_{x,y}-k$，进而我们能求出坐标 $(p,q)$ 想要被走到需要向下挖 $mp_{p,q}-(mp_{x,y}-k+p+q-2)$ 格。

而如果此时对于 $(x_1,y_1)$ 有 $mp_{x_1,y_1}<mp_{x,y}-k+x_1+y_1-2$，这个点是无论如何都走不到了。

如果我们朴素地枚举起点挖的深度 $k$，那么时间复杂度是爆炸的。

考虑去除无效枚举。对于枚举的 $k_1$ 和 $k_2$，假设 $k_1<k_2$，如果起点挖了 $k_1$ 格和 $k_2$ 格能够通行的坐标一样，那么肯定挖 $k_1$ 次，因为挖的更少。

扩展一下，有贡献的 $k$ 一定使某些点恰好不需要挖。形式化地，对于优秀的 $k$，应当存在坐标 $(x,y)$ 满足 $mp_{x,y}=mp_{1,1}-k+x+y-2$。其实就是起点挖掉 $k$ 格之后想要走到 $(x,y)$ 的话 $(x,y)$ 的地方就不需要再挖了。

思考一下，可以发现此时枚举 $k$ 和枚举 $(x,y)$ 是等价的。这个过程就推出了其他题解里的挖完之后一定有一个点不变的结论。

所以我们可以直接枚举不需要挖的坐标 $(x,y)$，然后就能算每个坐标想要通行的花费（不能通行的坐标花费为正无穷），再直接进行那个最板的 dp 即可。

总结：考场上想得有点麻烦，但好在殊途同归。由暴力优化到正解的关键在于约束 $k$ 的选择范围。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
	long long ans=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<3)+(ans<<1)+(ch^48);
		ch=getchar();
	}
	return ans;
}
void write(long long n){
	if(n>=10) write(n/10);
	putchar(n%10+'0');
}
int T;
int n,m;
long long mp[105][105],dp[105][105];
long long res;
int main(){
	T=read();
	while(T--){
		res=9e18;
		n=read(),m=read();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				mp[i][j]=read();
			}
		}
		for(int px=1;px<=n;px++){
			for(int py=1;py<=m;py++){
				long long stval=mp[px][py]-(px+py-2);
				if(mp[1][1]<stval) continue;
				for(int i=0;i<=n;i++){
					for(int j=0;j<=m;j++){
						dp[i][j]=9e18;
					}
				}
				dp[1][1]=mp[1][1]-stval;
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++){
						if(i==1&&j==1||mp[i][j]<stval+i+j-2) continue;
						dp[i][j]=min(dp[i-1][j],dp[i][j-1])+mp[i][j]-(stval+i+j-2);
					}
				}
				res=min(res,dp[n][m]);
			}
		}
		write(res);
		puts("");
		
	}
	
	return 0;
}
```

---

## 作者：Helloworldwuyuze (赞：1)

# CF1353F 题解

## Des

给定一个 $n\times m$ 的矩阵，你需要从 $(1,1)$ 走到 $(n,m)$。每个点有一个权值 $a_{i,j}$。每一次可以从 $(i,j)\to (i+1,j)$ 或 $(i,j)\to (i,j+1)$。并且没必须要求 $a_{i,j}+1=a_{i+1,j}$ 或 $a_{i,j}+1 = a_{i,j+1}$。

## Sol

首先，容易发现的是，如果我们确定了 $a_{1,1}$ 的值，那么剩下的地方是什么也就随之确定了。这是因为走到 $(i,j)$ 一定需要 $(i+j-2)$ 步。

于是，我们能够得到每个位置的目标值 $w_{i,j}$。如果原值 $a_{i,j}$ 比目标值大，那么它可达，且代价为 $a_{i,j}-w_{i,j}$。否则不可达。这样，我们就可以使用一个简单的 $O(n^2)$ 动态规划来解决问题。具体地，方程为：
$$
f_{i,j} = \min\{f_{i,j-1}, f_{i-1,j}\} +a_{i,j}-w_{i,j}
$$
但是，这不一定是最优的，甚至有可能是无解的，因此，我们并不能仅仅只设置这一种标准。

于是，我们又注意到，任意一个点被定为基准之后，其它的所有点也都可以被确定。因此，我们大胆猜测将上述过程重复 $n^2$ 遍就可以通过。但这是为什么呢？

我们设当前钦定的基准是 $(i,j)$。现在，我们让 $a_{i,j}$ 进行 $+1$ 或 $-1$ 操作。如果这个时候不优，那么继续加显然也不优。如果这个时候变优了，那么直到加到与它值域相邻的点为止都会变优，这是因为相对值域关系不变。这样，我们就可以在别的位置上算出这个值并算入答案中。

## Code

```cpp
#define int long long
const int INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
typedef pair<int,bool*> PIB;
const int N = 1e2 + 10;
const int M = 1e6 + 10;
inline int max(int x,int y){ return x<y ? y : x; }
inline int min(int x,int y){ return x<y ? x : y; }

int f[N][N], n, m, t, a[N][N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>t;
	memset(a, 0x3f, sizeof(a)), memset(f, 0x3f, sizeof(f));
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)	cin>>a[i][j];
		int ans = INF;
		for(int x=1;x<=n;++x)
			for(int y=1;y<=m;++y){
				for(int i=1;i<=n;++i)
					for(int j=1;j<=m;++j)	f[i][j] = INF;
				if(a[1][1] < a[x][y]-x-y+2)	continue;
				f[1][1] = a[1][1] - (a[x][y]-x-y+2);
				for(int i=1;i<=n;++i)
					for(int j=1;j<=m;++j)
						if(!(i==1 && j==1) && a[i][j] >= a[x][y]-x-y+i+j)
							f[i][j] = min(f[i-1][j], f[i][j-1]) + a[i][j] - (a[x][y]-x-y+i+j);
				ans = min(ans, f[n][m]);
			}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：bananamilktea (赞：0)

### 思路

不难发现，如果 $(1, 1)$ 的高度确定了，那么其他位置的高度肯定也是固定的，因为你只能向下或向右，而每一步都只能向上走一格，所以你走了几步，你当前的位置就是 $(1, 1)$ 处加上几。

根据这个性质，可以枚举 $(1, 1)$ 的高度，再做 dp。但是格子的高度最多是 $10^{15}$，如果直接枚举就会超时。所以需要通过其他的方式来确定 $(1, 1)$ 的高度。

可以发现，与其将除了 $(1, 1)$ 外的每个格子都降低一格，不如直接通过更改 $(1, 1)$ 的方式替代。所以除了 $(1, 1)$ 外，至少有一个格子不会被更改。那么枚举这个未被更改的格子，可以通过这个位置的高度计算出 $(1, 1)$ 的高度，接着就可以 dp 解决了。

### 代码

感觉我自己讲的不是很清楚，直接上代码好了。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 1;

__int128 ans = LLONG_MAX, dp[MAXN][MAXN];             //因为正无穷的值太大会越界，太小有会出bug，所以索性直接开int128 
long long n, m, t, a[MAXN][MAXN], res;
__int128 dis(__int128 x, __int128 y) {                // x表示更改后的数，y表示原数，这个函数用于计算原数需要更改几次可以得到更改后的数
	return (x > y ? LLONG_MAX : y - x);               // 更改后的数只会比原数小，如果比原数大，说明无解 
}

int main() {
	cin >> t;
	while(t--) {
		ans = LLONG_MAX;
		cin >> n >> m;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				cin >> a[i][j];
			}
		}
		for(int i = 1; i <= n; i++) {                            //由于如果所有的值都减少，可以用只减少(1, 1)的方式来代替，所以至少会有一个未被更改的数 
			for(int j = 1; j <= m; j++) {                        //枚举这个数，并且通过这个值来计算初始值 
				__int128 st = a[i][j] - (i + j - 1 - 1);         //因为只能往下或者往右，所以可以通过当前的数计算(1, 1)处的高度 
				fill(dp[0], dp[n] + m + 1, LLONG_MAX);           //全都设为正无穷，方便更改dp数组 
				dp[1][1] = dis(st, a[1][1]);                     //计算初始值 
				for(int k = 1; k <= n; k++) {                    //得到初始值后，不难计算出每个位置应该被更改为多高，所以可以开始dp 
					for(int l = 1; l <= m; l++) {
						if(k == 1 && l == 1) {                   //(1, 1)已经初始化，无需再次计算 
							continue;
						} 
						dp[k][l] = min(dp[k - 1][l], dp[k][l - 1]) + dis(st + k + l - 1 - 1, a[k][l]); //每次可以从上方和左方转移而来 
					}
				}
				ans = min(ans, dp[n][m]);                        //如果计算出来的结果比答案小，更新答案 
			}
		}
		res = ans;          //int128不可以直接输出，所以找一个long long来替代
		cout << res << "\n";
	}
	return 0;
}
```

注意一下，如果要使用 int128，要选择语言 `GNU G++20 13.2 (64 bit, winlibs)`。

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：


如果直接按照题目中给出的方式计算路径的代价会非常不方便，对其进行转化。

具体地考虑某一条路径，发现每一次的要求值都是在前一个的基础上增加 $1$ 形成的，由此可以考虑对于这条路径上第 $i$ 个走到的位置的权值减少 $i$，注意到题目只和相对值有关，在这一步中加入任何常数都是没有意义的。那么问题也就转化成了在更改之后的路径上选择一个数，使得差的绝对值最小且要求路径上的每一个点都不比这个值小。很明显这个值表示起点的修改之后的位置，且应当是修改后序列中最小的一个值。换言之，这个值一定出现在序列中。

由此拓展到矩阵，可以发现，每一个位置被经过时的位置是固定的，可以直接在矩阵上进行操作。而且，由于数据范围较小，可以直接枚举取定的初始值，并在接下来的过程中用 $\text{DP}$ 解决问题。

更具体的，设当前取出的初始值为 $x$，再设 $f_{i,j}$ 表示从 $(1,1)$ 到达 $(i,j)$ 的最小代价。每一个位置能且仅能从 $f_{i-1,j}$ 或者 $f_{i,j-1}$ 转移，每一次转移的代价即为 $a_{i,j}-i-j-x$，注意能够进行的操作只有减少，如果此值小于 $0$ 无法进行操作使其变成需要的值，需要跳过。

总复杂度为 $O(n^4)$，对于 $100$ 的数据范围而言可以接受。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
int T,n,m,a[105][105],f[105][105],ans;
void work(int x){
	for(int i=0;i<=n;i++) 
	for(int j=0;j<=m;j++)
	f[i][j]=923372036854775808;
	f[0][1]=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		if(a[i][j]<x)continue;
		f[i][j]=min(f[i-1][j],f[i][j-1])+a[i][j]-x;
	}
	ans=min(ans,f[n][m]);
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		ans=9223372036854775807;
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%lld",&a[i][j]);
			a[i][j]-=i+j;
		}
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		work(a[i][j]);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

