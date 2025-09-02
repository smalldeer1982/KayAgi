# Even Substrings

## 题目描述

You are given a string $ s=s_1s_2\dots s_n $ of length $ n $ , which only contains digits $ 1 $ , $ 2 $ , ..., $ 9 $ .

A substring $ s[l \dots r] $ of $ s $ is a string $ s_l s_{l + 1} s_{l + 2} \ldots s_r $ . A substring $ s[l \dots r] $ of $ s $ is called even if the number represented by it is even.

Find the number of even substrings of $ s $ . Note, that even if some substrings are equal as strings, but have different $ l $ and $ r $ , they are counted as different substrings.

## 说明/提示

In the first example, the $ [l, r] $ pairs corresponding to even substrings are:

- $ s[1 \dots 2] $
- $ s[2 \dots 2] $
- $ s[1 \dots 4] $
- $ s[2 \dots 4] $
- $ s[3 \dots 4] $
- $ s[4 \dots 4] $

In the second example, all $ 10 $ substrings of $ s $ are even substrings. Note, that while substrings $ s[1 \dots 1] $ and $ s[2 \dots 2] $ both define the substring "2", they are still counted as different substrings.

## 样例 #1

### 输入

```
4
1234
```

### 输出

```
6```

## 样例 #2

### 输入

```
4
2244
```

### 输出

```
10```

# 题解

## 作者：Ptilopsis_w (赞：4)

# 1.题意
给定一个长度为 $n$ 的数字字符串，求其中数值为偶数的子串数

# 2.分析
1. 是不是偶数只看个位就可以了，当子串最后一个字符是偶数时就是偶数
2. 例如`123456`这个字符串，我们只对偶数字符分析就可以，当子串的末尾为`2`时，只有`12`，`2`这两个子串，同理末尾为`4`时，只有`1234`，`234`，`34`，`4`这四个子串，即以**第 $i$ 个字符结尾的字串有 $i$ 个**

# 3.代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n, ans;

