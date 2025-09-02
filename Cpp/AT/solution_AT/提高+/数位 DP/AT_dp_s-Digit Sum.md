# Digit Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_s

$ 1 $ 以上 $ K $ 以下の整数のうち、十進表記における各桁の数字の総和が $ D $ の倍数であるようなものは何個でしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ K\ <\ 10^{10000} $
- $ 1\ \leq\ D\ \leq\ 100 $

### Sample Explanation 1

$ 4,\ 8,\ 13,\ 17,\ 22,\ 26 $ の $ 6 $ 個です。

### Sample Explanation 2

答えを $ 10^9\ +\ 7 $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
30
4```

### 输出

```
6```

## 样例 #2

### 输入

```
1000000009
1```

### 输出

```
2```

## 样例 #3

### 输入

```
98765432109876543210
58```

### 输出

```
635270834```

# 题解

## 作者：TonyYin (赞：14)

这里提供一篇代码有注释的题解。

本题标签：数位DP

大致难度：按照Luogu上其他数位DP的评级，这题应该在绿题到蓝题之间。

## $\rm{Description}$

求区间 $[1, k]$ 中有多少个整数满足：其十进制表示的数字和为 $D$ 的倍数。答案对 $1e9+7$ 取模。

## $\rm{Solution}$

观察数据范围：$1\leq k\leq 10^{10000}$. 

再看题面，形如”**求在数位限制下有多少满足条件的数**“，想到数位 $\rm{DP}$.

如果你没有学过数位 $\rm{DP}$，那么可以参考[这篇博客](https://blog.csdn.net/KonnyWen/article/details/104475276)，我就是照着这篇博客学懂的。

如果你学过数位 $\rm{DP}$，那么现在考虑状态如何设置。

**状态设置：**

首先可以看出，这道题不需要前导零标记。

第二步需要思考 $\rm{DP}$ 中需要存储什么前缀状态。通过题目描述可以比较容易的看出，我们只需要存储前缀数字和对 $D$ 取模的余数即可，将其记为 $\rm{pre}$，

那么能对答案作出贡献的条件就是：前缀数字和 $\bmod D =0$，也就是 $pre = 0$. 

至此，根据数位 $\rm{DP}$ 的套路，我们可以设置如下状态：

> $\rm{DP}[pos][pre][sta]$ 表示还有 $pos$ 位需要处理；
>
> 当前状态的前缀数字和 $\bmod D$ 是 $pre$；
>
> 前缀的最大值状态是 $sta$，若前 $len-pos$ 位与题目给出的 $k$ 相同，则 $sta=0$，反之亦然。

**状态转移：**

于是可以使用记忆化搜索来实现数位 $\rm{DP}$，详见代码注释。

个人觉得注释还比较清晰，认真多看几遍是能看懂的。

```cpp
int dfs(int pos, int res, int sta) {
	if(pos == 0) return res == 0; //能对答案作出贡献的条件：前缀数字和 mod D == 0
	if(dp[pos][res][sta] != -1) return dp[pos][res][sta]; //记忆化搜索
	int ret = 0, maxx = 9; //ret是函数返回值，maxx是当前位可选的最大值
    if(sta) maxx = num[pos]; //如果当前前缀与k的前缀相同，那么这一位最大值就是num[pos]
	for(int i = 0; i <= maxx; i++) { //之后遍历这一位可选的数字
		ret += dfs(pos - 1, (res + i) % d, sta && (i == maxx));
        //pos - 1: 继续看下一位
        //(res + i) % d: 把前缀数字和加上新选的这一位
        //sta && (i == maxx): 前缀and当前这一位, 都与k的前缀相同，那么新的前缀还是最大值状态 
	}
	dp[pos][res][sta] = ret;//记忆化
	return ret;
}
```

由于加上取模之后不美观，上面的代码没有给 $ret$ 加取模，需要加上。（下面的代码中是有取模的）

## $\rm{Code}$

放出完整代码，可以再重点看一下 `solve()` 函数里面的初始化。

关键部分的注释已经在上面了。

如果没有看懂，建议再读几遍[这篇博客](https://blog.csdn.net/KonnyWen/article/details/104475276)，或者自行百度学习数位 $\rm{DP}$.

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXLEN = 10008;
const int MAXD = 108;
const int mod = 1e9 + 7;
int d, num[MAXLEN];
string s;
int dp[MAXLEN][MAXD][2];
int dfs(int pos, int res, int sta) {
	if(pos == 0) return (res == 0);
	if(dp[pos][res][sta] != -1) return dp[pos][res][sta];
	int ret = 0, maxx = 9;
	if(sta) maxx = num[pos];
	for(int i = 0; i <= maxx; i++) {
		ret = (ret + dfs(pos - 1, (res + i) % d, sta && (i == maxx))) % mod;
	}
	dp[pos][res][sta] = ret;
	return ret;
}
int solve() {
	memset(dp, -1, sizeof(dp));
	for(int i = 0; i < s.length(); i++) {
		num[i + 1] = s[s.length() - i - 1] - '0';
	}
	return dfs(s.length(), 0, 1);
}
signed main() {
	cin >> s;
	scanf("%lld", &d);
	printf("%lld\n", ((solve() - 1) % mod + mod) % mod);
	return 0;
}
```


