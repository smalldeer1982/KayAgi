# Minimum Binary Number

## 题目描述

给定一个二进制数（没有多余前导0），可以对这个二进制数执行两种操作：

1. 交换相邻数位的数字；
2. 用 1 代替 11（例如 110 变成 10）。

输出执行任意操作（或者不操作）后这些二进制数中最小的二进制数。

## 样例 #1

### 输入

```
4
1001
```

### 输出

```
100
```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
1
```

# 题解

## 作者：thomas_zjl (赞：6)

### 这道题是一道非常水的字符串题。

题目是让你输入一个长$n$二进制数$s$，然后进行一些移位操作来得到最小的二进制数 $($ 而且用$1$代替$11$$)$。 

由于这道题目里规定是二进制,所以只有$0$和$1$。

而且最后这个式子只会留下$1$个$1$。

让我们来对样例进行一次模拟。

样例一：

$4$

$1001$

首先我们来找一下$0$的个数，有$2$个，记为$sum$。

然后输出$1$和$sum$个$0$，为100。

接下来就是我的代码了。

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;
	int n;
	cin>>n;
	cin>>a;
	int sum=0;
	if(a=="0")//这里有特判，如果a为0的话，直接输出0。
	{
		cout<<0;
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		if(a[i]=='0')
		{
			sum++;
		}
		//如果a[i]为0的话，sum就要+1。                  
	}
	cout<<1;
	//开始直接输出1。
	for(int i=0;i<sum;i++)
	{
		cout<<0;
	}
  	//输出sum个0。
    return 0;//完美结束！
}
```


---

## 作者：Yi_Fan (赞：1)

## 前言：
第一次写题解有一点点小紧张

------------
## 题意：
- 给你一个长度为 $n$ 的数（只含 $1$ 和 $0$ ）
- 两位可以换位置，两个1可以换为一个1
	
可以得出：

   当有$1$时，$0$ 无法处理， $1$ 最后会剩一个
    
------------

## 思路
- 当只有一位时直接输出
- 如果大于$2$位，就统计$0$的个数,第一位一定是$1$，接下来是多个$0$


------------
## 代码
```cpp
#include<bits/stdc++.h>//万能头好评 
using namespace std;
int n;
char s;
int a=0;//统计0的个数 
int main() {
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;//读入每一位 
		if(n==1)//只有一位 
		{
			cout<<s<<endl;
			return 0;//提前结束 
		}
		if(s=='0'){//统计0 
		a++;
		}
	}
	cout<<'1';//最后剩一个1 
	for(int i=1;i<=a;i++){
		cout<<'0';
	}
	return 0;//好习惯 
}
```


---

## 作者：Zhoumy (赞：1)

我们发现不管有多少个1，都可以通过转换视为1个1。  
所以如果有一个1的话就输出一个1，其他的按位数输出0就行了。
```
#include<iostream>
#include<string>
using namespace std;
string a;
int main(){
	cin>>a>>a;//第一个a是输入多少位，对于string来说没什么意义，所以不用管
	if(a!="0")cout<<1;//特判为0的情况
	for(int i=0;i<=int(a.size())-1;i++)if(a[i]=='0')cout<<0;//如果原来的有0就输出0
	return 0;
}

```

---

## 作者：yf最qhhh (赞：0)

