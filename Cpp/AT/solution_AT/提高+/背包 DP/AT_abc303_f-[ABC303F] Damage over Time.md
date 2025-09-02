# [ABC303F] Damage over Time

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc303/tasks/abc303_f

あなたの前に体力 $ H $ のモンスターが現れ、ターン制の戦闘が開始しました。

あなたは、ターン $ 1,2,… $ のそれぞれに呪文 $ 1,…,N $ の $ N $ 種類の呪文のうち一つを唱えます。

ターン $ i $ に呪文 $ j $ を唱えると、その呪文の効果としてターン $ i,i+1,…,i+t_j\ －1 $ のそれぞれでモンスターの体力が $ d_j $ 減ります。

モンスターの体力を $ 0 $ 以下にすることが可能な最も早いターンを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ H\ \leq\ 10^{18} $
- $ 1\ \leq\ t_i,d_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

以下のようにするとターン $ 6 $ にモンスターの体力を $ 0 $ 以下に出来ます。これが最も早いターンです。 - ターン $ 1 $ に魔法 $ 1 $ を使う。ターン $ 1 $ に使った魔法の効果でモンスターの体力が $ 2 $ 減り、$ 18 $ になる。 - ターン $ 2 $ に魔法 $ 2 $ を使う。ターン $ 1,2 $ に使った魔法の効果でモンスターの体力が $ 2+1=3 $ 減り、$ 15 $ になる。 - ターン $ 3 $ に魔法 $ 1 $ を使う。ターン $ 2,3 $ に使った魔法の効果でモンスターの体力が $ 1+2=3 $ 減り、$ 12 $ になる。 - ターン $ 4 $ に魔法 $ 2 $ を使う。ターン $ 2,3,4 $ に使った魔法の効果でモンスターの体力が $ 1+2+1=4 $ 減り、$ 8 $ になる。 - ターン $ 5 $ に魔法 $ 1 $ を使う。ターン $ 2,4,5 $ に使った魔法の効果でモンスターの体力が $ 1+1+2=4 $ 減り、$ 4 $ になる。 - ターン $ 6 $ に魔法 $ 2 $ を使う。ターン $ 2,4,5,6 $ に使った魔法の効果でモンスターの体力が $ 1+1+2+1=5 $ 減り、$ -1 $ になる。

## 样例 #1

### 输入

```
2 20
2 2
5 1```

### 输出

```
6```

## 样例 #2

### 输入

```
10 200
1 21
1 1
1 1
8 4
30 1
3 1
10 2
8 1
9 1
4 4```

### 输出

```
9```

# 题解

## 作者：_•́へ•́╬_ (赞：17)

吐槽一下，kenkooooooooooooo 上这个题的难度不是这场最高的，但是 solve time 最长。

赛时一直写到结束才过。真麻烦。

注意别把 `i+1` 打成 `i`。

## 思路

考虑二分答案。

对于一个时刻，我能够知道在该时刻使用的咒语至多生效多长时间，记为 $x$。

- 对于生效时长 $t\leq x$ 的，可以打满伤害 $t\times d$。
- 对于 $t\geq x$ 的，不能打满伤害，应按照其 dps $d$ 贪心。

自然地，按 $t$ 排序，统计前缀最大值和后缀最大值。

然后贪心每个时刻所能打出的最大伤害。

