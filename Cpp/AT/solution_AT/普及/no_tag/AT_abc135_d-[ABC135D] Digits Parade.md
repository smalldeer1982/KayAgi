# [ABC135D] Digits Parade

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc135/tasks/abc135_d

文字列 $ S $ が与えられます。$ S $ の各文字は、数字 (`0` ～ `9`) か `?` です。

`?` を数字に置き換えてできる整数のうち、$ 13 $ で割って $ 5 $ あまる数は何通りあるでしょうか？ただし、頭文字が $ 0 $ である場合も整数とみなすものとします。

答えは非常に大きくなる可能性があるため、$ 10^9+7 $ で割ったあまりを答えてください。

## 说明/提示

### 制約

- $ S $ は数字 (`0` ～ `9`) と `?` からなる文字列。
- $ 1\ \leq\ |S|\ \leq\ 10^5 $

### Sample Explanation 1

たとえば $ 482305,\ 002865,\ 972665 $ などが条件を満たします。

### Sample Explanation 2

$ 044 $ のみが条件を満たします。

### Sample Explanation 3

条件を満たす整数を作ることが不可能な場合もあります。

## 样例 #1

### 输入

```
??2??5```

### 输出

```
768```

## 样例 #2

### 输入

```
?44```

### 输出

```
1```

## 样例 #3

### 输入

```
7?4```

### 输出

```
0```

## 样例 #4

### 输入

```
?6?42???8??2??06243????9??3???7258??5??7???????774????4?1??17???9?5?70???76???```

### 输出

```
153716888```

# 题解

## 作者：μηδσ (赞：8)

## Solution

这道题可以用DP来做

$dp[i][j]$表示到第$i$个字符为止，初一13余$j$($j$表示的是到$i-1$为止模13余$j$)有多少种情况

若当前的字符是数字,则递推公式为:
~~~cpp
dp[i][(j*10+s[i])%13] = (dp[i][(j*10+s[i])%13] + dp[i-1][j])%mod;
~~~
若当前的字符是$?$，则递推公式为：
~~~cpp
dp[i][(j*10+k)%13] = (dp[i][(j*10+k)%13] + dp[i-1][j])%mod;（k为1~9）
~~~
有了递推式那么直接看代码吧

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;

char s[100005];									//定义字符数组表示原数
ll dp[100005][13];								//动态规划数组

int main(){					
	cin >> s + 1;								//输入字符串，记得要+1，从s[1]开始输入
	int n = strlen(s + 1);						//判断字符串的长度
	dp[0][0] = 1;								//将dp[0][0]初始化
	for(int i = 1;i <= n;i++){		
		if(s[i] != '?'){						//判断输入是不是？
			s[i] -= '0';						//如果不是？将字符减'0'
			for(int j = 0;j < 13;j++)			//循环递推dp
				dp[i][(j * 10 + s[i]) % 13] = (dp[i][(j * 10 + s[i]) % 13] + dp[i - 1][j]) % MOD;
		}
		else{									//如果输？
			for(int k = 0;k < 10;k++)			//循环看新的数是什么
				for(int j = 0;j < 13;j++)		//循环递推dp
					dp[i][(j * 10 + k) % 13] = (dp[i][(j * 10 + k) % 13] + dp[i - 1][j]) % MOD;
		} 
	}
    cout << dp[n][5];							//输出dp[n][5]
}
~~~

---

## 作者：Gokix (赞：4)

