# A Blend of Springtime

## 题目描述

**题目大意：**

给定一个由'A','B','C','.'构成的字符串，'A''B''C'控制左中右三个位置，问是否存在一个位置'A''B''C'同时控制

## 样例 #1

### 输入

```
.BAC.
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
AA..CB
```

### 输出

```
No
```

# 题解

## 作者：Alex_Wei (赞：8)

模拟

读懂题意即可

### 如果一个格子里三种颜色都有，那么它和与它相邻两个格子里的颜色一定互不相同

即判断有没有连续的三种不同的颜色，且不能是空地

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	for(int i=1;i<s.size()-1;i++)
		if(s[i]!=s[i-1]&&s[i]!=s[i+1]&&s[i-1]!=s[i+1]&&s[i-1]!='.'&&s[i]!='.'&&s[i+1]!='.')//判断
			cout<<"Yes",exit(0);
	cout<<"No";
	return 0;
}
```

求赞$QWQ$

---

## 作者：btng_smith666 (赞：1)

```cpp
/*by btng_smith666 juruo*/
#include<bits/stdc++.h>//讲解全在代码里 
using namespace std;//命名空间 
string str;//存字符串 
bool flag=true;//true表示存在，false表示不存在，初始化为 true 
int main()//主函数 
{
	/*******************************
	*思路：此题就是枚举字符串，      *
	*如果这个字符和它左边、右边      *
	*的字符都是 ABC 中一个且不重     *
	*复就视为可被'A''B''C'同时控制   *
	*本篇代码主要是在循环中判断不     *
	*能被控制的一些情况              *
	*                              *
	*举几个栗子：                   *
	* ABC √                        *
	* ACA ×                        *
	* A.B ×                        *
	*******************************/
    cin>>str;//输入 
    for(int i=1;i<str.size()-1;++i)
    {//循环查询字符串从左到右的第二位到倒数第二位的字符，最左边和最右边都缺少元素无需考虑 
    	//这里的左、中、右分别表示成 str[i-1],str[i],str[i+1] 
		if(str[i]==str[i-1])//如果中间和左边是一样的 
			flag=false;//不行 
		else if(str[i]==str[i+1])//如果中间和右边是一样的 
			flag=false;//不行 
		else if(str[i-1]==str[i+1])//如果左边和右边是一样的 
			flag=false;//不行 
		else if(str[i]=='.')//如果中间的不是 ABC 中一个 
			flag=false;//不行 
		else if(str[i-1]=='.')//如果左边的不是 ABC 中一个 
			flag=false;//不行 
		else if(str[i+1]=='.')//如果右边的不是 ABC 中一个 
	        flag=false;//不行 
	    else//如果都上面的都不满足，就说明可以控制 
	    {
	    	printf("Yes");//直接输出 Yes 
	    	return 0;//结束 
		}
	}
    printf("No");//否则输出 No 
}//求赞 qwq 
```

---

## 作者：judgejudge (赞：1)

# 最短代码！！！


------------

首先在这里要先感谢Dawn_Chase大佬的帮助，帮我解决了程序最后的不足之处！！

这个程序的意思其实就是让我们找一个位置**被A,B,C控制**，重点是要如何确定是否被控制，大部分大佬写得比较复杂，在这里我提供一个新思路：

我们不是知道每一个字符有ASCII码？**那么我们可以定义一个数组，作为位置，一旦出现A,B,C就可以记录下来，最后判断是否有！！！
**

所以我的判断方式是**ASCII码！！**

奉上代码及解说：
```cpp
#include <iostream>
#include <string>
using namespace std;
long long a[1000000];//此处建议数组开大点，Code的数据点都很庞大的 
int main(){
	int i,j;
	long long k,n;//long long 保险
	string st;
	cin>>st;
	for(i=0;i<st.length();i++){
		if(st[i]>='A'&&st[i]<='C'){//此处判断是否为A,B,C
			a[i]+=st[i];//我们利用ASCII码，加上A,B,C的ASCII码！！
			a[i+1]+=st[i];//这样的话就可以辨认是否有A,B,C
			a[i+2]+=st[i];
		}
	}
	for(i=1;i<=st.length();i++)
	if(st[i-1]>='A'&&st[i-1]<='C'){//优化：因为是.时不可能存在
		if(a[i]==198&&st[i-1]!=st[i]){//注意：BBB时这个程序会有漏洞！所以加上st[i-1]!=st[i]来判断不是BBB
			cout<<"YES"<<endl;
			return 0;
		}
	}
	cout<<"NO"<<endl;//如果没执行YES，说明必然没有，输出NO
	return 0;
}
```

---

## 作者：wushuang0828 (赞：1)

这道题主要求一个字符串是否存在一个长度为三且含有A, B, C三个字母的子串，如果有输出Yes，否则输出No


这里我用到了POS函数

###     pos函数的作用：
####      作用：返回子串在某个字符串中起始位置
       例如：
        s:='123453';
        x:=pos('3',s);
        结果：x=3，而不是6
        
### halt是结束整个程序

### break是结束当前循环
        
以下就是代码：

```
var
 s,s1:string;
 i:longint; 
