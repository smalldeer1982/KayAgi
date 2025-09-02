# Kuroni and the Score Distribution

## 题目描述

Kuroni is the coordinator of the next Mathforces round written by the "Proof by AC" team. All the preparation has been done, and he is discussing with the team about the score distribution for the round.

The round consists of $ n $ problems, numbered from $ 1 $ to $ n $ . The problems are ordered in increasing order of difficulty, no two problems have the same difficulty. A score distribution for the round can be denoted by an array $ a_1, a_2, \dots, a_n $ , where $ a_i $ is the score of $ i $ -th problem.

Kuroni thinks that the score distribution should satisfy the following requirements:

- The score of each problem should be a positive integer not exceeding $ 10^9 $ .
- A harder problem should grant a strictly higher score than an easier problem. In other words, $ 1 \leq a_1 < a_2 < \dots < a_n \leq 10^9 $ .
- The balance of the score distribution, defined as the number of triples $ (i, j, k) $ such that $ 1 \leq i < j < k \leq n $ and $ a_i + a_j = a_k $ , should be exactly $ m $ .

Help the team find a score distribution that satisfies Kuroni's requirement. In case such a score distribution does not exist, output $ -1 $ .

## 说明/提示

In the first example, there are $ 3 $ triples $ (i, j, k) $ that contribute to the balance of the score distribution.

- $ (1, 2, 3) $
- $ (1, 3, 4) $
- $ (2, 4, 5) $

## 样例 #1

### 输入

```
5 3```

### 输出

```
4 5 9 13 18```

## 样例 #2

### 输入

```
8 0```

### 输出

```
10 11 12 13 14 15 16 17```

## 样例 #3

### 输入

```
4 10```

### 输出

```
-1```

# 题解

## 作者：皎月半洒花 (赞：12)

比较自然的想法是从头开始填 $1,2,3\cdots$，因为这样容易填且满足条件。同时可以发现，这种构造方式是使得每个位置作为 $k$ 时，贡献三元组最多的方式：由于序列满足单调性，所以一定不存在前面的 $i,j$ 彼此有交。那么对于一个 $a_k=k$ 他可以贡献 $\lfloor \frac{k-1}{2}\rfloor$ 的答案。

考虑如果超出 $m$ 如何处理。假设当前答案超出了 $x$ 。对于一个 $k$ ，按照上述方式能够贡献 $\lfloor \frac{k-1}{2}\rfloor$ 的答案，那么如果想要只贡献 $\lfloor \frac{k-1}{2}\rfloor-x$ 的答案，就需要让其中的 $x$ 对 $(i,j)$ 无效。具体的，考虑令当前的 $k$ 变为 $k+2x$ ，那么考虑前 $k-1$ 个数里面最大的是 $k-1$ ，只能去匹配 $2x+1$，这样就会少掉 $2x$ 个可以用的数，答案变成了 $\lfloor\frac{k-1-2x}{2}\rfloor=\lfloor \frac{k-1}{2}\rfloor-x$ 。

那么补齐 $n$ 个数也很简单。只需要考虑如果当前填了的最大的数是 $j$ ，从 $10^9$ 向下按照 $2\cdot j$ 的步长递减即可。不难证明这样做是对的。

```cpp
int main(){
    std :: cin >> n >> m ;
    for (int i = 1 ; i <= n ; ++ i){
        ans[i] = i ; cnt += (i - 1) / 2 ;
        if (cnt >= m){
            int s = 1000000000 ;
            ans[i] += 2 * (cnt - m) ;
            for (int j = n ; j > i ; -- j)
                ans[j] = (s -= (ans[i] + 1)) ;
            gf = 1 ; break ;
        }
    }
    if (gf)
        for (int i = 1 ; i <= n ; ++ i)
            printf("%d ", ans[i]) ;
    else return puts("-1"), 0 ;
}
```

---

## 作者：xht (赞：8)

