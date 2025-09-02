# [ARC153D] Sum of Sum of Digits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc153/tasks/arc153_d

正整数 $ x $ に対し，その各桁の和を $ f(x) $ と表すことにします．例えば $ f(153)\ =\ 1\ +\ 5\ +\ 3\ =\ 9 $，$ f(2023)\ =\ 2\ +\ 0\ +\ 2\ +\ 3\ =\ 7 $，$ f(1)\ =\ 1 $ です．

正整数列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ が与えられます．$ x $ を非負整数とするとき，$ \sum_{i=1}^N\ f(A_i\ +\ x) $ としてありうる最小値を求めてください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ <\ 10^9 $
 
### Sample Explanation 1

例えば $ x\ =\ 7 $ とすると，$ \sum_{i=1}^N\ f(A_i+x)\ =\ f(11)\ +\ f(20)\ +\ f(15)\ +\ f(13)\ =\ 14 $ となります．

### Sample Explanation 2

例えば $ x\ =\ 22 $ とすると，$ \sum_{i=1}^N\ f(A_i+x)\ =\ f(145)\ +\ f(67)\ +\ f(700)\ +\ f(112)\ =\ 34 $ となります．

### Sample Explanation 3

例えば $ x\ =\ 0 $ とすると，$ \sum_{i=1}^N\ f(A_i+x)\ =\ f(1)\ +\ f(10)\ +\ f(100)\ =\ 3 $ となります．

### Sample Explanation 4

例えば $ x\ =\ 9999846846847 $ とすると，$ \sum_{i=1}^N\ f(A_i+x)\ =\ f(10000000000000)\ =\ 1 $ となります．

## 样例 #1

### 输入

```
4
4 13 8 6```

### 输出

```
14```

## 样例 #2

### 输入

```
4
123 45 678 90```

### 输出

```
34```

## 样例 #3

### 输入

```
3
1 10 100```

### 输出

```
3```

## 样例 #4

### 输入

```
1
153153153```

### 输出

```
1```

# 题解

## 作者：mod998244353 (赞：10)

由于是求数字和，自然想到数位dp。而且是要考虑进位问题的，所以我们设计状态如下：

设 $f_{u,i}$ 表示让第 $u$ 位恰好有 $i$ 个数进位时所有数的末 $u$ 位数字和的最小值。

初始状态为$f_{0,0}=0$，

显然是由第 $u$ 位转移到第 $u+1$ 位。我们采用刷表法实现。先把 $a$ 按照末 $u$ 位从大到小排序，这样进位的数字一定是 $a$ 的一段前缀。

从小到大枚举 $i$，同时对进位后的 $a$ 数组的第 $u+1$ 位进行计数，然后枚举 $x$ 的第 $u+1$ 位的值 $j$。

这样我们就可以算出这种情况下第 $u+1$ 位有几个数进位、第 $u+1$ 位的数字和。

