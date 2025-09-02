# [GCJ 2009 Qualification] Welcome to Code Jam

## 题目描述

你已经注册了。我们给你发了一封欢迎邮件，欢迎你来到 code jam。但也许你还没有真正感受到 code jam 的欢迎氛围。这就是为什么我们决定将本题命名为“welcome to code jam”。解决了这道题后，我们希望你能感受到真正的欢迎。真正的欢迎，当然，是来自 code jam。

如果你读了上面这段话，你可能会疑惑它为什么会出现在这里。但如果你非常仔细地阅读，你会发现我们已经多次写下了“welcome to code jam”这句话：总共 400263727 次。毕竟，在这段话中，你完全可以先找到一个 'w'，再找到后面的一个 'e'，再找到后面的一个 'l'，如此下去。你的任务是编写一个程序，统计任意给定文本中，子序列“welcome to code jam”出现了多少次。

更准确地说，给定一个文本字符串，请你确定字符串“welcome to code jam”作为**子序列**在该字符串中出现了多少次。换句话说，找到一个严格递增的下标序列 $s$，使得 input[s[0]]、input[s[1]]、……、input[s[18]] 拼接起来恰好是“welcome to code jam”。

由于结果可能非常大，为了方便，只需要输出答案的最后四位数字。

## 说明/提示

**限制条件**

- $1 \leq N \leq 100$

**小数据集（10 分）**

- 每行长度不超过 $30$ 个字符。

**大数据集（23 分）**

- 每行长度不超过 $500$ 个字符。

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
elcomew elcome to code jam
wweellccoommee to code qps jam
welcome to codejam```

### 输出

```
Case #1: 0001
Case #2: 0256
Case #3: 0000```

# 题解

## 作者：b_donk (赞：3)

## 题目简化

给一个字符串 $S$，求出子序列为 $\texttt{welcome to code jam}$ 的个数，输出答案并保留答案后四位。

## 题目思路

这道题算是一道比较经典的**线性** dp 题，可以用二维 dp 和一维 dp 来写。

### 二维 dp 思路

$dp_{i,j}$ 表示在字符串 $S$ 中，前 $i$ 个字符中，匹配字符串 $\texttt{welcome to code jam}$ 的方案数。如果 $s_i \neq t_j$，那么只能继承前一个状态，即 $dp_{i,j} = dp_{i-1,j}$。否则当 $s_i = t_j$ 时，就可以把选和不选的两种情况的方案数的和相加，也就是 $dp_{i,j} = dp_{i-1,j} + dp_{i-1,j - 1}$。最后答案答案就表示为 $dp_{n,m}$。


### 二维 dp 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const string id = "welcome to code jam"; 
const int MOD = 10000; // 取后四位要用到的
const int N = 1e3+10;
signed main() {
	int T;
	cin >> T;
	cin.ignore(); // 防止换行符影响到答案
	for(int x = 1; x <= T; x ++) {
		string s;
		getline(cin, s);
		int n = s.size();
		int m = id.size();
		int dp[N][N];
		for(int i = 1; i <= n; i ++) {
			dp[i][0] = 1; // 初始化
			for(int j = 1; j <= m; j ++) {
				dp[i][j] = dp[i-1][j];
				if(s[i-1] == id[j-1]) { // 当字符匹配的时候
					dp[i][j] += dp[i-1][j-1]; // 更新 dp[i][j] 的值
					dp[i][j] %= MOD; // 因为这里要取后四位， 所以这里要 mod 10000
				}
			}
		}
		cout << "Case #" << x << ": ";
		cout << setw(4) << setfill('0') << dp[n][m] << '\n'; // 输出的时候如果后四位位数不够 补充0
	}
	return 0;
}
```

### 一维 dp 思路

如果字符串 $S$ 的长度变得更大的话，那么二维 dp 就会超空间，所以说我们需要写出一种空间复杂度只有 $O(N)$ 的写法，我们减去一个维度，其中 $dp_j$ 表示匹配到目标字符串前 $j$ 个字符的方案数，注意循环要**从后往前**遍历，不然会出现重复统计答案的情况。
当 $s_i = id_{j - 1}$ 时，我们需要累加答案，所以状态转移方程为 $dp_j = dp_j + dp_{j-1}$。最后 $dp_n$ 就表示最后算出来的答案了。

### 一维 dp 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e4+5;
const int MOD = 10000;
string id = "welcome to code jam";
signed main() {
	int t;
	cin >> t;
	cin.ignore(); // 防止换行符影响到答案
	for(int x = 1; x <= t; x ++) {
		int dp[N];
		string s;
		getline(cin, s);
		memset(dp, 0, sizeof(dp));
		dp[0] = 1; // 初始化答案
		int n = s.size();
		int m = id.size();
		for(int i = 0; i < n; i ++) {
			for(int j = m; j >= 1; j --) { // 从后往前遍历防止重复计数
				if(s[i] == id[j-1]) {
					dp[j] = (dp[j] + dp[j-1]) % MOD; // mod 10000是因为要取后4位
				}
			}
		}
		cout << "Case #" << x << ": " << setw(4) << setfill('0') << dp[m] << '\n';
	}
	return 0;
}
```

