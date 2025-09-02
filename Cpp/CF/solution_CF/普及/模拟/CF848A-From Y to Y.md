# From Y to Y

## 题目描述

From beginning till end, this message has been waiting to be conveyed.

For a given unordered multiset of $ n $ lowercase English letters ("multi" means that a letter may appear more than once), we treat all letters as strings of length $ 1 $ , and repeat the following operation $ n-1 $ times:

- Remove any two elements $ s $ and $ t $ from the set, and add their concatenation $ s+t $ to the set.

The cost of such operation is defined to be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848A/b9f484e4ed173bfc4ef212f87b2ee294375749df.png), where $ f(s,c) $ denotes the number of times character $ c $ appears in string $ s $ .

Given a non-negative integer $ k $ , construct any valid non-empty set of no more than $ 100000 $ letters, such that the minimum accumulative cost of the whole process is exactly $ k $ . It can be shown that a solution always exists.

## 说明/提示

For the multiset {'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b'}, one of the ways to complete the process is as follows:

- {"ab", "a", "b", "a", "b", "a", "b"}, with a cost of $ 0 $ ;
- {"aba", "b", "a", "b", "a", "b"}, with a cost of $ 1 $ ;
- {"abab", "a", "b", "a", "b"}, with a cost of $ 1 $ ;
- {"abab", "ab", "a", "b"}, with a cost of $ 0 $ ;
- {"abab", "aba", "b"}, with a cost of $ 1 $ ;
- {"abab", "abab"}, with a cost of $ 1 $ ;
- {"abababab"}, with a cost of $ 8 $ .

The total cost is $ 12 $ , and it can be proved to be the minimum cost of the process.

## 样例 #1

### 输入

```
12
```

### 输出

```
abababab
```

## 样例 #2

### 输入

```
3
```

### 输出

```
codeforces
```

# 题解

## 作者：lukelin (赞：5)

我们发现，最小的合并应该就是按字典序排列以后的顺序合并  
然后套个等差数列求和公式二分一下小学生都会做

```cpp
#include <cstdio>
#define ll long long

ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

ll getNum(ll a){
    return (((1 + a) * a) >> 1);
}

int main(){
    int k = read();
    if (k == 0){
        printf("ab");
        return 0;
    }
    char ch = 'a';
    while (k > 0){
        int l = 0, r = 100000, mid, ans = 0;
        while (l <= r){
            mid = (l + r) >> 1;
            if (getNum(mid) > k){
                r = mid - 1;
            }else{
                l = mid + 1;
                ans = mid;
            }
        }
        k -= getNum(ans);
        for (int i = 0; i <= ans; ++i)
            printf("%c", ch);
        ++ch;
    }
    return 0;
}
```

---

## 作者：Binary_Lee (赞：3)

## [题面传送门](https://www.luogu.com.cn/problem/CF848A)

### 解决思路

首先可以发现，一段长度为 $n+1$ 的连续相同字母合并所需的最小代价为 $1\times 1+2\times1+3\times 1\dots+n\times 1$（一个一个合并），构成了一个等差数列。

而当多段连续相同的字母组合在一起时，例如 $\text{aaaaacccyy}$，其总最小代价即为每段的代价相加（$10+3+1$），因为不同段之间没有相同字母，合并不需要代价。

因为 $k$ 的大小只有 $10^5$，所以我们可以大胆猜想：

$10^5$ 之内的数都可以表示为 $26$ 个之内三角形数（即 $\sum_{i = 1}^{x} i$）之和。~~通过打表~~事实证明，最多 $7$ 个数就够了。

所以答案显而易见。注意特判一下，$k=0$ 时输出任意一个字母，否则可能没有输出。

## AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0) 
#define int long long
using namespace std;
int i,k,f[10005];
char c='a';
signed main(){
	IOS;TIE;
	cin>>k;
	if(k==0) cout<<c;
	for(i=1;f[i-1]<=k;i++) f[i]=f[i-1]+i; //预处理三角形数
	for(int j=i-1;j>=1;j--){
    	while(k>=f[j]){     //从大到小，可以输出就输出
    		k-=f[j];
    		int t=j+1;   
    		while(t--) cout<<c;
    		c++;
		}
	}
	return 0;
}
```

---

## 作者：Pt_crN (赞：2)

简单构造题，评蓝高了。

首先手模样例，发现直接从左到右合并答案也是 $12$。所以提出猜想：无论怎么合并答案都一样。

当然你也可以和作者一样直接猜，挺容易猜到的。

证明：考虑对于每一对 $(i,j)$ 满足 $s_i=s_j$ 计算贡献。容易发现，每次合并 $s,t$ 本质上是计算有多少 $(x,y)$ 满足 $s_x=t_y$。所以每一对 $i,j$ 只会在 $i,j$ 合并到一起的时候产生贡献。

于是就变成用若干个 $\frac{i\times (i-1)}{2}$ 凑出 $k$。从大到小贪心即可。注意特判 $k=0$，不能输出空串。

code：

```cpp
int n;
void Yorushika(){
	scanf("%d",&n);
	if(!n){
		puts("a");
		return;
	}
	char c='a';
	drep(i,500,2){
		int x=i*(i-1)/2;
		while(x<=n){
			n-=x;
			rep(j,1,i){
				pc(c);
			}
			c++;
		}
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Karry5307 (赞：2)

### 题意

略。

$\texttt{Data Range:}1\leq n\leq 10^5$

### 题解

我会这场的 E 但是差点不会这场的 A……（其实是因为昨天打卡了 848 天所以来写这个题）

这个题一开始看发现不是很会，然后想了想发现其实不难。

CF 题目中样例给出的构造基本上具有误导性质，所以还是不要看为好。

首先是一个结论：对于 $n$ 个相同字母合并的最小贡献为 $\dbinom{n}{2}$，这个可以用数学归纳法证明出来。

假设对于 $1\sim n-1$ 结论都成立那么很明显枚举最后一次分割的位置，设答案为 $r_n$，那么很显然有

$$r_n=\min\left\{\binom{i}{2}+\binom{n-i}{2}+i(n-i)\right\}$$

大括号里面的东西不随 $i$ 的变化而变化，所以可以代入 $i=0$ 来计算得到答案为 $\dbinom{n}{2}$。

接下来考虑如下的构造：每一次二分出小于当前值最大的那个 $\dbinom{n}{2}$，加入 $n$ 个一样的字符然后换一个重复如下步骤，首先这个方法正确性显然，然后需要证明在这个范围内可以使用不超过 $26$ 种字符。

由于第一次操作之后 $n$ 最多不超过 $446$（因为 $\dbinom{448}{2}>10^5$ 而 $\dbinom{447}{2}<10^5$），然后还有 $25$ 个字符可以用，后面怎么搞都行吧。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,c,cur;
ll x[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read(),cur=97;
	if(!n)
	{
		return puts("ab"),0;
	}
	for(register int i=1;i<=1000;i++)
	{
		x[i]=i*(i-1)/2;
	}
	while(n)
	{
		c=upper_bound(x+1,x+1001,n)-x-1;
		for(register int i=1;i<=c;i++)
		{
			putchar(cur);
		}
		n-=x[c],cur++;
	}
}
```

---

## 作者：mulberror (赞：2)

## 题目大意
给一个费用k，输出一个字符串，合并这个字符串的最小费用为k，费用为：一个字母在两个字符串中出现的次数的乘的累加和。
## 题解
大力构造吼呀！
首先特判特殊情况，也就是$k=0$时，答案可以是$a$。  
好了特判完了。    
正解开始。    
简要分析一下。    
如果是最简单的。假设是这种情况$aaaaa..bbbbb..$。  
我们需要考虑的就是如何让这个费用是$k$。  
就让这个东西从左到右合并。     
每一次合并就是上一个相同颜色的费用$+1$。  
那么相同的颜色一共可以得到的费用就是$\frac{(n+1)\times n}2$（不要跟我说你不会等差数列求和公式   
可以证明这个情况一定是合法的。    
**证明：**  
我们可以用$\sum_{i=1}^{26}\frac{(x_i+1)\times x_i}2$来表示任意的$k$。  
易证。。。。（光速逃跑
~~如果以上的式子不成立，好像很多方法都是不可以做~~
那么我们只需要一步步逼近$k$就可以了。  
字符的种类没有关系。  
## 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
int main() {
	cin >> k;
	if (k == 0) { puts("a"); return 0; }
	for (int i = 0; i < 26 && k; i ++) {
		putchar('a' + i);
		for (int j = 1; j <= k; k -= j, j ++) putchar('a' + i);
	}
	return 0;
}
```

---

## 作者：zym20249_ (赞：0)

## []()


## 题意
对于一个包含 $n$ 个小写英文字母的无序多重集合，同一字母可以出现多次，你可以对它进行 $n−1$ 次如下操作：

从集合中移除任意两个元素 $s$ 和 $t$，将它们的拼接 $s+t$ 添加到集合中。更简单的说就是每次将无序多重集中的两个元素串合并为一个元素串。
这种操作的的代价为 $\sum_{c\in M}^{}f(s,c)\cdot f(t, c)$，其中 $f(s,c)$ 表示字符串 $s$ 中字符 $c$ 出现的次数， $f(t,c)$ 表示字符串 $t$ 中字符 $c$ 出现的次数，集合 $M$ 表示字符串 $s$ 和字符串 $t$ 字母集合，无序不重集。

给定一个非负整数 $k$，请你构建一个包含不超过 $10^5$ 个字母的有效非空无序多重集合，使得整个过程的最小代价总和恰好为 $k$。

## 思路
题目大致意思就是你要输出他一个串，满足代价为输入的值，操作为合并两个串，合并需要有代价。通过模样例我们会发现，这个合并满足结合律，即无论他什么顺序合并，最后的代价都是一样的。所以我们直接从大到小开始贪心枚举就可以。
### 注意事项
当 $k=0$ 时也需要输出，直接输出 `a` 即可。

---

## 作者：_Lazy_whr_ (赞：0)

根据贪心，最小的合并其实就是按字典序排列以后的顺序来合并。

所以我们可以按照字典序枚举每一个字符，二分出打印次数，可以用等差数列高斯求和把 $\sum_{i = 1}^{mid}{i}$ 优化成 $\frac{mid \times (mid + 1)}{2}$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define x1 x10
#define y1 y10
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 20), stdin), p1 == p2) ? EOF : *p1++)
// #pragma GCC target("avx")
// #pragma GCC optimize(3,"Ofast","inline")
namespace FastIO {
	char buf[(1 << 20)], *p1, *p2;
	char pbuf[(1 << 20)], *pp;
	inline int read () {
		int x = 0, f = 1;
		char ch = getchar ();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar ();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar ();
		}
		return x * f;
	}

	template<typename T> inline void read (T &x) {
		x = read ();
	}

	template<typename T,typename... Args> inline void read (T &x,Args &...x_) {
		read (x);
		read (x_...);
	}
}

