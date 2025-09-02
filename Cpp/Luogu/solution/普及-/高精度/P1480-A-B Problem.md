# A/B Problem

## 题目描述

输入两个整数 $a,b$，输出它们的商。


## 说明/提示

$0\le a\le 10^{5000}$，$1\le b\le 10^9$。

## 样例 #1

### 输入

```
10
2```

### 输出

```
5```

# 题解

## 作者：Idoyt (赞：539)

我不会说Python是自带高精的
```python
a , b = int(input()),int(input())
print (a // b)
```

---

## 作者：Timothy (赞：50)

这是一题高精除单精的题目，会高精的人细细想一下，就应该会做。代码如下（请勿抄袭）：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
char a1[10001];
long long b,c[10001],d,a[10001],len,lenc;
int main ()
{
    cin >>a1 >>b;//读入被除数和除数
    len=strlen(a1);//把被除数的位数存在len里
    for (int i=1;i<=len;i++)a[i]=a1[i-1]-'0';//将被除数一位一位放入a数组
    for (int i=1;i<=len;++i)//这一个循环是关键，将被除数一位一位除以除数，不过除，向下
   {                                //一位借位，d为余数，c数组为商
        c[i]=(d*10+a[i])/b;
        d=(d*10+a[i])%b;
    }
    lenc=1;
    while (c[lenc]==0&&lenc<len)lenc++;//整理位数，删除前导0
    for (int i=lenc;i<=len;++i)cout <<c[i]; //输出结果
    return 0;
}

```

---

## 作者：lyl81585777 (赞：28)

高精度除法之高精除以低精





```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <math.h>
#include <algorithm>
using namespace std;
string st1;
long long s,i,x,n,a[10001],l1,b[10001];
int main()
{
    cin >> st1 >> s ;
    l1=st1.size();
    for (i=1; i<=l1; ++i)    a[i]=int(st1[i-1])-48;
    for (i=1; i<=l1; ++i)
    {
        x=x*10+a[i];
        b[i]=x / s;
        x=x % s;
    }
    n=1;
    while (b[n]==0 && n<l1) n++;
    for (i=n; i<=l1; ++i)    cout << b[i] ;
    cout << endl ;
    return 0;
}
```

---

## 作者：wei2013 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P1480)

# 思路：

一看题目，这不简单然后就……$48 pts$。
再一看高精度还有俩参数，高精度对高精度那可就难了，再看题目，哦，是高精度对低精度，$b$ 不是高精度数，我们模仿除法算法自己重载运算符即可。

# code1（python）：
```python
a=int(input())
b=int(input())
print(a//b)
```

# code2（c++）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	string a;
	long long b; 
	cin>>a>>b;
	if(a[0]=='0' || b==0){
		cout<<0;
		return 0;
	}
	long long len=a.size(),r=a[0]-'0';
	bool ok=0;
	for(long long i=1;i<len;i++){
		long long num=(r*10+a[i]-'0')/b;// 计算这一位的积。
		r=(r*10+a[i]-'0')%b;// 计算余数。
		if(num>0){
			cout<<num;
			ok=1;
		}else if(ok==1){
			cout<<0;
		}
	}
	return 0;
}
```
望审核通过！


---

## 作者：封禁用户 (赞：5)

这是一道高精除低精模板题。

类似于模拟除法竖式吧？

模拟竖式被除数的每一位加上余数除以被除数并更新余数的过程即可。

不过要注意一下：在数 $a$ 后面拼上一位数 $b$ 是 $10a+b$。

自己推一下竖式就可以理解了。

记得最后要去除前导零。

直接上~~丑陋的~~代码的主要部分：
```cpp
#define int long long
string operator/(string s1,int s2){
    string r;
    int l1=s1.size(),x=0,a[N]={0},c[N]={0};
    for(int i=0;i<l1;i++)a[i]=s1[l1-i-1]-'0';//倒叙存储
    for(int i=l1;i>=0;i--)c[i]=(x*10+a[i])/s2,x=(x*10+a[i])%s2;//看看这一位的值是多少 且 更新余数
    while(!c[l1-1]&&l1>1)l1--;//去前导零
    for(int i=l1-1;i>=0;i--)r+=c[i]+'0';//倒叙取出结果
    return r;
}
```
~~其实 python 也行。~~

---

## 作者：tallnut (赞：3)

高精除低精模板题。

回忆一下~~小学的~~列竖式。我们用被除数的每一位除以除数，求出余数，再接着往余数的后面添加下一位数，以此类推。

所以我们这题也直接这样模拟即可。

不过要注意，向一个数 $n$ 的后面添加一个一位数 $m$ 应该这样做：
$$n\gets n\times 10+m$$

最后去一下前导零，把答案数组扫一遍即可。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/121950911)。
```
#include <iostream>
#include <algorithm>
using namespace std;
int a[5001];
int quotient[5001];
int main()
{
	string s;
	int b;
	cin >> s >> b;
	reverse(s.begin(),s.end());
	for (int i = 0;i < s.size();i++)
		a[i + 1] = s[i] - '0';
	long long tmp = 0;
	for (int i = s.size();i >= 1;i--)
	{
		tmp *= 10;
		tmp += a[i];
		quotient[i] = tmp / b;
		tmp %= b;
	}
	int i = 5000;
	for (;(i >= 2) && (quotient[i] == 0);i--);
	for (;i >= 1;i--)
		cout << quotient[i];
}
```
当然。。。用 Python 也不是不可以。。。

