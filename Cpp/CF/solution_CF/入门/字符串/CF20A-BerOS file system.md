# BerOS file system

## 题目描述

新的操作系统BerOS有一个很好的特性。可以在路径中使用任意数量的字符“/”作为分隔符，而不是使用一个传统的“/”。例如，字符串`//usr///local//nginx/sbin//`和`/usr/local/nginx///sbin//`是等效的。只有根目录的路径可以表示为单个字符“/”，才需要路径末尾的字符“/”（或此类字符的某些序列）。
如果路径包含尽可能少的字符数“/”，则称为normalized的路径。

您的任务是将给定路径转换为规范化形式。

## 样例 #1

### 输入

```
//usr///local//nginx/sbin
```

### 输出

```
/usr/local/nginx/sbin
```

# 题解

## 作者：览遍千秋 (赞：12)

字符串模拟题，先从后往前把尾部的/弄掉，再从头到尾扫一遍，遇到多个/只输出一个。


代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int l;
bool flag=0;
int main()
{
    cin>>s;
    l=s.size();
    while(s[l-1]=='/'&&l>=1) l--;
    if(!l) cout<<"/"<<endl;//需要特判的两种情况
    if(l==1) cout<<s[0]<<endl;
    for(register int i=0;i<l;i++)
    {
        if(flag)//如果之前有过斜杠了
        {
            if(s[i]!='/'){
                cout<<s[i];
                flag=0;
            }
        }
        else//如果之前没有斜杠
        {
            cout<<s[i];
            if(s[i]=='/') flag=1;
        }
    }
    return 0;
}
```

---

## 作者：蒟蒻wyx (赞：10)

我的思路是如果前一个=这一个==/，就不输出


否则输出


然后最后一位判段


---------------


然而会WA在”/////“的点上


所以我们开一个变量看输出量


然后最后一位判段如果输出量==0也输出


```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
//上面应该很清楚此处不再说了
    string s;
    cin>>s;//输入
    int len=s.length(),n=0;
    for(int i=1;i<len;i++){
        if(!(s[i]==s[i-1]&&s[i]=='/')){++n;cout<<s[i-1];}//删/
    }
    if(s[len-1]!='/'||n==0)cout<<s[len-1];//特判
}
                                          
```

---

## 作者：LW_h_FP (赞：4)

主要可以模拟寻找/


主要就是有几点


看有多个/的时候处理

```
while(a[i]=='/') i++;//就是一直判断到没有/时
```

最后面有/时或多个/时

```
while(a[al-1]=='/') al--;//反过来，al记录的是字符串a的长度
```

只有/的时候

```
if(al==0) cout<<'/';//这个是在前面的那个循环之后加个判断
```

但是前面的还是不太好可以直接加到while循环里


```
while(a[al-1]=='/'&&al!=1) al--;//改成这样它就不会到0了也就是至少留一个/
```

最后完整的

```
#include<iostream>
#include<cstring>
using namespace std;

char a[100]; //字符串
int al;      //a的长度

