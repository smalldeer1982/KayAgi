# [USACO09OCT] Even? Odd? G

## 题目描述

Bessie那惨无人道的二年级老师搞了一个有 $N$ 个正整数 $I$ 的表叫Bessie去判断“奇偶性”（这个词语意思向二年级的学生解释，就是“这个数是单数，还是双数啊？”）。Bessie被那个表的长度深深地震惊到了，竟然跟栋栋的泛做表格一样多道题！！！毕竟她才刚刚学会数数啊。

写一个程序读入 $N$ 个整数，如果是双数，那么在单立的一行内输出 `even`，如果是单数则类似地输出 `odd`。

## 说明/提示

**【样例解释】**

两个整数：$1024\text{ 和 }5931$

$1024$ 可被 $2$ 整除，$5931$ 不能

**【数据范围】**

$1\le N \le 100，1\le l_j \le 10^{60}$

## 样例 #1

### 输入

```
2 
1024 
5931 
```

### 输出

```
even 
odd 
```

# 题解

## 作者：woshishei (赞：76)

$\text{Upd. on 2020/2/7} $ 使用了 $\LaTeX$，修改了注释排版

------------


这道题有很多人得 50 分，是因为题目给出的数据很大（$1 \le l \le 10^{60}$)，用 `long long` 也会爆掉。

我用**字符串**做的。我的思路很简单，就是判断每个字符串的最后一位**数字**的奇偶性就行了。

附上C++代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>              //strlen()函数头文件
using namespace std;
int main()
{
    int n,i,len;               //len为每个字符串的长度
    char c[65];                //存储字符串，由于我是逐条输出（输入一个输出一个），所以每次只记一个字符串就行了
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>c;                //输入字符串
        len=strlen(c);         //判断字符串长度
        if((c[len-1]-'0')%2==0)//判断最后一位数字的奇偶性
            cout<<"even\n";
        else
            cout<<"odd\n";
    }
    return 0;                   
}
```

**本人只是蒟蒻一枚，更多方法求dalao指教~**


---

## 作者：HFColin (赞：29)

这道题按照楼下诸位大佬所说会爆

我不信邪信long long

结果炸了

这是个假入门

据楼下诸大佬所阐述用字符串做

一是浪费空间

二是如果出题人丧心病狂出个很长很长长到你怎么存都会MLE

既然是判断奇偶只有最后一位有意义

那为何前面的几位要存下来呢？

我们可只用一个字符存

``` cpp
#include<cstdio>//用getchar读入比较scanf快，最弱的快速读入int型就是不用scanf，一个一个字符用getchar读入
using namespace std;
int main()
{
    long long n;
    char x,s;
    scanf("%lld",&n);
    getchar();//既然要用getchar就要吞掉输入完n后的回车
    //前面两行可用n=0;while (((x=getchar())!=EOF)&&x!='\n') n=n*10+x-'0';
    //即正整数的快速读入
    while (n--)
    {
        scanf("lld",&x);
        while (((x=getchar())!=EOF)&&x!='\n') s=x;
        //读入x，若x不是回车且读入进了东西，将s赋值为x，不然停止循环
        //s储存着这个数的最后一位
                //EOF指End Of File，就是这个输入完了，读不到任何东西
                //！=EOF是很有用的，如果出题人丧心病狂输入完不打回车（十分常见），没有任何东西读入，getchar就会返回EOF（即-1）你就会死循环
                //我曾去掉！=EOF重新提交，最后全部TLE
        s-='0';
        if (s%2) printf("odd\n");
        else printf("even\n");
    }
    return 0;
}
```

---

## 作者：学而思李老师 (赞：28)

# P2955 [USACO09OCT]奇数偶数Even? Odd? 

相信很多童鞋都会像我一样，做此题时第一遍写的代码都是这样的：

```cpp
#include <cstdio>
using namespace std;
int main(){
    int n, tmp;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &tmp);
        if(tmp % 2 == 0){
            printf("even\n");
        } else{
            printf("odd\n");
        }
    }
    return 0;
}
```
然后，怀着一颗自信的心提交上去，结果。。。????

![50分](https://cdn.luogu.com.cn/upload/pic/71223.png )

然后。。一定有同学打开了题解，看看自己为什么错了。其实，错误的地方在这里：

![]( https://cdn.luogu.com.cn/upload/pic/71226.png )

$10^{60}$？？？貌似没有数据类型可以存储这么大的整数额......如果你有这个疑问，那么你来对地方了。

正文开始之前，我有需要声明你需要的前铺芝士：

- 会使用数组（包括定义、初始化、输入输出和下标就行了）

- 会使用结构体（仅供第二部分使用）

- 小学二年级数学（加减法竖式、单数与双数）

- 小学三年级数学（乘除法竖式）

下面，我宣布，正文开始！

## 第一部分：字符串
相信很多学过Python等语言的童鞋一定对字符串不陌生，因为这些语言中，字符串的定义非常简单，而且有许多内置函数对字符串进行处理。但是，作为一个比较基础的语言，C++的字符串通常被定义为字符数组（数组还不懂的童鞋，请自己查询资料，或在我的blog中浏览[这篇文章](https://www.luogu.org/blog/lch-zhazha/ke-yi-yong-lai-xun-lian-shuo-zu-di-ti-mu)）

注：分割线内的内容非常简单，如果你自认为自己时dalao可以跳过


------------



就以这道题为例，判断一个数是否为奇数或偶数，只需要看它的个位数（不懂的问问自己小学数学是怎么学的）是不是奇数或偶数。所以，我们可以把每一个数看成是一个字符串，取出它的最后一位进行判断即可。那怎样去取出数组的最后一位呢？在头文件cstring里面，有一个函数叫strlen，用来求出一个字符串的长度，下面介绍以下这个函数的具体用法：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
    char str[105] = "ILoveLuogu"; //定义一个字符数组
    printf("%d", strlen(str));	//获取一个字符数组的长度并输出
}
```
运行上面的程序，我们发现，strlen函数返回的值并不是我们声明数组时的大小，而是字符串真正的长度。所以，提取出字符串最后一位的程序我们可以这么写：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
    char str[105] = "ILoveLuogu";
    printf("%c", str[strlen(str) - 1]);
}
```
最后，可能很多萌新还会问这样的问题：这个字符数组的长度不固定，我不能使用循环进行输入和输出，怎么办？C/C++语言中，字符串的读入时这样的：

```cpp
char a[105] = "LuoguIsTheBestOnlineJudge";
C/C++语言：
scanf("%s", a);
printf("%s", a);
C++语言专属（iostream流输入输出）
cin >> a;
cout << a;
```

关于字符串，除了数组的注意事项外，我们还需要注意以下几点：

1. 本人强烈推荐！！！字符数组的下标一定从0开始用！因为如果从1开始的话，第0个字符就是'\\0'，这样使用strlen和输出的时候会出现异常。

2. 字符串的输入输出遇到空格、换行、制表符进行终止，不把空格、换行、制表符输入在内。如果需要进行以行为单位的输入输出，可使用gets、puts和getline。为了节省篇幅，各位可以自行这几个函数的用法。
------------
最后，贴一个不是很好看的代码和注意事项。如果想要简化代码，马上讲到的知识点会帮助你。
```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
char a[10000001];
int main(){
    int i, n;
    scanf("%d", &n);
    for(i = 1; i <= n; i ++){
        scanf("%s", a);
        switch(a[strlen(a) - 1]){
            case '0' : case '2' : case '4' : case '6' : case '8' :
                printf("even\n");
                break;
            case '1' : case '3' : case '5' : case '7' : case '9' :
                printf("odd\n");
                break;
            default :
                printf("error\n");
                return 0;
        }
    }
    return 0;
}
```
注意事项：switch-case语句里面的单引号不要弄丢！虽然弄丢了不会报错，但是马上你就会知道这样的问题！让我们有请我们的救星——ASCII！

### ASCII
> ASCII ((American Standard Code for Information Interchange): 美国信息交换标准代码）是基于拉丁字母的一套电脑编码系统，主要用于显示现代英语和其他西欧语言。它是最通用的信息交换标准，并等同于国际标准ISO/IEC 646。ASCII第一次以规范标准的类型发表是在1967年，最后一次更新则是在1986年，到目前为止共定义了128个字符 。

> ——百度百科

ASCII，其实就是一张表格，下面给大家展示一下：
![ASCII码表](https://cdn.luogu.com.cn/upload/pic/71268.png )

计算机存储一个字符类型，并不是存储这个字符，而是存储**这个字符所对应的ASCII码**。这就是一些编程书上写出char类型的数据范围是0~128的原因（现在你懂了吧）同样，char类型的变量也可以当成一个int类型的变量进行使用。这个表格不需要背下来，在NOIP中，运行下面简简单单的程序，就可以把ASCII表打印出来。

```cpp
#include <cstdio>
using namespace std;
int main(){
    for(int i = 0; i < 128; i ++){
        printf("%4d %c\n", i, i);
    }
    return 0;
}
```
注：如果运行这个程序后听到你的计算机响了一声，不要担心，不是这个程序对你的计算机造成了损害，而是ASCII码中有一个对应的字符是可以发出声音的~~我也不知道是哪一个~~。

所以，这题的switch-case语句也可以用ASCII码简化。因为0，2，4，6，8所对应的ASCII码都是偶数，而1，3，5，7，9对应的是奇数。所以只用判断这个字符是不是偶数就可以了（严谨点说，就是字符对应的int类型数值）。
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
char a[10000001];
int main(){
    int i, n;
    scanf("%d", &n);
    for(i = 1; i <= n; i ++){
        scanf("%s", a);
        if(a[strlen(a) - 1] % 2 == 0) printf("even\n");
        else printf("odd\n");
    }
    return 0;
}
```
讲完了字符串，下面再来讲一讲高精度。
## 第二部分：高精度
注：这部分C语言请跳过，因为只有C++可以使用这种方法。

