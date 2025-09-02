# Easy Problem

## 题目描述

Vasya is preparing a contest, and now he has written a statement for an easy problem. The statement is a string of length $ n $ consisting of lowercase Latin latters. Vasya thinks that the statement can be considered hard if it contains a subsequence hard; otherwise the statement is easy. For example, hard, hzazrzd, haaaaard can be considered hard statements, while har, hart and drah are easy statements.

Vasya doesn't want the statement to be hard. He may remove some characters from the statement in order to make it easy. But, of course, some parts of the statement can be crucial to understanding. Initially the ambiguity of the statement is $ 0 $ , and removing $ i $ -th character increases the ambiguity by $ a_i $ (the index of each character is considered as it was in the original statement, so, for example, if you delete character r from hard, and then character d, the index of d is still $ 4 $ even though you delete it from the string had).

Vasya wants to calculate the minimum ambiguity of the statement, if he removes some characters (possibly zero) so that the statement is easy. Help him to do it!

Recall that subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

## 说明/提示

In the first example, first two characters are removed so the result is ardh.

In the second example, $ 5 $ -th character is removed so the result is hhzawde.

In the third example there's no need to remove anything.

## 样例 #1

### 输入

```
6
hhardh
3 2 9 11 7 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
8
hhzarwde
3 2 6 9 4 8 7 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
6
hhaarr
1 2 3 4 5 6
```

### 输出

```
0
```

# 题解

## 作者：floatery (赞：14)

个人认为滚动数组更容易理解

注意状态转移，dp\[1]表示的是清除所有的h

