# [AHOI2017初中组] rexp

## 题目背景

为了解决形形色色的字符串匹配问题，正则表达式是一个强有力的工具。正则表达式通过定义一套符号体系，能够表示出需要查找的字符串所具有的性质。如 `a|aa` 能匹配 `a` 或 `aa`，`(a|b)c` 能匹配 `ac` 或 `bc`。


## 题目描述

完整的正则表达式过于复杂，在这里我们只考虑由 `(`、`)`、`|` 和 `a` 组成的正则表达式。运算遵循下列法则：

1. 有括号时，我们总是先算括号内的部分；

2. 当两个字符串（或由括号定义的子串）间没有符号时，我们总把它们连起来作为一个整体；

3. `|` 是或连接符，表示两边的字符串任取其一，若同一层里有多个或连接符，可以看作在这些或连接符所分开的若干字符串里任取其一。

例如，`(aaa)aa|aa|(a(aa)a)`、`(aaaaa)|(aa)|aaaa` 和 `aaaaa|aaaa|aa` 是等价的，它们都能匹配长度为 $2,4$ 或 $5$ 的全 `a` 字符串。

下面给定一个简化正则表达式，试编程计算它最多能匹配多长的全 `a` 字符串。

## 说明/提示

**【数据范围】**

对于 $20\%$ 数据，表达式长度不超过 $100$，且不存在括号。

对于 $40\%$ 数据，表达式长度不超过 $100$。

对于 $70\%$ 数据，表达式长度不超过 $2 \times 10^3$。

对于 $100\%$ 的数据，表达式长度不超过 $10^5$。

保证表达式合法（即 `|` 两端和括号内运算结果均非空字符串）。

## 样例 #1

### 输入

```
(aaa)aa|aa|(a(aa)a)```

### 输出

```
5
```

## 样例 #2

### 输入

```
((a|aaa)|aa)|a```

### 输出

```
3```

## 样例 #3

### 输入

```
(a(aa|aaa)a|(a|aa))aa```

### 输出

```
7```

# 题解

## 作者：迈吉扣 (赞：74)

### 这个题真心简单，其实根本不要楼上那么复杂，18行代码一个递归就AC了

```
#include<bits/stdc++.h>
using namespace std;
int p(int j)
{
    char c;
    while(scanf("%c",&c)!=EOF)
    {
        if(c=='a') j++;
        if(c=='(') j=j+p(0);
        if(c=='|') return max(j,p(0));
        if(c==')') return j;
    }
    return j;
}
int main()
{
    cout<<p(0);
    return 0;
}
```

---

## 作者：清风霁月 (赞：14)

    
    
    
    
        
    
    
    

 
```cpp
#include <stdio.h>
#include <string.h>
int i=1;
char ch[100005];
int work()
{
    int len=0,t;
    while(1)
    { i++;
    if(ch[i]==')') {return len;}//右括号必须写在前面
    if(ch[i]=='a') len++;
    if(ch[i]=='(') len+=work();
    if(ch[i]=='|') {t=work();return (len>t)?len:t;}    //这个地方必须加return 
     }
    }
int main()
{
    scanf("%s",ch+1);
    int len,num,sum=0,max=0;
    len=strlen(ch+1);
    while(i<=len)
    {
        if(ch[i]=='a') sum++,i++;
        else if(ch[i]=='(') {num=work();sum=sum+num;}
                else if(ch[i]=='|') if(sum>max) max=sum,sum=0,i++;
                                       else sum=0,i++;
                        else if(ch[i]==')') i++;
        }
         printf("%d",(sum>max)?sum:max);
    return 0;
    }
```
主思路：
先考虑没有括号的情况：aaa|aaaa，这个比较简单，设计一个len和max，len是当前状态的长度，max是碰到|符号后，存放最大值长度。
其次考虑有括号的情况：

（aa）    有括号

（aa（aa））括号中有括号  （aa（aa）a）

（aa|a）括号有分隔符号

