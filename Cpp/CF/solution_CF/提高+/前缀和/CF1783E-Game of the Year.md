# Game of the Year

## 题目描述

Monocarp 和 Polycarp 正在玩电脑游戏。游戏特点：$ n $ 个编号从 $ 1 $ 到 $ n $ 的BOSS。

他俩将用以下方式与BOSS战斗

- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- ...

Monocarp 在第 $ a_i $ 次尝试中撒掉了第 $ i $ 只BOSS。Polycarp 在第 $ b_i $ 次尝试中撒掉了第 $ i $ 只BOSS。其中一个人撒掉第 $ i $ 只BOSS后，他们就会尝试撒第 $ (i+1) $ 只BOSS。并且他们的尝试计数器都会清空。撒掉第 $ n $ 只BOSS后，游戏结束。

找到从$ 1 $ 到 $ n $所有的 $ k $ 值， 使得 Monocarp 可以杀死所有的BOSS。

## 说明/提示

考虑最后一组测试样例

使 $ k = 1 $。首先，Monocarp经过1次尝试撒死第一只BOSS。成功，因为 $ a_1 = 1 $。 然后，Monocarp进行一次尝试撒死第二只BOSS。不成功，因为 $ a_2 > 1 $。于是，Polycarp尝试了一下。也不成功，因为 $ b_2 > 1 $。然后Monocarp进行了另一次尝试。仍然不成功，因为 $ a_2 > 2 $。直到Polycarp 在第三次尝试撒掉了BOSS。Monocarp没能撒掉BOSS。因此，$ k = 1 $ 不是答案。

使 $ k = 2 $ . Monocarp仍然在他的第一次尝试中撒死了BOSS。然后，他进行了两次不成功的尝试未能撒死BOSS。然后，Polycarp进行了两次不成功的尝试。然后，Monocarp进行了两次尝试，并且在第四次尝试中撒掉了BOSS。撒掉第三只BOSS的方法也类似。首先，Monocarp进行两次不成功的尝试。然后，Polycarp进行两次不成功的尝试。然后，Monocarp还有两次尝试机会，但在这两次机会中第一次就撒死了BOSS，因为 $ a_3 = 3 $。 第四只BOSS也被Monocarp撒死。因此，$ k = 2 $ 是答案。

## 样例 #1

### 输入

```
3
3
1 1 1
2 3 1
1
1
1
4
1 4 3 2
3 3 4 1```

### 输出

```
3
1 2 3 
1
1 
2
2 4```

# 题解

## 作者：Alex_Wei (赞：18)

A 和 B 分别在第 $\lceil \frac {a_i} k\rceil$ 和第 $\lceil \frac {b_i} k\rceil$ 次攻击时杀死第 $i$ 个怪物，所以题目相当于找到所有 $1\leq k\leq n$ 使得 $\lceil \frac {a_i} k\rceil\leq \lceil \frac {b_i} k\rceil$。

我们直接对 $\lceil \frac {a_i} k\rceil$ 进行整除分块，对每个整除值 $d$ 算出使得 $\lceil \frac {b_i} k\rceil\geq d$ 的合法区间，时间复杂度 $\mathcal{O}(n\sqrt n)$，然而 [无法通过](https://codeforces.com/contest/1783/submission/188645851)。

换种角度考虑。对 $a_i\leq b_i$ 显然所有 $k$ 均合法。当 $a_i > b_i$ 时，考虑 $k$ 不合法的充要条件：在 $[b_i, a_i - 1]$ 之间存在 $k$ 的倍数。这样就简单了：区间覆盖 $[b_i, a_i - 1]$，则一个 $k$ 合法当且仅当它的所有倍数均没有被覆盖，枚举即可。时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1783/submission/188539775)。

---

## 作者：fast_photon (赞：14)

**-1. Upd**  
Upd 2023/1/10 13:53 一个 $\log n$ 脑残写成 $n\log n$，fixed（感谢@一个程序员 的指正）

**0. 前言**  
好久没写题解了，来找回熟悉的讲题的感觉。  
第一次赛时切 E，没吃罚时一遍过，挺好的。  
不知道为啥有猴子因为我发现他写的题解有问题就来疯狂给我的题解点踩。自觉一点。  
今天话比较多，我们进入正题。  

