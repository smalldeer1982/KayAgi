# 「chaynOI R1 T1」一维数组

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/tc5is950.png)

## 题目描述

给你两个正整数 $n,m$，你要构造两个正整数 $x,y$（不能有前导 $0$），使得 $x$ 有 $n$ 位，$y$ 有 $m$ 位，且 $x\times y$ 是回文数。

请保证你构造的输出合法，否则后果自负。

## 说明/提示

对于 $100\%$ 的数据，$n,m \le 10^3$。

**本题采用捆绑测试。**

- Subtask 1(25pts)：$n,m \le 6$。
- Subtask 2(10pts)：$m = 1$。
- Subtask 3(65pts)：无特殊限制。

## 样例 #1

### 输入

```
2 6```

### 输出

```
83 138017‬
```

## 样例 #2

### 输入

```
5 5```

### 输出

```
24513 40723
```

# 题解

## 作者：canwen (赞：6)

考察找规律。

写出打表程序，如下。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e3 + 5;
int s[N];
bool pd(int a){
	int n = 0;
	while(a>0){
		s[++n] = a%10, a /= 10;
	}
	for(int i=1;i<=n/2;i++){
		if(s[i]!=s[n-i+1]) return 0;
	}
	return 1;
}
signed main(){
	int n, m;
	cin >> n >> m;
	for(int i=pow(10,n-1);i<=pow(10,n)-1;i++){
		for(int j=pow(10,m-1);j<=pow(10,m)-1;j++){
			if(pd(i*j)){
				cout << i << " " << j << endl;
				return 0;
			}
		} 
	}
	return 0;
}
```

不难发现两个答案可以形为首尾是 `1`，中间是 `0`，然后特判一点东西就能过。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e3 + 5;
int s[N];
bool pd(int a){
	int n = 0;
	while(a>0){
		s[++n] = a%10, a /= 10;
	}
	for(int i=1;i<=n/2;i++){
		if(s[i]!=s[n-i+1]) return 0;
	}
	return 1;
}
signed main(){
	int n, m;
	cin >> n >> m;
	if(n==1){
		cout << 1;
	}else if(n==2){
		cout << 11;
	}else{
		cout << 1;
		for(int i=1;i<=n-2;i++) cout << 0;
		cout << 1; 
	}
	cout << " ";
	if(m==1){
		cout << 1;
	}else if(m==2){
		cout << 11;
	}else{
		cout << 1;
		for(int i=1;i<=m-2;i++) cout << 0;
		cout << 1; 
	}
	
	return 0;
}
```

接下来是严谨的证明：

首先我们知道，$10^i$ 表示的数数位是 $i+1$。

那么有 $x\cdot y = (10^{n-1}+1) \cdot (10^{m-1}+1) = 10^{n+m-2}+10^{n-1}+10^{m-1}+1$。

这里我们假设 $n < m$，实际上 $n\ge m$ 交换一下 $m,n$ 的值同理可以证明。

那么上面的值可以画图表示成这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/2k3705so.png)

看起来很显然回文，小算一下。

显然形如 `10...01` 的是回文的。

左边红色圈里的 `0` 的数量可以表示为 $n+m-1-m-1=n-2$ 位。

右边红色圈里的 `0` 的数量也等于 $n-2$。

所以可以看出是回文的，所以如此构造可以使得 $x \cdot y$ 一定是回文数，得证。

---

## 作者：WsW_ (赞：4)

### 思路
考察选手的注意力。  
如果你做过小学找规律题，那你应该知道 $11\cdots11\times 11\cdots11$ 这样的东西在位数少的时候结果会是个回文数，因为这东西拆成竖式运算就是一堆 $11\cdots11$ 错位相加。例如 $111\times 11=1221$。  
所以先试试输出 $\underbrace{11\cdots11}_{n 个 1}\times\underbrace{11\cdots11}_{m 个 1}$。发现只能通过前两个 sub，思考一下什么情况不能这样构造。  
还是根据竖式运算发现，在错位相加的时候要是出现进位那就毁了，我们想一想如何消除掉这个进位。  

