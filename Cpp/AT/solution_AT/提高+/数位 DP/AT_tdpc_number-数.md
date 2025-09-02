# 数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_number


$N$ 以下の正整数であって、十進法表記したときの各桁の数の和が $D$ の倍数であるものの個数を mod 1,000,000,007 で求めよ。

## 说明/提示

### Constraints

- $ 1 \le N \le 10^{10000} $
- $ 1 \le D \le 100 $

### Sample Explanation 1

1 以上 100 以下の 3 の倍数 33 個が条件を満たす。


## 样例 #1

### 输入

```
3
100```

### 输出

```
33```

## 样例 #2

### 输入

```
7
123456789012345678901234567890```

### 输出

```
468357804```

# 题解

## 作者：Brilliant11001 (赞：5)

### [更好的阅读体验](https://www.cnblogs.com/Brilliant11001/p/18385569)

## 题目大意

求 $[1, N]$ 中有多少个数在十进制表示下数码和是 $D$ 的倍数。

数据范围：$1\le N\le 10^{10000},1\le D\le 100$。 

## 思路

很明显的数位 dp。

这里采用了记忆化搜索来实现数位 dp。

记忆化搜索实现比较板子，不光写起来比较简单，而且容易扩展，所以建议大家都学习一下。

首先把上界 $N$ 的每一位抠出来，然后进行填数，个人喜欢从最高位开始填。

加上记忆化，设 $f(pos, r)$ 表示在没有顶上界和前导零的情况下，当前填到了第 $pos$ 位，余数为 $r$ 的数的个数。

然后在搜索过程中记一下当前数位和 $\bmod p$ 等于多少，再简单转移一下即可，详细注释在代码中。

注意到状态数为 $D\cdot\lg N$，每次转移时最多枚举 $10$ 个可填的数，所以时间复杂度为 $O(D\cdot \lg N)$，可以通过此题。

注意！由于最后要 $-1$，所以为防止减为负数要先加上模数再取模。

$\texttt{Code:}$

```cpp
#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 10010, M = 110, mod = 1e9 + 7;
typedef long long ll;
char s[N];
int len, d;
int f[N][M];
vector<int> num;

//记忆化搜索
//pos 记录当前填到了哪一位，r 记录填完 pos + 1 到 len - 1 位后数位和模 d 的值
//limit 记录当前有没有顶上界，zero 记录当前是不是前导零
ll dfs(int pos, int r, bool limit, bool zero) {
    //边界，若填完了就检查一下是否符合条件
    if(pos < 0) return (r == 0);
    //若不顶上界且没有前导零就记忆化，因为顶上界和前导零是特殊情况，满足条件的数可能和普通情况不同
    if(!limit && !zero && f[pos][r] != -1) return f[pos][r];
    //看一下当前这位需不需要顶上界，若前面填的数都是贴着上界的，这一位最多只能填到 num[pos]，否则不受限
    int mx = (limit ? num[pos] : 9);
    ll res = 0;
    //枚举第 pos 位填什么
    for(int i = 0; i <= mx; i++)
        //去填下一位，更新当前余数，看下一位是不是顶上界，看下一位是不是前导零
        res = (res + dfs(pos - 1, (r + i) % d, limit && (i == num[pos]), zero && (!i))) % mod;
    //若不顶上界且没有前导零就记忆化
    if(!limit && !zero) f[pos][r] = res;
    return res;
}

ll calc(char str[]) {
    //把每一位抠出来，注意是倒过来的
    for(int i = len - 1; i >= 0; i--)
        num.push_back(s[i] - '0');
    memset(f, -1, sizeof f);
    return dfs(len - 1, 0, 1, 1);
}

int main() {
    scanf("%s%d", s, &d);
    len = strlen(s);
    //因为我们搜索考虑了 0，最后要把一减去
    printf("%lld", (calc(s) + mod - 1) % mod);
    return 0;
}
```

---

## 作者：Guitar_Jasmine (赞：4)

