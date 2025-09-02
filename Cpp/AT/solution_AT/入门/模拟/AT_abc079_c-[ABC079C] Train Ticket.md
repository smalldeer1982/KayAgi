# [ABC079C] Train Ticket

## 题目描述

坐在车站候车室的 joisino 姐姐正在看着她的车票。

车票上依次写着 $4$ 个 $0$ 到 $9$ 之间的整数 $A$、$B$、$C$、$D$，作为整理编号。

请在 $A$、$B$、$C$、$D$ 之间依次插入 $op1$、$op2$、$op3$，每个 $op$ 可以是 `+` 或 `-`，使得 $A\ op1\ B\ op2\ C\ op3\ D = 7$。

请构造出满足条件的表达式。

另外，输入保证一定存在解。如果有多个答案，输出任意一个即可。

## 说明/提示

## 限制

- $0 \leq A,B,C,D \leq 9$
- 输入均为整数
- 输入保证一定存在解

## 样例解释 1

$1+2+2+2=7$ 满足条件。

## 样例解释 2

除此之外，$0-2+9-0=7$ 也满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1222```

### 输出

```
1+2+2+2=7```

## 样例 #2

### 输入

```
0290```

### 输出

```
0-2+9+0=7```

## 样例 #3

### 输入

```
3242```

### 输出

```
3+2+4-2=7```

# 题解

## 作者：TRZ_2007 (赞：2)

这不就是~~著名的~~算法$\color{RED}\text{模拟}$吗？  
这题有两种算法来过掉TA  
- 1：模拟  
定义三个字符变量$i,j,k$，让他们从$+$跑到$-$然后再依次判断即可。  
$Code$
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	char a1,b1,c1,d1;//注意数字是连着输进来的，得用字符来存
	int ans,a,b,c,d;
	cin>>a1>>b1>>c1>>d1;
	a=a1-'0';b=b1-'0';c=c1-'0';d=d1-'0';
	for(char i='+';i<='-';i++)
		for(char j='+';j<='-';j++)
			for(char k='+';k<='-';k++)
			{
				ans=a;//刚开始的结果一定是a
				if(i=='+') ans+=b;//如果符号是加，就加上去
				else if(i=='-') ans-=b;//否则如果是减，就减下来
				if(j=='+') ans+=c;
				else if(j=='-') ans-=c;
				if(k=='+') ans+=d;
				else if(k=='-') ans-=d;
				if(ans==7)//找到了
				{
					cout<<a<<i<<b<<j<<c<<k<<d<<"="<<ans<<"\n";
					return 0;
				}
			}
}
```
- 2：暴力  
反正只有$2^3$种可能，我们也可以一 一判断即可  
$Code$
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    char a1,b1,c1,d1;
    cin>>a1>>b1>>c1>>d1;
    int a,b,c,d,ans;
    a=a1-'0';b=b1-'0';c=c1-'0';d=d1-'0';
    if(a+b+c+d==7)
    {
        cout<<a<<"+"<<b<<"+"<<c<<"+"<<d<<"=7\n";
        exit(0);
    }
    if(a+b+c-d==7)
    {
        cout<<a<<"-"<<b<<"+"<<c<<"-"<<d<<"=7\n";
        exit(0);
    }
    if(a+b-c+d==7)
    {
        cout<<a<<"+"<<b<<"+"<<c<<"-"<<d<<"=7\n";
        exit(0);
    }
    if(a-b+c+d==7)
    {
        cout<<a<<"-"<<b<<"+"<<c<<"+"<<d<<"=7\n";
        exit(0);
    }
    if(a-b+c-d==7)
    {
        cout<<a<<"-"<<b<<"+"<<c<<"-"<<d<<"=7\n";
        exit(0);
    }
    if(a+b-c-d==7)
    {
        cout<<a<<"+"<<b<<"-"<<c<<"-"<<d<<"=7\n";
        exit(0);
    }
    if(a-b-c-d==7)
    {
        cout<<a<<"-"<<b<<"-"<<c<<"-"<<d<<"=7\n";
        exit(0);
    }
}
```

---

## 作者：Kiel (赞：2)

看到题意，非常简单，只要硬生生的模拟和判断即可。

上代码：

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    char s[10];//字符串
    cin>>s;
    int a,b,c,d;
    a=s[0]-'0';//分离
    b=s[1]-'0';
    c=s[2]-'0';
    d=s[3]-'0';
    for(int i=43;i<=45;i+=2){//本来准备用‘+’，‘-’的，后来想了想还是没用
        for(int j=43;j<=45;j+=2){
            for(int k=43;k<=45;k+=2){
                int ans=a;
                if(i==43){//厚颜无耻的判断
                    ans+=b;
                }
                else{
                    ans-=b;
                }
                if(j==43){
                    ans+=c;
                }
                else{
                    ans-=c;
                }
                if(k==43){
                    ans+=d;
                }
                else{
                    ans-=d;
                }
                if(ans==7){
                    cout<<a<<char(i)<<b<<char(j)<<c<<char(k)<<d<<"=7"<<endl;//只要输出一种
                    return 0;
                }
            }
        }
    }
    //cout<<int('-');
    return 0;
}
```

