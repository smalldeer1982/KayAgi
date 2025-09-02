# NIT orz!

## 题目描述

NIT, the cleaver, is new in town! Thousands of people line up to orz him. To keep his orzers entertained, NIT decided to let them solve the following problem related to $ \operatorname{or} z $ . Can you solve this problem too?

You are given a 1-indexed array of $ n $ integers, $ a $ , and an integer $ z $ . You can do the following operation any number (possibly zero) of times:

- Select a positive integer $ i $ such that $ 1\le i\le n $ . Then, simutaneously set $ a_i $ to $ (a_i\operatorname{or} z) $ and set $ z $ to $ (a_i\operatorname{and} z) $ . In other words, let $ x $ and $ y $ respectively be the current values of $ a_i $ and $ z $ . Then set $ a_i $ to $ (x\operatorname{or}y) $ and set $ z $ to $ (x\operatorname{and}y) $ .

Here $ \operatorname{or} $ and $ \operatorname{and} $ denote the [bitwise operations OR and AND](https://en.wikipedia.org/wiki/Bitwise_operation) respectively.

Find the maximum possible value of the maximum value in $ a $ after any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, one optimal sequence of operations is:

- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (3\operatorname{or}3)=3 $ and $ z $ becomes $ (3\operatorname{and}3)=3 $ .
- Do the operation with $ i=2 $ . Now $ a_2 $ becomes $ (4\operatorname{or}3)=7 $ and $ z $ becomes $ (4\operatorname{and}3)=0 $ .
- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (3\operatorname{or}0)=3 $ and $ z $ becomes $ (3\operatorname{and}0)=0 $ .

After these operations, the sequence $ a $ becomes $ [3,7] $ , and the maximum value in it is $ 7 $ . We can prove that the maximum value in $ a $ can never exceed $ 7 $ , so the answer is $ 7 $ .

In the fourth test case of the sample, one optimal sequence of operations is:

- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (7\operatorname{or}7)=7 $ and $ z $ becomes $ (7\operatorname{and}7)=7 $ .
- Do the operation with $ i=3 $ . Now $ a_3 $ becomes $ (30\operatorname{or}7)=31 $ and $ z $ becomes $ (30\operatorname{and}7)=6 $ .
- Do the operation with $ i=5 $ . Now $ a_5 $ becomes $ (27\operatorname{or}6)=31 $ and $ z $ becomes $ (27\operatorname{and}6)=2 $ .

## 样例 #1

### 输入

```
5
2 3
3 4
5 5
0 2 4 6 8
1 9
10
5 7
7 15 30 29 27
3 39548743
10293834 10284344 13635445```

### 输出

```
7
13
11
31
48234367```

# 题解

## 作者：Prms_Prmt (赞：2)

### 首先看与、或运算的特殊性质。

$z'=z \land x$：原来是 $ 0 $ 的位仍然是 $ 0 $；原来是 $ 1 $ 的位不一定是 $ 1 $.
如果把 $ 0 $ 看作该位不在集里，$ 1 $ 反之，则 $ z' \subset  z $.

$z'=z \lor x$：原来是 $ 0 $ 的位不一定是 $ 0 $；原来是 $ 1 $ 的位仍然是 $ 1 $.
如果把 $ 0 $ 看作该位不在集里，$ 1 $ 反之，则 $ z \subset z' $.

可以想见, 无论 $ x $ 取值， 在 $ z' = x \land z $ 下，因为 $ z' \subset z $，所以 $ z $ 始终**不逊于** $ z' $.

#### 则仅需操作一次即可（$ z $ 取原值一定最优）。

接下来循环取和 $ z $ 或求最大值即可，放码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,a,z;

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int mx=0;
		scanf("%d%d",&n,&z);
		for(int i=1;i<=n;i++)
			scanf("%d",&a),mx=max(mx,a|z);//求最大值
		printf("%d\n",mx);
	}
	return 0;
}
```
### 后记
	2023/6/29  感谢 hdkghc 的提醒，修正了不恰当的集合符号。

---

## 作者：zhicheng (赞：2)

### 思路

题目中说每一次操作过后，$a_i$ 会**或**上 $z$，$z$ 会**与**上 $a_i$。而题目要求输出操作后最大的一个 $a_i$，所以要使 $z$ 尽量大。而**与**操作要求两个操作数这一位上都是 $1$，所以 $z$ 经过操作后，为 $0$ 的位上不可能是 $1$。也就是说，$z$ 只能越来越小。所以第一次操作一定是最大的。枚举每个 $a_i$ 即可。

### Code

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a,b,p,ans;
	scanf("%d",&n);
	while(n--){
		ans=0;
		scanf("%d%d",&a,&b);
		while(a--){
			scanf("%d",&p);  //枚举每个数
			ans=max(ans,b|p);  //一次操作肯定是最优的
		}
		printf("%d\n",ans);  //取最大输出
	}
}
```

