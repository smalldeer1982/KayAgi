# Little Pony and Harmony Chest

## 题目描述

### 题目背景

紫悦正在宇宙公主和月亮的城堡里研究和谐之元的宝箱。


对于一个正整数序列 $b_i$，当且仅当它的任意两个元素都互质时，这个序列 $b_i$ 才是和谐的。据古书记载，宝箱的钥匙是能让以下表达式的值最小的和谐序列 $b_i$：

$$ \sum_{i=1}^n|a_i-b_i| $$

现在紫悦已经得到了序列 $a_i$，你能帮助紫悦找到开启宝箱的钥匙吗？

## 样例 #1

### 输入

```
5
1 1 1 1 1
```

### 输出

```
1 1 1 1 1 ```

## 样例 #2

### 输入

```
5
1 6 4 2 8
```

### 输出

```
1 5 3 1 8 ```

# 题解

## 作者：周子衡 (赞：11)

思路：数论+状态压缩

这道题的关键条件是：

```
当且仅当它的任意两个元素都互质时，这个序列bi才是和谐的。
```

也就是说，我们要让$b$中的元素两两互质。

很容易想到质数。一个简单的引理是：**两个正整数互质，当且仅当它们没有共同的质因数。**（证明从略）

因此转化为这$n$个数均没有相同的质因子。我们再观察，题中$a_i$的范围非常小，我们猜测在$b$中出现的质因子不会很大。

**定理一：$b$中的元素所含质因子最大为$53$。**

**证明：**假设存在$b$中元素存在$>53$的质因子，令其为$b_i$，由质数离散性得$b_i\geq 59$。将$b_i$改为$1$，可知此时一定还是两两互质，且由于$a_i\leq 30,|b_i-a_i|=b_i-a_i\geq 59-30=29=30-1\geq a_i-1$，矛盾！故命题得证。

同时我们还可以得到一个限定每个元素范围的定理：

**定理二：$b$中每个数均小于$59$。**

证明基本同上，从略。

计算得出$[2,53]$内的质数共$16$个，我们可以考虑状态压缩动态规划：设前$i$个数，能用的质数集合为$j$的最小值为$dp[i][j]$，其中$j$是一个$16$位二进制数，每一位分别代表一个质数能不能用。

转移方程：

$dp[i][j]=min\{|a[i]-k|+dp[i-1][j-table[k]]|table[k]\subset j\}$

其中$k$枚举每个决策，$table[k]$是预先处理好的数组，表示能整除$k$的质数组成的集合，转移时判断$k$是否能用集合$j$中的质数乘出（可用位运算判断），如果能则转移。

另外本题要求输出方案，额外开一个数组$way[i][j]$存方案即可。

代码：

```cpp

#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

int a[101]={};
int dp[101][(1<<16)]={},way[101][(1<<16)]={};

const int prm[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

int table[54]={};

void out(int now_x,int now_y)
{
	if(!now_x)return;
	out(now_x-1,now_y^table[way[now_x][now_y]]);
	printf("%d ",way[now_x][now_y]);
}

int main()
{
	int n=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	
	for(int i=1;i<=58;i++)
	{
		for(int j=0;j<16;j++)
		{
			if(i%prm[j]==0)
			{
				table[i]^=(1<<j);
			}
		}
	}
                                 
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(1<<16);j++)
		{
			dp[i][j]=1e9;
			for(int k=1;k<=58;k++)
			{
				if((table[k]|j)!=j)continue;
				int tmp=abs(k-a[i])+dp[i-1][j^table[k]];
				if(tmp<dp[i][j])dp[i][j]=tmp,way[i][j]=k;
			}
		}
	}
	
	out(n,(1<<16)-1);
}

```

---

## 作者：Durancer (赞：3)

### 前言

素数筛法+~~简单~~状压DP

### 思路

与数论相关的题目先看数据范围。

