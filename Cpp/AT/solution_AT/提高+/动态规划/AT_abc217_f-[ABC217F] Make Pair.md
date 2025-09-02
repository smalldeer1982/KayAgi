# [ABC217F] Make Pair

## 题目描述

一共 $2N$ 个学生站成一排，其中有 $M$ 对朋友关系。老师每次从队列中挑出两个相邻的学生作为同桌。为了关系和睦，每次选出的两个学生必须是朋友关系。选出的两个学生离开队列，空出来的位置左右合拢。

请问老师有多少种方式选完所有学生？对于两种选人的方案，即使同桌关系相同，只要离开队列的顺序不同，也算是不同的方案。

## 样例 #1

### 输入

```
2 3
1 2
1 4
2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
2 2
1 2
3 4```

### 输出

```
2```

## 样例 #3

### 输入

```
2 2
1 3
2 4```

### 输出

```
0```

# 题解

## 作者：_zzzzzzy_ (赞：7)

# 思路

我们可以看出这是一道区间 DP，我们设 `dp[l][r]` 表示区间 $(l,r)$ 全部消掉所要的操作。

显然当 $(l,r)$ 的长度为奇数时 `dp[l][r]=0`，当 $l,r$ 相邻时可以合并时显然可以通过 `dp[l+1][r-1]` 转移过来。

接下来我们可以枚举一个 $K$，如果 $K$ 和右端点能够消掉的话就可以把区间分成两部分左端点到 $K$，剩下的是一部分。

如果不考虑两个区间之间的先后顺序，根据乘法原理我们可以知道是前面区间乘上后面区间的个数就可以了。

那么如果考虑枚举的顺序就相当于求 $(l,r)$ 的操作次数中选第一部分全部消除的操作次数。

那么最后可以推出方程为 $dp_{l,r}+=dp_{l,k-1}\times dp_{k+1,r-1}\times \begin{pmatrix}\frac{len}{2} \\ \frac{r-k+1}{2}\end{pmatrix}$。

最后记得我们说的当区间是偶数的时候才能够消除吗，在遍历的时候可以把长度和 $K$ 只枚举偶数。

最后的答案就是 `dp[1][2*n]`。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=450,mod=998244353;
map<pair<int,int>,bool>vis;
int dp[maxn][maxn],c[maxn][maxn];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if((x-y+1)%2==0){
			vis[{x,y}]=1;
			if(x+1==y||y+1==x){
				dp[x][y]=dp[y][x]=1;
			}
		}
	}
	for(int i=0;i<450;i++){
		for(int j=0;j<=i;j++){
			if(i==0)c[i][j]=1;
			else c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
		}
	}
	for(int len=2;len<=2*n;len+=2){
		for(int l=1;l+len-1<=2*n;l++){
			int r=l+len-1;
			if(vis[{l,r}])
				dp[l][r]=dp[l+1][r-1];
			for(int k=l+2;k<r;k+=2){
				if(vis[{k,r}]){
					dp[l][r]=(dp[l][r]+dp[l][k-1]*dp[k+1][r-1]%mod*c[len/2][(r-k+1)/2]%mod)%mod;
				}
			}
		}
	}
	cout<<dp[1][2*n];
	return 0;
}
```

---

## 作者：2020luke (赞：6)

# [[ABC217F] Make Pair](https://www.luogu.com.cn/problem/AT_abc217_f) 题解

## 思路解析

通过 $n \le 200$ 和 “选出的两个学生离开队列，空出来的位置左右合拢” 这两个细节可以想到能用区间 dp 做，$f_{i,j}$ 表示将 $i \to j$ 这个区间全部选完的方案数，然后常规区间 dp，加一个判断如果当前区间 $[l,r]$ 中 $l,r$ 是朋友，就可以从 $[l+1,r-1]$ 推过来，于是加上 $f_{l+1,r-1}$ 代表除去两个端点后的区间方案数。

接下来是重点，就是遍历每一个 $k$，然后统计 $f_{l,k}+f_{k+1,r}$，表示枚举每一个中间点，统计从该点切割开来的两半的贡献。如果对于这一点不太理解，建议去做 [P1063 [NOIP2006 提高组] 能量项链](https://www.luogu.com.cn/problem/P1063) 学习区间 dp。但是题目要求方案数，就很有可能出现判重，例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/e7iezov8.png)

这体现了一个区间 $[l,r]$ 的学生示意图，圆圈代表学生，连线代表他们是朋友关系，线上的数字用于区分标记。接下来有几种可能的 $k$ 的取值。

![](https://cdn.luogu.com.cn/upload/image_hosting/hjs85ga7.png)

这种情况下可能出现的方案有：【1，2，3，4】，【2，1，3，4】，【1，3，4，2】……

![](https://cdn.luogu.com.cn/upload/image_hosting/yun14vcv.png)

这种情况下的方案则和上一种情况一模一样，原因则是因为我们没有给 $k$ 的可能性做一个判断。可以想到我们的 $k$ 的取值一定会与端点有联系，于是在转移前判断 $k$ 是否与 $l$ 连接，这样就可以有效排除掉重复的方案，因为我们需要统计的根本是和 $l$ 联系的那一部分（例如我的例子中的 1 号朋友）加上和 $l$ 没联系的部分（例如我的例子中的2，3，4），这样就可以排除掉 $k$ 与当前 $l$ 无关的重复方案。

最后就是由于是算方案数，就说明区间 $[l,k]$ 和 $[k+1,r]$ 中每一种可能的方案在两段合并到一起后当前方案中的元素出现的相对顺序不会改变，例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/4sv4myju.png)

左边的 1，2，3 代表区间 $[l,k]$ 中的一种可行方案，右边的 a，b 代表区间 $[k+1,r]$ 中的一种可行方案，那么当两者合并后的可行方案的顺序就有可能是：

![](https://cdn.luogu.com.cn/upload/image_hosting/r1y22zeq.png)

这里不放出 a，b 是因为合并后原来一个方案中的相对顺序不会改变，画出横线是为了更好理解其实这就是一个在横线中填入相对顺序有序数字的一个问题，其实这个例子的方案数就是 $\mathrm{C}_5^3$，扩展到所有方案就是 $\mathrm{C}_{len/2}^{(k-l+1)/2}$。于是便在状态转移时乘上该式即可。

时间复杂度：三层区间 dp，每层最大都是 $n$，复杂度 $O(n^3)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
const ll mod = 998244353;
ll n, m, f[N][N], c[N][N];
bool frd[N][N];
int main() {
	cin >> n >> m;
	n *= 2ll;
	for(int i = 1, a, b; i <= m; i++) {
		cin >> a >> b;
		frd[a][b] = frd[b][a] = true;	//标记为朋友
	}
	for(int i = 1; i <= n; i++) f[i + 1][i] = 1;
	c[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i; j++) {
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;	//预处理组合数
		}
	}
	for(int i = 2; i <= n; i += 2) {
		for(int l = 1, r = l + i - 1; l + i - 1 <= n; l++, r++) {
			if(frd[l][r]) f[l][r] = f[l + 1][r - 1];	//小特判
			for(int k = l + 1; k <= r - 1; k += 2) {
				int l1 = (k - l + 1) / 2, l2 = (r - k) / 2;
				if(frd[l][k]) {	//去重的关键
					f[l][r] = (f[l][r] + ((f[l + 1][k - 1] * f[k + 1][r]) % mod * c[i / 2 + 1][l1 + 1]) % mod) % mod;	//注意要乘上组合数
				}
			}
		}
	}
	cout << f[1][n];
	return 0;
}
```

