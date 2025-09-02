# [USACO22OPEN] Subset Equality S

## 题目描述

奶牛们正在尝试一种相互交换编码信息的新方法，她们在相关的字母中混入不相关的字母，使信息难以解码。

奶牛们传输两个字符串 $s$ 和 $t$，每个字符串的长度不超过 $10^5$，仅由小写字母 'a' 到 'r' 组成。为了尝试理解这条编码消息，你将被给定 $Q$ 个询问（$1 \leq Q \leq 10^5$）。

每个询问给定小写字母 'a' 到 'r' 的一个子集。你需要对每个询问判断 $s$ 和 $t$ 在仅包含询问中给定的字母时是否相等。


## 说明/提示

【样例解释】

对于第一个询问，当仅包含字符 'a' 时，两个字符串均变为 "aa"。

对于第二个询问，第一个字符串变为 "aac" 而第二个字符串变为 "caa"。

【测试点性质】

- 测试点 2 满足 $|s|,|t|,Q\le 1000$。
- 测试点 3-11 没有额外限制。



## 样例 #1

### 输入

```
aabcd
caabd
4
a
ac
abd
abcd```

### 输出

```
YNYN```

# 题解

## 作者：YBaggio (赞：17)

## 题意
首先，给我们两个字符串，分别为 $S,T$ ( $S$ 和 $T$ 的长度均小于 $10^5$  )， 这两个字符串只包含 `a-r` 这些字符。然后给我们 $Q (Q \leq 10^5)$ 个查询，每个查询输入一个字符串，比如输入了 `abc` 这个查询，我们应该判断 $S$ 和 $T$ 中的 `a,b,c` 都提取出来，看是否相同。
__________
## 思路
我们第一眼看到字符只能是 `a-r` 时，会想到为什么不是 `a-z` 呢？我们可以想到用 $O(18^2 \cdot \max(|S|,|T|))$ 的时间复杂度来求解，刚好可以卡过这一题，而 `a-z` 时的 $O(26^2 \cdot \max(|S|,|T|))$ 刚好会被卡。**Tip**：$|S|$ 表示字符串 $S$ 的长度。

### step-1：预处理
我们设 $f_{i,j} = true$ 表示将 `a-r` 中第 $i,j$ 个字符 (如 `a` 和 `c` ) 从 $S,T$ 中提取出来时，提取出来的这些字符并不相等，等于 $false$ 则反之。
#### 举个例子:
- $S:$ `abcd`

- $T:$ `abccd`

那么 $f_{0,2}$ 显然是等于 $true$， 因为将第 $0,2$ 个字符(分别是 `a` 和 `c` )从 $S$ 和 $T$ 提取出来,发现他们不同，所以等于 $true$。
__________________
### step-2：处理询问。
现在我们对于每一个询问就很好处理了。设一个询问为 $C$， 长度为: $|C|$ 那么我们枚举 $C$ 的第 $i$ 和 $j (1 \le {i,j} \le |C|)$， 个字符如果 $f_{C_i,C_j} = true$ 的话，就代表它不合法，反之代表它合法。
______________
### 最后贴上代码

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxlen=200010;
char s[maxlen],t[maxlen],tmp[maxlen];
int q;
bool b[25][25];
int main(){
    cin>>s>>t;
    int lens=strlen(s),lent=strlen(t);
    for(char i='a';i<='r';i++){
        for(char j='a';j<='r';j++){
            char strs[maxlen],strt[maxlen];
            int cnts=0,cntt=0;
            for(int k=0;k<lens;k++){
                if(s[k]==i||s[k]==j)strs[cnts++]=s[k];
            }
            for(int k=0;k<lent;k++){
                if(t[k]==i||t[k]==j)strt[cntt++]=t[k];
            }
            if(cnts!=cntt){b[(int)i-'a'][(int)j-'a']=1;continue;}
            bool flag=0;
            for(int k=0;k<cnts;k++){
                if(strs[k]!=strt[k]){flag=1;}
            }
            b[(int)i-'a'][(int)j-'a']=flag;
        }
    }
    scanf("%d",&q);
    while(q--){
        scanf("%s",tmp);
        int len=strlen(tmp);
        bool flag=0;
        for(int i=0;i<len;i++){
            for(int j=0;j<len;j++){
                if(b[tmp[i]-'a'][tmp[j]-'a']){flag=1;break;}
            }
            if(flag)break;
        }
        if(flag)printf("N");
        else printf("Y");
    }
    return 0;
}```










---

## 作者：Disjoint_cat (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/P8270)

在打这一次 USACO 的时候，我感觉这一题是最难的。

开始，我是这样想的：先预处理出每两个字母放在一起是不是一样的，然后查询的时候看每两个字母放在一起是不是一样的，如果全都是一样的，就输出 `Y`，否则输出 `N`。

设字符串含有的不同的字符数是 $r$，字符串长度是 $N$，复杂度是 $O(r^2(N+Q))$，可过。

此外，我们要特判只有一个字符的情况。而且即使不是一个字符也应该判断对于每一个字符是否相同。（其实不用，因为如果两个字符放在一起相同，一个字符也必然相同。）

然后我又优化了一下，把一个字符的情况直接和两个字符的放在一起判断。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,q,suba,subb;
int T,s,t;
bool can[20][20],ok;
int main()
{
	getline(cin,a);
	getline(cin,b);
	s=a.size(),t=b.size();
	for(int i='a';i<='r';i++)
		for(int j=i;j<='r';j++)
		{
			suba=subb="";
			for(int k=0;k<s;k++)if(a[k]==i||a[k]==j)suba+=a[k];
			for(int k=0;k<t;k++)if(b[k]==i||b[k]==j)subb+=b[k];
			if(suba==subb)can[i-96][j-96]=1;
		}
	cin>>T;
	getline(cin,q);
	while(T--)
	{
		getline(cin,q);
		ok=1;
		for(int i=0;i<q.size()&&ok;i++)
			for(int j=i;j<q.size()&&ok;j++)
				if(!can[min(q[i],q[j])-96][max(q[i],q[j])-96])
				{
					putchar('N');
					ok=0;
				}
		if(ok)putchar('Y');
	}
	return 0;
}
```

