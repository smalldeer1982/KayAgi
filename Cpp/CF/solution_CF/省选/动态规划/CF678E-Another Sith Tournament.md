# Another Sith Tournament

## 题目描述

The rules of Sith Tournament are well known to everyone. $ n $ Sith take part in the Tournament. The Tournament starts with the random choice of two Sith who will fight in the first battle. As one of them loses, his place is taken by the next randomly chosen Sith who didn't fight before. Does it need to be said that each battle in the Sith Tournament ends with a death of one of opponents? The Tournament ends when the only Sith remains alive.

Jedi Ivan accidentally appeared in the list of the participants in the Sith Tournament. However, his skills in the Light Side of the Force are so strong so he can influence the choice of participants either who start the Tournament or who take the loser's place after each battle. Of course, he won't miss his chance to take advantage of it. Help him to calculate the probability of his victory.

## 样例 #1

### 输入

```
3
0.0 0.5 0.8
0.5 0.0 0.4
0.2 0.6 0.0
```

### 输出

```
0.680000000000000
```

# 题解

## 作者：_edge_ (赞：10)

另外的题解没解释清楚这道题目。

感觉这道还是挺好的。

考虑进行倒着 DP，因为正着不太好进行处理。

如果是正着进行处理的话，会发现有些奇奇怪怪的情况。

倒着进行 DP 的话可以考虑列出状态，$f_{i,j}$ 表示在 $i$ 这个集合里面，$j$ 在目前是擂主，显然当前如果想要 $1$ 号赢，就必然最后擂主是他。

为了方便一点，我们列状态的时候 $i$ 中那一位为 $1$ 的话，表示他还活着，否则代表他已经被淘汰掉了。

对于最后的，我们要枚举一开始谁是擂主。

转移方程式为在 $i$ 这个集合里面任选两个进行决斗，具体代码如下：

`f[i][k]=max(f[i][k],f[i-(1<<j)][k]*p[k][j]+f[i-(1<<k)][j]*p[j][k]);`

第一个表示 $k$ 击败了 $j$ ，然后后面的状态擂主是 $k$，第二个表示 $j$ 击败了当前擂主，后面状态擂主为 $j$。

并不是为了写题解而写，而是想让更多的人更好地理解这道题目。

复杂度 $O(2^n \times n^2)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=20;
int n;
double p[INF][INF];
double f[1<<INF][INF];
signed main()
{
//	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin>>p[i][j];
	f[1][0]=1;
	for (int i=2;i<(1<<n);i++) {
		for (int k=0;k<n;k++) {
			if (!(i&(1<<k))) continue;
			for (int j=0;j<n;j++) {
				if (!(i&(1<<j))) continue;
				if (j==k) continue;
				f[i][k]=max(f[i][k],f[i-(1<<j)][k]*p[k][j]+f[i-(1<<k)][j]*p[j][k]);
//				cout<<f[i][k]<<" "<<i<<" "<<k<<" "<<j<<" "<<f[i-(1<<j)][k]<<" over\n";
			}
		}
	}
	double ans=0;
	for (int i=0;i<n;i++)
		ans=max(ans,f[(1<<n)-1][i]);
	printf("%.19lf\n",ans);
	return 0;
}
```


---

## 作者：Iamacat (赞：8)

今天模拟赛上做了这道题，状压写爆了想写贪心混混分（本来期望得分0），没想到就这么水过去了.....

```cpp
//n^3贪心，求hack
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define gc getchar()
#define inf 999999999
#define ma
#define mo
using namespace std;
inline ll R()
{
	ll an=0,k=1;char c=gc;
	while(c<'0'||c>'9'){if(c=='-')k=-1;c=gc;}
	while(c>='0'&&c<='9')an=an*10+c-'0',c=gc;
	return an*k; 
}//可以无视的读优 
double a[20][20],an[20];//an表示选i个数（含1），1胜出概率 
int b[20],p[20];//b表示选出的决斗序列，越靠后越先进行决斗	p表示是否已选 
int main()
{
	int n=R();double ct,cnt;
	p[1]=1;b[1]=1;an[1]=1;//初始化 
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%lf",&a[i][j]);
	for(int i=2;i<=n;i++)
	{
		for(int j=2;j<=n;j++)if(!p[j])//找一个没在队列中的人 
		{
			ct=1;cnt=0;//ct为到达k去的概率	cnt为选j时1胜出的概率 
			for(int k=i-1;k;k--)//选第i个人为j，倒序模拟比赛过程 
			{
				cnt+=ct*a[b[k]][j]*an[k];//若在第k个人时输了，1的胜率加上只看前k人时1的胜率乘上ct
				ct*=a[j][b[k]];//ct乘上j赢过第k个人的概率 
			}
			if(cnt>an[i])an[i]=cnt,b[i]=j;
		}p[b[i]]=1;
	}
	printf("%.10lf",an[n]);
}
```

---

## 作者：Loop1st (赞：4)

### CF678E Another Sith Tournament
状压 dp，考虑 $dp_x$ 表示当前状态为 $x$ 时 $1$ 号获胜的概率，$x$ 二进制下第 $i-1$ 位为 $0$ 表示第 $i$ 个人被淘汰了，为 $1$ 表示第 $i$ 个人没被淘汰。

那么 $dp_x=\max(x\cap i\ne\varnothing,x\cap j\ne\varnothing,dp_{x-2^{i-1}}\times a_{j,i}+dp_{x-2^{j-1}}\times a_{i,j})$，这个也容易理解，就是 $i$ 输了之后 $1$ 号获胜的概率和 $j$ 输了之后 $1$ 号获胜的概率之和。最终答案为 $dp_{2^{n-1}}$。

时间复杂度 $O(2^n \times n^2)$。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 19;
typedef long long ll;
typedef pair<int, int> pii;
template <class T>
void cmax(T &x, T y) { x = max(x, y); }
int n;
double a[N][N], dp[1 << N]; //dp[x]: 当前状态为 x 时 1 号获胜的概率, 0 为已经被淘汰, 1 为未被淘汰
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++) scanf("%lf", &a[i][j]);
    dp[0] = 0.0;
    dp[1] = 1.0;
    for (int i = 2; i <= ((1 << n) - 1); i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (j != k && (i & (1 << (j - 1))) && (i & (1 << (k - 1)))) {
                    cmax(dp[i], dp[i - (1 << (j - 1))] * a[k][j] + dp[i - (1 << (k - 1))] * a[j][k]);
                }
            }
        } 
    }
    printf("%.10lf", dp[(1 << n) - 1]);
    return 0;
}
```

