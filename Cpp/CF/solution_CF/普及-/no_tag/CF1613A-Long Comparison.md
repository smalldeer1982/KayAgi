# Long Comparison

## 题目描述

Monocarp 在一个黑板上写下了两个数。每一个数都用两个整数 $x,p$ 表示，表示其值为 $x$ 后有 $p$ 个 $0$。Monocarp 想让你比较这两个数的大小。

## 说明/提示

样例中的五组数分别为 $20\gt 19,1000=1000,1999\lt 2000,1=1,99\lt 100$。

By @[雨伞CKY](/user/415445)

## 样例 #1

### 输入

```
5
2 1
19 0
10 2
100 1
1999 0
2 3
1 0
1 0
99 0
1 2```

### 输出

```
&gt;
=
&lt;
=
&lt;```

# 题解

## 作者：Jerrlee✅ (赞：2)

## 题意
求 $\max{x_1 \times 10^{p_1},x_2 \times 10^{p_2}}$。
## 思路
套用公式：如题的两数差为 `log10(x1/x2)+p1-p2`。

具体是什么呢？其实这是科学计数法的形式，当两个数数位不同，他们的指数会不同，而指数相同时，左下方的基数越大，数越大。

`x1` 除以 `x2`，结果一定小于十（科学计数法基数在一到十之间，可取一，不可取十），这样就可以做到先判断指数大小，再判断基数大小了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        double x1,p1,x2,p2;
        cin>>x1>>p1>>x2>>p2;
        double ans;
        ans=log10(x1/x2)+p1-p2;
        if(ans==0) cout<<"="<<endl;
        else if(ans>0) cout<<">"<<endl;
        else cout<<"<"<<endl;
    }
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/64190522)

