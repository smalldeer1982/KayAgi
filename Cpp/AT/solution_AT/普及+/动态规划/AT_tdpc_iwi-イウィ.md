# イウィ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_iwi

入力は以下の形式で標準入力から与えられる。

> $ s $

 答えを一行に出力せよ。 ```

iwiwii
```

```

2
```

```

iwiwwwiiiwiwiwiiwii
```

```

5
```

## 说明/提示

### Constraints

 $ s $ は i と w からなる文字列である。すぬけ君は、この中から連続する三文字が "iwi" となっている部分を取り除く操作を繰り返すことができる。(iwi を取り除くと、その左側と右側にあった文字列が連結され、長さが三文字短い新しい文字列ができる。) 操作を行うことのできる回数の最大値を求めよ。

- - - - - -

- $ 1\ <\ =\ |s|\ <\ =\ 300 $
- Each character in $ s $ will be either 'i' or 'w'.

# 题解

## 作者：Nightsky_Stars (赞：5)

# 题目大意：

给你一个字符串，把其中连续的 iwi 消掉，左侧和右侧会合在一起，求最大操作次数。

# 思路：

这是一道很经典的区间 DP，$dp[i][j]$ 表示 $i$ 到 $j$ 的最大操作数。

而转移方程就为 $dp[i][j]=\max{dp[i][k]+dp[k+1][j]}$。

最后输出 $\frac{dp[1][n]}{3}$ 即可。

# CODE:

```
#include<bits/stdc++.h>
using namespace std;
int n,dp[310][310];
int main(){
    string s;
    cin>>s;
    n=s.size();
    s=" "+s;
    for(int len=2;len<=n;len++){//区间DP
		for(int j=1;j<=n-len+1;j++){
			int i=j+len-1;
			for(int k=j;k<i;k++){
				dp[j][i]=max(dp[j][i],dp[j][k]+dp[k+1][i]);
				if(s[j]=='i'&&s[i]=='i'&&s[k]=='w'&&dp[j+1][k-1]==k-j-1&&dp[k+1][i-1]==i-k-1){
					dp[j][i]=i-j+1;
				}
			}
		}
	}
    cout<<dp[1][n]/3<<"\n";
    return 0;
}
```

---

## 作者：alex_liu (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT688)

## 思路：

其实我一开始的想法也是 DP，但是转移的时候比较麻烦（也有可能是本人太弱）。

于是我从样例开始思考，可以发现，我们想要要求删除的次数最大，就需要让删掉一个 `iwi` 之后还能再生成一个 `iwi`。

那么生成的条件是什么呢？很明显，就是在原有的一个 `iwi` 的左侧或右侧还有一个 `i`，这样有可能继续生成，也就是说，先在字符串中找到所有的 `iiwi` 和 `iwii` 并删除，最后再扫一遍字符串删除 `iwi` 即可。

最后的删除次数为：$(len-|S|)/3$ （$len$ 为原字符串的长度）

## AC CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	cin>>s;
	int len=s.size();
	while(s.find("iwii")!=s.npos)s.erase(s.find("iwii"),3);
	while(s.find("iiwi")!=s.npos)s.erase(s.find("iiwi")+1,3);
	while(s.find("iwi")!=s.npos)s.erase(s.find("iwi"),3);
	int ans=(len-s.size())/3;
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Obviathy (赞：2)

## Solution

很经典的区间 DP 了，我们定义 $f_{i,j}$ 记录 $i$ 到 $j$ 能删掉多少字符，显然最后答案应除以三。

因为答案计算的是最大的步数，那么对于一个大区间，考虑在一般情况下的答案就应该是其分成的两个小区间的答案之和。考虑枚举这两个区间之间的分界点 $k$，答案区最大值即可。比较类似与合并石子。

但有些情况直接相加是不正确的。即如果 $i$ 和 $j$ 位置上都是 `i`，$k$ 位置上是 `w`，且中间的两个小段可以被完全删除。那么，当中间的被删掉之后，左右的 `i` 和中间的 `w` 就会拼在一起，也可以删掉，那么这个区间的答案就应该是它的长度，但显然直接相加有可能会出错。

## AC code:
```cpp
#include <bits/stdc++.h>
#include <cstring>
using namespace std;
const int N = 303;
char s[N];
int n,f[N][N];
int main(){
   scanf("%s",s+1);
    n = strlen(s+1);
    for(int len = 2;len <= n;len ++){
        for(int i = 1;i+len-1 <= n;i ++){
            int j = i+len-1;
            for(int k = i;k < j;k ++){
                f[i][j] = max(f[i][j],f[i][k]+f[k+1][j]);
                if(s[i] == 'i' && s[j] == 'i' && s[k] == 'w' && f[i+1][k-1] == k-i-1 && f[k+1][j-1] == j-1-k)f[i][j] = j-i+1;
            }
            //cout << f[i][j] << endl;
        }
    }
    cout << f[1][n] / 3 << endl;
    return 0;
}
```

