# Xum

## 题目描述

You have a blackboard and initially only an odd number $ x $ is written on it. Your goal is to write the number $ 1 $ on the blackboard.

You may write new numbers on the blackboard with the following two operations.

- You may take two numbers (not necessarily distinct) already on the blackboard and write their sum on the blackboard. The two numbers you have chosen remain on the blackboard.
- You may take two numbers (not necessarily distinct) already on the blackboard and write their [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) on the blackboard. The two numbers you have chosen remain on the blackboard.

 Perform a sequence of operations such that at the end the number $ 1 $ is on the blackboard.

## 样例 #1

### 输入

```
3```

### 输出

```
5
3 + 3
3 ^ 6
3 + 5
3 + 6
8 ^ 9```

## 样例 #2

### 输入

```
123```

### 输出

```
10
123 + 123
123 ^ 246
141 + 123
246 + 123
264 ^ 369
121 + 246
367 ^ 369
30 + 30
60 + 60
120 ^ 121```

# 题解

## 作者：Suiseiseki (赞：10)

~~咋做法又和官方题解不一样啊。~~

一个很好想的思路是考虑每一次将最高位去掉转换成一个子问题，所以说我们的目标就是构造出最高位的那一个 1，即令 $high_x$ 为 $x$ 转换为二进制后最高的非 0 位，我们需要找到 $2^{high_x}$ ，那么我们可以将 $x$ 在二进制意义下向左平移使得平移最小的非 0 位与 $high_x$ 相等，令这个数为 $y$ ，然后再将两个数异或起来，这样的话我们就可以将 $high_x$ 处置为 0，令这个数为 $z$ ，然后再将 $z+y$ 记为 $p$，紧跟着将 $p\oplus x$ 得到 $q$ ，最后在将 $y+y$ 得到 $h$ ，然后将 $q\oplus h$ 得到 $2^{high_x+1}$ ，然后在利用这一个数将 $y$ 中在 $>high_x$ 的位全部异或掉，这样的话我们就得到了 $2^{high_x}$ ，可以将其转换成子问题。

可能上面讲得不太好理解，下面举一个例子（以下所有的数均为二进制下的数）：

```
x=000111
000111 + 000111 = 001110
001110 + 001110 = 011100
011100 ^ 000111 = 011011
011011 + 001110 = 110111
110111 ^ 000111 = 110000
011100 + 011100 = 111000
110000 ^ 111000 = 001000
011100 ^ 001000 = 010100
001000 + 001000 = 010000
010100 ^ 010000 = 000100
000111 ^ 000100 = 000011
```

至此，原问题成功地被转换为了规模更小的子问题。

时间复杂度以及操作数均为 $O(\log^2 n)$ 。

