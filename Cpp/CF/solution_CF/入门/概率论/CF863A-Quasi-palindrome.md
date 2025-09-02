# Quasi-palindrome

## 题目描述

Let quasi-palindromic number be such number that adding some leading zeros (possible none) to it produces a palindromic string.

String $ t $ is called a palindrome, if it reads the same from left to right and from right to left.

For example, numbers $ 131 $ and $ 2010200 $ are quasi-palindromic, they can be transformed to strings " $ 131 $ " and " $ 002010200 $ ", respectively, which are palindromes.

You are given some integer number $ x $ . Check if it's a quasi-palindromic number.

## 样例 #1

### 输入

```
131
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
320
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2010200
```

### 输出

```
YES
```

# 题解

## 作者：dsaykc233 (赞：1)

 ~~一道需要一点思想的题目~~QWQ

[题目传送门](https://www.luogu.com.cn/problem/CF863A)

本题思路如下

因为n加上前导0要使其变成回文数，那么末尾要有对应的0。

那么做法便是 n去掉后缀0后，是回文数便输出“YES”，否则输出“NO"。

别的话便不多说了，直接上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define	fo(a,b,c) for(int a=b;a<=c;++a)
#define fr(a,b,c) for(int a=b;a>=c;--a)
#define ll long long
bool check(int n)//判断n是否为回文数 
{
	int s=0,x=n;
	while(x)
	{
	  s=s*10+x%10;
	  x/=10;
	}
	if(s==n)
          return true;
	else
    	  return false;	
}
int main()
{
	int n;
	scanf("%d",&n);
	while(1)//删后缀0 
	{
	  int x=n%10;
	  if(x)break;
	  n/=10;
	}
	if(check(n))
	  cout<<"YES";
	else
	  cout<<"NO";	
    return 0;
}

```


---

## 作者：houyinuo (赞：1)

~~涨个咕值我容易吗~~

这道题是让我们在前面加0使其构成一个回文串，由于回文串是对称的，所以在前面加0和在后面减0对于回文串来说是一样的，所以我们直接将串后面的0全部去掉，在判断剩下的串是不是回文就可以了。

主要代码：
```cpp
for (;i<=j;i++,j--) if (a[i]!=a[j]){printf ("NO");return 0;}
printf ("YES");
```
此处的i等于第1个字符的下标（因为题目中说了不会又前导0，所以不用判断），j是从后往前的第一个不是0的字符的下标。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[15];
int main (){
	scanf ("%s",a+1);
	int l=strlen(a+1),i=1,j;
	for (j=l;j>=1&&a[j]=='0';j--);//求从后往前的第一个不是0的字符的下标
	for (;i<=j;i++,j--) if (a[i]!=a[j]){printf ("NO");return 0;}
	printf ("YES");
    return 0;
}
```
~~不求赞，不求关~~

---

## 作者：智子·起源 (赞：1)

### 下面的题解我觉得比较乱，所以在这里提供一篇清晰一点的。

对于准回文数的定义是：加上若干个前导0（包括0个）可以使其变成回文数的数。

接下来我们想：为什么要加前导0呢？肯定是因为后面有0，前面的0的作用就是为了和后面的0形成对称。


### 所以我们只要把后面的0全部删掉，看看它是不是个回文数就可以了。

其原理如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/26i3gfrj.png)

上代码：

```cpp
#include<iostream>
#include<string>
using namespace std;
string ss,s;int s_len;
int main()
{
  cin>>s;s_len=s.size();
  while(s[s_len-1]=='0'&&s_len>1)s_len--;
  for(int i=s_len-1;i>=0;i--)ss+=s[i];
  if(ss==s.substr(0,s_len))cout<<"YES";
  else cout<<"NO";
  return 0;
}

```


---

## 作者：Porsche (赞：1)

大佬的题解都好大佬，各种函数，本宝宝表示好6P

