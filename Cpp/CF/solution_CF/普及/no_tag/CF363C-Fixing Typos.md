# Fixing Typos

## 题目描述

Many modern text editors automatically check the spelling of the user's text. Some editors even suggest how to correct typos.

In this problem your task to implement a small functionality to correct two types of typos in a word. We will assume that three identical letters together is a typo (for example, word "helllo" contains a typo). Besides, a couple of identical letters immediately followed by another couple of identical letters is a typo too (for example, words "helloo" and "wwaatt" contain typos).

Write a code that deletes the minimum number of letters from a word, correcting described typos in the word. You are allowed to delete letters from both ends and from the middle of the word.

## 说明/提示

The second valid answer to the test from the statement is "heloo".

## 样例 #1

### 输入

```
helloo
```

### 输出

```
hello
```

## 样例 #2

### 输入

```
woooooow
```

### 输出

```
woow
```

# 题解

## 作者：InfiniteRobin (赞：1)

## 题目大意

给出一个字符串 $s$，删除 $s$ 中尽可能少的字母，使得 $s$ 中既没有 $3$ 个相连的相同字母，也不存在一对相同的字母后面紧跟着另一对相同的字母的情况。  
输出修改后的 $s$。

---

## 分析

先看第一个要求，若是有三个连在一起的相同字母，为了使删除字母的个数最小，我们肯定选择删除中间的那个字母。

再看第二个要求，若 $s_{i}=s_{i-1}$ 且 $s_{i+1}=s_{i+2}$，那我们就应该删去 $s_{i+1}$。  

但是，需要注意的是，我们在进行一次删除操作后，下一次依然要对当前位再进行一次判断，以避免类似 $\texttt{aabbb}$ 的情况。

删除字符的操作使用 ```s.erase()```。

---

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	string s;
	cin>>s;
	
	for(int i=1;i<s.length()-1;i++){ //防止超界
		if(s[i]==s[i-1]){
			if(s[i]==s[i+1]){  //如果是情况一
				s.erase(i,1); //删除中间的字符
				i--; //相当于下一次循环还是当前位置
			}
			else if(i<s.length()-2&&s[i+1]==s[i+2]){ //情况二
				s.erase(i+1,1);
				i--;
			}
		}
	}
	cout<<s; //完结撒花！
	return 0;
} 
/*
贴心附上 #7：
Input:
abbbbbccbbbbbbbccccbbbbzbbbbbccbbbbbbbccccbbbbxybbbbbccbbbbbbbccccbbbb
Ans:
abbcbbcbbzbbcbbcbbxybbcbbcbb
*/
```

洛谷 CF 的 RMJ 炸了，放上 CF 的评测链接：[here](https://codeforces.com/contest/363/submission/283471017)。

---

## 作者：A_small_WA (赞：1)

一道简单的模拟，首先把字符串从头开始遍历。

先分析第二种情况，当 $s_i=s_{i+1}$ 且 $s_{i+1}=s_{i+2}$ 时，就应当删去 $s_{i+2}$ 不删 $s_i,s_{i+1}$ 的原因是要保证删除的元素总数最少。

然后分析第一种情况，只要当 $s_i=s_{i+1}$ 且 $s_{i+2}=s_{i+3}$ 时，则删去 $s_{i+3}$ 吗？不对，还得特判 $s_{i+1}\ne s_{i+2}$。否则程序将会把 ```aaaa``` 第二种情况处理。

好啦，完结撒代码！

```cpp
#include <bits/stdc++.h>
using namespace std;
string s,s1;
int main(){
	cin>>s;
	s+=' ';
	s+=' ';
	for(int i=0;i<s.size()-2;i++){
		char tmp1=s[i],tmp2=s[i+1],tmp3=s[i+2],tmp4=s[i+3];
		if(tmp1==tmp2&&tmp3==tmp4&&tmp2!=tmp3) s.erase(s.begin()+i+3),i--;
      //第一种情况
		if(tmp1==tmp2&&tmp2==tmp3) s.erase(s.begin()+i+2),i--;
      //第二种情况
	}
	cout<<s;
	return 0;
}
```
这是蒟蒻的第 $7$ 篇题解，支持一下孩子吧！

---

## 作者：Hutao__ (赞：0)

## 思路

由于 $s_i$ 的答案只跟它附近四个有关，所以我们输入时可以只存储四个字符，然后判断是否删除这个字符。

## 代码


```cpp
//lgRMJ坏了此代码不保证通过此题 
#include<bits/stdc++.h>
using namespace std;
char a,b,c,d;
int main(){
	while(cin>>a){
		if(!(a==b&&b==c)&&!(a==b&&c==d)){//如果满足条件
			cout<<a;//输出
			d=c;
			c=b;
			b=a;
		}
	}
	return 0
} 
```

---

## 作者：liuzhongrui (赞：0)

## 思路
我们发现，每次只会用到四个字符，因此，我们只需要存储四个相邻的字符即可，用 $a,b,c,d$ 存储输入的字符，依次为当前的第一、二、三、四个字符，每次读入新的字符，如果连续三个字符不相同，或者当前字符和前一个字符相同但与前两个字符不相同，则输出当前字符，并更新 $a,b,c,d$，具体操作见代码。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	char a,b,c,d;
	while(cin>>a) {
		if(!(a==b&&b==c)&&!(a==b&&c==d)) {
			cout<<a;
			d=c;
			c=b;
			b=a;
		}
	}
	return 0; 
}
```

