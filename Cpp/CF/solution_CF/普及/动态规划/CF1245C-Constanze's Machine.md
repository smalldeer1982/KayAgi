# Constanze's Machine

## 题目描述

$Constanze$是全村最聪明的女孩，但是她视力不好

一天，她发明了一台神奇的机器。当你念字母时，机器会把它们写刻在一张纸上。举个例子，如果你按这个顺序念“$c$”、“$o$”、“$d$”和“$e$”，那么机器就会在纸上写“$code$”。多亏了这台机器，她终于不用眼镜就能写信了

但是，她的朋友$Akko$决定对她开个玩笑，$Akko$改了机器，如果你念$w$，它会写$uu$而不是$w$，如果你念$m$，它会写$nn$而不是$m$。由于$Constanze$视力不好，她不知道$Akko$做了什么

其他字母和以前一样：如果你念的是“$w$”,“$m$”以外的字母，机器就会把它原封不动地写在纸上

第二天，我在邮箱里收到了一封信。但我看不懂，我想这应该是$Constanze$用她的机器写的。但既然我知道$Akko$做了什么，我就可以把$Constanze$的机器写的话变成我原本可能得到的信息。

但是因为我很菜，所以我要向你求助。你需要告诉我告诉我所有原本可能得到的信息有多少种。

由于答案可能很大，请输出答案对$10^9+7$取模后的结果。

如果没有一个字符串经过$Constanze$的机器后能得到我的结果，请输出$0$

## 说明/提示

对于第一个样例，可能的字符串如下：“$ouokarin$”、“$ouokarim$”、“$owokarim$”和“$owokarin$”

第二个样例只有一个：“$banana$”

对于第三个样例，可能的字符串如下：“$nm$”、“$mn$”和“$nnn$”

在最后一个样例中，没有任何字符串可以被机器转换成“$amanda$”，因为机器不会写下“$m$”。

## 样例 #1

### 输入

```
ouuokarinn
```

### 输出

```
4
```

## 样例 #2

### 输入

```
banana
```

### 输出

```
1
```

## 样例 #3

### 输入

```
nnn
```

### 输出

```
3
```

## 样例 #4

### 输入

```
amanda
```

### 输出

```
0
```

# 题解

## 作者：Ludo (赞：5)

## $Part$ $I.$ 题意简述

有个文章，其中的$w$，变成了$uu$；其中的$m$，变成了$nn$。

现在要复原这篇文章，请问有多少种不同的？答案模$10^9+7$

## $Part$ $II.$ 思考细节

首先，样例四不存在一个合法的原文，因为**其中的$m$一定不会出现，在翻译过程中一定会被转为$nn$。**

### 即不合法输出$0$。

第二，只要能够数出连续的$u$，连续的$n$。便可以进行统计了。

**数的方法**

```cpp
对于每一个字串中的字符c
	若是n，（连续的u必被截断）
		对连续的u进行统计，u清零。
		n加一
	若是u，（连续的n必被截断）
		对连续的n进行统计，n清零。
		u加一
	若是其他，（连续的n（或u）必被截断）
		对u，n进行统计，u，n清零。

循环外，由于可能没有东西把最后可能存在的连续的u，n截断，故需要再统计。
```

第三，统计的方法可以是**dp或是递推**。我只会递推的方法。

下表展示了一些连续的字符串与其方案数的关系：

| 字符串 | 方案数 |
| :----------: | :----------: |
| uu | 2 |
| uuu | 3 |
| uuuu | 5 |
| uuuuu | 8 |
| uuuuuu | 13 |

从表看出，这些连续的$u$（或$n$）构成了一个**斐波那契数列**。

特别地，**单一字符u或n，不对方案数进行任何贡献**。

最后，根据**乘法原理**，可以把**这些方案数乘起来**，得到最后答案。

例如样例一中的“$ouuokarinn$”，$uu$的方案数是$2$，$nn$的方案数也是$2$，乘起来得到$4$。

