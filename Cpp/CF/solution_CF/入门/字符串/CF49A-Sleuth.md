# Sleuth

## 题目描述

Vasya plays the sleuth with his friends. The rules of the game are as follows: those who play for the first time, that is Vasya is the sleuth, he should investigate a "crime" and find out what is happening. He can ask any questions whatsoever that can be answered with "Yes" or "No". All the rest agree beforehand to answer the questions like that: if the question’s last letter is a vowel, they answer "Yes" and if the last letter is a consonant, they answer "No". Of course, the sleuth knows nothing about it and his task is to understand that.

Unfortunately, Vasya is not very smart. After 5 hours of endless stupid questions everybody except Vasya got bored. That’s why Vasya’s friends ask you to write a program that would give answers instead of them.

The English alphabet vowels are: A, E, I, O, U, Y

The English alphabet consonants are: B, C, D, F, G, H, J, K, L, M, N, P, Q, R, S, T, V, W, X, Z



## 样例 #1

### 输入

```
Is it a melon?
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
Is it an apple?
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
  Is     it a banana ?
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
Is   it an apple  and a  banana   simultaneouSLY?
```

### 输出

```
YES
```

# 题解

## 作者：松毛虫 (赞：7)

弱弱的问一句，为什么大家的题解的代码都这么长（逃）
```cpp
#include<iostream>
using namespace std;
int i=0;
int main()
{
	char c[100];
	while(cin>>c[i])
	{
		i++;//循环测出字符串的长度
	}
		if(c[i-2]=='A'||c[i-2]=='O'||c[i-2]=='U'||c[i-2]=='Y'||c[i-2]=='I'||c[i-2]=='E'||c[i-2]=='a'||c[i-2]=='o'||c[i-2]=='u'||c[i-2]=='y'||c[i-2]=='i'||c[i-2]=='e')//臃肿的判断
		cout<<"YES";
		else cout<<"NO";
	return 0;
 } 
```



---

## 作者：char32_t (赞：5)

# 题解 CF49A 【Sleuth】

------------

一道简单的字符测试题


字符测试函数`isalpha()`<-判断一个字符是否为英文字母


```cpp
#include<cstdio>
#include<ctype.h>//字符测试函数头文件
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
string str;
int main() {
    getline(cin, str);//因为句中有空格，所以用getline()读入数据
    int len=str.length()-1;
    while(!isalpha(str[len])) len--;//获得倒数第一个字母的下标
    if(str[len]=='A'||str[len]=='E'||str[len]=='I'||str[len]=='O'||str[len]=='U'||str[len]=='Y'||str[len]=='a'||str[len]=='e'||str[len]=='i'||str[len]=='o'||str[len]=='u'||str[len]=='y') printf("YES");//判断是否为元音字母
    else printf("NO");
    return 0;
}
```

---

## 作者：Higashikata_Jousuke (赞：1)

这道题其实挺水的吧，考点大概是对于字符的判断吧。。。
## 大概思路
   _**输入后倒序检查字符串，如果是英文字符就判断是否是元音，如果不是英文字符，就检查下一个**_ 
   
具体看代码和注释
## 代码
```
#include<cstdio>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;
char a[105];
int main()
{
    gets(a);//可以输入空格 
    for(int i=strlen(a);i>=0;i--)
        if(a[i]>='A'&&a[i]<='Z'||a[i]>='a'&&a[i]<='z')//确保要进行判断元音的最后一个字符是英文字符,如果不是,就下一个 
            {
             	if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u'||a[i]=='y'||a[i]=='A'||a[i]=='E'||a[i]=='I'||a[i]=='O'||a[i]=='U'||a[i]=='Y')
             	{
             		cout<<"YES";
             		break;
             		//一找到元音字符就输出 YES ,然后结束 
                }
             	else 
                {
                    cout<<"NO";
                    break;
                    //否则就无法满足最后是元音,输出 NO ,结束 
                }
            }
    return 0;
}
```
如有误欢迎私信骚扰，谢谢支持

