# [ABC104D] We Love ABC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc104/tasks/abc104_d

文字列 $ T $ の *ABC 数* とは、以下の条件をすべて満たす整数の組 $ (i,\ j,\ k) $ の個数です。

- $ 1\ <\ =\ i\ <\ j\ <\ k\ <\ =\ |T| $（$ |T| $ は $ T $ の長さ）
- $ T_i\ = $ `A`（$ T_i $ は $ T $ の先頭から $ i $ 番目の文字）
- $ T_j\ = $ `B`
- $ T_k\ = $ `C`

例えば、$ T\ = $ `ABCBC` のとき、条件をすべて満たす組 $ (i,\ j,\ k) $ は $ (1,\ 2,\ 3),\ (1,\ 2,\ 5),\ (1,\ 4,\ 5) $ の $ 3 $ 個であるため、$ T $ の ABC 数は $ 3 $ です。

文字列 $ S $ が与えられます。$ S $ のそれぞれの文字は `A`, `B`, `C`, `?` のいずれかです。

$ S $ に含まれる `?` の個数を $ Q $ とします。$ S $ に含まれる `?` をそれぞれ `A`, `B`, `C` のいずれかに置き換えることで $ 3^Q $ 通りの文字列が作られます。これらの文字列すべての ABC 数の和を求めてください。

ただし、この和は非常に大きくなりうるため、和を $ 10^9\ +\ 7 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 3\ <\ =\ |S|\ <\ =\ 10^5 $
- $ S $ のそれぞれの文字は `A`, `B`, `C`, `?` のいずれかである。

### Sample Explanation 1

この場合、$ Q\ =\ 2 $ であり、`?` をそれぞれ `A`, `B`, `C` のいずれかに置き換えることで $ 3^Q\ =\ 9 $ 通りの文字列が作られます。これらの文字列それぞれの ABC 数を以下に示します。 - `AAAC`: $ 0 $ - `AABC`: $ 2 $ - `AACC`: $ 0 $ - `ABAC`: $ 1 $ - `ABBC`: $ 2 $ - `ABCC`: $ 2 $ - `ACAC`: $ 0 $ - `ACBC`: $ 1 $ - `ACCC`: $ 0 $ これらの和は $ 0\ +\ 2\ +\ 0\ +\ 1\ +\ 2\ +\ 2\ +\ 0\ +\ 1\ +\ 0\ =\ 8 $ であり、$ 8 $ を $ 10^9\ +\ 7 $ で割った余りである $ 8 $ を出力します。

### Sample Explanation 2

$ Q\ =\ 0 $ のときは、$ S $ 自体の ABC 数を $ 10^9\ +\ 7 $ で割った余りを出力します。この文字列は問題文中で例として挙げたものと同じであり、その ABC 数は $ 3 $ です。

### Sample Explanation 3

この場合、$ 3^Q $ 通りの文字列すべての ABC 数の和は $ 2291979612924 $ であり、これを $ 10^9\ +\ 7 $ で割った余りである $ 979596887 $ を出力します。

## 样例 #1

### 输入

```
A??C```

### 输出

```
8```

## 样例 #2

### 输入

```
ABCBC```

### 输出

```
3```

## 样例 #3

### 输入

```
????C?????B??????A???????```

### 输出

```
979596887```

# 题解

## 作者：Composite_Function (赞：6)

$$\text{思路}$$

裸计数 DP 问题，很好解决。

状态：`dp[i][j]` 表示第 $i$ 位字符为 $j$ 的记录数量（注意若 $s[i]\not = j$ 则继承上一位）。

> 注：
> - 若 $j = 0$ 表示字符 `?`
> - 若 $j = 1$ 表示字符 `A`
> - 若 $j = 2$ 表示字符 `B`
> - 若 $j = 3$ 表示字符 `C`

初始值：`dp[0][0] = 1`

递推方程：有 `?` 时则为原来的三倍，反之只继承原来的值。（具体细节见代码）

------------

