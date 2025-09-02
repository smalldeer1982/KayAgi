# Robin Hood Archery

## 题目描述

在这种时候，射箭总是一天中的主要运动，因为诺丁汉郡的自耕农是整个快乐的英格兰最好的长弓手，但今年郡长犹豫了……



诺丁汉郡长组织了一场射箭比赛。这是最后一轮，罗宾汉对阵警长!

编号为$ 1 $ ～ $ n $的行中有$ n $个目标。当玩家射击目标$ i $时，他们的得分增加$ a_i $，目标$ i $被摧毁。游戏由回合组成，玩家轮流轮到谁。罗宾汉总是先开始游戏，然后是警长等等。游戏继续进行，直到所有目标被摧毁。两名球员都以得分$ 0 $开始。

在游戏结束时，得分最多的玩家获胜，而另一名玩家输了。如果双方得分相同，则为平局，没有人赢也没有人输。在每个回合中，玩家可以射击任何之前没有射击过的目标。两种游戏都是为了获得尽可能多的分数。

诺丁汉郡长怀疑他可能会输掉比赛!不能这样，你必须帮助警长。Sheriff将提出$ q $查询，每个查询指定$ l $和$ r $。这意味着游戏将只与目标$ l, l+1, \dots, r $一起玩，因为其他目标将在游戏开始前被Sheriff删除。

对于每个查询$ l $, $ r $，在只考虑目标$ l, l+1, \dots, r $的情况下，确定警长是否不会输掉比赛。

## 样例 #1

### 输入

```
2
3 3
1 2 2
1 2
1 3
2 3
5 3
2 1 2 1 1
1 2
1 3
4 5```

### 输出

```
NO
NO
YES
NO
NO
YES```

# 题解

## 作者：沉石鱼惊旋 (赞：13)

# 题目翻译

有一个长度为 $n$ 的序列 $a$。

A 和 B 进行决斗。

决斗指每个人在选择一个数之后删除，全部选完之后比较谁选择的数之和更大。，

一共进行 $q$ 次，每次决斗范围是 $[l,r]$。也就是两人只可以用 $a_l,a_{l+1},\dots,a_{r-1},a_r$ 这 $r-l+1$ 个数。

B 先手，判断每次决斗 A 是否不会输，也就是 A 选择的数不小于 B 选择的数。

$1\leq n,q,\sum n,\sum q\leq 2\times 10^5$，$1\leq a_i\leq 10^6$。

# 题目思路

显然 A 和 B 都会选择目前最大的数。

如果此时有奇数个数可选，B 每次选最大，而且多拿一次，一定会比 A 拿到的要大。

如果有偶数个数，大部分情况 B 也会比 A 拿得多。除非 $a_l,a_{l+1},\dots,a_{r-1},a_r$ 可以两两匹配，也就是分成两个完全相同的序列。那么 B 拿什么 A 就跟着拿什么，就会平局。

因此我们判断 $a_l,a_{l+1},\dots,a_{r-1},a_r$ 是否可以两两抵消。考虑到异或有 $0\oplus x=x$ 且 $x\oplus x=0$，判断 $a_l,a_{l+1},\dots,a_{r-1},a_r$ 异或和是否为 $0$ 即可。

但这随便 hack 都能死。不妨随机赋权，把 $[1,10^6]$ 映射到一个极大范围，一般我们选择 $[0,2^{64})$ 也就是 C++ 中 unsigned long long 的范围。之后再使用异或哈希。

# 正义制裁

这个做法真的是对的吗？

不难发现，我们如果知道了随机种子，我们用 $\log$ 个数就可以构造一个两两不同但是异或为 $0$ 的序列。

如何找到这样的序列？我们可以使用线性基。如果插入发现这个数已经被基内的数凑出来了那么就说明这些异或起来为 $0$。

具体的，我们知道了对方的随机种子和随机生成方法，按着他的方法生成随机数，扔到基内，直到基没有成功插入这个值。期望 $\log$ 个数就可以干掉一个随机方法。

例子是 <https://codeforces.com/contest/2014/submission/282293924> 和 <https://codeforces.com/contest/2014/submission/282345418>。前者使用了没有给种子，但是也相当于生成方式固定。后者使用了固定种子 $10^{18}$。

