# Vasya and Digital Root

## 题目描述

Vasya has recently found out what a digital root of a number is and he decided to share his knowledge with you.

Let's assume that $ S(n) $ is the sum of digits of number $ n $ , for example, $ S(4098)=4+0+9+8=21 $ . Then the digital root of number $ n $ equals to:

1. $ dr(n)=S(n) $ , if $ S(n)&lt;10 $ ;
2. $ dr(n)=dr(S(n)) $ , if $ S(n)>=10 $ .

For example, $ dr(4098)=dr(21)=3 $ .

Vasya is afraid of large numbers, so the numbers he works with are at most $ 10^{1000} $ . For all such numbers, he has proved that $ dr(n)=S(S(S(S(n)))) $ $ (n<=10^{1000}) $ .

Now Vasya wants to quickly find numbers with the given digital root. The problem is, he hasn't learned how to do that and he asked you to help him. You task is, given numbers $ k $ and $ d $ , find the number consisting of exactly $ k $ digits (the leading zeroes are not allowed), with digital root equal to $ d $ , or else state that such number does not exist.

## 说明/提示

For the first test sample $ dr(5881)=dr(22)=4 $ .

For the second test sample $ dr(36172)=dr(19)=dr(10)=1 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
5881
```

## 样例 #2

### 输入

```
5 1
```

### 输出

```
36172
```

## 样例 #3

### 输入

```
1 0
```

### 输出

```
0
```

# 题解

## 作者：Alex_Wei (赞：4)

挺有意思的一道构造题

如果 $k>1,d=0$，那么肯定无解

否则先输出 $d$，再输出 $k-1$ 个 $0$ 即可

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,d;
int main()
{
	cin>>k>>d;
	if(!d&&k>1)cout<<"No solution";
	else{cout<<d;for(int i=1;i<k;i++)cout<<0;}
	return 0;
}
```


---

## 作者：Reobrok_Kk (赞：2)

显而易见，此题是一道构造题。

拿到这题十分迷惑，看起来特别难写，于是开了题解，才知道构造题的答案满足条件即可。

题解只有一篇，于是便有了这篇题解。

#### 题意

输入 $k$，$d$。

输出一个 $k$ 位数，设它每位上的数字之和为 $sum$，如果 $sum$ 不是两位数，则求出 $sum$ 每位上的数字之和，继续分解，分解到最后等于 $d$。

和翻译差不多，就是要注意没有数满足的时候，要输出 `No solution` 。（已发讨论求修改）

#### 思路

既然只要答案满足条件，那我们直接构造一个每位上的数字之和等于 $d$ 的 $k$ 位数，但如果 $d > 9$ 的情况就不好就不好处理，但 $d \le 9$，我们可以构造一个第一位就为 $d$ 剩下 $k - 1$ 位全部为 $0$，这样既满足条件，又很好实现。

#### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0; bool flag = 1; char c = getchar();
    while (!isalnum(c)) {if (c == '-') flag = 0; c = getchar();}
    while (isalnum(c)) {x = (x << 3) + (x << 1) + c - '0'; c = getchar();}
    if (flag) return x;
    return ~(x - 1);
}
inline void write(int x) {
    if (x < 0) {putchar('-'); x = ~(x - 1);}
    int stk[30], top = 0;
    while (x) {stk[++top] = x % 10; x /= 10;}
    if (!top) putchar('0');
    while (top) {putchar(stk[top--] ^ 48);}
    return ;
}
//快读快输模板
//貌似没用
int main() {
    int k = read(), d = read();
    if (k > 1 && d == 0) //特判没有数满足的情况
        puts("No solution");
    else {
        putchar(d ^ 48); //输出d，这里是输出字符的方式，因为d <= 9，因此可以直接输出，要不然就要像快输模板输出
        while (--k) putchar('0'); //--k是先减再判，等价于循环k - 1次
        puts(""); //换行
    }
    return 0;
}

```



---

## 作者：guozhetao (赞：1)

## 题意
现有一个函数 $S(n)$ 表示 $n$ 各个数位之和；

又有 $dr(n)$ 满足：

$S(n)<10 \rightarrow dr(n)=S(n)$

$S(n)\ge 10\rightarrow
dr(n)=dr(S(n))$

给定 $k,d$， 求一个 $k$ 位数 $n$ 满足：

$dr(n)=d$

若没有数满足条件，请输出 `No solution`。

## 思路

很明显这是一道构造题。只要输出一种方法即可。

如果 $k > 1$ 且 $d = 0$，那么显而易见，肯定没解。否则输出 $d$，再输出 $k - 1$ 个 $0$ 即可满足题目要求。

构造题目推荐：[CF441C](https://www.luogu.com.cn/problem/CF441C)。

## 代码
因为爬虫挂了，我直接到 CF 上交。[CF的AC记录](https://codeforces.com/problemset/submission/355/171691779)。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int a,b;
    scanf("%d%d",&a,&b);
    if(!b and a > 1) {
        printf("No solution");
    }
    else{
        printf("%d",b);
        a--;
        while(a--) {
            printf("0");
        }
    }
}
```


