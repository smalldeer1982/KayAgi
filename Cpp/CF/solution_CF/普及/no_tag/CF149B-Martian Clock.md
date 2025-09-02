# Martian Clock

## 题目描述

Having stayed home alone, Petya decided to watch forbidden films on the Net in secret. "What ungentlemanly behavior!" — you can say that, of course, but don't be too harsh on the kid. In his country films about the Martians and other extraterrestrial civilizations are forbidden. It was very unfair to Petya as he adored adventure stories that featured lasers and robots.

Today Petya is watching a shocking blockbuster about the Martians called "R2:D2". What can "R2:D2" possibly mean? It might be the Martian time represented in the Martian numeral system. Petya knows that time on Mars is counted just like on the Earth (that is, there are $ 24 $ hours and each hour has $ 60 $ minutes). The time is written as " $ a $ : $ b $ ", where the string $ a $ stands for the number of hours (from $ 0 $ to $ 23 $ inclusive), and string $ b $ stands for the number of minutes (from $ 0 $ to $ 59 $ inclusive). The only thing Petya doesn't know is in what numeral system the Martian time is written.

Your task is to print the radixes of all numeral system which can contain the time " $ a $ : $ b $ ".

## 说明/提示

Let's consider the first sample. String "11:20" can be perceived, for example, as time 4:6, represented in the ternary numeral system or as time 17:32 in hexadecimal system.

Let's consider the second sample test. String "2A:13" can't be perceived as correct time in any notation. For example, let's take the base-11 numeral notation. There the given string represents time 32:14 that isn't a correct time.

Let's consider the third sample. String "000B:00001" can be perceived as a correct time in the infinite number of numeral systems. If you need an example, you can take any numeral system with radix no less than 12.

## 样例 #1

### 输入

```
11:20
```

### 输出

```
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22```

## 样例 #2

### 输入

```
2A:13
```

### 输出

```
0
```

## 样例 #3

### 输入

```
000B:00001
```

### 输出

```
-1
```

# 题解

## 作者：Rex01 (赞：18)

## [CF149B 题目传送门](https://www.luogu.com.cn/problem/mF149B)

## 题目大意
给你一个 $24$ 进制下的时间，若这个时间在 $n$ 进制下，满足 $24$ 进制的时间，则输出 $n$。如果没有，输出 $0$。如果有无穷个，则输出 $−1$。

## 解决思路
分步走：
- 处理输出 $0$ 或 $-1$ 的情况。分别计算出小时的最大值 $Maxh$ 和分钟的最大值 $Maxm$，并且把去掉前导零的字符串存入数组 $hh$ 和 $mm$ 当中。

- 判断其初始时间是否合法，即小时的最大值 $Maxh$ 是否 $> 23$，或者分钟的最大值 $Maxm$ 是否 $> 59$。如果不合法，根据 $n$ 进制中每一位一定 $< n$ 的性质，输出 $0$。

- 判断 $hh$ 数组和 $mm$ 数组的大小是否 $\leq 1$，如果 $\leq 1$，则输出 $−1$，$\because$ 末尾的数值在 $n$ 进制转十进制中不受影响。

- 处理所有的合法进制。将 $f$ 设为最小的可能进制，即 $f$ 为 $\max(Maxh,Maxm) + 1$。不断地增大 $f$，将小时和分钟的 $10$ 进制算出来，同样如第一步，判断时间是否合法。如果合法，则输出，否则结束。但是注意，当第一个可能的 $f$ 就不行的话就直接输出 $0$。

