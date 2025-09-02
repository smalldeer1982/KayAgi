# [ABC386F] Operate K

## 题目描述

给定字符串 $ S $，你需要判断是否有可能通过最多 $ K $ 次操作将其变为字符串 $ T $。

这里操作的定义如下：
1. 在 $ S $ 的任意位置（包括头尾）插入一个字符。
2. 从 $ S $ 删除一个字符。
3. 将 $ S $ 中的某个字符替换为另一个字符。

## 样例 #1

### 输入

```
3
abc
awtf```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2
abc
awtf```

### 输出

```
No```

## 样例 #3

### 输入

```
17
twothousandtwentyfour
happynewyear```

### 输出

```
Yes```

# 题解

## 作者：Inv_day_in_R (赞：8)

DP。看C题的时候就想到[编辑距离](https://www.luogu.com.cn/problem/P2758)这题，设计DP状态：$dp(i,j)$ 表示 $s$ 的前 $i$ 个字符与 $t$ 的前 $j$ 个字符之间最少操作次数。如果最后一次使用替换字符，那么从 $dp(i-1,j-1)+1$ 转移来，如果使用删除，那么从 $dp(i,j-1)+1$ 转移来，如果使用插入，那么从 $dp(i-1,j)+1$ 转移来，如果 $s_i=t_j$，还可以直接从 $dp(i-1,j-1)$ 转移来。$dp(i,j)=max\{dp(i-1,j-1)+[s_i\not=t_j],dp(i-1,j)+1,dp(i,j-1)+1\}$

但是有一些不同，如数据范围 $n\le5\times10^5$，看似得用更快的做法，实际上操作次数大于 $k$ 的，我们并不需要知道它们具体多少，压根不用算。观察到当 $|i-j|>k$ 时，操作次数显然大于 $k$，只需开一个 $f$ 数组，用 $f(i,i-j)$ 表示 $dp(i,j)$（由于 $i-j$ 可能是负数，真正实现时我额外加上了 $22$），$f$ 数组开到 $n\times45$ 就绝对够了。状态转移方程不变。

记得特判 $\lvert\lvert s\rvert-\lvert t\rvert\rvert>k$ 的情况。

代码：

```cpp
int k;
string s,t;
int f[500010][45];
int&dp(int i,int j){return f[i][i-j+22];}//通过传引用的方式实现dp与f的转化
void solve(){
	cin>>k>>s>>t;
	int n=s.size(),m=t.size();
	if(abs(n-m)>k){
		cout<<"No";
		return;
	}
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=k;i++){
		dp(0,i)=i;
		dp(i,0)=i;
	}
	for(int i=1;i<=n;i++)for(int j=max(1ll,i-k);j<=min(i+k,m);j++){
		dp(i,j)=min({dp(i-1,j)+1,dp(i,j-1)+1,dp(i-1,j-1)+(s[i-1]!=t[j-1])});
	}
	if(dp(n,m)<=k)cout<<"Yes";
	else cout<<"No";
}
```

---

## 作者：wang54321 (赞：7)

# abc386_f Operate K Solution

提供一种 $O(k^2\log n+n)$ 的做法。

一个朴素的求编辑距离的方法是暴力 $O(n^2)$，状态是当前匹配到哪一位，因为 $k$ 很小，考虑设 $dp_{i,j}$ 为第一个串匹配了 $i$ 个，第二个串匹配了 $i+j$ 个，显然 $j \in [-k,k]$。

转移比较简单，直接分讨这一位用哪种操作就好了。

考虑继续优化，我们注意到dp数组的值很小，但是 $i$ 却很大，考虑键值互换，因为如果状态 $dp_{i,j}$ 可以通过 $x$ 次操作以内得到，那么 $dp_{i-1,j-1}$ 也可以通过 $x$ 次操作以内得到，所以设 $dp_{i,j}$ 表示操作过 $i$ 次，两串匹配长度差 $j$ 的最远匹配距离。

转移的时候发现只有使用操作才转移，所以求 LCP 即可，根据求 LCP 的实现不同可以得到不同的复杂度，我这里使用二分哈希可以做到 $O(k^2\log n+n)$ ，用倍增 SA 加 ST 表可以做到 $O(k^2+n\log n)$ ，用 SA-IS 加四毛子之类的算法可以做到 $O(k^2+n)$。

---

## 作者：xyx404 (赞：4)

## 思路：

动态规划。

计算出最小编辑距离，并检查其是否小于等于 $K$。

### 二维动态规划：

现在先考虑二维 $dp$ 数组的情况。

二维 $dp$ 数组时，$dp_{i,j}$ 表示将 $S$ 的前 $i$ 个字符转换为 $T$ 的前 $j$ 个字符所需的最小操作数。

然后考虑转移。

在动态规划中，$dp_{i,j}$ 表示将字符串 $S$ 的前 $i$ 个字符转换为字符串 $T$ 的前 $j$ 个字符所需的最小操作数。为了计算 $dp_{i,j}$，我们需要考虑三种可能的操作：删除、插入和替换。

具体来说：

1. 删除：如果我们从 $S$ 中删除一个字符，那么 $dp_{i,j}$ 可以由 $dp_{i-1,j}$ 转移而来，因为删除一个字符后，$S$ 的前 $i-1$ 个字符需要转换为 $T$ 的前 $j$ 个字符，这一步对应的操作次数加 $1$。
2. 插入：如果我们向 $S$ 插入一个字符，使得它与 $T$ 的第 $j$ 个字符匹配，那么 $dp_{i,j}$ 可以由 $dp_{i,j-1}$ 转移而来，因为插入一个字符后，$S$ 的前 $i$ 个字符需要转换为 $T$ 的前 $j-1$ 个字符，这一步对应的操作次数加 $1$。
3. 替换：如果我们用 $T$ 的第 $j$ 个字符替换 $S$ 的第 $i$ 个字符，那么 $dp_{i,j}$ 可以由 $dp_{i-1,j-1}$ 转移而来，因为替换一个字符后，$S$ 的前 $i-1$ 个字符需要转换为 $T$ 的前 $j-1$ 个字符。如果 $S_{i-1}$ 已经等于 $T_{j-1}$，则不需要额外增加操作次数；否则，这一步对应的操作次数加 $1$。

因此，$dp_{i,j}$ 的值是上述三种情况中的最小值。

同时当两个字符串的长度差大于 $K$ 时，一定是不可能在 $K$ 步内让他们相同的。

现在写出的代码可以解决一些**数据小**的测试点了，但是数据大一点的话，二维 $dp$ 数组会炸内存，因此考虑优化内存。

### 优化为一维：

观察状态转移方程可以发现，计算 $dp_{i,j}$ 只需要用到 $dp_{i-1,j}$、$dp_{i,j-1}$ 和 $dp_{i-1,j-1}$ 这三个值。这意味着我们并不需要整个二维数组来存储所有的中间结果，只需要当前行和上一行的结果即可。

具体的：

定义两个一维数组 $dp$ 和 $dp2$，$dp2$ 是上一行的值，数组大小为 $m+1$。

优化成一维后转移方程也要发生改变。

只需要将使用了上一行数据的改为访问 $dp2$ 的就行了，举个例子，对于二维时的 $dp_{i-1,j}$ 现在应该访问 $dp2_{j}$。

对应没有访问上一行数据的直接访问 $dp$ 数组就行了，举个例子，对于二维时的 $dp_{i,j-1}$ 现在应该访问 $dp_{j-1}$。

为了防止转移错误，我们要保证 $m \le n$，如果当 $m > n$ 时，会导致初始化错误，注意这是在数组大小为 $m+1$ 的情况下。

现在代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
LL k;
string S,T;
//vector<vector<int> >dp(500050,vector<int>(500050));
int dp[500050];
void solve(string S,string T){
	int n=T.size(),m=S.size();
//	vector<vector<int> >dp(m+1,vector<int>(n+1));
	if(m>n){
		solve(T,S);
		return;
	}
	vector<int>dp(m+1);
	vector<int>dp2(m+1);
	for(int i=0;i<=m;i++)dp2[i]=i;
	for(int i=1;i<=n;i++){
		dp[0]=i;
		char ti=T[i-1];
		for(int j=1;j<=m;j++){
			char sj=S[j-1];
			int add=(ti==sj)?0:1;
			dp[j]=min({dp2[j]+1,dp[j-1]+1,dp2[j-1]+add});
		}
		swap(dp,dp2);
	}
	if(dp2[m]<=k){
		cout<<"Yes";
	}
	else cout<<"No";
}
int main(){
	cin>>k>>S>>T;
	solve(S,T);
	return 0;
}


```

