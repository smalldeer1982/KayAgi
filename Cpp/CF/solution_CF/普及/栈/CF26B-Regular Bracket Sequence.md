# Regular Bracket Sequence

## 题目描述

给定一个由左右括号组成的序列 $s$，求其最长合法括号子序列（我们定义空串也是一种合法括号序列）。

## 说明/提示

$1 \leq |s| \leq 10^6$

## 样例 #1

### 输入

```
(()))(
```

### 输出

```
4
```

## 样例 #2

### 输入

```
((()())
```

### 输出

```
6
```

# 题解

## 作者：Siyuan (赞：6)

### 括号匹配问题：https://www.luogu.org/problemnew/show/P1739

- 很显然，此题就是用栈实现的（具体参考上方题目）。

- 如果是左括号则入栈；如果是右括号，只要栈非空就说明有一对合法括号。

- 使用$\ cnt$来记录栈中的元素个数。

**代码如下**：
> （一边读入，一边进行入栈出栈；并且不使用真正的栈而是虚构一个栈，使空间复杂度降至$\ O(1)$，时间复杂度为$\ O(N)$）

```
#include<cstdio>
using namespace std;

int main()
{
	register int ans=0,cnt=0;
	register char c=getchar();
	while(c!='\n'&&c!=EOF)
	{
		if(c=='(')  cnt++;
		else  if(cnt>0)  ans+=2,cnt--;
		c=getchar();
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：TLMPEX (赞：3)

这道题就是括号匹配问题。

思路：用一层循环枚举每一个括号，如果是左括号，则左括号数加一，如果是有括号，则看前面有没有左括号，如果有则左括号数减一，括号对数加一。最后输出括号对数乘2了，因为每对括号包含两个括号，分别是左括号和右括号。

代码如下。
```c
#include<bits/stdc++.h>
using namespace std;
string k;
int main(){
	int i,l,t=0,z=0;
	getline(cin,k);
	l=k.size();
	for(i=0;i<l;i++)
		if(k[i]=='(')t++;//如果是左括号，t加一
		else if(t&&k[i]==')'){//如果有有括号且有左括号，左括号数减一，括号对数加一
			t--;
			z++;
		}
	cout<<z*2;//因为是有z对括号，所以要乘2
}
```


---

## 作者：SIXIANG32 (赞：3)

## [题目传送门：CF26B](https://www.luogu.com.cn/problem/CF26B)  
题目概述：  
给你个括号序列，输出最长合法的序列的长度。  


------------
其实这道题很像[这道题](https://www.luogu.com.cn/problem/P1739)。  
关于括号匹配的~~水~~题目，首先想到的是**栈**这个数据结构。  
栈是啥呢？简单来说，栈就是一个线性表，只能从顶端进出。

打个比方：栈就像一摞书，你只能在最上面放一本或取一本书，总不能从中间或最后放书和取书吧。  

------------

懂了栈是啥，这道题就很简单了。  
括号匹配的精髓在于：**左括号进栈，右括号出栈**。  
如果遇上了右括号且栈空了，说明无法匹配成功。  
否则匹配成功的话，把栈首弹出。  

这道题要求我们输出最长的合法子序列，那么在匹配成功时要在答案计数器上+2，表示加上了这个左括号和右括号。  

我们遍历一遍字符串，只要根据上面所说的操作去做就阔以AC这道题啦！


------------
奉献上简简单单的代码：
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str;
	cin>>str;
	int stack=0,ans=0;//这里我们只要记录栈的大小即可，反正里头元素都一样，都是左括号
	for(int p=0;p<=str.size()-1;p++)//遍历字符串
	{
		if(str[p]=='(')stack++;//遇上左括号，进栈
		if(str[p]==')')//遇上右括号
			if(stack>0)//匹配成功
				stack--,ans+=2;//出栈并更新答案
	}
	cout<<ans<<endl;//快乐的输出
}
```

---

## 作者：Blunt_Feeling (赞：2)

# CF26B Regular Bracket Sequence 题解

这道题用栈模拟即可。

大体的思路就是在遍历string的同时，