---

## 作者：Morgen_Kornblume (赞：1)

# A

**or** （或操作），只有可能让 $a_i$ 中为 1 的二进制位变得更多，而 **and** （与操作）不会让 $z$ 中为 1 的位置变多，只有可能让它们的数量越变越少。

所以我们由以上可以证明，只用贪心地做一次操作，答案即为所有 $a_i|z$ 的最大值。

```cpp

int T;
	
	int n,z;
	
	int a[2010];
	
	void main(){
		cin>>T;
		
		while(T--){
			
			cin>>n>>z;
			
			int ans=0;
			
			for(int i=1;i<=n;i++)cin>>a[i];
			for(int i=1;i<=n;i++)ans=max(ans,a[i]|z);
			
			cout<<ans<<endl;
			
		}

	}

```


---

## 作者：智子 (赞：1)

## 题目大意

给你一个长度为 $n$ 的整数序列 $a$ 和一个整数 $z$，你可以执行若干次（可以为零）操作，每次操作将 $a_i$ 变为 $(a_i\operatorname{or} z)$ 并将 $z$ 变为 $(a_i\operatorname{and} z)$。求序列 $a$ 中最大值最大可能是多少。

## 思路

考虑位运算的性质，$z$ 在进行与运算的过程中一定只会减少而不会增大，并且为 0 的位不可能再变成 1。所以对于一个已经与 $z$ 进行过运算的数，在任何情况下再与 $z$ 进行运算，其值也不会增大。所以答案就是序列 $a$ 中每个 $a_i$ 与 $z$ 进行或运算后的最大值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2000 + 5;

