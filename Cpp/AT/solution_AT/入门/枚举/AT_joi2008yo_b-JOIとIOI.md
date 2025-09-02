# JOIとIOI

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2008yo/tasks/joi2008yo_b

与えられた文字列内の連続する $ 3 $ 文字が，`JOI` または `IOI` という並びになっている個所がそれぞれ何個所あるのかを数え上げるプログラムを作成せよ．文字列はアルファベットの大文字だけからなる．例えば下図の「`JOIOIOI`」という文字列には `JOI` が $ 1 $ 個所，`IOI` が $ 2 $ 個所に含まれている．

![2008-yo-t2-sample.png](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_joi2008yo_b/b4202de9541777caaf09e0fb98aba7dc6657072a.png)

- - - - - -

## 说明/提示

### Sample Explanation 1

\- - - - - -

### Sample Explanation 2

\- - - - - -

## 样例 #1

### 输入

```
JOIJOI```

### 输出

```
2
0```

## 样例 #2

### 输入

```
JOIOIOIOI```

### 输出

```
1
3```

## 样例 #3

### 输入

```
JOIOIJOINXNXJIOIOIOJ```

### 输出

```
2
3```

# 题解

## 作者：Gmt丶FFF (赞：4)

# 没人写find函数吗？
那本萌新来一篇吧。

萌新必看：find函数是string函数里面的一个自带函数，可以查找字符串中的某个字串，查找到了第一个字串就会给出下标，如果没有，就爆出-1。查找有两种方式，第一个是不加后缀，格式为 a.find("zichuan"); 第二种则是加了后缀，意味从下标第几位开始查找，格式为 a.find("zichuan",0); 注意，find只能查找到最近的一个字串。当然还有几个类似的 find ，但是这个是最实用的，其他的就暂时不讲了。

暴力find查找就行了，不解释。

```
#include<iostream>
#include<string>
using namespace std;
int main()
{
	int l=-1,ioi=0,joi=0;
	string a;
	cin>>a;
	while(a.find("IOI",l+1)!=-1)//注意，必须l+1，否则会无限寻找，死循环。
	{
		l=a.find("IOI",l+1);
		ioi++;
	}
	l=-1;
	while(a.find("JOI",l+1)!=-1)//如上。
	{
		l=a.find("JOI",l+1);
		joi++;
	}
	cout<<joi<<endl<<ioi<<endl;
	return 0;
}
```

---

## 作者：I_will (赞：2)

这道题比较简单，我认为要注意一个问题-->当JOIOIOI是算1个JOI和2个IOI。

这是一个思路：
* 输入：一个字符串
* 过程：一个for①或④（①配②，④配③），在for中判断IOI和JOI的数量，有两种算法：详情请看②和③。
* 输出：注：先输出JOI数量然后换行，再输出IOI数量和换行。
* ①：0~字符串范围-2-1-->(-3)。
* ②-Ⅰ：如发现‘I’则将这个和后面两个存进一个字符串，判断是否是IOI，是则ih++。
* ②-Ⅱ：如发现‘J’则将这个和后面两个存进一个字符串，判断是否是JOI，是则jh++。
* ③-Ⅰ：如发现‘I’则将这个和前面两个存进一个字符串，判断是否是IOI，是则ih++。
* ③-Ⅱ：如发现‘I’则将这个和前面两个存进一个字符串，判断是否是JOI，是则jh++。
* ④：2~字符串范围-1。

思路一程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
string n;
string v,vt;
int jh,ih;
int main()
{
	cin>>n;
	for(int i=0;i<n.size()-2;i++)
	{
		if(n[i]=='I'){v=n[i];v+=n[i+1];v+=n[i+2];
		}
		if(n[i]=='J'){vt=n[i];vt+=n[i+1];vt+=n[i+2];
		}
		if(v=="IOI")ih++;
		if(vt=="JOI")jh++;
		v="";
		vt="";
	}
	cout<<jh<<endl;
	cout<<ih<<endl;
	
	return 0;
}
```
思路二程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
string n;
string v,vt;
int jh,ih;
int main()
{
	cin>>n;
	for(int i=2;i<n.size();i++)
	{
		if(n[i]=='I'){v=n[i];v+=n[i-1];v+=n[i-2];
		}
		if(n[i]=='I'){vt=n[i];vt+=n[i-1];vt+=n[i-2];
		}
		if(v=="IOI")ih++;
		if(vt=="IOJ")jh++;//JOI反过来就是IOJ。IOI是回文字母。 
		v="";
		vt="";
	}
	cout<<jh<<endl;
	cout<<ih<<endl;
	
	return 0;
}
```


