# 「LAOI-4」Mex Tower (Hard ver.)

## 题目背景

**本题与 Easy Version 的区别为本题需判断方案的合法性。**

**保证本题所有的测试点时空限制均为 std 的 $2.5$ 倍及以上**。


## 题目描述


定义 $\operatorname{mex}(x, y)$ 表示在集合 $\{x, y\}$ 中最小的未出现的 **自然数**。例如，$\operatorname{mex}(1, 5) = 0$，$\operatorname{mex}(3, 0) = 1$。

继而，我们定义对自然数序列 $a_1\dots a_n$ 的一次操作，是将序列 $a$ 替换为 **长度为 $\bm{n - 1}$ 的** 序列 $a'_1\dots a'_{n-1}$，其中 $a'_i = \operatorname{mex}(a_i, a_{i+1})$。

一个长度为 $n$ 的整数序列 $a_1\dots a_n$，满足 $0 \leq a_i \leq 10^9$；然后依次对它进行 $n - 1$ 次操作。显然最终序列 $a$ 只会剩下一个数，定义这最终一个数的值成为 **该序列的价值**，记为 $f(a)$。

请问对于给定的 $n$ 和 $a$ 序列，是否对于所有长度为 $n$ 的自然数序列 $b$，$f(a)\ge f(b)$。


## 说明/提示

## 提示

### 样例解释

对于 $n = 2$，$f(a)=2$。可以证明，对于所有长度为 $2$ 的 $b$ 序列满足 $f(b)\le 2$。

对于 $n = 3$，$f(a)=0$，存在序列 $b=[114,514,1919]$，$f(b)=1>0$。

### 数据规模与约定

**「本题采用捆绑测试」**

| $\text{Subtask}$ | $\sum n \le$|  特殊性质  | 总分值 |
| :--------------: | :-----: |:-----: | :--------: |
|       $1$        |  $10^3$ | 无| $10$ |
$2$        | $5\cdot 10^5$  | $\text{A}$ | $5$ |
|       $3$        | $5\cdot 10^5$  | $\text{B}$ | $10$ |
|       $4$        | $5\cdot 10^5$ | $a_i< 2$ | $15$ |
|       $5$        | $10^6$ | 无 | $20$ |
|       $6$        | $3\cdot 10^6$ |     无     | $40$ |

特殊性质 $\text{A}$：保证 $a_i=i$。

特殊性质 $\text{B}$：保证 $a_i=i\bmod 3$。

对于所有数据，保证 $1 \leq T \leq 10^4$，$n > 1$，$\sum n \leq 3\cdot 10^6$。

## 样例 #1

### 输入

```
2
2
0 1
3
1 0 2```

### 输出

```
Yes
No```

# 题解

## 作者：Breath_of_the_Wild (赞：6)

洛谷赛时的时候没做出来，没想到今天校内模拟赛就推出来了，特此写一篇题解。

首先我们注意到，$\operatorname{mex}\{a,b\}$ 一定为 $0$、$1$ 或 $2$，因为答案最多的情况就是 $a=0,b=1$，答案为 $2$。

于是序列算出来的结果不会超过 $2$。于是题面就变成了：给一个序列，按照题目要求模拟，最后结果是否为 $2$。只有这样所有的 $f(b)$ 才会一定 $\le f(a)$。

但是直接模拟会超时。于是考虑：什么样的序列操作完毕后为 $2$？可以从还剩一个数为 $2$ 的情况，倒推回还剩 $n$ 个数的情况回去。

我先举几个例子。倒推 $1$ 行，显然为了使结果为 $2$，这一行应该为 $0$ 和 $1$（注意翻转过去也可以）。再往前推一行，由于中间位置和两个数操作结果又有 $0$ 又有 $1$，故中间应该填一个 $\ge 2$ 的数。于是左边应填 $\ge 1$ 的数，右边应填 $0$。

以此类推，剩下的可以参考我画的这张图：

