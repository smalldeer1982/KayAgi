# Construct the String

## 题目描述

定义 $f(s)$ 为一个字符串函数，其接收的字符串中只包含小写字母和`.`。$f(s)$ 的作用方法为：

1. 初始状态 $r$ 为空字符串`""`。
2. 从左至右处理 $s$ 中的字符。如果当前字符为小写字母，则将其添加到 $r$ 的末尾；如果当前字符为`.`，则
删去 $r$ 的最后一个字符。特别的，如果当前 $r$ 为空，而当前字符为`.`，则函数会崩溃（输入字符串非法）。
3. 最终得到的 $r$ 即为函数的返回值。

对于给定的字符串 $s$ 和 $t$ ，你需要从 $s$ 中删去尽可能少的字符，使得 $f(s')=t$（$s'$必须是合法的输入字符串，也即，函数作用过程中不能发生崩溃）。

求最少要删除的字符数目。

## 样例 #1

### 输入

```
a.ba.b.
abb```

### 输出

```
2```

## 样例 #2

### 输入

```
.bbac..a.c.cd
bacd```

### 输出

```
3```

## 样例 #3

### 输入

```
c..code..c...o.d.de
code```

### 输出

```
3```

# 题解

## 作者：include13_fAKe (赞：5)

学习 DP 优化应用的作业题，是 dwh 的讲课。



---

我并不清楚 $O(n^3)$ 的 dp 到底是怎么会事，那就直接讲 $O(n^2)$ 吧。

在两个字符串上 dp，可以设 $dp_{i,j}$ 表示 dp 到字符串 $s$ 的第 $i$ 位（本文的字符串下标从 $1$ 开始）、字符串 $t$ 的第 $j$ 位时的情况。

本题求的是删除字符数量的最小值，我们就用 $dp$ 数组存储 $s$ 的前 $i$ 位和 $t$ 的前 $j$ 位完全匹配时需要在 $s$ 中删除的字符个数。若不能完全匹配，$dp_{i,j}$ 的值赋为极大值。

有以下转移方式：

- 任何情况下均可以在末尾新增一个字符，此时需要删除的字符数量也随之加 $1$。此时 $i$ 的值加 $1$，$j$ 的值不变。

$$dp_{i+1,j}=\min(dp_{i+1,j},dp_{i,j}+1)$$

- 新增一个与字符串 $t$ 的下一位相同的字符，此时 $i,j$ 均加 $1$。

$$dp_{i+1,j+1}=\min(dp_{i+1,j+1},dp_{i,j})$$

- 当出现 `.` 号时，可以去掉一个匹配的字符，$i$ 加 $1$，$j$ 减 $1$。

$$dp_{i+1,j-1}=\min(dp_{i+1,j-1},dp_{i,j})$$

- （本题很有可能的巅峰难度）当某一段可以用 `.` 消除完，则可以对该段段尾的 $dp$ 值和段头前面的那个 $dp$ 值取 $\min$。

当将某一段的字母看作左括号、`.` 看作右括号时，若整段呈一个**合法括号序列**，则这一段可以被消除完。

令 $nxt_i$ 表示从第 $i$ 个字符开始的最短的可以被消除完的子串的末尾，以此类推，再令 $nxt1_i$ 表示从第 $i+1$ 个字符开始的最短的可以被消除完的子串的末尾。

$$dp_{nxt1_i,j}=\min(dp_{nxt1_i,j},dp_{i,j})$$

将上列 $dp$ 方程式结合起来即可得到正解。

此外，CF 机子较快，$O(n^2)$ 可以胜任 $n=10^4$。我的代码用时为 $\texttt{46 ms}$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int dp[10359][10359];
int nxt[10359];
int nxt1[10359];
string s;
string t;
//本题的要求是求最小值 不是和  
//(1) 任何字符 		直接插	dp[i+1][j]<-dp[i][j]+1 
//(2) 是点的字符 			dp[i+1][j-1]<-dp[i][j]
//(3) 相同的字符  			dp[i+1][j+1]<-dp[i][j]
//(4) 下一个有效的位置 		dp[nxt[i]][j]<-dp[i][j] 
signed main(){
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	cin>>s;
	cin>>t;
	int n=s.size();s=' '+s;
	int m=t.size();t=' '+t;
	memset(nxt,-1,sizeof(nxt));
	memset(nxt1,-1,sizeof(nxt1));
	for(int i=1;i<=n;i++){
		int now=0;
		for(int j=i;j<=n;j++){
			if(s[j]!='.')	now++;
			else	now--;
			if(now<0)	break;
			if(now==0){
				if(nxt[i]==-1)	nxt[i]=j,nxt1[i-1]=j;//cout<<i<<' '<<nxt[i]<<endl;
			}
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
			if(s[i+1]=='.')	dp[i+1][j-1]=min(dp[i+1][j-1],dp[i][j]);
			if(s[i+1]==t[j+1])	dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]);
			if(nxt1[i]!=-1)	dp[nxt1[i]][j]=min(dp[nxt1[i]][j],dp[i][j]);
		}
	}
	cout<<dp[n][m]<<endl;
	return 0;
}//我只能永远读着对白 读给我对你的伤害  
```

提交时要去掉一切中文注释，不然 CF 不接受提交。（CSP2024 我也有相似的经历……）

---

## 作者：ybw051114 (赞：2)

## 思路:

首先有一个很显然的思路，$dp_{i,j}$ 表示 $s_{1\cdots i}$ 匹配$t_{1\cdots j}$要删掉的字符的最小值。
$$dp_{i,j}=min\begin{cases}dp_{i-1,j}+1\\dp_{i-1,j-1}& & s_i=t_j\\dp_{i-1,j}& & si='.'&\end{cases}$$

然后我们发现它是假的，因为有可能存在先有一段字符，之后又会出现一段删除
所以我们可以统计一个 nxt 表示上一个清空的位置即可
现在式子变成
$$dp_{i,j}=min\begin{cases}dp_{nxt_i,j}+1\\dp_{i-1,j-1}& & s_i=t_j\\dp_{i-1,j}& & si='.'&\end{cases}$$

注意程序中的 nxt 表示下一个清空的位置。

## 实现:

```cpp
#include <bits/stdc++.h>

