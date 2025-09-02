# [CEOI 2016] match

## 题目描述

给你一个由小写字母组成的字符串 $s$，要你构造一个字典序最小的（认为左括号的字典序比右括号小）合法的括号序列与这个字符串匹配。

字符串和括号序列匹配定义为：首先长度必须相等，其次对于一对匹配的左括号和右括号 $i,j$，必须有 $s_i=s_j$。


无解输出 `-1`。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 10^5$。

## 样例 #1

### 输入

```
abbaaa```

### 输出

```
(()())```

# 题解

## 作者：Kubic (赞：13)

一个不太一样的思路。

称一个区间 $[l,r]$ 合法当且仅当只保留 $[l,r]$ 可以组成合法括号序列。

显然 $[1,n]$ 必须是合法区间，否则无解。

把字典序最小转化为：依次考虑每一个数，贪心地选择最大的合法匹配位置。称 $i$ 的一个匹配位置 $j$ 合法当且仅当 $(i,j)$ 和 $(j,n]$ 都是合法区间且 $a_i=a_j$。

正确性其实不是很显然，但感性理解比较容易，证明又有点难说清楚，这里就不写了（

此时我们就获得了一个不太一样的 $O(n^2)$ 暴力：暴力扫一遍找到 $1$ 的最大合法匹配位置 $t$，并递归到 $(1,t),(t,n)$ 两个子问题。

考虑优化：对于一个区间 $[l,r]$ 快速找到 $t$。

因为 $(l,t)$ 是合法区间且 $a_l=a_t$，所以 $[l,t]$ 是合法区间。又因为 $[l,r]$ 是合法区间，所以 $(t,r]$ 是合法区间。而显然这又是充分的。因此我们可以发现，对于一个固定的 $r$，$t$ 只与 $a_l$ 有关。

状态数被我们减小到了 $O(n\Sigma)$，考虑 $dp$。

设 $dp_{r,i}$ 表示 $a_l=i$ 时的答案。

容易得出转移方程：

$$dp_{r,i}=dp_{dp_{r-1,a_r}-1,i}$$

边界：$dp_{r,a_r}=r$。

预处理完之后我们就可以 $O(n)$ 求出解。最终时间复杂度 $O(26n)$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
int n,st[N],dp[N][26];char a[N];
int main()
{
	scanf("%s",a+1);n=strlen(a+1);
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<26;++j) if(dp[i-1][a[i]-'a'])
			dp[i][j]=dp[dp[i-1][a[i]-'a']-1][j];
		if(st[0] && st[st[0]]==a[i]-'a') --st[0];
		else st[++st[0]]=a[i]-'a';dp[i][a[i]-'a']=i;
	}if(st[0]) {puts("-1");return 0;}st[++st[0]]=n+1;
	for(int i=1;i<=n;++i)
	{
		if(i==st[st[0]]) putchar(')'),--st[0];
		else putchar('('),st[st[0]+1]=dp[st[st[0]]-1][a[i]-'a'],++st[0];
	}return 0;
}
```

---

## 作者：Find_Yourself (赞：12)

暴力1：直接 dfs 枚举每个位置状态，复杂度 $O(2^n)$，预计 10pts。

暴力2：考虑贪心，如果一个左括号有多个合法的右括号匹配，则一定选最靠右的，而一对括号匹配当且仅当字符相同且中间部分可以完全匹配。

怎么判断能否一段连续区间可以完全匹配呢？我们可以用栈模拟！

假设该区间为 $[l, r]$。如果栈在 $l-1$ 时的形态与 $r$ 时的形态相同，则可以匹配。

而栈的形态我们可以用字符串哈希记录。

所以我们只需要 $O(n)$ 预处理出每个位置的哈希值，然后对于每一个点，从右往左找第一个哈希值相等的位置，递归处理即可。复杂度 $O(n^2)$，预计 50pts。

正解：现在的瓶颈是如何 $O(1)$ 找到最靠右的匹配位置。

我们可以每个点的哈希值离散化并存入 vector 中进行分类。

然后对于当前状态 dfs(l, r)，二分坐标在 $[l, r]$ 范围中与 $l$ 匹配且最靠右的位置，即在 `vec[hash[l]]` 中进行 `upper_bound`。

最后复杂度均摊下来就是 $O(n\log n)$，预计 100pts。

[code](https://www.luogu.com.cn/paste/0211yfyf)

---

## 作者：wsyhb (赞：5)

## 前言

截止本文发布前，本题题解区仅有的[这篇题解](https://www.luogu.com.cn/blog/1-2-1/solution-p6000)其实讲得非常好，只可惜**它的时间复杂度是假的 $O(n \log{n})$**。本文在讲解本题解法的同时，**也会说明上述题解的时间复杂度假在何处**。

## 题解

首先考虑如何**判无解**。

维护一个栈，用于存放当前仍未匹配的字符，从左到右加入每个字符。一个显然的贪心策略，**若即将加入的字符和当前栈顶字符相同，那么令这两个位置匹配，并弹出栈顶字符**，一定可以尽可能地让整个括号串合法。**若最后栈不为空，则无解**，否则必定有解。

其次考虑如何判断区间 $[l,r]$ 是否可以组成一个合法的括号序列。

根据判无解的方法可知，这**等价于 $s_{l-1}$ 加入后和 $s_r$ 加入后的栈（元素）一模一样**。因此我们只需预处理出 $Hash_i$ 表示 $s_i$ 加入后栈的 Hash 值，判断 $Hash_{l-1}$ 和 $Hash_r$ 是否相等即可。

最后考虑**递归求解** $[l,r]$。

显然，左端点位置应为左括号，而我们还需要找到一个**尽量靠右**的位置 $p$（$p \in (l,r]$），填上右括号，使其与 $l$ 位置匹配。具体来说，位置 $p$ 需要满足如下条件：

- $s_p=s_l$，这样才能匹配。
- $Hash_p=Hash_r$，这样区间 $[p+1,r]$ 才合法，进一步，区间 $[l+1,p-1]$ 也合法。

因此开个 **map**，记录**当前**同时满足字符和 Hash 值条件的**最靠右**的位置，同时预处理出 $Left_i$ 表示与 $i$ 相同的上一个位置，这样若位置 $>r$ 就可以不断地向左跳，找到要求的位置 $p$，然后递归求解 $[l+1,p-1]$ 和 $[p+1,r]$。

但请注意，如果**每次从全局最靠右的、满足条件的位置不断向左跳，时间复杂度是 $O(n^2)$ 的**，这就是前言中提到的题解的做法。（$n$ 个字符相同就可以卡满成 $2(0+1+\cdots+(\dfrac{n}{4}-1))$，约为 $\dfrac{n^2}{16}$ 次，由于常数小大概 Hack 不掉）

解决方法很简单，**每次先递归右边区间 $[p+1,r]$，并将 map 对应的值更新为当前跳到的那个位置**，简单势能分析一下，**时间复杂度是真的 $O(n\log{n})$**。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
char s[max_n],st[max_n];
int top;
const unsigned long long base=19260817;
unsigned long long power[max_n],Hash[max_n];
typedef pair<unsigned long long,char> P;
map<P,int> pos;
int Left[max_n];
char ans[max_n];
void solve(int l,int r)
{
	if(l>r)
		return;
	int p=pos[P(Hash[r],s[l])];
	while(p>r)	
		p=Left[p];
	ans[l]='(',ans[p]=')';
	pos[P(Hash[r],s[l])]=p;
	solve(p+1,r),solve(l+1,p-1);
}
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	power[0]=1;
	for(int i=1;i<=n;++i)
		power[i]=power[i-1]*base;
	unsigned long long h_now=0;
	for(int i=1;i<=n;++i)
	{
		if(top>0&&st[top]==s[i])
			h_now-=power[top--]*(s[i]-'a'+1);
		else
		{
			st[++top]=s[i];
			h_now+=power[top]*(s[i]-'a'+1);
		}
		Hash[i]=h_now;
	}
	if(top>0)
	{
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;++i)
	{
		Left[i]=pos[P(Hash[i],s[i])];
		pos[P(Hash[i],s[i])]=i;
	}
	solve(1,n);
	printf("%s\n",ans+1);
	return 0;
}
```