## $Part$ $III.$ 代码

由于本人的码风比较**丑**，所以**斟酌着看看**就好。

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int modulo=1e9+7;
string s;int n,u;long long ans,fib[100004];bool flag;
int main(void)
{
	cin>>s;ans=1;flag=true;
	fib[1]=1;fib[2]=1;
	for (int i=3;i<=100002;i++)
	{
		fib[i]=(fib[i-1]+fib[i-2])%modulo;
	}
	for (int i=0;i<s.size();i++)
	{
		if (s[i]=='n')
		{
			n++;
			if (u>1) flag=true,ans*=fib[u+1],ans%=modulo;
			u=0;
		}
		else if (s[i]=='u')
		{
			u++;
			if (n>1) flag=true,ans*=fib[n+1],ans%=modulo;
			n=0;
		}
		else if (s[i]!='m'&&s[i]!='w')
		{
			if (n>1) flag=true,ans*=fib[n+1],ans%=modulo;
			n=0;
			if (u>1) flag=true,ans*=fib[u+1],ans%=modulo;
			u=0;
		}
		else
		{
			cout<<0;
			return 0;
		}
	}
	if (u>1) flag=true,ans*=fib[u+1],ans%=modulo;
	if (n>1) flag=true,ans*=fib[n+1],ans%=modulo;
	if (flag==true) cout<<ans;
    else cout<<0; 
}

```


---

## 作者：andyli (赞：4)

考虑使用动态规划，定义$dp(i)$表示以$i$结尾字符串的方案数。若末尾$2$字符为nn或uu，方案数当$i=2$为$2$，否则为$dp(i-1)+dp(i-2)$，若末尾$2$字符不为nn且不为uu，则方案数为$dp(i-1)$，边界条件为$dp(0)=0, dp(1)=1$。 

注意若原字符串中出现m或w即为不合法，输出$0$,另外dp过程中使用记忆化搜索并对$10^9+7$取模。  

主要代码如下：
```cpp
const int maxn = 100005, MOD = 1000000007;

int d[maxn];
char str[maxn];
int dp(int i)
{
	// 边界条件
    if (i < 1)
        return 0;
    if (i == 1)
        return 1;
    // 记搜
    if (d[i])
        return d[i];
    // 末尾两字符为nn或uu
    if (str[i] == 'n' && str[i - 1] == 'n' || str[i] == 'u' && str[i - 1] == 'u')
        return d[i] = i == 2 ? 2 : (dp(i - 1) + dp(i - 2)) % MOD;
    return d[i] = dp(i - 1);
}
int main()
{
    io.read(str + 1);
    int n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        if (str[i] == 'm' || str[i] == 'w') { // 不合法
            writeln(0);
            return 0;
        }
    writeln(dp(n));
    return 0;
}
```

---

## 作者：ttq012 (赞：1)

这是一道大氵题。

容易发现字符串中出现了 `w` 或者 `m` 就一定没有可能，输出 $0$。

然后如果出现的不是 `u` 或者 `n` 就是原样输出的，答案不变。

否则设出现了连续的 $k$ 个 `u` 或者 `n`，那么考虑计算一下贡献。

设 $f_i$ 代表连续出现了 $i$ 个 `u` 或者 `n`。

那么显然有 $f_1=1$，$f_2=2$，$f_i=f_{i-1}+f_{i-2}$。

那么预处理一下即可。

时间复杂度 $\mathcal O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7, N = 2e5 + 10;
int f[N];
signed main()
{
  string s;
  cin >> s;
  int l = s.size(), res = 1;
  f[1] = 1, f[2] = 2;
  for (int i = 3; i <= l; i++)
    f[i] = (f[i - 1] + f[i - 2]) % mod;
  for (int i = 0; i < l; i++)
  {
    if (s[i] == 'u')
    {
      int cnt = 0;
      while (i < l && s[i] == 'u') i++, cnt++;
      res = res * f[cnt] % mod;
      i--;
    }
    else if (s[i] == 'n')
    {
      int cnt = 0;
      while (i < l && s[i] == 'n') i++, cnt++;
      res = res * f[cnt] % mod;
      // cout << cnt << ' ' << f[cnt] << '\n';
      i--;
    }
    else if (s[i] == 'm' || s[i] == 'w')
    {
      res = 0;
      break;
    }
  }
  cout << res << '\n';
  return 0;
}
```


