# Blog Photo

## 题目描述

某博客的照片上传功能如下：
    对于一张原照片，系统会裁剪其中的一个矩形部分上传，这个矩形部分被称为“上传矩形”。上传矩形的宽高比的合法取值范围为0.8至1.25。另外，上传矩形至少要有一条边的长度等于2^x（x为整数）且各边长度都为正整数。
    现在给出原照片的高度h和宽度w，请你求出一个最大面积合法上传矩形，并给出它的高和宽。

## 样例 #1

### 输入

```
2 1
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
2 2
```

## 样例 #3

### 输入

```
5 5
```

### 输出

```
5 4
```

# 题解

## 作者：agicy (赞：5)

# 思路

$CodeForces$水题，枚举即可。

# 代码

代码如下。

```cpp
#include<cstdio>//头文件
#define min(a,b) ( (a) < (b) ? (a) : (b) )//宏定义min()函数

long long h,w,t,p=1,a,b;//开long long防止溢出

int main(void){
    register int i;//寄存器更快些
    scanf("%lld%lld",&h,&w);//读入
    for(i=0;i<30;++i,p<<=1){//用p枚举2^p，位运算比乘法更快
        if(p<=h&&4*p<=5*w){
            t=min(w,5*p/4);
            if(p*t>a*b||(p*t==a*b&&a<p))
                a=p,b=t;//更新答案
        }
        if(p<=w&&4*p<=5*h){
            t=min(h,5*p/4);
            if(p*t>a*b||(p*t==a*b&&a<t))
                a=t,b=p;//更新答案
        }
    }
    printf("%lld %lld\n",a,b);//输出
    return 0;//结束
}
```

## [我的评测记录](https://www.luogu.org/record/show?rid=10181928)

---

## 作者：very_easy (赞：2)

~~一道水题。~~

首先要先枚举出 $2^a$ 最大可以是多少，而如果长是 $2^a$，则宽是 $\min(w,2^a \div 4)$ 反之，长也是一样。

所以就只是这样是不是太无聊了？

今天我来介绍一种优化幂次方的方法：

# 快速幂

~~神犇们可以直接跳过~~

众所周知，直接求解 $a^b$ 是 $O(n)$ 的时间复杂度，代码如下：

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,ans=1;
	cin>>a>>b;
	for(int i=1;i<=b;i++){
		ans*=a;
	}
	cout<<ans;
	return 0;
}
```
~~但是这样也太慢了吧！~~

所以我们就可以使用快速幂来优化。（注：为美观起见，以下所有除法均视为向下取整）

设求 $a^b$

1. 如果 $b$ 是奇数，则 $a^b = a^{b\div2}\times a^{b\div2} \times a$

2. 如果 $b$ 是偶数，则 $a^b=a^{b/2}\times a^{b/2}$

3. **如果 $b$ 是 $0$，答案就是 $1$**

那么我们可以使用递归来解决这个问题，代码如下：

```c++
int ksm(int a,int b){
	if(b==0){
		return 1;
	}
	int t=ksm(a,b/2);
	if(b&1){
		return t*t*a;
	}
	else{
		return t*t;
	}
}
```

# 代码

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long//注意要开long long 
int h,w;
int ksm(int a,int b){//快速幂 
	if(b==0){
		return 1;
	}
	int t=ksm(a,b/2);
	if(b&1){
		return t*t*a;
	}
	else{
		return t*t;
	}
}
signed main(){
	cin>>h>>w;
	int a=1;
	while(ksm(2,a)<=h&&ksm(2,a)<=w){
		a=ksm(2,a);//求出最大的a 
	}
	int x=min(h,a*5/4);
	int y=min(w,a*5/4);
	if(x<y){
		cout<<a<<" "<<x;
	}
	else{
		cout<<y<<" "<<a;
	}
	return 0;
}
```


---

## 作者：e4fsrc2e4fsrc2 (赞：2)

## [Blog Photo](https://www.luogu.com.cn/problem/CF53B)
## 思路分析
对于当前的 $w$ 和 $h$ 来说，他们所能允许的 $2^x$ 的便一定会满足 $2^x\le h$ 并且 $2^x\le w$。

所以我们考虑求出这个满足要求的 $2^x$ 的最大值。

直接利用 $\verb|STL|$ 中的 ```__lg``` 函数或 ```log2``` 函数就可以直接求出 $x$ 的最大值，再用 ```pow``` 函数就可以求出 $2^x$ 的最大值是多少了。

