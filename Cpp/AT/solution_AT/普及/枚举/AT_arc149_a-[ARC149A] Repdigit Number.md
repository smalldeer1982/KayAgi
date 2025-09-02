# [ARC149A] Repdigit Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc149/tasks/arc149_a

正整数 $ N,\ M $ が与えられます．次の条件をすべて満たす正整数 $ X $ のうち，最大であるものを答えてください．

- $ X $ は $ 10^N $ 未満の正整数で，$ X $ を $ 10 $ 進法表記したときのどの桁の数字も同じである．
- $ X $ は $ M $ の倍数である．

ただし，条件を満たす正整数 $ X $ が存在しない場合には `-1` と出力してください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 10^5 $
- $ 1\leq\ M\leq\ 10^9 $

### Sample Explanation 1

条件を満たす正整数 $ X $ は，$ 444,\ 888,\ 444444,\ 888888 $ の $ 4 $ つです．このうち最大のものである $ 888888 $ が答となります．

### Sample Explanation 2

条件を満たす正整数 $ X $ は，$ 444,\ 888,\ 444444,\ 888888,\ 444444444,\ 888888888 $ の $ 6 $ つです．

### Sample Explanation 3

条件を満たす正整数 $ X $ は，$ 3,\ 6,\ 9 $ の $ 3 $ つです．

### Sample Explanation 4

条件を満たす正整数 $ X $ は存在しません．

## 样例 #1

### 输入

```
7 12```

### 输出

```
888888```

## 样例 #2

### 输入

```
9 12```

### 输出

```
888888888```

## 样例 #3

### 输入

```
1 3```

### 输出

```
9```

## 样例 #4

### 输入

```
1000 25```

### 输出

```
-1```

## 样例 #5

### 输入

```
30 1```

### 输出

```
999999999999999999999999999999```

# 题解

## 作者：Garbage_fish (赞：2)

### 1. 分析题目

题目要求小于 $10^n$ 的最大的 $m$ 的倍数，并且这个数的每个数字相同。

### 2. 数学分析

如果现在有一个数 $x$，现在要往后添加 $num$ 这个数字，显然的，新数字是 $10x+num$。如果要判断它是不是 $m$ 的倍数，判断 $(10x+num) \mod m$ 的值即可。

可是题目告诉我们， $n$ 最大可达 $10^5$，若直接求出 $10^{100000}$，必须使用高精度，而高精度又过于麻烦，~~我相信没多少人愿意打高精度吧~~。

因此需要寻找数学方法，不难发现：

$$(a+b)\mod m=(a \mod m+b\mod m)\mod m$$

证明：设 $a=pm+k$，$b=qm+l$，其中 $p$ 和 $q$ 表示商，$k$ 和 $l$ 表示余数，则：
$$a+b=pm+k+qm+l=(p+q)m+k+l$$

因为 $(p+q)m$ 是 $m$ 的倍数，所以：
$$(a+b)\mod m=(k+l)\mod m=(a \mod m+b \mod m) \mod m$$

通过以上证明，我们就可以不用把数字算出来再判断是否为 $m$ 的倍数，可以边算边模 $m$。

### 3. 代码部分

我们可以用 $f_{i,j}$ 来表示由 $i$ 个数字 $j$ 组成的数模 $m$ 的余数，可以得到状态转移方程为：

$$f_{i,j}=(f_{i-1,j}\times10+j)\mod m$$

此时，发现第一个维度可以省略掉：

$$f_j=(f_j\times10+j)\mod m$$

如果 $f_j=0$，那么就说明这个数字是可行的，记录下它组成的数字和个数。

**AC Code:**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void fread(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
const int N=1e5+10;
int n,m,f[15],cnt=1,num=-1;
//cnt 表示重复次数，num 表示答案由哪个数字构成，初始答案是 -1，出现 1 次。
signed main(){
	fread();
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=9;j++){
			f[j]=(f[j]*10+j)%m;
			if(!f[j]){
				cnt=i,num=j;//由于 i 与 j 越来越大，因此越往后答案必然越优。
			}
		}
	}
	for(int i=1;i<=cnt;i++){
		cout<<num;
	}
	return 0;
}
```

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_arc149_a)&[Atcoder 链接](https://atcoder.jp/contests/arc149/tasks/arc149_a)

本篇题解为此题较**简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

求满足以下条件的小于 $10 ^ n$ 数最大是多少？

- 每一位数字均相同；

- 是 $m$ 的倍数。

数据范围：$1\le n\le 10^5$，$1\le m\le 10^9$。

## 思路

首先**每位数字都相同**很好满足，仅需**枚举** $n$ 位后，**枚举每位的数字** $1 \sim 9$，注意**不包含** $0$，因为最高位**不能**为 $0$。

接着想要满足是 $m$ 的倍数，可以想到类似**动态转移**的思路，定义二维数组 $mp[i][j]$ 表示在有 $i$ 位数的情况下每位都为 $j$ 的数**除以** $M$ 的**余数**。在枚举中**实时更新答案**，因为位数是从 $1 \sim N$，每位是从 $1 \sim 9$，所以存储的答案**一定为最大的解**。

## 代码实现

经过以上分析及一些数组设计，很容易即可得到代码。首先我们先看一下 $mp$ 数组的**处理**：

```cpp
for(int i = 1; i <= n; i ++)
	for(int j = 1; j <= 9; j ++) {
		mp[i][j] = (mp[i - 1][j] * 10 + j) % m;
		if(!mp[i][j]) ans1 = i, ans2 = j;
	}