## 代码展示
```cpp
#include <iostream>
#include <cmath>
using namespace std;

string s;
int l, z, z1, z2, hh[15], mm[15];
int cnt1, cnt2, f, h, m;
int Maxh = -1, Minh = 1e9 + 7;
int Maxm = -1, Minm = 1e9 + 7;
//定义一大堆变量爽了

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);//减少输入时间
	cin >> s;
	l = s.size();
	for(int i = 0; i < l; i++)
		if(s[i] == ':') z = i;//记录':'的位置
	for(int i = 0; i < z; i++)
	{
		if(s[i] != '0'){z1 = i; break;}
		if(i == z - 1) z1 = z - 1;
	}
	for(int i = z + 1; i < l; i++)
	{
		if(s[i] != '0'){z2 = i; break;}
		if(i == l - 1) z2 = l - 1;
	}
	for(int i = z1; i < z; i++)
		if(isdigit(s[i]))//isdigit(x)判断x是否为数字
		{
			int z = s[i] - '0';
			Maxh = max(Maxh, z);
			Minh = min(Minh, z);
			hh[++cnt1] = z;
		}
		else if('A' <= s[i] && s[i] <= 'Z')
		{
			int z = s[i] - 'A' + 10;
			Maxh = max(Maxh, z);
			Minh = min(Minh, z);
			hh[++cnt1] = z;
		}
	for(int i = z2; i < l; i++)
		if(isdigit(s[i]))
		{
			int z = s[i] - '0';
			Maxm = max(Maxm, z);
			Minm = min(Minm, z);
			mm[++cnt2] = z;
		}
		else if('A' <= s[i] && s[i] <= 'Z')
		{
			int z = s[i] - 'A' + 10;
			Maxm = max(Maxm, z);
			Minm = min(Minm, z);
			mm[++cnt2] = z;
		}
	if(Maxh > 23 || Maxm > 59)
	{//如果'时'最大超过23且'分'最大超过59
		cout << "0" << endl;
		return 0;//换行是个好习惯
	}
	if(cnt1 <= 1 && cnt2 <= 1)
	{
		cout << "-1" << endl;
		return 0;//好习惯 * 2
	}
	f = max(Maxh, Maxm) + 1;
	while(true)
	{
		int a = cnt1 - 1;
		h = 0; m = 0;//h表示小时,m表示分钟
		for(int i = 1; i <= cnt1; i++)
		{
			int z = pow(f, a);
			h += z * hh[i]; a--;
			//计算小时↑
		}
		a = cnt2 - 1;
		for(int i = 1; i <= cnt2;i++)
		{
			int z = pow(f, a);
			m += z * mm[i]; a--;
			//计算分钟↑
		}
		if((h < 0 || h > 23) || (m < 0 || m > 59))
		{//如果小时和分钟均不成立(我在说什么...)
			if(f == max(Maxh, Maxm) + 1)
				cout << "0" << endl;
			break;//不加这行将会喜提TLE
		}
		else cout << f << " ";//按题目格式输出
		f++;//别忘了每次输出完加1
	}	
	return 0;
}
```

### 温馨提示
**不抄题解，从我做起！**~~别跟我说你没看见或者不识字。~~

---

## 作者：alan1118 (赞：12)

好家伙，一道字符串模拟硬控我将近一个小时，必须写篇题解梳理一下好吧，~~还是太菜~~，所以我会写的比较详细。

### 题意

给你一个时间，请你求出这个时间用哪些进制表示是合法的。如果无解输出 $0$，有无数解输出 $-1$。

### 思路

1. 将时和分分别抠出来，而且要同时去掉前导零。这一步我感觉细节还是挺多的。（不知道是不是和我是直接用字符串存的有关）

   具体代码如下：

   ``` cpp
   string a;
   cin >> a;
   int b, c = 0, d = 0;
   for(int i = 0; i < a.size(); i++) // 找到冒号的位置
   {
   	if(a[i] == ':')
   	{
   		b = i;
   		continue;
   	}
   }
   for(int i = 0; i < b-1; i++) // 找到时的第一个不是零的地方
   {
   	if(a[i] == '0') c++;
   	else break;
   }
   string h = a.substr(c, b-c); // 抠出时
   for(int i = a.size()-1; i >= 0; i--) // 找到分的第一个不是零的地方
   {
   	if(i == b) break;
   	if(a[i] != '0') d = i;
   }
   string m = (d ? a.substr(d, a.size()) : "0"); // 抠出分
   ```

   我这里处理的可能有些繁琐，大家有自己的想法的话可以写自己的。

   补充：`str.substr(pos, len)`：$str$ 字符串 $[pos, pos+len)$ 所构成的字符串（$pos,len$ 均为整数）。

2. 特判无解和无数解

   无解：如果输入的时间的时和分的最大的一位就以 $>24$ 或 $>59$，那么就无解，~~易证~~，因为在 $x$ 进制下每一位要小于 $x$。

   无数解：如果输入的时间的时和分都只有一位，那么就有无数解。证明如下：

   设一个数 $n$ 是 $x$ 进制的，且只有一位

   $\therefore$ 这个数的 $10$ 进制为 $n \times x^0=n \times 1=n$

   $\therefore$ 此时无论 $x$ 为几都必然成立。

   （本蒟蒻数学不好，不规范勿喷，大概就是这个意思）

   注意：这两个特判的顺序不能改变，无数解的特判必须是在已经确认合法后进行的。

