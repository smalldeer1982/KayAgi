# [ABC311F] Yet Another Grid Task

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc311/tasks/abc311_f

$ N\ \times\ M $ のグリッドがあります。  
 このグリッドの上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ と書きます。  
 このグリッドの各マスは 白 か 黒 であり、その情報は $ N $ 個の長さ $ M $ の文字列 $ S_1,S_2,\dots,S_N $ として与えられます。

- もし $ S_i $ の $ j $ 文字目が `.` なら、マス $ (i,j) $ は 白 である。
- もし $ S_i $ の $ j $ 文字目が `#` なら、マス $ (i,j) $ は 黒 である。
 
以下の条件を満たすグリッドを **美しい** グリッドと呼びます。

- 全ての $ 1\ \le\ i\ \le\ N,\ 1\ \le\ j\ \le\ M $ を満たす整数組 $ (i,j) $ について、マス $ (i,j) $ が 黒 であれば、その下と右下のマスも (存在すれば) 黒 である。
- 厳密には、以下の条件を全て満たす。
  - マス $ (i,j) $ が 黒 でありマス $ (i+1,j) $ が存在するなら、マス $ (i+1,j) $ も 黒 である。
  - マス $ (i,j) $ が 黒 でありマス $ (i+1,j+1) $ が存在するなら、マス $ (i+1,j+1) $ も 黒 である。
 
高橋くんは、 白 のマスを $ 0 $ 個以上何個でも 黒 に塗ることができ、この操作によってグリッドを美しくしようとしています。  
 高橋くんが作ることのできる美しいグリッドの種類数を $ 998244353 $ で割った余りを求めてください。  
 但し、ある $ 2 $ つのグリッドが異なるとは、両者で色が異なるマスが存在することを指します。

## 说明/提示

### 制約

- $ 1\ \le\ N,M\ \le\ 2000 $
- $ S_i $ は `.` と `#` からなる長さ $ M $ の文字列
 
### Sample Explanation 1

作ることのできる美しいグリッドは以下の $ 3 $ 種類です。 ``` .# .# ## .# ## ## ```

### Sample Explanation 3

$ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
2 2
.#
..```

### 输出

```
3```

## 样例 #2

### 输入

```
5 5
....#
...#.
..#..
.#.#.
#...#```

### 输出

```
92```

## 样例 #3

### 输入

```
25 25
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................
.........................```

### 输出

```
604936632```

# 题解

## 作者：LJ07 (赞：6)

容易发现合法的形态长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/0uff7zny.png)

那就是对于高度 $h$ 有这样一个限制：$h_{i+1}\ge h_{i}-1$。

设 $dp_{i,j}$ 表示前 $i$ 列最后列高度为 $i$，全为空转移式为 $dp_{i,j}=\sum_{z=1}^{\min(n,j+1)}dp_{i-1,z}$。不全为空就相当于要求 $h_i\ge c_i$。$c_i$ 为第 $i$ 列最高黑点的高度。

前缀和优化即可。

```cpp
const int N(2e3), P(998244353);
int n, m, dp[N + 5][N + 5], h[N + 5];
char c[N + 5][N + 5];

int main() {
//  freopen("input.in", "r", stdin);
  rd(n), rd(m);
  U(i, 1, n) {
    scanf("%s", c[i] + 1);
  }
  U(j, 1, m) {
    U(i, 1, n) {
      if (c[i][j] == '#') {
        h[j] = n - i + 1;
        break;
      }
    }
  }
  U(i, 0, n + 1) {
    dp[0][i] = 1;
  }
  U(i, 1, m) {
    U(j, h[i], n) {
      dp[i][j] = dp[i - 1][j + 1];
    }
    U(j, h[i] + 1, n + 1) {
      dp[i][j] = (dp[i][j - 1] + dp[i][j]) % P;
    }
  }
  cout << dp[m][n + 1];
  return 0;
}
```

---

## 作者：Erinyes (赞：2)

朴素的题目。

### 分析

根据题意，我们可以把原矩阵一些白格子涂黑来使它合法，然后在这个合法的矩阵上面再涂黑一些格子来构造新的合法矩阵，令这个合法的矩阵为 $a$。

