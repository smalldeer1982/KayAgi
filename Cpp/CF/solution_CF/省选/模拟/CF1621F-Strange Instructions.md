# Strange Instructions

## 题目描述

Dasha has $ 10^{100} $ coins. Recently, she found a binary string $ s $ of length $ n $ and some operations that allows to change this string (she can do each operation any number of times):

1. Replace substring 00 of $ s $ by 0 and receive $ a $ coins.
2. Replace substring 11 of $ s $ by 1 and receive $ b $ coins.
3. Remove 0 from any position in $ s $ and pay $ c $ coins.

It turned out that while doing this operations Dasha should follow the rule:

- It is forbidden to do two operations with the same parity in a row. Operations are numbered by integers $ 1 $ - $ 3 $ in the order they are given above.

Please, calculate what is the maximum profit Dasha can get by doing these operations and following this rule.

## 说明/提示

In the first test case one of the optimal sequences of operations is 01101 $ \rightarrow $ 0101 $ \rightarrow $ 011 $ \rightarrow $ 01. This sequence of operations consists of operations $ 2 $ , $ 3 $ and $ 2 $ in this order. It satisfies all rules and gives profit $ 3 $ . It can be shown that it is impossible to achieve higher profit in this test case, so the answer is $ 3 $ .

In the second test case one of the optimal sequences of operations is 110001 $ \rightarrow $ 11001 $ \rightarrow $ 1001 $ \rightarrow $ 101.

In the third test case one of the optimal sequences of operations is 011110 $ \rightarrow $ 01110 $ \rightarrow $ 1110 $ \rightarrow $ 110 $ \rightarrow $ 11 $ \rightarrow $ 1.

## 样例 #1

### 输入

```
3
5 2 2 1
01101
6 4 3 5
110001
6 3 2 1
011110```

### 输出

```
3
11
4```

# 题解

## 作者：Alex_Wei (赞：5)

