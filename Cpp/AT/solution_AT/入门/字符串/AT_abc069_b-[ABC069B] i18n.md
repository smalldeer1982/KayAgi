# [ABC069B] i18n

## 题目描述

单词 `internationalization` 有时会被缩写为 `i18n`。这是因为首字母 `i` 和末尾字母 `n` 之间夹着 $18$ 个字母。

现在给定一个只包含小写英文字母且长度不少于 $3$ 的字符串 $s$，请按照同样的规则对 $s$ 进行缩写。

## 说明/提示

## 限制条件

- $3 \leq |s| \leq 100$（其中 $|s|$ 表示 $s$ 的长度）
- $s$ 只包含小写英文字母。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
internationalization```

### 输出

```
i18n```

## 样例 #2

### 输入

```
smiles```

### 输出

```
s4s```

## 样例 #3

### 输入

```
xyz```

### 输出

```
x1z```

# 题解

## 作者：没有输入 (赞：8)

# 字符串

本题主要考查对字符串的认识和理解。虽然是一道**紫题**，但只要对字符串有基本的了解，就可以完成此题。

获取字符串长度
```cpp
strlen(s)
```
这个函数返回的是字符串中含有字符的数量，即字符串长度。因为不算头尾两个字符，所以不要忘记减2。

### 总结

本题是一道字符串的入门题目，只要不掉坑，基本可以一遍过。**注意字符串下标是从零开始的。**
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10000];//定义
int main()
{
	gets(s);//输入
	cout<<s[0]<<strlen(s)-2<<s[strlen(s)-1];//输出
	return 0;//完美结束
}
```
## 拓展：字符串

字符串或串(String)是由数字、字母、下划线组成的一串字符。一般记为 s=“a1a2···an”(n>=0)。它是编程语言中表示文本的数据类型。在程序设计中，字符串（string）为符号或数值的一个连续序列，如符号串（一串字符）或二进制数字串（一串二进制数字）。

通常以串的整体作为操作对象，如：在串中查找某个子串、求取一个子串、在串的某个位置上插入一个子串以及删除一个子串等。两个字符串相等的充要条件是：长度相等，并且各个对应位置上的字符都相等。设p、q是两个串，求q在p中首次出现的位置的运算叫做模式匹配。串的两种最基本的存储方式是顺序存储方式和链接存储方式。

