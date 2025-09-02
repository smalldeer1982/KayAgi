# Igor and Interesting Numbers

## 题目描述

Igor likes hexadecimal notation and considers positive integer in the hexadecimal notation interesting if each digit and each letter in it appears no more than $ t $ times. For example, if $ t=3 $ , then integers 13a13322, aaa, abcdef0123456789 are interesting, but numbers aaaa, abababab and 1000000 are not interesting.

Your task is to find the $ k $ -th smallest interesting for Igor integer in the hexadecimal notation. The integer should not contain leading zeros.

## 说明/提示

The first 20 interesting integers if $ t=1 $ : 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, d, e, f, 10, 12, 13, 14, 15. So the answer for the first example equals 12.

## 样例 #1

### 输入

```
17 1
```

### 输出

```
12
```

## 样例 #2

### 输入

```
1000000 2
```

### 输出

```
fca2c
```

# 题解

## 作者：zplqwq (赞：4)

[CF747F] Ignor and Interesting Numbers 解题报告

我们知道，三位数显然是大于两位数的，所以我们可以先确定第 $k$ 大的有趣的十六进制数有几位。

我们令 $dp_{i,j}$ 表示目前用了 $i$ 个数，填了 $j$ 个位置的方案数。需要注意的是，因为我们求的是方案数，所以并不需要按照从小到大的顺序统计，只需要最后答案是对的即可，所以我们不放考虑从小到大枚举 $i$。

考虑 $dp_{i,j}$ 怎么转移，我们枚举一个 $k$ ，表示当前数 $i$ 要填多少个，$\text{len}$ 表示当前枚举的位数。

$dp_{i,j}=dp_{i-1,j-k}*\binom{len-j+k}{k}$ 最后那个组合数意义是总共有 $\text{len}$ 个可以放数的位置，前 $i-1$ 个数已经占用了 $j-k$ 个位置，那么还剩下 $len-(j-k)$ 个位置可以填数，我们要在这么多个位置中选 $k$ 个。

对于每一个 $\text{len}$ ，其对应的方案数都是 $dp_{15,len}$ 。所以当我们求出来第一个 $\text{len}$ 使得 $dp_{15,len} \ge k$ 的时候就代表我们找到了答案的 $\text{len}$。

确定了位数之后我们再来确定每一个数是啥，此时我们从高位往低位填，对于每一个位置，从小往大试，也就是枚举每一位的值。对于位置 $i$，枚举的值 $k$，那么我们求出以 $k$ 开头且长度为 $len-i+1$ 的有趣的数的数量，此时找到第一个 $k$ 使得此时的总数量 $\ge$ 剩余的 $k$，那么第 $i$ 位就应该填 $k$。

考虑我们要求的以 $k$ 开头且长度为 $len-i+1$ 的有趣的数其实跟这个开头的数没有什么关系，这个 $k$ 对后面的影响仅限于能用的 $k$ 的数量少了一个，这个在 dp 的时候你看一下当前能不能填这么多就完了。所以这个问题就转化成了求长度为 $len-i$ 的有趣的数的数量，这个问题又变成了我们之前会做的那个问题。

然后需要考虑一下边界问题。对于一开始求长度为 $\text{len}$ 的有趣的数的方案数我们并不知道第一位是啥，所以 $dp_{0,j}=\binom{len-1}{j}$。但是在确定了长度之后对于非首位的位置由于我们已经知道了第一位是啥所以此时 $0$ 就可以随便填了，对于首位，我们枚举其值的时候从 $1$ 枚举就可以了。