现在发现不会超内存了，但是会超时，考虑优化动态规划的循环。

### 优化循环：
对于每一个字符的位置，我们只需要考虑在编辑距离范围内的子串部分，即 $\max(1,i-K)$ 到 $\min(m,i+K)$。

## AC 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
LL k;
string S,T;
//vector<vector<int> >dp(500050,vector<int>(500050));
int dp[500050];
void solve(string S,string T){
	LL n=T.size(),m=S.size();
	if(abs(n-m)>k){
		cout<<"No";return;
	}
//	vector<vector<int> >dp(m+1,vector<int>(n+1));
	if(m>n){
		solve(T,S);
		return;
	}
	vector<int>dp(m+1);
	vector<int>dp2(m+1);
	for(int i=0;i<=min(m,k);i++)dp2[i]=i;
	for(LL i=1;i<=n;i++){
		dp[0]=i;
		char ti=T[i-1];
		for(LL j=max(1ll,i-k);j<=min(m,i+k);j++){
			char sj=S[j-1];
			int add=(ti==sj)?0:1;
			dp[j]=min({dp2[j]+1,dp[j-1]+1,dp2[j-1]+add});
		}
		swap(dp,dp2);
	}
	if(dp2[m]<=k){
		cout<<"Yes";
	}
	else cout<<"No";
	return;
}
int main(){
	cin>>k>>S>>T;
	solve(S,T);
	return 0;
}


