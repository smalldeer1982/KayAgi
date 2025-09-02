# [ABC048D] An Ordinary Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc048/tasks/arc064_b

長さ $ 3 $ 以上の文字列 $ s $ があります。 $ s $ の中に同一の文字が隣り合う箇所はありません。

高橋君と青木君がゲームで勝負します。 二人は交互に次の操作を行います。 高橋君が先手です。

- $ s $ から両端以外の文字をひとつ取り除く。 ただし、その文字を取り除くことで、$ s $ の中に同一の文字が隣り合う箇所ができる場合、その文字を取り除くことはできない。

先に操作を行えなくなった人が負けです。 二人が最適に行動したとき、どちらが勝つかを判定してください。

## 说明/提示

### 制約

- $ 3\ <\ =\ |s|\ <\ =\ 10^5 $
- $ s $ は英小文字のみからなる。
- $ s $ の中に同一の文字が隣り合う箇所はない。

### Sample Explanation 1

先手の高橋君は操作を行うことができません。 なぜならば、$ s $ から両端以外の文字の `b` を取り除くと、$ s $ は `aa` となって `a` が隣り合うからです。

### Sample Explanation 2

先手の高橋君が $ s $ から `b` を取り除くと、$ s $ は `ac` となります。 すると、後手の青木君は操作を行うことができません。 なぜならば、$ s $ には両端以外の文字が存在しないからです。

## 样例 #1

### 输入

```
aba```

### 输出

```
Second```

## 样例 #2

### 输入

```
abc```

### 输出

```
First```

## 样例 #3

### 输入

```
abcab```

### 输出

```
First```

# 题解

## 作者：DPair (赞：20)

## 【前言】
`这么水的题都没人说明一下的吗。。。我看题解里全是打表诶。。。DPair不才，不得不挺身而出了`

## 【说明】
其实看其他题解也能知道要从**字符串长度**以及**首尾是否相同**去考虑，我详细说明一下：

首先我们发现一个及其显然的结论：删除到无法删除时，字符串情况只可能是这样的：
$$
abababab...abab
$$
即字符串中出现且只出现**两种不同**的字符，并**交替出现**（或只剩两个，但也可以看作这种情况）。

证一下：

首先，不可能只有一种字符，因为相邻字符保证不同，而且由于首尾不能被删除，因此最后至少剩下两个字符，即不可能出现只有一个字符的情况。

排除这种可能性后，只出现两种不同字符的原因在于，由于相邻字符保证不同，且我要保证我现在的状态是一个死局，那么字符串$s$中$s_{i-1}=s_{i+1}$，即所有奇数下标位置的字符相同，所有偶数下标位置的字符相同，且这两种字符不同。故只有两种字符，且**奇偶交替出现**。

然后我们发现，若字符串长度为奇数，则首尾下标都为奇数，故要使该状态成为死局必须保证**首尾相同**，反之，即**首尾不同**，则绝对安全，不可能死局，也就是必胜，那么对手也就必败。所以当**字符串长度为偶数且首尾不同**时，我的下一步操作一定会使对手进入必胜态，那么我就必败（因为本游戏没有平局）。

**首尾相同**的情况也类似，只不过此时字符串长度为偶数时是安全的必胜态，奇数才为必败态。

因此当**首尾相同且长度偶数**或**首尾不同且长度奇数**时，先手必胜，反之后手必胜。

代码就不放了，其他题解提供了同一份代码的各种各样的写法，而且也很短很浅显，主要是理解上述推导过程。

---

## 作者：first_fan (赞：7)

算不上是博弈论吧……跟机房隔壁同学玩了几发（人肉打表），发现了事情似乎很~~不~~简单：

```cpp
现在定义事件A和B
A.字符串的两端字符相同
B.字符串的长度为奇数
发现如果AB同时成立或不成立，那么玩家2会胜出；
如果这俩事件中仅一个成立，那么玩家1会胜出。
（这貌似是一个公平游戏）
```

那么我们就想到了如何表示这样一对有趣的事件了：`A xor B`，（xor即异或，AB不同时该位上记1）

> ## `A xor B`为真的时候，显然两件事只发生一件，玩家1胜出，为假的时候，玩家2胜出。

那么我们就得到了本题的（目前）最精简代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin>>s;
	return 0&(int)printf("%s",((s[0]==s[s.length()-1])^(s.length()%2))?"First":"Second");
}
```

其中可以观察到，前者为A事件，后者为B事件，运用xor和三目搞定。

---

## 作者：精神小伙！ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT2153)

## 结论

根据题意~~以及我和我妈的多次试验~~，结论大致如下：
1. 如果字符串的第一个字符与最后一个字符相等：

   - 字符串长度为**偶数**时**第一个人赢**。
   
   - 字符串长度为**奇数**时**第二个人赢**。
   
2. 如果字符串的第一个字符与最后一个字符不相等：

   - 字符串长度为**偶数**时**第二个人赢**。
   
   - 字符串长度为**奇数**时**第一个人赢**。
   



   
## 举例验证：

假设现在字符串是“abcab”，第一个人先把“c”删掉，就会形成一个“abab”的字符串，由于字符串的两边无法删除，所以说第二个人无论怎么删都赢不了，第一个人获胜。

我们可以发现当字符串删除到无法删除时总会出现一个**只有两个字符交替出现**的字符串，因为**不可能出现只有一种字符的字符串**（不能有相邻的两个字符相等），而且两边的字符无法删除，所以也不会出现只有一个字符的情况。

如果要获胜，就要让对方无论怎么删除都会使两个相同的字符相邻，也就是说要让 $ s_{i-1} = s_{i+1} $ ,即所有奇数下标位置上的字符相同，所有偶数下标位置上的字符相同,并且**奇偶交替出现**（不懂的可以再看看上面的例子）。

若字符串长度为奇数，则首尾下标都为奇数，若字符串长度为偶数，则首位下标都为偶数。这时若**首尾相同**，长度为偶数时第一个人必胜。反之，则第二个人必胜。而当**首尾不相同**时长度为奇数时第一个人必胜。反之，则第二个人必胜。

参考了一下 DPair 大佬的题解。

代码如下：


------------

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int len=s.size();
    if(s[0]==s[len-1])//如果首尾相同
    {
    	if(len%2==0) cout<<"First"<<endl;//长度为偶数第一个人赢
    	else         cout<<"Second"<<endl;//否则第二个人赢
    	return 0;
	}
	else//如果首尾不相同
	{
		if(len%2==0) cout<<"Second"<<endl;//长度为偶数第二个人赢
		else         cout<<"First"<<endl;//否则第一个人赢
		return 0;
	}
	return 0;
}

```


