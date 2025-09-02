# logo语言

## 题目描述

Logo 语言命令可以指挥海龟在屏幕中爬行。本问题只使用 Logo 语言的三个语句：前进 `FD`，倒退 `BK` 和重复 `REPEAT`，因此，海龟只在一条直线上来回爬行。输入一行 logo 的命令行，输出海龟在屏幕中离开原来位子的距离（假设屏幕很大，可以让海龟移开 $10^9$ 的距离）。

例如：

- 输入 `FD 100` ，输出：$100$。

- 输入 `FD 100 BK 150`， 输出：$50$。

- 输入 `REPEAT 5[FD 100 BK 50]`， 输出：$250$。

- 输入 `REPEAT 5[FD 50 REPEAT 10[FD 100]]`， 输出：$5250$。

## 说明/提示

每个语句输入数据的绝对值不超过 $1000$。输出结果不会超过 $10^9$。


## 样例 #1

### 输入

```
FD 100
```

### 输出

```
100
```

# 题解

## 作者：a1_1 (赞：60)

### P1322 【logo语言】
我写了两种方法，一种**递归**，一种**模拟**。~~交了**10**次A了**2**次(三次90,一次80)????????~~

**递归(绝对纯递归)**:
```cpp
#include<bits/stdc++.h>
using namespace std;
int dg()
{
    string s;
    char c;
    int k,l=0,v;
    while (cin>>c)//回车+^z自动结束输入.
    {
        if (c==']') break;//特判像"REPEAT 1[] BK 1"这样的情况,不然只有90.
        cin>>s>>k;
        if (c=='R') 
        {
            v=getchar();//读'['.
            l+=k*dg();
            v=getchar();//读']'后' '.
        }
        if (c=='B') v=getchar(),l-=k;
    	if (c=='F') v=getchar(),l+=k;
    	if (v==int(']')) break;//如果v==int(' ')就一直读
    }
    return l;//这里就不必多说了
}
int main()
{
    cout<<abs(dg());//巨短主函数
    return 0;
}
```
~~是不是巨短???才0.42kb!!!~~

------------
**模拟(绝对纯模拟，不含一丁点递归和栈)**:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct logo
{
    int v;
    char c;
    int d;
    int i;
}a[150];
bool cmp(logo a,logo b)
{
    if (a.d!=b.d) return a.d>b.d;
    else return a.c>b.c;//巧用字典排序
}
int main()
{
    int n,m,j,k=0,l=0,i=0,o=1,p=0,w=0;
	char c,v;
    string s;
    while (cin>>c)
    {
    	if (isupper(c)) 
    	{
    		i++;
    		cin>>s>>a[i].v;
    		a[i].c=c;a[i].d=k;//a[i].c存命令等级,a[i].d存运算等级(过于抽象，只可意会不可言传)
        }
        if (c=='[') {k++;l=0;}//等级++
        if (c==']') 
        {
            k--;
            sort(a+o,a+o+i,cmp);//repeat语句内的命令按运算等级和命令等级
            for (j=o;j<=i;j++)
            {
                if (a[j].c=='R') l=l*a[j].v;//计算repeat语句内部
                if (a[j].c=='F') l=l+a[j].v;//同上
                if (a[j].c=='B') l=l-a[j].v;//同上
            }
            o=j;//下一次执行命令的起始位置
            if (k==0) p=p+l;
        }
        if (v=='['&&c==']') w=1;//特判像"REPEAT 1[] BK 1"这样的情况,不然只有90.
        v=c;
    }
    if (o==1||w==1)//如果没有repeat语句的情况
    {
        sort(a+o,a+o+i,cmp);
        for (j=o;j<=i;j++)
        {
            if (a[j].c=='R') l=l*a[j].v;
            if (a[j].c=='F') l=l+a[j].v;
            if (a[j].c=='B') l=l-a[j].v;
        }
        p=p+l;
    }
    cout<<abs(p)<<endl;
    return 0;
}

