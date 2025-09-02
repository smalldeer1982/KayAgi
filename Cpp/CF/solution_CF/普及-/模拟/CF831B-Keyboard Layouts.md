# Keyboard Layouts

## 题目描述

There are two popular keyboard layouts in Berland, they differ only in letters positions. All the other keys are the same. In Berland they use alphabet with $ 26 $ letters which coincides with English alphabet.

You are given two strings consisting of $ 26 $ distinct letters each: all keys of the first and the second layouts in the same order.

You are also given some text consisting of small and capital English letters and digits. It is known that it was typed in the first layout, but the writer intended to type it in the second layout. Print the text if the same keys were pressed in the second layout.

Since all keys but letters are the same in both layouts, the capitalization of the letters should remain the same, as well as all other characters.

## 样例 #1

### 输入

```
qwertyuiopasdfghjklzxcvbnm
veamhjsgqocnrbfxdtwkylupzi
TwccpQZAvb2017
```

### 输出

```
HelloVKCup2017
```

## 样例 #2

### 输入

```
mnbvcxzlkjhgfdsapoiuytrewq
asdfghjklqwertyuiopzxcvbnm
7abaCABAABAcaba7
```

### 输出

```
7uduGUDUUDUgudu7
```

# 题解

## 作者：Eason_AC (赞：2)

## Content
给你 $26$ 个字母的映射（都是小写，大写的映射方式相同），再给你一个字符串 $s$，求它的映射结果（如果有非字母的字符保持不变）。

**数据范围：$1\leqslant |s|\leqslant 1000$。**
## Solution
强大的 $\texttt{map}$ 正好能够为我们做出映射的功能，我们直接存储每个字母的映射再直接将原字符串映射即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>
#include <map>
using namespace std;

string a, b, c;
map<char, char> mm;