---

## 作者：falling_cloud (赞：10)

这题大致算是数位 DP 的基础题了，相当适合新手练手。

题目求解的范围是小于 $k$ 的正整数，所以在数位上从高位开始进行一遍 DP 就可以了，由于各位数字值和需要模 $p$，所以可以将各位数字值之和替代为各位数字之和模 $p$ 的值，就可以将这一状态的最大值从 $9 \times 10^4$ 降至 $100$，使空间复杂度降至可以通过。

再用 $limit$ 表示此时的数字是否达到上限。显而易见地，当先前的数字达到上限后，第 $i$ 位选择的数字需要小于等于 $k$ 的第 $i$ 位。

用 $dp_{len,pre,limit}$ 来代表状态：求解到第 $len$ 位，此时各位数字之和模 $p$ 的值为 $pre$，上限状态为 $limit$。设定 $maxk$ 为枚举上限，用记忆化搜索求解，状态转移为：

```cpp
for(i=0;i<=maxk;i++) res+=dfs(len-1,(pre+i)%d,limit && i==maxk);
```

边界条件：$dp_{0,0,0/1}=1$。

具体实现见代码和注释：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int dp[10005][105][2];
int num[10005],d;
int dfs(int len,int pre,int limit)
{
	int i,res=0,maxk = limit ? num[len] : 9;	//未达到枚举上限时 i 可以从 0 枚举至 9 
	if(!len)
		if(!pre) 				return 1;
		else					return 0;
	if(~dp[len][pre][limit])	return dp[len][pre][limit];	//被求解过的情况直接返回值 
	for(i=0;i<=maxk;i++)
		res=(res+dfs(len-1,(pre+i)%d,limit && i==maxk))%mod;
	return dp[len][pre][limit] = res;						//保存结果 
}

