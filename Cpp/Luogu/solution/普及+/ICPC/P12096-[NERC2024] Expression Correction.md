# [NERC2024] Expression Correction

## 题目描述

Eve 正在学校学习数学。他们已经学会了如何进行十进制数字的加法和减法，并通过解决有趣的难题进行练习。他们正在解决的难题的具体描述如下：给定一个包含加法和减法的等式，可能是正确的，也可能是错误的。他们需要验证这个等式，如果它不是正确的，那么他们需要判断是否可以通过将一个数字移动到等式的不同位置，使其成为正确的等式。

让我们正式定义这个难题中的等式：

- **数字** 是一个包含 **至少一个，至多十个十进制数字**（$0$ 到 $9$）的字符串，且没有额外的前导零（唯一允许以零开头的数字是 $\texttt{0}$）。
- **表达式** 是由一个或多个数字组成的字符串，这些数字通过加法（$\texttt{+}$）或减法（$\texttt{-}$）操作符连接。
- **等式** 是一个由表达式（如上所述）组成的字符串，后面跟一个等号（$\texttt{=}$），然后是另一个表达式。
- **正确的等式** 是一个等式，其中等号两边的表达式根据标准的算术运算计算后得到相同的十进制数。请注意，尽管表达式中的所有数字都是正数，但计算结果可以为负数。此外，计算结果可以超过 10 位数字。
- **移动数字** 在一个等式中意味着从字符串的任何位置删除一个数字并将其插入到另一个位置，从而使得结果字符串仍然是一个等式。

这个难题相当简单，一旦你知道如何进行十进制数字的加法和减法，但是它也很容易出错。在进行计算时很容易分心并犯错误。你的任务是编写一个程序，帮助 Eve 解决表达式纠错难题。

## 样例 #1

### 输入

```
2+2=4```

### 输出

```
Correct```

## 样例 #2

### 输入

```
123456789+9876543210=111111110+11-1```

### 输出

```
123456789+987654321=1111111100+11-1```

## 样例 #3

### 输入

```
10+9=10```

### 输出

```
Impossible```

## 样例 #4

### 输入

```
24=55-13```

### 输出

```
42=55-13```

## 样例 #5

### 输入

```
1000000000-10=9999999999```

### 输出

```
Impossible
```

# 题解

## 作者：luuia (赞：0)

### Solution

模拟题，按照题意模拟即可。具体模拟一下表达式的计算和单个字符的转移就行了，$O(n^3)$、$O(n^4)$ 都能过。

要注意一些 corner case，例如单个 $0$ 是合法的，首位为 $0$ 是不合法的。


### Code

```cpp
/**
 *    author: luuia
 *    created: 2025.04.10 14:59:02
 **/
#include <bits/stdc++.h>
using ll = long long;
#define For(i, j, k) for (int i = j; i <= k; i++)
#define Rep(i, j, k) for (int i = j; i >= k; i--)
#define pb push_back
using namespace std;
const int N = 1e6 + 10;
string s, t;
ll n;
ll tu(string s)
{
    ll o = 0, f = 1;
    if (s[0] == '-')
        f = -1;
    for (auto ch : s)
        if (ch != '-')
            o = o * 10 + ch - 48;
    return o * f;
}
bool ck(string s)
{
    if ((s[0] != '-' && s.size() > 10) || (s[0] == '-' && s.size() > 11))
        return 1;
    if (s != "0" && ((s[0] == '-' && s[1] == '0') || s[0] == '0'))
        return 1;
    return 0;
}
bool chk(string s)
{
    string t;
    vector<string> vec;
    bool f = 1;
    For(i, 1, s.size() - 1) if (!isdigit(s[i]) && !isdigit(s[i - 1])) return 0;
    for (auto ch : s)
    {
        if (ch == '=')
            vec.pb(f ? t : "-" + t), t = "", vec.pb("###"), f = 1;
        else if (ch == '+')
            vec.pb(f ? t : "-" + t), t = "", f = 1;
        else if (ch == '-')
            vec.pb(f ? t : "-" + t), t = "", f = 0;
        else
            t += ch;
    }
    if (t != "")
        vec.pb(f ? t : "-" + t);
    bool fl = 0;
    vector<string> ct1, ct2;
    for (auto x : vec)
    {
        if (ck(x) || x == "")
            return 0;
        if (x == "###")
        {
            fl = 1;
            continue;
        }
        (fl ? ct2 : ct1).pb(x);
    }
    if (!ct1.size() || !ct2.size() || !isdigit(s.back()) || !isdigit(s[0]))
        return 0;
    ll o1 = 0, o2 = 0;
    for (auto x : ct1)
        o1 += tu(x);
    for (auto x : ct2)
        o2 += tu(x);
    return o1 == o2;
}
void sol()
{
    cin >> s, n = s.length();
    if (chk(s))
    {
        cout << "Correct\n";
        return;
    }
    For(i, 0, n - 1)
    {
        if (!isdigit(s[i]))
            continue;
        For(j, 0, n)
        {
            string t, t1, t2;
            if (i == 0)
                t1 = "", t2 = s.substr(1, n - 1);
            else if (i == n - 1)
                t1 = s.substr(0, n - 1), t2 = "";
            else
                t1 = s.substr(0, i), t2 = s.substr(i + 1, n - i - 1);
            t = t1 + t2;
            if (j < n)
                t.insert(j, 1, s[i]);
            else
                t += s[i];
            if (chk(t))
            {
                cout << t << '\n';
                return;
            }
        }
    }
    cout << "Impossible\n";
}
int main()
{
    // freopen("input.in","r",stdin);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    ll T = 1;
    while (T--)
        sol();
    return 0;
}
```