设 $h_i=\sum_{j=1}^{n}[a_{j,i}=1],(i\in[1,m])$，即 $i$ 这一列上黑点的数量，容易发现在这一列上，所有的黑点都是从下到上连续的，那么我们要做的就是通过确定每一列填完后的黑点数量（高度）来计数。

根据合法矩阵的性质，容易发现对于相邻的两列 $x,y$，它们填完的高度 $h\rq_x,h\rq_y$ 一定满足 $h\rq_x\le h\rq_y+1$，考虑 dp，设 $f_{i,j}$ 表示第 $i$ 列填完后的高度是 $j$，前 $i$ 列的合法方案数，于是可以写出朴素的转移：

$$f_{i,j}\longleftarrow \sum_{k=0}^{j+1} f_{i-1,k}$$

其中 $i\in[1,m],j\in[a_i,n]$，因为你不能删掉黑点。

答案即为 $\sum_{i=h_m}^{n} f_{m,i}$。

然后很明显这个可以前缀和优化，于是就完了，时间复杂度 $\operatorname{O}(nm)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int mod=998244353;
int n,m;
int a[2005][2005],h[2005],vst[2005][2005],f[2005][2005],g[2005][2005];
void col(int x,int y){
	a[x][y]=vst[x][y]=1;
	if(x+1<=n && !vst[x+1][y]) col(x+1,y);
	if(x+1<=n && y+1<=m && !vst[x+1][y+1]) col(x+1,y+1);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c; cin>>c;
			a[i][j]=(c=='#');
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			//将原矩阵补全为合法 
			if(a[i][j] && !vst[i][j]) vst[i][j]=1,col(i,j);
		}
	}
	for(int i=1;i<=n;i++){
		//统计每一列的高度h[i] 
		for(int j=1;j<=m;j++) if(a[i][j]) h[j]++;
	}
	f[0][0]=g[0][0]=1;
	for(int i=1;i<=n;i++) g[0][i]=(g[0][i-1]+f[0][i])%mod;
	for(int i=1;i<=m;i++){
		for(int j=h[i];j<=n;j++) f[i][j]=g[i-1][min(j+1,n)];
		g[i][0]=f[i][0];
		//前缀和优化 
		for(int j=1;j<=n;j++) g[i][j]=(g[i][j-1]+f[i][j])%mod;
	}
	int ans=0;
	for(int i=h[m];i<=n;i++) ans=(ans+f[m][i])%mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：0xyz (赞：2)

- 给你一个 $n\times m$ 的方格表，其中一些格子已经被染色了，你可以将一些无色格子染色，问有多少种不同的染色方法使得染完后的方格表满足“如果 $(i,j)$ 被染色，那么 $(i+1,j)$ 和 $(i+1,j+1)$ 也要被染色”。

赛时没做出来。后来想了一下，不算难。

```cpp
...#......
...##.....
.#.###..#.
.######.##
.#########
.#########
```

我们不妨手膜一组“美丽的方格表”（如上图），看到这些在“左上-右下”方向的平滑切面，我们陷入了沉思。

我们将这些“左上-右下”方向的每一排分开考虑。我们令 $a_{c}(1\le c\le n+m-1)$ 代表满足 $i-j=c-m$ 的格子里最终染色的个数，$b_c$ 代表第 $c$ 排一开始给定的最左上的被染色格子右下方有多少个格子（包括自己）。容易发现并证明第 $c$ 排的所有 $a_c$ 个被染色的格子都挤在右下方向。那么我们总的染色方法等同于合法的 $a$ 序列的个数。

现在我们要定义这个合法。首先，假设 $d_c$ 代表第 $c$ 排的格子个数，那么我们有 $b_c\le a_c\le d_c$。同时，要满足题目条件，我们发现，因为 $(i,j)$ 染色对应 $(i+1,j)$ 染色，所以有 $a_c\ge a_{c-1}(2\le c\le n)$。同时，因为在 $n+1\le c\le n+m-1$ 时依然有以上对应，只是最后的一个会不存在，所以此时有 $a_c\ge a_{c-1}-1$。

