# CF

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualc/tasks/codefestival_2016_qualC_a

このコンテストの名前は`CODEFESTIVAL`で、いくつかの文字を消すと`CF`という文字列にすることが出来ます。

好奇心旺盛な高橋君は、他の文字列に対してもこのように`CF`を得られるか気になりました。

英大文字アルファベットからなる文字列$ s $が与えられるので、$ s $からいくつかの文字を消して`CF`という文字列にすることが出来るか判定してください。

## 说明/提示

### 制約

- $ 2≦|s|≦100 $
- $ s $は英大文字(`A`-`Z`)のみからなる文字列である

### Sample Explanation 1

1文字目の`C`と5文字目の`F`を残して消すことで`CF`が得られます。

### Sample Explanation 2

`FC`なら得ることが出来ますが、文字の順番を変えることは出来ないので、この場合は`CF`を作ることが出来ません。

### Sample Explanation 3

一文字も消さないこともありえます。

### Sample Explanation 4

1文字目を消すことで得られます。

## 样例 #1

### 输入

```
CODEFESTIVAL```

### 输出

```
Yes```

## 样例 #2

### 输入

```
FESTIVALCODE```

### 输出

```
No```

## 样例 #3

### 输入

```
CF```

### 输出

```
Yes```

## 样例 #4

### 输入

```
FCF```

### 输出

```
Yes```

# 题解

## 作者：Error_Eric (赞：8)

## 字符串~~新手级~~题目

这是一道字符串练手题，然而对于我这种蒟蒻来说，~~还是很打击自信心的~~。

首次提交，~~没初始化。~~

第二次提交，~~大小写写错。~~

一道红题让我觉得自己应当是“A+B”水平。


------------
看了一些大佬的题解，我感觉这道题目大佬的代码可能过于复杂了，于是蒟蒻来写题解，望大家指出不足。

看了另一些大佬的题解，我觉得他们的题解时间复杂度太大了，于是我来了一个O(N)复杂度的题解，个人认为属于最快的方法了。（~~我用的空间似乎也挺小的~~）

总体思路：先找到“C”,并且存储下结果（v0=1),在找到“F”时查询是否找到过“C”如果找到过，记录结果（v1=1）。

代码：（极致压行，你值得拥有）

```cpp
#include<iostream>//头文件~~~ 
using namespace std;//emm……
int main(){
	string a;	bool v[2]={0};//这个初始化害人不浅啊 
	cin>>a;//读入 
	for(int i=0;i<a.length();i++){//a[0]==>a[n-1]全部看一遍 
		if(a[i]=='C') v[0]=1;//出现了C 
		if(a[i]=='F'&&v[0])  v[1]=1;//出现了F 
	}
	if(v[1]) cout<<"Yes";//可以 
	else cout<<"No";//不行 
	return 0;
}
```


---

## 作者：FCBM71 (赞：5)

思路还是挺简单的，我们需要判断这个字符串是否是这样的形式: $ ...C...F...$ 

因此这题的主要思路就是，找到最靠前的一个C,找到最靠后的一个F。如果C出现在F之前，则符合条件

**AtCoder的题目需要严格按照格式输出，请注意大小写与换行! **

附上pascal代码：


------------
```pascal
program hrn;
 var
  s:string;
  i,l,sc,sf:longint; 
   //l表示字符串长度; sc,sf分别表示第一个C的坐标和最后一个F的坐标.
 begin
  read(s);
  l:=length(s);sc:=maxlongint; //sc一定要赋值为maxlongint！
  for i:=1 to l do if s[i]='F'then sf:=i; //寻找最后一个F
  for i:=l downto 1 do if s[i]='C'then sc:=i;//寻找第一个C
  if sc<sf then writeln('Yes')
           else writeln('No');  //注意输出格式
 end.
```


---

## 作者：唔啊唔 (赞：4)