我是[没有输入](https://www.luogu.org/space/show?uid=154344)，我们下次再见！

---

## 作者：xxckie (赞：2)

本蒟蒻又来发题解啦！！！

看到各位dalao的很简短...我的嘛，有点麻烦，不过还是挺“实用”滴......

我的方法就是
## **逐位枚举**！！

这样的话就可以把输入的字符串分成三部分：

1、第1位：直接输出

2、第2位~倒数第2位：长度个数++

3、最后1位：**先输出长度个数**，再把当前字符输出

~~Finish！~~

岛国题，最好加个endl...

### **Finish！！**

下面请各位dalao签收代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>

using namespace std;
string st;
int ans,len;
int main()
{
	cin>>st;
	len=st.size();//记录字符串长度
	for(int i=0;i<len;i++)
	{
		if(i==0)cout<<st[i];//如果是第一位，就直接输出
		else //否则...
		{
			if(i!=len-1)ans++;//如果是第2位~倒数第2位，长度个数++
			else //否则...（如果是最后一位的话...）
            	cout<<ans<<st[i];//就输出长度个数和当前字符
		}
	}
    cout<<endl;
return 0;//可以完美的AC了！！！
}
```

以上就是本蒟蒻这道题滴思路，如果各位dalao觉得有什么不足，在右边→评论区告诉我吧，886~~

---

## 作者：Xiamo_Azure (赞：2)

为啥？别人的程序都这么长？？？？
（还有，这为啥是紫题？？？？）

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;/*定义字符串*/
int len; /*定义s长度*/
int main()
{
	/*好短啊！！！mua~*/
	cin>>s;/*输入s*/
	len=s.size();/*求出s长度*/
	cout<<s[0];/*输出第一个*/
	cout<<len-2;/*输出中间长度——总长度-（第一个和第二个）*/
	cout<<s[len-1];/*输出最后一个*/ 
	return 0;/*结束*/
}
```
我想昂！！！这个连智商-1的小屁孩都可以想得出来呀！！！

喜欢的点个赞吧，作者也不容易啊！每天只可以在机房里吃着泡面：-）

@chen_zhe   
求通过！！！

---

## 作者：Yoo_ (赞：2)

这道题竟然还没有题解？我来补一下吧
```
//（这道题的翻译我提交了，希望能通过吧）

```
这道题看样例就能大体看明白，输出第一个字符加第一个和最后一个中间有多少个字符，加上最后一个字符
所以代码如下

```
#include<bits/stdc++.h>
using namespace std;
char a[10001];
int main()
{
    cin>>a;
    cout<<a[0]<<strlen(a)-2<<a[strlen(a)-1]<<endl;//字符串的第一个是a[0]要注意，然后就输出他，strlen就是求这个字符串的长度，因为这道题要求中间的长度，所以要-2，
    //最后一项就是最后一个字符了，因为第一个字符时a[0]，所以第n个就是a[n-1]；
    //endl不要忘记
    return 0;//好习惯要养成
}
```

---

## 作者：封禁用户 (赞：1)

这道题是字符串的基础题

考察第一天学字符串的OIer有没有听课/--A--\

所以是一道~~红题~~

提取字符串长度:
```
string类型可以用:len=s.size();

还有:len=s.strength();

char类型可以用:len=strlen(s);
```
说了这么多，是时候该让你们知道咋写了

code:
```
#include<此题太水>
#include<bits/stdc++.h>//懒人专属万能表头
using namespace std;
string s;//定义字符串类型变量s
int len;//用来存s的长度
int main()
{
	cin>>s;//输入字符串
	len=s.size();//取它的长度
	cout<<s[0]<<len-2<<s[len-1];//一行输出
   //字符串是从0开始存的
   //它两头的字符不算,所以中间的长度是len-2
   //既然字符串是从0开始存的,那么最后一个字符就存在len-1
	return 0;//养成良好的写代码习惯
}
```
## 在最后,本蒟蒻想说一句话:"这道岛国(日本)的题怎么不用换行就能AC!。"

---

## 作者：MikeC (赞：1)

这道题是一道水题（~~废话~~） 
  
很明显只要用到cstring中自带的字符串函数就能完成，但是这种方法对于“刚学OI两小时”的萌新们显得十分不友好。  
  
想到历史上屡次在OI赛场上创造奇迹的——
  
### 暴力法  
  
思路：统计字符串长度len，输出第一个字符+len-2+最后一个字符。
  
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    char a[101];
    int len=0;
    cin>>a;
    while(a[len]){
        len++;
    };
    cout<<a[0]<<len-2<<a[len-1];
    return 0;
}
```




---

## 作者：xxxjz (赞：1)

其实我和楼上大佬的意思差不多，但换了一种方法。

- 读入不说，截取字串的除了两头的中间。

- 然后再把原串的开头的字符输出。

- 再把截取的字串输出。

- 最后再把原串最后一个字符输出。

还想不出来吗？那就上代码吧：

```cpp分     
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>

using namespace std;
string st,st1;
int main()//完美的开始o(∩_∩)o 
{
    cin>>st;//读入
    st1=st.substr(1,st.size()-2);//截取字串的开头和结尾之间的字母
    cout<<st[0]<<st1.size()<<st[st.size()-1];//一个完美的输出o(∩_∩)o 

    return 0;//完美的结束o(∩_∩)o 
}
```


---

## 作者：TYT_L (赞：1)

说一个中间过程用for循环的做法（说实话是我脑子抽抽了忘了直接用长度）。

把字符串输入之后用一个for循环，从头到尾计数算出来有多少位，再减二。

说实话感觉真的有点多余。

```
#include<bits/stdc++.h> //万能头文件
using namespace std;
int main()
{
	string s;
	cin>>s;
	int i,flag=0;
	for(i=1;i<=s.size();i++)
	{
		flag++; //计数
	}
	cout<<s[0]<<flag-2<<s[s.size()-1]<<endl; //注意下标从0开始
	return 0;
}
```


---

## 作者：xujian (赞：1)

## 已重新进行排版，请管理员重新进行审核

## 做法：string字符串的测长。

### 补充：简单介绍一下字符串string的用法。

string字符串，相对于char字符数组，是方便的许多，但是在许多初学者学习的时候，根本分不清两者的区别，所以我来简单介绍一下有何不同，而又何方便。

1、字符串可以赋值和相加，而字符数组则需要另建函数。列如将两个字符串连起来可以直接s1+=s2，而字符数组则不行。

2、字符串是弹性空间，而字符数组是固定的空间。假如，一串字母需要输入进串s中，字符数组需要知道字母的个数来定义串的大小，而字符串则不需要。

3、字符串可以直接用>、<等符号比较大小，而字符数组必须用strcmp函数。

综上所述，我们便可以看出string比char到底好在哪里了。

上面是给初学者讲解的，下面是代码↓

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;
    cout<<s[0]<<s.size()-2<<s[s.size()-1];
    //输出首字母，中间字母的串长，以及尾字母
    return 0;
}
```