---

## 作者：BugGod (赞：6)

首先看到区间合并，脑补出区间 dp。定义 $dp_{p,q}$ 代表消掉 $[p,q]$ 的方案数。首先，如果枚举的 $p,q$ 两个端点都可以消掉，那么这个一定是要消掉的，不会节外生枝，那么 $dp_{p,q}=dp_{p+1,q-1}$（即除去两边的代价）。然后考虑枚举中间点 $k$，如果 $k$ 能和 $q$ 匹配，那么我们可以先消掉 $[p,k-1]$，然后消掉 $[k+1,q-1]$，最后消掉 $k$ 和 $q$，得到转移方程：$dp_{p,q}=dp_{p,q}+dp_{p,k-1}\times dp_{k+1,q-1}\times C_{\frac{len}{2}}^{\frac{q-k+1}{2}}$。

注意我们并不考虑消除顺序，所以是乘法（乘法原理）。为什么是 $C_{\frac{len}{2}}^{\frac{q-k+1}{2}}$ 呢？因为总共要消除 $\frac{len}{2}$ 对，其中消除 $[k,q]$ 的占了 $\frac{q-k+1}{2}$ 对，这些对可以以任何顺序消除，而前面的 $dp_{p,k-1}\times dp_{k+1,q-1}$ 只计算了每两种方案的组合，没有精细到每种方案具体消除的顺序，所以要乘上组合数。

注意 $len$ 和 $k$ 都一定是偶数。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void file(string file_name)
{
	freopen((file_name+".in").c_str(),"r",stdin);
	freopen((file_name+".out").c_str(),"w",stdout);
}
int n,m,dp[410][410],C[410][410];
map<pair<int,int>,bool>fl;//判断是否成对
const int modd=998244353;
signed main()
{
	//IOS();
	//file("");
	for(int i=0;i<=400;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(!i)C[i][j]=1;
			else C[i][j]=(C[i-1][j-1]+C[i-1][j])%modd;
		}
	}
	cin>>n>>m;
	for(int i=1,a,b;i<=m;i++)
	{
		cin>>a>>b;
		if((a-b+1)%2)continue;
		fl[mp(a,b)]=1;
		if(abs(a-b)==1)dp[a][b]=dp[b][a]=1;//相邻的可以预处理
	}
	for(int len=2;len<=(n<<1);len++)
	{
		for(int p=1;p+len-1<=(n<<1);p++)
		{
			int q=p+len-1;
			if(fl[mp(p,q)])dp[p][q]=dp[p+1][q-1];
			for(int k=p+2;k<q;k+=2)
			{
				if(fl[mp(k,q)])
				{
dp[p][q]=(dp[p][q]+dp[p][k-1]*dp[k+1][q-1]%modd*
C[len>>1][q-k+1>>1]%modd)%modd;
				}
			}
		}
	}
	cout<<dp[1][n<<1];
	return 0;
}
```

---

## 作者：CQ_Bab (赞：5)

# 思路
我们可以发现这一定是一个区间 Dp，那么我们定义 $f_{l,r}$ 为消掉 $l\sim r$ 的最小操作次数，那么我们就可以枚举一个区间长度以及左端点。然后我们如果枚举的左右端点可以消掉，那么 $f_{a,b}=f_{a+1,b-1}$ 即将中间消掉的代价。

然后我们可以枚举一个中间点 $k$，如果它能和 $b$ 匹配上，即可使用和上面一样的方法，然后再将 $f_{a,k-1}$ 的方案数乘上，最后因为要求的是方案数所以可以调换顺序，那么再乘上一个 $\tbinom{l\div 2}{(k-b+1)\div 2}$ 即可。

注意这里的 $l$ 和 $k$ 必须是偶数。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n,m;
const int N=501;
int mp[N][N];
int f[N][N];
int c[455][455];
const int mod=998244353;
fire main() {
	cin>>n>>m;
	rep(i,1,m) {
		int a,b;
		cin>>a>>b;
		if((a-b+1)%2==0) {
			mp[a][b]=1;
			if(a+1==b||b+1==a) f[a][b]=f[b][a]=1;
		}
	}
	rep(i,0,450-1) {
		rep(j,0,i) {
			if(!i) c[i][j]=1;
			else c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
		}
	}
	rep(l,2,2*n) {
		rep(a,1,2*n+1-l) {
			int b=a+l-1;
			if(mp[a][b]) f[a][b]=f[a+1][b-1];
			rep(k,a+2,b-1) {
				if(mp[k][b]) {
					f[a][b]=(f[a][b]+f[a][k-1]*f[k+1][b-1]%mod*c[l/2][(b-k+1)/2]%mod)%mod;
				}else if(mp[a][k]) f[a][b]=(f[a][b]+f[a+1][k-1]*f[k+1][b]%mod*c[l/2][(k-a+1)/2]%mod)%mod;
				k+=1;
			}
		}
		l++;
	}
	cout<<f[1][2*n]<<endl;
	return false;
}

```

