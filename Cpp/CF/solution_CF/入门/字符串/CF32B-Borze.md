# Borze

## 题目描述

### 题面描述

三进制数字符号在Berland很受欢迎。如果用borze编码表示电报的三进制数。数字 $0,1,2$ 分别被作为`.`，`-.`和`--`。你需要为borze编码解码。（把borze编码转换为三进制数）。

## 样例 #1

### 输入

```
.-.--
```

### 输出

```
012```

## 样例 #2

### 输入

```
--.
```

### 输出

```
20```

## 样例 #3

### 输入

```
-..-.--
```

### 输出

```
1012```

# 题解

## 作者：绝顶我为峰 (赞：11)

题目说的全是3进制，其实卵用没有

就是一个字符串处理的简单问题

挨个字符判断满足条件的即可

但是因为3个数字的代号会重复出现

所以需要把用过的字符重置~~当然重置成什么你随意了~~

具体来看一下代码

```cpp
#include<iostream>
using namespace std;
string s;
int main()
{
    cin>>s;
    int len=s.length();//测算长度
    for(int i=0;i<len;++i)//循环判断
    {
        if(s[i]=='.')//“.”是0，此时不用重置（想一想，为什么）
            cout<<0;
        if(s[i]=='-')//一条横分类讨论
        {
            if(s[i+1]=='.')//“-.”为1
                cout<<1;
            if(s[i+1]=='-')//“--”为2
                cout<<2;
            s[i+1]='?';//快乐重置
        }
    }
    return 0;
}
```

~~反正重置成#￥@！%^&$都无所谓~~

~~溜了溜了~~

---

## 作者：endorphin250 (赞：2)

这道题说简单不简单，~~说难也不~~难

题目链接：[CF32B Borze](https://www.luogu.com.cn/problem/CF32B)

根据思路，我们只需判断字符串内字符是否是对应的字符，然后输出对应的数字就行了（简单之处）

但是!!!

仔细看下，“.”是0，“-.”是1，“--”是2，那么按照简单的思路，当输入为“-.--.”的时候，就会输出121。

但看看样例，很明显，程序要从左向右判断，如果一个字符已经被用作他用，那么这个字符就要舍弃（变为除了“-”“.”任意一个字符）

理解这个就很好办了。

这是作者由于没有舍弃字符，导致重复输出的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string n;
	cin>>n;
	int len=n.length();
	for(int i=0;i<len;i++)
	{
		if(n[i]=='.'&&n[i-1]!='-')
			printf("0");
		else if(n[i]=='-'&&n[i+1]=='.')
			printf("1");
		else if(n[i]=='-'&&n[i+1]=='-')
			printf("2");//错误原因：没有考虑其他情况，没有分类讨论
	}
	return 0;
}
```

下面是经过修整AC的代码，解释在代码里：
```cpp
#include<bits/stdc++.h>//万能头了解 
using namespace std;
char Nacly_Fish[205];//让我们定义一个漂亮的鱼鱼 
int main()
{
	scanf("%s",Nacly_Fish);//输入鱼鱼 
	int kkksc03=strlen(Nacly_Fish);//定义英俊的3k让3k等于鱼鱼的长度
	//PS:循环放strlen可能爆炸 
	for(int chen_zhe=0;chen_zhe<kkksc03;chen_zhe++)//定义一个阔爱的cz，用cz遍历
	//要初始化为零，字符串输入是从0开始 
	{
		if(Nacly_Fish[chen_zhe]=='.')//如果字符等于“.” 
			printf("0");//输出0
			//不要换行 
		if(Nacly_Fish[chen_zhe]=='-')//如果字符等于“-” 
		{//分类讨论 
			if(Nacly_Fish[chen_zhe+1]=='.')//如果下一个字符等于“.” 
				printf("1");//符合1的标准，输出1 
			else//如果不是就是第二种情况 
				printf("2");//输出2 
			Nacly_Fish[chen_zhe+1]='A';//将字符舍弃，防止重复输出 
			//变成除了“.”，“-”的任意字符都可以 
		}
	}
	return 0;//结束 
}
```


---

## 作者：Blunt_Feeling (赞：2)

这道题题面上说是三进制，

实质上是对字符串的处理。 

遇到"."和"-"分类讨论，再挨个输出即可。 

但是"-"比较特殊，可能会重复，

比方说样例二:
>--.

正确的输出应是
>20

而如果我们在遍历时把"--"判为2，又把"-."判为1，输出的就会是21。

想要避免这个问题，就得在遍历"--"之后标记一下，

把第二个"-"改为除了".","-"之外的其他字符。

------------
这里再提一下此题解关于输出的问题。 

此题解的输出全部用的是putchar()函数，

事实证明，putchar()的速度要比cout,甚至比printf()快得多。

本蒟蒻做过一个实验，写两个程序比较putchar()与printf()的输出效率：
```cpp
//st1 用printf()输出a
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
int a=0;
char c='0';
int main()
{
	freopen("st1.out","w",stdout);
	For(i,1,1e6)
		printf("%d",a);
	return clock();
}
```
```cpp
//st2 用putchar()输出c
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
int a=0;
char c='0';
int main()
{
	freopen("st2.out","w",stdout);
	For(i,1,1e6)
		putchar(c);
	return clock();
}
```
注：这里clock()函数返回用了几毫秒。

编译运行，于是——
## 第一个程序的运行结果：
![](https://cdn.luogu.com.cn/upload/image_hosting/pt0kenio.png)
## 第二个程序的运行结果：
![](https://cdn.luogu.com.cn/upload/image_hosting/cx71xr9n.png)

同样是输出1000000个0，printf用了2372Ms，putchar仅用了68Ms，
## 可见putchar的效率有多快。

最后附上C++的AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	int len=s.length();//求长度 
	for(int i=0;i<len;i++)
	{
		if(s[i]=='.')
		{
			if(i==0) putchar('0');//字符串首的"."为前导零 
			else if(s[i-1]=='-')//"-."的情况 
				putchar('1');
			else putchar('0');//字符串中的零 
		}
		else if(i!=0&&s[i-1]=='-')//"--"的情况(这里i不能为零,想想为什么)
		{
			putchar('2');
			s[i]='@';//做个标记,避免重复 
		}
	}
	return 0;
}
```

