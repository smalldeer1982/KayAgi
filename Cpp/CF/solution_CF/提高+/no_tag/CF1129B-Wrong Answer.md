# Wrong Answer

## 题目描述

考虑如下问题：给定一个包含 $n$ 个整数的数组 $a$（下标从 $0$ 到 $n-1$），求
$$
\max\limits_{0 \leq l \leq r \leq n-1} \sum\limits_{l \leq i \leq r} (r-l+1) \cdot a_i
$$
在本题中，$1 \leq n \leq 2000$，且 $|a_i| \leq 10^6$。

为了解决上述问题，Alice 很快想出了一个极快的贪心算法并进行了编码。她的伪代码实现如下：

```
function find_answer(n, a)
    # 假设 n 是 1 到 2000 之间的整数
    # 假设 a 是一个包含 n 个整数的列表：a[0], a[1], ..., a[n-1]
    res = 0
    cur = 0
    k = -1
    for i = 0 to i = n-1
        cur = cur + a[i]
        if cur < 0
            cur = 0
            k = i
        res = max(res, (i-k)*cur)
    return res
```

然而，正如你所见，Alice 的想法并不完全正确。例如，假设 $n = 4$ 且 $a = [6, -8, 7, -42]$，则 find\_answer(n, a) 会返回 $7$，但正确答案是 $3 \cdot (6-8+7) = 15$。

你告诉 Alice 她的解法是错误的，但她并不相信。

给定一个整数 $k$，你需要构造一个长度为 $n$ 的整数序列 $a$，使得正确答案与 Alice 算法的输出恰好相差 $k$。注意，$n$ 和序列内容由你选择，但必须满足上述约束：$1 \leq n \leq 2000$，且每个元素的绝对值不超过 $10^6$。如果不存在这样的序列，请输出相应信息。

## 说明/提示

第一个样例对应题目描述中的例子。

第二个样例中，一种可行解为 $n = 7$，$a = [30, -12, -99, 123, -2, 245, -300]$，此时 find\_answer(n, a) 返回 $1098$，而正确答案为 $1710$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
```

### 输出

```
4
6 -8 7 -42
```

## 样例 #2

### 输入

```
612
```

### 输出

```
7
30 -12 -99 123 -2 245 -300
```

# 题解

## 作者：Trimsteanima (赞：9)

既然 $ n \leq 2000$ 那我们就假使所有的 $n = 2000 $ ~~主要是为了方便~~。再使 $x = \sum_{i=1} ^ {1999}$ 以及 $a_1=a_2=a_3=...=a_{1998}=0 $，$a_{1999}=-d$，$a_{2000}=x+d$。
正确答案就应该是$2000x$，而爱丽丝答案为$x+d$，两个答案的差值为$2000x-x+d$，所以$1999x=k+d$，$x=\frac{k+d}{1999}$，则d = 1999 - k % 1999。
```cpp
#include<bits/stdc++.h>
using namespace std;
int k, a;
int main() {
    scanf("%d", &k);a = 2000 - k % 2000 + 998000;
    printf("2000\n");
    for (int i = 1; i <= 1998; i ++) printf("0 ");
    printf("%d %d\n", -a + (k + a) / 2000, a);
    return 0;
}
```

---

## 作者：Carotrl (赞：2)

构造思维题

注意到 Alice 使用了最大子段和类似的思路，在遇到和为负数时会自动清零，故应先将和值加为负数，再加为正数，使后者总权值和更最大。

因为 $n \le 2000$，故使 $n=2000$，并令 $a_{1,2...,1998}=0$，通过构造 $a_{1999}$ 和 $a_{2000}$来完成需求。

设 $a_{1999}=x$，$a_{2000}=y$，$x$ 为负数， $y$ 为正数，因为错解在 $a_{1999}$ 小于 $0$ 时计数器并没有累加而归 $0$，所以答案为 $y$，而正解显然为 $2000(x+y)$。

现在即求 $2000(x+y)-y=k$，化简得$2000x+1999y=k$，设 $n=x+y$，得 $1999n+x=k$，即$n= \frac{k-x}{1999}$，因为 $n$ 为正整数，所以 $k-x$ 应为 $1999$ 的倍数，因为 $x$ 是负数，所以是求大于 $k$ 的一个 $1999$ 的倍数，那么 $1999n = k-k\%1999+1999$ 显然成立。然后就可以求出 $n,x,y$ 了，详细可以见代码。

code:

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
using namespace std;
long long k,n;
int main(){
	printf("2000\n");
	for(int i=1;i<=1998;i++)printf("0 ");
	scanf("%lld",&k);
	n=k-k%1999+1999;
	printf("%lld %lld",k-n,n/1999-k+n);
}
```


