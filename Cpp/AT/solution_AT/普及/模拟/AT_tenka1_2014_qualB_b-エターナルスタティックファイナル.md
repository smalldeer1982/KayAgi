# エターナルスタティックファイナル

## 题目描述

## 题意
小A通过组合他所学的短语来吟唱咒语。

同一个短语可以在诵读咒语的过程中使用多次。

例如，如果你记住了 $aaa$、$bbb$ 和 $ccc$ 三个短语，你就可以念出 $aaaccc$、$aaabbb$ 和 $cccaaaaaa$ 这样的咒语。

小A不确定他是否能够通过组合他所记住的短语来吟唱他所要学习的新咒语。

为小A创建一个程序，计算有多少种短语的排列组合可以构建他所要学习的新咒语。

变化的数量可能很大，所以输出对 $10^9+7$ 取模后的结果。

## 样例 #1

### 输入

```
3
eternalstaticfinal
eternal
static
final```

### 输出

```
1```

## 样例 #2

### 输入

```
5
eternalstaticfinal
eternal
static
final
fin
al```

### 输出

```
2```

## 样例 #3

### 输入

```
5
abcdef
abc
def
abcdef
d
ef```

### 输出

```
3```

## 样例 #4

### 输入

```
5
aaaa
a
aa
aaa
aaaa
b```

### 输出

```
8```

## 样例 #5

### 输入

```
10
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
a
aa
aaa
aaaa
aaaaa
aaaaaa
aaaaaaa
aaaaaaaa
aaaaaaaaa
aaaaaaaaaa```

### 输出

```
146491918```

# 题解

## 作者：Bpds1110 (赞：2)

很明显，一眼 DP。

考虑设计状态。我们令 $dp_i$ 表示原串 $S$ 拼接到第 $i$ 位时的方案总数，即目标状态为 $dp_{\left | S \right | }$。初始状态很明确，当长度为 $0$ 时，只有一种方案，故 $dp_0 = 1$。

接着开始状态转移。对于每个 $dp_i$，我们可以枚举每个 $T_j$，看成最后一个接上去的串。若当前 $S$ 串到第 $i$ 个位置的末尾为 $T_j$，才能转移。当前的末尾位置为 $i$，在没接上 $T_j$ 前，末尾的位置为 $i - {\left | T_j \right | }$，则得出 $dp_i$。 
$$
dp_i = \sum_{j = 1}^{n} dp_{i - \left | T_j \right | } (T_j = \left [ S_{i - \left | T_j \right | + 1}, S_i \right ] )
$$

最后别忘记取模。

---

## 作者：CheZiHe929 (赞：1)

## 简要题意

给定字符串 $s$ 和 $n(1\le n \le 100)$ 个字符串 $t$，求使用任意个字符串 $t$ 构成字符串 $s$ 的方案数。

## 简要思路

注意到求方案数，考虑动态规划。

设 $dp_i$ 表示拼接到 $s_i$ 时的方案总数，则最终答案为 $dp_{len_s}$，初始化为 $dp_0=1$。

对于转移，由于 $n$ 较小，所以可以每次遍历每个字符串 $t_j$，看是否与当前位置 $s$ 的后缀相同。若相同，则更新 $dp_i+=dp_{i-|t_j|}$。

对于 $s$ 后缀的截取，可以使用 `substr` 函数。

> `substr(pos, len)` 函数的参数返回从 `pos` 位置开始截取最多 `len` 个字符组成的字符串（如果从 `pos` 开始的后缀长度不足 `len` 则截取这个后缀）。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Time std::cout<<1.0*clock()/CLOCKS_PER_SEC<<'s'<<endl;
#define Memory std::cout<<abs(&mst - &men)/1024.0/1024<<"MB"<<endl;
#define eps 1e-5

#define YES puts("YES")
#define Yes puts("Yes")
#define yes puts("yes")
#define NO puts("NO")
#define No puts("No")
#define no puts("no")