```
~~模拟是不是巨长???1.13kb!!!~~

------------
~~模拟很容易被hack,欢迎大佬hack~~

**敬请大佬指出错误**

P.S.可以看看我坎坷的AC道路

---

## 作者：封禁用户 (赞：21)

### 这道题是一道很好的递归题。（当然模拟也可以做）
首先我们看题:在次题中，logo有3个关键词:

1.**FD**(向前）；

2.**BK**（向后）；

3.**REPEAT**（重复)。

这些关键词语法分别为：

1.FD n 表示**向前**移动n步；

2.BK n 表示**向后**移动n步；

3.REPEAT n[......(代码）]表示重复执行**中括号**里面的代码n次。

好，我们的题意讲完了。（终于讲完了）


------------
现在，我们正式开始讲解题目：

首先的首先，再声明一下，我用的是递归做法。（别告诉我您不会递归）


首先来看你们最爱的**coding**:
## 重要提醒：勿抄代码，否则将会有棕名危险
```cpp
#include<bits/stdc++.h>
using namespace std;
int func()
{
	char ch,x;
	string wz;//尾缀(K,D,EPEAT) 
	int k,rt=0/*return*/;
	while(cin>>ch)
	{
		if(ch==']')break;
		cin>>wz>>k;
		if(ch=='R')//REPEAT
		{
			x=getchar();//[
			rt+=k*func();
			x=getchar();//]
		}
		if(ch=='B')//BK
		{
			x=getchar(); 
			rt-=k;
		}
		if(ch=='F')//FD
		{
			x=getchar(); 
			rt+=k;
		}
		if(x==']') break;
	}
	return rt;
}
int main()
{
	cout<<abs(func());//别忘记有abs（绝对值）
   	return 0;
}
```
### 看了代码，心情好了很多吧，现在进入重点，讲解部分：
#### 我们来分析一波代码：
  前两行很好理解，是头文件和命名空间，我们把精力放在func函数上；


  func里首先是**定义变量**，ch表示**输入的当前字符**，k表示前面的n,wz是**尾缀**，x是一个**无用的变量**，rt是返回值；
    
  接着是一个~~巨大~~的while，括号里面**用来输入**，如果ch是']',直接break，接着输入尾缀和k,很好理解；
    

  终于来到了主体，这边,如果**ch为R**，则代表wz="EPEAT"，先将‘[’输入了，在进行递归，让他把REPEAT过后的值算出来，最后输入‘]’,easy，下面两个if很简单，分别处理**BK**和**FD**（~~别问我为什么先处理BK再处理FD~~）,最后，我们判断x是否为‘]’，若为‘]’，表示**REPEAT结束**，break掉，最后的最后，return~~好不容易~~算出来的rt;
    

  主函数很好理解，别忘记有**abs**就行;
（the end）.



### 本人蒟蒻，有误勿喷（这是本蒟蒻第一次写题解，必定有讲得不好的地方），另外希望管理员大大给一个过。


---

## 作者：max0810 (赞：17)

这个道题看了看，觉得是个纯模拟，但仔细想了想后，还是觉得递归最简单。

首先，我们要知道：

fd = +

bk = -

repeat = ×

于是原式相当于一个含有加减乘的算式，那明显有乘法就需要递归，加减号就是模拟。

上代码（有注释）
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int s(string a,int l,int r)//将a[l~r]转换成数
{
    int ans = 0;
    for(int i = l;i <= r;i++)
        ans = ans*10+(a[i]-'0');
    return ans;
}
int fid(string a,int st)//a[st]一定是'[',此函数会找到a[st]对应的']'
{
    int c = 1,i = st;
    while(c)
    {
        if(a[++i]=='[')c++;
        else if(a[i]==']')c--;
    }
    return i;
}
int f(string a)
{
    int ans = 0;
    for(int i = 0;i < a.size()-1;)//开始模拟之路
    {
        if(a[i] == 'F')
        {
            int x = a.find_first_not_of("0123456789",i+2)-1;
            ans += s(a,i+2,x);//+2是因为fd有两个字母
            i = x+1;
        }
        else if(a[i] == 'B')
        {
            int x = a.find_first_not_of("0123456789",i+2)-1;
            ans -= s(a,i+2,x);//同理
            i = x+1;
        }
        else
        {
            int y = a.find_first_of('[',i);
            int x = fid(a,y);
            ans += f(a.substr(y+1,x-y-1)+' ')*s(a,i+6,y-1);//+6是因为reapeat有6个字母
            i = x+1;
        }
    }
    return ans;
}
int main()
{
    string a,b;
    while(cin >> b)a+=b;//这样a里面就没有空格（其实也没啥用）
    a+=' ';
    cout << abs(f(a));//一定记得加abs，距离一定非负
    return 0;
}

```
 
下面，为大家拓展一些关于字符串的函数（纯手打，有错请多多关照~~）
```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string a = "123456123456";
    
    cout << a.find_first_of("345",2) << endl;//a.find_first_of(x,y)表示从第y个字符起从前往后第一个是x这个字符的字符的位置（若x是字符串，则字符只需是x的任意一个字符即可）。
    
    cout << a.find_first_of("345") << endl;//a.find_first_of(x)表示（从开头找，从前往后）第一个是x这个字符的字符的位置（若x是字符串，则字符只需是x的任意一个字符即可）。
    
    cout << a.find_last_of("345",10) << endl;//a.find_last_of(x,y)表示从第y个字符起从后往前第一个是x这个字符的字符的位置（若x是字符串，则字符只需是x的任意一个字符即可）。
    
    cout << a.find_last_of("345") << endl;//a.find_last_of(x)表示（从末尾找，从后往前）第一个是x这个字符的字符的位置（若x是字符串，则字符只需是x的任意一个字符即可）。
    
    cout << a.find_first_not_of("345",2) << endl;//a.find_first_not_of(x,y)表示从第y个字符起从前往后第一个不是x这个字符的字符的位置（若x是字符串，则字符需要不是x的任意一个字符）。
    
    cout << a.find_first_not_of("345") << endl;//a.find_first_not_of(x)表示（从开头找，从前往后）第一个不是x这个字符的字符的位置（若x是字符串，则字符需要不是x的任意一个字符）。
    
    cout << a.find_last_not_of("345",2) << endl;//a.find_last_not_of(x,y)表示从第y个字符起从后往前第一个不是x这个字符的字符的位置（若x是字符串，则字符需要不是x的任意一个字符）。
    
    cout << a.find_last_not_of("345") << endl;//a.find_last_not_of(x)表示（从末尾找，从后往前）第一个不是x这个字符的字符的位置（若x是字符串，则字符需要不是x的任意一个字符）。
    
    cout << a.substr() << endl;//就是cout << a;
    
    cout << a.substr(1,3) << endl;//a.substr(x,y)表示从下标为x起，长度为y的字符串
    
    cout << a.substr(1) << endl;//a.substr(x)表示从下标为x起，一直到末尾的字符串
    return 0;
}

```
```
输出：
2
2
10
10
5
0
1
11
123456123456
234
23456123456
```
这些都是很常用的，学习c++的人一定要背哦！