可以看见 $a_i \leq 30$ ，那么我们就来思考 $b_i$ 的数据范围。

可以发现，当 $b_i \geq 59$ 的时候。

看 $59$ 这个质数，考虑一种最坏的情况。

$$|1-30|=|59-30|=29$$ 

所以选用 $59$ 明显是不必要的，可以减去这个质数，减少枚举的次数。

那么在 $b_i \leq 58$ 只有 $16$ 个质数，显然可以状压DP。

首先先来解决一个问题，为什么要用质数。

根据**唯一分解定理**可以发现的时：任何 $\geq 1$ 的数，都可以被表示为若干个质数相乘的形式，那么如果要保证 $b_i$ 中的一个数与其它数是互质的，只要保证 $b_i$ 前面的数不会出现能够整除 $b_i$ 的质数因子即可。

那么可以考虑先预处理出每一个可以放进 $b_i$ 中的数的可以被整除的质数集合 $\text{Ming}_i$，用二进制表示。

想到这里就可以很清晰的想出来方程：

设 $f_{i,j}$ 为前 $i$ 个数，包含的质数因子集合的状态为 $j$ 的时候的最小值。

但是发现我们要求的值没有被表示全，所以就要另外设一个数组 $g_{i,j}$ 表示前 $i$ 个数质数因子状态为 $j$ 时的最小值时的 $b_i$ 所表示的数为。

那么就可以想出来状态转移方程是！

$$f_{i,j}=\min_{k\in j}\{ f_{i-1,j\oplus \text{Ming}_k}+|a_i-k|\}$$

当当前转移的值更优时，可以考虑转移 $g_{i,j}=k$

最后的值需要递归来输出。

那么即可完成此题。

时间复杂度为 $O(n\log n+b_{i,max}\times 16+2^{16}n)$

