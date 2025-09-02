# Sofia and Strings

## 题目描述

Sofia has a string $ s $ of length $ n $ , consisting only of lowercase English letters. She can perform operations of the following types with this string.

1. Select an index $ 1 \le i \le |s| $ and remove the character $ s_i $ from the string.
2. Select a pair of indices $ (l, r) $ ( $ 1 \le l \le r \le |s| $ ) and sort the substring $ s_{l} s_{l+1} \ldots s_r $ in alphabetical order.

 Here, $ |s| $ denotes the current length of $ s $ . In particular, $ |s| = n $ before the first operation. For example, if $ s = \mathtt{sofia} $ , then performing the operation of the first type with $ i=4 $ results in $ s $ becoming $ \mathtt{sofa} $ , and performing the operation of the second type with $ (l, r) = (2, 4) $ after that results in $ s $ becoming $ \mathtt{safo} $ .Sofia wants to obtain the string $ t $ of length $ m $ after performing zero or more operations on string $ s $ as described above. Please determine whether it is possible or not.

## 说明/提示

In the first test case, Sofia can perform the following operation:

1. operation of the second type with $ l=1 $ and $ r=5 $ : string $ s $ becomes $ \mathtt{afios} $ after it.

In the second test case, Sofia can perform the following operations:

1. operation of the second type with $ l=1 $ and $ r=2 $ : string $ s $ becomes $ \mathtt{bca} $ after it;
2. operation of the first type with $ i=3 $ : string $ s $ becomes $ \mathtt{bc} $ after it.

In the third test case, it can be shown that it is impossible to obtain $ t $ from $ s $ using the provided operations.

## 样例 #1

### 输入

```
8
5 5
sofia
afios
3 2
cba
bc
5 1
sofia
e
15 7
anavolimilovana
aamanan
26 4
abcdefghijklmnopqrstuvwxyz
nope
26 4
zyxwvutsrqponmlkjihgfedcba
nope
7 3
apricot
cat
3 3
cba
acb```

### 输出

```
YES
YES
NO
YES
NO
YES
NO
YES```

# 题解

## 作者：Komomo (赞：9)

考虑没有排序操作的情况：枚举 $t$ 的每一个字符 $t_i$，匹配第一个 $s_j=t_i$，并删去 $s[1..j]$，若中途无法匹配则无解。这个贪心的正确性在于每次选第一个使得后面选的机会最大化。

现在加入了排序，发现一段字符排序之后是不可逆的，所以我们尽量保证每次匹配操作后 $s$ 保持原来的顺序。同样的，我们每次找到第一个 $s_j=t_i$，对于 $s_k<s_j(k<j)$，这些字符以后肯定是无法匹配的，因为如何排序 $s_k$ 必然在 $s_j$ 前面。于是我们删除这些 $s_k$，为了保持原来顺序，每次把 $s_j$ 与前一个字符交换（排序），一直交换到开头，这里保证了后面机会选择的最大化。

每个字符的出现位置用队列维护，时间复杂度 $\mathcal O(|\Sigma|m)$。

```cpp
const int maxn = 2e5 + 10;
int n, m; char s[maxn], t[maxn]; queue<int> q[26];

void work() {
	n = read(), m = read();
	scanf("%s %s", s + 1, t + 1);
	
	for (int i = 0; i < 26; i ++) while (!q[i].empty()) q[i].pop();
	for (int i = 1; i <= n; i ++) q[s[i] - 'a'].push(i);
	for (int i = 1; i <= m; i ++) {
		int c = t[i] - 'a', id;
		if (q[c].empty()) return printf("NO\n"), void();
		
		id = q[c].front(), q[c].pop();
		for (int j = 0; j < c; j ++)
			while (!q[j].empty() && q[j].front() < id) q[j].pop();
	}
	
	printf("YES\n");
}

```

---

## 作者：Louis_lxy (赞：5)

显然我们一定能通过排序使得当个点与字典序大于它的所有点交换，因此我们只需要判断所有字典序小于它的点的出现时间是否早于它，如果早于它就要先删除。

