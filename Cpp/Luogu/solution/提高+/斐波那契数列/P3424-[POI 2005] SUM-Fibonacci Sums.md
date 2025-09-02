# [POI 2005] SUM-Fibonacci Sums

## 题目描述

斐波那契数是一个这样定义的整数：$F(0)=1$，$F(1)=1$，$F(i)=F(i-1)+F(i-2)$  $(i>=2)$，前几个数是这样的 $1, 1, 2, 3, 5, 8, \ldots$ 

伟大的计算机学家 $\texttt{Byteazar}$ 正在做一个非凡的计算机，其中的数由斐波那契表示！

如一个数列 $b_1, b_2, \ldots , b_n$ 表示数字 $F(1) \times b_1+b_2 \times F(2)+ \ldots +b_n \times F(n)$（不使用 $F(0)$ ）。

不幸的是，这样的表示并不明确，即相同的数字可以有不同的表示。比如 $42$ 可以表示为 $(0,0,0,0,1,0,0,1)$，$(0,0,0,0,1,1,1,0)$ 或 $(1,1,0,1,0,1,1)$，于是  $\texttt{Byteazar}$ 加了一个限制：

- 如果 $n>1$，那么$b_n=1$，即数字的表示不包含前导零。
- 如果 $b_i=1$，那么 $b_{i+1}=0$，即数字的表示不包含两个（或多个）连续的数字。

这个计算机的建设比  $\texttt{Byteazar}$ 所认为的要难，现在请你来帮帮他~。

你需要写一个程序：

读取两个正整数的表示，计算并向标准输出写入其和的表示。

## 样例 #1

### 输入

```
4 0 1 0 1
5 0 1 0 0 1```

### 输出

```
6 1 0 1 0 0 1```

# 题解

## 作者：Alex_Wei (赞：10)

> **[P3424 [POI2005]SUM-Fibonacci Sums](https://www.luogu.com.cn/problem/P3424)*
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/poi.html)。

好题！先求和，再调整。

由于题目给出的 $x, y$ 是齐肯多夫表示法，所以简单地对应位求和 $z = x + y$ 后，$z_i = 0/1/2$。

考虑从高往低位调整，即依次保证长为 $1$ 的前缀，长为 $2$ 的前缀 …… 直到整个数都满足齐肯多夫表示法，类似 **数学归纳法**。因为从低到高涉及进位，很麻烦。下称满足齐肯多夫表示法为 **合法**。

我们发现最棘手的是 $z_i = 2$，别的都好办。由于 $0200 = 0111 = 1001$，考虑一次操作 $op(i)$ 表示令 $z_i\gets z_i - 2$，$z_{i + 1}\gets z_{i + 1} + 1$，$z_{i - 2}\gets z_{i - 2} + 1$。此时可能导致低位 $3$ 的出现，但是问题不大，因为我们只关心 $i$ 及其高位。

我们的目标是 **尽可能消掉 $2$**，自然不希望已经处理好的高位重新出现 $2$。由于 $i + 1$ 及其高位合法，所以不会出现连续的两个 $1$。因此，若 $z_{i + 1} = 1$ 且 $z_i \geq 2$，$op(i)$ 会令 $z_{i + 1}$ 变成 $2$。

不妨先执行进位操作，即 $z_i \gets z_i - 1$，$z_{i + 1}\gets z_{i + 1} - 1$，$z_{i + 2}\gets z_{i + 2} + 1$。由于 $z_{i + 2}$ 一定等于 $0$，所以进位后等于 $1$。同时，若 $z_{i + 3} = 1$，那么继续进位到 $z_{i + 4}$。称从 $i$ 开始不断进位的过程为 $\mathrm{flush}(i)$，其代码如下：

```cpp
void flush(int p) {while(z[p] && z[p + 1]) z[p + 2]++, z[p]--, z[p + 1]--, p += 2;}
```