3. 剩下的就比较简单了，就是通过枚举找出所有合法的进制，因为分最大到 $59$，所以从时、分中最大的一位 $+1$ 枚举到 $60$ 进制就行了，代码也比较简单。但是要记住如果没找到任何一个合法的进制的话，最后也要输出无解。

### AC Code

``` cpp
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

bool isTime(int h, int m)
{
	return (0 <= h && h <= 23 && 0 <= m && m <= 59);
}

int toTen(string s, int jz)
{
	int res = 0, m = 0;
	for(int i = s.size()-1; i >= 0; i--)
	{
		int x = ('A' <= s[i] && s[i] <= 'Z' ? s[i]-'A'+10 : s[i]-'0');
		res += x * pow(jz, m);
		m++;
	}
	return res;
}

int main()
{
	string a;
	cin >> a;
	
	int b, c = 0, d = 0, maxn = 0, maxh = 0, maxm = 0;
	for(int i = 0; i < a.size(); i++)
	{
		if(a[i] == ':')
		{
			b = i;
			continue;
		}
		int x = ('A' <= a[i] && a[i] <= 'Z' ? a[i]-'A'+10 : a[i]-'0');
		if(x > maxn) maxn = x;
	}
	for(int i = 0; i < b-1; i++)
	{
		if(a[i] == '0') c++;
		else break;
	}
	string h = a.substr(c, b-c);
	for(int i = a.size()-1; i >= 0; i--)
	{
		if(i == b) break;
		if(a[i] != '0') d = i;
	}
	string m = (d ? a.substr(d, a.size()) : "0");
	
	for(int i = 0; i < a.size(); i++)
	{
		int x = ('A' <= a[i] && a[i] <= 'Z' ? a[i]-'A'+10 : a[i]-'0');
		if(i < b && x > maxh) maxh = x;
		if(i > b && x > maxm) maxm = x;
	}
	if(maxh > 23 || maxm > 59) return cout << 0 << endl, 0;
	
	if(h.size() <= 1 && m.size() <= 1) return cout << -1 << endl, 0;
	
	bool f = false;
	for(int i = maxn + 1; i <= 60; i++)
	{
		if(isTime(toTen(h, i), toTen(m, i)))
		{
			cout << i << " ";
			f = true;
		}
	}
	if(!f) return cout << 0 << endl, 0;
	return 0;
}
```

完结撒花！

---

## 作者：PR_CYJ (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/CF149B)
# 题意
这道题就是给一个未知进制的 $ 24 $ 小时格式的时钟，输出所有合法的进制。

这道题其实就在考察进制有关知识。
# 前置铺垫
对于一个 $ x $ 进制的数 $ \overline{a_1,a_2,a_3,\cdots ,a_n} $，定义其数码最大值为 $ \max(a_1,a_2,a_3,\cdots ,a_n) $。

对于一个 $ x $ 进制的数，其每一位上的数码值都一定小于 $ x $。反过来也一样，一个数的进制基数必然小于其数码最大值。
# 思路
看到这道题，我们能确定思路是枚举加模拟。
### Step one：预处理
直接以字符串的形式读入时间，然后分开处理。

对于小时，一位一位往过读，跳过无用的前导零，将数码部分从字符转化为数，并按位存储到 vector 里。

对于分钟，以同样方法处理。

在处理过程中，分别求出小时和分钟部分的数码最大值，记作 $ maxh $ 和 $ maxm $。如果小时部分的数码最大值大于 $ 23 $，那么直接输出 $ 0 $。如果小时和分钟的位数（不含已去掉的前导零）都小于等于，那么就输出。因为，一个数从右向左的第一位的值不受这个数的进制地影响。（不懂的可以自己转化一下进制试试）
### Step two：枚举加模拟
我们直接从 $ \max(maxh,maxm) $ 开始枚举，按次枚举进制。对于每个进制，我们用模拟计算出小时和分钟对应的十进制值，再判断它合不合法。这样我们找出第一个不符合要求的进制，并将这个进制基数减一作为合法进制基数的最大值，记作 $ ans $。
### Step three：输出答案
根据定义，我们可以思考出，在 $ \max(maxh,maxm) $ 和 $ ans $ 构成的区间里，所有的进制都是合法的。所以，我们可以直接一个循环输出答案。