**0.5 题意**  
对于每组数据，给定 $\{a_n\}$，$\{b_n\}$。保证 $a_i,b_i\le n$。对于每个 $(a_i,b_i)$，有以下操作：  
有两个人 A 和 B。他们的分数初始是 $0$。A 的分数先增加 $k$，然后是 B 增加 $k$，接下来又轮到 A，循环往复。直到 A 的分数先达到了 $a_i$，A 胜利，或 B 的分数先达到 $b_i$，B 胜利。此时清空两人分数，进入第 $i+1$ 轮。  
问有多少个、以及哪些 $1\le k\le n$ 使得 A 赢下每一轮。  

**1. 推式子**  
我们假设第 $i$ 轮游戏 B 增加了 $x$ 次，也就是 A 增加了 $x+1$ 次。则有：  
$$(x+1)k\ge a_i$$  
$$xk < b_i$$  
整理得  
$$\frac{a_i-k}{k}\le x<\frac{b_i}{k}$$  
显然， $x$ 是整数。（可能是 $0$）  
也就是说，$\left\lceil\frac{a_i-k}{k}\right\rceil \le x$。  
而 $\left\lceil\frac{n}{m}\right\rceil=\left\lfloor\frac{n+m-1}{m}\right\rfloor$。  
> 证明：设 $n=mq+r(1\le r\le m)$。则 $\left\lceil\frac{n}{m}\right\rceil=q+1$。而 $n+m-1=m(q+1)+r(0\le r<m)$。此时，$\left\lfloor\frac{n+m-1}{m}\right\rfloor=q+1$。证毕。  

则 
$$\left\lceil\frac{a_i-k}{k}\right\rceil=\left\lfloor\frac{a_i-1}{k}\right\rfloor$$  
因为 $x<\frac{b_i}{k}$ 且 $x$ 是整数，所以 $\left\lceil\frac{b_i}{k}\right\rceil\ge x+1$。  
又因为$\left\lfloor\frac{n+m}{m}\right\rfloor=\left\lfloor\frac{n}{m}\right\rfloor$  
所以同理可得  
$$\left\lceil\frac{b_i}{k}\right\rceil=\left\lfloor\frac{b_i+k-1}{k}\right\rfloor=\left\lfloor\frac{b_i-1}{k}\right\rfloor+1$$  
代入整理，得  
$$\left\lfloor\frac{a_i-1}{k}\right\rfloor\le x\le \left\lfloor\frac{b_i-1}{k}\right\rfloor$$  
这样的得到了符合要求的 $(x,k)$ 的式子。那么什么样的是不符合要求的呢？  
$a_i-1$ 和 $b_i-1$ 除以 $k$ 的商不一样。且前者大于后者。则 $[b_i-1+1,a_i-1]$ 的区间里有一个 $k$ 的倍数。换言之，$[b_i,a_i-1]$ 区间内所有数的所有因子都不是合法的 $k$。  

**2. 得出答案**  
我们可以用差分序列维护区间加（区间式子在上面）和单点查（全部修改完求前缀和）的操作。  
我赛时没法想太多，就直接写了一个树状数组维护 $n\log^2n$ 的，~~居然卡过去了~~。  
查询一个 $k$ 是否合法的时候，直接遍历每一个 $k$ 的倍数，看这个数是否被标记过。虽然这样的枚举在 $k=1$ 时可以被卡到最坏复杂度单个 $O(n)$，但是可以用数学方法证明 $\sum\limits_{i=1}^n\frac{1}{i}$ 在 $\log n$ 量级。这里不再赘述。  

**3. 代码**  
这里赛后改成差分代码了。
```cpp
#include<iostream>
#include<cstdio>
#define maxn 200005

using namespace std;

int t, n, a[maxn], b[maxn], c[maxn + 10], logn;
bool kmn[maxn];

void work() {
	cin >> n;
	for(int i = 1; i <= n; i++) c[i] = 0;
	for(int i = 1; i <= n; i++) {
		can[i] = true;
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	for(int i = 1; i <= n; i++) {
		if(a[i] > b[i]) {
			c[b[i]]++;
			c[a[i]]--;
		}
	}
	for(int i = 1; i <= n; i++) c[i] += c[i - 1];
	int adorable = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; i * j <= n; j++) {
			if(c[i * j]) {
				kmn[i] = false;
				break;
			}
		}
		if(kmn[i]) adorable++;
	}
	cout << adorable << endl;
	for(int i = 1; i <= n; i++) {
		if(kmn[i]) cout << i << ' '; 
	}cout << endl;
}

int main() {
	cin >> t;
	while(t--) 
	work();
}
```

---

## 作者：Robin_kool (赞：2)

首先想到暴力枚举 $k$，然后暴力代入每一个 $a_i$，复杂度为 $O(T\times n^2)$，显然爆炸。

