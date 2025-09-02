# [ABC195E] Lucky 7 Battle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc195/tasks/abc195_e

`0`,$ \ldots $,`9` からなる長さ $ N $ の文字列 $ S $ と、`A`,`T` からなる長さ $ N $ の文字列 $ X $ が与えられます。また、空文字列で初期化された文字列 $ T $ があります。

高橋君と青木君がこれらを使ってゲームをします。ゲームは $ N $ ラウンドからなり、$ i $ 回目 $ (1\leq\ i\ \leq\ N) $ のラウンドでは次の操作が行われます。

- $ X_i $ が `A` なら青木君が、`T` なら高橋君が以下の操作を行う
- 操作：$ T $ の末尾に $ S_i $ か `0` のどちらか一方を加える

$ N $ 回の操作が終了したあと、$ T $ は `0`,$ \ldots $,`9` からなる長さ $ N $ の文字列となります。 $ T $ を (先頭の余計な $ 0 $ を取り除いた上で) $ 10 $ 進法で表された数と解釈したとき、$ 7 $ の倍数であれば高橋君の勝ちであり、そうでなければ青木君の勝ちです。

$ 2 $ 人が最適に行動する時、どちらが勝つか判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ S,X $ の長さは $ N $
- $ S $ は `0`,$ \ldots $,`9` のみからなる
- $ X $ は `A`,`T` のみからなる

### Sample Explanation 1

$ 1 $ 回目のラウンドでは青木君が `3` か `0` を $ T $ の末尾に加え、$ 2 $ 回目のラウンドでは高橋君が `5` か `0` を $ T $ の末尾に加えます。 青木君が `3` を加えた場合、高橋君が `5` を追加すると $ T $ は `35` となり、これは $ 7 $ の倍数です。 青木君が `0` を加えた場合、高橋君が `0` を追加すると $ T $ は `00` となり、これは $ 7 $ の倍数です。 したがって、かならず高橋君が勝ちます。

## 样例 #1

### 输入

```
2
35
AT```

### 输出

```
Takahashi```

## 样例 #2

### 输入

```
5
12345
AAAAT```

### 输出

```
Aoki```

## 样例 #3

### 输入

```
5
67890
TTTTA```

### 输出

```
Takahashi```

## 样例 #4

### 输入

```
5
12345
ATATA```

### 输出

```
Aoki```

# 题解

## 作者：olegekei (赞：9)

首先思考一个问题：能被 $7$ 整除的数翻十倍之后也一定能被 $7$ 整除，不能被 $7$ 整除的翻十倍仍然不能被 $7$ 整除（但是余数会改变）。

那么我们就可以考虑化简每一轮的 $T$ 为原 $T$ 除以 $7$ 的余数。

举个例子，$30\bmod{7}=2$，那么我们就可以把 $2$ 当作此时的 $T$（$2+5 \equiv 0 \pmod{7}$，$30+5 \equiv 0 \pmod{7}$）。

接下来考虑递推游戏过程。

对于 Aoki 来说自己的每一轮都需要考虑 Takahashi 下一个或连续几个操作能够凑出的数，而自己需要让他无法凑出 $7$ 的倍数。那么需要预处理 Takahashi 的每个连续回合而且需要分类讨论，麻烦至极而且并不好写。

那么考虑倒着递推。状态设计为 $f[i][j]$，$i$ 代表游戏第 $i$ 轮，$j$ 代表第 $i$ 轮的余数 $j$ 可以取到。我们假设最后是 Takahashi 获胜，那么最后 $T$ 一定是 $7$ 的倍数，状态记录为 $f[n+1][0]=1$，接下来考虑怎样由 $f[i+1][?]$ 转移到 $f[i][j]$。

若当前由 Takahashi 进行操作，他会想尽办法让自己有更多条路进行转移，所以只要当前 $f[i+1][10j \bmod 7]$（对应当前第 $i$ 轮取 $0$）或 $f[i+1][10j+S[i-1] \bmod 7]$（对应当前第 $i$ 轮取 $S_i$，但是由于字符串下标从 $0$ 开始，所以为 $i-1$）为 true，那么 $f[i][j]$ 为 true。

