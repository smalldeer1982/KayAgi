# [ABC303D] Shift vs. CapsLock

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc303/tasks/abc303_d

あなたのパソコンのキーボードには、a キー・Shift キー・CapsLock キーの $ 3 $ 種類のキーがあります。また、CapsLock キーにはランプが付いています。 初め、CapsLock キーのランプは OFF であり、パソコンの画面には空文字列が表示されています。

あなたは、以下の $ 3 $ 種類の操作のうち $ 1 $ つを選んで実行するということを $ 0 $ 回以上何度でも行うことができます。

- $ X $ ミリ秒かけて a キーのみを押す。CapsLock キーのランプが OFF ならば画面の文字列の末尾に `a` が付け足され、ON ならば `A` が付け足される。
- $ Y $ ミリ秒かけて Shift キーと a キーを同時に押す。CapsLock キーのランプが OFF ならば画面の文字列の末尾に `A` が付け足され、 ON ならば `a` が付け足される。
- $ Z $ ミリ秒かけて CapsLock キーを押す。CapsLock キーのランプが OFF ならば ON に、ON ならば OFF に切り替わる。

`A` と `a` からなる文字列 $ S $ が与えられます。画面の文字列を $ S $ に一致させるのに必要な最短の時間は何ミリ秒かを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X,Y,Z\ \leq\ 10^9 $
- $ X,Y,Z $ は整数
- $ 1\ \leq\ |S|\ \leq\ 3\ \times\ 10^5 $
- $ S $ は `A` と `a` からなる文字列

### Sample Explanation 1

以下のように操作を行うと $ 9 $ ミリ秒で画面の文字列を `AAaA` に一致させられます。これが最短の時間です。 - $ Z(=3) $ ミリ秒かけて CapsLock キーを押す。CapsLock キーのランプが ON になる。 - $ X(=1) $ ミリ秒かけて a キーを押す。`A` が画面の文字列の末尾に付け足される。 - $ X(=1) $ ミリ秒かけて a キーを押す。`A` が画面の文字列の末尾に付け足される。 - $ Y(=3) $ ミリ秒かけて Shift キーと a キーを同時に押す。`a` が画面の文字列の末尾に付け足される。 - $ X(=1) $ ミリ秒かけて a キーを押す。`A` が画面の文字列の末尾に付け足される。

## 样例 #1

### 输入

```
1 3 3
AAaA```

### 输出

```
9```

## 样例 #2

### 输入

```
1 1 100
aAaAaA```

### 输出

```
6```

## 样例 #3

### 输入

```
1 2 4
aaAaAaaAAAAaAaaAaAAaaaAAAAA```

### 输出

```
40```

# 题解

## 作者：2huk (赞：4)

## 题目描述

你需要用电脑打一串由 `a` 和 `A` 组成的字符串。你的键盘上有 $3$ 个按键，分别是 `a` 按键、`Shift` 按键，`Capslock` 按键。你可以执行以下操作任意次：

- 花 $x$ 毫秒时间按 `a` 按键。如果此时 `Capslock` 的指示灯是灭的，打印 `a`。否则打印 `A`。
- 花 $y$ 毫秒时间按 `a` + `Shift` 按键。如果此时 `Capslock` 的指示灯是灭的，打印 `A`。否则打印 `a`。
- 花 $z$ 毫秒时间按 `Capslock` 按键。如果此时 `Capslock` 的指示灯是灭的，则将指示灯变亮。否则变灭。

问最少需要花多少毫秒。

$1 \le x, y, z \le 10^9,\ 1 \le \left| S \right| \le 3 \times 10^5$

## 分析

考虑 `DP`。

显然状态中需要有一维表示当前正在打字的位置，其次还需要知道当前的 `Capslock` 的状态。所以设 $f_{i, 0/1}$ 表示打完前 $i$ 个字符，且打完后的状态为大写 / 小写所需要花的最少时间。显然答案为 $\min(f_{n, 0},f_{n,1})$，表示打完前 $n$ 个字符后状态为大写或小写所需要花的最少时间。

考虑边界。由于最开始时 `Capslock` 的状态为小写，所以前 $0$ 个字符打完后状态为大写的情况是不存在的。所以 $f_{0, 0} = +\infty$。

接下来考虑转移。转移过程相对繁琐，以下是递推式：