---

## 作者：CQ_Bab (赞：1)

# 思路
构造题

无解 ： 如果 $k>1$ 且 $d$ 为零

否则 ： 因为 $d\le9$，所以我们先输出一个 $d$，再用 $k-1$ 个 $0$ 展位岂可，这样它就相当于一直在去零。

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,d;
int main(){
	cin>>k>>d;
	if(k>1&&d==0) {
		puts("No solution");
		return false;
	} // 无解情况 
	cout<<d;
	while(k--) cout<<0; // 用k-1个0展位 
	return false; // 完美散花 
}
```


---

## 作者：_easy_ (赞：1)

# 思路
构造题

首先判断无解的情况。当 $\texttt{k}$ 大于一且 $\texttt{d}$ 为零时无解，直接输出 $\texttt{No solution}$。

如果有解，因为 $d \leqslant 9$，所以我们在第一位直接输出 $\texttt{d}$，后面用零凑位就行了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int k,d; 
int main(){
	cin>>k>>d;
	if(k>1&&d==0){
		cout<<"No solution";
		return 0;
	}//无解
	k--;//注意要先减一，因为要体现输出一个d
	cout<<d;
	while(k--){
		cout<<0;
	}
	return 0;
}
```

---

## 作者：Starw (赞：1)

### 题面补充：

若无解，则输出 `No solution` 。

### 思路：

看到这题，我就飞快地想到了暴搜，代码如下：

```cpp
#include<bits/stdc++.h>//万能头
#define re register int
using namespace std;
int k,d,a[1005];
inline bool cheak(int sum){//判断是否符合要求的函数
	while(sum>=10){
		int x=sum;
		sum=0;
		while(x)sum+=x%10,x=10;
	}
	if(sum==d)return 1;
	else return 0;
}
inline bool cmp(int x,int y){
	return x>y;
}
inline void print(){//输出的函数
	sort(a+1,a+k+1,cmp);//为了防止有前导零先由大到小排序一下
	for(re i=1;i<=k;i++)
		printf("%d",a[i]);
}
inline void dfs(int l,int sum){
	if(l>k){
		if(cheak(sum)&&(sum!=0||(sum==0&&k==1))){//如果其成立且不是全为零的情况(位数为1除外),就输出,结束程序
			print();
			exit(0);
		}
		return;
	}
	for(re i=0;i<=9;i++){//平平无奇的深搜
		a[l]=i;
		dfs(l+1,sum+i);
	}
}
int main(){
	scanf("%d%d",&k,&d);
	dfs(1,0);
	printf("No solution");//如果程序运行到了这,就说明无解,输出"No solution"
	return 0;
}
```