int main() {
	cin >> a >> b;
	int len = a.size();
	for(int i = 0; i < len; ++i) mm[a[i]] = b[i], mm[a[i] - 32] = b[i] - 32;
	cin >> c;
	len = c.size();
	for(int i = 0; i < len; ++i)
		if((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z'))
			c[i] = mm[c[i]];
	cout << c;
	return 0;
}

```

---

## 作者：Arghariza (赞：0)

开个大小 $26$ 的 $mp$ 数组存储 $a$ 到 $z$ 键的值，然后输出的时候逐一访问键值就行了。（为了节省空间就用了$字符-a$的方法，结果一开始转换大写的时候手贱把 $-32$ 打成了 $+32$ /kk）

当然还要特判一下大小写。


```
#include <bits/stdc++.h>
#define maxn 1001
using namespace std;

int n;
char s1[26], s2[26], mp[26], s3[maxn];

int main() {
	cin >> s1 >> s2 >> s3;
	n = strlen(s3);// 获取长度
	for (int i = 0; i < 26; i++) {// 记录每对键值
		mp[s1[i] - 'a'] = s2[i];
	}
	for (int i = 0; i < n; i++) {
		int f = 0;
		if (s3[i] >= 'A' && s3[i] <= 'Z') f = 1;// 特判大写
		if ((s3[i] >= 'a' && s3[i] <= 'z') || f == 1) {
			if (f == 1) cout << (char)(mp[s3[i] - 'A'] - 32);// 从小写转字母换成大写字母
			else cout << (char)mp[s3[i] - 'a'];// 如果是小写字母就正常输出
		} else cout << s3[i];// 如果不是字母就照常输出
	}
	return 0;
}
```

---

## 作者：MC小萌新 (赞：0)


## 铺垫知识

[ASCII码](https://tool.oschina.net/commons?type=4)


## 题目分析

康了这道题之后，发现有一点点像之前提高组 NOIP 的一道题。

[P1079 Vigenère 密码](https://www.luogu.com.cn/problem/P1079)



不过不同的是，这道题是直接给出了每一个小写字母映射后的结果。

对于这道题，我们可以利用字母的 ASCII 码来解决。

我们知道，如果把一个 char 类型的东西转化 int 类型，会变为 ASCII 码的形式。

而字母的 ASCII 值最多就 $ 100 $ 多，我们可以直接把这个当做下标，定义一个 char 类型数组，存储每一个字母对应的映射关系。

在输出时，只需判断当前要映射字符 $ c $ 为小写字母、大写字母还是其他字符就好了。


## 代码实现
```cpp
#include <iostream>
using namespace std;
char s[300],c;
string a,b;
int main(){
    cin>>a>>b;
    for(int i=0;i<=25;++i){
        s[a[i]]=b[i];
    }
    while(cin>>c){
        if(c>='a' && c<='z')
            cout<<s[c];
        else if(c>='A' && c<='Z')
            cout<<(char)(s[c-'A'+'a']-'a'+'A');
        else
            cout<<c;
    }
    return 0;
}
```

---

## 作者：TLMPEX (赞：0)

思路：模拟，注意大小写，主要思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
string a,b,c;
int main(){
	int l,i,j;
	cin>>a>>b>>c;
	l=c.size();
	for(i=0;i<l;i++){
		if(c[i]>='0'&&c[i]<='9')cout<<c[i];
		else if(c[i]>='a'&&c[i]<='z'){
			for(j=0;j<26;j++)
				if(c[i]==a[j]){
					cout<<b[j];
					break;
				}
		}
		else if(c[i]>='A'&&c[i]<='Z'){
			c[i]+=32;
			for(j=0;j<26;j++)
				if(c[i]==a[j]){
					cout<<char(b[j]-32);
					break;
				}
		}
	}
}
```


---

## 作者：peppaking8 (赞：0)

## 思路：

这是一道简单的字符串题。

首先输入两个字符串表示映射关系，就直接记录以下就好了。设 ```to[i]``` 表示字符 ```i``` 对应的字符，所以说可以这样写代码：
```cpp
for(int i=0;i<strlen(a);i++){
	to[a[i]]=b[i];
}
```
但是注意到**需要处理大写字符**，所以说：
```cpp
for(int i=0;i<strlen(a);i++){
	to[a[i]]=b[i];
    to[a[i]-'a'+'A']=b[i]-'a'+'A';
}
```
这样的话，比如输入的字符串其中一位是 ```a``` 和 ```g```，那么对应的代码就是 ```to['a']='g',to['A']='G'```。

好了，这样映射关系也就做完了。接下来输入最后一个字符串，需要**将其转化为映射后的字符串**。而且还要判断每一位**是否为大写字母或小写字母**。判断的函数是这样的：
```cpp
bool is_alpha(char x){
	if(x>='A'&&x<='Z') return true;
    if(x>='a'&&x<='z') return true;
    return false;
}	
```
然后，如果 ```is_alpha()``` 返回值为 ```true```，则输出 ```to[x]``` 即可；否则，当作其他字符进行处理，**输出本身**。

## CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[30],b[30],c[1005];
int to[30];
int main(){
	scanf("%s\n%s\n%s",a,b,c);
	int lena=strlen(a);
	int lenc=strlen(c);
	for(int i=0;i<lena;i++){
		to[a[i]]=b[i];
		to[a[i]-'a'+'A']=b[i]-'a'+'A';//处理小写和大写字符的映射关系
	}
	for(int i=0;i<lenc;i++){
		if(c[i]>='a'&&c[i]<='z') printf("%c",to[c[i]]);
		else if(c[i]>='A'&&c[i]<='Z') printf("%c",to[c[i]]);
        //前两个判断是is_alpha()函数，如果符合就输出to[]
		else printf("%c",c[i]);
        //否则就是其他字符，输出本身即可
	}
	printf("\n");//输出换行，好习惯qwq
	exit(0);//及时退出，好习惯qwq
}
```
写题解不容易，看完记得点个赞哦~~

---

## 作者：Nortrom (赞：0)

# 字符串处理题
~~其实这是一道水题~~，主要考察字符串的处理。

------------
分析：

其实这题扫一遍就行了，一遍过，难点主要在字符串的处理。

关于字符串处理：

分类，一类是小写字母处理，另一类是大写字母处理，查找的时候可以先把被搜索的字母小写化，然后按第一类处理，最后转大写。
说明如下：

如果是小写字母处理如下：逐个字母对应比较，当找到对应小写字母后**返回值并退出循环**。
```cpp
	if(a[i]==zm[j])//找到时
	{	
    		a[i]=zmx[j];
		break;//一定要退出，否则会错
	}
```
如果是大写字母处理如下：先转换为小写字母查找，逐个字母对应比较，当找到对应小写字母转换为大写字母后，**返回值并退出循环**。其中a[i]=zmx[j]-'a'+'A';是将结果转化为大写
```cpp
a[i]=a[i]-'A'+'a';//转换为小写字母
for(int j=0;j<26;j++)//查找
	if(a[i]==zm[j])
	{
		a[i]=zmx[j]-'a'+'A';//再转化为大写
		break;//一定要退出，否则会错
	}
```
完整过程如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>//strlen的头文件
using namespace std;
char zm[30],zmx[30],a[1010];
int l;
int main()
{
	scanf("%s",zm);//输入
	scanf("%s",zmx);		
	scanf("%s",a);
	l=strlen(a);//测长
	for(int i=0;i<l;i++)
	{
		if(a[i]>='a' && a[i]<='z')//如果是小写字母处理如下
		{
			for(int j=0;j<26;j++)//查找
				if(a[i]==zm[j])
				{
					a[i]=zmx[j];
					break;//一定要退出，否则会错
				}
		}
		else 
		if(a[i]>='A' && a[i]<='Z')//如果是大写字母处理如下
		{
			a[i]=a[i]-'A'+'a';//转换为小写字母
			for(int j=0;j<26;j++)//查找
				if(a[i]==zm[j])
				{
					a[i]=zmx[j]-'a'+'A';//再转化为大写
					break;//一定要退出，否则会错
				}
		}
	}
	printf("%s",a);//输出
	return 0;
}
```
简单来说，就是找到对应字母处理，但只限于**小数据**，防止超时。


------------

拒绝通过抄题解方式刷题，珍惜每一次测评机会。

---

## 作者：codemap (赞：0)

本蒟蒻用了一种不需要用大小写转换函数或map的无脑做法

做法:

用一个char数组记录字母的映射(下标1到26表示小写,27到52表示大写)

然后只要把最后一个的字符串按照这个数组输出即可

上代码
```cpp
#include<iostream>
using namespace std;
int main()
{
	string a,b,c;
	char d[1000];
	int i;
	cin>>a>>b>>c;
	for(i=0;i<26;i++)
	{
		d[a[i]-'a'+1]=b[i];//映射
		d[a[i]-'a'+1+26]=(char)(b[i]-32);//大写映射(小写到大写ASCII码要-32)
	}
	for(i=0;i<c.size();i++)
	{
		if(c[i]<='z'&&c[i]>='a')//如果是小写
			cout<<d[c[i]-'a'+1];//输出对应映射
		else if(c[i]<='Z'&&c[i]>='A')//如果是大写
			cout<<d[c[i]-'A'+1+26];//输出对应映射
		else//如果不是字母
			cout<<c[i];//直接输出
	}
	return 0;//完美结束
}
```
# 请勿抄袭

---

## 作者：Rainbow_qwq (赞：0)

[原题链接](https://www.luogu.org/problemnew/show/CF831B)

## 一道模拟题。

**思路：**

比较简单吧，用一个$t$数组记录$26$个字母的映射,具体如下。

注意$char$类型也能做数组下标哦~
```cpp
char s1[30],s2[30],s[1010],t[300];
//s1,s2,s是输入的字符串
cin>>s1>>s2>>s;
for(int i=0;i<26;i++)
	t[s1[i]]=s2[i];
```
然后是转换输入字符串的部分。

注意有大小写，还有其他字符(~~坑人~~)，但是只要转换大小写字母就行了。

具体见代码与注释：
```cpp
for(int i=0;s[i];i++)
//一个小技巧，可以遍历字符串
{
	if(isupper(s[i]))s[i]=t[s[i]+32]-32;
    	//大写字母，要减32
	else if(islower(s[i]))s[i]=t[s[i]];
    	//小写字母，直接映射
	cout<<s[i];//输出。
}
```
最后是完整**AC 代码**：(大家不要抄袭哦)
```cpp
#include<bits/stdc++.h>
using namespace std;
char s1[30],s2[30],s[1010],t[300];
int main()
{
    ios::sync_with_stdio(0);//cin的优化
    cin>>s1>>s2>>s;
    for(int i=0;i<26;i++)
        t[s1[i]]=s2[i];
    for(int i=0;s[i];i++)
    {
        if(isupper(s[i]))s[i]=t[s[i]+32]-32;
        else if(islower(s[i]))s[i]=t[s[i]];
        cout<<s[i];
    }
    return 0;
}
```

---

## 作者：Erusel (赞：0)

#### 题目大意：给你26个字母的映射（均为小写），再给你一串长度不大于1000的字符串，要你输出它的映射结果。 （其他符号如数字不变）

因为是映射，同时字符串长度才1000，直接用map进行求解。

将原字符串的字符映射到map里。

### 注意大写还是大写，数字还是数字。

代码：

```cpp
//This is by Robinzh

#include<bits/stdc++.h>

using namespace std;

string s;
string s1,s2;
map<char,char>m;//定义map

int main()
{
    cin>>s1>>s2;
    for(int i=0;i<26;i++)m[s1[i]]=s2[i];//将字符映射
    for(char c='A';c<='Z';c++)m[c]=m[c-'A'+'a']-'a'+'A';//处理大写字符
    for(char c='0';c<='9';c++)m[c]=c;//处理数字
    cin>>s;
    int l=s.length();
    for(int i=0;i<l;i++)cout<<m[s[i]];//输出
    cout<<endl;
    
    return 0;
}
```
题目难度不高，主要考察STL。

---