---

## 作者：UnyieldingTrilobite (赞：15)

Python好玩。

这题我调了好久才过，感谢给予帮助的dalao们。

首先我们不难想到把这些方式当成一些运算。

$\operatorname{FD}:+$

$\operatorname{BK}:-$

$\operatorname{REPEAT}:\times$（<-大致算是

于是不难想到把这玩意转成一个我们所熟悉的四则运算表达式然后~~用表达式求值的做法~~直接调用库函数 eval 干掉。

于是不难写出代码：

```python
print(abs(eval(input().replace(' ','').replace('FD','+').replace('BK','-').replace('REPEAT','+(').replace('[',')*(').replace(']',")"))))
```

90分。

错在了哪里？

这个点很坑，是一位dalao点醒我的，我本来也没想到。

来看一组数据：

```python
REPEAT 100[]
```

很简单，不是吗？

重复100遍什么都不做，当然最后也是什么都没做，是0。

但是转化后变成了：

```python
+100*()
```

会发现出现了一对空括号，出现了问题。

原来为什么没问题？

因为我们知道，空括号相当于什么都不做相当于0。

但eval不知道。

于是我们改一下，手动识别出这些空括号就能AC了。

```python
print(abs(eval(input().replace(' ','').replace('FD','+').replace('BK','-').replace('REPEAT','+(').replace('[',')*(').replace(']',")").replace('()','0'))))
```

Over.

---

## 作者：KesdiaelKen (赞：14)

这道题其实可以很明显地看出来是一个类似于中缀表达式求值的东西。

可以把FD看做+，BK看做-，REPEAT看做+\*，那么这个表达式的运算结果的绝对值就是最终的输出。

对于处理中缀表达式，可以不用递归，最标准的解法是转化为后缀表达式。本人使用栈的方法转化的，具体转化的方法大家可以自己搜索一下，这里只给出程序。

注意要先在数字栈中加入一个0，否则会RE。

下为代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
stack<char>ope;//符号栈
stack<int>num;//数字栈
int cal(int a,char cz,int b)//运算
{
    if(cz=='+')return a+b;
    if(cz=='-')return a-b;
    if(cz=='*')return a*b;
}
int main()
{
    num.push(0);//先推入0
    char s[260];
    char cz;int shu;
    int a,b;
    while(scanf("%s",s)!=EOF)//以每一个运算为一节读入
    {
        if(s[0]!=']')scanf("%d",&shu);//如果是右括号，则无数字输入
        if(s[0]=='F')//以下为运算处理
        {
            while(!ope.empty()&&ope.top()!='[')
            {
                b=num.top();num.pop();
                a=num.top();num.pop();
                cz=ope.top();ope.pop();
                num.push(cal(a,cz,b));
            }
            ope.push('+');num.push(shu);
        }
        if(s[0]=='B')
        {
            while(!ope.empty()&&ope.top()!='[')
            {
                b=num.top();num.pop();
                a=num.top();num.pop();
                cz=ope.top();ope.pop();
                num.push(cal(a,cz,b));
            }
            ope.push('-');num.push(shu);
        }
        if(s[0]=='R')
        {
            while(!ope.empty()&&ope.top()!='[')
            {
                b=num.top();num.pop();
                a=num.top();num.pop();
                cz=ope.top();ope.pop();
                num.push(cal(a,cz,b));
            }
            ope.push('+');num.push(shu);ope.push('*');ope.push('[');num.push(0);//注意，这里也要推入一个0，因为括号内可以看作一个新的运算式，那么不推入的话也同样会RE
            getchar();//把之后的那个‘[’读掉
        }
        if(s[0]==']')
        {
            for(int i=strlen(s);i>0;i--)
            {
                while(ope.top()!='[')
                {
                    b=num.top();num.pop();
                    a=num.top();num.pop();
                    cz=ope.top();ope.pop();
                    num.push(cal(a,cz,b));
                }
                ope.pop();
            }
        }
    }
    while(!ope.empty())//若还有剩余，继续处理
    {
        b=num.top();num.pop();
        a=num.top();num.pop();
        cz=ope.top();ope.pop();
        num.push(cal(a,cz,b));
    }
    printf("%d",abs(num.top()));//输出，结束
    return 0;
}
```

---

## 作者：RenaMoe (赞：9)

**这里是栈的做法**

递归快写吐了，决心用栈，结果调了半天。。。

应该都能想到，FD就加，BF就减，REPEAT就压栈，']'就弹栈

手写栈比较舒服，~~用STL的stack有点丑~~

**细节太重要了**

敲的时候应该注意：读入是否从有效字符开始（用char[]的注意）、']'的读入、用过的那层栈要清空。。。

~~都是废话，自己写写就知道了~~

```cpp
#include <cstdio>
#include <cctype>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

