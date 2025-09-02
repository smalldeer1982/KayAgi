# Divisible by Twenty-Five

## 题目描述

### 题意翻译
Chanek先生有一个数字字符串 $s (1\le\left\vert s \right\vert\le8)$，且该字符串只包含 $0$，$1$，$2$，$3$，$4$，$5$，$6$，$7$，$8$，$9$，$X$，$\_$ （下划线）。每个 $X$ 都表示相同的数字，每个 $\_$ 都表示任意一个数字。

他可以用任一数字替换掉所有的 $X$ ，也可以将 $\_$ 替换为任一数字。但是他要求该数字不能有任何前导 $0$（$0$ 本身除外）。他想知道有多少钟替换方法可以使 $s$ 能被 $25$ 整除。

## 样例 #1

### 输入

```
25```

### 输出

```
1```

## 样例 #2

### 输入

```
_00```

### 输出

```
9```

## 样例 #3

### 输入

```
_XX```

### 输出

```
9```

## 样例 #4

### 输入

```
0```

### 输出

```
1```

## 样例 #5

### 输入

```
0_25```

### 输出

```
0```

# 题解

## 作者：ran_qwq (赞：6)

这题暴力就能过啊，为什么评绿啊？

大概的思路就是枚举位数为 $\left|s\right|$ 的数字 $i$，统计能被 $25$ 整除并且 $s$ 可以变为 $i$ 的 $i$ 的个数。

1. 如何判断 $s$ 能否变为 $i$ 呢？

首先如果 $s$ 已经确定的那一位与 $i$ 有冲突，肯定不行。

其次如果 $s$ 中字符 `X` 的那些位 $i$ 有几种数字但也就是不能同时满足这些需求，也不行。例如 $s$ 为 $\texttt{12XX5}$，$i$ 是 $12225$ 就可以，但是 $i$ 为 $12325$ 就不行。

2. 要特判 $s$ 是个位数的情况，只有 $s$ 是 $\texttt{0}$ 或 $\texttt{\_}$ 或 $\texttt{X}$ 时才可以。

---

## 作者：fxwqctb (赞：4)

本蒟蒻的第一篇题解，请大家笑纳。  
感谢管理员大大指出了笔误。

