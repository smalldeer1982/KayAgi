# Help Far Away Kingdom

## 题目描述

In a far away kingdom lived the King, the Prince, the Shoemaker, the Dressmaker and many other citizens. They lived happily until great trouble came into the Kingdom. The ACMers settled there.

Most damage those strange creatures inflicted upon the kingdom was that they loved high precision numbers. As a result, the Kingdom healers had already had three appointments with the merchants who were asked to sell, say, exactly $ 0.273549107 $ beer barrels. To deal with the problem somehow, the King issued an order obliging rounding up all numbers to the closest integer to simplify calculations. Specifically, the order went like this:

- If a number's integer part does not end with digit $ 9 $ and its fractional part is strictly less than $ 0.5 $ , then the rounded up number coincides with the number’s integer part.
- If a number's integer part does not end with digit $ 9 $ and its fractional part is not less than $ 0.5 $ , the rounded up number is obtained if we add $ 1 $ to the last digit of the number’s integer part.
- If the number’s integer part ends with digit $ 9 $ , to round up the numbers one should go to Vasilisa the Wise. In the whole Kingdom she is the only one who can perform the tricky operation of carrying into the next position.

Merchants found the algorithm very sophisticated and they asked you (the ACMers) to help them. Can you write a program that would perform the rounding according to the King’s order?

## 样例 #1

### 输入

```
0.0
```

### 输出

```
0```

## 样例 #2

### 输入

```
1.49
```

### 输出

```
1```

## 样例 #3

### 输入

```
1.50
```

### 输出

```
2```

## 样例 #4

### 输入

```
2.71828182845904523536
```

### 输出

```
3```

## 样例 #5

### 输入

```
3.14159265358979323846
```

### 输出

```
3```

## 样例 #6

### 输入

```
12345678901234567890.1
```

### 输出

```
12345678901234567890```

## 样例 #7

### 输入

```
123456789123456789.999
```

### 输出

```
GOTO Vasilisa.```

# 题解

## 作者：江山_远方 (赞：2)

Hey 一起来快乐的水~~水~~题吧

题目很简单啦 只不过...

#### 1000位令人窒息！

emmmmm....

要说高精哪家强，字符串做法来帮忙！

~~众所周知，~~ 有一个函数叫find

