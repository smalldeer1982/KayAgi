# [ABC154E] Almost Everywhere Zero

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc154/tasks/abc154_e

$ 1 $ 以上 $ N $ 以下の整数であって、 $ 10 $ 進法で表したときに、$ 0 $ でない数字がちょうど $ K $ 個あるようなものの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ <\ 10^{100} $
- $ 1\ \leq\ K\ \leq\ 3 $

### Sample Explanation 1

条件を満たす数は次の $ 19 $ 個です。 - $ 1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100 $

### Sample Explanation 2

条件を満たす数は次の $ 14 $ 個です。 - $ 11,12,13,14,15,16,17,18,19,21,22,23,24,25 $

## 样例 #1

### 输入

```
100
1```

### 输出

```
19```

## 样例 #2

### 输入

```
25
2```

### 输出

```
14```

## 样例 #3

### 输入

```
314159
2```

### 输出

```
937```

## 样例 #4

### 输入

```
9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
3```

### 输出

```
117879300```

# 题解

## 作者：紊莫 (赞：5)

## Part 1 思路--从暴力到满分

先说最无脑的做法，暴力用高精一个个累加计算，不仅繁琐，而且很慢。  

但是思考这种做法的本质，其实就是对每一个数字的遍历，不妨换一种方法，那么就可以引出主角：数位 DP。对于最基本的记搜框架，可以自行百度。

用搜索的方法，改成按**位**去枚举每个**数位**。可以写出朴素的搜索（甚至加了剪枝）。  

```cpp
int dfs(int p,int flag,int cnt){
	if(p>m) return cnt==k;
	if(cnt>k) return 0;
	int _F=0;
	for(int i=0;i<=(flag?a[p]:9);i++)
		_F+=dfs(p+1,flag&&i==a[p],cnt+(i!=0));
	return _F;
}
```

然而改成这样并没有什么复杂度的优化。  

进一步想到位数和数字总出现次数能构成的可能并不多，即**状态空间**很小。那么就可以加上一个记忆化的操作来降低复杂度。  

```cpp
#define _F f[p][flag][cnt]
int f[105][2][20];
int dfs(int p,int flag,int cnt){
	if(p>m) return cnt==k;
	if(_F!=-1) return _F;
	if(cnt>k) return 0;
	_F=0;
	for(int i=0;i<=(flag?a[p]:9);i++)
		_F+=dfs(p+1,flag&&i==a[p],cnt+(i!=0));
	return _F;
}
```  

于是就过啦！  

## Part 2 参考程序

注：篇幅受限，且程序**仅供参考**，所以去掉了快读，保证代码正确。  

```cpp
//Author: Velvet on Luogu(uid=443675)
#include <bits/stdc++.h>
#define int long long
#define _F f[p][flag][cnt]
using namespace std;
int m,a[105],k;
int f[105][2][20];
int dfs(int p,int flag,int cnt){
	if(p>m) return cnt==k;
	if(_F!=-1) return _F;
	if(cnt>k) return 0;
	_F=0;
	for(int i=0;i<=(flag?a[p]:9);i++)
		_F+=dfs(p+1,flag&&i==a[p],cnt+(i!=0));
	return _F;
}
signed main(){
	string n;cin>>n>>k;
	memset(f,-1,sizeof f);
	for(int i=0;i<n.size();i++)
		a[i+1]=n[i]-'0';
	m=n.size();	
	writeln(dfs(1,1,0));
    return 0;
}
```



---

## 作者：HoshizoraZ (赞：3)

一道很简单的数位 DP。

记 $dp[i][j][0/1]$ 为当前从高到低第 $i$ 位，已经有 $j$ 个非零数位，当前是 / 否处于有数位比 $N$ 对应数位小的方案数。

针对第三维状态解释一下：

当 $N=20123$，那么如果从高到低枚举数位，第一位将枚举的是万位。

但是这个数需要不大于 $N$，所以万位只能取到 $0,1,2$，分两种情况。

