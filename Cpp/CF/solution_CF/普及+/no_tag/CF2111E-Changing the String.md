# Changing the String

## 题目描述

Given a string $ s $ that consists only of the first three letters of the Latin alphabet, meaning each character of the string is either a, b, or c.

Also given are $ q $ operations that need to be performed on the string. In each operation, two letters $ x $ and $ y $ from the set of the first three letters of the Latin alphabet are provided, and for each operation, one of the following two actions must be taken:

- change any (one) occurrence of the letter $ x $ in the string $ s $ to the letter $ y $ (if at least one occurrence of the letter $ x $ exists);
- do nothing.

The goal is to perform all operations in the given order in such a way that the string $ s $ becomes lexicographically minimal.

Recall that a string $ a $ is lexicographically less than a string $ b $ if and only if one of the following conditions holds:

- $ a $ is a prefix of $ b $ , but $ a \neq b $ ;
- at the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that comes earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test case, both operations need to be applied to the first letter:

1. after the first operation, $ s =  $ "bb"
2. after the second operation, $ s =  $ "ab"

In the second test case, the string could change as follows:

1. "bbbbabbbbb" (changed the $ 5 $ -th letter)
2. "cbbbabbbbb" (changed the $ 1 $ -st letter)
3. "cbbbabbbbb" (did nothing)
4. "cbbaabbbbb" (changed the $ 4 $ -th letter)
5. "abbaabbbbb" (changed the $ 1 $ -st letter)
6. "abcaabbbbb" (changed the $ 3 $ -rd letter)
7. "abcaabbbbb" (did nothing)
8. "aacaabbbbb" (changed the $ 2 $ -nd letter)
9. "aacaabbbbb" (did nothing)
10. "aaaaabbbbb" (changed the $ 3 $ -rd letter)

## 样例 #1

### 输入

```
3
2 2
cb
c b
b a
10 10
bbbbbbbbbb
b a
b c
c b
b a
c a
b c
b c
b a
a b
c a
30 20
abcaababcbbcabcbbcabcbabbbbabc
b c
b c
c a
b c
b c
b a
b c
b c
b a
b a
b a
b a
c a
b c
c a
b c
c a
c a
b c
c b```

### 输出

```
ab
aaaaabbbbb
aaaaaaaaaaaaaaabbbabcbabbbbabc```

# 题解

## 作者：lilong (赞：2)

首先可以把所有操作的类型及时间记录下来，分类存进 map 里。

根据贪心，显然越靠前的字母越小越好。从前往后考虑每位 $s_i$：

- $s_i=a$ 已经最优了，无需处理。
- $s_i=b$ 优先考虑 $b \rightarrow a$，如果不存在这样的操作就考虑 $b \rightarrow c \rightarrow a$（先找 $b \rightarrow c$ 是否存在，存在则取时间最早的，并在 $c\rightarrow a$ 中找到第一个时间在它后面的，若能找到则更新，**并同时删除两个操作**）。
- $s_i=c$ 优先考虑 $c \rightarrow a$，如果不存在则考虑 $c\rightarrow b\rightarrow a$（先找 $c \rightarrow b$ 是否存在，存在则取时间最早的，$s_i\leftarrow b$，并在 $b\rightarrow a$ 中找第一个时间在它后面的，**此时再删除第一步的操作**。若能找到则更新为 $a$，**并删除该操作**）。

注意实现时一定要**先查找完再删除**对应的迭代器，否则会因迭代器无效而导致 RE。