但是为什么有人使用了 time(0) 也被我卡了？例如 74TrAkToR 的 <https://codeforces.com/contest/2014/submission/282303785>。~~薄纱 74，最正义的一集。~~

考虑到 time(0) 本质是秒为单位的时间戳，我们虽然不知道 hack 的时候的具体时间，但是可以，跑出此刻开始 200s 的时间戳作为种子的 hack，提交上去。

但是 CF 时间和本地时间似乎有区别，可以在 custom test 里测一下。我测了一下跑出 $[t-200,t]$ 的时间戳的 hack 即可。其中 $t$ 是本地目前时间。

那么为了避免被卡，推荐使用 `random_device` 或者 `chrono::system_clock::now().time_since_epoch().count()` 作为种子。前者不太懂原理，cppreference 上的描述是：

> std::random_device may be implemented in terms of an implementation-defined pseudo-random number engine if a non-deterministic source (e.g. a hardware device) is not available to the implementation. In this case each std::random_device object may generate the same number sequence.

~~后者是毫秒级别的。理论上后者也可以被叉掉，但是需要刻意控制时间到很精密的时刻，~~正常人指定干不出这种事~~。即使在本题控制 10s 的 hack 也需要 $10^4$ 组，带上前面的 $\log$ 还是有点困难的。并且除了本题，有点题的 hack 规模可能不止 $\log$。实在是太难卡。~~

感谢 @[Z_301](/user/175087) 提醒，后者不加限制直接调用是纳秒级别的。那么用后面的是根本不会被卡的。

# 完整代码

