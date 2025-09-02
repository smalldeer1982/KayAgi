# A Map of the Cat

## 题目描述

If you have ever interacted with a cat, you have probably noticed that they are quite particular about how to pet them. Here is an approximate map of a normal cat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952B/ac74b4a6b7c2f3f70f434fbbbba9b66903682fc4.png)However, some cats won't tolerate this nonsense from the humans. Here is a map of a grumpy cat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952B/8b21a0f522686b6bb86b329b669f56577afc2e8b.png)You have met a cat. Can you figure out whether it's normal or grumpy?

## 说明/提示

Please make sure to use the stream flushing operation after each query in order not to leave part of your output in some buffer.

# 题解

## 作者：Ariadne (赞：5)

**这道题之所以看起来让人难受是因为**：

1、涉及不到我们熟悉的算法

2、英文太难了我们都看不懂~~尤其还是俄国人写的英文~~

3、这道题是愚人节特辑


**总体来说难度其实不大，想要AC的话直接添加判定Normal或者是Grumpy的特征就可以了，if&else相信大家都会。**

---（就像数学里集合的思想一样，只要保证cout或者printf没问题就行了）---

以下是官方**毒瘤**题解



_________
```
#include<bits/stdc++.h>
using namespace std;
string a;
int main(){
    for(int i=0;i<6;i++)
    {
        cout<<i<<endl;
        cin>>a; 
        if(a[0] =='w'||a[0] =='a'||a[2]==' ')
        {
            cout<<"grumpy";
            return 0;
        }
    }
    cout<<"normal";
}
```
________

看懂了吗？
**~~没看懂就对了~~**

我反正是想不太出来（我太弱了orz）用链表转换定义的这个方法，其难点在于string a的域要保证和题目中所给的一样……这个时候就需要我们~~反复横跳~~回去题目看题。

---

## 作者：　　　吾皇 (赞：1)

蒟蒻表示看不懂..~~直到去了CF官网查看~~\
\
**只能给出代码了QAQ**
### 代码
```
#include<bits/stdc++.h>
using namespace std;
string a;
int main(){
	for(int i=0;i<6;i++)
	{
		cout<<i<<endl;
		cin>>a; 
		if(a[0] =='w'||a[0] =='a'||a[2]==' ')
		{
			cout<<"grumpy";
			return 0;
		}
	}
	cout<<"normal";
}
```


---

## 作者：__main__ (赞：1)

这是一道**愚人节题**

题目大意：如果一只猫的特征含有`great`、`don't think so`、`don't touch me`、`not bad`、`cool`，则它是`normal`的；如果一只猫的特征含有`no way`、`don't even`、`worse`、`terrible`、`go die in a hole`、`are you serious`，则它是`grumpy`的。

按题意模拟即可。

这里有个小问题：读入字符串要用`getline`，我猜是因为读入缓存的问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	for (int i = 0; ; ++i)
	{
		printf("%d\n", i);
		string s;
		getline(cin, s);
		if (s == "great" || s == "don't think so"
		    || s == "don't touch me" || s == "not bad" || s == "cool")
		{
			puts("normal");
			return 0;
		}
		else if (s == "no way" || s == "don't even" || s == "worse"
		         || s == "terrible" || s == "go die in a hole" || s == "are you serious")
		{
			puts("grumpy");
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Li_zi_wei (赞：0)

~~我才不会告诉你这是愚人节题目~~

首先肯定看不懂题面 实际上是这样的——

```
如果输入的内容有normal或grumpy特有的特征就输出这种猫
```

### 给一份样例：

#### Input:

```
qwq
orz
tql
ddw
great
```
#### Output:
```
1
2
3
4
5
normal
```

接下来就是作为愚人节题目的坑点

1. ！号忽略不计

2. 大写转小写

然后就是**代码**了

```
#include<bits/stdc++.h>

using namespace std;
string s;
int i = 1;
bool inseg(in
t bef,int ob,int aft)
{
	return bef <= ob && ob <= aft;
}

void change()
{
	int len = s.length();
  	for(int i = 0;i < len;i ++)
    if(inseg('A',s[i],'Z')) s[i]=s[i]-'A'+'a';
}
int main()
{
	while(true)
	{
		cout << i << endl;
		
		getline(cin,s);
		
		change();
		
		if(s == "great"||s == "don't think so"||s == "don't touch me"||s == "not bad"||s == "cool")
		{
			cout << "normal";
			return 0;
		}
		if (s == "no way"||s == "don't even"||s == "terrible"||s == "worse"||s == "are you serious"||s == "go die in a hole")
        {
        	cout << "grumpy";
        	return 0;
		}
		i ++;
	}
	return 0;
} 
```

P.S 因为输入实际都是小写所以你也可以——

```
#include<bits/stdc++.h>

using namespace std;
string s;
int i = 1;

{
	while(true)
	{
		cout << i << endl;
		
		getline(cin,s);
		
		
		if(s == "great"||s == "don't think so"||s == "don't touch me"||s == "not bad"||s == "cool")
		{
			cout << "normal";
			return 0;
		}
		if (s == "no way"||s == "don't even"||s == "terrible"||s == "worse"||s == "are you serious"||s == "go die in a hole")
        {
        	cout << "grumpy";
        	return 0;
		}
		i ++;
	}
	return 0;
} 
```

---

## 作者：Ludo (赞：0)

### 这是一道交互题

交互题是非传统题的一种。

选手程序需要写一个程序，通过与测评程序交互来完成任务。

选手程序通常会向测评程序发出询问，并得到其反馈。

通常题目也会通过限制交互次数来达到最优解的效果。

比如猜数字 范围是1-100的随机数 让我们去猜 

反馈结果是这个被猜数与我们猜的数的大小关系 

在最优策略下只需要 （2^7=128>100） 7次即可猜出

### 思路解析

这道题是要我们**分辨一只猫是 “normal” 还是 “grumpy”**

而且这是愚人节的题 它并没有讲**交互的次数限制**

我们会想**令交互次数最小**

当我们找到结果以后我们就输出结果 这也不失为一种好方法

一只$normal$ $cat$的独有特征是

- "great!"

- "don't think so"

- "don't touch me!"

- "not bad"

- "cool"

一只$grumpy$ $cat$的独有特征包括

- "no way"

- "DON'T EVEN"

- "Worse"

- "Terrible"

- "Go die in a hole"

- "Are you serious?"

另外还有个我觉得很坑的东西 **大写都要变成小写** **问号感叹号判断的时候不能要**

### 代码

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
string s;
int main(void)
{
	for (int i=0;i<10;i++)
	{
		cout<<i<<endl;
		getline(cin,s);
		if (s=="great"||s=="don't think so"||s=="don't touch me"||s=="not bad"||s=="cool")
		{
			cout<<"normal";
			return 0;
		}
		if (s=="no way"||s=="don't even"||s=="worse"||s=="terrible"||s=="go die in a hole"||s=="are you serious")
		{
			cout<<"grumpy";
			return 0;
		}
	}
}
```


---

