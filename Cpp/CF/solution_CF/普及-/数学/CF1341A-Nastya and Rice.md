# Nastya and Rice

## 题目描述

有$n$个范围为$[a-b,a+b]$的数，判断他们的和是否可能在$[c-d,c+d]$范围中。

输入有多组数据（$1 \le T \le 1000$），保证：

- $1 \le n \le 1000$
- $0 \le b < a \le 1000 $
- $0 \le d < c \le 1000$

## 样例 #1

### 输入

```
5
7 20 3 101 18
11 11 10 234 2
8 9 7 250 122
19 41 21 321 10
3 10 8 6 1```

### 输出

```
Yes
No
Yes
No
Yes```

# 题解

## 作者：hhoppitree (赞：7)

# $A$题 [$\color{red}CF1341A$](https://codeforces.com/problemset/problem/1341/A)
和往常一样，CF的A题总是很水的，而且有多组数据。   

题目：[洛谷](https://www.luogu.com.cn/problem/CF1341A)  

题意简述：  
有$n$粒米,$1$个背包，由于$Nastya$糊涂，她只记得每粒米的重量为$[a-b,a+b]$中的一个数,背包的重量为$[c-d,c+d]$中的一个数，问$Nastya$有没有可能记对，多组数据。

数据范围：
数据的组数$T\le1000$，$0\le b<a\le1000$，$0\le c<d\le1000$

题解：  
每粒米的重量最小为$a-b$，最大为$a+b$，所以$n$粒米的重量最小为$n×(a-b)$，最大为$n×(a+b)$，所以若$n×(a+b)$小于背包的最小值$c-d$，则$Nastya$~~这头猪~~肯定记错了；若$n×(a-b)$大于背包的最大值$c+d$，则$Nastya$~~这头猪~~同样肯定记错了。  
即若$n×(a+b)<c-d$或$n×(a-b)>c+d$，则肯定不行  
反之，若$n×(a+b)\ge c-d$且$n×(a-b)\le c+d$，则肯定可以，构造方法略。  
标程：
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int res=0;
    char c;
    bool zf=0;
    while(((c=getchar())<'0'||c>'9')&&c!= '-');
    if(c=='-')zf=1;
    else res=c-'0';
    while((c=getchar())>='0'&&c<='9')res=(res<<3)+(res<<1)+c-'0';
    if(zf)return -res;
    return res;
}
int main(){
	int T=read();
	while(T--){
		int n=read(),a=read(),b=read(),c=read(),d=read();
		if((a+b)*n<c-d||(a-b)*n>c+d)cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```

考场上我这题题目看了半天，~~因为是英文~~，此题我在$00:12$时提交，一次$AC$  

---

## 作者：sz_wsy (赞：2)

#### [CF1341A题目传送门](https://www.luogu.com.cn/problem/CF1341A)

## 题目大意

- 现有 $n$ 个数，每个数都在 $[a-b,a+b]$ 范围内。

- 判断它们的和是否可能在 $[c-d,c+d]$ 范围内。


## 分析
~~这是道水题~~，第一步，求出这 $n$ 个数的**和的范围**，设最小值 $L=n(a-b)$，最大值 $R=n(a+b)$。

**注意点**：题目中说的是是否**可能**在 $[c-d,c+d]$ 范围内，而不是**完全**在 $[c-d,c+d]$ 区间内，这一点要注意。

也就是说，在数轴上，只有以下两种情况时无法满足：$L$ 在 $c+d$ 右侧或 $R$ 在 $c-d$ 左侧。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/c3h8ren1.png)


代码如下：
```cpp
#include <iostream>
using namespace std;

int main(){
	int T,n,a,b,c,d;
	cin>>T;
	while(T--){
		cin>>n>>a>>b>>c>>d;
		int L=n*(a-b),R=n*(a+b);
		if(L>c+d || R<c-d) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
} 
```

第一篇题解，希望能帮到大家。


---

## 作者：Vct14 (赞：1)

### 题意

- 有 $n$ 个范围为 $[a-b,a+b]$ 的数，求它们的和是否可能在 $[c-d,c+d]$ 范围中。若可能，则输出 `Yes`；否则输出 `No`。有 $T$ 组测试数据。

- $1 \le T \le 1000,1 \le n \le 1000,0 \le b < a \le 1000,0 \le d < c \le 1000$。

### 思路

可以通过最值来思考。

因为所有 $n$ 个数应该都大于 $a-b$，所以可以得到这样一个结论：当 $n$ 个数全为 $a-b$ 时，若它们的和还大于 $c+d$，则无论取什么数，它们的和都大于 $c+d$，一定不可能。

同理，当 $n$ 个数全为 $a+b$ 时，若它们的和还小于 $c-d$，则无论取什么数，它们的和都小于 $c-d$，也一定不可能。

也就是已知这 $n$ 个数的和的最小值为 $n\times(a-b)$，最大值为 $n\times(a+b)$。如果连和的最小值都大于 $c+d$，或者连和的最大值都小于 $c-d$，则一定不可能。


### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;
    cin>>T;
    while(T--){//多测
    	int n,a,b,c,d;
        cin>>n>>a>>b>>c>>d;
        if(n*(a-b)>c+d) cout<<"No";//和最小值大于 c+d，不可能
        if(n*(a+b)<c-d) cout<<"No";//和最大值小于 c-d，也不可能
        else cout<<"Yes";
        cout<<"\n";//多测记得换行
    }
    return 0;
}
```

---

## 作者：Hughpig (赞：0)

观察发现，想让所有 $n$ 个数的和最小，可以让它们全部取 $a-b$。

反之，如果想让所有 $n$ 个数的和最大，可以让他们全部取 $a+b$。

如果 $n\times(a-b)>c+d$，即所有数都取最小都比 $c+d$ 大，那么肯定无法满足条件，输出 `No`。

同理，如果 $n\times(a+b)<c-d$，即所有数都取最大也比 $c-d$ 小，也同样无法满足条件，输出 `No`。

而其他情况就可以满足了，输出 `Yes`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b,c,d;//定义变量，意义同题目中

int main()
{
    cin>>t;
    while(t--)//多组数据
    {
    	cin>>n>>a>>b>>c>>d;
    	cout<<(n*(a-b)>c+d||n*(a+b)<c-d?"No\n":"Yes\n");//计算是否可以满足条件，输出
	}
	return 0;
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
不难发现，当我们选 $n$ 个 $a-b$ 时，和是最小的，而选 $n$ 个 $a+b$ 时，和是最大的。  

若最小的和大于 $c+d$ 或者最大的和小于 $c-d$，则都是无解的。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b,c,d;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>a>>b>>c>>d;
		if((a+b)*n<c-d||(a-b)*n>c+d){
			cout<<"No"<<endl;
		}
		else{
			cout<<"Yes"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：ZigZagKmp (赞：0)

本文同步发表于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13749280.html)

本场题解见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1340-solution)


## CF1341A
### 题意简述
现在有 $n$ 个数，每个数的大小在 $[a-b,a+b]$ 内，问是否存在一种情况，使得这 $n$ 个数的和在 $[c-d,c+d]$ 内。

多测，$t\le 1000,0\le b<a\le 1000,0\le d<c\le 1000$

### 算法分析
不难发现，这 $n$ 个数的和的最小值为 $(a-b)n$，和的最大值为 $(a+b)n$ ，且范围内的每一个和都可以构造。

因此只要区间 $[(a-b)n,(a+b)n]$ 与 $[c-d,c+d]$ 有交集即可。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
template <typename Tp>void read(Tp &x){
	x=0;int fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=fh;
}
int n,a,b,c,d;
signed main(){
	int T;
	read(T);
	while(T--){
		read(n);read(a);read(b);read(c);read(d);
		int al=(a-b)*n,ar=(a+b)*n;
		int bl=(c-d),br=(c+d);
		if(ar<bl||al>br)puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：lingfunny (赞：0)

# 题目分析
考虑不成立的情况：

如果这$n$个数取最大值（即取$a+b$）还比给定的区间的最小值（即$c-d$）小，显然不成立。即：

```cpp
if( (a+b) * n < c-d )
printf("No\n");
```

如果这$n$个数取最小值（即取$a-b$）还比给定的区间的最大值（即$c+d$）大，显然不成立。即：

```cpp
if( (a-b) * n > c+d )
printf("No\n");
```

其他情况就是```Yes```啦。
# 上代码
```cpp
#include <cstdio>

int T,a,b,c,d,n;
inline int read();

int main(){
	T=read();
	while(T--){
		n=read();a=read();b=read();c=read();d=read();
		if( (a-b) * n > (c+d) )
		printf("No");
		else if( (a+b) * n < (c-d) )
		printf("No");
		else printf("Yes");
		printf("\n");
	}
	return 0;
}

inline int read(){
	int x=0,f=1;
	char ch = getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*f;
}
```

---

## 作者：Sora1336 (赞：0)

对于这道题，是一道不折不扣的水题。

判断区间 $[a-b,a+b]$ 和区间 $[c-d,c+d]$有没有交集。

我们很容易可以证明，在$[a-b,a+b]$ 和区间 $[c-d,c+d]$内有交集时，必有解决方案，$O(1)$的时间复杂度。

CF小技巧：第一道题如果有样例极大时，请考虑$O(1)$算法。

代码：
```cpp
#include <iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int n,a,b,c,d;
		cin>>n>>a>>b>>c>>d;
		if((a+b)*n<c-d || (a-b)*n>c+d){		//如果区间没有交集
			cout<<"No"<<endl;
		}else{						//否则
			cout<<"Yes"<<endl;
		}
	}
} 
```


---

## 作者：juicyyou (赞：0)

# CF1341A - Nastya and Rice
## 题目大意：
本题一共有 $t$ 组数据，对于每组数据，给定五个整数 $n, a, b, c, d$ 请你判断有没有一个长度为 $n$ 数列 $x$ 使得：
$$a - b \le x_i \le a + b\,\, (1 \le i \le n)$$
并且：
$$c - d \le \sum\limits_{i = 1}^n x_i \le c + d$$
## 解法：
首先由于第一个条件，我们就有：
$$n\cdot(a - b) \le \sum\limits_{i = 1}^nx_i \le n\cdot(a + b)$$
并且 $\sum\limits_{i = 1}^n x_i$ 一定可以取区间 $\left[a  - b, a + b\right]$ 中的每一个数。又因为第二个条件，所以我们只需要判断区间 $\left[a  - b, a + b\right]$ 和区间 $\left[c - d,\, c + d\right]$有没有交集就行了。

下面是我的Code:
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<set>
#include<cstdlib>
#include<cctype>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e5 + 5;
const ll maxm = 1e3 + 5;
template<class T>
inline T qread(T &IEE){ // 快读
	register T x = 0, f = 1;
	register char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -f;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return IEE = x * f;
}
ll t;
ll n, a, b, c, d;
ll l1, r1, l2, r2;
int main(){
	qread(t);
	while(t--){ // 多测
		qread(n);
		qread(a);
		qread(b);
		qread(c);
		qread(d);
		l1 = n * (a - b);
		r1 = n * (a + b);
		l2 = c - d;
		r2 = c + d;
		if(r1 < l2 || l1 > r2){ // 判断交集
			puts("NO");
		} else {
			puts("YES"); // 输出
		}
	}
	return 0;
}
```

上述算法单次复杂度 $\mathcal O(1)$ ，那总复杂度就是 $\mathcal O(t)$ ，可以通过此题。

---

