# A and B and Interesting Substrings

## 题目描述

# A 与 B 与有趣的子串

## 题目大意

给定每个小写字母一个数值，给定一个只包含小写字母的字符串 $s$，求 $s$ 的子串 $t$ 个数，使 $t$ 满足：

- 首尾字母相同，长度大于 $1$。
- 首尾字母除外的其余字母的数值之和为 $0$。


A 与 B 正在为程序设计竞赛做准备。

经历了数年的编程，做了很多需要对各种古怪对象进行计算的题目，A 与 B 也形成了独特的喜好。

A 喜爱小写字母。他给定每个字母一个数值，来描述对这个字母的喜爱程度。

B 喜爱子串。他尤其喜爱首尾字母相同的子串（长度大于 $1$）。

并且，A 与 B 有一个字符串 $s$。他们尝试计算出，字符串 $s$ 的子串 $t$ 的个数，其中 $t$ 是 B 喜爱的（即，$t$ 的首尾字母相同且长度大于$1$），且首尾字母除外的所有字母的数值（由 A 给定）之和等于 $0$。

自然地，A 与 B 很快计算出了他们喜爱的子串 $t$ 的个数。你可以算出吗？

## 说明/提示

第一组样例中，满足条件的子串有 $abca$ 与 $bcab$。

第二组样例中，满足条件的子串是两次出现的 $aa$。

Translated by @Capella

## 样例 #1

### 输入

```
1 1 -1 1 1 1 1 1 1 1 1 1 1 1 1 7 1 1 1 8 1 1 1 1 1 1
xabcab
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 1 -1 1 1 1 1 1 1 1 1 1 1 1 1 7 1 1 1 8 1 1 1 1 1 1
aaa
```

### 输出

```
2
```

# 题解

## 作者：HansLimon (赞：6)

## 前缀和水题
- **最初思路**：把第二行的字符串转换成第一行所示的数字然后求前缀和，再判定首位是否相同。

###### ~~可惜这么直接做可能会T~~

- **修改一下**：用map对每一个字符及其前缀和做记录(makepair或者开结构体，不过我开的结构体)。
------------
然后关于前缀和，其实感觉不需要提的：
对于第$ i $个字符，如果在这之前存在第$ x $位字符与该字符相同且第$ x + 1 $位与第$ i - 1 $位字符的前缀和相同，则符合条件，$ otp $ ++。

------------
下面放代码，如果有需要自己想的小伙伴就可以不用看了：
```cpp
#include <cstdio>
#include <map>
using namespace std;

int words[30];
long long otp, bef;
char now;
struct points{
	long long str;
	char id;
	bool operator <(const points & other)const {
		if (str == other.str)return id < other.id;
		return str < other.str;
	}
};
map<points, long long> corder;

int main(){
	for (register int i = 1;i <= 26;i ++)scanf("%d", &words[i]);
	getchar();
	while (now = getchar(), now != 10){
		otp += corder[(points){bef, now}];
		bef += words[now - 'a' + 1];
		corder[(points){bef, now}] ++;
	}
	printf("%lld", otp);
	return 0;
}
```

---

## 作者：2011Andy (赞：2)

## 题目思路
总的思路是利用 map 来记录每个字母和当前字母数值之和的组合出现的次数，在遍历字符串的过程中，如果遇到一个组合之前出现过，那么就可以构成一个满足条件的子串，将 $ans$ 加上这个个数。最后输出 ans 即可。
## AC code
```cpp
#include <bits/stdc++.h>  
#define int long long  
using namespace std;  
int a[30]; // 存储每个字母的数值  
int sum, ans; // sum用于记录当前子串的字母数值之和,ans用于记录满足条件的子串个数  
map<pair<char, int>, int> mp; // 用于记录每个字母和当前字母数值之和的出现次数
signed main(){  
	for(int i = 1 ; i <= 26 ; i++) cin >> a[i]; // 输入每个字母的数值  
	string s;  
	cin >> s; // 输入给定的字符串  
	for(int i = 0 ; i < s.size() ; i++){ // 遍历字符串  
		if(mp[{s[i] , sum}] != 0){ // 如果之前出现过这个字母和当前字母数值之和的组合  
			ans += mp[{s[i] , sum}]; // 说明可以构成一个满足条件的子串,将ans加上这个个数  
		}  
		sum += a[s[i] - 'a' + 1]; // 将当前字母的数值加到sum中  
		mp[{s[i] , sum}]++; // 记录这个组合出现的次数  
	}  
	cout << ans; // 输出答案  
	return 0;  // 华丽的结束
}
```
## 感谢观看~

