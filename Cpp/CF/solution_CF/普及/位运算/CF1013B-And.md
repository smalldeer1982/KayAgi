# And

## 题目描述

There is an array with $ n $ elements $ a_{1},a_{2},...,a_{n} $ and the number $ x $ .

In one operation you can select some $ i $ ( $ 1<=i<=n $ ) and replace element $ a_{i} $ with $ a_{i}&x $ , where $ & $ denotes the [bitwise and](https://en.wikipedia.org/wiki/Bitwise_operation#AND) operation.

You want the array to have at least two equal elements after applying some operations (possibly, none). In other words, there should be at least two distinct indices $ i≠j $ such that $ a_{i}=a_{j} $ . Determine whether it is possible to achieve and, if possible, the minimal number of operations to apply.

## 说明/提示

In the first example one can apply the operation to the last element of the array. That replaces 7 with 3, so we achieve the goal in one move.

In the second example the array already has two equal elements.

In the third example applying the operation won't change the array at all, so it is impossible to make some pair of elements equal.

## 样例 #1

### 输入

```
4 3
1 2 3 7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 228
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 7
1 2 3
```

### 输出

```
-1
```

# 题解

## 作者：Surge_of_Force (赞：8)

首先证明一个结论：**$x\ \&\ y = x\ \&\ y\  \&\ y\ \&\ y ······\& \ y$**。

证明这个结论可以从集合的角度来想：

$ x\ \&\ y$ 就相当于是 $ x_{(2)}$ 与 $y_{(2)}$ 取交，而 $x\ \&\ y\ \&\ y$ 相当于 $y$ 与 $x\cap y$ 取交，显然 $x\cap y$ 是 $y$ 的子集，而一个集合与自己的子集无论取多少次交，结果都是那个原来的子集，所以该结论得证。

那么有了这个结论，我们就可以考虑开两个桶，一个存储 $a_i$ 是否出现过，一个 $a_i\ \&\ x$ 是否出现过，扫一遍原数组，对答案取个 $\min$，然后输出就好了。

附 AC 代码：

```cpp

#include<bits/stdc++.h>
#define ll long long
// #define int long long
using namespace std;
inline int read() {
  int fh = 1, res = 0; char ch = getchar();
  for(; !isdigit(ch); ch = getchar()) if(ch == '-') fh = -1;
  for(; isdigit(ch); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ '0');
  res = res * fh;
  return res;
}
inline void write(ll x) {
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int tong1[100010],tong2[100010];
int main()
{
	int n=read(),x=read(),ans=3;//显然答案集合是{0,1,2}，所以初值赋为3就好了
	for(int i=1;i<=n;i++)
	{
		int a=read();
		if(tong1[a])
		{
			cout<<0;//一个小优化，遇到答案为0直接输出
			return 0;
		}
		if(tong2[a]||tong1[a&x]) ans=min(ans,1);
		if(tong2[a&x]) ans=min(ans,2);
		tong1[a]=tong2[a&x]=1;
	}
	cout<<(ans==3?-1:ans);
	return 0;
}

---

## 作者：fmj_123 (赞：6)

这题需要用到一个性质：$x$&$y=x$&$y$&$y$...&$y$

所以，每个数只用&一次，再用数组记录一下就行了。把数组每个数&后寻找是否在数组中有这个数或有&之后等于次数的数,再判断无解和输出0的情况就可以通过了。

```
#include<bits/stdc++.h>
using namespace std;
int n,x,a[100100],b[100100],minn=2147483647;
int main()
{
	cin>>n>>x;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (b[a[i]]) {cout<<0;return 0;}//有重复的数，直接输出0
		b[a[i]]=1;//1代表直接得到的，2代表&得到的
	} 
	for (int i=1;i<=n;i++)
	{
		if (b[a[i]&x]&&(a[i]&x)!=a[i]) {minn=min(minn,b[a[i]&x]);}	
        //有相同，取操作次数的最小值（萌新因为这个被Hack了一次）
		if (!b[a[i]&x])b[a[i]&x]=2;//记录此数
	}
	if (minn<=2) cout<<minn<<endl;else
	cout<<-1;//无解输出-1
	return 0;
} 
```
from-$div2$还$rank2135$的蒟蒻


---

## 作者：Cappuccino_mjj (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/CF1013B)
题目意思：

给你一个长度为 $n$ 的序列 $a_i$，再给一个数 $x$。每一步你可以将序列中的一个数与上 $x$。请问最少要多少步才可以使得序列中出现两个相同的数，如果无解输出 $-1$。

---

思路：
1. 首先通过找规律我们发现：一个序列最多与两次 $x$，最少与零次 $x$ 就可以出现两个相同的数。
2. 那么首先我们就先判断当前序列中是否已经存在两个相同的数了，如果有，就直接输出 $0$。
3. 如果上述的条件不成立，我们就将序列中的每一个数都与上 $x$ 并存入一个数组中，判断原本的序列里和现在与完 $x$ 的序列里是否有相同的数，并且它们两个不在同一个位置。如果有，就输出 $1$。
4. 如果上述的条件还不成立，我们就判断与完 $x$ 后的序列中有没有两个同样的数，如果有，就输出 $2$。
5. 如果以上条件都不成立，就证明无解，输出 $-1$。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
const int N=5e5+10;
int a[N],b[N],c[N],d[N];
int main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(b[a[i]]>1)//原本的序列中已有两个相同的数
		{
			cout<<0;
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		c[i]=a[i]&x;
		d[c[i]]++;
		if(b[c[i]]&&c[i]!=a[i])
		{//原本的序列与现在的序列中有相同的数并且不在同一个位置
			cout<<1;
			return 0;
		}
	}
	for(int i=1;i<=500005;i++)
	{
		if(d[c[i]]>1)
		{//现在的序列中有相同的数
			cout<<2;
			return 0;
		}
	}
	cout<<-1;//无解
	return 0;
}
```