上述做法启示了正确做法，我们发现在竖式乘法的时候，乘数的某一位上放一个 $1$ 相当于在那一位上放另一个乘数相加。要是放的 $1$ 太多了就会导致出现进位，所以我们可以把靠在中间的一些 $1$ 改成 $0$，例如将 $111111$ 改成 $110011$。发现想要消除进位的影响，把尽可能多的 $1$ 改成 $0$ 一定不劣，但是要保证没有前导 $0$，所以首末两位一定得是 $1$。  
接下来惊奇地发现 $1\underbrace{00\cdots00}_{n-2 个 0}1$ 这个东西乘上一个回文数，结果一定还是一个回文数，除非产生了进位。可以用竖式运算证明。  
所以答案就是上面那个东西乘上随便一个不会导致进位的回文数。容易发现只要所有位上的数字都小于 $5$ 就一定不会导致进位。  
到这里其实已经做完了。一个合法的答案是 $1\underbrace{00\cdots00}_{n-2 个 0}1\times\underbrace{11\cdots11}_{m 个 1}$。  


又发现 $1\underbrace{00\cdots00}_{n-2 个 0}1$ 本身就是一个回文数，所以两个数字都可以构造成这个样子。  
另一个可行的答案是 $1\underbrace{00\cdots00}_{n-2 个 0}1\times1\underbrace{00\cdots00}_{m-2 个 0}1$。注意，需要特判 $n=1$ 和 $m=1$ 的情况。  

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long ull;
int n,m;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	cin>>n>>m;
	cout<<1;
	if(n!=1){
		for(int i=2;i<n;i++)cout<<0;
		cout<<1;
	}
	cout<<'\n';
    for(int i=1;i<=m;i++)cout<<1;//换成小于5的数字都行
	
	return 0;
}
```
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	cin>>n>>m;
	cout<<1;
	if(n!=1){
		for(int i=2;i<n;i++)cout<<0;
		cout<<1;
	}
	cout<<'\n'<<1;
	if(m!=1){
		for(int i=2;i<m;i++)cout<<0;
		cout<<1;
	}
	
	return 0;
}
```

---

## 作者：Vct14 (赞：3)

惊人的注意力，$1\underbrace{00\cdots0}_{n-2\  \text{个}\ 1}1\times1\underbrace{00\cdots0}_{m-2\  \text{个}\ 1}1=10^{n+m-2}+10^{n-1}+10^{m-1}+1$ 一定是回文数。这样构造即可。