- 当你万位取到 $0,1$ 时，千位就可以随便取，因为不管怎样这个数都不大于 $N$；
- 如果你取的是 $2$，那么万位就和 $N$ 的万位相同了，为了保证数字不大于 $N$，你的千位也不能大于 $N$ 的千位 $0$，以此类推。

所以这个第三维的作用就是判断当前能不能使用所有数位。

代码如下（本代码采用记忆化搜索）：

```cpp
#include <cstring>
#include <cstdio>
#define INF 1e9
#define eps 1e-6
typedef long long ll;

char c[210];
int k, n, dp[110][5][2];

int dfs(int now, int cnt, bool equalN){
	if(now == n + 1)
		return cnt == k;			// 刚好 k 位
	if(cnt > k)						// 超过 k 位了就剪掉
		return 0;
	if(dp[now][cnt][equalN] >= 0 && !equalN)	// 已经有状态则无需继续搜索
		return dp[now][cnt][equalN];
	
	int maxx = equalN ? c[now] - '0' : 9, sum = 0;
	// 如果 equalN = 1 就代表前面所有位都和 N 的相等，此时这一位也不能超过 N；否则任意位数都可以取到
   
	for(int i = 0; i <= maxx; i++)			// 继续搜索，统计答案
		sum += dfs(now + 1, cnt + (i != 0), equalN && (i == maxx));
	
	return dp[now][cnt][equalN] = sum;		// 记忆化
}

int main(){

	memset(dp, -1, sizeof(dp));				// 初始化
	scanf("%s\n%d", c + 1, &k);
	n = strlen(c + 1);
	printf("%d\n", dfs(1, 0, 1));

	return 0;
}
```

---

## 作者：peterwuyihong (赞：2)

题意：给定 $N,K$,求 $[1,N]$ 中有多少数非 $0$ 位正好有 $K$ 个，$1\le N\le10^{100},1\le K\le3$。

你用 $f_{i,j}$ 表示 $[0,10^i)$ 间 $j$ 个数位不为 $0$ 的情况数，考虑上前缀 $0$。那么

$$f_{i,j}=9f_{i-1,j-1}+f_{i-1,j},f_{0,0}=1$$

然后你倒着做即可。

```cpp
#define maxn 110
using i64 = long long;
int top,k;
char s[maxn];
i64 f[maxn][4],ans;
signed main(){
  cin>>s>>k;
  top=strlen(s);
  reverse(s,s+top);
  f[0][0]=1;
  rep(i,1,top){
    f[i][0]=1;
    rep(j,1,3)
    f[i][j]=9*f[i-1][j-1]+f[i-1][j];
  }
  int u=1;
  per(i,top-2,0){
    if(k>=u+1)rep(j,1,s[i]-'0'-1)ans+=f[i][k-u-1];
    if(k>=u&&s[i]!='0')ans+=f[i][k-u];
    if(s[i]!='0')u++;
  }
  ans+=(s[top-1]-'0'-1)*f[top-1][k-1];
  per(i,top-2,0)
    ans+=9*f[i][k-1];
  int flg=0;//左闭右开，要统计右边界 
  rep(i,0,top-1)if(s[i]!='0')flg++;
  if(flg==k)ans++;
  cout<<ans;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

经典的数位动态规划题。

数位DP的用处是来统计数字，但是只保存状态，数的长度，当前位置值和是否现在的数等于一个上线。

可以参考[这里](https://oi-wiki.org/dp/number/)的特别详细数位DP讲解。

在这个题目里，状态就是有多少个不是0的数位；DP公式就是直接这个数量转移。

需要注意这道题是直接在`string`类型操作应为数字有100位，所以需要把位置`i`做`s[i]-'0'`才可以得到第`i`位的数字。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

ll swdp[101][10][2][4]; // swdp[cdig][digit val][eq to q][nonzero]

#define SWDP_COND(prevdig, nexdig) if(max(prevdig-nexdig, nexdig-prevdig) >= 2)

// assuming there are no preceding zeroes

int K;

ll _solve_swdp(string s) {
    memset(swdp, 0, sizeof swdp);
    swdp[0][s[0]-'0'][1][s[0] != '0'] = 1;
    // change to 0 if can have preceding zeroes
    iter(d, 0, s[0]-'0') swdp[0][d][0][d != 0] = 1;
    rep1(dig, s.size()-1) {
        rep(pdval, 10) rep(dval, 10)
            rep(d, 4) if(d || !dval) swdp[dig][dval][0][d] += swdp[dig-1][pdval][0][d - (dval != 0)];
        rep(dval, s[dig]-'0')
            rep(d, 4) if(d || !dval) swdp[dig][dval][0][d] += swdp[dig-1][s[dig-1]-'0'][1][d - (dval != 0)];
        rep(d, 4) if(d || s[dig] == '0') swdp[dig][s[dig]-'0'][1][d] += swdp[dig-1][s[dig-1]-'0'][1][d - (s[dig] != '0')];
    }
    ll ans = 0; rep(dval, 10) ans += swdp[s.size()-1][dval][0][K] + swdp[s.size()-1][dval][1][K];
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s >> K;
    cout << _solve_swdp(s) << endl;
}

```

