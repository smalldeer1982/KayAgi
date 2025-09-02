# Hamming Distance Sum

## 题目描述

吉诺斯需要你的帮助。他被要求完成塞塔玛出的如下编程问题：  
  
  字符串 s 的长度被表示为 $\left|s\right|$。两个等长字符串 s 和 t 之间的“Hamming”距离被定义为 $\sum\limits_{i=1}^{\left|s\right|}\left|s_i-t_i\right|$，其中，$s_i$ 是字符串 s 的第 i 个字符，$t_i$ 是字符串 t 的第 i 个字符。  
  
  比如说，字符串“0011”和字符串“0110”之间的“Hamming”距离为 $\left|0-0\right|+\left|0-1\right|+\left|1-1\right|+\left|1-0\right|=0+1+0+1=2$。
  
  给定两个字符串 a 和 b，找到字符串 a 和所有字符串 b 的长度为 $\left|a\right|$ 的子串之间的“Hamming”距离总和。

## 样例 #1

### 输入

```
01
00111
```

### 输出

```
3
```

## 样例 #2

### 输入

```
0011
0110
```

### 输出

```
2
```

# 题解

## 作者：D23lhc (赞：2)

#### 题目大意:
给你两个字符串，第一个字符串的长度小于等于第二个，然后拿第一个字符串 1 与字符串 2 从头到尾移动进行比较，求出此比较过程中出现的 01 对数。

### 解题思路：
一开始我们肯定会想到暴力枚举，在字符串 2 上操作，拿字符串 1 从第一位往后移动进行比较，然后计算出每次移动所得的 01 对数，然而这样做复杂度太大，那么我们应该怎么来解决这个问题呢？这里给大家介绍另一种思路：对于字符串 1 中的每个字符，在比较时都是在一个确定的区间里移动的，所以我们只要求出这个区间中字符串 2 中与该字符不同的个数即可，对于不同的个数我们就可以用前缀和 $sum[a~b] = pre[b]-pre[a-1]$ 来解决，这样我们的复杂度就降低到了 $O(b)$。
## 代码：

```
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<queue>
#define bug printf("***\n");
//#define mem0 memset(a, 0, sizeof(a));
using namespace std;
typedef pair<long long, int> par;
const int mod = 1e9+7;
const int INF = 1e9;
const int N = 10010;
 
int main()
{
    char str[N], ch[N];
    int pre0[N], pre1[N]; //前缀0的个数、前缀1的个数
    while(~scanf("%s%s", ch, str)) {
        long long ans = 0;
        int len1 = strlen(ch);
        int len2 = strlen(str);
        pre0[0] = pre1[0] = 0;
        if(str[0] == '0') pre0[0] = 1;
        else pre1[0] = 1;
        for(int i = 1; i < len2; i ++) { //统计前缀和
            if(str[i] == '1') {
                pre1[i] = pre1[i-1]+1;
                pre0[i] = pre0[i-1];
            }else {
                pre0[i] = pre0[i-1]+1;
                pre1[i] = pre1[i-1];
            }
        }
        for(int i = 0; i < len1;  i++) { //计算出匹配区间内所有不同的对数
            if(i == 0) {
                if(ch[i] == '0') ans += pre1[len2-len1];
                else ans += pre0[len2-len1];
            }else {
                if(ch[i] == '0') ans += (pre1[len2-len1+i] - pre1[i-1]);
                else ans += (pre0[len2-len1+i] - pre0[i-1]);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：DiDi123 (赞：1)

# 一、题意
求字符串 $b$ 中长度为 $|a|$ 的子串中与字符串 $a$ 不同的字符数量之和是多少。

# 二、分析

一开始看到这道题肯定是想暴力解决，复杂度是 $O(n^2)$ 的，但是 $|a|\leq2\times 10^5$ 肯定是这个复杂度解决不了的。

接着我们发现 $a$ 每次都在与跟自己长度相同的子串做对比，而这样做对比时每位都是对齐的。$a$ 在逐渐向右移动比较的过程中，$a$ 中的每一位也在逐渐向右移动，而且它们总是只和相应位置的 $b$ 中的那一位比较。所以整个比较的过程就可以拆解成 $a$ 中的每一位去和 $b$ 比较，让后让和累加就好了。

还要注意每个元素移动的范围，因为一个元素前面后面都有其他元素垫着，所以它一定的范围要比这个 $b$ 要小一些，第 $i$ 个元素的移动范围是 $[i,|b|-(|a|-i)]$（建议手推一遍）。

累加的过程我们可以用前缀和预处理快速解决，这样可以把复杂度降到 $O(n)$。如果 $a_i=0$，我们就统计 $i\sim|b|-(|a|-i)$ 中有多少个 $1$，否则，就统计 $0$ 的数量就好了。

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200001
string a,b;
long long ans,sum[MAXN];
long long get_sum(int l,int r)
{
	return sum[r]-sum[l-1];
}
int main()
{
	cin>>a>>b;
	for(int i=0;i<b.length();i++)
		sum[i+1]=sum[i]+b[i]-'0';
	for(int i=0;i<a.length();i++)
	{
		if(a[i]=='0') ans+=get_sum(i+1,b.length()-a.length()+i+1); //和的大小就是1的个数
		else ans+=b.length()-a.length()+1-get_sum(i+1,b.length()-a.length()+i+1); //不是1的位置就是0
	}
	cout<<ans;
}
```


