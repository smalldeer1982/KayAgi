# [EC Final 2020] Namomo Subsequence

## 题目描述

「gshfd1jkhaRaadfglkjerVcvuy0gf」教授 Pang 说道。

为了理解 Pang 教授的话，我们想要计算它的 $\textit{namomo 子序列}$ 的数量。Pang 教授的话是一个长度为 $n$ 的字符串 $s$，其中每个字符要么是英文字母（大小写），要么是数字。字符串 $s$ 的第 $i$ 个字符记为 $s[i]$（$1\le i\le n$）。字符串 $s$ 的子序列 $t$ 由一组下标 $t_1, \ldots, t_6$ 定义，满足 $1\le t_1 < t_2 < \ldots < t_6\le n$。定义一个函数 $compare(c_1, c_2)$，对于两个字符 $c_1$ 和 $c_2$，当 $c_1=c_2$ 时 $compare(c_1, c_2)=1$，否则 $compare(c_1, c_2)=0$。当且仅当对于任意 $1\le i<j\le 6$，$compare(s[t_i], s[t_j]) = compare(namomo[i], namomo[j])$ 时，$t$ 是字符串 $s$ 的一个 namomo 子序列，其中 $namomo[x]$ 表示字符串「namomo」的第 $x$ 个字符（$1\le x\le 6$）。

输出给定字符串 $s$ 的 namomo 子序列的数量，结果对 $998244353$ 取模。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
wohaha```

### 输出

```
1```

## 样例 #2

### 输入

```
momomo```

### 输出

```
0```

## 样例 #3

### 输入

```
gshfd1jkhaRaadfglkjerVcvuy0gf```

### 输出

```
73```

## 样例 #4

### 输入

```
retiredMiFaFa0v0```

### 输出

```
33```

# 题解

## 作者：wujingfey (赞：8)

[传送门](https://www.luogu.com.cn/problem/P10816)

~~所实话这题真的只有绿题难度吗？道心破碎了。~~

挑战本题最详细题解，求通过。

## 题意（人话版）
给你一个字符串 $s$，找其中一个长度为 $6$ 的**序列**满足```ABCDCD```形式的方案数，对 $998244353$ 取模。

$n\leqslant 10^6$

## 题解
观察```ABCDCD```的形式，可以把此题分成两部分考虑：```AB+CDCD```。详细地说，我们枚举每一位 $i$，分别求出 $[1,i-1]$ 中形如```AB```的方案数，然后在 $[i,len]$ 中求出形如```CDCD```的方案数。

### 对于前者

我们可以预处理：先开个桶 $t_{i,j}$ 表示前 $i$ 位，字符 $j$ 出现了多少次。再设 $g_{i}$ 表示前 $i$ 个字母能有多少种 AB 方案。

桶的转移很简单，就不细说了。考虑 $g$：每个 $g_i$ 从定义出发，就可以枚举每种字符出现的次数，然后乘以其他字符出现的次数：
```
for(int j=0;j<=61;j++){
	t[i][j]=t[i-1][j];//继承
	if(a[i]==j) t[i][j]++;//更新桶 
    g[i]+=t[i][j] * (i-t[i][j]);
	//枚举i,有i*(i-t[i][j])种AB方案 
}
g[i]>>=1;//AB、BA都会被计算，去除重复贡献
```

### 对于后者
我们从后往前枚举 $i$，维护```CDCD```方案数，同时记录答案。

记录```CDCD```的方案数，我们采用最朴素的“拼接法”。（设现在枚举到的字符是 $p$）。

- 如果我要知道 CDCD 的方案数，并且把 $p$ 固定成第一个 C，那么我们要在后面拼接 DCD。
- 如果我要知道后面 DCD 有多少种可行方案，我就要同时维护一个 DCD 的方案数。与上面类似，如果把 $p$ 固定成第一个 D，那我只需要再后面拼接 CD。
- 如果我要知道后面 CD 的方案数，同上，我需要记录 D 的方案数，也就是个桶了。

所以我用 $f1,f2,f3$ 分别记录：$p$ 固定成最后一个 D、最后一个 C、第一个 D 的方案数。

那么转移就不难想了。

- $f2$ 转移的时候，我们就是在 C 后面拼 D，那枚举所有可能的 D 加上贡献就好。
- $f3$ 转移也是同理，我们在第一个 D 后面拼接 CD，直接枚举每个 C，然后把 $f2$ 的方案数加在 $f3$ 上就好了。
- 现在知道了后面拼接 DCD 的方案数，第一个 C 也固定了，现在只需要解决前面 AB 的方案数就好。方案数已经预处理好了，现在只需要容斥掉 ABCD 出现相等的情况。
- 利用第一个桶中的信息和 $p$ 的位置，不难容斥出 AB 方案数。

```
for(int i=n;i>=1;i--){
	int p=a[i];
	f1[p]++;//f1记录D方案数 
	for(int j=0;j<=61;j++){
		//当前字母为p，也就是说：C固定为p，枚举所有CDC 
		if(j==p) continue;//重复不能计入 
		f3[p][j]+=f2[j][p], f3[p][j] %=mod;//f3记录DCD方案数 
		f2[p][j]+=f1[j], f2[p][j] %=mod;//f2记录CD方案数 
		//----------------------------容斥过程 
		int x1=t[i-1][j] * (i-1-t[i-1][j]) %mod;
		int x2=t[i-1][p] * (i-1-t[i-1][p]) %mod;
		int x3=t[i-1][j] * t[i-1][p] %mod;
		int x=(g[i-1] -x1 -x2 +x3 +mod) %mod;
		ans+=f3[j][p] * x, ans %= mod;
	}
}
```
两份核心代码加在一起就是 AC 代码了。

## CODE：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+7,mod=998244353;
char s[N];
int n,ans,a[N],t[N][65];
int g[N],f1[65],f2[65][65],f3[65][65],f4[65][65];//dp数组 
void init(){//初始化 
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if('A'<=s[i]&&s[i]<='Z') a[i]=s[i]-'A';
		else if('a'<=s[i]&&s[i]<='z') a[i]=s[i]-'a'+26;
		else a[i]=s[i]-'0'+52;
		for(int j=0;j<=61;j++){
			t[i][j]=t[i-1][j];//继承
			if(a[i]==j) t[i][j]++;//更新桶 
			g[i]+=t[i][j] * (i-t[i][j]);
			//枚举i,有i*(i-t[i][j])种AB方案 
		}
		g[i]>>=1;//AB、BA都会被计算，去除重复贡献 
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>(s+1);
	init();
	for(int i=n;i>=1;i--){
		int p=a[i];
		f1[p]++;//f1记录D方案数 
		for(int j=0;j<=61;j++){
			//当前字母为p，也就是说：C固定位p，枚举所有CDC 
			if(j==p) continue;//重复不能计入 
			f3[p][j]+=f2[j][p], f3[p][j] %=mod;//f3记录DCD方案数 
			f2[p][j]+=f1[j], f2[p][j] %=mod;//f2记录CD方案数 
			//----------------------------容斥过程 
			int x1=t[i-1][j] * (i-1-t[i-1][j]) %mod;
			int x2=t[i-1][p] * (i-1-t[i-1][p]) %mod;
			int x3=t[i-1][j] * t[i-1][p] %mod;
			int x=(g[i-1] -x1 -x2 +x3 +mod) %mod;
			ans+=f3[j][p] * x, ans %= mod;
		}
	}
	cout<<ans;
	return 0;
}
```