int main()
{
	scanf("%d", &n);getchar();
	for(int i = 1; i <= n; i++)
	{
		char ch = getchar();
		if(ch%2 == 0)//字符里的数字从'48'开始，和普通数字的奇偶性一样，直接取模即可
			ans += i;//上面得出的结论
	}
	printf("%d", ans);//最后输出即可
}
```

---

## 作者：wuwenjiong (赞：2)

## 题意：
给出一个长度为 $n$ 的字符串，求字符串中有多少个连续的子串所代表的数为偶数，输出个数。
### 分析：
相信大家都知道，一个整数，如果它的最后一位数是偶数，那么这个数就是偶数。知道这个就简单了，我们可以将字符串从前往后遍历，如果是偶数，就将计数器加上这个字符在字符串中的位置，最后输出。

具体代码实现如下：
```cpp
#include<cstdio>
inline int read(){
    char ch=getchar();
    int x=0,f=1;
    while(ch<48||ch>57){
        if(ch=='-')
        	f=-1;
        ch=getchar();
    }
    while(ch>=48&&ch<=57){
        x=(x<<1)+(x<<3)+ch-48;
        ch=getchar();
    }
    return x*f;
}//快速读入
inline void print(int x){
    if(x>9)
        print(x/10);
    putchar(x%10+48);
}//快速输出
int main(){
	int n,i,x,s=0;
	char a;
	n=read();
	for(i=1;i<=n;i++){//循环进行处理
		a=getchar();//输入字符
		x=a-'0';//将字符转换成整数
		if(!(x&1))//判断是否是偶数
			s+=i;//如果是偶数就加上字符的位置
	}
	print(s);//输出
	return 0;
}
```
谢谢！！！

---

## 作者：梦游的小雪球 (赞：2)

## 咳咳，梦雪小课堂开课了：

#### 第15课：Even Substrings


------------
- ## 思路讲解
### 一. 偶数的概念：
文字版：偶数是2的倍数。

式子版：a(偶数）%2==0.

#### 	但如果是字符该怎么办呢？
- 	方法很简单，只要看个位是否为偶数（0,2,4,6,8）即可
### 二.核心——统计第二部.1：
1. 定义一个常数项（s）用来统计次数（累加），补充知识点：因为s是用来累加的，所以s需初始化0，方法是把TA的定义放在主函数上方或在定义时加上=0

1. 统计方法：定义一个循环，从第一个开始（共a个），边输入边判断，若为偶数，则s加上当时的i，因为以TA结尾（见偶数的概念）的数共有i个。
### 三.现在献上代码
#### 梦雪小课堂提醒您：注释很重要

```
#include<iostream>	//或万能头
using namespace std;
int a,s;	//定义，自动初始化0
int main(){
	cin>>a;	//字符个数
	for(int i=1;i<=a;i++){	//二.核心——统计 第二部.1
		char b;
		cin>>b;	//每次的字符
		if(b=='0'||b=='2'||b=='4'||b=='6'||b=='8')
			s+=i;	//核心（详情请见二.核心——统计 第二部）
	}
	cout<<s<<endl;	//输出
    return 0;	//؏؏☝ᖗ乛◡乛ᖘ☝؏؏完美结束
}
```



---

## 作者：Meteorshower_Y (赞：1)

~~21中考已在即，发篇题解涨RP~~

相信题目大家已经看过了，我就不给大家打[链接](https://www.luogu.com.cn/problem/CF1139A)了

### 进入正题
给定一个一个仅由数字构成字符串 S ，问有多少个连续的字串所代表的数为偶数
#### 1.小学必学知识——偶数
偶数即除以 2 余数为 0 的整数，0 也是偶数
#### 2.题目解析
cnt表示下标（此处 $0≤cnt≤n-1$）  
cnt=i，表示第 i 位之前的字串有几个偶数  
换句话说，就是以第 i 位为数字末尾时偶数的个数

所以这时，我们要解决的只有2个问题：  
1. 这一位是不是偶数（众所周知，末尾为偶数的整数必定为偶数）  
2. 以此为为结尾的数字共多少个
#### 3.代码解析
```cpp
for(register int i=0;i<n;i+=1)
	if((s[i]-'0')%2==0)
		ans+=i+1;
```
1. 将字符 0~9 转换为数字类型，只需要减去 0 的ASCII码即可，对 2 取模，得数为 0 则为偶数。
2. 从第 0 位到第 i 位一共 i+1 位（字符串下标从 0 开始），所以将ans加上（i+1），最后ans的值即为答案
#### 4.Code完整版
```cpp
#include<iostream>
#include<string>
using namespace std;
string s;
int ans,n;
int main()
{
	cin>>n>>s;
	for(int i=0;i<n;i+=1)
		if((s[i]-'0')%2==0)
			ans+=i+1;
	cout<<ans;
	return 0;
}
```
#### 5.结语
感谢大家对本蒟蒻的支持，若有错希望及时联系更正


---

## 作者：MilkyCoffee (赞：1)

首先，一个数是偶数，代表着他的个位数为偶数。

所以我们只需枚举这个数中的偶数数位，并且要每次乘以他的位数。

比如说$134$这个数。

他有$134$、$34$、$4$三种情况，也就是正好的唯一的偶数$4$的位数。

代码实现十分简易。

```
// #include <bits/stdc++.h>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long n;
string s;

