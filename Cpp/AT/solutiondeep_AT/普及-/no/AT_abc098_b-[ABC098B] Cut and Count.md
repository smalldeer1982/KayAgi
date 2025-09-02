# 题目信息

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

# AI分析结果

### 题目翻译
# [ABC098B] 切割与计数

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

### 算法分类
枚举

### 题解分析与结论
题目要求将字符串分割成两部分，并找出这两部分共有的字符种数的最大值。由于字符串长度较小（$N \le 100$），可以直接枚举所有可能的分割点，然后统计每对分割后字符串的共有字符种数。

### 所选题解
#### 1. 作者：Black_Porridge (赞：2)
- **星级**: 4
- **关键亮点**: 使用二维数组 `flag` 来记录前后字符串中的字符出现情况，避免了重复计算，代码简洁且高效。
- **核心代码**:
```cpp
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
}
```

#### 2. 作者：EuphoricStar (赞：1)
- **星级**: 4
- **关键亮点**: 使用 `set` 来存储前后字符串中的字符，利用 `set` 的去重特性，代码清晰易读。
- **核心代码**:
```cpp
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

### 最优关键思路或技巧
- **使用二维数组记录字符出现情况**: 通过二维数组 `flag` 来记录前后字符串中的字符出现情况，避免了重复计算，提高了效率。
- **使用 `set` 去重**: 利用 `set` 的去重特性，简化了共有字符的统计过程，代码更加清晰易读。

### 可拓展之处
- **类似题目**: 可以拓展到更复杂的字符串分割问题，例如分割成多个部分，或者要求分割后的字符串满足某些特定条件。
- **优化思路**: 对于更长的字符串，可以考虑使用位运算或其他更高效的数据结构来优化字符统计过程。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
3. [P3371 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P3371)

---
处理用时：32.32秒