若当前由 Aoki 进行操作，他会想尽办法让 Takahashi 有更少条路进行转移，则相应的只有当前 $f[i+1][10j \bmod 7]$ 与 $f[i+1][10j+S[i-1] \bmod 7]$ 都为 true，对应的 $f[i][j]$ 才能为 true。

最后判断一下 $f[1][0]$ 是否为 true 即可。

代码：
```cpp
#include<iostream>
using namespace std;
bool f[200015][7];
int N;
string S,X;
int main(){
cin>>N>>S>>X;
f[N+1][0]=1;
for(int i=N;i>=1;i--){
	for(int j=0;j<7;j++){
		bool x=f[i+1][10*j%7],y=f[i+1][(10*j+S[i-1]-48)%7];
		if(X[i-1]=='A')f[i][j]=x&y;
		else f[i][j]=x|y;
	}
}
cout<<(f[1][0]?"Takahashi":"Aoki");
return 0;
}
```

---

## 作者：max666dong123 (赞：5)

## 定义
认为类似博弈论，求的是是否必胜，定义 $f_{i,j}=x (x=0/1)$ 表示到第 $i$ 轮后余数为 $j$ 为 ``Takahashi`` 必胜或必败。

## 起点

$f_{n+1,0}=1$ 很明显，最后余 $0$，``Takahashi`` 必胜。

## 转移方程
定义 $a$ 为 $f_{i,j \times 10+s_{i-1}+7}$，$b$ 为 $f_{i,j \times 10}$。
$$
f_{i-1,j}=
\begin{cases}
a \operatorname{or} b&(t_{i-1}=T) \\
a\operatorname{and} b&(t_{i-1}=A) \\
\end{cases}
$$

## 答案
$f_{0,0}$ 为最终的答案。

**注意**：逆序推导方程。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
bool f[N][10];
int n;
string s,t;
signed main(){ 
//	while(cin>>n){
//		if(n==0){
//			return 0;
//		}
		memset(f,0,sizeof(f));
		cin>>n;
		cin>>s;
		cin>>t;
		f[n][0]=1;
		for(int i=n;i>=0;i--){
			for(int j=0;j<=6;j++){
				bool x=f[i][(j*10+s[i-1]-'0'+7)%7];
				bool y=f[i][(j*10+7)%7];
				if(t[i-1]=='T'){
					f[i-1][j]=x|y;
				}
				else{
					f[i-1][j]=x&y;
				}
			}
		}
		if(f[0][0]==1){
			cout<<"Takahashi"<<endl;
		}
		else{
			cout<<"Aoki"<<endl;
		}		
//	}

	
	return 0;
}

```



---

## 作者：Barryb (赞：3)

# 大意
让第 $i$ 个人把 $T$ 变成 $10T$ 或 $10T + S_i$。问 $N$ 轮后 $T$ 是不是 $7$ 的倍数。类似博弈论的 DP 题。
# 定义
设 $i$ 为第 $x$ 轮，$j$ 为 $10T$ 或 $10T + S_{i - 1}$ 模 $7$ 的余数，也就是 $7$ 个状态。那 $f_{i,j}$ 就表示第 $x$ 轮的 $T$ 模 $7$ 下的状态。
# 思路
如果 $X_i$ 是 $T$，$f_{i,j}$ 就在 $10T$ 和 $10T + S_{i - 1}$ 里选一种就行了。否则就只能两种都选才能满足要求。
# 提醒
第二维数组只有 $0$ 到 $6$，$7$ 种情况，要模 $7$。
# 状态转移方程
```cpp
int a=dp[i][(j*10+s[i-1]-'0'+7)%7];
int b=dp[i][j*10%7];
dp[i-1][j%7]=(x[i-1]=='T'?(a||b):(a&&b));
```
# 整体代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[200010][10];
string s,x;
int main(){
	cin>>n>>s>>x;dp[n][0]=1;
	for(int i=n;i;i--) {
		for(int j=0;j<=6;j++) {
			int a=dp[i][(j*10+s[i-1]-'0'+7)%7];
			int b=dp[i][j*10%7];
			dp[i-1][j%7]=(x[i-1]=='T'?(a||b):(a&&b));
		}
	}
	if(dp[0][0]==1) cout<<"Takahashi";
	else cout<<"Aoki";
	return 0;
}
```
也可以记搜 DFS，代码就不放了。

