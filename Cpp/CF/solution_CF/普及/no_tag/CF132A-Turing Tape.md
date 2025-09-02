# Turing Tape

## 题目描述

INTERCAL is the oldest of esoteric programming languages. One of its many weird features is the method of character-based output, known as Turing Tape method. It converts an array of unsigned 8-bit integers into a sequence of characters to print, using the following method.

The integers of the array are processed one by one, starting from the first. Processing $ i $ -th element of the array is done in three steps:

1\. The 8-bit binary notation of the ASCII-code of the previous printed character is reversed. When the first element of the array is processed, the result of this step is considered to be 0.

2\. The $ i $ -th element of the array is subtracted from the result of the previous step modulo 256.

3\. The binary notation of the result of the previous step is reversed again to produce ASCII-code of the $ i $ -th character to be printed.

You are given the text printed using this method. Restore the array used to produce this text.

## 说明/提示

Let's have a closer look at the beginning of the example. The first character is "H" with ASCII-code $ 72=01001000_{2} $ . Its reverse is $ 00010010_{2}=18 $ , and this number should become the result of the second step of processing. The result of the first step is considered to be 0, so the first element of the array has to be $ (0-18) $ mod $ 256=238 $ , where $ a $ mod $ b $ is the remainder of division of $ a $ by $ b $ .

## 样例 #1

### 输入

```
Hello, World!
```

### 输出

```
238
108
112
0
64
194
48
26
244
168
24
16
162
```

# 题解

## 作者：bj12z_donglinxi (赞：1)

## 分析

本题的难点就在于理解题，其实这就是一道模拟，码中没有任何难点，至于二进制反转……

二进制转换其实就是将一个数 $\bmod$ $2$ 后反转，代码如下：

```cpp
x += first % 2 * temp;
temp /= 2;
first /= 2;
```
另外，题目中给出的 ASCII 码值只到 $100$，所以可以直接将用来存储系数的 temp 值设为 $128$，方便后面的转换。


## 代码

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
//誓死不用万能头
using namespace std;

int last = 0, x = 0;
int first, temp;//first用来存储初始值
string s;

int main() {
	getline(cin, s);//避免空格问题，整行读入
	for (int i = 0 ; i < s.size() ; i++) {
        x = 0;//记得再归零一次（我被卡了几次（可以看我提交记录））
		first = s[i];
		temp = 128;
		for (int j = 1 ; j <= 8 ; j++) {
			x += first % 2 * temp;
			temp /= 2;
			first /= 2;
		}
		printf("%d\n", (last - x + 256) % 256);//记得换行
		last = x;
	}
	return 0;
}
//严禁抄袭题解，共创和谐洛谷
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)


## 分析思路
这道题最主要的其实是思路，思路有了这道题其实就是很简单。

最开始大家的想法应该是把每一个数的 ASCII 码都求出来，再进行翻转模拟出结果对吧？

这么写肯定 AC 是能 AC 的，但是这里的方法可以不用那么难。本蒟蒻在用这个方法 AC 之后点开题解区，发现一楼的 dalao 似乎用了更简便的方法，~~但是本蒟蒻理解不了这么高深的艺术，所以~~ 把他的思路整理解释出来。

因为题目要求把二进制码求出来之后再进行翻转，我们知道 **求一个数的二进制就是把这个数除以二的余数进行反转** ，那么反转之后又要反转不就是代表不用反转吗？

于是，思路进行到这里应该就很清晰了，我们再来看这道题目的数据范围，发现给出的 ASCII 码值最高只到 100，于是 **我们可以把系数设置成 128**，也就是 $2^{7}$，这样我们就可以把每一位的数在求二进制码的时候就转换好了。

很简洁易懂有木有！

**这里有一些题目中的坑需要注意：**
1. 样例中给了我们有空格，于是我们需要整行读入，可以用 `getline(cin,s)` 函数整行读入；
2. 题目中没有说 ~~（也可能是本蒟蒻没有读懂题）~~ 最后的取余怎么取，但是本蒟蒻亲测需要输出 $(last-x+256)\bmod256$ 的值。

于是，这道模拟的水题就被我们用一个极其简单的方式解决了！！！

