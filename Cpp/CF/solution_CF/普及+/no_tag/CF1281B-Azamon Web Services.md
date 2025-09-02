# Azamon Web Services

## 题目描述

Your friend Jeff Zebos has been trying to run his new online company, but it's not going very well. He's not getting a lot of sales on his website which he decided to call Azamon. His big problem, you think, is that he's not ranking high enough on the search engines. If only he could rename his products to have better names than his competitors, then he'll be at the top of the search results and will be a millionaire.

After doing some research, you find out that search engines only sort their results lexicographically. If your friend could rename his products to lexicographically smaller strings than his competitor's, then he'll be at the top of the rankings!

To make your strategy less obvious to his competitors, you decide to swap no more than two letters of the product names.

Please help Jeff to find improved names for his products that are lexicographically smaller than his competitor's!

Given the string $ s $ representing Jeff's product name and the string $ c $ representing his competitor's product name, find a way to swap at most one pair of characters in $ s $ (that is, find two distinct indices $ i $ and $ j $ and swap $ s_i $ and $ s_j $ ) such that the resulting new name becomes strictly lexicographically smaller than $ c $ , or determine that it is impossible.

Note: String $ a $ is strictly lexicographically smaller than string $ b $ if and only if one of the following holds:

- $ a $ is a proper prefix of $ b $ , that is, $ a $ is a prefix of $ b $ such that $ a \neq b $ ;
- There exists an integer $ 1 \le i \le \min{(|a|, |b|)} $ such that $ a_i < b_i $ and $ a_j = b_j $ for $ 1 \le j < i $ .

## 说明/提示

In the first test case, it is possible to swap the second and the fourth letters of the string and the resulting string "AMAZON" is lexicographically smaller than "APPLE".

It is impossible to improve the product's name in the second test case and satisfy all conditions.

In the third test case, it is possible not to swap a pair of characters. The name "APPLE" is lexicographically smaller than "BANANA". Note that there are other valid answers, e.g., "APPEL".

## 样例 #1

### 输入

```
3
AZAMON APPLE
AZAMON AAAAAAAAAAALIBABA
APPLE BANANA
```

### 输出

```
AMAZON
---
APPLE
```

# 题解

## 作者：万弘 (赞：5)