注意特判输入 $n=1$ 或 $m=1$ 时的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m;cin>>n>>m;
    if(n==1) cout<<1;
    else{cout<<"1";for(int i=2; i<=n-1; i++) cout<<"0";cout<<"1";};
    cout<<" ";
    if(m==1) cout<<1;
    else{cout<<"1";for(int i=2; i<=m-1; i++) cout<<"0";cout<<"1";};
	return 0;
}
```

---

## 作者：niuniudundun (赞：2)

赛时没想出来，赛后想出来了。

[原题](https://www.luogu.com.cn/problem/P11568)

# 题目大意

构造出一个 $n$ 位的数值 $x$ 和一个 $m$ 位的数值 $y$，使得 $xy$ 为回文数。

# 解法

## $35\texttt{pts}$ 解法

注意到第二个 Subtask 的限制。

不妨设 $y=\overline{11 \cdots 11}$，即 $m$ 个 $1$，那么只需要令 $x$ 是任意回文数，$xy$ 就一定回文数。

代码如下。

```cpp
#include<iostream>
using namespace std;
int n,m;
string x,y;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		x+="1";
	}
	for(int i=1;i<=m;i++){
		y+="1";
	}
	cout<<x<<" "<<y<<endl;
	return 0;
}
```

## 满分

设有两个回文数（第一个比第二个短）的积：

$$
\overline{10\cdots01}\times \overline{10\cdots01}
$$

这个数一定是回文数。

所以可以输出一个 $1$，然后 $n-2$ 个 $0$，接一个 $1$，就是 $x$ 了，用同样方法写出 $y$ 即可。不过要特判 $n\le2$ 和 $m\le2$。

代码：

复杂度：$O(n+m)$。

```cpp
#include<iostream>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(n<3||m<3){
		if(n==1){
			cout<<"1";
		}else{
			for(int i=1;i<=n;i++){
				cout<<"1";
			}
		}
		cout<<" ";
		if(m==1){
			cout<<"1";
		}else{
			for(int i=1;i<=m;i++){
				cout<<"1";
			}
		}
	}else{
		cout<<"1";
		for(int i=1;i<=n-2;i++){
			cout<<"0";
		}
		cout<<"1 ";
		cout<<"1";
		for(int i=1;i<=m-2;i++){
			cout<<"0";
		}
		cout<<"1 ";
	}
	cout<<"\n";
	return 0;
}
```

---

## 作者：syx_2014 (赞：2)

分类讨论（下列 $n,m$ 为题目中的意思）。

1. $m < n$。 $(10^m+1) \times t=\overline{t00\cdots00t}$，所以如果 $t$（有 $n$ 位）是回文数，$\overline{t00\cdots00t}$ 就也是回文数。
2. $m > n$。 我们发现把情况一倒过来就行了。
3. $m = n$。 假设 $t$ 有 $q$ 位，那 $10^q+1 \times t=t+ t\times 10^q$。不难得出如果 $t$ 的第一位和最后一位相加不进位，那 $(10^m+1) \times t$ 也是回文数。

我们发现 $111\cdots111$ 可以满足的 $t$ 的条件。

所以，我们可以输出 $10^m+1$ 和 $n$ 位的 $111\cdots111$ 就可以满足条件。

别忘了特判 $m=1$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	if(n>1){
	    cout<<"1";
    	for(int i=1;i<=n-2;i++) cout<<"0";
    	cout<<"1 ";
	}
    if(n==1) cout<<1<<' ';
	for(int i=1;i<=m;i++) cout<<"1";
	return 0;
}
```

---

## 作者：RAY091016 (赞：1)

### 1. 题目解释

给出正整数 $n$ 和 $m$，求两个分别为 $n$ 位和 $m$ 位的正整数，使得他们的积为回文数。

### 2. 思路

看到 Special Judge 就知道这肯定是构造题。

学过小学奥数的人都知道，$\begin{matrix}\underbrace{111\cdots1}\\n 个 1\end{matrix}\times\begin{matrix}\underbrace{111\cdots1}\\m 个 1\end{matrix}$ **在 $n$ 和 $m$ 较小时为回文数。**

证明不难，只需要看成 $\begin{matrix}\underbrace{111\cdots1}\\n 个 1\end{matrix}\times\begin{matrix}1\underbrace{00\cdots0}\\n-1 个 0\end{matrix}+\begin{matrix}\underbrace{111\cdots1}\\n 个 1\end{matrix}\times\begin{matrix}1\underbrace{00\cdots0}\\n-2 个 0\end{matrix}+\cdots\begin{matrix}\underbrace{111\cdots1}\\n 个 1\end{matrix}\times1$ 进行加法即可。

然而 $n$ 和 $m$ 较大时就不行了，加法进位会导致数位错位。

因而考虑另外的构造方法。

不难想到将中间的 $1$ 全部替换为 $0$，就可以减少加法的次数从而减少进位。

因此答案为 $\begin{matrix}1\underbrace{00\cdots0}1\\n-2 个 0\end{matrix}\times\begin{matrix}1\underbrace{00\cdots0}1\\m-2 个 0\end{matrix}$。

---

## 作者：liuzhuoran141516 (赞：1)

