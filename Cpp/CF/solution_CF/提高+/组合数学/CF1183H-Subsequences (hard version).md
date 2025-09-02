# Subsequences (hard version)

## 题目描述

简单版和困难版的唯一区别在于约束条件。

子序列是指可以通过从另一个字符串中删除若干（可以为零）字符且不改变剩余字符顺序得到的字符串。被删除的字符不要求连续，中间可以有任意间隔。例如，对于字符串 "abaca"，以下字符串是它的子序列："abaca"、"aba"、"aaa"、"a" 和 ""（空串）。但以下字符串不是它的子序列："aabaca"、"cb" 和 "bcaa"。

给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

每次操作，你可以取 $s$ 的任意一个子序列 $t$，并将其加入集合 $S$。集合 $S$ 不能包含重复的元素。每次操作的代价为 $n - |t|$，其中 $|t|$ 表示所添加子序列的长度（即代价等于被删除字符的数量）。

你的任务是求出获得大小为 $k$ 的集合 $S$ 的最小总代价，或者报告无法做到。

## 说明/提示

在第一个样例中，可以生成 $S = \{\text{"asdf"}, \text{"asd"}, \text{"adf"}, \text{"asf"}, \text{"sdf"}\}$。$S$ 中第一个元素的代价为 $0$，其余元素的代价为 $1$。所以 $S$ 的总代价为 $4$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 5
asdf
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 6
aaaaa
```

### 输出

```
15
```

## 样例 #3

### 输入

```
5 7
aaaaa
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
10 100
ajihiushda
```

### 输出

```
233
```

# 题解

## 作者：肖然 (赞：18)

按长度j找出所有本质不同子串，之后长度由大->小贪心选取即可。
```
dp[i][j] = 前i个字符中长度=j的本质不同子串数量
转移
dp[i][j] = dp[i-1][j]（不选第i个字符）
           + dp[i-1][j-1] - dp[pre[i]-1][j-1]（选第i个字符）
其中pre[i] = i的前驱位置
```

总复杂度O(N^2)

```cpp
#include<bits/stdc++.h>
#define MAXN 105
#define LL long long
using namespace std;
 
int N;
LL K;

string s;
int pre[MAXN], last[MAXN];
LL dp[MAXN][MAXN];

