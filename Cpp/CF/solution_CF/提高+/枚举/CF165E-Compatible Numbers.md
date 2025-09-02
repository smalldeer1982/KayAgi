# Compatible Numbers

## 题目描述

Two integers $ x $ and $ y $ are compatible, if the result of their bitwise "AND" equals zero, that is, $ a $ $ & $ $ b=0 $ . For example, numbers $ 90 $ $ (1011010_{2}) $ and $ 36 $ $ (100100_{2}) $ are compatible, as $ 1011010_{2} $ $ & $ $ 100100_{2}=0_{2} $ , and numbers $ 3 $ $ (11_{2}) $ and $ 6 $ $ (110_{2}) $ are not compatible, as $ 11_{2} $ $ & $ $ 110_{2}=10_{2} $ .

You are given an array of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to find the following for each array element: is this element compatible with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.

## 样例 #1

### 输入

```
2
90 36
```

### 输出

```
36 90```

## 样例 #2

### 输入

```
4
3 6 3 6
```

### 输出

```
-1 -1 -1 -1```

## 样例 #3

### 输入

```
5
10 6 9 8 2
```

### 输出

```
-1 8 2 2 8```

# 题解

## 作者：__Watcher (赞：33)

这题是一道高位前缀和的模板题

题目大意：对于每一个 $a_i$，询问是否有 $a_j$ 使得 $a_i\  \&\ a_j=0$。若有，输出任意一个 $a_j$，否则输出 $-1$。

分析：  

对于每一对 $a_i\  \&\ a_j=0$，若 $a_i$ 与 $a_j$ 的二进制表示中有同一位均为 $1$，那么 $a_i\  \&\ a_j$ 的这一位也会为 $1$。因此可以发现，$a_j$ 是 $a_i$ 按位取反后的子集。

实现：

预处理出数组 $a$ 的高维前缀和，每一次询问时先取反，再看取反后子集是否为空。高维前缀和只需存储子集中的任意一个数即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[1000005], f[1<<22];
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		scanf("%d", &a[i]);
		f[a[i]]=a[i];
	}
	for(int i=0;i<=21;i++) {
		for(int j=0;j<(1<<22);j++) {
			if((j&(1<<i))&&f[j^(1<<i)]) f[j]=f[j^(1<<i)];
		}
	}//高维前缀和
	for(int i=1;i<=n;i++) {
		int b=((1<<22)-1)^a[i];//取反操作
		printf("%d ", f[b]?f[b]:-1);
	}
}

```


---

## 作者：Prurite (赞：19)

### 这道题写代码不难，关键在于找到递推的方法（DP方程）

## 1. 思路

为了思路表述清晰，我就用“ *x* 的答案”表示在给定的序列中能与 *x* 相容的数。

我们可以想到，如果两个数 *x* 与 *y* 是相容的，那么从 *x* 的二进制里去掉了一些 *1* 的 *x'* 一定也能与 *y* 相容。比如，（二进制） *1011* 与 *0100* 相容，那 *1001* 一定也与 *0100* 相容。

也就是说，如果我们不知道 *a* 与哪个数相容，我们可以尝试把它添上一些 *1* 变成 *a'* ，如果 *a'* 的答案已知，那么 *a* 的答案就可以直接借用 *a'* 的答案。比如，我们不知道 *1001* 与哪个数相容，但是知道 *1011* 与 *0100* 相容，那么 *1001* 必定与 *0100* 相容。

**（可能会有点绕，可以多看几遍加深理解）**

## 2. 实现

具体实现到代码上， 用 *num\[ \]* 数组存储给定的序列，  *ans\[ i \]* 存储与i相容的一种答案。

首先读入序列，并把 *ans\[ \]* 数组全部初始化为 *-1* 。然后对于序列中的每个元素 *x* ,使 *ans\[ ~x&inf \]* = *x*。 *&inf*  是为了不超出限制。反向更新是因为 *~x&inf* 不一定在序列中，直接 *ans\[ x \]* = *~x&inf* 可能会WA（如果序列中根本没有 *~x&inf*）。但我们可以肯定，如果 *~x&inf* 在序列中，那么 *x* 一定与它相容。并且，即使它不在序列中，我们也可以借助它推出其他数的答案（下面会详细讲）

然后就是从大往小更新了，1层循环枚举 *m* ，如果 *ans\[ m \]* == *-1* （已经有解的就不用更新了，节省时间），进入2层循环，枚举 *m* 的哪一位是 0 :如果 *m* 从右往左数的第 *j* 位为 0 ，则尝试把这一位变成 1 ，通过 *ans\[ m|1<<j-1 \]* 来更新 *ans\[ m \]* ，如果更新成功就 break （还是为了节省时间）。如果循环完了还是没有值能使 *ans\[ m \]* 更新，它会保持无解的 *-1* 不变。

最后依次输出每一个数的答案。

## 3. 另一种理解

**事实上，你也可以把它理解为DP**：本来我们要求的是序列中的数（含1少的较小数）的答案，而我们把它转化为先求含1多（较大数）的答案，直到最后的边界转化为已知（序列中的数的取反）。

状态转移方程： *ans\[ i \] = ans\[ i|1<<j-1 \] ( ans\[ i|1<<j-1 \] != -1 )* 

初始化（边界）： *ans\[ ~x&inf \] = x* 。

## 4. 其他

这类二进制的题还有一个需要注意的地方，就是位运算的优先级，一不留神就会错，不确定的地方还是**把括号加上**，避免交了之后WA WA大哭。

## 5. 代码

建议看了以上思路之后**自己先尝试实现**，实在实现不了或实在理解不了思路再看代码。

**看了代码还不清楚可以发评论，我会尽力说明得更详细**

```cpp
#include <stdio.h>