---

## 作者：codeLJH114514 (赞：0)

## 题解：CF519D A and B and Interesting Substrings

### 题意

对于 $\texttt{a}\sim\texttt{z}$ 的所有字符规定一个分值 $\text{score}$。

给定一个长度为 $n$ 字符串 $t$，问同时满足以下条件的子串 $s$ 有多少个：

- $|s| \geqslant 2$，长度至少为 $2$；
- $s_1 = s_{|s|}$，第一个和最后一个字符相同；
- $\sum_{i=2}^{|s| - 1} \text{score}(s_i) = 0$，除第一个和最后一个的字符以外的字符的分值和为 $0$。

注：字符串 $s$ 的子串的定义为 $s$ 删去一个前缀（可能为空），再删去一个后缀（可能为空）后得到的字符串（可能为空）。

#### 数据范围

- $1 \leqslant n \leqslant 10^5$；
- $-10^5 \leqslant \text{score} \leqslant 10^5$。

### 思路

首先，经常做 Codeforces 的字符串题的人就可以想到**分字母分别考虑**。

因为字母只有 $26$ 个，在套个 $\mathcal{O}(n)$ 也不会超时，所以为了操作方便我们将满足条件的子串依据第一个和最后一个字符划分为 $26$ 种，分别计算。

枚举首尾字符之后，不妨设字符是 $c$，我们先**找到字符串中的所有 $c$**，考虑**分段处理**。

我们发现，所有首尾都是 $c$ 的子串都有如下的形式：

$$c\dots c\dots c \dots c$$

如果我们将每一段的分值和处理出来，那么这样的子串的分值和也好处理了。

总共有 $\mathcal{O}(n)$ 段，肯定不能暴力求段和，我们**使用前缀和来静态地算区间和**。

然后，只有段和还是不能 $\mathcal{O}(1)$ 算出一种首尾都是 $c$ 的子串分值和，所以我们**再套一个前缀和**，即段和的前缀和。

举个例子：

$$
\texttt{xabcaba}
$$

以字符 $\texttt{a}$ 为例，能划分出两段 $\left\{\texttt{bc},\texttt{b}\right\}$

那么，段和的前缀和就是 $\left\{0, \text{score}(\texttt{bc}),\text{score}(\texttt{bcab})\right\}$。

注意一下这里前缀和其实是 $\dots c \dots c \dots$ 的形式。

然后我们就把问题转化成了在一个序列上，找 $a_r - a_{l - 1} = \text{score}_c$ 的 ${l, r}$ 对数。

迭代加 `unordered_map` 存储即可。

时间复杂度 $\mathcal{O}(nm)$：
- $m$ 为字符集大小，本题为 $26$；
- $n$ 为字符串长度，本题最大为 $10^5$；

可以通过本题。

```cpp
#include <bits/stdc++.h>
#define int long long

const int maxn = 100010;
const int maxletter = 32;

std::string str;

int n, s[maxn];
int score[maxn];
int result;

auto sum = [] (int l, int r) {return s[r] - s[l - 1];};

void findletters(std::vector<int>& to, char lt) {
    to.clear();
    for (int i = 1; i <= n; i++)
        if (lt == str[i])
            to.push_back(i);
}

void getdifferences(std::vector<int>& to) {
    std::vector<int> nw;
    for (int i = 0; i < to.size() - 1; i++)
        nw.push_back(sum(to[i] + 1, to[i + 1] - 1));

    to = nw;
}

signed main() {
    std::cin.tie(0);
    std::cin.sync_with_stdio(0);

    for (int i = 1; i <= 26; i++)
        std::cin >> score[i];
    
    std::cin >> str;
    n = str.size();
    str = "@" + str;

    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + score[str[i] - 'a' + 1];
    
    // for (int i = 1; i <= n; i++) std::cout << s[i] << " \n"[i == n];
    
    for (int i = 1; i <= 26; i++) {
        char letter = 'a' + i - 1;
        int scr = score[i];

        // std::cout << "Executing letter " << letter << ":\n";

        std::vector<int> lts;
        findletters(lts, letter);

        if (lts.size() <= 1) continue;

        // for (auto i : lts) std::cout << i << " ";
        // std::cout << std::endl; 

        getdifferences(lts);

        // for (auto i : lts) std::cout << i << " ";
        // std::cout << std::endl; 
        
        std::deque<int> pfs;
        pfs.push_back(0);

        if (lts.size()) {
            pfs.push_back(lts[0]);
            for (int i = 1; i < lts.size(); i++)
                pfs.push_back(pfs.back() + lts[i] + scr);
        }
        
        pfs.pop_front();

        // for (auto i : pfs) std::cout << i << " ";
        // std::cout << std::endl;
        
        std::unordered_map<int, int> appeared;
        appeared[-scr] += 1;
        for (int i = 0; i < pfs.size(); i++) {
            result += appeared[pfs[i] - scr];
            appeared[pfs[i]] += 1;
        }
    }

    std::cout << result << std::endl;
    return 0;
}
```