### 高精度的原理
一开始，我说过C++语言里没有可以撑下$10^{60}$的数据结构，那么，学过结构体的同学们可能就想：我们能不能创建一个结构体存下这么大的一个数值呢？

当然可以！而且我们还能像int类型一样一样方便！（下一部分会详细叙述）

想知道高精度的原理，首先问一下各位同学们怎样计算下面的式子呢？

1. 13234+123412
2. 672367676-234543
3. 898989*767676
4. 10000/12321

没错是使用竖式！~~看起来我想小学数学老师~~我们可以创建一个类型，所有的计算都通过模拟竖式的方式进行，再加上重载运算符......
### 重载运算符
同样，我们也可以对我们自定义的类型创建一个运算符，为节省版面，大家可自学。这样，我们的大整数类型就可以和int类型一样方便啦！

所以，大整数类型模板可以戳[这里](https://www.luogu.org/paste/xn94dtv9)（这个模板包括几乎所有int类型运算符，码量比较大，所以还是放到云剪贴板里面合适一些。

### 大整数重载运算符做法
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
struct bign{    //这里只需要判断最后一位是否为偶数
    char num[100005];
    bign(){
        num = "";
    }
    bool iseven(){
        return num[strlen(num) - 1] % 2 == 0;
    }
}
istream& operator >> (istream& in, bign a){
    in >> a.num;
    return in;
}
int main(){
    int n;
    bign tmp;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> tmp;
        if(tmp.iseven()){
            printf("even\n");
        } else{
            printf("odd\n");
        }
    }
    return 0;
}
```
不知不觉，我的手指已经在键盘上跳舞三个小时了。希望各位看来我的题解都能学会字符串和大整数类型。最终，祝各位：
$while(true)Noip2019.^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++^{rp++}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++}}_{Luck++Luck++}}}_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++_{score++}}}}}}}}}}}}}}}}}};$！！！

---

## 作者：yuzhechuan (赞：11)

-----------------------------------------------------我是代码分割线--------------------------------------------------------

```cpp
#include <bits/stdc++.h>//万能的，真方便
using namespace std;