![](https://sy.hhwdd.com/RequireFile.do?fid=FOmf9Mg6)

注意到当 $n$ 很大时，用到的只有中间的几个数，因为其他的位置可以随便填。

根据图片，进行分情况讨论：如果 $n$ 是奇数，只需要判断 $a_{\frac{n+1}{2}}\ge 2$ 且 $a_{\frac{n+1}{2}-1}\ge 1$ 且 $a_{\frac{n+1}{2}+1}=0$，或者 $a_{\frac{n+1}{2}}\ge 2$ 且 $a_{\frac{n+1}{2}-1}=0$ 且 $a_{\frac{n+1}{2}+1}\ge 1$ 即可（第二种情况是翻转，也可以）。

如果 $n$ 是偶数，只需要判断 $a_{\frac{n}{2}}=0$ 且 $a_{\frac{n}{2}+1}=1$ 且 $a_{\frac{n}{2}+1}=1$ 且 $a_{\frac{n}{2}+2}\ge 1$，或者翻转过来 $a_{\frac{n}{2}+1}=0$ 且 $a_{\frac{n}{2}}=1$ 且 $a_{\frac{n}{2}-1}\ge 1$ 即可。

另外，注意特判 $n=2$，因为 $n=2$ 时 $a$ 满足条件的只可能为 $\{0,1\}$ 或 $\{1,0\}$。

---

## 作者：Mr_Az (赞：1)

### [T3「LAOI-4」Mex Tower (Hard ver.)](https://www.luogu.com.cn/problem/P10370)

#### Solution：猜性质

打表观察（真的是）得：

1. 对于 $n$ 为奇数时：
    1. 中间项必为 2。
    2. 中间项左右两侧必为 $[1,0]$ 或 $[2,0]$ 或 $[0,1]$ 或 $[0,2]$。
2. 对于 $n$ 为偶数时，中间两项为 $[0,1]$ 或 $[1,0]$。

**细节**

1. 原始数组先处理一遍成只有 $0,1,2$ 的数组。
2. $n$ 为奇数时，特判 $n=1$ 时情况，此时只需要 $a_1=2$ 即可。

证明：

其实在手模的时候就可以看出不超过 4 次操作后，继续操作两次相当于减去一对头尾，最后剩下的只有中间。所以中间只要构造为 $[0,2,1]$ 或者 $[0,1]$ 这样的样子。

#### Code: 

```cpp
signed main(){
    read(T);
    while(T--){
        read(n);
        for(rint i=1;i<=n;i++) read(a[i]);
        n--;
        for(rint i=1;i<=n;i++){
            if(a[i]!=0&&a[i+1]!=0) a[i]=0;
            else if(a[i]!=1&&a[i+1]!=1) a[i]=1;
            else a[i]=2;
        }//细节1
        bool f=0;
        if(n%2==1){
            int t=(n+1)/2;
            if(t==1&&a[t]==2) f=1;//细节2
            else if(a[t]==2&&a[t-1]!=a[t+1]&&(a[t-1]==0||a[t+1]==0)) f=1;
        }
        else{
            if(a[n/2]+a[n/2+1]==1) f=1;
        }
    	puts(f?"Yes":"No");
    }
    return 0;
}
```

打表代码：

```cpp
int n;
inline int work(vector<int> a){
	for(rint k=1;k<a.size();k++){
		for(rint i=1;i<a.size();i++){
			if(a[i-1]!=0&&a[i]!=0) a[i-1]=0;
			else if(a[i-1]!=1&&a[i]!=1) a[i-1]=1;
			else a[i-1]=2;
		}
	}
	return a[0];
}
inline void dfs(int p,vector<int> a){
	if(p>n){
		if(work(a)==2){for(auto x:a) cout<<x<<" ";puts("");}
		return ;
	}
	a.push_back(0);
	dfs(p+1,a);
	a.pop_back();a.push_back(1);
	dfs(p+1,a);
	a.pop_back();a.push_back(2);
	dfs(p+1,a);
	return ; 
} 

signed main(){
	cin>>n;
	dfs(1,{});
    return 0;
}

```

---

## 作者：SafariMo (赞：1)

由 Easy Ver 可知，$\max_af(a)=2$。

也就是说，原问题就是在问 $f(a)$ 是否 $=2$。

易证在不超过 $4$ 次操作后每两次操作相当于掐头去尾，后面其实随便做就行了，有点轻微卡常，结论可简单证明。

验题人做法：<https://www.luogu.com/paste/awi09oom>

---

## 作者：Claire0918 (赞：1)

本文性质推导部分可以用于 [Easy ver.](https://www.luogu.com.cn/problem/P10369)。

我们注意到
$$
(\forall x, y \in \mathbb{N})(\operatorname{mex}(x, y) \in \{0, 1, 2\})
$$
且 $\operatorname{mex}$ 具有交换律。

又有对应关系
$$
\operatorname{mex}(x, y) = 
\begin{cases}
2 & x = 0, y = 1\\
1 & x = 0,y \neq 1\\
0 & x \neq 0, y \neq 0
\end{cases}
$$

为保证得到的序列可以继续倒推，即该序列可能是某一个序列通过一次变换得到的序列，我们要求序列中所有数的取值范围为 $\{0, 1, 2\}$ 而不是 $\mathbb{N}$。

而欲要使得最后的数最大，即序列为 $[2]$。

读者易证，翻转序列不会影响最终结果，我们只考虑其中一个。

再倒推，即得到 $[0, 1]$。

我们设上一级的序列为 $[a, b, c]$。

显而易见，$b \neq 0$，所以 $c = 0$，又有 $b \neq 1$，所以 $b = 2$，而且有 $a \neq 0$。我们简记为 $[\neq 0, 2, 0]$。

再设有上一级的 $[a, b, c, d]$。

又十分显然地，$b = 0$，所以 $a$ 任意取值，$c = 1$，又 $d \neq 0$。那么结果简记为 $[\text{all}, 0, 1, \neq 0]$。

再设有上一级的 $[a, b, c, d, e]$。

显然有 $b \neq 0, c \neq 0 \wedge c \neq 1$，所以有 $a$ 任意取值，$c = 2, d = 0$，所以 $e$ 任意取值。简记为 $[\text{all}, \neq 0, 2, 0, \text{all}]$。

再设有上一级的 $[a, b, c, d, e, f]$。

显然有 $d \neq 0$，所以 $c = 0, d = 1$，所以 $a, b, f$ 任意取值，简记为 $[\text{all}, \text{all}, 0, 1, \neq 0, \text{all}]$。

我们将上述结果列在一起
$$
[2]\\
[0, 1]\\
[\neq 0, 2, 0]\\
[\text{all}, 0, 1, \neq 0]\\
[\text{all}, \neq 0, 2, 0, \text{all}]\\
[\text{all}, \text{all}, 0, 1, \neq 0, \text{all}]
$$

我们不难发现，从 $n \geq 5$ 开始，结果总是在 $n - 2$ 的结果两侧各加上一个 $[\text{all}]$。我们只需要判断不是 $\text{all}$ 的部分即可。注意 $n = 4$ 与 $n = 2$ 相比出现了新的元素，所以 $n = 2$ 特判。

但是，这样并不能适用于任何情况。上文中我们令序列中每一个元素都属于 $\{0, 1, 2\}$，但实际上给定的 $a$ 未必满足条件。不难想到，我们可以先手动变换一次，从而得到一个满足条件的长为 $n - 1$ 的数列 $a'$。易证 $f(a) = f(a')$，所以我们可以直接判断是否有 $f(a') = 2$。

需要注意新序列长度为 $n - 1$，所以要特判 $n - 1 = 1$。

Code: 
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 3e6 + 10;

int t, n;
int a[maxn];

inline int mex(int x, int y){
    return x + y == 1 ? 2 : x && y ? 0 : 1;
}

int main(){
    scanf("%d", &t);
    while (t--){
        scanf("%d", &n);
        for (int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; i++){
            a[i] = mex(a[i], a[i + 1]);
        }
        n--;
        if (n == 1){
            printf(a[1] == 2 ? "Yes\n" : "No\n");
            continue;
        }
        if (n == 2){
            printf(a[1] + a[2] == 1 ? "Yes\n" : "No\n");
            continue;
        }
        if (n & 1){
            printf(a[(n >> 1) + 1] == 2 && bool(a[n >> 1]) + bool(a[(n >> 1) + 2]) == 1 ? "Yes" : "No");
        }else{
            printf(!a[n >> 1] && a[(n >> 1) + 1] == 1 && a[(n >> 1) + 2] || a[(n >> 1) - 1] && a[n >> 1] == 1 && !a[(n >> 1) + 1] ? "Yes" : "No");
        }
        putchar('\n');
    }

return 0;
}
```

附[失败记录](https://www.luogu.com.cn/record/list?pid=P10370&user=660816)。

---

## 作者：ni_ju_ge (赞：0)

有一定难度的思维题。

[题目传送门](https://www.luogu.com.cn/problem/P10370)/[安利博客](https://www.cnblogs.com/ni-ju-ge/p/18605946)
## 思路
首先，$\operatorname{mex}(x,y)$ 的结果一定为 $0,1,2$，因为只有两个数，所以结果最多为 $2$（$x=1,y=0$ 或 $x=0,y=1$ 时）。因此，可以将问题转化为最后的数是否为 $2$。

考虑倒推，当 $n=1$ 时，显然只能为 $2$；要从 $n=2$ 的情况变为 $n=1$ 的情况，那么这两个数应该为 $0$ 和 $1$；当 $n=3$ 时，$a_1\ge 1,a_2\ge 2,a_3=0$（当然反过来也可以）。

多推几个 $n$，发现最后的结果是否为 $2$ 只与中间的三个数有关，并且有如下规律：

 - 设 $mid=\left\lfloor\dfrac{n+1}{2}\right\rfloor$。
 - 若 $n\bmod 2=1$，则当 $a_{mid-1}\ge1,a_{mid}\ge 2,a_{mid+1}=0$ 或 $a_{mid+1}\ge1,a_{mid}\ge 2,a_{mid-1}=0$ 时，最后的数字为 $2$。
 - 若 $n\bmod 2=0$，则当 $a_{mid}=0,a_{mid+1}=1,a_{mid+2}\ge 1$ 或 $a_{mid+1}=0,a_{mid}=1,a_{mid-1}\ge 1$ 时，最后的数字为 $2$。

注意特判 $n=2$ 的情况。
## 核心代码
```cpp
mid=(n+1)/2;
if(n==2) {
	if((a[1]==1&&a[2]==0)||(a[1]==0&&a[2]==1))cout<<"Yes";
	else cout<<"No";
} else {
	if(n%2) {
		if((a[mid-1]>=1&&a[mid]>=2&&a[mid+1]==0)||(a[mid+1]>=1&&a[mid]>=2&&a[mid-1]==0))cout<<"Yes";
		else cout<<"No";
	} else {
		if((a[mid]==0&&a[mid+1]==1&&a[mid+2]>=1)||(a[mid+1]==0&&a[mid]==1&&a[mid-1]>=1))cout<<"Yes";
		else cout<<"No";
	}
}
```

---

## 作者：naught (赞：0)

# 「LAOI-4」Mex Tower (Hard ver.)

## 题意

给定一个长度为 $ n $ 的序列 $ a $，求序列的 $ \operatorname{Mex} $ 值是否大于等于其他所有长度为 $ n $ 的自然数序列的 $ \operatorname{Mex} $ 值。

## Solution

不难发现，两个数或一个序列的 $ \operatorname{Mex} $ 一定是 $ 0 $，$ 1 $ 或 $ 2 $。

而要使序列 $ \operatorname{Mex} $ 大于等于其他所有等长序列 $ \operatorname{Mex} $ 值，显然得使序列 $ a $ 本身 $ \operatorname{Mex} $为 $ 2 $，故原问题被转化为“判断原序列 $\operatorname{Mex}$ 值是否为 $ 2 $”。

暴力求的时间复杂度为 $ n^2 $，显然不行。

想到一句话：“正难则反”。我们无法快速求一个序列的 $ \operatorname{Mex} $ 值。无妨，我们倒推，判断什么样的序列的 $ \operatorname{Mex} $ 值为 $ 2 $。

推导的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/w5n75kaf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

发现只有圈内的数要特判，其他随便填。

按奇偶分类，分别处理即可。

## 代码

```cpp
//written by Naught
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define Maxn 3000005
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

int n, a[Maxn];

int main()
{
    int _ = read();
    while(_--)
    {
        n = read();
        fo(i, 1, n) a[i] = read();
        if( n == 1 )
        {
            if(a[1] == 2) puts("Yes");
            else puts("No");
            continue;
        }
        if( n == 2 )
        {
            if( (a[1] + a[2]) == 1 ) puts("Yes");
            else puts("No");
            continue;
        }
        if(n & 1)
        {
            if(a[n/2+1] < 2) {puts("No"); continue;}
            if( (a[n/2] + a[n/2+2]) != 0 && (a[n/2] * a[n/2+2]) == 0 ) puts("Yes");
            else puts("No");
        }
        else
        {
            if( (a[n/2] == 0 && a[n/2+1] == 1 && a[n/2+2] >= 1) || (a[n/2-1] >= 1 && a[n/2] == 1 && a[n/2+1] == 0) ) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
```

## Tips

记得特判 $n = 1$ 和 $n = 2$ 的情况。

---

## 作者：DDF_ (赞：0)

赛时这一题卡了很久。

## 题解

其实根据上一题可以得知这一题也是一道找规律的题目。

注意到两个数的 $\operatorname{mex}$ 值只有三种取值，为 $\{0,1,2\}$，所以可以在代码一开始就将整个数组处理成只有 $\{0,1,2\}$ 的形式。

然后推性质。

在 $S=\{0,1,2\}$ 这个集合中，$2$ 是最大值，所以要使给定的 $a$ 序列满足题目中的条件，那么 $f(a)=2$。

列出所有情况中 $\operatorname{mex}$ 的值，可得当 $\operatorname{mex}(x,y)=2~(x \le y)$ 时，$x=0,~y=1$；当 $\operatorname{mex}(x,y)=1~(x \le  y)$ 时，$x=0,~y \not = 1$；当 $\operatorname{mex}(x,y)=0~(x \le  y)$ 时，$x \not = 0,~y \not = 0$。

然后以此一层一层往下推得到下表（下表中 $x$ 为集合 $S=\{0,1,2\}$ 中的任一元素，$t$ 为集合 $S$ 中的不等于 $0$ 的任一元素）。

$$
2\\
0 ~ 1\\
0 ~ 2 ~ t\\
x ~ 1 ~ 0 ~ t\\
x ~ 0 ~ 2 ~ t ~ x\\
x ~ t ~ 1 ~ 0 ~ x ~ x\\
x ~ x ~ 0 ~ 2 ~ t ~ x ~ x\\
x ~ x ~ t ~ 1 ~ 0 ~ x ~ x ~ x\\
x ~ x ~ x ~ 0 ~ 2 ~ t ~ x ~ x ~ x\\
x ~ x ~ x ~ t ~ 1 ~ 0 ~ x ~ x ~ x ~ x\\
$$

注意得到的表中，两边全为任意的数，而中间部分在 $n$ 为奇数和 $n$ 为偶数时呈现不同的性质。当 $n$ 为奇数时，数列中处于中间位置的数为 $2$，它左边的数为 $0$，右边的数不等于 $0$；当 $n$ 为偶数时，数列中处于中间位置的两个数分别为 $1$ 和 $0$，这两个数左边的数为不等于 $0$。接着在数列中判掉这个性质就可以了。

类似地，将表对称得到另一个表，发现对称得到的表也是满足 $\operatorname{mex}$ 的规律的，于是再判掉这个表的性质。

最后别忘记特判 $n=1$ 或 $n=2$ 的情况。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e6+2;
int t;
int n,a[N];
void solve() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		if(a[i]>2) a[i]=2;
	}
	if(n==1) {
		if(a[1]==2) puts("Yes");
		else puts("No");
	}
	if(n==2) {
		if(a[1]+a[2]==1) puts("Yes");
		else puts("No");
	}
	if(n>2) {
		if(n&1) {
			if(a[n/2+1]==2) {
				if(a[n/2]==0&&a[n/2+2]>0) puts("Yes");
				else if(a[n/2+2]==0&&a[n/2]>0) puts("Yes");
				else puts("No");
			}
			else puts("No");
		}
		else {
			if(a[n/2]==0&&a[n/2+1]==1&&a[n/2+2]>0) puts("Yes");
			else if(a[n/2]==1&&a[n/2+1]==0&&a[n/2-1]>0) puts("Yes");
			else puts("No");
		}
	}
	return;
}
int main() {
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：FlyPancake (赞：0)

## [P10370 「LAOI-4」Mex Tower (Hard ver.)](https://www.luogu.com.cn/problem/P10370) 题解

赛时硬推推出来的。
## Ideas
可以发现如果想要 $f(a)\ge f(b)$，那么 $a$ 序列必定满足最后得到的值**最大**，而最大的值一定为 $2$，且其一定由 $\{1, 0\}$ 或 $\{0, 1\}$ 得到，考虑一步一步向上倒推找规律。

可观察到一些限制条件（以下皆默认集合去重）：

- 如果当前行第 $i$ 位为 $0$，那么上一行第 $i$ 位和第 $i+1$ 位均不为 $0$。
- 如果当前行第 $i$ 位为 $1$，那么上一行第 $i$ 位和第 $i+1$ 位中一个为 $0$，一个不为 $1$。
- 如果当前行第 $i$ 位不为 $0$，那么上一行第 $i$ 位和第 $i+1$ 位中至少有一个 $0$。
- 如果当前行第 $i$ 位不为 $1$，那么上一行第 $i$ 位和第 $i+1$ 位中没有 $0$ 或者一个为 $0$，一个为 $1$。

以下先考虑倒数第二步为 $\{1, 0\}$ 的情况（规定 $x$ 为**可以是任何数**）：

![](https://cdn.luogu.com.cn/upload/image_hosting/m1tf05hk.png)

推着推着按奇偶看规律就出来了，只要序列 $a$ 满足上图的构造即可。

倒数第二步为 $\{0, 1\}$ 的情况也就是上图整个反过来的情况。


最好特判 $n$ 为 $2$ 的情况。

## Code
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int a[3000005];
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        for(int i=1; i<=n; i++) cin>>a[i]; // 其实完全可以不用a数组存，只要在输入相应的位置时判断就行了，不过这样比较清晰
        if(n==2){
            if(a[1]==0&&a[2]==1 || a[1]==1&&a[2]==0) cout<<"Yes\n";
            else cout<<"No\n";
        }
        else if(n%2==1){
            int x = n/2;
            if((a[x]!=0&&a[x+2]==0 || a[x]==0&&a[x+2]!=0)&&a[x+1]!=0&&a[x+1]!=1) cout<<"Yes\n"; // 这里直接将两种情况合起来写了
            else cout<<"No\n";
        }
        else{
            int x = n/2;
            if(a[x]==0&&a[x+1]==1&&a[x+2]!=0 || a[x-1]!=0&&a[x]==1&&a[x+1]==0) cout<<"Yes\n";
            else cout<<"No\n";
        }
    }
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

前置知识：[Easy ver 的结论](https://www.luogu.com.cn/problem/P10369)。

由 Easy ver 可得，$f(b)$ 最多为 $2$，所以只用判断 $f(a)$ 是否 $=2$ 即可。

那如何来判断 $f(a)$ 是否 $=2$ 呢？可以像 Easy ver 一样来倒推（其中斜杠为或，问号为未知的数）：

$$2 \\ 0\ 1 \\ 1/2\ 2 \ 0 \\ ?\ 0\ 1\ ?\\ ?\ 1/2\ 2\ 0\ ? \\ \cdots$$

因为整个三角形是可以翻转的，所以可得出条件：

1. 首先先模拟至少 $4$ 次。
1. 当 $n\equiv 1\pmod2$ 时，中间 $\ge 2$，任意一边为 $0$ 即可。
2. 反之模拟再一遍后再判断即可。

---