代码可以去我的博客查看：[My Blog](https://www.cnblogs.com/withhope/p/13805006.html)

---

## 作者：TernaryTree (赞：9)

智慧构造。考虑每次消掉 $x$ 最高位上的 $1$。我们来手摸一下。假设 $x=\overline{1abc1}$。 

$$
\begin{aligned}
1abc&1 \\
1abc1000&0 \\
1abc0abc&1 \\
1abc01abc&1 \\
1abc00000&0 \\
1abc10000&0 \\
10000&0
\end{aligned}
$$

具体过程：设 $d=\lfloor \log_2x\rfloor$，则第二个数由 $x$ 自增 $d$ 次后得到，第三个数是 $x$ 异或第二个数，第四个数是第二个数加第三个数，第五个数是 $x$ 异或第四个数，第六个数是第二个数自增一次，第七个数是第五个数异或第六个数，也就是 $2^{d+1}$。我们反复自增 $2^{d+1}$，消掉第二个数上 $\ge d+1$ 位上的 $1$，即可得到 $2^{d}$，并异或 $x$ 得到 $x$ 去掉最高位上的 $1$ 的结果。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const bool multidata = 0;

template<typename T = int>
T read() {
	T x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

template<typename T = int>
void write(T x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write<T>(x / 10), pc(x % 10 + '0');
}

int x, m;
int u[maxn], v[maxn];
char op[maxn];

int make(int x, char o, int y) {
	u[++m] = x, op[m] = o, v[m] = y; 
	if (o == '+') return x + y;
	else return x ^ y;
}

void solve(int x) {
	if (x == 1) return;
	int d = __lg(x);
	int y = x;
	rep(i, 1, d) y = make(y, '+', y);
	int z = make(x, '^', y);
	int w = make(z, '+', y);
	int p = make(w, '^', x);
	int q = make(y, '+', y);
	int D = make(p, '^', q);
	rep(i, d + 1, 61) {
		if (y >> i & 1) y = make(y, '^', D);
		if (!(y >> i)) break;
		D = make(D, '+', D);
	}
	solve(make(x, '^', y));
}

void fake_main() {
	x = read();
	solve(x);
	write(m), pc('\n');
	rep(i, 1, m) write(u[i]), pc(' '), pc(op[i]), pc(' '), write(v[i]), pc('\n');
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}

```

---

## 作者：SSerxhs (赞：8)

考虑将 $x$ 左移使得最低位和 $x$ 最高位对齐

例如 $x=1001\rightarrow y=1001000$

$z=x$ xor $y$ 一定不会是 $x$ 的倍数（因为这个数与 $x+y$ 减少了 $2^n$，而 $x,y$ 都是奇数）

考虑到相邻两数 xor 可能是 1，可以借助 $z$ 找到一个膜 $x$ 余 $1$ 的数，然后对 $x$ 跑快速乘就可以找到相邻两数

如何得到这个数？这相当于一个同余方程问题 $kz\equiv 1\pmod{x}$ ，套个板子就可以了，或者写扩欧（拉）

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+2,M=1e6+2;
ll m;
ll ans[N][3],phi[M],ss[M];
ll n,c,fh,i,j,t,q,gs,x,y,z;
bool ed[M];
inline void read(ll &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
inline ll ksm(register ll x,register ll y,const ll p)
{
	register ll r=1;
	while (y)
	{
		if (y&1) r=(ll)r*x%p;
		x=(ll)x*x%p;y>>=1;
	}
	return r;
}
int main()
{
	read(n);m=n;phi[1]=1;
	for (i=2;i<=n;i++)
	{
		if (!ed[i]) phi[ss[++gs]=i]=i-1;
		for (j=1;(j<=gs)&&(i*ss[j]<=n);j++)
		{
			ed[i*ss[j]]=1;
			if (i%ss[j]==0)
			{
				phi[i*ss[j]]=phi[i]*ss[j];break;
			}
			phi[i*ss[j]]=phi[i]*(ss[j]-1);
		}
	}
	for (i=1;i<=n;i<<=1);i>>=2;
	while (i)
	{
		ans[++q][1]=m;ans[q][2]=m;ans[q][0]=0;
		m<<=1;i>>=1;
	}
	ans[++q][1]=m;ans[q][2]=n;ans[q][0]=1;m^=n;//printf("m=%lld\n",m);
	x=ksm(m%n,phi[n]-1,n);if (1^x*m&1) x+=n;y=0;//printf("x=%lld\n",x);
	while (x)
	{
		if (x&1) {if (y){ans[++q][1]=m;ans[q][2]=y;y+=m;} else y=m;}
		x>>=1;if (x){ans[++q][1]=m;ans[q][2]=m;m<<=1;}
	}//printf("y=%lld\n",y);
	if (y%n!=1) while (1);
	if (y!=1){
	x=(y-1)/n;z=y;y=0;
	while (x)
	{
		if (x&1) {if (y){ans[++q][1]=n;ans[q][2]=y;y+=n;} else y=n;}
		x>>=1;if (x){ans[++q][1]=n;ans[q][2]=n;n<<=1;}
	}x=z-1;
	ans[++q][1]=x;ans[q][2]=x+1;ans[q][0]=1;}
	printf("%lld\n",q);
	for (i=1;i<=q;i++) printf("%lld %c %lld\n",ans[i][1],ans[i][0]?'^':'+',ans[i][2]);
}
```

---

## 作者：feecle6418 (赞：7)

没打 Global Round，赛后看题 10min 就会了，错失上分机会，，，

---

不难想到一种贪心：

- 每次选择能够得到的数最小（且得到的数未写在黑板上）的操作，直到得到 $1$。

但显然很劣，随便输个数就会卡死。因为这样就像无头苍蝇一样乱撞，没有方向。

什么时候我们会有方向呢？当 $(x,y)=1$ 时，存在 $a,b$ 使 $ax-by=1$。假如 $ax$ 是奇数，$by$ 是偶数，则 $(ax)\ \mathrm{xor}\ (by)=1$！而要得到一个数的倍数是很简单的，直接用二进制思想处理即可。随便试试，好像只需要几步上述贪心就能找到一对满足要求的 $(x,y)$。似乎我们已经做出了这道难度评分 2500 的题目！！

可是这样仍然有问题：考虑形如 $2^x+1$ 的起始数，这样子会使“能够得到的最小的数”总是其倍数，因此无法满足 $(x,y)=1$，又会陷入死循环。

怎么办？最开始先预处理出 $x$（起始数）的所有 $2$ 的次方倍（$x2^i(i\le 30)$），这样 $(2^x+1)\ \mathrm{xor}\ (2^x(2^x+1))$ 就不再是 $2^x+1$ 的倍数了！

可是我们的算法一直找的是“最小数”，并不能找到以上说的那一对，怎么办？我们加入随机化：一半的概率找最小数，一半的概率随便找两个数，这样就雨露均沾，大大提高正确率。（这里非常巧妙，请注意不能一直随便找两个数！否则又会出现“无头苍蝇乱撞”的老问题，没有贪心的方向）

这里我们才终于通过了这道题，不得不说确实值得 2500 的评分。标算大多数时候需要 $1100$ 次左右的运算，我们的方法最坏情况下只需 $277$ 次，非常优秀。

丢个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll x,a[50005],n,sum=0;
set<ll> s;
struct Thing {
	char opt;
	ll x,y;
} t[500005];
ll Exgcd(ll a,ll b,ll &x,ll &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	ll ret=Exgcd(b,a%b,x,y),t=x;
	x=y,y=t-(a/b)*y;
	return ret;
}
void Add(ll a,ll b) {
	t[++sum]= {'+',a,b};
}
void Xor(ll a,ll b) {
	t[++sum]= {'^',a,b};
}
void Make(ll a,ll b) {
	ll t=0;
	for(int i=0; i<=60; i++)if((b-1)&(1ll<<i))t=i;
	for(int i=1; i<=t; i++)if(a*(1ll<<i-1)<2e18)Add(a*(1ll<<i-1),a*(1ll<<i-1));
	ll ans=a;
	for(int i=0; i<=t; i++)if((b-1)&(1ll<<i))Add(ans,a*(1ll<<i)),ans+=a*(1ll<<i);
}
void Print() {
	cout<<sum<<endl;
	for(int i=1; i<=sum; i++)printf("%lld %c %lld\n",t[i].x,t[i].opt,t[i].y);
}
bool Judge(ll x,ll y) {
	if(__gcd(x,y)>1)return 0;
	ll a,b,t=x*y;
	Exgcd(x,y,a,b);
	a=(a%y+y)%y,b=(a*x-1)/y;
	if((a*x)%2==1) {
		Make(x,a),Make(y,b);
		Xor(a*x,b*y);
		Print();
		return 1;
	}
	return 0;
}
void Do(){
	ll m1,m2,mn=1e18,mnp;//0+ 1^
	if(rand()&1){
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				if((a[i]^a[j])<mn&&a[i]!=a[j]&&!s.count(a[i]^a[j]))mn=(a[i]^a[j]),m1=a[i],m2=a[j],mnp=1;
				if((a[i]+a[j])<mn&&!s.count(a[i]+a[j]))mn=(a[i]+a[j]),m1=a[i],m2=a[j],mnp=0;
			}
		}
		if(mnp==0)Add(m1,m2);
		else Xor(m1,m2);
		a[++n]=mn,s.insert(mn);
		for(int i=1;i<n;i++)if(Judge(mn,a[i])||Judge(a[i],mn))exit(0);
	}
	else {
		random_shuffle(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				if(!s.count(a[i]+a[j])){
					mn=(a[i]+a[j]),m1=a[i],m2=a[j],mnp=0;
					break;
				}
				if(a[i]!=a[j]&&!s.count(a[i]^a[j])){
					mn=(a[i]^a[j]),m1=a[i],m2=a[j],mnp=1;
					break;
				}
			}
		}
		if(mnp==0)Add(m1,m2);
		else Xor(m1,m2);
		a[++n]=mn,s.insert(mn);
		for(int i=1;i<n;i++)if(Judge(mn,a[i])||Judge(a[i],mn))exit(0);
	}
}
int main() {
	cin>>x,a[n=1]=x,s.insert(x);
	for(int i=1;i<=20;i++){
		Add(a[i],a[i]);
		n++;
		a[n]=a[n-1]*2;
		s.insert(a[n]);
	}
	while(1)Do();
}
```

---

## 作者：char_phi (赞：7)

学校比赛的时候考了这道题，~~我当然是一分没得~~。

这是一道好构造题。

先不说正解，我看别的题解都没有说怎么拿部分分，但是如果赛时不会正解，那么拿部分分就是很必要的一件事了，所以我在这里说一说。想直接看正解的可以跳过部分分讲解。

注：下文中的 $“⊕”$ 指的是异或运算。

## 算法一 暴力枚举 $(30pts)$ 

我们考虑在什么情况下能够合成一。因为加和运算是始终使数增加的，所以是用异或运算来合成 $1$，并且当且仅当一对相邻的奇数偶数时才能异或出来 $1$。

也就是在类似这种情况下再进行一步异或即可合成 $1$：

```
00010110101
00010110100
```

可以称此局面为出解局面。

考虑如何枚举。设 $S$ 为已经合成的数的集合，那么可以枚举每一个 $S$ 里的元素然后对 $S$ 里的元素全部进行相加和异或操作，得到的新数再次扔到 $S$ 里，继续枚举，直到出现出解局面为止。

关于如何判断出解局面是否出现，可以用一个 $map$ 记录出现了哪些数，然后在合成了新的数 $w$ 时 $\text{check}$ 一下 $w+1\text{、}w-1$ 有没有出现过，出现的话了判断一下异或出来是否为 $1$ ，如果为 $1$ 则输出答案。

## 算法二 随机化 $(40 \sim 96pts)$

随机化还是比较好用的，我们学校 $\text{OJ}$ 上有人 $\text{40pts}$，也有人 $\text{96pts}$，得分高低主要看你写的丑不丑以及你是怎样随机化的了。

分数相对低一点的做法( 一般在 $\text{80pts}$ 以下)，可在已经 $S$ 里随机选一个出来，然后对 $S$ 里的元素全部进行相加和异或操作，把新的数再扔到 $S$ 里，如此往复直到达到出解局面。当然了如果你写的**足够好**也可以获得接近 $\text{90pts}$ 的高分。

对于写数字次数不超过 $10^5$ 这个限制，显然我们在得到答案的路上是有很多无用的数被合成的，对存答案的结构体一趟 $dfs$ 把这些数从答案中删掉即可。也可以 $dfs$ 查找答案是怎样被合成的。

分数较高一点的做法( $\text{80pts}$ 以上)是 [$\text{Delov}$](https://www.luogu.com.cn/user/277792) 大佬想出来的，考虑样例是怎样构造的：$+ ⊕ + + ⊕$，两个样例都是这样，这似乎昭示了什么规律。大胆猜测这种构造方式可以构造出答案，那么就按照他这个操作去进行随机化，也就是循环这个操作数列，然后每次在 $S$ 里随机选一个数出来对 $S$ 中的数进行当前循环到的操作( $+$ 或者 $⊕$ )，相应判断是否达到出解局面。可以获得 $\text{85pts}$ 左右的高分。

提高出解率的方法是构造如下的操作数列并执行：

$$+++\ ...++\ ⊕\ ++++...$$

也就是随机在操作数列里插入一些 $⊕$，使得 $+$ 的操作次数要较多于 $⊕$。这样目前测得最高可以获得 $\text{93pts}$。

还有一种可以获得最高 $\text{96pts}$ 的随机化，涉及到 $\text{exgcd}$，这里不再赘述，因为并不是正解。

## 算法三 构造 $(100pts)$

正解其实挺简单的。考虑如何将数字 $9$ 合成为1：

```
9: 0000 1001
```

因为题目保证给出的 $x$ 是奇数，所以 $x$ 的最低位一定是 $1$。

考虑如何运用这个性质。观察到对于相同的数 $w$ 进行加和运算就是使 $w$ 乘上一个 $2$，**也就等同于 $w$ 左移一位**，那么就可以通过左移来用 $x$ 最低位的 $1$ 去消去较高位的 $1$，不妨每次去消掉 $x$ 最高位的 $1$。考虑如何实现。

首先另取一个数 $y=x$，令 $y$ 最低位的 $1$ 与 $x$ 最高位的 $1$ 对齐：

```
x: 0000 1001
y: 0100 1000
```

之后令 $x ⊕ y$ 得到 $z$：

```
x: 0000 1001
y: 0100 1000
z: 0100 0001
```

再令 $y + z$ 得到 $a$：

```
x: 0000 1001
y: 0100 1000
z: 0100 0001
a: 1000 1001
```

再令 $a ⊕ (y<<1) ⊕ x$ 得到 $b$：

```
x: 0000 1001
y: 0100 1000
z: 0100 0001
a: 1000 1001
   1001 0000 ←(y<<1)
