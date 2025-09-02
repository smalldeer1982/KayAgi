# Ranom Numbers

## 题目描述

No, not "random" numbers.

Ranom digits are denoted by uppercase Latin letters from A to E. Moreover, the value of the letter A is $ 1 $ , B is $ 10 $ , C is $ 100 $ , D is $ 1000 $ , E is $ 10000 $ .

A Ranom number is a sequence of Ranom digits. The value of the Ranom number is calculated as follows: the values of all digits are summed up, but some digits are taken with negative signs: a digit is taken with negative sign if there is a digit with a strictly greater value to the right of it (not necessarily immediately after it); otherwise, that digit is taken with a positive sign.

For example, the value of the Ranom number DAAABDCA is $ 1000 - 1 - 1 - 1 - 10 + 1000 + 100 + 1 = 2088 $ .

You are given a Ranom number. You can change no more than one digit in it. Calculate the maximum possible value of the resulting number.

## 说明/提示

In the first example, you can get EAAABDCA with the value $ 10000-1-1-1-10+1000+100+1=11088 $ .

In the second example, you can get EB with the value $ 10000+10=10010 $ .

## 样例 #1

### 输入

```
4
DAAABDCA
AB
ABCDEEDCBA
DDDDAAADDABECD```

### 输出

```
11088
10010
31000
15886```

# 题解

## 作者：XSean (赞：9)

## C: Ranom Numbers