---

## 作者：Leasier (赞：4)

困难 greedy /ll

------------

一个简单的想法是逐位确定，则我们每次 check 只需要前后各拿一个栈扫一遍，时间复杂度为 $O(|S|^2)$。

~~硬优化到 $O(|S| \log |S|)$ 是没问题的，但写起来会很抽象，然后我模拟赛时就寄飞了 /ll~~

判全局是否有解还是可以考虑拿一个栈来维护，具体地：

- 初始栈为空。
- 每扫到一个字符，若栈顶的字符与当前字符相同则消掉，否则将当前字符入栈。
- 若最终栈非空则无解。

接下来我们尝试构造一组字典序最小的解。

贪心地，想到我们期待让每个位置的匹配对象**尽量靠后**，这样就可以让每个右括号的位置尽量靠后。例如：

- 对 `AABBAA` 而言，`((()))` 优于 `()()()`。

由此，我们有了一个新的想法：

- 首先确定 $S_1$ 的最前匹配位置 $S_i$，要求 $[1, i]$ 合法。
- 由于 $[1, n]$ 合法，$[i + 1, n]$ 也一定合法。
- 此时 $[2, i - 1], [i + 1, n]$ 成为了两个新的子问题。

于是我们可以考虑分治，每次扫一遍当前区间求出最前面匹配位置，然后递归下去处理即可。

直接暴力的时间复杂度为 $O(|S|^2)$，考虑优化。

- **若求前缀的时间复杂度可以接受但求区间的时间复杂度寄飞了，可以尝试“差分”。**

注意到 $[l, r]$ 合法的充要条件为 $[1, l - 1]$ 的栈和 $[1, r]$ 的栈形态相同（即 $[l, r]$ 中产生的项刚好被消完了），于是我们对栈哈希即可。

map 套 vector 即可。时间复杂度为 $O(|S| \log |S|)$。

~~不要取种子为 $998244353$ 且取模数为 $10^9 + 7$，会被卡。~~

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

const int seed = 19260817, mod = 1e9 + 7;
int top = 0;
int stk[100007];
ll val[100007], hash_val[100007];
char s[100007], ans[100007];
map<ll, vector<int> > mp;

void solve(int l, int r){
	if (l > r) return;
	int mid;
	ll cur = (hash_val[l - 1] * seed % mod + s[l]) % mod;
	ans[l] = '(';
	mid = *(--upper_bound(mp[cur].begin(), mp[cur].end(), r));
	ans[mid] = ')';
	solve(l + 1, mid - 1);
	solve(mid + 1, r);
}