遇到‘(’就把它压入我们的栈里面。

当string里遇到一个‘)’，并且此时栈顶元素为‘(’时，

就相当于遇到了一个完整的括号。

这个时候吧栈顶的‘(’弹出，以便处理这个括号之外套着的括号，

同时把ans+=2（因为一个括号算两个字符）。

附上C++的AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans=0;
stack<char> stk;//定义一个char类型的栈 
int main()
{
	cin>>s;
	int len=s.length();
	for(int i=0;i<len;i++)
	{
		if(!stk.empty()&&stk.top()=='('&&s[i]==')')//遇到一个括号 
		{
			stk.pop();//弹出栈顶的‘(’
			ans+=2;
		}
		else stk.push(s[i]);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：pigstd (赞：2)

方法：用栈

先直接全部读入，然后从头到脚扫描。遇到‘(’压一个数进去，遇到‘)’，如果栈不为空，则弹出一个数，再把答案加2

c++代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

int ans;
stack<int> s;//建一个栈
string a;

int main()
{
	cin>>a;
	for (int i=0;i<a.size();i++)
		if (a[i]=='(')
			s.push(1);//压一个数
		else
			if (!s.empty())//不为空
				s.pop(),ans+=2;
	cout<<ans;
	return 0;
}
```

---

## 作者：Into_qwq (赞：1)

由于它要求的是最长的合法的子序列，我们自然可以想到栈其实

栈的思想:

## $FILO$->$First$ $in$ $last$ $out$　先进后出

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rgj03j8b.png)

------------
### 我们便可以利用这种数据结构来解题

**思路：**

如果是左括号就入栈

如果是右括号，有两种情况：

1.如果栈内为空（没有左括号可以和它匹配）

则它没有任何的用处，不管它

2.如果栈内不为空（有左括号可以和它匹配）

则弹出栈顶（拿出一个与它匹配），并把答案增加$2$（$1$对括号是两个）

### 代码如下：
```c++
#include<cstring>
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1000000;
int ans=0,top=0;
char stack[N],a[N];
int main()
{
	scanf("%s",a);
	for(int i=0;i<strlen(a);++i)
	{
		if(a[i]=='(') stack[top++]='(';
		else if(top>0) ans+=2,top--;
	}
	cout<<ans;
	return 0;
}
```

------------
但是，这样的代码不够简洁~~改了也简洁不了多少~~：

**为什么非要用栈呢，模拟一下栈的操作不就好了吗**

我们可以用一个变量->$top$来表示栈的最顶层

P.S.$top$初始化为0

如果是左括号'('就将$top$的值增加（入栈）

如果是右括号')'

先判断$top$的值是否大于0（栈内是否有左括号）

如果是，那么将答案增加2，并把$top$减少1（找到匹配的 , 出栈）

否则，就不管它（此时这个不合法，舍弃）

## AC代码如下
```c++
#include<bits/stdc++.h>
using namespace std;
int ans,top;
int main()
{
	char a[1000000];
	scanf("%s",a);
	for(int i=0;i<strlen(a);++i)
	{
		if(a[i]=='(') top++;
		else if(top>0) ans+=2,top--;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Programmtion (赞：1)

括号匹配问题。

[再看一眼题目](https://www.luogu.com.cn/problem/CF26B)
## 思路：
用栈来实现。

遇到左括号入栈，

遇到右括号并且此时栈顶元素为左括号时，

就遇到了一个括号。

这个时候吧栈顶的左括号弹出，

同时把数量加2因为一个括号有两个字符。

好了，上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	stack<char> s;
	string a;
	int ans=0;
	cin>>a;
	for(int i=0;i<=a.size();i++){
		if(a[i]=='(') s.push(a[i]);
		if(a[i]==')'){
			if(!s.empty()){
				s.pop();
				ans+=2;
			}
		}
	}
	cout<<ans;
	return 0;
}
```
不要抄袭

---

## 作者：qhztz (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF26B)
## 思路：
显然，这道题跟[括号匹配](https://www.luogu.com.cn/problem/P1739)很像，在做这道题前可以先做做那道题。

我们只需要再那道题的基础上多设置一个变量 $ans$ 记录输出匹配的数量，最后输出即可。

**具体思路：** 先输入，如果是 ‘(’ 就进栈，如果是 ‘)' 且栈不空就匹配，弹出栈，$ans++$，具体详见代码。
## 代码：
```cpp
#include<cstdio>
#include<stack>
#include<cstring>
using namespace std;
char k[1000000];
int ans;
stack<char>b;
int main(){
    gets(k);
    int l=strlen(k);
    for(int i=0;i<l;++i){
        if(k[i]=='(') b.push(k[i]);//进栈
        else if(k[i]==')'&&b.empty()==0){//找到匹配的括号
            b.pop();
            ans+=2;//记录个数
    	}
	}
	printf("%d\n",ans);
}
```
拜拜qwq

---

## 作者：FutureThx (赞：0)

### 题 面
[传送门](https://www.luogu.com.cn/problem/CF26B)

### 思 路

~~作为一个$ OI $ 选手首先看到题目就应该想到这题应该用栈做（教练原话）。~~
$ $

简单分析一下：
$ $

 1.遇到左括号就入栈
$ $

 2.遇到右括号就与栈内元素匹配，若栈不为空就弹出栈首，同时将记录字符串长度的计数器 $t$ 加**2**(记住，一定是加 **2** ，因为一对括号有两个字符)
$ $

3.输出计数器 $t$

### 伪代码


```
定义计数器:t = 0,栈:s,字符串:a
输入a
遍历整个字符串a:
          若当前遍历字符为 '(':
                       将'('压入栈
          若当前遍历字符为 ')'并且栈不为空:
                       弹出栈顶，计数器+2
输出计数器t

```
### 代码实现

```cpp
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

int main()
{
    int t = 0;
    stack<int> s;
    string a;
    cin >> a;
    for(int i = 0;i < a.size();i++){
        if(a[i] == '(') s.push(a[i]);
        if(a[i] == ')' && !s.empty()){
            t += 2;    
            s.pop();
        }
    }
    cout << t;
    return 0;
}
```


---

## 作者：tobie (赞：0)

这道题就是裸的括号匹配，但是多了一些小要求。

简单来说就是要我们找到有多少个不重复的`()`子序列。

所以我们只需要用栈模拟即可。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int ans=0,s=0;//由于永远都是左括号进栈，所以只需要用一个变量存储即可
char ch;
int main()
{
	ch=getchar();
	while(ch!='\n'&&ch!=EOF)
	{
		if(ch=='(')  s++;//进栈
		else if(s>0)  ans+=2,s--;//找到匹配的括号
		ch=getchar();
	}
	printf("%d",ans);//愉快地输出
	return 0;
}
```


---

