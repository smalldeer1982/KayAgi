# [ABC346D] Gomamayo Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc346/tasks/abc346_d

`0`, `1` からなる長さ $ N $ の文字列 $ S $ が与えられます。

`0`, `1` からなる長さ $ N $ の文字列 $ T $ は以下の条件を満たすとき、またそのときに限り **良い文字列** であると定義します。

- $ 1\ \leq\ i\ \leq\ N\ -\ 1 $ を満たす整数 $ i $ であって、$ T $ の $ i $ 文字目と $ i\ +\ 1 $ 文字目が一致するようなものがちょうど $ 1 $ つ存在する。
 
$ i\ =\ 1,2,\ldots,\ N $ について以下の操作を $ 1 $ 度行うか行わないか選ぶことができます。

- $ S $ の $ i $ 文字目が `0` であるとき $ S $ の $ i $ 文字目を `1` に、そうでないとき $ S $ の $ i $ 文字目を `0` に置き換える。操作を行った場合、$ C_i $ のコストがかかる。
 
$ S $ を良い文字列にするために必要なコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ S $ は長さ $ N $ の `0`,`1` からなる文字列
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- $ N,\ C_i $ は整数
 
### Sample Explanation 1

$ i\ =\ 1,\ 5 $ に対して操作を行い、$ i\ =\ 2,\ 3,\ 4 $ に対して操作を行わないことで $ S\ = $ `10010` となり、$ S $ は良い文字列となります。このときかかるコストは $ 7 $ であり、コスト $ 7 $ 未満で $ S $ を良い文字列にすることはできないため、$ 7 $ を出力します。

## 样例 #1

### 输入

```
5
00011
3 9 2 6 4```

### 输出

```
7```

## 样例 #2

### 输入

```
4
1001
1 2 3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
11
11111100111
512298012 821282085 543342199 868532399 690830957 973970164 928915367 954764623 923012648 540375785 925723427```

### 输出

```
2286846953```

# 题解

## 作者：2huk (赞：12)

给定一个长度为 $n$ 的 $01$ 串 $s$。

如果 $s$ 是「IOIAKer」，当且仅当满足以下条件：

- 有且仅有一个整数 $i$ 满足 $1 \le i < n$ 且 $s_i = s_{i + 1}$。

对于每个 $i = (1, 2, 3, \dots, n)$，执行以下操作：

- 花费 $c_i$ 的代价将 $s_i$ 取反。

求将 $s$ 变成「IOIAKer」所需的最小代价。

$n \le 2 \times 10^5$，$c_i \le 10^9$。

---

一眼 DP。

设状态 $f_{i, 0/1, 0/1}$ 表示若只考虑 $s$ 的前 $i$ 位，第 $i$ 位将要变成 $0/1$，且字符串将要变成状态 $0/1$ 所需要花费的最小代价。其中，「状态 $0$」表示 $01$ 交替，即不存在 $s_i = s_{i + 1}$。「状态 $1$」表示题目中的要求，即存在一个 $s_i = s_{i + 1}$。那么答案即 $\min(f_{n, 0, 1}, f_{n, 1, 1})$。

转移可以枚举上一位填的什么。然后根据是否需要翻转计算代价。

```cpp
f[i][0][0] = f[i - 1][1][0] + (s[i] == '1') * c[i];
f[i][1][0] = f[i - 1][0][0] + (s[i] == '0') * c[i];
f[i][0][1] = min(f[i - 1][1][1], f[i - 1][0][0]) + (s[i] == '1') * c[i];
f[i][1][1] = min(f[i - 1][0][1], f[i - 1][1][0]) + (s[i] == '0') * c[i];
```

