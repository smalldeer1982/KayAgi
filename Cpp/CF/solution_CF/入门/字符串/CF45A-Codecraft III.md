# Codecraft III

## 题目描述

给你一个月份，问你 $k$ 个月后的月份。

月份列表：

January, February, March, April, May, June, July, August, September, October, November, December

## 样例 #1

### 输入

```
November
3
```

### 输出

```
February
```

## 样例 #2

### 输入

```
May
24
```

### 输出

```
May
```

# 题解

## 作者：xhQYm (赞：18)



这题是一道模拟题，十分简单。

这题的思路如下：

1. 输入

2. 找出要输出的是那个月份

3. 输出

是不是很简单鸭。

首先，这题需要定义一个数组来存月份（如果泥愿意写12个if也行qaq）:

```cpp
string M[]={"January","February","March","April","May","June","July","August","September","October","November","December"};

//M数组不用定义大小，如果不写的话就默认你填的多少个数那么大。
```

顺便说一句：string是一个好东东qaq。

string的用法再次不讲了，详见：[String的用法](https://www.baidu.com/s?wd=C%2B%2Bstring%E7%9A%84%E7%94%A8%E6%B3%95&rsv_spt=1&rsv_iqid=0xd8fb3b2300015f3b&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&tn=baiduhome_pg&rsv_enter=1&rsv_dl=tb&rsv_sug3=20&rsv_sug1=10&rsv_sug7=100&rsv_sug2=0&inputT=5028&rsv_sug4=5028)

好了，现在上代码！其余见注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
string M[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
//M数组不用定义大小，如果不写的话就默认你填的多少个数那么大。
int main()
{
//	freopen("Codecraft III.in","r",stdin);
//	freopen("Codecraft III.out","w",stdout);	
	string a;//定义string类型的a
	cin>>a;//输入a
	int n,now;
	cin>>n;
	for(int i=0;i<12;i++)//枚举。看当前是那个月份
		if(M[i]==a) now=i;
	int ans=(now+n)%12;//注意取模，不然越界了
	cout<<M[ans];//输出
	return 0;
}
```

总的来说，这题很良心，没有坑。

求管理员通过啊，写的真么详细qwq。

---

## 作者：qwerta (赞：8)

~~啊哈又一道入门水题~~

用string读入当前月份，然后一些~~鬼畜~~操作

具体看代码吧2333
```cpp
#include<iostream>
using namespace std;
int main()
{
    string s;
    cin>>s;//读入
    int y,x;
    if(s=="January")y=1;
    if(s=="February")y=2;
    if(s=="March")y=3;
    if(s=="April")y=4;
    if(s=="May")y=5;
    if(s=="June")y=6;
    if(s=="July")y=7;
    if(s=="August")y=8;
    if(s=="September")y=9;
    if(s=="October")y=10;
    if(s=="November")y=11;
    if(s=="December")y=12;
    //
    cin>>x;
    x=x+y;
    x=x%12;
    if(x==1)cout<<"January";
    if(x==2)cout<<"February";
    if(x==3)cout<<"March";
    if(x==4)cout<<"April";
    if(x==5)cout<<"May";
    if(x==6)cout<<"June";
    if(x==7)cout<<"July";
    if(x==8)cout<<"August";
    if(x==9)cout<<"September";
    if(x==10)cout<<"October";
    if(x==11)cout<<"November";
    if(x==0)cout<<"December";
    return 0;
}
```

---

## 作者：zr太弱了 (赞：5)

本题不算特别难，题面还贴心的给出了12个月的英文（省的手打），既然给出了英文，那就用数组做喽，所以：

```cpp
string a[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};

```
### 注意：这里千万不要用0占位，否则待会更容易错！

接下来，正常输入：


```cpp
cin>>ans;
cin>>k;
```

接下来，我们需要将题目中的月份英文转化成数字，也就是在我们开好的数组中查找：

```cpp
for(long long i=0;i<=11;i++)
    {
    	if(ans==a[i])
    	{
    		sum=i;
    		break;
		}
	}
```

最后输出输入月份加上经过的月数对12取余的结果对应的月份，
即a[（输入月份+经过月份）%12]

```cpp
cout<<a[(sum+k)%12];
```

完整code   ~~我知道你们只会复制这一段~~

```cpp
#include <bitss/tdc++.h>
using namespace std;
string ans,a[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
long long k,sum;
int mian()
{    
    cin>>ans;
    cin>>k; 
    for(long long i=0;i<=11;i++)
    {
    	if(ans=a[i])
    	{
    		sum=i;
    		break;
		}
	}
	cout<<a[(sum+k)%12];
    return 0；//防伪处理过了
}
```

~~看在窝打字这么辛苦的份上~~，求管理大大通过！



---

## 作者：花千树 (赞：4)

**本道题还是~~挺水的~~**

**其实只用打个表，纪录1至12月的月份（不要告诉我你不会拼）**
#### 然后利用C++的strcmp还数进行比较，不就行了吗？
# 打表大法好！
**详细过程见代码：**
```
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char s[25][20]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"},c[25];//打表QAQ
int k;
int main(){
    cin>>c>>k;//读入
    for(int i=0;i<12;i++){
        if(!strcmp(c,s[i])){//C++库函数进行比较
            k+=i;//k加上i，找到当前字符串位于数组的哪个位置，加上这个位置
            break;
        }
    }
    cout<<s[k%12]<<endl;//直接%12输出
    return 0;//过程结束
}
```
**其实在比赛中，打表可以帮助我们解决类似的题目，所以我们不能屏蔽它，任何算法都要学习。~~（虽然打表不是一种正规的算法）~~**
### 看我打的这么累，管理员给过吧QAQ

---

## 作者：hensier (赞：1)

这道题$C++$用$string$可以轻松过，但是本蒟蒻却是用$C$过的。我们知道$strcpy$是一个很强大的函数，但是不知道在这里为什么用不起来。于是我们写了一个$check$函数（注意：$C$语言是没有$bool$这个说法的）：

```cpp
bool check(char *a,char *b)//数组在函数中可以用指针
{
    if(strlen(a)-strlen(b))return 0;//如果两个字符串的大小不相等当然就不完全相同
    for(int i=0;a[i];i++)if(a[i]-b[i])return 0;//不一样就返回0
    return 1;//否则返回1
}
```

上述的函数是代码的核心之处。

$AC$代码：

```cpp
#include<cstdio>
#include<cstring>
int k,i;
char s[50],c[12][50]={"January","February","March","April","May","June","July","August","September","October","November","December"};//这算不算打表？？？
bool check(char *a,char *b)
{
    if(strlen(a)-strlen(b))return 0;
    for(int i=0;a[i];i++)if(a[i]-b[i])return 0;
    return 1;
}
int main()
{
    scanf("%s%d",s,&k);//输入
    for(;i<12;i++)if(check(s,c[i]))break;//check函数返回1就break
    printf("%s",c[(i+k)%12]);//输出
}
```

---

## 作者：sinsop90 (赞：1)

这道题首先就是输入字符串月份,然后和每个月份的名称进行比较

最后得出是几月,加上给定的n,再取模12,得出几月

strcmp就是string compare,就是字符串比较

假设a = "abc",b = "abc"

那么strcmp(a,b)返回的值就是0
 
如果a>b比如a = "abd",b = "abc"

那么返回的就是1

a<b返回的就是-1

所以我们可以利用bool中的false和true结合这个特性来完成比较

```
#include<bits/stdc++.h>
using namespace std;
char mps[12][100] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int main(){
	int n;
	char maps[100005];
	cin>>maps>>n;
	for(int i=0;i<=11;i++){
		if(!strcmp(mps[i],maps)){//比较看看是不是一样的
			cout<<mps[(i+n)%12]<<endl;
			return 0;
		}
	}
}

```


---

## 作者：Andysun06 (赞：1)

# 第一个发题解
## 只要输入时变成数字，中间如果累加>12就-12，输出时变成字符串就可以了。
#### pascal代码：
    var a,b,n:longint;
        c,v:ansistring;
    begin
    readln(c);//输入
    if c='January' then a:=1 else//把字符串变成数字
    if c='February' then a:=2 else
    if c='March' then a:=3 else
    if c='April' then a:=4 else
    if c='May' then a:=5 else
    if c='June' then a:=6 else
    if c='July' then a:=7 else
    if c='August' then a:=8 else
    if c='September' then a:=9 else
    if c='October' then a:=10 else
    if c='November' then a:=11 else
    if c='December' then a:=12;
    readln(b);//输入过了的月份
    if b mod 12=0 then//如果过了12，24，36...就直接输出
    begin
    writeln(c);//输出
    halt;//退出程序
    end;
    n:=b+a;//没有退出就累加
    while n>12 do//如果>12就循环
     n:=n-12;//累减
    if n=1 then writeln('January') else//变成字符串输出
    if n=2 then writeln('February') else
    if n=3 then writeln('March') else
    if n=4 then writeln('April') else
    if n=5 then writeln('May') else
    if n=6 then writeln('June') else
    if n=7 then writeln('July') else
    if n=8 then writeln('August') else
    if n=9 then writeln('September') else
    if n=10 then writeln('October') else
    if n=11 then writeln('November') else
    if n=12 then writeln('December');
    end.
## 严禁抄袭！！！    


---

## 作者：呵呵侠 (赞：0)

19行代码，简单易懂

分析：
```
众所周知，一共有12个月份
所以我们先把12个月份敲进去

然后我们想，假如现在是6月，过了120个月，是几月？
不会是126月吧……
答案：还是6月
每年都有12个月份，也就是说每个月再过12个月就还是这个月
所以我们把所有的完整的12月份都忽略，月份数要mod 12

假如现在是12月（其实确实是12月），又过了1个月，是几月？
不会是13月吧……
答案：是1月
所以可以在算出了之后mod 12，但是我不是这么做的
为了防止出现13月这种东西，我把所有月份敲了2次

详见代码注释
```

```cpp
#include <iostream>
using namespace std;
string months[24]={"January","February","March","April","May","June","July","August","September","October","November","December","January","February","March","April","May","June","July","August","September","October","November","December"};//为了避免出现月份数下标大于11，我要把所有月份敲2次
int main()
{
    string a;
    cin>>a;//当前月份
    int b;
    cin>>b;//过了几个月
    b=b%12;
    for(int i=0;i<12;i++)//记住在前12个找，不要在后12个找，不然会出现“13月”这种情况
        if(a==months[i])//如果符合
        {
            a=months[i+b];//把下标增加
            break;
        }
    cout<<a;
    return 0;
}
```

好了，这篇题解就到这里了

时间：2019年12月19日 20:19:22

---

## 作者：_Qer (赞：0)

~~水题解辣~~

用**char**类型的数组做的

先开一个二维来存十二个月份的英文

然后再开一个字符串数组存输入的月份

用输入的k加上当前月份，再** mod 12 **得到最后的结果

输出那个月份的英文即可

```cpp
#include<bits/stdc++.h>
using namespace std;
char month[13][20]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};//十二个月
int n;//n即为题目中的k
char in[20];//当前月份
bool com(char a[],char b[]){//自己写的一个比较函数，也有库函数可以用
    int l=strlen(a);//字符串a的长度
    if(l!=strlen(b)){//长度不同直接返回假（false）
        return false;
    }
    for(int i=0;i<l;++i){//比较每一位
        if(a[i]!=b[i]){//如果某一位不同，直接返回假（false）
            return false;
        }
    }
    return true;
}
int main(){
    cin>>in>>n;
    for(int i=0;i<12;++i){//循环，判断当前是几月，n加上这个月份
        if(com(in,month[i])){//这里也可以直接用字符串比较库函数
            n+=i;
            break;//找到了可以直接跳出循环
        }
    }
    cout<<month[n%12];//输出是字符串，要 mod 12，一年只有12个月，超过的要到下一年
    return 0;
}
```

---

## 作者：Arghariza (赞：0)

$题目真良心，直接给了月份名字，我也懒得打了，这题就用数组吧$

首先我们定义一个数组month表示月份：

```
string month[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
```

然后我们定义n（输入字符串）, m（m表示月份n排第几）, k（输入跳k月）：

```
int k, m;
string n;
```

接着我们输入：

```
cin >> n >> k;
```

然后我们循环全部月份，如果有月份名字等于n，则```m = i - 1```并且跳出循环：

```
for (int i = 1; i <= 12; i++) { //枚举月份
    if(month[i - 1] == n) {		//如果找到
        m = i - 1;				//得出m值
        break;					//跳出循环
    }
}
```

最后输出（记得取模）：

```
cout << month[(m + k) % 12];
```

所以整个代码就出来了：

```
#include <iostream>
using namespace std;

int k, m;
string n, month[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int main() {
    cin >> n >> k;
    for (int i = 1; i <= 12; i++) {
        if(month[i - 1] == n) {
            m = i - 1;
            break;
        }
    }
    cout << month[(m + k) % 12];
    return 0;
}
```

---

## 作者：monkeywoora (赞：0)

Python3派悄悄地来一发O(1)的题解。。
```python
# -*- coding: utf-8 -*-
#!/usr/bin/env python
a=input()
b={"January":1,"February":2,"March":3,"April":4,"May":5,"June":6,"July":7,"August":8,"September":9,"October":10,"November":11,"December":12}
#取元素。。
c={1:"January",2:"February",3:"March",4:"April",5:"May",6:"June",7:"July",8:"August",9:"September",10:"October",11:"November",0:"December"}
#取月份。。（注意哦，可能有错。。）
d=int(int(input())+int(b[a]))
#整合计算。。。
print(c[int(d%12)])
#输出！
#为了维护洛谷的环境，请勿盲目抄题解，谢谢！（反正抄了也无法AC，呵呵呵。）
```

---

