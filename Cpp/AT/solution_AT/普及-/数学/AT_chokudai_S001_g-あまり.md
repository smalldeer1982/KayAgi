# あまり

## 题目描述

有一个长度为n的数列a，你需要把这个数列里的所有数从左到右拼接起来形成一个数，然后把这个数%$1,000,000,007(1e9+7)$并输出。

## 说明/提示

$1 ≤ N ≤ 100,000$。

别忘了结尾换行！

## 样例 #1

### 输入

```
5
3 1 5 4 2```

### 输出

```
31542```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
123456```

## 样例 #3

### 输入

```
7
7 6 5 4 3 2 1```

### 输出

```
7654321```

## 样例 #4

### 输入

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
370453866```

# 题解

## 作者：da32s1da (赞：17)

由于string做加法可以连接，于是本题迎刃而解。
```
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
string a,b;
int n;
long long m;
int main(){
	scanf("%d",&n);cin>>a;
	for(int i=1;i<n;i++)cin>>b,a+=b;
	for(int i=0;a[i];i++)
	m=(m*10+a[i]-'0')%mod;
	printf("%lld\n",m);
}
```

---

## 作者：wanghy989 (赞：3)

### 这道题主要考察字符串的运用。直接模拟即可 AC。

### 介绍一个函数：split()。

它可以将字符串分割并转化为列表。

举个栗子：

```python
a = "1 2 3"
a.split()

这时，变量 a 就变成了 ["1","2","3"]
```

#### 不仅如此，split 函数中还可以填内容。

再举个栗子：

```
a = "1s2s3s4s5"
a.split("s")

这时，变量 a 就变成了 ["1","2","3","4","5"]
```

#### 然后，这题就很简单了。

#### Python3 AC 代码：

```python
a = input()
s = input().split()  # 输入，再将字符串分割成列表。
d = ''.join(s)      # 拼接。
print(int(d) % 1000000007)  # 用 int 函数转化为数字类型，对 1e9+7 取余并输出。
```


---

## 作者：gtl_caiji (赞：1)

本蒟蒻感觉自己的虽然麻烦，但却是比较好理解的做法
# 前言
乍一眼看这道题时，吓了没有常识的我一跳，马上去翻自己高精度模板。其实这道题不需要高精度（~~你愿意写也可以~~）

我是主要用了快速幂算法以及字符串

# 主要思路
先让我们利用string的特性，string可以用“+”运算符的，就是把2个字符串拼凑起来，于是我们可以每次输入字符串后就马上相加起来
```cpp
for(int i=1; i<=n; i++)
{
	string tmp;//tmp是每次输入的字符串
	cin>>tmp;
	s+=tmp;//s是整体的字符串
}
```
接着，我们需要把这个字符串转化为long long，我们可以运用~~小学~~的知识得出，第i位就相当于
```
s[i]*10^i//此处i从各位开始计数，个位是第0位
```
于是，我们就可以从末尾到头一次枚举每一位，然后一起相加，最后就是结果了！
# 最重要的部分——快速幂
[推荐一下这道题](https://www.luogu.com.cn/problem/P1226)
具体讲解大家可以看一下这道题的题解

快速幂就是一个求x的y次方然后%mod的算法，这里给一个模板（为了防止你们把这个代码直接套快速幂的题，我特意利用这题数据之水修改个一下，你们不能把P1226AC呦，建议系统学习）

```cpp
const long long mod=1000000007;
long long cf(long long a,long long b)
{
    long long ans=1;
    a=a%mod;
    while(b>0)
    {
        if(b%2==1) ans=(ans*a)%mod;
        b/=2;
        a=(a*a)%mod;
    }
    return ans;
}
```
# 最后就是你们喜欢的代码部分了！

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<stack>
#include<ctime>
#include<map>
#include<list>
using namespace std;

string s;
const long long mod=1000000007;//const就是一个从头到尾都不会改变的数，简称常量 
long long cf(long long a,long long b)//cf就是快速幂的简称 
{
    long long ans=1;//注意：是1，不是0, 
    a=a%mod;
    while(b>0)
    {
        if(b%2==1) ans=(ans*a)%mod;
        b/=2;
        a=(a*a)%mod;
    }
    return ans;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		string tmp;
		cin>>tmp;
		s+=tmp;
	}
	long long len=s.length();
	long long ans=0;//这两个变量用int应该没事，就是我不放心，加一个保险而已 
	for(int i=len-1; i>=0; i--)//倒序，这样就是从个位枚举了 
	{
		ans+=(s[i]-'0')*(cf(10,len-i-1));
		ans%=mod;
	}
	printf("%lld\n",ans);
 	return 0;
}

```


---

## 作者：CZQ_King (赞：1)

看到这种题二话不说就是一句：

py大法好！

------------
做法：

$n$个数输入在第二行，所以利用$Python$整行读入的特性，然后去掉字符串里的所有空格即可。当然记得要模$1e9+7$。

------------
$Python2$代码：
```python
n=raw_input()
b=raw_input() # 整行读入
a=b.replace(" ","") # 替换所有空格
print int(a)%1000000007 # 模1e9+7
```

---

## 作者：LJY_ljy (赞：1)

## 这道题就是一道模拟题（吧）。


------------


### 首先，我们要明白"连接"两个数是什么意思。

举个例子：

23 和 56连接是2356=23*100+56.

666 和 888连接是666888=666*1000+888.

233 和 2826连接时2332826=233*10000+2826.

### 所以，我们可以得到 a和b连接就是a*10^(b的位数)+b.

这道题便迎刃而解了。

------------

### 其次：我们需要掌握一些数学知识：

(a+b) mod k=a mod k + b mod k

(ab) mod k=(a mod k)(b mod k)


------------



## Code：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int MOD=1000000007;//因为要对1e9+7取余
int weinum(int x)//计算x的位数
{
    int cnt=0;
    while (x)
    {
        cnt++;
        x/=10;
    }
    return cnt;
}
long long int cf(int x,int y)// 求 x^y%MOD，用快速幂也可以，但是这道题数据小直接模拟就行了
{
    long long int sum=1;
    for (int i=1;i<=y;i++)
        sum=(sum*x)%MOD;//每一次都要取模，防止溢出
    return sum;
}
int main()
{
    int n;
    long long int ans=0;//记录最终结果
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        ans=(ans*cf(10,weinum(x))+x)%MOD;//公式
    }
    printf("%lld\n",ans);//long long 用printf输出是%ld!!不是%d!
    return 0;
}

```

#### 因为这道题数据水，所以我的算法可以AC,但是正解还是字符串！

### 如果有表达上的不清楚，请及时指出！

---

