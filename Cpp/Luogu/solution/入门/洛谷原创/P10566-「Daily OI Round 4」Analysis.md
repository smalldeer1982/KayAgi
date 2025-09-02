# 「Daily OI Round 4」Analysis

## 题目描述

小 C 的信息技术老师给小 C 布置了一项作业，作业内容如下：

> 有一个字符串，包含大小写字母和数字。你可以把任意一个字符变成另外一个字符，设变化之前字符的 ASCII 码为 $a$，变化之后字符的 ASCII 码为 $b$，则这次变化消耗 $|a-b|$ 的时间。你需要把整个字符串变成只包含大写字母的字符串。

小 C 还有语文数学英语等很多其他重要作业要做，为了节省时间，你需要计算小 C 最少需要多久才能令字符串只包含大写字母。

## 说明/提示

#### 【样例解释】

对于第一组样例，最好的办法是变成 $\texttt{AAAZZ}$，这样的话消耗就为 $0+0+|48-65|+|97-90|+|97-90|=31$，容易证明不存在更优的解法。

其中 $48$ 是字符 $\texttt{0}$ 的 ASCII 码，$65$ 是字符 $\texttt{A}$ 的 ASCII 码，$90$ 是字符 $\texttt{Z}$ 的 ASCII 码，$97$ 是字符 $\texttt{a}$ 的 ASCII 码。

#### 【数据范围】

**本题开启捆绑测试。**

设 $len$ 为字符串 $s$ 的长度。

| $\text{Subtask}$ | 分值 | $len \le$ |
| :-----------: | :-----------: | :-----------: |
| $0$ | $10$ | $3$ |
| $1$ | $30$ | $10$ |
| $2$ | $60$ | $10^5$ |

对于全部数据，保证：$1 \le len \le 10^5$，且 $s$ 中只包含大小写字母和数字。

## 样例 #1

### 输入

```
AA0aa```

### 输出

```
31```

## 样例 #2

### 输入

```
3kyOu```

### 输出

```
89```

# 题解

## 作者：cute_overmind (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/P10566)

### 题目大意
给定一个字符串 $s$，现在要将这个字符串变成只有大写字母的字符串。

设变换前的字符 `ASCII` 码为 $a$，变换后的 `ASCII` 码为 $b$。每一次变换的时间 $t$ 为 $|a-b|$。求 $t$ 的最小值。

### 题目分析
考虑暴力枚举。

我们可以先定义一个字符串的长度 $n$，然后再进行暴力枚举。

我们可以分成两类进行讨论：
- 当字符 $s_i \le 64$ 时，此时最小值为 $t = 65 - s_i$。
- 当字符 $s_i \ge 91$ 时，此时最小值为 $t = s_i - 90$。

所以即得最后答案 $t$。

### [代码](https://www.luogu.com.cn/record/161169767)
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n , t;
int main()
{
	cin >> s; 
	n = s.length();
	for(int i = 0;i < n;i++){
		if(s[i] > 'Z') t += s[i] - 'Z';
		if(s[i] < 'A') t += 'A' - s[i];
	}
	cout << t;
	return 0;
 } 
```

---

## 作者：hcy1117 (赞：4)

来贡献一篇**思路十分简单**的题解
### 前置知识
字符串
## 简单的思路
对于字符串中的每一个字符 $s_{i}$，暴力枚举每一个大写字母，计算出将其变成这一大写字母的时间，取最小值。最后将每个字母的时间最小值累加得到答案。

时间复杂度$O(n \times 26)$。

其余不懂的可以参考代码和注释。
## 简单的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;//字符串长度 
int main()
{
	cin>>s;
	n=s.size();
	s=' '+s;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int minn=INT_MAX;//最小值 
		for(int j=1;j<=26;j++)//暴力枚举 
		{
			minn=min(minn,abs(j+'A'-1-s[i])/*时间*/);
		}
		ans+=minn;
	}
	cout<<ans;//输出 
	return 0; 
}
```

---

## 作者：zcs_ (赞：3)

## 题目大意：