```cpp
#include <stdio.h>
long long min(long long a,long long b)
{
	return a<b?a:b;
}
long long dp[5],a[100001];
char str[100001];
int main()
{
	int n,i=0,ans=0;
	scanf("%d",&n);
	scanf("%s",str);
	for(i=0;i<n;i++)
	{
		scanf("%I64d",&a[i]);
	}
	for(i=0;i<n;i++)
	{
		switch(str[i])
		{
			case 'h': dp[1]+=a[i];break;
			case 'a': dp[2]=min(dp[1],dp[2]+a[i]);break;
			case 'r': dp[3]=min(dp[2],dp[3]+a[i]);break;
			case 'd': dp[4]=min(dp[3],dp[4]+a[i]);break;
		}
	}
	printf("%I64d\n",dp[4]);
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：9)

我们设 $f[i][j]$ 为让原字符串满足最多包含 $\texttt{hard}$ 的前 $j$ 个字符，所需要的最小修改代价  
特别的，$f[i][0]$ 表示不包含 $h$ 的最小修改代价

考虑转移方程，有两种情况

当 $s[i] \ne c[j+1]$ 时（$c$ 是预先处理好的 $\texttt{hard}$），加上第 $i$ 个字符后不会增加最大匹配的长度，所以 $f[i][j]=f[i-1][j]$

当 $s[i] = c[j+1]$，又可以选择删与不删第 $i$ 个字符  
所以 $f[i][j]=\min(f[i-1][j]+a[i],f[i-1][j-1])$  
在选择不删除的时候，为了不凑出 $\texttt{hard}$ 的前 $j+1$ 个字符，我们在前面最多只能凑出前 $j-1$（使得 $c[j+1]$ 与前面的字符断开）。

我们发现在每次转移的时候，只用到了 $f[i-1]$ 和 $f[i]$ 这两层，所以我们可以把第一维用滚动数组省略掉

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const long long Maxn=100000+10,inf=(1ll<<60);
long long f[5],a[Maxn];
char c[5]={'f','h','a','r','d'};
char s[Maxn];
long long n,ans=inf;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld",&n);
	scanf("%s",s+1);
	for(long long i=1;i<=n;++i)
	scanf("%lld",a+i);
	for(long long i=1;i<=n;++i)
	for(long long j=3;j>=0;--j)
	if(s[i]==c[j+1])
	{
		f[j]+=a[i];
		if(j)f[j]=min(f[j],f[j-1]);
	}
	for(long long i=0;i<4;++i)
	ans=min(ans,f[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ForTomorrow (赞：3)

## 简单的分析
首先思考题目，需要使删除完的字符串中不包括 $\texttt{hard}$，同时还要保证得到的结果还是最小的代价，正面去思考会发现情况变得非常的复杂，所以我们想到使用动态规划！既可以保证状态的正确性又能获得最小的代价。

## 动态规划的定义与初始化
**定义：** $dp_{i,j}$ 表示进行到第 $i$ 个字符时，不能包含 $\texttt{hard}$ 的前 $j$ 个字符的最小代价。

- $dp_{i,1}$ 表示前 $i$ 个字符不存在 $\texttt{h}$ 子序列的最小代价
- $dp_{i,2}$ 表示前 $i$ 个字符不存在 $\texttt{ha}$ 子序列的最小代价
- $dp_{i,3}$ 表示前 $i$ 个字符不存在 $\texttt{har}$ 子序列的最小代价
- $dp_{i,4}$ 表示前 $i$ 个字符不存在 $\texttt{hard}$ 子序列的最小代价

**初始化：** $dp_{0,j} = 0,j \in [1,4]$（没有字符时代价肯定为 $0$ 呗），其他初始化 $+\infty$。

## 状态转移方程
我们把 $\{h,a,r,d\}$ 映射成 $\{1,2,3,4\}$，其余字符为 $0$。例如：$f(h) = 1$

当 $f(s_i) \neq j$ 时，这个字符我们就可以不用管它了，直接 $dp_{i,j} = dp_{i-1,j}$ 就可以了

当 $f(s_i) = j$ 时，有两种状态转移过来可以保证不形成对应的子序列：
1. $dp_{i,j} = dp_{i-1,j}+cost_i$： 付出当前代价 $cost_i$，删除当前字符。
2. $dp_{i,j} = dp_{i-1,j-1}$： 从前 $i-1$ 个字符中不存在 $\texttt{hard}$ 的前 $j-1$ 个的子序列的末尾拼接上 $s_i$。例如：$i=j=4$ 时，我们可以保留这个字符 $\texttt{d}$ 的同时拼接上前 $i-1$ 个字符不存在 $\texttt{har}$ 子序列，这样子也可以保证不存在 $\texttt{hard}$ 子序列。

然后保证最小取 $min$ 即可

$$
dp_{i,j} = 
\begin{cases}
dp_{i,j-1} & f(s_i) \neq j\\
min(dp_{i-1,j}+cost_i,~ dp_{i-1,j-1}) & f(s_i) = j
\end{cases}
$$

## AC代码
```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

int f (char op) {
    if (op == 'h') return 1;
    if (op == 'a') return 2;
    if (op == 'r') return 3;
    if (op == 'd') return 4;
    return 0;
}

signed main(){
    int n;
    string s;
    cin >> n >> s;
    vector<int> cost(n+1);
    vector<vector<ll>> dp(n+1, vector<ll>(5, INF));
    
    for (int i = 1; i <= 4; ++i) dp[0][i] = 0;
    for (int i = 1; i <= n; ++i) cin >> cost[i];
    
    for (int i = 1; i <= n; ++i) {
        int op = f(s[i-1]);
        for (int j = 1; j <= 4; ++j) {
            if (op != j) dp[i][j] = dp[i-1][j];
            else dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]+cost[i]);
        }
    }
    cout << *min_element(dp[n].begin()+1, dp[n].end()) << '\n';
    return 0;
}