---

## 作者：Ciyang (赞：1)

### 这个题比较水,做法暴力枚举三个符号,那么就三个循环嵌套就够了
### 为了写起来方便,看起来比较美观~~不暴力~~,我用了几个小技巧
#### 读入使用char类型,这样限定了一个字符,读入之后减去'0'就行了
#### 为了枚举判断方便,循环变量为0代表加号,为1代表减号
#### 三个循环,每个循环中都记录一次当前的和,并用记录符号
#### 第三个循环中,如果运算后为7就输出退出
#### ~~自我感觉还可以~~
```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
char a[4], f[3];
int  t[3];
int  main() {
	for(int i= 0; i < 4; i++) cin >> a[i], a[i]-= '0';
    //使用char类型输入,只读1位
	for(int i= 0; i < 2; i++) {
		 if(!i) t[0]= a[0] + a[1], f[0]= '+';
		 if(i) t[0]= a[0] - a[1], f[0]= '-';
         //记录前两个数的运算,并记录第一个符号
		 for(int j= 0; j < 2; j++) {
			 if(!j) t[1]= t[0] + a[2], f[1]= '+';
			 if(j) t[1]= t[0] - a[2], f[1]= '-';
             //记录前三个数的运算,并记录第二个符号
			 for(int q= 0; q < 2; q++) {
				 if(!q) t[2]= t[1] + a[3], f[2]= '+';
				 if(q) t[2]= t[1] - a[3], f[2]= '-';
                 //记录四个数的运算,并记录第三个符号
				 if(t[2] == 7) {
					 printf("%d%c%d%c%d%c%d=7\n", a[0], f[0], a[1], f[1], a[2], f[2], a[3]);
                     //输出数字和符号
					 return 0;
				 }
			 }
		 }
	}
	return 0;
}
```

---

## 作者：空城旧梦— (赞：1)

## 题解怎么能少了pascal！！
首先，这道题我的方法可能不好，大佬勿喷

也没啥好说的，就是枚举各种情况，因为只有三个运算符号所以总方案数就只有2×2×2=8种，所以可以暴力打表

直接上代码
```pascal
var  a,b,c,d:longint;
     s:string;
begin
  readln(s);
  a:=ord(s[1])-ord('0');
  b:=ord(s[2])-ord('0');
  c:=ord(s[3])-ord('0');
  d:=ord(s[4])-ord('0');//字符串预处理
  if  a+b+c+d=7  then
    begin  writeln(a,'+',b,'+',c,'+',d,'=7');  exit;  end;//只要找到一种就可以结束输出，下同
  if  a+b+c-d=7  then
    begin  writeln(a,'+',b,'+',c,'-',d,'=7');  exit;  end;
  if  a+b-c+d=7  then
    begin  writeln(a,'+',b,'-',c,'+',d,'=7');  exit;  end;
  if  a-b+c+d=7  then
    begin  writeln(a,'-',b,'+',c,'+',d,'=7');  exit;  end;
  if  a-b-c+d=7  then
    begin  writeln(a,'-',b,'-',c,'+',d,'=7');  exit;  end;
  if  a-b+c-d=7  then
    begin  writeln(a,'-',b,'+',c,'-',d,'=7');  exit;  end;
  if  a+b-c-d=7  then
    begin  writeln(a,'+',b,'-',c,'-',d,'=7');  exit;  end;
  if  a-b-c-d=7  then
    begin  writeln(a,'-',b,'-',c,'-',d,'=7');  exit;  end;
end.

```