> [CF1621F Strange Instructions](https://www.luogu.com.cn/problem/CF1621F)。

我们有如下贪心策略：

- 对于操作 $1$，我们消去在两个 $1$ 段之间最短的 $0$ 段的一个 $0$，因为这样可以尽快提供**能够让两个 $1$ 段拼在一起**的操作 $3$ 的机会。
- 在还能进行操作 $2$ 和操作 $1$ 的前提下，我们不会进行操作 $3$。

这两个策略已经足够了。记 $cur$ 表示当前收益，$ans$ 表示答案。

- 如果需要执行操作 $2$：

    - 如果还能执行操作 $2$，就执行。
    - 否则，已经没有操作 $2$ 可以执行，退出。

- 如果需要执行操作 $1$ 或 $3$：

    - 如果还能执行操作 $2$：

        - 如果能执行操作 $1$，那么消去两个 $1$ 段之间最短的 $0$ 段的一个 $0$。若不存在两个 $1$ 段之间的连续两个 $0$，如 $0010100$，那么消去两端的 $0$ 段中的任意一个 $0$。
        - 否则，如果能执行让两个 $1$ 段拼在一起的操作 $3$，则执行，并令可执行操作 $2$ 次数 $+1$。
        - 否则，如果能执行两端的操作 $3$（显然，此时两端各仅有一个 $0$，否则我们可以执行操作 $1$），则执行。
        - 否则，已经没有 $1$ 或操作 $3$ 可以执行，退出。

    - 否则：

        - 如果能执行操作 $1$，尝试**虚拟地**更新答案，即令 $ans\gets \max(ans, cur + a)$。因为执行操作 $1$ 并不会新增可执行的操作 $2$，因此若执行操作 $1$ 则整个过程将在下一步结束。这说明我们应该执行操作 $3$ 维持整个过程。尽管如此，操作 $3$ 的收益 $-c$ 加上操作 $2$ 的收益 $+b$ 可能还没有一个 $+a$ 更优，所以要尝试更新答案。

        - 如果能执行让两个 $1$ 段拼在一起的操作 $3$，则执行。

        - 否则，执行两端的操作 $3$ 不仅没办法增加可执行的操作 $2$ 次数，还会让代价减小，因此我们选择退出。

注意特判 $n = 1$ 以及全 $0$ 的情况。枚举第一步进行操作 $2$ 还是操作 $1 / 3$，时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
const int N = 1e5 + 5;
ll n, a, b, c; char s[N];
int cnt, L, R, one, d[N], e[N];
ll calc(int now) {
	ll p = 1, q = 1, ans = 0, cur = 0;
	cpy(e, d, cnt + 2);
	int tmpL = L, tmpR = R, rest = one;
	while(1) {
		if(now) {
			if(rest == 0) return ans;
			cur += b, rest--;
		} else {
			while(p <= cnt && e[p] == 1) p++;
			if(rest == 0) {
				if(p <= cnt || tmpL > 1 || tmpR > 1) cmax(ans, cur + a);
				if(q < p) rest++, q++, cur -= c;
				else return ans;
			} else {
				if(p <= cnt) e[p]--, cur += a;
				else if(tmpL > 1) tmpL--, cur += a;
				else if(tmpR > 1) tmpR--, cur += a;
				else if(q < p) q++, rest++, cur -= c;
				else if(tmpL) tmpL = 0, cur -= c;
				else if(tmpR) tmpR = 0, cur -= c;
				else return ans;
			}
		} now ^= 1, cmax(ans, cur);
	}
}
void solve() {
	cin >> n >> a >> b >> c >> s + 1;
	cnt = L = R = one = 0;
	for(int i = 1; i <= n; i++) {
		int r = i;
		while(r < n && s[r + 1] == s[i]) r++;
		if(s[i] == '0') {
			if(i == 1) {
				if(r == n) return cout << (n == 1 ? 0 : a) << endl, void();
				L = r - i + 1;
			} else if(r == n) R = r - i + 1;
			else d[++cnt] = r - i + 1;
		} else one += r - i; i = r;
	} sort(d + 1, d + cnt + 1);
	cout << max(calc(0), calc(1)) << endl;
}
int main() {
	int T; cin >> T;
	while(T--) solve();
	return flush(), 0;
}
```

---

## 作者：Cry_For_theMoon (赞：4)

# CF1621F  Strange Instructions

Hello 2022 的难度在我看来是D>F ... 

地理网课的时候摸鱼想了这道题，上课开始想，快下课的时候A掉了（雾）

## 题意：

给定一个长度为 $n$ 的 $01$ 串 $s$，有三种操作：

1. 选择两个连续的 $0$，并删除一个，得分增加 $a$。
2. 选择两个连续的 $1$，并删除一个，得分增加 $b$。
3. 删除一个 $0$，得分减少 $c$。

初始得分为 $0$，允许中间得分出现负数。

此外，必须遵循如下约束：不能连续进行两次奇偶性相同的操作（即一个操作不能连续做两次，不能 $1$ 操作做完立马做 $3$ 操作，也不能 $3$ 操作做完立即做 $1$ 操作）。

试求进行若干次操作（可以不操作）后，得分的可能最大值。

$n\le 10^5,1\le a,b,c\le 10^9$。

## 分析：

### Part 1.

让我们抛开操作 $3$ 来看这个问题。

我们重点关注同一种字符形成的极长段。具体地说，设共有 $s_0$ 个 $0$，$s_1$ 个 $1$；$cnt_0$ 段字符 $0$ 构成的极长段，$cnt_1$ 段字符 $1$ 构成的极长段，那么，我们将能执行 $s_0-cnt_0$ 次 $1$ 操作，$s_1-cnt_1$ 次 $2$ 操作。分别记这个最大操作数为 $x,y$。

由于约束，所以操作序列必定是两种操作交替进行的。我们不妨设第一次操作是 $1$ 操作（第一次是 $2$ 操作的话，就把 $y$ 减去 $1$，最后答案加上 $b$，然后变成了是 $1$ 打头的情况），那么答案将是 
$$
\begin{cases}a(y+1)+by (x\gt y) \\ ay+by(x=y) \\ ax+bx(x\lt y) \end{cases}
$$
这一部分的思考给我们了什么启示？$1,2$ 操作的可执行次数只和 $0$ 和 $1$ 的出现次数，和连续段数目有关。

### Part 2.

我们来考虑加入 $3$ 操作。

**引理：当我们执行一次 $3$ 操作的时候，该位置 $i$ 一定满足 $a_i=0,a_{i-1}=1,a_{i+1}=1(a_0=a_{n+1}=1)$，换言之，该元素所在的 $0$ 段只有它一个数**。

十分显然，考虑反证：如果该段有超过 $1$ 个 $0$，由于 $1,3$ 操作奇偶性相同，所以完全可以把 $3$ 操作替换成 $1$ 操作。

这个引理告诉我们，当我们执行 $3$ 操作的时候，$1$ 操作剩余可执行次数不会变（$s_0$ 少了 $1$，同时 $cnt_0$ 也少了 $1$），而 $cnt_1$ 可能会增加 $1$（如果该元素左右两边都有 $1$ 的话），所以我们发现执行 $3$ 操作的时候，可能会让 $2$ 操作的可执行次数增加 $1$。

我们来分析一下 $3$ 操作到底为什么要执行：

-  让左右两端的 $2$ 合并。（这个是很容易想到的）
-  为了可以多执行几次 $2$ 操作（容易漏掉）

这个第二条，我们举个例子：```111110011111100111111```，注意到这个串只能执行 $2$ 次 $1$ 操作，但可以执行很多次 $2$ 操作。如果 $c$ 很小而 $b$ 很大，我们完全可以构造出这样的操作序列：```12123232```，使得答案最大。

我们继续思考，如果第一种目的不存在，就是说，如果我们仅仅为了多执行几次 $2$ 操作而去执行 $3$ 操作，忽略掉可能产生的新的 $2$ 操作执行次数（换言之，如果 ```101``` 我们删了 $0$，当作没看见，左右两个 ```1``` 还是分开，不合并），这种情况下，我们能否利用总字符数量，和连续段数来得到答案。

直觉告诉我们这个应该不难，因为 $2$ 操作的可操作次数不会忽然又增加了，那样会很麻烦。我们假设这个是可以的（后面我将展示大分类讨论解决这个问题）。

好，那么我们只用考虑 $3$ 操作的第一种，这样的目的是增加 $2$ 操作的次数，那就是因为 $2$ 操作次数比较少。因为比较少，我们要尽可能早的增加 $2$ 操作的次数。因为要尽可能早地增加它的次数，所以我们把所有 $0$ 构成的极长段（注意去掉两边的）排序。然后暴力枚举消灭前 $k$ 个极长段。

还是不妨假设第一次执行奇数编号的操作，那么设我们可以执行 $x$ 次奇数编号的操作（$cnt_0$）和 $y$ 次偶数编号的操作（$s_1-cnt_1$），那么每次我们要新消除一个 长度为 $len$ 的 $0$ 连续段时，$x$ 应该减小 $len$，$y$ 应该减小 $(len-1)$，然后判断合法性。这个合法性的判断也有点讲究，因为注意到，我们按照奇数操作在消除哪个段来对操作划分阶段，那么会发现每个阶段的最后都是偶数操作结尾的，又因为开头确定是奇数操作开头的，所以操作的奇偶一定是“奇-偶-奇-偶-...-奇-偶”这样的。那么可以大概写出这样的代码：

```cpp
    
	ll op=s1-cnt1,sum=0; //op是上文的y
    rep(i,0,len){
        sum+=arr[i];op++; //len是去掉两边的连续段以后的连续段数目，arr[i]表示当前段长度
        if(op<sum)break;
        //update answer 
    }  
```

这里的 ```update answer```，就是我们下文要进行打分类讨论的部分。它的前置约束是我们忽略所有由于 $3$ 操作新产生的 $2$ 操作的执行次数，因为我们上面的循环就是来考虑这个东西的。

### Part 3.

在 $3$ 操作不会影响到 $2$ 操作以后，整个问题逐渐变得 naive 起来...

在上面的循环中，每次 ```update answer``` 的时候，我们将有 $s_0-sum$ 个 $0$，$cnt_0-i$ 个 $0$ 连续段，$op$ 次执行 $2$ 操作的机会。

那么我们要多次解决这样一个问题：给定 $x,y,z$，至多可以执行 $x-y$ 次 $1$ 操作，$y$ 次 $3$ 操作，$z$ 次执行操作 $2$ ，第一次操作必须是 $1/3$ 操作，问最大得分。（这里的操作是抽象的，就是当我们执行某个操作的时候只会更改得分，不再关注字符串会变成啥了，这也是上文多次提到的让 $3$ 操作不再影响到 $2$​ 操作的意思）。

请欣赏分类讨论：

- 当 $x-y\gt z$ 的时候，答案为 $(x-y+z)\times(a+b)+a$。
- 否则当 $x-y=z$ 的时候，答案为 $(x-y+z)\times (a+b)。$

- 否则当 $c\ge b$ 的时候，答案为 $(x-y)\times(a+b)$。
- 否则，说明 $c\lt b$ 了，当 $x\ge z$ 的时候，答案为 $(x-y)\times a+z\times b-(z-x+y)\times c$。
- 否则，答案为 $(x-y)\times a+x\times b-y\times c$。

这样可以单次 $O(1)$ 解决这个问题，那么整个问题就可以 $O(n\log n)$​ 解决，瓶颈在排序，事实上利用桶排可以线性...

## 代码：

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10;
ll T,n,a,b,c,ans,tot,s0,s1,cnt0,cnt1;
array<int,2>d[MAXN];
int arr[MAXN],len;
string s;
void upd(ll& x,ll y){x=max(x,y);}
ll calc(ll s0,ll op1,ll cnt0){
    ll op0=s0-cnt0;
    if(op0>op1)return (a+b)*op1+a;
    if(op0==op1)return (a+b)*op1;
    if(c>=b)return (a+b)*op0;
    if(s0>=op1)return a*op0+b*op1-c*(op1-op0);
    return a*op0+b*s0-c*cnt0;
}
void solve(){
    cin>>n>>a>>b>>c>>s;
    s=" "+s;
    ans=tot=0;int cnt=1;
    s0=s1=cnt0=cnt1=0;
    rep(i,2,n){
        if(s[i]!=s[i-1]){
            d[++tot]={cnt,s[i-1]-'0'};
            cnt=1;
        }else cnt++;
    }
    d[++tot]={cnt,s[n]-'0'};
    if(tot==1){
        if(d[1][0]>1){
            if(d[1][1]==0)cout<<a<<endl;
            else cout<<b<<endl;
        }else cout<<0<<endl;
        return;
    }
    len=0;
    rep(i,2,tot-1)if(d[i][1]==0)arr[++len]=d[i][0];
    sort(arr+1,arr+1+len);
    rep(i,1,n)if(s[i]=='0')s0++;else s1++;
    rep(i,1,tot)if(d[i][1]==0)cnt0++;else cnt1++;

    upd(ans,calc(s0,s1-cnt1,cnt0));
    if(s1-cnt1>0)upd(ans,b+calc(s0,s1-cnt1-1,cnt0));

    ll op=s1-cnt1,sum=0;
    rep(i,1,len){
        sum+=arr[i];op++;
        if(op<sum)break;
        upd(ans,a*(sum-i)+b*sum-c*i+calc(s0-sum,op-sum,cnt0-i));
    }  
    if(s1==cnt1){cout<<ans<<endl;return;}

    op=s1-cnt1-1,sum=0;
    rep(i,1,len){
        sum+=arr[i];op++;
        if(op<sum)break;
        upd(ans,b+a*(sum-i)+b*sum-c*i+calc(s0-sum,op-sum,cnt0-i));
    }  
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--)solve();

    return 0;
}
```



---

## 作者：MiniLong (赞：0)

先把连续两个 $0$ 和 $1$ 的个数找出来，分别是 $x,y$。然后分讨一下，记 $cnt_0,cnt_1$ 为总 $0,1$ 的个数。

- $x<y$

显然操作序列肯定是形如 $2121\cdots21(232323)2$，括号处取到当且仅当 $b>c$。当取完连续两个 $0$ 后序列一定长成若干个 $1$ 连着一个 $0$ 再有若干个 $1$，那就把首位的 $0$ 去掉剩下 $t$ 个 $0$，那么当 $b>c$ 时显然可以把这 $t$ 个 $0$ 都删掉，此时剩下的 $y$ 不会变，还会剩下首位的 $0$ 能取就取就行。所以答案是 $x \times (a+b) + \max(0,b-c) \times (t+\min(y-x-1,cnt_0 - t)) + b$。

- $x\ge y$

操作序列是形如 $1212\cdots 12(323232)[1]$，小括号取到当且仅当 $b>c$，中括号取到当且仅当 $x>y$。考虑小括号中最多取到多少个 $32$，那把相邻两个 $1$ 中间的 $0$ 个数统计出来，去掉 $0$ 的，把剩下的排序。在前 $y$ 次 $12$ 操作中可以尽量把中间连续的 $0$ 变成一个 $0$，即设连续长度为 $cnt_1 \le cnt_2\le \cdots \le cnt_k$，从头开始取 $cnt_i - 1$ 贪心能取就取即可，设最多把 $t$ 个 $cnt_1$ 变成 $1$，答案即 $y \times (a+b) + \max(0,b-c) \times t + [x>y]a$。

复杂度 $\Theta(n\log n)$，在于排序。

---

## 作者：Little09 (赞：0)

分讨题。

假设相邻的 $0$ 有 $x_0$ 对，相邻的 $1$ 有 $x_1$ 对。考虑一个贪心的事实：我们肯定交替进行 $1,2$ 操作，直到 $x_0$ 或 $x_1$ 有一个降到了 $0$。接下来如果 $c<b$，我们可以用一次 $3$ 操作的代价换取一次 $2$ 操作。但是你会感觉这个东西的量谁多谁少好像很多情况，那就讨论一下。

- $x_0=x_1$

这种情况最后一定会形成一个 $01$ 交替的序列（或空序列）。假设 $0$ 有 $x$ 个，$1$ 有 $y$ 个。如果 $c\ge b$，就啥也不干了；否则当 $y>0$ 时，可以进行 $y-1$ 次 $3,2$ 的交替操作。这样显然是最优的。

- $x_0>x_1$

最后的序列是有一些单独的 $1$ 分割开的 $0$ 段，形如 $00..0100..0100..0100..0$。不过这个最终序列的形态不是唯一的，只要满足 $01$ 段数不变，$0$ 的位置可以任意挪动。

如果 $c\ge b$，就再删一组 $00$ 就可以了；否则我们应该反复执行 $3,2$ 操作，最后再删一组 $00$。但是 $3$ 操作要求存在一个不在两端的 $0$ 连续段只有一个元素，假设有 $s$ 个这样的段，那么就可以进行 $s$ 次 $3,2$ 操作。为了最大化 $s$，我们在第一步删 $00$ 的时候就要先选 $0$ 少的段删就行了。这里需要一个排序。

- $x_0<x_1$

最后的序列是有一些单独的 $0$ 分割开的 $1$ 段，形如 $11..1011..1011..1011..1$。

我们无论怎样都要先删一组 $11$，因为这样一定不劣，还可以把交替操作给到删 $0$。如果 $c\ge b$，就啥也不用干了；否则我们应该反复执行 $3,2$ 操作。可以算一下最多还能进行几组 $3,2$ 操作：假设还有 $x$ 个 $1$ 和 $y$ 个 $0$，那么考虑显然的上界是 $\min(\max(x-1,0),y)$，因为每次 $3$ 操作要消耗一个 $0$，$2$ 操作在有至少两个 $1$ 的时候要消耗一个 $1$。这个上界也是容易取到的。如果某次消耗完 $0$ 但找不到 $11$，那么一定存在 $101$，那么上一次可以消耗这个 $0$。

```cpp
void work()
{
	cin >> n >> a >> b >> c;
	int s0=0,s1=0;
	for (int i=1;i<=n;i++)
	{
		char x;
		cin >> x;
		s[i]=x-'0';
		if (s[i]==1) s1++;
		else s0++;
	}
	int x1=0,x0=0;
	for (int i=2;i<=n;i++)
	{
		if (s[i]==s[i-1])
		{
			if (s[i]==1) x1++;
			else x0++;
		}
	}
	if (x1==x0)
	{
		ll x=s0-x0,y=s1-x1;
		ll ans=(a+b)*x0;
		if (c>=b)
		{
			cout << ans << endl;
			return;
		}
		ll g=b-c;
		ans+=max(y-1,0ll)*g;
		cout << ans << endl;
		return;
	}
	else if (x0>x1)
	{
		ll ans=(a+b)*x1;
		if (c>=b)
		{
			cout << ans+a << endl;
			return;
		}
		cnt=0;
		ll lst=-n-1;
		for (int i=1;i<=n;i++)
		{
			if (s[i]==0) lst++;
			else 
			{
				if (lst>0) d[++cnt]=lst;
				lst=0;
			}
		}
		sort(d+1,d+cnt+1);
		ll sum=x1,tot=0;
		for (int i=1;i<=cnt;i++)
		{
			if (d[i]-1<=sum)
			{
				sum-=(d[i]-1);
				tot++;
			}
			else break;
		}
		ll g=b-c;
		ans+=tot*g+a;
		cout << ans << endl;
		return;
	}
	else
	{
		ll ans=(a+b)*x0;
		if (c>=b)
		{
			cout << ans+b << endl;
			return;
		}
		s0-=x0,s1-=x0+1;
		ll tot=min(max(s1-1,0),s0);
		ll g=b-c;
		ans+=tot*g;
		cout << ans+b << endl;
	}
}
```

因为是赛时，代码有点冗长。但是应该是可以阅读的。

这道题可能不是一道很 OI 的题，也没那么有趣。不过我们也需要这样的讨论题来训练，减少讨论的错漏和粗心程度。在保证正确性的情况下加快思考速度和代码速度。


---