不能每个时刻都跑，要把相邻两个 $t$ 之间的时间一起计算，而这一段时间中有两种策略，分别对应一个零次函数（第一种）和一个一次函数（第二种，总伤害与时刻有关），故取最大值有三种可能，分别处理即可。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#define int long long
#define N 300009
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,h,l,r,mid,pfx[N],sfx[N];
struct node
{
	int t,d;
	inline bool operator<(const node&kkk)const{return t<kkk.t;}
}a[N];
inline bool jg()
{
	__int128 x=h,now=mid;
	for(int i=n-1;i>=0;--i)if(now>a[i].t)
	{
		if(sfx[i+1]*now<=pfx[i])
		{
			x-=pfx[i]*(now-a[i].t);now=a[i].t;
			continue;
		}
		if(sfx[i+1]*(__int128)(a[i].t+1)>=pfx[i])
		{
			x-=sfx[i+1]*(a[i].t+1+now)*(now-a[i].t)/2;now=a[i].t;
			continue;
		}
		int u=pfx[i]/sfx[i+1];
		x-=sfx[i+1]*(u+1+now)*(now-u)/2+pfx[i]*(u-a[i].t);
		now=a[i].t;
	}
	x-=sfx[0]*(1+now)*(now)/2;
	return x<=0;
}
main()
{
	read(n);read(h);l=1;r=h;
	for(int i=0;i<n;read(a[i].t),read(a[i++].d));
	sort(a,a+n);
	for(int i=0;i<n;++i)pfx[i]=max((i?pfx[i-1]:0),a[i].t*a[i].d);
	for(int i=n-1;i>=0;--i)sfx[i]=max(sfx[i+1],a[i].d);
	for(;l<=r;)
	{
		mid=l+r>>1;
		if(jg())r=mid-1;
		else l=mid+1;
	}
	printf("%lld",l);
}
```

---

## 作者：Assembly_line (赞：5)

贪心地想，我们选 $\max(d_i\times t_i)$ 肯定是最优的，因为这样可以打出最高的伤害。

有一种情况：当我们快把怪兽打完时，其实有时选 $d_i$ 大的反而优，这是因为选 $\max(d_i\times t_i)$ 时，可能这个技能时间打不完游戏已经结束了。

怎么判断何时打完怪兽呢？容易想到可以二分答案，然后把两种情况分开考虑。设当前的时间为 $j$，二分的答案为 $k$。

- $j+t_i-1\le k$。即这个技能可以打完全部时间，那么我们就找 $\max(d_i\times t_i)$。

- $j+t_i-1>k$。即这个技能打不完全部时间，那么答案就是 $d_i\times (k-j+1)$，找 $\max(d_i)$。

发现两种情况之间的转换只有可能是第一种情况转换为第二种情况，而转换的顺序是按照 $t_i$ 由大到小的顺序，所以我们排序，维护前缀最大 $d_i\times t_i$ 和后缀最大 $d_i$。

相邻的两个技能之间的时间段的情况是一样的，要一起处理了。

在两种情况中取最大值时，我们解一个不等式得到两种情况分别取的范围，有三种情况，判断一下即可。

时间复杂度 $O(n\log V)$。

```cpp
#include<bits/stdc++.h>
#define ll __int128
const ll inf=1e18;
using namespace std;
int n;
ll h;
struct node{
	ll t,d;
}a[300003];
bool cmp(node x,node y){return x.t<y.t;}
ll maxn[300003],maxx;
ll read(){char ch=getchar();ll cnt=0;while(ch<'0'||ch>'9')ch=getchar();while(ch>='0'&&ch<='9')cnt=(cnt<<3)+(cnt<<1)+ch-'0',ch=getchar();return cnt;}
void write(ll x){if(!x)return;write(x/10),putchar(x%10+'0');}
bool check(ll k)
{
	ll maxx=-inf,l=1,r,i=n,ans=0;
	for(;i>=1;i--)
	{
		if(a[i].t>k)maxx=max(maxx,a[i].d);
		else break;
	}
	for(;i>=1;i--)
	{
		r=k-a[i].t+1;
		if(maxx==-inf)ans+=(r-l+1)*maxn[i];
		else
		{
			ll p=maxn[i]/maxx,xr=k-l+1,xl=k-r+1;
			if(maxn[i]%maxx!=0)p++;
			if(p<=xl)ans+=maxx*(xl+xr)*(xr-xl+1)/2;
			else if(p>xr)ans+=maxn[i]*(xr-xl+1);
			else
			{
				ans+=maxx*(xr-p+1)*(xr+p)/2;
				ans+=maxn[i]*(p-xl);
			}
		}
		while(i>1&&a[i].t==a[i-1].t)maxx=max(maxx,a[i].d),i--;
		maxx=max(maxx,a[i].d);
		l=r+1;
	}
	ans+=maxx*(k-l+2)*(k-l+1)/2;
	return ans>=h;
}
int main()
{
	n=read(),h=read();
	for(int i=1;i<=n;i++)a[i].t=read(),a[i].d=read();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)maxn[i]=max(maxn[i-1],a[i].t*a[i].d);
	ll l=1,r=1e18,ans;
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	write(ans);
	return 0;
}
```

---

## 作者：panzhouao (赞：2)

## 分析
记技能种类数为  $n$ ，第 $i$ 种技能的属性是 $t_{i}$，$d_{i}$（详见题目）， $t$ 时刻怪兽的血量为 $H_i$，认为 $H_0$ 为怪兽初始血量。

首先考虑使用第 $i$ 种技能后，经过 $t$ 回合（时间）后对怪兽造成的总伤害，记为 $D_{i,t}$，可知 $D_{i,t} = min\{t+1,t_{i}\} \cdot d_{i}$，图像如下：

![picture1](https://cdn.luogu.com.cn/upload/image_hosting/wk5hih2g.png)

记当前时间为 $T$，由于每个时刻都要使用一次技能，$t$ 时刻使用的技能 $i$ 造成的伤害为 $D_{i,T-t}$，可知从 $1$ 时刻至 $T$ 时刻怪兽受到总伤害为 $\overset{T}{\underset{i=1}{\sum}} D_{C_i,T-i} \lparen C_i \in \{0,1,2,\dots,n\} \rparen$，即 $\overset{T-1}{\underset{i=0}{\sum}} D_{C_i,i}\lparen C_i \in \{0,1,2,\dots,n\} \rparen$，其中 $C$ 表示第 $i$ 时刻选择第 $C_i$ 种技能（此处可理解为从最后一个时刻开始倒序计算伤害）。

对于每个 $i$，必存在一个 $k$，使得 $D_{k,i}$ 最大，从 $i=0$ 开始贪心地选取这样的 $k$，在 $T-i$ 时刻用第 $k$ 种方法攻击怪兽，就可使得 $H_i$ 取得最小值，从而最快地使怪兽血量不高于 $0$。

关键是如何找出使 $D_{k,i}$ 最大的 $k$。

考虑上方的图像，若把所有技能的图像画在一起，大致如下：

![picture2](https://cdn.luogu.com.cn/upload/image_hosting/umo09fir.png)

对于每个 $t$，最大伤害如红线所示。

首先，对于 $2$ 个技能 $a$ 、$b$（ $a$ 、$b$ 均为下标），容易发现
1. 若 $d_a < d_b$ 且 $ d_a \cdotp t_a < d_b \cdotp t_b$，则 $D_{a,i} < D_{b,i}$。（看图更直观）

2. 若 $d_a \le d_b $ 且 $ d_a \cdotp t_a \ge d_b \cdotp t_b$，则 $D_{a,i} \ge D_{b,i} (i=\lceil \dfrac{d_b \cdotp t_b}{d_a} \rceil, \lceil \dfrac{d_b \cdotp t_b}{d_a} \rceil + 1,\dots)$ 且 $D_{a,i} \le D_{b,i} (i=1,2,\dots,\lceil \dfrac{d_b \cdotp t_b}{d_a} \rceil-1)$。（同样，看图更直观，这两个结论都是从图中发现的）

此时若按照 $d$ 升序对技能排序，综合以上结论可知：
若两个技能 $a$ 、$b$ （$a$ 、$b$ 均为下标）能使 $D$ 最大，靠前的技能使 $D$ 最大的范围更靠前。于是，用如上 2. 的结论对两个连续的技能使 $D$ 最大的范围进行分段，即可对于每个 $t$ 求出 $D_{i,t}$ 的最大值 $D_{max, t}$。

其次，每一段分出的 $D_{max}$ 必为一段等差数列后加一段常数数列，能够在 $O(1)$ 复杂度内求出总和，可按以下顺序处理：
1. 若本段是最后一段，可分类讨论，求出该段中第一个使血量不大于 $0$ 的时间（由于后方有无限的时间，故总可在本段处理完），复杂度 $O(\log n)$（此处我使用二分求解等差数列段的第一个使血量不大于 $0$ 的时间）；
2. 否则可求出这段 $D_{max}$ 的总和 $S$，若怪兽受到该段之前所有段的伤害后血量小于或等于 $S$，就可分类讨论，求出该段中第一个使血量不大于 $0$ 的时间；
3. 若怪兽受到该段之前所有段的伤害后血量大于 $S$，那么把血量减去 $S$，交给下一段处理。

总复杂度 $O(n \log n)$。

注意这种方法在运算过程中数据可能达到 $10^{24}$，需要用 `__int128` 存储过程数据。

## 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;

#define int __int128

const int N = 3e5+5;

struct S {
    long long d,t;    
} A[N], tmp[N];

// 文中所述的排序方法
bool cmp(const S& a, const S& b) {
    return a.d == b.d ? a.t > b.t : a.d > b.d;
}

int n,H;

int rangeL[N]; //区域左边界，第i段右边界为rangeL[i+1]-1
int rangeI[N]; //区域取得最大值的技能的下标

int calc(int i, int t) {
    return min(t, (__int128)(A[i].t))*A[i].d;
}

// 二分求解等差数列段第一个使血量不大于 0 的时间
int erfen(int r1, int d, int l, int h, int R) {
    int L = l-1;
    while (L < R) {
        int t = (L+R-1)>>1;
        if ((r1+t*d)*(t+1-l)/2 == h) {
            return t;
        } else if ((r1+t*d)*(t+1-l)/2 < h) {
            L = t+1;
        } else {
            R = t;
        }
    }
    return R;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
  	  
    // __int128 无法直接IO，要用 long long 代替
    long long nn,hh;
    cin >> nn >> hh;
    H=hh;
    n=nn;
  
    for (int i = 0; i < n; i++) cin >> A[i].t >> A[i].d;
    // 文中所述的排序  
    sort(A, A+n, cmp);
    
    
    // 文中所述的求区间
    int maxEnd = 0, idx=0;
    for (int i = 0; i < n; i++)
    {
        if (maxEnd > A[i].t*A[i].d) continue;
        rangeI[idx]=i;
        rangeL[idx]=maxEnd/A[i].d+1;
        idx++;
        maxEnd=__int128(A[i].t)*A[i].d;
    }
    rangeL[0]=1;
    rangeL[idx] = LLONG_MAX;
  
    // 文中所述的处理
    for (int i = 0; i < idx && H > 0; i++) {
        int l = rangeL[i], r = rangeL[i+1]-1, ID = rangeI[i];
        int ed1 = A[ID].t;
        int r1 = calc(ID, l), r2 = calc(ID, ed1), sum1;
        
        // 当心点求值，会炸
        if ((r1+r2)&1) {
            sum1=__int128(ed1-l+1)/2*(r1+r2);
        } else {
            sum1=__int128(r1+r2)/2*(ed1-l+1);
        }
      	// 正好在等差数列段后结束
        if (H == sum1) {
            cout << (long long)(ed1) << endl;
            return 0;
        } else if (H < sum1) {
            // 在等差数列段内结束，二分求值
            cout << (long long)(erfen(r1, __int128(A[ID].d), l, H, ed1)) << endl;
            return 0;
        } else {
            // 常数数列段
            H -= sum1;
            
            // 最后一段
            if (r == LLONG_MAX-1) {
                cout << (long long)(ed1 + (H+r2-1)/r2) << endl;
                return 0;
            }
            
            // 正好在常数数列段后结束
            if (H == (r-ed1)*(r2)) {
                cout << (long long)(r) << endl;
                return 0;
            } else if (H < (r-ed1)*(r2)) {
            // 在常数数列段内结束， O(1) 求值
                cout << (long long)(ed1 + (H+r2-1)/r2) << endl;
                return 0;
            } else {
            // 不在本段结束， 交给下一段求解
                H -= (r-ed1)*(r2);
            }
        }
    }
    cout << flush;
    return 0;
}
```