## 刚学OI三天的蒟蒻又来~~水社区~~写题解啦QWQ!
- 先看一眼数据范围 嗯~n~~只有~~10000位啊，很显然是数位DP（~~废话~~）
- 如果没有学过数位DP的小伙伴建议拿这道~~模板~~题练手：[P2657 [SCOI2009]windy数](https://www.luogu.org/problem/P2657)
- 不过这两道题总体来说类似，感觉本题还简单一些（~~不知道怎么上紫的qwq~~）


------------
## ~~闲聊结束，开始讲题~~
- 根据数位DP的套路，再加上此题的d（d为要求倍数的数，详见题面）很小（d≤100），所以考虑设f[i][j][k]表示——总共i位的数，最高位为j时（注意设状态时j可以为0），%d==k的数一共有多少（都说了d很小，所以数组只需开到10000 * 10 * 100）
- 状态转移方程
- f[i][j][k]=∑f[i-1][p][q] (其中p=0~9,(q+j)%d==k)(此处的q需要读者好好理解~~感性~~一波，~~其实也不难~~，根据设的状态~~很好~~推出来)
- 这是预处理~

```
int Mod(int x)//处理状态，也就是算出q
{
	return x<0?(x%d+d)%d:x;
}

void prework()//预处理
{
	for (int i=0;i<=9;i++)//只有一位的情况下特判
		f[1][i][i%d]=1;
	for (int i=2;i<=n;i++)
		for (int j=0;j<=9;j++)
			for (int k=0;k<d;k++)
				for (int l=0;l<=9;l++)
					f[i][j][k]=add(f[i][j][k],f[i-1][l][Mod(k-j)]);
}
```
- ~~现在到了精彩的累加答案的环节了~~
- 这里讲一下数位DP的精髓——分类讨论的累加答案
- 为什么要分类讨论：题目要我们求出1~n的所有满足条件的数的个数，但我们枚举时用的却是每位上的数字，这就使我们枚举的数可能大于n(这是绝不允许累加进答案的)
#### 分类讨论：
1. 位数小于题目给定数（也就是n）的数（不含前导0）
2. 位数等于n而且前i位等于n的数（i=0~n的位数），这里要注意在i=0也就是枚举的最高位小于n的数时，要单独拎出来处理，因为只有这一位不能为0（毕竟不含前导0）

**注意的地方：**
1. 以下我的代码中，n和题面中给出的n完全没有关系，我的代码中的n表示的是题面给的n（也就是原数）的位数
2. 因为运用了读入的小技巧，我直接从高位开始读入，所以下面work()中看似从低位开始枚举实则是从高位开始枚举（顺序问题很好理解吧）
3. 在分类讨论第二种情况时，累加答案时千万不能忘了前面相同的i位兄嘚对答案产生的影响，所以要在边做的时候边累加
4. 这些都是细节，~~不重要~~，对数位DP的基本思想没有太大影响，每个题目有每个题目的不同点，我们学习主要还是了解思想嘛qwq

上完整代码，细节看注释好啦，~~自以为~~注释写的很详细

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

using namespace std;

const int M=1000000007;
typedef long long LL;
int d,a[10009],f[10009][10][109],n;

int Mod(int x)//处理状态，也就是算出q
{
	return x<0?(x%d+d)%d:x;
}

LL add(LL x,int y)//加完再取余(%%%)
{
	return x+y>=M?x+y-M:x+y;
}

void prework()//预处理
{
	for (int i=0;i<=9;i++)//只有一位的情况下特判
		f[1][i][i%d]=1;
	for (int i=2;i<=n;i++)
		for (int j=0;j<=9;j++)
			for (int k=0;k<d;k++)
				for (int l=0;l<=9;l++)
					f[i][j][k]=add(f[i][j][k],f[i-1][l][Mod(k-j)]);
}

void init()
{
	scanf("%d",&d);
	while(scanf("%1d",&a[++n])!=EOF);//读入小技巧：限制宽度
	n--;//因为++n的时候多加了一次，所以要给他减掉
}

void work()
{
	prework();//预处理qwq
	LL ans=0;
	for (int i=n-1;i>=1;i--)//先把答案加上不足n位的情况
		for (int j=9;j>=1;j--)
			ans=add(ans,f[i][j][0]);
	for (int i=a[1]-1;i>=1;i--)//单独处理第n位也就是最高位(由于之前读入的原因，所以a[1]就是最高位)
		ans=add(ans,f[n][i][0]);
	int k=a[1];//记录等于原数的情况时最高位到当前位的数字之和
	for (int i=2;i<=n;i++)//从次高位到最低位(顺序问题和上文相同)
	{
		for (int j=0;j<a[i];j++)//这一位小于原数的情况
			ans=add(ans,f[n-i+1][j][Mod(d-k)]);//后面的数位随便，所以放心大胆的把所有预处理的情况加上，其中的Mod(d-k)类似上文处理q的过程
		k+=a[i];//累加
	}
	//其实按道理来讲自始至终没有累加原数对模d的贡献，最后还要特判一下
	//但数据好像比较水，没加竟然也过了(才不是我忘了QWQ)
	//懒得加了，写一波伪代码
	//if(原数%d==0)
	//    ans++;
	printf("%lld\n",ans);
}

int main()
{
	//freopen("AT681.in","r",stdin);
	//freopen("AT681.out","w",stdout);
	init();
	work();
	return 0;
}

```

蒟蒻的第一篇紫题题解，写的不好但希望尽可能给大家带来帮助QWQ。最后，祝奋斗在前线的所有OIer们：
# 2019 CSP-J/S RP++！！！

---

## 作者：edward1346 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_tdpc_number)

**备注：** 如果各位大神在提交过程中被返回“未知错误”，那么请大神们移步至[原 oj](https://atcoder.jp/contests/tdpc/tasks/tdpc_number) 提交。

很显然，这是一道~~裸的~~数位 dp 题。

可以先令 $f(pos,mod)$ 表示该状态下合法数的个数。

其中 $pos$ 表示当前还剩 $pos$ 位没填，$mod$ 表示当前数码和模 $d$ 的余数。

同时，我们要注意前导零和最高位限制。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int d;
string n;
int num[10001],len;
int f[10001][101];
int mm=1e9+7;
int dfs(int pos,int mod,int lead,int limit)
{
	if(pos==0)
	{
		if(mod==0&&!lead)return 1;
		return 0;
	}
	if(!limit&&!lead&&f[pos][mod]!=-1)
		return f[pos][mod];
	
	int up=9,ans=0;
	if(limit)up=num[pos];
	for(int i=0;i<=up;i++)
	{
		if(i==0&&lead)
			ans+=(dfs(pos-1,mod,1,limit&&i==up));
		else{
			ans+=(dfs(pos-1,(mod+i)%d,0,limit&&i==up));
		}
		ans=(ans)%mm;
	}
	ans=(ans)%mm;
	
	if(!lead&&!limit)
		f[pos][mod]=ans;
	return ans;
}
main()
{
	cin>>d>>n;
	for(int i=n.size()-1;i>=0;i--)
		num[++len]=n[i]-48;
	memset(f,-1,sizeof f);
	cout<<(dfs(len,0,1,1))%mm;
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

**分析**

[双倍经验](https://luogu.com.cn/problem/AT_dp_s)。

看到 $n$ 非常大，考虑数位 dp，其中一种数位 dp 的实现方法就是记搜。考虑 $dp_{p,sum}$ 表示 $p$ 位数里面小于 $n$ 的前 $p$ 位的数里有多少个数位和模 $d$ 余 $sum$ 的数个数。那么考虑一个限制 $limit$，当前位只能取 $0\sim maxt$ 的数字，否则可能搜着搜着就比 $n$ 大了，导致不方便统计答案，其中若 $limit=0$，$maxt=9$，否则是 $n$ 的第 $|n|=p$ 位。从高位往低位搜，并更新 $sum,limit$。其中 $limit$ 的更新取决于搜下去时的数字是否等于 $maxt$。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[10010][110],d,k[10010];
string s;
const int mod=1e9+7;
int dfs(int p,int sum,int lim)
{
	if(!p) return (!sum);
	if(!lim&&~dp[p][sum]) return dp[p][sum];
	int maxt=lim?k[p]:9,ret=0;
	for(int i=0;i<=maxt;i++) ret=(ret+dfs(p-1,(sum+i)%d,lim&&i==maxt))%mod;
	if(!lim) dp[p][sum]=ret;
	return ret;
}
signed main()
{
	memset(dp,-1,sizeof dp);
	cin>>d>>s;
	for(int i=1;i<=s.size();i++) k[i]=s[s.size()-i]-'0';
	cout<<(dfs(s.size(),0,1)-1+mod)%mod<<'\n';
	return 0;
}

---

## 作者：aCssen (赞：1)

### Solution
$N$ 很大，考虑数位 dp。

输入时，我们以字符串形式输入 $N$，然后将其转为数组，注意要倒着存。

设 $f_{pos,val}$ 表示考虑了 $N$ **从高到低**的 $pos$ 位，各位数之和对 $d$ 取模为 $val$ 的数的数量。

采用记忆化搜索实现。

具体的，为了防止前导 $0$ 和最高位限制影响答案，我们只在没有前导 $0$ 限制和最高位限制才进行记忆化。

每次我们枚举 $i$，表示第 $pos$ 位可能的数是多少，设 $res$ 表示第 $pos$ 位能取到的最大数，则可以得到：
$$f_{pos,val}=\sum_{i=0}^{res} f_{pos-1,(val+i) \bmod d}$$

当搜到 $pos=0$ 时，如果 $val=0$ 返回 $1$，否则返回 $0$。

注意最后要减去 $1$，因为 $0$ 不符合条件，此时需要取模。

**要输出换行**。

### Code
[Link](https://atcoder.jp/contests/tdpc/submissions/47372501)

---

## 作者：Graphcity (赞：1)

Update：加入了取模。

数位 DP 的模板题。

发现本题中前导零对答案没有任何影响，所以不需要考虑前导零的问题。下文中默认个位是最后一位。

先设 $f_{i,j}$ 表示后 $i$ 位中数码和对 $d$ 取模后为 $j$，且可以自由填数（也就是前面已经有一位满足数码小于 $n$ 的对应位）的方案数。枚举这一位填什么，就有

$$
f_{i,j}=\sum_{k=0}^9f_{i-1,j-k\bmod d}
$$

初始值 $f_{0,0}=1$。

再设 $g_{i,j}$ 为后 $i$ 位中数码和对 $d$ 取模后为 $j$ 的方案数。还是考虑当前位填什么，就有

$$
g_{i,j}=g_{i-1,j-s_i\bmod d}+\sum_{k=0}^{s_i-1}f_{i-1,j-k\bmod d}
$$

其中 $s_i$ 表示 $n$ 在第 $i$ 位的数。初始值 $g_{0,0}=0$。可以用记忆化搜索实现。

注意到零不是正整数，所以最后答案要减去一。时间复杂度 $O(|n|d)$，$|n|$ 表示 $n$ 的位数。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5,Mod=1e9+7;

char ch[Maxn+5]; int n,m;
int g[Maxn+5][105],f[Maxn+5][105];
bool vis[Maxn+5][105];

inline int dfs(int x,int y,int flag)
{
    if(flag) return f[x][y];
    if(vis[x][y]) return g[x][y];
    if(!x) return (!y);
    int res=0,id=ch[x]-'0';
    For(i,0,id)
    {
        if(i<id) res=(res+dfs(x-1,((y-i)%m+m)%m,1))%Mod;
        else res=(res+dfs(x-1,((y-i)%m+m)%m,0))%Mod;
    }
    vis[x][y]=1; return g[x][y]=res;
}

int main()
{
    scanf("%d%s",&m,ch+1),n=strlen(ch+1),f[0][0]=1;
    reverse(ch+1,ch+n+1);
    For(i,1,n) For(j,0,m-1) For(k,0,9)
        f[i][j]=(f[i][j]+f[i-1][((j-k)%m+m)%m])%Mod;
    printf("%d\n",(dfs(n,0,0)-1+Mod)%Mod);
    return 0;
}
```

---

## 作者：斜揽残箫 (赞：1)

## Description

给定两个数 $d$, $N$，求从 $1$ ~ $N$ 中有多少个数各个数位上的数码和是 $d$ 的倍数，答案对 $10 ^ 9 + 7$ 取模。

$1 \leq N \leq 10 ^ {10000}$。

## Solution

这是一篇使用记忆化搜索来实现求解的题解。~~(记搜多么省事啊，背过模板就好了)。~~

对于一个长度为 $cnt$ 的数字，我们可以从高位向低位枚举数字，统计字符相加 $\bmod \ \ d$ 的值。

+ 我们枚举的位数是必须要记录的。 $(id)$
+ 其次，我们还要记录各个数位上的数 $\bmod \ \ d$ 的值。 $(last)$
+ 还要记录是否上一位是否到达了边界。 $(limit)$
+ 记录是否有前导零。 $(zero)$

上面四个参数就是我在记忆化搜索中用到的变量。

所以设 $f[i][j][k][p]$ 为到达第 $i$ 个数位，$\bmod \ \ d$ 的余数为 $j$ ，$k$ 为是否到达上界（是则为 ```true```，否则为 ```false```）， $p$ 为是否含有前导零（是则为 ```true```，否则为 ```false```），到最后 $cnt$ 为 0 的时候看余数是否为 0，如果余数为 0，总答案就加一，否则就不加。

此外还要注意 $N$ 很大，要用字符串读入，再转化为数组来储存，储存时要倒序储存。

最后献上主要代码。

## Code

```cpp
#define LL long long
const int mod = 1000000007;
int a[10010];
LL f[10010][110][2][2];
LL Dfs(int id,int last,int limit,int zero)
// 代表 进行到第几位，上一个数字，是否到边界，是否有前导 0
{
  if(!id) return !last ? 1 : 0;
  //当搜索完了最后一位，看看余数是否为 0 ， 为 0 则说明能够整除，答案 + 1;
  if(~f[id][last][limit][zero] && !limit && !zero) return (f[id][last][limit][zero] + mod) % mod;
  // 记忆化过程，如果以前已经搜到了这个位置，并且没有前导零，没到边界就可以返回，已经搜到的答案。
  int up = limit ? a[id] : 9;
   //从高位向低位枚举，所以如果之前一位的数码和最大的数码相同，这一位就只能从 0 枚举到 a[id]，防止越界。
    //否则如果之前一位比最大数的数码小，那这一位就可以从 0 ~ 9 枚举了，这样肯定不会越界。
  LL ans = 0;//统计答案
  for(int i = 0;i <= up;i ++) {
    int h = (last + i) % d;//计算各个数位上的和。
    if(zero && (i == 0)) ans += (Dfs(id - 1,h,limit && (i == up),1) + mod) % mod;
    // 当有前导 0 的时候分开来计算。
    else ans += (Dfs(id - 1,h,limit && (i == up),0) + mod) % mod;
  }
  if(!limit && !zero) f[id][last][limit][zero] = (ans + mod) % mod;
  //如果没到边界并且没有前导零，就可以记忆化。
  return (ans + mod) % mod;
  //别忘取模
}
```

---

## 作者：梧桐灯 (赞：1)

一看到数据范围：$d$很小，$n$很大很大很大，就知道此题大致思路是数位DP。

那我们设：$f[i][j][k]$表示位数为$i$，最高位为$j$（可以是$0$），放最高位之前所有数的和对$d$的余数为$k$的方案数。

当然第三维也可表示放过最高位后的余数，我为了方便才这样设的。

考虑转移：
$$f[i][j][(k + last)\%d] = f[i - 1][last][k]$$

其中$i$表示当前位数，$j$表示当前最高位，$k$表示上一维的余数，$last$表示上一维的最高位。

其中我们需要枚举$i,j,k,last$。总复杂度为$n*10*100*10$

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10003, MOD = 1000000007;
int a[N], n, d, ans;
char s[N];
int f[N][10][100];

inline int pd () {
	int i, s = 0;
	for (i = 1; i <= n; ++i) {
		s += a[i];
		s %= d;
	}
	return !s;
} //判断=n的情况

int main(){
	scanf ("%d %s", &d, s + 1);
	n = strlen (s + 1);
	for (int i = 1; i <= n; ++i) a[i] = s[n - i + 1] ^ 48;
	f[0][0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < d; ++k) {
				int t = (k + j) % d;
				for (int last = 0; last < 10; ++last) {
					f[i][j][t] += f[i - 1][last][k];
					f[i][j][t] = f[i][j][t] >= MOD ? f[i][j][t] - MOD : f[i][j][t];
				}
			} //预处理
		}
	}
	ans = (pd () - 1 + MOD) % MOD; //-1是因为0被统计到了方案里
	int now = 0;
	for (int i = n; i; --i) {
		for (int j = 0; j < a[i]; ++j) {
			ans += f[i][j][(d - now) % d];
			ans = ans >= MOD ? ans - MOD : ans;
		}
		now += a[i];
		now %= d; //now表示前i位数位和除d的余数
	}
	printf ("%d\n", ans);
	return 0;
}
```


---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_tdpc_number)

# 前置知识

[数位 DP](https://oi-wiki.org/dp/number/) | [记忆化搜索](https://oi-wiki.org/dp/memo/)

# 解法

本题的提交在 luogu 上挂了，建议去[原站](https://atcoder.jp/contests/tdpc/tasks/tdpc_number)或 [Vjudge](https://vjudge.net/problem/AtCoder-tdpc_number) 上提交。

基础数位 DP，记录当前位置、已填的数码之和，接着记忆化搜索即可。

需要注意的是 $0 \bmod d=0$，如果写得不太好看（未处理前导零）的话需要减去其贡献。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll p=1000000007;
ll a[10010],f[10010][110];
char k[10010];
ll dfs(ll pos,ll pre,ll lead,ll limit,ll d)
{
	if(pos<=0)
	{
		return (pre==0);
	}
	if(f[pos][pre]!=-1&&lead==0&&limit==0)
	{
		return f[pos][pre];
	}
	ll ans=0,maxx=(limit==0)?9:a[pos],i;
	for(i=0;i<=maxx;i++)
	{
		ans=(ans+dfs(pos-1,(pre+i)%d,(i==0)*lead,(i==maxx)*limit,d))%p;
	}
	return (lead==0&&limit==0)?f[pos][pre]=ans:ans;
}
ll ask(ll len,ll d)
{
	memset(f,-1,sizeof(f));
	return dfs(len,0,1,1,d);
}
int main()
{
	ll d,len,i;
	scanf("%lld%s",&d,k+1);
	len=strlen(k+1);
	reverse(k+1,k+1+len);
	for(i=1;i<=len;i++)
	{
		a[i]=k[i]-'0';
	}
	printf("%lld\n",(ask(len,d)-1+p)%p);
	return 0;
}
```