由于 $t$  非常小，所以就算每一个数都出现 $t$ 次，此时也只有 $16\times t$ 位，所以复杂度是正确的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=20,M=2e5;
int dp[N][N],k,t,lft[N],c[110][110];//lft表示当前数还剩多少个可以填
void pre(){
	for(int i=0;i<=100;i++) c[i][0]=1;
	for(int i=1;i<=100;i++){
		for(int j=1;j<=i;j++){
			c[i][j]=c[i-1][j]+c[i-1][j-1];
		}
	}
}
signed main(){
	cin>>k>>t;
	int l;pre();
	for(int i=0;i<=15;i++) lft[i]=t;
	for(int len=1;len<=16*t;len++){
		memset(dp,0,sizeof(dp));
		for(int i=0;i<=min(len-1,lft[0]);i++) dp[0][i]=c[len-1][i];
		for(int i=1;i<=15;i++){
			for(int j=0;j<=len;j++){
				for(int k=0;k<=min(j,lft[i]);k++){
					dp[i][j]+=dp[i-1][j-k]*c[len-j+k][k];
				}
			}
		}
		// if(len==2) cout<<dp[15][len]<<endl;
		if(dp[15][len]>=k) {l=len;break;}
		k-=dp[15][len];
	}
	// cout<<l<<endl;
	for(int pos=1;pos<=l;pos++){
		if(pos==1){
			for(int num=1;num<=15;num++){
				lft[num]--;
				memset(dp,0,sizeof(dp));
				for(int i=0;i<=min(l-pos,lft[0]);i++) dp[0][i]=c[l-pos][i];
				for(int i=1;i<=15;i++){
					for(int j=0;j<=l-pos;j++){
						for(int k=0;k<=min(j,lft[i]);k++){
							dp[i][j]+=dp[i-1][j-k]*c[l-pos-j+k][k];
						}
					}
				}
				if(dp[15][l-pos]>=k){
					if(num>=10){cout<<char('a'+num-10);}
					else cout<<num; 
					break;
				}
				k-=dp[15][l-pos];
				lft[num]++;
			}
			
		}
		else{
			for(int num=0;num<=15;num++){
				lft[num]--;
				memset(dp,0,sizeof(dp));
				for(int i=0;i<=min(l-pos,lft[0]);i++) dp[0][i]=c[l-pos][i];
				for(int i=1;i<=15;i++){
					for(int j=0;j<=l-pos;j++){
						for(int k=0;k<=min(j,lft[i]);k++){
							dp[i][j]+=dp[i-1][j-k]*c[l-pos-j+k][k];
						}
					}
				}
				if(dp[15][l-pos]>=k){
					// cout<<num<<"qwq\n";
					if(num>=10){cout<<char('a'+num-10);}
					else cout<<num; 
					break;
				}
				k-=dp[15][l-pos];
				lft[num]++;
			}
		}
	}
	return 0;
}
```





---

## 作者：PPL_ (赞：3)

# 前言

讲过没听懂，再讲没调出来的题——有价值的题，需要写题解的题

# 题目

[洛谷](https://www.luogu.com.cn/problem/CF747F)

[CF](http://codeforces.com/problemset/problem/747/F)

# 讲解

配合代码食用更佳

这题用$DP$应该很好看出来吧(只是可能会想到奇怪的状压= =)

首先我们发现我们受到了数字长度的限制，不知道长度使我们的转移难上加难，所以我们先要把该数字的长度算出来

**这是一个DP：(getlen函数)**

我们令$dp[i][j]$为只使用前$i$个数字，目前填了$j$个位置的方案数(当然是忽略了前导零的)

然后我们选择暴力枚举长度，计算出每种长度的方案数加上后是否达到了$k$，如果达到了，那么说明该数的长度为$k$，没达到就减去，为之后统计答案做准备

设枚举长度为$len$

由于忽略了前导零，所以$dp[0][i]=C(len-1,i)$(习惯这么表达组合数= =)

对于其它的$dp[i][j]$，我们考虑从$dp[i-1][j-k]$转移

上一个状态是填了$j-k$个位置，剩下$len-(j-k)$个位置，我们要填$k$个位置

那么$dp[i][j] = \sum^{min \{j,t\}}_{k=0} dp[i-1][j-k]*C(len-(j-k),k)$

然后我们就可以计算出该数字的长度了

**这是另一个DP：(solve函数)**

接下来我们要考虑在知道长度的情况下的第$k$小的数字是什么(因为我们已经把长度小于该数的数减掉了)

其实与上面的思路和DP都很类似

我们 **从高位到低位** 再 **从小到大** 枚举当前位置的数字

然后用类似的方法统计个数，看是否达到$k$，没达到就减去

由于我们枚举了当前位置的数字，所以在用DP统计方案数的时候0就可以作为首位计算

仍然是这个式子，只是$len$的含义不同了，是没选的位置的长度

$dp[i][j] = \sum^{min \{j,t\}}_{k=0} dp[i-1][j-k]*C(len-(j-k),k)$

当然我们还是需要特殊处理$i=0$的时候的DP值

因为$0$之前没有状态了，无法从前面转移

我们发现如果$j \neq k$，那么由于无法从前面转移，那么方案数为0

否则就是$C(len-j,k)$，方案数依然是$C($总长$-$已填长度$=$剩余长度$,$选填长度$)$

所以两个DP只是有一个要不要管前导零的区别

# 代码
```cpp
//12252024832524
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 165;
const int MAXJZ = 16;
int n,t,len;
int lim[MAXJZ];
char dic[MAXJZ];
LL C[MAXN][MAXN],dp[MAXN][MAXN];