---

## 作者：Proxima_Centauri (赞：1)

[雅虎曰：原题传送门](https://www.luogu.com.cn/problem/AT_tdpc_iwi)

------------
# 题意
就像玩消星星的游戏：给你一个字符串，把**连续**的`iwi`消掉，左右两边的会合在一起，求最多能消多少次。
# 思路
考虑**区间 DP**。

定义 $f[i][j]$ 表示：第 $i$ 个到第 $j$ 个字符中间能消掉多少个字符，最后答案也就显而易见了，如果设 $n$ 为字符串长度的话，那么就是 $f[1][n] / 3$。

俗话说得好，DP 成功在于转移方程。枚举 $i$ 和 $j$ 中间的转折点 $k$，这个点左边能消掉的字符加上右边能消掉的字符个数,加起来取最大值，就是 $i$ 和 $j$ 中间能消掉的字符。
$$f[i][j] = \max\{f[i][k] + f[k + 1][j]\}$$

但是还要考虑一种情况，如果字符串在 $i$ 和 $j$ 的位置是`i`，$k$ 的位置上是`w`，并且 $i + 1$ 到 $k - 1$ 以及 $k + 1$ 到 $j - 1$ 都能完全消掉，那么 $i$ 到 $j$ 也全都能消掉。
```
if (s[i] == 'i' && s[j] == 'i' && s[k] == 'w' && f[i + 1][k - 1] == k - i - 1 && f[k + 1][j - 1] == j - k - 1)
	f[i][j] = j - i + 1;
```
上面是关于这种情况的代码。

本题的初值并不需要特殊赋值。
# AC code
```
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int f[310][310];
int main()
{
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;//介绍一种字符串处理操作：在前面加一个空格，就可以让字符串从1到n了
	for (int i = 1; i <= n; i++) f[i][i] = 0;//写不写都可以，初值默认就是0
	for (int len = 2; len <= n; len++)
		for (int i = 1; i <= n - len + 1; i++)
		{
			int j = i + len - 1;
			for (int k = i; k < j; k++)
			{
				f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j]);
				if (s[i] == 'i' && s[j] == 'i' && s[k] == 'w' && f[i + 1][k - 1] == k - i - 1 && f[k + 1][j - 1] == j - k - 1)
					f[i][j] = j - i + 1;
			}
		}
   //区间DP的转移
	cout << f[1][n] / 3 << endl;//输出答案
	return 0;
}
```
# 总结
区间 DP 的初级应用，适合区间 DP 没学好的小蒟蒻（比如我）食用。

只要想到了方法，那么转移方程不难得出，所以关键是想到本题使用区间 DP 来做。

---

## 作者：Wf_yjqd (赞：1)

所以 `iwi` 到底是啥意思？。

------------

考虑区间 dp。

用 $dp_{i,j}$ 表示从 $i$ 到 $j$ 的最大操作数。

枚举断点，肯定可以直接拼接。

如果$i$ 和 $j$ 为 `i`，断点处为 `w`，且两个中间夹着的都删完（即 $dp_{l+1,k-1}\times3=k-l-1$ 且 $dp_{k+1,r-1}\times3=r-k-1$）时，$dp_{i,j}=\frac{r-l+1}{3}$。

总体复杂度 $\operatorname{O}(n^2)$。

------------

这题就挺板的吧。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=384;
int n,dp[maxn][maxn];
char s[maxn];
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i+2<=n;i++)
        if(s[i]=='i'&&s[i+1]=='w'&&s[i+2]=='i')
            dp[i][i+2]=1;
    for(int len=4;len<=n;len++){
        for(int l=1,r;l+len-1<=n;l++){
            r=l+len-1;
            for(int k=l;k<r;k++){
                dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]);
                if(s[l]=='i'&&s[k]=='w'&&s[r]=='i'&&dp[l+1][k-1]*3==k-l-1&&dp[k+1][r-1]*3==r-k-1)
                    dp[l][r]=(r-l+1)/3;
            }
        }
    }
    printf("%d\n",dp[1][n]);
    return 0;
}
```


---

## 作者：makerlife (赞：0)

[更好的阅读体验](https://blog.makerlife.top/post/dp-problems/#TDPC-IWI-%E3%82%A4%E3%82%A6%E3%82%A3) | [Link](https://www.luogu.com.cn/problem/AT_tdpc_iwi)

### Solution

区间 DP，类似合并石子。

我们定义 $f_{i,j}$ 记录 $i$ 到 $j$ 能删掉多少字符，显然最后答案应除以 $3$。

直接按区间 DP 的思路枚举这两个区间之间的分界点 $k$，答案取最大值即可。

本题还需要特判一种特殊情况。如果 $s_i$ 和 $s_j$ 为 `i`，$s_k$ 为 `w`，且中间的两个小段可以被完全删除。那么，当中间的被删掉之后，左右的部分也可以被删掉，需要特判。

### Core Code

```cpp
for(int a=2;a<=len;a++)
{
	for(int i=1;a+i-1<=len;i++)
	{
		int j=a+i-1;
		for(int k=i;k<j;k++)
		{
			f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]);
			if(s[i]=='i' && s[j]=='i' && s[k]=='w' && f[i+1][k-1] == k-i-1 && f[k+1][j-1] == j-1-k)
			{
				f[i][j]=j-i+1;
			}
		}
	}
}
write(f[1][len]/3);
```

---

## 作者：OIer_ACMer (赞：0)

## 第一种题目解析：

本题可以用两种做法。

一种是，我们发现，这道题其实要注意的点就是在删掉一段字符串后可能**会有两边的字符合在一起再次可以删**，所以，我们要考虑左右两边各多出一个能够匹配的字符的情况，而且，顺序也要考虑，我们第一步要先处理左右两边有可匹配字符的情况，在处理左右两边没有可匹配字符的情况。

最后，要注意的是，我们在处理左右两边时要注意下标变化，是加 $1$ 还是不变。

## 第一种代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[1009][1009];
string s;
int len = 0;
int main()
{
    cin >> s;
    len = s.length();
    while (s.find("iwii") != s.npos)
    {
        s.erase(s.find("iwii"), 3);
    }
    // cout << s << endl;
    while (s.find("iiwi") != s.npos)
    {
        // cout << s << endl;
        s.erase(s.find("iiwi") + 1, 3);
    }
    // cout << s << endl;
    while (s.find("iwi") != s.npos)
    {
        s.erase(s.find("iwi"), 3);
    }
    // cout << s << endl;
    int ans = (len - s.length()) / 3;
    cout << ans;
    return 0;
}
```