不过，要特判一下，如果 $ \max(maxh,maxm) $ 大于 $ ans $，那么就没有合法进制，则输出 $ 0 $。
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	vector<int> h,m;
	int ans=0,maxh=0,maxm=0,ii=0;
	string s;
	cin>>s;
	for(;s[ii]=='0';ii++){}
	for(;s[ii]!=':';ii++)
	{
		int t;
		if (s[ii]<='9')
			t=s[ii]-'0';
		else
			t=s[ii]-'A'+10;
		maxh=max(maxh,t);
		h.push_back(t);//将数一位一位的存进 vector 
	}
	ii++;
	for(;s[ii]=='0';ii++){}
	for(;ii<s.size();ii++)
	{
		int t;
		if (s[ii]<='9')
			t=s[ii]-'0';
		else
			t=s[ii]-'A'+10;
		maxm=max(maxm,t);
		m.push_back(t);//将数一位一位的存进 vector 
	}
	if (maxh>23)//先特判小时无论怎样都不合法的情况 
	{
		cout<<0<<endl;
		return 0;
	}
	if (h.size()<=1&&m.size()<=1)//再特判有无数种合法进制的情况 
	{
		cout<<-1<<endl;
		return 0;
	}
	//此前皆为预处理部分 
	maxh=max(maxh,maxm);
	maxh++;
	for(int i=maxh;;i++)
	{
		int a=0,b=0;
		for(int j=0;j<h.size();j++)
		{
			a*=i;
			a+=h[j];
		}
		for(int j=0;j<m.size();j++)
		{
			b*=i;
			b+=m[j];
		}
		//转化为十进制 
		if (a>=24||b>=60)//如果小时或分钟不合法 
		{
			ans=i-1;//找到最大值 
			break;
		}
	}
	//模拟部分，找出合法进制基数的最大值 
	if (ans<maxh)
		cout<<0<<endl;
	else
		for(int i=maxh;i<=ans;i++)
			cout<<i<<" ";
	//输出答案
	//注意：此时要特判，如果最大值小于左区间，就说明没有合法进制 
}
```

---

## 作者：OIer6666 (赞：4)

## CF149B题解：

题目：
给一个未知进制的 $24$ 小时格式的时钟，输出所有合法的进制。

这道题主要练习进制转换。

枚举 $2$ 至 $100$ 进制。如果该进制可行，即输出该进制。
如何判断 $0$ 或 Infinity？

如果 $2$ 至 $100$ 进制没有一个可行，则输出 $0$；（下面把时称为 $s$，分称为 $f$）若 $s_{100}\le N_{100}$，且 $f_{100}\le Z_{100}$，则输出 $-1$。

### Code：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
bool f(char x[],char y[],int jin){
	int xlen=strlen(x),ylen=strlen(y);
	ll xint=0,yint=0;
	ll j=1,temp;
	for(int i=xlen-1;i>=0;i--){
		if(jin<10){
			if(x[i]>='0'&&x[i]<='0'+jin-1){
				temp=x[i]-'0';
				temp*=j;
			}else{
				return false;
			}
		}else{
			if(x[i]>='0'&&x[i]<='9'){
				temp=x[i]-'0';
				temp*=j;
			}else if(x[i]>='A'&&x[i]<='A'+jin-11){
				temp=x[i]-'A'+10;
				temp*=j;
			}else{
				return false;
			}
		}
		xint+=temp;
		if(xint>=24)
			return false;
		j*=jin;
	}
	j=1;
	for(int i=ylen-1;i>=0;i--){
		if(jin<=10){
			if(y[i]>='0'&&y[i]<='0'+jin-1){
				temp=y[i]-'0';
				temp*=j;
			}else{
				return false;
			}
		}else{
			if(y[i]>='0'&&y[i]<='9'){
				temp=y[i]-'0';
				temp*=j;
			}else if(y[i]>='A'&&y[i]<='A'+jin-11){
				temp=y[i]-'A'+10;
				temp*=j;
			}else{
				return false;
			}
		}
		yint+=temp;
		if(yint>=60)
			return false;
		j*=jin;
	}
	return true;
}
int main(){
	char s[10005];cin>>s;
	char l[10005],r[10005];
	int lop=-1,rop=-1;
	bool zero=true;
	bool qian=true;
	for(int i=0;i<strlen(s);i++){
		if(s[i]==':'){
			qian=false;
			zero=true;
			continue;
		}
		if(s[i]=='0'&&zero){
			continue;
		}
		if(qian){
			l[++lop]=s[i];
		}else{
			r[++rop]=s[i];
		}
		zero=false;
	}
	if(lop==-1&&rop==-1){
		cout<<-1;
		return 0;
	}
	if(lop==-1)
		lop++,l[0]='0';
	if(rop==-1)
		rop++,r[0]='0';	
	if(lop==0&&rop==0){
		if(((l[0]>='0'&&l[0]<='9')||(l[0]>='A'&&l[0]<='N'))&&((r[0]>='0'&&r[0]<='9')||(r[0]>='A'&&r[0]<='Z')))
			cout<<-1;
		else
			cout<<0;
	}else{
		int cnt=0;
		for(int i=2;i<=100;i++){
			if(f(l,r,i)){
				cout<<i<<" ";
				cnt=1;
			}
		}
		if(cnt==0)
			cout<<0;
	}
	return 0;
}
```

