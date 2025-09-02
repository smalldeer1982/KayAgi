# Madoka and Math Dad

## 题目描述

Madoka finally found the administrator password for her computer. Her father is a well-known popularizer of mathematics, so the password is the answer to the following problem.

Find the maximum decimal number without zeroes and with no equal digits in a row, such that the sum of its digits is $ n $ .

Madoka is too tired of math to solve it herself, so help her to solve this problem!

## 说明/提示

The only numbers with the sum of digits equal to $ 2 $ without zeros are $ 2 $ and $ 11 $ . But the last one has two ones in a row, so it's not valid. That's why the answer is $ 2 $ .

The only numbers with the sum of digits equal to $ 3 $ without zeros are $ 111 $ , $ 12 $ , $ 21 $ , and $ 3 $ . The first one has $ 2 $ ones in a row, so it's not valid. So the maximum valid number is $ 21 $ .

The only numbers with the sum of digits equals to $ 4 $ without zeros are $ 1111 $ , $ 211 $ , $ 121 $ , $ 112 $ , $ 13 $ , $ 31 $ , $ 22 $ , and $ 4 $ . Numbers $ 1111 $ , $ 211 $ , $ 112 $ , $ 22 $ aren't valid, because they have some identical digits in a row. So the maximum valid number is $ 121 $ .

## 样例 #1

### 输入

```
5
1
2
3
4
5```

### 输出

```
1
2
21
121
212```

# 题解

## 作者：happy_dengziyue (赞：1)

### 1 思路

很明显，这个数字只用 $1$ 和 $2$ 组成。

为了使得这个数字最大：

+ 当 $n\operatorname{mod}3=0$：输出 $2121...21$；

+ 当 $n\operatorname{mod}3=1$：输出 $1212...121$；

+ 当 $n\operatorname{mod}3=2$：输出 $2121...212$。

即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1647A_1.in","r",stdin);
	freopen("CF1647A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n%3==0){
			for(int i=1;i<=n/3;++i)printf("21");
		}
		if(n%3==1){
			for(int i=1;i<=n/3;++i)printf("12");
			printf("1");
		}
		if(n%3==2){
			for(int i=1;i<=n/3;++i)printf("21");
			printf("2");
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/71288304)

By **dengziyue**

---

## 作者：郑朝曦zzx (赞：0)

# 解题思路
本题解题思路是**贪心**，要想让数尽可能大，位数就要尽可能多，要让位数尽可能多，每位的数就要尽可能小。由于相邻两位不能相同，所以我们就要用 1 和 2 来组成这个多位数。

通过分析样例可知多位数的形态和输入整数除以 3 的余数有关系。

- 余数为 0

多位数形态：“2121……21”
- 余数为 1

多位数形态：“1212……121”
- 余数为 2
多位数形态：“2121……212”
# 代码
```cpp
#include <cstdio>
int t;
void solve()
{
	int x;
	scanf("%d", &x);
	if (x % 3 == 0)
	{
		for (int i = 1; i <= x / 3; ++i)
			printf("21");
	}
	else if (x % 3 == 1)
	{
		for (int i = 1; i <= x / 3; ++i)
			printf("12");
		printf("1");
	}
	else
	{
		for (int i = 1; i <= x / 3; ++i)
			printf("21");
		printf("2");
	}
	printf("\n");
}
int main()
{
	scanf("%d", &t);
	for (int i = 1; i <= t; ++i)
		solve(); 
	return 0;
}
```


---

## 作者：Dream_weavers (赞：0)

## 题意

求一个多位数，使这个数的数位**连续不带零且不相等**，数位和为 $n$。

## 思路

让这个数最大，该数只能由 $1$ 和 $2$ 组成，并且 $1$ 和 $2$ 是交替出现。

设这个数为 $s$，先枚举十个找一下规律。