---

## 作者：qiuzijin2026 (赞：3)

# AT_abc195_e [ABC195E] Lucky 7 Battle
## [题面](https://www.luogu.com.cn/problem/AT_abc195_e)
## 思路
经典倒序 `` dp ``。

#### 定义

这种玩游戏的 `` dp `` 题，一般为倒序。
本题只要求是的倍数，所以我们可以开个二维数组维护每一轮模 $7$ 的情况。
即 $ f(i,j) $ 表示从第 $i$ 轮结束后余数是 $j$ 的比赛结果。

- 如果 $ f(i,j) $ 是 ``true`` 表示是 ``Takahashi`` 赢。
- 如果 $ f(i,j) $ 是 ``false`` 表示是 ``Aoki`` 赢。

#### 初始化

$ f(n,0)=true $，因为第 $n$ 轮后余 $0$ 一定是 ``Takahashi`` 赢。

#### 转移方程

- 如果 $ x(i) $ 为 `T`，$ f(i-1,j)=f(i,(j \times 10+s(i)-0) \bmod 7)  \operatorname{or} f(i,j \times 10 \bmod 7) $。

- 如果 $ x(i) $ 为 `F`，$ f(i-1,j)=f(i,(j \times 10+s(i)-0) \bmod 7) \operatorname{and} f(i,j \times 10 \bmod 7) $。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
string s;
string x;
bool f[200005][7];
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	while(cin>>n){
		if(n==0) return 0;
		cin>>s;
		cin>>x;
		memset(f,false,sizeof(f));
		f[n][0]=true;
		for(int i=n;i>=1;i--)
			for(int j=0;j<=6;j++){
				if(x[i-1]=='T') f[i-1][j]=f[i][(j*10+s[i-1]-'0')%7]|f[i][j*10%7];
				else f[i-1][j]=f[i][(j*10+s[i-1]-'0')%7]&f[i][j*10%7];
			}
			
		if(f[0][0]) printf("Takahashi\n");
		else printf("Aoki\n");
	}
	return 0;
}
```

---

## 作者：nxd_oxm (赞：3)

## 思路
这种玩游戏的题，一般都是倒序计算。
 
定义 $f_{i,j}=s$ ，为第 $i$ 轮结束后余数为 $j$ ，  $s = 1$  时， ``Takahashi`` 必胜，反之 ``Aoki`` 必胜。

显然，$f_{n,0}=1$。  

最后当余数为 $0$ 时 ``Takahashi`` 必胜。

## 转移方程
定义：

$x=f_{i,j \times 10+a_{i-1} \bmod 7}$  ，

$y=f_{i,j \times 10 \bmod 7}$  。

$
f_{i-1,j}=
\begin{cases}
x  \ \operatorname{or} \ y \ (b_{i-1}=T)\\
x  \ \operatorname{and} \ y \ (b_{i-1}=A)\\
\end{cases}
$

 $x$ 为选 $a_i$ 的余数, $y$ 为不选 $a_i $ 的余数。
 如果当前是 ``Takahashi`` 选，那只要两个中有一个能让 ``Takahashi`` 必胜就行。
 如果当前是 ``Aoki`` 选，那需要两个都能让  ``Takahashi`` 必胜才能使 `` Takahashi``  必胜，反之当前情况 ``Aoki`` 必胜。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string a,b;
bool dp[200001][8];
signed main(){
	cin>>n; 
	cin>>a;
	cin>>b;
	dp[n][0]=1;
	for(int i=n;i>=1;i--){
		for(int j=0;j<7;j++){
			bool x=dp[i][(j*10+(a[i-1]-'0'))%7];
			bool y=dp[i][(j*10)%7];
			if(b[i-1]=='T'){
				dp[i-1][j]=x|y; 
			}else{
				dp[i-1][j]=x&y; 
			}
		}
	}
	cout<<(dp[0][0]==1?"Takahashi\n":"Aoki\n");
	return 0;
}
```