~~奇怪~~


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int N=1e2+9;
const int mod=998244353;
const int M=(1<<16);
int a[N];
int cnt;
int n;
bool vis[N];
int prime[N];
int f[N][M+9];
int g[N][M+9];//存贮这个方案的最佳数为多少
int Ming[N];//存储能够整除i的质数的集合为 
int	imp;
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')s=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
void prepare()
{
	for(int i=2;i<=58;i++)//考虑到到了 59 和 1的贡献值是相同或者劣的，所以不打算枚举 
	{
		if(!vis[i]) prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=N;j++)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	for(int i=1;i<=58;i++)
	{
		for(int j=1;j<=16;j++)
			if(i%prime[j]==0) 
				Ming[i]|=(1<<(j-1));
		//cout<<i<<"= "<<Ming[i]<<endl;
	}
	
}
void work(int x,int i)
{
	if(x==0) return;
	work(x-1,(i^Ming[g[x][i]]));
	printf("%d ",g[x][i]);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	prepare();
	for(int i=1;i<=n;i++)
		for(int j=0;j<M;j++)//枚举该放的数
		{
			f[i][j]=0x3f3f3f3f;
			for(int k=1;k<=58;k++)
			{
				if((Ming[k]|j)!=j) continue;//不是子集，那么就不找
				imp=f[i-1][j^Ming[k]]+abs(k-a[i]);
				if(imp<f[i][j])
				{
					f[i][j]=imp;
					g[i][j]=k;
					//cout<<k<<endl;
				}
			}
		}
	work(n,M-1);
	return 0;
}
```





---

## 作者：一念之间、、 (赞：2)

# 题意：

构一个序列 满足 $\sum _i |a_i-b_i|$ 最小，序列长度 $100$，$a_i \le 30 $，$b$ 序列满足限制：两两互质。


# 题解

解法是很多了，但是为什么要写这个题解，因为这里做法更优一点，无论是复杂度还是常数上面：`rank1 547 ms` 然后 ` rank2 4s +`。

首先明显尝试用 `Dp/贪心` 先得到这个答案再考虑构方案的事情。

把 $A$ 数组排序，显然 $B$ 构出来排序后与 $A$ 排序后对位匹配是最优的，从这个角度进行 `dp`，观察到题目要求互质，我们先从质数的角度考虑，$30$ 以内的质数只会有 $10$ 个，然后对于 $> 30$ 的质数，若使用，则一定是独立使用而不是作为一个合数的因子使用。

对于 $< 30$ 的质数，我们观察到其可以作为合数因子，拼凑出来的数不应该超过 $60$ 不然一定没有单独作为质数填入优。

于是 `dp` 过程形如：前 $i$ 个，然后从小到大枚举到的数是多少（$60$ 以内）然后状压 $10$ 个质因子。

复杂度 $O(60\times 1024\times n)$。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define ull unsigned ll 
#define dd double
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
#define getchar gc
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x);pc(op,0);
}
const int xx=1005;
int n,a[xx],prim[xx],cnt;
int f[105][63][1025],s[xx];
void ad(int &x,int y){x=min(x,y);}
int rem[xx],id[xx];
char pr[105][63][1025];
int main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),id[i]=i;
	sort(id+1,id+n+1,[&](int x,int y){return a[x]<a[y];});
	sort(a+1,a+n+1);
	
	int cnt=0;
	for(int i=2;i<=1000;i++)
	{
		int cr=1;
		for(int j=2;j<i;j++)
			if(i%j==0)cr=0;
		if(cr)prim[++cnt]=i;
	}
	memset(f,0x3f,sizeof(f));
	f[1][1][0]=0;
	//不能 用上任何一个大质数 
	for(int i=1;i<=1000;i++)
	{
		for(int j=1;j<=cnt;j++)
		{
			if(i%prim[j]==0)
			{
				if(prim[j]>30)
				{
					s[i]=-1;
					break;
				}
				s[i]+=(1<<(j-1));
			}
		}
	}
	int ans=1e9,nx=0,ny=0,nz=0;
	for(int i=1;i<=n;i++)
	{
		int j=11;
		for(int k=n-i+1;k<=n;k++)
			rem[i]+=abs(a[k]-prim[j++]);
	}
	for(int i=1;i<=n+1;i++)
	{
//		cerr<<i<<"$$\n";
		for(int j=1;j<=61;j++)
		{
			for(int k=0;k<1024;k++)
			{
				if(f[i][j][k]>=1e9)continue;
				ans=min(ans,f[i][j][k]+rem[n+1-i]);
				if(ans==f[i][j][k]+rem[n+1-i])nx=i,ny=j,nz=k;
				if(i==n+1)continue;
				ad(f[i][j+1][k],f[i][j][k]);
				if(f[i][j+1][k]==f[i][j][k])pr[i][j+1][k]=2;
				if(s[j]!=-1&&((s[j]&k)==0))
				{
					ad(f[i+1][j][k+s[j]],f[i][j][k]+abs(a[i]-j));
					if(f[i+1][j][k+s[j]]==f[i][j][k]+abs(a[i]-j))pr[i+1][j][k+s[j]]=1;
				}
			}
		}
//		cerr<<i<<"$$\n";
	}
//	cerr<<nx<<" "<<ny<<" "<<nz<<" "<<f[nx][ny][nz]<<" "<<(int)pr[nx][ny][nz]<<"%%\n";
	vector<int>te;
	int j=11;
	for(int i=nx;i<=n;i++)te.push_back(prim[j++]);
	while(pr[nx][ny][nz])
	{
//		cerr<<nx<<" "<<ny<<" "<<nz<<"$$\n";
		if(pr[nx][ny][nz]==1)te.push_back(ny),nz-=s[ny],nx--;
		else ny--;
	}
	sort(te.begin(),te.end());
	int lp=0;
	vector<int>ANS(n+2);
	for(int i=1;i<=n;i++)ANS[id[i]]=te[lp++];
	for(int i=1;i<=n;i++)
		cout<<ANS[i]<<" ";
	puts("");
//	cout<<ans<<"\n";
	pc('1',1);
	return 0;
}
```

