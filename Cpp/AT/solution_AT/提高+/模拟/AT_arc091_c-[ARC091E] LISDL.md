# [ARC091E] LISDL

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc091/tasks/arc091_c

$ 1,2,...,N $ を並べ替えてできる列であって、以下の条件を満たすものがあるかどうか判定し、あればその例をひとつ構成してください。

- 最長増加部分列の長さは $ A $ である
- 最長減少部分列の長さは $ B $ である

## 说明/提示

### 注釈

列 $ P $ の部分列とは $ P $ の要素をいくつか抜き出して元の順に並べてできる列のことを指し、 また、列 $ P $ の最長増加部分列とは、$ P $ の単調増加な部分列の中で列の長さが最大のものを指します。

同様に、列 $ P $ の最長減少部分列とは、$ P $ の単調減少な部分列の中で列の長さが最大のものを指します。

### 制約

- $ 1\ \leq\ N,A,B\ \leq\ 3\times\ 10^5 $
- 入力はすべて整数である

### Sample Explanation 1

$ {2,4,5} $ が最長増加部分列の一例、$ {4,3} $ が最長減少部分列の一例です。

## 样例 #1

### 输入

```
5 3 2```

### 输出

```
2 4 1 5 3```

## 样例 #2

### 输入

```
7 7 1```

### 输出

```
1 2 3 4 5 6 7```

## 样例 #3

### 输入

```
300000 300000 300000```

### 输出

```
-1```

# 题解

## 作者：_always_ (赞：6)

# [ARC091E] LISDL 题解

**题意**：构造一个 $n$ 的**排列**，满足其最长上升子序列长度为 $a$ ，最长下降子序列长度为 $b$，若不存在则输出 `-1`。

## 思路 

**1.边界条件：** 

+ $a>n$ 或 $b>n$ 显然无解。
+ $a+b>n+1$，即最多有一个数同时在最长上升子序列和最长下降子序列中。   
	证明：若同时有两个数（设为 $x$，$y$）同时存在于最长上升子序列和最长下降子序列中，又因为两个数的相对位置无法改变，则 $x<y$ 且 $x>y$，显然矛盾。得证。
    
+ $ab<n$，$a$ 和 $b$ 过小无解，这个无解的证明则与接下来的做法有关。

接下来考虑如何构造出正解。

**2.尝试：**