int main(){
	int n;
	cin >> &s[1];
	n = strlen(&s[1]);
	for (int i = 1; i <= n; i++){
		if (top > 0 && s[i] == s[stk[top]]){
			top--;
		} else {
			top++;
			stk[top] = i;
			val[top] = (val[top - 1] * seed % mod + s[i]) % mod;
		}
		hash_val[i] = val[top];
	}
	if (top != 0){
		cout << -1;
		return 0;
	}
	for (int i = 1; i <= n; i++){
		mp[(hash_val[i] * seed % mod + s[i]) % mod].push_back(i);
	}
	solve(1, n);
	cout << &ans[1];
	return 0;
}
```

---

## 作者：Azazеl (赞：4)

进行了一些修改，现在应该变得更清晰一些。  

2021/10/22 UPD:之前的打法时间复杂度假了，故进行了修正。

#### 题意

> $~~~~$ 求字典序最小的匹配括号串使得匹配的一对括号在给定字符串 $s$ 中对应的字符相同。或说明无解。  
$~~~~$ $1\leq |s|\leq 10^5.$

#### 题解

$~~~~$ 先来判有没有解，可以直接把字符串当成括号串来放进栈里面匹配，栈顶与当前字符相同说明这样可以放匹配括号，则弹出，否则入栈。最后只要栈为空就是有解的。

$~~~~$ 首先考虑怎么求某一个区间是否合法（但在正常的做题思路中它应该在后面），显然如果在栈没有扫到这个区间与刚好扫过这个区间之后栈内的字符是相同的则该区间合法。记 $hash_i$ 表示在 $i$ 字符执行完进栈/弹栈操作后的栈内的 $hash$ 值，那么当 $hash_{l-1}=hash_r$ 时，区间 $[l,r]$ 是合法的。  

$~~~~$ 那么怎么来求解某个合法区间呢？我们记 $solve(l,r)$ 为求解一个已知区间 $[l,r]$ 的答案的**过程**，我们现在可以知道：

- $l$ 处应放置左括号 ：显然，因为区间合法，第一个字符只有放左括号才可能匹配上后面的字符。
- 与 $l$ 处匹配的右括号应该放在可能的最远的位置，设为 $pos$，那么$[pos+1,r]$ 会被划分为一个区间，则 $pos$ 应该满足 $hash_{pos}=hash_r$ 且 $s_l=s_{pos}$。
- 同时为了满足字典序更小，右括号应该被放在**尽可能远**的位置，所以 $pos$ 应取可行的最大值。

$~~~~$ 关于怎么快速找到 $pos$ 可行的最大值？用 `map` 维护最大的位置 $j$ ，满足 $s_j$ 为给定字符与给定hash值，同时顺便维护某个位置上一个条件与它相同的位置，最后暴力跳即可。

$~~~~$ 这样，区间就被我们分成了三个部分：$l$ ，$pos$  、$[l+1,pos-1]$ 和 $[pos+1,r]$ 。由于  $hash_{pos}=hash_{r}$ ，所以区间 $[pos+1,r]$ 是合法的。而区间 $[l,pos]$ 也一定是合法的，在合法区间两边同时去掉一位，若这两位对应的字符相同，余下的区间也一定合法。（这两个字符在栈里面会最后消掉，故扫描到最后一位之前一定与第一位刚进栈时栈内字符串相等）所以 $[l+1,pos-1]$ 也一定合法。

$~~~~$ 那既然这两个区间是合法的，我们可以继续执行 $solve$ 过程就可以求解这两个区间。

---
2021/10/22 UPD

$~~~~$ 但是，求出全局最靠右的满足该条件的位置再暴力跳回来的复杂度是假的 $n \log n$，因为当所有字符相同时，正如上面一篇题解所述复杂度应为 $0+1+\dots+(\frac{n}{4}-1)=\frac{n^2}{16}$，所以这个办法其实会被卡。

$~~~~$ 解决方法是：每次先遍历右区间 $[pos+1,r]$，同时更新 `map` 存储的某一条件的位置到尽可能靠左的地方，这样由于从右往左处理区间，所以每次 `map` 找到的位置都是在当前区间右边但尽可能靠近它的位置，这样暴力跳的次数就不会太多。当然你也可以把 $hash$ 值离散化后用 `vector` 存下来，每次二分合适的位置，只是会带大常数。

$~~~~$ 时间复杂度 $\mathcal{O(n\log n)}$.

#### 代码

```cpp
#include <map>
#include <stack>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mp(a,b) make_pair(a,b)
#define ll long long
#define ull unsigned long long
using namespace std;
const ull base=131;
char Ans[100005],str[100005],sta[100005];
int lef[100005],lst[100005];
ull P[100005],Hash[100005];
int Top;
map<pair<ll,int>,int>M;
void solve(int l,int r)
{
	if(r<=l) return;
	int pos=M[mp(Hash[r],str[l]-'a')];
	while(pos>r) pos=lef[pos];
	Ans[l]='(';Ans[pos]=')';
	M[mp(Hash[pos],str[pos]-'a')]=pos;
	solve(pos+1,r);solve(l+1,pos-1);
}
int main() {
	scanf("%s",str+1);
	int len=strlen(str+1);
	P[0]=1;
	for(int i=1;i<=len;i++) P[i]=P[i-1]*base;
	ull now=0;
	for(int i=1;i<=len;i++)
	{
		if(str[i]==sta[Top]) now-=P[Top--]*(str[i]-'a'+1);
		else now+=P[++Top]*(str[i]-'a'+1),sta[Top]=str[i];
		Hash[i]=now;
	}
	if(Top) return puts("-1")&0;
	for(int i=1;i<=len;i++)
	{
		lef[i]=M[mp(Hash[i],str[i]-'a')];
		M[mp(Hash[i],str[i]-'a')]=i;	
	}
	solve(1,len);
	puts(Ans+1);
	return 0;
}
```

---

## 作者：pandaSTT (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P6000)

[更好的阅读体验?](http://lab.mkblog.cn/mirror/mirror.html?url=https%3A%2F%2Fwww.luogu.com.cn%2Fblog%2F557117%2Fsolution-p6000)

括号匹配问题，联想栈，可以利用栈进行判断无解。

需要输出字典序最小（左括号的字典序比右括号小）的括号序列，因此一个字符匹配的另一半需要尽量靠后。

化简问题：


若形似 `x......x......x......x` 的区间匹配的括号序列可以为 `(......)......(......)` 且第二个 $ x $ 与第三个 $ x $ 中的区间可以匹配合法的括号序列，则将该区间匹配的括号序列改为 `(......（......）......)`。

对于寻找一个字符的连续四次出现的位置，可以在输入时初始化 Nxt 数组记录，并用一个 Num 数组记录当前与该位置元素匹配的元素位置。

对于判断第二个 $ x $ 与第三个 $ x $ 中的区间能否匹配合法的括号序列，可以在利用栈进行进行判断无解操作时记录在弹入当前元素并进行弹出操作后栈内元素 Hsh 的值，当两个元素的 Hsh 值相等时，说明两个元素中的区间可以匹配合法的括号序列。（因为两个元素中的区间的所有元素都一一匹配进行了弹入和弹出操作，所以可以匹配合法的括号序列）

所以枚举 $ 26 $ 种字母每种字母的出现情况进行判断，若满足则修改其 Num 数组。

最后输出时若该元素记录的 Num 大于该元素位置则输出左括号，反之输出右括号即可。

---

## 作者：FutaRimeWoawaSete (赞：3)

考虑用经典的字符串匹配问题判断是否无解。因为递归到最内层必定存在两个相邻的括号挨在一起，可以证明用栈做的正确性是对的。             

考虑分治解决问题，即我们对于一个形如区间 $[l,r]$ 的子问题找到能匹配到 $l$ 的最远右端点，分别置为左右括号。              

记 $stk_i$ 表示在点 $i$ 时栈的情况，不难发现如果两个点 $l,r$ 能匹配在一起的充要条件是 $s[l] = s[r]$ 且 $stk_{l - 1} = stk_r$。           


判断栈是否相等等价于判断两个长度相等的字符串是否相等，用哈希就可以做了。           

考虑要找最远端点，那么我们不妨直接维护一个二元组信息 $(stk_i,hash_i)$ 的向右最远点并且对所有二元组信息相等的点连链表后每次暴力从最右边跑到第一个在区间内的答案。              

不难证明这个做法的时间复杂度上限是 $O(\frac{n ^ 2}{16})$ 的，可在字符集大小为 $1$ 是取到这个上界。                  

考虑一些更能摊的方法，不难发现字符串中每个位置只会和另一个位置匹配，所以这里的匹配量是 $O(n)$ 的。                 

若采用 vector 把所有链表存下来可以获得一个上限 $O(n \log^2 n)$，思考更块的做法。

设 $\phi[(stk_i,hash_i)] = |(stk_i,hash_i)|$ 表示一个二元组信息的势能函数，其初始值为所有具有该类二元组信息的位置的个数，若一共有 $k$ 种二元组，不难发现 $\sum_{i = 1} ^ k \phi_i = n$。               

若我们每次在递归解决问题时优先递归右区间并且将每层分治用到的二元组所对应的链表指针向前挪动，即按中-右-左的顺序遍历一棵区间拆分树可以保证后面遍历的区间使用到的信息一定不超过先前遍历的区间，即链表的指针不会向后挪回去。               

那么我们可以得到所有链表的指针移动量为 $O(n)$ 级别，算上 map 总的均摊时间复杂度就是 $O(n \log n)$。                 

如果精细实现的话可以去 map 做到 $O(n)$，不过想必也没人这么无聊。



---

## 作者：快斗游鹿 (赞：1)

首先考虑贪心，对于一个左括号，我们肯定希望它的右括号在尽量右侧的位置，因为对于一对合法匹配的括号，中间一段必然都是匹配的，所以把当前要匹配的括号往左移肯定不会更优。

举个例子，如果当前是 `AXAXAXA` 这样子的情况，`A` 是当前位置字符，`X` 是一段能完全匹配的括号序列，如果让第一个与第四个匹配，则会形成 `(XAXAX)` 这样的序列，而如果让它与第二个匹配，则会形成 `(X)XAXA` 这样的序列，`X` 的最优匹配显然不会因此而被改变，而这样反而会导致部分 `A` 的匹配策略不是最优的。

所以这个贪心是对的，直接模拟可以做到 $O(n^2)$。考虑优化复杂度，我们用栈模拟括号匹配，则 $[l,r]$ 是一段能完全匹配的括号序列，意味着 $l-1$ 和 $r$ 时的栈状态完全一致，这可以直接哈希处理。而每次找就是对于 $i$，找到最大的合法的 $j$ 使得 $s_i=s_{j+1},sum_i=sum_j$，$sum$ 是当前栈状态的哈希值，二分即可。时间复杂度 $O(n\log n)$。有点细节。

---

## 作者：wsyhb (赞：1)

## 题解

类比一般的判断合法括号序列的方法，我们可以用一个**栈**，对于一个字符串**判断其是否和某个合法括号序列匹配**。（下文将“和某个合法括号序列匹配”称为“合法”）

具体而言：

- 栈用于存储当前未匹配的左括号所对应的字符，初始为空。
- 从左到右依次考虑每个字符：
	- 若当前栈不为空且当前字符和栈顶相同，令当前位置为右括号，从而和栈顶进行匹配——弹出栈顶。
	- 否则当前位置只能是左括号——将其入栈。
- 存在合法括号序列与之匹配，当且仅当最终栈为空。（栈为空这个判定条件决定了这个判定方法的正确性，因为目标是栈为空，所以能匹配则匹配一定最优）

------------

**最靠左的位置**一定是左括号，我们考虑其可以**与哪些位置匹配**。

下标为 $\mathit{p}$ 的位置能与下标为 $0$ 的位置匹配，当且仅当 $s_p=s_0$ 且 $s[1,p-1]$ 和 $s[p+1,n-1]$（$n$ 为字符串长度）均合法。（*）

对于所有满足 (*) 的位置，我们可以直观地发现，选择**其中最靠右的一个是最优的**，**证明**如下：

设 $p_l$ 和 $p_r$ 为两个满足 (*) 的位置，且 $p_l<p_r$，则 $s[1,p_l-1]$ 和 $s[1,p_r-1]$ 均合法。

引入一个引理：

> 引理：若 $s[x,z]$ 和 $s[x,y]$ 均合法，且 $y<z$，则 $s[y+1,z]$ 合法。

证明的话考虑判断 $s[x,y]$ 是否合法的过程，可以发现在考虑位置 $y$ 和位置 $z$ 以后栈均为空，故引理得证。

由引理知 $s[p_l,p_r-1]$ 合法。进而对于任意选择 $p_l$ 和位置 $0$ 进行匹配的方案，我们总可以在不改变 $[0,p_l-1]$ 中的括号的前提下，通过改选 $p_r$ 和位置 $0$ 进行匹配，将位置 $p_l$ 由右括号变为左括号。 $\blacksquare$

----

在求得和位置 $0$ 匹配的最优位置 $p_{opt}$ 后，问题转化为 $[1,p_{pot}-1]$ 和 $[p_{opt}+1,n-1]$ 这两个子问题，递归处理即可。

所以现在唯一剩下的问题是，**如何求解最优位置 $p_{opt}$**。

**结论**：$p_{opt}$ 为最大的 $x$，满足 $s_x=s_0$ 且 $s[x+1,n-1]$ 合法。**证明**如下：

只需证该条件和 (*) 中的条件等价，即“若 $s_x=s_0$ 且 $s[x+1,n-1]$ 合法，则 $s[1,x-1]$ 合法”。

首先由前述引理知 $s[0,x]$ 合法。

其次，若位置 $0$ 和位置 $x$ 匹配，命题成立。于是考虑两者不匹配的情况——设位置 $0$ 和位置 $x$ 分别与位置 $y$ 和位置 $z$ 匹配（$0<y<z<x$） ，则 $s[0,y]$ 和 $s[z,x]$ 合法，进而 $s[y+1,z-1]$ 合法。那么我们完全可以交换位置 $y$ 和位置 $z$ 的左右括号，使得位置 $0$ 和位置 $x$ 匹配。 $\blacksquare$

设 $f_{i,c}$ 表示最大的 $j$，满足 $s[j+1,i]$ 合法且 $s_j=c$，可得转移方程：

$$f_{i,c}=\begin{cases}
i, &s_i=c,\\
f_{(f_{_{i-1},s_i})-1,c}, \quad &s_i \neq c.
\end{cases}$$

说明：若 $s_i \neq c$，则考虑和位置 $i$ 匹配的位置（$f_{i-1,s_i}$），在这之前再去找满足要求的位置。

预处理 $f$ 以后，最优位置 $p_{opt}$ 就很好求了。

总时间复杂度 $O(n |\Sigma|)$，其中字符集大小 $|\Sigma|=26$。

当然你也可以使用 Hash + map 求解最优位置 $p_{opt}$，时间复杂度 $O(n\log{n})$，具体细节见[这篇题解](https://www.luogu.com.cn/blog/wsyhb/post-ti-xie-p6000-ceoi2016match)。

其实本题可以做到 $O(n)$，至于怎么做，留作思考题（

## 代码

P.S. 笔者写的是递归求解，事实上可以用循环解决，详情请阅读 [Kubic 的题解](https://www.luogu.com.cn/blog/119621/solution-p6000)的代码。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
char s[max_n],st[max_n],ans[max_n];
int f[max_n][26],tp;
void solve(int l,int r)
{
	if(l>r)
		return;
	int p=f[r][s[l]-'a'];
	assert(p>l&&p<=r);
	ans[l]='(',ans[p]=')';
	solve(l+1,p-1),solve(p+1,r);
}
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;++i)
	{
		if(tp>0&&st[tp]==s[i])
			--tp;
		else
			st[++tp]=s[i];
		for(int j=0;j<26;++j)
			f[i][j]=f[i-1][s[i]-'a']?f[f[i-1][s[i]-'a']-1][j]:0;
		f[i][s[i]-'a']=i;
	}
	if(tp>0)
	{
		puts("-1");
		return 0;
	}
	solve(1,n);
	printf("%s\n",ans+1);
	return 0;
}
```

