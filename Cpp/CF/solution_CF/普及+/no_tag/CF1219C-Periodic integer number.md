# Periodic integer number

## 题目描述

Alice became interested in periods of integer numbers. We say positive $ X $ integer number is periodic with length $ L $ if there exists positive integer number $ P $ with $ L $ digits such that $ X $ can be written as $ PPPP…P $ . For example:

 $ X = 123123123 $ is periodic number with length $ L = 3 $ and $ L = 9 $

 $ X = 42424242 $ is periodic number with length $ L = 2,L = 4 $ and $ L = 8 $

 $ X = 12345 $ is periodic number with length $ L = 5 $

For given positive period length $ L $ and positive integer number $ A $ , Alice wants to find smallest integer number $ X $ strictly greater than $ A $ that is periodic with length L.

## 说明/提示

In first example 124124 is the smallest number greater than 123456 that can be written with period L = 3 (P = 124).

In the second example 100100 is the smallest number greater than 12345 with period L = 3 (P=100)

## 样例 #1

### 输入

```
3
123456
```

### 输出

```
124124
```

## 样例 #2

### 输入

```
3
12345
```

### 输出

```
100100
```

# 题解

## 作者：_6_awa (赞：2)

题目大意：输入 $n$ 和 $a$，输出第一个比 $a$ 大的，以 $n$ 为周期且每个周期都是完整的周期的数。

什么是以 $n$ 周期呢？举个例子：$aaaaaaaaa...a$，其中 $a$ 为一个长度为 $n$ 的数。

题目分析：这些题只需要分类讨论，更据不同的状况输出即可。

一、全 $9$ 型或字符串长度 $\bmod\;n$ 有余数型：这时候不管怎么样都只能进入能满足条件的长度了。这里因为首位至少为 $1$，又因为是周期串，所以对应的位置也要变为 $1$。

二、加一型。举个例子：

```
6
111114111115
```

我们发现如果全部变成 `111114` 的字符串的话最后得到的字符串会更小，所以我们需要对首个 `111114` 进行加一操作。那如果是 `199999` 的话呢？只需要根据高精度加法，对前面一个字符进行加一操作就行了，直到没有进位。

三、普通型。此时没有任何的坑，直接转化即可。

最后放一下标准代码：

```cpp
#include <iostream>
using namespace std;
int n,w;
string s,t;
int main()
{
    cin >> n >> s;
    for(int i = 0;i < s.size();i ++)if(s[i] != '9')w = 1;
    if((int)s.size() % n || w == 0)//第一种情况
    {
        for(int i = 1;i <= (int)s.size() / n + 1;i ++)
        {
            cout << "1";
            for(int j = 1;j < n;j ++)cout << "0";
        }
        return 0;
    }
    else
    {
        t = s.substr(0,n);
        int r = 0,r2 = 0;
        for(int i = n;i < s.size();i += n)
        {
            string x = s.substr(i,n);
            if(t < x)
            {
                r = 1;
                break ;
            }
            if(t > x)r2 = 1;
        }
        if(r == 1 || r2 == 0)//加一型
		{
			int p = n - 1;
			t[p] ++;
			while(t[p] == 58)t[p] = '0',t[--p] ++;
		 } 
        for(int i = 1;i <= (int)s.size() / n;i ++)cout << t;//普通型
        return 0;
    }
}

---

## 作者：AlicX (赞：0)

## Solution 

一共有三种情况：

1. $len$ 不为 $n$ 的倍数，则最终的答案一定会比 $a$ 大，所以考虑选择最小的数 $100$ 来循环。

2. $len$ 为 $n$ 的倍数且 $a$ 不全为 $9$，考虑首先将 $a$ 的前 $n$ 个数截下来复制 $\frac{len}{n}$ 遍与 $a$ 比较，若大于 $a$，就输出，否则就将最后一位加 $1$，再次循环，注意进位。

3. $len$ 为 $n$ 的倍数且 $a$ 全为 $9$，此时若继续进位就会得到 $n+1$ 的字符串的循环，不满足条件。则我们选择 $1$ 加上 $n-1$ 位 $0$ 循环 $\frac{len}{n}+1$ 次即可。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=1e5+10; 
int n; 
string a; 
void print(int len){ 
	for(int i=1;i<=len/n+1;i++){ 
		printf("1"); 
		for(int j=2;j<=n;j++) printf("0"); 
	} puts("");  
} 
signed main(){ 
	scanf("%d",&n); cin>>a; 
	string lst=a; 
	a=" "+a; int len=a.size()-1; 
	if(len%n) print(len); 
	else{ 
		string s="",str=""; 
		for(int i=1;i<=n;i++) str+=a[i]; 
		for(int i=1;i<=len/n;i++) s+=str; 
		if(s>lst) return cout<<s<<endl,0; 
		if(str[n-1]=='9'){ 
			bool flg=1; 
			for(int i=n-1;i>=0;i--){ 
				if(str[i]=='9') str[i]='0'; 
				else{ str[i]+=1,flg=0; break; } 
			} if(flg){ 
				print(len); 
				return 0; 
			} 
		} else str[n-1]+=1; s=""; 
		for(int i=1;i<=len/n;i++) s+=str; 
		cout<<s<<endl; 
	} return 0; 
} 
```



