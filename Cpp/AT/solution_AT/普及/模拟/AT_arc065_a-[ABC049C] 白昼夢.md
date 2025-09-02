# [ABC049C] 白昼夢

## 题目描述

# 题目大意
输入一个以英文小写字母组成的字符串S，规定一个空的字符串T，现在你可对字符串T进行你喜欢的操作，问是否能让字符串T变为字符串S？

**喜欢的操作如下 ：**

在字符串T的末尾加入
“dream”或“dreamer”或“erase”或“eraser”。

------------

## 样例 #1

### 输入

```
erasedream```

### 输出

```
YES```

## 样例 #2

### 输入

```
dreameraser```

### 输出

```
YES```

## 样例 #3

### 输入

```
dreamerer```

### 输出

```
NO```

# 题解

## 作者：赤霞QvQ (赞：5)

# 做法：只要读到d或e就判断是不是dream,dreamer,erase,eraser中的一个
###### 注意：dreamer与erase会首尾重叠！！大坑。所以读到d的时候还要分分类。上代码！BGM！
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	char a[101000];
    long long k,m,n;
    cin>>a;
    n=strlen(a);
    for(int i=0;i<n;i++)
    {
        if(a[i]=='e')       //读到e就判断
        {
            if(a[i+1]=='r'&&a[i+2]=='a'&&a[i+3]=='s'&&a[i+4]=='e')       //erase或eraser
            {
                if(a[i+5]=='r')       //eraser
                {
                    i+=5;
                }
                else          //erase
                {
                    i+=4;
                }
            }
        }
        else if(a[i]=='d')         //读到d就判断
        {
            if(a[i+1]=='r'&&a[i+2]=='e'&&a[i+3]=='a'&&a[i+4]=='m')    //dream还是dreamer还是dreamerase还是dreameraser
            {
                if(a[i+5]=='e'&&a[i+6]=='r'&&a[i+7]=='a'&&a[i+8]=='s'&&a[i+9]=='e')        //dreamerase
                {
                    i+=4;
                }
                else
				{
				    if(a[i+5]=='e'&&a[i+6]=='r')      //排除完就只剩dreamer
				    {
                        i+=6;
                    }
                    else
                    {
                        i+=4;
                    }
                }
            }
        }
        else     //如果以上都不是，说明挂了，直接输出NO就好了
        {
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;
    return 0;        //完美结束
}
```
###### 总结：不难，就是有点坑！求过！！！！！

---

## 作者：ACE_ZY (赞：2)

超级模拟(Pas):

```pascal
var
  s:ansistring;
  p:boolean;
  l:longint;
begin
  readln(s);
  while true do//一直循环,反正while循环里会跳出的
  begin
    if s='' then begin writeln('YES');exit;end;//判断s字符串是否为空,为空就退出
    p:=false;//每次做都得重置p
    if length(s)<5 then begin writeln('NO');exit;end;//如果字符串小于5就可以直接退出了
    l:=length(s);//计算出s的长度
    if (s[l]='m') and (s[l-1]='a') and (s[l-2]='e') and (s[l-3]='r') and (s[l-4]='d') then begin delete(s,l-4,5);p:=true;end;//第1个判断
    if s='' then begin writeln('YES');exit;end;
    l:=length(s);//必须重新计算,否则会出错
    if (s[l]='r') and (s[l-1]='e') and (s[l-2]='m') and (s[l-3]='a') and (s[l-4]='e') and (s[l-5]='r') and (s[l-6]='d') then begin delete(s,l-6,7);p:=true;end;//第2个判断
    if s='' then begin writeln('YES');exit;end;
    l:=length(s);
    if (s[l]='e') and (s[l-1]='s') and (s[l-2]='a') and (s[l-3]='r') and (s[l-4]='e') then begin delete(s,l-4,5);p:=true;end;//第3个判断
    if s='' then begin writeln('YES');exit;end;
    l:=length(s);
    if (s[l]='r') and (s[l-1]='e') and (s[l-2]='s') and (s[l-3]='a') and (s[l-4]='r') and (s[l-5]='e') then begin delete(s,l-5,6);p:=true;end;//第4个判断
    if s='' then begin writeln('YES');exit;end;
    l:=length(s);
    if p=false then begin writeln('NO');exit;end;//如果一个都没做,就可以直接退出了
  end;
end.

```


---

## 作者：勘探员·引魂人 (赞：1)

**前言：啊啊啊！我居然只拿了个部份分！**

**思路：先截取从后往前截取，若截取到"dream"、"erase"、"eraser"、"dreamer"，输出YES,否则输出NO**

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>//文件头你好，文件头再见
using namespace std;
string st;//定义字符串
int i;//这玩意儿记录字符串长度
int main()
{
    cin>>st;//输入字符串
    i=st.size();//记录长度
    if(st.substr(i-5,i)=="dream"||st.substr(i-5,i)=="erase"||st.substr(i-6,i)=="eraser"||st.substr(i-7,i)=="dreamer") cout<<"YES";//开始截取，若截取到"dream"、"erase"、"eraser"、"dreamer"，输出YES
    else cout<<"NO";//否则输出NO
    
    return 0;
}
```

---