---

完美撒花~

---

## 作者：peppaking8 (赞：4)

## 思路

首先，考虑 $S=a\ \text{and}\ b$ 的本质，即为将 $a$ 和 $b$ 化为二进制，如果对于一个二进制位，两个数均为 $1$，此时 $S$ 的这一位为 $1$，否则为 $0$。

这就得到了：如果 $b$ 的某一位是 $0$，则 $S$ 的这一位必定是 $0$，故 $S\ \text{and}\ b=S$。

综上所述，$a\ \text{and}\ b=a\ \text{and}\ b\ \text{and}\ b....$

所以这就告诉我们，将一个数与 $x$ 与多次是**没有意义的**。所以答案只有 $-1,0,1,2$。

如果答案是 $0$，则开始的 $a$ 数组中就有两数相同。这很好判断。

如果答案是 $1$，即存在 $a_i\ \text{and}\ x=a_j$，其中 $i$ 不等于 $j$。考虑将 $a_i$ 的值记录为一个桶，如果 $a_i\ \text{and}\ x$ 不等于 $a_i$，并且存在 $a_i\ \text{and}\ x=a_j$，则输出 $1$ 即可。

如果答案是 $2$，即存在 $a_i\ \text{and}\ x=a_j\ \text{and}\ x$，其中 $i$ 不等于 $j$。定义 $b_i=a_i\ \text{and}\ x$，则判断 $b_i$ 中是否有相等即可。

如果以上三种答案都不满足，则输出 $-1$ 即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,x;
int a[N],b[N];//同思路中定义的数组
int t[N];//桶
int main(){
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		t[a[i]]++;//记录桶
		if(t[a[i]]>=2){//如果出现两个相同的数，直接输出0并退出
			printf("0\n");
			exit(0);
		}
	}
	for(int i=1;i<=n;i++){
		b[i]=a[i]&x;//处理b数组
		if(t[b[i]]&&b[i]!=a[i]){//如果b[i]不等于a[i]，并且存在a[j]使得a[j]=b[i]，则直接输出1并退出
			printf("1\n");
			exit(0);
		}
	}
	memset(t,0,sizeof(t));//重新记录桶，这回要记录b数组
	for(int i=1;i<=n;i++){
		t[b[i]]++;
		if(t[b[i]]>=2){//如果b数组出现相同，输出2并退出
			printf("2\n");
			exit(0);
		}
	}
	printf("-1\n");//否则，输出-1，即为不存在
	exit(0);//拜拜~记得点个赞再走哦~
} 
```

---

## 作者：Uuuuuur_ (赞：1)

## 思路
这道题要用到一个很重要的技巧，$a\&b=a\&b\&b$，所以，我们的答案只会有 $-1,0,1,2$四种情况，分别对应，无解，原数组两个数相等，一个进行与操作过的数和原数组一个数相等，两个进行与操作过的数相等。

## 代码
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int a[100005], n, x;
bool vis[100005];
bool f;
int main() {
	cin >> n >> x;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		
		if (vis[a[i]]) {
			f = 1;
		}
		vis[a[i]] = 1;
	}
	if (f) {
		cout << 0;
		return 0;
	}
	
	for (int i = 1; i <= n; i++) {
		if (vis[a[i] & x] && (a[i] & x) != a[i]) {
			cout << 1;
			return 0;
			
		} 
	}
	
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		a[i] &= x;
		if (vis[a[i]]) {
			cout << 2;
			return 0;
		}
		vis[a[i]] = 1;
	}
	cout << -1;
	return 0;
}
```


---

## 作者：Binary_Lee (赞：1)

## [题面传送门](https://www.luogu.com.cn/problem/CF1013B)

