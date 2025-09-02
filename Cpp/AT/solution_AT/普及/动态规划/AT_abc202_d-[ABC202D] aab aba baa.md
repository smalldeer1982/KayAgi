# [ABC202D] aab aba baa

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc202/tasks/abc202_d

$ A $ 個の `a` と $ B $ 個の `b` からなる長さ $ A\ +\ B $ の文字列のうち、辞書順で $ K $ 番目のものを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ A,\ B\ \leq\ 30 $
- $ A $ 個の `a` と $ B $ 個の `b` からなる長さ $ A\ +\ B $ の文字列の総数を $ S $ 個とおいたとき、$ 1\ \leq\ K\ \leq\ S $
- 入力は全て整数である。

### Sample Explanation 1

$ 2 $ 個の `a` と $ 2 $ 個の `b` からなる文字列を辞書順に並べると、`aabb`、`abab`、`abba`、`baab`、`baba`、`bbaa` となります。 よって、$ 4 $ 番目である `baab` を出力します。

### Sample Explanation 2

$ K $ の値は $ 32 $ bit 整数に収まらないことがあります。

## 样例 #1

### 输入

```
2 2 4```

### 输出

```
baab```

## 样例 #2

### 输入

```
30 30 118264581564861424```

### 输出

```
bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa```

# 题解

## 作者：Inexistented (赞：7)

## 解析

首先，我们需要找到一种方法来表示以 $A$ 个 $a$ 和 $B$ 个 $b$ 组成的长度为 $A+B$ 的字符串中的所有可能性。一个简单的方法是通过二进制数来表示，将 $A$ 个 $a$ 和 $B$ 个 $b$ 交替排列，用 0 表示 $a$，用 1 表示 $b$。例如，当 $A=3$，$B=2$ 时，我们可以将所有的可能性表示成如下的二进制数：

```
00011
00101
00110
01001
01010
01100
10001
10010
10100
11000
```

这种方法的好处是可以方便地计算所有可能性的个数，即 $2^{A+B}$。但是，这种方法并不便于按照词典序求解第 $K$ 个字符串。因此，我们需要使用别的方法。

注意：要求的是按词典序的第 $K$ 个字符串，因此我们可以考虑按照从左到右的顺序逐个确定每个字符。具体来说，我们从左到右依次考虑每个字符，对于第 $i$ 个字符，如果以 $a$ 开头的字符串的排列组合数小于等于 $K$，则第 $i$ 个字符为 $a$；否则第 $i$ 个字符为 $b$。这样，我们就可以递归地求解第 $K$ 个字符串。

我们可以定义一个递归函数 `getKthString(A, B, K)`，表示以 $A$ 个 $a$ 和 $B$ 个 $b$ 组成的长度为 $A+B$ 的字符串中，按词典序第 $K$ 个字符串。在递归函数中，我们首先判断如果只有 $a$ 或 $b$，则直接返回字符串；否则计算以 $a$ 开头的字符串的排列组合数 $S_a$，如果 $K \leq S_a$，则第 $K$ 个字符串以 $a$ 开头，否则第 $K$ 个字符串以 $b$ 开头，并继续递归求解下一个字符。

总的时间复杂度为 $O(A^2+B)$，可以快速计算出结果。

## 代码

```c
#include <bits/stdc++.h>
using namespace std;

long long Fast(long long x,long long y)
{
    long long i,sum=1;
    
	for(i=1;i<=y;i++)
	{
		sum=sum*(x-i+1)/i;
	}
	
	return sum;
}
int main()
{
	long long i,a,b,c,n;
	
	cin>>a>>b>>c;
	
	n=a+b;
	
	for(i=1;i<=n;i++)
	{
		if(a==0)
		{
			cout<<"b";
		}
		else if(b==0)
		{
			cout<<"a";
		}
		else if(Fast(a+b-1,a-1)<c)
		{
			c=c-Fast(a+b-1,a-1);
			
			cout<<"b";
			
			b=b-1;
		}
		else
		{
			cout<<"a";
			
			a=a-1;
		}
	}
	
	return 0;
}
```

Tip： 方法很多，不一定要按照我这个代码。

---

## 作者：lateworker (赞：3)

## 题目大意