## 思路 
通过打表可以发现 $(10^{n-1}+1) \times (10^{m-1}+1)$ 一定是一个回文数，为什么呢？  
我们首先展开这个表达式。设 $a = 10^{n-1}$ 和 $b = 10^{m-1}$，则表达式变为 $(a+1)(b+1)$。展开这个乘积，我们得到：

$$
(a+1)(b+1) = ab + a + b + 1
$$

将 $a$ 和 $b$ 的值代回，我们有：

$$
ab + a + b + 1 = 10^{n-1} \times 10^{m-1} + 10^{n-1} + 10^{m-1} + 1 = 10^{n+m-2} + 10^{n-1} + 10^{m-1} + 1
$$

不难证明，这个数一定是回文数
## 优化
因为 $n,m \le 10^3$，所以我们不能用 pow 函数来生成 $10$ 的幂，所以我们用字符串来表示 $10$ 的幂，这样本题就完成了，复杂度 $O(n+m)$
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
string num(int n) {
    if (n == 1) {
    	return "1";
	}//n=1时特判，返回1 
    string res = "1";
    for (int i = 1; i < n - 1; i++) {
        res += "0";
    }
	res += "1";
    return res;
}
int n, m;
int main() {
    cin >> n >> m;
    cout << num(n) << ' ' << num(m);
    return 0;
}
```

---

## 作者：luckyqwq (赞：1)

# P11568「chaynOI R1 T1」一维数组 题解

### 大致思路：

首先这是一道大胆猜测题，因为我们看一个数，就要看他长久的规律，一位数，两位数，我们看不出什么规律，我们想三位数，首先思考最特殊的三位数中的平方数，我们会想到一个很特殊的 $11 × 11 = 121$，从这里我们可以推测出答案与 $1$ 有一些关联，首先我们能够想到，是否能够全是 $1$ 呢？我原本用的是这种方法，看上去毫无问题，提交上去喜提 $35pts$，通过举反例能够看出在 $10$ 个 $1$ 乘上 $12$ 个 $1$ 时出现了问题。那么考虑以两个 $1$ 为边界往里面塞相同的数。通过试验发现两个数可以构造为 $1...1$ 其中 $...$ 表示若干个 $0$，通过验证可以通过。

### 代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
signed main()
{
    cin >> n >> m;
    if (n < 2)
        cout << 1;
    else
    {
        cout << 1;
        for (int i = 1; i <= n - 2; ++i)
            cout << 0;
        cout << 1;
    }
    cout << ' ';
    if (m < 2)
        cout << 1;
    else
    {
        cout << 1;
        for (int i = 1; i <= m - 2; ++i)
            cout << 0;
        cout << 1;
    }
}
```

这样这道题目就完成啦！！！

---

## 作者：Eason_cyx (赞：1)

简单题。

不难注意到，构造 $1000...0001$ 和 $1000...0001$ 是合法解。注意特判 $n=1$ 或 $m=1$。

时间复杂度 $O(n+m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m; cin >> n >> m;
	if(n != 1) {
		cout << 1; for(int i = 2;i < n;i++) cout << 0; cout << 1 << ' ';
	} else cout << 1 << ' ';
	if(m != 1) {
		cout << 1; for(int i = 2;i < m;i++) cout << 0; cout << 1 << ' ';
	} else cout << 1 << ' ';
	return 0;
}
···

---

## 作者：xinxin2022 (赞：1)

诈骗题。

运用小学数学知识可知，对于较小的 $n$ 和 $m$，全部输出 $1$ 即可。

拿到 $35$。

发现有进位就凉，考虑如何消除进位。

容易发现除首尾外，只要放 $1$ 可以，放 $0$ 也行，有小学三年级数学水平的列竖式即可证明。

于是首尾为 $1$，中间为 $0$。