具体代码如下：
```cpp
//用g刷新f 
for(int i=0; i<=n; ++i) {
	//先枚举第u位有几个数进位
	if(i) --cnt[a[i]/x%10],++cnt[a[i]/x%10+1];
	//第i个数的第u位进位,这里的x是10的u次方
	if(g[i]<1e18) {
		for(int j=0; j<10; ++j) {
          	//枚举x的第u+1位的值
			int tmp=0,sum=0;
			//进位个数，数字和
			for(int k=0; k<=10; ++k) {//枚举a数组第u+1位的值 
				if(j+k>=10) tmp+=cnt[k],sum+=(j+k-10)*cnt[k];//进位
				else sum+=(j+k)*cnt[k];//不进位
			}
			f[tmp]=min(f[tmp],g[i]+sum); 
		}
	}
}
```
时间复杂度是$O(n)$，有巨大常数，完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=200005,N=10;
int n;
ll f[MAXN],g[MAXN],a[MAXN],b[MAXN],cnt[N+1];
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		f[i]=1e18;
	}
	for(ll x=1; x<1e10; x*=10) {
		for(int i=0; i<=N; ++i)cnt[i]=0;
		for(int i=0; i<=n; ++i) {
			g[i]=f[i],f[i]=1e18;
			if(i)++cnt[a[i]/x%10];
		}
		for(int i=0; i<=n; ++i) {
			if(i) --cnt[a[i]/x%10],++cnt[a[i]/x%10+1];
			if(g[i]<1e18) {
				for(int j=0; j<10; ++j) {
					int tmp=0,sum=0;
					for(int k=0; k<=10; ++k) {
						if(j+k>=10) tmp+=cnt[k],sum+=(j+k-10)*cnt[k];
						else sum+=(j+k)*cnt[k];
					}
					f[tmp]=min(f[tmp],g[i]+sum);
				}
			}
		}
		for(int i=0; i<=N; ++i)cnt[i]=0;
		for(int i=1; i<=n; ++i)++cnt[a[i]/x%10];
		for(int i=1; i<N; ++i) cnt[i]+=cnt[i-1];
		for(int i=1; i<=n; ++i) b[cnt[a[i]/x%10]--]=a[i];
		for(int i=1; i<=n; ++i)a[i]=b[n-i+1],assert(i==1||(a[i]%(10*x))<=(a[i-1]%(10*x)));
	}
	printf("%lld\n",f[0]);
	return 0;
} 
```

---

## 作者：spider_oyster (赞：5)

简化题意：

$ans=\sum\limits_{k=1}^{n} f(a_{k})+nf(x)-9\times c$，$c$ 为进位次数。

$\sum\limits_{k=1}^{n} f(a_{k})+nf(x)$ 这一部分很好计算，关键是求 $c$。

考虑是否会进位，设当前位为 $i$，$a$ 数组里某个数第 $i$ 位数字为 $num$，若 $num+x_{i}+lst \geq 10$，则进位。$lst$ 为上一位进的位。注意，这里的加法只会进一位。

所以，只用关心 $num$，$x_{i}$ 和 $lst$。

考虑如何求 $lst$。

> 如果将 $a$ 数组按后 $i-1$ 位降序排序，那么发生了从 $i-1$ 给 $i$ 进了位（即需要加上 $lst$ ）的一定是一段前缀。
>
> 一种思路是多加一维状态表示一共进了多少位。那么喜得 TLE+MLE。
>
> 另一种精简的状态是记录当前位的进位次数，即 $f_{i,j}$ 表示考虑到第 $i$ 位，这一位进了 $j$ 次位的最小值。
>
> 由于排序后上一位的进位的是一段前缀，转移时只需要枚举上一位的进位状态即可。
>
> 这样就解决了 $lst$。

考虑如何计算 $c$。
> 注意刚刚状态没有计算 $c$。
>
> 事实上，$c$ 不需要刻意计算。
> 
> 考虑到当前位 $-10$，往后 $+1$，就是一次进位的贡献。
>
> 其实，$+1$ 的贡献就是 $lst$，可以不管。
>
> 于是每次进位时只考虑对当前位的贡献 $-10$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
const int p[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
int n,x,ans=2e9,a[N],f[10][N];
inline bool cmp(int &a,int &b) {return a%p[x]>b%p[x];}//按 后 x 位排序

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<10;i++)
    {
        vector<int> cnt(11);//桶
        for(int j=1;j<=n;j++) cnt[a[j]/p[i-1]%10]++;
        //枚举上一位的进位情况，上一位进位，就要加上 lst
        //j=0 表示不进位
        for(int j=0;j<=n;j++)
        {
            //不要漏了 num=9,lst=1 这种不加 x_i 就直接进位的情况，用 cnt[10] 统计
            if(j!=0) cnt[a[j]/p[i-1]%10]--,cnt[a[j]/p[i-1]%10+1]++;// 加上 lst
            int jin=cnt[10],s=0;//jin : 当前位进位次数; s : 累加答案
            for(int k=1;k<10;k++) s+=k*cnt[k];
            for(int x=0;x<10;x++)//枚举 x_i
            {
                f[i][jin]=min(f[i][jin],f[i-1][j]+x*n+s);
                jin+=cnt[9-x];
                s-=10*cnt[9-x];
            }
        }
        // 按后 x 位排序
        x=i;
        sort(a+1,a+1+n,cmp);
    }
    for(int i=0;i<=n;i++) ans=min(ans,f[9][i]+i);//不要漏了最后的进位
    cout<<ans;
}
```


---

## 作者：Galex (赞：2)

神仙 dp 题。

设 $dp[i][j]$ 表示考虑了从小到大的前 $i$ 位，向第 $i+1$ 位进了 $j$ 位的答案。