### 解决思路

首先我们可以得出，$ a $ $\&$ $ x $ $=$ $ a $ $\&$ $ x $ $\&$ $ x $。由此得知，同一个 $a$ 反复 $\&$ $x$ 是没有意义的。所以我们得到，答案仅可能是以下几种情况：

- $ans = 0$ ，即有相同的数字，不需要操作。
- $ans = 1$ ，即对于某个 $a_i$ $\&$ $ x $ $=$ $a_j$，其中 $1 \le i,j\le n $ 且 $j \ne i$ 。
- $ans = 2$ ，即对于某两个 $a_i$ $\&$ $ x $ $=$ $a_j$ $\&$ $ x $ ，其中 $1 \le i,j\le n $ 且 $j \ne i$ 。
- $ans = -1$ ，即对于任意的 $a_i$ $\&$ $ x $ $\ne$ $a_j$ $\&$ $ x $ ，其中 $1 \le i,j\le n $ 且 $j \ne i$ 。

有了这个思路，再看到$a_i \le 10^5$ ，我们就可以借助桶存下每个  $a_i$ $\&$ $ x $ ，然后判断即可。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[100005],t[100005],t2[100005],fl; 
//t储存a[i]&x,t2用于判重（ans=0的情况） 
int main(){
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	if(t2[a[i]]!=0){
    		printf("0");
    		return 0;     //ans=0的情况
		}
		t2[a[i]]++;
    	if((a[i]&x)!=a[i]) t[a[i]&x]++;  //a[i]&x=a[i]的不能计算在内 
    	if(t[a[i]&x]>=2) fl=1;  //如果出现过两次，就必有解 
	}
	for(int i=1;i<=n;i++){
		if(t[a[i]]>0){
			printf("1");  //ans=1的情况
			return 0;
		}
	}
	if(fl==1) printf("2");   //有解
	else printf("-1");       //无解
  	return 0; 
}
```


---

## 作者：Edmundino (赞：1)

# 题意

```
给定一个长度为 n 的序列 a[i]，并给定一个数 x。
每一步可以将序列中的一个数与上 x。
求使序列中出现两个相等的数的最小步数。如果不可能则输出 −1。
```


# 分析

首先我们需要知道一条式子：

$ a$&$b=a$&$b$&$b$……&$b$（$ b $的个数大于等于$0$）

证明：

当$a$&$b$得到的值，我们把这个值设为$c$。

此时$c$转为二进制的数中为$1$的位置在$b$的二进制数也是$1$。

所以$c$&$b=c$。

接着我们来看一下这一题：


所以这题最大的步数不会超过$2$。

然后，分类讨论就行啦。

$o$为要输出的数，

初始化为$-1$。

如果原来的数组中有重复的数：

$o=0$。

接着来两次&$x$，判断有没有相同的数。

如果有，$o=$次数。

没有 $o=-1$。






# 代码

**$AC$代码**

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<map>

using namespace std;

int n,k,x,o;

map<int,int>ma,mb;

int main()
{
    o=-1;
   cin>>n>>x;
   while(n--)
   {
     cin>>k;
     if(ma[k]>0)
     {
        o=0;
     }
     if(o!=0&&ma[k&x]>0||o!=0&&mb[k]>0)
     {
        o=1;
     }
     if(o==-1&&mb[k&x]>0)
     {
       o=2;
     }
     ma[k]++;
     mb[k&x]++;
   }
   cout<<o;
}

  
```


---

## 作者：Claire0918 (赞：0)

下文中，用 $\&$ 表示位与运算。

定理 $1$：$x \& y = x \& y \& y \ldots \& y$。

证明：

显然，位与运算满足结合律。故 $x \& y \& y \ldots \& y = x \& (y \& y \ldots \& y)$。

同时，位与运算具有自反性，即 $x \& x = x$。可得 $x \& y \& y \ldots \& y = x \& y$。$\square$

记结果为 $r$。

则必有 $r \leq 3$。因为若需要 $3$ 个或更多个数参与运算且有两个数结果相等，则只需要那两个数参与运算即可。否则，由位运算的自反性得，一个数多次参与运算没有意义。

开两个桶 $vis1$ 和 $vis2$。$vis1_i = 1$ 表示 $a$ 中出现了 $i$，$vis2_i = 1$ 表示 $a$ 中出现了 $k$，使得 $k \& x = i$。

设当前读入为 $in$。

如果 $vis1_{in} = 1$，则 $a$ 中有重复的 $in$，$r = 0$。

否则，如果 $vis2_{in}$ 或 $vis1_{in \& x}$，表示 $a$ 中出现了 $k$，使得 $k \& x = in$。情况二可用自反性转化为情况一。此时需要做一次运算，$r = \min\{r, 2\}$。