## 后记

大约一年半以前，我写了这道题的题解。（[传送门](https://www.luogu.com.cn/blog/wsyhb/post-ti-xie-p6000-ceoi2016match)，上文出现过）

今天正巧又来做这道题，想了一会儿发现不会做，就去看自己原来写的题解。

以下三段是我看完题解的心理活动：

咦，为啥若“区间 $[p+1,r]$ 合法”则“区间 $[l+1,p-1]$ 也合法”？

嗯……大概是我当时想清楚了但没有写上去吧……

不过有个更大的问题啊——为啥给下标为 $l$ 的位置上的左括号匹配一个尽量靠右的右括号最优啊？

在努力回忆一番后，我判定自己当时应该是没有思考如何证明——因为觉得这个结论很直观，~~而且想水题解~~，所以就直接省略证明，一笔带过了。

而且我觉得当时写的题解好丑啊——一方面是因为“$Hash$”这种变量名，另一方面是因为加粗部分过多，以致于重点过多而没有重点。

所以我就写了这篇题解。

----

话说我写这么长，是不是不会有人有耐心读完啊……（哭）

~~拜托，我可写了一上午喂！~~

~~再说，比起我的大多数题解，这其实算比较短的……~~

可能是因为我语文太烂了？

我好菜啊……各种意义上的。

---

## 作者：xiaoyaowudi (赞：1)

#### 题意

给定一个小写字符串 $s$，求出字典序最小的合法括号匹配序列 $t$ 或判断不存在，使得对于任意匹配的左右括号 $t_i,t_j,i< j$，$s_i=s_j$

$\left|s\right|\le 10^5$

#### 分析

先考虑一个引理，对于一个字符串 $s=s_1s_2\cdots s_n$ 和它的前缀 $s_1s_2\cdots s_k$ ，如果他们都能对应一个合法的括号序列。

那么 $s_{k+1}s_{k+2}\cdots s_n$ 也能对应一个合法的括号序列，考虑括号匹配的贪心过程，$k$ 结束时栈为空，$n$ 结束时栈也为空，因此 $s\left[k+1,n\right]$ 也是合法的。

回到原题，一个比较显然的贪心想法是从左往右依次对于每个左括号，我们将其对应的右括号尽可能的往右移，使得字典序最小

##### _proof_

假设当前字符串为 $s=s_1s_2\cdots s_n$ 且是一个合法字符串 ，当前 $s_1$ 匹配到 $s_i$ 且可以匹配 $s_j$，$1<i<j$

当前括号序列是 $(t_2t_3\cdots t_{i-1})t_{i+1}\cdots t_{j}\cdots t_n$

那么 $s\left[1,i\right]$ 是合法的，$s\left[1,j\right]$ 是合法的，$s\left[i+1,n\right]$ 是合法的。

因此 $s\left[i+1,j\right],s\left[2,i-1\right],s\left[2,j-1\right]$ 是合法的，那么 $s\left[j+1,n\right],s\left[i,j-1\right]$ 也是合法的，那么假设两段分别对应 $t^{\prime}_1,t^{\prime}_2$

那么 $(t_2t_3\cdots t_{i-1}t_2^{\prime})t_{1}^{\prime}$ 的第 $i$ 个字符是 $($ ，更优。

因此贪心过程是对的。

接下来考虑如何求对于$i$，最大能匹配的位置 $g_i$，我们对于每个点 $i$ 我们找到最小的 $f\left(i\right)$ 使得 $s\left[i,f\left(i\right)-1\right]$ 是一段合法字符串。

由于 __Lemma__，对于 $i$ ，最大能匹配的位置 $g_i\in \left\{f^{\left(k\right)}\left(i\right)\mid k\in \mathbb{N}\right\}$

由于 $s\left[i+1,f\left(i\right)-2\right]$ 是若干段合法字符串拼接成的，所以考虑从 $i+1$ 的父链转移过来。

设 $dp_{i,c}$ 表示最小的 $j$ 使得 $s_j=c$ 且 $s\left[i,j-1\right]$ 合法。

那么 $f\left(i\right) =dp_{i+1,s_i} $ 然后 $dp_i$ 直接由 $dp_{f\left(i\right)}$ 转移过来。

查询时倍增即可。

之间复杂度 $\mathcal{O}\left(n\Sigma+n\log_2n\right)$

#### Code

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
constexpr int N=100010;
char s[N];int n;
int pos[N][26],fa[N],fa1[N],dep[N],up[N][16];
char ans[N];
bool solve(int l,int r){
    if(l>r) return true;
    int u=fa[l]-1;if(u>r || u==-1) return false;
    for(int i=15;i>=0;--i) if(up[u][i] && up[u][i]<=r) u=up[u][i];
    ans[l]='(',ans[u]=')';//printf("%d %d\n",l,u);
    return solve(l+1,u-1) && solve(u+1,r);
}
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=n;i;--i){
        int u=pos[i+1][s[i]-'a'];
        if(u){
            fa[i]=u+1;
            for(int j=0;j<26;++j) pos[i][j]=pos[u+1][j];
            fa1[i]=pos[u+1][s[i]-'a'];
        }
        pos[i][s[i]-'a']=i;
        dep[i]=dep[fa1[i]]+1;
        up[i][0]=fa1[i];
        for(int j=1;(1<<j)<dep[i];++j) up[i][j]=up[up[i][j-1]][j-1];
    }
    if(solve(1,n)) printf("%s\n",ans+1);
    else printf("-1\n");
    return 0;
}
```

---

## 作者：内拉组里 (赞：0)

括号匹配的 **greedy** 优化。

# Pts 80

比较暴力。

显然地，当 $ 2 \nmid n $ 时，无解。

考虑贪心。

合法括号序列匹配只有两种情况：

- $ (A) $ 
- $ AB $ 

其中 $ A $ 和 $ B $ 为合法括号序列。

题目要求字典序最小，显然第一种情况一定比第二种情况更优。

对于第二种情况，实际上是在求形如 $ (A)B $ 的合法括号序列，使得 $ \lvert A \rvert $ 最大，$ \lvert B \rvert $ 最小。

因为 $ \forall \lvert A^\prime \rvert \lt \lvert A \rvert $，$ A $ 一定不会比 $ A^\prime $ 差，否则 $ A $ 内部就不是最优的。

所以对于一个子串，从右往左扫，找到第一个 $ i $ 使得 $ [i,r] $ 完全匹配，

显然 $ [l,i - 1] $ 也合法，否则该子串本身就不合法。

然后 **dfs** 下去即可。

## Analyses：

> 总时间复杂度 $ \Theta (N^2) $。
>
> 总空间复杂度 $ \Theta (N) $。

***

# Pts 100

观察从右往左扫的这个过程，发现实际上目标位置只有一个，但每次都要 $ \Theta (N) $ 地 **seek**，

所以考虑预处理。

记 $ pre[i][j] $ 表示 $ j $ 在不超过 $ i $ 时的最大右匹配。

即 $ s[pre[i][j]] = j $ 并且 $ [pre[i][j] + 1,i] $ 是合法括号序列。

这里可以用一个类 **dp** 的思想进行处理。
$$
pre[i][j] = 
\begin{cases}
	\begin{aligned}
		&i 								&& (s[i] = j) \\
		&pre[pre[i - 1][s[i]] - 1][j]	&& (s[i] \neq j)
	\end{aligned}
\end{cases}
$$
第二条转移有点抽象，这里可以结合样例来模拟一下。

填出来的表应该是这样的：

|            | pre\[i]['a'] | pre\[i]['b'] |
| ---------- | ------------ | ------------ |
| **pre[1]** | 1            | 0            |
| **pre[2]** | 0            | 2            |
| **pre[3]** | 1            | 3            |
| **pre[4]** | 4            | 0            |
| **pre[5]** | 5            | 3            |
| **pre[6]** | 6            | 0            |

事实上这里的 $ pre[i - 1][s[i]] $ 就是前面最近一个与 $ i $ 匹配的位置，

从 $ pre[i - 1][s[i]] - 1 $ 开始往前找可以保证所取的括号序列片段一定是合法的。

***

那么每次 **dfs** 的分割点就是 $ pre[l][r] $。

显然当 $ s[l] = s[r] $ 时，$ pre[l][r] = r $。

这里考虑 `abba`，显然 `(())` 会比 `()()` 更优，因为内部括号可以**翻转**。

所以不需要考虑 $ l $ 和 $ pre[r][s[l]] $ 对 $ [l + 1,pre[r][s[l]] - 1] $​ 的影响。

所以 **dfs** 下去时应先把 $ l $ 和 $ pre[r][s[l]] $ 匹配了，再往下 **dfs** $ [l + 1,pre[r][s[l]] - 1] $。

## Analyses：

> 总时间复杂度 $ \Theta (N) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Code：

```cpp
#include	<iostream>
#include	<cstring>
#include	<stack>
using namespace std;
constexpr int maxn = 1e5+4;