---

## 作者：lizuting (赞：2)

### 题解：Lucky 7 Battle (ABC195E)

#### 题目概述

给定长度为 $N$ 的数字字符串 $S$ 和选择字符串 $X$。

每一轮，玩家可以选择追加数字 $0$ 或从字符串 $S$ 中取一个数字。经过 $N$ 轮后，得到的数字模 $7$ 的余数决定胜负。

我们需要决定最后的胜者。

#### 解题思路

由于数字模 $7$ 只有 $7$ 种可能的余数,我们可以针对每种余数保存一个状态，表示是否可以得到这种余数。

我们采用逆向 `DP` 策略，从最后一轮回溯到第一轮。定义 $dp_{i,j}$ 为在第 $i$ 轮，是否存在一个数字 $T$ 使得 $T \bmod 7 = j$。

#### 状态转移

- 如果 $X_i = A$，`Aoki` 希望在下一轮 `Takahashi` 不论选择哪个数字都无法赢。如果都能赢，那么当前状态不可取。

- 如果 $X_i = T$，`Takahashi` 只需要一个选择能使他赢即可。

状态转移方程如下：

- 如果 $X_i = A$，$ dp_{i,j} = dp_{i + 1,j\times 10\bmod 7} \land dp_{i + 1,(j\times 10+s(i))\bmod 7} $

- 如果 $X_i = T$，$ dp_{i,j} = dp_{i + 1,(j\times 10)\bmod 7} \lor dp_{i + 1,(j\times 10+s(i))\bmod 7}$
 
#### 代码实现

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MOD = 7;

int main() {
    int N;
    string S, X;
    cin >> N >> S >> X;

    vector<vector<bool>> dp(N + 1, vector<bool>(7, false));
    dp[N][0] = true;

    for (int i = N - 1; i >= 0; --i) {
        int num = S[i] - '0';
        for (int j = 0; j < 7; ++j) {
            int next0 = (j * 10) % MOD;
            int next1 = (j * 10 + num) % MOD;
            if (X[i] == 'A') {
                dp[i][j] = dp[i + 1][next0] && dp[i + 1][next1];
            } else {
                dp[i][j] = dp[i + 1][next0] || dp[i + 1][next1];
            }
        }
    }

    if (dp[0][0]) {
        cout << "Takahashi" << endl;
    } else {
        cout << "Aoki" << endl;
    }
    return 0;
}
```

#### 结论

通过逆向 `DP`，我们可以确定每一轮玩家的最佳选择，并据此判断最终的胜者。

---

## 作者：Little_Cabbage (赞：2)

**思路**

这道题需要倒序计算。

定义 $dp_{i,j}=f$ 表示第 $i$ 轮结束后余数为 $j$ ，$f=1$ 时， `Takahashi` 必胜，否则 `Aoki` 必胜。

**动态转移方程式**

令：

$x=dp_{i,(j \times 10 + a_i)\bmod 7}$

$y=dp_{i,j \times 10 \bmod 7}$

$dp_{i-1,j}=\begin{cases}x\ \operatorname{or}\ y&b_i=T\\x\ \operatorname{and}\ y&b_i=A\end{cases}$

$x$ 为选 $a_i$ 的余数, $y$ 为不选 $a_i$ 的余数。

如果当前是 `Takahashi` 选，那只要两个中有一个能让 `Takahashi` 必胜就行。

如果当前是 `Aoki` 选，那需要两个都能让 `Takahashi` 必胜才能使 `Takahashi` 必胜，否则当前情况 `Aoki` 必胜。

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,dp[200010][10];
string a,b;
int main(){
	cin>>n;
	cin>>a>>b; 
	a=" "+a;
	b=" "+b;
	memset(dp,0,sizeof dp);
	dp[n][0]=1;
	for(int i=n;i>=1;i--)
		for(int j=0;j<7;j++){
			bool x=dp[i][(j*10+a[i]-'0')%7];
			bool y=dp[i][j*10%7];
			if(b[i]=='T')
				dp[i-1][j]=x|y;
			else
				dp[i-1][j]=x&y;
		}
	cout<<(dp[0][0]==0?"Aoki":"Takahashi")<<endl;
	return 0;
} 
```

