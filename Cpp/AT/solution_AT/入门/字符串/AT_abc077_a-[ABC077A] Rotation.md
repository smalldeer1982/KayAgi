# [ABC077A] Rotation

## 题目描述

给定两个长度为 $3$ 的字符串，如果一个字符串反转后与另一个相等，那么输出 `YES`，否则输出 `NO`。

提示：输出的末尾要输出一个换行符。

## 说明/提示

输入数据中只会出现两个长度为 $3$ 的，由小写字母组成的字符串。

感谢@福州周圣力  提供的翻译

## 样例 #1

### 输入

```
pot
top```

### 输出

```
YES```

## 样例 #2

### 输入

```
tab
bet```

### 输出

```
NO```

## 样例 #3

### 输入

```
eye
eel```

### 输出

```
NO```

# 题解

## 作者：Reywmp (赞：5)

~~楼下用STL的dalao太强了，只能%%%~~


------------

>反转字符穿是基本操作，必须要会的。
学习字符串时相信大家也接触过，所以我就话不多说了。

------------

原理很简单，记住反转字符串的公式就可以了:

`s[i]=s[len-i-1]`

其中len为字符串长度，而这个-1非常重要，不能缺少！因为使用gets(a)或scanf("%s",a)...时,是从下标0开始输入的。

当然了，使用gets(a+1),scanf("%s",a+1)...便可以从字符串1下标1开始输入了。那上面的式子也就变成了：

`s[i]=s[len-i+1]`


------------

不说废话了，上代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
int main()
{
	char a[5],b[5];
    gets(a);
    gets(b);
    int len=3;//其实我可以直接写3的，不过习惯了。
    for(int i=0;i<len;i++)
    {
    	a[i]=a[len-i-1];
	}
    /*同样的，你可以使用：
    for(int i=1;i<=len;i++)
    {
    	a[i]=a[len-i+1];
	}
    那么上面就是gets(a+1);gets(b+1);
    */
    for(int i=0/*或者是1*/;i<len/*或者是<=*/;i++)
    {
        if(a[i]!=b[i])
        {
            printf("NO\n");//不一样就直接输出，结束程序了
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
```

------------

其实我AC代码不是这样写的，不过也贴上来吧：

------------


```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
int main()
{
    char a[3],b[3];
    gets(a);
    gets(b);
    char ch=a[2];//ch临时储存最后一个字符
    a[2]=a[0];//将最后一个字符赋值为第一个
    a[0]=ch;//再将第一个赋值为ch，也就是最后一个字符
    /*直接将第一个字符与最后一个对调，
    由于是3个字符，反转过来的话第二个一直是第二个*/
    for(int i=0;i<3;i++)
    {
        if(a[i]!=b[i])
        {
            printf("NO\n");//同上
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
```

再给大家推荐一道字符串反转的练手题，很水，noip原题
：[P1307 数字反转](https://www.luogu.org/problemnew/show/P1307)

------------

>~~奥义·水题解长度！~~

>~~最近没怎吗发blog也没发题解，所以来找个大水题凑个数~~



---

## 作者：CZQ_King (赞：2)

## 好像没多少$dalao$想到直接判断，都是用翻转后判断的。
###### ~~此题特难~~
 
------------

上代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a,b;//定义不多说
int main(){
    cin>>a>>b;//输入这两个字符串
    if(a[0]==b[2]&&a[1]==b[1]&&a[2]==b[0])cout<<"YES"<<endl;
    else cout<<"NO"<<endl;//直接判断
    return 0;//完美结束
}
```

---

## 作者：封禁用户 (赞：0)

居然没有人用pascal？尼古拉斯·沃斯会伤心的……              
# 正题： 暴力判断字符串！

代码如下：

```pascal
var
    s1,s2:string;
begin
    readln(s1);
    readln(s2);
    if(s2[1]<>s1[3])then//暴力判断，暴力判断，暴力判断！（重要的事情说三遍！）
    begin
        writeln('NO');
        exit;
    end;
    if(s2[2]<>s1[2])then
    begin
        writeln('NO');
        exit;
    end;
    if(s2[3]<>s1[1])then
    begin
        writeln('NO');
        exit;
    end;
    writeln('YES'); 
end.   //↑这换行坑了我多年

```
好了就这样草草结束吧（草率233）-(:з」∠)_

---

## 作者：xyn0901 (赞：0)

交了三四次发现'YES'打成了'yes'     

(qwq)

没有楼上大佬那么流批，

我是一个一个判断

上代码
```pascal
var s,s1:string;
begin
readln(s);
readln(s1);
if 
(s[1]=s1[3])and
(s[2]=s1[2])and
(s[3]=s1[1]) then writeln('YES')
else writeln('NO');
end.
```

---

## 作者：Tomone (赞：0)

用C++的STL
```
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

//const int maxn(10086);

int main(){
	ios::sync_with_stdio(false); //输入输出优化
	string s1,s2;
	cin>>s1>>s2;
	reverse(s1.begin(),s1.end()); //将s1翻转
	if(s1==s2) printf("YES\n"); //若翻转后==s2则输出YES
	else printf("NO\n"); 
	return 0;
}

```

---

## 作者：da32s1da (赞：0)

c++中自带了字符串翻转函数和字符串比较函数，于是乎
```
#include<bits/stdc++.h>
using namespace std;
char s[100001],s1[100001];
int main(){
    cin>>s>>s1;
    if(strlen(s)!=strlen(s1)) puts("NO");  //若长度不同，肯定不可以
    else{
    	reverse(s1,s1+strlen(s1));  //翻转一下
    	if(!strncmp(s,s1,strlen(s))) puts("YES");  //相同为YES
    	else puts("NO");  //不同为NO
    }
}
```

---

## 作者：⚡YMJcvjk⚡ (赞：0)

  这题挺简单，你可以将其中的一个字符串反一下，在跟另外一个字符串比较。代码:
//pascal代码   
var    
 s1,s2,s3:ansistring;    
 i:longint;    
begin     
 readln(s1);    
 readln(s2);    
 for i:=length(s2) downto 1 do s3:=s3+s2[i];//反转    
 if s3=s1 then writeln('YES')//比较   
          else writeln('NO');   
end.

---

