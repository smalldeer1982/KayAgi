# JULKA - Julka

## 题目描述

 Julka surprised her teacher at preschool by solving the following riddle:

  _Klaudia and Natalia have 10 apples together, but Klaudia has two apples more than Natalia. How many apples does each of he girls have?_

 Julka said without thinking: Klaudia has 6 apples and Natalia 4 apples. The teacher tried to check if Julka's answer wasn't accidental and repeated the riddle every time increasing the numbers. Every time Julka answered correctly. The surprised teacher wanted to continue questioning Julka, but with big numbers she could't solve the riddle fast enough herself. Help the teacher and write a program which will give her the right answers.

   
Task
----

 Write a program which

- reads from standard input the number of apples the girls have together and how many more apples Klaudia has,
- counts the number of apples belonging to Klaudia and the number of apples belonging to Natalia,
- writes the outcome to standard output

## 样例 #1

### 输入

```
10
2
[and 9 test cases more]```

### 输出

```
6
4
[and 9 test cases more]```

# 题解

## 作者：YUYGFGG (赞：4)

有十组数据，每次输出$(a+b)/2$和$(a-b)/2$即可
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a;
int main(){
    int a,b;
    for(int i=1;i<=10;i++){
        cin>>a>>b;
        cout<<(a+b)/2<<endl<<(a-b)/2<<endl;
    }
}
```

于是：![](https://tva1.sinaimg.cn/large/007S8ZIlgy1genmkjbutij305u05qmx7.jpg)

仔细一看：**两数均为小于10^100的整数**

好吧，上高精

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
string sub(string str1,string str2)//高精度减法
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

int main(){
     for(int i=1;i<=10;i++)
     {
         string a="",b="",ans="",r="";
         cin>>a>>b;
         div(add(a,b),"2",ans,r);
         cout<<ans<<endl;
         div(sub(a,b),"2",ans,r);
         cout<<ans<<endl;
     }
     return 0;
}
```
倒霉的C++党啊

---

## 作者：159号程序员 (赞：4)

这道题是一个数学上的和差问题，但是要用高精度，我们可以用**Python**(自带高精)和**和差公式**来做。

首先，我们来了解一下和差公式：

**大数=(和+差)/2**

**小数=(和-差)/2**