要求构造一个只由 `'a','b'` 两个字母组成的字符串，给定 `'a'` 的个数 $A$，`'b'` 的个数 $B$，将所有符合要求的字符串排序后，求第 $K$ 小的字符串是什么。

## 题目解析

这是一道很经典的字符串搜索题。我们可以先假设在开始时答案字符串中所有位置均为空。尝试从空字符串第一位开始搜索，逐位判断并填入 `'a'` 或 `'b'`。很显然，填入 `'a'` 时字符串的字典序更小。我们知道，在 $A,B$ 固定的情况下, 字符串的总方案数也是固定的。因此，我们可以求出：填入 `'a'` 后，剩下未填的字符有多少种组合方案。与此同时，我们可以把题目转化为：要在未填的字符串中求字典序第 $K$ 大的字符串，并动态维护 $A,B,K$ 的值。填第 $i$ 位时，我们可以把后 $A+B-i$ 位的字符串的总方案数记为 $qa$。如果 $qa<K$，就说明在第 $i$ 位应填入 `'b'`，反之应填入 `'a'`。因此，我们可以递归查找第 $K$ 小字符串。

在递归的时候要注意：

- 填入 `'a'` 或 `'b'` 时，对应的 $A,B$ 的值需要自减。若填入 `'b'`，则还需要改变 $K$ 的值，$K=K-qa$。
- 若 $A=0$ 或 $B=0$ 时，答案只有一种情况，这时要将剩余的所有字符输出。
- 要开 long long

回顾思路, 我们需要一个 `query` 函数用来计算 $qa$，还需要一个 `dfs` 函数用来搜索答案。还有问题请看注释自行理解。

### 简单的代码 (无优化)

```c++
#include <iostream>
using namespace std;
int query(int a, int b) {
    // 如果a或b为0, 只有一种情况.
    if(a == 0 or b == 0) return 1;
    // 不为0, 等于用去一个a的数量加上用去一个b的数量.
    return query(a-1, b) + query(a, b-1);
}
void dfs(int a, int b, int k) {
    // 如果a或b为0, 输出剩余所有字符.
    if(a == 0) {
        cout<<string(b, 'b'); // 直接调用string构造函数.
        return;
    } else if(b == 0) {
        cout<<string(a, 'a');
        return;
    }
    // 填入a时会产生qa个字符串, 判断qa, 选择填入a或b.
    int qa = query(a-1, b);
    if(qa >= k) {
        printf("a");
        dfs(a-1, b, k);
    } else {
        printf("b");
        // k也要动态维护.
        dfs(a, b-1, k-qa);
    }
}
int main() {
    int a, b, k;
    cin>>a>>b>>k;
    dfs(a, b, k);
    return 0;
}
```

这时，我们会发现反复调用 `query` 函数会非常慢。$A,B$ 都不大，考虑记忆化搜索或 DP。

## 正解（记忆化搜索）
**本题解禁止理解性默写！**
```c++
#include <iostream>
using namespace std;
int f[35][35]; // 记忆化搜索数组.
int query(int a, int b) {
    if(a == 0 or b == 0) return 1;
    // 如果没有记录, 进行搜索.
    if(f[a-1][b] == 0) f[a-1][b] = query(a-1, b);
    if(f[a][b-1] == 0) f[a][b-1] = query(a, b-1);
    // 返回记录的答案.
    return f[a-1][b] + f[a][b-1];
}
void dfs(int a, int b, int k) {
    if(a == 0) {
        cout<<string(b, 'b');
        return;
    } else if(b == 0) {
        cout<<string(a, 'a');
        return;
    }
    int qa = query(a-1, b);
    if(qa >= k) {
        printf("a");
        dfs(a-1, b, k);
    } else {
        printf("b");
        dfs(a, b-1, k-qa);
    }
}
int main() {
    int a, b, k;
    cin>>a>>b>>k;
    dfs(a, b, k);
    return 0;
}
```

ps. 这是本蒟蒻的第二篇题解，希望审核通过。~~第一篇沉了~~

---

## 作者：封禁用户 (赞：3)

### 题目大意

在长度为 $A+B$ 的字符串有 $A$ 次 "a" 出现，$B$ 次 "b" 出现，找出按字典序排列第 $K$ 个的字符串。

