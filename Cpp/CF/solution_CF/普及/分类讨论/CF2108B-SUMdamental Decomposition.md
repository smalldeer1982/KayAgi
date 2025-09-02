# SUMdamental Decomposition

## 题目描述

在最近的一次生日中，你最好的朋友 Maurice 给了你一对数字 $n$ 和 $x$，并要求你构造一个长度为 $n$ 的正数数组 $a$，使得 $a_1 \oplus a_2 \oplus \cdots \oplus a_n = x$ $^{\text{∗}}$。

这个任务对你来说太简单了，因此你决定给 Maurice 一个回礼：在所有满足条件的数组中，构造一个元素和最小的数组。你立刻想到了一个合适的数组；然而，由于把它写下来太费时间，Maurice 只能得到它的元素和。

$^{\text{∗}}$ $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 说明/提示

在第一个测试用例中，一个合适的数组是 $[2, 3]$。可以证明无法获得更小的数组元素和。

在第二个测试用例中，一个合适的数组是 $[1, 3, 4]$。同样可以证明这是最优的和。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2 1
3 6
1 0
2 0
5 0
2 27
15 43
12345678 9101112```

### 输出

```
5
8
-1
2
8
27
55
21446778```

# 题解

## 作者：Zskioaert1106 (赞：3)

题目传送门：[CF2108B SUMdamental Decomposition](https://www.luogu.com.cn/problem/CF2108B)

答应我，这样的分类讨论不要出在 OI 赛制好吗？

### 做题过程

一整个特判过的。

- 当 $n=1$，若 $x>0$ 返回 $x$，否则无解。

- 当 $x=0$，若 $n$ 为偶数答案为 $n$，否则答案为 $n+3$。  
这个其实好理解，偶数就全是 $1$，奇数就一堆 $1$ 加上一个 $2$ 一个 $3$。

- 当 $x=1$，若 $n$ 为奇数答案为 $n$，偶数为 $n+3$。（思路与上面类似）

开始讨论其它情况。

我们考虑尽量将 $x$ 的每一位分配到一个数上，这样剩下空的 $a_i$ 最少。

```cpp
while(x){
  n-=(x&1);
  x>>=1;
}
```

此时如果剩下的 $n \leqslant 0$，直接返回 $x$ 就行了。因为所有的数都非空，且总和一定是 $x$。

否则呢？

如果剩下的 $n$ 是偶数，就全设成 $1$。否则我们需要找一个有值的 $a_i$ 跟它们一块加 $1$。显然一定可以找到一个 $a_i$ 在 $2^0$ 那位为 $0$。

### 代码实现

```cpp
#include<iostream>
using namespace std;
int t,n,x;
int solve(){
	if(n==1)return (x?x:-1);
	if(!x)return ((n&1)?n+3:n);
	if(x==1)return ((n&1)?n:n+3);
	int ans=x;
	while(x)n-=(x&1),x>>=1;
	if(n<=0)return ans;
	return ans+n+(n&1);
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		cout<<solve()<<'\n';
	}
	return 0;
}
```

[AC on CF](https://codeforces.com/contest/2108/submission/320482304)。

---

## 作者：ZMQ_Ink6556 (赞：2)

## 题解：CF2108B SUMdamental Decomposition

### 解题思路

要求使用正整数异或得 $x$，所以很明显不能在只用一个数的时候得到 $0$。所以当且仅当 $n = 1 , x = 0$ 时输出 $-1$。

由于异或的性质，要使两个位置无效则最少花费的代价是 $2$，因为两个 $1$ 异或起来会抵消为 $0$。使 $3$ 个位置无效的最少花费是 $6$，需要令 $1 , 2 , 3$ 异或在一起，此时二进制位上的最低位和次低位都出现恰好两个 $1$，所以为 $0$。我们发现将奇数个位置异或起来会更亏，所以尽量少使用。

为了尽量节省开销，我们将 $x$ 拆分成尽量多个数，可以发现，代价最低的拆分方法是将每个不为零的二进制位单独拆开，这样没有相互的抵消还能占据尽量多的位数。

根据以上 $3$ 个发现，我们可以进行分类讨论（记 $x$ 的二进制位上有 $k$ 个 $1$）：

- $n =1 $ 且 $x = 0$：输出 $-1$。
- $n \le k$：输出 $x$。
- $n - k$ 是偶数：输出 $x + n - k$（拆分为每个二进制位放置后全放 $1$）。
- $n - k$ 是奇数且 $x > 1$：输出 $x + n - k + 1$（在其中一个 $> 1$ 的二进制位上 $+ 1$，后面全放 $1$）。
- $n - k$ 是奇数且 $x \le 1$：输出 $n + 3$（只能用奇数的方法）。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long t , n , x , cnt;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> x;
		if(n == 1 && x == 0)
		{
			cout << "-1\n";
			continue;
		}
		cnt = 0;
		for(long long i = 0 ; i <= 30 ; i++)
		{
			if((x >> i) & 1)
			{
				cnt++;
			}
		}
		if(n <= cnt)
		{
			cout << x << '\n';
		}
		else if((n - cnt) % 2 == 0)
		{
			cout << x + (n - cnt) << '\n';
		}
		else
		{
			if(x <= 1)
			{
				cout << n + 3 << '\n';
			}
			else
			{
				cout << x + (n - cnt + 1) << '\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：Manki23333333 (赞：2)

#### 闲话

交错题了，B 题交到 C 题上了，令人汗颜！

#### 翻译 

给定 $n, x$，构造 $n$ 个元素的数组 $a$ 使得 $\mathop{\oplus}\limits_{i=1}^{n}a_i=x$，且最小化 $\sum\limits_{i=1}^na_i$。

#### 解析

显然将 $x$ 二进制拆位。记 $s$ 为二进制下 $x$ 中 $1$ 的个数。

如果 $s \ge n$，显然我们可以让一个数字去凑一个二进制位，少的我们用一个字符就可以补齐。这样每个数字二进制位都是不重复的，那就是加法啊。所以这种情况输出 $x$ 即可。

如果 $s \lt n$，分 $n - s$ 的奇偶讨论。如果是偶数，显然全填 $1$ 是最优解；如果是奇数，只需要让去填 $x$ 的二进制位的那部分抽一个 $1$ 过来，答案比偶数多 $1$。

需要注意的细节：

- $n=1, x=0$ 特判无解。
- $x=1$ 特判，分 $n$ 奇偶考虑。奇数只需要全填 $1$，答案为 $n$；偶数只能填 $2, 3$ 凑一个 $1$，所以输出 $(n - 2) + 2 + 3 = n + 3 $。
- $s < n, n$ 为奇数的情况，当 $x = 0$ 时，上面抽不出一个 $1$。因为 $n = 1$ 的情况已经特判掉了，所以 $n \ge 2$。这样就可以仿照 $x=1$ 的情况填 $2, 3$。

#### 赛时 AC 代码（注释已对侮辱性词汇打码）

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, x, sum;
void Turn () {
	cin >> n >> x;
	
	if (n == 1 && x == 0) {
		cout << -1 << endl;
		return ;
	}
	
	if (x == 1) { // 这******啥东西
		if (n % 2 == 1) {
			cout << n << endl;
		} else {
			cout << n + 3 << endl;
		}
		return ;
	}
	
	int p = x;
	sum = 0;
	while (x) {
		sum += x % 2;
		x /= 2;
	}
	x = p;
	
	if (sum >= n) { // 一个位一个位拼，没重复，少的拿一个位补
		cout << x << endl;
		return ;
	}
	
	// 有多的
	int more = n - sum;
	// 本来 sum 个就能干完活了，非要添点乱子
	
	if (more % 2 == 0) { // 偶数全填 1
		cout << x + more << endl;
	} else { // ******的******玩意儿，这******怎么过样例的我都不知道
		if (x == 0) {
			cout << x + more + 3 << endl;
			return ;
		}
		
		cout << x + more + 1 << endl;
	}
}

signed main () {
	int T = 1;
	cin >> T;
	
	while (T --) {
		Turn ();
	}
	
	return 0;
}
```