---

## 作者：Abeeel51 (赞：1)

 [传送门](https://www.luogu.com.cn/problem/CF1245C)

#### 题意总结

有一个字符串，将m变为nn，w变为uu，问操作前有多少种不同的字符串？

#### 解题思路

首先，字符串中出现了m或w，直接输出0。记录连续的n或u，方法如下：

设计数器为连续的长度

读入字母

为u？前一个为u？计数器++；否则 计数器=1；

为n？前一个为n？计数器++；否则 计数器=1；

否则 计数器清零；

得到了连续的长度，不难想出结果是每个连续段的方法数相乘。接着，来推一下方法数的规律

我们以n为例：

n：1种 n

nn：2种 nn m

nnn：3种 nnn nm mn

nnnn：5种 nnnn nnm nmn mnn mm

nnnnn：8种 nnnnn nnnm nnmn nmnn mnnn nmm mnm mmn

nnnnnn：13种 太多了，不一一列举

nnnnnnn：21种

nnnnnnnn：34种

而斐波那契数列（兔子数列）正是：

1 1 2 3 5 8 13 21 34 55 89 144……

边乘边取余$10^9+7$，别忘了开long long

#### AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[1000005][10]={0};
long long dp[1000005]={0,1,2};
long long mod=1000000007;
int main(){
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='w'||s[i]=='m'){
			printf("0");
			return 0;
		}else if(s[i]=='n'){
			a[i][1]=a[i-1][1]+1;
		}else if(s[i]=='u'){
			a[i][0]=a[i-1][0]+1;
		}
	}
	for(int i=3;i<=s.size()+3;i++){
		dp[i]=(dp[i-1]+dp[i-2])%mod;
	}
	long long sum=1;
	for(int i=0;i<s.size();i++){
		if(a[i][1]>0&&a[i+1][1]==0){
			sum=(sum*dp[a[i][1]])%mod;
		}else if(a[i][0]>0&&a[i+1][0]==0){
			sum=(sum*dp[a[i][0]])%mod;
		}
	}
	printf("%lld",sum);
	return 0;
}
//抄题解不以为耻反以为荣？
```

---

## 作者：きりと (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/CF1245C)**

### 题目大意

见中文翻译

### 解题思路

瞄了一眼，题解区大佬都或多或少作了一些关于 $n$ 和 $u$ 数量对答案贡献的分析。由于我太弱了导致完全不想推柿子，所以提供一种暴力dp的做法，设计出状态就A了。

定义 $f[i][j]$ 表示前 $i$ 个字符中，以 $j$ 字符结尾的前缀，可能的情况组数。

对于一般的情况，显然有 $f[i][s[i]-'a']=\sum^{j\le 25}_{j=0}f[i-1][j]$ 。

当 $s[i]$ 为 $u$ 或 $n$ 是，考虑更新 $j=w,j=m$ 的状态即可，具体可见代码。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define forr(i,l,r) for(int i=l;i<=r;i++)
#define ffor(i,r,l) for(int i=r;i>=l;i--)
#define int long long
const int N=1e5+10,mod=1e9+7;
int f[N][26];
signed main()
{
    string s;
    cin>>s;
    int l=s.size();
    s=' '+s;
    int c;
    bool flag=0;
    f[0][0]=1;
    forr(i,1,l)
    {
        if(s[i]=='m'||s[i]=='w')
        {
            flag=1;
        }
        forr(j,0,25)
        {
            if(s[i]=='u'&&s[i-1]=='u')
            {
                f[i]['w'-'a']+=f[i-2][j];
                f[i]['w'-'a']%=mod;
            }
            if(s[i]=='n'&&s[i-1]=='n')
            {
                f[i]['m'-'a']+=f[i-2][j];
                f[i]['m'-'a']%=mod;
            }
            f[i][s[i]-'a']+=f[i-1][j];
            f[i][s[i]-'a']%=mod;
        }
    }
    if(flag)
    {
        cout<<0<<endl;
        return 0;
    }
    int ans=0;
    forr(i,0,25)
    {
        ans+=f[l][i];
        ans%=mod;
    }
    cout<<ans<<endl;
}

```