---

## 作者：MuYC (赞：3)

```cpp
#include <bits/stdc++.h>
//这个题目我采用模拟竖式的写法来做
char a1[10050];
long long a[10005];
using namespace std;
int main(){
	long long i,j,k,n,m,x,flag=0;
	cin>>a1;//读入被除数
	cin>>n;//读入除数
	for(i=0;i<strlen(a1);i++)
		a[i+1]=a1[i]-'0';//转换格式
	for(i=1;i<=strlen(a1);i++){
		x=a[i]/n;//求得的结果
		a[i+1]+=(a[i]%n)*10;//余数处理
		if(x!=0||flag!=0)cout<<x;//如果不是首位或者是首位不是0就输出
		if(x!=0)flag=1;//标记为非首位
	}
	if(flag==0)cout<<0;//如果除数大于被除数，输出0
	return 0;
} 
```

---

## 作者：Goder (赞：3)

简单的高精度除法：

```cpp
const max=5000;
var a,c:array[1..max] of longint;;
      x,b,lena,i,j:longint;
      n1,n2:ansistring;
begin
    readln(n1);
    readln(n2);
    lena:=length(n1);
    for i:=1 to lena do a[i]:=ord(n1[i])-48;
    val(n2,b);
    x:=0;
    for i:=1 to lena do
        begin
            c[i]:=(x*10+a[i]) div b;
            x:=(x*10+a[i]) mod b;
        end;
    j:=1;
    while (c[j]=0) and (j<lena) do inc(j);
    for i:=j to lena do write(c[i]);
end. 
这道题应该算入门级别的哦！
```

---

## 作者：封禁用户 (赞：3)

#这题数据较大(a<=10^5000,b<=10^9)，因此这题需要使用高精度除法来做，提供参考程序及详解。

【思路详解】

这里，我们讨论一下高精度除以单精度数的结果，采取按位相除法。

【参考程序】

```cpp
program P1480;
var a,c:array[0..5005] of longint;
      x,b,lena,i,j:longint;
      n1,n2:ansistring;
begin
    readln(n1);
    readln(n2);
    lena:=length(n1);
    for i:=1 to lena do a[i]:=ord(n1[i])-48;
    val(n2,b);        {字符串N2转换成数值B}
    x:=0;
    for i:=1 to lena do           {按位相除}
        begin
            c[i]:=(x*10+a[i]) div b;
            x:=(x*10+a[i]) mod b;
        end;
    j:=1;
    while (c[j]=0) and (j<lena) do inc(j);       {去除高位的0}
    for i:=j to lena do write(c[i]);
end.
```

---

## 作者：Dijkstra49 (赞：2)

```cpp
#include<iostream>
#include<cstdio>
//#include<algorithm>
//#include<cstring>
#include<string>
using namespace std;
typedef long long ll;
string a;
ll b[10001],n,x,t;
int main()
{
    cin>>a>>n;
    ll qq=a.length();
    for(ll i=0;i<qq;i++)a[i]-='0';//转数字编号
    for(ll i=0;i<qq;i++){
        x=x*10+a[i];
        b[i]=x/n;
        x%=n;
    }//模拟竖式开始除
    for(ll i=0;i<qq;i++)if(b[i]){t=i;break;}//去除前导0
    if(t==qq){cout<<0<<endl;return 0;}//如果只有0就输出0
    for(ll i=t;i<qq;i++)cout<<b[i];//输出证书部分
}
```

---