[AC记录（CF）](https://codeforces.com/contest/1613/submission/137894193)

---

## 作者：快乐的大童 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1613A)

## 题目描述
Monocarp  在一个黑板上写下了两个数。每一个数都用两个整数  $x,p$  表示，表示其值为  $x$  后有  $p$  个 0。Monocarp  想让你比较这两个数的大小。

## 思路

我们可以将这两个数转化成**科学计数法**的形式，也就是  $a\times 10^n(1\le |a|< 10,n$ 为整数 $)$  的形式，不知道科学计数法的可以[点这里](https://baike.baidu.com/item/%E7%A7%91%E5%AD%A6%E8%AE%B0%E6%95%B0%E6%B3%95/1612882?fromtitle=%E7%A7%91%E5%AD%A6%E8%AE%A1%E6%95%B0%E6%B3%95&fromid=756685&fr=aladdin)。

**如何比较两个科学计数法形式的数？**

我们假设第一个数是  $a\times 10^n$，第二个数是  $b\times 10^m$。
 
首先比较  $n$  和  $m$  的大小，较大的一方即为大数。

如果  $n=m$，这时比较  $a$  和  $b$，较大的一方即为大数。

否则这两个数相等。

最后一点就是，上文中的  $a$  和  $b$  都要用  **double**  存。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int R(){//快读
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
int result(int x){
  	//转化成科学计数法形式时判断n需要除10的几次方，要除的也就是10的这个数的总位数-1次方。
  	//这个函数求的是n的总位数
	int res=0; 
	while(x){
		res++;
		x/=10;
	}
	return res;
} 
int main(){
	int t=R();
	while(t--){
		int n=R(),k=R(),n1=R(),k1=R();
		int p=result(n);
		double q=n*1.0/(int)pow(10,p-1);//将第一个数转化为科学计数法形式
		int p1=result(n1);
		double q1=n1*1.0/(int)pow(10,p1-1);//将第二个数转化为科学计数法形式
		k+=p-1;//将n除的数再乘回来，下一行也是一样
		k1+=p1-1;
  		//比较两个科学计数法形式的数的大小
		if(k>k1||(k==k1&&q>q1)) printf(">\n");
		else if(k<k1||(k==k1&&q<q1)) printf("<\n");
		else printf("=\n");
	} 
}
```


---

## 作者：szkzyc (赞：1)

此题一看就非常适合用字符串处理。

思路：先比较两个数的长度，如果不一样就直接输出。否则就给长度短的补 $0$ 直到长度一样，然后直接用大于号小于号比较即可。

我们需要方便的 string 类。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF INT_MAX
#define debug puts("qwq")
using namespace std;

int main(){
	int t;
	cin >> t;
	while(t--){//t组数据 
		string x1, x2;//x1 x2当字符串处理 
		int p1, p2;//p1 p2整形即可 
		cin >> x1 >> p1 >> x2 >> p2;
		int len1 = x1.size();//x1的长度 
		int len2 = x2.size();//x2的长度 
		if(len1 + p1 > len2 + p2) puts(">");//第一个数长度比第二个数大就输出> 
		else if(len1 + p1 < len2 + p2) puts("<");//第一个数长度比第二个数小就输出< 
		else{//长度一样 
			if(len1 > len2){//x1的长度比x2的长 
				for(int i = len2; i < len1; i++) x2 += "0";//给x2补0直到与x1的长度相同 
			}
			else if(len2 > len1){//x2的长度比x1的长 
				for(int i = len1; i < len2; i++) x1 += "0";//给x1补0直到与x2的长度相同 
			}//直接用大于小于号比较 
			if(x1 > x2) puts(">"); //x1大 
			else if(x2 > x1) puts("<");//x2大 
			else puts("=");//一样 
		}
	} 
	return 0;
}

```


---

## 作者：IYSY2009I (赞：1)

这道题调了我一个小时你们信吗。

这道题的做法有很多，我来讲两种：

首先是一种我写挂的（就是这个写法浪费了我 40 分钟）：

我们可以看到，如果我们正常存这个数的话，肯定会爆 long long ，所以我们就自然想到了高精，我们用一个字符数组（ string 也可以）来存储两个数，然后从高位向低位依次比较大小。

但是这个时候我们来看一下数据范围：

$1 \le t \lt 10^4,1 \le x_1,x_2 \le 10^6,0 \le p_1,p_2 \le 10^6$

我们很容易地发现，这串代码的时间复杂度为 O(tp)，是会 TLE 的，事实也是如此。

那么，我们应该如何优化呢？

我们来观察几个数：

2|0 10|00 1999  1 99

19  100|0 2|000 1 1|00

我们可以很~~不~~显然地发现，如果我们设 $x_1$ 的位数为 $len(x_1)$ ， $x_2$的位数为 $len(x_2)$ ，那么我们只需要判断前 $\max(len(x_1),len(x_2))$ 位数就可以了。

> 特别提醒：本人并没有用本思路通过该题，大佬如果发现该思路有错误可以指出。

在这种方法没过之后，我玩了几把游戏让自己冷静下来，然后有了第二种思路。

在此感谢 用户编号 448884 ，否则我可能真做不出来。

他说了什么呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/mf9h3413.png)

那么接下来我们来由这个式子推一下：

前置知识：加减乘除乘方

我们这里假设 $p_1>p_2$

$x_1 \times (10^{p_1})???x_2  \times (10^{p_2})$ 

$x_1 \times (10^{p_1-p_2})???x_2 \times (10^{p_2-p_2})$ 

$x_1 \times (10^{p_1-p_2})???x_2 \times (10^0)$ 

$x_1 \times (10^{p_1-p_2})???x_2 \times 1$

$x_1 \times (10^{p_1-p_2})???x_2 $

那么这道题相当于求 $x_1 \times (10^{p_1-p_2})$ 与 $x_2$ 的大小的，时间复杂度就变成了 O(t($p_1-p_2$))。

那么显然地，我们可以先将 $x_1,x_2$ 用字符数组（或字符串）的方式读进来，然后判断两个数的位数，因为 $1 \le x_1,x_2 \le 10^6$ ，所以 $\max p_1-p_2 = 6$ ，相当于一个常数，所以我们再把读进来的两个数转化为 long long 类型（转 int 可能会炸，没试过，大家可以自己试试），此时真正的两个数已经同时除以了 $10^{p_2}$，就可以愉快地过掉这道题了。

这道题大概是红题或橙题难度（所以我说那么详细干嘛）。

附上本蒟蒻的 AC 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void cf(){
	char a[1000020];
	char b[1000020]; 
	int za,zb;
	cin>>a;
	za=read();
	cin>>b;
	zb=read();
	int cnta=strlen(a);
	int cntb=strlen(b);
	if(cnta+za>cntb+zb){ //先进行位数判断，如果位数都不相同就没必要继续了
		printf(">\n");
		return;
	}
	if(cnta+za<cntb+zb){
		printf("<\n");
		return;
	}
	long long aa=0,bb=0;
	for(int i=0;i<=cnta-1;i++) //转 long long(看不懂的萌新可以自己手动模拟一下)
		aa=aa*10+a[i]-'0';
	for(int i=0;i<=cntb-1;i++)
		bb=bb*10+b[i]-'0';
	if(zb>za) for(int i=1;i<=zb-za;i++) //乘上 10^(p1-p2)（懒得用快速幂了）
			bb*=10;
	if(za>zb) for(int i=1;i<=za-zb;i++)
			aa*=10;
	if(aa>bb){
		printf(">\n");
		return;
	}
	if(aa<bb){
		printf("<\n");
		return;
	}
	printf("=\n");
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0; //画上完美的句号
}
```
over.

---

## 作者：徐晨轩✅ (赞：0)

我们知道，两个数同时除以某个数，它们的大小关系不变。在本题里，我们先把这两个数同时除以 $\min(p1,p2)$，使得两个数中的一个数变得较小。接着，如果另一个数的 $p$ 值很大（$\ge 7$），就可以直接判定是 `>` 还是 `<`，因为较小的数一定 $<10^6$，而较大的数一定 $\ge 10^7$。如果另一个数的 $p$ 值不大的话，就可以直接将这两个数还原并判断了（此时的 $p1,p2$ 都 $<7$，时间上完全没问题）。

AC Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,x1,x2,p1,p2,mn;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> x1 >> p1 >> x2 >> p2;
		mn=min(p1,p2);
		p1-=mn;p2-=mn;
		if(p1>=7)cout << ">" << endl;
		else if(p2>=7)cout << "<" << endl;
		else
		{
			for(int i=1;i<=p1;i++)x1*=10;
			for(int i=1;i<=p2;i++)x2*=10;
			if(x1<x2)cout << "<" << endl;
			else if(x1>x2)cout << ">" << endl;
			else cout << "=" << endl;
		}
	}
	return 0;
}

---

## 作者：Aiopr_2378 (赞：0)

### 题目大意：


比较两个数的大小，每一个数都用两个整数 $x,p$ 表示，表示其值为 $x$ 后有 $p$ 个 $0$。

其中，$1\leq x\leq 10^{6},0\leq p\leq 10^{6}$ 

### 解题思路：

对于每个$x$，我们不知道它是几位数，所以不方便比较。但是我们可以将这几个数用**科学计数法**表示出来，显而易见，很容易比较。

科学计数法：把一个数表示成形如 $a\times 10^n$ 的格式，其中，$1\leq a<10,n\in\mathbb{N}$

注意，用科学计数法表示出来的数 $a$ 是浮点数，所以要用 `double` 存储变量，同时，每移一位，相应地对 $p$ 进行加一操作。

### 参考代码：

```cpp
#include<iostream>
using namespace std;
int t,x1,x2,p1,p2;
int main(){
    cin>>t;
    while(t--){
        cin>>x1>>p1>>x2>>p2;
        double a1=x1,a2=x2;
        while(a1>=10){//转化成科学计数法的形式
            a1/=10;
            p1++;
        }
        while(a2>=10){
            a2/=10;
            p2++;
        }
        if(p1>p2) cout<<">"<<endl;//普普通通的比较
        if(p1==p2){
            if(a1>a2) cout<<">"<<endl;
            if(a1==a2) cout<<"="<<endl;
            if(a1<a2) cout<<"<"<<endl;
        }
        if(p1<p2) cout<<"<"<<endl;
    }
    return 0;
}
```


---

## 作者：智子 (赞：0)

## 题意

Monocarp 在一个黑板上写下了两个数。每一个数都用两个整数 $x,p$ 表示，表示其值为 $x$ 后有 $p$ 个 $0$。

Monocarp 想让你比较这两个数的大小。

## 思路

首先，在两个数后面减去数目相同的 $0$ 不会影响这两个数的大小关系，所以我们可以先将两个 $p$ 都减去其中较小的值，这样其中一个 $p$ 是 $0$。此时如果另一个 $p$ 大于 $10$，那么我们就不用继续比较了，因为 $x$ 最多是 $10^6$ 不可能有 $10$ 位。

否则，此时两个数都小于 $10^{16}$，完全可以一位一位塞进两个数组里再比较。

## 代码

```cpp
#include<cstdio>
#include<cmath>
using namespace std;

const int MAXN = 1000000 + 100;

int a[MAXN], b[MAXN];

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        int x1, p1, x2, p2;

        scanf("%d%d%d%d", &x1, &p1, &x2, &p2);
        if(p1 <= p2) {
            p2 -= p1;
            p1 = 0;
        } else if(p1 > p2) {
            p1 -= p2;
            p2 = 0;
        }
        if(fabs(p1 - p2) > 10) {
            if(p1 < p2) {
                printf("<\n");
            } else {
                printf(">\n");
            }
            continue;
        }
        int len1 = 0, len2 = 0;
        for(int i = 1; i <= p1; i++) {
            a[++len1] = 0;
        }
        int t = x1;
        while(t > 0) {
            a[++len1] = t % 10;
            t /= 10;
        }

        for(int i = 1; i <= p2; i++) {
            b[++len2] = 0;
        }
        t = x2;
        while(t > 0) {
            b[++len2] = t % 10;
            t /= 10;
        }
        if(len1 < len2) {
            printf("<\n");
            continue;
        } else if(len1 > len2) {
            printf(">\n");
            continue;
        }
        int flag = 0;
        for(int i = len1; i >= 1; i--) {
            if(a[i] < b[i]) {
                flag = 1;
                break;
            } else if(a[i] > b[i]) {
                flag = -1;
                break;
            }
        }
        if(flag == 0) {
            printf("=\n");
        } else if(flag == 1) {
            printf("<\n");
        } else {
            printf(">\n");
        }
    }

    return 0;
}