---

## 作者：DPair (赞：2)

构造好题，写篇题解纪念一下。

主要是解释另一篇题解没解释的思路。

## 【思路】
首先确定我们的目标是构造一组数据，使得正确答案与错误答案之差为 $k$ 。

先观察样例。

发现 Alice 最大的问题在于用类似最大子段和的思想进行了 **错误的贪心**，忽略了 **子段长度的贡献** 。

比如样例中， $6 - 8 = -2 < 0$ ，但事实上它会对后面的 $7$ 进行加倍。

这也同时告诉我们， $Alice$ 的程序遇到负数会自动忽略负数。

那我们就要想办法利用这个特点。

于是我们有了第一种构造方法：一个序列有两个数，第一个是负数 $x_1$，第二个是正数 $x_2$，那我们就能成功限制 Alice 的答案为 $x_2$ ，而正确答案为 $max(x_2,(x_1+x_2) * 2)$ 。

此时如果 $x_1$ 的绝对值足够小，那么 Alice 的答案就错了，并且与正确答案的差距是我们可以控制的。

然而这道题 $k$ 有 $1e9$ ，而 $x_i$ 最多 $1e6$ ，因此我们考虑扩展上述解法。

不难发现，$x_i\le 0$ 对 Alice 的答案是没有影响的，它只会在 **正解** 中为长度增加贡献。

因此我们考虑把上文中的 $2$ 直接变为 $n_{max}=2000$ ，然后$x_1,x_2$ 变为 $x_{n-1},x_n$ 即可。

那么现在只需要构造一组数据，使得 $k=(x_{n-1}+x_{n})*2000-x_{n}$ 即可。

下面设 $x_{n-1}=val,x_n=x$

得
$$
k=2000val+2000x-x
$$
$$
val=\frac{k-1999x}{2000}
$$
$$
-val=x-\frac{x+k}{2000}
$$

由于$val\le 0, -val\ge 0$，所以现在我们只需要使得 $x-\frac{x+k}{2000} \ge 0$ 且为整数即可。

那么我们让 $x+k=0(mod~2000)$ 且 $x$ 尽可能大。

那么有 $x=2000-k(mod~2000)$ ，取 $x=1000000-(k \% 2000)$ 即可满足题意。

并且此时 $x > 998000$ ，而 $\frac{x+k}{2000}$ 大约是 $500000$ 级别的，满足题意。

所以构造一组这样的数据即可：

$$n=2000$$

$$a_1=a_2=\dots=a_{1998}=0$$

$$a_{2000}=1000000-(k \% 2000)$$

$$a_{1999}=-(a_{2000}-\frac{a_{2000}+k}{2000})$$

## 【代码】
实现过于简单。
```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
int main(){
    scanf("%d", &k);
    int num = k % 2000;
    int x = 1000000 - num;
    printf("2000\n");
    for (register int i = 1;i <= 1998;i ++) printf("0 ");
    printf("%d %d\n", -(x - ((x + k) / 2000)), x);
}
```

---

## 作者：沉石鱼惊旋 (赞：1)

# 题目翻译

长度为 $n$ 的序列 $a$，求 $\max\limits_{0 \leq l \leq r \leq n-1} \sum\limits_{l \leq i \leq r} (r-l+1) \cdot a_i$。

