# Crash

## 题目描述

在“俄罗斯代码杯”编程比赛的期间，代码测试系统储存了每一位参赛者发送的所有程序，有很多参赛者会在他们自己的代码程序中使用随机数，并发送几个具有相同的的程序。

每个参赛者由一个唯一的正整数 $k$ 来标识，每个发送的程序 $A$ 都由两个数字表示：$x$，在与 $A$ 相同的第一个程序之前发送的不同的程序的数量；$k$，参赛者的编号，即程序的作者。因此，所有相同的程序具有相同的 $x$。      

众所周知，测试系统中的数据是按照时间顺序来存储的，就是说，如果测试系统有一个数字为 $x$（$x \ge 0$）的程序，而参赛者的编号为 $k$，那么测试系统有一个编号为 $x - 1$ 的程序存储在以前的某个地方。      
比赛期间，测试系统崩溃了，但随后所有的参赛者提交的数据都已经恢复了。现在的陪审团想核实恢复的数据是否按照时间顺序储存， 请你帮助陪审团这样做。

## 样例 #1

### 输入

```
2
0 1
1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
0 1
1 2
1 1
0 2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
0 1
1 1
0 1
0 2
```

### 输出

```
YES
```

# 题解

## 作者：ZSYZSYZSYZSY (赞：2)

# CF417B Crash

## Description
有 $n$ 个程序，每个程序有 $x$ 和 $k$，在与 $a$ 相同的第一个程序之前发送的不同的程序的数量，参赛者的编号 $k$，即程序的作者。

## Solution
因为数据范围极小，而整个的每次输入对答案均有影响，所以使用模拟。

首先，我们要用一个数组 $a$ 来记录记录编号等于它下标的人发送了几个程序，然后分情况讨论即可。

如果 $x = a_k$，那么说明这个作者有个新的程序了，需要记录下来。

如果 $x > a_k$，则证明现在输入的代码比记录的代码数量要多，所以直接不合法，此时可以直接输出NO结束程序。

如果 $x < a_k$，就说明输入的方案数比记录的少，也就是说这次的方案与之前相同的方案中的其中一个相等，所以就不用做任何处理。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[1000005];

