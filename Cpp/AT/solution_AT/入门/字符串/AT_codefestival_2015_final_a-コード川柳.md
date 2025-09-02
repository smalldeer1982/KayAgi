# コード川柳

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-final-open/tasks/codefestival_2015_final_a

コード川柳コーナーでは、プロコンに関する「あるある」を五七五の調べに乗せた川柳を募集しています。

そこで、高橋君はコード川柳コーナーに投稿する川柳を作りました。

高橋君が作った川柳が五七五になっているかどうかをチェックするプログラムを作成してください。

ただし五七五になっている川柳とは、$ 5 $ 文字、$ 7 $ 文字、$ 5 $ 文字の文字列をこの順に並べたものを指すこととします。

## 说明/提示

### Sample Explanation 1

川柳としては素晴らしい作品ですが、この問題においては五七五になっていません。

## 样例 #1

### 输入

```
using namespace std```

### 输出

```
invalid```

## 样例 #2

### 输入

```
using namespa cestd```

### 输出

```
valid```

# 题解

## 作者：封禁用户 (赞：2)

这道题@da32s1da 已经给出了翻译，应该都能懂题意。

你们最喜欢的环节来了，附**AC代码：**
```cpp
#include<iostream>
using namespace std;
int main()
{
    string a,b,c;
    cin>>a>>b>>c;
    if(a.size()==5 && b.size()==7 && c.size()==5)//xx.size意思是获取长度
    {
        cout<<"valid"<<endl;
    }
    else
    {
        cout<<"invalid"<<endl;
    }
    return 0;//AT题换行！
}
```

---

## 作者：TRZ_2007 (赞：1)

## 这是一道水题！
- 1：三个字符串长度都小于十。
- 2：只要求三个字符串的长度。
- 3：时间复杂度：$O(1)$，空间复杂度：$O(n)$  
### 以上这三个原因造成了为什么称他是水题的原因。
## 上代码$qwq$
```
#include <stdio.h>//stdio库，匹配scanf和printf。
#include <string.h>//string库，匹配strlen函数。
int main()
{
    char a[11],b[11],c[11];//长度都不超过10
    scanf("%s",a);
    scanf("%s",b);
    scanf("%s",c);//三个读入
    if(strlen(a)==5&&strlen(b)==7&&strlen(c)==5)//根据题意判断
    {
        printf("valid\n");
        return 0;//return 0防止输出两行答案。
    }
    printf("invalid\n");//AT题目要换行！
}//完美收场2333（防伪标记
```

---

## 作者：CZQ_King (赞：1)

# ~~这题真水~~

------------
做法：只需逐个判断三个字符串的长度是否为$5,7,5$是的话输出$valid$，否则输出$invalid$。
#### 用的问号运算符

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a,b,c;//3个就够了
int main(){
	cin>>a>>b>>c;
	a=(a.length()==5&&b.length()==7&&c.length()==5)?"valid\n":"invalid\n";//直接用a，不浪费
	cout<<a;//就不输出回车
	return 0;//结束
}
```

---

## 作者：wushuang0828 (赞：0)

莫名羡慕c++，Pascal只能把一行输完在来pos

题目水，直接上代码：
```pascal
var
 x,y:longint;
 s:string;
begin
 readln(s);//输入
 x:=pos(' ',s);//查找第一个单词的结尾后面的空格在第几位
 delete(s,1,x);//删除第一个单词以及后面的空格
 y:=pos(' ',s);//查找第二个单词的结尾后面的空格在第几位
 delete(s,1,y);//删除第二个单词以及后面的空格
 dec(x);//长度要减一，因为包含了空格
 dec(y);//长度要减一，因为包含了空格
 if (x=5) and (y=7) and (length(s)=5) then writeln('valid')
                                      else writeln('invalid');//判断三个单词的长度依次是不是5，7，5，是就输出valid，否则输出invalid
end.
```

---