注意：对于求出来的 $2^x$ 而言，有两种情况。第一种是 $2^x$ 作为高，那么另外一条边的最大值就是 $\min(w,2^x\times5\div4)$，同理，如果 $2^x$ 作为宽则另一条边的最大值便为 $\min(h,2^x\times5\div4)$。

PS：要开 ```long long``` 不然会 $\color{red}{\text{WA}}$。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
ll x,y;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>x>>y;
	ll a=pow(2,(int)__lg(min(x,y)));
	ll m=min(x,a*5/4),n=min(y,a*5/4);
	if(m>=n)cout<<m<<' '<<a;
	else cout<<a<<' '<<n;
	return 0;
}
```

---

## 作者：Buried_Dream (赞：2)

## 题意：

从一张 $h \times w$ 的照片上找到一张最大上传矩形，上传矩形要求有一条边为 $2$ 的幂次，同时长宽比在 $[0.8,1.25]$ 之间。

## 思路：

先根据 $h$ 和 $w$ 算出最大的能容忍的 $2$ 的幂次。

因为要找最大的，我们让找出来的 $2$ 的幂次为最小边，去找他的 $1.25$ 倍，但是要注意他的 $1.25$ 倍有可能超出范围，所以要和 $h,w$ 取一个 $\min$。

## AC code:

```cpp

/*
work by: TLE_Automation
Time: O(轻轻松松过)
knowledge: 垃圾算法
*/
#include<bits/stdc++.h>
#define int long long
#define Min(x, y)  (x > y ? y : x);
#define Max(x, y)  (x > y ? x : y);
#define orz cout << "szt lps fjh AK IOI";
using namespace std;

const int maxn = 3e6;
const int MAXN = 3e3;
const double down = 0.996;
const double limit = 1e-10;
const int mod = 1e9 + 7;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (!isdigit(ch)) {if(ch == '-') {w = -1;}ch = getchar();}
	while (isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48);ch = getchar();}
	return s * w;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}

int H = 1, h, w;

void init( ) {
	while(H * 2 <= h && H * 2 <= w) H <<= 1; 
}

signed main() {
	h = read(), w = read();
	init();
	int ans1 = min(h, H * 5 / 4);
	int ans2 = min(w, H * 5 / 4);
	if(max(ans1, ans2) == ans1) return printf("%lld %lld\n", ans1, H), 0;
	else return printf("%lld %lld\n",H, ans2) , 0;
}
```

---

## 作者：CGDGAD (赞：2)

### 题解 $\texttt{CF53B Blog Photo}$

----

### 题目大意

在一个 $h \times w$ 的矩形中取一个最大的矩形，使得它的有一条边是 $2$ 的次方，且 $0.8 \leq \text{两条边的长度的比值} \leq 1.25$。

----

### 解题思路

这道题目，我们可以发现，裁剪出来的正方形的其中边长是 $2$ 的次方的那条边的长度，可以根据 $h$ 和 $w$ 计算出来，即满足 $2^n \leq h, 2^n \leq w$ 的最大 $2^n$ ( $n$ 为正整数)。

即，这行代码。

```cpp
// a << 1 表示 a *= 2
while (a << 1 <= h && a << 1 <= w) a <<= 1;
```

那么根据这条边的长度，就可以计算出另外一条边的最大的长度，即代码的 $8$ 到 $11$ 行。

```cpp
#include <cstdio>
#include <iostream>
long long h, w;
int main() {
	scanf("%lld%d", &h, &w);
	long long a = 1;
	while (a << 1 <= h && a << 1 <= w) a <<= 1;
	long long m = std::min(h, a * 5 / 4);
	long long n = std::min(w, a * 5 / 4);
	if (m >= n) printf("%lld %lld\n", m, a);
	else printf("%lld %lld\n", a, n);
	return 0;
}
```

---

## 作者：nxd_oxm (赞：0)

# 思路
首先只需要找到原图中最大的“上传矩形”就好了。

“上传矩形”呢指的是原图中的一部分，高和宽的比例保证在 $0.8 \sim 1.25$ 就好了。

~~本人数学不好，懒得算~~

所以我们直接暴力枚举。

每次枚举高的长度，保证他是 $2^n$。不用管其他的情况，因为后面枚举宽的时候会包含所有情况。

因为高已经定了，所以我们要最大化宽。因为比例在 $0.8 \sim 1.25$ 里面，最大化就是高除以 $0.8$。每次检测这种情况在要求里没，只要可以就记录最大就好了。

算宽也同理。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int h,w,maxs=0,hh=0,ww=0;
    cin>>h>>w;
	for(int newh=1,nums=0;nums<30;newh<<=1,nums++){
		if(newh<=h&&4*newh<=5*w){
			int neww=min(5*newh/4,w);
			if(newh*neww>maxs||(newh*neww==maxs&&newh>hh)){
				maxs=newh*neww;
				hh=newh;
				ww=neww;
			}
		}
	}
	for(int neww=1,nums=0;nums<30;neww<<=1,nums++){
		if(neww<=w&&4*neww<=5*h){
			int newh=min(neww/4*5,h);
			if(newh*neww>maxs||(newh*neww==maxs&&newh>hh)){
				maxs=newh*neww;
				hh=newh;
				ww=neww;
			}
		}
	}
	cout<<hh<<" "<<ww; 
    return 0;
}
```