[CF submission 282295625](https://codeforces.com/contest/2014/submission/282295625)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
typedef unsigned long long ull;
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int n, q;
ull a[200020];
ull to[1000020];
void solve()
{
    read(n, q);
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
        a[i] = a[i - 1] ^ to[a[i]];
    }
    while (q--)
    {
        int l, r;
        read(l, r);
        if (r - l + 1 & 1)
        {
            puts("NO");
            continue;
        }
        puts(a[r] == a[l - 1] ? "YES" : "NO");
    }
}
int main()
{
    for (int i = 1; i <= 1000000; i++)
        to[i] = rnd();
    int t;
    read(t);
    while (t--)
        solve();
    return 0;
}
```

Hack Generator 直接找 [P3812 【模板】线性基](https://www.luogu.com.cn/problem/P3812) 的任意代码。

---

## 作者：Super_Cube (赞：4)

# Solution

每次的先手都一定会取当前剩下最大的值，所以 Sheriff 不可能赢，顶多平局。当且仅当一个区间长度为偶数且任意数都出现偶数次的情况下 Sheriff 才能不输。随机异或哈希即可。

# Code

```cpp
#include<bits/stdc++.h>
std::mt19937 rnd(time(0));
unsigned long long s[200005],v[1000005];
int T,n,m;
int main(){
	for(int i=1000000;i;--i)v[i]=rnd();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1,x;i<=n;++i)
			scanf("%d",&x),s[i]=s[i-1]^v[x];
		for(int l,r;m--;)
			scanf("%d%d",&l,&r),
			puts(s[r]==s[l-1]?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：Hide_In_The_Shadow (赞：3)

普通莫队板题。

显然两人每次都只会打最大的，容易观察到 S 不输的条件是每个数都出现偶数次，于是发现每次扩展或收缩都可以做到 $O(1)$ 修改。于是考虑使用莫队。莫队的知识这里就不过多讲述，可以参考 [OI Wiki](https://oi-wiki.org/misc/mo-algo/)。

这里提一下怎么扩展，观察到值域空间不大（大的话也可以离散化），对于每个数字记录它出现的次数，每次扩展时判断它是不是偶数即可。

时间复杂度 $O(n\sqrt n)$。

```c++
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fio std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
template<typename T>inline void read(T &x){
	x=0;
	char c=getchar();
	T ret=0;
	while(!isdigit(c))ret|=!(c^'-'),c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(ret)x=(~x)+1;
	return;
}
template<typename T,typename ...Args>
inline void read(T &x,Args &...xs){
    read(x);
    read(xs...);
}
template<typename T>inline void print(T x){
	if(x<0)putchar('-'),x=(~x)+1;
	if(x>9)print(x/10);
	putchar((x-x/10*10)^48);
	return;
}
template<typename T>inline void wr1(T x){
	print(x);
	putchar(' ');
	return;
}
template<typename T>inline void wr2(T x){
	print(x);
	putchar('\n');
	return;
}
int t,n,q;
int a[214514],num[1145141],ans[214514],id[214514],siz,temp;
struct quarry{
    int l,r,id;
}Q[214514];
bool cmp(quarry a,quarry b){
	return id[a.l]!=id[b.l]?a.l<b.l:(a.r==b.r?0:((id[a.l]&1)^(a.r<b.r)));
}
void add(int x){
	temp-=num[a[x]]&1;
	num[a[x]]++;
	temp+=num[a[x]]&1;
}
void red(int x){
	temp-=num[a[x]]&1;
	num[a[x]]--;
	temp+=num[a[x]]&1;
}
int main(){
	read(t);
    while(t--){
        read(n);
		siz=sqrt(n);
        read(q);
        for(int i=1;i<=n;++i){
            read(a[i]);
			id[i]=(i/siz)+1;
			num[a[i]]=0;
        }
        for(int i=1;i<=q;++i){
            read(Q[i].l,Q[i].r);
			Q[i].id=i;
        }
		sort(Q+1,Q+q+1,cmp);
		int l=1,r=0;
		temp=0;
		for(int i=1;i<=q;++i){
			while(r<Q[i].r)add(++r);
			while(l>Q[i].l)add(--l);
			while(r>Q[i].r)red(r--);
			while(l<Q[i].l)red(l++);
			ans[Q[i].id]=temp;
		}
		for(int i=1;i<=q;++i){
			if(ans[i]){
				puts("NO");
			}
			else{
				puts("YES");
			}
		}
    }
	return 0;
}
```

这里给出第二种取巧的思路即 XOR HASH，注意到每个数出现偶数次即代表着其异或和为 $0$，于是我们可以考虑将其异或起来，然而对于 $1e6$ 范围内的数，其二进制位有限，容易构造出 HACK 数据，使不相同的数异或和也为 $0$。于是我们考虑使用 HASH，将每种数值转化为 $long long$ 范围内的随机数，这样冲突的概率就会很小。预处理之后只需要利用前缀异或和即可 $O(1)$ 处理询问，于是时间复杂度为 $O(n)$。

```c++
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fio std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
template<typename T>inline void read(T &x){
	x=0;
	char c=getchar();
	T ret=0;
	while(!isdigit(c))ret|=!(c^'-'),c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(ret)x=(~x)+1;
	return;
}
template<typename T,typename ...Args>
inline void read(T &x,Args &...xs){
    read(x);
    read(xs...);
}
template<typename T>inline void print(T x){
	if(x<0)putchar('-'),x=(~x)+1;
	if(x>9)print(x/10);
	putchar((x-x/10*10)^48);
	return;
}
template<typename T>inline void wr1(T x){
	print(x);
	putchar(' ');
	return;
}
template<typename T>inline void wr2(T x){
	print(x);
	putchar('\n');
	return;
}
mt19937_64 rnd(time(0));//mt19937_64是一个64位随机数生成器
int n,t,q,a;
ll b[1145141],x[214514];
int main(){
    read(t);
    for(int i=1;i<=1e6+10;++i){
        b[i]=rnd();
    }
    while(t--){
        read(n,q);
        for(int i=1;i<=n;++i){
            read(a);
            x[i]=x[i-1]^b[a];
        }
        for(int i=1;i<=q;++i){
            int l,r;
            read(l,r);
            if(x[r]^x[l-1]){
                puts("NO");
            }
            else{
                puts("YES");
            }
        }
    }
    return 0;
}
```

---

## 作者：QinYulang (赞：1)

# 题目翻译
问一个区间内每个数是否出现偶数次。

# 思路
一道异或哈希题。

首先思考罗宾汉每次一定会取序列中最大的那一个，那么警长只可能去取第二小的，这样警长的得分永远会比罗宾汉的要小，所以警长只可能与罗宾汉的得分相同。由此可以得出当一个区间的数字出现的次数为偶数次时警长才可能与罗宾汉的得分相同。

正如题目翻译所说：问一个区间内每个数是否出现偶数次。
  至此异或哈希就已经很显而易见了。随机数用梅森旋转 `mt19937_64` 即可（据说每生成 $2^{19937}$ 才会出现重复）。

# 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cmath>
#include <random>
#include <ctime>

#define LOCAL
#define int unsigned long long
namespace ly{
    namespace IO{
        #ifndef LOCAL
            constexpr auto maxn = 1 << 20;
            char in[maxn], out[maxn], *p1 = in, *p2 = in, *p3 = out;
            #define getchar() (p1 == p2 && (p2 = (p1 = in) + fread(in, 1, maxn, stdin), p1 == p2) ? EOF : *p1++)
            #define flush() (fwrite(out, 1, p3 - out, stdout))
            #define putchar(x) (p3 == out + maxn && (flush(), p3 = out), *p3++ = (x))
            class Flush{public: ~Flush(){flush();}}_;
        #endif
        namespace usr{
            template <typename type>
            inline type read(type &x){x = 0; bool flag(0); char ch = getchar(); while(!isdigit(ch)) flag ^= ch == '-', ch = getchar(); while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return flag ? x = -x : x;}
            template <typename type>
            inline void write(type x){x < 0 ? x = -x, putchar('-') : 0; static short Stack[50], top(0); do Stack[++top] = x % 10, x /= 10; while(x); while(top) putchar(Stack[top--] | 48);}
            inline char read(char &x){do x = getchar(); while(isspace(x)); return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch; read(ch); do *(x++) = ch; while(!isspace(ch = getchar()) && ~ch);}
            template <typename type> inline void write(type *x){while(*x) putchar(*(x++));}
            inline void read(std::string &x){static char ch; read(ch), x.clear(); do x += ch; while(!isspace(ch = getchar()) && ~ch);}
            inline void write(const std::string &x){for(int i = 0, len = x.length(); i < len; ++i)putchar(x[i]);}
            template <typename type, typename...T> inline void read(type &x, T&...y){read(x), read(y...);}
            template <typename type, typename...T>
            inline void write(const type &x, const T&...y){write(x), putchar(' '), write(y...), sizeof...(y) ^ 1 ? 0 : putchar('\n');}
            template <typename type>
            inline void put(const type &x, bool flag = 0){write(x), flag ? putchar('\n') : putchar(' ');}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    } using namespace IO::usr;
} using namespace ly::IO::usr;

std::mt19937_64 rnd(std::time(0)); //梅森旋转。
int mt[1000005], n, m, a[1000005];
void solve(){
    read(n, m);
    for(int i = 1; i <= n; ++i) read(a[i]), a[i] = a[i - 1] ^ mt[a[i]]; //映射成随机数并做前缀异或和。
    while(m--){
        int l, r;
        read(l, r);
        put(a[r] == a[l - 1] ? "Yes" : "No", 1); //恶心的异或优先级，推荐食用这种写法。
    }
    return ;
}
signed main(){
    int t;
    read(t);
    for(int i = 1; i <= 1000005; ++i) mt[i] = rnd();
    while(t--)
        solve();
    return 0;
}
```

---

## 作者：Union_Find (赞：1)

我下文称 A 为先手，B 为后手。

显然的，A 和 B 会轮流选择当前序列的最大值。而每一轮，A 先选，B 再选，那么 A 选的数就一定不会比 B 选的数小。我们设 $a_i$ 表示 A 第 $i$ 轮选的数，$b_i$ 表示 B 第 $i$ 轮选的数，我们就有 $\forall i,a_i \geq b_i$。所以当长度为偶数时，就有 $\sum a_i \geq \sum b_i$。而如果是奇数，A 会再多选一个数，那么就有 $\sum a_i > \sum b_i$。

我们希望 B 不输，而我们证明了 B 不会赢，所以 B 输出 YES 的情况只能是平局。考虑平局的条件。

如果长度是奇数，我们证明了 B 必输，所以我们考虑长度为偶数的情况。

因为 $\sum a_i \geq \sum b_i,\forall a_i \geq b_i$，我们希望取到等号，就只能是 $\forall i,a_i = b_i$。换而言之，就是 A 取什么数，B 就取什么数。这样子的前提是 $[l,r]$ 的区间内所有数字都有偶数个。这样子，问题就转化成询问一段区间内是否每个数字都有偶数个。

这样子就有两种做法。

## Hash

我们知道，一个数异或自己就会变成 $0$。所以我们考虑让区间内所有数字异或起来，判断是否等于 $0$。但是这样会导致如下例子无法通过，因为多个数异或也可能变成 $0$。

```
1
6 1
1 2 3 3 5 6
1 6
```

所以我们给每个数赋一个随机值，然后进行异或。这种方法叫做 XOR HASH。

具体实现可以用随机数和前缀异或值处理。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
#define M 1000005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}il ll rnd(){return (rand() | (rand() << 16));}
ll n, m, a[N], l, r, s[N], t[M];
int main(){
	srand(time(0));
	for (int T = rd(); T--;){
		n = rd(), m = rd();
		for (int i = 1; i <= n; i++){
			a[i] = rd();
			if (!t[a[i]]) t[a[i]] = rnd();
			s[i] = s[i - 1] ^ t[a[i]];
		}while (m--) l = rd(), r = rd(), puts((s[r] ^ s[l - 1]) ? "NO" : "YES");
		for (int i = 1; i <= n; i++) t[a[i]] = 0;
	}
	return 0;
}
```

## 莫队

既然 $n \leq 2 \times 10^5$，为什么不适用优秀的 $O(n\sqrt n)$ 算法呢。考虑使用莫队，每次移动是判断当前数字个数是否为偶数即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
#define M 1000005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, m, sqn, a[N], l, r, val, ans[N], t[M];
struct Q{
	ll l, r, id;
}q[N];
il bool cmp(Q a, Q b){return (a.l / sqn) != (b.l / sqn) ? a.l < b.l : ((a.l / sqn) & 1) ? a.r > b.r : a.r < b.r;}
il void move(ll x){t[a[x]] ^= 1, val += (t[a[x]] ? 1 : -1);}
int main(){
	for (int T = rd(); T--;){
		n = rd(), m = rd(), sqn = sqrt(n);
		for (int i = 1; i <= n; i++) a[i] = rd();
		for (int i = 1; i <= m; i++) q[i] = Q{rd(), rd(), i};
		sort (q + 1, q + m + 1, cmp);
		l = r = 1, val = 1, t[a[1]] = 1;
		for (int i = 1; i <= m; i++){
			while (l > q[i].l) move(--l);
			while (r < q[i].r) move(++r);
			while (l < q[i].l) move(l++);
			while (r > q[i].r) move(r--);
			ans[q[i].id] = (bool)val;
		}for (int i = 1; i <= m; i++) puts(ans[i] ? "NO" : "YES");
		for (int i = 1; i <= n; i++) t[a[i]] = 0;
	}
	return 0;
}
```

---

## 作者：liujinxv123 (赞：1)

## [CF题目传送门](https://codeforces.com/contest/2014/problem/H)
## 题目大意
Robin 和 Sheriff 比赛，Robin 先手，每次比赛他们选择 $l - r$ 的区间内的目标进行射击。射击编号为 $i$ 的目标会加 $a_i$ 分，然后这个目标被摧毁。两人初始得分均为 0。若 Sheriff 能获胜或平局输出 `YES`，否则输出 `NO`。
## 题目思路
由于 Robin 先手，为了获胜，当轮到 Robin 时他一定会选择当前剩余目标中最大分值的目标。所以无论如何 Sheriff 一定不会获胜，最多只能平局。

如果能平局，说明 $l - r$ 这个区间内所有出现过的数的出现次数均为偶数（这样两人才能平均分，达到平局的效果）。此时用莫队维护区间数值出现次数。

剩下的便是板子了。

不会的去[这里](https://blog.csdn.net/GROZAX/article/details/130069889)。
## Code
附上完整代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
struct node{
	int l,r,id;
}q[N];
int a[N];
int ans[N],cnt[N];
int n,m,sq;
bool cmp(node x,node y){
	if(x.l / sq != y.l / sq) return x.l / sq < y.l / sq;
	else return x.r / sq < y.r / sq; 
}
int cur = 1;
void add(int p){
	cnt[a[p]] ++;
	if(cnt[a[p]] & 1) cur ++;
	else cur --;
}
void del(int p){
	cnt[a[p]] --;
	if(cnt[a[p]] & 1) cur ++;
	else cur --;
}
void solve(){
	cur = 1;
	cin >> n >> m;
	sq = min((int)sqrt(n) + 1,n);
	for(int i = 0;i < n;i ++){
		cin >> a[i];
		cnt[a[i]] = 0;
	} 
	for(int i = 0;i < m;i ++){
		cin >> q[i].l >> q[i].r;
		q[i].l --;
		q[i].r --;
		q[i].id = i;
		ans[i] = 0;
	}
	sort(q,q + m,cmp);
	cnt[a[0]] ++;
	int L = 0,R = 0;
	for(int i = 0;i < m;i ++){
		while(R < q[i].r) add(++ R);
		while(L > q[i].l) add(-- L);
		while(L < q[i].l) del(L ++);
		while(R > q[i].r) del(R --);	
		ans[q[i].id] = cur;
	}
	for(int i = 0;i < m;i ++){
		if(ans[i]) cout << "NO\n";
		else cout << "YES\n";
	}
}
int main(){
	int T;
	cin >> T;
	while(T --) solve();
	return 0;
}
```

---

## 作者：conti123 (赞：1)

### 前言

大无语，只有我认为难度排序是 $H<F<E<G$ 吗？

### 分析

一个莫队的裸题放在最后一题？

我们可以发现，**先手一定不输**，那么后手不输时只能是和先手打平。

那什么时候会平呢？

只可能是每一个在区间中的数的出现次数都是偶数，这样后手跟着先手才可能打平。

放一道[模板题](https://www.luogu.com.cn/problem/P3901)，而这题我们只需要在维护每个数出现次数的同时顺便维护它是奇数还是偶数即可。

### Code
```cpp
inline bool cmp(fy x,fy y){
	return pos[x.l]==pos[y.l]?(pos[x.l]&1?x.r<y.r:x.r>y.r):pos[x.l]<pos[y.l];
}
//注意特判0
inline void add(int x){
	x=a[x];
	cnt[x]++;
	if(cnt[x]==1)
		sum++;
	else{
		if(cnt[x]&1)
			res--;
		else
			res++;
	}
}
inline void del(int x){
	x=a[x];
	cnt[x]--;
	if(cnt[x]==0)
		sum--;
	else{
		if(cnt[x]&1)
			res--;
		else
			res++;
	}
}
void solve(){
	int n,m;
	std::cin>>n>>m;
	int ks=sqrt(n);
	for(int i=1;i<=n;i++)
		std::cin>>a[i],pos[i]=(i-1)/ks+1;
	for(int i=1;i<=m;i++)
		std::cin>>q[i].l>>q[i].r,q[i].id=i;//模板莫队
	std::sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	sum=0,res=0;
	for(int i=1;i<=m;i++){
		int ql=q[i].l,qr=q[i].r,j=q[i].id;
		while(l<ql)
			del(l++);
		while(r>qr)
			del(r--);	
		while(l>ql)
			add(--l);
		while(r<qr)
			add(++r);
		ans[j]=(sum==res);//如果区间内不同数字个数=区间内出现偶数次数的数的个数
	}
	for(int i=1;i<=m;i++)
		std::cout<<(ans[i]==1?"YES\n":"NO\n");
	for(int i=1;i<=n;i++)
		cnt[a[i]]=0;
}
```


发现其实可以线性做法，用异或哈希即可，不再赘述。~~因为暴力随便跑~~。总时间复杂度：$O(n\sqrt n)$

---

## 作者：gmb7291234 (赞：0)

## 思路
我们把区间长度分为奇和偶两种。

第一种，区间长度为奇数。显然罗宾汉每次拿的都不小于警长，且多拿一次，警长一定会输，输出 NO。

第二种，区间长度为偶数。罗宾汉每次拿的还是都不小于警长，如果要输出 YES，就只能让他们每次获得的分数两两匹配等，也就是区间异或和为 $0$。

但是，有可能不相等的情况下也可能相等，比如 $1,2,4,7$，虽然异或和为 $0$，但是每次获得的分数不是两两匹配，所以我们要给每一个位置赋一个全新的值，最好是随机的。

但是普通的随机因为范围太小，被卡了，于是我们想到扩大随机范围，就对了。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,to[1000005],a[1000005],n,q,l,r;
signed main(){
	srand(time(0));
	for(int i=1;i<=1000000;i++){
		to[i]=rand();
		to[i]*=rand();
	}
	cin>>t;
	while(t--){
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			a[i]=(a[i-1]^to[a[i]]);
		}
		while(q--){
			cin>>l>>r;
			if((r-l+1)&1){
				cout<<"NO\n";
				continue;
			}
			if(a[r]==a[l-1])cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：sad_lin (赞：0)

## 简化题意

因为我们想让后手不输，每个人都会拿当前最大的数，所以区间长度为奇数时我们完全赢不了，偶数时只有**每个数都出现偶数次**才只能平局~~好可怜~~。

## 莫队

因为是查询区间出现次数不难想到用**莫队**，我们每次移动指针时更新每个数的出现次数，并且更新出现次数为奇数的数的个数，如果奇数个数不为 $0$ 那就必输。

[类似的题。](https://www.luogu.com.cn/problem/P1997)

因为比较经典所以不上代码~~不是因为懒~~。

## 异或哈希

我们都知道异或操作，但是其实异或是可以统计出现次数奇偶性的，```1,1,1,2,2``` 异或后结果为 $1$ 说明 $1$ 的出现次数为奇数，```1,1,2,2,2,2``` 异或后结果为 $0$ 说明所有数出现次数都为偶数。

所有说我们只要求**前缀异或和**然后查询端点上的值是否相等就行了吗？显然并不对，```1,2,3``` 异或后结果也为 $0$ 但是显然并不出现奇数次，我们用**哈希**的思想异或上随机数就好了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register 
const int N=1e6+10;
using namespace std;

int n,m;
int a[N];
int b[N];

mt19937 rnd(time(0));

void solve(){
	
	cin>>n>>m;
	
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a[i]=a[i-1]^b[x];
	}
	
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		if(a[r]==a[l-1]){
			cout<<"YES\n";
		}
		else{
			cout<<"NO\n";
		}
	} 
	for(int i=1;i<=n;i++){
		a[i]=0;
	} 
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    for(int i=1;i<=1e6;i++){
		b[i]=rnd();
	}
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：eb0ycn (赞：0)

首先很难不看出来，后手绝对赢不了。考虑什么时候会平局。

即先手取一个数，后手总能取相同的数。也就是区间内所有数的出现次数为偶数。

一开始我一直在想主席树做法，感觉假了，不知道别人有没有做出来的。

那就乖乖写莫队吧。


```cpp
#include<bits/stdc++.h>
using namespace std;
bool tong[1000001];
int t,n,q,a[200001],L,R,blk,ans[200001],cur;
struct query{
	int l,r,id;
	bool operator<(const query&cwx)const{
		if(l/blk!=cwx.l/blk)return l/blk<cwx.l/blk;
		return r<cwx.r;
	}
}Q[200001];
void ad(int pos){
	if(tong[a[pos]])--cur;
	else ++cur;
	tong[a[pos]]^=1;
}
int main(){
	scanf("%d",&t);
	while(t--){
		for(int i=1;i<=n;++i)tong[a[i]]=0;
		scanf("%d%d",&n,&q),blk=sqrt(n),cur=R=0,L=1;
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		for(int i=1;i<=q;++i)scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
		sort(Q+1,Q+q+1);
		for(int i=1;i<=q;++i){
			while(L>Q[i].l)ad(--L);
			while(R<Q[i].r)ad(++R);
			while(L<Q[i].l)ad(L++);
			while(R>Q[i].r)ad(R--);
			ans[Q[i].id]=cur;
		}
		for(int i=1;i<=q;++i)printf("%s\n",ans[i]?"NO":"YES");
	}
	return 0;
}
```

---

## 作者：doumingze (赞：0)

首先根据样例我们可以发现，两人的最优策略就是每次把区间内目前剩下的得分最大的靶子打下来。那么显然 Sheriff 最多只能做到平局，且可以发现平局时两人每一轮击打的靶子得分是相同的。

于是问题就转化为：求一段区间内所有的数字出现次数是否都是偶数。这个问题有很多解法，莫队就是其中之一。本题莫队的玩法比较基础，不熟悉莫队的同学可以手动移步至 [P1494 [国家集训队] 小 Z 的袜子](https://www.luogu.com.cn/problem/P1494)，先对莫队有个大致的了解，然后根据这个思想应该就可以光速写出来了。时间复杂度 $O(n\sqrt{n})$，可以通过本题。

不太理解的就看代码罢。

```cpp
const int N = 2e5 + 10, M = 1e6 + 10;
int a[N], cnt[M]; // cnt 记录区间内某个数的出现次数
int n, m, B;
struct Query{
	int l, r, id;
	bool operator < (const Query &w) const // 基本的莫队排序，不多讲。
	{
		if(l / B != w.l / B) return l < w.l;
		if(l / B & 1) return r < w.r;
		return r > w.r;
	}
}q[N];
bool ans[N];
int cur; // cur 为当前区间出现次数为奇数次的数的数量

void add(int x)
{
	cnt[x] ++;
	if(cnt[x] & 1) cur ++; // 出现次数变奇数，对 cur 产生贡献
	else cur --; // 反之，失去了对 cur 的贡献
}

void del(int x)
{
	if(cnt[x] & 1) cur --; // 原来是奇数，现在将变成偶数，失去对 cur 贡献
	else cur ++; // 反之现在将变成奇数，对 cur 产生贡献
	cnt[x] --;
}

int main()
{
	int t;
	cin >> t;
	while(t --)
	{
		cur = 0;
		scanf("%d%d", &n, &m);
		B = sqrt(n); //得到块长
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i ++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
		sort(q + 1, q + 1 + m); //离线，排序。
		int l = 1, r = 0;
		for(int i = 1; i <= m; i ++)
		{
			while(l > q[i].l) add(a[-- l]);
			while(r < q[i].r) add(a[++ r]);
			while(l < q[i].l) del(a[l ++]);
			while(r > q[i].r) del(a[r --]);
			ans[q[i].id] = (cur == 0);
		}
		for(int i = 1; i <= m; i ++)
		{
			if(ans[i]) puts("YES");
			else puts("NO");
			ans[i] = false;
			q[i].l = q[i].r = q[i].id = 0;
		}
		for(int i = 1; i <= n; i ++) cnt[a[i]] = 0, a[i] = 0;
	}
	return ((1 << 1) ^ 4 & 5 + 1 - 4) * (1 + 9 - 1 + 9 * 8 - 1) * 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

双方要赢肯定尽量选大的，那么能平局当前仅当有偶数个数，且存在划分成若干个值全部相同的大小为 $2$ 的可重集。

那么异或哈希即可。

（二）

AC 代码。

```cpp
//2024-09-22 00:15:12
#include<bits/stdc++.h>
#define db double
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mkp make_pair
#define pii pair<int,int>
#define ull unsigned long long
using namespace std;
bool MBE;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f; 
}
int s[200010];
ull has[1000010];
mt19937_64 rnd(time(0));
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    int T=read();
    for(int i=1;i<=1000000;i++)
    	has[i]=rnd();
   	while(T--){
   		int n=read(),q=read();
   		for(int i=1;i<=n;i++){
   			int x=read();
   			s[i]=s[i-1]^has[x];
   		}
   		while(q--){
   			int l=read(),r=read();
   			if((r-l+1)&1)puts("NO");
   			else if(s[r]==s[l-1])puts("YES");
   			else puts("NO");
   		}
   	}
    bool MED;
    cerr<<(&MED-&MBE)/1048576.0<<" MB, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

