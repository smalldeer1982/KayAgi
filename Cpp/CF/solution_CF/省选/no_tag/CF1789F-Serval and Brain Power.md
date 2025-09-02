# Serval and Brain Power

## 题目描述

定义一个字符串 $T$ 是好的，当且仅当存在字符串 $T'$ 和整数 $k(k\geq2)$，使得 $T$ 可以由 $k$ 个 $T'$ 首尾相接得到。  
例如，字符串 $\texttt{gogogo}$ 就是好的，因为它可以由 $3$ 个字符串 $\texttt{go}$ 首尾相接得到；而 $\texttt{power}$ 就不是好的。  
给定仅包含小写英文字母的字符串 $S$。  
你需要求出 $S$ 最长的好的子序列（不一定连续）的长度，特别的如果 $S$ 没有好的子序列，答案为 $0$。

## 样例 #1

### 输入

```
buaa```

### 输出

```
2```

## 样例 #2

### 输入

```
codeforcesround```

### 输出

```
6```

## 样例 #3

### 输入

```
oooooooooooaaaaeaaiaujooooooooooooo```

### 输出

```
24```

## 样例 #4

### 输入

```
zero```

### 输出

```
0```

# 题解

## 作者：Iam1789 (赞：24)

哼哼哼，啊啊啊啊啊。（记得加句号。）

捏麻麻，被这题狠狠地创死了。

## 正文

考虑最朴素的暴力，枚举 $T'$ 出现了 $k$ 次，暴力枚举 $k-1$ 个分割点跑 LCS，时间复杂度 $\Theta(n^{2k-1})$，只能跑过 $k\leq 3$。

考虑另一个暴力。将 $S$ 划分为长度为 $\frac{n}{k}$ 的段，则 $T'$ 一定为至少一个段的子序列，对于每一段，枚举 $T'$ 后贪心匹配，时间复杂度为 $\Theta(2^{\frac{n}{k}}kn)$，可以跑过 $k \geq 5$。

$k$ 等于 $4$ 怎么办呢？我们发现，对于任何 $k=4$ 的串 $S$，一定可以在 $k=2$ 的时候找到 $S=2T'_2=2(T'_4+T'_4)$ 从而被统计入答案，因此无需单独考虑。题就做完了。