[妥妥的超时。](https://www.luogu.com.cn/record/55509314)

那就优化一下吧。

我们想，如果为无解，那么 $O(k^{10})$ 就会全部运行到，就导致了超时，那我们加个特判不就好了。

我们又想，只有一种方式会导致无解，就是 $d$ 为 $0$ 且 $k$ 不为 $1$，这样，就可以打出如下特判代码：

```cpp
	if(d==0)//若 d 为 0 
		if(k==1)printf("0");//若 k 为 1 就直接输出个零 
		else printf("No solution");//否则就无解 
	else dfs(1,0);//若 d 不为 0 就深搜 
```

上方的判断也可以改一改了。

`if(cheak(sum)&&(sum!=0||(sum==0&&k==1)))` 可改为 `if(cheak(sum)&&sum!=0)` 因为 `d==0&&k==1` 在上方已经特判过了，所以不可能有 `sum==0` 的情况了。

[这就过了？!](https://www.luogu.com.cn/record/55509684)

### 代码：

完整代码我就不放了~~抄题解的照上面改就行了~~。

---

## 作者：_ouhsnaijgnat_ (赞：1)

建议红，顶多橙。

## 思路

这道题看上去一大串描述，很难懂。其实我只要 $14$ 行就对了。

这道题，怎么判断无解？肯定是如果 $k>1$ 并且 $d=0$ 就是无解。

接下来，我们直接输出 $d$，不够的再在后面补 $0$。

代码奉上。

## 代码

```cpp
#include <iostream>
using namespace std;
int k,d; 
int main(){
	cin>>k>>d;
	if(k>1&&d==0){//无解 
		cout<<"No solution";
		return 0;
	}
	cout<<d;
	for(int i=1;i<k;i++)//补0 
		cout<<0;
	return 0;
}
```


---

## 作者：xmkevin (赞：0)

首先，这道题是一道构造题。

如果 $k > 1$ 并且 $d = 0$，那么肯定无解。

否则先输出 $d$，再输出 $k - 1$ 个 $0$ 就可以了。

代码：

```
#include<iostream>
using namespace std;
int k,d;
int main()
{
	cin >> k >> d;
   	if(d == 0 && k > 1) {
    		cout << "No solution";
    	}
	else{
    		cout << d;
            	for(int i = 1; i < k; i++) cout<<0;
        }
	return 0;
}
```

---

## 作者：囧仙 (赞：0)

## 题解

容易发现， $S(n)$ 的定义就是十进制下 $n$ 的数根（即各个数位上的数字之和，进行递归处理，直到成为一位数）。由于题目只要我们找到一种方案，于是考虑构造。

- 先考虑 $d=0$ 的情况。当 $n>0$ 时，显然 $n$ 的各位数字之和大于 $0$ 。由归纳法易得 $S(n)>0$ 。因此，对于 $S(n)=0$ 的情况，$n$ 只能为 $0$ 。于是，当 $k=1,d=0$ 时结果是 $0$ ；否则无解，输出 `No solution` 。

- 否则，当 $d>0$ 时，构造 $n=\overline{\mathtt{d\underbrace{00...00}_{\textrm{共 k-1 个 0}}}}$ ，显然 $S(n)=d$ ，且 $n$ 恰好为 $k$ 位。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    int k=qread(),d=qread();
    if(d==0){
        if(k==1) puts("0"); else puts("No solution");
    } else {
        printf("%d",d); up(1,k-1,i) putchar('0'); puts("");
    }
    return 0;
}
```

---

## 作者：mnesia (赞：0)

这是一道较为简单的构造题。

首先看到 $y = \text{dr(x)}$ 是一个分段函数，其值取决于 $\text{S(x)}$ 的值。但是考虑到 $\text{dr(x)} = d$ 的解有无穷多组，其中大部分解的产生都是通过多重 $\text{S(x)}$ 嵌套而成（这类解的数字和都大于 $10$），很难模拟得出答案，因此这条思路可以近似于无法实现。

那么考虑较为简便的做法：

观察到数据范围中 $0 \leq d \leq 9$，因此可以发现可以仅通过首位（最高位）的一个有效数字及其余位的 $0$ 来达成此目的。

由此思路，实现就很简单了：首位输出 $d$，其余位输出 $0$，这样可以满足 $\text{S(x)} = d$ 的条件。

但是此外还需考虑一种情况：数据范围中提到 $d = 0$ 这种情况是可能存在的。因此对这种情况需要先行特判：如果此时 $k = 1$，即目标输出只有 $1$ 位，此时可以直接输出 $d$，即 $0$，这种情况可以并到后面的输出中。但是如果 $k > 1$，此时根据上面的思路，由于首位输出 $d$，而 $d = 0$，因此按照上面的策略输出就只有 $k$ 个 $0$，没有意义。因此此种情况下是无解的，需要输出 ``No solution``。

下面给出代码：
```cpp
#include<iostream>

using namespace std;
int k, d;
int main()
{
	cin >> k >> d;
	if(d == 0 && k > 1)
	{
		cout << "No solution";
	}
	else
	{
		cout << d;
		for(int i = 1;i < k;i++)
		{
			cout << 0;
		}
	}
	return 0;
}

```


---

## 作者：_cmh (赞：0)

目前最优解来一发题解。

这是一道**构造题**。

观察数据范围：$1\le k\le1000,0\le d\le 9$。

由题反推，题目要求 $dr(n)=d$ 这种情况，而 $0\le d\le 9$，可知最后一次的 $dr(n)\le 9$。

当 $S(n)<10$ 时，$dr(n)=S(n)$ 。所以可知最后一次的 $S(n)\le 9$。

所以可以构造出一个序列：

- 第一位是题目所求的 $d$。

- 接下来 $k-1$ 位都为 $0$。

这个序列满足题目所求，但是因为 $d$ 可能为 $0$，又因为 $0$ 不能为最高位，所以容易想出：当 $k>1,d=0$ 时，无解。

接下来是代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
#define in(x) x=read()
#define in2(x,y) x=read(),y=read()
#define F(i,x,y) for(register w i=x;i<=y;i++)
#define reF(i,x,y) for(register w i=x;i>=y;i--)
#define w int
using namespace std;
w read(){w f=1,ans=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){ans=ans*10+ch-'0';ch=getchar();}return ans*f;}
int main(){
	w in2(k,d);
	if(k>1&&d==0){
		puts("No solution");
		exit(0);
	}
	cout<<d;
	F(i,1,k-1)
		cout<<0;
    return 0;
}
```

---