int main(){
	ll n;
	cin>>n;
	for(int i=1;i<=n;i++){
		ll x,k;
		cin>>x>>k;
		if(x==a[k]){
			a[k]++;
		}
		else if(x>a[k]){
			cout<<"NO"<<endl;
			return 0;
		}
	} 
	cout<<"YES"<<endl;
	return 0;
}
```


---

## 作者：Blikewsr (赞：2)

 - [$\color{orange}\text{[CF417B 原题链接]}$](https://www.luogu.com.cn/problem/CF417B)
 
 - 题目描述
   [$\color{lightblue}\text{[见云切板]}$](https://www.luogu.com.cn/paste/w9mk3pzc)

 - 输入格式
   [$\color{lightblue}\text{[见云切板]}$](https://www.luogu.com.cn/paste/w9mk3pzc)
   
 - 输出格式
   [$\color{lightblue}\text{[见云切板]}$](https://www.luogu.com.cn/paste/w9mk3pzc)

 - 思路              
 
   根据题意， 可知： 
   
   测试系统中的数据是按时间顺序存储的， 也就是说， 如果测试系统有一个数字为 $x$（$x \ge 0$）的解， 而参与者的编号为 $k$， 那么测试系统有一个编号为 $x - 1$ 的解存储在以前的某个地方。 
   
   所以， 在输入时， 我们把每一个 $k$ 记录下来， 如果输入的 $k$ 的个数 $x$ 大于之前记录的 $k$ 的个数， 那么就说明输入的顺序是错误的， 就输出 `NO`； 反之， 输出 `YES`。
   
   那么， 怎么记录呢？  
   
   我们可以用一个一维数组 $code$ 来把每一个 $k$ 记录下来。
   
   初始时， 每个 $code$ 都赋值为 $0$。
   
   之后， 在输入时， 每输入一个 $k$， 就判断一下， 并根据判断的结果， 选择把 $code_k + 1$ 或不变。
   
   那么， 问题又来了： 要怎么判断呢？
   
   因为 “如果测试系统有一个数字为 $x$（$x \ge 0$）的解， 而参与者的编号为 $k$， 那么测试系统有一个编号为 $x - 1$ 的解存储在以前的某个地方。” 
   
   所以：
   - 如果输入的 $x$ 比记录的 $code_k$ 的值大， 就说明输入的方案数比记录的多， 不正确， 直接输出 `NO` 并结束程序。
   - 如果输入的 $x$ 与记录的 $code_k$ 的值相等， 就说明输入的是一个新的方案， 那么就把 $code_k + 1$。
   - 如果输入的 $x$ 比记录的 $code_k$ 的值小， 就说明输入的方案数比记录的少， 也就是说这次的方案与之前相同的方案中的其中一个相等， 所以就不用做任何处理。
   
   最后， 因为我们在输入的时候就已经判断了， 如果不是按照顺序输入的， 就会输出 `NO` 并结束程序。 所以， 我们可以直接在程序的最后输出 `YES` 就行了。  
   
 - 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define N 100001
using namespace std;
int n, code[N];   
/*
	n : 数据总个数 
	code[] :  记录 k 的个数 
*/
inline int read () {   // 快读 
	int f = 0, n = 1;
	char ch = getchar ();
	while (!isdigit (ch)) {
		n *= -1;	
		ch = getchar ();
	}
	while (isdigit (ch)) {
		f = (f << 3) + (f << 1) + ch - '0';
		ch = getchar ();
	}
	return f * n;	
}
inline void write (int x) {   // 快写 
	if (x < 0) putchar ('-'), x = -x;
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return;
}
signed main () {   // 主程序 
	n = read ();  // 输入总个数 
	for (int i = 0; i < n; ++ i) {   // 边输入边判断 
		int x = read (), k = read ();  // 输入数据 
		if (x == code[k]) code[k] ++;  // 输入新的方案 
		if (x > code[k]) {             // 不正确的输入顺序 
			cout << "NO" << '\n';        
			return 0;	           // 输出 NO 并结束程序 
		}
	}
	cout << "YES" << '\n';   // 最后直接输出 YES 
	return 0;	
}
```

 - 此题解仅供参考， 欢迎指正， 谢谢！
 

---

## 作者：naroto2022 (赞：1)

# CF417B题解
博客里使用更佳。
### 思路
简单的模拟，稍微的分析加上分类讨论就 AC 啦~
### 做法
首先，我们要用一个数组 $a$ 来记录记录编号等于它下标的人发送了几个方案，然后就开始开心的模拟:每行输入一个 $x$（在与 $A$ 相同的第一个程序之前发送的不同程序的数量），$k$（参赛者的编号，即程序的作者）。

然后就分为以下几种情况：

1. $x<a[k]$，就说明输入的方案数比记录的少，也就是说这次的方案与之前相同的方案中的其中一个相等，所以就不用做任何处理。
2. $x=a[k]$，说明这是一种新的情况，相应的 $a[k]+1$。
3. $x>a[k]$，也就是说输入的方案比记录的还多，不正确，此时可以直接输出 NO 结束程序。

分析就到此为止啦~
### 总结

1. 简单的纯模拟
2. 分析加分类讨论

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[1000005],n;
//a数组来记录编号等于它下标的人发送了几个方案。
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x,k;
		scanf("%d %d",&x,&k);
		if(x==a[k]) a[k]++;//有一个情况和记录的a[k]相等，说明这是一种新的情况，a[k]++
		else if(x>a[k]){//如果x大于a[k]，也就是说输入的方案比记录的还多，不正确。
		    printf("NO");
		    return 0;//直接结束程序。
		}	
		//else if(x<a[k])          这种情况不做处理。
	} 
	printf("YES");//要是要输出NO，前面已经结束程序，能撑过前面的循环就表明数据是按照顺序输入的。
	return 0; 
} 
//完结撒花✿✿ヽ(°▽°)ノ✿。
```


---

## 作者：sto__Liyhzh__orz (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF417B)

简单模拟。

首先输入 $x$ 和 $k$，

* 若 $x = a_k$，满足情况，将 $a_k$ 加一。

* 若 $x > a_k$，不满足，直接输出 `NO`，并结束程序。

* 若 $x < a_k$，不用管它。

* 若最后没有并结束，输出 `YES`。

完了，上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

const int MAXN=100000+5;
int a[MAXN],n,x,k;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x>>k;
        if(x==a[k]) a[k]++;
        else if(x>a[k]) return cout<<"NO"<<endl,0;
    }
    cout<<"YES"<<endl;
    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
因为数据范围极小，而整个的每次输入对答案均有影响，所以显然模拟。
## 分析。
我们开一个桶，来记录编号等于它下标的人发送了几个程序。然后分情况讨论即可：

首先如果是 $x$ 与 $a_k$ 相等则证明出现了一个新的代码，将它扔进桶中。

其次如果是 $x$ 大于 $a_k$ 则证明现在输入的代码比记录的代码数量要多，所以直接不合法。

其它的 $x$ 小于 $a_k$ 的情况对整个的答案没有影响，因为现在输入的代码量比之前的一次相同，所以可以存在。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,x,k;
int pd=1,a[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>k;
		if(x==a[k]){
			a[k]++;
		}
		else if(x>a[k]){
			pd=0;
		}
	} 
	(pd)?cout<<"YES\n":cout<<"NO\n";
	return 0; 
}  
```
## 后记。
大家如有疑问。可以在评论区提出，我会尽力解答的。