于是我们要求满足以上这些条件的 $a$ 序列的个数。因为 $a_c$ 仅与它本身限制和 $a_{c-1}$ 有关，尝试用动态规划。假设 $f_{i,j}$ 代表 $a_i=j$ 时第 $1\sim m$ 排到第 $i$ 排的 $a$ 序列总个数。我们有 $f_{i,j}=\sum\limits_{1\le k\le j+[i>n]}f_{i-1,k}$。这样一看就是 $O(n^3)$ 的。考虑前缀和优化，变为 $O(n^2)$，可以通过此题。使用滚动数组，空间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define w(x) (x>=mod?x-mod:x)
using namespace std;
typedef long long ll;
const ll mod=998244353,_=4010;
ll n,m,b[_],d[_],f[2][_];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;f[0][0]=1;
	for(ll i=1;i<n+m;i++)b[i]=min(n,i)+1;
	for(ll i=1;i<=n;i++){
		string g;cin>>g;
		for(ll j=1;j<=m;j++){
			d[i-j+m]++;
			if(g[j-1]=='#')b[i-j+m]=min(b[i-j+m],i);
		}
	}
	for(ll i=1,p=0,q=1;i<n+m;i++,swap(p,q)){
		for(ll j=1;j<=d[i]+1;j++)f[p][j]=w(f[p][j]+f[p][j-1]);
		for(ll j=min(n,i)-b[i]+1;j<=d[i];j++)f[q][j]=f[p][j+(i>n)];
		memset(f[p],0,sizeof(f[p]));
	} 
	cout<<w(f[(n+m-1)&1][0]+f[(n+m-1)&1][1])<<'\n';
	return 0;
}
```

---

## 作者：OtterZ (赞：1)

# 题意
你有一个 $ N \times M $ 方格阵，里面填了几个黑格，你可以额外填几个黑格，然后将每个黑格 $(i,j)$ 不断扩展到 $(i + 1,j)$ 和 $(i + 1,j + 1)$，问能形成多少种不同的新方格阵。
# 模拟起步
我们先将一个全白格子的一格涂黑，得到：
![](https://cdn.luogu.com.cn/upload/image_hosting/grjf2fqu.png)
然后扩展一次：
![](https://cdn.luogu.com.cn/upload/image_hosting/so77kt6s.png)
再扩展一次：
![](https://cdn.luogu.com.cn/upload/image_hosting/rj711vp8.png)
循环往复，我们最终会得到：
![](https://cdn.luogu.com.cn/upload/image_hosting/pcay95vo.png)
这时我们发现，对于每一列，从一行开始，后续都会被涂黑，且对于我们的每一次将小方格涂黑，我们发现后若干行被涂黑且行数最小的格子行数单调加 $1$。
![](https://cdn.luogu.com.cn/upload/image_hosting/jpqd58kn.png)
我们再涂一个格子：
![](https://cdn.luogu.com.cn/upload/image_hosting/vqli6r7w.png)
扩展得：
![](https://cdn.luogu.com.cn/upload/image_hosting/bnugqzrm.png)
我们发现：
对于每一列，我们行数最小的为黑格的格子行数 $x_i$ 为 $\min{x_{i - 1} + 1,\min_{(i,j) \text{ 为黑格 }}{j}}$，且对于任意 $j \ge x_i,(i,j)\text{ 为黑格}$。
# 动规打爆
接下来我们以此 `dp`，设 $dp_{i,j}$ 为第 $i$ 列 $\text{行数最小的黑格行数 }\ge j$ 的情况总数，易得：  
$$
dp_{i,j} = dp_{i - 1,j - 1} + dp_{i,j + 1}
$$   
为了方便转移，我们要求 $dp_{i,0} = dp_{i,1}$。  
这样答案就是 $dp_{n,1}$。
此时时间复杂度 $\operatorname{O}(nm)$。
# 注意事项

1. 转移时注意原有黑格。
2. 转移第一维为列而非行。
3. 原问题需要对 $998244353$ 取模。

# 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,mn[2009],dp[2009][2009];//dp[i][j]指第i列黑格最小行数为j的方案数。
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= m; i ++){
		mn[i] = n + 1;
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			char c;
			scanf(" %c",&c);
			if(c == '#' && mn[j] == n + 1){
				mn[j] = i;
			}
		} 
	}
	for(int i = 0; i <= n + 1; i ++){
		dp[0][i] = 1;
	}
	mn[0] = n + 1;
	for(int i = 1; i <= m; i ++){
		mn[i] = min(mn[i],mn[i - 1] == n + 1 ? n + 1 : mn[i - 1] + 1);
		for(int j = mn[i]; j >= 1; j --){
			dp[i][j] = (dp[i][j + 1] + dp[i - 1][j - 1]) % 998244353;
			//printf("%d %d\n",j,dp[i][j]);
		}
		dp[i][0] = dp[i][1];
	}
	printf("%d\n",dp[m][1]);
} 
```