---

## 作者：Allanljx (赞：1)

## 题意
给你一个字符串，乐乐修改了字符串的内容，乐乐把所有的 $m$ 改成了 $nn$ ，把所有的 $w$ ，改成了 $uu$ 。

现在给你被乐乐改动过得字符串，你知道他原来的字符串有多少种可能性吗？

你需要将答案取模于$1000000007$后输出。

如果不可能得到这样的字符串，就输出$0$。
## 思路
首先，如果字符串中有 $m$ 或 $w$ 就直接输出$0$。

然后，需要解决的是连续多个 $n$ 或 $u$ 。通过找规律发现：

$2$ $2$

$3$ $3$

$4$ $5$

$5$ $8$

$6$ $13$

左边表示的是 $n$ 或 $u$ 的个数，右边表示，原来字符串的可能数量。

发现这是一个斐波那契数列。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1000000007;
int dp[100005],n,m;
string str;
signed main()
{
	getline(cin,str);
	n=str.size();
	if(str[0]=='w'||str[0]=='m')//特判
	{
		cout<<0<<endl;
		return 0;
	}
	dp[1]=1,dp[0]=1;//初始化
	for(int i=2;i<=n;i++)
	{
		if(str[i-1]=='w'||str[i-1]=='m')//特判
		{
			cout<<0<<endl;
			return 0;
		}
		dp[i]=dp[i-1];
		if(str[i-1]==str[i-2]&&(str[i-1]=='n'||str[i-1]=='u')) dp[i]+=dp[i-2];//递归处理斐波那契数列
		dp[i]%=mod;
	}
	cout<<dp[n]<<endl;
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：1)

关键在于若有$n$连续`'n'`或`'u'`,有几种划分方案:  
记$f_n$为$n$个的结论  
1.第$n$个变,肯定与第$n-1$个结合,方案数为$f_{n-2}$  
2.不变,方案数为$f_{n-1}$  
故$f_n = f_{n-1} + f_{n-2}$  
相乘即可。  
```cpp
#include <cstdio>
#include <cstring>
#define ull unsigned long long

using namespace std;

const int N = 123456, mod = 1e9 + 7;
char s[N];
int f[N];

int main() {
	scanf("%s", s);
	int len = strlen(s);
	s[len] = 'a'; ++len;
	ull ans = 1;
	f[0] = f[1] = 1;
	for(int i = 2; i <= len; ++i) f[i] = (f[i-1] + f[i-2]) % mod;
	int leng = 1;
	if(s[0] == 'w' || s[0] == 'm') {
		printf("0\n");
		return 0;
	}
	for(int i = 1; i < len; ++i) {
		if(s[i] == 'w' || s[i] == 'm') {
			printf("0\n");
			return 0;
		}
		if(s[i] == s[i-1] && (s[i] == 'u' || s[i] == 'n')) {
			++leng;
		} else {
			if(leng == 1) continue;
			ans = ans * f[leng] % mod;
			leng = 1;
		}
	}
	printf("%llu\n", ans);
	return 0;
}
```

---

