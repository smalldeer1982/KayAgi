# Weights

## 题目描述

给你一个长度为 $N$ 的质量为 $A_1,A_2,\dots,A_N$ 的数组 $A$。每个数组中的值表示各个砝码的重量。  

所有砝码的质量均不相同。你可以把每个砝码放在天平的一边（左边或右边）。  

你不必按照 $A_1,\dots,A_N$ 的顺序放置砝码。还有一个由字符 $\texttt{L}$ 和 $\texttt{R}$ 组成的字符串 $S$，意思是在放完第 $i$ 个砝码（不是 $A_i$ ，而是选择第 $i$ 个砝码）后，天平的左边或右边应该更重。  

找出在天平上放置砝码的顺序，以便满足字符串 $S$ 的规则。

## 样例 #1

### 输入

```
5
3 8 2 13 7
LLRLL```

### 输出

```
3 L
2 R
8 R
13 L
7 L```

# 题解

## 作者：Miko35 (赞：14)

### 题意概述

给出 $n$ ($1 \leq n \leq 2 \times 10^5$) 个物品，第 $i$ 个物品重量为 $a_i$ ($1\leq a_i \leq 10^9$)。你需要将所有物品按照一定的顺序分别摆在天平的左端或右端。

给出一个仅包含 `L` 与 `R` 的长度为 $n$ 的字符串，其中第 $i$ 个字符表示，放置完第 $i$ 个物品后，天平的左端 `L` 或右端 `R` 更重。你需要构造一种满足字符串限制的放置物品的方案。若无解，输出 `-1`。

### Solution

样例没给 `-1` 那就是没有，思考通解。

因为是构造题，考虑把规模为 $n$ 的问题转化为规模为 $n-1$ 的问题的套路。

从最终情况（不妨设是 `R`）倒推，每次取出一个元素。先说结论，将第 $1,3,5,\ldots$ 大的元素放在右边，其他的放在左边，是一种合法的最终情况。

在这种情况下，考虑取出什么元素能够使天平状态不变/改变，且能使问题的形式一样：

- 取出最小的元素，天平状态一定不变。
- 取出最大的元素，天平状态一定改变。

而且在这两种情况下，天平的摆放状况仍然是，物品从小到大摆放左右交替的形式，而规模变为了 $n-1$。所以模拟即可。

```cpp
#include<bits/stdc++.h>
#define rgi register int
#define FOR(i,a,b) for(rgi i=a;i<=b;++i)
using namespace std;
const int N=400010;
int n,a[N],ans[N];
char s[N];
signed main(){
	scanf("%d",&n);
	FOR(i,1,n)scanf("%d",&a[i]);
	sort(a+1,a+n+1),scanf("%s",s+1);
	for(rgi l=1,r=n;l<=r;){
		rgi w=r-l+1;
		ans[w]=(s[w]==s[w-1]?l++:r--);
	}
	FOR(i,1,n)printf("%d %c\n",a[ans[i]],"LR"[(ans[i]&1)^(n&1)^(s[n]=='R')]);
	return 0;
}

```



---

## 作者：whiteqwq (赞：6)

