# [ARC122C] Calculator

## 题目描述

Snuke有整数$x$和$y$。最初，$x=0，y=0$。

Snuke可以以任何顺序执行以下四种操作任意次: 

- 操作$1$:将$x+1$。 
- 操作$2$:将$y+1$。 
- 操作$3$:将$x+y$。 
- 操作$4$:将$y+x$。

给你一个正整数$N$。最多做$130$次运算，使$x$的值为$N$。在这里，$y$可以有任何值。

我们可以证明，在这个问题的约束下，存在这样一个运算序列。

## 样例 #1

### 输入

```
4```

### 输出

```
5
1
4
2
3
1```

# 题解

## 作者：lihe_qwq (赞：2)

### 思路

注意到，如果我们给 $x$ 或 $y$ 加 $1$ 后，做 $3$ 与 $4$ 操作，则会额外生成一个斐波那契数列，则我们考虑用若干个斐波那契数列的值拼出 $n$。我们考虑贪心的拼，能减就减，由于斐波那契数列的增长很快，在 $80$ 次操作左右便可以达到 $10^{18}$，所以一定可以在 $130$ 次操作内拼出答案，我们只需要据此构造一组解即可。

### 代码如下

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
#define int long long
const int N=2e6+10;
int n,fei[N],vis[N],tot,mp[N];
bool fl=0;
signed main()
{
    scanf("%lld",&n);
    fei[1]=1;
    for(int i=2;i<=84;i++)
        fei[i]=fei[i-1]+fei[i-2];
    for(int i=84;i;i--)
        while(n>=fei[i])
        {
            vis[++tot]=i;
            mp[i]++;
            n-=fei[i];
        }
    printf("%lld\n",vis[1]+tot-1);
    if(vis[1]%2)    fl=1;
    for(int i=1;i<=vis[1]-1;i++)
    {
        while(mp[vis[1]-i+1])
            printf("%lld\n",(vis[1]-i+1)%2?1:2),mp[vis[1]-i+1]--;
        if(i%2)
        printf("%lld\n",fl?4:3);
        else
        printf("%lld\n",fl?3:4);
    }
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：2)



# [ARC122C] Calculator



## 思路：斐波那契数列

首先明确一点，对于同一个 $N$，操作序列很可能是不唯一的！

如果你愿意枚举的话，那么可以发现以下两个操作序列的结果是一样的。

```Plain Text
4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 4 3 2 4 3 2 4 3
//and
1 4 2 3 1
```


结果都满足 $n=4$（没错上面的那个就是本人写出来的代码跑的，一开始还纳闷，结果模拟后发现结果是一样的！）

接下来我们一边证明次数限制为什么是 $130$，一边解决问题。

我们考虑以下轮换操作：操作 $4\rightarrow3\rightarrow4\rightarrow3\rightarrow\cdots$。假设我们在这里总共进行了 $S$ 次的操作。为了方便起见，我们假设 $S$ 是偶数。

对于每个 $i\ (0\leq i\leq S)$，我们考虑在上述第 $i$ 个操作之后插入操作 $1$ 或 $2$。我们关注以下内容：

- 如果 $i$ 是偶数：执行一次 $1$ 操作将使 $x$ 的最终值增加 $fib(S-i)$。

- 如果 $i$ 是奇数：执行一次 $2$ 操作将使 $x$ 的最终值增加 $fib(S-i)$。

这里，$fib(n)$ 表示斐波那契数，其中 $fib(0)=1$，$fib(1)=1$ 和 $fib(n)=fib(n-1)+fib(n-2)$ 其中 $2\leq n$。

我们考虑到每个 $i$ 总共最多执行一次操作 $1$ 和 $2$。在这种情况下，我们应该选择最大的 $S$，在 $fib(S)\leq 10^{18}$ 的前提下，因为选择更大的 $S$ 没有帮助。计算表明，我们应该选择 $S=86$。

剩下的就是解决将 $N$ 表示为 $fib(S-i)$ 的和的问题。我们可以贪心地解决它：按照 $i$ 的升序，我们应该尽可能使用当前枚举到的值。在这里，我们永远不会同时取 $i$ 和 $i+1$，因为在这种情况下，我们会取 $i-1$（即我们不会同时取 $fib(S-i)$ 和 $fib(S-i-1)$，而取 $fib(S-i+1)$，因为它就是前面两个斐波那契数的和）。因此，我们将总共执行 $1$ 和 $2$ 最多 $S/2+1=44$ 次操作（实际上，最多 $43$ 次）。

因此，我们总共最多将有 $86+44=130$ 的操作。

**Code**

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
using pii = pair<int, int>;
using pll = pair<long long, long long>;
 
const int N = 87;
int fib[N],n;
bool flg[N];
 