#ifndef use_ios11
#define use_ios11
using namespace std;
struct ins
{
    int ans;
    ins()
    {
        ans = 1;
    }
#define endl '\n'
    void read()
    {
    }
    void read1(char &s)
    {
        char c = getchar();
        for (; !isprint(c) || c == ' ' || c == '\n' || c == '\t'; c = getchar())
            ;
        s = c;
        if (c == EOF)
            ans = 0;
    }
    void read1(string &s)
    {
        s = "";
        char c = getchar();
        for (; !isprint(c) || c == ' ' || c == '\n' || c == '\t'; c = getchar())
            ;
        for (; isprint(c) && c != ' ' && c != '\n' && c != '\t'; c = getchar())
            s += c;
        if (c == EOF)
            ans = 0;
    }
    template <typename T>
    void read1(T &n)
    {
        T x = 0;
        int f = 1;
        char c = getchar();
        for (; !isdigit(c); c = getchar())
        {
            if (c == '-')
                f = -1;
            if (c == EOF)
            {
                ans = 0;
                return;
            }
        }
        for (; isdigit(c); c = getchar())
            x = x * 10 + c - 48;
        n = x * f;
        if (c == EOF)
            ans = 0;
        if (c != '.')
            return;
        T l = 0.1;
        while ((c = getchar()) <= '9' && c >= '0')
            x = x + (c & 15) * l, l *= 0.1;
        n = x * f;
        if (c == EOF)
            ans = 0;
    }
    void write() {}
    void write1(string s)
    {
        int n = s.size();
        for (int i = 0; i < n; i++)
            putchar(s[i]);
    }
    void write1(const char *s)
    {
        int n = strlen(s);
        for (int i = 0; i < n; i++)
            putchar(s[i]);
    }
    void write1(char s)
    {
        putchar(s);
    }
    void write1(float s, int x = 6)
    {
        char y[10001];
        sprintf(y, "%%.%df", x);
        printf(y, s);
    }
    void write1(double s, int x = 6)
    {
        char y[10001];
        sprintf(y, "%%.%dlf", x);
        printf(y, s);
    }
    void write1(long double s, int x = 6)
    {
        char y[10001];
        sprintf(y, "%%.%dLf", x);
        printf(y, s);
    }
    template <typename T>
    void write1(T n)
    {
        if (n < 0)
            n = -n, putchar('-');
        if (n > 9)
            write1(n / 10);
        putchar('0' + n % 10);
    }
    template <typename T>
    friend ins operator>>(ins x, T &n);
    template <typename T>
    friend ins operator<<(ins x, T n);
    operator bool()
    {
        return ans;
    }
};
template <typename T>
ins operator>>(ins x, T &n)
{
    if (!x.ans)
        return x;
    x.read1(n);
    return x;
}
template <typename T>
ins operator<<(ins x, T n)
{
    x.write1(n);
    return x;
}
ins yin;
ins yout;
#endif
using namespace std;
string s, t;
const int maxn = 1e4 + 10;
int dp[maxn][maxn];
int nxt[maxn];