begin
 readln(s);//输入字符串
 for i:=1 to length(s) do//枚举
  begin
   s1:=copy(s,i,3);//将当前这位和后面两位拷出来
   if length(s1)<3 then break;//如果长度＜3直接退出循环，因为位数不够无法判断
   if (pos('A',s1)<>0) and (pos('B',s1)<>0) and (pos('C',s1)<>0) then
    begin//如果这个子串中同时含有A, B, C三个字母则直接输出Yes
     writeln('Yes'); //输出Yes
     halt;//结束整个程序
    end;
  end;
 writeln('No');//如果每一位都判断完了，但还是没找到，就输出No
end.
```

---

## 作者：Victory_Defeat (赞：1)

这道题很水，就是**每一个字母分裂成左、中、右三个**，然后有没有位子是**三个字母都有的**

这里我使用了$STL$中的$map$，它可以统计负数，当然，由于**$1$号左边和$n$号右边是不可取的**，所以不必统计

代码：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<queue>
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;
typedef double lf;
typedef unsigned un;
typedef int in;
#define mian main
#define _(a) read(a)
#define non void
#define inf 2147483647
#define bre break
#define con continue
#define prq priority_queue
#define Re register
#define bu bool
#define cz char
#define cst const
#define ope operator
#define inl inline
#define upp upper_bound
#define low lower_bound
#define next_pre next_premutation
template<typename T>inl T Max(T a,T b){return a>b?a:b;}
template<typename T>inl T Min(T a,T b){return a<b?a:b;}
template<typename T>inl T Abs(T a){return a<0?-a:a;}
template<typename T>inl non read(T &a){a=0;T k=1;char c=getchar();while(c<'0'||c>'9')k=c=='-'?-1:k,c=getchar();while(c>='0'&&c<='9')a=a*10+(c^48),c=getchar();a*=k;}
template<typename T>non write(T a,cz t=' '){if(a==0){putchar(48),putchar(t);return;}if(a<0){a=-a;putchar('-');}cz c[30];in le=0;while(a){c[++le]=a%10+48;a/=10;}for(Re in i=le;i>=1;--i)putchar(c[i]);putchar(t);}
//这上面不用管
cz a[105];
in s[105][3],l;
in main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>a;
	l=strlen(a);
    //输入
	for(Re in i=0;i<=l-1;++i)
	{
		if(a[i]=='A')++s[i-1][0],++s[i+1][0],++s[i][0];
		if(a[i]=='B')++s[i-1][1],++s[i+1][1],++s[i][1];
		if(a[i]=='C')++s[i+1][2],++s[i-1][2],++s[i][2];
	}
    //每一个都分裂
	for(Re in i=-1;i<=l;++i)if(s[i][0]&&s[i][1]&&s[i][2]){printf("Yes");return 0;}
    //判断并输出
	printf("No");
}
```

---