signed main () {
	fib[1] = 1;
	for(int i = 2; i < N; i++) fib[i] = fib[i - 1] + fib[i - 2];
	
	cin >> n;
	for(int i = N - 1; i >= 1; i--) {
		if (n >= fib[i]) {
		 	flg[i] = true;
		  	n -= fib[i];
		}
	}
	
	vector<int> ans;
	if (flg[86]) ans.push_back(2);
	for(int i = 1; i <= 43; i++) {
	ans.push_back(4);
	ans.push_back(3);
	if (flg[87 - 2 * i]) ans.push_back(1);
	if (flg[86 - 2 * i]) ans.push_back(2); 
	}
 
	cout << ans.size() << '\n';
  	for(int i=0;i<ans.size();i++)cout<<ans[i]<<'\n';
 	return 0;
}
 
```




---

## 作者：under_the_time (赞：1)

## 题意

> 有两个数 $x,y$，初始 $x=y=0$，可以执行若干次操作，每次操作选择一种：
>
> - $x\gets x+1$；
> - $y\gets y+1$；
> - $x\gets x+y$；
> - $y\gets y+x$。
>
> 给定 $N$，求操作数量在 $130$ 次以内的一组操作方案，使得 $x=N$。
>
> $N\le 10^{18}$。

## 解法

最快增大 $x$ 的方法显然是令 $x=1$ 或 $y=1$，然后 $x\gets x+y,y\gets y+x$ 交替进行，可以发现 $x,y$ 构成斐波那契数列。单纯这么加会导致错过 $N$，考虑在交替相加的过程中插入 $+1$ 的操作。观察到若 $+1$，随着交替相加相加 $k$ 次最终的 $x$ 就会增大斐波那契数列的第 $k$ 项。那就好办了，把 $N$ 拆成若干斐波那契数的和，然后交替过程中预判一下什么时候对谁加一即可。可能有些地方需要分类讨论一下。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 87; // f[86] 后的斐波那契数大于 10^18 没有贡献了
int fib[maxn], n; bool chs[maxn];
signed main() {
	fib[1] = 1;
	for (int i = 2; i < maxn; i ++) 
		fib[i] = fib[i - 1] + fib[i - 2];
	scanf("%lld", &n);
	for(int i = maxn - 1; i >= 1; i --) 
		if (n >= fib[i]) 
		 	chs[i] = 1, n -= fib[i];
	vector<char> ans; bool apr = 0;
	if (chs[maxn - 1]) ans.push_back(2);
	for (int i = 1; i <= (maxn >> 1); i ++) {
		if (apr) ans.push_back(4), ans.push_back(3);
		if (chs[(maxn - 1) - i * 2 + 1]) ans.push_back(1), apr = 1;
		if (chs[(maxn - 1) - i * 2]) ans.push_back(2), apr = 1; 
	} printf("%d\n", ans.size());
	for (auto x : ans) printf("%d\n", x);
 	return 0;
}
```

---

## 作者：Nelofus (赞：1)

摆在这个位置肯定是有通用的简易构造方法的。

想一想怎么样才能快速把数值升到差不多和 $N$ 一个量级，很显然最快的做法就是先令 $x=1,y=1$，然后交替做 $3$ 和 $4$。

在这个过程中 $x$ 和 $y$ 的变化是什么？观察得到这个是斐波那契数列。

那事情就简单了，如果 $N$ 恰好是一个斐波那契数，那么令 $x$ 或 $y$ 之中的一个为 $1$，然后交替这样做就可以凑出 $N$ 了。

进一步扩展到一般的 $N$，它肯定可以被分解成若干个斐波那契数之和。一边交替做，一边加上新的斐波那契数起点即可。

```cpp
constexpr int M = 88;
i64 fib[M];
i64 n;
std::vector<int> Div;
int tag[M][2];

int main() {
#ifdef HeratinoNelofus
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;

	fib[0] = 1, fib[1] = 1;
	for (int i = 2; i < M; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	for (int i = M - 1; i >= 1; i--) {
		if (n >= fib[i])
			n -= fib[i], Div.push_back(i);
	}

	int lst = (Div[0] - 1) / 2 + 1;
	for (const int &x : Div) {
		int p = (x - 1) / 2 + 1;
		if (x & 1) {
			tag[lst + 1 - p][1] = 1;
		} else {
			tag[lst + 1 - p][0] = 1;
		}
	}

	std::vector<int> ope;
	for (int i = 1; i <= lst; i++) {
		ope.push_back(3);
		if (tag[i][0])
			ope.push_back(1);
		ope.push_back(4);
		if (tag[i][1])
			ope.push_back(2);
	}
	ope.push_back(3);
	std::cout << ope.size() << '\n';
	for (const int &x : ope)
		std::cout << x << '\n';
	return 0;
}
```

