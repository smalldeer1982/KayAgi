# Weather Tomorrow

## 题目描述

`Vasya`想出了一个他自己的天气预报方法。他知道最近$n$天每天的平均气温。假设每天的平均气温是个整数。

`Vasya`相信这$n$天每天的平均气温构成一个等差数列，在这个数列中，第一项是第一天的平均气温，第二项是第二天的平均气温，以此类推。那么第$n+1$天（也就是明天）的平均气温将是这个数列的第$n+1$项。如果这个数列前$n$项并没有他所想的那样是个等差数列，那么按`Vasya`的算法，第$n+1$天的气温将等于第$n$天的气温。

你需要根据`Vasya`的算法求出明天的平均气温。

## 样例 #1

### 输入

```
5
10 5 0 -5 -10
```

### 输出

```
-15
```

## 样例 #2

### 输入

```
4
1 1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
5 1 -5
```

### 输出

```
-5
```

## 样例 #4

### 输入

```
2
900 1000
```

### 输出

```
1100
```

# 题解

## 作者：Liweiang (赞：9)

**题目：**[CF847M Weather Tomorrow](https://www.luogu.com.cn/problem/CF847M)



------------

## 方法一：

按照题目模拟一遍，具体思路很多 dalao 已详细讲解，这里就不多说了。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000];
int main() 
{
	int n;
	cin>>n; 
	for(int i=1;i<=n;i++){
		cin>>a[i]; 
	}
	int t=a[2]-a[1];
	for(int i=3;i<=n;i++){
		if(a[i]-a[i-1]!=t){
			cout<<a[n]<<endl;
			return 0;
		}
	}
	cout<<a[n]+t<<endl;
	return 0;
}
```


------------

## 方法二：

边读入边判断，定义 $d$ （记录前两天温度的差）和变量 $t$ ，$t$ 需要初始化为第二天的温度，然后接下来每一天都加上 $d$ 。如果每次读入的 $a$ 都等于 $t$ ,说明是等差数列，则输出最后读入的数加上 $d$ 的值。反之则不是，则输出最后读入的数。

**代码如下：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() 
{
	int n,a,a1,a2,ai,an,d=0,t=0;
	bool flag=true;
	cin>>n;
	if(n==2){//需要特判n等于2的情况
		cin>>a1>>a2;
		cout<<a2+a2-a1<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++){
		cin>>a;
		if(i!=1&&i!=2)ai=a;//变量ai存储每次读入的a，不然数据可能会混乱（不知道为啥）
		if(i==1) a1=a; 
		if(i==2){
			a2=a;
			d=a2-a1;//记录前两天温度的差 
			t=a2;//初始化 
			continue;
		}
		if(i==n) an=a;//记录最后一天的温度
		t+=d;//t加上前两天温度的差 
		if(i!=1&&i!=2&&t!=ai){
			flag=false;
		}
		if(flag==false&&i==n){//不是等差数列，输出最后一个数 
			cout<<ai<<endl;
			return 0;
		}
	}
	cout<<an+d<<endl;
	return 0;
}
```


------------

**后话：** 本蒟蒻的代码或思路如有问题还请各位指出，谢谢大家！

---

## 作者：yangyuanxi44 (赞：2)

- 题目大意：

输入 $ n $ 个数，判断数列是否为等差数列，

如果是，按照公差输出下一个数。

否则，输出数列最后一个数。


------------
- 思路

1. 按照要求模拟一遍。

2. 如果是等差数列，公差可能有正负两种情况（正数，数增加，负数，数减小），若为负，加上公差，正数亦然。


------------

