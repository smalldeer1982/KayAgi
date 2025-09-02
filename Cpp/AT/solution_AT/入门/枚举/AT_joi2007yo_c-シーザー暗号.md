# シーザー暗号

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2007yo/tasks/joi2007yo_c

ガイウス・ユリウス・カエサル（Gaius Julius Caesar)，英語読みでジュリアス・シーザー（Julius Caesar）は，古代ローマの軍人であり政治家である．カエサルは，秘密の手紙を書くときに，`A` を `D` に，`B` を `E` に，`C` を `F` に，というように $ 3 $ つずらして表記したという記録が残っている．

大文字のアルファベット $ 26 $ 文字だけからなる文字列を，カエサルがしたように3文字ずつずらす変換を施し得られた文字列がある．このような文字列を元の文字列に戻すプログラムを作成せよ．

各文字の変換前と変換後の対応は次のようになる．  
変換前 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z  
変換後 D E F G H I J K L M N O P Q R S T U V W X Y Z A B C

例えば，この方法で文字列 `JOI` を変換すると `MRL` が得られ，この方法で変換された文字列 `FURDWLD` の元の文字列は `CROATIA` である．

- - - - - -

## 说明/提示

### Sample Explanation 1

\- - - - - -

## 样例 #1

### 输入

```
MRL```

### 输出

```
JOI```

## 样例 #2

### 输入

```
FURDWLD```

### 输出

```
CROATIA```

# 题解

## 作者：Soyilieber (赞：1)

水题，就直接打表，把所有26种可能列出来。

```pascal
var
    a:char;
begin
    while not eof do//文件一直读取
        begin
            read(a);//读字符，以下打表
            if a='A' then write('X');
            if a='B' then write('Y');
            if a='C' then write('Z');
            if a='D' then write('A');
            if a='E' then write('B');
            if a='F' then write('C');
            if a='G' then write('D');
            if a='H' then write('E');
            if a='I' then write('F');
            if a='J' then write('G');
            if a='K' then write('H');
            if a='L' then write('I');
            if a='M' then write('J');
            if a='N' then write('K');
            if a='O' then write('L');
            if a='P' then write('M');
            if a='Q' then write('N');
            if a='R' then write('O');
            if a='S' then write('P');
            if a='T' then write('Q');
            if a='U' then write('R');
            if a='V' then write('S');
            if a='W' then write('T');
            if a='X' then write('U');
            if a='Y' then write('V');
            if a='Z' then write('W');
    end;
    WRITELN;//此处很重要一定要换行！！！
end.
```

---

## 作者：da32s1da (赞：1)

按照题意模拟即可。
```
#include<bits/stdc++.h>
using namespace std;
char a[1005];
int b;
int main(){
    cin>>a;b=strlen(a);
    for(int i=0;i^b;i++)
    a[i]>'C'?a[i]-=3:a[i]+=23;
    cout<<a<<endl;
    return 0;
}
```

---

## 作者：xyn0901 (赞：0)

这道题的意思其实就是把字符向后**倒退三步**
Pascal代码如下
```pascal
var s:ansistring;
l,i:longint;
begin
readln(s);
l:=length(s);
for i:=1 to l do
if ord(s[i])<=67 then s[i]:=chr(ord(s[i])+23) else s[i]:=chr(ord(s[i])-3);
writeln(s);//注意要换行，我卡了好久
end.
```


---