const int INF = ( 1 << 22 ) - 1 ; //正无穷 
const int SIZE1 = 1 << 22 ; //每个数的大小的最大值 
const int SIZE2 = 1000000 ; //所有数的个数的最大值 
int ans[SIZE1];
int num[SIZE2];
int n; //数的个数 

inline void reset(); //重置变量 
inline void read(); //读入数据 
inline void solution(); //程序主体 
inline void output(); //输出结果 

int main()
{
	reset();
	read();
	solution();
	output();
	return 0;
} //疯狂的主程序 

inline void reset()
{
	for(int i=0;i<SIZE1;i++)
		ans[i]=-1;
	return;
}

inline void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
}

inline void solution()
{
	for(int i=1;i<=n;i++)
		ans[~num[i]&INF]=num[i]; 
//DP边界条件：能够与当前序列中的数相容的数的最大值
	for(int m=INF;m>0;m--) //枚举范围内的每一个数
		if(ans[m]==-1) //需要更新
			for(int j=1;j<=22;j++)
				if(!(m&1<<j-1)) //m的从右往左数第j位为0
					if(ans[m|1<<j-1]!=-1) //在这一位加上1后的数有答案
					{
						ans[m]=ans[m|1<<j-1];
						break;
					}
	return;
}

inline void output()
{
	for(int i=1;i<=n;i++)
		printf("%d ",ans[num[i]]);
	printf("\n");
	return;
}
```

[这份代码的提交记录](https://www.luogu.org/record/show?rid=5686789)

~~（呼，打了那么多字，累死我了）~~

---

## 作者：Mooncrying (赞：10)

#  CF165E Compatible Numbers 题解 && 高维前缀和

## 这是一篇对新手比较友好的题解。

### 题目大意

给出一个 $a$ 数列，对于数列中的每一个数 $a_i$，找到并输出数列中与之相容的数 $a_j$（即 $a_i \& a_j = 0$），无解输出 $-1$。

### 题意分析

- 我们首先会想，每个  $a_i$ 所对应的解集是什么。

	其实很好想，对该数**取反**（把该数二进制表示下的每一位的 $0$ 变成 $1$，$1$ 变成 $0$），取反之后的结果一定满足与该数相容。
    
    然后我们不难发现，取反之后的数在二进制表示下，任何一位或几位的 $1$ 变成 $0$，所得出的数仍满足与原数相容。
    
    举个栗子：
    
    一个数为 $(010010101) _ {2}$，该数取反后变为 $(101101010) _ {2}$，我们易证得这两个数相容。同样地，易证出 $(101101000) _ {2}$，$(001101010) _ {2}$，$(100001010) _ {2}$ 等数都与原数相容（可以在草稿纸上写写）。
    
- 怎样求解出任意的一个解呢？

	这里我们可以用一个类似维护**高维前缀和**的东西来维护其中的一个解。
    
    关于高维前缀和，以下是[我的一些见解](https://www.luogu.com.cn/blog/wwwjy4612code/gao-wei-qian-zhui-hu)，建议不懂的同学先看一看。
    
- 我们已知高维前缀和的求解代码为：
 	```cpp
	for(int i = 0; i < t; ++ i)
		for(int j = 0;j < n; ++ j) 
	       	if( (1 << i) & j) sum[j] += sum[j ^ (1 << i)];
 	```
	而这道题让我们求的是任意一个解，那我们可以用赋值刷新解的方法存下任意的一个解。

	代码这样写：
	```cpp
   memset(ans, -1, sizeof(ans) );
	for(int i = 1; i <= n; ++ i)
		 read(a[i]), ans[a[i]] = a[i];//基本的赋值
         
	for(int i = 0; i < 22; ++ i)
		for(int j = 0; j < (1 << 22); ++ j)
			if(j & (1 << i) && ans[j ^ (1 << i)] != -1) ans[j] = ans[j ^ (1 << i)];//存在就覆盖
	```

	这样我们就求出了取值范围内所有数的任一解（当然无解还是 $-1$）。

- 接下来的事情就简单了，我们只需要对每一个 $a_i$ 进行取反，然后判断取反之后的数所对应的 $ans$ 数组是否有实际数字（即是否不为 $-1$）即可。

	这里我们要注意在有符号整数类型中对一个数进行二进制取反时所得的数一定不是正确的取反结果（机房大佬说我看不起读者的知识水平 QaQ），因为题目给定的取值范围是大约 $2 ^ {22}$ 的规模，于是我们可以 $a_i \oplus (2 ^ {22}  - 1)$ （二进制表示下就是 $22$ 个 $1$）（就是异或操作），这样的结果相当于对该数取反。
    
- 于是写出代码后，我们就能愉快地切掉~~这道大水题~~啦。
 
 下面是你们最喜欢的代码：
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
const int M = (1 << 22) + 10;
int n, a[N], ans[M];
template <typename T> void read(T &x)
{
		int f = 1; x = 0; char ch = getchar();
		while(ch > '9' || ch < '0') {if(ch == '-') f = -1;ch = getchar(); }
		while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
		x *= f;
}
template <typename T> void write(T x, char ch)
{
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x / 10, 0);
		putchar(x % 10 + '0');
		if(ch == ' ') putchar(' ');
		if(ch == '\n') putchar('\n');
}
int main()
{
		read(n);
		memset(ans, -1, sizeof(ans) );
		for(int i = 1; i <= n; ++ i)
			 read(a[i]), ans[a[i]] = a[i];
		for(int i = 0; i < 22; ++ i)
			for(int j = 0; j < (1 << 22); ++ j)
				if(j & (1 << i) && ans[j ^ (1 << i)] != -1) ans[j] = ans[j ^ (1 << i)];
		for(int i = 1; i <= n; ++ i)
			write(ans[a[i] ^ ( (1 << 22) - 1)], ' ');
		return 0;//完结撒花
} 
```

