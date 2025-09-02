# Lightsabers (hard)

## 题目描述

There used to be unrest in the Galactic Senate. Several thousand solar systems had declared their intentions to leave the Republic. But fear not! Master Heidi was able to successfully select the Jedi Knights that have restored peace in the galaxy. However, she knows that evil never sleeps and a time may come when she will need to pick another group of Jedi Knights. She wants to be sure she has enough options to do so.

There are $ n $ Jedi Knights, each of them with a lightsaber of one of $ m $ colors. Given a number $ k $ , compute the number of differently colored collections of $ k $ lightsabers that some $ k $ Jedi Knights might have. Jedi Knights with lightsabers of the same color are indistinguishable (it's not the person, it's the lightsaber color that matters!), and their order does not matter; that is, we consider two collections of Jedi Knights to be different if and only if their vectors of counts of lightsabers of each color (like what you were given in the easy and the medium versions) are different. We count all subsets, not only contiguous subsegments of the input sequence. Output the answer modulo $ 1009 $ .

## 样例 #1

### 输入

```
4 3 2
1 2 3 2
```

### 输出

```
4
```

# 题解

## 作者：zac2010 (赞：2)

对于一种元素 $v$，假设它在给出可重集合中出现了 $t$ 次，那么容易把它表示成基础的生成函数形式：$1+x+x^2+x^3+\dots+x^t$。

显然，把所有元素的生成函数卷一下就是答案。但是这样最坏情况为 $O(nm\log n)$的，不能通过这道题。

在思考优化方式时，容易想到启发式合并来优化这个过程。但是启发式合并本质上就是对分治的同一层区间进行无序合并，二者复杂度相同，故而我采取了比较好写的分治。

```cpp
#include <bits/stdc++.h>
namespace Poly{
    constexpr int N = 2.7e5 + 10;
    constexpr double Pi = acos(-1);
    int n, m, p[N];
    std::complex<double> f[N], g[N];
    void FFT(int n, std::complex<double> *c, int x = 1){
        for(int i = 0; i < n; ++i) if(i < p[i]) std::swap(c[i], c[p[i]]);
        for(int b = 2, k = 1; b <= n; b <<= 1, k <<= 1){
            std::complex<double> t(cos(2 * Pi / b), sin(2 * Pi / b) * x), w(1, 0);
            for(int i = 0; i < n; i += b, w = 1){
                for(int j = 0; j < k; ++j, w *= t){
                    c[i + j] += c[i + j + k] * w;
                    c[i + j + k] = c[i + j] - c[i + j + k] * w - c[i + j + k] * w;
                }
            }
        }
    }
    std::vector<double> Convolution(const auto &a, const auto &b){
        if(!a.size() || !b.size()) return std::vector<double>();
        n = a.size(), m = b.size();
        int l = 1 << (int)ceil(log2(n + m - 1));
        for(int i = 0; i < l; ++i){
            f[i] = i < n? a[i] : 0, g[i] = i < m? b[i] : 0;
            p[i] = (p[i >> 1] >> 1) | (i & 1? l >> 1 : 0);
        }
        n += m - 1, FFT(l, f), FFT(l, g);
        for(int i = 0; i < l; ++i) f[i] *= g[i];
        FFT(l, f, -1); std::vector<double> ret;
        for(int i = 0; i < n; ++i)
            ret.emplace_back(f[i].real() / l);
        return ret;
    }
}
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
typedef std::vector<int> vi;
using Poly::Convolution;
constexpr int N = 2e5 + 10, P = 1009;
int n, m, k, cnt[N];
vi Solve(int l, int r){
    if(l == r) return vi(cnt[l] + 1, 1);
    int mid = l + r >> 1;
    vi t1 = Solve(l, mid), t2 = Solve(mid + 1, r), ret;
    auto t = Convolution(t1, t2);
    for(auto x: t) ret.emplace_back((long long)round(x) % P);
    vi().swap(t1), vi().swap(t2), std::vector<double>().swap(t);
    return move(ret);
}
int main(){
    scanf("%d%d%d", &n, &m, &k); int x;
    FL(i, 1, n) scanf("%d", &x), ++cnt[x];
    vi ans = Solve(1, m);
    printf("%d\n", ans[k]);
    return 0;
}
```