int Read()
{
	int x = 0,f = 1;char c = getchar();
	while(c > '9' || c < '0'){if(c == '-')f = -1;c = getchar();}
	while(c >= '0' && c <= '9'){x = (x*10) + (c^48);c = getchar();}
	return x * f;
}
void Put1(int x)
{
	if(x > 9) Put1(x/10);
	putchar(x%10^48);
}
void Put(int x,char c = -1)
{
	if(x < 0) putchar('-'),x = -x;
	Put1(x);
	if(c >= 0) putchar(c);
}
template <typename T>T Max(T x,T y){return x > y ? x : y;}
template <typename T>T Min(T x,T y){return x < y ? x : y;}
template <typename T>T Abs(T x){return x < 0 ? -x : x;}

void pre()
{
    C[0][0] = 1;
    for(int i = 1;i <= 160;++ i)//其实20左右就够用了
    {
        C[i][0] = 1;
        for(int j = 1;j <= i;++ j)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
    for(int i = 0;i <= 9;++ i) dic[i] = '0' + i;
    for(int i = 10;i < MAXJZ;++ i) dic[i] = 'a' + i - 10;
}
void getlen()
{
    for(len = 1;;++len)
    {
        memset(dp,0,sizeof(dp));
        for(int i = 0;i < Min(len,t+1);++ i) dp[0][i] = C[len-1][i];
        for(int i = 1;i < MAXJZ;++ i)
        {
            for(int j = 0;j <= len;++ j)//现在的总长度
            {
                for(int k = 0;k <= Min(j,t);++ k)//填k个i
                    dp[i][j] += dp[i-1][j-k] * C[len-(j-k)][k];
            }
        }
        if(dp[15][len] >= n) break;
        n -= dp[15][len];
    }
    //printf("len : %d\n",len);
}
void solve()
{
    //printf("less : %d\n",n);//935395
    LL dz;
    for(int i = 0;i < MAXJZ;++ i) lim[i] = t;
    for(int LEN = len;LEN >= 1;-- LEN)
    {
        int MIN = 0 + (LEN == len);//这一位是否能为0
        for(int i = MIN;i < MAXJZ;++ i)//枚举当前这一位
        {
            if(!lim[i]) continue;
            memset(dp,0,sizeof(dp));
            lim[i]--;
            //需要填的长度：LEN-1
            for(int j = 0;j < MAXJZ;++ j)//枚举现在填什么数字
                for(int lennow = 0;lennow <= LEN-1;++ lennow)//现在的长度
                    for(int k = 0;k <= Min(lennow,lim[j]);++ k)//填k个j
                    {
                        if(!j)
                        {
                            if(k == lennow) dz = 1;
                            else dz = 0;
                        }
                        else dz = dp[j-1][lennow-k];
                        dp[j][lennow] += dz * C[LEN-1-(lennow-k)][k];
                    }
            if(dp[15][LEN-1] >= n)
            {
                putchar(dic[i]);
                break;
            }
            n -= dp[15][LEN-1];
            lim[i]++;
        }
    }
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    n = Read(); t = Read();
    pre();
    getlen();
    solve();
	return 0;
}
```

---

## 作者：gSE2xWE (赞：2)

[更好的阅读体验](https://www.cnblogs.com/loney-s/p/13343675.html)

~~其实作者只是单纯地骗阅读量~~

# 题目

[传送门](https://www.luogu.com.cn/problem/CF747F)

# 思路

求第k大的题大多都是要一位一位的来求

我们考虑固定了首位有多少种情况

设$tot_i$表示数字$i$还能选多少次

$dp_{i,j}$表示前i个数一共占了j个位置

$dp_{i,j}=\sum_{k=0}^{min(j,tot_i)}dp_{i-1,j-k}*C_j^k$

方程的意义即为考虑第i个数加入的时候的情况

但是注意，这个dp求出来的方案一定是固定了有多少位的，并且不保证没有前导0

但是通过这个dp，我们只需要枚举首位是什么就可以得到没有前导0的情况，但是同样的，**这里一样数位是固定的**

我们可以通过先求出数位再一位一位试着填进去就可以得到答案

# 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,t,_ind;
int tot[18],cho[18];
long long mem[205][205],f[205][205];
long long C(int n,int m)
{
    if(mem[n][m])
        return mem[n][m];
    long long ret=1;
    for(int i=n;i>=n-m+1;i--)
        ret=ret*i/(n-i+1);
    return mem[n][m]=ret;
}
long long dp1(int len)//带前导0,但是固定了位数
{
    if(len==0)
        return 1;
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=1;i<=16;i++)
    {
        for(int j=0;j<=len;j++)
            for(int k=0;k<=tot[i]&&k<=j;k++)
                f[i][j]+=f[i-1][j-k]*C(j,k);
    }
    return f[16][len];
}
long long dp2(int len)//不带前导0,同样要固定位数
{
    long long ret=0;
    for(int i=2;i<=16;i++)
    {
        if(tot[i])
        {
            tot[i]--;
            ret+=dp1(len-1);
            tot[i]++;
        }
    }
    return ret;
}
int main()
{
    cin>>n>>t;
    for(int i=1;i<=16;i++)
        tot[i]=t;
    for(int i=1;i<=18;i++)
    {
        long long k=dp2(i);
        if(k>=n)
        {
            _ind=i;
            break;
        }
        n-=k;
    }
    for(int i=_ind;i>=1;i--)
    {
        for(int j=1;j<=16;j++)
        {
            if(i==_ind&&j==1)
                continue;
            if(tot[j]==0)
                continue;
            tot[j]--;
            long long ret=dp1(i-1);
            if(ret>=n)
            {
                cho[i]=j;
                break;
            }
            tot[j]++;
            n-=ret;
        }
    }
    for(int i=_ind;i>=1;i--)
    {
        if(cho[i]<=10)
            cout<<cho[i]-1;
        else
            cout<<(char)('a'+cho[i]-11);
    }
    return 0;
}
```



---

## 作者：violin_wyl (赞：1)

# Igor and Interesting Numbers

## 解析： 

写的时候大概思路没什么问题，但降智用乱搞选数调了 1 小时。

首先肯定是对这个十六进制数按照位数讨论，即如果记 $num_i$ 表示 $i$ 位“有趣的数”有多少个，那么就需要找一个最小的 $i$，使得:  $(\sum_{j=0}^{i}num_j)\geq k$ ，那第 $k$ 小的数就一定是个 $i$ 位数。

考虑怎么找这个 $i$ ，我本来直接组合数选数，然后发现会有重复计算的情况，所以就寄了。

考虑 dp，设 $dp_{i,j}$ 表示前 $i$ 个十六进制位当前用了 $j$ 个数。转移和 NOIP2021T2 一模一样：
$$
dp_{i,j}=\sum_{k=0}^{min(t,j)} dp_{i-1,j-k}\times C_{len-(j-k)}^{k}
$$
其中 $k$ 表示当前的第 $i$ 位选 $k$ 个数，$len-(j-k)$ 表示在 $i-1,j-k$ 的情况下还有多少个位置可以填。

我们令 $len=1\to 16\times n$，如果当前的 $i$ 位有趣的数的数量比 $k$ 小，那令 $k\leftarrow k-num_i$ ，直到 $num_i\geq k$。

 现在我们确定了 $i$ 位，考虑如何确定这个数，设计的 dp 状态和前半部分一样，考虑从高位往低枚举每一位放什么数，假设当前在选第 $i$ 位，那剩下未选的数位有 $len-i$（前半部分找到的 $i$ 称为 $len$），dp 看当前位放 $j$ 是否可以达到了 $k$，未达到就令 $k\leftarrow  k-num_i$，以此类推。

时间复杂度 $\mathcal O(16\times n\times len^2+len^2\times 16^2\times n)$，$len$ 表示 $i$ 的期望位数，大概不会超过 $20$。

具体看代码吧。

----------------------------------------------------

## code：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100 + 10;
const int INF = 2e9;
typedef pair <int, int> pii;
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <='9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int n, k;
int c[N][N];
int dp[N][N];
int lim[16];
void init ( )
{
    for (int i = 0; i <= 100; i++) c[i][0] = 1;
    for (int i = 1; i <= 100; i++)
        for (int j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]);
}
int solve (int len, bool flag)
{
    memset (dp, 0, sizeof (dp));
    for (int i = 0; i <= min (len - flag, lim[0]); i++) dp[0][i] = c[len - flag][i];
    for (int i = 1; i < 16; i++)
        for (int j = 0; j <= len; j++)
            for (int k = 0; k <= min (j, lim[i]); k++)
                dp[i][j] += dp[i - 1][j - k] * c[len - (j - k)][k];
    return dp[15][len];
}
signed main()
{
    k = read ( ), n = read ( );
    init ( ); int len;
    for (int i = 0; i < 16; i++) lim[i] = n;
    for (len = 1; len <= 16 * n; len++)
    {
        int cnt = solve (len, 1);
        if (cnt >= k) break;
        else k -= cnt;
    }
    for (int i = 1; i <= len; i++)
        for (int j = (i == 1) ? 1 : 0; j < 16; j++)
        {
            lim[j]--;
            int cnt = solve (len - i, 0);
            if (cnt >= k) { printf ("%llx", j); break; }
            else k -= cnt;
            lim[j]++;
        }
    return 0;
}
```



---

## 作者：Jsxts_ (赞：1)

做了一上午，写篇题解纪念。

首先看到求第 $k$ 小，自然地想到二分。我们二分答案，每次 $\text{check}$ 求出 $1\sim mid$ 的有趣数的个数，如果 $>k$ 往左找，否则往右找。

现在问题就转换成如何实现 $\text{check}$。

首先，先思考一个问题：一个 $n$ 位 $16$ 进制数，每一位可以填一个数，并要求 $i$ 的个数不超过 $c_i$，问有多少种填数方案？这其实就是 $\text{check}$ 函数去掉 $lim$ 限制后的内容（$lim$ 限制就是，假设 $mid=12345$，那么填数就填不到 $12346$ ）。对于这个问题，用记搜或 $DP$ 解决都可以。记搜代码如下：

```cpp
ll dfs(int x,int d,int s) {//记搜就枚举每个数（0~15）的出现次数，s是已填数的个数，d是位数 
	if (x > 15) return s == d;
	if (f[x][s] != -1) return f[x][s];
	ll res = 0;
	for (int i = 0;i <= t - c[x] && s + i <= d;i ++ ) {
		res += dfs(x+1,d,s+i) * C[d-s][i];//这里可以理解为：已填s个数，剩下d-s个空位选i个空填数，共C(d-s,i)种 
	}
	return f[x][s] = res;
}
```

再考虑有 $lim$ 的情况。当这个数的位数小于 $mid$ 时，没有限制，所以判掉前导零后用上面的方法做。当位数和 $mid$ 相同时，可以枚举前缀，钦定这些位都与 $mid$ 对应位相等，然后下一位强制小于 $mid$ 的对应位，这样剩下的位置一样咋填都行，也记搜处理。最后注意判断 $mid$ 本身行不行，因为前面的计数都没有算到。

输出十六进制可以用 $\text{\%llx}$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	int s = 0,f = 1; char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s * 10 + ch - '0'), ch = getchar();
	return s * f;
}
int k,t,cnt,a[100010],c[16];
int C[20][20];
ll f[16][110];
void init() {
	C[0][0] = 1;
	for (int i = 1;i <= 19;i ++ ) {
		C[i][0] = 1;
		for (int j = 1;j <= i;j ++ ) C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
}
ll dfs(int x,int d,int s) {//记搜就枚举每个数（0~15）的出现次数，s是已填数的个数，d是位数 
	if (x > 15) return s == d;
	if (f[x][s] != -1) return f[x][s];
	ll res = 0;
	for (int i = 0;i <= t - c[x] && s + i <= d;i ++ ) {
		res += dfs(x+1,d,s+i) * C[d-s][i];//这里可以理解为：已填s个数，剩下d-s个空位选i个空填数，共C(d-s,i)种 
	}
	return f[x][s] = res;
}
ll check(ll x) {
	ll t = x; cnt = 0;
	while (x) a[++cnt] = x % 16, x /= 16;
	ll ans = 0;
	memset(c,0,sizeof c);
	for (int i = 1;i < cnt;i ++ ) {//位数不到mid 
		for (int j = 1;j <= 15;j ++ ) {
			c[j] ++;
			memset(f,-1,sizeof f);//记搜要清空 
			ans += dfs(0,i-1,0);
			c[j] --;
		}
	}
	for (int i = cnt;~i;i -- ) { 
		if (!i) ans ++;
		for (int j = 0;j < a[i];j ++ ) {//这一位不能到a[i] 
			if (c[j] == t || (!j && i == cnt)) continue;//同样，第一位不能是0 
			memset(f,-1,sizeof f);
			c[j] ++;
			ans += dfs(0,i-1,0);
			c[j] --;
		}
		c[a[i]] ++;
		if (c[a[i]] > t) break;
	}
	return ans;
}
int main() {
	init();
	k = read(), t = read();
	ll l = 1,r = 1e18;
	while (l < r) {
		ll mid = l + r + 1 >> 1;
		if (check(mid) <= k) l = mid;
		else r = mid - 1;
	}
	printf("%llx",l);
	return 0;
}
```


---