$1\leq n\leq 2000,|a_i|\leq 10^6$。

Alice 写了伪代码如下：

```
function find_answer(n, a)
    # Assumes n is an integer between 1 and 2000, inclusive
    # Assumes a is a list containing n integers: a[0], a[1], ..., a[n-1]
    res = 0
    cur = 0
    k = -1
    for i = 0 to i = n-1
        cur = cur + a[i]
        if cur < 0
            cur = 0
            k = i
        res = max(res, (i-k)*cur)
    return res

```

给定 $k$ 请你给出一组 hack 满足正确答案比 Alice 的输出大 $k$。

你给出的 hack 也应该满足原题的数据范围限制。

# 题目思路

Alice 写了个类似最大子段和的东西，但是没有考虑长度带来的影响。换言之，我们让答案区间内包含较少的小负数，但是长度很长，就可以叉掉 Alice。

为了让我们自己方便得到正确答案，我们在最后出现 $2$ 个数，一正一负。

考虑直接构造 $n=2000$ 的情况。

令 $ans$ 表示正确答案，$alice$ 表示 Alice 的答案。我们构造的序列为 $0,0,0,\cdots,0,-x,y$。

然后直接用小学就学过的等式的基本性质推柿子。

首先我们的 $ans=2000(y-x)$，而 Alice 的 $alice=y$ 这个是肯定的。

也就是我们要解出 $2000(y-x)$

那么我们就是要解 $2000(y-x)-y=k$ 这个方程的一个整数解。

移项得到 $y=\frac {2000x+k}{1999}$。

那么我们任取一个 $x$ 不一定满足能整除，那么也就是我们找到的 $x,y$ 必须满足 $2000x+k\equiv 0\pmod{1999}$。减掉 $1999x$ 得到 $x+k\equiv 0\pmod{1999}$。

又因为我们有 $|a_i\leq 10^6|$ 的限制，不能乱找 $x$。保险一点直接取最小的正整数 $x$。即为 $1999-k\bmod {1999}$。

那么我们目前得到了 $1\leq x\leq 1999$，还可以得到 $y=\frac{2000x+k}{1999}=x+\frac{x+k}{1999}\leq 10^6$。

那么做完了。

# 完整代码

推导过程也写代码里了，duel 的时候手边没有草稿纸是这样的。

```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
int main()
{
    cin >> k;
    cout << 2000 << endl;
    for (int i = 1; i <= 1998; i++)
        cout << 0 << " ";
    /*
    -x, y
    ans: 2000 * (y - x)
    alice: y
    ans - alice = k
    2000 * (y - x) - y = k
    1999 * y - 2000 * x =k
    y = (2000 * x + k)/1999
    2000 * x % 1999 + k % 1999 = 0 (mod 1999)
    x + k % 1999 = 0 (mod 1999)
    */
    int x = (1999 - k % 1999);
    int y = (2000 * x + k) / 1999;
    cout << -x << " " << y << endl;
    return 0;
}
```

---

## 作者：DJRzjl (赞：1)

# [CF1129B](https://www.luogu.com.cn/problem/CF1129B) $~~$ Wrong Answer

原问题要求一个序列某个字串使 长度 $\times$​​​​​ 元素和 最大，观察 Alice 的程序，它一旦发现当前字串和为负，便会直接截断，也就是它只更新了每个前缀和都非负字串的答案，形如序列 $a=\{0,0,0,-1,11\}$​，正确答案为 $5 \times 10 =50$​，而 Alice 求得  $1 \times 11=11$​​​​。

不难想到利用 一长串 $0$ $+$ 一个负数 $+$ 正数 的结构来构造，因为要求 $n \le 2000$ ，方便起见，我们直接令 $n=2000$ ，不影响可行性。

如果最后只有一个正数 $a_{2000}$​​​​​​​ ，那么我们令 $a_0=a_1=\cdots=a_{1998}=0,a_{1999}=-x,a_{2000}=y$​​​​​​​，此时正确答案为 $2000*(y-x)$​​​​​，而 Alice 求得 $y$​​​​。