## 作者：jiangXxin (赞：1)

首先，如果字符串里面有'w'和'm'肯定是不行的，因为机器已经被魔改了,所以我们遇到w或m直接输出0就好了

考虑机器只有w和m被魔改了，那么可能的情况就只与u和n有关,考虑一串连续的n:

n:1种

nn ,m:2种

nnn, mn, nm:3种

nnnn,  nnm,  nmn,  mnn ,mm:5种

通过打表，我们可以发现这是一个斐波拉契数列，那么我们的问题就变得简单了起来，找连续的n和u长度，算出斐波拉契数列，相乘即可.


**丑陋的比赛代码:**

```cpp
    /**
    *    author:  a2954898606
    *    created: 2019/11/01 23:54:39
    **/
    #include<bits/stdc++.h>
    #define REP(A,B,I) for(int I=(A);I<=(B);I++)
    #define PER(A,B,I) for(int I=(A);I>=(B);I--)
    #define max(X,Y) ((X)<(Y)?(Y):(X))
    #define min(Y,X) ((X)<(Y)?(X):(Y))
    #define read(FILENAME) freopen((FILENAME + ".txt"), "r", stdin);
    #define write(FILENAME) freopen((FILENAME + ".txt"), "w", stdout);
    #define LL long long
    #define N 152220
    using namespace std;
    const long long mod=1e9+7;
    //char s[N];
    string s;
    int f[N];
    int main(){
        //read(1)
        //write(1)
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
     
        long long ans=1;
        f[0]=f[1]=1;
        REP(2,100000,i)f[i]=(f[i-1]+f[i-2])%mod;
        cin>>s;
        int n=s.length()-1;
        REP(0,n,i){
            if(s[i]=='w'||s[i]=='m'){
                cout<<"0"<<endl;
                return 0;
            }
        }
        int i=0;
        for(i=0;i<=n;i++){
            if(s[i]=='u'){
                int cnt=0;
                while(i<=n){
                    if(s[i]!='u')break;
                    cnt++;
                    i++;
                }
                ans=(ans*f[cnt])%mod;
                i--;
                continue;
            }
            if(s[i]=='n'){
                int cnt=0;
                while(i<=n){
                    if(s[i]!='n')break;
                    cnt++;
                    i++;
                }
                ans=(ans*f[cnt])%mod;
                i--;
                continue;
            }
        }
        cout<<ans<<endl;
        return 0;
    }
```


---

## 作者：k2saki (赞：0)

发现此题答案只和连续的 n 和 u 有关，我们考虑求出 k 个连续的 n 时的答案，记作 dp[k]。

显然，dp[0]=dp[1]=1，然后考虑 dp[i]，有两种选择：第一个是就当作一个 n/u 来看，方案数是 dp[i-1]，第二个是把这个 n/u 和前面一个 n/u 合并成 m/w ，这样的方案数就是 dp[i-2]。

所以 $\text{dp[i]=dp[i-1]+dp[i-2]}$

用乘法原理统计就可以了，注意特判串里有 m/w 的情况

```
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
char s[1010101];
int dp[101010];
const int mod = 1e9 + 7;
signed main()
{
    cin >> s + 1;
    n = strlen(s + 1);
    dp[1] = 1, dp[0] = 1;
    for (int i = 1; i <= 1e5 + 10; ++i)
    {
        dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
    }
    int sumn = 0, sumu = 0, ans = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == 'm' || s[i] == 'w')
        {
            puts("0");
            return 0;
        }
        if (s[i] == 'n')
            ++sumn;
        if (s[i] == 'u')
            ++sumu;
        if (s[i] != 'n')
            ans *= dp[sumn], sumn = 0;
        if (s[i] != 'u')
            ans *= dp[sumu], sumu = 0;
        ans %= mod;
    }
    ans *= dp[sumn] * dp[sumu];
    ans %= mod;
    cout << ans;
}
```


---

