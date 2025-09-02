# Pavel and Triangles

## 题目描述

Pavel has several sticks with lengths equal to powers of two.

He has $ a_0 $ sticks of length $ 2^0 = 1 $ , $ a_1 $ sticks of length $ 2^1 = 2 $ , ..., $ a_{n-1} $ sticks of length $ 2^{n-1} $ .

Pavel wants to make the maximum possible number of triangles using these sticks. The triangles should have strictly positive area, each stick can be used in at most one triangle.

It is forbidden to break sticks, and each triangle should consist of exactly three sticks.

Find the maximum possible number of triangles.

## 说明/提示

In the first example, Pavel can, for example, make this set of triangles (the lengths of the sides of the triangles are listed): $ (2^0, 2^4, 2^4) $ , $ (2^1, 2^3, 2^3) $ , $ (2^1, 2^2, 2^2) $ .

In the second example, Pavel cannot make a single triangle.

In the third example, Pavel can, for example, create this set of triangles (the lengths of the sides of the triangles are listed): $ (2^0, 2^0, 2^0) $ , $ (2^1, 2^1, 2^1) $ , $ (2^2, 2^2, 2^2) $ .

## 样例 #1

### 输入

```
5
1 2 2 2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
3 3 3
```

### 输出

```
3
```

# 题解

## 作者：StudyingFather (赞：7)

一个比较显然的结论：若 $a \leq b \lt c$，则 $2^a+2^b \leq 2^c$。

所以可能的三角形只有两种情况：

1. $a \lt b=c$；
2. $a=b=c$。

因此我们从小到大考虑，为了充分利用前面留下的木棍，我们最好先搭建第一种情况的三角形，有剩余的时候再考虑第二种三角形。

```cpp
// Problem : E. Pavel and Triangles
// Contest : Codeforces Global Round 2
// URL : https://codeforces.com/contest/1119/problem/E
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cp-editor)

#include <iostream>
#include <queue>
using namespace std;
priority_queue<int,vector<int>,greater<int> > q;
int main()
{
 int n;
 long long ans=0;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  int x;
  cin>>x;
  while(!q.empty()&&x>=2)
  {
   int u=q.top();
   q.pop();
   int res=min(u,x/2);
   ans+=res;
   x-=res*2,u-=res;
   if(u>0)
    q.push(u);
  }
  ans+=x/3;
  x%=3;
  q.push(x);
 }
 while(!q.empty())
 {
  int u=q.top();
  q.pop();
  ans+=u/3;
 }
 cout<<ans<<endl;
 return 0;
}
```

---

## 作者：RainFestival (赞：4)

贪心题，codeforces 评分 $1900$, ~~标签（codeforces）里有 fft ,惊恐~~。

首先 ，定义有序数对 $(a,b,c)$ 为一个三角形，三边长为 $a,b,c$，其中 $a\le b\le c$。**根据三角形不等式，$a+b>c$**。

设某一个三角形最短边为 $2^i$，则三角形只能是**第一类 $(2^i,2^i,2^i)$** 或者**第二类 $(2^i,2^{i+1},2^{i+1})$**。

所以，**每一种长度的边只与一种其它长度边有关**。

设计一种贪心策略，稍后证明：**对于每一种长度的边，我们每一次都先取第一类，直到不能取为止，再取第二类，直到不能取为止**。

证明如下：

定义“使用”某条边为这条边在某三角形中，“多余”某条边为没有使用这条边但是可能还可以使用 ，“浪费”某条边为确定不“使用”这条边，$/$ 为或者符号。记 $ans$ 为如上取法的答案，$ans'$ 为新取法的答案。

因为不管什么三角形，都只用 $3$ 条边，所以我们发现 “使用” 优于 “多余” 优于 “浪费”。

对于 $2^i$ 边：