这道题我居然做了[这么久](https://www.luogu.com.cn/record/list?pid=CF976A&user=yf%E6%9C%80qhhh&page=1)。。。。。

首先，任意两位可以互相交换且无次数限制说明我们可以把这个数排列成任意我们想要的形式。

$11$ 可以变成 $1$ 说明无论如何这个二进制数最后 $1$ 都只剩下一个。~~（我就是因为忽略了这一点才做这么久qwq）~~

所以要使它最小，只需把那个 $1$ 放在首位保证数合法，$0$ 按照个数输出在后面就好了。

再说简单点，就是求0的个数。

所以就做完了。

$Code$:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rll register long long
using namespace std;
const int MAX_N=1e2+5;
ll a[MAX_N],N,i,ans;
inline bool cmp(rll a,rll b){return a>b;}
int main(){
	scanf("%lld",&N);
	string s;cin>>s;
	if(s=="0")return printf("0"),0;//0的特判
	for(i=1;i<=N;i++)a[i]=s[i-1]-'0';//我做复杂了，其实可以直接找的。。。主要是我的思路是排序
	sort(a+1,a+1+N,cmp);//从大到小排序。
	for(i=1;i<=N&&a[i];i++);//把1都先跳过
	printf("1");//首位输出1
	for(;i<=N;i++)printf("0");//0直接输出
	return 0;
}
```

---

## 作者：REAL_曼巴 (赞：0)

此题是说要求二进制数经过若干次两种操作后，这个数最小能变成几。我们可以把二进制数看成是普通的数，因让数最小，要让位数尽量少。我们不难发现，通过第一种操作把“一”都凑到一起，再通过第二种操作可以把这个数中的所有“一”都去除，最后只剩一个“一”。因为“零”不能为首位，只能让唯一一个“一”做首位，剩下有多少个零就在后面输出几个。所以，经过以上推理，此题的方法就变成了先统计一个数中“零”的个数，再输出一个“一”，接着数中有几个“零”就输出几个就行了。

```cpp
#include<iostream>
using namespace std;
string s;
int n;
int sum=0;//清零保险
int main(){
    cin>>n>>s;//输入数的长度及这个数，我们因已知道操作方法，用字符串也行
    if(s=="0"){//特判0
        cout<<'0';
        return 0;
    }
    for(int i=1;i<=n;i++)//统计0的个数
        if(s[i]=='0')
            sum++;
    cout<<'1';//输出首位1
    for(int i=1;i<=sum;i++)
        cout<<'0';//有几个零就输出几个
    return 0;
}

```


---

## 作者：人间凡人 (赞：0)

### 多举几个栗子，可以发现这题大概的意思为：

给定一个字符串。统计其中 $0$ 的个数$，$如果0的个数为 $0$，那么就输出 $0$，不然就先输出 $1$，然后输出字符串内所有的 $0$$。$

来把样例模拟一下：

$S:1001$ 

$0$的个数$：$ $2>0$ 

所以先输出$1,$然后输出$2$个$0$$,$就是$100$

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int len,ans;
char ch[105];
int main(){
	scanf("%d\n",&len);
	ans=0;
	for(int i=0;i<len;i++){
		scanf("%c",&ch[i]);
		ans=ans+(1-(ch[i]-'0'));//统计0的个数
	}
	if(ans==len)printf("0\n");
	else {
		printf("1");
		for(int i=1;i<=ans;i++)printf("0");
	}
	return 0;
}
```




---

## 作者：ACE_ZY (赞：0)

题意差不多就是:

如果有1，就先输出1个1，然后再输入所有的0;

如果没有1,就输出0。

```pascal
var
  i,s1,s2,n:longint;
  x:char;
begin
  readln(n);
  for i:=1 to n do//统计0或1的个数
  begin
    read(x);
    if x='1' then inc(s1) else inc(s2);
  end;
  if (s1=0) then begin writeln(0);exit;end;//如果没有1，直接输出0
  if s1>=1 then write(1);//只要有1，就先输出1个1
  for i:=1 to s2 do write(0);//输出剩下的0
  writeln;
end.
```


---

## 作者：OdtreePrince (赞：0)

# -字符串儿-

先来个特判，如果输入的字符串为零，输出零

否则，字符串的开头一定是1，无法消掉所有的一，只需输出一个1,。接着统计0的数量，输出所有零。

AC喽！！！！！！！！！

~~~
#include<bits/stdc++.h>
using namespace std;
int sum,l;
int main(){
    string s;
    cin>>l>>s;
    if(s=="0"){
        cout<<0;
        return 0;
    }
    cout<<1;
    for(int i=0;i<l;i++){
        if(s[i]=='0') sum++;
    }
    for(int i=1;i<=sum;i++){
        cout<<0;
    }
    return 0;
}
~~~

---

