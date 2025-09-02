# Simple Permutation

## 题目描述

给定一个整数 $n$。构造一个长度为 $n$ 的排列 $p_1, p_2, \ldots, p_n$，使其满足以下性质：

对于 $1 \le i \le n$，定义 $c_i = \lceil \frac{p_1 + p_2 + \ldots + p_i}{i} \rceil$，那么在 $c_1, c_2, \ldots, c_n$ 中必须至少有 $\lfloor \frac{n}{3} \rfloor - 1$ 个素数。

## 说明/提示

第一个测试案例中，$c_1 = \lceil \frac{2}{1} \rceil = 2$，$c_2 = \lceil \frac{2+1}{2} \rceil = 2$。这两个数都是素数。

第三个测试案例中，$c_1 = \lceil \frac{2}{1} \rceil = 2$，$c_2 = \lceil \frac{3}{2} \rceil = 2$，$c_3 = \lceil \frac{6}{3} \rceil = 2$，$c_4 = \lceil \frac{10}{4} \rceil = 3$，$c_5 = \lceil \frac{15}{5} \rceil = 3$。所有这些数都是素数。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
2
3
5```

### 输出

```
2 1
2 1 3
2 1 3 4 5```

# 题解

## 作者：luckyclover (赞：3)

构造 $p$ 的前 $\lfloor\frac{n}{3}\rfloor-1$ 项为 $a,a-1,a+1,a-2,a+2,\cdots$，$a$ 是素数，满足 $2\times\min(n-a,a-1)+1\ge\lfloor\frac{n}{3}\rfloor-1$，则 $c_1=c_2=\cdots=c_{\lfloor\frac{n}{3}\rfloor-1}=a$。

证明：在 $(\lfloor\frac{n}{3}\rfloor,2\lfloor\frac{n}{3}\rfloor]$ 间必有一个素数，所以一定存在这样的 $a$。

时间复杂度 $O(n)$，赛时的实现是 $O(n\log n)$ 的。

[submission](https://codeforces.com/contest/2090/submission/311991134)

---

## 作者：Muel_imj (赞：1)

一个性能惊人的随机化做法。

可以发现，$c_i$ 的值可以一直都不是很大，而质数其实没那么稀疏（质数定理，$n$ 以内质数数量大约与 $\frac{n}{\ln n}$ 同阶）。所以随机 $p_i$ 也是有不小的概率让 $c_i$ 为质数的。

于是每个 $p_i$ 都直接随机选 200 次，如果中途 $c_i$ 变成了质数就停止。写出来发现 $n$ 较大时 $c_i$ 是质数的情况经常能占 99% 以上！？

用筛法预处理来判断质数，差不多筛到 $10^6$ 就够用了，筛 $10^7$ 也不费事。然后随机选 200 次其实在前期基本跑不满，只有后期这个次数才会用的多一点。

所以时空复杂度也挺好的。就很暴力的解决了。

```cpp
#include<bits/stdc++.h>
#define EL puts("Elaina")
typedef long long ll;
using namespace std;
random_device rd;mt19937 rnd(rd());
inline int rand(int l,int r){return uniform_int_distribution<int>(l,r)(rnd);}
const int maxn=1e6+5,maxm=2e7+3;
bitset<maxm> vis;
inline void Eratosthenes(const int n=20000000){
	int i=2;vis[1]=1;
	for(;i*i<=n;++i)if(vis[i]==0)
		for(int j=i+i;j<=n;j+=i)vis[j]=1;
}
inline bool check(ll n){return vis[n]==0;}
int n,p[maxn],a[maxn],pos[maxn];
inline void MyDearMoments(){
	scanf("%d",&n),iota(a+1,a+n+1,1),iota(pos+1,pos+n+1,1);
	ll sum=0;
	for(int i=1;i<=n;++i){
        int j,tms=200;
        while(tms--){
            j=rand(1,n-i+1);
            if(check((sum+a[j]-1)/i+1))break;
        }
        p[i]=a[j],pos[a[n-i+1]]=j,a[j]=a[n-i+1];
		sum+=p[i];
	}
	for(int i=1;i<=n;++i)printf("%d ",p[i]);
    puts("");
}
int main(){
	Eratosthenes();
	int T;scanf("%d",&T);
	while(T--)MyDearMoments();
	return 0;
}
```

---

## 作者：Jordan_Pan (赞：1)

介绍一个非常抽象的随机算法。

发现 $c_i$ 的范围是 $[1,n]$，这个范围里的质数分布并不密集，所以直接 random_shuffle 就似了。

所以考虑分块，对于每长度为 $k$ 的块，随机打乱 $d$ 次，如果超过一半的 $c_i$ 是质数就直接退出。

但是这样不能很好地保证正确性，没关系多做几次直到满足要求就可以了。

经过调参，$k=100$ 且 $d=50$ 直接过了。


```cpp
#include<bits/stdc++.h>
constexpr int rSiz=1<<21;
char rBuf[rSiz],*p1=rBuf,*p2=rBuf;
#define gc() (p1==p2&&(p2=(p1=rBuf)+fread(rBuf,1,rSiz,stdin),p1==p2)?EOF:*p1++)
template<class T>void rd(T&x){
	char ch=gc();
	for(;ch<'0'||ch>'9';ch=gc());
	for(x=0;ch>='0'&&ch<='9';ch=gc())
		x=(x<<1)+(x<<3)+(ch^48);
}
int st[14],tp;
void wt(int x){
	tp=0;
	for(;x;x/=10)st[++tp]=x%10;
	if(!tp)st[++tp]=0;
	for(;tp;tp--)putchar(st[tp]+'0');
}
constexpr int _=1e5+5;
bool isp[_];int p[_],cnt;
void init(int M){
	for(int i=2;i<=M;i++){
		if(!isp[i])p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<=M;j++){
			isp[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
std::mt19937 Rnd(std::chrono::steady_clock::now().time_since_epoch().count());
int Get(int m){return Rnd()%m+1;}
int n,m,k,a[_],b[_];
void solve(){
	rd(n);m=n/3-1;
	if(n<=100){
		k=1;
		for(;k*k<=n;k++);
		k--;
	}
	else k=100;
	for(;;){
		m=n/3-1;
		for(int i=1;i<=n;i++)a[i]=i;
		long long sum=0;
		for(int i=1;i<=n;i+=k){
			int qwq=0;
			for(int o=1;o<=50;o++){
				long long val=sum;int tot=0,tpp=std::min(i+k,n+1);
				for(int j=i;j<tpp;j++){
					std::swap(a[j],a[n-Get(n-j+1)+1]);val+=a[j];
					if(!isp[(val+j-1)/j])tot++;
				}
				if(tot>qwq){
					qwq=tot;
					for(int j=i;j<=n;j++)
						b[j]=a[j];
					if(qwq>k/2)break;
				}
			}
			m-=qwq;
			for(int j=i;j<=n;j++){
				a[j]=b[j];
				if(j<i+k)sum+=a[j];
			}
			if(m<=0||m-(n-(i+k)+1)/2>0)break;
		}
		if(m<=0)break;
	}
	for(int i=1;i<=n;i++)
		wt(a[i]),putchar(' ');
	putchar(10);
}
int main(){
	init(1e5);isp[1]=1;
	int T;rd(T);
	for(;T;T--)solve();
}
```

奇怪的是 CF 有三个编译语言，G++17、G++20 和 G++23，用 G++17 过不了所以进行疯狂的卡常，疑似没开 O2？

---

## 作者：__hjyakioi__ (赞：1)

赛时乱搞做法。

## 做法
记 $c$ 为目前的 $c_i$ 。\
显然，$c$ 为质数时选择最小的 $p_i$ 最优。\
否则，二分选择一个合适的 $p_i$ 使得 $c_{i+1}$ 为质数。如无法选择，选最大的。这样选择较优。\
可以通过维护`set`来加速到单次 $O(\log n)$ 的时间复杂度。\
[AC code](https://codeforces.com/contest/2090/submission/312026920)

---