完整[代码](https://atcoder.jp/contests/abc346/submissions/51566144)。

---

## 作者：KSCD_ (赞：4)

# 题意
给出一个只包含 $0$ 和 $1$ 的字符串，每个字符取反需要一定代价，要求最后使串中有且仅有一组相邻字符相同，求最小代价。
# 思路
考虑动态规划（或者说是递推）。

首先能想到的是设 $f_i$ 表示前 $i$ 个字符的答案。

然而我们发现难以从 $f_{i-1}$ 向 $f_{i}$ 转移，有以下两个问题需要解决：

- 转移时当前位是否要改变？这还与上一位的值有关。
- 相同的那组字符在哪？是这一位与上一位还是在这一位之前？

为了解决这两个问题，我们就要增加状态的维度，于是有了新的状态：设 $f_{i,j,k}$ 为前 $i$ 位中有 $j$ 组相同的相邻字符，且第 $i$ 位为 $k$ 的最小代价。显然这里的 $j,k$ 都只有 $0$ 和 $1$ 两种取值。

接下来考虑转移：$f_{i,0}$ 只能从 $f_{i-1,0}$ 转移来，分为修改和不修改两种。而 $f_{i,1}$ 可从 $f_{i-1,0}$ 且令第 $i$ 位与上一位相同，或 $f_{i-1,1}$ 且令第 $i$ 位与上一位不同转移来。

最后是边界：显然有 $f_{1,0,a_i}=0,f_{1,0,!a_i}=c_i,f_{1,1,0}=f_{1,1,1}=+\infty$

答案即为 $f_{n,1,0}$ 与 $f_{n,1,1}$ 的较小值。
# 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+10;
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar();}
    return s*w;
}
char s[N];
int n,a[N],c[N],f[N][2][2];//状态如上述 
signed main()
{
	n=read();
	cin>>s;
	for(int i=1;i<=n;i++) a[i]=s[i-1]-'0',c[i]=read(); 
	f[1][0][a[1]]=0,f[1][0][!a[1]]=c[1];
	f[1][1][a[1]]=f[1][1][!a[1]]=1e18;//初值 
	for(int i=2;i<=n;i++)
	{
		f[i][0][a[i]]=f[i-1][0][!a[i]];
		f[i][1][a[i]]=min(f[i-1][1][!a[i]],f[i-1][0][a[i]]);//不修改 
		f[i][0][!a[i]]=f[i-1][0][a[i]]+c[i];
		f[i][1][!a[i]]=min(f[i-1][1][a[i]],f[i-1][0][!a[i]])+c[i];//修改 
	}
	cout<<min(f[n][1][0],f[n][1][1]);
	return 0;
}
```

---

## 作者：wangbinfeng (赞：4)

[![](https://img.shields.io/badge/题目-AT__abc346__d_[ABC346D]_Gomamayo_Sequencet-green)
![](https://img.shields.io/badge/难度-暂无评定（普及/提高−）-yellow)
![](https://img.shields.io/badge/考点-动态规划（DP）-blue)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/AT_abc346_d)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009) 

-----------
题意：已知一个 `01` 串，修改第 $i$ 个字符需要 $a_i$ 的花费。问对 $\forall i\in\left(0,n-2\right)$ 恰好有且只有一个 $s_i=s_{i+1}$ 的最小花费。

考虑动态规划。具体的 $dp_{i,j,k}$ 表示目前枚举到第 $i$ 个，当前字符为 $j\in\{0,1\}$，目前已经有 $k\in\{0,1\}$ 个连续相同的字符对。

具体的预处理和转移可以看代码，应该不难理解（主要是太多了 qwq）。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[2000009],dp[2000009][2][2];//第i位，当前为0/1，是否已经有相同字符对 
string s;
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++)cin>>a[i];
  //预处理开始
	if(s[0]=='0'&&s[1]=='0'){
		dp[0][0][0]=0,dp[0][0][1]=-1,dp[0][1][0]=a[0],dp[0][1][1]=-1;
		dp[1][0][0]=a[0],dp[1][0][1]=0,dp[1][1][0]=a[1],dp[1][1][1]=a[0]+a[1];
	}else if(s[0]=='0'&&s[1]=='1'){
		dp[0][0][0]=0,dp[0][0][1]=-1,dp[0][1][0]=a[0],dp[0][1][1]=-1;
		dp[1][0][0]=a[0]+a[1],dp[1][0][1]=a[1],dp[1][1][0]=0,dp[1][1][1]=a[0];
	}else if(s[0]=='1'&&s[1]=='0'){
		dp[0][0][0]=a[0],dp[0][0][1]=-1,dp[0][1][0]=0,dp[0][1][1]=-1;
		dp[1][0][0]=0,dp[1][0][1]=a[0],dp[1][1][0]=a[0]+a[1],dp[1][1][1]=a[1];
	}else if(s[0]=='1'&&s[1]=='1'){
		dp[0][0][0]=a[0],dp[0][0][1]=-1,dp[0][1][0]=0,dp[0][1][1]=-1;
		dp[1][0][0]=a[1],dp[1][0][1]=a[0]+a[1],dp[1][1][0]=a[0],dp[1][1][1]=0;
	}
  //预处理结束
  //转移开始
	for(int i=2;i<n;i++){
		if(s[i]=='0'){
			dp[i][0][0]=dp[i-1][1][0],dp[i][1][0]=dp[i-1][0][0]+a[i];
			dp[i][0][1]=min(dp[i-1][1][1],dp[i-1][0][0]),
			dp[i][1][1]=min(dp[i-1][0][1],dp[i-1][1][0])+a[i];
		}else if(s[i]=='1'){
			dp[i][0][0]=dp[i-1][1][0]+a[i],dp[i][1][0]=dp[i-1][0][0];
			dp[i][0][1]=min(dp[i-1][1][1],dp[i-1][0][0])+a[i],
			dp[i][1][1]=min(dp[i-1][0][1],dp[i-1][1][0]);
		}
	}
  //转移结束
	cout<<min(dp[n-1][0][1],dp[n-1][1][1]);
}
```

---

## 作者：JuRuoOIer (赞：3)

# 题解 ABC346D - Gomamayo Sequence

前排提示：本题解包含 **DP** 做法和 **简单扫描** 做法。

### 题意

已提交翻译。

定义一个 01 串 $T$ 是**好串**，当且仅当存在**恰好一个** $1 \le i < |T|$，使得 $T_i=T_{i+1}$。

给定长度为 $n$ 的 01 串 $S$，对第 $i$ 位取反的代价为 $c_i$，求使其成为一个好串的最小代价。

数据范围：$n \le 2 \times 10^5$。

### DP 做法

赛时看到这玩意就想 dp。

首先好串那一坨定义归根结底就是一个：恰好有一次连续的两个字符相同。

于是设 $dp_{i,0/1,0/1}$ 表示考虑前 $i$ 个字符，是否已经出现过连续两个相同了，这个字符是否取反了的最小答案。

初始化时 $dp_{0,0,0}\leftarrow0,dp_{0,0,1}\leftarrow c_0$，其余的全部设成 $\text{inf}$。

转移时根据 $S_i$ 是否等于 $S_{i-1}$ 简单分讨一下后两维即可。由于一共有 $12$ 种可能，这里不再赘述，需要的可以直接对着状态设计看代码。

最终的答案就是 $\min(dp_{n,1,0},dp_{n,1,1})$。时空复杂度 $O(n)$。

```cpp
//个人习惯，代码中下标从 0 开始，所以与题解中略有不同。
ll n,a[200010],dp[200010][2][2];//a 数组相当于题目中的 c
string s;
int main(){
	cin>>n>>s;
	for(int i=0;i<n;i++){
		cin>>a[i];
		//记得初始化
		dp[i][0][0]=(1ll<<62);
		dp[i][0][1]=(1ll<<62);
		dp[i][1][0]=(1ll<<62);
		dp[i][1][1]=(1ll<<62);
	}
	dp[0][0][0]=0;
	dp[0][0][1]=a[0];
	for(int i=1;i<n;i++){
		//大力分讨
		if(s[i]==s[i-1]){
			dp[i][1][0]=min(dp[i][1][0],dp[i-1][0][0]);
			dp[i][0][0]=min(dp[i][0][0],dp[i-1][0][1]);
			dp[i][1][0]=min(dp[i][1][0],dp[i-1][1][1]);
			dp[i][1][1]=min(dp[i][1][1],dp[i-1][0][1]+a[i]);
			dp[i][0][1]=min(dp[i][0][1],dp[i-1][0][0]+a[i]);
			dp[i][1][1]=min(dp[i][1][1],dp[i-1][1][0]+a[i]);
		}
		else{
			dp[i][0][0]=min(dp[i][0][0],dp[i-1][0][0]);
			dp[i][1][0]=min(dp[i][1][0],dp[i-1][1][0]);
			dp[i][1][0]=min(dp[i][1][0],dp[i-1][0][1]);
			dp[i][0][1]=min(dp[i][0][1],dp[i-1][0][1]+a[i]);
			dp[i][1][1]=min(dp[i][1][1],dp[i-1][1][1]+a[i]);
			dp[i][1][1]=min(dp[i][1][1],dp[i-1][0][0]+a[i]);
		}
	}
	cout<<min(dp[n-1][1][0],dp[n-1][1][1]);
	return 0;
}

```