我们将 $A$ 数组按照前 $i$ 位的大小从大到小排序，则向后进位的一定是前 $j$ 个数，故总状态数是 $O(NK)$ 的。其中 $K$ 为最高位数，约为 $10$。

考虑转移，枚举第 $i-1$ 位向第 $i$ 位进了多少位及 $x$ 的第 $i$ 位是多少，即可算出 $i$ 向 $i+1$ 位进了多少位。

总复杂度 $O(K(N\log N+NK))$，跑的极慢。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n, a[200005], w = 1, o[200005];
int dp[15][200005];

bool cmp(int x, int y) {
	return a[x] % w > a[y] % w;
}

signed main() {
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read(), o[i] = i;
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	for (int i = 1; i <= 10; i++, w *= 10) {
		sort(o + 1, o + n + 1, cmp);
		for (int j = 0; j <= 9; j++) {
			int cnt = 0, sum = 0;
			for (int k = 1; k <= n; k++)
				cnt += ((a[k] / w) % 10 + j) > 9, sum += ((a[k] / w) % 10 + j) % 10;
			dp[i][cnt] = min(dp[i][cnt], dp[i - 1][0] + sum);
			for (int k = 1; k <= n; k++) {
				if ((a[o[k]] / w) % 10 + j == 9)
					cnt++, sum -= 9;
				else
					sum++;
				dp[i][cnt] = min(dp[i][cnt], dp[i - 1][k] + sum);
			}
		}
	}
	int ans = 1e9;
	for (int i = 0; i <= n; i++)
		ans = min(ans, dp[10][i] + i);
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Feyn (赞：1)

题意：定义 $f(x)$ 为其十进制意义下各位数字之和，比如 $f(1)=1,f(123)=6$。给定长度为 $n$ 的序列 $A$，请找到一个非负整数 $x$ 使得 $\sum\limits_{i=1}^nf(A_i+x)$ 最小，并输出这个最小值。

由于 $n$ 很大，不大可能是以 $n$ 为阶段进行 DP，所以只可能是以数位为阶段。然后用 $f_{i,y}$ 代表从低到高第 $i$ 位，并且这一位产生了 $y$ 个进位时最多能减少的值（也就是假设 $x$ 这一位是 $t$，那么数字和增加了 $nt$，而由于产生了 $y$ 次进位，变化的量就是 $nt-9y$，维护的就是这个东西的最小值）。

思考这样的状态是否足够。我们发现一个性质，由于每个数加的 $x$ 是相同的，所以后 $i$ 位越大的数越容易在这一位产生进位。于是我们可以按照后 $i$ 位的大小把 $A$ 排序，这样一来就可以精准地知道到底是哪些数进位了。

梳理一下流程。枚举上一阶段的状态以及 $x$ 当前位放什么数。假设当前枚举到了 $f_{i-1,z}$，当且这一位放的数是 $t$，于是发现一个数能进位当且仅当这一位上的数 $t'+t\ge 10$，也就是 $t'\ge 10-t$。动态维护 $t'$ 的后缀和即可。由于有进位的影响，而根据前面的分析，上一阶段每个进位都确定地对应了某个数，这样一来只需要给这个数对应的位置减一，然后给后一个位置加一，并更新后缀和即可。

复杂度 $O(T^2n)$，$T$ 是 $10$，即表示阶段数（也就是最大数的位数）以及字符集大小。

---

## 作者：happybob (赞：0)

考虑 $f(a+b)$，显然等于 $f(a)+f(b)-9\times g(a, b)$，$g(a,b)$ 表示 $a+b$ 的进位次数。

然后考虑数位 DP，对于从右到左第 $i$ 位，显然其右侧加上 $x$ 会进位的数必然是只保留后面的数后排序后的一段后缀。于是记 $f_{i,j}$ 表示到第 $i$ 位，第 $i-1$ 位也就是右侧的那位会进位的最小的是第 $j$ 个数。转移可以顺序枚举 $j$，注意到 $j \gets j+1$ 时只需要在一个集合中加入或删除一个数，查询是查询最小值。`set` 访问首迭代器的复杂度是 $O(1)$ 的，所以复杂度是正确的。

---

## 作者：DerrickLo (赞：0)

考虑从小到大确定 $x$，记 $f_{i,j}$ 表示现在到了第 $i$ 位，现在的 $x$ 满足有 $j$ 个数可以从第 $i-1$ 位进位到第 $i$ 位，最小的答案是多少，转移时可以枚举 $k$ 表示第 $i$ 位填的数，因为这 $j$ 个数显然是前 $i-1$ 位最大的那 $j$ 个数，预处理一些前缀和即可算出有多少个数从第 $i$ 位进位到第 $i+1$ 位，直接主动转移即可。

时间复杂度 $\mathcal O(nk\log n+nk^2)$，其中 $k=10$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],b[15][200005],f[15][200005],pw[15],ans=1e18;
signed cnt[15][15][200005];
vector<int>ve[15],ve2[15];
int calc(int x){int ans=0;while(x)ans+=x%10,x/=10;return ans;}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,pw[0]=1;
	for(int i=1;i<=10;i++)pw[i]=pw[i-1]*10;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=0;i<=10;i++)for(int j=1;j<=n;j++)b[i][j]=a[j]%pw[i];
	for(int i=0;i<=10;i++){
		for(int j=1;j<=n;j++)ve[i].emplace_back(j);
		sort(ve[i].begin(),ve[i].end(),[&](int x,int y){return b[i][x]>b[i][y];});
		if(i<10){
			for(int j=1;j<=n;j++)ve2[i].emplace_back(b[i+1][ve[i][j-1]]/pw[i]);
			for(int j=0;j<n;j++){
				if(j!=0)for(int k=0;k<10;k++)cnt[i][k][j]=cnt[i][k][j-1];
				cnt[i][ve2[i][j]][j]++;
			}
			for(int j=0;j<n;j++)for(int k=9;~k;k--)cnt[i][k][j]+=cnt[i][k+1][j];
		}
	}
	memset(f,0x3f,sizeof f),f[0][0]=0;
	for(int i=0;i<10;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<10;k++){
				int now=0;
				if(!j)now=cnt[i][10-k][n-1];
				else now=cnt[i][9-k][j-1]-cnt[i][10-k][j-1]+cnt[i][10-k][n-1];
				f[i+1][now]=min(f[i+1][now],f[i][j]+k*n-9*now);
			}
		}
	}
	for(int i=0;i<=n;i++)ans=min(ans,f[10][i]);
	for(int i=1;i<=n;i++)ans+=calc(a[i]);
	cout<<ans;
	return 0;
} 
```

---

## 作者：XYQ_102 (赞：0)

看起来像数位 dp，其实也确实是 dp。

令原数组所有数的数位和为 $S$，$x$ 的数位和为 $X$。那么最终的数位和为 $S+n\times X-$ 所有数加 $x$ 的总进位次数 $\times 9$，这个模拟一下加法的过程就能发现。我们把进位次数 $\times 9-n\times X$ 称为"收益"，我们想让收益最大。

我们从低往高确定 $x$ 的每一位。关键观察：当确定了 $x$ 的最低的 $i$ 位时，$a$ 数组中那些会从第 $i$ 位到第 $i+1$ 位进一位的数，肯定是 $a$ 中前 $i$ 位按照数值比较最大的一些数。所以就可以 dp 了：$dp_{i,j}$ 表示计算到第 $i$ 位，前 $i-1$ 位最大的 $j$ 个数被第 $i-1$ 位到第 $i$ 位进位了一次的情况下的最大收益。转移时枚举 $x$ 的当前这一位选什么，计算第 $i$ 位到第 $i+1$ 位的进位数只要用前缀和预处理一下就行了。

## Code
```cpp
#include <bits/stdc++.h>
 