namespace Constants {
	const int INF = 1e18;
	const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	const double EPS = 1e-7;
	const double PI = acos (-1);
}

using namespace std;
using namespace FastIO;
using namespace Constants;

void CLOSE () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	cout.tie (nullptr);
}

int n;

main() {
	CLOSE ();
	read (n);
	if (n == 0) { // 注意这种情况的特判
		cout << "ab" << endl;
		return 0;
	}

	char ch = 'a';
	while (n > 0) {
		int l = 0, r = 1e5;
		int ret = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (mid * (mid + 1) / 2 <= n) { // 等差数列求和
				l = mid + 1;
				ret = mid;
			} else {
				r = mid - 1;
			}
		}
		n -= ret * (ret + 1) / 2;
		for (int i = 0; i <= ret; i++) {
			cout << ch;
		}
		ch++;
	}
	cout << endl;
	return 0;
}
```

---

## 作者：xiaoxiaoxia (赞：0)

## 题目概要
对于给定的一个长度为 $n$ 的字符串，初始时，我们将它视作 $n$ 个长度为 $1$ 的字符串的可重集，然后重复下列操作 $n-1$ 次：

- 从这些字符串中任取两个字符串 $s,t$，将它们删除，将 $s+t$ 加入集合。注意这里的 $+$ 是指字符串拼接。

操作的成本被定义为 $\sum_{c\in\left\{\texttt{a},\texttt{b},\cdots,\texttt{z}\right\}}f\left(s,c\right)\times f\left(t,c\right)$，其中 $f\left(s,c\right)$ 是字符 $c$ 在 $s$ 中出现的次数。更通俗地说，每次操作的成本为**每个小写字母在两个字符串中出现次数的积**。

现在给定一个非负整数 $k\left(0\leqslant k\leqslant 10^5\right)$，请你构造一个不超过 $10^5$ 个字符的可重集，使得操作成本的最小值为 $k$。可以证明，这样的解一定是存在的。
## 思路概述
我觉得话这一道题目就是一个简单的构造题目，随便取一段字符串来看看，就不难发现就是一个等差数列，所以说最小的合并应该就是按字典序排列以后的顺序合并。所以代码的结构差不多就是直接循环走一遍，然后如果可以输出就输出，不然就不输出。
然后我们证明一下:
考虑对于每一对 $\left(i,j\right)$ 满足 $s_i=s_j$ 计算贡献，然后我们可以每次合并看一下，他到底想让我们干什么东西，所以不难得出：如果合并 $s,t$，本质就是计算有多少 $\left(x,y\right)$ 满足 $s_x=t_y$。所以我们就可以等到两个东西合并后再计算答案。所以最后就跟上面的一样，就是贪心。
## 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,f[10005];
char ans='a';
signed main()
{
	cin>>k;
	if(k==0) 
		cout<<ans;
	int i=1; 
	for(i=1;f[i-1]<=k;i++) 
	 	f[i]=f[i-1]+i;
	for(int j=i-1;j>=1;j--)
	{
    	while(k>=f[j])
		{
    		k-=f[j];
    		int t=j+1;   
    		while(t--) 
				cout<<ans;
    		ans++;
		}
	}
	return 0;
}
```