### 思路

首先可以看出：**a越靠前，字典序越小，b越靠前，字典序越大**。

如果直接求全排列，大约是有 $C(a,a+b)$ 种排列方式，很明显求乘法会爆，那么就模拟成一种位于 $(0,0)$ 点时，每次向右走和向上走，一共有多少种走法。

设 $dp[i][j]$ 为 $a$ 和 $b$ 分别为 $i$，$j$ 时排列的个数：

当 $k \le dp[a-1][b]$ 时，说明如果把当前的位置放上字母 $a$，那说明可以直接放上 $a$，然后再递归寻找下一个。

当 $k>f[a-1][b]$ 时，说明当前位置放 $a$ 的话，那说明此时只能放 $b$，放了 $b$ 之后，那么字典序就直接减少了 $f[a-1][b]$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[105][105];//不开long long见祖宗 
void f(int n) //预处理，dp数组存的就是杨辉三角 
{
    dp[0][0]=1;
    for(int i=1;i<=n;i++) 
	{
        dp[i][0]=1;
        for(int j=1;j<=i;j++)
		{
			dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
		}
    }
}
int main()
{
    int a,b;
    long long k;
    cin>>a>>b>>k;
    f(60);
    int n=a+b;
    for(int i=1;i<=n;i++) 
	{
        long long ans=dp[n-i][a-1];
        if(a==0) ans=0; //特判 
        if(k>ans) //按思路模拟 
		{
			k-=ans;
			cout<<"b";
			b--;
		}
        else 
		{
			cout<<"a";
			a--;
		}
    }
    return 0;
}


```


---

## 作者：CRTL_xzh2009 (赞：2)

对于样例 $1$：

1. $\texttt{aabb}$
2. $\texttt{abab}$
3. $\texttt{abba}$
4. $\texttt{baab}$
5. $\texttt{baba}$
6. $\texttt{bbaa}$

## 暴力算法：

不难发现：对于 $s[i-1]<s[i]$，要交换，并将 $s[i+1]$ 到 $s[n+m]$ 进行升序排序。

```cpp
void work1()//暴力 
{
	s=string(n,'a')+string(m,'b');
    n=m+n;
    k--;
    while(k--)
    {
    	for(int i=n-1; i>0; i--)//从后往前找第一个ab 
    	{
    		if(s[i-1]<s[i])
    		{
    			swap(s[i-1],s[i]);//交换 
    			sort(s.begin()+i,s.end());//升序排序 
    			break;
			}
		}
	}
	cout<<s<<endl;
}
```

## 正解：

我们定义：$f[i][j]$ 表示 $i$ 个 $a$，$j$ 个 $b$ 构成的串个数。

对于样例 $1$ 有：

```cpp
f[0][0]=1;
f[0][1]=1;
f[0][2]=1;
f[1][0]=1;
f[1][1]=f[0][1]+f[1][0]=2;
f[1][2]=f[0][2]+f[1][1]=3;
f[2][0]=1;
f[2][1]=f[1][1]+f[2][0]=3;
f[2][2]=f[1][2]+f[2][1]=6;
```

不难得出 $f[i][j]=f[i-1][j]+f[i][j-1]$；初始化 $f[i][0]=1,f[0][j]=1$。
 
1. 当 $k \le f[n-1][m]$ 时那说明可以直接加上 $a$，然后再寻找下一个字母；
2. 当 $k > f[n-1][m]$ 时，那说明此时只能放 $b$，放了 $b$ 之后，那么减少了 $f[n-1][m]$。

```cpp
#include<bits/stdc++.h>//
#define ll long long
using namespace std;
const int N=35;
ll f[N][N],k;
int n,m; 
string s;
void work1()//暴力 
{
	s=string(n,'a')+string(m,'b');
    n=m+n;
    k--;
    while(k--)
    {
    	for(int i=n-1;i>0;i--)//从后往前找第一个ab 
    	{
    		if(s[i-1]<s[i])
    		{
    			swap(s[i-1],s[i]);//交换 
    			sort(s.begin()+i,s.end());//升序排列 
    			break;
			}
		}
	}
	cout<<s<<endl;
}
string dfs(int n,int m,ll k)
{
	if(n==0) return string(m,'b');//两个边界 
	if(m==0) return string(n,'a');
	if(k<=f[n-1][m])//这一位为 a 
	    return 'a'+dfs(n-1,m,k);
	else//这一位为 b 
	    return 'b'+dfs(n,m-1,k-f[n-1][m]); 
}
void work2()
{
	f[0][0]=1;
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			if(i>0) f[i][j]+=f[i-1][j];
			if(j>0) f[i][j]+=f[i][j-1];
		}
	}
	cout<<dfs(n,m,k);
}
int main()
{
    cin>>n>>m>>k;
    if(k<=1000000)//这个范围内可以直接暴力求解 
        work1();
    else
        work2();
	return 0;
}
```


---

## 作者：_zhx (赞：1)

# AT_abc202_d [ABC202D] aab aba baa 题解

## 题目大意

给定 $A$，$B$，$K$ 三个数，求由 $A$ 个 $a$，$B$ 个 $b$ 组成的所有可能的字符串中的按字典序第 $K$ 个字符串。

### 题目思路

我们只用计算以 $a$ 和 $b$ 组成的字符串中的第 $k$ 个字符串。

这种方法比递归更加高效，而又是一种类似递归的方法 ~~（但不妨碍我叫它递归）~~。

代码中的 add 函数用于确定在当前位置该添加 $a$ 还是 $b$。然后根据 add 函数的结果和 $k$ 的比较，来决定添加 $a$ 或 $b$ 或减少 $a$ 或 $b$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long add(long long a,long long b)
{
    long long x=1;
    for(long long i=0;i<b;i++) x*=(a+b-i),x/=(i+1);
    return x;
}
string di_gui(long long d,long long e,long long f)
//d是a，e是b，f是k
{
    if(d==0) return string(e,'b');
    if(e==0) return string(d,'a');
    long long s=add(d-1,e);
    if(f<=s) return "a"+di_gui(d-1,e,f);
    else return "b"+di_gui(d,e-1,f-s);
}
int main()
{
    long long a,b,k;
    cin>>a>>b>>k;
    cout<<di_gui(a,b,k);
    return 0;
}
```