一道较水的字符串模拟题
贴上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string a;
	cin>>a;
	int cnt=0;	//用来标记
	for(int i=0;i<a.size();i++){
		if(a[i]=='C'){
			cnt=1;
		}
		if(a[i]=='F'&&cnt==1){
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
```


---

## 作者：HOIer_9_42 (赞：3)

这是一段悲伤的故事……

/*^被和谐部分^*/

  最终，~~莫名WA的第八个点~~那个非常愚蠢的bug被“wjy2006”红名大佬一眼就看出来了。

  好了，话归正题。其实这道题~~很坑~~还是满水的，主要是让初学者复习简单的字符串模拟。我的大体思路是这样的——

  首先，在输入的字符串中查找第一个C，并记录第一个C的下标；同时查找在C后面的第一个F，如果找到了，标记下标，跳出循环。我的第一份代码如下——
  
  ```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma once
#include<bits/stdc++.h>
#define q register
typedef long long ll;
using namespace std;
string s;
ll tag1,tag2,ans,tot;
inline ll Min(ll a,ll b)
{
    return a<b?a:b;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>s;
    for(q ll i=0;i<s.length();i++){
        if((s[i]=='C')&&(!ans)){
            tag1=i,ans++;
               tot=tag1;   	
        }
        if(s[i]=='F'){
            tag2=i;   
            if(ans)   {
            break;//(1)
            }
        }
    }
    if((tag2)&&(tot<=tag2)){
        puts("Yes");//(2)
        return 0;
    }
    puts("No");
    return 0;
}
```

  这么一看好像没有什么毛病，但是经“wjy2006”大佬一提醒，这个程序输入“FF”也会输出“Yes”。我们检查一下程序就会发现，在上方程序标记的地方，如果模拟一下样例，此时的tag2是2，而tot是0，满足（2）处的判断条件，这就是bug所在。
  于是，我们修补一下bug，正确的代码如下——
  ```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("inline")//玄学优化可以不
//理它
#pragma once
#include<bits/stdc++.h>
#define q register
typedef long long ll;
using namespace std;
string s;
ll tag1,tag2,tot;
bool ans;
//这里tag1表示第一个C出现的位置，tag2表示第一
//个F出现的位置,ans是固定住第一个C的位置，保证
//判断的正确性
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>s;
    for(q ll i=0;i<s.length();i++){
        if((s[i]=='C')&&(!ans)){
            tot=tag1=i;
			ans=true;//第一个C出现了？  
        }
        if(s[i]=='F'){
            tag2=i;   
            if(ans){//如果C出现了，且后面有F，
       //那么一定符合条件，输出Yes，结束程序
                puts("Yes");
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}
```



---

## 作者：xieyufeng665 (赞：3)

这道题，目的就要找到一条字符串中存在"C"跟"F"两个字母 并且保证"C"总是在"F"在前面。根据这个思路 就可以直接打代码了
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
 int q,p,w[1000001],u[1000001],o;
 string a;
 int main()
 {
     cin>>a;//首先输入字符串
     for (int i=0;i<a.size();i++)//从0位开始循环
     {
         if (a[i]=='C') 
         {
             p++;
             u[p]=i+1;
         }//判断是否发现C这个东西，并统计其位置
         else if (a[i]=='F')
         {
            q++;
             w[q]=i+1;
         }
     }//判断是否发现F，同理 统计位置情况
     if (q>=1 && p>=1)
     {
     for (int i=1;i<=p;i++)
     {
         for (int j=1;j<=q;j++)
         {
             if (u[i]<w[j])
             {
                 o=1;
             }
         }
     }//循环，找到C是否在F的前面
	 if (o==1) cout<<"Yes"<<endl;//在前面则Yes
     else cout<<"No"<<endl;//否则No	
     }
     else cout<<"No"<<endl;//不存在两个数，直接No
     //以上为全部过程，希望能理解。
 }
```


---

## 作者：时律 (赞：3)

看到这题，立刻想起了$STL$里$string$的$find()$和$rfind()$是可以用的！

$find()$从程序的最左边找起，直到找到括号内的字符串，如没有找到返回$-1$。

$rfind()$从程序的最右边找起，直到找到括号内的字符串，如没有找到返回$-1$。

用这两个函数分别找一下最左边的$C$和最右边的$F$，再判断一下$F$是不是在$C$的右边即可。

这不就好了吗？

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;
	cin>>a;
	if(int(a.find('C'))!=-1 and int(a.rfind('F'))!=-1 and a.find('C')<a.rfind('F'))//个人码风问题，习惯用and而不是&&
		cout<<"Yes";
	else
		cout<<"No";
}
```

~~话说这题到底和CF有没有关系啊~~

---

## 作者：wpy233 (赞：2)

看了几篇题解、、、发现楼上大佬们的代码都写复杂了。。。

其实这题完全可以这样来做：
```
①当出现‘C’时，标记一下；
②当出现‘F’时，如果前面标记过‘C’，就直接输出“Yes”；
③如果没有输出，就输出“No”；
```
嘎嘎嘎、三步走~就AC了。。。。
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
string a;
int main()
{
    cin>>a;//输入字符串
    bool flag=false;//定义标记变量
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='C')
			flag=true;//如果碰到‘C’，就标记一下
		if(a[i]=='F')
			if(flag)//碰到‘F’，判断‘C’有没有出现过
			{
				cout<<"Yes"<<endl;//如果出现，就输出
				exit(0);//终止程序
			}
			else
				continue;//如果没有出现过，继续寻找
	}
	cout<<"No"<<endl;//输出“No”
    return 0;
}
```
QAQ希望大家AC愉快~~~

---

## 作者：zzhz (赞：1)

这题不难，直接上代码     
代码如下：
```cpp

#include<bits/stdc++.h>//万能头文件
using namespace std;
char a[10001];
bool f=false;
int main(){//主函数
    cin>>a;//输入
    int l=strlen(a);//a的长度
    for(int i=0;i<=l-1;i++){
        if(a[i]=='C'){
            for(int j=i;j<=l-1;j++){
                if(a[j]=='F')f=true;//判断是否存在CF
            }
        }
    }
    if(f==true)cout<<"Yes"<<endl;//存在，输出YES
    else cout<<"No"<<endl;//不存在，输出NO
    return 0;
}
```

最后提醒一点：     
AT的题一定要换行！    
本蒟蒻心地善良    
但是，     
非紧急情况不要用此功能！     

---

## 作者：pqlamz (赞：1)

```
#include<bits/stdc++.h>
using namespace std;
string b;
int main(){
	int q=0;
    cin>>b;
    for(int i=0;i<b.size();i++){
    	if(b[i]=='C')
	qwq++;//判是否有C
	if(q!=0&&b[i]=='F')//若有C且后面有F
	q-=10000000000;//q绝对比0小
	}
	if(q<0)//如果q比0小
	cout<<"Yes";
	else
	cout<<"No";
	return 0;
}
```

---

## 作者：willbe233 (赞：1)

****嗯****，水题~。

分析一下题目，也就是要找一前一后的C和F，那么，我马上就有了一个~~奇葩~~耗空间的思路。

我想，可以把所有C和F都存起来，因为存的时候是顺序的，所以查找字符串中CF就可以了。

贴一下代码：
```pascal
Var s,x:ansistring;
    n,i:longint;
Begin
        readln(s);
        for i:=1 to length(s) do //遍历字符串s
        Begin
                if s[i] in ['C','F'] then //当s串的第i个位置是C或F就存入x串。
                Begin
                        x:=x+s[i];
                end;
                
                if pos('CF',x)<>0 then //判断是否出现过CF，如果有，就输出Yes并跳出
                Begin
                        write('Yes');
                        halt;
                end;
        end;
        write('No'); //因为如果有前面就跳出程序了，所以如果执行到这一步肯定是找不到
end.
```

---

## 作者：DreamShadow (赞：1)

    对于这题：
    我觉得挺水的（对于Pascal的学者来说）

    var
      i:longint;
      st:string;
     begin
       readln(st);//输入不必多说了
       for i:=length(st) downto 1 do//务必倒着来，找到最后一个‘F’否则会错的啦~。
       if st[i]='F' then//如果等于，那么直接开始判断
       if (pos('C',st)<>0) and (pos('F',st)<>0) and (pos('C',st)<i) then //pos函数用一下，因为pos是找这个字符的第一个位置，刚刚好与题目所求的意思相符合。
       begin
         writeln('Yes');
         halt;//halt不结束程序，那么只有————死循环！！！
       end;
       writeln('No'); //no的情况不说啦
     end.


---

## 作者：vocaloid (赞：1)

看大家代码都比较长，我给个相对短一点的

做法很水，求出第一个$C$和最后一个$F$的位置，看看是否能凑成$CF$即可。

```cpp
#include<bits/stdc++.h>
#define inf 2147400000
using namespace std;
string s;
int fg1=inf,fg2;
int main()
{
	cin >> s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='C') fg1=min(fg1,i);
		else if(s[i]=='F') fg2=max(fg2,i);
	}
	printf("%s",fg1<fg2?"Yes":"No");
	return 0;
}
```

三目运算符真好用

---

## 作者：LW_h_FP (赞：1)

一道水体，可以直接打表，再记录一下，这样还适用于其他一些类似的题
```
#include<iostream>
#include<cstring>
using namespace std;

string a,b="CF"; //打表
int al,bl;

int main(){
	getline(cin,a);
	al=a.length();
	for(int i=0;i<al;i++)
		if(a[i]==b[bl]){ //当找到一个的时候加一
			bl++;
		    if(bl==2)   //都找到的时候就退出
		        break;
		}
	if(bl==2) cout<<"Yes"; //判断并且输出
	else cout<<"No";
	cout<<endl;//最后不要忘了打个换行
	return 0;
}
```

---

## 作者：迷失再黑夜里 (赞：0)

# 一道超级大水题啊！
## 废话少说直接上代码
```cpp
#include<bits/stdc++.h>//万能头文件不必解释！
using namespace std;
string s;//先定义一个字符串。
int jsq=0,sum=0,a=0;
int main()
{
	cin>>s;//输入字符串
	for(int i=0;i<s.size();i++)
	{
	     if(s[i]=='C' && sum==0) jsq=1;//判断这个字符是不是C，并且判断计算F的是不是的等于0，是则jsq=1；
	     if(s[i]=='F' && jsq==1) sum=1;//判断这个字符是不是F，并且判断计算C的是不是的等于1，是则sum=1；
	}
	a=jsq+sum;//用a把jsq和sum相加起来；
	if(a==2) cout<<"Yes"<<endl;//判断a是不是等于2，是就输出Yes；
	else cout<<"No"<<endl;//否就输出No;
	
	
	
	return 0;
}
```
//本篇真的是良心题解，这是本蒟蒻第一次写题解!! ~~希望给过！！！~~


---

## 作者：PrefixAMS (赞：0)

模拟 字符串入门题

枚举每一个

在遇见C之后才能判断F ~~所以我被卡了很长时间，难受~~

用两个bool 来判断即可

上代码

```cpp
#include<bits/stdc++.h>
#define us using namespace std;
us
#define MAXN [10001400]
#define ll long long
#define in cin>>
#define st strlen
#define bo bool
#define ch char
#define out cout<<
#define rrr return 0;
#define iC(x) if((x)=='C')flagC=true;
#define iF(x) if((x)=='F'&&flagC)flagF=true;
#define _if(a,b) if((a)&&(b))cout<<"Yes";else cout<<"No";
#define _for(i,a,b); for(int i=(a);i<=(b);i++)
#define IM int main()
#define begin {
#define end }
ch as MAXN;
bo flagC,flagF; 
IM
begin
	in as
	_for(i,0,st(as))//循环从头到尾比较
	begin
		iC(as[i])//判断是否是C
		iF(as[i])//判断是否在C后有F
	end
	_if(flagC,flagF)//判断是否符合条件 符合输出Yes 否则输出No
	rrr
end
```


---

## 作者：lky1433223 (赞：0)

# 显然的大水题

# [推销博客](https://www.cnblogs.com/Shiina-Rikka/p/11769551.html)
不过为了把这场比赛所有题都交一篇题解我还是写了2333

题目怎么说就怎么做

直接放代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200];
int main()
{
	cin >> s + 1;
	int len = strlen(s + 1);
	bool c,f;
	c = f = 0;
	for(register int i = 1; i <= len; ++i)
	{
		if(s[i] == 'C')
			c = 1;
		if(s[i] == 'F' && c)
			f = 1;
	}
	puts(c && f ? "Yes" : "No");
	return 0;
}
```

---

## 作者：QiFeng233 (赞：0)

#### 今天做语文作业的时候被烦到了，就想着刷一道水题，结果。。。
#### 第一次：CE（reutrn 0，淦）
#### 第二次：险些WA，因为我在最后输入了\n，但还好提交前发现了
#### 第三次：真WA了，我搜成c和f了（小写）
#### 正解：首先搜索有没有C，有的话再看C后边有没有F，都满足就Yes，否则No
然后我用的是一个叫strchr的库函数，用法是char* strchr(char* s1,char c)，返回一个指针，指向s1中第一次出现c的位置，没有则返回NULL。
#### 最后上AC代码
```cpp
#include<bits/stdc++.h>
char str[256],*c,*f;
int main(void){
    scanf("%s",str);
    c=strchr(str,'c');
    if(c!=NULL)f=strchr(c+1,'f');
    printf("%s",c!=NULL&&f!=NULL?"Yes":"No");
    reutrn 0;
}
```
#### 极限压行，最后的printf可以理解为
```cpp
if(c!=NULL&&f!=NULL)printf("Yes");
else printf("No");

```



---

## 作者：Suuon_Kanderu (赞：0)

我点开这题的标签，好，栈。那我就用栈吧。
思路：定义一个栈（手工也可以）

判断输入进来的是不是C，是则push进来。

如果输入进来是F判断栈顶是不是C，是的话，输出YES，否则输出NO。

很清晰吧。

对于不熟悉STL的同学，我解释一下，a.push(x)意为将x放入栈顶，a.top()意为取栈顶元素，这里要注意了，a.pop()意为弹出栈顶元素。要和top区分开来。

另外，在介绍几个常用函数

empty()：判断栈是否为空。
size（）：栈中元素数量


```
#include<bits/stdc++.h>
using namespace std;
stack<char> a;
char s;
int main() 
{  
    while(cin>>s)
    {
    	if(s=='C')a.push(s);//压栈
    	if(s=='F')
	{
        if(a.top()!='C')//判断栈顶是不是C
    	{cout<<"NO"<<endl;return 0;}
    	else 
    	{cout<<"YES"<<endl;return 0;}
	}
	
	}
	return  0;	  	
}
```
但是，这就完了吗？ return 0 好像预示着什么。是不是循环结束后要输出一个什么啊。

对，我找到了一组hack数据 C。 这样只会进栈，不会判断啊。

so,完整代码应该在后面加一个
```
		cout<<"NO"<<endl;
```
这卡了我很多次




---

## 作者：明空 (赞：0)

~~题意很好懂所以直接上代码~~
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105];
int main()
{
	cin>>s;//输入字符串
	int n=strlen(s);//定义一个n=字符串的长度
	int c=0,m=0;//c记录找到C的位置，m记录找没找到C（0为没找到，1为找到了）
	for(int i=0;i<n;i++)//因为是从s[0]开始存的，所以从s[0]开始找
	{
		if(s[i]=='C')//若找到了C
		{
		c=i;//记录位置
		m=1;//找到了
		break;//结束循环
		}	
	}
	int f=0;//记录找没找到F
        for(int i=c+1;i<n;i++)//因为在s[c]时找到了C且F必须在C的后面才能构成CF，所以直接从s[c+1]开始找F 
	{
		if(s[i]=='F') //若找到了F 
		{
		f=1;//记录找到了 
		break;//结束循环 
		}	
	}
	if(m==1&&f==1) cout<<"Yes";//若C和F都被找到了，输出Yes 
	else cout<<"No";//若都没找到或只找到一个，输出No 
    return 0;//养成写return 0的好习惯 
}  //完结撒花 
```


---

## 作者：呵呵侠 (赞：0)

有一些小伙伴是这么写的：
```
#include <cstring>
#include <iostream>//我不喜欢万能头文件
using namespace std;
int main()
{
    char a[100000005];//开一个巨大的数组
    cin>>a;
    bool c=0,f=0;//检测字母存在性
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i]=='c')
            c=1;
        if(a[i]=='f'&&c==1)
            f=1;//其实已经可以输出了
    }
    if(c==1&&f==1)
        cout<<"Yes";
    else
        cout<<"No";
    return 0;//好习惯养成
}
```
得了40分

算了，我好心告诉你们BUG的位置

BUG在for循环里
```
for(int i=0;i<strlen(a);i++)
    {
        if(a[i]=='c')
            c=1;
        if(a[i]=='f'&&c==1)
            f=1;//其实已经可以输出了
    }
```

if判断里
```
	if(a[i]=='c')
            c=1;
        if(a[i]=='f'&&c==1)
            f=1;//其实已经可以输出了
```
if(a[i]=='c')

if(a[i]=='f'&&c==1)


应该是大写字母

想不到吧哈哈哈

```
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    char a[100000005];
    cin>>a;
    bool c=0,f=0;
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i]=='C')
            c=1;
        if(a[i]=='F'&&c==1)
        {
            cout<<"Yes";
            return 0;
        }
    }
    cout<<"No";
}
```
附上另一份代码（同样AC）

---

## 作者：Xiamo_Azure (赞：0)

# 这道题是不是恶意评分鸭？？？

------------
本体本意：问一个字符串S（2<=S<=100）中是否可以去掉几个字符，变成CF（大写）两个字母，如果可以，输出‘Yes’，不可以，输出‘No’。 输入格式： 字符串S 输出格式： 如果可以去掉几个数字，变成CF（大写），输出‘Yes’，不可以，输出‘No’

------------
我的理解：前面有个C 后面有个F 就输出“Yes” 否则 输出“No”

------------
不废话 放代码！
   
   
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;//输入 字符串 
	int len=s.size();//提取字符串长度 
	for(int i=0;i<=len;i++)//前面 
	{
		if(s[i]=='C')//前面的C 
		{
			for(int j=i;j<=len;j++)//后面 
			{
				if(s[j]=='F')//后面的F 
				{
					cout<<"Yes"<<endl;//输出 
					return 0;//结束 
				}
			}
		}
	}
	cout<<"No"<<endl;//没有C和F 输出 
	return 0;
}
```

---

## 作者：TARMO (赞：0)

这是一道~~难~~大水题

一边输入一边输出

搞定~
```
#include<bits/stdc++.h>
using namespace std;
bool x=0,y=0;
char a;
int main()
{
	while（a!='\n')
	{
		a=getchar();
		if(a=='C') x=1;
		if(a=='F'&&x) y=1;
	}
	if(x&&y) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```
~~（control+C会有大惊喜）~~

---

## 作者：Ace_Radom (赞：0)

## 这题……

	不需要花心思去删除，只需查找即可
    从第一个开始查找，依次查找到“C”和“F”即可
    
也可以在读入时就开始查找，使用如下的while写法即可

```
while( cin >> x )
{
//......
}
```

但不会在读入完成后直接结束

# 需要打入Ctrl^z才可

## 不要认为是死循环

Code：

```
#include<bits/stdc++.h>
bool C = false,ans = false;  
//C存放字母“C”是否出现
//ans存放答案
void Ss( char c ){
	if ( ( C ) && ( c == 'F' ) )  
    //由于必须以“CF”的形式出现，在判断出现“F”时需先判断“C”是否出现
		ans = true;  //都出现了，ans变true
	return;
}
using namespace std;
int main(){
	char c;
	while ( cin >> c )  //程序段解释如上
	{
		if ( c == 'C' )  //“C”出现了
			C = true;
		Ss( c );
	}
	if ( ans )  //ans为true，输出Yes；反之，输出No
	{
		printf( "Yes" );
		return 0;  //直接return是个人习惯，用else当然可以
	}
	printf( "No" );
	return 0;
}
```

---

## 作者：skyping (赞：0)

STL大法

string 中 find,rfind

find:若查找成功，返回按查找规则找到的第一个字符或子串的位置；若查找失败，返回npos，即-1（打印出来为4294967295).---<from baidu>

refind:反向查找


```cpp
#include<bits/stdc++.h>
using namespace std;
string s; 
int main(){
	cin>>s;
    //
	if(s.find('F')==std::string::npos){printf("No");return 0;}//如果查不到
    //T的数据,如‘C’
	if(s.find('C')<s.rfind('F')) printf("Yes");
	else printf("No");
	return 0;
}
```
感谢skyping,newblash

---

## 作者：天野_阳菜 (赞：0)

大概思路：先读入，然后找C和F，找到了C就把它的位置记录下来，找到了F就看看之前有没有C，如果之前有就OK了，如果之前没有就继续找

奉上蒟蒻长长的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool first_C=true;//是否为第一个C
bool first_F=true;//是否为第一个F
int C_POS=-1;//C的位置
int rp;//0：没找到  1：只找到C  2：都找到了
char command[1000000];//输入
int main()
{
    gets(command);//输入
    for(int i=0;i<strlen(command);i++)//一个一个判断
    {
        if(command[i]=='C' && first_C)//如果找到了C
        {
            rp++;
            first_C=!first_C;//不是第一个C了
            C_POS=i;//C的位置
        }
        if(command[i]=='F' && first_F && i>C_POS && C_POS!=-1)//找到了F
        {
            rp++;
            first_F=!first_F;//不是第一个F了
        }
        if(rp==2)//如果已经符合要求了
        {
            cout<<"Yes";//输出yes
            return 0;//退出
        }
    }
    cout<<"No";//输出no
    return 0;//退出
}
```

---

## 作者：_vercont (赞：0)

## AT2084  CF
### 这里只放主函数代码

    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);//读入优化
    register string st;//定义字符串
    register bool c=false,f=false;//判断是否存在C,F
    cin>>st;//输入
    int len=st.length();//字符串长度
    register char ch[len];//定义字符数组
    for(int i=0;i<len;i++)ch[i]=st[i];//字符串转字符数组
    for(register int i=0;i<len;i++){
        if(ch[i]=='C')c=true;//判断C
        if(c)if(ch[i]=='F')f=true;//判断F
        if(c&&f){
            cout<<"Yes\n";//可以组成CF
            return 0;//结束程序
        }
    }
    cout<<"No\n";//无法组成CF
    return 0;//结束程序

