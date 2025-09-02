# [ARC027B] 大事な数なのでZ回書きまLた。

## 题目描述

有一个长度为 $N$ 的数字串 $S$。它现在被2个混有大写字母的字符串替代。

你需要找到有多少个数字串 $S$ ，可以符合以下条件：

> - 不含前导零；
>
> - 在给出的2个字符串中，可以把每一个大写字母都分别替换成一种数字，相同的字母替换为相同的数字；
>
> - 替换完成后，两个字符串都和这个字符串 $S$ 相等。

## 样例 #1

### 输入

```
4
1XYX
1Z48```

### 输出

```
1```

## 样例 #2

### 输入

```
3
XXX
YYY```

### 输出

```
9```

## 样例 #3

### 输入

```
6
PRBLMB
ARC027```

### 输出

```
90```

# 题解

## 作者：TemplateClass (赞：1)

AT 的远古题目了，为啥没有人写题解啊。

并查集，在同一个集合表示要被映射到同一个数字，初始时 $s _ {1, i}$ 和 $s _ {2, i}$ 在同一个集合，显然如果集合里面有一个数字，那么集合里所有的元素都要被映射到这个数字，合并的时候注意把数字当父亲，这样可以直接 `getfa`。

最后用一个集合统计一下有多少个字母是“自由的”，也就是可以被映射到任意一个数字的，然后判断（记该集合的大小为 $|s|$）：

- 若该集合是空的，则所有的字母都会被映射到一个确定的值，此时答案为 $1$；
- 若该集合里有 $s _ {1, 0}$ 的父亲，说明需要判断前导零，此时答案就是 $9 \times 10 ^ {|s| - 1}$；
- 否则，集合里的所有元素都可被映射到 $0 \sim 9$ 中的任何一个数，此时答案就是 $10 ^ {|s|}$。

时间复杂度 $O(N \log N)$，可以发现这题答案最多是 $10 ^ N = 10 ^ {18}$，不用高精度。

```cpp
#include<iostream>
#include<cctype>
#include<climits>
#include<set>

typedef long long ll;
typedef unsigned long long ull;

int n; std::string s1, s2;
char father[CHAR_MAX];

char getfa(char x) {
	if(father[x] == x) return x;
	return father[x] = getfa(father[x]);
}

inline void merge(char a, char b) {
	char fa = getfa(a), fb = getfa(b);
	if(std::isdigit(fa)) father[fb] = fa;
	else father[fa] = fb;
}

ull fpow(int x, int y) {
	if(y == 0) return 1;
	ull ret = fpow(x, y >> 1);
	if(y & 1) ret *= ret * x;
	else ret *= ret;
	return ret;
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n >> s1 >> s2;
	for(int i = 0; i < n; ++i) {
		father[s1[i]] = s1[i], father[s2[i]] = s2[i];
	}
	for(int i = 0; i < n; ++i) {
		merge(s1[i], s2[i]);
	}
	
	std::set<char> s;
	for(const auto& i : s1 + s2) {
		if(!std::isalpha(i)) continue;
		if(!std::isdigit(getfa(i))) {
			s.insert(getfa(i));
		}
	}
	
	if(s.empty()) std::cout << "1" << "\n";
	else if(s.find(getfa(s1[0])) != s.end()) {
		std::cout << 9ull * fpow(10, s.size() - 1) << "\n";
	} else {
		std::cout << fpow(10, s.size()) << "\n";
	}
	
	return 0;
}
```

---