### 简单扫描做法

预处理出下面四个数组：
- $pre0_i$ 表示前 $i$ 个字符变成 `010101...` 的代价；
- $pre1_i$ 表示前 $i$ 个字符变成 `101010...` 的代价；
- $suf0_i$ 表示第 $i+1$ 至 $n$ 个字符变成 `...101010` 的代价；
- $suf1_i$ 表示第 $i+1$ 至 $n$ 个字符变成 `...010101` 的代价；

然后扫一遍，枚举出现连续两个相同字符的位置，并推算出前后缀分别使用哪个数组即可。也就是说：
- 对于前缀：
  - 当 $i$ 为偶数时，$S_i$ 与 $S_1$ 相反，即希望 $S_i=0$ 时前 $i$ 项代价为 $pre1_i$，反之亦然。
  - 当 $i$ 为奇数时，$S_i$ 与 $S_1$ 相同，即希望 $S_i=1$ 时前 $i$ 项代价为 $pre1_i$，反之亦然。
- 对于后缀：
  - 当 $n-i$ 为偶数时，$S_i$ 与 $S_1$ 相反，即希望 $S_{i+1}=0$ 时后 $n-i$ 项代价为 $suf1_{i+1}$，反之亦然。
  - 当 $n-i$ 为奇数时，$S_i$ 与 $S_1$ 相同，即希望 $S_{i+1}=1$ 时后 $n-i$ 项代价为 $suf1_{i+1}$，反之亦然。

取个最大值即可。时空复杂度也都是 $O(n)$。

