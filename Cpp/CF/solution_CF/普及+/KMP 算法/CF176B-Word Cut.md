# Word Cut

## 题目描述

Let's consider one interesting word game. In this game you should transform one word into another through special operations.

Let's say we have word $ w $ , let's split this word into two non-empty parts $ x $ and $ y $ so, that $ w=xy $ . A split operation is transforming word $ w=xy $ into word $ u=yx $ . For example, a split operation can transform word "wordcut" into word "cutword".

You are given two words $ start $ and $ end $ . Count in how many ways we can transform word $ start $ into word $ end $ , if we apply exactly $ k $ split operations consecutively to word $ start $ .

Two ways are considered different if the sequences of applied operations differ. Two operation sequences are different if exists such number $ i $ ( $ 1<=i<=k $ ), that in the $ i $ -th operation of the first sequence the word splits into parts $ x $ and $ y $ , in the $ i $ -th operation of the second sequence the word splits into parts $ a $ and $ b $ , and additionally $ x≠a $ holds.

## 说明/提示

The sought way in the first sample is:

ab $ → $ a|b $ → $ ba $ → $ b|a $ → $ ab

In the second sample the two sought ways are:

- ababab $ → $ abab|ab $ → $ ababab
- ababab $ → $ ab|abab $ → $ ababab

## 样例 #1

### 输入

```
ab
ab
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
ababab
ababab
1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
ab
ba
2
```

### 输出

```
0
```

# 题解

## 作者：ylxmf2005 (赞：13)

### Description

求经过 $k$ 次将 $S$ 划分成两部分并交换使 $S$ 串变成 $T$ 串的方案数并对 $10^9 + 7$ 取模。

$2 \leq |S| \leq 1000, 0 \leq k \leq 10^5$

### Solution

可以发现，只要能从一个串变成一个串，都可以**通过仅一次变换**得到，所以先预处理出一个 $cnt$ 来表示 $S$ 通过一次变换有多少个位置可以得到 $T$。暴力和 kmp 都可以，由于数据范围不大所以选择前者。

令 $f_{i,0}$ 为经过 $i$ 次变换所产生的原串个数，$f_{i,1}$ 为产生其它串的个数。因为最后要得到 $T$，我们把 $T$ 看作原串。那么转移要考虑原串变原串，原串变其它串，其它串变其它串，其它串变原串。

- 得到原串的情况：$f_{i-1,1}$ 个其它串中，每个其它串可以通过一次变换得到 $cnt$ 个原串。$f_{i-1,0}$ 个原串中，每个原串通过一次变换得到**除了自己以外**的 $cnt - 1$ 个原串。如果算上自己的话，相当于没变换所以不合法。

- 得到其它串的情况：$f_{i-1,0}$ 个原串中，每个原串可以通过一次变换得到 $|S| - cnt$ 个其他串。$f_{i-1,1}$ 个其他串中，每个其他串可以通过一次变换得到除了自己以外的 $|S| - cnt - 1$ 个其他串。



综上所述，转移方程如下

$$f_{0,s \not=t} = 1$$

$$f_{i,0} = cnt \times f_{i-1,1} + (cnt - 1) \times f_{i-1,0}$$

$$f_{i,1} = (|S| - cnt) \times f_{i-1,0} + (|S| - cnt - 1) \times f_{i-1,1}$$ 

