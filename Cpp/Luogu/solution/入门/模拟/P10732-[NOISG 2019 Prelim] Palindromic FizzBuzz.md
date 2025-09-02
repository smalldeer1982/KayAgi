# [NOISG 2019 Prelim] Palindromic FizzBuzz

## 题目背景

翻译自 [NOISG2019 Prelim A.Palindromic FizzBuzz](https://github.com/noisg/sg_noi_archive/blob/master/2019_prelim/)。

## 题目描述

给定 $S,E$，对于在 $S,E$ 区间中的每一个数字，如果它不回文，输出它本身，否则输出 `Palindrome!`。

## 说明/提示

### 【样例 #1 解释】
$8,9,11$ 都是回文数，所以输出 `Palindrome!`。
### 【样例 #2 解释】
$3$ 是回文数。
### 【数据范围】
为方便，下文令 $x$ 满足 $1 \leq S \leq E \leq x$。
| $\text{Subtask}$ | 分值 | $x$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $0$ | - | 样例 |
| $1$ | $7$ | $9$ | $S=E$ |
| $2$ | $11$ | $9$ | 无 |
| $3$ | $14$ | $100$ | 无 |
| $4$ | $8$ | $10^5$ | 无 |
| $5$ | $9$ | $10^9$ | $S=E$ |
| $6$ | $20$ | $10^9$ | 无 |
| $7$ | $31$ | $10^{18}$ | 无 |

对于 $100\%$ 的数据，$1 \leq S \leq E \leq 10^{18},E-S+1\leq 10^5$。

## 样例 #1

### 输入

```
8 13```

### 输出

```
Palindrome!
Palindrome!
10
Palindrome!
12
13```

## 样例 #2

### 输入

```
3 3```

### 输出

```
Palindrome!```

## 样例 #3

### 输入

```
999999997 1000000000 ```

### 输出

```
999999997
999999998
Palindrome!
1000000000```

# 题解

## 作者：yfl20130101 (赞：7)

### 思路
对于 $s$ 到 $e$ 之间的所有数，反转这个数，再与原数比较，相同则回文，不相同则不回文，然后按题目输出即可。
### 代码
```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
long long f(long long x){
	long y=0;
	while(x){
		y=y*10+x%10;
		x/=10;
	}
	return y;
}
int main(){
	long long s,e;
	cin>>s>>e;
	for(long long i=s;i<=e;i++){
		if(f(i)==i){
			cout<<"Palindrome!\n";
		}
		else{
			cout<<i<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：__Cyn__ (赞：3)

思路：我们只要枚举在 $S,E$ 区间中的每一个数，再判断它是否和它反转过来的数是否相等即可。

对了，不开 `long long` 见祖宗。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int huiwenshu (int x) {
	int y = 0;
	while (x) {
		y = y * 10 + x % 10;
		x /= 10;
	}
	return y;
}
signed main () {
	int s, e;
	cin >> s >> e;
	for (int i = s; i <= e; i++) {
		if (i != huiwenshu (i)) cout << i << endl;
		else {
			puts ("Palindrome!");
		}
	}
	return 0;
}

```

---

## 作者：huangzilang (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P10732)

## 思路：

这题其实是判断从 $S$ 到 $E$ 之间的数是不是回文数，如果是，输出 `Palindrome!`，不是就输出那个数。但是题目的数据最大是 $10^{18}$，所以要开 `long long`。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long hw(long long x) //求这个数的回文形式
{							 
	long long y=0;	//记得用long long 
	while(x!=0)
	{
		y=y*10+x%10;
		x/=10;
	}
	return y;
}
int main()
{
	long long a,b;
	scanf("%lld%lld",&a,&b); //输入
	for(long long i=a;i<=b;i++)
	{
		if(hw(i)==i) cout<<"Palindrome!\n"; //是回文就输出Palindrome!
		else cout<<i<<endl; //不是就输出那个数本身
	}
	return 0;
}
```

---

## 作者：shenziqi (赞：2)

这是本蒟蒻的第一篇题解，求过。

这道题其实就是从 $S$ 到 $E$ 逐个枚举，判断哪些数是回文数，如果是就输出 `Palindrome!`，否则输出它本身。但提交过后没过，一看数据，原来没开 `long long`。

### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
long long s , e ;	//要开long long
bool hui(long long x){
	long long _x = x , y = 0 ;
	while(_x) {
		y = y * 10 + _x % 10 ;
		_x /= 10 ;
	}
	return (y == x);
}
int main(){
	cin >> s >> e ;
	for(long long i = s ; i <= e ; i ++){
		if(hui(i)){
			cout <<"Palindrome!\n" ;
		}else{
			cout << i << endl ;
		}
	}
	return 0 ; //好习惯
}
```

[题目传送门](https://www.luogu.com.cn/problem/P10732)

---

## 作者：cmask4869 (赞：2)

## 思路
简单的判断，只需要判断每个数是否回文，按照题意输出即可。

## 代码
```
#include<bits/stdc++.h>
using namespace std ;
typedef long long ll ;

bool hw(ll n){
    ll x=0 ;
	ll s=n ;
	while (s>0){
		x=x*10+s%10 ;
		s=s/10 ; 
	}
	if (x==n) return true ;
	else return false ;
}

int main(){
	ll s,e ;
	cin >> s >> e ;
	for (ll i=s ; i<=e ; i++){
		if (!hw(i)){
			cout << i << "\n" ;
		}
		else cout << "Palindrome!" << "\n" ;
	}
	return 0 ;
}
```

---

## 作者：IOI_official (赞：1)

**前置知识：**
1. [to_string() 函数](https://blog.csdn.net/snowcatvia/article/details/96617917)

2. [将 Dev-C++ 改为 c++14](https://blog.csdn.net/Aibiabcheng/article/details/104708516)
  

## 思路：

为什么要改为 c++14 呢？因为 to_string() 这个函数到 c++14 才有，而 DEV 默认是 c++11。

我们枚举这个区间，将其中的每个数用 to_string() 变为字符串，这样就可以枚举它的每一位，方便判断。

若字符串的长度为 $s$，则枚举位数的循环只需循环 $\left \lfloor \frac{s}{2} \right \rfloor$ 次即可。

若此字符串为 $w$，则 $w_i$ 对应的为 $w_{s-i-1}$。

按照这个将相等的组数记下来，如果它是回文数的话，那么相等的组数应为 $\left \lfloor \frac{s}{2} \right \rfloor$。

判断一下即可。

## 注意：

数据范围为 $1 \le S \le E \le 10^{18},E-S+1\le 10^5$，需要开 long long。

## AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,e,c;
string ss;
int main(){
	cin>>s>>e;
	for(long long i=s;i<=e;i++){
		ss.clear();
		c=0;
		ss=to_string(i);
		for(int i=0;i<ss.size()/2;i++){
			if(ss[i]==ss[ss.size()-i-1]){
				c++;
			}
		}
		if(c==ss.size()/2){
			cout<<"Palindrome!"<<endl;
		}
		else cout<<i<<endl;
	}
	return 0;
}
```

---

## 作者：Hanrui1206 (赞：0)

## 【题目大意】
输入 $S,E$。判断 $S \sim E$ 里的回文数，如果是输出 `Palindrome!`，否则输出原数。 

## 【解题思路】
回文数顾名思义，回文的数。

暴力枚举 $S \sim L$ 的每一个数。$E − S + 1 \le 10 ^ 5$ 不会 TLE。

写一个 $\operatorname{check}$ 函数判断是否回文，主函数中用 for 循环，循环加判断。

由于 $1 \leq S \leq E \leq 10^{18}$ ，会爆 `int` 类型，所以要开 `long long` 类型。

## 【参考程序】
```
#include <bits/stdc++.h>
using namespace std;
long long S, E;
//回文数判断。
bool check(long long x) {
	int a[20], flag = 1;
	while (x > 0) { //用一个数组将数字反过来。
		a[flag] = x % 10;
		x /= 10;
		flag++;
	} 
	for (int i = 1; i <= flag / 2; i++) //回文数中心对称，所以只要判断到 flag / 2。
		if(a[i] != a[flag-i]) return 0; //一旦不一样，这个数肯定不是回文数。
	return 1; //没有不一样就是回文数。
} 

int main() {
	cin >> S >> L;
	for (long long i = S; i <= L; i ++) {
		if (check(i) == 1) { //是回文数。
			cout << "Palindrome!\n";
		} else { //不是回文数。
			cout << i << "\n";
		}
	}
	return 0;
}
```

---

## 作者：queenbee (赞：0)

# P10732 Palindromic FizzBuzz题解

## 思路
循环 $S$ 到 $E$，判断是否为回文数。

回文数判断：用数组存储数的每一位，并判断数字翻转后与原数是否相同。

## 程序
```
#include<bits/stdc++.h>	//我爱万能头 
using namespace std;
const int N=100;
long long l,r;
long long kk,ll,len,tt;
int a[N]; 
void Plus(){	//高精加？ 
	for(int i=1;i<=len;i++){
		a[i]++;
		if(a[i]<10){
			return;
		}
		if(a[i]>=10){
			a[i]%=10;
			if(i==len){
				len++;
			}
		}
	}
}
int main(){
	scanf("%lld%lld",&l,&r);
	ll=l;
	while(ll>0){	//设定l为初始值 
		len++;
		a[len]=ll%10;
		ll/=10;
	}
	for(long long i=l;i<=r;i++){	//循环l到r （记得开long long） 
		kk=0;
		for(long long j=1;j<=len/2;j++){	//判断是否为回文数 
			if(a[j]!=a[len-j+1]){
				kk=1;
				printf("%lld\n",i);
				break;
			}
		}
		if(kk==0){
			puts("Palindrome!");
		}
		Plus();	//原数+1 
	}
	return 0;	//完结撒花 
}
```

---

## 作者：Eason_cyx (赞：0)

观察到 $E-S\le10^5$，所以直接枚举从 $S$ 到 $E$，然后逐个判断是否为回文数即可。

记得开 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;
int isp(long long x) {
    string s = to_string(x),t = s;
    reverse(t.begin(),t.end());
    return s == t;
}
int main() {
    long long s,e; cin >> s >> e;
    for(long long i = s;i <= e;i++) {
        if(isp(i)) cout << "Palindrome!\n";
        else cout << i << endl;
    }
    return 0;
}
```

---

## 作者：donnieguo (赞：0)

对于这道题目，我们需要遍历 $S \sim E$ 区间中的每一个数，将其转成字符串，然后判断是否为回文即可。

- 判断字符串回文可以使用一个函数 `reverse`，这个函数可以将一个字符串反转。

- 用法：`reverse(s.begin(), s.end())`，其中 `s` 是要反转的字符串。

- 记得开 `long long`。$1\leq S \leq E \leq 10^{18}$。

代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

long long l, r;
int main()
{
	cin >> l >> r;
	for (long long i = l; i <= r; i++)
	{
		string s1 = to_string(i);
		string s2 = s1;
		reverse(s1.begin(), s1.end());
		if (s1 == s2)
			cout << "Palindrome!" << '\n';
		else	
			cout << s2 << '\n';
	}
	return 0;
}
```

---

## 作者：hard_learn (赞：0)

# 简要题意
判断区间内的数是否为回文数，如果是输出 `Palindrome!`，不是输出本身。
# 思路
遍历区间，判断是否为回文数。
# 注意
要开 `long` `long`。
# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int s,e;
bool check(int x){
	int o=x,cnt=0;
	while(o){
		cnt=cnt*10+o%10;
		o/=10;
	}
	if(cnt==x){
		return 1;
	}
	else{
		return 0;
	} 
}
signed main(){
	cin>>s>>e;
	for(int i=s;i<=e;i++){
		if(check(i)==1){
			cout<<"Palindrome!"<<endl;
		}
		else{
			cout<<i<<endl;
		}
	}
	return 0;
} 
```

---

## 作者：封禁用户 (赞：0)

# 题解：P10732 [NOISG2019 Prelim] Palindromic FizzBuzz

## 题意

题意十分明了，给予你一个区间，判断区间中每一个数是否是回文数。

## 思路

思路比较简单，首先将每一个数按每一位放入一个数组中，顺序无论由前到后和由后到前都可以。

接下来将数组折半循环，判断前后是否一样。

一样的话是回文数，否则就不是回文数。

## AC Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long l,r;
bool hw(int x){
    int a[50]={},t=0;
    while(x>0){
        t++;
        a[t]=x%10;
        x/=10;
    }
    for(int i=1;i<=t/2;i++){
        if(a[i]!=a[t-i+1])return 0;
    }
    return 1;
}
signed main(){
    cin>>l>>r;
    for(int i=l;i<=r;i++){
        if(hw(i))cout<<"Palindrome!";
		else cout<<i;
        cout<<endl;
    }
	return 0;
}
```

---

