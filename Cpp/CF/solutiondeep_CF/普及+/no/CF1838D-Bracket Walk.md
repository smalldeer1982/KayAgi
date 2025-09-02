# 题目信息

# Bracket Walk

## 题目描述

There is a string $ s $ of length $ n $ consisting of the characters '(' and ')'. You are walking on this string. You start by standing on top of the first character of $ s $ , and you want to make a sequence of moves such that you end on the $ n $ -th character. In one step, you can move one space to the left (if you are not standing on the first character), or one space to the right (if you are not standing on the last character). You may not stay in the same place, however you may visit any character, including the first and last character, any number of times.

At each point in time, you write down the character you are currently standing on. We say the string is walkable if there exists some sequence of moves that take you from the first character to the last character, such that the string you write down is a regular bracket sequence.

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()", "(())" are regular (the resulting expressions are: "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1838D/258127971c1944c307e76094dff5383eb1dfb8b7.png)One possible valid walk on $ s=\mathtt{(())()))} $ . The red dot indicates your current position, and the red string indicates the string you have written down. Note that the red string is a regular bracket sequence at the end of the process.You are given $ q $ queries. Each query flips the value of a character from '(' to ')' or vice versa. After each query, determine whether the string is walkable.

Queries are cumulative, so the effects of each query carry on to future queries.

## 说明/提示

In the first example:

- After the first query, the string is (())()()(). This string is a regular bracket sequence, so it is walkable by simply moving to the right.
- After the second query, the string is (())()))(). If you move right once, then left once, then walk right until you hit the end of the string, you produce the string (((())()))(), which is a regular bracket sequence.
- After the third query, the string is ()))()))(). We can show that this string is not walkable.

 In the second example, the strings after the queries are ()) and ()(, neither of which are walkable.

## 样例 #1

### 输入

```
10 9
(())()()))
9
7
2
6
3
6
7
4
8```

### 输出

```
YES
YES
NO
NO
YES
NO
YES
NO
NO```

## 样例 #2

### 输入

```
3 2
(()
2
3```

### 输出

```
NO
NO```

# AI分析结果

### 题目内容重写

#### 题目描述

有一个长度为 $n$ 的字符串 $s$，由字符 '(' 和 ')' 组成。你在这个字符串上行走。你从第一个字符开始，目标是走到第 $n$ 个字符。在每一步中，你可以向左移动一步（如果你不在第一个字符上），或者向右移动一步（如果你不在最后一个字符上）。你不能停留在原地，但你可以多次访问任何字符，包括第一个和最后一个字符。

在每个时间点，你记录下你当前所在的字符。如果存在一种移动序列，使得你从第一个字符走到最后一个字符，并且记录下的字符串是一个合法的括号序列，那么我们称这个字符串是“可行走的”。

一个合法的括号序列是指可以通过插入字符 '1' 和 '+' 将其转换为一个合法的算术表达式的括号序列。例如，括号序列 "()()" 和 "(())" 是合法的（转换后的表达式分别为 "(1)+(1)" 和 "((1+1)+1)"），而 ")(" 和 "(" 不是。

你被给定 $q$ 个查询。每个查询会翻转一个字符，将 '(' 变为 ')' 或反之。在每个查询之后，判断字符串是否是“可行走的”。

查询是累积的，因此每个查询的效果会延续到后续的查询中。

#### 说明/提示

在第一个例子中：

- 在第一个查询之后，字符串变为 (())()()()。这个字符串是一个合法的括号序列，因此它可以通过简单地向右移动来实现“可行走”。
- 在第二个查询之后，字符串变为 (())()))()。如果你先向右移动一次，然后向左移动一次，接着一直向右移动直到字符串的末尾，你会生成字符串 (((())()))()，这是一个合法的括号序列。
- 在第三个查询之后，字符串变为 ()))()))()。我们可以证明这个字符串不是“可行走的”。

