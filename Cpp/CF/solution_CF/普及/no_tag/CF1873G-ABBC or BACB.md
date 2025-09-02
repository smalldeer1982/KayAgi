# ABBC or BACB

## 题目描述

You are given a string $ s $ made up of characters $ \texttt{A} $ and $ \texttt{B} $ . Initially you have no coins. You can perform two types of operations:

- Pick a substring $ ^\dagger $ $ \texttt{AB} $ , change it to $ \texttt{BC} $ , and get a coin.
- Pick a substring $ ^\dagger $ $ \texttt{BA} $ , change it to $ \texttt{CB} $ , and get a coin.

 What is the most number of coins you can obtain? $ ^\dagger $ A substring of length $ 2 $ is a sequence of two adjacent characters of a string.

## 说明/提示

In the first test case you can perform the following operations to get $ 2 $ coins: $ $$$\color{red}{\texttt{AB}}\texttt{BA} \to \texttt{BC}\color{red}{\texttt{BA}} \to \texttt{BCCB} $ $ </p><p>In the second test case you can perform the following operation to get  $ 1 $  coin:  $ $ \color{red}{\texttt{AB}}\texttt{A} \to \texttt{BCA} $ $ </p><p>In the third test case you can perform the following operations to get  $ 3 $  coins:  $ $ \color{red}{\texttt{BA}}\texttt{ABA} \to \texttt{CBA}\color{red}{\texttt{BA}} \to \texttt{C}\color{red}{\texttt{BA}}\texttt{CB} \to \texttt{CCBCB} $ $$$

## 样例 #1

### 输入

```
8
ABBA
ABA
BAABA
ABB
AAAAAAB
BABA
B
AAA```

### 输出

```
2
1
3
1
6
2
0
0```

# 题解

## 作者：ICE__LX (赞：7)

为什么没有人用 DP？来水一发 DP 题解。   

典型的线性 DP，先来考虑两个特殊情况：`AAAB` 和 `BAAA`。   
第一个情况可以变为 `BCCC`，获得 $3$ 枚金币。第二个情况可以变为 `CCCB`，获得 $3$ 枚金币。不难发现，当出现 $k$ 个 $A$ 与一个 $B$ 的组合，可通过操作一和二获得这 $k$ 枚硬币。  

我们可以通过遍历一遍字符串确定每一组连续的 $A$ 子串的左边界，从而确定这一组的长度，用数组 $l$ 储存下来，方便状态转移。  
先建立一个 DP 数组 $dp_{i,j}$，表示到第 $i$ 个字符可获得的最大金币数，$j$ 表示是否对第 $i-1$ 与 $i$ 个字符形成的子串进行操作，$0$ 表示不进行，$1$ 表示进行。  

随后分类讨论进行转移。

当第 $i-1$ 与 $i$ 个字符形成的子串为 `AB`，即可获得 $i-l_{i-1}$ 枚金币，可以由 $dp_{l_{i-1}-1,0}$ 或 $dp_{l_{i-1}-1,1}$ 转换而来，从而得到转换方程：  
$$dp_{i,1}=\max(dp_{l_{i-1}-1,0},dp_{l_{i-1}-1,1})+i-l_{i-1}$$

当第 $i-1$ 与 $i$ 个字符形成的子串为 `BA`，由于 $i$ 的限制，不能直接转移到连续 $A$ 子串的右边界，因此只能获得一枚金币，然后用一个变量 $c$ 记录下进行操作后第 $i$ 个字符的变化，用于第三种情况。可得转换方程：  
$$dp_{i,1}=dp_{i-1,0}+1$$

当 $c$ 与 $i$ 个字符形成的子串为 `BA`，表示上一次操作后可再进行一次操作，因此由 $dp_{i-1,1}$ 转换而来，可得转换方程：  
$$dp_{i,1}=dp_{i-1,1}+1$$

