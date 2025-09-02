# Little Elephant and Bits

## 题目描述

The Little Elephant has an integer $ a $ , written in the binary notation. He wants to write this number on a piece of paper.

To make sure that the number $ a $ fits on the piece of paper, the Little Elephant ought to delete exactly one any digit from number $ a $ in the binary record. At that a new number appears. It consists of the remaining binary digits, written in the corresponding order (possible, with leading zeroes).

The Little Elephant wants the number he is going to write on the paper to be as large as possible. Help him find the maximum number that he can obtain after deleting exactly one binary digit and print it in the binary notation.

## 说明/提示

In the first sample the best strategy is to delete the second digit. That results in number $ 11_{2}=3_{10} $ .

In the second sample the best strategy is to delete the third or fourth digits — that results in number $ 11010_{2}=26_{10} $ .

## 样例 #1

### 输入

```
101
```

### 输出

```
11
```

## 样例 #2

### 输入

```
110010
```

### 输出

```
11010
```

# 题解

## 作者：159号程序员 (赞：5)

简单模拟+一点点字符串。

如何使删的数更大呢？

`10011110`，观察一下，只需要删除**数位最大且是0**的数，这样可以使左边的1向右移位后最大。

`10011110` -> `1011110`，发现最左的1从128位变成64位，损失最少。

我们可以把二进制串看成一个字符串，在找到第一个0时删除。

但是注意，如果为 `1111` 之类的串，需要特判一下

_AC Code_

```
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == '0' || i == s.length() - 1) //判断是否找到/到达末尾仍未找到（注意需要-1）
        {
            s.erase(i, 1); //删除s[i]
            break;
        }
    }
    cout << s;
    return 0;
}
```

---

## 作者：DPseud (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF258A)

# 题目意思

给出一个二进制数，求删除任意一位后最大的数，注意是必须删除最后一位。

# 思路

能明显看出这是一道贪心题，既然要保证删除后最大，那肯定要删除 '0'，而高位的 '0' 显然又比低位的 '0' 占更大位权，因此我们只需要删除最高位的 '0'。

删除最高位的 '0' 怎么办？用 for 循环吗？不！用 find 函数更方便！

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	getline(cin,s);
	if(s.find('0')!=-1)s.erase(s.find('0'),1);
	else s.erase(s.length()-1,1);
	cout<<s;
    return 0;
}
```


---

## 作者：王炸拆开打 (赞：1)

# 核心思想：贪心
既然是贪心，那我们要贪什么呢？

仔细思考，显然，删除高位的0比较划算，所以我们**遇0则消**


------------
很~~简单~~的贪心题，上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define LL long long
#define Re register
using namespace std;
int main(){
	string s;
	cin>>s;//读入 
	int c=0;
	for(int i=0;i<s.size();++i){
		if(s[i]=='0'&&!c){//遇0则消 
			c++;
			continue;
		}
		if(i==s.size()-1&&!c) return 0;//如果没有0就只能消掉一个1了 
		cout<<s[i];
	}
	return 0;
}
```


---

## 作者：梨衣 (赞：1)

## 题目大意
给定一个二进制数，输出去掉一位后的最大二进制数
## 思路分析
根据二进制数的性质，位数越往前所代表的数越大，且当前位为 $0$ 时所代表的数为 $0$ 。

那么思路就很明显了，从前往后循环，删去第一个 $0$ 即为正确答案，为方便判断全为 $1$ 的情况，直接加上标记后特判最后一位即可。
## 代码如下
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int main(){
	string s;
	bool v=0;
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='0'&&!v){
			v=1;
			continue;
		}
		else if(!v&&i==s.size()-1)continue;
		else cout<<s[i];
	}
} 
```
## 谢谢观赏

---

## 作者：封禁用户 (赞：0)

# 题意
给定一个二进制的整数（含前导 $0$ ），求删去任意一位数之后最大的二进制整数（含前导 $0$ ）。

# 思路
**其实就是一道贪心题。**

怎样求删去任意一位数之后最大的二进制整数呢？

当我们多列出几个二进制的整数时可以发现一个规律。

情况一：

如果二进制整数中全部都是 $1$ ，那么就**删除数中的最后一位**。

情况二：

如果二进制整数中有 $0$ ，那么**删除整数中的第一个 $0$ 。**

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
long long a=-1;
int main()
{
    cin>>st;
    for(int i=0; i<st.size(); i++) if(st[i]=='0') {a=i; break;}
    if(a==-1) st.erase(st.size()-1,1);
    else st.erase(a,1);
    cout<<st;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 题目分析
这题让我们删掉一位数后最大，那么只需要删掉最高位的 $0$ 就可以了。

如果都是 $1$ ，就删最后一位。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long p;
string st;
int main()
{
	cin>>st;
	for(int i=0; i<st.size(); i++)if(st[i]=='0'||i+1==st.size()){p=i;break;}
	st.erase(p,1);
	cout<<st;
	return 0;
}
```