除非不得不浪费，浪费边肯定是不更优秀 $(ans\ge ans')$ 的,因为有可能浪费边使得使用了更大的边，可能使得更大的边不够。

对于第一类分完之后多余的 $2^i$ 边，与 $2$ 个 $2^{i+1}$ 组成 $(2^i,2^{i+1},2^{i+1})$，只使用了 $2$ 条 $2^{i+1}$ 就构成 $1$ 个三角形。如果这条边不要，那么 $2$ 条 $2^{i+1}$ 还要配 $1$ 条 $2^{i+1}$ 才能组成 $1$ 个三角形。浪费 $1$ 条 $2^i$，则必须多使用 $1$ 条 $2^{i+1}$。

如果将一种第一类拆成 $3$ 条 $2^i$ 边，受到 $2^{i+1}$ 边影响，设未使用的 $2^{i+1}$ 边有 $p$ 条，只能再组成 $k=\min(\lfloor\frac{p}{2}\rfloor,3)$ 个第二类，使用 $k,0\le k\le 3$ 条 $2^i$，再使用 $2\times k$ 条 $2^{i+1}$，可以组成 $k$ 个 $(2^i,2^{i+1},2^{i+1})$ , $\Delta ans'=k$。

而 $\Delta ans=1$，即构成 $1$ 个 $(2^i,2^i,2^i)$ ,
但是必须考虑多用的 $2\times k$ 条边构成的贡献 $(2^{i+1},2^{i+1},2^{i+1})$，计 $\lfloor\frac{2\times k}{3}\rfloor$ 个。所以 $\Delta ans=1+\lfloor\frac{2\times k}{3}\rfloor$。

下面对 $k$ 进行分类讨论。

当 $k=0$，$\Delta ans=1,\Delta ans'=0,\therefore \Delta ans>\Delta ans'$；

当 $k=1$，$\Delta ans=1,\Delta ans'=1,\therefore \Delta ans=\Delta ans'$ , $ans$ 多余 $2$ 条 $2^{i+1}$  , $ans'$ 浪费 $2$ 条 $2^i$；

当 $k=2$，$\Delta ans=2,\Delta ans'=2,\therefore \Delta ans=\Delta ans'$ , $ans$ 多余 $1$ 条 $2^{i+1}$  , $ans'$ 浪费 $1$ 条 $2^i$；

当 $k=3$，$\Delta ans=3,\Delta ans'=3,\therefore \Delta ans=\Delta ans'$；

$\therefore \Delta ans\ge\Delta ans'$ ,并且 $ans$ 还有多余。

证毕

代码如下：

```cpp
#include<cstdio>
int n,a[300005];
long long ans=0;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	int now=1;
	for (int i=1;i<=n;i++)
	{
		ans=ans+(a[i]/3);
		a[i]=a[i]%3;
		if (now<=i) now=i+1;
		while (now<=n&&a[now]<2) ++now;
		if (a[i]>=1&&a[now]>=2) ++ans,--a[i],--a[now],--a[now];
		while (now<=n&&a[now]<2) ++now;
		if (a[i]>=1&&a[now]>=2) ++ans,--a[i],--a[now],--a[now];
	}
	printf("%lld\n",ans);
}
```

谢谢观看！


---

## 作者：Frozencode (赞：3)

注意到每种边长都是$2^k$，那么等边三角形是无所谓的，但是等腰三角形的话只能把小的边作为底边，那么我们从大到小枚举就行啦~
```cpp 
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
ll n,a[maxn],ans=0,cnt=0;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=n;i>=1;i--)
    {
        cnt+=a[i]/2;//cnt代表当前有多少对相等的边。
        if(a[i]%2==1&&cnt>0)//如果有单个边多余那么我们看前面有没有一对边可以和它匹配。
        {
            ans++;
            cnt--;
        }
    }
    ans+=2*cnt/3;最后只要把总边数除以3就行了，因为只要按照大边的作为腰小边作为底的话是一定可行的。
    cout<<ans;
    return 0;
}
```


---

## 作者：Zechariah (赞：2)

考虑到只有两种三角形：等腰和等边，其中等腰的底是一条较小的边  
要构造最多的三角形，其实就是要用掉最多的边，怎么用掉最多的边呢？  
对于一类边$2^k$，我们发现比他小的边都只能作为等腰的底边，而三条相同的边就能组成等边  
于是贪心的策略就很明显了：顺次考虑每条边，优先造等腰，再造等边
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
typedef unsigned int uint;
const int N = 5e5 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int a[N];

int main(void) {
    rg int n = fast_IO::read();
    rg ll ans = 0, sum = 0;
    for (rg int i = 1; i <= n; ++i) {
        a[i] = fast_IO::read();
        rg int del = fast_IO::min(a[i] >> 1, sum);
        ans += del; sum -= del; a[i] -= del << 1;
        ans += a[i] / 3; a[i] %= 3;
        sum += a[i];
    }
    fast_IO::write(ans);
    return 0;
}
```


---

## 作者：irris (赞：1)

> CF-style / 贪心 / 调整

## Preface

感觉这种奇怪题还是得加训......

## Solution

考虑三角形不等式，此外有 $2^{i-1} + 2^{i-1} \leq 2^i$，于是我们可以肯定三角形全部为等腰、且腰长 $\geq$ 底长的三角形。

问题转化为：定义一次操作为选定 $1 \leq j \leq i \leq n$，令 $a_i \gets a_i - 2$，$a_j \gets a_j - 1$。要求每次操作后 $\forall a_i \geq 0$。问最多能操作多少次。

考虑贪心：因为大的总能匹配更小的，我们想到从大到小操作。对于每个下标最多作为 $j$ 操作 $1$ 次，然后剩下的全部用于尝试拼凑等边三角形。

这个似乎有点假，但是它的方向是对的。我们下面证明一个引理：

> **引理**：若 $\forall 1 \leq i \leq n$ 满足 $2 \mid a_i$，那么答案就是 $\lfloor\frac{\sum a_i}3\rfloor$。

构造性证明，我们按 $i$ 从大向小匹配 $i, j$ 对。

若 $a_i \geq 6$，我们匹配 $\lfloor \frac{a_i}{6}\rfloor$ 次 $(i, i)(i, i)$。这当然合法。下面 $\forall a_i \in \{0, 2, 4\}$，我们再证明一遍引理：

- $a_i = 0$：我们什么都不干。
- $a_i = 2$：我们选择一个 $j$ 然后尝试匹配 $(i, j)$。这个 $j$ 当然总是可以选择最小的 $a_j \gt 0$。当然这要求我们后面也存在一个 $i'(a_{i'} \bmod 6 = 2)$ 并且匹配这个 $j$，否则这里变成奇数会导致一些不必要的麻烦。但是，如果不存在这个 $i'$，那么 $\sum a_i$ 模 $3$ 就一定余 $2$，我们不操作就达到上界了，那么这个操作虽然此刻不合法也无关紧要。
- $a_i = 4$：我们选择一个 $j$ 然后尝试匹配两次 $(i, j)$。这个 $j$ 当然总是可以选择最小的 $a_j \gt 0$。显然，如果不存在这个 $j$，那么就说明剩下的 $a_j$ 都是 $0$，那我们匹配一次 $(i, i)$ 后结束。这当然也取到了上界。

得证，所以我们的奋斗目标就在于把所有的 $a_i$ 都变成奇数，这当然对每个数最多调整 $1$ 次。然后从大到小贪心匹配即可。

这样达成了上界，时间复杂度 $\mathcal O(n)$。

## Code

十分简易。

```cpp
#include <bits/stdc++.h>

namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return; write<T>(x / 10), putchar(x % 10 ^ '0'); }
	template <typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; else if (x == 0) putchar('0'); write<T>(x); }
	template <typename T> inline void print(T x, char en) { if (x < 0) putchar('-'), x = -x; else if (x == 0) putchar('0'); write<T>(x), putchar(en); }
}; using namespace FastIO;