最后的答案为 $\max(dp_{n,0},dp_{n,1})$，其中 $n$ 表示字符串末尾下标。  

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I_love_Foccarus return
#define rep(i,a,b) for(int i=a;i<=b;i++)
//#define int long long
const int N = 2e5 + 5;
void fast() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
string a;
int dp[N][2] , l[N];
char c;
signed main(){
	fast();
	int t;
	cin>>t;
	while(t--){
		memset(dp , 0, sizeof(dp));
		cin>>a;
		int len = a.size();
		a = " " + a;
		l[0] = 1;
		for(int i = 1 ; i <= len ; i++)	l[i] = a[i] == 'A' ? l[i - 1] : i + 1;
		c = a[0];
		for(int i = 2 ; i <= len ; i++){
			if(a[i - 1] == 'A' && a[i] == 'B'){
				dp[i][1] = max(dp[l[i - 1] - 1][1] , dp[l[i - 1] - 1][0]) + i - l[i - 1];
				c = 'C';
			}else if(a[i - 1] == 'B' && a[i] == 'A'){
				dp[i][1] = dp[i - 1][0] + 1;
				c = 'B';
			}else if(c == 'B' && a[i] == 'A'){
				dp[i][1]  = dp[i - 1][1] + 1;
				c = 'B';
			}
			dp[i][0]  = max(dp[i - 1][0] , dp[i - 1][1]);
		}
		cout<<max(dp[len][0] , dp[len][1])<<'\n';
	}
	I_love_Foccarus 0;
}
```

---

## 作者：__Star_Sky (赞：7)

## Description
给定一个由字符 `A` 和 `B` 组成的字符串。一开始你没有硬币。你可以执行两种类型的操作:

- 选择子字符串 `AB`，将其改为 `BC`，并获得一枚硬币。

- 选择子字符串 `BA`，将其改为 `CB`，并获得一枚硬币。

问最多能获得多少硬币?

注意，这里说的子字符串必须是连续的。

---
## Solution
观察样例，可以发现形如 `AAAB` 的子串和形如 `BAAA` 的子串一定都可以一次性消完。以 `BAAA` 为例，消去的过程如下: `BAAA`,`CBAA`,`CCBA`,`CCCB`，显然这时能获得的硬币数量就是连续的 `A` 的数量。消去 `A` 的过程其实可以看作将 `B` 左移或右移。

但是并不是所有的连续的 `A` 都能被消去。考虑如下数据：`AABAAA`，这时只能消去其中一边的 `A`。

那么什么时候所有的连续的 `A` 都能被删去呢？经过思考容易发现，只要原字符串以 `B` 开头或结尾，或存在至少一个子串 `BB`，那么所有的 `A` 都能够被删去，此时能获得的最大的硬币数量就是所有 `A` 的数量。例如 `BAAAABAAA`，`AAABBAABA`。如果不满足条件，那么最优的选择一定是选择最小的连续一段 `A` 不删，枚举即可。

## Code
```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
char a[N];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",a+1);
		int n=strlen(a+1);
		int ans=0x3f3f3f3f,cnt=0;
		bool flag=false;
		if(a[1]=='B'||a[n]=='B') flag=true;
		else for(int i=1;i<=n;i++)if(a[i]=='B'&&a[i-1]=='B') {flag=true;break;}
		if(flag)
		{
			for(int i=1;i<=n;i++) if(a[i]=='A') cnt++;
			printf("%d\n",cnt);
			continue;
		}
		for(int i=1;i<=n+1;i++)
		{
			if(a[i]=='A') cnt++;
			else if(cnt) ans=min(ans,cnt),cnt=0;
		}
		cnt=0;
		for(int i=1;i<=n;i++) if(a[i]=='A') cnt++;
		if(cnt==n||cnt==0) puts("0");
		else printf("%d\n",cnt-ans);
	}
	return 0;
}
```

---

## 作者：cqbzhr (赞：5)

通过观察可以发现：

不管是 $\texttt A\texttt B$ 的情况还是 $\texttt B\texttt A$ 的情况，实际上都是 $\texttt B$ 字母在向左还是向右移动，然后将走过的 $\texttt A$ 字母全部变为 $\texttt C$ 字母

对于 $\texttt B\texttt A\texttt A\texttt A$ 或 $\texttt A\texttt A\texttt A\texttt B$ 而言， $\texttt B$ 字母可以一直向前移动，直到将所有的 $\texttt A$ 字母消耗完为止。

因此，对于这个问题而言，只要存在某个子串，其形状如 $\texttt B\texttt A\texttt A\texttt A$ 或 $\texttt A\texttt A\texttt A\texttt B$ 的情况，那么，这其中所有的字母 $\texttt A$ 都可以消除。

因此，这个问题就变为了：找出任意两个 $\texttt B$ 之间最少的字母 $\texttt A$ 的个数 $k$，答案就是整个字符串中 $\texttt A$ 字母的数量减去 $k$ 的答案。(因为一个字母 $\texttt B$ 可以消除一个方向的 $\texttt A$，$m$ 个字母 $\texttt B$ 可以将整个字符串中的字母 $\texttt A$ 划分为 $m+1$ 段，并可以消除其中的 $m$ 段内容)。而这，可以直接通过枚举答案得到。

注意：别忘了要计算字符序列中最后一个字母。

### AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,x,y,k,l,minn;
string s;
int main(){
	cin>>t;
	while(t--){
		x=0,y=0,k=0,minn=INT_MAX;
		cin>>s;
		l=s.length();
		for(int i=0;i<l;i++){
			if(s[i]=='B'){
				y++;
				k+=x;
				minn=min(minn,x);
				x=0;
			}
			else x++;
		}
		k+=x;
		minn=min(minn,x);
		if(!y)cout<<0<<endl;
		else cout<<k-minn<<endl;
	}
	return 0;
}
```