namespace BANANA {//防止命名冲突

inline int read() {// 快读
	int re = 0, k = 1; char in = getchar();
	while (!isdigit(in)) { if (in == '-') k = -1; in = getchar(); }
	while (isdigit(in)) re = re * 10 + in - '0', in = getchar();
	return re * k;
}

int stack[305], k[305];// stack：栈，k：这一层栈repeat的次数
string s;

int num(string s) {// 把s串开头的数字提出来
	int ans = 0;
	for (int i = 0; isdigit(s[i]); i++)
		ans = ans * 10 + s[i] - '0';
	return ans;
}

inline void main() {
	int top = 1;
	while (cin >> s) {// ctrl+z结束
		if (s[0] == 'F') {
			cin >> s;
			stack[top] += num(s);
			int len = s.size() - 1;
			while (s[len] == ']')// 结尾有']'要退栈
				stack[top-1] += k[top-1] * stack[top], top--, len--;
		}
		else if (s[0] == 'B') {
			cin >> s;
			stack[top] -= num(s);
			int len = s.size() - 1;
			while (s[len] == ']')
				stack[top-1] += k[top-1] * stack[top], top--, len--;
		}
		else if (s[0] == 'R') {
			k[top] = read();
			top++;
			stack[top] = 0;// 用之前清空（之前因为这个WA了
		}
		else {
			// 特判"[]"里什么都没有的
			int i = 0;// 前面已经读入了'['，所以从0开始
			while (s[i] == ']' && i < s.size())
				stack[top-1] += k[top-1] * stack[top], top--, i++;
		}
	}
	printf("%d\n", abs(stack[1]));// 注意是距离（绝对值）
}
}

int main() {
	BANANA::main();
	return 0;
}
```
[关于代码中的namespace](https://banana.blog.luogu.org/tong-guo-namespace-fang-zhi-ming-ming-chong-tu)

---

## 作者：Sunlight9 (赞：6)

好久没有写题解了，今天突然想发一下。（RP++；）
这道题其实可以用纯模拟来做，把字符串看做一个算式，‘FD’相当于加，‘BK’相当于减，‘REPEAT’相当于乘，‘【】’相当于（）。
详细解释见代码注释。。。
```cpp
//Honor Liso 防伪标识 
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[260];//字符串 
int b[]={0,1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};//用来处理字符串中的位数关系，一直到十亿 
int num[7878]={1};//用来记录REPEAT(相当于乘)当前的数 
int lena,now,pd,numn,len_num;//lena=字符串长度  now=当前距起点的距离  pd=1时表示前进，pd=2时表示后退，pd=3时表示REPEAT
//numn表示num数组当前下标  len_num用来为num数组加数 
int main()//主程序（程序快乐的开始了） 
{
	gets(a);//输入  注：gets 一直读到回车（'\n'）  scanf读到空格（' '） 所以要用gets 
	lena=strlen(a);//记录长度 
	for(int i=0;i<lena;)//处理 
	{
		while(a[i]==' ')//空格跳过 
			i++;
		if(i>=lena)  break;//判断是否到头 
		if(a[i]=='[')//当出现‘【’时说明有REPEAT 以便乘num数组 
		{
			numn++;
			i++;
			continue;
		}
		if(a[i]==']')//当出现‘】’时说明REPEAT结束 乘之前的num数组 
		{
			numn--;
			i++;
			continue;
		}
		if(a[i]=='R'&&a[i+1]=='E')//处理REPEAT 
		{
			pd=3;//防止处理前进或后退 
			i+=6;//往前处理 
			while(a[i]==' ')//跳过空格 
				i++;
			int ii=0,iii=i;//处理数字 
			while(a[iii]>='0'&&a[iii]<='9')//符合数字范围 
			{
				ii++;//用来记数的位数 
				iii++;//用来往前处理数字 
			}
			int x=0;//数的总和 
			while(ii)//计算数的总和 
			{
				x=int(a[i]-'0')*b[ii]+x;//当前数*位数+原来的数 
				ii--;//位数-1 
				i++;//往前处理 
			}
			x*=num[numn];//乘之前的REPEAT 
			num[++len_num]=x;//加入新的乘数（REPEAT） 
		}
		if(a[i]=='F'&&a[i+1]=='D')//处理前进 
		{
			i+=2;//往前处理 
			pd=1;//用来表示前进 
			continue;
		}
		if(a[i]=='B'&&a[i+1]=='K')//处理后退 
		{
			i+=2;//同上 
			pd=2;//用来表示后退 
			continue;
		}
		if(pd!=3)//处理前进或后退而不处理REPEAT 
		{
			int ii=0,iii=i;//同上 
			while(a[iii]>='0'&&a[iii]<='9')
			{
				ii++;
				iii++;
			}
			int x=0;
			while(ii)
			{
				x=int(a[i]-'0')*b[ii]+x;
				ii--;
				i++;
			}
			x*=num[numn];
			if(pd==1)  now+=x;//如果前进 + 
			else  if(pd==2)  now-=x;//如果后退 - 
		}
		pd=0;//pd归零 
	}
	if(now<0)  now=0-now;//处理负数（求绝对值，可用abs(cmath)） 
	printf("%d",now);//输出 
	return 0;//程序快乐的结束了 
}
//Honor Liso 防伪标识 
```
我看到有许多DALAO用栈、递归等，感觉本人代码瞬间变LOW了。。。
希望我的代码能够帮助到大家。
注：代码仅供参考，请不要抄袭，我相信LuoGu伟大的管理员会监督的。

---

## 作者：xukuan (赞：4)

算法：栈

栈里存运算符，数字到时候再读，边读边做

读入必须用读入优化，因为有一些字母

此代码仅针对c++（有STL之stack），Pascal莫入

```cpp
#include<bits/stdc++.h>
using namespace std;