```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
map<int,int> ba,bc,ca,cb;
string s;
int n,m;
char x,y;
void solve(){
    ba.clear();bc.clear();ca.clear();cb.clear();
    cin>>n>>m;
    cin>>s;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        if(x=='b'&&y=='a')ba[i]=i;
        if(x=='b'&&y=='c')bc[i]=i;
        if(x=='c'&&y=='b')cb[i]=i;
        if(x=='c'&&y=='a')ca[i]=i;
    }
    for(int i=0;i<n;i++){
        // cout<<i<<endl;
        if(s[i]=='a')continue;
        if(s[i]=='b'){
            if(ba.size()){
                auto it=ba.begin();
                ba.erase(it);
                s[i]='a';
            }
            else if(bc.size()){
                auto it=bc.begin();
                auto it1=ca.upper_bound(it->second);
                if(it1!=ca.end()){
                    s[i]='a';
                    bc.erase(it);
                    ca.erase(it1);
                }
            }
        }
        if(s[i]=='c'){
            if(ca.size()){
                auto it=ca.begin();
                ca.erase(it);
                s[i]='a';
            }
            else if(cb.size()){
                auto it=cb.begin();
                s[i]='b';
                auto it1=ba.upper_bound(it->second);
                cb.erase(it);//必须先查找再删迭代器，否则 it 指向的迭代器无效会发生 Runtime Error。或者记录迭代器对应的值也可以
                if(it1!=ba.end()){
                    s[i]='a';
                    ba.erase(it1);
                }
            }
        }
    }
    cout<<s<<'\n';
    return;
}
int main(){
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：Kevin911 (赞：1)

先观察一些性质。

1.$a$ 不用处理。

2.只有五类有效操作：$b$ 到 $a$，$b$ 到 $c$ 到 $a$，$c$ 到 $a$，$c$ 到 $b$，$c$ 到 $b$ 到 $a$。

3.若将一组 $bc$ 变为 $aa$，操作 2 和操作 5 不同时用，因为用操作 1和操作 3替换更佳。

4.若将 $c$ 变为 $a$，尽量使用操作 1，因为若用操作 2，可以节省一次操作1,在后面把 $a$ 变为 $b$ 无区别；作用于下一个 $c$ 变为 $a$，即操作 5，则违背了性质 2。

5.将 $c$ 变为 $a$ 同理。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
string ss;
set<int> s[3][3];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		for(int i=0;i<=2;i++)	
			for(int j=0;j<=2;j++) s[i][j].clear();
		cin>>n>>q>>ss;
		ss=' '+ss;
		for(int i=1;i<=q;i++)
		{
			char x,y;
			cin>>x>>y;
			s[x-'a'][y-'a'].insert(i);
		}
		for(int i=1;i<=n;i++)
		{
			if(ss[i]=='a') continue;
			if(ss[i]=='b')
			{
				if(!s[1][0].empty())
				{
					s[1][0].erase(s[1][0].begin());
					ss[i]='a';
					continue;
				}
				if(!s[1][2].empty())
				{
					auto p=s[2][0].lower_bound(*s[1][2].begin());
					if(p!=s[2][0].end())
					{
						s[1][2].erase(*s[1][2].begin()),s[2][0].erase(p);
						ss[i]='a';
					}
					continue;
				}
			}
			if(ss[i]=='c')
			{
				if(!s[2][0].empty())
				{
					s[2][0].erase(*s[2][0].begin());
					ss[i]='a';
					continue;
				}
				if(!s[2][1].empty())
				{
					auto p=s[1][0].lower_bound(*s[2][1].begin());
					if(p!=s[1][0].end())
					{
						s[2][1].erase(*s[2][1].begin()),s[1][0].erase(p);
						ss[i]='a';
					}
					else s[2][1].erase(*s[2][1].begin()),ss[i]='b';
					continue;
				}
			}
		}
		cout<<ss<<endl; 
	}
}
```

---

## 作者：sSkYy (赞：1)

# [CF2111E Changing the String](https://www.luogu.com.cn/problem/CF2111E)

## 题意

给定一个仅由 $a,b,c$ 组成的字符串 $S$。

给出 $q$ 次操作。每个操作 $(x,y)$ 表示将 $S$ 中任意一个 $x$ 换成 $y$，**可以不换**。

求按**给定的顺序**执行所有操作后得到字典序最小的字符串。

## 题解

简单贪心。

首先越前面优先级越高，所以从前往后考虑，能换则换。

