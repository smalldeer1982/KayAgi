# [GCJ 2021 Qualification] Moons and Umbrellas

## 题目描述

Cody-Jamal 正在创作他最新的抽象艺术作品：一幅由一排渐亏的月亮和闭合的雨伞组成的壁画。不幸的是，贪婪的版权流氓声称渐亏的月亮看起来像大写字母 C，而闭合的雨伞看起来像字母 J，并且他们拥有 CJ 和 JC 的版权。因此，每当壁画中出现 CJ 时，Cody-Jamal 必须支付 $\mathbf{X}$，而出现 JC 时则需支付 $\mathbf{Y}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/sqo2l8si.png)

Cody-Jamal 不愿让他们破坏自己的艺术，因此不会更改已经画好的部分。但他决定，可以通过策略性地填充尚未完成的空白部分来最小化版权费用。

例如，如果 `CJ?CC?` 表示壁画的当前状态，其中 `C` 代表渐亏的月亮，`J` 代表闭合的雨伞，而 `?` 代表需要填充为渐亏月亮或闭合雨伞的空白部分。他可以将壁画完成为 `CJCCCC`、`CJCCCJ`、`CJJCCC` 或 `CJJCCJ`。第一种和第三种选择需要支付 $\mathbf{X} + \mathbf{Y}$ 的版权费用，而第二种和第四种则需要支付 $2 \cdot \mathbf{X} + \mathbf{Y}$。

给定费用 $\mathbf{X}$ 和 $\mathbf{Y}$ 以及一个表示壁画当前状态的字符串，如果 Cody-Jamal 以最小化成本的方式完成壁画，他需要支付多少版权费用？

## 说明/提示

**样例解释**

样例 #1 是题目描述中解释的情况。最小费用为 $\mathbf{X} + \mathbf{Y} = 2 + 3 = 5$。

在样例 #2 中，Cody-Jamal 已经完成了壁画，因此无法选择。壁画中有两个 `CJ` 和一个 `JC`。

在样例 #3 中，无论是将 `?` 替换为 `C` 还是 `J`，都会在第二和第三个字符或第一和第二个字符之间形成一个 `CJ`。

在样例 #4 中，Cody-Jamal 可以将壁画全部填充为 `J`。由于这既不包含 `CJ` 也不包含 `JC`，因此不需要支付版权费用。

以下附加样例 2 符合测试集 3 的限制，但不会在提交的解决方案中运行。

在测试集 3 的样例 #1 中，Cody-Jamal 可以最优地将壁画完成为 `JCJJCC` 或 `JCJJJC`。无论哪种方式，壁画中都有一个 `CJ` 和两个 `JC`。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $\mathbf{S}$ 中的每个字符为 $\mathbf{C}$、$\mathbf{J}$ 或 $\mathbf{?}$。

**测试集 1（5 分，可见判定结果）**

- $1 \leq \mathbf{S}$ 的长度 $\leq 10$。
- $1 \leq \mathbf{X} \leq 100$。
- $1 \leq \mathbf{Y} \leq 100$。

**测试集 2（11 分，可见判定结果）**

- $1 \leq \mathbf{S}$ 的长度 $\leq 1000$。
- $1 \leq \mathbf{X} \leq 100$。
- $1 \leq \mathbf{Y} \leq 100$。

**额外奖励！**

如果某些版权持有者反而会支付 Cody-Jamal 广告费而不是向他收费呢？Cody-Jamal 获得报酬的情况用负成本表示。

**测试集 3（1 分，隐藏判定结果）**

- $1 < \mathbf{S}$ 的长度 $< 1000$。
- $-100 \leq \mathbf{X} \leq 100$。
- $-100 \leq \mathbf{Y} \leq 100$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2 3 CJ?CC?
4 2 CJCJ
1 3 C?J
2 5 ??J???```

### 输出

```
Case #1: 5
Case #2: 10
Case #3: 1
Case #4: 0```

## 样例 #2

### 输入