---

## 作者：include13_fAKe (赞：1)

五一节晚上打了这场 CF 切了这题，讲下思路。

---

考虑将 $n$ 二进制拆分。分类讨论：

- 若可以拆成 $\ge x$ 个数，将其合并为 $x$ 个（合并直接相加）。答案即为 $n$。
- 若只能拆成 $<x$ 个数，考虑填上**重复的较小的数**，举例如下：

> $n=7,x=5$ 时，前 $3$ 个数填上 $4,2,1$，剩下的填上 $1$ 即可。  
> $x=6$ 咋办？考虑将后 $3$ 个数先填上 $1$，再在第 $1$ 个数加 $1$ 变成 $5$ 即可。

一个特例是 $n=1$ 的情况，此时若只剩一个数未被染色，需要和另外一个数一起加 $2$ 才满足条件（可证明此时 $x$ 为偶数）。

$x=0$ 的情况类似处理即可，无解当且仅当 $n=1,x=0$。

每一次求解都是 $O(1)$ 的，能够完成。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int popcnt(int x){
	if(x<2)	return x;
	return popcnt(x/2)+(x%2);
}
void solve(){
	int n,x;
	cin>>n>>x;
	if(x==0&&n==1){
		cout<<-1<<endl;
		return;
	}
	else if(x==0&&n%2==0){
		cout<<n<<endl;
		return;
	}
	else if(x==0){
		cout<<(n-1)+4<<endl;
		return;
	}
	int c=popcnt(x);
	if(c>n){
		cout<<x<<endl;
		return;
	}
	int d=n-c;
	if(d%2)	d++;
	int include13=x+d;
//	cout<<x<<' '<<d<<endl;
	if(x==1&&n%2==0)	include13+=2;
	cout<<include13<<endl;
}
int T;
signed main(){
	cin>>T;
	while(T--)	solve();
	return 0;
} 
```

---

## 作者：feng_0108 (赞：1)

# 题目大意
输入一个 $n$ 和 $x$，构造一个长度为 $n$ 的数组，使得 $a_1 \oplus a_2 \oplus ... \oplus a_n = x$，并输出 $\sum_{i = 1}^{n} a_i$ 的最小值。
# 解题思路
在解决问题之前，我们需要知道 $a \oplus a = 0$，那么为了使得 $\sum_{i = 1}^{n} a_i$ 尽可能的小，我们需要构造尽可能少的 $1$，且 $1$ 的个数为偶数，这样异或结果等于 $0$。另外，为了使得最终异或结果等于 $x$，需要统计 $x$ 中二进制为 $1$ 的个数。知道了解题思路我们需要考虑以下情况：
## 情况一：$x = 0$ 
如果 $n$ 为偶数，那么 $n$ 个 $1$ 异或结果为 $0$；如果 $n$ 为奇数，那么需要用一次 $1 \oplus 2 \oplus 3$ 把 $n$ 转换成偶数。
## 情况二：$x = 1$ 
如果 $n$ 为奇数，那么必然不可能出现奇数异或等于 $1$ 的情况；如果 $n$ 为偶数，那么需要 $2 \oplus 3$ 来生成一个 $1$，并使得 $n - 2$ 个 $1$ 相互异或得 $0$。
## 情况三：$c \ge n$ 
这个时候直接输出 $x$ 即可，想想为什么。
## 情况四：$c < n$ 
我们要尽可能得腾出偶数个 $1$ 的情况出来， $\lceil \frac{n - c}{2} \rceil \times 2$ 向上取整能保证尽可能少的偶数个 $1$。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
typedef long long LL;

int t, n, x; 

void solve() {
    cin >> n >> x;
    if(x == 0) {
    	if(n % 2) {
    		if(n >= 3) {cout << n + 3 << endl;return;}
    		else {cout << -1 << endl;return;}
    	}
    	else {cout << n << endl;return;}
    }
    if(x == 1) {
    	if(n % 2 == 0) 
    		if(n >= 2) {cout << n + 3 << endl;return;}
    	else
    		{cout << -1 << endl;return;}
    }
    
    int c = 0, xx = x;
    while(xx) {
    	if(xx & 1) c ++;
    	xx >>= 1;
    }
    
    if(c >= n) {
    	cout << x << endl;
    	return;
    }
    else {
    	int tmp = ceil((n - c) * 1.0 / 2) * 2;
    	cout << tmp + x << endl;
    }
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> t;
	while(t -- )
      solve();
	return 0;
 } 

```

