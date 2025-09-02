# 帰ってきた器物損壊！高橋君

## 题目描述

[problemUrl]: https://atcoder.jp/contests/language-test-ver1/tasks/test001_b

 高橋君はある日、コンピューターのキーボードの中の $ 1 $ つのキーが壊れていることに気づきました。  
 壊れたキーは押しても文字が出力されません。  
 力が強いことで有名な高橋君なので、キーを強く叩きすぎたのでしょう。  
 しかし、高橋君は小さいことは気にしない性格なので、そのキーボードを壊れたまま使うことにしました。  
 高橋君がタイピングする文字列が与えられるので、壊れたキーボードを用いてタイピングした場合の出力結果を答えなさい。 入力は以下の形式で標準入力から与えられる。

> $ X $ $ s $

- 入力は $ 2 $ 行ある。
- $ 1 $ 行目には、壊れたキーを表す文字 $ X $ が与えられる。 
  - $ X $ は英字の小文字(`a-z`)のいずれかである。
- $ 2 $ 行目にはタイピングする文字列を表す $ 1 $ 文字以上 $ 50 $ 文字以下の文字列が与えられる。 
  - 文字列は英語の小文字(`a-z`)のみで成り立っている。

 壊れたキーでの入力は出力されない状態で文字列をタイピングした場合に、出力される文字列を標準出力に $ 1 $ 行で出力せよ。  
 なお、最後には改行を出力せよ。  
 もし何も出力されない場合は改行のみを出力せよ。 ```

a
abcdefgabcdefg
```

 ```

bcdefgbcdefg
```

- $ 1 $ 文字目と $ 8 $ 文字目に含まれる `a` の文字が出力されないので、bcdefgbcdefgが答えになります。
 
```

g
aassddffgg
```

 ```

aassddff
```

- 最後の `g` が $ 2 $ 文字出力されません。
 
```

a
aaaaa
```

 ```


```

- 何も表示されない場合は改行のみ出力します。
 
```

l
qwertyuiopasdfghjklzxcvbnm
```

 ```

qwertyuiopasdfghjkzxcvbnm
```


```

d
qwsdtgcszddddsdfgvbbnj
```

 ```

qwstgcszsfgvbbnj
```

# 题解

## 作者：loceaner (赞：4)

众所周知，岛国水题一大堆，今天我又来刷水题了

首先这个题的确很简单，很好做！

但是

**坑点太多了！**


1. 你知道要先输入字符再输入字符串吗?

2. 你知道岛国的题目一定要换行吗？

### 知道就可以做了qwq

很简单的一道字符串题，先输入字符再输入字符串，然后for循环判断字符串中的元素是不是和输入字符相同，若相同就不输出，否则就输出

例如我们输入了

**a   kkkjassa**

则在for循环中一个一个判断，发现字符串的第5个元素是a，就不输出，后面的那个元素一样

所以就这样吧，上我的代码

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
char a;