---

## 作者：出言不逊王子 (赞：1)

题意很简单。

给 $n\times m$ 的格子染色。

若 $(i,j)$ 被染成了黑色，则 $(i+1,j)$ 与 $(i+1,j+1)$ 也必须是黑色。

求方案数。

我们发现，如果 $(i,j)$ 被染了色，则 $(i,j)$ 以下的点（即行数大于 $i$ 的点）都会被染色。

所以我们只要确定每一列被染色的最高点，就能依此画出一张图。

看上去不是很好组合计数，所以我们考虑 DP。

考虑 $f_{i,j}$ 为当前染色到第 $i$ 列且第 $i$ 列的染色最高点在 $j$ 的方案数。

如果第 $j$ 行被染了色，那么第 $i-1$ 列最多在第 $j+1$ 行被染色，也就是 $(i,j)$ 左上角一格的位置。

再往上的话，第 $j+1$ 行也得被染色了，但是这是不合法的。

对于原图上的每一列 $i$，记录这些列上的黑点所在的最高行，设为 $h_i$。

很显然，每一列的 $j$ 至少得是 $h_i$。

则 $f_{i,j}=\sum_{x=h_{i-1}}^{\min(n,j+1)} f_{i-1,x}$。

这个 DP 是三次方的。

但是因为每次转移对应的 $f_{i-1,x}$ 都是一段连续区间，所以我们可以前缀和优化。

这样复杂度就是二次方的了。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=2005,inf=998244353;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int n,m,h[N],f[N][N];
char c[N][N];	
signed main(){
	n=read(),m=read();
	fs(i,1,n,1) scanf("%s",c[i]+1);
	fs(i,1,m,1) fs(j,1,n,1) if(c[j][i]=='#'){h[i]=n-j+1;break;}
	fs(i,0,n,1) f[0][i]=1;
	fs(i,1,m,1){
		fs(j,h[i],n-1,1) f[i][j]=f[i-1][j+1];
		f[i][n]=f[i-1][n];
		fs(j,h[i]+1,n,1) (f[i][j]+=f[i][j-1])%=inf; 
	}
	cout<<f[m][n];
	return 0;
}
//f[i][j]表示第i列，高度为j的方案数
//f[i][j]=\sum_{x=h[i-1]}^{min(n,j+1)} f[i-1][x] 
//不可能出现上一个是n，这一个还是n的情况
//为啥不可能
//是可能的啊
//那这个咋统计 
//前缀和优化
```

---

## 作者：DengDuck (赞：1)

这道 F 怎么这么水，考场看都没看。

首先我们发现题目要求的图形相当于几个直角三角形，每个三角形内部递减。

我们考虑当前为第 $i$ 列高度为 $j$ 前一行的高度的可能，发现只可能是 $[mx,j+1]$，$mx$ 表示输入中原有的最高高度，然后直接转移即可。

注意这里的高度指的是到第 $n$ 行的距离。

注意需要前缀和优化。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2005;
const LL mod=998244353;
LL n,m,mx[N],f[N][N],sum[N][N];
char c[N][N];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>(c[i]+1);
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]=='#'&&mx[j]==0)mx[j]=n-i+1;
		}
	}
	for(int i=0;i<=n+1;i++)sum[0][i]=1;
	for(int i=1;i<=m;i++)
	{
		for(int j=mx[i];j<=n;j++)
		{
			f[i][j]=sum[i-1][j+1];
			if(mx[i-1]!=0)f[i][j]-=sum[i-1][mx[i-1]-1];
			f[i][j]+=mod;
			sum[i][j]=sum[i][j-1]+f[i][j];
			f[i][j]%=mod;
			sum[i][j]%=mod;
		}
		sum[i][n+1]=sum[i][n];
	}
	cout<<sum[m][n+1]<<endl;
}
```

