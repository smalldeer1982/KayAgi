# Kate and imperfection

## 题目描述

Kate has a set $ S $ of $ n $ integers $ \{1, \dots, n\}  $ .

She thinks that imperfection of a subset $ M \subseteq S $ is equal to the maximum of $ gcd(a, b) $ over all pairs $ (a, b) $ such that both $ a $ and $ b $ are in $ M $ and $ a \neq b $ .

Kate is a very neat girl and for each $ k \in \{2, \dots, n\} $ she wants to find a subset that has the smallest imperfection among all subsets in $ S $ of size $ k $ . There can be more than one subset with the smallest imperfection and the same size, but you don't need to worry about it. Kate wants to find all the subsets herself, but she needs your help to find the smallest possible imperfection for each size $ k $ , will name it $ I_k $ .

Please, help Kate to find $ I_2 $ , $ I_3 $ , ..., $ I_n $ .

## 说明/提示

First sample: answer is 1, because $ gcd(1, 2) = 1 $ .

Second sample: there are subsets of $ S $ with sizes $ 2, 3 $ with imperfection equal to 1. For example, $ \{2,3\} $ and $ \{1, 2, 3\} $ .

## 样例 #1

### 输入

```
2```

### 输出

```
1```

## 样例 #2

### 输入

```
3```

### 输出

```
1 1```

# 题解

## 作者：gyh20 (赞：15)

经 dalao 不要叫我比赛 提议，进行了一些修改。

这可能是最水的 F 了。

先证明一些东西：

接下来的 $a,b$ 都指数列中存在的两个数，且 $a>b$。

$1.$如果 $a \bmod b=0$，那么删去 $a$ 一定比删去 $b$ 更优。

$2.$如果 $a$ 存在在数列中，那么 $a$ 的约数全部在数列中（反证法，见第一条）。

$3.$如果 $\gcd(a,b)=c$，那么 $c$ 一定存在（见第二条）

$4.$一个数的集合的答案即为拥有最大的非自己约数的数。

证明：

由第三条得出，答案一定为自己的一个约数。

由第二条得出，这个最大非自己约数一定是对于自己来说最大的。

所以，埃氏筛求出每个数的最大约数，排序即可（比 C,D 简单多了）。（早知道先做 F 的）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,b[500002],m,t;
int main(){
	n=read();
	for(re int i=1;i<=n;++i)for(re int j=i+i;j<=n;j+=i)b[j]=i;
	sort(b+1,b+n+1);
	for(re int i=2;i<=n;++i)printf("%d ",b[i]);
}
```
你没看错，就这么简单。


---

## 作者：BFqwq (赞：6)

为什么我没打的 div2 就水成这个样子啊。。。

不妨假设这个 $n$ 很大。显然，优先加入 $n$ 以下的质数是最优的。

那么质数加完之后呢？我们通过模拟发现加入 $4$ 最优。此时答案为 $2$。

然后我们加入 $6,9$，此时答案为 $3$。

然后我们加入 $8$，此时答案为 $4$。

然后我们加入 $10,15,25$，此时答案为 $5$。

我们发现了什么？

**在最优状况下加入一个数之后的答案就是这个数除以它的最小质因子**。

然后我们想起，线性筛的时候我们要记录最小因子。

因此我们可以在线性筛的同时记录答案。

然后我们直接将答案排序输出即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200],str[200];int tt;
inline void print(int x,char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
int pri[500050];
int vis[500050];
int val[500050];
int n;
void xxs(int lim){
    for(int i=2;i<=lim;i++){
		if(!vis[i])pri[++pri[0]]=vis[i]=i,val[i]=1;
		for(int j=1;j<=pri[0]&&pri[j]<=vis[i]&&i*pri[j]<=lim;j++){
			vis[i*pri[j]]=pri[j];
			val[i*pri[j]]=i;
		}
	}
}
signed main(){
	n=read();
	xxs(n); 
	sort(val+1,val+1+n);
	for(int i=2;i<=n;i++){
		print(val[i],' ');
	}
	return 0;
}
```