---

## 作者：stry (赞：0)

这道题很水，直接进行打表，最多也才8-1种可能，
八种可能分别是：
|1  |a+b+c+d  |
| -----------: | -----------: |
|2  |a+b+c-d  |
|3  |a+b-c+d  |
|4  |a-b+c+d  |
|5  |a-b+c-d  |
|6  |a+b-c-d  |
|7  |a-b-c-d  |
## 还有一点需注意：岛国题需换行
# 我们直接切入正题，程序如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
char a1,b1,c1,d1;
cin>>a1>>b1>>c1>>d1;
int a,b,c,d,ans;
a=a1-'0';b=b1-'0';c=c1-'0';d=d1-'0';
if(a+b+c+d==7)
{
    cout<<a<<"+"<<b<<"+"<<c<<"+"<<d<<"=7\n";
    exit(0);
}
if(a+b+c-d==7)
{
    cout<<a<<"-"<<b<<"+"<<c<<"-"<<d<<"=7\n";
    exit(0);
}
if(a+b-c+d==7)
{
    cout<<a<<"+"<<b<<"+"<<c<<"-"<<d<<"=7\n";
    exit(0);
}
if(a-b+c+d==7)
{
    cout<<a<<"-"<<b<<"+"<<c<<"+"<<d<<"=7\n";
    exit(0);
}
if(a-b+c-d==7)
{
    cout<<a<<"-"<<b<<"+"<<c<<"-"<<d<<"=7\n";
    exit(0);
}
if(a+b-c-d==7)
{
    cout<<a<<"+"<<b<<"-"<<c<<"-"<<d<<"=7\n";
    exit(0);
}
if(a-b-c-d==7)
{
    cout<<a<<"-"<<b<<"-"<<c<<"-"<<d<<"=7\n";
    exit(0);
}
}
```


---

## 作者：CZQ_King (赞：0)

# ~~这题真水~~

------------

做法：
- 如果要实现$0='+',1='-'$，可以用公式$char(a*2+43)$解决。（$a$为$0$或$1$）

- 分解一个四位数字可以用下面四个公式：
 - 千位：$q=int(l/1000)$
 - 百位：$b=int(l/100-q*10)$
 - 十位：$s=int(l/10-q*100-b*10)$
 - 个位：$g=l\mod 10$
 
- ### 所以可以先分解成四个数字，然后~~暴力~~判断$+-$符号，找到正确的就输出并结束

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,b,c,d,v;
int p(int a,int b,int c){//plus的简写（其实还有减法）
	return (char(b)=='+')?(a+c):(a-c);
	/*
	如果b是43(+)，返回a+c 
	否则返回a-c
	*/
}
int main(){
	cin>>v;
	         a=v/1000;//分解千位
	     b=v/100-a*10;//分解百位
	c=v/10-a*100-b*10;//分解十位
	           d=v%10;//分解个位
    //                ↑强迫症↑
	for(int i=0;i<2;i++){//第一个符号 
		for(int j=0;j<2;j++){//第二个 
			for(int k=0;k<2;k++){//还有第三个 
				if(p(p(p(a,i*2+43,b),j*2+43,c),k*2+43,d)==7){//如果式子计算出7，利用了ASCII码 
					cout<<a;<<char(i*2+43)<<b<<char(j*2+43)<<c<<char(k*2+43)<<d<<"=7"<<endl;//输出答案 
					return 0;//只需要一种答案，所以要结束
				}
			}
		}
	}
	return 0;//好像是没用的
}
```

---

