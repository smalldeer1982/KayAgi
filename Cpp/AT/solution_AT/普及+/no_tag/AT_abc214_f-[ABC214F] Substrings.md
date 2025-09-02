# [ABC214F] Substrings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc214/tasks/abc214_f

文字列 $ S $ が与えられます。高橋君はこの文字列から以下の手順にしたがって新しい文字列 $ T $ を作ります。

- まず、$ S $ の文字のうちの一つ以上に印をつける。ただし、印をつけた文字どうしが隣り合ってはならない。
- 次に、印がついていない文字を全て削除する。
- 最後に、残った文字列を $ T $ とする。ただし、この時に文字を並び替えてはならない。

$ T $ としてありうる文字列は何種類ありますか？ $ (10^9\ +\ 7) $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ S $ は英小文字のみからなる長さ $ 1 $ 以上 $ 2\ \times\ 10^5 $ 以下の文字列

### Sample Explanation 1

$ T $ としてありうるものは `a`、 `b`、 `c`、 `ac` の $ 4 $ つです。 $ S $ の $ 1 $ 文字目のみに印をつけたとき $ T $ は `a`、 $ S $ の $ 2 $ 文字目のみに印をつけたとき $ T $ は `b`、 $ S $ の $ 3 $ 文字目のみに印をつけたとき $ T $ は `c`、 $ S $ の $ 1 $ 文字目と $ 3 $ 文字目のみに印をつけたとき $ T $ は `ac`、 となります。例えば $ 1 $ 文字目と $ 2 $ 文字目の両方に印をつけることはできないことに注意してください。

### Sample Explanation 2

$ T $ としてありうるものは `a` のみです。 印をつけた位置が異なっていても $ T $ が同じ文字列となる可能性があることに注意してください。

### Sample Explanation 3

$ T $ としてありうるものは `a`、 `b`、 `c`、 `aa`、 `ab`、 `ca` の $ 6 $ つです。

## 样例 #1

### 输入

```
abc```

### 输出

```
4```

## 样例 #2

### 输入

```
aa```

### 输出

```
1```

## 样例 #3

### 输入

```
acba```

### 输出

```
6```

## 样例 #4

### 输入

```
chokudai```

### 输出

```
54```

# 题解

## 作者：songge888 (赞：4)

### 题意

给你一个字符串 $S$，求去除若干个不相邻的字符后得到的不同的字符串的个数。

### 思路

考虑 DP，$dp_{i,j}$ 表示前 $i$ 位以字母 $j$ 为结尾的不同字符串的个数。

对于 $S_i$：

+ 若 $S_i=j$，$dp_{i,j}= \sum_{k=1}^{26} dp_{i-2,k} +1$。
+ 若 $S_i \ne j$，$dp_{i,j}=dp_{i-1,j}$。

最后答案就是 $\sum_{i=1}^{26} dp_{n,i}$。

时间复杂度比 $O(n)$ 大一点，但是实际上达不到，可以通过此题。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define bug cout<<"___songge888___"<<'\n';
using namespace std;
string s;
int n;
int dp[200010][30];
int get(char c){
	return c-'a'+1;
}
int ans;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s;
	n=s.size();
	s=' '+s;
//	cout<<get(s[1])<<'\n';
	dp[1][get(s[1])]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=26;j++){
			if(get(s[i])==j){
				for(int k=1;k<=26;k++){
					dp[i][j]+=dp[i-2][k];
				}
				dp[i][j]++;
			}
			else{
				dp[i][j]=dp[i-1][j];
			}
			dp[i][j]%=1000000007;
		} 
	}
	for(int i=1;i<=26;i++){
//		cout<<ans<<'\n';
		ans+=dp[n][i];
		ans%=1000000007;
	}
	cout<<ans;
	return 0;
}

```

[提交记录](https://atcoder.jp/contests/abc214/submissions/62890195)

---

## 作者：StevenLiTheOIer (赞：4)

## 思路：
字符串 dp。设 $dp_{i,j}$ 表示考虑到第 $i$ 位，尾部字母为 $j$ 的方案数。则很明显，当结尾字母不等于当前字母时，对答案没有影响，即 $dp_{i,j}=dp_{i-1.j}$。当结尾字母等于当前字母时，最后结尾的字母要从 $s_{i-2}$ 位转移过来，再加上最后这一个字母的方案。所以 $dp_{i,j}=\sum_{k} dp_{i-2,k}+1$，用前缀和优化统计即可 $O(1)$ 转移。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
long long dp[200006][26], sum[200006];
string s;
int main()
{
	cin >> s;
	int n = s.size();
	dp[1][s[0] - 'a'] = sum[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (s[i - 1] != j + 'a') dp[i][j] = dp[i - 1][j];
			else dp[i][j] = (sum[i - 2] + 1) % mod;
			sum[i] = (sum[i] + dp[i][j]) % mod;
		}
	}
	cout << sum[n] << endl;
	return 0;
}
```