[本场比赛完整题解](https://www.luogu.com.cn/blog/c2522943959/cf1281round-607-div-2-ti-xie)

### B - Azamon Web Services
简化题意:  给两个串$A,B$,你可以把$A$中的任意两个字符交换(至多一次),问能否让$A$的字典序小于$B$,输出一种可行解,或者给出无解.$|A|,|B|\le 5000$

假设$A$经过一次操作(或者不操作)后得到的最小字典序串是$A'$.如果$A'\ge B$那么显然无解,否则$A'$就是一种可行解

接下来让我们得到这个$A'.$  
枚举$i$,假设$[1,i)$不改变,用$[i,n]$中的一个字符来换掉$a_i$,而字典序满足贪心性质,所以用最小的$a_j$(如果有多个最小,选择$j$最大的)来换掉$a_i$就是$[1,i)$不改变的最优方案,如果此时得到的串字典序小于$B$就直接输出,否则继续尝试

如果这$n$次操作后都无法让串字典序小于$B$,就无解(这题出在div2B似乎不是很合适?我第一眼看了一个假贪心吃了两口罚时)

时间复杂度$O(n^2)$
```cpp
/**********/
str a,b;
void work()
{
	std::cin>>a>>b;
	for(ll s=0;s<a.size();++s)
	{
		ll pos=s;
		for(ll i=s+1;i<a.size();++i)
			if(a[i]<=a[pos])pos=i;
		std::swap(a[s],a[pos]);
		if(a<b)
		{
			std::cout<<a<<std::endl;
			return;
		}
		std::swap(a[s],a[pos]);
	}
	std::cout<<"---"<<std::endl;
}
int main()
{
	ll task=read();
	while(task--)work();
	return 0;
}
```

---

## 作者：ccxswl (赞：2)

#  Azamon Web Services  

看到目前题解都是 $O(n^2)$ 的复杂度，来一发 $O(n\log n)$ 的**贪心**题解。

***

思路很简单，先求经过至多一次的交换后，最小的字符串 $S$。再和 $T$ 比较，如果小于就输出，否则无解。

问题转化成了两个子问题：

1. 求经过至多一次的交换后，最小的字符串 $S$。
2. 和 $T$ 作比较。

第二个问题很好解决，自己看代码吧，详细说第一个问题。

```cpp
bool operator < (string a, string b) {
	int n = min(a.size(), b.size());
	for (int i = 0; i < n; i++) {
		if (a[i] < b[i]) return true;
		if (a[i] > b[i]) return false;
	}
	return (a.size() < b.size());
}
```

**贪心**地想：字符串最小肯定是让**字典序最小的字母尽量靠前**。

现在有了初步的思路：用一个堆来维护 $S$ 中的每个元素，从前往后扫一遍 $S$，如果当前元素等于堆顶，弹出堆顶，否则交换并退出循环。

代码：

```cpp
using pci = pair<char, int>;

bool operator < (string a, string b) {
	int n = min(a.size(), b.size());
	for (int i = 0; i < n; i++) {
		if (a[i] < b[i]) return true;
		if (a[i] > b[i]) return false;
	}
	return (a.size() < b.size());
}

void Sol() {
	string s, t;
	cin >> s >> t;
	priority_queue<pci, vector<pci>, greater<pci>> p;
	for (int i = 0; i < s.size(); i++)
		p.push({s[i], i});
	for (auto &i : s) {
		if (i == p.top().first) p.pop();
		else {
			swap(i, s[p.top().second]);
			break;
		}
	}
	if (s < t) cout << s << '\n';
	else puts("---");
}
```

提交后你会发现错了，为什么？

看下面这组样例：

```
1
AZAAA AAZAA
```

上面代码所构造出的最小 $S$ 是 `AAZAA`，这显然不是正确答案。

交换的 `A` 是要越后面越好，因为在**让字典序最小的字母尽量靠前**的前提下，**让字典序大的字母越靠后越优**。

用 `set` 实现，详细看代码（也没什么细节）。

最终代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int read() {
	int x;
	scanf("%d", &x);
	return x;
}

using pii = pair<int, int>;

bool operator < (string a, string b) {
	int n = min(a.size(), b.size());
	for (int i = 0; i < n; i++) {
		if (a[i] < b[i]) return true;
		if (a[i] > b[i]) return false;
	}
	return (a.size() < b.size());
}

set<pii> p;
void Sol() {
	p.clear();
	string s, t;
	cin >> s >> t;
	for (int i = 0; i < s.size(); i++)
		p.insert({s[i], i});
	for (auto &i : s) {
		char mn = (*p.begin()).first;
		if (i == mn) p.erase(p.begin());
		else {
			auto it = --p.lower_bound({mn, int(1e9)});
			swap(i, s[(*it).second]);
			break;
		}
	}
	if (s < t) cout << s << '\n';
	else puts("---");
}

int T;
int main() {
	T = read();
	while (T--) Sol();
}
```

由于常数和数据等问题，本题时间并不比 $O(n^2)$ 快多少。 

---

## 作者：a1a2a3a4a5 (赞：1)

# 毫无思维难度的暴力

## 1. 思路

- 一眼贪心，直接把一个最小的字母和最前面的字母换就行了。

- 贪心的时候我们把最前面大的字母和最后面小的字母换，你看一下：

初始图：（倒数第一个和倒数第三个等高）

![](https://cdn.luogu.com.cn/upload/image_hosting/dasfs6nk.png?x-oss-process=image/resize,m_lfit,h_800,w_800)

如果与倒数第三个交换：

![](https://cdn.luogu.com.cn/upload/image_hosting/9dyl99fa.png?x-oss-process=image/resize,m_lfit,h_800,w_800)

与倒数第一个交换：（一看这个就最小）

![](https://cdn.luogu.com.cn/upload/image_hosting/gwtexqbi.png?x-oss-process=image/resize,m_lfit,h_800,w_800)

所以肯定要交换和最后一个最小的换。

给你一个无法实现这样情况的代码的 hack 样例：

```
AZAAA 
AAAZA
```

## 2. 复杂度
你可能看的第一眼以为暴力过不去，但是再多看一眼就会~~爆炸~~发现加点小优化就对了！

- 我们有 $ n $ 组或者说 $ t $ 组数据。
- 然后循环从高位枚举 $ s$。
- 枚举 $ 26 $ 个字母。
- 然后枚举 $ s $ 看有没有这个单词。

时间复杂度是：$O\left( ns^{2}\right)$。

哦！过不了。

怎么优化呢？用一个桶存着这个字母可以换的数量，然后就可以发现我们只用执行一次 $ 5000 $ 就可以了，时间复杂度是：$O\left( ns\right)$。

哦！能过。


## 3. 比较函数

 很多人不知道怎么字符串比较，我讲一下：
- 比较字符大小是参考下面的表格：（ascii 码）

![](https://img1.baidu.com/it/u=1233554280,1388386635&fm=253&fmt=auto&app=138&f=JPEG?w=800&h=800)

- 主要就是第一位进行比较，如果相等就下一位，如果不相等就直接返回……
- 如果一个字符串是另一个字符串的前缀，那么长的字符串值更大。

具体看下面代码。

## 4. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tong[27];
string s,t;
bool xiao(string a,string b)
{
	int chang=a.size()-1,bi=b.size()-1,zuo=min(chang,bi);
	for(int i=1;i<=zuo;i++)
	{
		if((int)a[i]>(int)b[i]) return 0;
		else if((int)a[i]<(int)b[i]) return 1;
	}
	if(bi==chang) return 0;
	else if(bi>chang) return 1;
	else return 0;
}
int main()
{
	cin>>n;
	for(int i1=1,chang;i1<=n;i1++)
	{
		cin>>s>>t;
		memset(tong,0,sizeof(tong));
		chang=s.size();
		s='*'+s;t='*'+t;
		for(int i=1;i<=chang;i++)
			tong[s[i]-'A'+1]++;
		bool f=0;
		for(int i=1;i<=chang&&!f;i++)
		{
			for(int j=1;j<s[i]-'A'+1&&!f;j++)
				if(tong[j])
					for(int k=chang;k>i;k--)
						if(s[k]==(j+'A'-1))
						{
							swap(s[i],s[k]);
							f=1;
							break;
						}
			tong[s[i]-'A'+1]--;
		}
		if(xiao(s,t))
		{
			for(int i=1;i<=chang;i++) cout<<s[i];
			puts("");
		}
		else puts("---");
	}
	return 0;
}
```
建议降橙。

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1281B)