```

可以看到**第三行**对于 $mp$ 数组**状态的转移**：

$$mp_{i,j} \gets mp_{i-1,j}$$

可以从 $i-1$ 位都是 $j$ 的余数转移过来，根据**同余的相关知识**很容易推出**转移方程式**：

$$mp_{i,j} \gets (mp_{i-1,j} \times 10 + j) \% M$$

解决状态转移后需更新答案，这一部分很简单就不在赘述。接着需要在处理 $mp$ 数组后，**特判** $-1$ 的情况：

```cpp
if(!ans1 || !ans2) {
	cout << "-1\n";
	return 0;
}
```

这样整体代码框架就完成了。

## AC code

```cpp
#include<iostream>
using namespace std;

long long n, m, mp[100005][15];
long long ans1, ans2;

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= 9; j ++) {
			mp[i][j] = (mp[i - 1][j] * 10 + j) % m;
			if(!mp[i][j]) ans1 = i, ans2 = j;
		}
	if(!ans1 || !ans2) {
		cout << "-1\n";
		return 0;
	}
	for(int i = 1; i <= ans1; i ++) cout << ans2;
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117303341)

$$\text{The End!}$$

---

## 作者：Rainbow_Sky (赞：0)

## 思路

我们可以通过两个条件来分析。

1. 每一位数字均相同。这个条件相对来说比较好处理，我们可以枚举 $n$ 位，每一位上再枚举 $9$ 个数字，即可以枚举出所有 $10^n$ 以内的各位数字相同的数。

1. 是 $m$ 的倍数。在计算过程中，对 $m$ 取模，再定义两个变量，$k$ 和 $p$，如果取模后为零，则用 $k$ 记录下当前的这个数字，用 $p$ 记录下这个数字重复了几次，最后循环 $p$ 遍，输出 $k$ 即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000+10;
const int MAXM=100000+10;
const int INF=100000;
int a[MAXM];
int main()
{
	int n,m;
	int k=0,p=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=9;j++)
		{
			a[j]=(a[j]*10+j)%m;
			if(a[j]==0) 
			{
				k=j;p=i;
			}
		}
	}
	if(k==0||p==0)
	{
		cout<<"-1";
		return 0;
	} 
	for(int i=1;i<=p;i++)
	{
		cout<<k;
	}
	return 0;
}
```

---

## 作者：hubin1 (赞：0)

# ARC149A Repdigit Number

## 题目大意
问满足以下条件的小于 $10 ^ n$ 数最大是多少？

- 每一位数字均相同；
- 是 $m$ 的倍数。

$1\le n\le 10^5$，$1\le m\le 10^9$。

## 思路
1. 每一位数字均相同，这一点很好实现。
2. 是 $m$ 的倍数可以用它除以 $m$ 的余数来判断，如果余数为零，那么它就**有可能**是答案，只是这时我们不能确定它就是**最大**的，但一直运行到最后，所保存的数就一定是答案了。

## 实现
1. 我们用 $\mathit{a}_{i,j}$ 来表示这个长度为 $i$，全部的数字都是 $j$ 的这个数的**余数**。
2. 如果这个余数为零，我们就把它的**长度**以及**数字**存起来。
3. 最后输出。

## Code
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=1e5+10;
int a[MAX][15];
signed main()
{
    int n,m;
    int ans_len=0;
    int ans_data=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)//位数
    {
        for(int j=1;j<=9;j++)//当前位上放的什么
        {
            a[i][j]=(a[i-1][j]*10+j)%m;
            if(a[i][j]==0)  //是它的倍数
                ans_len=i,ans_data=j;
        }
    }
    if(ans_len==0||ans_data==0)
        cout<<"-1"<<endl;
    else
        for(int i=1;i<=ans_len;i++)
            cout<<ans_data;
        
    return 0;
}
```