---

## 作者：wuzijie (赞：0)

## 题面解释：
有 $n$ 个程序，每个程序有 $x$ 和 $k$，在与 $A$ 相同的第一个程序之前发送的不同的程序的数量，而 $k$ 作为这个程序的作者。

## 思路分析：
测试系统中的数据是按照时间顺序来存储的，就是说，如果测试系统有一个数字为 $x$（$x \ge 0$）的程序，而参赛者的编号为 $k$，那么测试系统有一个编号为 $x - 1$ 的程序存储在以前的某个地方。

也就是说，如果 $x \le $ 之前所出现的 $k$ 的数量，那么就满足时间顺序；
反之，直接输出 `NO`。

同时，如果之前记录的数量和此时输入的相等了，那么说明这个作者有个新的程序了，需要记录下来。

记录的过程就是一个简单的桶计数。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,t[N],x[N],k[N];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&x[i],&k[i]);
	for(int i=1;i<=n;i++){
		if(x[i]<t[k[i]])continue;
		else if(x[i]==t[k[i]])t[k[i]]++;
		else {
			printf("No");
			return 0;
		}
	}	
	printf("Yes");
	return 0;
} 
```

谢谢！

---

## 作者：流绪 (赞：0)

模拟！

我们用一个数组，来记录编号等于它下标的人发送了几个方案，然后我们开始模拟，输入 x,k（意义同题目中）

如果 x==a[k]，也就是输入了一个新方案，a[k]++。

如果 x>a[k]，也就是现在输入的方案比记录的多，这是不合法的用 flag 记录下来。

如果 x<a[k]，也就是现在输入的方案和之前的某次相同，可以不做处理。

最后根据 flag 来输出就好啦。

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int a[maxn]={0};
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int flag = 1;
	for(int i=1;i<=n;i++)
	{
		int x,k;
		cin >> x >> k;
		if(x == a[k])
			a[k] ++;
		else if(x > a[k])
			flag = 0;	
	} 
	if(flag)
		cout << "YES";
	else
		cout << "NO";
	return 0; 
}  
```


---

## 作者：Acerkaio (赞：0)

### NO.1 思路
题目第三段明显提示了我们：

如果测试系统有一个数字为 $x$（$x \ge 0$）的解，而参与者的编号为 $k$，那么测试系统有一个编号为 $x - 1$ 的解存储在以前的某个地方。

所以这题就是一个模拟。

### NO.2 实现

用一个数组 $A$ 储存作者编号，依据有一个编号为 $x - 1$ 的解存储在以前的某个地方。，可得以下操作：

如果 $x = A_k$，说明输入的是一个新方案，令 $A_k +1$。  
如果 $x \ge A_k + 1$ 说明输入的是储存在后来的某个地方，即系统不是按时间储存的。  
 ### NO.3 代码
 
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, A[1000001], x, k;
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
	    cin >> x >> k;
		if(A[k] == x) {A[k]++;} else {
			if(x > A[k]) {cout << "NO";return 0;}
		}
	}
	cout << "YES";
	return 0;
}

```


---