const int p=1e9+7;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

inline void IOS(){std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0);}
inline void Freopen(){freopen("test.in","r",stdin);freopen("test.out","w",stdout);}

bool mst;
int n,m,dp[1005];
std::string t[1005],s;
bool men;

signed main(){

	n=read();
	std::cin>>s;
	m=s.size();
	for(int i=1;i<=n;i++)std::cin>>t[i];
	
	dp[0]=1;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(i>=t[j].size()&&t[j]==s.substr(i-t[j].size(),t[j].size())){
				dp[i]+=dp[i-t[j].size()];
				dp[i]%=p; 
			}
			
	println(dp[m]);

	return 0;
}
```

---

## 作者：lyh0217 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_tenka1_2014_qualB_b)

### 题意

给定 $n$ 个字符串 $t_i$ 和一个字符串 $s$，求有多少种不同的方法能在 $n$ 个 $t_i$ 中选取一些字符串按顺序拼出 $s$。

### 思路

考虑 dp，设 $dp_i$ 表示拼出来了 $s$ 的前 $i$ 位的方案数，则

$$dp_i=\sum\limits_{j=1}^{n}\sum\limits_{k=1}^{i}dp_{k-1}\left[str(k,i)=t_j\right]$$

其中 $str(l,r)$ 表示 $s$ 从 $l$ 到 $r$ 这个子串。

注意取模。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[1005];
string s[105];
int main()
{
	int n;
	cin>>n;
	string t;
	cin>>t;
	for(int i=1;i<=n;i++) cin>>s[i];
	dp[0]=1;
	for(int i=1;i<=t.size();i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(s[j].size()<=i)//先判长度够不够
			{
				string y="";
				for(int k=i-s[j].size();k<i;k++)
				{
					y+=t[k];
				}
				if(y==s[j]) //如果可以拼
				{
					dp[i]=(dp[i]+dp[i-s[j].size()])%1000000007;//注意取模！！！
				}
			}
		}
	}
	cout<<dp[t.size()]<<'\n';//行末要多输出一个换行
	return 0;
}
```
[评测记录](https://atcoder.jp/contests/tenka1-2014-qualb/submissions/61963584)

---

## 作者：Specthraimn (赞：0)

# エターナルスタティックファイナル 题解  

### 大致题意  

给定 $1$ 个字符串 $S$ 和 $n(1 \le n \le 10^2)$ 个短语字符串 $T_i$，求 $T$ 构成 $S$ 的方案数。  

### 解题思路  

看到求方案数，很明显的动态规划。可以参考类似走楼梯一类的题目（[P1255](https://www.luogu.com.cn/problem/P1255)）：枚举第 $i$ 位，如果当前的 $S$ 可以从不含后缀 $T$ 的状态 $S'$ 转移过来，那么，$S$方案数就加上 $S'$ 的方案数。每次记录前 $i$ 位由 $T$ 构成的方案数，累加取模即可。

例如，若 $S = final$，$T = \{final, fin, al\}$，则 $S$ 可以由空串加上 $final$ 直接转移过来，也可以由上一个状态 $fin$ 加上 $al$ 得到，而 $fin$ 又是从空串转移过来，所以总的方案数为 $2$。

状态设计：$dp[i]$ 表示前 $i$ 位的方案数，显然地，$dp[0] = 1$（空串的方案数为 $1$，只有一种）。  

状态转移：$dp[i] = \sum_{j = 1}^n dp[i - \vert T_j \vert]$。  

最后的答案即为 $dp[\vert S \vert]$。  

### AC 代码  

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e3 + 5;
const int mod = 1e9 + 7;
string b[N];
int dp[N];
void solve()
{
	string s;
	int n;
	cin >> n;
	cin >> s;
	for(int i = 1; i <= n; i++)
	{
		cin >> b[i];
	}
	dp[0] = 1;
	for(int i = 1; i <= s.size(); i++)
	{
		for(int j = 1; j <= n; j++)
		{

			if(i >= b[j].size())
			{
				if(b[j] == s.substr(i - b[j].size(), b[j].size()))
				{
					// s.substr(pos, len) 截取起点为 pos，长度为 len 的子串 
					dp[i] += dp[i - b[j].size()] % mod;
					dp[i] %= mod;
				}
			}
		}
	}
	cout << dp[s.size()] % mod << endl;
}
signed main()
{
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

```
**[AC 记录](https://www.luogu.com.cn/record/183062354)**  

**完结撒花✿✿ヽ(°▽°)ノ✿**

---

## 作者：HotWood (赞：0)

# 题意

把题目给定的字符串 $T_i$ 按一定顺序拼接起来，求有多少种拼接方案可以得到字符串 $S$。

# 思路

这道题和 [P4591](https://www.luogu.com.cn/problem/P4591) 很像，考虑动态规划。

用 $f_i$ 表示从 $S_1$ 到 $S_i$ 全部拼接完成的方案数，因为 $S_i$ 是在某个合法拼接得到的字符串 $S$ 的前缀（可能是空串）后拼接上某个字符串 $T_j$ 得到的，显然有 $f_i=\sum{f_{i-len_{T_j}}(T_j=S_{i-len_{T_j}+1,i})}$。

答案即为 $f_{len_s}$。

# 实现

本题数据范围较小，暴力比较可以通过，我现在介绍一种更加强大的方法 —— 字符串哈希。

我们把字符串当做一个 $base$ 进制的数，就可以把每个字符串转换成整数，但这个转换的结果很大，可以考虑对一个大质数取余。

用 $hash_i$ 表示字符串 $S$ 以第 $i$ 位为结尾的前缀的哈希值，那么这是字符串 $S$ 哈希的计算方式：$hash_i=hash_{i-1} \cdot base+S_i$。

容易发现：$hash_i=\sum_{j=1}^{i}(base^{i-j} \cdot S_j)$。

可得：$hash_{l,r}=hash_r-hash_{l-1}\cdot base^{r-l+1}$。

配合快速幂由此我们可以以 $O(\log_2len_T)$ 的复杂度比较字符串了，时间复杂度也由暴力的 $O({len_S}\cdot{len_T}\cdot n)$ 优化至 $O(len_S \cdot\log_2len_T\cdot n)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=1010,base=94367;
#define ULL unsigned long long
ULL n,f[N],k,sum[N],hx[N];//ULL自然溢出相当于模2^64
string a[N];
ULL pw(int n,int k){
	ULL ret=1,now=n;
	while(k){
		if(k&1)ret*=now;
		now*=now;
		k>>=1;
	}
	return ret;
}
ULL js(int l,int r){
	return sum[r]-sum[l-1]*pw(base,r-l+1);
}
int main(){
	ios::sync_with_stdio(0);
	string s,in;
	cin>>n;
	cin>>in;
	s+=" ";s+=in;//字符串从第一位开始输入，方便处理
	k=s.size()-1;
	for(int i=1;i<=k;i++){
		sum[i]=sum[i-1]*base+s[i];
	}
	for(int i=1;i<=n;i++){
		string inn;
		cin>>inn;a[i]+=" ";a[i]+=inn;
		for(int k=1;k<=a[i].size()-1;k++){
			hx[i]=hx[i]*base+a[i][k];
		}
	}		
	f[0]=1;
	for(int j=1;j<=k+1;j++){
		for(int i=1;i<=n;i++){
			if(j>=(int)a[i].size()-1){
				if(hx[i]==js(j-a[i].size()+2,j)){
					f[j]=(f[j]+f[j-a[i].size()+1])%mod;
				}
			}
		}
	}
	cout<<f[k]<<endl;
	return 0;
}
```

[AC](https://www.luogu.com.cn/record/172589268)

---

## 作者：__Creeper__ (赞：0)

## 思路

一道非常简单的线性 dp。

### 状态定义

- $dp_{i}$ 表示形成字符串 $\texttt {s}$ 的前缀直到索引 $\texttt {j}$（下标从 $0$ 开始）的方式数量。

### 初始化

- $dp_{0} = 1$，形成空串的方式只能不使用任何短语。

### 状态转移

- 遍历 $\texttt {s}$ 的每个位置 $i$ 对于每个位置，遍历每个短语 $t_{j}$。看当前 $\texttt {s}$ 的后缀是否与 $t_{j}$ 相同。如果相同，更新 $dp_{i}$。

- 即：$dp_{i} = dp_{i} + dp_{i - |t_{j}| }$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
string s, t[N];
const int mod = 1e9 + 7;
int dp[N];

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> s;
	m = s.size();
	for ( int i = 1; i <= n; i++ ) cin >> t[i];
	dp[0] = 1; 
	for ( int i = 1; i <= m; i++ )
	{
		for ( int j = 1; j <= n; j++ )
		{
			if ( i >= t[j].size() && s.substr ( i - t[j].size(), t[j].size() ) == t[j] )
			{
                dp[i] = ( dp[i] + dp[i - t[j].size()] ) % mod;
			}
		}
	}
	cout << dp[m] % mod << endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 思路

一道动态规划。

1. **状态定义**：
   - 定义 $dp_j$ 表示形成字符串 $S$ 的前缀直到索引 $j$ 的方式数量。
   - 初始化 $dp_0 = 1$，因为形成空前缀（不使用任何短语）的方式只有一种。

2. **DP 状态转移**：
   - 遍历 $S$ 的每个位置 $j$。
   - 对于每个位置，遍历每个短语 $T_i$。
   - 看当前 $S$ 的后缀是否与 $T_i$ 匹配。匹配的话，更新（使用 $T_i$ 形成 $S_{0\dots j}$ 的方式数量）。

## Code

```cpp
#include <iostream>
#include <string>
using namespace std;

const int mod = 1e9 + 7;

long long f[1005]; 
string str[105], S;

int main() 
{
    int n;
    cin >> n >> S;
    for (int i = 0; i < n; ++ i)  cin >> str[i];
    int m = S.size();
    f[0] = 1; 
    for (int j = 0; j < m; ++ j)
	{
        if (f[j] > 0) 
            for (int i = 0; i < n; ++ i) 
			{
                int lenth = str[i].size();
                if (j + lenth <= m && S.substr(j, lenth) == str[i])  f[j + lenth] = (f[j + lenth] + f[j]) % mod;
            }
    }
    cout << f[m] << endl;
    return 0;
}
```

---

## 作者：hubin1 (赞：0)

# エターナルスタティックファイナル

## 题意

给定 $1$ 个咒语和 $n$ 个短语，求这 $n$ 个短语构成这个咒语的方案数。答案对 $10^9+7$ 取模。

## 思路

1. 很明显，这道题是一个动态规划。
2. 状态：设 $dp_i$ 表示这个咒语从 $S_0$ 到 $S_i$ 的方案数。
3. 转移：如果有一个短语 $t_i$ 和 $S$ 中的某个区间 $[S_{i-\operatorname{len}(t_i)},S_{i-1}]$ 相等，那么 $dp_i=dp_i+dp_{i-\operatorname{len}(t_i)}$。在这里 $\operatorname{len}(t_i)$ 表示 $t_i$ 的长度。
4. 初始化：$dp_0$ 只有一种情况，因此 $dp_0=1$。

## Code

``` cpp
#include<bits/stdc++.h>
using namespace std;

// #define int long long
#define debug(x,i) cerr<<#x<<'='<<x<<" \n"[i]

const int MAX=1e5;
string s,t[MAX];
const int mod=1e9+7;
int dp[MAX];

string str(string st,int end)
{
	string temp;
	for(int i=end-st.size();i<=end-1;i++)
	{
		temp=temp+s[i];
	}
	return temp;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	int n;
	cin>>n;
	cin>>s;
	for(int i=1;i<=n;i++)
		cin>>t[i];
	dp[0]=1; 
	int len=s.size();
	for(int i=1;i<=len;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i>=t[j].size()&&str(t[j],i)==t[j])
                	dp[i]=(dp[i]+dp[i-t[j].size()])%mod;
		}
	}
	cout<<dp[len]%mod<<endl;
	return 0;
}
```





---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_tenka1_2014_qualB_b)
# 题目描述
存在 $n$ 个序列 $a_{1},a_{2},\dots,a_{n}$。问将这 $n$ 个序列排列组合有多少种排列方法能构成给定字符串 $s$。
# 题目分析
考虑 `dp`。但如果对于第 $i$ 个字符串 $a_{i}$ 来计算，显然推导方程就跟暴力一样。
### 设定
那就对于 $s$ 的每一位 `dp` 对于 $s$ 的前 $i$ 个字符，$dp_{i}$ 代表能够匹配的数量。
### 转移方程
方程：$dp_{i}=\sum\limits_{k=1}^{n}check(s,a_{k},i)\times dp_{i-size_{i}}$。

其中 $check(s,a_{k},i)$ 代表 $s$ 的前 $i$ 个字符是否与 $a_{i}$ 相同。

$size_{i}$ 代表 $a_{i}$ 的长度。
### 答案
答案为 $dp_{size_{s}}$。
# 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e2+5;
const int P=1e9+7;
int n;
string s;
string a[MAXN];
int dp[MAXN];
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
    cin>>n>>s;
    for(int i=1;i<=n;i++)
		cin>>a[i];
    dp[0]=1;
    int k=s.size();
    for(int i=1;i<=k;i++)
        for(int k=1;k<=n;k++)
            if(i>=a[k].size())
				if(s.compare(i-a[k].size(),a[k].size(),a[k])==0)
                	dp[i]=(dp[i]+dp[i-a[k].size()])%P;
    cout<<dp[k];
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [エターナルスタティックファイナル](https://www.luogu.com.cn/problem/AT_tenka1_2014_qualB_b)

## 题意
计算出用给定的短语，有多少种方法构成所要的单词。

## 思路分析
可以用 $\verb|dp|$ 来解决。

定义：$f_i$ 表示从拼写 $S$ 的开头到第 $i$个字符的子串的短语的排列组合的数量；$|S|$ 表示字符串 $S$ 的长度。

若 $i\ge|T_j|$ 且 $S$ 的第 $i-|T_j|$ 到第 $|T_j|$ 位所构成的字符串与 $|T_j|$ 相等，则 $f_i=f_i+{f_{i-|T_j|}}$。

那么，$f_{|S|}$ 就是最后的答案。

$PS$：

1.字符串是从第一位开始输入的（从 $0$ 开始就会错，[错误记录](https://www.luogu.com.cn/record/109793442)）。

2.字符串比较要用 $\verb|string|$ 库中的 $\verb|compare|$ 函数，不能用 $==$,否则会出错（如果不会，请点击[这里](https://blog.csdn.net/qq_40968179/article/details/104384232)）。

3.代码中的 $\verb|s.compare(i-t[j].size(),t[j].size(),t[j])|$ 表示字符串 $s$ 的第 $i-t_j$ 开始，连续 $|t_j|$ 位所组成的字符串是否等于 $t_j$。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=101,mod=1e9+7;
int n,dp[N];string s,t[N];
int main(){
    cin>>n>>s;
    for(int i=1; i<=n; ++i)cin>>t[i];
    dp[0]=1;
    for(int i=1; i<=s.size(); i++)
        for(int j=1; j<=n; j++)
            if(i>=t[j].size()&&!s.compare(i-t[j].size(),t[j].size(),t[j]))
                dp[i]=(dp[i]+dp[i-t[j].size()])%mod;
    cout<<dp[s.size()]<<'\n';
    return 0;
}
```

---