[C - Ranom Numbers](https://codeforces.com/problemset/problem/1841/C)

本题最暴力的方法就是将每一个位置都改变取最大值，此方法是 $O(n^2)$ 的。

考虑是否可以只改变几个位置，答案是可以的。

定义：一个字母小是字典序小，大同理。

先给结论：

- 一个字母若要**变大**，只需要改这个字母**最左边**的即可。
- 一个字母若要**变小**，只需要改这个字母**最右边**的即可。

---

## 结论证明：

严谨证明较复杂，不过思路很清晰，只证结论 1 ($A_1$ 那一列永远不劣于 $A_2$ 那一列)，结论 2 同理可证。

证：![](https://cdn.luogu.com.cn/upload/image_hosting/gtjlq7bk.png)

就以字母 $A$ 为例：

设**中间**的字母的最大值为 $X$，$A_1,A_2$ 可以变为以下几种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/vyolaa3n.png)

先证 $A_1$ 的情况 1 是不优于情况 2 的(以下都是简单文字描述)：首先明确一点：改变一个字母只会影响从**第一个字母到其的贡献**。不管 $A$ 一开始对整个字符串的贡献是正是负，变为情况 2 贡献都是增加了，且**左**的贡献该是负还是负该是正还是正，所以 $A_1$ 的情况 1 不优于情况 2，$A_2$ 同理。

现在我们只需要知道 $A_1,A_2$ 的后两种情况的关系即可。

为了阅读的方便，以下的“优于”和“更优”都是**“不劣于”**的意思，除“一定优于”外。

先证 $A_1,A_2$ 的情况 2 是优于 $A_2$ 的情况 2 的：很显然两个情况对**左**的贡献是相同的，并且两个 $A$ 字母上升到 $X$ 对整体的贡献也是相同的，意思只有**中间**是不同的，那么**中间**大于 $A$ 小于 $X$ 的字母的贡献就会变成负号，得证。$A_1$ 的情况 3 是优于 $A_2$ 的情况 3 同理。

再证如果 $A_1$ 的情况 2 是比 $A_1$ 的情况 3 更优的，那么 $A_2$ 的情况 2 也比 $A_2$ 的情况 3 更优：想象一下如果 $A_1$ 的情况 2 是比 $A_1$ 的情况 3 更优的，其实就是**左**中字母 $X$ 较多(多多少？只需**感性理解**这个就行，其实就是从情况 2 到 3 多出来的 $A_1$ 自身上升的贡献比不上**左**中字母 $X$ 提供的负贡献)，同理若连 $A_1$ 和**中间**的区域的负贡献都不看，$A_2$ 的情况 2 也比 $A_2$ 的情况 3 更优。

最后证 $A_1$ 的情况 3 比 $A_2$ 的情况 2 更优(也是本题较难证明的一部分)：首先证这个的条件是就 $A_1$ 的情况 2，3 而言 3 更优和 $A_2$ 的情况 2，3 而言 2 更优**同时满足**。由条件 1 可知(以下都是同上的**感性理解**)：**左**中字母 $X$ 提供的负贡献比不上(或者说不大于)从情况 2 到 3 多出来的 $A_1$ 自身上升的贡献。就先假设 $X = B$，则再假设 $>X = C$，你没看错就是 $>X$，易知 $C = 10B = B+ 9B$，$B$ 是情况 2 的贡献，$9B$ 可以形象的成为 $\Delta$。由条件 1 可知**左**中的 $B$ 的个数小于等于 $9$，就设 $A = 1,B = 10\cdots$ 以此类推。因此 $A_1$ 的情况 3 的贡献 $\ge B-A=10-1=9$。先在考虑 $A_2$ 的情况 2，因为**中间**部分可能会有小于 $B$ 的，所以 $A_2$ 的情况 2 的贡献 $\le B-A=10-1=9$，$X$ 为其他字母的时候也同理。所以 $A_1$ 的情况 3 比 $A_2$ 的情况 2 更优。

整理上述 4 个证明可知：$A_1,A_2$ 的情况 1 是不优于情况 2 的，所以只需要知道 $A_1,A_2$ 的后两种情况的关系即可。又知道 $A_1,A_2$ 的情况 2 和 3 是分别优于 $A_2$ 的情况 2 和 3 的，又知道了如果 $A_1$ 的情况 2 是比 $A_1$ 的情况 3 更优的，那么 $A_2$ 的情况 2 也比 $A_2$ 的情况 3 更优，最后知道了 $A_1$ 的情况 3 比 $A_2$ 的情况 2 更优，就证毕了！

---

## 代码实现：

- 计算整个字符串的值，从后往前。

- 为了方便，因为已经知道了两条结论，所以直接对 10 个位置进行更换为 $A$ 到 $E$ 的暴力修改。

时间复杂度：$O(n)$。

**核心代码：**

```cpp
const int N = 2e5 + 10;
char str[N];
int ch[5] = {1, 10, 100, 1000, 10000};
int ans, L[5], R[5];
void init(){
	ans = -inf;
	mms(L, 0), mms(R, 0);
}
int calc(int len){
	int res = 0;
	char maxc = 'A';
	pre(i, len, 1){
		int c = str[i] - 'A';
		if(maxc > str[i]) res += -ch[c];
		else{
			maxc = str[i];
			res += ch[c];
		}
	}
	return res;
}
int main(){
	int T; rd(T);
	while(T--){
		sf("%s", str + 1);
		int len = strlen(str + 1);
		init();
		rep(i, 1, len){
			if(!L[str[i] - 'A']) L[str[i] - 'A'] = i;
			R[str[i] - 'A'] = i;
		}
		rep(i, 0, 4){ //替换前 
			if(!R[i]) continue; //LR都行 
			rep(j, 0, 4){ //替换后 
				//替换L 
				char temp = str[L[i]];
				str[L[i]] = 'A' + j;
				ans = max(ans, calc(len));
				str[L[i]] = temp;
				//替换R 
				temp = str[R[i]];
				str[R[i]] = 'A' + j;
				ans = max(ans, calc(len));
				str[R[i]] = temp; 
			}
		}
		prf("%d\n", ans);
	}
	return 0;
}
```

**[完整代码](https://www.luogu.com.cn/paste/onku53id)**

---

## 作者：jhdrgfj (赞：9)

## 题目大意

定义 $\texttt{A}$ 的值为 $1$，$\texttt{B}$ 的值为 $10$，$\texttt{C}$ 的值为 $100$，$\texttt{D}$ 的值为 $1000$，$\texttt{E}$ 的值为 $10000$。

对于一个字符串，其中每个字符在右边没有比它的值大的字符时带来正贡献，否则带来负贡献。

现在给你 $T$ 个字符串 $s$，对于每个 $s$，你可以修改至多一个字符，请你最大化修改后字符串的值，并输出它。

数据保证 $\sum |s| \le 10^5$。

## 解法

首先来讨论修改同一种字符时的最佳方案。

如果要将一个字符改大，那么修改的字符必定是这种字符**最左边**的那一个。感性理解一下，修改同一种字符带来的贡献是相等的，而修改非最左位置的字符只会使得有更多的字符变为负贡献，所以修改最左边的更优。

同理可证，如果要将一个字符改小，那么修改的字符必定是这种字符**最右边**的那一个。因为当尝试修改一种字符非最右的一个来试图让负贡献转正时，那些负贡献的字符一定还会因为最右边的同种字符而继续产生负贡献。

接下来就简单了，开两个数组 $f$ 与 $l$ 分别储存每个字符第一次和最后一次出现的位置，然后枚举每一个字符修改即可。这样能让原本 $O(n^2)$ 的时间复杂度降为 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;	
char s[200005];
long long v(long long siz){
	char m='A';
	long long ans=0;
	for (int i=siz-1;i>=0;i--){   //求字符串的值
		if (s[i]<m){
			ans-=pow(10,s[i]-'A');
		}
		if (s[i]>=m){
			m=s[i];
			ans+=pow(10,s[i]-'A');
		}
	}
	return ans;
}
int main() 
{
    cin>>t;
    while (t--){
    	scanf("%s",&s);
    	long long siz=strlen(s),fa[6]={},la[6]={},ans=-2000000001;  //这里的 ans 要初始化为负数，因为可能存在答案为负数的情况。
	//fa 储存每个字符第一次出现的位置，la 储存最后一次出现的位置。
    	for (int i=siz-1;i>=0;i--){
            if (!fa[s[i]-'A']){
                fa[s[i]-'A']=i;
            }
            la[s[i]-'A']=i;   //更新 fa 与 la
		}
        for (int i=0;i<5;i++){
            for (int j=0;j<5;j++){
                char y=s[fa[i]];   //用 y 来临时储存 s[i]，以便修改后复原
                s[fa[i]]='A'+j;
                ans=max(ans,v(siz));
                s[fa[i]]=y;
                y=s[la[i]];
                s[la[i]]='A'+j;
                ans=max(ans,v(siz));
                s[la[i]]=y;
            }
        }
		cout<<ans<<endl;
	}
}
```


---

## 作者：EuphoricStar (赞：5)

先反转 $s$ 串，然后考虑 dp，设 $f_{i, j, 0/1}$ 为考虑了 $[1, i]$，前缀最大值为 $j$，是否修改过字符的最大得分。

转移讨论是否在这个位置修改即可。

时间复杂度 $O(n)$。

[code](https://codeforces.com/contest/1841/submission/209853503)

---

## 作者：一扶苏一 (赞：3)

## Description
Ranom Number 是一个字符串，这个字符串只含字母 $\texttt A \sim \texttt E$。$\texttt{A}$ 的值是 $1$，$\texttt{B}$ 的值是 $10$，$\texttt{C}$ 的值是 $100$，$\texttt{D}$ 的值是 $1000$，$\texttt{E}$ 的值是 $10000$。

这个串的值按如下规则计算：如果一个字母的右侧没有值**严格大于**它的字母，那么它对串的值贡献为正的该字母的值，否则贡献为负的该字母的值。一个串的值就是把所有字母的贡献加起来。

例如，$\texttt{DAAABDCA}$ 的值是 $ 1000 - 1 - 1 - 1 - 10 + 1000 + 100 + 1 = 2088 $。

现在，给定一个 Ranom Number，你可以把它的**不超过一个**的字符改为其它的 $\texttt A \sim \texttt E$ 之间的字符，求你能得到的新 Ranom Number 的值最大可能是多少。

多组数据，输入串的总长度不超过 $2 \times 10^5$。

## Analysis

在本文中，如果一个字母的右侧全都是**严格小于**它的数，我们称这个数是串的一个『后缀最大值』。显然一个串的后缀最大值不超过 $5$ 个。

考虑枚举每个位置，尝试把它改成别的字母。讨论一下，对于一个位置的字母 $x$，存在把它的值改大和改小两种情况：

- 改小：
  + 如果 $x$ 本身是个后缀最大值，把它改小可能会让前面一些数的贡献由负变正，这样的改变可能是合理的。因为后缀最大值一共只有五个，可以枚举这些后缀最大值，再枚举变成了什么数，然后 $O(|s|)$ 地暴力计算新串的值即可。
  + 如果 $x$ 不是后缀最大值，把 $x$ 改小没有意义：如果 $x$ 本身贡献是正的，把 $x$ 改小会让 $x$ 的贡献减小，同时因为 $x$ 右边还有一个等于 $x$ 的数，所以把 $x$ 改小不会让 $x$ 左边的数贡献由负变正，这是不优的；如果 $x$ 本身贡献是负的，把 $x$ 改小得到的收益不会大于把等于 $x$ 的后缀最大值改小得到的收益，因为在都改成相同的字符的情况下，改后缀最大值可能会让其他数的贡献变大。
  + 例如，对于串 $\texttt {BAAAAAAAAAAB}$，把第二个 $\texttt B$ 改小的收益比把第一个 $\texttt B$ 改小的收益高，因为他会让它左侧的 $\texttt A$ 的贡献由负变正；对于串 $\texttt {BAAAAAAAAAABE}$，把第二个 $\texttt B$ 改小的收益仍然不低于把第一个 $\texttt B$ 改小的收益，即使两个 $\texttt B$ 本身的贡献都是负的。
- 改大：
  + 如果 $x$ 是个后缀最大值，同样枚举改成什么并直接暴力重新算串的值即可。这部分和改小的第一部分加起来，暴力计算的次数不会超过 $25$ 次。
  + 如果 $x$ 不是后缀最大值，考虑把 $x$ 改成 $y > x$，注意到只有当 $y$ 自身贡献一定是正，也就是右侧没有大于它的数时修改才有意义，此时考虑整个串的值的变化：$x$ 右侧的数不会受影响；$x$ 左侧本身小于 $x$ 的数，贡献本身为负，修改后还是为负；$x$ 左侧介于 $[x, y - 1]$ 之间的数，本身如果贡献为负，修改后还是为负，本身如果贡献为正，修改后变为负；$x$ 左侧本身大于等于 $y$ 的数不受影响。综合来看，把 $x$ 变成 $y$ 会让 $x$ 左侧在 $[x, y - 1]$ 范围内正贡献的数贡献变为负的。因为 $[0, x - 1]$ 范围内的数本身全部一定是负贡献，所以其实影响就是把 $x$ 左侧所有小于 $y$ 且正贡献的数的贡献均变为负的。

考虑改大第二个 case 怎么维护，也就是怎么维护一个数左侧所有小于给定数 $y$ 的正贡献的数的贡献和：

设 $\mathrm{contribution}_{i, j}$ 表示 $[1, i]$ 这个前缀里等于 $j$ 的所有正贡献数的贡献和，易得转移：

$$\mathrm{contribution}_{i, j} = \mathrm{contribution}_{i - 1, j} + a_i \times [a_i = j] \times [\mathrm{sig}_i > 0]$$

式中 $[]$ 是艾弗森括号，当括号内条件为真时取 $1$ 否则取 $0$，$\mathrm{sig}_i$ 表示第 $i$ 位的贡献系数。

于是，把第 $i$ 位的 $x$ 改成 $y$ 时，整个串的值就会变为

$$sum - 2 \times \sum_{j = 0}^y \mathrm{contribution}_{i - 1, j} + y - x \times \mathrm{sig}_i$$

这样就能 $O(1)$ 算出 case 2.2 修改后的串值了。

## Code

```cpp
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>

int T;

const int val[] = {1, 10, 100, 1000, 10000};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  auto read = []() { int x; std::cin >> x; return x; };
  for (std::cin >> T; T; --T) {
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<int> a(n), postmax(n + 1), sgn(n);
    for (int i = 0; i < n; ++i) {
      a[i] = val[s[i] - 'A'];
    }
    int sum = 0;
    for (int i = n - 1; ~i; --i) {
      postmax[i] = std::max(postmax[i + 1], a[i]);
      sgn[i] = (postmax[i] == a[i]) ? 1 : -1;
      sum += a[i] * sgn[i];
    }
    int ans = sum;
    std::array<std::vector<int>, 5> contri; // 贡献数组，这里和文字叙述的两维是反着的
    for (auto &v : contri) v.resize(n);
    for (int i = 0; i < n; ++i) {
      if (i != 0) for (int j = 0; j < 5; ++j) contri[j][i] = contri[j][i - 1];
      if (sgn[i] == 1) contri[s[i] - 'A'][i] += a[i];
    }
    for (int i = 0; i < n; ++i) {
      if (postmax[i + 1] < a[i]) {  // 此时 a[i] 是后缀最大值
        int rec = a[i];
        for (int j = 1; j <= 10000; j *= 10) { // 枚举后缀最大值变成了什么数
          a[i] = j;
          sum = 0;
          for (int i = n - 1; ~i; --i) { // 暴力重算整个串的值
            postmax[i] = std::max(postmax[i + 1], a[i]);
            sgn[i] = (postmax[i] == a[i]) ? 1 : -1;
            sum += a[i] * sgn[i];
          }
          ans = std::max(ans, sum);
        }
        sum = 0;
        a[i] = rec;
        for (int i = n - 1; ~i; --i) {
          postmax[i] = std::max(postmax[i + 1], a[i]);
          sgn[i] = (postmax[i] == a[i]) ? 1 : -1;
          sum += a[i] * sgn[i];
        }
      } else {      // 此时 a[i] 不是后缀最大值，只有把 a[i] 改成不小于 postmax[i] 的数才有意义
        for (int j = postmax[i]; j <= 10000; j *= 10) {
          int tmp = 0;
          if (i != 0) for (int k = 0; val[k] < j; ++k) {
            tmp += contri[k][i - 1];
          }
          ans = std::max(ans, sum - tmp * 2 + j - a[i] * sgn[i]);
        }
      }
    }
    std::cout << ans << '\n';
  }
}
```

---

## 作者：hcywoi (赞：2)

首先，我们把 $s$ 翻转。

考虑 dp，$f_{i, j, k}$ 表示到了第 $i$ 个字符，操作了 $j$ 个字符，最大的字符为 $k$ 的最大值。

转移时枚举 $i-1$ 的最大字符 $\ell(0\le\ell<5)$。

- 不操作第 $i$ 个字符；
	- $f_{i, j, k}=\max\{f_{i-1, j, \ell} + w\}$。

- 操作第 $i$ 个字符。
	- 我们稍加思考，可以发现一定是操作成字符 $k$。
    > 证明：  
    > 如果 $k>\ell$，只有将第 $i$ 个字符操作成 $k$，才能满足定义中的条件。  
    > 如果 $k=\ell$，将其变成 $<\ell$，则权值为负，肯定不优。
    - $f_{i, j, k}=\max\{f_{i-1,j-1,\ell}+w\}$。

[代码。](https://codeforces.com/contest/1841/submission/209914353)

---

## 作者：inc1ude_c (赞：1)

DP 题。

先将字符串翻转，这样就能使得每个字符的正负贡献都取决与它左边的最大字符。

然后将字符串中的 $A$ 变为 $0$，$B$ 变为 $1$……方便后面的计算。

设 $f_{i,j,k}$ 为对于前 $i$ 个字符，使用了 $j(j\in\left\{0,1\right\})$ 次修改，遇到的最大数字为 $k(k\in[0,4])$，所得到的最大贡献值之和。

枚举 $t(t\in[0,4])$，表示将 $s_i$（第 $i$ 个数字）改为 $t$，那么就有 $Newj=j+[s_i\ne t]$，$Newk=\max(k,t)$。

于是有：

$f_{i,Newj,Newk}=\max\left\{f_{i-1,j,k}+val(t,k)\right\}$

其中 $val(a,b)=\left\{\begin{matrix}10^{a}
  &a\ge b \\-10^{a}
  &a< b
\end{matrix}\right.$

即：如果 $t\ge$ 左边的最大数字，那么贡献就为 $10^t$，否则为 $-10^t$。

显然对于 $Newj>1$ 的状态我们不用计算。

答案为 $\max_{j\in\left\{0,1\right\},k\in[0,4]}{f_{n,j,k}}$。

使用滚动数组优化空间。

---

## 作者：Furthe77oad (赞：1)

# Ranom Numbers

## 写在最前

是个大模拟，思路简单，建议评橙。

## 分析

我们很容易想到大模拟的思路，即：

先处理一个**后缀字母最大值**，以及**后缀在没有修改**的条件下的和。

然后从 $0$ 到 $n$ 枚举每一位改成每一位数，在这个过程中维护一个**类似单调栈**的东东，就是加入一个字母，将小于这个字母的值都改为负，再将正的当前字母加入。

当枚举到第 $i$ 位，作为第 $j$ 个字母时，$i$ 及 $i$ 以后的最大的字母是 $\max(j,u)$，记 $u = i + 1$ 的后缀最大值，且 $[i+1,n]$ 的和，可以通过后缀和算出，$i$ 的值通过后缀最大值讨论出正负，前面直接负的值直接加上，前面目前仍是正的值通过与 $i$ 及 $i$ 以后的最大的字母的关系得到正负，最后把这些加到一起得到答案取 $\max$。

## 参考代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, z[10], q[200015], a[200015], c[200015], ho[200015], b[10];
map <char, int> p;
string s;
int now = 0;
int cal (int l, int r) {
	if (l > r) return 0;
	return q[r] - q[l - 1];
}
void add(int k) {
	for (int i = 1; i < k; i++) {
		now -= b[i] * z[i];
		z[i] = 0;
	}
	z[k]++;
}
void solve() {
    memset(z, 0, sizeof(z));
    int ans = -1e18;
    cin >> s;
    ho[s.size()] = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
	    ho[i] = max(ho[i + 1], (int)(s[i] - 'A' + 1));
    }
    for (int i = 0; i < s.size(); i++) {
	    a[i] = p[s[i]];
	    if (s[i] - 'A' + 1 >= ho[i + 1]) c[i] = 1;
	    else c[i] = -1;
    }
    q[0] = a[0] * c[0];
    for (int i = 1; i < s.size(); i++) q[i] = q[i - 1] + a[i] * c[i];
    ans = q[s.size() - 1];
    now = 0;
    for (int i = 0; i < s.size(); i++) {
        for (int j = 1; j <= 5; j++) {
            int temp = cal(i + 1, s.size() - 1) + now;
            int li = max(j, ho[i + 1]);
            for (int k = 1; k < li; k++) temp -= z[k] * b[k];
            for (int k = li; k <= 5; k++) temp += z[k] * b[k];
            if (j >= ho[i + 1]) temp += b[j];
            else temp -= b[j];
            ans = max(ans, temp);
        }
	    add(s[i] - 'A' + 1);
    }
    cout << ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	p['A'] = 1;
	p['B'] = 10;
	p['C'] = 100;
	p['D'] = 1000;
	p['E'] = 10000;
	b[1] = 1;
	b[2] = 10;
	b[3] = 100;
	b[4] = 1000;
	b[5] = 10000;
    T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
```



---

## 作者：zhangjiting (赞：0)

## 分析
操作只有两种目的：

1. 修改某个字符变大让其贡献增大，不难发现这种情况操作时一定是操作最早出现位置的字符。
1. 修改某个字符变小，让其之前的某些位置贡献变大，不难发现这种情况操作时一定是操作最后出现位置的字符。

所以我们只要枚举每个字符第一次和最后一次出现的位置，然后暴力枚举其修改成哪个字符，每次暴力求价值，然后取最大值即可。

## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
const int pow10[] = {1, 10, 100, 1000, 10000};
int main(){

    
    auto get = [&](const string &s){
        int ans = 0, mx = -1;
        for(int i = s.size() - 1; i >= 0; i--){
            int c = s[i] - 'A';
            if (c < mx) ans -= pow10[c];
            else ans += pow10[c];
            mx = max(mx, c);
        }
        return ans;
    };

    int T;
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        int ans = get(s);
        vector<vector<int> > pos(5);
        for(int i = 0; i < s.size(); i++){
            int c = s[i] - 'A';
            pos[c].push_back(i);
        }
        for(int i = 0; i < 5; i++){
            if (pos[i].empty()) continue;
            for(int j = 0; j < 5; j++){
                s[pos[i][0]] = char('A' + j);
                ans = max(ans, get(s));
                s[pos[i][0]] = char('A' + i);

                s[pos[i].back()] = char('A' + j);
                ans = max(ans, get(s));
                s[pos[i].back()] = char('A' + i);
            }
        }
        cout << ans << endl;
    }

}
```


---