注意，当 $i + 1$ 及其高位均合法时，操作才不会出错，即操作结束后 $i + 1$ 及其高位仍合法。容易证明这一点。否则可能出现数码 $2$。如当 $z_i = z_{i + 1} = z_{i + 2} = 1$ 时，这样的进位导致 $z_{i + 2} = 2$，破坏了齐肯多夫表示法，但若 $i + 1$ 及其高位合法，则不会出现 $z_{i + 1} = z_{i + 2} = 1$ 的情况。

执行完 $0$ 或 $1$ 次进位操作后，$z_{i + 1} = 0$，因此若 $z_i \geq 2$，再执行 $\mathrm{op}(i)$ 仅会将 $z_{i + 1}$ 变为 $1$，且由于 $z_i\leq 3$，故现在所有 $i$ 及其高位均有 $z \leq 1$，但 $i + 1$ 及其高位不一定合法，因为可能 $z_{i + 1} = z_{i + 2} = 1$。由于此时 $i + 2$ 及其高位合法，所以先 $\mathrm{flush}(i + 1)$，再 $\mathrm{flush}(i)$ 即可保证对于得到的结果，$i$ 及其高位合法。

啰里啰嗦这么一大堆，只是为了严谨证明以下做法的正确性：

- 从高到低考虑每一位 $i$。保证 $i + 1$ 及其高位合法。
- 首先 $\mathrm{flush}(i)$。
- 若 $z_i \geq 2$，则依次执行 $\mathrm{op}(i)$，$\mathrm{flush}(i + 1)$，$\mathrm{flush}(i)$。
- 此时 $i$ 及其高位合法。

特殊情况：$\mathrm{op}(2)$ 令 $z_1\gets z_1 + 1$，$z_2 \gets z_2 - 2$，$z_3\gets z_3 + 1$。$\mathrm{op}(1)$ 令 $z_1\gets z_1 - 2$，$z_2\gets z_2 + 1$。不难发现我们对高位的影响最多仅是令 $z_{i + 1}$ 加 $1$，和普通的 $\mathrm{op}(i)\ (i > 2)$ 是一样的，故特殊情况也一定合法。

时间复杂度分析：考虑 $d = \sum z_i$，每次进位均会让 $d$ 减少 $1$，而 `op` 不改变 $d$，故 `flush` 的总复杂度均摊为 $d$，即总时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, m, x[N];
void flush(int p) {while(x[p] && x[p + 1]) x[p + 2]++, x[p]--, x[p + 1]--, p += 2;}
int main() {
	cin >> n; for(int i = 1; i <= n; i++) scanf("%d", &x[i]);
	cin >> m; for(int i = 1, y; i <= m; i++) scanf("%d", &y), x[i] += y;
	if(m > n) n = m;
	for(int i = n; i; i--) {
		flush(i);
		if(x[i] >= 2) {
			if(i >= 2) x[i] -= 2, x[max(1, i - 2)]++, x[i + 1]++;
			else x[i + 1]++, x[i] -= 2;
			flush(i + 1), flush(i);
		}
	} for(int i = n + 2; i; i--) if(x[i]) {cout << (n = i) << " "; break;}
	for(int i = 1; i <= n; i++) putchar(x[i] + '0'), putchar(' ');
	return 0;
}
```

---

## 作者：caohan (赞：1)

# 思路

这道题说的那串东西实际上是齐肯多夫表示。

肯定是先相加，再求和。

加完了之后会出现：$0,1,2$。

要消去 $2$ 的话，必须要有以下四个式子（$x'=x+1$ 一位上加一）

$020x=100x'$

$030x=110x'$

$021x=110x$

$012x=101x$

当然，这也不能确保没有任何的相邻的 $1$。所以还要再用

$011x=100x$

来解决。

这样就完美了。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000002];
int n;
signed main()
{
	cin>>n; 
	for(int i=2;i<n+2;i++)
	{
		cin>>a[i];
	}
	cin>>n;
	int x;
	for(int i=2;i<n+2;i++)
	{
		cin>>x;
		a[i]+=x;
	}
	for(int i=1000001;i>=2;i--)
	{
		if(a[i]==0&&a[i-1]==2&&a[i-2]==0)
		{
			a[i]=1;
			a[i-1]=0;
			a[i-2]=0;
			a[i-3]++;
		}
		else if(a[i]==0&&a[i-1]==3&&a[i-2]==0)
		{
			a[i]=1;
			a[i-1]=1;
			a[i-2]=0;
			a[i-3]++;
		}
		else if(a[i]==0&&a[i-1]==2&&a[i-2]==1)
		{
			a[i]=1;
			a[i-1]=1;
			a[i-2]=0;
		}
		else if(a[i]==0&&a[i-1]==1&&a[i-2]==2)
		{
			a[i]=1;
			a[i-1]=0;
			a[i-2]=1;
		}
	}
	for(int i=1000001;i>=2;i--)
	{
		if(a[i]==0&&a[i-1]==1&&a[i-2]==1)
		{
			a[i]=1;
			a[i-1]=0;
			a[i-2]=0;
		}
	}
	if(a[1]==1)
	{
		a[2]=1;
	}
	for(int i=4;i<=1000001;i++)
	{
		if(a[i]==0&&a[i-1]==1&&a[i-2]==1)
		{
			a[i]=1;
			a[i-1]=0;
			a[i-2]=0;
		}
	}	
	int ptr;
	for(ptr=1000001;!a[ptr];ptr--);
	cout<<ptr-1<<' ';
	for(int i=2;i<=ptr;i++)
	{
		cout<<a[i]<<" ";
	}
	return 0;
}
```