### [一维 dp AC记录](https://www.luogu.com.cn/record/226834823)
### [二维 dp AC记录](https://www.luogu.com.cn/record/226793713)

希望这篇题解能够帮助你更好的完成这道题。

---

## 作者：zhongjunnan561234 (赞：1)

# 题意
题目给定一个字符串，要求统计其中 `welcome to code jam` 作为子序列出现的次数。即找出所有严格递增的位置序列，使得按这些位置依次选取的字符恰好组成目标字符串。由于结果可能非常大，为了方便，只用输出答案的最后四位数字即可。
# 思路
这是一道线性 DP 问题，可以用二维 DP 求解。

  $dp_{i,j}$ 表示字符串 $S$ 的前 $i$ 个字符中，匹配目标串前 $j$ 个字符的方案数。
若 $S_{i} ≠ T_{j}$，则 $dp_{i,j} = dp_{i,j}$（不选当前字符）。
若 $S_{i} = T_{j}$，则 $dp_{i,j} = dp_{i-1,j}+dp_{i-1,j-1}$（选或不选当前字符）。
最终答案为 $dp_{n,m}$。
# AC Code
```
#include <bits/stdc++.h>
using namespace std;
const string target="welcome to code jam";
const int MOD=10000;
int main() {
    int N;
    cin>>N;
    cin.ignore();
    for(int x=1;x<=N;x++) {
        string s;
        getline(cin, s);
        int n=s.size();
        int m=target.size();
        vector<vector<int>>dp(n+1,vector<int>(m+1,0));
        for (int i=0;i<=n;i++) {
            dp[i][0]=1;
        }
        for (int i=1;i<=n;++i) {
            for (int j=1;j<=m;j++) {
                dp[i][j]=dp[i-1][j];
                if (s[i-1]==target[j-1]) {
                    dp[i][j]+=dp[i-1][j-1];
                    dp[i][j]%=MOD;
                }
            }
        }
        int ans=dp[n][m]%MOD;
        printf("Case #%d: %04d\n",x,ans);
    }
    return 0;
}
```

---

## 作者：koukou (赞：1)

经典的动态规划问题。

不难想到，我们可以定义状态 $dp_i{_j}$ 为文本前 $i$ 各字符中 `welcome to code jam` 的前 $j$ 各字符出现的次数。状态转移也很容易，首先先保持原来的状态，即 $dp_i{_j} = dp_i{_j} + dp_{i-1}{_j}$，如果这个字符匹配，则 $dp_i{_j} = dp_i{_j} + dp_{i-1}{_{j-1}}$，最后的答案就是 $dp_{len}{_{19}}$（因为我的下标从 $1$ 开始）。\
还有一个问题，初始化是什么呢？不难想到，就是 $dp_i{_0} = 0$。