$$ans  =f_{k,0}$$

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, p = 1e9 + 7;
char s[N], t[N];
ll f[N][2];
int n, k, cnt;  
bool check(int l, int r) {
	int j = 0;
	for (int i = l; i <= r; i++) if (s[i] != t[++j]) return 0;
	return 1;
}
int main() {
	scanf("%s%s%d", s + 1, t + 1, &k); 
	n = strlen(s + 1); 
	for (int i = 1; i <= n; i++) s[i + n] = s[i];
	for (int i = 1; i <= n; i++) if (check(i, i + n - 1)) cnt++;
	f[0][!check(1, n)] = 1;
	for (int i = 1; i <= k; i++) {
		f[i][0] = (cnt * f[i - 1][1] % p + (cnt - 1) * f[i - 1][0] % p) % p;
		f[i][1] = ((n - cnt) * f[i - 1][0] % p + (n - cnt - 1) * f[i - 1][1] % p) % p;
	}
	printf("%lld\n", f[k][0]);
	return 0;
} 
```

---

## 作者：pitiless0514 (赞：5)

#### 简述题意：
有两个字符串$a$,$b$，长度均$≤1000$个字符，把字符串$a$从任意一个地方截取，然后交换这两部分位置得到新的字符串，对它进行$k$次操作，问最后变到$b$串时的方法有多少种。
 $0<=k<=10^5$

------------
当我看到此题的标签时，阿勒？绿题，~~就这啊？~~ 但当我仔细想了一想此题，啪啪啪打脸，可能也是因为我太弱了，QAQ，看了 **@FP·荷兰猪大佬 @Mickey_snow等大佬** 的题解才写出来，本篇题解主要是对他们的题解进行蒟蒻式的说明，不喜勿喷。

------------
首先我们可以发现一个串进行变换的话，他是可以有$Len$(字符串的长度)种变换方式的。
#### 举个栗子：$ABC$字符串，它的变换方法有$ABC-CAB-CBA$三种方法，也就是他的长度。而且一个串变换到另一个串只需要一步，那么我们可以考虑预处理出一个x，表示一个字符串变换中有多少个目标串。看代码：
```cpp
	for(int i=1;i<=len;i++){ 
		if(check(i,i+len-1)){ //一个字符串的长度
			x++;
		}
	}
```
在这里大家会注意到一件事，我们在查找时，最大长度是$len+len-1$，这个是怎么回事呢？还是举原先的例子：
**$ABC$**当我们把他长度扩充两倍后，他就会变成**$ABCABC$**，我们在$(i,i+len-1)$的式子看一下，阿勒，$ABC-BCA-CAB$这不就是我们要找的拆分方法吗？真是妙啊！于是：
```cpp
    int len=strlen(a+1);
    for(int i=1;i<=len;i++){
    	a[i+len]=a[i];
	}
```
那么现在还有一个$check$函数的问题，这个$check$函数就很好解释，它就是把我们选出来的这一段字符串与字符串b去比较，看看如果一样，那么$x++$；
```cpp
bool check(int l,int r){
	int p=0;
	for(int i=l;i<=r;i++){
		if(a[i]!=b[++p]){
			return 0;
		}
	}
	return 1;
}
```


------------
### 接下来就是正题了：
#### 我们在经历了以上的分析后，我们再看一看题目，发现这是一道计数dp，那么接下来开始设置状态$f[i][1/0]$
1. $f[i][0]$表示的是在经过i次变换后，产生的原串个数，于此同时我们把字符串b给设置为原串。

2. $f[i][1]$表示的是经过i次变换后产生的其他串个数


分析：
1. $f[i][0]=f[i-1][1]*x+(x-1)*f[i-1][0]$

首先我们知道一个串在变换时，可以一次变换出x个原串，所以在$f[i-1][1]$个其他串中，每个串时可以转换出x个原串的，也就是$f[i-1][1]*x$个原串。其次，在$f[i-1][0]$个原串中，他们变换也是可以继续变换出原串的，那么，又因为**他们本身是一个原串**，所以变换出来的是**除他以外的**$x-1$个原串，所以$f[i][0]=f[i-1][1]*x+(x-1)*f[i-1][0]$

2.$f[i][1]=f[i-1][0]*(len-x)+f[i-1][1]*(len-x-1)$

在这里我们先前说了一个串的变换可以得到$len$个串，那么每个原串就可以变换出$len-x$个其他串也就是$f[i-1][0]*(len-x)$，而在$f[i-1][1]$个其他串中他们通过一次变换得到的是除自己以外的$len-x-1$个其他串。所以$f[i][1]=f[i-1][0]*(len-x)+f[i-1][1]*(len-x-1)$。

### 建议大家多看一下。有点难理解。
这一段的代码就是：
```cpp
for(int i=1;i<=k;i++){
    	f[i][0]=f[i-1][1]*x+(x-1)*f[i-1][0];
    	f[i][1]=f[i-1][0]*(len-x)+f[i-1][1]*(len-x-1);
	    f[i][0]=(f[i][0]+P)%P;
	    f[i][1]=(f[i][1]+P)%P;//取模惯用招数，不管是否为负数，先加一个模数，反正后面再%一次，是没有影响的
	}