int main() {
	cin >> n;
	cin >> s;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if ((s[i-1] - '0') % 2 == 0) {
			ans += i;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：_HiKou_ (赞：0)

~~大水题我爱你！~~

我们都知道，判断一个数是否为偶数只需要看这个数的个位数是否为偶数。

但是如果要去重就不好办了。

但是的但是，我们看到说明/提示区域写着：

>Note, that while substrings $s[1…1]$ and $s[2…2]$ both define the substring "2", they are still counted as different substrings.

这句话的意思是说，即使 $s[1…1]$ 和 $s[2…2]$ 这两个字符串都为 "2" ，他们仍然被当做不同的字符串被计数。

也就是说不用去重！

那不就一大水题吗！

也就是说，我们只要枚举个位为偶数的连续的子串就可以求出答案了。

当然，以第 $i$ 个数结尾的连续的子串有 $i$ 个，比如字符串 $114514$，以第 4 个字符 ‘5’结尾的连续的子串共有 4 个，分别是 $s[1...4]$，$s[2...4]$，$s[3...4]$ 和 $s[4...4]$。

所以，得出结论，只要把字符串里所有偶数的位置加起来就得到答案了！


还有一件事，因为输入没有空格，所以要用 char 类型读入再转换为数字。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114514];
int main(){
	int n,i,sum=0;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		char w;
		cin>>w;
		a[i]=w-'0';
	}
	
	for(i=1;i<=n;i++)
	sum+=(a[i]%2==0)*i;
	
	cout<<sum;
	
	return 0;
}
```

---

## 作者：Jekyll_Y (赞：0)

## 题意
长度为$n$的字符串中有多少个连续的子串为偶数。
## 思路
只要个位偶数就可以了。所以我们只需要将这个字符串遍历一遍找到偶数时，再加上此时的下标就可以了。
## 代码
```c
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
int n,ans;string xx;
int main()
{
	cin>>n>>xx;
	for(int i=0;i<n;i++)
	{
		if((int(xx[i])-'0')%2==0)ans+=i+1;
	}
	cout<<ans;
	return 0;
}
```
### 完结撒花


---

## 作者：wfycsw (赞：0)

- ## 首先，我们要读懂题。
题中所说的**连续的子串所代表的整数为偶数**，其实就是说一个数字串它的**最后一位是0,2,4,6,8**。而题目求的是有多少这样的数字串，当读懂题后，这就是一个非常简单的题了。

- ## 方法
其实只要确定了**最后一为数的位置**，那么以它结尾的数字串的个数就是它的**下标所表示的数值
**。
比如：$1352$只有$2$一个偶数，则他所包含的数字串就有$2,52,352,1352$这四个，很明显就是从一位数到i位数算，其中i最大为它的下标（从一开始记）。

所以边输入边判断，这位数字是否是偶数，再加上其下标即可。

奉上完整代码：
```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
int main(){
	RI n,x,ans=0;
	scanf("%d",&n);
	for(RI i=1;i<=n;i=-~i){
		scanf("%1d",&x);//直接输入一位数
		if(!(x&1)) ans+=i;//加上下标
	}
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：zqwzqwzqw (赞：0)

- ### 算法

1. 我们知道，偶数$\%2\!=\!0$，那么，我们可知**尾数**为偶数$\left(0,2,4,6,8 \right)$的数都是偶数。

2. 当我们从左往右遍历到一个偶数字时，以它为尾数的数有几个呢？那就是从左往右遍历到它时的数字数。

3. 以样例为例，$1234$中以$2$为尾数的数的个数就是$2$，以$4$为尾数的数的个数就是$4$。

- ### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		char a;
		cin>>a;//输入
		if(a=='0' || a=='2' || a=='4' || a=='6' || a=='8')//遍历到偶数字
			ans+=i;//加上从左往右遍历到它时的数字数
	}
	printf("%d",ans);//输出
	return 0;
}
```


---

## 作者：WinterRain208 (赞：0)

CF1139A 【Even Substrings】

~~我来水题解了~~。

### 题意分析

给你一个字符串，求有几个化为数字后为偶数的子串。

### SOLUTION

偶数由$2,4,6,8,0$结尾，扫到一个位置$a_i$是偶数，那它作为最后一位时可以组成$i$个满足条件的子串。

```
123456

2:12,2.
4:1234,234,34,4.
6:123456,23456,3456,456,56,6.
```
这题就解决了。

### $CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

string a;
int ans=0;
int main(){
	cin>>a;
	cin>>a;
	F(i,0,a.size()-1)
		if((a[i]-'0')%2==0)ans+=(i+1);
	cout<<ans<<endl;
    return 0;
}

```