---

## 作者：MspAInt (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P8270)

有意思的题！

一位伟大的教练曾说过，要抓住数据的漏洞。

那这题的漏洞就是令人感到奇怪的 “仅由小写字母 `a` 到 `r` 组成”，为什么恰好是 $18$ 个字母，而不是 $26$ 个？

$2^{18}$，很像搜索，但显然不可行。这类询问的题目通常要做预处理，怎么写呢？

手玩了一波，发现一个有趣的结论：**假如字符串 $S$ 能够使两个信息串满足题意，那么其子串也一定可行**。

毕竟提取出的两个部分已经相等，再去掉一些相同的部分何尝不可呢？

此结论显然可逆，问题转化为**找到足够的能够使两个信息串满足题意的子串，证明本次询问的字符串也满足题意。**

肯定要选尽量短的字符串作为子串（不然莫得正确性，枚举还会 T 飞），然后由短至长，一层层往上证，一直证到询问给出的字符串。虽然代码中没有体现出这样的意图，但**本质还是倍增**。

长度为 $1$ 的用不上，长度为 $2$ 的正好，并且复杂度刚好能过，应该是正解。

Code:

```cpp
#include<bits/stdc++.h>
#define End puts("")
#define inf 0x3f
using namespace std;
const int N=1e5+10;
char ch1[N],ch2[N],ch[N],c1[N],c2[N];
int q,l1,l2,s1,s2;
bool f[200][200];
signed main(){
	scanf("%s%s",ch1+1,ch2+1);
	l1=strlen(ch1+1);l2=strlen(ch2+1);
	for(char i='a';i<='r';i++)
		for(char j='a';j<='r';j++){
			s1=s2=0;
			for(int k=1;k<=l1;k++)
				if(ch1[k]==i||ch1[k]==j)c1[++s1]=ch1[k];
			for(int k=1;k<=l2;k++)
				if(ch2[k]==i||ch2[k]==j)c2[++s2]=ch2[k];
			if(s1!=s2)continue;
			f[i][j]=1;
			for(int k=1;k<=s1&&f[i][j];k++)
				f[i][j]=(f[i][j]&&c1[k]==c2[k]);
		}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%s",ch+1);
		int len=strlen(ch+1);
		bool flag=1;
		for(int j=1;j<=len&&flag;j++)
			for(int k=1;k<=len&&flag;k++)
				flag=(flag&&f[ch[j]][ch[k]]);
		if(flag)putchar('Y');
		else putchar('N');
	}
    return 0;
}
```