int main(){
	
	cin>>N>>K;
	cin>>s;
	
	s = "%" + s;
	for(int i=1;i<=N;i++){
		int c = s[i]-'a';
		pre[i] = last[c];
		last[c] = i;
	}
	
	for(int i=0;i<=N;i++) dp[i][0] = 1;
 
	for(int i=1;i<=N;i++){
		for(int j=1;j<=i;j++){
			dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
			if(pre[i]) dp[i][j] -= dp[pre[i]-1][j-1];
		}
	}

	LL ans = 0;
	for(int j=N;j>=0;j--){
		if(K>=dp[N][j]){
			ans += (LL)(N-j)*dp[N][j];
			K -= dp[N][j];
		}
		else{
			ans += (LL)(N-j)*K;
			K = 0;
			break;
		}
	}
	if(K) cout<<"-1"<<endl;
	else cout<<ans<<endl;
	
	return 0;
}
```

---

## 作者：wucstdio (赞：3)

首先我们希望选出来的$k$个字符串长度尽可能长，因为这样代价小。

所以我们考虑对于每一个$i$，算出来长度为$i$的本质不同的字符串的数量。这样最后贪心选取就行了。

考虑和楼下不一样的$O(26n^2)$的DP。

我们设$f[i][j][c]$表示前$i$个字符，长度为$j$，最后一个字符为$c$的数量。

为了去重，如果$s[i]=c$那么就只能让字符串的结尾为$i$，否则就任意。

考虑转移。考虑$s[i]$是否等于$c$可得：

$$f[i][j][c]=\begin{cases}f[i-1][j][c]&\text{if $s[i]\neq c$}\\\sum_{c'}f[i-1][j-1][c']+[j=1]&\text{else}\end{cases}$$

令$s[i][j]=\sum_{c}f[i][j][c]$，直接转移即可，时间复杂度$O(26n^2)$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
int n;
ll k,f[105][105][26],s[105][105],ans;
char t[105];
int main()
{
	scanf("%d%I64d",&n,&k);
	scanf("%s",t+1);
	for(int i=1;i<=n;i++)
	{
		f[i][1][t[i]-'a']=1;
		for(int j=1;j<=i;j++)
		{
			for(int c=0;c<26;c++)
			{
				if(c+'a'==t[i])f[i][j][c]+=s[i-1][j-1];
				else f[i][j][c]+=f[i-1][j][c];
				if(f[i][j][c]>k)f[i][j][c]=k;
				s[i][j]+=f[i][j][c];
			}
			if(s[i][j]>k)s[i][j]=k;
		}
	}
	s[n][0]=1;
	for(int i=n;i>=0;i--)
	{
		if(s[n][i]>k)
		{
			ans+=k*(n-i);
			k=0;
			break;
		}
		ans+=s[n][i]*(n-i);
		k-=s[n][i];
	}
	if(k)
	{
		printf("-1\n");
		return 0;
	}
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：MuYC (赞：2)

### [CF1183H Subsequences (hard version)](https://www.luogu.com.cn/problem/CF1183H)

#### 具体做法

这是一道不难的 $dp$。

不难发现题目的意思实际上就是让我们求长度为前 $k$ 长的本质不同的子序列，找出每个长度对应有多少个本质不同的子序列即可。

所以问题就在于找本质不同的子序列。

怎么找呢？遇事不决，$dp$ 来解。

考虑设置状态如下:

$dp[i][j]$ 表示的是原串的前 $i$ 个字符中长度为 $j$ 的本质不同的子序列数量。

接下来就要想如何转移了。

在做 $dp[i][j]$ 的时候，我们默认已经求出来了 $dp[i - 1][1$ ~ $n]$。我们现在要考虑怎么样才能利用已知的信息推出当前信息。

不难发现，$dp[i - 1][j]$ 表示的就是前 $i - 1$ 个字符中长度为 $j$ 的本质不同的子序列数量。我们可以选择从它这里继承过来，不往这些字串后面加上当前字符，所以可以通过它来得到 $dp[i][j]$。

然后 $dp[i - 1][j - 1]$ 要转移为 $dp[i][j]$ ，那么前面所有串的末尾都要加上当前字符。但是我们又可能算重复，也就是可能会导致求出来的子序列有部分不满足是**本质不同的**子序列。于是我们要考虑容斥掉其中一部分。 这一部分是什么呢？

不难发现是 $dp[pre[i] - 1][j - 1]$ ($pre[i]$ 表示的是前一个跟当前字符相同的字符的位置)，因为 $dp[pre[i] - 1][j - 1]$ 得到的所有子序列都跟当前串是本质相同的。

于是状态转移方程 : $dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] - dp[pre[i] - 1][j - 1]$(最后一项当且仅当当前字符存在前驱的时候才会有)

最后我们显然选择长度为前 $k$ 的子序列计算答案即可。

时间复杂度:O($n ^ 2$)

具体实现放代码里面了。

#### Code

```cpp

// Problem: CF1183H Subsequences (hard version)
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;
LL k;
char s[105];
LL dp[105][105],pre[105];//前1~i个字符，长度为j，本质不同的字串的数量