---

## 作者：lfxxx (赞：2)

其实我们发现很多博弈论的动态规划都是从后往前的，比如过河卒和本题。

这是因为从某种角度上来说这些动态规划**有后效性而无前效性**。

所以设计状态 $dp_{i,j}$ 表示第 $i$ 次操作 $T$ 模 $7$ 的余数为 $j$ 的情况下**能否走到 Takahashi 的胜利状态**。

然后就是正常的博弈论**倒序**转移。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 3e5+114;
string X,S;
int n;
int dp[maxn][10];//第 i 次操作后 base-10 T % 7 = j 是否可能达成目标 
signed main(){
	cin>>n;
	cin>>X>>S;
	dp[n][0]=1;
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<7;j++){
			if(S[i]=='T'){
				dp[i][j]=dp[i+1][(j*10+((int)(X[i]-'0')%7))%7]|dp[i+1][(j*10)%7];
			}
			else{
				dp[i][j]=dp[i+1][(j*10+((int)(X[i]-'0')%7))%7]&dp[i+1][(j*10)%7];
			}
		}
	}
	cout<<(dp[0][0]==1?"Takahashi":"Aoki");
} 
```


---

## 作者：wth2026 (赞：1)

注：下文中，T 指 Takahashi，A 指 Aoki。
# 题目大意
给定长度为 $N$（$1 \le N \le 2 \times 10^5$）的字符串 $S$（由数字 $0 \sim 9$ 组成），现在 T 要和 A 进行 $N$ 轮游戏，第 $i$ 轮游戏可以让数字 $T$（初始时 $T=0$）变成 $10T$ 或 $10T+S_i$。

若游戏结束时 $T$ 是 $7$ 的倍数，则 T 获胜，否则 A 获胜。

现在给了你字符串 $X$，在第 $i$ 轮时若 $X_i$ 为 $A$ 则由 A 行动,为 $T$ 则由 T 行动，两人都会按照最优策略行动，问最后谁会获胜。
# 题目思路
考虑动态规划。

使用 $f_{i,j}$ 表示第 $i$ 次后余数为 $j$，当最后 $s=1$ 时，T 胜，反之 A 胜。

初始化：$f_{n,0}=1$。

转移（$\LaTeX$ 太麻烦，就放代码片段了）：
```cpp
_[0] = f[i][(j * 10 + (a[i - 1] ^ 48)) % 7], _[1] = f[i][(j * 10) % 7];

if (b[i - 1] == 'T') {
    f[i - 1][j] = _[0] || _[1];
} else {
    f[i - 1][j] = _[0] && _[1]; 
}
```
# AC Code
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f3f

#pragma GCC optimize (1)
#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimize (4)
#pragma GCC optimize (5)
#pragma GCC optimize ("Os")
#pragma GCC optimize ("Ofast")

using namespace std;

const int N = 200000, M = 8;

int n;
string a,b;
bool f[N + 5][M + 5], _[2];

signed main() {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
	
	cin >> n >> a >> b;
	f[n][0] = 1;
	
	for (register int i = n; i; -- i) {
		for (register int j = 0; j < 7; ++ j) {
			_[0] = f[i][(j * 10 + (a[i - 1] ^ 48)) % 7], _[1] = f[i][(j * 10) % 7];
			
			if (b[i - 1] == 'T') {
				f[i - 1][j] = _[0] || _[1]; 
			} else {
				f[i - 1][j] = _[0] && _[1]; 
			}
		}
	}
	
	if (f[0][0]) {
		cout << "Takahashi" << endl;
	} else {
		cout << "Aoki" << endl;
	}
	
	return 0;
}
```