---

## 作者：OIerBoy (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc154_e)
### 前言
这是本蒟蒻第一次写数位 dp，发现题解里都写的记忆化，我就来写写正常的数位 dp 吧。
## 解析
这道题是一道很典型的数位 dp。

我们只需要不断的枚举它前面第 $i-1$ 位的状态，并枚举第 $i$ 位的数字 $\left[0,9\right]$ 的方案数统计即可。

我们可以定义 $f_{i,j,k}$ 中 $i$ 是当前执行到了第 $i$ 位，$j$ 是 $0/1$ 表示是否达到上限 $n$，$k$ 是枚举第 $i$ 位中有 $k$ 个非零整数，$f_{i,j,k}$ 就是当前共有多少种方案。

根据题意我们可以得到：

$f_{i,j,k}=\sum\limits_{l=0}^{k}f_{i-1,0,l}+f_{i-1,1,l}+f_{i-1,0,l-1}+f_{i-1,1,l-1}$

详细细节可以参考代码。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long K,n,a[1000];
long long f[10005][2][10];
string x;
int main(){
	cin>>x>>K;
	x=' '+x;n=x.size()-1;
	for(int i=1;i<=n;i++)a[i]=x[i]-'0';
	f[0][1][0]=1;	//给f赋初值
	for(int i=0;i<n;i++)	//枚举1~n的前一位
	for(int j=0;j<=1;j++)	//枚举是否达到上限
	for(int k=0;k<=K;k++)	//枚举非零整数的个数
	for(int l=0;l<10;l++){	//枚举第i+1位的整数
		if(j==1&&l>a[i+1])break;	//如果达到上限且大于i+1位则退出
		if(k==K&&l>0)break;	//如果已经有k个非零整数且l非零则退出
		long long nk=k+(l!=0),nj=(j==1&&a[i+1]==l);	//判断非零整数及是否达到上限
		f[i+1][nj][nk]+=f[i][j][k];	//转移
	}cout<<f[n][0][K]+f[n][1][K];	//输出没达到上限的方案和达到的方案
	return 0;
}
```


---

## 作者：StevenLiTheOIer (赞：0)

## 思路：
数位 dp。设计状态 $dp_{i,0/1,k}$ 表示当前考虑了最高 $i$ 位，是否达到上界（第二维为 $1$ 表示达到上界），其中有 $k$ 位有非零数字的方案总数。

首先排除非法的转移。以下用 $N_i$ 表示输入 $N$ 的第 $i$ 位。
+ 如果已经达到上界，则第 $i$ 位至多能填 $N_i$，超过 $N_i$ 则非法。
+ 如果当前已经有 $K$ 个数非零，第 $i$ 位非零，则不合题意。

以上情况都可以在转移前排除。

接下来推转移方程：设新的状态为 $dp_{newi,newj,newk}$，不难得出 $newi=i+1$。如果第 $i$ 位非零，则 $newk=k+1$。如果前几位都达到上界且当前位也达到上界，则 $newj=1$，反之 $newj=0$。

综上，状态转移方程为：
```cpp
dp[i + 1][j && (l == N[i] - '0')][k + (bool) l] += dp[i][j][k];
```
最终答案为 $dp_{n,0,K}+dp_{n,1,K}$。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long dp[106][2][4];
string N;
int main()
{
	int K;
	cin >> N >> K;
	int n = N.size();
	dp[0][1][0] = 1;
	for (int i = 0; i < n; i++) //当前位 
	{
		for (int j = 0; j <= 1; j++) //是否达到上界 
		{
			for (int k = 0; k <= 3; k++) //当前非零个数 
			{
				for (int l = 0; l <= 9; l++) //将要填的数 
				{
					if (j && l > N[i] - '0') continue;
					if (k == K && l) continue; //排除非法情况 
					dp[i + 1][j && (l == N[i] - '0')][k + (bool) l] += dp[i][j][k];
				}
			}
		}
	}
	cout << dp[n][0][K] + dp[n][1][K] << endl;
	return 0;
}
```

