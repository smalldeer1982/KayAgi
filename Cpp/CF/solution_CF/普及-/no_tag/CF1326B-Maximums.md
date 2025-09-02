# Maximums

## 题目描述

Alicia has an array, $ a_1, a_2, \ldots, a_n $ , of non-negative integers. For each $ 1 \leq i \leq n $ , she has found a non-negative integer $ x_i = max(0, a_1, \ldots, a_{i-1}) $ . Note that for $ i=1 $ , $ x_i = 0 $ .

For example, if Alicia had the array $ a = \{0, 1, 2, 0, 3\} $ , then $ x = \{0, 0, 1, 2, 2\} $ .

Then, she calculated an array, $ b_1, b_2, \ldots, b_n $ : $ b_i = a_i - x_i $ .

For example, if Alicia had the array $ a = \{0, 1, 2, 0, 3\} $ , $ b = \{0-0, 1-0, 2-1, 0-2, 3-2\} = \{0, 1, 1, -2, 1\} $ .

Alicia gives you the values $ b_1, b_2, \ldots, b_n $ and asks you to restore the values $ a_1, a_2, \ldots, a_n $ . Can you help her solve the problem?

## 说明/提示

The first test was described in the problem statement.

In the second test, if Alicia had an array $ a = \{1000, 1000000000, 0\} $ , then $ x = \{0, 1000, 1000000000\} $ and $ b = \{1000-0, 1000000000-1000, 0-1000000000\} = \{1000, 999999000, -1000000000\} $ .

## 样例 #1

### 输入

```
5
0 1 1 -2 1```

### 输出

```
0 1 2 0 3```

## 样例 #2

### 输入

```
3
1000 999999000 -1000000000```

### 输出

```
1000 1000000000 0```

## 样例 #3

### 输入

```
5
2 1 2 2 3```

### 输出

```
2 3 5 7 10```

# 题解

## 作者：AutumnKite (赞：4)

由 $c_i$ 的定义可得
$$\begin{aligned} b_i&=a_i-c_i \\&=a_i-\max\{0,\max\limits_{j=1}^{i-1} a_j\} \end{aligned}$$

移项后可得
$$a_i=b_i+\max\{0,\max\limits_{j=1}^{i-1}a_j\}$$

我们只要在递推的同时维护 $a_1,a_2,\cdots,a_{i-1}$ 的最大值即可。

时间复杂度 $O(n)$。

```cpp
const int N = 200005;
int n, a[N];
void solve(){
	read(n);
	for (register int i = 1; i <= n; ++i) read(a[i]);
	long long now = 0;
	for (register int i = 1; i <= n; ++i)
		if (a[i] > 0) now += a[i], print(now, ' ');
		else print(now + a[i], ' ');
	putchar('\n');
}
```

---

## 作者：xht (赞：2)

依照题意，我们可以得到一个递推式 $a_n = \max_{i=1}^{n-1} a_i + b_n$，时间复杂度 $\mathcal O(n)$。

```cpp
const int N = 2e5 + 7;
int n;
ll a[N], x;

int main() {
	rd(n), rda(a, n);
	for (int i = 1; i <= n; i++)
		print(x + a[i], " \n"[i==n]), x = max(x, x + a[i]); 
	return 0;
}
```

---

## 作者：Aehnuwx (赞：1)

因为 $x_i=\max\{0,a_1\sim a_{i-1}\}$，所以当 $i=1$ 时，$x_i=0$。

又因为 $b_i=a_i-x_i$，所以 $b_1=a_1-x_1=a_1-0=a_1$。

以此类推，$b_2=a_2-x_2=a_2-\max\{0,a_1\sim a_{2-1}\}=a_2-\max\{0,a_1\}$，$b_3=a_3-x_3=a_3-\max\{0,a_1\sim a_{3-1}\}=a_3-\max\{0,a_1\sim a_2\}$，……

因为数组 $b$ 的值已知，所以只需维护 $\max\{a_1\sim a_{i-1}\}$ 的值即可得到数组 $a$ 的值。

Code:
```cpp
const int maxN=200005;
int n,b[maxN],a[maxN];
int main() {
	cin>>n;
	for (int i=1;i<=n;i++) cin>>b[i];
	a[1]=b[1];
	int maxx=max(a[1],0);
	for (int i=2;i<=n;i++) a[i]=maxx+b[i],maxx=max(0,max(maxx,a[i]));
	for (int i=1;i<=n;i++) cout<<a[i]<<' ';
}
```


---

## 作者：Fairicle (赞：1)

对于这题我们可以发现，输入的 $b_1$ $=$ $a_1-0$，对此我们就知道了 $a_1$，接着往后推，$b_2$ $=$ $a_2-max(0,a_1)$，也可以求出 $a_2$，显然我们可以不断地求出 $a$ 数组，前提是我们维护了前 $i-1$ 个数的最大值。

代码更容易看懂。

```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ri register int
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
int n,maxn;
int b[2000010],a[2000010];
int main()
{
	n=read();
	maxn=read();a[1]=maxn;
	for(ri i=2;i<=n;++i)
	{
		b[i]=read();
		a[i]=b[i]+maxn;
		maxn=max(a[i],maxn);
	}
	for(ri i=1;i<=n;++i) cout<<a[i]<<" ";
    return 0;
}
```