## 注意事项：

1、串首字母是s[0]，尾字母是s[串长-1]，中间字母的串长即使总串长减去首尾两字母的串长，即减去2.

2、s.size()是求串s的串长，用法同s.length()，字符数组需用strlen(s)。

### 全文完，感谢您的阅读，若有疑问，欢迎您在评论区指出。

---

## 作者：sounds_666 (赞：1)

首先[题目在这](https://www.luogu.org/problemnew/show/AT2685)
其次，讲一下思路：

（1）用getline读入，然后再利用字符转的长度输出。
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    string c;
    getline(cin,c);//输入
    printf("%c%d%c",c[0],c.length()-2,c[c.length()-1]);//输出
    //注意字符串下标为零.长度要减去2，因为开头和结尾不能算。
    return 0;
}
```
(2)先读入第一个字符，然后输出。在用while(getchar())读入累加，最后再输出字符长度和最后一个
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    char c,k;
    int ans=0;
    scanf("%c",&c);
    printf("%c",c);
    while(c=getchar()){
    	if(c==' '||c=='\n')break;//如果不是字符了，就跳出。
    	ans++;
    	k=c;//即得记得要替身，因为c最后一次都到了空格或换行
    }
    printf("%d%c",ans-1,k);//输出要减1，因为把最后一个也读进去了。
    return 0;
}
```
（3）思路同（2），只不过是用scanf输入，不多解释。
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    char c,k;
    int ans=0;
    scanf("%c",&c);
    printf("%c",c);
    while(scanf("%c",&c)!=-1){
    	//记住cin输入失败返回0，scanf输入失败返回-1
    	if(c==' '||c=='\n')break;
    	ans++;
    	k=c;
    }
    printf("%d%c",ans-1,k);
    return 0;
}
```





---

## 作者：Loren_Mariano (赞：0)

这是一道考察字符串掌握的题目
（看看你有没有听课）
 
 整体思路：可以将第一个字母和最后一个字母用
 两个变量存起来，再用for扫一遍统计中间字母的个数，最后在组合起来输出(其实也不难）
 
 首先，我们要学会如何求一个字符串的长度。


string类型：
```cpp
len=s.size();//len是长度的缩写，s是一个string类型的变量，.size()的用法适用于string类型
```

char类型：
```cpp
len=strlen(s);//s是一个char类型的变量，strlen的用法适用于char类型
```

### 在这里，我们可以用string类型的

## 上代码！

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<string>
#include<cmath>//一波头文件【cstring和string务必打上】
using namespace std;
string s;//定义一个string类型的变量
char fz,fz1;//fz用来存第一个字母，fz1用来存最后一个字母
int sum;//用来统计首位之间字母的个数
int main()
{
	cin>>s;//输入这个字符串
	 fz=s[0];//字符串下标从零开始
	 int len=s.size();//用上我们上面说的求一个字符串的长度的方法
	 fz1=s[len-1];//字符串最后一位的下标是长度-1
	
	for(int i=1;i<=len-2;i++) sum++;//从下标1开始，到长度减2，用sum来统计个数
	
	cout<<fz<<sum<<fz1;//输出fz（第一个字母）
    //sum（中间字母的个数）和fz1（最后一个字母）
	
	
	
	return 0;//完美结束！
}
```

