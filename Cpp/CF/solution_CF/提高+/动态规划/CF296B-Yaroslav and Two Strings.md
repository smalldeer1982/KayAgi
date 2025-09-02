# Yaroslav and Two Strings

## 题目描述

Yaroslav thinks that two strings $ s $ and $ w $ , consisting of digits and having length $ n $ are non-comparable if there are two numbers, $ i $ and $ j $ $ (1<=i,j<=n) $ , such that $ s_{i}&gt;w_{i} $ and $ s_{j}&lt;w_{j} $ . Here sign $ s_{i} $ represents the $ i $ -th digit of string $ s $ , similarly, $ w_{j} $ represents the $ j $ -th digit of string $ w $ .

A string's template is a string that consists of digits and question marks ("?").

Yaroslav has two string templates, each of them has length $ n $ . Yaroslav wants to count the number of ways to replace all question marks by some integers in both templates, so as to make the resulting strings incomparable. Note that the obtained strings can contain leading zeroes and that distinct question marks can be replaced by distinct or the same integers.

Help Yaroslav, calculate the remainder after dividing the described number of ways by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

The first test contains no question marks and both strings are incomparable, so the answer is $ 1 $ .

The second test has no question marks, but the given strings are comparable, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
2
90
09
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
11
55
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
?????
?????
```

### 输出

```
993531194
```

# 题解

## 作者：EuphoricStar (赞：25)

## 思路

dp。

设 $f_{i,0/1,0/1}$ 表示当前考虑到第 $i$ 位，当前否/是存在 $i$ 使得 $s_i < w_i$，当前否/是存在 $i$ 使得 $s_i > w_i$。

转移就枚举新添加的两个字符（$s_i$ 和 $w_i$），设它们分别为 $ch1,ch2$。则有：

$$f_{i,j|[ch1<ch2],k|[ch1>ch2]} \gets f_{i,j|[ch1<ch2],k|[ch1>ch2]} + f_{i-1,j,k}$$

最终的答案即为 $f_{n,1,1}$。时间复杂度 $O(n)$（大常数）。

## 代码

[code](https://pastebin.ubuntu.com/p/Gz2wdRbM5S/)

---

## 作者：Yahbim (赞：11)

## 题意

如果两个只包含数字且长度为 $n$ 的字符串 $s$ 和 $w$ 存在两个数字 $\leq i,j\leq n$，使得 $s_i<w_i,s_j>w_j$，则称 $s$ 和 $w$ 是不可比的。现在给定两个包含数字和问号且长度为 $n$ 的字符串，问有多少种方案使得将所有问号替换成 0 到 9 的数字后两个字符串是不可比的？

### 题解

说实话我感觉这题并没有要用 DP 的理由……每个位置对答案的贡献都是独立的，不依赖于前面的状态，这应该已经可以直接做了吧。

然后贡献合并时也差不多是或的形式，只要有一个位置满足式子即可。因此考虑容斥。

把使得 $a_i\leq b_i$、$b_i\leq a_i$、$a_i=b_i$  恒成立的方案数挑出来，再计算出所有可能的方案数即可。

要算相等的情况的原因是，对于小于和等于同时存在的方案，如果是用严格小于去求，会导致漏掉这些解；如果把这些解放到小于里头用不严格小于去算，最极端的都相等的情况会被算两次，所以加回来一次。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
const ll P=1e9+7;

int n,cnt;char a[N],b[N];
ll ans1=1,ans2=1,ans3=1;

ll quickpow(ll x,int y,ll ret=1){
    for(;y;x=x*x%P,y>>=1) if(y&1) ret=ret*x%P;
    return ret;
}

signed main(){
    scanf("%d%s%s",&n,a+1,b+1);
    for(int i=1;i<=n;++i)
		cnt+=(a[i]=='?')+(b[i]=='?');
    for(int i=1;i<=n&&ans1;++i)
		ans1=ans1*(a[i]=='?'?(b[i]=='?'?55:10-b[i]+'0'):(b[i]=='?'?a[i]-'0'+1:a[i]>=b[i]))%P;
    for(int i=1;i<=n&&ans2;++i)
		ans2=ans2*(b[i]=='?'?(a[i]=='?'?55:10-a[i]+'0'):(a[i]=='?'?b[i]-'0'+1:b[i]>=a[i]))%P;
    for(int i=1;i<=n&&ans3;++i)
		ans3=ans3*(a[i]=='?'?(b[i]=='?'?10:1):(b[i]=='?'?1:a[i]==b[i]))%P;
    printf("%d\n",((quickpow(10,cnt)-ans1-ans2+ans3)%P+P)%P);
    return 0;
}

//~kawaii~

```

---