# AD

[My Blog](https://www.luogu.com.cn/blog/713916/)

# 参考资料

[齐肯多夫表示法的介绍](https://zimpha.github.io/algonotes/zeckendorf-arithmetic/)




---

## 作者：Argon_Cube (赞：1)

本题解搬自 [zimpha's blog:Zeckendorf Arithmetic](https://zimpha.github.io/algonotes/zeckendorf-arithmetic/)。

* **【题目链接】**

[Link:P3424](https://www.luogu.com.cn/problem/P3424)

* **【解题方法】**

题目中的整数表示方式其实就是`Zeckendorf representation`。

这一题实际上就是做加法。

首先，我们像高精加一样，直接把两个数的`Zeckendorf representation`加起来。就是，一位一位的加起来。拿样例举例，加完了之后像这样：`1 1 0 2 0`（题目中输入是从低位到高位，这里采用从高位到低位）。

然后，我们考虑把那些不合法的地方消去。具体来讲，从高到低遍历。我们的首要任务是把 $2$ 与 $3$ 消去。当然，本来是没有 $3$ 的。不过，我们在把 $2$ 消去的过程中，可能会把某个 $2$ 加 $1$。如果我们用 $\color{brown}x$ 代表 $x+1$，规则是这样的：

$$
\begin{aligned}
020x&\to100{\color{brown}x}\\030x&\to110{\color{brown}x}\\021x&\to110 x\\012x&\to 101x
\end{aligned}
$$

当然，我们可能要特殊处理最后几位。不过，如果我们把 $F_0=1$ 和 $F_{-1}=0$ 加入表示中，我们就可以不用特殊处理。不过，如果表示中含有 $F_{-1}$，那直接忽略就行了。如果含有 $F_{0}$ 呢？我们稍后处理。

现在我们处理连续的 $1$。我们用两次 $011\to100$，第一次从高位到低位，第二次从低位到高位。第一次做完后，没有连续的 $3$ 个 $1$，表示中不可能同时含有 $F_0$ 和 $F_1$，所以如果表示中有 $F_0$ 那么直接把它变成 $F_1$ 即可。在这个基础上，第二遍直接做即可。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

array<int,1000002> fib_rep;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt;
	cin>>cnt;
	for(int i=2;i<cnt+2;i++)
		cin>>fib_rep[i];
	cin>>cnt;
	for(int i=2;i<cnt+2;i++)
		cin>>fib_rep[0],fib_rep[i]+=fib_rep[0];
	fib_rep[0]=0;
	for(int i=1000001;i>=2;i--)
		if(fib_rep[i]==0&&fib_rep[i-1]==2&&fib_rep[i-2]==0)
			fib_rep[i]=1,fib_rep[i-1]=0,fib_rep[i-2]=0,fib_rep[i-3]++;
		else if(fib_rep[i]==0&&fib_rep[i-1]==3&&fib_rep[i-2]==0)
			fib_rep[i]=1,fib_rep[i-1]=1,fib_rep[i-2]=0,fib_rep[i-3]++;
		else if(fib_rep[i]==0&&fib_rep[i-1]==2&&fib_rep[i-2]==1)
			fib_rep[i]=1,fib_rep[i-1]=1,fib_rep[i-2]=0;
		else if(fib_rep[i]==0&&fib_rep[i-1]==1&&fib_rep[i-2]==2)
			fib_rep[i]=1,fib_rep[i-1]=0,fib_rep[i-2]=1;
	for(int i=1000001;i>=2;i--)
		if(fib_rep[i]==0&&fib_rep[i-1]==1&&fib_rep[i-2]==1)
			fib_rep[i]=1,fib_rep[i-1]=0,fib_rep[i-2]=0;
	if(fib_rep[1]==1)
		fib_rep[2]=1;
	for(int i=4;i<=1000001;i++)
		if(fib_rep[i]==0&&fib_rep[i-1]==1&&fib_rep[i-2]==1)
			fib_rep[i]=1,fib_rep[i-1]=0,fib_rep[i-2]=0;
	int ptr;
	for(ptr=1000001;!fib_rep[ptr];ptr--);
	cout<<ptr-1<<' ';
	for(int i=2;i<=ptr;i++)
		cout<<fib_rep[i]<<' ';
	return 0;
}
```

---

## 作者：100Accepted (赞：0)

先逐位相加，然后要消去所有大于 $1$ 的数。从 $n$ 到 $1$ 倒序枚举，可以避免存在连续两个 $1$ 的情况。简单计算后得到如下规律：

当 $n>2$ 时，$f[n]+f[n]=f[n+1]+f[n-2]$。

当 $n=2$ 时，$f[2]+f[2]=f[1]+f[3]$。

当 $n=1$ 时，$f[1]+f[1]=f[2]$。

据此化简。


```cpp
#include<iostream>
using namespace std;
int x,y,z[100005],i,p,l;
void ok(int k){
	while (z[k]&&z[k+1]) 
		z[k]--,z[k+1]--,z[k+2]++,k+=2;
}
int main(){
	for(i=0;i<99999;i++)z[i]=0;//初始化
	scanf("%d",&x);
	for(i=1;i<=x;i++){
		scanf("%d",&z[i]);
	}
	scanf("%d",&y);
	for(i=1;i<=y;i++){
		scanf("%d",&p);
		z[i]+=p；//累加
	}
	if(y>x)x=y;
	for(i=x;i>=1;i--){//倒序枚举
		ok(i);
		while(z[i]>=2){
			if(i>2)z[i]-=2,z[i+1]++,z[i-2]++;
			else if(i==2){
				z[i]-=2;z[i+1]++,z[i-1]++;
			}
			else z[i]-=2,z[i+1]++;
			ok(i+1);ok(i);
		}
	}
	for(i=x+2;i>=1;i--){
		if(z[i]){
			x=i;break;
		}
	}
	printf("%d ",x);
	for(i=1;i<=x;i++){
		printf("%d ",z[i]);
	}
    return 0;
}
```

---