---

## 作者：cosf (赞：0)

对于一个“beautiful”的格子的每一列，显然是某一格是黑的，它的下面全部都是黑的。特殊地，如果一列全白，我们可以认为它的第 $n + 1$ 个格子是黑的。

那么，我们令 $dp_{j, i}$ 表示第 $j$ 列从第 $i$ 个起都是黑色的方案数，则容易发现，可以从左往右地推：

$$
dp_{j, i} = \sum_{k = i - 1}^{n + 1}dp_{j - 1, i}
$$

注意，假设在给定的图中，假设第 $j$ 列最上面的黑色格子是 $(i', j)$，则 $dp_{j, i + 1}, \dots, dp_{j, n + 1}$ 都应该是 $0$，因为他们不可能作为最上面的黑格子。特别判断一下即可。

答案即 $\sum_{i = 1}^{n + 1}dp_{m, i}$。~~用库让代码更美观。~~

```cpp
#include <iostream>
#include <numeric>
#include "atcoder/modint"
using namespace std;

#define MAXN 2005

using mint = atcoder::modint998244353;

int n, m;

mint dp[MAXN][MAXN];

string s[MAXN];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        s[i] = " " + s[i];
    }
    dp[0][n + 1] = 1;
    for (int j = 1; j <= m; j++)
    {
        mint las = dp[j - 1][n + 1];
        int l = n + 1;
        for (int i = 1; i <= n; i++)
        {
            if (s[i][j] == '#')
            {
                l = i;
                break;
            }
        }
        for (int i = n + 1; i; i--)
        {
            las += dp[j - 1][i - 1];
            if (i <= l)
            {
                dp[j][i] = las;
            }
        }
    }
    cout << accumulate(dp[m] + 1, dp[m] + n + 2, mint(0)).val() << endl;
    return 0;
}

```

---

## 作者：Leaper_lyc (赞：0)

显然，一个位置为黑的，那么它往下的所有位置一定为黑，它往右下的所有位置一定为黑，即长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/4922md28.png)

为此，我们可以得出关于黑测块的高的性质：$h_{i+1}-1< h_i$。

设 $f_{i,j}$ 表示第 $i$ 行填了高度为 $j$ 的方案数。

根据 $h$ 的性质，不难得出转移方程：
$f_{i,j}={\sum_{k=0}^{j+1}}f_{i-1,k}$。

由于不能把黑色删去，所以枚举的时候直接从每列最高的黑点位置开始就行了。

这个可以前缀和优化，于是就做完了。

时间复杂度 $O(nm)$。

code:
```cpp
#include <bits/stdc++.h>
using namespace std;

const int _ = 2005;
const int mod = 998244353;

char a[_][_];
int n, m;
int h[_];
int f[_][_];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> (a[i] + 1); 
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (a[j][i] == '#') {
				h[i] = n - j + 1;
				break;
			}
	for (int i = 0; i <= n + 1; i++) f[0][i] = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = h[i]; j <= n; j++)
			f[i][j] = f[i - 1][j + 1];
		for (int j = h[i] + 1; j <= n + 1; j++)
			f[i][j] = (f[i][j] + f[i][j - 1]) % mod;
	}
	cout << f[m][n + 1];
}
```

---

## 作者：Xy_top (赞：0)

DP，很简单的 DP。

如果一个格子是黑的，那么它右下角的所有格子都是黑的。

对于行来考虑发现不太可行，此时对于列来考虑。

设 $f_{j,i}$ 为到第 $j$ 列，第 $i$ 列的第一个黑格子是第 $i$ 行时的方案数目。

