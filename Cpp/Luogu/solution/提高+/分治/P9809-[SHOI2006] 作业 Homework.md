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

## 作者：rui_er (赞：7)

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

## 作者：shinzanmono (赞：6)

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

## 作者：liaiyang (赞：0)

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