## 第二种题目解析：

根据第一种~~懒狗~~做法我们可以知道本题其实就是在**不同的区间内寻找能够删除几次目标字符串**，因此我们设 $dp_{i, j}$ 为从 $i$ 到 $j$ 能够删除几次，转移方程式便不难推出：

$$dp_{i, j} = \max(dp_{i, j}, dp_{i, k} +dp_{k +1, j})$$

就是从分割点 $k$ 开始左右两边的答案相加寻找最大答案。不过要注意的是，如果要做到**删掉一段合并后还能再删**就要保证是连续的，不然答案计算后少些情况，要做到这点就是在转移后要看左右端点是否和原目标字符串相应位置匹配，同时动态规划数组结果得和删除长度相同，以保证连续。

## 第二种代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
// int n, m;
string s;
int dp[1009][1009];
int main()
{
    cin >> s;
    int n = s.length();
    // cout << s << endl;
    s = ' ' + s;
    // for (int i = 1; i <= n; i++)
    // {
    //     dp[i][i] = 1;
    // }
    for (int len = 1; len <= n; len++)
    {
        for (int l = 1; l <= n - len + 1; l++)
        {
            int r = l + len - 1;
            for (int k = l; k < r; k++)
            {
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r]);
                if (s[l] == 'i' && s[k] == 'w' && s[r] == 'i' && dp[l + 1][k - 1] == k - l - 1 && dp[k + 1][r - 1] == r - k - 1)
                {
                    dp[l][r] = r - l + 1;
                }
            }
        }
    }
    cout << dp[1][n] / 3 << endl;
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

区间 dp，还有点板。

## Solution AT_tdpc_iwi

### Idea

设 $dp_{i,j}$ 表示 $[i,j]$ 最多能删多少字符。

则有：$dp_{i,j}=\max\{dp_{i,k}+dp_{k+1,j}\}$，其中 $i\le k<j$。

但是这样显然会错误。

考虑下面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/owot4lu6.png)