由于洛谷 Codeforces RemoteJudge 炸了，所以附下 Codeforces 通过的[记录](https://codeforces.com/contest/519/submission/304639438)。

---

## 作者：寒鸽儿 (赞：0)

暴力:  
求前缀和。  
对每一种字符记录之前出现的个数。然后暴力枚举两个点看看这之间的段和是为0。  
复杂度$O(n^2)$  
优化:  
考虑优化暴力,类似于kmp的思想:  
>kmp认为,既然我们已经匹配过了,那么这个串的信息是知道的

那么我们可以记录之前的字串的有效信息,即前缀和。令$pre_i$为前$i$个字母的权值和,对答案有贡献的段可视为:$s_i = s_j \space \&\& \space pre_{i-1} = pre_j$。  
那么,我们只要能快速找到在这之前相同字母的相同$pre_j$即可。  
这时候对每个字母搞个平衡树即可。  
在这里用STL的map实现。  
复杂度$O(nlogn)$  
```cpp
#include <cstdio>
#include <cstring>
#include <map>
#define ll long long
#define itra map<ll,int>::iterator 

using namespace std;

const int L = 123456;
map<ll, int> h[30];
char s[L];
ll pre[L];
int val[30];

int main() {
	for(int i = 0; i < 26; ++i) scanf("%d", val + i);
	scanf("%s", s);
	int len = strlen(s);
	ll cnt = 0;
	pre[0] = val[s[0]-'a']; ++h[s[0]-'a'][pre[0]];
	for(int i = 1; i < len; ++i) {
		int ch = s[i] - 'a';
		pre[i] = pre[i-1] + val[ch];
		cnt += h[ch][pre[i-1]];
		++h[ch][pre[i]];
	}
	printf("%lld\n", cnt);
	return 0;
}
```

---

## 作者：zhengrunzhe (赞：0)

乍一看像个字符串题，~~考虑后缀自动机~~

实际上我也不知道这题怎么黑的

看题面

$1.\text{限制：首尾字符相同}$ 考虑把同种字符的出现位置丢到一个$vector$里面每次枚举每个字母累计答案即可

$2.\text{限制：开区间权值和为0}$ 考虑维护前缀和，$Sum(l,r)=0$即$sum[r-1]-sum[l]=0$即$sum[r-1]=sum[l]$然后我们就可以对于每一个$r$看有几个$l$
满足$sum[l]=sum[r-1]$
总思路：

同种字母的出现位置丢到对应的$vector$里

枚举$a$->$z$累计答案

对于一种字母，开个桶$cnt[i]$表示之前前缀和大小为$i$的位置有几个，对于每次出现位置$pos$，答案加上$cnt[sum[pos-1]]$，然后把$sum[pos]$扔到桶里

因为用map实现桶，所以总复杂度:$O(nlogn)$
```cpp
#include<map>
#include<cstdio>
#include<vector>
#include<cstring>
using std::map;
using std::vector;
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
typedef long long ll;
const int N=1e5+10;
int numeral[26],n;
vector<int>pos[26];
char s[N];
ll sum[N],ans;
map<ll,int>cnt;
inline const ll query(int c)
{
	ll tot=0;
	cnt.clear();
	for (int i=0;i<pos[c].size();i++)
		tot+=cnt[sum[pos[c][i]-1]],
		cnt[sum[pos[c][i]]]++;
	return tot;
}
int main()
{
	for (int i=0;i<26;i++)scanf("%d",&numeral[i]);
	scanf("%s",s+1);
	n=strlen(s+1);
	for (int i=1;i<=n;i++)
		pos[s[i]-'a'].push_back(i),
		sum[i]=numeral[s[i]-'a']+sum[i-1];
	for (int i=0;i<26;i++)ans+=query(i);
	write(ans);
	return 0;
}
```

---