在第二个例子中，查询后的字符串分别为 ()) 和 ()(，它们都不是“可行走的”。

#### 样例 #1

##### 输入

```
10 9
(())()()))
9
7
2
6
3
6
7
4
8
```

##### 输出

```
YES
YES
NO
NO
YES
NO
YES
NO
NO
```

#### 样例 #2

##### 输入

```
3 2
(()
2
3
```

##### 输出

```
NO
NO
```

### 算法分类
字符串

### 题解分析与结论

这道题的核心在于判断一个括号序列是否可以通过某种行走方式生成一个合法的括号序列。题解主要集中在如何通过维护连续括号的位置来判断字符串是否“可行走”。大多数题解都使用了 `set` 来维护连续括号的位置，并通过一些条件判断来确定字符串是否合法。

### 所选高分题解

#### 题解1：作者：TLEWA (赞：8)

**星级：5星**

**关键亮点：**
- 通过维护两个 `set` 分别记录连续左括号和连续右括号的位置，简化了判断逻辑。
- 通过判断连续括号的位置关系，快速确定字符串是否合法。
- 代码简洁且高效，逻辑清晰。

**核心代码：**
```cpp
set<int> L,R;

int main() {
	cin >> n >> q >> s;
	s=' '+s;
	for(int i=1;i!=n;++i) {
		if(s[i+1]==s[i]) {
			if(s[i]=='(') L.insert(i);
			else R.insert(i);
		}
	}
	
	while(q--) {
		cin >> p;
		if(n%2) {cout << "NO" << endl;continue;}
		if(p!=1 && s[p]==s[p-1]) {
			if(s[p]=='(') L.erase(p-1);
			else R.erase(p-1); 
		}
		if(p!=n && s[p]==s[p+1]) {
			if(s[p]=='(') L.erase(p);
			else R.erase(p); 
		}
		if(s[p]=='(') s[p]=')';
		else s[p]='(';
		if(p!=1 && s[p]==s[p-1]) {
			if(s[p]=='(') L.insert(p-1);
			else R.insert(p-1);
		}
		if(p!=n && s[p]==s[p+1]) {
			if(s[p]=='(') L.insert(p);
			else R.insert(p); 
		}
		if(s[1]==')' || s[n]=='(') cout << "NO" << endl;
		else if(L.empty() && R.empty()) cout << "YES" << endl;
		else if(L.empty() || R.empty()) cout << "NO" << endl;
		else if( (*L.begin()<*R.begin()) && (*L.rbegin()<*R.rbegin()) ){
			cout << "YES" << endl;
		}else cout << "NO" << endl;
	}
	return 0;
}
```

#### 题解2：作者：World_Creater (赞：6)

**星级：4星**

**关键亮点：**
- 通过维护四个 `set` 分别记录左括号、右括号、连续左括号和连续右括号的位置，进一步细化了判断条件。
- 通过判断连续括号的位置关系，快速确定字符串是否合法。
- 代码逻辑清晰，但相比题解1稍显复杂。

**核心代码：**
```cpp
set<int> s1,s2,s3,s4;

int main() {
	cin >> n >> q >> s+1;
	for(int i=1;i<=n;i++) {
		if(s[i]=='(') {
			s1.insert(i);
			if(i!=1&&s[i-1]=='(') s3.insert(i);
		}
		if(s[i]==')') {
			s2.insert(i);
			if(i!=1&&s[i-1]==')') s4.insert(i);
		}
	}
	while(q--) {
		int x;
		cin >> x;
		if(n&1) {
			cout << "NO\n";
			continue ;
		}
		if(s[x]=='(') {
			auto it=s1.upper_bound(x);
			s3.erase(x);
			if(it!=s1.end()&&*it-x==1) s3.erase(*it);
			s1.erase(x);
			it=s2.upper_bound(x);
			if(it!=s2.end()&&*it-x==1) s4.insert(*it);
			if(it!=s2.begin()) {
				it--;
				if(x-*it==1) s4.insert(x);
			}
			s2.insert(x);
			s[x]=')';
		}
		else {
			auto it=s2.upper_bound(x);
			s4.erase(x);
			if(it!=s2.end()&&*it-x==1) s4.erase(*it);
			s2.erase(x);
			it=s1.upper_bound(x);
			if(it!=s1.end()&&*it-x==1) s3.insert(*it);
			if(it!=s1.begin()) {
				it--;
				if(x-*it==1) s3.insert(x);
			}
			s1.insert(x);
			s[x]='(';
		}
		if(s[1]==')' || s[n]=='(') cout << "NO\n";
		else if(s3.empty() && s4.empty()) cout << "YES\n";
		else if(s3.empty() || s4.empty()) cout << "NO\n";
		else {
			int x=*s3.begin(),y=*s4.begin(),u=*s3.rbegin(),v=*s4.rbegin();
			cout << (x<y&&u<v?"YES\n":"NO\n");
		}
	}
}
```

### 最优关键思路与技巧

1. **维护连续括号的位置**：通过 `set` 维护连续括号的位置，可以快速判断字符串是否合法。
2. **条件判断**：通过判断连续括号的位置关系（如第一个连续左括号是否在第一个连续右括号之前），可以快速确定字符串是否“可行走”。
3. **动态更新**：在每次查询后，动态更新 `set` 中的内容，确保判断条件的准确性。

### 可拓展之处

1. **类似问题**：可以扩展到其他类型的括号序列问题，如判断括号序列是否合法、计算合法括号序列的数量等。
2. **数据结构优化**：可以使用其他数据结构（如线段树）来进一步优化查询和更新的效率。

### 推荐题目

1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
3. [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)

---
处理用时：68.88秒