```

---

## 作者：雨伞CKY (赞：0)

# 题目分析
如果 $n$ 可以用 $x,p$ 表示，则有 $n=10^{p}x$。所以**对于每组数据，你需要比较 $n_{1}=10^{p_{1}}x_{1}$ 和 $n_{2}=10^{p_{2}}x_{2}$ 的大小。**

两数同时除以 $10^{\min (p_{1},p_{2})}$，得：

$$
n_{1}'=10^{p_{1}-\min (p_{1},p_{2})}x_{1},n_{2}'=10^{p_{2}-\min (p_{1},p_{2})}x_{2}
$$

$n_{1}'$ 和 $n_{2}'$ 中，必有至少一个数为 $10^{0}k=k$，其中 $k$ 的值为 $x_{1}$ 或 $x_{2}$。

考虑到 $1\leq x_{1},x_{2}\leq 10^{6}$，可以分为以下三种情况：
- 如果 $p_{1}-\min (p_{1},p_{2})\geq 7$，则 $n_{1}'\geq 10^{7}\gt n_{2}',n_{1}\gt n_{2}$。
- 如果 $p_{2}-\min (p_{1},p_{2})\geq 7$，则 $n_{1}'\lt 10^{7}\leq n_{2}',n_{1}\lt n_{2}$。
- 否则，可以直接计算 $n_{1}'$ 和 $n_{2}'$ 并比较。

# 代码
```cpp
#include <algorithm>
#include <cstdio>
using namespace std;