---

## 作者：ilibilib (赞：2)

前言：写了几道数位 DP 后发现用记搜做大部分题都比直接做自然很多欸。

## 分析：

数据范围看得出是状压，用 $x$ 表示当前人物存活状态（编号直接从 $0$ 开始，也就是说我是 $0$..）。$dp_x$ 为 $x$ 状态下我获胜的概率。

如果 $x=1$，显然只有我，我获胜的概率就为 $1$。

如果 $x$ 为偶数，显然没有我，我获胜的概率就为 $0$。

如果我们让当先存活的两个人 $i$ 和 $j$ 打架，有 $a_{i,j}$ 的概率 $j$ 被 $i$ 打死了，有 $a_{j,i}$ 的概率 $i$ 被 $j$ 打死了，也就是说 ：

$$dp_x=a_{i,j}\times dp_A+a_{j,i}\times dp_B$$
其中 $A$ 表示从 $x$ 中剔除了 $j$ 的状态，$B$ 表示从 $x$ 中剔除了 $i$ 的状态。

对 $x$ 取每一对 $i,j$ 下的最大值即可。

## code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20;
typedef double db;
int n;
bool vis[1<<N];
db tu[N][N],dp[1<<N];
db dfs(int x)
{
    if(!(x&1)) return 0;
    if(x==1) return 1;
    if(vis[x]) return dp[x];
    for(int i=0;i<n;++i)
        if(x&(1<<i))
            for(int j=0;j<n;++j)
                if((x&(1<<j))&&i!=j)
                    dp[x]=max(dp[x],dfs(x^(1<<i))*tu[j][i]+dfs(x^(1<<j))*tu[i][j]);
    vis[x]=true;
    return dp[x];
}
int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            cin>>tu[i][j];
    printf("%.7lf",dfs((1<<n)-1));
    return 0;
}
```

---

## 作者：spire001 (赞：2)

## CF678E 题解

### 前言
因为发现题解里的状态转移方程都一模一样，所以写了方程不太一样的题解。

### 思路

这个题目第一眼看到有很多想法。

比较逆天一点的就是对擂台顺序模拟退火每次动态规划计算取最优值。  
比较正规一点的就是状态压缩求解。
这个题解选择的是后者。

首先这个题目看起来是概率，实际上每一步过程除了你选择的骑士决斗结果你都是可以确定的。

考虑是正推还是反推，无论正推还是反推，最自然的想法是对生存情况进行状态压缩。  
如果这样设置状态的话，如果正推，开始所有人存活，答案是什么你并不知道，于是你必然选择反推。

考虑反推，$dp_{n, state}$ 表示第 $n$ 个人在 $state$ 状态下与其他人决斗（这说明了 $state$ 状态必然包含了 $n$）后 $1$ 号骑士获胜的概率。

状态转移方程为：
$$
dp_{p, st \cup p} = \max\{j\cap st\neq\emptyset,p\cap st=\emptyset|~dp_{j, st}\times f_{j,p}+dp_{p,(st \cup p)/ j}\times f_{p,j}\}
$$

形象的解释一下，假设安排了 $j,p$ 对战，$p$ 当擂主的概率可以表示为 $p$ 本来就是擂主，他守擂成功的概率和 $p$ 挑战擂主 $j$ 成功的概率。  
由于 $1$ 号骑士作为天选之子可以选择人对决，所以需要取最大值。

那么就可以写出代码。。。


```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int N = 18;