---

## 作者：方123456 (赞：0)

有趣的构造题。

可以尝试手玩几个东西，比如说 `aa` 还有 `aaa` 以及 `aaaa`，玩出来的结果分别是 $1$ 和 $1+2$ 还有 $1+2+3$。

可以发现，对于相同字符出现了 $j$ 次，那么它产生的贡献即为 $1+2+3+4+ \cdots + j$。

上面这个是等差数列，把它写出来是 $\dfrac{j \times (j+1)}{2}$，发现这东西不超过 $\sqrt n$ 个。

那么我们把这些等差数列的和写出来打个背包，发现很有趣的是 $10^5$ 大约只需要 $21$ 个字母就可以完成。

因此，我们直接对 $k$ 进行拆解，拆成若干等差数列的和，然后用背包倒推求字符串。

具体的，字符串一定是 `aaaaaa....bbbbb...cccc...dddd` 这样的形式。

然后就做完了，复杂度 $O(n \sqrt n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring> 
#define int long long 
using namespace std;
const int INF=1e5+5;
int n,F[INF],f[INF],f1[INF],f2[INF];
string ans;
void print(int x,int y) {
	if (!x) return ;
	for (int i=f2[x]+1;i;i--) 
		ans+=(char)(y+'a');
//	ans+=(char)(y+'a');
	print(x-f1[x],y+1);
}
void solve() {
	memset(F,63,sizeof F);
	cin>>n;f[1]=1;f[2]=3;
	for (int i=3;i<=100;i++) f[i]=f[i-1]+i;
	if (n==0) {
		cout<<"a\n";
		return ;
	}
	F[0]=0;
	for (int i=1;i<=n;i++) {
		for (int j=100;j>=1;j--)
			if (i>=f[j]) {
//				F[i]=min(F[i-f[j]]+1,F[i]);
				if (F[i]>F[i-f[j]]+1) {
					F[i]=F[i-f[j]]+1;
					f1[i]=f[j];
					f2[i]=j;
//					cout<<i<<" "<<f2[i]<<" "<<f1[i]<<" yiwyiw\n";
				}
			}
	}	
//	for (int i=1;i<=n;i++)
//		cout<<F[i]<<" ?\n";
	print(n,0);
	cout<<ans<<"\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	int t=1;
	while (t--) solve();
	return 0;
}
```


---

## 作者：aimcf (赞：0)

$\color{blue}\texttt{Difficulty : 1600}$

结论题。

定义 $S(x)$ 为 $1 + 2 + 3 + \cdots + x = \frac{x\times (x+1)}{2}$。

结论 $1$：一段长度为 $n$ 且所有字母都相同的字符串合并时间为 $S(n - 1)$。

结论 $2$：一个被分成 $k$ 段长度为 $a_i$ 并且每一段中所有字母都相同，任意两个不同段中没有相同的字母，那么合并需要时间是 $\sum_{i=1}^k S(a_i - 1)$。

> It can be shown that a solution always exists.

也就是说，题目保证存在一组这样的解。

那么打表 $10^3$ 个 $S(i)$，用这些 $S(i)$ 的和凑出来 $n$ 即可。

特殊：$n=0$ 需要输出一个随机的字母，否则会 $\texttt{\color{red}{WA}}$。

使用双指针的时间复杂度为 $O({c})$ 的，其中 $ c$ 是一个常数。

[Code](https://codeforces.com/contest/848/submission/176668816)

---

## 作者：泠小毒 (赞：0)

# From Y to Y

给你一个数n，让你构造一个小写字母序列使它的最小答案为n

对于答案的定义是执行n-1次合并操作，每次合并操作有一个贡献，答案即为n-1次操作的贡献之和

对于贡献的定义是两个序列合并时，枚举每一个字母'a'~'z'，每一个字母的子贡献为字母在两个序列中出现次数的乘积，而贡献是子贡献之和

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190429/)

## 解法

你可以发现，对于相同的n个字母，不管怎么合，贡献都是n*(n-1)/2

而对于不同的字母，合并时没有贡献

所以把1~n这一区间的贡献都求出来，由于只有26个字母，所以一种字母的贡献尽量的大

tips：n为0时要特判，随便输出一个字母

## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,res,ans[30];
long long f[100010];
int main()
{
	scanf("%d",&n);
	if(!n){puts("a");return 0;}
	for(int i=2;i<=n+5;i++)f[i]=f[i-1]+i-1;
	while(n)
	{
		k=upper_bound(f+1,f+1+n+5,n)-f-1;
		ans[++res]=k;
		n-=f[k];
	}
	for(int i=1;i<=res;i++)
		for(int j=1;j<=ans[i];j++)
			printf("%c",'a'+i-1);
	return 0;
}
```

---

