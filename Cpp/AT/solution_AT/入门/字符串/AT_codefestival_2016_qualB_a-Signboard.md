# Signboard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_a

CODE FESTIVAL 2016が開催されます。開催にあたって、高橋君はCODE FESTIVAL 2016の看板を作ることにしました。

看板には`CODEFESTIVAL2016`と書きたかったのですが、高橋君は間違えて異なる文字列$ S $を書いてしまいました。幸い、書いた文字列の長さは間違っていませんでした。

そこで高橋君は、ある文字を別の文字に書き換えるという操作を最小の回数行って、この文字列を`CODEFESTIVAL2016`に書き換えることにしました。

書き換えの回数の最小値を求めてください。

## 说明/提示

### 制約

- $ S $の長さは$ 16 $である。
- $ S $ は英大文字、英小文字、数字からなる。

### Sample Explanation 1

$ 2 $文字目の`0`を`O`に、$ 14 $文字目の`O`を`0`に書き換える必要があります。

## 样例 #1

### 输入

```
C0DEFESTIVAL2O16```

### 输出

```
2```

## 样例 #2

### 输入

```
FESTIVAL2016CODE```

### 输出

```
16```

# 题解

## 作者：Ca1JH (赞：4)

##    [题 目 传 送 门](https://www.luogu.com.cn/problem/AT2079)

###  题意 
输入一个长度为16且无特殊字符的字符串和“CODEFESTIVAL2016”比较，求出有几个字符不相同

### 思路
逐一比对，可以直接用字符，也可以用ASCII码

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans,b[16]={67,79,68,69,70,69,83,84,73,86,65,76,50,48,49,54};//CODEFESTIVAL2016的ASCII码值 
char a[16]; 
int main()
{
	for(int i=0;i<16;i++)//循环十六遍 
	{
		cin>>a[i];
		if(a[i]!=b[i])//是“！=”号 
		{
			ans++;
		}
       		//输入并逐一比对 
	}
	cout<<ans<<endl;//别忘换行
	return 0;//结束
}

```


---

## 作者：Messi李 (赞：2)

这么~~难~~的一题怎么没人发题解嘞

我来一篇

一位dalao的隐藏 题意：初始字符串：CODEFESTIVAL2016

然后输入一个长度相同的字符串，输出有几个字符与初始字符串不同。

代码上

```
#include<bits/stdc++.h>//万能文件头
using namespace std;
string s="CODEFESTIVAL2016";//好像也没什么用
string a;
long long ans;
int main(){
    cin>>a;//输入字符串
    if(a[0] != 'C') ans++;//开始无脑判断
    if(a[1] != 'O') ans++;//要是有一个不一样
    if(a[2] != 'D') ans++;//就马上加上去
    if(a[3] != 'E') ans++;
    if(a[4] != 'F') ans++;
    if(a[5] != 'E') ans++;
    if(a[6] != 'S') ans++;
    if(a[7] != 'T') ans++;
    if(a[8] != 'I') ans++;
    if(a[9] != 'V') ans++;
    if(a[10] != 'A') ans++;
    if(a[11] != 'L') ans++;
    if(a[12] != '2') ans++;
    if(a[13] != '0') ans++;
    if(a[14] != '1') ans++;
    if(a[15] != '6') ans++;
    cout<<ans<<endl;//加完了，输出
}
```

---

## 作者：高雍博 (赞：1)

**水啊！只有16个字符！**

~~跑题了。~~

大致思路（这玩意还需要思路？！）：输入一个字符串，用自带的数组存储，接下来用 $if$ 语句判断，如果相同则计数器 $ans$ 增加，最后用$16$一减就是不同的，输出即可。

**注意数组要从$0$开始！从$0$开始！从$0$开始！**（重要的事情说三遍）

同时，一定要对计数器进行初始化，不然可能会有玄学错误。



该说的都在代码里。

```python
s=input()   #输入字符串
ans=0      #初始化总数

#接下来挨个字符判断，没什么好说的，一样就增加总数

#要注意的一点就是数组一定要从0开始，不然会数组越界

if s[0]=='C':
    ans+=1
if s[1]='O':
    ans+=1
if s[2]='D':
    ans+=1
if s[3]='E':
    ans+=1
if s[4]='F':
    ans+=1
if s[5]='E':
    ans+=1
if s[6]='S':
    ans+=1
if s[7]='T':
    ans+=1
if s[8]='I':
    ans+=1
if s[9]='V':
    ans+=1
