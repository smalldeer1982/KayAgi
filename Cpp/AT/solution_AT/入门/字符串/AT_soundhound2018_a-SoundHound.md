# SoundHound

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018/tasks/soundhound2018_a

kenkooooさんはSoundHound社で働いています。彼は会社の知名度を上げるため、SoundHoundに名前が似ている言葉を見つけてマーケティングを行うことにしました。手始めに、$ 2 $ 単語からなる言葉で、それぞれの単語の頭文字を順につなげると`SH`となるような単語を似ていると見なすことにしました。

あなたの仕事は、$ 2 $ 単語 $ X $ $ Y $ からなる言葉が与えられたとき、頭文字を順につなげると`SH`となるか判定することです。

## 说明/提示

### 制約

- 与えられる単語は英大文字からなる
- 単語の長さは $ 1 $ 以上 $ 10 $ 以下である

## 样例 #1

### 输入

```
SAINT HELENA```

### 输出

```
YES```

## 样例 #2

### 输入

```
SOUND HOUND```

### 输出

```
YES```

## 样例 #3

### 输入

```
SOUND SPIDER```

### 输出

```
NO```

## 样例 #4

### 输入

```
S H```

### 输出

```
YES```

## 样例 #5

### 输入

```
X Y```

### 输出

```
NO```

# 题解

## 作者：不到前10不改名 (赞：1)

at水题++
```
#include<stdio.h>
int main()
{
    char mzy[101],zjq[101];
    scanf("%s%s",mzy,zjq);//分行会吃gets（上次就被坑，但scanf就不会）
    if(mzy[0]=='S'&&zjq[0]=='H')//一开始认为是mzy【0】==‘H’&&zjq【0】==‘S’也可以，没想到~哎。。。
    printf("YES\n");
    else
    printf("NO\n");//不想吐槽回车及大写
}
```

---

## 作者：两年打铁 (赞：0)

这么~~难的~~一道题竟然没有人发题解。
题意是两个字符串首字母是不是S 和 H。
直接上代码



------------

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    char s1[11],s2[11];
    scanf("%s%s",s1,s2);
    if(s1[0]=='S'&&s2[0]=='H')cout<<"YES"<<endl;//直接判断首字母分别是不是S 和 H。
    else cout<<"NO"<<endl;
}
```


---