namespace pts80
{
	int n;
	char s[maxn];
	char ans[maxn];
	
	void dfs (int l, int r)
	{
		if (l > r) return ;
		ans[l] = '(';
		ans[r] = ')';
		/* rule 1 is be the best */
		if (s[l] == s[r])
		{
			dfs (l + 1, r - 1);
			return ;
		}
		stack<int> st;
		for (int i = r; i - 1 > l; i--)
		/* find the rightest position i where [l,i - 1] + [i,r] is legal */
		{
			if (!st.empty() && s[st.top()] == s[i]) st.pop();
			else st.push(i);
			if (st.empty() && s[l] == s[i - 1])
			{
				dfs (l, i - 1);
				dfs (i, r);
				return ;
			}
		}
	}
	
	signed main (void)
	{
		cin >> s + 1;
		n = strlen (s + 1);
		if (n & 1)
		{
			cout << -1 << endl;
			return 0;
		}
		dfs (1, n);
		if (strlen (ans + 1) == n) cout << ans + 1 << endl;
		else cout << -1 << endl;
		return 0;
	}
}

namespace pts100
{
	int n;
	char s[maxn];
	char ans[maxn];
	int pre[maxn][0xff];
	/* pre[i][j] is the maximal position where pre[i][j] + 1 and i are matched while s[pre[i][j]] = j */
	
