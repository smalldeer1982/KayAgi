# BowWow and the Timetable

## 题目描述

已知圣彼得堡的车站会在第 $4^k(k\geq 0)$ 分钟开出新的一趟火车，已知BowWow团队将在第 $s(0\leq s\leq 2^{100})$ 分钟时到达火车站，他们想知道自己错过了多少趟火车；换句话说，在第 $s$ 分钟之前开出了多少趟火车。举个例子，当 $s=20$ 时，他们错过了第 1、4 和 16 分钟的火车。现在只有你知道这个时间 $s$，请你求出他们错过了多少趟火车。

## 样例 #1

### 输入

```
100000000
```

### 输出

```
4
```

## 样例 #2

### 输入

```
101
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10100
```

### 输出

```
3
```

# 题解

## 作者：rsjw (赞：4)

CF昨天晚上的比赛第一题，大水题。

~~但没第二道题水，第三道题题面看不懂~~

先发发广告：[这是我搭的OJ](https://rsjoj.cf)

首先要弄清题目意思，在$4^k$的时间会经过火车，那么，我们很容易想到把输入的二进制转化成四进制，两位一压就可以了。然后数一下有几位，就是错过了多少站。

当然，如果此时此刻刚好开来火车，不算错过，所以还需要特判。

下面是代码：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
char in[110];
int l,ans=0;
int main() {
	scanf("%s",in);
	l=strlen(in);
	if(l%2)
		for(int i=l-1; i>=1; i--) 
        if(in[i]=='1') {
				printf("%d",1+l/2);
				return 0;
			}
	printf("%d",l/2);
	return 0;
}
```


---

## 作者：一个低调的人 (赞：4)

- 这道题的题意是给你一个二进制形式的数字，求4的非负整数次幂有多少个小于它。
- 由于4是2的二次幂，所以当这个二进制的数的长度大于 $1,3,5,7...$ 时，就分别大于等于 $4^0,4^1,4^2,4^3...$ ，由于题目告诉我们只有大于这个开车时间，才能算是错过了，故需要特判一下位数为奇数的情况，看看除了最高位外是否还有位置上的数为 $1$ 。
- 具体细节详见 **代码** 。
## Code
```cpp
#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
using namespace std;
int na,ans;
char s[101];
int main()
{
	scanf("%s",s+1);
	na=strlen(s+1);
	if(na==1&&s[1]=='0')
	{
		ans=0;
	}
	else if(na%2==1)
	{
		ans=na/2;
		for(int i=na;i>1;i--)
		{
			if(s[i]=='1')
			{
				ans++;break;
			}
		}
	}
	else
	{
		ans=na/2;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：xxxalq (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/CF1204A) &[CF链接](http://codeforces.com/problemset/problem/1204/A)

## 题意简述：

求二进制数 $s$ 一共包含了多少 $4^k$ 的数，如果 $4^k=s$ 则不算，可以参考样例 $1$。

## 思路分析：

通过分析可得一个数二进制形式的奇数位代表 $4^k$，所以只需要看 $s$ 有多少个奇数位即可，还需要判断在 $s$ 时刻是否正好有火车到站，只需判断当 $s$ 的二进制形式位数为奇数时，除最高位以外是否都是 $0$。

## 代码：

```cpp
#include<iostream>
using namespace std;
string str;
int main(){
	cin>>str;
	if(str.size()%2==0){//如果是偶数
		cout<<str.size()/2;//直接计算
	}else{//否则就是奇数
		for(int i=1;i<str.size();i++){//i从第二位枚举
			if(str[i]=='1'){
				cout<<str.size()/2+1;//如果有1直接正常输出
				return 0;
			}
		}
		cout<<str.size()/2;//如果全是0，向下取整输出
	}
	return 0;
}
```

---

## 作者：fls233666 (赞：2)

**2020年2月16日更新：修正题解排版格式。**

-----------

首先你会发现，把题目给出的二进制数转化为十进制数是不可能的。这个数字无比的大，把这个数存下来是一件及其麻烦的事。那么，有没有什么简单的办法呢？

首先我们知道，$2^2=4$。所以在二进制下每两位对应着四进制中的一位。那么我们不妨试试把一些形如 $4^n$ 的数字转化成二进制看看。

- $4^0=1=(1)_2$
- $4^1=4=(100)_2$
- $4^2=16=(10000)_2$
- $4^3=64=(1000000)_2$

你会发现：在二进制下从 $4^n$ 变化到 $4^{n+1}$，只要在二进制下的数后面添上两个零即可。

那么比较是否会错过某一班火车，只要在二进制下实现比较即可。

如何实现比较？

最简单的方法就是用字符串比较。把手动产生的二进制下的 $4^n$ 数与题目给出的二进制数比较，如果比题目给的二进制数小，则这一班火车会被错过。

那么，梳理一下程序实现过程：

1. 把题目给出的二进制数以字符串形式读入；
2. 循环产生二进制下的 $4^n$ 数；
3. 将两个字符串比较大小，如果产生的数比题目给出的二进制数小，进行计数；
4. 如果产生的数比题目给出的二进制数大，则跳出循环；
5. 输出计数结果。

下面是代码：

```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str,ps="1";
	cin>>str;   //读入题目给的二进制数
	int s=0;   //计数器置0
	while(ps.size()<=str.size()){
		if(ps<str)   //比较并计数
			s++;
		ps=ps+"00";   //产生新数
	}
	cout<<s;   //输出计数结果
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：2)

[在窝的博客阅读](https://froldh.github.io/2019/08/21/OI/codeforcesPlan/R581/1204A/)  
[在窝的luogu博客阅读](https://www.luogu.org/blog/oldherd/solution-cf1204A)  
数据采用二进制表示,这方便我们知道该数字介于哪两个二的幂次数之间。例如对数字100000010, 我们数出该数字前导1之后共有8位数字,该数字,故而该数字应当介于$2^8$和$2^9$之间。即一个二进制k位数应当介于$2^{k-1}$与$2^{k}$之间。特殊地,若一个二进制k位数在前导1之后的数位全为0,该数等于$2^{k-1}$。这样一来,我们就很容易求出该数介于哪两个4的幂次数之间（在这里幂次数不一定为整数）。即$4^\frac{k-1}{2}$和$4^\frac{k}{2}$。同样,特殊地,若一个数在前导1之后的数为全部为0,那么该数字等于$4^\frac{k-1}{2}$     
那么，如果$\frac{k-1}{2}$为整数,对于等于$4^\frac{k-1}{2}$的数,应当有$\frac{k-1}{2}$班车开过。  
否则,对于任意一个介于$4^\frac{k-1}{2}$和$4^\frac{k}{2}$之间的数应当有$ \lfloor\frac{k-1}{2}\rfloor+1$班车开过。  
附代码(码风略卡常):  
```cpp
#include <cstdio>

using namespace std;

char buf[2000000], *p1 = buf, *p2 = buf;
inline char gc() { return p1==p2&&(p2=(p1=buf)+fread(buf,1,2000000,stdin), p1==p2)?EOF:*p1++; }

int main() {
	int n = 0;
	bool flag = true, f2 = false;
	char ch = gc();
	while(ch != '1' && ch != '0') 
		ch = gc();
	if(ch == '0') {
		putchar('0'); putchar('\n');
		return 0;		
	}
	while(ch == '0' || ch == '1') {
		ch = gc();
		if(flag && ch == '1') flag = false;
		++n;
		f2 = true;
	}
	if(f2) --n;
	if(!(n%2) && flag) n /= 2;
	else n = n / 2 + 1;
	printf("%d\n", n);
	return 0;
}

```

---

## 作者：So_noSlack (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF1204A)&[CF 链接](http://codeforces.com/problemset/problem/1204/A)

本篇题解为此题**较简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定一个二进制字符串 $S$，求这个二进制数包含 $4 ^ k$ 的个数。

特殊的：若 $4 ^ k = S$ **则此情况不计**。

## 思路

简单**思维题**。

通过**二进制**进行操作，首先二进制长度 $(1 \le len \le 100)$ 还是挺大的，如果想直接模拟的话，转为十进制是**不现实**的，所以只能通过~~二进制操作~~。

通过样例观察可发现，二进制无非就**两种情况**：

1. 长度为**偶数**；

2. 长度为**奇数**。

对于情况 $1$ 就很简单，**因为此题的根本是找二进制的奇数位的个数，所以对于长度为偶数的字符串**，直接输出长度除以 $2$ 即可。

对于情况 $2$，我们就需要判断**除最高位以外是否有其他位为 $1$ 的情况**，也非常简单，稍微模拟即可。

经过以上分类讨论，思路就很清晰了，下面是**代码实现**：

```cpp
#include<iostream>
using namespace std;

string str;

int main(){
    cin >> str; 
    int n = str.length(); // 记录字符串长度
    // 长度为偶数，情况 1
    if(!(n & 1)) {
        cout << n / 2;
        return 0; 
    }
    // 长度为奇数，情况 2
    // 模拟即可
    for(int i = 1; i < n; i ++)
        if(str[i] == '1'){
            cout << n / 2 + 1; // 除最高位有其他位为 1，正常输出
            return 0;
        }
    cout << n / 2; // 否则特判
    return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/118383270)

$$\text{The End!}$$

---

## 作者：hcl156 (赞：1)

## 解题说明:
题意是城市从第 $1$ 分钟开始，每到 $4^k$ 分钟的时候都有车离开， 现给出一个二进制串, 问在该时间到达城市, 已经离开了多少辆车。考虑四次方每多开一次, 就是在二进制串后去掉 $2$ 个 $0$，首先假设长度为 $\dfrac{len}{2}$ 。如果 $len$ 为偶数, 说明其正好为 $4^k$ 。 直接输出如果 $len$ 为奇数，说明其一定比 $4^k$ 还多一个，$+1$ 输出。

### 代码（目前最优解）
```cpp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int main(){
	char str[200];
	scanf("%s", str);
	int len = strlen(str);
	int m = 0;
	if (len % 2 == 1){
		for (int i = 1; i < strlen(str); i++){
			int t = str[i] - '0';
			m = m + t;
		}
	}
	if (m > 0){
		m = 1;
	}
	int ans = len / 2 + m;
	printf("%d\n", ans);
	return 0;
}
```





---

## 作者：Kira_GYT (赞：1)

题意：每第4^k（k为自然数）会发一辆车，问s分钟内发了多少辆车（不包括第s分钟）。

思路：  由于读入的为二进制数，很容易想到将发车时间4^k转化为2^2k。于是问题就转化为有多少个2^2k（k为自然数）小于s
		
现在分类讨论：

(1)当s=2^n时，

            即读入的二进制数只有开头为1。此时n等于二进制数长度-1。因为
            2^2k<2^n，所以2k<n,即k<n/2。所以0<=k<n/2。只要求出有多少
            个满足不等式的自然数即可。显然答案n为偶数时答案为n/2个，n
            为奇数时答案为（n-1）/2+1个。
            我们设二进制数长度为len，那么n=len-1。
            当n为偶数，即len为奇数时答案（len-1)/2。
            当n为奇数，即len为偶数时，答案为(len-1-1)/2+1=len/2。
            综上答案可以表示为len/2。
            
（2）当s≠2^n时，

		即读入的二进制数有多个1。设最高位为2^n，这里n也等于二进数长
            度-1此时情况和（1）相似不同的时2^n可以取到，所以2^2k<=2^n,
            所以2k<=n,得出0<=k<=n/2。当n为偶数时答案为n/2+1,当n为奇数
            时答案为（n-1）/2+1
  		还设二进制数长度为len，那么n=len-1
            当n为偶数，即len为奇数时，答案为（len-1）/2+1=（len+1）/2
        	当n为奇数，即len为偶数时，答案为（len-1-1）/2+1=len/2
            综上答案可以表示为（len+1）/2
            
实现：用字符串读入二进制数，然后判断一下1的个数，最后分类用len()表示答案即可

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k,len;
int main(){
	cin>>s;len=s.length();
	for(int i=0;i<len;i++){
		if(s[i]=='1')k++;
		if(k>1){
			printf("%d\n",(len+1)/2);
			return 0;
		}
	}
	printf("%d\n",len/2);
	return 0;
} 
```

        

---

## 作者：luguangxing (赞：1)

这题很简单可以找规律得出答案，答案是由二进制数的位数决定的规律如下:

```cpp
位数：1 2 3 4 5 6 7 8 9 10 

车数：1 1 2 2 3 3 4 4 5 5
```

根据这个规律我们可以推出思路来：我们先判断 $2$ 进制串中有几个 $1$（$ans$），之后判断 $ans$ 是否大于 $1$，如果是就直接套公式然后全部结束，之后等循环结束，如果还是不满足条件的话就套用另一个公式输出。

这里来开始求公式公式 $1$：我们先输入一个字符串（因为要求他的长度所以输入字符串），然后去求他的长度（位数），举个例子 $1$ 他就应该是：（位数 $+1$）$\div 2$。第二个公式就例如说 $2$ 他应该是：位数 $\div 2$。

得出公式就可以开始写程序了。

代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std; 
string s;
int ans=0;
int main()
{
    cin>>s;
    for(int i=s.size()-1;i>=0;i--)
    {
    	if(s[i]=='1')
    		ans++;
    	if(ans>1)
    	{
    		cout<<(s.size()+1)/2<<endl;
    		return 0;
		}
	}
	cout<<s.size()/2<<endl;
    return 0;
}
```

---

## 作者：TemplateClass (赞：0)

先上题目传送门，洛谷是[这个](https://www.luogu.com.cn/problem/CF1204A)，CodeForces 是[这个](https://codeforces.com/problemset/problem/1204/A)。

本题可以看到输入为二进制的形式，于是观察 $4^k$ 的二进制形式。

$(4^0)_{10}=(1)_{10}=(1)_{2}$

$(4^1)_{10}=(4)_{10}=(100)_{2}$

$(4^2)_{10}=(16)_{10}=(10000)_{2}$

$\cdot\cdot\cdot$

可以看出 $4^k$ 的二进制形式就是 $1$ 后面跟着 $2k$ 个 $0$，考虑用字符串 `string` 做，因为字符串可以直接比较之间的字典序。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int ans=0;
string s, k="1";
int main(){
	cin>>s;
	while(s>k && s.size()>=k.length())
		ans++, k+="00";
	cout<<ans;
}
```

---

## 作者：ink_ngm (赞：0)

分析一下题目：因为输入数据的第 $s$ 分钟使用的是二进制数，而火车每 $4^k$ 分钟开一辆。因此，我们可以将火车开来的时间转换为二进制数：$4^k=2^{2k}$ ，答案就可以转换为 $ans=\lfloor{n\over2}\rfloor$ 。


但是，如果到达的时间 $s$ 刚好等于 $4^k$ 时，将不会错过这趟火车，即为 $ans=\lfloor{n\over2}-1\rfloor$。


所以，
$$ ans=\left\{
\begin{aligned}
\lfloor{n\over2}\rfloor&\text{（当 $s$ 不等于 $4^k$ 时）}\\
\lfloor{n\over2}-1\rfloor&\text{（当 $s$ 等于 $4^k$ 时）} \\
\end{aligned}
\right.
$$


```
#include<bits/stdc++.h>
using namespace std;
string a;
int main(){
    register int n; 
    cin>>a;
    n=a.size();
    if (a[0]=='1'&&(n-1)%2==0){
        for (register int i=1;i<n;++i){
            if (a[i]=='1'){
                printf ("%d\n",(n+1)/2);
                return 0;
            }
        }
        printf ("%d\n",n/2);
        return 0;
    }
    printf ("%d\n",n/2);
    return 0;
}
```

---

## 作者：世末OIer (赞：0)

~~气死我了，CF尽然不让用__int128~~

---

于是直接利用Python自带的高精度，模拟就是了

连二进制都不用转

```python3
a=int(input())
t=1
ans=0
while t<a:
	ans=ans+1
	t=t*100    //相当于*4
print(ans)
```

---

## 作者：SilverStar (赞：0)

### 题意

给定一个数 $s$ ，试求满足 $ s < 4^{k-1}$ 的最大的 $k$ 值

**输入格式**

包含一个数 $s$ ，用二进制形式表示 $0≤s<2^{100}$ ，保证不存在前缀零

**输出格式**

一行一个整数，表示最大的 $k$

### 题解

题目要求求出 $\lceil \log_4s\rceil$ ，根据换底公式将其转化为 $\lceil \frac{\log_2s}{log_24}\rceil=\lceil \frac{\log_2s}{2}\rceil$ ，若 $s$ 为 $2$ 的整数次幂，则答案为 $\frac{len_s-1}{2}+1$ ，否则为 $\frac{len_s}{2}$

### $\text{Code}$
```cpp
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn = 105;

char s[maxn];
int n,flag;

int main(){
    scanf("%s",s);
    n = strlen(s);
    for(int i = 1; i<n; i++)
        if(s[i] == '1')
            flag = 1;
    if(flag) printf("%d",(n-1)>>1+1);
    else printf("%d",n>>1);
    return 0;
}
```

其实也可以使用直接 $\text{Python}$ 模拟


```python
s = input()
a = int(s, 2)
i = 1
ans = 0
while i < a :
    ans = ans+1
    i = i*4
print(ans)
```


---

## 作者：LevenKoko (赞：0)

### **多写几个串会发现其实这里只跟最高位的1有关**


------------


### **因为就算后面的位置上全部是1，假设总共有n位，也只有$2^{n-1}-1$,而第一位如果是1就直接有$2^{n-1}$,所以后面的位数其实是没用的**


------------

### 然后我们观察位数和答案的关系:
```
位数：1 2 3 4 5 6 7 8

答案：1 1 2 2 3 3 4 4
```


------------

### 是不是发现了什么
$$ans=\frac{n+1}{2}$$


------------

### 当然是有特例的,只有第一位是1，并且这个数转成十进制是4的倍数的话，就不是严格小于了，要特判掉

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-')f=-1;chr=getchar();}
	while(isdigit(chr)) {ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}const int M = 2e5+5;
char s[M];
int ans,sum,n;
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	if(n&1) ans=(n+1)/2;
	else ans=n/2;
	for(int i=1;i<=n;i++)sum+=s[i]-48;
	if(sum<=1)if(n&1)--ans;
	cout<<ans;
	return 0;
}

```

---

## 作者：Happy_Dream (赞：0)

首先看到这题，我的思路是把二进制转化为十进制，再把十进制转化为四进制，可是发现数据量太大，转换的话需要高精，我又懒得写，于是就想道了别的思路。。。

***

因为两个二进制位相当于一个四进制位，所以我们只需要把序列长度除以二，并向上取整即可，但这题有两个很坑的点：

1，如果刚好为（1，4，8，16，64）这些数的话呢，这个代码就会崩，原因是只有大于这个序列中的数才能被算作一个，否则不行，那样例一举例，100000000（2）是256，但是由于必须大于才可以，所以这个不算一个，但是程序会直接将（9/2）向上取整导致答案是五，所以应特判一下（从第二个字符一个一个判断，如果是一，那肯定不行就跳出去，是零就继续判断下去，如果全都为零那么就把答案减一）但是这有一个问题就是如果二进制串为10怎么办？很简单只要判一下它的长度模二是否等于一即可（其实更确切说是零的个数是否为偶数）

2，可能有二进制串为0的情况，那么需要再特判一下（我在打比赛的时候就是因为这个而被罚分了）。

***

AC CODE：
```cpp
#include <bits/stdc++.h>//万能头
using namespace std;//常规
int main()//主函数
{
	string a;//定义一个字符串用来存储二进制串
	cin>>a;//输入
	int sum=0,flag=0,la=a.length();//flag是标记，sum是用来记录
	if(la==1)//特判：如果长度为一则都为零
	{
		cout<<0;//输出零
		return 0;//直接结束
	}
	if(a[0]=='1'&&la%2==1)//特判如果刚好为序列中的数
	{
		for(int i=1;i<la;i++)//一位一位检查
		{
			if(a[i]!='0')//如果不是零
			flag=1;//标记一下
		}
		if(flag==0)//如果除第一位以外其他都为零
		sum=-1;//标记一下
	}
	cout<<ceil(la*1.0/2)+sum;//输出length除二+标记
	return 0;//结束
 } 
```

***
最后祝大家在CF的比赛中取得好成绩！

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1204A)

## 题目大意

已知圣彼得堡的车站会在第 $4^k(k\geq 0)$ 分钟开出新的一趟火车，已知 ```BowWow``` 团队将在第 $s(0\leq s\leq 2^{100})$  分钟时到达火车站，他们想知道自己错过了多少趟火车。

换句话说，在第 $s$ 分钟之前开出了多少趟火车。举个例子，当 $s=20$ 时，他们错过了第 $1、4$ 和 $16$ 分钟的火车。

现在只有你知道这个时间 $s$，请你求出他们错过了多少趟火车。

## 分析

火车每 $4^k$ 来一次。所以就只用把 $s$ 从二进制改四进制。数数有几位就可以了。

**注意：刚好来的不是错过，要特判。**

所以要判断除了首位还有没有 $1$，如果有，就要多算一次。

## 下面是 AC 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin>>s;
	int len=s.size();
		for(int i=len-1;i>0;i--)
		{
			if(s[i]=='1')
			{
				cout<<(len+1)/2; 
				return 0;
			} 
		} 
		cout<<len/2;
}
```


---

