# Phone numbers

## 题目描述

Phone number in Berland is a sequence of $ n $ digits. Often, to make it easier to memorize the number, it is divided into groups of two or three digits. For example, the phone number 1198733 is easier to remember as 11-987-33. Your task is to find for a given phone number any of its divisions into groups of two or three digits.

## 样例 #1

### 输入

```
6
549871
```

### 输出

```
54-98-71```

## 样例 #2

### 输入

```
7
1198733
```

### 输出

```
11-987-33
```

# 题解

## 作者：Eason_AC (赞：35)

怎么说呢。。。水字符串模拟题吧。

由于这个题目~~有spj~~**可以有多种解**，所以判断字符串长度的奇偶性即可。

我的想法是：

1. 长度为奇数，以$A_1A_2-A_3A_4-......A_{n-4}A_{n-3}-A_{n-2}A_{n-1}A_n$输出即可。例如，输入2可以这样输出：$11-98-733$。

2. 长度为偶数，以以$A_1A_2-A_3A_4-......A_{n-3}A_{n-2}-A_{n-1}A_n$输出即可。样例1就是这样子的。

还有不懂的可以看下代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n, flag, a[107];
int main() {
	scanf("%d", &n);
	if(n % 2)	flag = 1;	//判断奇偶性
	for(int i = 1; i <= n; ++i)
		scanf("%1d", &a[i]);
	for(int i = 1; i <= n; ++i) {
		printf("%d", a[i]);	//一个数字一个数字地输出
		if(flag) {			//如果是奇数
			if(!(i % 2) && (i != n - 1))	//下标为偶数，在后面输出"-"。注意！下标为n-1的数后面不需要加"-"！不然会判错！
				putchar('-');
		} else
			if(!(i % 2) && (i != n))		//下标为偶数，在后面输出"-"。注意！最后一个数后面不需要加"-"！
				putchar('-');
	}
	return 0;
}
```

你都看完了，不点一下右上方的赞再走嘛？

当然，有问题的话可以在题解讨论区或直接私信我（$UID=112917$）哦。

---

## 作者：キリ卜 (赞：4)

最短题解来临

这道题只要平均2个数字输一个 ' - ' 就好了，如果n为奇数，那么说明有3个数字的组合，就是最后一个组合，因为奇数减去3（奇数）是偶数，可以组2个一组。那么通过观察输出 ' - ’ 的数量m的规律：

当 n 为奇数时 m = ( n - 1 ) / 2 - 1

当 n 为偶数时 m = n / 2 - 1

参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,tot;
int main(){
    scanf("%d",&n);getchar();
    if (n&1) m=(n-1)/2-1;
    else m=n/2-1;
    for (int i=1;i<=n;i++){
        printf("%c",getchar());
        if (m){tot++;if (tot==2) printf("-"),m--,tot=0;}
    }
    return 0;
}
```


---

## 作者：Register (赞：4)

# 哈哈，一个超级字符串模拟水题
只需要注意两个地方，长度奇偶数分类讨论，不要在最前面或者最后面多输出一个"-"

奉上代码：
```cpp
#include <iostream>//输入输出流库
#include <string>//字符串STL库
using namespace std;
int main(){
	string s;//电话号码
	int len;//电话号码长度
	cin>>len;
	cin>>s;
	if(len%2)//如果电话号码长度为奇数
	{
		for(int i=0;i<len-3;i++)
			if(i%2) cout<<s[i]<<"-";//与-一起输出
			else cout<<s[i];;//与-一起输出
		cout<<s.substr(len-3,3)<<endl;//输出最后剩下3个
	}
	else//如果电话号码长度为偶数
	{
		for(int i=0;i<len-2;i++)
			if(i%2) cout<<s[i]<<"-";;//与-一起输出
			else cout<<s[i];//与-一起输出
		cout<<s.substr(len-2,2)<<endl;//输出最后剩下2个
	}	
	return 0;
}
```

---

## 作者：开心的猪 (赞：2)

这道题，由于可以输出任意一种符合条件的情况，所以可以分两种情况讨论：第一种——偶数。直接每隔两位加上－就行了。第二种——奇数。在除了最后三位以外，每隔两位加上-，最后三位之前加上-就行了。

下面是代码：
```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int a;
	scanf("%d", &a);
	char alpha[a];
	char no;
	scanf("%c", &no);
	for(int i=0; i<a; i++)
	{
		scanf("%c", &alpha[i]);
	}
	if(a%2==0)
	{
		for(int i=0; i<a/2-1; i++)
		{
			printf("%c%c-", alpha[i*2], alpha[i*2+1]);
		}
		printf("%c%c", alpha[a-2], alpha[a-1]);
	}
	else
	{
		for(int i=0; i<a/2-1; i++)
		{
			printf("%c%c-", alpha[i*2], alpha[i*2+1]);
		}
		printf("%c%c%c", alpha[a-3], alpha[a-2], alpha[a-1]);
	}
	return 0;
}
```


---

## 作者：yuzhechuan (赞：2)