---

## 作者：Igallta (赞：0)

- 注：后文称 Takahashi 为高桥，Aoki 为青木。

这道题我们开题之后简单看一眼发现正着推十分困难，因为每一次有两种选择。

所谓正难则反，这题就变简单了很多。

我们设计一个 $dp$ 数组，$dp_{i,j}$ 代表选到第 $i$ 个时，模 $7$ 余数为 $j$ 的胜负情况。

$dp_{i,j}$ 为 $1/0$ 分别代表高桥赢和青木赢。

也是就说这题其实是一个倒序布尔 dp。

首先要初始化 $dp_{n,0}=1$，因为 $n$ 轮之后（结束了）余 $0$ 一定是高桥赢。

现在来设计转移方程。

由于这道题的添加就只有两种情况所以直接套就可以。

```cpp
bool x=f[i][(j*10+s[i]-'0')%7];
bool y=f[i][(j*10)%7];
```


我们再想一下，如果这两种情况里面只要有一个是 $0$（青木赢）那么青木就一定会选择这个 $0$。反之，只要这两种情况有一个 $1$（高桥赢）那么高桥一定会选择这个 $1$。

所以青木做的是“与”运算。（只要不是全都是 $1$ 都是他赢）

而高桥做的是“或”运算。（只要有一个 $1$ 他就能赢）

这部分的代码：

```cpp
for(int i=n;i>=1;i--){
  for(int j=6;j>=0;j--){
    bool x=f[i][(j*10+s[i]-'0')%7];
    bool y=f[i][(j*10)%7];
    if(t[i]=='T')f[i-1][j]=x|y;
    else f[i-1][j]=x&y;	
  }
}
```

最后一个坑点，要判断的是 $dp_{0,0}$，而不是 $dp_{1,0}$ 更不是 $dp_{n,0}$。

为什么呢？

因为我们存储的是“下一步”谁会赢，而当 $i=1$ 时，下一步谁会赢会存储在 $dp_{0,x}$ 中。

最后用你的脚都能想到是 $dp_{0,0}$，这里就不讲了。

