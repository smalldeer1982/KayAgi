# Middle-Out

## 题目描述

The problem was inspired by Pied Piper story. After a challenge from Hooli's compression competitor Nucleus, Richard pulled an all-nighter to invent a new approach to compression: middle-out.

You are given two strings $ s $ and $ t $ of the same length $ n $ . Their characters are numbered from $ 1 $ to $ n $ from left to right (i.e. from the beginning to the end).

In a single move you can do the following sequence of actions:

- choose any valid index $ i $ ( $ 1 \le i \le n $ ),
- move the $ i $ -th character of $ s $ from its position to the beginning of the string or move the $ i $ -th character of $ s $ from its position to the end of the string.

Note, that the moves don't change the length of the string $ s $ . You can apply a move only to the string $ s $ .

For example, if $ s= $ "test" in one move you can obtain:

- if $ i=1 $ and you move to the beginning, then the result is "test" (the string doesn't change),
- if $ i=2 $ and you move to the beginning, then the result is "etst",
- if $ i=3 $ and you move to the beginning, then the result is "stet",
- if $ i=4 $ and you move to the beginning, then the result is "ttes",
- if $ i=1 $ and you move to the end, then the result is "estt",
- if $ i=2 $ and you move to the end, then the result is "tste",
- if $ i=3 $ and you move to the end, then the result is "tets",
- if $ i=4 $ and you move to the end, then the result is "test" (the string doesn't change).

You want to make the string $ s $ equal to the string $ t $ . What is the minimum number of moves you need? If it is impossible to transform $ s $ to $ t $ , print -1.

## 说明/提示

In the first example, the moves in one of the optimal answers are:

- for the first test case $ s= $ "iredppipe", $ t= $ "piedpiper": "iredppipe" $ \rightarrow $ "iedppiper" $ \rightarrow $ "piedpiper";
- for the second test case $ s= $ "estt", $ t= $ "test": "estt" $ \rightarrow $ "test";
- for the third test case $ s= $ "tste", $ t= $ "test": "tste" $ \rightarrow $ "etst" $ \rightarrow $ "test".

## 样例 #1

### 输入

```
3
9
iredppipe
piedpiper
4
estt
test
4
tste
test
```

### 输出

```
2
1
2
```

## 样例 #2

### 输入

```
4
1
a
z
5
adhas
dasha
5
aashd
dasha
5
aahsd
dasha
```

### 输出

```
-1
2
2
3
```

# 题解

## 作者：初云悕 (赞：1)

虽然在CF上这道题是2200分的呢，但是实际做起来发现完全是道水题呢...

拿到题目首先要吐槽一下这个过于简洁的翻译，我这种英语蒟蒻完全看不懂英文只能看翻译的就只能谔谔了。补充一些题目中要注意的点吧。

1. 如果无法通过操作把串 $S$ 变成串 $T$ ，则输出 $-1$ 。

2. 串 $S$ 和串 $T$ 中仅含小写字母。

似乎有点难搞呢，不过看到数据范围 ($1≤q≤1$) , ($1≤n≤1$)，用O（$n^3$）的暴力也能过呢，那就完全是道水题了。

我们可以直接暴力出串 $S$ 的子序列和串 $T$ 的子串的最大公共长度，这个长度就是不用进行操作字符的数量，这个长度可以用 $n^3$ 的暴力得出。

要注意判断输出 $-1$ 的情况，可以建一个桶然后暴力比较两个字符串的各个字符出现次数，只要有一个不一样，就可以直接输出 $-1$ ~~数据范围小就可以随便乱搞~~。

代码的细节不多，主要是各个循环的跳出要稍微注意一下，然后就可以愉快的打出暴力AC这道题了。

~~呐...程序里把S和T弄反了，应该问题不大吧。~~

```cpp
#include<bits/stdc++.h>

using namespace std;

int Q , n , t1[30] , t2[30];

string T , S;

int doit(int x) {
	int now = 0 , res = 0 , ans = 0;
	for(int k = 0 ; k < x ; k ++){//枚举以串T中每个字符开头
		res = 0;//每个字符开头的最大长度
		now = 0;//串S中的枚举用的指针
		for(int i = k ; i < x ; i ++) {
			int fl = 0;
			for(int j = now ; j < x ; j ++) {
				if(T[j] == S[i]) {
					now = j + 1;
					res++;
					fl = 1;
					break;
				}
			}
			if(!fl)//如果T中有一个字符无法被S中的字符匹配，就直接跳出，计算下一个字符。
				break;
			ans = max(ans , res);
		}
	}
	return ans;
}

int main(void) {
	cin >> Q;
	while(Q--) {
		cin >> n >> T >> S;
		int fl = 0;
		memset(t1,0,sizeof(t1));
		memset(t2,0,sizeof(t2));
		for(int i = 0 ; i < n ; i ++ )
			t1[T[i]-'a']++;
		for(int i = 0 ; i < n ; i ++ )
			t2[S[i]-'a']++;
		for(int i = 0 ; i < 28 ; i ++ )//建桶暴力判断是否有解
			if(t1[i] != t2[i]) {
				cout << "-1" <<endl;
				fl = 1;
				break;
			}
		if(!fl)
			cout <<n - doit(n) << endl;
	}
}
```


---