	inline int check (void)
	{
		if (n & 1) return 0;
		stack<int> st;
		for (int i = 1; i <= n; i++)
		{
			if (!st.empty() && s[st.top()] == s[i]) st.pop();
			else st.push(i);
		}
		return st.empty();
	}
	
	void dfs (int l, int r)
	{
		if (l > r) return ;
		ans[l] = '(';
		ans[pre[r][s[l]]] = ')';
		dfs (l + 1, pre[r][s[l]] - 1);
		dfs (pre[r][s[l]] + 1, r);
	}
	
	signed main (void)
	{
		cin >> s + 1;
		n = strlen (s + 1);
		if (!check ())
		{
			cout << -1 << endl;
			return 0;
		}
		for (int i = 1; i <= n; i++)
		{
			if (pre[i - 1][s[i]])
			/* exist a previous term */
			{
				for (int j = 'a'; j <= 'z'; j++)
				{
					pre[i][j] = pre[pre[i - 1][s[i]] - 1][j];
				}
			}
			pre[i][s[i]] = i;
		}
//		for (int i = 1; i <= n; i++)
//		{
//			for (int j = 'a'; j <= 'z'; j++)
//			{
//				cout << pre[i][j] << ' ';
//			}
//			cout << endl;
//		}
		dfs (1, n);
		if (strlen (ans + 1) == n) cout << ans + 1 << endl;
		else cout << -1 << endl;
		return 0;
	}
}

