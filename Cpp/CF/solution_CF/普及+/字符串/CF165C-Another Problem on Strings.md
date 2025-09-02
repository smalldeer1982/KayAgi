# Another Problem on Strings

## 题目描述

A string is binary, if it consists only of characters "0" and "1".

String $ v $ is a substring of string $ w $ if it has a non-zero length and can be read starting from some position in string $ w $ . For example, string "010" has six substrings: "0", "1", "0", "01", "10", "010". Two substrings are considered different if their positions of occurrence are different. So, if some string occurs multiple times, we should consider it the number of times it occurs.

You are given a binary string $ s $ . Your task is to find the number of its substrings, containing exactly $ k $ characters "1".

## 说明/提示

In the first sample the sought substrings are: "1", "1", "10", "01", "10", "010".

In the second sample the sought substrings are: "101", "0101", "1010", "01010".

## 样例 #1

### 输入

```
1
1010
```

### 输出

```
6
```

## 样例 #2

### 输入

```
2
01010
```

### 输出

```
4
```

## 样例 #3

### 输入

```
100
01010
```

### 输出

```
0
```

# 题解

## 作者：Mine_King (赞：6)

假设我们现在已经有了一个包含 $k$ 个 $1$ 的 $s$ 的子串 $[l,r]$,且 $s_l$ 和 $s_r$ 都是 $1$。那么我们可以向左右扩展这个子串。我们尝试在 $O(1)$ 的时间复杂度内求出由这个子串扩展而来的满足条件的子串个数。  
这个可以根据乘法原理得到，就是 $l$ 左边连续的 $0$ 的个数 $+1$ 再乘上 $r$ 右边连续的 $0$ 的个数 $+1$ 的和的积。

那么我们如何求所有的上述子串和记录每个 $1$ 左右 $0$ 的个数呢？枚举即可。只要从头开始搜整个字符串，遇到 $1$ 就记录一下，如果 $1$ 的个数大于等于 $k$，那么就向左找 $k$ 个 $1$，再用上面说到的方法求区间个数。

但是上面这个做法好麻烦呀！不能优化一下吗？当然可以！首先定义一个数组 $f_i$ 表示第 $i$ 个 $1$ 右边连续的 $0$ 的个数，然后扫描整个字符串，遇到 $1$ 则计数器 $+1$。然后，如果 $1$ 的个数 $onenumber \ge k$，那么 $f_{onenumber-k}$ 就是以第 $onenumber$ 个 $1$ 为 $r$ 的满足条件的子串的左边连续的 $0$ 的个数，接着把答案加上 $f_{onenumber-k}+1$。然后继续往下搜，每搜到 $0$，就把答案加上 $f_{onenumber-k}+1$，这样的做法其实就是把上面提到的乘法变成了加法，又不增加时间复杂度。最后扫完整个字符串答案就出来了。