不难写出代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
    cin>>n>>m;
    n--;m--;
    putchar('1');
    while(n>1) putchar('0'),n--;
    if(n) putchar('1');
    putchar(' ');
    putchar('1');
    while(m>1) putchar('0'),m--;
    if(m) putchar('1');
    return 0;
}
```

---

## 作者：jimmy9_666 (赞：1)

# P11568 「chaynOI R1 T1」一维数组 题解

### 分析

通过惊人的注意力可以发现：$(10^{n-1}+1) \times (10^{m - 1}+1)$ 一定是一个回文数。

证明如下：

因为：

$$(a + b)\times (c + d) = a\times c + a\times d + b\times c + b\times d$$

所以：

$$(10^{n-1}+1) \times (10^{m - 1}+1)=10^{n-1}\times 10^{m-1} + 10^{n-1} \times 1 + 1\times 10^{m-1} + 1 \times 1$$

化简得：

$$(10^{n-1}+1) \times (10^{m - 1}+1) = 10^{n+m-2}+10^{n - 1} + 10^{m - 1} + 10^0$$

观察指数 $n + m - 2, n-1,m-1,0$：我们可以注意到 $(n+m-2)-(n-1)=(m-1)-0$。

在这个数中，最高位是 $10^{n + m - 2}$， 最低位是 $10^0$。而在与它们相距 $m - 1$ 位的那个数位又都为 $1$，所以这个数是对称的，就是是说这个数是个回文数。

放一张图方便理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/6274rins.png)

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#define LL long long
#define int long long

using namespace std;

const int N = 1e3 + 10;

int n, m;

signed main() {
	scanf("%lld%lld", &n, &m);
	printf("1");
	if (n != 1) {
		for (int i = 2; i < n; i ++ )
			printf("0");
		printf("1");
	}
	printf(" 1");
	if (m != 1) {
		for (int i = 2; i < m; i ++ )
			printf("0");
		printf("1");
	}
	return 0;
}
```

---

## 作者：MnZnOIer (赞：1)

### 解题思路
构造题，应该挺一眼的。

我们可以结合乘法的竖式来思考。

令 $a=a_1\times10^n+a_2\times10^{n-1}+\dots+a_n\times10^1+a_{n+1}\times10^0$，$b=b_1\times10^m+b_2\times10^{m-1}+\dots+b_m\times10^1+b_{m+1}\times10^0$，并假设 $a\times b$ 为回文数，不产生进位。

原式 $a\times b=$

$$(a_1\times10^n+a_2\times10^{n-1}+\dots+a_n\times10^1+a_{n+1}\times10^0)\times(b_1\times10^m+b_2\times10^{m-1}+\dots+b_m\times10^1+b_{m+1}\times10^0)$$

化简得：

$$a_1\times b_1\times10^{n+m} + \dots+a_{n+1}\times b_{m+1}\times10^0$$

合并同类项得：

$$10^{n+m}\times(a_1\times b_1)+10^{n+m-1}\times(a_1\times b_2+ a_2\times b_2)+\dots+10^0\times(a_{n+1}\times b_{m+1})$$

我们知道，回文数是回文的，所以从前往后读和从后往前读是一样的。~~（废话）~~

所以：

$$a_1\times b_1=a_{n+1}\times b_{m+1}$$

$$a_1\times b_2+a_2\times b_1=a_n\times b_{m+1}+a_{n+1}\times b_{m}$$

$$a_1\times b_3+a_2\times b_2+a_3\times b_1=a_{n - 1}\times b_{m + 1}+a_{n}\times b_{m}+a_{n+1}\times b_{m-1}$$

$$\dots$$

所以我们可以想到，令 $a_1=a_{n+1}=b_1=b_{m+1}=1$，其余的都为 $0$。（无论如何，只要让上式成立即可并且都 $<10$ 就是满足题意的）

