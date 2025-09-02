# Haiku

## 题目描述

Haiku is a genre of Japanese traditional poetry.

A haiku poem consists of 17 syllables split into three phrases, containing 5, 7 and 5 syllables correspondingly (the first phrase should contain exactly 5 syllables, the second phrase should contain exactly 7 syllables, and the third phrase should contain exactly 5 syllables). A haiku masterpiece contains a description of a moment in those three phrases. Every word is important in a small poem, which is why haiku are rich with symbols. Each word has a special meaning, a special role. The main principle of haiku is to say much using a few words.

To simplify the matter, in the given problem we will consider that the number of syllable in the phrase is equal to the number of vowel letters there. Only the following letters are regarded as vowel letters: "a", "e", "i", "o" and "u".

Three phases from a certain poem are given. Determine whether it is haiku or not.

## 样例 #1

### 输入

```
on  codeforces 
beta round is running
   a rustling of keys 
```

### 输出

```
YES```

## 样例 #2

### 输入

```
how many gallons
of edo s rain did you drink
                                cuckoo
```

### 输出

```
NO```

# 题解

## 作者：hensier (赞：7)

大部分$C++$大佬都会使用$getline(cin,string)$解决该题，不过我们可以使用兼容$C$语言的方法解决。

对于整行输入，我们可以用$gets(char*)$。然后设置一个判断函数即可。

```cpp
#include<cstdio>
char a[100],b[100],c[100],i,t[2][4]={"NO","YES"};
bool check(char *s,int n)//char指针表示char数组，等同于string
{
    int p=0;//元音数量为0
    for(i=0;s[i];i++)if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u')p++;//是元音就加1
    return p==n;//p与n相同返回1，否则返回0
}
int main()
{
    gets(a);
    gets(b);
    gets(c);//输入
    printf("%s",t[check(a,5)*check(b,7)*check(c,5)]);//输出——音节要求为5、7、5，必须同时满足才能是YES，可以用逻辑乘连接。
}
```

---

## 作者：YosemiteHe (赞：4)

字符串水题。

题目大意：给你三个串，如果第一个串和第三个串中的元音字母数量等于5个，并且第二个串中的元音字母数量等于7个，那么输出 `YES`，否则输出 `NO`。

因为 `允许有空格前缀或空格后缀`，所以要用 `getline` 读入字符串。读入方法：

`getline(cin, 字符串名称)`

然后就可以打出AC代码了。

```cpp
#include <bits/stdc++.h>//万能头 
using namespace std;//命名空间 
string a, b, c;//定义字符串 
int ca, cb, cc;//定义统计变量 
int main(void) { //主函数 
	getline(cin, a);//用getline读入 
	getline(cin, b);//同上 
	getline(cin, c);//同上 
	for (int i = 0; i < a.length(); ++i) { //开始枚举每一位 
		char ch = a[i];//用一个char类型变量保存a[i] 
		if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') ca++;//判断并累加 
	}
	for (int i = 0; i < b.length(); ++i) { //同上 
		char ch = b[i];
		if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') cb++;
	}
	for (int i = 0; i < c.length(); ++i) { //同上 
		char ch = c[i];
		if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') cc++;
	}
	if (ca == 5 && cb == 7 & cc == 5) printf("YES\n");//如果成立，输出"YES" 
	else printf("NO\n");//否则输出"NO" 
    return 0;//结束 
}

```

---

## 作者：wzm2007 (赞：4)

    此题模拟即可
    需注意读入时要用scanf
    代码:

------------

    #include<bits/stdc++.h>
    using namespace std;
    int a[]={0,5,7,5};  //元音个数
    int main()
    {
        int ans=0;
        char c;
        for(int i=1;i<=3;i++)  //三个短句
        {
            while(scanf("%c",&c))
            {
                if(c=='\n')break;
                if(c!='a'&&c!='e'&&c!='i'&&c!='o'&&c!='u')continue;  //判断是否是元音
                ans++;
            }
            if(ans!=a[i])
            {
                cout<<"NO";
                return 0;
            }
            ans=0;  //清零ans
        }
        cout<<"YES";
        return 0;
    }

---

## 作者：至成天下 (赞：2)

这题是一道非常水的紫题

注意读入的字符串中可能有空格

所以要用getline读