```cpp
ll n,a[200010],p0[200010],p1[200010],s0[200010],s1[200010],ans=(1ll<<62);
string s;
int main(){
	cin>>n>>s;
	s="0"+s;//string 编号从 0 开始，前面加个 0 变成从 1 开始
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){//预处理前缀 
		p0[i]=p0[i-1]+(s[i]-'0'==i%2)*a[i];
		p1[i]=p1[i-1]+(s[i]-'0'!=i%2)*a[i];
	} 
	for(int i=n;i;i--){//预处理后缀 
		s0[i]=s0[i+1]+(s[i]-'0'==(n-i+1)%2)*a[i];
		s1[i]=s1[i+1]+(s[i]-'0'!=(n-i+1)%2)*a[i];
	} 
	for(int i=1;i<n;i++){//注意！！！这里是小于，不是小于等于！！！
		ans=min(ans,(i%2?p1[i]:p0[i])+((n-i)%2?s1[i+1]:s0[i+1]));
		ans=min(ans,(i%2?p0[i]:p1[i])+((n-i)%2?s0[i+1]:s1[i+1]));
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：jerry1717 (赞：2)

## 题意
给定一个长度为 $N$ 的字符串 $S$，由 $0$ 和 $1$ 构成。可以花 $C_i$ 改变第 $i$ 位的字符为 $1$ 或 $0$。最后花最少的钱让 $S$ 有且只有一个 $i$ 满足 $C_i = C_{i+1}$。
## 做法
观察发现 $N$ 数量级较大，不支持 $n^2$ 算法暴力选点算和，所以使用前缀和数组 $suma_i$ 表示把第 $1$ 到第 $i$ 位变成偶数位都为 $0$，奇数位都为 $1$ 的字符串的花费。$sumb_i$ 表示把第 $1$ 到第 $i$ 位变成偶数位都为 $1$，奇数位都为 $0$ 的字符串的花费。

然后是算花费，在第 $i$ 个点，把前面的点和点 $i$ 构成一个任意相邻两位都不同的字符串，让后面的点第一个与点 $i$ 相同，剩下的也构成任意相邻两位都不同的字符串。这里有个细节，你可以把第 $i$ 个点改为另一个字符，可能会少花费一些。

这是代码
```cpp
#include<bits/stdc++.h>
#define int long long //要开long long 
using namespace std;
int a[1000001],ans=9e18,suma[1000001],sumb[1000001];
int n;
char c[1000001];
signed main(){
	scanf("%lld",&n);
	scanf("%s",c+1);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		suma[i]=suma[i-1];
		sumb[i]=sumb[i-1];
		if((i&1)==0&&c[i]=='1')suma[i]+=a[i];//sum[a]:101010...
		if((i&1)==1&&c[i]=='0')suma[i]+=a[i];
		if((i&1)==1&&c[i]=='1')sumb[i]+=a[i];
		if((i&1)==0&&c[i]=='0')sumb[i]+=a[i];//sum[b]:010101...
	}
	for(int i=1;i<=n-1;i++){ //枚举到n-1即可 我调了半天 
		int res=0;
		if(c[i]=='0'){
			res=0;
			if(((i-1)&1)==0)res+=sumb[i-1];//若i-1位为偶数 
			else res+=suma[i-1];
			if(((i+1)&1)==0)res+=(suma[n]-suma[i]);//若i+1位为偶数 
			else res+=(sumb[n]-sumb[i]);
			ans=min(ans,res);
			res=a[i];//要赋初始值  
			if(((i-1)&1)==0)res+=suma[i-1];//和下面代码一样 
			else res+=sumb[i-1];
			if(((i+1)&1)==0)res+=(sumb[n]-sumb[i]);
			else res+=(suma[n]-suma[i]);
			ans=min(ans,res);
		}else{
			res=0;
			if(((i-1)&1)==0)res+=suma[i-1];
			else res+=sumb[i-1];
			if(((i+1)&1)==0)res+=(sumb[n]-sumb[i]);
			else res+=(suma[n]-suma[i]);
			ans=min(ans,res);
			res=a[i];//要赋初始值  
			if(((i-1)&1)==0)res+=sumb[i-1];
			else res+=suma[i-1];
			if(((i+1)&1)==0)res+=(suma[n]-suma[i]);
			else res+=(sumb[n]-sumb[i]);
			ans=min(ans,res);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Liyunze123 (赞：2)

# 1.题意
有一个长为 $N$ 的 $01$ 串 $S$。

定义好字符串：有且仅有一个 $1 \le i < N$，满足 $S_i = S_{i+1}$。

把每个字符修改（$0$ 变 $1$，$1$ 变 $0$）需要 $c_i$ 块钱。问你把 $S$ 改成好字符串需要几块钱。
# 2.解题思路
考虑前缀和。

设 $s_{1,i}$ 表示把前 $i$ 个字符修改成 $1010……$ 需要的费用，$s_{0,i}$  表示把前 $i$ 个字符修改成 $0101……$ 需要的费用。

接着枚举把哪两个相邻的字符改成 $x$。计算出第 $i$ 个字符为 $x$ 时第一个字符为 $t$，如果第 $i+2$ 个字符为 $(x+1) \mod 2$ 时，第一个字符 $p$。如果第 $i$ 个字符，第 $i+1$ 个字符不是 $x$，要加修改费，再加上 $s_{t,i-1} + s_{p,n} - s_{p,w+1}$，跟答案取个最小值。
# 3.注意事项
一开始要把 $ans$ 初始化成正无穷！

注意是 $s_{0,i}$ 而不是 $s_{2,i}$。

最重要的就是**不开 long long 见祖宗！**
# 4.代码展示
```
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],b[200010];
long long s[3][200010],ans=1e18,sum;
char c[200010];
int main(){
    scanf("%d%s",&n,c);
    for(int w=1;w<=n;w++)scanf("%d",&b[w]),a[w]=c[w-1]-'0';
    for(int w=1;w<=n;w++)
        if(a[w]!=w%2)s[1][w]=s[1][w-1]+b[w];
        else s[1][w]=s[1][w-1];
    for(int w=1;w<=n;w++)
        if(a[w]==w%2)s[0][w]=s[0][w-1]+b[w];
        else s[0][w]=s[0][w-1];
    for(int w=1;w<n;w++){//w,w+1
        for(int x=0,t,p;x<=1;sum=0,x++){
            if(a[w]!=x)sum+=b[w];
            if(a[w+1]!=x)sum+=b[w+1];
            if(x)t=w%2;
            else t=(w+1)%2;
            p=(t+1)%2;
            sum+=s[t][w-1]+s[p][n]-s[p][w+1],ans=min(ans,sum);
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：2)

### 思路
观察答案字符串可以发现，只有一对相邻的位置是相同的，其它都是 $0$ 和 $1$ 交错出现，那么只需要枚举相同的这对位置同时计算形成的这个字符串的成本取最小值就行了。
### 暴力做法
根据上文所述的思路，可以写出一个 $O(n^2)$ 的暴力算法。就是枚举位置和这个位置相同的数值，在写个循环遍历操作的代价。
### 正解
我们可以发现除了这个位置以外的其它位置的代价是可以通过预处理计算的，时间复杂度为 $O(n)$。因为答案字符串等同于在两种开头分别为 $0$ 和 $1$ 的 $01$ 串里取反一位，所以我们可以前缀和预处理每一位两种取值的总代价,取所有情况的最小值。
![](https://cdn.luogu.com.cn/upload/image_hosting/s5j9qvzd.png)
代码如下：
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define ll long long
const int N=1e6+5;
ll n,c[N];
string s;
ll f[N][2],g[N][2];
int main(){
    cin>>n>>s;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        char ch=s[i-1];
        if(ch=='0') f[i][0]=f[i-1][1],f[i][1]=f[i-1][0]+c[i];
        else f[i][1]=f[i-1][0],f[i][0]=f[i-1][1]+c[i];
    }
    for(int i=n;i>=1;i--){
        char ch=s[i-1];
        if(ch=='0') g[i][0]=g[i+1][1],g[i][1]=g[i+1][0]+c[i];
        else g[i][1]=g[i+1][0],g[i][0]=g[i+1][1]+c[i];
    }
    ll ans=1e18;
    for(int i=1;i<n;i++){
        char ch=s[i-1]-'0';
        ans=min({ans,f[i][ch]+g[i+1][ch],f[i][ch^1]+g[i+1][ch^1]});
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：2023lpx (赞：1)

# [ABC346D] Gomamayo Sequence 题解

## 题目大意

给你一串 01 串 $S$，对于每个位置 $i$，将其变为其反值的代价为 $C_i$，求让 $S$ 变为形如两段，由多个 ```01``` 或 ```10``` 组成的子串。求最小代价。

## 思路

考虑**前缀和**和**后缀和**。

设 $qz_{i,0}$ 表示使 $S$ 的前 $i$ 个位置变为形如 ```1010...``` 的代价。

设 $qz_{i,1}$ 表示使 $S$ 的前 $i$ 个位置变为形如 ```0101...``` 的代价。

设 $hz_{i,0}$ 表示使 $S$ 的后 $i$ 个位置变为形如 ```...1010``` 的代价。

设 $hz_{i,1}$ 表示使 $S$ 的后 $i$ 个位置变为形如 ```...0101``` 的代价。

那么对于位置 $i$，若要使其不改变，则代价为 $\min(qz_{i,0}+hz_{i+1,1},qz_{i,1}+hz_{i+1,0})$。

统计前缀后缀有手就行。

## code

```cpp
#include<cstdio>
using namespace std;
#define int long long
int n;
int const maxn=200000;
int s[maxn+1];
int c[maxn+1];
long long f1,f2;
long long ans=maxn*1000000000+1;
int min(int a,int b){
	return a<b?a:b;
}
long long qz[maxn+1][2];
long long hz[maxn+1][2];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		char in=getchar();
		while(in!='0'&&in!='1'){
			in=getchar();
		}
		s[i]=in-'0';
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&c[i]);
	}
	for(int i=1;i<=n;i++){
		qz[i][0]=qz[i-1][0];
		qz[i][1]=qz[i-1][1];
		qz[i][0]+=s[i]==i%2?0:c[i];
		qz[i][1]+=s[i]==(i+1)%2?0:c[i];
	}
	for(int i=n;i>=1;i--){
		hz[i][0]=hz[i+1][0];
		hz[i][1]=hz[i+1][1];
		hz[i][0]+=s[i]==i%2?0:c[i];
		hz[i][1]+=s[i]==(i+1)%2?0:c[i];
	}
	for(int i=1;i<n;i++){
		ans=min(ans,qz[i][0]+hz[i+1][1]);
		ans=min(ans,qz[i][1]+hz[i+1][0]);
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：cqbzhyn (赞：1)

这道题是一道 $\operatorname{dp}$ 题。

首先，题面明确要求了**有且只有一个** $i$ 满足条件，那么第一思路肯定是暴力枚举 $i$。

但是，枚举 $i$ 的时间是 $O(n)$。如果我们需要对于每一个 $i$ 都遍历一遍字符串判断每一位是否相同的话，时间复杂度就是 $O(n^2)$，肯定会超时。

这时候考虑 $\operatorname{dp}$。我们发现，第 $i$ 位和第 $i+1$ 位可以将字符串分成 $[1,i]$ 和 $[i+1,n]$ 两段，而不管第 $i$ 位和第 $i+1$ 位取什么颜色，这两段分别只有两种情况：
1. 对于 $[1,i]$ 来说，两种情况分别为第 $1$ 位为 $0$ 和第 $1$ 位为 $1$ 。

2. 对于 $[i+1,n]$ 来说，两种情况分别为第 $n$ 位为 $0$ 和第 $n$ 位为 $1$ 。

于是我们定义 $pre_{i,j}$ 为对于 $[1,i]$ 区间，第 $1$ 位为 $j$ 时的转换总代价，$suf_{i,j}$ 为对于 $[i,n]$ 区间，第 $n$ 位为 $j$ 时的转换总代价 $(j \in \{1,2\})$。

以 $pre$ 数组为例，推出如下状态转移方程：

当第 $i$ 位为 $j$ 时，如果 $i \bmod 2$ 为 $0$，那么第 $1$ 位就应该是 $1 \oplus j$；同时，如果 $i \bmod 2$ 为 $1$，那么第 $1$ 位就应该是 $j$。

根据以上，推出状态转移方程为：
$$pre_{i,0}=pre_{i-1,0}+(i \bmod 2=s[i]) \times c[i]$$
$$pre_{i,1}=pre_{i-1,1}+(i \bmod 2 \ne s[i]) \times c[i]$$

$suf$ 数组同理，请读者自行推理。

最后枚举 $i$ ，对于第 $i$ 位取 $0$ 或 $1$ 的情况分别处理即可，处理过程同上。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,c[200005],ans=1e18,s[200005],pre[200005][2],suf[200005][2];
int main(){
	cin >> n;
	for(int i=1;i<=n;i++) scanf("%1d",&s[i]);
  	//%1d为每次读取一个字符作为值
	for(int i=1;i<=n;i++) cin >> c[i];
	for(int i=1;i<=n;i++){ //预处理前缀
		pre[i][0]=pre[i-1][0]+((i+1)%2!=s[i])*c[i];
		pre[i][1]=pre[i-1][1]+(i%2!=s[i])*c[i];
	}
	for(int i=n;i;i--){ //预处理后缀
		suf[i][0]=suf[i+1][0]+((n-i)%2!=s[i])*c[i];
		suf[i][1]=suf[i+1][1]+((n-i+1)%2!=s[i])*c[i];
	}
	for(int i=1;i<n;i++){ //计算答案
		ans=min(ans,pre[i][(i-1)%2]+suf[i+1][(n-i-1)%2]);
		ans=min(ans,pre[i][i%2]+suf[i+1][(n-i)%2]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：CEFqwq (赞：1)

我从去年辞帝京，谪居卧病浔阳城。浔阳【】无音乐，终岁不闻丝竹声。——白居易《琵琶行》

这道题很经典。我 $10min$ 切了。我们考虑用 $f_{i,j,k}$ 表示状态。

$i$ 表示处理到第 $i$ 个字符。

$j$ 表示当前字符是否修改。

$k$ 表示此前是否有两个连续字符相同。

然后就非常简单了。我们分讨当前字符是否等于前一个字符。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int f[200005][2][2], a[200005], n;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	cin >> s;
	memset(f, 0x3f3f3f3f, sizeof f);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	f[0][0][0] = 0;
	f[0][1][0] = a[0];
	for (int i = 1; i < n; i++)
		if (s[i] == s[i - 1]){
			f[i][1][0] = min(f[i][1][0], f[i - 1][0][0] + a[i]);
			f[i][0][0] = min(f[i][0][0], f[i - 1][1][0]);
			f[i][0][1] = min(f[i][0][1], min(f[i - 1][0][0], f[i - 1][1][1]));
			f[i][1][1] = min(f[i][1][1], min(f[i - 1][0][1], f[i - 1][1][0]) + a[i]);
		}else{
			f[i][1][0] = min(f[i][1][0], f[i - 1][1][0] + a[i]);
			f[i][0][0] = min(f[i][0][0], f[i - 1][0][0]);
			f[i][0][1] = min(f[i][0][1], min(f[i - 1][1][0], f[i - 1][0][1]));
			f[i][1][1] = min(f[i][1][1], min(f[i - 1][1][1], f[i - 1][0][0]) + a[i]);
		}
	cout << min(f[n - 1][1][1], f[n - 1][0][1]);
}
```

---

## 作者：kczw (赞：1)

# 题意
给定一个长 $N$ 的 `01` 串 $S$ 和序列 $C$。

你可以对 $S$ 操作，每次择 $i(1\le i\le N)$ 并有 $C_i$ 的代价，然后若 $S_i$ 为 `0` 则改为 `1`，若为 `1` 则改为 `0`。

求，使对于 $S$ 有且仅有一个 $i(1\le i\le N-1)$ 有 $S_i=S_{i+1}$ 的最小贡献是多少。
# 思路
首先明确一点，因为同一 $i$ 操作两次等于没有操作还有贡献，所以对于最优策略，同一 $i$ 至多操作一次。于是，不难发现这是一个简单的动规题。

分析一下：

- 易得转移是相邻两字符间的，所以对于每个字符的状态必有表示，所以有第一维表示字符位置。
- 不难明白我们需要表示字符最后的状态，第二维便是如此。
- 因为有且仅有一 $i(1\le i\le N-1)$ 有 $S_i=S_{i+1}$，所以，我们需要存储之前是否有 $S_i=S_{i+1}$ 的情况，第三维表示是否具有特殊情况。

知道了如何存储状态，其实转移就已经很明显了。为方便，这里令字符 $S_i$ 的值为 $0$ 或 $1$。

此处可根据转移自行理解，因为逻辑不难：

- $f_{i,S_i,0}=f_{i-1,s_i\oplus1,0}$
- $f_{i,S_i,1}=\min(f_{i-1,s_i,0},f_{i-1,s_i\oplus1,1})$
- $f_{i,S_i\oplus1,0}=f_{i-1,s_i,0}+c_i$
- $f_{i,S_i\oplus1,1}=\min(f_{i-1,s_i\oplus1,0},f_{i-1,s_i,1})+c_i$

最后记得初始化一下 dp 数组最大值。

到这里，相信代码已经不难构造了。
# 代码
```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N=2e5+5;

int n,c[N],f[N][2][2];

char s[N];

main(){
    
    scanf("%lld%s",&n,s+1);
    for(int i=1;i<=n;i++)
        scanf("%lld",&c[i]);
    //输入
    memset(f,0x3f,sizeof(f));
    //初始化最大值
    f[1][s[1]-'0'][0]=0;
    f[1][(s[1]-'0')^1][0]=c[1];
    //初始化 dp 值
    for(int i=2;i<=n;i++){
        int C=s[i]-'0';
	//当前字符值
        f[i][C][0]=f[i-1][C^1][0];
        f[i][C][1]=min(f[i-1][C][0],f[i-1][C^1][1]);
        f[i][C^1][0]=f[i-1][C][0]+c[i];
        f[i][C^1][1]=min(f[i-1][C^1][0],f[i-1][C][1])+c[i];
        //如上转移
    }
    printf("%lld",min(f[n][0][1],f[n][1][1]));
    //输出取最后字符为 0 和 1 两种情况的最大值
    return 0;
}
```

---

## 作者：Shadow_T (赞：1)

### 题目大意

给定一个长度为 $n$ 的 $\texttt{01}$ 字符串 $s$，和一个数组 $c$，你可以进行以下操作任意次：

- 花费 $c_i$ 代价，翻转 $s_i$。

求使得 $s$ 有且仅有一对相邻位相同的最小代价。

### 题目大意

可以发现，满足条件的 $s$ 分为两种形式，每种形式由 $3$ 段组成：

- 一个 $\texttt{1}$ 结尾的 $\texttt{01}$ 交替串，两个 $\texttt{0}$ 再加上一个 $\texttt{1}$ 开头的 $\texttt{01}$ 交替串。比如 $\texttt{0101010010101}$。

- 一个 $\texttt{0}$ 结尾的 $\texttt{01}$ 交替串，两个 $\texttt{1}$ 再加上一个 $\texttt{0}$ 开头的 $\texttt{01}$ 交替串。比如 $\texttt{010101100101}$。

我们可以枚举一下中间为 $\texttt{00}$ 或 $\texttt{11}$ 的位置，剩下的都 $\texttt{01}$ 交替，计算出所有不符合的地方的价值，然后把这些价值取最小值。

我们可以维护四个前缀和 $q0o$，$q0j$，$q1o$，$q1j$：

- $s_i$ 为 $1$ 且 $i$ 为偶数。

- $s_i$ 为 $1$ 且 $i$ 为奇数。

- $s_i$ 为 $0$ 且 $i$ 为偶数。

- $s_i$ 为 $0$ 且 $i$ 为奇数。

（名字有点奇怪）。

然后分类讨论特殊点位置的花费，假设分类点位置为 $i$：

如果准备把 $s_i$ 和 $s_{i+1}$ 变成 $\texttt{0}$：

- 如果 $i-1$ 为偶数，花费为 $(q0j_{i-1}+q1o_{i-1})+(q0o_n-q0o_{i+1}+q1j_n-q1j_{i+1})+z$。

- 否则，花费为 $(q0o_{i-1}+q1j_{i-1})+(q0j_n-q0j_{i+1}+q1o_n-q1o_{i+1})+z$。

如果准备把 $s_i$ 和 $s_{i+1}$ 变成 $\texttt{1}$：

- 如果 $i-1$ 为偶数，花费为 $(q1j_{i-1}+q0o_{i-1})+(q1o_n-q1o_{i+1}+q0j_n-q0j_{i+1})+z$。

- 否则，花费为 $(q1o_{i-1}+q0j_{i-1})+(q1j_n-q1j_{i+1}+q0o_n-q0o_{i+1})+z$。

其中 $z$ 为 $s_i$ 和 $s_{i+1}$ 需要的花费。

复杂度 $O(n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int c[maxn],q0o[maxn],q0j[maxn],q1o[maxn],q1j[maxn];
signed main()
{
	int n;
	cin>>n;
	string s;
	cin>>s;
	for(int i=1;i<=n;i++)
	cin>>c[i];
	for(int i=1;i<=n;i++)
	{
		q0o[i]=q0o[i-1];
		q0j[i]=q0j[i-1];
		q1o[i]=q1o[i-1];
		q1j[i]=q1j[i-1];
		if(i&1)
		{
			if(s[i-1]=='0') q0j[i]+=c[i];
			else q1j[i]+=c[i];
		}
		else
		{
			if(s[i-1]=='0') q0o[i]+=c[i];
			else q1o[i]+=c[i];
		}
	}
	int Min=1e18;
	for(int i=1;i<n;i++)
	{
		int left,right;
		if((i-1)&1) left=q0j[i-1]+q1o[i-1];
		else left=q0o[i-1]+q1j[i-1];
		if(i&1) right=q0j[n]-q0j[i+1]+q1o[n]-q1o[i+1];
		else right=q0o[n]-q0o[i+1]+q1j[n]-q1j[i+1];
		int z=0;
		if(s[i-1]!='0') z+=c[i];
		if(s[i]!='0') z+=c[i+1];
		Min=min(Min,left+right+z);
		left=0,right=0,z=0;
		if((i-1)&1) left=q1j[i-1]+q0o[i-1];
		else left=q1o[i-1]+q0j[i-1];
		if(i&1) right=q1j[n]-q1j[i+1]+q0o[n]-q0o[i+1];
		else right=q1o[n]-q1o[i+1]+q0j[n]-q0j[i+1];
		if(s[i-1]!='1') z+=c[i];
		if(s[i]!='1') z+=c[i+1];
		Min=min(Min,left+right+z);
	}
	cout<<Min;
}
```

---

## 作者：zcz0263 (赞：1)

## 题目大意
有一个由 $0$ 和 $1$ 组成的长度为 $n$ 的 $S$ 序列，分别给定将第 $i$ 位修改为另一种取值的代价 $c_i$，问至少花费多少代价使得序列内有且仅有一对相邻位置相同。
## 思路
考虑开两个数组 $d1,d2$，用 $d1_i$ 记录将 $S$ 序列的 $1 \sim i$ 位改为形如 $\left\{ 0,1,0,1 \cdots \right\}$ 所需的代价，用 $d2_i$ 记录将 $S$ 序列的 $1 \sim i$ 位改为形如 $\left\{ 1,0,1,0 \cdots \right\}$ 所需的代价，然后枚举需要相同的两位中左边的一位，运用前缀和的思想不难发现：  
- 如果枚举的位置 $i$ 为奇数，那么将这两位均改为 $0$ 且让序列合法所需的代价就是 $[s_i==1] \times c_i + [s_{i+1}==1] \times c_{i+1} + d1_{i-1}+(d2_n-d2_{i+1})$，均改为 $1$ 则为 $[s_i==0] \times c_i + [s_{i+1}==0] \times c_{i+1} + d2_{i-1}+(d1_n-d1_{i+1})$。
- 如果枚举的位置 $i$ 为偶数，那么将这两位均改为 $0$ 且让序列合法所需的代价就是 $[s_i==1] \times c_i + [s_{i+1}==1] \times c_{i+1} + d2_{i-1}+(d1_n-d1_{i+1})$，均改为 $1$ 则为 $[s_i==0] \times c_i + [s_{i+1}==0] \times c_{i+1} + d1_{i-1}+(d2_n-d2_{i+1})$。

我们只需要枚举所有 $i$ 的时候让这几个值更新答案即可，注意答案可能爆 `long long`。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define INF INT_MAX
#define INF LLONG_MAX
#define pii pair<int,int>
#define vi vector<int>
string s;
vi c(200005),d1(200005),d2(200005);
int n,ans=INF;
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>s;
	s=" "+s;//这里是让字符串的下标从 1 开始 
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++){
		int to0=c[i]*(s[i]=='1'),to1=c[i]*(s[i]=='0');
		if(i&1){
			d1[i]=d1[i-1]+to0;
			d2[i]=d2[i-1]+to1;
		}else{
			d1[i]=d1[i-1]+to1;
			d2[i]=d2[i-1]+to0;
		}
	}
	for(int i=1;i<n;i++){
		int to0=(s[i]=='1')*c[i]+(s[i+1]=='1')*c[i+1],to1=(s[i]=='0')*c[i]+(s[i+1]=='0')*c[i+1];
		if(i&1){
			ans=min(ans,to0+d1[i-1]+d2[n]-d2[i+1]);
			ans=min(ans,to1+d2[i-1]+d1[n]-d1[i+1]);
		}else {
			ans=min(ans,to0+d2[i-1]+d1[n]-d1[i+1]);
			ans=min(ans,to1+d1[i-1]+d2[n]-d2[i+1]);
		}
	}
	cout<<ans;
}

```

---

## 作者：xiaofu15191 (赞：0)

递推题。

定义“A字符”为相同的第 $i$ 与 $i+1$
 个字符中的第 $i$ 个，“B字符”为第 $i+1$ 个，“C字符”为互不相同的字符。

设状态 $f_{i,j,k,l}$（$j \in \lbrace 0,1,2 \rbrace,k \in \lbrace 0,1\rbrace,l \in \lbrace 0,1 \rbrace$）。

$i$ 表示当前递推到字符串 $T$ 的第 $i$ 个字符处。

$j=0$ 表示当前字符为”C字符”，$j=1$ 表示当前为 “A字符”，$j=2$ 表示“B字符”。

$k$ 表示当前的期望字符为 $0/1$。

$l$ 表示是否满足第 $1$ 至 $i$ 个字符为题目中的 `good string`。

于是递推的转移方程就很好想了。

[AC记录](https://atcoder.jp/contests/abc346/submissions/51583805)

---

## 作者：QWQ_123 (赞：0)

我们发现最后的字符串除了相等的部分，一定是类似 $\texttt{0101010101}$ 或 $\texttt{1010101010}$。

于是考虑处理出前缀变成这两个字符串对应的花费和。

那么考虑枚举哪两个数相等，并枚举是 $\texttt{11}$ 还是 $\texttt{00}$。

然后分类讨论：
*	若是 $\texttt{11}$，并且前面有奇数个数，那么一定是 $\texttt{\dots01010\underline{11}01010\dots}$，所以就加上前缀 $\texttt{01}$ 和后缀 $\texttt{10}$ 的和。
*	若是 $\texttt{11}$，并且前面有偶数个数，那么一定是 $\texttt{\dots1010\underline{11}01010\dots}$，所以就加上前缀 $\texttt{10}$ 和后缀 $\texttt{01}$ 的和。
*	若是 $\texttt{00}$，并且前面有奇数个数，那么一定是 $\texttt{\dots10101\underline{00}101010\dots}$，所以就加上前缀 $\texttt{10}$ 和后缀 $\texttt{01}$ 的和。
*	若是 $\texttt{00}$，并且前面有偶数个数，那么一定是 $\texttt{\dots010101\underline{00}101010\dots}$，所以就加上前缀 $\texttt{01}$ 和后缀 $\texttt{10}$ 的和。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, m, k;
pair<int, int> g[200010], h[200010];
int ma[200010];
int s[200010];

signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for(int i = 1; i <= 200000; ++i) g[i] = {0, 0};
	for(int i = 1; i <= 200000; ++i) h[i] = {0, 0};
	for (int i = 1; i <= k; ++i) {
		int opt, x, y; scanf("%lld%lld%lld", &opt, &x, &y);
		if (opt == 1) {
			g[x] = {y, i};
		} else if (opt == 2) {
			h[x] = {y, i};
		}
	}
	sort(g + 1, g + 1 + n, [&](pair<int, int> a, pair<int, int> b) {
		return a.second < b.second;
	});
	g[0] = {-1, -1};

	for (int i = 1; i <= m; ++i) {
		int l = 0, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (g[mid].second <= h[i].second) l = mid;
			else r = mid - 1;
		}
		ma[h[i].first] += l;
		++s[l + 1];
	}
	for (int i = 1; i <= n; ++i) s[i] += s[i - 1];
	for (int i = 1; i <= n; ++i) ma[g[i].first] += s[i];

	int cnt = 0;
	for (int i = 0; i <= 200000; ++i) if (ma[i]) ++cnt;
	printf("%lld\n", cnt);
	for (int i = 0; i <= 200000; ++i) if (ma[i]) printf("%lld %lld\n", i, ma[i]);

	return 0;
}
```

---

## 作者：Ace_FutureDream (赞：0)

首先分析题目，题目要求只有一个地方能连续相同，并且只能由 $0$ 或 $1$ 组成。容易发现，可以找到一个分界点，例如 $0101010\ 010101$，中间空格处就是分界点，而两边都是规律交替的 $01$ 或者 $10$ 序列。

一开始我想二分分界点然后暴力求值，之后发现不行，因为答案没有单调性，所以只能先预处理出所需的代价再枚举分界点取 $\min$。

为了预处理，我开了两个数组 $\text{dp1}$ 和 $\text{dp2}$，存从前面，和从后面分别需要多少代价。但是后来发现不行，应该再存一维，表示开头为 $0/1$ 与结尾为 $0/1$ 的代价。然后注意一下判断 $n$ 的奇偶就能愉快的 AC 了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

char s[200010];
int a[200010];
int dp1[200010][2];
int dp2[200010][2];
signed main(){
	int n;
	cin>>n>>s+1;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(i%2==1){
			dp1[i][0]=dp1[i-1][0]+(s[i]=='1'?a[i]:0);
			dp1[i][1]=dp1[i-1][1]+(s[i]=='0'?a[i]:0);
		}else{
			dp1[i][0]=dp1[i-1][0]+(s[i]=='0'?a[i]:0);
			dp1[i][1]=dp1[i-1][1]+(s[i]=='1'?a[i]:0);
		}	
	}
	for(int i=n;i>=1;i--){
		if(i%2==(n%2==0)){
			dp2[i][0]=dp2[i+1][0]+(s[i]=='0'?a[i]:0);
			dp2[i][1]=dp2[i+1][1]+(s[i]=='1'?a[i]:0);
		}else{
			dp2[i][0]=dp2[i+1][0]+(s[i]=='1'?a[i]:0);
			dp2[i][1]=dp2[i+1][1]+(s[i]=='0'?a[i]:0);
		}	
	}

	int ans=1e18;
	if(n%2==1)		
		for(int i=1;i<n;i++)
			ans=min(ans,min(dp1[i][0]+dp2[i+1][1],dp1[i][1]+dp2[i+1][0]));	
	else
		for(int i=1;i<n;i++)
				ans=min(ans,min(dp1[i][0]+dp2[i+1][0],dp1[i][1]+dp2[i+1][1]));	
	cout<<ans;
	return 0;
}
/*
5
10 010
010 01
4
00 00
0 010
*/