---

## 作者：myyyIisq2R (赞：4)

### 讲得比较细，应该比较好懂。

首先看到区间问题，且大区间可以由小区间汇总，想到区间 dp。

状态就设 `f[l][r]` 表示消除掉区间 $[l,r]$ 的情况数。考虑到消除的数必须两两配对，则 $[l,r]$ 的长度必须为偶数。

接下来思考怎么转移。那么我们来枚举断点 $k$，这个区间能被分成 $[l,k-1],[k],[k+1,r-1],[r]$ 四部分，其中我们钦定 $[l,k-1]$ 和 $[k+1,r-1]$ 能够被消除，然后 $k$ 和 $r$ 上的数在拼到一起后能够被消除。那么这个时候我们就需要保证:

1. $[l,r],[l,k-1]$ 和 $[k+1,r-1]$ 的区间长度均为偶数。
2. $k$ 和 $r$ 是在给出的 $m$ 个关系之中的。

### 现在考虑几种特殊情况
1. 当 $[l,k-1]$ 为空（即 $l=k$）时，区间中仅剩 $[k],[k+1,r-1],[r]$ 三部分，既然已经钦定 $[k+1,r-1]$ 、 $k$ 和 $r$ 上的数在拼到一起后能够分别被消除，那么 $[l,r]$ 的方案数直接与 $[l+1,r-1]$ 的方案数相等，$l$ 与 $r$ 匹配时继承即可。
2. 当 $[k+1,r-1]$ 为空（即 $k=r-1$）时，直接计算 $[k+1,r-1]$ 会存在区间左端点大于右端点的情况，又有区间长度为 $1$ 且可消除，那么我们就可以特判，即当 $i$ 与 $i+1$ 可消除时，使 $f[i][i+1]=f[i+1][i]=1$。

### 接下来考虑取值范围
从第一个保证点且我们特判了第一种特殊情况，所以就不用考虑 $[l,k-1]$ 为空了，那么其长度至少为偶数 $2$，则我们可以推出，$r \ge l+1$，$k \ge l+2$。又因为我们避免了 $[k+1,r-1]$ 为空时的越界情况，所以 $k=r-1$ 可成立，即 $k < r$。

综上，$l+2 \le k < r$。

### 接下来是转移方程
首先，$[l,k-1],[k],[k+1,r-1],[r]$ 中，$[l,k-1]$ 和 $[k+1,r-1]$ 的方案已经计算过了，对 $[l,r]$ 的贡献用乘法原理直接相乘。

其次，这两个区间的方案分别有序，但是组合起来就有多种顺序了。我们想到把一个有序的序列往另一个有序的序列里插，序列长度分别为 $a$ 和 $b$，插法排列数为 $\begin{pmatrix}    a+b  \\    a   \end{pmatrix} $。那么同理，我们把整个区间直接看作 $[l,k-1]$ 和 $[k,r]$（因为 $[k],[k+1,r-1],[r]$ 可合并），其可消除的组对数分别为其长度的一半，排列数为 $\begin{pmatrix}    \frac{r-l+1}{2}   \\    \frac{r-k+1}{2}    \end{pmatrix} $。

### 综上，得到转移方程

若 $i$ 与 $j$ 匹配，有 $f[i][j] = f[i+1][j-1]$。

一般的，$f[i][j] = f[i][j] +  f[i][k-1] \times  f[k+1][j-1] \times \begin{pmatrix}    \frac{r-l+1}{2}   \\    \frac{r-k+1}{2}   \end{pmatrix} $

### Code
```cpp
int n,m;
n = read(),m = read();
for(int i{1};i<=m;i++)
{
  int u = read(),v = read();
  if((u-v+1)%2) continue;
  if(v-u==1) f[u][v] = f[v][u] = 1; //特判特殊情况2
  vis[u][v] = vis[v][u] = true;  //判断是否可消除
}
n<<=1;
for(int len{2};len<=n;len+=2)
{
  for(int i{1};i+len-1<=n;i++)	
  {
    int j = i+len-1;
    if(vis[i][j]) f[i][j] = f[i+1][j-1]; 
    for(int k{i+2};k<j;k+=2)
    {
      //min k: i k-1 k
      //i k-1   k   k+1 j-1  j
      if(!vis[k][j]) continue;
      f[i][j] = (f[i][j] + (f[i][k-1] * f[k+1][j-1] % MOD * C(len>>1,(j-k+1)>>1))%MOD)%MOD;
    }
  }
}
writeln(f[1][n]);
return 0;
```

---

## 作者：daniEl_lElE (赞：4)

## 思路

将原题意思改变为括号匹配，要求每一组括号均为给出中的一个。

使用类似题目的经典思路，考虑 $dp_{i,j,0/1}$ 分别表示 $i\sim j$ 区间已被消除，目前组成的是一个/多个括号区间拼在一起的有序方案数。

考虑转移，分为两类，一种是在目前的两边加上括号，由于这两个是在合并内部以后才可以进行的操作，故不会改变有序方案数。