---

## 作者：AutumnKite (赞：5)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

考虑依次求出 $I_2,I_3,\cdots,I_n$。

开始时集合大小为 $1$，我们强制集合中只包含 $1$。我们贪心地往集合内加入元素。

由于我们需要使集合中两两 $\gcd$ 的最大值最小，一开始我们一定是考虑依次加入所有质数。

加入完所有质数后，我们不可能再保证答案为 $1$，我们考虑放宽限制，使得两两 $\gcd$ 的最大值为 $2$。

显然，我们可以加入 $4=2\times 2$，但不可以加入 $6=2\times 3,8=2\times 4,\cdots$。

然后我们考虑使得最大值为 $3$，那么我们可以加入 $6=2\times 3,9=3\times 3$，但不能加入 $12=4\times 3,\cdots$。

接下来考虑使得最大值为 $4$，我们可以加入 $8=2\times 4$，可是我们不能加入 $12=3\times 4$，因为之前已经加入了 $6$。

那么什么时候可以加入 $12$？在我们枚举最大值为 $6$ 时才可以加入 $12$。

再往后模拟若干次，大胆猜想，一个数 $x$ 会在枚举最大值为 $x$ 的最大真因子（即不等于本身的因子）时被加入集合。

直接使用欧拉筛求出 $2$ 到 $n$ 每个数的最大真因子即可。

时间复杂度 $O(n)$。

（做题全靠猜结论.jpg）

### 代码

```cpp
const int N = 500005;

int n, c[N];
int cnt, p[N], vis[N], minp[N];

void solve() {
	read(n);
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			p[++cnt] = i;
			minp[i] = i;
		}
		for (int j = 1; j <= cnt && 1ll * p[j] * i <= n; ++j) {
			vis[i * p[j]] = 1;
			minp[i * p[j]] = p[j];
			if (i % p[j] == 0) {
				break;
			}
		}
	}
	for (int i = 2; i <= n; ++i) {
		++c[i / minp[i]];
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= c[i]; ++j) {
			print(i, ' ');
		}
	}
	putchar('\n');
}
```

---

## 作者：ix35 (赞：3)

不会什么筛法的解，写一个暴力模拟。

考虑 $I_n$，它一定是 $1,\ldots,n$ 中某两个数的 GCD，也就是 $I_n$ 在 $1,\ldots,n$ 中有至少两个倍数，所以 $2I_n\leq n$，则 $I_n$ 取最大值时有 $I_n=\lfloor\dfrac{n}{2}\rfloor$。

接下来我们希望 $I_{n-1}$ 尽量小，那么 $I_n$ 和 $2I_n$ 中至少要干掉一个，显然干掉 $2I_n$ 更优（用决策包容性易证）。

所以我们模拟这个删除过程即可。

设定一个指针 $cur$，一开始指向 $\dfrac{n}{2}$，当 $cur,2cur,3cur,\ldots$ 只剩一个没有删除时，就令 $cur=cur-1$，也就是指针左移一位，否则我们就依次删除 $2cur,3cur,\ldots$ 中还没被删除的元素，过程中顺便倒序记录答案。

