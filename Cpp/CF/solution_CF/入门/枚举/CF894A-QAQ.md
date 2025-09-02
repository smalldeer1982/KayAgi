# QAQ

## 题目描述

"QAQ" is a word to denote an expression of crying. Imagine "Q" as eyes with tears and "A" as a mouth.

Now Diamond has given Bort a string consisting of only uppercase English letters of length $ n $ . There is a great number of "QAQ" in the string (Diamond is so cute!).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF894A/333c4dadce3b03c143ff500b3cc7457c4f2b76a3.png)illustration by 猫屋 https://twitter.com/nekoyaliuBort wants to know how many subsequences "QAQ" are in the string Diamond has given. Note that the letters "QAQ" don't have to be consecutive, but the order of letters should be exact.

## 说明/提示

In the first example there are $ 4 $ subsequences "QAQ": "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN".

## 样例 #1

### 输入

```
QAQAQYSYIOIWIN
```

### 输出

```
4
```

## 样例 #2

### 输入

```
QAQQQZZYNOIWIN
```

### 输出

```
3
```

# 题解

## 作者：「已注销」 (赞：18)

#### 暴力?dp?
#### 每个A能形成的QAQ数量是左边Q的数量乘右边Q的数量
#### 数组保存每个位置前Q数量，然后找A就行
```cpp
#include<iostream>
using namespace std;
int ans,t,q[100];
string s;
int main(){
	cin>>s;
	for(int i=0;i<s.size();++i)q[i]=s[i]=='Q'?++t:t;
	for(int i=0;i<s.size();++i)if(s[i]=='A')ans+=q[i]*(t-q[i]);
	cout<<ans;
}
```

---

## 作者：一扶苏一 (赞：11)

###  一道入门动态规划。这种题写暴力其实浪费了

我们用Q[i]表示第i位（含）以前的**Q**的个数，QA[i]表示第i位（含）以前的**QA**的个数。

不难发现，我们如果在**第i位**找到**Q**，则QAQ的个数就要加上**QA[i-1]**位。（因为前i-1位QA**每个**QA都能和第i位的QA进行匹配）。

不难写出状态转移方程：