总体来说还是比较简单的，代码：

```
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e4;
const int N = 5e2 + 1;
const string fd = " welcome to code jam";
string a;
int T, n, dp[N][20];
int main() 
{
	cin >> T;
	getline(cin, a);//过滤掉末尾换行
	for(int id = 1; id <= T; id++)
	{
		getline(cin, a);//读入一个字符串
		n = a.size();
		a = " " + a;
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;//初始化
		for(int i = 1; i <= n; i++)
		{
			dp[i][0] = 1;//初始化
			for(int j = 1; j <= 19; j++)
			{
				dp[i][j] = dp[i - 1][j];
				if(a[i] == fd[j]) dp[i][j] += dp[i - 1][j - 1];
				dp[i][j] %= mod;//状态转移
			}
		}
		cout << "Case #" << id << ": " << setw(4) << setfill('0') << dp[n][19] << "\n";//保留后4位输出
	}
    return 0;
}
```

---

## 作者：Clouds_dream (赞：1)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13430)  
即统计给定字符串中 `welcome to code jam` 作为子序列出现的次数。
::::info
在下文中，$s$ 表示给定的字符串，$t$ 表示目标字符串，即 `welcome to code jam`。
::::
### 题目分析
我们可以用动态规划来解决这道问题。  
我们设 $dp_{i,j}$ 表示在 $s$ 的前 $i$ 个字符中等于 $t$ 前 $j$ 个字符的子序列数量。  

我们有两种基本情况：

- 当 $j = 0$ 时，表示 $t$ 为空，此时只有一种方式，即不选任何字符，所以 $dp_{i,0} = 1$。
- 当 $i = 0$ 且 $j > 0$ 时，表示 $s$ 为空，所以 $dp_{0,j} = 0$。

那么如何得到动态转移方程呢？  

我们需要考虑两种情况：

- **当前字符不匹配**：如果 $s$ 的第 $i$ 个字符不等于 $t$ 的第 $j$ 个字符，那么当前字符不能用于匹配 $t$ 的第 $j$ 个字符。所以，子序列的数量等于前 $i-1$ 个字符匹配前 $j$ 个字符的数量，即 $dp_{i,j} = dp_{i-1,j}$。
- **当前字符匹配**：那么当前字符可以用于匹配 $t$ 的第 $j$ 个字符。此时，子序列的数量包括两部分：
    - 不使用当前字符匹配第 $j$ 个字符的数量：$dp_{i-1,j}$。
    - 使用当前字符匹配第 $j$ 个字符的数量：$dp_{i-1,j-1}$。

综上所述，动态转移方程为：
$$
dp_{i,j} = \begin{cases} 
    dp_{i-1,j} + dp_{i-1,j-1} & (s_i = t_j) \\
    dp_{i-1,j} & (s_i \neq t_j) 
\end{cases}
$$
::::warning[注意]
不要忘了取模！！！
::::

### 代码实现
```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int P = 10000;//！！！

string t="welcome to code jam";//目标字符串

void f(int ti){
	string s;//给定字符串
	getline(cin,s);
    int n=s.size();
    int m=t.size();
	int dp[510][510];
	for(int i=0;i<=n;i++){
		dp[i][0]=1;//初始化
	}
	for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=dp[i-1][j];
            if(s[i-1]==t[j-1]){
                dp[i][j]+=dp[i-1][j-1];
                dp[i][j]%=P;
            }
        }
    }
    printf("Case #%lld: %04lld\n",ti,dp[n][m]);
}

signed main()
{
	fst
	int ti;
	cin>>ti;
    cin.ignore();//去除第一行的换行符
	for(int i=1;i<=ti;i++){
		f(i);
	}
	return 0;
}
```

---

## 作者：Hkb150429 (赞：1)