第二类是合并两个括号区间，先枚举中点，为了避免重复强制一段是单独的括号区间。在这种情况中，两段是并列关系存在的，于是当前一段有 $x$ 组，后一段有 $y$ 组时，应该乘上系数 $\dbinom{x+y}{y}$。

复杂度 $\Theta(n^3)$，可以通过。、

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int ok[405][405];
int dp[405][405][2];
int C[405][405];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	for(int i=0;i<=400;i++) C[i][0]=1;
	for(int i=1;i<=400;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		ok[a][b]=1;
	}
	for(int i=1;i<n*2;i++) if(ok[i][i+1]) dp[i][i+1][0]=1;
	for(int len=2;len<=n*2;len+=2){
		for(int l=1,r=len;r<=n*2;l++,r++){
			if(ok[l][r]) dp[l][r][0]=(dp[l][r][0]+dp[l+1][r-1][0]+dp[l+1][r-1][1])%mod;
			for(int k=l+1;k<r;k+=2){
				dp[l][r][1]=(dp[l][r][1]+(dp[l][k][0]+dp[l][k][1])*dp[k+1][r][0]%mod*C[(r-l+1)/2][(k-l+1)/2]%mod)%mod;
			} 
		}
	}
	cout<<(dp[1][2*n][0]+dp[1][2*n][1])%mod;
	return 0;
}
```

---

## 作者：zrl123456 (赞：3)

[题目](https://www.luogu.com.cn/problem/AT_abc217_f)  
考察：区间 dp，组合数。  
### 状态与边界条件：
我们设 $[l,r]$ 区间的方案数用 $f_{l,r}$ 表示（$1\le l,r\le 2n$），那么边界条件就是一个空序列的方案数（即 $f_{i+1,i}$）的方案数便是 $1$。  
### 转移方程：
对于每一个 $f_{l,r}$，若 $l$ 与 $r$ 为朋友关系（我们记作 $vis_{l,r}=1$），那我们就需要先加上 $f_{l+1,r-1}$。  
接下来我们需要找到一个点（同学）$k$，把区间 $[l,r]$ 分成两部分，即区间 $[l,k-1]$ 和 $[k,r]$，然后再将区间 $[k,r]$ 分成 $k$ 点，$[k+1,r-1]$ 区间和 $r$ 点，若 $vis_{k,r}=1$，则我们需要加上一个数。  
就是下面这张图（paint 画图有点丑）：  
![](https://cdn.luogu.com.cn/upload/image_hosting/f75ypiqy.png)  
若只是将 $f_{l,k-1}$ 与 $f_{k,r}$ 相乘，则无法满足题目中**对于两种选人的方案，即使同桌关系相同，只要离开队列的顺序不同，也算是不同的方案**的条件，那么我们来分析一下：  
对于整个 $[l,r]$ 区间需要选 $\frac{r-l+1}{2}$ 次，$[k,r]$ 区间需要选 $\frac{r-k+1}{2}$，那么我们需要在 $\frac{r-l+1}{2}$ 次中选 $\frac{r-k+1}{2}$ 次，这就是组合数，也就是说这一次的答案是 $f_{l,k-1}f_{k+1,r-1}C_{\frac{r-k+1}{2}}^{\frac{r-l+1}{2}}$，我们需要提前维护好任意的 $C_{i,j}$（$0\le j\le i\le 2n$）。  
那么我们得到最后的转移方程：  
$$f_{l,r}=vis_{l,r}f_{l+1,r-1}+\sum_{k=l+2}^{r-1}vis_{k,r}f_{l,k-1}f_{k+1,r-1}C_{\frac{r-k+1}{2}}^{\frac{r-l+1}{2}}$$
当然，我们得保证 $r-l+1$，$r-k+1$，$k-l$ 均为偶数。  
代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define inl inline
#define reg register
#define INF 214748364721474836
using namespace std;
inl int read(){
	int f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
inl void write(int x){
	if(x<0){
		x=-x;
		putchar('-');
	}
	if(x>=10) write(x/10);
	putchar(x%10^48);
}
#define MOD 998244353
#define N 405
int n,m,u,v,f[N][N],c[N][N];
bool vis[N][N];
signed main(){
	n=read()<<1;
	m=read();
	for(int i=1;i<=m;++i){
		u=read();
		v=read();
		if((u^v)&1) vis[u][v]=vis[v][u]=true;
	}
	for(int i=0;i<=n;++i) f[i+1][i]=1;
	for(int i=0;i<=n;++i)
		for(int j=0;j<=i;++j) 
			if(j==0) c[i][j]=1;
			else c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	for(int len=2;len<=n;len+=2)
		for(int l=1;l+len-1<=n;++l){
			int r=l+len-1;
			if(vis[l][r]) f[l][r]=f[l+1][r-1];
			for(int k=l+2;k<r;k+=2)
				if(vis[k][r]) f[l][r]=(f[l][r]+(f[l][k-1]*f[k+1][r-1]%MOD)*c[len>>1][(r-k+1)>>1]%MOD)%MOD;
		}
	write(f[1][n]%MOD);
	return 0;
}
```

---

## 作者：A_Step_Back (赞：2)

难度适中的区间 dp。~~F 题真的有这么简单吗~~

# 思路解析

可以这么想：在 $dp_{l,r}$ 中，假如第 $l$ 个同学和第 $x$ 个同学是好朋友 $( l < x \le r )$，那么我们可以把 $l$ 和 $x$ 中间的同学安排好，记为 $A$ 任务，再把 $x$ 和 $r$ 中间的同学安排了，记为 $B$ 任务。

接着，我们发现 $A$，$B$ 两个任务是同时进行的且互不影响的，接着就是一个排列组合，也就是在总步数里选 $A$ 的步数个操作是用于完成 $A$ 的，所以有 $C_{(j-i+1) \div 2}^{(j-k) \div 2}$ 种情况。