---

## 作者：不到前10不改名 (赞：2)

```
#include<stdio.h>
#include<string.h>//调用strlen函数（类似c++的size？？？~）
long long srx,sry;//防伪标识
char lhy[10001];
int i;
int main()
{
    scanf("%s",lhy);
    for(i=0;i<strlen(lhy);i++)
    {if(lhy[i]=='J'&&lhy[i+1]=='O'&&lhy[i+2]=='I')
    {srx++;}//判断就是暴力枚举，数据水（at不都这样~）
    if(lhy[i]=='I'&&lhy[i+1]=='O'&&lhy[i+2]=='I')
    {sry++;}}
    printf("%lld\n%lld\n",srx,sry);//回车
}
```

---

## 作者：Jinyeke (赞：0)

#### 怎么能木有p党的身影，咳咳，就是两个字，求过，废话不多说，看代码
```pascal
var
 a:ansistring;//不开ansistring会爆掉，简称bong！
 i,s1,s2:longint;
begin
 read(a);
 for i:=1 to length(a)-2 do //因为是连续三个，所以到length(s)-2就好了
  begin 
   if (a[i]='J') and (a[i+1]='O') and (a[i+2]='I') then inc(s1);//找JOI
   if (a[i]='I') and (a[i+1]='O') and (a[i+2]='I') then inc(s2);//找IOI
  end;
 writeln(s1);//输出JOI的数量
 writeln(s2);//输出IOI的数量
end.
   
```
### 共建文明洛谷，请勿Ctrl+C！

---

## 作者：RioBlu (赞：0)

暴力枚举即可

算法时间复杂度:O(N*3)

如果a[i]=='J'&&a[i+1]=='O'&&a[i+2]=='I'

JOI的数量+1

如果a[i]=='I'&&a[i+1]=='O'&&a[i+2]=='I'

IOI的数量+1
```
#include<bits/stdc++.h>
using namespace std;
string a;
long long ans1,ans2;
int main()
{
    cin>>a;
    for(int s=0;s<a.size()-2;s++)//for到a.size()-2即可
    {
        if(a[s]=='J'&&a[s+1]=='O'&&a[s+2]=='I')//判断
        ans1++;//JOI++
        if(a[s]=='I'&&a[s+1]=='O'&&a[s+2]=='I')//判断
        ans2++;//IOI++
    }
    cout<<ans1<<endl<<ans2<<endl;
}
```

---

## 作者：勘探员·引魂人 (赞：0)

**前言：怎么又是AT字符串入门题啊！**

**思路：用check和checked函数分别求出"IOI"的个数和"JOI"的个数，然后直接调用函数输出**

```
#include<iostream>
#include<string>//文件头是啥？能吃吗？
using namespace std;
string n;//定义字符串n
int check(string x)//check函数登场啦！
{
	int io=0;//io是"IOI"的个数
	for(int i=0;i<x.size()-2;i++)//从0到x.size()-2循环
	{
		if(x.substr(i,3)=="IOI") io++;//截取从i开始往后3个并判断，如果是"IOI"，"IOI"个数++
	}
	return io;//return "IOI"个数
}
int checked(string y)//checked函数登场啦！
{
	int jo=0;//jo是"JOI"的个数
	for(int j=0;j<y.size()-2;j++)//从0到y.size()-2循环
	{
		if(y.substr(j,3)=="JOI") jo++;//截取从i开始往后3个并判断，如果是"JOI"，"JOI"个数++
	}
	return jo;//return "JOI"个数
}
int main()
{
    cin>>n;//输入字符串
    cout<<checked(n)<<endl;//直接调用函数输出"JOI"个数
    cout<<check(n)<<endl;//直接调用函数输出"IOI"个数
	
    return 0;//结束“题解 AT2502 【JOIとIOI】”
}
```

---

