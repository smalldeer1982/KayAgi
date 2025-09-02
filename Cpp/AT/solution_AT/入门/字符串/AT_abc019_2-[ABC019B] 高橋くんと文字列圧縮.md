# [ABC019B] 高橋くんと文字列圧縮

## 题目描述

将字符串经过以下步骤压缩后输出：

1. 将字符串$s$按照连续字符分割成若干个子串。
2. 将每个子串里的字符和子串的长度链接起来，形成新的子串。
3. 将若干个新的子串连接起来，形成新的字符串。

例如：字符串`aabbbaad`的压缩过程：

1. 将`aabbbaad`分割成`aa``bbb``aa``d`;
2. 将`aa``bbb``aa``d`转换成`a2``b3``a2``d1`;
3. 将`a2``b3``a2``d1`链接起来形成`a2b3a2d1`。

`a2b3a2d1`就是压缩后的字符串。

## 样例 #1

### 输入

```
aabbbaad```

### 输出

```
a2b3a2d1```

## 样例 #2

### 输入

```
aabbbbbbbbbbbbxyza```

### 输出

```
a2b12x1y1z1a1```

## 样例 #3

### 输入

```
edcba```

### 输出

```
e1d1c1b1a1```

# 题解

## 作者：applese (赞：6)

虽然我的题解可能和下面大佬的题解有点相同（可能吧QAQ

但是我还是来发一个(顺带详细过程QAQ：
```
#include<bits/stdc++.h>
using namespace std;
int sum;   //用于累计数字
int main()
{
    string st;
    cin>>st;
    for(int i=0;i<st.size();i++)
    {
    	if(st[i]==st[i+1])    //当相同时，sum累加
    	{
    		sum++;
		}
		if(st[i]!=st[i+1])    //当不相同时，那么久停止累加，别忘了要加1，因为要包括自己
		{
			cout<<st[i]<<sum+1;
			sum=0;    //要清零
		}
	}
	cout<<endl;    //要做AT的题目就必须要有回车
}
```
如果Oler们**对题解有疑问**请在右侧说QAQ~蟹蟹

---

## 作者：蒟蒻取不来名 (赞：1)

$$QwQ$$
我好蒻啊

（也不知道我是怎么扯这么长的QwQ（顺便求过））
```
#include<iostream>
#include<string>
using namespace std;
int n, i, qwq, qaq;//qwq用来计数
string s, a;//a是当前计数的字符QwQ
int main()
{
	cin >> s;
	n = s.size();
	for(i = 0; i < n; i++){
		if(s.substr(i, 1) == a) {//判断下一个字符与上一个是否相同
		qwq ++;}//相同继续计数
		else {
			if(qaq != 0) cout << a << qwq;//如果不特判开头会多一个0（卡了n久QwQ）
			else qaq = 1;
			qwq = 1;//计数完将qwq定义为1，否则下次计数会出错
			a = s.substr(i, 1);//当当前字符遇上个字符不一样时，计数对象更换，要重新赋值
		}
	}
	cout << a << qwq;//循环结束之后还要输出一次
	return 0;
}
```
PS：AT不换行会听取WA声一片的QwQ

---

## 作者：xxxjz (赞：1)

这题看上去很麻烦，实际上~~更麻烦~~（其实很简单）

俗话说得好：代码虽短，五脏俱全。

好了，现在让我来给你们讲讲这题的思路吧。

首先，我先给大家讲一下我的算法（并不是模拟），而是 
# 搜索。

- 我们可以定义搜索函数的两个参数,一个是要搜索的字符串，一个是位置，我们可以来搜索字符串的位置。

- 我们可以每次累加和。

- 判断如果当前搜索位置不等于下一个位置的话，就输出我们当前位置的字符和累加的和。段代码如下：
```cpp
	if(st[q]!=st[q+1])
	{
		cout<<st[q]<<he;
		he=0;//记得要清0
	}
```
- 记得要有一个退出搜索的条件：就是当当前搜索位置大过字符串的位置，就输出当前字符和累加的和，再退出。段代码如下：
```cpp
	if(q+1>st.size()-1)
	{
		cout<<st[q]<<he<<endl;
		return;
 	}
```
附赠代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
long long he;
void ss(string st,int q)
{
	he++;
	if(q+1>st.size()-1)
	{
		cout<<st[q]<<he<<endl;
		return;
	}
	if(st[q]!=st[q+1])
	{
		cout<<st[q]<<he;
		he=0;
	}
	ss(st,q+1);
}
int main()
{
	cin>>st;
	ss(st,0);
	return 0;
}
```


---

## 作者：林家三少 (赞：1)

一道有关字符串的题目

题目说得挺复杂的，但其实就是输出字符的数量

我也说不了啥了，接下来就直接上程序吧：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
string st;  //那个字符串
int ans=1;  //字符的数量
int main()
{
	cin>>st;  //输入字符串
	for(int i=0;i<=st.size()-1;i++)  //循环
	{
		if(i>=1&&st[i]==st[i-1])  //判断
			ans++;  //答案变量++
		if(i>=1&&st[i]!=st[i-1])  //判断
		{
			cout<<st[i-1]<<ans;  //输出那个字符和数量
			ans=1;  //将变量清成1
		}
	}
	cout<<st[st.size()-1]<<ans;  //最后还要输出
	cout<<"\n";  //输出换行，At要这样的
	return 0;
}
```


---

## 作者：LiveZoom (赞：0)

# 题解 AT1202 【高橋くんと文字列圧縮】
此题是道基础字符串+循环的题目。

我们先设一个变量tot,表示目前连续了几个，并赋初值为1（因为我们是从第二个开始扫）

```cpp
	int tot=1;
```
然后开始循环，就是这题的解题关键：

```cpp
	for(int i=1;i<s.size();i++){//从1开始扫
		if(s[i]==s[i-1])tot++;//若和前一个相同，则继续更新tot
		else{//否则
			cout<<s[i-1]<<tot;//输出前一个字符，和连续个数
			tot=1;//别忘了赋初值为1哦~
		}
	}
```

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	getline(cin,s);
	int tot=1;
	for(int i=1;i<s.size();i++){
		if(s[i]==s[i-1])tot++;
		else{
			cout<<s[i-1]<<tot;
			tot=1;
		}
	}
	cout<<s[s.size()-1]<<tot;//别忘了输出最后一个的连续值哦，因为我们最后还没输出呢
	puts("");//注意换行，AT不换行，暴零两行泪啊！！！
    return 0;
}
```

# The end

---

## 作者：wushuang0828 (赞：0)

题意在讨论帖里有

思路：判断s[i]和s[i+1]是否相等，相等就累加，不相等就将字符以及长度，累加到，s2中

代码如下：
```pascal
var
 s,s2,s3:ansistring;
 i,ss:longint;
