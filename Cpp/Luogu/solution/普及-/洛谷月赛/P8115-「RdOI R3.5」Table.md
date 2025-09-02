# 「RdOI R3.5」Table

## 题目背景

小 A 想要打表过题，但是代码长度过长。他想到了把数字用十六进制表示有时比用十进制表示更短，决定把答案表用十六进制进行改写。

## 题目描述

我们定义下文中的「十六进制」均用数字 $0\sim 9$ 和大写英文字母 $\tt A\sim F$ 表示，且每个十六进制数字都包含前缀 $\colorbox{#ddd}{\tt 0x}$。

给出若干个用大括号包裹，用逗号分隔的十进制整数，代表小 A 的答案表。你需要对答案表内的每个数字进行改写：

- 若该整数使用十六进制表示所占字符数小于或等于十进制表示，则将该数改写为十六进制。
- 否则，该数保留十进制不变。

输出改写后的答案表。


## 说明/提示

### 样例解释

#### 样例 \#1

- $1$ 用十六进制表示为 $\tt 0x1$，共 $3$ 个字符，长度大于十进制的 $1$ 个字符。
- $314159$ 用十六进制表示为 $\tt 0x4CB2F$，共 $7$ 个字符，长度大于十进制的 $6$ 个字符。
- $3141592653589793$ 用十六进制表示为 $\tt 0xB29430A256D21$，共 $15$ 个字符，长度小于十进制的 $16$ 个字符。

#### 样例 \#2

输入为空数组，所以输出也应为空数组。

### 数据范围及约定

本题共五个测试点，每个测试点 20 分，总分数为各测试点分数之和。

记答案表中共有 $n$ 个整数，这些整数分别为 $a_1,a_2,\cdots,a_n$。则对于 $100\%$ 的数据，$0\le n\le10^3$，$0\le a_i < 2^{64}$。

## 样例 #1

### 输入

```
{1,314159,3141592653589793}```

### 输出

```
{1,314159,0xB29430A256D21}
```

## 样例 #2

### 输入

```
{}```

### 输出

```
{}```

# 题解

## 作者：wimg6_ (赞：13)

# P8115 题解

题目指标 [Table](https://www.luogu.com.cn/problem/P8115).

该文章同步发表于 [我的博客](https://www.luogu.com.cn/blog/Kingson123456/) 内。

审核一经通过，他人不得盗用博客。若未通过，引用时需注明出处，并私信作者。

### 正解

读题。题意挺明确的，要你将十进制转换成十六进制。如果十六进制比十进制位数少两个及以上，则使用十六进制，否则使用十进制。

进制转换非常容易，也就小学奥数的难度。如下所示：

例：需使 $(A)_{10}=(B)_{16}$，求 $B$ 的值。

可以使用短除法：

首先 $A \div 16= s_1 …… r_1$，记录 $r_1$。

再 $s_1 \div 16= s_2 …… r_2$，记录 $r_2$。

接着 $s_2 \div 16= s_3 …… r_3$，记录 $r_3$。

以此类推，直到 $s_i=0$ 为止，有 $r_1,r_2,r_3,……,r_{i-1}$。

有 $B=\overline{r_{i-1}\ r_{i-2}……r_3\ r_2\ r_1}$。

即可完成转化。

### 代码

这道题代码难点即在实现短除法以及进行比对。请读者依照以上分析与下列代码自行理解。

同时需要注意，这道题的 long long 很大几率会炸掉，所以我一开始就选了 unsigned long long，但是完全没有必要使用高精度。

以下是代码：

```
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
unsigned long long n,f,p,q[1005];
string s;
char r;
int main()
{
    cin>>r;
    while(cin>>q[++n])
		cin>>r;
    printf("{");
    for(int i=1;i<n;i++)
	{
        s="",f=q[i],p=0;
        while(f) p++,f/=10;
        f=q[i];
        while(q[i])
		{
            if(q[i]%16>9) s=char(q[i]%16-10+'A')+s;
            else s=char(q[i]%16+'0')+s;
            q[i]/=16;
        }
        s="0x"+s;
        if(s.size()<=p) cout<<s;
        else cout<<f;
        if(i<n-1) cout<<",";
    }
    return !printf("}");
}
```


---

## 作者：Ginger_he (赞：12)

# 题解
1. 用字符串读入，特判 $\texttt{\{\}}$ 的情况；  
2. 将读入的字符转化为数为止，即 `x=x*10+s[i]-'0'`;
3. 若遇到 $\texttt{,}$ 或 $\texttt{\}}$，将 $x$ 转化为十进制和十六进制比较长度即可；  

放上转化为十六进制的代码：
```cpp
while(x)
{
    if(x%16<10) s+=x%10+'0';
    else s+=x%10+'7';
    x>>=4;
}
s="0x"+s;
```

---

## 作者：Hanghang (赞：11)



只有 $5$ 个数据点，好评！！！

简单分析一下，就是将十进制转化为十六进制，然后判断一下两个数的位数。

坑点：

1，要开 ull。

2，特判没有数的情况。

具体看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

string c;//读入数据
unsigned long long x,y,z,zz,w[23],W,l;//记得开ull
int main()
{
	cin>>c;l=c.size();//l表示长度
	if(l==2){cout<<c[0]<<c[1];return 0;}cout<<c[0];//特判没有数的情况
	for(int i=1;i<l;i++)
	{
		if(c[i]!=','&&c[i]!='}')
		{
		    x=x*10+c[i]-'0',z++;//如果是数字，就转化
		}
		else
		{
			y=x;W=0;
			while(y>0)
			{
				w[++W]=y%16;y/=16;//十进制十六进制,W表示位数，w数组的每一位代表数的每一位
			}
			if(W+2<=z)//即要转化为十六进制
			{
				cout<<"0x";
				for(int j=W;j>0;j--)
				{
					if(w[j]<10)cout<<w[j];
					else cout<<char(w[j]-10+'A');//将10-15转化为A-F
				}
			}
			else cout<<x;
			cout<<c[i];x=0;z=0;//记得输出符号，别忘了清零
		}
	}
	return 0;
}
```

---

## 作者：minstdfx (赞：10)

来写一发题解。

看题解区的大家都用各种搞法写出了这道签到题，~~证明这场比赛还是有人打的，我很欣慰~~。那么我来讲一讲我当时验题的时候的做法。

首先注意到题目需要开 `unsigned long long`，不用 `__int128`，~~真是太良心了（棒读）。~~

我们需要用到下面这个东西：

```cpp
int sprintf(char *str, const char *format, ...);
```

这个东西，使用和 `printf` 一样的格式输出，不过是输出到给定的字符数组 `str` 里面去。

那么在我~~小学二年级~~普及二等奖的时候就学过，在 `printf` 家族的格式化字符串标识符中，`%x` 可以表示输出一个无符号十六进制整数。如果是 `long long` 的 $64$ 位整数，使用 `%llx`。题目中需要大写字母并加上 `0x` 前缀，那么 `0x%llX`。

搜一下这个函数的返回值？

>如果成功，则返回写入的字符总数，不包括字符串追加在字符串末尾的空字符。如果失败，则返回一个负数。

诶这就很舒服了啊，连长度都统计好了。  
记得特判空序列
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	// printf("%llx\n",1ull+LLONG_MAX);
	unsigned long long a;
	char b,c=0,s1[201],s2[201];
	putchar('{');
	while(scanf("%c%llu",&b,&a)==2)
	{
		if(c) putchar(c);
		for(char *p=(sprintf(s1,"%llu",a)<sprintf(s2,"0x%llX",a)?s1:s2);*p;++p)
			putchar(*p);
		c=',';
	}
	putchar('}');
	putchar('\n');
	return 0;
}
```
~~然后在另一个验题人写传统做法的时候我花两分钟就切了。~~

传统做法的代码也不长，很简单。  
就考虑读进来然后和快速输出一样弄就行了。
```
#include <bits/stdc++.h>
using namespace std;
const char *f="0123456789ABCDEF";
std::string _0x16(unsigned long long k)
{
	std::string res="";
	if(k>15) res=_0x16(k>>4);
	res+=f[k&15];
	return res;
}
std::string _10(unsigned long long k)
{
	std::string res="";
	if(k>9) res=_10(k/10);
	res+=f[k%10];
	return res;
}
int main()
{
	// printf("%llx\n",1ull+LLONG_MAX);
	unsigned long long a;
	char b,c=0;
	putchar('{');
	while(scanf("%c%llu",&b,&a)==2)
	{
		if(c) putchar(c);
		std::string s10=_10(a),s16="0x"+_0x16(a);
		if(s10.length()<s16.length())
			printf(s10.c_str());
		else printf(s16.c_str());
		c=',';
	}
	putchar('}');
	putchar('\n');
	return 0;
}
```

---

## 作者：Jerrlee✅ (赞：5)

## 题意
把用大括号括起来，逗号隔开的数转为 $16$ 进制（开头都有 `0x`），如果比 $10$ 进制表示的字符串长度短或等于，就输出 $16$ 进制的表示，否则输出 $10$ 进制的表示（放在大括号里）。
## 思路
这题一加入主题库就有很多人发讨论求助，看来大家不太擅长大括号的处理。所以本题解分成三部分来讲解：

### 一：大括号的处理
开头和结尾的大括号直接输出，每次读入一个 `char`，如果是数，就把它转 `int` 并加到数 $n$ 中，如果是逗号，**输出这个字符**并将 $n$ 转 $16$ 进制与十进制的长度对比。

然后我们能写出以下代码（`solve` 是转 $16$ 进制的函数）：
```cpp
char c;
cin>>c;
cout<<c;
int n=0;
char a;
cin>>a;
if(a=='}'){solve(n);cout<<a;return 0;}
else if(a!=','){n=n*10+((int)a-48);goto be;}
else{solve(n);cout<<a;n=0;goto be;}
```
即使 $16$ 进制转换写对，这个主函数只有 $80$ 分，为什么？

看向样例 $2$：

in：`{}`

out：`{0}`

ans：`{}`

我们会发现，要对读入的字符串特判：直接读入一对空大括号时直接输出！

code for main：
```cpp
char c;
cin>>c;
cout<<c;
int n=0,f=0;
if(0){//除了 goto，永不进入此 if 语句
    be:
    f=1;
}
char a;
cin>>a;
if(a=='}'){if(!f){return cout<<a,0;}solve(n);cout<<a;return 0;}
else if(a!=','){n=n*10+((int)a-48);goto be;}
else{solve(n);cout<<a;n=0;goto be;}
```
### 二：转进制的处理
像数位分离一般的处理，每次模 $16$，这一位数小于等于 $10$ 就正常处理到字符串中，否则用 `A` 此类字母处理到字符串中。

核心处理：
```cpp
while(a>0){
    y=a%16;
    if(y<10) s=char('0'+y)+s;
    else s=char('A'-10+y)+s;
    a=a/16;
}
```
比较字符串长度只要将处理好的字符串开头补 `0x` 并与 `main` 处理好的 $n$ 转字符串比长度即可。

code for solve：
```cpp
int y=0;
string s="";
string st=to_string(a);//C++11 的函数，将 int 转为 string 类
if(a==0){
    cout<<0;
    return;
}//数是 0 是必须特判！
while(a>0){
    y=a%16;
    if(y<10) s=char('0'+y)+s;
    else s=char('A'-10+y)+s;
    a=a/16;
}
s="0x"+s;
if(st.length()>=s.length()) cout<<s;
else cout<<st;
```
### 三：一些特殊的注意点
这题是需要 `unsigned long long` 的！处理数字时，因为 `unsined`，所以无需管负数的情况。
## 整体代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
void solve(int a){
    int y=0;
    string s="";
    string st=to_string(a);
    if(a==0){
        cout<<0;
        return;
    }
    while(a>0){
        y=a%16;
        if(y<10) s=char('0'+y)+s;
        else s=char('A'-10+y)+s;
        a=a/16;
    }
    s="0x"+s;
    if(st.length()>=s.length()) cout<<s;
    else cout<<st;
}
signed main(){
    char c;
    cin>>c;
    cout<<c;
    int n=0,f=0;
    if(0){
        be:
        f=1;
    }
    char a;
    cin>>a;
    if(a=='}'){if(!f){return cout<<a,0;}solve(n);cout<<a;return 0;}
    else if(a!=','){n=n*10+((int)a-48);goto be;}
    else{solve(n);cout<<a;n=0;goto be;}
}
```
[AC 记录](https://www.luogu.com.cn/record/68650641)

Add：在比赛中加上了快读，卡进了 $17$ ms，需要的也可以参照：<https://www.luogu.com.cn/record/68616414>

---

## 作者：yeshubo_qwq (赞：3)

## 题意
给你一些用大括号括起来，用逗号分开的十进制数，如果将其转为十六进制长度小于等于原十进制数，就转换，否则不转换。

要求输出最后的结果。
## 思路
遇到不同的字符，做不同的操作。

遇到左大括号，输出。

遇到数字，保存下来。

遇到逗号，判断前面的数输出十进制还是十六进制，并输出相应的进制及逗号。

遇到右大括号，处理方式同逗号，唯一区别在于最后输出的是右大括号。
## 代码
```cpp
#include<bits/stdc++.h>
#define int unsigned long long//注意要开unsigned long long 
using namespace std;
const string num="0123456789ABCDEF";
int s,i,len,x,l,j;
char a[50],c;
int get(char x){//字符对应的数 
	if(x>='A')return x-'A'+10;
	return x-'0';
}
void print(int x){//转十六进制并输出
	if(x/16>0)print(x/16);
	putchar(num[x%16]);
}
signed main(){
	c=getchar();
	while(c!='}'){
		if(c=='{'){//遇到左大括号 
			putchar('{');
			c=getchar();continue;
		}
		if(c==','){//遇到逗号 
			s=0;
			for(i=len,j=1;i>=1;i--,j*=10)
				s=s+get(a[i])*j;
			x=s;
			l=2;while(x>0)x/=16,l++;//求出十六进制长度 
			if(l<=len){
				putchar('0');putchar('x');
				print(s);
			}
			else for(i=1;i<=len;i++)putchar(a[i]);
			putchar(c);len=0;
			c=getchar();continue;
		}
		a[++len]=c;c=getchar();//遇到数字存下来 
	}
	//最后还有1个右大括号要做 
	s=0;
	for(i=len,j=1;i>=1;i--,j*=10)
		s=s+get(a[i])*j;
	x=s;l=2;
	while(x>0)x/=16,l++;
	if(l<=len){
		putchar('0');putchar('x');
		print(s);
	}
	else for(i=1;i<=len;i++)putchar(a[i]);
	putchar('}');
	return 0;
}
```


---

## 作者：Jorisy (赞：3)

该题是一个典型的进制转换问题。

我们知道，十六进制的数字包含 $0 \sim 9,A \sim F$ 十五个字符，其中 $A \sim F$ 分别对应十进制的 $10 \sim 15$。

因为出现了字母，所以我们需要进行一些特殊操作。其中最典型的就是开一个字符串常量 $R$，$R_i$ 表示 $i_{10}$ 所对应的 $i_{16}$。

进制转换部分：
```cpp
const string R="0123456789ABCDEF";

string f(ull n)//题目数字最大是 2^64-1，需要 unsigned long long
{
	string res="";
	while(n)
	{
		res=R[n%16]+res;
		n/=16;
	}
	return "0x"+res;
}
```
AC Code：
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const string R="0123456789ABCDEF";

string f(ull n)//十进制转十六进制
{
	string res="";
	while(n)
	{
		res=R[n%16]+res;
		n/=16;
	}
	return "0x"+res;
}

int main()
{
	string s;
	cin>>s;
	if(s=="{}")//空数组特判
	{
		cout<<s;
		return 0;
	}
	cout<<'{';
	for(int i=1;i<s.size();i++)
	{
		ull x=0;//用于截取十进制数
		int l=0;//用于记录十进制数长度
		while(isdigit(s[i]))
		{
			x=x*10+s[i++]-48;//截取数字
			l++;
		}
		string y=f(x);
		if(y.size()<=l) cout<<y;//十六进制长度小于等于十进制长度则输出十六进制
		else cout<<x;
		cout<<s[i];//输出逗号或右大括号
	}
   //因为在循环末尾已经输出逗号或右大括号，因此这里无需再次输出
 	return 0;
}

```

---

## 作者：ckk11288 (赞：2)

一道难一点的入门题，但题意简洁明了。我们就跟着题意做：先用字符串存储答案表中数的 16 进制形式，接着比较改动后的数的位数（注意要加前缀）与原数的位数，若改动后位数更少则保留 16 进制形式。

当然别忘了有特判：若表为空，直接输出。

**Code:**
```cpp
#include <bits/stdc++.h>
using namespace std;
char a;//字符，用于分隔数
int main()
{
    unsigned long long n;//无符号超长整型，符合题目要求
    string s;//存储n的16进制形式
    while(1)
    {
    	int ansn=0;
        cin>>a;//输入数前的字符，不参与运算
        if(a=='}') break;//当a为右括号，结束输入
        if(scanf("%llu",&n)!=1)//若表为空，输出并退出
        {
        	cout<<"{}"<<endl;
        	return 0;
		}
       	unsigned long long nn=n;
       	unsigned long long ss=n;
    	while(nn!=0)
    	{
    		nn/=10;
    		ansn++;
		}//算出原数有几位
        s="";//字符串初始化
        if (n == 0)
        {
        	s = "0";//若n为0则不变
		} 
        while (n != 0)
        {
            if (n%16 >9 )
                s += n%16 - 10 +'A';
            else
                s += n%16 + '0';
            n = n / 16;
        }//转16进制操作
        reverse(s.begin(), s.end());//调转顺序
        if(s.size()+2<=ansn) cout<<a<<"0x"<<s;//改动后更短（前缀为0x），输出16进制形式
        else cout<<a<<ss;//否则输出原数
    }
    cout<<"}";//输出右括号
    return 0;
}
```

---

## 作者：FFTotoro (赞：2)

先读入字符并将它们转化为十进制数，压入一个 `std::vector`，然后一个一个弹出来处理（将它们转化为十六进制数，判断哪一个占字符位比较多）即可。

求十进制数的位数可以使用 cmath 中的 `log10()` 函数。

模拟题注意读入和输出时的细节。读入时可以使用 cctype 中的 `isdigit()` 函数来判断是否是数字，输出时注意输出 $16$ 进制数时的格式。

放代码：

```cpp
// 本题的坑点：使用该方法 unsigned long long 要开，不然会 RE 或 WA
#include<bits/stdc++.h>
using namespace std;
int main(){
  char c; bool f=false;
  vector<unsigned long long> v;
  while(c=getchar()){
    if(isdigit(c)){
      unsigned long long x=c-48;
      while(c=getchar()){
        if(isdigit(c))x=x*10+c-48;
        else if(c=='}'){f=true; break;}
        else break;
      }
      v.emplace_back(x);
    }
    if(f||c=='}')break;
  } // 读入处理
  putchar('{');
  for(int i=0;i<v.size();i++){
    if(!v[i])putchar(48);
    else{
      unsigned long long d=v[i]; vector<int> v2;
      while(v[i])v2.emplace_back(v[i]&15),v[i]>>=4;
      if(v2.size()+2>(int)log10(d)+1)printf("%lld",d); // 判断长短
      else{
        printf("0x");
        for(int j=v2.size()-1;j>=0;j--){
          if(v2[j]>9)printf("%c",v2[j]+55);
          else printf("%d",v2[j]);
        } // 输出十六进制数
      }
    }
    if(i!=v.size()-1)putchar(','); // 按格式输出逗号
  }
  putchar('}');
  return 0;
}
```

---

## 作者：jxbe6666 (赞：2)

### 题意：

- 给你一个一个字符串，字符串中仅包含大括号、逗号和数字，不包含空格和其他字符等。
- 要求你在十进制和十六进制中挑选字符数少的输出。
- 每个数 $0 \le n <2^{64}$，需要使用 $\text{unsigned long long}$ 无符号长整型数

### 思路：
这道题的难点是输入。先用 $\text{getchar()}$ 读入大括号。再用 
``` cpp
scanf("%llu%c",n,c);
```
读入每个数。注意这有一个特点，无符号长整型数的标识符是 $\text{llu}$。因为 $\text{ll、l、L}$ 这类是长度修饰符，修饰在 $\text{u、d、f}$ 前面(有些搭配不行)。  
至于比较长度、转十六进制，相信各位大佬都会了，我就不说了~~逃~~。

### AC Code：
``` cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    unsigned long long i = 0, n, m, num[100], a = 0, b = 0;
    char ch = getchar(), hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    cout << '{';//
    while (ch != '}')
    {
        a = 0, b = 0, i = 0;
        memset(num, 0, sizeof(num));//
        scanf("%llu%c", &n, &ch);
        if (ch == '{')//如果为{}的空串就直接输出，并结束
        {
            cout << "}";
            return 0;
        }
        if (n == 0)//特判0
        {
            cout << 0 << ch;
            continue;
        }
        m = n;
        for (unsigned long long i = m; i > 0; i /= 10)//十进制位数
        {
            a++;
        }
        while (n > 0)//十六进制位数
        {
            num[i++] = n % 16;
            n = n / 16;
            b++;
        }
        b += 2;//别忘记加2
        if (b <= a)// 十六进制少
        {
            cout << "0x";//先输出0x
            for (int j = i - 1; j >= 0; j--)
            {
                cout << hex[num[j]];
            }
            cout << ch;//输出，或者}
        }
        else
        {
            cout << m << ch;//同理
        }
    }
    return 0;
    cout<<"qwq";
}
```
[qwq](https://www.luogu.com.cn/record/68794433)


---

## 作者：WaTleZero_pt (赞：1)

## 显而易见的，本题需要用到进制转换。

说明：如果您已掌握进制转换的方法，请跳过下面横线之间的内容。

---

### **$10$ 进制转 $k$ 进制的方法**

您也可以参考[这里](https://oi-wiki.org/math/base)的详细介绍，可能会更加准确。

我们不妨设这个需要进行进制转换的整数为 $x$。

将 $x$ 反复除以 $k$，同时从上至下记录每一次除后的余数（若余数 $≥10$ 则需要转换成字母），直到 $x$ 变为 $0$ 即可。这时候，我们只需把列出的余数**从下到上**排成一行，就得出了 $k$ 进制下的 $x$ 了。

这里是一个将 $165$ 转换为 $16$ 进制的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/g33irq9q.png)

C++ 也是同理，我们可以使用 ``string`` 来存储（因为**可以使用 + 运算**），每次运算的时候将余数加到结果的最前面即可。（**别忘记了本题需要加上前缀符 ``0x``**）

这里给出一个十进制转十六进制的代码：（返回 ``string`` 类型）

```cpp
char tohex[21]="0123456789ABCDEF";
string to16(type k){
    string res;
    while(k>0){
        res=tohex[k%16]+res;
        k/=16;
    }
    res="0x"+res;
    if(res=="0x") return "0x0"; //特判：如果为“0x”则说明k=0，需改为“0x0”
    return res;
}
```

---

这一题我们可以使用读入到 ``string`` 变量中，定义整形变量 $n$，同时在定义一个变量保存 $n$ 的长度 $len$，然后循环每一个字符，遇到数字就加到 $n$ 的后面，如果该字符不是数字但前一个是数字的话，将 $n$ 转为十六进制后比较两者的长度，输出长度较短的数字（题目已说明，同样长的情况下输出十六进制数）并输出这个非数字的字符，如果这个字符的前一个也不是数字，直接输出该字符。

看到这里，想必写代码就很简单了~~才怪~~。

## **“典型”的错误示例：**

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,hexn;
long long n;
int len;
char tohex[21]="0123456789ABCDEF";
string to16(long long k){
    string res;
    while(k>0){
        res=tohex[k%16]+res;
        k/=16;
    }
    res="0x"+res;
    if(res=="0x") return "0x0";
    return res;
}
int main(){
    cin>>s;
    if(s.size()==2){ //如果长度为2则一定是空括号，直接输出空括号即可
        cout<<s;
        return 0;
    }
    for(int i=0;i<s.size();i++){
        if(isdigit(s[i]))
            n=n*10+s[i]-'0',++len;
        else{
            if(len==0){
                cout<<s[i];
                continue;
            }
            hexn=to16(n);
            if(hexn.size()<=len) cout<<hexn;
            else cout<<n;
            cout<<s[i];
            n=0;
            len=0;
        }
    }
}
```

---

很简单吗？不好意思，如果您这样写，您就~~喜提~~ ~~WA~~ **只能得到 $60pts$ 的分数了**。

想想看，题目说 $0≤a_{i}<2^{64}$，而 ``long long`` **只能存储到 $2^{63}-1$**。~~什么题目啊我要用 ``int128`` 了~~ 冷静，还没必要动用 ``int128``，这时候 ``unsigned long long`` 就可以解决这个问题了。

# **AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull; //执行后ull便可以当作unsigned long long使用了，非常方便
string s,hexn;
ull n;
int len;
char tohex[21]="0123456789ABCDEF";
string to16(ull k){
    string res;
    while(k>0){
        res=tohex[k%16]+res;
        k/=16;
    }
    res="0x"+res;
    if(res=="0x") return "0x0";
    return res;
}
int main(){
    cin>>s;
    if(s.size()==2){ //如果长度为2则一定是空括号，直接输出空括号即可
        cout<<s;
        return 0;
    }
    for(int i=0;i<s.size();i++){
        if(isdigit(s[i]))
            n=n*10+s[i]-'0',++len;
        else{
            if(len==0){
                cout<<s[i];
                continue;
            }
            hexn=to16(n);
            if(hexn.size()<=len) cout<<hexn;
            else cout<<n;
            cout<<s[i];
            n=0;
            len=0;
        }
    }
}
```

---

### 结束语

这道题目虽然标签难度是入门，但我认为实际难度应该是普及-，要比其它入门题目难度要高一些，也比较坑，所以如果没有做对请不要太灰心。

### Bye-bye!

---

## 作者：happybob (赞：1)

签到题，先将字符串中的每个数字分离，然后转成 $16$ 进制对比即可。但是我 $80$ 分了很多次，因为要特判 $0$。

数据比较大，最好开 `__int128_t`。

代码：

```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define int __uint128_t

vector<int> vec;
string ss;
string s;

string change(int x)
{
	if (x == 0) return "0x0";
	string k = "";
	while (x)
	{
		int m = x % 16;
		x /= 16;
		if (m <= 9) k += m + '0';
		else
		{
			k += (char)('A' + (m - 10));
		}
	}
	reverse(k.begin(), k.end());
	string l = "0x" + k;
	return l;
}

string __128tostring(int x)
{
	if (x == 0) return "0";
	string p = "";
	while (x)
	{
		p += x % 10 + '0';
		x /= 10;
	}
	reverse(p.begin(), p.end());
	return p;
}

signed main()
{
	cin >> s;
	int pre = -1, l = s.size() - 1;
	for (int i = 0; i <= l; i++)
	{
		if (isdigit(s[i]))
		{
			if (pre == -1) pre = 0;
			pre = pre * 10 + (s[i] - '0');
		}
		else
		{
			if (s[i] == '{' || pre == -1) continue;
			vec.push_back(pre);
			pre = -1;
		}
	}
	for (int i = 0; i < vec.size(); i++)
	{
		string m = change(vec[i]);
		string q = __128tostring(vec[i]);
		if (m.size() <= q.size()) ss += m;
		else ss += q;
		ss += ",";
	}
	printf("{");
	string ans = ss;
	if (ans.size()) ans.pop_back();
	cout << ans << "}\n";
	return 0;
}
```


---

## 作者：Arctic_1010 (赞：1)

来一发不用 `sprintf` 的题解。

### 题目简述

给出一个长度为 $n$ 的十进制表 $a$，对于每一个数，如果把数字用十六进制表示有时比用十进制表示更短，就将其转为十六进制并输出，否则按原样输出。

$0\leq n\leq 10^3$，$0\leq a_i< 2^{64}$。

### 思路

既然不用 `sprintf`，那我们就可以模拟十进制转十六进制的过程。

因为表不是纯数字，所以我们把它当做字符串读入，每次循环取出每个元素。

然后比较两个数的长度大小即可。

### 一些坑点与边界

1. 每个数的范围小于 $2^{64}$，会爆 `long long` ，在暴力模拟进制转换的时候需要预处理 $16$ 的幂，我们发现 $16^{16}=2^{64}$，所以只需预处理到 $16^{15}$ 即可（因为第 $16$ 位用不到），所以不需要 `__int128`。
2. 进制转换时字符串初值不要忘记设为 `0x` 方便后续操作。
3. 注意对于进制转换的前导零处理。
4. 注意对于其他字符（`,`、`{` 和 `}`）的处理。
5. 如果选择用暴力拆位判断一个数字的长度，不要忘记特判 $0$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long 
using namespace std;
string s;
ull Pow[16];
int getlen(ull x)//暴力拆位判断数字长度
{
	ll ans=0;
	if(x==0) return 1;//特判：0的长度显然是1
	while(x) x/=10,ans++;
	return ans;
}
char trans(int x)//对于单个数字的转换
{
	if(x<=9 && x>=0) return x+'0';
	else return x-10+'A';
}
string DectoHex(ull x)//对于整体的转换
{
	string ans="0x";//注意初值
	bool flag=false;//前导零标记
	for(int i=15;i>=0;i--)//转换每一位
	{
		int nowdigit=0;
		if(Pow[i]<=x)
		{
			flag=true;
			while(Pow[i]<=x) x-=Pow[i],nowdigit++;
		}
		if(flag) ans+=trans(nowdigit);
	}
	return ans;
}
signed main()
{
	Pow[0]=1;
	for(int i=1;i<=15;i++) Pow[i]=Pow[i-1]*16;//预处理16的幂
	cin>>s;
	cout<<'{';
	for(int i=1;i<s.length()-1;i++)//只处理中间数字部分
	{
		ull x=0;
		for(int j=i;j<s.length()-1 && s[j]!=',';i++,j++)//取出原表中每个元素
			x=(x*10)+s[j]-'0';
		
		string hex=DectoHex(x);//进制转换
		if(hex.length()<=getlen(x)) cout<<hex;//比较大小并输出
		else cout<<x;
		if(i!=s.length()-1) cout<<',';//边界处理
	}	
	cout<<'}';
    return 0;
}

```

### Bonus

在场上的时候写 `sprintf` 寄了~~于是写成了大模拟~~，赛后才知道竟然有 `%llx` 这个东西。

如果不用这个东西的话也可以是一道不错的模拟题。



---

## 作者：Firstly (赞：1)

## 题意分析
这道题是要对比一个数在十六进制下和在十进制下的长度，如果十六进制的长度小于等于（注意：等于也算，不算 20 分！！）十进制的情况下，输出十六进制下的数，否则输出十进制下的数。

## 解题思路


------------
我们可以读到一个数，就将这个数直接转换为十六进制，使用栈来存储这个数在十六进制下的结构。然后求出原本这个数的位数，并且将栈内元素个数与之相比，如果后者小，则输出原数，否则输出栈内存放的元素。

如果有不熟悉进制转换原理的，推荐先做这道题：[P1143](https://www.luogu.com.cn/problem/P1143)

## **Code:**
```cpp
#include<cstdio>
#include<stack>
#include<cstring>
#include<iostream>
using namespace std;
string s,str;
unsigned long long num;
stack<int>st;
bool check(){
	unsigned long long a=num;//看数据范围，int肯定会爆，只能用 unsigned long long
	while(a!=0){//进制转换核心代码
		if(a%16<=9)st.push((a%16)+48);
		else st.push((a%16)+55);
		a/=16;
	}int siz=st.size();//获取栈内元素个数
	siz+=2;//因为十六进制有前缀，所以长度要 +2
	a=num;
	int len=0;
	while(a!=0){//获取原来数的位数
		len++;
		a/=10;
	}
	while(!st.empty())str+=st.top(),st.pop();//将栈内元素存到字符串里。
	if(siz<=len)return true;//比较
	else return false;
}
int main(){
    cin>>s;
    if(s=="{}"){cout<<s;return 0;}//特判，不然我们的程序会输出 {0}
    int len=s.size();
    cout<<'{';
    for(int i=0;i<len;i++){
        if(s[i]=='{')continue;
        if(s[i]==','||s[i]=='}'){//当检测到一个数结束时
            bool flag=check();
            if(flag){
            	cout<<"0x"<<str;//注意有前缀
            }
            else cout<<num;
            num=0;
            str="";
            cout<<s[i];
        }else num=num*10+s[i]-48;//否则存储这个数
    }return 0;
}
```


---

## 作者：安舒阳 (赞：0)

这道题的整体思路是将数据以字符串输入，再将所有数从字符串汇总分离出来，再将这些数一次转为十六进制字符串类型，与证书类型比较最终得出答案。

整体思路并不难，但是麻烦于有很多的小细节需要注意，所有的细节我都标注在代码里了。

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long back[10005];
unsigned long long len[10005];//back是下面fen函数的返回值，len是back中每个数字的长度，因为函数返回数组比较麻烦，至于为什么要用unsigned long long看main函数后面的注释 
char da[25]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};//代表16进制下每种情况对应的字符 
int fen(string data){//将每个数字从字符串中分开，输入string，返回back和len数组的长度 
	if(data.size()<=2){
		return 0;
	}//这里进行特判，如果只有两字符（"{"和"}"）就直接返回0（没有数字） 
	
	unsigned long long ttmp=0,cnt=1;//cnt的位数和a[i]最大位数一致，所以也需要unsigned long long
	int now=data.size()-2,cnt1=0,cnt2=0;
	//ttmp代表当前数的值；cnt代表当前数添加一位需要乘的数（相当于增加的位数）
	//now是一个类似指针的东西，代表当前位置，从后往前；cnt1代表当前共有多少个数，cnt2代表当前数字有多少位 
	while(now>=0){
		if(data[now]==','||data[now]=='{'){//注意前括号也需要处理，代表一个数的结束，这也是为什么上面要特判2 
			back[cnt1]=ttmp;
			len[cnt1++]=cnt2;
			cnt=1;
			cnt2=0;
			ttmp=0;
		}else{
			ttmp+=(data[now]-'0')*cnt;
			cnt*=10;
			cnt2++;
		}
		now--;
	}
	
	return cnt1;
}
string zhuan(unsigned long long data){//10进制转为16进制
	string back2;
	while(data){
		back2=da[data%16]+back2;
		data/=16;
	}
	back2="0x"+back2;//此处千万别忘了开头的"0x"
	return back2;
}
int main(){//注意long long的最大范围是2^63但是题目中最大为2^64所以需要使用unsigned long long也就是无符号行长整型，能够多出一位
	string a;
	while(cin>>a){//string似乎不能使用scanf和printf输入和输出或者非常麻烦，所以此处使用cin和cout规避此问题 
		int cnt=fen(a);
		cout<<"{";
		for(int i=cnt-1;i>=0;i--){
			string cheng=zhuan(back[i]);
			if(cheng.size()<=len[i]){
				cout<<cheng;
			}else{
				cout<<back[i];
			}
			if(i!=0){
				cout<<",";
			}
		}
		cout<<"}\n";
	} 
	return 0;
} 
```


---

## 作者：lsj2009 (赞：0)

## 题目大意
<https://www.luogu.com.cn/problem/P8115>。
## 思路
这题一看就是个模拟，我们可以考虑使用****秦九韶算法****在读入字符时计算每一个数字 $x$ 的十进制，然后遇见非数字字符就清空 $x$，再考虑需要输出十进制还是十六进制。

## code:
```cpp
#include<bits/stdc++.h>
#define int __int128 //十年 OI 一场空，不开 __int128 见祖宗
using namespace std;
char f(int x) { //看看 x 在十六进制中代表什么
	if(x<10)
    	return x+'0';
    else
    	return 'A'+x-10;
}
string Solve(int x) {
    string dec="",hex="";
    int t=x;
    do //十进制
    	dec+=t%10+'0';
    while(t/=10);
    reverse(dec.begin(),dec.end()); //需要翻转string Solve(int x) {
    do //十六进制
    	hex+=f(x%16);
    while(x/=16);
	reverse(hex.begin(),hex.end()); //需要翻转
    hex="0x"+hex; //加前缀 "0x"
    return hex.size()<=dec.size()? hex:dec; //十六进制小于等于十进制就选择十六进制
}
signed main() {
    char c=getchar(),l;
    int x=0;
    while(true) {
    	if(isdigit(c)) //秦九韶算法，如果为数字，就塞在 x 的末尾继续计算
        	x=x*10+c-'0';
        else {
        	if(c=='{') // '{' 开头输出
            	putchar(c);
        	else if(c==',') //为 ',' 就清空 x 并输出 x 和 ','
            	cout<<Solve(x),putchar(c),x=0;
            else {
                if(l!='{') //注意空数组情况
            	    cout<<Solve(x); 
                putchar(c); break; // '}' 退出
            }
        }
        l=c;
        c=getchar(); //继续读入
    }
	return 1;
}
```
除此之外，我们还有一种更~~装逼~~优秀的解法。

我们发现输入格式比较固定，基本上就是：

若干字符+一个整数+若干字符+一个整数+……+一个整数+若干字符。

其实，****我们可以忽略字符，只读数字****。看看快读模板：
```cpp
void read(int &x) {
	x=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) { x=(x<<3)+(x<<1)+(c&15); c=getchar(); }
	return;
}
```
思考一下，第一个 ``while`` 的作用是什么呢？是的，就是****过滤非数字字符****！

我们可以设计这么一个算法：

1. 输出 ``{``；
2. 读入 $x$；
3. 计算使用十进制还是十六进制，并输出对应进制的 $x$;
4. 重复 $2$、$3$ 两步，直至读入 ``}``;
5. 输出 ``}``。

当然，细节还需管控，如逗号的输出、空数组的处理等等。

## code:
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
int read(int &x) {
	int flag=0; x=0;
	char c=getchar();
	while(!isdigit(c)) { flag|=c=='}'; c=getchar(); if(flag) return -1; }
	while(isdigit(c)) { x=(x<<3)+(x<<1)+(c&15); c=getchar(); flag|=c=='}'; }
	return !flag;
}
char f(int x) {
	if(x<10)
		return x+'0';
	else
		return 'A'+x-10;
}
string Solve(int x) {
    string a="",b="";
	int t=x;
	do a+=t%10+'0'; while(t/=10);
	do b+=f(x%16); while(x/=16);
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end()); b="0x"+b;
	return b.size()<=a.size()? b:a;
}
signed main() {
	putchar('{');
	int x=-1,flag=0,ed=1;
	while(ed) {
	    ed=read(x);
	    if(ed==-1)
	        break;
		if(!flag) flag=1; else putchar(',');
		cout<<Solve(x);
	}
	putchar('}');
	return 0;
}
```

---

## 作者：CpppRCG (赞：0)

# 题目大意：

输入一个答案表，由大括号，十进制数字和逗号组成。改写表内的每个数字，若该整数使用十六进制表示所占字符数小于或等于十进制表示，则将该数改写为十六进制，否则不该写。最后输出改写后的答案表。

# 思路：

给大家介绍一个比较简单的思路：

先读入一个字符串；

特判如果输入了一对大括号，那么直接原模原样输出；

然后遍历整个字符串，把答案表中的每个数存放到数组中；

接着先输出左大括号，然后遍历数组，如果当前的数转换成十六进制后长度增加，那么原封不动输出；

否则，输出转换后的数。

最后输出右大括号，程序结束。

至于如何转换成十六进制，写一个函数就可以了。

# 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[1015];
string DecInt(unsigned long long num)
{
	string str;
	unsigned long long Temp=num/16;
	int left=num%16;
	if(Temp>0)
		str+=DecInt(Temp);
	if(left<10)
		str+=(left+'0');
	else
		str+=('A'+left-10);
	return str;
}
string DecStr(string str)
{
	unsigned long long Dec=0;
	for (int i=0;i<str.size();++i)
		Dec=Dec*10+str[i]-'0';
	return DecInt(Dec);
}
string change(string s)
{
	string ans;
	ans+="0x";
	ans+=DecStr(s);
	return ans;
}
int main()
{
	string n,st;
	cin>>n;
	if(n.size()==2) 
	{
		cout<<"{}";
		return 0;
	}
	int j=0;
	for(int i=1;i<n.size()-1;i++)
	{
		if(n[i]==',') j++;
		else a[j]+=n[i];
	}
	cout<<"{";
	for(int i=0;i<j+1;i++)
	{
		if(change(a[i]).size()>a[i].size())
		{
			cout<<a[i];
		} 
		else
		{
			cout<<change(a[i]);
		}
		if(i!=j) cout<<",";
	}
	cout<<"}";
	return 0;
}
```
完美结束！

---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8115)