```
[AC 记录](https://atcoder.jp/contests/abc386/submissions/61254688)。

---

## 作者：Drifty (赞：2)

### Solution

赛时写炸了，忘记加一。

显然我们有 $\mathcal{O}(nm)$ 的编辑距离。

但是我们注意到实际上当前的修改只有可能从前面 $k$ 个字符或后面 $k$ 个字符操作而来，那么我们就取前面 $k$ 个和后面 $k$ 个状态转移就好。

实现的时候实际上记录的 $f_{i,k}$ 这个 $k$ 是相对 $i$ 的，因此当从 $i-1$ 转移过来的时候要注意下标的变化，实际上加了 $1$，赛时并没有注意到这一点，样例都没过。

[My Submission.](https://atcoder.jp/contests/abc386/submissions/61297255)

---

## 作者：dengchengyu (赞：2)

# abc386_f Operate K Solution

**题目大意**：给定串 $A,B$，可以做至多 $K(K\le 20)$ 次以下操作之一：

* 往 $A$ 中插入一个字符。
* 删除 $A$ 的一个字符。
* 替换 $A$ 的一个字符。

问最终能否将 $A$ 变成 $B$。

**解题思路**：首先暴力地想，设$f_{i,j}$ 表示 $A$ 的前 $i$ 个考虑完后，匹配到 $B$ 的第 $j$ 个字符最少做多少次操作。

注意到只有 $i-K\le j\le i+K$ 的 $j$ 是有用的，所以我们设新的 DP 状态 $f_{i,j}(-K\le j\le K)$ 表示 $A$ 的前 $i$ 个考虑完后，匹配到 $B$ 的第 $i+j$ 个字符最少做多少次操作。

 那么转移就是：

* 插入 $B$ 的下一个字符：$f_{i,j}+1\to f_{i,j+1}$。
* 删除 $A$ 的下一个字符：$f_{i,j}+1\to f_{i+1,j-1}$。
* 替换 $A$ 的下一个字符为 $B$ 的下一个字符：$f_{i,j}+1\to f_{i+1,j}$。
* 若 $A_{i+1}=B_{i+j+1}$ 则直接匹配：$f_{i,j}\to f_{i+1,j}$。

转移过程中要求操作数始终不大于 $K$ 即可。

时间复杂度 $O(nK)$，其中 $n$ 为字符串的长度。

AC 代码：

```cpp
int K;
const int N=5e5+5;
char a[N],b[N];
int n,m;
int f[N][45];
void get(int &x,int y){
	if(y<x)x=y;
}
signed main(){
	cin>>K;
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1),m=strlen(b+1);
	memset(f,0x3f,sizeof f);
	f[0][0+K]=0;
	fo(i,0,n){
		fo(j,-K,K){
			if(f[i][j+K]>K||i+j<0||i+j>m)continue;
			if(j+K-1>=0)get(f[i+1][j+K-1],f[i][j+K]+1);
			get(f[i][j+K+1],f[i][j+K]+1);
			get(f[i+1][j+K],f[i][j+K]+1);
			if(a[i+1]==b[i+j+1])get(f[i+1][j+K],f[i][j+K]);
		}
	}
	if(m-n<=K&&m-n>=-K&&f[n][m-n+K]<=K)cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```

---

## 作者：ANDER_ (赞：2)

#### 考察：DP、二进制。
## 题意
判断是否有可能在 $0$ 至 $K \le 20$ 次对字符串 $S$ 进行以下操作，使其与字符串 $T$ 相同。

- 对于每次操作，从以下三个子操作中选择一个并执行。
    - 在 $S$ 的任意位置插入一个字符（可能是开头或结尾）。
    - 从 $S$ 中删除一个字符。
    - 在 $S$ 中选择一个字符并替换为另一个字符。
## 数据限制
- $1\le|S|,|T|\le5 \times 10^5$，$K \le 20$。
- $S$ 和 $T$ 均由小写英文字符组成。
## 思路一
用 DP，设 $dp_{i,j}$ 表示将 $S_1...S_i$ 改成 $T_1...T_j$，最少需要几次操作。最后只需要判断 $dp_{N,M} \le K$ 即可。分操作进行转移：

- 删除一个字符，即 $dp_{i - 1,j} + 1$。
- 添加一个字符，即 $dp_{i,j - 1} + 1$。
- 修改一个字符，即 $dp_{i - 1,j - 1} + 1$。
- 不需要操作，满足 $S_i = T_j$，即 $dp_{i - 1, j - 1}$。

这要暴力的时间复杂度为 $\mathcal{O}(NM)$，起飞了。

注意到 $K \le 20$，且对于字符串 $S,T$ 的修改次数 $tim \ge |(|S|-|T|)|$。对于 DP，在 $dp_{i,j}$ 中，若 $|i - j| > K$，再去计算它毫无意义。只考虑 $|i - j| \le K$ 的 $dp_{i,j}$ 即可，时间复杂度降为 $\mathcal{O}(NK)$。

对于在 DP 过程中类似这样的优化，我们将此方法称为 **稀疏性优化（Sparsity）**，这本来是人工智能里的一个内容。抽象成一个坐标系 $xOy$ 的第一象限，可以这样 OI 的理解：

- 若 $dp_{i,j}$ 被计算有意义，在 $xOy$ 中记录一个点 $(i,j)$。若这些点分布在一条由点 $A = (0,k_1),B = (k_2, 0)$ 连成的线段 $AB$ 附近（其中 $k_1,k_2 \isin \R_+$）。那么只需要计算一部分的点，而不是计算所有满足 $i \isin (0,k_1],j\isin (0,k_2]$ 的点 $(i,j)$。

其本质上是来解一个线性方程组，其中 $x \isin \R^n,y \isin \R^m$，矩阵 $A \isin \R^{n\times m}$，且 $m \ll n$：

$$Ax = y$$

这里没必要继续深入，[代码](https://atcoder.jp/contests/abc386/submissions/61280677)并[不难写](https://atcoder.jp/contests/abc386/submissions?f.Task=&f.LanguageName=&f.Status=&f.User=ANDER_)，跑了 `147ms`。

## 思路二
我们发现 DP 数组中存储的值都不大，所以可以把数组的定义改一下：$dp_{i,r}$ 表示 $S_1...S_i$ 在经过 $r$ 次操作之后，能匹配到哪些 $T_1...T_j$。也就是说，每个 $dp_{i,r}$ 都是一个 `vector`。但是，如果暴力维护 `vector`，复杂度是 $\mathcal{O}(NK^2)$ 的，会超时。

注意到，$\forall x \isin dp_{i,r}(x \isin [i - r,i + r])$。这个值域大小不会超过 $2\times K + 1$，因此可以使用 `long long` 进行压位，转移时使用位运算即可。转移方程与思路一类似，无需赘述。

时间复杂度为 $\mathcal{O}(NK)$，但常数比较小，跑了 `93ms`。[代码](https://atcoder.jp/contests/abc386/submissions/61281367)。

---

## 作者：PUTONGDEYITIREN (赞：1)

# 思路
## 题面分析
这道题是第三题的加强版，$k$ 的数据范围变大了。但还是很小，有一个重要的概念，知道了它，对了这道题轻轻松松。
## 关键
两个字符串，如果他们的长度相差超过了 $k$，那么，他们修改的次数一定大于 $k$。
## 实现
相信大家看到这里也懂了，我们只用在编辑距离的基础上把第二维变成两个字符串相差的长度就行了，这里展示记忆化搜索的代码。
# code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,dp[500005][45],sn,tn;
string s,t;
long long dfs(long long n,long long m){
	if(abs(n-m)>k) return k+1;
	if(n==0||m==0) return n+m;
	if(~dp[m][m-n+20]) return dp[m][m-n+20];
	return dp[m][m-n+20]=min(dfs(n-1,m-1)+(s[n]!=t[m]),min(dfs(n-1,m),dfs(n,m-1))+1);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	cin>>k>>s>>t;
	sn=s.size(),tn=t.size();
	s=' '+s,t=' '+t;
	memset(dp,-1,sizeof(dp));
	if(dfs(sn,tn)>k) cout<<"No"<<endl;
	else cout<<"Yes"<<endl;
	return 0;
}

```