$$
f_{i, 0} = \left\{\begin{matrix}\min(f_{i - 1, 0} + \min(x, z + y + z), f_{i - 1, 1} + \min(z + x, y + z)) & (S_i = \texttt{'A'})\\\min(f_{i - 1, 0} + \min(y, z + x + z), f_{i - 1, 1} + \min(x + z, z + y)) & (S_i = \texttt{'a'})\end{matrix}\right.
$$
$$
f_{i, 1} = \left\{\begin{matrix}\min(f_{i - 1, 0} + \min(x + z, z + y), f_{i - 1, 1} + \min(y, z + x + z))  & (S_i = \texttt{'A'})\\\min(f_{i - 1, 0} + \min(z + x, y + z), f_{i - 1, 1} + \min(x, z + y + z))  & (S_i = \texttt{'a'})\end{matrix}\right.
$$

接下来分 $8$ 种情况分析。

- 大写 $\to \texttt{'A'} \to$ 大写：
  
  首先打完前 $i - 1$ 个字符后的状态为大写的最少时间为 $f_{i - 1, 0}$，先将答案加上。
  
  对于这种情况，可以直接按 `a` 打出 `A`。也可以先换成小写，再按 `Shift` + `a` 打出 `A`，再切换成大写。
  
  因此答案为 $f_{i - 1, 0} + \min(x, z + y + z)$。
- 小写 $\to \texttt{'A'} \to$ 大写：
  
  首先打完前 $i - 1$ 个字符后的状态为小写的最少时间为 $f_{i - 1, 1}$，先将答案加上。
  
  对于这种情况，可以先切换成大写，再直接按 `a` 打出 `A`。也可以先按 `Shift` + `a` 打出 `A`，再切换成大写。
  
  因此答案为 $f_{i - 1, 1} + \min(z + x, y + z)$。
- 大写 $\to \texttt{'a'} \to$ 大写：
  
  首先打完前 $i - 1$ 个字符后的状态为大写的最少时间为 $f_{i - 1, 0}$，先将答案加上。
  
  对于这种情况，可以直接按 `Shift` + `a` 打出 `a`。也可以先切换成小写，再直接按 `a` 打出 `a`，再切换成大写。
  
  因此答案为 $f_{i - 1, 0} + \min(y, z + x + z)$。
- 小写 $\to \texttt{'a'} \to$ 大写：
  
  首先打完前 $i - 1$ 个字符后的状态为小写的最少时间为 $f_{i - 1, 1}$，先将答案加上。
  
  对于这种情况，可以先直接按 `a` 打出 `a`，再切换成大写。也可以先切换成大写，再按 `Shift` + `a` 打出 `a`。
  
  因此答案为 $f_{i - 1, 1} + \min(x + z, z + y)$。
- 大写 $\to \texttt{'A'} \to$ 小写：
  
  首先打完前 $i - 1$ 个字符后的状态为大写的最少时间为 $f_{i - 1, 0}$，先将答案加上。
  
  对于这种情况，可以先直接按 `a` 打出 `A`，再切换成小写。也可以先切换成小写，再按 `Shift` + `a` 打出 `A`。
  
  因此答案为 $f_{i - 1, 0} + \min(x + z, z + y)$。
- 小写 $\to \texttt{'A'} \to$ 小写：
  
  首先打完前 $i - 1$ 个字符后的状态为小写的最少时间为 $f_{i - 1, 1}$，先将答案加上。
  
  对于这种情况，可以直接按 `Shift` + `a` 打出 `A`。也可以先切换成大写，再直接按 `a` 打出 `A`，再切换成小写。
  
  因此答案为 $f_{i - 1, 1} + \min(y, z + x + z)$。
- 大写 $\to \texttt{'a'} \to$ 小写：
  
  首先打完前 $i - 1$ 个字符后的状态为大写的最少时间为 $f_{i - 1, 0}$，先将答案加上。
  
  对于这种情况，可以先切换成小写，再直接按 `a` 打出 `a`。也可以先按 `Shift` + `a` 打出 `a`，再切换成小写。
  
  因此答案为 $f_{i - 1, 0} + \min(z + x, y + z)$。
- 小写 $\to \texttt{'a'} \to$ 小写：
  
  首先打完前 $i - 1$ 个字符后的状态为小写的最少时间为 $f_{i - 1, 1}$，先将答案加上。
  
  对于这种情况，可以直接按 `a` 打出 `a`。也可以先换成大写，再按 `Shift` + `a` 打出 `a`，再切换成小写。
  
  因此答案为 $f_{i - 1, 1} + \min(x, z + y + z)$。

转移过程十分复杂，需要耐心求解。

[$\text{Code}$](https://www.luogu.com.cn/paste/dbjn6a4p)


---

## 作者：lilong (赞：4)

看到本题，很容易想到贪心，对每一段相同的子串计算最小代价。但这种思路的评测结果显示有 $3$ 个测试点 WA 了，因此解法错误。既然贪心行不通，我们不妨使用 dp，对每一位进行分类讨论并求最小耗时。

设 $dp_{i,j}$ 表示 Capslock 状态为 $j$ 时（$j$ 为 $0$ 或$1$，$0$ 表示熄灯，$1$ 表示亮灯），前 $i$ 位的最小耗时，接下来具体分析状态转移方程：

记 $s_i$ 表示 $s$ 中下标为 $i$ 的字符。

- $s_i = s_{i - 1}$

这种情况下有如下状态转移方程：

1. 若 $s_i$ 为 A，则有

$$dp_{i,0} =  \min( dp_{i-1,0} + y ,dp_{i-1,1} + z + y ) $$

$$dp_{i,1} =  \min( dp_{i-1,0} + z + x,dp_{i-1,1} + x )$$

2. 若 $s_i$ 为 a，则有

$$dp_{i,0} =  \min( dp_{i-1,0} + x ,dp_{i-1,1} + z + x ) $$

$$dp_{i,1} =  \min( dp_{i-1,0} + z + y,dp_{i-1,1} + y )$$

- $s_i \ne s_{i - 1}$

推导过程同理，这里略过。

### 总结

这些式子看起来很长，其实理解起来并不难：**先看状态是否一致**，不一致则加上 $z$，**然后再看只按 a 是否为需要的字母**，如果不是则加上 $y$，否则加上 $x$。

具体实现如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long

using namespace std;

int x,y,z,len,l,nw;
int ans;
int dp[1000001][2];
char s[1000001];

signed main()
{
	cin >> x >> y >> z;
	cin >> s;
	len = 1;
	if( s[0] == 'a' )
	{
		dp[0][0] = x;
		dp[0][1] = z + y;
	}
	else
	{
		dp[0][0] = y;
		dp[0][1] = z + x;
	}
	l = strlen(s);
	for( int i = 1 ; i < l ; i ++ )
	{
		if( s[i] == s[i - 1] )
		{
			if( s[i] == 'A' )
			{
				dp[i][0] = min( dp[i - 1][0] + y , dp[i - 1][1] + z + y );
				dp[i][1] = min( dp[i - 1][0] + z + x , dp[i - 1][1] + x );
			}
			else
			{
				dp[i][0] = min( dp[i - 1][0] + x , dp[i - 1][1] + z + x );
				dp[i][1] = min( dp[i - 1][0] + z + y , dp[i - 1][1] + y );
			}
		}
		else
		{
			if( s[i - 1] == 'A' )
			{
				dp[i][0] = min( dp[i - 1][0] + x , dp[i - 1][1] + x + z );
				dp[i][1] = min( dp[i - 1][0] + z + y , dp[i - 1][1] + y );
			}
			else
			{
				dp[i][0] = min( dp[i - 1][0] + y , dp[i - 1][1] + z + y );
				dp[i][1] = min( dp[i - 1][0] + z + x , dp[i - 1][1] + x );
			}
		}
	}
	cout << min( dp[l - 1][0] , dp[l - 1][1] );
	return 0;
}
```


---

## 作者：__Emerald__ (赞：3)

可以考虑 $\text{dp}$。设 $\text{dp}_{i,j}$ 为打印前 $i$ 个字符需要的时间，$j=0$ 时为打印完后 Capslock 键上面的灯是关着的最短时间，$j=1$ 时是打印完后 Capslock 上面的灯亮着的最短时间。

仅需考虑以下4种情况：

- 花 $X$ 毫秒按下 `a` 键；

- 花 $Y$ 毫秒同时按下 Shift 键和 `a` 键；

- 花 $Z+X$ 毫秒按下 Capslock 键和 `a`键；

- 花 $Z+Y$ 毫秒按下 Capslock 键然后同时按下 Shift 键和 `a` 键。

这样，思路就来了。

代码（C++）：
```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr long long INF = 1000000000000000000;
int main(){
	long long X,Y,Z;
	cin >> X >> Y >> Z;
	string S;
	cin >> S;
	vector dp(S.size() + 1,vector<long long> (2,INF));
	dp[0][0] = 0;
	for(int i = 0;i < S.size();i++){
		int cur;
		if(S[i] == 'a')cur = 0;
		else cur = 1;
		for(int j = 0;j < 2;j++){
			for(int k = 0;k < 2;k++){
				long long v = dp[i][j];
				if(j != k)v += Z;
				if(cur == k)v += X;
				else v += Y;
				dp[i+1][k] = min(dp[i + 1][k],v);

			}
		}		
	}
	cout << min(dp[S.size()][0],dp[S.size()][1]);
	return 0;
}
```


---

## 作者：Cure_Wing (赞：3)

[题目](https://www.luogu.com.cn/problem/AT_abc303_d)

### 解析

你会发现我们在输出下一个字符之前一定会考虑好这个字符的输出方式和 `CapsLock` 的亮暗，而且这玩意没有后效性，就自然而然的想到了 `dp`。

状态也很好想，设 $f_{i,0/1}$ 表示现在要输出第 $i$ 个字符，且输出后 `CapsLock` 是暗/亮。

但是分类讨论的种类比较多，这里就只讲输出 `a` 的做法，`A` 的就同理即可。

考虑转移一定是从前一个字符输出后 `CapsLock` 的亮暗出发，转移到这个字符输出后的亮暗，我们先考虑输出后 `CapsLock` 是暗的情况。

如果上一次这个按键是亮的，我们就有两种方式：

1. 先按 `CapsLock`，再按 `a`，花费 $z+x$。

2. 先按 `Shift`+`a`，再按 `CapsLock`，花费 $y+z$。

如果上一次这个按键是暗的，我们也有两种方式：

1. 直接按 `a`，花费 $x$。

2. 先按 `CapsLock`，再按 `Shift`+`a`，最后按 `CapsLock`，花费 $z+y+z$。

然后你就得到了一个转移方程：$f_{i,0}=\max\{f_{i-1,1}+\max\{x,y\}+z,f_{i-1,0}+\max\{x,z+y+z\}\}$。

我们考虑要输出后 `CapsLock` 是亮的怎么办。

如果上一次这个按键是亮的，我们有两种方式：

1. 直接按 `Shift`+`a`，花费 $y$。

2. 先按 `CapsLock`，再按 `a`，最后按 `CapsLock`，花费 $z+x+z$。

如果上一次这个按键是暗的，我们也有两种方式：

1. 先按 `CapsLock`，再按 `Shift`+`a`，花费 $z+y$。

2. 先按 `a`，再按 `CapsLock`，花费 $x+z$。

然后你就又得到了一个转移方程：$f_{i,1}=\max\{f_{i-1,1}+\max\{y,z+x+z\},f_{i-1,0}+\max\{x,y\}+z\}$。

再对 `A` 同理一下你就发现做完了。

然后只需要比较 $f_{n,0}$ 和 $f_{n,1}$ 的大小就可以了。

最后不要忘记给 $f_{0,1}$ 赋合适的初值，不然程序会认为一开始 `CapsLock` 灯可以是亮的了。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long//不开long long见祖宗
using std::cin;using std::cout;
constexpr int N=300005;
int n,x,y,z,f[N][2];
std::string s;
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>x>>y>>z>>s;n=s.size();s=" "+s;f[0][1]=1e18;
	for(int i=1;i<=n;++i){
		if(s[i]=='A'){
			f[i][0]=std::min(f[i-1][0]+std::min(y,z+x+z),f[i-1][1]+std::min(x,y)+z);
			f[i][1]=std::min(f[i-1][0]+std::min(x,y)+z,f[i-1][1]+std::min(x,z+y+z));
		}else if(s[i]=='a'){//上面的讲解部分
			f[i][0]=std::min(f[i-1][0]+std::min(x,z+y+z),f[i-1][1]+std::min(x,y)+z);
			f[i][1]=std::min(f[i-1][0]+std::min(x,y)+z,f[i-1][1]+std::min(y,z+x+z));
		}
	}
//	for(int i=1;i<=n;++i) cout<<f[i][0]<<(i==n?'\n':' ');
//	for(int i=1;i<=n;++i) cout<<f[i][1]<<(i==n?'\n':' ');
	cout<<std::min(f[n][0],f[n][1]);
    return 0;
}
```

---

## 作者：luogu_gza (赞：2)

这是一个 dp。

定义 `f[i][0/1]` 为正在打第 $i$ 个字符，有没有按 `caps lock` 的最小时间。

转移分为两种。

`s[i]=='a'`：

```
f[i][0]=min(f[i-1][0]+x,f[i-1][1]+min(x,y)+z);
f[i][1]=min(f[i-1][1]+y,f[i-1][0]+min(x,y)+z);
```

`s[i]=='A'`：

```
f[i][0]=min(f[i-1][0]+y,f[i-1][1]+min(x,y)+z);
f[i][1]=min(f[i-1][1]+x,f[i-1][0]+min(x,y)+z);
```

答案：`min(f[n][0],f[n][1])`

[代码](https://atcoder.jp/contests/abc303/submissions/41743278)

---

## 作者：xiaoming007 (赞：2)

dp 好题。

## 思路

提供一个比较繁琐的思路。

先考虑一下有什么可能的按键组合：

只选择 `x`，耗费 $x$。按出来一个与原来相同的字符。大小写状态不变。

只选择 `y`，耗费 $y$。按出来变更大小写后的字符。大小写状态也不变。

接下来要注意选择完 `z` 之后的 `Caps lock` 变化。

选择 `z`，再选 `x`，耗费 $z + x$。按出来变更大小写后的字符。此时将状态从大写换成小写/小写换成大写。

选择 `z`，再选 `y`，耗费 $z + y$。按出来与原来相同的字符。将大小写状态从大写换成小写/小写换成大写。

然后对于每种可能的操作取 $\min$ 即可。

注意此题的正无穷最小得是 $10^9 \times 3 \times 10^5 \times 2$ 也就是 $6 \times 10^{14}$，否则会 WA。

## 代码

```cpp
//Author: Saint_ying_xtf
//xiaoming007 = Saint_ying_xtf
#include <bits/stdc++.h>
using namespace std;
#define int long long
unsigned long long dp[301010][4];
char tp[301010][4];
char cg(char c){return c == 'A' ? 'a' : 'A';}
signed main(){
    for(int i = 1; i <= 300100; ++i) for(int j = 0; j < 4; ++j) dp[i][j] = 4e18, tp[i][j] = '~';
    int x, y, z;
    scanf("%lld%lld%lld", &x, &y, &z);
    char s[305001];
    scanf("%s", s);
    int len = strlen(s);
    tp[0][0] = tp[0][1] = tp[0][2] = tp[0][3] = 'a';
    for(int i = 0; i < len; ++i){
        if(s[i] == tp[i][0]){
            tp[i+1][0] = s[i];
            dp[i+1][0] = min(dp[i][0] + x, dp[i+1][0]);
            tp[i+1][3] = cg(tp[i][0]);
            dp[i+1][3] = min(dp[i][0] + y + z, dp[i+1][3]);
        }else if(tp[i][0] == 'A' || tp[i][0] == 'a'){
            tp[i+1][1] = tp[i][0];
            dp[i+1][1] = min(dp[i][0] + y, dp[i+1][1]);
            tp[i+1][2] = s[i];
            dp[i+1][2] = min(dp[i][0] + x + z, dp[i+1][2]);
        }
        if(s[i] == tp[i][1]){
            tp[i+1][0] = s[i];
            dp[i+1][0] = min(dp[i][1] + x, dp[i+1][0]);
            tp[i+1][3] = cg(tp[i][1]);
            dp[i+1][3] = min(dp[i][1] + y + z, dp[i+1][3]); 
        }else if(tp[i][1] == 'A' || tp[i][1] == 'a'){
            tp[i+1][1] = tp[i][1];
            dp[i+1][1] = min(dp[i][1] + y, dp[i+1][1]);
            tp[i+1][2] = s[i];
            dp[i+1][2] = min(dp[i][1] + x + z, dp[i+1][2]);
        }
        if(s[i] == tp[i][2]){
            tp[i+1][0] = s[i];
            dp[i+1][0] = min(dp[i][2] + x, dp[i+1][0]);
            tp[i+1][3] = cg(tp[i][2]);
            dp[i+1][3] = min(dp[i][2] + y + z, dp[i+1][3]);
        }else if(tp[i][2] == 'A' || tp[i][2] == 'a'){
            tp[i+1][1] = tp[i][2];
            dp[i+1][1] = min(dp[i][2] + y, dp[i+1][1]);
            tp[i+1][2] = s[i];
            dp[i+1][2] = min(dp[i][2] + x + z, dp[i+1][2]);
        }
        if(s[i] == tp[i][3]){
            tp[i+1][0] = s[i];
            dp[i+1][0] = min(dp[i][3] + x, dp[i+1][0]);
            tp[i+1][3] = cg(tp[i][3]);
            dp[i+1][3] = min(dp[i][3] + y + z, dp[i+1][3]);
        }else if(tp[i][3] == 'A' || tp[i][3] == 'a'){
            tp[i+1][1] = tp[i][3];
            dp[i+1][1] = min(dp[i][3] + y, dp[i+1][1]);
            tp[i+1][2] = s[i];
            dp[i+1][2] = min(dp[i][3] + x + z, dp[i+1][2]);
        }
    }
    //for(int i = 0; i <= 6; ++i) cout << dp[len][1] << ' ';
    printf("%llu\n", min({dp[len][0], dp[len][1], dp[len][2], dp[len][3]}));
    return 0;
}
```

---

## 作者：Mortidesperatslav (赞：1)

这道题是很经典的 dp。

我们考虑分类讨论。

|  | 已开 Capslock | 未开 Capslock |
| -----------: | -----------: | -----------: |
| 下一个是 A | $X$ 或 $Z+Y$ | $Y$ 或 $Z+X$ |
| 下一个是 a | $Y$ 或 $Z+X$ | $X$ 或 $Z+Y$ |

状态转移方程就是上表。

然后我们采用 dp（这个模板 LJC00118 也用过），第一个字符特殊初始化即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[300005][2];
int x,y,z;
string t;
int main(){
	cin>>x>>y>>z;
	cin>>t;
	if(t[0]=='a'){//第一个字符默认没开 Capslock，初始化一下
		f[0][0]=x;
		f[0][1]=z+y;
	}else{
		f[0][0]=y;
		f[0][1]=z+x;
	}
	for(register int i=1;i<t.length();i++){
		if(t[i]=='a'){//下一个是 a
			f[i][0]=min(f[i-1][0]+x,f[i-1][1]+z+x);
			f[i][1]=min(f[i-1][0]+z+y,f[i-1][1]+y);
		}else{// 下一个是 A
			f[i][0]=min(f[i-1][0]+y,f[i-1][1]+z+y);
			f[i][1]=min(f[i-1][0]+z+x,f[i-1][1]+x);
		}
	}
	cout<<min(f[t.length()-1][0],f[t.length()-1][1]);
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

你要输出一段含有 `a` 和 `A` 的字符串，可以按键盘上的大写锁定键，shift 键，a 键。其中，只按 a 键要 $X$ 毫秒，a 和 shift 键一起按要 $Y$ 毫秒，按大写锁定键要 $Z$ 毫秒。初始大写锁定键熄灭，问最少要多长时间输出这段字符串。

$1\le X,Y,Z\le 10^{9}$，

$1\le |S|\le3\times10^5$。

## 题目分析
这题乍一看可能会感觉是一道贪心题，但仔细一想发现 $X,Y,Z$ 的大小关系是没有保证的，那就只能换思路了。

考虑 dp。

从左到右遍历这个字符串。显然，影响用时的就是当前字符的大小写和上一个字符打完的大写锁定键的状态。这只会有四种情况，我们就拿大写锁定键的状态设计状态 $dp_{i,0/1}$ 表示在打完第 $i$ 个字符之后大写锁定键是熄灭或是亮起的最小用时。

然后状态转移就很简单了，只需分类讨论，拿当前字符是 `a` 来举例。

- 对于 $dp_{i,0}$，可以是在大写锁定熄灭的状态下直接按一次 a 键，花费 $X$ 毫秒，或是先按一次大写锁定键，再 shift 键和 a 键一起按，再按大写锁定键，花费 $Y+2Z$ 毫秒，或是在大写锁定亮起的情况下，先 shift 键和 a 键一起按，再按大写锁定键，花费 $Y+Z$ 毫秒，或是先按大写锁定键，再按 $a$ 键，花费 $Z+X$ 毫秒。这四种方案取最小值。这样得到状态转移方程：
$dp_{i,0}=\min(dp_{i-1,0}+\min(X,Y+2Z),dp_{i-1,1}+\min(Y+Z,Z+Y))$

- 对于 $dp_{i,1}$，可以采用相同的思路得到状态转移方程。这里没有意义多赘述。

对当前字符是 `A` 的情况也是思路一样的讨论。

初始化时，要注意到大写锁定键此时一定是灭的。

但是，在输出答案的时候要注意，不能直接输出最后一个字符的两种状态的最小值，因为最后一个字符输出完之后大写锁定键的灭或亮是没有意义的。

细节可以看一下参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pf printf
#define cf scanf
#define rt return
using namespace std;
const int N=3e5+5;
ll x,y,z;
string s;
ll dp[N][2];
int main(){
	cin >>x>>y>>z>>s;
	int len=s.length();
	if(len==1){//注意特判1的情况
		if(s[0]=='a')cout <<min(x,y+z);
		else cout <<min(y,x+z);
		return 0;
	}
	if(s[0]=='a')dp[1][0]=min(x,z*2+y),dp[1][1]=min(x+z,z+y);
	else dp[1][0]=min(y,z*2+x),dp[1][1]=min(y+z,z+x);//初始化
	
	for(int i=2;i<len;i++){
		char c=s[i-1];
		if(c=='a'){
			dp[i][0]=min(dp[i-1][0]+min(x,z*2+y),dp[i-1][1]+min(y+z,z+x));
			dp[i][1]=min(dp[i-1][0]+min(x+z,z+y),dp[i-1][1]+min(y,x+2*z));
		}
		else {
			dp[i][0]=min(dp[i-1][0]+min(y,z*2+x),dp[i-1][1]+min(y+z,z+x));
			dp[i][1]=min(dp[i-1][0]+min(x+z,z+y),dp[i-1][1]+min(x,y+2*z));
		}
	}
	if(s[len-1]=='a'){
		cout <<min(dp[len-1][0]+min(x,y+z),dp[len-1][1]+min(y,x+z));
	}
	else cout <<min(dp[len-1][0]+min(y,x+z),dp[len-1][1]+min(x,y+z));//输出结果
	return 0;
}
```

 

---

## 作者：0xyz (赞：1)

#### 一、初步想法

我们发现仅有改变 Caps Lock 状态会影响其它的操作。然后我们考虑怎么处理。容易发现一个 Caps Lock 操作只会影响之后的操作。所以我们可以认为，Caps Lock 操作没有“前效性”。那么就可以倒着 dp。对当前状态有影响的是 Caps Lock 是否有大写锁定。所以记录一下就可以了。

#### 二、状态设计

我们令 $f_{0,i}$ 表示打到第 $i$ 位时没开大写锁定，打完第 $i\to n-1$ 位至少要多久。同时，令 $f_{1,i}$ 表示打到第 $i$ 位时开了大写锁定，打完第 $i\to n-1$ 位至少要多久。

#### 三、状态转移

注意有一个坑点，就是有可能 $Y+Z>X$，即转成大写，打个 `A`，然后再按 Shift 转成 `a` 有时候会比直接打 `a` 更快。

那么状态转移就是

$(1)$`s[i]='a'` 

$$\begin{cases}f_{0,i}=\min\{X+f_{0,i+1},Z+Y+f_{1,i+1}\}\\f_{1,i}=\min\{Z+X+f_{0,i+1},Y+f_{1,i+1}\}\end{cases}$$

$(2)$`s[i]='A'` 

$$\begin{cases}f_{0,i}=\min\{Z+X+f_{1,i+1},Y+f_{0,i+1}\}\\f_{1,i}=\min\{X+f_{1,i+1},Z+Y+f_{0,i+1}\}\end{cases}$$

然后不用初始化，答案就是 $f_{0,0}$。

#### 四、代码

代码很短。是我 A-Ex 里面最短的。

```cpp
#include<bits/stdc++.h>
#define c (s[i]=='A')
using namespace std;
typedef long long ll;
ll n,x,y,z,f[2][300010];
string s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>x>>y>>z>>s;n=s.size();
	for(ll i=n-1;i>=0;i--){
		f[!c][i]=min(z+x+f[c][i+1],y+f[!c][i+1]);
		f[c][i]=min(x+f[c][i+1],z+y+f[!c][i+1]);
	}
	cout<<f[0][0]<<'\n';
	return 0;
}
```

---

## 作者：shinzanmono (赞：0)

**update 2023.5.31：修改了一些变量名错误**

# [ABC303D] Shift vs. CapsLock

此题解使用 `A`，`B`，`C` 代替 `a key`，`Shift`，`Capslock`。

我们设 $f_{i,0/1}$ 表示当前输入到了第 $i$ 位，当前的 C 是否开启的所需的最小时间。初始，$f_{0,0}=0$，$f_{0,1}=Z$

对于第 $i$ 个字母为小写的情况，$f_{i-1,0}$ 可以通过 `A` 或 `C+A+C` 推出 $f_{i,0}$，$f_{i-1,1}$ 可以通过 `C+A` 或 `B+C` 推出 $f_{i,0}$；$f_{i-1,0}$ 可以通过 `C+B` 或 `A+C` 推出 $f_{i,1}$，$f_{i-1,1}$ 可以通过 `B` 或 `C+A+C` 推出 $f_{i,1}$。

同理我们可以得到第 $i$ 个字母为大写的情况。

最后的答案为 $\min(f_{n,0},f_{n,1})$。

给出代码：

```cpp
#include<iostream>
#include<algorithm>
const int sz = 3e5 + 10;
using ll = long long;
ll f[sz][2];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll x, y, z;
    std::string s;
    std::cin >> x >> y >> z >> s;
    int n = s.length();
    s = " " + s;
    f[0][0] = 0;
    f[0][1] = z;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'a') {
            f[i][0] = std::min(std::min(f[i - 1][0] + x, f[i - 1][0] + z + y + z), std::min(f[i - 1][1] + z + x, f[i - 1][1] + y + z));
            f[i][1] = std::min(std::min(f[i - 1][0] + x + z, f[i - 1][0] + z + y), std::min(f[i - 1][1] + y, f[i - 1][1] + z + x + z));
        } else {
            f[i][0] = std::min(std::min(f[i - 1][0] + y, f[i - 1][0] + z + x + z), std::min(f[i - 1][1] + z + y, f[i - 1][1] + x + z));
            f[i][1] = std::min(std::min(f[i - 1][0] + y + z, f[i - 1][0] + z + x), std::min(f[i - 1][1] + x, f[i - 1][1] + z + y + z));
        }
    }
    std::cout << std::min(f[n][0], f[n][1]);
    return 0;
}
```

---

## 作者：zzx0102 (赞：0)

考虑 dp。

令 $dp_{i,0}$ 表示到 $i$ 了且结束后为大写字母的最小花费。

$dp_{i.1}$ 表示到 $i$ 了且结束后为小写字母的最小花费。

那么 $dp_{0,0}$ 这个方案就不存在。

当 $s_i=$ `A` 时：

而 $dp_{i,1}$ 可以由原来是小写字母，按 Shift 得来，方案为 $dp_{i-1,1}+y$。

也可以是原来是大写字母，敲了一下，然后按了 CapsLock 键得来，方案为 $dp_{i-1,0}+x+z$。

也可以是 $dp_{i-1,0}+z+y+z$，原来是大写，然后摁了 CapsLock，在按 Shift，再按 CapsLock。

$dp_{i,0}$ 也可以 $dp_{i-1,0}+x$，就是原来是大写，然后按一下。

$s_i=$ `a` 的情况同理推一下就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 300010; int dp[N][4], x, y, z; string s;
signed main() {
	cin >> x >> y >> z >> s; s = ' ' + s; int n = s.length() - 1; dp[0][1] = 1e18;
	for(int i = 1; i <= n; i++) {
		if(s[i] == 'A') {
			dp[i][0] = dp[i - 1][0] + y;
			dp[i][1] = min(dp[i - 1][0] + z + x, dp[i - 1][1] + x);
			dp[i][1] = min(dp[i][1], dp[i - 1][1] + z + y + z);
			dp[i][0] = min(dp[i][0], dp[i - 1][1] + z + y);
		}
		else {
			dp[i][1] = dp[i - 1][1] + y;
			dp[i][0] = min(dp[i - 1][1] + z + x, dp[i - 1][0] + x);
			dp[i][0] = min(dp[i][0], dp[i - 1][0] + z + y + z);
			dp[i][1] = min(dp[i][1], dp[i - 1][0] + z + y);
		}
//		cout << dp[i][0] << ' ' << dp[i][1] << endl;
	}
	cout << min(dp[n][0], dp[n][1]);
	return 0;
}
```

---

## 作者：ReeChee (赞：0)

## Problem

键盘上有三个按键：A 键，Caps Lock（大小写锁定切换）键和 Shift 键，给定三个正整数 $X,Y,Z$，分别代表的含义如下：

- 花费 $X$ 毫秒的时间按 A 键，此时若大小写锁定状态为大写则将显示 `A`，反之则显示 `a`。

- 花费 $Y$ 毫秒的时间同时按 Shift 键和 A 键，若此时大小写锁定状态为大写则会显示 `a`，反之则显示 `A`。

- 花费 $Z$ 毫秒的时间按 Caps Lock 键，若此时大小写锁定状态为大写则切换其为小写，反之亦然。

初始时大小写锁定状态为小写，给定一个字符串 $S$，问打出 $S$ 最少要多少毫秒。

$1\leq X,Y,Z\leq 10^9,1\leq |S|\leq 3\times 10^5$，$S$ 仅含 `a` 和 `A`。

## Solution

对于这种分阶段决策的问题很明显用动态规划求解。

**状态**：设 $f_{i,0/1}$ 为打出前 $i$ 个字符后大小写锁定状态为小写或大写的最短耗时。

**初始状态**：$f_{0,0}=0,f_{0,1}=Z$，其余全为极大值。

**决策**：

以 $S_i$ 为小写为例。

- 若打完当前字符后的状态为小写，则有一下几种可能：
- - 上次为小写，这次直接按 A 键：$f_{i-1,0}+X$。
- - 上次为大写，这次切换到小写后按 A 键：$f_{i-1,1}+Z+X$。

- 若打完当前字符后的状态为大写，则有以下几种可能：
- - 上次为小写，那么按 A 键之后切换到大写：$f_{i-1,0}+X+Z$。
- - 上次为大写，那么同时按 Shift 键和 A 键：$f_{i-1,1}+Y$。
- - 上次为大写，那么切换到小写后按 A 键，随后再切换到大写：$f_{i-1,1}+Z+X+Z$。

转移时对不同决策取最小值即可。

$S_i$ 为大写的时候把上面转移反过来就可以了。

**答案**：$\min(f_{|S|,0},f_{|S|,1})$。

时间复杂度 $\mathcal{O}(|S|)$。

## Code

```cpp
const int N = 3e5+5;
int X,Y,Z,n,f[N][2];
char s[N];
signed main(){
    memset(f,0x3f,sizeof(f));
    X=read(),Y=read(),Z=read();
    f[0][0]=0,f[0][1]=Z;
    scanf("%s",s+1);
    n=strlen(s+1);
    F(i,1,n){
        if (isupper(s[i])){
            f[i][1]=min(f[i-1][1]+X,f[i-1][0]+Z+X);
            f[i][0]=min(f[i-1][1]+X+Z,min(f[i-1][0]+Y,min(f[i-1][0]+2*Z+X,f[i-1][1]+Z+Y)));
        }
        else{
            f[i][0]=min(f[i-1][0]+X,f[i-1][1]+Z+X);
            f[i][1]=min(f[i-1][0]+X+Z,min(f[i-1][1]+Y,min(f[i-1][1]+2*Z+X,f[i-1][0]+Z+Y)));
        }
    }
    printf("%lld",min(f[n][0],f[n][1]));
    return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc303_d)     
一眼 dp 题。             
我们设 $dp_{i,j}$ 为第 $i$ 位时，大小写状态为 $j$ 时，打出这些字符所需要的最小时间。这里如果 $j=1$ 为大写，$j=0$ 为小写。    
我们扫一遍这个字符串，设这一次扫到了第 $i$ 位。    
## $s_i$ 为小写     
### $i>1$   
我们可以发现，有 $3$ 种方法打出这个字符：     
- 上一个字符的状态是大写，用 $y$ 毫秒按下 `shift` 和 `a`。     
- 上一个字符的状态是大写，用 $x+z$ 毫秒按下 `CapsLock` 和 `a`。    
- 上一个字符的状态是小写，用 $x$ 毫秒按下 `a`。 

注意这里对于第二三种操作，最后的大小写状态为小写，第一种操作最后的状态为大写。       
所以我们可以写出以下状态转移方程：    
$dp_{i,0}=\min(dp_{i-1,0}+x,dp_{i-1,1}+z+x)$    
$dp_{i,1}=dp_{i-1,1}+y$    
### $i=1$   
特殊情况，这里明显 $dp_{1,0}=x,dp_{1,1}=z+y$。   

## $s_i$ 为大写   
这里的推导过程与上面的大致相同，就不写了。
### $i>1$      
这里的转移方程为：    
$dp_{i,1}=\min(dp_{i-1,1}+x,dp_{i-1,0}+z+x)$    
$dp_{1,0}=dp_{i-1,0}+y$     
### $i=1$   
这里 $dp_{i,1}=z+x,dp_{i,0}=y$。       


我们发现，我们每次操作之后可以改变大小写状态，我们可以通过改变大小写状态来获得更小的时间。所以我们每次转移后都要再进行如下的转移：     
$dp_{i,0}=\min(dp_{i,0},dp_{i,1}+z)$    
$dp_{i,1}=\min(dp_{i,1},dp_{i,0}+z)$     
答案最后为 $\min(dp_{n,0},dp_{n,1})$。    
[CODE](https://www.luogu.com.cn/paste/lfy006yj)

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc303_d)
### 思路
一眼 DP。
设 $f_{i,0/1}$ 表示在第 $i$ 字母 **打完后** 的状态为关/开着 Caps lock。


若打第 $i$ 个字母打完后关着 Caps lock：

- 若第 $i$ 个字母打完前关着 Caps lock：

	- 若要打的字母是大写，那么我们有两种方式：
    
		- 直接按 Shift + a，耗时 $y$ ms。
        
	    - 先按 Caps lock，再按 a，最后按 Caps lock，耗时 $z + x + z$ ms。
        
	- 若要打的字母是小写，那么我们有两种方式：
    	
        - 直接按 a，耗时 $x$ ms。
        - 先按 Caps lock，再按 Shift + a，最后按 Caps lock，耗时 $z + y + z$ ms。
        
- 若第 $i$ 个字母打完前开着 Caps lock：
	- 若要打的字母是大写，那么我们有两种方式：
    
    	- 先按 Caps lock，再按 Shift + a，耗时 $z + y$。
        - 先按 a，再按 Caps lock，耗时 $x + z$。
        
    - 若要打的字母是小写，那么我们有两种方式：
    
    	- 先按 Caps lock，再按 a，耗时 $z + x$。
        - 先按 Shift + a，再按 Caps lock，耗时 $y + z$。
        
        
其他两种状态不予分析，请读者自行思考。
### 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <set>
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair <int,int> PII;
const int N = 300010;
LL x,y,z;
int n;
string s;
LL f[N][2];
int main () {
	cin >> x >> y >> z >> s;
	n = s.size (),s = ' ' + s;
	memset (f,0x3f,sizeof (f));
	f[0][0] = 0;
	for (int i = 1;i <= n;i++) {
		f[i][0] = min (f[i - 1][1] + (s[i] == 'A' ? min (x + z,z + y) : min (y + z,z + x)),f[i - 1][0] + (s[i] == 'A' ? min (y,z + x + z) : min (x,z + y + z)));
		f[i][1] = min (f[i - 1][1] + (s[i] == 'A' ? min (x,z + y + z) : min (y,z + x + z)),f[i - 1][0] + (s[i] == 'A' ? min (z + x,y + z) : min (z + y,x + z)));
	}
	cout << min (f[n][0],f[n][1]) << endl;
    return 0;
}
```

---

