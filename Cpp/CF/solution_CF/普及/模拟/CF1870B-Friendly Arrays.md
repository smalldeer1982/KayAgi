# Friendly Arrays

## 题目描述

给你一个长度为 $n$ 的数组 $a$，一个长度为 $m$ 的数组 $b$。你可以进行若干次操作：选出 $b$ 中的任意一个元素 $b_j$，然后令所有 $a$ 中的元素 $a_i$ 变为 $a_i | b_j$。

请你求出若干次操作后，数组 $a$ 所有元素的**异或和**的最小值与最大值。

## 说明/提示

$1 \leq t \leq 10^4$，$1 \leq n, m \leq 2 \times 10^5$，$0 \leq a_i, b_i \leq 10^9$。

## 样例 #1

### 输入

```
2
2 3
0 1
1 2 3
3 1
1 1 2
1```

### 输出

```
0 1
2 3```

# 题解

## 作者：jr_inf (赞：3)

## 翻译
给出长度为 $n$ 的序列 $a$ 和长度为 $m$ 的序列 $b$，选出 $b$ 中的任意个数（可以不选），让 $a$ 的每个数都或上它们，求 $a_1 \oplus a_2 \oplus \dots \oplus a_n$ 的最大值和最小值。

## 思路
令 $x=a_1 \oplus a_2 \oplus \dots \oplus a_n$。

当 $m=1$ 时，如果选择 $b_1$，每个 $a_i$ 在 $b_1$ 每位为 $1$ 的二进制位上也为 $1$，此时 $x$ 在这些位上的值取决于 $n$ 的奇偶性（$n$ 个 $1$ 异或）。取消 $m$ 的限制，可以发现，每多取一个 $b_i$，$x$ 只会不断变大或变小。

当 $n$ 为偶数时，$x$ 会不断变小，全部不选时值最大，全选时值最小；

当 $n$ 为奇数时，$x$ 会不断变大，全选时值最大，全部不选时值最小。

code：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=2e5+10;
int t,n,m,a[N],b[N],suma,sumb;
signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		suma=sumb=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),suma^=a[i];
		for(int i=1;i<=m;i++)scanf("%d",&b[i]),sumb|=b[i];
		if(n%2)printf("%d %d\n",suma,suma|sumb);
		else printf("%d %d\n",(suma|sumb)-sumb,suma);
	}
}
```


---

## 作者：UncleSam_Died (赞：2)

## 前言
这是一道大水题~~但我还是想了很久~~，主要考查选手对于位运算的理解。

## 正文
### 题目大意
已知有一个长度为 $n$ 的序列 $a$ 和一个长度为 $m$ 的序列 $b$，现在你可以选取任意的一个 $b_j$ 满足 $1\leq j\leq m$，并把**所有的**满足 $1\leq i\leq n$ 的 $a_i$ 和 $b_j$ 做按位或运算。已知变量 $x=a_1 \oplus a_2 \oplus   \dots \oplus a_n$，请分别求出 $x$ 的最小值和最大值。
#### 解题思路
我们可以把 $a$ 数组转化成二进制后近似的看作一个二维数组。易证，对于每一个 $b$ 数组中的元素，该元素可以把与它每一位相对应的且元素该位为 $1$ 的 $a_i$ 的这一位全部转化为 $1$，如下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/5kjtbn7e.png)
由此可以知道，对于 $n$ 为偶数的 $a$ 数组，其 $x$ 的最大值为原本数组中所有元素的异或和，最小值为数组中的元素对于 $b$ 数组中的所有元素的按位或运算之和的按位或的值的异或和；同理，当 $n$ 为奇数时，最大值为运算后的异或和，最小值为原来的元素的异或和。
#### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline char gc() {
	static char buf[1 << 14], * p1 = buf, * p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 14, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(int& x) {
	x = 0; int f = 1; char ch = getchar();
	while (ch < '0' || ch>'9') { if (ch == '-') f = -f; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
	x = (f == -1 ? -x : x); return;
}
inline void put(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) put(x / 10);
	putchar(x % 10 + '0'); return;
}inline void write(int x) { put(x); putchar('\n'); }
#define N 200005
int n,m,ans,mint,maxt;
int a[N],b[N];
inline void work(){
	read(n),read(m);
	for(int i=1;i<=n;i++)
		read(a[i]);
	for(int i=1;i<=m;i++)
		read(b[i]);
		maxt=a[1];
	for(int i=2;i<=n;i++){
		maxt^=a[i];
	}mint=maxt;
	if(n%2==0){
		int huo=0;
		for(int i=1;i<=m;i++)
			huo|=b[i];
		mint=(a[1]|huo);
		for(int i=2;i<=n;i++){
			mint^=(a[i]|huo);
		}
	}else{
		int huo=0;
		for(int i=1;i<=m;i++){
			huo|=b[i];
		}maxt=a[1]|huo;
		for(int i=2;i<=n;i++){
			maxt^=a[i]|huo;
		}
	}
	put(mint),putchar(' '),write(maxt);
}
int main() {
	int T;read(T);
	while(T--) work();
	return 0;
}
```