getline用法:getline(cin,字符串名称);

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string st;
    bool pd=0;//判断是否为Haiku
    int count=0;
    getline(cin,st);//getline读入
    for(int i=0;i<st.size();++i){//扫描字符串
        if(st[i]=='a'||st[i]=='e'||st[i]=='i'||st[i]=='o'||st[i]=='u')count++;
    }
    if(count!=5)pd=1;
    count =0;
    getline(cin,st);
    for(int i=0;i<st.size();++i){
        if(st[i]=='a'||st[i]=='e'||st[i]=='i'||st[i]=='o'||st[i]=='u')count++;
    }
    if(count!=7)pd=1;
    count =0;
    getline(cin,st);
    for(int i=0;i<st.size();++i){
        if(st[i]=='a'||st[i]=='e'||st[i]=='i'||st[i]=='o'||st[i]=='u')count++;
    }
    if(count!=5)pd=1;
    if(pd==1)cout<<"NO"<<endl;//不是输出NO
    else cout<<"YES"<<endl;//否则输出YES
return 0;
}

```

---

## 作者：一滴小水滴 (赞：1)

## 似乎没有人用函数诶，那我就用函数做一做吧
***
# 窝们可以分别 geline 三个string字符串 x，y，z，然后用一个函数来判断这三个字符串是不是Haiku
## 具体函数操作是这样的（本蒟蒻的代码可能比较笨重）
```cpp
bool isHaiku(string x,string y,string z)
{
	int a=0,b=0,c=0;
	for(int i=0;i<x.size();i++)
		if(x[i]=='a'||x[i]=='e'||x[i]=='i'||x[i]=='o'||x[i]=='u')a++;
	if(a!=5)return 0;   //先判断第一个字符串x，如果不符合Haiku，就返回false。
	for(int i=0;i<y.size();i++)
		if(y[i]=='a'||y[i]=='e'||y[i]=='i'||y[i]=='o'||y[i]=='u')b++;
	if(b!=7)return 0;   //再判断第二个字符串y，如果不符合，就返回false。
	for(int i=0;i<z.size();i++)
		if(z[i]=='a'||z[i]=='e'||z[i]=='i'||z[i]=='o'||z[i]=='u')c++;
	if(c!=5)return 0;   //最后判断最后一个z，不符合就返回false。
	return 1;    //如果函数还没有结束，就说明符合Haiku，返回true。
}
```
## 接下来是main函数
```cpp
string x,y,z;
	getline(cin,x);
	getline(cin,y);
	getline(cin,z);
	if(isHaiku(x,y,z))cout<<"YES"<<endl;
	else cout<<"NO"<<endl;   //输入后判断是不是Haiku，
                  //是就输出YES，不是输出“NO”（注意都是大写）。
	return :);  //让我通过好不好鸭。（顺便弄个坑）