（aa（aa|a）a）括号中有括号也有分隔符号

那么可以想简单点，例如有这样一组数据：

aaaaaa(.................................)|aaaaaa(............)我们可以算出这个括号里的长度，直接参与计算，括号里怎么计算我再想办法。前一个括号里算出来长度是6那么分隔符左边的长度就是12，后一个括号里的算出来长度是2，那么分隔符右边的长度就是8，那么比较下，总长度就是12。

下面讨论下有趣的括号：

我的第一次解法是利用栈的原理来写的，先进后出，work函数里的bir数组是临时数组，当栈来用，遇到a进栈直到碰到')'，开始退栈，退栈时计算a的个数并比较大小，找出最大的长度，直到top指向栈底，也是我程序的if(j==1) return max; j值就是top，当top指向栈底的时候表面栈里所有的元素都是空，这个时候返回栈里最大长度max。arr数组是记录过滤掉括号后的数组，这个数组就是我们前面讨论的（aaa|aaaa，这个比较简单）情况了，这个就比较好处理了。

但是放到落谷里测试就过了2个测试点，我的天好郁闷！发现超时的现象过多，还有2个测试点是错误。思路这个时候要转变了，说明不能开这么大的数组来做这个题目（范围是10个6次方）。不能开数组意味着只能不断的计算这个长度，max不断在被更替。

那么在括号里的算法就也要改进。首先考虑最简单的情况，a（aa（aa）），i是字符数组的下标，这个字符的长度是9。i=1时，字符是a，我只要记录长度，i=2时是个括号，那么我要计算这个括号的长度，就调用函数work（work的含义就是计算括号内长度的函数），在函数work里i=3时，字符是a，在函数内记录长度，i=4是，字符是a，照旧。关键来了，i=5是，字符是'('，这个时候我们又要计算"这个"括号的长度了，是不是又要使用work()这个函数了，这就实现了递归。把上述的意思翻译成代码，应该这样写：

    if(ch[i]=='a') len++;

    if(ch[i]=='(') len+=work();

下面我们接着处理，程序现在在执行红色这个work()，就是我们测试数据a（aa（aa））红色部分，这个时候i=6，len++，i=7，len++   len=2；i=8问题又来了，是')'字符，怎么处理？按照我们的本意理解，这组红色的括号计算完了，要退出，所以代码是这样的：

if(ch[i]==')') {return len;}// 右括号必须写在前面

因为没有'|'字符，所以我们的测试数据可以测试了，出来的结果是正确的。



右括号写前面的道理：

 

(aa(aa)a)

下面我们要在测试数据中加入'|'字符，a（aa|a），我们先不做复杂的，先搞好最简单的。

'|'字符的意思就是比较红色的a和蓝色的a的长度，红色部分a的长度显而易见在变量len中，那么蓝色部分的a在哪里呢？怎么来解决这个问题，我们能不能写一个函数来专门计算蓝色部分a的长度，这个函数的写法如下：

```cpp
     int solve()   
     {  
       int  len=0
       if(ch[i]=='a') len++;
       if(ch[i]==')') {return len;}
           }
```
这个时候发现这个solve函数和谁长的一样，和work函数一样啊。那么蓝色部分的长度就是再一次调用work()函数，work的返回值就是蓝色部分的长度。比较红色和蓝色的长度，较大的给len，具体的写法如下：
if(ch[i]=='|') {t=work();return (len>t)?len:t;}    //这个地方必须加return

（aa|a）整个括号里的长度算出来要返回给我们，所以这个地方要加个return。

如果这里不加return，我们调试程序的时候会发现，i的值会一直往右跑，超出这个字符数组的范围。

所以整个递归的写法如下：

```cpp
    int work()
{    int len=0,t;
    while(1)
    { i++;
    if(ch[i]==')') {return len;}//右括号必须写在前面
    if(ch[i]=='a') len++;
    if(ch[i]=='(') len+=work();
    if(ch[i]=='|') {t=work();return (len>t)?len:t;}    //这个地方必须加return 
         }
    }

```