![状态转移方程](https://cdn.luogu.com.cn/upload/pic/19184.png)

其中s表示给定的字符串。

下面是C语言代码：
```c
#include<stdio.h>
#include<string.h>

char ch[110];int Q[110],QA[110],ans;

int main() {
	scanf("%s",ch);
	int l=strlen(ch);
	for(int i=0;i^l;++i) {
		Q[i]=Q[i-1],QA[i]=QA[i-1];
		if(ch[i]=='Q') {
			++Q[i];
			ans+=QA[i];
		}	
		if(ch[i]=='A')	QA[i]+=Q[i];
	}
	printf("%d\n",ans);
	return 0；
}
```

---

## 作者：开挂老司机 (赞：5)

一道简单的深搜题(￣▽￣)／

其实这道题我本来不愿意刷（太水了），可俗话说“不交一日闲过（好像不是这个交吧）”，所以我还是刷了~~

二话不说上代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>//字符串头文件
using namespace std;
string s,s1="QAQ";
int ans;
void dfs(int step,int x)//深搜部分
{
	if(step==3)//如果三次都查找成功
	{
		ans++;//累加答案
		return ;//结束递归
	}
	for(int i=x+1;i<s.length();i++)//从上次的地方继续搜索
		if(s[i]==s1[step])//如果当前字符和需要找的一样
			dfs(step+1,i);//递归
}
int main()
{
	getline(cin,s);//输入字符串
	dfs(0,-1);//深搜开始
	printf("%d\n",ans);//输出
	return 0;
}
```

求各位大佬不喜勿喷orz

---

## 作者：return先生 (赞：4)

各位大佬的代码都很厉害，我就用了个暴力又简单的方法了。

一开始的时候我以为每个QAQ中间不能有其他的QAQ，也就是每个QAQ只能跟中间没有隔着其他A的A匹配，写完发现样例过不了，只好仔细看了一下，从新打了一个代码，却发现会超时了，只好优化。

这是一开始的RE代码：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int ans=0;
    string a;
    cin>>a;
    for(int i=0;i<a.size()-2;i++)
    {
        if(a[i]=='Q')
        {
            for(int j=i+1;j<a.size();j++)
            {
                if(a[j]=='A')
                {
                    for(int k=j+1;k<=a.size();k++)
                    {
                        if(a[k]=='Q')
                        {
                            ans++;
                        }
                    }
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
```
后来想到，可能是在除了Q和A的其他字符上面浪费了太多的时间，不如先把Q和A从中提取出来，再做判定。

于是

```cpp
#include<iostream>
using namespace std;
int main()
{
    string a;
    char b[10086];
    int js=0,A=0,B=0,C=0,ans=0;
    cin>>a;
    for(int i=0;i<a.size();i++)
    {
        if(a[i]=='Q'||a[i]=='A')
        {
            js++;
            b[js]=a[i];
        }
    }
    for(int i=0;i<=js;i++)
    {
        if(b[i]=='Q')
        {
            if(A==0)
            {
                A=1;
            }
            else
            {
                if(B==1)
                {
                    C=1;
                }
            }
        }
        if(b[i]=='A')
        {
            if(A==1)
            {
                B=1;
                //C=0;
            }
        }
        if(A*B*C==1)
        {
            ans++;
            //B=0;
            //C=0;
        }
    }
    cout<<ans;
    return 0;
}
```

然后就AC了。

(真不敢想象我在这道题上面浪费了四个小时）

---

## 作者：litianle (赞：4)

**P.S:Code Forces是俄罗斯一个非常棒的OI网站，入门级别的题目可以练手，最难也差不多NOI级别。题目全英文，洛谷上附有大犇翻译，想要练英文的同学也可以自己理解。**

------------
****
[CF894A 题目链接](https://www.luogu.org/problemnew/show/CF894A)

#### 题目描述

"QAQ" is a word to denote an expression of crying. Imagine "Q" as eyes with tears and "A" as a mouth.

Now Diamond has given Bort a string consisting of only uppercase English letters of length n n . There is a great number of "QAQ" in the string.

#### 输入输出格式

##### 输入格式：
The only line contains a string of length n n ( 1<=n<=100 1<=n<=100 ). It's guaranteed that the string only contains uppercase English letters.

##### 输出格式：
Print a single integer — the number of subsequences "QAQ" in the string.

#### 输入输出样例

##### 输入样例#1： 
QAQAQYSYIOIWIN
##### 输出样例#1： 
4
##### 输入样例#2： 
QAQQQZZYNOIWIN
##### 输出样例#2： 
3

#### 题目分析
简单地理解，就是求字符串中三个字符可以构成'QAQ'的种数。

#### 解答方法
1.暴力三层循环（对新手比较友好的做法）

由于题目数据范围是100，所以允许我们使用这种简单暴力的做法。
```cpp
#include "bits/stdc++.h"
using namespace std;
char str[101]={'\0'};
int main()
{
	int i,j,k,len,count=0;//初始值赋0不要忘记
	scanf("%s",str);
	len=strlen(str);//提前存好字符串长度避免重复运算
	for(i=0;i<len;i++)
	{
		for(j=i+1;j<len;j++)//由于是往后找所以从i+1开始循环
		{
			for(k=j+1;k<len;k++)//与j同理
			{
				if(str[i]=='Q'&&str[j]=='A'&&str[k]=='Q')
				{
					count++;
				}
			}
		}
	}
	printf("%d\n",count);
	return 0;
}
```

P.S:本人因为有强迫症代码较为整齐，大家看得也清晰些。

2.数学算法

对于每一个A，可以组成"QAQ"的种数就是该A之前的Q的数量乘以之后的Q的数量（根据乘法定理）。
```cpp
#include "bits/stdc++.h"
using namespace std;
char str[101]={'\0'};
vector<int> pre,next;//pre[i],next[i]分别代表第i个字符前后各有几个Q
int main()
{
	int i,len,count=0;
	scanf("%s",str);
    len=strlen(str);
    pre.resize(len+1);
    next.resize(len+1);
    pre[0]=0;//处理数据边界
    next[len-1]=0;
    for(i=1;i<len;i++)
	{
		pre[i]=pre[i-1];
    	if(str[i-1]=='Q')
        {
            pre[i]++;
		}
	}
    for(i=len-2;i>=0;i--)
    {
    	next[i]=next[i+1];
    	if(str[i+1]=='Q')
    	{
    		next[i]++;
		}
	}
	for(i=0;i<len;i++)
	{
		if(str[i]=='A')
		{
			count+=(pre[i]*next[i]);
		}
	}
	printf("%d\n",count);
	return 0;
}
```
**代码可能有些繁琐，各位大犇勿喷。**

---

## 作者：土川崇贺 (赞：3)

		这道题很多dalao是花费了很多时间琢磨出了一些很巧妙的方法，但其实数据不是很大，暴力枚举就可以AC的。
        代码奉上：
```cpp
#include<iostream>
using namespace std;
int main()
{
    string a;
    int c=0;
    bool flag;
	cin>>a;
	for(int i=0;i<a.length();i++)
	{
		flag=true;
		if(a[i]=='Q') 
		{
			for(int j=i;j<a.length();j++)
			{
				if(a[j]=='A')
				{
					for(int k=j;k<a.length();k++)
					{
						if(a[k]=='Q')
						{
							c++;
							flag=false;
						}
					}
				}
			}
		}
	 } 
	 cout<<c;
	return 0;
}

```

---

## 作者：AdzearDisjudge (赞：2)

翻了一下题解全是考虑A前后Q的个数的解法（那就来一发三个分类好了）

对于每个Q

能形成1个“Q”

能形成到此为止“QA”个数个“QAQ”

对于每个A

能形成到此为止“Q”个数个“QA”

dp转移即可

~~这题要是我就直接把|S|开到1e8，还是Div2A难度（逃）~~

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(register int i=a;i<=n;++i)
using namespace std;
string s;
int QAQ[3][101]={0},x; 
int main()
{
	cin>>s;
	x=s.size();
	rep(i,0,x-1)
	{
		if(i!=0)
		{
			QAQ[0][i]=QAQ[0][i-1];
			QAQ[1][i]=QAQ[1][i-1];
			QAQ[2][i]=QAQ[2][i-1];
		}
		if(s[i]=='Q')
		{
			QAQ[0][i]+=1;
			QAQ[2][i]+=QAQ[1][i];
		}
		if(s[i]=='A')
		QAQ[1][i]+=QAQ[0][i];
	}
	cout<<QAQ[2][x-1];
    return 0;
}

```

---

## 作者：Tarensev (赞：1)

让我为你们提供一种~~看上去不暴力的~~递归题解

虽然说三重暴力也行，但是循环体一多写起来就很麻烦

而且我按照一些情况适当进行了剪枝

听上去蛮不错的样子，我们开始吧

```pas
const a:array[1..3] of char=('q','a',‘q’);
var s:string;
    ans:longint;
procedure p(x,y:longint);{x记录是qaq中的某一位，因为qaq是有顺序的，所以要用一个y来记录}
 var i:longint;
 begin
  if x=4 then {这是一个边界，表示已经弄好了}
   begin
    {writeln(y);}
    ans:=ans+1;
   end;
  for i:=y+1 to length(s)-(3-x) do{这是一个剪枝，如果是第一个q那么就只要减去，因为还要腾出位置给a和q}
   if s[i]=a[x] then p(x+1,i);{如果符合qaq，那么就递归}
 end;
begin
 readln(s);
 p(1,0);{调用递归}
 writeln(ans);
end.
```
蒟蒻还有很多东西需要完善，请各位神犇们指点，谢谢！

---

## 作者：yuzhechuan (赞：1)

方法与楼下的有异曲同工之妙

但个人认为更好理解

~~应为楼下的代码蒟蒻我看不懂~~

-------------------------华丽的代码分割线---------------------------
```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
    int l,ans,i,a[100];
    char s[100];
    gets(s);
    l=ans=0;
    if(strlen(s)<3)//！！！注意！！！一个易错点...
    {              //特判连3个字符都不足的情况，不然会乱码？负数？
        cout<<0;   //别问我是怎么知道的...
        return 0;
    }
    for(i=0;i<=strlen(s)-1;i++) //-1因为strlen的特性...
    {
		if(s[i]=='Q') l++;
		a[i]=l;            //a[]存储i左边(包括本身)的Q数量
    	//cout<<a[i]<<" ";
	}
	//cout<<endl;
	for(i=1;i<=strlen(s)-2;i++)
    if(s[i]=='A')
    {
    	ans+=a[i]*(a[strlen(s)-1]-a[i]);//用最多(即strlen(s)-1)减当前位表示右边的Q数量
	}
	cout<<ans;
}
```
--------------------------华丽的结束分割线---------------------------



---

## 作者：_Qer (赞：1)

看到N只有100

直接水一手暴力

一手递归，慢一点没关系

每次判断到是QAQ中的一位，就往后递归每一位

如果发现数完三个字母了，就返回1，即答案数加一

```cpp
#include<bits/stdc++.h>
using namespace std;
char in[105],fi[5]={"QAQ"};//in是输入的字符串,fi是要找的QAQ
int ans,l;//ans为答案数，l为字符串长度
int f(int x,int k){//递归函数
    if(in[x]==fi[k]){//如果是当前要找的字母
        ++k;//找下一个
        if(k==3){//如果已经找完三个，返回1
            return 1;
        }
        int tp=0;//接下来的方法总数
        for(int i=x+1;i<l;++i){//循环字符串每一位
            tp+=f(i,k);//加上第i位的方法数
        }
        return tp;//返回下面所有的方法数
    }
    return 0;//不是要找的字母，0种方法
}
int main(){
    cin>>in;
    l=strlen(in);
    for(int i=0;i<l;++i){//每一位递归
        ans+=f(i,0);//加上第i个字符为首字符的方法数
    }
    cout<<ans;
    return 0;
}
```

---

