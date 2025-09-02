# ヘイホー君と置き換え

## 题目描述

**题意描述：**\
给定$1$个字符串$str$，要改动其中多少字符才可以使这个字符串重复呢？\
例子：
- 将第二个字符替换为 $a$，得 $aaacbabc$。
- 将第三个字符替换为 b，得 $aabcbabc$。
- 将第 5 个字符替换为 a，得 $aabcaabc$。\
这样重复的子串为$aabc$，符合题意。

## 样例 #1

### 输入

```
8
abacbabc```

### 输出

```
3```

## 样例 #2

### 输入

```
8
abababab```

### 输出

```
0```

## 样例 #3

### 输入

```
5
abcde```

### 输出

```
-1```

## 样例 #4

### 输入

```
26
codefestivaltwozeroonefive```

### 输出

```
11```

# 题解

## 作者：Y_J_Y (赞：1)

日常翻译问题:首先这道题的意思是给你一个长度为n的字符串s,然后问你要改几个字符能使他变成重复的字符串

了解题意后,稍微思考一下就可以特判奇数了,因为重复的肯定是偶数
然后每一个i判断他的另一半是不是跟他一样(想一想,为什么,这个是关键一步)


```
//写这道水题是有原因的
//这回蒟蒻打比赛dfs一直卡住,打自闭了,希望水个题解宽宽心  
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;
int n;
int main() {
	cin>>n;
	string s;
	cin>>s;
	if((n&1)) {//位运算来判断是不是奇数,===(n%2==1)
		cout<<"-1"<<endl;
		return 0;
	}
	int ans=0;
	for(int i=0;i<n/2;i++) {//这是关键
		if(s[i]!=s[i+n/2]) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

