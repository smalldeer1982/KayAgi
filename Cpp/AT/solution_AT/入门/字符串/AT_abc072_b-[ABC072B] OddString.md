# [ABC072B] OddString

## 题目描述

给定一个由小写英文字母组成的字符串 $s$。请输出由字符串中从前往后数奇数位置的字符组成的新字符串。注意，字符串的第一个字符视为第 $1$ 个字符。

## 说明/提示

## 限制条件

- $s$ 的每个字符都是小写英文字母。
- $1 \leq |s| \leq 10^5$

## 样例解释 1

取第 $1$ 个字符 `a`，第 $3$ 个字符 `c`，第 $5$ 个字符 `d`，第 $7$ 个字符 `r`，得到 `acdr`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
atcoder```

### 输出

```
acdr```

## 样例 #2

### 输入

```
aaaa```

### 输出

```
aa```

## 样例 #3

### 输入

```
z```

### 输出

```
z```

## 样例 #4

### 输入

```
fukuokayamaguchi```

### 输出

```
fkoaaauh```

# 题解

## 作者：绝艺 (赞：1)

这道题其实可以边读入边输出
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	char c;
	int i=0;
	while(cin>>c){
		i++;
		if(i%2==1) cout<<c;
	}
	cout<<endl;
	return 0;
} 
```


---

## 作者：PC_DOS (赞：1)

本题的要求是:

> 给定一个字符串，输出所有索引号为奇数的位置上的字符。

唯一需要注意的地方在于，此处字符串第一个字符的索引号为1。

C++的标准库提供了string库，该库实现了一个类型安全的字符串类并重载了相关运算符，同时提供了大量函数，可以轻松实现可变长度字符串的处理。但是请注意: string中第一个字符的索引号为0

代码:

```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInput; //输入的字符串
	int i; //循环计数器
	cin >> sInput; //读入
	for (i = 0; i < sInput.length(); i+=2){ //枚举奇数位置，注意由于string中第一个字符的索引号为0，因此题目的奇数位事实上是字符串中索引号为偶数的位置
		cout << sInput[i]; //输出对应位置的字符，注意string中第一个字符的索引号为0
	}
	cout << endl; //换行
	return 0; //结束
}
```

---

## 作者：A_Plus_Gu (赞：0)

考察内容：**字符串**

思路：
- **1.输入**
- **2.输出所有索引号为奇数的位置上的字符**

代码如下：

```
#include<iostream>
#include<string>
using namespace std;
int main(){
	string s;
	cin>>s;//输入
	for(int i=0;i<s.length();i++){
		if(i%2==0) cout<<s[i];//输出奇数位置上的字符
        //因为这里是从索引号为0开始扫的，奇数-1=偶数，所以输出所有索引号为偶数的位置上的字符，而不是奇数
	}
	cout<<endl;//AT的题要换行！（别忘了）
	return 0;
}
```


---

## 作者：qiukaichen (赞：0)

由于题目要求输出奇数位上的数，那么只要循环判断就行了。但由于循环位数时要从0开始，所以判断变成了偶数。未理解的同学看下面：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;//定义字符串
	long long i;//定义循环的变量，也可当做下标
	cin>>s;//输入字符串
	for(i=0;i<s.length();i++)//从0开始循环，小于字符串长度
	{
		if(i%2==0)因为从0开始，所以0作为第一位，以此类推奇数位为偶数
		{
			cout<<s[i];输出这个位上的字符
		}
	}
	return 0;结束
}
```
收工撒花

---

## 作者：WKAHPM (赞：0)

如题，输出奇数位上的字母即可AC

注意字符串下标是从0开始的！

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100010];
int main()
{    
    gets(s);
    for(int i=0;i<strlen(s);i+=2)//输出奇数位
    {
    	printf("%c",s[i]);
	}
	printf("\n");//记得换行
	return 0;
}

```


---

## 作者：Jinyeke (赞：0)

### 题目：给定一个字符串，输出所有索引号为奇数的位置上的字符。
就判断下奇偶就ok了呀，以下为代码（pascal）
```pascal
var
 s:string;
 i:longint;
begin
 read(s);
 for i:=1 to length(s) do //一个一个找过去
  if i mod 2=1 then write(s[i]);//是奇数就直接输出
 writeln;//AT大坑，换行输出！
end.
```
#### 共建文明洛谷，请勿Ctrl+C！

---

## 作者：Palind_Rome (赞：0)

这道题说遇奇则输出，那就可以在读入时输出咯？

动下脑子发现贼简单
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int i=0;
    char ch;
    while(cin>>ch){
        i++;
        if(i%2!=0)cout<<ch;
    }
    return 0;
}
```

---

