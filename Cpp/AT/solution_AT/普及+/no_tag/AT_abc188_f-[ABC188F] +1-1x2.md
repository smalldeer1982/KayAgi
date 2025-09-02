# [ABC188F] +1-1x2

## 题目描述

高桥君在黑板上写下了一个正整数 X，现在高桥君想要让这个正整数变成 Y，每一次都可以按以下三种中的任意一种方式来改变这个数:

1. 将目前黑板上的数加1。

2. 将目前黑板上的数减1。

3. 将目前黑板上的数乘以2。

现在高桥君想要知道从 X 变成 Y 的最小次数。

## 说明/提示

- 1≤X≤${10^{18}}$
- 1≤Y≤${10^{18}}$

## 样例 #1

### 输入

```
3 9```

### 输出

```
3```

## 样例 #2

### 输入

```
7 11```

### 输出

```
3```

## 样例 #3

### 输入

```
1000000000000000000 1000000000000000000```

### 输出

```
0```

# 题解

## 作者：The_End_of_GCC (赞：10)

[传送门](https://www.luogu.com.cn/problem/AT_abc188_f)

## 题目大意：

现有两个数 $x$、$y$，每一步可以将 $x+1$，$-1$ 或 $\times2$
，求将 $x$ 变为 $y$ 共要几步。

## 思路简述：

先定义一个 $key$ 为 long long，value 为 string 的 [map](https://blog.csdn.net/nyist_zxp/article/details/119840727) 容器 $f$，再写一个 dfs 的函数，往这个函数中传入两个值 $a\rightarrow x$ 和 $b\rightarrow x$：

1. 若 $a$ 等于 $b$，达成目标退出递归

2. 若 $a$ 大于 $b$，则 $a$ 一定是一步步减 1 变为 $b$ 的，故返回 $a-b$；

3. 若 $b=a$ 的情况已经算过，那就返回已经算过的答案；
        
4. 既然已经不是上述特殊情况，那我们就先把 $f_b$ 的值设为 $b$ 与目标 $a$ 的差以便后面的计算和判断第 $3$ 点的情况。
        
5. 干完这些，就只要判断 $b\bmod2$ 等于 0 或 1 两种情况了：

	1. 若 $b\bmod2$ 等于 0，将 $f_b$ 设为 $A$、$B$ 的较小值。
（$A$：搜索 $a$，$b/2$ 的情况，并将搜索出的结果（步数）$+1$；$B$：$f_b$。）

	2. 若 $b\bmod2$ 等于 1，将 $f_b$ 设为 $C$、$D$、$E$ 的最小值。（$C$：搜索 $a$，$(b+1)/2$ 的情况，并将搜索出的结果（步数）$+2$；$D$：搜索 $a$，$(b-1) /2$ 的情况，并将搜索出的结果（步数）$+2$；$E$：$f_b$。）
   
6. 返回 $f_b$。


**总结：简单说成这样：**

- 若 $b$ 为偶数：

	$f_b\rightarrow\min(\text{dfs}(a,b/2)+1,f_b);$
    
- 若 $b$ 为奇数：

	$f_b\rightarrow\min(\text{dfs}(a,(b+1)/2)+2,\text{dfs}(a,(b-1)/2)+2,f_b); $



------------

        
## 代码：

```
#include <bits/stdc++.h>
using namespace std;
map<long long,long long>f;
long long dfs(long long a,long long b)
{
	if(a==b)    //第一种情况。
		return 0;
	if(a>b)    //第二种情况。
		return a-b;
	if(f.count(b)!=0)    //第三种情况。
		return f[b];
	f[b]=b-a;    //第四步。
	if(b%2==0)    //情况 5.1。
		f[b]=min(dfs(a,b/2)+1,f[b]);    //递归判断较小值。
	else    //情况 5.2。
		f[b]=min(min(dfs(a,(b+1)/2)+2,dfs(a,(b-1)/2)+2),f[b]);   //递归判断最小值。
	return f[b];    //返回 f[b]。
}
int main()
{
    long long x,y;    //数据很大，要开 long long。
    cin>>x>>y;    //输入。
    cout<<dfs(x,y)<<endl;    //将 x，y 传入函数并输出。
    return 0;
}
```

[$AC$ 记录。](https://www.luogu.com.cn/record/97148186)

希望大家采纳。

---

## 作者：Mzaaa (赞：5)

## 题意简述

给 $x,y$ 两个数，可以使 $x$ 加一，减一和乘二，求让 $x$ 变为 $y$ 的最小次数。

## 题目分析

由于 $1\le x,y\le10^{18}$，直接暴力肯定不行，所以可以倒叙使用记忆化搜索，由 $y$ 搜到 $x$，有如下操作：

1. 当 $y<x$ 时，只有减一操作可以使用，步数为 $x-y$。
2. 当 $x=y$ 时，步数为 $0$。
3. 当 $y>x$ 时，要考虑 $y$ 是否能被 $2$ 整除：
- 当 $y$ 能被 $2$ 整除时，$y$ 可以除 $2$ 和直接减到 $x$。步数为 $\min(\operatorname{dfs}(y/2)+1,y-x)$。
- 当 $y$ 不能被 $2$ 整除时，$y$ 可以减 $1$ 和加 $1$。步数为 $\min(\operatorname{dfs}(y+1),\operatorname{dfs}(y-1))+1$。
    
 用数组记忆化会炸，可以使用比 `map` 效率更高的 `unordered_map`。
    
## Code:


```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,r;	//记得开 long long 
unordered_map<long long,long long>mp;	//记忆化用的 map 
long long dfs(long long y)
{
	if(x==y)	//相等返回 0
		return 0;
	if(y==x+1||y==x-1||y==2*x)	//一步能搜到 
		return 1;
	if(mp[y]) return mp[y];		//如果搜过，直接返回 
	if(y<x) return mp[y]=x-y;
	else
		if(y%2!=0)
			return mp[y]=min(dfs(y+1),dfs(y-1))+1;
		else
			return mp[y]=min(dfs(y/2)+1,y-x);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>x>>r;
	cout<<dfs(r);
	return 0;
}
```


---

## 作者：linxuanrui (赞：3)

### 题目大意

给出 $x$ 和 $y$，每次进行以下操作：

- 将  $x + 1$。

- 将  $x - 1$。

- 将  $x \times 2$。

求 $x$ 至少要经过几次操作才能变成 $y$。

### 题解

这一题就是一道简单的深搜题目。

这里讲一讲为什么要倒着搜。

首先，如果你用正着搜的话，你就会发现一个问题：

- 有些数据可能 $y$ 比 $x$ 小或者有其他情况，所以要把 $x - 1$ 也递归一下。

- 然而，如果你 $x + 1$，$x - 1$，$x \times 2$，都递归的话，肯定会进入死循环的（记忆化也没用）。

因此，考虑倒着搜。这就是本题的难点啦。

接着，这题肯定要用记忆化搜索，不然会出现一个状态被枚举过多遍而导致超时的后果。

常见的记忆化搜索有数组、`map` 还有 `unordered_map`（不了解 `unordered_map` 的人可以看一下这个[介绍](https://blog.csdn.net/zou_albert/article/details/106983268)）。

用数组显然会超出内存，因为 $n,m \le 10^{18}$。

因此，这里可以用 `map` 或者 `unordered_map`，看个人习惯吧。

### 代码

```cpp
#pragma GCC optmize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
unordered_map<int,int> m;
int x,y;
int dfs(int i){
	if(i == x)return 0;
	if(i < x)return x - i;
	if(m.count(i))return m[i];
	return m[i] = (i & 1 ? min(min(dfs(i + 1),dfs(i - 1)) + 1,i - x) : min(dfs(i >> 1) + 1,i - x));
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> x >> y;
	cout << dfs(y);//qwq
}
```

---

## 作者：vanueber (赞：3)

[原题传送门](https://atcoder.jp/contests/abc188/tasks/abc188_f)

[小芝士1-bfs](https://oi-wiki.org//search/bfs/)

[小芝士2-map](https://oi-wiki.org/lang/csl/associative-container/#map)

# 题目大意

给定正整数 $X$ 和 $Y$，我们有三种操作：

- 将 $X$ 加 $1$。
- 将 $X$ 减 $1$。
- 将 $X$ 乘以 $2$。

求将 $X$ 变为 $Y$ 的最少操作次数。

# 题目分析

看到其他题解中都用的是 dfs 结合记忆化搜索，这里给出一种 bfs 的思路。

## 暴力
首先我们考虑正着搜，对于 $X$ 的三种操作情况各自扩展一个节点，将其插入队列，如果得到了满足条件的 $X$ 则输出操作次数，因为此题中的 $X$ 和 $Y$ 都极大，所以显然无法通过此题。

## 正解

既然正着不行，那我们考虑**倒着搜**，从 $Y$ 开始搜索，原操作可转化成为下操作：

- 将 $Y$ 加 $1$。
- 将 $Y$ 减 $1$。
- 将 $Y$ 除以 $2$。

可以使用 map 判重并记录变为 $i$ 的最小次数，并在过程中将答案存储到变量 $ans$ 中，最后直接输出即可。详细实现见代码。

# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <map>
#include <cmath>
#define INF 1e18

using namespace std;

long long x, y;

struct node
{
	long long num; //当前的Y
	long long cnt; //操作次数
};

long long bfs(long long s, long long f)
{
	queue<node> Q;
	map<long long, long long> p;
	p[f] = 1;
	Q.push(node{f, 0});
	long long ans = INF;
	while (!Q.empty())
	{
		node x = Q.front();
		Q.pop();
		if (p.find(x.num) != p.end() && p[x.num] < x.cnt)
			continue;
		p[x.num] = x.cnt;
		ans = min(ans, x.cnt + abs(s - x.num)); //计算当前最少操作数
		node tmp;
		if (x.num % 2 == 0)
		{
			Q.push(node{x.num / 2, x.cnt + 1});
		}
		else
		{
			Q.push(node{(x.num + 1) / 2, x.cnt + 2});
			Q.push(node{(x.num - 1) / 2, x.cnt + 2});
		} //扩展，加入队列中
	}
	return ans;
}

int main()
{
	scanf("%lld%lld", &x, &y);
	if (x == y)
	{
		printf("0");
		return 0;
	}
	if (x > y)
	{
		printf("%lld", x - y);
		return 0;
	} //特殊情况，直接输出
	printf("%lld", bfs(x, y));
	return 0;
}

```
[AC记录](https://atcoder.jp/contests/abc188/submissions/44399651)

---

## 作者：BlackPanda (赞：2)

*[Problem](https://www.luogu.com.cn/problem/AT_abc188_f)*

------------
## Description

给出正整数 $\verb!X!$ 和 $\verb!Y!$，有三种操作：

- 将 $\verb!X!$ 加上 $1$。

- 将 $\verb!X!$ 减去 $1$。

- 将 $\verb!X!$ 乘以 $2$。

求出将 $\verb!X!$ 变成 $\verb!Y!$ 的最小操作次数。

-----------
## Solution

首先考虑暴力，$\verb!DFS!$ 不考虑顺序搜索求解，指数级时间复杂度，数据范围在 $10^{18}$，肯定超时。

可以考虑引入记忆化搜索优化 $\verb!DFS!$，逆向搜索从 $y$ 到 $x$，记 $f_i$ 表示从 $y$ 到 $x$ 的最小操作数，递归函数为 $dfs(y)$。可以进行三种操作，分别是：除以 $2$、加 $1$ 和减 $1$。

这里分多种情况来讨论：

- 当 $y \lt x$ 时，只能通过 $+1$ 操作来使 $y$ 变成 $x$，所以要进行 $x-y$ 次操作。

- 当 $y = x$ 时，需要进行 $0$ 次操作，返回 $0$ 即可。

- 当 $y > x$ 时，分奇偶数来讨论：
	
    - 当 $y$ 为奇数时，可以通过 $+1$ 操作或 $-1$ 操作来将 $y$ 变成偶数，取 $dfs(y-1)$ 和 $dfs(y+1)$ 的最小值即可，因为贡献了一次操作，答案数要加 $1$。
    
    - 当 $y$ 为偶数时，这里可以通过 $\div 2$ 和 $+1$ 操作到达目标值，取  $dfs(y/2)+1$ 和 $x-y$ 的最小值即可。
    
这里 $x$ 和 $y$ 最大到 $10^{18}$，所以记忆化数组要用 map 来映射。

**[$\verb!map!$](https://oi-wiki.org/lang/csl/associative-container/#map)**

[记忆化搜索](https://oi-wiki.org/dp/memo/)

------------
## Code

**十年 OI 一场空，不开 long long 见祖宗。**

```cpp
#include <bits/stdc++.h>
using namespace std;
long long x, y;
map<long long, long long> f;
long long dfs(long long y)
{
	if (y == x)	return 0;
	if (y < x) return x - y;	
	if (f.find(y) != f.end())	return f[y];
	if (y % 2 != 0) return f[y] = min(dfs(y + 1), dfs(y - 1)) + 1;
	else return f[y] = min(dfs(y / 2) + 1, y - x);
}
int main()
{
	cin >> x >> y;
	cout << dfs(y);
	return 0;
}
```

---

## 作者：qiuqiuqzm (赞：1)

# [ABC188F] +1-1x2 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc188_f)

## 题目大意
给定 $2$ 个数，$x$ 和 $y$。要让 $x$ 在最小的操作数内变成 $y$。每次可以对目前的数进行以下 $3$ 种操作。

* 将目前的数加上 $1$。
* 将目前的数减去 $1$。
* 将目前的数乘上 $2$。

## 分析
* 这道题，我们第一个考虑的就是爆搜。但看到数据范围：

$1\ \le\ X\ \le\ 10^{18}$，$1\ \le\ Y\ \le\ 10^{18}$。

直接爆搜必然超时，那就要考虑优化。这时，就要请出我们的~~大杀器~~，记忆化搜索。因为数据范围很大，我们不得不讲记忆化搜索的数组(我用的是 $vis$)，用 map 来进行存储。对了，一定要记得开 **long long**。
 
* 解决了时间问题，那具体要怎么做呢？
 * 如果 $x > y$ 的话，因为只有第二个操作能减小数字，所以只能用操作二。
 * 如果 $x < y$ 的话，就要判断直接加和用乘法那个快，取最小值。而乘法又要分 $2$ 种情况。
  * 如果 $y$ 为偶数，那这种情况直接让 $x \times 2$，也就是等于 $y \div 2$。
  * 如果 $y$ 是奇数的话，就又要分 $2$ 种情况，一是 $(y+1) \div 2$，二是 $(y-1) \div 2$。
 * 如果 $x = y$ 的话，就不需要动，返回 $0$ 就好了。

## 结尾
* 至此，所有的问题都解决了，我们就可以~~很简单~~的将代码写出来啦。

## Code:
 ```cpp
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
ull x,y;
unordered_map<ull,ull> vis; //记忆化数组
ull dfs(ull a,ull b)
{
	if(a==b) //已经相等情况
		return 0;
	if(a>b) // x>y 情况
		return a-b;
	if(vis[b]!=0) //记忆化
		return vis[b];
	vis[b]=b-a;
	if(b%2==0)
		vis[b]=min(vis[b],dfs(a,b/2)+1); //x<y 且 y 为偶数
	else
		vis[b]=min(vis[b],min(dfs(a,(b+1)/2)+2,dfs(a,(b-1)/2)+2));//x<y 且 y 为奇数
	return vis[b]; //记忆化
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>x>>y;
	cout<<dfs(x,y);
	return 0;
}
```

---

## 作者：_H17_ (赞：1)

## 思路分析

这道题我们可以使用记忆化深度优先搜索，设 $f(y)$ 是 $x\to y$ 的最少次数，于是得到一下结果：

$f(y)=\begin{cases}x-y & y\le x\\\min\{y-x,k\} & other\end{cases}$

当 $y\le x$ 时表示只能减，可以直接得到结果。

否则我们讨论了加和乘，取较小值。

我们看见了 $k$ 这个数，$k$ 是通过乘得到的步数。计算方法如下：

$k=\begin{cases}k=\min\{f((y+1)\div 2),f((y-1)\div2)\}+2 & 2 \nmid y\\k=f(y/2)+1; & other \end{cases}$

如果 $y$ 不能整除 $2$ 那么必须先加一或减一，取较小，否则可以直接除。

## 知识讲解

大概讲一下记忆化，先给出模板

```cpp
int rem[MAXN];
int a(int b){
    if(终止条件)
        return 返回值;
    if(rem[b])
        return rem[b];//如果以前执行过a(b)则直接返回
    int k=a(b-1)+各种算式;//a(b-1)只是一个递归的形式
    return rem[b]=k;//最后进行记忆化
}
```

但是我们发现 $x,y\le10^{18}$ 数组和 `vector` 都无法开那么大，我们需要使用 `map` 来解决。

`map` 的用法：

- 头文件：`<map>`
- 定义：`map<type1,type2>mapname` 举例： `map<int,bool>mp;`
- 赋值：`mp[a]=b;`
- 看看有没有被赋值过（赋值乘 $0$ 也算）`mp.count(a);`
- 清空：`mp.clear();
`
## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,y;
map<int,int>m;
//定义map用来记忆化
int f(int y){
    if(y<=x)
        return x-y;
    //判断
    if(m.count(y))
        return m[y];
    //记忆化
    int k;
    if(y%2)//求k
        k=min(f((y+1)/2),f((y-1)/2))+2;//先加再除，先减再除取较小的
    else
        k=f(y/2)+1;//能整除
    return m[y]=min(y-x,k);//取步数较少的
}

signed main(){
    scanf("%lld%lld",&x,&y);
    printf("%lld\n",f(y));
    return 0;
}
```

---

## 作者：Tang_poetry_syndrome (赞：0)

## [ABC188F] 
简单搜索。
### 思路
考虑深搜剪枝，用 `map` 记忆化。  
分类讨论：  
1. 直接加/减到达 $y$，代价为 $\left|x-y\right|$  
2. 将 $x$ 乘 $2$，代价为 $1$。
3. 将 $x$ 加减 $1$，代价为 $1$，这是为了保证大多数奇数可以被遍历。  

但很明显，这样的**复杂度是不够优的**，操作三会占用大量不必要时间，考虑优化。  
考虑倒搜，将操作三融入操作二，操作二逆反，最后特判操作二被除数的奇偶性进行运算。  
那么从 $z$ 倒搜的代价 $dfs(z)$ 即为  
$dfs(z)=\min\begin{cases}\left|x-z\right|\\\min\begin{cases}dfs(z\div2)+2\\dfs(z\div2+1)+2\end{cases}(z\equiv1\pmod{2})\\dfs(x\div2)+1(z\equiv0\pmod{2})\end{cases}$
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a,b;
map<ll,ll>mp;
ll ans(ll y){
    if(mp.count(y))return mp[y];
    if(y==1)return a-y;
    ll res=abs(a-y);
    if(y&1)res=min({res,ans(y/2)+2,ans(y/2+1)+2});
    else res=min(res,ans(y/2)+1);
    mp[y]=res;
    return res;
}
int main(){
    cin>>a>>b;
    cout<<ans(b)<<endl;
}
```
[提交记录](https://atcoder.jp/contests/abc188/submissions/48688213)

---

## 作者：ruanwentao666 (赞：0)

# [ABC188F] +1-1x2 题解
[题目](https://www.luogu.com.cn/problem/AT_abc188_f)

## 题意分析
给定两个数 $x$，$y$，问如何用最少的次数将 $x$ 变为
 $y$。

变换方式如下：

1. 将目前黑板上的数加 $1$。

2. 将目前黑板上的数减 $1$。

3. 将目前黑板上的数乘以 $2$。

## 解法分析
首先我们很容易想到用队列记录三个状态，但很明显会超时，所以我们需要思考其他方法。

正着来不行，我们就反着来。我们可以反推，让 $y$ 变换到 $x$。

1. 当 $x > y$ 时，只能让 $y$ 一直加 $1$。

2. 当 $x = y$ 时，返回 $0$。

3. 当 $x < y$ 时，需要分类讨论。
- 当 $y$ 为奇数时，可以通过加 $1$ 或减 $1$ 的方式使得 $y$ 变为偶数，再执行下面的操作。

- 当 $y$ 为奇数时，递归调用，在执行 $y \div 2$ 得到的答案和执行 $y - 1$ 得到的答案中取最小值即可

## 代码展示
注：在 dfs 的过程中，我们需要用 map 进行记忆化搜索。

附上 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
map<long long,long long>mp;
long long dfs(long long y){
	if(a==y)return 0;
	if(mp[y])return mp[y];
	if(a>y)return mp[y]=a-y;
	if(y%2!=0)return mp[y]=min(dfs(y-1),dfs(y+1))+1;
	else return mp[y]=min(dfs(y/2)+1,y-a);
}
int main(){
	cin>>a>>b;
	cout<<dfs(b);
	return 0;
}
```


---

## 作者：Erica_N_Contina (赞：0)

# [ABC188F] +1-1x2



## 思路

一开始我们应该会想到 dfs 搜索，但是我们发现这样即使加上记忆化我们也会 TLE。

```C++
int dfs(int x){
	if(y<=x){
		return x-y;
	}
	if(mp[x])return mp[x];
	return mp[x]=min(dfs(x*2),dfs(x+1))+1;
}
```


所以我们考虑倒序的记忆化搜索。我们从 $y$ 作为初始状态开始，让 $y$ 转移到 $x$。这样的话我们就有 $y+1,y-1,y\times 2$ 这 $3$ 种操作。

在转移过程中，我们分 $3$ 种情况

- $y'≤x$

这种情况直接返回 $x-y'$ 即可，因为我们只能使用 $+1$ 的操作。当然如果 $x=y'$，那么 $x-y'$ 自然为 $0$。

- $y'>x$ 且 $y'$ 是偶数。

这种情况，我们考虑从 $y'$ 转移到 $y'\div2$，或者我们直接全部使用 $-1$ 操作让 $y'$ 转移到 $x$。那么为什么我们不先将 $y$ 减去一个 $k$ 然后再除以 $m$ 次 $2$ 呢？

证明：

将 $y$ 减去一个 $k$ 然后再除以 $m$ 次 $2$，操作数为 $k+m$，最终值为 $ (y-k)\div 2^m$。

变形一下：

$(y-k)\div 2^m=y\div 2^m-k\div2^m$

这样的话我们的操作数为 $m+(k\div 2^m)$ 次，明显比上面的少。

证毕。

- $y'>x$ 且 $y'$ 是奇数。

这种情况我们考虑转移到 $y'+1$ 或者 $y'-1$，这样我们就可以转化为情况 $2$ 了。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=2e5+5;
const int M=1e3;
const int MOD=903250223;
const int INF=1e9;
//变量
int n,a,b,c,x,y,ans,res,tmp,cnt,web[M][M];


//unordered_map<int,int> mp;
map<int,int> mp;
int dfs(int y){
	if(y<=x){
		return x-y;
	}
	if(mp[y])return mp[y];
	if(y%2)return mp[y]=min(dfs(y+1),dfs(y-1))+1;
	return mp[y]=min(y-x,dfs(y/2)+1);//+1是因为把y变成y/2需要一次操作
}

signed main(){
	scanf("%lld%lld",&x,&y);
	
	cout<<dfs(y);
	return 0;
}


```




---

## 作者：CrazyWisdom (赞：0)

### 前言
[[ABC188F] +1-1x2](https://www.luogu.com.cn/problem/AT_abc188_f)
的题解。

思路：记忆化搜索。

代码长度：短。

代码尾部有做题时的思路注记，可结合题解阅读。
### 思路
贪心思路总结不出来，于是采用记忆化搜索。

题目给出三种操作，分别是：

- $X+1$
- $X-1$
- $X*2$

要求执行尽量少次以上操作，使得 $X=Y$。

不难看出，以上要求相当于使用：

- $Y-1$
- $Y+1$
- $Y/2$

三种操作，使得 $Y=X$。

采用后者可以更好地寻找搜索策略。

#### 策略

首先我们发现 $X$ 与 $Y$ 的大小关系可能是这几种：

- $X>Y$
- $X<Y$
- $X=Y$

我们来进行分类讨论。

当 $X=Y$ 时，显然不需要进行任何操作即可相等，因此直接输出 $0$。

当 $X>Y$ 时，我们发现只有 $Y+1$ 这种操作能够使得 $Y=X$，因此操作数为 $X-Y$。

当 $X<Y$ 时，我们就需要进行搜索了，这时可以利用奇偶性来进行搜索。

我们发现，只有当 $Y$ 为偶数时，才可以进行除以 $2$ 的操作。因此我们可以采用 $Y/2$ 和 $Y-1$ 的操作来逼近 $X$。使用 $Y+1$ 是没必要的，因为显而易见这个操作的唯一作用就是把奇数的 $Y$ 变成偶数，然后用 $Y/2$ 来逼近 $X$，不然不会多余地去增加 $Y$。因此我们总结出偶数的搜索策略:

```cpp
min(dfs(y/2)+1,y-X)
```
然后我们考虑 $Y$ 为奇数的情况。由于奇数不能进行 $Y/2$ 操作，因此奇数只能进行加减法，所以奇数的策略是：

```cpp
min(dfs(y+1),dfs(y-1))+1
```
每次把新计算的 $Y$ 重复进行整个策略这章的操作即可。

最后记得加上记忆化。

### 代码
为减少长度，[代码](https://www.luogu.com.cn/paste/87abkyct) 见云剪贴板。
### 后记

此题解完全由自己思考，欢迎指正批评。


---

## 作者：Robin_kool (赞：0)

首先看到题目，可以理解为抽象的三种转移方法，第一眼想到的算法应该是dfs或者bfs，但是我们可以发现两个问题：

1、dfs不确定顺序，如果纯暴力肯定会以一种转移方法不断深搜，会爆炸。

2、看数据范围，bfs的队列很容易在多种状态(即使剪枝也不行)的累乘下溢出。



------------
### 因此可以采用记忆化以部分贪心的方式解决此题

$dp_i$ 表示从 $i$ 到 $y$ 的最少步数。

代码如下(记忆化部分注释会讲到):

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
unordered_map<ll,ll> dp;//10^18开map
ll x,y,ans;
inline ll read() {
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x) {
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline ll dfs(ll now) {
	if(now <= x) return x - now;//如果当前的值小于初始值，无法*2，因此只能不断减1
	if(dp.count(now)) return dp[now];//记忆化，调用之前已经得出的值
	return dp[now] = min(now - x, now % 2 ? min(dfs((now - 1) >> 1) + 2, dfs((now + 1) >> 1) + 2) : dfs(now >> 1) + 1);//这里有两种方案，不断减一或者/2找最小步数，如果now为奇数只能+1、-1使他变成偶数，注意加上当前操作的步数
}
signed main() {
	x = read(), y = read();
	ans = dfs(y);//考虑到从x开始的不确定因素比较多，所以这里用倒推法
	write(ans);
	return 0;
}

```


---

## 作者：COsm0s (赞：0)

## 前置芝士

[unorder_map](https://blog.csdn.net/weixin_45745854/article/details/122785542)

[记忆化](https://blog.csdn.net/hjf1201/article/details/78680814?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167265867216782425156049%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167265867216782425156049&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-78680814-null-null.142^v68^pc_rank_34_queryrelevant25,201^v4^add_ask,213^v2^t3_esquery_v1&utm_term=%E8%AE%B0%E5%BF%86%E5%8C%96%E6%90%9C%E7%B4%A2&spm=1018.2226.3001.4187)

## 思路

记忆化递归。

逆向搜索，从 $y$ 开始递归，期间求出各个数到 $x$ 的最小步数。

设递归函数为 $work(k)$，则 $work(k)$ 有两种情况。

* 当 $k<x$，则只能用第二种方法（即减 $1$）递归，则对答案的贡献为 $k-x$。

* 当 $k=x$，则已遍历到目标点，返回 $0$。

* 当 $k>x$，则可以用第一种方法和第三种方法（加 $1$ 或 乘 $2$）。有两种情况。
  
  + 当 $k$ 为奇数，则在第三种方法上有 $(k-1)÷2$ 或 $(k+1)÷2$ 两种递归策略，因为此时无法整除 $2$，只能先加 $1$ 变为偶数后再递归。此时第一种方法对答案的贡献为 $min(work((k-1)÷2),work((k+1)÷2)))+2$。
  
  + 当 $k$ 为偶数，则第三种方法对答案的贡献为 $work(k÷2)+1$。
  
  第一种方法的贡献为 $x-k$（显而易见，需要一步一步加上去），设第三种方法的贡献为 $sum1$，则整个 $work(k)$ 的贡献为 $min(sum1,x-k)$。
  


------------


但是，$10^{18}$ 的数据使得纯递归会超时，爆栈。
所以我们引入记忆化。

设 $mp$ 数组为记忆化数组。

当此数在记忆化数组中出现过，说明被搜索过了，那么直接返回，进行剪枝。

**注意，我们不能开这么大的数组，因此需要用 map 或 unordered_map 处理**。

而一般情况下， unordered_map 的复杂度为 $O(1)$，而 map 的复杂度为 $O(\log n)$，因此我们选择 unorder_map。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long x, y;
unordered_map<long long, long long> mp;//记忆化数组，注意long long 
inline long long work(long long k);
inline long long check(long long k) {
	if(k & 1) return min(work(k + 1 >> 1), work(k - 1 >> 1)) + 2;
	return work(k >> 1) + 1;
}//第三种情况的两种方法 
inline long long work(long long k) {
	if(k < x) return x - k;
	if(k == x) return 0;
	if(mp.count(k)) return mp[k];//记忆化处理 
	return mp[k] = min(k - x, check(k));
}
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);//输入输出优化 
    cin >> x >> y;
	cout << work(y) << '\n';
    return 0;
}
```


---

