# Indeedなう！

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-quala/tasks/indeednow_2015_quala_2

あなたには、$ N $ 個の文字列 $ {S_1,S_2,...,S_N} $が与えられます。 それぞれの $ i\ (1≦i≦N) $ について、$ S_i $ が `indeednow` のアナグラムになっているかどうかを判定しなさい。

文字列 $ A $ と $ B $ について、$ A $ に含まれる文字を任意の順番で並び替えて $ B $ にできるとき、$ A $ を $ B $ のアナグラムと呼びます。

## 说明/提示

### Sample Explanation 1

たとえば `nowindeed` や `windoneed` に含まれる文字を並び替えると `indeednow` にすることができます。 したがって `nowindeed` や `windoneed` は `indeednow` のアナグラムです。 一方、 `indeedwow` や `a` は、並び替えても `indeednow` にすることはできないため、`indeednow` のアナグラムではありません。

## 样例 #1

### 输入

```
10
nowindeed
indeedwow
windoneed
indeednow
wondeedni
a
indonow
ddeennoiw
indeednoww
indeow```

### 输出

```
YES
NO
YES
YES
YES
NO
NO
YES
NO
NO```

# 题解

## 作者：智子·起源 (赞：6)

### ~~第二篇题解的详细版~~

## 对于每个字符串，我们可以将其排序之后与“ddeeinnow”（排序后的“indeednow”）进行比较。

### 如果等于就证明它可以变成indeednow，输出“YES”，否则输出“NO”。

程序也是目前码风最好，最简短的。请过目：
```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int n;string s;
int main()
{
  cin>>n;
  for(int i=0;i<n;i++)
  {
    cin>>s;
    sort(s.begin(),s.end());//对字符串进行排序
    if(s=="ddeeinnow")cout<<"YES"<<endl;//如果等于“ddeeinnow”那就输出“YES”
      else cout<<"NO"<<endl;//否则输出“NO”。
  }
  return 0;
}
```


---

## 作者：ACE_ZY (赞：3)

来一篇pascal的题解吧

意思是:有n个字符串 判读它是否能组成indeednow这个单词

能的话 输出YES 不能的话 输出NO

其它就不多说了 直接上pascal代码
```pascal
var
  n,i,j:longint;
  s:string;
  p:boolean;
  a:array['a'..'z'] of longint;
begin
  readln(n);//n个字符串
  for i:=1 to n do
  begin
    readln(s);//读入字符串
    fillchar(a,sizeof(a),0);//将数组清空 因为上一次的不能保留到这一次
    if length(s)=9 then//首先判断字符串的长度(长度都不符合 就更别说了)
    begin
      for j:=1 to length(s) do//累计各个字符出现的个数
      begin
        a[s[j]]:=a[s[j]]+1;
      end;
    end;
    p:=true;//反证法 我们刚开始认为它是可以组成的 p等于true 然后一个一个判断 判断条件是否满足
    if a['i']<>1 then p:=false;//indeednow这个单词里i出现了一次 所以要判断我们读入的单词了i是否也只出现了一次 
    if a['n']<>2 then p:=false;//以此类推
    if a['d']<>2 then p:=false;
    if a['e']<>2 then p:=false;
    if a['o']<>1 then p:=false;
    if a['w']<>1 then p:=false;
    if p then writeln('YES')//判断是否有不满足的条件 没有输出YES
      else writeln('NO');//有 输出NO
  end;
end.
```

望通过 谢谢

---

## 作者：hjxxcbq (赞：1)

# 这道题永远少不了桶来记！

