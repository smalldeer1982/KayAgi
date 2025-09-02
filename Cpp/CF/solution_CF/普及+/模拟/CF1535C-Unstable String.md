# Unstable String

## 题目描述

You are given a string $ s $ consisting of the characters 0, 1, and ?.

Let's call a string unstable if it consists of the characters 0 and 1 and any two adjacent characters are different (i. e. it has the form 010101... or 101010...).

Let's call a string beautiful if it consists of the characters 0, 1, and ?, and you can replace the characters ? to 0 or 1 (for each character, the choice is independent), so that the string becomes unstable.

For example, the strings 0??10, 0, and ??? are beautiful, and the strings 00 and ?1??1 are not.

Calculate the number of beautiful contiguous substrings of the string $ s $ .

## 样例 #1

### 输入

```
3
0?10
???
?10??1100```

### 输出

```
8
6
25```

# 题解

## 作者：LinkZelda (赞：12)

- **题意**：

$t$ 组询问，每次给定一个仅包含字符 `1` 或 `0` 或 `?` 字符串 $s$。定义一个子串是不稳定的当且仅当子串中任意相邻两数均不相同，如 $101010...$ 或 $010101...$。其中 `?` 可以变为 $1$ 或 $0$ 其中一种。请求出给定的 $s$ 中最多可以有的不稳定子串个数。

$1\leq t\leq 10^4,1 \leq\left\vert s\right\vert\leq2\times10^5,\sum \left\vert s\right\vert\leq2\times10^5$。

- **题解**：

考虑 `dp`，定义 $dp_{i,1/0}$ 表示第 $i$ 位为 $1/0$ ，以 $i$ 为结尾的极长不稳定子段长。

当 $s_i=$`1`，有 $dp_{i,1}=dp_{i-1,0}+1$。

当 $s_i=$`0`，有 $dp_{i,0}=dp_{i-1,1}+1$。

当 $s_i=$`?`，有 $dp_{i,1}=dp_{i-1,0}+1$，$dp_{i,0}=dp_{i-1,1}+1$。

然后我们扫一次 `dp` 数组，把每一个 $\max(dp_{i,1},dp_{i,0})$ 加起来就是答案了。时间复杂度为 $O(\left\vert s\right\vert)$。

