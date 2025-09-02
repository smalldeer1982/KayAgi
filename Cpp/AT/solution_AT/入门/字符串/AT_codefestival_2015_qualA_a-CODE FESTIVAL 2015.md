# CODE FESTIVAL 2015

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-quala/tasks/codefestival_2015_qualA_a

このコンテストの名前は`CODE FESTIVAL 2015`です。

しかし、高橋君はいつも`CODE FESTIVAL 2014`というように年度を間違えてしまいます。

そこで高橋君は、文字列の末尾の`2014`を`2015`に書き換えるソフトを作ろうと思いました。

末尾が`2014`である文字列 $ S $ が与えられます。文字列 $ S $ の末尾の`2014`を`2015`に書き換えた文字列を出力してください。

## 样例 #1

### 输入

```
CODEFESTIVAL2014```

### 输出

```
CODEFESTIVAL2015```

## 样例 #2

### 输入

```
CHOKUDAI2014```

### 输出

```
CHOKUDAI2015```

# 题解

## 作者：_Qer (赞：2)

题意：给定一个以2014结尾的字符串，把最后的2014改为2015后输出。

可以用一个string存输入的字符串，以L代表其长度，输出前L-1个字符，因为最后一个字符是4，而我们要将它改为5，所以我们不用输出4，直接在后面输出5即可。

____

```cpp
#include<bits/stdc++.h>
using namespace std;
string c;//输入的字符串
int main(){
    cin>>c;
    for(int i=0;i<c.length()-1;++i){//循环到第L-1个
        cout<<c[i];//输出其中第i个字符
        //其实string类型就算一个数组，所以可以使用下标来访问元素
    }
    cout<<5<<endl;//结尾放一个5
    return 0;
}
```

---

## 作者：char32_t (赞：1)

# 题解 AT1507 【CODE FESTIVAL 2015】
------------
~~哇一道红题竟然WA两次~~

题意：将字符串的最后一位改为`5`

刚开始想的是用转义字符`\b`退掉`4`再输出一个`5`，然后打出了代码：
```cpp
#include<cstdio>
int a[10010];//字符数组 
int main(){
	scanf("%s", a);//读入字符串 
	printf("%s\b5", a);//输出字符串 
	return 0;
}
```
在本机上测试后结果也没有问题，然后信心满满地提交

$\color{red}WA$

然后突然想起没有加换行保平安，于是加上之后又交了一次

$\color{red}WA$

~~啊啊啊啊啊啊啊啊啊啊啊啊绝望~~

然后在luoguIDE上试了一下，终于发现了问题所在——

样例#1的输出是这个：`CODEFESTIVAL20145`(懒得截图了，可以自己把代码复制上去看看)

所以就换了一种方式：读入字符串后，将字符串输出到倒数第二位时停止，再输出`5`，然后换行保平安

code：
```cpp
#include<cstdio>
#include<cstring>
char a[10010];//字符数组 
int main(){
    scanf("%s", a);//读入字符串 
    int len=strlen(a)-2;
    for(int i=0; i<=len; i++) printf("%c", a[i]);//输出到倒数第二个字符 
    printf("5\n");//输出5 
    return 0;
}
```
路漫漫其修远兮，吾将上下而求索。还有很多东西需要学习啊。

PS:一道红题写了这么长还真不容易呢

---