b: 0001 0000
```

这时候发现 $b$ 只剩下一位了，但并不是 $x$ 的最高位；不过因为 $y$ 的最低位即为 $x$ 的最高位，容易想到用 $b$ 依次左移把 $y$ 较高位的 $1$ 通过异或操作消掉，直到 $y$ 仅剩 $x$ 的最高位(也就是把 $y$ 的非最低位全部消掉)，再用 $y$ 去异或消掉 $x$ 的最高位，此时便达到了我们消掉 $x$ 最高位的目的。

如此循环消掉 $x$ 最高位直到 $x=1$ 即可。

代码实现：

```cpp
#include <iostream>
#include <bitset>
#define GMY (520&1314)
#define FBI_OPENTHEDOOR(x, y) freopen(#x ".in", "r", stdin), freopen(#y ".out", "w", stdout);
#define re register int
#define char_phi signed
#define N 100005
using namespace std;
inline void Fastio_setup(){ios::sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL);}

struct Answer{int opt; long long x, y;};

long long x, y, z, a, tmp, plc, anscnt, b, c, d;
struct Answer ans[N];

#define lowbit(x) ((x) & (-(x)))
inline void Xiao(){
	tmp = x; y = x;
	while (tmp != 0)// 取出来x的最高位
		plc = lowbit(tmp), tmp ^= plc;
	while (lowbit(y) != plc)
		{ans[++ anscnt] = (Answer){1, y, y}; y <<= 1;}// 得到y
	// 对齐之后另其与x异或
	ans[++ anscnt] = (Answer){2, x, y};
	z = x ^ y;
	// 另z与y相加得到a
	ans[++ anscnt] = (Answer){1, y, z};
	a = y + z;
	// y左移
	ans[++ anscnt] = (Answer){1, y, y};
	d = y + y;
	// a与y与x异或
	ans[++ anscnt] = (Answer){2, a, d};
	ans[++ anscnt] = (Answer){2, a^d, x};
	b = a ^ d ^ x;
	// 用b去消y
	c = b>>1;
	while (y != c){
		if ((y & b) == b)
			{ans[++ anscnt] = (Answer){2, y, b}, y = y ^ b;}
		ans[++ anscnt] = (Answer){1, b, b}; b <<= 1;
	}
	// 此时剩下的y就是x最高位了
	ans[++ anscnt] = (Answer){2, y, x};
	x = x ^ y;
}