当 $[i+1,k-1]$ 可以完全被删掉，$[k+1,j-1]$ 可以完全被删掉，$(s_i,s_k,s_j)$ 可以构成 `iwi` 时，显然可以先把 $[i+1,k-1]$ 和 $[k+1,j-1]$ 删掉，然后 $(s_i,s_k,s_j)$ 就会连在一起，然后可以直接删掉。对于这一部分，在代码中加一个特判即可。

最后，这道题比较远古，所以输出末尾务必要加换行。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=305;
int dp[N][N],n;
string s;
int main(){
	cin>>s;
	n=s.length();
	s=' '+s;
	for(int len=1;len<=n;len++){
		for(int i=1,j=len;j<=n;i++,j++){
			for(int k=i;k<j;k++){
				dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
				if(s[i]=='i'&&s[j]=='i'&&s[k]=='w'&&dp[i+1][k-1]==-(i+1)+(k-1)+1&&dp[k+1][j-1]==(j-1)-(k+1)+1)dp[i][j]=j-i+1;
			}
		}
	}
	printf("%d",dp[1][n]/3);
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

### 目的
消掉`iwi`
### 思路解法
区间 **DP**，我们可以定义一个 $f[i][j]$，用它来表示 $i$ 到 $j$ 可以消掉的字符，然后将最后的答案除以 $3$，到这里应该都看得出来。  
考虑一种情况：$i$ 和 $j$ 位置为 $i$，$k$ 为 $w$ 将中间完全消掉。
### 核心代码

```c

	for(int len=2;len<=n;len++){
		for(int j=1;j<=n-len+1;j++){
			i=j+len-1;
			for(int k=j;k<i;k++){
				f[j][i]=max(f[j][i],f[j][k]+f[k+1][i]);
				if(s[j]=='i'&&s[i]=='i'&&s[k]=='w'&&f[j+1][k-1]==k-j-1&&f[k+1][i-1]==i-k-1){
					f[j][i]=i-j+1;
				}
			}
		}
	}
```

---

## 作者：fa_555 (赞：0)

under 题解 [AT688](https://www.luogu.com.cn/problem/AT688)

同步发布于[个人博客](https://fa555.github.io/2020/某At的dp场/#I-イウィ)

### problem

给定一个仅由字符 $\texttt{i}$ 和 $\texttt{w}$ 构成的字符串 $s \ (1 \le |s| \le 300)$。你可以进行若干次操作，每次从串中选取连续的三个字符 $\texttt{iwi}$ 并删除。删除后这三个字符的左侧和右侧会连接在一起，得到一个长度比原来小 $3$ 的新串。求可能的最大操作次数。

### solution & code 1

设 $f_{l, r}$ 表示 $s$ 的子串 $s_{l..r}$ 的答案。这个可以直接枚举分界点 $m \in [l, r)$ 分治转移。

套上记忆化，总复杂度是 $O(n^2)$ 的。

``` cpp
int f[303][303];
std::string s;

int dfs(int l, int r) { // [l, r]
  if (r - l <= 1) return 0;
  if (f[l][r] != -1) return f[l][r];

  int ans = 0;
  for (int m = l; m < r; ++m) {
    ans = std::max(ans, dfs(l, m) + dfs(m + 1, r));
    if (s[l] == 'i' && s[m] == 'w' && s[r] == 'i')
      if (dfs(l + 1, m - 1) == m - l - 1 && dfs(m + 1, r - 1) == r - m - 1)
        ans = r - l + 1;
  }
  return f[l][r] = ans;
}

int solve() {
  memset(f, -1, sizeof f);
  std::cin >> s;
  return dfs(0, s.size() - 1) / 3;
}

```

### solution & code 2

其实这题大可不必 dp。考虑删去一个串 $\texttt{iwi}$ 后当且仅当它的左侧或右侧是 $\texttt{i}$ 才有可能出现一个新的串 $\texttt{iwi}$。

可以首先删去所有的 $\texttt{iwii}$ 和 $\texttt{iiwi}$ 的子串 $\texttt{iwi}$。

总复杂度也是 $O(n^2)$，带一个很小的常数 ~~，具体多小取决于数据强度~~。

``` cpp
std::string s;

int solve() {
  std::cin >> s;
  const int N = s.size();

  for (std::string::size_type p = 0; ; )
    if ((p = s.find("iiwi")) != std::string::npos)
      s.erase(p + 1, 3);
    else if ((p = s.find("iwii")) != std::string::npos)
      s.erase(p, 3);
    else break;

  for (std::string::size_type p = 0; (p = s.find("iwi", p)) != std::string::npos; )
    s.erase(p, 3);

  return (N - s.size()) / 3;
}

```

---