- 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];//数列
int main(){
	 int n;
	 cin>>n;
	 int pd=1,cz;//判断是否为等差数列，公差
	 for(int i=1 ; i<=n ; i++){
		 cin>>a[i];
		 if(i==2) cz=a[i]-a[i-1];//计算公差
		 if(i>2) 
		   if(a[i]-a[i-1]!=cz&&cz!=0) pd=0;//如果后来的数不符合公差且公差不为0，直接输出输出数列最后一个数
	 }
	 if(pd==1){
		 if(cz<0) cout<<a[n]+cz;//同上
		 else cout<<a[n]+cz;//同上
	 }
	 else cout<<a[n];
	 return 0;
}
```


------------

- 后话

谢谢管理员的审核，谢谢大家的观看，谢谢大家指正。

## 理解最重要！！！




---

## 作者：charleshe (赞：1)

纯模拟，详情见代码。

注：那么多大佬用了数组，蒟蒻深感佩服，但这题五个变量足矣。
```cpp
#include <iostream>
using namespace std;
int main(){
	int last,now,n,cha;//last保留上一次的结果，now为当次输入结果，n参见题目，cha为每两天的温度差（默认第二天减第一天，因此可能出现负数，对题目没有影响）。
	bool flag=true;//flag用来记录整个数列是否是等差数列，是true否false。
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>now;
		if(i>1 && flag){//i=1时last无实际值，可以跳过；数列非等差数列时亦可跳过，记录即可。
			if(i==2){//i=2时cha无实际值，赋值后跳出整个if。
				cha=now-last;
			}
			else{
				if(cha!=now-last){//判断当时是否还是等差数列。
					flag=false;
				}
			}
		}
		last=now;//保留这次的结果至last，now在下一次循环时直接重置。
	}
	if(flag) cout<<now+cha;//是等差数列则输出等差数列下一项，否则输出最后一天气温。
	else cout<<now;
	return 0;
}
//注：如果n=1则此TJ或许会被hack掉，但数据很弱，n至少为2，因此可过。
```


---

## 作者：__Hacheylight__ (赞：1)

#### CF847M Weather Tomorrow 题解

【题意】

给你一个数组，判断该数组构成的数列是不是等差数列

如果是，输出下一项是多少

如果不是，输出最后一行

【分析】

绿题？6666

首先n=2的一定是等差数列

等差数列满足每个$a[i]$和$a[i-1]$的差都为确定值$(i>=1)$

那么我们只要知道$a[2]-a[1]$是多少之后$for$循环判定就行了

$emm$送分题

【代码】

```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
    char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
    cout << x << endl ;
    exit(0) ;
}

void PRINT(string x) {
    cout << x << endl ;
    exit(0) ;
}

void douout(double x){
     printf("%lf\n", x + 0.0000000001) ;
}

int n ;
int a[N] ;

signed main(){
    scanf("%d", &n) ;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]) ;
    int x = a[2] - a[1] ;
    if (n == 2) cout << a[2] + x << endl ;
    else {
        for (int j = 3; j <= n; j++) if (a[j] - a[j - 1] != x) print(a[n]) ;
        print(a[n] + x) ;
    }
    
}

/*
写代码时请注意：
    1.是否要开Long Long？数组边界处理好了么？
    2.实数精度有没有处理？
    3.特殊情况处理好了么？
    4.做一些总比不做好。
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
*/

```

---

## 作者：zhoujingxuan (赞：0)



[题目传送门](https://www.luogu.com.cn/problem/CF847M)

## 题目大意
给你 $ n $ 个数，如果这 $ n $ 个数是等差数列，那么就输出这个数列的 $ n + 1 $ 项，否则就输出第 $ n $ 项。

## 思路
其实题目就是一道纯模拟，直接按照意思去做即可

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000010];
int main()
{   
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=3;i<=n;i++)
    {
    	if(a[i]-a[i-1]==a[i-1]-a[i-2]) continue; 
    	else {printf("%d",a[n]);return 0;}//如果不为等差数列，直接输出a[n]。 
    }
    printf("%d",a[n]*2-a[n-1]);//实际就是a[n]+公差(a[n]-a[n-1])。 
	return 0;
}
```
结束。

---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF847M)

一道难度不高的模拟题。


------------
### 分析

别看题目内容那么长就觉得复杂，仔细读题，就会发现这道题就是要我们求出等差数列的公差。如果这个数列并不是等差数列，那么输出 ```n``` 。

那如何判断是不是等差数列呢？可以创造个函数来判断等差数列：

```
bool Arithmetic_sequence(int a[],int n)
```


------------
### 函数部分

既然要判断这个数是不是等差数列，那我们可以先找两个数求出公差，再通过循环查找每组相邻的两个数是不是公差，一旦不等于，说明这个数列并不是等差数列。

```
bool Arithmetic_sequence(int a[],int n){
    int sum=a[1]-a[2];
    for(int i=1;i<=n-1;i++){
        if(a[i]-a[i+1]!=sum)return false;
    }
    return true;
}
```

接下来，只需要依题意判断就行了。如果是等差数列，输出这个数列的下一个数；否则输出 ```n``` 。


------------
### 完整 ```AC``` 代码

```
#include<iostream>
using namespace std;
int n,a[1010];
bool Arithmetic_sequence(int a[],int n){
    int sum=a[1]-a[2];
    for(int i=1;i<=n-1;i++){
        if(a[i]-a[i+1]!=sum)return false;
    }
    return true;
}
int main(){
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    if(Arithmetic_sequence(a,n)==true)cout << a[n]-(a[1]-a[2]) << endl;
    else cout << a[n] << endl;
    return 0;
}
```


---