---

## 作者：绝艺 (赞：3)

这道题居然没有C++题解？！

于是决定自己发一篇

思路不多说，楼下大佬讲得很清楚了（~~其实是懒得打字~~）

# Code

```cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
	string s;
	cin>>s;
	int l=s.length();
	if(s[0]==s[l-1]){
		if(l%2==0){
			cout<<"First"<<endl;
			return 0;
		}
		else{
			cout<<"Second"<<endl;
			return 0;
		}
	}
	else{
		if(l%2==0){
			cout<<"Second"<<endl;
			return 0;
		}
		else{
			cout<<"First"<<endl;
			return 0;
		}
	}
}
```


---

## 作者：醉梦未苏 (赞：2)

### 这道题可以理解为找规律(大雾)

~~既然我提供了翻译,自然也要发题解了~~

> 如果这个字符串头尾相等

- 如果字符串长度为奇数,答案为玩家2,否则玩家1

> 如果这个字符串头尾不相等

- 如果字符串长度为奇数,答案为玩家1,否则玩家2



```python
s=input() #输入
if(s[0]==s[len(s)-1]): #头尾相等
    if(len(s) & 1): # x&1等价于x%2==1
        print('Second')
    else:
        print('First')
else:
    if(len(s) & 1): #头尾不相等
        print('First')
    else:
        print('Second')
```

---

## 作者：Alpha_Zero (赞：2)

## **这题只要会if和else就好了。**

~~三目运算符是个好东西~~

二话不说上代码
~~~cpp
#include<iostream>
#include<string>
using namespace std;
string s;
int main()
{
    cin >> s;
    unsigned len=s.size();
    bool(s[0]==s[len-1])?(bool(len%2)?cout << "Second\n":cout << "First\n"):(bool(len%2)?cout << "First\n":cout << "Second\n");
    return 0;
}
~~~
 _以上代码等价于_ 
~~~cpp
#include<iostream>
#include<string>
using namespace std;
string s;
int main()
{
    cin >> s;
    unsigned len=s.size();
    if(s[0]==s[len-1])
    {
    	if(len%2==1) cout << "Second\n";
        else cout << "First\n";
    }
    else
    {
    	if(len%2==1)cout << "First\n";
        else cout << "Second\n";
    }
    return 0;
}
~~~
 _或者还可以这么写_ 
~~~cpp
#include<iostream>
#include<string>
using namespace std;
string s;
int main()
{
    cin >> s;
    unsigned len=s.size();
    if((s[0]==s[len-1] && len%2==0) || (s[0]!=s[len-1] && len%2==1))cout << "First\n";
    else cout << "Second\n";
    return 0;
}
~~~
你们觉得那个更好呢？

补充说明：
~~~cpp 
A?B:C
~~~
等于
~~~cpp
if(A)
{
    B;
}
else
{
    C;
}
~~~

---

## 作者：Lithium_Chestnut (赞：0)

依据题意找规律即可。

题目很不良心，$6$ 个样例都是字符串长度为奇数。但这也给我们留下了思考空间，手玩完全就可以直接找规律。

不难猜，首先，如果字符串长度为奇数，分类讨论：首尾相等是 `Second`，首尾不等是 `First`；如果字符串长度为偶数，分类讨论：首尾相等是 `First`，首尾不等是 `Second`。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int l;
int main()
{
	cin>>s;
	l=s.length();
	if(l%2==1)
	{
		if(s[0]!=s[l-1])
		{
			cout<<"First"<<endl;
			return 0;
		}
		else
		{
			cout<<"Second"<<endl;
			return 0;
		}
	}
	else
	{
		if(s[0]!=s[l-1])
		{
			cout<<"Second"<<endl;
			return 0;
		}
		else
		{
			cout<<"First"<<endl;
			return 0;
		}
	}
}
```

---

## 作者：piggymichael (赞：0)

一个好玩的游戏。经过多次试验得到了这个结论：1，字符串首尾两个字符相同。2，字符串长度为奇数。如果两个条件满足一个，First赢；否则Second赢。知道了规律代码就很好写了。用一种不同的写法，不用if里再套if：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string s;
int judge=0;//用一个变量统计满足条件数
int main()
{
    cin>>s;
    if(s[0]==s[s.size()-1])//满足条件1
        judge++;
    if(s.size()%2==1)//满足条件2
        judge++;
    if(judge==1)//满足一个是First
        cout<<"First"<<endl;
    else
        cout<<"Second"<<endl;
    return 0;
}
```
s.size()就是字符串的长度。还有要注意输出时首字母要大写，输出要加换行。

---