---

## 作者：OIerBoy (赞：2)

# Sol
一道大水题。

这道题解法非常的套路，我们需要对于处理按位或和按位异或时，首先就要把数拆成二进制的形式去考虑。

首先我们需要简单了解一下按位或和按位异或的运算规则：

- 按位或，对于两个数每一位，只要有一个是 $1$ 结果就是 $1$，只有当两个都是 $0$ 是结果才为 $0$。

- 按位异或，对于两个数每一位，如果两位相同即为 $0$，两位不同即为 $1$。

知道这些已经可以做这道题了，我们就可以考虑贪心了。

我们的贪心要做一个小小的分讨：

- 当 $n\equiv0\pmod{2}$ 时，每对 $b_i$ 做一次处理，$b_i$ 中为 $1$ 的位在 $a_i$ 之中就都为 $1$ 了。而由于 $1$ 的个数是偶数个，异或结果就只能为 $0$，这很明显答案单调不增。所以最大答案就是不进行任何的操作，而最小答案则是对每一个 $b_i$ 都进行一次操作，这样 $b_i$ 中含 $1$ 的位数在答案中就都是 $0$。

- 当 $n\equiv1\pmod{2}$ 时，而由于 $1$ 的个数是奇数个，异或结果就为 $1$，这很则是答案单调不减。所以最小答案不进行任何的操作，最大答案就每一个 $b_i$ 都进行一次操作，这样 $b_i$ 中含 $1$ 的位数在答案中就都是 $1$ 了。