int n;
double dp[N + 1][1 << N];
double f[N + 1][N + 1];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n; (cout << fixed).precision(8); // 保留 8 位小数

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> f[i][j];
  
  const int x = 1 << n; // 子集数

  dp[1][1] = 1; // 最后 1 号是唯一存在的

  for (int i = 1; i != x; i++)  
    for (int j = 1; j <= n; j++)
      if (i & (1 << (j - 1))) // 枚举 j 拿过
        for (int p = 1; p <= n; p++)
          if (!(i & (1 << (p - 1)))) // 枚举 p 没拿过
            dp[p][i ^ (1 << (p - 1))] = max(dp[p][i ^ (1 << (p - 1))], dp[j][i] * f[j][p] + dp[p][i ^ (1 << (p - 1)) ^ (1 << (j - 1))] * f[p][j]); // 状态转移
        
  double ans = 0;
  for (int i = 1; i <= n; i++) ans = max(ans, dp[i][x - 1]); // 最终状态所有人都活着

  cout << ans << endl;

  return 0;
}
```

从代码上来看，和其他题解思路差不太多，但是从其他题解的解说来看，这篇题解的方程似乎更利于理解？

---

## 作者：Lgx_Q (赞：2)

这题可以算是根据状压模板衍生出来的比较畸形的题目。

我一开始的想法是设 $f_{i,j}$ 表示在骑士集合为 $i$ 的骑士中，$j$ 胜利的最大概率。

这个想法看似正确，实际在转移的时候出现了困难，因为概率本应该相加，但是和取 $\operatorname{max}$ 有点混淆，以及还会出现其他奇奇怪怪的问题。

仔细观察题目，因为在每一步骑士决斗后，我们都能知道结果，并选择下一次的决策（即：选择哪个骑士和上一次胜利的骑士决斗）。这可能就有点类似博弈论了，就像玩游戏，每一步都做出一定的选择。

尝试利用博弈论的方法倒序 DP。实际我们没必要存一维表示哪个骑士胜利，不难想到 $f_{i,j}$ 表示上一次胜利的骑士是 $j$，目前还需要和集合为 $i$ 的骑士决斗，最后骑士 $1$ 获得胜利的最大概率。

转移：枚举 $j$ 需要的决斗对象 $k$，$j$ 赢的贡献为 $a_{j,k}\times f_{i-k,j}$，$k$ 赢的贡献为 $a_{k,j}\times f_{i-k,j}$，两者之和即为总贡献，从所有可能的 $k$ 中取个最大值即可。

初始化 $f_{\text{空集},1}=1$。

计算答案：枚举每个 $i$，从每个可能的 $i$ 中取 $f_{\{1,2,3,...n\}-i,i}$ 的最大值。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=19;
ll n;
double a[maxn][maxn],f[1<<18][maxn];
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++) scanf("%lf",&a[i][j]);
	f[0][1]=1;
	for(ll i=1;i<(1<<n);i++)
	{
		for(ll j=1;j<=n;j++)
			if(i&(1<<j-1)^1)
			{
				for(ll k=1;k<=n;k++)
					if(i&(1<<k-1))
					{
						f[i][j]=max(f[i][j],a[j][k]*f[i^(1<<k-1)][j]+a[k][j]*f[i^(1<<k-1)][k]);
					}
			}
	}
	double ans=0;
	for(ll i=1;i<=n;i++) ans=max(ans,f[((1<<n)-1)^(1<<i-1)][i]);
	printf("%lf",ans);
	return 0;
}//
```