完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int n,f[N][11];
string s,t;
signed main(){
	cin>>n;
	cin>>s>>t;
	s=' '+s;//为了方便计算
	t=' '+t;
	f[n][0]=1;//初始化
	for(int i=n;i>=1;i--){
		for(int j=6;j>=0;j--){
			bool x=f[i][(j*10+s[i]-'0')%7];
			bool y=f[i][(j*10)%7];
			if(t[i]=='T')f[i-1][j]=x|y;
			else f[i-1][j]=x&y;	
		}
	}
	cout<<(f[0][0]?"Takahashi\n":"Aoki\n");
	return 0;
}
```

---

## 作者：COsm0s (赞：0)

记忆化搜索。

考虑直接按照题目爆搜。

+ 当前为 $A$ 操作时，由于两人都是按照最优决策进行，所以其所能转移到的两个状态 $S+0/X_i$ 都必须能够到达合法状态。

	这个很好理解，如果有一种状态无效的话 $T$ 方直接选择那种状态即可。
    
+ 同理当 $T$ 操作时，如果有一种状态无效的话当前状态就无效。

然后可以发现如果记下当前位置和余数的话，状态数是严格 $\Theta(Bn)$ 的，其中 $B$ 为值域。

那么记搜即可。

```cpp
const int N = 2e5 + 5, M = 1e6;
	int n, a[N], vis[N], f[N][10];
	char ch[N];
	bool dfs(int k, int sum) {
//		cout << k << ' ' << sum << ' ' << f[k][sum] << '\n';
		if (k > n) {
			if (sum % 7 == 0) return 1;
			else return 0;
		}
		if (f[k][sum] != -1) return f[k][sum];
		if (ch[k] == 'A') {
			if (dfs(k + 1, sum * 10 % 7) && dfs(k + 1, (sum * 10 + a[k]) % 7)) {
				return f[k][sum] = 1;
			}
			return f[k][sum] = 0;
		} else {
			if (dfs(k + 1, sum * 10 % 7) || dfs(k + 1, (sum * 10 + a[k]) % 7)) {
				return f[k][sum] = 1;
			}
			return f[k][sum] = 0;
		}
	}
	signed main() {
		cin >> n;
		REP(i, 1, n) {
			char ch;
			cin >> ch;
			a[i] = ch - 48;
		}
		REP(i, 1, n) cin >> ch[i];
		memset(f, -1, sizeof f);
		cout << (!dfs(1, 0) ? "Aoki" : "Takahashi") << '\n';
		return 0;
	}
}
```

---

## 作者：Down_syndrome (赞：0)

**（友情提示：由于本人并不喜欢下标从 $0$ 开始，所以以下题解及代码均以下标从 $1$ 开始为准）**
## 思路
由于正着考虑并不好想，于是可以考虑倒着使用 dp 的思想。我们令 $f_{i,j}$ 表示第 $i$ 轮开始前 $T\bmod7$ 的值为 $j$ 是高桥还是青木赢。如果是高桥赢则为 $1$，否则为 $0$。可以证明没有两人都可能赢的情况。接下来考虑递推式。

- 若 $X_i=T$，则高桥的获胜条件为当前的 $j$ 下一轮能变成的两个数**其中之一**可以获胜，因为高桥会采取最优策略，所以只要有一个能获胜就行了，因此递推式为: 
$$f_{i,j}=f_{i+1,(j\times10+S_i)\bmod7}\ or\ f_{i+1,j\times10\bmod7}$$
- 若 $X_i=A$，则高桥的获胜条件为当前的 $j$ 下一轮能变成的两个数**两个都**可以获胜，因为青木会采取最优策略，所以不能给青木获胜的机会，两个都要获胜，因此递推式为：
$$f_{i,j}=f_{i+1,(j\times10+S_i)\bmod7}\ and\ f_{i+1,j\times10\bmod7}$$
注意初始化为 $f_{n+1,0}\gets1$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n;
bool f[N][7];
char s[N],x[N]; 
int main(){
	scanf("%d%s%s",&n,s+1,x+1);
	f[n+1][0]=1;
	for(int i=n;i>=1;i--){
		for(int j=0;j<7;j++){
			if(x[i]=='T') f[i][j]=f[i+1][(j*10+s[i]-'0')%7]||f[i+1][j*10%7];
			else f[i][j]=f[i+1][(j*10+s[i]-'0')%7]&&f[i+1][j*10%7];
		}
	}
	if(f[1][0]) printf("Takahashi");
	else printf("Aoki");
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# AT_abc195_e [ABC195E] Lucky 7 Battle 题解

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/AT_abc195_e)

给出 $n$ 个数和 Aoki 与 Takahashi 的取数顺序，求能否保证 Takahashi 能赢。

## 思路

- 这道题考虑使用 $dp$ 求解，定义 $dp_{i_j}$ 为能否保证倒叙取到第 $i$ 个数，模 $7$ 余数是 $j$，为 true 是表示可以保证 false 表示不能保证。

- 转移方程

- 定义 $z=dp_{i,(j\times 10+t[i-1]) \bmod 7}$

- 定义 $y=dp_{i,j\times 10 \bmod 7}$

$
\left\{
	\begin{aligned}
		dp_{i-1,j}=z \ \operatorname{or} \  y && x_{i-1}=T\\
		dp_{i-1,j}=z \ \operatorname{and} \  y && x_{i-1}=A\\
	\end{aligned}
\right.
$

- 最后答案是 $dp_{0,0}$ 的真假。

## code:全部都在上面说过，不再加注释

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int maxn=2e6+1;
int n;
string t,x;
int dp[maxn][7];

signed main()
{
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	cin>>t>>x;
	memset(dp,0,sizeof dp);
	dp[n][0]=1;
	for(int i=n;i>=1;i--)
	{
		for(int j=6;j>=0;j--)
		{
			bool z=dp[i][(j*10+t[i-1]-'0')%7];
			bool y=dp[i][j*10%7];
			if(x[i-1]=='T')
			{
				dp[i-1][j]=z||y;
			}
			else
			{
				dp[i-1][j]=z&&y;
			}
		}
	}
	if(dp[0][0])
	{
		cout<<"Takahashi\n";
	}
	else
	{
		cout<<"Aoki\n";
	}
	return 0;
}
```