---

## 作者：花千树 (赞：1)

# **一道字符串模拟题**

**考察知识点：字符串处理**

字符串读入（string，也可以用char数组），然后从第一个字符开始检查，确认就输出（但是要if判断一下，因为1和2有2个字符，都是第一个相同，第二个不相同）其实主程序主要就是一个检查用的循环，里面套3个if语句就可以了。

详情见代码：
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
string s; 
int main(){
	cin>>s;//读入
	int len=s.size(),i=0;//len纪录字符串的长度
	while(i<len){//还没达到长度
		if(s[i]=='-'&&s[i+1]=='.'){//判断是否为1，需要满足2个条件，注意i+2
			cout<<1;
			i+=2;
		}
		if(s[i]=='.'){//判断是否为0，i+1
			cout<<0;
			i++;
		}
		if(s[i]=='-'&&s[i+1]=='-'){//判断是否为2，两个都需要为'-',i+2
			cout<<2;
			i+=2;
		}
	}
	return 0;//while循环做完就结束了
}
```

---

## 作者：PC_DOS (赞：1)

一道字符串模拟题，只需要从头到尾读一遍就可以了。

如果读到"."，直接输出一个0，同时指针往后移动1位。

如果读到"-"，且下一个字符为"."，输出一个1，同时指针往后移动2位。

如果读到"-"，且下一个字符为"-"，输出一个2，同时指针往后移动2位。

于是得到代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //关闭与STDIO的同步，加快速度
	string sBroze; //输入的Broze码
	int i; //循环变量
	getline(cin, sBroze); //读入Broze码
	for (i = 0; i <= sBroze.length() - 1;){ //开始一个个读取
		if (sBroze[i] == '.'){ //如果读到"."
			cout << 0; //直接输出一个0
			++i; //指针往后移动1位
		}
		else if (sBroze[i] == '-' && sBroze[i + 1] == '.'){ //如果读到"-"，且下一个字符为"."
			cout << 1; //输出一个1
			i += 2; //指针往后移动2位
		}
		else if (sBroze[i]=='-' && sBroze[i+1]=='-'){ //如果读到"-"，且下一个字符为"-"
			cout << 2; //输出一个2
			i += 2; //指针往后移动2位
		}
		else{ //如果读到非法字符
			++i; //指针向后移动1位
		}
	}
	return 0; //结束
}
```

---

## 作者：SUNCHAOYI (赞：0)

**这是一道关于字符串操作的题**

**首先，如果字符是“.”,则直接输出对应的0；若是“-”则要分类讨论下一个字符，若是“.”，输出1，是“-”，输出2。**

**然后最重要的是，分类讨论后的标记，使得循环下一位时不会再次输出！**

## 康康代码：
```
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string str;
	cin>>str;
	for(int i = 0;i < str.size();i++)
	{
		if(str[i] == '.') cout<<0;
		if(str[i] == '-')
		{
			if(str[i + 1] == '-') cout<<2;
			if(str[i + 1] == '.') cout<<1;
			str[i + 1] = '+'; //标记成什么都可（除"."与"-"）
		} 
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：judgejudge (赞：0)

# 用数组来记录是否出现！！！
首先这道题只有三种形式：".","-.","--"。

那么我们的问题是不让它们重复判断。这样一来我们就会想到用**数组储存它们是否出现过。**

比如样例1：
| . | - | . | - | - |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 0 |?  | ? | ? | ? |
| 1 | 0 | 0 | 0 | 0 |

那么我们判断下一个：
| . | - | . | - | - |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 0 | 1 |  | ? | ? |
| 1 | 1 | 1 | 0 | 0 |
那么我们再次判断的时候，此处”.“就会说明已出现过，就不会重复判断。

AC代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
int a[100001];//记录是否出现
int main(){
	int i,j,k,n;
	string st;
	cin>>st;
	for(i=0;i<st.length();i++){
		if(a[i]==0){//如果没有出现过
			if(st[i]=='.'){//是.，输出0
				cout<<0;
				a[i]=1;//记录：说明已出现过
			}
			if(st[i]=='-'){//分类讨论：1和2
				if(st[i+1]=='.')cout<<1;
				if(st[i+1]=='-')cout<<2;
				a[i]=1;a[i+1]=1;//记录：说明已出现过
			}
		}
	}
	return 0;
}
```




---

## 作者：Star_Wind (赞：0)

话说这题真的很水，会字符串的都知道吧。

### 但是

陷阱终究是有的，毕竟CF的题也不是吃素的。

首先，我们需要了解两个函数

```cpp
getline(cin,st)
putchar(' ')
```

getline代表读入一行字符串（注意含换行）

putchar是一种较快的输入字符的方法

这题就是考虑了三种情况的字符串简单模拟

话不多说，附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int main()
{
	getline(cin,st);
	for(int i=0;i<st.size();i++)
	{
		if(st[i]=='.') putchar('0');
		if(st[i]=='-'&&st[i+1]=='.') {putchar('1');i++;}
		if(st[i]=='-'&&st[i+1]=='-') {putchar('2');i++;}//注意这两个i++表示跳过下一个循环
	}
	return 0;
}
```

我觉得，这种题目还是别抄了吧。。。。



---

