# [PA 2014] Iloczyn

## 题目背景

译自 PA 2014 Trial Round.

## 题目描述

斐波那契数列的定义为：
 
- $k=0$ 或 $1$ 时， $F_k=k$；

- $k>1$ 时，$F_k=F_{k-1}+F_{k-2}$。

数列的开头几项为 $0,1,1,2,3,5,8,13,21,34,55,…$。

你的任务是判断给定的数字能否被表示成两个斐波那契数的乘积。

## 说明/提示

对于 $100\%$ 的数据，$1\le T\le 10$，$0\le n_i\le 10^9$。

## 样例 #1

### 输入

```
5
5
4
12
11
10```

### 输出

```
TAK
TAK
NIE
NIE
TAK```

# 题解

## 作者：快斗游鹿 (赞：7)

## 题意

共 $T$ 组数据，对于每组数据，判断 $n$ 是否为两个斐波那契数的乘积。

## 思路

观察数据 $n_i\le10^9$，设 $n_i$ 能由 $x_1$，$x_2$ 两个斐波那契数相乘得到，则 $x1,x2\le10^9$。而经实测，斐波那契数第 $50$ 位为 $12586269025$，所以只需要先预处理出前 $50$ 位的斐波那契数，再一次枚举每种情况即可得出答案。总时间复杂度大概是 $O(T\times50^2)$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
long long T;
long long feb[100];
int main(){
	scanf("%lld",&T);
	feb[1]=1;
	for(long long i=2;i<=50;i++){//预处理出前50位
		feb[i]=feb[i-1]+feb[i-2];
	}
	for(long long kkk=1;kkk<=T;kkk++){//输入T组数据
		long long n;scanf("%lld",&n);bool flag=0;
		for(long long i=0;i<=50;i++){//枚举每种情况
			for(int j=0;j<=50;j++){
				if(feb[i]*feb[j]==n){
					cout<<"TAK"<<endl;
					flag=1; 
					break;
				}
			}
			if(flag==1)break;
		}
		if(!flag){
			cout<<"NIE"<<endl;
		}
	}
	return 0;
}

```


---

## 作者：风之影音 (赞：4)

这是本蒟蒻的第9篇题解。~~（从弱鸡上升到了蒟蒻）~~

还是那句话，如有雷同，纯属巧合。

这道题是一道非常“普通”的题，整体思路：先求出斐波那契数列，再判断符不符合条件。~~（貌似只需要知道斐波那契的求法和多层循环就可以做出来的样子）~~

~~好像事实就是这样~~↑

看了楼上（有可能是楼下）的题解，啥也没看懂。本来循环枚举完全可以解决的，干嘛那么复杂呢？可能我的水平只能做水题，不会其他难的方法，~~(反正我也没学过，难的方法我也看不懂，更别提做了。）~~ 那我就为蒟蒻们提供水题的优质简单方法的题解吧。

好了，不多说了，上代码。
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
long long a[50]={0,1,1};//斐波那契开头（如果不开longlong...）
int b[10001];//输入的数组
int main(){
  for(int i=2;i<=50;i++){//求斐波那契数列
	a[i]=a[i-1]+a[i-2];
  }
    long long n;//输入个数
    bool kkksc03=false;//判断是否符合标准 PS：膜拜kkk
    cin>>n;//输入n
    for(int i=1;i<=n;i++){//输入数组
    	cin>>b[i];
	}
	for(int i=1;i<=n;i++){//第一层循环是b数组的
    	for(int j=0;j<=46;j++){//第二三层是判断的
    		for(int k=0;k<=46;k++){
			if(a[k]*a[j]==b[i])//如果符合标准
				kkksc03=true;//则为真
				continue;//跳出循环
			}
		}
		if(kkksc03)//如果是真
			cout<<"TAK"<<endl;//输出TAK
		else//如果是假
			cout<<"NIE"<<endl;//输出NIE
		kkksc03=false;//重新恢复false状态
	}//结束循环
	return 0;//好习惯
}//完美结束
```

我所有的题解，都是很基础的方法，~~（因为难的我不会）~~，所以...

# [蒟蒻们，可以考虑往这看！](https://www.luogu.com.cn/blog/fengzhiyy/)

好了，详细内容看代码，做题解不易，希望给个赞。QAQ

本题解到此结束，我先溜啦溜啦~~~

PS：管理员大人求过orz