```
1
2 -5 ??JJ??```

### 输出

```
Case #1: -8```

# 题解

## 作者：qkj_qwq (赞：3)

## 解题思路

动态规划。

设 $f_i$ 为当前点选 $\texttt{C}$，$g_i$ 为当前点选 $\texttt{J}$，所以初始化易得。

然后分情况讨论：

- 当 $a_i=\texttt{C}$ 时，若 $a_{i-1}=\texttt{C}$，不用支付版权费用；若 $a_{i-1}=\texttt{J}$，支付 $y$ 版权费用。转移方程为 $f_i=\min(f_{i-1},g_{i-1}+y)$
- 当 $a_i=\texttt{J}$ 时，若 $a_{i-1}=\texttt{J}$，不用支付版权费用；若 $a_{i-1}=\texttt{C}$，支付 $x$ 版权费用。转移方程为 $g_i=\min(g_{i-1},f_{i-1}+x)$
- 当 $a_i=\texttt{?}$ 时，分别把问号当做 $\texttt{C}$ 和 $\texttt{J}$ 进行转移。把上面两个转移方程都复制一遍即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[1010],g[1010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		memset(f,63,sizeof f);
		memset(g,63,sizeof g);
		int x,y;
		string a;
		cin>>x>>y>>a;
		if(a[0]=='?')f[0]=g[0]=0;
		else if(a[0]=='C')f[0]=0;
		else g[0]=0;
		for(int i=1;i<a.size();i++)
			if(a[i]=='?')
			{
				f[i]=min(f[i-1],g[i-1]+y);
				g[i]=min(g[i-1],f[i-1]+x);
			}
			else if(a[i]=='C')f[i]=min(f[i-1],g[i-1]+y);
			else g[i]=min(g[i-1],f[i-1]+x);
		cout<<min(f[a.size()-1],g[a.size()-1])<<'\n';
	}
	return 0;
}
```

---

## 作者：ryf_loser (赞：1)

此题简单线性动态规划。

想到设 $dp_{i,0/1}$ 表示第 $i$ 个位置选 `C` 和 `J` 所用的最小值。

因为需要知道两个字符，我们判断 $i-1$ 状态：

1. $i-1$ 为 `C`，若 $i$ 状态为 `J`，则需要加价值 $X$，其余延续。

2. $i-1$ 为 `J`，若 $i$ 状态为 `C`，则需要加价值 $Y$，其余延续。

3. $i-1$ 为 `?`，将以上两种情况相结合，要枚举 `C` 和 `J` 两种情况。

那么再次判断 $i$ 状态即可，若为 `C` 和 `J` 仅需要转移 $dp_{i,0}$ 和 $dp_{i,1}$ 即可。若为 `?` 需要转移 $dp_{i,0/1}$ 两种状态。

其中 `CJ` 状态转移为 $dp_{i,1}=\min(dp_{i-1,0}+x,dp_{i-1,1})$，
`JC` 状态转移为 $dp_{i,0}=\min(dp_{i-1,1}+y,dp_{i-1,0})$。

AC CODE

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline int in(){//快读
	int x=0,f=1;char c;
	c=getchar();
	while (c<'0'||c>'9'){
		if (c=='-')f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
} 
int t,x,y,n,dp[1005][2];
char ch[1005];
int main(){
	t=in();
	for (int w=1;w<=t;w++){
		memset(dp,0x3f,sizeof dp);//初始化最大值
		x=in();y=in();
		scanf ("%s",ch+1);//字符串读入
		n=strlen(ch+1);//读取字符串长度
		dp[1][0]=dp[1][1]=0;
		for (int i=2;i<=n;i++){
			if (ch[i]=='?'){//问号的转移
				if (ch[i-1]=='?'){
					dp[i][0]=min(dp[i-1][1]+y,dp[i-1][0]);
					dp[i][1]=min(dp[i-1][0]+x,dp[i-1][1]);
				}
				else if (ch[i-1]=='C'){
					dp[i][0]=dp[i-1][0];
					dp[i][1]=dp[i-1][0]+x;
				}
				else{
					dp[i][1]=dp[i-1][1];
					dp[i][0]=dp[i-1][1]+y;
				}
			}
			else if (ch[i]=='C'){//C 转移
				if (ch[i-1]=='?')dp[i][0]=min(dp[i-1][1]+y,dp[i-1][0]);
				else if (ch[i-1]=='J')dp[i][0]=dp[i-1][1]+y;
				else dp[i][0]=dp[i-1][0];
			}
			else {//J 转移
				if (ch[i-1]=='?')dp[i][1]=min(dp[i-1][0]+x,dp[i-1][1]);
				else if (ch[i-1]=='C')dp[i][1]=dp[i-1][0]+x;
				else dp[i][1]=dp[i-1][1];
			}
		}
		printf ("Case #%d: %d\n",w,min(dp[n][0],dp[n][1]));//输出
	}
	return 0;
}
```