[题目传送门](https://www.luogu.com.cn/problem/CF1575D)  
## 一、题目分析  
### 思路  
我们都知道，$0$ 是任何数的倍数，所以 $0$ 要特判。当输入 $0$、$\_$、$X$ 的情况，应该先输出 $1$，并且 `return 0` 。

因为判断是否为 $25$ 的倍数，只需要判断最后两位，当最后两位为 $25$、$50$、$75$、$00$ 时，这个数就为 $25$ 的倍数。  
**注意：本题规定所有数字都不能含有前导 $0$($0$ 本身除外)。所以当 $\text{字符串长度}\le2$ 时，你需要注意不能有 $00$ 这种情况。**  

### $\_$ 的可能性
因为要考虑前导 $0$ 的情况，所以我们可以把字符串分为两种。  

#### 当 $\text{字符串长度}\ge3$ 时
当 $\text{字符串长度}\ge3$ 时，每一个 $\_$ 都可以表示 $0-9$，但是一下情况需要注意。  
- 如果 $\_$ 在最高位，那么它的取值只能为 $1-9$。  
- 如果字符串是以 $\_5$ 结尾，则 $\_$ 只能为 $2$ 或 $7$。
- 如果字符串是以 $\_0$ 结尾，则 $\_$ 只能为 $0$ 或 $5$。
- 如果字符串是以 $5\_$ 或 $0\_$ 结尾，则 $\_$只能为 $0$。
- 如果字符串是以 $2\_$ 或 $7\_$ 结尾，则 $\_$只能为 $5$。
- 如果字符串是以 $\_\_$结尾，则末尾两位只能为 $00$、$25$、$50$、$75$。
- 其余情况都为无解。
#### 当 $\text{字符串长度}\le2$ 时
当 $\text{字符串长度}\le2$ 时，有一下几种情况。  
- 如果字符串是 $\_5$，则 $\_$ 只能为 $2$ 或 $7$。
- 如果字符串是 $\_0$，则 $\_$ 只能为 $5$。
- 如果字符串是 $5\_$，则 $\_$只能为 $0$。
- 如果字符串是 $2\_$ 或 $7\_$，则 $\_$只能为 $5$。
- 如果字符串是 $\_\_$ 结尾，则末尾两位只能为 $25$、$50$、$75$。
- 其余情况都为无解。

### X 的可能性
因为每一个 $X$ 都表示同一个数字，所以这时你就要考虑最高位的问题。  

#### 当 $\text{字符串长度}\ge3$ 时
当 $\text{字符串长度}\ge3$ 时，$X$ 可以表示 $0-9$，但是一下情况需要注意。  
- 如果 $X$ 在最高位，那么它的取值只能为 $1-9$。  
- 如果字符串是以 $X5$ 结尾，则 $X$ 只能为 $2$ 或 $7$。
- 如果字符串是以 $X0$ 结尾，则 $X$ 只能为 $0$ 或 $5$，如果 $X$ 为 $0$，还要考虑最高位。
- 如果字符串是以 $5X$ 或 $0X$ 结尾，则 $X$只能为 $0$，并且还要考虑最高位。
- 如果字符串是以 $2X$ 或 $7X$ 结尾，则 $X$只能为 $5$。
- 如果字符串是以 $XX$结尾，则 $X$只能为 $0$，并且也要考虑最高位。
- 其余情况都为无解。
#### 当 $\text{字符串长度}\le2$ 时
当 $\text{字符串长度}\le2$ 时。  
- 如果字符串是 $X5$，则 $X$ 只能为 $2$ 或 $7$。
- 如果字符串是 $X0$，则 $X$ 只能为 $5$。
- 如果字符串是 $5X$，则 $X$只能为 $0$。
- 如果字符串是 $2X$ 或 $7X$，则 $X$只能为 $5$。
- 如果字符串是 $XX$，则无解，因为不能出现 $00$。
- 如果字符串是 $X\_$ 或 $\_X$ 结尾，则只有 $25$、$50$、$75$ 的情况。
- 其余情况都为无解。

## 二、统计个数
很显然，本题需要统计 $X$ 和 $\_$ 的数量。  
而最高位和最后两位都需要另外统计。 

统计字符个数的代码：  
```cpp
char a[10000]={};
cin>>a;
int x=0,y=0;  //x表示字符X的数量，y表示字符_的数量
for(int i=1;i<strlen(a)-2;i++)  //strlen()函数是求字符串的长度
{
	if(a[i]=='X')x++;
	if(a[i]=='_')y++;
}
```
## 三、计算数量
而最高位是否为 $X$ 或 $\_$，需要特殊处理。
```cpp
int w=0,z=0;//w表示最高位是否为X，z表示最高位是否为_。
if(a[0]=='X')w=1;
if(a[0]=='_')z=1;
```
当最后两位能够成的数量求出来时，结果也就算出来了，可以推出以下代码。  
```cpp
1/*前面这个数字表示后两位构成的种数*/*(w==1?9:x==0?1:1)/*a?b:c 是三目运算符，若a为真则返回b，否则返回c，前面的三目运算符表示对第一个字符为X的情况特判*/*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y)));//后面的自行理解
```

## 四、AC代码
以下是我的完整代码：  
```cpp
#include<bits/stdc++.h> //你熟悉的万能头
using namespace std;
char a[10]={};
int main()
{
	cin>>a;
	if(strlen(a)<=2)  //当a的长度≤2时的情况
	{
		if(strlen(a)==1)
		{
			if(a[0]=='0'||a[0]=='X'||a[0]=='_')cout<<1;  ///特判
			else cout<<0;
			return 0;
		}
		else
		{
			if((a[0]=='2'||a[0]=='7')&&a[1]=='5')cout<<1;
			else if(a[0]=='5'&&a[1]=='0')cout<<1;
			else if(a[0]=='X'&&a[1]=='5')cout<<2;
			else if(a[0]=='_'&&a[1]=='5')cout<<2;
			else if(a[0]=='X'&&a[1]=='0')cout<<1;
			else if(a[0]=='_'&&a[1]=='0')cout<<1;
			else if(a[0]=='X'&&a[1]=='X')cout<<0;
			else if(a[0]=='X'&&a[1]=='_')cout<<3;
			else if(a[0]=='_'&&a[1]=='X')cout<<3;
			else if(a[0]=='_'&&a[1]=='_')cout<<3;
			else if(a[0]=='2'&&a[1]=='X')cout<<1;
			else if(a[0]=='5'&&a[1]=='X')cout<<1;
			else if(a[0]=='7'&&a[1]=='X')cout<<1;
			else if(a[0]=='2'&&a[1]=='_')cout<<1;
			else if(a[0]=='5'&&a[1]=='_')cout<<1;
			else if(a[0]=='7'&&a[1]=='_')cout<<1;
                          				//所有情况
			else cout<<0;
		}
		return 0;
	}
	int x=0,y=0,w=0,z=0;//X个数、_个数、第一位是否为X、第一位是否为_
	for(int i=1;i<strlen(a)-2;i++)
	{
		if(a[i]=='X')x++;
		if(a[i]=='_')y++;
        		//统计X和_的个数
	}
	if(a[0]=='0')//以0开头的情况
	{
		cout<<0;
		return 0;
	}
	if(a[0]=='X')w=1;
	if(a[0]=='_')z=1;
	if(a[strlen(a)-1]=='5')
	{
		if(a[strlen(a)-2]=='2'||a[strlen(a)-2]=='7')cout<<(w==1?9:x==0?1:10)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y)));
		else if(a[strlen(a)-2]=='X')cout<<(long long int)(2*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y))));
		else if(a[strlen(a)-2]=='_')cout<<(long long int)(2*(w==1?9:x==0?1:10)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y))));
		else cout<<0;
	}
	else if(a[strlen(a)-1]=='0')
	{
		if(a[strlen(a)-2]=='5'||a[strlen(a)-2]=='0')cout<<(w==1?9:x==0?1:10)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y)));
		else if(a[strlen(a)-2]=='X')cout<<(long long int)(((w==1)?1:2)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y))));
		else if(a[strlen(a)-2]=='_')cout<<(long long int)(2*(w==1?9:x==0?1:10)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y))));
		else cout<<0;
	}
	else if(a[strlen(a)-1]=='X')
	{
		if(a[strlen(a)-2]=='X')cout<<((w==1)?0:1)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y)));
		else if(a[strlen(a)-2]=='_')cout<<(long long int)(((w==1)?2:4)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y))));
		else if(a[strlen(a)-2]=='2'||a[strlen(a)-2]=='7')cout<<(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y)));
		else if(a[strlen(a)-2]=='5'||a[strlen(a)-2]=='0')cout<<((w==1)?0:1)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y)));
		else cout<<0;
	}
	else if(a[strlen(a)-1]=='_')
	{
		if(a[strlen(a)-2]=='X')cout<<(long long int)(((w==1)?3:4)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y))));
		else if(a[strlen(a)-2]=='_')cout<<(long long int)(4*(w==1?9:x==0?1:10)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y))));
		else if(a[strlen(a)-2]=='2'||a[strlen(a)-2]=='5'||a[strlen(a)-2]=='7'||a[strlen(a)-2]=='0')cout<<(long long int)((w==1?9:x==0?1:10)*(z==1?9*((y==0)?1:(pow(10,y))):(y==0?1:pow(10,y))));
		else cout<<0;
	}
	else cout<<0;
    						//以上是所有情况
	return 0;
}
```

### _END_ 

---

## 作者：yanhao40340 (赞：3)

不一定有~~[更好的阅读体验](https://www.luogu.com.cn/blog/yanhao40340/solution-cf1575d)~~。

### 题意翻译
Chanek先生有一个数字字符串 $s (1\le\left\vert s \right\vert\le8)$，且该字符串只包含 $0$，$1$，$2$，$3$，$4$，$5$，$6$，$7$，$8$，$9$，$X$，$\_$ （下划线）。每个 $X$ 都表示相同的数字，每个 $\_$ 都表示任意一个数字。

他可以用任一数字替换掉所有的 $X$ ，也可以将 $\_$ 替换为任一数字。但是他要求该数字不能有任何前导 $0$（$0$ 本身除外）。他想知道有多少钟替换方法可以使 $s$ 能被 $25$ 整除。

### 解法

数据范围极小，显然可以暴力，复杂度 $O(\dfrac{s\log s}{25})$，可以通过。
代码就不贴了。

考虑优化：能被 $25$ 整除的数的末两位只能是 $25$，$50$，$75$，$00$。所以如果有 $X$ 的话，我们可以依次用 $0\sim9$ 这 $10$ 个数去替换 $X$，再去统计当 $X$ 取某一数字时的答案。然后将答案求和。如果没有 $X$，统计一遍即可。

统计方法（乘法原理）：

- 如果末两位均为 $\_$ 且 $\left\vert s \right\vert>2$，那么有 $4$ 种选法。

- 如果末两位均为 $\_$ 且 $\left\vert s \right\vert=2$，那么有 $3$ 种选法。

- 如果 $\_$ 在第一位且 $\left\vert s \right\vert>2$，$\_$ 就可以取到一切非零值，有 $9$ 种选法。

- 如果 $\_$ 在第一位且 $\left\vert s \right\vert=2$：

    - 如果 $s=\texttt{\_5}$，那么 $\_$ 就有 $2$ 种选法。
    
    - 如果 $s=\texttt{\_0}$，那么 $\_$ 就只有 $1$ 种选法。
    
    - 否则这种情况无解。
    
- 如果 $\_$ 在最后一位且前一位是 $2$ 或 $5$ 或 $7$ 或 $0$，那么就有唯一的一种取法。

- 否则 $\_$ 就可以取到任何数字，有 $10$ 种取法。

注意当 $\left\vert s \right\vert=1$ 时要特判。

代码实现时可以将最后两位单独考虑，这样码量较少，且更加便捷。

具体细节详见代码。

### ~~你们最想要的~~ 代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;
char s[100];bool flag[100];int ans;
void change(char number){
	for (int i=0;i<=9;++i)
		if (flag[i])
			s[i]=number;
	return;
}
void counts(int len){
	int cnt=1;
	if (((s[len-1]-48)*10+s[len]-48)%25 && s[len-1]!='_' && s[len]!='_') return;//特判，如果最后两位不被25整除则直接返回
	for (int i=1;i<=len-2;++i){
		if (i==1 && s[i]=='_') cnt*=9;
		else if (s[i]=='_') cnt*=10;
	}
   //接下来单独讨论后两位
	if (s[len-1]=='_' && s[len]=='_' && len>2) cnt*=4;
	else if (s[len-1]=='_' && s[len]=='_' && len==2) cnt*=3;
	else if (s[len-1]=='_' && (s[len]=='5' || (s[len]=='0' && len>2))) cnt*=2;
	else if (s[len-1]=='_' && s[len]=='0' && len==2);
	else if (s[len]=='_' && (s[len-1]=='2' || s[len-1]=='7' || s[len-1]=='5' || s[len-1]=='0'));
	else if (s[len-1]=='_' || s[len]=='_') return;
	ans+=cnt;return;
}
int main(){
	scanf("%s",s+1);
	int len=strlen(s+1);bool flg=false;
	for (int i=1;i<=len;++i)
		if (s[i]=='X')
			flg=true,flag[i]=true;//判断有无X
	if (len>1 && s[1]=='0'){puts("0");return 0;}
	else if (len==1 && (s[1]=='0' || s[1]=='X' || s[1]=='_')){puts("1");return 0;}
	else if (len==1){puts("0");return 0;}//特判
	if (flg)
		for (char i=(s[1]=='X'?'1':'0');i<='9';++i){
			change(i);//尝试每一个数字
			counts(len);//统计个数
		}
	else counts(len);
	printf("%d\n",ans);
	return 0;
}
```
### 完结撒花！！！


---

## 作者：rui_er (赞：2)

值域非常小，其中只有 $4\times 10^6$ 个数是 $25$ 的倍数，因此可以暴力枚举所有位数正确的 $25$ 的倍数，然后检查是否合法。

检查方法就是枚举每一位，如果是数字就必须一模一样，否则记录字符 `X` 表示的数是多少，看看是否自始至终都是一样的。

需要特判 $|s|=1$ 的情况。

```cpp
// Problem: CF1575D Divisible by Twenty-Five
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1575D
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

int n;
char s[10];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
bool check(int val) {
	int x = -1;
	per(i, n, 1) {
		int u = val % 10;
		val /= 10;
		if(isdigit(s[i]) && s[i] - '0' != u) return 0;
		if(s[i] == 'X') {
			if(x == -1) x = u;
			else if(x != u) return 0;
		}
	}
	return 1;
}

int main() {
	scanf("%s", s+1);
	n = strlen(s+1);
	if(n == 1) return puts(s[1]=='_'||s[1]=='X'||s[1]=='0'?"1":"0")&0;
	int k = 1, ans = 0;
	rep(i, 2, n) k *= 10;
	for(int i=k+(25-k%25)%25;i<k*10;i+=25) ans += check(i);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：_weishiqi66_ (赞：1)

[CF1575D Divisible by Twenty-Five](https://www.luogu.com.cn/problem/CF1575D)

![](https://cdn.luogu.com.cn/upload/image_hosting/68vv30om.png)

一道思路很裸的暴力题。首先分析题目给定一个数字字符串 $s (1\le\left\vert s \right\vert\le8)$，其中有一些特殊字符 # 和  _。要求根据规则填上一些数，使得数字字符串整除 $25$ 的方案数。

因此，我们可以想到先枚举数字字符串的可能，再判断是否整除 $25$。

代码方面 函数 work 中 $t$ 表示遍历到第几个数字，$s$ 表示当前情况下数字字符串的大小，$xf$ 表示 $X$ 的大小（当 $x=-1$ 时，则表示当前没有 $X$ 被填过）。

代码如下
```
#include<bits/stdc++.h>
using namespace std;
char a[9];
int n=0,ans=0;
void work(int t,int s,int xf){
	if(t>n){
		if(s%25==0) ans++;
		return ;
	}
	if(a[t]<='9'&&a[t]>='0') work(t+1,s*10+(a[t]-'0'),xf);
	else{
		if(a[t]=='X'){
			if(xf!=-1) work(t+1,s*10+xf,xf);
			else{
				for(int i=0;i<=9;i++){
					if(t==1&&i==0) continue;
					
					work(t+1,s*10+i,i);
				} 
			}
		}
		if(a[t]=='_'){
			for(int i=0;i<=9;i++){
				if(t==1&&i==0) continue;
				work(t+1,s*10+i,xf);
			} 
		}
	}
	
}
int main(){
	cin>>a+1;
	n=strlen(a+1);
	if(n==1&&(a[1]=='X'||a[1]=='_')){//提前处理长度为1的数字字符串。
		cout<<1;
		return 0;
	}
	if(n>1&&a[1]=='0'){//单独处理前导零情况
		cout<<0;
		return 0;
	}
	work(1,0,-1);
	cout<<ans;
	return 0;
}
```


---

## 作者：denominator (赞：0)

# 「CF1575D Divisible by Twenty-Five」题解

超多 `if` 警告！

---

## Part \#(-1) 暴力

如果你只想知道暴力，请右转其他几篇题解。

## Part \#0 前置知识

快速幂，如果你不会的话，暴力求幂可过，或参阅[此题](https://www.luogu.com.cn/problem/P1226)。

本人采用快速幂做法。

## Part \#1 被 25 整除的性质

有一个数 $n$，若它被 $25$ 整除（在下面的叙述中我们记作 $25\mid n$），令 $n=100p+q$，显然 $25\mid100p$，于是可知 $25\mid q$。

不妨设 $q<100$，由上述条件可得 $25\mid q$，故有 $q$ 为 $0,25,50,75$ 中的一个。

发现此时的 $q$ 即为 $n$ 在十进制下的末两位（若 $n$ 至少两位，只有一位的 $n$ 显然只有 $0$ 满足），故有若 $25\mid n$，则有 $n$ 在十进制下的末两位为 $00,25,50,75$ 中的一个。

读者不难发现其逆命题亦成立，即它们是等价的。

## Part \#2 分类讨论

由上面的讨论，我们先把一位数的情况特判掉。

「$n$ 在十进制下的末两位为 $00,25,50,75$ 中的一个」这个性质可以转化为 「$n$ 在十进制下的个位为 $0,5$ 中的一个，在十进制下的十位为 $0,2,5,7$ 中的一个，且 $0,5$ 作十位时个位只能为 $0$，$2,7$ 作十位时个位只能为 $5$」。

分类讨论时，可以将末两位分成 $9$ 类：`__`、`XX`、`X_`、`_X`、`X*`、`*X`、`_*`、`*_`、`**`（其中 `*` 可以指代任何已知的数）。

每一类中都可能有一些 `_` 是「自由」的，即其取值不是被 $25$ 整除这个条件的约束。设它们的个数是 $m$，则它们对答案的贡献（即它们可以取的值对的总个数）为（这里将 $m=0$ 的情况记为 $1$）：

$$
\begin{cases}
1, & m=0 & \cdots(1)\\
10^m, & s_1\neq\texttt{\_} & \cdots(2)\\
9\times10^{m-1}, & s_1=\texttt{\_} & \cdots(3)
\end{cases}
$$

$(2),(3)$ 合并为 $\left(10-\left[s_1=\texttt{\_}\right]\right)\times10^{m-1}$，这里 $[\text{cond}]$ 指若条件 $\text{cond}$ 成立则该结果为 $1$，不成立则为 $0$。如果 $(1)$ 也能合并就很舒服了。在我的代码里把 $m=1$ 的情况下：

- $\left[s_1=\texttt{\_}\right]$ 设为 $9$；
- 负指数幂设为 $1$，

就也可以这么计算了。其他情况的计算详见代码。

之后还有许多细节，代码里也一一注释。

复杂度 $\mathcal O(|s|)$，比题解第一的那位 dalao 稍微好个常数。

## Part \#3 代码

~~怒打 2KB~~

~~我才不告诉你我是一个一个点踩过去的呢~~

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int cntx, cnt_, leadx, lead_;
// cntx/cnt_ 为 X/_ 的个数
// leadx/lead_ 表示第一个字符是否为 X/_，
// 值为 0/1/9，_ 的情况即上文所处理的，X 同理
int fastpow (int a, int b) { // 快速幂（不带取模）
	if (b < 0) {
		return 1;
	}
	int s = 1;
	while (b) {
		if (b & 1) {
			s *= a;
		}
		a *= a;
		b >>= 1;
	}
	return s;
}
int main () {
	cin >> s;
	if (s.size () == 1) { // 特判长度为 1，只有 0 可行
		if (s == "0" || s == "X" || s == "_") {
			cout << 1;
		} else {
			cout << 0;
		}
		exit (0);
	}
	if (s[0] == '0') { // 特判是否已有前导 0
		cout << 0;
		exit (0);
	}
	if (s[s.size () - 1] != '0' && s[s.size () - 1] != '5' && s[s.size () - 1] != 'X'
		&& s[s.size () - 1] != '_' || s[s.size () - 2] != '0' && s[s.size () - 2] != '2'
		&& s[s.size () - 2] != '5' && s[s.size () - 2] != '7' && s[s.size () - 2] != 'X'
		&& s[s.size () - 2] != '_') { // 即特判上文说的那个转化
		cout << 0;
		exit (0);
	}
	// 下面几行在说明变量意义时已提及，不再赘述
	for (int i = 0; i < s.size (); i++) {
		if (s[i] == 'X') {
			cntx++;
			if (i == 0) {
				leadx = 1;
			}
		}
		if (s[i] == '_') {
			cnt_++;
			if (i == 0) {
				lead_ = 1;
			}
		}
	}
	if (cntx == 0) { // 没有 X，该处理方法与 _ 相同
		leadx = 9;
	}
	if (cnt_ == 0) { // 没有 _，自然没有「自由」的 _
		lead_ = 9;
	}
	// 1. __
	if (s.substr (s.size () - 2, 2) == "__") {
		if (cnt_ == 2 && lead_ == 1) { // 特判 s 就是 __ 的情况
			cout << 3;
		} else {
			if (cnt_ == 2) { // 如果除这两个 _ 外没有其他 _，即没有「自由」的 _
				lead_ = 9;
			}
			// 4            -> 这两个 _ 有 4 种填法
			// (10 - leadx) -> X 有 (10 - [s_1 = X]) 种填法
			cout << 4 * (10 - leadx) * (10 - lead_) * fastpow (10, cnt_ - 3);
		}
		exit (0);
	}
	// 2. XX
	if (s.substr (s.size () - 2, 2) == "XX") {
		// (1 - leadx) -> 这两个 X 有 (1 - [s_1 = X]) 种填法（即 00，若 X 为首字符则不行）
		cout << (1 - leadx) * (10 - lead_) * fastpow (10, cnt_ - 1);
		exit (0);
	}
	// 3. X_
	if (s.substr (s.size () - 2, 2) == "X_") {
		if (cnt_ == 1) { // 同理
			lead_ = 9;
		}
		// 注意这里 X 的值唯一确定了 _ 的值，所以不用乘 2
		cout << (4 - leadx) * (10 - lead_) * fastpow (10, cnt_ - 2);
		exit (0);
	}
	// 4. _X
	if (s.substr (s.size () - 2, 2) == "_X") {
		if (cnt_ == 1 && lead_ == 1) { // 也是特判 s = _X
			cout << 3;
		} else {
			if (cnt_ == 1) { // 同理（不用写了吧 qwq）
				lead_ = 9;
			}
			// 注意这里必须分成两类：X = 0 与 X = 5
			// 前者即 X = 0，后者即 X = 5
			cout << 2 * (1 - leadx) * (10 - lead_) * fastpow (10, cnt_ - 2) + 2 * (10 - lead_)
					* fastpow (10, cnt_ - 2);
		}
		exit (0);
	}
	// 5. X*
	if (s[s.size () - 2] == 'X') {
		if (s[s.size () - 1] == '0') { // 特判最后一位为 0，此时 X = 0 或 5，注意前导 0
			cout << (2 - leadx) * (10 - lead_) * fastpow (10, cnt_ - 1);
		} else { // X = 2 或 7，无需考虑前导 0
			cout << 2 * (10 - lead_) * fastpow (10, cnt_ - 1);
		}
		exit (0);
	}
	// 6. *X
	if (s[s.size () - 1] == 'X') {
		if ((s[s.size () - 2] == '0' || s[s.size () - 2] == '5') && leadx == 1) {
			// X 一定为 0，但是第一个字符是 X
			cout << 0;
		} else { // X 可以唯一确定，只考虑 _
			cout << (10 - lead_) * fastpow (10, cnt_ - 1);
		}
		exit (0);
	}
	// 7. _*
	if (s[s.size () - 2] == '_') {
		if (cnt_ == 1) {
			if (lead_ == 1 && s[s.size () - 1] == '0') { // 特判 _0 的情况
				cout << 1;
				exit (0);
			}
			lead_ = 9;
		}
		// 此时，该 _ 只有两个数满足要求
		cout << 2 * (10 - leadx) * (10 - lead_) * fastpow (10, cnt_ - 2);
		exit (0);
	}
	// 8. *_，这个自己看吧，应该还好理解
	if (s[s.size () - 1] == '_') {
		if (cnt_ == 1) {
			lead_ = 9;
		}
		cout << (10 - leadx) * (10 - lead_) * fastpow (10, cnt_ - 2);
		exit (0);
	}
	// 9. **，这个就直接判断后两位是否是上文说的 4 种情况即可
	if (s.substr (s.size () - 2, 2) == "00" || s.substr (s.size () - 2, 2) == "25" ||
		s.substr (s.size () - 2, 2) == "50" || s.substr (s.size () - 2, 2) == "75") {
		cout << (10 - leadx) * (10 - lead_) * fastpow (10, cnt_ - 1);
		exit (0);
	}
	cout << 0;
	return 0;
}
```

本人文笔欠佳，有看不懂的可以在评论区留言。代码有问题也欢迎 hack。

---

## 作者：Presentation_Emitter (赞：0)

数据范围极小，直接暴力即可。

特别地，对于长度为 1 的情况需要特判 $s=0$。

时间复杂度 $\Theta(\dfrac{s \log s}{25})$。

Code:

```cpp
char s[11];ll n,ans;
il bool chk(ll t)
{
	ll x=-1;
	for(int i=n;i>=1;--i)
	{
		int d=t%10;t/=10;
		if(s[i]=='X')
		{
			if(x>=0&&x!=d)ret 0;
			x=d;
		}
		else if(s[i]!='_'&&s[i]!=(d|48))ret 0;
	}
	ret 1;
}
int main()
{
	scanf("%s",s+1);n=strlen(s+1);
	if(n<=1)ret prt((s[1]<='0'||s[1]>'9'?1:0)),0;
	int t=1;for(int i=1;i<=n;++i)t*=10;
	for(int i=n<=2?25:t/10;i<t;i+=25)ans+=chk(i);
	prt(ans);
	ret 0;
}
```

---