---

## 作者：Leap_Frog (赞：2)

### P.S.
有意思的生成函数题。  
需要`FFT`来优化。  
翻译已提交，布吉岛能不能过。  


### Problem.
给你一个可重集，求它大小为$k$的子集有多少种不同的情况。  

### Solution.
首先，这很**显然**是生成函数。  
如果不会生成函数的建议见自行百度`生成函数`或`母函数`，也可参照`数学一本通`自行了解学习。  
如果不会FFT的建议自行参照鰰的博客，或自行百度`FFT`学习，笔者在这里不再赘述。  
这道题它是可重集，所以我们要用普通型生成函数。  
对于每个可重集的数，我们记它的个数为$k$。  
对于这个数，它的普通型生成函数为$(1+x+...+x^k)$  
于是这题的答案为$(1+x+...+x^{k_1})(1+x+...+x^{k_2})...$的答案的$x^k$的系数。  
于是我们直接模拟一下上面这个多项式的乘法就好了（（（  
可是，正常的多项式乘法复杂度是$O(n^2)$的，我们用FFT来优化它。  
可是，正常的FFT复杂度是$O(n\log n)$的，这里我们需要进行最多$n$次多项式乘法，复杂度会被卡成$O(n^2\log n)$。  
于是，我们用启发式合并的方法来优化这$n$次FFT，复杂度变成了$O(\text{玄学})$。  

### Some Reasons of UnAccept.
1. 没开long long，亲测WA on 51。
2. FFT写炸，无亲测。
3. 没加上启发式合并或启发式合并写扎，亲测TLEon46

### Coding.
```cpp
//声起立华乐独奏 曲末音无心结弦
//只要记住你的名字 不管你在世界的哪个地方 我一定会去见你
//你指尖跳动的电光 是我永恒不变的信仰
//拜托 请把力量借给软弱的我 给我从这里再度起身迈步的力量
//虽然灯塔已经失去了光明…… 但是 只要有你的那首歌在 就一定能将那些人再次导向
//【上：代码缺省源】
//下：火车头，其实应该不需要。
//温馨提醒：火车头必须要C++14才能正常食用
#pragma GCC optimize(2)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
//上：火车头，其实应该不需要。
#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
struct comp
{
	double x,y;
	inline comp operator+(comp b) const {return(comp){x+b.x,y+b.y};}
	inline comp operator-(comp b) const {return(comp){x-b.x,y-b.y};}
	inline comp operator*(double b) const {return(comp){x*b,y*b};}
	inline comp operator/(double b) const {return(comp){x/b,y/b};}
	inline comp operator*(comp b) const {return(comp){x*b.x-y*b.y,x*b.y+y*b.x};}
}a[800005],b[800005];
//按照序列长度维护一个小根堆，所以node需要重定义小于号。
struct node{vector<int>v;bool operator<(node b) const {return v.size()>b.v.size();}};//这个是vector的结构体，笔者比较懒，直接新定义结构体
int n,m,k,c[800005],r[800005];priority_queue<node>q;//q是那个用于启发式合并的有限队列
//下：FFT模板
inline void FFT(int n,comp *a,int fla)
{
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int d=1;d<n;d<<=1)
	{
		comp wn=(comp){cos(pi/d),fla*sin(pi/d)},w;
		for(int i=0,k;i<n;i+=(d<<1))
			for(k=0,w=(comp){1,0};k<d;k++,w=w*wn)
				{comp x=a[i+k],y=w*a[i+k+d];a[i+k]=x+y,a[i+k+d]=x-y;}
	}
	if(fla==-1) for(int i=0;i<n;i++) a[i]=a[i]/n;
}
//上：FFT模板
//下：多项式乘法模板
inline node times(node A,node B)
{
	int n=A.v.size(),m=B.v.size(),T;
	for(T=1,r[0]=0;T<=n+m;) T<<=1;
	for(int i=0;i<T;i++) r[i]=((r[i>>1]>>1)|((i&1)?(T>>1):0));
	for(int i=0;i<T;i++) a[i]=b[i]=(comp){0,0};
	for(int i=0;i<n;i++) a[i].x=A.v[i];
	for(int i=0;i<m;i++) b[i].x=B.v[i];
	FFT(T,a,1),FFT(T,b,1);
	for(int i=0;i<T;i++) a[i]=a[i]*b[i];
	FFT(T,a,-1);node t;t.v.clear(),t.v.resize(n+m-1);//这里必须开longlong，因为虽然每一位都<1009，但是乘起来可能很大
	for(int i=0;i<=n+m-2;i++) t.v[i]=(long long)(a[i].x+0.5)%1009;
	return t;//这里其实可以加点优化，可以把指数大于k-1的全都不要
}
//上：多项式乘法模板
int main()
{
	scanf("%d%d%d",&n,&m,&k);node t;t.v.clear(),t.v.push_back(1);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),c[x]++,c[x]=min(c[x],k+1);//记录可重即中每个元素的数量
	sort(c+1,c+n+1);//按照数量大小排序，便于启发式合并
	for(int i=1;i<=n;i++) {while((int)t.v.size()-1<c[i]) t.v.push_back(1);q.push(t);}//构造出每个生成函数
	while((int)q.size()>1) {node a=q.top();q.pop();node b=q.top();q.pop();q.push(times(a,b));}//启发式合并
	return printf("%d\n",q.top().v[k]),0;//输出答案的k次方的项
}
```