---

## 作者：白鲟 (赞：9)

## 题意简述
给出数列 $\{a_i\}$，对于每个 $a_i$，求任意一个满足 $a_i \operatorname{and} a_j=0$ 的 $a_j$。

## 题目分析
容易发现，由于 $a_i \operatorname{and} (\operatorname{not} a_i)=0$，我们所要求的 $a_j$ 事实上满足 $a_j \operatorname{and} (\operatorname{not} a_i)=a_j$。根据数据规模，$(2^{22}-1)\operatorname{xor} a_i$ 与 $\operatorname{not} a_i$ 是等效的，意即 $a_j \operatorname{and} [(2^{22}-1)\operatorname{xor} a_i]=a_j$。对于 $[1,2^{22}-1]$ 中的每一个数 $p$，设我们求出的满足 $a_j \operatorname{and} p=a_j$ 的 $a_j$ 为 $match_p$，对于每个询问我们只需要简单地查询 $match_{a_i \operatorname{xor} (2^{22}-1)}$ 的值即可。  

问题转化为了求解 $match_p$ 的值。首先可以明确 $match_{a_i}=a_i$。之后我们发现，若将 $a_i$ 二进制表示中任意一个 $0$ 改为 $1$ 得到 $x$，$x$ 将满足 $a_i \operatorname{and} x=a_i$，则 $match_x=a_i$。显然 $match_x$ 可用于再次更新。这样就能够求出所有 $match_p$。