---

## 作者：Kylin_ZHH (赞：2)

初看此题，对于怎么选择技能感觉比较棘手，原因在于技能是持续伤害而不是一次性的。比如一个技能持续伤害10回，但可能5回合后怪物就死了，这样该技能实际伤害量只有一半。因此在考虑选择技能的时候不能仅考虑 $t_i \times d_i$ 的值。尽管如此，对于如何选取技能仍没有头绪。

细想上述的棘手点，因为持续回合不确定，导致选择的技能实际造成的伤害是不确定的。如果我们确定了一个持续回合，比如我就打 $x$ 回合，然后看怪物的血量是否变为 $0$ 或以下，那么，假设当前是第 $i$ 轮的话， 我用什么技能，其实际造成的伤害是确定的，此时那我肯定是贪心地选择造成伤害最大的一个技能。

因此可以枚举持续的回合数 $x$，然后从第一回合考虑依次使用什么技能。但因为回合数最多高达 $10^{18}$，因此不能枚举。但注意到回合数与怪物剩余血量之间存在单调性，因此我们可以二分这个回合数，然后计算一下怪物的血量能否变为$0$ 或以下。

假设枚举的回合数为 $x$，当前处在第 $i$ 回合，也就是说接下来使用的技能伤害最多持续 $t = x - i + 1$ 回合。我们考虑使用什么技能。