```
然后就是初始化的问题，我们看下面：
```cpp
if(check(1,len)) f[0][0]=1;//如果a字符串本来就等于b字符串，那么它不用转移，就可以有一个原串
	else f[0][1]=1;//如果不是，那么它在不用转移时，就可以有一个其他串。
```
那么基本就差不多了，放AC代码，甚至你还可以在我的基础上加个O2，O3优化，那你就可以是rank2了
```cpp
#include<bits/stdc++.h>
using namespace std;
#define P 1000000007 //等同于P=1000000007
long long k,f[100005][3];//开个long long,防止见ZZ
char a[3005],b[1005];
bool check(int l,int r){
	int p=0;
	for(int i=l;i<=r;i++){
		if(a[i]!=b[++p]){//判断
			return 0;
		}
	}
	return 1;
}
int main(){
    scanf("%s%s%lld",a+1,b+1,&k);//加1方便计算
    int len=strlen(a+1);
    for(int i=1;i<=len;i++){
    	a[i+len]=a[i];
	}
    int x=0; 
	for(int i=1;i<=len;i++){
		if(check(i,i+len-1)){
			x++;
		}
	}
	if(check(1,len)) f[0][0]=1;
	else f[0][1]=1;
    for(int i=1;i<=k;i++){
    	f[i][0]=f[i-1][1]*x+(x-1)*f[i-1][0];
    	f[i][1]=f[i-1][0]*(len-x)+f[i-1][1]*(len-x-1);
	    f[i][0]=(f[i][0]+P)%P;
	    f[i][1]=(f[i][1]+P)%P;
	}
	cout<<f[k][0]%P;//最后答案就是第k次转换时的原串个数
	return 0;
} 
```
点个赞罗$QAQ$

$upd:$于$2020.1.24$加上$Latex$

---

## 作者：FP·荷兰猪 (赞：4)

> 题意：定义一轮操作：对于一个串，从任意地方截断，然后把两部分位置交换得到新的串。

> 对于a串一共进行k轮这种操作。

> 问从a串变到b串有多少种方法。

~~竟然没有人发C++题解233~~

**DP！**

其实每一次变换，只是把数组str，从str[i]输出而已

循环构成条件：守恒的操作或者是可以确定状态的变换

先掌握变换的本质,先掌握变换的本质啊！！！！

详见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
char a[1002<<1],b[1002];
long long dp[100003][2];
int main()
{
    int k,x=0,len,i;
    cin>>a>>b>>k;
    len=strlen(a);
    dp[0][strcmp(a,b)!=0]=1;
    for(i=0;i<len;i++)
    {
        a[i+len]=a[i];
    }
    for(i=0;i<len;i++)
    {
    	if(strncmp(a+i,b,len)==0)
        {
            x++;
        }
    }
    for(i=0;i<k;i++)
    {
        dp[i+1][0]=(x*dp[i][1]+(x-1)*dp[i][0])%mod;
        dp[i+1][1]=((len-x)*dp[i][0]+(len-x-1)*dp[i][1])%mod;
    }
    cout<<dp[k][0]<<endl;
    return 0;
}
```

---

## 作者：Mickey_snow (赞：3)