前面一列第一个黑格子所在的行必须大于等于 $i-1$，不然此行第一个黑格子还要在更上面。

把这些加到 $f_{j,i}$ 上。

然后还有特殊情况就是前一列不填，此时要预处理一个 $s$，表示的是前面不填的方案总和，如果第 $j$ 列没有已经给了的黑格子，那么 $s \to s + \sum\limits_{i=1}^n f_{j,i}$，如果有任意一个已经给了的黑格子，$s$ 清零。（当前这一列不可能不填了）

最后输出的答案还要再加上 $s$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m, t, s;
char a[2005][2005];
int pre[2005];
int f[2005][2005];//第 j 列，垒到第 i 行的方案数
const int mod = 998244353;
void solve () {
	cin >> n >> m;
	f[0][n] = 1;
	For (i, 1, m) pre[i] = n + 1;
	For (i, 1, n) {
		For (j, 1, m) {
			cin >> a[i][j];
			if (a[i][j] == '#') pre[j] = min (pre[j], i);//i 上面都可以涂黑
		}
	}
	t = 1;
	For (j, 1, m) {
		For (i, 1, pre[j]) {
			if (i == n + 1) break;
			if (i >= 2) f[j][i] = f[j - 1][i - 1] - f[j - 1][i - 2];
			f[j][i] += (f[j - 1][n] - f[j - 1][i - 1]) % mod;
			f[j][i] += mod;
			f[j][i] %= mod;
			f[j][i] += s;
			f[j][i] %= mod;
		}
		if (pre[j] == n + 1) s += t;
		else s = 0;
		s %= mod;
		t = f[j][n];
		For (i, 1, n) f[j][i] += f[j][i - 1], f[j][i] %= mod;
	}
	cout << (f[m][n] + s) % mod;
}
signed main () {
	ios :: sync_with_stdio (false);
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：zhongpeilin (赞：0)

## 题目大意：
给你一个字符矩阵，其中有两种字符，一种是 `.` 另一种是 `#`，一个矩阵是漂亮的当且仅当对于每一个 $op_{i, j}$ 为 `#`，都有 $op_{i+1, j}$ 和 $op_{i+1,j+1}$ 都为 `#`，现在给你初始矩阵，你可以将任意的 `.` 变成 `#`，请问最后有多少种不同的漂亮的矩阵？$mod = 998244353$。

## 解题思路: 
首先分析一下他的要求，就是相当于说：如果第 $i$ 列有一个从下往上高度为 $j$ 的黑点，那么第 $i+1$ 列必须有一个高度为 $j-1$ 的黑点。且第 $i$ 列的黑点是从下往上是连续的一段。再分析一下会发现：如果已经确定了第 $i$ 列的黑点从下往上最高是 $j$，那么第 $i-1$ 列的黑点从下往上高度就会为 $1 \sim j + 1$。  
那么设 $dp_{i,j}$ 表示前 $i$ 列最后一列黑点高度为 $j$ 的方案数，会推这样一个式子：
$$ dp_{i, j} = \sum_{k = 1, k \leq j + 1}dp_{i - 1, k}$$
但是他是 $O(n^3)$ 的，所以可以用一个前缀和来优化掉这个 $O(n)$ 的转移，总时间复杂度：$O(n^2)$。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

int n, m, maxn[2005], sum[2005][2005];
char op[2005][2005];
int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> op[i][j];
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(op[i][j] == '#'){
				op[i + 1][j] = op[i + 1][j + 1] = '#';
				maxn[j] = max(maxn[j], n - i + 1); //这里因为他初始的时候还有#的点，所以在dp的时候要判一下j >= maxn[i]
			}
		}
	}
	for(int i = 0; i <= n + 1; i++) sum[0][i] = 1;
	
	for(int j = 1; j <= m; j++){//枚举列
		for(int i = maxn[j]; i <= n; i++){ //枚举最高黑点
			sum[j][i] = (sum[j][i - 1] + sum[j - 1][i + 1]) % mod;
		}
		sum[j][n + 1] = sum[j][n];
	}
	cout << sum[m][n] << endl;
	return 0;
}

---