否则，如果 $vis2_{in \& x} = 1$，则 $a$ 中出现了 $k$，使得 $k \& x = in \& x$，对 $k$ 和 $in$ 分别进行运算即可，$r = \min\{r, 2\}$。

如果最后 $r = 3$，则无解。

Code:
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 100000 + 10;

int n, x, res = 3;
bool vis1[maxn], vis2[maxn];

int main(){
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++){
        int a;
        scanf("%d", &a);
        if (vis1[a]){
            printf("0");
            return 0;
        }
        if (vis2[a] || vis1[a & x]){
            res = min(res, 1);
        }
        if (vis2[a & x]){
            res = min(res, 2);
        }
        vis1[a] = vis2[a & x] = true;
    }
    printf("%d", res == 3 ? -1 : res);

return 0;
}
```

---

## 作者：Aw顿顿 (赞：0)

先简单说明一个引理：$a\text{ and }b=a\text{ and }b\text{ and }b$。

对于两者中存在一个 $0$ 的情况，进行无数次与运算结果都不会变成 $1$，同理，如果两者都是 $1$，则运算结果恒为 $1$。对于每一个位考虑如此，对于整个数而言便也是如此，由此可以得出结论，$a$ 与上 $b$ 无论运算多少次，答案都和与一次一样。

那么将 $a_i$ 中的数每个都和 $x$ 进行依次与运算，之后判断是否存在相同数即可。

考虑运算个数。

- 若原数组本来就有重复，则无需操作，输出 $0$。
- 若某个数操作过后与原数组中另一个数重复，则只需要操作一次输出 $1$。
- 若某两个数在操作过后有相等，则需要将这两个数分别操作，输出 $2$。
- 否则输出 $-1$。

有什么值得注意的呢？

首先显然，如果某个数**操作过后没有变化，那这个数肯定是没有用的**，否则在第一轮筛查的时候就会发现了。我们来思考如果没有进行这样的判断会出现怎样的情况：“我”进行与运算之后和“我”相同，于是输出了 $1$——而这显然是不符合条件的。

你或许会想到通过排序进行计数，这样有两个问题：

- 操作过后的数组和原数组不方便进行比对。
- 时间复杂度 $O(n\log n)$ 不够优秀。

显然，$a_i\le 10^5$ 的数量级足够我们开一个桶进行记录，不过需要注意的是，在进行操作后数组比对之前，要重新清空桶。

这里给出代码实现：

```cpp
#include<bits/stdc++.h>
#define N 100005 
using namespace std;
int n,x,a[N],axor[N],t[N];
signed main(){
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);t[a[i]]++;
		if(t[a[i]]>1){puts("0");return 0;}
	}for(int i=1;i<=n;i++){
		axor[i]=a[i]&x;
		if(axor[i]!=a[i]&&t[axor[i]]){puts("1");return 0;}
	}memset(t,0,sizeof t);
	for(int i=1;i<=n;i++){
		t[axor[i]]++;
		if(t[axor[i]]>1){puts("2");return 0;}
	}puts("-1");return 0;
} 
```


---

## 作者：小蒟蒻皮皮鱼 (赞：0)

首先，对于与运算，有一个显然的性质是 $a\ \& \ b \leq\min(a,b)$ ，因为与运算只会把1变为0，而不会把0变为1。

其次，考虑与运算的性质。一个数多次按位与同一个数，得到的结果是相同的。

注意到这道题里 $a_i\leq 10^5$ ，这启示我们对于开一个桶，记录每一个数是否可以通过与运算获得。由于性质一，桶的大小和 $a_i$ 的大小是相同的。

通过性质二可以知道，如果可以通过与运算获得两个相同的数，答案只可能是0、1、2，分别对应原数列有两个数相同，原数列一个数与 $x$ 可以得到原数列的另一个数，原数列两个数与 $x$ 的结果相同。

有一个小坑，注意如果一个数按位与 $x$ 是他自己，那么这时不需要累加到对应的桶中。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
int n, a[N], b[N], x;
int main()
{
	scanf("%d%d", &n, &x);
	for(int i = 1; i <= n; i ++) 
	{
		scanf("%d", &a[i]);
		b[a[i]] ++;
		if(b[a[i]] > 1) 
		{
			printf("0");
			return 0;
		}
	}
	memset(b, 0, sizeof(b));
	for(int i = 1; i <= n; i ++)
	{
		if((a[i] & x )!= a[i])
			b[a[i] & x] ++;
	}
	for(int i = 1; i <= n; i ++)
	{
		if(b[a[i]])
		{
			printf("1");
			return 0;
		}
	}
	for(int i = 0; i < N; i ++)
	{
		if(b[i] >= 2) 
		{
			printf("2");
			return 0;
		}
	}
	printf("-1");
	return 0;
}
```



---