---

## 作者：bsb543263w57843356 (赞：1)

# P13022 [GCJ 2021 Qualification] Moons and Umbrellas

## 题目简述

题目很短，可以轻松理解。

## 题目分析

要求最小要交的版权费，我们可以使用动态规划。设 $dp[i][0]$ 是选 `C` 的最小值，$dp[i][1]$ 是选 `J` 的最小值。那么根据题目，动态转移方程可以分成三种情况。

- 当 $s _ {i-1}$ 为 `?` 时：$$dp[i][0]=\min(dp[i-1][1]+y,dp[i-1][0])$$，$$dp[i][1]=\min(dp[i-1][0]+x,dp[i-1][1])$$。

- 当 $s _ {i-1}$ 为 `C` 时：$$dp[i][0]=dp[i-1][0]$$，$$dp[i][1]=dp[i-1][0]+x$$。


- 当 $s _ {i-1}$ 为 `J` 时：$$dp[i][0]=dp[i-1][1]+y$$，$$dp[i][1]=dp[i-1][1]$$。

最后根据 $s _ {n-1}$ 的字符来更新答案。

## Code

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,dp[100001][3],ans1,ans2;
signed main(){
    cin>>t;
    int nn = t;
    for(int p=1;p<=t;++p){
        int x,y;cin>>x>>y;
		string s;cin>>s;
		int n=s.size();
		dp[0][0]=dp[0][1]=0;
		for(int i=1;i<n;i++) {
			if(s[i-1]=='?'){
				dp[i][0]=min(dp[i-1][1]+y,dp[i-1][0]);
				dp[i][1]=min(dp[i-1][0]+x,dp[i-1][1]);
			}
			else if(s[i-1]=='C'){
				dp[i][0]=dp[i-1][0];
				dp[i][1]=dp[i-1][0]+x;
			}
			else{//剩下s[i-1]是J的情况 
				dp[i][0]=dp[i-1][1]+y;
				dp[i][1]=dp[i-1][1];
			}
		}
		int ans;
		if(s[n-1]=='?') ans = min(dp[n-1][0], dp[n-1][1]);
		else if(s[n-1]=='C') ans = dp[n-1][0];
		else ans = dp[n-1][1]; //最终答案要看s[n-1] 
		cout<<"Case #"<<p<<": "<<ans<<endl;
    }
}
```

---

## 作者：Sheep_YCH (赞：1)

## 洛谷 P13022

[题目传送门](https://www.luogu.com.cn/problem/P13022)

## 题目大意

原题面已经表述的很清晰了，相信各位巨佬可以看得懂。。。

## 题目分析

简单的**动态规划**题目（标签大法好）。

记 $dp[i][0]$ 为第 $i$ 个位置选择字母 `C` 的最小费用，$dp[i][1]$ 为第 $i$ 个位置选择字母 `J` 的最小费用。

记 $A[i][0]$ 为第 $i$ 个位置可以选择字母 `C`，$A[i][1]$ 为第 $i$ 个位置可以选择字母 `J`。

- 当第 $i - 1$ 个字符为 `?` 时：

  - $dp[i][0] = min(dp[i - 1][1] + y, dp[i - 1][0])$

  - $dp[i][1] = min(dp[i - 1][0] + x, dp[i - 1][1])$

- 当第 $i - 1$ 个字符为 `C` 时：
  - $dp[i][0] = dp[i - 1][0]$
  - $dp[i][1] = dp[i - 1][0] + x$

- 当第 $i - 1$ 个字符为 `J` 时：
  - $dp[i][0] = dp[i - 1][1] + y$
  - $dp[i][1] = dp[i - 1][1]$

还有不懂的看代码注释。

## Code

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <queue>
#include <stack>
#define ll long long
using namespace std;
const int MAXN = 1e6 + 5;
const int INF = 2e9 + 5;

int dp[MAXN][2];
bool A[MAXN][2];

void Solve() {
	int x, y; cin >> x >> y;
	string S; cin >> S;
	int n = S.size();
	for(int i = 0; i < n; i ++) {
		A[i][0] = A[i][1] = 1;
		if(S[i] == 'C') A[i][1] = 0; // 不能为 J 
		if(S[i] == 'J') A[i][0] = 0; // 不能为 C
	}
	dp[0][0] = dp[0][1] = 0;  // 不要忘记初始化
	for(int i = 1; i < n; i ++) {
		if(A[i - 1][0] && A[i - 1][1]) { // i-1为 ?
			dp[i][0] = min(dp[i - 1][1] + y, dp[i - 1][0]); // JC
			dp[i][1] = min(dp[i - 1][0] + x, dp[i - 1][1]); // CJ
		}
		else if(A[i - 1][0]) { // i-1为 C
			dp[i][0] = dp[i - 1][0];
			dp[i][1] = dp[i - 1][0] + x; // CJ
		}
		else { // i-1为 J
			dp[i][0] = dp[i - 1][1] + y; // JC
			dp[i][1] = dp[i - 1][1];
		}
	}
	int ans = INF;
	if(A[n - 1][0] && A[n - 1][1]) ans = min(dp[n - 1][0], dp[n - 1][1]);
	else if(A[n - 1][0]) ans = dp[n - 1][0];
	else ans = dp[n - 1][1];
	cout << ans;
	return ;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T; cin >> T;
	for(int Case = 1; Case <= T; Case ++) {
		cout << "Case #" << Case << ": ";
		Solve();
		cout << "\n";
	}
	
	return 0;

}
```