## 题意

更准确地说，给定一个文本字符串，请你确定字符串`welcome to code jam`作为**子序列**在该字符串中出现了多少次。换句话说，找到一个严格递增的下标序列 $s$，使得 $input[s[0]]$、$input[s[1]]$、……、$input[s[18]]$ 拼接起来恰好是`welcome to code jam`。由于结果可能非常大，为了方便，只需要输出答案的最后四位数字。

## 思路

$dp$ 是一个二维数组，$dp[i][j]$ 表示处理到输入字符串前 $i$ 个字符时，匹配到目标字符串前 $j$ 个字符的子序列数目。初始化时，$dp[i][0] = 1$ 表示空子序列的匹配数为 $1$。遍历输入字符串的每个字符，检查是否与目标字符串的当前字符匹配。如果匹配，则更新 $dp[i][j]$ 为不选当前字符和选当前字符的方案数之和，否则就是前一个状态的值，每次更新后取模 $10000$ 就可以了。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const char* mubiao="welcome to code jam";
int main() {
    int mc=19;
    int t;
    cin>>t;
    cin.ignore();
    for(int i=1;i<=t;i++){
        string s;
        getline(cin,s); 
        int dp[19+5]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        for(int i2=0;i2<s.size();i2++) {
            char c=s[i2];
            for(int j=mc;j>=1;j--) {
                if(c==mubiao[j-1]) {
                    dp[j]=(dp[j]+dp[j-1])%10000;
                }
            }
        }
        int ans=dp[mc]%10000;
        cout<<"Case #"<<i<<": ";
        if(dp[mc]<10)cout<<"000"<<dp[mc];
        else if(dp[mc]<100)cout<<"00"<<dp[mc];
        else if(dp[mc]<1000)cout<<"0"<<dp[mc];
        else cout<<dp[mc];
        cout<<endl;
    }

    return 0;
}
```

---

## 作者：yihang2011 (赞：0)

### [P13430 [GCJ 2009 Qualification] Welcome to Code Jam](https://www.luogu.com.cn/problem/P13430)

动态规划简单题。

记目标字符串 $g$ 为 ` welcome to code jam`。

记 $f_{i, j}$ 为在字符串 $s$ 的前 $i$ 个字符中为 $g$ 的前 $j$ 个字符的子序列个数。

很好想到转移，枚举 $i, j$，若 $s_i = g_j$，则有 $f_{i, j} = f_{i - 1, j} + f_{i - 1, j - 1}$，否则 $f_{i, j} = f_{i - 1, j}$。

初始状态 $f = 0, f_{i, 0(0 \le i \le 19)} = 1$。

最终答案为 $f_{n, m}$，其中 $n$ 为 $s$ 的长度，$m$ 为 $g$ 的长度，即 $m = 19$。

记得取模。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define seta(f, x) memset(f, x, sizeof f)
using ll = long long;
#define gc getchar()
ll read() { ll x = 0, f = 1; char ch = gc; while (ch < '0' || ch > '9') { if (ch == '-') { f = -1; } ch = gc; } while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0', ch = gc; } return x * f; }
#define rd read()
void write(const string& s) { for (char c : s) { putchar(c); } }
void write(ll x) { if (x < 0) { putchar('-'), x = -x; } if (x > 9) { write(x / 10); } putchar(x % 10 + '0'); }
void write(double x, int len) { ll i = x, s = round(1.0 * (x - i) * (pow(10, len))); write(i); putchar('.'); write(s); } 
template<typename... Args> void wrt(ll x, Args... rest) { write(x); if constexpr (sizeof...(rest) > 0) { putchar(' '); wrt(rest...); } }
template<typename... Args> void wrln(ll x, Args... rest) { write(x); if constexpr (sizeof...(rest) > 0) { putchar(' '); wrln(rest...); } else { putchar('\n'); } }
#define wln(x) write(x); putchar('\n')
#define wt(x) write(x); putchar(' ')

const int N = 5e2 + 10, M = 20, mod = 1e4;
int n, m = 19, f[N][M];
string g = " welcome to code jam";

string solve(string s) {
    seta(f, 0);
    n = s.size();
    s = " " + s;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = 1;
        for (int j = 1; j <= m; j++) {
            f[i][j] = f[i - 1][j];
            if (s[i] == g[j]) {
                f[i][j] += f[i - 1][j - 1];
            }
            f[i][j] %= mod;
        }
    }
    if (f[n][m] < 10) {
        return "000" + to_string(f[n][m]);
    } else if (f[n][m] < 100) {
        return "00" + to_string(f[n][m]);
    } else if (f[n][m] < 1000) {
        return "0" + to_string(f[n][m]);
    } else {
        return to_string(f[n][m]);
    }
}

int main() {
    int T = rd;
    for (int i = 1; i <= T; i++) {
        string s;
        getline(cin, s);
        write("Case #"), write(i), wt(":"), wln(solve(s));
    }
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/230592002)

~~写完才发现 `cout` 和 `printf` 都有格式化输出但我自己写了快写。~~

---

## 作者：Zayn_Pan (赞：0)

## 题目

戳[这里](https://www.luogu.com.cn/problem/P13430)看题目。

## 思路

DP。

首先定义输入的字符串为 $a$ 一个标准字符串  $b=$`welcome to code jam`。

#### 状态定义

我们要对比 $a$ 和 $b$，所以状态有两维。

$dp_{i,j}$ 表示 $a$ 的前 $i$ 位中 $b$ 的前 $j$ 个字符的出现次数。

#### 转移

对于 $a_i\ne b_j$ 的情况，我们继承前一位的答案。

对于 $a_i=b_j$ 的情况，有选和不选两种，所以次数加上这两种。

更加直观的：

$\begin{cases}
dp_{i,j}=dp_{i-1,j},a_i\ne b_j
\\dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-1},a_i=b_j
\end{cases}$

发现可以压维，也就是 $dp_j$ 表示 $b$ 的第 $1$ 至 $j$ 在 $a$ 中的出现次数。

转移：

$\begin{cases}
dp_{j}=dp_{j},a_i\ne b_j
\\dp_{j}=dp_{j}+dp_{j-1},a_i=b_j
\end{cases}$

初始化 $dp_0=1$。

注意 $j$ 要从大到小枚举，不然会算重。

对于这个神秘输出，只用答案对 $10000$ 取模后在前面补零即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,dp[20];
string a,b="welcome to code jam";
int main(){
    cin>>T;
    cin.ignore();
    for(int k=1;k<=T;k++){
        getline(cin,a);
        int n=a.size(),m=b.size();
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        for(int i=0;i<n;i++){
            for(int j=m;j>=1;j--){
                if(a[i]==b[j-1])dp[j]=(dp[j]+dp[j-1])%10000;
            }
        }
        cout<<"Case #"<<k<<": ";
        dp[m]%=10000;
        if(dp[m]>=1000)cout<<dp[m];
        else if(dp[m]>=100&&dp[m]<1000)cout<<"0"<<dp[m];
        else if(dp[m]>=10&&dp[m]<100)cout<<"00"<<dp[m];
        else cout<<"000"<<dp[m];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：Nahia (赞：0)

### 思路

一眼**动态规划**。

定义 $s$ 为待测字符串，$e$ 为 `welcome to code jam`。

定义 $f_{i,j}$ 为 $s$ 的前 $i$ 个字符中 $e$ 的前 $j$ 个字符出现的次数。

如何状态转移？

- 如果 $s_i = e_j$，$f_{i,j} \gets f_{i,j}+f_{i-1,j-1}$。

- 否则，$f_{i,j} \gets f_{i,j}+f_{i-1,j}$。

答案存储在 $f_{|s|,19}$ 中（$|s|$ 为 $s$ 的长度，下标从 $1$ 开始）。

如何初始化？对于 $1 \sim n$ 的每一个 $i$，初始化 $f_{i,0}$ 为 $1$ 即可。

:::warning[注意]
记得**取模**。
:::

### solution

```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
string e = " welcome to code jam",s;
int f[505][20];
int main(){
    int t;
	cin>>t;
	getline(cin, s);//过滤掉数字后的换行
	for(int cnt = 1;cnt<=t;cnt++){
		getline(cin,s);
		int len = s.size();
		s = " " + s;
		memset(f, 0, sizeof(f));
		for(int i = 0;i<=len;i++) f[i][0] = 1;
		for(int i = 1; i<=len; i++){
			for(int j = 1; j<=19; j++){
				f[i][j] = f[i - 1][j];
				if(s[i] == e[j]) f[i][j] += f[i - 1][j - 1];
				f[i][j] %= 10000;//记得取模 
			}
		}
		cout<<"Case #"<<cnt<<": "<<setw(4)<<setfill('0')<<f[len][19]<<"\n";//保留后4位输出
	}
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

## 思路

此题为动态规划经典题型。

换句话说，我们要比较原字符串 $S$ **子序列** $\texttt{welcome to code jam}$（以下简称为 $S'$）的个数。

可以去做“最长上升子序列”的题目再做此题印象会更深。

设 $f_{i,j}$ 表示在 $S$ 前 $i$ 个字符有多少个子序列为 $S'$ 前 $j$ 个字符。

则有：

$$
f_{i,j} = \begin{cases} 
f_{i-1,j}+f_{i-1,j-1} & \text{if } S_i = S'_j \text{ and }i,j\not=0\\
f_{i-1,j} & \text{if } S_i\not=S'_j \text{ and } i,j\not=0
\end{cases}
$$

初始条件 $f_{i,0}=1$，因为 $S'$ 若为空串也是 $S$ 的一个子序列。

最后答案为 $f_{n,m}\bmod 10000$，$n$ 为 $S$ 的长度，$m$ 为 $S'$ 的长度，即为 $19$，不足 $4$ 位补零。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[505][505];
int main(){
    int t;
    cin>>t;
    int q=t;
    cin.ignore();
    while(t--){
        cout<<"Case #"<<q-t<<": ";
        string target="welcome to code jam";
        memset(f,0,sizeof f);
        string s;
        getline(cin,s);
        int n=s.size();
        int m=target.size();
        for(int i=0;i<=n;i++)f[i][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                f[i][j]=f[i-1][j];
                if(s[i-1]==target[j-1]){
                    f[i][j]+=f[i-1][j-1];
                    f[i][j]%=10000;
                }
            }
        }
        printf("%04d\n", f[n][m]%10000);
    }
    return 0;
}
```

---

## 作者：Zjb13927701829 (赞：0)

# P13430 [Welcome to Code Jam](https://www.luogu.com.cn/problem/P13430) 题解
[~~评测机咋了？~~](https://cdn.luogu.com.cn/upload/image_hosting/5znpa2qn.png)
## 题目大意
题目给定一个文本字符串，请我们确定字符串`welcome to code jam`作为子序列在该字符串中出现了多少次。换句话说，找到一个严格递增的下标序列 $s$，使得 $input_{s_{0}}$、$input_{s_1}$、……、$input_{s_{18}}$ 拼接起来恰好是`welcome to code jam`。
## 解题思路
这是一道~~典型的~~DP题。

我们可以定义动规数组 $dp_{i,j}$，表示在前 $i$ 个字符中匹配到目标字符串的前 $j$ 个字符时的方案数，其中：
- $i$ 负责遍历输入字符串的每个位置（从 $1$ 开始）。
- $j$ 负责遍历目标字符串的每个位置（从 $0$ 到 $18$，因为目标长度是 $19$）。

**注意**：初始化时，$dp_{0,0} = 1$，表示空字符串匹配空模式有一种方式。其他初始值为 $0$。

## 动态转移方程
对于每一个输入的字符 $s_{i-1}$：
- 如果它等于目标字符串的第 $j$ 个字符（即 $tg_j$），那么我们可以选择是否使用这个字符来**扩展**之前的匹配。具体来说：

  ◦如果不使用当前字符，那就保持原来的状态：
  `dp[i][j] += dp[i-1][j]`。

  ◦否则，就需要从前一步的 $j-1$ 状态转移过来：`dp[i][j] += dp[i-1][j-1]`。
- 如果不等于，那只能不选当前字符：`dp[i][j] += dp[i-1][j]`。

## 一些优化
我们注意到 $dp_{i,j}$ 只依赖于 $dp_{i-1,***}$，因此可以将二维数组优化为一维数组，按逆序更新以避免覆盖未处理的数据。


根据**动规的原理**，最终的结果是 `dp[len(tg)]`，即整个输入的字符串完全匹配目标字符串的所有方式的数量。\
由于结果可能很大，我们只需要最后四位数字就行了。

下面放出代码，细节都写在注释里面了，敬请各位观看。
## [AC](https://www.luogu.com.cn/record/226619738) Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    // 目标字符串
    const char* target = "welcome to code jam";
    // 目标字符串的长度
    int m = 19;

    int T;     
    cin >> T;  
    cin.ignore(); // 忽略换行符，防止影响后续getline()读取整行内容

    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        char line[501]; 
        cin.getline(line, sizeof(line)); // 读取一整行（包括空格）

        long long dp[m + 1];
        memset(dp, 0, sizeof(dp)); // 初始化
        dp[0] = 1; // 初始状态

        // 遍历输入字符串中的每一个字符
        for (int i = 0; line[i] != '\0'; ++i) {
            char curC = line[i]; // 当前的字符
            for (int j = m; j >= 1; --j) {
                // 如果当前字符与目标串的第j-1个字符相等
                if (curC == target[j - 1]) {
                    // 更新dp[j]
                    dp[j] = (dp[j] + dp[j - 1]) % 10000;
                }
            }
        }

        // 最终结果是dp[m]
        int res = dp[m] % 10000;
        printf("Case #%d: %04d\n", caseNum,res); // 输出四位数，不足补前导零
    }

    return 0;
}
```
`审核题解不易，管理员辛苦了！`

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13430)

