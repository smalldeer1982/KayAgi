# Bark to Unlock

## 题目描述

As technologies develop, manufacturers are making the process of unlocking a phone as user-friendly as possible. To unlock its new phone, Arkady's pet dog Mu-mu has to bark the password once. The phone represents a password as a string of two lowercase English letters.

Mu-mu's enemy Kashtanka wants to unlock Mu-mu's phone to steal some sensible information, but it can only bark $ n $ distinct words, each of which can be represented as a string of two lowercase English letters. Kashtanka wants to bark several words (not necessarily distinct) one after another to pronounce a string containing the password as a substring. Tell if it's possible to unlock the phone in this way, or not.

## 说明/提示

In the first example the password is "ya", and Kashtanka can bark "oy" and then "ah", and then "ha" to form the string "oyahha" which contains the password. So, the answer is "YES".

In the second example Kashtanka can't produce a string containing password as a substring. Note that it can bark "ht" and then "tp" producing "http", but it doesn't contain the password "hp" as a substring.

In the third example the string "hahahaha" contains "ah" as a substring.

## 样例 #1

### 输入

```
ya
4
ah
oy
to
ha
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
hp
2
ht
tp
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
ah
1
ha
```

### 输出

```
YES
```

# 题解

## 作者：thomas_zjl (赞：5)

这道题只要看随便$2$个的字符串拼接是否与$S$有相同就行了。

本来我看到这道题想用$find$函数的，但是他过不了。

于是我就手写了一个相当于查找的函数。

```
int f(string a,string b)//a表示S,b表示2个字符串拼接的单词。
{
	for(int i=0;i<4;i++)//因为我们知道，1个字符串规定长度为2，那么2个拼接起来就是2*2=4。
	{
		if(b[i]==a[0])//如果这个字母与S的起始端相同，那么就可以开始进行下面的比较了。
		{
			int zz=0;//计数器。
			for(int j=0;j<2;j++)//因为S的长度的规定为2，所以j<2完全正确。
			{
				if(b[i+j]!=a[j])//i+j表示的是b的位置与a[j]相对应的位置。
				{
					zz=1;
					break;
					//如果不是，那么计数器变化，跳出循环。
				}
			}
			if(zz==0)
			{
				return 1;//如果计数器为1，返回1。
			}
		}
	}
	return 0;//如果经过上面的比较没有相同的地方，返回1。
}
```
最难的部分讲解完了，接下来了看看代码吧。
```
#include<bits/stdc++.h>
using namespace std;
int f(string a,string b)
{
	for(int i=0;i<4;i++)
	{
		if(b[i]==a[0])
		{
			int zz=0;
			for(int j=0;j<2;j++)
			{
				if(b[i+j]!=a[j])
				{
					zz=1;
					break;
				}
			}
			if(zz==0)
			{
				return 1;
			}
		}
	}
	return 0;
}
//用来比较，不多说了。
int main()
{
	string s;
	cin>>s;
	int n;
	cin>>n;
	string a[n];
	string b;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)//因为题目中说可以重复使用字符串，使用j要从0开始进行循环。
		{
			b=a[i]+a[j];
			if(f(s,b))
			{
				cout<<"YES";
				return 0;	
				//如果进行查找函数返回1的话，直接输出YES,结束代码。
			}	
		} 
	}
	cout<<"NO";//如果经过什么的拼接以及比较发现没有与S相同的拼接字符串，输出NO。
    return 0;
}
```



---

## 作者：Inorganic_Chemistry (赞：1)