---

## 作者：cold_cold (赞：2)

* **问题思考**：一个和谐的序列两两互质，满足什么性质？
- 它们分解质因数后，没有两个数拥有相同的质因子。
* **状态构思**：如果我已经决定完前i 个数是多少，现在要决定下一个
数，需要满足什么限制？——不能有和前面重复的质因子。
- 这代表我们需要记录下，目前已经用了哪些质因子了。
* **状态设计**：设F[i][j] 为，已经决定完前i 个数是多少，而且已经用
了状态为j 的质因子了，现在的最小权值差是多少。
- **如何状态压缩**？2,3,5,7,11,...；一个代表一个二进制位；用了是1，
没有是0。




```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 105;
const int M = 61;
const int S = 1 << 17;

int n, a[N], b[N];
int p[N], fg[N];

int g[M];
int f[N][S], opt[N][S];

int absp(int x)
{
	return x > 0 ? x : -x;
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; ++ i) cin >> a[i];
	// 预处理质数
	for(int i = 2; i < M; ++ i)
	{
		if(!fg[i]) p[++p[0]] = i;
		for(int j = 1; j <= p[0] && i * p[j] < M; ++ j)
			fg[i * p[j]] = 1;
	}
	// 预处理每个数的质因子所代表的状态
	for(int i = 1; i < M; ++ i)
	{
		g[i] = 0;
		for(int j = 1; j <= p[0]; ++ j)
			if(i % p[j] == 0) g[i] |= 1 << (j-1);
	}
	// 动态规划主过程
	int ns = 1 << p[0];
	// 初值：最大值
	for(int i = 1; i <= n + 1; ++ i)
		for(int j = 0; j < ns; ++ j) f[i][j] = S;

	f[1][0] = 0;

	for(int i = 1; i <= n; ++ i)// 初值：最大值
		for(int j = 0; j < ns; ++ j) if(f[i][j] < S)// 枚举状态
			for(int k = 1; k < M; ++ k)// 枚举这个位置的数
				if((g[k] & j) == 0)// 如果之前没有出现过
				{
                	// 计算最优值
					int t = f[i][j] + absp(k - a[i]);
					if(t < f[i+1][g[k] | j])// 更新最优值
						f[i+1][g[k] | j] = t,
						opt[i+1][g[k] | j] = k;
				}
	// 最优值输出
	int ansp = S;
	int ansm = 0;

	for(int j = 0;  j < ns; ++ j)// 记录最优值所对应的状态
		if(f[n+1][j] < ansp) ansp = f[n+1][j], ansm = j;

	for(int i = n+1; i > 1; -- i)// 依次向前查询
	{
		b[i-1] = opt[i][ansm];
		ansm ^= g[b[i-1]];
	}

	for(int i = 1; i <= n; ++ i) cout << b[i] << " ";
	cout << endl;

	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

水题。

我们注意到 $\max b_i\le 60$，因为假如 $b_i> 60$，不如令 $b_i=1$。

我们注意到 $60$ 以内的素数个数为 $16$，那么不妨考虑状压。

那么我们设 $dp_{i,S}$ 为前 $i$ 个数中质因子使用的情况为 $S$ 时 $\sum_{k=1}^i|a_k-b_k|$ 的最小值。

那么就有转移方程：

$$dp_{i,S\cup pri_j}=\min_j\{dp_{i-1,S}[pri_j\cap S=\varnothing]\}$$

其中 $pri_x$ 为 $x$ 的质因子集合。

然后我们发现要构造，那么就在转移可行时记录一下就行了。

---

## 作者：Epoch_L (赞：0)

## Solution
观察范围 $a_i\le 30$ 比较特殊，于是我们可以试着考虑 $b$ 的范围。

直觉告诉我们 $b$ 不会很大，当 $b_i\le 59$ 时，有 $|a_i-b_i|\le 29$。当 $b_i > 59$ 时，$|a_i-b_i|> 29$，但是如果这时我们将 $b_i$ 换成 $1$，也是满足互质的，且 $|a_i-b_i|$ 可以变得更小，所以我们可以知道最优答案中 $b_i\le 59$。

然后就是经典套路，状压，$st_i$ 表示 $i$ 中所含质因子种类，$f_{i,j}$ 表示前 $i$ 个数所选的数质因子状态为 $j$ 的最小答案，转移方程：
$$
f_{i,j\operatorname{or} st_k}=\min(f_{i-1,j}+|a_i-k|)(st_k \operatorname{and}j=0)
$$
其中 $k$ 为第 $i$ 位选的数，$\operatorname{or}$ 和 $\operatorname{and}$ 表示按位或和与。

$[1,59]$ 质数共 $17$ 个，故 $j\le 2^{17}-1$。

需要枚举 $i,j,k$，时间复杂度约为 $O(100\times 2^{17}\times 59)\approx O(7.7\times 10^8)$。$4s$ 随便跑。

因为要输出方案，多记一个 $g_{i,j}$ 表示决策点，并且要用滚动数组可能有点麻烦，建议直接正常写。

## Code
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=107,M=2e5+7,inf=1e9;
int a[N],f[N][M],st[N],g[N][M];
int prim[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};
int ans[N];
int main(){
  int n;read(n);
  for(int i=1;i<=n;i++)read(a[i]);
  for(int i=1;i<=60;i++)for(int j=0;j<=16;j++)
    if(i%prim[j]==0)st[i]^=(1<<j);
  int S=(1<<17)-1;
  memset(f,63,sizeof f);
  for(int i=0;i<=S;i++)f[0][i]=0;
  for(int i=1;i<=n;i++)for(int j=0;j<=S;j++)for(int k=0;k<=59;k++){
    if(st[k]&j)continue;
    int tmp=f[i-1][j]+abs(a[i]-k);
    if(tmp<f[i][j|st[k]])f[i][j|st[k]]=tmp,g[i][j|st[k]]=k;
  }
  int res=inf,lst;
  for(int i=0;i<=S;i++)if(f[n][i]<res)res=f[n][i],lst=i;
  for(int i=n;i>=1;i--)ans[i]=g[i][lst],lst^=st[ans[i]];
  for(int i=1;i<=n;i++)printf("%d ",ans[i]);
  return 0;
}
```

