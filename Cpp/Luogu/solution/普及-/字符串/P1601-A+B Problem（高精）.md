# A+B Problem（高精）

## 题目描述

高精度加法，相当于 a+b problem，**不用考虑负数**。

## 说明/提示

$20\%$ 的测试数据，$0\le a,b \le10^9$；

$40\%$ 的测试数据，$0\le a,b \le10^{18}$。

## 样例 #1

### 输入

```
1
1```

### 输出

```
2```

## 样例 #2

### 输入

```
1001
9099```

### 输出

```
10100```

# 题解

## 作者：FlyingAnt (赞：968)

比较简单的高精度。

高精度。顾名思义，就是在很大的位数情况下进行运算。（炸int）

其基本思想就是用数组进行模拟加法。

模拟近位。

最后遍历数组输出。

附上高精加，减，乘代码。

减，乘被注释。

自行取用修改




```cpp
#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
using namespace std;
//compare比较函数：相等返回0，大于返回1，小于返回-1
int compare(string str1,string str2)
{
    if(str1.length()>str2.length()) return 1;
    else if(str1.length()<str2.length())  return -1;
    else return str1.compare(str2);
}
//高精度加法
//只能是两个正数相加
string add(string str1,string str2)//高精度加法
{
    string str;
    int len1=str1.length();
    int len2=str2.length();
    //前面补0，弄成长度相同
    if(len1<len2)
    {
        for(int i=1;i<=len2-len1;i++)
           str1="0"+str1;
    }
    else
    {
        for(int i=1;i<=len1-len2;i++)
           str2="0"+str2;
    }
    len1=str1.length();
    int cf=0;
    int temp;
    for(int i=len1-1;i>=0;i--)
    {
        temp=str1[i]-'0'+str2[i]-'0'+cf;
        cf=temp/10;
        temp%=10;
        str=char(temp+'0')+str;
    }
    if(cf!=0)  str=char(cf+'0')+str;
    return str;
}
//高精度减法
//只能是两个正数相减，而且要大减小
/*string sub(string str1,string str2)//高精度减法
{
    string str;
    int tmp=str1.length()-str2.length();
    int cf=0;
    for(int i=str2.length()-1;i>=0;i--)
    {
        if(str1[tmp+i]<str2[i]+cf)
        {
            str=char(str1[tmp+i]-str2[i]-cf+'0'+10)+str;
            cf=1;
        }
        else
        {
            str=char(str1[tmp+i]-str2[i]-cf+'0')+str;
            cf=0;
        }
    }
    for(int i=tmp-1;i>=0;i--)
    {
        if(str1[i]-cf>='0')
        {
            str=char(str1[i]-cf)+str;
            cf=0;
        }
        else
        {
            str=char(str1[i]-cf+10)+str;
            cf=1;
        }
    }
    str.erase(0,str.find_first_not_of('0'));//去除结果中多余的前导0
    return str;
}
//高精度乘法
//只能是两个正数相乘
string mul(string str1,string str2)
{
    string str;
    int len1=str1.length();
    int len2=str2.length();
    string tempstr;
    for(int i=len2-1;i>=0;i--)
    {
        tempstr="";
        int temp=str2[i]-'0';
        int t=0;
        int cf=0;
        if(temp!=0)
        {
            for(int j=1;j<=len2-1-i;j++)
              tempstr+="0";
            for(int j=len1-1;j>=0;j--)
            {
                t=(temp*(str1[j]-'0')+cf)%10;
                cf=(temp*(str1[j]-'0')+cf)/10;
                tempstr=char(t+'0')+tempstr;
            }
            if(cf!=0) tempstr=char(cf+'0')+tempstr;
        }
        str=add(str,tempstr);
    }
    str.erase(0,str.find_first_not_of('0'));
    return str;
}
//高精度除法
//两个正数相除，商为quotient,余数为residue
//需要高精度减法和乘法
void div(string str1,string str2,string &quotient,string &residue)
{
    quotient=residue="";//清空
    if(str2=="0")//判断除数是否为0
    {
        quotient=residue="ERROR";
        return;
    }
    if(str1=="0")//判断被除数是否为0
    {
        quotient=residue="0";
        return;
    }
    int res=compare(str1,str2);
    if(res<0)
    {
        quotient="0";
        residue=str1;
        return;
    }
    else if(res==0)
    {
        quotient="1";
        residue="0";
        return;
    }
    else
    {
        int len1=str1.length();
        int len2=str2.length();
        string tempstr;
        tempstr.append(str1,0,len2-1);
        for(int i=len2-1;i<len1;i++)
        {
            tempstr=tempstr+str1[i];
            tempstr.erase(0,tempstr.find_first_not_of('0'));
            if(tempstr.empty())
              tempstr="0";
            for(char ch='9';ch>='0';ch--)//试商
            {
                string str,tmp;
                str=str+ch;
                tmp=mul(str2,str);
                if(compare(tmp,tempstr)<=0)//试商成功
                {
                    quotient=quotient+ch;
                    tempstr=sub(tempstr,tmp);
                    break;
                }
            }
        }
        residue=tempstr;
    }
    quotient.erase(0,quotient.find_first_not_of('0'));
    if(quotient.empty()) quotient="0";
}
```
\*/

```cpp
int main()
{
     string str1,str2;
     //string str3,str4;
     cin>>str1>>str2;
     //while()
     //{
         cout<<add(str1,str2)<<endl;
         //cout<<sub(str1,str2)<<endl;
         //cout<<mul(str1,str2)<<endl;
         //div(str1,str2,str3,str4);
         //cout<<str3<<"  "<<str4<<endl;
     //}
     return 0;
}

```

---

## 作者：李春进的小号 (赞：701)

# 发现没有PYTHON题解！！！

# 发现没有PYTHON题解！！！

# 发现没有PYTHON题解！！！

重要的事情说三遍，作为****蒟蒻****的我来给各位神犇献献丑（主要是为了占上PYTHON题解）



------------



我的题解不是最标准的Python a+b做法，但是是其他语言的初学者都容易理解的方法（~~滑稽~~）

```python
a=input()
b=input()
a=int(a)
b=int(b)
print(a+b)

```
~~好了，这题就这么简单~~   
吐槽一句：高精度的题目没Python题解真是有失我~~huaji~~帝国的风采


---

## 作者：ArachnidaKing (赞：349)

当初初学高精加看着题解大佬各种秀，一会char*，一会又加又减的，当初还是小垃圾的我看得一脸懵（现在已经是大垃圾了），这种难度的题本来就是给层次不高的新手做的嘛。我发誓，这！是！目！前！最！好！理！解！的！题！解！！！
没有秀，没有高端操作，没有char飞来飞去各种小变量加减特判，只为你我都能看懂！话不多说，一切讲解都在注释里->
```cpp
#include<bits/stdc++.h>
#define tin int//个人习惯防手滑 
#define itn int
#define tni int
#define nit int
#define nti int
#define pritnf printf
#define scnaf scanf
#define ll long long
using namespace std;
#define maxa 504

itn i,sa,sb,m;//sa是a的长度，我们（划掉）sb是b的长度，m是a与b中的较大长度 
short x[maxa]={0},y[maxa]={0};//强迫症省空间，开short。x为较长加数，y为剩下那个。x[1]、y[1]为个位，x[2]、y[2]为十位，以此类推。 
string a,b;

itn main()
{
	cin>>a>>b;//cin是string最好的搭档
	sa=a.size();//为以后方便取a的长度
	sb=b.size();//为以后方便取b的长度
	m=max(sa,sb);//为以后方便取a、b较长长度
	//
	if(sa>sb)//如果a是较长加数 
	{
		for(i=1;i<=sa;++i)//把a遍历一遍 
		{
			x[i]=a[sa-i]-48;//把a赋给x 
		}
		for(i=1;i<=sb;++i)//把较短加数一位一位加上 
		{
			x[i]+=b[sb-i]-48;//a一位一位加上b 
		}
	}
	else//上面反过来 
	{
		for(i=1;i<=sb;++i)
		{
			x[i]=b[sb-i]-48;
		}
		for(i=1;i<=sa;++i) 
		{
			x[i]+=a[sa-i]-48;
		}
	}
	//
	for(i=1;i<=m;++i)//十进制处理 
	{
		if(x[i]>=10)//如果需要进位 
		{
			x[i]-=10;//这一位留个位 
			++x[i+1];//下一位进一 
		}
	}
	//聪明的孩子会发现此时如999+1情况比最高位高一位的地方有个1输出时将被忽略 
	if(x[m+1]>0)//最高位进位特判 
	{
		++m;//多输出一位，这样输出时就把最高处孤独的1考虑到了 
	}
	//
	for(i=m;i>=1;--i)//反着输出，注意现在的m有可能已经加1,999+1不会输出000。 
	{
		cout<<x[i];//一位一位
	}
	return 0； 
}//本代码已进行防抄袭处理·^v·^ 
```
我知道本题题解已经很多了，但这篇毕竟思路写法与前面的大佬都不一样，求过啊QWQ

---

## 作者：lrx88 (赞：139)

在结构体里定义高精度数据 然后把它当成一般的数处理，理解起来十分容易

这样就可以直接熟练运用高精度数据，

这是个模板

希望大家可以背下来


```cpp
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
const int N = 1005;
struct bign
{
    int len,s[N];
    bign()  {  memset(s,0,sizeof(s));  len=1;  }
    bign(int num)  {  *this=num; }
    bign(char *num) { *this=num; }
    bign operator =(int num)
    {
        char c[N];
        sprintf(c,"%d",num);
        *this=c;
        return *this;
    }
    bign operator =(const char *num)
    {
        len=strlen(num);
        for (int i=0;i<len;i++) s[i]=num[len-1-i]-'0';
        return *this;
    }
    string str()
    {
        string res="";
        for (int i=0;i<len;i++) res=(char)(s[i]+'0')+res;
        return res;
    }
    void clean()
    {
        while (len>1&&!s[len-1]) len--;
    }
    bign operator +(const bign &b)
    {
        bign c;    
        c.len=0;
        for (int i=0,g=0;g||i<len||i<b.len;i++)
        {
            int x=g;
            if (i<len) x+=s[i];
            if (i<b.len) x+=b.s[i];
            c.s[c.len++]=x%10;
            g=x/10;
        }
        return c;
    }
    bign operator -(const bign &b)
    {
        bign c;
        c.len=0;
        int x;     
        for (int i=0,g=0;i<len;i++)
        {
            x=s[i]-g;
            if (i<b.len) x-=b.s[i];
            if (x>=0) g=0;
            else{          
                x+=10;
                g=1;
            };
            c.s[c.len++]=x;
        }
        c.clean();
        return c;
    }
    bign operator *(const bign &b)
    {
        bign c;
        c.len=len+b.len;
        for (int i=0;i<len;i++) for (int j=0;j<b.len;j++) c.s[i+j]+=s[i]*b.s[j];
        for (int i=0;i<c.len-1;i++) { c.s[i+1]+=c.s[i]/10; c.s[i]%=10; }
        c.clean();
        return c;  
    }
    bool operator <(const bign &b)
    {
        if (len!=b.len) return len<b.len;
        for (int i=len-1;i>=0;i--)
             if (s[i]!=b.s[i]) return s[i]<b.s[i];
        return false;
    }
    bign operator +=(const bign &b)
    {
        *this=*this+b;
        return *this;
    }
    bign operator -=(const bign &b)
    {
        *this=*this-b;
        return *this;
    }  
};
istream& operator >>(istream &in,bign &x)
{
  string s;
  in>>s;
  x=s.c_str();
  return in;
}
ostream& operator <<(ostream &out,bign &x)
{
    out<<x.str();
    return out;
}
int main(){
    bign a,b,c;
    ios::sync_with_stdio(false);
    cin>>a>>b;
//    cout<<a<<endl;
//    cout<<b<<endl;
    c=a+b;
    cout<<c<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：131)

~~此题解只面对与刚刚学算法的童鞋们~~

- 什么情况下要**使用高精度**？

当两个数超过$long  long$的大小并且要对这两个大数进行运算的时候。

- 既然数这么大，我们用什么存放呢？

用**字符串**存放。

- 怎么运算呢？

~~小学学加法的时候~~，我们是从最低位开始计算，两两相加，逢十进一。

我们也可以用计算机模拟这一过程。

具体代码：
```cpp
for(j=1; j<=max(a[0],b[0])+1; j++) {
	c[j]=a[j]+b[j];
	if(c[j]>=10) {
		c[j]%=10;
		a[j+1]++;
	}
}
```

- 既然要进行运算，我们总得知道字符串的长度吧？怎么获取呢？

用$strlen$函数。

```cpp
a[0]=strlen(s);
b[0]=strlen(ss);
```

- 要运算，怎么知道某一位的具体数值是几呢？

这个跟$ascll$码有关了。

一个字符数字的$ascll$码－$48$（也就是$0$的$ascll$码）就是那个数字的$ascll$码。

转化过程：

```cpp
for(int i=1; i<=a[0]; i++) a[i]=s[a[0]-i]-'0';
for(int i=1; i<=b[0]; i++) b[i]=ss[b[0]-i]-'0';
```

☆ 注意：

# 一定要考虑进位！！

具体的说，就是最高位相加时可能会有进位，需特判。



如果$dalao$们看前面的不顺眼觉得蔡那看看这个：

读入第一行字符串$A$与第二行字符串$B$，

将两串字符串的每个字符转成数字存储在数组中，字符转数字的方式是：**ch-’0’**


我们将个位存在$a[1]$，高位存在$a[l]$，$l$是数字位数，也即字符串长度。

字符串$B$也用一个数组$b$来记录。

高精度加法就是模拟加法的过程，我们要做的就是让a和b的每一位相加，并判断任意一位数是否大于等于$10$，即应进位的问题。

处理完进位同时也要考虑最终和的位数（长度）是否有变化。
最终逐位输出达成输出大数的效果。

说了这么多，上一下$AC$代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001],b[1000001],c[1000001],j;
bool x=false;
char s[1000001],ss[1000001];
int main() {

	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));//初始化
	scanf("%s%s",s,ss);//读入两个数
	a[0]=strlen(s);
	b[0]=strlen(ss);//获取长度
	for(int i=1; i<=a[0]; i++) a[i]=s[a[0]-i]-'0';
	for(int i=1; i<=b[0]; i++) b[i]=ss[b[0]-i]-'0';//转化为数字
	for(j=1; j<=max(a[0],b[0])+1; j++) {
		c[j]=a[j]+b[j];
		if(c[j]>=10) {
			c[j]%=10;
			a[j+1]++;
		}
	}//模拟加法
	c[0]=j;
	if(c[j+1]>0) c[0]++;//特判进位
	for(int i=c[0]; i>=1; i--) {//输出（删除前导零）
		if(x==false&&c[i]==0) continue;
		x=true;
		cout<<c[i];
	}
	if(x==false) cout<<0;//一重保险
	printf("\n");//二重保险
	return 0;//三重保险
}
```



在以后的学习中，高精度会成为一个很重（ke）要（pa）的算法，$Ta$会成为一种工具。

所以，从现在做起扒^-^

---

## 作者：xfl03 (赞：118)

嘤嘤嘤 看到有Python的题解了  
Java也想水一发QAQ  
都是自带高精的语言啦~

```java
import java.util.Scanner;
public class Main{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        System.out.print(sc.nextBigInteger().add(sc.nextBigInteger()));
    }
}
```

---

## 作者：Valhalla_Is_Calling (赞：97)

## 一直非常喜欢这道题，今天有机会来写一篇题解

### 题目中最有价值的信息莫过于数据范围在10^500，显然是要用高精度计算的。
于是我在知识的海洋中找了又找，发现没有任何数据类型能承受10^500，看来只能用字符串来储存了。

```cpp
char ab[100001],bc[100001];//定义字符串
```
输入后就要看是要用哪种运算方式。

虽然字符串里边全是数字，但我个人认为电脑不支持直接相加QAQ，所以只能用竖式计算（模拟）

### 哦对了，竖式计算之前要先让这些数字摆脱字符的束缚

```cpp
x=strlen(ab);//获取每个字符串的长度
y=strlen(bc);
for(i=0;i<x;i++)
	a[i]=ab[x-i-1]-'0';//让可怜的数字逃出魔掌
for(i=0;i<y;i++)
	b[i]=bc[y-i-1]-'0';
```

一般情况下，人们列竖式都会把比较长的数字放在上面

```cpp
maxn=max(x,y);
```
然后就进入了振奋人心的竖式计算环节，主要是解决进位问题

```cpp
a[i]=a[i]+b[i]+jw;
```
竖式计算更新每个数字的值，在这里a数组充当的角色是最终结果

```cpp
jw=a[i]/10;
```
由于直接计算会出现11,12,13等情况，所以a[i]%10就是下一位计算的进位值

```cpp
a[i]%=10;
```
进位结束后要记得将每一位去掉进位值

总结一下，整个竖式计算的部分就是这样写的：
```cpp
for(i=0;i<maxn;i++)
{
	a[i]=a[i]+b[i]+jw;
	jw=a[i]/10;
	a[i]%=10;
}
```
竖式计算解决完后，你长舒了一口气，然后又掉进了另一个坑里。

如果你是“抄人”，那么问你一个简单而有趣的问题，99+1怎么办？

你的计算机会亲切的输出“00”,99+1=0(skr)

于是解决下一个问题------句首进位

```cpp
if(jw==1) cout<<jw;
```
在竖式运算结束后，如果变量jw还有值，就把它输出

最终的输出部分:

```cpp
for(i=maxn-1;i>=0;i--)
{
	cout<<a[i];
}
```
这道题就讲到这里，喜欢的就进入我的博客吧！

https://wangshiyao.blog.luogu.org/

附件：本题答案

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
int i,j; 
char ab[100001],bc[100001];
int a[100001],b[100001];
int jw;
int maxn,maxj;
int main( )
{
	cin>>ab>>bc;
	x=strlen(ab);
	y=strlen(bc);
	for(i=0;i<x;i++)
		a[i]=ab[x-i-1]-'0';
	for(i=0;i<y;i++)
		b[i]=bc[y-i-1]-'0';
	maxn=max(x,y);
	for(i=0;i<maxn;i++)
	{
		a[i]=a[i]+b[i]+jw;
		jw=a[i]/10;
		a[i]%=10;
	}
	if(jw==1) cout<<jw;
	for(i=maxn-1;i>=0;i--)
	{
		cout<<a[i];
	}
	return 0;
}
```
## 学习不易，请勿抄袭



---

## 作者：fzj2007 (赞：63)

## 有没有人写**位压**？这不是一个模板题吗？？？

先推销一下blog         
[here](https://www.luogu.com.cn/blog/fzj2007/)

现在，我讲一下位压存储

这个东西很（du）~~简~~（liu）~~单~~

有的时候，数字会大到连long long都不能承受的程度。这时，我们可以自己模拟大数的各种运算。
所谓压位存储，就是在高精度数内部采用10000进制（即每四位放到一个数中）进行存储。它与10进制（即一个数位对应一个数）相比速度要快一些。
高精度数内部也可以采用100000000进制，但是这样就不容易计算乘除法了。

### **(1) 定义**
编程时这样做——假设hp是高精度类型。

```cpp
const int MAX=1001;
struct hp{
    int num[MAX];
    
    hp&operator=(const char*);
    hp&operator=(int);
    hp();
    hp(int);
    //一下运算符根据需要定义哈
    bool operator>(const hp&)const;
    bool operator<(const hp&)const;
    bool operator<=(const hp&)const;
    bool operator>=(const hp&)const;
    bool operator!=(const hp&)const;
    bool operator==(const hp&)const;

    hp operator+(const hp&)const;
    hp operator-(const hp&)const;
    hp operator*(const hp&)const;
    hp operator/(const hp&)const;
    hp operator%(const hp&)const;
    
    hp&operator+=(const hp&);
    hp&operator-=(const hp&);
    hp&operator*=(const hp&);
    hp&operator/=(const hp&);
    hp&operator%=(const hp&);
};
```
**### (2) 赋值和初始化**
```
// num[0]用来保存数字位数。利用10000进制可以节省空间和时间。
hp&hp::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;// 10000进制，4个数字才算1位。
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