---

## 作者：igAC (赞：3)

# $\text{Description}$

给定一个由 ``A`` 和 ``B`` 组成的字符串。

你可以进行以下两种操作：

1. 将一个 ``AB`` 变成 ``BC``，并获得一个金币。

2. 将一个 ``BA`` 变成 ``CB``，并获得一个金币。

求最大能获得的金币数。

# $\text{Solution}$

发现无论多少个 ``A`` 后面接上 ``B`` 都能通过操作一全部消完。

且 ``B`` 后面接上多少个 ``A`` 都能通过操作二消完。

于是我们可以枚举分界点，使分界点左边的 ``B`` 全部使用操作一，分界点右边的 ``B`` 全部使用操作二。

然后前缀和后缀和就做完了。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n,sum[N],suf[N];
string s;
void solve(){
	cin>>s;n=s.length(),s=" "+s;int ans=0;
	memset(sum,0,sizeof(sum));
	memset(suf,0,sizeof(suf));
	vector<int>p;
	for(int i=1;i<=n;++i) sum[i]=sum[i-1]+(s[i]=='A');
	for(int i=n;i>=1;--i) suf[i]=suf[i+1]+(s[i]=='A');
	for(int i=1;i<=n;++i) if(s[i]=='B') p.push_back(i);
	if(!p.empty()) ans=max({sum[p[0]],suf[p[0]],sum[p.back()],suf[p.back()]});
	for(int i=1;i<p.size();++i) ans=max(ans,sum[p[i-1]]+suf[p[i]]);
	printf("%d\n",ans);
}
int main(){
	T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：_Ink (赞：3)

## 题意：

给你一个只含有字符 $\text{A}$ 和 $\text{B}$ 的字符串 $s$。你最开始没有硬币。你可以做如下两种操作：

1. 选取一个字串 AB，将其改变为 BC，获得一个硬币。

2. 选取一个字串 BA，将其改变为 CB，获得一个硬币。

$\\$

请问你最多可以得到多少枚硬币？

### 数据范围：

多组测试数据。测试数据个数 $t$ 满足 $1\le t \le1000$。

$1\le|s|\le2⋅10^5$

## 题解:

我们可以探究两种操作的特性：

对于操作 $1$，设 s=AAAAAB，我们可以如下操作：

`AAAAAB -> AAAABC -> AAABCC -> AABCCC -> ABCCCC -> BCCCCC`

对于操作 $2$，设 s=BAAAAA，我们可以如下操作：

`BAAAAA -> CBAAAA -> CCBAAA -> CCCBAA -> CCCCBA -> CCCCCB`

显然，我们可以观察到，操作 $1$ 中选取的 AB 变为 BC 后，BC 中的 B **可以再次作为后继与之前的 A 连接起来**，再次进行消除。

而操作 $2$ 同理，变成的 CB 中的 B **可以作为前继与之后的 A 连接起来**进行消除。

于是，我们可以观察到一个很显然的性质：对于字符串中的一个 B，若其左侧或右侧有一个仅有 A 组成的子串，那么这个 B 就可以消除这个子串。其获得的硬币数即为消除的 A 的个数（当然，如果 B 左右两侧均有 A 串，则只能消除其中一个）。

于是，我们可以遍历整个字符串，去记录两个数据：

$1.$ 仅有 A 组成的子串的个数 $k_a$。   
$2.$ 能够消除 A 串的字符 B 的个数 $k_b$。

（更严谨地说：上述记录中，仅有 A 组成的子串记录的次数应尽量小，如 AAAA 就只记录一次而非拆成 AA, AA 等记录两次或多次）

记录完成后，我们就能得出一个结论：

$1.$ 当 $k_a\le k_b$ 时，字符串中所有的 A 串都能消除，此时得到的硬币个数即为 A 的个数。  
$2.$ 当 $k_a > k_b$ 时，字符串中有一个 A 串无法消除，此时得到的硬币个数为 A 的个数减去长度最小 A 串的长度。

结论正确性证明如下：

首先结论 $1$ 是非常显然的，关键在于结论 $2$。

对于 $k_a > k_b$，实际上只会发生唯一一种情况，即 $k_a = k_b + 1$。此时字符串构型为 $\dots\text{(A)B(A)B(A)}\dots$，其中，$\text{(A)}$ 表示仅由 A 组成的连续字符串。此时，不论如何再往该字符串中添加或减少字符 A 或 B，$k_a$ 始终不会大于 $k_b + 1$。

于是，这种情况下，我们只能消除 $k_a-1$ 个 A 串，换言之我们要留下一个 A 串不消除。所以，我们留下 A 串长度最小的那个串，就可以保证获得的硬币尽量大。

这样一来，这道题就可做了，如果还不会实现的话就看代码吧。

时间复杂度为 $O(t⋅|s|)$。

## $\text{Code:}$

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define maxn 200005
using namespace std;

int t;
void _run()
{
	string s;
	cin >> s;
	int len = s.length();
	int minlen = inf, ka = 0, kb = 0, lena = 0, ans = 0;
	for(int i = 0; i < len; i ++) //遍历字符串 
	{
		if(s[i] == 'B')//找到了一个字符 B 
		{
			if(s[i - 1] == 'A' || s[i + 1] == 'A') kb ++; //该字符 B 可消除 A 串
			if(lena != 0) //如果记录的 A 串长度不为零，说明找到了一个新 A 串 
			{
				minlen = min(lena, minlen); //随时更新长度最小的 A 串 
				ka ++;
				ans += lena;
			}
			lena = 0;
		}
		else lena ++; //找到一个字符 A 
	}
	if(lena != 0) //当字符串最后一个字符不为 B 时，要额外处理一次
	{
		minlen = min(lena, minlen);
		ka ++;
		ans += lena;
	}
	 
	if(kb < ka) ans -= minlen; //如题解 
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> t;
	while(t --) _run();
	
	return 0;
}
```

---

## 作者：One_JuRuo (赞：2)

## 思路

首先发现，无论是 ```AB``` 变 ```BC```，还是 ```BA``` 变 ```CB```，最重要的都是 ```A```，因为 ```B``` 的数量不会变化，```C``` 既不是变化所需要的，数量还会变多，只有 ```A``` 是需要的并且数量还会变少。

首先思考 ```AB``` 变 ```BC``` 的情况，什么情况下可以继续变化呢？很显然 ```AB``` 前还有 ```A```就可以继续变化，而后面因为 ```C```的出现是不可能继续变化的，同理对于 ```BAA...``` 的情况也是可以连续变化的。

所以对于每一个 ```B``` 我们可以选择向左或者是向右变化，显然的，我们可以贪心，把所有的 ```A``` 都变化了。证明很显然。

对于第 $x$ 个 ```B```，假设我们选择向右变化 ```A```，那么不变化完的话，答案就会变少，如果想要这一段答案不变的话，就必须让第 $x+1$ 个 ```B``` 向左变化，但是显然就可能浪费第 $x+1$ 个 ```B``` 右侧的 ```A``` 可能贡献的答案。

所以很容易想到，统计 ```B``` 之间的 ```A``` 的数量，包括最右边和最左边的 ```A```，同时数量为 0 的我们也要统计。

对于每个 ```B``` 我们都可以选择一个方向，将答案增加其中 ```A``` 的数量，那么，一定有一段的 ```A``` 无法被统计，所以我们取最少的那一段即可。

做法很显然了，直接扫描一遍字符串，统计连续 ```A``` 的个数中最小的那个，和总共 ```A``` 的数量，最后就是总数减去最小的连续数。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,bf,res,sum,minn,n;
char ch[200005];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",ch+1),bf=res=sum=0,minn=200005,n=strlen(ch+1);
		for(int i=1;i<=n;++i)
			if(ch[i]=='B') sum+=res,bf=1,minn=min(minn,res),res=0;
			else ++res;
		sum+=res,minn=min(minn,res);
		if(!bf) printf("0\n");//记得特判没有B的情况
		else printf("%d\n",sum-minn);
	}
}
```

---

## 作者：LOvO (赞：1)

# CF1873G ABBC or BACB 题解

## 题目大意：

给你一个只含有字母 `A`、`B`、`C` 的字符串与两种操作：

- 将一个子串 `AB` 换成 `BC`。
- 将一个子串 `BA` 换成 `CB`。

求最大操作次数。

## 题目分析：

不难想到，对于每一个子串 `AAA...AB`，可以变为 `BCCC...C`；对于每一个 `BAAA...A`，可以变为 `CCC...CB`。

但是，对于一个子串 `AAA...ABAAA...A`，我们只能选择将它变为 `BCCC...CAAA...A` 或 `AAA...ACCC...CB`。

所以，我们就需要在两个 `AAA...A` 子串中选择 `A` 最多的一个。

令 `B` 的个数为 $k$，我们就需要在 $k+1$ 个区间中选择 $k$ 个区间，使 `A` 的总个数最多。

这就相当于用 `A` 的总个数减去只包含 `A` 的连续子串长度的最小值。



## code：

```cpp
#include <iostream>
#include <vector>
using namespace std;
vector<int> l;
int main() {
	cin.tie(0);
	cout.tie(0);
	int t, num, sum;	//sum 为'A'的总个数，num 为'A'的一个连续子串长度。
	string s;
	cin >> t;
	while (t--) {
		l.clear();
		num = sum = 0;	//记得每组数据初始化。
		cin >> s;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'A') num++, sum++;
			else l.push_back(num), num = 0;		//这个字符是 'B',则记录这一段的长度。 
		}
		l.push_back(num);	//别忘了最后一段。
		sort(l.begin(), l.end());
		cout << sum - l[0] << endl;
	}
	return 0;
}
```



---

## 作者：UncleSam_Died (赞：1)

### 解题思路
显然，对于每一个形如 `BAAAA` 和 `AAAAB` 的串，可以分别通过操作一和操作二消除，同时获得和 A 的长度相等的金币。

那么，我们可以先预处理出每一段连续的 A 的长度，统计与 A 相邻的 B 的个数，接着对于A 的连续段进行排序，即优先消除长度大的连续段。排序后依次消除，直到没有 A 或没有 B 为止。

---

## 作者：Falling_Sakura (赞：1)

# 思路

首先对于单独的 `AB` 或者 `BA`，可以直接把它变成 `BC` 和 `CB` 并获得一枚金币。

想想扩展一下呢？假如 `AB` 变成 `BC` 后发现前面还有一个 `A`，也就是说可以从 `AAB` 变成 `BCC`。

以此类推，`AAAAAAAAA...B` 就可以变成 `BCCCCCCCCCCCC...`，得到的价值是参与变换的 `A` 的个数。

同理可得，`BAAAAAAAA...` 就可以变成 `CCCCCCCC...B`，得到的价值也是参与变换的 `A` 的个数。

所以我们可以把原串看作若干个被 `B` 分割的区间，对于每个 `B`，我们维护它到上一个 `B` 之间 `A` 的个数和它到下一个 `B` 之间 `A` 的个数。

假设有 $n$ 个 `B`，那么就会有 $n+1$ 个区间（包括长度为 0 的区间），那么对于每一个 `B` 都有两种选择，选左边或者选右边（不选重的情况下），最后会选出 $n$ 个区间，那么可以转化一下，也就是有一个区间不选，我们排一下序拿总区间和减去这个最小的区间和得到的就是最大价值了。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 8;

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int ans = 0;
        char s[N];
        cin >> s;
        int len = strlen(s);
        int cnt = 0, be = 0;
        int l[N], r[N], last[N];
        for(int i = 0, j = 0; i < len; i++)
        {
            if(s[i] == 'B')
            {
                cnt++;
                last[cnt] = be;
                be = cnt;
                j = i - 1;
                while(j >= 0 && s[j] != 'B') j--;
                l[cnt] = i - j - 1;
                if(last[cnt] != 0)
                {
                    r[last[cnt]] = l[cnt];
                }
            }
        }
        for(int i = len - 1; i >= 0; i--)
        {
            if(s[i] == 'B')
            {
                r[cnt] = len - i - 1;
                break;
            }
        }
        vector<int> num;
        for(int i = 1; i <= cnt; i++)
        {
            num.push_back(l[i]);
            num.push_back(r[i]);
            ans += l[i];
        }
        ans += r[cnt];
        if(ans == 0)
        {
            cout << 0 << endl;
            continue;
        }
        sort(num.begin(), num.end());
        ans -= num[0];
        cout << ans << endl;
    }
    return 0;
}
```


---

## 作者：phigy (赞：1)

我们发现对于连续的 `BAAAAA` 或 `ABBBBB` 我们可以将其变为 `CCCCCB` 或 `BCCCCC`。

然后根据这个特性我们分析变化会发现由于 `B` 会变成 `C` 而 `C` 不能变化，所以当我们有 `A…ABA…A` 的情况时，我们的 `B` 选择了 `BA` 或 `AB` 后，另一端就被堵死了。

再结合开头的连续段，我们就明白了我们应当将整个串当做夹着 `B` 的多段 `A` 的连续段考虑，而答案就是 `A` 的个数。

我们发现会有两种情况一种是每段 `A` 的都可以分配到一个两端的 `B` 。

还有一种情况就是有一段 `A` 是分配不到的。

第二种情况的唯一可能就是只有 `A` 段之间有 `B` 且每段间也只有一个 `B`。

而在这种情况我们自然只需要舍弃 `A` 最少的段即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

#define int long long

using namespace std;

int T;
int n;
char a[2000005];
signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        int ans=0,res=0,f=99999999;
        cin>>a+1;
        n=strlen(a+1);
        if(a[1]=='B'||a[n]=='B')
        {
            for(i=1;i<=n;i++)
            {
                ans+=(a[i]=='A');
            }
            cout<<ans<<endl;
        }
        else
        {
            int p=0,q=0;
            for(i=1;i<=n;i++)
            {
                if(a[i]=='A')
                {
                    if(p==1)q=1;
                    ans++;
                    res++;
                }
                else
                {
                    if(res&&a[i+1]=='B')
                    {
                        p=1;
                    }
                    f=min(f,res);
                    res=0;
                }
            }
            if(res)f=min(f,res);
            if(q)
            {
                cout<<ans<<endl;
            }
            else if(ans==0||ans==n)
            {
                cout<<0<<endl;
            }
            else 
            {
               cout<<ans-f<<endl;
            }
        }
    }
    return 0;
}
```