int i,a[1010];
string s;
stack<int> zhai;

int work(int l,int r)
{
    if(l>r) return 0;//递归出口：左指针>右指针
    while(s[l]==' ') l++;//处理左边空格
    while(s[r]==' ') r--;//处理右边空格
    int t,x=0;
    if(s[l]=='R'){//开始读入的位数，repeat长为6
    	t=l+7;
	}
	else t=l+3;//fd和bk长为3
	
    //注意：这里必须用读入优化！！！
    while(isdigit(s[t])){
		x=x*10+s[t]-48;
		t++;
	}
	
    switch(s[l])//分类讨论
    {
        case 'R':{
        	return work(a[t]+1,r)/*repeat后面的*/+x/*重复次数*/*work(t+1,a[t]-1)/*重复区间内的值*/;
			break;
		}
        case 'F':{
        	return x+work(t+1,r);//加上去
			break;
		}
        case 'B':{
        	return work(t+1,r)-x;//减掉
			break;
		}
    }
}

int main()
{
    getline(cin,s);
    for(i=0; i<=s.size()-1; i++)
    {
		if(s[i]==']'){
			a[zhai.top()]=i;
			zhai.pop();//出栈
		}
		else
        if(s[i]=='[') zhai.push(i);//入栈
    }
    cout<<abs(work(0,s.size()-1));//有一个绝对值，可能会弄错（上面的样例已经有说明了）
    return 0;
}
```

---

## 作者：SIGSEGV (赞：4)

模拟是个好东西。

根本用不着什么算术栈啊这些乱七八糟的（我对此有心理阴影），只要弄一个link数组来从‘[’的位置连接到到‘]’的位置（有点像哈希表）

上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,l,ans,link[300];
char s[300];
int expr(int start,int end) //前闭后开[start,end)区间
{
	int ans = 0;
	for (int i = start;i < end;i++)
	{
		if (!isalpha(s[i])) continue;//数字空格这些统统去掉
		bool fr = 0;bool rp = 0;int num = 0;
		if (s[i] == 'F') sscanf(&s[i + 3],"%d",&num),fr = 1;//前进
		else if (s[i] == 'B') sscanf(&s[i + 3],"%d",&num);
		else if (s[i] == 'R') sscanf(&s[i + 7],"%d",&num),rp = 1;//循环
		else continue;//一边去
		if (!rp)
		{
			if (fr) ans += num;else ans -= num;
			continue;
		}
		while (s[i] != '[') i++;//挪到左括号位置
		int ed = link[i];
		ans += num * expr(i + 1,ed);
		i = ed;
	}
	return ans;
}
int main ()
{
	gets(s);l = strlen(s);
	stack<int> stk;
	for (int i = 0;i < l;i++) //匹配计算
	{
		if (s[i] == '[') stk.push(i);
		if (s[i] == ']') link[stk.top()] = i,stk.pop();
	}
	;
	printf("%d",abs(expr(0,l)));//打印结果，注意abs
	return 0;
}
```

---

## 作者：Wei_wei_ (赞：2)