[AT4802](https://www.luogu.com.cn/problem/AT4802)

允许前导 0 何必数位 DP。

顺便滚掉一维。

------------

从这个 $n$ 位数的低位向高位递推。假设现在递推到倒数第 $i$ 位，记 $f_{k:0\to 12}$ 表示从倒数第 $i+1$ 位向后的数字组成的数模 $13$ 余 $k$ 的数有 $f_k$ 个。记 $g_{k:0\to 12}$ 表示从第 $i$ 位向后的数字组成的数模 $13$ 余 $k$ 的数有 $f_k$ 个。

接下来考虑由 $f$ 转移到 $g$：

1. 假如倒数第 $i$ 位不是 `?`，是 $x$

	记 $S=10^{i}$，则 $f_k$ 会转移到 $g_{(k+S) \bmod 13}$ 上。循环一遍即可 。
    
2. 假如倒数第 $i$ 位是 `?`

	从 $0$ 到 $9$ 枚举该位，然后每次按照上面的方法做一遍。最后加起来就行。
    
转移后将 $g$ 赋值给 $f$，重复递推即可。
    
最终递推完后，答案即 $f_5$

时间复杂度 $O(130n)$。

------------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long rd(){char ch=getchar();long long x=0,f=1;while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
                        while('0'<=ch && ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void wr(long long x){if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');}

const long long p=1e9+7;
long long n,f[20],g[20],yu,ans;
char s[100010];

int main(){
	long long i,j,u,v,k;
	scanf("%s",s+1);
	n=strlen(s+1);
	f[0]=1;yu=1;
	for(i=n;i>=1;i--){
		if(s[i]=='?'){
			memset(g,0,sizeof(g));
			for(k=0;k<10;k++){
				v=yu*k;v%=13;
				for(j=0;j<13;j++) g[(j+v)%13]+=f[j],g[(j+v)%13]%=p;
			}
			yu=yu*10;yu%=13;
			for(j=0;j<13;j++) f[j]=g[j],f[j]%=p;
		}
		else{
			v=yu*(s[i]-'0');v%=13;
			yu=yu*10;yu%=13;
			for(j=0;j<13;j++) g[(j+v)%13]=f[j],g[(j+v)%13]%=p;
			for(j=0;j<13;j++) f[j]=g[j],f[j]%=p;
		}
	}
	wr(f[5]%p),putchar('\n');
	return 0;
}
```


---

## 作者：zhangjiting (赞：3)

## 题意

给你一个数，其中有些位置不知道，用 `?` 代替。

在通过用数字替换每次出现的 `？` 而获得的整数中，当除以 $13$ 时有多少个余数为 $5$？

## 思路

一眼 DP。

$dp_{i,j}$ 表示到第 $i$ 位为止，除以 $13$ 余数为 $j$ 的情况数。

当 $s_i$ 是数字时。递推式为：

```cpp
dp[i][(j*10+s[i])%13]+=dp[i-1][j];
dp[i][(j*10+s[i])%13]%=mod;
```

否则，枚举这个位置上的数。递推式为：

```cpp
dp[i][(j*10+k)%13]+=dp[i-1][j];
dp[i][(j*10+k)%13]%=mod;
```

最后输出 `dp[n][5]`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[100005][15]={1};
const int mod=1e9+7;
int main(){
	string s;
	cin>>s;
	int n=s.size();
	s=' '+s;
	for(int i=1;i<=n;i++){
		if(s[i]!='?'){
			s[i]-='0';
			for(int j=0;j<=12;j++){
				dp[i][(j*10+s[i])%13]+=dp[i-1][j];
				dp[i][(j*10+s[i])%13]%=mod;
			}
		}
		else{
			for(int j=0;j<=12;j++){
				for(int k=0;k<=9;k++){
					dp[i][(j*10+k)%13]+=dp[i-1][j];
					dp[i][(j*10+k)%13]%=mod;
				}
			}
		}
	}
	cout<<dp[n][5]%mod;
	return 0;
}

```


---

## 作者：零殇 (赞：2)

#### 题意

给你一个数，有些位置不知道，求多少种可能能够让这个数 $\mod 13$ 结果为 $5$。

#### 思路

我们可以想象一下我们小学时是怎么求余数的。

在我们求除法时，我们会把之前的余数保留，乘 $10$ 后再加上现在位置的数，再除一次。

最后我们计算完后就顺便求出了余数。

因此，我们后面的余数是会受前面余数的限制的。

那我们就保留前面的余数。

考虑 $DP$。

假设 $dp[i][j]$ 表示在第 $j$ 位时余数为 $i$ 的可能个数，则有两种状态转移方程。

第一种，现在不是问号。我们把所有 $dp[i][j-1]$ 枚举一遍，设 $x=dp[i][j-1]*10+s[i]$（$s[i]$ 表示现在的数）。那么 $dp[x][j]+=dp[i][j-1]$。

第二种，现在是问号。只要把上面的 $s[i]$ 改成从 $1$ 到 $9$ 的枚举就好了。

注意最开头的预处理。

上代码：

```
#include<bits/stdc++.h>
const int N=1e5+7,mod=1e9+7;
using namespace std;
int dp[13][N];
int main() {
	string s;
	cin>>s;
	if(s[0]!='?')
		dp[s[0]-'0'][0]=1;
	else
		for(int i=0;i<=9;i++)
			dp[i][0]=1;
	for(int i=1;i<s.size();i++) {
		if(s[i]!='?')
			for(int j=0;j<=12;j++) {
				int x=((s[i]-'0')+j*10)%13;
				dp[x][i]+=dp[j][i-1];
				dp[x][i]%=mod;
			}
		else
			for(int k=0;k<=9;k++)
				for(int j=0;j<=12;j++){
					int x=(k+j*10)%13;
					dp[x][i]+=dp[j][i-1];
					dp[x][i]%=mod;
				}
	}
	printf("%d",dp[5][s.size()-1]);
	return 0;
}
```

完结撒花~

---

## 作者：_AyachiNene (赞：2)

# 思路：
记 $dp_{i,j}$ 表示前 $i$ 位数，总和除以 $5$ 的余数为 $j$ 的方案数。那么不难推出转移方程。

当第 $i$ 位为数字时：
```cpp
dp[i][(j*10+x)%13]=(dp[i][(j*10+x)%13]+dp[i-1][j])%mod;（x为当前这一位的数字）
```
当第 $i$ 位为问号时，则需要枚举这一位填的数字：
```cpp
dp[i][(k*10+j)%13]=(dp[i][(k*10+j)%13]+dp[i-1][k])%mod;
```
有了状态转移方程还需要想的就是初值，很好想到在第 $0$ 位时，余数当然是 $0$，而这时只有一种情况。所以 $dp_{0,0}=1$。答案显然就是 $dp_{n,5}$。
# Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int dp[114514][13];//前i位，总和mod 13=j的方案数（1<=i<=n  0<=j<=12) 
string s; 
int n;
signed main()
{
	cin>>s;
	s=' '+s;    //下标从1开始 
	n=s.size()-1;
	dp[0][0]=1; 
	for(int i=1;i<=n;i++)
	{
		if(s[i]!='?')
		{
			int x=s[i]-'0';
			for(int j=0;j<13;j++)
				dp[i][(j*10+x)%13]=(dp[i][(j*10+x)%13]+dp[i-1][j])%mod;
		}
		else
		{
			for(int j=0;j<10;j++)
				for(int k=0;k<13;k++)
					dp[i][(k*10+j)%13]=(dp[i][(k*10+j)%13]+dp[i-1][k])%mod;
		}
	}			
	cout<<dp[n][5];
}       
```


---

## 作者：Silence_World (赞：1)

# 思路

比较好想的一道数位 dp，首先我们考虑一个数的余数能和什么凑成关系，很明显和被除数和除数有关，那么我们在不知道被除数只知道除数的情况下怎么办呢，我们思考我们在列竖式时怎么算的，是把上一个留下来的余数乘了十又加上了这一位上的数，也就是说余数其实和上一位的余数是有关的！那么 dp 式就很好想了，我们考虑上一位的余数与这一位余数的关系，然后枚举这一位余数，加上所有可能就可以了，具体见代码，注意一些小细节统计之类的就可以了。

# AC 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 1000000007
int dp[100005][15];
signed main(){
	string s;
	cin>>s;
	if(s[0]=='?'){
		for(int i=0;i<10;i++){//注意此处到九 
			dp[0][i]=1;
		}
	}
	else{
		dp[0][s[0]-'0']=1;
	}//初始化 
	for(int i=1;i<s.length();i++){
		if(s[i]=='?'){
			for(int j=0;j<13;j++){ 
				for(int k=0;k<=9;k++){ 
					if(dp[i-1][j]){
						dp[i][(j*10+k)%13]+=dp[i-1][j]%mod;//DP START!注意取模 
					}
				}
			}
		}
		else{
			for(int j=0;j<13;j++){
				int t=s[i]-'0';
				if(dp[i-1][j]){
					dp[i][(j*10+t)%13]+=dp[i-1][j]%mod;//DP START!注意取模 
				} 
			}
		}
	}
	cout<<dp[s.length()-1][5]%mod;//注意取模 
}
```


---

## 作者：SilverLi (赞：1)

> [Digits Parade の 传送门](https://www.luogu.com.cn/problem/AT_abc135_d)

> [更杂乱的阅读体验](https://www.cnblogs.com/Silver-Wolf/p/ABC135D.html)

## Solution

首先看到

> $1\le |S|\le 10^5$

考虑 DP。

定义 $f_{i,j}$ 表示前 $i$ 个位置的数除以 $13$ 的余数为 $j$。

则有

- 当 $s_i = ?$ 时，枚举余数 $j$($0\le j\le 12$) 和当前选的数 $k$($0\le k\le 9$)，则有 $f_{i+1,j*10+k}=f_{i+1,j*10+k}+f_{i,j}$。

- 当 $s_i \neq ?$ 时，同样枚举余数 $j$($0\le j\le 12$)，则有 $f_{i+1,j*10+t}=f_{i+1,j*10+t}+f_{i,j}$(其中 $t$ 表示 $s_i$ 转换成数字的数)。

## Code

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 5;
const int M = 1e1 + 5;
const int mod = 1e9 + 7;
int n, f[N][M];
string s;
#define t (s[i] - '0')
signed main() {
	cin >> s;
	n = s.size();
	f[0][0] = 1;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 13; ++j) {
			if (s[i] == '?') {
				for (int k = 0; k <= 9; ++k) {
					int now = (j * 10 + k) % 13;
					f[i + 1][now] += f[i][j];
					f[i + 1][now] %= mod;
				}
			}
			else {
				int now = (j * 10 + t) % 13;
				f[i + 1][now] += f[i][j];
				f[i + 1][now] %= mod;
			}
		}
	cout << f[n][5];
	return 0;
}
```

---

## 作者：small_john (赞：1)

## 思路

简单的 DP 题。

设 $dp_{i,j}$ 表示前 $i$ 位对 $13$ 取余余数是 $j$ 的情况数。

在 DP 时，设第 $i$ 位的数是 $x$。枚举余数 $j$，又由于余数的可加性和可乘性，有：$dp_{i,(10\times j+x)\bmod13}=dp_{i,(10\times j+x)\bmod13}+dp_{i-1,j}$。然后分类讨论确定 $x$：

1. 当 $s_i=1\sim9$ 时，$x$ 可以被直接确定，即 $x=s_i-48$；
2. 否则，就直接枚举 $x$。

最后输出 $dp_{|s|,5}$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+5,mod = 1e9+7;
string s;
int n,dp[N][15];
signed main()
{
	cin>>s;
	n = s.size(),s = ' '+s;
	dp[0][0] = 1;
	for(int i = 1;i<=n;i++)
		if(s[i]!='?')
			for(int j = 0;j<13;j++)
				(dp[i][(j*10+s[i]-'0')%13]+=dp[i-1][j])%=mod;
		else
			for(int j = 0;j<10;j++)
				for(int k = 0;k<13;k++)
					(dp[i][(k*10+j)%13]+=dp[i-1][k])%=mod;
	cout<<dp[n][5];
	return 0;
}
```

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc135_d)

思路：DP。

很我们可以首先考虑一个数的余数与被除数和除数之间的关系。很明显，余数与被除数和除数有关。但是，如果我们只知道除数而不知道被除数，我们该如何处理呢？我们可以回想一下我们在列竖式时是如何进行计算的。我们将上一个留下来的余数乘以十，然后再加上这一位上的数。这意味着余数实际上与上一位的余数有关。基于这个思路，我们可以得到动态规划的递推式。

相信你一定已经看懂了思路，代码就不上了（逃）。

---

## 作者：watcher_YBH (赞：0)

# 思路：
根据题目意思，我们可以得到状态为：$dp_{i,j}$ 表示前 $i$ 个数的余数为 $j$ 的情况数。再根据与数的可乘性，可以得到方程式为：

1. 当此位置是问号时。
```
dp[k][(i*10+j)%13] = (dp[k][(i*10+j)%13]+dp[k-1][i])%mod
```
2. 当此位置不是问号时。
```
dp[k][(i*10+(s[k]-'0'))%13] = (dp[k][(i*10+(s[k]-'0'))%13]+dp[k-1][i])%mod
```

# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 1e5+5;
const int mod = 1e9+7;
int n;
string s;
int dp[MAX][13];
int main(){
	cin>>s;
	n = s.size(); s = ' '+s;
	dp[0][0] = 1;
	for(int k = 1; k<=n; k++){
		if(s[k] == '?'){
			for(int i = 0; i<=12; i++)
				for(int j = 0; j<=9; j++)
					dp[k][(i*10+j)%13] = (dp[k][(i*10+j)%13]+dp[k-1][i])%mod;
		}
		else{
			for(int i = 0; i<=12; i++)
				dp[k][(i*10+(s[k]-'0'))%13] = (dp[k][(i*10+(s[k]-'0'))%13]+dp[k-1][i])%mod;
		}
	}
	cout<<dp[n][5];
	return 0;
}
```


---

## 作者：Yang818 (赞：0)


## problem:
给你一个数，有些数字用问号替代，你可以将问号替换成任何数字，问把所有问号换成数字后有几种情况可以使得整个数字除以 $13$ 余数为 $5$。
## solution:

首先，第一位参数肯定要有现在是第几位，还要保存这一位之前的数字，但是不用将之前的所有数字保存下来，只用保存之前数字除以 $13$ 的余数。

两个参数有了，看看怎么推吧：

如果这一位是数字，直接保存之前的余数乘10后加上这位数再 $mod$ $13$ ,如果这一位是问号，那么就把 $0\sim9$ 每个数字遍历一遍，将余数乘 $10$ 后加上遍历到的这个数再 $mod$ $13$。代码如下：
```cpp
long long dfs(int i,int mod){
	if(i==len) return mod==5;//如果到最后一位了，直接返回这个数除以5的余数
	long long ans=0;
	if(s[i]=='?')
		for(int j=0;j<10;j++){
			ans=(ans+dfs(i+1,(mod*10+j)%13))%MOD;
		}
	else
		ans=dfs(i+1,(mod*10+s[i]-'0')%13)%MOD;
	return ans;
}
```

但人家毕竟是黄题啊，怎么可能就这样过掉。交了一遍后直接 $TLE$ 。怎么办？ $dfs$ 的优化我能想到的也就只有剪枝和记忆化了，这道题减不了枝，那就加上记忆化呗。

加上之后就能过了，完整代码如下：
## code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
const int MOD=1e9+7;
string s;
int len,f[MAXN][13];

long long dfs(int i,int mod){
	if(i==len) return mod==5;
	if(f[i][mod]!=-1)
		return f[i][mod];//记忆化搜索
	long long ans=0;
	if(s[i]=='?')
		for(int j=0;j<10;j++){
			ans=(ans+dfs(i+1,(mod*10+j)%13))%MOD;
		}
	else
		ans=dfs(i+1,(mod*10+s[i]-'0')%13)%MOD;
	f[i][mod]=ans;//别忘了赋值
	return ans;
}

int main(){
	memset(f,-1,sizeof(f));//这道题中初值定成-1最好，因为会有算出来是0的情况，但也被算过了
	cin>>s;
	len=s.size();
	cout<<dfs(0,0);
	return 0;
} 

```
望通过，谢谢


---

## 作者：VERACITY (赞：0)

## 题意
给一个含 `?` 的数，`?` 可以被 $0$ 到 $9$ 替换。   
求每个可能出现的数中，有多少个数除以 $13$ 余数为 $5$。    
输出答案模 $10^9+7$。

## 思路
由于求模这一特殊性，靠前位置的 `?` 会对靠后位置的 `?` 的答案产生影响，但靠后的并不会影响前面的，因此考虑从前往后 DP。 
$dp_{i,j}$ 表示前 $j$ 位确定时，余数为 $i$ 的方案数。    
如何确定遍历至第 $i$ 位为 `?` 时，前 $i$ 位表示的数模 $13$ 的余数？回忆小学数学得知，可由前 $i-1$ 位产生的余数乘 $10$ 加上第 $i$ 位的数再模 $13$ 得出。

首先确定第一个位置。当 $s_0$ 为`?` 时，以 $i$ 枚举 $0$ 到 $9$ 进行填写，$dp_{i,0} = 1$；当 $s_0$ 为确定的数字时，$dp_{s_0,0} = 1$。   
接下来遍历后续字符串。$s_i$ 为确定的数时，以 $j$ 枚举 $0$ 到 $12$ 的余数，那么当前表示的数模 $13$ 的余数为 $(s_i + j \times 10) \bmod 13$，得出式子 $dp_{(s_i + j \times 10) \bmod 13,i} + dp_{j,i-1} $；当 $s_i$ 为 `?` 时，用 $0$ 到 $9$ 枚举替换 $s_i$ 后，重复上述操作即可。   
最后答案即为 $dp_{5,|s|-1}$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mx=1e5+1,mod=1e9+7;
int dp[13][mx],len;
string s;
int main() 
{
	cin >> s;
	len=s.length();
	if(s[0]=='?')	for(int i=0;i<=9;i++)	dp[i][0]=1;
	else	dp[s[0]-'0'][0]=1;
	for(int i=1;i<len;i++) 
	{
		if(s[i]!='?')
			for(int j=0;j<=12;j++) 
				dp[((s[i]-'0')+j*10)%13][i]=(dp[((s[i]-'0')+j*10)%13][i]+dp[j][i-1])%mod;
		else
			for(int num=0;num<=9;num++)
				for(int j=0;j<=12;j++)
					dp[(num+j*10)%13][i]=(dp[(num+j*10)%13][i]+dp[j][i-1])%mod;
	}
	cout<<dp[5][len-1];
	return 0;
}
```


---