---

## 作者：我是蒟弱 (赞：1)

思路：

1.输入**带空格的**字符串

2.处理，全**变成小写**

3.**删除无用**字符

4.**判断最后一位**是不是元音

上代码【C++】
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string a;
inline void tolower(){//手写tolower函数，因为中间可以加删除操作
	for(register int i=0;i<a.length();i++){//循环判断
		if(a[i]>='A'&&a[i]<='Z'){//大写字母
			a[i]=a[i]-'A'+'a';//转成小写
		}
		if(a[i]<'a'||a[i]>'z'){//不是字母，如：空格、标点等
			a=a.erase(i,1);//删除
			i--;//不减会跳字符，漏循环
		}
	}
}
int main(){
	getline(cin,a);//输入带空格的字符串
	tolower();//进行转小写+删除操作
	if(a[a.length()-1]=='a'||a[a.length()-1]=='e'||a[a.length()-1]=='i'||a[a.length()-1]=='o'||a[a.length()-1]=='u'||a[a.length()-1]=='y'){//判断末位是否为元音
		printf("YES");//是，输出YES
	}else{
		printf("NO");//否则，输出NO
	}
	return 0;//结束
}
```

---

## 作者：不到前10不改名 (赞：0)

//这种破水题一次都没过，我太弱了...怪不得pj凉了
```
#include<stdio.h>
#include<string.h>
int i;
char srx[101];
int main()
{
    gets(srx);//虽说有空格，但是为什么要用getline呢？？？好不容易有个不卡gets的233...qwq
    for(i=strlen(srx)-1;i>=0;i--)//反向寻找才是最后一个，道理不解释
    {if(srx[i]>=65&&srx[i]<=90||srx[i]>=97&&srx[i]<=122)//根据ASCII码值确定是否是字母（一开始居然加错了...）也可以写为srx[i]>='a'&&srx[i]<='z'一类的，和今年pj第一题没什么大区别（除了数字）
    {if(srx[i]=='a'||srx[i]=='e'||srx[i]=='i'||srx[i]=='o'||srx[i]=='u'||srx[i]=='y'||srx[i]=='A'||srx[i]=='E'||srx[i]=='I'||srx[i]=='O'||srx[i]=='U'||srx[i]=='Y')//判断是否为元音字母
    printf("YES");
    else
    printf("NO");//辅音字母
    break;}}//退出
    return 0;
    }
//日常QAQ
```

---

## 作者：DreamShadow (赞：0)

【先敲个黑板】，咳咳，我开讲咯：

     1.你先找准倒数第一个字符：
     for(i=n,i>=1,i--);或for i:=n downto 1 do
     2.找到以后（那么）把他给拦下来，记录位置
     3.把知道的位置上的字符弄下来
     4.判断是不是元音
     5.搞定


```pascal
var
s,st:string;
i:longint;
j:char;
 begin
   for j:='A' to 'Z' do
   st:=st+j;//把所有大写字母枚举出来，并记录
   readln(s);
   s:=upcase(s);//统一换成大写（或者小写)
   i:=length(s);//最后一位
   while pos(s[i],st)=0 do //如果不符合条件
     dec(i);//一直减

      if s[i] in['A','E','I','O','U','Y'] THEN writeln('YES') else writeln('NO');//因为是大写，所以不必判断是不是小写字符
 end.

```

---

## 作者：Chthology (赞：0)

~~这题好水呀，于是先卖个萌QAQAQ~~

C++ ctype里的`isalpha`似乎大多数题解都提到了，~~那就不讲了~~

然而ctype里还有一些~~玄学鬼畜~~有趣的函数：`tolower`和`toupper`

`tolower`把字母字符转小写，`toupper`反之

于是就不用判最后一个字母是大写还是小写了QwQ

那么，代码如下:
```
#pragma once //每个库只引用一次，用bits最好加这个，少用好多空间QwQ

#include<bits/stdc++.h>
using namespace std;

