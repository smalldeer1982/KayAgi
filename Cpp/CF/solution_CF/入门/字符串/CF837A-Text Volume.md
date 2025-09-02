# Text Volume

## 题目描述

You are given a text of single-space separated words, consisting of small and capital Latin letters.

Volume of the word is number of capital letters in the word. Volume of the text is maximum volume of all words in the text.

Calculate the volume of the given text.

## 说明/提示

In the first example there is only one word, there are 5 capital letters in it.

In the second example all of the words contain 0 capital letters.

## 样例 #1

### 输入

```
7
NonZERO
```

### 输出

```
5
```

## 样例 #2

### 输入

```
24
this is zero answer text
```

### 输出

```
0
```

## 样例 #3

### 输入

```
24
Harbour Space University
```

### 输出

```
1
```

# 题解

## 作者：Viston (赞：3)

This Explanation is written by viston. (If you do many red subjects ,you'll sometimes see me).

好的让我们开始讲中文！   
这道题嘛，就是每次输入一个字符串，然后把已经用的长度更新，如果超过了就退出，每输入一个字符串更新一下$ans$，最后输出即可。
```
#include<bits/stdc++.h>
using namespace std;
string s;
int a,b,tot,i,ans=-2147483633;
int main()
{
	tot=0;
	cin>>a;
	while(b<a)//判断条件
	{
		tot=0;
		cin>>s;
		b+=s.size()+1;
		for(i=0;i<s.size();i++)
		if(s[i]>='A'&&s[i]<='Z')//是否为大写字母
			tot++;
		ans=max(ans,tot);//更新ans
	}
	cout<<ans;
	return 0;
}
```

See you Next red subject!

---

## 作者：K2sen (赞：1)

### CF837A Text Volume
[传送门](https://www.luogu.com.cn/problem/CF837A)
发现我不读题，_Destiny 菜死了
### 题目大意 
给你字符串的长度，每个单词之间用空格隔开，

然后让你求一个单词内最多有多少个大写字母

### 思路
我们可以开两个计数器

其中一个用来记录每一个单词的大写字母的数目，另一个记全部的

一读到空格就更新一次

**注意**:读入要用$getchar$

### code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 100010
#define M 210

using namespace std;
int n, ans, ss; char sy;

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

int main() {
	int n = read();
	for (int i = 1; i <= n; i++) {
		sy = getchar();
		if (sy >= 'A' && sy <= 'Z') ss++;
		if (sy == ' ') {
			ans = max(ans, ss);
			ss = 0;
		}
	}
	cout << max(ans, ss);
}
```

---

## 作者：Thomas_Cat (赞：1)

这题的简要意思概括：

- 输入一个字符串，包含空格。
- 在所有的用空格间隔的单词中，找到有做多大写字母的那一个单词
- 输出大写字符个数

没啥好说的，直接上代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
    char ch[100001];//定义字符串，注意开大一点，因为数据有点毒瘤
    int n,sum=0,ans=INT_MIN;//这里注意吧ANS设为最小值，要不然可能会出锅
    cin>>n>>ch;//输入
    for(int i=0;i<n;i++){//循环枚举判断
        if(ch[i]==' '){//如果是一个空格，表示单词结束
            ans=max(ans,sum);//比较大小，取最大值
            sum=0;//当前sum清零
        }
        if(ch[i]>='A'&&ch[i]<='Z') sum++; //其他情况如果是大写字母就sum++   
    }
    cout<<max(ans,sum);//输出最大值
    return 0;    
}
```

---

## 作者：Laser_Crystal (赞：1)

### 来一发字符串的~
~~（冒险用gets）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	char s[1000];
	gets(s);//读取换行
	gets(s);
	int ans=0,maxn=0;//看到一堆大佬ans=-2147483648，其实答案不会为负数
	for(int i=0;i<n;i++)
	if(s[i]>='A'&&s[i]<='Z') 
    		maxn++;//如果是大写字符就加
	else if(s[i]==' ')//碰上空格就为新单词
	{
		ans=max(maxn,ans);//取最大值
		maxn=0;//清零
	}
	ans=max(ans,maxn);//还要取一次最大值，不然在只有一个单词下或最后一个单词为最大值的情况下会炸
	cout<<ans;
	return 0;
}
```
94这么H2O啦，拜拜~

---

## 作者：tzl_Dedicatus545 (赞：0)

## 1.思路

1. 先求出每个单词里大写的数量，放在 $cap_i$ 里。
1. 在求出 $cap$ 数组里的最大值，输出。

## 2.知识点

1. 在头文件 <cctype> 中有一个函数 $isupper$ ，如果字符是大写，该函数返回1，否则返回0。
1. 用以下代码可以不间断的输入：
  ```cpp
while(cin>>t)
{
	//do something...
}
```

## 3.实现
  
**先看找单词里的大写字母：**
  ```cpp
int cap[201]={};

void findcap(string t,int no)
{
	for(int i=0;i<t.size();i++)
	{
		if(isupper(t[i]))
			cap[no]++;
	}
}

```

**找最大：**
                                
 ```cpp
int getmax(int no)
{
	int max=-1;
	
	for(int i=0;i<=no;i++)
	{
		if(max<cap[i])
			max=cap[i];
	}
	return max;
}

```

**主函数：**
                       
```cpp
int main()
{
	string t;
	int no=0;
	
	int n;
	
	cin>>n;
	
	while(cin>>t)
	{
		//no++;
		findcap(t,no);
		no++;
	}
	
	cout<<getmax(no);
	
	return 0;
}
```


---

## 作者：FR_qwq (赞：0)

这题，窝看了一下题，没仔细看，就认为求一个字符串中的大写字母个数，这是错误代码：
```pascal
var i,n,sum:longint;
s:string;//这里珂以不用ansistring
begin
readln(n);
readln(s);//读入
for i:=1 to n do if(s[i] in['A'..'Z'])then inc(sum);//判断是否是大写字母
writeln(sum);//输出答案
end.
```
结果，泥第三个样例都没过，然后重新看了一下题，才知道它是要求最大。

之后，改成了这样：
```pascal
var i,n,sum,max:longint;
s:string;
begin
readln(n);
readln(s);//读入
for i:=1 to n do
  begin
  if(s[i]=' ')then begin if sum>max then max:=sum;sum:=0;end//如果它是空格，说明一个单词结束，求最大，清零。
  else if(s[i]in['A'..'Z'])then inc(sum);//否则判断它是不是大写字母，如果是，累加器加一
  end;
writeln(max);//输出最大值
end.
```

这次错的更惨，样例1就错了，泥想想看，如果他给你的只有一个单词咋办啊，对不对？所以我们要在最后再加一个特判，判断是否最后一个单词是最大值。

$AC$ $CODE$：
```pascal
var i,n,sum,max:longint;
s:string;//定义
begin
readln(n);
readln(s);//输入
for i:=1 to n do
  begin
  if(s[i]=' ')then begin if sum>max then max:=sum;sum:=0;end//判断
  else if(s[i]in['A'..'Z'])then inc(sum);//累加
  end;
if sum>max then max:=sum;//再次判断
writeln(max);//输出
end.
```

此时，窝又想到了一个神奇的做法：在那个字符串后面直接加上一个空格，使最后一个单词珂以直接在循环里判断，还缩短了代码的长度，代码如下：
```pascal
var i,n,sum,max:longint;
s:string;//定义
begin
readln(n);
readln(s);//输入
s:=s+' ';//本代码精华：在那个字符串后直接加一个空格
for i:=1 to n+1 do//注意：现在字符串长度不是n了，是n+1，或者用length(s)
  begin
  if(s[i]=' ')then begin if sum>max then max:=sum;sum:=0;end//判断
  else if(s[i]in['A'..'Z'])then inc(sum);//累加
  end;
writeln(max);//输出
end.
```
$THE$ $END$.

---

## 作者：Franka (赞：0)

### **题目**
求在一个字符串$n$中，**大写字母**的个数。
### **思路**
先介绍一个$Pascal$的函数：$in$。

框架如下：

$if$ $n$ $in$ $['A'..'Z']$ $then$

其中n是一个变量，当然，你也可以把n换成其他的变量。

$in$ $['A'..'Z']$的意思就是看看$n$有没有在$A$~$Z$的范围内，如果有，就返回$TRUE$,否则返回$FALSE$。

其实$if$ $n$ $in$ $['A'..'Z']$ $then$就相当于$if$ $(n>='A')$ $and$ $(n<='Z')$ $then$。

#### 因此，判断一个字符是否是大写就可以用如下语句：

$if$ $n[i]$ $in$ $['A'..'Z']$ $then$
### **代码**~~(不要在意我的码风)~~
```pascal
var
 n:string;//定义n字符串
 s,i,max:longint;//定义s和i
begin
 readln(n);//因为这里不需要用到长度，所以直接覆盖掉
 readln(n);//读入n
 for i:=1 to length(n) do//最大平台长度
  if n[i] in ['A'..'Z'] then inc(s)//如果是大写，s累加
                        else//否则
                          if n[i]=' ' then//如果是空格，表示另一个单词
                            begin
                             if s>max then max:=s;//找最大值
                             s:=0;//s清零
                            end;
 if s>max then max:=s;//因为这里最后一位没有判过，所以单判最后一个单词
 writeln(max);//输出最大值
end.
```


---

## 作者：Heap_Sort (赞：0)

**为P党发一个题解**

### 题意转化
一个字符串，用空格分成若干子串，求大写字母最多的子串内的大写字母有多少。

由于n<200,所以string就能存下。但是长度超过255，就需要ansistring，否则多余位数就会被抹去！！！

思路：一个一个字符来看，如果是大写字母，就把当前单词内的大写字母数量+1；如果是空格，就把当前单词的大写字母数量与之前最多的比较，取最大值。

### 代码
```pascal
var
  a,b,c,d:integer;
  s:char;
begin
  readln(a);
  for b:=1 to a do
   begin
    read(s);
    if s=' ' then begin if c>d then d:=c;c:=0;end;//更新最大值并归0
    if(ord(s)>=65)and(ord(s)<=90)then inc(c);//是大写字母就+1
   end;
  if c>d then d:=c;//结尾比较不能忘！！否则最后一个单词就比较不到。
  writeln(d);
end.
```


---

## 作者：agicy (赞：0)

# 题意

## 题目描述

给出一个长度为$n$的一个字符串，字符串中包含多个用空格隔开的单词，请问一个单词中最多有多少个大写字母？

## 输入输出格式

### 输入格式

第一行，一个整数$n(1≤n≤200)$，表示字符串的长度。

第二行，一个字符串。

### 输出格式

一个整数，表示一个单词中最多有多少个大写字母。

## 题面源代码

```
## 题目描述

给出一个长度为$n$的一个字符串，字符串中包含多个用空格隔开的单词，请问一个单词中最多有多少个大写字母？

## 输入输出格式

### 输入格式

第一行，一个整数$n(1≤n≤200)$，表示字符串的长度。

第二行，一个字符串。

### 输出格式

一个整数，表示一个单词中最多有多少个大写字母。
```

# 思路

我们可以**直接忽略$n$的存在**，因为单词之间使用空格隔开，我们只要**分别读入每一个单词**并**统计大写字母的数量**即可。

# 代码

代码如下。

```cpp
#include<stdio.h>
#include<string.h>
#define max(a,b)    ( (a) > (b) ? (a) : (b) )//宏定义max()函数

char str[1024];//字符串

int main(void){
	register int i,len,sum,ans=0;//寄存器更快些，记得初始化ans为0
	scanf("%*d");//忽略n的存在，%*d表示读入一个整型数据但不保存在变量中
	while(~scanf("%s",str)){//读入每一个单词
		sum=0,len=strlen(str);
		for(i=0;i<len;i++)
			if('A'<=str[i]&&str[i]<='Z')
				sum++;//统计大写字母的数量
		ans=max(ans,sum);//更新答案
	}
	printf("%d\n",ans);//输出
	return 0;//结束
}
```

## [我的测评记录](https://www.luogu.org/record/show?rid=9538273)

---

## 作者：jinhangjie2006 (赞：0)

pascal的话，字符串是不管空格有没有的，比如（dsa dsa f），这样一个是算一个字符串的，那么就是一检测到一个空格，然后和最大值比较，最后累加值清0。

```cpp
var
  i,n,e,max:longint;
  s:string;
begin
  readln(n);
  read(s);
  for i:=1 to n do
   begin
     if s[i] in ['A'..'Z'] then inc(e);//如果是大写字母就累加
     if s[i]=' ' then begin if e>max then max:=e;e:=0;end;//空格了，求最大值，然后累加值清0.
  end;
  if e>max then max:=e;//注意，我们没把最后一个字符串算进去，因为最后一个字符串后面没有空格，所以再求一次。
  write(max);//输出
  end.
```


---

