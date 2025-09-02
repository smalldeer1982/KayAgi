# Shifts and Sorting

## 题目描述

Let's define a cyclic shift of some string $ s $ as a transformation from $ s_1 s_2 \dots s_{n-1} s_{n} $ into $ s_{n} s_1 s_2 \dots s_{n-1} $ . In other words, you take one last character $ s_n $ and place it before the first character while moving all other characters to the right.

You are given a binary string $ s $ (a string consisting of only 0-s and/or 1-s).

In one operation, you can choose any substring $ s_l s_{l+1} \dots s_r $ ( $ 1 \le l < r \le |s| $ ) and cyclically shift it. The cost of such operation is equal to $ r - l + 1 $ (or the length of the chosen substring).

You can perform the given operation any number of times. What is the minimum total cost to make $ s $ sorted in non-descending order?

## 说明/提示

In the first test case, you can choose the whole string and perform a cyclic shift: 10 $ \rightarrow $ 01. The length of the substring is $ 2 $ , so the cost is $ 2 $ .

In the second test case, the string is already sorted, so you don't need to perform any operations.

In the third test case, one of the optimal strategies is the next:

1. choose substring $ [1, 3] $ : 11000 $ \rightarrow $ 01100;
2. choose substring $ [2, 4] $ : 01100 $ \rightarrow $ 00110;
3. choose substring $ [3, 5] $ : 00110 $ \rightarrow $ 00011.

 The total cost is $ 3 + 3 + 3 = 9 $ .

## 样例 #1

### 输入

```
5
10
0000
11000
101011
01101001```

### 输出

```
2
0
9
5
11```

# 题解

## 作者：lihongqian__int128 (赞：7)

