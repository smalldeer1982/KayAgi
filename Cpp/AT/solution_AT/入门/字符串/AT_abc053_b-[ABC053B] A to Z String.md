# [ABC053B] A to Z String

## 题目描述

题目大意：
输入一个字符串s，问从第一个A到最后一个Z之间有多少个字母（含A和Z）（包括A和Z，如：UYEAERTZUY,就是UYE AERTZ UY,A到Z之间有5个字符。数据保证了开头是A的末尾是Z的部分一定存在的。）

## 样例 #1

### 输入

```
QWERTYASDFZXCV```

### 输出

```
5```

## 样例 #2

### 输入

```
ZABCZ```

### 输出

```
4```

## 样例 #3

### 输入

```
HASFJGHOGAKZZFEGA```

### 输出

```
12```

# 题解

## 作者：LW_h_FP (赞：3)

一道水题，只需要从最左找出A的位置，再从最右找出Z的位置
再输出z-a+1
```
#include<iostream>
#include<cstring>
using namespace std;

string a;

int main(){
    int left,right;
    cin>>a;
    for(int i=0;i<a.length();i++)
        if(a[i]=='A'){
            left=i;
            break;
        }
    for(int i=a.length()-1;i>=0;i--)
        if(a[i]=='Z'){
            right=i;
            break;
        }
    cout<<right-left+1<<endl;
    return 0; 
} 
```

---

## 作者：FCBM71 (赞：1)

题意已经表达的非常清楚了，找出第一个A和最后一个Z。所以我们就按照题目说的照做就行了。

思路，用两个变量来储存A和Z的位置(记为a和b吧).
 - 先从前往后遍历一边,只要找到一个Z,b就赋值为当前的Z的坐标，这样可以确保找到的是最后一个Z.
 - 再从后往前遍历一边,只要找到一个A,a就赋值为当前的A的坐标,这样也可以确保找到了第一个A.
 
最后，学过小学奥数的你应该知道这题的答案就是b-a+1
 
当然其实你用repeat(或while)也可以,前后各找一遍，找到后直接停，这里就不详细说明了

#### 上代码：

------------
```
program hrn;
 var
  s:string;
  l,a,b,i:longint;  //l代表字符串长度,a和b上面已经解释过了
 begin
  read(s); 
  l:=length(s);   //读入，计算长度
  for i:=1 to l do if s[i]='Z'then b:=i;  //找最后一个Z
  for i:=l downto 1 do if s[i]='A'then a:=i;  //找第一个A
  writeln(b-a+1);  //输出
 end.
```

---

## 作者：_newbie_ (赞：0)

```c
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    string a;
    cin>>a;
    int l,r;
    for(int i=0;i<a.size();i++)
    {
        if(a[i]=='A')  //从左向右找
        {
            l=i;
            break;
        } 		
    } 
    for(int i=a.size()-1;i>=0;i--)
    {
        if(a[i]=='Z')  //从右向左找
        {
            r=i;
            break;
        }
    }
    cout<<r-l+1<<endl;	//加上端头的1
    return 0;
}
```

---

## 作者：Jack_cjj (赞：0)

//这话必须说：前面某位的题解误导了我！

//此题记得找到最前一个A,最后一个Z,注意,找到了以后立刻退出！（否则不是最后一个）

上代码


------------
```pascal
var a:array[1..200000] of char;
i,j,k,l:longint;
begin
while not eoln do//判断是否换行
  begin
  k:=k+1;//新的读入方法
  read(a[k]);
  
  end;//有20万位，字符串存不下，所以用字符数组；



for i:=1 to k do if a[i]='A' then begin j:=i; break; end;//退出;
for i:=k downto 1 do if a[i]='Z' then begin k:=i;break;end;
writeln(k-j+1);//因为通过样例时间，需要+1

end.
```


---

## 作者：char32_t (赞：0)

# 题解 AT2297 【A to Z String】
------------
按照题意，找到第一个`A`和最后一个`Z`即可

code:
```cpp
#include<cstdio>
#include<cstring>
char c[210000];
int flag_b=-0x3f3f3f3f;//开始标志 
int flag_e;//结束标志 
int main() {
    scanf("%s", c);//读入字符串 
    for(int i=0; i<strlen(c); i++){
        if(c[i]=='A'&&flag_b==-0x3f3f3f3f) flag_b=i;//标出第一个A的位置 
        if(c[i]=='Z') flag_e=i;//标出最后一个Z的位置 
    }
    printf("%d", flag_e-flag_b+1);//输出结果 
    return 0;
}
```

---

## 作者：Soyilieber (赞：0)

看了下数据规模，那个s的绝对值是什么鬼，于是把数据开大，也不敢用字符串，不敢用ansistring，所以开char。

第一次看到这题，认为是从第一个A到第一个Z中的字母总数（包括一头一尾），于是写了

------------

```
var
    ans:longint;
    ch:char;
    cancount:boolean;
begin
    while not eof do
        begin
            read(ch);
            if ch='A' then cancount:=true;
            if ch='Z' then begin writeln(ans+1); halt; end;
            if cancount then inc(ans);
        end;
end.
```

------------
发现是假的。样例都过不了，后来仔细发现，是左数第一个A到右数第一个Z中的字母总数（包括一头一尾），所以改进了

------------
```pascal
var
    i,j,n:longint;
    ch:array[1..200000]of char;
begin
    while not eoln do//换行时停止读入
        begin
            inc(n);
            read(ch[n]);
        end;
    for i:=1 to n do if ch[i]='A' then break;
    for j:=n downto 1 do if ch[j]='Z' then break;
    writeln(j-i+1);
end.
```

---