# C++解法▼
第二次发题解，还是有点紧张。但作为曾今的 logo 选手，我必须写一篇题解。~~玩过 logo 的都知道， logo 语言远不止这些命令。~~  
废话不多说，进入正题。  
### 首先，一看完题目，就知道，这肯定是递归呀！
REPEAT 的嵌套，当然要用递归啦！  
举个栗子：
```
REPEAT 6[FD 30 BK 20 REPEAT 2[FD 10]]
```
模拟一下：( read 代指“读”)
```
read(f(首字母))->read(s(尾缀))->read(' ')->read(k(参数))
if(f=='R')read('[')->递归
```
开始以为可以用循环，但我忘记了**嵌套**这回事。  
理解了递归的思路，前进后退不是难事。设置一个计算长度的变量：$l$（记得制0！）。前进多少就$l+=k$，后退多少就$l-=k$。最后输出绝对值，妥妥的。  
### 接下来上代码，还有什么不懂的，参见注释：
```
#include<iostream>
#include<cstring>//要定义string类型
#include<cstdio>//getchar()
#include<cmath>//abs()
using namespace std;
int My_dg();
int main()
{
	cout<<abs(My_dg());//绝对值。
}
int My_dg()//开始递归喽！
{
	string a;//FD、BK、REPEAT的后半部分(D、K、EPEAT)｡
	char f;//first，即第一个字母(F、B、R)｡
	int k,l=0,tsg;//k指跟在后面的参数，l指长度，tsg用来存放'['与' '(替死鬼)。
	while(cin>>f)//enter+^Z 
	{
		if(f==']')break;//防止 REPEAT k[]里没东西(empty)的情况。
		cin>>a>>k;//如上。
		if(f=='R')
		{
			tsg=getchar();//替死鬼上线收'['｡
			l+=k*My_dg();//重复k次递归。
			tsg=getchar();//替死鬼收' '。
		}
		if(f=='B')tsg=getchar(),l-=k;//替死鬼收' '。
		if(f=='F')tsg=getchar(),l+=k;//替死鬼收' '。
		if(tsg==']')break;//等到替死鬼等于']'，循环结束。
	}
	return l;//返回长度(length)｡｣
}
```
还有问题的话，私信我就行了（注意告诉我是那一题）。

---

## 作者：hongzy (赞：2)

这题主要的是Repeat的处理。

扫描，如果是Repeat，找需要循环的部分，拿一个Sub数组存下来，多次递归执行Sub.

（本题数据小，复制Sub的过程不会导致超时）


还有，sscanf是个好东西 —— 从字符串中读取.


```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char Command[256];
int pos;

void GO(char * c) {
    int len = strlen(c), x, times;
    char Do[256];
    for(int i=0; i<len; i++) {
        if(c[i] < 'A' || c[i] > 'Z') continue;
        if(c[i] == 'R') {
            int l = -1, r = -1, tmp = 0;
            sscanf(&c[i+7], "%d", &times);
            for(int j=i+7; j<len; j++) {
                if(c[j] == '[') {
                    l = j;
                    break;
                }
            } 
            for(int j=l+1; j<len; j++) {
                if(tmp == 0 && c[j] == ']') {
                    r = j;
                    break;
                }
                if(c[j] == '[') tmp ++;
                else if(c[j] == ']') tmp --;
            }
            char Sub[256];
            for(int j=l+1; j<=r-1; j++) Sub[j-l-1] = c[j];
            Sub[r-l-1] = '\0';
            for(int j=1; j<=times; j++) GO(Sub);
            i = r;
        }
        else if(c[i] == 'F') {
            sscanf(&c[i+3], "%d", &x);
            pos += x;
        } else if(c[i] == 'B') {
            sscanf(&c[i+3], "%d", &x);
            pos -= x;
        }
    }
}

int main() {
    gets(Command);
    GO(Command);
    printf("%d\n", (pos>0)?pos:-pos);
    return 0;
}
```

---

## 作者：发源于 (赞：2)

想法较为简单

不用提取[]

一遍从左向右扫

递归
发现[就进递归

发现]就退出（以此脱[]）

这样一个递归必然处理一个repeat，不会早退也不会晚退

递归返回值是]的位置

递归后指针直接调到]继续向后搜索

处理主代码也是递归

所以在所有代码外面套了层[]（我懒得特判什么的）

代码如下

```delphi

var
  s,ls:string;
  i,l,ans,c,v:longint;{c是现在的倍数（如repeat 9次就c*9。每次（如fd时）就fd操作数*c（为什么））}
function fd(i:longint):longint;{找到fd的操作}
begin
  ********{已被本人屏蔽}{自行脑补，过于简单}
end;
function bk(i:longint):longint;
begin
  ********{同上}
end;
function logo(i:longint):longint;{核心递归}
var j,L:longint;
begin
  while s[i]<>']' do
    begin
      if s[i]='F' then
        i:=fd(i);{i是指针的位置}
      if s[i]='B' then
        i:=bk(i);
      if s[i]='R' then  {重点}
        begin
          i:=i+7;
          while s[i]=' ' do inc(i);
          ls:='';
          while (s[i]<>'[') and (s[i]<>' ') do
            begin
              ls:=ls+s[i];
              inc(i);
            end;
          val(ls,l);
          while s[i]=' ' do inc(i);
          inc(i);{前面是预处理，把repeat的次数提取出来，把指针指到[的右一个。下面是核心}
            if l<>0 then {防repeat 0}
            begin
              c:=c*l;{不解释}
              logo:=logo(i);{很简单吧}
              c:=c div l;{不解释｝
            end
            else
              begin
                v:=c;
                c:=0;
                logo:=logo(i);
                c:=v;{只是为了求坐标}
              end;
          i:=logo;
        end;
      if s[i]=' ' then
        inc(i);{怕死循环}
    end;
   logo:=i+1;
end;
begin
  readln(s);
  s:='['+s+']';
  i:=1;
  ans:=0;
  c:=1;
  l:=logo(2);{其实l没用啦}
  writeln(abs(ans));
end.

```
[color=red]没有难的地方。完全是为了我偷懒而设计的。（偷懒是件好事？）[/color]


---

## 作者：sfd158 (赞：2)