# CF1969B Shifts and Sorting题解
[题目传送门](https://www.luogu.com.cn/problem/CF1969B)

首先，我们可得一个贪心的思路：每次遇到 $0$ 就把它放到最前面一个 $1$ 的前面。证明见下：

若遇到的 $0$ 没有及时提到前面去，设位置为 $pos_1$，设下一个 $0$ 的位置为 $pos_2$，则如果在位置 $pos_1$ 上的 $0$ 没有在在位置 $pos_2$ 上的 $0$ 前面提到前面去，则此时答案 $\ge$ 前面的答案 $+$ 前面连续 $1$ 的个数 $\times 2 + 1>$ 原答案。

$\mathbb{CODE}$：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std ;
int t , a , c , ans ;
string s ;
void work()
{
    ans = 0 , c = 0 ;
    cin >> s ;
    for(int i = 0 ; i < s.size() ; i++)
    {
        if(s[i] == '1')    c++ ;
        else if(c != 0)  ans += c + 1 ;
    }
    cout << ans << '\n' ;
    return ;
}
signed main()
{
    cin >> t ;
    while(t--)  work() ;
    return 0 ;
}
```

---

## 作者：fuchenxi666 (赞：3)

## 题意
给你一个字符串，由 $0$ 或 $1$ 组成。

你可以将这一个字符串的最后一个字符移到第一个位置，但是，你要花费等于所选子串长度的代价。

你要让所有的 $1$ 都移到最后面，请问最少要花费多少代价？

## 思路
 只需模拟即可。
 
 用建立两个变量表示目前所移动的字符串的左端点与右端点。一先找到第一个 $1$ ，给左端点和右端点赋值后，接下来重复以下过程：左指针向后移动一位如果遇到 $1$ ，左端点将加 $1$ ；反之，将总代价增加 $r−l+2$，然后将左，右端点都加 $1$ 。如此扫完整个序列求出总代价。
 
 因为把 $1$ 移到最后面就是把 $0$ 移到最前面，所以我们也可以反着写（我就是这么写的）。
 
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
		{
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
signed main()
{
	cin>>n;
	while(n--)
	{
		int ans=0,cnt=0;
		string s;
		cin>>s;
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='1')
			{
				cnt++;
			} 
			else if(cnt!=0)
			{
				ans+=(cnt+1);
			} 
		}
		cout<<ans<<endl;
	}
    return 0;
}
```

---

## 作者：_WHITE_NIGHT_ (赞：3)

一道题究竟是什么颜色，得看你把它当成什么颜色的题来做。

#### 题目大意|翻译

> 我们定义某一个字符串 $s$ 的循环移动为从 $s_1 s_2 \dots s_{n-1} s_{n}$ 到 $s_{n} s_1 s_2 \dots s_{n-1}$ 的一种变换。换句话说，就是将最后一个字符 $s_n$ 放在第一个字符之前，同事将所有其他字符向后移动。

> 给你一个二进制字符串 $s$ (一个只由 $0$ 或 $1$ 组成的字符串)。

> 在一次操作中，你可以选择任意一个子串 $s_l s_{l+1} \dots s_r$ ($1 \le l < r \le |s|$) 并且循环移动它。 这种操作的代价为 $r - l + 1$ (或者说是所选子串的长度)。

> 你可以执行任意次数的操作。要使 $s$ 非降序排序，**总**成本最小是多少？

说人话，这道题的题意就是：给你一个只由 $0$ 和 $1$ 构成的序列，你可以花费等于所选子串长度的代价将这一个子串的最后一个字符移到第一个。让你将所有的 $1$ 移到最后面，求代价最小是多少？

------------
#### 思路分析

其实，这就是一道很普通的模拟题……

显然的，对于一个序列最少的操作次数明显是从前往后将**分离开的** $1$ 移动到一起，再向序列尾部移动。

例如：

原序列 $1001010$
将从左向右数（以下序数词皆为从左往右）第一个和第二个 $1$ 挪到一起，我们可以交换第一个数和第二个数，它就变成了：

$0101010$

同理，我们可以将前两个 $1$ 移到一起：

$0011010$

接下来，我们就要将两个一一起向后移动，我们可以将两个一后的零前置到两个一最前面，也就是将第五个数字移动到原本第三个数字的位置：

$0001110$

同理，完成下一步操作：

$0000111$

通过一次模拟，我们就可以很清楚地了解如何操作了。

以上只是我个人在初见这道题时的猜想，但如何证明？（过程不严谨处，请感性理解）（ps:其实假如不证明的话这道题做了和没做没什么区别……）

首先，我们假设一个序列长为 $d$，第一个 $1$ 在第 $p_1$ 的为位置，共有 $t$ 个 $1$，那么，第一个 $1$ 要移动到指定位置，也就是 $d - t + 1$ 处，不考虑其他情况，就需要移动 $d - t - p_1 + 1$ 次。推广一下，我们将第 $i$ 个 $1$ 移动到它相应的位置，就需要移动 $d - t - p_i + i$ 次。所以总共，我们需要移动的总次数为 $\sum_{i = 1}^t{d - t - p_i + i}$ 次。

如果我们暴力移动，也就是只移动相邻两个，我们所花费的总代价为 $2 \times \sum_{i = 1}^t{d - t - p_i + i}$。但是这样明显可以优化。因为当我们有连续的 $k(k \ge 2)$ 个 $1$，我们就可以将连续的几个 $1$ 后的那个 $0$ 花费 $k + 1$ 的代价将所有的 $1$ 向后移动了一次，相比于暴力移动的 $2k$ (代公式运算的结果)的代价明显小得多。总共节省的代价为 $k - 1$。于是，我们的思路就很清晰了。

------------
#### 写法与代码
~~ps:由于本题代码太短，没什么可讲的，所以不放代码了（懒得加注释）~~

- 第一种：首先，可以明确的是，可以模拟。用建立两个变量 $l$ 和 $r$ 表示目前所移动的 $1$ 串的左端点与右端点。一个指针从前向后扫，先找到第一个 $1$，给 $l$ 和 $r$ 赋值后，接下来重复以下过程：先指针向后移动一位如果遇到 $1$ ，将 $r$ 增大 $1$；若遇到 $0$，将总代价增加 $r - l + 2$，然后将 $l$ 和 $r$ 都增大 $1$。如此扫完整个序列求出总代价。理论效率 $O(kn)$。$k$ 为一个较小的常数。

- 第二种：就是以上较为严谨的证明的办法：首先计算出暴力移动的总代价 $2 \times \sum_{i = 1}^t{d - t - p_i + i}$，依然是指针从前向后扫，将扫过的 $1$ 记录下来，合并到一起（其实记录扫过 $1$ 的个数即可，无需真的交换位置）再依次减去能够节省的总代价 $k - 1$（$k$为目前扫到过的 $1$ 的个数。记得要重复减！！！因为同一个 $1$ 的代价可能会被节省多次！！！）。如此扫完整个序列即可。理论效率 $O(kn)$。$k$ 为一个较小的常数。

以上是两种代码写法。如果不考虑严谨证明，第一种方法容易想到，但是希望大家不要知其然不知其所以然，就放弃更加深入的思考。个人认为第二种写法虽然更加难想，但是更能体现本题的数学美，所以虽然有点麻烦，还是介绍给大家。如果只需通过本题，结论很好猜，但是若严谨证明，相信大家都能上一个新的台阶。

若有错误，望私信或者评论区指出，十分感谢~

完结撒花~

---

## 作者：liuhongyang123 (赞：1)

# 题目大意

有 $T$ 组数据，每组数据给你一个 $01$ 串，你可以调换字符串里任意两个位置上的数，代价为这两个数的距离 $+1$。

求最小代价使字符串所有 $0$ 前，$1$ 在后。

# 解法

直接模拟，遇到一个 $0$ 就和前面第一个 $1$ 调换（如果前面有的话）。

具体细节全在代码里。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans,cnt,bj,T;
string s;
signed main(){
	cin>>T;
	while(T--){
		cnt=bj=ans=0;
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='1') cnt++,bj=1;
			else if(bj) ans+=cnt+1;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
### 完结散花

---

## 作者：Dream_Mr_li (赞：1)

## Problem

我们将某个字符串 $ s $ 的循环移位定义为将 $ s_1 , s_2 \dots s_{n-1} , s_{n} $ 转变为 $ s_{n} , s_1 , s_2 \dots s_{n-1} $ 的过程。换句话说，你将最后一个字符 $ s_n $ 放到第一个字符的位置，并将所有其他字符向右移动。

给定一个二进制字符串 $ s $（只包含 0 和/或 1）。

在一次操作中，你可以选择任意子串 $ s_l , s_{l+1} \dots s_r $（$ 1 \le l < r \le |s| $），并对其进行循环移位。此操作的代价等于 $ r - l + 1 $（即所选子串的长度）。

你可以任意次数地执行给定的操作。使得 $ s $ 按非递减顺序排列的最小总代价是多少？

## Solution

从题目描述中可以得出，输入是一个只用 `0` 和 `1` 组成的字符串，让你把它变成所有 `0` 在前面，所有 `1` 在后面的字符串，所以我们可以很容易的想出思路：

- 如果 $s_i$ 是 `0`，就将它与从左到右的第一个 `1` 互换。

按此操作步骤算出最后能量值即可。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
#define str string
using namespace std;
const int N=1e5+10;
int t;
signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		int ans,l,r;
		str s;
		cin>>s;
		ans=l=0;
		r=s.size();
		for(int i=0;i<s.size();i++){
			if(s[i]=='0'){
				while(s[l]=='0'&&l<i){
					l++;//找到从左到右的第一个1
				}
				if(s[l]!=s[i]){//如果找到了1，就互换
					swap(s[l],s[i]);//互换
					ans+=i-l+1;//统计能量值
				}
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
} 
```

---

## 作者：cheng2010 (赞：0)

# Shifts and Sorting
## 题意
给你一个字符串 $s$，每次可以选两个数：$l$ 和 $r$，并把 $s_r$ 放到 $s_l$ 前面，代价为 $r-l+1$。求把 $s$ 变为 $000 \ldots 111$ 的代价。

## 思路
遍历 $s$，如果遍历到一个 $1$，$cnt$ 加一，如果遍历到个 $0$，就把他提到 $1$ 的前面（如果有的话），代价就是 $cnt+1$。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		string a;
		int cnt=0,bz=0,sum=0;
		cin>>a;
		for(int i=0;i<a.size();i++)if(a[i]=='1') cnt++,bz=1;else if(bz) sum+=cnt+1;
		cout<<sum<<'\n';
	}
	return 0;
}
```

---

## 作者：keep_shining (赞：0)

我又来水题解了！

## 题意：
有 $T$ 组数据，每组数据给你一个包含 $0$ 和 $1$ 的字符串 $S$，现在你可以对其任意的子序列做反转，反转次数不限，反转代价为 $r-l+1$，现在求让其变成升序序列的最少代价。

## 思路：
虽然说是升序序列，其实就是把所有的 $0$ 放到前面，那很明显，每遇到一次 $0$ 都要翻转一次。

那**代价**是什么呢？这显然跟**前面的 $1$ 的个数**有关。

- 如果前面没有 $1$，显然没有代价。
- 如果前面共有 $k$ 个 $1$，那代价就是 $k+1$。

#### 警示：需要开 long long！

## AC code:
```cpp
#include<bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false);cin.tie();cout.tie();
#define Endl endl
#define itn int
#define For(i,a,b) for(register int i=a;i<=b;i++)
#define endl '\n'

const int N=1e6+5;
const int M=2e3+5;

int read()
{
	register int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

int main()
{
	fst
	int t;
	cin>>t;
	while(t--)
	{
		long long a,b;//b是前面1的个数，a是答案
		string s;
		cin>>s;
		a=b=0;
		For(i,0,s.size()-1)
		{
			if(s[i]=='1')b++;//统计1的个数
			else if(b!=0)a=a+b+1;//如果是0且前面有1，则加上代价
		}
		cout<<a<<endl;
	}
    return 0;
}

```

---

## 作者：zhangyuhaoaa (赞：0)

## 题意

给定一个只含有 $0$ 和 $1$ 的字符串，让你经过几次操作使得这个字符串非递减排序。

每一次操作可以让一个字符串 $a_l,a_{l+1},a_{l+2}\dots a_{r-1},a_r$ 变成 $a_r,a_l,a_{l+1},a_{l+2}\dots a_{r-1}$。他的费用为 $r-l+1$。

## 思路

这道题的思路非常容易想，我们可以把所有的 $0$ 字符都一道前面，这样的费用就是它中间夹着的 $1$ 的个数。

## code

```cpp
#include <bits/stdc++.h>
#define re register
#define il inline
#define int long long
#define endl '\n'
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int P = 998244353;
const int INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e6 + 5;

int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}

string s;
int ans = 0;
int cnt = 0;

void work() {
	cin >> s;
	ans = 0, cnt = 0;
	for (int i = 0; i < s.size(); ++ i ) {
		if (s[i] == '1') {
			cnt ++;
		} else {
			if (cnt != 0) {
				ans += (cnt + 1);
			}
		}
	}
	cout << ans << endl;
}

signed main() {
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    fst;

	int t;
	cin >> t;
	while (t --) {
		work();
	}

    return 0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1969B)
## 题目意思
给你一个 $01$ 串 $s$，每次操作你可以使 $s_l s_{l+1}\dots s_{r-1}s_{r}$ 变为 $s_{r}s_ls_{l+1}\dots s_{r-1}$，代价是 $r-l+1$，求至少几次能使 $s$ 变为 $000\dots0111\dots1$。
## 解题思路
直接模拟。

遍历串 $s$，如果遍历到一个 $1$，计数器加一；如果遍历到一个 $0$，就把他提到 $1$ 的前面（如果有的话），代价就是当前 $1$ 的个数加上 $1$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		string a;
		int s=0,f=0,sum=0;
		cin>>a;
		for(int i=0;i<a.size();i++)
			if(a[i]=='1')s++,f=1;
			else if(f)sum+=s+1;
		cout<<sum<<'\n';
	}
	return 0;
}

```

---

## 作者：zxy1919810 (赞：0)

# CF1969B Shifts and Sorting 题解
[洛谷传送门。](https://www.luogu.com.cn/problem/CF1969B)

[CF传送门。](https://codeforces.com/problemset/problem/1969/B)
## 题意
让我们将对于字符串 $s$
 的一次操作定义为将最后一个字符放在第一个字符之前，同时将所有其他字符向右移动。

您将得到一个只有 $0$ 和 $1$ 组成的字符串 $s$。

在一次操作中，您可以选择任意子串并对他它进行一次操作。这种操作的代价等于或所选子串的长度。

您可以执行任意次数的操作。要使 $s$
 按非降序排序，最小代价**总和**是多少？
## 思路
可以遍历字符串 $s$，如果第 $i$ 个字符 $s_i$ 是 $0$，则可以进行操作把它移动到所有 $1$ 前面，显然 **TLE**。
## 优化
我们可以使用一个计数器 $cnt$ 记录数字 $1$ 的个数，在遇到 $0$ 时，直接让代价和 $ans$ 增加 $cnt$，因为在操作时，$0$ 也在字符串里，所以 $ans$ 要再增加 $1$。**特殊地**，$cnt$ 为 $0$ 时答案不增加。
## code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
signed main(){
	cin>>t;
	while(t--){
		string s;
		int ans=0,cnt=0;
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='1')cnt++;
			else if(i!=0)ans+=(cnt!=0?cnt+1:0ll);
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：junee (赞：0)

# CF1969B 题解

## 题目分析

题目要求把一个只包含 $0,1$ 的串，经过若干次操作后将其变为 $0$ 在前 $1$ 在后的串。

我们可以发现我们一次性最多只能把 $1$ 往后移动一位。当我们从左到右交换时，我们会发现，其实我们都是将一个前面有若干个 $1$，最后一个 $0$ 的串操作，操作代价就是这个前面 $1$ 的个数加一。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long LL;
const int N=2e5+10;
int T;
string a;
int main(){
	cin>>T;
	while(T--){
		LL cnt=0,ans=0;
		cin>>a;
		for(int i=0;i<a.length();i++){
			if(a[i]=='1')cnt++;
			else if(cnt!=0)ans+=(cnt+1);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：_dbq_ (赞：0)

## 前言
没有读题的同学可以点击[这里](https://www.luogu.com.cn/problem/CF1969B)先读题。

## 思路
由于只有 0 和 1 两种数字，所以我们应把 0 往前放，所以只要碰到 0 就移动，把它移到第一个。这样 0 就能放在前面，长度就是中间夹着的 1 的个数。

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
	int T=read();
	while(T--)//多组数据
	{
		LL ans=0,cnt=0;//ans是答案，cnt是1的个数
		string s;
		cin>>s;//读入
		for(int i=0;i<s.size();i++)//从前往后扫
		{
			if(s[i]=='1') cnt++;//统计1的个数
			else if(cnt!=0) ans+=(cnt+1);//长度是1的个数+1
		}
		cout<<ans<<endl;//输出
	}
    return 0;
}
```

---

