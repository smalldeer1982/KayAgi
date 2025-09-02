# [ABC070A] Palindromic Number

## 题目描述

给定一个 $3$ 位的正整数 $N$。  
请判断 $N$ 是否为回文数。  
回文数是指在十进制下，将数字反转后与原数相同的数。

## 说明/提示

## 限制条件

- $100 \leq N \leq 999$
- $N$ 是整数

## 样例解释 1

$N=575$，将数字反转后仍为 $575$，因此是回文数。所以输出 `Yes`。

## 样例解释 2

$N=123$，将数字反转后为 $321$，不是回文数，因此输出 `No`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
575```

### 输出

```
Yes```

## 样例 #2

### 输入

```
123```

### 输出

```
No```

## 样例 #3

### 输入

```
812```

### 输出

```
No```

# 题解

## 作者：据设错了 (赞：1)

很多人都认为这道题用字符串比用数字简单，易懂，容易......其实，只要尝试一下，就会发现：其实~~数字比字符串更简单~~数字和字符串一样简单，大家用字符串的原因就是可以直接判断a[0]和a[2]，但是数字也可以直接判断a%10和a/100啊，~~所以说，不要被表面蒙蔽了双眼~~

下面贴代码：
```
//简的不能再简的代码
#include<bits/stdc++.h>//万能头
using namespace std;
int n;
int main()
{
    cin>>n;
    if(n/100==n%10)cout<<"Yes";//判断百位和各位是否相等
    else cout<<"No";
	return 0;//好习惯
}
```
第n次(n<=3)次发题解，~~然而并没有一次过的QWQ~~就给过了吧

---

## 作者：CZQ_King (赞：1)

## 见人都发字符串的，我就来发数字的吧
###### ~~难题一道~~
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
long long a;//其实应该用int的
int main(){
    cin>>a;//输入这个三位数
    if(a%10==(a-a%100)/100)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;//判断并输出
    //并没有写return 0;
}
```

---

## 作者：RioBlu (赞：0)

看大佬都没发python2题解

# ~~我来水一发~~
```
a=""
a=raw_input()
if a[0]==a[2]:
    print "Yes"
else:
    print "No"
```

---

## 作者：xyn0901 (赞：0)

这题也太水了吧，直接字符串就能过好吗

```pascal
var s:string;
begin
readln(s);
if s[1]=s[3] then writeln('Yes') 
else writeln('No');
end.
```

---

## 作者：da32s1da (赞：0)

与AT3703相似。。

不过这个只有3位，判断一下第一位与第三位是否相同即可
```
#include<bits/stdc++.h>
using namespace std;
char s[10];
int main(){
    cin>>s;
    if(s[0]==s[2]) puts("Yes");//判断，相同为Yes
    else puts("No");//不同为No
}
```

---

## 作者：durbin中将 (赞：0)

用字符串来处理就很方便了
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;//定义这个数
	cin>>a;//输入这个数
	if(a[0]==a[2]) cout<<"Yes"<<endl;//如果第一个元素和第三个元素（百位和个位）相同，就是“Yes”
	else cout<<"No"<<endl;//反之输出"No"
	return 0;//结束
}
```

---

## 作者：qwq2003 (赞：0)

我们来看题目说明。
![Luogu](https://cdn.luogu.com.cn/upload/pic/25055.png) 

~~请忽略掉左下角的水印谢谢~~

这道题的难点在需要分离个位和百位上的数字进行比较。

上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main()
{
    int a,b,c;
    int sum;
    cin>>sum;           //输入数据
    a=sum%10; //得到个位数
    sum=sum/10;
    b=sum%10; //得到十位数
    c=sum/10; //得到百位数
    if(c==a)            //最后的判断
    {
    	cout<<"Yes"<<endl;
    }
    else
    {
    	cout<<"No"<<endl;
	}
	return 0;           //结束程序
}
```

我们来分析一下分离各位数字的程序部分，复习一下运算符：



四则运算：加法（+）减法（-）乘法（*）除法（/）

其他：求余数（%）  


sum（int类型）为150；
a,b,c三个变量均为int类型。

    a = sum%10;   
    
    %是求余数的对不，150可以被10整除
    （不信的自己算去），得到0（sum不变），就是sum的值150的个位。将这个数赋值给a。
    sum = sum/10;
    这条语句将sum÷10的值赋值给sum。因为150÷10=15，所
    以执行完这条语句后sum的值为15.
    
    b = sum%10;
    
    之前提到过%是求余的，现在sum的值是15，所以15÷10=1......5，得到5（sum不变），将这个数赋值给b
    。
    c=sum/10;
    
    现在sum的值为15，这条语句可以理解为15÷10=1.5，这个运算会得到1.5。
    出现小数了！重点来了啊！如果试图将小数赋给int类型的变量时，
    这个小数将舍掉小数点和小数点后面的所有数字。
    1.5赋值给int类型的c变量，最终c的值为1。
    
    到此我们已经成功的把150分离各位数并存入变量。
    本期题解到此结束。
    
    

---

## 作者：封禁用户 (赞：0)

首先，我首先想到的是字符串：
```pascal
var
    s:string[3];//这个节约空间的习惯要养成，不然NOIP会MLE的（别问我是怎么知道的…(:ｪ)|￣|＿）
    i:longint;
begin
    readln(s);
    if(s[1]=s[3])then writeln('Yes')
    else writeln('No'); 
end.

```
别告诉我你不懂
可我担心萌新不懂（虽说我也是）就改成了简单易懂的

# 字符# 
代码如下：
```pascal

    var
    s:array[1..3]of char;//其实就是s:string[3]的双胞胎
    i:longint;
begin
    for i:=1 to 3 do
    begin
        read(s[i]);//输入
    end;
    if(s[1]=s[3])then writeln('Yes')//判断输出
    else writeln('No'); 
end.

```

---