## 代码
```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxa=(1<<22)-1;
int n,a[1000001],ans[1<<22];
int main()
{
	memset(ans,-1,sizeof ans);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		ans[a[i]]=a[i];
	}
	for(int i=1;i<=maxa;++i)
		for(int j=1;j<=22;++j)
			if(ans[i]!=-1&&(i|(1<<(j-1)))!=i&&(i|(1<<(j-1)))<=maxa)
				ans[i|(1<<(j-1))]=ans[i];
	for(int i=1;i<=n;++i)
		printf("%d ",ans[maxa^a[i]]);
	return 0;
}
```

---

## 作者：chenxia25 (赞：9)

这他妈的就属于超级无敌大水题了吧。。。。。

就 $x\operatorname{and}y=0$ 当且仅当 $y$ 包含于 $x$ 的补。那就看 $x$ 的补的子集里面有没有东西呗……这个甚至不需要高维前缀和，一个状压 DP 就搞定，转移的时候枚举缺失的位。为什么能这样呢？因为操作重复没关系，不像加法。

---

## 作者：喵仔牛奶 (赞：3)

下文用 $\operatorname{bitand}$ 表示按位与。

令 $c$ 为 $b$ 的补集，由 $a\operatorname{bitand}b=0$ 可得 $a\in c$，由按位与的定义易证。

