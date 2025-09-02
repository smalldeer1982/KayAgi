# 378QAQ and Core

## 题目描述

378QAQ 有一个长度为 $n$ 的字符串 $s$。定义一个字符串的“核心”为其字典序最大的子串$^\dagger$。

例如，"bazoka" 的核心是 "zoka"，"aaa" 的核心是 "aaa"。

378QAQ 想要重新排列字符串 $s$，使得其核心的字典序最小。请你找出所有 $s$ 的重排中，核心字典序最小的方案。

$^\dagger$ 字符串 $s$ 的子串是 $s$ 中一段连续的字母。例如，"defor"、"code" 和 "o" 都是 "codeforces" 的子串，而 "codes" 和 "aaa" 不是。

$^\ddagger$ 如果字符串 $p$ 满足以下任一条件，则称 $p$ 的字典序小于 $q$：

- $p$ 是 $q$ 的前缀，且 $p \ne q$；
- 在 $p$ 和 $q$ 第一个不同的位置，$p$ 的该字符的 ASCII 码小于 $q$ 的对应字符。

例如，"code" 和 "coda" 的字典序都小于 "codeforces"，而 "codeforceston" 和 "z" 则不是。

## 说明/提示

在第一个测试用例中，所有可能的重排及其对应的核心如下：

- "qaq"，其核心为 "qaq"。
- "aqq"，其核心为 "qq"。
- "qqa"，其核心为 "qqa"。

因此，所有重排方案中核心字典序最小的是 "qaq"。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
3
qaq
4
cccc
6
bazoka
6
zazzzz
7
ababbbb
7
ccbabcc```

### 输出

```
qaq
cccc
z
zzz
bbababb
cbcacbc```

# 题解

## 作者：yyyyxh (赞：9)

好有趣的一个题！本来在想怎么实现 std 中那个递归做法，然后翻到了[一个厉害的提交记录](https://codeforc.es/contest/1975/submission/263021219)，发现这个题完全可以做线性代码也很好写，所以在这里记录一下。

题目中的 Core 讲的是一个串的最大后缀。这个最大后缀肯定以最大字符（设为 $c$）结尾，那么假设 $c$ 唯一存在，你直接把这个字符扔到末尾就是最优解了。

但往往 $c$ 存在多个，你可以容易地得到第一个和最后一个都填 $c$ 是最优的，如果第一个不填 $c$，那么把首个字符丢到第二个 $c$ 前面一定不劣。末尾不填 $c$ 的话，把末尾的字符串扔到最后一个 $c$ 前面同样不劣。

所以最优的字符串结构形如 $cs_1cs_2c\dots cs_kc$。假设我们已经得知了所有的 $s_1,s_2\dots s_k$（这些字符串可能为空！），那么我们考虑重排这些字符串使得原串 Core 最小化，这于原问题形式类似，也就是变成了一个子问题。即重排 $(cs_1)(cs_2)\dots (cs_k)(c)$ 这 $k+1$ 个字符串。

值得一提的是，这个子问题的单个字符变成了一个字符串，而字符串之间的大小比较不是**直接的字典序比较**，真正的比较关系 $s_1\prec s_2\iff cs_1cs_2c<cs_2cs_1c$，即将 $s_i$ 的末尾塞无限个 $\infin$ 扩充的无穷字符串之间的比较。以及最后一个字符串 $(c)$ 后面跟的是边界，可以认为是跟了一个 $-\infin$ 然后再跟无穷个 $\infin$。

我们将字符串离散化之后可以递归下去做。现在的问题就变成了如何确定一个能生成最优解的 $s_1,s_2\dots s_k$？

第一个观察是由于 $s_i$ 内部可以任意排，所以所有的 $s_i$ 都升序最优。进一步地，所有的 $s_i$ 的第一个字符一定取字符集排序后的一个前缀，否则 Core 的第二个字符不在这个前缀中就严格不优了。

设原串有 $a$ 个 $c$，$b$ 个不是 $c$。当 $b\ge a$ 的时候你发现空串严格不优，因为 Core 中前两个字符都成了 $c$ 而这是可以避免的。所以 $b\ge a$ 的时候你的最优策略肯定是先用字符集前缀填上所有 $s_i$ 的第一个字符。此时已经不是最大值的 $s_i$ 可以直接扔了！可以简单的调整法证明这个策略的正确性，比较繁琐所以不展开了。这样我们一轮一轮填下去直到所有的不是 $c$ 的字符都填完即得到了最终的 $s_i$。

精细实现上述做法，由于每次递归规模减半（$a>b$ 时至多递归规模为 $a\bmod b$，$b\ge a$ 时至多递归规模为 $a$）所以是 $O(n\log n)$ 的。

我们有更高明的实现！！注意到我们递归做法中经常重复扫一些已经不是最大值的 $s_i$，我们考虑改成一种类似非递归的形式。

我们维护一个有序的无穷字符串数列（这个无穷字符串的比较同我们上面所讲的比较），一开始所有位置都是单字符（后面跟一堆 $\infin$）： $A=(-\infin,S_1,S_2\dots,S_n)$（其中 $S$ 是输入字符串排序后的结果）。

然后我们从左到右扫描这个序列 $A$，每次将 $A_i$ 拼接到从左往右第一个最大值位置上，然后删去 $A_i$。**直到 $A_n$ 的最后一个非 $\infin$ 字符是 $-\infin$**（不是删得只剩下一个串的时候！）。那么 $A_n$ 去掉带有 $-\infin,\infin$ 的部分就是我们想要的最小 Core 了！

看起来很神秘？但玩一玩可以发现这和上面的递归做法流程完全等价！只是减少了许多不必要的字符串缩减成一个字符和字符串的移动！

这个过程的复杂度是什么呢？观察发现在这个过程中 $A$ 始终保持有序，所以说它第一个最大值的位置 $pos$ 一定是每次加一，直到其大于 $n$ 之后又跳回某一个位置，暴力维护最大值指针，由于有序用哈希判断最大值，复杂度就是 $O(n)$ 的了。

具体讲下这两个做法为什么本质一样：当每次扫到的 $A_i$ 是以 $-\infin$ 结尾的时候意味着完成了一次递归。每一次 $pos$ 指针跳回一个位置时相当于又给当前 $s_i$ 加完了一轮字符。然后更新指针相当于你扔掉了那些不是最大值的 $s_i$。

My Code:

```cpp
#include <list>
#include <cstdio>
using namespace std;
const int N=1000003;
const int B=29,P=1000000009;
typedef long long ll;
int n;
char s[N];
int pw[N];
struct node{
	list<int> s;int val;
	node(){}
	node(int c):s(1,c),val(c+1){}
	void operator+=(node &x){
		s.splice(s.end(),x.s);
		val=((ll)val*pw[x.s.size()]+x.val)%P;
	}
}o[N];
int f[N],cnt[27];
void solve(){
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;++i) ++cnt[s[i]-96];
	pw[0]=1;
	for(int i=1;i<=n;++i) pw[i]=(ll)pw[i-1]*B%P;
	o[0]=node(0);n=0;
	for(int c=1;c<=26;++c) while(cnt[c]) --cnt[c],o[++n]=node(c);
	int ps=n;
	for(int i=0;i<=n&&o[n].s.back();++i){
		if(ps==n) while(ps>i&&o[ps].val==o[n].val) --ps;
		o[++ps]+=o[i];
	}
	for(int c:o[n].s) if(c) putchar(c+96);
	putchar('\n');
}
int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/CF1975H)

