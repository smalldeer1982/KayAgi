# [ABC048A] AtCoder *** Contest

## 题目描述

すぬけ君打算举办一个名为 AtCoder $s$ Contest 的比赛。这里，$s$ 是一个长度不少于 $1$ 的字符串，第一个字符为英文大写字母，第二个及以后的字符为英文小写字母。

すぬけ君决定将这个比赛的简称定为 A$x$C。这里，$x$ 是 $s$ 的首字母（即英文大写字母）。

给定比赛的名称，请输出该比赛的简称。

## 说明/提示

### 限制条件

- $s$ 的长度不少于 $1$，不超过 $100$。
- $s$ 的第一个字符为英文大写字母。
- $s$ 的第二个及以后的字符为英文小写字母。

### 样例解释 1

这是你正在参加的比赛。

### 样例解释 2

这个比赛并不存在。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
AtCoder Beginner Contest```

### 输出

```
ABC```

## 样例 #2

### 输入

```
AtCoder Snuke Contest```

### 输出

```
ASC```

## 样例 #3

### 输入

```
AtCoder X Contest```

### 输出

```
AXC```

# 题解

## 作者：Develop (赞：2)

输入三个字符串，再输出第一个字符。

用scanf的%s就可以读取一行字符串，遇到空格停止；

然后再输出第一个字符

要注意的是，当下次再用%s读入字符串时

scanf会跳过空格直接读下一个字符

如果有两个空格scanf会读取到空字符串

所以这里不用处理空格啦~

新手练习字符串的话可以做一做~

代码

```cpp
#include <stdio.h>
#include <math.h>
#include <string.h>
int main(){
	char a[20000];
	scanf("%s",a);       printf("%c",a[0]);
    scanf("%s",a);       printf("%c",a[0]);
    scanf("%s",a);       printf("%c",a[0]);
	return 0;
}
```

---

## 作者：CZQ_King (赞：1)

## 题意：输入三个字符串，求这三个字符串的首字母并输出。
#### ~~感谢[@ 一条小鱼](https://www.luogu.org/space/show?uid=95436)的隐藏~~
为什么$dalao$们都用$for$读入呢，难道是因为$dalao$们很~~懒~~吗
###### 用了一行输入和输出（可能是最短的了）
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a,b,c;
int main(){
    cin>>a>>b>>c;//输入这三个单词（好像是字符串）
    cout<<a[0]<<b[0]<<c[0]<<endl;//输出第一位
    return 0;//完美结束
}
```

---

## 作者：Obito (赞：0)

这题很水的，题目大概意思是：输入几个单词，输出他们的第一个字母
所以：只要把字符串第一个字母输出，再每遇到一个空格，就输出后面一个字母就行了
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	getline(cin,s);//输入
	cout<<s[0];//输出第一个
	for(int i=1;i<s.size();i++)//遇到空格输出
	if(s[i]==' ')cout<<s[i+1];
	return 0;//完美结束
}

```


---

## 作者：Rbu_nas (赞：0)

首先感谢管理们百忙之中抽出时间审核这篇题解qwq

题目描述：读入三个字符串输出它们的首字母

思路：这道题的难点就是含空格字符串的输入输出，遇到空格输出下一位就好了。

代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[105];//长度100保险
int main()
{
	ios::sync_with_stdio(false);	//关闭流同步不解释
	gets(a);	//这里用gets()是因为cin,scanf读取到空格会停止
	int len=strlen(a);
	cout<<a[0];	//第一个字母一定是第一句话首字母
	for(int i=1; i<len; i++)
		if(a[i]==' ')	//判断遇到空格输出下一位即首字母
			cout<<a[i+1];
	cout<<endl;
	return 0;
}
```

这道题思路还是比较易懂的就不用copy了吧。

---

## 作者：封禁用户 (赞：0)

 题意看讨论。                       
很简单，不解释上代码：
```pascal
var
    s:string;//定义字符串
    i,j:longint;
begin
    readln(s);
    writeln('A',s[pos(' ',s)+1],'C'); //我翻译里没说，输出的第一个字母一定是A，第三个一定是C
end.                    ↑            
                     查找输出
```

---