---

## 作者：scp020 (赞：0)

先考虑一个弱化版本，求：是 $m$ 的倍数的 $n$ 位数，其中每一位都相同。

不难发现，每位上的数只能是 $1,2,3,4,5,6,7,8,9$，我们只要从 $1$ 到 $9$ 枚举这个 $n$ 位数就好。现在的问题是，$n \le 10^5$，不能用一种数据类型来存储，所以考虑线性处理方法。

假如我们现在已经得到了一个 $x$ 位每一位都为 $a$ 的数，这个数记为 $s$，则我们可以用 $s \times 10 + a$ 表示一个 $x + 1$ 位每一位都为 $a$ 的数。同理，假如我们现在已经得到了一个 $x$ 位每一位都为 $a$ 的数，将这个数除以 $m$ 的余数记为 $r$，则我们可以用 $r \times 10 + a$ 表示一个 $x + 1$ 位每一位都为 $a$ 的数除以 $m$ 的余数。我们就求出了线性复杂度的处理式。这里还要注意答案的覆盖。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mod,ans;
int main()
{
	cin>>n>>m;
	const int p=m;//取模优化，加 const 比不加快好多
	for(int i=1;i<=9;i++)
	{
		mod=0;
		for(int j=1;j<=n;j++) mod=(mod*10+i)%p;
		if(mod==0) ans=i;
	}
	if(ans) for(int i=1;i<=n;i++) putchar(ans+'0');
	else cout<<-1;
	return 0;
}
```

现在考虑本题。现在是小于等于 $n$ 位。我们只需要在每一次处理完 $r \times 10 + a$ 后判断一次当前 $r$ 是否等于 $0$。如果等于，则与现在已有的答案比较。最后输出即可。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mod,ansn,ansnum;
int main()
{
	cin>>n>>m;
	const int p=m;//取模优化，加 const 比不加快好多
	for(int i=1;i<=9;i++)
	{
		mod=0;
		for(int j=1;j<=n;j++)
		{
			mod=(mod*10+i)%p;
			if(mod==0 && j>=ansn) ansn=j,ansnum=i;
		}
	}
	if(ansn && ansnum) for(int i=1;i<=ansn;i++) putchar(ansnum+'0');
	else cout<<-1;
	return 0;
}
```





---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc149_a)               
一道很水的枚举。       
## 0 前置知识       
$(a+b)\bmod m=(a\bmod m+b\bmod m)\bmod m$           
## 1 生成数字     
这里我们要实现一个函数 $get(x,n)$ 用于求出 $\begin{matrix}\underbrace{\overline{xxxxx\cdots xxx}}\\len=n\end{matrix}\bmod m$ 的结果。        
首先，我们想一下 $\begin{matrix}\underbrace{\overline{xxxxx\cdots xxx}}\\len=n\end{matrix}$ 的生成方式。      
对于长度为 $n$ 的这样的数字，它等同于 $\sum\limits^{n}_{i=1}x\times 10^{i-1}$。加上取模，为 $\sum\limits^{n}_{i=1}x\times 10^{i-1}\bmod m$。          
根据我们的前置知识，容易求出这个式子等同于 $\sum\limits^{n}_{i=1}(x\times 10^{i-1}\bmod m)\bmod m$。         
所以它可以用以下这段代码生成：      
```cpp
inline int get(int x,long long n){
	long long y=0;
	for(int i=1;i<=n;i++){
		y*=10;
		y+=x;
		y%=m;
	}
	return y;
}
```
## 2 暴力枚举      
容易发现，当 $get(x,n)=0$ 的时候，所生成出的数字就是一个结果。       
我们对 $x$ 和 $n$ 都取最大值即可。          
用两重循环解决即可。     
    
## 3 第一次优化      
上面的代码 TLE 了。       
我们不难发现，两重循环暴力枚举的时候，差都是 $\begin{matrix}\underbrace{\overline{11111\cdots111}}\\len=n\end{matrix}$，所以我们每次只生成它模 $m$ 的值就可以推出剩下的了。         
    