$wtrl$。



---

## 作者：Brian_WBY (赞：0)

第一篇 `py` 的题解。

首先我们知道，如果一个数为偶数，那么他的末位数字一定是偶数。对于这道题，如果字符串的第 $i$ 位对应的数字是偶数，那么所有前面的连续数字都可以与他组成偶数，总共有 $i$ 中情况。

那么代码就很好写了，直接扫描字符串并判断即可。

```python
n = int(input())
s = input() # 输入
ans = 0
for i in range(len(s)): # 扫描字符串
	if (int(s[i]) & 1) == 0: # 如果某位字符对应数字是奇数
		ans += i + 1 # python字符串下标从 0 开始，所以要 + 1
print(ans) # 输出答案即可
```


---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的数字串 $s$，试求出代表偶数的子串个数。

**数据范围：$1\leqslant n\leqslant 65000$，$s$ 仅包含数字 $1\sim9$。**
## Solution
众所周知，看一个数是否是偶数，只要看其最后一位是否能被 $2$ 整除即可。所以，我们遍历一遍数字串，一旦碰见了能被 $2$ 整除的数，那么假设其位置为 $i$，那么显然，答案要增加 $i$，因为这个数是偶数，那么前面连续的数组合起来的话也都是偶数。比如 $1234$，我们扫到了 $2$ 是偶数，那么 $12,2$ 都是偶数，扫到了 $4$ 是偶数，那么 $1234,234,34,4$ 都是偶数。

那么这样一来，代码就很简单了。
## Code
```cpp
int n, x, ans;

int main() {
	getint(n);
	_for(i, 1, n) {scanf("%1d", &x); if(!(x % 2)) ans += i;}
	writeint(ans);
	return 0;
}
```

---

## 作者：YosemiteHe (赞：0)

如何判断一个连续的子串是否为偶数？当这个连续的子串的个位数是偶数即可。

如何判断 $x$ 是否为偶数？ 和 $2$ 取模就能得到答案。进行 `x % 2` 的运算后的结果即是 $x$ 的奇偶性（结果是 $1$ 代表 $x$ 是奇数，结果是 $0$ 代表 $x$ 是偶数数）。

当第 $i$ 位是偶数时答案就加上 $i$，最后输出答案即可（以这个数结尾的子串个数有 $i$ 个）。

最后注意数据范围，要开 `long long`。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 6;
long long ans, n;
char s[N];
int main() {
    scanf("%lld%s", &n, s + 1);
    for (int i = 1; i <= n; i++)
        if (!((s[i] - '0') & 1)) ans += i;
    printf("%d\n", ans);
}
```

Tks.

---

## 作者：xht (赞：0)

题目地址：[CF1139A Even Substrings](https://www.luogu.org/problemnew/show/CF1139A)

一个数是偶数等价于其最后一位为偶数（2/4/6/8/0）

从左往右扫一遍，如果一个数是奇数则直接跳过，偶数则加上它对答案的贡献

这里的贡献应该为以它结尾的数的个数，自然就是它的下标了（下标从1开始）

注意开long long

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 6;
int n;
char s[N];
ll ans;

int main() {
    cin >> n;
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
        if (!((s[i] - '0') & 1)) ans += i;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：0)

- 题目：输入$n$和一个长度为$n$的数字串$s$，求在$s$里可截取的子串中有多少是偶数
- 思路：偶数只看末尾，找到一个就和前面的所有字符取一次。末尾是$s_i$，就能做$i$个子串。
- code：
	```cpp
    #include<stdio.h>
	int n,ans;char s[66666];
	main()
	{
	    scanf("%d%s",&n,s+1);//输入
	    for(register int i=1;i<=n;++i)
	        if((s[i]-'0')%2==0)ans+=i;//处理
	    printf("%d",ans);//输出
	}/**/
	```

---