## 作者：Werner_Yin (赞：6)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/13306330.html)
# 题目
[传送门](https://codeforces.com/contest/296/problem/B)

## 题目大意

> 如果两个只包含数字且长度为 $n$ 的字符串 $s$ 和 $w$ 存在两个数字 $1≤i,j≤n$，使得 $s_i<w_i,s_j>w_j$ ,则称 $s$ 和 $w$ 是不可比的。现在给定两个包含数字和问号且长度为 $n$ 的字符串，问有多少种方案使得将所有问号替换成 $0$ 到 $9$ 的数字后两个字符串是不可比的？

# 思路
## 分析
DP 题， 我们注意到，只要有一对这样的数就可以满足条件，而等于是不属于判断情况的，因此我们要单独记一个状态。

## 状态
```
f[i][k]: 当在第 $i$ 位时，第 $k$ 种情况的方案数。
以下： j < i
k = 0 : 前面只出现了 s[j] < w[j] 的情况，并没有 s[j] > w[j] ，即 s[j] <= w[j]
k = 1 : 前面 s[j] < w[j] , s[j] > w[j]
k = 2 : 前面只出现了 s[j] > w[j] 的情况，并没有 s[j] < w[j] ,即 s[j] >= w[j]
k = 3 : 前面只有 s[j] == w[j] 情况
```

## 转移
我们要对每一位考虑该位上填每个数字的情况。

对于已经确定数字的位，我们要只要对该数字讨论。

如果有'?',我们要枚举 1~9 进行转移。

~~感觉有点像数位DP？~~

## 初始状态
```cpp
f[0][3] = 1
```
# 代码
按照各种状态进行转移即可，代码量有点大。

当然，也有一种代码量小的解法，可以预先算出每种情况转移，就不必枚举。
 ```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>

#define ll long long
using namespace std;

const int MAXN = 1e5+10;
const ll mod = 1e9+7;

int n;
ll f[MAXN][4];
char s[MAXN],w[MAXN];

int main (){
	scanf("%d",&n);
	scanf("%s",s+1);
	scanf("%s",w+1);
	f[0][0] = f[0][1] =f[0][2] = 0;
	f[0][3] = 1;
	for(int i = 1;i <= n;i++){
		if(s[i] != '?' &&w[i] != '?'){
			if(s[i] > w[i]) {
				f[i][0] = 0;
				f[i][1] = f[i-1][0] + f[i-1][1];
				f[i][2] = f[i-1][2] + f[i-1][3];
				f[i][3] = 0;
			} else if(s[i] == w[i]){
				f[i][0] = f[i-1][0];
				f[i][1] = f[i-1][1];
				f[i][2] = f[i-1][2];
				f[i][3] = f[i-1][3];
			} else{
				f[i][0] = f[i-1][0] + f[i-1][3];
				f[i][1] = f[i-1][2] + f[i-1][1];
				f[i][2] = 0;
				f[i][3] = 0;
			}
		} else if(s[i] == '?' && w[i] != '?'){
			for(int j = '0';j < w[i] ;j++){
				f[i][0] += f[i-1][0] + f[i-1][3];
				f[i][1] += f[i-1][1] + f[i-1][2];
				f[i][2] += 0;
			}
			f[i][0] += f[i-1][0];
			f[i][1] += f[i-1][1];
			f[i][2] += f[i-1][2];
			f[i][3] += f[i-1][3];
			for(int j = w[i] + 1;j <= '9';j++){
				f[i][1] += f[i-1][0] + f[i-1][1];
				f[i][2] += f[i-1][2] + f[i-1][3];
			}
		} else if(s[i] != '?' && w[i] == '?'){
			
			for(int j = '0' ;j < s[i] ;j++){
				f[i][1] += f[i-1][0] + f[i-1][1];
				f[i][2] += f[i-1][2] + f[i-1][3];
			}
			f[i][0] += f[i-1][0];
			f[i][1] += f[i-1][1];
			f[i][2] += f[i-1][2];
			f[i][3] += f[i-1][3];
			for(int j = s[i] +1;j <= '9' ;j++){
				f[i][0] += f[i-1][0] + f[i-1][3];
				f[i][1] += f[i-1][1] + f[i-1][2];
			}
		} else{
			for(int j = 0;j < 10;j++){
				for(int k = 0;k < 10;k++){
					if(j<k){
						f[i][0] += (f[i-1][0] + f[i-1][3])%mod;
						f[i][1] += (f[i-1][1] + f[i-1][2])%mod;
					} else if(j == k){
						f[i][0] += f[i-1][0];
						f[i][1] += f[i-1][1];
						f[i][2] += f[i-1][2];
						f[i][3] += f[i-1][3];
					} else{
						f[i][1] += (f[i-1][0] + f[i-1][1])%mod;
						f[i][2] += (f[i-1][2] + f[i-1][3])%mod;
					}
					f[i][0] %= mod;
					f[i][1] %= mod;
					f[i][2] %= mod;
				}
			}
		}
		f[i][0] %= mod;
		f[i][1] %= mod;
		f[i][2] %= mod;
	}
	printf("%d",f[n][1] % mod);
	return 0;
}
```

---

## 作者：BootsH (赞：3)

考虑暴力递推。


### 状态

本题有4种状态。

我们用 $dp_{i, st}$ 来表示在第 i 位上，状态为 st 的方案数。

* $st=0$ 表示之前仅有 $s_{j} \leq w_{j}$  
* $st=1$ 表示之前同时出现 $s_{j_{1}} < w_{j_{1}}$ 和 $s_{j_{2}} > w_{j_{2}}$
* $st=2$ 表示之前仅有 $s_{j} \geq w_{j}$
* $st=3$ 表示之前仅有 $s_{j} = w_{j}$

### 转移
对于出现 `'?'` 的情况，我们从0到9进行枚举。枚举时注意用字符 `'0'` 到 `'9'`。

* 当 $s_{i} < w_{i}$ 时，$dp_{i, 0}$ 可以从 $dp_{i - 1, 0}$ 和 $dp_{i - 1, 3}$ 转移来。$dp_{i, 1}$ 可以从 $dp_{i - 1, 1}$ 和 $dp_{i - 1, 2}$ 转移来。
* 当 $s_{i} > w_{i}$ 时，$dp_{i, 1}$ 可以从 $dp_{i - 1, 0}$ 和 $dp_{i - 1, 1}$ 转移来。$dp_{i, 2}$ 可以从 $dp_{i - 1, 2}$ 和 $dp_{i - 1, 3}$ 转移来。
* 当 $s_{i} = w_{i}$ 时，可直接加上前一步的方案数。

### 初始状态

$dp_{0, 3} = 1$

### 代码

看了 @Werner_Yin 的题解才懂。所以思路和代码跟他的题解差不多。

```cpp
#include <iostream>
#include <fstream>

using ll = long long;

namespace MOD
{
    const ll mod = 1e9 + 7;
} // namespace MOD

#include <string>

namespace Solution
{

    ll dp[100005][4];
    std::string s, w;

    int main()
    {
        #ifndef ONLINE_JUDGE
            std::ifstream cin("main.in");
            std::ofstream cout("main.out");
        #else
            std::ios::sync_with_stdio(false);
            std::cin.tie(nullptr);
            std::cout.tie(nullptr);
            using std::cin;
            using std::cout;
        #endif

        int n;
        cin >> n >> s >> w;
        dp[0][3] = 1;
        s = ' ' + s;
        w = ' ' + w;
        for (int i = 1; i <= n; ++i)
        {
            if (s[i] != '?' && w[i] != '?')
            {
                if (s[i] > w[i])
                {
                    dp[i][0] = 0;
                    dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
                    dp[i][2] = dp[i - 1][2] + dp[i - 1][3];
                    dp[i][3] = 0;
                }
                else if (s[i] == w[i])
                {
                    dp[i][0] = dp[i - 1][0];
                    dp[i][1] = dp[i - 1][1];
                    dp[i][2] = dp[i - 1][2];
                    dp[i][3] = dp[i - 1][3];
                }
                else  
                {
                    dp[i][0] = dp[i - 1][0] + dp[i - 1][3];
                    dp[i][1] = dp[i - 1][1] + dp[i - 1][2];
                    dp[i][2] = 0;
                    dp[i][3] = 0;
                }
            }
            else if (s[i] == '?' && w[i] != '?')
            {
                for (int j = '0'; j < w[i]; ++j)
                {
                    dp[i][0] += dp[i - 1][0] + dp[i - 1][3];
                    dp[i][1] += dp[i - 1][1] + dp[i - 1][2];
                }
                dp[i][0] += dp[i - 1][0];
                dp[i][1] += dp[i - 1][1];
                dp[i][2] += dp[i - 1][2];
                dp[i][3] += dp[i - 1][3];
                for (int j = w[i] + 1; j <= '9'; ++j)
                {
                    dp[i][1] += dp[i - 1][0] + dp[i - 1][1];
                    dp[i][2] += dp[i - 1][2] + dp[i - 1][3];
                }
            }
            else if (s[i] != '?' && w[i] == '?')
            {
                for (int j = '0'; j < s[i]; ++j)
                {
                    dp[i][1] += dp[i - 1][0] + dp[i - 1][1];
                    dp[i][2] += dp[i - 1][2] + dp[i - 1][3];
                }
                dp[i][0] += dp[i - 1][0];
                dp[i][1] += dp[i - 1][1];
                dp[i][2] += dp[i - 1][2];
                dp[i][3] += dp[i - 1][3];
                for (int j = s[i] + 1; j <= '9'; ++j)
                {
                    dp[i][0] += dp[i - 1][0] + dp[i - 1][3];
                    dp[i][1] += dp[i - 1][1] + dp[i - 1][2];
                }
            }
            else  
            {
                for (int j = '0'; j <= '9'; ++j)
                {
                    for (int k = '0'; k <= '9'; ++k)
                    {
                        if (j < k)
                        {
                            dp[i][0] += dp[i - 1][0] + dp[i - 1][3];
                            dp[i][1] += dp[i - 1][1] + dp[i - 1][2];
                        }
                        else if (j == k)
                        {
                            dp[i][0] += dp[i - 1][0];
                            dp[i][1] += dp[i - 1][1];
                            dp[i][2] += dp[i - 1][2];
                            dp[i][3] += dp[i - 1][3];
                        }
                        else 
                        {
                            dp[i][1] += dp[i - 1][0] + dp[i - 1][1];
                            dp[i][2] += dp[i - 1][2] + dp[i - 1][3];
                        }
                    }
                }
            }
            dp[i][0] %= MOD::mod;
            dp[i][1] %= MOD::mod;
            dp[i][2] %= MOD::mod;
            dp[i][3] %= MOD::mod;
        }
        cout << dp[n][1] % MOD::mod;

        #ifndef ONLINE_JUDGE
            cin.close();
            cout.close();
        #endif
        return 0;
    }
} // namespace Solution


int main(int argc, const char* argv[])
{
    Solution::main();
    return 0;
}
```

---

## 作者：Resurgammm (赞：2)

> 给定两个包含数字和问号且长度为 $n$ 字符串 $s,w$，求有多少种方案使得将所有问号替换成 $0$ 到 $9$ 的数字后两个字符串是 `不可比` 的。

> `不可比` 定义为：存在 $i,j\in[1,n]$，使 $s_i<w_i$ 且 $s_j>w_j$。

状态转移有点麻烦，需要分类讨论 $+$ 容斥。

设 $f_{i,k}$ 为前 $i$ 个字符，情况为 $k$ 的方案数（以下 $j<i$）。

* $f_{i,0}$ 为前 $i$ 个字符不可比的字符串的方案数。

* $f_{i,1}$ 为前 $i$ 个字符可比的字符串且所有 $s_j\leq w_j$ 的方案数。

* $f_{i,2}$ 为前 $i$ 个字符可比的字符串且所有 $s_j\geq w_j$ 的方案数。
 
* $f_{i,3}$ 为前 $i$ 个字符可比的字符串且所有 $s_j=w_j$ 的方案数。

起始有 $f_{1,0}=0,f_{0,1\sim 3}=1$。

然后进行分类讨论：

1. $s_i\not=\ ?,w_i\not=\ ?$

$f_{i,0}=f_{i-1,0}+f_{i-1,1}[s_i>w_i]+f_{i-1,2}[s_i<w_i]-f_{i-1,3}[s_i\not= w_i]$

$f_{i,1}=f_{i-1,1}[s_i\leq w_i]$

$f_{i,2}=f_{i-1,2}[s_i\geq w_i]$

$f_{i,3}=f_{i-1,3}[s_i=w_i]$

就是之前的方案加上和现在相反的方案，还要减去相等的方案。

2. $s_i=\ ?,w_i\not=\ ?$ （两种一样，这里只说一种）

$f_{i,0}=10\times f_{i-1,0}+(9-(w_i-'0'))\times f_{i-1,1}+(w_i-'0')\times f_{i-1,2}-9\times f_{i-1,3}$

$f_{i,1}=((w_i-'0')+1)\times f_{i-1,1}$

$f_{i,2}=(10-(w_i-'0'))\times f_{i-1,2}$

$f_{i,3}=f_{i-1,3}$

就是将问号所有的情况都乘起来。

3. $s_i=\ ?,w_i=\ ?$

$f_{i,0}=100\times f_{i-1,0}+45\times f_{i-1,1}+45\times f_{i-1,2}-90\times f_{i-1,3}$

$f_{i,1}=55\times f_{i-1,1}$

$f_{i,2}=55\times f_{i-1,2}$

$f_{i,3}=10\times f_{i-1,3}$

也是和上面一样，将问号所有情况乘起来。

最后答案为 $f_{n,0}$。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
#define int long long
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=1e5+5,mod=1e9+7;
	
	int n;
	int f[maxn][4];// <&&> <= >= =
	char s[maxn],w[maxn];
	
	inline int main(){
		n=read(); scanf("%s%s",s+1,w+1);
		f[0][1]=f[0][2]=f[0][3]=1;
		for(int i=1;i<=n;i++){
			if(s[i]!='?' && w[i]!='?'){
				f[i][0]=(f[i-1][0]+f[i-1][1]*(s[i]>w[i])%mod+f[i-1][2]*(s[i]<w[i])%mod-f[i-1][3]*(s[i]!=w[i])%mod+mod)%mod;
				f[i][1]=f[i-1][1]*(s[i]<=w[i])%mod;
				f[i][2]=f[i-1][2]*(s[i]>=w[i])%mod;
				f[i][3]=f[i-1][3]*(s[i]==w[i])%mod;
			}
			if(s[i]=='?' && w[i]!='?'){
				f[i][0]=(10*f[i-1][0]%mod+(9-(w[i]-'0'))*f[i-1][1]%mod+(w[i]-'0')*f[i-1][2]%mod-9*f[i-1][3]%mod+mod)%mod;
				f[i][1]=((w[i]-'0')+1)*f[i-1][1]%mod;
				f[i][2]=(10-(w[i]-'0'))*f[i-1][2]%mod;
				f[i][3]=f[i-1][3]%mod;
			}
			if(s[i]!='?' && w[i]=='?'){
				f[i][0]=(10*f[i-1][0]%mod+(s[i]-'0')*f[i-1][1]%mod+(9-(s[i]-'0'))*f[i-1][2]%mod-9*f[i-1][3]%mod+mod)%mod;
				f[i][1]=(10-(s[i]-'0'))*f[i-1][1]%mod;
				f[i][2]=((s[i]-'0')+1)*f[i-1][2]%mod;
				f[i][3]=f[i-1][3]%mod;
			}
			if(s[i]=='?' && w[i]=='?'){
				f[i][0]=(100*f[i-1][0]%mod+45*f[i-1][1]%mod+45*f[i-1][2]%mod-90*f[i-1][3]%mod+mod)%mod;
				f[i][1]=55*f[i-1][1]%mod;
				f[i][2]=55*f[i-1][2]%mod;
				f[i][3]=10*f[i-1][3]%mod;
			}
			f[1][0]=0;
		}
		printf("%lld\n",f[n][0]%mod);
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：Cesare (赞：2)

## $Solution$

勾巴题，复杂度 $O(n)$

设 $f_{i, 0/1, 0/1}$ 表示做到 $i$ ，$s_i > w_i$ 是否满足， $w_i > s_i$ 是否满足时的方案数。

转移讨论这一位有几个问号

如果两个都不是直接根据两者的偏序关系继承或者转移

如果有一个是就乘上合法的方案数

如果两个都是就暴算

具体实现看代码，注意细节。

```cpp
if (a[i] == -1 || b[i] == -1) {
	if (a[i] == -1 && b[i] != -1) {
		Add(f[i][0][0], f[i - 1][0][0]);
		Add(f[i][0][1], (f[i - 1][0][0] * b[i] % P + f[i - 1][0][1] * (b[i] + 1) % P) % P);
		Add(f[i][1][0], (f[i - 1][0][0] * (9 - b[i]) % P + f[i - 1][1][0] * (10 - b[i]) % P) % P);
		Add(f[i][1][1], ((f[i - 1][0][1] * (9 - b[i]) % P + f[i - 1][1][0] * b[i] % P) % P + f[i - 1][1][1] * 10 % P) % P);
	}
	if (a[i] != -1 && b[i] == -1) {
		Add(f[i][0][0], f[i - 1][0][0]);
		Add(f[i][0][1], (f[i - 1][0][0] * (9 - a[i]) % P + f[i - 1][0][1] * (10 - a[i]) % P) % P);
		Add(f[i][1][0], (f[i - 1][0][0] * a[i] % P + f[i - 1][1][0] * (a[i] + 1) % P) % P);
		Add(f[i][1][1], ((f[i - 1][0][1] * a[i] % P + f[i - 1][1][0] * (9 - a[i]) % P) % P + f[i - 1][1][1] * 10 % P) % P);
	}
	if (a[i] == -1 && b[i] == -1) {
		Add(f[i][0][0], f[i - 1][0][0] * 10 % P);
		Add(f[i][0][1], (f[i - 1][0][0] * 45 % P + f[i - 1][0][1] * 55 % P) % P);
		Add(f[i][1][0], (f[i - 1][0][0] * 45 % P + f[i - 1][1][0] * 55 % P) % P);
		Add(f[i][1][1], ((f[i - 1][0][1] * 45 % P + f[i - 1][1][0] * 45 % P) % P + f[i - 1][1][1] * 100 % P) % P);
	}
} else {
	if (a[i] > b[i]) {
		Add(f[i][1][0], (f[i - 1][0][0] + f[i - 1][1][0]) % P);
		Add(f[i][1][1], (f[i - 1][0][1] + f[i - 1][1][1]) % P);
	}
	if (a[i] < b[i]) {
		Add(f[i][0][1], (f[i - 1][0][0] + f[i - 1][0][1]) % P);
		Add(f[i][1][1], (f[i - 1][1][0] + f[i - 1][1][1]) % P);
	}
	if (a[i] == b[i]) {
		f[i][0][0] = f[i - 1][0][0], f[i][1][0] = f[i - 1][1][0];
		f[i][0][1] = f[i - 1][0][1], f[i][1][1] = f[i - 1][1][1];
	}
}
```
$ps:$ $Add$ 是两数相加函数。

---

## 作者：鹤箩芠 (赞：2)

水一个题解 （ 

这题一开始怎么看怎么像DP , 后来感觉状态转移很麻烦 ， 便想到了容斥。

设$ans$ 所有情况 （包括不合法的情况 + 合法情况） ， 不难想到 ，不合法的情况就只有全部等于 ， 全部大于 ， 和 全部小于这三种

便设

$res1$ = 全部大约的情况

$res2$ = 全部小于的情况

$res3$ = 全部等于的情况

那答案是不是就是 $ans$ $ - $ $res1$ $-$ $res2$ - $res3$ 呢 ? 

稍后在代码中给出答案$qwq$

求$res1$的代码
```cpp
void EI1 () { // A[i] > B[i]
    for (int i = 0 ; i < n ; i ++) {
    	if (A[i] == '?' && B[i] == '?') res1 = (res1 * 55) % mod ;
    	else if (A[i] == '?' && B[i] != '?') res1 = (res1 * (10 - (B[i] - '0'))) % mod ;
    	else if (A[i] != '?' && B[i] == '?') res1 = (res1 * ((A[i] - '0') + 1)) % mod ;
    	else if ((A[i] - '0') < (B[i] - '0')) { // 注意这里 ， 我写的不是小于等于 ， （留下伏笔
    		res1 = 0 ;
    		break ;
		}
	}	
}
```
$res2$ 以此类推 

$res3$ 代码 
```cpp
void EI3 () {
	for (int i = 0 ; i < n ; i ++) {
		if (A[i] == '?' && B[i] == '?') res3 = (res3 * 10) % mod ;
		else if((A[i]=='?' && B[i]!='?') || (A[i]!='?' && B[i]=='?')) continue ; // 为了保证一样 ，啥都不需要干 
		else if (A[i] != B[i]) {
			res3 = 0 ;
			break ;
		}  
	}
}
```
ans 显而易见就是 遇到问号就 * 10 就可以了 

最后答案
```cpp
cout << (ans + (mod * 2) - res1 - res2 + res3) % mod ;
// 为什么这里我们把res3 加上了 呢 ， 因为我们减去了两个相等的情况 ， res1 上 包括一个 ， res2 上 包括一个 ， 为了保证答案的正确性 ， 我们便要加上一个 
```



---

## 作者：Minuit (赞：1)

update4:加上了中文标点。

update3:去掉了头图。

update2:在所有英文字符前后加了空格。

update1:把公式里的中文换成了 & 和 | , latex 前后加了空格。


目前是最优解rk1。

**阴间题**,大力转移要转一页纸.写码时最好标注好 dp 数组意义(~~不然就忘了~~)。

## **题意**
给定两个由数字和问号组成的等长字符串 $A , B$ ,定义性质 P : 存在 $ 1 \le i,j \le len$ ,满足 $A_i < B_i \&\& A_j > B_j$ ,求将问号替换成数字使 $A,B$ 满足性质 $P$ 的方案数。


## **题解**

**状态设计**:考虑序列 `dp` ,观察到性质是**两方面的**,一方面是令 `A`  中有数大于 `B` ,另一方面则是小于,这两方面显然**不能在一次转移**中完成,故在状态设计中加入两维,分别记录是否已满足这两方面性质,再加一维表示序列的前 $i$ 个,即用 $dp_{0/1,0/1,i}$ 存储方案数.初始化较为显然: $dp_{0,0,0}=1$ , $dp_{1,1,n}$ 即为答案。

**考虑转移**:由于不可能一次满足两方面性质,显然满足一个性质的要从不满足任何性质和满足**同一性质**转移过来,而满足两个性质的要从**两种**满足一个性质和已经满足两个性质的转移过来,不满足任何性质的只能从之前不满足任何性质的转移过来,同时注意根据问号数量讨论:若都不是问号,根据**数字大小关系**直接转移;若有一个及以上问号,考虑在满足给定性质时问号的方案数,显然种类并不多,可以提前算出,即:**两个问号没有任何限制为100种,要求严格大于有45种,非严格大于有55种**.另外,有一个为括号时要根据给定的数字判断方案,也要注意严格大于小于和非严格大于小于的区别.至此,易得转移方程:( $D(x)$ 为 `is_digit(x)` )。

$$dp_{i,0,0}=\left\{
\begin{array}{rcl}
dp_{i-1,0,0},D(A_i)\| D(B_i) \\
10dp_{i-1,0,0},!D(A_i)\&\& !D(B_i)
\end{array}
\right.
$$
$$
dp_{i,0,1}=\left\{
\begin{array}{rcl}
dp_{i-1,0,1},A_i=B_i\\
dp_{i-1,0,0}+dp_{i-1,0,1},A_i<B_i\\
(10-A_i)dp_{i-1,0,1}+(9-A_i)dp_{i-1,0,0},D(A_i)\&\& !D(B_i)\\
(B_i+1)dp_{i-1,0,1}+B_idp_{i-1,0,0},!D(A_i)\&\& D(B_i)\\
45dp_{i-1,0,0}+55dp_{i-1,0,1},!D(A_i)\&\& !D(B_i)
\end{array}
\right.
$$
$$
dp_{i,1,0}=\left\{
\begin{array}{rcl}
dp_{i-1,1,0},A_i=B_i\\
dp_{i-1,0,0}+dp_{i-1,1,0},A_i>B_i\\
(10-B_i)dp_{i-1,1,0}+(9-B_i)dp_{i-1,0,0},!D(A_i)\&\& D(B_i)\\
(A_i+1)dp_{i-1,1,0}+A_idp_{i-1,0,0},D(A_i)\&\& !D(B_i)\\
45dp_{i-1,0,0}+55dp_{i-1,1,0},!D(A_i)\&\& !D(B_i)
\end{array}
\right.
$$
$$
dp_{i,1,1}=\left\{
\begin{array}{rcl}
dp_{i-1,1,1},A_i=B_i\\
dp_{i-1,1,0}+dp_{i-1,0,1},A_i\not =B_i\\
B_idp_{i-1,1,0}+(9-B_i)dp_{i-1,0,1}+10dp_{i-1,1,1},!D(A_i)\&\& D(B_i)\\
(9-A_i)dp_{i-1,1,0}+A_idp_{i-1,0,1}+10dp_{i-1,1,1},D(A_i)\&\& !D(B_i)\\
45dp_{i-1,0,1}+45dp_{i-1,1,0}+100dp_{i-1,1,1},!D(A_i)\&\& !D(B_i)
\end{array}
\right.
$$
## 代码

```cpp
//写转移时始终想着一次最多只能满足一方面性质就会好写很多
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100005,Mod=1000000007;
int n,a[N],b[N];
long long dp[2][2][N];
string s1,s2;
int main() {
	ios::sync_with_stdio(false);
	cin>>n>>s1>>s2;
	s1=' '+s1,s2=' '+s2;//让下标从1开始
	for (int i=1; i<=n; i++) {
		if (s1[i]=='?')a[i]=-1;//问号标为-1
		else a[i]=s1[i]-'0';
		if (s2[i]=='?')b[i]=-1;
		else b[i]=s2[i]-'0';
	}
	dp[0][0][0]=1;
	for (int i=1; i<=n; i++) {
		if (a[i]!=-1&&b[i]!=-1) {
			if (a[i]==b[i]) {//直接转移
				dp[0][0][i]=dp[0][0][i-1]%Mod;
				dp[0][1][i]=dp[0][1][i-1]%Mod;
				dp[1][0][i]=dp[1][0][i-1]%Mod;
				dp[1][1][i]=dp[1][1][i-1]%Mod;
			}
			if (a[i]>b[i]) {//只能满足一方面性质
				dp[1][0][i]=dp[0][0][i-1]%Mod+dp[1][0][i-1]%Mod;
				dp[1][1][i]=dp[0][1][i-1]%Mod+dp[1][1][i-1]%Mod;
			}
			if (a[i]<b[i]) {//另一方面
				dp[0][1][i]=dp[0][0][i-1]%Mod+dp[0][1][i-1]%Mod;
				dp[1][1][i]=dp[1][0][i-1]%Mod+dp[1][1][i-1]%Mod;
			}
			continue;
		}
		if (a[i]!=-1&&b[i]==-1) {//单问号
			dp[0][0][i]=dp[0][0][i-1]%Mod;
			dp[0][1][i]=dp[0][1][i-1]*(10-a[i])%Mod+dp[0][0][i-1]*(9-a[i])%Mod;
			dp[1][0][i]=dp[1][0][i-1]*(a[i]+1)%Mod+dp[0][0][i-1]*a[i]%Mod;
			dp[1][1][i]=dp[1][0][i-1]*(9-a[i])%Mod+dp[0][1][i-1]*a[i]%Mod+dp[1][1][i-1]*10%Mod;
			continue;
		}
		if (a[i]==-1&&b[i]!=-1) {//单问号
			dp[0][0][i]=dp[0][0][i-1]%Mod;
			dp[0][1][i]=dp[0][1][i-1]*(b[i]+1)%Mod+dp[0][0][i-1]*b[i]%Mod;
			dp[1][0][i]=dp[1][0][i-1]*(10-b[i])%Mod+dp[0][0][i-1]*(9-b[i])%Mod;
			dp[1][1][i]=dp[1][0][i-1]*b[i]%Mod+dp[0][1][i-1]*(9-b[i])%Mod+dp[1][1][i-1]*10%Mod;
			continue;
		}
		if (a[i]==-1&&b[i]==-1) {//双问号
			dp[0][0][i]=dp[0][0][i-1]*10%Mod;
			dp[0][1][i]=dp[0][0][i-1]*45%Mod+dp[0][1][i-1]*55%Mod;
			dp[1][0][i]=dp[0][0][i-1]*45%Mod+dp[1][0][i-1]*55%Mod;
			dp[1][1][i]=dp[0][1][i-1]*45%Mod+dp[1][0][i-1]*45%Mod+dp[1][1][i-1]*100%Mod;
			continue;
		}
		cout<<"Fail"<<endl;
	}
	cout<<dp[1][1][n]%Mod<<endl;
}

---

## 作者：eee_hoho (赞：1)

考虑直接对不可比的串进行dp，设$f_i$表示前$i$个字符不可比的串的个数，$g1_i$表示前$i$个字符可比的字符串且所有$s\leq t$的个数，$g2_i$表示前$i$个字符可比的字符串且所有$s\geq t$的个数，$g3_i$表示前$i$个字符可比的字符串且$s=t$的个数。

于是考虑转移方程：

1. $s_i\neq ?,w_i\neq?$

$$\begin{cases}f_i=f_{i-1}+g1_{i-1}[s_i>w_i]+g2_{i-1}[s_i<w_i]-g3_{i-1}[s_i\ne w_i]\\g1_i=g1_{i-1}[s_i\le w_i]\\g2_i=g2_{i-1}[s_i\ge w_i]\\g3_i=g3_{i-1}[s_i=w_i]\end{cases}$$

就是之前的方案乘和这一位相反的方案，但还要减去之前都相等的方案。

2. $s_i=?,w_i\neq?$

有一个是问号的做法是类似的，所以我只拿一个来说。

$$\begin{cases}f_i=10f_{i-1}+(9-(w_i-'0'))g1_{i-1}+(w_i-'0')g2_{i-1}-9g3_{i-1}\\g1_i=(w_i-'0'+1)g1_{i-1}\\g2_i=(9-(w_i-'0')+1)g2_{i-1}\\g3_i=g3_{i-1}\end{cases}$$

直接考虑问号会取到哪些值，然后用和上面一样的容斥处理方案。

3. $s_i=?,w_i=?$

$$\begin{cases}f_i=100f_{i-1}+45g1_{i-1}+45g2_{i-1}-90g3_{i-1}\\g1_i=55g1_{i-1}\\g2_i=55g2_{i-1}\\g3_i=10g3_{i-1}\end{cases}$$

多考虑一个问号，就是多用一个求和公式算算就可以了。

最后注意下$i=1$的时候不会构成不可比的串，所以$f_1=0$

**Code**
``` cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
const int N = 1e5;
const int p = 1e9 + 7;
using namespace std;
int n,g1[N + 5],g2[N + 5],f[N + 5],g3[N + 5];
char s[N + 5],w[N + 5];
int main()
{
    scanf("%d",&n);
    scanf("%s",s + 1);
    scanf("%s",w + 1);
    g1[0] = g2[0] = g3[0] = 1;
    for (int i = 1;i <= n;i++)
    {
        if (s[i] != '?' && w[i] != '?')
        {
            if (s[i] <= w[i])
                g1[i] = g1[i - 1];
            if (s[i] >= w[i])
                g2[i] = g2[i - 1];
            if (s[i] == w[i])
                g3[i] = g3[i - 1];
            f[i] = f[i - 1];
            if (s[i] < w[i])
                f[i] += g2[i - 1],f[i] %= p;
            if (s[i] > w[i])
                f[i] += g1[i - 1],f[i] %= p;
            if (s[i] != w[i])
                f[i] -= g3[i - 1],f[i] %= p;
        }
        if (s[i] == '?' && w[i] != '?')
        {
            f[i] = 10ll * f[i - 1] % p;
            g1[i] = 1ll * g1[i - 1] * (w[i] - '0' + 1) % p;
            g2[i] = 1ll * g2[i - 1] * (9 - (w[i] - '0') + 1) % p;
            g3[i] = g3[i - 1];
            f[i] += 1ll * g1[i - 1] * (9 - (w[i] - '0')) % p;
            f[i] %= p;
            f[i] += 1ll * g2[i - 1] * (w[i] - '0') % p;
            f[i] %= p;
            f[i] -= 9ll * g3[i - 1] % p;
            f[i] %= p;
        }
        if (s[i] != '?' && w[i] == '?')
        {
            f[i] = 10ll * f[i - 1] % p;
            g1[i] = 1ll * g1[i - 1] * (9 - (s[i] - '0') + 1) % p;
            g2[i] = 1ll * g2[i - 1] * (s[i] - '0' + 1) % p;
            g3[i] = g3[i - 1];
            f[i] += 1ll * g1[i - 1] * (s[i] - '0') % p;
            f[i] %= p;
            f[i] += 1ll * g2[i - 1] * (9 - (s[i] - '0')) % p;
            f[i] %= p;
            f[i] -= 9ll * g3[i - 1] % p;
            f[i] %= p;
        }
        if (s[i] == '?' && w[i] == '?')
        {
            f[i] = 100ll * f[i - 1] % p;
            g1[i] = 55ll * g1[i - 1] % p;
            g2[i] = 55ll * g2[i - 1] % p;
            g3[i] = 10ll * g3[i - 1] % p;
            f[i] += (45ll * g1[i - 1] % p + 45ll * g2[i - 1] % p) % p;
            f[i] %= p;
            f[i] -= 90ll * g3[i - 1] % p;
            f[i] %= p;
        }
        f[1] = 0;
    }
    cout<<(f[n] + p) % p<<endl;
    return 0;
}
```

---

## 作者：SoyTony (赞：0)

这种计数类 dp 需要交叉转移的时候，比较暴躁的做法，就是把所有情况都加进状态中，于是定义 $dp(i,[0,3])$ 分别表示在前 $i$ 位中不可比较、只含有大于等于、只含有小于等于以及只含有等于的情况。

之后讨论是否有通配符然后转移即可。

可以发现一件事情：在每种通配符讨论的情况内，$dp(i-1)$ 的各情况对 $dp(i)$ 产生贡献的次数都是相等的，可以用来 debug。

转移见代码

```cpp
int n;
char s[maxn],w[maxn];
ll dp[maxn][4];//合法、不存在小于，不存在大于，全部相等
inline void output(int l,int r){
	for(int i=l;i<=r;++i) printf("%d %lld %lld %lld %lld\n",i,dp[i][0],dp[i][1],dp[i][2],dp[i][3]);
}
int main(){
	n=read();
	scanf("%s",s+1);
	scanf("%s",w+1);
	if(s[1]=='?'&&w[1]=='?') dp[1][0]=0,dp[1][1]=45,dp[1][2]=45,dp[1][3]=10;
	else if(s[1]=='?'&&w[1]!='?') dp[1][0]=0,dp[1][1]='9'-w[1],dp[1][2]=w[1]-'0',dp[1][3]=1;
	else if(s[1]!='?'&&w[1]=='?') dp[1][0]=0,dp[1][1]=s[1]-'0',dp[1][2]='9'-s[1],dp[1][3]=1;
	else{
		dp[1][0]=0,dp[1][1]=0,dp[1][2]=0,dp[1][3]=0;
		if(s[1]>w[1]) dp[1][1]=1;
		else if(s[1]<w[1]) dp[1][2]=1;
		else dp[1][3]=1;
	}
	for(int i=2;i<=n;++i){
		if(s[i]=='?'&&w[i]=='?'){
			dp[i][0]=(dp[i-1][0]*100%mod+dp[i-1][1]*45%mod+dp[i-1][2]*45%mod)%mod;
			dp[i][1]=(dp[i-1][1]*55%mod+dp[i-1][3]*45%mod)%mod;
			dp[i][2]=(dp[i-1][2]*55%mod+dp[i-1][3]*45%mod)%mod;
			dp[i][3]=dp[i-1][3]*10%mod;
		}
		else if(s[i]=='?'&&w[i]!='?'){
			dp[i][0]=(dp[i-1][0]*10%mod+dp[i-1][1]*(w[i]-'0')%mod+dp[i-1][2]*('9'-w[i])%mod)%mod;
			dp[i][1]=(dp[i-1][1]*('9'-w[i]+1)%mod+dp[i-1][3]*('9'-w[i])%mod)%mod;
			dp[i][2]=(dp[i-1][2]*(w[i]-'0'+1)%mod+dp[i-1][3]*(w[i]-'0')%mod)%mod;
			dp[i][3]=dp[i-1][3];
		}
		else if(s[i]!='?'&&w[i]=='?'){
			dp[i][0]=(dp[i-1][0]*10%mod+dp[i-1][1]*('9'-s[i])%mod+dp[i-1][2]*(s[i]-'0')%mod)%mod;
			dp[i][1]=(dp[i-1][1]*(s[i]-'0'+1)%mod+dp[i-1][3]*(s[i]-'0')%mod)%mod;
			dp[i][2]=(dp[i-1][2]*('9'-s[i]+1)%mod+dp[i-1][3]*('9'-s[i])%mod)%mod;
			dp[i][3]=dp[i-1][3];
		}
		else{
			if(s[i]>w[i]){
				dp[i][0]=(dp[i-1][0]+dp[i-1][2])%mod;
				dp[i][1]=(dp[i-1][1]+dp[i-1][3])%mod,dp[i][2]=0,dp[i][3]=0;
			}
			else if(s[i]<w[i]){
				dp[i][0]=(dp[i-1][0]+dp[i-1][1])%mod;
				dp[i][1]=0,dp[i][2]=(dp[i-1][2]+dp[i-1][3])%mod,dp[i][3]=0;
			}
			else{
				dp[i][0]=dp[i-1][0],dp[i][1]=dp[i-1][1],dp[i][2]=dp[i-1][2],dp[i][3]=dp[i-1][3];
			}
		}
	}
	printf("%lld\n",dp[n][0]);
	return 0;
}

```

---