---

## 作者：cjh20090318 (赞：1)

## 题意

你需要构造一个长度为 $n$ 的**正整数**序列 $a$，使得 $a$ 的元素异或和为 $x$。

求符合条件的 $a$ 序列元素和的最小值。

## 分析

定义 $\operatorname{popcount}(x)$ 为 $x$ 在二进制下 $1$ 的个数，令 $p = \operatorname{popcount}(x)$。

### 当 $n \le p$  时

对 $x$ 进行二进制拆分，分别作为不同的元素，此时总元素和为 $x$，不存在比这个更小的答案。

例如对于第六个样例 $n=2,x=27=2^4+2^3+2^1+2^0$，某一种方案是拆成序列 $2^4=16,2^3+2^1+2^0=11$，此时元素和为 $27$。

### 当 $n > p$ 时

只能将 $x$ 二进制拆分为 $p$ 个元素，为了达到 $n$ 个元素此时需要填充额外的元素，最有策略是尽可能使用 $1$。

#### 填充偶数个 $1$，即 $n - p \equiv 0 \pmod{2}$ 时

添加的 $n-p$ 个 $1$ 的异或和为 $0$，总元素和为 $x + (n - p)$。

#### 填充奇数个 $1$，即 $n - p \equiv 1 \pmod{2}$ 时