---

## 作者：kfhkx (赞：2)

看见没有题解，就来一波吧~

题意：

锦标赛共有N（1<=n<=18)个人参加，共进行N-1轮。
第一轮随机挑选两名选手进行决斗，胜者进入下一轮的比赛，第二轮到第N-1轮再每轮随机挑选1名选手与上一轮胜利的选手决斗，最后只剩一轮选手。第i名选手与第j名选手决斗，第i名选手胜利的概率是a[i][j].

作为一号选手的Jedi Ivan想知道如何安排每轮出场的选手可以使得他获胜的概率最大，并求出这个最大概率。

做法：

看到n那么小，第一感觉就是状压dp（正解就是)

所以我们可以设状态1表示第i个人还在场,0表示已经gg了。 

设F[k][i]表示状态为k时，第i个选手的获胜概率。 

转移方程很显然

双重循环 

对于每一个状态乘上他对应的概率 
最后记录答案，取max(ans,f[b[n]-1][i]）;
（b[n]记录$2^n$）


------------
### CF678E.pas
```pascal
var
        n,i,j,k,l:longint;
        ans:real;
        a,f:array[0..300000,0..30] of real;
        b:array[0..500] of longint;
function max(x,y:real):real;
begin
        if x>y then exit(x) else exit(y);
end;
begin
        assign(input,'jjj.in');reset(input);
        assign(output,'jjj.out');rewrite(output);
        readln(n);
        b[0]:=1;
        for i:=1 to n do for j:=1 to n do read(a[i,j]);
        for i:=1 to 18 do b[i]:=b[i-1]<<1;
        f[1,1]:=1;
        for k:=1 to b[n]-1 do
         for i:=1 to n do
          if (((1<<(i-1)) and k)<>0) then
           for j:=1 to n do
            if (((1<<(j-1)) and k)<>0) then
             f[k,i]:=max(f[k,i],f[k-(1<<(j-1)),i]*a[i,j]+f[k-(1<<(i-1)),j]*a[j,i]);
        for i:=1 to n do ans:=max(ans,f[b[n]-1,i]);
        writeln(ans:0:7);//开了7位，其实误差不超过0.00001就行
end.
```


------------

### CF678E.cpp
```
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#define fo(i,a,b) for (int i=a;i<=b;i++)
#define N 30
using namespace std;
const int Two=300000;
int n;
double a[N][N],F[Two][N],ans=0;
int b[N];
int main()
{
    scanf("%d",&n);
    fo(i,1,n) 
    	fo(j,1,n) scanf("%lf",&a[i][j]);
    two[0]=1;
    fo(i,1,18) b[i]=two[i-1]*2;
    F[1][1]=1;
    fo(k,1,b[n]-1) 
    {
        fo(i,1,n) if(((1<<(i-1))&k)!=0)
        	fo(j,1,n) if(((1<<(j-1))&k)!=0)
          		F[k][i]=max(F[k][i],F[k-(1<<(j-1))][i]*a[i][j]+F[k-(1<<(i-1))][j]*a[j][i]);
    }
    fo(i,1,n) ans=max(ans,F[b[n]-1][i]);
    printf("%.7lf",ans);
}

```


------------



---

## 作者：Demoe (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF678E)

### $\text{Description}$

- 给定一个 $n\times n$ 的矩阵，其中 $a_{i,j}$ 表示 $i$ 击杀 $j$ 的概率，问通过排列决斗顺序，最后只留下 $1$ 的最大概率。

### $\text{Solution}$

一看到 $n\le 18$ 就觉得肯定是 $2^n$ 或者 $\dfrac{n}{2}!$ 类似的东西。

这题一看就很状压（确信）。

考虑 $f_s$ 为当前状态为 $s$ 的赢的最大概率，其中 $s$ 表示有哪些人已经参与了决斗。

初始状态 $f_{\{1\}}=1$。

有转移方程 $f_s=\max\{f_{s/\{i\}}\times a_{j,i}+f_{s/\{j\}}\times a_{i,j}|i,j\in s\}$。

意义为 $j$ 把 $i$ 杀了的概率加上 $i$ 把 $j$ 杀了的概率。

答案即为 $f_{\{i|i\in N\&i\in[1,n]\}}$。

时间复杂度 $O(n^22^n)$，可以通过本题。

### $\text{Code}$

```cpp
// wish to get better qwq

#include<bits/stdc++.h>
#define re register int
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
#define dec(x) fixed<<setprecision(x)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

template<class T> inline void rd(T &x){
	int fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
template<class T> inline void wr(T x){
	if(x<0) x=-x,putchar('-');
	if(x<10){putchar(x+'0');return ;}
	int tmp[30]={0},cnt=0;
	while(x) tmp[cnt++]=x%10,x/=10;
	for(re i=cnt-1;i>=0;--i) putchar(tmp[i]+'0');
}

// ---------- IO ---------- //

const int N=19;
int n;
double a[N][N],f[(1<<N)+5];

// ----------  ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(re i=0;i<n;++i)
		for(re j=0;j<n;++j) cin>>a[i][j];
	f[1]=1.0;
	for(re s=2;s<(1<<n);++s)
		for(re i=0;i<n;++i)
			if(s&(1<<i))
				for(re j=i+1;j<n;++j)
					if(s&(1<<j)) f[s]=max(f[s],f[s^(1<<i)]*a[j][i]+f[s^(1<<j)]*a[i][j]);
	cout<<dec(7)<<f[(1<<n)-1];
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：「已注销」 (赞：0)

`状压DP`，`f[S]`表示当前比赛的人的集合为`S`时的最大胜率

把集合$S$用一个二进制数表示，第$i$位为$1$表示第$i$个人在比赛中，否则表示他被淘汰

转移：若$i\in S$且$j\in S$，`f[S]=max(f[S],p[j][i]*f[S^(1<<i)]+p[i][j]*f[S^(1<<j)])`

时间复杂度$\mathcal O(n^2\cdot2^n)$，空间复杂度$\mathcal O(2^n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double p[18][18],f[1<<18];
int main(){
    f[1]=1;// 只有第一个人活着，胜率为1
    cin>>n;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            cin>>p[i][j];// i赢j的概率
    for(int S=2;S<(1<<n);++S)// 枚举状态
        for(int i=0;i<n-1;++i)if(S>>i&1)// i还活着
            for(int j=i+1;j<n;++j)if(S>>j&1)// j还活着
                f[S]=max(f[S],f[S^(1<<i)]*p[j][i]+f[S^(1<<j)]*p[i][j]);// j赢i的概率*i被打败的答案+i赢j的概率*j被打败的答案
    cout<<f[(1<<n)-1];// 最终答案即为起始状态
}
```

---

## 作者：ifffer_2137 (赞：0)

好水的紫……建议降绿吧。
### 题意
$n$ 个骑士进行决斗，每两人之间的胜负概率给定。你是 $1$ 号，可以安排决斗顺序，实行擂台制，问你胜利的最大概率。
### 分析
这个数据范围……一眼状压 DP 吧。

设计状态，$f_{i,j}$ 表示当前存活状态为 $i$，擂台上为 $j$ 号骑士，接下来胜利的最大概率。然后我们枚举下一个参与决斗的骑士编号，需要满足其存活，并且不为 $j$，然后就可以容易地推出转移：
$$f_{i,j}=\max_{k\in i,k\neq j}a_{k,j}f_{i\oplus2^j,k}+a_{j,k}f_{i\oplus2^k,j}$$
然后注意一下边界，如果当前 $1$ 号已经死了就为 $0$，只有一号活着就为 $1$。

求答案的时候枚举第一个上擂台的人，取个最大就好。时间复杂度 $\mathcal O(2^nn^2)$。

代码写的记搜，个人感觉比较好写。
### 代码
```cpp
double dfs(int s,int x){
	if(f[s][x]+eps>=0) return f[s][x];
	if((s&1)==0) return 0.0;
	if((s&(s-1))==0&&!x) return 1.0;
	for(int i=0;i<n;i++){
		if(i==x||(s&(1<<i))==0) continue;
		f[s][x]=max(f[s][x],a[i][x]*dfs(s^(1<<x),i)+a[x][i]*dfs(s^(1<<i),x));
	}
	return f[s][x];
}
signed main(){
	n=read();
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%lf",&a[i][j]);
	for(int i=0;i<(1<<n);i++) for(int j=0;j<n;j++) f[i][j]=-1.0;
	for(int i=0;i<n;i++) ans=max(ans,dfs((1<<n)-1,i));
	printf("%.10lf\n",ans);
	return 0;
}
```

---

