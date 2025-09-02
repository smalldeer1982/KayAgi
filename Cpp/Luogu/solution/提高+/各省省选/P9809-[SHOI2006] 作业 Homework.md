# [SHOI2006] 作业 Homework

## 题目描述

给定一个集合为 $S$，初始为空，你需要执行以下两个操作共 $N$ 次。

操作一，在集合 $S$ 中加入一个新元素，其代号为 $X$，保证 $X$ 在当前集合中不存在。

操作二，在当前的集合 $S$ 中询问所有元素 $\bmod\ Y$ 最小的值。

## 说明/提示

对于 $100\%$ 的数据，$N\leq10^5$，$X,Y\leq3\times10^5$。数据保证，第一个操作为操作一。

## 样例 #1

### 输入

```
5
A 3
A 5
B 6
A 9
B 4```

### 输出

```
3
1```

# 题解

## 作者：MeteorFlower (赞：21)

不是，没人写纯正根号吗……退役壬来口胡一下。

看到 $\text{mod}$ 啪的一下就是一个根号分治，很快啊。

考虑模数 $\leq \sqrt V$ 的部分。此时因为模数只有 $O(\sqrt V)$ 种，考虑直接记录每种模数的答案。单次复杂度为 $O(\sqrt V)$ 修改，$O(1)$ 查询。

考虑模数 $> \sqrt V$ 的部分。由于此时商数的级别为 $O(\sqrt V)$，考虑直接存储集合 $S$，询问时枚举商数 $i$，找到集合中最小的 $\geq Y \times i$ 的值然后减一下即可。因此有 $O(n)$ 次修改，$O(n \sqrt V)$ 次查询。使用 $O(\sqrt V)$ 修改，$O(1)$ 查询的值域分块平衡复杂度。具体地，用 $next1_i$ 表示最小的 $\geq i$ 且同块的数，用 $next2_i$ 表示最小的大于第 $i$ 块最后一个数的数。插入新数时修改所属块的前缀 $next1$ 以及前面所有块的 $next2$。查询时先查 $next1$，查不到再查所属块的 $next2$ 即可。

综上所述，总复杂度 $O(n \sqrt V)$。

AFO 了，没时间写代码，应该很简单就不写了。

~~（吐槽：这种小常数根号题数据范围居然就这么点……生怕乱搞过不去吗……我谔谔。）~~

---

## 作者：rui_er (赞：8)

看到不好维护的取模相关信息，想到根号分治。设值域为 $V$，根号分治的阈值为 $B$。

对于模数不超过 $B$ 的情况，我们需要利用情况数为 $O(B)$ 这一性质。在每次插入元素时动态维护所有情况的答案，查询时查表回答即可。

对于模数超过 $B$ 的情况，我们需要利用商数个数为 $O(\frac{V}{B})$ 这一性质。使用 set 维护集合中所有元素，每次查询时枚举所有可能的商数，二分查找这种情况下最小可能的余数。

令 $B=O(\sqrt{V})$ 即可得到 $O(N\sqrt{V}\log N)$ 的并不优秀的复杂度。

事实上应该可以通过使用并查集代替 set 做到 $O(N\sqrt{V}\alpha(N))$，或者使用值域分块代替 set 做到 $O(N\sqrt{V})$。但反正能过，我懒得写了，如果有一天加强数据被卡常了那就不要参考下面的代码好了。

```cpp
// Problem: P9809 [SHOI2006] 作业 Homework
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9809
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 3e5 + 5, B = 550;

int n, ans[B];
set<int> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    rep(i, 1, B - 1) ans[i] = i;
    for(cin >> n; n; --n) {
        string op; int x;
        cin >> op >> x;
        if(op == "A") {
            rep(i, 1, B - 1) chkmin(ans[i], x % i);
            st.insert(x);
        }
        else {
            if(x < B) cout << ans[x] << endl;
            else {
                int now = x;
                for(int i = 0; i < N; i += x) {
                    auto it = st.lower_bound(i);
                    if(it == st.end()) break;
                    chkmin(now, *it - i);
                }
                cout << now << endl;
            }
        }
    }
    return 0;
}
```

