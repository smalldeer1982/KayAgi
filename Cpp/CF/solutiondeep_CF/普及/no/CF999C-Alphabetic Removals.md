# 题目信息

# Alphabetic Removals

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters. Polycarp wants to remove exactly $ k $ characters ( $ k \le n $ ) from the string $ s $ . Polycarp uses the following algorithm $ k $ times:

- if there is at least one letter 'a', remove the leftmost occurrence and stop the algorithm, otherwise go to next item;
- if there is at least one letter 'b', remove the leftmost occurrence and stop the algorithm, otherwise go to next item;
- ...
- remove the leftmost occurrence of the letter 'z' and stop the algorithm.

This algorithm removes a single letter from the string. Polycarp performs this algorithm exactly $ k $ times, thus removing exactly $ k $ characters.

Help Polycarp find the resulting string.

## 样例 #1

### 输入

```
15 3
cccaabababaccbc
```

### 输出

```
cccbbabaccbc
```

## 样例 #2

### 输入

```
15 9
cccaabababaccbc
```

### 输出

```
cccccc
```

## 样例 #3

### 输入

```
1 1
u
```

### 输出

```
```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。Polycarp 想要从字符串 $s$ 中删除恰好 $k$ 个字符（$k \le n$）。Polycarp 使用以下算法执行 $k$ 次操作：

- 如果字符串中至少有一个字母 'a'，则删除最左边的 'a' 并停止算法，否则继续下一步；
- 如果字符串中至少有一个字母 'b'，则删除最左边的 'b' 并停止算法，否则继续下一步；
- ...
- 删除最左边的字母 'z' 并停止算法。

该算法每次删除一个字符。Polycarp 执行该算法恰好 $k$ 次，因此删除恰好 $k$ 个字符。

帮助 Polycarp 找到操作后的字符串。

#### 样例 #1

##### 输入

```
15 3
cccaabababaccbc
```

##### 输出

```
cccbbabaccbc
```

#### 样例 #2

##### 输入

```
15 9
cccaabababaccbc
```

##### 输出

```
cccccc
```

#### 样例 #3

##### 输入

```
1 1
u
```

##### 输出

```
```

### 算法分类
模拟

### 题解分析与结论

本题的核心是模拟删除字符的过程，按照字母顺序从 'a' 到 'z' 依次删除最左边的字符，直到删除 $k$ 个字符为止。题解中主要有以下几种思路：

1. **直接模拟删除过程**：通过遍历字符串，按照字母顺序删除字符，直到删除 $k$ 个字符。这种方法简单直观，但时间复杂度较高，适合小规模数据。
2. **使用桶统计字符数量**：通过统计每个字符的数量，按字母顺序删除字符，直到删除 $k$ 个字符。这种方法优化了删除过程，减少了不必要的遍历。
3. **使用链表或链式前向星**：通过链表结构记录字符的位置，快速找到并删除字符。这种方法进一步优化了删除过程，适合大规模数据。

### 所选高分题解

#### 题解1：作者：Eason_AC (赞：4)

**星级：4星**

**关键亮点**：直接模拟删除过程，代码简洁易懂，适合初学者理解。

**核心代码**：
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;

string s;
int n, k, vis[400007];
char cur = 'a';

int main() {
	scanf("%d%d", &n, &k);
	cin >> s;
	while(1) {
		int flag = 1;
		for(int i = 0; i < n; ++i)
			if(s[i] == cur) {
				vis[i] = 1;
				k--;
				if(!k) {flag = 0; break;}
			}
		if(!flag) break;
		cur++;
	}
	for(int i = 0; i < n; ++i)
		if(!vis[i]) printf("%c", s[i]);
	return 0;
}
```

#### 题解2：作者：良知 (赞：4)

**星级：4星**

**关键亮点**：使用桶统计字符数量，优化了删除过程，代码结构清晰。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<char , int> mp,mp1;
char str[400005];
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	
	for(int i=1;i<=n;++i){
		mp[str[i]]++;
	}
	for(char c='a';c<='z';c++){
		if(mp[c]>m){
			mp1[c]=m;break;
		}
		else{
			mp1[c]=mp[c];
			m-=mp1[c];
		}
	}
	
	for(int i=1;i<=n;i++){
		if(mp1[str[i]]==0)printf("%c",str[i]);
		else mp1[str[i]]--;
	}
	printf("\n");
	return 0;
}
```

#### 题解3：作者：Jsxts_ (赞：0)

**星级：4星**

**关键亮点**：使用链表结构优化删除过程，适合大规模数据，代码效率高。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[400005];
int Next[400005];
int head[200];
int main() {
    int i,n,m;
    scanf("%d%d%s",&n,&m,s+1);
    for(i=n;i>=1;i--){
        Next[i]=head[s[i]];
        head[s[i]]=i;
    }
    int j;
    while(m) {
        for(i=97;i<=122;i++) {
            for(j=head[i];j;j=Next[j]) {
                s[j]='A';
                m--;
                if(m==0)break;
            }
            if(m==0)break;
        }
        if(m==0)break;
    }
    for(i=1;i<=n;i++)
        if(s[i]!='A')
            printf("%c",s[i]);
    return 0;
}
```

### 最优关键思路与技巧

1. **直接模拟删除过程**：适合小规模数据，代码简单易懂。
2. **使用桶统计字符数量**：优化了删除过程，减少了不必要的遍历，适合中等规模数据。
3. **使用链表或链式前向星**：进一步优化了删除过程，适合大规模数据，效率高。

### 可拓展之处

本题的删除过程可以拓展到其他类似的模拟问题，如按照特定规则删除数组中的元素。类似的算法套路可以应用于字符串处理、数组操作等问题。

### 推荐题目

1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

---
处理用时：38.71秒