int t;
long long int x1,p1,x2,p2,tmp;

int main(){
	scanf("%d",&t);
	for (int i = 1;i <= t;i++){
		scanf("%lld%lld%lld%lld",&x1,&p1,&x2,&p2);
		tmp = min(p1,p2);
		p1 -= tmp,p2 -= tmp;
		if (p1 >= 7){
			printf(">\n");
		}
		else if (p2 >= 7){
			printf("<\n");
		}
		else{
			while (p1 > 0){
				x1 *= 10;
				p1--;
			}
			while (p2 > 0){
				x2 *= 10;
				p2--;
			}
			if (x1 < x2) printf("<\n");
			else if (x1 > x2) printf(">\n");
			else printf("=\n");
		}
	}
	return 0;
}
```

---

## 作者：zbk233 (赞：0)

## 题意简述

共 $t$ 次操作，每次给定两个数，每个数用 $x,p$ 表示，表示其值为 $x$ 后有 $p$ 个 $0$ 。

要求求出这两个数的大小关系。

## 解题思路

 $p\le10^6$，肯定无法用整数来表示这两个数。而若是用高精度，会有超时的风险。
 
我们都知道，确定一个数末尾连续 $0$ 的个数，再确定这个数除末尾的连续 $0$ 以外的数字，就能知道这个数与另外的数的大小。

但是，题目给出的 $x$ 可能是会有末尾的 $0$ 的。

例如：

```
10  2

