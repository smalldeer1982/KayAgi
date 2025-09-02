# Guess the Permutation

## 题目描述

This is an interactive problem.

Jury initially had a sequence $ a $ of length $ n $ , such that $ a_i = i $ .

The jury chose three integers $ i $ , $ j $ , $ k $ , such that $ 1 \leq i < j < k \leq n $ , $ j - i > 1 $ . After that, Jury reversed subsegments $ [i, j - 1] $ and $ [j, k] $ of the sequence $ a $ .

Reversing a subsegment $ [l, r] $ of the sequence $ a $ means reversing the order of elements $ a_l, a_{l+1}, \ldots, a_r $ in the sequence, i. e. $ a_l $ is swapped with $ a_r $ , $ a_{l+1} $ is swapped with $ a_{r-1} $ , etc.

You are given the number $ n $ and you should find $ i $ , $ j $ , $ k $ after asking some questions.

In one question you can choose two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ) and ask the number of inversions on the subsegment $ [l, r] $ of the sequence $ a $ . You will be given the number of pairs $ (i, j) $ such that $ l \leq i < j \leq r $ , and $ a_i > a_j $ .

Find the chosen numbers $ i $ , $ j $ , $ k $ after at most $ 40 $ questions.

The numbers $ i $ , $ j $ , and $ k $ are fixed before the start of your program and do not depend on your queries.

## 说明/提示

In the first test case, $ i = 1 $ , $ j = 3 $ , $ k = 5 $ , so the sequence $ a $ is $ [2, 1, 5, 4, 3] $ .

In the second test case, $ i = 2 $ , $ j = 4 $ , $ k = 5 $ , so the sequence $ a $ is $ [1, 3, 2, 5, 4] $ .

## 样例 #1

### 输入

```
2 
5 

4 

3 

3 

5 

2 

2 

1```

### 输出

```
? 1 5

? 2 5

? 3 5

! 1 3 5

? 1 5

? 2 5

? 3 5

! 2 4 5```

# 题解

## 作者：scp020 (赞：3)

# CF1584D Guess the Permutation 题解

被薄纱了。

## 解法

考虑何时产生逆序对。在翻转两个不相交的区间后，原序列被分为四段，分别是 $[1,i-1],[i,j-1],[j,k],[k+1,n]$。

每一段中数都是单调的，分别是单调递增，单调递减，单调递减，单调递增。只有中间两段内部有逆序对，个数分别是 $\dfrac{(j - i) \times (j - i - 1)}{2},\dfrac{(k - j + 1) \times (k - j)}{2}$。我们询问 $[1,n]$ 中逆序对的个数等价于询问 $[i,k]$ 中逆序对的个数。

我们二分确定 $i$ 的值，即每次询问 $[1,mid]$ 中逆序对的个数，如果没有逆序对则表示 $mid \le i-1$，否则表示 $mid \ge i$。

下一步确定 $j$ 的值。我们可以询问 $[i,n]$ 中逆序对的个数，这等价于询问 $[i,k]$ 中逆序对的个数。我们再询问 $[i+1,n]$ 中逆序对的个数。根据上面的推导，设 $[i,n]$ 中逆序对的个数为 $x_1$，$[i+1,n]$ 中逆序对的个数为 $x_2$，则 $x_1 - x_2 = \dfrac{(j - i) \times (j - i - 1)}{2} - \dfrac{(j - i - 1) \times (j - i - 2)}{2} = j - i - 1$。因为我们已经确定了 $i$ 的值，所以即可确定 $j$ 的值。

类似于 $j$，我们可以确定 $k$ 的值。我们可以询问 $[j,n]$ 中逆序对的个数和 $[j+1,n]$ 中逆序对的个数。设 $[j,n]$ 中逆序对的个数为 $x_1$，$[j+1,n]$ 中逆序对的个数为 $x_2$，则 $x_1 - x_2 = \dfrac{(k - j + 1) \times (k - j)}{2} - \dfrac{(k - j) \times (k - j - 1)}{2} = k - j$。