~~这么好的题解真的不点个赞再走吗？~~

---

## 作者：_Ch1F4N_ (赞：7)

先观察 ``namomo`` 这个串。

其所具备的性质是形如 $ABAB$ 的串与前面任意两个与 $A,B$ 指代不同的字符拼接而成。

考虑怎么处理 $ABAB$，由于只有两种字符，所以设计状态 $dp_{i,j,0/1/2}$ 分别表示起始位置为 $i$ 形如 $s[i],j$，$s[i],j,s[i]$ 与 $s[i],j,s[i],j$ 的串数量，这里由于空间不够你可能只能开两个 dp 数组交替使用。

对于前面选取两个不同字符的方案，相仿的 dp 再容斥即可。

时间复杂度线性乘字符集。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;
const int mod = 998244353;
string S;
int a[maxn];//[0,62)
int dp[maxn][62];//s[i] c -> s[i] c s[i] -> s[i] c s[i] c
int DP[maxn][62];
int cnt[62];
int g[62][62];
int p[62][62],n;
int F[62];
int sum;
signed main(){
    cin>>S;
    n=S.size();
    for(int i=1;i<=n;i++){
        if(S[i-1]>='a'&&S[i-1]<='z') a[i]=S[i-1]-'a';
        else if(S[i-1]>='A'&&S[i-1]<='Z') a[i]=S[i-1]-'A'+26;
        else a[i]=S[i-1]-'0'+52;
    }
    for(int i=n;i>=1;i--){
        for(int j=0;j<62;j++) dp[i][j]=cnt[j];
        cnt[a[i]]++;
    }
    memset(cnt,0,sizeof(cnt));
    for(int i=n;i>=1;i--){
        for(int j=0;j<62;j++) DP[i][j]=g[a[i]][j];
        for(int j=0;j<62;j++) g[j][a[i]]=(g[j][a[i]]+dp[i][j])%mod;
    }
    memset(dp,0,sizeof(dp));
    memset(g,0,sizeof(g));
    for(int i=n;i>=1;i--){
        for(int j=0;j<62;j++) dp[i][j]=g[a[i]][j];
        for(int j=0;j<62;j++) g[j][a[i]]=(g[j][a[i]]+DP[i][j])%mod;
    }
    memset(DP,0,sizeof(DP));
    for(int i=1;i<=n;i++){
        for(int j=0;j<62;j++) DP[i][j]=cnt[j];
        cnt[a[i]]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<62;j++){
            if(j!=a[i]){
                int res1=(((sum+mod-F[a[i]])%mod+mod-F[j])%mod+p[a[i]][j]+p[j][a[i]])%mod;
                ans=(ans+res1*dp[i][j]%mod)%mod;
            }
        }
        for(int j=0;j<62;j++){
            if(j!=a[i]){
                sum=(sum+DP[i][j])%mod;
                F[a[i]]=(F[a[i]]+DP[i][j])%mod;
                F[j]=(F[j]+DP[i][j])%mod;
                p[j][a[i]]=(p[j][a[i]]+DP[i][j])%mod;
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：lwwwb_555 (赞：5)

题意：给定一个字符串，叫你从中按顺序选 $6$ 个字符，满足前 $4$ 个字符互不相同，第 $5$ 个字符与第 $3$ 个字符相同，第 $6$ 个字符与第 $4$ 个字符相同。

# 题解
题目无非是想让我们找形似```abcdcd```的不连续子串个数，我们可以先考虑后面的```cdcd```，那么我们要如何来寻找这种类型的子串呢？

我们可以倒着来推，我们设整个字符串长度为 $len$，$t_{0,i}$ 来表示从第 $len$ 位到第 $i$ 位 $s_i$ 出现了多少次，$t_{1,i,j}$ 表示第 $5$ 位是 $i$ 且第 $6$ 位是 $j$ 的方案总数，$t_{2,i,j}$ 表示第 $4$ 位是 $i$ 且第 $5$ 位是 $j$ 的方案总数，$t_{3,i,j}$ 表示第 $3$ 位是 $i$ 且第 $4$ 位是 $j$ 的方案总数。
那么转移方程就是这样：

```cpp
int zhuan(char c){
	if(c>='a' && c<='z') return c-'a';
	if(c>='A' && c<='Z') return c-'A'+26;
	return c-'0'+52;
}//先把字符转成数字
for(int i=len;i>=1;i--){
	int p=zhuan(s[i]);
	t[p]++;
	for(int j=0;j<=61;j++){
		if(j==p) continue;
		t1[p][j]=(t1[p][j]+t[j])%mod;
		t2[p][j]=(t2[p][j]+t1[j][p])%mod;
		t3[p][j]=(t3[p][j]+t2[j][p])%mod;
	}
}
```
然后我们再来考虑在前面加上```ab```的情况。

首先，我们先算出前面不重复的选两个字符的方案数，然后减去包含```c```的方案数，减去包含```d```的方案数，因为同时包含```c```和```d```的方案数会被多减，所以我们最后再把它加上。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000005];
long long t1[62],t2[62][62],t3[62][62],t4[62][62],tong[1000005][62],res[1000005];
const long long mod=998244353;
long long ans=0; 
int zhuan(char c){
	if(c>='a' && c<='z') return c-'a';
	if(c>='A' && c<='Z') return c-'A'+26;
	return c-'0'+52;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>(s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++){
		int p=zhuan(s[i]);
		res[i]=res[i-1];
		for(int j=0;j<=61;j++){
			tong[i][j]=tong[i-1][j];
			res[i]=(res[i]+tong[i-1][j])%mod;
			if(p==j) tong[i][j]++,res[i]=(res[i]-tong[i-1][j]+mod)%mod;
		}
	}
	for(int i=len;i>=1;i--){
		int p=zhuan(s[i]);
		t1[p]++;
		for(int j=0;j<=61;j++){
			if(j==p) continue;
			t2[p][j]=(t2[p][j]+t1[j])%mod;
			t3[p][j]=(t3[p][j]+t2[j][p])%mod;
			ans=ans+(long long)(t3[j][p])*(res[i-1]-(long long)tong[i-1][j]*(i-1-tong[i-1][j])%mod+mod-(long long)tong[i-1][p]*(i-1-tong[i-1][p])%mod+mod+tong[i-1][p]*tong[i-1][j]%mod)%mod;
			ans%=mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