[CF1599A Weights](https://www.luogu.com.cn/problem/CF1599A) 解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/15490589.html)

## 题意

$n$ 个数，你要把它们按照任意的顺序放入两个集合 $L,R$ 中，满足第 $i$ 次放置数之后集合 $s_i=\{L,R\}$ 更大，输出任意方案或报告无解。

$1\leqslant n\leqslant 2\times 10^5,1\leqslant a_i\leqslant 10^9$。

## 分析

ISIJ T3，hzr 考场就切了，而我在半年后还只会贺题解，实力差距就这么大吗。

不妨令 $s_n=L$，若不是可以直接交换集合 L,R。

考虑一个很经典的问题，给定的串为 $LRLRLRL\cdots$ 形式的，容易发现给 $a$ 排序之后交错放入两个集合中即可满足条件。

容易发现正着构造并不好处理，原因是你不好保存两个集合的差。正难则反，我们考虑不断从两个集合中删除元素。

一个简单而容易被忽略的性质是对于按照大小交错放入两个集合内的数，删去其最小的不会改变集合大小关系，删去其最大的一定会改变集合大小关系。

利用这个性质我们就可以维护当前剩下的区间直接模拟了，时间复杂度 $O(n\log n)$。

## 代码
```
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=200005;
int n,c;
int a[maxn],b[maxn];
string s;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	cin>>s,s=" "+s;
	for(int l=1,r=n,i=n;i>=1;i--){
		if(s[i]!=s[i-1])
			b[i]=r,r--;
		else b[i]=l,l++;
	}
	for(int i=1;i<=n;i++)
		printf("%d %c\n",a[b[i]],((b[i]&1)^(s[n]=='R')^(n&1))==0? 'L':'R');
	return 0;
}
```

---

## 作者：_Felix (赞：6)

首先，我们对 $a$ 数组进行排序。

注意到：
>如果直接将一个从小到大排序的数列交替的放在天平两边。即：奇数位放在 $A$ 侧，偶数位放在 $B$ 侧。
>
>就会发现每次放置砝码，都是刚刚放置了砝码的那一侧较重。

证明：

>放了偶数个的时候：
>
>$A$ 侧放了 $a_1,a_3,...a_{2k-1}$，$B$ 侧放了 $a_2,a_4,...a_{2k}$，
>
>显然 $a_i < a_{i + 1}$，$B$ 侧更重
>
>放了奇数个的时候：
>
>$A$ 侧放了 $a_1,a_3,...a_{2k-1},a_{2k+1}$，$B$ 侧放了 $a_2,a_4,...a_{2k}$，
>
>$\because a_i < a_{i + 1}$
>
>$\therefore a_3+...+2_{2k+1}>a_2+a_4...+a_{2k}$
>
>$\therefore a_1+a_3+...+2_{2k+1}>a_2+a_4...+a_{2k}$
>
>$A$ 侧更重

---

现在如果有一个已经排好序的数组按如上方式被放置在天平上。
- 若取出最大的数，那么天平一定会改变他的状态。
- 若取出最小的数，那么天平的状态将不变。

无论取出最大数还是最小数，天平上都仍然是一个新的排好序的数组按照之前的方式被放置。

那么我考虑一开始就直接放一个排好序的数组，然后第 $i$ 次我取出一个数 $x$，也就是答案中第 $n-i+1$ 次我放置的数。很显然每次都能取到数，所以一定存在答案。

---

上面那个东东的实现方法有很多。
下面是CF官方题解的实现方法，非常简单。

>先对 $a$ 进行排序。
>
>当我们从 $L$ 转到 $R$ 或从 $L$ 转到 $R$ 时，会发生一次转换。
我们设有 $cnt$ 次转换。
>
>先将 $a_{n-cnt}$ 放置在 $s_1$ 侧。
>
>现在维护两个指针：左指针 $l$ 和 右指针 $r$，初始指向 $n-cnt$ 处。
>对于 $s_i(i\in [2,n])$ ，
>
>- 如果没有发生转换，即 $s_i \neq s_{i-1}$，减小左指针，将左指针指向的砝码放在与上一次放置左指针指向的砝码时所放置的相反的一侧
>- 如果发生了一次转换，即 $s_i = s_{i-1}$，增大右指针，将右指针指向的砝码放在与上一次放置右指针指向的砝码时所放置的相反的一侧，也就是此时的 $s_i$ 侧。



证明构造的是合法的解：
>考虑 $[1,i]$ 与 $[1,i-1]$ 时天平的状态。
>- 如果没有发生转换，即 $s_i \neq s_{i-1}$，从 $[1,i]$ 的天平中取出了最小数，变成了 $[1,i-1]$ 的天平。
>- 如果发生了一次转换，即 $s_i = s_{i-1}$，从 $[1,i]$ 的天平中取出了最大数，变成了 $[1,i-1]$ 的天平。
>用了 $cnt$ 次右指针，$n-cnt-1$ 次左指针，还有一次是 $s_1$。所以一定能通过这个方法找到合法的解。


---

## 作者：pigstd (赞：6)

### [CF1599A Weights](https://www.luogu.com.cn/problem/CF1599A)

简单想象一下，貌似是必然有解的。

然后不难发现，如果给出的字符串是 $\text{LRLRLRLRL}$ 这样的，那么把所有数从大到小排序，然后第一个放左边，第二个放右边……就可以了。正着做有点困难，考虑倒着做，考虑每次从天平中取出一个砝码，同时令放右边的乘以 $-1$，那么就需要满足每次删掉一个数，满足剩余的数的个数是正数或者负数。

可以发现，如果排序后将所有奇数/偶数位的数乘以 $-1$，下一个删掉最前面的数和最后面的数，两个的正负形恰好是相反的，而且删掉后还是满足有序和奇偶并列，这意味着只要先把所有的奇数或者偶数位乘 $-1$ 那么就可以归纳的构造了。

然后根据最后天平的结果选择奇数或者偶数位乘 $-1$ 然后维护两个指针即可。

[code](https://codeforces.com/contest/1599/submission/131987779)。



---

## 作者：DaiRuiChen007 (赞：1)

# CF1599A 题解



## 思路分析

首先注意到 $a_i$ 互不相同，因此考虑忽略 $a_i$ 的值域，通过比较 $a_i$ 的排名来构造。

又因为我们的切换过程应该要尽可能得简单，因此我们考虑对 $a_i$ 排序后把奇偶的两项放到天平的两侧，如下图，对于任意一种情况，我们都能给出一种合法的构造：

[![pS2CpmF.png](https://s1.ax1x.com/2023/02/07/pS2CpmF.png)](https://imgse.com/i/pS2CpmF)

如上图所示，圆圈中的数表示 $a_i$ 排完序后在序列中的下标。

而当我们从 $n\to n+1$ 转移的情况如下图，依然可以继续做：

[![pS2C9w4.png](https://s1.ax1x.com/2023/02/07/pS2C9w4.png)](https://imgse.com/i/pS2C9w4)

我们发现每次转移的时候只会选择当前序列的最大值或最小值，因此我们可以先从左到右扫描一遍，记录一下每次操作选择的放置方向和砝码是当前的最大值还是最小值，最后倒序依次考虑，用 `multiset` 从后到前依次分配权值。

从上面的分析可以看出，对于任何的一组数据，我们都给出了合法的构造，并且与 $a_i$ 的具体值无关。

时间复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define MIN 0
#define MAX 1
using namespace std;
const int MAXN=2e5+1;
char str[MAXN],op[MAXN];
int a[MAXN],ch[MAXN],val[MAXN];
signed main() {
	int n;
	scanf("%d",&n);
	multiset <int> s;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),s.insert(a[i]);
	scanf("%s",str+1);
	ch[1]=MIN,op[1]=str[1];
	for(int i=2;i<=n;++i) {
		if(str[i-1]=='L') {
			if(i%2==0) {
				if(str[i]=='L') op[i]='R',ch[i]=MIN;
				if(str[i]=='R') op[i]='R',ch[i]=MAX;
			} else {
				if(str[i]=='L') op[i]='L',ch[i]=MIN;
				if(str[i]=='R') op[i]='R',ch[i]=MAX;
			}
		} else {
			if(i%2==0) {
				if(str[i]=='L') op[i]='L',ch[i]=MAX;
				if(str[i]=='R') op[i]='L',ch[i]=MIN;
			} else {
				if(str[i]=='L') op[i]='L',ch[i]=MAX;
				if(str[i]=='R') op[i]='R',ch[i]=MIN;
			}
		}
	}
	for(int i=n;i>=1;--i) {
		if(ch[i]==MIN) val[i]=*s.begin(),s.erase(s.begin());
		if(ch[i]==MAX) val[i]=*prev(s.end(),1),s.erase(prev(s.end(),1));
	}
	for(int i=1;i<=n;++i) printf("%d %c\n",val[i],op[i]);
	return 0;
}
```

---

## 作者：strcmp (赞：0)

首先将 $a$ **排序**，无论如何一定会比不排序好处理很多。

正着做很难，不妨考虑从终状态转移到初始状态。

然后你考虑一下什么终状态可能是好的。

一个很好的想法就是奇偶分组，$a_1,\,a_3,\,a_5,\,\dots$ 分到一组（左边 A 组），$a_2,\,a_4,\,a_6,\,\dots$。（右边 B 组）

**如果 $n$ 是奇数：**

我们有 $a_2 < a_3,\,\dots,\,a_{n - 1} < a_n$ 进而有 A 组和大于等于 B 组，进而天平左偏。

如果最开始要求天平右偏怎么办，直接交换 AB 就行了。

从后往前，考虑当前，如果天平左偏要改成右偏怎么办。那我们直接把 $a_n$ 删掉就好了，一定改变偏序关系。

因为我们有：$a_1 < a_2,\,a_3 < a_4,\,\dots,\,a_{n - 2} < a_{n - 1}$。

如果要维持左偏呢？我们直接删掉 $a_1$ 即可，不改变 $a_2 < a_3,\,\dots,\,a_{n - 1} < a_n$。

如果继续左偏呢？删掉 $a_2$ 即可，继续左偏就删掉 $a_3$，以此类推。

也就是说，对于奇偶分组后的两个组，我们交替删掉它们最小的元素，不会改变重量关系。删掉较大的那个组的最大元素，一定改变重量关系。

比如：

```
a1 a3 a5 a7
a2 a4 a6
LLRLRRL
```

我们这样改变：

```
a1 a3 a5 a7
a2 a4 a6
L
a1 a3 a5
a2 a4 a6
R
a3 a5
a2 a4 a6
R
a3 a5
a2 a4
L
a3
a2 a4
R
a3
a2
L
a3
L
```

$n$ 是偶数也是类似讨论。

那么奇偶分组，每次要维持当前重量关系就交替删最小值，否则删较大的组的最大值即可。

官方题解用了一个挺妙的方法简单维护了这个东西。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
using namespace std;
using ld = double;
typedef long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 4e5 + 10, mod = 1e9 + 7;
const ll inf = 1145141919810520L;
int n, p[maxn]; ll a[maxn]; char s[maxn];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]); scanf("%s", s + 1);
	sort(a + 1, a + n + 1);
	for (int l = 1, r = n, k; l <= r; k = r - l + 1, p[k] = s[k] == s[k - 1] ? l++ : r--);
	for (int i = 1; i <= n; i++) printf("%lld %c\n", a[p[i]], p[i] & 1 ^ s[n] == 'R' ^ n & 1 ? 'R' : 'L');
	return 0;
}
```

---

