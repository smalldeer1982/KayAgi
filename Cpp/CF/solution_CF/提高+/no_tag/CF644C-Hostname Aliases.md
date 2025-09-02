# Hostname Aliases

## 题目描述

有一些网站可以通过不同的地址进行访问。比如，过去 Codeforces 可以通过两个网址 codeforces.com 和 codeforces.ru 访问。

现提供一个网页地址查询列表。为简化问题，我们假设所有地址的格式为 http://<hostname>\[/<path>\]，其中：

- <hostname> 是服务器名，由单词组成，可能存在用点隔开的情况；
- /<path> 是可选部分，其中 <path> 由斜杠隔开的单词组成。

如果针对第一个 <hostname> 的每个查询，在第二个 <hostname> 上也有完全相同的查询，并且反之亦然——对于第二个 <hostname> 的每个查询，在第一个 <hostname> 上同样存在，那么我们就认为这两个 <hostname> 对应于同一个网站。具体情况请参考示例。

你的任务是确定哪些服务器名称属于同一个网站，且忽略只包含一个服务器名称的情况。

需要特别注意，按照上面的定义，查询 http://<hostname> 与 http://<hostname>/ 被视为不同的查询。

## 样例 #1

### 输入

```
10
http://abacaba.ru/test
http://abacaba.ru/
http://abacaba.com
http://abacaba.com/test
http://abacaba.de/
http://abacaba.ru/test
http://abacaba.de/test
http://abacaba.com/
http://abacaba.com/t
http://abacaba.com/test
```

### 输出

```
1
http://abacaba.de http://abacaba.ru 
```

## 样例 #2

### 输入

```
14
http://c
http://ccc.bbbb/aba..b
http://cba.com
http://a.c/aba..b/a
http://abc/
http://a.c/
http://ccc.bbbb
http://ab.ac.bc.aa/
http://a.a.a/
http://ccc.bbbb/
http://cba.com/
http://cba.com/aba..b
http://a.a.a/aba..b/a
http://abc/aba..b/a
```

### 输出

```
2
http://cba.com http://ccc.bbbb 
http://a.a.a http://a.c http://abc 
```

# 题解

## 作者：wizardMarshall (赞：1)

## 题意

给定若干个网站，分为主机名与路径。如果两台主机查询的路径都相同，它们就属于一个集合。求出所有集合。

网站给出的是如下格式：

```
http://主机名/路径
```

注意题目强调主机名后可能不会有斜杠，这也算一种查询。

## 思路

首先肯定先想到把一个主机的所有路径记录下来然后去重（重复没有意义还会干扰判断）。之后通过 map 等数据结构找哪几个机子是相等的。可以用字符串哈希来做。

这里使用单哈希会爆，双哈希也会爆，字符串之间加了间隔等也会爆。只是数据点多少的问题。我们可以用 std 库中自带的哈希函数。

具体格式：

```
hash<数据结构名>()(需要哈希的变量)
```

最后判断哈希值相同的是否多于一个即可输出。

## 代码

```c++
#include <bits/stdc++.h>
 
using namespace std;
#define int long long
const int p = 998244353;
map <string, bool> is;//去重
map <string, vector <string> > mp;//每个主机后路径的集合
map <int, vector <string> > hsh;//同一个哈希值的主串集合
signed main() {
	ios::sync_with_stdio();
	cin.tie(0);cout.tie(0);
	int n;
	cin >>n;
	while (n--) {
		string s;
		cin >> s;
		
		if (is[s])continue;
		is[s] = 1;
		int len = s.size(), i;
		string name1 = "", name2 = "";
		for (i = 7; i < len; i++) {
			if (s[i] == '/')break;
			name1 += s[i];
		}
		for (; i < len; i++) {
			name2 += s[i];
		}
		mp[name1].push_back(name2);//name1是主机名，name2是路径
	}
	for (auto i : mp) {
		sort(i.second.begin(), i.second.end());
		string sum = "";
		for (auto j : i.second) {
			sum += j + '-';//字符串之间最好用-隔开，不然会出现诸如a-bc=ab-c的错误
		}
		hsh[hash<string>()(sum)].push_back(i.first);//哈希映照
	}
	int cnt = 0;
	for (auto i : hsh) {
		if (i.second.size() > 1) {//统计相同的个数
			cnt++;
		}
	}
	cout << cnt << endl;
	for (auto i : hsh) {
		if (i.second.size() <= 1)continue;
		for (auto j : i.second) {
			cout << "http://" << j << " ";//记录的时候不带http就要加上
		}cout << endl;
	}
	return 0;
}

```

---