代码如下（和一楼 dalao 的代码很相似，因为思路基本相同）：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
int last=0,x=0,t,tmp;//last如题，x是反转之后的数，t为一开始的数，tmp为系数 2^n 
int main(){
	getline(cin,s);//样例里面都告诉我们有空格了，所以得用整行读取 
	for(int i=0;i<s.size();i++){
		t=int(s[i]);
		x=0;
		tmp=128;
		for(int j=1;j<=8;j++){
			x+=t%2*tmp;
			tmp/=2;
			t/=2;
		}
		cout<<(last-x+256)%256<<endl;//输出注意换行 
		last=x;
	}
	return 0;
}

```


---

## 作者：小恐 (赞：1)

~~恕我直言，这道题最难得地方就是理解题意~~

~~话说楼下题解代码有点长~~

一个大模拟题，就是题目让你干啥你就干啥。

反转压根不用快速幂（其实是我不会写），因为系数都是$2^n$，只需要存一个变量为128，每次除以2就行。

没听明白？上代码吧：
```cpp
#include<stdio.h>
#include<string.h>
using namespace std;
char a[105];
int main()
{
	fgets(a,104,stdin);//读入字符串的函数，在string.h下，能读空格，自己上网搜 
	int last=0;//记录上一个字符反转后的数，初始为0。 
	for(int i=0;a[i]!='\0'&&a[i]!='\n';++i)
	{
		int t=128;//系数 
		int x=a[i];//直接转换成数 
		int y=0;//记录反转后的数 
		/*反转*/ 
		for(int j=1;j<=8;++j)
		{
			y+=x%2*t;
			t/=2;
			x/=2;
		}
		printf("%d\n",(last-y+256)%256);//输出 
		last=y;//为下一个记录 
	}
	return 0;
}
```
珍爱生命，远离抄袭！

---

## 作者：Leaves_xw (赞：0)

思路：

我们可以循环遍历每一个字符，再取 ASCII 码，记为 $x$，随后进行二进制取反，记为 $last$，最后输出 $(last-x)\bmod 256$。

注意的是，输入该字符需要使用 `getline` 函数读入，因为可能含有空格。

核心代码：

```
for(int i=0;i<=s.szie()-1;++i)
{
    t=int(s[i]),x=0,ans=128;
    for(int j=1;j<=8;++j)//二进制转换
    {
       x+=t%2*ans;
       ans/=2;t/=2;
    }
    cout<<(last-x+256)%256<<endl;//输出公式
    last=x;//别忘了标记
}
```

---

## 作者：ZM____ML (赞：0)

一道普通模拟题，不用太多讲述。

注意一点我们要把二进制码求出来之后再进行反转，而求一个数的二进制就是把这个数除以二的余数进行反转，所以说反转再反转就等于不变。

注意一个坑点：空格也要进行运算（我一开始就把空格排除了），于是我们需要整行读入，可以用```
getline(cin,s)```
函数整行读入。

其他没什么问题了，直接上代码。
```cpp
#include<iostream>
using namespace std;
const int p=256;
string s;
int l;
int main(){
	getline(cin,s);
	for(int i=0;i<s.size();i++){
		int t=s[i],x=0,tmp=p/2;
		for(int j=1;j<=8;j++){
			x+=t%2*tmp;
			tmp/=2;
			t/=2;
		}
		cout<<(l-x+p)%p<<"\n";
		l=x;
	}
	return 0;
}
```


---

## 作者：Firstly (赞：0)

## **题目思路：**

这是一道模拟题。我们可以将数字的 $\texttt{ASCII}$ 码值转换为二进制的字符串，然后将其翻转。注意：在这里需要八位二进制数，所以如果在翻转后二进制的位数没有达到八位，那么需要在后面补 $0$，再将其重新转换为十进制，得到取反后的结果 $\text{x}$。

然后直接输出答案即可。注意：当答案为负数，我们需要将这个值加上 $256$，使其变为一个正数，再对答案取模输出即可。

最后不要忘记将 $\text{last}$ 更新。

## **Code：**

```cpp
#include<iostream>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    string str;
    getline(cin,str);int last=0;
    for(int i=0;i<str.size();i++){
        char ch=str[i];
        int asc=(int)ch;
        stack<char>st;
        while(asc!=0){
            st.push((asc%2)+48);
            asc/=2;
        }string s;
        while(!st.empty()){
            s+=st.top();
            st.pop();
        }
        reverse(s.begin(),s.end());
        while(s.size()<8)s+="0";
        int rate=1,ans=0;
        for(int i=s.size()-1;i>=0;i--){
            ans+=(s[i]-48)*rate;
            rate*=2;
        }if(last<ans)cout<<256+(last-ans)%256<<endl;
        else cout<<(last-ans)%256<<endl;
        last=ans;
    }return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