---

## 作者：wflhx2011 (赞：1)

比较简单。

这题先考虑暴力做法，和[编辑距离](https://www.luogu.com.cn/problem/P2758)这道题类似。

设 $f_{i,j}$ 表示让 $s$ 的前 $i$ 个字符和 $t$ 的前 $j$ 个字符相同的最小操作次数，同时 $s$ 的长度为 $n$，$t$ 的长度为 $m$。

- 删除操作是 $f_{i-1,j}+1$。

- 插入操作是 $f_{i,j-1}+1$。

- 改变操作，若 $s_i=t_j$ 是 $f_{i-1,j-1}$，否则是 $f_{i-1,j-1}+1$。

手推一下应该比较容易，不再赘述原因。

时间复杂度是 $O(nm)$ 的，这个题中会超时。

注意到 $k \le20$，不难想到如果 $\mid i-j \mid >k$ 一定不行，因为把它们变成长度一样的字符串都需要比 $k$ 次操作更多。

所以我们可以改变状态，设 $f_{i,j}$ 表示 $s$ 的前 $i$ 个字符 和 $t$ 的前 $i+j$ 个字符相等的最小操作次数。

然后转移方程是这个：


```cpp
f[i][j]=min({f[i][j],f[i-1][j+1]+1,f[i][j-1]+1,f[i-1][j]+(s[i]!=t[r])});

```
分别代表删除，插入，改变，$t_r$ 代表 $t$ 的第 $r$ 个字符。手推一下，结合上面的暴力，也容易得到。

通过映射的思想，可以把 $j$ 的取值范围从 $-20 \le j \le 20$ 变成 $0 \le j \le 40$，当然，保险一些可以开的更大。

注意边界和一些特殊情况，代码也就没什么难的。

最后如果 $f_{n,m-n+p} \le k$，其中 $p$ 为映射时加的值，那么就有解，否则无解。

时间复杂度 $O(nk)$。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int k,n,m;
string s,t;
int f[500005][50];
bool fl;
int main()
{
	cin>>k>>s>>t;
	n=s.size(),m=t.size(); 
	s=' '+s,t=' '+t;
	if(abs(n-m)>k)
	{
	    cout<<"No";
	    return 0;
    }
	memset(f,0x3f,sizeof(f));
	for(int i=25;i<=49;i++) 
		f[0][i]=i-25;
	for(int i=1;i<=n;i++)
	{
	    for(int j=1;j<=49;j++)
	    {
	        int r=i-25+j;
	        if(r<0||r>m) 	
				continue;
	        if(r==0) 
				f[i][j]=i;
	        else 
				f[i][j]=min({f[i][j],f[i-1][j+1]+1,f[i][j-1]+1,f[i-1][j]+(s[i]!=t[r])});
        }
    }
    if(f[n][25+m-n]<=k) 
		cout<<"Yes";
    else 
		cout<<"No";
    return 0;
}
```

---

## 作者：small_lemon_qwq (赞：0)

这题和 [P2758](https://www.luogu.com.cn/problem/P2758) 很像，但是会 T。

由于只需判断答案是否小于等于 $k$，所以计算过程中大于 $k$ 的可以视作无穷大。

显然长度相差超过 $k$ 的最少操作次数一定大于 $k$，所以只需计算长度相差不超过 $k$ 的。

```
#include<bits/stdc++.h>
using namespace std;
int k;
unordered_map<int,int>f[500005];
string s,t;
int get(int x,int y){
	if(x==0){
		return y+1;
	}
	if(y==-1){
		return x;
	}
	if(x>0&&y>=0&&abs(x-1-y)<=k){
		return f[x][y];
	}
	return 0x3f3f3f3f;
}
int Min(int x,int y){
	if(x>y){
		return y;
	}
	return x;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>k>>s>>t;
	int len=s.size(),len2=t.size();
	if(abs((int)s.size()-(int)t.size())>k){
		cout<<"No";
		return 0;
	}
	f[0][-1]=0;
	for(int i=0;i<len;i++){
		for(int j=max(0,i-k);j<=Min(i+k,len2-1);j++){
			f[i+1][j]=Min(Min(get(i,j),get(i+1,j-1)),get(i,j-1))+1;
			if(s[i]==t[j]){
				f[i+1][j]=Min(f[i+1][j],get(i,j-1));
			}
		}
	}
	if(f[len][len2-1]<=k){
		cout<<"Yes";
	}else{
		cout<<"No";
	}
	return 0;
}
```

---