if s[10]='A':
    ans+=1
if s[11]='L':
    ans+=1
if s[12]='2':
    ans+=1
if s[13]='0':
    ans+=1
if s[14]='1':
    ans+=1
if s[15]='6':
    ans+=1
ans=16-ans
print(ans)  #由于是统计了相同的，最后要减一下，然后输出即可
```

我是统计了相同的，大家也珂以尝试直接统计不同的然后输出，效果相同。~~因为我作，~~我选择了一个较容易出错的，大家记得最后用$16$减一下。

**求过！！**

---

## 作者：蒟蒻取不来名 (赞：1)

没有什么是一个数组解决不了的，如果有，那就开两个

没错，我又来水岛国水题了，这题翻译非常通俗易懂，我就不说了

```
#include<iostream>
using namespace std;
char a[16], b[16] = {'C', 'O', 'D', 'E', 'F', 'E', 'S', 'T', 'I', 'V', 'A', 'L', '2', '0', '1', '6'};//直接字符数组走一波，后面比较方便
int ans;//定义ans为答案/在函数外面定义的全局变量初始值默认为0
int main()
{
	cin >> a;//不需要一个字符一个字符的输，题目数据全都是16位的，不用担心超界限
	for(int i = 0; i < 16; i ++){
		if(a[i] != b[i]) ans ++;//循环比较，如果不一样ans+1
	}
	cout << ans << endl;//endl可以不加
	return 0;//养成好习惯
}
```
最后花式求过QwQ

---

## 作者：ShimizuSKT (赞：1)

看完题解，发现没有正向计数的程序呢（本蒟蒻也就看懂了两篇），干脆动手写一篇算了~~（反正是大水题）~~
（蒟蒻第一次发题解，各位大佬勿喷）
下面为AC代码：
```cpp
#include<bits/stdc++.h>//祖传头文件 
using namespace std;
string m,n="CODEFESTIVAL2016";//同逆向计数做法，用字符串秒天秒地秒空气 
int tot;//定义总数total 
int main(){
    cin>>m;//读入需判断的字符串 
    for(int i=0;i<16;i++){
    	if(m[i]!=n[i])//依次判断 
    		tot++;//若不一样，总数自增 
	}
	cout<<tot<<endl;//打印total,ps:我感觉ATcoder都要求加换行符，加上保险些（反正加上又不会错） 
    return 0;//完结撒花，QAQ求过 
}
```


这里提醒一下，本题有个误区，此处判断是否一致的对象是对应的，比方说样本第一个C就对应对象的以一个字符，若一致值就增加1，反之则否
以下为中招代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
string m,n="CODEFESTIVAL2016";
int tot,to;
int main(){
    cin>>m;
    for(int i=0;i<16;i++){
    	for(int l=1;l<=16;l++){
    		if(m[i]!=n[l])
    			to++;
		}
		if(to=16)
			tot++;
	}
	cout<<tot<<endl;
    return 0;
}
```
这题真的很~~难~~，米娜桑务必自己动手（笑）

---

## 作者：CZQ_King (赞：1)

做法：先假设全部错误，然后如果有正确的，就减去$1$，最后就是答案。


------------

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a,b="CODEFESTIVAL2016";
int c=16;//全错
int main(){
    cin>>a;
    for(int i=0;i<16;i++)//循环16次，逐个判断
    c-=(a[i]==b[i])?1:0;//问号运算符
    cout<<c<<endl;//输出答案
    return 0;//完美结束
}
```

---

## 作者：liuyifan (赞：1)

~~楼下那位暴力判断的,你就不会写个for吗~~

题意:输入一个字符串,输出它与“CODEFESTIVAL2016”不同字符的个数

正解:将输入的字符串与标准字符串逐字比对,如果不一样就ans++

code:
```cpp
#include<bits/stdc++.h>//万能头文件,包含了c++中几乎所有的库
#define ll long long
using namespace std;
string s="CODEFESTIVAL2016a;//定义字符串
ll ans;//习惯性开long long
int main()
{
	getline(cin,a);//与cin>>a相比可以直接读入一整行,将空格一并读入,遇到回车停止
	//虽然这道题好像并没有这类数据
	for(register ll i=0;i<=15i++)
	if(a[i]!=s[i])ans++;//逐字比对
	注意字符串是从0开始存储的,到length-1截止
    cout<<ans<<endl;
    return 0;
}
```
拒绝抄袭,共建和谐洛谷

---

## 作者：Franka (赞：0)

~~没有Pascal的题解？那我就来水一发。~~

### **题目**
输入一个**字符串**,输出它与**CODEFESTIVAL2016**不同字符的个数。

### **思路**
只需读入一个字符串，然后一个$for$循环，看看$n_i$跟$n1_i$是不是不一样，如果不一样，则$s$加一。
### **代码**
```pascal
var
 n,n1:string;//定义n和n1
 i,s:longint;//定义i和s
