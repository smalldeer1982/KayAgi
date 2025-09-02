# Ternary Logic

## 题目描述

Little Petya very much likes computers. Recently he has received a new "Ternatron IV" as a gift from his mother. Unlike other modern computers, "Ternatron IV" operates with ternary and not binary logic. Petya immediately wondered how the $ xor $ operation is performed on this computer (and whether there is anything like it).

It turned out that the operation does exist (however, it is called $ tor $ ) and it works like this. Suppose that we need to calculate the value of the expression $ a\ tor\ b $ . Both numbers $ a $ and $ b $ are written in the ternary notation one under the other one ( $ b $ under $ a $ ). If they have a different number of digits, then leading zeroes are added to the shorter number until the lengths are the same. Then the numbers are summed together digit by digit. The result of summing each two digits is calculated modulo 3. Note that there is no carry between digits (i. e. during this operation the digits aren't transferred). For example: $ 14_{10}\ tor\ 50_{10}=0112_{3}\ tor\ 1212_{3}=1021_{3}=34_{10} $ .

Petya wrote numbers $ a $ and $ c $ on a piece of paper. Help him find such number $ b $ , that $ a\ tor\ b=c $ . If there are several such numbers, print the smallest one.

## 样例 #1

### 输入

```
14 34
```

### 输出

```
50
```

## 样例 #2

### 输入

```
50 34
```

### 输出

```
14
```

## 样例 #3

### 输入

```
387420489 225159023
```

### 输出

```
1000000001
```

## 样例 #4

### 输入

```
5 5
```

### 输出

```
0
```

# 题解

## 作者：ikunTLE (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF136B)

### 思路

要使 $b$ 最小，就要使 $b$ 在三进制下每一位最小。因此列出式子，$b_i=(c_i-a_i+3)\mod3$（$a_i,b_i,c_i$ 分别表示 $a,b,c$ 的三进制从右数的第 $i$ 位)。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,p=1;
int main(){
	scanf("%d%d",&a,&c);
	while(a||c){
		b+=(c%3-a%3+3)%3*p;
		a/=3,c/=3,p*=3;
	}
	printf("%d",b);
	return 0;
}
```

---

## 作者：miraculously (赞：4)

分析：

这题用到贪心的思想，要让 $b$ 最小，就要让三进制下 $b$ 的每一位都最小，可以看出，$b$ 每一位的最小值即 $(c \bmod 3-a \bmod 3+3) \bmod 3$，最后把 $b$ 每一位转化成十进制相加就可以了。

代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a,b=0,c,cnt=0;//cnt记录已经转化到第几位了
	scanf("%d%d",&a,&c);
	while(a!=0||c!=0)
	{
		b+=(c%3-a%3+3)%3*pow(3,cnt);//算出每一位最小值，并把三进制转化成十进制
		a/=3;
		c/=3;
		cnt++;
	}
	printf("%d",b);
}
```


---

## 作者：lutaoquan2012 (赞：3)

## 思路:
我们这道题可以把 $a$ 和 $c$ 转换为三进制，按照枚举 $a$ 和 $c$ 的三进制下每一位，推出 $b$ 的值，最后再把三进制下的 $b$ 转换为十进制。

如果按照前面的这个思路，我们会得到 $0$ 分的好成绩，因为这是 CF 的题目，所以没有部分分。