---

## 作者：Ptilopsis_w (赞：6)

## [题目传送门](https://www.luogu.com.cn/problem/P3719)
这题是典型的递归题，这题其实是比较水的，因为只有'a'单种字符，不需要过多地处理，有一道类似的递归题推荐做一下  
[P1928外星密码](https://www.luogu.com.cn/problem/P1928)

## tips
没有说明长度的读入可以直接用`while(cin>>s)`这种方式读入，因为`cin`和`scanf`在没有读取到数据时会返回文件结束符EOF，若读取到数据则会返回读取到几个数据，比如`cin>>a>>b`如果 $a$ 和 $b$ 都成功读取会返回2

## 思路
因为括号和`|`可以算是运算符，所以遇到他们就递归解决然后return结果，即把每个运算符看成单独的式子解决,把大问题分解为小问题(递归思想)，具体注释在代码里，其实其他dalao的题解已经解释的很详细了

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int work()
{
	int s = 0;//因为字符都是'a'就直接用数字表示个数就行
	char ch;
	while(cin >> ch)
	{
		if(ch == ')')//括号结束，返回递归结果
			return s;
		else if(ch == '(')//括号开始，当前字符数加上括号的结果
			s += work();
		else if(ch == '|')//判断左右，因为出现|时左边已经计算完毕，所以要return结果
			return max(s, work());
		else//是'a'就字符数++
			s++;
	}
	return s;
}

int main()
{
	cout<<work();//递归解决
}
```

---

## 作者：localhost (赞：4)

我来发一个不需要递归的代码

解释见代码

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
il int max(int x,int y){return x>y?x:y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;rg char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 100011
int n,q[N],tp=0,a[N],mx[N];
char s[N];
int main(){
    in(s+1);
    int len=strlen(s+1);
    for(int i=1;i<=len;++i){
        if(s[i]=='(')a[++tp]=0,mx[tp]=0; // 如果是'('则进入下一层
        else if(s[i]==')')--tp,a[tp]+=mx[tp+1];// 如果是')'返回上一层，上一层加上当前答案
        else if(s[i]=='|')a[tp]=0;
        else ++a[tp];
        mx[tp]=max(mx[tp],a[tp]);//去当前合并后的长度
    }
    printf("%d\n",mx[0]);
}
```

---

## 作者：dfydada⚡⚡⚡ (赞：4)

这题用递归模拟会简单一点。

递归内容也不复杂。while输入字符，进一个做一个。到时候可以用Ctrl+Z返回退出。

循环内容就是4个判断。

if是a
累加器就++；

if是(
累加器就+递归0进去。

if是|
比较累加器和递归0进去，返回最大值。

if是)
返回累加器的值。

如果输入完了递归就结束了。

上代码：

```cpp
int asd(int ans)
{
    while(scanf("%c",&ch)!=EOF)
    {
        if(ch=='a')
        {
        	ans++;
		}
        else if(ch=='(')
        {
        	ans=ans+asd(0);
		}
        else if(ch=='|')
        {
        	return max(ans,asd(0));
		}
        else if(ch==')')
        {
        	return ans;
		}
    }
    return ans;
}
```
主函数就只用调用递归和输出就可以了；

总代码：

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(2)//O2优化
using namespace std;
typedef long long ll;
const int N=3000+10;
int ant;
char ch;
int asd(int ans)
{
    while(scanf("%c",&ch)!=EOF)
    {
        if(ch=='a')
        {
        	ans++;
		}
        else if(ch=='(')
        {
        	ans=ans+asd(0);
		}
        else if(ch=='|')
        {
        	return max(ans,asd(0));
		}
        else if(ch==')')
        {
        	return ans;
		}
    }
    return ans;
}
int main()
{
	ant=asd(0);
    cout<<ant;
    return 0;
}

```


---

## 作者：天泽龟 (赞：3)

### 马上又是一年一度的AHOI了呢……
目前两个题解都是正解的递归算法，但是考场上像我这种蒟蒻，只能想到暴力模拟对不对啊~~（只有你一个人吧）~~

所以本蒟蒻就给大家模拟一下考场上如何
# 暴力骗分！
因为暴力骗分的程序也能拿90（第八个点超时了），所以只要第一题稳住，第二题~~玄学~~找规律骗分，拿一等奖真的不是梦！


------------

#### 暴力模拟时候只要想到以下几点就成功一半！
1.判断括号的优先区间时，应以后括号为准，且上一个前括号一定匹配。

2.判断一个区间中的答案时，可以用pos（当时仍是p党）逐步判断长度，虽然思路简单但很容易实现~~（为之后的DEBUG留下充裕时间）~~。

3.因为程序最外围可能无括号，所以在程序最后仍需进行一次搜索。

------------
```pascal
program rexp;       
var
  s,s1:ansistring;
  i,p,p1,l1,l2,sum:longint;
function search(s:ansistring):ansistring;  //区间处理
var
  s2:ansistring;
  i,j,p,p1:longint;
begin
  p:=pos('|',s);     //寻找
  while p<>0 do begin p:=pos('|',s); s2:=s;
    l1:=p-1;
    delete(s2,1,p);
    p1:=pos('|',s2);
    if p1<>0 then l2:=p1-1
    else l2:=length(s2);
    if l1<l2 then begin
      l1:=l2;
      delete(s,1,p);
    end
    else delete(s,p,l2+1);  //将左右两个部分进行判断，留下较优的
    if p1=0 then break
    else p:=p1;
  end;
  exit(s);
end;

begin
  //assign(input,'rexp.in');reset(input);
  //assign(output,'rexp.out');rewrite(output);
  readln(s);
  {
  for i:=length(s)-1 downto 1 do
  begin
    if (s[i]=')') and (s[i+1]=')') then inc(sum)
    else break;
    if (sum>1000) then begin
    writeln('20000'); halt;
    end;
  end;   }        //为了AC不择手段，针对第八个点的部分程序，略去
  p:=pos(')',s);
  while p<>0 do begin     //若仍有优先处理的区间就继续
    for i:=p downto 1 do         //倒序寻找第一个出现的前括号
      if s[i]='(' then begin
        p1:=i; break;
      end;
    s1:=copy(s,p1+1,p-p1-1);   //将区间独立处理，删除该区间并加上处理后的单元正解区间
    delete(s,p1,p-p1+1);
    insert(search(s1),s,p1);
    p:=pos(')',s);             //继续搜
    //writeln(s);
  end;
  s:=search(s);               //没有后括号进行最后处理
  writeln(length(s));
  readln;readln;
  //close(input);close(output);
end.


```

---

## 作者：Blender (赞：2)

这一题其实并未有太多解法，我只是详细解释一下大众的解法。

#### 题意

给一个串，有表示优先级的括号 ``` () ```， 单个字符```a```，以及运算```|```（姑且称它max运算吧）。

------------


### max运算的定义如下：
   aa...($ \textit{n} $个a)...aa | aa...($ \textit{m} $个a)...aa
   =  aa...( $ \textit{max}(\textit{n}, \textit{m}) $ 个a)...aa
求化简后 a 的个数

### 题解：

1. 我们可以从左到右遍历，遇 a 就 ++。

2. 遇上max运算就将前半部分放一边，再开一层递归，等到后半部分处理完后（遇上另一个 ```|``` 或该串结束，即遇上```)```），比较它俩。

3. 遇上左括号就把括号内看作一个整体，再开一层递归，处理内部的内容，再将括号中内容加到当前的数量中。

4. 括号内，仍然重复1-4步。

5. 遇见```)```，说明该括号结束，结束该函数，返回当前数量。

6. 如果EOF了，说明串结束了 ~~（这还用说）~~， 结束该函数， 输出。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int f (){ // 返回值是从调用时开始的部分中化简后 a 的个数
	int t = 0; // t 为当前 a 的个数
	char a; // 这只是一个暂存字符的变量，和a没有关系
	while (scanf("%c", &a) != EOF){ // 重复输入字符直到文件末
		if (a == '(') t += f (); // 步骤 3
		if (a == ')') return t; // 步骤 5
		if (a == '|') return max (t, f()); // 步骤 2
		if (a == 'a') t ++; // 步骤 1，注意这里不能写else 否则会wa 我也不知道为什么
	}
	return t;
}
int main (){
	printf ("%d", f());
	return 0;
}
```



