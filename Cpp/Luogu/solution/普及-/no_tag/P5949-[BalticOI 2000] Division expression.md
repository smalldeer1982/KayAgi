# [BalticOI 2000] Division expression

## 题目描述

除法表达式有如下的形式:  

$X_1/X_2/X_3.../X_n$ ，其中 $X_i$ 是正整数且 $X_i\le 10^9$， 除法表达式应当按照从左到右的顺序求。

例如表达式 $1/2/1/2$的值为 $1/4$。

但可以在表达式中加入括号来改变计算顺序，例如 $(1/2)/(1/2)$ 的值为 $1$.现给出一个除法表达式 $E$，求是告诉是否可以通过增加括号来使其结果为整数。

## 说明/提示

对于 $100\%$ 的数据，$1\le D\le10$，$1\le n\le10^4$。

## 样例 #1

### 输入

```
2
4
1
2
1
2
3
1
2
3```

### 输出

```
YES
NO```

# 题解

## 作者：清风雪月 (赞：6)

第一篇可提交的题解，望通过。

下面切入正题。

------------
通过找规律和观察我们发现，要想得到整数，我们应该要选择输入的第二个数，也就是第一个分数的分母作为整体的分母。

那么怎么判断是否可行呢？我们就需要用到约分，即把两个数同时除以它们的最大公约数。

除完之后，如果最终的结果不是一，除不干净，那么就说明它不是整数。

有了思路我们就可以做了。

------------
```
//~柠月~
#include<bits/stdc++.h>
using namespace std;
int d,n,a[10001],q;//q是第二个数
int gcd(int a,int b)//约分
{
	if(b==0)return a;
	return gcd(b,a%b);
}
int main()
{
	cin>>d;
	for(int i=1;i<=d;i++)
	{
		memset(a,0,sizeof(a));//把a数组初始化
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		q=a[2];
		for(int i=1;i<=n;i++)
		{
			if(i!=2)q/=gcd(q,a[i]);
		}
		if(q==1)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
    return 0;
}
```
不要直接抄代码哦，至少先看看分析吧。

---

## 作者：cq_loves_Capoo (赞：4)

这题楼上说过了，只要第二个数除以别的数后能等于0，就输出YES，否则输出NO。  
现在，我就按照楼上的方法，写一个C++版的程序！  
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstdlib>
#include<cstring>//头文件不解释那么多
using namespace std;
int m;//定义数据组数
int gcd(int a,int b)//最小公倍数函数
{
	if(a%b==0) return b;//辗转相除法，如果两数的余数为0，直接返回b。
	else return gcd(b,a%b);//否则，递归b和a%b。
}
void print()//处理每个数据的函数
{
	int s[111111];//定义数组
	memset(s,0,sizeof(s));//清零数组
	int n=0;//有n个数
	scanf("%d",&n);//输入n
	if(n==1) //特判，如果n是一，直接输出yes
	{
		scanf("%d",&s[1]);
		printf("YES");
		return;//退出，不执行下面的语句
	}
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);//如题，输入n个数
	for(int i=1;i<=n;i++)
	{
		if(i==2) continue;//如果n等于2，直接跳过此次循环
		if(s[i]==0) continue;//如果等于0，也跳过（我就被这个坑了）
		s[2]=s[2]/gcd(s[2],s[i]);//第二个数与第i个数除后的商
		if(s[2]==1) //如果第二个数等于1，直接结束循环，并输出YES
		{
			printf("YES\n");
			return;
		}
	}
	if(s[2]==1) printf("YES\n");//判断第二个数是否等于1，输出YES
		else printf("NO\n");//否则输出NO
	return;
}
int main()
{
	scanf("%d",&m);//m组数据
	for(int i=1;i<=m;i++) print();//每个数据的执行
}