## 后记
![](https://cdn.luogu.com.cn/upload/image_hosting/etux2wl0.png)

---

## 作者：Miraik (赞：10)

数据范围很小，不妨考虑对于 $k$ 值不同的情况设计不同的方案。

对于 $k \le 3$ 的情况，我们有一个暴力的想法：枚举 $k-1$ 个终点，如 $k=3$ 时枚举 $x,y$，然后计算 $s[1,x]$，$s[x+1,y]$，$s[y+1,n]$ 的最长公共子序列。

这部分复杂度似乎是 $O(n^5)$ 的，但是实际上它远远跑不满，因为你枚举 $x$ 和 $y$ 有 $\frac{1}{2}$ 的常数，把序列划出的三部分平方起来至少有 $\frac{1}{27}$ 的常数，所以它至少有一个 $\frac{1}{54}$ 的常数，并不会超时。

你再考虑对于 $k \ge 4$ 的情况设计方案。首先你会发现 $k=2$ 严格包含 $k=4$，所以我们只需要考虑 $k \ge 5$ 的情况。

在 $n\le 80$，$k \ge 5$ 时，我们需要注意到：对于任意 $T$ ，必然存在某个 $i$ 满足 $T'$ 为 $s[i,i+15]$ 的子序列。因为如果不满足，那么每个子序列的跨度超过 $16$，其需要的总长度就会超过 $16 \times 5=80$，显然不合法。

于是枚举 $i$，状压后 $16$ 位的状态，再到原序列检查一遍即可。这部分的复杂度为 $O(n^2 \times 2^{16})$。可以做到更优复杂度，但是这个已经足以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[85][85],g[85][85][85],ans; char s[85],t[85];
inline int lcs2(int l1,int r1,int l2,int r2){
	for(int i=l1-1;i<=r1+1;i++)
		for(int j=l2-1;j<=r2+1;j++)
			f[i][j]=0;
	for(int i=l1;i<=r1;i++)
		for(int j=l2;j<=r2;j++)
			f[i][j]=max(max(f[i][j-1],f[i-1][j]),f[i-1][j-1]+(s[i]==s[j]));
	return f[r1][r2];
}
inline int lcs3(int l1,int r1,int l2,int r2,int l3,int r3){
	for(int i=l1-1;i<=r1+1;i++)
		for(int j=l2-1;j<=r2+1;j++)
			for(int k=l3-1;k<=r3+1;k++)
				g[i][j][k]=0;
	for(int i=l1;i<=r1;i++)
		for(int j=l2;j<=r2;j++)
			for(int k=l3;k<=r3;k++)
				g[i][j][k]=max(max(g[i][j][k-1],max(g[i][j-1][k],g[i-1][j][k])),g[i-1][j-1][k-1]+(s[i]==s[j]&&s[i]==s[k]));
	return g[r1][r2][r3];
}
inline int check(){
	int ans=0;
	for(int i=1,j=1;i<=n;i++)
		if(s[i]==t[j]){
			j++;
			if(j==m+1) j=1,ans++;
		}
	return ans>1?ans*m:0;
}
int main(){
	scanf("%s",s+1); n=strlen(s+1);
	for(int i=1;i<n;i++) ans=max(ans,2*lcs2(1,i,i+1,n));
	for(int i=1;i<n;i++)
		for(int j=i+1;j<n;j++)
			ans=max(ans,3*lcs3(1,i,i+1,j,j+1,n));
	for(int i=1;i<=n;i++){
		for(int sta=1;sta<(1<<16);sta+=2){
			m=0;
			for(int j=0;j<16&&i+j<=n;j++)
				if(sta&(1<<j)) t[++m]=s[i+j];
			ans=max(ans,check());
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Fan_sheng (赞：4)

人类智慧题，初见直呼不可做，其实思路很简单，颇受启发。

容易想到的做法是枚举 $k-1$ 个断点，把 $S$ 划分成 $k$ 个部分，对这 $k$ 部分求最长公共子序列。时间复杂度 $\mathbb O(n^{2k-1})$，由于枚举自带小常数，可以跑 $k\le3$。

$k$ 较大的时候，怎么枚举都不好做，必须想办法知道 $T^{\prime}$ 的形态才行。

**关键性质：一定存在一段 $T^{\prime}$，其开头位置和结尾位置距离不超过 $\lfloor\frac{n}{k}\rfloor-1$**。容易证明。

那么直接枚举这个开头 $i$，以及对于 $j\in [i,\min(n,i+\lfloor\frac{n}{k}\rfloor-1)]$，$s_j$ 是否被选。这样就知道了 $T^{\prime}$，暴力扫一遍 $S$ 来匹配。复杂度 $\mathbb O(n^22^{\lfloor\frac{n}{k}\rfloor})$，可以跑 $k\ge5$。

对于 $k=4$ 的情况，一定在 $k=2$ 就统计过了。

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
char s[83];
namespace task1{
	int dp[83][83];
	inline void solve(){
		for(int mid=1;mid<n;mid++){
			for(int i=1;i<=mid;i++)
			for(int j=1;j+mid<=n;j++){
				dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
				if(s[i]==s[j+mid])dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
			}ans=max(ans,dp[mid][n-mid]<<1);
		}
	}
}
namespace task2{
	int dp[83][83][83];
	inline void solve(){
		for(int l=1;l<n;l++)
		for(int r=l+1;r<n;r++){
			for(int i=1;i<=l;i++)
			for(int j=1;j+l<=r;j++)
			for(int k=1;k+r<=n;k++){
				dp[i][j][k]=max({dp[i][j][k-1],dp[i][j-1][k],dp[i-1][j][k]});
				if(s[i]==s[j+l]&&s[i]==s[k+r])
				dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-1][k-1]+1);
			}ans=max(ans,dp[l][r-l][n-r]*3);
		}
	}
}
namespace task3{
	char t[83];
	void dfs(int id,int F,int m){
		if(id>F){
			int res=0,now=1;
			for(int i=1;i<=n;i++){
				if(s[i]==t[now])now++;
				if(now>m)res++,now=1;
			}
			if(now==1&&res>1)ans=max(ans,res*m);
			return;
		}
		dfs(id+1,F,m),t[m+1]=s[id],dfs(id+1,F,m+1);
	}
	inline void solve(){
		for(int i=1;i<=n;i++)dfs(i,min(i+15,n),0);
	}
}
int main(){
	scanf("%s",s+1),n=strlen(s+1);
	task1::solve(),task2::solve(),task3::solve();
	printf("%d",ans);return 0;
}
```


---

## 作者：cmk666 (赞：2)

[题目传送门](/problem/CF1789F)

简单分讨一下。

当 $k=2$ 时，我们枚举分点，把 $S$ 分成 $S_1+S_2$，并钦定 $T'$ 在 $S_1,S_2$ 中出现各一次。这样就转变为 $S_1,S_2$ 的 LCS，总时间复杂度小常数 $O(|S|^3)$。

当 $k=3$ 时类似，只不过分成三段，时间复杂度 $O(|S|^5)$。理论上 $|S|=80$ 时会 TLE，但这部分带一个 $\dfrac1{120}$ 的常数，可参见乌姆尼克的[这条评论](//codeforces.com/blog/entry/113246?#comment-1007671)，所以能跑过去。

当 $k=4$ 时，不需要计算，因为 $T'+T'+T'+T'=(T'+T')+(T'+T')$，可以转化为 $k=2$ 的情况。

当 $k>4$ 时，把 $S$ 分成 $5$ 部分，则 $T'$ 必然是其中某一部分的子串，证明不难。直接枚举所有的子串贪心匹配即可。时间复杂度 $O(|S|2^{|S|\div5})$。

综上，我们在可以接受的时间内做完了此题。核心代码如下：
```cpp
string s, nw; unordered_set < string > st; int n, ans, p, q, cnt;
inline int lcs(const string &x, const string &y)
{
	vector < vector < int > > dp((int)x.size() + 9);
	for ( auto &i : dp ) i.resize((int)y.size() + 9);
	For(i, 1, (int)x.size()) For(j, 1, (int)y.size())
	{
		dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		if ( x[i - 1] == y[j - 1] ) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
	}
	return dp[(int)x.size()][(int)y.size()];
}
inline int lcs(const string &x, const string &y, const string &z)
{
	vector < vector < vector < int > > > dp((int)x.size() + 9);
	for ( auto &i : dp ) i.resize((int)y.size() + 9);
	for ( auto &i : dp ) for ( auto &j : i ) j.resize((int)z.size() + 9);
	For(i, 1, (int)x.size()) For(j, 1, (int)y.size()) For(k, 1, (int)z.size())
	{
		dp[i][j][k] = max({ dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1] });
		if ( x[i - 1] == y[j - 1] && x[i - 1] == z[k - 1] )
			dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k - 1] + 1);
	}
	return dp[(int)x.size()][(int)y.size()][(int)z.size()];
}
inline void dfs(int u, int v)
{
	if ( u == v ) { st.emplace(nw); return; }
	dfs(u + 1, v), nw.push_back(s[u]), dfs(u + 1, v), nw.pop_back();
}
int main()
{
	read(s), n = s.size();
	For(i, 1, n - 1) ans = max(ans, lcs(s.substr(0, i), s.substr(i)) << 1);
	For(i, 1, n - 1) For(j, i + 1, n - 1)
		ans = max(ans, lcs(s.substr(0, i), s.substr(i, j - i), s.substr(j)) * 3);
	For(i, 0, 4) dfs(n / 5 * i, i == 4 ? n : n / 5 * ( i + 1 ));
	for ( const auto &i : st ) if ( i.size() )
	{
		for ( p = q = cnt = 0 ; ; )
		{
			while ( q < n && s[q] != i[p] ) q++;
			if ( q >= n ) break;
			p++, q++;
			if ( p == (int)i.size() ) p = 0, cnt++;
		}
		if ( cnt > 1 ) ans = max(ans, (int)i.size() * cnt);
	}
	return println(ans), 0;
}
```

---

## 作者：bluewindde (赞：1)

1999ms 惊险卡过。

设 $n = |S|, m = |T'|$。

考虑暴力，枚举每一个子序列并统计其在原串中的出现次数，时间复杂度 $O(n 2^m)$。

显然过不了，但发现 $m$ 受 $k$ 的大小限制，必定有 $m \leqslant \dfrac n k$。

这个约束随着 $k$ 的增加而收紧，在 $k = 5$ 时 $(2^m)_{\max} = 2^{16}$ 达到可接受程度。

所以考虑用其他方法解决 $k = 2, 3, 4$ 的情况。发现 $k = 4$ 被 $k = 2$ 完全包含，所以只需考虑 $k = 2, 3$ 的情况。

$k = 2$ 时，枚举每一种字符串 $S$ 的分割方式 $S = S_1 + S_2$。钦定 $T'$ 在 $S_1, S_2$ 中各出现一次，使用 LCS 可以求出 $T'$，时间复杂度 $O(n^3)$。

$k = 3$ 时，同理，枚举每一种字符串 $S$ 的分割方式 $S = S_1 + S_2 + S_3$。钦定 $T'$ 在 $S_1, S_2, S_3$ 中各出现一次，使用 LCS 可以求出 $T'$。写个程序算一下，可以得到大约需要操作 $377447148$ 次，勉强可以冲一冲。

所以得到了一个时间复杂度大大优于 $O(n^5 +  2^{16}n)$ 的优秀算法。只要稍微卡一点常数就过了。

---

## 作者：Leasier (赞：1)

首先有一个暴力：枚举 $k - 1$ 个断点跑 LCS。时间复杂度为 $O(|S|^{2k - 1})$，只能跑 $k \leq 3$。

但是还有一个暴力：注意到这 $k$ 个子序列中一定**存在**一个使得其结尾减开头 $\leq \lfloor \frac{n}{k} \rfloor$，于是我们枚举一个开头以及其后面 $\lfloor \frac{n}{k} \rfloor$ 个数是否被选即可。时间复杂度为 $O(|S| 2^{\frac{|S|}{k}})$，只能跑 $k \geq 4$。

于是我们把两个暴力拼起来即可。注意 $k = 4$ 的情况已经包含在 $k = 2$ 中了，于是不需要再算一遍。

代码：
```cpp
#include <stdio.h>
#include <string.h>