int main() {
	cin >> n >> k >> (s + 1);
	for(int i = 1 ; i <= n ; i ++) {
		for(int j = i + 1 ; j <= n ; j ++)
		if(s[i] == s[j]) pre[j] = i;
	}
	for(int i = 0 ; i <= n ; i ++) dp[i][0] = 1;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= i ; j ++){
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
			if(pre[i]) dp[i][j] -= dp[pre[i] - 1][j - 1];
		}
	LL Ans = 0;
	for(int j = n ; j >= 1 && k; j --) {
		Ans += min(dp[n][j],k) * (n - j) ;
		k = max(k - dp[n][j],0ll);
	}
	if(k > 1) {printf("-1"); return 0;}//之所以是 k > 1是因为要考虑空串
	if(k == 1) Ans += n;//没有考虑空串，所有要考虑一下
	cout << Ans;
	return 0;
}
```

---

## 作者：Dilute (赞：2)

[$$\Huge\color{darkblue}\texttt{My blog}$$](https://dilute.xyz/2019/06/27/Solutions/Solution-CF1183H/)

## 瞎搞DP

~~CF出了H没出G 菜的真实~~

发现$k$从$\texttt{E}$题的$100$变成了$O(10^{12})$，考虑与$k$复杂度无关的做法。

我们考虑$f_{i, j}$表示以$s_i$开始，**本质不同**的长度为$j$的子序列数量。

<!--more-->

显然直接转移是错误的，例如下面这种情况就会在计算字符串$\texttt{baa}$的$f_{1, 2}$的时候把$\texttt{ba}$给计算两遍。

我们考虑如何去掉这些重复算的字符串。

首先，我们枚举下一个出现的位置$u$，考虑$f_{u, j - 1}$被算重的条件。

如果存在一个$k$，使得$s_k = s_j$且$i < k < u$，那么我们发现$f_{k, j - 1}$完全包含的$f_{u, j - 1}$，换句话说就是$f_{u, j - 1}$整个算重了。

也就是说，我们在枚举转移的时候，我们只需要选择$s_u$是在$(l, n]$这段区间内第一次出现的$f_{u, j - 1}$转移即可。

求出了$f$之后，我们可以得出长度为$len$的本质不同的子序列就是$f[0][len + 1]$。

我们只需要从高到低枚举$len$，然后贪心的尽量取长的字符串即可。

最终复杂度$O(n^3)$（其实是可以做到$O(26 n^2)$的，但是过了就行）。

## 代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

ll inp(){
    char c =getchar();
    while(c < '0' || c > '9')
        c = getchar();
    ll sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

ll f[200][200];
bool used[30];
char s[200];

int main(){
    int n = inp();
    ll k = inp();
    scanf("%s", s + 1);
    for(int i = 0; i <= n; i++)
        f[i][1] = 1;
    for(int len = 2; len <= n + 1; len++){
        for(int i = 0; i <= n; i++){
            memset(used, false, sizeof(used));
            for(int j = i + 1; j <= n; j++)
                if(!used[s[j] - 'a']){
                    used[s[j] - 'a'] = true;
                    f[i][len] += f[j][len - 1];
                    f[i][len] = std::min(f[i][len], k);
                }
        }
    }
    ll ans = 0;
    for(int i = n; i >= 0; i--){
        ll sum = f[0][i + 1];
        memset(used, false, sizeof(used));
        if(k > sum){
            k -= sum;
            ans += (n - i) * sum;
        } else {
            ans += (n - i) * k;
            k = 0;
        }
    }
    if(k > 0){
        printf("-1\n");
        return 0;
    }
    printf("%lld\n", ans);
}
```



---

## 作者：ZMQ_Ink6556 (赞：1)

## 题解：CF1183H Subsequences (hard version)

抽象 Easy version $2000$ 但 Hard version $1900$。

### 解题思路

明显**贪心**，**优先选择长度更长的子序列**。

求不同长度的不同子序列可以 **dp 解决**。

设 $dp_{i,j}$ 表示前 $i$ 个字符中长度为 $j$ 的子序列数量。

如果不考虑本质不同的子序列，则有 $dp_{i,j} = dp_{i - 1,j} + dp_{i - 1,j - 1}$。

考虑最后一位的情况：如字符串 `abc`，那么从 `ab` 转移到所有字符 `c` 时都相同。

所以减去 $dp_{pre_i - 1 , j-1}$ 即可，其中 $pre_i$ 表示 $S_i$ 上一次出现的位置，如果没有出现过默认为 $0$。

所以最终的 dp 公式为：$dp_{i,j} = dp_{i - 1,j} + dp_{i - 1,j - 1} - dp_{pre_i - 1 , j-1}$。

所以长度为 $x$ 的子序列的个数为 $dp_{n , x}$。

如果出现以下情况：

$$k - 1 > \sum_{i = 1}^{n} dp_{n,i}$$

则无解，否则从多至少选择即可。