```


---

## 作者：Great_Influence (赞：3)

容易发现，第二个数字只可能是分母的一部分。

那么我们能够得到的最优答案只可能是分母为第二个数， 其他所有数字做分子。

容易发现， 当我们用括号将第二个数字和后面所有数字全部括起来的时候， 我们正好可以取到这个最优答案。

那么只要判断这个答案是否合法就行了。

我们用第二个数字依次除掉和其他数字的 $\gcd$ ，然后看看最后这个数字是否变成 $1$ 即可。 $\gcd$ 可以用系统内置的。

时间复杂度 $O(n\log n)$ 。

核心代码:
```cpp
read(n);
read(cr);
static int pc;
if(n == 1) puts("YES");
else
{
	read(pc);
	pc /= __gcd(pc, cr);
	Rep(i, 3, n) read(cr), pc /= __gcd(pc, cr);
	puts(pc == 1 ? "YES" : "NO");
}
```

---

## 作者：ez_lcw (赞：2)

这是一个经典 ~~CF题~~ 结论题。

先把结论摆出来：除了第一个除号外，可以通过增加括号把第二个除号以后的任意一个除号改成乘或除。

证明：

比如现在是 $a\div b$，我想要改成 $a\times b$，应该如何增加括号？

因为这不是第一个除号，所以在 $a$ 前面必定还有一个除号，也就是类似这样的形式：$\cdots\div a\div b$。

那么我们可以在 $a$ 前面加一个左括号变成这样：$\cdots\div (a\div b\cdots)$。

至于右括号在哪里，这无关紧要，因为这对左右括号肯定包含了 $a$、$b$ 之间的那个除号。

既然包含它，拆括号后就要变号：$\cdots\div (a\div b\cdots)=\cdots\div a\times b\cdots$。

这样我们就能把除变成乘了。

既然有了这个结论，考虑如何做才能使结果为整数。

为了让结果是整数，肯定是要让每个除号都变成乘最好，但是第一个除号不能变。

也就是说，我们可以贪心地把原式变成：$X_1/X_2\times X_3\times X_4 \times \cdots \times X_n$。

那么我们只用看 $X_1\times X_3\times X_4\times \cdots\times X_n$ 是否是 $X_2$ 的倍数就好了。

因为这个数，所以我们要边输入边约分。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^'0');
		ch=getchar();
	}
	return x*f;
}

int t,n;

int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

int main()
{
	t=read();
	while(t--)
	{
		n=read();
		if(n<2)
		{
			read();
			puts("YES");
			continue;
		}
		int tmp=read(),b=read();
		int d=gcd(tmp,b);
		b/=d;
		for(int i=3;i<=n;i++)
		{
			tmp=read();
			int d=gcd(tmp,b);//用gcd约分
			b/=d;
		}
		if(b==1) puts("YES");
		else puts("NO");
	}
	return 0;
}
/*
1
5
7 6 3 5 3
*/
/*
4
32
1 1073741824 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
31
1 1073741824 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
31
1 1073741824 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
32
1 1073741824 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
*/
```

---

## 作者：qwq自动机 (赞：1)

### Part 1 题意理解 + 简述

多组数据。对于每组数据，给出 $n$ 和 $n$ 个整数 $X_1 \sim X_n$，询问能否通过“加括号的方式”改变式子 $X_1\div X_2\div\cdots\div X_n$ 除法运算顺序使得结果是整数。

### Part 2 思路分析

假设改变顺序后的式子化简成分数为 $\dfrac{A}{B}$，则容易知道 $X_1$ 是 $A$ 的一部分，$X_2$ 是 $B$ 的一部分。

同时我们又可以知道我们完全可以通过改变运算顺序使得 $B=X_2$ 且 $A=X_1\times X_3\times X_4\times \cdots \times X_n$，因为对于每一个 $2\leq i\lt n$ 的 $X_i$ 都有她前面存在一个除号，所以对于每一个这样的 $X_i$，可以这样构造：$\cdots\div(X_i\div X_{i+1}\div\cdots)=\cdots\div X_i\times X_{i+1}\div\cdots$，这样就可以将原本在分母（即 $B$）中的 $X_{i+1}$ “翻”到分子上（即 $A$ 中）。所以我们是可以构造出一种运算的顺序使得最终得到的式子为 $\dfrac{X_1\cdot\prod_{i=3}^nX_i}{X_2}$。容易证明这是一种“最优”的情况（即如果这样不行，其他的运算顺序也不可能做到）。

那么现在的问题就在于判断 $X_2$ 是否整除上面的那个分子。很显然我们可以使用与小学学的“分数约分”相似的思想，对于分子中所有的 $X_i$，将分母 $X_2$ 除掉 $\gcd(X_2,X_i)$，消掉能消掉的部分。那么在除完所有的分子之后判断一下分母 $X_2$ 除掉剩下的值是否是 $1$ 就行了！

### Part 3 代码

有了思路就很容易写出代码。

C++：

```cpp
#include <iostream>
using std::cin;
using std::cout;
// 辗转相除求gcd
int gcd(int m, int n) { return n ? gcd(n, m % n) : m; }
int d;
int x[100010];
int main()
{
    cin >> d;
    while (d--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> x[i];
        x[2] /= gcd(x[2], x[1]);
        for (int i = 3; i <= n; i++)
            x[2] /= gcd(x[2], x[i]);
        if (x[2] == 1)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
```

Python：