# 后记

多倍经验：[AT_dp_s Digit Sum](https://www.luogu.com.cn/problem/AT_dp_s)

---

## 作者：ZnPdCo (赞：0)

题目不知道出了什么问题，这里是[提交链接](https://atcoder.jp/contests/tdpc/tasks/tdpc_number)。

---

我认为这是一个数位 DP 的模版（~~让它当模版好了~~）

> 数位是指把一个数字按照个、十、百、千等等一位一位地拆开，关注它每一位上的数字。如果拆的是十进制数，那么每一位数字都是 $0\sim9$，其他进制可类比十进制。
>
> 数位DP：用来解决一类特定问题，这种问题比较好辨认，一般具有这几个特征：
>
> 1. 要求统计满足一定条件的数的数量（即最终目的为计数）；
> 2. 这些条件经过转化后可以使用「数位」的思想去理解和判断；
> 3. 输入会提供一个数字区间（有时也只提供上界）来作为统计的限制；
> 4. 上界很大（比如 $10^{18}$），暴力枚举验证会超时。

首先，我们会发现这个数据范围非常的大（$N\le10^{10000}$），所以不能使用一般的 DP，我们只能用数位进行维护。

设计 $f_{i,j,k}$ 表示数字长度为 $i$，最高位（最左边的）为 $j$，数码和模 $D$ 的余数为 $k$ 的合法个数。

那么很容易可以得到一个转移方程为：
$$
f_{i,j1,k1}\gets f_{i-1,j2,k2}
$$
其中，$i,j_1,k_1,j_2$ 可以通过枚举得出，发现 $k_2+j_1=k_1$，也就是方程右边的数码和 $k_2$ 加上新的最高位 $j_1$ 可以得到新的数码和 $j_1$。逆推可以得到 $k_2 = k_1 - j_1$。

我们知道了这一点可以很快写出预处理代码（下位中的 $n$ 是输入的**位数**）：

```c++
for(ll i = 0; i < 10; i++) {		// 处理初始值
	f[1][i][i % d] = 1;
} 

for(ll i = 2; i <= n; i++) {
	for(ll j1 = 0; j1 < 10; j1++) {
		for(ll k1 = 0; k1 < d; k1++) {
			ll k2 = ((k1 - j1) % d + d) % d;
			for(ll j2 = 0; j2 < 10; j2++) {
				(f[i][j1][k1] += f[i-1][j2][k2]) %= P;
			}
		}
	}
}
```

（很想做不嵌套主义者但~~偷懒更宝贵~~）

---

我们就进入了统计答案环节，这里是比较容易错的，首先我们先处理位数比 $N$ 小的答案，很容易统计：（注意最高位不能为 $0$）

```c++
for(ll i = 1; i < n; i++) {
	for(ll j = 1 /*注意最高位从1开始*/ ; j < 10; j++) {
		(ans += f[i][j][0]) %= P;
	}
}
```

---

位数与 $N$ 相同的情况比较麻烦，以最高位为例子，我们枚举最高位为 $j$，因为结果不能超过 $N$，所以有：

```c++
for(ll j = 1 /*注意最高位从1开始*/ ; j < a[1]; j++) {
	ll k = 0;
	(ans += f[n][j][k]) %= P;
}
```

接下来，我们就固定最高位为 $a[1]$，枚举第二高位：

```c++
for(ll j = 0 /*注意第二高位从0开始，因为第一位已经有a[1]了，不需要保证首位不为0了*/ ; j < a[2]; j++) {
	ll k = ((d - a[1]) % d + d) % d;	// 去掉第一高位的和
	(ans += f[n-i+1][j][k]) %= P;
}
```

以此类推，以上一框可以写为：

```c++
sum = 0;
for(ll i = 1; i <= n; i++) {
	for(ll j = (i == 1 ? 1 : 0) /*如果是最高位，就从1开始，保证首位不为0；如果不是，就从0开始*/; j < a[i]; j++) {
		ll k = ((d - sum) % d + d) % d;
		(ans += f[n-i+1][j][k]) %= P;
	}
	sum += a[i];
}
```

---

最后在准备提交时发现了数据过水，有一个 hack：

```
3
3
```

也很好理解，就是我忘记考虑 $N$ 本身是否可以被整除了，所以我们需要加一个修改：

```c++
for(ll i = 1; i <= n; i++) {
	for(ll j = (i == 1 ? 1 : 0); (i == n ? j <= a[i] : j < a[i]) /*如果是最低位，可以枚举到a[i]*/; j++) {
		ll k = ((d - sum) % d + d) % d;
		(ans += f[n-i+1][j][k]) %= P;
	}
	sum += a[i];
}
```

---

完整代码：

```c++
#include <cstdio>
#include <cstring>
#define N 10010
#define D 110
#define P 1000000007
#define ll long long
ll n, d, ans, sum;
char a[N];

ll f[N][10][D];
int main() {
	scanf("%lld %s", &d, a+1);
	n = strlen(a+1);
	for(ll i = 1; i <= n; i++) {
		a[i] -= '0';
	}
	
	for(ll i = 0; i < 10; i++) {
		f[1][i][i % d] = 1;
	} 
	
	for(ll i = 2; i <= n; i++) {
		for(ll j1 = 0; j1 < 10; j1++) {
			for(ll k1 = 0; k1 < d; k1++) {
				ll k2 = ((k1 - j1) % d + d) % d;
				for(ll j2 = 0; j2 < 10; j2++) {
					(f[i][j1][k1] += f[i-1][j2][k2]) %= P;
				}
			}
		}
	}
	
	for(ll i = 1; i < n; i++) {
		for(ll j = 1; j < 10; j++) {
			(ans += f[i][j][0]) %= P;
		}
	}
	for(ll i = 1; i <= n; i++) {
		for(ll j = (i == 1 ? 1 : 0); (i == n ? j <= a[i] : j < a[i]); j++) {
			ll k = ((d - sum) % d + d) % d;
			(ans += f[n-i+1][j][k]) %= P;
		}
		sum += a[i];
	}
	
	printf("%lld\n", ans);
}
```

最重要的事情，**记得换行**

---