---

## 作者：SkyLines (赞：0)

## 题目翻译：

有一个 ``A`` 和 ``B`` 组成的字符串 $s$，一开始金币数为 $0$，有以下两种操作：

* 将一个子串 ``AB`` 转换为 ``BC``，并获得一枚金币。

* 将一个子串 ``BA`` 转换为 ``CB``，并获得一枚金币。

可以进行若干次操作，求最多能获得多少枚金币。

## 思路：

很明显，类似 ``AAAA...B`` 的字符串可以转换为 ``BCCCC...C``，类似 ``B...AAAA`` 的字符串可以转换为 ``CCCC...B``。

所以，可以枚举字符串 $s$ 中的所有 ``B``，如果**左边和右边只有一个方向**有 ``A``，就可以按如上规则转换。

转换后，字符串 $s$ 变为类似 ``AAAA...AAAABAAAA...AAAABAAAA...AAAA`` 的字符串，可以转换**除长度最小的区间**，以达到金币最大化。遍历到一个 ``A``，将后面连续的 ``A`` 跳过，并更新长度。当然，也可以一个一个地遍历。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, lens, ans, tmp, a[400005], num, na;
string s;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
int getA(int aa){
	if(s[aa] != 'A') return -1;
	while(aa < lens && s[aa] == 'A') aa++;
	return aa;
}
int main(){
	scanf("%d", &t);
	for(int kk = 1; kk <= t; kk++){
		ans = 0;
		cin >> s;
		lens = s.length();
		for(int i = 0; i < lens; i++){
			if(s[i] != 'B') continue;
			if(i && i != lens - 1 && s[i - 1] == 'A' && s[i + 1] == 'A') continue;
			tmp = i - 1;
			while(tmp >= 0 && s[tmp] == 'A'){
				s[tmp--] = 'B';
				ans++;
			}
			tmp = i + 1;
			while(tmp <= lens - 1 && s[tmp] == 'A'){
				s[tmp++] = 'B';
				ans++;
			}
		}
		num = 0;
		for(int i = 0; i < lens; i++){
			if(s[i] != 'A') continue;	
			while(i < lens){
				na = getA(i);
				a[++num] = na - i;
				i = max_(i, na + 1);
				if(s[na] != 'B' || na == -1 || na == lens) break;
			}
		}
		sort(a + 1, a + num + 1, greater<int>());
		for(int i = 1; i <= num - 1; i++) ans += a[i];
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：lijunxi1 (赞：0)

# 思路

这到题，我们可以把每一个字符串看做：```AAAAAA........ABA.........ABA........AA``` 形式，在这种形式中，我们发现，对于每一个连续的 ```a```，只有这边或右边有一个 ```B``` 能分配给它，它就能全部替换，这样的话会有一组 ```A``` 不能被匹配，所以答案为 ```A``` 的个数减最短连续 ```A``` 的个数。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
string s;
int T,ans,c,mina,si;
int main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>s;
		si=s.size();
		mina=1e9,c=0,ans=0;
		for(int i=0;i<si;i++)
		if(s[i]=='A')
		{
			ans++;
			c++;
		}
		else
		{
			mina=min(mina,c);
			c=0;
		}
		mina=min(mina,c);
		cout<<ans-mina<<"\n";
	}
}
```

---

## 作者：SWAP__ (赞：0)

首先容易得出，对于 $k$ 个连续的 ```A```，只要开头或结尾加上一个 B，就可以消除全部的 ```A``` 并得到 $k$ 个金币。如 ```BAAA``` 可以用操作二清除并得到 $3$ 个金币，```AAAB``` 可以用操作一清除。

因此我们只需要计算是否有足够的 ```B``` 去一一配对这些连续的 ```A``` 就行了。设 ```B``` 的个数为 $x$，连续的 ```A``` 的子串数为 $y$，如果 $x\geq y$，可以全部消除；而 $y\equiv x-1$ 时，也就是像 ```AAABAA``` 这样的数据就要取舍掉这些连续 ```A``` 的子串长度最小的那一个。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
	cin>>n;
	while(n--){
		cin>>s;
		int ans=0,k=0,minn=1e9;
		int l=0,l1=0;
		bool f=0;
		for(int i=0;i<s.length();i++){
			if(s[i]=='A'){
				if(!f)l1++;
				k++,f=1;
			}else{
				l++;
				if(f){
					ans+=k;
					minn=min(minn,k);//计算连续A子串长度的最小值
				}
				f=k=0;
			}
		}
		ans+=k;//结束时还要更新一次
		minn=min(minn,k);
		if(l<l1){
			ans-=minn;
		}
		printf("%d\n",ans);
	}
}
```

---

