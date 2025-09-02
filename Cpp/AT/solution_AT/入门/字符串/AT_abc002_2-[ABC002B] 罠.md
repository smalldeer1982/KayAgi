# [ABC002B] 罠

## 题目描述

在神明恩赐下积累财富的高桥君，没想到竟落入了陷阱。
神明将他话语中的所有元音字母 `a`、`i`、`u`、`e`、`o` 尽数偷走。
现在给定一个字符串 $W$ 表示高桥君原本的话语，请编写程序，输出周围人实际听到的内容。

## 说明/提示

对于所有数据，$W$ 的长度 $|W|$ 满足 $1\le|W|\le30$。

## 样例 #1

### 输入

```
chokudai
```

### 输出

```
chkd
```

## 样例 #2

### 输入

```
okanemochi
```

### 输出

```
knmch
```

## 样例 #3

### 输入

```
aoki
```

### 输出

```
k
```

## 样例 #4

### 输入

```
mazushii
```

### 输出

```
mzsh
```

# 题解

## 作者：ivyjiao (赞：7)

~~7 行写完，果然是大水题。~~

不用字符串的做法：每次读入一个字符，如果这个字符不是 $a,e,i,o,u$ 中的一个，就输出。记得最后要输出换行。

```cpp
#include<iostream>
using namespace std;
char c;
int main(){
    while(cin>>c) if(c!='a'&&c!='e'&&c!='i'&&c!='o'&&c!='u') cout<<c;
    cout<<endl;
}

```


---

## 作者：Macrohard (赞：2)

##AT783 【罠】
字符串水题，直接模拟处理即可。
上C代码：
```
#include<stdio.h>//头文件哇
#include<string.h>//头文件哇
int main(void)//完美的main函数
{
    char a[100000];//存字符串
    fgets(stdin,a,100000);
    //注意：由于在C11gets函数被移除了，所以我使用等价的fgets来处理
    //但是fgets在AtCoder上无法使用
    //所以你在提交测评的时候要使用gets(a)
    int l=strlen(a);//先计算长度，节省时间
    for(int i=0;i<l;i++)
    {//遍历处理
        if(a[i]!='a'&&a[i]!='e'&&a[i]!='i'&&a[i]!='o'&&a[i]!='u')
        printf("%c",a[i]);//处理现场
    }
    puts("");//回车保险
    return 0;//结束
}
```

---

## 作者：_Qer (赞：2)

题意：给定一个字符串，去掉其中的元音字母（ _a,e,i,o,u_ ）后输出。

用一个while循环，每次输入一个字符，判断是否是元音，若不是则输出，输出最后加上一个换行。（~~水~~

```cpp
#include<bits/stdc++.h>
using namespace std;
char c;//字符（一次只能读入一个字符）
int main(){
    while(cin>>c){//一直输入知道程序结束
        if(c!='a'&&c!='e'&&c!='i'&&c!='o'&&c!='u'){
            cout<<c;//若不为元音则输出，否则不管了
        }
    }
    cout<<endl;//换行保平安
    return 0;
}
```

---

## 作者：Soyilieber (赞：0)

方法：一个一个字符边输入，边比较

代码如下：
```pascal
var
    s:string;
    ch:char;
begin
    while not eoln do//输入循环
        begin
            read(ch);//读1个字符
            if (ch<>'a')and(ch<>'e')and(ch<>'i')and(ch<>'o')and(ch<>'u') then s:=s+ch;//不为aeiou则往s里拉
        end;
    writeln(s);//PRINT
end.
```

---

## 作者：LJC00111 (赞：0)

又是水题
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    char a[100000];
    gets(a);
    int len=strlen(a);
    for(int i=0;i<len;i++)
    {
    	if(a[i]!='a'&&a[i]!='e'&&a[i]!='i'&&a[i]!='o'&&a[i]!='u')
    	cout<<a[i];
	}
	cout<<endl;
	return 0;
}
```

---