[CF176B](http://codeforces.com/contest/176/problem/B)  _Word Cut_ : 递推。

题目大致意思：给你两个字符串 $s$ 和 $t$ ,你一次操作可以将 $s$ 分为两部分，交换这两部分的位置，你要恰好执行 $k$ 次这样的操作，使得 $s$ 变为 $t$ ,有多少种不同的方法？只要中间有一步不同就视为两种不同的方法。

我们需要知道，这个所谓的操作是不会从根本上打乱串 $s$ 的，如果将 $s$ 看成是一个字符首尾相连圆圈，那么执行一次这样的操作就是将这个圆圈旋转了一下，并没有打乱字符之间的位置关系。

如果 $s$ 与 $t$ 的长度不想等，那么答案就是0，在这里我们假设它们长度一样。

首先，我们先找一下有多少个点 $k$ ，在这里切开 $s$ 之后可以得到 $t$ ，记这些点的总数量为 $cnt$ .这一步如果暴力匹配，时间复杂度最坏可能逼近 $O(N^2)$ ，但是应对大部分数据已经足够。当然，应该也可以用 KMP, 将 $s$ 与 $s + s$ 匹配一下，时间复杂度可以降到 $O(N \times 2)$ .保险起见我没有这么做。

之后开始递推，假设 $D[i]$ 是 执行了 $i$ 次操作之后的情况，$D[i,0]$  代表与 $t$ 相等的方案数，$D[i,1]$ 代表与 $t$ 不等的方案数，那么转移如下：

```cpp
	D[now, 0] = (D[last, 0] * (cutPoints - 1) % mod + D[last, 1] * cutPoints % mod) % mod;
	D[now, 1] = (D[last, 0] * (len - cutPoints) % mod + D[last, 1] * (len - cutPoints - 1) % mod) % mod;
```

1. 与 $t$ 相同，可以由上一步已经相同的选择一个未被选择的点 $k$ ，也可以由上一步不一样的任意选择一个 $k$ 得到。
2. 与 $t$ 不同，可以由上一步已经相同的选择一个不是 $k$ 的点，也可以由上一步不一样的任意选择一个不是 $k$ 的点得到

最终的答案，就是

```c#
	D[totOptns, 0] %= mod;
```

由于每一次转移只使用到了上一次的值，所以 $D$ 数组可以滚动，空间复杂度为 $O(1)$ .

完整的程序如下：

```c#
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace CF176B
{
	class Program 
	{
		public class Global {
			public static string fr, to;
		}

		static void Main(string[] args) 
		{
			Global.fr = Console.ReadLine();Global.to = Console.ReadLine();
			if(Global.fr.Length != Global.to.Length) { Console.WriteLine("0");return; }

			int totChanges = Convert.ToInt32(Console.ReadLine()), mod = 1000000007;
			Int64[,] D;

			D = new Int64[2, 2];

			int now = 0, last = 1, cutPoints = Solve(), len = Global.to.Length;
			if(Global.fr == Global.to) { D[now, 0] = 1; D[now, 1] = 0; } 
			else { D[now, 0] = 0; D[now, 1] = 1;}

			for(int i = 0; i < totChanges; i++) {
				now ^= last;last ^= now;now ^= last;

				D[now, 0] = (D[last, 0] * (cutPoints - 1) % mod + D[last, 1] * cutPoints % mod) % mod;
				D[now, 1] = (D[last, 0] * (len - cutPoints) % mod + D[last, 1] * (len - cutPoints - 1) % mod) % mod;
			}

			D[now, 0] %= mod;
			Console.WriteLine(D[now, 0].ToString());
		}

		static int Solve() {
			int cnt = 0;
			for(int i = 0; i < Global.fr.Length; i++) if(Solve(i)) { cnt++; }
			return cnt;
		}
		static bool Solve(int Pos) {
			for(int i = Pos; i < Global.fr.Length; i++)
				if(Global.fr[i] != Global.to[i - Pos]) return false;
			for(int i = 0; i < Pos; i++)
				if(Global.fr[i] != Global.to[i + Global.to.Length - Pos]) return false;
			return true;
		}
	}
}

```



---

## 作者：hhhqx (赞：1)

没看懂其他题解为什么说 "可以发现，只要能从一个串变成一个串，都可以通过仅一次变换得到"。

# 转化

将题目中的操作转化一下：对于一个串 $s$，将串 $s$ 复制一份接到 $s$ 末尾，然后选择一段长度 $n
$ 的子串。

发现：经过一次操作后，接下来的操作**任然是** 在原 $s$ 复制后的串中选择一个长度 $n$ 的子串。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/u7imorla.png)