begin
 readln(n);//读入n
 n1:='CODEFESTIVAL2016';//n1初始化
 for i:=1 to 16 do if n[i]<>n1[i] then inc(s);如果不一样，则s加一
 writeln(s);//输出s
end.//完美结束
```


---

## 作者：ygl666666 (赞：0)

# 题意梳理
要求我们求输入的字符串中有几个和CODEFESTIVAL2016不同，
所以只要**一个个判断**(✪ω✪)即可qwq
# 代码，判断判断再判断
```
/**/
#include<bits/stdc++.h>
using namespace std;
char a[100001];
int ans;
int main(){
	ios::sync_with_stdio(false);
	gets(a);
	if(a[0]!='C'){
		ans++;
	}if(a[1]!='O'){
		ans++;
	}if(a[2]!='D'){
		ans++;
	}if(a[3]!='E'){
		ans++;
	}if(a[4]!='F'){
		ans++;
	}if(a[5]!='E'){
		ans++;
	}if(a[6]!='S'){
		ans++;
	}if(a[7]!='T'){
		ans++;
	}if(a[8]!='I'){
		ans++;
	}if(a[9]!='V'){
		ans++;
	}if(a[10]!='A'){
		ans++;
	}if(a[11]!='L'){
		ans++;
	}if(a[12]!='2'){
		ans++;
	}if(a[13]!='0'){
		ans++;
	}if(a[14]!='1'){
		ans++;
	}if(a[15]!='6'){
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：可爱的小白 (赞：0)

解题思路：输入一个字符串,输出它与“CODEFESTIVAL2016”不同字符的个数
上代码
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std; 
int ans;//定义一个计数器，来记录与CODEFESTIVAL2016不同的字母个数 
string s;//定义一个字符串 
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",strout);
	cin>>s;//输入这个字符串，↓使用打表的方法 
	if(s[0]!='C')  ans++;//CODEFESTIVAL2016
	if(s[1]!='O')  ans++;//ODEFESTIVAL2016
	if(s[2]!='D')  ans++;//DEFESTIVAL2016
	if(s[3]!='E')  ans++;//EFESTIVAL2016
	if(s[4]!='F')  ans++;//FESTIVAL2016
	if(s[5]!='E')  ans++;//ESTIVAL2016
	if(s[6]!='S')  ans++;//STIVAL2016
	if(s[7]!='T')  ans++;//TIVAL2016
	if(s[8]!='I')  ans++;//IVAL2016
	if(s[9]!='V')  ans++;//VAL2016
	if(s[10]!='A')  ans++;//AL2016
	if(s[11]!='L')  ans++;//L2016
	if(s[12]!='2')  ans++;//2016
	if(s[13]!='0')  ans++;//016
	if(s[14]!='1')  ans++;//16
	if(s[15]!='6')  ans++;//6
	cout<<ans<<endl;//最后输出 

	return 0;//完美结束 
}
```


---

## 作者：wushuang0828 (赞：0)

大水题……

题意讨论帖里有……

**思路：先给初始字符串赋值，再for循环判断**

直接上代码：
```pascal
var
 s,s1:string;
 ss,i:longint;
begin
 readln(s);
 s1:='CODEFESTIVAL2016';//初始字符串赋值
 for i:=1 to 16 do
  if s[i]<>s1[i] then inc(ss);//判断是否相等，不相等就累加
 writeln(ss);//输出有多少个不同的字符
end.
```

---

## 作者：不到前10不改名 (赞：0)

楼下那位大佬貌似不会用LaTeX呢（逃~）

```
#include<stdio.h> 
#include<string.h>
int main()
{
    int i,ans=0;
    char srx[21],sry[21]={"CODEFESTIVAL2016"};
    gets(srx);//还是使用C语言gets的我是不是很蠢...
    for(i=0;i<strlen(srx);i++)
    if(srx[i]!=sry[i])
    ans++;//其实也可以是ans=15; if(srx[i]==sry[i]）ans--;
    printf("%d\n",ans);//回车这种东西不用说...
    return 0;
}
```

---