```py
def gcd(n, m): # 辗转相除
    if m == 0:
        return n
    else:
        return gcd(m, n % m)

d = int(input())
for i in range(d):
    n = int(input())
    x = []
    for j in range(n):
        x.append(int(input()))
    x[1] = x[1] / gcd(x[1], x[0])
    for j in range(2, n):
        x[1] = x[1] / gcd(x[1], x[j])
    if x[1] == 1:
        print("YES")
    else:
        print("NO")

```

嗯，差不多就这样吧。还有：不要抄题解！

---

## 作者：雨伞CKY (赞：0)

# 题目分析
无论如何添加括号，前两个数总会有且仅有以下几种情况：
- $X_{1}/X_{2}/\dotsc$，此时 $X_{1}$ 是被除数，$X_{2}$ 是除数。
- $X_{1}/(X_{2}/\dotsc)$，此时 $X_{1}$ 是被除数，$X_{2}$ 是除数。
- $(X_{1}/X_{2})/\dotsc$ 或 $(X_{1}/X_{2}/\dotsc)/\dotsc$，此时 $X_{1}$ 是被除数，$X_{2}$ 是除数。

综上所述，$X_{1}$ 总为被除数，$X_{2}$ 总为除数。

所以，我们如需使最终结果为整数，应该使分母只有 $X_{2}$，其余数均为被除数。考虑 $1\leq n\leq 10^{4},X_{i}\leq 10^{9}$，应使用最大公因数约分。

# 代码
## C++14
```cpp
#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;

long long int fast_read(){
	long long int res = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)){
		res = (res << 3) + (res << 1) + (ch ^ '0');
		ch = getchar();
	}
	return res;
}

long long int gcd(long long int a,long long int b){
	if (a < b) swap(a,b);
	return ((b == 0) ? a : gcd(a % b,b));
}

long long int t,n,A1,A2,tmp,ans;

int main(){
	t = fast_read();
	for (int i = 1;i <= t;i++){
		n = fast_read();
		A1 = fast_read();
		A2 = fast_read();
		ans = A2 / gcd(A1,A2);
		for (int j = 3;j <= n;j++){
			tmp = fast_read();
			ans /= gcd(ans,tmp);
		}
		if (ans == 1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

## C++17
C++17 在头文件 numeric 中，新增了函数 `std::gcd`。若 $m=0$ 且 $n=0$，返回 $0$。否则返回 $\lvert m\rvert$ 与 $\lvert n\rvert$ 的最大公因数。

```cpp
#include <cctype>
#include <cstdio>
#include <iostream>
#include <numeric>
using namespace std;

long long int fast_read(){
	long long int res = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)){
		res = (res << 3) + (res << 1) + (ch ^ '0');
		ch = getchar();
	}
	return res;
}

long long int t,n,A1,A2,tmp,ans;

int main(){
	t = fast_read();
	for (int i = 1;i <= t;i++){
		n = fast_read();
		A1 = fast_read();
		A2 = fast_read();
		ans = A2 / gcd(A1,A2);
		for (int j = 3;j <= n;j++){
			tmp = fast_read();
			ans /= gcd(ans,tmp);
		}
		if (ans == 1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Leasier (赞：0)

显然，无论如何加括号，$X_1$ 一定在分子上，$X_2$ 一定在分母上，其他位任意。

在理想情况下，$X_3, X_4, \cdots, X_n$ 均在分子上，即：$\dfrac{X_1 \displaystyle\prod_{i = 3}^n X_i}{X_2}$。我们只需用 gcd 约分并判断此时的结果是否为整数即可。

最后特判 $n = 1$ 的情况即可。时间复杂度为 $O(dn \log \max(X_1, X_2, \cdots, X_n))$。

代码：
```cpp
#include <stdio.h>

int x[10007];

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

int main(){
	int d;
	scanf("%d", &d);
	for (int i = 1; i <= d; i++){
		int n;
		scanf("%d", &n);
		for (int j = 1; j <= n; j++){
			scanf("%d", &x[j]);
		}
		if (n == 1){ // 特判
			printf("YES\n");
			continue;
		}

		x[2] /= gcd(x[1], x[2]);
		for (int j = 3; j <= n; j++){
			x[2] /= gcd(x[2], x[j]);
		}
		if (x[2] == 1){
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：Cylete (赞：0)

一道思维题

首先无论怎么加括号$x_1$都在分母上，$x_2$都在分子上

显然其他数放在分子上最优

判断$x_2$与其他数约分后是不是1即可

```cpp
int T;
int n, x[10010];

inline int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

signed main()
{
	into();
	read(T);
	while(T--)
	{
		read(n);
		for(R int i = 1; i <= n; i++) read(x[i]);
		for(R int i = 1; i <= n; i++)
			if(i != 2)
				x[2] /= gcd(x[i], x[2]);
		puts(x[2] == 1 ? "YES" : "NO");
	}
	return 0;
}
```

---