对于一个字符串，里面有大小写字母与数字，要把每个字母都变成大写的字母。设变化之前字符的 ASCII 码为 $a$，变化之后字符的 ASCII 码为 $b$，则这次变化消耗 $|a-b|$ 的时间。求这个时间的最小值。

## 解法

显然，对于每个要变换的数字，变换到字母 ```A```
的时间是最短的。而对于每个小写字母，变换到字母 ```Z```
的时间是最短的。又因为字母 ```A```
的ASCII码所对应的数字是 $65$ ,字母 ```Z```
的ASCII码所对应的数字是 $90$。所以能得到以下代码。

## AC Code:

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
string s;
int ans;
int main(){
	getline(cin,s);
	for (int i=0;i<s.length();i++){
		if (s[i]>='0' && s[i]<='9'){
			ans+=abs(65-s[i]);
		}
		else if (s[i]>='a' && s[i]<='z'){
			ans+=abs(90-s[i]);
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：NC20061226 (赞：2)

# Analysis 题解

## 题意

给定一个包含大小写字母、数字的字符串，将字符串的所有字符转化为大写字母，求所有字符变化前与变化后的 ASCII 码的差值的绝对值之和的最小值是多少。

## 手玩样例

对于样例二 $s=\texttt{3kyOu}$，包含非大写字母 $\texttt 3$、$\texttt k$、$\texttt y$、$\texttt u$。原字串 ASCII 码分别为 $51,107,121,79,117$，显然最优解为 $s'=\texttt{AZZOZ}$，ASCII 码分别为 $65,90,90,79,90$，转化后与转化前的 ASCII 码差值为：

$$\lvert 51-65\rvert +\lvert 107-90\rvert +\lvert 121-90\rvert+\lvert 79-79\rvert+\lvert 117-90\rvert=89$$

$89$ 这个数值显然是最小的绝对值之和，没有更优解。

## 转化原则

这里放一张 ASCII 码表：

| $\texttt 0$ | $\texttt 1$ | …… | $\texttt 9$ | …… | $\texttt A$ | $\texttt B$ | …… | $\texttt Z$ | …… | $\texttt a$ | $\texttt b$ | …… |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $48$ | $49$ | **……** | $57$ | **……** | $65$ | $66$ | **……** | $90$ | **……** | $97$ | $98$ | **……** |

因为题目中说字符串 $s$ 包含大小写字母和数字。

- 大写字母不用转化，这样可以使差值为 $0$，尽量减小结果；
- 根据上表，大写字母 ASCII 码和数字的 ASCII 码最接近的是大写字母 $\texttt A$，它与所有数字的差值都比其他大写字母和数字的差值更小，所以所有的数字转化为大写字母 $\texttt A$；
- 根据上表，大写字母 ASCII 码和小写字母的 ASCII 码最接近的是大写字母 $\texttt Z$，它与所有字母的差值是最小的，所以小写字母转化为大写字母 $\texttt Z$。

思路知道了，就可以开始砸键盘了。

## 代码实现

在代码中，我们需要遍历字符串并一个计数器 $ans$ 来累加绝对值之和。这里的绝对值就是：

- 当 $s_i$ ASCII 码小于 $65$ 时，说明 $s_i$ 为数字，计算它的 ASCII 码与 $\texttt A$ 的 ASCII 码 $65$ 之差的绝对值；
- 当 $s_i$ ASCII 码大于等于 $97$ 时，说明 $s_i$ 为小写字母，计算它的 ASCII 码与 $\texttt Z$ 的 ASCII 码 $122$ 之差的绝对值；

在 Python 中，字符串和数字是不能直接比较的，需要使用函数 `ord(i)` 得出字符串 $i$ 的 ASCII 码。

### CODE

```python
s = input()            # 输入
ans = 0                # 创建计数器
for i in s:            # 遍历字符串
    ASCII=ord(i)       # 计算 s[i] 的 ASCII 码
    if ASCII<65:       # 如果 s[i] 是数字
        k = 65-ASCII   # 计算与 A 的差值
        ans+=abs(k)    # 计数器累加绝对值
    elif ASCII>=97:    # 如果 s[i] 是小写字母
        k = ASCII-90   # 计算与 Z 的差值
        ans+=abs(k)    # 计数器累加绝对值
print(ans)             # 输出计数器结果
```

感谢大家的观看！求管理员通过，幸苦了！

---

## 作者：_Epsilon_ (赞：1)

## 思路
首先强制转换计算 ASCII 码，再去判断是不是大小写，若不是，就把这个字符转换为最近的大写。

而最近的大写字母我们稍微思考一下也可以知道。把所有大写字母想象成一个区间，在区间外的字符只能是小了或者大了。直接用 `A` 和 `Z` 比较一下，哪个近就改成哪个。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
char c;
int ans,ac;
const int A=int('A'),Z=int('Z');
int main()
{
    while(cin>>c)
    {
        ac=int(c);
        if(ac>=A&&ac<=Z)
        {
            continue;
        }
        else if(ac<A)
        {
            ans+=A-ac;
        }
        else
        {
            ans+=ac-Z;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_little_Cabbage_ (赞：1)

简单题。对于字符串的每一位，若它是数字，则把它变成 A，若它是小写字母，则把它变成 Z，若它是大写字母，不变即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main()
{
	string s;
	cin>>s;
	int len=s.size();
	int ans=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]>='0'&&s[i]<='9')
		{
			ans+='A'-s[i];
		}
		else if(s[i]>='a'&&s[i]<='z')
		{
			ans+=s[i]-'Z';
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：王逸辰 (赞：0)

# P10566 「Daily OI Round 4」Analysis 题解
## 前置芝士：
字符串操作，字符的 ASCII 码。
## 思路
由于输入只包含大写字母，小写字母和数字，又因为数字的 ASCII 码 小于 大写字母的 ASCII 码 小于 小写字母的 ASCII 码。

为了使花费最少，我们使用就近原则。

- 当这个字符是小写字母，我们用它减去最接近它的大写字母 Z。 

- 当这个字符是数字，我们就用最接近它的大写字母 A 减去它。 

最后累加即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	long long ans=0;
	for(int i=0; i<s.size(); i++){
		if(s[i]>='a'&&s[i]<='z')
			ans=ans+s[i]-'Z';
		else if(s[i]>='0'&&s[i]<='9')
			ans=ans+'A'-s[i];
	}
	cout<<ans<<endl;
	return 0;
}
``````

---

## 作者：iyka (赞：0)

### 题目大意
题目中已经说的十分清楚了，略。

### 求解方法
我们首先需要了解 ASCII 码表是什么，ASCII 码表是一套编码标准，它定义了二进制与字符的对应关系，在 ASCII 码表的编码下我们可以实现单个字符和二进制数字的转换，而在 c++ 中就体现为可以把单个字符转换为一个十进制数，比如字符 $A$ 就可以转换为 $(65)_{10}$，同时我们常见的单个字符与单个字符进行的直接比较就是把它们的 ASCII 码进行比较，如 ``'a'<'b'`` 这句就是在比较字符 $a$ 和 $b$ 的 ASCII 码的大小。

而在 ASCII 码表中，字符 $0 \sim 9$、$A \sim Z$、$a \sim z$ 都是连续的且递增的，所以我们要把一个字符串变成一个大写字符串，还要求变化的时间（也就是每次变换的 ASCII 码差值）最少，我们就采用贪心思维去思考一下，不难得出以下结论（设当前字符为 $a$，且为了说明方便，令 $|a|$ 为取字符 ``'a'`` 的 ASCII 码值）：
- 如果 $a<|A|$：则令 $a$ 变换为 ``'A'``，答案增加 $|A-a|$。
- 如果 $a>|Z|$：则令 $a$ 变换为 ``'Z'``，答案增加 $|a-Z|$。

在 c++ 中一个字符减去另一个字符，返回值就是它们 ASCII 码值的差值，在本题中也就是每次变换的时间。

### 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
int ans;
int main()
{
	cin>>str;
	for(int i=0;i<str.size();++i)
	{
		if(str[i]<'A')
			ans+='A'-str[i];
		else if(str[i]>'Z')
			ans+=str[i]-'Z';
	}
	cout<<ans;
	return 0; 
} 
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10566)
### 思路
想要让花费的时间更少，那么我们肯定是选择离这个字母或者数字最近的大写字母，如果这个字母本身就是大写字母，那么我们就不用再为了这个字母浪费时间了，而对于小写字母，这些小写字母的 ASCII 码都比每一个大写字母大，所以最接近的大写字母即为字母 $\texttt{Z}$，而对于每一个数字，这些数字的 ASCII 码都比每一个大写字母小，所以最接近的大写字母即为字母 $\texttt{A}$，将每一个字母或数字所用所用的时间相加即为答案。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;
	cin>>a;
	int ans=0;
	int c=a.length();
	for (int i=0;i<c;i++)
	{
		if (a[i]<'A')
		{
			ans=ans+(int)'A'-(int)a[i];
		}
		if (a[i]>'Z')
		{
			ans=ans+(int)a[i]-(int)'Z';
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：Hy13_xsm (赞：0)

## 题目分析

有一个字符串，对于其中每一个字母的变换，如果变换前 `ASCII` 码为 $a$，变换后为 $b$，那么变换的消耗为 $|a-b|$。问想要把给的字符串转换为全大写字母，至少要多少耗费。

## 题目解决

这种题就是对极端的思考。还是要分一下情况的。

- 如果一个字符 $x$ 的 `ASCII` 码小于 `A`，那么耗费至少是 $65-x$。（`A` 的 `ASCII` 码为 $65$）

- 如果一个字符 $x$ 的 `ASCII` 码大于 `Z`，那么耗费至少是 $x-90$。（`Z` 的 `ASCII` 码为 $90$）

- 如果一个字符 $x$ 本身就是大写字母，没必要变换。

## 总结

这道题就是一个贪心的思想，比较入门。

## 核心代码

```cpp
for(int i=0;i<s.size();i++)
{
	if(s[i]>='A'&&s[i]<='Z')continue;
	if(s[i]<'A')ans+=abs(s[i]-'A');
	else ans+=abs(s[i]-'Z');
}
//学习不是为了抄题解
```

---

## 作者：Vct14 (赞：0)

### 题意

你需要输出一个只包含大写字母的字符串，并使原字符串和输出字符串对应的两个字母的 ASCII 码之差尽量小。

### 思路

我们知道，数字的 ASCII 码小于大写字母的 ASCII 码，而大写字母的 ASCII 码小于小写字母的 ASCII 码。那么我们把所有数字都转换为 ASCII 码最小的大写字母 `A`，把所有小写字母都转换为 ASCII 码最大的大写字母 `Z` 即可。

我们可以使用 `isdigit()` 和 `islower()` 来分别判断一个字符是否是数字或小写字母。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	string s;cin>>s;int t=0,len=s.length();
	for(int i=0; i<len; i++){
		if(isdigit(s[i])) t+='A'-s[i];
		if(islower(s[i])) t+=s[i]-'Z';
	}
	cout<<t;
	return 0;
}
```

---

## 作者：Seqfrel (赞：0)

# 题解：P10566 「Daily OI Round 4」Analysis

#### 考查知识点：字符串。

## 题意分析

设变化之前字符的 ASCII 码为 $a$，变化之后字符的 ASCII 码为 $b$，则变化消耗 $|a-b|$ 的时间。求整个字符串全部变换为大写字母的时间总和。

## 解题思路

大写字母的 ASCII 码为从 $65$ 到 $90$，而其他字符的 ASCII 码则要么比 $65$ 小，要么比 $90$ 大。根据题意，每个非大写字母只需要变换为任意一个大写字母即可，所以对于非大写字母，我们要变换为 ASCII 码最接近的大写字母，而 ASCII 码最接近的大写字母一定是 A 或 Z。对于大写字母，因为它们已经是大写字母了，所以不需要变换。我们需要遍历这个字符串，并对每个字符进行分类处理。

设所需时间总和为 $t$，第 $i$ 个字符的 ASCII 码为 $a_i$，那么如果 $a_i > 90$，$t$ 就加上 $a_i-90$；如果 $a_i < 65$，$t$ 就加上 $65-a_i$；其他情况也就是第 $i$ 个字符已经是大写字母时 $t$ 保持不变，即可用时最少。

## 代码实现

```cpp
#include<iostream>
#include<string>
using namespace std;
string s;
int l,t;
int main(){
	cin>>s;
	l=s.size();
	for(int i=0;i<l;i++){
		if(s[i]>'Z') t+=int(s[i])-int('Z');//使用 int 类型强转获取 ASCII 码
		else if(s[i]<'A') t+=int('A')-int(s[i]);
	}
	cout<<t;
	return 0;
} 
```

时间复杂度 $O(n)$，其中 $n$ 是字符串的长度。

## 注意事项

string 类型下标默认从 $0$ 开始。

---

## 作者：_dbq_ (赞：0)

## 前言
还没有读题的同学可以点击[这里](https://www.luogu.com.cn/problem/P10566)读题。

## 目标
将不是大写字母的字符变为大写字母，使 ASCII 码之差最小。

## 思路
定义 $a_i$ 为 $s_i$ 的 ASCII 码。

如果 $65 \le a_i \le 90$，则 $s_i$ 为大写字母，不用变化。

如果 $a_i \le 65$，则 $s_i$ 变成 A 消耗的时间最少，为 $65-a_i$。

如果 $a_i \ge 90$，则 $s_i$ 变成 Z 消耗的时间最少，为 $a_i-90$。

## 代码
```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
inline auto read(){//快读
    auto x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
	string s;
	LL ans=0;//记录答案
	cin>>s;
	for(int i=0;i<s.size();i++)
		if(s[i]<65) ans+=65-s[i];//ASCII码比A小
		else if(s[i]>90) ans+=s[i]-90;//ASCII码比Z大
	cout<<ans;//输出答案
   return 0;
}
```

## 提示
[ASCII码对照表](https://cdn.luogu.com.cn/upload/image_hosting/aahvao2h.png)

---

## 作者：Flaw_Owl (赞：0)

# P10566 「Daily OI Round 4」Analysis 题解

原题链接：[P10566 「Daily OI Round 4」Analysis](https://www.luogu.com.cn/problem/P10566)

## 摘要

简单的模拟。

## 题目分析

如果对 ASCII 码比较熟悉，就会知道数字 `0`，大写字母 `A`，小写字母 `a` 的 ASCII 码分别是 $48,65,97$。也就是说，如果我们要把数字和小写字母都变为大写字母，并且使变化的 ASCII 码最小，那么数字比较靠近 `A`，小写字母比较靠近 `Z`，这样变化即可。代码实现比较简单，只需简单模拟。对数据进行估算，最大变化为 `z` 到 `Z` 是 $32$，字符串最长为 $10^5$，不会爆 `int`。~~但是为了安全还是写了 `long long`~~。

## 参考代码

```cpp
#include <iostream>
#include <cctype>
#define ll long long

using namespace std;

string s;
ll ans;

int main()
{
    cin >> s;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
            continue;
        else if (s[i] >= 'a' && s[i] <= 'z')
            ans += s[i] - 'Z';
        else
            ans += 'A' - s[i];
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Double_Light (赞：0)

首先显然如果本身是大写字母就不需要变。

接下来设当前的字符为 $c$，分类讨论：

- 如果 $s$ 是 $0$ 到 $9$：`ASCII` 码小于大写字母，而大写字母中 `ASCII` 码最小的字符是 `A`，所以把 $c$ 变成 `A` 即可。

- 如果 $s$ 是小写字母：`ASCII` 码大于大写字母，而大写字母中 `ASCII` 码最大的字符是 `Z`，所以把 $c$ 变成 `Z` 即可。

对 $s$ 每一位依次做上述变换即可。

```cpp
#include<iostream>
using namespace std;
string s;
int ans;
int main(){
	cin>>s;
	int n=s.size();
	for(int i=0;i<n;i++){//注意循环范围
		if(s[i]<'A')ans+='A'-s[i];
		if(s[i]>'Z')ans+=s[i]-'Z';
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