其实这样的代码就可以了......
###### ~~小学生也会~~

------------

```cpp
#include<bits/stdc++.h>//万能库，方便
using namespace std;

char c;//边读边做，只需一个字符
int n;

int main()
{
    cin>>n;
    cin>>c;
    cout<<c;//输出第一个字符
    cin>>c;
    cout<<c;//输出第二个字符
    n-=2;//减去前两个字符
    if(n%2==1)//如果是奇数个
    {
    	cin>>c;
    	cout<<c;//输出第三个(以为n一定是>=2的)
    	n--;//减去第三个字符
	}	
    for(int i=1;i<=n;i++)//其余都按2个2个输出处理
    {
    	if(i%2==1)cout<<'-';//注意！此处不是判偶，而是判奇，在奇数个前加杠
    	cin>>c;
    	cout<<c;//继续输出
	}
}
```

---

## 作者：PC_DOS (赞：2)

一道字符串模拟题，由于允许多解，只需要判断一下输入的字符串的长度是奇数还是偶数即可

如果是偶数，直接按照两个数字一组的分组方法输出。

如果是奇数，前三个数字分为一组，后面的数字按照两个数字一组的分组方法输出。

所以就有代码了:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sNumber; //电话号码
	int iLength, i; //iLength-长度，i-循环计数器
	cin >> iLength >> sNumber; //读入长度和号码
	if (iLength % 2 == 0){ //如果长度为偶数
		for (i = 0; i <= iLength - 1; ++i){ //按照两个数字一组的分组方法输出
			cout << sNumber[i]; //逐个输出字符
			if (i % 2 != 0 && i!=iLength-1) //如果循环计数器为奇数，也就是已经输出了两个数，且目前没有抵达最后一个数(一定要判断，否则会多一个分隔符)
				cout << '-'; //输出分隔符
		}
	}
	else{ //长度为奇数
		cout << sNumber[0] << sNumber[1] << sNumber[2]; //先输出前三个字符
		if (iLength!=3) //如果只有三个字符，那么就结束了，不需要输出分隔符
			cout<<'-'; //后面还有字符时输出分隔符
		for (i = 3; i <= iLength - 1; ++i){ //从第四个字符开始，按照两个数字一组的分组方法输出
			cout << sNumber[i]; //逐个输出字符
			if (i % 2 == 0 && i!=iLength-1) //如果循环计数器为偶数，也就是已经输出了两个数，且目前没有抵达最后一个数(一定要判断，否则会多一个分隔符)
				cout << '-'; //输出分隔符
		}
	}
	return 0; //结束
}
```

---

## 作者：Frank_R_Z (赞：0)

###
看到各位dl的题解，立刻“awsl”，十分~~高级~~，char+一维数组还是比较适合这种题目的。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	char a[10002];
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(n%2)//忘了再次分支
	{
		cout<<a[1]<<a[2]<<a[3];
		if(n-3)//在这里判断小于3的情况
		{
			cout<<'-';
			for(int i=4;i<=n;i+=2)
			{
				cout<<a[i]<<a[i+1];
				if(n-i-1)cout<<'-';
			}
		}
		cout<<endl;
	}
	else 
	{
		cout<<a[1]<<a[2];
		if(n-2)//同上
		{
			cout<<'-';
			for(int i=3;i<=n;i+=2)
			{
				cout<<a[i]<<a[i+1];
				if(n-i-1)cout<<'-';
			}
		}
		cout<<endl;
	}
	return 0;//完美结束
}

```


---

## 作者：WKAHPM (赞：0)

### 一道字符串模拟题

首先我们知道

偶数+偶数=偶数

偶数+奇数=奇数

然后我们就可以对$N$进行分类讨论：

- 当$N\le3$时，直接输出字符串即可

- 当$N=2k$ $(k\ge2)$时，可以把$N$拆分成若干个长度为2的字符串，在两个字符串之间添上-号

- 当$N=2k+1$  $(k\ge2)$时，可以把$N$拆分成一个长度为3的字符串和若干个长度为2的字符串，在两个字符串之间添上-号

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int sum;
int n;
int main()
{
	scanf("%d",&n);
	cin>>s;
	if(n<=3) //如果n<=3，直接输出
	{
		cout<<s;
		return 0;
	}
	if(n%2==0) //n为偶数则拆分成若干个长度为2的字符串
	{
		for(int i=0; i<n; i++)
		{
			sum++;
			printf("%c",s[i]);
			if(i==n-1) return 0;
			if(sum==2)
			{
				printf("-");
				sum=0;
			}
		}
	}
	else //n为奇数则拆分成一个长度为3的字符串和若干个长度为2的字符串
	{
		for(int i=0; i<3; i++)
		{
			printf("%c",s[i]);
		}
		printf("-");
		for(int i=3; i<n; i++)
		{
			sum++;
			printf("%c",s[i]);
			if(i==n-1) return 0;
			if(sum==2)
			{
				printf("-");
				sum=0;
			}
		}
	}
	return 0;
}

```


---