---

## 作者：hello_world_djh (赞：0)

本蒟蒻第 $70$ 道蓝题祭！

进入正题：

因为这个题目只关心有多少位非零数位，再加上 $n \le 10^{100}$ $k \le 3$ 的数据，可以看出这个题目是数位 dp。

只需要注意几个小细节即可：

1. 我们可以加一个最优性剪枝，如果非零位超过 $k$ 个就直接返回 $0$。因为接下来无论怎么填都不可能是一个正确的解。

1. 注意只要非零数位个数超过 $k$ 的长度就要退出，无论是不是一个正确的解。

1. 注意存 $n$ 的时候用高精度。

代码：

```cpp
#include <bits/stdc++.h>
//省略快读

typedef long long ll;
std::string n;
int k, num[110], len;
ll f[110][110][2];

ll dp(int now, int cnt, bool limit) {
    if (cnt > k)
        return 0;
    if (now > len)
        return cnt == k;
    if (f[now][cnt][limit] != -1)
        return f[now][cnt][limit];
    int MAX = limit ? num[now] : 9;
    ll res = 0;
    for (int i = 0; i <= MAX; i++)
        res += dp(now + 1, cnt + (i != 0), limit && (i == MAX));
    return f[now][cnt][limit] = res;
}

ll sol(std::string n) {
    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 110; j++)
            for (int k = 0; k < 2; k++)
                    f[i][j][k] = -1;
    len = n.size();
    for (int i = 0; i < n.size(); i++)
        num[i + 1] = n[i] - '0';
    return dp(1, 0, true);
}

int main() {
    std::cin >> n;
    k = read<int>();
    printf("%lld\n", sol(n));
    return 0;
}
```

---

## 作者：Lagerent (赞：0)

数位 dp。

设 $N = \overline{a_na_{n - 1}...a_2a_1}$，状态 $f_{pos, k, tag}$ 为当前从高位到低位已经填好前 $pos - 1$ 位，已经有的非零位数为 $k$，且上界状态为 $tag$ 的情况。

对于 $tag$ 的解释，请看下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/acmetgdt.png?x-oss-process=image/resize,m_lfit,h_400,w_1000)

设我们当前正在填第 $pos$ 位，那么当第 $pos - 1$ 位填了 $x \in[0, a_{pos} - 1]$ 时，我们无论怎样填第 $pos$ 位，都不会超过 $N$，而当第 $pos - 1$ 位填了 $a_{pos - 1}$ 达到上界时，我们为了整个数不超过 $N$，第 $pos$ 位只能填 $x \in [0, a_{pos}]$。

所以 $tag$ 的作用是标记我们当前可以随便填还是只能填 $[0, a_{pos}]$ 之间的数。

记忆化搜索实现 dp 即可。