下面考虑如何操作：

- 对于 $a$，不用换，所以 $a \rightarrow b$ 和 $a \rightarrow c$ 没用。
- 对于 $b$，考虑 $b$ 换成 $a$，尝试用 $b \rightarrow a$ 或者 $b \rightarrow c \ + c \rightarrow a$，两者无优先顺序。
- 对于 $c$，
  1. 先考虑将 $c$ 换成 $a$，尝试用 $c \rightarrow a$ 或者 $c \rightarrow b \ + \ b \rightarrow a$，两者无优先顺序。
  2. 再考虑将 $c$ 换成 $b$，尝试用 $c \rightarrow b$。

注意复合操作时，如 $c \rightarrow b \ + \ b \rightarrow a$ 要保证 $c \rightarrow b$ 在 $b \rightarrow a$ 的前面，并且要确保找到第一个位置大于 $c \rightarrow b$ 的 $b \rightarrow a$，保证后续能用到的 $b \rightarrow a$ 操作尽可能靠后，用 `upper_bound` 实现。

实现时，用 `set` 维护每种操作的位置，用 `insert` 插入，`erase` 删除使用过了的操作，`upper_bound` 满足复合操作的需求。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,q;
set<int> ba,bc,cb,ca;//b->a b->c c->b c->a
char s[N];