100 1

810 0
```

我们就需要把 $x$ 末尾的 $0$ 去掉，再让 $p$ 加上 $x$ 末尾连续 $0$ 的个数就行了。

这样就可以把上面的例子转化为：

```
1000 0

1000 0

81  1
```

那么，就可以求出两数的大小关系了。

## 参考代码


```cpp
#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t, x1, x2, p1, p2;
	cin >> t;
	while (t--)
	{
		cin >> x1 >> p1 >> x2 >> p2;
		while (x1 % 10 == 0)
		{
			x1 /= 10;
			p1++;
		}
		while (x2 % 10 == 0)
		{
			x2 /= 10;
			p2++;
		}
		if ((p1 > p2) || (p1 == p2 && x1 > x2))
		{
			cout << ">\n";
		}
		else if ((p1 < p2) || (p1 == p2 && x1 < x2))
		{
			cout << "<\n";
		}
		else
		{
			cout << "=\n";
		}
	}
	return 0;
}
```


---

## 作者：Fa1thful (赞：0)

### 一、题意
给定两个数的 `x` 和 `p`，这两个数为 `x` 后面跟着 `p` 个 `0`，比较这两个数的大小。

### 二、分析
首先想到的第一个思路就是暴力构造出这两个数分别是什么，然后逐位比较。但是因为 $1 \le p \le 10^6$，而且会有 $1 \le t \le 10^4$组数据，所以整体的时间复杂度就是 $p*t$，就是 $10^{10}$，肯定会 TLE。所以我们考虑下一个思路

首先因为 $x \le 10^6$，所以整个大整数的非末尾 $0$ 部分只有最多 $6$ 位，而且 $0$ 的部分在比较的过程中只会影响位数，也就是说在两个大整数位数相同的情况下。$p$ ，也就是 $0$ 的个数，不会对两数的大小产生任何影响。但是我们考虑到也会出现两个数的 $x$ 的位数不同，但是总位数相同的情况，这样只需要给 $x$ 少的位数补 $0$ 即可。而且当 $x$ 位数少的数且这个数的$p$大的时候才会出现总位数相同的情况，所以可以证明这种情况是一定可以补 $0$ 的。

### 三、代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int a[1000010];  //记录第一个数x倒过来的位数 
int b[1000010];  //记录第二个数x倒过来的位数 
int sz[1000010]; //记录第一个数x位数 
int sz1[1000010];//记录第二个数x位数 
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		for (int i = 0; i <= 10; i++)     //因为对结果只会有x的位数产生影响，所以只需要用到前6位，这也是不TLE的关键 
		{
			a[i] = b[i] = sz[i] = sz1[i] = 0;     //初始值 
		}
		int x, p, x1, p1;
		cin >> x >> p;
		cin >> x1 >> p1;    //输入 
		int now = x, now1 = x1;    //替身 
		int w = 0, w1 = 0;    //记录每个数x的位数 
		while (now > 0)
		{
			w++;
			a[w] = now % 10;      //拆位 
			now /= 10;
		}
		for (int i = w; i >= 1; i--)
		{
			sz[w - i + 1] = a[i];    //倒过来将第一个数的每一位存在数组里 
		}
		while (now1 > 0)
		{
			w1++;
			b[w1] = now1 % 10;//拆位 
			now1 /= 10;
		}
		for (int i = w1; i >= 1; i--)
		{
			sz1[w1 - i + 1] = b[i];//倒过来将第二个数的每一位存在数组里 
		}
		if (x == x1 && p == p1)
		{
			cout << "=" << endl;   //如果都相等那么一定相等 
			continue;
		}
		if (p == p1)   //如果0的位数相同，x大的大 
		{
			if (x > x1) cout << ">" << endl;
			if (x == x1) cout << "=" << endl;
			if (x < x1) cout << "<" << endl;
			continue;
		}
		if (x == x1) //如果x相同，位数多的大 
		{
			if (p > p1) cout << ">" << endl;
			if (p == p1) cout << "=" << endl;
			if (p < p1) cout << "<" << endl;
			continue;
		}
		int ws = p + w, ws1 = p1 + w1;   //计算总位数 
		if (ws > ws1)   //位数多的大 
		{
			cout << ">" << endl;
			continue;
		}
		if (ws < ws1)//位数少的小 
		{
			cout << "<" << endl;
			continue;
		}
		if (ws == ws1)   //如果位数相同 
		{
			int jiba = 0;    //是否已经判断出大小 
			for (int i = 1; i <= max(w, w1); i++)   //逐位比较，不够补0 
			{
				if (sz[i] > sz1[i])
				{
					cout << ">" << endl; 
					jiba = 1;
					break;
				}
				if (sz[i] < sz1[i])
				{
					cout << "<" << endl;
					jiba = 1;
					break;
				}
			}
			if (jiba == 0)   //一直没比出来，说明相等，输出= 
			{
				cout << "=" << endl;
			}
		}
	}
	return 0;
}
```
谢谢观赏