三年级小学数学，如果还有不懂请点[这里](https://baike.baidu.com/item/%E5%92%8C%E5%B7%AE%E5%85%AC%E5%BC%8F/9799203?fr=aladdin)

然后， _AC Code_ 

```py
for i in range(10): #每一次有10个测试样例
    x = input() 
    y = input()
    x = int(x) #把x和y转换成int
    y = int(y)
    print((x + y) // 2)#输出公式
    print((x - y) // 2)
```
我们来解释一下这个程序：

1. 一个10次的循环(对应十个输入)

1. 输入x，y。6, 4

3. 输出较大的数：
$$\frac{6+4}{2}=5$$

4. 输出较小的数：

$$\frac{6-4}{2}=1$$

---

## 作者：STL_Lover (赞：2)

来一篇 Java 的题解。

我们先来了解一下 Java 中的 BigInteger。

定义方式： ``BigInteger a;``

复制方式：``a = new BigInteger("0")//赋值为0``

加法：``a.add(b) //a+b ``

减法：``a.subtract(b) //a-b``

除法：``a.divide(b) // a/b``


当然我们还要知道：

大的数=(和+差)/2

小的数=(和-差)/2

以下是代码。


```
import java.math.*;//数学函数库
import java.util.*;
public class Main {
    public static void main(String args[]) throws Exception {
        Scanner cin=new Scanner(System.in);
        for(int i=1;i<=10;i++){ //循环10次
            BigInteger a = cin.nextBigInteger(), b = cin.nextBigInteger(); //读入a,b
            BigInteger tmp=new BigInteger("2");//临时定义一个大整数
            BigInteger TT=a.add(b);//计算a+b
            BigInteger TTT=a.subtract(b);//计算a-b
            System.out.println(TT.divide(tmp));
            System.out.println(TTT.divide(tmp));//分别除以二输出
        }
    }
}
```

Accepted.

完。

---

## 作者：Brian_WBY (赞：1)

题解区已经有大佬用返回字符串的形式写出了高精度，但是我还是更习惯另一种写法：封装。

题意：给出两个数的和与差，求出这两个数。

我们把两个数的和记为 $a$，两个数的差为 $b$，设两个数为 $x,y(x\geq y)$。

则

$$\begin{cases}x+y=a\\x-y=b\end{cases}$$

两式相加得 $2x=a+b,x=\dfrac{a+b}{2}$；

两式相减得 $2y=a-b,y=\dfrac{a-b}{2}$。

结论非常容易推，但是因为$a,b\leq10^{100}$，所以要写一个高精度实现。

代码如下（高精度的实现及细节注释都在代码里）：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct BigInteger//定义一个高精度的结构体
{
	int len,x[101];//len表示一个高精度数的长度，x[i]表示高精度数的第i位
	BigInteger()//初始化
	{
		len=0;
		memset(x,0,sizeof(x));
	}
	BigInteger(string s)//通过string构造
	{
		len=s.size();//高精度数的长度就是字符串长度
		memset(x,0,sizeof(x));//清零
		for (int i=0;i<len;++i)
			x[i]=s[i]^'0';//把字符转化为数字，在这里 ^'0' 相当于 -'0'
		reverse(x,x+len);//翻转，使 x 数组的储存由低位到高位
	}
	void print()//输出
	{
		for (int i=len-1;i>=0;--i)
			putchar(x[i]^'0');//异或运算可逆
		puts("");
	}
	friend BigInteger operator + (BigInteger a,BigInteger b)//高精加，重载加号
	{
		BigInteger ans;
		ans.len=max(a.len,b.len)+1;//最大长度为两个加数的最大长度 +1
		for (int i=0;i<ans.len;++i)
		{
			ans.x[i]+=a.x[i]+b.x[i];
			if	(ans.x[i]>=10)//处理进位
			{
				++ans.x[i+1];
				ans.x[i]-=10;
			}
		}
		while (!ans.x[ans.len-1])	--ans.len;//去除前导0
		return ans;//返回答案
	}
	friend BigInteger operator - (BigInteger a,BigInteger b)//高精减，因为a>b，所以不需要判断大小
	{
		BigInteger ans;
		ans.len=a.len;//最大长度就是被减数长度
		int x=0;//记录退位
		for (int i=0;i<ans.len;++i)
		{
			ans.x[i]=a.x[i]-b.x[i]-x;
			x=0;
			if	(ans.x[i]<0)//处理退位
			{
				ans.x[i]+=10;
				x=1;
			}
		}
		while (!ans.x[ans.len-1])	--ans.len;//去除前导0
		return ans;//返回答案
	}
	friend BigInteger operator / (BigInteger a,int b)//高精除
	{
		BigInteger ans;
		ans.len=a.len;
		int t[101]={0},l=0,x=0;//t是一个辅助数组，记录答案，l记录当前的长度
		for (int i=a.len-1;i>=0;--i)//除法从高位到低位
		{
			x=x*10+a.x[i];
			t[l++]=x/b;
			x%=b;
		}
		for (int i=l-1;i>=0;--i)
			ans.x[i]=t[l-i-1];
		while (!ans.x[ans.len-1]&&ans.len>1)	--ans.len;//去除前导0
		return ans;//返回答案
	}
}a,b,ans;
BigInteger read()//方便读入，也可以不写
{
	string s;
	cin>>s;
	return BigInteger(s);
}
int main(void)
{
	for (int i=1;i<=10;++i)//10组数据
	{
		a=read(),b=read();//输入
		ans=(a+b)/2;//计算较大的数
		ans.print();//输出答案
		ans=(a-b)/2;//计算较小的数
		ans.print();//输出答案
	}
	return 0;
}
```

PS：多组数据的题建议测试的时候跑两遍，防止数组未清空等错误。

---

## 作者：RioBlu (赞：1)

刚开始我打了好久的代码都WA

后来不断的审题才发现有$10$组数据

# 好气啊

### 所以各位要好好审题!

1.首先建立一个$a$变量一个$b$变量

2.循环$10$次第$3$点到第$6$点

3.里面是输入$a$和$b$

4.$c=(a+b)/2$得到第一个数（下面代码分两行）

5.$d=(a-b)/2$得到第二个数（下面代码分两行）

6.输出$c$和$d$

```
a=0
b=0
for s in range(10):
    a=input()
    b=input()
    c=a+b
    c=c/2
    d=a-b
    d=d/2
    print c
    print d
```

---

## 作者：BotDand (赞：0)

# Problems
给出两个人的苹果个数的和与差，确定他们的苹果个数。
# Answer
先推公式。

设第一个人的苹果数为$x$个，第二个人的苹果数为$y$个。

$x+y=$和

$x-y=$差

将这两个式子相加，得$x=($和$+$差$)\div2$；

带入其中一个式子得$y=($和$-$差$)\div2$

再看数据范围：$10^{100}$

于是可以用$python$。
# Code
```python
for i in range(10): # 循环
    a=int(input()) # 读入a，其中a为整形
    b=int(input()) # 读入b，其中b为整形
    print((a+b)//2) # 套公式，求除第一个人的苹果数
    print((a-b)//2) # 套公式，求除第一个人的苹果数
```

---

## 作者：听取MLE声一片 (赞：0)

~~c++党来做一道P党的题目~~

首先，$10^{100}$ 的数据规模，c++的 $long long$ 显然是不能过的，高精度又太麻烦了，所以用了Python。

设数量和为 $a$ ，数量差为 $b$,两个数为 $x,y$ ($ab$为参数)则：

$$x+y=a,x-y=b$$

然后用加减消元法两个式子加在一起，即

$$x+y+x-y=a+b$$

然后；

$2x=a+b$

所以：

$x=(a+b)/2$

同理可得（用减法）：

$y=(a-b)/2$

然后代码实现一下就行啦！

代码就不放了，参照其他大佬的就行了。


---

## 作者：hero_brine (赞：0)

本题的数据范围比较大，最多有10^100，前面已经有几位大佬发了Python和C++高精题解，本蒟蒻在此水一篇Ruby题解（因为Ruby也自带高精且速度较快）：  
```ruby
for i in 1..10
	a = gets.to_i
    b = gets.to_i
    #读入两数
	print (a+b)/2
    puts ("\n")
    #记得换行
    print (a-b)/2
    puts ("\n")
end
#end十分重要
```
注意事项有且只有一个，就是**for循环末尾需要打end**。

---

## 作者：user2004 (赞：0)

本体大意为，已知$a+b$,$a-b$,求$a$,$b$，有十组数据

十分的简单，但是要求高精度
```cpp
#include<iostream>
using namespace std;
string jia(string a,string b)
{   
    if(a.length()<b.length()) swap(a,b);
    int p=a.length()-1,q=b.length()-1;
	for(int i=b.length()-1;i>=0;i--)
	{a[p]=a[p]+b[i]-48;p--;} 
	for(int i=a.length()-1;i>=1;i--)
	{
		if(a[i]>'9') {a[i]-=10;a[i-1]++;}
	}
	string c;
	if(a[0]>'9') {a[0]-=10;c="1"+a;}
	else c=a; 
	return c;
}
string jian(string a,string b)
{   
    if(a.length()<b.length()||(a.length()==b.length()&&a<b)) {swap(a,b);cout<<"-";}
    int p=a.length()-1,q=b.length()-1;
	for(int i=b.length()-1;i>=0;i--)
	{a[p]=a[p]-b[i]+48;p--;} 
	for(int i=a.length()-1;i>=1;i--)
	{
		if(a[i]<'0') {a[i]+=10;a[i-1]--;}
	}
	string c;
	if(a[0]<'0') {a[0]=96-a[0];c="-"+a;}
	else c=a;
	string u;
	bool flag=0;
	for(int i=0;i<c.length();i++)
	{
		if(flag||c[i]>48) 
		{
		flag=1;
		u+=c[i];		
		}
	} 
	if(u=="") u="0";
	return u;
}
string chen(string a,string b)
{
	string d="0";
	int base=1;
	for(int i=b.length()-1;i>=0;i--)
{
	string c="0"; 
	for(int j=1;j<=(b[i]-48);j++)
	{
		c=jia(c,a);
	}
	for(int i=1;i<base;i++) 
	c+='0';
	base++;;
	d=jia(d,c);
}		
    return d;
}
bool cmp(string a,string b)
{
	if(a.length()<b.length()) return false;
	if(a.length()>b.length()) return true;
	if(a>b) return true;
	if(a==b) return true;
	return false;	
}
string chu(string a,string b,string &rec)
{
	string p;
	string tot="0";
	string ready="0";
	string q=b;
	int base=0;
	while(cmp(a,chen(b,"10")))
	{
		b=chen(b,"10");
		base++;
	}
	int cont=0;
	string c;
	while(cmp(a,q))
	{
	ready="";
	cont=0;
	while(1)
	{	
		if(!cmp(a,b)) break;
		a=jian(a,b);
		cont++;
	}
	string k="";
	for(int i=0;i<b.length()-1;i++)
	k+=b[i];
	if(p=="")p="0";
	b=k;
	ready+=(char)(cont+48);
	for(int i=1;i<=base;i++)
	ready=ready+"0";
	base--;
	tot=jia(tot,ready);
	}
	rec=a;
	return tot;
}
int main()
{
	string a,b,rec;
	for(int i=1;i<=10;i++)
	{
	string p;
	cin>>a>>b;
    p=chu(jia(a,b),"2",rec);
	cout<<p<<endl;
	cout<<jian(a,p)<<endl;
	}
}
```


---

## 作者：hongyubin (赞：0)

## **这么好的高精练习题用Python水过去简直是暴殄天物**
其实这题就是解一个二元一次方程

**a+b=n;**

**a-b=m;**

这里面用到了高精加法，高精减法，高精除法。

(不多说直接贴代码)
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,a1[1010],a2[1010],a3[1010],ans1[1010],ans2[1010],tem[1010];
char ch1[1010],ch2[1010];
int main()
{
	int T=10;
	while(T--)
	{
		int len1,len2,len3,len_ans1=0,len_ans2=0;
		memset(a1,0,sizeof(a1));
		memset(a2,0,sizeof(a2));
		memset(a3,0,sizeof(a3));
		memset(ans2,0,sizeof(ans2));
		memset(ans1,0,sizeof(ans1));
		memset(tem,0,sizeof(tem));
		scanf("%s%s",ch1+1,ch2+1);
		len1=strlen(ch1+1);
		len2=strlen(ch2+1);
		for(int i=1;i<=len1;i++)
		a1[len1-i+1]=ch1[i]-'0';
		for(int i=1;i<=len2;i++)
		a2[len2-i+1]=ch2[i]-'0';
		len3=max(len1,len2);
		for(int i=1;i<=len3;i++) //高精加法
		{
			a3[i]=a3[i]+a2[i]+a1[i];
			if(a3[i]>=10)
			a3[i+1]++;
			//cout<<a3[2]<<"!!";
			a3[i]%=10;
		}
		if(a3[len3+1])
		{
			len3++;
		}
		bool flag=0;
		int now=0;
		for(int i=len3;i>=1;i--)  //高精除法
		{
			//cout<<a3[i]<<"!!";
			a3[i]=now+a3[i];
			if(a3[i]/2>=1||flag)
			{
				flag=1;
				ans1[++len_ans1]=a3[i]/2;
			}
			if(a3[i]%2==1)
			now=10;
			else
			now=0;
		}
		for(int i=1;i<=len_ans1;i++)
		cout<<ans1[i];cout<<endl;
		for(int i=1;i<=len_ans1;i++)
		tem[i]=ans1[len_ans1-i+1];
		for(int i=1;i<=len_ans1;i++)
		ans1[i]=tem[i];
		for(int i=1;i<=len1;i++)  //高精加法
		{
			if(a1[i]<ans1[i])
			{
				a1[i]+=10;
				a1[i+1]--;
			}
			
			ans2[i]=a1[i]-ans1[i];
			if(ans2[i]!=0)
			len_ans2=i;
		}
		for(int i=len_ans2;i>=1;i--)
		cout<<ans2[i];cout<<endl;
		//cout<<ans1<<endl<<ans2<<endl;
	}
	return 0;
}
```
如果高精度还不太熟练的可以做一下以下几题

[高精度减法](https://www.luogu.org/problem/P2142)

[a*b Problen](https://www.luogu.org/problem/P1601)

[高精度加法](https://www.luogu.org/problem/P1601)

[高精度除法](https://www.luogu.org/problem/P1480)


### 注意有十组数据！！！！！

---