---

## 作者：damage (赞：0)

# 还是[正则表达式](/blog/damage/solution-at3602)

---

(点击上面的[链接](/blog/damage/solution-at3602))

### 正则表达式

其中```.*```表示匹配任意个任意字符(即输入字符串中要删除的)。

如```LUOGUCHENZHESHISHENBENFJULAO```这个字符串匹配正则表达式```.*C.*F.*```，因为其中含有字符```C```和字符```F```并且```C```在```F```前面，所以可以匹配成功。

其他详情可以自己网上阅读资料了解。

---

```java
import java.util.Scanner; //java输入库
import java.util.regex.*; //java正则表达式库
public class Main //洛谷里java程序默认类名(文件名)为Main
{
	public static void main(String args[])
	{
		Scanner input=new Scanner(System.in); //相当于输入流
		String str=input.nextLine(); //输入字符串(其实是读取一行)
		String pattern=".*C.*F.*"; //要被匹配的正则表达式
		if(Pattern.matches(pattern,str)) System.out.println("Yes");  //如果匹配成功就输出"YES",函数参数顺序千万不能反了!
		else System.out.println("No"); //反之则输出"NO"
   }
}
```

# 事实证明：正则表达式很适用于这种题目（建议使用```java```或```python```写这类正则表达式的题目）