#define MAXN 300001
int a[MAXN];

int main() {
	int N = read<int>();
	for (int i = 1; i <= N; ++i) a[i] = read<int>();
	long long mth = 0, o = 0;
	for (int i = N; i; --i) {
		mth += (a[i] >> 1);
		if (a[i] & 1 && mth > 0) mth -= 1, o += 1;
	}
	return print<long long>((mth << 1) / 3 + o), 0;
}
```

## Postscript

原来可以从小到大贪，绷不住了。

---

## 作者：gary2005 (赞：1)

贪心！
首先我们可以确定只有等腰三角形满足条件（等边是特殊的等腰）那么久可以将其每边表示为（ij,j） 其中i≤j

如果底边设为i，那么只要腰大于等于i那么都满足条件，也就无论j取几对答案的贡献是一样的，反而j更靠前会有剩余的边供后面的作为底，也就有更多的机会。

这样为了防止浪费底，那么前面剩余的就尽快将其用掉，也满足上面j靠前的贪心思路。所以就OK了。

CODE
```
//* AuThOr GaRyMr *//
#include<bits/stdc++.h>
#define rb(a,b,c) for(int a=b;a<=c;++a)
#define rl(a,b,c) for(int a=b;a>=c;--a)
#define niv vector<int>
#define LL long long
#define IT iterator
#define PB(a) push_back(a)
#define II(a,b) make_pair(a,b)
#define FIR first
#define SEC second
using namespace std;
const int INF=0x3f3f3f3f;
typedef pair<int,int> mp;
typedef pair<mp,mp> superpair;
int n;
int a[300000+10];
LL final=0;
LL ret=0;
int main(){
	scanf("%d",&n);
	rb(i,1,n) scanf("%d",&a[i]);
	rb(i,1,n){
		LL cost=ret;
		if(a[i]/2>ret){
			a[i]-=ret*2;
			final+=ret;
			ret=0;
			final+=a[i]/3;
			a[i]%=3;
			ret+=a[i];
		}
		else{
			final+=a[i]/2;
			ret-=a[i]/2;
			ret+=a[i]&1;
		}
	}
	printf("%I64d\n",final);
	return 0;
}
```


---

## 作者：Graph_Theory (赞：0)

~~由于我过于菜了，所以题解区里的一道都看不懂。后来过了一中午想出来了~~ 所以我来写一片通俗一点的题解来给大家食用。

顺便祝大家 `2024 CSP-J/S rp++` 取得不错的分数。

### 思路

给大家模一个样例如下：

```
i:1 2 3 4 5
  1 2 4 8 16