inline void work(){
	cin >> x;
	
	while (x != 1)
		Xiao();
	
	cout << anscnt << '\n';
	for (re i = 1 ; i <= anscnt ; ++ i){
		cout << ans[i].x;
		cout << ((ans[i].opt == 1) ? (" + ") : (" ^ "));
		cout << ans[i].y << '\n';
	}
}
// #define IXINGMY
char_phi main(){
	#ifdef IXINGMY
		FBI_OPENTHEDOOR(a, a);
	#endif
	Fastio_setup();
	work();
	return GMY;
}
```

---

## 作者：lanos212 (赞：6)

### 关于该做法

总操作次数 $O(\log x)$，数字大小上界 $O(x^2)$，时间复杂度 $O(\log x)$，目前各指标最优解。

---
### I.

我们先凑出一些基本的运算操作。

- $2A$：操作次数 $O(1)$，数字上界 $O(A)$。

$$
A+A=2A
$$

- $2^k A$：操作次数 $O(k)$，数字上界 $O(2^k A)$。

$$
A+A=2^1A \\
2^1A+2^1A=2^2A \\
\cdots \\
2^{k-1}A+2^{k-1}A=2^kA
$$

- $kA$：操作次数 $O(\log k)$，数字上界 $O(kA)$。

这一部分类似快速幂，对二进制位进行拆分即可。

例如，可以用下式得到 $11A$：

$$
2^3A+2^1A+2^0A=11A
$$


- $2(A\operatorname{or}B)$：操作次数 $O(1)$，数字上界 $O(A+B)$。

$$
(A+B)+(A \operatorname{xor} B)=2(A\operatorname{or}B)
$$

- $2(A\operatorname{and}B)$：操作次数 $O(1)$，数字上界 $O(A+B)$。

$$
2(A\operatorname{or}B)\operatorname{xor} 2(A \operatorname{xor} B)=2(A\operatorname{and}B)
$$

- $|A-B|$：操作次数 $O(\log A)$，数字上界 $O(AB)$。

假设 $A\ge B$，不满足交换它们即可。

考虑 $A \operatorname{xor} B = A-B$ 的条件为，在二进制下，$B$ 中为 $1$ 的位，$A$ 中也必须为 $1$。（即 $A\operatorname{or}B=A$）

故我们可以通过大幅度的移位来得到 $A-B$。

下式以 $A=10101_2,B=1001_2$ 为例：

$$
\begin{matrix}
\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ {\color{Red}1001}\\
\times\ \ \ \ \ \ \ \ \ \ \ \ 11111\\
\hline
\ \ \ \ \ \ \ {\color{Red}100}{\color{Orange}0}10111\\
+\ \ \ \ \ \ \ \ \ \ \ \ 10101\\
\hline
\ \ \ \ \ \ \ {\color{Red}1001}01100\\
\operatorname{xor}\ {\color{Red}1001}00000\\
\hline
\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 1100

\end{matrix}
$$

这样最后一步的 $\operatorname{xor}$ 运算就与 $-$ 运算等价了。

用一般的式子写就是下式：

$$
((2^{\lfloor{\log_2{A}}\rfloor+1}-1)B+A) \operatorname{xor} (2^{\lfloor{\log_2{A}}\rfloor+1}B) = A-B
$$

其实用到的是 $\operatorname{xor}$ 的性质，当运算的两个数没有 $1$ 的数位相交时，它们的 $\operatorname{xor}$ 和它们相加的值是一样的。

那么这里相当于构造一个 $A-B$ 与 $2^{\lfloor{\log_2{A}}\rfloor+1}B$ 不交，所以用
$\operatorname{xor}$ 可以代替减法反过来得到 $A-B$。

---
### II.

接下来我们从 $x$ 开始做如下操作。

下式以 $x=101011_2$ 为例：

$$
\begin{matrix}
 \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 101011\\
 \operatorname{2and}\  10101100000\\
\hline 
 \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 1000000 \\
-\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 101011\\
\hline 
 \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 10101\\
 \operatorname{2and}\ \ \ \ \ \ \ \ \ \ \ 101011\\
\hline
 \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 10
\end{matrix}
$$

用一般的式子写就是下式：

$$
2((2(x \operatorname{and} 2^{\lfloor \log_2{x} \rfloor}x)-x)\operatorname{and} x)=2
$$

哇哦，现在我们得到了 $2$！

由于 $x$ 是奇数，那么让 $x$ 异或上若干个 $2$ 的幂次即可得到 $1$：

$$
\begin{matrix}
 \ \ \ \ \ \ \ 101011\\
\ \ \ \ \ \ \ 100000\\
\ \ \ \ \ \ \ \ \ \ \ 1000\\
 \operatorname{xor}\ \ \ \ \ \ \ \ \ 10\\

\hline
\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ {\color{Red}1} 
\end{matrix}
$$

code（将节省操作次数与调试用的 set 删去，时间复杂度为 $O(\log x)$） 


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

set<int> S;
int n;
vector<array<int, 3>> ans;

inline bool find(int x) {
    return (S.find(x) != S.end());
}

inline int ADD(int x, int y) {
    assert(find(x) && find(y));

    if (!find(x + y))
        ans.push_back({x, 0, y}), S.insert(x + y);
    return x + y;
}

inline int XOR(int x, int y) {
    assert(find(x) && find(y));

    if (!find(x ^ y))
        ans.push_back({x, 1, y}), S.insert(x ^ y);
    return x ^ y;
}

inline int SUB(int x, int y) {
    if (x < y)
        swap(x, y);

    int lim = 0;

    while (((y << lim) & (-(y << lim))) <= x)
        ADD(y << lim, y << lim), ++lim;

    int na = x;

    for (int i = 0; i < lim; ++i)
        na = ADD(na, y << i);

    return XOR(na, y << lim);
}

inline int OR_2(int x, int y) {
    return ADD(ADD(x, y), XOR(x, y));
}

inline int AND_2(int x, int y) {
    return XOR(ADD(XOR(x, y), XOR(x, y)), OR_2(x, y));
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);

    cin >> n;
    S.insert(n);

    int np = n;

    while ((np & -np) * 2 <= n)
        np = ADD(np, np);

    int P = AND_2(n, np);
    int m = SUB(P, n);
    int two = AND_2(n, m);

    for (int i = 1; i < 20; ++i)
        ADD((1ll << i), (1ll << i));

    for (int i = 19; i; --i)
        if (n >> i & 1)
            n = XOR(n, (1ll << i));

    assert(n == 1);

    cout << ans.size() << '\n';

    for (auto [x, op, y] : ans)
        cout << x << ' ' << (op ? '^' : '+') << ' ' << y << '\n';

    return 0;
}
```

---

## 作者：7KByte (赞：4)

观察条件，由于给定的一定是奇数，所以在二进制下最低位一定是$1$。

这也就意味着我们只用将其他位上的$1$消掉即可。

我们可以每次消除最高位。

但消除最高位需要找到最高位。我们只能进行异或和求和操作。

首先我们将$x$左移若干位使得第一位与原来的最高位对齐，将这个数记做$y$。取$x$和$y$的异或和，记做$z$,可以保证$x$的最高位被消掉。

我们再求出$z+y$，记做$r$，不难发现$r$的低位和$z$相同，高位为$y$左移一位，而中间不同的恰好为最高位的进位。异或起来可以得到最高位。