记得开 **long long**！

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long n , k , p , dp[105][105] , ans;
char s[105];
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> s[i];
	}
	for(int i = 0 ; i <= n ; i++)
	{
		dp[i][0] = 1;
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= i ; j++)
		{
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
			for(int k = i - 1 ; k >= 1 ; k--)
			{
				if(s[i] == s[k])
				{
					dp[i][j] -= dp[k - 1][j - 1];
					break;
				}
			}
		}
	}
	for(int i = n ; i >= 0 ; i--)
	{
		ans += min(dp[n][i] , k) * (n - i);
		k -= min(dp[n][i] , k);
		if(!k)
		{
			break;
		}
	}
	if(k)
	{
		cout << "-1";
	}
	else
	{
		cout << ans;
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1183H)
## 思路
@[_edge_](https://www.luogu.com.cn/user/208653) 最喜欢的诈骗题。

乍一看这个 $k$ 的范围非常吓人，但是这个 $n$ 的范围非常小。不妨考虑复杂度和 $n$ 有关的 $\verb!DP!$。

设 $f_{i,j,k}$ 表示在区间 $1$ 到 $i$ 中，长度为 $j$，结尾字母为 $k$ 的子序列数目。

显然，若 $s_i=k$，$f_{i,j,k}=f_{i-1,j-1,k_1}\ \ \ \ (k1 \ne k)$。

而若 $s_i \neq k$，$f_{i,j,k}=\sum f_{i-1,j-1,k1}$。

显然我们发现 $\sum$ 是可以前缀和优化的。

这道题目其实并不用滚存，但是由于今天模拟赛没开滚存 $\verb!MLE!$ 了有心理阴影，所以我开了个滚存，把 $i$ 这一维滚掉，同时真心建议大家养成这个好习惯，~~不过有时候也会因为滚存转移炸掉~~。
## 代码
不放了，自己写。

---

## 作者：decoqwq (赞：1)

递推求解

令$f[i][j]$代表以$i$位置结尾长度为$j$的不同子串个数，并记录每一个字母上次出现的位置$las[i]$

可以得到，如果这个字母是第一次出现，那么$f[i][j]=f[i-1][j]+max(f[i-1][j-1],1ll);$

否则$f[i][j]=f[i-1][j]+f[i-1][j-1]-f[las[a[i]]-1][j-1];$(减去相同的情况)

然后从长到短取不同子串即可

PS:防止抄袭，此代码将会wa on 59
```cpp
#include <bits/stdc++.h>
using namespace std;
long long f[110][110];
char a[110];
map<char,int> las; 
int main()
{
    int n,k;
    cin>>n>>k;
    scanf("%s",a+1);
    f[n][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            if(las[a[i]]==0)
            {
                f[i][j]=f[i-1][j]+max(f[i-1][j-1],1ll);
            }
            else
            {
                f[i][j]=f[i-1][j]+f[i-1][j-1]-f[las[a[i]]-1][j-1];
            }
        }
        las[a[i]]=i;
    }
    long long ans=0;
    for(int i=n;i>=0;i--)
    {
        if(k<=f[n][i])
        {
            ans+=k*(n-i);
            k=0;
            break;
        }
        k-=f[n][i];
        ans+=f[n][i]*(n-i);
    }
    cout<<(k>0?-1:ans);
}
```

---

## 作者：CWzwz (赞：0)

[CF1183H Subsequences (hard version)](https://www.luogu.com.cn/problem/CF1183H) 题解

[Codeforces](http://codeforces.com/problemset/problem/1183/H)

---

数据范围十分令人不解的 dp 题。第一眼以为和 $\sqrt{k}$ 有关，最后用倒一 $O(n ^ 3)$ 草过了。

要选出 $k$ 个子序列，容易发现长度更大的子序列严格优于短的。所以只要知道 $\forall l$，长为 $l$ 的不同子序列个数，就可以贪心选更长的了。

考虑 dp，$f_{i, L}$ 表示 $s_{1..i}$ 有多少个长为 $L$ 的本质不同子序列、且钦定 $s_i$ 必选。

容易想到，枚举上一个字符 $s_j$，$f_{i, L} = \sum_{j = 1} ^ {i - 1} f_{j, L - 1}$。但是 $i$ 前有多个相同字符的时候会算重，所以对于某种多次出现的字符，只从离 $i$ 最近的该字符处转移即可。这样，这些等价字符的贡献只在该位置计算一次。

转移是 $O(n)$ 的，可以优化到字符集级别，但是既然 $n$ 没有给到 $1000$ 就算了。

时间 $O(n^3)$，或 $O(n^2 \cdot |V|)$，$|V|$ 为字符集。

[Submission](https://codeforces.com/contest/1183/submission/293211804)

---

## 作者：wmrqwq (赞：0)

vp 到的。

# 题目链接

[CF1183E Subsequences (eazy version)](https://www.luogu.com.cn/problem/CF1183E)

[CF1183H Subsequences (hard version)](https://www.luogu.com.cn/problem/CF1183H)

# 解题思路

考虑动态规划。

设 $dp_{i,j}$ 表示考虑到字符串前 $i$ 个字符中选取的字符长度为 $j$ 的**不同**的子序列数量。

于是我们就有以下转移：

$dp_{i,j} = dp_{i-1,j} + dp_{i-1,j-1} - dp_{lst_{i},j-1}$。

其中，$lst_{i}$ 表示字符串的第 $i$ 个字符上一次出现在哪里。

然后大力将 dp 结果贪心选取即可。

**注意**，$dp_{n,i}$ 可能会小于 $0$，贪心前需要先将 $dp_{n,i}$ 和 $0$ 取最大值，不然就会 Wrong Answer on test #35。

时间复杂度 $O(n^2)$，足以通过 Eazy ver 和 Hard ver。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
/*
dp,

dp[i][j]表示前i个字符中长度为j的不同的子序列数量 
*/
ll n,m;
ll dp[110][110],ans;
string s;
ll lst[310],pre[310];
ll f(char x){
	return x-'a';
}
void solve()
{
	_clear();
	cin>>n>>m>>s;
	s=' '+s;
	forl(i,1,n)
		pre[i]=lst[f(s[i])],lst[f(s[i])]=i;
	forl(i,0,n)
		dp[i][0]=1;
	forl(i,1,n)
		forl(j,1,i)
		{
			dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
			if(pre[i])
				dp[i][j]-=dp[pre[i]-1][j-1];
		}
	forr(i,n,0)
	{
		Max(dp[n][i],0ll);
		if(m>=dp[n][i])
			ans+=(n-i)*dp[n][i],m-=dp[n][i];	
		else
			ans+=(n-i)*m,m=0;
	}
	if(m==0)
		cout<<ans<<endl;
	else
		cout<<-1<<endl;
}
int main()
{
	IOS;
	_t_=1;
// 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：qczrz6v4nhp6u (赞：0)

Eazy \*2000 绿，Hard \*1900 蓝，世界名画。

貌似是一种与现有做法不同的 DP？

### Solution

一个显然的想法是将所有长度的子序列求出来，按长度从大到小贪心计算贡献，正确性一目了然。

然而我们只关心长度为 $i$ 的子序列数量，所以我们考虑设计一种算法来求出每种子序列的数量。

考虑 DP。设 $f_{i,j}$ 表示长度为 $i$，结尾为 $j$（此处设 $\texttt{a}=1,\texttt{b}=2,\cdots,\texttt{z}=26$）的**本质不同**子序列个数。

当我们扫到 $c$ 的时候，考虑更新每一个 $f_{x,c}$。

显然将长度为 $x-1$ 的子序列后拼上 $c$ 就能得到长度为 $x$，以 $c$ 结尾的子序列，同时归纳可得这些子序列本质不同。那么有：

$$f_{x,c}=\sum_{i=0}^{26}f_{x-1,i}$$

初值 $f_{0,0}=1$。

容易发现前缀和可以优化掉一个常数，复杂度为 $O(n^2)$。

实际上不前缀和也没事，反正 $n\le 100$ 随便碾过。

### Code

```cpp
#include<bits/stdc++.h>
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
using namespace std;
using ll=long long;
using ull=unsigned long long;
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())c=='-'&&(f=1);
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
Tp inline void assign(T *a,int n,T b){while(n--)*a++=b;}
Tp inline void copy(T *a,T *b,int n){while(n--)*a++=*b++;}
Tp inline void ckmin(T &a,T b){b<a&&(a=b);}
Tp inline void ckmax(T &a,T b){a<b&&(a=b);}
const int N=1e2+5;
int n;ll K;
char str[N];
ll f[N][26],s[N];
int main(){
	scanf("%d%lld%s",&n,&K,str+1);
	s[0]=f[0][0]=1;
	for(int p=1;p<=n;p++)
		for(int i=n;i>=1;i--){
			s[i]-=f[i][str[p]-'a'];
			f[i][str[p]-'a']=s[i-1];
			s[i]+=f[i][str[p]-'a'];
		}
	ll ans=0;
	for(int i=n;i>=0&&K;i--)
		ans+=min(s[i],K)*(n-i),K-=min(s[i],K);
	if(!K)printf("%lld\n",ans);
	else printf("-1\n");
	return 0;
}
```

---