所以有 $1999y-2000x=k$​​​​，即 $1999 \times (y-x) -x=k$​​​。

显然，一组特解为 $x=1999-k\bmod1999,y=\frac{k+x}{1999}+x$​​​​​​​​，其中 $0 \le x<1999,0\le y \le\frac{10^9+1999}{1999}+1999<10^6$​​​​​​​，满足题意。

所以我们仅需构造长度为 $2000$​​​​ 的序列 $a=\{0,0,0,\cdots,0,-(1999-(k\bmod1999)),\lfloor \frac{k}{1999} \rfloor+1+(1999-(k\bmod1999)) \}$​​​​​ 即可。

​                                                                                                                                                                                                                               
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int k;

int main(){
	scanf("%d",&k);
	puts("2000");
	for(int i=1;i<=1998;i++) printf("0 ");
	printf("%d %d\n",-(1999-k%1999),k/1999+1+1999-k%1999);
	return 0;
}
```


---

## 作者：Hoks (赞：0)

## 前言
比较有意思的构造题，不是很难。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
重点关注数据范围，发现 $\frac{\max(k)}{\max(a_i)}=1000$，小于 $n$，考虑人类智慧。

不难发现 Alice 的代码求的是最大的连续正数和乘区间长度。

所以我们只需要在任何一个位置扔一个负数就可以让 Alice 的代码把两边断开求。

考虑朴素至极的想法，只填一个负数卡掉 Alice，然后用一个正数拉开差距。

给前面空位全部填上 $0$ 来拉开正解和 Alice 答案之间的差距。

也就是构造形如：
$$0,0,0,\dots,-x,y$$
那么正确答案即为 $2000(y-x)$，错误答案即为 $y$。

解方程 $k=2000(y-x)-y$。

化简一下可得 $1999(y-x)=k-y$。

因为都是整数，所以取一个最小的 $1999|k-y$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10,V=1e6,INF=0x3f3f3f3f,b=1145141,mod=1004535809;
int n=2000,k;
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='('||c==')'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
signed main()
{
	k=read();int d=1999-k%1999,x=(k+d)/1999;print(2000),put('\n');
	for(int i=1;i<=1998;i++) print(0),put(' ');
	print(-d),put(' '),print(x+d);
	genshin:;flush();return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

$\textbf{CF1129B}$

考虑一种简单的构造 $a = [0,0,\ldots,x,y]$ 其中 $x < 0,y > 0$，则答案的差值为 $n(y+x)-y$。考虑解 $n(y+x)-y = k$ 这个方程，化简即为 $(n-1)y+nx=k$，exgcd 解出通解再调整即可。注意到这个方程不一定有合法解，我们枚举 $n$ 一一检验。时间复杂度 $\mathcal O(n \log k)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 12.08.2024 21:10:54
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,k,n,m;
void exgcd(int a,int b,int &x,int &y){
    if(!b) return x = 1,y = 0,void();
    exgcd(b,a % b,y,x),y -= (a / b) * x;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> k;
    for(int i = 2;i <= 2000;i ++){
        int a = i - 1,b = i,x,y;
        exgcd(a,b,x,y);
        x = (x + b) % b;
        ll tx = 1ll * x * k,ty = (k - a * tx) / b; 
        if(tx > 1e6){
            ll df = (tx - 1e6),p = (df + b - 1) / b;
            tx -= p * b,ty += p * a;
        }
        // while(tx > 1e6) tx -= b,ty += a;
        if(abs(ty) <= 1e6 && ty < 0){
            cout << i << "\n";
            for(int j = 1;j <= i - 2;j ++) cout << "0 ";
            cout << ty << " " << tx << "\n";
            return 0; 
        }
        
    }
}
```

---

## 作者：Liuxizai (赞：0)

## Description

给定一个序列 $a$，有 $n$ 个元素，编号从 $0$ 到 $n-1$。求 $\max\limits_{0 \leq l \leq r \leq n-1} \sum\limits_{l \leq i \leq r} (r-l+1) \cdot a_i$。