---

## 作者：2011FYCCCTA (赞：2)

[原题](https://www.luogu.com.cn/problem/CF149B)

---

### 思路

直接暴力枚举在每一种进制下 $a$ 和 $b$ 的值是否超过范围即可，范围是 $2 \sim 59$，最大范围是 $59$ 是因为它是分和时的范围中更大的那一个（分）的上限。

大于此范围若仍满足条件就有无限种解，因为这样的数据只能是：`1:1`（可能有前导零），由于 $n^0 = 1$，因此有无限种解。

若在此范围内无解则无解，因为若在最小的进制 $2$ 进制下仍不满足条件，则在其它更大的进制下就更不可能有解。



---

## 作者：123456zmy (赞：1)

题意：  
给一个未知进制的 24 小时格式的时钟，输出所有合法的进制。
___
枚举所有可能的进制，再用类似快读的方式计算出值，如果小时不超过 $24$ 且分钟不超过 $60$ 则为合法，统计并输出。至于 $0$ 和 $INF$ 的特判，$0$ 就是进制超过 $59$ 但还没有解，$INF$ 则是进制超过 $59$ 还有解。代码中判断方法略有不同但本质上是一样的。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long//位数大了会炸int，其实加上特判也可以不开
using namespace std;
string _a;
int ans,a,b,ansi[101];
signed main()
{
	cin>>_a;
	int k=1;
	while(k++)
	{
		if(ans>60)
		{
			puts("-1");
			return 0;
		}
		if(k>=100)
		{
			if(ans)for(int i=1;i<=ans;i++)printf("%d ",ansi[i]);
			else puts("0");
			return 0;
		}
		int i=0;
		a=0;b=0;
		for(i;_a[i]!=':';i++)
		{
			a*=k;
			a+=((_a[i]>'9'?_a[i]-'A'+10:_a[i]-48)<k?_a[i]>'9'?_a[i]-'A'+10:_a[i]-48:1000);
		}
		++i;
		for(i;i<_a.size();i++)
		{
			b*=k;
			b+=((_a[i]>'9'?_a[i]-'A'+10:_a[i]-48)<k?_a[i]>'9'?_a[i]-'A'+10:_a[i]-48:1000);
		}
//		printf("%d %d\n",a,b);
		if(a<24&&b<60)ansi[++ans]=k;
	}
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF149B)
## 思路
由样例三可以发现时间是可能有前导零的，所以先去除所有前导零，然后在进行下面的操作。

由于 $k$ 进制每位最大只能有 $(k - 1)$，所以假设该时钟每位数字的最大值为 $mx$，则至少为 $mx + 1$ 进制。所以当 $mx + 1$ 进制下时间的小时 $h \geq 24$ 或分钟 $m \geq 60$，那么就没有合法的进制。否则如果小时与分钟的位数都为一（注意**先去前导零**），那么有无穷解（因为无论是几进制，最小位的权值都为一，所以当小时与分钟的位数都为一时无论进制如何变化，表示的时间都不变。一定要**先判断是否有解**）。

当有解且非无穷解时，可以从 $mx + 1$ 进制起开始尝试每种进制，当表示的时间不合法时退出循环，否则输出这个进制。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)

// #define debug

typedef long long ll;
typedef double dou;
typedef pair<int, int> pii;

const int maxlen = 5 + 10;

string str;

int len, la, lb, rea, reb, mx, cnt;
int a[maxlen], b[maxlen];
string stra, strb;
void srt_int (int &lx, int &rex, int *x, string strx)
{
	char ch;
	
	FOR (0, lx - 1, i)
	{
		ch = strx[i];
		if (i - rex == 0 && ch == '0') {
			++rex;
		}
		if (isdigit(ch))
		{
			x[i + 1 - rex] = (int)(ch - '0');
		}else
		{
			x[i + 1 - rex] = (int)(ch - 'A') + 10;
		}
		mx = MAX(mx, x[i + 1 - rex] + 1);
	}
	lx -= rex;
}
int to_k (int &lx, int *x, int k)
{
	int res = 0, val = 1;
	RFOR (1, lx, i) {
		res += val*x[i];
		val *= k;
	}
	
	return res;
}