第一个字符串中红色区间表示选择的子串。原 $s$ 复制后的串，不妨将其分为四段 $s_1+s_2+s_1+s_2$。

第一次操作后得到的串 $t$，发现其任然可以分为四段 $s_2+s_1+s_2+s_1$。

容易看出在 $t$ 中选择一个长度为 $n$ 的子串等价于在 $s$ 中选择一个长度为 $n$ 的子串。

所以：题目中的 $a$ 通过多次操作得到的串，这个串通过一步变为 $b$ 的操作种类数，是固定的，我们不妨直接求出 $a$ 可以通过几种操作得到 $b$，记为 $cnt$。

# 解法
$cnt$ 可以直接求。

然后考虑 dp。$f_{i,0/1}$ 表示经过 $i$ 次操作，当前字符串是 原串 还是 非原串，的操作种类数。

具体转移可以去看其他题解，例如这位大佬的：https://www.luogu.com.cn/article/84ns8qcl 。

# Code
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const LL mod = 1e9 + 7;
const int MAXK = 1e5 + 3;

string a, b;
int k, cnt = 0;
LL f[MAXK][2];

int main(){
	cin >> a >> b >> k;
	if(a == b) cnt++;
	for(int i = 0; i < a.size() - 1; i++){
		string t = a.substr(i + 1, a.size()-i-1) + a.substr(0, i+1);
		if(t == b) cnt++;
	}
	f[0][(a == b ? 0 : 1)] = 1;
	for(int i = 1; i <= k; i++){
		f[i][0] = 1ll * cnt * f[i - 1][1] % mod + 1ll * (cnt - 1) * f[i - 1][0] % mod;
		f[i][0] %= mod;

		f[i][1] = 1ll * (a.size() - cnt) * f[i - 1][0] + 1ll * (a.size() - cnt - 1) * f[i - 1][1] % mod;
		f[i][1] %= mod;
	}
	cout << f[k][0];
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：1)

~~我怎么这么菜呀！！！~~