---

## 作者：Kris_hukr (赞：0)

### 分析

根据小学数学，比较两个数可以首先比较两个数的位数，位数大的一定更大。

考虑到虽然数很大，但是有效数位却小得可怜，因此处理完 $x$ 的位数后也不需要什么复杂的操作，用实数比较即可。

### 代码

仅给出部分实现，请读者自行补全。

```cpp
double x1 = read<int>(), p1 = read<int>();
double x2 = read<int>(), p2 = read<int>();

while (x1 > 9) {
    x1 /= 10;
    p1++;
}
while (x2 > 9) {
    x2 /= 10;
    p2++;
}

if (p1 < p2) {
    std::cout << '<' << '\n';
} else if (p1 > p2) {
    std::cout << '>' << '\n';
} else {
    if (x1 < x2) {
        std::cout << '<' << '\n';
    } else if (x1 > x2) {
        std::cout << '>' << '\n';
    } else {
        std::cout << '=' << '\n';
    }
}
```



---

## 作者：heaksicn (赞：0)

## 1 题意
给定两个数 $x_1* 10^{p^1}$ 和 $x_2* 10^{p^2}$ ，比较大小。
多组数据。
## 2 思路
乍一看很像科学计数法。  
但 $x_1,x_2\leq 10^6$ ，所以我们需要将其转换成科学计数法。  
如果转换后 $x_1=x_2,p_1=p_2$ ，那么输出等于。  
如果 $p_1>p_2$ 或者 $p_1=p_2$ 且 $x_1>x_2$ ，输出大于。  
否则输出小于。  
时间复杂度 $O(T\log x)$ 。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
double x[5];
int main(){
	cin>>n;
	while(n--){
		for(int i=1;i<=4;i++) cin>>x[i];
		while(x[1]>=10){//转换成科学计数法
			x[1]/=10;
			x[2]++;
		}
		while(x[3]>=10){
			x[3]/=10;
			x[4]++;
		}
		if(x[1]==x[3]&&x[2]==x[4]){//相等
			cout<<"=\n";
			continue;
		}
		if(x[2]>x[4]||(x[2]==x[4]&&x[1]>x[3])){//大于
			cout<<">\n";
			continue;
		}
		if(x[2]<x[4]||(x[2]==x[4]&&x[1]<x[3])){//小于
			cout<<"<\n";
		}
	}
    return 0;
}
```


---

## 作者：BigSmall_En (赞：0)

## 题意描述

给定 $n$ 个询问，每个询问四个数 $a_1,p_1,a_2,p_2$ ，比较 $a_1\times 10^{p_1}$ 和 $a_2\times 10^{p_2}$ 的大小。 （数均 $\leq 10^6$ ）

## 题解

由于 $p_1,p_2$ 很大，可以比较自然地想到取对数，再比较的方法，由于都是乘上 $10^p$ 次方，则取以十为底的对数。然后利用作差法比较大小，即：

$$
\lg{(a_1\times 10^{p_1})}-\lg{(a_2\times 10^{p_2})}=\lg{\frac{a_1}{a_2}}+p_1-p_2
$$

只需要比较 $\lg{\frac{a_1}{a_2}}+p_1-p_2$ 与 $0$ 的大小即可，若大于 $0$ ，则输出 ${a_1}\times 10^{p_1}$ 大，为 $0$ 则相等。

对于 $\lg$ ，可以直接调用 `cmath` 库中的 `log10` 函数。

## 代码

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        int a1,t1,a2,t2;double k;
        scanf("%d%d%d%d",&a1,&t1,&a2,&t2);
        k=log10((double)a1/(double)a2);
        if(t1+k>t2)puts(">");
        else if(t1+k==t2)puts("=");
        else puts("<");
    }
    return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

## 题意
一个整数 $x$，后面有 $p$ 个 $0$。

现在有两个这样的数，求那个数更大，第一个更大输出 `>`，第二个更大输出 `<`，否则为 `=`。
## 思路
求出 $x_1$ 的位数 $f_1$，$x_2$ 的位数为 $f_2$

如果 $f_1+p_1>f_2+p_2$，输出 `>`；如果 $f_1+p_1<f_2+p_2$，输出 `<`，这是因为：位数多的数就大。此时若 $f_1>f_2$，就在 $x_2$ 后面加 $0$，$p_2\gets p_2-1$，若 $p_2$ 为 0 就结束；若 $f_1<f_2$，就在 $x_1$ 后面加 $0$，$p_1\gets p_1-1$，若 $p_1$ 为 $0$ 就结束。此时若 $f_1=f_2$ 仍然要结束。

此时后面的 $0$ 一样多，我们只需要判断 $x$ 的值即可：若 $x_1>x_2$，输出 `>`；若 $x_1<x_2$，输出 `<`；否则输出 `=`。
## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	scanf("%d",&t);
	for(int i=1,x1,x2,p1,p2;i<=t;++i){
		scanf("%d%d%d%d",&x1,&p1,&x2,&p2);
		while(x1%10==0)
			x1/=10,++p1;
		while(x2%10==0)
			x2/=10,++p2;
		int p=x1,q=x2,f1=0,f2=0;
		while(p){
			++f1;
			p/=10;
		}
		while(q){
			++f2;
			q/=10;
		}
		if(f1+p1>f2+p2)
			puts(">");
		else if(f1+p1<f2+p2)
			puts("<");
		else{
			while(f1!=f2){
				if(f1<f2){
					if(!p1)
						break;
					++f1;
					x1*=10,--p1;
				} else{
					if(!p2)
						break;
					++f2;
					x2*=10,--p2;
				}
			}
			if(x1>x2)
				puts(">");
			else if(x1<x2)
				puts("<");
			else
				puts("=");
		}
	}
	return 0;
}
```

---

## 作者：Skylmt (赞：0)

思路很简单

就是优先比较 $p_1$ 和 $p_2$ ,再比较 $x_1$ 和 $x_2$

注意要先把 $x_1$ 和 $x_2$ 尾部的 $0$ 挪到 $p_1$ 和 $p_2$ 上

code:
```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#define register
typedef unsigned long long ull;
typedef long long ll;
using namespace std;


auto solve()
{
	double x1, x2, y1, y2;
	cin>>x1>>x2>>y1>>y2;
	while(x1>=10) x1/=10, x2++;
	while(y1>=10) y1/=10, y2++;
	if(x2!=y2)
	{
	    if(x2>y2) return ">";
	    else return "<";
	} 
	if(x1==y1) return "=";
	if(x1>y1) return ">";
	return "<";
}

int main()
{
	int t;
	t=read();
	while(t--)
	{
		cout << solve() << '\n';
	}
 } 
```


---

