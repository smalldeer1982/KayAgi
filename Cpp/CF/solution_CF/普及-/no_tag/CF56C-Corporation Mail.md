# Corporation Mail

## 题目描述

The Beroil corporation structure is hierarchical, that is it can be represented as a tree. Let's examine the presentation of this structure as follows:

- $ employee $ ::= $ name $ . | $ name $ : $ employee_{1} $ , $ employee_{2} $ , ... , $ employee_{k} $ .
- $ name $ ::= name of an employee

That is, the description of each employee consists of his name, a colon (:), the descriptions of all his subordinates separated by commas, and, finally, a dot. If an employee has no subordinates, then the colon is not present in his description.

For example, line MIKE:MAX.,ARTEM:MIKE..,DMITRY:DMITRY.,DMITRY... is the correct way of recording the structure of a corporation where the director MIKE has subordinates MAX, ARTEM and DMITRY. ARTEM has a subordinate whose name is MIKE, just as the name of his boss and two subordinates of DMITRY are called DMITRY, just like himself.

In the Beroil corporation every employee can only correspond with his subordinates, at that the subordinates are not necessarily direct. Let's call an uncomfortable situation the situation when a person whose name is $ s $ writes a letter to another person whose name is also $ s $ . In the example given above are two such pairs: a pair involving MIKE, and two pairs for DMITRY (a pair for each of his subordinates).

Your task is by the given structure of the corporation to find the number of uncomfortable pairs in it.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF56C/9868b26a06de68925d83118f98afdf9f4510a164.png)

## 样例 #1

### 输入

```
MIKE:MAX.,ARTEM:MIKE..,DMITRY:DMITRY.,DMITRY...
```

### 输出

```
3
```

## 样例 #2

### 输入

```
A:A..
```

### 输出

```
1
```

## 样例 #3

### 输入

```
A:C:C:C:C.....
```

### 输出

```
6
```

# 题解

## 作者：Fr0sTy (赞：4)

### 首先：这道题的题面上画了一颗树，但好像并不是关于树的题目啊...

### 1 . 题意概述

题目就是让我们统计所谓“**不舒服情况**”，即上级与下级名字相同。题目就是要统计这种情况数。


### 2 . 变量


------------

**_1 ._** 定义一个 **char 形变量**   c，一个个读入那些字符，直到  **EOF** ❶。

**_2 ._** 定义一个存储名字用的 **字符串数组**   names。

**_3 ._** 定义一个记录人数用的  **int 形变量**   people。

### 3 . 思路


------------

**_1 ._** 在遇到.字符时,计算其之前与其同名的人的个数,然后  `ans++`。
 
**_2 ._** 在遇到 $,$ 或 $:$ 时，增加人数，即  `people++`。

**_3 ._** 如果输入的是人名的一部分，那么继续“堆叠”这个名字，可以有    `names[people]+=c`。

### 4 . 可能会犯的一些问题


------------

**_1 ._** 用  while 输入时，必须特判 **EOF**，不然样例一会 **TLE**，样例三会 **RE**。

**_2 ._** 判断完这个  people 以后，必须将其删去，不然会重复判断。

### 代码


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,people=1;
char c;
string names[1000005];
int main() {
	while(scanf("%c",&c)!=EOF) {
		if(c=='.') {
			for(int i=0;i<people;i++)
				if(names[people]==names[i])
					ans++;
			names[people--]="";
		}
		else if(c==':'||c==',') people++;
		else names[people]=names[people]+c;
	}
	printf("%d",ans);
	return 0;
}
```


### 一些备注：

  ❶   : 什么，你不知道 **EOF**？研究一下[这个](https://baike.baidu.com/item/EOF/1017800?fr=aladdin) ，也许对你有帮助。

---

## 作者：_zzzzzzy_ (赞：2)

## 思路
通过读题可知，~~有用的字符只有,:.~~

- 当这个字符是 $.$ 时，计算其之前与其同名的人的个数。
- 当这个字符是 $,$ 或 $:$ 时增加人数。
- 否则这个就是人名，堆叠名字即可。

暴力模拟即可 $A$ 掉这题。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[1000005];
int ans,tot=1;
char x;
int main() {
	while(cin>>x) {
		if(x=='.') {
			for(int i=0; i<tot; i++)
				if(a[tot]==a[i])
					ans++;
			a[tot--]="";
		} else if(x==':'||x==',') tot++;
		else a[tot]=a[tot]+x;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：nanatsuhi (赞：2)

一道看起来跟树有关，但实际上只需要用字符串处理就可以解决的题。

简单的思路就是以 

> ### **. : ,**

三种字符来界定不同名字，并加以统计。

具体操作请看代码。

```cpp
#include <iostream>
using namespace std;
char S;//当前字符
int n, ans;//n是当前位置，ans是“不舒服情况总数”
string s[600];//名字字符串
int main()
{
    while (cin >> S)//不断读入字符
    {
        if (S == '.')//"."的情况就是要结算一次
        {
            for (int i = 0; i < n; i++)//检查所有排在自己之前的名字
                if (s[i] == s[n])
                    ans++;
            s[n] = "";
            n--;//返回上一个名字
        }
        else if (S == ':' || S == ',')//新的名字
            n++;
        else
            s[n] += S;//给当前名字增加字符
    }
    cout << ans << endl;//输出答案
    return 0;
}
```


---

## 作者：EthanC_ (赞：0)

本题看似与树有关，其实是一道有关分类讨论的字符串模拟题。
### 思路：
本题可以分成三个部分：
- 当这个字符为 ` . ` 时，计算与该字符前面的人名同名的人数。
- 当这个字符为 ` , ` 或 ` : ` 时，增加人数。
- 否则，这就是一个人名。我们将当前人名增加字符即可。

### 代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s[1001];
string x;
int n,ans;
int main(){
	cin>>x;
    for(int i=0;i<x.length();++i){
		char c=x[i];
        if(c=='.'){//如果是字符.那么计算相同人数
            for(int i=0;i<n;++i){
				if(s[i]==s[n])ans++;
			}
            s[n--]="";
        }
        else if(c==','||c==':')n++;//增加人数
        else s[n]=s[n]+c;//增加字符
    }
    cout<<ans<<endl;
  	return 0;
}

```


---

## 作者：Rosmarinus (赞：0)

## 思路分析

看上去是一道树的难题。

但事实上不需要使用与树有关的数据结构。

我们发现，题目中的所有“不舒服”的情况都只会出现在一条树链上。

因此，我们可以使用一个栈，每一次遇到逗号或冒号就推入，遇到句号就弹出。

每次加入一个完整的单词后再栈中暴力查找有没有与其名字相同的人即可。

## AC 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s[600];
int main()
{
	string x;
	int n = 0, ans = 0;
	cin >> x;
    for(int i = 0; i < x.size(); i ++)
    {
		char ch = x[i];
        if(ch == '.')
        {
            for(int i = 0; i < n; i++)
			{
				if (s[i] == s[n]) ans ++;
			}
            s[n --] = "";
        }
        else if (ch == ',' || ch == ':') n ++;
        else s[n] = s[n] + ch;
    }
    cout << ans << endl;
    return 0;
}
```

---