---

## 作者：_NaOH_ (赞：1)

## 题意简述

给定由字符 `C`、`J` 和 `?` 组成的字符串 $S$，需要将每个 `?` 替换为 `C` 或 `J`，使得总版权费用最小。收费规则如下：

- 每出现一个子串 `CJ`，花费 $X$。
- 每出现一个子串 `JC`，花费 $Y$。

值得注意的是，$X$ 和 $Y$ 均可能是负数，这便意味着可以通过刻意制造字串（`CJ` 或 `JC`）以获得收益（即支付负的费用）。

## 问题分析

首先想到枚举每个 `?` 处可能的字符。但，按题目所述，最多可能有 $1000$ 个 字符 `?`，时间复杂度为 $\mathcal{O}(2^{|S|})$，不可行。

再次阅读题目，发现 $S$ 的每一位上都只能选填 `C` 或 `J`，我们可以用 `0` 表示选填 `C` 的情况，反之用 `1` 表示选填 `J` 的情况。于是，自然而然地想到使用动态规划。

定义两个状态数组：

- $dp_{i,0}$：表示处理到第 $i$ 个字符且选填 `C` 时的最小费用。
- $dp_{i,1}$：表示处理到第 $i$ 个字符且选填 `J` 时的最小费用。

于是得到状态转移方程为：
$$
\begin{cases}
    dp_{i,0} \gets \min(dp_{i-1,0},\ dp_{i-1,1} + Y)  ,& \text{当} S_i \in \{\texttt{C}, \texttt{?}\} \\
    dp_{i,1} \gets \min(dp_{i-1,0} + X,\ dp_{i-1,1}) ,& \text{当 } S_i \in \{\texttt{J}, \texttt{?}\}