---

## 作者：秋本馄淡 (赞：0)

首先，要用pos函数找到C字母的位置，但是F的位置不能用pos函数找，因为pos函数找到的是第一个F，所以第一个F可能不在C的前面。
所以，我们要用一个循环，从字符串末端往前扫。

所以，代码很简单：
```pascal
var
  p1,p2,i:longint;
  s:string;
begin
  readln(s);
  p1:=pos('C',s); //用pos函数找到C最靠前的位置
  for i:=length(s) downto 1 do  //从后往前扫
    if (s[i]='F') and (p1<i) and (p1<>0) then  //这是所有的条件
    begin
      writeln('Yes');  //符合就输出
      halt;  //别再往后扫了
    end;
  writeln('No');  //一直没扫到的话就回到这里，输出No
end.
```

---

## 作者：Kai_Fu (赞：0)

### 我有一个换行可能会让你砸烂电脑
### 被换行卡一下午...
## 思路：我是用栈做的，如果是C的话就进栈，碰到F就出栈并且直接跳出循环，最后判断出栈的那一个元素是否为C就可以了
#### 可能这种思路不如其他的一些简单明了，但是多几种做法也是好的(^o^)
#### 下面是AC代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string.h>
using namespace std;
int main()
{
    char a[500],stack[500],t;//t用来存出栈元素
    int top=0;//指针初始化0
    cin>>a;//读入
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i]=='F'&&top==0)
        continue;//如果栈是空的且读到了F，就进行下一次循环
        else if(a[i]=='C')
        {      
        stack[top++]=a[i];//读到了C就进栈
        }
        else
        { 
            if(a[i]=='F')
            {
            t=strack[--top];//读到F就出栈
            break;//因为已经有一对CF了，所以后面没必要读下去，那么就跳出了
            }
        }
    }
    if(t=='C')
    cout<<"Yes"<<endl;//如果出来的是C就Yes
    else
    cout<<"No"<<endl;//否则No
    
}
```
### 以后一定得看清换不换行T T
### 请勿直接Copy

---

## 作者：xyn0901 (赞：0)

看了那么多题解，为什么要那么麻烦？

我的思路：找F，看前面有没有C.

```pascal
var s:string;
i:integer;
c,f:boolean;
begin
c:=false;
f:=false;
read(s);
for i:=1 to length(s) do
begin
if s[i]='C' then c:=true;
if s[i]='F' then f:=true;
if not(c) then f:=false;
end;
if c and f then writeln('Yes') else writeln('No');
end.
```

---

## 作者：char32_t (赞：0)

# 题解 AT2084 【CF】
------------
因为要求`F`应出现在`C`的后面，所以可以用两个标志变量进行标记，在出现`C`时标记C，在出现`F`且C已经被标记时标记F，最后判断F是否被标记

code：
```cpp
#include<cstdio>
#include<cstring>
char a[10010];//字符数组 
bool c, f;//标志变量 
int main() {
	scanf("%s", a);//读入字符串 
	for(int i=0; i<strlen(a); i++) {
		if(a[i]=='C') c=true;//找到C后标记 
		if(a[i]=='F'&&c==true) f=true;//在找到C后再找到F时标记 
	}
	if(f==true) printf("Yes\n");//如果找到C和F输出Yes 
	else printf("No\n");//否则输出No 
	return 0;
}
```

---

## 作者：_newbie_ (赞：0)

```c
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    string a;
	cin>>a;
	int flag=false;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='C')
		flag=true;  //判断标志 
		if(a[i]=='F'&&flag==true)  //f在c的后面，表示有cf 
		{
			cout<<"Yes";
			return 0;
		}
	} 
	cout<<"No"<<endl;  //否则输出no 
    return 0;
}
```

---

## 作者：Soyilieber (赞：0)

拿char做一下吧

顺带pascal code：

```
var
    s:longint;
    ch:char;
begin
    while not eoln do//经典无限读入
        begin
            read(ch);
            if ch='C' then s:=1;//出现了C就用s标记
            if (s=1)and(ch='F') then//有C并有F就……
                begin
                    writeln('Yes');//输出Y
                    halt;//haruto！
                end;
        end;
    writeln('No');//如果上面输出了的话这句语句就不会被执行_（输出N）
end.
```

---