---

## 作者：OIerZhang (赞：1)

# [CF608B Hamming Distance Sum](https://www.luogu.com.cn/problem/CF608B) 题解

## 题意

极简题意：给定 $2$ 个 $01$ 字符串 $a$ 和 $b$，求 $b$ 中所有长度为 $|a|$ 的子串与 $a$ 相比不同的字符的数量之和。（$1 \le |a| \le |b| \le 2 \times 10^5$）

## 思路

由于本题的数据达到了惊人的 $2 \times 10^5$，所以 $O(n^2)$ 的暴力肯定是不行的。注意到每次计算“Hamming”距离时会有大量重复工作（这不是废话吗），所以我们就需要用**前缀和**来优化计算过程。

我们会发现，计算过程中 $a$ 和子串的每一位的两两比较可以看作 $a$ 的每一位在和 $b$ 比较，例如 $|a|=2,|b|=3$，那么结果就是：
$$
\begin{aligned}
    (|a_1 - b_1| + |a_2 - b_2|) + (|a_1 - b_2| + |a_2 - b_3|) &= \displaystyle \sum_{i=1}^{2} |a_1 - b_i| + \sum_{i=2}^{3} |a_2 - b_i| \\
    &= \sum_{i=1}^{|a|} \sum_{j=i}^{|b| - |a| + i} |a_i - b_j|
\end{aligned}
$$

所以我们可以先预处理出 $b$ 的前缀和，计算时只需要找到 $a_i$ 移动区间的范围，$a_i$ 为 $0$ 时，用前缀和求区间内 $1$ 的个数，$a_i$ 为 $1$ 时，求区间内 $0$ 的个数，这样程序的时间复杂度就降到了 $O(n)$。

接下来我们面临一个棘手的问题：$a_i$ 移动的区间是什么？因为 $a_i$ 前后都有字符，所以 $a_i$ 的移动范围就是 $[$ 字符串 $b$ 的第一个字符 ${} + a_i$ 前面的字符数 $,$ 字符串 $b$ 的最后一个字符 ${} + a_i$ 后面的字符数 $] = [i, |b| - (|a| - i)]$（$a$ 和 $b$ 下标从 $0$ 开始，前缀和下标从 $1$ 开始）。但是前缀和只统计了 $1$ 的个数，所以统计 $0$ 时要用区间内元素的个数减去区间内 $1$ 的个数。

还有一个点要注意：$|b|$ 最大是 $2 \times 10^5$，意味着答案最大是 $10^5 \times 10^5 = 10^{10}$，需要开 long long。

## 核心代码

```cpp
for (int i = 1; i <= lb; i++) // la 和 lb 是 a 和 b 的长度
    s[i] = s[i - 1] + b[i - 1] - '0'; // 由于 b 下标从 0 开始，所以是 b[i - 1]
for (int i = 1; i <= la; i++) // #define int long long
{
    if (a[i - 1] == '0') // 同上
        ans += s[i + lb - la] - s[i - 1];
    else
        ans += lb - la + 1 - (s[i + lb - la] - s[i - 1]); // |b| - (|a| - i) = i + |b| - |a|
}
```

---

## 作者：N_z_ (赞：0)

## 思路
因为我们注意到每一位对答案的贡献取决于它与它能对上的另一个字符串的位置中与它不同的数量。

所以我们先处理出 $b$ 字符串的前缀和，然后对于 $a$ 字符串的每一位，判断它能对上 $b$ 字符串的几位。

记得答案要开 $long\ long$。

具体见代码。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200002];
signed main()
{
	string s,t;
	cin>>s>>t;
	s=' '+s,t=' '+t;
	for(int x=1;x<t.size();x++)
	a[x]=a[x-1]+(t[x]=='1');
	int ans=0;
	for(int x=1;x<s.size();x++) //{
	ans+=(s[x]=='1')*(t.size()-s.size()+1-a[t.size()-s.size()+x]+a[x-1])+(s[x]=='0')*(a[t.size()-s.size()+x]-a[x-1]);
	//cout<<t.size()-s.size()+1-a[t.size()-s.size()+x]+a[x-1]<<','<<a[t.size()-s.size()+x]-a[x-1]<<',';
	cout<<ans<<endl;//}
}
```

---