```

---

## 作者：fuxiheng (赞：0)

### 题意
给你一个01串 $S$，每一个位置有一个代价 $c_i$ 可以把这一位取反，求最小代价使得整个串有且只有一个 $i$ 使得 $S_i=S_{i+1}$。
### 分析
一眼DP。设 $f_{i,j,k}$ 代表当前在第 $i$ 位，以 $j$ 结尾，合法状态为 $k$ 的最小代价。转移看代码应该能看懂。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 200005;
	const long long inf = 0x7fffffffffffffff / 2;
	char ch[MAXN];
	long long c[MAXN];
	long long f[MAXN][2][2];
	int main(){
		int n;
		scanf("%d%s", &n, ch + 1);
		for(int i = 1;i <= n;i++) scanf("%lld", &c[i]);
		if(ch[1] == '0'){
			f[1][0][0] = 0;
			f[1][0][1] = inf;
			f[1][1][0] = c[1];
			f[1][1][1] = inf;
		}
		else{
			f[1][0][0] = c[1];
			f[1][0][1] = inf;
			f[1][1][0] = 0;
			f[1][1][1] = inf;
		}
		for(int i = 2;i <= n;i++){
			if(ch[i] == '0'){
				f[i][0][0] = f[i - 1][1][0];
				f[i][0][1] = min(f[i - 1][0][0], f[i - 1][1][1]);
				f[i][1][0] = c[i] + f[i - 1][0][0];
				f[i][1][1] = c[i] + min(f[i - 1][0][1], f[i - 1][1][0]);
			}
			else{
				f[i][0][0] = c[i] + f[i - 1][1][0];
				f[i][0][1] = c[i] + min(f[i - 1][0][0], f[i - 1][1][1]);
				f[i][1][0] = f[i - 1][0][0];
				f[i][1][1] = min(f[i - 1][0][1], f[i - 1][1][0]);
			}
		}
		printf("%lld", min(f[n][0][1], f[n][1][1]));
		return 0;
	}
} 
signed main(){
	return Luo_ty::main();
}
```