## 思路
我们换完后得字符串越小越好，但是直接换可能有字符重复导致有解当成无解，所以我们可以从后往前循环，记录下后缀最小字母和对应的位置，然后尝试交换，如果 $S$ 比 $T$ 小了就输出，否则继续往前找。如果尝试了每一位都不行，就输出 `---` 表示无解。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = (st); i <= (ed); ++i)
#define RFOR(st, ed, i) for (int i = (ed); i >= (st); --i)

//#define debug

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;

const int maxn = 5e3 + 10;

int t;
	string s, c;

	char ch;
	int lens, lenc, idx;

void work_t () {
	cin >> s >> c;
	
	lens = s.size();
	ch = s[lens - 1];
	idx = lens - 1;
	RFOR (0, lens - 1, i) {
		if (ch > s[i]) {
			ch = s[i];
			idx = i;
		}
		swap(s[i], s[idx]);
		if (s < c) {
			cout << s << '\n';
			return;
		}
		swap(s[i], s[idx]);
	}
	printf("---\n");
}
int main () {
	scanf("%i", &t);
	while (t--) {work_t();}
	return 0;
}
```

---

## 作者：alan1118 (赞：0)

## 题意

给你两个字符串 $s,t$，请你最多交换一次 $s$ 中的一对字符，使 $s>t$。请你输出修改后的 $s$。

注意：使交换 $s$ 中的一对字符，不是交换 $s$ 和 $c$ 中的一对字符。

## 思路

首先最先想到的是暴力枚举。过于简单，就不讲了。

### Code

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t;
    cin >> t;
	while(t--)
	{
		string s, c;
		cin >> s >> c;
		if(s < c)
		{
			cout << s << endl;
			continue;
		}
		bool f = false;
		for(int i = 0; i < s.size() && !f; i++)
		{
			for(int j = i+1; j < s.size(); j++)
			{
				swap(s[i], s[j]);
				if(s < c)
				{
					cout << s << endl;
					f = true;
					break;
				}
				swap(s[i], s[j]);
			}
		}
		if(!f) cout << "---" << endl;
	}
	return 0;
}
```