---

## 作者：Misty_Post (赞：1)

模拟赛没有拿下绿题，在深刻反思后写下此题解，借此警钟长鸣。

### 题意
给出一个字符串，可以给其中任意个字符打上标记，但是要保证标记不相邻。

然后把所有打了标记的字符组合形成一个字符串，问能组成多少种不相同的字符串。

### 分析

考虑到 $n$ 范围不小，但可以发现字母只有26种，遂考虑使用动态规划。

设 $f_{i,j}$ 为前 $i$ 个字母以 $j$ 结尾的方案数。

显然，若 $S_i=j$ 的话，就可以化成 $dp_{i,j}=dp_{i-2,a}+dp_{i-2,b}+...+dp_{i-2,z}+1$ 这样，可以使用前缀和优化，当然也可以不用，毕竟数据范围不大。

否则，化成 $dp_{i,j}=dp_{i-1,j}$。

这样就做完啦。

---

## 作者：returnzheng (赞：1)

这道题乍一看数据范围，$|S| \le 2 \times 10^{5}$，以为要 $O(n)$，实则不然，调了我一天。

思路比较简单。考虑第一个字符为 $S_i$，第二个字符为 $S_j$，只要有一个字符 $S_{i'}$ 可以替代 $S_i$，也就是说存在 $S_{i'}$ 使得 $S_{i'} = S_i \land i + 2 < i'\le j - 2$，就不能累加到当前答案。所以只需循环到符合条件就退出循环即可。 

定义 $f_i$ 为字符串中下标 $i$ 之后的子串按题目中的规则能产生多少种方案。对于转移，先看一下当前字母有没有出现过，如果没有初始化为 $1$，否则为 $0$。暴力从  $i+2$ 到 $n$。当遍历到第 $j$ 个位置时，如果 $S_{j - 2} = S_i \land j \ne i + 2$ 时就退出循环，否则就累加到 $f_i$。虽然是 $O(n^2)$ 的，但是跑不满，还是能过的。

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long f[300000];
long long v[30];
bool vis[30];
long long mod = 1e9 + 7;
int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    string s;
    cin >> s;
    long long n = s.size();
    s = ' ' + s;
    f[n] = 1;
    if (n == 1){
        cout << 1 << '\n';
        return 0;
    }
    if (s[n] == s[n - 1]){
        f[n - 1] = 0;
    }
    else{
        f[n - 1] = 1;
    }
    vis[s[n] - 'a'] = true;
    vis[s[n - 1] - 'a'] = true;
    for (long long i = n - 2; i >= 1; i--){
        if (vis[s[i] - 'a'] == false){//初始化
            vis[s[i] - 'a'] = true;
            f[i] = 1;
        }
        else{
            f[i] = 0;
        }
        for (int j = i + 2; j <= n; j++){
            if (s[j - 2] == s[i] && j != i + 2){//存在可替代的S[i']
                break;
            }
            f[i] += f[j];
            f[i] %= mod;
        }
    }
    long long ans = 0;
    for (long long i = 1; i <= n; i++){
        ans += f[i];
        ans %= mod;
        // cout << f[i] << ' ';
    }
    // cout << '\n';
    cout << ans << '\n';
    return 0;
}
/*
堆积如山的hack
abc
4

aa
1

acba
6

chokudai
54

aaaaaa
3

aaaaaab
7

abaa
4

baaaaaa
7
*/
```

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题一看就是动态规划，所以我们就来想状态，我们定义 $f_{i,j}$ 为前 $i$ 个字符串组合出来以 $j$ 结尾的总方案数，这一我们在输出是做一点小优化，我们将 $f_{i,26}$ 存为前 $i$ 个数的总方案数，那么我们在每一层循环后都将 $f_{i,26}=f_{i,26}+f_{i,j}$ 即可。

现在我们来思考状态转移方程，对于每一个 $j$ 和 $s_i$ 都可以分成两种情况讨论，第一种 $j$ 不等于 $s_i$  那么我们就直接将 $f_{i,j}=f_{i-1,j}$ 即可，这个就不解释了。第二种 $j$ 等于 $s_i$ 那么我们就可以发现不取 $j$ 的话就位 $f_{i-1,j}$ 若取第 $i$ 为就是 $f_{i-2,26}$ 因为这里没有影响毕竟我们都要往后面加上一个 $s_i$ 呀，并且之前的也肯定是去过重的。但是最后还要在 $f_{i-2,26}$ 后加一个 $1$ 毕竟只有一个 $s_i$ 也是嘛。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
inline void read(int &x) {
	int f=0,s=1;
	char c=' ';
	while(c>'9'||c<'0') {
		if(c=='-') s=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		f=f*10+c-'0';
		c=getchar();
	}
	x=f*s;
}
const int mod=1e9+7;
const int N=2e5+10;
const int M=30;
int f[N][M];
string s;
fire main() {
	cin>>s;
	int n=s.size();
	s=' '+s;
	f[1][s[1]-'a']=f[1][26]=1; //初始化
	rep(i,2,n) {
		rep(j,0,25) {
			if(s[i]!=j+'a') f[i][j]=f[i-1][j]; //分类讨论
			else f[i][j]=(f[i-2][26]+1)%mod;
			f[i][26]+=f[i][j];
			f[i][26]%=mod;
		}
	}
	cout<<f[n][26]; //输出
	return false;
}
```