---

## 作者：tribool4_in (赞：1)

思路显然，可以使用递归或栈（话说递归不就是用栈实现的吗），对于每一个字符，如果是左括号则递归调用计算括号内的内容，遇到右括号则直接返回（因为当前括号计算完毕了），如果是 ```|``` 则将后面的内容递归计算，否则则为 a，计数器加一。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int calc() {
	int num = 0; char c;
	while (cin >> c) {
		switch (c) {
			case '(': num += calc(); break;
			case ')': return num;
			case '|': return max(num, calc());
			case 'a': num++; break;
		}
	}
	return num;
}
int main() {
	printf("%d\n", calc());
	return 0;
}
```


---

## 作者：追梦之鲸 (赞：1)

本蒟蒻的第$011$篇题解。

[经典回顾P3719](https://www.luogu.com.cn/problem/P3719)

其实这道题就是一道很好的递归练习题

首先我们要知道 $cin$ 和 $scanf$ 的循环输入的方式

```c
cin

while(cin>>ch)
or
for(;cin>>ch;)

scanf

while(scanf("%d",&x)!=EOF)
or
for(;scanf("%d",&x)!=EOF;)
```

这样你就能一直读入了

我们先考虑遇到 $|$

很简单，就是当前 $a$ 的个数和 $|$ 后 $a$ 的个数做一个 $\max$ 就行

然后我们再考虑遇到括号

也很简单，就是遇到 $($ 的时候再开一个递归数组就行，遇到 $)$ 直接返回值

 如果您已经掌握的炉火纯青，那你可以跳过 样例解释

[样例解释](https://www.luogu.com.cn/paste/g24xe6v0)

### code：
```c
#include<cstdio>
#include<iostream>
using namespace std;
int qwq()
{
	int x=0;
	char c;
	while(cin>>c)
	{//重点来了
		if(c=='a')x++;
		else if(c=='|')return max(qwq(),x);//想想为什么用 return
		else if(c=='(')x+=qwq();
		else if(c==')')return x;
	}
	return x;
}
int main()
{
	cout<<qwq();
	return 0;
}
```

最后管理大大辛苦了**OTZ**&&[来玩啊](https://www.luogu.com.cn/user/361726)

---

## 作者：想不好名字 (赞：0)

# **传送门**

[P3719 [AHOI2017初中组]rexp](https://www.luogu.com.cn/problem/P3719)




------------
# 题目分析

给出一个由(,),|,a组成的序列，求化简后有多少个a。但是如果有括号要先算括号。

这题明显是一个裸的递归，求“|”的左右最大值，但要先计算括号的，将括号的和括号外的加在一起。明显是裸的递归，直接将“|”旁边最大值求出来，再比大小。话不多说，直接上代码



------------
# AC Code

```c
#include<bits/stdc++.h>
using namespace std;