---

## 作者：drah_yrev (赞：0)

## 题意
若一个字符串中有三个相同的字母连在一起，或有一对相同的字母后面紧跟着另一对相同的字母，则这个字符串是一个错别字。

给定一个字符串，从这个字符串中删除最少的字符以纠正该词中的错别字（就是让这个串不是错别字），求删除的最少字符后得到的字符串。

## 思路
遍历整个 $S$ 字符串，当前字符为 $S_i$：

如果：$S_i$ 与$S_{i+1}$ 与 $S_{i+2}$ 相等，那么删除 $S_{i+1}$ 与 $S_{i+2}$ 两个字符。

如果 $S_i$ 与 $S_{i+1}$ 相等且 $S_{i+2}$ 与 $S_{i+3}$ 相等，那么将 $S_{i+2}$ 与 $S_{i+3}$ 中的一个删掉。
`S.erase()` 是可以删除 `string` 字符串中的子串的。


---

## 作者：InversionShadow (赞：0)

## CF363C Fixing Typos 题解

简单模拟题。

### 思路：

如果当前位为 $s_i$：

+ 如果三个相同的字母连在一起，即 $s_i=s_{i+1}=s_{i+2}$，那么我们就将其中两个删掉。

+ 如果有一对相同的字母后面紧跟着另一对相同的字母，即 $s_i=s_{i+1}$ 且 $s_{i+2} = s_{i+3}$，那么我们将 $s_{i+2}$ 和 $s_{i+3}$ 中的一个删掉。

### 知识点：

我代码运用了 `.erase` 函数，其用法为：

+ `s.erase(s.begin() + x)` 删除 $s$ 的第 $x$ 位。

+ `s.erase(s.begin() + x, s.begin() + y)` 删除 $s$ 的第 $x \sim y$ 位。

+ `s.erase(s.begin(), s.end())` 删除整个 $s$。

### Code:

```cpp
#include <bits/stdc++.h>
 
using namespace std;

string s;

int main() {
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
	  if (i + 2 < s.size() && s[i] == s[i + 1] && s[i] == s[i + 2]) {
	    s.erase(s.begin() + i + 1, s.begin() + i + 2);  // 删除 (i + 1) ~ (i + 2)
	    i--; // 字符串长度减一，但是 i 便利的次数不能变
	  } else if (i + 3 < s.size() && s[i] == s[i + 1] && s[i] != s[i + 2] && s[i + 2] == s[i + 3]) {
	    s.erase(s.begin() + i + 2); // 按上文，删除 (i + 2) 或 (i + 3) 中的一个
	    i--;
	  }
	}
	cout << s << endl;
	return 0;
}
```

### 题外话：

荣获最劣解，[link](https://www.luogu.com.cn/record/list?pid=CF363C&orderBy=1&status=&page=1)。

---

## 作者：andyli (赞：0)

遍历字符串，若当前字符加入答案后不出现末三位相等或末四位满足“一对相同的字母后面紧跟着另一对相同的字母”，则将其加入答案。  

```cpp
int main() {
    dR(std::string, S);
    std::string ans;
    foreach(c, S) {
        ans += c;
        int n = len(ans);
        if (n >= 3 && ans[n - 1] == ans[n - 2] && ans[n - 2] == ans[n - 3])
            ans.pop_back();
        if (n >= 4 && ans[n - 1] == ans[n - 2] && ans[n - 3] == ans[n - 4])
            ans.pop_back();
    }
    writeln(ans);
    return 0;
}
```

---