---

## 作者：ShanCreeperPro (赞：2)

## P5993 [PA2014]Iloczyn 題解

前言：

$\texttt{FOI T1}$，不亏是一场比赛全是原题的 $\texttt{FOI}$！

***

这题考场上写了个暴力代码，结果忘记判断两个完全一样的斐波那契数相乘的情况。

寄。

***

我们可以自己写出所有的斐波那契数列。

递推式为：$f_i=f_{i-1}+f_{i-2} (i>2)$。

所以我们可以这么写：

```cpp
f[1]=1;
f[2]=1;
printf("%lld,%lld",f[1],f[2]);
for(int i=3;i<=1000000000;i++){
    f[i]=f[i-1]+f[i-2];
    printf("%lld",f[i]);
}
```

由于每个斐波那契数的差会随着大小而越来越大，所以最后小于 $10^9$ 的斐波那契数不会很多。

接着，我们可以定义两个数组 $a$ 和 $b$，在里面放入我们暴力程序生成的结果：

```cpp
int a[MAXX]={1,1,2,3,5,8,13,21,...};
int b[MAXX]={1,1,2,3,5,8,13,21,...};
```

接着读入每个数据，并对每个数据进行枚举，如果发现乘积相同，结束并输出：

```cpp
for(int i=1;i<=MAXX;i++){
	fore(int j=1;j<=MAXX;j++){
    	if(c==a[i]*b[j]){
        	puts("TAK");
        } else puts("NIE");
    }
}
```

如果你闲的无聊，可以加上一些特判。



---

## 作者：xieyuhao2022 (赞：2)

# 题目大意
给定 $T$ 个数，问这些数是否能用两个斐波那契数的乘积表示。

# 算法分析
观察数据范围，我们发现 $n$ 最大在 $10^{9}$，简单估算一下，这个数在斐波那契数列的五十位以内。

斐波那契数列的第五十位：$12586269025$。

那么我们很容易得到思路，直接运用暴力，开一个双重循环，枚举每一个斐波那契数并判断乘积是否与 $n$ 相等，那么这道题就做完了。

时间复杂度为 $O(T\times50^{2})$。

# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,f[100];
void init(){	//预处理出前五十位斐波那契数
	f[0]=0,f[1]=1;
	for(register int i=2;i<=50;i++)
		f[i]=f[i-1]+f[i-2];
}
int main(){
	init();
	cin>>T;
	while(T--){
		bool flag=0;
		cin>>n;
		for(register int i=0;i<=50;i++){
			for(register int j=0;j<=50;j++)
				if(f[i]*f[j]==n) {
					flag=1;
					break;
				}
			if(flag) break;
		}
		//双重循环判断是否能被表示
		if(!flag) puts("NIE");
		else puts("TAK");
	}
}
```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个整数 $n$，判断该整数是否可以表示为两个斐波那契数的乘积。

#### 题目分析


------------
首先看数据范围 $0 \le n \le 10^9$。

通过计算可知 $n$ 只可能表示为斐波那契数列前 $50$ 项中的两个数的乘积，因为斐波那契数列第 $50$ 项的值为 $12586269025$ 明显超出了数据的范围。

- 首先处理出斐波那契数列前 $50$ 位的值，循环或者打表皆可。
- 用两层 ```for``` 循环枚举所有可能的情况，判断 $n$ 是否能表示为两个数的乘积。

一秒数据稳过。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;
const int N = 10010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

long long T,n,f[100];

int main(){
	f[0] = 0,f[1] = 1;
	for(int i=2;i<=50;i++){
		f[i] = f[i-1] + f[i-2];
	}
	T = read();
	while(T--){
		bool flag = 0;
		n = read();
		for(int i=0;i<=50;i++){
			for(int j=0;j<=50;j++){
				if(f[i] * f[j] == n){
					flag = 1;
					break;
				}
			}				
			if(flag) break;
		} 
		if(!flag)	
			printf("NIE\n");
		else 
			printf("TAK\n");
	}
	return 0;
}
```


---

## 作者：sysong (赞：1)

# 题解 P5993 [PA2014]Iloczyn

题意很清楚，坑也不多（~~但也不是没有。。。~~），很快就过了此题。（~~好像跑得还挺快~~）

## 题目描述

判断一个数是否为两个斐波那契数的乘积。

**（这个斐波那契数列从$0,1$开始）**