------------
今天下午，本着一道水题的心情来~~被这道题切~~切这道难题，本以为很快就可以用 KMP 水掉这道题，结果正好跳了出题人的陷阱，硬是想了三个小时，一点眉目都没有。后来看了看[大佬题解](https://www.cnblogs.com/NaVi-Awson/p/8667818.html)的解法，瞬间~~愁眉不展~~有所变化，便心血来潮，写出来这道题，并写出了这篇题解。

------------
## 大致思路：
字符串题目是各大 OJ 上老生常谈的题目，而这道题要我们实现的是**将一个字符串切成两段并进行交换**的操作来将 $s$ 字符串改成 $t$ 字符串，按道理来说，字符串题大部分可以用 dp 和 KMP 来做，而这道题用 dp 显然是更优的。

首先，我们定义 $dp[i][j]$ 为在操作 $i$ 次后在第 $j$ 位砍断的方法数。根据我们之前学过的组合数学的知识可以知道，这种情况的转移要从 $i - 1$ 的所有不等于 $j$ 的位置中获取答案（因为 dp **具有子问题重叠性的性质**，那么到了第 $i$ 次操作时想要得到的种数就可以将前面的各个操作的种类数求和，同时**记得取模**）。

但是，如果仅仅这样做，时间复杂度肯定会超时（因为 dp 的时间复杂度为 $O(n ^ {2})$）。同时我们可以发现：在有些地方执行操作得到的字符串得到的新字符串与 $t$ 串**本质相同**。那么，我们就可以定义一个变量 $same$ 来存储有多少个位置砍断后与 $t$ 串本质相同，计算完 $same$ 后我们就可以在转移的时候直接减去 $same$ 来剔除重复的操作。这样就可以减少大量时间复杂度~~同时练习一下搜索~~。

在做 dp 之前，我们要判断当在 $1$ 的位置是否会在切割之后是否还是和 $t$ 字符串本质一样，因为在后面的循环中我们不会在关注前面的情况，而是直接调用，因此**要预处理好**。

至于状态转移方程，我们在前面已经说过，要在转移的同时减去重复情况，还要直接用 $same$ 函数的处理结果减去 $1$ 来实现**具有组合数学性质的转移**，说白了就是在一个点**已经确定的同时将原来的结果直接乘上去**，因此转移方程如下：

$dp[i][0] = (dp[i - 1][0] \times (same - 1) \bmod modd  + dp[i - 1][1] \times same \bmod modd) \bmod modd$。

还有，我们要知道，我们要**考虑不在这个点放的情况**，所以就要和上面的情况反过来，同理：

$dp[i][1] = (dp[i - 1][0] \times (len - same) \bmod modd + dp[i - 1][1] \times (len - same - 1) \bmod modd) \bmod modd$。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000, modd = 1e9 + 7;
char s[N + 5], t[N + 5];
int same, len, dp[N * 100 + 5][2], k;
bool check(int x)
{
    for (int i = 1; i <= len; i++)
    {
        if (s[x] != t[i])
        {
            return false;
        }
        x++;
        if (x > len)
        {
            x = 1;
        }
    }
    return true;
}
signed main()
{
    scanf("%s%s", s + 1, t + 1);
    len = strlen(s + 1);
    cin >> k;
    for (int i = 1; i <= len; i++)
    {
        if (check(i))
        {
            same++;
        }
    }
    if (check(1))
    {
        dp[0][0] = 1;
    }
    else
    {
        dp[0][1] = 1;
    }
    for (int i = 1; i <= k; i++)
    {
        dp[i][0] = (dp[i - 1][0] * (same - 1) % modd + dp[i - 1][1] * same % modd) % modd;
        dp[i][1] = (dp[i - 1][0] * (len - same) % modd + dp[i - 1][1] * (len - same - 1) % modd) % modd;
    }
    cout << dp[k][0];
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121203141)


---

## 作者：Kketchup (赞：0)

## CF176B Word Cut

- 字符串
- DP

【题意】

给定一个长度为 $n\le 1000$ 的字符串，再给定一个长度相等的目标串和**非负**整数 $k\le 10^5$，请问是否可以使用正好 $k$ 次操作，将原串变成目标串。

每一次操作选择一个位置 $p\in[1,n)$，然后将字符串变成 $[p+1,n]+[1,p]$。其中 $+$ 表示连接。

求操作方案数，取模。两个方案不同当且仅当至少有一步 $p$ 的选择不同。

【解析】

一个非常重要的结论：如果一次操作不行的话，那一定不行。

推广一下，也就是说做任意多次操作以后只需要做 $1$ 次操作就可以变成想要的样子。

所以我们可以先暴力求出一次操作能满足条件的方案数，记为 $\text{cnt}$。

则考虑 DP，设 $f_i$ 表示第 $i$ 步变成目标串的方案数，$g_i$ 表示第 $i$ 步没变成目标串的方案数。

推出转移方程 $f_i=cnt\times g_{i-1}+(cnt-1)\times f_{i-1}$。表示有 $\text{cnt}$ 种方式从上一个的任意非目标串状态变成目标串状态，$\text{cnt-1}$ 种方式从上一个的目标串再操作一次还是目标串。

类似地，$g_i=(n-cnt)\times f_{i-1}+(n-cnt-1)\times g_{i-1}$。

答案是 $f_k$，初始状态就是看看原串和目标串是否一样，是则 $f_0=1$，否则 $g_0=1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define Fo(i,x,y) for(int i=(x);i>=(y);--i)
const int N=1e5+10,mod=1e9+7;
string a,b,s,t;
int n,k;
ll f[N][2],cnt;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>s>>t>>k;
    n=s.size();
    if(k==0){
        if(s==t) cout<<1<<endl;
        else cout<<0<<endl;
        return 0;
    }
    if(s==t){
        cnt=1;
        f[0][0]=1;
    }
    else f[0][1]=1;
    F(i,1,n-1){
        a=s.substr(0,i);
        b=s.substr(i,n-i);
        a=b+a;
        if(a==t) cnt++;
    }
    F(i,1,k){
        f[i][0]=(cnt*f[i-1][1]+(cnt-1)*f[i-1][0])%mod;
        f[i][1]=((n-cnt)*f[i-1][0]+(n-cnt-1)*f[i-1][1])%mod;
    }
    cout<<f[k][0]<<endl;
    return 0;
}
```

---

## 作者：_JF_ (赞：0)

## CF176B Word Cut

挺厉害的一道题，做一些补充说明。

果然还是数数题不是很行。

首先可以观察到一点，对于一个字符，他在任何位置，他转一圈回来所得到的字符串是不会变化的，因为相对的顺序并没有改变。（其实可以手玩出来。）

所以就可以得到，这做了 $k$ 次操作，就相当于只做了一次操作。（也就是最后一次）。

所以现在要解决，在 所有和 $S$ 构成循环同构的字符串中，找到和 $T$ 相等的字符串，把 $S$ 复制一次跑字符串匹配即可，设符合的位置有 $x$ 个。

因为对于一个字符，在哪个位置操作对构成的字符串都没有影响。所以不妨在 $T$ 上操作，因为这样可以避免掉 $S$ 的第一个字符不能转的问题。且处理来的 $x$ 个位置，在 $T$ 中同样符合转一次，和 $T$ 重合的条件。

然后就设 $dp_{i,0/1}$ 表示转了 $i$ 次，和 $T$ 一样的种类，以及转出来其他串的情况。

转移就是：

$$dp_{i,0}=dp_{i-1,0}\times (x-1)+dp_{i-1,1}\times x$$

$$dp_{i,1}=dp_{i-1,0}\times (n-x)+dp_{i-1,1}\times (n-x-1)$$

在这里主要是注意一下不能从开头来转（因为没有位置可以断了），所以要减去 $1$，不然就是不操作，那就不合法了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
const int mod=1e9+7;
#define int long long 
int k,f[N],dp[N][2],cnt,n;
char s[N],t[N];
void init(){
	f[0]=-1;
	int i=1,j=-1;
	while(i<=n){
		while(j!=-1&&t[i]!=t[j+1])	j=f[j];
		f[i++]=++j;
	}
}
void KMP(){
	int j=0;
	for(int i=1;i<=strlen(s+1);i++){
		while(j!=-1&&t[j+1]!=s[i])	j=f[j];
		j++;
		if(j==n&&i-n+1<=n)	cnt++;
	}
}
signed main(){
	scanf("%s%s%d",s+1,t+1,&k);
	string a=s+1,b=t+1;
	if(a==b)	dp[0][0]=1;
	else	dp[0][1]=1;
	n=strlen(s+1);
	for(int i=1;i<=n;i++)	s[i+n]=s[i];
	init(),KMP();
	for(int i=1;i<=k;i++){
		dp[i][0]+=(dp[i-1][0]%mod*(cnt-1)%mod+dp[i-1][1]%mod*cnt%mod)%mod;
		dp[i][1]+=((dp[i-1][0]%mod*(n-cnt)%mod)+(dp[i-1][1]%mod*(n-cnt-1)%mod))%mod;
		dp[i][0]%=mod,dp[i][1]%=mod;
	}
	cout<<dp[k][0]<<endl;
}
```


---