| $n$ | $s$ |
| :----------: | :----------: |
|  $1$  |  $1$  |
|  $2$  |  $2$  |
|  $3$  |  $21$  |
|  $4$  |  $121$  |
|  $5$  |  $212$  |
|  $6$  |  $2121$  |
|  $7$  |  $12121$  |
|  $8$  |  $21212$  |
|  $9$  |  $212121$  |
|  $10$  |  $1212121$  |

可以发现，当 $n\equiv1\pmod{3}$，$s$ 的首位是 $1$，其他情况为 $2$。先判断首位为几，然后让 $1$ 和 $2$ 交替输出，并且让 $n$ 减去刚才输出的数，直到 $n=0$ 为止。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
void slove(){
	scanf("%d",&n);
	int tmp;
	if(n%3==1){
		printf("1");
		n-=1;
		tmp=2;
	}else{
		printf("2");
		n-=2;
		tmp=1;
	}
	while(n){
		printf("%d",tmp);
		n-=tmp;
		if(tmp==1)tmp=2;
		else tmp=1;	
	} 
	printf("\n");
	return;
}
int main(){
	scanf("%d",&t);
	while(t--)
		slove(); 
    return 0;
}

```


---

## 作者：BMTXLRC (赞：0)

转化一下题目给的条件，自然是选择使输出序列**最长**。

又因为不准有 $0$ 且不准有两个相邻数相同，我们考虑使 $1$ 与 $2$ 交替。

分为以下几种情况：

- 必须先 $2$ 再 $1$ 才能达到条件的，设 $2$ 的个数为 $x$，则 $1$ 的个数为 $x$ 或 $x-1$。

	- 若 $1$ 的个数为 $x-1$，则有 $2x+x-1=n$，解得 $n\equiv 2\pmod 3$。
    - 若 $1$ 的个数为 $x$，此时 $1$ 不能在第一个因为一定没有 $2$ 在第一个的结果大。故有 $2x+x=n$，解得 $n\equiv 0\pmod 3$。
- 必须先 $1$ 再 $2$ 才能达到条件的，跟上面同理，可以得到 $n\equiv 1\pmod 3$。

于是根据 $n$ 对 $3$ 的模数分类讨论就可以了。

```cpp
//CF1647-A
#include<bits/stdc++.h>
using namespace std;
int T,n;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        int k=(n+(3-n%3)%3)/3;//计算方程中的x
        if(n%3==1){
            for(register int i=1;i<=2*k-1;i++){
                if(i%2==1) printf("1");
                else printf("2");
            }
            printf("\n");
            continue;
        }else if(n%3==2){
            for(register int i=1;i<=2*k-1;i++){
                if(i%2==1) printf("2");
                else printf("1");
            }
            printf("\n");
            continue;
        }else{
            for(register int i=1;i<=2*k;i++){
                if(i%2==1) printf("2");
                else printf("1");
            }
            printf("\n");
            continue;
        }
    }
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1647A](https://www.luogu.com.cn/problem/CF1647A)

* **【题目翻译】**

给定一个数 $n$，要求找到一个数 $m$，满足

* $m$ 的数位内不含 $0$；
* $m$ 的两个相邻的数位不能相同；
* $m$ 的数位之和等于 $n$。

输出最大可能的 $m$。

* **【解题思路】**

显然 $m$ 的数位只包含 $1$ 和 $2$。

然后就可以分类讨论了。

1. 当 $n\equiv 0\pmod 3$，输出 $\dfrac n3$ 个`21`即可；
2. 当 $n\equiv 1\pmod 3$，先输出一个 `1`，再输出 $\dfrac {n-1}3$ 个`21`；
2. 当 $n\equiv 2\pmod 3$，先输出一个 `2`，再输出 $\dfrac {n-2}3$ 个`12`；

* **【代码实现】**

```cpp
#include <iostream>
#include <array>
 
using namespace std;
 
int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int n;
		cin>>n;
		if(n%3==2)
		{
			cout<<2,n-=2;
			while(n)
				n-=3,cout<<"12";
			cout<<'\n';
			continue;
		}
		if(n%3)
			cout<<n%3,n-=n%3;
		while(n)
			n-=3,cout<<"21";
		cout<<'\n';
	}
	return 0;
}
 
```

---

## 作者：风羽跃 (赞：0)

### 题意简述：

构造最大的整数使得各位数字之和为 $n$ 且相邻位数字不同。

### 题目分析：

考虑如果我们某一位上有一个 $3$，我们一定会把它拆成 $21$，多一位肯定更优。

扩展这个情况，如果某一位大于等于 $3$，我们一定会把它拆成若干个 $3$ 的和再拆成 $21$ 的情况，最后剩下一个余数。

分类讨论：

- 余数是 $0$，输出若干个 $21$；
- 余数是 $1$，最高位填 $1$，后面若干个 $21$；
- 余数是 $2$，最低位填 $2$，前面若干个 $21$。

### Code：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>

#define For(i,l,r) for(int i=(l);i<=(r);i++)
 
using namespace std;
 
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
 
int main()
{
	int T=read();
	while(T--){
		int n=read();
		if(n%3==0) For(i,1,n/3) printf("21");
		else if(n%3==1){
			putchar('1');
			For(i,1,n/3) printf("21");
		}
		else{
			For(i,1,n/3) printf("21");
			putchar('2');
		}
		puts("");
	}
	return 0;
}
 
/*
*/
```


---

## 作者：清烛 (赞：0)

题意：找到最大的不含前导零且没有连续的两位相同的十进制整数，满足每一位之和为 $n$。

注意到，我们肯定要让位尽可能多，而又不能连续两位相同，所以只能 $1,2,1,2,\cdots$ 这样交替。然后观察样例 + 手玩可以发现

```
1	1
2	2
3	21
4	121
5	212
6	2121
7	12121
8	21212
9	212121
```

似乎是 $3$ 个一组的，所以直接构造就行了。

```cpp
int main() {
    int T; read(T);
    while (T--) {
        int n; read(n);
        if (n % 3 == 1) {
            --n; putchar('1');
        }
        for (int i = 0; n; i ^= 1) {
            if (!i) n -= 2, putchar('2');
            else --n, putchar('1');
        }
        putchar('\n');
    }
    return output(), 0;
}
```

---

## 作者：Toorean (赞：0)

## 题意
给出一个数 $x$，输出任意个数的和为 $x$ 且最大的值，相邻两个数不相等且不包含 $0$。

## 思路
首先，拆数当然是长度越大，数字也就越大。其次，如果这个数要想长度最大，那么这个数字尽量小，由于不可使用 $0$，因此 $1$ 和 $2$ 为最小的两个数。那么优先考虑拆这两个数，则可得最优解。

## AC Code
```cpp
#include <cstdio>

#define LL long long
#define MAXN 1000010 // Datas MAX
#define INF 0x3f3f3f3f
#define mpa make_pair
#define fir first
#define sec second
#define max(x,y) (x > y ? x : y)
#define min(x,y) (x < y ? x : y)
#define openFile(_FileName) freopen (_FileName".in", "r", stdin); freopen (_FileName".out", "w", stdout)
#define yon(x) ((x) ? puts ("YES") : puts ("NO"))
#define ffor(_INDEX,l,r) for (int _INDEX = (l); _INDEX <= (r); _INDEX++)
#define _for(_INDEX,l,r,_Value) for (int _INDEX = (l); _INDEX <= (r); _INDEX += _Value)
#define rfor(_INDEX,l,r) for (int _INDEX = (l); _INDEX >= (r); _INDEX --)
#define _rfor(_INDEX,l,r, _Value) for (int _INDEX = (l); _INDEX >= (r); _INDEX -= _Value)

// using namespace std;

int t, n;

template <typename T> inline void read (T &x) {
    T f = 1; x = 0;
    char ch = getchar ();
    while (ch < '0' || ch > '9') {
        if (ch == '-') { f = -1; };
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar ();
    }
    x *= f;
}

template <typename T, typename ... Args> inline void read (T &t, Args&... args) {
    read(t), read(args...);
}

void solve (int x) {
    if (x <= 2) {
        printf ("%d\n", x);
    } else {
        if (x % 3 == 1) {
            x -= 3;
            while (x >= 0) {
                printf ("12");
                x -= 3;
            } puts ("1");
        } else if (x % 3 == 2) {
            x -= 3;
            while (x >= 0) {
                x -= 3;
                printf ("21");
            } puts ("2");
        } else {
            x -= 3;
            while (x >= 0) {
                printf ("21");
                x -= 3;
            } puts ("");
        }
    }
}

signed main (void) {
    
    read (t);
    while (t--) {
        read (n);
        solve (n);
    }

    return 0;
}
```

---

## 作者：Elgo87 (赞：0)

简化题意：给出一个整数 $n$，你需要求一个数 $x$，$x$ 各个位数都不能是 $0$，而且 $x$ 相邻两个数都不能相同，而且 $x$ 各个数位上的和为 $n$，并且你需要使 $x$ 最大。

显然，我们要让 $x$ 最大，那就让 $x$ 的位数尽可能大即可。

那么如果没有“相邻两个数不能相同”这个条件，显然答案一定就是 $\overbrace{111..111}^{n \text{ 个 1}}$。

那如果不能相同呢？

我们可以把一些 $1$ 合并成 $2$，这样就可以保证不相同。

例如，$8$ 拆分成 $11111111$，经过处理后就是 $21212$；再例如 $7$，拆分是 $1111111$，处理后变为 $12121$ 再例如 $6$，拆分成 $111111$，处理后就是 $2121$。

我们发现不同的数，处理后的首位数都不同，其它位数交替 $1$ 和 $2$ 就行了。

经过观察，我们发现如果 $n\bmod 3=1$ 时，首位数就是 $1$，否则就是 $2$。

那么此题就得到了解决。

参考代码：

```cpp
# include <bits/stdc++.h>
# define max(a,b) ((a)>(b) ? (a) : (b))
# define min(a,b) ((a)<(b) ? (a) : (b))
# define abs(a,b) ((a)> 0  ? (a) : -(a))
# define endl putchar('\n')
# define space putchar(' ');
# define begining {
# define ending }
# define int long long
using namespace std;

inline int read() {
	int num = 0; int nev = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') nev = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { num = (num<<1) + (num<<3) + (ch ^ 48); ch = getchar(); }
	return num * nev;
}

inline void print(const int& x) {
	if (x < 0) { putchar('-'); print(-x); return ; }
	if (x < 10) { putchar(x+'0'); return ;}
	print(x/10), putchar(x%10 + '0'); return ;
}

signed main()
{
	int T = read();
	while (T --) {
		int n = read();
		if (n % 3 == 0 || n % 3 == 2) {
			int f = 2;
			while (n>0) {
				n -= f;
				print(f);
				f = (f == 2 ? 1 : 2);
			}
			endl;
		} else {
			if (n % 3 == 1) {
				int f = 1;
				while (n>0) {
					n -= f;
					print(f);
					f = (f == 2 ? 1 : 2);
				}
				endl;
			}
		}
	}
	return 0;
}


 
```

---

## 作者：JS_TZ_ZHR (赞：0)

## 题意：

给定一个数 $n$，请你找出来一个最大的不含 $0$ 的十进制数使得这个数各位和等于 $n$ 且没有相邻的两个数相等。

## 题解：

显然答案要数位尽量多，所以直接 $2121...21$ 的填即可。注意当 $n\bmod 3=1$ 时会出现 $2121..21$ 之后填不了的情况，特判一下，开头从 $1$ 开始填。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long 
using namespace std;
int T,n,m;
bool check(int x){
	
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		if(n%3!=1){
			while(n>=3){
				cout<<21;
				n-=3; 
			}
			if(n)cout<<n;
		}
		else{
			while(n>=3){
				cout<<12;
				n-=3; 
			}
			if(n)cout<<n;
		}
		cout<<endl;
	}
} 
```


---