~~也就这么一个坑点了。。。~~

## $Solution$

别的dalao都是枚举两个斐波那契数的，我只枚举了一个，所以耗时较少。

斐波那契数列的递推公式很简单， `f[i]=f[i-1]+f[i-2]; `，只要设置 `f[0]=0;f[1]=1;` 即可。

预处理部分$code$:

---

```c++
h[0]=0;h[1]=1;
for(R int i=2;i<46;i++)h[i]=h[i-1]+h[i-2];
```

---

接下来只要对于每一个输入，判断是否为两个斐波那契数的积。

枚举一个因子$h[i]$  ($h[i] \times h[i] \le n$)，二分查找另一个是否为斐波那契数即可

**注意：由于我们从$1$开始判断是否为因子，所以$0$要特判。**

判断部分$code$:

---

```c++
inline void check(int n){
	if(!n){													// 对于 0 ，特判
		printf("TAK\n");
		return;
	}
	for(R int i=1;h[i]*h[i]<=n;i++){						// 枚举一个斐波那契数
		if(n%h[i]==0&&binary_search(h,h+46,n/h[i])){		// 前一半判断 h[i] 是否为 n 因子，
            												// 后一半为 STL 的二分查找函数，用来判断 n/h[i] 是否为斐波那契数
			printf("TAK\n");return;
		}
	}
	printf("NIE\n");										// 枚举结束还没有匹配，那就说明不符合要求
	return;
}
```

---

## 完整$C++\ \ \ Code$:

```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
using namespace std;

inline int rd(){
	R int x=0;R char c=gc();
	while(c>'9'||c<'0')c=gc();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x;
}

int h[50];

inline void check(int n){
	if(!n){
		printf("TAK\n");
		return;
	}
	for(R int i=1;h[i]*h[i]<=n;i++){
		if(n%h[i]==0&&binary_search(h,h+46,n/h[i])){
			printf("TAK\n");return;
		}
	}
	printf("NIE\n");
	return;
}

int main(){
	h[0]=0;h[1]=1;
	for(R int i=2;i<46;i++)h[i]=h[i-1]+h[i-2];// 只要算到 46 位就达到了 10 的 9 次方
	int t=rd();
	for(R int i=0,k;i<t;i++)k=rd(),check(k);
	return 0;
}

```



***by jsntsys***

$2020.10.3$

---

## 作者：sinsop90 (赞：1)

这道题我们先从数据范围入手

我们发现$1 ≤ T ≤ 10$, $0 ≤ n_i ≤ 10^{9}$

因此,如果我们估算一下,斐波拉契的第$50$位大概就是这个数值了

因此我们可以直接打个暴力,最坏情况是枚举 $50^{2} * T$ 次,显然是很可观的

首先:预处理斐波拉契数列

```
fit[0] = 0;//将前两位赋值
fit[1] = 1;
for(int i = 2;i <= 50;i++) {
	fit[i] = fit[i-1]+fit[i-2];//斐波拉契规律
}
```

接着是暴力枚举任意两个斐波拉契数的相乘:

```
for(int j = 1;j <= 50;j++) {
	for(int k = 1;k <= 50;k++) {
		if(fit[j] * fit[k] == x) { // 如果找到答案了,跳出循环
			flag = true;
			break;
		}
	}
	if(flag) break;
}
```

因此有了以下代码:

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int n, fit[100005];
	cin >> n;
	fit[0] = 0;
	fit[1] = 1;
	for(int i = 2;i <= 50;i++) {
		fit[i] = fit[i-1]+fit[i-2];
	}
	for(int i = 1;i <= n;i++) {
		int x;
		bool flag = false;
		cin >> x;
		if(x == 0) {
			cout << "TAK"<<endl;
			continue;
		}
		for(int j = 1;j <= 50;j++) {
			for(int k = 1;k <= 50;k++) {
				if(fit[j] * fit[k] == x) {
					flag = true;
					break;
				}
			}
			if(flag) break;
		}
		if(flag) cout<<"TAK"<<endl;
		else cout << "NIE" << endl;
	}
}
```


---

## 作者：Yukinoshita_Yukino (赞：1)

这道题暴力轻松过。

具体思路：

1.建一个斐波那契数组，数组在30000以下就行。

2.枚举斐波那契数，看和不和$n$一样。这里为了不TLE，最好写个特判：如果两斐波那

契数之积大于目标数，就不用枚举了，直接$break$。

坑点：1.有些数是有两组斐波那契数之积的，需要建一个记录变量。

附AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int F[1000001],i,j,k,flag=0,fflag=0;
void csh()
{
	for(i=3;i<=284783;i++)
	{
		F[i]=F[i-1]+F[i-2];
	}
	return ;
 } 
int main()
{
	F[0]=0;
	F[1]=1;
	F[2]=1;
	csh();
	int t;
	cin>>t;int n;
	for(i=1;i<=t;i++)
	{
		
		cin>>n;
		for(j=1;j<=284783;j++)
		{
			for(k=j;k<=284783;k++)
			{
				if(F[k]*F[j]==n) {cout<<"TAK"<<endl;flag=1;fflag=1;break;}
				if(F[k]*F[j]>n) break;
			}
			if(fflag==1){
				fflag=0;
				break;
			}
		}
		if(flag==0) cout<<"NIE"<<endl;
		flag=0;
	}
	return 0;
 } 
```