要求构造一个长度为 $n$ 的单调上升序列 $a$，使得恰好有 $m$ 个三元组 $(i,j,k)(i < j < k)$ 满足 $a_i + a_j = a_k$。

很傻的一道构造题。

先 $1,2,3,4,5,\dots$ 的填，产生的三元组个数为 $0,0,1,1,2,\dots$。

一直填到第一次个数 $\ge m$ 的位置，假设多了 $k$ 个。

注意到在这个位置上的数每增加 $2$，个数会减 $1$，因此这个位置上的数加上 $2k$ 即可。

后面的不应该再存在满足条件的三元组了，那么填一定间隔下最大的几个数就够了。

如果填完 $n$ 个数，三元组的数量依旧 $< m$，则说明无解，因为这个填数的方法最大化了三元组的数量。

```cpp
const int N = 5e3 + 7;
int n, m, a[N];

int main() {
	rd(n), rd(m);
	int t = 0;
	for (int i = 0; i < n; i++) {
		a[i] = i + 1;
		t += i >> 1;
		if (t >= m) {
			a[i] += (t - m) << 1;
			for (int j = n - 1, k = 1e9; j > i; j--, k -= i + 2)
				a[j] = k;
			for (int j = 0; j < n; j++)
				print(a[j], " \n"[j==n]);
			return 0;
		}
	}
	print(-1);
	return 0;
}
```

---

## 作者：Binaerbaka (赞：1)

# 题面
构造出一个长度为 $n$ 序列 $a_i$ 有且恰好有 $m$ 个 三元组 $(i,j,k)$ $(i<j<k)$ 使得 $a_i + a_i = a_k$。

# 过程

- 考虑 $m$ 有解最大值

可以考虑优先填充 $1,2,3....n$ 所构造的三元组为 $0,0,1,1,2...$ 发现这是构造三元组个数最多的填充方式，考虑证明。

在这种方法下，任意 $n$，前面 $n-1$ 个数都可以分成两组数，一组 $x_1<n\div2$，一组 $x_2>n\div2$，任意一组 $({x_1},{x_2})$ 都有且仅有一组与 $n$ 构造合法三元组。当 $n$ 为偶数时候，会有 ${x_3}=n\div2$ 时无法构造三元组。

而其他的构造方法都无法比这样子构造更多，因为它无法保证任意一对 $(x_1,x_2)$ 都一定有一组三元组。因此自然数填充方法构造个数最多。当自然数填充方法无法满足 $m$ 时此数据无解。

- 考虑如何去除多余三元组

根据上述结论可以发现，当你 $a_k$ 这个位数时，三元组个数已经大于 $m$ 了，你就只需要在 $k$ 位置上多增加 $2$ 就可以减少一对三元组，因为每当增加后，就会损失一对三元组为 $(x_1,x_2)$，保留一对 $(x_1-1,x_2+1)$ 的三元组。为什么呢?因为这两对的差值刚好是 $2$。

- 考虑如何填充剩余构造数  两种办法

1. 极大值递减

当你填充完到 $k$ 位时，已经满足 $m$ 了，如何填充后面的 $n-k$ 个构造数呢，只需要从一个极大值不断减去数组内最大值多减去一即可。

2. 非法值递增