在二分过程中，我们最多询问 $\lceil \log_2 10^9 \rceil = 30$ 次确定 $i$，再用 $4$ 次确定 $j,k$。所以一定在 $40$ 次以内。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,l,r,mid,tmp,i,j,k,xx1,xx2;
inline void ask(const int &l,const int &r) noexcept
{
	printf("? %d %d\n",l,r),fflush(stdout);
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		l=1,r=n;
		while(l<=r)
		{
			mid=(l+r)/2,ask(1,mid),scanf("%lld",&tmp);
			if(tmp==0) l=mid+1;
			else r=mid-1;
		}
		i=l-1;
		ask(i,n),ask(i+1,n),scanf("%lld %lld",&xx1,&xx2);
		j=xx1-xx2+i+1;
		ask(j,n),ask(j+1,n),scanf("%lld %lld",&xx1,&xx2);
		k=xx1-xx2+j;
		printf("! %lld %lld %lld\n",i,j,k),fflush(stdout);
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：2)

> CF1584D. [Guess the Permutation](https://codeforces.ml/problemset/problem/1584/D) *2000

显然我们首先得二分出至少一个边界 $l$，这是容易的。但是剩余的询问次数不足以再进行一次二分。我们知道序列 $a,a-1,\cdots,2,1$ 的逆序对个数为 $\dbinom {a-1}2$，$\dbinom a 2-\dbinom{a-1}2=a-1$ 这一性质启发我们通过用 $[l,n]$ 的逆序对个数与 $[l+1,n]$ 的逆序对个数作差，就可以得到 $k-l$ 的长度。长度一旦确定，$[l,k-1]$ 的逆序对数量以及 $k$ 就固定了，从而可以计算出 $[k,r]$ 的逆序对个数并反推出 $[k,r]$ 的长度，把右边界 $r$ 确定下来。解关于 $x$ 的方程 $\dbinom{x}2=y$ 可以使用数学或二分法，为了保险赛时写了二分。总询问次数 $3+\log n\approx 33$，$3$ 是询问 $[1,n]$，$[l,n]$ 和 $8[l+1,n]$。

代码见 https://codeforces.com/contest/1588/submission/135350305 。

---

## 作者：_sunkuangzheng_ (赞：1)

**【题目大意】**

交互库有一个长度为 $n(1 \le n \le 10^9)$ 的排列 $p$，满足 $p_i = i$。现在区间 $[i,j-1]$ 和 $[j,k]$ 两个区间的排列被翻转。你每次可以询问一个区间 $[l,r]$ 内的逆序对数量。你需要在 $40$ 次询问内猜出 $i,j,k$。

**【题目分析】**

首先我们注意到在没有翻转的地方逆序对数量为 $0$。因此我们一定可以二分出左端点 $i$，最多需要 $\log_2 10^9 = 30$ 次询问。这样我们就只剩 $10$ 次询问了。（悲）

那我们考虑如何确定 $j,k$。考虑一个被被翻转的区间 $[l,r]$，如果我们询问 $[l+1,r]$ 的逆序对，我们就可以通过这两者逆序对数量的差值，推断出区间的长度。因此我们可以在 $2$ 次询问内得到 $j$ 的值。同理，$2$ 次询问也可以得到 $k$ 的值。这样我们就用 $34$ 次询问完成这道题啦！

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,tmp;
int ask(int a,int b){cout << "? " << a << " " << b << endl,cin >> tmp;return tmp;}
int sb(int a,int b,int c){
    int l = a,r = b;
    while(l <= r){
        int mid = (l + r) / 2;
        if(ask(a,mid) == c) l = mid + 1;
        else r = mid - 1; 
    }return l-1;
}
signed main(){
    cin >> t;
    while(t --){
        cin >> n;
        int i = sb(1,n,0),j = ask(i,n),k = ask(i+1,n),p = i + j - k + 1;
        int l = ask(p,n),r = ask(p+1,n),q = p + l - r;
        ask(2,n),ask(1,n-1);//如果交互库的逆序对实现的是 O(n log n) 并且特判掉了 ask(1,n)，我们就让他愉快的死掉吧！
        cout << "! " << i << " " << p << " " << q << endl;
    }
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$
---
### 解题思路：

首先确定是二分，关键是如何二分。因为只有 $40$ 次查询，想要通过三次二分查询是不现实的。

但是可以确定的是，至少需要二分出三个结果中的一个才能继续做下去。中间的点很难确定，左右两边的对称，不妨取左边的点。

---
在二分出左端点之后，可以发现，其实再查询四次就可以得出结果了。

首先向右查询一次（或者用最一开始的查询结果，反正就是包括了整个经过颠倒的区间的一个答案，不过好像不卡这个），不妨设为 $a$。然后查询左端点向右一个单位到最右边，不妨设得到的结果为 $b$。

两次答案更改的量是 $a-b$，就是翻转的左半区间的长度减一，因为受到影响的只有最左边的一个点，而这个点产生的贡献就是左区间的长度减一。

根据左端点的位置和左区间的长度，求得中间点的位置，然后就可以用同样的方法求出右端点。

---
记得开 $\text{long long}$。

---
### 代码：
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
#define int long long
int n,T,l,r,mid,ans,x,y,z,I,J,K;
int query(int x,int y){
	printf("? %I64d %I64d\n",x,y);
	fflush(stdout);
	int z=0;
	scanf("%I64d",&z);
	return z;
}
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		l=1,r=n;
		while(l<=r){
			mid=(l+r)>>1;
			x=query(1,mid);
			if(x>0)r=mid-1;
			else ans=mid,l=mid+1;
		}
		I=ans;
		x=query(I,n);
		y=query(I+1,n);
		J=I+x-y+1;
		x=query(J,n);
		y=query(J+1,n);
		K=J+x-y;
		printf("! %I64d %I64d %I64d\n",I,J,K);
		fflush(stdout);
	}
	/*
	x^2+x-2c
	d=sqrt(1+8c)
	\dfrac{-1+d}{2}
	*/
	return 0;
}
```


---

## 作者：CSP_Sept (赞：1)

**[Technocup 2022 - Elimination Round 2](http://codeforces.com/contest/1584)** [A](https://www.luogu.com.cn/blog/supervise/solution-cf1584a) / [B](https://www.luogu.com.cn/blog/supervise/solution-cf1584b) / [C](https://www.luogu.com.cn/blog/supervise/solution-cf1584c) / D / [E](https://www.luogu.com.cn/blog/supervise/solution-cf1584e) / [F](https://www.luogu.com.cn/blog/supervise/solution-cf1584f) / [G](https://www.luogu.com.cn/blog/supervise/solution-cf1584g)

如果以上链接所指链接不存在，就是作者咕了 /dk

### Description

**这是一道交互题。**

给定一个长度为 $n$ 的数列 $a$，满足 $a_i=i$。

现在选择了 $i,j,k(1\le i<j<k\le n,j-i>1)$，翻转区间 $[i,j-1],[j,k]$。

你每次可以询问交互库 $[l,r]$ 的逆序对个数。

你需要用不超过 $40$ 次询问确定 $i,j,k$ 的值。

### Soluition

我们记 $Q(l,r)$ 表示询问 $l,r$ 得到的答案。

显然有 $Q(1,i)=0$，我们可以二分 $i$，每次询问 $1,i$，直到二分区间长度为 $1$ 为止。

这样使用了 $\log10^9<30$ 次询问。

接下来我们询问 $[i,k],[i+1,k]$，记 $Q_1=Q(i,k)-Q(i+1,k)$。

则 $Q_1$ 就是满足 $p>i\And a_p<a_i$ 的数的个数。

容易发现 $\forall p\in[i+1,j-1]$ 都满足这一条件，而 $\forall p\in[j,n]$ 都不满足这一条件。

于是 $Q_1$ 就是 $[i+1,j-1]$ 的长度，即 $Q_1=j-i-1$，进一步可推得

$$
j=i+Q_1+1
$$

我们继续询问 $[j,n],[j+1,n]$，记 $Q_2=Q(j,n)-Q(j+1,n)$。

同理有

$$
k=j+Q_2
$$

这样我们在 $34$ 次询问内完美解决了问题。

### Code

[$\textit{135387087}$](http://codeforces.com/contest/1589/submission/135387087)

---

## 作者：steambird (赞：0)

## 思路

看到查询次数要求，首先考虑二分。

一种容易想到的思路是分别二分两个端点 $i,k$，然后查询 $[i+1,k]$。设两段被反转的区间长度分别为 $a,b$，两次查询所得值的差值即为 $a-1$（第 $i$ 个数和 $[i+1, j-1]$ 内的每个数产生一个逆序对），即 $j=i+a$。

但是二分一个端点需要 $\lceil \log n \rceil$ 次查询，$n = 10^9$ 时大约为 $30$ 次，两个端点就要 $60$ 次，超过了 $40$ 次的限制，因此不能二分两个端点，只能二分一个端点。

假设我们二分的是左端点 $i$（右端点思路类似），我们如何通过这个信息获取右端点 $k$ 和中间端点 $j$ 的位置呢？

注意到 $\forall x \in [i,j-1], \forall y \in [j, k], a_x < a_y$，故 $[i, j-1]$ 和 $[j, k]$ 两部分之间不会产生逆序对，整个序列的总逆序对数 $N = {{a(a-1)} \over 2} + {{b(b-1)} \over 2}$。

已知 $N,a$，通过二分或解一元二次方程等方法即可求出 $b$。下面给出的代码使用二分法。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

inline void train() {
	   ios::sync_with_stdio(false);
	   cin.tie(0);
	   cout.tie(0);
}

int ansl, ansr;

map<pair<int, int>, long long> cache; 

long long ask(int l, int r) {
	auto p = make_pair(l, r);
	if (cache.count(p)) return cache[p];
	cout<<"? "<<l<<" "<<r<<"\n"<<flush;
	long long x;
	cin>>x;
	if (x == -1) {
		cout<<"OH NO!!!"<<endl;
		exit(0);
	}
	return cache[p] = x;
}

int main() {

	train();
	
	int t;
	cin>>t;
	for (int gs = 0; gs < t; gs++) {
		cache.clear();
		int n;
		cin>>n;
		ansl = 1;
		ansr = n;
		long long tot,x;
		tot = ask(1, n);
		int l = 1, r = n;
		while (l <= r) {
			int mid = (l+r) >> 1;
			x = ask(mid, n);
			if (x == tot) {
				ansl = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		x = ask(ansl+1, ansr);
		long long diff = tot - x;
		
		long long llen = diff + 1;
		long long lcontrib = (llen * (llen - 1)) >> 1;
		long long rcontrib = tot - lcontrib;
		
		l = 1;
		r = n;
		long long ans = -1;
		while (l <= r) {
			int mi = (l + r) >> 1;
			long long mid = mi;
			long long cur = (mid * (mid - 1)) >> 1;
			if (cur >= rcontrib) {
				ans = mid;
				r = mi - 1;
			} else {
				l = mi + 1;
			}
		}
		cout<<"! "<<ansl<<" "<<(ansl+diff+1)<<" "<<(ansl+diff+ans)<<"\n"<<flush;
	}

	return 0;
}
```