---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/P5993)

~~FOI题题都是原题。~~

## 分析

[FOI2022]T1，建议红。

斐波那契数列，又称黄金分割数列。该数列具有神奇的特性：数列中每一数字都是其前面两个数字之和。前一数字与后一数字之比趋近于固定常数 $0.618$。由此可以推算出：当 $k=45$ 时，$F_{45}>10^9$。

因此我们只要预处理到 $F_{45}$ 就可以了，然后再用两层循环枚举判断即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=50;
ll t,n,f[N];
int main(){
	cin>>t;
	f[0]=0;
	f[1]=1;
	for(int i=2;i<=45;i++)
		f[i]=f[i-1]+f[i-2];
	while(t--){
		cin>>n;
		bool flag=0;
		for(int i=0;i<=45;i++){
			for(int j=i;j<=45;j++){
				if(n==f[i]*f[j]){
					flag=1;
					break;
				}
			}
			if(flag)
				break;
		}
		if(flag)
			cout<<"TAK"<<endl;
		else
			cout<<"NIE"<<endl;
	}
	return 0;
}
```

---

## 作者：2021hych (赞：0)

# 直接看思路：
**斐波那契数列**肯定是**不会变**的，所以说每一项的**斐波那契数列**都是**确定**的。那么为了**节省时间**，**防止超时**，可以进行**预处理斐波那契数列**，那么**预处理**多少项呢？我们注意到 $n$ 的值不会超过 $10^9$ ，所以只要预处理出所有小于等于 $10^9$ 的**斐波那契数列的值**就好了。至于**判断**，**暴力匹配**即可。
# AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,f[60],cnt=1;
bool flag=true;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	f[0]=0;
	f[1]=1;
	for(int i=2;;i++) {
	    f[i]=f[i-1]+f[i-2];
	    cnt++;
	    if(f[i]>1e9) {
	        cnt--;
	        break;
	    }
	}
	while(t--) {
		cin>>n;
		flag=true;
		for(int i=0;i<=cnt;i++) {
			for(int j=0;j<=cnt;j++) {
				if(f[i]*f[j]==n) {
					cout<<"TAK"<<endl;
					flag=false;
					break;
				}
			}
			if(!flag) break;
		}
		if(flag) cout<<"NIE"<<endl;
	} 
	return 0;
} 
```


---

## 作者：Trollz (赞：0)

这道题的思路很简单，无非就是弄出斐波那契数列然后再循环，看数列中有没有两数相乘一样的。

有$2$种思路，正解&打表。

先来看看正解。
### 正解（蒟蒻都看得懂的）

首先我们得求出来斐波那契数列。怎么求呢？

咱们不妨来看看斐波那契数列。
```
0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 ......
```
不难发现，**每个数都是前面两个数的和**。

也就是说，换做数学思想的话，公式就是$a_i=a_{i-1}+a_{i-2}$。

我们在程序中，可以先定义一个数组$a$，然后模拟一遍，一步一步求出来斐波那契的每个数。

这样代码就出来了。

**值得注意的是，新定义的a数组默认每个元素都是0，所以如果不做一些前提的话，用下面的程序是没有任何意义的。所以我们得把第1、2个元素加上：**