有点丑，请见谅

---

## 作者：zibenlun (赞：0)

# 这题太水了！

首先我们可以发现因为有了其中一边是 $2$ 的 $x$ 方，所以我们可以轻而易举的算出其中一条边，那么另一条边就可以通过这条边推出。此时分为两种情况，第一种是已经算出的为高，另一种就是已经算出的边为宽，最后取最大值输出就可以了。

# 注意事项

要开 long long

# 我的 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {
		s=(s<<3)+(s<<1)+(ch^48);
		ch=getchar();
	}
	return s;
}
inline void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
long long h,w,ans=1;
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	h=read();
	w=read();
	while(ans<<1 <= min(h,w)) ans<<=1;
	if(min(h, (long long)(ans*1.25))>=min(w, (long long)(ans*1.25))) {
		write(min(h, (long long) (ans*1.25)));
		putchar(' ');
		write(ans);
	} else {
		write(ans);
		putchar(' ');
		write(min(w, (long long) (ans*1.25)));
	}
	return 0;
}

```

# [我的 AC 截图](https://cdn.luogu.com.cn/upload/image_hosting/yjz3hev1.png)


---

## 作者：GFyyx (赞：0)

## 解题思路
先求出特殊边 $x=2^k$ 最大值（$x\leq h\leq w$）。判断 $x$ 作上传图片的高还是宽，再根据 $x$ 的值求出满足条件第二条边。

### 代码优化
不难发现 $x=2^k$ 可以使用位运算减小时间复杂度的常数。

## AC 代码
```cpp
#include <iostream>
using namespace std;
long long h,w,x=1;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> h >> w;
	for(;x<=h&&x<=w;x<<=1);//倍增求特殊边
	x>>=1;//除回一个2
	long long n=min(w,(x*5)>>2);//x作长
	long long m=min(h,(x*5)>>2);//x作宽
	if (m>=n) cout << m << " " << x << endl;
	else cout << x << " " << n << endl;
	return 0;//AC
}
```


---

## 作者：IcyFoxer_XZY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF53B)

这题我们可以先找到一个最大的 $2^k$ 使得 $2^k\le\min(h,w)$，然后以 $2^k$ 为剪出照片里较小的那个边，枚举它的 $1.25$ 倍到 $0.8$ 倍，如果满足题意就可直接输出。

代码：

```cpp
#include<iostream>
#define int long long
using namespace std;
int ans=1,h,w;
signed main(){
	cin>>h>>w;
	while(ans*2<=min(h,w))ans*=2;
	int x=min(h,ans*5/4),y=min(w,ans*5/4);
	if(x>=y)printf("%lld %lld",x,ans);
	else printf("%lld %lld",ans,y);
	return 0;
}
```
Bye！

---

## 作者：Mx_sky (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/CF53B)

## 解法一
枚举 $2^x$，根据题目条件，已知一条边，即可求出另一条边的长度，最多枚举 $30$ 次（因为 $2^{31}=2147483648$，那么     $2^{30}=2^{31}\div2=1073741824\geq10^9$)。

代码没写，就不放了。

## 解法二
求出 $2^x$ 最大是多少（$2^x$ 必须同时满足 $\leq h$  和 $\leq w$），根据 $2^x$ 求出另一条边的边长，时间复杂度跟解法一相同。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000000+9;
#define ll long long   
ll h,w,x=1,a,b;     //开long long防止溢出
int main(){ 
    scanf("%lld %lld",&h,&w);  //格式化输入
    for(;x<=h&&x<=w;x=x*2);
	x=x/2;   //别忘了除2，因为多乘了个2
	a=min(h,x*5/4),b=min(w,x*5/4);
   //5/4=1.25。可能边长比原本的长度还要小
   //另一条边可能是h，也可能是w，都要算出来
	if(a>=b) cout<<a<<" "<<x<<endl;
	else cout<<x<<" "<<b<<endl;
   //我们要求的是最大面积
    return 0;
}
```

---