```cpp

#include<cstdio>
char s[500];
int stk[500],len;
long long pla[500];
inline const int doing(const int l,const int r)//递归处理
{
    if(s[l]=='R')//如果是repeat
        return pla[l]*doing(l+2,pla[l+1])+doing(pla[l+1]+1,r);//repeat的部分加上后
                                                                                                                       //面的部分
    else
    {
        int i,ans=0;
        for(i=l;i<r && s[i]!='R';i++)
        {
            if(s[i]=='F')ans+=pla[i];//前进
            else ans-=pla[i];//后退
        }
        if(i<r)ans+=doing(i,r);//repeat
        return ans;
    }
}
inline const int abs(const int x)//注意，结果一定要加绝对值
{
    if(x>=0)return x;
    else return -x;
}
int main()
{
    char c=getchar();
    int top=-1,i,ans;
    long long x;
    while(c!=EOF)//读入
    {
        if(c=='[')//处理括号
        {
            stk[++top]=len;
            s[len++]='[';
        }
        else 
        if(c==']')
        {
            pla[pla[len]=stk[top]]=len;
            stk[top--]=0;
            s[len++]=']';
        }
        else
        if(c=='B' || c=='F' || c=='R')//处理命令
        {
            s[len]=c;
            while('0'>c || '9'<c)c=getchar();
            x=0;
            while('0'<=c && c<='9')//读入数字(我作死的用了读入优化)
            {
                x=x*10+c-'0';
                c=getchar();
            }
            pla[len++]=x;
            continue;
        }
        c=getchar();
    }
    printf("%d\n",abs(doing(0,len)));
    return 0;
}

```

---

## 作者：happybob (赞：1)

摆明的递归题目，先来看看解题思路

首先while读入char类型的ch

如果是]那么就break