完结散花

---

## 作者：Dzhao (赞：1)

题意：给定一个可重集合，其中有 $n$ 个元素，元素范围为 $[1, m]$，
求它大小为 $k$ 的子集有多少种情况。

题解：每种元素的选法都可以用一个生成函数表示 $G_i(x)=\sum\limits_{j=0}^{cnt_i}x^j$ 分别表示选 $0$ 个到 $cnt_i$ 个，$cnt_i$ 表示有多少种 $i$ 元素。

那么答案就是把这 $m$ 个生成函数卷起来后 $x^k$ 项的系数，由于如果一项一项卷起来时间复杂度会退化为 $\mathcal{O}(n^2\log n)$。考虑优化，我们可以分治，定义 $solve(l, r)$ 为 $[l, r]$ 卷起来得到的多项式，那么可以在做 $[l, r]$ 时先做 $[l, mid]$ 和 $[mid+1, r]$ 然后把两边卷起来，这样的复杂度是 $\mathcal{O}(n\log^2 n)$ 的，因为总共只会递归 $\log n$ 层，每个多项式只会被 DFT $\log n$ 次，而多项式总次数又是 $\mathcal{O}(n)$ 的，所以总时间复杂度为 $\mathcal{O}(n\log^2 n)$。

注意：由于模数不是 NTT 模数，所以要用 FFT，注意需要开 long long，因为卷起来系数可能会很大。

```cpp
//省去了又臭又长的头
using Poly_ftt :: mul;
using Poly_ftt :: mul_ll;
poly operator * (poly a, poly b) {return mul(a, b);}
poly_ll operator * (poly_ll a, poly_ll b) {return mul_ll(a, b);}
const int N = 2e5 + 5;
int n, m, K, cnt[N];
auto solve(int l, int r) {
	if (l == r) {
		poly_ll ret(cnt[l] + 1);
		for (int i = 0; i <= cnt[l]; i++)
			ret[i] = 1;
		return ret;
	}
	int mid = l + r >> 1;
	poly_ll ret = solve(l, mid) * solve(mid + 1, r);
	for (int i = 0; i < (int)ret.size(); i++) ret[i] %= mod;
	return ret;
}

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 1, x; i <= n; i++)
		scanf("%d", &x), cnt[x]++;
	poly_ll res = solve(1, m);
	printf("%lld\n", res[K]);
	return 0;
}
```

---

