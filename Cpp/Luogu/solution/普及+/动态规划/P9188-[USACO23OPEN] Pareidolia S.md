# [USACO23OPEN] Pareidolia S

## 题目描述

### 题目背景

**注意：本题的时间限制为 4 秒，是默认时间限制的 2 倍。**

Pareidolia 是一种现象，指的是人们倾向于在并不真正存在的地方看到熟悉的图案——例如在云中看到一张脸。可以想象，由于农夫 John 经常与奶牛接触，他常常在日常物品中看到与奶牛相关的图案。例如，如果他看到字符串 "bqessiyexbesszieb"，农夫 John 的眼睛会忽略其中的一些字母，而他看到的只是 "bessiebessie"。


给定一个字符串 $s$，令 $B(s)$ 表示通过删除 $s$ 中的零个或多个字符后，能够形成的 "bessie" 的最大重复次数。在上面的例子中，$B(\text{``bqessiyexbesszieb"}) = 2$。

计算 $B(s)$ 是一个有趣的挑战，但农夫 John 对解决一个更有趣的挑战感兴趣：给定一个长度不超过 $3 \cdot 10^5$ 的字符串 $t$，且仅由字符 a-z 组成，计算所有连续子串 $s$ 的 $B(s)$ 之和。

## 说明/提示

对于第一个样例，有 12 个子串恰好包含 $1$ 个 "bessie"，有 $1$ 个子串恰好包含 $2$ 个 "bessie"，因此总数为 $12 \cdot 1 + 1 \cdot 2 = 14$。

- 输入 3-5：字符串长度不超过 $5000$。
- 输入 6-12：没有额外限制。

## 样例 #1

### 输入

```
bessiebessie
```

### 输出

```
14
```

## 样例 #2

### 输入

```
abcdefghssijebessie
```

### 输出

```
28
```

# 题解

## 作者：Nuyoah_awa (赞：14)

### 题目大意

给定一个字符串，求这个字符串所以子段中 `bessie` 出现的数量。
### 题目分析
思路：dp。

我们观察一个子段的值是子段中 `bessie` 的数量，我们可以考虑把这个值分开来算。

我们定义 $dp[i]$ 表示以 $i$ 结尾的字串中 `bessie` 的数量。我们从第 $i$ 位倒过来找 `bessie`，第一个 `bessie` 的 `b` 在第 $j$ 位。

转移方程为：
$$dp[i] = dp[j-1] + j$$
答案为:
$$\sum^{i\le n}_{i = 1}dp[i]$$

其中 $j$ 表示 $s[1…i],s[2…i],……,s[j…i]$ 都会把最后那个 $bessie$ 包含一次，$dp[j-1]$ 表示以 $j-1$ 结尾的那些子段所包含的那些 `bessie`，在末尾拼上 $s[j…i]$ 形成以 $i$ 结尾的那些子段里都被包含。这样子，每个 `bessie` 在某个子段中出现几次就会被记几次。

然后问题就变成了如何求 $j$，我们定义 $f[i]$ 表示到当前字符，最后一个 `bessie` 的前 $i$ 个字母中 `b` 出现的位置，转移方程为：如果当前字符串为 `bessie` 的第 $i$ 个字母，$f[i] = f[i-1]$。所以最后一个 `bessie` 中的 `b` 出现的位置为 $f[6]$（$j = f[6]$）。

这样时间复杂度就是 $\mathcal O(n)$ 的。

### code
```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

const int N = 3e5 + 5; 
int n, f[7], ans, dp[N];
string s;

signed main()
{
	cin >> s;
	n = s.size(); 
	s = "#" + s;
	for(int i = 1;i <= n;i++)
	{
		if(s[i] == 'b')
			f[1] = i;
		if(s[i] == 'e')
			f[6] = f[5], f[2] = f[1];
		if(s[i] == 's')
			f[4] = f[3], f[3] = f[2];
		if(s[i] == 'i')
			f[5] = f[4];
		dp[i] = dp[f[6] - 1] + f[6];
	}
	for(int i = 1;i <= n;i++)
		ans += dp[i];
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：ylch (赞：3)

## Description

给定一个字符串序列 $s\ (|s| \le 3 \times 10^5)$，求 $s$ 的所有子串中 `bessie` 出现的次数。

## Analysis

这道题的原型其实是一个叫“子序列自动机”的东西，但这道题序列只有6个字符，相当于是“阉割版”。

其他题解都没有讲明白前半段思路（倒求和符号）是怎么来的。

### part 1.

我们已知有一种很神奇的技巧：**通过改变求和符号的顺序来降低时间复杂度。**


例如这道题，题目要求的东西如下：

$$\sum\limits_{l=1}^{n} \sum\limits_{r=1}^{n} B(l,r)$$

考虑把第二个表示 $r$ 的求和符号提到前面去，式子就变成：

$$\sum\limits_{r=1}^{n} (\sum\limits_{l=1}^{r} B(l,r))$$

我们凭直觉可以知道：后面括号里的东西是一定可以预处理或递推出来的，这样时间复杂度就是 $O(n)$ 的了（只需要枚举 $r$ 即可）。


---

### part 2.

说人话：我们需要求一个  $dp[i]$，表示在前i个里面出现了多少个 `bessie`，答案显然即为 $\sum\limits^{n}_{i=1} dp[i]$。

假设我们要求位置 $i$ 的答案，且 $1 \sim i$ 中最后一个 `bessie` 出现的（开头 `b` 的）位置为 $j$，则转移方程为：$dp[i]=dp[j-1]+j$。

$dp[j-1]$ 很好解释，是前面已经求好的部分；$j$ 则表示最后一个 `bessie` 会对 $j$ 个区间产生贡献：$[1,i], [2,i], \cdots , [j,i]$。


---

### part 3.

问题就转化成：已知 $i$，如何求 $j$。

这里其实第一篇题解已经讲得很清楚了。我们可以考虑用类似递推的方法，设 $lst[i]$ 表示上一个 `bessie` 第 $i$ 个字符出现的位置。

考虑类似“滚动”的转移方法：假设当前字符为 `bessie` 的第 $i$ 个字符，则 $lst[i]=lst[i-1]$。

这样下来，最后一个 `b` 的出现位置即为 $lst[6]$，即 $j=lst[6]$。

## Summary

思想：改变求和符号的顺序来降低时间复杂度。

递推：$lst[i]=lst[i-1]$，其中当前字符为 `bessie` 的第 $i$ 个。

转移方程：$dp[i]=dp[j-1]+j$，其中 $j=lst[6]$。

答案：$\sum\limits^{n}_{i=1} dp[i]$（别忘了开 long long）

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 7;

int len, lst[maxn]; 
ll dp[maxn];

void solve()
{
	string s; cin >> s;
	len = s.size();
	s = " " + s; // 让下标从1开始
	
	for(int i = 1; i <= len; i ++){
		if(s[i] == 'b') lst[1] = i; 
		if(s[i] == 'e') lst[6] = lst[5], lst[2] = lst[1];
		if(s[i] == 's') lst[4] = lst[3], lst[3] = lst[2];
		if(s[i] == 'i') lst[5] = lst[4];
		int j = lst[6];
		dp[i] = dp[j - 1] + j;
	}
	
	ll ans = 0;
	for(int i = 1; i <= len; i ++) ans += dp[i];
	cout << ans << '\n';
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：DengDuck (赞：3)

第一篇题解的做法就是我的做法，在此我讲详细一点，让大家听得不要那么茫然。

首先我们设 $f_i$ 表示以 $i$ 作为结尾的区间中总共有多少 `bessie`。

考虑转移。

首先我们需要找到最近的一个 `bessie`，我们可以考虑设一个 $lst_i$ 表示找到的上一个 `bessie` 的前 $i$ 项的起始位置。

举个例子，字符串 `bessie` 就有 $lst_i=1(1\leq i\leq 6)$。

那这个怎么算呢？我们找到一个字符，先设想其是 `bessie` 哪一位，设为 $x$ 位，则它的开头显然是 $lst_{x-1}$。

接下来，我们把贡献分成两份，一份是上一个 `bessie` 的贡献，一份是其他 `bessie` 的贡献。

后者的贡献我们发现就是 $f_{lst_6-1}$，因为往后的字符串与我们当前的这个 `bessie` 不可以同时出现。

对于当前的字符串，我们发现对于 $l\in[1,lst_6]$ 而言都可以包含当前这个 `bessie`，因此 `bessie` 总数会增加 $lst_6$。

得转移方程：

$$
f_i=f_{lst_6-1}+lst_6
$$

而问题问的是所有区间，所有我们需要把它们加起来，即：

$$
ans=\sum_{i=1}^n f_i
$$

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
char c[N];
LL n,lst[N],f[N],ans;
int main()
{
	scanf("%s",c+1);
	n=strlen(c+1);
	for(int i=1;i<=n;i++)
	{
		if(c[i]=='b')lst[1]=i;
		if(c[i]=='e')lst[2]=lst[1],lst[6]=lst[5];
		if(c[i]=='s')lst[4]=lst[3],lst[3]=lst[2];
		if(c[i]=='i')lst[5]=lst[4];
		f[i]=f[lst[6]-1]+lst[6];
	}
	for(int i=1;i<=n;i++)
	{
		ans+=f[i];
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：luogu_gza (赞：2)

我们考虑问题的一个子问题。

如果求整个子串的 $B$ 函数，怎么求？我们考虑双指针匹配就好了。

但是在这个问题中，我们考虑建立如下数组：

$f_{1,i}$：从第 $i$ 个位置以后，第一个字符 b 的位置。

$f_{2,i}$：从第 $i$ 个位置以后，第一个字符 e 的位置。

$f_{3,i}$：从第 $i$ 个位置以后，第一个字符 s 的位置。

$f_{4,i}$：从第 $i$ 个位置以后，第一个字符 i 的位置。

随之，我们就可以求出 $g$ 数组，令 $g_i$ 表示从第 $i$ 个位置以后，第一个子串 `bessie` 结尾的位置。

通过不断跳 $g_i$ 数组，我们就可以极其快速的统计答案。

其实，我们就是在试图找到第一个拥有一个 `bessie` 的位置，第一个拥有两个 `bessie` 的位置。

然后就是暴力了。

还有一个小细节：我们考虑记录从上一个 `bessie` 开始，不是 b 字符的位置个数，每次 ans 更新的时候，贡献全部乘上 cnt 就好了。

因为一开头如果不是 b 字符的话，实际上不会对答案产生任何贡献，这也是为了减小常数而进行的操作。

实测跑的贼快，记得开龙龙捏。

[record](https://www.luogu.com.cn/record/119411711)

---

## 作者：ForwardStar (赞：2)

## 非常详细的解析
### [更差的阅读体验](https://www.luogu.com.cn/blog/xzzw/p9188-usaco23open-pareidolia-s-ti-jie)
首先注意题目的要求： 

- $\texttt{bessie}$ 要相连，不能重叠
- 统计的是每个子串，开头和结尾都要考虑

于是我们就想到了暴力算法，枚举每个起点，找出从这个起点开始的每个子串 $\texttt{bessie}$ 最多出现的次数，最后累加。找次数时运用贪心，即能遇到能与之前的接上前面就接。  
证明也很显然，如果不接，删除这个字母，就需要在后面找相同的字母接上，这样不仅没有增加答案个数，还浪费了字母。
### 代码：
```c++
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#define int long long
using namespace std;
const int N=5003;
int n,ans;
char b[10]={' ','b','e','s','s','i','e'};
char str[N];
int a[N][N],sum[N];
signed main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	int now;
	for(int i=1;i<=n;i++){
		now=1;
		for(int j=i;j<=n;j++){
			if(str[j]==b[now]){
				now++;
				if(now==7){
					now=1;
					a[i][j]++;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		memset(sum,0,sizeof(sum));
		for(int j=i;j<=n;j++){
			sum[j]=sum[j-1]+a[i][j];
			ans+=sum[j];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```
（~~其实在暴力中这个也过于暴力了，有许多地方可以优化~~）

时间复杂度 $O(N^2)$，只能通过前五个测试点。此时，需要优化代码。  
想想我们刚刚的贪心策略，能接上就接上，就是让最后面的字符尽量靠前。那相同的，我们在统计每个 $\texttt{bessie}$ 时，让前头在条件满足时尽量靠后，因为能够接成 $\texttt{bessie}$ 的子串越短，他被其他子串包含的次数就会越多。   
此时就很明了是状态转移，设 $f[i]$ 为以第 $i$ 位为结尾的所有子串包含 $\texttt{bessie}$ 的次数。  
此时我们再临时假设一个 $pos$，代表当前离第 $i$ 位的最近的拼接成功的 $\texttt{bessie}$ 的 $\texttt{b}$ 的位置（也就是最前面的）。  
当到了 $i$ 这个点，要统计以第 $i$ 位为结尾的子串出现 $\texttt{bessie}$ 的次数和，我们以 $pos$ 为分界，分开统计下面两种情况： 

- 统计以第 $i$ 位为结尾的子串，$\texttt{bessie}$ 在 $pos$ 之前的出现次数和。
- 统计以第 $i$ 位为结尾的子串，$\texttt{bessie}$ 在 $pos$ 之后出现的次数和。

对于第一种情况，说白了就是只能用到 $pos$ 之前，可以直接使用之前的状态，就是 $f[pos - 1]$。  
对于第二种情况，由于 $pos$ 到 $i$ 之间只有一个完整的 $\texttt{bessie}$，且其起点就在 $pos$ 的位置，所以只有以 $pos$ 之前（包含 $pos$）为起点的子串才会包含这个 $\texttt{bessie}$。  
最后得到状态转移方程 
$$
f[i] = f[pos-1] + pos
$$
如何找到 $pos$ 呢？  
继续运用贯穿全题的贪心思想，能接就接，我们所接的上一个字母应当是前面离我最近的，所以这个字母的 $pos$，就是离他最近的与它拼接的字母的 $pos$。  
我们将 $\texttt{bessie}$ 这六个字母中的第 $j$ 个字母离第i位最近的对应拼接字母的 $pos$ 定义为 $pos[j]$。  
当第 $i$ 位发现了新字母时，更新对应字母的 $pos$。
$$
pos[j] = pos[j-1]
$$
$$
pos[1] = i
$$
而当拼到最后一个字母时才组成完整的 $\texttt{bessie}$，$pos$ 要取 $pos[6]$。  
最后的状态转移方程： 
$$
f[i] = f[pos[6] -1] + f[6]
$$
由于不同起点已经在每一项累加过了，所以只需要把不同终点的累加起来。  
## 代码：

```c++
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdio>
using namespace std;
const int N=3e5+5,inf=2147483647;
char str[N];
int n;
int pos[10];
long long f[N];
long long ans;
int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;i++){
		if(str[i]=='b')pos[1]=i;
		else if(str[i]=='e'){
			pos[2]=pos[1];
			pos[6]=pos[5];
		}
		else if(str[i]=='s'){
			pos[4]=pos[3];
			pos[3]=pos[2];
		}
		else if(str[i]=='i')pos[5]=pos[4];
		f[i]=f[pos[6]-1]+1ll*pos[6];
		ans+=f[i];
	}
	printf("%lld\n",ans);
	return 0;
}

```



---

## 作者：cff_0102 (赞：1)

设 $s$ 的长度为 $n$。不难在 $O(n)$ 的时间内预处理出以每个 `e` 为结尾的 `bessie` 的那个 `b` 最晚可能出现的位置。

设 $f_i$ 表示所有以 $i$ 为结尾的区间的 $B$ 函数值之和。

如果 $s_i$ 不是 `e`，则有 $f_i=f_{i-1}$，即所有 $f_i$ 中提到的区间右端点都往后移动 $1$。由此不可能出现新的 `bessie`。

如果 $s_i$ 是 `e`，首先找到 `bessie` 中 `b` 的位置 $b$，如果存在的话，就有 $f_i=f_b+b$。即，所有 $f_b$ 中提到的区间右端点都直接越过了一个新的 `bessie` 到达后面的这个 `e`，那么所有这些区间的 $B$ 函数的和就增加了 $b$。对于 $(b,i)$ 的数，显然这中间不可能再出现一个 `bessie`，$B$ 函数值为 $0$。

需要注意的是不能使用 $f_i=f_{i-1}+b$，这里给出一个 hack：`bessibessie`，正确输出是 $10$。

我的代码用了一个比较抽象且复杂的方法来找到 `bessie` 中 `b` 的位置，但是看起来似乎更好懂？

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int f[N];
int lstb[N],lste[N],lsts[N],lsti[N];
int lstbessie(int e){
	int ie=lsti[e];
	if(ie==-1)return -1;
	int sie=lsts[ie];
	if(sie==-1)return -1;
	int ssie=lsts[sie];
	if(ssie==-1)return -1;
	int essie=lste[ssie];
	if(essie==-1)return -1;
	int bessie=lstb[essie];
	return bessie;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	string s;cin>>s;int n=s.length();s=" "+s;
	lstb[0]=lste[0]=lsts[0]=lsti[0]=-1;
	for(int i=1;i<=n;i++){
		lstb[i]=lstb[i-1];
		lste[i]=lste[i-1];
		lsts[i]=lsts[i-1];
		lsti[i]=lsti[i-1];
		if(s[i-1]=='b')lstb[i]=i-1;
		if(s[i-1]=='e')lste[i]=i-1;
		if(s[i-1]=='s')lsts[i]=i-1;
		if(s[i-1]=='i')lsti[i]=i-1;
	}
	f[0]=0;
	long long ans=0;
	for(int i=1;i<=n;i++){
		f[i]=f[i-1];
		if(s[i]=='e'){
			int b=lstbessie(i);
			if(b!=-1){
				f[i]=f[b]+b;
			}
		}
		ans+=f[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Timmy_ (赞：1)

# 前言

经过四次来自银组的折磨，我 USACO 终于过了！！！

## 算法一

针对 $n\le 5000$ 进行暴力枚举。

把所有子串都枚举出来，在枚举的过程中顺手统计 ```bessie``` 出现的次数。

代码过于简单，在这里就不放了~~懒得写~~。

## 算法二

首先问题的本质是让你在 $s$ 串中找到 ```bessie``` 这个子串，但是值得一提的是当一个子串中出现了不止一个 ```bessie``` 并且不重叠而且有先后顺序的话，价值会是不同的，其次，答案求的是子串中 ```bessie``` 最大的数量，如果单纯考虑 ```bessie``` 出现的次数，是会出错的。

### 子问题 1
不过，在得出最终结论之前，我们先想想这个问题的简化版，在 $s$ 串中找到 ```bessie``` 出现的次数。

不难发现，这是一个非常模板的题，我就不过多赘述了。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N=3e5+5;
char x[N];
int n;
long long dp[6];
long long sum,ans;
int main()
{
	int i,j;
	cin>>(x+1);
	n=strlen(x+1);
	for(i=1; i<=n; i++)
	{
		if(x[i]=='b')
			dp[1]++;
		else if(x[i]=='e')
			dp[2]+=dp[1],ans+=dp[5];
		else if(x[i]=='s')
			dp[4]+=dp[3],dp[3]+=dp[2];
		else if(x[i]=='i')
			dp[5]+=dp[4];
	}
	cout<<ans;
	return 0;
}
```
### 子问题 2

在完成子问题 1 的情况下，我们可以吧问题变的复杂一点，变成求出含有 ```bessie``` 的字串的数量。

其实很简单，在当 $dp_i=dp_{i-1}+dp_i$ 转移时，把 $dp_{i-1}$ 清空就行了。

之后每次加上 $dp_6$ 就行了。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N=3e5+5;
char x[N];
int n;
long long dp[10];
long long sum,ans;
int main()
{
	int i,j;
	cin>>(x+1);
	n=strlen(x+1);
	for(i=1; i<=n; i++)
	{
		dp[0]++;
		if(x[i]=='b')
			dp[1]+=dp[0],dp[0]=0;
		else if(x[i]=='e')
			dp[2]+=dp[1],dp[1]=0,dp[6]+=dp[5],dp[5]=0;
		else if(x[i]=='s')
			dp[4]+=dp[3],dp[3]=dp[2],dp[2]=0;
		else if(x[i]=='i')
			dp[5]+=dp[4],dp[4]=0;
        sum+=dp[6];
	}
	cout<<sum;
	return 0;
}
```
### 最终问题

解决完子问题 2 之后，我们就要考虑一下对于字串之中 ```bessie``` 含量不同而导致的价值不同问题。

看起来这个问题很难，不过我们发现把 $dp$ 数组循环起来就可以，这种做法不改变价值但是把通过复制的方法变相增加价值。

### AC CODE
```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N=3e5+5;
char x[N];
int n;
long long dp[6];
long long sum,ans;
int main()
{
	int i,j;
	cin>>(x+1);
	n=strlen(x+1);
	for(i=1; i<=n; i++)
	{
		dp[0]++;
		if(x[i]=='b')
			dp[1]+=dp[0],dp[0]=0;
		else if(x[i]=='e')
			dp[2]+=dp[1],dp[1]=0,dp[0]+=dp[5],sum+=dp[5],dp[5]=0;
		else if(x[i]=='s')
			dp[4]+=dp[3],dp[3]=dp[2],dp[2]=0;
		else if(x[i]=='i')
			dp[5]+=dp[4],dp[4]=0;
		ans+=sum;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：slzx2021zjx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9188)

#### 题目大意
求出在一个字符串中，所有子串中直接或间接出现 ```bessie``` 的总和。
#### 思路
先用 $f[i]$ 记录到 $s[i]$ 时，前面离它最近的“b”所在的下标。
即 $f[6]$ 可以表示此时前面离他最近直接或间接出现 ```bessie``` 的首字母。
再用 $dp[i]$ 表示以 $i$ 结尾的答案。
那么可列出转移方程 ```dp[i]=dp[f[6]-1]+f[6]```。

最终答案是
$ \sum_{i=1}^{n} dp[i]$。

###### CODE
```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
int f[10],ans,dp[300005];
string s;
signed main()
{
	cin>>s;
	s=' '+s;
	for(int i=1;i<s.size();i++){
		if(s[i]=='b') f[1]=i;
		if(s[i]=='e') f[6]=f[5],f[2]=f[1];
		if(s[i]=='s') f[4]=f[3],f[3]=f[2];
		if(s[i]=='i') f[5]=f[4];
		dp[i]=dp[f[6]-1]+f[6];
	}
	for(int i=1;i<s.size();i++) ans+=dp[i];
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：lianchanghua (赞：1)

#### 题目大意

当你获得一个字符串的时候，你会数一数这个字符串中最多有多少 `bessie`。你会保留这个字符串的一个子序列，满足这个子序列形如若干个 `bessie` 拼接起来。当你获得一个序列的时候，你会计算这个序列所有子串中最多 `bessie` 个数之和。

#### 粗略的思路（老师的题解）

首先我们应该考虑 $B$ 函数怎么求，只需要对这个序列从左往右扫，不断匹配 `bessie` 这个子串，最后统计有匹配出几个即可。

考虑根据这个匹配过程 $dp$，设 $dp_{i,j}$ 表示到了第 $i$ 个位置，匹配到第 $j$ 个字母的左端点个数，则当匹配

完一个 `bessie` 的时候，就可以算贡献，这个贡献对于每个右端点都成立。时间复杂度 $O(n)$。

#### 详细的思路（自己的理解）

很明显，这是一个动态规划。

首先，我们可以将这个 `bessie` 拆分出来，分别为：`b`，`be`，`bes`，`bess`，`bessi`，`bessie`。

考虑 $dp_i$ 为 右端点为 $i$ 处 的所有子串包含 `bessie` 的答案总和。

具体如何计算 $dp_j$ 呢？

加入从 $i$ 往前找到最近的一个 $j$，使得 $j+1$ 到 $i$ 的区间恰好包含了一个 `bessie` 子序列，那么 $dp_i = dp_j + j$，因此右端点从 $j$ 处拉到 $i$ 处，原来包含的 `bessie` 依然被包含，而对于右端点，当左端点落在 $1$ 到 $j$ 时，会额外多包含刚刚发现的一个 `bessie` 子序列。

考虑下我们的 $dp$ 数组。$dp_1$ 表示，字符串 `b` 离我们当前位置最近的位置，每当遇到字符 `b` 时，就更新。$dp_2$ 表示，字符串 `be` 离我们当前位置最近的位置，每当遇到字符 `be` 时，就更新。$dp_3$ 表示，字符串 `bes` 离我们当前位置最近的位置，每当遇到字符 `bes` 时，就更新。$dp_4$ 表示，字符串 `bess` 离我们当前位置最近的位置，每当遇到字符 `bess` 时，就更新。$dp_5$ 表示，字符串 `bessi` 离我们当前位置最近的位置，每当遇到字符 `bessi` 时，就更新。$dp_6$ 表示，字符串 `bessie` 离我们当前位置最近的位置，每当遇到字符 `b` 时，就更新。


最后的答案为 $\sum_{i=1}^{n}{dp_i}$

#### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int f[15],ans;
char c[N];
signed main(){
//	freopen("bessie.in","r",stdin);
//	freopen("bessie.out","w",stdout);
	cin>>(c+1);
	int n=strlen(c+1);
	for(int i=1;i<=n;i++){
        f[0]++;
        if(c[i]=='b') 		f[1]+=f[0],f[0]=0;
        else if(c[i]=='e') 	f[2]+=f[1],f[1]=0,f[0]+=f[5],ans+=f[5]*(n-i+1),f[5]=0;
        else if(c[i]=='s') 	f[4]+=f[3],f[3]=f[2],f[2]=0;
        else if(c[i]=='i') 	f[5]+=f[4],f[4]=0;
    }
    cout<<ans;
	return 0;
}

```

---

## 作者：muyangli (赞：0)

# P9188 [USACO23OPEN] Pareidolia S

## 题目描述

定义 $B(str)$ 为在一个字符串里能通过删除字符得到最多的连续 `bessie` 串（即形如 `bessiebessie......bessie` 的串）中，`bessie` 子串的个数。求一个字符串的所有子串的 $B$ 函数之和。

## 分析

前五个点的做法和正解无甚关系，直接考虑正解。

考虑动态规划。很容易想到令 `dp[i]` 表示以字符串第 $i$ 位结尾的子串中 $B$ 函数之和。难点在于转移。我们发现，若令 $B$ 函数计算的序列为 $B$ 序列，则 `dp[i]` 的答案中 $B$ 序列的最后一个 `bessie` 中的 `b` 的位置之前的部分已经计算过了。设其位置为 $pos$。则 `dp[pos - 1]` 即为那一部分。以 `pos - 1` 为结尾的子串有 `pos - 1` 个，为最后一个 `bessie` 产生的贡献的贡献为 `pos - 1`，加上 `pos` 开头 `i` 结尾的子串产生的一次贡献。得出转移方程为：

$$
dp[i] = dp[pos - 1] + pos
$$

如何处理最后一个 `bessie` 的 `b` 的位置呢？我们可以像滚动数组一样处理。具体见下方代码：

```cpp
int pos[7];// 记录 第一个 b 出现的位置

...

if(s[i] == 'b') pos[1] = i + 1;// 找到 b，记录其位置
else if(s[i] == 'e') pos[2] = pos[1], pos[6] = pos[5];// 找到 e，和 b 与 i 组成 be 和 bessie
else if(s[i] == 's') pos[4] = pos[3], pos[3] = pos[2];// 找到 s，同理组成 bess 和 bes
else if(s[i] == 'i') pos[5] = pos[4];// 找到 i，组成 bessi

...

```

`pos[i]` 存储 `bessie` 的前 $i$ 位串最后一次出现的首位位置。每当找到一个其中的字符，就将其前驱存储的前缀的首位位置传递下来，这样 `pos[6]` 存储的就是最后一个 `bessie` 的首字母位置。

## 完整代码

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <cstdio>
#define int __int128
#define rd() read128()
#define pr(a) print128(a)
#define pc(b) putchar(b)
#define pel(c) pr(c), pc('\n')
#define psp(d) pr(d), pc(' ')
using namespace std;
int read128()
{
	int ttpttp = 0, flgflg = 1;
	char chrchr = getchar();
	if(chrchr == '-') flgflg = -1;
	while((chrchr < '0' || chrchr > '9') && chrchr != '-') chrchr = getchar();
	if(chrchr == '-') flgflg = -1, chrchr = getchar();
	while(chrchr >= '0' && chrchr <= '9') ttpttp = ttpttp * 10 + chrchr - '0', chrchr = getchar();
	return ttpttp * flgflg;
}
void print128(int ttpttp)
{
	char char_inserted_list[38];
	if(ttpttp < 0) putchar('-'), ttpttp *= -1;
	int iiiiii = 0;
	while(ttpttp > 0)
	{
		char_inserted_list[++iiiiii] = (char)(ttpttp % 10 + '0');
		ttpttp /= 10;
	}
    if(iiiiii == 0) putchar('0');
    else
    {
    	for(int i = iiiiii; i >= 1; i--) putchar(char_inserted_list[i]);
	}
}
int pos[7];// 记录 第一个 b 出现的位置
int dp[300010];// 表示以 i 结尾的子串里 B(i) 的和
signed main()
{
	string s;
	cin >> s;
	int sm = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] == 'b') pos[1] = i + 1;// 找到 b，记录其位置
		else if(s[i] == 'e') pos[2] = pos[1], pos[6] = pos[5];// 找到 e，和 b 与 i 组成 be 和 bessie
		else if(s[i] == 's') pos[4] = pos[3], pos[3] = pos[2];// 找到 s，同理组成 bess 和 bes
		else if(s[i] == 'i') pos[5] = pos[4];// 找到 i，组成 bessi
		if(pos[6] == 0) dp[i + 1] = 0;
		else dp[i + 1] = dp[pos[6] - 1] + pos[6];
		sm += dp[i + 1];
	}
	pr(sm);
	return 0;
}
```

---

## 作者：内拉组里 (赞：0)

一道 dp 水题。

# Thoughts :

选择枚举右端点对左端点进行计数。

令 $ dp_i $ 表示所有以 $ i $ 为右端点的子串 $ s^\prime $ 的 $ \sum B(s^\prime) $。

转移 $ dp_i = dp_{j - 1} + j $。

其中 $ j $ 表示在 $ i $ 之前最后一个完整的 "$ \texttt{bessie} $" 的首字母的位置。

现在问题在于如何求解 $ j $。

新开一个数组，令 $ idx_i $ 表示第 $ i $ 个字母成功与 "$ \texttt{bessie} $" 匹配的最后一个母串的首字母的位置。

$ idx_6 $ 即所求的 $ j $。	

转移也非常简单，在模式串匹配处转移即可。

最后的答案即 $ \sum dp_i $。

# Analyses :

> 总时间复杂度 $ \Theta (N) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Code :

```cpp
/* reference : @Luogu.Nuyoah_awa (551108) */
#include	<iostream>
#include	<cstring>
#define		int		long long
using namespace std;
constexpr int maxn = 3e5+4;

int idx[10];
int dp[maxn];
char s[maxn] = "bessie";

signed main (void)
{
	cin >> s + 1;
	int n = strlen (s + 1);
	for (int i = 1; i <= n; i++)
	{
		switch (s[i])
		{
			case 'b':
				idx[1] = i;
				break;
			case 'e':
				idx[2] = idx[1];
				idx[6] = idx[5];
				break;
			case 's':
				idx[4] = idx[3];
				idx[3] = idx[2];
				break;
			case 'i':
				idx[5] = idx[4];
				break;
		}
		dp[i] = dp[idx[6] - 1] + idx[6];
//		cerr << ">>>> " << s[i] << ' ';
//		for (int i = 1; i <= 6; i++) cerr << idx[i] << ' ';
//		cerr << endl;
	}
	for (int i = 1; i <= n; i++) dp[i] += dp[i - 1];
	cout << dp[n] << endl;
	return 0;
}
```

---

## 作者：JOKER_chu (赞：0)

**大家好像做法都是一样的吧。~~(蒻)~~**

我觉得这个只能评个黄啊，这题的 `dp` 简单。

`dp[i]` 表示第 $i$ 个位置贝西最多出现次数，显而易见的，最终答案为最后一位，也就是 $e$ 的 `dp` 记录，这里就要辅助一个数组 `cnt` 来记录上一个字母存在的位置，当出现一个字母时，我们考虑它**前一个**字母的位置，当我们统计到一个完整的 `bessie` 时，更新 `dp` 数组，这时需要分类讨论，如果这 $1$ 次没有找到，我们的 `dp[i]` 应是**上一个 `bessie` 出现时的 `dp`数组，也就是 `dp[cnt[6]]` ，而不是等于 $0$ ，没找到不代表没有，等于 $0$ 前面会被忽略。** 第 $2$ 种就是这次循环找到了，那就是上一次的 `dp` 数组加上当前找到单词最后 $1$ 个字母的坐标，因为可能找到了**不止 $1$ 个**新的贝西。最后发现可以合成为 $1$ 行。注意，这个问题问的是所有**区间之和**，最后输出 `dp[6]` 的会错，应当去统计整个 `dp` 数组的和。

### 接下来是代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int hutao = 3e5 + 5;

string a;
int ans, dp[hutao], cnt[7]; 

signed main(){
	cin >> a;
	for(int i = 0; i < a.size(); i++){
		if(a[i] == 'b'){
			cnt[1] = i + 1; // 记录最接近的 b 的位置 
		}else if(a[i] == 'e'){
			cnt[2] = cnt[1]; // 注意这里都要更新，可以是后面的也可以是前面的，因为出现了两个 e 
			cnt[6] = cnt[5];
		}else if(a[i] == 's'){
			cnt[4] = cnt[3]; // 同上所述 
			cnt[3] = cnt[2];
		}else if(a[i] == 'i'){
			cnt[5] = cnt[4];
		}
		dp[i] = dp[cnt[6] - 1] + cnt[6]; // 合并，找到了和没找到都加上 
		ans += dp[i]; // 统计答案 
	}
	cout << ans;
	return 0;
}
```

最后：请注意 `long long` 问题

~~完~~

---

## 作者：Loser_Syx (赞：0)

考虑 dp。

由于要凑出 `bessie` 这个字符串，所以我们可以定义一个 $last$ 数组，$last_i$ 表示离他最近的 `b` 且从这个下标开始到 $i$ 的其中一个子串可以凑出 $bessie_1 \sim bessie_i$。

对于每个 $s_i$，直接对于其种类，更新 $last$ 数组即可。

然后对于每个 $dp_i$，发现至少存在 $dp_{last_6-1}$ 种方案，还会多出 $last_6$ 种方案，因为对于 $j \in [1,last_6]$，$s_j \sim s_i$ 是肯定能拼出一个 `bessie` 来的。故转移方程为 $dp_i = dp_{last_6-1} + last_6$。


```cpp
int dp[301010], lastb[10];
signed main() {
	//freopen("data.in", "r", stdin);
	string s;
	cin >> s;
	int len = s.size(), ans = 0;
	for (int i = 0; i < len; ++i) {
		if (s[i] == 'b') lastb[1] = i+1; // 懒得 s = " " + s 了，干脆下标直接加 1（（（
		else if (s[i] == 'e') {
			lastb[2] = lastb[1];
			lastb[6] = lastb[5];
		} else if (s[i] == 's') {
			lastb[4] = lastb[3];
			lastb[3] = lastb[2];
		} else if (s[i] == 'i') {
			lastb[5] = lastb[4];
		}
		if (lastb[6] != 0) dp[i+1] = dp[lastb[6]-1] + lastb[6];
		ans += dp[i+1];
	}
	write(ans, '\n');
	return 0;
}
```

---