---

## 作者：_Weslie_ (赞：0)

### 思路

一眼 $\tt dp$。（虽然听说前缀和也能做？）

我们设 $f_{i,0/1}$ 表示 $i$ 和 $i+1$ 位置都变为 $0/1$。

如果我们枚举 $i$，再去推，显然会超时。

不如看一组样例：

```
01011101
```

如果我们把 $3$ 和 $4$ 位置都变为 $0$，这样会：

```
01001010
```

如果把 $4$ 和 $5$ 位置都变为 $1$，发现：

```
01011010
```

会发现只有 $4$ 位置发生了变化。

同理，如果我们把 $3$ 和 $4$ 位置都变为 $1$，把 $4$ 和 $5$ 位置都变为 $0$，都满足这个定律。

推广后，发现在整个序列都满足该定律，即改变 $i-1$ 和 $i$ 位置为 $0$ 到改变 $i+1$ 和 $i$ 位置为 $1$ 只需要改变 $i$ 位置的代价。把 $0$ 和 $1$ 交换同理。

这样，我们只需要算出把 $1$ 和 $2$ 位置改变的代价，就可以 $\operatorname{O}(n)$ 的时间复杂度推出来了。

转移方程：
- 若 $s_i=0$，则 $f_{i,0}=f_{i-1,1}-c_i$，$f_{i,1}=f_{i-1,0}+c_i$；
- 若 $s_i=1$，则 $f_{i,0}=f_{i-1,1}+c_i$，$f_{i,1}=f_{i-1,0}-c_i$；