**题目大意**

> 给定长度为 $n$ 的字符串 $s$，重排 $s$ 以最小化 $s$ 的最大字典序子串。
>
> 数据范围：$n\le 10^6$。

**思路分析**

首先一个字符串的最大字典序子串一定是后缀，且由最大字符 $z$ 开头。

$z$ 唯一的时候显然把 $z$ 放在最后，否则如果开头不为 $z$，可以把开头放在第二个 $z$ 的前面，答案变小。

同理末尾不为 $z$ 时把末尾放在最后一个 $z$ 的前面，答案变小。

因此可以调整使得开头结尾都是 $z$，原串就可以写成 $z+S_1+z+S_2+z+\dots+z+S_k+z$ 的形式。

假设 $S_1\sim S_k$ 已知，我们可以把所有 $z+S_i$ 看成单个字符，然后这个问题变成一个 $k$ 个字符的新问题。

因此我们只需要确定所有 $S_i$，排序可以递归解决

并且根据朴素贪心，如果当前的最大后缀从 $z+S_i$ 开始，那么把某个 $j<i$ 的 $S_j$ 里的字符放到 $S_i$ 末尾更优。

如果 $n-k<k$，那么显然每个 $|S_i|\le 1$，否则把 $|S_i|=2$ 的一个字符给 $|S_i|=0$ 的串显然更优。

那么每个 $S_i$ 都是一个字符，递归一次就会给每个 $S_i$ 前面加一个 $z$，进行 $\lfloor (n-k)/k\rfloor$ 轮，然后变成 $n-k\ge k$ 的情况。

对于这种情况，显然每个字符串的开头一定是字符集中最小的 $k$ 个元素，此时如果 $S_i$ 不是最大值，那么 $z+S_i$ 不可能成为最大后缀，那么我们只要在最大的 $S_i$ 后面继续放字符集中最小的元素，不断递归。