int dp1[87][87], dp2[87][87][87];
char s[87], s_[87];

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int n, ans = 0;
	scanf("%s", &s[1]);
	n = strlen(&s[1]);
	for (int i = 1; i < n; i++){
		for (int j = 1; j <= n; j++){
			for (int k = 1; k <= n; k++){
				dp1[j][k] = 0;
			}
		}
		for (int j = 1; j <= i; j++){
			for (int k = i + 1; k <= n; k++){
				dp1[j][k] = max(dp1[j][k - 1], dp1[j - 1][k]);
				if (s[j] == s[k]) dp1[j][k] = max(dp1[j][k], dp1[j - 1][k - 1] + 1);
			}
		}
		ans = max(ans, dp1[i][n] * 2);
	}
	for (int i = 1; i <= n - 2; i++){
		for (int j = i + 1; j < n; j++){
			for (int k = 1; k <= n; k++){
				for (int l = 1; l <= n; l++){
					for (int x = 1; x <= n; x++){
						dp2[k][l][x] = 0;
					}
				}
			}
			for (int k = 1; k <= i; k++){
				for (int l = i + 1; l <= j; l++){
					for (int x = j + 1; x <= n; x++){
						dp2[k][l][x] = max(dp2[k][l][x - 1], max(dp2[k][l - 1][x], dp2[k - 1][l][x]));
						if (s[k] == s[l] && s[l] == s[x]) dp2[k][l][x] = max(dp2[k][l][x], dp2[k - 1][l - 1][x - 1] + 1);
					}
				}
			}
			ans = max(ans, dp2[i][j][n] * 3);
		}
	}
	for (int i = 5; i <= n; i += 2){
		int max_diff = n / i, full = (1 << max_diff) - 1;
		for (int j = 1; j <= full; j++){
			bool flag = false;
			for (int k = 1; k + i - 1 <= n; k++){
				int len = 0, pos = 1;
				bool flag2 = true;
				for (int l = 1; l <= max_diff; l++){
					if (j >> (l - 1) & 1) s_[++len] = s[k + l - 1];
				}
				for (int l = 1; l <= i; l++){
					for (int x = 1; x <= len; x++){
						while (pos <= n && s[pos] != s_[x]) pos++;
						if (pos > n){
							flag2 = false;
							break;
						}
						pos++;
					}
					if (!flag2) break;
				}
				if (flag2){
					flag = true;
					break;
				}
			}
			if (flag) ans = max(ans, i * __builtin_popcount(j));
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：寄风 (赞：1)

## 解法
你发现 $|S|\leq 80$，范围也很有限，考虑分类讨论 $k$。

1. $k\leq3$ 

枚举断点，直接求构成的字符串的 $\operatorname{LCS}$ 就可以了。

等下，时间复杂度最坏好像是 $O(n^5)$ 的？为啥能过。

上述时间复杂度的计算忽略了常数因子的影响，实际上有一个极小的常数，再加上神机子，实际上跑到飞起。

但是实现的时候注意，不要用 `substr` 和 `vector`。不要用 `substr` 和 `vector`。不要用 `substr` 和 `vector`。不要用 `substr` 和 `vector`。我这么写 T 的好惨。

2. $k=4$

这个时候 $T=T'+T'+T'+T'$，也就是 $T=(T'+T')+(T'+T')$，定义 $T''=T'+T'$，则 $T=T''+T''$，转化到 $k=2$ 的情况，不用重新计算。

3. $k\geq 5$

这个时候前面的暴力过不去了。

考虑另一个暴力。

发现当 $k\geq 5$ 的时候，$T'$ 的长度一定 $\leq 16$，不然 $T$ 的长度就会比 $80$ 大。

又发现我们让 $T'$ 的总长度尽量小是一定不劣的，所以 $T'$ 的总跨度（就是 $T'$ 里的元素在 $S$ 中出现的下标的极差，下同）$sz$ 一定也 $\leq 16$，不然 $T$ 的总跨度就超过了 $k\times sz \geq 80$，不合法。

所以我们可以枚举每一个长度为 $16$ 的连续区间，再枚举子序列，再判断让这个子序列作为 $T'$ 是否可行，最后如果可行就更新答案。

注意特判 $|S|\leq 15$ 的情况。
## 代码
因为不想写状压枚举子序列所以写了十六重循环，导致代码很臭，将就着看。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define PII pair <int , int>
//省略读写模板
inline void chkmax(int &a,int b){
    (a<b)&&(a=b);
}
inline void yes(){
    putchar('Y');
    putchar('e');
    putchar('s');
    putchar('\n');
}
inline void no(){putchar('N');putchar('o');putchar('\n');}
string s;
int dp1[85][85];
inline int lcs(int l1,int r1 , int l2,int r2){
    int s1=r1-l1+1,s2=r2-l2+1,u=max(s1,s2);
    for(int i=0;i<=u;i++)dp1[i][0]=dp1[0][i]=0;
    for(int i=1;i<=s1;i++){
        for(int j=1;j<=s2;j++){
            dp1[i][j]=max(dp1[i-1][j],dp1[i][j-1]);
            if(s[l1+i-1]==s[l2+j-1])chkmax(dp1[i][j],dp1[i-1][j-1]+1);
        }
    }
    return dp1[s1][s2];
}
int dp2[85][85][85];
inline int lcs(int l1,int r1,int l2,int r2,int l3,int r3){
    int s1=r1-l1+1,s2=r2-l2+1,s3=r3-l3+1;
    int u=max(s1,max(s2,s3));
    for(int i=0;i<=u;i++){
        dp2[i][0][0]=dp2[0][i][0]=dp2[0][0][i]=0;
    }
    for(int i=1;i<=s1;i++){
        for(int j=1;j<=s2;j++){
            for(int k=1;k<=s3;k++){
                dp2[i][j][k]=max(dp2[i-1][j][k],max(dp2[i][j-1][k],dp2[i][j][k-1]));
                if(s[l1+i-1]==s[l2+j-1]&&s[l2+j-1]==s[l3+k-1])
                chkmax(dp2[i][j][k],dp2[i-1][j-1][k-1]+1);
            }
        }
    }
    return dp2[s1][s2][s3];
}
inline vector <int> getnxt(string ss){
    vector <int> nxt(ss.size());
    if(ss.empty()) return nxt;
    nxt[0] = 0;
    int i = 1 , j = 0;
    while(i < ss.size()){
        j = nxt[i - 1];
        while(j > 0 && ss[i] != ss[j]) j = nxt[j - 1];
        nxt[i] = j + (ss[i] == ss[j]);
        i++;
    }
    return nxt;
}
inline int calc(string now){
    int anss=0;
    int p=0;
    for(int k=0;k<s.size();k++){
        if(s[k]==now[p]){
            p++;
            if(p==now.size())anss++,p=0;
        }
    }
    if(anss>1)return anss*(int)now.size();
    return 0;
}
inline void solve(){
    char c=getchar();
    while(c>='a'&&c<='z')s+=c,c=getchar();
    int ans = 0;
    for(int i=0;i<s.size()-1;i++){//k=2
        chkmax(ans,lcs(0,i,i+1,s.size()-1)*2);
    }
    for(int i=0;i<s.size()-1;i++){//k=3
        for(int j=i+1;j<s.size()-1;j++){
            chkmax(ans,lcs(0,i,i+1,j,j+1,s.size()-1)*3);
        }
    }
    //k=4->k=2
    int len=s.size();
    for(int i=0;i<len;i++){
        string now="";
for(int a1=0;a1<=1;a1++){if(a1)now+=s[i];if(i+1>=len){chkmax(ans,calc(now));break;}
for(int a2=0;a2<=1;a2++){if(a2)now+=s[i+1];if(i+2>=len){chkmax(ans,calc(now));break;}
for(int a3=0;a3<=1;a3++){if(a3)now+=s[i+2];if(i+3>=len){chkmax(ans,calc(now));break;}
for(int a4=0;a4<=1;a4++){if(a4)now+=s[i+3];if(i+4>=len){chkmax(ans,calc(now));break;}
for(int a5=0;a5<=1;a5++){if(a5)now+=s[i+4];if(i+5>=len){chkmax(ans,calc(now));break;}
for(int a6=0;a6<=1;a6++){if(a6)now+=s[i+5];if(i+6>=len){chkmax(ans,calc(now));break;}
for(int a7=0;a7<=1;a7++){if(a7)now+=s[i+6];if(i+7>=len){chkmax(ans,calc(now));break;}
for(int a8=0;a8<=1;a8++){if(a8)now+=s[i+7];if(i+8>=len){chkmax(ans,calc(now));break;}
for(int a9=0;a9<=1;a9++){if(a9)now+=s[i+8];if(i+9>=len){chkmax(ans,calc(now));break;}
for(int a10=0;a10<=1;a10++){if(a10)now+=s[i+9];if(i+10>=len){chkmax(ans,calc(now));break;}
for(int a11=0;a11<=1;a11++){if(a11)now+=s[i+10];if(i+11>=len){chkmax(ans,calc(now));break;}
for(int a12=0;a12<=1;a12++){if(a12)now+=s[i+11];if(i+12>=len){chkmax(ans,calc(now));break;}
for(int a13=0;a13<=1;a13++){if(a13)now+=s[i+12];if(i+13>=len){chkmax(ans,calc(now));break;}
for(int a14=0;a14<=1;a14++){if(a14)now+=s[i+13];if(i+14>=len){chkmax(ans,calc(now));break;}
for(int a15=0;a15<=1;a15++){if(a15)now+=s[i+14];if(i+15>=len){chkmax(ans,calc(now));break;}
for(int a16=0;a16<=1;a16++){if(a16)now+=s[i+15];
chkmax(ans,calc(now));
if(a16)now.pop_back();
}
if(a15)now.pop_back();}
if(a14)now.pop_back();}
if(a13)now.pop_back();}
if(a12)now.pop_back();}
if(a11)now.pop_back();}
if(a10)now.pop_back();}
if(a9)now.pop_back();}
if(a8)now.pop_back();}
if(a7)now.pop_back();}
if(a6)now.pop_back();}
if(a5)now.pop_back();}
if(a4)now.pop_back();}
if(a3)now.pop_back();}
if(a2)now.pop_back();}
if(a1)now.pop_back();}
    }
    pt(ans);
}
signed main(){
    int T=1;
    while(T--)solve();
}
```

---

## 作者：happybob (赞：0)

神秘题。

不妨考虑若周期为 $k$，那么如何判定答案。

一个想法是，枚举 $k-1$ 个分割点，对 $k$ 段做 LCS 就好。枚举复杂度为 $O(n^k)$，求 LCS 的复杂度是 $O(n^{k-1})$，总复杂度为 $O(n^{2k-1})$，由于枚举分割点本质是组合数，常数比较小，能过 $k \leq 3$。

另一方面，考虑字符串中有 $k$ 段不相交的相同字符串，那么若将序列分为 $k$ 段，这个字符串必然是某段的子序列。此时复杂度为 $O(nk2^{\frac{n}{k}})$。实测可以通过 $k \geq 5$。

$k=4$ 怎么办。注意到在枚举分割点时，$k=2$ 的时候必然会枚举到中间的位置，从而这个答案会被 $k=2$ 时计算。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 85;

string s;
int n, ans = 0;
array<array<int, N>, N> f;
array<array<array<int, N>, N>, N> g;

inline int solve1(int x)
{
	for (int i = 0; i < N; i++) f[i].fill(0);
	for (int i = 1; i <= x; i++)
	{
		for (int j = x + 1; j <= n; j++)
		{
			if (s[i] == s[j])
			{
				f[i][j] = f[i - 1][j - 1] + 1;
			}
			f[i][j] = max({f[i][j], f[i - 1][j], f[i][j - 1]});
		}
	}
	return f[x][n];
}

inline int solve2(int x, int y)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) g[i][j].fill(0);
	}
	for (int i = 1; i <= x; i++)
	{
		for (int j = x + 1; j <= y; j++)
		{
			for (int k = y + 1; k <= n; k++)
			{
				if (s[i] == s[j] && s[j] == s[k]) g[i][j][k] = g[i - 1][j - 1][k - 1] + 1;
				g[i][j][k] = max({g[i][j][k], g[i - 1][j][k], g[i][j - 1][k], g[i][j][k - 1]});
			}
		}
	}
	return g[x][y][n];
}

inline int check(string& x)
{
	int ans = 0, now = 0;
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == x[now])
		{
			now++;
			if (now == x.size())
			{
				ans++, now = 0;
			}
		}
	}
	if (ans <= 1) return 0;
	return ans;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);	
	cin >> s;
	n = s.size();
	s = " " + s;
	for (int i = 1; i <= n; i++)
	{
		ans = max(ans, 2 * solve1(i));
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			ans = max(ans, 3 * solve2(i, j));
		}
	}
	for (int k = 5; k <= n; k++)
	{
		int r;
		int c = n / k;
		for (int l = 1; l <= n; l = r + 1)
		{
			r = min(n, l + c - 1);
			int len = r - l + 1;
			for (int S = 1; S < (1 << len); S++)
			{
				string res = "";
				for (int j = l; j <= r; j++)
				{
					if ((S >> (j - l)) & 1) res += s[j];
				}
				ans = max(ans, (int)res.size() * check(res));
			}
		}
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：Muse_Dash (赞：0)

[**Brain Power!**](https://music.163.com/#/song?id=399343130)

一个显然的做法，$2^{|S|}$ 的复杂度二进制枚举这个循环节 $T'$，然后判断其在 $S$ 中的出现次数 $k$，答案为 $\max\{T'k\}$。

实际上，假设 $k$ 的下限 $k'$ 是你所选定的，那么一定存在一段 $[i,i+\frac{|S|}{k'}]$ 区间包含至少一个子序列 $T'$。这不难证明，因为如果任何 $[i,i+\frac{|S|}{k'}]$ 这样的区间都不包含，那么 $T$ 在 $S$ 上左右两端的下标长度将 $>k'\times\frac{|S|}{k'}=|S|$，故证毕。

因此，可以考虑枚举左端 $l$，设定一个下界 $k'\leq k$，在 $[l,l+\frac{|S|}{k'}]$ 二进制枚举并判断。

而另外一种做法是，发现这就是在找重复的子序列，假设你固定了 $k$ 的上界 $k'>k$ 并枚举 $k$，可以枚举 $k-1$ 个断点 $t_1,t_2,\dots,t_{k-1}$，那么题意转化为求 $[1,t_1],[t_1+1,t_2],\dots,[t_{k-1},n]$ 的 $\text{LCS}$。

很容易计算出，第一个做法的复杂度是 $\Theta(2^{S\cdot k'^{-1}}|S|^2)$，第二个是 $\Theta(k'|S|^{k'-1})$。因为 $k'$ 在两个做法的意义分别是 $k$ 的上、下界，可以考虑合并做法。

发现对于第一个做法，取 $k'=5$，总复杂度为 $\Theta(2^{0.2S}|S|^2)$，而 $0.2S\leq16$，实现常数小完全可以跑得过去。而当取 $k'=5$，第二个做法似乎跑不过去。但实际上，$k=4$ 的解法被 $k=2$ 完全覆盖了，当且仅当存在 $T''$ 使得 $T'=T''+T''$ 时，$k=4,T''$ 为循环节的情况会被 $k=2,T'$ 为循环节覆盖。故对于第二种解法，分别求出 $k=2,3$ 的答案取 $\max$ 即可，这样也就完全能跑过去了。


```cpp
const int N=85,B=(1ll<<16)-1;
string s;
int ans,n,f[N][N],g[N][N][N];
int twolcs(int x){
	for (int i=0;i<=x+1;i++)
		for (int j=x;j<=n+1;j++)
			f[i][j]=0;
	for (int i=1;i<=x;i++)
		for (int j=x+1;j<=n;j++)
			f[i][j]=max({f[i][j-1],f[i-1][j],f[i-1][j-1]+(s[i]==s[j])});
	return f[x][n]*2;
}
int threelcs(int x,int y){
	for (int i=0;i<=x+1;i++)
		for (int j=x;j<=y+1;j++)
			for (int k=y;k<=n+1;k++)
				g[i][j][k]=0;
	for (int i=1;i<=x;i++)
		for (int j=x+1;j<=y;j++)
			for (int k=y+1;k<=n;k++)
				g[i][j][k]=max({g[i-1][j][k],g[i][j-1][k],g[i][j][k-1],g[i-1][j-1][k-1]+(s[i]==s[j]&&s[j]==s[k])});
	return g[x][y][n]*3;
}
int clac(string mode){
	int t=mode.size()-1,c=0;
	for (int i=1,_=1;i<=n;i++){
		if (s[i]==mode[_]) _++;
		if (_>t) _=1,c++;
	}
	return c;
}
signed main(){
	cin>>s,s=' '+s,n=s.size()-1;
	for (int x=1;x<n;x++)
		ans=max(ans,twolcs(x));
	for (int x=1;x<n;x++)
		for (int y=x+1;y<n;y++)
			ans=max(ans,threelcs(x,y));
	for (int i=1;i<=n;i++){
		for (int c=0;c<=B;c++){
			string mode=" ";
			int pop_count=0;
			for (int j=i,_=1;j<=min(n,i+15);j++,_<<=1)
				if (_&c) mode+=s[j],pop_count++;
			int cnt=clac(mode);
			if (cnt>=5) ans=max(ans,cnt*pop_count);
		}
	}
	cout<<ans;
	return 0;
}
```

---