我们按照样例 $3$ 能够知道原因，$a$ 转换为三进制是 $1000000000000000000$，而 $c$ 转换为三进制是 $120200200021010002$。如果按照前面的话，是不可能对的，因为 $a$ 比 $c$ 大。我们可以看到这个是不进位的，所以我们只能用 $b$ 来抵消 $a$ 才能得到 $c$。我们可以枚举 $a$ 三进制下每一位，算出 $b$ 的固定值。
## 代码：
```cpp
//
// Created by 55062 on 2024/2/19.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll a,b,x[110],y[110],X,Y,z[110],Z,xx[110],yy[110],ans,mi=1;
void f(ll yy,ll r){
    if(yy>=r) f(yy/r,r);
    xx[++X]=yy%r;
}void d(ll xx,ll r){
    if(xx>=r) d(xx/r,r);
    yy[++Y]=xx%r;
}
int main() {
    cin>>a>>b;
    f(a,3);//把a和c转成3进制
    d(b,3);
    for(int i=1;i<=X;i++) x[X-i+1]=xx[i];//倒过来，方便一会儿操作
    for(int i=1;i<=Y;i++) y[Y-i+1]=yy[i];
    Z=Y;//b的长度最多是Y，但也可能不是Y，后面删
    for(int i=1;i<=Y;i++){//枚举每一位
        if(x[i]==0&&y[i]==0) z[i]=0;//枚举三进制下每一种可能
        if(x[i]==0&&y[i]==1) z[i]=1;
        if(x[i]==0&&y[i]==2) z[i]=2;
        if(x[i]==1&&y[i]==0) z[i]=2;
        if(x[i]==1&&y[i]==1) z[i]=0;
        if(x[i]==1&&y[i]==2) z[i]=1;
        if(x[i]==2&&y[i]==0) z[i]=1;
        if(x[i]==2&&y[i]==1) z[i]=2;
        if(x[i]==2&&y[i]==2) z[i]=0;
    }if(X>Y){//按照样例3，我们需要用b把c给抵消没
        for(int i=Y+1;i<=X;i++){
            if(x[i]==1) z[i]=2;
            if(x[i]==2) z[i]=1;
            if(x[i]==0) z[i]=0;
        }Z=X;
    }
    while(z[Z]==0) Z--;//因为是反过来的，所以看前面的
    for(int i=1;i<=Z;i++){
        ans+=z[i]*mi;
        mi*=3;
    }cout<<ans;
    return 0;
}
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
这显然是一道非常简单的模拟题。
## 2. 题目做法
我们先将 $a$ 和 $c$ 转化为三进制数，分别用两个数组倒着存下来。  
然后，对于这两个数组，我们可以通过它们逐位计算 $b$ 的值。若当前位 $a$ 小于 $c$，则当前位用 $c$ 减去 $a$ 得到 $b$；若当前位 $a$ 大于 $c$，则当前位用 $3$ 减去 $a$ 加上 $c$ 得到 $b$。  
最后，逐位统计答案。
## 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int x,y,wa,wc,n;
long long t,ans;
int a[N],b[N],c[N];
int main()
{
	x=read(),y=read();
	t=1;
	while(t<=x)
		t*=3,wa++;
	t/=3;
	for(int i=wa;i>=1;i--)
		a[i]=x/t,x%=t,t/=3;
	t=1;
	while(t<=y)
		t*=3,wc++;
	t/=3;
	for(int i=wc;i>=1;i--)
		c[i]=y/t,y%=t,t/=3;
	n=max(wa,wc);
	for(int i=1;i<=n;i++)
	{
		if(a[i]<c[i])
		{
			b[i]=c[i]-a[i];
		}
		else if(a[i]>c[i])
		{
			b[i]=3-a[i]+c[i];
		}
	}
	t=1;
	for(int i=1;i<=n;i++)
		ans+=t*b[i],t*=3;
	printf("%lld",ans); 
	return 0;
}
```

---

## 作者：hy8z (赞：1)