根据技能生效的回合数 $t_i$ 与 $d$ 的关系，可以将技能分成两类：

剩余回合能完整造成伤害的，即造成伤害数为 $t_i \times d_i$（即 $t_i \leq t$）
剩余回合不能完整造成伤害的，即造成伤害数为 $t \times d_i$（即 $t_i > t$）
将技能按照 $t_i$ 升序排序，前一类是 $t_i \leq t$，我们预处理一个关于 $t_i \times d_i$ 的前缀最大值。后一类因为 $t$ 是固定的，因此就要找一个满足 $t_i > t$ 最大的 $d_i$，因此再处理一个关于 $d_i$ 的后缀最大值。

对于当前回合使用的技能，就取这两类技能中造成伤害值较大的那个。

由于回合数高达 $10^{18}$，一回合一回合考虑会超时，因此考虑能否多回合地考虑。

如果此时伤害值较大的第一类技能，那么包括这回合之后的回合，我们肯定是一直使用这个技能（因为它始终是第一类技能（能完整造成伤害）中伤害最大的，而第二类技能的伤害会随着 $t$ 减少而更少，不会比第一类伤害值大），直到剩下的回合数不足以该技能完整造成伤害，再重新考虑，即持续使用 $cnt = t - t_i + 1$ 次，造成 $cnt \times t_i \times d_i$ 的伤害。之后该技能变成了第二类。