int turn(int sum)
{
	char c;
	while(scanf("%c",&c)!=EOF)
	{
		
		if(c=='a') sum++;
		if(c=='|') return sum=max(turn(0),sum);
		if(c=='(') sum=sum+turn(0);
		if(c==')') return sum;
	}
	return sum;
}
int main()
{
	
	cout<<turn(0);
	return 0;
}
```


---

## 作者：happybob (赞：0)

本题是练习递归的好题目！！！

先说下思路吧：

首先，用scanf(%c, ch) != EOF一直读入

如果是'a'的话ans + 1

如果是左括号那么就将ans加上再次递归的结果，最后可以得到括号中全部的结果

如果是右括号就返回ans，因为括号匹配，不可能突然返回答案的

如果是|那么就返回ans和下一个递归的结果

代码来，不过因为重复调用系统栈会导致内存多一些，也正常：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

char ch;

int func()
{
    int ans = 0;
    while(scanf("%c", &ch) != EOF)
    {
        if(ch == 'a')
        {
            ans++;
        }
        else if(ch == '(')
        {
            ans += func();
        }
        else if(ch == '|')
        {
            return max(ans, func());
        }
        else if(ch == ')')
        {
            return ans;
        }
    }
    return ans;
}

int main()
{
    cout << func() << endl;
    return 0;
}
```


