# Vitaly and Strings

## 题目描述

Vitaly is a diligent student who never missed a lesson in his five years of studying in the university. He always does his homework on time and passes his exams in time.

During the last lesson the teacher has provided two strings $ s $ and $ t $ to Vitaly. The strings have the same length, they consist of lowercase English letters, string $ s $ is lexicographically smaller than string $ t $ . Vitaly wondered if there is such string that is lexicographically larger than string $ s $ and at the same is lexicographically smaller than string $ t $ . This string should also consist of lowercase English letters and have the length equal to the lengths of strings $ s $ and $ t $ .

Let's help Vitaly solve this easy problem!

## 说明/提示

String $ s=s_{1}s_{2}...\ s_{n} $ is said to be lexicographically smaller than $ t=t_{1}t_{2}...\ t_{n} $ , if there exists such $ i $ , that $ s_{1}=t_{1},s_{2}=t_{2},...\ s_{i-1}=t_{i-1},s_{i}<t_{i} $ .

## 样例 #1

### 输入

```
a
c
```

### 输出

```
b
```

## 样例 #2

### 输入

```
aaa
zzz
```

### 输出

```
kkk
```

## 样例 #3

### 输入

```
abcdefg
abcdefh
```

### 输出

```
No such string
```

# 题解

## 作者：引领天下 (赞：6)

安利一发C++

如楼下大佬所说，此题有SPJ

不过我只想说，是有No such string 这种情况的

所以需要判断

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s,t;
int i;
int main(void){
    cin>>s>>t;
    i=s.size()-1;
    s[i]++;//先加了再说
    if (s>=t)return !printf ("No such string");//判断，这是不是一个小于t的字符串（字典序）
    //在C++中，string类的比较就是比较字典序
    while(s[i]=='{')s[i]='a',s[--i]++;//求下一个字典序
    if (s>=t)return !printf ("No such string");//重要！还要再检查一遍！因为下一个字典序可能已经大于t了
    //#14
    cout<<s;
}
```

---

## 作者：Tarensev (赞：2)

由于这道题是spj，所以如果有这样的字符串就可以直接向前进一位

这里有一个很坑的点，猜猜看啊~

no such string？别傻了，我本来就考虑到了，结果我一直wa

举个栗子：

yzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

~~我一直在大喊z，装作睡觉的样子~~

看，如果向前进一位，结果就会变成这样：

azzzzzz{

所以我们需要加个特判

这里贴代码

```pas
var s,t:string;
    i,j:longint;
begin
 readln(s);
 readln(t);
 i:=length(s);
 s[i]:=chr(ord(s[i])+1);
 if s>=t then {如果不符合条件直接退出}
  begin
   writeln('No such string');
   exit;
  end;
 while s[i]='{' do{这就是我说的特判，因为ascii码小z的后继是大括号}
  begin
   s[i]:='a';
   i:=i-1;
   s[i]:=chr(ord(s[i])+1);{进位，之所以用while而不是if，是因为可能有很多个z}
  end;
 writeln(s);
end.
```

敢抄袭我就掐爆他的小脑袋

---

## 作者：B_lhx (赞：1)

[CF518A Vitaly and Strings](https://www.luogu.com.cn/problem/CF518A)
===

思路：本质和高精度加法很像，想象一个数字，$a$是1，$b$是2……$z$是26，也就是一个27进制的数，把这个数$+1$，也就是$+a$，就是答案啦，当人，得先特判不能的情况

```
#include <bits/stdc++.h>
using namespace std;
string s1,s2; //两个字符串
int main(){
cin>>s1>>s2;//输入
if(s1>=s2){//如果1比2大，就无法运算了
	cout<<"No such string";//输出
	return 0;//结束程序
}
s1[s1.size()-1]++;//+1
for(int i = s1.size()-1;i>=0;i--){//从后往前进位
	if(s1[i]>'z'){//如果超了
		s1[i]-='z'-'a'+1;//本位减去26
		if(i==0){//特判如果还要向前进位的情况
			cout<<"a";//输出a，就像十进制加法中的99+1=100而不是00
			continue;//结束循环
		}
		s1[i-1]++;//进位
	}else{
		break;//如果没法进位就跳出
	}
}
if(s1==s2){//如果+1了后一样就输出"No such string"
	cout<<"No such string";
	return 0;//结束程序
}
cout<<s1;//输出:)
return 0;
}

```


---

## 作者：Error_Eric (赞：0)

### 前言

python好难。

### 正文

这道题我们可以理解为26进制高精自加1的模板。

遇到高精度，我们有两种方式，第一种是其他题解中都在用的模拟高精度，另一种是用 python。

这里给出第二种方法的代码。

### Code

```python
a=input();b=input();da=db=0;ans=""
for ai in a: # 输入并进制转换
    da=da*26+ord(ai)-97
for bi in b:
    db=db*26+ord(bi)-97