```cpp
int a[10001];
a[0]=0;//第0个元素是0
a[1]=0;//第1个元素是1
a[2]=1;//第2个元素是1
for(int i=3/*从3开始，因为前面2个元素不能再加一遍*/;i<=20;i++){
    a[i]=a[i-1]+a[i-2];//实现公式
}
```
然后我们再加上一些简单的处理。

既然有$T$组数据，我们只要用一个循环就能搞定：
```cpp
for(int i=1;i<=T;i++){
	
}
```
然后再在数组里面搜索，发现一样的就输出TAK，然后跳转至finish；如果没有一样的，就自然不会跳转，直接输出NIE了。
```
#include <iostream>
using namespace std;
long long Fibonacci[1001];//不开longlong见祖宗
int main(){
	Fibonacci[0]=0;//第0个元素是0
	Fibonacci[1]=0;//第1个元素是1
	Fibonacci[2]=1;//第2个元素是1
	for(int i=3;i<=20;i++){
	    Fibonacci[i]=Fibonacci[i-1]+Fibonacci[i-2];
	}
	int T,cnc,limit=1;
	cin>>T;
	while(limit<=T){
		cin>>cnc;//输入数字；
		for(int j=0;j<=57;j++){
			for(int k=0;k<=57;k++){
            			//暴力
				if(Fibonacci[k]*Fibonacci[j]==cnc){//如果可以被其中2个元素相乘得到
					cout<<"TAK\n";//输出
					goto finish;//直接跳转	
				}
			}
		}
		cout<<"NIE"<<endl;
		finish:
		limit++;
	}
	return 0;
}
```
### 打表
当然，有些蒟蒻不会递推，我们就可以打表，网上搜的都有，或者用这个代码模拟：
```cpp
#include <iostream>
using namespace std;
long long f[1001];
int main(){
	f[0]=0;
	f[1]=0;
	f[2]=1;
	freopen("temp.txt","w",stdout);
	for(int i=3;i<=60;i++){
		f[i]=f[i-1]+f[i-2];
	}
	cout<<"int Fibonacci[60]={";
	for(int i=0;i<=60;i++){
		cout<<f[i]<<",";
		if(i==60){
			cout<<f[60]<<"};";
		}
	}
	return 0;
}
```
然后把输出的结果从temp.txt里拿出来，复制在主代码上，就可以了。

$Code:$
```cpp
#include <iostream>
using namespace std;
bool flag=false;
long long Fibonacci[57]={0,0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,
2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,
317811,514229,832040,1346269,2178309,3524578,5702887,9227465,
14930352,24157817,39088169,63245986,102334155,165580141,
267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976
,7778742049};
int main(){
	int T,cnc,limit=1;
	cin>>T;
	while(limit<=T){
		cin>>cnc;
		for(int j=0;j<=57;j++){
			for(int k=0;k<=57;k++){
				if(Fibonacci[k]*Fibonacci[j]==cnc){
					cout<<"TAK\n";
					flag=true;
					goto finish;			
				}
			}
		}
		cout<<"NIE"<<endl;
		finish:
		limit++;
	}
	return 0;
}
```
虽然对时间复杂度~~没什么卵用~~，但是这也算是一种奇妙的方法吧。

~~至少有些蒟蒻就不用学习如何打斐波那契了~~

那么题解就到这里。**望审核大大通过！**

---

## 作者：Daidly (赞：0)

### 思路：

预处理出斐波那契数列（大概$50$位就行），暴力枚举两个斐波那契数之积就可以了。记得每一次输出完之后返回原状态。

```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T>inline bool read(T &x){x=0;register char c=getchar();register bool f=0;
while(!isdigit(c)){if(c==EOF)return false;f^=c=='-',c=getchar();}
while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();if(f)x=-x;return true;}
template<class T>inline void print(T x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10^48);}
template<class T>inline void print(T x,char c){print(x),putchar(c);}
//快读不用管
int t,n;
long long f[50];
bool ct=false;
void init(){
	f[0]=0,f[1]=1;
	for(int i=2;i<=50;++i)f[i]=f[i-1]+f[i-2];
}
int main(){
	init();
	read(t);
	while(t--){
		read(n);
		for(int i=0;i<=49;++i){
			for(int j=0;j<=49;++j){
				if(f[i]*f[j]==n){
					ct=true;
					break;
				}
			}
		}
		if(ct==true)puts("TAK");
		else puts("NIE");
		ct=false;//返回原状态
	}
	return 0;
}
```

---