---

## 作者：Cure_Wing (赞：1)

[AT_arc122_c [ARC122C] Calculator](https://www.luogu.com.cn/problem/AT_arc122_c)

### 思路

这是一道思维含量很高的题。

先考虑正向解题，很容易考虑到此时的瓶颈在于选择方案上，此时我们不知道什么时候才能到达结果，于是陷入了漫长的搜索中......

这个时候考虑把题目反过来，如果知道 $x$ 和 $y$ ，方案 $1$：将 $x$ 减去 $1$；方案 $2$：将$y$ 减去 $1$；方案 $3$：将 $x$ 减去 $y$；方案 $4$：将 $y$ 减去 $x$。能不能将这两个数变为 $0$ 呢？答案是可以的。那么如何确定优秀方案呢？我们为了使步数尽可能的少，此时贪心的想，操作 $3,4$ 用的越多肯定是越好的，此时可分为两种情况：$(x,y)\to\begin{cases}(x-y,x)&(x>=y)\\(x,y-x)&(x<y)\end{cases}$。在 $x$ 或 $y$ 等于 $0$ 时，使用 $1,2$ 将另外一个变为 $0$，这样就可以确定方案了。

但是另外一个问题随之产生了，我们只知道 $x$ ，又不知道 $y$，怎么办呢？

这个时候就可以用随机化了，我们可以一直随机 $y$，验证组合 $(x,y)$ 是否可能是最终结果，直到出现可行解为止。

考虑到 $x$ 有 $10^{18}$ 级别，建议使用 `std::mt19937_64 rnd(std::random_device{}());`(`#include<random>`) 进行随机。

时间复杂度 $\mathcal{O}(?)$，但是有保证，因为使 $x=n$ 的方案有很多种，相对应的 $y$ 值也很多。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<random>
using std::cin;using std::cout;
std::mt19937_64 rnd(std::random_device{}());
long long n;
int len[200],cnt;
inline void dfs(long long x,long long y){//确定方案
	if(cnt>130||(!x)&&(!y)) return ;//方案太长或达到方案
	if(!y){
		len[++cnt]=1;
		dfs(x-1,y);
	}else if(!x){
		len[++cnt]=2;
		dfs(x,y-1);
	}else if(x>=y){
		len[++cnt]=3;
		dfs(x-y,y);
	}else if(x<y){
		len[++cnt]=4;
		dfs(x,y-x);
	}
}
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(long long m=rnd()%n;;m=rnd()%n){//不断随机y
		cnt=0;
		dfs(n,m);
//		printf("%lld %lld\n",n,m);
		if(cnt<=130){//由于确定方案的时候是反向确定的，输出的时候需要倒序。
			cout<<cnt<<'\n';
			for(int i=cnt;i>=1;--i)
				cout<<len[i]<<'\n';
			exit(0);
		}
	}
    return 0;
}
```

---

## 作者：incra (赞：0)

### Sol
[可能更好的阅读体验？](https://www.cnblogs.com/incra/p/18776347)

第一眼想到二进制，但是发现并不好实现。

继续观察题目：如果交替操作 `3` 和 `4`，那么得到的数不难发现是斐波那契数列，同时斐波那契数列有个性质：每一项至多选一次就能凑出所有正整数。

那么有如上性质，我们考虑在相邻的 `3` 和 `4` 操作间插入 `1` 和 `2` 操作，注意到如果在某个位置加上 $1$，我们可以容易求出这个位置的对 $x$ 的最终贡献是斐波那契数列的哪一项。

例如：对于操作序列 `343434`，把操作 `2` 插入到第 $1$ 项，那么这个操作对答案的贡献是经计算是 $8$，也就是斐波那契数列的第 $6$ 项，所以它造成的贡献等价于后面 `3` 和 `4` 的操作数量对应的斐波那契数列的数字。

设 `3` 和 `4` 的总个数为 $len$，且形如 `343434...34` 所以假如我们要加入斐波那契数列的第 $i$ 项：

- 如果 $i$ 是奇数，那么在第 $len-i$ 前插入 $1$。
- 如果 $i$ 是偶数，那么在第 $len-i$ 前插入 $2$。

手摸不难发现这是正确的。
### Code
[Link](https://atcoder.jp/contests/arc122/submissions/63900859)。

---

## 作者：wmrqwq (赞：0)

# 题目链接

[AT_arc122_c [ARC122C] Calculator](https://www.luogu.com.cn/problem/AT_arc122_c)

# 解题思路

## hint1：

考虑构建斐波那契数列来解决问题。

## hint2：

二进制。

## hint3：

考虑如何解除后效性。

## sol：

首先我们考虑如何构建斐波那契数列。

进行 `1,2` 操作中的一个，然后交替进行 `3,4` 操作即可。

一个数字能变成斐波那契的第 $n$ 列，可以在对应二进制位上构建 $1$。

那么我们只需要从大往小枚举需要斐波那契数列中的哪些数字，然后直接构建二进制数列即可，具体构建方式可以查看代码。

# 参考代码

```cpp
ll n;
ll a[110];
bool vis[110];
void _clear(){}
void solve()
{
    _clear();
    cin>>n;
    a[1]=1;
    forl(i,2,86)
        a[i]=a[i-1]+a[i-2];
    forr(i,86,1)
        if(n>=a[i])
            n-=a[i],
            vis[i]=1;
    vector<ll>ans;
    if(vis[86])
        ans.pb(2);
    forl(i,1,43)
    {
        ans.pb(4);
        ans.pb(3);
        if(vis[87-i*2])
            ans.pb(1);
        if(vis[86-i*2])
            ans.pb(2);
    }
    cout<<ans.size()<<endl;
    for(auto i:ans)
        cout<<i<<endl;
}
```

---

## 作者：cyq32ent (赞：0)

考虑使得 $x,y$ 快速增长的方法：先使 $x=y=1$，然后交替用操作 $3$ 和 $4$，发现 $x,y$ 为 $F_n$（斐波那契数）。假如我们确定了这样一个操作序列：`1234343434343..`，然后我们在之间插入一个操作 $1$ 或 $2$，发现这个行为对答案的贡献也是 $F_n$。所以只需要把 $N$ 拆分成若干 $F_n$ 之和即可。时间复杂度为 $O(\lg N)$。

```cpp
#include<iostream>
using namespace std;
int64_t N,f[150]={0,1},c[89],a,i=1,k;
int main(){
	cin>>N;
	for(;++i<89;)f[i]=f[i-1]+f[i-2];
	for(i=89;--i;)if(N>=f[i])N-=f[i],c[i]++;
	for(i=0;++i<45;){
		if(a)f[++k]=4,f[++k]=3;
		if(c[89-i*2])f[++k]=a=1;
		if(c[88-i*2])f[++k]=a=2;
	}cout<<k<<endl;
	for(i=0;++i<=k;)cout<<f[i]<<endl;
}
```

---

## 作者：FutureSnow (赞：0)

### 简要题意：

给定 $n$，有一个数对 $(x, y)$，初始时 $x = y = 0$，可以进行两种操作，第一种是给其中任意一个数 $+1$，另外一个操作是将 $x$ 赋值为 $x + y$ 或将 $y$ 赋值为 $x + y$。请构造一种操作方案使 $x = n$。所给出的方案中操作数必须小于 $130$。

### 思路：

考虑最终状态为 $(n, p)$，则不难想到 $n$ 可以表示为 $n = kp + p$（最后一步的操作）。想办法求出 $k$，我们可以列方程：
$$\frac{kp + p}{p} = \frac{1}{k}$$

等价于

$$k + 1 = \frac{1}{k}$$

解得 

$$k = \frac{\sqrt{5} - 1}{2}$$

也就是说，$(n, \frac{n(\sqrt{5} - 1)}{2})$ 一定可以是最终状态。考虑根据最终状态推出之前的状态，我们使用更相减损法，设当前状态为 $(x, y)$，如果 $x > y$，则将状态变为 $(y, x - y)$，如果 $x < y$，则将状态变为 $(x, y - x)$。如果某一个数为 $0$，则将另一个数一直 $-1$，直到两个数都为 $0$ 为止。这样我们就能得到操作方案。

考虑到 $\frac{n(\sqrt{5} - 1)}{2}$ 不一定是整数，强转成整数会有误差，设 $m = \frac{n(\sqrt{5} - 1)}{2}$，我们试验 $[m - 5, m + 5]$ 内的所有整数，其中一定有符合要求的整数。

```cpp


#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
int a[150000], cnt = 0;

void work(int x, int y){
	if(!x){
		while(y && cnt <= 130){
			y--;
			a[++cnt] = 2;
		}	
		return;
	}
	if(!y){
		while(x && cnt <= 130){
			x--;
			a[++cnt] = 1;	
		}
		return;
	}
	if(x < y){
		work(x, y - x);
		a[++cnt] = 4;
	}
	else{
		work(x - y, y);
		a[++cnt] = 3;
	}
}

signed main (){
	cin >> n;
	int p = (double)((sqrtl(5.0) - 1.0) * (double)n / 2.0);
	for(int i = max(p - 5, (int)0); i <= p + 5; i++){
		work(n, i);
		if(cnt > 130){
			cnt = 0;
			continue;
		}
		cout << cnt << endl; 
		for(int j = 1; j <= cnt; j++){
			cout << a[j] << endl;
		}
		break;
	}
	return 0;
}
```

---