```
### 蒟蒻第一次写题大佬轻喷 $QAQ$


---

## 作者：A_Pikachu (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/CF1096D)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf1096d-easy-problem)）

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

看到最小化代价就想到用动态规划。

有一维一定是计算到的位置，观察剩下的字符串，仅有的条件只是不含 "hard" 子序列，也就是说，当在不断在字符串末尾添加字符时，如果出现了子序列 "hard"，那么其中必有一个要删除。考虑删除的状态，因为只有 'h'，'a'，'r'，'d' 四个字符对合法性有影响，所以只需要考虑这四个字符出现的位置，又因为需要求出删除和保留方案，则将第二维定义为经过若干次删除后的字符串中的子序列至多与 "hard" 匹配的长度。

也就是说，$f[i][j]$ 表示计算到第 $i$ 位时，其子序列与 "hard" 匹配的最长长度为 $j-1$ 的代价。

首先，对于不在 "hard" 内的字符 $s_i$，它对答案没有影响，即$f[i][j]=f[i-1][j]$。

其次，如果不删除新添的字符 $s_i=j$，则第 $j$ 匹配位数新增 $1$，即 $f[i][j]=f[i-1][j-1]$。

最后，如果删除新添的字符 $s_i=j$，则第 $j$ 匹配位数上需加上相应的代价，即 $f[i][j]=f[i-1][j]+a[i]$。

注意到第一维只与前一位相关，故可省，即若 $j$ 在 "hard" 内，$f[j]=\min\{f[j]+a[i],\ f[j-1]\}$，如果 $s_i$ 为 'h' 的话则不需要与 $f[j-1]$ 取最小值。

$\Large\mathscr{Part\,\,2\;\;}\text{Code}$

```cpp
#include <cstdio>
const int N=1e5+5,AL=26;
const long long inf=0x7fffffffffffffff;
int n,u,d[AL];
long long ans=inf,f[5];
char s[N];
long long min(long long x,long long y){return x<y?x:y;}
int main(){
	scanf("%d%s",&n,s+1); f[0]=inf;
	d['h'-'a']=1; d['a'-'a']=2; d['r'-'a']=3; d['d'-'a']=4;
	for(int i=1; i<=n; i++){
		scanf("%d",&u);
		if(!d[s[i]-'a']) continue;
		f[d[s[i]-'a']]=min(f[d[s[i]-'a']]+u,f[d[s[i]-'a']-1]);
	}
	for(int i=1; i<=4; i++) ans=min(ans,f[i]);
	printf("%lld\n",ans);
	return 0;
}
```
时间复杂度 $\Theta(n)$。


---

## 作者：G_A_TS (赞：3)

题解同步发布于[blog](https://www.cnblogs.com/wzzorz/articles/10365025.html)  

------------
**unaccept**的同学们  
#### 要开long long！  
事实上此题就是dp，dp[i][j]表示前i个字符中清到‘hard’的第几个  
状态转移方程：  

------------
```cpp
if(S[i]!=hard[j])
{
	dp[i][j]=dp[i-1][j];
}
else
{
	dp[i][j]=min(dp[i-1][j-1],dp[i-1][j]+a[i]);
}
```

------------
关于else里的转移方程：因为要破掉‘hard’，**可以扔前面的，也可以灭当前这个**  
第一个方程就不用讲了吧  
然后就可以到代码中理解了

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],dp[100010][10],ans;
char hard[5]={'\0','h','a','r','d'},S[100010];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>S[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	memset(dp,0x7f,sizeof(dp));
	for(int i=1;i<=4;i++)
	{
		dp[0][i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=4;j++)
		{
			if(S[i]!=hard[j])
			{
				dp[i][j]=dp[i-1][j];
			}
			else
			{
				dp[i][j]=min(dp[i-1][j-1],dp[i-1][j]+a[i]);
			}
		}
	}
	ans=dp[n][1];
	for(int i=2;i<=4;i++)
	{
		if(dp[n][i]<ans)
		{
			ans=dp[n][i];
		}
	}
	cout<<ans;
}
```

---

## 作者：Neil_Qian (赞：2)

# Easy Problem 题解

翻译题目上有了，这里就不说了。

仔细看题目会发现只有 ```hard``` 这几个字母与答案有关，其它可以忽略。