a:1 1 4 5 1 
```

首先记录每一组木棍两两结合后有几对，剩下几个，我们可以得出：


```
i:1 2 3 4 5
  1 2 4 8 16
a:1 1 4 5 1 
b:0 0 2 2 1=5
c:1 1 0 1 0
```

接着将每一组多余的都可以与大于该组木棍长度的任意一组木棍的一对进行结合，此时 $ans+1$ 对应的木棍减去 $1$ 可得：

```
i:1 2 3 4 5
  1 2 4 8 16
a:1 1 4 5 1 
b:0 0 1 1 0=2
c:0 0 0 0 0
ans:1
```
注意这里 $b_3$ 和 $b_4$ 都减去的 $1$ 但实际上这里的 $b$ 我们只记录总和，循环时从后往前循环，可以保证不违反规定。

最后的答案就是 $ \frac{b\times2}{3} + ans=2$ 也就是可以组合出两个。

到这里大家应该想问为什么是 $ \frac{b\times2}{3}$ 因为 $b$ 记录的是两两组合后的答案，如果我们将前面小的拆分来补上后面大的，也就是补上一个底边，不难发现此时一定可以用完所有的边，不会存在有大于 $3$ 条边的情况。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 500010
using namespace std;
int n,a[maxn],ans=0,b=0;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=n;i>=1;i--)
    {
        b+=(a[i]/2);
        if(a[i]%2==1 && b) ans++,b--;
    }
    cout<<ans+(2*b/3);
    return 0;
}
```

---

## 作者：SnapYust (赞：0)

# 题目传送门

[Pavel and Triangles](https://www.luogu.com.cn/problem/CF1119E)

# 思路

只要得出结论就很简单了。

我们知道：

$$2^x+2^x=2\times 2^x=2^{x+1}$$

对于所有三角形种类来说：

### （1）等边三角形

显然可以，因为只要小木棍足够，那么两条相同小木棍的长相加一定大于另外一边。

### （2）等腰三角形（顶角 $<60°$）

显然可以，几何知识可知，腰长大于底边长，两块长木棍和一个短木棍一定可以组成一个三角形。

### （3）等腰三角形（顶角 $>60°$）

显然不行，几何知识可知，腰长小于底边长。每条小木棍长度都是 $2$ 的次方数，由上面的等式可推得此种情况不成立。

### （4）普通三角形

显然不行，设长边为 $a$，次长边为 $b$，短边为 $c$，由等式可知，$a$ 至少是 $b$ 的两倍，而 $c$ 小于 $b$，所以 $b+c<a$，此种情况不成立。

### 结论

所以三条木棍能构成三角形当且仅当其中两条木棍长相等并且第三条木棍长小于等于这两条木棍长。

然后进行贪心即可，贪心策略如下：

设当前枚举到 $i$ 位置，那么假设在 $1\rightarrow i-1$ 中有 $x$ 个落单没有组成三角形的木棍，那么先与这 $x$ 个木棍先组成几个三角形，前面的木棍利用完后再组成等边三角形，假设最后还剩了 $a$ 个木棍，那就不去管它，让后面的位置去和这 $a$ 个木棍组成三角形。

OK~

---