[record](https://www.luogu.com.cn/record/106810966)

---

## 作者：tzyt (赞：4)

update： 2022/4/17 更正了博客地址

[题目连接](https://www.luogu.com.cn/problem/P8270)

[博客](https://ttzytt.com/2022/04/P8270/)中观看体验更佳
# 1：题意
给你两个字符串，$s$ 和 $t$ （ $s$ 和 $t$ 的长度都不超过 $10^5$ ）。再给你一些询问 （ 询问数量不超过 $10^5$ ），每个询问为小写字母 `'a'` 到 `'r'` 的子集，对于每个询问，请你回答在 $s$ 串和 $t$ 串只包含询问中给定的字母时是否相等。
# 2：分析
## 2.1：暴力
很容易想到暴力的方法，对于每个询问，我们可以只考虑包含在集合中的字符，然后对比两个字符串。当然，这样我们就会需要对于每个询问重新遍历一遍字符串，复杂度也会到达 $n^2$ （ $n$ 为询问的数量和字符串的长度）。通过这个方法，我们可以拿到这道题的部分分。

不过如何才能拿到其他分数呢？

## 2.2：简化问题

直接解决这个问题可能太复杂了，我们可以试试看化简一下这个问题，再把化简过的解法推广到原问题。

我们首先考虑询问中只包含两个字母的情况。设这两个字母为 a 和 b。那么我们如何判断两个只包含 a 和 b 的字符串是否相等呢？

首先需要考虑的肯定是两个串中 a 和 b 的数量是否相等，如果 a 和 b 的数量不等，那这两个串一定不一样。

其次，我们得考虑字符串中每个 a 和 b 的位置，如果位置和数量都对了，这两个串就一定相等了。

判断 a 和 b 的位置时，我们肯定不能直接看它们的下标是否相等，因为我们比较的是这两个字符串中只包含 a 和 b 时的位置，而把其他字符删除后，它们的下标一定会变化。

删除其他字符后，每个字符串的下标其实就是它前面 a 的数量加上 b 的数量（其他的字符都被删除了）。

当然，依次判断每个 a 和 b 的下标太废时间了，我们可以做一些优化。比如我们只需要判断 a 和 b 中一个字符的位置是否全部相等就行了。因为两个字符串 a 和 b 的数量相等，所以只要确定了其中一个字符的位置，另一个的就能确定了（所有不是 a 的位置肯定都是 b）。

这个判断过程其实还可以进一步简化，我们可以只考虑 a 前面 b 的数量，考虑这样一个字符串: `"baa"` 。可以发现如果把 a 前面 b 的数量当作 a 的下标，那么这两个 a 的下标都是一样的。如果我们交换这两个 a，这个字符串还是一样的，所以这两个 a 的下标一样并不会对我们判断 a 的位置产生影响。

总结一下，只包含两个字符的字符串（假设这两个字符为 a 和 b），如果是相等的，一定满足：
- a 和 b 的数量相等
- 每个 a 前面 b 的数量相等 

----
可是我们为什么要用这样的方法求字符串是否相等呢？

因为通过前缀和的方法，我们可以很快的速度处理出这两个字符串只包含两个字符时是否相等。

考虑前文中提到的两个条件。要求出每个 a 前面 b 的数量是否相等（注意这里的 a 和 b 可以是任何字符），我们需要快速求出：
- 原串中每个位置前面每种字符的数量。
- 原串种每种字符的位置（所有位置）

对于第一个问题，我们可以使用前缀和来预处理。

我们开两个数组 `char_sum_s[i][j]` 和 `char_sum_t[i][j]`，分别表示在串 $s$ 和 $t$ 中，从下标 $0$ 到下标 $i$ 为止（包括 $i$）有多少个字符 $j$。

然后使用下面这段代码求出：
```cpp
    for(int i = 0; i < s.length(); i++){
        char_sum_s[i][s[i] - 'a'] = 1; // 打上标记
    }
    for(int i = 1; i < s.length(); i++){
        for(int j = 0; j < 20; j++){ // 枚举字符
            char_sum_s[i][j] += char_sum_s[i - 1][j]; // 求前缀和
        }
    }
```

对于第二个问题，我们开两个 vector `char_pos_s[i]` 和 `char_pos_s[i]`， 分别表示串 $s$ 和 $t$ 中，字符 $i$ 的所有位置，并且使用下面的代码求出：

```cpp
    for(int i = 0; i < s.length(); i++){
        char_pos_s[s[i] - 'a'].push_back(i);
    }
```


## 2.3：考虑原问题
现在我们已经能快速求出只包含两个字符时两个串是否相等了，下面我们来考虑如何把它用到原问题中。

假设两串原本是一样的，有下面几种方法使它们变得不一样：
- 增加字符
- 删除字符
- 交换字符（两个相同字符交换等于没交换）

注：为了方便，我们把判断两字符串在只包含字符 a , b 时是否相等的函数记为 `isok(a, b)` 

对于前面两种改变方式，两串中每种字符的数量肯定会改变。假设增加或删除的字符为 a，那么 `isok(a, 其他任何字符)` 返回的一定是 `false`，这是因为在 $s$ 串中和 $t$ 串中，字符 a 的数量不相等了。

现在考虑交换这种改变方式，假设交换的字符为 a 和 b， 那么 `isok(a, b)` 返回的也一定是 `false`。因为在 $s$ 和 $t$ 中，仅由 a 和 b 组成的字符串一定不相等。

所以，对于每个询问，我们只需要枚举询问中包括的两个不同的字符，然后判断 $s$ 串和 $t$ 串在只包含这两种字符时是否相等就可以了。

注意我们需要把每个 `isok(a, b)` 的结果存下来，这样下此使用时就不需要重新算了。

## 2.3：复杂度分析
- **预处理**： $O(n)$
- **`isok(a, b)`** ：因为需要知道每个 a 前面 b 的数量，所以需要枚举 a，复杂度就为 a 的数量。
- **处理所有 `isok(a, b)`** ： $O(n)$（ $n$ 为字符串长度） 因为要枚举所有的 a 和 b 来计算 `isok(a, b)` ，而所有的 a 和 b 的数量和一定是字符串长度。
- **询问**：$\text{一次询问中字母的数量}^2 \times \text{询问数量}$，因为已经处理过所有的 `isok(a, b)` 了，所以在枚举枚举询问中包括的两个不同的字符时，只需要返回结果，复杂度为 $O(1)$。而一共要枚举 $\text{一次询问中字母的数量}^2$ 次。

# 3：代码
有详细注释，相对来说还是比较快的，[提交记录](https://www.luogu.com.cn/record/73616097)。
```cpp
/*Date: 22 - 03-26 16 22
PROBLEM_NUM: Subset Equality*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
string s, t;
int q;

vector<int> char_pos_s[20], char_pos_t[20];
int char_sum_s[MAXN][20], char_sum_t[MAXN][20]; 
short isok_result[20][20];

bool ans[MAXN];

bool isok(char a, char b){// 判断 s 和 t 串在只包含 a 和 b 的情况下是否等价
    if(isok_result[a][b] != -1 || isok_result[b][a] != -1){// 如果之前已经计算过了，直接返回结果，注意 isok(a, b) == isok(b, a)
        return isok_result[a][b];
    }

    if(a == b){// 如果 a 和 b 相等，则返回这个字符在两串中出现的次数是否相等
        return isok_result[a][b] = (char_pos_s[a].size() == char_pos_t[a].size());
    }

    if(char_pos_s[a].size() != char_pos_t[a].size() || char_pos_s[b].size() != char_pos_t[b].size()){// 如果 a 和 b 的个数在 s 串和 t 串中不相等，返回 false
        return isok_result[a][b] = false;
    }

    vector<int> b_cnt_s;//s串中，某个 a 前面的 b 的数量

    for(int cur_apos : char_pos_s[a]){ // 枚举 s 串中 a 的位置
        b_cnt_s.push_back(char_sum_s[cur_apos][b]);
    }

    for(int i = 0; i < char_pos_t[a].size(); i++){// 枚举 t 串中 a 的位置，对比 t 串中 a 前面 b 的
                                                  // 数量是否和 s 串中 a 前面的 b 的数量相等
        if(char_sum_t[char_pos_t[a][i]][b] != b_cnt_s[i]){
            return isok_result[a][b] = false;
        }
    }
    return isok_result[a][b] = true;
}

void pre_proc(){
    for(int i = 0; i < s.length(); i++){
        char_pos_s[s[i] - 'a'].push_back(i);
        char_sum_s[i][s[i] - 'a'] = 1; // 打标记
    }

    for(int i = 0; i < t.length(); i++){
        char_pos_t[t[i] - 'a'].push_back(i);
        char_sum_t[i][t[i] - 'a'] = 1;
    }

    for(int i = 1; i < s.length(); i++)// s 串前缀和
        for(int j = 0; j < 20; j++)
            char_sum_s[i][j] += char_sum_s[i - 1][j];

    for(int i = 1; i < t.length(); i++)// t 串前缀和
        for(int j = 0; j < 20; j++)   // j 为字符
            char_sum_t[i][j] += char_sum_t[i - 1][j];

    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 20; j++)
            isok_result[i][j] = -1;// 没计算过的时候，设置为 -1
}

int main(){
    ios::sync_with_stdio(false);
    cin>>s>>t>>q;
    
    pre_proc();// 预处理

    for(int i = 1; i <= q; i++){// 枚举每个询问中的每个字符
        string cur_query;
        cin>>cur_query;
        ans[i] = true;
        for(char char_a : cur_query){
            for(char char_b : cur_query){
                if(!isok(char_a - 'a', char_b - 'a')){ // 如果有一个 isok(a, b) == false，则说明不等价 
                                                       //（当 s 和 t 只包含询问中的字符时）
                    ans[i] = false;
                    break;
                }
            }
            if(!ans[i]) break;
        }
    }

    for(int i = 1; i <= q; i++){
        if(ans[i])
            cout<<"Y";
        else
            cout<<"N";
    }
    system("pause");
}
```
最后希望这篇题解能帮到你。如果有看不懂的，或者是发现题解有问题，欢迎通过评论区和私信联系我。

---

## 作者：xixike (赞：3)

[更好的阅读体验](https://xixike.github.io/USACO2022.3%20Silver/)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/P8270)

## Solution

感觉这题是银组三道题里最难的。

主要思路：预处理出任意两个字符能否共存，查询时枚举所有字符对判断即可。

预处理复杂度 $O(18^2n)$，查询复杂度 $O(m\left\vert S\right\vert^2)$，所以总复杂度就是 $O(18^2n + m\left\vert S\right\vert^2)$

接下来说说怎么预处理。

先把所有字符出现的位置全都放到 $\text{vector}$ 里。具体来说，$g_c$ 存字符 $c$ 所有出现的位置的下标，两个串要分开存（感觉说不清楚 QwQ，具体看代码吧）。

- 两个串（以下称 $s$ 串 和 $t$ 串）中某个字符个数不相同，那么这个字符一定不合法。
- 相同时，双指针扫一下。具体而言，枚举 $l_1$ 为字符 $a$ 在 $s$ 串中出现的位置，$l_2$ 为 $s$ 串中 $l_1$ 后面的第一个字符 $b$ 出现的位置，然后判断 $a, b$ 分别在 $s, t$ 串中的位置是否相交，即判断 $a$ 在 $t$ 串中的位置是否在 $b$ 在 $t$ 串中的位置的后面。不交则合法，反之不合法（边界略恶心）。

你迅速码完后交了一发，怎么就 20 分？？？

然后你可以试一试以下样例：

```
ba
ab
1
ab
```

你惊奇的发现输出的是 `Y`，那么这是为什么呢？

问题在于上面这组样例中你会先枚举到 `b`，再枚举 `a`，这就出现了一定问题。

由此可以发现预处理时 $flag_{i, j}$ 和 $flag_{j, i}$ 不一定相等（或者说有可能一个为 0，一个为 1），所以 $j$ 的枚举也需要 1 开始。

查询判断时正反也都要判一下。

（代码略有毒瘤）

## Code
```cpp
#include <bits/stdc++.h>
#define pb push_back
#define ll long long

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 2e5 + 10;
char s[N], t[N], p[N];
int vis[20];
int n, m;
bool flag[20][20];
vector <int> g1[20], g2[20];

inline bool check(int a, int b){
    int l1 = 0, l2 = 0;
    for(; l1 < (int)g1[a].size(); ++l1){
        for(; l2 < (int)g1[b].size() && g1[b][l2] <= g1[a][l1]; ++l2);
        if(l2 < (int)g1[b].size() && g2[a][l1] > g2[b][l2]) return 0;
    }
    return 1;
}

inline void init(){
    n = strlen(s + 1);
    for(int i = 1; i <= n; ++i) g1[s[i] - 'a'].pb(i);
    n = strlen(t + 1);
    for(int i = 1; i <= n; ++i) g2[t[i] - 'a'].pb(i);
    for(int i = 0; i < 18; ++i){
        if(g1[i].size() != g2[i].size()) continue;
        flag[i][i] = 1;
        for(int j = 0; j < 18; ++j)
            if(g1[j].size() == g2[j].size()) flag[i][j] = check(i, j);
    }
}

signed main(){
    scanf("%s%s", s + 1, t + 1);
    init();
    m = read();
    while(m--){
        scanf("%s", p + 1);
        int len = strlen(p + 1), ok = 1;
        for(int i = 1; i <= len; ++i)
            for(int j = i; j <= len; ++j)
                if(!flag[p[i] - 'a'][p[j] - 'a'] || !flag[p[j] - 'a'][p[i] - 'a']) ok = 0;
        putchar(ok ? 'Y' : 'N');
    }
    return 0;
}
```

---

## 作者：Sparkle_ZH (赞：3)

**题意简述**
+ 给定两个字符串 $s$ 和 $t$，仅由小写字母 'a' 到 'r' 组成。
+ $q$ 次询问，每次给出一个小写字母 'a' 到 'r' 的子集，你需要判断 $s$ 与 $t$ 在删去了不包含在子集内的字符后是否相等，相等输出 'Y'，不相等输出 'N'。每次询问独立。
+ $\mid s \mid, \mid t \mid \leq 10^5$，$1 \leq q \leq 10^5$。

**解题思路**

首先思考暴力做法：对于每次询问，对两个字符串暴力地扫一遍，剔除不包含在自己内的字符，然后 $O(n)$ 判断两个字符串是否相等。

时间复杂度达到了 $O(nq)$，显然过不去。怎么办呢？

观察题面，注意到本题有一个不同寻常的限制：

> 仅由小写字母 'a' 到 'r' 组成。

'r' 是字母表里的第 $18$ 个字母，而所有 'a' 到 'r' 的子集个数只有 $2^{18} = 262144$，似乎......不是很大？

考虑使用状压 dp 预处理出答案，我们设询问子集的元素个数为 $k$，分类如下：
- 如果 $k = 1$，比如 'a'、'b'，我们直接统计这个字符在 $s$ 与 $t$ 中出现的次数即可。
- 如果 $k = 2$，比如 'ab'、'ac'，我们用暴力方法判断是否相等。
- 如果 $k \geq 3$，比如 'abc'、'defg'、'acdfh'，我们发现当且仅当询问子集的所有子集的答案都是 'Y' 的时候询问子集的答案才是 'Y'。为了简化，我们只用判断询问子集的所有元素个数等于 $k-1$ 的子集即可。

比如，对于样例中的情况，即 $s = $ "$\texttt{aabcd}$"，$t = $ "$\texttt{caabd}$"：
- 我们观察到两个字符串中 'a'、'b'、'c'、'd' 的数量都相同，所以:
  $dp[$'a'$] = dp[$'b'$] = dp[$'c'$] = dp[$'d'$] = true$
- 对于子集 'ab'、'ac'、'ad'、'bc'、'bd'、'cd'，我们暴力判断，得出:
  $dp[$'ab'$] = dp[$'ad'$] = dp[$'bd'$] = dp[$'cd'$] = true$，$dp[$'ac'$] = dp[$'bc'$] = true$
- 对于子集 'abc'，我们发现 $dp[$'ab'$] = true$，$dp[$'ac'$] = dp[$'bc'$] = false$，不满足它所有子集答案都是 'Y'，所以：
  $dp[$'abc'$] = false$。
- 而对于子集 'abd'，我们发现 $dp[$'ab'$] = dp[$'ad'$] = dp[$'bd'$] = true$，所以 $dp[$'abd'$] = true$。
- 子集 'acd'、'bcd'、'abcd' 同理。

具体如何实现呢？我们考虑使用二进制的思想将所有 'a' 到 'r' 的子集变为一个数。比如将 'a' 转化为 $1$、将 'b' 转化为 $2$、将 'c' 转化为 $4$、将 'abc' 转化为 $7$。

同时，我们预处理出元素个数等于 $1$ 的子集与元素个数等于 $2$ 的子集，进行特殊处理。

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int x = 0; char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = (x<<3) + (x<<1) + ch - '0', ch = getchar();
    return x;
}

const int L = (2<<18);
int q, x, cnt, f1[L], f2[L], tmp1[L], tmp2[L], cnt1[20], cnt2[20];
string s, t, ask;
bool dp[L];

int main() {
    cin >> s >> t;
    for (int i = 0; i < s.size(); i++)
	cnt1[s[i]-'a']++; // 预处理出 s 中每个字符出现的个数
    for (int i = 0; i < t.size(); i++)
	cnt2[t[i]-'a']++; // 预处理出 t 中每个字符出现的个数
	
    for (int i = 0; i <= 17; i++) { // 预处理出元素个数等于 1 的子集与元素个数等于 2 的子集
	f1[(1<<i)] = i+1;
	for (int j = i+1; j <= 17; j++)
    	    f1[(1<<i)+(1<<j)] = i+1, f2[(1<<i)+(1<<j)] = j+1;
    }
	
    for (int i = 1; i <= L-1; i++) {
	if (f1[i] && !f2[i]) { // 元素个数等于 1 的子集
	    if (cnt1[f1[i]-1] == cnt2[f1[i]-1])	
		dp[i] = true;
	    else dp[i] = false;
	} else if (f1[i]) { // 元素个数等于 2 的子集
	    if (cnt1[f1[i]-1] != cnt2[f1[i]-1] || cnt1[f2[i]-1] != cnt2[f2[i]-1])
		dp[i] = false;
	    else {
                // 暴力判断
		cnt = 0;
		for (int j = 0; j < s.size(); j++)
		    if (s[j]-'a' == f1[i]-1 || s[j]-'a' == f2[i]-1)
			tmp1[++cnt] = s[j]-'a';
		cnt = 0;
		for (int j = 0; j < t.size(); j++)	
		    if (t[j]-'a' == f1[i]-1 || t[j]-'a' == f2[i]-1)
			tmp2[++cnt] = t[j]-'a';
				
		dp[i] = true;
		for (int j = 1; j <= cnt; j++)
		    if (tmp1[j] != tmp2[j])
			dp[i] = false;
	    }
	} else {
	    dp[i] = true, x = i;
	    for (int j = 17; j >= 0; j--) {
		if (x < (1<<j)) continue;
		x -= (1<<j);
		if (!dp[i-(1<<j)]) dp[i] = false;
	    }
	}
    }
	
    q = read();
    while (q--) {
	cin >> ask, x = 0;
	for (int i = 0; i < ask.size(); i++)
	    x += (1<<(ask[i]-'a'));
	if (dp[x]) printf("Y");
	else printf("N");
    }
	
    return 0;
}
```

---

## 作者：Presentation_Emitter (赞：2)

正解其他题解里已经讲的比较清楚了，下面是一种随机化乱搞做法。

下面设两个字符串串长同阶，记为 $n$。

首先 $\Theta(nq)$ 的暴力做法比较显然。发现每次枚举一遍整个串很慢，考虑通过一些预处理减少枚举的次数。

观察到字符集大小只有 18。将所有种类的字符随机分成等大的 $k$ 组。之后暴力预处理组内的询问。时间复杂度 $\Theta(nk2^{\lceil{18 \over k}\rceil})$。这样对于每一组询问，因为该询问合法当且仅当不存在两种字符冲突（即任意两种字符提取后相等），所以该询问可以通过预处理数据推出结果的概率约为 $1 \over k^2$。这个概率比较小，但是可以多做几次预处理。设做了 $t$ 次，则概率变为 $1-(1-{1 \over k^2})^t$。不能推出结果的暴力 $\Theta(n)$ 处理即可。

时间复杂度 $\Theta(tnk2^{\lceil{18 \over k}\rceil}+(1-{1 \over k^2})^tnq)$。

Code:

```cpp
cst ll Z=20;
ll n,m,q,bl[Z][18],ord[Z][18],mp[Z][6][3],c1[18],c2[18],S[Z][6],r[100005];
bool eq[Z][6][8];char s[100005],t[100005],qu[19];
il bool chk1()
{
	if(n^m)ret 0;
	for(int i=1;i<=n;++i)if(s[i]^t[i])ret 0;
	ret 1;
}
mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());
int main()
{
	//file("subset");
	scanf("%s%s",s+1,t+1);n=strlen(s+1);m=strlen(t+1);q=rd();
	memset(mp,0xff,sizeof(mp));memset(eq,1,sizeof(eq));
	for(int i=1;i<=n;++i)++c1[s[i]-'a'];
	for(int i=1;i<=m;++i)++c2[t[i]-'a'];
	if(chk1())
	{
		for(int i=1;i<=q;++i)pc('Y');
		puts("");ret 0;
	}
	for(int J=0;J<Z;++J)
	{
		for(int i=0;i<18;++i)bl[J][i]=i/3;
		shuffle(bl[J],bl[J]+18,rng);
		for(int i=0;i<18;++i)
		{
			while(~mp[J][bl[J][i]][ord[J][i]])++ord[J][i];
			mp[J][bl[J][i]][ord[J][i]]=i;
		}
		for(int cs=0;cs<6;++cs)
		{
			for(int S=0;S<8;++S)
			{
				int ss=0;
				for(int i=0,c;i<3;++i)
				{
					if((S>>i)&1)
					{
						ss|=1<<(c=mp[J][cs][i]);
						if(c1[c]^c2[c])eq[J][cs][S]=0;
					}
				}
				if(!eq[J][cs][S])continue;
				int t1=0,t2=0;
				for(int i=1;i<=n;++i)
				{
					r[i]=0;
					if((ss>>(s[i]-'a'))&1)r[++t1]^=s[i]-'a';
					if(((ss>>(t[i]-'a'))&1)&&i<=m)r[++t2]^=t[i]-'a';
				}
				for(int i=n+1;i<=m;++i)if((ss>>(t[i]-'a'))&1)r[++t2]^=t[i]-'a';
				for(int i=1;i<=t1;++i)if(r[i]){eq[J][cs][S]=0;break;}
			}
		}
	}
	//cerr<<clock()<<endl;
	for(int coc=1;coc<=q;++coc)
	{
		scanf("%s",qu+1);int qc=strlen(qu+1),ss=0;bool f=1;
		for(int J=0;J<Z;++J)
		{
			for(int i=0;i<6;++i)S[J][i]=0;
			for(int i=1;i<=qc;++i)S[J][bl[J][qu[i]-'a']]|=1<<ord[J][qu[i]-'a'],ss|=1<<(qu[i]-'a');
			for(int i=0;i<6;++i)f&=eq[J][i][S[J][i]];
		}
		if(!f)pc('N');
		else
		{
			int t1=0,t2=0;
			for(int i=1;i<=n;++i)
			{
				r[i]=0;
				if((ss>>(s[i]-'a'))&1)r[++t1]^=s[i]-'a';
				if(((ss>>(t[i]-'a'))&1)&&i<=m)r[++t2]^=t[i]-'a';
			}
			for(int i=n+1;i<=m;++i)if((ss>>(t[i]-'a'))&1)r[++t2]^=t[i]-'a';
			for(int i=1;i<=t1;++i)if(r[i]){f=0;break;}
			pc(f?'Y':'N');
		}
	}
	puts("");
	ret 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

### Analysis

以下 $n$ 表示串长，$\Sigma$ 表示字符集。

每次询问线性扫描肯定是吃不消的。

我们考虑预处理。

------------

**结论：** 若 $s,t$ 两个字符串中**每种字符出现的次数相同**，且**任意两种字符** $a,b$，均使得 $s,t$ 中提取出 $a,b$（顺序保持不变）的**子序列相同**，则 $s=t$。

**证明：** 假设存在满足上述条件且不同的两个字符串 $s,t$。找到两者第一个不同的位置 $x$。设 $s_x=a,t_x=b(a\ne b)$，则将 $s,t$ 中字符 $a,b$ 分别提取后这一位上是第一个不同的位置，矛盾。假设不成立，原命题得证。

------------

所以，我们可以 $O(|\Sigma|^2n)$ 预处理出 $s,t$ 中提取任意两个字符 $a,b$ 后是否相等，然后 $O(T|\Sigma|^2)$ 求出每个询问的答案。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N -1

string s,t,ss,tt,q;
bool a[18][18];
int cnt[18]; 
bool check(int x,int y){
	ss=tt="";
	for(char i:s) if(i-'a'==x || i-'a'==y) ss=ss+i;
	for(char i:t) if(i-'a'==x || i-'a'==y) tt=tt+i;
	return ss==tt;
}
signed main(){IOS;
	int T,n;
	bool flag;
	cin>>s>>t>>T;
	for(char i:s) cnt[i-'a']++;
	for(char i:t) cnt[i-'a']--;
	For(i,0,16) For(j,i+1,17) a[i][j]=check(i,j);
	while(T--){
		cin>>q;
		sort(q.begin(),q.end());
		n=q.size();
		flag=1;
		for(char i:q) if(cnt[i-'a']!=0){
			cout<<'N';
			flag=0; 
			break;
		}
		if(!flag) continue;
		For(i,0,n-2){For(j,i+1,n-1) if(!a[q[i]-'a'][q[j]-'a']){
			cout<<'N';
			flag=0;
			break;
		}
		if(!flag) break;
		}
		if(flag) cout<<'Y';
	}
	cout<<endl;
return 0;}
```

---

## 作者：huhangqi (赞：0)

发现字母的范围比较小，但是也没有小多少，那么多半是需要对字母组合求解。

第一想法就是给计入的字母状压，确认是否相同。

但是字符串长度又太长了，并且不好优化，只能放弃。

那么该怎么组合？

我们发现影响两个字符串在选择这几个字符后的串是否相等需要看两点：

1. 字符的数量

2. 不同字符之间的位置关系

第一个特别水，每个字符都简单判断一下数量即可，重点在第二点。

两个相同字符串中任意选择两个字符组成的串一定相等，这是显然的。

那么如果这个逆命题成立，即任意选择两个字符在原有的两个字符串中组成串相等，则字符串一定相同，这样我们就可以直接判断任意两个字符了。

虽然这个结论看起来很一眼，但是作为题解还是要稍微证明一下的。

问题可以转化为我们已知每两个组成的字符串，是否能够得到唯一的字符串。

那么我们肯定是有第一位的，只要在这个字符对应其它字符组成的串中的第一个字符就是这个字符，那么这个字符就是第一个字符。

如果找不到那么就一定不存在合法匹配。

那么找到第一个，删掉，再找下一个开头，就是第二个了。

以此类推，最后对应的字符串就是唯一的。

那么代码就好写了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s1[100005],s2[100005],c1[100005],c2[100005],q[100005];
bool ans[40][40];
int n;
signed main(){
	cin>>s1+1>>s2+1;
	int len1=strlen(s1+1),len2=strlen(s2+1);
	for(int i='a';i<='r';i++){
		for(int j=i;j<='r';j++){
			int l1=0,l2=0;
			for(int k=1;k<=len1;k++)if(s1[k]==i||s1[k]==j)c1[++l1]=s1[k];
			for(int k=1;k<=len2;k++)if(s2[k]==i||s2[k]==j)c2[++l2]=s2[k];
			ans[i-'a'][j-'a']=1;
			if(l1!=l2)ans[i-'a'][j-'a']=0;
			else for(int k=1;k<=l1;k++)if(c1[k]!=c2[k])ans[i-'a'][j-'a']=0;
		}
	}
	cin>>n;
	while(n--){
		cin>>q+1;
		int len=strlen(q+1);
		bool fl=1;
		for(int i=1;i<=len;i++){
			for(int j=i;j<=len;j++){
				fl&=ans[q[i]-'a'][q[j]-'a'];
			}
		}
		if(fl)cout<<"Y";
		else cout<<"N";
	}
	return 0;
}

``````

---

## 作者：qip101 (赞：0)

### Solution：

预处理出去掉两个字符之后两个字符串是否相同。

对于每一次询问，枚举每两个字符判断是否相同即可。

详见代码。

### Code

```
#include <bits/stdc++.h> 
#define MAXN 100100
#define MAXM 100
#define ull unsigned long long
#define MAXNLEN 200200
using namespace std;
char s[MAXNLEN],t[MAXNLEN],tmp[MAXNLEN];
int Q;
bool f[MAXM][MAXM];
int main()
{
	//freopen("Asubset.in","r",stdin);
	//freopen("Asubset.out","w",stdout);
	cin >> s >> t;
	int lens=strlen(s),lent=strlen(t);
	for(char i='a';i<='r';i++)
	{
		for(char j='a';j<='r';j++)
		{
			char strs[MAXNLEN],strt[MAXNLEN];
			int cnts=0,cntt=0;
			for(int k=0;k<lens;k++)
				if(s[k]==i || s[k]==j) 
					strs[cnts++]=s[k];
			for(int k=0;k<lent;k++)
				if(t[k]==i || t[k]==j)
					strt[cntt++]=t[k];
			if(cnts!=cntt)
			{
				f[(int)i-'a'][(int)j-'a']=true;
				continue;
			}
			bool flag=false;
			for(int k=0;k<cnts;k++)
				if(strs[k]!=strt[k])
					flag=true;
			f[(int)i-'a'][(int)j-'a']=flag;
		}
	}
	cin >> Q;
	while(Q--)
	{
		scanf("%s",tmp);
		int len=strlen(tmp);
		bool flag=false;
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<len;j++)
				if(f[tmp[i]-'a'][tmp[j]-'a']==true)
				{
					flag=true;
					break;
				}
			if(flag)
				break;
		}
		if(flag)
			cout << "N";
		else
			cout << "Y";
	}
	return 0;
}
```


---

## 作者：SSER_ZRQ (赞：0)

[题目传送门·](https://www.luogu.com.cn/problem/P8270)

主要思路：预处理出任意两个字符是否矛盾，查询时枚举所有字符判断即可。

矛盾：有两个字符 $i,j$ .如果第 $x$ 个 $i$ 在 $s$ 串是在第 $y$ 个 $j$ 的右边，而在 $t$串是在 第 $y$ 个 $j$ 左边，则是矛盾。$i$ 在 $s$ 串是在第 $y$ 个 $j$ 的左边时同理。

用一个二维数组记录任意两个字符矛盾情况。

查询复杂度 $O(m \times |s|^2)$

预处理复杂度：

枚举两个字符 $i,j$  再乘上检验复杂度,即 $i$  字符在 $ s $ 串出现次数 $|i|$ 乘上 $j$  字符在 $s $ 串出现次数 $|j|$ ,总复杂度为 $ O(18^2 \times \sum |i| \times |j| )$ ，很卡.

**如何优化？**

其实，当枚举 $j$ 时，只需枚举最近左边的 $i$ 和最近右边的 $i$

如果矛盾，直接判否。 如果不矛盾，如何证明其他也不矛盾？

设最近左边的 $i$ 为 第 $x$ 个。

因为此时不矛盾，所以 $t$ 串第 $x$ 个 $i$ 位置小于 $j$ 在 $t$ 串位置。

此时有第 $y(y<x)$ 个 $i$ 在第 $x$ 个前 ,那么因为 $y<x$，所以 $t$ 串第 $y$ 个 $i$ 位置小于 第 $x$ 个 $i$ 位置，即小于 $j$ 在 $t$ 串位置，可得出并不矛盾,证毕。

因为枚举 $j$ 有单调性，所以可以搞一个指针，每次枚举新的 $y$ 时往后找第一个位置大于 $j$ 的 $i$ 即可。

证明了正确性，预处理时间复杂度为 $O(18^2 n)$

总时间复杂度为：$O(18^2 n + m \times |s|^2)$

**贴上代码**

**code**

[代码](https://www.luogu.com.cn/paste/magz7o5i)

---