string s;

int main(){
	getline(cin,s);
	int i=s.size()-1;
	for(;!isalpha(s[i]);--i);
	s[i]=tolower(s[i]);
	if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'||s[i]=='y') puts("YES");
	else puts("NO");
}
```

---

## 作者：温情 (赞：0)

看到之前的题解都是读进一个字符串然后从最后一位开始找最后一个英文字母判断...介绍一种不需要数组的方法

思路是一个个字符读就好了.读到文件结尾(EOF)时就退出.

每次读到的英文字母如果是元音字母就把标记置为true,该字母是**当前的**(也可能是整个字符串的)最后一个英文字母

相反,如果读到的是一个英文字母而且不是元音字母就把标记置为false,该字母也可能是**当前的**(或者是整个字符串的)最后一个英文字母.

相比开数组省了点空间~.

算是优化了一下空间复杂度吧.

~~虽然入门的题几乎全都不需要去考虑优化这个2333.~~

代码如下:

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	char ch;
	bool flag=false;                //记得置为false,因为可能出现输入没有任何英文字母的情况.
	while((ch=getchar())!=EOF)
	{
		if(ch=='A'||ch=='a'||ch=='E'||ch=='e'||ch=='I'||ch=='i'||ch=='O'||ch=='o'||ch=='U'||ch=='u'||ch=='V'||ch=='v'||ch=='Y'||ch=='y')
			flag=true;
		else if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))
			flag=false;
	}
	if(flag)
		cout<<"YES";
	else
		cout<<"NO";
	return 0;
}
```

---

## 作者：Andysun06 (赞：0)

# CF49A 【Sleuth】题解


------------
## 注意：问号前面可能有多个空格！！
#### pascal题解：
    var a,b,i:longint;
        s,x:string;//不用太大，string够了
    begin
    readln(s);//输入字符串s
    i:=length(s)-1;//最后一个一定是‘？’所以可以-1
     while (s[i-b]='?')or(s[i-b]=' ')do//一直检测到是字母
     begin
      b:=b+1;//不是就加1
     end;
     if ((s[i-b]='a')or(s[i-b]='A')or(s[i-b]='e')or(s[i-b]='E')or(s[i-b]='i')or(s[i-b]='I')or(s[i-b]='o')or(s[i-b]='O')or(s[i-b]='u')or(s[i-b]='U')or(s[i-b]='y')or(s[i-b]='Y')) then//判断是否是元音
    writeln('YES')//是，输出YES（要大写）
    else
     writeln('NO');//否，输出NO（要大写）
    end.


---

## 作者：panda_wang (赞：0)

# 【题意】

### 要求读入一个字符串，判断最后一个字母是否为元音字母

### 元音字母：A,E,I,O,U,Y


# 【解决方案】

### 使用语言：Python3

### 解决方法：从末位读起，一直读到最前面一位（我会在【题目分析】中讲到），判断是否为元音字母

### 代码：


```Python3
s = input()
c = len(s)-1
fr1 = c

for fr1 in range(c,-1,-1):
    if (s[fr1].upper()=='A' or s[fr1].upper()=='E' or s[fr1].upper()=='I' or s[fr1].upper()=='O' or s[fr1].upper()=='U'or s[fr1].upper()=='Y'):
        print("YES")
        exit()
    elif (s[fr1].isalpha()):
        print("NO")
        exit()
```

# 【题目分析】

### 1.为什么是一直读到最前面一位？

### 1.答：我们不妨先假设一个字符串：

```cpp
a   ?
```
### 1.如果此时我们不读到最前一位，程序肯定会输出NO！题目说是读到最后一个字母，而上面的字符串则只有一个字母，所以a就是最后一个字母了。


# 【坑点分析】

### 1.c的长度：由于在Python里面的len函数会多算一位的（和C++的XXX.length()不同），所以必须要减一

### 2.if语句：题目里说是所有的字母，所以当然包括大写和小写字母。那就要使用Python的内置函数：XXX.upper()来把小写换成大写，大写不变。