$$\text{代码}$$

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10, mod = 1e9 + 7;
int dp[N][4]; char c[N];
signed main()
{
	cin >> c, dp[0][0] = 1;
	for (int i = 0; c[i]; ++i) {
		if (c[i] == '?') {
			dp[i + 1][0] = dp[i][0] * 3 % mod;
			dp[i + 1][1] = (dp[i][1] * 3 + dp[i][0]) % mod;
			dp[i + 1][2] = (dp[i][2] * 3 + dp[i][1]) % mod;
			dp[i + 1][3] = (dp[i][3] * 3 + dp[i][2]) % mod;
		}
		else {
			for (int j = 0; j <= 3; ++j) dp[i + 1][j] = dp[i][j];
			if (c[i] == 'A') dp[i + 1][1] = (dp[i][1] + dp[i][0]) % mod;
			if (c[i] == 'B') dp[i + 1][2] = (dp[i][2] + dp[i][1]) % mod;
			if (c[i] == 'C') dp[i + 1][3] = (dp[i][3] + dp[i][2]) % mod;
		}
	}
	cout << dp[strlen(c)][3] << endl;
	return 0;
}
```

---

## 作者：I_am_sb___ (赞：5)

题意还是很简洁的，我们直接来看思路：

考虑没有“?”字符的情况，我们可以考虑统计中点的情况，显然每一个“B”字符的贡献为 $ sum_{A}\times sum_{C} $。

但是现在又多出了一个“?”字符该如何解决呢，我们发现每一个“?”都有三种情况，延续之前统计每个中点的贡献的思路，先考虑“?”被当成“A”的情况，这种情况多出的贡献即为 $ cnt\times sum_{C}\times 3^{cnt-1} $（$cnt$ 代表“?”的个数，下同），这可以理解为从“?”中选出一个作为“A”，其他都是贡献三种情况。

显然当“?”作为“C”时与作为“A”是时同理，贡献为 $ cnt\times sum_{c}\times 3^{cnt-1}$。

还有一种两边都为“?”的情况，这就可以理解为有两个“?”被确定了情况，贡献为 $ sum_{cnt_{front}}\times sum_{cnt_{behind}}\times 3^{cnt-2} $，我们总共只需要统计这四种贡献即可。

那这道题结束了吗？~~显然没有~~。我们发现，在统计中间字符的思路中，我们少考虑了一种情况，即为“?”作为中间字符的情况，当然这种情况不会有任何附加的思维难度，只需要将上式中的 $cnt--$ 即可。

code：
```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
#include<string>
#include<cmath>
#include<queue>
#include<vector>
#include<map>
#include<set>

#define int long long

using namespace std;

inline int read(){
	int s=0,w=1;
	char c=getchar();
	while(!isdigit(c)) {if(c=='-')w=-1;c=getchar();}
	while(isdigit(c)) s=s*10+(c^48),c=getchar();
    return s*w;
}