---

## 作者：shinzanmono (赞：7)

考虑对 $Y$ 进行根号分治。

加入一个数 $X$ 时，对 $\leq\sqrt V$ 的 $Y$ 进行维护，并向序列中加入 $X$。

查询时，若 $Y\leq\sqrt V$，则直接输出；否则暴力枚举 $kY$，然后二分查找即可。

时间复杂度 $O(n\sqrt V\log n)$，可过。当然也有不二分的方法（反正能过就不写了）。

---

## 作者：meyi (赞：3)

这题让我想起来[我的另一篇题解](https://www.luogu.com.cn/blog/zankizero/solution-p7811)。

所以考虑如何用 bitset 爆草这题。

首先你发现这题是全局查询所以不用考虑删除，设一个阈值 $B$，对于 $y\leq B$ 的我们就直接维护答案了，也即加入元素的复杂度为 $O(B)$，查询答案的复杂度为 $O(1)$。

然后你发现 $y>B$ 不好搞，但是 bitset 能草过 P7811 这种大卡常题告诉你直接 bitset 找最小的 $b$ 使得 $ay+b$ 存在于集合中是非常优秀的。虽然它貌似是 $O(\frac{V}{w})$ 的，但是小编也不知道为什么跑的飞快。

瞎取了个 $B=3000$ 就过了，实际上我交的五发 TLE 是 bitset 在 find_next 的时候写错了个东西导致死循环才寄的，所以感觉直接取 $B=\sqrt n$ 也不是不能过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int B=3000;
int a[B];
typedef unsigned long long ull;
template<int siz>
struct bset{
	ull b[((siz+63)>>6)+1];int len;
	inline bset(){len=(siz+63)>>6;}
	inline void set0(int p){b[p>>6]&=~(1llu<<p);}
	inline void set1(int p){b[p>>6]|=(1llu<<p);}
	inline int find_first(){for(int i=0;i<len;++i)if(b[i])return (i<<6)|__builtin_ctzll(b[i]);return siz;}
	inline int find_next(int p){
		if(++p>=siz)return siz;
		int hi=p>>6,lo=p&63;
		if(b[hi]>>lo)return p+__builtin_ctzll(b[hi]>>lo);
		for(int i=hi+1;i<len;++i)if(b[i])return (i<<6)|__builtin_ctzll(b[i]);
		return siz;
	}
};
bset<300001>b;
int main(){
	int n;
	scanf("%d",&n);
	memset(a,0x3f,B<<2);
	while(n--){
		char ch;
		while(!isupper(ch=getchar()));
		int x;
		scanf("%d",&x);
		if(ch=='A'){
			for(int i=0;i<B;++i)a[i]=min(a[i],x%(i+1));
			b.set1(x);
		}
		else{
			if(x<=B)printf("%d\n",a[x-1]);
			else{
				int mn=INT_MAX;
				for(int i=b.find_first();i<300001;i=b.find_next((i/x+1)*x-1))mn=min(mn,i%x);
				printf("%d\n",mn);
			}
		}
	}
	return 0;
}
```

---

## 作者：MPLN (赞：1)

~~原来这就是传说中的根号分治，没见过的时候还以为什么神仙递归呢~~

本片题解同时也是我的笔记。



---

下称 $X,Y$ 的最大可能取值为 $V$（$V=3\times 10^5$）。

首先要做 $O(nV)$ 的暴力有两种可能：要么操作一暴力，加入元素的时候枚举除数更新最小余数；要么操作二暴力，去已有元素里面一个一个试。

如果答案比较小，设一个阈值为 $K$，当答案（余数）$\le K$ 的时候我们就采用操作一暴力的方法，复杂度 $O(nK)$。当答案 $>K$ 就有一个有趣的性质：

既然这个余数 $>K$，而小学我们学过除数大于余数，所以设最终满足余数最小的数为 $x=aY+b$（$b$ 为余数即答案），则有 $Y>b>K$。因为涉及到的数都是正整数，所以由等式有 $a\le \frac{x}{Y}$。综上，$a\le \frac{x}{K}\le \frac{V}{K}$。

我们不妨枚举 $a$，在集合 $S$ 里二分找到 $\ge aY$ 的最小数 $d$，用 $d-aY$ 尝试更新答案即可。复杂度 $O(\frac{Vn\operatorname{log}n}{K})$。

所以我们的算法复杂度是 $O(nK+\frac{Vn\operatorname{log}n}{K})$，当 $K=\sqrt V$ 时最优，为 $O(n\operatorname{log}n\sqrt{V})$，且实际常数很小。



---


实现集合查找可以用现成的 STL 模版 ```set<int>```，```s.insert()``` 插入，```s.lower_bound()``` 查找。查找的时候记得判是否出界。写起来十分方便且跑得很快（最慢的点不到 200ms）。

好像可以去掉 $\operatorname{log}$，但是没有必要。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int K = 548; // ≈ sqrt(300000)
int T, a[550];
set<int> s;
signed main() {
    for (int i = 1; i <= K; i++) a[i] = i - 1;
    scanf("%d", &T);
    while (T--) {
        char op; while (!isupper(op = getchar()));
        int x; scanf("%d", &x);
        if (op == 'A') {
            for (int i = 1; i <= K; i++)
                a[i] = min(a[i], x % i);
            s.insert(x);
        } else {
            if (x <= K) {
                printf("%d\n", a[x]);
            } else {
                int ans = x - 1;
                for (int t = 0; t <= 300000 / x; t++) {
                    auto it = s.lower_bound(t * x);
                    if (it != s.end()) ans = min(ans, *it - t * x);
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
```

---

## 作者：kind_Ygg (赞：1)

## 题解：P9809 [SHOI2006] 作业 Homework
集训**并查集**专题考试考了这道题，~~鬼知道为什么将这道题放进来。~~  
### 题目大意
最开始是一个空集 $s$，有两个操作：  
1. 插入一个数 $v$。（$v\le3\times 10^5$）
2. 求 $\displaystyle \min_{u\in s}(u\bmod v)$。
### 思路
第一种：  
**时间复杂度**：（$O(n^2)$）。  
直接打暴力，插入是 $O(1)$ 的，求解是 $O(n)$。

第二种：
**时间复杂度**：$O(n\sqrt n \log n)$。  
还有第二种暴力：每次插入时都将每个要求解的 $v$（$v\le3\times 10^5$）记录一遍，这样插入是 $O(v)$ 的，求解是 $O(1)$ 的。  
考虑将这两种暴力结合，用根号分治。  

假设一个阀值 $B$。  
在插入中，首先将他插入到 `set` 容器中（方便二分），再用第二种暴力，将每个小于 $B$ 的 $v$ 求解一遍，复杂度为 $O(nB+n\log n)$。

在求解中，分两种情况。  
如果 $v\le B$，可以直接输出（前面统计过了）。  
如果 $v>B$，那么我们可以用到他在 $3\times 10^5$ 范围内只有 $\frac{3\times 10^5}{v}$ 个倍数，可以暴力枚举他的每个倍数，再用 `lower_bound` 求解，复杂度为 $O(nB\log n)$。

易得 $B=\sqrt n$，时间复杂度最小。
### 代码
别想抄题解，代码是不可能给的，思路都告诉你了。

---

## 作者：liaiyang (赞：1)

题意：你需要支持加入一个数，查找区间模当前数的最小值。

很明显的根号分治。

我们设对于 B 根号分治。

对于小于等于 B 的询问，我们直接预处理出每个数的值，用数组存起来，时间复杂度 $O(nB)$。

对于大于B的询问，我们用 set 维护序列里的数，枚举当前数的所有倍数，二分找第一个大于等于它的，时间复杂度 $O(n\frac V B \log n)$。

此时插入的复杂度 $O(nB\log n)$，查询的复杂度 $O(n\frac V B\log n)$ 或者 $O(1)$。

我们取 $B=O(\sqrt V)$，可得时间复杂度为 $O(n\sqrt V\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define y1 Y1
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define min(a,b) (a<b?a:b) 
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
#define abs(x) ((x)<0?-(x):(x))
mt19937 rnd(time(0));
inline int read(int u=0, char c=getchar(), bool f=false){
	for (;!isdigit(c);c=getchar()) f|=c=='-';
	for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
	return f?-u:u;
}
inline void wt(int x){
	if(x<0) x=-x,putchar('-');
	if(x>9) wt(x/10);
	putchar(x%10+48);
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1; 
const int mod=998244353,g=3,gi=332748118;
const int N=3e5+10,B=600;
int n,ans[B+10];
set<int>s;
main(){
	n=rd;
	memset(ans,0x3f,sizeof ans);
	while(n--){
		char c;
		int x;
		cin>>c>>x;
		if(c=='A'){
			s.insert(x);
			for(int i=1;i<=B;i++) ans[i]=min(ans[i],x%i);
		}
		else{
			if(x<=B){
				wt(ans[x],'\n');
				continue;
			}
			int sum=inf;
			for(int i=0;;i+=x){
				auto it=s.lower_bound(i);
				if(it==s.end()) break;
				sum=min(sum,(*it)-i);
			}
			wt(sum,'\n');
		}
	}
	return 0;
}
```

---

## 作者：BaiBaiShaFeng (赞：0)

## 题意概括

> 有两个操作，一个往集合里加数，一个问集合中模 $y$ 最小的值。

## 分析

乍一看感觉不难，但好像想不出来什么复杂度好的做法。

先考虑暴力做法。

我们可以开一个数组维护所有模数的最小值，每次全部更新，这么做肯定不行，时间复杂度会爆炸。

考虑一下操作的本质，可以看作把集合切成一段一段的，如果从这一点入手，我们可以从 $0$ 开始枚举所有长度为 $y$ 的段，二分找到距离段左端点最近的点，取这个距离，每个段的这个距离取最小值。

但是这中办法在 $y$ 小的时候不太行，仅仅在 $y$ 较大时表现比较优秀。

想到我们刚才的垃圾暴力，我们可以使用根号分治把前边的暴力拼接到我们后边的做法中，解决 $y$ 较小时的情况。

我们设定阈值 $B$ 为 $\sqrt{n}$，开数组维护模数在 $[1,B]$ 的最小值，同时使用一个容器来记录这个值，我这里就使用 set 了。

在询问中，如果 $y\le B$，我们就直接输出数组中的数字，否则按照我们上述处理。

不难分析时间复杂度，最坏是 $O(n\sqrt{n}\log n)$。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
const int B=521;
set <int> st;
int n, minn[B+10], maxn;
int main(){
    memset(minn,0x3f,sizeof(minn));
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); cin>>n;
    for(int tim=1,val; tim<=n; ++tim){
        char op; cin>>op>>val;
        if(op=='A'){
            st.insert(val); maxn=max(maxn,val);
            for(int i=1; i<=B; ++i)
                minn[i]=min(minn[i],val%i);
        }else{
            int ans=0x3f3f3f3f;
            if(val>B){
                for(int i=0; i*val<=maxn; ++i){
                    int v=*st.lower_bound(val*i);
                    if(v-val*i>=0) ans=min(ans,v%val);
                }                
            }else{
                ans=minn[val];
            }
            cout<<ans<<'\n';
        }
    }

    return 0;
}
```

---