---

## 作者：littlesnake (赞：0)

### 思路

如果我们定义 $f[i][j]$ 表示表示 $i$ 个 $a$，$j$ 个 $b$ 组成的全排列个数。

而我们对于样例 $1$：

```cpp
f[0][0]=1;
f[0][1]=1;
f[0][2]=1;
f[1][0]=1;
f[1][1]=f[0][1]+f[1][0]=2;
f[1][2]=f[0][2]+f[1][1]=3;
f[2][0]=1;
f[2][1]=f[1][1]+f[2][0]=3;
f[2][2]=f[1][2]+f[2][1]=6;
```
我们可以得出 $f[i][j] = f[i - 1][j] + f[i][j - 1]$，并且 $f[i][0]$ 和 $f[0][j]$ 初始化为 $1$。
 
- 当 $k \le f[n − 1][m]$ 时那说明可以直接加上 `a`，可以继续递归。

- 否则说明当前位只能放 `b` ，放了之后，减少了 $f[n − 1][m]$。

### 代码

```cpp
//[ABC202D] aab aba baa.cpp
#include <bits/stdc++.h>
#define ll long long
#define N 40
using namespace std;
ll f[N][N], k;
int n, m;
string dfs(int n, int m, ll k) {
	if(n == 0) return string(m, 'b');
	if(m == 0) return string(n, 'a');
	if(k <= f[n - 1][m]) return 'a' + dfs(n - 1, m, k);
	else return 'b' + dfs(n, m - 1, k - f[n - 1][m]);
}
int main() {
	cin >> n >> m >> k;
	f[0][0] = 1;
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			if(i > 0) f[i][j] += f[i - 1][j];
			if(j > 0) f[i][j] += f[i][j - 1];
		}
	}
	cout << dfs(n, m, k);
	return 0;
}

```

[洛谷 AC 记录](https://www.luogu.com.cn/record/146304546)

[ATcoder AC 记录](https://atcoder.jp/contests/abc202/submissions/50042705)

---