## 作者：Endline (赞：0)

# CF847M 明天的天气

[题目传送门](https://www.luogu.com.cn/problem/CF847M)

根据题意，定义d为公差，有两种情况

$$
ans=
\left\{\begin{matrix}
  &a_n+d(\forall a_i-a_{i-1}=d) \\
  &a_n
\end{matrix}\right.
$$

于是我们可以写一个判断函数：

```cpp
bool weather()
{
    d=a[2]-a[1];						//d为公差
    for(int i=2;i<=n;i++)
        if(a[i]-a[i-1]!=d)return false;
    return true;
}
```

复杂度 $O(n)$ ，题目中 $2\le n\le100$ ，可以通过

$AC$ $Code:$

```cpp
#include<bits/stdc++.h>
#define re register
#define MAXN 102
using namespace std;
namespace FastIO
{
	char buf[1<<23],*p1,*p2;
	#ifdef ONLINE_JUDGE
	#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1==p2))?EOF:*p1++
	#else
	#define gc() getchar()
	#endif
	inline int read()
    {
        re int f=1,w=0;re char ch=gc();
        while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}
        while(ch>='0'&&ch<='9')w=w*10+ch-'0',ch=gc();
        return f*w;
    }
}
using FastIO::read;
int n,a[MAXN],d;
bool weather()
{
    d=a[2]-a[1];
    for(int i=2;i<=n;i++)
        if(a[i]-a[i-1]!=d)return false;
    return true;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    printf("%d\n",weather() ? a[n]+d:a[n]);
    system("pause");
    return 0;
}
```


---

## 作者：EuphoricStar (赞：0)

## 简化题意

给出一个数列的前 $n$ 项，如果该数列为等差数列则输出该等差数列的 $n + 1$ 项，否则输出该等差数列的第 $n$ 项

## 思路

暴力模拟。

定义 $diff$ 为该数列的公差，$flag$ 为该数列是否为等差数列，之后依次判断其他数之间的差值是否为 $diff$，如果不是则将 $flag$ 修改为 `false` 。

最后判断 $flag$ 为 `true` 还是 `false` 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, t[105], diff;
bool flag = 1;

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &t[i]);
    diff = t[1] - t[0];
    for (int i = 2; i < n; ++i) flag = flag && (t[i] - t[i - 1]) == diff;
    if (flag) printf("%d", t[n - 1] + diff);
    else printf("%d", t[n - 1]);
    return 0;
}
```


---

## 作者：Graphcity (赞：0)

## 思路

先用前两项相减求出公差 $d$ ，再在后面判断是否是一个等差数列即可。如果是，那么最后输出第 $n$ 项加上 $d$ 的值即可。不是的话，直接输出第 $n$ 项。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=100;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int t[Maxn+5];
int n,d,flag; //flag标记是否是等差数列

int main()
{
    n=read();
    for(register int i=1;i<=n;++i)
    {
        t[i]=read();
        if(i==2) d=t[i]-t[i-1]; //求公差
        else if(i>2)
        {
            if(flag) continue; //如果已经不是,直接跳过
            if(t[i]-t[i-1]!=d) //判断目前是否还是等差数列
                flag=1,d=0;
        }
    }
    printf("%d",t[n]+d);
    return 0;
}
```

---

## 作者：Node_Edge (赞：0)

**题目大意：**

输入 $n$ 个数，判断数列是否为等差数列，

如果是，按照公差输出下一个数。

否则，输出数列最后一个数。

**个人思路：**

先求公差，判断是否是等差数列。如果是，那么最后输出末项加上公差（即 $n+1$ 项）。不是，输出末项。

**AC Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005];
int main() {
	int n;
	cin>>n; 
	for(int i=1;i<=n;i++){
		cin>>a[i]; 
	}
	int x=a[2]-a[1];//公差 
	for(int i=3;i<=n;i++){
		if(a[i]-a[i-1]!=x){//如果不是等差数列 
			cout<<a[n]<<endl;
			return 0;//结束程序 
		}
	}
	cout<<a[n]+x<<endl;//输出 n+1 项
	return 0;
}
```


---

## 作者：三点水一个各 (赞：0)

求出等差数列的公差，之后若两项之差不等于之前的公差，直接输出 $a_n$，

如果整个for跑下来没问题，输出$a_n+$公差。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],d;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	d=a[2]-a[1];   //公差
	for(int i=3;i<=n;i++)  //判断是不是等差数列
	  if(a[i]-a[i-1]!=d) {printf("%d",a[n]);return 0;}
	printf("%d",a[n]+d);  //是等差数列，且包含了n=2的情况
   return 0;
}
```

---