就结束了。

### Code

```
#include<bits/stdc++.h>
using namespace std;
long long f[200005][2];
int n,c[200005],a[200005],a1[200005],a0[200005];
string s;
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=0;i<s.length();i++){
		a[i+1]=s[i]-'0';
	}
	a0[1]=0;a0[2]=0;
	a1[1]=1;a1[2]=1;
	for(int i=3;i<=n;i++){
		if(a0[i-1]==0)a0[i]=1;
		else a0[i]=0;
		if(a1[i-1]==1)a1[i]=0;
		else a1[i]=1;
	}
	long long sum0=0,sum1=0;
	for(int i=1;i<=n;i++){
		if(a0[i]!=a[i])sum0+=c[i];
		if(a1[i]!=a[i])sum1+=c[i];
	}
	f[1][0]=sum0,f[1][1]=sum1;
	for(int i=2;i<n;i++){
		f[i][1]=f[i-1][0];
		f[i][0]=f[i-1][1];
		if(a[i]==0){
			f[i][1]+=c[i];
			f[i][0]-=c[i];
		}
		else{
			f[i][1]-=c[i];
			f[i][0]+=c[i];
		}
	}
	long long ans=9223372036854775807;
	for(int i=1;i<n;i++){
		if(f[i][1]<ans)ans=f[i][1];
		if(f[i][0]<ans)ans=f[i][0];
	}
	cout<<ans;
	return 0;
}
```

---