int main()
{
	int i,j,k,l;
	string s;
	cin>>s;
	cin>>d;
	l=s.length();
	for(i=0;i<l;i++)	num[l-i]=s[i]-'0';
	memset(dp,-1,sizeof(dp));		//记忆化搜索的预处理，当值为 -1 时一定未被查过 
	cout<<(dfs(l,0,1)-1)%mod;		//由于 0 也会被判定为模 d 余 0，所以解出的答案需要减去 1
	return 0;
}
```

---

## 作者：EastPorridge (赞：9)

为啥题解中的所有代码的状态都是三维的啊，同质化严重且大可不必，提供一种省空间的写法。

### 题目概述：

求 $1$ 到 $k$ 之间能被 $d$ 整除的数的个数。 $1 \le k \le 10^{10000}$ 。

### 题目分析：

看到这巨大无比的 $k$ 考虑数位 dp 解决。

我们用 $dp[pos][m]$ 表示当前第 $pos$ 位，模 $d$ 等于 $m$ 的数的个数，合法状态即为当 $pos=0$ 时，$m$ 为 $0$ 即表示被整除，记录一个高位限制 $top$ ，每次转移就是加上 $(m+i) \mod d$ ，每次 $pos-1$ 向后转移，所以说根本不需要把 $top$ 记录在 dp 数组中。

需要注意的是， $0$ 也会被记录成一种合法方案，我们在最后统计出的答案中把它减掉。

减少计算中取模的次数可以试着卡一下最优解。

### Code.
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10,mod=1e9+7;
int dp[N][110],d,a[N]; char s[N];
int dfs(int pos,int m,int top)
{
	if(! pos) return m == 0;
	if(! top && ~dp[pos][m]) return dp[pos][m];
	int mx =top?a[pos]:9,res=0;
	for(int i=0;i<=mx;i++) res=(res+dfs(pos-1,(m+i)%d,top && i == mx))%mod;
	if(! top) dp[pos][m]=res;
	return res%mod;
}
int main()
{
	memset(dp,-1,sizeof dp); scanf("%s",s); int len=strlen(s); cin>>d;
	for(int i=1;i<=len;i++) a[i]=s[len-i]-48;
	printf("%d",(dfs(len,0,1)-1+mod)%mod);
	return 0;
}
```

---

## 作者：Doqin07 (赞：4)

## 题意
#### 求 {1,2,3,...,k}中有多少数字的各位之和是d的倍数。
## 解题思路
##### 我们有一个很显然的暴力，枚举$1-k$中每一个数，计算数位之和，判断是否能被$d$整除。代码也很好写。但是k<=10^10000,会tle。
#### 那么接一下来，分析题目，“数字之和”此类的字眼，不免让人想到数位$dp$。
#### 这类题目的基本框架就是求某一个范围[l, r]内有多少个数满足XXX性质。由于[l, r]=[0, r]−[0, l−1]，我们通常转化为只有上界，而下界为0的两个独立情况分别计算。于是以下只考虑[0, r]的计算方法。
----
## 数位$dp$：
#### 这题我们运用$01$背包的思想：在考虑第i件物品的时候，只关心之前选择的总重量以及总价值，而不需要知道具体的方案是什么——即合并等价状态。
#### 回到本题，我们枚举第 $i$ 位的时候，只有这些信息是重要的：
- 1.之前的数位和。
- 2.是否已经小于上界r，如果是的话，那么可以枚举$[0-9]$，否则只可以枚举到$r[i]$——因为我们只考虑小于等于r的数。

#### 那么我们可以设$dp[i][j][k=0/1]$表示在考虑第i位之前的数位和(模$d$)等于$j$，以及是否已经小于上界的方案数。转移也很简单，对于状态$dp[i][j][k]$，只需要枚举第$i$位的值$x[i]$，那么转移到的状态为dp[i+1][(j+x[i])%d][k or x[i]<r[i]]。最后一个值的意思是，小于上界的条件是之前已经小于上界或者当前位小于上界对应位。
---
#### 思路已经很清楚了，接下来看一下核心Code:
```cpp
dp[0][0][0] = 1;
for (int i = 0; i < n; ++i){
	for (int j = 0; j < d; ++j){
		for (int k = 0; k < 2; ++k){
			for (int cur = 0; cur <= 9; ++cur){
				if (k == 0 and cur > r[i])
					break;
				dp[i + 1][(j + cur) % d][k or cur < r[i]] += dp[i][j][k];
			}
		}
	}
}
//小于上界+不小于上界（即等于上界）- 0的情况（因为题目里不包含0
ans = dp[n][0][0] + dp[n][0][1] - 1; 
```
---
# 求过啊^_^


---

## 作者：Bpds1110 (赞：3)