因为是子序列，因此可以 ```h```、一堆字母、```a```、一堆字母，以此类推。请注意，```hrad``` 是可以出现的。以此为启发，我们可以用 $dp_{i,j}$ 表示到了第 $i$ 个字母了，如果 ```h``` 没有出现过则为 $0$，如果 ```a``` 没有出现过则为 $1$，如果 ```r``` 没有出现过则为 $2$，如果 ```d``` 没有出现过则为 $3$。我们细看动规细节：

```cpp
for(ll i=1;i<=n;i++)for(ll j=0;j<4;j++){//枚举上述的i,j。
	dp[i][j]=1e18;
	if(!t.find(x[i])>=t.size()){dp[i][j]=dp[i-1][j];break;}//和这个字母没关系。
	for(ll k=0;k<=j;k++)//枚举从哪一个转移
		dp[i][j]=min(dp[i][j],dp[i-1][k]+a[i]*(x[i]==t[k]));
//重点：从它转移以后，如果正好是对应的字母，那么必须把它删掉，否则就不符合题目的要求。t见完整代码。
	if(i==n)ans=min(ans,dp[i][j]);//统计答案
}
```

下面放上完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;const ll N=1e5+2;//将long long替换为ll。
const string t="hard";ll n,a[N],dp[N][6],ans=1e18;string x;
//t这样做的好处是：如果要找一个字符的编号，用find即可；如果要找下标对应的字符，访问下标对应的位置即可。
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//关同步，可以加速。切记：这样加速以后，千万千万不要用scanf了！！！
	cin>>n>>x,x=" "+x;//加个空格，可以从1开始。
	for(ll i=1;i<=n;i++)cin>>a[i];//输入。
	for(ll i=1;i<=n;i++)for(ll j=0;j<4;j++){//dp过程。
		dp[i][j]=1e18;
		if(!t.find(x[i])>=t.size()){dp[i][j]=dp[i-1][j];break;}
		for(ll k=0;k<=j;k++)
			dp[i][j]=min(dp[i][j],dp[i-1][k]+a[i]*(x[i]==t[k]));
		if(i==n)ans=min(ans,dp[i][j]);
	}
	return printf("%lld\n",ans),0;//输出。
}
```

感谢大家，不要吝惜您的赞！

---

## 作者：LJC00118 (赞：2)

$ f[i][j] $ 表示到了第 $ i $ 个字母，$ hard $ 已经匹配到了第 $ j $ 个字母的最小代价

直接 $ dp $ 即可

```cpp
#include <bits/stdc++.h>
#define int long long
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 1e5 + 5;

int f[N][5], w[N];
char c[N];
int n;

int calc(char t) {
	if(t == 'h') return 1;
	if(t == 'a') return 2;
	if(t == 'r') return 3;
	if(t == 'd') return 4;
	return 0;
}

#undef int
int main() {
#define int long long
	memset(f, -1, sizeof(f));
	read(n); scanf("%s", c + 1);
	for(register int i = 1; i <= n; i++) read(w[i]);
	f[0][0] = 0;
	for(register int i = 0; i < n; i++) {
		int val = calc(c[i + 1]);
		for(register int j = 0; j <= 3; j++) {
			if(f[i][j] == -1) continue;
			if(val == j + 1) {
				if(f[i + 1][j + 1] == -1) f[i + 1][j + 1] = f[i][j];
				else f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j]);
				if(f[i + 1][j] == -1) f[i + 1][j] = f[i][j] + w[i + 1];
				else f[i + 1][j] = min(f[i + 1][j], f[i][j] + w[i + 1]);
			} else {
				if(f[i + 1][j] == -1) f[i + 1][j] = f[i][j];
				else f[i + 1][j] = min(f[i + 1][j], f[i][j]);
			}
		}
	}
	int ans = f[n][0];
	for(register int i = 0; i <= 3; i++) if(f[n][i] != -1) ans = min(ans, f[n][i]);
	cout << ans << endl;
	return 0;
}
```

---