int main ()
{
	getline(cin, str);
	
	len = str.size();
	FOR (0, len - 1, i)
	{
		if (str[i] == ':')
		{
			stra = str.substr(0, i);
			la = i;
			strb = str.substr(i + 1, len);
			lb = len - i - 1;
		}
	}
	srt_int(la, rea, a, stra);
	srt_int(lb, reb, b, strb);
	if (la <= 1 && a[1] < 24 && lb <= 1 && b[1] < 60)
	{
		printf("-1\n");
		return 0;
	}
	FOR (mx, 60, k)
	{
		if (to_k(la, a, k) < 24 && to_k(lb, b, k) < 60) {
			++cnt;
			
			printf("%i ", k);
		}else {
			if (!cnt) {
				printf("0");
			}
			printf("\n");
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：浮光掠影 (赞：0)

### 题意：

定义火星时间也是小时化为十进制后不能大于 $23$，分钟化为十进制后不能大于 $59$，给定一个时间，问在哪些进制中这个时间是合法时间。

### 思路：

先处理一下前缀零，然后把冒号前后的串分开，遍历进制数暴力判断即可，需要注意一些小的细节。

### Code


```cpp
#include <bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
string s,s1,s2;
int tr(char c)
{
	if(c>='0'&&c<='9')
		return (c-'0');
	else if(c>='A'&&c<='Z')
		return (c-'A'+10);
}
bool check(int num)
{
	int sum1=0,sum2=0;
	int tmp=1;
	for(int i=s1.size()-1;i>=0;i--)
	{
		sum1+=tr(s1[i])*tmp;
		tmp*=num;
	}
	tmp=1;
	for(int i=s2.size()-1;i>=0;i--)
	{
		sum2+=tr(s2[i])*tmp;
		tmp*=num;
	}
	if(sum2>=60||sum1>=24)
	return false;
	return true;
}
int main()
{
	cin>>s;
	int maxx=-1;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]==':')
		{
			s1=s.substr(0,i);
			s2=s.substr(i+1,s.size()-i-1);
		}
		else
		{
			maxx=max(maxx,tr(s[i]));
		}
	}
	while(*s1.begin()=='0')
	s1.erase(s1.begin());
	while(*s2.begin()=='0')
	s2.erase(s2.begin());
	if(s1.size()<=1&&s2.size()<=1&&tr(s1[0])<24&&tr(s2[0])<60)
	{
		printf("-1\n");
	}
	else if((s1.size()<=1&&s2.size()<=1)&&(tr(s1[0])>=24||tr(s2[0])>=60))
	{
		printf("0\n");
	}
	else
	{
		if(check(maxx+1)==false)
		{
			printf("0\n");
			return 0;
		}
		for(int num=maxx+1;;num++)
		{
			if(check(num))
			printf("%d ",num);
			else
			break;
		}
	}
}
```

---

## 作者：liuli688 (赞：0)

### 前置知识：
`scanf` 的扫描集：

ANSI C 标准向 `scanf()` 增加了一种新特性，称为扫描集（scanset）。 扫描集定义一个字符集合，可由 `scanf()` 读入其中允许的字符并赋给对应字符数组。 扫描集合由一对方括号中的一串字符定义，左方括号前必须缀以百分号。例如，以下的扫描集使 `scanf()` 读入字符 A、B 和 C：
```
%[ABC]
```
（摘自[百度百科](https://vhsagj.smartapps.baidu.com/pages/lemma/lemma?lemmaTitle=scanf&lemmaId=10773316&from=askcard)）

`from_chars`：
见 [xyf007](https://www.luogu.com.cn/user/68273) 的[题解](https://www.luogu.com.cn/article/mazn6yoh)。
### 思路：
有了上述知识，实现本题便十分简单了。

首先，用 `scanf` 读入时和分。虽然直接 `%s` 会连冒号一起输入，但是可以用扫描集把冒号过滤掉。

然后，从字符层面确定最低进制。枚举时和分的每个字符，对字母和数字分类讨论，再取最大值。

接着只需用 `from_chars` 计算每个进制下的值，判断是否合法即可。注意要从时和分的最低进制中取最大值开始循环，到 $60$ 结束（如果有超过 $59$ 的进制合法，说明有无穷种合法的进制）。
### 代码：
```cpp
#include <bits/stdc++.h>
#include <charconv>
using namespace std;

#define pb push_back
#define reg register

#define int long long//记得开 long long

char h[9],m[9];
int hv,mv,hlim,mlim,hlen,mlen;
vector<int> ans;

signed main()
{
    reg int i;
    reg vector<int>::iterator it;//声明 vector 迭代器，输出方便
    scanf("%[0-9A-Z]:%[0-9A-Z]",&h,&m);//只读入 0~9、A~Z 区间内的字符
    hlen = strlen(h);//时的长度
    mlen = strlen(m);//分的长度
    for(i = 0;i < hlen;++i)//确定时的最低进制
        if(isalpha(h[i]))//分类讨论
            hlim = max(hlim,h[i]-'A'+10ll);//max 函数的两个参数必须一样，所以加上 long long 类型的数后整个数将会变为 long long 类型
    	else
            hlim = max(hlim,(long long)h[i]-'0');//同上
    for(i = 0;i < mlen;++i)//确定分的最低进制
        if(isalpha(m[i]))//PS:isalpha 函数返回该字符是否为字母
            mlim = max(mlim,m[i]-'A'+10ll);
    	else
            mlim = max(mlim,(long long)m[i]-'0');
    for(i = max(hlim,mlim) + 1ll;i <= 60ll;++i)//计算每个进制下的值，判断是否合法
    {
        from_chars(h,h+hlen,hv,i);//计算时
        from_chars(m,m+mlen,mv,i);//计算分
        if(hv < 24ll && mv < 60ll)
            ans.pb(i);//存入 vector，不能直接输出，因为有无穷种合法的进制要输出 -1
        else
            break;//进制过大，break，节省时间
    }
    if(ans.empty())//无合法进制
        printf("0");
    else if(ans.back() == 60ll)//无穷种
        printf("-1");
    else
        for(it = ans.begin();it != ans.end();++it)//迭代器遍历 vector，此语句相当于 for(it = 0;it != ans.size();++it)
            printf("%lld ",*it);//*it 相当于 ans[it]
    return 0;
}
```
**记得用 C++20 提交。**

Ex：附正解一份。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define reg register

#define int long long

char h[9],m[9];
int a[9],hlim,mlim,hlen,mlen;
vector<int> ans;

#define change(c) (isalpha(c) ? c - 'A' + 10 : c - '0')
int basec(int base,int len,char c[])
{
    reg int i,ans = 0,w = 1;
    for(i = len - 1;~i;--i)
	    a[len-1-i] = change(c[i]);
	for(i = 0;i < len;++i)
    {
		ans += w * a[i];
		w *= base;
	}
	return ans;
}

signed main()
{
    reg int i;
    reg vector<int>::iterator it;
    scanf("%[0-9A-Z]:%[0-9A-Z]",&h,&m);
    hlen = strlen(h);
    mlen = strlen(m);
    reverse(h,h+hlen);
    reverse(m,m+mlen);
    for(i = hlen - 1;i && h[i] == '0';--i,--hlen);
    for(i = mlen - 1;i && m[i] == '0';--i,--mlen);
    reverse(h,h+hlen);
    reverse(m,m+mlen);
    h[hlen] = m[mlen] = '\0';
    for(i = 0;i < hlen;++i)
        if(isalpha(h[i]))
            hlim = max(hlim,h[i]-'A'+10ll);
    	else
            hlim = max(hlim,(long long)h[i]-'0');
    for(i = 0;i < mlen;++i)
        if(isalpha(m[i]))
            mlim = max(mlim,m[i]-'A'+10ll);
    	else
            mlim = max(mlim,(long long)m[i]-'0');
    for(i = max(hlim,mlim) + 1ll;i <= 60ll;++i)
    {
        if(basec(i,hlen,h) < 24ll && basec(i,mlen,m) < 60ll)
            ans.pb(i);
        else
            break;
    }
    if(ans.empty())
        printf("0");
    else if(ans.back() == 60ll)
        printf("-1");
    else
        for(it = ans.begin();it != ans.end();++it)
            printf("%lld ",*it);
    return 0;
}
```

---

## 作者：weihaozhen2010 (赞：0)

# 题意：

### [CF149B](https://www.luogu.com.cn/problem/CF149B)

给你一个 $24$ 进制的时间，这个时间在 $n$ 进制下，满足 $24$ 进制的时间，则输出 $n$。如果没有，输出 $0$。如果有无穷个，则输出 $-1$。

#  思路：

- 一道模拟题。

- 步骤一：首先，优先处理没有和无穷多的情况。将小时和分钟分开算出其中的最大值 $mx1$ 和 $mx2$，并且把去掉前导零的字符串存入数组 $b$ 和 $c$ 当中。

- 步骤二：接着判断其初始是否为合格的时间，即 $mx1$ 是否大于 $23$ 呢，或者 $mx2$ 是否大于 $59$。若为是，根据 $n$ 进制中每一位必须小于 $n$ 的必然，则输出 $0$。

- 步骤三：然后判断 $b$ 和 $c$ 的大小是否小于等于 $1$，若为是，则输出 $-1$。因为，末尾的数值在 $n$ 进制转十进制中并不受影响。

- 步骤四：最后处理所有的合法进制。将 $k$ 设为最小的可能进制，即 $k$ 为 $mx1$ 和 $mx2$ 的最大值再加 $1$。不断地增大 $k$，将小时和分钟的 $10$ 进制算出来，同样如步骤一，判断是否合法。若为是，则输出，否则结束。但是注意，当第一个可能的 $k$ 就不行的话就需要输出 $0$。

# 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char a[20];
int b[20],c[20]; 
int len,p,q1,q2,cnt1=0,cnt2=0;
int mx1=-1,mn1=1e9+7;
int mx2=-1,mn2=1e9+7;
int k,x=0,y=0;
bool flag=0;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>a;
	len=strlen(a);
	for(int i=0;i<len;i++)
	{
		if(a[i]==':') p=i;
	}
	for(int i=0;i<p;i++)
	{
		if(a[i]!='0') 
		{
			q1=i;
			break;
		}
		if(i==p-1)
		{
			q1=p-1;	
		} 
	}
	for(int i=p+1;i<len;i++)
	{
		if(a[i]!='0')
		{
			q2=i;
			break;
		}
		if(i==len-1)
		{
			q2=len-1;
		}
	}
	for(int i=q1;i<p;i++)
	{
		if(a[i]<='9'&&a[i]>='0') 
		{
			mx1=max(mx1,a[i]-'0');
			mn1=min(mn1,a[i]-'0');
			b[++cnt1]=a[i]-'0';
		}
		else if(a[i]<='Z'&&a[i]>='A')
		{
			mx1=max(mx1,a[i]-'A'+10);
			mn1=min(mn1,a[i]-'A'+10);
			b[++cnt1]=a[i]-'A'+10;
		}
	}
	for(int i=q2;i<len;i++)
	{
		if(a[i]<='9'&&a[i]>='0') 
		{
			mx2=max(mx2,a[i]-'0');
			mn2=min(mn2,a[i]-'0');
			c[++cnt2]=a[i]-'0';
		}
		else if(a[i]<='Z'&&a[i]>='A')
		{
			mx2=max(mx2,a[i]-'A'+10);
			mn2=min(mn2,a[i]-'A'+10);
			c[++cnt2]=a[i]-'A'+10;
		}
	}
	if(mx1>23||mx2>59)
	{
		cout<<"0";
		return 0;
	}
	if(cnt1<=1&&cnt2<=1)
	{
		cout<<"-1";
		return 0;
	}
	k=max(mx1,mx2)+1;
	while(1)
	{
		int t=cnt1-1;
		x=0;
		y=0;
		for(int i=1;i<=cnt1;i++)
		{
			int s=pow(k,t);
			x+=s*b[i];
			t--;	
		}
		t=cnt2-1;
		for(int i=1;i<=cnt2;i++)
		{
			int d=pow(k,t);
			y+=d*c[i];
			t--;
		}
		if((x<0||x>23)||(y<0||y>59))
		{
			if(k==max(mx1,mx2)+1) cout<<"0";
			break;
		}
		else
		{
			cout<<k<<" ";
		}
		k++;
	}	
	return 0;
}
```

---

## 作者：fkcufk (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF149B)

## 思路

一道进制转换题。

由于 $1$ 时等于 $60$ 分，因此最大为 $59$ 进制。

我们可以暴力枚举所有进制，如果这个进制符合要求，那么输出这个进制。我们可以用一个 $flag$ 变量来记录是否满足条件。初始时 $flag=0$，如果满足，则 $flag=1$。

如果枚举完毕以后没有，即 $flag=0$，再大的范围也就无解，那么输出 $0$。

如果大于此范围后依然符合要求，即时和分都 $<2$，则有无穷种，输出 `-1`。这种情况有 `01:01`,`00:00`,`01:00`,`00:01`。

---

