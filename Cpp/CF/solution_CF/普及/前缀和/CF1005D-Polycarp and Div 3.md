# Polycarp and Div 3

## 题目描述

Polycarp likes numbers that are divisible by 3.

He has a huge number $ s $ . Polycarp wants to cut from it the maximum number of numbers that are divisible by $ 3 $ . To do this, he makes an arbitrary number of vertical cuts between pairs of adjacent digits. As a result, after $ m $ such cuts, there will be $ m+1 $ parts in total. Polycarp analyzes each of the obtained numbers and finds the number of those that are divisible by $ 3 $ .

For example, if the original number is $ s=3121 $ , then Polycarp can cut it into three parts with two cuts: $ 3|1|21 $ . As a result, he will get two numbers that are divisible by $ 3 $ .

Polycarp can make an arbitrary number of vertical cuts, where each cut is made between a pair of adjacent digits. The resulting numbers cannot contain extra leading zeroes (that is, the number can begin with 0 if and only if this number is exactly one character '0'). For example, 007, 01 and 00099 are not valid numbers, but 90, 0 and 10001 are valid.

What is the maximum number of numbers divisible by $ 3 $ that Polycarp can obtain?

## 说明/提示

In the first example, an example set of optimal cuts on the number is 3|1|21.

In the second example, you do not need to make any cuts. The specified number 6 forms one number that is divisible by $ 3 $ .

In the third example, cuts must be made between each pair of digits. As a result, Polycarp gets one digit 1 and $ 33 $ digits 0. Each of the $ 33 $ digits 0 forms a number that is divisible by $ 3 $ .

In the fourth example, an example set of optimal cuts is 2|0|1|9|201|81. The numbers $ 0 $ , $ 9 $ , $ 201 $ and $ 81 $ are divisible by $ 3 $ .

## 样例 #1

### 输入

```
3121
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1000000000000000000000000000000000
```

### 输出

```
33
```

## 样例 #4

### 输入

```
201920181
```

### 输出

```
4
```

# 题解

## 作者：SUPERLWR (赞：11)

看到好多大佬用 dp 做，不过本蒟蒻觉得好像可以贪心。


## 分析

主要思路就是遍历一遍字符串，累加已遍历的数，碰到以下三种情况时：

1. 目前累加的数的个数已到 3 个。

1. 当前的数是 3 的倍数。

1. 前面已累加的数的和是 3 的倍数。

就可以分出 1 段然后将已累加的数清零，但是为什么呢？


## 证明

 _（对 3 种情况一一讨论）_ 

**第 1 种情况**

即累加个数已到达 3 个，有几种可能的情况。

- 其中出现 0，则转化为第 2 种情况（**0 也是 3 的倍数**）。

- 三个数全是 1，则三个可划为一组。

- 三个数中有两个 1，一个 2，则其中一个 1 可以和 2 划为一组。

- 三个数中有一个 1，两个 2，则其中一个 2 可以和 1 划为一组。

- 三个数全是 2，则三个可划为一组。

**第 2 种情况**

即当前数是 3 的倍数。

因为当前遍历到的数是 3 的倍数，所以这个数可以单独划为一组。

**第 3 种情况**

即前面已累加的数的和是 3 的倍数。

如果没有遇上以上两种情况，这 3 个数可以划为一组。

**综上，当目前累加的数的个数已到 3 个、当前的数是 3 的倍数、前面已累加的数的和是 3 的倍数时，可以划出一组（不一定是当前累加的所有数）。**