---

## 作者：伊地知虹夏 (赞：0)

这有 2000？

我们考虑先找到 $i$，二分最大的使得 $[1, p]$ 中逆序对数量为 $0$ 的位置 $p$，这个 $p$ 就是题目中的 $i$。为什么呢？考虑第一个逆序对产生在哪里，显然是 $(i, i+1)$，所以二分出来的 $p$ 即为 $i+1-1 = i$。这里共用 $32$ 次。

设 $x = j-i,y = k-j+1$，容易知道 $[1,n]$ 中的逆序对数为 ${x \choose 2} + {y \choose 2}$，我们询问 $[i,n]$，令答案为 $A$。

我们想办法求出这个 $x$，与 $i$ 组成的逆序对个数刚好是 $x-1$，那么我们询问 $[i+1,n]$，令答案为 $B$，则 $x = A-B+1$，共用 $2$ 次。

既然知道 $x,A$，那么 $y$ 就很好求了，你写个二分或是直接暴力解一元二次方程，我选择的是前者。到这就做完了，共用 $34$ 次，可以通过本题，[评测情况](https://codeforces.com/problemset/submission/1584/271742415)

---

## 作者：Inui_Sana (赞：0)

vp 时候搞出来的 $\le\log n+2+?$ 次询问做法。看了一圈没有做法跟我相同的，为什么呢。

首先看到 $40$ 次猜测是一次二分的 $\log$ 加上常数。然后发现，如果我们找到了 $j$，又知道 `? 1 n` 和 `? 1 j-1` 的结果，就可以解出来 $i,k$。于是想怎么二分。

设当前二分到 $mid$，我们先询问 $[1,mid]$ 得到 $x$，然后开始分讨：

- $x=0$ 则 $j>mid$。

- $x$ 等于询问 $[1,n]$ 的答案则 $j<mid$。

- $\exists k,x=\binom{k}{2}$，此时是都有可能的，于是再询问 $[1,mid+1]$ 得到 $y$，分情况：

- $\exists m,y=\binom{m}{2}\land m=k+1$，则一定有 $j<mid$，因为 $mid+1$ 显然仍在第一段区间内。

- $y=x$ 则容易发现，一定有 $mid+1=j$，否则会有 $y>x$。

- 否则 $mid>j$。

但是这样询问次数可能去到 $2\log n$。考虑怎么样节省一点。发现如果出现过上述第三种情况的第一种小情况，则可以记录一个位置，并且以后根据记录的这个位置就可以判断出是否还在第一段。

对于第二种小情况，遇到了可以直接 break。第三种情况大概猜测会分散在不同位置，遇到概率不大，不会造成多少次额外的询问。

于是就是 $\log n+2+?$ 次解决了。

code：

```cpp
int n,m;
il ll ask(int l,int r){
	printf("? %d %d\n",l,r);
	fflush(stdout);
	ll x;read(x);
	if(x==-1){
		exit(0);
	}
	return x;
}
il bool check(ll x){
	ll y=sqrt(x*2)+1;
	return x==y*(y-1)/2;
}
void Yorushika(){
	read(n);
	ll s=ask(1,n);
	int l=1,r=n,ans=0;
	int p=0,x=0;
	while(l<=r){
		int mid=(l+r)>>1;
		ll tmp=0;
		if(check(tmp=ask(1,mid))){
			if(!tmp){
				ans=mid,l=mid+1;
				continue;
			}
			ll z=sqrt(tmp*2)+1;
			if(p){
				if(z==x+mid-p){
					ans=mid,l=mid+1;
				}else{
					r=mid-1;
				}
			}else{
				ll tmpp;
				if(mid<n&&tmp!=s&&(tmpp=ask(1,mid+1))==(z+1)*z/2){
					ans=mid,l=mid+1;
					p=mid,x=z;
				}else{
					if(tmpp==tmp&&tmp!=s){
						ans=mid;
						break;
					}
					r=mid-1;
				}
			}
		}else{
			r=mid-1;
		}
	}
	ll tmp=ask(1,ans);
	ll u=sqrt(tmp*2)+1;
	tmp=s-tmp;
	ll v=sqrt(tmp*2)+1;
	printf("! %lld %d %lld\n",ans-u+1,ans+1,ans+v);
	fflush(stdout);
}
signed main(){
	int t=1;
		 read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：lzyqwq (赞：0)

我是真的一点脑子没有啊 /ll。

题目说要求至多询问 $40$ 次，发现这个数约为 $\mathcal{O}(\log n)$，因此先考虑二分。

我们先用一次询问 $\texttt{?}\space\space 1\space\space n$，得到总逆序对数 $N$。

然后，当我们询问一个前缀的逆序对个数时，这个东西是单调不降的，而 $k$ 就是最小的满足 $[1,m]$ 逆序对数为 $N$ 的 $m$。因此可以再用 $\mathcal{O}(\log n)$ 次二分询问得到 $k$。

现在，剩余询问次数不足 $10$ 次。如果故技重施肯定不行。我们考虑反转的两端长度分别为 $a,b$，则 $j=k-b+1$，$i=j-a$。那么有 $a(a-1)+b(b-1)=2N$。

注意到原来的排列是 $a_i=i$，我们考虑 $[1,i-1],[i,j-1],[j,k],[k+1,n]$ 这四个段，则任意两端之间不会产生逆序对。并且一、四段内部不会产生逆序对。因此对于一个数 $x$，若它在 $[i,j-1]$ 这一段，则以它为较大位置的逆序对数为 $x-i$，考虑它和这一段前面每一个点都会产生逆序对。在 $[j,k]$ 的情况类似。

那么神奇的事情发生了，我们再使用一次询问 $\texttt{?}\space\space 1\space\space k-1$ 得到新的结果 $M$，则 $N-M$ 就是 $k$ 这个位置产生的逆序对数。**它恰好等于 $\boldsymbol{b-1}$**。这样我们就可以知道 $j$ 了。

然后我们只剩一个关于 $a$ 的一元二次方程，可以直接解出来，但是也可以根据 $y=x(x-1)$ 在 $(0,+\infty)$ 的单调性二分得到 $a$，二分最后一个 $a(a-1)\ge 2N-b(b-1)$ 的 $a$。

那么 $i,j,k$ 就全部解出来了，只需要用到 $35$ 次不到的询问。

[AC Link & Code](https://codeforces.com/contest/1584/submission/273052276)

---

