# [ABC098B] Cut and Count

## 题目描述

给定一个长度为 $N$ 的字符串 $S$。我们可以在任意一个位置将字符串分割，使它变成两个字符串 $X$ 和 $Y$。现在要求出可能的 $X$ 和 $Y$ 都包含的字符种数的最大值。

## 说明/提示

- $2\ \le N\ \le 100$
- $|S|\ =\ N$
- $S$ 里的字符均为小写字符。

### 数据解释 1

在 $S$ 的第 $3$ 个字符后切割字符串，此时 $X\ =\ \texttt{aab}$，$Y\ =\ \texttt{bca}$。 它们共同包含的字符有 $\texttt{a}$ 和 $\texttt{b}$ 两种。所以答案为 $2$。

### 数据解释 2

显然，无论怎么切割字符串， $X$ 和 $Y$ 都包含的字符只可能为 $\texttt{a}$。所以答案为 $1$。

## 样例 #1

### 输入

```
6
aabbca```

### 输出

```
2```

## 样例 #2

### 输入

```
10
aaaaaaaaaa```

### 输出

```
1```

## 样例 #3

### 输入

```
45
tgxgdqkyjzhyputjjtllptdfxocrylqfqjynmfbfucbir```

### 输出

```
9```

# 题解

## 作者：Black_Porridge (赞：2)

这道题又木有翻译orz

## 题意与分析
给你一个长度为$N$的字符串$S$，由小写字母组成。请你将字符串分成两半，问你这两个字符串共有的字母的最多个数（字母不重复）。

看完题目再看看数据范围，很明显直接模拟就可以了。先找切割点，然后逐个枚举前后两个字符串，标记含有的字母，最后统计相同的字母即可。

## $Code$

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n, ans;
string s;
bool flag[50][2];//这个数组是去重的作用

int main()
{
	cin >> n >> s;//输入
	for(int i = 0; i < n; i++)//找切割点
	{
		memset(flag, false, sizeof(flag));//先赋初值
		int cnt = 0;
		for(int j = 0; j <= i; j++)
		{
			flag[s[j] - 'a'][0] = true;//代表前一个字符串中有这个字母	
	    }
		for(int j = i + 1; j < n; j++)
		{
			flag[s[j] - 'a'][1] = true;	//代表后一个字符串中有这个字母	
		}
		for(int j = 0; j < 26; j++)//从表示a的到表示z的
		{
			if(flag[j][0] and flag[j][1])//如果说有一样的cnt就加
				cnt++;
		}
		 ans = max(ans, cnt);//ans取最大值
	}
	cout << ans << endl;
	完结撒花~
}



---

## 作者：EuphoricStar (赞：1)

## 题意

一个字符串 $S$，将它分割成两个字符串 $x$ 和 $y$，求 $x$ 和 $y$ 中最大的共有的不同字母个数。

## 思路

直接模拟分割即可，分割后使用两个 `set` 存储 $x$ 和 $y$ 中的字母，统计一下它们有多少共有的元素，最后取最大值即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans;
string s;

int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> s;
    for (int i = 1; i < s.size() - 1; ++i)
    {
        int cnt = 0; // x 和 y 共有的字母个数
        string x = s.substr(0, i), y = s.substr(i);
        set<char> a, b;
        // 将 x 和 y 中的每一个字符插入 set
        for (char c : x) a.insert(c);
        for (char c : y) b.insert(c);
        // 统计一下 a 和 b 中共有的元素个数
        // b.count(c) 求 b 中元素 c 在集合中的出现次数
        for (char c : a) cnt += b.count(c);
        // 取最大值
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
```


---