而如果伤害值较大的是第二类技能，那么包括这回合之后的回合，我们还是一直使用这个技能（因为它始终是第二类技能（不能完整造成伤害）中伤害最大的），但由于随着不断的使用，其造成的伤害会越来越少（剩余回合 $t$ 不断变小），因此直到其伤害值小于第一类技能的最大值，再重新考虑，即持续使用 $cnt = t - \lfloor \frac{max_1}{d_i} \rfloor$ 次，造成 $d_{max} \times (t + t - 1 + t - 2 + \cdots + t - cnt + 1) = d_{max} \times \frac{(t + t - cnt + 1)cnt}{2}$ 伤害。其中 $max_1$ 是第一类技能造成伤害的最大值。

这样每个技能最多考虑两次（一次第一类，一次第二类），因此验证的复杂度为$O(n)$。

总的时间复杂度就是 $O(n\log n)$

由于回合数有 $O(10^{18})$，技能总伤害也有 $O(10^{18})$，验证时可能会超 long long 范围，因此得开 __int128。

看看代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main(void) {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n;
    LL h;
    cin >> n >> h;
    vector<array<LL, 3>> spell(n); // t * d, t, d
    for(auto &i : spell){
        cin >> i[1] >> i[2];
        i[0] = i[1] * i[2];
        i[1] = -i[1];
    }
    sort(spell.begin(), spell.end(), [](const auto& a, const auto&b){
            return a[1] > b[1]; // t, small first
        });
    vector<array<LL, 3>> premax(n);
    premax[0] = spell[0];
    for(int i = 1; i < n; ++ i){
        premax[i] = max(premax[i - 1], spell[i]);
    }
    auto check = [&](LL x){
        int pos = n - 1;
        __int128 cur = h;
        LL sufmax = 0;
        while(cur > 0 && x > 0){
            while(pos >= 0 && -premax[pos][1] > x){
                sufmax = max(sufmax, spell[pos][2]);
                -- pos;
            }
            if (pos < 0 || premax[pos][0] < __int128(1) * sufmax * x){
                __int128 down = 0;
                if (pos >= 0)
                    down = premax[pos][0] / sufmax;
                __int128 cnt = x - down;
                __int128 sum = cnt * (x - cnt + 1 + x) / 2 * sufmax;
                cur -= sum;
                x -= cnt;
            }else{
                __int128 cnt = x - -premax[pos][1] + 1;
                cur -= cnt * premax[pos][0];
                x -= cnt;
            }
        }
        return cur <= 0;

    };
    LL l = 0, r = 1e18;
    while(l + 1 < r){
        LL mid = (l + r) >> 1;
        if (check(mid))
            r = mid;
        else 
            l = mid;
    }
    cout << r << '\n';

    return 0;
}
```


---

## 作者：dengchengyu (赞：1)

## abc303_f

首先考虑二分答案，然后在时间 $j$ 用 $i$ 方式攻击的贡献就确定了，我们要判断以最优方式攻击的贡献和是否不小于 $H$。

考虑把攻击方式按 $t_i$ 排序，我们依次确定时间为 $t_i\sim t_{i+1}$ 这一段以最优方式攻击的贡献和。

那么对于 $j\le i$ 的攻击方式，一个时间的贡献就是 $\max\{t_j\times d_j\}$。
而对于 $j>i$ 的攻击方式，时间 $k$ 的贡献就是 $k\times \max\{d_j\}$。

在每个段，我们可以 $O(1)$ 计算一个分界点，分界点前以 $j\le i$ 的作为攻击方式更优，分界点后以 $j>i$ 的作为攻击方式更优。
具体地，就是解
$$
x\times \max_{j>i}\{d_j\}>\max_{j\le i}\{t_j\times d_j\}
$$
细节：我们可以插入一个 $t=1,d=0$ 的攻击方式，可以方便实现。check 时需要注意特判 $mid$ 的边界，同时记得开 `__int128`。

时间复杂度 $O(n\log V)$。

AC 代码：

```cpp
const int N=3e5+5;
ll h;
int n;
pair<int,int> a[N];
int mx[N];
int check(ll x){
	it128 sum=0;
	ll Max=0;
	fo(i,1,n){
		Max=max(Max,(ll)a[i].first*a[i].second);
		if(a[i].first>x)break;
		if(a[i].first!=a[i+1].first){
			if(i==n)sum+=(it128)(x-a[i].first+1)*Max;
			else {
				ll t=floor((ld)Max/mx[i+1]);
				if(t<a[i].first)t=a[i].first-1;
				if(t>=a[i+1].first)t=a[i+1].first-1;
				if(t>=x){
					sum+=(it128)(x-a[i].first+1)*Max;
					break;
				}
				sum+=(it128)(t-a[i].first+1)*Max;
				int up=a[i+1].first;
				if(up>x)up=x+1;
				sum+=(it128)(t+up)*(up-t-1)/2*mx[i+1];
			}
		}
	}
	return sum>=h;
}
signed main(){
	read(n,h);
	fo(i,1,n)read(a[i].first,a[i].second);
	++n;
	a[n]={1,0};
	sort(a+1,a+1+n);
	fd(i,n,1)mx[i]=max(mx[i+1],a[i].second);
	ll l=1,r=1e18,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	write(ans);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

马上都是老年退役选手了，还在做蓝题。/cf

因为每一招可以重复使用，所以肯定会贪心的选最优的。如果时间一样，单位伤害小的可以舍去；如果单位伤害一样，时间短的可以舍去。另一种贪心的方法是每次选总伤害最大的招。

不过总伤害大可能建立在时间超长的基础上。比如你有有两种操作：伤害为 $1$，持续 $998244353$ 秒；伤害为 $998244352$，持续 $1$ 秒。如果你来一个血量为 $998244353$ 的怪物，显然来两个招数二可以更快解决问题。

于是你可以考虑在开始的时候使用总伤害较大的，在后面使用见效快的。

不过这个“见效快”没有具体的定义。

我们考虑倒着做。如果知道离最后一句的时间是 $T$，那么目前能产生的伤害就是 $d_i \times \min\{T,t_i\}$，这是一个可量化的指标。

而 $\min \{T,t_i\}$ 到底是哪一个需要将 $t$ 排序。对于 $t_i < T$ 的操作，我们当然要选 $d_i \times t_i$ 最大的；否则要选择 $d_i$ 最大的，乘上 $T$。于是我们挨个枚举 $T$ 所在的区间即可。

注意每个区间内都有可能会有两种情况。所以最终最优伤害应该是一段平的加上等差数列。

如果等差数列啥时候会超过 $H$，要么解二次方程，这样处理答案时你是线性的，但是我太懒了，懒得管 Corner case。你直接二分答案就可以了，反正排序带 log，这里不是瓶颈。

总的复杂度为 $O(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10; 
int n,h,tot,pre[MAXN],suf[MAXN]; struct Skill {int t,d;}v[MAXN],eff[MAXN];
map<int,int> mp;
int check(int t) {
	int lst=0,H=h;
	ffor(i,1,tot) {
		int l=lst+1,r=min(t,eff[i].t); //在 i 之前的都是原值,在 i 后的都是乘上 i
		if(l>r) return 0;
		int csa=pre[i-1],csb=suf[i];
		int dft=csa/csb+1;
		if(dft<=l) {
			int A=csb*l,B=csb*r;
			if(r-l+1>=H*2/(A+B)+((H*2)%(A+B)!=0)) return 1;
			H-=(r-l+1)*(A+B)/2;
		}
		else if(dft>r) {
			if(csa>=H/(r-l+1)+(H%(r-l+1)!=0)) return 1;
			H-=(r-l+1)*csa;	
		}
		else {
			int prda=dft-l;
			if(csa>=H/prda+(H%prda!=0)) return 1;
			H-=csa*prda;
			int A=csb*dft,B=csb*r;
			if((A+B)>=H*2/(r-dft+1)+((H*2)%(r-dft+1)!=0)) return 1;
			H-=(A+B)*(r-dft+1)/2;
		}
		lst=eff[i].t;
	}
	int rst=t-lst;
	if(rst>=H/pre[tot]+(H%pre[tot]!=0)) return 1;
	return 0;
}
int bfind(int l,int r) {
	int ans=0;
	while(l<=r) {
		int mid=l+(r-l)/2;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>h;
	ffor(i,1,n) cin>>v[i].t>>v[i].d;
	ffor(i,1,n) if(mp[v[i].t]) eff[mp[v[i].t]].d=max(eff[mp[v[i].t]].d,v[i].d); else eff[++tot]=v[i],mp[v[i].t]=tot;
	sort(eff+1,eff+tot+1,[](Skill A,Skill B){return A.t<B.t;});
	ffor(i,1,tot) pre[i]=max(pre[i-1],eff[i].t*eff[i].d);
	roff(i,tot,1) suf[i]=max(suf[i+1],eff[i].d);
	cout<<bfind(1,h); 
	return 0;
}
```

附：我在判超限的时候用了很神秘的方式，因此调了一个小时。/cf

---

## 作者：Laisira (赞：1)

这道题感觉是贪心加二分，二分答案 $ans$，先肯定是用 $t_{i}\times d_{i}$ 最高的打他。

设当前时间为 $x$，有的 $t_i$ 贡献不完，要与 $ans-x+1$ 取最小值。

否则考虑枚举时间，枚举时间肯定不能挨着枚举，由于最大值的可能更新只有 $O(n)$ 个,于是离散了枚举。

每次的最大值表示为：

- $t_i \leq ans-x+1$，$\max(t_i\times d_i)$
- $t_i > ans-x+1$，$\max((ans-x+1)\times d_i)$

分别维护一下 $t_i$ 大于和小于 $ans-x+1$ 的最大值就行了，平衡树、线段树或者单纯的排个序都可以做。 

然后把最大的总贡献算出来，最后判断与 $H$ 的大小就行了。

---