```

***

# 其实这个题目还是很水的，大家AC哟

---

## 作者：天有不测风云 (赞：1)

这题只要看每一行有几个aeiou就行了。

因为一行中可能有空格，所以这题考虑用getline。

贴代码，原版防抄，内含注释~~不在意码风就行了~~：

------------

```cpp
#<iostream>//输入输出头文件
#<string>//字符串头文件
using namespace std;//名字空间
long long a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;//不用在意这个
string S1,S2,S3;//定义字符串变量
main()
{
	getline(cin,S1）；//输入数据
	getline(cin,S2）；
	getline(cin,S3）；
	for(i=0;i<S1.size();i++）//统计第一个字符串aeiou的个数
	{
		if((S1[i]=='a')||(S1[i]=='e')||(S1[i]=='i')||(S1[i]=='o')||(S1[i]=='u')）
		x++；
	}
	for(i=0;i<S2.size();i++)//统计第二个字符串aeiou的个数
	{
		if((S2[i]=='a')||(S2[i]=='e')||(S2[i]=='i')||(S2[i]=='o')||(S2[i]=='u'))
		y++;
	}
	for(i=0;i<S3.size();i++)//统计第二个字符串aeiou的个数
	{
		if((S3[i]=='a')||(S3[i]=='e')||(S3[i]=='i')||(S3[i]=='o')||(S3[i]=='u'))
		z++；
	}
	if((x==5)&&(y==7)&&(z==5))//最后判断
    //如果是输出YES
	{
		cout<<"YES"<<endl;
		return 0;
	}
	else//如果不是输出NO
	{
		cout<<"NO"<<endl;
		return 0;
	}
	return 0；
}
```


---

## 作者：小鲍bob (赞：0)

### 此题主要考查字符串的读入以及运用
首先我们先来分析一下题目，输入的字母全部为小写，就可以不用判断大写。

注意这题有个坑，就是输入的字符串有空格。空格意味着我们不能用cin来读入，因为cin遇到空格就自动结束。

所以，我们这题得用getline来输入了。

用法格式：getline(cin,输入的字符串名字);

知道了这点后，我们就可以开始做程序了。

首先，我们发现题目中有一个地方可以优化:
```
if(a.length()<5||b.length()<7||c.length()<5)
	{
		cout<<"NO";
		return 0;
	}
```
这里先令字符串为a，b，c，如果他们长度分别小于5，7，5，那么就绝对不可能元音字母的个数超过5，7，5了。所以这里我们可以直接输出NO。

接着就上完整代码：
```
#include<bits/stdc++.h>//万能头
using namespace std;
int main()
{
	string a,b,c;
	int i,s=0;//i用于循环，s用于找原音字母个数
	getline(cin,a);//输入
	getline(cin,b);
	getline(cin,c);
	if(a.length()<5||b.length()<7||c.length()<5)//优化
	{
		cout<<"NO";
		return 0;
	}
	for(i=0;i<=a.length();i++)//注意字符串的存储是从0开始的，所以要从0开始循环
	{
		if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u')
		{
			s++;//累加
		}
	}
	if(s!=5)//直接判断
	{
		cout<<"NO";
		return 0;
	}
	s=0;//记得一定要清零，不然会从非5的数开始算
	for(i=0;i<=b.length();i++)
	{
		if(b[i]=='a'||b[i]=='e'||b[i]=='i'||b[i]=='o'||b[i]=='u')
		{
			s++;
		}
	}
	if(s!=7)
	{
		cout<<"NO";
		return 0;
	}
	s=0;
	for(i=0;i<=c.length();i++)
	{
		if(c[i]=='a'||c[i]=='e'||c[i]=='i'||c[i]=='o'||c[i]=='u')
		{
			s++;
		}
	}
	if(s!=5)
	{
		cout<<"NO";
		return 0;
	}
	cout<<"YES";//不符合的都去掉了，就可以输出YES了。
	return 0;
} 
```
最后，实验可得：优化后的代码比未优化后的代码用时少了0.04s。

所以这告诉我们：我们做信息题一定要学会优化吗，也许不优化就会超时，但优化后超时的几率会降低。


---

## 作者：wpy233 (赞：0)

# getline，好东西！

题目其实不难，用$getline$这个神奇的东东输入，然后依次判断里面的元音字母个数，然后输出就行了。

关键是代码写得比较~~皮~~完美QAQ

$Code$:
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int pd(string a)//pd=判断
{
    int s=0;//计数
    for(int i=0;i<a.size();i++)//扫一遍，遇到援引字母就累加
        if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u')
            s++;
    return s;//返回
}
void sc(bool x)//sc=输出
{
    if(x) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;//判断输出，注意YES和NO都要大写
}
int main()
{
    string a,b,c;//定义
    getline(cin,a);
    getline(cin,b);
    getline(cin,c);//getline万岁！！！
    sc(pd(a)==5&&pd(b)==7&&pd(c)==5);//？？？（窝好皮呀）
    return 0;
}
```

---

## 作者：追风少年σχ (赞：0)

### 简单模拟，关键是读入（我冒险用gets()）
### 我的代码应该比较简洁。。。（~~自恋狂~~）
好吧上代码：（简单）


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char ch[104];
int work(){
    int n,s=0;
    gets(ch);
    n=strlen(ch);
    for(int i=0;i<n;i++)
        if(ch[i]=='a'||ch[i]=='e'||ch[i]=='i'||ch[i]=='o'||ch[i]=='u')
            s++;
    return s;
}

int main(){
    if(work()!=5){
        printf("NO");
        return 0;
    }
    if(work()!=7){
        printf("NO");
        return 0;
    }
    if(work()!=5){
        printf("NO");
        return 0;
    }
    printf("YES");
    return 0;
}
```
通俗易懂的题解对吧~~QWQ~~

---

## 作者：珅肐 (赞：0)

模拟即可，注意细节

一共三行，每行音节数应为$5$,$7$,$5$

开个数组记录一下

因为有空格，$getline$读入

每行字符扫一遍看是否符合

如果不符合直接退出

就非常简单
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string s;
int a[]={0,5,7,5};
int main(){
	for(int i=1,cnt=0;i<=3;++i){
		getline(cin,s);cnt=0;
		for(int j=0;j<s.size();++j)cnt+=(s[j]=='a' || s[j]=='e' || s[j]=='i' || s[j]=='o' || s[j]=='u');
		if(cnt!=a[i]){puts("NO");return 0;}//如果不是5、7、5,直接退出
	}
	puts("YES");//执行到这里说明符合Haiku,输出YES
	return 0;//好习惯
}
```


---

## 作者：t162 (赞：0)

蒟蒻迷上了正则，迷上了Python。

题目已经说得很清楚了，`短句的音节数视为这个短句中的元音字母数`，所以使用正则匹配就行了。

```
[a,e,i,o,u]{1}	#意思是匹配中括号中字符的任意一个。
```

我们使用re模块的findall函数，分别找到三个字符串所有匹配的字符，分别对每个结果取长度并判断即可。

代码：

```python
import re

s1 = input()
s2 = input()
s3 = input()

if(len(re.findall(r'[a,e,i,o,u]{1}',s1))==5 and len(re.findall(r'[a,e,i,o,u]{1}',s2))==7 and len(re.findall(r'[a,e,i,o,u]{1}',s3))==5):
    print('YES')
else:
    print("NO")
```

---

## 作者：xh39 (赞：0)

# 简单的模拟
## 定义三个字符串
#### 介绍一个输入函数叫cin.getline
cin.getline有2个参数第一个参数表示要输入那个字符串，第二个参数表示最多接收多少个字符，后面输入的字符全丢弃。
比如第二个参数是3，输入abcde,字符串就只会是abc
#### cin.getline的好处是可以含空格输入字符串，用cin或scanf有空格就会断开
每个字符串分别判断是a||是e||是o||是i||是u,就sum++

第一个字符串sum!=5||第二个字符串sum!=7||第三个字符串!=5 就输出"NO" 否则输出"YES"

代码就不要看了吧。。。
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1005],b[1005],c[1005];//用cin.getline输入string会CE的(不信你自己试试~)
int main(){
    int sum=0,i;
    cin.getline(a,2000000000);//把它设置为最大，这样无论输入多少个都可以完整接受。
    cin.getline(b,2000000000);
    cin.getline(c,2000000000);
    for(i=0;a[i]!='\0';i++){
        if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='u'||a[i]=='o'){
            sum++;
        }
    }
    if(sum!=5){
        cout<<"NO";
        return 0;
    }
    sum=0;
    for(i=0;b[i]!='\0';i++){
        if(b[i]=='a'||b[i]=='e'||b[i]=='i'||b[i]=='u'||b[i]=='o'){
            sum++;
        }
    }
    if(sum!=7){
        cout<<"NO";
        return 0;
    }
    sum=0;
    for(i=0;c[i]!='\0';i++){
        if(c[i]=='a'||c[i]=='e'||c[i]=='i'||c[i]=='u'||c[i]=='o'){
            sum++;
        }
    }
    if(sum!=5){
        cout<<"NO";
        return 0;
    }
    cout<<"YES";
    return 0;
}
```

---

## 作者：BCZSX (赞：0)

这就是一道~~超级水的~~紫题，话不多说，讲解看代码里吧！
```cpp
#include<cstdio>
using namespace std;
const int l[]={0,5,7,5};
char s;
int ans=0;
int main()
{
	for(int i=1;i<=3;++i)//三句话
	{
		while(scanf("%c",&s))//读入字符
		{
			if(s=='\n') break;
			if(s!='a'&&s!='e'&&s!='i'&&s!='o'&&s!='u') continue;//如果不是元音就跳过
			ans++;//否则就ans++
		}
		if(ans!=l[i])//判断是否与题目要求的一样
		{
			printf("NO");//不是输出NO
			return 0;//结束程序
		}
		ans=0;//初始化ans
	}
	printf("YES");//符合题目要求，输出YES
	return 0;
}
```
本蒟蒻的第一篇题解,qwq!

---

## 作者：CobaltChloride (赞：0)

```
见代码
#include<bits/stdc++.h>
using namespace std;
int a[4],i=1,m;
char c;
int main(){
    c=getchar();
    while(1){//一个个字符读入
        m++;
        if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u') a[i]++;//是元音
        if(c=='\n') i++;//换一行
        c=getchar();
        if(m>300) break;//最多有300个字符
    }
    if(a[1]==5&&a[2]==7&&a[3]==5) cout<<"YES";//判断
    else cout<<"NO";
    return 0;
}
```

---

## 作者：shenmadongdong (赞：0)

~~既然没有Pascal的题解，那本蒟蒻来水一发~~

其实只要判断每个短句的元音个数即可

代码：
```
var a,b,c,i:longint;
    s:ansistring;
begin
  readln(s);
  for i:=1 to length(s) do if (s[i]='a')or(s[i]='e')or(s[i]='i')or(s[i]='o')or(s[i]='u') then inc(a);
  readln(s);
  for i:=1 to length(s) do if (s[i]='a')or(s[i]='e')or(s[i]='i')or(s[i]='o')or(s[i]='u') then inc(b);
  readln(s);
  for i:=1 to length(s) do if (s[i]='a')or(s[i]='e')or(s[i]='i')or(s[i]='o')or(s[i]='u') then inc(c);//统计
  if (a=5)and(b=7)and(c=5) then writeln('YES') else writeln('NO');//判断
end.
```

---

## 作者：向日葵小班 (赞：0)

# $\color{red}\text{这是一道大水题}$

**但我那么敬业，还是讲一讲吧**

## 思路：
**1.输入三个字符串（这里叫a，b，c），注意：要用getline，用cin不能读取空格（          getline用法：getline（cin,字符串名称））**

**2.分别循环a，b，c的长度次，如果字符串中的一个字符为元音（就是a，e，i，o，u），对应的用于统计的变量++（这里叫h，hh，hhh）**

**3.判断：如果h==5，hh==7，hhh==5就输出YES，否则输出NO**

## 放代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string a,b,c;//定义3个字符串，这里叫a，b，c
int h,hh,hhh;//定义3个用于统计的变量，这里叫h，hh，hhh
int main()
{
     getline(cin,a);//输入a
	 getline(cin,b);//输入b
	 getline(cin,c);//输入c
	 for(int i=0;i<a.size();i++)//循环a的长度次
	 if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u')h++;//如果字符串a中的一个字符为元音，h++
	 for(int i=0;i<b.size();i++)//循环b的长度次
	 if(b[i]=='a'||b[i]=='e'||b[i]=='i'||b[i]=='o'||b[i]=='u')hh++;//如果字符串b中的一个字符为元音，hh++
 	 for(int i=0;i<c.size();i++)//循环c的长度次
	 if(c[i]=='a'||c[i]=='e'||c[i]=='i'||c[i]=='o'||c[i]=='u')hhh++;//如果字符串c中的一个字符为元音，hhh++
	 if(h==5&&hh==7&&hhh==5)//cout<<"YES";如果h==5，hh==7，hhh==5就输出YES
	 else cout<<"NO";//否则输出NO
    return 0;//完美结束
}
```


---

## 作者：liuyifan (赞：0)

题意已经有[讨论](https://www.luogu.org/discuss/show?postid=67678)发过了,这里就不再重复了

按题意模拟统计即可,时间复杂度O(n)

code:
```cpp
#include<bits/stdc++.h>
#define reg regis
using namespace std;
char s;
int a[10];
int main()
{
    for(reg int i=1;i<=3;i++)
    {
		memset(s,0,sizeof s);//一种快速将数组清0的方法,对其他数据类型也可以使用
        gets(s);
        for(reg int j=0;j<strlen(s);j++)
        if(s=='a'||s=='e'||s=='i'||s=='o'||s=='u')a[i]++;//按题意模拟
    }
    puts(a[1]==5&&a[2]==7&&a[3]==5?"YES":"NO");//满足就输出yes
    //puts自带换行,应对ATcoder
    return 0
}
//该代码做了错误化处理,不影响阅读,但不能直接复制
```
提交记录：

![](https://i.postimg.cc/hPVqtjYg/image.png)

[My Blog](https://www.luogu.org/blog/liuyifan/)

---