如果是T就读入空格然后再构造char类型的字符和string的字符串，每次读入一直到[停止读入，并且随时将字符串加上这个字符，再递归结果乘以这个字符串转成数字的结果

另外的前进后退就简单了

代码，20ms，616.00KB，代码长度945B，C++11 O2

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int cl()
{
    int ans = 0;
    char s;
    while(scanf("%c", &s) != EOF)
    {
        if(s == ']')
        {
            break;
        }
        else if(s == 'T')
        {
            scanf(" ");
            char a;
            string s;
            while(scanf("%c", &a))
            {
                if(a == '[')
                {
                    break;
                }
                s += a;
            }
            ans += stoi(s) * cl();
        }
        else if(s == 'D')
        {
            scanf(" ");
            int a;
            cin >> a;
            ans += a;
        }
        else if(s == 'K')
        {
            scanf(" ");
            int x;
            cin >> x;
            ans -= x;
        }
    }
    return ans;
}

int main()
{
    cout << abs(cl()) << endl;
    return 0;
}
```


---

## 作者：WanderingTrader (赞：1)

$\texttt{update on 2020-08-01}$ 调整了一下部分排版，一切变量和函数名称均加入了 $\LaTeX$。  
$\texttt{update on 2020-07-31}$ 稍微调整了一下部分排版。  

这道题还是非常简单的，主要是递归，注意一些细节就没问题。

其实我觉得评黄有点过了，不过看在 [P1928 外星密码](/problem/P1928) 都评了绿，那也就算了吧。
### 题目分析&代码
这题的思路和P1928几乎完全一致，写法也很相似。

第一步还是将字符串中的括号匹配，这样在后续操作中会非常方便：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=260;
int logo[maxn];
stack <int> st;
string str;
int main()
{
	getline(cin,str);
	int size=str.length(),x;
	for(int i=0;i<size;++i)
	{
		if(str[i]=='[') 
			st.push(i);
		else if(str[i]==']')
		{
			logo[st.top()]=i;
			st.pop();
		}
	}//括号匹配 
	return 0;
}
```
这里不会RE吗？显然不会。因为题目给的字符串一定是合法的logo语言，所以当我们遇到一个`]`，那必有一个`[`尚未匹配。

接下来定义一个int类型的函数为 $getint$ ，顾名思义它是在字符串中提取整数用的。
```cpp
int getint(int& pos)
{
	int x=0;
	while(isdigit(str[pos]))
		x=x*10+str[pos++]-'0';
	//类似快读的写法,将字符提取出来变为数字 
	--pos;
	//调整位置 
	return x;
}
```
写法和快读真的很像。  

这里 $pos$ 传了引用，这样函数结束后$pos$ 的值就是最后一个数字字符的位置，比如：
```
54321
```
操作前 $pos$ 为 $1$，操作后为 $5$。

最后是重头戏，一个返回值为int型的  $deal(l,r)$ 函数，用于处理区间 $[l,r)$ 的答案。  

```cpp
int deal(int l,int r)
{//处理区间[l,r) 
	int ans=0;
	for(int i=l;i<r;++i)
	{
	}
	return ans;
}
```
如果此时碰到的字符是`F`，说明这个命令是`FD`，那么先将 $i+3$ （挪到命令结尾空格的后面），然后 $getint$，将 $ans$ 加上对应的值即可。
```cpp
	if(str[i]=='F')
	{
		i+=3;
		//调整到合适位置 
		ans+=getint(i);
		//如果命令是"FD"那就将位置向前挪[数字]格 
	}
```
如果碰到的是`B`，说明命令为`BK`，操作和`FD`相同，只是加改成减。
```cpp
	else if(str[i]=='B')
	{
		i+=3;
		ans-=getint(i);
		//同"FD",只是向前挪改成向后挪 
	}
```
如果是`R`，说明命令为`REPEAT`，按如下顺序操作。

先将 $i+7$ (调整到命令结尾空格以后)。

再 $getint$ ，结果赋给 $times$。

接着将 $i+1$ (调整到左括号位置)。

然后递归操作 $deal(i,logo[i])$ （也就是求出方括号内操作的答案），答案赋给 $k$。

完成后将 $ans$ 加上 $k\times times$ （把中间内容执行 $times$ 次的答案）即可。

最后别忘了把 $i$ 变为 $logo[i]$ ，调整位置以免重复计算。
```cpp
	else if(str[i]=='R')
	{
		i+=7;
		//调整位置 
		int times=getint(i);
		//计算出循环次数 
		++i;
		//调整位置again 
		int k=deal(i,logo[i]);
		//递归 
		ans+=k*times;
		//修改答案 
		i=logo[i];
		//调整位置the last time 
	}
```
如果它压根不是字母，那就不用理它了。

现在我们求出了海龟的位置，而题目中要求的是它与原点的距离，那么取绝对值即可。

全部代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=260;
int logo[maxn];
stack <int> st;
string str;
int getint(int& pos)
{
	int x=0;
	while(isdigit(str[pos]))
		x=x*10+str[pos++]-'0';
	//类似快读的写法,将字符提取出来变为数字 
	--pos;
	//调整位置 
	return x;
}
int deal(int l,int r)
{//处理区间[l,r) 
	int ans=0;
	for(int i=l;i<r;++i)
	{
		if(str[i]=='F')
		{
			i+=3;
			//调整到合适位置 
			ans+=getint(i);
			//如果命令是"FD"那就将位置向前挪[数字]格 
		}
		else if(str[i]=='B')
		{
			i+=3;
			ans-=getint(i);
			//同"FD",只是向前挪改成向后挪 
		}
		else if(str[i]=='R')
		{
			i+=7;
			//调整位置 
			int times=getint(i);
			//计算出循环次数 
			++i;
			//调整位置again 
			int k=deal(i,logo[i]);
			//递归 
			ans+=k*times;
			//修改答案 
			i=logo[i];
			//调整位置the last time 
		}
	}
	return ans;
}
int main()
{
	getline(cin,str);
	int size=str.length(),x;
	for(int i=0;i<size;++i)
	{
		if(str[i]=='[') 
			st.push(i);
		else if(str[i]==']')
		{
			logo[st.top()]=i;
			st.pop();
		}
	}//括号匹配 
	printf("%d\n",abs(deal(0,size)));
	//输出答案.注意一定要取绝对值!
	//而且一定要等到这一步才能取绝对值! 
	return 0;
}
```

$$\texttt{The End.}$$

---

## 作者：__Cocoa__ (赞：1)

经过2天的调试，我终于AC了。

WA->RE->MLE->AC!

坑点：

- FW、BK、REPEAT和[]之间可能有空格，可能没有
- 递归效率太低可能会栈溢出

~~看了一下好像只有我一个人是导入全部字符串再一起处理的~~


```C++
#include <cstdio>

int strlen(char * str){//计算字符数组长度; 
	int i=0;
	for(;str[i]!='\0';i++);
	return i;
}

int decode(char * code){//编译函数; 
    char c;//临时字符变量 
    
	int dis=0;//运行的距离 
	
    char x[255]="";//存储REPEAT中的语句 
    
    int num=0;//存储数字（例如FW后面） 
    
    for(short i=0;(c=code[i])!='\0';num=0	/*每次循环使num归零*/	){
        if(c=='F'){
            i+=3;
            c=code[i];
        
            while('0'<=c && c<='9'){//存储FW后面的num 
                num=num*10+c-'0';
                c=code[++i];
            }
            dis+=num;
        }
        else if(c=='B'){
            i+=3;
            c=code[i];
            while('0'<=c && c<='9'){//存储BK的num 
                num=num*10+c-'0';
                c=code[++i];
            }
            dis-=num;
        }
        else if(c=='R'){
            i+=7;
            c=code[i];
            while('0'<=c && c<='9'){//读取REPEAT后面的循环次数 
                num=num*10+c-'0';
                c=code[++i];
            }
            while((c=code[++i])!=']'){//读取[]中间的代码 
                x[strlen(x)]=c;
            }
            i--;
            dis+=num*decode(x); 
            for(int i=0;i<strlen(x);i++)//将字符数组x归零 
				x[i]='\0';
            i++;
        }  
        else i++;
    }
    return dis;
}

int main(){
    char code[255];
    scanf("%[^\n]",&code);//导入本行logo代码 
    
    int a=decode(code);
    printf("%d",((a>=0)?a:-a)	/*绝对值*/	);
    return 0;
}
```
30ms,776KB,代码长度~~只有~~1.27KB

---

