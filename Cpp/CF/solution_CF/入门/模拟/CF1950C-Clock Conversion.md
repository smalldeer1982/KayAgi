# Clock Conversion

## 题目描述

给定一个 24 小时制的时间，请输出其对应的 12 小时制时间。

- [24 小时制](https://en.wikipedia.org/wiki/24-hour_clock#Description) 将一天分为 24 个小时，从 $00$ 到 $23$，每个小时有 60 分钟，从 $00$ 到 $59$。
- [12 小时制](https://en.wikipedia.org/wiki/12-hour_clock#Description) 将一天分为上午（AM）和下午（PM）两个部分。每个部分的小时顺序为 $12, 01, 02, 03, \dots, 11$。每个小时有 60 分钟，分钟编号从 $00$ 到 $59$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
11
09:41
18:06
12:14
00:59
00:00
14:34
01:01
19:07
11:59
12:00
21:37```

### 输出

```
09:41 AM
06:06 PM
12:14 PM
12:59 AM
12:00 AM
02:34 PM
01:01 AM
07:07 PM
11:59 AM
12:00 PM
09:37 PM```

# 题解

## 作者：封禁用户 (赞：4)

## Description

给定一个 $24$ 时计时法的时间，将其转为 $12$ 时计时法。

## Solution

可以把问题划分成两个部分，第一部分求时间，第二部分求是 `AM` 还是 `PM`。

**第一部分**

设 $24$ 时计时法的小时数为 $h$，分钟数为 $m$，$12$ 时计时法的小时数为 $h'$，分钟数为 $m'$。

首先，我们可以看出，$m$ 一定是不会变的，即 $m'=m$。而对于 $h$，通过观察样例可以得出结论：

- 如果 $h=0$，则 $h'=12$。
- 如果 $1\le h\le12$，则 $h'=h$。
- 如果 $h>12$，则 $h'=h-12$。

**第二部分**

这一部分比较简单，若 $h<12$，则为 `AM`，否则为 `PM`。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define il inline
using namespace std;
int h,m;
il void solve()
{
	scanf("%d:%d",&h,&m);
	if(h==0)
		printf("%02d:%02d",12,m);
	else if(h<=12)
		printf("%02d:%02d",h,m);
	else
		printf("%02d:%02d",h-12,m);
	if(h<12)
		printf(" AM\n");
	else
		printf(" PM\n");	
	return;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：_Star_Universe_ (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1950C)

### 题意
将 $24$ 小时制时间转化为 $12$ 小时制时间。

### 思路
这里我用的变量 $a$ 是小时，$b$ 是分钟，针对 $a$ 总共分以下几类：

第一类：$1 \le a \le 11$ 时，直接输出，再加上 `AM`。

第二类：$a$ 是 $12$ 时，直接输出，加上 `PM`。

第三类：$a$ 是 $0$ 时，加上 $12$ 输出，加上 `AM`。

第四类：$13 \le a \le 23$ 时，将 $a$ 减 $12$ 输出，再加上 `PM`。

针对 $b$ 是不用讨论的，自己想一想为什么。

### Code
```c
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t,n,a;
	string b;
	char c;
	cin>>t;
	while(t--){
		cin>>a>>c>>b;
		if(a>=1&&a<=11){
			if(a>=0&&a<=9){
				cout<<0<<a<<":"<<b<<" AM"<<endl;
			}
			else{
				cout<<a<<":"<<b<<" AM"<<endl;
			}
		}
		if(a==12){
			cout<<a<<":"<<b<<" PM"<<endl;
		}
		if(a==0){
			a+=12;
			cout<<a<<":"<<b<<" AM"<<endl;
		}
		if(a>=13&&a<=23){
			a-=12;
			if(a>=0&&a<=9){
				cout<<0<<a<<":"<<b<<" PM"<<endl;
			}
			else{
				cout<<a<<":"<<b<<" PM"<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：1)

# CF1950C Clock Conversion 题解

说句闲话：建议评红。

考察知识点：分值（选择）结构。

### 翻译

将一个 $24$ 小时制的时间转为 $12$ 小时制并输出。

### 解析

观察样例，我们可以得到如下结论。

为了方便表述，记小时数为 $a$，分钟数为 $b$。

+ 在 $12$ 小时制中没有 $0$ 点多少的说法，应该是 $12$ 点（这让我非常不适应）。

+ 如果 $a=0$ 或 $a=12$，在 $12$ 小时制中都是 $12$ 点多；否则就是 $a\bmod 12$ 点。

+ $b$ 输入时是几，输出时还是几。

+ $00:00\sim 11:59$ 时，即 $a<12$ 时是上午（AM）；否则是下午（PM）。

### 代码

所以我们不难写出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
string s;
int hour;
void output(bool x){ //x=1 是上午，x=0 是下午
	printf("%02d",hour);
	for(int i=2;i<s.size();i++){
		cout<<s[i];
	} 
	cout<<" ";
	if(x){
		cout<<"AM\n";
	}
	else{
		cout<<"PM\n";
	}
}
int main(){
//	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>s;
		int ten=s[0]-'0',one=s[1]-'0';
		int h=ten*10+one;
		if(h==0||h==12){
			hour=12;
		}
		else{
			hour=h%12;
		}
		if(h<12){
			output(1);
		}
		else{
			output(0);
		}
	}
return 0;
}
```

---

## 作者：MhxMa (赞：1)

[更好的阅读体验](https://blog.mhxma.tech/2024/04/03/tijie-CF1950C/)

本题是一个简单的时间转换程序，将给定的二十四小时制时间转换为十二小时制时间。

模拟即可，读取字符串后，提出小时和分钟部分，下标为 $0$ 和 $1$ 的数字组成小时部分，$3$ 和 $4$ 组成分钟部分。

按照题意，根据小时部分和分钟部分，如果小时部分小于 $12$，则时间为 `AM`，如果小时部分等于 $0$，则小时部分改为 $12$，小时部分大于 $12$，时间为 `PM`，小时部分减 $12$ 输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int main() {
	cin >> T;
	while (T--) {
		string s, ans1 = "", ans2 = "", ans3 = "", ans;
		cin >> s;
		ans = s.substr(2, 3);
		int n;
		n = (s[0] - '0') * 10 + (s[1] - '0');
		ans1 += s[0], ans1 += s[1], ans1 += ans, ans1 += " AM";
		ans2 += "12", ans2 += ans;
		if (n % 12 > 9) {
			if (n % 12 == 10)ans3 += "10";
			else ans3 += "11";
		} else {
			ans3 += "0";
			ans3 += (n % 12 + '0');
		}
		ans3 += ans;
		ans3 += " PM";
		cout << ((n < 12) ? ((n == 0) ? ans2 + " AM" : ans1): ((n == 12) ? ans2 + " PM" : ans3))<< endl;
	}
}
```

---

## 作者：minVan (赞：1)

**题目大意**

给定一个二十四小时制的时间，将其转换为十二小时制。

**解题思路**

令原来为 $\texttt{a:b}$，如果 $a=0$，则改为 $a=12$，下面关于 $a$ 分类讨论：

1. 若 $a=12$，则如果 $b>0$，为下午 $\texttt{PM}$，否则为上午 $\texttt{AM}$。
1. 若 $a<12$，直接输出。
1. 若 $a>12$，则 $a-12$ 后输出。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int a;
		char c;
		string b;
		cin >> a >> c >> b;
		if(a == 0) {
			cout << "12:" << b << " AM\n";
		} else if(a > 12) {
			a -= 12;
			if(a < 10) {
				cout << "0" << a;
			} else {
				cout << a;
			}
			cout << ":" << b << " PM\n";
		} else if(a == 12) {
			cout << a << ":" << b << " PM\n";
		} else {
			if(a < 10) {
				cout << "0" << a;
			} else {
				cout << a;
			}
			cout << ":" << b << " AM\n";
		}
	}
	return 0;
}
```

---

## 作者：jsisonx (赞：0)

# 简化题意
给出一个 $24$ 小时制时间，将其转换成 $12$ 小时制时间。
# 分析
不难看出，时间转换只与小时有关，所以不需要考虑具体的分钟。

对于小时，我们发现转换的过程很像取模运算：
把给出的时间表示为 $x:y$ 的形式，则

 1. 若 $x=0$，则 $x$ 变为 $12$。
 2. 若 $0<x \le 12$，则 $x$ 不变
 3. 若 $x>12$，则 $x$ 变为 $x \bmod 12$。
 
 对于操作 $2$，$3$，可以使用取模运算：
 设变化后的小时为 $x_1$，则 $x_1=x \bmod 12$。
 
 注意：操作 $1$ 应在操作 $2$，$3$ 之后进行，以防 $x \bmod 12=0$ 时发生的错误。
 
 上下午的判断比较简单：若 $x<12$，则该时间为上午，否则为下午。
 
 # 代码
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	while(n--){
		int a,b;
		string s="AM";
		char c;
		cin>>a>>c>>b;
		if(a>=12){
			s="PM";
		}
		a%=12;
		if(a==0){
			a=12;
		}	
		if(a<10){
			cout<<0;
		}
		cout<<a<<':';
		if(b<10){
			cout<<0;
		}
		cout<<b<<' '<<s<<endl;
	}
	return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

首先，判断这个时间是上午还是下午。

- 上午：小时、分钟都不变。
- 下午：小时减去 $12$、分钟不变。

然后就是补全 `0`。如果当前输出的数字小于十，那么在前面补上 $0$ 之后再输出。

最后就是关于十二点与零点的特判。注意转换至十二小时制之后应该用 `AM` 还是 `PM`。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("\n%d:%d",&a,&b);
        if(a == 12){
            if(b >= 10){
                printf("12:%d PM",b);
            }else{
                printf("12:0%d PM",b);
            }
        }else if(a == 0){
            if(b >= 10){
                printf("12:%d AM",b);
            }else{
                printf("12:0%d AM",b);
            }
        }else if(a > 12){
            if(a-12 >= 10){
                printf("%d:",a-12);
            }else{
                printf("0%d:",a-12);
            }
            if(b >= 10){
                printf("%d",b);
            }else{
                printf("0%d",b);
            }
            printf(" PM");
        }else{
            if(a >= 10){
                printf("%d:",a);
            }else{
                printf("0%d:",a);
            }
            if(b >= 10){
                printf("%d",b);
            }else{
                printf("0%d",b);
            }
            printf(" AM");
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Harrylzh (赞：0)

不难发现二十四小时制下的小时数和十二小时制下的模 $12$ 的结果相同，且十二小时制下的小时数一定在一到十二之间。根据这一点可以得到小时数；分钟数不变，再根据小时数判断上午或下午。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		long long h,m;
		char ch;
		cin>>h>>ch>>m;
		printf("%02lld:%02lld",(h-1+12)%12+1,m);
		if(h>=12) printf(" PM\n");
		else printf(" AM\n");
	}
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

Despriction
-----------

给定一个二十四小时制的时间，请将它转换为题目要求的十二小时制。

Solution
------------

入门模拟。

设读入的小时为 $h$，分钟为 $m$。

- 当 $h>12$，说明是下午，$h\gets h-12$，并且标记哨兵。

- 当 $h=12$，说明也是下午，只不过这时**只用**标记哨兵，$h$ 并不用减少。

- 当 $h=0$，则将 $h$ 修改为 $12$。

最后输出即可，注意判断是否需要添加前导零。

Code
------------
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define sc scanf
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int T,h,m;

inline void solve(){
  sc("%lld:%lld",&h,&m);
  bool f = false;//注意多测。
 /* 情况讨论。*/
  if(h>12) h -= 12 , f = 1;
  if(h == 12) f = 1;
  if(!h) h=12;
  
 /* 分“需要添加前导零”和“不需要添加前导零”讨论。*/
  
  (h < 10) ? pr("0%lld:" , h) : pr("%lld:" , h);
  (m < 10) ? pr("0%lld " , m) : pr("%lld " , m);
  f ? pr("PM\n") : pr("AM\n");
}
signed main(){
  T=read();
  while(T--) solve();
}
```

---

## 作者：xd244 (赞：0)

同样是一道模拟水题。

用 $h$ 表示小时，用 $m$ 表示分钟，则可以分类讨论：

1.$1\leq h\leq11$ 时，输出 ```hh:mm AM```。

2.$13\leq h\leq 23$ 时，输出 ```hh-12:mm PM```。

3.$h=12$ 时，输出 ```12:mm AM```。

4.$h=0$ 时，输出 ```12:mm PM```。

代码：
```cpp
#include<iostream>
using namespace std;
inline long read(){
    long x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;ch=getchar();
    }while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}int main(){
    int t;cin>>t;
    while(t--){
        long h=read(),m=read();bool f=0;
        if(h<12)f=1;
        if(h==0)h=12;
        else if(h>12)h-=12;
        if(h<10)cout<<0;
        cout<<h<<":";
        if(m<10)cout<<0;
        cout<<m<<" ";
        if(f)cout<<"AM\n";
        else cout<<"PM\n";
    }
}
```

---

## 作者：nyC20 (赞：0)

# 思路
很简单的题，只不过要考虑的情况很多，难度入门。设小时数为 $h$，分钟数为 $m$，根据题意，每一个输入都可以分为下列几个情况：

- $h=0$，AM。
- $h=12$，PM。
- $1 \le h \le 11$，AM。
- $13 \le h \le 24$，PM。

然后 $h > 12$ 的情况都要将 $h$ 减去 $12$，输出答案即可，注意小于 $10$ 的要用 $0$ 占位。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int h, m, t;
char c;
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d%c%d",&h,&c,&m);
		if(h==0){
			if(m>=10)printf("%d:%d AM\n",12,m);
			else printf("%d:0%d AM\n",12,m);
		}
		else if(h==12){
			if(m>=10)printf("%d:%d PM\n",12,m);
			else printf("%d:0%d PM\n",12,m);
		}
		else if(h>=1&&h<=11){
			if(h>=10){
				if(m>=10)printf("%d:%d AM\n",h,m);
				else printf("%d:0%d AM\n",h,m);
			}
			else {
				if(m>=10)printf("0%d:%d AM\n",h,m);
				else printf("0%d:0%d AM\n",h,m);
			}
		}
		else {
			if(h-12>=10){
				if(m>=10)printf("%d:%d PM\n",h-12,m);
				else printf("%d:0%d PM\n",h-12,m);
			}
			else {
				if(m>=10)printf("0%d:%d PM\n",h-12,m);
				else printf("0%d:0%d PM\n",h-12,m);
			}
			
		}
	}
	return 0;
}
```

---