本题让在前面加上若干个0，判断是否可以成为回文串，那么我们不妨去除后缀0，在判断是不是回文串

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string str;//string类型的更方便一些
int main()
{
	cin>>str;//string类型为C++特有，所以不能使用scanf输入
	int len=str.length();//求出str的长度
	for(int i=len-1;i>=0;i--)//去除后缀0的操作
	{
		if(str[i]!='0')
		{
			len=++i;//因为string类型输入时从第0位开始输入，所以此处需要让len=i+1
			break;
		}
	}
	for(int i=0;i<=len/2-1;i++)//判断是否为回文串
	{
		if(str[i]!=str[len-1-i])
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：happybob (赞：0)

其实我们只需要按照程序模拟即可，读入一个字符串，在前面加前导0，同时做一个判断回文函数：

```cpp
bool huiwen(string s)
{
    string x = s;
    reverse(x.begin(), x.end());
    return x == s;
}

```
接下来511ms的简单代码来啦：

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

string s;

bool huiwen(string s)//判断是否回文
{
    string x = s;
    reverse(x.begin(), x.end());
    return x == s;
}

int main()
{
    cin >> s;
    if(huiwen(s))
    {
        cout << "YES\n";
        return 0;
    }
    for(int i = 1; i <= 10; i++)//10遍就够了
    {
        s = '0' + s;//注意是'0'+ s不是s + '0'
        if(huiwen(s))//如果是回文就是YES
        {
            cout << "YES\n";//不然就是NO
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
```


---

## 作者：Franka (赞：0)

### **题目**
准回文数是这样一个数字，在这个数字的前面添加一些前导0（可能不添加），使它变成一个回文串。现在给你一个数，判断是否为准回文数。
### **思路**
既然说要在**前面添加0**，那我们不妨把**后面的0全部删除**，再判断删完的数是否是回文数。

考虑到判断回文数，用**字符串**更简便。

将后面的0全部删除，就要用到一个函数：$delete$。

$delete$的作用：举个栗子，$delete('123',2,1)$表示从**字符串**123中，从第二位开始，删除一个。

那么将后面的0全部删除这一操作的代码也就出来了（如下）

$while$ $n[length(n)]='0'$ $do$ $delete(n,length(n),1);$

上面一个程序的解$(ren)$释$(hua)$：当**字符串**$n$的最后一位为$0$时，删除最后一位。

### **代码**
```pascal
var
  n:string;//定义n字符串
 function work(n:string):string;//判断回文数的函数
  var
    i:longint;
  begin
    for i:=1 to length(n) div 2 do if n[length(n)-i+1]<>n[i] then exit('NO');//若不成回文数，输出NO
    exit('YES');//成回文数
  end;
begin
  readln(n);//读入n
  while n[length(n)]='0' do delete(n,length(n),1);//删除末尾0
  writeln(work(n));//输出
end.//求过QwQ
```


---

## 作者：FR_qwq (赞：0)

这题，我们珂以换一个思路，就是把那个数的末尾的 0 删掉，然后判断它是否是回文数，这样就珂以节省时间和空间。

判断一个数是否是回文数的代码如下：

```pascal
function pd(s:string):boolean;
var i:longint;//定义
begin
for i:=1 to length(s)div 2{这里要用 div 2 ，因为这样珂以节省时间} do
  if(s[i]<>s[length(s)-i+1])then exit(false);//如果不相等，退出，返回错误
exit(true);
end;
```

AC 代码：

```pascal
var s:string;
k:longint;
function pd(s:string):boolean;
var i:longint;
begin
for i:=1 to length(s)div 2 do
  if(s[i]<>s[length(s)-i+1])then exit(false);
exit(true);
end;//判断
begin
readln(s);//读入
k:=length(s);
while(k>0)and(s[k]='0')do begin delete(s,k,1);dec(k);end;//删0
if(pd(s))then writeln('YES')
else writeln('NO');//判断后输出
end.
```

---

## 作者：Erusel (赞：0)

这是很久以前写的远古题解

---

给一种更 _**STL**_ 的做法

思路还是那样，删除前导0之后判断回文。

删除时可以使用STL的 _**erase**_ 函数删除，erase(pos,len)代表从pos位开始删除len位

判断回文时可以采用STL的 _**reverse**_ 函数 ,reverse(s.begin(),s.end())代表将字符串s反转。

代码：
```
#include<bits/stdc++.h>

using namespace std;

string s;
bool check(string s)
{
	string s1=s;
	reverse(s.begin(),s.end());
	if(s1==s)return true;
	return false;
}

int main()
{
	cin>>s;
	int l=s.length();
	int i=l-1;
	while(s[i]=='0')
	{
		s.erase(i,1);
		i--;
	}
	if(check(s))cout<<"YES"<<endl;
	else cout<<"NO"<<endl;

	return 0;
}
```

---

## 作者：Core (赞：0)

其实这题就是基本回文字符串考察。

基本思路：先将字符串末尾的0删去（因为有几个0都能加在前面），然后判断是否回文。

代码：

```
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int check(char a[])      //判断
{
    int k=strlen(a);   //先求出字符串长度
    for(int i=k-1;i>=0;i--)     //从最后一位往前循环
    {
        if(a[i]=='0') k--;     //如果为0位数就减1
        else break;      //如果不是0立刻退出
    }
    for(int i=0;i<k;i++)    //回文判断
    {
        if(a[i]!=a[k-i-1]) return 0;    //如果不回文就返回0
    }
    return 1;   //回文
}
char a[15];   //定义数组
int main()
{
    cin>>a;  //输入
    if(check(a)) cout<<"YES"<<endl;   //回文输出YES
    else cout<<"NO"<<endl;    //不回文输出NO
    return 0;  //退出
}
```

---

## 作者：brealid (赞：0)

此题本质上是：**求一个数去掉后缀零后是否是回文串**

因此，代码分为：
```
>>> 读入
>>> 删除后缀0
>>> 判断回文
	>>> 转为数组存储
    >>> 依次比较开头和结尾是否相同（头指针后移，尾指针前移）
>>> 输出结果
```

所以，我们有了：
```cpp
#include <?????.?>		//杜绝抄袭！

??? main()				//杜绝抄袭！
{
	int n;
    
    //读入
	scanf("%d", &n);	
    
    //删除后缀0
	while (n % 10 == 0) n /= 10;		
    
    int a[10], len = 0;		//a存储数组形式的n
    bool huiwen = true;		//删除后缀0的n是否是回文
    
    //转为数组存储
	while (n != 0) a[m++] = n % 10, n /= 10;
    
    
    //依次比较开头和结尾是否相同（头指针后移，尾指针前移）
	for (int i = 0, j = m - 1; i <= j; i++, j--)
		if (a[i] != a[j]) huiwen = false;		
        
    //输出
	if (huiwen)
    	printf("YES");
    else
        printf("NO");
    return 0;
} 
avoiding plagiarism!						//杜绝抄袭！
```

---

## 作者：SocietyNiu (赞：0)

## ~~日常水题~~
这道题十分的简单，主要的思路是调转字符串后根据前导0添加后导0，最后再判断字符串是否相等，代码如下
```
#include<iostream>
using namespace std;
void turn(string &n)//自定义翻转函数，必须&！是传址调用
{
	string a;
	for(int i=n.length()-1;i>=0;i--)
		a+=n[i];//string的好处，可以直接加到后面的！！
	n=a;
}
int main()
{
	string n;cin>>n;
	turn(n);//先翻转
    int begin=0;
	while(n[begin]=='0') //前导0决定循环，而循环决定添加的后导0个数
		n+='0',begin++;//string好处，可以直接加
	string b;
	b=n;//先保存n
	turn(n);//再翻转
	if(n==b) cout<<"YES";
	else cout<<"NO";
	return 0;
}
```

---

## 作者：PC_DOS (赞：0)

这是一道字符串模拟题，为了处理前导零的问题，我们可以按照字符串的形式读入数字，统计其结尾'0'的个数并在字符串开头补上相应个数的'0'并判断是不是回文即可。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
string strReverse(string strOrigin){ //字符串反转函数
	if (strOrigin.length() == 0){
		return "";
	}
	long long i;
	string ans;
	for (i = strOrigin.length() - 1; i >= 0; --i) ans += strOrigin[i];
	return ans;
}
string CreateRequiedString(long long nCount, char chrChrarater){ //根据给定的字符chrChrarater创建指定长度的字符串
	int i;
	string sAns;
	for (i = 1; i <= nCount; ++i)
		sAns += chrChrarater;
	return sAns;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sNum; //字符串形式的数字
	int i, nZero=0, iLength; //i-循环计数器；nZero-字符串末尾'0'的个数；iLength-字符串长度
	cin >> sNum; //读入数字
	iLength = sNum.length(); //计算长度
	for (i = iLength - 1; i >= 0; --i){ //倒序遍历字符串，统计其结尾'0'的个数
		if (sNum[i] == '0') //是'0'
			++nZero; //个数加1
		else //否则
			break; //结束循环
	}
	sNum = CreateRequiedString(nZero, '0') + sNum; //在字符串开头补上相应个数的'0'
	if (sNum == strReverse(sNum)) //判断是不是回文
		cout << "YES";
	else
		cout << "NO";
	return 0; //结束
}
```

---