---

## 作者：zwy__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF258A)
### 题意
给定一个二进制的整数（含前导 $0$ ），求删去任意一位数之后最大的二进制整数（含前导 $0$ ）。
### 思路
不要因为这题是蓝题就想复杂了，其实，只要删掉第一个出现的 $0$ 或者如果没有 $0$ 就随便删除一个 $1$ 就行了。

### [记录](https://www.luogu.com.cn/record/72687428)

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int main()
{
	cin>>a;
	for(int i=0; i<a.size(); i++)
	{
		if(a[i]=='0'||i==a.size()-1)
		{
			a.erase(i,1);
			break;
		}
	} 
	cout<<a;
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

# 题意

给定一个二进制的整数（含前导 $ 0 $ ），求删去任意一位数之后最大的二进制整数（含前导 $ 0 $ ）。

# 思路

要让这个数最大，那肯定要让 $ 0 $ 最少 。 如果有 $ 0 $ ， 肯定要把最早出现的 $ 0 $ 删掉 。 如果没有 $ 0 $ ，那只能随意删掉 $ 1 $ 个 $ 1 $ 。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int main(){
	cin>>st;
	for(int i=0;i<st.size();i++)
		if(st[i]=='0'||i==st.size()-1){
			st.erase(i,1);
			break;
		}
	cout<<st; 
	return 0;
}
```

---

## 作者：Yukinoshita_Yukino (赞：0)

一道贪心题。

给定一个二进制的整数（含前导 0），求删去任意一位数之后最大的二进制整数（含前导 0）。

我们先来考虑一下有 0 的情况，删掉最前面的 0 的方法是最优的。因为不论删掉哪一位，都相当于把前面的所有数左移一位。我们希望左移的有效数越少，这样修改后的数就越大。显然，最前面的0前面的有效数（即 1）最少。

如果都是 1，则删掉任意一位即可，因为不论删掉哪一位答案都是一样的。

顺便一提，这题卡掉坏习惯，如果用如下代码会 TLE（


```cpp
#include<bits/stdc++.h>
using namespace std;
char str[100010];
int f=-1;
int main()
{
	scanf("%s",&str);
	for(int i=0;i<strlen(str);i++) 
		if(str[i]=='0'&&f==-1) 
			f=i;
	if(f!=-1) 
		for(int i=0;i<strlen(str);i++) 
			if(f!=i) 
				printf("%c",str[i]);
	if(f==-1) 
		for(int i=0;i<strlen(str)-1;i++) 
			printf("%c",str[i]);
	return 0;
 } 

```

而使用如下代码会 AC（

```cpp

#include<bits/stdc++.h>
using namespace std;
string str;
int f=0;
int main()
{
    cin>>str;
    for(int i=0;i<str.length();i++) if((i==str.length()-1||str[i]=='0')&&f==0) str.erase(i,1),f=1;
    cout<<str;
    return 0;
}


```

---

## 作者：WinterRain208 (赞：0)

CF258A 【Little Elephant and Bits】

### 题意分析

给定一个二进制的整数（含前导0），求删去任意一位数之后最大的二进制整数（含前导0）。

如果别扭，有简化版题意：

给你一个字符串，删除一个字符使剩下的字符串字典序最大。

我们自然想到比这个问题复杂却只是黄题的[P1106](https://www.luogu.com.cn/problem/P1106).

### SOLUTION

P1106我们是用砍山峰的策略去贪的，这里也可以砍，遍历找第一个比前面小的位置，因为是二进制串，所以找零即可。

特别地，如果该串全部为$1$，随意删除即可。

###### 题外话

###### ~~这就是$CF$蓝题，大家快来$CF$啊~~

（逃

### $CODE$

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	string str;
	cin>>str;
	for(int i=0;i<str.size()-1;++i)
		if(str[i]=='0'||i==str.size()-1){
			str.erase(i,1);
			break;
		}
	cout<<str;
    return 0;
}

```

$wtrl$

---

## 作者：yewanxingkong (赞：0)

思路很简单。由于是删除一位数，所以删掉这一位数等价于让这一位数前面那几位位数减一，也就是除于二，同时再减去删掉的这个数的值。

所以，删掉的这一位越靠前越好。同时，如果你删掉的这一位如果是个 $1$ ，那你在前面的数除二的同时还要减掉这一位的值，但你如果你删掉这一位后面的一位 $0$ ，你所多减去的是这一位 $1$ 到那一位 $0$ 之间的数除于二，但你不用减去那一位 $1$ 的值。

由于二进制的定义，这一位 $1$ 到那一位 $0$ 之间的数除于二肯定是小于那一位 $1$ 的值的。所以答案就出来了，删去最靠前面的那一位 $0$ 。由于有前导 $0$ 所以需要特殊判断一下。

下面是代码
```cpp
#include<iostream>
#include<cstdio> 
#include<cstring>
using namespace std;
string ru;
int main(){
    cin>>ru;
    int len=ru.size(),ji=0;
	for(int i=0;i<len;++i)
		if(ru[i]=='0'&&ru[i-1]=='1'){ji=i;break;}
	for(int i=0;i<len;++i)
		if(ji!=i)cout<<ru[i];
    return 0;
}
```


---

## 作者：Phoenix_chaser (赞：0)

## 核心：贪心

我们需要考虑一个问题，怎么删数最大。

**首先 肯定不能删1，肯定要删0**

那么该删哪个位置？

拿样例二举例

110010

如果我删了最后一个，那么数变为11001为25

如果我删最前一个，11010为26

是不是发现了什么？没错，我们如果删的0靠前，那后面的1数值会增大，删的靠后，前面的会变小。

### 也就是说：我们需要删一个尽量靠前的0

上代码：
```cpp
#include<iostream>
using namespace std;
string s;
int jilu;
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++)
	if(s[i]=='0') 
	{jilu=i;
	break;}
	for(int i=0;i<s.size();i++)
	if(i!=jilu) cout<<s[i];
}
```
谢谢观看

---

## 作者：EDqwq (赞：0)

### 题意：

给定一个二进制的整数，求删去任意一位数之后得到最大的二进制整数。

***

### 思路：

分两类讨论：

1. 只有1或0（如11111）

此时无论删除哪一位，得到的数都是一样的，直接输出这个二进制数的前$len - 1$位即可。

2. 有1有0（如1010010）

显然，删除0比删除1要优，删除1会损失一些值，删除0不会损失任何东西，只是将前面的数变小一点。

既然删除0会让前面的数变小（全部除以2），那么我们肯定要让变小的数少一点。

所以我们删除出现的第一个0即可，这时，变小的数是最少的。

***

### 代码：

```cpp
/*
  Author : EnderDeer
  OnlineJudge : Luogu
*/

#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

string a;
bool flag;
int len;
bool flag_;

signed main(){
	cin>>a;
	len = a.length();
	for(int i = 0;i <= len - 1;i ++){
		if(a[i] == '0'){
			flag = true;
			break;
		}
	}
	if(!flag){
		for(int i = 1;i <= len - 1;i ++)cout<<1;
		return 0;
	}
	for(int i = 0;i <= len - 1;i ++){
		if(a[i] == '0' && !flag_){
			flag_ = true;
			continue;
		}
		cout<<a[i];
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：0)

**题意：有一个二进制数$s$，让你去掉$1$个数，使得剩下的二进制数最大**

- 去掉的数一定是$0$，并且那个$0$所在的数位表示的数值**越大越好**

啥意思？

~~看样例解释~~

先看$101$：

- 显而易见，去掉$0$是最大的。所以我们应该尽量选$0$

然后看$110010$：

- 这个时候我们就有了$3$个$0$可选，所在数位分别表示$2^0,2^2,2^3$，我们就选择大的，让其变成$11010$

**但如果全部数字都是$1$呢？**

直接任意去掉一个即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, f;
string str;

bool chk() {//判断是否全部为1。
	for (int i = 0; i < n; i++) {
		if (str[i] == '0') return true;
	}
	return false;
}

int main() {
	cin >> str;
	n = str.length();//获取长度
	if (chk()) {//如果含有0
			for (int i = 0; i < n; i++) {
			if (str[i] == '0' && f == 0) {//获取到了所在数位数值最大的0，跳过去。
				f = 1;
				continue;
			}
			cout << str[i];
		}
	} else {//如果全是1，输出字符串长度 - 1个1即可
		for (int i = 0; i < n - 1; i++) {
			cout << 1;
		}
	}
	return 0;
}
```


---