最后，一句话：注意细节。注意取模，还有题目中有 $2n$ 个同学，而不是 $n$ 个。

# 双手奉上AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
int n,m;
long long dp[405][405],c[205][205];
bool fri[405][405];
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int u,v;
		scanf("%d%d",&u,&v);
		fri[u][v]=1,fri[v][u]=1;
	}
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;//这里也要取模的（前车之鉴
		}
	}
	for(int i=1;i<2*n;i++){
		if(fri[i][i+1])dp[i][i+1]=1;
	}
	for(int i=2;i<=2*n;i++){
		for(int j=1;j<i;j++){
			dp[i][j]=1;
		}
	}
	for(int l=3;l<2*n;l+=2){
		for(int i=1;i+l<=2*n;i++){
			int j=i+l;
			if(fri[i][j])dp[i][j]=dp[i+1][j-1];
			for(int k=i+1;k<j;k+=2){
				if(fri[i][k]){
					dp[i][j]=(dp[i][j]+dp[i+1][k-1]*dp[k+1][j]%mod*c[(j-i+1)/2][(j-k)/2]%mod)%mod;//这行写起来要谨慎
				} 
			}
		}
	}
	printf("%d",dp[1][2*n]);
	return 0;
}
```

谢谢大家！

---

## 作者：Fracture_Dream (赞：2)

#### F - Make Pair

小清新的区间 `dp` 题。

相邻删除这样的操作就应该往区间 `dp` 上去想。

定义 $f(i, j)$ 表示将区间 $[i, j]$ 匹配完的方案数，显然需要满足 $2 \mid r - l + 1$。

可得：

$$f(i, j) = \sum_{k \in (l, r], 2 | k - i + 1} f(i + 1, k) \times f(k + 1, j) \times \binom{\frac {j - i + 1} {2}}{\frac {j - k + 1} {2}}$$

其中 $k$ 同学和 $i$ 同学关系友好，且对于任意 $i$，若 $0 \leq i \leq n$，有 $f(i, i + 1) = 1$。

其中组合数可以理解为我们共有 $\frac {j - i + 1} {2}$ 个盒子（盒子间被认为是不同的），且我们有 $\frac {k - i - 1} {2}$ 个 $a$ 球，$1$ 个 $b$ 球，和 $\frac {j - k} {2}$ 个 $c$ 球（同种类的球被认为是相同的，这是因为在上面的转移柿子中我们已经考虑了球种类内部的情况），且 $b$ 球放入的盒子编号必须大于任意一个 $a$ 球放入的盒子编号。

感性理解一下其实就是我们在所有的盒子中选 $\frac {j - k} {2}$ 个出来放 $c$ 球。

时间复杂度 $O(n^3)$。


```cpp
#include <cstdio>

typedef long long LL;
int Max(int x, int y) { return x > y ? x : y; }
int Min(int x, int y) { return x < y ? x : y; }
int Abs(int x) { return x < 0 ? -x : x; }

int read() {
    int x = 0, k = 1;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar();
    }
    while ('0' <= s && s <= '9') {
        x = (x << 3) + (x << 1) + (s - '0');
        s = getchar();
    }
    return x * k;
}