这样我们就解决了这道题，具体细节请看代码。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(long long i=j;i<=k;++i)
#define FoR(i,j,k) for(long long i=j;i^k;++i)
#define FOR(i,j,k) for(long long i=j;i>=k;--i)
using namespace std;
#define N 200005
#define Mod 998244353
int T,n,m,ans1,ans2,k;
int a[N],b[N];
int x[40];
void er(int a){
    int tot=0;
    while(a){
        tot++;
        if(a&1)x[tot]=1;
        a>>=1;
    }
}
signed main(){
    cin>>T;
    while(T--){
        mem(x,0);
        ans1=ans2=0;
        cin>>n>>m;k=n%2;
        For(i,1,n)cin>>a[i];
        For(i,1,m)cin>>b[i];
        For(i,1,m)er(b[i]);
        For(i,1,n)ans1^=a[i];
        For(i,1,35)ans2+=x[i]*pow(2,i-1);
        if(k)cout<<ans1<<" "<<(ans2|ans1)<<endl;
        else cout<<(~ans2&ans1)<<" "<<ans1<<endl;
    }
    return 0;
}
```

---

## 作者：Endline (赞：2)

# CF1870B 题解
## 题意

输入两个数组 $a$ 和 $b$，每次可以选择一个 $b_j$ 把所有的 $a_i\leftarrow a_i\operatorname{or}b_j$，可以进行无限次操作，求操作完后最大的 $a$ 的异或和、最小的 $a$ 的异或和。

## 做法

注意到对于一个操作的 $b_j$，若 $b_j$ 上的某一位是 $1$，那么所有的 $a_i$ 的这一位都一定会变为 $1$，并且无法通过别的操作重新变成 $0$，那么进行操作后：

- 若 $n$ 为偶数，那么异或和的这一位最后一定会变成 $0$，会使其变小（或不变）。

- 若 $n$ 为奇数，那么异或和的这一位最后一定会变成 $1$，会使其变大（或不变）。

这样，我们将所有 $b_j$ 都对 $a_i$ 进行操作，那么答案就会是：

- 若 $n$ 为偶数，那么最大异或和就是原始异或和，最小异或和是操作后的异或和。

- 若 $n$ 为奇数，那么最大异或和就是操作后的异或和，最小异或和是原始异或和。

复杂度 $\Theta(n)$，随便过。

附上代码：

```cpp
#include<bits/stdc++.h>
#define MAXN 200002
using namespace std;
int T;
int n,m,sum,sumb,suma;
int a[MAXN],b[MAXN];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        sum=sumb=suma=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            sum^=a[i];
        }
        for(int i=1;i<=m;i++)
        {
            cin>>b[i];
            sumb|=b[i];
        }
        for(int i=1;i<=n;i++)
            a[i]|=sumb,suma^=a[i];
        if(n&1)swap(sum,suma);
        printf("%d %d\n",suma,sum);
    }
    return 0;
}
```

---

## 作者：zhangyaiwei (赞：1)

#### 题外话
[也许更好的阅读体验](https://www.luogu.com.cn/blog/684245/solution-cf1870b)

------------
在题解的开始，让我们先把题意转化一下，设选出的数的按位或合为 $x$，则我们要求  $(a_1\operatorname{or}x)\oplus\left(a_2\operatorname{or}x\right)\oplus\ldots\oplus(a_n\operatorname{or}x)$ 的最大最小值。

先讲一个重要结论，$x$ 中为 1 的二进制位在 $a_i \operatorname{or} x$ 中肯定也为 1。

我们先按照 $n$ 的奇偶性进行讨论，至于为什么，我等下会讲。

#### 首先考虑 $n$ 是偶数的情况：

由于 $n$ 是偶数，所以异或和在 $x$ 为1的二进制位上肯定为 0。为什么呢？根据上面提到的重要结论，$x$ 中为 1 的二级制位在 $a_i \operatorname{or} x$ 中肯定也为 1 ，而这样的 $a_i \operatorname{or} x$ 有 $n$ 个，偶数个为 1 的二进制位异或起来不就是 0 了吗？

那剩下的部分呢？由于剩下的部分不会被 $x$ 影响，直接把他们异或在一起就好了。

总结一下,在 $n$ 为偶数的情况下
$$ (a_1\operatorname{or}x)\oplus\left(a_2\operatorname{or}x\right)\oplus\ldots\oplus(a_n\operatorname{or}x)=\left(a_1\oplus a_2\oplus\ldots\oplus a_n\right)\operatorname{and}\left(\sim x\right) $$
- 其中 $\left(a_1\oplus a_2\oplus\ldots\oplus a_n\right)$ 表示不会被 $x$ 影响的部分，由于异或仅影响一位，所以直接把 $a_i$ 异或在一起就好了，剩下的被 $x$ 影响的部分就只需要交给 $\operatorname{and}\left(\sim x\right) $ 就好了~。（$\sim x$ 表示按位取反）

接下来再考虑求最大值最小值。

由于 $\operatorname{and}\left(\sim x\right)$ 只能去掉 1，则最小值希望去掉尽可能多的 1，所以 $x$ 是所有 $b_i$ 的按位或和；最大值希望保留最多，所以 $x=0$。

#### 而奇数情况也简单：
奇数部分和偶数部分的不同就在于奇数个为 1 的二进制位异或起来为 1，所以我们只要把将 $x$ 中为 1 的二级制位在答案中替换为 0 的 $ \operatorname{and} \left( \sim x \right) $ 改成替换为 1 的 $\operatorname{or}x$ 就好了

综上所述，可得在 $n$ 为奇数的情况下
$$(a_1\operatorname{or}x)\oplus\left(a_2\operatorname{or}x\right)\oplus\ldots\oplus(a_n\operatorname{or}x)=\left(a_1\oplus a_2\oplus\ldots\oplus a_n\right)\operatorname{or} x$$
- 其中 $\left(a_1\oplus a_2\oplus\ldots\oplus a_n\right)$ 仍表示不会被 $x$ 影响的部分，剩下的被 $x$ 影响的部分就只需要交给 $\operatorname{or}x$ 就好了~。

接下来考虑求最大值最小值。

由于 $\operatorname{or}x$ 只能添加 1，则最小值希望尽可能少添 1，所以 $x=0$；最大值希望加的 1 最多，所以 $x$ 是所有 $b_i$ 的按位或和。

----

#### 喜闻乐见的代码部分
最后，上代码（+贴心注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		int xors=0,ors=0;
		//xors表示a的异或和，ors表示b的按位或和
		for(int i=1;i<=n;i++){
			cin>>a;
			xors^=a;
		}
		for(int i=1;i<=m;i++){
			cin>>b;
			ors|=b;
		}
		if(n%2==0){
			cout<<(xors&(~ors))<<" "<<xors<<endl;
			//当n为偶数时，最小值希望去掉尽可能多的1("operatorname{and}(~ors)")；最大值希望保留最多("operatorname{and}(~0)")，由于operatorname{and}(~0)不会带来变化，所以省略
		}
		else{
			cout<<xors<<" "<<(xors|ors)<<endl;
			//当n为奇数时，最小值希望尽可能少添1("|0")，由于|0不会带来变化，所以省略；最大值希望加的1最多("|ors")
		}
	}
} 

```
PS:在输出的时候一定一定要注意带好括号，尤其是使用cout时，位运算的神奇优先级会让你的代码原地升天。