---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1219C)    
简单题，但是细节量巨大。    
## 题意
给出正整数 $n$ 和另一个数 $s$，现在要求你给出一个最小的 $m$，使得 $m>s$ 且 $m$ 以 $n$ 为周期循环。     
## 解法
设 $l$ 为 $s$ 的长度。    
首先我们需要判掉一种特殊情况：   
- 如果 $l$ 不是 $n$ 的倍数，那么我们直接使用一个长度为 $n$ 的形如 `100...00` 的串为循环节即可，要循环 $\lfloor\dfrac{l}{n}\rfloor+1$ 次。    

接下来，我们进行预处理：设 $a_i$ 为 $s$ **从高位到低位**数的第 $(i-1)n+1$ 到第 $in$ 位所组成的数字。    
那么，我们就有了一个贪心策略：先取 $a_1$ 进行判定。若 $a_1$ 成立，就使用 $a_1$ 作为循环节；否则用 $a_1+1$。     
但这里又有了一个特殊情况：$a_1+1$ 可能长度会长于 $n$。所以我们在此做特判，如果出现了这种情况，我们就用最前面的构造方法进行构造。   
其他的情况直接输出即可。    
时间复杂度 $O(l)$，能过。    
[CODE](https://www.luogu.com.cn/paste/p01d6apf)

---

## 作者：Wander_E (赞：0)

这题分两种情况：

记 $A$ 的位数为 $len$。

- 如果 $L\mid len$ 那么就将 $A_i + 1$ 当且仅当 $L \mid i$（换句话说就是每个循环节 $+1$）。

- 否则，直接从头开始每 $L$ 位输出 $1$，其余输出 $0$（例如  $len=6$，$L=3$ 时输出 $100100$）。

注意特判全为 $9$ 的情况。

附上 AC 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
int n; 
bool flag = 1;
string s, t, ans;

void add()
{
	int temp = t[t.size() - 1] - '0' + 1 - 10;
	if(temp < 0) t[t.size() - 1] = char(temp + 10 + '0');
	else
	{
		int i = t.size();
		while(t[--i] == '9')t[i] = '0';
		if(i < 0) t = "1" + t;
		else t[i]++;
	}
}

signed main()
{
	cin >> n;
	cin >> s;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] != '9') flag = 0; 
	}
	if(s.size() % n != 0 || flag || s.size() < n)
	{
		for(int i = 0; i < s.size() / n + 1; i++)
		{
			putchar('1');
			for(int j = 2; j <= n; j++)
				putchar('0');
		}
	}
	else
	{
		t = s.substr(0, n);
		for(int i = 1; i <= s.size() / n; i++) ans += t;
		if(ans <= s)
		{
			add(), ans = "";
			for(int i = 1; i <= s.size() / n; i++) ans += t;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Victory_Defeat (赞：0)

这题其实是一道字符串题啦

大概说一下思路：

首先，如果两者长度不为倍数关系，直接输出长度为循环节的最小值（如$n=3$,那么为$100$）

其次，如果是倍数关系，将原数的循环节$++$即可

上代码（详见注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double lf;
#define reg register
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define input(a){a=0;char c=gc();int f=1;while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+(c&15);c=gc();}a*=f;}
static char buf[1<<21],*p1=buf,*p2=buf;
char bu[1<<21],cha[20];int p,pp=-1;
#define flush(){fwrite(bu,1,pp+1,stdout),pp=-1;}
#define output(x){if(pp>1<<20)flush();if(x<0)bu[++pp]=45,x=-x;do{cha[++p]=x%10+48;}while(x/=10);do{bu[++pp]=cha[p];}while(--p);}
#define Endl bu[++pp]='\n'
#define Space bu[++pp]=' '
#define pc(c) bu[++pp]=c
const int N=100010;
//自行忽略本注释以上部分
int l;
string a;
int main()
{
	cin>>l>>a;
    //输入
	int n=a.size();
	if(n%l!=0)//不为倍数关系
	{
		n=1+(n-1)/l;//求出所需循环次数（自带上取整）
		string w(l,'0');//初始化为000……0
		w[0]='1';//第一位为1
		while(n--)cout<<w;//输出
		cout<<endl;
		return 0;
	}
	string w=a.substr(0,l);//求出原数循环节
	string ww;
	for(int i=1;i<=n;i+=l)ww+=w;//初始为原数循环节
	if(ww<=a)//如果不行
	{
		for(int i=l-1;i>=0;--i)
		{
			if(w[i]=='9')w[i]='0';
			else
			{
				++w[i];
				break;
			}
            //最后一个不是9的++
		}
        //循环节++
		if(w[0]=='0')
		{
			w[0]='1';
			n+=l;
		}
        //进位
		ww="";
		for(int i=1;i<=n;i+=l)ww+=w;//更新答案
	}
	cout<<ww<<endl;//输出
	return 0;
}
```

---