最后我们将$x$的每一位一个个消掉即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define int long long 
#define N 10005
using namespace std;
struct node{
	int x,y,op;
	node(int X,int Y,int t){x=X;y=Y;op=t;}
};
vector<node>c;
int calc(int x){
	int y=x,ty=(x>>1);
	while(ty){
		c.push_back(node(y,y,0));
		ty>>=1,y<<=1;
	}
	int z=x^y;c.push_back(node(y,x,1));
	//cout<<"s1 "<<z<<endl;
	int rc=z+y;c.push_back(node(z,y,0));
	//cout<<"s2 "<<rc<<endl;
	int we=y+y;c.push_back(node(y,y,0));
	//cout<<"s3 "<<we<<endl;
	int p=we^rc;c.push_back(node(we,rc,1));
	//cout<<"s4 "<<p<<endl;
	int q=p^x;c.push_back(node(p,x,1));
	//cout<<"s5 "<<q<<endl;
	while(y!=(y&-y)){
		if(y&q){
			c.push_back(node(y,q,1));y^=q;
		}
		c.push_back(node(q,q,0));q<<=1;
	}
	c.push_back(node(y,x,1));return x^y;
}
signed main(){
	int n;scanf("%lld",&n);
	while(n!=1)n=calc(n);
	printf("%lld\n",(int)c.size());
	for(int i=0;i<(int)c.size();i++){
		if(c[i].op==0)printf("%lld + %lld \n",c[i].x,c[i].y);
		else printf("%lld ^ %lld\n",c[i].x,c[i].y);
	}
	return 0;
}
/*
g++ E.cpp -o E -Wall -std=c++11
*/
```

---

## 作者：luchenxi2012 (赞：3)

# CF1427E Xum 题解
蒟蒻从下午 1:30 开始一直调到 4:00，特来发一篇题解警示后人。此题解有详细证明构造方法的正确性。

[题目传送门](https://www.luogu.com.cn/problem/CF1427E)

## 思路
容易想到，可以每次消掉 $x$ 的最高位，这样就可以很轻易的得到一了。

关键是这个怎么做。

由于我们是要消掉最高位，所以我们考虑每次把 $x$ 最低位平移至最高位，这是可以通过多次加法完成的。我们设 $y$ 为操作后的数。

接下来，可以把 $x$ 最高位消掉，令 $z=x\oplus y$。

此时再令 $m=y+z$，$n=m\oplus x$，有 $n\oplus (y+y)$ 就是 $x$ 最高位再高一位了，证明如下：（以下均为二进制）

令 $x=\overline{a_0a_1a_2\ldots a_N000\ldots 0}$，其中有 $A$ 个零，$a_0=a_N=1$。

则 $y=\overline{a_0a_1a_2\ldots a_N000\ldots 0}$，其中零个数比 $x$ 多 $N$ 个，为 $A+N$ 个。可以见得，$x$ 中 $a_0$ 与 $y$ 中 $a_N$ 是对齐的。

则 $z=\overline{a_0a_1a_2\ldots a_{N-1}0a_1a_2\ldots a_N000\ldots 0}$，一样也有 $A$ 个零。$a_{N-1}$ 与 $a_1$ 中间是零是因为 $1\oplus 1=0$。

则 $m=\overline{a_0a_1a_2\ldots a_{N-1}0a_Na_1a_2\ldots a_N000\ldots 0}$，其实就相当于是把 $z$ 在 $a_1$ 那里插入了一个 $a_N$。

则 $n=\overline{a_0a_1\ldots a_N000\ldots 0}$，因为 $a_N=a_0=1$，异或一下就抵消了。

而 $y+y$ 中前 $N$ 位均与 $n$ 的前 $N$ 位对齐，于是，一异或就消除了。

于是，就只剩一个 $\overline{a_N000\ldots 0=1000\ldots 0}$，其中有 $A+N+1$ 个零，也就是 $x$ 的最高位再高一位上的权值。

得出最高位后，就可以用这个二的幂去异或，消去 $y$ 更高的位数，只保留 $x$ 的最高位上的权值。

此时再异或一下就可以把 $x$ 最高位“删除”了。

此后每次删除最高位，时间复杂度和操作数均为 $\log^2n$。

如果不太理解可以看这个例子：

```
n = 4, A = 4
x = 00000110010000
y = 01100100000000
z = 01100010010000
m = 11000110010000
n = 11000000000000
y+y=11001000000000
与 n 异或后即抵消。
```

## 代码
~~调两个小时调出来的~~

代码有注释，可对照着看。
```cpp
#include <cstdio>
#define int long long
struct answer {
	int op, a, b;
} ans[100001];
#define lowbit(x) (x & (-x)) // 求最低位
int cnt, y, z, m, n, a, t, x;
void kracha() { // 分裂最高位
	y = x, t = x;
	while (t)
		a = lowbit(t), t ^= a; // 找最高位
	while (lowbit(y) != a) // 将y平移
		ans[++cnt] = {1, y, y},
		y <<= 1; // 下面都是讲过的，没记住可以回头看
	ans[++cnt] = {2, x, y}, z = x ^ y;
	ans[++cnt] = {1, y, z}, m = y + z;
	ans[++cnt] = {1, y, y}, n = y << 1;
	ans[++cnt] = {2, m, n}, t = m ^ n;
	ans[++cnt] = {2, t, x}, t ^= x;
	int T = t >> 1; // T为x最高位
	while (y != T) {
		if ((y & t) == t)
			ans[++cnt] = {2, y, t},
			y ^= t;
		ans[++cnt] = {1, t, t};
		t <<= 1;
	}
	ans[++cnt] = {2, x, y}, x ^= y; // 把最高位消去
}
signed main() {
	scanf("%lld", &x);
	while (x != 1) kracha();
	printf("%lld\n", cnt);
	for (int i = 1; i <= cnt; i++) // 输出答案。
		if (ans[i].op == 1)
			printf("%lld + %lld\n", ans[i].a, ans[i].b);
		else printf("%lld ^ %lld\n", ans[i].a, ans[i].b);
	return 0;
}
```
## 警示后人
+ `lowbit(x)` 要写成 `(x & (-x))` 而不是 `x & (-x)`!
+ 不要为了省事就把 `T` 换成 `t >> 1` ，因为 `t` 是会变的！
+ 记得开 `long long`！

upd 2024.7.29：补充证明中的一些漏洞，添加了解释说明。

---

## 作者：chenhouyuan (赞：2)

~~为什么我的思路与众不同...~~

我们发现 $1$ 只能通过 $2x\oplus2x+1$ 得到，因此我们的任务就变成了找到一组 $a,b$ 使得 $ax-by=1$。这可以用扩展欧几里得求解，但是根据裴蜀定理我们首先得保证 $\gcd(x,y)=1$。当 $y=x\oplus 2^{n-1}x$ 可行，其中 $n$ 为 $x$ 在二进制下的长度，证明如下：

$\gcd(x,y)=\gcd(x,x\oplus 2^{n-1}x)=\gcd(x,(2^{n-1}+1)x-2^n)=\gcd(x,-2^n)=\gcd(x,2^n)$ 因为 $x$ 是奇数所以显然有 $\gcd(x,2^n)=1$。

但是有时候 $ax$ 算出来是偶数导致 $ax\oplus by\ne1$ 怎么办呢？$ax$ 和 $by$ 都加上 $x$ 即可。
### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node{
	ll e,f,g;//0+1^
}ans[100010];
ll cnt;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	ll g=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
ll ksc(ll x,ll y){
	ll res=0;
	while(y){
		if(y&1){
			if(res){
				ans[cnt]={res,x,0};
				cnt++;
			}
			res+=x;
		}
		if(y!=1){
			ans[cnt]={x,x,0};
			cnt++;
		}
		x+=x;
		y>>=1;
	}
	return res;
}
int main(){
	ll x;
	scanf("%lld",&x);
	ll y=x;
	ll n=log2(x);
	while(y<(x<<n)){
		ans[cnt]={y,y,0};
		cnt++;
		y+=y;
	}
	ans[cnt]={x,y,1};
	cnt++;
	ll a,b;
	exgcd(x,-(x^y),a,b);
	ll p=ksc(x,a),q=ksc(x^y,b);
	if((p^q)!=1){
		ans[cnt]={p,x,0};
		cnt++;
		ans[cnt]={q,x,0};
		cnt++;
		q+=x;
		p+=x;
	}
	ans[cnt]={q,p,1};
	cnt++;
	printf("%lld\n",cnt);
	for(ll i=0;i<cnt;i++){
		printf("%lld",ans[i].e);
		if(ans[i].g){
			printf(" ^ ");
		}
		else{
			printf(" + ");
		}
		printf("%lld\n",ans[i].f);
	}
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：2)

### 分析：
观察到所给的数一定是一个奇数，所以其最低位一定为 $1$，考虑消掉其高位的 $1$，从而构造出一个 $1$ 来。那么如何消呢，考虑构造一个仅有一个 $1$ 的数字，用其来异或消去高位的 $1$，那么我们的问题就转化为了构造一个仅有一个 $1$ 的数字。

首先设原数字为 $x$，考虑通过不断自己加自己的方法，不断让自己左移一位，用 $x$ 左移构造出 $y$，使 $y$ 最低位的 $1$ 与 $x$ 最高位的 $1$ 对齐。那么 $x$ 异或上 $y$ 得到 $z$，使 $x$ 的最高位被消去，再计算 $z+y$，记为 $a$，此时感性理解一下，$z$ 的高位是 $y$ 的高位，相加之后高位向上进位，而 $z$ 的低位是 $x$ 的低位。所以很显然将 $a$ 异或上 $x$ 再异或 $y$ 左移一位，之后即可得到一个仅有一个 $1$ 的数字，但是这个数字比 $x$ 要大，我们只能继续自加消去 $y$ 高位的 $1$，因为 $y$ 的低位就是 $x$ 的最高位，就此就可以消去 $x$ 的高位了，循环往复即可。
### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000005
#define lowbit(i) (i&(-i))
using namespace std; 
ll x;
struct node{
	ll a,b;
	bool op;
};
vector<node> ans;
int solve(ll x){
	ll xx=x>>1,y=x,z,a,b,yy;
	while(xx!=0){
		ans.push_back((node){y,y,0});
		xx>>=1;
		y<<=1;
	}
	z=x^y;
	ans.push_back({x,y,1});
	a=y+z;
	ans.push_back({y,z,0});
	ans.push_back({y,y,0});
	y=y<<1;
	ans.push_back({a,y,1});
	a=a^y;
	b=a^x;
	ans.push_back({a,x,1});
	y>>=1;
	yy=y-lowbit(y);
	while(yy!=0){
		if(yy&b){
			ans.push_back({yy+lowbit(y),b,1});
			yy=yy^b;
		}
		else{
			
			ans.push_back({b,b,0});
			b<<=1;
		}
	}
	ans.push_back({lowbit(y),x,1});
	return lowbit(y)^x;
}
int main(){
	cin>>x;
	while(1){
		x=solve(x);
		if(x==1){
			cout<<ans.size()<<'\n';
			for(int i=0;i<ans.size();i++){
				cout<<ans[i].a<<" ";
				if(ans[i].op) cout<<"^ ";
				else cout<<"+ ";
				cout<<ans[i].b<<'\n'; 
			}
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Melting_Pot (赞：2)

# Xum
## [洛谷传送门](https://www.luogu.com.cn/problem/CF1427E)
- ### 题意：
    简化来说就是给你一个奇数 $x$，而你只能使用 $+$ 或 $\bigoplus$，让你构造出一个包含 $1$ 的数集。
- ### Analysis：
    首先为了得到 $1$，我们一般有两种思路，第一种是构造出 $n$ 与 $n+1$ 这种“出解情况”，这种思路考场寄掉了，先咕。
    那么来说说正解思路：
    对于一个数 $x$，我们考虑它的运算集：“$+$”可以实现二进制数的左移操作，而 $\bigoplus$ 本身就是二进制操作，因此，我们考虑以下转移：

    说明：未知位用 $a$ 代替，设二进制数长度为 $k$。
    $$1aaaaaaa1\tag{1}$$
    左移 $k$ 位得：
    $$1aaaaaaa100000000\tag{2}$$
    $1$ 式 $\bigoplus$ $2$ 式得：
    $$1aaaaaaa0aaaaaaa1\tag{3}$$
    $3$ 式 $+$ $2$ 式得：
    $$1aaaaaaa10aaaaaaa1\tag{4}$$
    $2$ 式自加后与 $\bigoplus$ $4$ 式得：
    $$aaaaaaa1\tag{5}$$
    $5$ 式 $\bigoplus$ $1$ 式即可得最高位：
    $$100000000\tag{6}$$
- ### 实现：
    经过上述分析，我们已经实现了消去最高位，接下来只要一直循环求解下去即可。

    
    



---

## 作者：kiritokazuto (赞：2)

# Xorum
> ~~机房大佬们用随机化切掉了这个题，我谔谔。~~

- 一道非常巧妙的构造题。

- 因为我们最初是一个奇数，将他记做 $x$，所以它的最低位肯定是一个一，那我们只需要将它除最低位的一之外的一都消除掉就行。
- 首先我们考虑一个数它的最低两位是 $0,1$，对于是 $1,1$ 的可以将自己加三次，相当于左移一次再将那个一进一下位来变成这种情况。
- 考虑将这个最低位的一一直左移到与我的最高位对齐产生一个低位都是 $0$ 的新数，记为 $y$。
- 之后将 $x$ 和 $y$ 相加，答案记做 $z$，再将 $x$ 和 $y$ 异或，得到 $k$。
- 之后将 $z$ 和 $k$ 异或得到 $tmp$，我们可以发现一个神奇的东西，这个 $tmp$ 是只有原数 $x$ 的最高位左边的一位有 $1$ 的一个数字(也就是说这个数字所有位上只有一位有 $1$)。
- 那么我们就可以快乐地用它一直左移，将我 $y$ 除去和 $x$ 最高位对着的 $1$ 都消掉。
- 之后将这个新的 $y$ 与 $x$ 异或，就可以将 $x$ 的最高位消除。
- 然后重复这个过程，把 $x$ 消为 $1$。
- 整体大概是个 $O(\log ^ {2} x)$ 的复杂度。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define Re register int
#define LD double
#define mes(x, y) memset(x, y, sizeof(x))
#define cpt(x, y) memcpy(x, y, sizeof(x))
#define fuc(x, y) inline x y
#define fr(x, y, z)for(Re x = y; x <= z; x ++)
#define fp(x, y, z)for(Re x = y; x >= z; x --)
#define delfr(x, y, z)for(Re x = y; x < z; x ++)
#define delfp(x, y, z)for(Re x = y; x > z; x --)
#define frein(x) freopen(#x ".in", "r", stdin)
#define freout(x) freopen(#x ".out", "w", stdout)
#define ki putchar('\n')
#define fk putchar(' ')
#define WMX aiaiaiai~~
#define pr(x, y) pair<x, y>
#define mk(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define re(x) return x
#define sec second
#define fst first


using namespace std;
namespace kiritokazuto{
    auto read = [](){
        LL x = 0;
        int f = 1;
        char c;
        while (!isdigit(c = getchar())){ if (c == '-')f = -1; }
        do{ x = (x << 1) + (x << 3) + (c ^ 48); } while (isdigit(c = getchar()));
        return x * f;
    };
    template  <typename T> fuc(void, write)(T x){
        if (x < 0)putchar('-'), x = -x;
        if (x > 9)write(x / 10); putchar(x % 10 | '0');
    }
}

using namespace kiritokazuto;



const int maxn = 1e5 + 10, maxm = 505, Mod = 1e9 + 7;
const LL Inf = 0x7ffffffffffffff;
#define int long long
int x;

struct Node {
    int x, y, type;
    Node(){};//1 为加 2为xor
    Node(int a, int b, int c){x = a, y = b, type = c;};
};
int bit[51],bbit[51];
int tot = 0, tot1 = 0;
vector <Node> wmx;
#define add(x, y) wmx.push_back(Node{x, y, 1})
#define Xor(x, y) wmx.push_back(Node{x, y, 2})
fuc(void, calc)(int x, int type) {
    if(type) {
        int num = 0;
        while(x){
            if(x & 1) bit[++tot] = num;
            num++;
            x >>= 1;
        }
    }else {
        int num = 0;
        tot1 = 0;
        while(x){
            if(x & 1) bbit[++tot1] = num;
            num++;
            x >>= 1;
        }
    }
}
fuc(void, work)(int x) {//此时为低位01
    calc(x, 1);
    fp(i, tot, 2){
        int tmp = x;//取出x
        int res = x;
        int xx = (tmp << (bit[i]));//对齐最高位 -> 就是 tmp
        fr(j, 1, bit[i]) {
            add(tmp, tmp);
            tmp += tmp;
        }
        //int xxx = (xx + x);//加起来
        //int xxxx = (xx ^ x);//异或
        int xxx = (xx + x) ^ (xx ^ x);//拿出最高位左边的一
        add(xx, x);
        Xor(xx, x);
        Xor(xx + x, xx ^ x);
        calc(xx, 0);
        tmp = xxx;
        bbit[1]++;
        fr(j, 2, tot1) {
            fr(k, bbit[j - 1] , bbit[j] - 1){
                add(tmp, tmp);
                tmp += tmp;
            }
            Xor(tmp, xx);
            xx ^= tmp;
        }
        Xor(xx, x);
        x ^= xx;
    }
}
signed main() {
    x = read();
    if((x >> 1) & 1) {
        int tmp = x << 1;
        add(x, x);
        add(x, tmp);
        x = x + tmp;
        work(x);
    }else {
        work(x);
    }
    write(wmx.size());
    ki;
    for(auto it : wmx) {
        if(it.type == 1){
            printf("%lld + %lld\n", it.x, it.y);
        }else {
            printf("%lld ^ %lld\n", it.x, it.y);
        }
    }
    return 0;
}
```