### 3.elif语句：这里万万不可用else！！！因为，当用else时就只会判断末位了（因为末位不是字母），而末位常常是标点符号，所以会输出NO！

# 【函数分析】

### 1.XXX.upper():

###     把一个字符串的某一位转换成大写字母，如不是字母，返回空字符，若是小写字母，返回该小写字母的大写，大写字母返回原字符

### 1.案例：

```Python3
s = "panda_wanG"
print(s[0].upper())
print(s[5].upper())
print(s[9].upper())
```
### 1.分别输出：

### P
### \_
### G

---

## 作者：_Qer (赞：0)

- 看这题没有人发题解唉


- ~~自己偷偷来水一发贡献~~


- 挺水的一题


- 我不熟字符串的函数，就随便搞了一下


- 先输入一行字符，往后一直找到最后一个


- 然后在这个基础上往前找，知道发现一个字母


- 最后判断一下该字符是否是元音

```cpp
  
#include<string>    
#include<cstring>    
#include<iostream>  
using namespace std;   
char s[110];   
int main(){   
    cin.getline(s,110);//输入一行字符   
    int l=0;//长度   
    while(s[l]!=0){//找到最后一个字符   
        ++l;   
    }  
    while(s[l]<'A'||s[l]>'z'||(s[l]>'Z'&&s[l]<'a')){  
        --l;//往前找，知道发现一个字母   
    }   
       if(s[l]=='A'||s[l]=='a'||s[l]=='E'||s[l]=='e'||s[l]=='I'||s[l]=='i'||s[l]=='O'||s[l]=='o'||s[l]=='U'||s[l]=='u'||s[l]=='Y'||s[l]=='y'){  
        cout<<"YES";//这里的条件我都压到一行了，有点乱   
    }else{  
        cout<<"NO";  
    }  
    return 0;  
}  
   
```

- OK啦，是不是很简单？


---

## 作者：蒟蒻wyx (赞：0)

思路很简单:


从后往前找第一个字母


看是不是元音


```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    string  s;
    getline(cin,s);//整行输入
    for(int i=s.length();i>=0;i--){
        if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))    //从后往前找第一个字母
            if(    s[i]=='a'|| //判断元音
                s[i]=='e'||
                s[i]=='i'||
                s[i]=='o'||
                s[i]=='u'||
                s[i]=='y'||
                s[i]=='A'||
                s[i]=='E'||
                s[i]=='I'||
                s[i]=='O'||
                s[i]=='U'||
                s[i]=='Y'
                ){
                cout<<"YES\n";
                return 0;
            } 
        else{
            cout<<"NO\n";
            return 0;
        }
    } 
    cout<<"NO\n";//若无字母
    return 0;
}
```

---

## 作者：Playnext (赞：0)

一道模拟题。 题意求字符串**最后一个字母是否属于“元音”**。


直接按题意进行**模拟**即可。


------------


代码：


```cpp
#include <bits/stdc++.h>
#define REG register
using namespace std;    //BY Playnext

string T1;

AN bool Check (REG int Num) {    //一个一个检查
    if (T1[Num] == 'A' || T1[Num] == 'E' || T1[Num] == 'I' || T1[Num] == 'O' || T1[Num] == 'U' || T1[Num] == 'Y')
        return 1;
    if (T1[Num] == 'a' || T1[Num] == 'e' || T1[Num] == 'i' || T1[Num] == 'o' || T1[Num] == 'u' || T1[Num] == 'y')
        return 1;        
    return 0;
}


int main () {
    getline (cin, T1);            //读入一整行
    for (REG int i = T1.size () - 1; i >= 0 ; i--)        //逆序检查
        if (isalpha (T1[i])) {        //判断是否是字母
            if (Check (i))        //判断是否是“元音”
                puts ("YES");
            else
                puts ("NO");    //找到后直接退出
            return 0;    
        }
    puts ("NO");
    return 0;            
}
```

---