int main(){
    cin>>a; al=strlen(a);           //读入a，a的长度保存到al中
    while(a[al-1]=='/'&&al!=1) al--;//把后面的/去掉
    for(int i=0;i<al;i++){
        if(a[i]!='/') cout<<a[i];   //不是/直接输出
        else{ cout<<"/"; while(a[i]=='/') i++; i--; }找到一个/就先输出一个，再循环吧后面的都跳过，因为for循环会加1，所以再i--
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：Adam_Ng (赞：3)

思路很简单


一些用到的变量

```cpp
char n;//遍历时的临时存储变量
string ans="",to;//ans空串把答案往里加，to是初始输入串
bool be=0;//用来判断是否多个斜杠
int cut;//存储最后一个非斜杠位
```
---
除了串中间的斜杠去重，还要注意串尾不能有斜杠

所以要多一个操作

```cpp
for(int i=to.size()-1;i>=0;i--)
    if(to[i]!='/'){cut=i;break;}//从后往前取不是斜杠的最后一位，后面的省略。
```
---
接下来就是遍历去重，遍历到刚才取到的最后一个非斜杠位就好了。

```cpp
for(int i=0;i<=cut;i++)  //从头到最后的非斜杠位
    {
        n=to[i];
        if(n=='/'&&!be)    //如果是第一次出现的斜杠就加进ans串
        {
            be=1;    //be是用来判断是否多个斜杠的布尔
            ans+=n;
        }
        if(n!='/')    //如果不是斜杠就往ans串加,如果不是斜杠就一定要加
        {
            be=0;
            ans+=n;
        }
    }
    cout<<ans;
    return 0;
```
---
然后就AC啦~



---

## 作者：OdtreePrince (赞：2)

# -字符串-

请恕我到题解的王国里蹭口饭吃。

本题坑点重重，蒟蒻花了不少时间修代码，终于成功了

开心一秒钟！

切正题：

1.如果输入的字符全是'/',那么，输出一个/即可；

2.如果字符串后缀为/，无序输出；

3.如果遇到重复的/，去重。

OK,重点讲完了，上代码！

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;
    int i=0,check=0;
    for(int j=0;j<s.size();j++){
        if(s[j]!='/') check=1;
    }
    if(check==0){
        cout<<'/';
        return 0;
    }
    while(i<s.size()){
        while(s[i]!='/'&&i<s.size()) cout<<s[i],i++;
        int k=1;
        for(int j=i;j<s.size();j++){
        	if(s[j]!='/') k=0;
		}
        if(!k) cout<<'/';
        while(s[i]=='/') i++;
    }
    return 0;
}
~~~

---

## 作者：lwzheng00000 (赞：1)

一个比较简单的解法

#### 用一个flag标记一下就好了

一定要有一个变量来记录‘/’的数量，防止“/”，“///////”之类的数据
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
string a;
int main(){
    cin>>a;
    int len=a.length();
    int co=0;
    bool flag=true;//标记
    for(int i=0;i<len;i++){
        if(a[i]=='/'){
            flag=true;//如果有‘/’，标记为true，接下来到第一个不是‘/’的地方输出
            continue;
        }
        if(flag){//如果被标记了就输出
            putchar('/');
            co++;//记录输出‘/’的数量
            flag=false;//不能忘了标成false
        }
        printf("%c",a[i]);//原样输出路径
    }
    if(co==0){//如果没有输出‘/’，那就强行补一个
        putchar('/');
    }
    return 0;
}
```
是不是很~~复杂~~简单呢？

---

## 作者：anotherrainyday (赞：0)

看了一下 还没有人用这个方法做

一看到这个题面 我就想到了**replace** 只要把"//" 替换成"/" 就可以把多余的"/" 消除掉了

于是有了

```cpp
a = a.replace(a.find("//", 0), 2, "/");//把 //(两个字符)替换成/
```

但是一次肯定替换不完啊 所以

```cpp
L1:
a = a.replace(a.find("//", 0), 2, "/");
if (a.find("//", 0) != string::npos)//string::npos就是找不到了
	goto L1;
```

但是我RE了 原因是有可能并没有"//"(题目说的是**至少有一个"/"**)

改进后得到

```cpp
L1:
	if (a.find("//", 0) == string::npos)
		goto L2;
	a = a.replace(a.find("//", 0), 2, "/");
	goto L1;
L2:
```

但是又WA了 发现题面还说道 

> 路径末的/可以省略

```cpp
L1:
	if (a.find("//", 0) == string::npos)
		goto L2;
	a = a.replace(a.find("//", 0), 2, "/");
	goto L1;
L2:
	if (a[a.length() - 1] == '/')
		a = a.substr(0, a.length() - 1);
```

然后又WA了 因为如果整个路径就一个/ 那就会被去掉

```cpp
L1:
	if (a.find("//", 0) == string::npos)
		goto L2;
	a = a.replace(a.find("//", 0), 2, "/");
	goto L1;
L2:
	if (a[a.length() - 1] == '/' && a.length() != 1)//加了个判断
		a = a.substr(0, a.length() - 1);
```

终于AC了QAQ

最后上完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	string a;
	cin >> a;
L1:
	if (a.find("//", 0) == string::npos)
		goto L2;
	a = a.replace(a.find("//", 0), 2, "/");
	goto L1;
L2:
	if (a[a.length() - 1] == '/' && a.length() != 1)
		a = a.substr(0, a.length() - 1);
	cout << a;
	return 0;
}
```



---

## 作者：PC_DOS (赞：0)

这是一道字符串模拟题，只需要依照题目要求，将输入的字符串从头到尾检查一遍即可。如果读到一个斜杠"/"而且它的下一个也是斜杠，就不要输出它，其他情况原样输出当前读取的字符即可。至于最后一个字符，判断一下是不是斜杠即可，如果不是就输出。


需要注意的情况:


1. 字符串长度为1。前述算法为了防止溢出导致RE只能循环到(字符串长度-2)的位置，因此长度为1时需要特判(由于没有非法字符，只需要直接输出即可)。


2. 字符串长度不为1，但是全是斜杠，即形如"/////"的字符串。这时可以设定一个默认为True布尔变量isAllVirgule，如果执行前述循环时读取到了非斜杠字符，就把它设为False，这样输出最后一个字符的时候判定一下isAllVirgule，如果isAllVirgule为True，则直接输出最后一个字符即可。


代码:

```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
int main(){
    ios::sync_with_stdio(false); //关闭与STDIO的同步，一定意义上的输入输出加速
    string sInput; //输入的字符串
    bool isAllVirgule = true; //设定一个默认为True布尔变量isAllVirgule，如果执行前述循环时读取到了非斜杠字符，就把它设为False，这样输出最后一个字符的时候判定一下isAllVirgule，如果isAllVirgule为True，则直接输出最后一个字符即可。
    int i; //循环变量
    getline(cin, sInput); //读入路径
    if (sInput.length() <= 1){ //长度为1时需要特判(由于没有非法字符，只需要直接输出即可)
        cout << sInput; //输出
        goto endapp;
    }
    for (i = 0; i <= sInput.length() - 2; ++i){ //将输入的字符串从头到倒数第二个字符检查一遍。如果读到一个斜杠"/"而且它的下一个也是斜杠，就不要输出它，其他情况原样输出当前读取的字符即可。 
        if (sInput[i] == '/'){ //如果读到一个斜杠"/"
            if (sInput[i + 1] == '/') //而且它的下一个也是斜杠
                continue; //不输出
            else //否则
                cout << sInput[i]; //原样输出
        }
        else{
            isAllVirgule = false; //读取到了非斜杠字符，就将isAllVirgule设为False
            cout << sInput[i]; //原样输出
        }
    }
    if (sInput[sInput.length() - 1] != '/' || isAllVirgule) //如果最后一个字符不是斜杠，或者整个字符串都是斜杠
        cout << sInput[sInput.length() - 1]; //输出最后一个字符
endapp:
    return 0; //结束
}
```

---

## 作者：outis_crypt (赞：0)

刚开始看到这道题的时候，不假思索地就想，只要把字符串全部提取出来，然后在每个字符串前加一个"/"，再拼接，输出就行了啊，关键是用Python只需要6行。
于是就有了下面错误代码：

```python
s=input().split("/")
ans=""
for i in s:
    if i:
        ans+="/"+i
print(ans)
```
事实证明我还是太弱了。。。列举一下自己踩过的坑

**1.没有字符串，全部都是"/"**

很显然，按照上述错误代码，输出的是""， 什么都没有，但正确答案应该是一个"/"

**2.首字符没有"/" ,例如**

Input: a/b//c//
  
Output: /a/b/c

正确输出应该是: a/b/c

所以，知道所有的坑之后，就可以愉快的AC了

**完整正确代码如下**：

```python
head=0               //head就是用来解决第二个错误的
s=input()
if s[0]=='/':
    head=1
s=s.split("/")             //分离出字符串
s=[ i for i in s if i]         //数据清理，删掉所有""空串
ans=""                           //ans存放答案
for i in range(len(s)):
    if i==0 and not head:      //特判，首字符没有"/"就不用加"/"
        ans+=s[i]
    else:
        ans+="/"+s[i]
if len(s)==0:            //解决第一个错误，即输入全为"/"的情况
    ans="/"
print(ans)
```




---

## 作者：呵呵侠 (赞：0)

这一题耗费了我巨多的心血（痛）

第一边做：

```
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    char a[1000005];
    cin>>a;
    int i=strlen(a);
    for(int n=0;n<i;n++)
    {
        if(a[n]==a[n-1]&&a[n]=='/')
            continue;
        cout<<a[n];
    }
}
```
第六个点凉了

……

然后我分析原因，发现没有去尾

然后改了

第二遍做：
```
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    char a[1000005];
    cin>>a;
    int i=strlen(a);
    for(int n=0;n<i;n++)
    {
        if(a[n]==a[n-1]&&a[n]=='/')
            continue;
        if(n==i-1&&a[n]=='/')
            continue;
        cout<<a[n];
    }
}
```
又凉了，这次是第四个点

然后我再次分析原因

发现这样做会“死”在“/”上

哎

第三遍做：
```
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    char a[1000005];
    cin>>a;
    int i=strlen(a);
    bool k=0;
    for(int n=0;n<i;n++)
    {
        if(a[n]!='/')
            k=1;
        if(a[n]==a[n-1]&&a[n]=='/')
            continue;
        if(a[n]=='/'&&n==i-1&&k==1)
            continue;
        cout<<a[n];
    }
}
```
仍然凉了，还是第六个点

再次检查，发现BUG！

这个程序只适用于结尾只有一个“/”的情况

然而测试点应该至少有两个！！！

不过，这种情况会将结尾的“/”变成一个

所以不妨，两次循环

先不说别的，看我的AC代码（第四遍做）
```
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    char a[1000005],p[1000005];
    cin>>a;
    int q=0;
    int i=strlen(a);
    bool k=0;//这个是判断有没有字母的，以防被“////”这种情况坑
    for(int n=0;n<i;n++)
    {
        if(a[n]!='/')
            k=1;//有字母
        if(a[n]==a[n-1]&&a[n]=='/')//必要
            continue;//循环催眠
        if(a[n]=='/'&&n==i-1&&k==1)//这句似乎没用，但是留着吧
            continue;
        p[q]=a[n];//做完去重，然后读入
        q++;
    }
    //经过这一番捯饬，终于结尾只剩一个“/”了
    for(int n=0;n<q;n++)
    {
        if(p[n]!='/')
            k=1;
        if(p[n]==p[n-1]&&p[n]=='/')//从上面复制的，懒得删
            continue;
        if(p[n]=='/'&&n==q-1&&k==1)//必要
            continue;
        cout<<p[n];
    }
}
```

---

## 作者：文·和 (赞：0)

## 思路：

输入后在路径后加上一个‘/’，然后扫路径的前面几个字符，如果扫描到的字符是字母或者这是‘/’但下一项不是那么输出。因为最后多加了一个‘/’，所以最后一个也不会输出。

#### 注意在输出时记录输出的个数，如果最后发现没有输出就输出一个‘/’~~给题目面子~~来补足

根据以上思路贴出代码：

```
#include <bits/stdc++.h>  //万能头
using namespace std;
string s;
int i,j;              
int main(){
cin>>s;            //输入
s+='/';            //原串末尾加‘/’
for(i=0;i<s.size()-1;i++)    
if(s[i]!='/'||(s[i]=='/'&&s[i+1]!='/')){   //如果是字母或单独的‘/’则输出
cout<<s[i];  
j++;    //记录输出个数
}
if(j==0) cout<<'/';   //特判
return 0;    //结束
}
```

本蒟蒻的题解就到这里了，求通过QWQ

---