void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>s[i];
    ba.clear(),bc.clear(),cb.clear(),ca.clear();//多测清空
    for(int i=1;i<=q;i++){
        char x,y;
        cin>>x>>y;
        if(x=='b'){
            if(y=='a') ba.insert(i);
            else if(y=='c') bc.insert(i);
        }else if(x=='c'){
            if(y=='a') ca.insert(i);
            else if(y=='b') cb.insert(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(s[i]=='b'){
            if(!ba.empty()){
                s[i]='a';
                ba.erase(*ba.begin());
            }else{
                if(!bc.empty()&&!ca.empty()){
                    int BC=*bc.begin();
                    auto CA=ca.upper_bound(BC);
                    if(CA==ca.end()) continue;
                    s[i]='a';
                    bc.erase(BC);
                    ca.erase(*CA);
                }
            }
        }else if(s[i]=='c'){
            if(!ca.empty()){
                s[i]='a';
                ca.erase(*ca.begin());
            }else{
                if(!cb.empty()){
                    if(!ba.empty()){
                        int CB=*cb.begin();
                        auto BA=ba.upper_bound(CB);
                        if(BA==ba.end()){
                            s[i]='b';
                            cb.erase(CB);
                        }else{
                            s[i]='a';
                            cb.erase(CB);
                            ba.erase(*BA);
                        }
                    }else{
                        s[i]='b';
                        cb.erase(*cb.begin());
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++) cout<<s[i];
    cout<<"\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：Z3k7223 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Z3k7223/p/18958738)

模拟赛考到，好像场上写出了线性做法？

## Solution

要使最终串的字典序最小，肯定要从第一位贪心地来看。对于当前位，有如下情况：

- `a`：不用管。

- `b`：有两种修改方法，分别是 $b\to a$ 和 $b\to c\to a$，思考哪一种更优，如果我们在可以选择的情况下使用了一个 $b\to c\to a$，则有可能会破坏后面的一个 `c` 的 $c\to a$，而选择 $b\to a$ 虽然有可能破坏一个 $c\to b\to c$，但是仍然会留下至少一个 $c\to b$，可以让后面的 `c` 有机会变得更优，故应该优先选择 $b\to a$。

- `c`：同理，优先考虑变成 `a`，先后贪心尝试 $c\to a$，$c\to b\to a$，$c\to b$。

至于怎么计算每种配对，我用的是类似括号匹配的方式，匹配一组 $b\to c\to a$ 和 $c\to b\to a$，剩下的或者被拆掉的也加入匹配。

时间复杂度 $O(n+q)$。

## Code

[Link](https://codeforces.com/contest/2111/submission/326472305).

---

## 作者：postpone (赞：0)

对于每个操作，可以不做，或者选一个位置进行替换。最后需要整个字符串字典序最小。

换个角度想，我们可以先把所有操作离线下来。然后从前到后，对每个位置，找能让结果变优的操作，进行匹配。

分为三类：

- $s_i=a$，已经是最优了，不用管；

- $s_i=b$，有两种途径变优：$b\rightarrow a$ 和 $b\rightarrow c\rightarrow a$。先看有没有操作能直接让 $b\rightarrow a$，如果没有，再找第一个 $b\rightarrow c$ 和**它后面的** $c\rightarrow a$，这两个一定要都存在，否则仅仅 $b\rightarrow c$ 会让结果变劣。

- $s_i=c$，同样有两种途径：$c\rightarrow a$ 和 $c\rightarrow b\rightarrow a$，和 $s_i=b$ 不同的是，可以先选 $c\rightarrow b$，然后再看有没有 $b\rightarrow a$，都是优的。

为了实现，以 $x$ 与 $y$ 为维度，存操作的顺序，“某时刻后”这种情形，可以二分解决。

复杂度 $O((n+q)\log q)$。代码参考了官方题解。

```cpp
void solve() {
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    vector f(3, vector<set<int>>(3)); // 把所有操作离线
    for (int i = 0; i < q; i++) {
        char x, y;
        cin >> x >> y;
        f[x - 'a'][y - 'a'].insert(i);
    }

    auto popFront = [](set<int> &s) {
        s.erase(s.begin());
    };

    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') {
            continue;
        }
        if (s[i] == 'b') {
            if (not f[1][0].empty()) { // 先看 b 能不能直接变成 a
                popFront(f[1][0]);
                s[i] = 'a';

            } else if (not f[1][2].empty()) { // 否则看有没有 b-c-a 的途径

                int p = *f[1][2].begin();
                auto it = f[2][0].lower_bound(p);
                if (it != f[2][0].end()) {
                    popFront(f[1][2]);
                    f[2][0].erase(it);
                    s[i] = 'a';
                }
            }

        } else {

            if (not f[2][0].empty()) { // 同理
                popFront(f[2][0]);
                s[i] = 'a';

            } else if (not f[2][1].empty()) {

                int p = *f[2][1].begin(); // 看能不能 c-b
                popFront(f[2][1]);
                s[i] = 'b';

                auto it = f[1][0].lower_bound(p); // 再看能不能 b-a
                if (it != f[1][0].end()) {
                    f[1][0].erase(it);
                    s[i] = 'a';
                }
            }
        }
    }
    cout << s << "\n";
}
```

---

## 作者：yyrwlj (赞：0)

注意到让一个位置变劣也不会让前面的某个位置变优，所以我们不用让 $a$ 再变成其它的。

注意到最小化字典序首先要最大化前缀 $a$ 的长度，所以我们考虑二分这个长度。

一个前缀能全变成 $a$ 即能把这个前缀里所有的 $b$ 和 $c$ 都变成 $a$，且直接方式只有 $b \to a$ 和 $c \to a$。

那么接下来要考虑的就是如何进行 $b$ 和 $c$ 之间的转化，显然我们要尽可能利用上 $b \to a$ 和 $c \to a$。所以遇到 $b \to c$ 时，当 $b$ 的个数超过了后面 $b \to a$ 的次数且 $c$ 的个数小于后面 $c \to a$ 的次数，执行操作一定优，反之同理。

找到了最长的前缀 $a$ 后，我们还要最小化后面的字典序，只需要分别记录没用上的 $b \to a$，$c \to a$，$c \to b$ 的个数，然后从前往后贪心使用即可。

此时也不用担心会有 $c \to b$ 再 $b \to a$ 的情况，因为如果同时剩了这两个操作，则必然能让前缀 $a$ 的长度更大。

```cpp
#include <bits/stdc++.h>
#define lowbit(o) o & -o
#define pb push_back
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int N = 500005;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const LL INF = 2e18;
char s[N];
pair<char, char> a[N];
int sb[N], sc[N], n, q;
bool check(int mid)
{
	int b = 0, c = 0;
	for (int i=1;i<=mid;i++)
		if (s[i] == 'b')
			b ++;
		else if (s[i] == 'c')
			c ++;
	for (int i=1;i<=q;i++)
	{
		if (a[i].x == 'a' || a[i].x == a[i].y)
			continue;
		if (a[i].y == 'a')
		{
			if (a[i].x == 'b' && b)
				b --;
			if (a[i].x == 'c' && c)
				c --;
		}
		else if (a[i].y == 'c')
		{
			if (c < sc[i] && b > sb[i])
				b --, c ++;
		}
		else
		{
			if (c > sc[i] && b < sb[i])
				c --, b ++;
		}
	}
	return !b && !c;
}
void work()
{
	cin >> n >> q >> (s + 1);
	for (int i=1;i<=q;i++)
		cin>>a[i].x>>a[i].y;
	sb[q + 1] = sc[q + 1] = 0;
	for (int i=q;i;i--)
	{
		sb[i] = sb[i + 1] + (a[i].x == 'b' && a[i].y == 'a');
		sc[i] = sc[i + 1] + (a[i].x == 'c' && a[i].y == 'a');
	}
	int l = 1, r = n, ans = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid))
			ans = mid, l = mid + 1;
		else
			r = mid - 1;
	}
	int b = 0, c = 0;
	for (int i=1;i<=ans;i++)
		if (s[i] == 'b')
			b ++;
		else if (s[i] == 'c')
			c ++;
	for (int i=1;i<=ans;i++)
		s[i] = 'a';
	int cnt = 0, cc = 0, cb = 0;
	for (int i=1;i<=q;i++)
	{
		if (a[i].x == 'a' || a[i].x == a[i].y)
			continue;
		if (a[i].y == 'a')
		{
			if (a[i].x == 'b' && b)
				b --;
			else if (a[i].x=='b')
				cb ++;
			if (a[i].x == 'c' && c)
				c --;
			else if (a[i].x=='c')
				cc ++;
		}
		else if (a[i].y == 'c') // b -> c
		{
			if (c < sc[i] && b > sb[i])
				b --, c ++;
		}
		else				// c -> b
		{
			if (c > sc[i] && b < sb[i])
				c --, b ++;
			else
				cnt ++;
		}
	}
	//cout<<ans<<' '<<cc<<' '<<cb<<' '<<cnt<<'\n';
	for (int i=ans+1;i<=n;i++)
		if (cc && s[i] == 'c')
			s[i] = 'a', cc --;
		else if (cb && s[i]=='b')
			s[i] = 'a', cb --;
		else if (cnt && s[i]=='c')
			s[i]='b',cnt--;
	cout<<(s+1)<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int _T = 1;
    cin >> _T;
    while (_T--)
        work();
    return 0;
}
```

---

## 作者：Toorean (赞：0)

一个十分丑陋的赛时做法。

给出一个仅由 $\texttt {abc}$ 组成长度为 $n$ 的字符串 $s$，$Q$ 次有顺序的操作，将其中任意一个字符 $x$ 转化为 $y$，可以不操作。求转化后最小字典序的串。

如果我们贪心地想：只要当前修改可以使得当前字符变得更小就修改。然而这显然是不对的，因为如若存在 $\texttt b\to \texttt c$ 以及 $\texttt c\to \texttt a$ 的情况，无法完成修改。

因此我们需要考虑每个字符是否可以修改成比其小的字符。

于是自然想到，依次枚举 $s$ 的字符 $s_i$，如若 $s_i$ 可以变化为比其字典序更小，那么就尽量转化。这种贪心思路是正确的。

具体来说，我们做出如下分类讨论：
1. 若 $s_i=\texttt a$，那么无需操作。
2. 若 $s_i=\texttt b$，我们判断是否存在操作 $\texttt b\to \texttt a$，存在即使用这个操作；不存在，则继续判断是否同时存在 $\texttt b\to \texttt c$ 以及 $\texttt c\to \texttt a$，同时，需要使 $\texttt c\to \texttt a$ 的时间戳**大于** $\texttt b\to \texttt c$。为了保证贪心的正确性，我们需要寻找**首个**满足这样条件的操作。
3. 若 $s_i=\texttt c$，我们同上地判断是否存在 $\texttt c\to \texttt a$ 的操作，接着继续判断是否通过 $\texttt b$ 转化为 $\texttt a$。值得注意的是，如若不存在 $\texttt b\to\texttt a$ 时间戳大于 $\texttt c\to\texttt b$，我们仍然执行操作 $\texttt c\to\texttt b$，因为 $\texttt b$ 的字典序小于 $\texttt c$。

综上，我们便完成了这一修改的操作，设 $n$ 与 $Q$ 同阶，时间复杂度 $\mathcal O(n\log n)$。

但是，该用什么样的数据结构来实现时间戳的维护？

我在这里采用的是 pbds 库中的平衡树。

另外，我们如何保证第二个分类讨论中两种变换方案都存在时的正确性？

我们优先判断是否存在 $\texttt b\to\texttt a$ 的操作，而后判断第二种变换的存在性。这样，我们保证了对后续 $\texttt c$ 修改的可行性，我们尽量更少进行操作。另外，我们访问 $s$ 中字符的顺序，其实与操作的时间戳并无关联，因此我们无需过多考虑其他干扰因素。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>  
#include <ext/pb_ds/tree_policy.hpp>
 
#define rep(i,a,b) for (int i = (a); i <= (b); i ++)
#define per(i,a,b) for (int i = (a); i >= (b); i --)
#define ll long long
#define i128 __int128
#define MST(X,A) memset (X, (A), sizeof X)
 
using namespace std;
using namespace __gnu_pbds;
 
const int MAXN = 2e5 + 10;
 
struct quest {
    char f[20], t[20];
};
 
int n, q;
char str[MAXN];
tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update> trans[3][3];
quest a[MAXN];
 
void init () {
    for (int i = 0; i <= 2; i ++)
        for (int j = 0; j <= 2; j ++)
            trans[i][j].clear ();
}
 
void work () {
    init ();
 
    scanf ("%d%d\n", &n, &q);
    scanf ("%s", str + 1);
    for (int i = 1; i <= q; i ++) {
        scanf ("%s%s", a[i].f + 1, a[i].t + 1);
        trans[ a[i].f[1] - 'a' ][ a[i].t[1] - 'a' ].insert (i);
    }
 
    for (int i = 1; i <= n; i ++) {
        if (str[i] == 'b') { // 到 a
            if (trans[1][0].size ()) trans[1][0].erase (trans[1][0].begin ()), str[i] = 'a';
            else if (trans[1][2].size () && trans[2][0].size ()) {
                int tim1 = *trans[1][2].begin ();
                auto x = trans[2][0].lower_bound (tim1);
                if (x == trans[2][0].end ()) continue;
                trans[1][2].erase (trans[1][2].begin ());
                trans[2][0].erase (x);
                str[i] = 'a';
            }
        } else if (str[i] == 'c') {
            if (trans[2][0].size ()) str[i] = 'a', trans[2][0].erase (trans[2][0].begin ());
            else if (trans[2][1].size ()) {
                int tim1 = *trans[2][1].begin ();
                str[i] = 'b'; trans[2][1].erase (trans[2][1].begin ());
                auto x = trans[1][0].lower_bound (tim1);
                if (x == trans[1][0].end ()) continue;
                trans[1][0].erase (x);
                str[i] = 'a';
            }
        }
    }  
 
    printf ("%s\n", str + 1);
}
 
signed main (void) {
 
    signed t;
    scanf ("%d", &t);
    while (t--)
        work ();
 
    return 0;
}
```

---