---

## 作者：251Sec (赞：1)

首先注意到 $2t \oplus (2t+1)=1$，所以只要我们得到一个偶数和它加一就做完了，进一步地，如果我们得到两个互质的数 $p,q$，那么一定可以 ExGCD 得到 $2t$ 和 $(2t+1)$。

考虑怎么构造 $p,q$。发现设 $n=\lfloor\log_2 x\rfloor$，则 $p=x$，$q=(2^{n}x) \oplus x$ 是合法的，证明就是考虑 $q+2^{n+1}$ 是 $p$ 的倍数，而 $\gcd(p,2^{n+1})=1$。

最后还有一个问题，ExGCD 求的是整数解，但是我们没有减法，所以希望得到的是正整数解。但是由小凯的疑惑的结论，只需要保证 $2t>pq-p-q$ 即可，后者是 $10^{18}$ 级别的，在题目要求的 $5 \times 10^{18}$ 以内。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
mt19937_64 eng(363415);
const ll L = 1e18;
string ope; int opC;
void Add(long long x, long long y) { opC++, ope += to_string(x) + " + " + to_string(y) + "\n"; }
void Xor(long long x, long long y) { opC++, ope += to_string(x) + " ^ " + to_string(y) + "\n"; }
ll ExGCD(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	ll d = ExGCD(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
void Mul(ll x, ll y) {
	ll res = x; y--;
	for (; y; y >>= 1, Add(x, x), x *= 2) if (y & 1) Add(res, x), res += x;
}
int main() {
	long long x; scanf("%lld", &x);
	int p = __lg(x);
	long long y = x;
	while (__lg(y & -y) != p) {
		Add(y, y);
		y <<= 1;
	}
	Xor(x, y), y ^= x;
	ll a, b;
	ExGCD(x, y, a, b);
	ll a1, b1, a2, b2;
	a1 = a * L, b1 = b * L, a2 = a * (L + 1), b2 = b * (L + 1);
	if (a1 <= 0) {
		ll t = -a1 / y + 1;
		a1 += y * t, b1 -= x * t;
	}
	if (b1 <= 0) {
		ll t = -b1 / x + 1;
		a1 -= y * t, b1 += x * t;
	}
	if (a2 <= 0) {
		ll t = -a2 / y + 1;
		a2 += y * t, b2 -= x * t;
	}
	if (b2 <= 0) {
		ll t = -b2 / x + 1;
		a2 -= y * t, b2 += x * t;
	}
	Mul(x, a1), Mul(y, b1), Mul(x, a2), Mul(y, b2);
	Add(x * a1, y * b1), Add(x * a2, y * b2);
	Xor(L, L + 1);
	printf("%d\n%s", opC, ope.c_str());
	return 0;
}
```

---

## 作者：zesqwq (赞：1)

看到这个次数限制，$10^5$，直接乱搞吧，但是这是一个构造次数能爆标的乱搞。

后来看了 $\text{sol}$，发现只有一篇乱搞，而且写得很长很麻烦，所以我提供一种简单而稳定的乱搞解法，可以在 $600$ 次以内出解，实际上能达到更好。

你发现你很容易构造 $x$ 的倍数，然后把这个数放入线性基中。于是我们重复随机这个倍数，直到得到线性基中所对应 $2^0$ 的值即可。

问题来了，如何带上输出方案的线性基？你发现每一个线性基中的每个数都是其中你有的一些数异或的值，于是我们再用额外存一个 $\log V$ 个 `vector`，表示我们是如何异或出 $2^k(k \le \log V)$ 这个值的。

但是如果你直接实现会跑得巨慢，于是你可以加上这两个优化：

1. `vector` 中不应该有重复元素，因为 $a \operatorname{xor} a = 0$，
2. 当当前要插入的数所对应的 `vector` 大小比原有的小时，交换当前插入的和原有的。

具体可以参考代码：

```cpp
inline void zhenghe(vector<long long> &vec) { //优化1
    vector<long long> ans;
    for (int l = 0, r = 0; l < vec.size(); l = r) {
        while (r < vec.size() && vec[r] == vec[l]) ++r;
        if ((r - l) & 1) ans.push_back(vec[l]);
    }
    vec = ans;
}
inline void add(long long x, long long tmp) {
    vector<long long> now;
    gouzao(x, tmp);
    x *= tmp;
    now.push_back(x);
    for (int i = 60; ~i; i--) {
        if (!(x >> i)) continue;
        sort(now.begin(), now.end()), zhenghe(now);
        if (xxj[i].first) {
            if (xxj[i].second.size() > now.size()) //优化2
                swap(xxj[i].first, x), swap(xxj[i].second, now);
            for (auto v : xxj[i].second) now.push_back(v);
            x ^= xxj[i].first;
        } else
            return void(xxj[i] = {x, now});
    }
}
```

[提交记录](https://codeforces.com/contest/1427/submission/202599478)

---

## 作者：Celtic (赞：1)

随机化。

考虑 $x$ 的倍数都可以通过二进制来构造出来。我们可以随机一些 $x$ 的倍数，加入 $i$ 后能写下 $1$ 等价于这些数能异或出 $i-1$ 或者 $i+1$。

考虑把随机出来的数加入线性基。每加入一个新数就在线性基出询问能否构造出 $i+1$ 或者 $i-1$，构造也是直接按照线性基的构造来就行。由于线性基如果每一位都有数那么一定可以直接构造，于是这个随机次数不会太大。用满秩矩阵的个数算一下大概是随机 $64$ 个就有 $\frac{1}{3}$ 左右的概率了，于是可以通过。

```cpp
// ubsan: undefined
// accoders
#include<bits/stdc++.h>
#define N 2001001
#define MAX 3505
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=998244353,inf=1e18;
inline void read(ll &ret)
{
	ret=0;char c=getchar();bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll x;
set<ll>st;
vector<ll>v;
ll ans=0;
set<ll>hav;
struct node
{
	ll x,y,z; 
};
vector<node>res;
inline void work(ll y)
{
	ll now=0;
	ll tmp=x;
	for(int i=0;(1ll<<i)*x<=y;i++)
	{
		if((1ll<<i)&(y/x))	
		{
			if(now)
			{
				if(!hav.count(now+tmp))
				{
					ans++;
					res.push_back(node{1ll,now,tmp});
					hav.insert(now+tmp);
				}
				now+=tmp;
			}
			else
				now=tmp;
		}
		if(!hav.count(tmp+tmp))
		{
			ans++;
			res.push_back(node{1ll,tmp,tmp});
			hav.insert(tmp+tmp);
		}
		tmp<<=1;
	}
	return;
}
inline void print()
{
	printf("%lld\n",ans);
	for(auto x:res)
	{
		if(x.x==1)
		    printf("%lld + %lld\n",x.y,x.z);
		 else
		    printf("%lld ^ %lld\n",x.y,x.z);
	}
	return;
}
ll p[N];
inline void ins(ll x)
{
	for(int i=63;i+1;i--)
	{
		if((1ll<<i)&x)
		{
			if(!p[i])
			{
				p[i]=x;
				return;
			}
			else
			{
				if(!hav.count(p[i]^x))
				{
					hav.insert(p[i]^x);
					ans++;
					res.push_back(node{2ll,x,p[i]});
				}
				x^=p[i];
			}
		}
	}
	return;
}
inline bool query(ll x)
{
	for(int i=63;i+1;i--)
	{
		if((1ll<<i)&x)
		{
			if(!p[i])
				return false;
			else
				x^=p[i];
		}
	}
	return true;
}
inline void calc(ll x)
{
	ll tmp=0;
	ll c=x;
	for(int i=63;i+1;i--)
	{
		if((1ll<<i)&x)
		{
			x^=p[i];
			if(!tmp)
			{
				tmp=p[i];
				continue;
			}
			if(!hav.count(tmp^p[i]))
			{
				hav.insert(tmp^p[i]);
				ans++;
				res.push_back(node{2,tmp,p[i]});
			}
			tmp^=p[i];
		}
	}
	return;
}
signed main()
{
	read(x);
	v.push_back(x);
	hav.insert(x);
	mt19937 rnd(1919810);
	while(true)
	{
		ll i=rnd()*x;
		work(i);
		ins(i);
		v.push_back(i);
		for(auto c:v)
		{
			if(query(c+1))
			{
				calc(c+1);
				if(c&1)
				{
					if(!hav.count(c+x))
					{
						ans++;
						hav.insert(c+x);
						res.push_back(node{1ll,c,x});
					}
					if(!hav.count(c+1+x))
					{
						ans++;
						hav.insert(c+1+x);
						res.push_back(node{1ll,c+1,x});
					}
					if(!hav.count((c+x)^(c+1+x)))
					{
						ans++;
						hav.insert((c+x)^(c+1+x));
						res.push_back(node{2ll,c+x,c+1+x});
					}
				}
				else
				{
					if(!hav.count(c^(c+1)))
					{
						ans++;
						hav.insert((c)^(c+1));
						res.push_back(node{2ll,c,c+1});
					}
				}
				print();
				exit(0);
			}
			if(query(c-1))
			{
				work(c),calc(c-1);
				if((c-1)&1)
				{
					if(!hav.count(c-1+x))
					{
						ans++;
						hav.insert(c-1+x);
						res.push_back(node{1ll,c-1,x});
					}
					if(!hav.count(c+x))
					{
						ans++;
						hav.insert(c+x);
						res.push_back(node{1ll,c,x});
					}
					if(!hav.count((c-1+x)^(c+x)))
					{
						ans++;
						hav.insert((c-1+x)^(c+x));
						res.push_back(node{2ll,c-1+x,c+x});
					}
				}
				else
				{
					if(!hav.count((c-1)^c))
					{
						ans++;
						hav.insert((c-1)^(c));
						res.push_back(node{2ll,c-1,c});
					}
				}
				print();
				exit(0);
			}
		}
	}
	exit(0);
}
```

---

