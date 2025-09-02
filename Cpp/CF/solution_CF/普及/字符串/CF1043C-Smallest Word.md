# Smallest Word

## 题目描述

IA has so many colorful magnets on her fridge! Exactly one letter is written on each magnet, 'a' or 'b'. She loves to play with them, placing all magnets in a row. However, the girl is quickly bored and usually thinks how to make her entertainment more interesting.

Today, when IA looked at the fridge, she noticed that the word formed by magnets is really messy. "It would look much better when I'll swap some of them!" — thought the girl — "but how to do it?". After a while, she got an idea. IA will look at all prefixes with lengths from $ 1 $ to the length of the word and for each prefix she will either reverse this prefix or leave it as it is. She will consider the prefixes in the fixed order: from the shortest to the largest. She wants to get the lexicographically smallest possible word after she considers all prefixes. Can you help her, telling which prefixes should be chosen for reversing?

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first example, IA can reverse the second and the third prefix and get a string "abbb". She cannot get better result, since it is also lexicographically smallest string obtainable by permuting characters of the initial string.

In the second example, she can reverse any subset of prefixes — all letters are 'a'.

## 样例 #1

### 输入

```
bbab
```

### 输出

```
0 1 1 0
```

## 样例 #2

### 输入

```
aaaaa
```

### 输出

```
1 0 0 0 1
```

# 题解

## 作者：引领天下 (赞：4)

不得不说py3有的时候是真的强

这个题目py3有专用命令`zip`……

zip() 函数用于将可迭代的对象作为参数，将对象中对应的元素打包成一个个元组，然后返回由这些元组组成的对象。

```python
s=input()
print(*(int(x!=y)for x,y in zip(s,s[1:]+'b')))//直接强行命令
```

---

## 作者：liuyz11 (赞：4)

广告[这场比赛题解的原地址](https://www.cnblogs.com/nblyz2003/p/9868480.html)

这题大意就是给你一个字符串s（只由a和b组成），你每次可以将这个字符串的任意前缀翻转，让你求得到字典序最小的字符串的任意一种操作。

因为这个字符串只有ab，所以这题最后得到的字符串一定前面都是a，后面都是b（这是一定能得到的，至于为什么，我说不清），所以对于每次翻转，都要把所有的a放一起，b放一起。

然后我们开始模拟一下，随便写个字符串ababbaaababaaab。（懒得画图）

我们的算法就是把所有a和b分开放。

这是原先的字符串ab|abbaaababaaab

旋转ab

变成baa|bbaaababaaab

旋转baa

变成aabbb|aaababaaab

旋转aabbb

变成bbbaaaaa|babaaab

旋转bbbaaaaa

变成aaaaabbbb|abaaab

旋转aaaaabbbb

变成bbbbaaaaaa|baaab

旋转bbbbaaaaaa

变成aaaaaabbbbb|aaab

旋转aaaaaabbbbb

变成bbbbbaaaaaaaaa|b

旋转bbbbbaaaaaaaaa

变成aaaaaaaaabbbbbb

中间的竖杠之前的就是已经将a和b区分开来的字符串，然后我们发现，竖杠之前就是要旋转的地方（为了使a或b连在一起）。然后进一步发现旋转的地方就是a和b的交界线（why？no why！）。

所以我们只要找到所有a和b的交界线就好了，还有就是如果最后一位是a就要在最后将整个字符串旋转（我居然因为这个wa了一次……

代码如下
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define INF 1 << 30
#define MAXN 1005
using namespace std;
typedef long long LL;
typedef pair<int,int> par;

char st[MAXN];
bool flag[MAXN];

int main(){
    scanf("%s", st + 1);
    int len = strlen(st + 1);
    rep(i, 1, len - 1)
        if(st[i] != st[i + 1]) flag[i] = 1;
    if(st[len] == 'a') flag[len] = 1;
    rep(i, 1, len) printf("%d ", flag[i]);
    puts("");   
    return 0;
}
```

---

## 作者：ImNot6Dora (赞：0)

好久没有写题解了。

今天就来写（shui）一发。

为了让字典序最小，必须 $a$ 在前，$b$ 在后，所以当前后两个字符分别为 $a$ 和 $b$ 时，需要交换一次。但由于最后一个字母有可能是 $a$，所以最后还要特判是不是 $a$，如果是 $a$ 那就最后再次进行翻转。
### AC C++ CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	cin>>s;
 	for(int i=0;i<s.length();i++){
 		if(s.length()-1!=i&&s[i]!=s[i+1]||i==s.length()-1&&s[i]=='a')cout<<1<<' ';	
		else cout<<0<<' ';
	}
	return 0;
}
```
By ImNot6Dora

---

## 作者：Digital_Sunrise (赞：0)

## CF1043C题解

[CF1043题解合集](https://www.luogu.com.cn/blog/yl2330/I-Love-YR-Forever)

[Markdonw源代码](https://yhwh-group.coding.net/public/codingwiki/files/git/files/master/blog/CF1043/C.Markdown)

Update 21.11.17 更正博客地址

### 题意简述

给你一个字符串 $s$ （只由 $\tt a$ 和 $\tt b$ 组成），对于 **依次** 的每一个前缀，你可以选择翻转或不反转 （即之前的翻转会对现在的翻转有影响）

### 思路

字典序最小，即 $\texttt{a}$ 全都在字符串前端，而 $\texttt{b}$ 都在字符串的后端。

要想实现这样的目标，我们必须实现过程中的 “两极分化” 。

即**每当遇到相邻但不相等的两个字符，就将前一个字符所代表的前缀翻转**

注意，上述操作实在**保证前面的字符已经“两极分化”**执行的

因为在保证这个前提了之后，翻转后原来的第一个字符和这个字符可以切合在一起，继续维持这个形态。

比如对于字符串 $\tt bbbaaaaab$ ，

我们在 $\tt bbbaaaaa|b$ 处翻转（保证前面已经 " 两级分化 "），

则得到字符串 $\tt aaaaabbbb$

所以结论就是：在每一个 $\texttt{a}$ 与 $\texttt{b}$ 的交界处翻转。

注意：如果最后一个字符是 $\texttt{a}$ ，需要再次翻转（字典序最小）。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;

signed main()
{
	cin >> s;
	for(int i = 0;i < s.length();i++)
	{
	    if(i == s.length() - 1 and s[i] == 'a')
	    {
	        putchar('1');
			putchar(' ');
			return 0;
	    }
		if(i != s.length() - 1 and s[i] != s[i + 1])
		{
			putchar('1');
			putchar(' ');
		}
		else
		{
			putchar('0');
			putchar(' ');
		}
	}
	return 0;
}
```

---