void write(LL x) {
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void print(LL x, char s) {
    write(x);
    putchar(s);
}

const int MAXN = 4e2 + 5;
const int mod = 998244353;

bool w[MAXN][MAXN]; 
LL q[MAXN], sq[MAXN], dp[MAXN][MAXN];
 
LL A (int x, int y) { return q[x] * sq[x - y] % mod;}
 
LL C (int x, int y) { return A(x, y) * sq[y] % mod;}
 
LL Quick_Pow(LL a, LL b) {
	LL res = 1;
	while(b) {
		if(b & 1)
			res = res * a % mod;
		a = a * a % mod;
		b >>= 1;		
	}
	return res % mod;
}

int main() {
	int n = read(), m = read();
	q[0] = 1, sq[0] = 1;
	for(int i = 1; i <= (n << 1); i++) {
		q[i] = q[i - 1] * i % mod;
		sq[i] = Quick_Pow(q[i], mod - 2);
	}
	for(int i = 1, a, b; i <= m; i++) {
		a = read(), b = read();
		w[a][b] = w[b][a] = true;
	}
	for(int i = 1; i <= (n << 1) + 1; i++)
		dp[i][i - 1] = 1;
	for(int len = 2; len <= (n << 1); len += 2) 
		for(int l = 1; l + len - 1 <= (n << 1); l++) {
			int r = l + len - 1;
			for(int k = l + 1; k <= r; k += 2)
				if(w[l][k])
					dp[l][r] = (dp[l][r] + dp[l + 1][k - 1] * dp[k + 1][r] % mod * C(len / 2, (r - k + 1) / 2) % mod) % mod;
		}
	print(dp[1][n << 1], '\n');
	return 0;
}
```


---

## 作者：ZBH_123 (赞：1)

## 思路分析
### 1.状态设计与设置边界
我们可以设 $f_{l,r}$ 为区间 $[l,r]$ 全部配对成同桌的方案数。显然，在 $r-l+1$ 为奇数的情况下，这 $r-l+1$ 个人中总会有一个人没有同桌，所以在这种情况下，$f_{l,r}=0$。现在来考虑其他的情况。由于本题是一道区间 dp，所以我们要从区间长度短的区间入手。长度最短的区间就是相邻的两个人。当他们具有朋友关系时，将他们配对成同桌的方案数自然就是 $1$。而最终答案就是 $dp_{1,2 \times n}$。
### 2.状态转移方程
既然是一道区间 dp，那最外层循环肯定就是枚举区间长度 $len$，中间的循环枚举左端点 $l$，再根据 $l$ 和 $len$ 算出右端点 $r$，最内层就枚举中间点 $k$。知道 $l$，$r$ 和 $k$，如何得到 $dp_{l,r}$ 呢？这里我们可以让中间点 $k$ 和 $r$ 是朋友关系，这样的话，我们就可以把区间 $[l,r]$ 拆分成两部分，一部分是 $[l,k-1]$，另一部分是 $[k,r]$。左边部分的方案数就是 $dp_{l,k-1}$，右边部分的方案数就是 $dp_{k+1,r-1}$，因为 $k$ 和 $r$ 是需要配对成一对同桌的。但是光把 $dp_{l,k-1}$ 和 $dp_{k+1,r-1}$ 相乘是不对的。因为题目中有这样一句话：**对于两种选人的方案，即使同桌关系相同，只要离开队列的顺序不同，也算是不同的方案。** 也就是说，在 $dp_{l,k-1} \times dp_{k+1,r-1}$ 的基础之上，我们还要再乘 $C_{len \div 2}^{(r-k+1) \div 2}$，因为顺序不同，方案不同，所以我们还要在 $len \div 2$ 对朋友中挑选出 $(r-k+1) \div 2$ 对朋友到右边去。所以，我们就可以得到状态转移方程：
$$dp_{l,r}=\sum_{k=l+2}^{r-1} dp_{l,k-1} \times dp_{k+1,r-1} \times C_{len \div 2}^{(r-k+1) \div 2}$$
### 3.代码实现
由于只有区间长度为偶数的区间才能全部配对成同桌，所以如果一对朋友的两个人中间间隔了奇数个人，那这对朋友就对答案产生不了贡献了。$k$ 从 $l+2$ 到 $r-1$ 进行枚举也是这个原因。另外，$C_{len \div 2}^{(r-k+1) \div 2}$ 显然可以通过下面这个关系预处理出来：
$$C_{n}^{m}=\begin{cases} 1 & m=0,n \\ C_{n-1}^{m-1}+C_{n-1}^{m} & 1 \le m \lt n \end{cases}$$
**AC code：**
```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int mod=998244353;
int n,m,x,y;
long long dp[405][405],C[405][405];
bool vis[405][405];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		if((y-x+1)%2==0){
			vis[x][y]=true;
			if(x+1==y||y+1==x){
				dp[x][y]=dp[y][x]=1;
			}
		}
	}
	for(int i=0;i<=n;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	for(int len=2;len<=2*n;len+=2){
		for(int l=1;l+len-1<=2*n;l++){
			int r=l+len-1;
			if(vis[l][r]){
				dp[l][r]=dp[l+1][r-1];
			}
			for(int k=l+2;k<r;k+=2){
				if(vis[k][r]){
					dp[l][r]=(dp[l][r]+dp[l][k-1]*dp[k+1][r-1]%mod*C[len/2][(r-k+1)/2]%mod)%mod;
				}
			}
		}
	}
	cout<<dp[1][2*n];
	return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

其实这个题可能有一小点难！我不好评价。

明显要考虑区间 dp，设 $dp_{l,r}$ 为消除区间 $[l,r]$ 的方案数。第一种转移显然是先消除 $[l+1,r-1]$，留下 $(l,r)$ 并消除，这种情况要求 $(l,r)$ 可消除。

第二种转移就是套路地考虑枚举分割点，两边分别解决。那么可以得到 $dp_{l,r}\leftarrow dp_{l,k}\times dp_{k+1,r}\times \binom{(r-l+1)/2}{(k-l+1)/2}$，其中组合数表示两边操作交错进行的方案数。

但是你发现这显然是错的，因为对于分成三段以上的情况会被重复算。这也很好解决：我们强制钦定一段是极长的即可。比如现在规定最右边的段是极长的，那么对于 $[k+1,r]$ 这段，需要满足 $(k+1,r)$ 可消除，这时候的贡献为 $dp_{l,k}\times dp_{k+2,r-1}\times \binom{(r-l+1)/2}{(k-l+1)/2}$。

时间复杂度 $\mathcal O(n^3)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=409,Mod=998244353;
ll n,m,a[N*N],b[N*N],dp[N][N],e[N][N],C[N][N];
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read()*2,m=read();
    rep(i,1,m){
        a[i]=read(),b[i]=read();
        if((a[i]-b[i]+1)&1)continue;
        e[a[i]][b[i]]=e[b[i]][a[i]]=1;
    }
    rep(i,0,n+1){
        C[i][0]=1;
        rep(j,1,i)C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
    }
    rep(i,1,n-1)dp[i][i+1]=e[i][i+1],dp[i+1][i]=e[i+1][i];
    rep(len,2,n){
        if(len&1)continue;
        rep(l,1,n-len+1){
            ll r=l+len-1;
            dp[l][r]=e[l][r]*dp[l+1][r-1];
            rep(k,l+2,r-1){
                if((k-l)&1)continue;
                if(!e[k][r])continue;
                dp[l][r]=(dp[l][r]+dp[l][k-1]*dp[k+1][r-1]%Mod*C[len/2][(r-k+1)/2])%Mod;
            }
        }
    }
    write(dp[1][n]);
    return 0;
}
```

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/abc217f-make-pair-de-ti-jie/)
# 题目大意
一共 $2N$ 个学生站成一排，其中有 $M$ 对朋友关系。老师每次从队列中挑出两个相邻的学生作为同桌。为了关系和睦，每次选出的两个学生必须是朋友关系。选出的两个学生离开队列，空出来的位置左右合拢。

请问老师有多少种方式选完所有学生？对于两种选人的方案，即使同桌关系相同，只要离开队列的顺序不同，也算是不同的方案，其中 $1\le n\le 200$。

# 思路
定义 $f_{l,r}$ 表示将区间 $[l,r]$ 全部消除的方案数。

考虑 $r$ 与上一个区间的哪一个数配对：

- 如果 $l,r$ 组合在一起，那么首先因该消除区间 $[l+1,r-1]$，转移方程为 $f_{l,r}=f_{l+1,r-1}$。

- 如果 $k,r$ 组合在一起，那么将这个大区间拆分为两个小区间 $[l,k-1]$ 和 $[k+1,r]$。因为两个区间是相对独立的，两个物件互不影响。那么如果左侧有 $x$ 种方案，右侧有 $y$ 种方案，那么总方案为 $x\times y \times C_{\frac{r-l+1}{2}}^{\frac{r-k+1}{2}}$。

# AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=405,mod=998244353;
int n,m,inv[N],jc[N],f[N][N];
bool a[N][N];
int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }return ans;
}
void init(){
    inv[0]=jc[0]=1;
    for(int i=1;i<N;i++){
        jc[i]=(jc[i-1]*i)%mod;
        inv[i]=ksm(jc[i],mod-2);
    }
}
int c(int n,int m){
    return ((jc[n]*inv[m])%mod*inv[n-m])%mod;
}
signed main(){
    init();
    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y;
        a[x][y]=a[y][x]=1;
        if(abs(x-y)==1) f[x][y]=f[y][x]=1;
    }
    n*=2;
    for(int len=3;len<n;len+=2){
        for(int l=1;l+len<=n;l++){
            int r=l+len;
            if(a[l][r]) f[l][r]=f[l+1][r-1];
            for(int k=l+2;k<r;k+=2){
                if(a[k][r]) f[l][r]=(f[l][r]+(f[l][k-1]*f[k+1][r-1])%mod*c(len/2+1,(r-k+1)/2))%mod;
            }
        }
    }
    cout<<f[1][n];
    return 0;
}
```