---

## 作者：YuYuanPQ (赞：0)

看到这个题没有想到 DP，大失败。

---

按[官解](https://atcoder.jp/contests/abc214/editorial/2447)转化一下题意：

> 找出 $S$ 的非空子串个数。在这里，子串是原字符串去掉 $0$ 个或 $0$ 个以上字符后的无序连接。

这个时候再加上限制条件：当前取的这一个不能与上一个相邻。

那么个人认为 DP 思路就很好想了：

设 $dp_{i,j}$ 表示到第 $i$ 位，以 $j$ 这个字符（实际编码时是转化了一下的）结尾的方案数。

分类讨论：

- 如果 $s_i=j$，即当前取的这一个与上一个相邻，那就只能用再上一个，即 $i-2$ 的来转移，然后加上当前这个新方案。（这是满足题目的限制）
- 如果 $s_i\neq j$，那么就从上一个（即第 $i-1$ 个）转移。

得到的转移方程就是：

当 $s_i=j$ 时：$dp_{i,j}=dp_{i-2,j}+1$。\
当 $s_i\neq j$ 时：$dp_{i,j}=dp_{i-1,j}$。

（那个像函数一样的表示出来的比较直观，但是不会打，会打了再更）

记得取模。

---

## 作者：wth2026 (赞：0)

# 题目大意
给定一个字符串 $S$。从这个字符串，Takahashi 将按如下方式创建一个新字符串 $T$。

- 首先，在 $S$ 中标记一个或多个字符。这里，任何两个标记字符都不应相邻。
- 接下来，删除所有未标记的字符。
- 最后，让 $T$ 成为剩余的字符串。这里，禁止更改字符的顺序。

有多少个字符串可以作为 $T$？求计数模数 $(10^9 + 7)$。
# 题目思路
~~非常高级，以至于场切失败……~~

一道非常好的动态规划题。

令 $n$ 为字符串的长度。

考虑状态：
- $f_{i,j}$ 表示当前是第 $i$ 位，字母是 $j$ 的方案数。
- $Sm_i$ 表示 $\sum_{i=0}^{25} f_{i, j}$。

考虑转移：
- 对于 $i = 1$，有 $f_{i,s_1}=1$，其余为 $0$。
- 对于每一个 $2 \leq i \leq n$，枚举每一个 $char(a) \leq j \leq char(z)$：
  - 如果 $s_i \neq j$，则 $f_{i, j}=f_{i - 1,j}$；
  - 否则，$f_{i, j} = Sm_{i-2}$。

考虑答案表示：
- 可以将答案表示为 $Sm_n$。
# [AC Code](https://atcoder.jp/contests/abc214/submissions/58265001)
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define mod 1000000007
#define lnf 0x3f3f3f3f3f3f3f3f

using namespace std;

const int N = 2e5 + 5;

int n;
string x;
int f[N][26 + 5], _Sm[N];

signed main () {
	cin >> x;
	n = x.size ();
	x = ' ' + x;
	f[1][x[1] - 97] = 1;
	_Sm[1] = 1;
	
	for (register int i = 2; i <= n; ++ i) {
		for (register int j = 0; j ^ 26; ++ j) {
			if (x[i] ^ (j + 97)) {
				f[i][j] = f[i - 1][j];
			} else {
				f[i][j] = (_Sm[i - 2] + 1) % mod;
			}
			
			_Sm[i] += f[i][j];
			_Sm[i] %= mod;
		}
	}
	
	cout << _Sm[n] << endl;
}
```

---

## 作者：ttq012 (赞：0)

设 $f_{i, j}$ 表示 当前考虑到了 $i$ 位，最后一个字符是 $j$ 的时候得到的方案数。

假设已经枚举好了 $i$ 和 $j$ 那么就需要分类讨论。

+ 如果 $s_i\neq j$ 那么 $f_{i,j}=f_{i-1,j}$。
+ 如果 $s_i = j$ 那么 $f_{i,j}=f_{i-2,k}+1$。

初始条件显然有 $f_{1,s_1}=1$。

由于 $k$ 只有 $26$ 个不同的取值，所以直接暴力转移即可。

时间复杂度为 $O(n\omega^2)$ 的。其中 $\omega$ 是字母的数量即 $26$。

---

## 作者：Purslane (赞：0)

# Solution

就这么一道简单题，怎么卡我这么久。

设 $dp_u$ 表示以 $u$ 结尾的没有相邻项的本质不同的子序列个数。

考虑每个字符串能不能被表示出来。我们每次在所有能选的相同字符中选最靠前的那一个，这样就可以避免重复。

考虑 $dp_u$ 可以从哪转移。设 $S_u$ 上一次出现的位置为 $lst_{S_u}$。那么从 $v<lst_{S_u}-1$ 的地方转移可以强制让他不合法，因为这样我们可以选 $lst_{S_u}$ 而不是 $u$，会产生重复。不过 $v=lst_{S_u}-1$ 除外，因为当时并不能选相邻的。

所以能转移的 $v$ 的区间为 $\{lst_{S_u}-1\} \cup[lst_{S_u},u-2]$。前缀和优化即可。

代码：[code](https://atcoder.jp/contests/abc214/submissions/43278779)

PS : 学习了一下官方题解，其实不需要前缀和优化，因为总的枚举数是 $O(26n)$ 这个量级的。

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
这题我们可以设 `dp[i]` 表示选前 $i$ 个字符并以 `str[i]` 结尾的个数，那么可以很快的写出来一个转移式 $dp_x=\sum_{i=1}^{x-2}dp_i$，然后最后把枚举过的删掉就可以了，但这样的复杂度是 $O(n^2)$。

考虑优化，如果枚举到的字符和要作为结尾的字符是一样的，那么对于之前字符的字符就可以直接把替换的字符换成遍历到的字符就可以把重复的解决了，然后就可以直接退出本次循环了，可以记录这个字符的位置为 $k$，那么就是 $dp_x=\sum_{i=k}^{x-2}dp_i$，最后特判一下边界就行了。

这样看上去还是 $O(n^2)$，但我们可以稍微分析一下每一个字符最多是枚举 $26$ 次，所以这个复杂度就从 $O(n^2)$ 变成了 $O(26 n)$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7,maxn=10000000;
int dp[maxn];
signed main(){
	string str;cin>>str;
	int n=str.size();
	str=' '+str;
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=0;j--){
			if(j==0)dp[i]=(dp[i]+1)%mod;
			else dp[i]=(dp[i]+dp[j-1])%mod;
			if(str[i]==str[j])break;
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++)ans=(ans+dp[i])%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：smydahaoren (赞：0)

### **思路分析：**
这道题典型的字符串 $\text{dp}$，虽然拿 $\text{map}$ 暴力也可以拿到一点分。 

列状态转移方程，定义 $dp_{i,j}$ 为到 $s_i$ 的子串以字母 $j$ 结尾的方案数。

当 $j$ 不等于 $s_i$ 时，让 $dp_{i,j}=dp_{i-1,j}$，因为此时不影响结果。

当 $j$ 等于 $s_i$ 时，因为要取不相邻的字符，所以取前两位的结果，然后加上这个方案的 $1$，最后取模。

综上：

$$ 	dp_{i,j} = \begin{cases}
   dp_{i-1,j} &\text{if } j\not =s_i \\
   dp_{i-2,j}+1 &\text{if } j=s_i
\end{cases}$$

### **AC 代码：**

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=20005,M=30,mod=1e9+7;
int dp[N][M],cnt[N];
string s;
int main(){
	cin>>s;
	int n=s.size();
	dp[1][s[0]-'a']=1; //初始化 
	cnt[1]=1;//cnt数组储存结果 
	for(int i=2;i<=n;i++)
		for(int j=0;j<25;j++){
			char c=j+'a';
			if(c==s[i]) dp[i][j]=(cnt[i-2]+1)%mod;	
			else dp[i][j]=dp[i-1][j];
			cnt[i]+=dp[i][j];
			cnt[i]%=mod;//取模 
		}
	cout<<cnt[n];
	return 0;
}

```

---