## Code
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(a, b, c) for(int (a) = (b); (a) <= (c); ++ (a))
#define per(a, b, c) for(int (a) = (b); (a) >= (c); -- (a))
#define Rep(a, b, c) for(int (a) = (b); (a) < (c); ++ (a))
#define Per(a, b, c) for(int (a) = (b); (a) > (c); -- (a))
#define il inline
#define inf 0x3f3f3f3f
using namespace std;

il int read() {
   int x = 0, f = 1; char ch = getchar();
   while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
   while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48),  ch = getchar();
   return x * f;
}

const int N = 110;

char str[N];
int K, a[N], f[N][N][2];

int dfs(int pos, int k, int tag) {
	int &v = f[pos][k][tag];
	if(v != -1) return v;
	if(k == K) return v = 1;
	if(!pos) return v = 0;
	int end = tag ? a[pos] : 9;
	int res = 0;
	rep(i, 0, end) res += dfs(pos - 1, k + (i != 0), tag & (i == a[pos]));
	return v = res;
}

int main() {
	scanf("%s%d", str + 1, &K);
	int n = strlen(str + 1);
	rep(i, 1, n) a[i] = str[n - i + 1] - '0';
	memset(f, -1, sizeof f);
	printf("%d\n", dfs(n, 0, 1)); // 当前要填第 n 位，已经有了 0 个非零数，并且最高只能填到上界。
	return 0;
}
```

---

## 作者：SSER_ZRQ (赞：0)

## 题目描述：
给定 $n$ 与 $k$, 求 $[1,n]$ 中有多少数非零位正好有 $k$ 个。

数据范围： $ 1 \le n \le 10^{100}$,$ 1 \le k \le 3$。

## 题解：

看到 $n$ 的数据范围比较大，考虑数位 DP。

约定：对于一个 $n$ 位整数 $\overline{a_1a_2...a_n}$, 第一个数是 $a_1$, 第二个数是 $a_2$, 以此类推，第 $n$ 个数是 $a_n$。

用数组 $a$ 记录 $n$, 从前往后第 $i$ 个数是啥。

我们记录 $f_{i,j}$ 前 $i-1$ 个数有 $j$ 个非零数时，整个大数有 $k$ 个非零数位的个数。

数位 DP 使用记忆化搜索十分好实现。

我们在 dfs 中记录三个变量：$ x, y, p$，分别表示搜到第 $x$ 个数 ，前 $x-1$ 有 $y$ 位非零位，$p$ 表示是否贴着上界。

如果 $p=0$, 这一位只能在 $[0,a_x]$ 中取。否则，可以在 $[0,9]$ 中取。

**重要的一点：只有在 $ p=0$ 时才能进行记忆化（包括返回）。**

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int n,m,a[N],f[N][N];
char s[N];
int dfs(int x,int y,int p){
	if(x==0) return y==m?1:0;
	if(p&&~f[x][y]) return f[x][y];
	//p=1 才能记忆化 
	int res=0,k=9,q=0,l=0;
	if(!p) k=min(a[x],k);
	for(int i=0;i<=k;i++){
		q=i==0?0:1,l=i==a[x]?0:1;
		//q表示 这一位选的是否是非零数
		//l表示 是否还贴着上界 
		res=res+dfs(x-1,y+q,p|l);
	}
	if(p) f[x][y]=res;
	//p=1 才能记忆化 
	return res;
}
int main(){
	memset(f,-1,sizeof(f));
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		a[n-i+1]=s[i]-'0';
		//记录a数组 
	}
	printf("%d\n",dfs(n,0,0));
	return 0;
}

```




---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4815)

注：本篇题解手把手教你写数位 $\verb!DP!$。
## 思路
我们记变量 $f_{pos,k}$ 为从最后一位到第 $pos$ 位非零数位个数和恰好等于 $k$ 的数的个数。

数位 $\verb!DP!$ 通常是使用 $\verb!dfs!$ 转移的。

我们在 $\verb!dfs!$ 中记录四个变量：$\verb!pos,tag,k,zero!$，分别表示第几位，是否贴着上界，非零数位个数，是否为前导零。

