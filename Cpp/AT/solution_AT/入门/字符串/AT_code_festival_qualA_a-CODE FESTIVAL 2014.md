# CODE FESTIVAL 2014

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-quala/tasks/code_festival_qualA_a

このコンテスト名は、`CODE FESTIVAL 2014`です。

しかし、物覚えが悪い高橋君は、いつも、`2014`を付け忘れてしまいます。

そこで、高橋君は、文字列に自動的に`2014`を付け加えるソフトを作ろうと思いました。

文字列 $ S $ が与えられます。文字列 $ S $ に、`2014`を付け加えた文字列を出力してください。

なお、半角スペースなどを付ける必要はありません。

## 说明/提示

### Sample Explanation 1

`CODEFESTIVAL`に`2014`を付けると、`CODEFESTIVAL2014`になります。入力にスペース等が与えられることはありません。

## 样例 #1

### 输入

```
CODEFESTIVAL```

### 输出

```
CODEFESTIVAL2014```

## 样例 #2

### 输入

```
CHOKUDAI```

### 输出

```
CHOKUDAI2014```

# 题解

## 作者：陈洋琛 (赞：2)

题目大意：输入一个字符串，然后输出它，并且在它的末尾输出2014

献上代码：
~~~
#include <iostream>
using namespace std;
int main()
{
    string s;
    cin>>s; //输入字符串
    cout<<s<<"2014"<<endl; //输出这个字符串并且输出2014，之后换行
    return 0; //结束程序
}
~~~

---

## 作者：hzq18 (赞：0)

~~论如何冲刺最短代码~~  
输入一个字符串并输出，再输出2014并换行即可。  
# 献上代码:
```cpp
#include <iostream>
using namespace std;
string a;
int main(){return (cin>>a,cout<<a<<2014<<endl)&&0;}
```

---

## 作者：Soyilieber (赞：0)

输入一个字符串，再输出它+‘2014’。
pascal做法：
```
var
    s:string;
begin
    readln(s);
    writeln(s,2014);
end.
```

---

## 作者：_Qer (赞：0)

题意：输入一个字符串，输出这个字符串且末尾加上2014

char做法↓

```cpp
#include<bits/stdc++.h>
using namespace std;
char c;
int main(){
    while(cin>>c){//从键盘持续读入字符
    	cout<<c;//直接输出
    }
    cout<<2014<<endl;//最后加上2014（换行保平安）
    return 0;
}
```

---

