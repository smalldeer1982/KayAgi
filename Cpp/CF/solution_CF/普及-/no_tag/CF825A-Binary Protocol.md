# Binary Protocol

## 题目描述

Polycarp has just invented a new binary protocol for data transmission. He is encoding positive integer decimal number to binary string using following algorithm:

- Each digit is represented with number of '1' characters equal to the value of that digit (for 0 it is zero ones).
- Digits are written one by one in order corresponding to number and separated by single '0' character.

Though Polycarp learnt how to encode the numbers, he has no idea how to decode them back. Help him calculate the decoded number.

## 样例 #1

### 输入

```
3
111
```

### 输出

```
3
```

## 样例 #2

### 输入

```
9
110011101
```

### 输出

```
2031
```

# 题解

## 作者：TRZ_2007 (赞：6)

首先先吐槽一下这个翻译……  
欺负我初一蒟蒻！！（根本看不懂，我语文太菜了）  
所以来先重新翻译一遍。  
## 翻译：
现在给你一个长度为$n$的字符串，你需要执行如下两种操作：

- 1：$push$操作，当字符串中出现了“1”，你就需要把这个数加到计时器中（$num++$）

- 2：$pop$操作，当字符串出现“0”，你就需要输出计时器并且清零计时器。

## Solution
~~看完上面的翻译之后如果你还是不会做，于是就左转新手村~~  
正解就是按照操作模拟，不想解释。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 110;

char str[N];
int n,sum;

int main()
{
	scanf("%d\n",&n);
	scanf("%s",str+1);
	for(int i=1;i<=strlen(str+1);i++) {
		if(str[i] == '1')
			sum++;
		else {
			printf("%d",sum);
			sum = 0;
		}
	}
	printf("%d\n",sum);
}
```

---

## 作者：Mine_King (赞：0)

首先吐槽一下恶评……  
然后吐槽一下翻译，搞得人云里雾里的。下面是一个比较容易懂的**翻译：**  

给你一个01串的长度和这个01串，当一个点是1时，将他入栈；当一个点是0时，输出栈的大小并清空栈。**结束时还要再输出栈的大小。**  

看到这里，那就很容易想到了直接模拟栈。但是，栈内元素我们好像不需要知道？我们要的只是栈的大小而已。那么，我们可以用一个变量`num`记录当前栈的大小，入栈则`num++`,出栈则输出`num`并`num=0`。这样省空间还省码量，一举两得。接下来处理输入问题：你可以直接当一个数输入，但是，会有前导$0$，所以不能这样。你也可以用字符串输入，但内存并不是最优的， ~~而且枉费了题目的一片苦心给你长度~~ ，最好的方法是用`scanf`的一个功能：读入指定长度的整型：  
若需要的读入长度为`l`（`l`必须是常量），读入的变量名是`x`，则读入的方法是`scanf("%ld",&x);`。这样方便，快捷，省空间 ~~（虽然那点空间不省也没关系）~~    
**下面就是大家喜闻乐见的code：**
```cpp
#include<cstdio>
using namespace std;
int len,x;
int num;
int main()
{
	scanf("%d",&len);
	for(int i=1;i<=len;i++)
	{
		scanf("%1d",&x);
		if(x) num++;
		else printf("%d",num),num=0;
	}
	printf("%d",num);
	return 0;
}
```

---

## 作者：X_Chao_Bai (赞：0)

### ~~CF的题真的好水啊~~

不想说啥，就是这个翻译有点坑（我康了半天才知道什么意思）。

读懂了题目，其他的就没啥好说的了，就是一个正常模拟，解释看下面代码。

### 代码奉上：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
char a;
int ans,n;
int main(){
	cin>>n;
	scanf("\n");//这边要输入一个换行，不然会被后面的getchar读进去
	while(1){
		a=getchar();
		if(a=='\n'){//碰到换行就结束
			printf("%d",ans);
			break;
		}
		if(a=='1') ++ans;//计数
		else printf("%d",ans),ans=0;//遇到0就输出,ans清零
	}
    return printf("\n")&&0;//一个玄学的换行
}
```
（逃

---

## 作者：do_while_true (赞：0)

#### 一道水题，重要的是读懂题目

------------
**题目连接**