考虑填入，我们可以直接开 26 个队列，然后对于每个队列存不同字符的出现时间，按升序排序。对于每次要填入的 $t_i$，如果它对应的队列已经空了，则不可能填入，输出 `NO`。否则则遍历所有字典序小于它的队列，如果队头元素的出现时间早于它对应的队列的队头的出现时间，就要删除，因为字典序小于它的无论如何也不可能交换到它后面去。

AC 记录：https://www.luogu.com.cn/record/168256140

---

## 作者：Fengyiwei1234 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1898E)


# 思路

一个显而易见的结论是，如果 $t$ 中的元素不在 $s$ 中，那一定是不行的。

观察样例，发现一个重要的结论：

如果字符串  $s$ 中字符 $x$ 的字典序比字符 $y$ 的字典序小，且 $x$ 在 $y$ 的前面，则在字符串 $t$ 中 $x$ 绝不可能在 $y$ 的后面。

所以，我们可以考虑

## 贪心

如何贪心？

对于从左向右的 $t$ 中的每一个元素，在  $s$ 中查找该元素的位置，并且删除这个位置之前的比该元素的字典序小的字符。

[AC](https://www.luogu.com.cn/record/137891143) 代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int T,n,m;
char a[N],b[N];
int MAIN()
{
	queue<int>pos[309];
	for(int i=1;i<=n;i++)pos[a[i]].push(i);
	for(int i=1;i<=m;i++)
	{
		if(pos[b[i]].size()==0)return false;
		else
		{
			for(char c='a';c<b[i];c++)while(pos[c].size()&&pos[c].front()<pos[b[i]].front())pos[c].pop();
			pos[b[i]].pop();
		}
	}
	return true;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m>>a+1>>b+1;
		if(MAIN())cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

我写了一下翻译，不知道能不能上。

$t$ 组数据。

每一次测试，有长度为 $n$ 的序列 $s$，长度为 $m$ 的序列 $t$。

你可以对 $s$ 进行两种操作：

1. 删除 $s_i,1\le i\le |s|$（$s$ 从 $0$ 开始标号）.

2. 将 $s_l,s_{l+1},\dots,s_r$ 排序（$1\le l\le r\le|s|$）。

上面 $|s|$ 是 $s$ 的长度。

判断 $s$ 是否可以变成 $t$，输出 `YES` 或者 `NO`。

$1\le t\le10^4,1\le\Sigma n,\Sigma m\le2\times10^5$。

------------------------------------------------------

本题考虑贪心，进行配对。

发现一个性质，当 $t_i>t_j(i<j)$ 时，由于 $i,j$ 没有办法用排序达到顺序，所以我们需要让 $i$ 在 $s$ 中的位置小于 $j$ 在 $s$ 中的位置。

而如果 $t_i<t_j(i<j)$，那么可以排序达到我们要求的顺序，$j$ 对 $i$ 的位置选取没有影响。

由上面的做法可以看出，我们从后往前，贪心匹配。

考虑下面的样例：

```
s : aancnaannaa
t : ancana
```

首先，$t$ 的最后一个 `a` 先和 $s$ 的最后一个 `a` 配对。

![](https://cdn.luogu.com.cn/upload/image_hosting/kggo3l12.png)

$t$ 的倒数第二个元素 `n` 和 $s$ 倒数第三个元素 `n` 配对。

由于后面的对 $t$ 的倒数第三个元素 `a` 没有影响，所以 `a` 可以和 $s$ 倒数第二个元素匹配。

![](https://cdn.luogu.com.cn/upload/image_hosting/exlhix20.png)

下面 `c` 的配对显然。

![](https://cdn.luogu.com.cn/upload/image_hosting/px8gatem.png)

此时发现后面的 `c`，`a`，`a` 都对 `n` 的选取有影响，所以取最小的，`n` 要在 `c` 前面。

![](https://cdn.luogu.com.cn/upload/image_hosting/p9aluwmh.png)

所以照着上面的做法模拟就可以了，记录二十六个字母从哪里开始选择，并且记录比自己小的前一个相同字母，方便跳转。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int lens, lent, T, s[N], t[N], las[N][27], nxt[N], tag[27], x;
bool vis[N], ans;
string st;
inline void in(){
    for(int i = 1; i <= lens; i++) vis[i] = 0;
    scanf("%d%d", &lens, &lent);
    cin >> st;
    for(int i = 1; i <= lens; i++) s[i] = st[i - 1] - 'a' + 1;
    cin >> st;
    for(int i = 1; i <= lent; i++) t[i] = st[i - 1] - 'a' + 1;
    ans = 1;
}
inline int get(int x){
    if(vis[x] == 0) return x;
    return nxt[x] = get(nxt[x]);
}
int main(){
    scanf("%d", &T);
    while(T--){
        in();
        if(lens < lent){
            printf("NO\n");
            continue ;
        }
        for(int i = 1; i <= lens; i++){
            nxt[i] = las[i - 1][s[i]];//记录跳跃节点
            for(int j = 1; j <= 26; j++){
                las[i][j] = las[i - 1][j];
            }
            las[i][s[i]] = i;
        }
        for(int i = 1; i <= 26; i++) tag[i] = lens;//tag 就是第 i 个字母从哪里开始跳
        for(int i = lent; i >= 1 && ans; i--){
            x = las[tag[t[i]]][t[i]];
            x = get(x);
            las[tag[t[i]]][t[i]] = nxt[x];
            if(!x) ans = 0;
            else{
                vis[x] = 1;
                for(int j = t[i]; j <= 26; j++) tag[j] = min(tag[j], x);
            }
        }
        if(ans) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

好像洛谷 UKE，就用 CF 上的提交记录证明代码正确性吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ebi2lxt.png)

upd：洛谷上过了

---

## 作者：Msents (赞：1)

## 题意：

给你字符串 $s$ 和 $t$，你要用任意次如下两种操作把 $s$ 变成 $t$：
- 删除 $s$ 中的任意一个字符。
- 将 $s$ 中任意一个区间的字符排序。

## 思路：

第二种操作可以看作是如果左边的字符大于等于当前字符，就可以将当前字符左移一位。

从左到右遍历 $t$，在 $s$ 中寻找当前 $t$ 中对应的字符的第一个，然后将 $s$ 还未匹配完的部分的前面比当前字符小的字符删去，将这个字符挪到前面，于是这一位匹配成功了。

如果中途找不到对应字符，即匹配失败。

实现见代码。

码：

```cpp20
#include<bits/stdc++.h>
using namespace std;
const int MaxN=100000;
void Solve(){
	string s,t;
	int n,m;
	set<int>st[26];
	cin>>n>>m;
	cin>>s>>t;
	for(int i=0;i<n;i++)st[s[i]-'a'].insert(i);
	for(int i=0;i<m;i++){
		if(st[t[i]-'a'].empty()){
			cout<<"NO\n";
			return;
		}
		int pos=*st[t[i]-'a'].begin();
		for(char c='a';c<t[i];c++){
			while(st[c-'a'].size()&&*st[c-'a'].begin()<pos)
				st[c-'a'].erase(st[c-'a'].begin());
		}
		st[t[i]-'a'].erase(st[t[i]-'a'].begin());
	}
	cout<<"YES\n";
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--)
		Solve();
	return 0;
}

```

---

## 作者：AnicoderAndy (赞：0)

[题目传送门](https://codeforces.com/contest/1898/problem/E)
## 分析
注意到：对某个长度为 $n$ 的子串进行排序操作，可以拆分成若干次对长度为 $2$ 的子串排序的操作。具体地，对于子串 $s_is_{i+1}$，如果 $s_i>s_{i+1}$，调换两者顺序；否则不进行任何操作。所以，不妨化繁为简，每次只对长度为 $2$ 的子串考虑排序操作。

基于上面的思考，若能构造出目标字符串，目标字符串中的每个元素 $t_i$，要么是在原地没有因为排序移动过，要么被比它小的字符调换到右边，要么被比它大的字符调换到左边。形式化地，记 $t_i$ 在 $s$ 中的原始下标为 $now_i$，那么对于所有满足 $t_j<t_i$ 且 $j>i$ 的 $j$，有 $now_j>now_i$，对于所有满足 $t_j>t_i$ 且 $j<i$ 的 $j$，有 $now_j<now_i$。

不妨考虑贪心，从小到大循环 $26$ 个小写字母，从右往左填入当前循环的字母，记录 $now$ 在当前位置的后缀最小值 $mi$，最大化当前位置的 $now_i$，使得 $now_i< mi$。如果不存在这样的 $now_i$，则无法构造目标字符串。具体实现时可以分别预先记录每个字母在原字符串、目标字符串中的位置，方便填入。时间复杂度接近 $O(\alpha\cdot m)$，本题 $\alpha=26$。

## C++实现
```cpp
// C++11 or later
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e5 + 10;
int n, m, now[N];
char given[N], target[N];
// v1记录每个字母在原字符串中的位置，v2记录每个字母在目标字符串中的位置
vector<int> v1[26], v2[26];

bool sol() {
    for (int i = 0; i <= 25; i++) v1[i].clear(), v2[i].clear();
    n = read(), m = read();
    scanf("%s", given + 1);
    scanf("%s", target + 1);
    memset(now, 0x7f, sizeof(int) * (m + 2));
    for (int i = 1; i <= n; i++)
        v1[given[i] - 'a'].push_back(i);
    for (int i = 1; i <= m; i++)
        v2[target[i] - 'a'].push_back(i);
    // 循环26个字母：
    for (int i = 0; i <= 25; i++) {
        if (v1[i].size() < v2[i].size()) return false;
        if (v2[i].empty()) continue;
        auto p1 = v1[i].rbegin(), p2 = v2[i].rbegin();

        int mi = 0x7f7f7f7f;
        for (int j = m; j >= 1; j--) {
            if (p1 == v1[i].rend()) return false;
            mi = min(now[j], mi);
            // 试图使即将填入的now[i]小于mi
            if (mi < *p1) {
                while (p1 != v1[i].rend())
                    if (*p1 > mi) p1++;
                    else break;
                if (p1 == v1[i].rend()) return false;
            }
            if (j == *p2) now[*(p2++)] = *(p1++);
            if (p2 == v2[i].rend()) break;  // 当前字母已经填完了
        }
    }
    return true;
}

void tc() {
    int t = read();
    while (t--) {
        if (sol()) printf("YES\n");
        else printf("NO\n");
    }
}

int main() {
    tc();
    return 0;
}
```

---

## 作者：PDAST (赞：0)

## 题意
给你两个字符串和两种操作规则，规则为：
+ 删除一个字符；
+ 对一段字符进行排列。
问，是否能将第一个字符串变成第二个。
## 思路
众所周知，队列是一种先进先出的数据结构，刚好用来维护这道题给出的字符串。具体如何实现呢？让我们先按顺序把第一个字符串存进队列里，即把每个字符放进该字符对应的队列中，接着，再枚举第二个字符串的所有字符，如果队列里已经没有这个字符了，就表示不行，否则就把字典序小于该字符且位置在这个字符之前的给删除，最后弹出这个字符即可。
## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
queue<int>q[31];
int main(){
	int T;
	cin>>T;
	while(T--){
		int n,m,f=1;
		string s,t;
		cin>>n>>m>>s>>t;
		for(int i=0;i<26;i++){
			while(q[i].size())q[i].pop();
		}
		for(int i=0;i<n;i++)q[s[i]-'a'].push(i);
		for(int i=0;i<m&&f;i++){
			int tmp=t[i]-'a';
			if(!q[tmp].size()){
				f=0;
				break;
			}
			for(int j=0;j<tmp;j++){
				while(q[j].size()&&q[j].front()<q[tmp].front())q[j].pop();
			}
			q[tmp].pop();
		}
		if(f)cout<<"YES\n";
		else cout<<"NO\n";
	}
}
~~~

---