## 4 正解        
在第二和第三部分中，代码都是 $O(n^2)$ 的。      
如何让代码更快呢？        
可以发现，在两重循环暴力枚举时，位数每多一位，都是 $\begin{matrix}\underbrace{\overline{11111\cdots111}}\\len=n\end{matrix}$ 加上了 $10^{n-1}$。所以我们根据前置知识，利用 $10^{n-1}$ 的余数操作就可以省去 $get$ 函数的操作。           
[CODE](https://www.luogu.com.cn/paste/ap8xo9t9)

---

## 作者：SuperCowHorse (赞：0)

提供一种非常奇妙的做法。

参照 2006 年 NOIP 初赛完善程序，我们可以发现，他长得和这道题很像。

把主要部分贴出来：
``` cpp
do{
	c=a%p;
	a=c*10+1;
	++k;
}while(c>0);
```
把其中的 $1$ 换成 $x(1\le x\le9$) 就能计算全部是 $x$ 的最小值了。

还有一个问题：题目中要求求出是小于 $n$ 位的最大值，这里求最小值是什么意思？

那就在外面再套个`while`，只要满足条件就一直做下去；一旦大于 $n$ 位，直接返回当时 $ans$。也就是说，只有找到一个更大的答案才能更新。
``` cpp
int check(int x){//求 x 得最大值
	int a=0,k=0,c;
	while(a<p){a=a*10+x;++k;}
	int t=0,ans=-1;
	while(k<=n){
		do{
			if(k>n) return ans;//超过直接返回
			c=a%p;
			a=c*10+x;
			++k;
		}while(c>0);
		ans=k-1;//找到再更新
	}
	return ans;
}
```
是不是特别奇妙？

然后就是统计答案。

对于 $1$ 至 $9$ 每一个答案放在一个结构体 $a$ 中，$id$ 表示数字（$1\backsim9$），$num$ 表示每个 $id$ 最大的位数。

然后以 $num$ 为第一关键字，$id$ 为第二关键字，从大到小排序。

$a_1$ 即为答案。循环输出即可。

Code:
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p;
struct node{
	int num,id;
}a[10];
bool cmp(node u,node v){return u.num==v.num?u.id>v.id:u.num>v.num;}
int check(int x){
	int a=0,k=0,c;
	while(a<p){a=a*10+x;++k;}
	int t=0,ans=-1;
	while(k<=n){
		do{
			if(k>n) return ans;
			c=a%p;
			a=c*10+x;
			++k;
		}while(c>0);
		ans=k-1;
	}
	return ans;
}
bool fl;//fl 表示有没有解，懒得特判了
signed main(){
	scanf("%lld%lld",&n,&p);
	for(int i=9;i>=1;--i){
		int f=check(i);
		a[i].num=f;a[i].id=i;
		if(f!=-1) fl=1;
	}
	if(!fl) return printf("-1"),0;
	sort(a+1,a+10,cmp);
	for(int i=1;i<=a[1].num;++i)
		putchar(a[1].id+'0');
	return 0;
}
```

---

## 作者：Naro_Ahgnay (赞：0)

## 思路

我们可以枚举所有数位上的数字都相同的数，然后判断他们模上 $m$ 的值是否为 0。

构造每一位数字均相同的数的方法：假设现在有一个 $i$ 位数 $a$，数位上的数字为 $b$，我们只需要将 $a$ 变成 $a\times10+b$ 就能变成 ($i+1$) 位数。

判断是不是 $m$ 的倍数：众所周知，取模操作这玩意可以在运算的过程中进行，所以我们不需要求出最终 $a$ 的具体值，只需要存下 $a$ 对 $b$ 取模的值，也就是在每次 $a$ 变成 $a\times10+b$ 的过程中进行取模。 时间复杂度 $O(9n)$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,x,y,t;
long long a[11];
int main() 
{
	scanf("%d%d",&n,&m);
	x=y=0;
	for(int i=1;i<=n;++i) 
	{
		for(int j=1;j<=9;++j) 
		{
			a[j]=(a[j]*10+j)%m;
			if(a[j]==0) x=i,y=j;
		}
	}
	if(!x) puts("-1");
	else 
	{
		for(int i=1;i<=x;++i) printf("%d",y);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：xiaoPanda (赞：0)

## A - Repdigit Number

### Problem

问满足以下条件的 $n$ 位数最大是多少？

+ 每一位数字均相同

+ 是 $m$ 的倍数

$1\le n\le 10^5,1\le m\le 10^9$

### Solution

容易发现满足第一个条件数有 $n\times 9$ 个，但无法判断这些数是不是 $m$ 的倍数。

注意到并不用关心这些数的具体大小，只要关心这些数与 $m$ 的余数即可。

可以设 $f[i][j]$ 表示 $i$ 位数且每一位数字均位 $j$ 的数（即 $\overline{jj...j}$  共 $i$ 个 $j$）与 $m$ 的余数。

那么有 $f[i][j]=(f[i-1][j]\times 10+j)\bmod m$，当 $f[i][j]=0$ 时即可更新答案，时间复杂度为 $O(n)$。

---