int n;//本人喜欢在main外面定义，不用清0

int main()
{
	scanf("%d\n",&n);//
	for(int i=1;i<=n;i++)
	{
		char c[100];//定义一个串
```



 ## **重点来了**！！！



```cpp
		scanf("%[^\n]",c);
        //%[^]表示读一个串直到集合[]内的东东(也就是换行)为止(换行不读)
		getchar();
        //易错点：因为没读，所以要把换行getchar读一下
		if((c[strlen(c)-1]-'0')%2==0) cout<<"even"<<endl;
        //strlen求串长，因为从0开始，所以减一得末位下标
		else cout<<"odd"<<endl;
        //字符末位减字符0，得整型末位(C++真方便)根据小学知识：偶数末位也是偶数，模2判奇偶得出结果
	}
}
```
-----------------------------------------------------我是结束分割线--------------------------------------------------------
### 第二次了，给本魔芋过了吧~~~（楚楚可怜.jpg）

---

## 作者：AC机 (赞：10)

我们可以发现，这题的数据已经超过了long long了。

所以，我们可以用字符来做，只要学过小学数学都知道只要最后一位是偶数，这个数就是偶数，所以我们在判断的时候只要判断最后一位就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[10000000];/*这个数组太大了，所以得开在main函数外面*/
int main ()
{int i,n;
scanf("%d",&n);//先读入行数
for (i=1;i<=n;i++)
{scanf("%s",a);//
if (a[strlen(a)-1]%2==0)//只需判断最后一位即可。
{printf("even\n");//一定要输出换行！
}
else {printf("odd\n");}}
return 0;
}
```

第三篇题解求过！

---

## 作者：HikariForever (赞：6)

在介绍这篇题解时，我们要先了解一个东西：字符串流。

什么是字符串流呢？字符串流的头文件是sstream.h，今天我们要了解的是其中的stringstream。

stringstream有一个俗称：万能容器，也就是说这个容器可以装入任何类型的变量的值，它是这样定义的：
```cpp
	stringstream a;

```
那么定义后，我们就需要把一个变量的值放入这个万能容器中，存值方法如下：
```cpp
stringstream a;
char b;
a<<b;
```
要把万能容器中的值赋值到另一个变量中，方法如下：
```cpp
stringstream a;
char b;
a<<b;
int c;
a>>c;
```
这样的话，如果b是一个数字，那么c中就会是那个数字，否则会是那个字符的ASCLL码值。
这样一来，这道题就很简单了，因为这道题要求判断奇偶，而这道题数据又是高精度范围，所以可以这样写：
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[1001];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",&c);//字符串读入
        stringstream box;//定义stringstream
        int l=strlen(c)-1;
        box<<c[l];//将最后一位装入stringstream中
        int key;
        box>>key;//将stringstream中的值取出
        if(key%2==0)cout<<"even"<<endl;//对值进行判断
        else cout<<"odd"<<endl;
    }
    return 0;
}
这样写的话代码会比较短，也很方便，大家学会了吗？
```

---

## 作者：Karry5307 (赞：5)

首先，如果你细心，会发现这题数据超过long long int,我个人选择字符串数组，先定义一下：

```cpp
int count,i=0;
    cin>>count;
    string num[count];
    int eoo[count];
```
注意到num[count]是string类型的！
接下来，一遍一遍循环：

```cpp
for(i=0;i<count;i++)
    {
        cin>>num[i];
    }
```
接下来有点难懂：
```cpp
for(i=0;i<count;i++)
    {
        eoo[i]=num[i][num[i].length()-1]%2;
    }
```
对于每一个在num数组中的元素，它的奇偶性保存在eoo对应的索引里，num[i].length()-1是求该数的末位数字，num[i][num[i].length()-1]是指在num数组里的索引i的元素的末位（length()要用头文件cstring），num并不是一个二维数组，eoo对应的索引赋值为1或0，看这个数奇偶性，简单粗暴！
最后是判断：

```cpp
for(i=0;i<count;i++)
    {
        if(eoo[i]==1)
        {
            cout<<"odd"<<endl;
        }
        else
        {
            cout<<"even"<<endl;
        }
    }
```
献上完整代码：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    int count,i=0;
    cin>>count;
    string num[count];
    int eoo[count];
    for(i=0;i<count;i++)
    {
        cin>>num[i];
    }
    for(i=0;i<count;i++)
    {
        eoo[i]=num[i][num[i].length()-1]%2;
    }
    for(i=0;i<count;i++)
    {
        if(eoo[i]==1)
        {
            cout<<"odd"<<endl;
        }
        else
        {
            cout<<"even"<<endl;
        }
    }
}
```

---

## 作者：wangye714906 (赞：4)

这道题我开始的时候想的很简单，直接用int定义，结果40分

我很不明白，~~经过旁人提醒，我忽然融会贯通~~，我猜想是数据范围的问题

然后我用了long long，结果50分

于是我就上了高精度（汗）

思路很简单，只需要判断最后一位就行了（小学思路）

上代码


------------
这是蒟蒻的分割线