但是单纯的这样暴力枚举会 TLE 在第 $10$ 个点，所以我们要考虑优化。

不难看出，我们要想让 $s>t$，其实让 $s$ 尽可能大就行了。那么我们就可以枚举 $s$ 的每一位，然后找到这意味往后最大且最靠后的那位，最后交换 $s_i$ 和这一位就 AC 了。

## AC Code

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t;
    cin >> t;
	while(t--)
	{
		string s, c;
		cin >> s >> c;
		if(s < c)
		{
			cout << s << endl;
			continue;
		}
		bool f = false;
		for(int i = 0; i < s.size() && !f; i++)
		{
			int p = i;
			for(int j = i+1; j < s.size(); j++)
				if(s[j] <= s[p]) p = j;
			swap(s[i], s[p]);
			if(s < c)
			{
				cout << s << endl;
				f = true;
				break;
			}
			swap(s[i], s[p]);
		}
		if(!f) cout << "---" << endl;
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[洛谷](https://www.luogu.com.cn/problem/CF1281B) [CF](http://codeforces.com/problemset/problem/1281/B)

有一个比较显然的暴力，枚举 $s$ 的第 $1$ 到 $n$ 位，枚举到第 $i$ 位时，每次从后面找到第 $i$ 位后最小且最靠后的字符和它交换，判断 $s$ 是否比 $t$ 大。

如果两个字符相同，那么交换后面的不会更劣，因为这样可以把前面的这个更大的字符换到更后面的地方去。比如 `zaa`，把 `z` 交换到第 $2$ 和 $3$ 位分别是 `aza` 和 `aaz`，显然把 `z` 往后放会好一点。

注意特判 $s$ 本来大于 $c$ 的特殊情况，时间复杂度 $O(t|s|^2)$。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m;
char s[5001], c[5001];
bool sless(){
	for (int i = 0; i < min(n, m); i++){
		if (s[i] < c[i]) return true;
		else if (s[i] > c[i]) return false;
	}
	if (n < m) return true;
	else return false;
}
signed main(){
	scanf("%d", &t);
	while (t--){
		scanf("%s%s", s, c);
		n = strlen(s), m = strlen(c);
		if (sless()){printf("%s\n", s); continue;}//特判
		int flag = 0;
		for (int i = 0; i < n; i++){
			char minc = char('Z' + 1);
			int pos = 0;
			for (int j = i + 1; j < n; j++)
				if (s[j] <= minc) minc = s[j], pos = j;//往后找最小的
			swap(s[i], s[pos]);
			if (sless()){printf("%s\n", s); flag = 1; break;}
			swap(s[i], s[pos]);
		}
		if (!flag) puts("---");//记得无解
	}
	return 0;
}
```

---