# 题目分析

使用动态规划。

### 定义状态：

设 $f_{i,j}$ 表示使用给定字符串的前 $i$ 个字符拼出目标字符串的前 $j$ 个字符（必须使用第 $i$ 个字符）的方案数。注意，$i$ 从 $0$ 开始，而 $j$ 从 $1$ 开始。

### 初始状态：

如果给定字符串第 $0$ 个字符是 w，则 $f_{0,1}=1$，否则初始时 $f$ 全为 $0$。

### 状态转移方程

显然，对于给定字符串的第 $i$ 个字符，定义 $d_i$ 表示字符 $i$ 在目标字符串中出现的次数，二维数组 $s$，$s_{i,t}$ 为字符 $i$ 在目标字符串中出现的位置，$t$ 满足 $1\le t\le d_i$。下面分类讨论。

设给定字符串中第 $i$ 个字符为 $c$。

- 如果 $c$ 不是 w，则第 $i$ 个字符有可能拼出目标字符串的前 $s_{i,t}$ 个字符。枚举 $t$ 从 $1$ 到 $d_i$。若想用第 $i$ 个字符和 前 $i-1$ 个字符中的若干个拼出目标字符串的前 $s_{i,t}$ 个字符，就需要找一个 $k<i$ 使得用第 $k$ 个字符和前 $k-1$ 个字符拼出目标字符串的前 $s_{i,t}-1$ 个字符，然后在用上第 $i$ 个字符就拼出了目标字符串的前 $s_{i,t}$ 个字符。因此可列出状态转移方程：

   $$f_{i,s_{i,t}}=\sum\limits_{k=0}^{i-1} f_{k,s_{i,t}-1}$$