代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int k,f[1000005],onenumber;
long long ans;
int main()
{
	scanf("%d",&k);
	memset(f,-1,sizeof(f));
	f[0]=0;
	for(int x;scanf("%1d",&x)!=EOF;)
	{
		onenumber+=x;
		if(onenumber>=k) ans+=f[onenumber-k]+1;
		f[onenumber]++;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：_byta (赞：4)

这次与 dp 十分类似，但严格来说并不是 dp，我来说一下我的思路。

我们用 $dp(i)$ 表示包含 i 个一的子串个数，因为不是 dp，所以没有递推公式。

我在这里只讲一讲 dp 数组的求法，我们从 0 到 len 扫描字符串,扫到 1 个 1，

我们就把 $dp(i)$ 加加，这样就可以求出 dp 数组了。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long k , ans , t , dp[1000002];
string s;
int main()
{
	dp[0] = 1;
	cin >> k >> s;
	for(int i = 0 ; i < s.size() ; i++)
{
		if(s[i] == '1') t ++;
		if(t >= k) ans += dp[t-k];
		dp[t] ++;
	}
	cout << ans;
}
```





---

## 作者：LRL65 (赞：3)

我们可以先举一个例子来熟悉一下题目（第一行为$k$，第二行为字符串）：

2

0 1 0 1 0（为了方便，我加了空格）

接下来我们研究一下，要想有两个$k$，那么这个字串的结尾应在第二个1即以后。

**但是，还有0呀**。后面的0我们可以不用管，因为可以往后扫，就自动算上了。那前面的咋办呢？那我们可以用一个数组 $s0_i$，意思是第i个1后有多少个0。**我们初始化时应将这个数组的第一个设为1**，因为开头没算没有0（也就是0个0）的情况。

比如这个例子，我们就应该从第二个1开始看起，前面有一个0，所以有两种选择（1个或0个）。继续往后到最后一个字符，前面还是两种，所以加起来为4。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000005
int k,s0[MAXN]={1},s1=0;//初始化
char s;//用char输入会简单一点
long long ans=0;
int main(){
    cin>>k;
    while(cin>>s) {
        if(s=='1')s1++;//累计有多少个1
        if(s1>=k)ans+=s0[s1-k];
        s0[s1]++;//累加第s1个1后的0的个数
    }
    cout<<ans<<endl;
}
```


---

## 作者：GaryH (赞：1)

## CF165C 题解
看到其他人都用的dp，那我就来一发双指针好了。

首先，我们可以简单的想到一个 $O(n^2)$ 的做法：

计 $sum(i)$ 代表串 $s$ 中前 $i$ 个字符中 $1$ 的个数，

$Le(i)$ 代表串 $s$ 中第 $i$ 个字符左边的最长连续 $0$ 的长度，

$Ri(i)$ 代表串 $s$ 中第 $i$ 个字符右边的最长连续 $0$ 的长度，

枚举每一个数对 $(l,r)$ ，代表了两个字符串中的位置。当然，对答案有贡献的数对必须满足一个前置条件： $sum(r)-sum(l-1)=k$ .

那么，满足前置条件的数对对答案的贡献即为：

 $ans(l,r)=Le(l) \times Ri(r)$.
 
更形式化的，整个串的答案即为：

$\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}Le(l) \times Ri(r)\times [sum(r)-sum(l-1)=k] $.

朴素做法的时间复杂度显然会爆，所以我们考虑优化。

观察到区间中 $1$ 的个数随区间的扩展而增大，所以我们可以采用双指针的方法简化掉暴力的枚举。

即：建立两个指针 $l,r$ ，每次 $r$ 随着 $l$ 的增长而增长，所以在统计 $l,r$ 时用尺取的方法计算答案即可。

这样的时间复杂度是 $O(n)$ 的，因为 $l,r$ 最多加 $O(n)$ 次。

---

## 作者：oimaster (赞：0)

[题目链接点这里！](http://codeforces.com/problemset/problem/165/C)

题意简述：
- 给定一个数字 $k$ 和 01 串 $s$。
- 求出 $s$ 中恰好包含 $k$ 个 $1$ 的子串数量和。
- $0\le k\le 10^6$，$|s|\le10^6$
- 为了题解说明清楚，我把 $|s|$ 简称为 $n$。

暴力中的暴力复杂度 $O(n^3)$，稍优化暴力也只能达到 $O(n^2)$，无法通过此题。

正解是递推思路。假设我们处于第 $i$ 号字符。我们要计算从前面到 $i$ 号字符有 $k$ 个 $1$ 的字符串数量。像动态规划算法一样考虑问题，发现要想得到当前答案，只需要知道 $dp_{i-k}$ 的值即可，而那 $k$ 个 $1$ 在哪里我们没必要考虑。因 为每个 $dp_{i-k}$ 到 $i$ 都需要 k 个 $1$，所以这样做的正确性有了保证。

代码见[云剪贴板](https://www.luogu.com.cn/paste/bt4wowgk)。

---

## 作者：Awa486 (赞：0)

## 字符串练手题
只需要简单理解题意并按题意模拟即可

上简短代码
```cpp
#include<bits/stdc++.h>//没有必要的万能头 
#define MAXN 1000001
int k,s,d,array[MAXN]={1},i;
long long ans;
int main()
{
    scanf("%d",&k);
    getchar();
    while(s = getchar(),s!='\n')//只要还在输入s
    {
        if(s=='1')d++;//如果输入的s为1就累加d 
        if(d>=k)ans+=array[d-k];//如果此时k已经大于d，那么在ans上加上数组array的第d-k项。注意在此如果输入的s为0，那么仍能附着到前面为1的子串上，故仍需加1 
        array[d]++;//操作完后将array数组的第d项+1，如果s为0，那么这一位上将再累加一
    }
    printf("%I64d\n",ans);//不用这个会玄学WA 
}
```


---