因为输出任意一个数即可，所以我们可以看成求满足 $a\in c$ 的最大数，即 $\max\limits_{a\in c}\{a\}$，这个使用[高维前缀和](https://oi-wiki.org/basic/prefix-sum/)维护即可。

时间复杂度 $\mathcal{O}(n+a\log a)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1 << 22, mask = (1 << 22) - 1;
int n, a[N], sum[N];
int main() {
	memset(sum, -1, sizeof sum);
	cin >> n;
	for (int i = 1; i <= n; i ++)
		cin >> a[i], sum[a[i]] = a[i];
	for (int i = 0; i < 22; i ++)
		for (int j = 0; j < 1 << 22; j ++)
			if (j & 1 << i) sum[j] = max(sum[j], sum[j ^ 1 << i]);
	for (int i = 1; i <= n; i ++)
		cout << sum[~a[i] & mask] << ' ';
	return 0;
}
```


---

## 作者：FiraCode (赞：3)

#### 题解思路：
他让我们找到一个 $a_i \& a_j = 0$。
那么对于 $a_i = 1$ 那么 $a_j = 0$。
若 $a_i = 0$ 那么 $a_j = 0$ 或者 $a_j = 1$。
那么 $a_j$ 必须是 ~$a_i$ 的子集，其中 ~ 表示取反。
那么我们就是要求 $a_j \& i = a_j$ 并且 $j$ 最小。
那么我们令 $f_{a_j} = j$。
然后我们找到一个 $g_i = \min_{i \& j = j}\{f_j\}$。
那么这个就很像字集和问题，只要把字集和换成求最小值就可以了。
#### AC CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = (1 << 22) + 10;
const int M = 22;
int n;
int f[N], a[N];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < (1 << M); ++i)
		f[i] = n + 1;
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		a[i] = x;
		f[x] = min(f[x], i);
	}
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < (1 << M); ++j) {
			if (j & (1 << i))
				f[j] = min(f[j], f[j - (1 << i)]);
		}
	for (int i = 1; i <= n; ++i) {
		int x = (1 << M) - 1 - a[i];
		printf("%d%c", (f[x] > n) ? -1 : a[f[x]], " \n"[i == n]);
	}
	return 0;
}
```

---

## 作者：zyc____ (赞：2)

## CF165E Compatible Numbers

### 进入正题

### 题意

给定一组数，判断里面的元素与其他元素与其他是否相容，(即元素i与其他元素的亦或值都等于0，则输出-1，否则输出与其他任意元素的亦或值的值)


------------

### 思路

考虑dp。
我们发现对于二进制10101来说，它的合法结果一定是10001、00101、10100的合法结果。也就是说对于一个数i来讲，我们去掉i的二进制中任意一个1得到的数k，i的合法结果一定是k的合法结果。

最大的数为(1<<22)，记 N= 1<<22 - 1。
设置dp[i]为i的一个集合，也就是说对于集合中任意一个元素T，总会满足T & (N ^ i) == 0。题目只要求一个解，我们只记录一个就可以了。
对于a[i]的结果我们要找到一个T使得 T & (N ^ N ^ a[i]) == 0，显然结果为dp[N ^ a[i]]。

------------

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int inf=(1<<22)-1;
int m,n,a[10000005],b[inf],i,j;
int main()
{
    cin>>m;
    for(i=1;i<=m;++i)
    {
        cin>>a[i];
    	b[inf^a[i]]=a[i];
    }
    for(i=inf;i>=0;--i) 
    {
        if(!b[i])
        {
            for(j=0;j<22;++j)
                if(b[i|(1<<j)])
                    b[i]=b[i|(1<<j)];
        }
    }
    for(i=1;i<=m;++i)
    {
        if(i-1!=0) cout<<" ";
        if(b[a[i]]) cout<<b[a[i]]<<endl;
        else cout<<"-1";
    }
    return 0;
}
```


------------

然鹅，这个代码并不能AC（第12个点会T），我这只蒟蒻亲身尝试发现。。。只要把cin、cout改成scanf、printf就OK了，改成快读我也不反对~~懒得改~~

### 上AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int inf=(1<<22)-1;
int m,n,a[10000005],f[inf],i,j;
int main()
{
    scanf("%d",&m);
    for(i=1;i<=m;++i)
    {
        scanf("%d",&a[i]);
    	f[inf^a[i]]=a[i];
    }
    for(i=inf;i>=0;--i)
    {
        if(!f[i])
        {
            for(j=0;j<22;++j)
                if(f[i|(1<<j)])
                    f[i]=f[i|(1<<j)];
        }
    }
    for(i=1;i<=m;++i)
    {
        if(i-1!=0) printf(" ");
        if(f[a[i]]) printf("%d\n",f[a[i]]);
        else printf("-1");
    }
    return 0;
}
```

这个程序速度是真的慢，不过我也是实在没有办法了，大佬可以在评论区留言

---

## 作者：Hisaishi_Kanade (赞：1)

约定：

+ $\&$ 表示按位与。
+ $\mid$ 表示按位或。
+ $\sim$ 表示按位取反，和 C 语言的符号一样。

题意就是对于每一个 $a_i$，求任意一个可能的 $a_j$ 使得 $a_i\ \&\ a_j=0$。

直接按位与似乎不是很好做。既然 $a_i\ \&\ a_j=0$，那么必然会有 $(\sim a_i)\ \&\ a_j=a_j$。

证明也很显然：对于 $a_j$ 的某一位，如果是 $0$ 则显然在这一位成立，取反之后再按位与这一位得到的还是 $0$；如果是 $1$ 那么 $a_i$ 这一位必然是 $0$，取反之后这一位必然是 $1$，按位与之后这一位必然还是 $1$。

反之依然成立，证明类似。

接下来问题转化成：找到一个 $a_j$ 使得 $(\sim a_i)\ \&\ a_j=a_j$。

设 $f_x$ 表示 $\sim a_i=x$ 时，一个合法的 $a_k$。

容易想到，$a_j\ \&\ m=a_j$，$a_j\ \&\ (m\mid p)=a_j$。

那么转移就很自然了，当 $y\ \&\ x=y$ 且 $f_y$ 有解时，$f_x$ 可以从 $f_y$ 转移。

这样就可以实现了。

$\log_2 (4\times10^6)<22$，所以 $f$ 存到 $2^{22}$ 即可。

```cpp
#include <iostream>
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
int n,cnt,i,j;
int a[1000005],b[1000005],f[1<<22|5];
int main() {
	cin>>n;
	rep(i,1,n)
	{
		cin>>a[i];
		f[a[i]]=a[i];//初始化，a[i] & a[i]=a[i]
	}
	cnt=(1<<22)-1;
	rep(i,0,21)
		rep(j,0,cnt)
			if((j&(1<<i)) && f[j^(1<<i)])//j 从 j^(1<<i) 转移
				f[j]=f[j^(1<<i)];
	rep(i,1,n)
	{
		b[i]=cnt^a[i];//也就是取反。
		cout<<(f[b[i]]?f[b[i]]:-1)<<' ';
	}
	return 0;
}


```

---

## 作者：KSToki (赞：1)

题目大意很清楚了，在一个长度为$n$的序列$a$中，对于每个$a_i$找出一个$a_j$使得$a_i$&$a_j=0$，如果找不到则输出$-1$。

题解里的大佬们的解法都太强了，这里分享一下蒟蒻的思路。

$f[i]$表示集合$i$的一个子集（题目要求随便一个即可），如果没有则为$0$（当然全部初始值为$-1$输出时就不用特判了）。我们很容易想到暴力枚举子集来更新：
```cpp
for(int S=0;S<Max;++S)
	for(int i=S;i;i=(i-1)&S)
		if(f[i])
			ans[S]=i;
```
你会发现你TLE了，很显然某些$f[i]=0$被重复查了多次，都是没有用的。

这里的优化是对于每个状态只搜少一个$1$的状态，因为这些状态都在该状态前算出，每种状态仅被算了一遍。

当然可以枚举位数实现，题解中使用lowbit实现~~会快一些？~~

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000001],f[4194304];（4194304=1<<22）
inline int read()
{
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
inline int lowbit(int x)
{
	return x&(-x);
}
int main()
{
	n=read();
	for(register int i=1;i<=n;++i)
		a[i]=read(),f[a[i]]=a[i];//初始化：f[a[i]]肯定有子集a[i]
	int S=(1<<22)-1;
	for(register int i=0;i<=S;++i)
		for(register int j=i;j;j-=lowbit(j))
		    if(f[i^lowbit(j)])
		    {
		    	f[i]=f[i^lowbit(j)];
		    	break;
		    }//这就是枚举啦
	for(register int i=1;i<=n;++i)
	    printf("%d ",f[S^a[i]]?f[S^a[i]]:-1);
	return 0;
}
```
完！

---

## 作者：ZillionX (赞：1)

# Description

给定序列 $a$，对于每个 $a_i$，找到序列中满足 $a_i \& a_j=0$ 的 $a_j$，若没有则输出 $-1$。

$n \le 10^6,a_i \le 4 \times 10^6$。

# Solution

设 $a_i$ 的补集为 $b_i$，不难看出 $a_i \& a_j=0$ 即 $a_i | b_j =b_j$。

因此不妨设 $f_i$ 为满足 $j | i=i$ 的 $j$。

初始化的时候直接将 $f_{a_i}$ 赋值为 $a_i$，用 Or 的 FWT 转移就好了。

最后对应 $a_i$ 的结果即为 $f_{b_i}$。

至此我们就在 $\mathcal O(a \log a)$ 的复杂度下完成了本题。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5,S=(1<<22)+5;
int n,a[N],f[S];
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),f[a[i]]=a[i];
	for (int i=2,j=1;i<=(1<<22);i<<=1,j<<=1)
		for (int k=0;k<(1<<22);k+=i)
			for (int l=0;l<j;l++)
				if (f[k+l]) f[j+k+l]=f[k+l];
	for (int i=1;i<=n;i++)
		if (!f[((1<<22)-1)^a[i]]) printf("-1 ");
		else printf("%d ",f[((1<<22)-1)^a[i]]);
	return 0;
}
```


---

## 作者：wzy2021 (赞：0)

分析：

若 $s \& t = 0$，则肯定每一位是独立的，考虑第 $i$ 位：

1. $s_i = 0$，则 $t_i$ 可以为 $0$ 或 $1$；

2. $s_i = 1$，则 $t_i$ 必须为 $0$。

考虑把 $s_i$ 的 $0,1$ 对换：

1. $s_i = 1$，则 $t_i$ 可以为 $0$ 或 $1$；

2. $s_i = 0$，则 $t_i$ 必须为 $0$。

这可以发现，$t$ 是 $s$ 取反后的子集，故

在 $a_i$ 取反的子集中，看看有没有在 $a$ 数组里的即可。

做法：对于每个 $a_i$，把 $f[a_i] = i$，则

对于计算 $S$，在 $S$ 的子集中取最小值即可（一开始设为无穷大）。

注：若 $a_i$ 重复，取最小的 $i$。

代码：

~~~cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e6 + 10, M = 22;

int f[1 << M], a[N];

int main() {
	int n; scanf ("%d", &n);
	for (int i = 0; i < (1 << M); ++i) {
		f[i] = n + 1;
	}
	for (int i = 1; i <= n; ++i) {
		scanf ("%d", &a[i]);
		f[a[i]] = min (f[a[i]], i);
	}
	for (int i = 0; i < M; ++i) {
    	for (int j = 0; j < (1 << M); ++j) {
    		if ((1 << i) & j) f[j] = min (f[j], f[j - (1 << i)]);
		}
	} // 高维前缀和求子集
	for (int i = 1; i <= n; ++i) {
		int x = (1 << M) - 1 - a[i]; // x 为 a[i] 取反后的结果
		printf ("%d ", (f[x] == n + 1) ? -1 : a[f[x]]);
	}
	return 0;
}
~~~

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF165E](https://www.luogu.com.cn/problem/CF165E)

* **【解题思路】**

首先 $a_i\operatorname{and}a_j=0$ 不好处理，那么我们就设 $b_i=\operatorname{not}a_i$，问题转化为 $a_i\operatorname{and}b_j=a_i$。显然当 $b_j$ 的二进制位包含 $a_i$ 的二进制位时式子成立。于是我们可以直接状压 DP，处理出当 $b_j$ 取 $1\sim k$ （其中 $k=4
\times10^6$ 为值域）中每个数对应的答案。

时间复杂度 $\Theta(k\log k+n)$。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

constexpr int full=(1<<22)-1;
array<int,1000000> nums;
array<int,full> DP_arr;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt;
	cin>>cnt;
	for(int i=0;i<cnt;i++)
		cin>>nums[i],DP_arr[nums[i]]=nums[i];
	for(int i=1;i<=full;i++)
		if(!DP_arr[i])
			for(int j=0;j<22;j++)
				if((i&(1<<j))&&DP_arr[i-(1<<j)])
				{
					DP_arr[i]=DP_arr[i-(1<<j)];
					break;
				}
	for(int i=0;i<cnt;i++)
		cout<<(DP_arr[nums[i]^full]?DP_arr[full-nums[i]]:-1)<<' ';
	return 0;
}

