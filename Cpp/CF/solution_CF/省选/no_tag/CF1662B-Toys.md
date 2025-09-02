# Toys

## 题目描述

你有一些纸，你可以在纸的正反面各写一个字母。现在你要用这些纸拼三个单词。纸的顺序可以重新排列，正反面都可以用（当然，你不能同时用一张纸的正反面）。三个单词不必同时拼出，只要保证每个单词都能拼即可。

请你求出，为了拼这三个单词，你至少需要多少纸，并给出一种可行的写字母方案。

## 说明/提示

样例一中，答案用了两张纸：第一张一面写 A，另一面写 G；第二张一面写 A，另一面写 M。

三个单词中，单词 AA 可以用两个 A 拼出，单词 GA 可以用第一张纸的 G 与第二张纸的 A 拼出，单词 MA 可以用第二张纸的 M 和第一张纸的 A 拼出。

## 样例 #1

### 输入

```
AA
GA
MA```

### 输出

```
2
AG
AM```

## 样例 #2

### 输入

```
TEDDY
HEDWIG
RACCOON```

### 输出

```
8
AT
CH
CY
DG
DO
ER
IN
OW```

## 样例 #3

### 输入

```
BDC
CAA
CE```

### 输出

```
4
AD
AE
BB
CC```

# 题解

## 作者：an_ancient_ghoul (赞：0)

# My solution for CF1662B.Toys
赞美欧姆弥赛亚！！！！

为什么网上没有这题的题解呢？

------------

额，貌似我自二〇二二年底就在想这题了。
```
Toys is one of the most challenging problems of the contest,
but no particular knowledge of algorithms and data structures
is required to solve it. 
We propose two greedy solutions that start with a common 
reformulation of the problem statement.
The limit to the length of the three names is very permissive (≤1000), 
so there is no need to pay much attention to computational efficiency.
```


------------
 _——CF 官方题解_ 

 _“一个字，贪就完了。”——某同机房大佬_ 
 
## 分析
 
$$len=\max(l1,l2,l3,\frac{1}{2}\lceil\sum_{1\leq i\leq 3}\max cnt_{ic}\rceil)$$

对于每一个单词，我们记下其中每个字母 $c$ 的出现频率 $cnt_{ic}$，然后贪掉那些在两个以上单词中出现了的字母。对于可以贪的字母 $c$，我们都有: 

$$  \sum_{1\leq i\leq 3}{cnt_{ic}} \geq 2$$ 

以此解决需要,对于在此阶段所有被贪掉的字母 $c$，都物尽其用，它的纸张的另一面是一个与这个字母无关的第三个单词的字母，对于每一次贪心选择 $cnt_{xc}$ 最小的单词 $x$ 作为“无关”的单词，再将能够被贪掉的单词 $i$ 中的 $cnt_{ic}$ 减一。 
  
我们最多可以贪掉最多 $mn=\min(l1,l2,l3)$ 次，因为可以想象我们每一个贪掉的字母，其背面都应该有一个与之无关的单词中的字母，否则没有意义，比如在极端情况下，比如 “AAAA AACA BB” 字母 A 虽然在前两个单词中出现了三次，但事实上有意义的贪心只有两次。  

然后我们就处理它们的背面，因为标记可以贪掉的字母时已经标记了“无关”的单词了，直接从处理完了的“无关”的单词中随便拿一个字母贴在背面。

紧接着，处理无法被贪和垫背的字母。对于这些字母，需要 $\lceil\dfrac{\sum cnt}{2}\rceil$ 张纸。贪就是了，对于多出的那一张，背面随意。

## code

```cpp
#include<bits/stdc++.h>
#define maxn 100100
#define reg register
#define llg long long
#define inf 0x3f3f3f3f
using namespace std;
string A[3];
int cnt[3][30], len[3];
int n = 3;
vector<string> ans;
vector<int > aa[3];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int mn = inf;
	for (reg int i = 0; i < 3;i++)
	{
		cin >> A[i];
		aa[i].clear();
		for (reg int j = 0;  j < 26; j++) cnt[i][j] = 0;
		len[i] = A[i].length();
		for (reg int j = 0; j < len[i]; j++) cnt[i][A[i][j] - 'A']++;//count
		mn = min(mn, len[i]);//the maxium amount of characters we need

	}
	ans.clear();
	for (reg int i = 0; i < 26; i++)
	while (mn > 0 && (cnt[0][i] > 0) + (cnt[1][i] > 0) + (cnt[2][i] > 0) >= 2) 
	{//first greedy
		int tmp = 0;
		for (reg int j = 1; j <= 2; j++) if (cnt[j][i] < cnt[tmp][i]) tmp = j;
		for (reg int j = 0; j < 3; j++) if (j != tmp) cnt[j][i]--;
		//we can get a character's free at the back of a paper of tmp's
		aa[tmp].push_back(i);//the number we can use directly.
		mn--;
	}
	for (reg int i = 0; i < 3; i++)
	for (reg int j = 0; j < 26; j++)
	while (!aa[i].empty() && cnt[i][j] > 0) //deal with the rest characters
	{//greedy!!!
		string cur;
		cur.push_back('A' + aa[i].back());
		cur.push_back('A' + j);
		ans.push_back(cur);
		cnt[i][j]--; aa[i].pop_back();
	}
	for (reg int i = 0; i < 3; i++)
	{
		len[i] = 0;
		for (reg int j = 0; j < 26; j++)len[i] += cnt[i][j];//count the 
	}
	while (len[0] + len[1] + len[2] > 0)
	{//to solve all of we got
		int tmp = 0;
		for (reg int j = 1; j <= 2; j++) if (len[j] < len[tmp]) tmp = j;
		string cur;
		for (reg int j = 0; j < 3; j++) if (j != tmp) 
		{
			char x = 'A';
			for (reg int k = 0; k < 26; k++) 
			if (cnt[j][k] > 0)
			{
				cnt[j][k]--, len[j]--, x = 'A' + k;
				break;
			}
			cur.push_back(x);
		}
		ans.push_back(cur);
	}
	cout << ans.size() << '\n';
	for (reg int i = 0; i < ans.size(); i++) cout << ans[i] << '\n';
	return 0;
}
```

原本想 CTJ 的，看见没有题解，就服务一下后人吧！

---