int a[MAXN];
int n, z;

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &z);
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            ans = max(ans, a[i] | z);
        }
        printf("%d\n", ans);
    }

    return 0;
}
```

---

## 作者：Jasper08 (赞：1)

### 题目分析

在本文中，我们约定 $|$ 表示 **按位或** ，$\&$ 表示 **按位与** 。

**定理** $1$ 若 $a,b$ 均为正整数，则 $a\&b\le \min(a,b)$ .

首先我们知道 $1\&1=1,1\&0=0,0\&1=0,0\& 0=0$ . 也就是说，只有在 $a,b$ 的第 $k$ 位均为 $1$ 时，$a\&b$ 的第 $k$ 位才能是 $1$ ，否则就为 $0$ . 所以当 $b=a$ 时（即 $a$ 和 $b$ 的二进制表示完全相同），$a\& b$ 取得最大值 $a$ .

例如，若 $a=12=(1100)_2,b=9=(1001)_2$ . 则 $a\&b=(1000)_2=8<9$ .

**定理** $2$ 若 $a,b$ 均为正整数，则 $a|b\ge \max(a,b)$ .

也是从定义出发，这里不再赘述。还是举例子 $a=12,b=9$ 的例子，$a|b=(1101)_2=13>12$ .

那么，为了求出 $\{a\}$ （这里的 $\{a\}$ 表示题目中的数组 $a$ ）中的最大值，由于 $z$ 的值总是不会变大，所以只需要将 $z$ 与 $\{a\}$ 中的一个数进行一次操作并取最大值即可。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x*f;
}

int main() {
	int t = read();
	while (t -- ) {
		int n = read(), z = read();
		int maxl = 0;
		for (int i = 1; i <= n; ++i) {
			int a = read();
			maxl = max(a|z, maxl); //取按位或的最大值
		}
		int ans = maxl;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Dry_ice (赞：1)

[Blog浏览](https://www.cnblogs.com/dry-ice/p/16414694.html)

> 作为 Global Round の 第一题还是有一定难度的。

其实 cf 题目都这样，思维想通了代码很容易。

## 问题分析
考虑这道A题，发现 $z$ 会不断的进行按位与（$\text{and}$）。由按位与的性质可以知道 $z$ 的变化趋势是不严格单调**递减**（二进制中 $1$ 个数只减不加），而通过按位或尽量得使序列 $a$ 中的数字变大，故要使 $a$ 中出现可能的最大值，每数必须**仅有不超过一次**操作；倘若经过第二次操作，由于 $z$ 不严格单减，则有操作数 $a_i$ 和 $z$ 的 $\text{or}$ 值**一定不会大于**第一次对 $a_i$ 的操作结果。

综上所述，对于任意 $a_i$，最多**仅有一次**操作，故只需遍历找出 $\max\{a_i \text{or}\ x\}$ 就可以了。

## Code
```cpp
#include <stdio.h>
int n, z;
int main(void) {
    int t;
    for (scanf("%d", &t); t--; ) { //多组数据
        scanf("%d %d", &n, &z); int Ans = 0;
        for (int i = 1, a; i <= n; ++i) {
            scanf("%d", &a);
            Ans = (a | z) > Ans ? (a | z) : Ans; //求 a[i] | x 的最大值
        }
        printf("%d\n", Ans); //输出结果
    }
    return 0;
}
```
## The end. Thanks.

~~（记得赞过~~

 

---

## 作者：CodeMao (赞：0)

### 简述题意

给定一个序列 $a$，每次将 $a_i$ 赋值为 $(a_i \ \text{or}\ z )$，将 $z$ 赋值为 $(a_i\ \text{and}\ z)$。问进行 $n$ 次这样的操作后 $a$ 序列中的最大值。

### 主要思路

不熟悉位运算 $\text{and}$、$\text{or}$ 的小盆友们可以参照如下表格（摘自[OI Wiki](https://oi-wiki.org/math/bit/#_1)）：

| 运算  | 运算符 | 数学符号表示 | 解释  |
| --- | --- | --- | --- |
| 与   | `&` | $\&$、$\text{and}$ | 只有两个对应位都为 $1$ 时才为 $1$ |
| 或   | `|` | $\vert$、$\text{or}$ | 只要两个对应位中有一个 $1$ 时就为 $1$ |

通过表格可以看出，$\text{or}$ 可以使一个数变大或者不变，$\text{and}$ 会使一个数变小或者不变，所以 $z$ 总是会变小，而 $a_i$ 总是会变大。所以当 $z$ 经过一次赋值时，之后 $a_i$ 的值就不可能在改变。这里可能不太好理解，我们就简单举个例子：

$a_i=9=(1001)_2,\ z=5=(101)_2$

$a_i=(a_i\ \text{or}\ z)=(1001)_2\ \text{or}\ (101)_2=(1101)_2=13$

$z=(a_i\ \text{and}\ z)=(1001)_2\ \text{and}\ (101)_2=(1)_2=1$

$a_i=(a_i\ \text{or}\ z)=(1101)_2\ \text{or}\ (1)_2=(1101)_2=13$

$z=(a_i\ \text{and}\ z)=(1101)_2\ \text{and}\ (1)_2=(1)_2=1$

所以对于每个 $a_i$ 最多进行一次操作。

所以 $ans=\max\limits _{i=1}^n {(a_i\ \text{or}\ z)}$。

代码很简单：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
#define inf 0x7fffffff
#define ll long long
using namespace std;
int t,n,z,x,ans;
inline void in(int &a){
    a=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
        a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
}
inline void op(int a){
    if(a>9) op(a/10);
    putchar(a%10+'0');
}      
inline void out(int a,bool f){
    op(a);
    if(f) puts("");else putchar(' ');
}    
inline int max(int a,int b){
    return a>b?a:b;
}
inline int min(int a,int b){
    return a<b?a:b;
}
int main(){
	//freopen("G:\\C\\in.in","r",stdin);
	//freopen("G:\\C\\out.out","w",stdout);
	in(t);
	while(t--){
		in(n),in(z);ans=0;
        for(int i=1;i<=n;++i){in(x);ans=max(ans,x|z);}
        out(ans,1);
    }
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

NIT，是镇上新来的！成千的人排队要 orz 他。为了让他的 orzers 高兴，NIT 决定让他们解决与 $\operatorname{or} z$ 有关的问题。你也能解决这个问题吗?

给你一个以 $1$ 为初始下标，包含 $n$ 个整数的数组 $a$ 和一个整数 $z$。你可以做以下操作的任意次（可能为零）:

- 选择正整数 $i$ 满足 $1\le i\le n$。然后将 $a_i$ 赋值为 $(a_i\operatorname{or} z)$，将 $z$ 赋值为 $(a_i \operatorname{and} z)$。

在任意（可能为零）次操作后，找出最大的 $a$ 中的最大值。

# 题目分析

仔细分析，我们发现 $\operatorname{or}$ 会使一个数不变小，$\operatorname{and}$ 会使一个数不变大。所以 $a_i$ 只会不断变大，$z$ 会不断变小。 $z$ 经过一次操作后，$z$ 的所有二进制位数在 $a_i$ 上同样会出现，故再次 $\operatorname{or}$ 操作不会使答案更优。

故一次即可。

# 代码

```cpp
inline void solve() {
	n = read(),x = read();
	int maxx = 0;
	for (register int i = 1;i <= n; ++ i) maxx = std::max(maxx,x | read());
	printf("%d\n",maxx);
}
```

---

## 作者：BetaCutS (赞：0)

我们可以选一个数 $\operatorname{or} z$，得出的最大值为 $\max_{i=1}^n\{a_i\operatorname{or} z\}$。

但进行许多次操作是不是更优呢？如果对一个数操作，因为 $z$ 变为 $z \operatorname{and} a_i$，$z$ 的二进制分解中原来没有的位之后也没有，原来有的位现在有可能有，有可能没有，而就是因为 $z$ 没有新的 $1$，$a_i$ 也不会变大，所以不可能更优。

可能这里不太好理解，举个栗子（第 $4$ 组样例）：

> 5 7

> 7 15 30 29 27

最优方案是对第三个数进行操作，$30 \operatorname{or} 7=31$，答案就是 $31$。

但对第 $1,2,4,5$ 个数操作并不会更优。

综上，答案为 $\max_{i=1}^n\{a_i\operatorname{or} z\}$。

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T,n,m,a[N];
signed main()
{
	T=read();
	while(T--)
	{
		n=read(),m=read();
		int ans=0;
		for(int i=1,x;i<=n;i++)
			x=read(),ans=max(ans,x|m);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：SoyTony (赞：0)

# 题意
给定一个数列 $a$ 和一个数字 $z$，你可以进行若干次操作，令数列中一个数与 $z$ 进行或运算，同时修改 $z$ 为该数与 $z$ 与运算的结果。

求出数列中能得到的最大值。
# 题解
抽象的讲，就是不断把 $z$ 作为一个媒介在数列中传递。不难发现，进行或运算的数列中的数，大小只增不减，而反之 $z$ 是只减不增。

于是对于二进制上第 $k$ 位是 $1$ 的 $z$，这一位在对数列上某个第 $k$ 位是 $0$ 的数产生贡献后，就变作 $0$，无法再产生贡献。所以这种传递是一次性的，所以求出 $\max_{i=1}^n\{a_i\operatorname{or} z\}$ 即可。


---