\end{cases}
$$

另外，由题目可知，第一个字符所产生的费用为 $0$，因为前面没有字符可与其构成收费的子串。所以，处理边界条件：

$$
\begin{cases}
    dp_{0,0} \gets 0 ,& \text{当 } S_0 \in \{\texttt{C}, \texttt{?}\} \\
    dp_{0,1} \gets 0 ,& \text{当 } S_0 \in \{\texttt{J}, \texttt{?}\}
\end{cases}
$$

答案即为 $\min(dp_{n-1,0}, dp_{n-1,1})$。

时间复杂度为 $\mathcal{O}(T \cdot |S|)$。

## AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll INF=1e15;
const int N=1010;
ll dp0[N],dp1[N],X,Y,len,ans;
int T;
string S;
int main()
{
    cin>>T;
    for(int test=1;test<=T;test++)
	{
        cin>>X>>Y>>S;
        
		len=S.size();
        fill(dp0,dp0+len,INF);
        fill(dp1,dp1+len,INF);
        if(S[0]=='C') dp0[0]=0; //处理第一个字符的状态
        else if(S[0]=='J') dp1[0]=0;
		else dp0[0]=dp1[0]=0;
		
        for(int i=1;i<len;i++) //状态转移
		{
            if(S[i]=='C' || S[i]=='?')
			{
                dp0[i]=min(dp0[i-1],dp1[i-1]+Y);
            }
            if(S[i]=='J' || S[i]=='?')
			{
                dp1[i]=min(dp0[i-1]+X,dp1[i-1]);
            }
        }
        ans=min(dp0[len-1],dp1[len-1]);
        cout<<"Case #"<<test<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：aaa1145141919810 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P13022)

# 算法分析
题目大意：题目写的很清楚了。

仔细观察后我们可以发现，这道题非常像一道动态规划的题目，那么接下来就是我们的动规三板斧：

## 定义状态

这道题目的答案与当前位置所选的字母有关，字母只有 `C` 和 `J` 两种选择，故我们用 $0$ 来表示 `J`，$1$ 来表示 `C`；

那么状态表示就呼之欲出了：$dp_{i,j}$ 表示考虑前 $i$ 个位置，且在第 $i$ 个位置上选择 $j$ 所表示的字符时，所能达成的最小成本。

## 初始状态

初始状态分为两部分：边界与全局。这题作为黄题，初始状态相当明晰：因为求最小值，全局初始为 $+\infty$ ；边界为 $i=1$，考虑不同的字符串开头的影响，若不为 `J`，则 $dp_{1,1}=0$，若不为 `C`，则 $dp_{1,0}=0$。

形式化的，初始状态为：
$$dp_{i,j}=\begin{cases}
0 & S_0\ne\text{J 且 }j=1\text{ 或 }S_0\ne\text{C 且 }j=0\\
+\infty & \text{others}
\end{cases}$$

## 状态转移方程

分析题意，可以发现**当前一个字符为 `J` 且当前字符为 `C` 时**代价增加 $y$。转化为转移方程则是 $dp_{i,1}=\min(dp_{i-1,1},dp_{i-1,0}+y)$。

类似的，**当前一个字符为 `C` 且当前字符为 `J` 时**代价增加 $x$，方程为 $dp_{i,0}=\min(dp_{i-1,0},dp_{i-1,1}+x)$。

将以上两个方程综合，就有本题的转移方程：
$$
\begin{cases}
dp_{i,0}=\min(dp_{i-1,0},dp_{i-1,1}+x) & S_i\ne\text{C}\\
dp_{i,1}=\min(dp_{i-1,1},dp_{i-1,0}+y) & S_i\ne\text{J}
\end{cases}$$

同时由以上方程可以得出，$\min(dp_{|S|,0},dp_{|S|,1})$ 就是最终答案。这是因为当字符串结尾为 `?` 时两种答案一定取较小值，而为 `J` 或是 `C` 时不能填的那个答案值一定为 $+\infty$。所以直接在两个答案中取较小值即可。

# AC 代码 & 记录

有了以上的推导过程，我们就可以切了这道题了，如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e3+5;
int n, dp[N][2], T, x, y;
string s;

int main() {
	cin >> T;
	
	for(int j = 1; j <= T; j++) {
		cin >> x >> y >> s;
		s = ' ' + s;
		memset(dp, 0x3f, sizeof dp);
		if(s[1] == 'J')dp[1][0] = 0;
		if(s[1] == 'C')dp[1][1] = 0;
		if(s[1] == '?')dp[1][1] = dp[1][0] = 0;
		n = s.size()-1;
		
		for(int i = 2; i <= n; i++) {
			if(s[i] != 'J') {
				dp[i][1] = min(dp[i-1][1], dp[i-1][0] + y);
			}
			if(s[i] != 'C') {
				dp[i][0] = min(dp[i-1][0], dp[i-1][1] + x); 
			}
		}
		printf("Case #%d: %d\n", j, min(dp[n][1], dp[n][0]));
	}
	
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/222708650)。

---

## 作者：W_C_B_H (赞：0)

题意简述：定义一个字符串的权值为该串中 `CJ` 字串的个数乘以 $X$ 加上 `JC` 字串的个数乘以 $Y$。多组测试数据，每组中分别给定整数 $X,Y$（$|X|,|Y|\le100$）和一个仅由 `C`,`J`,`?` 构成的字符串 $S$（$|S|\le1000$），$S$ 中每个 `?` 都可以被替换为 `C` 或 `J`，求每个 `?` 都被替换后 $S$ 的权值的最小值。

考虑 dp。设 $dp_{i,j}$ 表示考虑 $S$ 的前 $i$ 个字符，且第 $i$ 个字符是 $j$ 时（第一维下标从 $1$ 开始，$j=0$ 表示 `C`，$j=1$ 表示 `J`，若原本 $S_i$ 为 `?` 则 $j$ 表示替换 $S_i$ 的字符）的最小权值，若 $S_i$ 不能为 $j$ 则 $dp_{i,j}=+\infty$。不难想到初始状态为 $dp_{1,0}=\begin{cases}0&\text{if }S_1\ne\texttt{J}\\+\infty&\text{if }S_1=\texttt{J}\end{cases},dp_{1,1}=\begin{cases}0&\text{if }S_1\ne\texttt{C}\\+\infty&\text{if }S_1=\texttt{C}\end{cases}$，且其余均为 $+\infty$。

状态转移方程：

- $dp_{i,0}=\begin{cases}\min\{dp_{i-1,0},dp_{i-1,1}+Y\}&\text{if }S_i\ne\texttt{J}\\+\infty&\text{if }S_i=\texttt{J}\end{cases}$；

- $dp_{i,1}=\begin{cases}\min\{dp_{i-1,0}+X,dp_{i-1,1}\}&\text{if }S_i\ne\texttt{C}\\+\infty&\text{if }S_i=\texttt{C}\end{cases}$。

最终答案即为 $\min\{dp_{|S|,0},dp_{|S|,1}\}$。单组测试数据时间复杂度 $O(|S|)$，总时间复杂度 $O(T\times|S|)$，可以通过本题。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define setinf(a) memset((a),0x3f,sizeof((a)))
int read()
{
	int r=0; char c=getchar(); bool f=0;
	while(c<48 || c>57){ if(c=='-'){ f=1; } c=getchar(); }
	while(c>=48 && c<=57){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return f?-r:r;
}
string readstr()
{
	string r=""; char c=getchar();
	while(c==' ' || c=='\n' || c=='\r') c=getchar();
	while(c!=' ' && c!='\n' && c!='\r' && c!=EOF){ r+=c; c=getchar(); }
	return r;
}
void write(int x)
{
	if(x<0){ putchar('-'); x=-x; }
	if(x>9){ write(x/10); }
	putchar(x%10+48);
}
void write(string x){ for(char c:x) putchar(c); }
void writeln(int x){ write(x); putchar('\n'); }
void writeln(string x){ write(x); putchar('\n'); }
#define N 1005
int T,x,y,n,dp[N][2];
string s;
signed main()
{
	T=read();
	for(int t=1;t<=T;t++)
	{
		x=read(), y=read();
		s=readstr();
		n=s.length();
		s=" "+s;
		setinf(dp);
		if(s[1]=='C')
		{
			dp[1][0]=0;
		}
		else if(s[1]=='J')
		{
			dp[1][1]=0;
		}
		else
		{
			dp[1][0]=dp[1][1]=0;
		}
		for(int i=2;i<=n;i++)
		{
			if(s[i]!='J')
			{
				dp[i][0]=min(dp[i-1][0],dp[i-1][1]+y);
			}
			if(s[i]!='C')
			{
				dp[i][1]=min(dp[i-1][0]+x,dp[i-1][1]);
			}
		}
		write("Case #");
		write(t);
		write(": ");
		writeln(min(dp[n][0],dp[n][1]));
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13022)

题目大意：给你一个字符串 $s$，其中含有字符 `C`、`J` 和 `?`。$s$ 中每出现一次子串 `CJ` 就增加 $x$ 的费用，每出现一次子串 `JC` 就增加 $y$ 的费用。现在要求把所有的 `?` 改为 `C` 或 `J`，求最小花费。

一眼 DP。

令 $dp_{i,0}$ 为第 $i$ 位为 `C` 时前 $i$ 个字符的最小花费，$dp_{i,1}$ 为第 $i$ 位为 `J` 时前 $i$ 个字符的最小花费。

显然当 $s_i=\texttt{C}$ 时 $dp_{i,1}=\inf$（因为没有这种情况），$s_i=\texttt{J}$ 时 $dp_{i,0}=\inf$。

当 $s_i=\texttt{C}$ 时，如果 $s_{i-1}=\texttt{C}$ 则没有增加花费，而当 $s_{i-1}=\texttt{J}$ 时则会增加 $y$ 的花费。$s_i=\texttt{J}$ 时同理。

于是我们可以推出式子：

$$dp_{i,0}=\begin{cases}\inf & s_i=\texttt{J}\\ \min(dp_{i-1,0},dp_{i-1,1}+y) & s_i\neq \texttt{J}\end{cases}$$

同理：

$$dp_{i,1}=\begin{cases}\inf & s_i=\texttt{C}\\ \min(dp_{i-1,1},dp_{i-1,0}+x) & s_i\neq \texttt{C}\end{cases}$$

代码：

```cpp
//copper_ingot
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
pii mkp(int x, int y){pii p; p.first = x, p.second = y; return p;}
int t, x, y, n, dp[2001][2]; char s[2001];
const int inf = 2147483647;
signed main(){
	scanf("%lld", &t);
	for (int cs = 1; cs <= t; cs++){
		scanf("%lld%lld%s", &x, &y, s + 1);
		n = strlen(s + 1);
		dp[1][0] = dp[1][1] = 0;
		if (s[1] == 'C') dp[1][1] = inf;
		else if (s[1] == 'J') dp[1][0] = inf;//初始化
		for (int i = 2; i <= n; i++){
			if (s[i] == 'C'){
				dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + y);
				dp[i][1] = inf;
			}
			else if (s[i] == 'J'){
				dp[i][0] = inf;
				dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + x);
			}
			else{
				dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + y);
				dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + x);
			}
		}
		printf("Case #%lld: %lld\n", cs, min(dp[n][0], dp[n][1]));//答案取min
	}
	return 0;
}
```

---