[题目](https://www.luogu.com.cn/problem/CF136B)

这题可以考虑两个思路。
- 可以将 `a` 和 `c` 都转换成三进制，再由每位进行不退位减法得出 `b` 的每一位（没有亲自试过，看题解区有大佬说会爆零）。

- 可以用贪心的思路，用一个 `while` 循环依次推出 `a` 和 `c` 在三进制下的末位，在满足题意的情况下使计算出 `b` 的末位最大，再根据三进制的每一位对应的十进制的数值叠加计算出答案的十进制值。

我们拿样例 `2` 进行一下笔算。


可以看到，（从右往左数）第 `1` 位本来要向第 `2` 位借 `1`，但由于使不退位，所以第 `1` 位加 `3` 而第 `2` 位不变。根据这个思路进行模拟就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,c;
	cin>>a>>c;
	int cnt=0,ans=0;
	//cnt用来存储目前是三进制的第几位，ans存储答案
	while(a||c)//当a或者c等于0时结束
	{
		int at=a%3,ct=c%3,bt;
		//at、bt和ct分别代表a、b和c在三进制下的末位
		if(at>ct)bt=ct+3-at;
		else bt=ct-at;//计算在进行不进位加法时满足当前at和ct的bt
		ans=ans+bt*pow(3,cnt);
		//答案为十进制数，用 pow 函数来计算幂
		cnt++;
		a/=3;
		c/=3;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Rookie_t (赞：1)

这题要使用贪心和进制转化来解决。

要使最终答案的 $b$ 最小，就要使这个 $b$ 在三进制下每一位都最小。

解法就是算出 $b$ 每一位的最小值，再把 $b$ 每一位都转化成十进制然后相加。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a,b,c,ans;
int main(){
	ios::sync_with_stdio(0);
	cin>>a>>c; 
	while(a != 0 || c != 0){
		b += (c%3-a%3+3)%3*pow(3,ans);
		c /= 3;
		ans++;
	}
	cout<<b;
}
``` 

---

## 作者：__O_v_O__ (赞：0)

要让 $b$ 最小，显然要 $b$ 的每一位都最小。所以我们枚举 $a$ 和 $c$ 三进制的每一位，计算 $b$ 当前位的最小值。

假设当前位 $a$ 和 $c$ 的值为 $a1$ 和 $c1$，则有两种情况：

- 若 $a1\le c1$，$b$ 这一位的最小值为 $c1-a1$。 

- 若 $a1>c1$，则需要不进位这个性质，手推可得 $b$ 这一位的最小值为 $c1+3-a1$。

所以我们现在就算出了 $b$ 每一位的最小值，接着还原出 $b$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,cn;
int main(){
	ios::sync_with_stdio(0),cin>>a>>c;
	while(a!=0||c!=0){//枚举a,c的每一位 
		int nw=0,c1=c%3,a1=a%3;//c1,a1表示c,a三进制当前位的值 
		if(c1>=a1)nw=c1-a1;
		else nw=c1+3-a1;//计算 
		b+=nw*pow(3,cn);//把b的当前位加上nw 
		a/=3,c/=3,cn++;//枚举下一位 
	}cout<<b;
	return 0;
}
```

---

## 作者：__DayLight__ (赞：0)

## 思路
这道题的关键在于理解 ternary 运算 $tor$ 的特性。

因为没有进位，所以每一位的计算是**独立**的。

要找到最小的 $b$，就要从最低位开始逐位确定 $b$ 中的数字。

为了确保逐位计算的进行，就需要保证 $a$ 与 $c$ 转为三进制后的位数相同。

怎么做呢？当然在最高位**补零**了。

当 $a_{(3)}$ 的位数与 $c_{(3)}$ 的位数不同时，在位数少的数的最高位补上对应数量的 $0$。

要注意的是：$a$ 与 $c$ 的大小关系并未确定，比如样例 #3。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string a3,b3,c3;
int a,c;
string turn(int x)//10进制转3进制。
{
	string ans;
	if(x==0)ans="0";
	while(x)
	{
		ans=char(x%3+'0')+ans;
		x/=3;
	}
	return ans;
}
int back(string s)//3进制转10进制。
{
	int ans=0;
	for(int i=s.size()-1,j=0; i>=0; i--,j++)
		ans+=pow(3,j)*(s[i]-'0');
	return ans;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>a>>c;
    a3=turn(a),c3=turn(c);
    //补零
    while(c3.size()>a3.size())
		a3='0'+a3;
    while(c3.size()<a3.size())
    	c3='0'+c3;
    //逐位计算 b。 
    for(int i=0; i<a3.size(); i++)
    {
    	if(c3[i]<a3[i])c3[i]+=3;//不够减当然要借 1，但因为每一位是独立计算的，所以不会互相影响。
		b3=b3+char(c3[i]-a3[i]+'0');
    }
    cout<<back(b3);
	return 0;
}
```

---

## 作者：NEKO_Daze (赞：0)

跟楼上楼下几位的解法差不多，水一发题解。

洛谷题目传送门：[CF136B](https://www.luogu.com.cn/problem/CF136B)   | |  CF原题传送门：[136B](https://codeforces.com/contest/1986/problem/B)

#### 简要题意

定义运算 $a$ tor $b = c$ 为 $a,b$ 在三进制下做不进位加法运算所得的答案的十进制形式。给出整数 $a$ 和 $c$，求出符合 $a$ tor $b = c$ 的 $b$，并最小化 $b$ 后输出。
#### 思路

$a,b$ 都是以三进制形式进行加法运算的，所以既然要最小化 $b$，又要在保证等式成立的情况下，我们反推出 $b$ 的表达式。

设 $a_i$ 和 $c_i$ 分别是 $a$ 和 $c$ 在三进制表示下的第 $i$ 位（从最低位开始计数，且 $i$ 从 $0$ 开始）。目标是找到 $b_i$，使得 $(a_i + b_i) \bmod 3 = c_i$。

对每一位计算差值 $c_i-a_i$，这里我们要分类讨论：

* 对于 $a_i \leq c_i$ 时，差值为 $(c_i-a_i)\bmod 3$；
* 对于 $a_i > c_i $ 时，差值为 $(c_i-a_i+3)\bmod 3$（因为 $c_i < a_i$ 而导致 $c_i - a_i < 0$ 的情况出现，所以进行借位操作）。

容易发现其实 $(c_i-a_i+3)\bmod 3$ 也适用于 $a_i \leq c_i$ 的情况，而且根据模运算的性质可以化简为 $(c_i \bmod 3 - a_i \bmod 3 + 3) \bmod 3$。所以只需要对于 $b$ 每一位赋值为 $(c_i \bmod 3 - a_i \bmod 3 + 3) \bmod 3$ 即可最小化 $b$ 的每一位，最后转换为 $10$ 进制输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c,t; //t为b的位数统计
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);	
    cin>>a>>c; 
    while(a || c){
    	b += (c%3-a%3+3)%3*t; //同时计算差值和转十进制
    	a /= 3, c /= 3, t *= 3;
    }
    cout<<b;
    return 0;
}
```

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF136B)  
[CodeForces 传送门](https://codeforces.com/problemset/problem/136/B)

当然首先将 $a,c$ 转换为三进制，令 $sa=(a)_3,sc=(c)_3$。进制转换可以套模板[洛谷 B3619](https://www.luogu.com.cn/problem/B3619)。

其次学习题面，将 $sa,sc$ 的位数补齐，即补全前导零。

现在开始求最小的 $(b)_3$。注意到 $\operatorname{tor}$ 运算为**不进位**加法，那么可以通过反推实现“减法”。  
具体地，设 $(b)_3$ 的第 $i$ 位为 $x_i$，那么得 $(sa_i+x_i)\bmod3=sc_i$。简单思考一下可得 $x_i=(sc_i+3-sa_i)\bmod3$（这里 $+3$ 是为了防止 $sc_i<sa_i$ 使得 $x_i$ 为负数）。那么将 $x_i$ 组合起来就可以得到最小的 $(b)_3$。最后再做一遍进制转换（[洛谷 B3620](https://www.luogu.com.cn/problem/B3620)），将 $(b)_3$ 转换成十进制即为答案。

```cpp
string jz="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string sa="",sc="";
inline string f(int n,string &s)
{
	if(n/3==0)
	{
		return s+=its(n);
	}
	return f(n/3,s),s+=jz[n%3];
}
inline void qdl(string &a,string &b)
{
	while(a.size()<b.size()) a='0'+a;
	while(b.size()<a.size()) b='0'+b;
}
signed main()
{
	int a,c;
	rd(a,c),sa=f(a,sa),sc=f(c,sc);
	qdl(sa,sc);
	string sb="";
	for(int i=0;i<sa.size();i++)
	{
		sb+=its((sc[i]+3-sa[i])%3);
	}
	int b=0;
	for(int i=0;i<sa.size();i++)
	{
		b+=(sb[i]-'0')*qp(3,sa.size()-i-1);
	}
	wtl(b);
	return 0;
}
```

---

## 作者：WoodReal12 (赞：0)

## 题目描述
这道题目要求我们找到一个整数 $b$，使得对于给定的整数 $a$ 和 $c$，满足 $a\ tor\  b = c$。其中，$tor$ 运算定义为将 $a$ 和 $b$ 分别转换为三进制并做不进位加法，然后将结果转换回十进制。

## 思路
按题意模拟即可，一共分三步：

1. 将问题转化为三进制的不进位加法

	注意：对应的三进制表示可能长度不同，**需要补齐到相同长度**。
    
1. 求解 $b$ 的所有可能值

	对于每一位，根据 $a$ 和 $c$ 的对应位，确定 $b$ 的可能取值。
    
	如果某位上 $a$ 的三进制位为 $x$，$c$ 的三进制位为 $y$，那么 $b$ 的这一位就是 $(y - x + 3) % 3$。
    
1. 确定最小的 $b$

	从高位到低位依次确定 $b$ 的每一位，使得 $b$ 尽可能地小。
    
	如果某一位确定了 $b$ 的值，就需要保证后面的位尽可能小，以确保整体 $b$ 最小。
    
本题按照这三步就可以愉快地 AC。

## 代码
```cpp
#include <iostream>
#include <string>
using namespace std;
string solve(int a, int c) {
    string at, ct;
    while (a > 0) {
        at = to_string(a % 3) + at;
        a /= 3;
    }
    while (c > 0) {
        ct = to_string(c % 3) + ct;
        c /= 3;
    }
    int mx = max(at.length(), ct.length());
    while (at.length() < mx) at = "0" + at;
    while (ct.length() < mx) ct = "0" + ct;
    string bt = "";
    for (int i = 0; i < mx; ++i) {
        int x = at[i] - '0';
        int y = ct[i] - '0';
        int b_10 = (y - x + 3) % 3;
        bt += to_string(b_10);
    }
    int b = 0;
    int p = 1;
    for (int i = bt.length() - 1; i >= 0; --i) {
        b += (bt[i] - '0') * p;
        p *= 3;
    }
    return to_string(b);
}
int main() {
    int a, c;
    cin >> a >> c;
    cout << solve(a, c) << endl;
    return 0;
}
```

---

## 作者：KyleShen1213 (赞：0)

## 题目思路
用贪心。要使得 $b$ 最小，就要使 $b$ 的每一位最小，由于三进制下 $a$ 和 $c$ 每一位加起来最大值最大不会超过 $4$，所以 $b$ 每一位的最大值就是 $(c \bmod 3−a \bmod 3+3) \bmod 3$。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,cnt=0;//cnt初始化为0 
int main()
{
	cin>>a>>c; 
	while(a||c)//循环 
	{
		b+=(c%3-a%3+3)%3*pow(3,cnt);//b最小值 
		a/=3,c/=3;//a，c除以3 
		cnt++;//cnt记录位数 
	}
	cout<<b<<endl;
	return 0;
}
```

---

## 作者：xiaoyang111 (赞：0)

### 前言

[题目传送门。](https://www.luogu.com.cn/problem/CF136B)

不进位加法的意思就是把这两个数加起来，对于中间进位直接舍去。

### 题解

#### 思路

这个模拟一下就可以了。

先把 $a$ 和 $c$ 的三进制表示法求出来，然后随便顺序扫。然后我们分类讨论。

下面简写 $a$ 的第 $i$ 位是 $a_i$，$c$ 的第 $i$ 位是 $c_i$。

扫到了第 $i$ 位，如果 $a_i$ 和 $c_i$ 位一样，就说明不用变。

如果 $a_i$ 位和 $c_i$ 位小，就说明要加上一个数，使得最终结果第 $i$ 位比 $a_i$ 大。这个数显然是 $c_i-a_i$。

如果 $a_i$ 位和 $c_i$ 位大，就说明需要加上一个数，使得最终结果第 $i$ 位比 $a_i$ 小。这种情况就说明要用到不进位加法了，让他加上一个数，产生进位，又把进位舍去了。显然是 $c_i+3-a_i$。

#### 代码

代码见下，可以过。

```cpp
#include <iostream>
using namespace std;
int main(){
	int a,c;
	cin >> a >> c;
	int ans=0;
	int t1,t2,pw=1;
	for (int i=0;i<=19;++i){
		t1=a/pw%3;
		t2=c/pw%3;
		if (t1<t2){
			ans+=pw*(t2-t1);
		}else if (t1>t2){
			ans+=pw*(t2+3-t1);
		}
		pw*=3;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：zhanghx0219 (赞：0)

先理解一下题意：给你 $2$ 个数 $a$ 、$c$ ，让你找出一个数 $b$ ，满足在三进制下 $a+b=c$ ，且最小。

这道题非常的简单，先把 $a$ 和 $c$ 转成 $3$ 进制，再求个差，再把差值转成 $10$ 进制就是答案。

对于一个数转换成三进制，我们采用取余法，每次对三取余，把每次区域的结果翻转一下即可。

将三进制转换成十进制，我们只需要按权求和即可。

下面附上代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
const int N = 1e5+39+7;
int a[N],len1,len2,b[N],c[N],n,m,k;
ll quickPow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=(ans*a);
		a=a*a;
		b>>=1; 
	}
	return ans;
}
int main(){
	n=read();m=read();
	while(n){
		a[++len1]=n%3;
		n/=3;
	}
	while(m){
		c[++len2]=m%3;
		m/=3;
	}
	ll len3=max(len1,len2);
	for(int i=1;i<=len3;i++)b[i]=(c[i]-a[i]+3)%3;
	for(int i=1;i<=len3;i++)k+=b[i]*quickPow(3,i-1);
	cout<<k;
	return 0;
}
```


---

## 作者：L_zaa_L (赞：0)

## 分析
可以直接把 $A$ 和 $C$ 分成两个三进制序列，然后 $B$ 的三进制序列就可以通过 $A$ 和 $C$ 的每一位推算出答案，因为不进位，所以每个数位选的数不会影响其他位，最后将 $B$ 的三进制序列换成十进制即可。

## Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){//快读
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
int A,B,C;
int a[1005];
int b[1005];
int c[1005];
int cnta,cntc;
signed main(){
	A=read(),C=read();
	while(A!=0){
		a[++cnta]=A%3;
		A/=3; 
	}
	while(C!=0){
		c[++cntc]=C%3;
		C/=3;
	}//将 A 和 C 拆成两个三进制序列
	for(int i=1;i<=max(cnta,cntc);i++){
		b[i]=(c[i]+3-a[i])%3;
	}//找到最小的 b
	for(int i=max(cnta,cntc);i>=1;i--){
		B=B*3+b[i];
	}//换算成十进制
	cout<<B;
	return 0;
}
```

---

## 作者：Melo_DDD (赞：0)

前置芝士：进制及其转换，不是很明白的请移步[这里](https://oi-wiki.org/math/base/)。

# 题目大意

给定一个加数和和，求它们在 $3$ 进制下的差的十进制最大值，减法无借位。

# 题目实现

远古 CF 题。

根据进制转化的方法，如果想让 $b$ 的十进制尽可能小，那么他在三进制下每一位也应该尽可能小。

说是贪心，其实你贪不贪无所谓，直接计算就好了。

不难发现对于第 $i$ 位，$(b_{i\ \min})_3=((c_i)_3-(a_i)_3+3)\bmod3$。

注意进制转化。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std ;
inline int read () {
	int x = 0 ,f = 1 ;
	char ch = getchar () ;
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			f = -1 ;
		}
		ch = getchar () ;
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0' ;
		ch = getchar () ;
	}
	return x * f ;
}
inline int pow (int base ,int p) {
	int y = 1 ;
	while (p --) {
		y *= base ;
	}
	return y ;
} 
int b ,ans ;
int main () {
	int a = read () ,c = read () ;
	while (a || c) {
		b += (c % 3 - a % 3 + 3) % 3 * pow (3 ,ans ++) ;
		a /= 3 ;
		c /= 3 ;  
	}
	cout << b << '\n' ;
	return 0 ;
}
```

---

## 作者：mahaoming (赞：0)

# CF136B Ternary Logic 题解

### 思路
贪心，考虑要让 $b$ 最小，就是要让三进制下 $b$ 的每一位都最小。

可以看出，$b$ 每一位的最小值即 $c%3−a%3$ ,再把 $b$ 每一位转化成十进制即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int s=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while('0'<=c&&c<='9')s=s*10+c-'0',c=getchar();
	return s;
}
int a,b,c,s=1;
int main(){
	a=read(),c=read();
	while(a||c)b+=(c%3-a%3+3)%3*s,a/=3,c/=3,s*=3;
	cout<<b;
	return 0;
}

```


---

## 作者：a18981826590 (赞：0)

# [Ternary Logic](https://www.luogu.com.cn/problem/CF136B)
## 解题思路
这道题运用贪心的思想，要让 $b$ 最小，就要让三进制下的 $b$ 的每一位最小。$b$ 在三进制下每一位 $b_{i}$ 的最小值即为 $(c_{i} \bmod 3-a_{i} \bmod 3+3) \bmod 3$，再转换为十进制即可。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d=1;
int main(){
	cin>>a>>c;
	while(a||c){
		b+=(c%3-a%3+3)%3*d;
		a/=3;
		c/=3;
		d*=3;
	}
	cout<<b;
	return 0;
}
```

---