Alice 的解法是令 $[l,r]$ 为序列 $a$ 权值和最大的子段。

请你给出一组 Hack 数据，使得 Alice 给出的答案与正确答案的差为 $k$。

$n\le2000,|a_i|\le10^6,k\le10^9$

## Solution

已有的三篇题解给出了三个一样的构造方法，同时，从我个人角度来看，令 $a_{1\dots1998}=0$ 这种构造方式并不是很符合直觉。

实际上这是一道难度不高且方法较多的构造题。

首先，想要 Hack Alice 的解法非常简单，Alice 忽略了子段长度对答案的影响，随便用负数就能卡掉。

延续样例的思路，我最开始给出的构造是 $1,-2,a_1,a_2,a_3,\dots,a_y$，这样，令 $x=\sum a_i$，Alice 的答案会是 $xy$，实际上期望的答案是加入 1 与 -2，即 $(x-1)(y+2)$。

Alice 答案与正确答案的差我们记作 $\Delta=(x-1)(y+2)-xy=2x-y-2$，我们希望 $\Delta=k$。

接下来，我们考虑一个向序列末尾动态加数的过程，初始时序列为 $1,-2$，$x=y=0$，$\Delta=-2$，每当我们像序列末尾添加一个数 $t$，其对 $\Delta$ 的贡献为 $2t-1$，需要注意的是 $t$ 有一个 $10^6$ 的上界，不断加数使得 $\Delta=k$ 即可。

$O(n)$ 模拟这一过程就能构造出一个合法的序列。

另外还有一种更加简洁的构造，让序列由 $-1,1$ 开头，类似上文，我们可以求出 $\Delta=x-y$，这样一个新数 $t$ 对 $\Delta$ 的贡献为 $t-1$。

## Code

给出第一种构造的代码。

```cpp
namespace Main{
    const int N = 2005;
    int k, n, a[N];
    void Main(){
        input(k);
        n = 2;
        a[0] = 1, a[1] = -2;
        k += 2;
        while(k) a[n] = min(1000000, (k + 1) / 2), k -= 2 * a[n++] - 1;
        cout << n << endl;
        for(ri i = 0; i < n; i++) cout << a[i] << ' ';
        return;
    }
} // namespace
```

---

## 作者：zhlzt (赞：0)

### 题解

发现 Alice 的做法类似于求最大子段和，并没有考虑到减负加正得正且 $r-l+1$ 更大的情况。

不妨取 $n=2000$，$\forall i\in [1,n-2]\Rightarrow a_i=0$。可以令 $a_{n-1}<0$，$a_n>0$，且 $|a_n|>|a_{n-1}|$。

此时 Alice 的程序求出的结果为 $a_n$，通过构造使得正确答案为 $n\times (a_{n-1}+a_n)$，相减得：

$$\begin{aligned} n\times a_{n-1}+(n-1)\times a_n &= k \\ (n-1)\times (a_{n-1}+a_n)+a_{n-1}&= k \\ (n-1)\times(a_{n-1}+a_n) &= k-a_{n-1}\\ a_{n-1}+a_n&= \dfrac{k-a_{n-1}}{n-1} \end{aligned}$$

为使 $n-1\mid k-a_{n-1}$，并满足条件 $a_{n-1}<0$，可令 $a_{n-1}=k\bmod (n-1)-(n-1)$。易知 $a_n=\dfrac{k-n\times a_{n-1}}{n-1}$。由于 $k>0$，代入原式知 $n\times (a_{n-1}+a_n)>a_n$，且有 $|a_{n-1}|<|a_n| \le10^6$ 满足条件。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+10;
int a[maxn];
int main(){
	int k,n=2e3;cin>>k;
	a[n-1]=k%(n-1)-(n-1);
	a[n]=(k-n*a[n-1])/(n-1);
	cout<<n<<'\n';
	for(int i=1;i<=n;i++){
		cout<<a[i]<<' ';
	}
	cout<<'\n';
	return 0;
} 
```

---

