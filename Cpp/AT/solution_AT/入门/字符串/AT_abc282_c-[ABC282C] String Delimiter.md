# [ABC282C] String Delimiter

## 题目描述

给定一个由小写英文字母、`,` 和 `"` 组成的长度为 $N$ 的字符串 $S$。保证 $S$ 中出现的 `"` 的个数为偶数。

如果 $S$ 中的 `"` 出现了 $2K$ 次，则对于每个 $i=1,2,\ldots,K$，从第 $2i-1$ 个 `"` 到第 $2i$ 个 `"` 之间的所有字符，称为**被括起来的字符**。

你的任务是，将 $S$ 中所有**不属于被括起来的字符**的 `,` 替换为 `.`，并输出替换后的字符串。

## 说明/提示

### 限制条件

- $N$ 是 $1$ 到 $2\times 10^5$ 之间的整数。
- $S$ 是一个长度为 $N$ 的字符串，仅包含小写英文字母、`,` 和 `"`。
- $S$ 中出现的 `"` 的个数为偶数。

### 样例解释 1

在 $S$ 中，`"a,b"` 是被括起来的字符，而 `c,d` 不是被括起来的字符。$S$ 中不属于被括起来的字符的 `,` 是从左数第 $7$ 个字符，因此将第 $7$ 个字符替换为 `.` 后的字符串即为答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
"a,b"c,d```

### 输出

```
"a,b"c.d```

## 样例 #2

### 输入

```
5
,,,,,```

### 输出

```
.....```

## 样例 #3

### 输入

```
20
a,"t,"c,"o,"d,"e,"r,```

### 输出

```
a."t,"c."o,"d."e,"r.```

# 题解

## 作者：InversionShadow (赞：2)

## AT_abc282_c [ABC282C] String Delimiter 题解

这 ```C``` 题好水呀。

### 题意：

给定一个长度为 $n$ 的字符串 $s$，其中 $s$ 包含偶数个 `"`。

请你将 $s$ 中没有被两个 `"` 括起来的 `,` 转换成 `.`，并输出。

### 思路：

用 ```cnt``` 来记录之前有多少个 `"`，如果 $s_i$ 是 `"`，如果 ```cnt = 1```，表示之前出现过一个 `"`，那么我们就把 ```cnt--```，表示一个完整的区间已经结束，否则 ```cnt++```，表示一个新的区间已经开始。那如果 $s_i$ 不是 `"` 是 `,`，如果 ```cnt = 0```，表示当前不是区间，那我们就把 $s_i$ 修改成 ```.```。

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

string s;
int n;

int main() {
  cin >> n >> s;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '"') {
      if (cnt == 0) {
        cnt++;
      } else {
        cnt--;
      }
    } else {
      if (cnt == 0 && s[i] == ',') {
        s[i] = '.';
      }
    }
  }
  cout << s << endl;
  return 0;
}
```

---

## 作者：NightStriker (赞：1)

题意：



> 给你一个由英文字母，`"` 和  `,` 所组成的字符串 $s$，让你把引号内的 `,` 全部替换为 `.`。

对于这道题我们可以考虑先把引号内的部分用布尔型数组打上标记，然后再判断打上标记的部分是否是 `,`，如果是就替换成 `.` 就可以了。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int n;
string s;
bool f,a[200001];
int main() {
	cin>>n>>s;
	for(int i = 0;i<s.size();i++){
		if(s[i]=='"'&&f==0) f = 1;//如果是左引号
		else if(s[i]=='"'&&f==1) f = 0;//如果是右引号
		if(f==0){//如果当前的字符在引号内。
			a[i] = 1;
		}
	}
	for(int i = 0;i<s.size();i++){
		if(a[i]==1&&s[i]==',') s[i] = '.';//如果是 "," 而且还在引号内，就替换成"."。
	}
	for(int i = 0;i<s.size();i++){//输出处理完的字符串
		cout<<s[i];
	}
    cout<<endl;//赛时没加换行也过了（
	return 0;
}
```



---

## 作者：tbdsh (赞：0)

# 题意
[题目传送门](/problem/AT_abc282_c)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-abc282-c)

给定长为 $N$ 的包含小写英文字母、`,` 和 `"`（双引号）的字符串 $S$。保证 $S$ 有偶数个 `"` 字符。令 $2K$ 表示 $S$ 中 `"` 的数量，第 $2i - 1$ 个双引号和第 $2i$ 个双引号中的字符被称为是被包围的。请你将 $S$ 中没有被包围的 `,` 替换成 `.`，并输出。

# 分析
我们可以先扫一遍整个字符串，将每个 `"` 的位置记录下来。

如果记录的 `"` 是第偶数个，就从上个 `"` 位置到当前 `"` 位置进行标记。

同时，因为只要修改字符 `,`，所以对每个不是 `,` 的字符也应进行标记。

最后输出，判断该位置的字符是否被标记。如果没有被标记，就输出 `.`，否则输出 $S_i$。

时间复杂度：$O(|S|)$。
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
string s;
int a[MAXN], sum;
bool v[MAXN];
int main(){
  cin >> s >> s;
  int len = s.size();
  for (int i = 0; i < len; i++){
    if (s[i] == '\"'){//因为 " 属于特殊字符，所以需要添加转义字符 \ 来进行判断。
      a[++sum] = i;
      if (sum % 2 == 0){
        for (int j = a[sum - 1]; j <= i; j++){
          v[j] = 1;
        }
      }
    }
    v[i] = (s[i] != ',');
  }
  for (int i = 0; i < len; i++){
    if (!v[i]){
      cout << ".";
    }else {
      cout << s[i];
    }
  }
  return 0;
}
```

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/AT_abc282_c)

[atcoder](https://atcoder.jp/contests/abc282/tasks/abc282_c)

### 题目大意
给你一个长度为 $N$ 的，由小写英文字母、字符`,`、字符`"` 组成的字符串 $S$。保证 $S$ 包含偶数个字符 `"`。

设 $2K$ 为 $S$ 中字符 `"` 的数量。对于每个 $i=1,2,\dots,K$，在第 $(2i-1)$ 个字符 `"` 和第 $(2i)$ 个字符 `"` 之间的内容是封闭的。

你的任务是用字符 `.` 替换 $S$ 中每一个不是封闭内容的字符 `,`，并输出结果。

（注意单个字符与正文标点符号的区别）

### 思路
记录一个标志代表当前内容是否封闭，然后 $O(N)$ 模拟即可。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f;//f 是标志
char s[200010];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>s;
	for(int i=0;i<n;++i)
		if(s[i]=='\"')f^=1;
		else if(s[i]==','&&!f)s[i]='.';//直接替换
	cout<<s;
	return 0;
}
```

---