---

## 作者：Jayun (赞：0)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF453B)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14453716.html)

# 题目大意：

给定一个数组 $a$，找到一个两两互质的数组 $b$ 使得 $\sum\limits_{i=1}^{n}|a_i-b_i|$ 最小。

# 正文：

我们可以从 $a_i\leq 30$ 想到这道题可能与状压沾边。设 $f_{i,J}$ 表示前 $i$ 个数选了集合 $J$ 中的质数作为 $b_i$ 的质因数。其中集合 $J$ 在实现中就是那么有：

$$f_{i,J}=\min_{K\subseteq J，k=|J-K|}\{f_{i-1,K}+|a_i-k|\}$$

---

但是还有一个问题：我们不知道 $b_i$ 的范围。

这个问题也好解决。还是 $a_i\leq 30$，因为 $b_i$ 最小是 $1$，那么 $|a_i-b_i|$ 的上界是 $30-1=29$。也就是说 $b_i$ 不超过 $30+29=59$，又因为差值如果是 $29$ 的话，$b_i=1$ 会更优，毕竟 $1$ 可以重复选择。所以实际上 $b_i$ 不超过 $58$。

以上是我的思考过程，仅供参考。如果要看更严谨的证明，可以移步题解区看 **@周子衡** 爷的[题解](https://www.luogu.com.cn/blog/zhouziheng666/solution-cf453b)。

# 代码：

我代码里 $b_i$ 的上界还是 $59$ 的，可以改成 $58$。

```cpp
int pri[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59}; 

void Output(int x, int y)
{
	if (!x) return;
	Output(x - 1, y ^ has[ans[x][y]]);
	printf ("%d ", ans[x][y]);
}

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf ("%d", &a[i]);
	for (int i = 1; i <= 59; i++)
		for (int j = 0; j < 17; j++)
			if(!(i % pri[j])) has[i] |= 1 << j;
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = 1e9;
		for (int j = 0; j < (1 << 17); f[i][++j] = 1e9)
			for (int k = 1, tmp = 0; k <= 59; k++)
			{
				if ((has[k] | j) != j) continue;
				tmp = abs(a[i] - k) + f[i - 1][j ^ has[k]];
				if (tmp < f[i][j]) f[i][j] = tmp, ans[i][j] = k;
			} 
	}
	Output(n, (1 << 17) - 1); 
    return 0;
}
```

---

## 作者：yu__xuan (赞：0)

### 题目

[CF453B Little Pony and Harmony Chest](https://www.luogu.com.cn/problem/CF453B)

### 思路

状压 DP。

>$b$ 中元素一定小于 $59$。
>若 $b$ 中某一个元素为 $59$，那么 $59 - a \ge 29$，不如使用 $1$ 代替 $59$，$a-1\le29$。

因为要求 $b$ 种元素都互质，也就是说没有相同的质因子。$[1,58]$ 以内一共 $16$ 个质因子。可以对质因子进行状压。

$f_{i,j}$ 表示 $a$ 的前 $i$ 个元素已经匹配了并且在 $j$ 状态下的最小值。

 $p_k$ 表示 $k$ 有哪些质因子。

$g_{i,j}$ 用于记录答案。

状态转移看代码吧。。

### Code

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define M 101
#define inf 2147483647

bool isprime[M];
int c, p[M], prm[M], res[M];
int n, a[M], b[M], f[M][1 << 17], g[M][1 << 17];

int min(int a, int b) { return a < b ? a : b; }

void Prime() {
    for (int i = 2; i <= 60; ++i) {
        if (!isprime[i]) {
            prm[c++] = i;
            int j = i + i;
            while (j <= 60) {
                isprime[j] = true;
                j += i;
            }
        }
    }
}//筛一下素数

int main() {
    Prime();
    for (int i = 2; i <= 59; ++i) {
        for (int j = 0; j < c; ++j) {
            int x = i;
            if (prm[j] > x) break;
            while (x % prm[j] == 0) {
                x /= prm[j];
                p[i] |= 1 << j;
            }
        }
    }//计算 p 数组。
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i =1; i <= n; ++i) {//枚举当前在 a 的哪个位置
        for (int k = 1; k <= 58; ++k) {//当前位置使用什么数
            int S = ((1 << 17) - 1) ^ p[k];//计算能使用 k 的状态 S（在 S 及 S 的子集的时候能使用 k）
            for (int j = S; j >= 0; j = (j - 1) & S) {
                int ad = abs(k - a[i]);
                if (f[i][j | p[k]] > f[i - 1][j] + ad) {
                    f[i][j | p[k]] = f[i - 1][j] + ad;
                    g[i][j | p[k]] = k;//记录这一步使用了什么数
                }
                if (j == 0) break;
            }
        }
    }
    int anss, minn = inf, now = n;//anss记录下最优解得质因子使用情况
    for (int i = 0; i <= (1 << 17) - 1; ++i) {
        if (f[n][i] < minn) {
            anss = i;
            minn = f[n][i];
        }
    }
    while (now) {
        res[now] = g[now][anss];
        anss ^= p[g[now--][anss]];
    }//找出 b 数组
    for (int i = 1; i <= n; ++i) printf("%d ", res[i]);
    return 0;
}
```

---