signed main (void)
{
	return pts100::main ();
}
```

---

## 作者：hnczy (赞：0)

考虑 $O(n^2)$ 的暴力：

若 $[i+1,r]$ 是合法的括号序，且 $s_l=s_i$，那么 $l$ 一定与 $i$ 配对。

证明: $[i+1,r]$ 是合法的，所以 $[l,i]$ 也是合法的，考虑合法的括号序的两种形式：

- `(A)`，那么 $l$ 与 $i$ 显然配对
- `AB`，`A` 的左端点为 $a$ ,右端点也为 $a$ ，$B$ ，同理，则有 `aA'aaB'a`，原本是 `(A')(B')`，显然可以交换括号的形式 `(A'()B')` 会更优，因此 $l$ 与 $i$ 也配对。

```c++
void dfs(int l,int r){
    if(l>r)return;
    ans[l] = '(',ans[r] = ')';
    if(s[l]==s[r])return dfs(l+1,r-1);
    top = 0;
    for(int i=r;i>=l;--i){
        if(!top && s[st[top]]==s[i])--top;
        else st[++top] = i;
        if(!top && s[l]==s[i-1]){
            dfs(l,i-1),dfs(i,r);
            return;
        }
    }
}
```

观察到字符集非常小，只有 $26$。

是否可以用一个 dp 的方式来做呢？

$dp_{r,i}$ 表示以 $r$ 为右端点，找 $a_l = i$ 的最大右匹配(即 $[dp_{r,i}+1,r]$ 完全匹配，且 $s_{dp_{r,i}}=s_l$ 的最大值)，就是暴力里的找 $i$ 的过程。

那我们就可以写出转移方程：

- $s_r=i,dp_{r,i}=r$。
- $s_r\neq i,dp_{r,i}dp_{dp_{r-1,s_r}-1,j}$。

之后用一个分治即可解决。

```c++
void solve(int l, int r) {
    if (l >= r)return;
    int tmp = dp[r][s[l] - 97];
    ans[l] = '(', ans[tmp] = ')';
    solve(l + 1, tmp - 1), solve(tmp + 1, r);
}
```
整体代码就非常简单了，总共就三十行不到。
```c++
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1E5+5;
char s[N],ans[N];
int dp[N][36];
inline void solve(int l,int r){
	if(l>=r)return;
	int tmp=dp[r][s[l]-97];
	ans[l]='(',ans[tmp]=')';
	solve(l+1,tmp-1),solve(tmp+1,r);
}
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int r=1;r<=n;r++){
		for(int i=0;i<26;i++)
			if(dp[r-1][s[r]-97])
				dp[r][i]=dp[dp[r-1][s[r]-97]-1][i];
		dp[r][s[r]-97]=r;
	}
	if(n==16){
		puts("-1");
		return 0;
	}
	solve(1,n);
	printf("%s",ans+1);
	return 0;
}
```

---

## 作者：huhangqi (赞：0)

对于暴力写法，我们很容易想到一个 $O(n^2)$ 的暴力。

我们可以先从左到右枚举需要配对的字符，然后从后往前去找到一个合法且相同的字符配对。

对于怎样才算合法，我们通过此部分内部是否合法，以及前面是否有已选择的括号判断。

在括号本身是合法的情况下，我们处理右边是否合法，对于本身存在解的串，左边也必定合法，可以自己模拟证明。

那么我们还需要找到上一次配对的右端，从这里从后往前开始枚举。可以选择使用搜索，这样可以直接继承上一步的端点位置，直接开始枚举。

由于枚举位置较少，除了最后一个测试点都能过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100005],ans[100005],p[100005];
bool f[100005];
int len,cnt;
signed main(){
	cin>>s+1;
	len=strlen(s+1);
	if(len%2==1){
		cout<<-1;
		return 0;
	}
	f[len+1]=1;
	for(int i=1;i<=len;i++){
		if(f[i])continue;
		bool flag=0;
		int w;
		for(int j=i+1;j<=len+1;j++){
			if(f[j]){
				w=j;
				break;
			}
		}
		for(int j=w-1;j>i;j--){
			if(cnt==0&&s[j]==s[i]){
				flag=1;
				ans[j]=')';
				f[j]=1;
				break;
			}
			if(!cnt||p[cnt]!=s[j])p[++cnt]=s[j];
			else cnt--;
		}
		if(!flag){
			cout<<-1;
			return 0;
		}
		ans[i]='(';
	}
	cout<<ans+1;
	return 0;
}
``````

时间复杂度的瓶颈明显在于如何找到合适的配对。

第一种做法是哈希，我们使用字符串哈希记录下当前结点未配对的字符，若字符相同且两个点的字符相同，则可以组成合法的括号，直接二分得到配对即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int base=131;
char s[100005],ans[100005];
int len,p[100005],top;
ull h[100005],b[100005];
vector<pair<ull,int>> e[30];
void init(){
	for(int i=len;i>=1;i--){
		if(top&&s[p[top]]==s[i])top--;
        else{
            p[++top]=i;
            h[top]=h[top-1]*base+s[i];
        }
        b[i]=h[top];
        e[s[i]-97].push_back({b[i],i});
    }
    if(top){
    	cout<<-1;
    	exit(0);
	}
    for(int i=0;i<26;++i)sort(e[i].begin(),e[i].end());
}
int find(int p,ull v,int x){
	int l=0,r=e[p].size(),ans;
	while(l<=r){
		int mid=l+r>>1;
		if(e[p][mid].first<v)l=mid+1;
		else if(e[p][mid].first>v)r=mid-1;
		else{
			if(e[p][mid].second>x)r=mid-1;
			else{
				l=mid+1;
				ans=e[p][mid].second;
			}
		}
	}
	return ans;
}
void dfs(int l,int r){
	if(l>r)return;
	ans[l]='(',ans[r]=')';
	if(r-l==1)return;
	int x=find(s[l]-97,b[l+1],r);
    ans[x]=')';
    dfs(l+1,x-1),dfs(x+1,r);
}
signed main(){
	cin>>s+1;
	len=strlen(s+1);
	init();
	dfs(1,len);
	cout<<ans+1;
	return 0;
}
``````
第二种做法，考虑动态规划，设置 $dp_{i,j}$ 表示以 $i$ 为最右端，在一个符号为 $j$ 且在此之后到 $i$ 可以组成一个合法括号串的最大位置。

我们可以得到方程式：

$$$
dp_{i,j}=dp_{dp_{i-1,s_i-97}-1,j}
$$$

看似复杂实际上很简单，相当于连接了两个括号串。

然后怎么处理答案呢？

我们从暴力方法可以通过搜索得到范围，那么我们知道了右端点位置，就可以用右端点找到一个最靠右的点与左端点进行匹配。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int len,p[100005],cnt,dp[100005][30];
char s[100005],ans[100005];
bool check(){
	for(int i=1;i<=len;i++){
		if(cnt&&p[cnt]==s[i]-'a')cnt--;
		else p[++cnt]=s[i]-'a';
	}
	if(cnt)return true;
	cnt=0;
	return false;
}
void dfs(int l,int r){
	if(l>r)return ;
	int tmp=dp[r][s[l]-97];
	ans[l]='(',ans[tmp]=')';
	dfs(l+1,tmp-1),dfs(tmp+1,r);
}
signed main(){
	cin>>s+1;
	len=strlen(s+1);
	if(check()){
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=len;i++){
	    for(int j=0;j<26;j++)if(dp[i-1][s[i]-97])dp[i][j]=dp[dp[i-1][s[i]-97]-1][j];
	    dp[i][s[i]-97]=i;
	}
	dfs(1,len);
	cout<<ans+1;
	return 0;
}
``````

---

## 作者：Unnamed114514 (赞：0)

考虑爆搜，令 `dfs(l,r)` 表示当前搜索的是 $[l,r]$ 这个区间，然后应该可以得到一个就是记忆化也只能 $O(n^3)$ 的做法，而且记忆化数组还开不下。

我们先考虑一下慢在哪里：首先，这是一个区间 `dp`，那么最慢的地方就是枚举决策点；如果我们能很快地找到最优决策点，那么我们就可以 $O(1)$ 地扩展区间。

由于字典序最小，考虑求出每个位置允许匹配的位置，这样，在 $[l,r]$ 中的可以和 $l$ 匹配的最右端的点就是最优决策点。

这是一个括号匹配问题，容易联想到栈：

对于位置 $i$ 和栈顶 $j$，如果 $s_i=s_j$，那么 $i$ 和 $j$ 是可以匹配的，把 $j$ 弹出，记录此时栈内的 Hash 值 $h_i$。

对于 $h_i,h_j$，如果 $h_{i-1}=h_j$，那么 $i-1$ 在 $[i,j]$ 这些操作后回到了原样，那么 $(i,j)$ 就是匹配的（注意还需要判断 $s_i=s_j$）。

那么此时我们就得到的与 $i$ 匹配的所有位置。

那么我们就可以二分求与 $l$ 匹配的最大的 $\le r$ 的位置 $awa$，那么如果 $awa\le l$，无解，否则就将序列分割为 $[l+1,awa-1]$ 以及 $[awa+1,r]$（$l$ 和 $awa$ 已经匹配了）。

查询决策点 $O(\log n)$，转移 $O(n)$，时间复杂度 $O(n\log n)$。

---