[题目传送门](https://www.luogu.org/problemnew/show/AT1206)

这道题只用桶来记它们的字母，之后就判断是否相同。

变量提醒：**n就是n个字符串。a[27]就是桶，之所以定义27，是因为有26个字母，为了保险，再加1。c[27]也是桶，和上面一样原因，l是来记是否一样，b就是n个字符串的字符串，d就是indeednow**。

我为什么要用桶呢？

1.简单，容易打。

2.不耗时。

3.可以对付n比较大的。

4.本人对桶不熟。

代码如下：

```
#include<bits/stdc++.h>//万能头文件
using namespace std;//使用标准命名空间
int n,a[27],c[27],l;//前面已经说得很清楚了
string b,d="indeednow";//字符串，string
int main()//也许可以直接main()，不用int 。
{
for(int i=0;i<d.size();i++)//懒得打了，让电脑来记
c[int(d[i])-97]++;//用桶来记
cin>>n;//输入n
for(int i=0;i<n;i++)//开始了
{
cin>>b;//输入b
if(b.size()!=9)cout<<"NO"<<endl;//如果两个字符串不一样，9的意思是indeednow有多少个字母，直接输出NO，要换行！
else//否则
{
for(int j=0;j<b.size();j++)
a[int(b[j])-97]++;//用桶来记
for(int j=0;j<26;j++)
if(a[j]!=c[j])l=1;//如果不一样
if(l==0)cout<<"YES"<<endl;//如果都一样，输出YES，要换行！
else cout<<"NO"<<endl;//否则输出NO，要换行！
l=0;//清零，否则会一直l=1，就一直输出NO
for(int j=0;j<26;j++)
a[j]=0;//清空数组，也可以用memset(a,0,sizeof(a));最好别用！
}
}
return 0;//注意要return 0;
}
```

只是27行而已，不多不多。（本人自我安慰能力很强）

**题解有问题，可以私信我。**

---

## 作者：勘探员·引魂人 (赞：0)

**前言：最近因为某些自然原因，所以停更了...**

**思路：算出每个字符串中i、n、d、e、o、w的个数，然后判断字符串中i、n、d、e、o、w的个数是否与“indeednow”中i、n、d、e、o、w的个数一样，如果是输出"YES"，否则输出"NO"**

```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<string>
#include<cstring>
#include<cmath>
#include<cfloat>//文件头是个好东西，丢掉就"WA"了
using namespace std;
long long n;//定义n（long long类型）
long long ai,an,ad,ae,ao,aw;//定义记录i、n、d、e、o、w的个数的变量（long long类型）
string st;//定义字符串
int main()
{
	scanf("%lld",&n);//输入n
	while(n--)//这玩意儿相当于for(int i=1;i<=n;i++)
	{
		cin>>st;//输入每个字符串
		long long l=st.size();//定义记录字符串长度的变量
		for(int i=0;i<l;i++)//从0至字符串长度循环
		{
			if(st[i]=='i') ai++;//如果st[i]是'i'，'i'的个数++
			if(st[i]=='o') ao++;//如果st[i]是'o'，'o'的个数++
			if(st[i]=='n') an++;//如果st[i]是'n'，'n'的个数++
			if(st[i]=='e') ae++;//如果st[i]是'e'，'e'的个数++
			if(st[i]=='w') aw++;//如果st[i]是'w'，'w'的个数++
			if(st[i]=='d') ad++;//如果st[i]是'd'，'d'的个数++
		}
 		if(ai==1&&an==2&&ad==2&&ae==2&&ao==1&&aw==1) cout<<"YES"<<endl;//判断字符串中i、n、d、e、o、w的个数是否与“indeednow”中i、n、d、e、o、w的个数一样，如果是输出"YES"（记得换行！）
		else cout<<"NO"<<endl;//否则输出"NO"（记得换行！）
		ai=0,an=0,ad=0,ae=0,ao=0,aw=0;//记录i、n、d、e、o、w的个数的变量全部清0
	}
	
	return 0;//结束“题解 AT1206 【Indeedなう！】”
}
```

---

## 作者：wushuang0828 (赞：0)

**思路：先统计出字符串中每个字符出现的次数，让后，在判断这个字符串和indeednow中的字符出现的次数与长度是否相同，相同输出YES，否则输出NO**

具体看代码：
```pascal
var
 n,i,j:longint;
 s1:string;
 k:char;
 a:array['a'..'z'] of longint;
begin
 readln(n);
 for i:=1 to n do
  begin
   readln(s1);
   for j:=1 to length(s1) do
    if s1[j] in ['a'..'z'] then inc(a[s1[j]]);//统计输入的字符串中出现了哪些字符以及个数
   if (a['i']=1) and (a['n']=2) and (a['d']=2) and (a['e']=2) and (a['w']=1) and (length(s1)=9) and (a['o']=1) then writeln('YES')
                                                                                                               else writeln('NO');//判断输入字符串和indeednow中字符出现的次数是否相同，还要判断长度，要不然可能会wa
   for k:='a' to 'z' do
    a[k]:=0;//清零，不清零也会wa
  end;
end.
```

---

## 作者：CZQ_King (赞：0)

## 怎么没有人发排序的呢，蒟蒻在这里就来一波排序的吧。

------------
做法：将字符串排序，如果等于$ddeeinnow$就输出$\color{green}YES$，否则输出$\color{red}NO$

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int num;//输入的个数
string str;
int f(string a){//用一个函数，好看一点
	sort(a.begin(),a.end());//先排序
	if(a=="ddeeinnow")return 0;//判断是否为ddeeinnow，如果是，返回0
	else return 1;//否则返回1
}
int main(){
	cin>>num;//输入个数
	for(int i=0;i<num;i++){
		cin>>str;//再输入那个字符串
		if(f(str))cout<<"NO"<<endl;//判断
		else cout<<"YES"<<endl;
	}
	return 0;//结束
}
```

---

## 作者：_Qer (赞：0)

题意：给出N个字符串，判断每一个字符串是否可以通过排序，得出indeednow这个字符串，如果可以，输出YES,否则输出NO（数据大水）

经过一定的思考，我们可以发现：只要这个字符串出现i,n,d,e,o,w的次数和indeednow这个字符串中所出现的次数一样，就肯定能够成立。

所以我们可以使用一个数组（letter），存储每个字符出现的次数，用一个循环遍历输入字符串的每个字符，把数组中对应的元素值+1，最后比较即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
void f(){//判断是否成立的函数
    string s;//输入的字符串
    int letter[30]={0};//存储每个字符的出现次数
    cin>>s;
    for(int i=0;i<s.length();++i){
        ++letter[s[i]-'a'];//把对应的元素值+1
    }
    if(letter['d'-'a']==2&&letter['i'-'a']==1&&letter['n'-'a']==2&&letter['e'-'a']==2&&letter['o'-'a']==1&&letter['w'-'a']==1){
//看出现次数是否足够
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;++i){
        f();//调用函数
    }
    return 0;
}
```

---