inline void write(int x){
    if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

const int mod = 1e9 + 7;

int n;
int cnta , cntb , cntc , divide = 1;
string s;

signed main(){
	cin >> s;
	n = s.size();
	for(int i = 0 ; i < n ; ++ i)
	{
		if(s[i] == 'A') cnta = (cnta + divide) % mod;
		else if(s[i] == 'B') cntb = (cntb + cnta) % mod;
		else if(s[i] == 'C') cntc = (cntc + cntb) % mod;
		else
		{
			cntc = (cntc * 3 + cntb) % mod;
			cntb = (cntb * 3 + cnta) % mod;
			cnta = (cnta * 3 + divide) % mod;
			divide = divide * 3 % mod;
		}
	}
	write(cntc);
	return 0;
}
```

---

## 作者：explorerxx (赞：5)

第一篇题解指出,这道题可以用DP或者计数来做
这里分享一下计数做法

看一个一般例子   
 $ ABCC$

它一共能够产生多少个ABC子串?   
显然是2个,这个B和前面的A作为一组,然后分别和后边的两个C组成ABC子串。

如果前面有两个A,即AABCC,那么B就分别和前面的两个A为一组，又分别与后边的两个C组成一组,最终得到四组ABC子串。

这里就产生了思路,对于一个位置上的B,它能产生的对答案的贡献就是前边的A的数量乘上后边的C的数量(乘法原理)

假如这道题没有"?"的参与,统计答案只需要记录一个A的前缀和$numa[i]$,以及一个C的后缀和$numc[i]$。枚举序列中的每个B，它产生的贡献就是    
$ 
 numa[i]* numc[i]
$。

但是很不巧的是这道题有"?"存在，不过问题不大

根据题目意思,一个"?"可以对序列的存在做扰动,也就是说它的变化能使序列变得不同。也就是说,每一个问号都能使得一个序列变成3个。

那么$totw$个问号就能够使得序列变成 $ 3^{totw}$个,所以它能够使得上述求得的原先实际存在的ABC贡献的答案变成$ numa[i] * numc[i] * 3^{totw}$个。

当然问号的存在不仅影响了序列的独立性,不仅是让原先的序列有一个不同的标记,同时由于"?"的变形,它也会影响子串中ABC的数量。

所以现在需要考虑一下"?"的位置对于实际存在的子串数量的贡献,分别来讨论。假如第i个B后面的"?"是C的话，那么它可以使得答案多一个   
$ 1* numa[i]* 3^{totw-1}$(因为少了一个"?"，所以说"?"的数量变为$totw-1$)   
 如果记这个B的后面的?的数量为$\_numw[i]$的话,那么每一个经过这样的计算,总和起来的贡献就是   
 $\  \_numw[i]*numa[i]*3^{totw-1}$。

同理,对于第i个B前面的"?",记$numw[i]$为i前面的?的数量，它们也可以变成A，所贡献的答案就是 $ nmuw[i]*numc[i]*3^{totw-1}$。

然后还要考虑两边的A和C都是"?"产生的情况(显然我们刚刚累积的贡献并没有包括这个贡献),如果第$i$个B前面的某个"?"变为A,然后后边的某个"?"变为C，产生的贡献就是$ 1* 3^{totw-2}$,现在考虑左边的所有"?"都变一次A，那么贡献就是$ numw[i]*3^{totw-2}$,再考虑右边的所有"?"都变一次C，还是乘法原理,得到贡献最后就是   
$ numw[i]*3^{totw-2}*\_numw[i]$。

然而刚刚我们只讨论了中间是一个确定的B的情况,假如中间的这个B是由"?"变过来的,那么上述的四个讨论依然成立,只是由于这个B是"?"变过来的,所以说每一步的totw要再多减个1。

多讨论一个细节,上述会出现$ 3^{totw-1} $或$ 3^{totw-2}$或$3^{totw-3} $,$totw$减去这几个数得大于等于0,出现负数就会出现错误,所以$totw-x$要与$0$取$max$。

最终只要我们枚举所有位置的B和"?"计算上述4个贡献,就可以得到答案,复杂度$O(n)$

代码如下


------------

```cpp
#include<bits/stdc++.h>
#define reg register
typedef long long ll;
using std::max;
inline int qr(){
	int x=0,f=0;char ch=0;
	while(!isdigit(ch)){f|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return f?-x:x;
}
const int mod=1e9+7;
const int maxn=1e5+100;
char s[maxn];
int n;
ll ans;
int numa[maxn],numc[maxn],totw,numw[maxn],_numw[maxn];//前缀a,后缀c,总数？,前后缀？ 
ll qkpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return ans%mod;
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(reg int i=1;i<=n;i++){
		numa[i]=numa[i-1];
		numw[i]=numw[i-1];
		if(s[i]=='?'){
			totw++;
			numw[i]++;
		}
		if(s[i]=='A'){
			numa[i]++;
		}
	}
	for(reg int i=n;i>=1;i--){
		_numw[i]=_numw[i+1];numc[i]=numc[i+1];
		if(s[i]=='?') _numw[i]++;
		if(s[i]=='C') numc[i]++;
	}

	for(reg int i=1;i<=n;i++){	
		
		if(s[i]=='B'){
			ans=(ans+(ll)numa[i]%mod*numc[i]%mod*qkpow(3,totw)%mod)%mod;//前A,后C 
			ans=(ans+(ll)numa[i]%mod*_numw[i]%mod*qkpow(3,max(totw-1,0))%mod)%mod;//前A后?
			ans=(ans+(ll)numw[i]%mod*numc[i]%mod*qkpow(3,max(totw-1,0))%mod)%mod;//前?后C
			ans=(ans+(ll)numw[i]%mod*_numw[i]%mod*qkpow(3,max(0,totw-2))%mod)%mod;//前?后? 
		}
		if(s[i]=='?'){
			ans=(ans+(ll)numa[i]%mod*numc[i]%mod*qkpow(3,max(totw-1,0))%mod)%mod;//前A,后C 
//			printf("%d ",ans);
			ans=(ans+(ll)numa[i]%mod*_numw[i+1]%mod*qkpow(3,max(0,totw-2))%mod)%mod;//前A后?
//			printf("%d ",ans);
			ans=(ans+(ll)numw[i-1]%mod*numc[i]%mod*qkpow(3,max(0,totw-2))%mod)%mod;//前?后C	
//			printf("%d ",ans);
			ans=(ans+(ll)numw[i-1]%mod*_numw[i+1]%mod*qkpow(3,max(0,totw-3))%mod)%mod;//前?后? 	
//			printf("%d\n",ans);
		}
	}
	printf("%d",ans);
	return 0;
}
```


------------




---

## 作者：星之尘埃 (赞：5)

这道题可以用DP或计数来做。
对于有m个'?'的字符串S，我们要把它填满，显然一共有$3^{m}$种填法。

因为不同的字符串是不同的答案，我们发现每出现一个‘？’号，答案会变为原基础的三倍。

所以具体的做法是，定义dp[i][j]表示前i个字符中形成了'ABC'的前j项的子串数量。首先我们从1~n枚举每个字符，如果该字符是'?',则把上一个答案乘3。
```cpp
if(s[i]=='?')//首先判断是否是?号,如果是,在上一个点的每种状态的基础上乘3 
    for(re int j=0; j<4 ;j++)
    dp[i+1][j] = (dp[i+1][j](dp[i[j]*3));
 else 
    for(re int j=0; j<4 ;j++)
    dp[i+1][j]=(dp[i][j]+dp[i+1][j]);//否则继承上一个点的状态 
```

否则就根据当前字符来进行更新。
```cpp
if(s[i] == 'A' )
dp[i+1][1]=(dp[i+1][1] + dp[i][0]);
if(s[i] == 'B' )
dp[i+1][2] = (dp[i+1][2] + dp[i][1]);
if(s[i] == 'C')
dp[i+1][3] = (dp[i+1][3] + dp[i][2]);
```



最后输出答案就是dp[N][3]。

具体代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define r(i,a,b) for(register int i=a;i<=b;++i)
#define mem(d) memset(d,0,sizeof(d))
#define ul unsigned long long
#define IsDigit(c) ('0' <= (c) && (c) <= '9')
#define re register
#define mod 1000000007
using namespace std;
const int N=1e5+10;
int n;
char s[N];
ll dp[N][5];
int main()
{
//	freopen("abc.in","r",stdin);
//	freopen("abc.out","w",stdout);
    scanf("%s",s+1);
    n=strlen(s+1);
    dp[1][0] = 1;
    for(re int i=1; i<=n ;i++)
	{
		if(s[i]=='?')//首先判断是否是?号,如果是,在上一个点的每种状态的基础上乘3 
        	for(re int j=0; j<4 ;j++)
            	dp[i+1][j] = (dp[i+1][j]+(dp[i][j]*3))%mod;
        else 
            for(re int j=0; j<4 ;j++)
				dp[i+1][j]=(dp[i][j]+dp[i+1][j])%mod;//否则继承上一个点的状态 
	// 接下来判断其他字符，注意如果是？号的话,它可以是ABC中任意一个，所以三种状态都要更新
	 if(s[i] == '?')
	  {
	 	dp[i+1][1] = (dp[i+1][1] + dp[i][0])%mod;
	 	dp[i+1][2] = (dp[i+1][2] + dp[i][1])%mod;
	 	dp[i+1][3] = (dp[i+1][3] + dp[i][2])%mod;
	  } 
        if(s[i] == 'A' )
			dp[i+1][1]=(dp[i+1][1] + dp[i][0])%mod;
        if(s[i] == 'B' )
			dp[i+1][2] = (dp[i+1][2] + dp[i][1])%mod;
        if(s[i] == 'C')
			dp[i+1][3] = (dp[i+1][3] + dp[i][2])%mod;
    }
    printf("%lld\n",dp[n+1][3]);
    return 0;
}
```


---

## 作者：一只书虫仔 (赞：4)

#### Description

> 给定一个字符串 $S$，求将 `?` 替换后的所有字符串中有多少个长度为三的子序列为 `ABC`，其中 $S$ 中的 `?` 可以换成 `A` / `B` / `C`。

#### Solution

考虑 dp，设 $f_{i,1/2/3}$ 为截止到第 $i$ 个字符有多少个子序列为 `A` / `AB` / `ABC`。

设 $g$ 为 $S$ 有多少个 `?`，则有转移：

- 当 $S_i=$ `A`，`A` 的情况可以进行更新：
	- $f_{i,1}=f_{i-1,1}+3^{g}$；
    - $f_{i,2}=f_{i-1,2}$；
    - $f_{i,3}=f_{i-1,3}$；
- 当 $S_i=$ `B`，`AB` 的情况可以进行更新：
	- $f_{i,1}=f_{i-1,1}$；
    - $f_{i,2}=f_{i-1,2}+f_{i-1,1}$；
    - $f_{i,3}=f_{i-1,3}$；
- 当 $S_i=$ `C`，`ABC` 的情况可以进行更新：
	- $f_{i,1}=f_{i-1,1}$；
    - $f_{i,2}=f_{i-1,2}$；
    - $f_{i,3}=f_{i-1,3}+f_{i-1,2}$；
- 当 $S_i=$ `?`，则一共 $3^{g}$ 种情况就划分为了三种，加 `A` 加 `B` 加 `C`，则 `A` `AB` `ABC` 三种子序列的转移量也从上一种情况除以 $3$ 得到（可以感性理解为有 $1/3$ 的概率得到这个子序列想要的字符），那剩下的 $2/3$ 就是不符合要求的，直接从第 $i-1$ 项转移过来即可，即为：
	- $f_{i,1}=\frac{f_{i-1,1}+3^{g}} 3+\frac{2f_{i-1,1}} 3=f_{i-1,1}+3^{g-1}$；
    - $f_{i,2}=\frac{f_{i-1,2}+f_{i-1,1}} 3+\frac{2f_{i-1,2}} 3=f_{i-1,2}+\frac{f_{i-1,1}}3$；
    - $f_{i,3}=\frac{f_{i-1,3}+f_{i-1,2}} 3+\frac{2f_{i-1,3}} 3=f_{i-1,3}+\frac{f_{i-1,2}}3$。
    
最后输出 $f_{n,3}$ 即可。

---

## 作者：zhang_kevin (赞：2)

# 题意简述
给定一个字符串 $\verb!s!$，只包含 $\verb!A,B,C,?!$ 这 $4$ 个字符， 其中 $\verb!?!$ 表示 $\verb!A,B,C!$ 中的任意一个。问在所有可能的只包含 $\verb!A,B,C!$ 的字符串中，总共有多少长度为 $3$ 的子序列是 $\verb!ABC!$。

# 解题思路

这道题可以用 $\verb!DP!$ 来做。

令 $\mathit{dpA}_{i}$、$\mathit{dpB}_{i}$、$\mathit{dpc}_{i}$ 分别表示前 $i$个字符中形成 $\verb!A,B,C!$ 的子串数量。

初始化 $\mathit{dpA}_{0} = 1$。

如果当前字符是 $\verb!?!$，应直接乘上 $2$ 再加上 $dp$... $_i$ 更新状态；如果不是，就普通加减更新。最后根据字符串更新即可。

# AC代码

```cpp
#include<iostream>
#define int __int128
using namespace std;

inline void write(int x){
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}

const int mod = 1e9 + 7;
int dpA[100001], dpB[100001], dpC[100001], dp[100001];

signed main(){
	
	string s;
	cin >> s;
	int len = s.length();
	
	dpA[0] = 1;
	
	for(int i = 0; i < len; i++){
		
		dpA[i+1] += dpA[i];
		dpB[i+1] += dpB[i];
		dpC[i+1] += dpC[i];
		dp[i+1] += dp[i];
		
		if(s[i] == 'A'){
			
			dpB[i+1] += dpA[i];
			
		}else if(s[i] == 'B'){
			
			dpC[i+1] += dpB[i];
			
		}else if(s[i] == 'C'){
			
			dp[i+1] += dpC[i];
			
		}else{
			
			dpA[i+1] += 1ll * dpA[i] * 2 % mod;
			dpB[i+1] += 1ll * dpB[i] * 2 % mod;
			dpC[i+1] += 1ll * dpC[i] * 2 % mod;
			dp[i+1] += 1ll * dp[i] * 2 % mod;
			dpB[i+1] += dpA[i];
			dpC[i+1] += dpB[i];
			dp[i+1] += dpC[i];
			
	    }
	    
	}
	
	write(dp[len]%mod), puts("");
	
	return 0;
	
}
```

---

## 作者：Nightingale_OI (赞：2)

### 大意

给定一个仅由“ A ”、“ B ”、“ C ”和“ ? ”组成的字符串（设长度为 $ n $ ，含有 $ m $ 个“ ? ”）。

每个“ ? ” 可以变为“ A ”、“ B ”、“ C ”中任意一个字符，所有“ ? ”变化完后就一共有 $ 3^m $ 种结果串。

求每个结果串的子序列“ ABC ”个数和。

结果对 $ 10^9+7 $ 取模。

### 思路

考虑枚举子序列中“ B ”的位置，再看其左边有多少个符合要求的“ A ”，右边有多少符合要求的“ C ”。

分类讨论“ A ”与“ C ”是否由问号变化来统计即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
const int mo=1e9+7;
const int maxn=101010;
int al[maxn],wl[maxn],le;
int cr[maxn],wr[maxn],ri;
char st[maxn];
int ksm(int x,int p){
    if(p==0)return 1;
    if(p==-1)return 0;
    int num=ksm(x,p/2);
    num=1ll*num*num%mo;
    if(p&1)num=1ll*num*x%mo;
    return num;
}
int main(){
    scanf("%s",st+1);
    n=strlen(st+1);
    f(i,1,n)al[i]=al[i-1]+(st[i]=='A');
    f(i,1,n)wl[i]=wl[i-1]+(st[i]=='?');
    g(i,n,1)cr[i]=cr[i+1]+(st[i]=='C');
    g(i,n,1)wr[i]=wr[i+1]+(st[i]=='?');
    f(i,1,n)if(st[i]=='B' || st[i]=='?'){
        le=(1ll*al[i-1]*ksm(3,wl[i-1])%mo+1ll*wl[i-1]*ksm(3,wl[i-1]-1)%mo)%mo;
        ri=(1ll*cr[i+1]*ksm(3,wr[i+1])%mo+1ll*wr[i+1]*ksm(3,wr[i+1]-1)%mo)%mo;
        s=(s+1ll*le*ri%mo)%mo;
    }
    printf("%d\n",s);
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15246614.html)

$\texttt{upd~on~2021/9/13:}$ 更改了部分 $\LaTeX$。

## 题目大意

给你一个字符串，只包含 `A,B,C,?`， 其中 `?` 表示 `A,B,C` 中的任意一个，问在所有可能的 `A,B,C` 的字符串中，总共有多少长度为 $3$  的子序列是 <'A', 'B', 'C'>。

## 题目分析

考虑动态规划。

**令 $dp[i][j]$ 表示前 $i$ 个字符中形成 `A,B,C` 的前 $j$ 项的字串数量。**

其中 $0\le i\le 3$，**当 $i=0$ 时无实际意义，只用来计数。**

初始化 $dp[1][0]\gets1$。

如果当前字符是 `?`，那么根据乘法原理，我们直接乘上 $3$ 更新状态：

```cpp
for(register int j=0;j<=3;j++)
{
	dp[i+1][j]=(dp[i+1][j]+dp[i][j]*3)%mod;//乘上 3
}
```

如果不是，那么普通加减即可：

```cpp
for(register int j=0;j<=3;j++)
{
	dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
}
```

最后根据字符更新即可，由于洛谷插入代码的缩进有一点问题，一行一行的修改过于麻烦，代码可以到 $\rm blog$ 里去看看 $\texttt{qwq}$。

---

## 作者：Erica_N_Contina (赞：0)

# [ABC104D] We Love ABC

## 题面整理

给你一个字符串 $S\ (3 \leq |S|\leq 10^5)$，只包含 `A`, `B`, `C`, `?`，其中`?` 表示 `A`, `B`, `C` 中的任意一个，问在所有可能的 `A`, `B`, `C` 的字符串中，总共有多少长度为 $3$ 的子序列是 <`A`, `B`, `C`>。答案对 $10 ^ 9 + 7$ 取模。

## 子序列

**子序列的定义：子序列就是在原来序列中找出一部分组成的序列（子序列不一定连续）**。

> 在数学中，某个序列的子序列是从最初序列通过去除某些元素但不破坏余下元素的相对位置（在前或在后）而形成的新序列。

## 思路

我们从 $1\sim n$ 枚举字符串的每一个字符，枚举 <`A`, `B`, `C`> 的中点也就是 `B`。

我们首先预处理出来几个数组/变量：

- $preA_i$ 记录第 $i$ 个字符前一共有多少个 `A`。

- $nxtC_i$ 记录第 $i$ 个字符后一共有多少个 `C`。

- $cnt$ 记录字符串中 `?` 的个数。

- $preQ_i , nxtQ_i$ 分别记录第 $i$ 个字符前一共有多少个 `?`，第 $i$ 个字符后一共有多少个 `?`。

（注释：以上“第 $i$ 个前/后”均不包括第 $i$ 个）

### 1.假设我们枚举到了一个 `B`

这里我们继续分类讨论。

1. **没有 `?` 字符的情况**

我们可以考虑统计中点的情况，显然第 $i$ 位的 `B` 字符的贡献为 $preA_{i}\times  nxtC_{i}$。这样的话我们一个 `?` 也没有使用，排列组合后 $cnt$ 个 `?` 可以产生 $3^{cnt}$ 种情况，那么最终的贡献就是 $preA_{i}\times  nxtC_{i}\times3^{cnt}$。

2. **有 `?` 字符的情况**

但是现在又多出了一个 `?` 字符该如何解决呢，我们发现每一个 `?` 都有三种情况，延续之前统计每个中点的贡献的思路。

- 考虑 `?` 被当成 `A` 的情况，这种情况多出的贡献即为 $preQ_i\times nxtC_{i}\times 3^{cnt-1}$，这可以理解为从 `B` 前面的任意一个 `?` 中选出一个作为 `A`，其他的 `?` 可以在 `A`，`B`，`C` 中任意选取并且组成不同的情况。

- 当 `?` 作为时，与 `C` 作为 `A` 是时同理，贡献为 $ nxtQ_i\times preA_{i}\times 3^{cnt-1}$。

- 两边都为 `?` 的情况，这就可以理解为有两个 `?` 被确定了下来，贡献为 $preQ_i\times nxtQi\times 3^{cnt-2}$，我们总共只需要统计这四种贡献即可。

### 2.假设我们枚举到了一个 `?`

`?` 作为中间字符的情况，我们只需要将其看成是 `B` 即可。当然这种情况还是分上面的几种情况讨论，只需要将上式中的 $cnt$ 换成 $cnt-1$ 即可，这里就不再赘述。

### 一个可能产生的疑惑

> 请解说一下 $cnt\times nxtC_{i}\times 3^{cnt-1}$ 等式子中的 $3^{cnt-1}$ 是什么意思吖？

我们考察以下实例：

```Plain Text
A??C
---
ABCC
ABAC
ABBC
```


对我们枚举到第 $i=2$ 个字符时（$i$ 从 $1$ 开始编号），我们发现只要前面有个确定的 `A`，后面有个确定的 `C`，那么多余的 `?` 无论取什么都可以。但 `?` 取不同字符时属于不同的情况，因此运用排列组合的乘法原理，我们就有了 $3^{cnt-1}$ 这个式子。

**My code**

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long//记得开LL
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;

const int N=2e5+5;
const int M=1e5;
const int Mod=1e9+7;
const int INF=1e5;
int cnta=0,cntq=0,cntc,cntqq,ans,cnt;
int prea[N],preq[N],nxtc[N],nxtq[N];

int kpow(int c,int k) {	//c^k %p
	int res=1;
	while(k) {
		if(k&1) {
			res=res*c%Mod;	//注意只有1句在里面！
		}
		k>>=1;	//不要写反了！
		c=c*c%Mod;
	}
	return res;
}

signed main(){
	char s[N];
	scanf("%s",s);
	
	for(int i=0;i<strlen(s);i++){
		prea[i]=cnta;
		preq[i]=cntqq;
		if(s[i]=='A')cnta++;
		if(s[i]=='?')cnt++,cntqq++;
	}
	cntqq=0;
	for(int i=strlen(s)-1;i>-1;i--){
		nxtc[i]=cntc;
		nxtq[i]=cntqq;
		if(s[i]=='C')cntc++;
		if(s[i]=='?')cntqq++;
	}
	
	
	for(int i=1;i<strlen(s);i++){
		if(s[i]=='B'){
			ans+=prea[i]*nxtc[i]*kpow(3,cnt)%Mod;
			ans+=preq[i]*nxtc[i]*kpow(3,max(0ll,cnt-1))%Mod;
			ans+=nxtq[i]*prea[i]*kpow(3,max(0ll,cnt-1))%Mod;//注意负次幂情况!
			ans+=preq[i]*nxtq[i]*kpow(3,max(0ll,cnt-2))%Mod;
		}if(s[i]=='?'){
			ans+=prea[i]*nxtc[i]*kpow(3,max(0ll,cnt-1))%Mod;
			ans+=preq[i]*nxtc[i]*kpow(3,max(0ll,cnt-1-1))%Mod;
			ans+=nxtq[i]*prea[i]*kpow(3,max(0ll,cnt-1-1))%Mod;
			ans+=preq[i]*nxtq[i]*kpow(3,max(0ll,cnt-2-1))%Mod;
		}
	}
	cout<<ans%Mod<<endl;
	return 0;
}

```


## 注意

- 注意负次幂情况！！

- 开 `long long`


---

## 作者：_Kamisato_Ayaka_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc104_d)

# 思路

用计数 dp 的思想，先预处理所有的可能，节省了每次用快速幂的时间。分别统计字母 ```A``` 和 ```C``` 和 ```?``` 的个数，然后用方程转移，将符合条件的 ```?``` 替换成字母 ```B```，ans 记录每次枚举的方案。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9+7;
const int N = 1e5+10;
char s[N];
int arr[N],pa[N][2],pb[N][2],ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>s+1;
	int len=strlen(s+1);
	arr[0]=1;
	for(int i=1;i<=len;i++)
		arr[i]=(arr[i-1]*3)%mod;//预处理快速幂 
	for(int i=1;i<=len;i++){
		pa[i][0]=pa[i-1][0];
		pa[i][1]=pa[i-1][1];
		if(s[i]=='A') pa[i][1]++;
		if(s[i]=='?') pa[i][0]++;
	}//统计A和?
	for(int i=len;i>=1;i--){
		pb[i][0]=pb[i+1][0];
		pb[i][1]=pb[i+1][1];
		if(s[i]=='C') pb[i][1]++;
		if(s[i]=='?') pb[i][0]++;
	}//统计C和? 
	for(int i=1,p;i<=len;i++)
	{ 
		if(s[i]=='B' || s[i]=='?'){//枚举B 
			p=((pa[i-1][1]*arr[pa[i-1][0]])%mod+(pa[i-1][0]*arr[pa[i-1][0]-1])%mod)%mod;//符合的?替换A 
			p=(p*((pb[i+1][1]*arr[pb[i+1][0]])%mod+(pb[i+1][0]*arr[pb[i+1][0]-1])%mod)%mod)%mod;//符合的?替换C 
			ans=(ans+p)%mod;//统计答案 
		}
	}
	cout<<ans<<endl;//完结撒花 
	return 0;
}
```


---