begin
 readln(s);
 ss:=1;//最初长度一定是1
 s:=s+' ';//增加空格，不然会201号错误
 for i:=1 to length(s)-1 do//长度要减一，不然也会201号错误
  if s[i]=s[i+1] then inc(ss)//如果相等就累加
     else//不相等
      begin
       str(ss,s3);//将长度转换成字符串
       s2:=s2+s[i]+s3;//s2加上字符以及它的长度
       ss:=1;//最初长度是1
      end;
 writeln(s2);//换行输出
end.
```

---

## 作者：该起什么名字 (赞：0)

依题意模拟
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
char as;
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>s;
	int n=s.size(),sum=1;
	as=s[0];//将第一个字母记录下来
	for(int i=1;i<n;i++)
	{
		if(int(s[i])==int(as)) sum++;//判断连续出现的字母的个数
		else
		{
			cout<<as<<sum;
			as=s[i];
			sum=1;
		}
	}
	cout<<as<<sum<<endl;//因为最后一次没输出，这里输出去，记得加回车
	return 0;
}

```

---

## 作者：凑_友希那 (赞：0)

依据题意模拟即可

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace NOIP2018 {

int main() {
	string lty;
	getline(cin, lty);
	char flag = lty[0];//标记当前连续出现的字母是什么
	int len = lty.length();
	int time = 0;
	putchar(lty[0]);
	for(int i = 0; i < len; i++) {
		if (lty[i] != flag) {
			cout << time;//输出上一个字母的计数器
			putchar(lty[i]);//输出连续出现的字母
			flag = lty[i];//输出并重置flag
			time = 1;
		} else {
			time++;//计数++
		}
	}
	cout << time << endl;
	return 0;
}

}

int main() {
	return NOIP2018::main();
}
```

---

## 作者：I_will (赞：0)

这道题是说：

高橋く要将一个文件压缩，压缩方法为：

* 原文件aabbbaad
* 压缩文件2a3b2a1d
* 压缩过程：

- 首先，将相同的字母分为一组：aa bbb aa d
- 将一组压缩成字母+数量，如aa-->a2 bbb-->b3。


### 特殊判断：
```cpp
	if(p==0||a[n-2]!=x)cout<<x<<m;
```    
* 判断：如果最后一组没有判断，就输出最后一组。
* 注：因为最后一组只有一个时，p=1，要加判断：a[n-1-1]!=x，最后n++，要-1。

送上程序：
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
int n,m,p;
char x;
char a[1005];
int main()
{
while(a[n]=getchar(),a[n]!='\n')
{
	p=0;
	if(x!=a[n])
	{
		if(n!=0)cout<<x<<m;
		x=a[n];
		p=1;
		m=0;
	}
	m++;
	n++;
}
if(p==0||a[n-2]!=x)cout<<x<<m;
cout<<endl;

return 0;
}
    ```

---