- 如果 $c$ 是 w，则有 $s_{i,1}=1$ 且 $d_i=1$。因此此时 $f_{i,s_{i,t}}=f_{i,1}=1$。

因此有状态转移方程：

$$f_{i,s_{i,t}}=\begin{cases} \sum\limits_{k=0}^{i-1} f_{k,s_{i,t}-1}& \text {if } c \ne 'w'\\1& \text {if } c='w' \end{cases}$$

最后的答案为

$$\sum\limits_{k=0}^{n-1} f_{k,19}$$

# 代码

```cpp
#include<bits/stdc++.h>
#define N 505
#define M 25
#define P 10000
using namespace std;
//w:1
//e:2,7,15
//l:3
//c:4,12
//o:5,10,13
//m:6,19
// :8,11,16
//t:9
//d:14
//j:17
//a:18
long long f[N][M];
int jl[35][10]={0},siz[35]={0};
inline void make(){
    jl['w'-'a'][1]=1;
    jl['e'-'a'][1]=2;jl['e'-'a'][2]=7;jl['e'-'a'][3]=15;
    jl['l'-'a'][1]=3;
    jl['c'-'a'][1]=4;jl['c'-'a'][2]=12;
    jl['o'-'a'][1]=5;jl['o'-'a'][2]=10;jl['o'-'a'][3]=13;
    jl['m'-'a'][1]=6;jl['m'-'a'][2]=19;
    jl[30][1]=8;jl[30][2]=11;jl[30][3]=16;
    jl['t'-'a'][1]=9;
    jl['d'-'a'][1]=14;
    jl['j'-'a'][1]=17;
    jl['a'-'a'][1]=18;
    siz['w'-'a']=1;
    siz['e'-'a']=3;
    siz['l'-'a']=1;
    siz['c'-'a']=2;
    siz['o'-'a']=3;
    siz['m'-'a']=2;
    siz[30]=3;
    siz['t'-'a']=1;
    siz['d'-'a']=1;
    siz['j'-'a']=1;
    siz['a'-'a']=1;
    return;
}
int main(){
    make();
    int t;
    cin>>t;
    char c[N];
    cin.getline(c,501);
    for(int o=1;o<=t;o++){
        cout<<"Case #"<<o<<": ";
        cin.getline(c,501);
        int len=strlen(c);
        for(int i=0;i<=len;i++){
            for(int j=0;j<25;j++){
                f[i][j]=0;
            }
        }
        if(c[0]=='w'){
            f[0][1]=1;
        }
        for(int i=1;i<len;i++){
            if(c[i]!=' '){
                for(int j=1;j<=siz[c[i]-'a'];j++){
                    if(jl[c[i]-'a'][j]==1){
                        f[i][1]=1;
                    }
                    else{
                        for(int k=0;k<i;k++){
                            f[i][jl[c[i]-'a'][j]]=(f[i][jl[c[i]-'a'][j]]+f[k][jl[c[i]-'a'][j]-1])%P;
                        }
                    }
                }
            }
            else{
                for(int j=1;j<=siz[30];j++){
                    for(int k=0;k<i;k++){
                        f[i][jl[30][j]]=(f[i][jl[30][j]]+f[k][jl[30][j]-1])%P;
                    }
                }
            }
        }
        int ws=0;
        long long f2=0,f3;
        for(int i=0;i<len;i++){
            f2=(f2+f[i][19])%P;
        }
        f3=f2;
        if(f2==0){
            cout<<"0000"<<endl;
            continue;
        }
        while(f2){
            ws++;
            f2/=10;
        }
        if(ws<4){
            for(int i=ws;i<4;i++){
                cout<<0;
            }
        }
        cout<<f3<<endl;
    }
    return 0;
}
```

---