首先可以先构造出两个序列中的一个，我选择的是最长上升子序列。  
以样例 `5 3 2` 举例：
首先尝试：  
![样例解释1](https://cdn.luogu.com.cn/upload/image_hosting/5e2iomnt.png) 

接下来需要构造最长下降子序列。  
显然不能放在前面，因为 $5$ 和 $4$ 均大于 $1,2,3$ ，会导致最长下降子序列长度增大。  
同样不能放在后面，同理会导致最长上升子序列长度增加。
如果加在中间：  
![样例解释2](https://cdn.luogu.com.cn/upload/image_hosting/eqbmn2u4.png)  

同理，最长上升子序列长度会增加。  
但是这也给了我们一些启发：  
如果最开始的最长上升子序列是由 $3,4,5$ 组成的呢？   
将 $1,2$ 插入中间：  
![样例解释4](https://cdn.luogu.com.cn/upload/image_hosting/bln6lm74.png)  

此时可以发现，因为我们的上升子序列事这个排列里最大的数，不会使最长上升子序列的长度增加，并且插入的数字都比最长上升子序列里的数小，最长下降子序列也可以构造出来。并且，可以插空的位置最多只有 $a$ 个，即使空中有 $a$ 个数构成了上升子序列，长度也不会比 $a$ 大。

当然，这种情况比较普通。
一个较大的 `8 3 3`。

![5](https://cdn.luogu.com.cn/upload/image_hosting/iaqd7td0.png)

理解这个样例后其实做法就很清晰了。   

**3.做法：**

其中每个在最长上升子序列中的数后都有最多 $b-1$ 个数组成的下降的序列，整个排列中有 $a$ 个长度不大于 $b$ 的下降子序列，并且至少有一个长度为 $b$ 的最长下降子序列。当然，因为构造时特意用最大的 $a$ 个数组成最长上升子序列，也并没有使最长上升子序列的长度因为新加入数字而增加。

这时候再看第三种无解情况：排列中最极限的情况是有 $a$ 个长度为 $b$ 的下降子序列组成，如果再添加数就会使两种子序列至少有一个的长度会发生变化。所以 $ab<n$ 时，也就是最极限的情况下都无法将所有数字放进排列，就是无解。

具体细节请看代码。

**4.代码：**

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int n,a,b;

int main(){
	scanf("%d%d%d",&n,&a,&b);
	if((a>n||b>n)||(a+b>=n+2)||((ll)a*b<n)){//此处a,b相乘要强转，否则会溢出
		printf("-1\n");
		return 0;
	}
	int x=0,y=n-a+1;
	int cnt=0,maxn=n-a;
	for(int i=1;i<=a;i++){
		printf("%d ",y);//y是最长上升子序列中的数字
		int p=min(maxn-cnt,b-1);
		int k=x+p;
		while(p--){
			printf("%d ",x+p+1);
			cnt++;
		}
		x=k,y++;
	}
	return 0;
}
```

完结撒花！

---

## 作者：火车司机 (赞：5)

## 简要分析

首先可以得到一个性质：若干个上升子序列按首元素大小递减前后拼接在一起之后，形成的序列的最长下降子序列长度一定为拼接前的上升子序列个数

于是可以不断地取出剩下元素中最大的 $A$ 个所形成的上升子序列拼在当前序列的末尾，直到取出 $B$ 个上升子序列

无解的情况就是取不到 $B$ 个或者取完 $B$ 个还有剩余元素

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
int n, a, b;
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
inline int mnn(int a, int b)
{
	return a < b ? a : b;
}
signed main()
{
	read(n), read(a), read(b);
	if (a + b - 1 > n || a * b < n)
	{
		puts("-1");
		return 0;
	}
	for (ri t = mnn(a, n - b + 1); n > 0; n -= t, --b, t = mnn(a, n - b + 1))
		for (ri i = n - t + 1; i <= n; ++i)
			print(i), putchar(' ');
	return 0;
}
```


---

## 作者：_l_l_ (赞：4)

考虑到当 $a,b$ 太大或者太小的时候会是无解，因此先来考虑怎么处理无解。

首先，当 $a>n$ 或者 $b>n$ 时肯定无解，原因显然。

然后，显然至多只有一个数会存在于 lis 和 lds 中，使用反证，如果存在两个数 $x, y$ 同时存在于 lis 和 lds，不妨设 $x$ 在排列中排在 $y$ 的前面，则因为同时在 lis 中，$x<y$，因为同时在 lds 中，$x>y$，不成立。

因此我们可以发现 $a+b$ 的上限为 $n+1$，超出了就无解。

$a,b$ 过小也会无解，但是我们先尝试构造：

1. 先大胆构造一个 lds 为 $b,b-1,\cdots,1$
2. 我们发现如果在这个 lds 后面继续接一个任意大于 b 的数，则你会发现 lis 已经变成 2 了。
3. 但是问题不大，你可以在后面继续下降，只要最长下降序列不超过 $b$ 就行，这个过程中 lis 的贡献只有从最开始那个 lds 到正在拓展的 lds，因此 lis 依旧为 2。

因此我们直接推出正解，定义数组 $p$ 为每一个 lds 的长度，保证前面的 lds 只能贡献到后面的 lds，因此数组 $p$ 的长度需要为 $a$。

然后因为题面说明了 lds 必须为 $b$，因此所有 $p_i$ 都必须 $\leq b$，而且有一个必须等于 $b$，假设为第一个。

因此问题变为了这样：

> 构造一个数组 $p$，使得：
>
> 1. $\sum p=n$
> 2. $|p|=a$
> 3. $p_1=b$
> 4. $\forall 1\leq i\leq n,p_i\leq b$

构造是显然的，如何将 $p$ 转换为答案可以看代码的输出。

最后看一下 $a,b$ 的下界，当 $p$ 数组所有值都取最大值时，$\sum p=ab$，因此需要保证 $ab\geq n$。

```cpp
#include <cstdio>
using namespace std;
const int MAXN = 300005;
int p[MAXN];
int main() {
	int n, a, b; scanf("%d %d %d", &n, &a, &b);
	if (a > n || b > n) return puts("-1"), 0;
	if (1ll * a * b < n) return puts("-1"), 0;
	if (a + b >= n + 2) return puts("-1"), 0;
	p[1] = b; int pt = n - b;
	for (int i = 2; i <= a; i++) {
		if (b + a - i < pt) p[i] = b, pt -= b;
		else {
			for (int j = i + 1; j <= a; j++) p[j] = 1, pt--;
			p[i] = pt; pt = 0; break;
		}
	}
	for (int i = 1; i <= a; i++) {
		for (int j = pt + p[i]; j > pt; j--) printf("%d ", j);
		pt += p[i];
	}
	return 0;
}
```

---

## 作者：_Imaginary_ (赞：3)

引理：任意 $mn+1$ 个数组成的数列有长度至少为 $m+1$ 的 LIS 或长度至少为 $n+1$ 的 LDS。

BDFS 就有很多的解答。

另外，也显然 LIS 和 LDS 至多有一个元素相同

所以有解当且仅当 $A+B-1\le N\le AB$

接下来构造。

我们先取一个 $AB\sim 1$ 的数列，再每隔 $A$ 项翻转一下。

举例：$A=2\ B=4$ 时就是 $7,8,5,6,3,4,1,2$

接下来删除一些元素使剩下的依然满足条件。

在这个例子中，我们保留 $7,8$ 和 $7,5,3,1$，剩下的随便即可满足题意。

**注意⚠️**：题目要求 $1\sim n$ 的排列，可能要离散化。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll ans[300005];
ll t[300005];
int main()
{
    ll n,a,b; 
    int tot=0;
    scanf("%lld%lld%lld",&n,&a,&b);
    if(n<a+b-1||n>a*b)
    {
        printf("-1");
        return 0;
    }
    ll ta=n-(a+b-1);
    for(ll i=1;i<=a;i++) ans[++tot]=(b-1)*a+i;
    for(ll i=2;i<=b;i++)
    {
        ans[++tot]=(b-i)*a+1; 
        for(ll j=2;j<=min(ta+1,a);j++)
            ans[++tot]=(b-i)*a+j;
        ta-=(a-1);
    }
    memcpy(t,ans,sizeof(t));
    sort(t+1,t+n+1);
    int nz=unique(t+1,t+n+1)-t;
    for(int i=1;i<=n;i++)
    {
        ans[i]=lower_bound(t,t+nz,ans[i])-t;
        printf("%lld ",ans[i]);
    }
    return 0;
}
```

---

## 作者：__Floze3__ (赞：2)

## 思路简介

由于题目要求的是最长上升子序列与最长下降子序列的长度，我们不难想到这样一种构造方式：把这个排列分为 $A$ 个长度至多为 $B$，但至少有一个长度为 $B$ 的连续的下降序列，将这些下降序列按照最大元素升序排列即可。根据这样的构造方式，我们不难得出有解的充要条件：$A + B - 1 \le N \le A \times B$

解释一下这个边界条件：  
- 下界：至少得有一个长度为 $A$ 的上升子序列和一个长度为 $B$ 的下降子序列，且这两个序列至多共用一个元素，总长度为 $A + B - 1$。
- 上界：考虑极限情况，所有 $A$ 个下降子序列的长度均为 $B$，总长度为 $A \times B$。

那么只要按照这样的方法进行模拟即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;

int n, a, b, c[maxn];

int main(){
    cin >> n >> a >> b;
    if (n >= a + b - 1 && n <= (long long) a * b){
        int cnt = n;
        for (int i = 0; i < a; i++) c[i] = 1, cnt--;
        for (int i = 0; i < a && cnt; i++){
            int d = min(b - 1, cnt);
            c[i] += d;
            cnt -= d;
        }
        cnt = 0;
        for (int i = 0; i < a; i++){
            for (int j = c[i]; j > 0; j--){
                cout << cnt + j << ' ';
            }
            cnt += c[i];
        }
    }
    else cout << -1;
    return 0;
}
```

---

## 作者：Angraecum (赞：1)

模拟赛的时候考了这个题，但是脑子是糊的，挂了五个点……

分享一个很暴力的想法，很适合我这种没有思维没有智慧的人，还有感性理解这个做法会容易一些。

---------

我们就看 ``5 3 2`` 这组样例，能很自然地构造出这样一个序列：``3 4 5 1 2``。从这个序列的形态入手，我们可以把它分成 ``3 4 5`` 和 ``1 2``，相当于是把序列分成前面一个连续的上升子段，后面一个上升子段。

也许这样不太明显，再来一组样例 ``8 3 3``，按照上面的思路可以构造出序列 ``6 7 8,3 4 5,1 2``（逗号是我加的），相当于将三个上升子段拼起来，并且这三个上升子段的值是逐渐下降的，也满足了下降子序列长度的限制。当然也可以反过来这样：``3 2 1 6 5 4 8 7``。

那么我们珂以取 $a,b$ 中的较大值来将序列分段，令 $a$ 为较大者，并且先忽略最后一段（还有很多注意的点），那么可以分出 $\lfloor \frac{(n-1)}{a}\rfloor$ 段，记为前 $k$ 段，每一段都是值逐渐减小的上升子段。

然后我们发现，很多情况下最后一段为上升子段时都不能满足下降子序列长度的限制。我们可以这样构造最后一段：设最后一段长度为 $len$，$len=n-k\times a$。现在我们需要最后一段对前 $k$ 段中的最长下降子序列的贡献为 $b-k$，如果 $b-k\le len$，那么直接将最后一段分成对最长下降子序列长度的贡献为 $k$ 的前一段和对最长下降子序列长度没有贡献的后一段。具体而言，对于样例 ``8 4 3``，可以构造出序列 ``5 6 7 8,2 1 3 4``，最后一段中 ``1 2`` 使得最长下降子序列长度变为 $3$，``3 4`` 则无贡献。可以理解为是将 ``1 2 3 4`` 改成了 ``2 1 3 4``。

但是 $b-k>len$ 时只改变最后一段是不够满足长度需求的，我们再去考虑修改倒数第二段。以 ``11 5 4`` 为例，正确的构造方案应是 ``7 8 9 10 11 3 2 4 5 6 1``，就直接把最后一段的构造方法搬到倒数第二段来了，而且最多也只会修改到倒数第二段。

无解情况就是 $a+b>n+1$ 或 $a\times b<n$ 其他题解有详细讲解，不再赘述。

由于是赛时脑子一团糊写的代码，所以非常复杂，对 $a,b$ 还分类讨论了，甚至可能还有点纰漏，建议看看就好。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2*114514,M=1919810;
ll n,a,b;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>a>>b;
	if(a*b<n||a+b>=n+2){
		cout<<-1;
		return 0;
	}
	ll mx=max(a,b),mn=min(a,b);
	ll k=(n-1)/mx;
	if(a>b){
		if(b==1){
			if(a==n){
				for(int i=1;i<=n;++i) cout<<i<<" ";
				return 0;
			}
			else cout<<-1;
			return 0;
		}
		ll lim=n-k*a;
		if(lim<b-k){
			for(int j=1;j<k;++j)
				for(int i=n-j*a+1;i<=n-(j-1)*a;++i)
					cout<<i<<" ";
			for(int i=n-k*a+1;i<=n-(k-1)*a-(b-1-lim);++i) cout<<i<<" ";
			for(int i=n-(k-1)*a;i>=n-(k-1)*a-(b-1-lim)+1;--i) cout<<i<<" ";
			for(int i=lim;i>=1;--i) cout<<i<<" ";
			return 0;
		}
		for(int j=1;j<=k;++j)
			for(int i=n-j*a+1;i<=n-(j-1)*a;++i)
				cout<<i<<" ";
		for(int i=b-k;i>=1;--i) cout<<i<<" ";
		for(int i=b-k+1;i<=n-k*a;++i) cout<<i<<" ";
	}
	else{
		if(a==1){
			if(b==n){
				for(int i=n;i>=1;--i) cout<<i<<" ";
				return 0;
			}
			else cout<<-1;
			return 0;
		}
		ll lim=n-k*b;
		if(lim<a-k){
			for(int j=1;j<k;++j)
				for(int i=b*j;i>=(j-1)*b+1;--i)
					cout<<i<<" ";
			for(int i=b*k-(a-k-lim);i<=b*k;++i) cout<<i<<" ";
			for(int i=b*k-(a-k-lim)-1;i>=b*(k-1)+1;--i) cout<<i<<" ";
			for(int i=n-lim+1;i<=n;++i) cout<<i<<" ";
			return 0;
		}
		for(int j=1;j<=k;++j)
			for(int i=b*j;i>=(j-1)*b+1;--i)
				cout<<i<<" ";
		for(int i=b*k+1;i<=b*k+(a-k)-1;++i) cout<<i<<" ";
		for(int i=n;i>b*k+(a-k)-1;--i) cout<<i<<" ";
	}
	return 0;
}//99163 1000 1000 
```

---

## 作者：__LiChangChao__ (赞：0)

## 思路

由于题目同时限定了最长上升子序列与最长下降子序列的长度，先选择一个角度入手。

我选择从最长上升子序列入手。

如何使最长上升子序列的长度固定？

显然，当一大堆长度均为 $l$ 的上升序列按照第一个元素**从大到小**排列，则组合起来的序列的最长上升子序列的长度为 $l$。

例如：$l=3$，则一个可能的序列为：

$$10,11,12,7,8,9,4,5,6,1,2,3$$


最长上升子序列长度为 $3$。

当然，一部分子序列长度小于 $l$ 也能达到同样的效果：

$$10,11,12,7,8,9,5,6,3,4,1,2$$

那最长下降子序列怎么办呢？

我们构造的时候是按照第一个元素**从大到小**排列，只要我们构造 $B$ 组长度不大于 $A$ 的上升子序列，按照第一个元素从大到小排列，那么最长上升子序列的长度就为 $A$，最长下降子序列的长度就为 $B$。

同时推出无解情况：

* $A+B-1>N$，显然，在这种情况下，$N$ 个根本不够用。
* $A\times B<N$，就像上面所述，我们要构造 $B$ 组长度不大于 $A$ 的上升子序列，在这种情况下，要么增加最长上升子序列的长度，要么增加最长下降子序列的长度。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,j;
int main() {
	cin>>n>>a>>b;
	if(a+b-1>n||1ll*a*b<n)return puts("-1"),0;//无解
	while(n) {
		j=min(a,n-b+1),n-=j,b--;
		for(int i=n+1;i<=n+j;i++)printf("%d ",i);//分组输出
	}
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [ARC091E] LISDL



## 思路

（一种比较无脑的做法）

题面很简单，那么我们怎么样思考呢？

注意，子序列可以不连续。

我们想到，$A,B$ 之间最多有一个元素是重复的。因此，如果 $A+B-1>N$，那么必定无解，同时，如果 $N>A\times B$ 也无解，这个很容易想到。否则我们就要考虑如何构造了。

假设 $N=A+B-1$，那么很好办，我们只需要把 $(B-1)\times2,\dots,4,2$ 放在最后面，前面的按升序排列即可。

例如 $A=5,B=3$ 时，`1 3 5 6 7 4 2` 即可。

或者还有一种方法，我们将 $A\sim 1$ 放在前面，然后 $A+1\sim B-1$ 放在后面，如 `5 4 3 2 1 6 7` 即可。

现在假设 $A\times B≥N>A+b-1$，那么我们来思考一下应该怎么样排列。



首先，我们考虑满足第一个条件，即最长下降子序列长度为 $B$。我们先不管 $A$，那么我们就可以这样构造：从 $1\sim N$ 从小到大每次选择 $B$ 个数字逆序放置。例如 $N=12,B=5$，序列为 `5 4 3 2 1 10 9 8 7 6 12 11`。

可以证明，我们把每 $B$ 个数字看成一个区间，那么后面的区间内的任意一个数字都比前面的区间内的任意一个数字大，所以跨区间不可能会有下降子序列。又由于最长的区间长度为 $B$，则最长下降子序列的长度即为 $B$。



现在我们来考虑 $A$。首先我们发现假设之前我们讨论的区间在序列中有 $k$ 个（不完整的也算），那么它的最长上升子序列长度为 $k$。并且我们认为，其做出贡献的数字是每个区间的最后一个数字。但很明显如果 $\lceil N\div B\rceil <A$，那么 $k<A$。那么我们就需要补充一些升序的数字，于是我们就需要让末尾的一些数字变成升序的。我们要保证，末尾翻转的数字的个数 $d$（注意不是升序的数字个数，因为假设翻转开始的位置 $i$ 恰好是一个区间的开始，那么翻转后 $i$ 与原来的 $i-1$ 也构成上升）与翻转一些数字后完整的区间数量 $k'$ 满足 $k'+d=A$。注意这里要求是完整的区间。

例如 $N=12,B=5,A=4$，序列为 `5 4 3 2 1 10 9 8 7 6 11 12`。

由于本题 $N$ 不大，所以我们直接枚举翻转的开始位置，然后判定即可。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 300005

int a,q[N],b,x,n,y,ans,res,idx,cnt;

void pr(int x){
//	cerr<<"x="<<x<<endl;
	for(int i=b;i;i+=b){
		int j=min(b,n-cnt);
		while(j){
			q[++cnt]=j+i-b;j--;
			if(cnt==n)break;
		}
		if(cnt==n)break;
	}
	sort(q+n-x+1,q+n+1);
	for(int i=1;i<=n;i++)cout<<q[i]<<' ';
}

signed main(){
	cin>>n>>a>>b;
	if(a+b-1>n||n>a*b){
		cout<<-1<<endl;
		return 0;
	}
	for(int i=0;i<=n;i++){//枚举翻转的长度
		if((n-i)/b+i==a){//判定是否可行
			pr(i);
			return 0;
		}
	}
	   return 0;
}
```


[Submission #45199546 - AtCoder Regular Contest 091](https://atcoder.jp/contests/arc091/submissions/45199546)




---

