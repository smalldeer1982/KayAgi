# Sum of Nestings

## 题目描述

我们定义一个括号序列是规则的当且仅当存在某种方式可以将字符`+`和`1`插入其中使得其成为一个合法的表达式。比如`(()())`是规则的因为我们可以将它变成`((1+1)+(1+1))`的形式，而这个形式是一个合法的表达式。此外，`()()()`、`(())`、`()`也是规则的括号序列。相反，`)(`、`(()`、`())(()`不是规则的括号序列。

在这个问题中，你被给予了两个数$n$和$k$，你的任务是构建一个规则的括号序列，使得它恰好含有$n$对括号并且恰好含有$k$对嵌套。

比如，`()(())`含有$3$对括号且它的嵌套对数为$1$，而`(((())))`含有$4$对括号且它的嵌套对数为$6=3+2+1$。

## 样例 #1

### 输入

```
3 1
```

### 输出

```
()(())```

## 样例 #2

### 输入

```
4 6
```

### 输出

```
(((())))```

## 样例 #3

### 输入

```
2 5
```

### 输出

```
Impossible
```

# 题解

## 作者：Xssion37_XY (赞：5)

### 前情提要

[题目链接](https://www.luogu.com.cn/problem/CF847C)

[更好的阅读体验](https://www.luogu.com.cn/blog/778802/solution-cf847c)

### 题目大意

构造括号序列。

举个例子，给定一个序列为 $(((())))$。

有些人会认为嵌套数是 $3$，但是这道题实际上说的是**不完全嵌套**（一对括号只要被另一对括号包含都算，并不一定要连续），所以嵌套数是为 $6=3+2+1$。

### 实际分析

- 判断 $k$ 的范围

我们想一想 $k$ 的最大值是多少。

当构造的括号序列为 $(((...)))$ 时，容易看出来最大嵌套数 $\large k_{max}=\frac{n\times(n-1)}{2}$。

- 有解的情况

$\large k\le\frac{n\times(n-1)}{2}$ 时有解。

那再思考一下有解的情况里是否都全部满足呢？

假设括号序列为 $(((())))$。

把第一个右括号移到第四个左括号的左边（即向外移动 $1$ 层），

序列就变成了 $((()()))$，嵌套数就会减少 $1$，从 $6$ 变为 $5$。

还是假设括号序列为 $(((())))$，向外移动 $2$ 层，

那么序列就会变为 $(()(()))$，嵌套数就会减少 $2$，从 $6$ 变为 $4$。

即括号拿出了 $i$ 层，嵌套数就会减少 $i$，也就是说，嵌套数一定小于最大数，所以在范围内一定有解。

- 部分代码实现

很容易写出来普通递归函数。

```
#include <iostream>
using namespace std;
long long n, k;
void dfs(long long n, long long k) {
	if (n == 0) {
		return; //边界
	}
	cout << "()";
    dfs(n - 1, k);
}
int main() {
	cin >> n >> k;
	if (n * (n - 1) / 2 < k) {
		cout << "Impossible" << endl;
	} else {
		dfs(n, k);
	}
	return 0;
}
```

但是这段代码有个很明显的问题，不能实现将括号嵌套的操作。

运用上面分析的，把括号向内拿 $i$ 层，嵌套数就增加 $i$。

得到当 $n\le k$ 时，当前嵌套数小于 $k$，于是就在当前括号里再嵌套一层，每次就可以增加 $1$ 对括号。

```

if (k >= n - 1) {
	cout << "(";
	dfs(n - 1, k - (n - 1));//嵌套数不够，多嵌套一层
	cout << ")";
}
```
这段代码就是在 $n\le k$ 时打印左括号，递归到另外一边时再打印右括号，中间就继续使用递归来添加括号，实现了括号嵌套的操作。

总结来说就是：```(```dfs(括号数-1，嵌套数-n+1)```)```。

### 代码部分

```
#include <iostream>
using namespace std;
long long n, k;//数据需开long long
void dfs(long long n, long long k) {
	if (n == 0) {
		return;//边界
	}
	if (k >= n - 1) {//继续嵌套
		cout << "(";
		dfs(n - 1, k - (n - 1));
		cout << ")";
	} else {
		cout << "()";//单独加1对括号
		dfs(n - 1, k);
	}
}
int main() {
	cin >> n >> k;
	if (n * (n - 1) / 2 < k) {
		cout << "Impossible" << endl;//无解
	} else {
		dfs(n, k);
	}
	return 0;
}
```
完结撒花！

[AC记录](https://www.luogu.com.cn/record/136794938)

最后再悄悄感谢 N_z_ 的耐心指导。

---

## 作者：xzggzh1 (赞：2)

题意：

构建一个规则的括号序列，使得它恰好含有 $n$ 对括号并且恰好含有 $k$ 对嵌套，或输出 `Impossible` 。（一对嵌套表示两对对应的括号一个被另一个包含）。

$n\leq 10^5$。

---

先确定一个上限，比较显然：这样排列 $((((…))))$ 就可以搞到最多的括号嵌套。这样得到的上限是 $k\leq \frac{n\times(n-1)}{2} $ 才可以有解。

可以证明，没有其他方案可以得到更多的嵌套。

那么思考另一个问题：是否小于上限的 $k$ 都一定有解，且如何构造。


对于 $((((…))))$ 的括号序列，只要将里面某的一对 $()$ 向外边提出 $i$ 对 $()$ 即可使得嵌套的数量减少 $i$。那么这样就可证明可以构造出的答案范围是稠密的。

知道了这些，正着构造用递归算法即可。

---

核心代码 ：

```cpp

ll n,k;
void c(ll n,ll k)
{
    if(n==0)return ;
    if(k>=n-1)
    {
        putchar('(');
        c(n-1,k-(n-1));
        putchar(')');
    }
    else 
    {
        putchar('(');
	putchar(')');
        c(n-1,k);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    if(n*(n-1)/2<k)cout<<"Impossible";
    else c(n,k);
}
```



---

## 作者：Special_Tony (赞：1)

# 思路
显然，如果一个括号里包含了 $x$ 个括号，里面的括号不管怎么排序，以这个括号为外层则一定会产生 $x$ 个嵌套。所以，我们只要对每个括号贪心判断能不能当外层即可。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n;
ll m;
void print (int n, ll m) {
	if (! n)
		return ;
	if (m < n - 1)
		print (n - 1, m), cout << "()";
	else
		cout << '(', print (n - 1, m - n + 1), cout << ')';
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	if (n * (n - 1ll) / 2 < m)
		cout << "Impossible";
	else
		print (n, m);
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：1)

看到还没有用递推写这个题的题解，那我就来发一篇吧。
## 题面

[Sum of Nestings](https://www.luogu.com.cn/problem/CF847C)

## 分析
分三种情况：无解，$n \gt k$，$n \le k$。

- 无解：容易发现即使 $n$ 个括号全部嵌在一起都小于 $k$ 的话就是无解了，嵌套的个数最多为 $\dfrac{n \times (n-1)}{2}$。
- $n \gt k$，此时即使最多使用只有一层嵌套的括号，仍然有多余的括号，那我们就直接把这 $n-k-1$ 打印出来，再打印一层 $k$ 个的嵌套括号。
- $ n \le k $ 此时处理起来就麻烦了捏，发现如果一层嵌套的括号不够 $k$ 的话，那就再嵌入这一层的一个括号中，这样每次可以增加 $1$ 对括号。

### 但是这样写会在第 $41$ 点挂，所以要考虑优化！

容易发现一次一次加可以被优化成一次加剩下的 $k$ 和当前层的括号减 $1$ 的最小值，括号减一是为了保留一个括号，使得剩下的括号全部到这个保留的括号内部。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long hys[700010];
int main()
{
//	freopen("tmp.out","w",stdout);
	long long n,k;
	scanf("%lld%lld",&n,&k);
	if(n*(n-1)/2<k)
	{
		printf("Impossible");
		return 0;;
	}
	if(n>k)
	{
		for(int i=k+1;i<n;i++)
		{
			putchar('(');
			putchar(')');
		}
		putchar('(');
		for(int i=1;i<=k;i++)
		{
			putchar('(');
			putchar(')');
		}
		putchar(')');
	}
	else
	{
		k-=n;
		k++;
		hys[1]=n-1;
		int xgd=1;
		while(k)
		{
			if(k&&hys[xgd]>1)
			{
				int tmp=min(hys[xgd]-1,k);
				hys[xgd]-=tmp;
				k-=tmp;
				hys[xgd+1]+=tmp;
			}
			else break;
			xgd++;
		}
		for(int i=0;i<=xgd;i++)
		{
			while(hys[i]>1)
			{
				putchar('(');
				putchar(')');
				hys[i]--;
			}
			putchar('(');
		}
		for(int i=0;i<=xgd;i++)putchar(')');
		
	}
}
/*
300000
600000


*/
```


---

## 作者：Code_Fish_GoodBye (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF847C)

## 思路

一道简单的**递归**题，题目要求我们构建一个有 $n$ 对括号且有 $k$ 对嵌套的括号序列（一对嵌套表示的是两对对应的括号一个被另一个包含）。如果无法构建满足条件的括号序列，则输出 Impossible。

确定上限：当 $k \leq \frac {n \times n - 1}{2}$  时才有解。

对于  ((((…))))((((…))))  的括号序列，只要将里面某的一对 $\binom{}{}$ 向外边提出 $i$ 对 $\binom{}{}$ 即可使得嵌套的数量减少 $i$。那么这样就可证明可以构造出的答案范围是稠密的。

综上，直接使用递归函数即可 AC。

参考代码（请勿抄袭）:

```cpp
#include<bits/stdc++.h> //万能头
#define ll long long //把ll定为long long，节约打字时间
using namespace std;
ll n,k;

void Nes(ll n,ll k){//构造函数
    if(n==0) return; //当所有的括号都输出完，代表任务完成，退出函数
    if(k>=n-1){
        putchar('(');
        Nes(n-1,k-(n-1));//递归
        putchar(')');
    }
    else{
        putchar('(');
		putchar(')');
        Nes(n-1,k);
    }
    /*putchar函数可以让程序输出一个字符，putchar(')') 等价于 cout<<')' */
}

int main(){
    scanf("%lld %lld",&n,&k);
    if(n*(n-1)/2<k) printf("Impossible\n");//不可能完成的任务
    else Nes(n,k);//开始构造
    return 0;
}
```



---

## 作者：Lyw_and_Segment_Tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF847C)  
## 题意简述
> 输入 $n$ 和 $k$，求出一个由 $n$ 对括号组成的含有 $k$ 对嵌套的规则括号序列，若不行，输出 `Impossible`。

## 开始解题！
首先发现这一题有两种不同的输出，于是进行分类讨论。  
首先，在不考虑 $k$ 的情况下，$n$ 对括号的嵌套对数最多有 $n-1 + n-2 + \dots + 1$ 个，通过等差数列求和公式的转化，得：$\frac{(n-1+1) \times (n-1)}{2}$。  
那么也就是说，如果 $\frac{(n-1+1) \times (n-1)}{2}$ 的值小于 $k$，说明无解，输出 `Impossible`。  
然后考虑另一种输出，显然，我们可以使用深搜来逐层输出，当 $k \ge n - 1$ 时，说明需要进行逐层分解，所以继续进行分解。否则输出一个括号，来消耗掉这一次的嵌套对数。  
最后是深搜的边界条件，当 $n = 0$ 时，说明已经没有括号了，故直接返回。  
综合上述结论，得出代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void dfs(int n,int k){
    if(n==0) return;
    if(k>=n-1){
        cout<<"(";
        dfs(n-1,k-(n-1));
        cout<<")";
    }else{
        cout<<"()";
        dfs(n-1,k);
    }
}
signed main(){
    int n,k;
    cin>>n>>k;
    if(n*(n-1)/2<k) cout<<"Impossible"<<endl;
    else dfs(n,k);
}
```

---

## 作者：Nuclear_Fish_cyq (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF847C)

## 做法


首先我们考虑一下什么时候无解。我们知道，当把所有括号都嵌套在一起的时候（即括号序列形如 `(((...(())...)))` 时）嵌套数可以取到最大值 $\frac{n(n-1)}{2}$。所以我们就可以知道，当 $k>\frac{n(n-1)}{2}$ 时无解。那么对于其他的情况我们可以证明都有解吗？

我们还是考虑一个括号序列。我们如果把其中一对括号向外提取出 $i$ 层的话，那么括号的嵌套数会减少 $i$。

比如说我们把 `(((())))` 的第四对括号提取出两层，就变成了 `((())())`，嵌套数从 $6$（$0+1+2+3$） 变成了 $4$（$0+1+2+1$），减少了 $2$。再比如说我们把第三对括号提取出一层，就变成了 `((()()))`，嵌套数变成了 $5$（$0+1+2+2$），减少了 $1$。这样子，我们就可以知道 $k$ 不超上界的情况一定有解。

接下来我们想一想怎么做。我们考虑使用递归。我们可以将问题分为两种情况：如果括号对数比嵌套数还大的话，我们就直接输出一对括号，然后问题就变成了一个括号对数少一，嵌套数不变的子问题。不然的话，就说明我们要开嵌套括号了，于是先输出 `(`，然后解决括号数少一，嵌套数少 $n-1$ 的子问题，然后再输出 `)`。具体看代码。

上代码，可能码风有点奇特，不要在意。

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a, b;//注意数据范围 
void dfs(ll n, ll k){
	if(n == 0){// 不需要匹配括号了，直接退出 
		return;
	}
	if(k >= n - 1){//嵌套数比括号数多，嵌套一层括号 
		cout << "(";
		dfs(n - 1, k - n + 1);//递归
		cout << ")"; 
		return;
	}
	//否则的话就单独加一对括号
	cout << "()";
	dfs(n - 1, k); 
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b;
	if(b > a * (a - 1) / 2){//就算全嵌套也不行，无解 
		cout << "Impossible" << endl;
		return 0;
	}
	dfs(a, b);
	cout << endl;
	return 0;
}

```


---

## 作者：ys_kylin__ (赞：0)

[原题](https://www.luogu.com.cn/problem/CF847C)


首先，我们可以发现对于每对括号，嵌套量最多加之前全部括号之和，所以当 $k > 1+2+\dots+n-1$ 时，无法构造。一加到 $n-1$ 可以转为 $\frac{n\times(n-1)}{2}$。也就是：`if(k>(n*(n-1))/2) printf("Impossible"),exit(0);` 直接不可能。

接下来可以递归，对于一个括号，里面装着若干括号，将其中 $x$ 个移出，总嵌套量减 $x$。去递归它，能嵌套的嵌套，不然移出。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
void dfs(long long n,long long k) {
	if(n==0) return;
	if(k>=n-1) {
		printf("(");
		dfs(n-1,k-(n-1));//嵌套 
		printf(")");
	}
	else {
		printf("()");
		dfs(n-1,k);//移出 
	}
}
int main(){
	long long n,k;
	scanf("%lld%lld",&n,&k);
	if(k>(n*(n-1))/2) printf("Impossible"),exit(0);//直接结束了 
	dfs(n,k);
	return 0;
}
```

---

## 作者：fangyicheng1216 (赞：0)

~~蒟蒻第四次发题解~~

[题目传送门](https://www.luogu.com.cn/problem/CF847C)

## 思路：

这个题要确定一个上限，是 $k \leq \frac {n \times n - 1}{2}$。当 $k$ 超过了这个值时，本题无解。

然后我们发现对于一个 $((((...))))$ 的排列，当一对括号向外挪 $i$ 对括号时，嵌套减少 $i$。这样我们就可以直接写出代码了。

## 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
void dfs(int x,int y){//习惯性函数名 
	if(x==0) return ;//如果没有括号用了，返回 
	else if(y>=x-1){//如果嵌套比括号数多 
		putchar('(');
		dfs(x-1,k-(x-1));//括号数少一个，嵌套少括号数-1个，继续递归 
		putchar(')'); 
	}
	else{
		putchar('(');
		putchar(')');
		dfs(x-1,y);//括号少一个 
	}
}
signed main(){
	cin>>n>>k;
	if(n*(n-1)/2<k) cout<<"Impossible";//如果达不到k个嵌套，输出Impossible 
	else dfs(n,k);//否则直接递归 
	return 0;
}
```


---

## 作者：Not_lazy (赞：0)

[题目](https://www.luogu.com.cn/problem/CF847C)
## The question：
------------
构建一个规则的括号序列，使得它恰好含有 $n$ 对括号并且恰好含有 $k$ 对嵌套，（一对嵌套表示两对对应的括号一个被另一个包含）或输出 `Impossible`。

$n\leq 10^5$。
## Train of thought：


------------

上限：$k\leq \dfrac{n\times n-1}{2}$ 才可以有解。

对于 `((((…))))` 的括号序列，只要将里面某的一对 `()`向外边提出 $i$ 对 `()` 即可使得嵌套的数量减少 $i$。那么这样就可证明可以构造出的答案范围是稠密的。

科普：`putchar`：C 语言函数之一，作用是向终端输出一个字符。其格式为 `putchar(c)`。
## Code:


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
void dg(long long n,long long k){
    if(n==0)return ;
    if(k>=n-1){
        putchar('(');
        dg(n-1,k-(n-1));
        putchar(')');
    }
    else{
        putchar('(');
		putchar(')');
        dg(n-1,k);
    }
}
int main(){
    scanf("%d %d",&n,&k);
    if(n*(n-1)/2<k)printf("Impossible\n");
    else dg(n,k);
}
```


---