---

## 作者：yyz_100110 (赞：0)

# [ABC195E Lucky 7 Battle 题解](https://www.luogu.com.cn/problem/AT_abc195_e)


## 思路：

此题为博弈论，但是涉及到了 ```dp```，我们需要判断的是必胜手段。但是可以发现博弈论加上动态规划基本都是从后往前推的，采用倒序方法。

## 做法：

因为我们是要计算必胜手段，所以 $f(n,0)=true$ 是必要的，因为我们只有在 $n$ 轮之后剩余数为 $0$，才能保证一定是 ```Takahashi``` 获胜。

## 方程:

我们需要用到一个很关键的**转移方程**。

- 当 $x(i)$ 为 `True`，$f(i-1,j)=f(i,(j\times10+s(i)-0) \bmod 7) \operatorname{or} f(i,j\times10 \bmod 7)$。

- 当 $x(i)$ 为 `False`,$f(i-1,j)=f(i,(j\times10+s(i)-0) \bmod 7) \operatorname{and} f(i,j\times10 \bmod 7)$。

## Accode:

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n,a[200001];
char c[200001];
int f[200001][11];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        char x;
        cin>>x;
        a[i]=x-'0';
    }
    f[n+1][0]=true; //关键
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=n;i>=1;i--) 
        for(int j=0;j<7;j++){
        if(c[i]=='A')
            f[i][j]=(f[i+1][(j*10)%7]&&f[i+1][((j*10)+a[i])%7]); //如上关键转移方程
        else
            f[i][j]=(f[i+1][(j*10)%7]||f[i+1][((j*10)+a[i])%7]);//如上关键转移方程
    }
    return cout<<(f[1][0]?"Takahashi":"Aoki"),0; //输出判断
}
```

感谢管理员审核！




---

## 作者：Light_Star_RPmax_AFO (赞：0)

## 前言

为了纪念 **长沙市一中** 第二次思维训练。

[传送门](https://www.luogu.com.cn/problem/AT_abc195_e)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-at-abc195-e)

思路——dp

考虑从必胜开始，此时 $f_{n,0}=1$，那么我们往前退如果 $f_{1,0}=1$，也就是说在 $0$ 局的时候是有方案走的，那么就为必胜局面输出 `Takahashi`，反之输出 `Aoki`。

状态转移方程如下

$$\left\{\begin{matrix}
f_{i,j} = f_{{i + 1},{(j \times  10 + a[i]) \mod  7}} \cap f_{{i + 1},{(j \times 10) \mod  7}} & S_i=A
\\f_{i,j} = f_{{i + 1},{(j \times  10 + a[i]) \mod  7}} \cup f_{{i + 1},{(j \times 10) \mod  7}} & S_i=T
\end{matrix}\right.
$$

# AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200010],x,s[200010];
bool f[200010][7];
signed main(){
	cin>>n;
	for(int i = 1;i <= n;i++){
		char ch;
		cin>>ch;
		a[i] = ch - '0';
	}
	for(int i = 1;i <= n;i++){
		char ch;
		cin>>ch;
		s[i] = (ch == 'A');
	}
	f[n + 1][0] = 1;
	for(int i = n;i >= 1;i--)
		for(int j = 0;j < 7;j++){
			if(s[i])f[i][j] = f[i + 1][(j * 10 + a[i]) % 7] & f[i + 1][(j * 10) % 7];
			else f[i][j] = f[i + 1][(j * 10 + a[i]) % 7] | f[i + 1][(j * 10) % 7];
		}
	cout<<(f[1][0] ? "Takahashi" : "Aoki");
	return 0;
}
```



---