#define rep(i,n) for(int i=0;i<n;++i)
#define repn(i,n) for(int i=1;i<=n;++i)
#define LL long long
#define pii pair <int,int>
#define fi first
#define se second
#define mpr make_pair
#define pb push_back
 
void fileio()
{
  #ifdef LGS
  freopen("in.txt","r",stdin);
  freopen("out.txt","w",stdout);
  #endif
}
void termin()
{
  #ifdef LGS
  std::cout<<"\n\nEXECUTION TERMINATED";
  #endif
  exit(0);
}
 
using namespace std;
 
void chmax(LL &x,LL y){if(x<y) x=y;}
 
LL n,a[200010],pw10[15],clue[200010],lft[200010],ord[20][200010];
LL pref[15][200010][15];//pref[i][j][k]: 第i层，前缀最大的j个中，当前位>=k的个数
LL dp[15][200010];//dp[i][j]: 第i层，前缀最大的j个被进位的最大收益
 
int main()
{
  fileio();
 
  pw10[0]=1;repn(i,12) pw10[i]=pw10[i-1]*10;
  cin>>n;
  rep(i,n) scanf("%lld",&a[i]);
  rep(i,10)
  {
    rep(j,n) clue[j]=a[j]%pw10[i],lft[j]=a[j]/pw10[i]%10,ord[i][j]=j;
    sort(ord[i],ord[i]+n,[](LL x,LL y){return clue[x]>clue[y];});
    rep(j,n)
    {
      rep(k,12) pref[i][j+1][k]=pref[i][j][k];
      for(int k=0;k<=lft[ord[i][j]];++k) ++pref[i][j+1][k];
    }
  }
  rep(i,14) rep(j,n+3) dp[i][j]=-1e18;
  dp[0][0]=0;
  rep(i,10) rep(j,n+1) if(dp[i][j]>-1e18)
  {
    rep(nxt,10)
    {
      LL gain=(LL)(-nxt)*n,add=pref[i][j][10-nxt-1]+pref[i][n][10-nxt]-pref[i][j][10-nxt];
      gain+=add*9;
      chmax(dp[i+1][add],dp[i][j]+gain);
    }
  }
  LL ans=-1e18;
  rep(j,n+1) ans=max(ans,dp[10][j]);
  LL ori=0;
  rep(i,n)
  {
    while(a[i]>0)
    {
      ori+=a[i]%10;
      a[i]/=10;
    }
  }
  ans=ori-ans;
  cout<<ans<<endl;
 
  termin();
}
```

---

## 作者：xuanxuan001 (赞：0)

做法跟官方题解不太一样，虽然做法比较草，但还是发一篇吧。

AT 四连掉啊，终于上分了~~还一把创新高了~~。

说句鲜花，其实官方题解的做法是可以推广到 $a_i \le 10^{18}$ 的，但我的不能，但是呢，它只开到了 $10^9$ 啊哈哈哈。

我的做法就是先取一个合适的 $B = 10^y$，我的代码里取的 $y = 7$。然后将每个数的较低的 $y$ 位和其他的分开考虑。~~这里为什么叫 $y$ 不叫 $x$ 呢，因为题面里有 $x$ 了~~。

首先考虑低 $y$ 位，这时另新数组 $b$ 满足 $b_i = a_i \bmod B$，这时考虑求出 $t_i(0 \le i <B)$ 表示 $\sum\limits_{j=1}^n f(b_j + i)$，也就是 $x = i$ 时前 $y$ 位对答案的贡献。函数 $f$ 就是题面里的定义，下同。

那么直接暴力求显然是不行的，但是可以考虑 $f(a) + f(b)$ 与 $f(a+b)$ 的关系。由广为人知的结论，它们之间相差的值就是 $a+b$ 的进位数的九倍。所以我们只需要求出进位数之和 $t'_i$ 就能得出 $t_i = \sum\limits_{i=1}^nf(a_i) + f(i)n - 9t'_i$。

那么再次由众所周知的结论，$a+b$ 的进位数其实就是 $\sum\limits_{i=1}^\infty[a \bmod 10^i + b \bmod 10^i \ge 10^i]$。代入这题里面就是

$$
t'_i =\sum\limits_{j=1}^n\sum\limits_{k=1}^y[a_j \bmod 10^k + i \bmod 10^k \ge 10^k]
$$

那么显然就可以把两个 $\sum$ 交换一下，依次考虑每个 $k$ 对答案的贡献。这时的贡献是 $10^k$ 一次循环的。并且 $a_i$ 会使所有满足 $j \ge 10^k - (a_i \bmod 10^k)$ 的 $t'_j$ 加一。这是个很显然的差分优化，所以这部分的总复杂度是 $O((n+B)y)$。

下面再考虑剩下的部分，但会发现只剩下两位了，也就是 100，并且不难发现只考虑 $0 \le x < 10^9$ 的情况不影响答案，所以我们可以直接枚举 $x$ 最高的两位，也就是剩下的部分，然后直接 $O(n)$ 计算。

但这时遇到了一个问题，就是低 $y$ 位的进位怎么考虑。

我赛事发现这个问题时有些蒙，我想直接枚举最高的三位，留一位重复，然后直接不考虑进位玄学过去，但连最后一个样例都过不了。于是我特判 $n=1$ 强行交了一发，结果一大半都是 WA。

这种玄学可能确实很难过去，特别是出题人会手造数据。

但其实好好想想，突然就恍然大悟了。虽然是 $n$ 个数是否进位的情况，但是情况数哪有 $2^n$ 种。进位的一定是 $a_i \bmod B$ 最大的几个，而这就取决于 $x \bmod B$ 的值，这就是前面处理出来的 $t$ 数组。

所以可以再记数组 $mn_i$ 表示如果 $a_i \bmod B$ 最大的 $i$ 个有进位那么前 $y$ 位对答案的贡献最小是多少，不难发现它其实就对应着 $t$ 数组上的一段区间的最小值，且这 $n+1$ 个区间互不重叠，覆盖全部。~~到底是哪段区间应该很显然吧，实在不行可以看代码，懒得描述了~~。

那么下面就只需要枚举最高的两位的 100 种可能和 $O(n)$ 种进位情况就能更新答案了。前两位对答案的贡献可以通过不同进位情况间转换来实现均摊 $O(1)$ 求出。所以这部分的复杂度是 $O(100n)$。

看起来两部分的复杂度都顶的挺满的，但跑得倒是挺快，跟官方题解时间差不多。

可以通过 $O(\sqrt{10^9})$ 的预处理来实现 $O(1)$ 求出 $f$ 的某个值，代码中直接处理了前 $B$ 个，因为大部分询问都是问的前 $B$ 个，这样常数小一些。

又是一些鲜花，处理完后我觉得其实是可以继续维护出新的 $mn$ 数组从而将位数继续扩大来实现 $a_i \le 10^{18}$ 的，但我没有细想，就算做到了其实也是跟官方题解思想差不多了。官方题解的 DP 的核心其实也就是我处理进位时的那个结论，但我一开始没想到，所以就搞出了这么个强行分治考虑的解法。

对于 $a_i$ 有重复元素，或者说 $a_i \bmod B$ 有重复元素的情况，我赛时没有细想，~~但赛后又懒得细想，但总之它过了，所以应该没问题吧~~。

代码：
```
#include<cstdio>
#include<algorithm>
#define TY int
#define MAXN 200002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
using namespace std;
typedef long long ll;
const TY M=998244353,B=10000000;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw1(TY a){if(a>9)qw1(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw1(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY n=qr(),a[MAXN],sm[B],b[B],t[B],val,p,d[MAXN],id[MAXN],mn[MAXN],ans;
inline TY js(TY a){return sm[a/B]+sm[a%B];}//f函数 
bool cmp(TY x,TY y){return d[x]<d[y];}
int main(){
	fOR(i,1,B)sm[i]=sm[i/10]+(i%10);//预处理的f函数 
	FOR(i,1,n)ans+=js(a[id[i]=i]=qr());
	for(TY x=10;x<=B;x*=10){//拆贡献求进位 
		fOR(i,0,x)b[i]=0;
		FOR(i,1,n)++b[x-a[i]%x];
		fOR(i,1,x)b[i]+=b[i-1];
		fOR(i,0,B){
			t[i]+=b[p];
			if((p=-~p)==x)p=0;
		}
	}FOR(i,1,n){val+=sm[d[i]=a[i]%B];d[i]=B-d[i];}//转换为答案 
	fOR(i,0,B)t[i]=val+sm[i]*n-t[i]*9;
	FOR(i,1,n)a[i]/=B;d[n+1]=B;
	sort(id+1,id+n+1,cmp);
	sort(d+1,d+n+1);
	FOR(i,0,n){
		mn[i]=t[d[i]];
		rOF(j,d[i+1]-1,d[i])mn[i]=minn(mn[i],t[j]);//求mn数组 
	}fOR(x,0,100){
		val=0;FOR(i,1,n)val+=sm[a[i]+x];
		ans=minn(ans,mn[0]+val);
		FOR(i,1,n){
			val-=sm[a[id[i]]+x];
			val+=sm[a[id[i]]+x+1];//通过迭代求出新的前两位的贡献 
			ans=minn(ans,mn[i]+val-i);//更新答案，我的t数组里包括了进位的数位和，所以这里需要减去 
		}
	}qw(ans,0);return 0;
}
```

---