---

## 作者：Ag2WO4 (赞：0)

看到题第一反应：串这么短，别说暴力 $O(n^2)$ 了，找个放 $O(n^3)$ 甚至常数小点的 $O(n^4)$ 来都能过啊，而且还是 Python 最经典的 ```eval()``` 环节，太简单啦！

实际一写：诶怎么这里 RE 了？！诶怎么这里又 WA 了！？

看数据汲取教训：
- 首先要套 ```try``` 和 ```except``` 防止报错；
- 其次考虑一些 ```eval()``` 函数不会报错的错误情况：
  1. 数长度超过十位；
  2. 数前单独的正负号；
  3. 前导零；
  4. 搬走了符号。

直接暴力置换，用正则表达式筛选避免 WA 即可。由于串很短，复杂度 $O(n^3)$（解释：被置换数的位置、插入位置和整串分析是三层 $O(n)$ 的操作）。注意特判无需置换的情况。
```python
a=input();l=len(a);d=0;import re
if eval(a.replace('=','==')):print('Correct');exit()
for i in range(l):
    if a[i]in'1234567890':
        b=a[:i]+a[i+1:]
        for j in range(l-1):
            try:
                c=b[:j]+a[i]+b[j:]
                if eval((c).replace('=','=='))and not re.search('[0-9]{11}|([-+=][-+=])|([-+=]0[0-9])|(^[-+])',c):print(b[:j]+a[i]+b[j:]);d=1
            except:0
            if d:exit()
print('Impossible')
```

---

## 作者：Redshift_Shine (赞：0)

作为一个懒惰的人，我们要学会使用 Python 偷懒。

前置知识：字符串切片，`eval` 函数。

知周所众，Python 的 `eval` 函数可以计算一个 Python 表达式的返回值。而它理所当然地可以用来判断一个等式是否正确。

然后，因为这道题 $n\le 100$，$O(n^3)$ 解法可行。

所以你就打了一份按照题目模拟的代码然后交上去 WA 了。

然后你发现 `+-` 会被认为是合法的。

然后又 WA 了。

然后你会发现前导 $0$ 非法但前导 $00$ 会被认为是合法的。

然后又 WA 了。

然后你会发现开头的单个 `-` 会被认为是合法的。

然后你终于 A 了。

建议 ICPC 时只有在特别熟悉 Python 特性并且确认计算时间合理后才选择 Python 解决问题，否则它缩短代码长度的优势不值一提。

```python
def check_10(s):
	t=0
	for i in s:
		if i<'0' or i>'9':
			t=0
			continue
		t+=1
		if(t>10):
			return False
	return True

def check_opr(s):
	n=len(s)
	for i in range(n-1):
		if s[i].isdigit() or s[i+1].isdigit() or (s[i]==s[i+1] and s[i]=='='):
			continue
		return False
	return True

def check_prev0(s):
	n=len(s)
	for i in range(n-2):
		if s[i].isdigit() or s[i+1]!=s[i+2] or s[i+1]!='0':
			continue
		return False
	return True

def check_full(s,ch):
	# print(s,ch)
	tn=len(s)
	ts=''
	for i in range(tn):
		ts=s[:i]+ch+s[i:]
		try:
			if not ts[0].isdigit() or not eval(ts) or not check_10(ts) or not check_opr(ts) or not check_prev0(ts):
				continue
			for i in range(tn+1):
				if ts[i]!='=':
					continue
				ts=ts[:i]+ts[i+1:]
				break
			print(ts)
			return True
		except SyntaxError:
			pass
	return False

stt=input()
n=len(stt)
for i in range(n):
	if stt[i]=='=':
		stt=stt[:i]+'='+stt[i:]
		break
n+=1
try:
	if stt[0].isdigit() and eval(stt) and check_10(stt) and check_opr(stt) and check_prev0(stt):
		print('Correct')
		exit(0)
except SyntaxError:
	pass
for i in range(n):
	if stt[i]<'0' or stt[i]>'9':
		continue
	if check_full(stt[:i]+stt[i+1:],stt[i]):
		exit(0)
print('Impossible')
```

---