# 题目大意

给出一些数，让你看看这些数的十进制形式和加上了 0x 的十六进制形式哪个短，输出短的一个。

# 思路

就是模拟，将输入的数转成 16 进制，加上 0x，判断长度，但是此题坑点还是比较多的，尤其需要注意此题要使用 unsigned long long。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string mp1[16]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};//16进制对应2进制表，因为2^4=16，所以可以用这个表来转换
char mp2[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
unsigned long long to_int(string s)//字符串转数字，因为是string，所以不能使用stoi
{
	unsigned long long res=0;
	for(long long i=s.length()-1,j=1;i>=0;i--,j*=10)//j为位权
	{
		int p=s[i]-48;
		res+=p*j;
	}
	return res;
}
string to_bin(unsigned long long d)//将十进制转成二进制
{
	string res="";
	while(d!=0)
	{
		res+=char(d%2+48);
		d/=2;
	}
	reverse(res.begin(),res.end());//反转
	return res;
}
string to_hex(string b)//二进制转16进制
{
	string bi;
	if(b.length()%4==1)bi="000"+b;//在前面补前导零
	else if(b.length()%4==2)bi="00"+b;
	else if(b.length()%4==3)bi="0"+b;
	else bi=b;
	string res="";
	for(int i=0;i<bi.length();i+=4)
	{
		string f="1";//这里不能直接f+=bi[i]+bi[i+1]+bi[i+2]+bi[i+3]
		f[0]=bi[i];
		string f1="1";
		f1[0]=bi[i+1];
		string f2="1";
		f2[0]=bi[i+2];
		string f3="1";
		f3[0]=bi[i+3];
		f+=f1+f2+f3;
		for(int j=0;j<16;j++)if(mp1[j]==f)res+=mp2[j];
	}
	return res;
}
int main()
{
	string s;
	cin>>s;
	string tmp="";
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='{')cout<<"{";//括号
		else if(isdigit(s[i]))tmp+=s[i];//如果是数字就加上
		else if(s[i]==','||s[i]=='}')//数字结束
		{
			unsigned long long dec=to_int(tmp);
			string bin=to_bin(dec);
			string hex=to_hex(bin);
			string res="0x"+hex;
			if(res.length()>tmp.length())res=tmp;//不要写成>=，要读题
			cout<<res<<s[i];
			tmp="";//记得清空
		}
	} 
	return 0;
}
```


---

## 作者：lym12321 (赞：0)

# P8115 Table

## 题意

以一种特别的输入方式输入若干个数：

- 对于每一个数，我们需要比较其十进制和十六进制所占字符数。  

- 若十六进制表示所占字符数小于等于十进制表示，则改写为十六进制。  
 
  否则保持十进制不变。
  
## 输入格式

> “输入一行一个字符串，字符串中仅包含大括号、逗号和数字，不包含空格和其他字符等。具体格式可以参考 C++ 语言的数组定义格式。”

就像这样：

$$
\texttt{\{val1,val2,val3,...,valn\}}
$$

## 输出格式

应与输入格式类似，仅对其中十进制整数进行替换，替换规则如上文。  

需要注意的是，每个十六进制数字都包含前缀 `0x`。

## 题目分析

~~众所周知~~，我们可以通过 [短除法](https://baike.baidu.com/item/%E7%9F%AD%E9%99%A4%E6%B3%95/3640958?fr=aladdin)，将十进制转化为二进制。

而对于本题来说，我们也可以使用此方法。  

所以，对于十进制数 $n$，我们只需要使用短除法，不断除以 $16$。

将每一步所得的余数，转化为相应的字符，倒序排列即可。

若需要更详细的介绍，请参考 [百度百科](https://baike.baidu.com/item/%E5%8D%81%E5%85%AD%E8%BF%9B%E5%88%B6/4162457?fr=aladdin)。

我们可以写出转换函数如下：

```cpp
char m[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
string Hex(unsigned long long nn){
    string res = "";
    while(nn){
        int tmp = nn % 16;
        nn /= 16;
        res = m[tmp] + res;
    }
    // 注意题目要求，记得加上 '0x'
    res = "0x" + res;
    return res;
}
```
解决了这个问题，我们只要注意一下细节，就可以 `AC` 啦！  

## Code

```cpp
#include<iostream>
#include<cstring>

using namespace std;

string s;
char m[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
unsigned long len;                  // len: 用于记录输入数字的长度
unsigned long long n;               // n: 用于记录输入数字

string Hex(unsigned long long nn){
    // 此函数用于将数字转换为十六进制下的字符串
    string res = "";
    while(nn){
        // tmp 即为余数
        int tmp = nn % 16;
        nn /= 16;
        // 将对应字符加到字符串内即可
        res = m[tmp] + res;
    }
    // 记得加上 '0x'
    res = "0x" + res;
    return res;
}

void Output(){
    // 输出符合题意的字符串或数字
    if(!len) return;                // 当 len == 0 的时候，说明什么都没有输入，我们也不应该输出任何东西
    string hexs = Hex(n);           // 十六进制字符串
    // 按题意比较并输出
    if(hexs.length() <= len) cout << hexs;
    else cout << n;
}

int main(){
    // 祖传加速
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> s;
    for(auto i : s){
        // 这里的 auto 用法是可以在考场上使用的
        // 用来遍历字符串、STL容器的时候甚是方便
        if(i == '{'){
            // 第一个数字开始了！
            cout << "{";
            continue;
        }
        if(i == ','){
            // 呐，这个数字结束了，开始处理吧qwq
            Output();
            cout << ",";
            n = len = 0;            // 记得重置 n 和 len
            continue;
        }
        if(i == '}'){
            // 已经全部结束了诶
            Output();
            cout << "}";
            continue;
        }
        // 读入下一个数字
        len++;
        n = n * 10 + i - '0';
    }

    return 0;
}
```

## 注意事项  

十 年 O I 一 场 空，不 开 `unsigned long long` 见 祖 宗。

---

## 作者：一只大龙猫 (赞：0)

我们可以考虑把整个字符串一次输入，遍历整个字符串，挨个字符处理。要输出时，比较一下使用十进制和十六进制表示所占的字符数，然后输出。

输出可以使用`iomanip`里面的`hex`和`dec`来切换十六进制和十进制的输出，使用`hex`和`uppercase`配合起来可以实现输出某数的大写十六进制（详见[这篇](https://www.cnblogs.com/xenny/p/9381468.html)文章）。这会使我们的代码简洁不少。

另外，因为数据保证每个数都大于等于 $0$ 且小于 $2^{64}$，恰好在 C++ 中`unsigned long long`的范围内，所以我们使用`unsigned long long`是不会出现溢出的情况的。

代码如下：

```cpp
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
string str;
unsigned long long now;
int len;//见下文
int hex_count(unsigned long long x){//使用十六进制表示所占的字符数
	if(x==0)return 3;//见下文
	int cnt=0;
	while(x!=0){
		cnt++;
		x/=16;
	}
	return cnt+2;
}
int dec_count(unsigned long long x){//使用十进制表示所占的字符数
	if(x==0)return 1;
	int cnt=0;
	while(x!=0){
		cnt++;
		x/=10;
	}
	return cnt;
}
void print(unsigned long long x){//输出
	if(hex_count(x)<=dec_count(x)){
		cout<<"0x"<<hex<<uppercase<<x;
	}else{
		cout<<dec<<x;
	}
	return;
}
int main(){
	cin>>str;
	len=str.size();
	if(len==2){//如果整个字符串的长度为2，那么肯定只有一对大括号，可以特判
		cout<<"{}";
		return 0;
	}
	cout<<"{";
	for(int i=1;i<len-1;i++){//开头结尾的大括号可以略去
		if(str[i]==','){
			print(now);
			cout<<",";
			now=0;
		}else{
			now=now*10+(str[i]-'0');//见下文
		}
	}
	print(now);
	cout<<"}";
	return 0;
}
```

注意事项：

1. **初始化！初始化！初始化！**`hex_count`函数和`dec_count`函数中的`cnt`要初始化为`0`；每次输出后（除最后一次）`now`的值都要重新赋值为`0`。

2. 在`main`函数的循环内**不会输出最后一个数**，不要忘记输出。

3. 标点符号的输出，`main`函数的循环内的输出是**需要输出逗号的**，循环外的则**不用**。同时不要忘记**开头结尾的一对大括号**。

**Q&A**

Q1：用`int`去存字符串长度会不会溢出？

A1：不会。因为数据保证每个数都大于等于 $0$ 且小于 $2^{64}$，也就是每个数十进制下最多 $20$ 位。而数据保证最多有 $1000$ 个整数，也就是说字符串的长度最多会比 $20 \times 1000 = 20000$ 略大一点（因为有标点符号），用`int`去存是绰绰有余的。

Q2：为什么在`hex_count`函数和`dec_count`函数中，要特判`x==0`的情况？我把这两句删掉了，也没问题呀？

A2：如果不特判，那么两个函数的返回值会分别为 $2$ 和 $0$（因为中间的循环被跳过了）。但实际上，$0$ 用十六进制表示为 $\texttt{0x0} $，十进制为 $0$，正确的返回值应为 $3$ 和 $1$。虽然不会影响程序运行的结果，但这是一种**很不好的习惯**，相当于为程序埋下一个“定时炸弹”，所以**强烈建议特判这种情况**。

Q3：为什么`now=now*10+(str[i]-'0');`一句可以更新 `now` 的值？

A3：

`str[i]-'0'`能将这一位字符转换成数字（如`'0'`转为 $0$，`'1'`转为 $1$）。

`now*10`相当于在`now`所储存的数后面后面加上一个 $0$（如果是 $0$ 则不变），然后再加上目前遍历到的字符转为数字的结果，这样就能实现更新的操作了。

如果不理解，可以自己手动模拟一下，或是看看[这个](https://www.luogu.com.cn/discuss/407163)帖子，各位大佬都给出了很好的答案。

---

## 作者：Nygglatho (赞：0)

首先，读入肯定需要字符串读入的，而转换为数组时可以考虑把字符串转换为数组，一旦碰到逗号，那么用数组中新的元素添加字符串中的数字，否则在末尾加入字符串当前这一位的数字即乘 $10$ 再加上字符串当前一位的数字，即：
```cpp
szt = 1;
for (int i = 1; i < s.size() - 1; ++i) {
	if (s[i] == ',') ++szt;//元素个数加一，此时最后一个元素未使用过
	else t[szt] = t[szt] * 10ll - 48ll + s[i];//最后一个元素
}
```
接下来，考虑判断位数，这里我用的是一种暴力的方法，判断十进制时这个数只要不为零就除以十，除的次数即为位数，十六进制也一样，只不过把十改成了十六，由于十六进制最前面要加个 `0x`，所以最后位数需要加上 $2$。
```cpp
//判断十进制位数
int ws(unsigned long long x) {
    int s = 0;
    while(x > 0) {
        ++s;
        x /= 10;
    }
    return s;
}
//判断十六进制位数
int sljzws(unsigned long long x) {
    int s = 0;
    while(x > 0) {
        ++s;
        x /= 16;
    }
    return s + 2;
}
```
最后，如果十进制位数大于十六进制位数，那么就直接输出，否则，先输出 `0x`，再转换为十六进制输出，但由于我们 $szt$（$t$ 数组元素个数）初值为 $1$，且最后输出时会输出 $t_{szt}$ 的十进制或是十六进制，所以我们需要特判一下。

[完整代码](https://paste.ubuntu.com/p/WTXV9TPJbH/)

---