读入一个字符串 $s$，让你用以下规则将字符串中的所有字符转换成数字：

- 先将这个字符的 $\texttt{ASCII}$ 码的 $8$ 位 $2$ 进制数反转，再将这个数转化为十进制数，记为 $x$。例如 $\texttt{H}$ 的 $\texttt{ASCII}$ 码是 $72=(01001000)_2$，将其反转得 $(00010010)_2=18$。
- 取出上一步的反转结果 $res$（第一步 $res=0$），求出最终的数字 $a=(res-x)\mod256$。例如，$\texttt{H}$ 作为第一个字符出现在字符串中，那么它的最终转换的数字就是 $(0-18)\mod256=238$。

**数据范围：$1\leqslant|s|\leqslant100$，各个字符的 $\texttt{ASCII}$ 码在 $32$ 到 $126$ 之间（包含 $32$ 和 $126$）。**
## Solution
就是一道模拟题目。

首先得出字符的 $\texttt{ASCII}$ 码以后我们把它转换为一个 $8$ 位二进制的数，再反转。这个可以用一个数组来保存。

我们再调出上一次的结果（可以用一个变量保存，初始值为 $0$），然后求出来结果。注意，如果是负数，那么先要把它给加上 $256$，使其变为正数，然后再取模。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

string s;
int pre;

int main() {
	getline(cin, s);	//考虑到可能读入空格，用getline读入字符串
	pre = 0;
	for(int i = 0; i < s.size(); ++i) {
		int x = (int)s[i], num[17] = {0}, newx = 0;
		for(int j = 7; j >= 0; --j)	if(x >= (int)pow(2, j)) num[j] = 1, x -= pow(2, j);
		for(int j = 0; j <= 7; ++j)	newx += num[j] * pow(2, 7 - j);
		printf("%d\n", (pre - newx + 256) % 256);
		pre = newx;
	}
}
```

---

## 作者：WCG2025 (赞：0)

CF~~水题~~

------------

这道题的背景是作者从[INTERCAL](https://baike.baidu.com/item/INTERCAL/4194765?fr=aladdin)
得到的灵感（顺便说一下，CF171E那道题的答案就是这种神奇语言）

这道题的题意是这样的：
给你一串字符串，你先是要求出每一个字符的ASCII值，然后将这个值的八位二进制进行反转（例如：72=01001000 反转过来 就是00010010=18），然后用前一个值减去现在这个值加上256后模256，依次输出

这道题的难点就是在于如何将二进制进行反转，其实我们可以想到，将二进制的每一位&1，如果等于一，就将这一位加上（二进制下），用一个快速幂处理，然后用前一个值减去现在这个值加上256后模256，就是这个字符串的最终值

可能我说的云里雾里的，具体就看代码来领会
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
       if(ch=='-') f=-1;
       ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
       x=x*10+ch-'0';
       ch=getchar();
    }
    return x*f;
}
string a;
int rev[1000];
int len;
int qpow(int a,int b)//直接一个快速幂模板
{
    int res=1;
    while(b)
    {
        if(b&1)
        res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}
int cl(int x)
{
    int res=0;
    for(int i=1;i<=8;i++)
    {
        if(x&1==1)//因为ascii值的二进制最多就8位，枚举8次就行了
        res+=qpow(2,8-i);//如果这一位的值是1，他的位置是2， 
        x>>=1;//那么他反转后的位置就应该是6
    }//例如 0000 0010 处理后就是 0100 0000
    //处理完一位后就右移处理下一位就好了
    return res;
}
int main()
{
    getline(cin,a);//中间是有空格的，用cin算的值不完全
    len=a.length();	
    for(int i=0;i<len;i++)
    {
        int x=a[i];
        int zlp=cl(x);
        rev[i+1]=zlp;//将处理的每一个值存入rev数组
    }
    for(int i=1;i<=len;i++)
    {
        int ans=(rev[i-1]-rev[i]+256)%256;//这一步就是按照题意模拟，特别地，rev[0]==0；
        printf("%d\n",ans);
    }
    return 0;
}
```


---