```

---

## 作者：XL4453 (赞：0)

### 解题思路：

设 $f_i$ 表示数字 $i$ 的一种可行答案。

可以发现，对于任意在 $i$ 的基础上去掉某一些位的 $1$ 之后的数的答案也可以是 $f_i$，因为去掉某一些位置上的 $1$ 后所有的 $0$  位都没有变成 $1$，也就不可能有不符合的现象出现。

初始时，$f_{111...1_{(2)} xor\  a_i}$ 一定有一解为 $a_i$，那么直接由此向外拓展即可。

---
### 代码：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=(1<<22)-1;
int n,a[1000006],f[MAXN+1];
int main(){
	memset(f,-1,sizeof(f));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		f[MAXN^a[i]]=a[i];
	}
	
	for(int i=MAXN;i>=1;i--)
	if(f[i]!=-1)
	for(int j=0;j<=21;j++)
	if((i&(1<<j)))
	f[i-(1<<j)]=f[i];
	
	for(int i=1;i<=n;i++)
	printf("%d ",f[a[i]]);
	return 0;
}
```



---

## 作者：漠寒 (赞：0)

## 分析

对于 $a\&b=0$，我们发现，将 $b$ 与 $2^{22}-1$ 异或的值，它与 $a$ 取并的值仍为 $a$，于是我们发现我们所求的就是 $a_i\oplus2^{22}-1\&a_j=a_j$，这个思路就显而易见的是类似于高维前缀和。

我们发现对于如果 $i$ 的第 $j$ 位为0，那么和它取与等于它的数，和它在这一位改为1的数取与的结果也为那个数本身。

因此转移方程就显然了。

最后对于每个数的答案，就以第一段发现的性质，取 $dp[a_i\oplus2^{22}-1]$ 即可。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,f[5000001],k,a[1000005];
inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int main()
{
	read(n);
	k=log2(4000000)+1;
	for(int i=1;i<=n;i++){
		read(a[i]);
		f[a[i]]=a[i];
	}
	for(int j=0;j<k;j++){
		for(int i=1;i<(1<<k);i++){
			if(!f[i])continue;
			if(!(i&(1<<j)))f[i^(1<<j)]=f[i];
		}
	}
	k=(1<<k)-1;
	for(int i=1;i<=n;i++){
		if(!f[a[i]^k])puts("-1");
		else printf("%d\n",f[a[i]^k]);
	}
	return 0;
}
```


---