[AC记录](https://www.luogu.com.cn/record/37138564)

其实直接模拟就行了。

一共只有两种可能性可以得到密码。

1.Kashtanka 会的单词恰好就是密码。

2.Kashtanka 会的单词的头是密码的尾，会的单词的尾是密码的头，必须两个同时满足才行。

以下为代码，更详细的解释都在里面。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	char a[3];//密码
	int n;//会的单词个数
	cin>>a>>n;//输入
	bool x=0,y=0;//标记第二种情况
	char b[3];//会的单词
	for(int i=1;i<=n;i++)//循环输入会的单词
	{
		cin>>b;//逐个输入
		if(a[0]==b[0]&&a[1]==b[1])//刚好就是原密码
		{
			cout<<"YES"<<endl;//正解
			return 0;//结束代码
		}
		if(a[0]==b[1]) x=1;//a头和b尾是一样的
		if(a[1]==b[0]) y=1;//a尾和b头是一样的
	}
	if(x==1&&y==1)//可以两个单词拼在一起组成密码
	{
		cout<<"YES"<<endl;//正解
		return 0;//结束代码
	}
	cout<<"NO"<<endl;//剩下的全部输出NO
	return 0;
}
```


---

## 作者：liuyifan (赞：1)

## 模拟,使用系统字符串函数可以快速AC
O(n^2)暴力枚举即可,对于这道题的数据范围可以通过

code:(注释下面有)
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
int n;
char str[1000],s[1000][1000],tmp[1000];//定义 
int main()
{
    scanf("%s%d",str,&n);//字符数组不用加& 
    for(reg int i=1;i<=n;i++)scanf("%s",s[i]);//scanf读入char数组 
    for(reg int i=1;i<=n;i++)
    for(reg int j=1;j<=n;j++)//O(n^2)暴力,能AC 
	{
        strcpy(tmp,s[i]),strcat(tmp,s[j]);
        //strcpy拷贝,strcat连接 
        if(strstr(tmp,str))return puts("YES"),0;//={puts("YES");return 0;} 
        //strstr判断是不是子串 
    }
    return puts("NO"),0;//同上 
}
//拒绝抄袭,共建和谐洛谷 
```

---

## 作者：xiezihan (赞：0)

看到没有**C语言**的，~~赶紧水一发~~



------------
其实，这道题的意思就是有三种情况
```
1、Kashtanka 会的只有解锁的单词

2、Kashtanka 会的单词的第二个字符就是解锁单词的第一个字符(好绕啊）

3、Kashtanka 会的单词的第一个字符就是解锁单词的第二个字符
```

然后就真的没什么东西了，上代码



------------
```c
#include<stdio.h>
int main()
{
	int x=0,y=0,i,n,flag=0;
	char a[10],b[10];
	scanf("%s%d",&a,&n);
	for(i=1;i<=n;i++)
	{
		scanf("%s",&b);
		if(b[1]==a[1]&&b[0]==a[0])
		{
			printf("YES");
			return 0;
		}
		if(b[0]==a[1])x=1;
		if(b[1]==a[0])y=1;
		if(x&&y)
		{
			printf("YES");
			return 0;
		}
	}
	printf("NO");
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/34099658)

---

## 作者：Thomas_Cat (赞：0)

那么这道题我们就直接判断就行了，这里分为两种情况：

- Kashtanka 会的单词正好是密码
- Kashtanka 会的单词第一种最后和第二种第一个正好是密码

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//using 不多说
char a[3],b[3];//字符串
int n;
int main(){
    bool YES=0;//定义判断最后的条件
    cin>>a>>n;//输入
    for(int i=1;i<=n;i++){//循环输入
        cin>>b;
        if(b[1]==a[1]&&b[0]==a[0]) YES=1;//如果满足情况第一种，YES
        if(b[0]==a[1]&&b[1]==a[0]) YES=1;//如果满足情况第二种，YES
    }
    if(YES==0) cout<<"NO";//输出NO
    if(YES==1) cout<<"YES";//输出YES
    return 0;//华丽结束
}
```

---

## 作者：风人 (赞：0)

+ 当你看到我的时候就知道这是道水题

 # 题解 [CF868A](https://www.luogu.com.cn/problem/CF868A)
 

### 思路：

总之就三种情况：

   1. Kashtanka 会的就是解锁的单词。
   2. Kashtanka 会的单词的第二个（末尾）字符为解锁单词的第一个字符。
   3. Kashtanka 会的单词的第一个（开头）字符为解锁单词的第二个字符。
   
易得，当满足情况1或情况2、3同时满足时，是可以解锁的，否则不能。

----

### 代码
```cpp
#include<iostream>
using namespace std;
char a[3],b[3];
bool k1,k2;
int n;
int main(){
    cin >> a >> n;
    for (int i = 1;i <= n;i++){
        cin >> b;
        if(b[1] == a[1] && b[0] == a[0]) goto YES; //情况一
        if(b[0] == a[1]) k1 = 1; //情况2
        if(b[1] == a[0]) k2 = 1; //情况3
        if(k1 && k2) goto YES; //同时满足情况1和2
    }
    cout << "NO";
    return 0;
    
    YES: //满足条件
    cout << "YES";
    return 0;
}
```

---