直接添加 $n-p$ 个 $1$ 的异或和为 $1$，需要调整一个元素来修正异或和。

- 若 $x > 1$，将 $x$ 最高位对应的元素加 $1$，总元素和为 $x+(n-p)+1$。

  例如第二个样例 $n=3,x=6=2^2+2^1$，构造出的序列即为 $2^2+1=5,2^1=2,1$，此时总元素和为 $8$。

- 若 $x = 1$，此类情况下的 $n$ 为偶数。

  如果序列中只有 $1$ 肯定是不可行的，此处引入数列 $2,3$ 来调和。

  构造方案即为在 $2,3$ 后添加 $n-2$ 个 $1$，元素总和为 $n+3$。

- 若 $x=0$，此类情况下的 $n$ 为奇数。

  $n = 1$ 显然无解。

  其余情况类似于 $x=1$，构造方案即为在 $2,3$ 后添加 $n-2$ 个 $1$，元素总和为 $n+3$。

单次询问时间复杂度 $O(1)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
using namespace std;
int n,x;
void solve(){
    scanf("%d%d",&n,&x);
    int p=__builtin_popcount(x);
    if(n<=p) printf("%d\n",x);
    else if((n-p)&1) printf("%d\n",!x&&n==1?-1:x<=1?n+3:x+n-p+1);
    else printf("%d\n",x+n-p);
}
int main(){
    int T;scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：Ag2WO4 (赞：1)

考虑分类讨论。

- $x=0$ 的情况：
  - $n$ 为偶数时直接 $n$ 个 $1$ 相消即可，答案为 $n$；
  - $n$ 为奇数时：
    - $n=1$ 显然无解；
    - 否则最简单的奇数异或和归零是 $3\oplus 2\oplus 1=0$ ，剩下的 $n-3$ 个 $1$ 相消即可，答案为 $n+3$；
- $x\neq 0$ 的情况，优先根据 $x$ 各位中 $1$ 的数量分配：
  - 若无剩余位输出 $x$ 即可；
  - 若剩余 $k$ 位则按 $1$ 成对消除的原则，不成对的从分配位中借位：
    - 注意特判 $x=1$ 且 $n$ 为偶数的情况要借第二位，答案为 $n+3$；
    - 否则若 $k$ 为奇数答案为 $k+x+1$；
    - 若 $k$ 为偶数答案为 $k+x$。

在 Python 中可以使用 ```int.bit_count()``` 函数求 $x$ 各位中 $1$ 的数量，在 C/C++ 中则可以使用 ```__builtin_popcount(int)```。复杂度 $O(1)$。

Python 代码
```python
for i in range(int(input())):
    n,x=map(int,input().split())
    if x:
        k=n-x.bit_count()
        if k<=0:print(x)
        elif x==1 and k&1:print(n+3)
        elif k&1:print(x+k+1)
        else:print(x+k)
    else:
        if n==1:print(-1)
        elif n&1:print(n+3)
        else:print(n)
```
C/C++ 代码
```c
#include<stdio.h>
int i,x,n,k;
int main()
{
    scanf("%d",&i);
    while(i--)
    {
        scanf("%d%d",&n,&x);
        if(x)
        {
            k=n-__builtin_popcount(x);
            if(k<=0)printf("%d\n",x);
            else if(x==1&&k&1)printf("%d\n",n+3);
            else if(k&1)printf("%d\n",x+k+1);
            else printf("%d\n",x+k);
        }
        else
        {
            if(n==1)puts("-1");
            else if(n&1)printf("%d\n",n+3);
            else printf("%d\n",n);
        }
    }
}
```

---

## 作者：wangboyue (赞：1)

# 思路
为了方便理解，接下来使用表格的形式表示二进制下的 $a$。例如，

||1|2|3|
|:-:|:-:|:-:|:-:|
|(4)||1|1|
|(2)||1||
|(1)|1||1|

表示 $a_1=1,a_2=2+4=6,a_3=1+4=5$。   
明显，当 $n\le \operatorname{popcount}(x)$ 时，可以构造一组解，使得答案达到最小值 $x$。以样例 `2 27` 为例：

||1|2|
|:-:|:-:|:-:|
|(16)||1|
|(8)||1|
|(4)|||
|(2)|1||
|(1)|1||

可以任意左右移动二进制 $1$ 的位置，只要每个数字不为 $0$。  
当 $n>\operatorname{popcount}(x)$ 时，先观察 $x\ge2$ 的一般情况，以 `3 6` 为例：

||1|2|3|
|:-:|:-:|:-:|:-:|
|(8)||||
|(4)||||
|(2)||1||
|(1)|1|**1**|**1**|

即使我们尽可能拆散 $x$，也会还有 $n-\operatorname{popcount}(x)$ 个数字为 $0$。根据异或的性质，我们可以在两个数字中都添加一个二进制 $1$（在表格中的加粗部分）。此时答案为 $x+n-\operatorname{popcount}(x)+p$，其中当 $n-\operatorname{popcount}(x)$ 为奇数时 $p=1$，否则 $p=0$。  
当 $x=1$ 且 $n$ 为奇数时，类似地，答案为 $n$。当 $n$ 为偶数，以 `2 1` 为例：

||1|2|
|:-:|:-:|:-:|
|(2)|**1**|**1**|
|(1)|1||

此时在最后一对数字中，二进制位 $1$ 被占用，只能将它们加 $2$。答案为 $n+3$。  
当 $x=0$，类似地，$n$ 为偶数时答案为 $n$，$n$ 为奇数时答案为 $n+3$。作为例外，$n=1$ 时无解，因为数字必须是正数，且没有其它数字与它异或使异或和为 $0$。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int help(){
	int n,x;
	cin>>n>>x;
	int b=__builtin_popcountll(x);
	if(n<=b){
		return x;
	}
	else if(x==1){
		if(n%2==1){
			return n;
		}
		else{
			return n+3;
		}
	}
	else if(x==0){
		if(n==1){
			return -1;
		}
		else if(n%2==0){
			return n;
		}
		else if(n%2==1){
			return n+3;
		}
	}
	int ne=n-b;
	if(ne%2==1){
		ne++;
	}
	return x+ne;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		cout<<help()<<endl;
	}
	return 0;
}
```

---

## 作者：xueshengyi (赞：0)

## 题目大意

给定 $n$ 和 $x$，构造一个长度为 $n$ 数组 $A$，使得 $A$ 各项的异或的值为 $x$，使得 $A$ 的各项值和最小，若无解输出 ```-1```。

## 题解

先考虑答案为 $-1$ 的情况：显然，只有当 $n=1$ 且 $x=1$ 时，答案为 $-1$。

除此之外，当 $n=1$ 时，直接输出 $x$ 即可。

先对 $x$ 进行二进制分解，每位上有 $1$ 的数字尽可能平分给 $n$ 个数字，即每位数字分给 $A$ 中的一个数字。

如果此时 $n$ 个数字仍有为 $0$ 的，就在最末尾两个两个加 $1$ 即可，只要两个两个加，就不会影响原来的 $x$。

举个例子：

假如 $n=3$，$k=6$。

$k$ 的二进制表示为 $110$。

先将前两个 $1$ 都各分给 $n$ 个数字中的两个，即 $A_{1}=4$,$A_{2}=2$。

此时 $A_{3}$ 仍然等于 $0$,就在 $110$ 的第三位上，异或两个 $1$ ,把其中一个 $1$ 分给 $A_{3}$ ，另一个给 $A_{2}$。

因此 $A_{1}=4$，$A_{2}=3$，$A_{3}=1$。

所以最小的和为 $8$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define For(i,x,y,...) for(int i=(x),##__VA_ARGS__;i<=(y);++i)
#define foR(i,x,y,...) for(int i=(x),##__VA_ARGS__;i>=(y);--i)
#define Rep(i,x,y,...) for(int i=(x),##__VA_ARGS__;i<(y);++i)
#define endl '\n'
#define debug(...)
#define debug1(a,i,...) cout<<i<<" "<<a[i]<<endl;
typedef long long ll;
#define fi first
#define se second
#define PII pair<int,int>
#define me(s,x) memset(s,x,sizeof s)
#define pb emplace_back

template<typename T=int>T read(){T x;cin>>x;return x;}
const int mod=998244353;
struct mint{
	int x;mint(int x=0):x(x<0?x+mod:x<mod?x:x-mod){}
	mint(ll y){y%=mod,x=y<0?y+mod:y;}
	mint& operator += (const mint &y){x=x+y.x<mod?x+y.x:x+y.x-mod;return *this;}
	mint& operator -= (const mint &y){x=x<y.x?x-y.x+mod:x-y.x;return *this;}
	mint& operator *= (const mint &y){x=1ll*x*y.x%mod;return *this;}
	friend mint operator + (mint x,const mint &y){return x+y;}
	friend mint operator - (mint x,const mint &y){return x-y;}
	friend mint operator * (mint x,const mint &y){return x*y;}
};mint Pow(mint x,ll y=mod-2){mint z(1);for(;y;y>>=1,x*=x)if(y&1)z*=x;return z;}
const int N=100;
ll n,x,cnt,res;
int a[N];
void MAIN(){
	cnt=res=0;
	me(a,0);
	cin>>n>>x;
	if(n==1){
		if(x>0) cout<<x<<endl;
		else puts("-1");
		return;
	}
	while(x){
		a[cnt++]=x&1;
		if(x&1) res++;
		x>>=1;
	}
	int ans=0;
	For(i,0,cnt) ans+=a[i]==1?1<<i:0;
	if(res<n){
		int cha=n-res;
		for(int i=0;;++i){
			if(a[i]==1){
				if(cha<n-1){
					ans+=(ceil(1.0*cha/2)*2)*(1<<i);
					cha-=ceil(1.0*cha/2)*2;
				}
				else{
					ans+=((n-1)/2*2)*(1<<i);
					cha-=(n-1)/2*2;
				}
			} 
			else{
				if(cha<n){
					ans+=(ceil(1.0*cha/2)*2)*(1<<i);
					cha-=ceil(1.0*cha/2)*2;
				}
				else{
					ans+=(n/2*2)*(1<<i);
					cha-=n/2*2;
				}
			}
			if(cha<=0) break;
		}
	}
	cout<<ans<<endl;
}signed main(){
	int t=read();while(t--){
		MAIN();
	}
	return 0;
}
```

---