用法：st.find(你要找的字符/字符串）

辣么，我们阔以根据楼上的思路写出代码啦：
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int k;
int main()
{
	cin>>st; 
	k=st.find(".");
	if(st[k-1]=='9')cout<<"GOTO Vasilisa.";
	  else 
	  {
	  	if(st[k+1]>='5')
	  	{
	  		for(int i=0;i<k-1;i++)putchar(st[i]);
	  		putchar(st[k-1]+1);
		}
	  	else
	  	for(int i=0;i<=k-1;i++)putchar(st[i]);
	  }
	return 0; 
} 
```
AC抱回家

---

## 作者：锦瑟，华年 (赞：0)

其实这题很简单，只需要一个读入加判断即可。

好了，我们讲一讲具体思路。首先，对其进行读入，要用字符串进行读入，而且不要全部读，只读到小数点后一位即可（因为要四舍五入），读入的方法大概像是快读的方法，不过要改一改。读完之后，判断整数的最后一位是不是9，如果是，输出 GOTO Vasilisa. ，如果不是，直接输出那个整数即可，不过要注意，还要进行四舍五入，对小数点后一位进行判断，如果大于4的话，则要进位。

好了，上代码吧：

	#include<stdio.h>
	using namespace std;
	int a[1005];
	int main(){
		int s=0,i;
		char c=getchar();//以下是类快读读入
		while(c<'0'||c>'9')c=getchar();
		while(c>='0'&&c<='9'){
			a[++s]=c-'0';
			c=getchar();
		}
		int h=getchar()-'0';//这个数是小数点后后一位
		if(a[s]==9)printf("GOTO Vasilisa.");//判断输出
		else{
			if(h>=5)a[s]+=1;
			for(i=1;i<=s;i++){
				printf("%d",a[i]);
			}	
		}
		return 0;//完美结束
	}
    
这题不算难，大家应该都看懂了吧。好了，题解结束，over~~(^_^)

---

## 作者：仗剑_天涯 (赞：0)

~~我一开始还是以为开double直接做就好了呢，不过double过不了（实锤，太天真了QAQ）。~~

思路：找到这个浮点数的小数点，如果他的前一位（整数的最后一位）是9，那么输出GOTO Vasilisa.

如果不是9，就将四舍五入处理过的数的整数部分输出。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
void sswr(int x)
{
	if(st[x+1]<='4') return;//四舍
	st[x-1]++;//五入
}
void out(int x)
{
	for(int i=0;i<x;i++)
	{
		cout<<st[i];//将四舍五入处理过的数的整数部分输出
	}
	cout<<endl;
}
void pd(int x)
{
	if(st[x-1]=='9') cout<<"GOTO Vasilisa."<<endl;//是9，那么输出GOTO Vasilisa.
	else //不是9
	{
		sswr(x);//四舍五入
		out(x);	//输出
	}
} 
int main()
{
	cin>>st;
	for(int i=0;i<st.size();i++)
	{
		if(st[i]=='.')//如果是小数点
		{
			pd(i);//开始处理
			break;//处理完后中断
		}
	} 
	return 0;
} 
```


---

## 作者：RioBlu (赞：0)

没有人用高精加，我真的是非常非常的伤心
___
思路：判断 小数点 的前面是否是9，是九输出"GOTO Vasilisa."
```
#include<bits/stdc++.h>
using namespace std;
string sum(string a,string b)//高精A+B
{
    int c[1000],d[1000],k,n;
    string ans;
    for(int s=0;s<1000;s++)c[s]=0,d[s]=0;
    while(a.size()!=b.size())
    {
        if(a.size()>b.size())
        {
            b="0"+b;
        }
        if(a.size()<b.size())
        {
            a="0"+a;
        }
    }
    for(int s=1;s<a.size()+1;s++)
    {
        k=(int)a[s-1]-'0';
        n=(int)b[s-1]-'0';
        c[s-1]=c[s-1]+(k+n)/10;
        c[s]=c[s]+(k+n)%10;
    }
    for(int S=0;S<2;S++)
    for(int s=1;s<a.size()+1;s++)
    {
        if(c[s]>=0)
        {
            c[s-1]+=c[s]/10;
        }
        c[s]=c[s]%10;
    }
    for(int s=a.size();s>0;s--)
    {
        if(c[s]>=0)
        {
            c[s-1]+=c[s]/10;
        }
        c[s]=c[s]%10;
    }
    for(int s=1;s<a.size()+1;s++)
    {
        ans=ans+((char)(c[s]+'0'));
    }
    if(c[0]>=1)
    {
        ans=(char)(c[0]+'0')+ans;
    }
    return ans;
}
char last,a;//上一个输入，当前输入
string zhen;//整数部分
bool point;//当前的前面是否有小数点
int main()
{
	while(cin>>a)
	{
		if(a=='.')point=1;//有小数点
		if(!point)
		zhen=zhen+a;//把整数的部分加进去
		if(a=='.')
		{
			if(last=='9')//在小数点前是九
			{
				cout<<"GOTO Vasilisa."<<endl;
				return 0;
			}
			
		}
		if(last=='.')
		{
			if(a<='4')cout<<zhen<<endl;//不用+1，直接输出
			else cout<<sum(zhen,"1");//将整数部分加一再输出
			return 0;
		}
		last=a;
	}
}
```

---

## 作者：谦谦君子 (赞：0)

#### 直接用字符串读入，然后找到小数点就行了

------------
**代码如下**
```
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string num;
    while(cin>>num)
    {
        for(int i=0;i<num.length();++i)
        {
            if(num[i]=='.')
            {
                if(num[i-1]=='9')
                {
                    cout<<"GOTO Vasilisa."<<'\n';
                    break;
                }
                else
                {
                    if(num[i+1]>='5')
                        num[i-1]+=1;
                    string n=num.substr(0,i);
                    cout<<n<<'\n';
                    break;
                }
            }
        }
    }
    return 0;
}
```


---