---

## 作者：andyli (赞：1)

题意：  
Alicia 有一个长度为 $n$ 的非负整数序列 $a$ ，现有另一个非负整数序列 $x$ ，满足 $x_i = \max\{0, a_1, ..., a_{i-1}\}$，随后她计算出一个序列 $b$ 满足 $b_i=a_i-x_i$ 。  
请你根据数组 $b$ 复原序列$a$ 。  
$3\leq n\leq 2\times 10^5, -10^9\leq b_i\leq 10^9$

分析：  
将 $b_i=a_i-x_i$ 变形后得 $a_i=b_i+x_i$ ，即 $a_i=b_i+\max\{0, a_1, ..., a_{i-1}\}$，在扫描序列 $b$ 的同时维护一个 $mx=\max\{0, a_1, ..., a_{i-1}\}$ ，则每次只需输出 $b_i+mx$ 即可。  
时间复杂度 $\mathcal O(n)$ 。  

代码如下 ([快读模板](https://www.luogu.com.cn/blog/andyli/read-template))：  
```cpp
const int maxn = 200005;

int B[maxn];
int main()
{
    int n;
    io.read(n);
    for (int i = 1; i <= n; i++)
        io.read(B[i]);
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        int a = mx + B[i];
        mx = std::max(mx, a);
        io.write(a, " \n"[i == n]);
    }
    return 0;
}
```

---

## 作者：StudyingFather (赞：1)

根据题意可以看出，本题存在递推式 $b_i=a_i-\max\{0,a_i-1\}$，这样我们就可以在 $O(n)$ 的时间内算出整个 $a$ 序列了。

```cpp
// Problem : B. Maximums
// Contest : Codeforces Global Round 7
// URL : https://codeforces.com/contest/1326/problem/B
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
using namespace std;
int main()
{
 int n;
 long long s;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  int x;
  cin>>x;
  if(x>=0)cout<<(s+=x)<<' ';
  else cout<<s+x<<' ';
 }
 return 0;
}
```

---

## 作者：Suyun (赞：0)

首先，$c[1] = 0$，$a[1] = b[1] + c[1] = b[1]$。

然后 $\forall i \ge 2, c[i] = \max(c[i - 1], a[i])$，即 $c[i] = \max(c[i - 1], b[i - 1] + c[i - 1])$。

递推即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	
	vector<int> b(n);
	for (int i = 0; i < n; ++i) {
		cin >> b[i];
	}
	
	int c = 0;
	for (int i = 0; i < n; ++i) {
		cout << b[i] + c << ' ';
		c = max(c, b[i] + c);
	}
	
	cout << endl;
}
```

---

## 作者：Aw顿顿 (赞：0)

这道题目是锻炼思考数列之间关系性质能力的一个好题目。

首先解释一下这个数列的定义：

- $c_i=\max\{0,a_1,a_2,\ldots a_{i-1}\}$

也就是说，$c_i$ 是 $a$ 数列中 $0$ 和前 $i-1$ 项当中最大的。

- $b_i=a_i-c_i$

也就是说，$b$ 数列的每一项都是 $a_i$ 与 $c_i$ 之差。

那么我们可以想到一种办法：按照题意模拟。

这时候可以想到一个十分方便而且易于理解的步骤：

- 首先读入 $n$，也就是接下来有 $n$ 个数需要读入。

- 接着开始循环，循环变量 $i=0,1\ldots n-1$。

- 然后每次读入数列中的一个数 $x$。

接着，请注意，核心部分：

- 输出目前的数列的这一项：即加上了新的一项的最大值 $x+mx$。

- 如果 $x>0$ ，也就是说 $mx+x$ 不会比原来更小，那就可以更新至最大值。

最后，在循环中我们已经完成了输出的任务，所以就可以结束主函数，需要用到的语句是`return 0;`。

如果你希望用代码进行对拍，请移步最后的代码区域，否则，接下来先展示的代码是有注释说明的：

```cpp
#include<bits/stdc++.h>//万能头文件，慎用，容易撞关键字
using namespace std;//使用std的命名空间
int n,mx,x;//定义变量，x为b数列，mx为最大值，n为数字个数
//定义在全局的变量自动初始化为0
int main(){//主函数
    cin>>n;//输入n，准备循环读入数列
    for(register int i=0;i<n;++i){
        cin>>x;//每次给定bi
        cout<<x+mx<<' ';//根据已经提到的求差性质，输出每一项的对应数列
        if(x>0){//如果这个x不会导致目前的ai更小
            mx+=x;//那么在这个数列中的最大值必然会更新至更大
        }
    }
    return 0;//结尾返回0值，更加保险
}
```

然后再次强调，如果将这几个变量定义在主函数内，系统会随机给他们赋值，所以请一定定义全局变量。这对于每次都要读入更新的 $x$ 和 $n$ 影响不大，但是对于用于统计答案的 $mx$ 来说，没有初始化意味着抱灵。

然后给出适合对拍的无注释代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, mx, x;
int main() {
    cin >> n;
    for (register int i = 0; i < n; ++ i){
        cin >> x;
        cout << x + mx << ' ' ;
        if (x > 0) {
            mx += x;
        }
    }
    return 0;
}
```

这是有空格的版本，如果您不适应这种码风，那么可以参照有注释代码。

---