- [代码](https://www.luogu.com.cn/paste/dotr7r10)

---

## 作者：HoshizoraZ (赞：3)

这题可以尝试暴力通过。

当然直接枚举子串的左右端是肯定过不去的，我们可以改变下枚举的东西。

如果说我们每确定一个左端点 $i$，都能找到它右边最多能延伸的最大长度 $j$，那么以 $i$ 为左端点的合法子串个数就是 $j-i+1$。

-----

再找找字符串的特征。

发现题目要求合法的串是 `01` 交替的，可以理解为相邻两个字符位置**不同**。

如果我们把 `01` 串每**奇数或偶数**下标的字符进行 `0,1` 反转，那么条件就可以变成相邻两个字符位置**相同**。

因此我们可以先利用类后缀和的方式找到**右边第一个等于 $0/1$ 的数的位置**

对于每个左端点 $i$：

- 如果 $s_i=0$，那么找右边第一个等于 $1$ 的位置 $j$，答案为 $j-i$；
- 如果 $s_i=1$，那么找右边第一个等于 $0$ 的位置即可。
- 如果 $s_i=$ `?`，我们找到右边第一个不等于 `?` 的位置 $j$，再找到 $s_j$ 右边第一个和 $s_j$ 相反且不是 `?` 的位置。
- 整合一下，$s_i=0/1$ 统计方法其实属于 $s_i=$ `?` 的情况。

提醒：以上统计中，注意到可能某个位置右边不存在 $0/1$，这时拿 $n+1$ 减去该位置即可。

时间复杂度 $O(\sum n)$。

**代码**

```cpp
#include <cstring>
#include <cstdio>
#define INF 1e9
#define eps 1e-6
typedef long long ll;

int t, n, a[200010][2];
char s[200010];
ll ans = 0;

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){

	scanf("%d", &t);
	while(t--){
		scanf("%s", s + 1), n = strlen(s + 1);
		for(int i = 1; i <= n; i += 2){			// 反转奇数位的 0/1
			if(s[i] == '0') s[i] = '1';
			else if(s[i] == '1') s[i] = '0';
		}
		a[n + 1][0] = a[n + 1][1] = n + 1, ans = 0;
		for(int i = n; i >= 1; i--){	// 每个位置右边第一个 0/1
			if(s[i] == '1') a[i][0] = a[i + 1][0], a[i][1] = i;
			if(s[i] == '0') a[i][1] = a[i + 1][1], a[i][0] = i;
			if(s[i] == '?') a[i][0] = a[i + 1][0], a[i][1] = a[i + 1][1];
		}
		for(int i = 1; i <= n; i++)
			ans += max(a[i][0], a[i][1]) - i;	// 右边第一个 0,1 中较远的位置减去 i
		printf("%lld\n", ans);
	}

	return 0;
}
```

---

## 作者：Lynkcat (赞：3)

考虑一种更好想的做法。

首先 `?` 无论如何都合法，不需要特别讨论，只讨论 $0/1$ 。

我们考虑钦定 $r$ 然后算 $l$ 的取值范围，显然当有一个位置满足奇偶性与 $r$ 相同但值不同或者奇偶性与 $r$ 不同但值相同时不合法。所以直接扫一遍维护一下 $f[0/1][0/1]$ 位置奇偶性值为 $0/1$ 目前位置最靠右的位置就没了。

```c++
int T,n,ans,f[2][2],dp[N],l,r;
string st;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>T;
	while (T--)
	{
		cin>>st;memset(f,0,sizeof(f));ans=0;
		int n=st.length();
		for (int i=0;i<st.length();i++)
		{
			int u=st[i]-'0';
			r=i+1;
			if (st[i]!='?')
			{
				l=max(f[i&1][u^1]+1,f[(i&1)^1][u]+1);
				f[i&1][u]=i+1;
			} else l=1;
			
			if (i!=0)
				dp[i]=max(dp[i-1],l); else dp[i]=1;
			ans+=(r-dp[i]+1);
		}
		writeln(ans);
	}			
}
```

---

## 作者：奥特战士 (赞：3)

原题链接：[洛谷](https://www.luogu.com.cn/problem/CF1535C)
[CF](https://codeforces.ml/contest/1535/problem/C)

# 题面分析
~~感谢翻译大哥~~

>$t$ 组询问，每次给定一个仅包含字符 $1$ 或 $0$ 或 $?$ 字符串 $s$。定义一个子串是不稳定的当且仅当子串中任意相邻两数均不相同，如 $101010...$ 或 $010101...$ 。其中 $?$ 可以变为 $1$ 或 $0$ 其中一种。请求出给定的 $s$ 中最多可以有的不稳定子串个数。

~~个人感觉~~翻译得还是很简单易懂的

那么问题就变得十分简单了

# 做法分析
## 法1
首先，最离谱的方法是

**把每个问号都01讨论一遍，然后枚举 $s$ 的所有子串**

且不说枚举子串的 $O(n^3)$，单是讨论问号的 $O(2^n)$ 就离谱到了极致

pass
## 法2
不难看出，一个个地讨论问号意义不大

那我们怎么办呢？

首先还是枚举出 $s$ 的所有子串

我们从左到右依次枚举子串的字符

如果相邻两个字符**相同**，那自然不行

要是我们枚举到了**问号**，我们应该把它当做**不同于前一字符的字符**

道理很简单，因为我们要找的是符合条件的字符串

这样的话，复杂度就只有枚举子串的 $O(n^3)$

但还是太久了
## 法3
仔细观察，当一个字符串**满足条件**的时候

**它的所有子串都满足条件**

因为任意一个**相邻字符不相同的01串**，不管怎么截取，**相邻两字符都不可能相同**

~~这不废话吗~~

那么问题就变得很简单

我们只需要依次遍历，当**相邻两字符相同**的时候，加上**之前统计的长度的子串个数**，然后**重新统计**

那么**问号**怎么办呢？

和 **法2** 一样，把它当做**不同于前一字符的字符**
### 注意
现在有这样一个字符串：
$101??1010$

按照我们之前的说法，我们应该挨个遍历

把**问号**变成相应的 $0$ 或 $1$

这个字符串就变成了这样：
$101011010$

在第五位的时候重新统计，最后我们得到的两个字符串的长度为 $5$ 和 $4$

但是**有个问题**

这两个**问号**并不是固定的

$101??$ 和 $??1010$ 都**符合条件**

所以说**在问号处重新统计**时

需要**加上这一串问号的长度**

复杂度 $O(n)$
### 注意
但是我们还没有做完

注意到子串$??$被统计了两次

所以说我们应该再减去**连续问号**的子串个数
# 代码实现
~~有误，勿抄~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RG register
#define ll long long
const int N=2e5+5;
int n,T,ans;
char s[N];
ll lent,lens,len;
inline int read(){
	RG int w=0;RG char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){w=(w<<3)+(w<<1)+(ch^48);ch=getchar();}
	return w;
} 
inline void write(ll x){
	if(x>9)write(x/10);
	putchar(x%10^48);
}
inline ll h(ll x){
	return (x*(x+1))/2+1; 
}
int main(){
	T=read();
	while(T--){
		scanf("%s",s+1);
		n=strlen(s+1);
		bool f1=1,f2=0;
		lent=0,lens=0,len=0;
		ans=0;
		for(RG int i=1;i<=n;++i){
			if(s[i]=='?'){
				if(s[i-1]!='?')len=0;
				++lens;
				++len;
				f2^=1;
			}
			else if(f1){
				f1=0;
				f2=s[i]-'0';
				++lent;
			}
			else{
				if(f2^1==s[i]-'0'){++lent;f2^=1;}
				else if(s[i-1]=='?'){
					ans+=h(lent+lens)-h(len);
					lens=len;
					lent=1;
					f2=s[i]-'0';
				}
				else{
					ans+=h(lent+lens);
					lens=0;
					lent=1;
					f2=s[i]-'0';
				}
			}
		}
		write(ans);
		putchar(10);
	}
	return 0;
}
```


---

## 作者：StayAlone (赞：3)

### 题意

给定一个只含有 `?`、`0`、`1` 的字符串。`?` 可以被替换成 `0` 或 `1`。  

如果一个字符串中每一个字符的左右两边都与它不相同，则称该字符串是**不稳定的**。  

请你输出输入的字符串的不稳定的子串的数量。**`0`、`1` 也是不稳定的**。  

### 思路

简单动态规划。

为了方便描述，下面将“不是 `?`”简略成“已知/确定”

动态规划最重要的就是数组的含义：

- $dp_{i, j}$ 表示以第 $i$ 个位置为结尾，这个位置是 $j$ 的合法子串数量。  

容易看出，$j$ 只有 `1`、`0` 两种可能，且很多时候是固定的。  

由于字符串 `0`、`1` 也是不稳定的，因此易得边界：

- 当 $s_0$ 确定时，$dp_{0, (s_0 - '0')} = 1$；

因为 $s_0$ 确定，故这个字符减 '0' 后的值就是这里的 $j$。

- 若 $s_0$ 不确定，那我们要假设它是 `0`、`1` 两种情况，故 $dp_{0, 1} = dp_{0, 0} = 1$。

```cpp
if (s[0] != '?') dp[0][s[0] - '0'] = 1;
else dp[0][0] = dp[0][1] = 1;
```

接下来就是推：

同样分两种情况：

- 当 $s_0$ 确定时，$dp_{i, (s_0 - '0')} = dp_{i-1, !(s_0 - '0')} + 1$；

因为这里会在上一次的基础上，增加一个合法的子串，而取反是为了保证串合法(即这个位置与上一个位置的值不相同)。  

- 若 $s_0$ 不确定，那我们要假设它是 `0`、`1` 两种情况，故 $dp_{i, 1} = dp_{i-1, 0} + 1,dp_{i, 0} = dp_{i-1, 1} + 1$。  

原因同上，不做赘述。  

最后的答案是所有以某个位置为结尾的子串数量之和：  
$$ans = \sum_{i = 0}^{len - 1}\max(dp_{i, 0}, dp_{i, 1})$$  
上面 $len$ 表示字符串的长度。  
由于要让值尽量大，故要取这个位置是 `0` 和这个位置是 `1` 的最大值。  

注意 $dp$ 数组和 $ans$ 要开 $\texttt{long long}$。  
~~比赛的时候第一次交没开，亏死了。~~

[AC code记录](https://www.luogu.com.cn/record/51488473)

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t; ll ans, dp[200010][2]; string s;

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		cin >> s;
        int len = s.length(); ans = 0;
		if (s[0] != '?') dp[0][s[0] - '0'] = 1;
		else dp[0][0] = dp[0][1] = 1; // 边界
		for (int i = 1; i < len; ++i)
			if (s[i] != '?')
				dp[i][s[i] - '0'] = dp[i-1][!(s[i] - '0')] + 1;
			else
				dp[i][0] = dp[i-1][1] + 1, dp[i][1] = dp[i-1][0] + 1;
		for (int i = 0; i < len; ++i) ans += max(dp[i][0], dp[i][1]); // 如题解公式
		printf("%lld\n", ans);
		for (int i = 0; i < len; ++i) dp[i][0] = dp[i][1] = 0; //记得清空
	}
	return 0;
}
```

---

## 作者：Create_Random (赞：2)

[C.Unstable String](https://codeforces.ml/contest/1535/problem/C)

提供一种不一样的做法：

题目要求求不稳定子串个数，

发现不稳定子串不好求，

那么我们可以正难则反求非法情况。

我们发现如果对于一段 $l$ 到 $r$ 的区间非法，

那么以 $l$ 及之前为开头, $r$ 为结尾的子串一定都非法，

那么就相当于可以对于每一个 $i$ ,

寻找距其最近的左侧的非法点减去答案。

情况可分 $3$ 类：

- $0/1$ 的相邻

- $0$ 和 $1$之间有奇数个 $\text{?}$

- $0$ 和 $0$ 或 $1$ 和 $1$ 之间有偶数个 $\text{?}$

在统计答案时同时更新最近非法点即可。

注意：

- 处理第一种情况时别忘了更新后两种情况下的最近非法点

- 如果开始点只是一个单独的 $\text{?}$, 那么在更新答案时要将其跳过

时间复杂度 $O(\left\vert s \right\vert t)$.

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int st[200010],ed[200010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		memset(st,0,sizeof(st));
		memset(ed,0,sizeof(ed));
		cin>>s;
		long long n=s.length();
		long long ans=(1+n)*n/2;
		int nope=-1,lastnope=-1;
		int cnt=0;
		for(int i=0;i<s.length();i++)
		{
			if(i==0&&s[i]=='?')
			{
				st[++cnt]=i;
				continue;
			}
			if(s[i]=='?'&&s[i-1]!='?')
			{
				st[++cnt]=i;
			}
			if(i==0)
			{
				continue;
			}
			if(s[i]!='?'&&s[i-1]=='?')
			{
				ed[cnt]=i-1;
			}
		}
		cnt=1;
		if(s[0]=='?'&&s[1]!='?')
		{
			cnt=2;
		}
		for(int i=1;i<s.length();i++)
		{
			if(s[i]!='?')
			{
				if(s[i]==s[i-1])
				{
					nope=i-1;
					ans-=i;
				}
				else
				{
					ans-=nope+1;
				}
				lastnope=nope;
			}
			else
			{
				int len=ed[cnt]-st[cnt]+1;
				if(s[st[cnt]-1]!=s[ed[cnt]+1]&&len%2||s[st[cnt]-1]==s[ed[cnt]+1]&&len%2==0)
				{
					nope=st[cnt]-1;
				}
				ans-=lastnope+1;
				if(ed[cnt]==i)
				{
					lastnope=nope;
					cnt++;
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

