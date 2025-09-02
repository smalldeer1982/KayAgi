# Yuhao and a Parenthesis

## 题目描述

One day, Yuhao came across a problem about checking if some bracket sequences are correct bracket sequences.

A bracket sequence is any non-empty sequence of opening and closing parentheses. A bracket sequence is called a correct bracket sequence if it's possible to obtain a correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, the sequences "(())()", "()" and "(()(()))" are correct, while the bracket sequences ")(", "(()" and "(()))(" are not correct.

Yuhao found this problem too simple for him so he decided to make the problem harder. You are given many (not necessarily correct) bracket sequences. The task is to connect some of them into ordered pairs so that each bracket sequence occurs in at most one pair and the concatenation of the bracket sequences in each pair is a correct bracket sequence. The goal is to create as many pairs as possible.

This problem unfortunately turned out to be too difficult for Yuhao. Can you help him and solve it?

## 说明/提示

In the first example, it's optimal to construct two pairs: "(( )())" and "( )".

## 样例 #1

### 输入

```
7
)())
)
((
((
(
)
)
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
(
((
(((
(())
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
(())
()
```

### 输出

```
1
```

# 题解

## 作者：Zechariah (赞：1)

这题思路其实很简单  
我们对输入进行括号匹配，并且消去匹配的括号  
这样一来，所有的输入就只有如下三种形式：  
((((((...  
))))))...  
))))...((((  
对于第三种形式，它无论和什么组对都不可能合法，因此这种我们直接不管他  
然后要记录的就是前两种，这里我用的方法是把'('看成1，')'看成-1，然后做前缀和s，s就可以表示有多少'('或者有多少')'，开一个桶记录就行  
显然如果要组对起来合法，左右括号应该一样多  
特别注意s==0的时候，这时候没有什么左右括号，我们用一个tot记录一下s==0的个数，答案中要加上tot/2
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
#define jh(x,y) (x^=y^=x^=y)
#define lowbit(x) (x&-x)
const int N = 1e6 + 10, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    int chread(rg char s[])
    {
        rg char ch;
        rg int len = 0;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        s[len++] = ch;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            s[len++] = ch;
        s[len] = 0;
        return len;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int a[N], tong[N], tong2[N];
char tt[N];

int main()
{
    rg int n = fast_IO::read(), tot = 0;
    for (rg int i = 1; i <= n; ++i)
    {
        rg string t; cin >> t;
        rg int len = 0, top = 0; tt[1] = 0;
        for (rg int j = 0; j != t.size(); ++j)
        {
            if (t[j] == '(')++top;
            else if (top)--top;
            else tt[++len] = ')';
        }
        while (top--)tt[++len] = '(';
        if (tt[1] == ')'&&tt[len] == '(')continue;
        for (rg int j = 1; j <= len; ++j)a[i] += tt[j] == '(' ? 1 : -1;
        a[i] += 500000;
        if (a[i] > 500000)++tong[a[i]]; else if (a[i] < 500000)++tong2[a[i]];
        else ++tot;
    }
    rg int l = 500000 - 1, r = 500000 + 1;
    rg ll ans = ((ll)tot >> 1);
    while (l >= 0)
    {
        ans += fast_IO::min(tong[r], tong2[l]);
        --l; ++r;
    }
    fast_IO::write(ans);
    return 0;
}

```

---

## 作者：TPJX (赞：0)

### 题目分析
这道题的核心思路在于通过计算每个序列的净余括号数量和序列的最低深度来决定其是否可以与其他序列配对形成合法序列。算法的实现通过使用两个哈希表来记录序列，一个记录开头的净余括号数量，另一个记录结尾的净余括号数量。我们遍历每个序列，计算其余括号数和最小深度，根据这些值将序列分类并记录。

首先，每个序列都计算两个关键值：净余括号数量和序列的最低深度（在遍历时的最小括号余额）。净余为正意味着多余的左括号，为负意味着多余的右括号。如果序列在遍历结束时括号数平衡（即净余为 $0$），并且最低深度非负，那么这个序列本身就是一个合法的括号序列。对于那些净余为正和非负最低深度的序列，我们记录其净余值在 $start$ 哈希表中；对于净余为负且其最低深度不小于其净余绝对值的序列，记录在 $end$ 哈希表中。

在分类完成后，首先计算自身就是合法括号序列的数量，这些序列可以单独成对。接着对于每一个净余为正的序列，尝试在 $end$ 哈希表中找到与之可以配对的序列（即净余相同但符号相反的序列）。通过取两者数量的最小值，就能得出最大的配对数量。

最后，输出所有可能的配对数量。

### C++ 代码
```cpp
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int main() {
    int n;
    cin >> n;
    string s;
    unordered_map<int, int> start, end;
    int vld = 0; 
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int bal = 0, min_bal = 0;
        for (char c : s) {
            if (c == '(') bal++;
            else bal--;
            min_bal = min(min_bal, bal);
        }
        if (bal == 0 && min_bal >= 0) vld++;
        else if (bal > 0 && min_bal >= 0) 
            start[bal]++;
        else if (bal < 0 && min_bal >= bal) 
            end[-bal]++;
    }
    int pairs = vld / 2;
    for (auto p : start) {
        int b = p.first, cnt = p.second;
        pairs += min(cnt, end[b]);
    }
    cout << pairs << endl;
    return 0;
}

```

---

## 作者：Lu_xZ (赞：0)

### [CF1097C Yuhao and a Parenthesis](https://codeforces.com/problemset/problem/1097/C)

stl 乱搞做法，感觉比正解更直接。

+ 每个字符串内部能匹配的尽可能匹配。
+ 匹配完成后，检验剩余序列是否只含有 `(` 或只含有 `)` 或为空，如果符合条件，插入待选序列。
+ 在待选序列中尽可能匹配。

### code

+ 用一个 `set<pair<string, int> >` 维护新字符串和位置两个信息。
+ 记录一个 `vis` 表示当前位置有没有用过。
+ 依次遍历每个新字符串 $s$，查询 $s$ 的翻转是否在 `set` 中存在。

> `((((` 是 `))))` 的翻转，不是 `)))` 或 `(` 的翻转。

具体实现可以利用 `pair` 的双关键字排序查询 `lower_bound(rev(s), -1)`。

```c++
#include<bits/stdc++.h>
using namespace std;

char stk[500000];
int tt;

bool check(string s) {
	int t = 0;
	for(char c : s) if(c == '(') ++ t;
	return (t == (int)s.size()) || t == 0;
}

string get_rev(string s) {
	string t = s;
	reverse(t.begin(), t.end());
	for(char &c : t) c == '(' ? (c = ')') : (c = '(');
	return t;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int n;
	cin >> n;
	vector<string> ss(n);
	set<pair<string, int> > se;
	vector<bool> vis(n, 0);
	for(int i = 0; i < n; ++ i) {
		cin >> ss[i];
		tt = -1;
		for(auto c : ss[i]) {
			if(~ tt && stk[tt] == '(' && c == ')') -- tt;
			else stk[++ tt] = c;
		}
		ss[i].clear();
		for(int j = 0; j <= tt; ++ j) ss[i] += stk[j];
		if(check(ss[i])) se.emplace(ss[i], i);
		else vis[i] = 1;
	}
	int ans = 0;
	for(int i = 0; i < n; ++ i) {
		if(vis[i]) continue;
		se.erase(se.find({ss[i], i}));
		vis[i] = 1;
		string t = get_rev(ss[i]);
		auto it = se.lower_bound({t, -1});
		if(it != se.end()) {
			auto [rev, j] = *it;
			if(rev == t) {
				vis[j] = 1;
				++ ans;
				se.erase({ss[j], j});
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```

---

