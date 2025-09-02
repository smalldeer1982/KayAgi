# Alternating Current

## 题目描述

两条电线分别插入了正确的位置，但是缠绕在一起，如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343B/800db6fdea950669ce9fc6c935adb535dd5b8f2e.png)

电线不能被剪断或断开，插入的设备也不能被移动，请问是否可以在这种情况下解开电线？

为了更好地理解题意，请阅读样例的解释。

## 样例 #1

### 输入

```
-++-
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
+-
```

### 输出

```
No
```

## 样例 #3

### 输入

```
++
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
-
```

### 输出

```
No
```

# 题解

## 作者：紊莫 (赞：2)

# 题意

~~可自行翻译。~~  
看如下图片，发现把红色的从上面翻过去，把蓝色的往下面绕过来即可解开。  

![](https://cdn.luogu.com.cn/upload/image_hosting/brntfboe.png)

# 分析

可以考虑用栈来模拟这一系列的变化（因为涉及到消消减减）。  

具体地说，当出现 ```++``` 或者 ```--``` 的情况就可以将两者消去，最后判断栈是否为空就是答案。  

其实和括号序列匹配很像。

# 代码

  

```cpp
#include <bits/stdc++.h>
using namespace std;
stack<char> a;
int main(){
	string s;cin>>s;
	for(int i=0,t;i<s.length();i++)
	{
		if(a.size()) t=a.top();
		a.push(s[i]);
		if(a.size()>=2&&t==s[i]) 
			a.pop(),a.pop();
	}
	puts(a.size()?"No":"Yes");
	return 0;
}


```

# 常见 Q&A
Q1： 为什么 $t$ 可以是整型？  
A1： 因为可以自动转换。  

Q2： 在不进入第一个判断的条件下，用值未定的 $t$ 去比较有问题吗？  
A2： 没有。要是第一个判断进不来，第二个也进不去，因为 ```&&``` 是短路运算符。


---

## 作者：KirBytronic (赞：2)

## 思路
分析题目，可知当相邻的两个地方符号相同时，可以解开。可以使用栈模拟，将字符串中的字符挨个放入栈，当栈最顶端的两个字符相同时，将其消去。最后判断栈是否为空即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
stack<char> a;
string s;
char b;
int main(){
    cin>>s;
    for(int i=0;i<s.size();i++){
	if(a.size())
           b=a.top();//将字符串中的字符挨个放入栈
	a.push(s[i]);
	if(a.size()>=2 and b==s[i]){//当栈的长度大于等于2时，判断栈顶的两个字符是否相等。
            a.pop();
            a.pop();
             }
	}
	if(!a.size()){//判断栈是否为空
        cout<<"Yes";
    }else{
        cout<<"No";
    }
    return 0;
}
```


---

## 作者：流绪 (赞：0)

模拟！

一看题目一脸懵逼，仔细读题加看图后发现，如果有两个相邻的地方符号一样，那么这里就可以解开。所以这题就是相邻的位置如果相同则消掉，看最后能不能把整个字符串消掉。

首先特判字符串长度是奇数，则不合法，因为两两相消，肯定要偶数才能消完啊！奇数的话有一个字符没人和他消。（正如情人节写题解的我一样T_T）

然后我们用栈来模拟这个过程，每次压入一个数据，如果栈内数据大于 1，我们就取出栈顶的两个来看看能不能消，不能消就放回去，注意这里放回要把先取的后放回，不然顺序就错了！整个过程模拟完看看栈空了没有，空了就是解开了，没空就是失败了。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
stack<char>q;
char a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	cin >> a;
	int len = strlen(a);
	if(len%2)
		cout << "No";
	else
	{
		for(int i=0;i<len;i++)
		{
			q.push(a[i]);
			if(q.size()>1)
			{
				while(q.size()>1)
				{
					char b,c;
					b=q.top();
					q.pop();
					c=q.top();
					q.pop();
					if(b!=c)
					{
						q.push(c);
						q.push(b);//先取后放
						break;
					}
				}
			}
		}
		if(q.empty())
			cout << "Yes";
		else
			cout << "No";
	}
	return 0; 
}  
```


---