------------


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string str;
	cin>>str;
	int len=str.size(),cnt=0,pre=0,ans=0;
	//cnt表示当前累加的数的个数，pre表示当前已累加的数的和，ans表示最终分成的组数
	for(int i=0;i<len;i++)//把字符串的长度提前算好可以节约时间
	{
		pre+=str[i]-'0';//累加 
		cnt++;//计数 
		if(cnt==3||pre%3==0||(str[i]-'0')%3==0)//解释在上面
		{
			ans++;//最终分成的组数加一 
			pre=0;
			cnt=0;//归零 
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Diaоsi (赞：11)

## 思路：

首先考虑一个 $\mathcal{O(n^2)}$ 的做法，设 $f_i$ 表示以 $i$ 为结尾时，每段之和被三整除的段数最多的个数。

显然有一个这样的转移方程：

$$f_i=\max_{j=1}^i\{f_{j-1}+\text{calc}(i,j)\}$$

 $\text{calc}(i,j)$ 表示区间 $[j,i]$ 对答案的贡献， $\text{calc}(i,j)=1$ 当且仅当 $\sum_{k=j}^ia_k \equiv 0 \pmod{3} $ 。

该算法的瓶颈主要在于枚举 $j$ ，考虑优化此处。

有一个这样的结论：**一定能在一个长度大于或等于 $3$ 的序列中划分出一个和能被 $3$ 整除的子串。**

### 证明：

考虑在对 $3$ 取模的意义下构造出一个长度为 $3$ 其任意一个子串的和无法被 $3$ 整除的序列。

+ 显然不能出现 $0$ ，因为 $0$ 自身构成的子串能被 $3$ 整除。

+ $1$ 和 $2$ 不能同时出现，无论怎么摆放，一对相邻的 $1$ 和 $2$ 能一定被 $3$ 整除。

剩下的构造就只有 $111$ 和 $222$ 了，显然这两种情况都可以被 $3$ 整除。

故无法构造出一个长度为 $3$ 且其任意一个子串的和均无法被 $3$ 整除的序列。

对于长度大于 $3$ 的情况，可以考虑在后三位中使用上述方法去划分出一个和**可以**被 $3$ 整除的序列。

### 证毕。

接下来考虑 $j$ 的决策位置，已知区间 $[i-2,i]$ 中一定至少存在一个和可以被 $3$ 整除的序列，由于我们需要划分尽可能多的段，所以当 $j$ 在区间 $(0,i-2)$ 中决策时答案一定不会更优。

这样就把 $j$ 的枚举范围限制在了 $[i-2,i]$ 内，时间复杂度由 $\mathcal{O(n^2)}$ 降至 $\mathcal{O(n)}$ 。

转移方程：

$$f_i=\max_{j=i-2}^i\{f_{j-1}+\text{calc}(i,j)\}$$

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
int n,a[N],f[N],sum[N];
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int &x,int &y){x^=y^=x^=y;}
string s;
int main(){
	cin>>s;
	n=s.size();
	for(int i=1;i<=n;i++)
		a[i]=(int)(s[i-1]-'0'),sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++)
		for(int j=i;j>=Max(1,i-2);j--)
			f[i]=Max(f[i],f[j-1]+((sum[i]-sum[j-1])%3==0?1:0));
	printf("%d\n",f[n]);
	return 0;
}
```


---

## 作者：elijahqi (赞：3)

 http://www.elijahqi.win/archives/3936
 
https://blog.csdn.net/elijahqi/article/details/80993800
我是直接贪心

我们考虑分类讨论即可 我在比赛中被hack了 因为我没有判断最后一个是什么

讨论情况1、遇到0一定切刀

2、如果前后两个非0且不一样一定切刀

3、 如果前后两个相同则一定需要切刀 因为一定会存在满足条件的情况

注意最后的边界特判

具体讨论细节看代码即可
```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+20;
char s[N];int a[N],n;
int main(){
	freopen("d.in","r",stdin);
	scanf("%s",s+1);n=strlen(s+1);
	for (int i=1;i<=n;++i) a[i]=s[i]-'0',a[i]%=3;
	int ans=0,last=0;
	for(int i=1;i<=n;++i){
		if (!a[i]) {++ans,last=0;continue;}
		if (!last) {last=a[i];continue;}
		if (last!=a[i]) {++ans,last=0;continue;}
		if (i+1>n) break;last=0;++i;++ans;
	}printf("%d\n",ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### 题目分析：

显然是 DP。

首先想到一种较为朴素的方法，对于每一个点，向前一直枚举到起点，前缀和一下判断是否可行，复杂度是 $O(n^2)$ 的，不能接受。

形式化地，有：$f_i$ 表示以 $i$ 为终点的一段区间最多能分成的能被三整除的段数，转移时，$f_i=f_j+1$，其中 $j$ 点是 $\sum_{k=i}^ja_i$ 能被 3 整除的一个点。 

考虑优化，发现如果向前枚举过多一定会有浪费，考虑缩小向前枚举转移点范围，~~那就随便找一个大一点的常数枚举一下赶紧把这道大水题过了得了~~。

实际上，这样的一个区间位置最多是 3，也就是每一个点最多向前枚举三个点就行了，否则即使没有找到也一定没有必要枚举下了。

考虑这样的一件事，对于任意一个长度为 $n$ 的序列中一定存在至少一个子串的和 $\bmod n=0$。因为这样的一个序列有 $n+1$ 个前缀和，根据抽屉原理，一定有两个对 $n$ 取余是相等的。这道题中 $n=3$，也就是在三个中一定有一个可以分出至少一个序列能被 3 整除。所以这里如果在往前枚举 3 的基础上再往前枚举一定是不优的。


-------
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[200005],a[200005],len,ans;
int check(int n){if(n%3==0)return 1;return 0;}
int main(){
	while(~scanf("%1d",&a[++len]));len--;
	for(int i=1;i<=len;i++){
		f[i]=max(f[max(0,i-1)]+check(a[i]),max(f[max(0,i-2)]+check(a[i]+a[max(0,i-1)]),f[max(0,i-3)]+check(a[i-1]+a[i]+a[max(0,i-2)])));
		ans=max(ans,f[i]);
	}
	printf("%d",ans);
}
```


---

## 作者：yimuhua (赞：1)

考虑dp。

设 $f(i,j)$ 表示区间 $[i,j]$ 的贡献，当且仅当此区间之和被三整除时 $f(i,j)$ 为 $1$。

设 $dp_i$ 表示将前 $i$ 个数分段后每段之和被三整除的段数最多为多少，显然有：

$dp_i=\max\limits_{j=1}^{i}\{dp_{j-1}+f(j,i)\}$

于是考虑优化，可以发现任何长度大于等于 $3$ 的序列中定能划分出一个和被三整除的子串。

### 证明：

首先可以将每个数转变为其模 $3$ 意义下的值，考虑如何构造反例：

显然长度大于三的序列可只管后三位，于是转变为长度等于三的序列。

显然不能出现 $0$，也不能有连续的 $1,2$，于是只剩下 $111$ 和 $222$，而这两种情况都可以被三整除。

故无法构造出反例。

### 证毕。

于是可知区间 $[i-2,i]$ 中定有至少一个和被三整除的序列，从区间 $[1,i-3]$ 中转移显然不会更优。

于是转移方程变为：

$dp_i=\max\limits_{j=i-2}^{i}\{dp_{j-1}+f(j,i)\}$

显然 $f(i,j)$ 可用前缀和预处理，总时间复杂度为 $O(n)$。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int sum[200005], dp[200005];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s;
    for(int i = 0; i < s.size(); i++)
        sum[i] = sum[i - 1] + s[i] - '0';
    for(int i = 0; i < s.size(); i++)
        for(int j = i; ~j && j > i - 3; j--)
            dp[i] = max(dp[i], dp[j - 1] + !((sum[i] - sum[j - 1]) % 3));
    cout << dp[s.size() - 1];
    return 0;
}
```


---

## 作者：happybob (赞：0)

本题标签是贪心、字符串和前缀和，但是最重要的是动态规划。

我们考虑设 $f_i$ 表示前 $i$ 个字符最多段数，很显然我们枚举 $j$ 从 $1$ 到 $i$，对于每个 $[j,i]$ 求一次数字和，如果为 $3$ 就对贡献加 $1$。

但是很明显这个复杂度是 $O(n^2)$，妥妥 TLE。这时，数学就登场了。

我们知道任一自然数除以 $3$ 余数可能为 $0, 1, 2$。从反面考虑，我们尽量让若干个数相加仍然不是 $3$ 的倍数。明显，我们尽量让余数为 $0$ 的不出现。那么 $1+2 \equiv 0\pmod 3$，$1+1+1 \equiv 2+2+2 \equiv 0\pmod 3$，可得，任取 $3$ 个自然数，其中必有连续的若干个数的和是 $3$ 的倍数。

因此，可以将 $j$ 的枚举范围变为 $[i-2, i]$，代码实现：

```cpp
#include <string>
#include <iostream>
using namespace std;

#define int long long
const int N = 2e5 + 5;

int dp[N], pre[N], ans = 0;
string s;

signed main()
{
	cin >> s;
	int len = s.size(), ans = 0;
	for (int i = 1; i <= len; i++) pre[i] = pre[i - 1] + (s[i - 1] - '0');
	for (int i = 1; i <= len; i++)
	{
		for (int j = i; j >= i - 2; j--)
		{
			if (j < 1) break;
			int x = pre[i] - pre[j - 1];
			dp[i] = max(dp[i], dp[j - 1] + (x % 3 == 0 ? 1 : 0));
		}
		ans = max(ans, dp[i]);
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：_edge_ (赞：0)

DP 题 ……

考虑列出状态为 $f_i$ 表示以 $i$ 为结尾，所产生的最大符合条件的段数。

容易想到 $O(n^2)$ 的解法，就是 $\max \limits _{1 \le j \le i} f_i=f_j+1$ 但是这里注意必须要 $(sum_i-sum_j) \mod 3=0$。

然后我们发现这个东西可以拆出来变成 $sum_i \mod 3-sum_j \mod 3=0$ 也就是说，他们在对 $3$ 取模之后必须是一样的。

由此我们可以想到用一个桶来记录最近的取模 $3$ 为 $0,1,2$ 的位置。

显然，当前如果有多个，肯定取最近的，因为 $f$ 数组具有单调性。

于是复杂度就变为了 $O(n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF=5e5+5;
string s1;
int f[INF],n,sum[INF],num[INF];
signed main()
{
        ios::sync_with_stdio(false);
        cin>>s1; n=s1.size(); s1=" "+s1;
        for (int i=1; i<=n; i++)
                sum[i]=sum[i-1]+s1[i]-'0';
        for (int i=1; i<=n; i++) {
                f[i]=f[i-1];// 继承！
                if (sum[i]%3==0 || num[sum[i]%3]) // 如果啥也没有，但是和最前面可以变为 0 的，也是可以的！
                        f[i]=max(f[num[sum[i]%3]]+1,f[i]);
                num[sum[i]%3]=i;
        }
        cout<<f[n]<<"\n";
        return 0;
}

```



---

## 作者：KCID (赞：0)

#### 前言

我的做法貌似是个“比较正确”的做法，时间复杂度是O($n$ * 玄学)

#### 做法

首先考虑$dp$，设置状态$dp[i]$表示将前$i$个数字进行分段可以得到的最多的为三的倍数的段的数量。

一开始想到的转移方法是O($n^2$)的，也就是首先预处理一个前缀和，然后转移的时候：

$dp[i] = max(dp[i],dp[j - 1]$ $+ sum[i] - sum[j]$)(是$or$不是三的倍数)

这样子得枚举一个$j$，显然不妥，过不了这一题。

但是我们想到，得到的$dp[]$数组是单调不降的，这个是很轻松可以知道的。

所以要是我们不把一段拿出来，显然直接用$dp[i]$继承$dp[i - 1]$是最优的。

然后我们想，每一次，将一段提出来，对答案的贡献显然只能加$1$或者$0$

$dp[i - 1]$又是$dp[i]$之前的所有$dp[j]$中最大的。倘若要使得$dp[j] + 1 > dp[i - 1]$($i - 1 > j$)，那么显然$dp[j]$应该是等于$dp[i - 1]$的。

因此，我们枚举的时候，实际上不需要枚举那么多，采用倒序枚举，只要枚举到的$dp[j]$已经小于$dp[i - 1]$了，就没有枚举下去的必要了，答案不可能比直接继承更优了，直接$break$

因此这样子的时间复杂度是是O($n$ * 玄学)的。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
char ch[200005];
int dp[200005];
int data[200005];
int sum[200005];

int pd(int x)
{
	if(x % 3 == 0)return 1;
	return 0;
}

int main()
{
	cin >> ch + 1;
	int n = strlen(ch + 1);
	for(int i = 1 ; i <= n ; i ++)
		data[i] = ch[i] - '0' , sum[i] = sum[i - 1] + data[i];
	if(data[1] % 3 == 0)dp[1] = 1;
	for(int i = 2 ; i <= n ; i ++)
	{
		int t = dp[i - 1];
		for(int j = i ; j >= 1 ; j --)
		{
			if(dp[j - 1] < t)break;
			dp[i] = max(dp[j - 1] + pd(sum[i] - sum[j - 1]),dp[i]);
		}
	}
	cout << dp[n];
	return 0;
}
```

#### 后话

同时也欢迎大家来Hack我！

（貌似想了想，这个做法的时间复杂度是可以保证比较优秀的，因为貌似很难被卡)

（可能是我太菜了不会。)


---

## 作者：cz666 (赞：0)

## 放在前面：

蒟蒻语文表达能力不是很好，思路里可能有些细节不到位，请多多包涵。

## 思路：

~~这题是一道算是很经典的dp的题目了。~~

我们先考虑 $dp$ 的四大要素。

状态：$dp[i]$表示从数字字符串开头到第 $i$ 位最多能划分出几段 $3$ 的倍数的数。

转移：这里要分几种情况讨论：

- 第 $i$ 位的数不放入最后一段可被 $3$ 整除的数字片段里能使 $dp[i]$ 达到最优，显然这个在所有情况下都存在。

	转移$(1):dp[i]=dp[i-1]$。
    
- 第 $i$ 位的数放入最后一段可被 $3$ 整除的数字片段里能使原来的 $dp[i]$ 更大：

	有一个~~公认的~~事实，那就是若从第 $i$ 位向前取一些数位组成的数字能被 $3$ 整除，那么取的数字越少越能使答案保持最优（不理解的自己想一想为什么，这里就不做解释了）
    
    所以预处理一个 $pre[i]$ 数组去存储以第 $i$ 位为结尾的最短的能被 $3$ 整除的数字片段的开头那一位置，第 $i$ 位的答案就从 $pre[i]$ 那里转移过来。
    
    转移$(2):dp[i]=dp[pre[i]]+1$。
    
    但是情况二是会出问题的，如果之前在做 $dp[pre[i]]$ 时已经把 $pre[i]$ 这位数字分配给前一段，$dp[pre[i]]$ 到 $dp[i]$这一段就不能成立，所以处理掉这种情况即可。

## AC代码：

```cpp
#define love_zqx_forever std
#include<bits/stdc++.h>
#define int long long
using namespace love_zqx_forever;
inline void write(int x){
    if (x<0) putchar('-'),x=-x;
    if (x>9) write(x/10);putchar(x%10|'0');
}
inline void wlk(int x){
    write(x);putchar(32);
}
inline void wln(int x){
    write(x);putchar(10);
}//快读
const int maxn=200003;
int a[maxn],pre[maxn];
int dp[maxn],fuz[maxn],cnt;
signed main(){
    char c=getchar();
    while(c>='0'&&c<='9'){
        a[++cnt]=c;
        c=getchar();
    }
    for (int i=cnt;i>=1;--i){
        int tot=a[i],now=i;
        if (!(tot%3)){pre[i]=i;continue;}
        while(tot%3&&now){
            now--;
            tot+=a[now];
        }
        pre[i]=now;
    }//预处理出pre[i]
  	 //看似是个O(N^2)的，其实均摊（是均摊！均摊！）每个位都向前跑最多3格，复杂度O(N)
    for (int i=1;i<=cnt;++i){
        dp[i]=dp[i-1];//情况(1)
        if (pre[i]){
            if (dp[pre[i]]+1>dp[i]&&!fuz[pre[i]]){
                dp[i]=dp[pre[i]]+1;//情况（2）
                fuz[i]=1;//用来处理掉不合法情况
            }
        }
        // if (pre[i]) dp[i]=max(dp[i],dp[pre[i]]+1);
        // cout<<i<<" "<<dp[i]<<endl;
    }
    return wln(dp[cnt]),0;
}
```


---

## 作者：wutiruo (赞：0)

这道题用DP~~（很显然的）~~（大雾）。

每个位置更新前缀余数(见程序)；
用 _Maxv_ 数组记录离当前位置最近且前缀余数相同的位置，初始为-1，注意， _maxv[0]_ 为，因为一开始前缀和为零，防止第一个数为3,6,9的情况。

如果存在与我余数相同的数，则将dp[maxv[r]]+1与dp[i]（也就是dp[i-1]）比大。

最后答案在dp[n]里。


程序：

```cpp
#include<iostream>
using namespace std;
int dp[200001],maxv[3]={0,-1,-1};//这是DP数组和存离当前位置最近且余数相同的maxv数组
int main(){
    string s;
    cin>>s;
    int n=s.size(),r=0;
    s=' '+s;//小技巧，使字符串下标变为1~size()-1
    for(int i=1;i<=n;i++){
        r=(r+s[i]-48)%3;//每个位置更新前缀余数
        dp[i]=dp[i-1];//不在当前位置切，则继承dp[i-1]
        if(maxv[r]!=-1)//存在与我余数相同的数
            dp[i]=max(dp[i],dp[maxv[r]]+1);//与自己（也就是dp[i-1]）比大
        maxv[r]=i;//更新maxv数组
    }
    cout<<dp[n];
    return 0;
}
```

---

## 作者：VenusM1nT (赞：0)

这题虽然是 $div3$ 的题，但难度还是不小，本来我只是打了个“暴力”试试，但没想到最终 $A$ 了，于是乎来瞎讲讲

-----
题目大意：给定一个大数，试将该数切成多段，形成多个数，并使其中 $3$ 的倍数尽可能多，试求出最多能切出多少个 $3$ 的倍数

$P.S.$ 值得注意的是，$0$ 也是 $3$ 的倍数

-----
对该题完全没有思路，于是想试一试贪心

定的贪心策略是：如果当前一位到上一次切的位置**之间**能够切出为 $3$ 的倍数的数，那么 $ans+1$ ，并使上一次切的位置为当前位置

略加思索，为了得到更优解，在当前已获得 $3$ 的倍数的情况下，没有必要再多选取一位数，因为很显然地，如果下一位数可以与当前获得的 $3$ 的倍数组成 $3$ 的倍数的话，那么下一位数必然可以自己组成一个 $3$ 的倍数

如果下一位数不能与当前获得的 $3$ 的倍数组成 $3$ 的倍数的话，那么肯定需要选取更多的数才能组成 $3$ 的倍数，而在多选取的数中没准就会包含一个 $3$ 的倍数，如果包含了，那么得到的解将不是最优解

比如 $24271$，最优的分法是 $24|27|1$，而非 $2427|1$

贪心的策略确定了，接下来要解决如何优化的问题了

很显然地，如果使用最暴力的写法，时间复杂度将到达 $O(n^2)$，对于一个位数多达达 $2*10^5$ 的数来说必然是承受不住的

那么这里可以使用字符串存数，前缀和计算是否为 $3$ 的写法，时间复杂度可以有效降低

代码见下

```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
int n,ans,sum[200005],tot;
string s;
int main()
{
	cin >> s;
	int len=s.size();
	s='%'+s;
	for(int i=1;i<=len;i++) sum[i]=sum[i-1]+s[i]-'0';//前缀和
	int lat=1;//lat记载上一个切的位置
	for(int i=1;i<=len;i++)
	{
		for(int j=lat;j<=i;j++)//计算在i处切一刀是否能形成3的倍数
		{
			int cnt=sum[i]-sum[j-1];
			if(cnt%3==0)
			{
				lat=i+1;//使上一次切的位置为当前位置
				ans++;
				break;
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

### 不懂如何验证一个数为 $3$ 的倍数的同学请自行温习小学数学

---

## 作者：ZVitality (赞：0)

挺简单的，至少代码跟思路都很好想。

如果 $\forall i(1\le i\le n),a_1\dots a_i$ 已经确定最大值，那跟后面就没有关系了，所以可以直接 $O(n)$ 推。

假设现在加的数字为 $a_x$，那么分三种情况：

1. 可以直接整除，即 $0,3,6,9$。
2. 与之前连接的加起来可以被 $3$ 整除，如 $1,2$ 这种连接起来又可以相加。
3. 最难想到的一点，连接超过三个数肯定可以被 $3$ 整除。

---

这里给出第三条的证明：

我们可以发现，有这几种情况：

$x,x,x$

$x,x,y$

如果 $3$ 个数相同，我们就可以相加，如果有不同的，那么肯定有一个 $1$，有一个 $2$，那么这也是可以被整除的。

注意要记得使用 string 存储，不然会炸。

---