if da+1==db: # 如果a+1就是b,显然不存在解
    print("No such string")
else :
    da=da+1
    if(da//(26**len(a))!=0): # 形如‘zzzz’的特判
        print("No such string")
    else :
        for i in range (1,len(a)+1):
            ans=ans+chr(da%(26**(len(a)-i+1))//(26**(len(a)-i))+97)
        print(ans)
    # 注意要补全前导0（前导'a'）
```


---

## 作者：BB2655 (赞：0)

**对字符串的处理**

在两个字符串之间查找一个符合题意的字符串，可以联想到数字

比如在数字$1081$和$1085$之间有哪几个数

显然为$1082,1803,1804$

值得注意的是，如果在$2019$和$2021$之间，需要考虑数的进位

那么形如$105999$的数，就要从最后一位开始，把所有$9$变成$0$，在找到不是$9$的数之后停止，并且把那个数$++$

------------

返回到字符串处理上

只要处理后的字符串之间有空隙，那么这之中任意一个都符合题意

否则$No\ such\ string$

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a,b;
	cin>>a>>b;  //输入两个字符串
	int n=a.length(),i=n-1;  //n为字符串长度
	while(a[i]=='z') a[i--]='a';  //进位思想
	a[i]++;  //最后一位不是'z'的
	if(a>=b) printf("No such string");  //判断是否有空格
	else cout<<a;
	return 0
}
```

---

## 作者：PC_DOS (赞：0)

这是一道字符串模拟题。

首先，我们需要理解字典序是什么？

>设想一本英语字典里的单词，何者在前何者在后？

>显然的做法是先按照第一个字母、以 a、b、c……z 的顺序排列；如果第一个字母一样，那么比较第二个、第三个乃至后面的字母。如果比到最后两个单词不一样长，那么把短者排在前。

字典序，是用于比较字符串"大小"的方法，它类似我们平常使用的字典：从第一个字母开始一个一个比较。A在B前，X在Y前；如果第一个字母相同，则比较第二个……以此类推。

本题只需要考虑一种简单的情况：对于长度为L的字符串S1和S2，先比较S1(0)和S2(0)的编码(例如ASCII或UNICODE等，此处比较的是ASCII编码)，若相等则比较S1(1)和S2(1)，若依旧相等则比较S1(2)和S2(2)……，以此类推。如果S1(0..L-1)和S2(0..L-1)均相等，则S1=S2；如果如果S1(0..D-1)和S2(0..D-1)均相等但是S1(D)和S2(D)不等(0<=D<=L-1)，那么对应位置编码较小的字符串的字典序小。

注意：一旦发现第一个不等的S1(D)和S2(D)，字典序就已经唯一确定，比较过程旋即终止，也就是说"AC"的字典必定大于"WA"的字典序。不严格地说，对于等长字符串，越靠前的字符，决定字典序的权重越高。

对于本题需要从后往前遍历字符串，处理两种情况:

1. 读取到字符'z'，此时需要将此位设为'a'，这是因为在26个英文字母中'z'没有后继字符，考虑字典序的比较方法，为了使字符串尽可能小，将此位置为'a'。

2. 如果发现非'z'的字符，则将该字符设为其后继字符，设置"找到"标志并退出循环，此时已经找到了第一个比第一个字符串大的字串。

循环结束后，如果"找到"标志没有被设置或者第一个比第一个字符串大的字串已经大于第二个字符串，这说明没有找到，否则已找到并输出。

代码:
```
#include <iostream>
#include <string>
using namespace std;
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInputMin, sInputMax; //输入的两个字符串，类似上下界
	int iLength; //长度
	register int i; //循环计数器
	bool IsFound = false; //"找到"标志，默认未找到
	cin >> sInputMin >> sInputMax; //读入
	iLength = sInputMin.length(); //保存长度
	for (i = iLength - 1; i >= 0; --i){ //倒序遍历下界字符串
		if (sInputMin[i] != 'z'){ //如果发现非'z'的字符，则将该字符设为其后继字符，设置"找到"标志并退出循环，此时已经找到了第一个比第一个字符串大的字串。
			IsFound = true; //设置"找到"标志
			++sInputMin[i]; //该字符设为其后继字符
			break; //退出循环
		}
		else{ //读取到字符'z'，此时需要将此位设为'a'，这是因为在26个英文字母中'z'没有后继字符，考虑字典序的比较方法，为了使字符串尽可能小，将此位置为'a'。
			sInputMin[i] = 'a'; //对应位置设为'a'
		}
	}
	if (!IsFound || sInputMax <= sInputMin) //如果"找到"标志没有被设置或者第一个比第一个字符串大的字串已经大于第二个字符串，这说明没有找到
		cout << "No such string"; //提示未找到
	else //否则
		cout << sInputMin; //输出
	return 0; //结束
}
```

---