时间复杂度为 $O(nH_n)=O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=500010;
int n,cp,cur,np,ans[MAXN],vis[MAXN];
void del () {
	while (1) {
		while (np<=n&&vis[np]) {np+=cur;}
		if (np>n) {cur--;np=2*cur;}
		else {
			ans[cp--]=cur,vis[np]=1;
			break;
		}
	}
	return;
}
int main () {
	scanf("%d",&n);
	cp=n,cur=n/2,np=(n/2)*2;
	for (int i=1;i<=n-1;i++) {del();}
	for (int i=2;i<=n;i++) {printf("%d ",ans[i]);}
	return 0;
}
```


---

## 作者：__stick (赞：1)

## 题意
对于每个 $k\in[2,n]$ 解决以下问题：

从 $[1,n]$ 中选出 $k$ 个数，设集合为 $S$，使得 $\max\limits_{a,b\in S,a\neq b}\gcd(a,b)$  最小。

## 思路

从小的情况想起，想要这个鬼东西最小，则最好的情况肯定是选择的所有数互质，则最多可以选择所有质数个（容易发现选择其他的一定不会更优）。

这时候我们就能隐隐约约猜到一个性质了，那就是我们选一个数之前，他的所有约数（除了自己）一定都要被选择，否则就不如选择这个没有被选择的约数。

因为无论其他数长什么样子，容易发现，如果 $a|b$：
$$
 \forall x\in N \gcd(a,x)\le \gcd(b,x)
$$

这样的话我们的选择方式就一定是正确的。

然后我们加入一个数的时候，因为其约数都已经完全加入了，所以其对结果的贡献一定就是最大的那个约数，而这里按这个最大约数从小到大加入即可。

实现起来不难，可以使用线性筛筛出来最小质因子，除以这个数就是最大约数。

然后使用桶排，复杂度就是 $O(n)$。
## code
```cpp
const int MAXN=5e5+10;
int sum[MAXN],cnt,p[MAXN],low[MAXN];
bool is[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(2);
	int n;
	cin>>n;
	for(int i=2;i<=n;i++)
	{
		if(!is[i])p[++cnt]=i,sum[1]++,low[i]=i;
		else sum[i/low[i]]++;
		for(int j=1;j<=cnt;j++)
		{
			int u=p[j]*i;
			if(u>n)break;
			is[u]=1;
			low[u]=p[j];
			if(i%p[j]==0)break;
		}
	}
	for(int i=1;i<=n;i++)while(sum[i]--)cout<<i<<' ';
	return 0;
} 
```


---

## 作者：abcdeffa (赞：0)

这里给出一个不需要脑子的俩 $\log$ 做法。

首先肯定是先把 1 和所有 $n$ 以内的质数加进来。

我们对每个还没加进所选集合的数 $i$ 维护一个值 $v_i$，表示若将 $i$ 加进来，会让 $\gcd$ 的最大值变成什么。每加进来一个数，我们就用这个数来更新其他数的 $v_i$。

我们可以用每次选取 $v_i$ 最小的位置加进来。但是若在每次更新其他位置的 $v_i$ 时，都进行一次删除和插入操作，虽然可以用 set 快速维护，但是常数非常大。

于是我们转而考虑先不删除，并转而用一个小根堆维护，每次取堆顶。堆中的每个元素 $(\text{id}, v)$ 包含了位置和该位置被加入堆时的 $v$ 值。如果我们发现，这个 $v$ 值并非真实值，就一直删除堆顶，直到满足要求为止。

但是每次更新时都插入会使得堆中元素特别多，实际运行效率还是比较低下，于是我们考虑做进一步优化，我们在更新 $v$ 值后并不将其插入堆中，只有当该位置的 $v$ 值位于堆顶，并且我们发现堆中储存 $v$ 值并非真实值时，我们才将堆顶删除并将当前实际的 $v$ 值加进堆中，这样便保证了堆中至多只有 $n$ 个元素。这个堆可以用优先队列来实现。

加上快输后可以通过本题，时间复杂度为 $O(n \ln n \log n)$。

```cpp
#include <set>
#include <bits/stdc++.h>
using namespace std;
const int maxN = 500010;
struct Pair{ int id, v; };
bool operator < (Pair P, Pair Q)
{
	if(P.v != Q.v) return P.v > Q.v;
	else return P.id > Q.id;
}
priority_queue<Pair> f;
bool ntpr[maxN], vis[maxN], in[maxN];
int pr[maxN], v[maxN];
int digit[20];
int read ()
{
	int x = 0, Fu = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') Fu = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = x * 10 + (c - '0');
		c = getchar();
	}
	return x * Fu;
}
void write (int x)
{
	int cnt = 0;
	while(x)
	{
		digit[++cnt] = x % 10;
		x /= 10;
	}
	for(int i = cnt;i >= 1; i--)
		putchar(digit[i] + '0');
}
int main ()
{
	int n = read();
	for(int i = 2;i <= n; i++)
	{
		if(ntpr[i]) continue;
		for(int j = 2 * i;j <= n;j += i)
			ntpr[j] = true;
	}
	vis[1] = true;
	pr[++pr[0]] = 1;
	for(int i = n;i > 1; i--)
	{
		if(!ntpr[i])
		{
			putchar('1'), putchar(' ');
			vis[i] = true;
			for(int j = i * 2;j <= n;j += i)
			{
				if(!vis[j])
				{
					if(!in[j])
					{
						in[j] = true;
						f.push((Pair){j, i});
						v[j] = i;
					}
					else if(i > v[j])
						v[j] = i;
				}
			}
		}
	}
	while(!f.empty())
	{
		f.top();
		Pair It = f.top();
		while(It.v != v[It.id])
		{
			f.pop(); f.push((Pair){It.id, v[It.id]});
			It = f.top();
		}
		if(f.empty()) break;
		f.pop();
		int id = It.id, val = It.v;
		write(val), putchar(' ');
		vis[id] = true;
		for(int j = id * 2;j <= n;j += id)
			if(!vis[j] && id > v[j]) v[j] = id;
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

Update：调整了表格中的内容。

转换一下思路，我们对于每个 $g$，求出当不完美值 $\le g$ 时的最大集合大小。

我们列一个表格来观察每次 $g$ 加一时往集合中加入的数字：

| $g=$ | 加入的数 |
| :----------: | :----------: |
| 1 | 全体质数 |
| 2 | 4 |
| 3 | 6 和 9 |
| 4 | 8 |
| 5 | 10，15 和 25 |
| 6 | 12 和 30 |

我们发现，当 $g$ 等于某个值时，加入的数一定是这个值乘上一个小于它的质数。也就是说，**每个数被加入的时间就是它最大的不是自身的因数**。

那么从 $1\cdots n$ 枚举每个数的倍数，更新它加入的时间就做完了。时间复杂度 $O(n\log n)$，用线性筛可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5;

int n,num[Maxn+5],ans[Maxn+5],tot;

int main()
{
    cin>>n; For(i,1,n) num[i]=1;
    For(i,1,n) for(int j=i+i;j<=n;j+=i) num[j]=i;
    For(i,1,n) ans[num[i]]++; ans[1]--;
    For(i,1,n) For(j,1,ans[i]) printf("%d ",i);
    printf("\n");
    return 0;
}
```

---

## 作者：Fuyuki (赞：0)

如果存在 $x\in S$，$d|x$ 且 $d\not\in S$，那么将 $x$ 替换成 $d$ 答案一定不会变劣。

也就是说，当往集合中加入一个元素 $x$ 的时候，一定可以调整成 $x$ 的真因数都在集合中，那么将 $x$ 加入 $S$ 对答案的贡献就是 $x$ 最大的真因数。因此，每次一定是选择当前最大真因数最小的数加入到 $S$ 中。

那么筛出或者暴力算出 $2$ 到 $n$ 的最大真因数，然后贪心即可。复杂度为 $O(n)$ 到 $O(nlogn)$ 不等。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
const int N=5e5+1;
int n,a[N],c[N];
int main(){
	cin>>n;
	FOR(i,1,n)FOR(j,2,n/i)a[i*j]=i;
	FOR(i,1,n)c[a[i]]++;
	FOR(i,1,n)while(c[i]--)cout<<i<<' ';
	return 0;
}
```

---