int main()
{
    yin >> s >> t;
    for (int i = 0; i < s.size(); i++)
    {
        nxt[i] = -1;
        int bal = 0;
        if (s[i] != '.')
            for (int j = i; j < s.size();j++)
            {
                if (s[j] == '.')
                    --bal;
                else
                    ++bal;
                if (!bal)
                {
                    nxt[i] = j;
                    break;
                }
            }
    }
    memset(dp, 0x7f7f7f7f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 0; j <= t.size(); j++)
        {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
            if (j < t.size() && s[i] == t[j])
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
            if (s[i] != '.' && nxt[i] != -1)
                dp[nxt[i] + 1][j] = min(dp[nxt[i] + 1][j], dp[i][j]);
        }
    }
    yout << dp[s.size()][t.size()] << endl;
    return 0;
}

```


---

## 作者：SFlyer (赞：1)

设 $dp_{i,j}$ 为 $s$ 中前 $i$ 个和 $t$ 中前 $j$ 个匹配的最小花费。

那么显然有转移：

- $dp_{i,j}+1\rightarrow dp_{i+1,j}$。

- $dp_{i,j}\rightarrow dp_{i+1,j+1}$（$s_{i+1}=t_{j+1}$）。

- $dp_{i,j}\rightarrow dp_{i+1,j-1}$（$s_{i+1}=.$）。

但是发现还有一种情况就是 $s=aab..$，$t=a$，我们其实答案是 $0$。发现这种就是「我前面加的后面一定会剪掉，不用管」。因此我们预处理 $nxt_i$ 表示第一次 $j$ 满足 $s_{i\sim j}$ 操作下来是空。

那么有转移 $dp_{i,j}\rightarrow dp_{nxt_{i+1}}{j}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e4+4;

int n,m,nxt[N],sm[N],dp[N][N];
string s,t;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>s>>t;
	n=s.size();
	m=t.size();
	s=" "+s;
	t=" "+t;
	for (int i=1; i<=n; i++){
		sm[i]=sm[i-1]+(s[i]=='.'?-1:1);
	}
	map<int,int> mp;
	for (int i=n; i; i--){
		if (mp.count(sm[i-1]) && s[i]!='.'){
			nxt[i]=mp[sm[i-1]];
		}
		else{
			nxt[i]=n+1;
		}
		mp[sm[i]]=i;
	}
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for (int i=0; i<=n; i++){
		for (int j=0; j<=m; j++){
			if (dp[i][j]>1e9) continue;
			if (i<n){
				dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
			}
			if (i<n && j<m && s[i+1]==t[j+1]){
				dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]);
			}
			if (i<n && j && s[i+1]=='.'){
				dp[i+1][j-1]=min(dp[i+1][j-1],dp[i][j]);
			}
			if (nxt[i+1]<=n){
				dp[nxt[i+1]][j]=min(dp[nxt[i+1]][j],dp[i][j]);
			}
		}
	}
	cout<<dp[n][m]<<"\n";
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

首先不难得出一个 $n^3$ dp。设 $f_{i,j,k}$ 表示用 $s_{1\cdots i}$ 匹配 $t_{1\cdots j}$，且后面有 $k$ 个多余字符。转移为：

+ 当前位是字母，匹配不上：$f_{i,j,k}\to f_{i+1,j,k+1}$
+ 当前位是字母，匹配得上：$f_{i,j,0}\to f_{i+1,j+1,0}$
+ 当前位是句号：$f_{i,j,k}\to f_{i+1,j,k-1}$
+ 当前位是句号，$k=0$：$f_{i,j,0}\to f_{i+1,j-1,0}$
+ 删去当前位：$f_{i,j,k}+1\to f_{i+1,j,k}$

结合括号序，观察到很重要的一点：**若将字母视为左括号，句号视为右括号，一个右括号只会删除其匹配的左括号，记一个左括号的匹配右括号位置为 $p_i$。**

我们发现 $f_{i,j,k}$ 中 $k$ 非 $0$ 位，仅适用于第一，三条转移，即出现，又按括号序消去若干字符。等价于直接转移 $i-1\to p_i$。

于是保留 $f_{i,j,0}$，转移如下：

+ 原第二类转移：$s_i=t_j$ 时有 $f_{i,j}\to f_{i+1,j+1}$。
+ 原第五类转移：$f_{i,j}+1\to f_{i+1,j}$
+ $f_{i,j}\to f_{p_{i+1},j}$

时空 $O(n^2)$，实现时使用 `short` 开下。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

int n,m,pos[N],stk[N],tp;
short f[N][N];
char s[N],t[N];

#define chkmin(x,y) x = min(x,y)

int main(){
	scanf("%s%s",s + 1,t + 1);
	n = strlen(s + 1),m = strlen(t + 1);
	for(int i = 1;i <= n;++i){
		if(s[i] != '.') stk[++tp] = i;
		else pos[stk[tp--]] = i;
	}
	memset(f,63,sizeof f);
	f[0][0] = 0;
	for(int i = 1;i <= n;++i)
		for(int j = 0;j <= m;++j){
			if(pos[i]) chkmin(f[pos[i]][j],f[i - 1][j]);
			if(s[i] == t[j]) chkmin(f[i][j],f[i - 1][j - 1]);
			chkmin(f[i][j],short(f[i - 1][j] + 1));
		}
	printf("%d\n",f[n][m]);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑 $dp_{i,j}$ 表示 $s$ 的前缀 $i$ 匹配上了 $t$ 的前缀 $j$ 时，$s$ 至少删除多少个位置。

考虑转移，$s_k=t_{j+1}$ 时，$dp_{i,j}+f(i+1,k-1)\to dp_{i+k,j+1}$，其中 $f(i+1,k-1)$ 表示 $s$ 的 $i+1\sim k-1$ 位置删除为不改变原序列的最少删除数量。

显然这个 dp 是 $O(n^3)$ 的，需要一些优化。

考虑 $f(i,j)$ 的计算方式，将不是 `.` 的位置看作 $+1$，是 `.` 的位置看作 $-1$。考虑记录目前前缀和 $pre$，初始为 $0$，对序列做前缀和。如果某一时刻前缀和 $<0$，则将前缀和变回 $0$ 并在额外答案 $ex$ 上加 $1$。$f(i,j)=pre+ex$。

考虑动态维护所有 $f(x,j)$，并随着 $j$ 后移发生变化。开一个桶记录所有初始前缀和 $p_i=k$ 的 $dp_{k,g}$ 中的最小值 $mv_k$，其中 $g$ 为目前考虑到 $t$ 的第 $g$ 位。转移时，如果遇到 $s_{i+1}$ 为 `.`，所有 $p_x=p_i$ 的位置的额外答案就会加上 $1$，同时 $pre$ 也会增加。容易发现该操作本质上就是将 $p_x=p_i$ 的所有位置转移系数加 $1$，此后表现出 $p_x=p_i-1$ 的特征。于是每次遇到 `.` 就将 $mv_{p_i}+1\to mv_{p_i-1}$，然后将 $mv_{p_i}$ 设为 inf 即可。

当然，我们还要计算 $\min(mv_i-i)$，考虑开一个 $tmp$ 维护这玩意。对于存在一个 $mv_i-i$ 修改的时候，它有可能变大或变小，显然可以可删堆维护，应该是过不去的。注意到 $tmp$ 变大的时候一定是遇到 `.` 了，并且一个 `.` 只会让 $tmp$ 增加最多 $2$，所以开个统计数组维护 $mv_i-i$ 出现的次数即可。

总复杂度 $O(n^2)$，细节一车。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int dp[10005],f[10005];
int rem[40005],mv[40005],tmpans,nowlev;
signed main(){
	string s,t; cin>>s>>t; int n=s.size(),m=t.size(); s=" "+s,t=" "+t; 
	memset(dp,1,sizeof(dp)); dp[0]=0;
	for(int i=1;i<=m;i++){
		tmpans=1e9;
		for(int j=0;j<=40004;j++) rem[j]=0,mv[j]=1e9;
		nowlev=20001;
		f[0]=1e9;
		for(int j=0;j<=n;j++){
			if(mv[nowlev]>dp[j]&&dp[j]<1e5){
				if(mv[nowlev]<1e5) rem[mv[nowlev]-(nowlev-20001)+20001]--;
				mv[nowlev]=dp[j];
				rem[mv[nowlev]-(nowlev-20001)+20001]++;
				tmpans=min(tmpans,mv[nowlev]-(nowlev-20001));
			}
			if(s[j+1]==t[i]) f[j+1]=tmpans+(nowlev-20001);
			else f[j+1]=1e9;
			if(s[j+1]!='.') nowlev++;
			else{
				if(tmpans>1e5){
					nowlev--;
					continue;
				}
				if(mv[nowlev]<1e5) rem[mv[nowlev]-(nowlev-20001)+20001]--;
				mv[nowlev]++;
				if(mv[nowlev-1]>mv[nowlev]&&mv[nowlev]<1e5){
					if(mv[nowlev-1]<1e5) rem[mv[nowlev-1]-(nowlev-1-20001)+20001]--;
					mv[nowlev-1]=mv[nowlev];
					rem[mv[nowlev-1]-(nowlev-1-20001)+20001]++;
					tmpans=min(tmpans,mv[nowlev-1]-(nowlev-1-20001)+20001);
				}
				mv[nowlev]=1e9;
				while(!rem[tmpans+20001]) tmpans++;
				nowlev--;
			}
		}
		for(int j=0;j<=n;j++) dp[j]=f[j];
	}
	int minv=1e18;
	for(int i=0;i<=n;i++){
		int now=0;
		for(int j=i+1;j<=n;j++){
			if(s[j]=='.') now--;
			else now++;
			if(now<0) now=0,dp[i]++;
		}
		dp[i]+=now;
	}
	for(int i=0;i<=n;i++) minv=min(minv,dp[i]);
	cout<<minv;
	return 0;
}
```

---