------------
```
#include<iostream>
#include<cstring> 
using namespace std;
string a;
int main()
{
	long long n;//50分代码的痕迹
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a;
		int la=a.size();
		if(a[la-1]%2==0)cout<<"even"<<endl;//判断最后一位
		else cout<<"odd"<<endl;
	}
	return 0;//程序再见
}
```
欢迎大佬改进

欢迎提意见

禁止抄袭，这不是个好习惯

---

## 作者：国服最强关羽 (赞：4)

这题较水，虽然我没有看清楚数据，不过用字符串是一定可以过的

```cpp
var n,i,j:longint;
    a:ansistring;//我在这里对刚学没多久的Pascal萌新解释一下，ansistring是1000位的字符串
 begin
  readln(n);
  for i:=1 to n do
   begin
    readln(a);
    val(a[length(a)],j);//这里吧a的最后一位赋值给j，然后再在下面判断就可以了
    if odd(j) then writeln('odd')
              else writeln('even');
   end;
 end.  

```

---

## 作者：minecraft_herobrine (赞：3)

## int代码

int炸掉了。。所以试试long long？
![](https://cdn.luogu.com.cn/upload/pic/60732.png)

## long long 代码
![](https://cdn.luogu.com.cn/upload/pic/60733.png)

![](https://cdn.luogu.com.cn/upload/pic/60734.png)


## 这题的正确打开方式是。。
# 用字符串QAQ

## string代码
```
#include<bits/stdc++.h>
using namespace std;
string str;
int main()
{
	int n,len,i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		cin>>str;
		len=str.size();
		if((str[len-1]+'0')%2==0) printf("even\n");
		else printf("odd\n");
	}
	return 0;
}
```
~~RP~~翻译质量太差这道题的翻译里没有说数据范围。。我看了原文才发现的
所以本题一定要用string或char[  ]存储，不然只有50分！




**管理大大求过(^_^)**

---

## 作者：寒鸽儿 (赞：1)

### 蒟蒻只能虐红题QaQ
    1.直接暴力就好了丫，不会超时的。
    2.题解里有巨擘说会MLE，其实用在线算法，边读边输出就好了丫。
    3.超过long long是存在的，然而管他丫的，快读模板的读法可以保证最后一位不失真，前面的让他溢出吧，反正最后一位在就能判奇偶性了。
    4.具体看代码和注释
```CPP
#include <cstdio>

using namespace std;

int read(){						//这是一个快读
	int x = 0,f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}

int main(){
	int n = read();
	while(n--){
		if(read() % 2) printf("odd\n");			//直接读入，边读边判边输出
		else printf("even\n");
	}
 	return 0;
}

```

---

## 作者：Michaelwu (赞：1)

第一次写题解~写得不好请指出~

~~我写得可好了~~

这题数据范围超大，一开始我用了**long long**都不行（范围爆掉了）所以就改用了**字符串**

```cpp
#include <iostream>
#include <string>//字符串头文件
using namespace std;
unsigned long long n;
string a[100010];
int main(){
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>a[i];//依次读入
    for (int i=1;i<=n;i++){
        if ((a[i][a[i].size()-1]-'0')%2==0)//这一步是核心：a[i][a[i].size()-1]表示字符串a[i]的第a[i].size()-1位，这里xxx.size()表示xxx的长度（计//算机里第一位是第0位，所以要-1），也就是获取它的最后一位，若%2（取余）得0，则输出为偶数
            cout<<"even"<<endl;
        else
            cout<<"odd"<<endl;//如果不能被2整除，则输出为奇数，换行符千万不能忘
    }
    return 0;
}
```

---

## 作者：zhshh (赞：1)

前面已经说过了，可以用字符串来表示。

那么能不能更简单呢，字符串是使用的最后一位，所以如果使用字符的话，直接略过前面的数（包括第一个数目，我就没动，拿一个无关变量过了一下）

变量使用上char a,b;始终让b保存上一个字符，这样当读到a='\n'时，b为数字末尾，判断b即可

=====补充EOF====

开始以为EOF是一个特殊字符（所以我又写了一个程序getchar()，输入CTRL+Z，出来是-1），但后来百度

>“发现EOF是一个在stdio.h中定义的一个值为-1的常量。关于-1是因为ASCII码范围是0~127，不可能出现-1。EOF不是字符也不是数字，而是作为文件结束的标志，还有就是判断函数调用是否成功比如：作为scanf的一种返回值，当遇到错误或end of file,scanf返回EOF。”
```cpp
#include <iostream>
using namespace std;
int main()
{
    int c;
    cin>>c;
//题目里面给了输入个数（虽然不需要吧，但是也得处理掉）
//在后面就废物利用了下这个变量
    char a,b;
    b=getchar();//cin是不读入换行符的，但是getchar读入，所以这里用b读入换行符
    //下面是正文
    while(a=getchar()) {
        if(a==EOF)break;//详见描述EOF 
        if(a=='\n' ) { //这里\n实际是一个字符
            c=b-'0';
            if(c %2==1) {
                cout<<"odd"<<endl;
            } else {
                cout<<"even"<<endl;
            }
        }
        b=a;//始终让b保存上一个字符，这样当读到a='\n'时，b为数字末尾，判断b即可
    }
}
```
====EOF补充结束====

补充一点感触，突然发现部分题第一个数据如果在使用while(cin或者scanf等等)时真的没什么用（只是有时！！）

按照上面人一些方法（或者其他题），如果使用数组，这时定义数组长度还是有用的


---

## 作者：叫我彪哥 (赞：1)

太年轻了，我一开始没注意数据范围，

C++的string太好用了，注意不要加.h，否则就成了c语言的字符处理函数库了，

看题目一定要仔细！

江西老表留


```cpp
#include<iostream>
#include<string.h>
using namespace std;
int main()
{
    int n;
    string a;
    cin>>n;//输入次数
    int i,l;
    for(i=1;i<=n;i++)
    {
        cin>>a;
        l=a.length(); //计算字符长度，方便判断奇偶（就是看最后个数是不是偶数或奇数）
        if((a[l-1]-'0')%2==0) cout<<"even"<<endl; //因为‘0’也占了最后个空间，所以-1，在判断即可
        else cout<<"odd"<<endl;
    }
    return 0; //哈哈
}
```

---

## 作者：飞翔 (赞：1)

如果你只看了中文翻译，你会漏掉一个很重要的信息——数据范围！

在原题（英文）第一行里，可以找到一个10^60，这就是这些数的范围了。

可以发现用long long/qword根本存不下。

于是想到了字符串。

字符串只要判断最后一位即可。

```cpp
var s:ansistring;
i,n,p:longint;
begin
readln(n);
for i:=1 to n do begin
 readln(s);
p:=ord(s[length(s)])-48;if p mod 2=0 then writeln('even') else writeln('odd');
end;
end.
```

---

## 作者：_YRH_ (赞：1)

其实基本思想就是只要判断最后一位的奇偶性就好了，用字符串存一下找最后的就好了，简单粗暴

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int i,j,k,m,n;
char s[100];
int main(){
    scanf("%d",&n);
    while(n--){                                   因为有多组数据，所以循环输出
        getchar();
        gets(s);
        k=strlen(s);                          //求长度
        if((s[k-1]-'0')%2==0)           //判断奇偶性
            printf("even\n");
        else 
            printf("odd\n");
    }
    return 0;
}
```

---

## 作者：syx2000121910 (赞：1)

为了防止炸变量范围，可以直接读入时候判断最后一位，这个的处理可以在读入优化中进行。

QwQ
```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cmath>
#define LL long long
using namespace std;
LL read(){
    LL a=0,f=1;char c=getchar();
    int fa;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){a=a*10+c-'0';fa=c-'0';c=getchar();}
    return (fa%2); 
}
int main(){
    LL n;
    cin>>n;
    while(n--){
        LL tmp=read();
        if(tmp==1)cout<<"odd"<<endl;
        else cout<<"even"<<endl; 
    }
}
```

---

## 作者：早右昕 (赞：1)

###给你们补充一些位运算的知识

```cpp
int main()
{
    int n,a;
    char num[10010];
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",num);
        printf((num[strlen(num)-1]-'0')&1?"odd\n":"even\n");
    }
    return 0;
 } 
IF ( A&1 ) ,THEN A%2==1

IF ( !A&1 ), THEN A%2==0

```

---

## 作者：microchip (赞：0)

## 本蒟蒻第二次发题解
刚开始做这道题，~~哇，好简单那~~……what？40分？……好吧，一定是不够大，我用unsigned long long int……还是没满分？？？……最后，我下载了一个数据，那个天文数字把我都看晕了，我才明白，这不是考你分支，这是考你字符串……

------------
思路挺简单的，分为三步。第一步，输入一个字符串（~~太简单了直接跳过~~）

------------
第二部，判断最后一个字符是啥，然后把他转数字（本题核心）。
```cpp
m=a[a.size()-1]-'0';/*由于字符串就是一个数组，所以可以直接找到最后一个字符是啥，最后减去0对应的ASCII码值即可*/
```

------------
现在知道最后一位的数字，最后一步就是判断奇偶性了（~~太简单了直接跳过~~）

------------
上AC代码，~~请大佬趁热放心食用~~
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,m;
	cin>>n;
	string a;
	for(int i=0;i<n;i++)//.size()
	{
		cin>>a;
		m=a[a.size()-1]-'0';
		if(m%2==0)
			cout<<"even"<<endl;
		else
			cout<<"odd"<<endl;
	}
	return 0;
}
```

---

## 作者：眼镜犬 (赞：0)

```
#include<bits/stdc++.h> //万能头，简单又省事 
using namespace std;
char a[10000];//注意，他说数据会很大，所以long long是不行的， 只能开数组 
int main(){
	long long n;//这里是个数 
	cin>>n;
	while(n--){//循环输入 
		cin>>a;//没有空格，可以直接cin,我是让他每一次覆盖，不然要开n个数组 
		if(   a[strlen(a)-1]=='1'//有点打表的样子呢 ，个位是1,3,5,7,9的就是偶数 ~~废话，谁不知道~~
			||a[strlen(a)-1]=='3'
			||a[strlen(a)-1]=='5'
			||a[strlen(a)-1]=='7'
			||a[strlen(a)-1]=='9'
		){
			cout<<"odd"<<endl;//这有个坑，奇数输出“odd”，偶数才输出“even” 
		}else{
			cout<<"even"<<endl;
		}
	}
    return 0;//我爱return!!! 
}

我试过，int是40分，long long 是50分，数组是100分（相信很多人都因为这个来看题解的吧）

---

## 作者：胡哲之 (赞：0)

在string头文件里有许多~~乱七八糟的~~函数

其中的size函数特别好用，可以读取string的长度

而且string没有长度限制

所以不用高精就能轻轻松松过了

-----------------------------------我叫代码分割线-----------------------------------

```cpp
//sbtxhzz 294
#include <iostream>
#include <string> //字符串名.size()的头文件
using namespace std;
int main()
{
	string a;
	int n;
	cin >> n;
	for (int i = 0; i < n; i ++)
		{
			cin >> a;
			int t = a[a.size() - 1]; //a.size()读取a字符串长度，-1后指向a字符串最后一位
			if (t % 2 == 0) 
				cout << "even" << endl;
				else
					cout << "odd" << endl; 
		}
	return 0;//完美结束
 }

```
~~管理员求过~~

---

## 作者：gipsy (赞：0)

本人刚开始做时，只弄到50分，看了篇题解之后才明白有一部分数据是高精度数。但本人想偷个懒。

那么，我们来分析一下奇数与偶数：

	奇数：不能被2整除（模2余1）
    偶数：能被2整除
    
那当然是这样啦！

再往下分析：


	奇数：首位数字不能被2整除（是奇数）
    偶数：首位数字能被2整除（是偶数）

所以……

我们只需要首位数字。

因为数字的ASCLL码也是按一定规则连续排列的，

so:这题用字符串做最好。

我们知道：0的ASCII码十进制值是48，所以：


在某个数字以字符的形式存储时：

	若其十进制ASCLL码值为偶数：
	其为偶数
    否则为基数

进一步推敲：

	字符串尾字符ASCII码值模2余0：偶数
    字符串尾字符ASCII码值模2余1：奇数
    
下面是c++代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1[1000];
int n,i;
int main()
{
    scanf("%d",&n);
    for(i=0;i<n;i++)
        cin>>s1[i]
;    for(i=0;i<n;i++){
        if(int(s1[i][s1[i].length()-1])%2) printf("odd\n");
        else printf("even\n");
    }
    return 0;
}
```


当然啦，也有毫不畏惧高精度的Python3代码

```python
n = int(input())
for i in range(0,n):
    x = int(input())
    if x % 2 == 0:
        print('even')
        continue
    print('odd')
```


---

## 作者：利欲熏心lyxx (赞：0)

直接判断奇偶性后输出即可。不过要注意整数的长度超过了long long，所以要用字符串。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l;//n是整数的个数,l是字符串的长度
string a;//因为1<=I<=10^60，long long也≤9223372036854775807，所以用string字符串
int main()
{
	cin>>n;//输入整数的个数
	for(int i=0;i<n;i++){
		cin>>a;//读入字符串
		l=a.size();//l赋值为字符串的长度
		if((a[l-1]-'0')%2==0/*判断奇偶性*/)cout<<"even\n";//输出even后换行
		else cout<<"odd\n";//输出odd后换行
	}
	return 0;
}
```

---

## 作者：_Cog_ (赞：0)

经过亲身尝试后，我发现Python的变量强大的不行，用Python可以直接模拟AC。

这里给出直接模拟的代码:
```python
n = int(input())

for x in range(0, n):
    a = int(input())
    if a % 2 == 0:
        print("even")
    else:
        print("odd")
```

---

## 作者：JustinRochester (赞：0)

[题目](https://www.luogu.org/problemnew/show/P2955)

我看了一下题解区的各位大犇。

嗯......实际上根本不需要用到字符串......

本题的奇偶判定只要看最后一位是奇数还是偶数就行了。所以读入的时候只要保存最后一位就可以了（可以参考读入优化的思想）。

其次补充一下位运算。如 $7$ 的 $2$ 进制为 $1111_{(2)}$ , $1$ 的为 $0001_{(2)}$ 。根据二进制运算原则。“$ \& $”运算符是当两者同一位都为 $1$ 时才输出 $1$ ，否则输出 $0$ 。即

$ 0\&1=0 $

$ 0\&0=0 $

$ 1\&0=0 $

$ 1\&1=1 $

（所以  $ 7_{(10)} \& 1_{(10)}=1111_{(2)} \& 0001_{(2)}=0001_{(2)}=1_{(10)}$ ）


而所有奇数的 $2$ 进制末位都为 $1$ 。因为奇数 $n=\cdots\dots+1 \times 2^0$ 所以在其二进制最后一位一定为 $1$ 。偶数则最后一位一定不为 $1$ 。不相信的，各位还可以用小学二进制数求法来验证一下。


所以奇数 $n\&1=1$ ，偶数 $m\&1=0$ ；


因此，根据上面的分析，我们只要写一个函数返回输入的最后一个数字，并用 $n&1$ 判断其为奇数还是偶数即可。


------------

那我这个蒟蒻就放代码了

```cpp
#include<cstdio>
#include<cctype>
using namespace std;
int read(){
    int abs=0;char c=getchar();//abs存最后一个数字，c将数字以字符的形式输入
    while(!isdigit(c)) c=getchar();//判断字符是否为数字字符，防炸
    while(isdigit(c)) abs=c-'0',c=getchar();//保存末位
    return abs;
}
int main(){
    int n;scanf("%d",&n);
    while(n--){
        int x=read();
        printf((x&1)?"odd\n":"even\n");
    }
    return 0;
} 
```

最后安利一下 [本蒟蒻的博客](https://www.luogu.org/blog/JustinRochester/)

---

## 作者：曦行夜落 (赞：0)

这题有好几个方法

方法1：高精

放心我是故意的，直接字符串形式读入，然后逐位转换

for i in range(1,len)

  a[i]=s[i]-48//48是0的编码，这样就可以把字符转成数字

然后判断最后一位是不是奇数

更麻烦一点的，高精度除法，本蒟蒻也不会

当然如同刚才看到的，只要判断最后一位即可。。。所以——

方法2：逐个字符

就是逐个字符读入，直到碰到换行符，这时候判断

给大家介绍一个技巧，我编程时没想到，那就是其实用编码就可以判断一个数的奇偶，因为0是48，所以偶数都是偶数编码，奇数亦然

这种方法的框架

while not eoln

```cpp
    c=getchar()
if c%2==1
  print 'odd';
else
   print 'even';
```
方法3：字符串
最多也就60长度，直接string

然后判断最后一位即可（本蒟蒻的方法）

贴方法3代码：


```cpp
var
  s:string;
  i,n,k:longint;
begin
  readln(n);
  for i:=1 to n do
    begin
      readln(s);
      k:=ord(s[length(s)])-48;
      if odd(k) then writeln('odd') else writeln('even');
    end;
end.
```

---

## 作者：皮皮虾letusgo (赞：0)

额
这题数据很大，要用字符串读入；

因为它是先全部读入，再判断，所以要用数组存储；

上代码：

```cpp
#include <iostream>//普通头文件
#include <string>//字符头文件
using namespace std;
int main ()
{
    int n;
    cin>>n;
    bool p[n+1];//定义数组存储
    for (int i=1;i<=n;i++)
    {
        string s;
        cin>>s;
        int x;
        x=s.size ();//字符串长度
        if ((s[x-1]-'0')%2==0) p[i]=0;//若为偶数定义为0
        else p[i]=1;//若为奇数定义为1
    }
    for (int i=1;i<=n;i++)
    {
        if (p[i]==1) cout<<"odd"<<endl;//输出奇数
        else cout<<"even"<<endl;//输出偶数
    }
    return 0;
}
完美结束！！！
```

---

## 作者：xukuan (赞：0)

第一眼看到：

if odd(i) then writeln('odd') else writeln('even');

正准备提交时：

###1 <= I <= 10^60

又想到高精度，正准备打代码时——

#除以2的余数看最后一位即可！




```cpp
var
 i,n:longint;
procedure work;
 var
  s:ansistring;
  n:longint; 
 begin
  readln(s);//那个数
  val(s[length(s)],n);//取最后一位并且转换为数字
  if odd(n) then writeln('odd') else writeln('even');//判断
end;
begin
 readln(n);
 for i:=1 to n do work;
end.
```

---

## 作者：Nightriver (赞：0)

因为这道题用数字可能会超过范围，所以这道题用字符串

通过扫描字符串的最后一位的数字（用odd）来解这道题

代码如下：

```cpp
var
  n,i,j,k,t,s,r:longint;
  st:array[1..100051]of ansistring;
begin
  readln(n);
  for i:=1 to n do readln(st[i]);//先读取各个数字（字符串形式）
  for i:=1 to n do begin
    k:=length(st[i]);//求字符串长，以便读取最后一位
    if (ord(st[i,k])-48) mod 2=0 then writeln('even')//用最后一位能否被2除来判断
    else writeln('odd');
  end;
end.//结束程序
```

---

## 作者：KillerXu (赞：0)

这道题必须用字符串，10的60次方用长整形什么的都不够，但用字符串就可以轻松解决~~

```cpp
#include<stdio.h>
#include<string.h>//字符串函数库
int main()
{
    char a[1001];
    int n,i;
    scanf("%d\n",&n);//若是像我一样用gets读入字符串，务必读入数字个数后加\n换行，否则按回车也算读入了一个数
    for(i=1;i<=n;i++)
    {
    gets(a);
    if((a[strlen(a)-1]-48)%2==0) printf("even\n"); else printf("odd\n");}//此时判断最后一位数是否偶数，strlen求字符串长度，字符串从a[0]开始，所以减一，字符0~9的ascll码-48得原数。
    return 0;
}
```

---

## 作者：Bartholomew (赞：0)

**是字符串的处理**\_0. \_


```cpp
#include <bits/stdc++.h>//万能头文件使用
using namespace std;
string a[10000];//将数字当做字符串来使用
int b[10000];//利用字符串a的末尾来储存
int main() {
    int n;//共有几个数字
    string s;//字符串
    cin>>n;//输入几个数字
    for(int i=0;i<n;i++)cin>>a[i];输入数据
    for(int i=0;i<n;i++)
    {s=a[i];//转换
    int len=s.length();//记录字符串下长度
      b[i]=s[len-1]-48;//利用ascii表来转换
      if(b[i]%2==0)cout<<"even"<<endl;//被2整除就是偶数
      else cout<<"odd"<<endl;//不是就是奇数
    }
}
```

---

## 作者：剑气箫心 (赞：0)

pascal的题解只有一个，我来个浅显易懂的

变量存不下，判断最后一个，入门级别语言风格

```pascal
var
 n,i,kkk:longint;
 strk:string;
begin
      readln(n);
      for i:=1 to n do 
            begin
                     kkk:=0;           //注意这个标记一定要赋为零，不然就不对了
                     readln(strk);
                     if strk[length(strk)]='0' then begin kkk:=1; writeln('even'); end;      //kkk为标记，偶数为1
                     if strk[length(strk)]='2' then begin kkk:=1; writeln('even'); end;
                     if strk[length(strk)]='4' then begin kkk:=1; writeln('even'); end;
                     if strk[length(strk)]='6' then begin kkk:=1; writeln('even'); end;
                     if strk[length(strk)]='8' then begin kkk:=1; writeln('even'); end;
                     if kkk=0 then writeln('odd');            //如果不是偶数就odd
           end;
end.    
```

---

## 作者：longyuxuan (赞：0)

这一题很简单，除了用字符串读入就没什么注意了。

###PS.判断奇偶数只要看最后一位就行了

```cpp
#include<iostream>
#include<string>
using namespace std;
void hehe(string x)
{
    switch(x[x.size()-1])//不知怎么回事想到了switch
    {
        case '1':cout<<"odd"<<endl;break;
        case '2':cout<<"even"<<endl;break;
        case '3':cout<<"odd"<<endl;break;
        case '4':cout<<"even"<<endl;break;
        case '5':cout<<"odd"<<endl;break;
        case '6':cout<<"even"<<endl;break;
        case '7':cout<<"odd"<<endl;break;
        case '8':cout<<"even"<<endl;break;
        case '9':cout<<"odd"<<endl;break;
        case '0':cout<<"even"<<endl;break;//判断奇偶数然后直接输出
    }
}
string a[10000001];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
      cin>>a[i];
    for(int i=1;i<=n;i++)
      hehe(a[i]);//判断~
    return 0;
}
```

---

## 作者：SAZZM (赞：0)

第一，这题的数据很大，可以赶得上高精，要用字符串读入。第二，这题的判断的数量很多，最好采取边读边判断。第三，判断一个数是奇数还是偶数只用看最后一位能不能被二整除即可，想这样做可以方便很多

```cpp
#include<stdio.h>
int main()
{
    char ch1,ch2;
    int n,a;
    scanf("%d\n",&n);//输入判断总数n
    for(int i=1;i<=n;i++)
    {
        while(1)
        {
            ch1=ch2;
            scanf("%c",&ch2);
            if(ch2=='\n')//每行必有'\n'，且存在于该行最后一位，因此可以作为判断该行数字最后一位的依据
                break;
        }
        a=ch1-'0';//字符转数字
        if(a%2==0)//判断奇偶
            printf("even\n");
        else printf("odd\n");
    }
    return 0;
}
```

---

## 作者：Sooke (赞：0)

pascal也挺有好处，自带判断奇偶函数ord(n)，相当于n mod 2 = 1，对于懒得打这么多字符的人也有好处~

int64挂了，高精度太麻烦，当然用**字符串**了，还能用什么呢……

```cpp
var
 n,i:longint;
 s:ansistring;