容易发现每次两次递归后 $n$ 减半，因此只会递归 $\mathcal O(\log n)$ 轮。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
string core(vector <string> S) {
	if(S.empty()) return "";
	int n=S.size(),x=1;
	string z=S[n-1];
	for(int i=n-2;i>=0&&S[i]==z;--i) ++x;
	if(x==1) return z;
	int y=n-x;
	if(y>=x) {
		int w=x-1,len=w;
		vector <string> T(w,z);
		for(int i=0;i<y;) {
			int nw=len;
			for(int p=w-len;p<w&&i<y;++p,++i) {
				T[p]+=S[i];
				if(p+1<w&&S[i]<S[i+1]) nw=w-p-1;
			}
			len=nw;
		}
		return core(T)+z;
	}
	vector <string> T;
	int k=x/(y+1);
	string kz="";
	for(int i=0;i<k;++i) kz+=z;
	for(int i=0;i<y;++i) T.push_back(kz+S[i]);
	for(int i=0;i<x%(y+1);++i) T.push_back(z);
	return core(T)+kz;
}
void solve() {
	int n; string s;
	cin>>n>>s;
	vector <string> S;
	for(auto c:s) S.push_back(string(1,c));
	sort(S.begin(),S.end());
	cout<<core(S)<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：TTpandaS (赞：2)

本题解不阐述思路，只是对[这篇题解](https://www.luogu.com.cn/article/04teche7)的细节进行解释。题解中提到的 $z$ 不是指最大字符，题解第 $6$ 行代码中的 $z$ 也不是最大字符，而是指将其先填入字符串后会使字典序最大的字符，注意二者区别。例如我们比较 $s_1$ 和 $s_2$ 时，不是比较 $s_1$ 与 $s_2$ 的字典序，而是看 $zs_1zs_2$ 与 $zs_2zs_1$ 的字典序大小。题解第 $28$ 行代码中将 $z$ 放在了字典序最大的位置，因为 $z[z]z[kz+s_i]$ 的字典序大于 $z[kz+s_i]z[z]$（该处 $z,kz,s_i$ 均为题解中所指）。因此按这样的顺序放入 $T$ 中是已经排好序的。

---

## 作者：Unnamed114514 (赞：2)

首先，容易想到，对于原串中的最大字符 $c$，若它只出现了一次，显然把它放结尾更优，这时候答案显然就是一个 $c$。

否则就会出现若干个 $c$，容易发现答案一定是原串的一个后缀，因为它一定比它的前缀大。答案显然是以 $c$ 开头的，如果不以 $c$ 结尾，显然把 $c$ 后面的那一坨放到 $c$ 前面去，这样会变得更小。也就是说，不以 $c$ 结尾的串一定是不优的。

因为让两个 $c$ 要尽量地相隔得远，所以原串的字符应该尽量地加进来，所以说这些字符不应该加到 $c$ 的两侧，所以最终构造的串一定是形如 $c+s_1+c+s_2+\cdots+c+s_k+c$ 的。

如果 $s_i$ 确定的话，我们可以把 $c+s_i$ 当成一个整体的字符递归处理，所以下文的 $c$ 并不是普通的字符，而是一个字符串。

那么我们先得到 $c$ 的数量 $cnt$ 和非 $c$ 的数量 $num$，对此进行分类讨论：

- $cnt=1$

显然，答案为 $c$。

- $num < cnt-1$

注意到此时显然这 $cnt$ 个 $c$ 不能两凉凉之间都有间隔，所以就会有一坨一坨的 $c$，显然它们应该是平均分配的，令 $k=\lfloor\dfrac{cnt}{num+1}\rfloor$，显然会得到若干形如 $c^k+s$ 的串（其中 $c^k$ 表示 $c$ 重复 $k$ 次）。对于剩下的单独的 $c$，会和 $c^k$ 合到一起，此时相当于 $c+c^k+s$ 的形式，我们只需要将这些 $c$ 单独考虑即可。

注意还要加上放在最后的 $z^k$。

但是此时仍然会出锅，比如 `ba` 和 `b`，因为后面要加上 `b` 的缘故，`bab` 是比 `bb` 更小的，但是 `b` 比 `ba` 更小，所以在扩展到字符串后，这里并不是按照字典序排列的，而是按照对后面的影响排列的，或者说是在后面接上了 $\infty$ 之后按照字典序排列的。

- $num\ge cnt-1$

显然每个 $c$ 之间都会间隔字符。

我们还是从小到大往里面插，但是注意到如果插入了 `a` 和 `b` 之后，前面那个 `a` 显然不会成为最大的，这时候就不用插了，动态维护还需要插的即可。

如果插了一部分后剩下的不能插完呢？那么显然是插在前边，因为你 `dab` 和 `dabac` 显然在后面接 `d` 的时候前者影响更大。

值得注意的是，`string` 的比较是 $O(|s|)$ 的，所以应该用原来的串比较而不是新的串比较，否则会随着串变长而退化到 $O(n^2)$。

然后是时间复杂度证明：

- 对于第一种情况，显然是 $O(1)$。

- 对于第二种情况，最后会留下 $num+cnt\bmod (num+1)$ 个串，容易发现当 $num=cnt$ 时规模恰好减半。否则随着 $cnt\bmod(num+1)$ 的增大，$cnt$ 也会增大，也就是说最终的所有的加起来不超过 $cnt$，也就是说规模会减半。

- 对于第三种情况，最后会得到 $cnt-1$ 个串，由于 $cnt-1\le num$ 所以 $cnt\le\dfrac{n}{2}$，所以规模仍然会减半。

因此每次递归规模减半，所以时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
int T,n;
string s;
string solve(vector<string> s){
	if(s.empty()) return "";
	int cnt=1;
	while(cnt+1<=s.size()&&s[s.size()-(cnt+1)]==s[s.size()-1]) ++cnt;
	if(cnt==1) return s[s.size()-1];
	int num=s.size()-cnt;
	if(num>=cnt){
		vector<string> S;
		for(int i=0;i<cnt-1;++i) S.emplace_back(s[s.size()-1]);
		int rest=cnt-1;
		for(int i=0;i<num;){
			for(int j=cnt-1-rest;j<cnt-1&&i<num;++j){
				S[j]+=s[i++];
				if(j!=cnt-1-rest&&s[i-1]!=s[i-2]) rest=cnt-1-j;
			}
		}
		return solve(S)+s[s.size()-1];
	}
	int k=cnt/(num+1);
	string t;
	vector<string> S;
	for(int i=0;i<k;++i) t+=s[s.size()-1];
	for(int i=0;i<num;++i) S.emplace_back(t+s[i]);
	for(int i=0;i<cnt%(num+1);++i) S.emplace_back(s[s.size()-1]);
	return solve(S)+t;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>s;
		vector<string> S;
		for(auto c:s){
			string t;
			t+=c;
			S.emplace_back(t);
		}
		sort(S.begin(),S.end());
		cout<<solve(S)<<endl;
	}
	return 0;
}
```

---

## 作者：eastcloud (赞：2)

[CF1975 题解集](https://www.cnblogs.com/eastcloud/p/18220540)

妙妙题，一个容易想到的做法是每次加字符然后转判定，但是你发现这个判定不是很能做，于是考察这个最小字符串的一些性质来直接求解。

首先，开头肯定是最大字符，我们设其为 $m$，如果整个字符串里只有一个最大字符，那答案显然就是 $m$  否则答案肯定是一个 $m$ 开头的字符串，其中洒着若干 $m$，设其为 $ms_1ms_2ms_3$，值得一提的是结尾肯定也是 $m$，因为如果不是的话我们可以考虑把 $s_3$ 放到某个 $m$ 的前面，答案肯定变小。

由于我们只用考虑第一个 $m$ 后面所有的字符，我们肯定会尝试先枚举用了几个 $m$，然后考虑怎样在 $m$ 中间插入字符使得最大后缀最小。但是这个也很难做，思考一下原因，发现其实是限制太死了，我们不能直接把答案字符串固定。

考虑弱化一些条件，比如我们不固定 $m$ 的个数，先考虑目标字符串把 $s_i$ 排序之后的形态，之后再把 $s$ 换序找后缀，也即确定所有 $s_i$。你发现如果我们能找到其中一个最优解对应的 $s$ 集合，那整个问题就被缩小成了一个规模更小的子问题，我们要把所有绑定完的字符串换序找最小，这好像很行。

考虑我们应该怎样确定 $s_i$：

- 如果最大字符的个数大于其他字符个数，那显然就是把 $m$ 接上小字符，最后剩一些零散的 $m$ 一起递归下去。注意如果最大字符个数很大，需要压缩操作过程。

- 否则考虑从小到大枚举其它字符，插到 $m$ 后面，你可能会想直接从左到右分配几遍就行，因为要保证长度尽量平均，但是有一个性质是如果有 $mc$ 和 $md$ 其中 $d$ 比 $c$ 大，那么后面的字符如果接在 $d$ 后面会更优，这个简单分讨就能证明。 

最后只要递归到平凡的情况即可。

---