### Preface:
[**原题传送门**](https://www.luogu.com.cn/problem/AT_dp_s)

题解社贡满了，本题可能是蒟蒻的最后一篇题解了，也是第一道蓝题的题解。

给出正整数 $K$ 和 $D$，求出 $1$ 到 $K$ 中有多少个数的各位之和能被 $D$ 整除，方案总数对 $10^9 + 7$ 取模。
### Solution:
明显一道数位 DP 水题，在这里可以用搜索做。观察数据范围：$1 \le k \le 10^{10000}$，发现读入 $K$ 不能用整型，于是考虑用字符串 $s$ 记录，再用 $a$ 整型数组保存每个位上的数。注意在 $a$ 中按由地位到高位排列，所以要进行翻转，方便搜索，对于每次搜索步骤如下。

1. 我们设 $tot$ 为当前在 $a$ 数组中的下标，$sum$ 为当前各位之和（对 $D$ 取模），$limit$ 为到当前位置的所有数是否与 $a$ 数组中相等，用于判断下一位数是否越界。
2. 如果当前方案已经完成，判断是否是 $D$ 的倍数，返回值。
3. 可以用到记忆化，我们设 $f$ 数组为记忆数组，则 $f[tot][sum][limit]$ 记录当前状态下的方案总数。
4. 枚举 $i$ 从 $1$ 到 $9$，表示下一位数字。如果前面几位与 $a$ 数组中的数相同（也就是 $limit = 1$）并且 $i > a_{tot}$，数字越界，直接终止当前循环。
5. 搜索下一位，`dfs(tot - 1, (sum + i) % d, limit && i == a[tot])`，代码中会详细解释。最后累加当前方案总数并取模。

### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int LEN = 1e4 + 1;
ll d, f[LEN][100][2], a[LEN];
ll dfs(ll tot, ll sum, ll limit)
{
	ll ans = 0;
	if(! tot) return (sum % d == 0);
	//如果当前方案已经完成，累加总和是否是D的倍数 
	if(f[tot][sum][limit] ^ -1)
		return f[tot][sum][limit];
	//记忆化搜索 
	for(int i = 0; i ^ 10; i ++)//枚举下一位 
	{
		if(limit && i > a[tot]) break ;//数字越界的情况 
		ans += dfs(tot - 1, (sum + i) % d, limit && i == a[tot]) % mod;
		//tot-1表示搜索下一位，(sum+i)%d表示累加选择的数字并对D取模，最后判断到当前有没有限制后一位的值 
		ans %= mod;//方案总数取模 
	}
	return f[tot][sum][limit] = ans;//记忆化 
}
ll digit(string s)
{
	memset(f, -1, sizeof(f));
	//记忆数组f赋成-1，表示全部没有做过 
	for(int i = 0; i ^ s.length(); i ++)
		a[i + 1] = s[i] - 48;//从1开始，方便储存 
	reverse(a + 1, a + 1 + s.length()); 
	//在a数组中翻转 
	return dfs(s.length(), 0, 1);
}
int main()
{
	string s = "";
	cin >> s >> d;
	cout << ((digit(s) - 1) % mod + mod) % mod;
	//对方案总数再次取模 
	return 0;
}
```


---

## 作者：xxx2022 (赞：1)

这是一道比较板子的数位 dp 。

首先观察到 $k$ 很大，肯定不能用枚举的方法求，然后就考虑用数位 dp 。对于这道题来说，我们可以在用记忆化搜索做数位 dp 的时候存一个当前各数位之和对 $d$ 取余的余数，当把数填完之后判断余数是否为 $0$ 就能判断这个数是否符合条件。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
inline int read(){
	int f=1,w=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		w=(w<<1)+(w<<3)+(c^48);
		c=getchar();
	}
	return f*w;
}
int a[10010];
char k[10100];
int d;
int tot;
int f[10100][110];
int dfs(int now,int res,int lim){
	if(now>tot){
		if(res)	return 0;//若余数不为0说明这个数各数位之和无法被d整除，那么返回0
		else	return 1;
	}
	if(!lim&&f[now][res]!=-1)	return f[now][res];//记忆化搜索实现数位dp
	int mx;
	if(lim){
		mx=a[now];
	}else{
		mx=9;
	}
	int ans=0;
	for(int i=0;i<=mx;i++){
		(ans+=dfs(now+1,(res+i)%d,lim&(i==mx)))%=mod;
	}
	if(!lim)	f[now][res]=ans;
	return ans;
}
void init(){
	for(int i=1;i<=tot;i++){
		a[i]=k[i]-'0';
	}
}
signed main(){
	scanf("%s",k+1);
	tot=strlen(k+1);
	d=read();
	init();
	memset(f,-1,sizeof(f));
	cout<<(dfs(1,0,1)-1+mod)%mod<<endl;
	return 0;
}

```


---

## 作者：Fishing_Boat (赞：1)

一道非常基础的数位 DP 题。

我们只需要记录枚举到当前位的数字和除以 $D$ 的余数即可。

核心代码：

```cpp
ll dfs(ll pos,ll mod,ll lim){
/*
pos 记录枚举到哪一位
mod 记录已经枚举的数字和除以 D 的余数
lim 记录是否达到上限
*/
	if(!pos) return !mod;
	if(dp[pos][mod][lim]!=-1) return dp[pos][mod][lim];
	ll up=lim?a[pos]:9,res=0;
	for(int i=0;i<=up;i++){
		res=(res+dfs(pos-1,(mod+i)%d,lim&&(i==up)))%P;
	}
	return dp[pos][mod][lim]=res;
}
```

这份代码会把 $0$ 也算上，所以要记录前导 $0$，或者最后减 $1$，如果使用后者，减 $1$ 可能会减成负数，然后愉快的 [WA](https://www.luogu.com.cn/record/84949034) 掉，~~可见出题人是何等的处心积虑，竟然能造出这种数据。~~

以下是 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const ll P(1e9+7);
string str;
ll d,a[10005],dp[10005][105][2];
ll dfs(ll pos,ll mod,ll lim){
	if(!pos) return !mod;
	if(dp[pos][mod][lim]!=-1) return dp[pos][mod][lim];
	ll up=lim?a[pos]:9,res=0;
	for(int i=0;i<=up;i++){
		res=(res+dfs(pos-1,(mod+i)%d,lim&&(i==up)))%P;
	}
	return dp[pos][mod][lim]=res;
}
ll work(string s){
	for(int i=0;i<s.size();i++){
		a[s.size()-i]=str[i]-'0';
	}
	memset(dp,-1,sizeof(dp));
	return (dfs(s.size(),0,1)-1+P)%P;
}
int main(){
	cin>>str>>d;
	cout<<work(str);
	return 0;
}

---

## 作者：Warriors_Cat (赞：1)

应该算是个数位 $DP$ 入门题了吧。

### $Solution:$
令这个多位数为 $a$，从低到高第 $i$ 位为 $a_i$。

考虑定义 $f_{i, j, lim}$ 表示当前枚举到第 $i$ 个数，余数为 $j$，最高位有没有到达限制时的方案数。

根据这个状态我们易得其转移方程：

$$f_{i, j, lim} = \sum_{k=0}^{9\cdot[lim = 0]+a_i\cdot[lim=1]}f_{i-1, (j+k)\bmod d, [k = a_i]\cdot[lim = 1]}$$

边界条件就是 $f_{0, j, lim} = [j = 0]$。

然后直接一个记忆化搜索就没了……

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define ll long long
#define fi first
#define se second
#define x1 x_csyakioi_1
#define x2 x_csyakioi_2
#define y1 y_csyakioi_1
#define y2 y_csyakioi_2
#define y0 y_csyakioi_0
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 10010, M = 110, mod = 1000000007;
int n, k, a[N], len, f[N][M][2]; char s[N];
inline int dfs(int x, int y, bool lim){
	if(x == 0) return y == 0; int ans = 0;
	if(f[x][y][lim] != -1) return f[x][y][lim];
	for(int i = 0; i <= (lim ? a[x] : 9); ++i){
		ans = (ans + dfs(x - 1, (y + i) % k, lim & (i == a[x]))) % mod;
	}
	return f[x][y][lim] = ans;
}
int main(){
	scanf("%s", s + 1); len = strlen(s + 1);
	for(int i = 1; i <= len; ++i) a[i] = (s[len - i + 1] ^ 48);
	memset(f, -1, sizeof(f)); k = read();
	printf("%d\n", (dfs(len, 0, 1) - 1 + mod) % mod);
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 分析

**【总体分析】**：

数位 DP 一眼题。

我们定义 $\mathit{f}_{i,j}$ 表示当前搜索到了第 $i$ 位，前 $i-1$ 位的取值的和对于 $d$ 的取模后的结果为 $j$。当 $i=0$ 时，若 $j=0$，则表示这个数是 $d$ 的倍数。剩下的就是数位 DP 的模板了，答案记得取模。

注：该题目的输入较大，考虑使用字符串。

**【数位 DP 模板之 DFS 写法分析】**：

首先，在搜索函数中，我们需要定义以下几个变量：目前寻找的是第几位；前面所有选定的值的和对于 $d$ 取模的结果； 是否有前导零； 能选择的数是否有上界。但由于 $0 \bmod d =0$，所以我们不需要判断是否有前导零。

函数如：
```
int dfs(int now,int msum,int if_le)
```

然后，我们对于这一位能够取到的值都去搜索一遍，也就是 $0$ 到上界（选择的数没有上界的时候即为 $9$）。对于每一位取到的 $i$，有：$msum=(msum+i) \bmod d$，也就是加上这一位之后取模的结果，答案累加即可。

注：我们使用的是记忆化搜索，所以在没有约束条件且这一位所处的情况有值时，我们可以直接返回值。对于这一位的情况赋值也是在没有约束条件的情况下才可以。

最终函数如下：

```cpp
int dfs(int now,int msum,int if_le){
	if(!now){//搜索完了
		return !msum;
	}
	else if(!if_le&&f[now][msum]!=-1){//记忆化
		return f[now][msum];
	}
	else{
		int ans=0,up=if_le?a[now]:9;//答案与上界
		for(int i=0;i<=up;i++){
			ans=(ans+dfs(now-1,(msum+i)%d,if_le&&i==up))%mod;//记得取模
		}
		return if_le?ans:f[now][msum]=ans;
	}
}
```


## 代码

```cpp
#include<bits/stdc++.h>
using namespace std; 
#define int long long
const int mod=1e9+7;
const int N=1e4+10,M=110;
string r,l="0";
int d;
int a[N],len;
int f[N][M];
int dfs(int now,int msum,int if_le){
	if(!now){
		return !msum;
	}
	else if(!if_le&&f[now][msum]!=-1){
		return f[now][msum];
	}
	else{
		int ans=0,up=if_le?a[now]:9;
		for(int i=0;i<=up;i++){
			ans=(ans+dfs(now-1,(msum+i)%d,if_le&&i==up))%mod;
		}
		return if_le?ans:f[now][msum]=ans;
	}
}
int check(string x){
	len=0;
	memset(f,-1,sizeof(f));
	for(int i=x.size()-1;i>=0;i--){
		a[++len]=(x[i]-'0');
	}
	return dfs(len,0,1);
}
signed main(){
	cin>>r>>d;
	cout<<(check(r)-check(l)+mod)%mod;
	return 0;
}
```


---

## 作者：DengDuck (赞：0)

数位 DP 基础题。

我们设 $f_{i,j,0}$ 表示在数字 $K$ 从左往右第 $i$ 位往后，余数为 $j$，不需要考虑小于 $K$ 这一条件的方案数。

我们设 $f_{i,j,1}$ 表示在数字 $K$ 从左往右第 $i$ 位往后，余数为 $j$，前面与 $K$ 都一样，需要考虑小于 $K$ 这一条件的方案数。

两个的不同在于选择的范围不同，没有限制则可以选择 $[0,9]$ 的所有数字，有限制则不能超过 $K$。

我们设 $K$ 从左往右第 $i$ 位为 $K_i$。

得：
$$
f_{i,j,0}=\sum_{k=0}^9f_{i+1,j-k,0}
$$

$$
f_{i,j,1}=\sum_{k=0}^{K_i-1}(f_{i+1,j-k,0})+f_{i+1,j-K_i,1}
$$
注意 $j-k$ 其实是要取模的，但我没写。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod=1e9+7;
char c[10005];
LL n,k,f[10005][105][2];
int main()
{
	cin>>(c+1)>>k;
	n=strlen(c+1);
	f[n+1][0][0]=f[n+1][0][1]=1;
	for(int i=n;i>=1;i--)
	{
		for(int j=0;j<=k-1;j++)
		{
			for(int l=0;l<=9;l++)
			{
				LL t=((j-l)%k+k)%k; 
				f[i][j][0]=(f[i][j][0]+f[i+1][t][0])%mod;
				if(l<c[i]-'0')f[i][j][1]=(f[i][j][1]+f[i+1][t][0])%mod;
				if(c[i]-'0'==l)f[i][j][1]=(f[i][j][1]+f[i+1][t][1])%mod;
			}
		}
	}
	cout<<(f[1][0][1]-1+mod)%mod<<endl;
}
```



---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17405449.html)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_s)

第一道数位 $\text{dp}$，检验一下自己懂没懂。

特别感谢 [$\text{yinhee}$](https://www.luogu.com.cn/user/578590) 大佬，他的讲解令我受益匪浅。

## 题目分析

$dp_{pos,res,lim}$ 为当前枚举到从高位往低位数第 $pos$ 位，数字和取模后的余数为 $res$ 时的方案数，其中 $lim$ 可以理解为一个布尔值，$0$ 表示没有到上限，$1$ 表示到了上限。

然后是一个数位 $\text{dp}$ 的板子，我特别讲一下这一行代码：

```cpp
tot+=dfs(pos-1,(res+i)%d,(lim!=0)&&(i==maxx));
```

其中 $maxx$ 是当前枚举位可选的最大值。

这里就是在枚举第 $pos-1$ 位，选择了 $i$ 作为这位的数，$res+i$ 就是新的数字和。而后面的判断条件就是在看枚举到目前为止，该数是否还与 $k$ 的前缀相同，是就说明到目前为止还是最大的，否则就不是。

## 贴上代码

```cpp
#include<bits/stdc++.h>
// #define int long long
#define ok printf("1")
#define no printf("0")
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int mod=1e9+7;
const int maxn=10010;
const int maxm=110;
int n,d;
int a[maxn];
int dp[maxn][maxm][2];
string s;
int dfs(int pos,int res,int lim){
	if(pos==0){
		if(res==0) return 1;
		else return 0;
	}
	if(dp[pos][res][lim]!=-1) return dp[pos][res][lim];
	int maxx=9,tot=0;
	if(lim!=0) maxx=a[pos];
	for(register int i=0;i<=maxx;++i){
		tot+=dfs(pos-1,(res+i)%d,(lim!=0)&&(i==maxx));tot%=mod;
	}
	dp[pos][res][lim]=tot;
	return tot;
}
inline void init(){
	cin>>s;n=s.size();
	cin>>d;
	for(register int i=0;i<n;++i) a[n-i]=s[i]-48;
	memset(dp,-1,sizeof(dp));
}
int main(){
	init();
	printf("%d",(dfs(n,0,1)-1+mod)%mod);
}
```

---

## 作者：chlchl (赞：0)

挺简单一道题，水水社贡吧。

## 题意简述
给定 $k,d$（$k\leq 10^{10000}$），问 $[1,k]$ 中有多少个数的数字和是 $d$ 的倍数，答案对 $10^9+7$ 取模。

## 做法
数位 DP 入门。

用字符串读入 $k$，然后设计状态：$f_{len,op,q}$ 表示填到从低往高数的第 $len$ 位，最高位是否被限制，当前数字和 $\bmod\ d$ 为 $q$ 的数字个数。

其他的基本上就是数位 DP 的模板了，不会的看 [这里](https://www.luogu.com.cn/blog/hugocaicai/shuo-wei-dp-xue-xi-bi-ji) 吧。

注意最后取模可能会出现负数，需要转正。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MOD = 1e9 + 7;
const int N = 1e4 + 10;
char k[N];
int n, d, dgt[N], f[N][2][110];

ll dp(int len, int op, int q){
	if(!len)
		return (q == 0 ? 1 : 0);
	if(f[len][op][q] != -1)
		return f[len][op][q];
	int lim = (op ? dgt[len] : 9);
	ll cnt = 0;
	for(int i=0;i<=lim;i++){
		(cnt += dp(len - 1, op & (i == lim), (q + i) % d)) %= MOD;
	}
	return f[len][op][q] = cnt;
}

ll solve(){
	for(int i=1;i<=n;i++)
		dgt[i] = k[n - i + 1] - '0';
	memset(f, -1, sizeof(f));
	return (dp(n, 1, 0) - 1) % MOD;
}

int main(){
	scanf("%s", k + 1);
	scanf("%d", &d);
	n = strlen(k + 1);
	printf("%lld\n", (solve() + MOD) % MOD);//负数转正
	return 0;
}
```


---

## 作者：novax (赞：0)

[题面](https://www.luogu.com.cn/problem/AT4540)

### 题意

求 $1 \sim K$ 间共有多少个数字各位数字之和为 $D$ 的倍数。

### 思路

**数位dp。**

设 $F_{i,j,k}$ 表示当前从高往低处理到第 $i$ 位，各位数字之和为模 $D$ 等于 $j$ 的数字个数。$k$ 则表示当前状态此前的前缀数字是否与给出的数字 $K$ 的相同，相同为 $1$，不同则为 $0$。则有转移方程 $F_{i,j,k}=\sum_{a=0}^{maxa} F_{i-1,(a+j)\bmod D ,k'}$。

其中 $a$ 为当前枚举的一位的数字，当当前的前缀不与给出的 $K$ 完全相同时，$maxa$ 为 $9$；完全相同时，则为数字 $K$ 在这一位上的值。在当前的前缀与 $K$ 不完全相同或与此时 $K$ 的前缀相同但当前枚举到的 $a$ 不等于 $maxa$ 时，前缀都不会与 $K$ 相同，所以此时 $k'$ 都为 $0$；否则 $k'$ 则为 $1$。

按照转移方程用记忆化搜索转移，时间复杂度 $O(nD)$，其中 $n$ 为 $K$ 的位数。

### 代码

```cpp
#include <cstdio>
const int mod=1e9+7;
void swp(int &a,int &b){int c;c=a;a=b;b=c;}
char K[10020];
int N,D,a[10020];
long long F[10020][103][2];
long long solve(int i,int j,int k)
{
	if(i==0)
		return j==0;
	if(F[i][j][k]!=-1)
		return F[i][j][k];
	int ret,jm,now;
	ret=0;
	jm=(k==1)?a[i]:9;
	for(now=0;now<=jm;now++)
	{
		ret+=solve(i-1,(j+now)%D,(k==1)&&(now==jm));
		ret%=mod;
	}
	F[i][j][k]=ret;
	return ret;
}
int main()
{
	scanf("%s%d",K+1,&D);
	for(N=1;K[N];N++)
		a[N]=K[N]-'0';
	N--;
	int i,j,k;
	for(i=1;i<=(N-i+1);i++)
		swp(a[i],a[N-i+1]);
	for(i=0;i<=N;i++)
		for(j=0;j<=D;j++)
			F[i][j][0]=F[i][j][1]=-1;
	printf("%lld\n",(solve(N,0,1)+mod-1)%mod);
}
```


---