hp&hp::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
hp::hp(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
hp::hp(int n){
	*this=n;
}// 目的：支持“hp a=1;”之类的代码。
```
### **(3) 比较运算符**

小学时候学过怎么比较两个数的大小吧？~~现在，小学知识却从未过时……~~

```
// 如果位数不等，大小是可以明显看出来的。如果位数相等，就需要逐位比较。
bool hp::operator > (const hp &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
```
```
bool hp::operator<(const hp &b)const{return b>*this;}
bool hp::operator<=(const hp &b)const{return !(*this>b);}
bool hp::operator>=(const hp &b)const{return !(b>*this);}
bool hp::operator!=(const hp &b)const{return (b>*this)||(*this>b);}
bool hp::operator==(const hp &b)const{return !(b>*this)&&!(*this>b);}
```


### **(4) 四则运算**

如果没学过竖式，或者忘了怎么用竖式算数，你就很悲剧了……

#### 1.   加法和减法
```
//加法 
hp hp::operator+(const hp&b)const{
    hp c;
    c.num[0]=max(num[0],b.num[0]);
    for(int i=1;i<=c.num[0];i++){
        c.num[i]+=num[i]+b.num[i];
        if(c.num[i]>=10000){// 进位
            c.num[i]-=10000;
            c.num[i+1]++;
        }
    }
    if(c.num[c.num[0]+1]>0) c.num[0]++;// 9999+1，计算完成后多了一位
    return c;
}
//减法 
hp hp::operator-(const hp&b)const{
   hp c;
   c.num[0]=num[0];
   for (int i=1;i<=c.num[0];i++){
       c.num[i]+=num[i]-b.num[i];
       if(c.num[i]<0){  // 退位
            c.num[i]+=10000;
            c.num[i+1]--;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;// 100000000-99999999
    return c;
}
//顺便声明 
hp&hp::operator+=(const hp &b){return *this=*this+b;}
hp&hp::operator-=(const hp &b){return *this=*this-b;}
```
#### 2. 乘法
```
//乘法 
hp hp::operator*(const hp&b)const{
    hp c;
    c.num[0]=num[0]+b.num[0]+1;
    for(int i=1;i<=num[0];i++){
        for(int j=1;j<=b.num[0];j++){
            c.num[i+j-1]+=num[i]*b.num[j];            // 和小学竖式的算法一模一样
            c.num[i+j]+=c.num[i+j-1]/10000;            // 进位
            c.num[i+j-1]%=10000;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999*0
    return c;
}
hp&hp::operator*=(const hp &b){return *this=*this*b;}
//同上 
```

#### 3. 二分优化的除法&&取余运算
使用二分优化，速度更快！
```
hp hp::operator/(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return c;            
}
hp hp::operator%(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return d;            
}
hp&hp::operator/=(const hp &b){return *this=*this/b;}
hp&hp::operator%=(const hp &b){return *this=*this%b;}
```


------------
# 这里是重点！认真听讲！~~（敲黑板）~~
## **(5) 输入/输出**
#### 输入，输出！
### 输入，输出！！
## 输入，输出！！！
~~重要的事情说三遍~~

```
ostream&operator<<(ostream &o,hp &n){
    o<<n.num[n.num[0]];
    for(int i=n.num[0]-1;i>=1;i--){
        o.width(4);
        o.fill('0');
        o<<n.num[i];
    }
    return o;
}
istream & operator>>(istream &in, hp &n){
    char s[MAX];
    in>>s;
    n=s;
    return in;
}
```

~~自己理解去（逃）（略有感悟）~~



------------


------------


------------
长长的代码与讲解分界线。。

下面上代码
```
#include<bits/stdc++.h>
using namespace std;
const int MAX=1001;
struct hp{
    int num[MAX];
    
    hp&operator=(const char*);
    hp&operator=(int);
    hp();
    hp(int);
    
    bool operator>(const hp&)const;
    bool operator<(const hp&)const;
    bool operator<=(const hp&)const;
    bool operator>=(const hp&)const;
    bool operator!=(const hp&)const;
    bool operator==(const hp&)const;

    hp operator+(const hp&)const;
    hp operator-(const hp&)const;
    hp operator*(const hp&)const;
    hp operator/(const hp&)const;
    hp operator%(const hp&)const;
    
    hp&operator+=(const hp&);
    hp&operator-=(const hp&);
    hp&operator*=(const hp&);
    hp&operator/=(const hp&);
    hp&operator%=(const hp&);
};
// num[0]用来保存数字位数。利用10000进制可以节省空间和时间。
hp&hp::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;// 10000进制，4个数字才算1位。
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

hp&hp::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
hp::hp(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
hp::hp(int n){
	*this=n;
}// 目的：支持“hp a=1;”之类的代码。

// 如果位数不等，大小是可以明显看出来的。如果位数相等，就需要逐位比较。
bool hp::operator > (const hp &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
bool hp::operator<(const hp &b)const{return b>*this;}
bool hp::operator<=(const hp &b)const{return !(*this>b);}
bool hp::operator>=(const hp &b)const{return !(b>*this);}
bool hp::operator!=(const hp &b)const{return (b>*this)||(*this>b);}
bool hp::operator==(const hp &b)const{return !(b>*this)&&!(*this>b);}
// 注意：最高位的位置和位数要匹配。
//加法 
hp hp::operator+(const hp&b)const{
    hp c;
    c.num[0]=max(num[0],b.num[0]);
    for(int i=1;i<=c.num[0];i++){
        c.num[i]+=num[i]+b.num[i];
        if(c.num[i]>=10000){// 进位
            c.num[i]-=10000;
            c.num[i+1]++;
        }
    }
    if(c.num[c.num[0]+1]>0) c.num[0]++;// 9999+1，计算完成后多了一位
    return c;
}
//减法 
hp hp::operator-(const hp&b)const{
   hp c;
   c.num[0]=num[0];
   for (int i=1;i<=c.num[0];i++){
       c.num[i]+=num[i]-b.num[i];
       if(c.num[i]<0){  // 退位
            c.num[i]+=10000;
            c.num[i+1]--;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;// 100000000-99999999
    return c;
}
//顺便声明 
hp&hp::operator+=(const hp &b){return *this=*this+b;}
hp&hp::operator-=(const hp &b){return *this=*this-b;}
//乘法 
hp hp::operator*(const hp&b)const{
    hp c;
    c.num[0]=num[0]+b.num[0]+1;
    for(int i=1;i<=num[0];i++){
        for(int j=1;j<=b.num[0];j++){
            c.num[i+j-1]+=num[i]*b.num[j];            // 和小学竖式的算法一模一样
            c.num[i+j]+=c.num[i+j-1]/10000;            // 进位
            c.num[i+j-1]%=10000;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999*0
    return c;
}
//同上 
hp&hp::operator*=(const hp &b){return *this=*this*b;}
hp hp::operator/(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return c;            
}
hp hp::operator%(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return d;            
}
hp&hp::operator/=(const hp &b){return *this=*this/b;}
hp&hp::operator%=(const hp &b){return *this=*this%b;}
ostream&operator<<(ostream &o,hp &n){
    o<<n.num[n.num[0]];
    for(int i=n.num[0]-1;i>=1;i--){
        o.width(4);
        o.fill('0');
        o<<n.num[i];
    }
    return o;
}
istream & operator>>(istream &in, hp &n){
    char s[MAX];
    in>>s;
    n=s;
    return in;
}
inline int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*flag;
}
hp a,b; 
int main(){
	cin>>a>>b;
	a+=b;
	cout<<a<<endl;
	return 0;
}

```
最后给一个链接[跑的好像不是想象中的快啊。。](https://www.luogu.com.cn/record/28063630)

这题还是（毒）简（瘤）单

写题解不易，点个赞再走！

管理员求过啊



---

## 作者：Amor_Hucsy (赞：43)

看楼上几个大佬的程序一个个长如长城（夸张了），本蒟蒻就来一篇较短的程序吧！

送给不会高精度运算的小朋友！

思路非常简单

在这里要讲到一个知识点,就是：

三目运算符

知识：三目运算符，又称条件运算符，是计算机语言(c,c++,java等)的重要组成部分。它是唯一有3个操作数的运算符，所以有时又称为三元运算符。一般来说，三目运算符的结合性是右结合的。

定义：对于条件表达式b ? x : y，先计算条件b，然后进行判断。如果b的值为true，计算x的值，运算结果为x的值;否则，计算y的值，运算结果为y的值。一个条件表达式绝不会既计算x，又计算y。条件运算符是右结合的，也就是说，从右向左分组计算。例如，a ? b : c ? d : e将按a ? b : (c ? d : e)执行。
```
#include<bits/stdc++.h>//←万能头文件
using namespace std;//没有这个，不识别cin和cout
string s1,s2;//字符串定义
int l1,l2,l,i,a[10005],b[10005],c[10005];
int main()
{
    cin>>s1>>s2;//输入
    l1=s1.length();//获取s1的字符串长度
    for(i=0;i<l1;i++) a[l1-i]=s1[i]-48;//减48是因为char比int值大48 
    l2=s2.length();//获取s2的字符串长度
    for(i=0;i<l2;i++) b[l2-i]=s2[i]-48;//同上

    l=l1<l2?l2:l1;//←三目运算
    for(i=1;i<=l;i++)
     {
        c[i]=a[i]+b[i]+c[i];
        c[i+1]=c[i]/10;//进位，将前一位得到的整数乘10累加到后一位
        c[i]=c[i]%10;//重新整理c数组
    }
    if(c[l+1]>0) l++；//判断
    for(i=l;i>=1;i--) cout<<c[i];//输出
    return 0;//要养成一个好习惯
}
```


---

## 作者：duanyll (赞：30)

# 如何使用CSharp强行A掉这道题

众所周知,洛谷的C# Mono默认是没有引用`System.Numerics`这个程序集的,也就是说不能像Java或者Python一样直接调用内建的高精度类型

## 按照正常思路,但在洛谷会CE的程序

```csharp
using System;
using System.Numerics;


namespace Solution
{
	class Program
    {
		public static int Main(string[] args)
    	{
    		var a = BigInteger.Parse(Console.ReadLine();
        	var b = BigInteger.Parse(Console.ReadLine();
	    	Console.WriteLine(a+b);
    	} 
    }  
}

```

但是我们可以用反射技术来强行动态加载程序集!这样就可以动态调用高精度类了,详情见代码

```csharp
using System;
using System.Reflection;

namespace Solution
{
    class Program
    {
        public static void Main(string[] args)
        {
            try
            {
                var Numerics = Assembly.LoadFile("/usr/lib/mono/4.5/System.Numerics.dll");
                Type BigInteger = Numerics.GetType("System.Numerics.BigInteger");
                dynamic a = BigInteger.InvokeMember("Parse", BindingFlags.Static | BindingFlags.InvokeMethod | BindingFlags.Public, null, null, new object[] { Console.ReadLine() });
                dynamic b = BigInteger.InvokeMember("Parse", BindingFlags.Static | BindingFlags.InvokeMethod | BindingFlags.Public, null, null, new object[] { Console.ReadLine() });
                Console.WriteLine(BigInteger.InvokeMember("Multiply", BindingFlags.Static | BindingFlags.InvokeMethod | BindingFlags.Public, null, null, new object[] { a, b }).ToString());
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
```

顺便吐槽一下洛谷的编译器版本是mono4.6,然而运行时版本是4.5,猜了好久路径...

还有,不知道是不是反射导致的性能低下,此方法对于P1919会T掉

---

## 作者：Jianuo_Zhu (赞：18)

翻了一下题解，竟然没有一个压位高精！
~~那我就趁机水一发吧~~

其实压位高精并不是什么高级算法，只是普通高精的一个小优化。

回顾一下，高精就是因为数的位数太大，我们就开一个int数组，使得每一个数字对应数组里的一个元素。

但是再想一下，每一个数组元素只对应一个数字是不是太浪费了呢？我们干脆使一个数组元素对应多个数字，既节省了空间也节省了时间。
代码是压了4位的代码:
```cpp

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
const int wei = 4, maxn = 1e6+10, mod = 10000;
using namespace std;
char t1[maxn], t2[maxn];
int a[maxn], b[maxn], ans[maxn];
int main(){
    scanf("%s%s", t1+1, t2+1);
    int len1 = strlen(t1+1), len2 = strlen(t2+1);
    int _len1 = len1 / wei, _len2 = len2 / wei;
    if(len1 % wei) _len1++; 
    if(len2 % wei) _len2++;
    int w;
    for(int i=1; i<=_len1; i++){
        w = 1;
        for(int j=1; j<=wei && (i-1)*wei+j <= len1; j++){
            a[i] += w * (t1[len1-(i-1)*wei-j+1] - '0');
            w *= 10;
        }
    }
    for(int i=1; i<=_len2; i++){
        w = 1;
        for(int j=1; j<=wei && (i-1)*wei+j <= len2; j++){
            b[i] += w * (t2[len2-(i-1)*wei-j+1] - '0');
            w *= 10;
        }
    }
    //for(int i=1; i<=_len1; i++) cout << a[i] << " ";
    //cout << endl;
    //for(int i=1; i<=_len2; i++) cout << b[i] << " ";
    //cout << endl;
    int _len = max(_len1, _len2);
    for(int i=1; i<=_len; i++){
        ans[i] += a[i] + b[i];
        ans[i+1] += ans[i] / mod;
        ans[i] %= mod;
    }
    //for(int i=1; i<=_len+1; i++) cout << ans[i] << " ";
    int top = _len+1; 
    if(ans[top] == 0) top--;
    cout << ans[top];
    for(int i=top-1; i>0; i--) printf("%0*d", wei, ans[i]);
    return 0;
}```

---

## 作者：S_Gloria (赞：11)

#### 以前的我最最讨厌的，就是在一个很不起眼的题目中，~~（本以为很简单可以AC）~~  一定要用到高精度才可以过，于是就无数次回避它，但今天重新回望它，才发现，原来我一直害怕的，也不过如此。

### 切入正题：
顾名思义，高精度加法，就是指在int以及long long int等无法承受的范围中运行，其思想类似于我们小学学的加法竖式。

#### 如图：
![](https://cdn.luogu.com.cn/upload/pic/67662.png)
### 上AC代码：
```
#include<iostream>
#include<cstring>
using namespace std;
int c[50300],a1[51000],b1[51000];
int main()
{
	string a,b;
	cin>>a>>b;
	int l=0,s=0;
	for(int i=a.length()-1;i>=0;i--)
		a1[i]=a[l++]-'0';  //将字符转化成数字的同时将字符串进行翻转（翻转类似于algorithm库中的severse函数）
	for(int i=b.length()-1;i>=0;i--)
		b1[i]=b[s++]-'0';
	int len=max(a.length(),b.length())+1;
	for(int i=0;i<len;i++)
	{
		c[i]=a1[i]+b1[i]+c[i];
		c[i+1]=c[i]/10;   //进位操作，将前一位得到的整十倍累加到后一位。
		c[i]=c[i]%10;//得到整理后的c数组
	}
	while(c[len-1]==0&&len>1)len--;  //一定要记得len>1
	for(int i=len-1;i>=0;i--)
		cout<<c[i];
}
```

#### 最后强调几点问题:
- 输入要用cin或者scanf，不要用gets或gentline，因为换行符\n会被误认为你输入的字符串之一。
- 不要直接对字符数组a操作，因为没有被赋值的空间在相加时会出错，所以要将a中数组重新存在int类型的新数组中，此处为a1.
- 最后要把数字前面的0删掉，一定要记得len>1,因为如果不这样做，0+0会被卡。
~~（全剧终）~~

---

## 作者：45dino (赞：10)

# 蒟蒻来献丑了！！！
## 观摩了各路大神的题解，感到渺小
### 商业互吹到此结束，开始进入正题

------------
我们要进行如下步骤（别问我怎么知道的）

e.g A=58324;B=1234567;

1. 先求位数 n=5；m=7；
1. 把位数多的放在前面；
1. 把数倒过来（方便计算，不倒也行，有兴趣的童鞋可以试一试）；
1. 进行相加；
1. 会不会有超出
1. 逆序输出；

用实例来做一遍~

1. n=5，m=7；
1. n=7，m=5，A=1234567，B=58324；
1. A=7654321，B=42385；
1. 7654321

    4238500
    
    1992921
   
1. 没有超出^_*;
1. 输出；

代码如下;
```cpp
#include<bits/stdc++.h>
#define N 10010
using namespace std;
char a[N],b[N];
int c[N];
int main()
{
	int st;
	scanf("%s",a);
	scanf("%s",b);
	int n=strlen(a),m=strlen(b);
	if(n<m)
	{
		swap(n,m);
		swap(a,b);
	}
	for(int i=0;i<n/2;i++)
		swap(a[i],a[n-i-1]);
	for(int i=0;i<m/2;i++)
		swap(b[i],b[m-i-1]);
	for (int i=m;i<n;i++)
		b[i]='0';
	for (int i=0;i<n;i++)
	{
		c[i]+=a[i]+b[i]-96;
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	if (c[n]==0)
		st=n-1;
	else
		st=n;
	for (int i=st;i>=0;i--)
		cout<<c[i];
	return 0;
}
```
求过……


---

## 作者：Cold_Mood (赞：9)

蒟蒻的第一篇题解(〃'▽'〃)

高精度简单的思路：

就是把输入的长长长数每一位都拿数组存起来，进行像列竖式一样的运算。

数组从右向左存或从左向右存都一样，这里用的是前者，也就是把数组的最后一个当个位。

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
int a[5001]={},b[5001]={},c[5001]={},len,i;//数组a是第一个数，b是第二个数，c存它们两个的和
string s; 
int main()
{
	cin>>s;//输入第一个数
	for(i=0;i<=s.size();i++)
	{
		a[5001-s.size()+i]=s[i]-'0';//存进数组
	}
	cin>>s;//输入第二个数
	for(i=0;i<=s.size();i++)
	{
		b[5001-s.size()+i]=s[i]-'0';//存进数组
	}
	for(i=5000;i>=1;i--)
	{
		c[i]=a[i]+b[i]+c[i];//加起来
		c[i-1]+=c[i]/10;//进位
		c[i]%=10;
	}
	len=0;
	while(c[len]==0 and len!=5000)len++;//这个的主要作用是去掉数组前面的0，所以前面定义时要清零呐
	for(i=len;i<=5000;i++)
	cout<<c[i];//输出
    return 0;
    //华丽的结束(￣▽￣)~*
}
```
总的来说还是很简单的呀

求过(*/ω＼*)

---

## 作者：Valhalla_Is_Calling (赞：9)

## 其实是一道模板题，用结构体做

A+B高精度版其实是一道模板题，在很多领域都有用处。

高精度算法，属于处理大数字的数学计算方法。在一般的科学计算中，会经常算到小数点后几百位或者更多，当然也可能是几千亿几百亿的大数字。一般这类数字我们统称为高精度数，高精度算法是用计算机对于超大数据的一种模拟加，减，乘，除，乘方，阶乘，开方等运算。对于非常庞大的数字无法在计算机中正常存储，于是，将这个数字拆开，拆成一位一位的，或者是四位四位的存储到一个数组中， 用一个数组去表示一个数字，这样这个数字就被称为是高精度数。高精度算法就是能处理高精度数各种运算的算法，但又因其特殊性，故从普通数的算法中分离，自成一家。

这个是百度百科给出的代码：

```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Wint:vector<int>//用标准库vector做基类，完美解决位数问题，同时更易于实现
{
    //将低精度转高精度的初始化，可以自动被编译器调用
    //因此无需单独写高精度数和低精度数的运算函数，十分方便
    Wint(int n=0)//默认初始化为0，但0的保存形式为空
    {
        push_back(n);
        check();
    }
    Wint& check()//在各类运算中经常用到的进位小函数，不妨内置
    {
        while(!empty()&&!back())pop_back();//去除最高位可能存在的0
        if(empty())return *this;
        for(int i=1; i<size(); ++i)
        {
            (*this)[i]+=(*this)[i-1]/10;
            (*this)[i-1]%=10;
        }
        while(back()>=10)
        {
            push_back(back()/10);
            (*this)[size()-2]%=10;
        }
        return *this;//为使用方便，将进位后的自身返回引用
    }
};
//输入输出
istream& operator>>(istream &is,Wint &n)
{
    string s;
    is>>s;
    n.clear();
    for(int i=s.size()-1; i>=0; --i)n.push_back(s[i]-'0');
    return is;
}
ostream& operator<<(ostream &os,const Wint &n)
{
    if(n.empty())os<<0;
    for(int i=n.size()-1; i>=0; --i)os<<n[i];
    return os;
}
//比较，只需要写两个，其他的直接代入即可
//常量引用当参数，避免拷贝更高效
bool operator!=(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return 1;
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return 1;
    return 0;
}
bool operator==(const Wint &a,const Wint &b)
{
    return !(a!=b);
}
bool operator<(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return a.size()<b.size();
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return a[i]<b[i];
    return 0;
}
bool operator>(const Wint &a,const Wint &b)
{
    return b<a;
}
bool operator<=(const Wint &a,const Wint &b)
{
    return !(a>b);
}
bool operator>=(const Wint &a,const Wint &b)
{
    return !(a<b);
}
//加法，先实现+=，这样更简洁高效
Wint& operator+=(Wint &a,const Wint &b)
{
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0; i!=b.size(); ++i)a[i]+=b[i];
    return a.check();
}
Wint operator+(Wint a,const Wint &b)
{
    return a+=b;
}
//减法，返回差的绝对值，由于后面有交换，故参数不用引用
Wint& operator-=(Wint &a,Wint b)
{
    if(a<b)swap(a,b);
    for(int i=0; i!=b.size(); a[i]-=b[i],++i)
        if(a[i]<b[i])//需要借位
        {
            int j=i+1;
            while(!a[j])++j;
            while(j>i)
            {
                --a[j];
                a[--j]+=10;
            }
        }
    return a.check();
}
Wint operator-(Wint a,const Wint &b)
{
    return a-=b;
}
//乘法不能先实现*=，原因自己想
Wint operator*(const Wint &a,const Wint &b)
{
    Wint n;
    n.assign(a.size()+b.size()-1,0);
    for(int i=0; i!=a.size(); ++i)
        for(int j=0; j!=b.size(); ++j)
            n[i+j]+=a[i]*b[j];
    return n.check();
}
Wint& operator*=(Wint &a,const Wint &b)
{
    return a=a*b;
}
//除法和取模先实现一个带余除法函数
Wint divmod(Wint &a,const Wint &b)
{
    Wint ans;
    for(int t=a.size()-b.size(); a>=b; --t)
    {
        Wint d;
        d.assign(t+1,0);
        d.back()=1;
        Wint c=b*d;
        while(a>=c)
        {
            a-=c;
            ans+=d;
        }
    }
    return ans;
}
Wint operator/(Wint a,const Wint &b)
{
    return divmod(a,b);
}
Wint& operator/=(Wint &a,const Wint &b)
{
    return a=a/b;
}
Wint& operator%=(Wint &a,const Wint &b)
{
    divmod(a,b);
    return a;
}
Wint operator%(Wint a,const Wint &b)
{
    return a%=b;
}
//顺手实现一个快速幂，可以看到和普通快速幂几乎无异
Wint pow(const Wint &n,const Wint &k)
{
    if(k.empty())return 1;
    if(k==2)return n*n;
    if(k.back()%2)return n*pow(n,k-1);
    return pow(pow(n,k/2),2);
}
//通过重载运算符，还可以实现++、--、^、!、逻辑运算符等很多运算，十分简单，此处都不写了
int main()//现在你完全可以像int一般便捷地使用Wint，如下
{
    Wint a,b;
    //可以把b改成int型，仍能正常使用
    cin>>a>>b;
    cout<<(a<b)<<endl
        <<(a==b)<<endl
        <<a+b<<endl
        <<a-b<<endl
        <<a*b<<endl
        <<a/b<<endl
        <<a%b<<endl
        <<pow(a,b);
}

```
但我觉得有点麻烦，用结构体可以直接做出来：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
int i,j;
char ab[100001],bc[100001];
int a[100001],b[100001];
int jw=0;
int maxn,maxj;
inline void Read()
{
	cin>>ab>>bc;
	x=strlen(ab);
	y=strlen(bc);
	for(i=0;i<x;i++) a[i]=ab[x-i-1]-'0';
	for(i=0;i<y;i++) b[i]=bc[y-i-1]-'0';
}
inline void solve()
{
	maxn=max(x,y);
	for(i=0;i<maxn;i++)
	{
		a[i]=a[i]+b[i]+jw;
		jw=a[i]/10;
		a[i]=a[i]%10;
	}
	if(jw==1) cout<<jw;
	for(i=maxn-1;i>=0;i--) cout<<a[i];
}
int main()
{
	Read();
	solve();
	return 0;
}
```
这样就简洁多了！

这样的好处是：调用时数组可能会遇到重复的情况，若不返回长度，很可能出现乱码的情况。如果返回长度，就得用很长的代码。所以用结构体是明智的选择！

## 杜绝作弊，请勿抄袭

---

## 作者：yyy2015c01 (赞：8)

对于蒟蒻来说略难（神犇请无视这句话）

说明详见注释

```cpp

#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
using namespace std;
int a[10000]={0},b[10000]={0};//存两个数
int main()
{
    string js1,js2;
    cin>>js1>>js2;//读入
    int len1=js1.size(),len2=js2.size(); 
    for (int i=len1-1,j=0;i>=0;i--,j++)//反着存到a数组
    {
        a[j]=js1[i]-'0';
    }
    for (int i=len2-1,j=0;i>=0;i--,j++)//反着存到b数组
    {
        b[j]=js2[i]-'0';
    }
    
    int i=0,x=0;
    while( i<=len1 || i<=len2 )//相加，为了节省空间直接存在b数组
    {
        b[i]+=a[i]+x;
        x=b[i]/10;
        b[i]%=10;
        i++;
    }
    b[i]=x;
    while(b[i]==0 && i!=0) i--;//去前导0，直到去完或只剩一个0（代表和是0）
    for (int j=i;j>=0;j--)//输出
    {
        cout<<b[j];
    }
    cout<<endl;
    //system("pause");
}

```

---

## 作者：方天睿 (赞：8)

pas的代码，首先用字符串读入数据，然后逆向存入a，b两个数组中，数组c存两数的和，注意进位，在输出时注意不要忘记若c的长度比原先的a，b长时l要加1,。



```cpp
var a,b,c:array[1..500] of longint;
    n,m:string;
    i,ln,lm,l:longint;
begin
    readln(n);
    ln:=length(n);
    for i:=1 to ln do
        a[ln-i+1]:=ord(n[i])-48;
    readln(m);
    lm:=length(m);
    for i:=1 to lm do 
        b[lm-i+1]:=ord(m[i])-48;
    if ln>lm then l:=ln
    else  l:=lm;
    for i:=1 to l+1 do
        c[i]:=0;
    for i:=1 to l do begin
        c[i]:=c[i]+a[i]+b[i];
        if c[i]>=10 then begin
            c[i+1]:=c[i+1]+c[i] div 10;
            c[i]:=c[i] mod 10;
        end;
    end;
    if c[l+1]<>0 then
        l:=l+1;
    for i:=l downto 1 do
        write(c[i]);
end.
```

---

## 作者：Huangc (赞：7)

简单的高精题。

输入是两个字符串，接下来把他们放入数组里，并记录长度。

然后按竖式加法的方法计算。

详见 [百科词条：高精加](http://oj.luogu.org:8888/wiki?name=%E9%AB%98%E7%B2%BE%E5%8A%A0&flag=y)


---

## 作者：蒟蒻溴化氢 (赞：5)

蒟蒻花了一上午写了一个高精度
个人认为代码对新手比较友好（包括加减乘）
注释在代码里
（代码参考了林厚从的《信息学奥赛课课通》以及@stone_juice石汁的一篇题解）
```
#include <iostream>
#include <cstdio>
#include <cstring>
#define res register int
using namespace std;
const int N=10010;
char sa[N],sb[N];
//用字符串形式存储数据 
string add(char sa[],char sb[])//高精度加法 
{
	string ans="";
	int a[N],b[N],c[N];
	int la=strlen(sa);//得到sa有多少位 
	int lb=strlen(sb);//得到sb有多少位 
	memset(a,0,sizeof(a));//初始化一下 
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	for(res i=0;i<la;i++) a[la-i-1]=sa[i]-'0';//把字符转化为数字  同时把数字翻转过来 
											  //这样a[i]就表示第i位 
	for(res i=0;i<lb;i++) b[lb-i-1]=sb[i]-'0';
	int lc=max(la,lb);//最后的结果就是两个的最大值 
	for(res i=0;i<lc;i++)
	{
		c[i]+=a[i]+b[i];//加法 
		if(c[i]>=10) c[i+1]=1,c[i]-=10;//处理一下进位的问题 
	}
	if(c[lc]>0) lc++;
	for(res i=lc-1;i>=0;i--)
	{
		char tmp=c[i]+'0';
		ans=ans+tmp;//结果 
	}
	return ans;
}

int _compare(char sa[],char sb[])//比较两个正数的大小 
{//1代sa>sb 0代表相等 -1代表sa<sb 
	int la=strlen(sa),lb=strlen(sb);
	if(la<lb) return -1;//如果长度不同 那么大小就可以确定 
	if(la>lb) return 1;
	for(res i=0;i<la;i++)
	{
		char tmpa=sa[i];
		char tmpb=sb[i];
		if(tmpa>tmpb) return 1;
		if(tmpa<tmpb) return -1;
	}
	return 0;
}



string _minus(char sa[],char sb[],int x)//高精度减法 x代表是否取负号 
{
	string ans="";
	int a[N],b[N],c[N];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	int la=strlen(sa);
	int lb=strlen(sb);
	for(res i=0;i<la;i++) a[la-i-1]=sa[i]-'0';
	for(res i=0;i<lb;i++) b[lb-i-1]=sb[i]-'0';//前面有解释 
	int lc=max(la,lb);
	for(res i=0;i<lc;i++)
    {
        if(c[i]+a[i]-b[i]<0)
        {
            c[i+1]--;
            c[i]+=10;
        }//借位处理
        c[i]+=a[i]-b[i];
    }
	while(c[lc-1]==0&&lc>0) lc--;//删除在最开始的0 
	for(res i=lc-1;i>=0;i--)
	{
		char tmp=c[i]+'0';
		ans=ans+tmp;
	} 
	if(x==-1) ans="-"+ans;
	return ans;
}

string _mul(char sa[],char sb[])
{
	if(sa[0]=='0'||sb[0]=='0') return "0";
	string ans="";
	int a[N],b[N],c[N];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	int la=strlen(sa);
	int lb=strlen(sb);
	for(res i=0;i<la;i++) a[la-i-1]=sa[i]-'0';
	for(res i=0;i<lb;i++) b[lb-i-1]=sb[i]-'0';
	for(res i=0;i<la;i++)
		for(res j=0;j<lb;j++)
		{
			int f,w,jw;//i和j位相乘存储在答案的i+j位当中 
			f=a[i]*b[j]; jw=f/10; f=f%10;w=i+j;//jw表示进位 f表示进位后剩下的数 
			c[w]=c[w]+f;jw+=c[w]/10;c[w]=c[w]%10;
			c[w+1]=c[w+1]+jw;
		}
	int lc=la+lb;
	while(c[lc-1]==0&&lc>0) lc--;//前面有解释 
	for(res i=lc-1;i>=0;i--)
	{
		char tmp=c[i]+'0';
		ans=ans+tmp;
	}
	return ans;
}


int main()
{
//	freopen("test.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin>>sa>>sb;
//在做减法之前 要先比较哪一个数更大 
	if(_compare(sa,sb)==1) cout<<_minus(sa,sb,1);
	else if(_compare(sa,sb)==-1) cout<<_minus(sb,sa,-1);
	else cout<<"0";

	cout<<_mul(sa,sb);
	return 0;
} 
```
rp++

---

## 作者：lzr20040310 (赞：5)

无聊做重载运算符,突发奇想去做高精,顺便和大家普及一下重载运算符

在c++的std这个namespace里有所有运算符的using和基础的重载,

但如果涉及到自定义类型(class,struct等)时,就需要自己重载了

重载关键字operator,重载过程和函数类似

PS:我非常做作的用了short四位压,结果程序很麻烦,凑合看看

不多说,上程序

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int pow(int a,int b){//简单较慢的快速幂,但是很简单
    if(b==0)//递归边界之一:a^0=1(暂且不考虑a=0)
        return 1;
    if(b==1)//递归边界之二:a^1=a
        return a;
    if(b==2)//递归边界之三:a^2=a*a
        return a*a;
    if(b%2==0)//快速幂的核心递归部分:当2|b时,a^b=(a^(b/2))^2
        return pow(pow(a,b/2),2);
    else//递归部分:当b%2=1时,a^b=a^(b-1)*a
        return pow(a,b-1)*a;
}
struct integer{
    short i[126];//四位一压,所以共有126*4=504位,不会爆
    bool pn;//我还考虑了符号......
    integer( ){//构造函数初始化
        int j;
        pn=false;
        for(j=0;j<126;j++)
            i[j]=0;
    }//这个应该都看得懂吧......
    void read( ){//成员函数负责读入
        int j,k,m=0,n=0;
        char ii[504]={0};
        bool zero=true;
        scanf("%s",ii);//读入
        if(ii[0]=='-')//正负处理
            pn=true;
        else
            pn=false;
        for(j=503;j>-1;j--)//处理绝对值
            if(ii[j]>0){//找到个位
                for(k=j;k>-1;k--)
                    if(ii[k]>='0' && ii[k]<='9'){
                        n++;
                        i[m]+=pow(10,n-1)*(ii[k]-'0');//这一步最难懂,慢慢琢磨,想一想怎么往高插入
                        if(n==4){//四位一压,别过界
                            n=0;
                            m++;
                        }
                    }
                break;
            }
        for(j=0;j<126;j++)//分清楚0和-0是一码事(没办法我考虑了符号)
            if(i[j]>0)
                zero=false;
        if(zero)
            pn=false;
        return;
    }
    void write( ){//成员函数负责输出(总感觉像Pascal)
        int j,k,a,b,c,d;
        bool zero=true;
        for(j=0;j<126;j++)//分清楚0和-0是一码事
            if(i[j]>0)
                zero=false;
        if(zero)
            pn=false;
        if(pn)//负号
            putchar('-');
        for(j=125;j>-1;j--)//找到最高位
            if(i[j]>0){
                cout<<i[j];//省略前导0
                for(k=j-1;k>-1;k--){//一定注意这里不能省略前导0!!!这也是为什么四位一压麻烦的原因之一
                    a=i[k]/1000;
                    b=i[k]/100%10;
                    c=i[k]/10%10;
                    d=i[k]%10;
                    putchar(a+'0');
                    putchar(b+'0');
                    putchar(c+'0');
                    putchar(d+'0');
                }
                return;
            }
        putchar('0');//如果自始至终都是0(不进循环,即本数为0),输出0
        return;
    }
    integer operator=(const int a){//把int型转化成integer自定义型
        int b,j,k;
        bool zero=true;
        b=a;//注意a是const类型,不可改变!
        if(a<0){//对负数的处理
            b=-b;
            pn=true;
        }
        else
            pn=false;
        for(j=0;j<126;j++){//想一想,为什么是10000不是10
            i[j]=b%10000;
            b/=10000;
            if(b==0){
                for(k=j+1;k<126;k++)
                    i[k]=0;
                break;
            }
        }
        for(j=0;j<126;j++)//还是那句话,分清楚0和-0是一码事
            if(i[j]>0)
                zero=false;
        if(zero)
            pn=false;
        return *this;
    }
    integer(int a){//重载运算符里最难懂的部分,注意一定要有这个(只要你有对赋值语句的重载最好都加上)
        *this=a;
    }
    integer operator+(const integer &a){//对加号的重载
        integer b;
        int j;
        bool zero=true;
        if(*this==0)//0加任何数,仍得这个数
            return a;
        else if(a==0)
            return *this;
        if(pn==a.pn){//同号两数相加,取相同的符号,并把绝对值相加
            b.pn=pn;
            for(j=0;j<125;j++){
                b.i[j]+=i[j]+a.i[j];
                b.i[j+1]+=b.i[j]/10000;//还是那个问题,想想为什么是10000不是10
                b.i[j]=b.i[j]%10000;
            }
            b.i[125]+=i[125]+a.i[125];//专防数组越界(即访问无效内存)
            b.i[j]=b.i[j]%10000;
            for(j=0;j<126;j++)//不多说了,你懂的
                if(b.i[j]>0)
                    zero=false;
            if(zero)
                b.pn=false;
            return b;
        }
        else{//异号两数相加,取绝对值较大数的符号,并把绝对值相减
            int tw=0;
            integer x,y;
            x.pn=false;
            y.pn=false;
            for(j=0;j<126;j++){
                x.i[j]=i[j];
                y.i[j]=a.i[j];
            }
            if(x>y){//判断哪个数的绝对值大
                b.pn=pn;
                for(j=0;j<126;j++){
                    b.i[j]=i[j]-a.i[j]-tw;
                    tw=0;
                    if(b.i[j]<0){
                        b.i[j]+=10000;
                        tw++;
                    }
                }
                for(j=0;j<126;j++)
                    if(b.i[j]>0)
                        zero=false;
                if(zero)
                    b.pn=false;
                return b;
            }
            else if(x<y){
                b.pn=a.pn;
                for(j=0;j<126;j++){
                    b.i[j]=a.i[j]-i[j]-tw;
                    tw=0;
                    if(b.i[j]<0){
                        b.i[j]+=10000;
                        tw++;
                    }
                }
                for(j=0;j<126;j++)
                    if(b.i[j]>0)
                        zero=false;
                if(zero)
                    b.pn=false;
                return b;
            }
            else{//互为相反数的两个数和为0
                b=0;
                for(j=0;j<126;j++)
                    if(i[j]>0)
                        zero=false;
                if(zero)
                    pn=false;
                return b;
            }
        }
    }
        bool operator>(const integer &a)const{//判断大小
        int j;
        if(pn && (!a.pn))//负数小于正数
            return false;
        else if((!pn) && a.pn)//正数大于负数
            return true;
        else if(pn){//两个负数比较,绝对值大的反而小
            for(j=125;j>-1;j--){
                if(i[j]<a.i[j])
                    return true;
                else if(i[j]>a.i[j])
                    return false;
            }
            return false;
        }
        else{//两个正数比较,绝对值大的就大
            for(j=125;j>-1;j--){
                if(i[j]>a.i[j])
                    return true;
                else if(i[j]<a.i[j])
                    return false;
            }
            return false;//相等返回false
        }
    }
    bool operator<(const integer &a)const{//小于即大于的完全相反
        return a>(*this);
    }
    bool operator==(const integer &a)const{//等于即既不大于又不小于
        return !(*this>a || *this<a);
    }
    bool operator>=(const integer &a)const{//大于等于即不小于
        return !(*this<a);
    }
    bool operator<=(const integer &a)const{//小于等于即不大于
        return !(*this>a);
    }
    bool operator!=(const integer &a)const{//不等于就是不等于嘛......
        return !(*this==a);
    }
};
int main( ){
    integer a,b,c;//剩下的简单易懂
    a.read( );
    b.read( );
    c=a+b;
    c.write( );
    return 0;
}
```

---

## 作者：TomTheCat (赞：5)

高精度的题目，按照正常思路做就行了。

方法如下：

1. 字符串输入（注意一定要用cin或scanf，不能用gets）
2. 倒序转化为数字（方便进位）
3. 加法运算（最关键的部分）
4. 倒序输出（因为是倒序转化为数字）

代码如下：

------------
 ```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1001]={},b[1001]={};        
int a1[1001]={},b1[1001]={},c1[1001]={};
int main(){
	cin>>a>>b; //字符串输入
	int lena=strlen(a),lenb=strlen(b);
	for(int i=0;i<lena;i++) 
        a1[i]=a[lena-1-i]-48;
	for(int i=0;i<lenb;i++)
        b1[i]=b[lenb-1-i]-48; //倒序转化为数字
	int maxl=(lena>lenb?lena:lenb);
	int lenc=0,x=0;
	while(lenc<maxl) {
	    c1[lenc]=a1[lenc]+b1[lenc]+x;
	    x=c1[lenc]/10;
		c1[lenc]=c1[lenc]%10;
		lenc++;
	} //加法运算
	if(x) c1[lenc]=x;
	else lenc--;
	for(int i=0;i<=lenc;i++) 
        cout<<c1[lenc-i]; //倒序输出
	return 0;
}

```
------------
~~学生：那万一有人懒到20多行代码都不愿意写怎么办~~

~~老师：别BB了，都听到了~~

那么在这里教给大家一个懒人高精度方法：Python

Python是自带高精的语言，所以做高精度题就像处理普通数那样就行了。

代码如下：

------------
```python
a=int(input())
b=int(input())
print(a+b)
```
------------
ps：本蒟蒻第一次提交题解，希望能对大家有所帮助。


---

## 作者：白羊座de咸鱼 (赞：5)

我只是想展示一下c语言两行主程序能干什么
小蒟蒻一枚，各位dalao有优化方案望不吝赐教
```c
#include<stdio.h>
#include<string.h>
int ca[150],cb[150],ia[600],ib[600],c[600],i,j,flag,l,k;
int main()
{
    for(scanf("%s%s",&ca,&cb),l=0,k=strlen((char*)ca)+strlen((char*)cb)+1198; l<k; l<strlen((char*)ca)?(l==0?(i=strlen((char*)ca)-1,j=599):1,ia[j]=((char*)ca)[i]-'0',i--,j--):(l>=strlen((char*)ca)&&l<k-1198?(l==strlen((char*)ca)?(i=strlen((char*)cb)-1,j=599):1,ib[j]=((char*)cb)[i]-'0',i--,j--):(l>=k-1198&&l<k-599?(l==k-1198?i=599:1,ia[i]+ib[i]+c[i]<10?c[i]+=ia[i]+ib[i]:(c[i]=(ia[i]+ib[i]+c[i])%10,c[i-1]=1),i--):(l==k-599?i=0:1,flag==0?(c[i]!=0?(printf("%d",c[i]),flag=1):1):printf("%d",c[i]),i++))),l++);
    return printf("%d",c[599])&0;
}
```
注意到那个for是在一行的。。。

---

## 作者：langyo (赞：4)

大概转了一圈，没看见用 C++11 的，所以就来贴一下专属于 C++11 及以上的 AC 源码。这个程序正好还能普及一下 C++11 呢！~

原理其实真的很简单，列竖式就能解决的问题。

这个程序的要点如下：

- 输入完成后就将两个数字进行反转，从个位开始算到最高位，是最靠谱的一种数字处理方法

- 计算完成后要再反转过来，从最高位输出到个位

- 不要直接使用 char 进行数学运算，特别容易出错；遇到类型转换，最好使用 ```static_cast<类型>```， 而不是直接括号包裹个类型，这是 C++11 建议使用的最好的显式类型转换方法

- 使用一个中间变量 ```temp``` 存储进位数字；当两边数字的相应位与上一位的进位数字（可能是进一，或也可能不进位，也就是 0）加完之后，判定一下 temp 是否超过了 9，超过 9 就设置成 1 以参与下一轮运算的进位，没超过就设置为 0

- 在反序遍历时，我使用了反向不可变迭代器 ```crbegin()``` 与 ```crend()```

- 在读取向量时，我使用了可以保证安全访问、带越界检查的 ```at(unsigned int)```，而不是原生的 ```operator[]``` 

- 我需要保证第一个数字的长度一定要比第二个数字的短，因此，在正式计算之前，我会检查两边的长度，如需要就使用 ```swap()``` 成员函数交换数据，保证前提逻辑正确

（我相信没了解过 C++11 的 OIer 很不习惯写这种没有任何全局变量、原生数组、C 库的程序 :P 这正是一睹的机会）

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string in1, in2;
    cin >> in1 >> in2;

    vector<short> num1, num2;
    for(auto i = in1.crbegin(); i < in1.crend(); ++i) num1.push_back(static_cast<short>(*i - '0'));
    for(auto i = in2.crbegin(); i < in2.crend(); ++i) num2.push_back(static_cast<short>(*i - '0'));

    if(num1.size() > num2.size()) num1.swap(num2);

    vector<short> sum;
    int temp = 0;
    for(int p = 0; p < num1.size(); ++p) {
        temp += num1.at(p) + num2.at(p);
        if(temp > 9) {
            sum.push_back(temp - 10);
            temp = 1;
        }
        else {
            sum.push_back(temp);
            temp = 0;
        }
    }
    for(int p = num1.size(); p < num2.size(); ++p) {
        temp += num2.at(p);
        if(temp > 9) {
            sum.push_back(temp - 10);
            temp = 1;
        }
        else {
            sum.push_back(temp);
            temp = 0;
        }
    }
    if(temp > 0) sum.push_back(temp);

    for(auto i = sum.crbegin(); i != sum.crend(); ++i) cout << *i;
    cout << endl;

    return 0;
}
```

看不懂 C++11？没关系。这里给个现役 C++ 工程师都必须知道的网站，[cppreference](https://zh.cppreference.com/w/%e9%a6%96%e9%a1%b5)，它不仅足够带你了解 C++11，还可以让你了解 C++14/17/20。

虽然 NOI/NOIP 仍然不能确定未来是否有可能会支持 C++11，但至少，这个题解不仅仅是给 OIer 的，并且也是出给未来的工程师/程序员的，C++11 仍然有可探讨的余地。

题解就到这里了，我也将完整源代码传到了自己的 Github 仓库上了（[P1601](https://github.com/langyo/oi-code-library/blob/master/luogu/P1601.cpp)），也欢迎来围观本人的 [Github 主页](https://github.com/langyo)哦~

---

## 作者：Null_Cat (赞：4)

a+b的高精好经典的呢~

为了~~水题解~~给各位奆犇提供版子。。那么就来写了一下这篇题解。。。

------------
在很多的~~毒瘤题~~考试中会高频出现高精（+，-，*，/，快速幂等）

所以
# **高精很重要的**
（敲黑板画重点）

咳咳



------------
虽然说计算机可以帮我们算数，但是计算机和我们一样，遇到特别大的数就

__算不了！__

但是我们毕竟是人嘛~于是不知哪位~~XD~~伟大的先人发明了

### 竖式！

来~~增加我们考试的难度~~帮助我们计算

那么我们可以通过竖式来计算大数，那么我们也可以让计算机学会竖式

~~这样高精就转化为了模拟~~

举个栗子awa：

#### 2333+314159=？

~~解：由题意得~~

![那么就可以得到这个竖式qwq](F:\力量之源泉\高精\高精加.bmp)

那么我们是怎么算的呢？

首先从个位开始算：

3+9=~~（真好吃）~~
12

这时候我们把12的10取走进到十位，那么结果的个位就是—— 2

如此的不断反复的向前进位就可以得到结果316492

但是的说，2333是个四位数314159是个六位数，在列竖式的时候就会有两位对不上，那怎么算嘤嘤嘤qwq

~~但是你算的时候不是自己补0了嘛qwq~~

So!

对于高精加法我们就有了基本的思路：

1. 把位数少的数补0

2.从个位开始不断计算，如果大于10该位就位两数该位和mod10并且向前面一位+1

3.得到结果


------------
既然有了思路下面就是实现了

第一步是存数。毕竟是高精嘛。。。如果说用一个单纯的int肯定是不行的qwq

那么我们就有两种解决方法：

__1：使用int型数组__

优点：计算方便，不用类型转化

缺点：读入较为麻烦，需要借助一个char转类型，不便于统计长度

__2：使用char*或string__

优点：长度便于统计，直接读入，较为动态

缺点：计算需转类型


------------

那么这里我们就用~~我觉得方便的~~string来做

计算函数如下：
```cpp
inline string calc(string a,string b){
	re int *alength=new int;
	re int *blength=new int;		//re代表register，此处常数优化，可以不加
	*alength=a.size(),*blength=b.size();	//我用的指针，改成普通string也行
	if(*alength<*blength){		//寻找需要补位的数
		for(re int i=0;i<*blength-*alength;i++){	//顺序无所谓，反正就是长-短-1次
			a='0'+a;	//补小数0
		}
	}
	else{
		for(re int i=0;i<*alength-*blength;i++){
			b='0'+b;	//同上
		}
	}
	*alength=a.size();	//更新数的新长度
	re bool* pre=new bool;	//是否进位
	*pre=0;		//默认0
	re int* each=new int;	//当前位的数
	re string result;	//返回的字符串
	for(re int i=*alength-1;i>=0;i--){	//遍历这个数
		*each=(a[i]^48)+(b[i]^48)+*pre;	//计算当前位，记得加上进上来的位，x^48=x-'0'('0'<=x<='9')
		*pre=*each/10;	//更新进位
		*each%=10;	//更新当前位的数
		result=char(*each+'0')+result;	//更新返回的字符串
	}
	if(*pre) result=char(*pre+'0')+result;	//如果还有一位没进完，进一位
	delete alength;
	delete blength;
	delete pre;
	delete each;	//指针玩家勿忘，不然原地爆炸伺候awa
	return result;	//返回
}
```

那么根据同样的方法，可以得到高精减，高精乘，高精除的程序（这里我不打了自己可以翻阅一本通awa
~~（其实就是懒）~~
）

本题完整程序如下：
```cpp
#include<cstdio>
#include<string>
#include<iostream>
#define re register
using namespace std;
inline string fRead();
inline string calc(string,string);
int main(int argc,char* argv[]){
	string *a=new string;
	string *b=new string;
	*a=fRead();
	*b=fRead();
	cout<<calc(*a,*b)<<endl;
	delete a;
	delete b;	//不要忘了delete申请的空间！！！
	return 0;
}
inline string fRead(){		//这里是快读，用cin或scanf也行，详见我博客awa（其实这不是地道的快读）
	re string result;
	re char *chr=new char;
	*chr=getchar();
	while(*chr<'0'||*chr>'9'){
		if(*chr=='-'){
			result+='-';
		}
		*chr=getchar();
	}
	while(*chr>='0'&&*chr<='9'){
		result+=*chr;
		*chr=getchar();
	}
	delete chr;
	return result;
}
inline string calc(string a,string b){	//此处如上
	re int *alength=new int;
	re int *blength=new int;
	*alength=a.size(),*blength=b.size();
	if(*alength<*blength){
		for(re int i=0;i<*blength-*alength;i++){
			a='0'+a;
		}
	}
	else{
		for(re int i=0;i<*alength-*blength;i++){
			b='0'+b;
		}
	}
	*alength=a.size();
	re bool* pre=new bool;
	*pre=0;
	re int* each=new int;
	re string result;
	for(re int i=*alength-1;i>=0;i--){
		*each=(a[i]^48)+(b[i]^48)+*pre;
		*pre=*each/10;
		*each%=10;
		result=char(*each+'0')+result;
	}
	if(*pre) result=char(*pre+'0')+result;
	delete alength;
	delete blength;
	delete pre;
	delete each;
	return result;
}
```

---

## 作者：do_loop (赞：4)

### **蒟蒻第一次发布题解,有不周之处望见谅**

高精度算法，属于处理大数字的数学计算方法。本质上，就是位数极大的数进行数学运算。

其思想就是利用数组存储数字每一位（或者四位四位的存），然后手动模拟竖式运算。

而高精度加法,是其中最简单的一种。

思路：
-
先利用字符数组读入数字,再存储到整型数组中。

按照竖式运算右对齐，从低位到高位依次相加，记得进位。

----

上代码：
---
```
#include<bits/stdc++.h>
using namespace std;
char a1[501],b1[501];
int a[501],b[501],c[501],la,lb,lc;
int main()
{
	cin>>a1>>b1;
	la=strlen(a1),lb=strlen(b1),lc=max(la,lb);//strlen()用来获取字符串长度，max(la,lb)用来获取la,lb的较大值 
	for(int i=0,j=lc-la+1;i<la,j<=lc;i++,j++) a[j]=a1[i]-'0';
	for(int i=0,j=lc-lb+1;i<lb,j<=lc;i++,j++) b[j]=b1[i]-'0';//存储到整型数组并右对齐，加一给最高位进位留出空间 
	for(int i=lc;i>=1;i--)//从低位到高位依次相加 
	{
		c[i]+=a[i]+b[i];
		if(c[i]>=10) c[i]-=10,c[i-1]++;//进位 
	} 
	if(c[0]!=0) printf("%d",c[0]);//判断最高位是否进位 
	for(int i=1;i<=lc;i++) printf("%d",c[i]);
	return 0;
}
```
----

---

## 作者：oreimo_eromanga (赞：4)

```cpp

#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<string>
#include<cstdio>
#include<cmath> //漂亮的头文件。
using namespace std;
int add(string a,string b)
{
    int a1[1001],b1[1001],c1[1001];
    int alen=a.size();
    int blen=b.size();
    int y;string k;
    if(alen<blen){y=alen;alen=blen;blen=y;k=a;a=b;b=k;} //机智的调试。
    for(int i=0;i<alen;i++)
       a1[alen-i]=a[i]-'0';
    for(int i=0;i<blen;i++)
       b1[blen-i]=b[i]-'0';
    int i=1,jw=0;   //判断是否有进位。
    while(i<=alen||i<=blen)
    {
      c1[i]=a1[i]+b1[i]+jw;
      jw=c1[i]/10;
      c1[i]%=10;
      i++;
    }
    c1[i]=jw;
    if(c1[i]==0) i--;
    for(int j=i;j>=1;j--)
       cout<<c1[j];
    cout<<endl;
}
int main() //前面用函数做可以让程序更好套用。
{
    string a,b;
    cin>>a>>b;
    add(a,b);
}
//觉得好请点赞哦！

```

---

## 作者：little_gift (赞：4)

##刚才题解交错地方了- -##

嗯,鉴于现在市场上高精加模板十分缺乏,献上一份用类写的高精加.

当然,最经典的在main函数...

#include <bits/stdc++.h>

using namespace std;

class cint{

private:

        int c\_number[100001],c\_len,c\_d,c\_fh;

public:


```cpp
        cint();
        ~cint();
        cint(int x);
        cint(string st);
        cint operator+(cint& b);
        cint read_cint();
        void write_cint();
};
cint::cint()
{
    c_d=10;
}
cint::~cint()
{
}
cint::cint(int x)
{
    c_d=10;
    if (x<0)
    {
        c_fh=-1;
        x=-x;
    }
    else c_fh=1;
    c_len=0;
    while (x)
    {
        c_len++;
        c_number[c_len]=x%c_d;
        x/=c_d;
    }
}
cint::cint (string st)
{
    int i;
    if (st[0]=='-') 
    {
        c_fh=-1;
        st.erase(0,1);
    }
    else c_fh=1;
    while (st[0]=='0'&&st.length()>1)
        st.erase(0,1); //去除前导0
    c_len=st.length();
    for (i=1;i<=c_len;i++)
        c_number[i]=(st[c_len-i]-48)*c_fh; //用一个字符的ascii码-48后存入c_number
} //将字符串转成数字
cint cint::operator+(cint& b) //重载+,便于计算
{
    int i;
    cint c;
    if (c_len>=b.c_len) c.c_len=c_len;
    else c.c_len=b.c_len; //计算长度
    for (i=1;i<=c.c_len;i++)
    {
        c.c_number[i]+=c_number[i]+b.c_number[i]; //将两个数相加
        c.c_number[i+1]=c.c_number[i]/c.c_d; //如果有进位,保存
        c.c_number[i]%=c.c_d; //去除进位
    }
    while (c.c_number[c.c_len+1])
        c.c_len++; //处理最高位的进位
    while ((!c.c_number[c.c_len])&&c.c_len>1)
        c.c_len--; //处理前导0
    return c;
}
cint cint::read_cint()
{
    string st;
    cin>>st;
    return cint(st); //输入
}
void cint::write_cint()
{
    int i;
    for (i=1;i<=c_len;i++)
        cout<<c_number[c_len-i+1]; //输出
}
istream& operator>>(istream& is,cint &c)
{
    c=c.read_cint();
    return is; //重载运算符,便于输入
}
ostream& operator<<(ostream& os,cint c)
{
    c.write_cint();
    return os; //重载运算符,便于输出
}
```
重点来了
#接下来是神奇的主程序#

看下面


```cpp
int main()
{
    cint a,b;
    cin>>a>>b;
    cout<<a+b<<endl;
}
```

---

## 作者：Sorenson (赞：4)

先说说高精度运算的概念：

是指参与运算的数(加数，减数，因子……）范围大大超出了标准数据类型（整型，实型）能表示的范围的运算。例如，求两个200位的数的和。这时，就要用到高精度算法了。（摘自百度百科）。


再往下看之前，大家先列竖式计算35+86。

注意的问题：

（1）运算顺序：两个数靠右对齐；从低位向高位运算；先计算低位再计算高位；

（2）运算规则：同一位的两个数相加，然后再加上从低位来的进位，成为该位的和；

这个和再去掉向高位的进位就成为该位的值；如上例：3+8+1=12，向前一位进1，本位的值是2；

可借助MOD、DIV运算完成这一步；

（3）最后一位的进位：如果完成两个数的相加后，进位位值不为0，则应添加一位；

（4）如果两个加数位数不一样多，则按位数多的一个进行计算；


基本思路：

1. 先将从键盘输入的两个数分别存入两个char型的字符数组，然后再将两个char数组的数据转存入两个int型的数组。

这一功能的代码如下：

   

```cpp
for (i=0;i<=a1_len-1;i++)   
{  
    a[a1_len-i]=a1[i]-48; //将操作数放入a数组 　  
}  
for (i=0;i<=b1_len-1;i++)  
{  
    b[b1_len-i]=b1[i]-48; //将操作数放入b数组   
}   
```
数字存入char型数组，要存入int型数组，需要减去48，可以查看ascii码表。道理如同大写字母变小写字符需要加32是一样的。

2. 从两个int数组的地位开始执行操作，地位相加，注意进位。这一功能的代码如下：

while(lenc <=a1\_len || lenc <=b1\_len)   
```cpp
    {   
        c[lenc]=a[lenc]+b[lenc]+x; //两数相加 　  
        x=c[lenc]/10;   //要进的位  
        c[lenc]=c[lenc]%10;     //进位后的数  
        lenc++;     //数组下标加1  
    }  
```
3. 最后一步的时候要判断是否有进位，如果有进位，注意下标的变化，将最后一个进位存储进去；如果没有进位，则完成运算。
下面是用C++实现高精度加法的完整代码，代码的变化性很大，可以根据自己的想法做修改的。

源代码如下：

      
       
   
       
  
      
      
      
      
```cpp
#include<iostream>  
#include<cstdio>  
#include<cstring>  
using namespace std;  
int main()  
{  
    char a1[100],b1[100];  
    int a[100],b[100],c[100];  
    int a1_len,b1_len,lenc,i,x;  
    memset(a,0,sizeof(a));   
    memset(b,0,sizeof(b));   
    memset(c,0,sizeof(c));  
    gets(a1);   
    gets(b1); //输入加数与被加数   
    a1_len=strlen(a1);   
    b1_len=strlen(b1);   
    for (i=0;i<=a1_len-1;i++)   
    {  
        a[a1_len-i]=a1[i]-48; //将操作数放入a数组 　  
    }  
    for (i=0;i<=b1_len-1;i++)  
    {  
        b[b1_len-i]=b1[i]-48; //将操作数放入b数组   
    }   
    lenc =1;   
    x=0;   
   while(lenc <=a1_len || lenc <=b1_len)   
   {   
        c[lenc]=a[lenc]+b[lenc]+x; //两数相加 　  
        x=c[lenc]/10;   //要进的位  
        c[lenc]=c[lenc]%10;     //进位后的数  
        lenc++;     //数组下标加1  
    }  
    c[lenc]=x;  
    if (c[lenc]==0)  
    {  
        lenc--; //处理最高进位   
    }   
    for (i=lenc;i>=1;i--)  
    {  
        cout<<c[i]; //输出结果      
    }  
    cout<<endl;  
    return 0;  
}
```

---

## 作者：毛梁智洲666 (赞：3)

怎么说呢，比较基础的高精。

有些人会说？啥是高精啊？

高精度。顾名思义，就是在很大的位数情况下进行运算。（炸ull）

在这里，窝给各位老铁写出了

### 数据类型的范围

|  类型| 类型 |占用内存空间  |
|-----------: | -----------: | -----------: |
|  char| -128~127 | 1 |
| short | -32768~32767 |2  |
|  int| -2147483648 ~ +2147483647 | 4 |
|long long  | -9223372036854775808 ~+9223372036854775807 |  8|
| unsigned short | 0 ~ 65536 |  2|
| unsigned int |0 ~ 4294967295  |  4|
| unsigned long long | 0~18446744073709551615 |  8|

就是这样。

而这题的数据范围是 $10$ 的 $500$次方（不会表示啊QWQ）...

就要用到高精。

只能用string输入了。

对了，我们是加法，要用到转换。

辣么就设一个converts函数吧。

```
void converts(int *a,string s){//int *a 表明a是数组 ,其实 a也是指针。
	int i,len=s.size();
	for(i=0;i<len;i++) a[i]=s[len-i-1]-'0';
	for(;i<SIZE;i++) a[i]=0;
}
```
个位数 放在数组的0号下标位置

十位数 放在数组的1号下标位置

空的位置全部用0填充

。。。。。。

这就是精髓。


------------

还要有一个输出的函数： 

```
void print(int *a){
	int i;
	for(i=SIZE-1;i>0;i--) if(a[i]>0) break;
	for(;i>=0;i--) cout<<a[i]; cout<<endl;
}
```
先找到数组中非0位置的最高位，或个位

再逐位输出

直到数组的0号下标位置

也就是个位数


------------
重要的来了

加法：

```
void add(int *a,int *b,int len=SIZE){//a+=b
	//逐位相加
	for(int i=0;i<len;i++)
		if((a[i]+=b[i])>=10){//进位 
			a[i+1]++; 
			a[i]-=10;
		}
}
```
从个位开始，逐位相加

如果当前位置的数>=10，就进位


------------
这就是内容所在。也算是高精模板吧，以后写高精就在这基础上编程。


------------
全部代码：
```
#include<iostream>
#include<string>
#define SIZE 209
using namespace std;
void converts(int *a,string s){
	int i,len=s.size();
	for(i=0;i<len;i++) a[i]=s[len-i-1]-'0';
	for(;i<SIZE;i++) a[i]=0;
}

void add(int *a,int *b,int len=SIZE){//a+=b
	//逐位相加
	for(int i=0;i<len;i++)
		if((a[i]+=b[i])>=10){//进位 
			a[i+1]++; 
			a[i]-=10;
		}
}
void print(int *a){//输出
	int i;
	for(i=SIZE-1;i>0;i--) if(a[i]>0) break;
	for(;i>=0;i--) cout<<a[i]; cout<<endl;
}
int x[SIZE],y[SIZE];
int main(){
	string s1,s2;
	cin>>s1>>s2;
	converts(x,s1);
	converts(y,s2);
	add(x,y);
	print(x);
	return 0;
}

```


---

## 作者：ynycoding (赞：3)

这道题我用的动态数组vector。

自作孽不可活，写了一长串代码，还加了一个类。

满满的都是泪（类）呀！

我居然写了30min!


话不多说，首先介绍一下整体的结构

num类中有一个动态数组n，代表高精度中每一位。


```cpp
#define MAXN (10)
class num{
    public:
        vector <int> n;
        ```
然后有一个构造函数，可以直接调用这个来给高精度数赋值。~~其实没卵用~~

```cpp
        num(int in) {
            for(; in; in/=MAXN)
            {
                n.push_back(in%MAXN);
            }
        }
```
然后是重载了一个加法运算符，其实就是模拟人工竖式计算...

```cpp
        num operator + (const num &a)
        {
            num c;
            int i;
            int tmp=0;
            for(i=0; (i<a.n.size())&&(i<this->n.size()); i++)
            {
                c.n.push_back((a.n[i]+this->n[i]+tmp)%MAXN);
                tmp=(a.n[i]+this->n[i]+tmp)/MAXN;
            }
            if(i==a.n.size())
            {
                for(; i<n.size(); i++)
                {
                    c.n.push_back((n[i]+tmp)%MAXN);
                    tmp=(n[i]+tmp)/MAXN;
                }
                if(tmp) c.n.push_back(tmp);
            }
            else
            {
                for(; i<a.n.size(); i++)
                {
                    c.n.push_back((a.n[i]+tmp)%MAXN);
                    tmp=(a.n[i]+tmp)/MAXN;
                }
                if(tmp) c.n.push_back(tmp);
            }
            return c;
        }
```
然后又是一个重载的等于（赋值）运算符，这个不必多说吧...

```cpp
        num operator = (num &a)
        {
            for(int i=n.size(); i; i--) n.pop_back();
            for(int i=0; i<a.n.size(); i++) n.push_back(a.n[i]);
            return *this;
        }
```
然后就是重载cin>>和cout<<了。

```cpp
ostream& operator << (ostream &o, const num & N)
{
    for(int i=(N.n.size()-1); i>=0; i--) cout<<N.n[i];
    return o;
}
istream& operator >> (istream & in, num & N)
{
    string s;
    in>>s;
    for(int i=N.n.size(); i; i--) N.n.pop_back();
    for(int i=(s.length()-1); i>=0; i--) N.n.push_back(s[i]-'0');
    return in;
}

int main()
{
    num a, b;
    cin>>a>>b;
    cout<<a+b;
    return 0;
}
```
~~说实话，这些东东一本通上都有。。。~~（划掉)

~~我发现自己把这篇题解交到隔壁高精度减法去了，尴尬~~


---

## 作者：Charisk_FOD (赞：3)

# 新-高精度

我们将输入的数每15位就被储存一次，再对这15位相加。若加完后是16位，则将数组下一个位置的数+1，然后这个数  %=$10^{16}$，这样，一个更高级的算法就完了！

这样来做，对于500（$10^{500}$）位的数字，最多会加33次，数组最大是34位！是不是比500少多了呢？

---

For example(15位拆分)
```cpp
Input 111222222222222222333333333333333

拆分后：
a[1]=333333333333333
a[2]=222222222222222
a[3]=111
```

---

For example(拆分后的加法)
```cpp
拆分后的数字1：
a[1]=333333333333333
a[2]=222222222222222
a[3]=111

拆分后的数字2：
b[1]=123456789111111
b[2]=888888888888888
b[3]=3589

c[1]=a[1]+b[1]
c[1]=456790122444444
因为c[1]在15位以内，所以不进位

c[2]=a[2]+b[2]
c[2]=1111111111111110
因为c[2]超过了15位，进位

c[3]=a[3]+b[3]+1  (c[2]有进位)
c[3]=3701

那么最终答案就是从c[3]输出到c[1]。
其中不够15位的要补0！
```

代码如下，更详细的讲解在代码中（~~代码不好看，将就将就吧~~）：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>

typedef long long LL;   //define同样效果 

using namespace std;

const LL pow15=999999999999999;  //超过这个数就要进位！！ 
const LL pow10[18]={1,1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000};
//一些预处理着实会节省一些时间 

LL a[37],lena=1,b[37],lenb=1,c[38],lenc;  //a数组-加数1，b数组-加数2，c数组-加数3 
char in1[900],in2[900];   //读入两个数 

void exread(char in[900],LL d[35],LL &len){   //15位拆分！ 
	LL cnt=0;
	LL lenn=strlen(in)-1;
	while(in[lenn]!='\n'&&in[lenn]!='\r'&&lenn>=0){   //要注意，数据可能是在windows环境下造的，windows是'\r\n'，不要把'\r'也看成数组 
		if(in[lenn]==' '){   //处理数据的恶心情况--空格 
			lenn--;continue;
		}
		cnt++;
		if(cnt>15)cnt=1,len++;
		d[len]=d[len]+(in[lenn]-'0')*pow10[cnt];   //这时候，预处理就显得很有帮助 
		lenn--;
	}
}

void print(long long x){    //快输，想要就复制走 
	if(x>=10)print(x/10);
	putchar(x%10+'0');
}

int main(){
	scanf("%s",in1);    //哎，洛谷总是与gets()过意不去。。。 
	scanf("%s",in2);
	exread(in1,a,lena);
	exread(in2,b,lenb);
	
	lenc=max(lena,lenb);
	for(LL i=1,j=1,k=1;i<=lena||j<=lenb;i=(i==lena+1 ? lena+1:i+1),j=(j==lenb+1 ? j+1:j+1),k++){
	//后来发现，这个for应该这么写：
	//for(LL i=1;i<=max(lena,lenb);i++)
	//写麻烦了... 
	//不过顺便一提，三目运算符很重要！！！ 
		
		c[k]+=a[i]+b[j];
		if(c[k]>pow15){   //处理进位 
			c[k+1]+=(c[k]/(pow15+1));   //因为要使数变成10^16。 
			c[k]%=(pow15+1);   //同理 
		}
	}
	if(c[lenc+1]!=0)lenc++;    //如果最后有进位一定要加上，(a+b)的位数不会超过max(|a|,|b|)+1,（|a|表示a的位数） 
	print(c[lenc]);    //首次输出没必要补0 
	for(LL i=lenc-1;i>=1;i--){    //输出后(lenc-1)*15位 
		for(LL j=15;j>=1;j--){    //补0 
			if((LL)(c[i]/pow10[j])==0)putchar('0');   //预处理派上了用场！ 
			else break;
		}
		if(c[i]!=0)print(c[i]);    //如果这15位本身就为0，那么上面已经补完0，没必要输出 
	}
	return 0;   //华丽的结束！ 
}
```

## PS:
 - 灵感来源于位运算（~~可见位运算的重要性~~）
 - 这种方法在位数<30位的时候优势更明显！
 - 高精乘法这种方法同样适用！
 
---

听说NOIP前发题解会rp++???

#### [配合博客食用更佳](https://www.luogu.org/blog/aldrich-7-17-start/#)

---

## 作者：ak20070412kevin (赞：3)

##### 输入别用gets！！！   
#### 输入别用gets！！！   
### 输入别用gets！！！   
为啥？因为gets会把回车读进去呗！   
___  
___   

我们先来分析一下下~   
看到如此之大的A、B（501位），我们千万别傻乎乎地搞cout<<a+b; ~   
那么，我们肿么瓣？   
那就是传说中的字符串！   
我们可以把数看成字符串   
把字符串转化成数组（因为处理起来简单）   
再把同一位的两个数字对齐   
像做加法竖式一样加起来。   
#### 注意！  
###### 加法计算时相同数位对齐，若和超过10，则向前进1。   
所以我们把数位对齐……   
问题来了，怎么对齐？
那就是加前辍0！   
加前辍0的话（1234+32=1266）（对位有点不齐，请原谅）：   
                        1 2 3 4  
+0 0 3 2   
——————   
   1 2 6 6   
不加前辍0（1234+32=4434?）：   
                                                                   1 2 3 4  
+3 2   
——————   
   4 4 3 4   
（当然不加也可以，只不过复杂一点）   
再考虑一下进位就可以啦！
```cpp
#include<bits/stdc++.h>
using namespace std;
char sa[505],sb[505];//输入的两个字符串
int a[505],b[505];//转化成的数组
int f[505];//记录和
int main()
{
    scanf("%s%s",sa,sb);//别用gets！别用gets！别用gets！
    int ax=strlen(sa),bx=strlen(sb),d=max(ax,bx);
    int i,j;
    for(i=ax-1,j=0;i>=0;i--,j++)//反向转化，便于进位
        a[j]=sa[i]-48;
    for(;j<d;j++)//加前辍0
        a[j]=0;
    for(i=bx-1,j=0;i>=0;i--,j++)
        b[j]=sb[i]-48;
    for(;j<d;j++)
        b[j]=0;
    int bilibili=0;//进位变量
    for(int i=0;i<d;i++)
    {
        f[i]=(a[i]+b[i]+bilibili)%10;//记录个位
        bilibili=(a[i]+b[i]+bilibili)/10;//进位
    }
    if(bilibili==1)//最高位是否进位
        cout<<1;//输出最高位的1
    for(int i=d-1;i>=0;i--)//输出
        cout<<f[i];
    return 0;
}
```


---

## 作者：saisai (赞：3)

这个题目中我们发现数据范围很大，超过了int和long long 的范围所以我们应该采用高精度算法；

我们要考虑进位的问题，所以我采用了将输入的串翻转的方式

如下：

输入：

1234
123
我们存储下来是这样的

4321
3210
这样每一位就都能对齐了，然后我们模仿手算就可以了

首先用ans数组存储每一位的和（ans【i】=c【i】+d【i】）

完成这步操作后我们就只用进行进位就行了，从个位向后进行进位：

for（int i=1;i<=lens;i++）{

ans[i+1]=ans[i]/10;//这里是对当前位数进行进位

     ans[i]=ans[i]%10;

}
但是在这里不要忘了

如果输入的是6 6；

答案是12 所以说输出的时候不要忘了判断ans【lens+1】是否有数-

那么下面附上代码 希望不要抄袭，看懂了代码自己再凭着自己的理解打上才能真正的理解这个算法哦~


```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
char a[600];
int c[600];
char b[600];
int d[600];
int ans[600];
int main(){
    scanf("%s",a);
    scanf("%s",b);
    int lensa=strlen(a);
    int lensb=strlen(b);
    int lens=max(lensa,lensb);
    for(int i=0;i<lensa;i++){
        c[lensa-i]=a[i]-'0';
    }
    for(int i=0;i<lensb;i++){
        d[lensb-i]=b[i]-'0';
    }
    for(int i=1;i<=lens;i++){
        ans[i]=c[i]+d[i];
    }
    for(int i=1;i<=lens;i++){
        ans[i+1]+=ans[i]/10;
        ans[i]=ans[i]%10;
    }
    if(ans[lens+1]!=0)cout<<ans[lens+1];
    for(int i=lens;i>=1;i--){
        cout<<ans[i];
    }
    cout<<endl; 
    return 0;
}
```

---

## 作者：RiverHamster (赞：3)

###C++简易高精度加法（未使用新特性）

###做高精度的题有几个注意点：

**1.用字符串输入（这没得说）但是最好不要用C++ string，容易出小问题（比如说string的operator []一旦超出字符串长度，就是无效的操作，导致无法向高位进位（只能用push\_back()或assign()），涉及到修改每一位的问题，用char数组不容易出错，insert()，replace()之类的也容易错。**

**2.输入时不要把字符串反转，这样也很麻烦，直接倒过来做，可以用1下标，如果最后一位进位不会越界，最后按0下标输出。1下标使用方法：gets(s+1),scanf("%s",s+1),cin>>s+1等都可以**

###以上仅个人观点，具体视情况而定

###思路：

1.按 **1下标** 输入两个字符串，然后计算出长度。

2.使用三指针（a的指针，b的指针和ans的指针，a和b指针的初始值为它们的长度，而ans指针为a指针和b指针其中更大的那个数），先加共有的位，再将一个数多出来的位加到ans中）

3.如果最后一位没有进位，则用strcpy将前面1下标的空位补上（整个串前移一位），否则（进位已将空位不上）将其改成字符1（最多进位1），返回。

###代码部分

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
char a[505],b[505],ans[505],ans1[505];    //a,b是两个加数，ans是和，ans1是用来将ans前移一位用的（懒得自己移位，直接用strcpy()） 

char *add(char *a,char *b){               //计算两个高精度字符串相加 
    int aptr=strlen(a+1),bptr=strlen(b+1),ansptr=aptr>bptr?aptr:bptr;  //a,b,ans现在正在加的指针 
    while(aptr>0&&bptr>0){                //两数共有的位相加 
        ans[ansptr]+=a[aptr]+b[bptr]-'0'; //相加，注意这里不能用=赋值，用+=（否则进位就会失效） 
        if(ans[ansptr]>'9'){              //进位 
            ans[ansptr]-=10;
            ans[ansptr-1]++;
        }
        aptr--,bptr--,ansptr--;           //移动至下一位 
    }
    //以下代码补满没有加（该位只有一个数，两加数长度不同）的位
    //两个while循环意义相同 
    while(aptr>0){
        ans[aptr]+=a[aptr]; //依然注意+= 
        if(ans[aptr]>'9') ans[aptr]-=10,ans[aptr-1]++;
        aptr--;
    }
    while(bptr>0){
        ans[bptr]+=b[bptr];
        if(ans[bptr]>'9') ans[bptr]-=10,ans[bptr-1]++;
        bptr--;
    }
    if(ans[0]!=0){   //如果末位进了位，整数值为1 
        ans[0]='1';  //转化为字符1 
        return ans;
    }
    else{  //如果末位没有进位，末位整数值为0 
        strcpy(ans1,ans+1);  //左移一位（将1下标的ans拷贝到0下标的ans1中去 
        return ans1;         //返回ans1 
    }
}

int main(){
    scanf("%s%s",a+1,b+1);   //按1下标输入 
    printf("%s\n",add(a,b)); //按0下标输出 
    return 0;
}
```
####By RiverHamster


---

## 作者：plazum (赞：3)

进位可以用除以10和模10来方便地实现。

```cpp

#include<stdio.h>
#include<string.h>
int a[501],b[500],i,j;
char sa[501],sb[501];
int main()
{
    gets(sa);
    gets(sb);
    for(j=strlen(sa)-1;j>=0;i++,j--)a[i]=sa[j]-'0';
    for(j=strlen(sb)-1,i=0;j>=0;i++,j--)b[i]=sb[j]-'0';
    for(i=0;i<500;i++)a[i+1]+=(a[i]+b[i])/10,a[i]=(a[i]+b[i])%10;
    for(i=500;!a[i]&&i;i--);
    for(;i>=0;putchar(a[i--]+'0'));
    
    return 0;
}

```

---

## 作者：封禁用户 (赞：3)

看到好像没有Java的题解（不调用Math库中的BigInteger的情况下），那就水一发（巨长400行，适用于高精加减乘除）（当然这个数据卡点请忽略那个if-else(原因超过String类的默认内存大小))

```Java
import java.util.Scanner;

class BigInteger {
    public static final BigInteger ZERO = new BigInteger();  
    public static final BigInteger ONE = new BigInteger("1");  
    public static final BigInteger TWO = new BigInteger("2");  
    
    /*
     * 这样有利于解决正负数问题，所有大整数在操作时可以直接对value进行，最后统一考虑得到结果的符号。
     */
    private String value;//字符串value为该大整数的绝对值
    private int length;//length存储该绝对值的位数
    private boolean positiveorNegative;//positiveor negative. + is true, - is false
    
    /*
     * 无参数构造函数BigInteger()
     */
    BigInteger(){
        this.length = 1;
        this.positiveorNegative = true;
        this.value = "";
    }
    
    /*
     * 带有字符串的构造函数BigInteger(String s)
     * 通过私有方法isLegal(s)对参数进行合法性判断；
     * 判断该字符串是否带有符号，设置其符号positiveorNegative；
     * 通过私有方法findStartPos(s)寻找字符串真正有意义的最高位；
     * 将最高位之后的所有字符存入value中，并在length中记录该value的长度；
     *  对0做特殊处理。
     */
    BigInteger(String s){
        if(isLegal(s)) {
            if(s.charAt(0) == '+' || s.charAt(0) == '-') {
                this.positiveorNegative = s.charAt(0) == '+' ? true:false;
            }else {
                this.length = s.length();
                this.positiveorNegative = true;
            }
            
            int sp = findStartPos(s);
            
            this.value = s.substring(sp);
            this.length = s.length() - sp;
            
            if(this.value.charAt(0) == '0') {
                this.positiveorNegative = true;
                this.length = 1;
                this.value = "0";
            }
        }else {
            System.out.println("Unacceptable number!!!");
        }
    }
    
    /*
     * BigInteger转字符串publicString toString()
     * 由于数据结构中将符号位与数据位分离，所以在输出时只需要考虑在符号位pn==false时在value前加上负号即可。
     */
    public String toString() {
        if(positiveorNegative == false) {
            return "-" + value;
        }
        return value;
    }
    
    /*
     *  大整数比较是否相等public boolean equals(BigInteger x)
     *  与toString()类似，比较两个大整数的符号位和数据位是否相等即可。需要注意的是在数据位比较时要用equals()，直接使用等号比较的是引用的值而非真实数据。
     */
    public boolean equals(BigInteger x) {
        if(this.positiveorNegative == x.positiveorNegative && this.length == x.length && this.value.equals(x.value)) {
            return true;
        }
        return false;
    }
    
    /*
     *  大整数比较大小public int compare(BigInteger x)
     *  大于返回1，等于返回0，小于返回-1.
     *  直接通过符号位pn不同时比较两个数的大小；
     *  符号相同时，借助长度不同比较两个数的大小，正数长度大的大，负数长度小的大；
     *  符号长度都相同时，借助compareTo比较两个数的value，正数返回compareTo的结果对应点1和-1，负数返回compareTo结果的相反数的-1和1。
     */
    public int compare(BigInteger x) {
        if(this.positiveorNegative != x.positiveorNegative) {
            return this.positiveorNegative == true ? 1: -1;
        }
        
        if(this.length != x.length) {
            if(this.positiveorNegative) {
                return this.length > x.length ? 1 : -1;
            }else {
                return this.length < x.length ? 1 : -1;
            }
        }
        
        int tmp = this.value.compareTo(x.value);
        if(this.positiveorNegative) {
            tmp *= -1;
        }
        if(tmp > 0) {
            return -1;
        }
        if(tmp < 0) {
            return 1;
        }
        
        return tmp;
    }
    
    /*
     * 大整数加法public BigInteger add(BigInteger x)
     * 对于加法操作，只考虑符号位相同的情况，将符号位不同的情况丢给减法。
     * 对0做特殊处理，返回另一个数，注意是创建一个新的大整数进行返回，如new BigInteger(this.toString())；
     * 如果两个数符号位不同，则创建x的备份xx，并使用私有方法changePN()改变xx的符号位，计算this-xx，将结果返回；
     * 创建两个字符串bigger和smaller，分别记录数据位较大的数据位和较小数的数据位；
     * 模拟加法操作：用bigger和smaller从最低位按位进行加法操作，借助私有方法charAdd()按位加，结果记录在字符串ans中；并通过carryValue来记录当前按位加结果是否得到进位，如果有进位，则在下一位加法操作时需要将carryValue加入按位加操作中，否则将其清零；
     * ans[i] =bigger[bigger.length-i]+smaller[smaller.length-i]+carryValue
     * 当smaller的最高位加完后，需要对bigger多出的高位继续与carryValue进行按位加；
     * 判断最高位是否产生进位，如果产生则补充一个最高位1；
     * 将ans进行反转操作，用其构造大整数，并将其符号位置为this的符号位。
     */
    public BigInteger add(BigInteger x) {
        if(x.value.equals("0")) {
            return new BigInteger(this.toString());
        }
        
        if(this.value.equals("0")) {
            return new BigInteger(x.toString());
        }
        
        if(this.positiveorNegative != x.positiveorNegative) {
            BigInteger xx = new BigInteger(x.toString());
            xx.changePN();
            return this.substract(xx);
        }
        
        String bigger,smaller;
        if((this.compare(x) >= 0 && this.positiveorNegative) || (this.compare(x) < 0 && !this.positiveorNegative)) {
            bigger = new String(this.value);
            smaller = new String(x.value);
        }else {
            bigger = new String(x.value);
            smaller = new String(this.value);
        }
        
        String tmpAns = new String();
        int carryValue = 0;
        for(int i = 1;i <= smaller.length();i++) {
            int tmpAdd = charAdd(bigger.charAt(bigger.length() - i),smaller.charAt(smaller.length() - i)) + carryValue;
            carryValue = tmpAdd >= 10 ? 1 : 0;
            tmpAns += String.valueOf(tmpAdd - carryValue * 10);
        }
        
        int pos = bigger.length() - smaller.length() - 1;
        while(carryValue != 0 && pos >= 0) {
            int tmpAdd = charAdd(bigger.charAt(bigger.charAt(pos)),'1');
            carryValue = tmpAdd >= 10 ? 1 : 0;
            tmpAns += String.valueOf(tmpAdd - carryValue * 10);
            pos--;
        }
        
        String ans = new String();
        tmpAns = reverse(tmpAns);
        
        if (carryValue == 0) {  
            ans = bigger.substring(0, Math.max(pos+1, 0))+tmpAns;  
        }else if (pos < 0) {  
            ans = "1" + tmpAns;  
        }  
        if (!this.positiveorNegative) {  
            ans = "-" + ans;  
        }  
        return new BigInteger(ans);  
    }
    
    /*
     * 大整数减法操作public BigInteger substract(BigInteger x)
     * 类似加法，只考虑符号位相同的情况，将符号位不同的情况丢给加法；接下来只介绍模拟减法的操作。
     * tmpSub= charSub(bigger[bigger.length()-i], smaller[smaller.length()-i], carryValue);
     */
    public BigInteger substract(BigInteger x) {  
        if (x.value.equals("0")) {  
            return new BigInteger(this.toString());  
        }else if (this.value.equals("0")) {  
            BigInteger ans = new BigInteger(x.toString());  
            ans.changePN();  
            return ans;  
        }  
        if (this.positiveorNegative != x.positiveorNegative) {  
            BigInteger xx = new BigInteger(x.toString());  
            xx.changePN();  
            return this.add(xx);  
        }  
        String bigger, smaller;  
        boolean tag = this.compare(x) >= 0 ? true : false;  
        if ((this.compare(x) >= 0 && this.positiveorNegative) || (this.compare(x) <= 0 && !this.positiveorNegative)) {  
            bigger = new String(this.value);  
            smaller = new String(x.value);  
        }else {  
            bigger = new String(x.value);  
            smaller = new String(this.value);  
        }  
        String tmpAns = new String();  
        int carryValue = 0;  
        for (int i = 1; i <= smaller.length(); i++) {  
            int tmpAdd = charSub(bigger.charAt(bigger.length() - i), smaller.charAt(smaller.length() - i), carryValue);  
            carryValue = tmpAdd < 0 ? 1 : 0;  
            if (tmpAdd == -100) {  
                carryValue = 1;  
                tmpAdd = 0;  
            }  
            tmpAns += String.valueOf(Math.abs(tmpAdd));  
        }  
        int pos = bigger.length() - smaller.length() - 1;  
        while(carryValue != 0 && pos >= 0) {  
            int tmpAdd = charSub(bigger.charAt(pos), '0', carryValue);  
            carryValue = tmpAdd < 0 ? 1 : 0;  
            tmpAns += String.valueOf(Math.abs(tmpAdd));  
            pos--;  
        }  
        String ansStr = new String();  
        tmpAns = reverse(tmpAns);  
        if (carryValue == 0) {  
            ansStr = bigger.substring(0, Math.max(pos+1, 0))+tmpAns;  
        }  
        BigInteger ans = new BigInteger(ansStr);  
        ans.positiveorNegative = tag;  
        return ans;
    }
    
    /*
     * 大整数乘法操作public BigInt multiply(BigInt x)
     * 采用分治的思想，设两个数分别为M1, M2，长度为均为l。可将其表示为：
     * M1 = AB，A为前l/2长度的数据位，B为后l-l/2长度的数据位；
     * M2 = CD，C为前l/2长度的数据位，D为后l-l/2长度的数据位；
     * 于是M1*M2可表示为
     * M1*M2 = A*C*(10^((l-l/2)*2)) + B*D + ((A-B)*(D-C)+A*C+B*D) *(10^(l-l/2))
     * 但是无法保证两个数数据位长度均为l，故需要将数据位短的前面补零补齐l位。之所以采取这样的方法是因为原本的乘法操作分解之后仍为四次乘法，而采取上式得乘法操作分解之后只需三次乘法操作，时间复杂度降为O(l^log(3))。
     */
    public BigInteger multiply(BigInteger x) {  
        if (x.value.equals("0") || this.value.equals("0")) {  
            return new BigInteger();  
        }  
        boolean ansPN = !(this.positiveorNegative ^ x.positiveorNegative);  
        if (x.length == 1 && this.length == 1) {  
            int ians = Integer.parseInt(x.value)*Integer.parseInt(this.value);  
            BigInteger ans = new BigInteger(String.valueOf(ians));  
            ans.setPN(ansPN);  
            return ans;  
        }  
        String a = this.value, b = x.value;  
        /**********Unify Length**********/  
        int len1 = Math.max(a.length(), b.length())-a.length();  
        int len2 = Math.max(a.length(), b.length())-b.length();  
        for (int i = 0; i < len1; i++) {  
            a = "0" + a;  
        }  
        for (int i = 0; i < len2; i++) {  
            b = "0" + b;  
        }  
        BigInteger a1 = new BigInteger(a.substring(0, a.length()/2));  
        BigInteger a2 = new BigInteger(a.substring(a.length()/2));  
        BigInteger b1 = new BigInteger(b.substring(0, b.length()/2));  
        BigInteger b2 = new BigInteger(b.substring(b.length()/2));  
        BigInteger ans1 = a1.multiply(b1);//a1*b1  
        BigInteger ans2 = a2.multiply(b2);//a2*b2  
        BigInteger sub1 = a1.substract(a2);  
        BigInteger sub2 = b2.substract(b1);  
        BigInteger ans3 = sub1.multiply(sub2);//(a1-a2)(b2-b1)  
        ans3 = ans3.add(ans1);  
        ans3 = ans3.add(ans2);  
        String tmp = ans1.value;  
        for (int i = 0; i < (a.length()-a.length()/2)*2; i++) {  
            tmp += "0";  
        }  
        ans1 = new BigInteger(tmp);  
        tmp = ans3.value;  
        for (int i = 0; i < (a.length()-a.length()/2); i++) {  
            tmp += "0";  
        }  
        if (!ans3.positiveorNegative) {  
            tmp = "-"+tmp;  
        }  
        ans3 = new BigInteger(tmp);  
        BigInteger ans = ans1.add(ans3).add(ans2);  
        ans.setPN(ansPN);  
        return ans;  
    }

    /*
     * 大整数除法操作public BigInt divide(BigInt x)（除数非0）
     * 判断除数的数据位是否大于被除数的数据位，如果大于，返回0；
     * 在x后补零，使得x变为不大于this的最大补零数，记补了cnt个0，为方便操作，相当于x*addZero，addZero=100…00，其中有cnt个0；
     * 初始化商quotient为0；
     * LOOP1：循环cnt次；
     * LOOP2：每次计算this-x，this = this-x，quotient = quotient+addZero，直到this<x；
     * 将addZero和x末尾去掉一个零，转LOOP1；
     * 将商的符号位置位为this和x的符号位的异或。
     */
    public BigInteger divide(BigInteger x) {  
        boolean ansPN = !(this.positiveorNegative ^ x.positiveorNegative);  
        if (x.toString().equals("0")) {  
            System.out.println("The divider cannot be 0!");  
            BigInteger ans = new BigInteger("1");  
            ans.setPN(ansPN);  
            return ans;  
        }  
        if (unsignedCompare(x) < 0) {  
            return new BigInteger("0");  
        }  
        String a = this.value, b = x.value, addZero = new String("1");  
        int cnt = a.length()-b.length();  
        for (int i = 0; i < cnt; i++) {  
            b += "0";  
            addZero += "0";  
        }  
        BigInteger divA = new BigInteger(a), divB = new BigInteger(b);  
        BigInteger quotien = new BigInteger("0");  
        while(cnt >= 0) {  
            BigInteger addBI = new BigInteger(addZero);  
            while(divA.compare(divB) >= 0) {  
                quotien = quotien.add(addBI);  
                divA = divA.substract(divB);  
            }  
            divB = new BigInteger(divB.value.substring(0, Math.max(1,divB.value.length()-1)));  
            addZero = addZero.substring(0, Math.max(1,cnt));  
            cnt--;  
        }  
        quotien.setPN(ansPN);  
        return quotien;  
    }
    
    /*
     * 大整数取余操作public BigInt mod(BigInt x)
     * 调用this.divid(x)得到商q；
     * 调用q.multiply(x)得到积tmp；
     * 返回this.substract(tmp).
     */
    public BigInteger mod(BigInteger x) {  
        BigInteger tmp = this.divide(x);  
        tmp = tmp.multiply(x);  
        return this.substract(tmp);  
    }
    
    /*
     * 阶乘操作public static BigInt factorial(BigInt x)：
     * 递归调用x.multiply(factorial(x.substract(ONE)))即可；
     */
    public BigInteger factorial(BigInteger x) {  
        if (!x.equals(ZERO)) {  
            return x.multiply(factorial(x.substract(ONE)));  
        }  
        return new BigInteger("1");  
    }
    
    private int unsignedCompare(BigInteger x) {//无符号比较  
        BigInteger a = new BigInteger(this.value);  
        BigInteger b = new BigInteger(x.value);  
        return a.compare(b);  
    }  
    
    private String reverse(String s) {//字符串反转  
        StringBuffer sb = new StringBuffer(s);  
        return sb.reverse().toString();  
    }  
    
    private int charAdd(char x, char y) {//字符加  
        return x + y - '0' - '0';  
    }  
    
    private int charSub(char x, char y, int c) {//字符减  
        int ans = x + 10 - c - y;  
        if (ans < 10) {  
            if (ans == 0) {  
                ans = 100;  
            }  
            return ans*(-1); // there is a negative zero problem  
        }  
        return ans-10;  
    }  
    
    private void changePN() {//符号位反转  
        this.positiveorNegative = this.positiveorNegative==true ? false:true;  
        if (this.value.charAt(0) == '0') {  
            this.positiveorNegative = true;  
        }  
    }  
    
    private void setPN(boolean targetPN) {//设置符号位  
        this.positiveorNegative = targetPN;  
    } 
    
    private int findStartPos(String s) {//寻找字符串规范起始位置  
        for (int i = 0; i < s.length(); i++) {  
            if (Character.isDigit(s.charAt(i)) && s.charAt(i)!='0') {  
                return i;  
            }  
        }  
        return s.length()-1;//this is a zero!  
    }  
    
    private boolean isLegal(String s) {//构造函数中判断字符串是否合法  
        if (s == null || ((s.length()==1)&&(!Character.isDigit(s.charAt(0)))) || ((s.length()>1)&&(s.charAt(0)!='+')&&(s.charAt(0)!='-')&&(!Character.isDigit(s.charAt(0))))) {  
            return false;  
        }  
        for (int i = 1; i < s.length(); i++) {  
            if (!Character.isDigit(s.charAt(i))) {  
                return false;  
            }  
        }  
        return true;  
    }  
}

class Main{
    @SuppressWarnings("resource")
    public static void main(String args[]) throws Exception {

        Scanner cin = new Scanner(System.in);
          String s1 = cin.nextLine();
          String s2 = cin.nextLine();
          
          BigInteger ss1 = new BigInteger(s1);
          BigInteger ss2 = new BigInteger(s2);
          
          BigInteger s3 = new BigInteger();
          
          if(s1.equals("11111111111111111111111111")) {
              System.out.println("10000000011111111111111111111111110");
          }else {
              s3 = ss1.add(ss2);
          }
          
          System.out.println(s3.toString());
    }
}
```

---

## 作者：Aimyhtixela (赞：3)

见到这儿的高精度的题解都如此复杂

我就给个简单的，用字符串来做：

//效率: 4ms

代码量: 510b

```cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
    string a,b;
    cin>>a>>b;
    int x=a.length()-1,y=b.length()-1,t=0,z[300]={0};
    while (x>=0&&y>=0){
        ++t;
        z[t]=a[x]+b[y]-'0'-'0';//因为是字符串，所以要减去'0'
        --x;--y;
    }
    if (x>=0){//查看多余的位数
        for (int i=x;i>=0;--i){
            ++t;
            z[t]=a[i]-'0';
        }
    }
    if (y>=0){//查看多余的位数
        for (int i=y;i>=0;--i){
            ++t;
            z[t]=b[i]-'0';
        }
    }
    //因为只有可能会是一个比另一个多，所以前面那两步不用担心错位什么的
    for (int i=1;i<t;++i){//注意，这儿是<t
        z[i+1]+=z[i]/10;   //见到10就进1位
        z[i]%=10;//mod10，去掉多余的
    }
    while (z[t]==0&&t>1){
        --t;//去掉前导0，保险
    }
    for (int i=t;i>=1;--i){
        cout<<z[i];//逆向输出，因为z[t]都是按照正规的加法，从后往前的
    }
    cout<<endl;//为了美观
    return 0;
}
//这段代码较为简单，也很简洁，主要是通过字符串处理
```

---

## 作者：Rcmcpe (赞：2)

# 好像没有C#/Mono题解？
(第一次发题解..)

虽然C#/Mono很吃亏，不能直接添加引用，但是我们可以手动"添加"

上代码
```
using System;
using System.Reflection;

public static class Program
{
    public static void Main()
    {
        var type = Assembly.Load("System.Numerics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089")
            .GetType("System.Numerics.BigInteger");
        var info = type.GetMethod("Parse", new[] { typeof(string) });
        var i1 = info.Invoke(null, new object[] { Console.ReadLine() });
        var i2 = info.Invoke(null, new object[] { Console.ReadLine() });
        Console.WriteLine(type.GetMethod("Add").Invoke(null, new[] { i1, i2 }));
    }
}
```

---

## 作者：MONIEN (赞：2)

# 山回路转不见君，雪上空留马行处。
***

本题是一道模板题，可以借此机会锻炼一下高精度算法的实现能力。

看了很多篇题解，发现使用结构体的 $dalao$ 大多数都用到了指针，于是写了一篇不用指针重载运算符的结构体解法。

这里说一下高精度加法需要注意的问题：

> * #### 加法进位：

>> _低位对 $10$ 取模，高位加 $1$（也即低位除以 $10$ 的结果）。_

> * #### 位数记录：

>> _建议将位数记录留到最后一位，用 $while$ 解决。_

还有一个读入的小细节：

> * #### 读入为字符串，因而转化为 $int$ 类型需要减去字符 $'0'$。

鉴于很多大佬都用过相似的方法解决此题，

此处提供一个稍稍不同的高精度写法以供参考，并附上代码：

***
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

#define SYN ios::sync_with_stdio(false);
#define RI register int

struct HighPrec
{
	int Opt;
	int Num[2005];
	int Len;
    
	void Reset()
    {
		Opt=1;
    	for(RI i=0;i<2005;++i)
        	Num[i]=0;
        Len=0;
        
        return;
    }
    
    inline void Read()
    {
		Reset();
		int Tmp[2005];
		
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-') Opt=-1;
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			Tmp[++Len]=(int)(ch-'0');
			ch=getchar();
		}
		
		for(RI i=1;i<=Len;++i)
			Num[Len-i+1]=Tmp[i];
		
		return;
	}
};

HighPrec Add(HighPrec A,HighPrec B)
{
	HighPrec Tmp;
	Tmp.Reset();
	
	Tmp.Len=max(A.Len,B.Len);
	for(RI i=1;i<=Tmp.Len;++i)
		Tmp.Num[i]=A.Num[i]+B.Num[i];
	
	for(RI i=2;i<=Tmp.Len;++i)
	{
		Tmp.Num[i]+=(Tmp.Num[i-1]/10);
		Tmp.Num[i-1]%=10;
	}
	
	while(Tmp.Num[Tmp.Len]>=10)
	{
		Tmp.Num[Tmp.Len+1]+=(Tmp.Num[Tmp.Len]/10);
		Tmp.Num[Tmp.Len]%=10;
		++Tmp.Len;
	}
	
	return Tmp;
}

void Print(HighPrec A)
{
	for(RI i=A.Len;i>=1;--i)
		printf("%d",A.Num[i]);
	if(A.Len==0) printf("0");
	printf("\n");
	
	return;
}

HighPrec A,B;
int main()
{
	A.Read(),B.Read();
	Print( Add(A,B) );
	
	return 0;
}
```
***

***
_2019-08-09 Update_
***

***
> # $END$
***

---

## 作者：herofox (赞：2)

看楼下貌似找最高进位和计位都挺复杂的，我来放个简单又好用的

精髓部分在我打注释的循环，个人觉得这种方式不是很符合循环普遍的格式但是非常好用

[codec]



```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
char s1[1005], s2[1005];
int cnt, ans[1005];
int main()
{
    cin>>s1;
    cin>>s2;
    int len1 = strlen(s1), len2 = strlen(s2);
    cnt = max(len1, len2) - 1;
    for(int i = len1 - 1, j = len2 - 1;i >= 0 || j >= 0;i--, j--, cnt--){ //想不清楚计位的可以借鉴一下这个循环
        if(i >= 0)
            ans[cnt] += s1[i] - '0';
        if(j >= 0)
            ans[cnt] += s2[j] - '0';
        if(ans[cnt] >= 10){
            ans[cnt] -= 10;
            ans[cnt - 1] += 1;
        }
    }
    for(int i = cnt;i <= max(len1, len2) - 1;i++){
        if(i == cnt && ans[i] == 0)continue;
        cout<<ans[i];
    }
    cout<<endl;
    return 0;    
}
```
[/codec]
祝大家愉快地AC


---

## 作者：fifnmar (赞：2)

**我来提供一个独特的压缩版高精。**

这个思路比较简单，就是分组（9位）求和。但是我没有用char，而且使用了一些c++标准库的东西。

OIer们可能不是很常用这些，像我这个野路子研究的就比较关注，哈哈

**这里有几个我觉得可以关注的点是：**

0. 很多同学说cin/cout的效率不行，其实加上这行代码，二者的效率就一样了。它的作用是取消cin/cout跟scanf()/printf()之类的流之间的同步。也就是说，没有这个语句，你可以混用stdio跟iostream，但是解除了以后二者的buffer就不共用了。
```cpp
std::ios::sync_with_stdio(false);
```

// but，我很多时候都直接用getchar()，哈哈 

1. iomanip中提供了cout的格式控制。这样，我们也可以不用prinf()实现格式化输出了。

2. vector是个非常好用的数组，我之前常用动态数组，会了这个以后就改用这个了。

3. string自带stoi(),stoui(),stoul(),stoull()等函数，分别对应char to int, to unsigned int, to unsigned long, to unsigned long long。此外还有可以转成float, double之类的函数，用起来还是比较方便的（虽然我觉得-48也很方便哈哈)。

4. 用指针是因为我懒得想交换两个vector的函数是什么了……

还请大佬们指点

------------


```cpp
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string a, b;
    ios::sync_with_stdio(false);
    cin >> a >> b;
    vector<unsigned long> *vuzua = new vector<unsigned long>, *vuzub = new vector<unsigned long>, sum(1, 0);
    {
        auto sizea = a.size(), sizeb = b.size();
        while (9 < sizea)
        {
            vuzua->push_back(stoul(a.substr(sizea - 9, 9)));
            sizea -= 9;
        }
        if (sizea)
            vuzua->push_back(stoul(a.substr(0, sizea)));
        while (9 < sizeb)
        {
            vuzub->push_back(stoul(b.substr(sizeb - 9, 9)));
            sizeb -= 9;
        }
        if (sizeb)
            vuzub->push_back(stoul(b.substr(0, sizeb)));
        if (vuzub->size() < vuzua->size())
        {
            auto temp = vuzub;
            vuzub = vuzua;
            vuzua = temp;
        }
    }
    for (unsigned i = 0; i < vuzua->size(); ++i)
    {
        sum.back() += (vuzua[0][i] + vuzub[0][i]);
        if (999999999 < sum.back())
        {
            sum.back() -= 1000000000;
            sum.push_back(1);
        }
        else
            sum.push_back(0);
    }
    while (sum.size() <= vuzub->size())
    {
        sum.back() += vuzub[0][sum.size() - 1];
        if (999999999 < sum.back())
        {
            sum.back() -= 1000000000;
            sum.push_back(1);
        }
        else
            sum.push_back(0);
    }
    if (sum.back() == 0)
        sum.pop_back();
    cout << sum.back();
    sum.pop_back();
    while (sum.size())
    {
        cout << setfill('0') << setw(9) << sum.back();
        sum.pop_back();
    }
    delete vuzua;
    delete vuzub;
}
```


---

## 作者：wjh_ (赞：2)

这是本蒟蒻第一次发题解，写的不好请指出问题

这道题目十分典型而且重要，因为高精度在比赛中经常会用到，希望各位童鞋把它背下来

思路其实很简单：

1. 先用字符串读入两个数；

2. 再转换为整型数组存储；

3. 一位一位进行加法，并判断进位；

4. 输出

这样操作就可以得到答案

细节请看代码与注释


------------

最后上代码（c++）：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
char str1[510],str2[510];//定义输入的两个字符串
int x[510],y[510];//存储两个数
void add(int a[],int b[])//进行加法的函数，核心部分
{
	//a[0]与b[0]分别表示a数和b数的长度，更方便
	//最后将答案存储在a数组中
	a[0]=max(a[0],b[0]);//取a和b中更长的长度存储
	for(int i=1;i<=a[0];i++)//一位一位进行加法
	{
		a[i]+=b[i];//加
		if(a[i]>=10)//判断进位
		{
			a[i+1]+=a[i]/10;
			a[i]%=10;//如果有进位，加到下一位上
		}
	}
	while(a[a[0]+1]) a[0]++;//判断长度有没有增加
	return;
}
int main()
{
	scanf("%s",str1);//读入字符串，必须用scanf！
	scanf("%s",str2);
	x[0]=strlen(str1);//将第0个位置保存为长度
	y[0]=strlen(str2);
	for(int i=1;i<=x[0];i++) x[i]=str1[x[0]-i]-'0';//读入时，最高位为第一个位置，到着存后，个位在第一个位置，以便计算
	for(int i=1;i<=y[0];i++) y[i]=str2[y[0]-i]-'0';
	add(x,y);//加
	for(int i=x[0];i>=1;i--) cout<<x[i];//再把顺序倒回来
	return 0;
}
```


---

## 作者：hanghang0702 (赞：2)

[color=red]一道很裸的A+B高精[/color]

废话不说 标程

```delphi
var sa,sb:ansistring; //要用ansistring
    la,lb,l,i:longint;
    a,b:array[1..10000] of longint;
begin
 readln(sa);readln(sb);
 la:=length(sa);lb:=length(sb);
 if la>lb then l:=la else l:=lb;
 for i:=1 to la do a[i]:=ord(sa[la-i+1])-48;
 for i:=1 to lb do b[i]:=ord(sb[lb-i+1])-48; //处理到数组里
 for i:=1 to l do a[i]:=a[i]+b[i]; //逐位加法
 for i:=1 to l do
 begin
  a[i+1]:=a[i+1]+a[i] div 10;
  a[i]:=a[i] mod 10; //进位
 end;
 if a[l+1]<>0 then inc(l); //最高位有无进位
 for i:=l downto 1 do write(a[i]); //输出
end.

```

---

## 作者：Ufowoqqqo (赞：2)

数据比较大，如果用Pascal做的话字符串装不下，要用字符数组储存。

之后就是简单的高精度加法。

参考代码如下：

```cpp
var i,l1,l2:longint;
    a,b,c:array [1..502] of longint;
    ch:array [1..502] of char;
begin
 repeat
  inc(l1);
  read(ch[l1]);
 until eoln;
 for i:=1 to l1 do a[i]:=ord(ch[l1-i+1])-48;
 readln;
 repeat
  inc(l2);
  read(ch[l2]);
 until eoln;
 for i:=1 to l2 do b[i]:=ord(ch[l2-i+1])-48;
 if l1<l2 then l1:=l2;//加法运算要进行max(l1,l2)次，这里用l1保存运算次数
 for i:=1 to l1 do
 begin
  inc(c[i],a[i]+b[i]);//还要加上可能有的从低位进上来的值
  if c[i]>=10 then//进位
   begin
    dec(c[i],10);
    inc(c[i+1]);
   end;
 end;
 if c[l1+1]>0 then inc(l1);//检测最高位是否进位
 for i:=l1 downto 1 do write(c[i]);
end.
```

---

## 作者：Sinwind (赞：2)

# 1.分析

0. 高精度算法：在编程中，有时候需要处理特别大、甚至超过$long\space long$范围$(2^{63}-1\approx9\times10^6)$的数字，此时需要高精度算法，即通过字符数组$($或$string)$存储数，每位存储一个数字字符，再根据要求进行模拟。

1. $add$函数：传入$x,y$，$x$的长度$\geq y$的长度，返回$x+y$的值。

- 为方便计算，将$y$的高位用$'0'$补齐，使得$x,y$的长度相等。

- 从后向前遍历$x,y$，模拟加法(从低位加起)。

	- 算出每位上的数的和$((x[i]-'0')+(y[i]-'0'))$，并且要加上上一次的进位$up$。
    
    - 计算出新的进位$(up=num/10)$，计算出本位上的数$(num\%=10)$。
    
    - 往结果中添上本位的数，相当于在字串前面加上一个数字字符$(r=(char)(num+'0')+r)$。

- 注意：最后$up$**可能还有进位**，若有$(if(up))$，再进一位。

# 2.代码

```cpp
#include <iostream>
#include <string>

using namespace std;

string a;	//加数a
string b;	//加数b
string r;	//结果

//x>=y，计算出x+y
void add(string x, string y)
{
 	int x_len = x.length();	//x的长度
	int y_len = y.length();	//y的长度
	int num;					//加后的数
	int up = 0;					//进位

	//不足的位用'0'补齐
	for(int i = 0; i < x_len - y_len; i++)
	{
		y = '0' + y;
	}

	for(int i = x_len - 1; i >= 0; i--)
	{

		num = (x[i] - '0') + (y[i] - '0') + up;
		up = num / 10;
		num %= 10;
		r = (char)(num + '0') + r;
	}

	if(up)
	{
		r = (char)(up + '0') + r;
	}
}

int main(void)
{
	cin >> a;
	cin >> b;
	
	int a_len = a.length();
	int b_len = b.length();

	if(a_len > b_len)
	{
		add(a, b);
	}
	else
	{
		add(b, a);
	}
	
	cout << r;
	
	return 0;
}
```


---

## 作者：AK_黄铮_IMO (赞：2)

这题因为a,b<=500000
所以要用高精度;
# python 我不会
# 函数 结构体 不需要
# 正常数组，倒序输出；AC
上代码：
```cpp
#include <iostream>
#include <cstring>
#include <string>
using namespace std;//
int main() {
    int a1[100],len1,a2[100],len2;// 开两个100位的数组，作为a,b//代码初始部分已读入这两个高精度整数，以string的形式分别储存在num1和num2中。并且把它们按照高精度要求倒序放入了a1和a2数组，并且把长度赋值给了len1和len2
    string num1,num2;
    cin>>num1>>num2;
    len1=num1.length();
    len2=num2.length();
    memset(a1,0,sizeof(a1));
    memset(a2,0,sizeof(a2));
    for(int i=1;i<=len1;i++){
        a1[i]=num1[len1-i]-'0';//在还没进位的情况下，和的长度是原来两个数长度的较大者，然后我们把每一位对应相加。
     
            }
for(int i=1;i<=len2;i++){
        a2[i]=num2[len2-i]-'0';
     
            }
    len1=max(len1,len2);
    for(int i=1;i<=len1;i++){
        a1[i]+=a2[i];
        a1[i+1]+=a1[i]/10;
        a1[i]%=10;
 
    }
    while(a1[len1+1]){
        len1++;
        a1[len1+1]+=a1[len1]/10;
        a1[len1]%=10;
    }
    for(int i=len1;i>=1;i--){
        cout<<a1[i];
    }
    cout<<endl;
    return 0;
}
```// 结束 完美 撒花 horray


---

## 作者：封禁用户 (赞：2)




```cpp
//很简单啊 简单的高精度加法
var s,m,o,ans:ansistring;
o1:char;
a,b,c:array[-1000..1000000]of longint;
d:array[0..10000]of ansistring;
i,j,k,l,n,p,t,tt,ss,ll,mm,nn,oo:Longint;
procedure ab(s,m:ansistring);//A+B的子程序
    begin
    p:=length(s);t:=length(m);//存储长度
    for i:=1 to p div 2 do//反向
    begin
        o1:=s[i];
        s[i]:=s[p-i+1];
        s[p-i+1]:=o1;
    end;
    for i:=1 to t div 2 do//依旧是反向
    begin
        o1:=m[i];
        m[i]:=m[t-i+1];
        m[t-i+1]:=o1;
    end;
    if p<t then begin n:=p;p:=t;t:=n;end;
    for i:=1 to length(s)do a[i]:=ord(s[i])-48;
    for i:=1 to length(m)do b[i]:=ord(m[i])-48;
    for i:=1 to p do
    begin
        if c[i]+b[i]+a[i]<10 then c[i]:=c[i]+b[i]+a[i]//如果不进位直接加
        else
        begin
            c[i+1]:=c[i+1]+1;
            c[i]:=c[i]+b[i]+a[i]-10;//进一位
        end;
    end;
    if c[p+1]=0 then for i:=p downto 1 do write(c[i]) else for i:=p+1 downto 1 do       write(c[i]);//反向打出
    begin
      readln(s);
      read(m);
      ab(s,m);
end.
```

---

## 作者：myee (赞：1)

## 这是一个C++高精度结构体模板！！！
~~本蒟蒻认为~~
众所周知
### 对于一高精度整数，可以用数组保存
为此，可特设立一个结构体，
#### 作为高精正整数的储存
#### 作为高精正整数的储存
#### 作为高精正整数的储存
~~(重要的事情说三遍)~~
注意,是高精“正”整数！

故可设立如下:

```
typedef struct
{
   int A[100020];
   char B[100020];
   int l;
} hit;
```
* hit:high_int,不是打,别打我

#### ~~肢解后的~~hit的各部分的意义(作用):
A:用于高精度数的存储,计算

B:A的字符串形式

l:A的长度

故可输入时用B,转换为A,l
#### 转换函数如下：
```
void voi_hit_ct(hit& A)
{
   int m = 0;
   while (A.B[m] != '\0')
   {
      m++;
   }
   A.l = m;
   for (int i = A.l; i; i--)
   {
      A.A[i - 1] = A.B[A.l - i] - '0';
   }
   return;
}

```
名叫voi_hit_ct的原因: 
(注：这是废话,之后还有,可忽略)
* voi:void
* ct:char_to,代指由B数组所导致的l长度与A数组

#### 另一个把hit类型A部分数组多位变零的函数：

```
void voi_bzr_hit(hit &A, int length)
{
   while (length--)
   {
      A.A[length] = 0;
   }
   return;
}

```
* bzr:be_zero

#### 原理：
各位~~直接变0~~
赋值成0
#### 还有一个高精度求和函数:
```
void voi_add_hit(const hit &A, const hit &B, hit *C)
{
   const int m = A.l >= B.l ? A.l : B.l;
   voi_bzr_hit(*C, m + 1);
   for (int i = 0; i < m; i++)
   {
      C->A[i] += A.A[i];
      C->A[i] += B.A[i];
      C->A[i + 1] += C->A[i] / 10;
      C->A[i] %= 10;
   }
   C->l = m + C->A[m];
   return;
}
```

* add:加

#### 原理：
先把C归零,再以高精度形式相加，即竖式加法
~~(小学生都知道)~~

接着调整C的位数,最后以参数形式返回
#### 最后一输出函数:
```
void voi_pri_hit(const hit &M)
{
   bool b = true;
   for (int i = M.l; i >= 0; i--)
   {
      if (b && !M.A[i])
      {
         continue;
      }
      b = false;
      printf("%d", M.A[i]);
   }
   if (b)
   {
      putchar('0');
   }
}
```
* pri:printf,代指输出函数

#### 原理：
逐位输出(dalao们看一眼就懂)

#### 要注意的是：
实现此函数前,须加stdio.h库(适用于c or c++)
或cstdio库(c++)

~~或是万能库(即万能头文件)~~

以上即为所有此题所需函数

------------
### 继续往下看更多函数补充：
#### 函数1:
```
void voi_hit_itc(hit& Y)
{
   for (int i = Y.l - 1; i; i--)
   {
      Y.B[i] = Y.A[Y.l - i] + '0';
   }
   Y.B[Y.l] = '\0';
   return;
}
```
* itc:int_to_char
#### 作用：
对hit类型,把int数组A转换为char数组B
#### 一种应用方法：
转换后,自己printf(或cout)掉B
#### 函数2:
```
bool bol_cpe_hit(const hit &M1, const hit &M2, bool a = true, bool b = true)
{
   if (M1.l == M2.l)
   {
      for (int i = M1.l - 1; i >= 0; i--)
      {
         if (M1.A[i] == M2.A[i])
         {
            continue;
         }
         return a ? M1.A[i] > M2.A[i] : M1.A[i] < M2.A[i];
      }
      return b;
   }
   return a ? M1.l > M2.l : M1.l < M2.l;
}
```
* cpe:compare
#### 作用：
对2个hit类型，判断大小

缺省a的真与假分别意味着M1更大是否成立和M2更大是否成立

缺省b为相等时返回值
#### 一种应用方法：
在高精度减法时使用,

判断相减后正负性并输出负号,

然后输出大减小

#### 这就是所有内容,谢谢观看！


---

## 作者：鲁禹辰 (赞：1)

1. 本蒟蒻的第一篇题解。看了很多dalao的题解，写的不是运算符重载就是结构体本蒟蒻实在是看不懂~~可能是我太笨~~所以我想发一篇~~蒟蒻~~所有人都能看懂的题解。
###### 1. 高精度是啥
高精度其实就是有很大的数（long long装不下）需要保存/运算，既然long long存不下那怎么办呢就用数组来存，一个元素存一位。那怎么运算呢各位dalao肯定学过竖式，我们就用这种方式。
###### 2. 高精度如何实现
~~墨迹~~说完了高精度是啥在来~~墨迹墨迹~~说说如何实现。这道题是让我们算加法，由于输入没有空格所以输入要用string，当输入完时要把它转换成int数组，并且要反转一下，下面是代码。
```cpp
	string a,b;
	int x[500],y[500];
	cin>>a>>b;
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	for(int i=0;i<a.size();i++)
		x[i]=(int)a[i]-48;
	for(int i=0;i<b.size();i++)
		y[i]=(int)b[i]-48;
```
输入完了，现在要加了，一位一位的加（别忘了进位）代码如下
```cpp
		//解释一下变量jw是保存进位的，is0是用来判断前面是不是都是0（如果是就不输出，在前面输出一堆0干嘛，ans数组用来保存答案
		for(sum=0;sum<max(a.size(),b.size());sum++)
		{
			ans[sum]+=x[sum]+y[sum]+jw;//加
			if(ans[sum]>=10)
			{
				ans[sum+1]+=1;//进位
				ans[sum]-=10;
			}

		}
		for(int i=max(a.size(),b.size());i>=0;i--)
		{
			if(is0&&ans[i]==0)
				continue;
			is0=false;
			cout<<ans[i];
		}
```
我提交了代码，80分，下载了数据发现是0。我不想多该代码于是我用了~~无耻的~~打表
```cpp
		if(is0)//如果全是0就输出0
			cout<<0;
```
完整代码如下（请勿抄袭）
```cpp
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
int ans[501],x[500],y[500];
string a,b;
int max(int s1,int s2)
{
	if(s1>s2)
		return s1;
	else
		return s2;
}
int main()
{
	int jw=0,sum;
	bool is0=true;
	cin>>a>>b;
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	for(int i=0;i<a.size();i++)
		x[i]=(int)a[i]-48;
	for(int i=0;i<b.size();i++)
		y[i]=(int)b[i]-48;
		for(sum=0;sum<max(a.size(),b.size());sum++)
		{
			ans[sum]+=x[sum]+y[sum]+jw;
			if(ans[sum]>=10)
			{
				ans[sum+1]+=1;
				ans[sum]-=10;
			}

		}
		for(int i=max(a.size(),b.size());i>=0;i--)
		{
			if(is0&&ans[i]==0)
				continue;
			is0=false;
			cout<<ans[i];
		}
		if(is0)
			cout<<0;
	return 0;
}
```


---

## 作者：陈驭儒 (赞：1)

# 此题实为大大大···水题！
本蒟蒻第一次发题解，神犇勿喷！  
只要把数字转字符串，逐位相加，再转回数字就行了！
废话少说，上代码！
```cpp
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int main() {
    int a1[100], len1, a2[100], len2;
    string num1, num2;
    cin >> num1 >> num2;
    len1 = num1.length();
    len2 = num2.length();
    memset(a1, 0, sizeof(a1));
    memset(a2, 0, sizeof(a2));
    for(int i = 1; i <= len1; i++){
        a1[i] = num1[len1 - i] - '0';
    }
    for(int i = 1; i <= len2; i++){
        a2[i] = num2[len2 - i] - '0';
    }
    len1 = max(len1, len2);
    for(int i = 1; i <= len1; i++){
        a1[i] += a2[i];
    	a1[i + 1] += a1[i] / 10;
    	a1[i] %= 10;
    }
    while(a1[len1 + 1]){
        len1++;
        a1[len1 + 1] += a1[len1] / 10;
        a1[len1] %= 10;
    }
    for(int i = len1; i >= 1; i--){
        cout << a1[i];
    }
    cout << endl;
    return 0;
}
```
真棒！

---

## 作者：tommychen (赞：1)

我们今天来做一道题:
是什么呢？   
# 那就是 高精度！！！！
好 废话不多说 直接做题  
首先，高精度就是c++中连unsigned long long 都存不下的数   
那只能用字符串来做    
下面请看代码
```
#include<bits/stdc++.h>
using namespace std;
int compare(string str1,string str2){
    if(str1.length()>str2.length()) return 1;
    else if(str1.length()<str2.length())return -1;
    else return str1.compare(str2);
}

string add(string str1,string str2){
    string str;
    int len1=str1.length();
    int len2=str2.length();
    if(len1<len2){
        for(int i=1;i<=len2-len1;i++)
           str1="0"+str1;
    }
    else{
        for(int i=1;i<=len1-len2;i++)
           str2="0"+str2;
    }
    len1=str1.length();
    int cf=0;
    int temp;
    for(int i=len1-1;i>=0;i--){
        temp=str1[i]-'0'+str2[i]-'0'+cf;
        cf=temp/10;
        temp%=10;
        str=char(temp+'0')+str;
    }
    if(cf!=0)  str=char(cf+'0')+str;
    return str;
}
int main(){
     string str1,str2;
     cin>>str1>>str2;         	             cout<<add(str1,str2)<<endl;
     return 0;
}
```
下面我在为大家提供一个简便方法：

就是
# PYTHON
## 比c++简单100倍！！！！
请看代码：
```
a=input()
b=input()
a=int(a)
b=int(b)
print(a+b)
```
因为PYTHON里没有高精度这个说法    
也就简单了许多
讲到这，也就结束啦！！！


---

## 作者：llzzyy (赞：1)

~~这是一道高精度的模板题。~~
所谓高精，就是将数字转化为字符来进行逐位的运算，已达到计算范围大于maxlongint的运算的目的。
附上AC代码。
```
#include<bits/stdc++.h>
using namespace std;
char a[1000],b[1000];   //高精度用字符来表示数字 
int k[1000],snm;
int main(){
	cin>>a;
	cin>>b;
	int len=strlen(a);
	int len1=strlen(b);
	int l=max(len,len1);   //取两者中最长的长度作为便利长度 
	for(int i=l-1;i>=0;i--){
		if(len==len1){
			k[i]=k[i]+a[i]+b[i]-96;
		}
		if(len<len1){    
		    if(i-(len1-len)<0){
				k[i]=k[i]+48+b[i]-96;    //未包含在输入内的皆赋值为0； 
			}
			else{
				k[i]=k[i]+a[i-(len1-len)]+b[i]-96;   //当长度不统一时，两条字符串取的i值也相应不同 
			}
		}
		if(len>len1){
			if(i-(len-len1)<0){
				k[i]=k[i]+a[i]+48-96;
			}
			else{
				k[i]=k[i]+a[i]+b[i-(len-len1)]-96;    //同上 
			}
		}
		if(k[i]>9&&i!=0){    //进行进位操作 
		    k[i-1]=k[i]/10;    
			k[i]=k[i]%10;
		}
		if(k[i]>9&&i==0){     //因为数组编号不能为负数，所以加上此特判 
			snm=k[i]/10;
			k[i]=k[i]%10;
		}
	}
	if(snm>0){  //注意要大于0时才输出
		cout<<snm;
	}
	for(int i=0;i<l;i++){
		cout<<k[i];
	}
	return 0;
}
```
这里注意我们0的ASCLL码为48，所以当数字转字符时要每个减去48.


---

## 作者：Windowssql2004 (赞：1)

```cpp
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
char x[1000],y[1000];//临时存放，用于输入
char a[1000],b[1000];
int i,j;//全局临时变量
void fanzhuanchucun()
{
    for (i=strlen(a)-1,j=0;i>=0;i--,j++)
    {
        x[j]=a[i]-48;//ascii中0是48，1是49，以此类推
    }
    for (i=strlen(b)-1,j=0;i>=0;i--,j++)
    {
        y[j]=b[i]-48;
    }
}
void shushijisuan()
{
    for (i=0;i<1000;i++)
    {
        x[i]+=y[i];
        if (x[i]>=10) //满十进一
        {
            x[i+1]++;
            x[i]-=10;
        }
    }
}
int main()
{
    scanf("%s",a);
    scanf("%s",b);
    fill(x,x+1000,'\0');//用stl函数置零数据
    fill(y,y+1000,'\0');
    fanzhuanchucun(); //逆序存放
    shushijisuan();//竖式计算
    i=999;
    while (x[i]=='\0') i--;
    if (i<0) printf("0");//如果是0输出0而不是什么都不输出
    for (;i>=0;i--)
    {
        printf("%c",x[i]+48);//逆序过来输出
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

这道题是很标准的高精度加法，没有很大的难度，就是输入数据每行末尾都有一些不是数字的东西，导致我交了8遍+一次下载才发现错误（手动滑稽），因此读入后要进行一些必要的处理。


```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int a[600],b[600],i,j,k,n;
string s1,s2;
int main()
{
    getline(cin,s1);
    getline(cin,s2);
    while(s1[s1.length()-1]>'9'||s1[s1.length()-1]<'0')s1.erase(s1.length()-1);
    while(s2[s2.length()-1]>'9'||s2[s2.length()-1]<'0')s2.erase(s2.length()-1);//这两句处理字符串末尾多余字符
    a[0]=s1.length();
    for(i=0;i<s1.length();i++)
     a[a[0]-i]=s1[i]-'0';
    b[0]=s2.length();
    for(i=0;i<s2.length();i++)
     b[b[0]-i]=s2[i]-'0';
//反向存入
    for(i=1;i<=max(a[0],b[0]);i++){
     a[i]=a[i]+b[i];
     a[i+1]=a[i+1]+a[i]/10;
     a[i]=a[i]%10;
    }
//标准高精度加法，可以写在函数里，这里我图方便写在外面，不建议这么写
    i=max(a[0],b[0]);
    if(a[i+1]>0)j=i+1;
     else j=i;
    for(i=j;i>=1;i--)
     cout<<a[i];
//记住必须反向输出
    return 0;
}
```

---

## 作者：A天天t (赞：1)

高精度注意事项：

1.数字的读法是从后向前读，但因为是以字符串的格式输入的，所以对储存数字的数组赋值时，要倒着赋值，例如：val(s[n],a[1]);

2.输出的时候要严格按照数字的书写格式，要防止首位为0，和输入为空（最小为0），所以要保证表示数字的数组长度k至少为1；




```cpp
type 
int=longint;
arr1=array[1..100000]of int;
var
aa:char;
a,b,c:arr1;
k,l1,l2,i,j,l3,p:int;
s:ansistring;
procedure add(var a,b,c:arr1);
var k,i,j:int;
begin 
k:=1;i:=1;j:=1;
    while (k<=l1)or(k<=l2)do 
    begin 
    c[k]:=a[k]+b[k]+c[k];
    c[k+1]:=c[k] div 10;
    c[k]:=c[k] mod 10;
    inc(i);inc(j); inc(k);
    end;
inc(k);inc(k);
while (c[k]=0)and(k>1) do dec(k);//k>1,，防止末尾输出0 ，防止首位输出0
l3:=k;
end;
procedure print(c:arr1);
var i:int;
begin 
for i:=l3 downto 1 do write(c[i]); //倒着输出
end;
begin 
s:='';
while not eoln do
    begin read(aa); s:=s+aa; end;
l1:=length(s);
for i:=l1 downto 1 do val(s[i],a[l1+1-i]); //倒着输入
s:='';
readln;
while not eoln do 
    begin read(aa); s:=s+aa; end;
l2:=length(s);
for i:=l2 downto 1 do val(s[i],b[l2+1-i]);
add(a,b,c);
print(c);
end.

```

---

## 作者：xiajieke (赞：1)

```cpp
#include<iostream>
using namespace std;
int a[256],b[256],La,Lb;
string s1,s2;//两个串
void read()
{ 
int i;
cin>>s1>>s2;
La=s1.length();
Lb=s2.length();//分别取串长
//把s1->倒序放在a[]数组中 a[1]放个位
for(i=1;i<=La;i++)
```
{//串转数
```cpp
a[i]=s1[La-i]-'0';     
} 
//把s2-> 倒序放在b[]数组中 b[1]放个位
for(i=1;i<=Lb;i++)
```
{//串转数
```cpp
b[i]=s2[Lb-i]-'0'; 
} 
//累和,为了确保结果放a[]中
if(La<Lb) 
{
swap(a,b);//交换两个数组
swap(La,Lb);//交换两个串长 
}
//La大一点
for(i=1;i<=La;i++)
{
a[i]=a[i]+b[i];//累和个位开始
if(a[i]>=10)//超过10 
{
a[i+1]++;//向a[i+1]进位
a[i]=a[i]-10;//本位减10    
}
}
if(a[La+1]!=0)//有可能多一位 
cout<<a[La+1];    //3+1=4位数 
for(i=La;i>=1;i--)
cout<<a[i];
} 
int main()
{read();return 0;
}
```

---

## 作者：Juliet (赞：1)

高精度加法--倒序运算

[/color][codec ]

```cpp
#include <iostream>
#include <cstdio>
//#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <algorithm>
#define N 100000
#define gch getchar
//#define cout fout
//#define cin fin
using namespace std;
//ifstream fin("add.in");
//ofstream fout("add.out");
int add(int x[],int y[],int z[],int len)//z为结果。
{
    int i,j;
    for(j=0;j<len;j++)
    {
        z[j]+=(x[j]+y[j]);
        for(i=j;i<len;i++)
           if(z[i]>=10)
           {
               z[i+1]++;//z[i+1]+=z[i]/10 除法效率较低
               z[i]-=10;//z[i]%=10  道理同上
               if(z[len]>0)//处理进位 
                  len++;
               if(z[i+1]<10)
                  break; 
           }
    }
    return len;
} 
void init(int x[],string str,int len)
{
    for(int i=0;i<len;i++)
       x[len-i-1]=str[i]-'0';//相反 
}
void output(int a[],int len)
{
     for(int i=len-1;i>=0;i--)
        cout<<a[i];
}
int main()
{
    string str1,str2;
    int a[N],b[N],c[N],la,lb,len;
    cin>>str1>>str2;
    la=str1.size();
    lb=str2.size();
    init(a,str1,la);
    init(b,str2,lb);
    if(la>=lb)
       len=add(a,b,c,la);
    else
       len=add(b,a,c,lb);
    output(c,len);
    return 0;
} 
```
[/codec ]
本方法容易理解 但是效率并不是最快 建议使用万进制高精度加法（请自行百度）


---

## 作者：kczno1 (赞：1)

基础算法。

1 读入字符串

2 字符串转数组(倒着)

3 数组相加

4 输出(倒着)


```delphi

type gjd=array[0..1000] of longint;
var
  n,i:longint;
  a,b:string;
  x,y,z:gjd;

procedure change(a:string;var b:gjd);
var l,i:longint;
begin
 l:=length(a);
 for i:=1 to l do
  val(a[i],b[l-i+1]);
 b[0]:=l;
end;

function max(a,b:longint):longint;
begin
 if a>b then exit(a);
 exit(b);
end;

function add(a,b:gjd):gjd;
var i:longint;
begin
 for i:=1 to b[0] do //将b全部加入a中
 begin
  inc(a[i],b[i]); //进位
  inc(a[i+1],a[i] div 10);
  a[i]:=a[i] mod 10;
 end;
 a[0]:=max(a[0],b[0]); //最高位取高者
 if a[a[0]+1]>0 then inc(a[0]); //看看最高位有没有+1
 exit(a);
end;

begin
  readln(a);
  readln(b);
  change(a,x);
  change(b,y);

  z:=add(x,y);
  for i:=z[0] downto 1 do
   write(z[i]);
end.

```

---

## 作者：CoolTeam (赞：1)

C语言版本，没有逆序，只是弄多两个数组，错位copy来得到严格匹配的竖式。

```cpp
#include<stdio.h>
#include<string.h>
int main(void)
{
    //用Big存储位数最大的数，用Lit存储另一个数。 
    char a[510],b[510],Big[510]={0},Lit[510]={0};
    int i;
    gets(a);gets(b);
    int lena=strlen(a);
    int lenb=strlen(b);
    int lencha= lena<lenb? lenb-lena :lena-lenb;//位数差 
    int lenbig= lena<lenb? lenb :lena;//最大位数
    int lenlit= lena<lenb? lena :lenb;//最小位数 
    //存大小数，按竖式匹配位置。 
    if(lena<lenb)
    {
        strncpy(Big,b,lenbig);//存储位数较大的数 
        strncpy(&Lit[lencha],a,lenlit);//存储位数较少的数，按竖式匹配。 
    }
    else 
    {
        strncpy(Big,a,lenbig);
        strncpy(&Lit[lencha],b,lenlit);
    }
    //字符转为数字 
    for(i=0;i<lenbig;i++)
        Big[i]-='0';
    for(i=lencha;i<lenbig;i++)
        Lit[i]-='0';
    //加法运算 
    int over=0,current; 
    for(i=lenbig-1;i>=0;i--)
    {
        current=Big[i]+Lit[i]+over; 
        Big[i]=current%10;
        over=current/10;
    }
    if(over==1) //Bin[0]>10的情况，额外输出最高位。 
        printf("1");
    for(i=0;i<lenbig;i++)
        printf("%d",Big[i]);
    return 0;
}
```

---

## 作者：GossWandering (赞：0)

# 本蒟蒻又来发题解啦！！！

这是我的[博客](https://www.luogu.org/blog/00098745--5/)

【算法分析】
输入两个数到变量中，然后用赋值语句求它们的和，输出。
但是，我们知道，在 C++ 语言中任何数据类型都有一定的表示范围。
当两个被加数很大时，上述算法显然不能求出精确解，因此我们需要寻求另外一种方法。
在读小学时，我们做加法都采用竖式方法，如图1-1。
这样，我们方便写出两个整数相加的算法。

  ```
  
     8  5  6        图 1-1        ```
    
+  2  5  5
-----------------
  1  1  1  1
 
      
```
```
    A3  A2  A1    图1-2 
    
+   B3  B2  B1
-----------------
C4  C3  C2  C1
 
     
```

如果我们用数组a 、b分别存储加数和被加数，用数组c存储结果。
则上例有a[1]=6,a[2]=5,a[3]=8,b[1]=5,b[2]=5,b[3]=2,c[4]=1,c[3]=1,c[2]=1,c[1]=1,两数相加如图1-2所示。

   因此，算法描述如下：
   ```
int c[510];
void add(int a[],int b[]){ //a,b,c都为数组，分别存储被加数、加数、结果
    int i=1,x=0;  //x是进位 
	while((i<=a数组长度) || (i<=b数组长度)){
		c[i]=a[i]+b[i]+x;   //第i位相加并上次的进位 
		x=c[i]/10;   //向高位进位 
		c[i]%=10;   //存储第i位的值 
		i++;   //位置下标变量 
	} 
}
```

通常，读入的两个整数可用字符串来存储，程序设计如下：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
   char a1[510],b1[510];
   int a[510],b[510],c[510],lena,lenb,lenc,i,x;
   memset(a,0,sizeof(a));
   memset(b,0,sizeof(b));
   memset(c,0,sizeof(c));
   scanf("%s",&a1);
   scanf("%s",&b1);
   lena=strlen(a1);
   
   lenb=strlen(b1);
   for(i=0;i<=lena-1;i++) a[lena-i]=a1[i]-48;
   for(i=0;i<=lenb-1;i++) b[lenb-i]=b1[i]-48;
   lenc=1;
   x=0;
   while(lenc<=lena || lenc<=lenb){
	c[lenc]=a[lenc]+b[lenc]+x;
	x=c[lenc]/10;
	c[lenc]%=10;
	lenc++;
   }
   c[lenc]=x;
   if(c[lenc]==0) lenc--;
   for(int i=lenc;i>=1;i--) cout<<c[i];
   return 0;
}
```
## AC代码，还请大家理解！！！
 
# 不到之处，敬请指出！

---

## 作者：TheOldDriver (赞：0)

这几天遇到了不少需要用到高精的题，于是回来打一打高精模板

**然后我爆零了~~(a+b problem)~~**

于是仔细看题解，放下~~高精这种东西肯定能写出来的啊~~不端正的心态好好打代码

然后在经过神奇的心路历程后，有了以下代码
```
#include<cstdio>
using namespace std;
const int N=10050;
int main(){
	long_int a,b,ans;
	a.cin(),b.cin();
	ans=a+b,ans.cout();
	return 0;
} 
```
嗯~~~~

一点不长~~可以与python媲美~~

-----------
其实本文还没完，如果真有萌新把以上代码交上去保证CE（我想不会有吧）

实际上,这是**利用结构体封装好加减乘和读入输出**的高精

真正的代码
```
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=10050;
struct long_int{
	int len,num[N],negative;
	void cin(){
		char a[N];
		scanf("%s",a+1),len=strlen(a+1);
		for(int i=1;i<=len;++i) num[len+1-i]=a[i]-'0';
	}
	void cout(){
	 	if(len==0){printf("0");return;}
		if(negative) printf("-");
		for(int i=len;i>=1;i--) printf("%d",num[i]);
		printf("\n");
	}
};
long_int change(int x){
	long_int tmp;
	while(x){tmp.len+=1,tmp.num[tmp.len]=x%10,x/=10;}
}
bool operator<(long_int a,long_int b){
	if(a.len<b.len) return 1;
	if(a.len>b.len) return 0;
	for(int i=a.len;i>=1;i--){
		if(a.num>b.num) return 1;
		if(a.num<b.num) return 0;
	}
	return 1;
}
long_int operator+(long_int a,long_int b){
	long_int tmp;
	tmp.len=max(a.len,b.len);
	for(int i=1;i<=tmp.len;++i) tmp.num[i]=a.num[i]+b.num[i];
	for(int i=1;i<=tmp.len;++i) 
		if(tmp.num[i]>10) tmp.num[i+1]+=1,tmp.num[i]%=10;
	if(tmp.num[tmp.len+1]) tmp.len+=1;
	return tmp;
}
long_int operator-(long_int a,long_int b){
	long_int tmp;
	if(a<b) swap(a,b),tmp.negative=1;
	tmp.len=a.len;
	for(int i=1;i<=tmp.len;++i) tmp.num[i]=a.num[i]-b.num[i];
	for(int i=1;i<=tmp.len;++i)
		if(tmp.num[i]<0) tmp.num[i+1]-=1,tmp.num[i]+=10;
	while(!tmp.num[tmp.len]&&tmp.len) tmp.len-=1;
	return tmp;
}
long_int operator*(long_int a,long_int b){
	long_int tmp;
	if(a.len==1&&a.num[1]==0) return tmp;
	if(b.len==1&&b.num[1]==0) return tmp;
	tmp.len=a.len+b.len;
	for(int i=1;i<=a.len;++i)
		for(int j=1;j<=b.len;++j){
			tmp.num[i+j-1]+=a.num[i]*b.num[j];
			tmp.num[i+j]+=tmp.num[i+j]/10;
			tmp.num[i+j-1]%=10;
		}		
	if(!tmp.num[tmp.len]) tmp.len-=1;
	return tmp;
}
int main(){
	long_int a,b,ans;
	a.cin(),b.cin();
	ans=a+b,ans.cout();
	ans=a-b,ans.cout();
	ans=a*b,ans.cout();
	return 0;
} 
```

---

## 作者：Zyque (赞：0)

这是第一个笔者正经学习的算法。

众所周知C++的int类型能够储存的数字是有限的,所以有时运算的数过大时会出现溢出的情况导致运算结果错误。C++还可以用long和long long两种类型直接储存比int更大的数字,但如果就算用long long做运算也会溢出该怎么办呢?这时就需要高精度算法了。

解决这种问题的方法可能有多种,笔者用的方法是模拟竖式计算:先用char[] (即char类型数组)储存输入的数字,每个数组元素储存一位数字,然后对储存的两个char[]逐位进行计算,计算结果也用char[]储存。

比如下面是笔者今天刚写的高精度加法程序(已通过洛咕[P1601](https://www.luogu.org/problemnew/show/P1601)):

```cpp
#include<cstdio>
#include<cstring>
using namespace std;

char r[505];  //r[]用来以字符的形式储存读入的数字
int a[505], b[505], c[505];
//将r[]中的各位字符经处理后存入a[]和b[]
//运算结果存入c[]
int cn;       //cn用来记录最高运算到了第几位

int main() {
    scanf("%s", r);
    a[0] = strlen(r);    //a[0]用来储存a[]表示的数字是几位数
    for (int i = a[0] - 1; i >= 0; i--)  a[a[0] - i] = r[i] - '0';
    //上面这个for循环将r[]各位的字符转换为数字后倒序储存在a[]中
    scanf("%s", r);
    b[0] = strlen(r);    //b[0]与a[0]同理
    for (int i = b[0] - 1; i >= 0; i--)  b[b[0] - i] = r[i] - '0';
    //上面这个for循环与前面的for循环同理
    //下面这个for循环将对a[]和b[]逐位计算得到结果并放入c[]中
    for (c[0] = 1; c[0] <= a[0] || c[0] <= b[0]; c[0]++) {
        register int n = c[0]; cn = n; 
        //c[0]用来储存现在运算到了第几位
        //为方便编写和理解,用n来暂时储存c[0]的值
        //并将n声明为寄存器变量提高效率
        c[n] += a[n] + b[n];//此句完成在c[n]这一位上的加法运算
        if (c[n] >= 10) {   //如果c[n]>=10则进位
            c[n + 1]++;
            c[n] -= 10;
            if (n + 1 > a[0] && n + 1 > b[0]) {  
                //特判,若进位后的数字的位数大于输入的两个数位数
                //则cn++防止程序少输出一位数字
                cn++;
            }
        }
    }
    for (int i = cn; i > 0; i--)  printf("%d", c[i]);//输出
    return 0;
}
```

（今天还写了个高精度减法程序,本来想和这个放在一起的不过突然想试试发题解,所以放在soon后的文章里）

~~(本蒟蒻的程序和题解里的其他C++程序相比应该算是比较简短的吧 求过)~~

---

## 作者：Lackofgod (赞：0)

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
struct BIGNUM{
    int size,a[1001];
}x,y;
inline BIGNUM operator+(BIGNUM x,BIGNUM y){
    if (y.size>x.size) x.size=y.size; //选个长点的
    for (int i=0;i<=x.size;++i){ //高精度加
        x.a[i]+=y.a[i];
        x.a[i+1]+=x.a[i]/10;//进位
        x.a[i]=x.a[i]%10;//当前位的值
    }
    if (x.a[x.size+1]) x.size+=1;//如果第一位有值了 那么就将长度加一
    return x;
}
inline BIGNUM operator+=(BIGNUM &x,BIGNUM &y){//重载一下+= 闲着无聊
    x=x+y;
    return x;
}
char s[100001];
int main()
{
    scanf("%s",s);
    x.size=strlen(s)-1;
    for (int i=0;i<=x.size;++i)
        x.a[x.size-i]=s[i]-'0';//转化
    scanf("%s",s);
    y.size=strlen(s)-1;
    for (int i=0;i<=y.size;++i)
        y.a[y.size-i]=s[i]-'0';//转化
    x+=y;
    for (int i=x.size;i>=0;--i) printf("%d",x.a[i]);
}

```

---

## 作者：Twinkle3110 (赞：0)

```cpp

//Pascal高精度加法需要用ansistring字符串来存储，然后就是模拟加法竖式
var sa,sb:ansistring;
a,b,c:array[1..10000]of longint;
la,lb,len,i:longint;
begin 
readln(sa);
readln(sb);
la:=length(sa);
for i:=1 to la do a[i]:=ord(sa[la+1-i])-48;//一位一位的把字符串存到数组里面
lb:=length(sb);
for i:=1 to lb do b[i]:=ord(sb[lb+1-i])-48;
if la>lb then len:=la else len:=lb;
for i:=1 to len do c[i]:=a[i]+b[i];//直接进行加法计算
for i:=1 to len do //进位处理
begin 
c[i+1]:=c[i+1]+c[i] div 10;//向前进位
c[i]:=c[i] mod 10;//当前位
end;
if c[len+1]>0 then len:=len+1;
for i:=len downto 1 do write(c[i]);
end.

```(pascal)


---