[洛谷](https://www.luogu.com.cn/problem/CF825A)

[CF](https://codeforces.com/problemset/problem/825/A)

看翻译显然得知，我们要讲一个01字符串转化成一个十进制数，那么显然这个翻译让人捉摸不透是怎么转化的。让我们来仔细观察一下样例

首先，我们看翻译得出，我们要一个一个转化十进制数，每两个十进制数在01串中用‘0’间隔。

观察样例很容易得出：在01串中，每两个‘0’之间有多少个‘1’，当前翻译过后的数字就是几。如果这两个‘0’之间一个‘1’也没有，那么翻译过后的数字就是0。

打个比方

- 1001101111

从前往后扫一遍，首先是连续读入了1个‘1’，那么第一个数字就是1

在第一个数字后的间隔‘0’后紧接着是另一个间隔‘0’，中间一共有0个连续的'1'，那么第二个数字就是0

接着连续读入了2个‘1’，那么第三个数字是2

接着连续读入了4个‘1’，那么第四个数字是4

所以，这个01串翻译过后是1024



------------
明白了怎么翻译，我们的程序就很好写了，我们选择在线处理，也就是边读入边处理

每读入一个‘1’，就把次数+1

每读入一个‘0’，就把次数输出，把次数置为0

但是仍然需要注意的一点是，翻译最后一个数后并没有间隔‘0’，我们需要在我们的循环外面多输出一遍次数

 _**Code1:**_
 
 ```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,t;
char ch;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	while(n--)
	  {
	  	cin>>ch;
	  	if(ch=='0')
	  	  {
	  	  	cout<<t;
	  	  	t=0;
		  }
		else
		  t++;
	  }
	cout<<t;
	return 0;
}
```



------------
不懂字符，字符串？没关系

我们有超级好用的
```
scanf("%1d",&x);
```

这个的意思就是只读入一位整数，存在x当中，当然也可以把1换成其他数，读入任意位数

 _**Code2:**_ 
 ```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,t,x;
int main()
{
	scanf("%d",&n);
	while(n--)
	  {
	  	scanf("%1d",&x);
	  	if(x==0)
	  	  {
	  	  	cout<<t;
	  	  	t=0;
		  }
		else
		  t++;
	  }
	cout<<t;
	return 0;
}
```

//已修正本文一些小的错误

---

## 作者：ProjectRed (赞：0)

其实完全不需要输入字串长度，仅仅只要输入一个字符串，然后遍历一遍，这种做法唯一的缺点是较为浪费时间，会比一边输入一边做慢一点，但是优点是写起来方便，下面会对两种做法都进行一定的讲解
```cpp
#include<bits/stdc++.h>
using namespace std;
int main ()
{
	int n;
	scanf ("%d", &n);
	string s;
	cin >> s;
	int l = s.length ();
	int num = 0;
	for (int i = 0; i < l; i++)//要注意的是字符串是从0开始读的，如果平时习惯从1开始的初学者很容易出错
	{//而且，s[l]这一个地址是没有的，不知道是越界了还是空的，，
		if (s[i] == '1')//这一条只要看懂了题意都是能做出来的
			num++;
		else
		{
			printf ("%d", num);//平淡无奇的输出
			num = 0;
		}
	}
	printf ("%d", num);//输出最后一个数，在之前的循环里是没有输出过的，尝试一下就能明白了
	return EXIT_SUCCESS;//花里胡哨的结尾
}
```

下面是边读边输出的做法
```cpp
#include<bits/stdc++.h>
using namespace std;
char s;
int main ()
{
	int n;
	scanf ("%d", &n);
	int num = 0;
	getchar ();//scanf会读入回车，使用一个getchar()来“吃”掉回车
	for (int i = 1; i <= n; i++)
	{
		scanf ("%c", &s);//朴素的输入和处理
		if (s == '1')
		   num++;
		else
			printf ("%d", num), num = 0;//c++是可以用逗号的，等同于下面的代码
//{
//	printf("%d", num);
//	num = 0;
//}                    
	}
	printf ("%d", num);
	return EXIT_SUCCESS;
}
```


---

## 作者：cbyybccbyybc (赞：0)

## **其实挺水的，根据题意，输入字符串长度（更方便了），再每输入一个字符，当它是1，就数值++，不然是0（且是第一次出现0），打断，如果还有0，再输出0**

```cpp
#include<bits/stdc++.h>
using namespace std;
char a;
int main()
{
	int n,sum=0;
	cin>>n;//长度
	bool flag=1;//用来判断是否是第一次出现0
	for(int i=0;i<n;i++)
	{
		cin>>a;//一个一个输入字符
		if(a!='0')//当它非0，数值++
		{
			sum++;
			flag=1;//调回第一次是0
		}
		else if(flag==1&&a=='0')//如果第一次出现0
		{
			cout<<sum;//输出数值
			sum=0;//数值归零
			flag=0;//调回为第二次0
		}
		else if(a=='0'&&flag==0)//如果不是第一次为0
		{
			cout<<"0";//则输出0
		}
	}
	cout<<sum;//最后别忘了输出最后的数值
	return 0;
}
```
# 珍爱生命，请勿抄袭。
# 祝大家刷题愉快，谢谢


---