---

## 作者：copper_ingot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1870B)

我们考虑 $n$ 的奇偶性。

当 $n$ 为奇数时，如果想让所有数的异或和最大，应该把所有能或上的全部或上。

为什么呢？

因为如果或上一个数，那么所有数与这个数的所有 $1$ 位对应的位置都会变成 $1$。

这个位上总共会有 $n$ 个 $1$。

因为 $n$ 是奇数，所以异或之后是 $1$。

想让所有数的异或和最小，应该什么也不做。

反之，当 $n$ 是偶数时，或上的位会有偶数个 $1$，会全部消掉变成 $0$。

所以当 $n$ 是偶数时，想让所有数的异或和最大，应该什么也不做；想让所有数的异或和最小，应该或上所有数。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, a[200001], b[200001], ans, ans1, ans2;
int main(){
	cin >> t;
	while (t--){
		cin >> n >> m;
		ans = ans1 = ans2 = 0;
		for (int i = 1; i <= n; i++){cin >> a[i]; ans1 ^= a[i];}
		for (int i = 1; i <= m; i++){cin >> b[i]; ans2 |= b[i];}
		for (int i = 1; i <= n; i++) ans ^= (a[i] | ans2);
		if (n % 2) cout << ans1 << " " << ans << endl;
		else cout << ans << " " << ans1 << endl;
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

有意思的一题。

但应该可以算作诈骗题。

如果 $n$ 是奇数，所有数都或一个数 $b_i$ 就相当于把 $a_i$ 是 $1$ 的部分变成 $1$，那么异或之后就是 $1$ 了，可以说，当 $n$ 是奇数的时候，整体或上任何一个数是让答案不劣的。简单地说，本来是 $1$ 的地方或上之后还是 $1$，是 $0$ 的地方，如果 $b_i$ 在这一位是 $1$，那么答案变成 $1$。

那么，有了上面的结论，所有 $a_i$ 异或起来就是 $n$ 为奇数的最小值了。

$n$ 为偶数其实是同理的。或上 $b_i$ 就相当于把答案的这些部分变成 $0$，答案一定不变优，因此，全部 $a_i$ 异或是 $\max$，或上 $b_i$ 再异或是 $\min$。

不用分类讨论，两个答案求出来取 $\min$ 和 $\max$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int T, n, m, a[N], b[N], ans1, ans2, tem;
inline void solve(){
	ans1 = ans2 = tem = 0;
	for(int i = 1; i <= m; i++) tem |= b[i];
	for(int i = 1; i <= n; i++){
		ans1 ^= a[i] | tem;
		ans2 ^= a[i];
	}
	if(ans1 > ans2) swap(ans1, ans2);
	printf("%d %d\n", ans1, ans2);
}
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		solve();
	}
	return 0;
}
/*
1
3 1
1 1 2
1
*/
```

[评测链接](https://codeforces.com/contest/1870/submission/237121279)

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1870B)
### 这道题是思维题
先假设 $a$ 数组中的元素个数，即题目中的 $n$ 为奇数，则异或和的的最大值为 $a$ 数组或 $b$ 数组的所有元素，最小值为 $a$ 数组。
### 证明：
当用 $b$ 数组中的一个元素或 $a$ 数组的所有元素时，$a$ 数组中的每一个数的对应的 $b$ 的位均会变为1。所以当 $n$ 为奇数时，最终异或和的结果为 1，结果最大。而想要结果最小，就一次或操作也不做。

同理，当 $n$ 为偶数时，一次或操作也不做的结果最大，执行所有操作的结果最小。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[200005],b[200005],ans1,ans2,ans3;
int main(){
	scanf("%d",&t);
	for(int tt=1;tt<=t;tt++){
		ans1=ans2=ans3=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=m;i++){
			scanf("%d",&b[i]);
			ans1=ans1|b[i];//先把所有b数组的元素或在一起
		}
		for(int i=1;i<=n;i++){
			ans2=ans2^a[i];//一次或操作也不做
			ans3=ans3^(a[i]|ans1);//执行所有或操作
		}
		printf("%d %d\n",min(ans2,ans3),max(ans2,ans3));//这里可以以奇偶分类讨论，但是我这里直接把最小值放前面，最大值放后面，更好理解。
	}
	return 0;
}
```