int main() {
	cin>>a>>s;
	for(int i=0; i<s.length(); i++) {
		if(s[i]!=a) {
			cout<<s[i];
		}
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：LJC00111 (赞：3)

一道纯字符串的题，仅需将首先输入的字符从后面的字符串中删除
```cpp
#include<bits/stdc++.h>
using namespace std;
char a,b[100];
int main()
{
	cin>>a;
	getchar();
	scanf("%s",b);
	int len=strlen(b);
	for(int i=0;i<len;i++)
	if(b[i]!=a)
	cout<<b[i];
	cout<<endl;
    return 0;
}
```

---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题十分简单，但是我们要注意：要先读入字符，再读入字符串，然后将字符串的每一位逐一枚举，如果当前要输出的字符的按键没坏，就输出当前字符，否则不输出。

在思路这块，最后写上：AT不换行，爆零两行泪。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    char a;//定义字符
    string st1;//定义字符串
    int ll;//定义存储字符串长度的变量
    int main()
    {
        cin>>a>>st1;//读入字符和字符串
        ll=st1.size();//存储字符串长度
        for(int i=0; i<ll; i++)//从字符串的第零位找起
        {
            if(a!=st1[i])cout<<st1[i];//如果这个字符的按键没坏，输出
            else continue;//否则继续
        }
        cout<<endl;//AT题记得换行
        return 0;//要有好习惯
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。
    

---

## 作者：GaltonLai (赞：0)

**水题一个**

读入字符串和字符，然后根据你所输入的字符来操作字符串（删除字符串中你输入的字符），然后输出就行了

**PS：AtCoder的题目要换行，否则就GG了**

不加cout的下场：

![WA](https://picabstract-preview-ftn.weiyun.com/ftn_pic_abs_v3/469fb10e5dfcb416914a1bcf3eb1edb131fbb2a6b02fdb2821cf250cd9b862c9b3d7432bd690c521ef05d6b1368189a3?pictype=scale&from=30113&version=3.3.3.3&uin=2462433690&fname=WA.png&size=750)

~~好吧，别扯远话题~~

代码就是这样子：

```cpp
#include <iostream> //懒得用头文件（滑稽）
#include <cstdio>
#include <cstring>
#include <string> 
using namespace std;
string s;
char c;
int main()
{
	cin >> c >> s;
	int sl = s.length();
	for (int i = 0;i < sl;i++)
	{
		if (s[i] == c) continue; //continue大法
		cout << s[i];
	}
	cout << endl; //注意！
	return 0;
}
```


---

## 作者：二字 (赞：0)

# 最短代码

### 本题其实不需要while(cin>>s)这样的东西因为数据全都是一个字符串，但这题坑点很多，只要不被坑基本AC稳稳的

下面贴代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	char x;
	cin>>x>>s;////坑点1！先输入字符再输入字符串！
	for(int i=0;i<s.length();i++) if(s[i]!=x) cout<<s[i];//坑点2！x不是'x'！ 
	cout<<endl;//坑点3！岛国题要换行！ 
	return 0; 
} 
```

是不是很简短？

---

## 作者：不到前10不改名 (赞：0)

```
发现楼上两位大佬都没写注释呢~那我来吧！
#include<stdio.h>
#include<string.h>
char s[1001];
int main()
{
    char x; 
    scanf("%c",&x);
    scanf("%s",s);
    for(int i=0;i<strlen(s);i++)
    {if(s[i]==x)//判断是否是坏的，是的话就删，不是就输出
    continue;//breakwa祭...   
    else
    printf("%c",s[i]);}
    printf("\n");//不要把回车打里面了！
    return 0;
}
```

---

## 作者：刘柏辰 (赞：0)

```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int main()
{	
    char a,g[101];
	scanf("%c",&a);
	scanf("%s",&g);
	for(int i=0;i<strlen(g);i++)
	{
		if(g[i]==a)
		continue;//相当于把它删除（跳过）
		else
		cout<<g[i];//输出修改过的字符串
	}
	puts("");//注意题目要求
}
```

---

## 作者：Jinyeke (赞：0)

### 题目：给出一个字符串 a与破掉的按键b。请输出a除去b后的新字符串
这题for+判断=输出呀，废话不多说，解释题解中，以下为代码（pascal）
```pascal
var
 a,t:string;
 b:char;
 i:longint;
begin
 readln(b);//输入一个字符
 read(a);//输入一个字符串
 for i:=1 to length(a) do
  if a[i]<>b then t:=t+a[i];//判断需要按的那个键有没有坏，没坏就加到字符串t里
 writeln(t);//输出t
end.
 
```
## 共建文明洛谷，请勿Ctrl+C！### 

---

## 作者：源氏可以吃吗 (赞：0)

### 这道题确实很水
其实只要学过字符串~~都能够做出来~~的

只要有一个循环+判断就行了
### 不过还是有坑点
1. 不能直接用scanf("%s",),因为有个空格
2. 岛国文字真难懂，其实不只是b，a-z中输入的字符
3. 必须要换行
### 下面直接粘题解
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
char x;
int main()
{
	cin>>x>>a;
    int len=a.length();//取字符串长度 
    for(int i=1;i<len;i++)//循环 
    {
    	if(a[i]!=x)//判断 
    	cout<<a[i]; 
	}
	printf("\n");//这里必须要换行 
	return 0;
}
```
我知道很水但就让我过了吧@管理员大人

---