$\verb!dfs!$ 部分代码（带有详细注释）：
```cpp
inline int dfs(int pos,int k,int tag,int zero){
    if (k==k1) return 1;//如果非零数位已经填完了，接下来一定填 0，所以只有一种情况，可以直接退出
    if (!pos || k>k1) return 0;//如果位数用完了还没填到 k1 个非零数位，或者非零数位已经多了，也直接退出
    if (!tag && !zero && ~f[pos][k]) return f[pos][k];//如果没有任何特殊限制，且这个状态搜过了，没必要再搜
    int end=tag? a[pos]:9;//如果贴着上界，我们只能到 a[pos]，不然可以到 9
    int res=0;
    for (rint i=0;i<=end;++i) res+=dfs(pos-1,k+(i!=0),tag&(i==end),zero&(!i));//转移
    if (!tag && !zero) f[pos][k]=res;//如果没有特殊限制，我们可以记忆化一下
    return res;
}
```
## 代码
全部代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=2e3+10;
int f[N][N],k1,a[N];
inline int dfs(int pos,int k,int tag,int zero){
    if (k==k1) return 1;
    if (!pos || k>k1) return 0;
    if (!tag && !zero && ~f[pos][k]) return f[pos][k];
    int end=tag? a[pos]:9;
    int res=0;
    for (rint i=0;i<=end;++i) res+=dfs(pos-1,k+(i!=0),tag&(i==end),zero&(!i));
    if (!tag && !zero) f[pos][k]=res;
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    string s;cin>>s;
    int n=s.length();s=" "+s;
    cin>>k1;
    for (rint i=1;i<=n;++i) a[i]=s[n-i+1]-'0';//把 s 序列翻转一下，变成从低位到高位
    memset(f,-1,sizeof(f));
    cout<<dfs(n,0,1,1)<<'\n';
    return 0;
}

```


---

## 作者：Jairon314 (赞：0)

> [题目链接](https://atcoder.jp/contests/abc154/tasks/abc154_e)

$ Solution $

------------

数位 dp 裸题，设 $ dp_{i,k,less} $ 表示到第 $i$ 个数位有 $ k$ 个位置非零是否比上界小的满足条件的个数，$c$ 为上界的当前数位上的数。

易得转移方程：

$$ dp_{i,k,less}=\sum_{r=0}^9 dp_{i-1,k+[r!=0],less|(r<c)} $$

使用记忆化搜索转移

[AC记录](https://atcoder.jp/contests/abc154/submissions/29217931)

代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
using namespace std;

#define int long long

/***** Fast_IO *****/

using vii = vector<int>;
using pii = pair<int,int>;

namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;

	#define gc getchar
	#define pc putchar

	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}

	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}

	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
	
	template<class I>
	inline void chmax(I &x,I y){ return x=max(x,y),void(); }
	
	template<class I>
	inline void chmin(I &x,I y){ return x=min(x,y),void(); }

	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define all(v) (v).begin(),(v).end()
	#define each(i,v) for(auto &i:v)
	#define umap unordered_map
	#define sqr(k) ((k)*(k))
	#define inf 0x3f3f3f3f3f3f
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
	#define db double
}using namespace IO;

/***** Fast_IO *****/

#define maxn 1000010
#define SIZE 5010

vii dig;
int mem[110][110][110];
string s;

int n,k;

int dfs(int pos,int K,int less){
	if(k<K){ return 0; }
	if(k==K){ return 1; }
	if(pos==0){ return 0; }
	int res=0;
	if(mem[pos][K][less]!=-1){
		return mem[pos][K][less];
	} char c=s[n-pos]-'0';
	FOR(i,0,9){
		if(!less&&i>c){ continue; }
		res+=dfs(pos-1,K+(i!=0),less||(i<c));
	} return mem[pos][K][less]=res;
}

int solve(){
	memset(mem,-1,sizeof mem);
	return dfs((int)n,0,0);
}

signed main(){
	cin>>s; read(k);
	n=(int)s.length();
	outn( solve() );
	return 0;
}
```


---