同理，在 $k+i$ 位逐渐递增一个无法被先前数之和相等的数即可。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+5;
const int inf=1e9;
int n,m,a[maxn],cnt,flag;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i]=i,cnt+=(i-1)/2;
		if(cnt>=m){
			a[i]+=2*(cnt-m);
			for(int j=n,k=inf;j>i;j--){
				a[j]=(k-=(a[i]+1));//我使用了方法 1
			}
			for(int j=1;j<=n;j++)cout<<a[j]<<" ";
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```





---

## 作者：RiceFruit (赞：1)

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF1305E)

给你两个正整数 $n$ 和 $m$，让你构造一个长度为 $n$ 的序列 $a$，并满足以下条件：

$\texttt{1.}$ 所有 $a_i$ 都在 $1\sim 10^9$ 之间。

$\texttt{2.}$ 这个序列必须严格单调递增。

$\texttt{3.}$ 满足 $a_i+a_j=a_k(i<j<k)$ 的个数必须为 $m$。

## 题目思路

我们先考虑构造一个满足 $\texttt{3}$ 条件数量最多的序列，那么肯定就是  $1,2,3\cdots$，那么对于第 $x$ 个数作为 $a_k$，则它对答案的贡献就是 $\lfloor \frac{x-1}{2} \rfloor$，这应该是显然的。

如果这个序列 $1\sim n$ 的总贡献还是不到 $m$，那么就可以输出无解 ，毕竟这是满足个数最多的序列。

接下来我们就考虑当第一次第 $x$ 位填了 $x$，总个数超过或者等于了 $m$。设之前的方案数为 $sum$ （不包括第 $x$ 位），则我们要让第 $x$ 位的贡献为 $m-sum$，而如果这一位填 $x$ 的贡献为 $\lfloor \frac{x-1}{2} \rfloor$，接下来我们考虑让这一位的贡献减少。

这时，我们先考虑一个子问题：把一个数加 $\color{red}{2}$，它的贡献会减少多少？

我们知道，第 $x$ 为填 $x$，那么会有一种方案是 $x=1+(x-1)$，而 $x$ 加了 $2$，那么以 $1$ 作为第一位肯定不行，因为没有 $x+1$；同理，以 $2$ 作为第一位也不行，因为没有 $x$，它已经变成了 $x+2$。

而对于以 $t$ （ $2\leq t< \lceil \frac{x}{2} \rceil$ ）作为第一位，它的方案都可以对应到 $x+2$ 的一种方案。

而对于以 $\lceil \frac{x}{2} \rceil$ 做为第一位，它在 $x$ 的方案中是不行的，而在 $x+2$ 中的方案中是可以出现的。

所以贡献会减少 $(0+2-1=1)$ 个。

故我们得出结论：把一个数加 $2$，它的贡献会见少 $1$。

这样，我们的子问题就解决了。

这时我们回到原问题：要让第 $x$ 位的贡献为 $m-sum$，而原贡献为 $\lfloor \frac{x-1}{2} \rfloor$，怎么修改？

根据我们刚刚得出的结论，我们只需要让 $x$ 加上 $[\lfloor \frac{x-1}{2} \rfloor-(m-sum)]\times 2$ 即可。

现在，我们只需要让第 $x+1\sim n$ 位的贡献为 $0$ 就好了。我们只需让 $a[n]$ 为最大的 $10^9$，然后每次往下是都减去 $x+1$ 即可。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define ri register int
#define ll long long
#define ull unsigned long long
#define lid (id<<1)
#define rid (id<<1|1)
void swap(int &x,int &y){int t=x;x=y;y=t;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
const int N=10001;
inline int read();
inline void write(int ans);
inline void put(int x,char c);
int n,m,ls=1e9,sum;
int a[N];
bool ok;
signed main(){
	ios_base::sync_with_stdio(0);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=i;
		if(sum+(i-1)/2>=m){
			a[i]+=(sum-(m-(i-1)/2))*2;
			ok=1;
			for(int j=n;j>i;j--){
				a[j]=ls-(i+1),ls-=i+1;
			}
			break;
		}
		sum+=(i-1)/2;
	}
	if(ok){
		for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	}
	else{
		cout<<-1;
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}
```


---

## 作者：Sai0511 (赞：1)

若按照 $\forall a_i=i$ 这样的方式填，那么 $a_x=a_1+a_{x-1}=a_2+a_{x-2}=a_3+a_{x-3}=....=a_{x-1}+a_1$，所以第 $i$ 个数的贡献就是 $\lfloor \frac{i-1}{2} \rfloor$。      
同时我们如果把最后一个数 $n$ 加上 $2$，那么 $a_n=a_3+a_{n-1}=a_{4}+a_{n-2}=....=a_{n-1}+a_3$，所以贡献为 $\lfloor \frac{i-3}{2} \rfloor = \lfloor{\frac{i-1}{2} \rfloor}-1$，所以最后一个数加了 $2$，三元组数就少了 $1$。        
故我们可以一直按照 $\forall a_i=i$ 这样填知道三元组数超过 $m$ 为止，把给最后一个数加上两倍的超过的数量就好。      
至于后面的数呢，反正 $a_i \leq 10^9$，记 $V=\max{a_i}+1$ **从第 $n$ 位开始倒着填**直接按照 $10^9,10^9-V,10^9-2V,10^9-3V..$，显然不会有影响。    

---

## 作者：奇米 (赞：1)

# 题解 - $\mathrm{CF1305E \ Kuroni \ and \ the\ Score \ Distribution}$

## 题目意思
就是构造一个递增使序列$a$得满足有$m$个三元组$(i,j,k)$使得满足$a_i+a_j=a_k$。

## $\mathrm{Sol}$
* 一道小清新构造题
* 我们首先考虑如果按编号（即$1,2,3...$）的顺序下去，每个数的贡献三元组数量为$\mathrm{(k-1)/2}$。于是我们不停地加直到总和超过$m$。这是我们要减去多余地贡献。然后我们又要得出一个结论
*  对于最后一个数，每增加$2$，他的贡献会减少$1$的贡献。所以我们要使得最后一个数增加$\mathrm{res=(las-m)\times 2}$。
* 对于后面的数如何构造，只要在$10^8$的基础上不停地以$\mathrm{res+1}$递增即可。此时构造的序列是合法的。

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=5005;

int n,m,a[N],gs;

int main()
{
	n=read();
	m=read();
	int dd=0;
	for ( int i=1;i<=n;i++ )
	{
		a[i]=i;
		gs+=(i-1)/2;
		if(gs>=m)
		{
			a[i]+=2*(gs-m);
			int add=1e7;
			for ( int j=n;j>i;j-- ) 
				a[j]=(add-=(a[i]+1));
			dd=1;
			break;
		}
	}
	if(!dd) return printf("-1\n"),0;
	for ( int i=1;i<=n;i++ ) printf("%d ",a[i]);
	return 0;
}
			 
```


---

## 作者：CQWDX (赞：1)

**Preface: 其实原来的思路挂了。看 #7 数据才有新的思路。**

---

首先有一个贪心的思路：先不管那么多，在前面尽量从 $1$ 开始顺序填充，把能放的 $[1,p]$ 先放了。

~~显然~~这样的方法在同等长度内是最优解。~~其实是没看出来怎么证。~~

手玩可得，若 $2\mid p$，对三元组的数量贡献为 $\frac{p(p-2)}{4}$ ；若 $2\nmid p$，对三元组的数量贡献为 $\frac{(p-1)^2}{4}$。

这样的话，若有 $m>\frac{p(p-2)}{4}$ 或 $m>\frac{(p-1)^2}{4}$，可以确定无解。

以 $n=15,m=39$ 为例。

$2\nmid n$，$\frac{(13-1)^2}{4}=36<m$ ，故 $p=13$ 为满足条件的最大值。

故 $a=\{1,2,3,4,5,6,7,8,9,10,11,12,13\}$。

接下来会剩余一些需要满足的三元组。

如果直接用 $a_{n+1}:=a_{n-1}+a_n$ 来套的话，$a$ 的增长速度是 $2$ 倍，显然不可接受。

那就说明 $a$ 的内部还有一些操作空间。

~~感谢 #7 测试点送的思路~~

观察发现评测姬给出的答案是 $a=\{1,2,\dots13,20,34\}$。显然 $34$ 与答案无关。而 $20=7+13=8+12=9+11$。

那么就有 $\forall x\in[p+1,2p-1]$，对答案的贡献为 $a$ 中任选两个值相加等于 $x$ 的个数。

再观察一下，发现 $\forall l\in[1, p-1]:(l+p)\in[p+1,2p-1]$。

然后区间 $[l,p]$ 内有 $\lfloor\frac{p-l+1}{2}\rfloor$ 个 $i$ 满足 $a_i+a_{p-i+1}=l+p$。

令 $x=l+p$，则其对三元组数量产生的贡献为 $\lfloor\frac{p-l+1}{2}\rfloor$。

~~然后聪明的你一定可以想到枚举 $l\in[1,p-1]$ 然后计算答案~~

当然，如果上述步骤中 $a$ 的大小超过了 $n$，可以视作无解。

显然上述策略是在 $p$ 一定的情况下对三元组数量贡献最大的。

这时候可能会存在三元组数量还没有到 $m$ 的情况。

但是由于前面把 $a$ 内部的元素处理完毕，所以最多也就只剩一个了。

将 $a_{n-1}+a_{n}$ 加入结果即可。

但是如果 $a$ 的大小还没有达到 $n$，怎么办？

很简单。从 $10^9$ 倒序往里面扔数。每个数的大小差值为 $5000$。

由于 $n=5000$ 时能够满足的最大 $m=\frac{p(p-2)}{4}=6247500<10^9-5000\times5000$，所以即使全程从 $10^9$ 倒序往里面扔数，前面的数也不会对其产生任何影响。

大致流程就是这样。放代码。~~我也不知道为什么长得那么丑~~

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3, "Ofast", "inline")
int n, k, m;
int last, pos;
std::vector <int> res;
int main() {
	scanf("%d %d", &n, &k), last = k;
    // 判断是否有解
	if(
		((n & 1) && k > (n - 1) * (n - 1) >> 2) ||
		(!(n & 1) && k > n * (n - 2) >> 2)
	) { printf("-1"); return 0; } 
    // 贪心填充前缀 [1,p] 区间
	for(int i = n; i >= 1; i--) {
		int tmp;
		if(i & 1) tmp = (i - 1) * (i - 1) >> 2;
		else tmp = i * (i - 2) >> 2;
		if(tmp <= k) { m = i, last -= tmp, n -= m; break; }
	}
	for(int i = 1; i <= m; i++) res.push_back(i);
    // 枚举区间 [l,p]，累加贡献
	for(int l = 1; l < m && last > 0; l++) {
		int tmp, len = m - l + 1;
		tmp = len >> 1;
		if(last >= tmp) last -= tmp, n--, res.push_back(l + m);
	}
    // 
	while(1) {
		if(n < 0) { printf("-1"); return 0; }
		if(last <= 0) break;
		res.push_back(*(res.end() - 1) + *(res.end() - 2));
		n--, last--;
	}
    // 用大数填充 res.size() < n 的部分
	while(n > 0) res.push_back(1e9 - n * 5001), n--;
	std::sort(res.begin(), res.end());
	for(int u : res) printf("%d ", u);
	return 0;
}
```



---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1305E)

本人构造幼儿园水平，看到隔壁小朋友在做构造题，来复健一下构造。

首先比较直观的想法就是 $1,2,3,4$ 这样一直填下去。然后显然每填一个数增加的三元组个数是 $0,0,1,1,2,2...$，第 $i$ 个数贡献 $\left\lfloor\dfrac{i-1}{2}\right\rfloor$。

然后这样加显然是最优的，如果一直加不到 $m$ 就无解。

比较难办的是加多了怎么办。假设当前第 $i$ 次加完了之后多了 $k$ 个。然后你要把这 $k$ 个减掉。随便观察一下会发现这个位置每 $+2$，贡献的三元环数量 $-1$，于是把这个位置 $+2k$ 就可以了。

剩下的 $n-i+1$ 空位置不能贡献三元环，我最开始的思路是令 $a_j=a_{j-2}+a_{j-1}+1$，但是这个数列显然增长速度太快轻松爆 $10^9$。所以考虑从上界向下减，每次 $-2a_i$ 即可保证不冲突。

做完了。

---