begin
 readln(n);
 for i:= 1 to n do begin
  readln(s);
  if odd(ord(s[length(s)])-48) then writeln('odd') else writeln('even');
//这一步判断最重要，ord(c)表示字符c的ASCII码，因为"0"的ASCII码是48，转换后减去48即可。
//odd(n)是判断奇数的，n为奇数返回值为真
 end;
end.
```

---

## 作者：13965282078m0 (赞：0)

```cpp
var
  a:string;//要判断的数
  b,c:longint;//C是有几组数 ，B是循环
begin
  read(c);
  for b:=1 to c do//读入几组数
  begin
    readln(a);//读入
    if s[length(a)] in ['1','3','5','7','9'] then//如果末位是基数
    writeln('odd')//打印odd
    else
    writeln('even');//相反打印even
  end;
  readln;
```
readln
end.

---

## 作者：guobaipeng0 (赞：0)

C++代码，开始也以为long long承受得住，没想到终究不行，在此提醒各位，注意只能用字符串形式读入。


```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long n,i;
string a;
int main()
{
    cin>>n;  //读入n，表示要判断n个数，n<=100，所以直接读入。
    for (i=1; i<=n; i++)
    {
        cin>>a;  //注意了，要用字符串
        if ((a[a.size()-1]-'0')%2==0) cout<<"even"<<endl; else cout<<"odd"<<endl;
                   //a[a.size()-1]-'0'表示提取个位，转化为数值，再对2求余。
    }
}
```

---

## 作者：「QQ红包」 (赞：0)

于是我用了STL。

读入用字符串读，取最后一位判断就好。

然后这题范围不支持用unsigned long long，小了。

```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long  
#define LO long long 
using namespace std;
string s;
int n;
int main()
{
    map<char,int> x;
    x['1']=1;x['3']=1;x['5']=1;x['7']=1;x['9']=1;//奇数 
    cin>>n;
    while (n--)
    {
        cin>>s;
        char c=s[s.size()-1];//取出最后一位 
        if (x[c]==1) cout<<"odd\n"; else cout<<"even\n";//输出 
    }
}
```

---

## 作者：_ljx_ (赞：0)

C++:
```cpp
#include<iostream>
#include<string.h>
using namespace std;
char a[2000]; //定义一个字符组，保存每个输入的数
int main()
{
    int n;
    cin>>n;//输入次数
    int i,l;
    for(i=1;i<=n;i++)
    {
        cin>>a;
        l=strlen(a); //计算字符长度，方便判断奇偶（就是看最后个数是不是偶数或奇数）
        if(int(a[l-1])%2==0) cout<<"even"<<endl; //因为‘0’也占了最后个空间，所以-1，在判断即可
        else cout<<"odd"<<endl;
    }
    return 0; //哈哈，又完成了一道
}
```

---

## 作者：_xcc_ (赞：0)

代码思路：

将数字读入字符串，直接判断数字最后一位的奇偶性，可省去用while分解大数各个位的时间，使之不超时。

```cpp
#include<iostream>
#include<cstring>              //strlen所需的库。 
using namespace std;
int main()
{
    ios::sync_with_stdio(false);         //加快cin、cout。 
    int s,i;
    char a[2000];                        //开大一点，防爆。 
    cin>>s;                              //s是数字个数。 
    for(i=0;i<s;i++)
    {
        cin>>a;                          //依次输入数字。 
        if((a[strlen(a)-1]-'0')%2==0) cout<<"even"<<endl;    //核心部分：把字符串里面的数字串的最后一位变为
            else cout<<"odd"<<endl;                            //数字，再判断奇偶。因为有'\0'结束符所以要减1。 
    }
    return 0;
}
```

---

## 作者：庸人 (赞：0)

```cpp
// 思路：判断最后一位就好辣 
#include<cstdio>
#include<cstring>//因为有字符串函数调用 
int main(){
    int n,i;
    char z[100];//开大点防止爆掉 
    scanf("%d",&n);//
    for(i=1;i<=n;i++){
        scanf("%s",z);//当成字符串来存 
        if((z[strlen(z)-1]-48)%2==0) printf("even\n");//只要最后一位能被2整除就是偶数 
        else printf("odd\n");//如果不能的话就是奇数 
    }
    return 0;//完工！！ 
}
```

---