---

## 作者：guozhe6241 (赞：0)

模拟赛时过的一道题，看了大佬的题解，感觉不用那么麻烦。

# 题目传送门

[CF1870B](https://www.luogu.com.cn/problem/CF1870B)

# 题意

给你一个长度为 $n$ 的数组 $a$，一个长度为 $m$ 的数组 $b$。你可以进行若干次操作：选出 $b$ 中的任意一个元素 $b_j$，然后令所有 $a$ 中的元素 $a_i$ 变为 $a_i \operatorname{or} b_j$（或运算）。请你求出若干次操作后，数组 $a$ 所有元素的异或和的最小值与最大值。此处的“异或和”是指进行操作后，求 $a_1 \operatorname{xor} a_2 \operatorname{xor} \dots \operatorname{xor} a_n$ 的最大值和最小值。

# 思路

思路很简单。最小值就是异或奇数的情况。最大值是不异或的情况。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int t,n,m;
int a[maxn],b[maxn];
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		int ansmin=0,minnn=0,minx=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=m;i++){
			cin>>b[i];
			minx|=b[i];
		}
		for(int i=1;i<=n;i++){
			minnn^=a[i];
			ansmin^=(a[i]|minx);
		}
		cout<<min(ansmin,minnn)<<" "<<max(ansmin,minnn)<<endl;
	}
	return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/133243969)

---

## 作者：nj_peak (赞：0)

# Friendly Arrays
比赛时切的一道题。
# 题目大意
给你一个长度为 $n$ 的数组 $a$，一个长度为 $m$ 的数组 $b$。你可以进行若干次操作：选出 $b$ 中的任意一个元素 $b_j$，然后令所有 $a$ 中的元素 $a_i$ 变为 $a_i | b_j$。

请你求出若干次操作后，数组 $a$ 所有元素的**异或和**的最小值与最大值。
# 思路
其实很简单将输入进去的 $n$ 进行分类。如果是奇数，则取或为最小，不或为最大。如果是偶数，则或为最大，不或为最小。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=200050;
int a[MAXN],b[MAXN],t,n,m;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		int ans=0;
		for(int i=1;i<=m;i++) cin>>b[i],ans|=b[i];
		int sum=0,res=0;
		for(int i=1;i<=n;i++){
			sum^=a[i];
			res^=a[i]|ans;
		}	
		cout<<min(res,sum)<<" "<<max(res,sum)<<endl;
	}
	return 0;
}
```

---