DALAO们有什么建议，欢迎评论！

## 一道岛国水题。。。qwq








---

## 作者：Aw顿顿 (赞：0)

这个题目是入门，考察字符串

当然，也有一道CF的题与此很像

这道题就是：[CF71A](https://www.luogu.org/problem/CF71A)


```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int main()
{
	cin>>a;
	cout<<a[0]<<a.size()-2<<a[a.size()-1]<<endl;
	return 0;
}
```
输入字符串

输出第一个字符，长度-2（去头去位），最后一个字符

解决!   $Over$

AT进口题一定注意换行

关于字符串长度

有这几点可讲：

1. string类型可以用a.size()
2. string 类型还可以用a.strength()
3. char数组类型可以用strlen(a)

注意需要头文件
#include<cstring>

---

## 作者：I_will (赞：0)

### 此题（不）是我开，此解是我栽，要想抄题解，留下点赞来。~~多押韵~~

----------


* 输出要求： 首字母+中间字母的数量+尾字母
* 输入：internationalization
* 过程：i    18个字母      n
* 输出：i+18+n---->i18n
--------

献上~~不一样的~~程序：
```
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
string x;
int o;
char a,b;
int main()
{
	cin>>x;
	a=x[0],b=x[x.size()-1];
	for(int i=1;;i++)
	{
		if(b==x[i]&&i>x.size()-2)break;
		o++;
	}
	cout<<a<<o<<b<<endl;
       	return 0;
}
    ```

---

## 作者：黯黑の夜 (赞：0)

不解释，直接上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int len;
    char a[1001];
    cin>>a;
    len=strlen(a)-2;
    cout<<a[0]<<len<<a[strlen(a)-1]<<endl;
    return 0;
}
```

# 别忘了换行! ! !

---

## 作者：zzhz (赞：0)

又是1道水题，找出第1个和最后1个字符即可       
代码如下：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
char s[100001],start,end;
int l;
int main(){
    cin>>s;//输入
    start=s[0];//s中第1个字符
    l=strlen(s);//l是s的长度
    end=s[l-1];//s中最后1个字符
    cout<<start<<l-2<<end<<endl;//输出
    return 0;//结束
}
```


---

## 作者：TCZN (赞：0)

这题连pascal题解都没有？？？蒟蒻补上再说

**思路**：运用pascal的字符测长函数length，将答案分成三个部分，分别输出第一个字符，中间的数字就是这个字符串的长度减去头和尾即为减去2，最后输出这个字符串的最后一位
```pascal
var
  n:string;  //极致pascal代码仅6行
begin
 readln(n);
  write(n[1],length(n)-2,n[length(n)]);//合并输出
end.
```
这是第一篇pascal题解，管理大大求过qwq


---

## 作者：Happy_Dream (赞：0)

这道题不难所以不毕紧张。

基本思路：

第一步：求出首字母。

第二部：求出除去首字母和末子母之后字符串的长度，直接将长度减二即可。

第三部：求出末子母。

直接上代码：
***
```cpp
#include <iostream>//头文件
using namespace std;
int main()//主函数
{
	string a;//定义一个字符串
	cin>>a;//输入字符串
	cout<<a[0]<<a.length()-2<<a[a.length()-1]<<endl;//先输出首字母，在输出除去首字母和末子母之后字符串的长度，后输出末字母。一定要还行。
	return 0;//华华丽丽的结束
}
```
***
最后讲一下.length()的用法吧。

用途：求出字符串长度

用法：在.length()前加上字符串名称即可。

其他：

每计算一次length都要花一次时间，所以最好在前面定义一下比如说：int la=a.length()或int lb=b.length()等。这样可以减少运行时间。


That's All.
***
不见不散！

---

## 作者：BCZSX (赞：0)

~~于是我来水一波恶意评分题目的题解了~~

大概题意：输入一个字符串，将这个字符串的第一个和最后一个字母中间的字母个数替换为数字，再将其输出。
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int len;
char s[110];
int main()
{
    scanf("%s",s);//读入字符串
    len=strlen(s);//得到长度
    printf("%c%d%c",s[0],len-2,s[len-1]);//按照题意输出
    return 0;//完美结束
}
```
~~这是我写过最短的题解了~~

---