---

## 作者：apiad (赞：0)

开始上难度，有意思的一题。感觉，和 23 年提高组消消乐有那么一点像，就是区间 Dp，类似括号匹配。但是这种题容易算重，所以我们需要保证每次转移都添加元素。对于一个区间 $[l,r]$，我们可以从 $[l+1,x-1]$ 和 $[x+1,r]$ 转移来，保证每次 $l$ 与 $x$ 是可以匹配，然后消除。$x$ 是区间 Dp 中断点。然后还需要乘一个组合数，那就是 $C_{\tfrac{x-l-1}{2}+1+\tfrac{r-x}{2}}^{\tfrac{r-x}{2}}$。就是你选择这两段拼接起来的先后顺序。

于是，如果 $l$ 与 $x$ 匹配，那么可以得到转移：$dp_{l,r} = dp_{l+1,x-1} \times dp_{x+1,r} \times C_{\tfrac{x-l-1}{2}+1+\tfrac{r-x}{2}}^{\tfrac{r-x}{2}}$。结束。[link](https://atcoder.jp/contests/abc217/submissions/50742813)。

---

## 作者：Minuswy (赞：0)

当时被卡了有点久的。vp 结束后一分钟调出来了。。

首先很容易发现是一个区间 dp。$dp_{l,r}$ 表示选 $[l,r]$ 的人有几种方案。考虑怎么转移。有两种情况。

第一种是 $l,r$ 被连接，$dp_{l,r}=dp_{l+1,r-1}$。想到边界情况，当 $l=r-1$ 的时候 $[l+1,r-1]$ 就是一个不合法的区间。所以要先把 $l,r$ 能连接且 $l=r-1$ 的 $dp_{l,r}$ 先设为 $1$。

还有一种是两个区间被拼接起来。这里我刚开始想了好久怎么处理。如果只是单纯枚举断点的话，就可能有方案被重复算，就比如说 `([ ][ ])[ ] 和 [ ]([ ][ ])` 同一种情况就会被算两次。

那该怎么办呢，可以想到枚举右端点 $r$ 能连接的位置，相当于就是枚举最右边的一个完整的块。那么不算顺序的转移方程就写成 $dp_{l,r}=\sum_{i=[l,r],link_{i,j}=1} dp_{l,i-1}\times dp_{i+1,r-1}$。这里的 $link_{i,j}$ 表示 $i,j$ 被连接。

同时题目说按不同的顺序选是不同的方案，我们刚才列的式子是没算顺序的。这里乘的系数我也卡了好久。首先 $[l,r]$ 中一共有 $\frac{r-l+1}{2}$ 个点对，$[i,r]$ 中有 $\frac{r-i+1}{2}$ 个点对。相当于是在这  $\frac{r-l+1}{2}$ 个位置中，选出 $\frac{r-i+1}{2}$ 个来塞右边块的点对，把这些位置填上一共有 $dp_{i+1,r-1}$ 种方案；剩下的那些位置就用来填左边的块，把这些位置填上一共有 $dp_{l,i-1}$ 种方案。

$$dp_{l,r}=\sum_{i=[l,r],link_{i,j}=1} dp_{l,i-1}\times dp_{i+1,r-1}\times \binom{\frac{r-l+1}{2}}{\frac{r-i+1}{2}}$$

再看看边界的情况。当 $i=r-1$ 时，$[i+1,r-1]$ 是 左端点大于右端点的区间，本来应该算上贡献的，但此时 $dp_{i+1,r-1}=0$ 没有贡献，所以要特判。

然后我们可以发现 $r-l+1$ 也就是块长为奇数时是无解的。因为两两配对，不管怎么配都会多出来一个。小优化吧，算是。

代码：[https://atcoder.jp/contests/abc217/submissions/46913817](https://atcoder.jp/contests/abc217/submissions/46913817)

---

## 作者：slzx2022YuYihan (赞：0)

## [AT_abc217_f	[ABC217F] Make Pair](https://www.luogu.com.cn/problem/AT_abc217_f)

# Solution

口胡一分钟，调试一小时，只想送毒瘤二字。

显然地令 ``dp[l][r]`` 表示 $l$ 到 $r$ 的这段区间合并的方案数。如果 $l$ 和 $r$ 为好朋友，那么 ``dp[l][r]=dp[l+1][r-1]``。然后枚举 $l+2$ 到 $r-1$ 之间的断点 $k$，那么 ``dp[l][r]+=dp[l][k-1]*dp[k+1][r-1]*C[(r-l+1)/2][(r-k+1)/2]``，其中 $C$ 表示组合数。

注意到 $k+1$ 有可能大于 $r-1$，因此 ``dp[i][i-1]=1``（就因为这个 WA 了好几次）。合并的长度必须是偶数。

在调试的过程中，我也看了其他几位大佬的题解，看他们如何处理细节，在这里特别感谢他们！

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>inline void read(T& x){
    x = 0; T w = 1; char ch = getchar();
    while (!isdigit(ch)){if (ch == '-')	w = -1; ch = getchar();}
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x *= w;
}
template<typename T>inline void write(T x){
    if (x < 0)	putchar('-'), x = ~(x - 1);
    if (x > 9)	write(x / 10);
    putchar(x % 10 ^ 48);
}

const ll mo = 998244353;

const int N = 405;

int n, m;
bool pd[N][N];
ll dp[N][N];

ll C[N][N];

int main(){
    //ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    read(n), read(m), n <<= 1;
    while (m--){
        int a, b;
        read(a), read(b);
        if (!((b - a + 1) & 1)) pd[a][b] = pd[b][a] = true;
    }
    for (register int i = 0; i <= n; ++i)
        for (register int j = 0; j <= i; ++j)
            if (!i) C[i][j] = 1;
            else    C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mo;
    for (register int len = 2; len <= n; len += 2)
        for (register int l = 1, r = l + len - 1; r <= n; ++l, ++r){
            if (len == 2){
                if (pd[l][r])   dp[l][r] = dp[r][l] = 1;
                continue;
            }
            if (pd[l][r])   dp[l][r] = dp[l + 1][r - 1];
            for (register int k = l + 2; k < r; k += 2)
                if (pd[k][r])   dp[l][r] += dp[l][k - 1] * dp[k + 1][r - 1] % mo * C[len >> 1][(r - k + 1) >> 1] % mo, dp[l][r] %= mo;
        }
    return write(dp[1][n]), putchar('\n'), 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

区间 DP 好题，合并的时候十分毒瘤。

首先，定义 $dp_{i,j}$ 表示合并 $[i,j]$ 区间不同的方案的数量。不难发现，如果区间长度为奇数（即 $j - i + 1$ 为奇数），一定无法合并。

然后，如果 $i,j$ 是朋友关系，有 $dp_{i, j} = dp_{i + 1,j - 1}$。

接着，我们可以枚举一个中间点 $k$，如果 $k,j$ 是朋友关系，那么，区间被分为了 $[i,k),[k,j]$ 两个区间，易得（还要乘一个组合数是因为还要考虑交换顺序所带来的不同方案数）：

$$
dp_{i,j} \leftarrow dp_{i,j} + dp_{i,k - 1} \times dp_{k,j} \times C_{\frac{j - i + 1}{2}}^{\frac{r - k +1 }{2}}
$$

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 510,mod = 998244353;
int n,m;
int C[N][N],dp[N][N];
bool vis[N][N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read() << 1;
	m = read();
	for (re int i = 1;i <= m;i++){
		int a,b;
		a = read();
		b = read();
		if (!((b - a + 1) & 1)){//长度为偶数才有可能合并 
			vis[a][b] = vis[b][a] = true;
			if (a == b + 1 || a + 1 == b) dp[a][b] = dp[b][a] = 1;
		}
	}
	for (re int i = 0;i <= n;i++){//预处理组合数 
		for (re int j = 0;j <= i;j++){
			if (!i) C[i][j] = 1;
			else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
		}
	}
	for (re int l = 2;l <= n;l += 2){//只枚举偶数 
		for (re int i = 1;i + l - 1<= n;i++){
			int j = i + l - 1;
			if (vis[i][j]) dp[i][j] = dp[i + 1][j - 1];//i,j 是朋友关系 
			for (re int k = i + 2;k < j;k += 2){//只枚举长度为偶数的情况 
				if (vis[k][j]) dp[i][j] = (dp[i][j] + dp[i][k - 1] * dp[k + 1][j - 1] % mod * C[l / 2][(j - k + 1) / 2] % mod) % mod;
			}
		}
	}
	printf("%lld",dp[1][n]);
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

计数型区间 DP。枚举分界点 $k$ 时要确保 $l,k$ 是朋友关系。先消去区间 $[l+1, k-1]$，然后 $l,k$ 就相邻了。

本题中的顺序不同也算作方案不同，因此 $[l,k]$ 与 $[k+1,r]$ 中抽出的朋友对要确定顺序的“穿插”关系。设区间 $[l,r]$ 长度为 $L_1$，区间 $[l,k]$ 长度为 $L_2$，穿插方案数为 $(^{L_1/2}_{L_2/2})$。

注意枚举的所有区间长度都是偶数。

```cpp
// Title:  Make Pair
// Source: ABC217F
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=405, mod=998244353;
using namespace std;

int n, m; bool st[N][N]; ll C[N][N], f[N][N];

int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	scanf("%d%d", &n, &m); n+=n;
	rep(i, 1, m)
	{
		int x, y; scanf("%d%d", &x, &y);
		st[x][y]=1;
	}
	rep(i, 0, n)
	{
		C[i][0]=1;
		rep(j, 1, i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	rep(i, 1, n) f[i+1][i]=1;
	for(int len=2; len<=n; len+=2)
	{
		rep(l, 1, n)
		{
			int r=l+len-1;
			if(st[l][r]) f[l][r]=f[l+1][r-1];
			rep(k, l+1, r-1) if(st[l][k])
				f[l][r]=(f[l][r]+f[l+1][k-1]*f[k+1][r]%mod*C[len/2][(k-l+1)/2]%mod)%mod;
		}
	}
	printf("%lld", f[1][n]);
	
	return 0;
}
```

---