### 代码部分
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
void print (int a){cout << 1;for (int i = 2; i < a; ++ i)cout << 0;if (a > 1)cout << 1;}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	int a, b;
	cin >> a >> b;
	print (a);
	cout << ' ';
	print (b);
	return 0;
}
```

---

## 作者：nannangua (赞：0)

[传送门](https://www.luogu.com.cn/problem/P11568)

首先这题跟数组没有半毛钱关系，就是一道数论题，我们构造即可。注意 $ n = 1 $ 或 $ m = 1 $ 的情况。

最终的结论只需输出 $ 10^{n-1} + 1 $ 与 $ 10^{m-1} +1 $ 即可。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	if(n>1)
	{
		cout<<'1';
		for(int i=1;i<=n-2;i++) cout<<'0';
		cout<<"1 ";
	}
	if(n==1)
	{
		cout<<1<<" ";
	}
	for(int i=1;i<=m;i++) cout<<1;
	return 0;
} 
```

---

## 作者：yu1128_AKIOI (赞：0)

## 思路

好像输出 $n$ 个 $1$ 和 $m$ 个 $1$ 即可。理由如下。

设一个数（若干个 $1$）为 $10^{a}+10^{a-1}+…+10^0$，另一个数（若干个 $1$）为 $10^{b}+10^{b-1}+…+10^0$。

则 $nm=(10^a+10^{a-1}+10^{a-2}+…+10^0)(10^b+10^{b-1}+10^{b-2}+…+10^0)$

$=10^{a+b}+10^{a+b-1}+…10^a+10^{a+b-1}+10^{a+b-2}+…+10^{a-1}+…10^b+10^{b-1}+…10^0$

$=10^{a+b}+2\times 10^{a+b-1}+3\times 10^{a+b-2}+…+3\times 10^2+2\times 10^1+10^0$

$=123…321$

好像是个回文数。

然而，当中间某一项系数 $>10$ 时，前一项就会进位，使其不为回文数。

那就只能把中间的 $1$ 改为 $0$。

这样，$nm=(10^a+1)(10^b+1)$

$=10^{a+b}+10^a+10^b+1$

$=100…010…010…01$ 或 $100…020…01$，为回文数。

注意特判 $n,m=1$ 的情况。

## 代码

```cpp
#include<iostream>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	if(n==1) cout<<1;
	else{
		cout<<1;
		while((--n)>1) cout<<0;
		cout<<1;
	}
	cout<<" ";
  	if(m==1) cout<<1;
  	else{
  		cout<<1;
		while((--m)>1) cout<<0;
		cout<<1;
	}
}

---

## 作者：chengjindong (赞：0)

[](https://www.luogu.com.cn/problem/P11568)

构造题。

$$

\begin{aligned}

&=1\underbrace{000 \cdots 000}_{n - 2\text{ 个 0}}1\times1\underbrace{000 \cdots 000}_{m-2 \text{ 个 0}}1 
\\ &=10^{n-1}\times 10^{m-1}+10^{n-1}+10^{m-1}+1
\\ &=10^{n+m-2}+10^{n-1}+10^{m-1}+1

\end{aligned}

$$

$10^{n+m-2}+10^{n-1}+10^{m-1}+1$ 明显是回文数，这就出现了通解，但需要 $n-2,m-2$，所以这种构造在 $n=1$ 或 $m=1$ 时是不对的，需要特判 $n=1,m=1$，此时，直接输出 $1$ 就行（因为另外一个也一定是回文数）。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define endl '\n'
using namespace std;
const int N=1e6+7;
const int M=1e6+7;
const int mod=1e9+7;
const double eps=1e-6;
signed main(){
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,m;
	cin >>n>>m;
	if(n==1){//特判 
		cout<<1;
	}else{//按照构造，正常输出 
		cout<<1;
		for(int i=0;i<n-2;i++){//n-2个0 
			cout<<0;
		}
		cout<<1;
	}
	cout<<" ";
	if(m==1){//特判 
		cout<<1;
	}else{//按照构造，正常输出 
		cout<<1;
		for(int i=0;i<m-2;i++){//m-2个0 
			cout<<0;
		}
		cout<<1;
	}
	return 0;
}
```

---