---

## 作者：柏木由纪AKB48 (赞：0)

本篇题解和楼下的写的略有不一样，比较好理解

同样采用dfs

但是听说第八个点和第十个点很鬼畜，听说全部都是括号和杠

具体实现运用了分治的思想，就是大问题化成小问题，很直观

下面黏贴代码，如有不懂的同学可以私信问我

直接按照题目示意的操作直接模拟好了

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char c[100000];
int len,s[100000],fix[100000],ds[100000];
//   aa(aa)|(aa|(a|aa))aa
int dfs(int a,int b){
    if(s[b]-s[a-1]==((int)'a')*(b-a+1)) return b-a+1;
    int ans=0;
    for(int i=a;i<=b;i++){
    	if(c[i]=='a') ans++;
        if(c[i]=='('){
            ans=ans+dfs(i+1,fix[i]-1);
            i=fix[i];continue;
        }
        if(c[i]=='|'){
            ans=max(ans,dfs(i+1,b));
            i=b;continue;
        }
    }
    return ans;
}

int main(){
    scanf("%s",c+1);
    len=strlen(c+1);int d=0;
    for(int i=1;i<=len;i++)s[i]=s[i-1]+(int)c[i];
    for(int i=1;i<=len;i++){
        if(c[i]=='(') ds[++d]=i;
        if(c[i]==')') fix[ds[d--]]=i;
    }
    printf("%d\n",dfs(1,len));
    return 0;
}
```

---

## 作者：G_A_TS (赞：0)

 _这不是 **递归~~水~~题**吗？_   
希望清晰易懂  
```cpp
#include<bits/stdc++.h>
using namespace std;
int work(int sum)
{
    char a;
    while (-1!=scanf ("%c",&a))//边读边递归
	{
        if (a==')') return sum;
        if (a=='a') sum++;
        if (a=='(') sum+=work(0);
        if (a=='|') {sum=max(sum,work(0));break;}
    }
    return sum;
}
int main ()
{
    printf ("%d",work(0));
    return 0;
}
```

---

## 作者：greenheadstrange (赞：0)

## 分析：
运用递推：

看到这道题就想到了表达式求值的问题。

表达式求值问题有两种算法：栈，或递推。

就这道题而言，递推的代码要好写一些。

具体操作如下：

- 读到了后括号就返回当前统计的值

- 读到了a就累加和+1

- 读到了前括号就加上新的统计 

-  读到|就取最大值

代码如下：

```cpp
int work(int s){//简单递推 
    char c;
    while(scanf("%c",&c)==1){//一边读一边递推 
        if(c==')')return s;//搜到后括号就返回 
        if(c=='a')s++;//搜到a的话统计和加一 
        if(c=='(')s+=work(0);//加上新的统计 
        if(c=='|'){s=max(s,work(0));break;}//重新统计答案 
    }
    return s;
}
```

在主函数中：

```cpp
int main(){
	cout<<work(0);//初始化得答案为0 
    return 0;
}
```

其实这道题还有一种方法，就是用**栈**，在这里我暂时不给代码，大家可以自行思考哦！

---