考虑优化性质。对于 $a_i$ 和 $b_i$，最好的情况就是 $a_i \leq b_i$，那样的话由于要求的人是先手，$k$ 可以取任意值。若 $a_i>b_i$，肯定不能让 $k$ 的某正整数倍在他们两个之间，包括 $b_i$ 但不包括 $a_i$。最后对于每一个 $k$，枚举他的正整数倍，判断有没有经过某一段上述区间即可。

记录每一个数 $x$ 在不在一段区间可用差分解决。

复杂度 $O(T n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll T, n, a[N], b[N], t[N], ans;
bool Ans[N];
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline void solve(){
	n = read(), ans = 0;
	for(int i = 1; i <= n; ++ i) a[i] = read(), t[i] = 0;
	for(int i = 1; i <= n; ++ i) b[i] = read(), Ans[i] = true;
	for(int i = 1; i <= n; ++ i) if(a[i] > b[i]) ++ t[b[i]], -- t[a[i]];
	for(int i = 1; i <= n; ++ i) t[i] += t[i - 1];
	for(int i = 1; i <= n;++ i){
		for(int j = 1; j <= n / i && Ans[i]; ++ j) if(t[i * j]) Ans[i] = false;
		ans += Ans[i];
	}
	write(ans), putchar('\n');
	for(int i = 1; i <= n; ++ i) if(Ans[i]) write(i), putchar(' '); putchar('\n');
}
signed main(){
    T = read();
    while(T --) solve();
	return 0;
}

```


---

## 作者：Fido_Puppy (赞：2)

题目传送门：[Game of the Year](https://www.luogu.com.cn/problem/CF1783E)。

## 思路

我们首先要分析出，假如已知 $k$，在什么条件下 Monocarp 获胜。

显然如果 $a_i \le b_i$，则 $\forall k \in [1,n]$，Monocarp 获胜。

如果 $b_i < a_i$，那么我们模拟击杀 BOSS 的过程后容易发现：

我们将**每 $2k$ 次操作**称作一轮，每轮中前 $k$ 次 Monocarp 尝试，后 $k$ 次 Polycarp 尝试。

如果 Monocarp 要获胜，则需满足 Monocarp 的第 $a_i$ 次尝试与 Polycarp 的第 $b_i$ 次尝试在同一轮中。

容易发现，Monocarp 或者 Polycarp 的第 $x$ 次尝试在第 $\lceil \dfrac{x}{k} \rceil$ 轮中。

所以我们首先忽略掉所有 $a_i \le b_i$ 的 $i$，然后对于一个 $k$，如果其合法，则需满足所有剩下的 $a_i, b_i$，都 $\exists t, tk \le a_i < b_i < tk + k$。

直接枚举每一个 $k$，调和级数的复杂度枚举 $t$，接着需要判断在 $[tk, tk + k)$ 中，对于每个 $i$，是否要么 $a_i, b_i$ 都不在区间内，要么 $a_i, b_i$ 都在区间内。假如我们给 $a_i, b_i$ 都加上一个标号 $i$，那么问题就变成了判断区间中每种标号的出现次数是否都是偶数。

这个明显可以用**异或哈希**来实现，对于每一个 $i$，我们赋一个随机权值，然后就变成了查询区间异或值是否为 $0$。

时间复杂度 $\Theta(n \log n)$。

## 代码链接

[https://codeforces.com/contest/1783/submission/191230337](https://codeforces.com/contest/1783/submission/191230337)

---

## 作者：Frodo (赞：1)

## 思路

我们考虑一个 $k$ 不合法的充要条件：

首先 $a_i \le b_i$ 的 BOSS 显然永远合法；

对于 $a_i > b_i$ 的 BOSS，合法的充要条件显然为 $\lfloor \frac{a_i}{k} \rfloor = \lfloor \frac{b_i}{k} \rfloor$，等价于不存在 $j$ 满足 $k \mid j$ 且 $j \in [b_i,a_i)$。

于是我们统计出所有被 $[b_i,a_i)$ 覆盖的数，将其因数排除，剩余的即为答案。

## 时间复杂度

$\Theta (n \times \tau(n) )$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Fastio{
	#define read Fastio::readuint
	#define write Fastio::writeuint
	#define flush Fastio::clear
	#define SIZE (1<<20)
	#define NUMLEN 12
	#define getchar() (_S==_T&&(_T=(_S=_in)+fread(_in,1,SIZE,stdin),_S==_T)?EOF:*_S++)
	char _in[SIZE],*_S=_in,*_T=_in;
	char _out[SIZE],*_P=_out;
	const char *_end=_out+SIZE;
	inline unsigned int readuint(){
		unsigned int ret=0;char ch=getchar();
		while(ch<'0'||ch>'9'){ch=getchar();}
		while(ch>='0'&&ch<='9'){ret=(ret<<1)+(ret<<3)+(ch^48);ch=getchar();}
		return ret;
	}
	inline void clear(){fwrite(_out,1,_P-_out,stdout);_P=_out;}
	inline void putchar(char ch){*(_P++)=ch;if(_P==_end)clear();}
	inline void outuint(unsigned int x){
		if(x==0){putchar(48);return;}
		unsigned int i=0;
		char st[NUMLEN];
		while(x) st[i++]=48^(x%10),x/=10;
		while(i--) putchar(st[i]);
	}
	inline void writeuint(int x,char ch){outuint(x);putchar(ch);}
}
const int N=200100;
int n,a[N],b[N],f[N],cnt[N];
vector<int>vec[N];
void init(){
	n=2e5;
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j+=i) vec[j].push_back(i);
}
void solve(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	for(int i=1;i<=n;i++) if(a[i]>b[i]) f[b[i]]++,f[a[i]]--;
	for(int i=1;i<=n;i++){
		f[i]+=f[i-1];
		if(f[i]) for(int j:vec[i]) cnt[j]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++) if(!cnt[i]) ans++;
	write(ans,10);
	for(int i=1;i<=n;i++) if(!cnt[i]) write(i,32);
	Fastio::putchar(10);
	for(int i=1;i<=n+1;i++) f[i]=cnt[i]=0;
}
signed main(){
	#ifdef LOCAL
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	init();
	int T=read();
	while(T--) solve();
	flush();
	return 0;
}
```

---

## 作者：zac2010 (赞：1)

这道题目是个水题，然后还是没能独立做出……

### 题意
因为有中文了，所以就不再赘述。

这里罗列翻译两个不太清晰的点（只是个人认为）：
1. 每一个 boss 是独立的，和上一个怪物没有关系。
2. 每个人的 $k$ 次只是对于自己，不算入对方的计数里面。

### 解题思路

先进行转换，题意是求所有满足 $\lceil \frac{a_i}{k} \rceil \leq\lceil \frac{b_i}{k} \rceil$ 。

不难想到用最基础的容斥：拿总数 $n$ 减去不合法的 $k$ 就是合法的 $k$ ，非不合法的就是合法的。那接下来又该怎么求呢？既然上面说怪物之间两两独立，不妨先单独考虑。

对于当前 $a_i,b_i$ ，不合法的 $k$ 有哪些呢？那我们可以再假设我们已经确定了 $k$ ，要判定他在当前 boss 这里合不合法，只需要判断 $k$ 有没有倍数处于 $[b_i,a_i-1]$ 这个区间即可，如果有的话是显而易见，可以直观的看这张图：
![](https://cdn.luogu.com.cn/upload/image_hosting/rrwqyczg.png)

反之同理，对于这个 boss 来说当前 $k$ 是合法的。所以对于一个 boss 来说合法的是在 $[b_i,a_i-1]$ 区间中没有他的倍数的数。

那么我们对于所有 boss 只需要枚举他在所有的 $[b_i,a_i-1]$ 中有没有他的倍数即可。

#### 时空复杂度

时间复杂度 $O(n \log n)$ ，为调和级数，是在枚举 $1$ 到 $n$ 中所有数的倍数时所用的时间花销，由于所有 $n$ 之和不超过 $2*10^5$ ，然后每组数据带的 $log$ 一定是小于 $\log n$ 的，所以时间复杂度不超过 $n \log n$ 。

空间复杂度 $O(n)$ 。

### 自我总结

这道题目没有做出来是不应该的，第一步基础容斥想到了，分开考虑也想到过，但是之后就没有朝着正解前进了。

所以主要还是没有发现最后的结论，以后可以**画个数轴**方便自己思考题目。

### 代码

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--) 
using namespace std;
const int N = 2e5 + 10;
int T, n, cnt, a[N], b[N], t[N], f[N];
void Solve(){
	scanf("%d", &n), cnt = 0;
	L(i, 1, n) scanf("%d", &a[i]), t[i] = 0;
	L(i, 1, n){
		scanf("%d", &b[i]);
		if(a[i] > b[i]) t[b[i]]++, t[a[i]]--;
	}
	L(i, 1, n) t[i] += t[i - 1];
	L(i, 1, n){
		int flag = 0; f[i] = 1;
		L(j, 1, n / i) 
			if(t[i * j]){f[i] = 0; break;}
		cnt += f[i];
	}
	printf("%d\n", cnt);
	L(i, 1, n)
		if(f[i]) printf("%d ", i);
	putchar('\n');
}
int main(){
	scanf("%d", &T);
	while(T--) Solve();
	return 0;
} 
```


---

## 作者：蒟蒻君HJT (赞：1)

我是煞笔，场上一直尝试用整除分块做，不仅发现自己不会上取整的整除分块，甚至 $\mathcal{O}(n\sqrt n)$ 的复杂度无法通过这题，我自认为不是大常数选手，这是为什么呢？

言归正传，想作对这道题，得先把题目看懂，我外语不好，搞了很久对着样例看才明白。题目是这样的：有 $n$ 个怪物，小 A 和小 B 分别独立打每个怪物（怪物之间和 AB 之间都独立），打法：小 A 打 $k$ 滴血，小 B 打 $k$ 滴血，然后循环轮流。每个怪物 $i$ 分别对小 A 和小 B 来说有不同的血量 $a_i$ 和 $b_i$。问你对于哪些 $k\in[1,n]$，小 A 每次都比小 B 先打死怪物。 

简单转化一下题意，实际上我需要求的是：有哪些 $k$ 满足 $\forall i \in[1,n],\lceil\frac{a_i}{k}\rceil\leq \lceil\frac{b_i}{k}\rceil$。

做到这里整除分块是自然的想法，但既然都想到商的个数有限了，且未知数 $k$ 存在于分母上，不妨考虑调和级数遍历。我们直接对每个 $k$ 考虑它是否合法。

为了方便后续操作，我们再简化一下要求。如果 $a_i\leq b_i$，那这个 $i$ 直接不用考虑；而如果 $a_i>b_i$，则 $\lceil\frac{a_i}{k}\rceil\geq \lceil\frac{b_i}{k}\rceil$，综合上式得出 $\lceil\frac{a_i}{k}\rceil= \lceil\frac{b_i}{k}\rceil$。

再想一想，对于每个 $k$ 根据 $t=\lceil\frac{a_i}{k}\rceil= \lceil\frac{b_i}{k}\rceil$ 这个商的不同取值，整个 $a_i,b_i$ 的值域被分成了若干段 $[1,k],[k+1,2k] \cdots$ 而由于我们只考虑 $a_i>b_i$ 的 $i$，所以 $a_i$ 一定落在 $b_i$ 后面；更进一步，只要所有 $(a_i,b_i)$ 两个数都落在同一段中，那么这个 $k$ 就合法。

由此，我们得到了一种简单的实现方法。对于每个 $k$，我们再枚举 $t=\lceil\frac{a_i}{k}\rceil= \lceil\frac{b_i}{k}\rceil$ 的值。此时 $a_i,b_i\in[(t-1)k+1,tk]$。求出所有 $a_i\in [(t-1)k+1,tk]$ 所对应的 $b_i$ 的最小值 $m$，若 $m\leq (t-1)k$ 则这个 $k$ 就不行，否则继续检查下一个 $t$。

维护区间最小值可以使用 $\text{ST}$ 表，再加上调和级数遍历 $k,t$，总复杂度 $\mathcal{O}(n\log n)$。

或者直接前缀和维护一段值域区间上的 $a_i$ 以及 $b_i$ 分别的个数，检查是否相等也可以，这样更简单，瓶颈只在调和级数上。

代码：

```cpp
#include <bits/stdc++.h>
int n, a[200005], b[200005], c[200005];
inline int read(){
	char c = getchar();
	int x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
	return x;
}
int ll[200005], mi[19][200005];
inline int askmin(int l, int r){
	int p = ll[r - l + 1];
	return std::min(mi[p][l], mi[p][r - (1 << p) + 1]);
}
void solve(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) b[i] = read();
	for(int i = 1; i <= n; ++i) mi[0][i] = 1141141; 
	for(int i = 1; i <= n; ++i)
		if(a[i] > b[i])
			mi[0][a[i]] = std::min(mi[0][a[i]], b[i]);
	for(int i = 1; i <= 17; ++i)
		for(int j = 1; j + (1 << i - 1) <= n; ++j)
			mi[i][j] = std::min(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
	int cnt = 0;
	for(int k = 1; k <= n; ++k){
		c[k] = 1;
		for(int j = 1; j <= n; j += k){
			int ce = std::min(n, j + k - 1);
			if(askmin(j, ce) < j){
				c[k] = 0;
				break;
			}
		}
		cnt += c[k];
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= n; ++i) if(c[i] == 1) printf("%d ", i);
	printf("\n");
	return ;
}
int main(){
	int T = 1;
	ll[1] = 0;
	int now = 0;
	for(int i = 2; i <= 200000; ++i){
		ll[i] = now;
		if(i == (1 << now + 1)) ++now;
	}
	scanf("%d", &T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：Enjoy2024 (赞：0)

如果 $a_i\le b_i$，那么一定满足 $\lceil \frac{a_i}{k}\rceil\le \lceil \frac{b_i}{k}\rceil$。

否则，$a_i > b_i$ 且 $\lceil \frac{a_i}{k}\rceil\le \lceil \frac{b_i}{k}\rceil$ 那么当且仅当 $\lceil \frac{a_i}{k}\rceil= \lceil \frac{b_i}{k}\rceil$，也就是 $b_i\sim a_i-1$ 之间没有一个数 $t$ 满足 $t=xk$，其中 $k\in N^+$。

那么可以考虑使用线段树维护 $b_i\sim a_i-1$ 的数每一个数出现了多少次。

然后枚举 $k$，判断所有 $k$ 的因数出现次数是否都为 $0$ 即可。

---

## 作者：baka24 (赞：0)

本篇题解将讲述一种 $O(n\sqrt{n})$ 的卡常做法，如果您已经会了 $O(n\sqrt{n})$ 的做法，可以直接跳到卡常部分。

## 解法

首先转化题意，给定两个长度为 $n$ 的序列 $a,b$，求所有 $k\in[1,n]$，满足 $\lceil \frac{a_i}{k}\rceil\le \lceil\frac{b_i}{k}\rceil$。

考虑计算出对于每个 $i$ 满足 $\lceil \frac{a_i}{k}\rceil\le \lceil\frac{b_i}{k}\rceil$ 的 $k$，最后所有满足所有条件的 $k$ 即为所求。

对于单个 $i$，可以枚举不同的 $\lceil \frac{a_i}{k}\rceil$ 对应的区间，并计算出对应的符合 $b_i$ 限制的 $k$ 区间。

具体的，设 $l,r,x$ 分别表示当 $\lceil \frac{a_i}{k}\rceil=x$ 的最小的 $k$，最大的 $k$，每次我们让 $l\to r+1$，并计算对应的 $x,r$，就可以不重不漏的枚举所有区间。

暴力枚举所有区间的复杂度是 $O(a_i\sqrt{a_i})$，对于小于 $\sqrt{a_i}$ 的 $k$，一共有 $O(\sqrt{a_i})$ 个，对于大于等于 $\sqrt{a_i}$ 的 $k$，最多有 $O(\sqrt{a_i}))$ 个不同区间。

关于计算 $x,r$，有 $x=\lceil \frac{a_i}{l}\rceil,r=\lfloor\frac{a_i-1}{x-1}\rfloor$。

关于 $r$ 的计算方式：$r$ 是最大的满足 $\lceil \frac{a_i}{k}\rceil=x$ 的数，那么就有:
$$
\lceil\frac{a_i}{r}\rceil=x\\
\lfloor\frac{a_i-1}{r}+1\rfloor=x\\
\lfloor\frac{a_i-1}{r}\rfloor=x-1\\
r=\lfloor \frac{a_i-1}{x-1}\rfloor
$$

特别的，注意到当 $x=1$ 时除数为 $0$，所以还需要特判 $x=1$。

之后，我们已经得到 $(l,r,x)$ 后，只需要考虑如何计算出对应的，使得 $\lceil \frac{a_i}{k}\rceil\le \lceil\frac{b_i}{k}\rceil$ 的 $k$ 区间。

设 $x=\lceil \frac{a_i}{k}\rceil$，我们希望 $\lceil \frac{b_i}{k}\rceil\ge x$，则有：

$$
\lceil \frac{b_i}{k}\rceil\ge x\\
\lfloor \frac{b_i-1}{k}\rfloor+1\ge x\\
\lfloor \frac{b_i-1}{k}\rfloor\ge x-1\\
\lfloor \frac{b_i-1}{x-1}\rfloor\ge k\\
$$

同理也需要特判 $x=1$。

由此我们可以得到一个区间上界。对于每段区间，我们用差分维护每个点的被覆盖次数。如果这个点被覆盖 $n$ 次，那么这个点就是一个合法点。

## 卡常

[上面这个做法会在第 $22$ 个点超时。](https://codeforces.com/problemset/submission/1783/295817097)

考虑如何卡常。

注意到对于每个点，复杂度均为 $O(\sqrt{a_i})$，则当 $a_i=n$ 时将会卡满复杂度。

在 CF 上测一下会发现需要跑 $3$ 秒。

观察代码可以发现题目中多处地方需要除法，而 C++ 中的除法很慢。

考虑能不能少算几次除法。我们注意到对于相同的 $a_i$，所分出的区间是相同的，于是便可以对于相同的 $a_i$，统一处理出区间后再一起算。

这样在 $a_i$ 都很大的时候将会有超大优化，而在 $a_i$ 互不相同的时候又卡不满复杂度，$a_i$ 很小的点可以算的很快。

这样的优化下跑 $2\times 10^5$ 个 $n$ 只需要跑 $700$ 多毫秒，而跑 $2\times 10^5$ 个 $i$ 则需要 $1900$ 毫秒左右，勉强通过。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int> 
#define fr first
#define sc second 
#define mk make_pair
#define pb push_back
int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();return x*f;}
const int MAXN=200010;
int n,m,ans,cnt,a[MAXN],b[MAXN],p[MAXN];
void upd(int l,int r){
    if(l>r)return;
    p[l]++,p[r+1]--;
}
vector<pair<pii,int> >G;
pii q[MAXN];
void slv(){
    cnt=n=read();
    for(int i=1;i<=n;i++)a[i]=read(),p[i]=0;
    for(int i=1;i<=n;i++)b[i]=read();
    for(int i=1;i<=n;i++)q[i]={a[i],b[i]};
    sort(q+1,q+n+1);
    for(int i=1;i<=n;i++)a[i]=q[i].fr,b[i]=q[i].sc;
    for(int i=1;i<=n;i++){
        if(a[i]==a[i-1]){
            for(auto e:G){
                int l=e.fr.fr,r=e.fr.sc,o=e.sc;
                upd(l,min(r,o==1?n:(b[i]-1)/(o-1)));
            }
        }
        else {
            G.clear();
            for(int l=1,r=1,o=a[i];l<=n;l=r+1){
                o=(a[i]-1)/l+1,r=o==1?n:(a[i]-1)/(o-1);
                upd(l,min(r,o==1?n:(b[i]-1)/(o-1)));
                G.pb(mk(mk(l,r),o));
            }
        }
    }
    ans=0;
    for(int i=1;i<=n;i++){p[i]+=p[i-1];
        if(p[i]==n)ans++;
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)if(p[i]==n)printf("%d ",i);printf("\n");
}
signed main(){
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    int _=read();while(_--)
    slv();
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<"s\n";    
    return 0;
}
```

---

## 作者：forest114514 (赞：0)

提供一个复杂度更优的解法。

考虑怎么的 $k$ 是不合法的。

1. $a_i\le b_i$，一定合法，跳过。

2. $a_i>b_i$，找到所有满足 ${\left\lceil \frac{a_i}{k}\right\rceil }= \left\lceil \frac{b_i}{k}\right\rceil$ 的 $k$，然后删除不满足条件的 $k$ 即可。

   此时有有倍数在 $[b_i,a_i)$ 的均不成立，用差分将这个区间的 $c$ 加一。

最后求所有满足 $\sum\limits_{i|j}c_j=0$ 的 $i$ 的数量，注意到 $\sum\limits_{i|j}c_j$ 是一个迪利克雷后缀和的形式，可以 $O(n\log\log n) $ 实现。

时间复杂度为 $O(n\log \log n)$，虽然在原题数据范围相比 $O(n\log n)$ 没有显著的优势就是了。

代码：
```cpp
bitset<200001> vis;
void solve(){
	int n;read(n);
	vector<int> a(n+1),b(n+1),c(n+1,0);
	rep(i,1,n) read(a[i]);
	rep(i,1,n){
		read(b[i]);
		if(b[i]<a[i]){
			c[b[i]]++,c[a[i]]--;
		}
	}
	rep(i,1,n) c[i]+=c[i-1];
	rep(j,2,n){
		if(!vis[j]) 
			per(i,n/j,1) c[i]+=c[i*j],vis[i*j]=1;
		vis[j]=0;
	}
	vector<int> ans;
	rep(i,1,n) if(!c[i]) ans.pb(i);
	write((int)ans.size(),'\n');
	for(auto i:ans) write(i,' ');
	putchar('\n');
}
```

---

## 作者：masonpop (赞：0)

首先一定要读懂题目，先手能抢先杀死怪物等价于 $\lceil\frac{a_i}{k}\rceil\leq \lceil\frac{b_i}{k}\rceil$。容易发现如果 $a_i\leq b_i$ 那么显然成立了，下设 $a_i>b_i$。

考虑不合法的情况，也就是 $\lceil\frac{a_i}{k}\rceil> \lceil\frac{b_i}{k}\rceil$。关键结论是，它等价于，在区间 $[b_i,a_i-1]$ 之间存在 $k$ 的倍数，如图。
![](https://cdn.luogu.com.cn/upload/image_hosting/uq87ewy4.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)


那么接下来就简单了，我们枚举所有的 $i$，作区间覆盖，那么 $k$ 合法等价于没有任何一个它的倍数被覆盖。暴力枚举 $k$ 及其倍数，由于值域是 $n$，故均摊复杂度是调和级数级别的，即 $O(n\ln n)$，可以通过。至于区间覆盖？连树状数组都不需要，直接差分。[代码](https://codeforces.com/contest/1783/submission/209616532)。

---

## 作者：honglan0301 (赞：0)

## 题意简述

给定长度为 $n\ (n\leq 2\times 10^5)$ 的数组 $a,b\ (a_i,b_i \leq n)$, 求所有的 $k\ (1\leq k\leq n)$, 使得对于每一个 $i$, 都有 $\lceil {a_i\over k} \rceil \leq \lceil {b_i\over k} \rceil$。

## 题目分析

先考虑对一组 $a_i,b_i$ 如何求满足要求的 $k$。容易发现这等价于不存在一个 $k$ 的倍数 $kx$, 满足 $b_i\leq kx\leq a_i-1$。那么对于全部的 $a_i,b_i$, 我们可以先用差分预处理出不能成为 $k$ 的倍数的数，再对于每个 $k$ 直接枚举其所有的倍数是否均满足要求即可。时间复杂度 $\sum {n\over i}=O(n\log n)$, 可以通过本题。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int t,n,a[200005],b[200005],cf[200005],sum[200005];
vector <int> ans;

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i]; for(int i=1;i<=n;i++) cin>>b[i];
		for(int i=1;i<=n;i++) cf[i]=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<=b[i]) continue;
			cf[b[i]]++; cf[a[i]]--;
		}
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+cf[i];
		ans.clear();
		for(int i=1;i<=n;i++)
		{
			bool flag=1;
			for(int j=i;j<=n;j+=i)
			{
				if(sum[j]) {flag=0; break;}
			}
			if(flag) ans.push_back(i);
		}
		cout<<ans.size()<<endl;
		for(auto i:ans) cout<<i<<" ";
		cout<<endl;
	}
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# CF1783E 题解



## 思路分析

转化题意，得到题目实际是让你求满足 $\forall i\in[1,n]:\left\lceil\dfrac{a_i}k\right\rceil\le \left\lceil\dfrac{b_i}k\right\rceil$ 的 $k$ 的数量。

容易想到用整除分块对于每个 $(a_i,b_i)$ 进行二维数论分块计算 $k$ 合法的区间，但是 $\Theta(n\sqrt n)$ 的复杂度容易被卡常，事实上还有复杂度更加优秀的算法。

转化一下 $\left\lceil\dfrac{a_i}k\right\rceil\le \left\lceil\dfrac{b_i}k\right\rceil$，显然对于 $a_i\le b_i$，这样的 $k$ 恒成立，因此只考虑 $a_i>b_i$ 的情况，就等价于不存在 $t$ 使得 $b_i\le tk<a_i$，因此用差分对每个区间 $[a_i,b_i)$ 进行覆盖，如果 $k$ 的某个倍数被覆盖那么 $k$ 不合法。

时间复杂度 $\Theta(n\ln n)$，瓶颈在枚举 $k$ 和 $k$ 的所有倍数上。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int a[MAXN],b[MAXN],d[MAXN];
inline void solve() {
	int n;
	vector <int> ans;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) d[i]=0;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	for(int i=1;i<=n;++i) if(a[i]>b[i]) ++d[b[i]],--d[a[i]];
	for(int i=1;i<=n;++i) d[i]+=d[i-1];
	for(int i=1;i<=n;++i)  {
		bool ok=true;
		for(int j=i;j<=n;j+=i) {
			if(d[j]) {
				ok=false;
				break;
			}
		}
		if(ok) ans.push_back(i);
	}
	printf("%d\n",(int)ans.size());
	for(int i:ans) printf("%d ",i);
	puts("");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

