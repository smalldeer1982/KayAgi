# 【MX-X5-T4】「GFOI Round 1」epitaxy

## 题目背景

原题链接：<https://oier.team/problems/X5E>。

---

> [epitaxy - かめりあ](https://music.163.com/#/song?id=2600753558)

## 题目描述

给你两个正整数 $n, m$。

定义一个 $1 \sim n$ 的排列 $p$ 的**价值**为所有的 $n - m + 1$ 个长度为 $m$ 的连续子串内最大值的最大公因数。  
（规定单个数的最大公因数为其自身。）

请你求出一个在所有 $1 \sim n$ 的排列中价值最大的排列，如果有多个，求出任意一个均可。

本题将使用**自定义校验器**检查你构造的排列是否正确，即输出任意一个价值最大的排列都会被认为通过。

## 说明/提示

**【样例解释】**

在第一组数据中，当 $n = 2, m = 2$ 时排列 $p = [1, 2]$ 具有最大价值，为 $2$。并且可以证明当 $n = 2, m = 2$ 时不存在价值 $> 2$ 的排列。

在第二组数据中，当 $n = 4, m = 2$ 时排列 $p = [1, 2, 4, 3]$ 具有最大价值，为 $2$，因为所有长度为 $2$ 的子段最大值分别为 $2, 4, 4$，其最大公因数为 $2$，并且可以证明当 $n = 4, m = 2$ 时不存在价值 $> 2$ 的排列。

**【数据范围】**

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | $n \le$ | $\sum n \le$ | 特殊性质 | 子任务依赖 | 分值 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $8$ | $100$ | 无 | 无 | $28$ |
| $2$ | $10^6$ | $10^6$ | A | 无 | $23$ |
| $3$ | $10^6$ | $10^6$ | B | 无 | $7$ |
| $4$ | $10^6$ | $10^6$ | 无 | $1, 2, 3$ | $42$ |

- 特殊性质 A：$m = 2$。
- 特殊性质 B：$m = n$。

对于所有数据，满足 $1 \le T \le 10^5$，$1 \le m \le 10^6$，$2 \le n, \sum n \le 10^6$，$m \le n$。

## 样例 #1

### 输入

```
4
2 2
4 2
7 5
10 3```

### 输出

```
1 2
1 2 4 3
5 3 6 7 1 2 4
6 3 5 8 1 2 4 10 9 7```

# 题解

## 作者：EuphoricStar (赞：8)

首先若 $2m > n$ 最大价值就是 $n$，一个答案是：
$$
1, 2, \ldots, m - 1, n, m, m + 1, \ldots, n - 1
$$
否则最大价值是 $n$ 的最大的 $\le m$ 的因数，设其为 $d$。一个答案是：
$$
1 \sim d, 2d, d + 1 \sim 2d - 1, \ldots, n, n - d + 1 \sim n - 1
$$
最大价值是 $d$ 的证明：

显然一个排列的价值是 $n$ 的因数。因为前面已经给出了一个最大价值为 $d$ 的构造，所以只需要证 $n$ 的 $> m$ 的因数不可能成为一个排列的价值。

任取 $n$ 的一个 $> m$ 的因数，设其为 $x$。那么首先每个长度为 $m$ 的子段都一定要有一个 $x$ 的倍数。

若一个 $x$ 的倍数 $y$ 是一个长度为 $m$ 的子段的最大值，就称 $y$ 支配了这个子段。

可以发现 $x$ 最多只能支配 $x - m + 1$ 个子段，还剩下 $n - x$ 个子段需要支配。

显然一个数至多支配 $m$ 个子段，剩下的 $x$ 的倍数有 $\frac{n}{x} - 1$ 个。

因为 $(\frac{n}{x} - 1) \times m < (\frac{n}{x} - 1) \times x = n - x$，所以这些数不可能支配所有长度为 $m$ 的子段。

时间复杂度：每个测试用例 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
	if (m * 2 > n) {
		for (int i = 1; i <= n; ++i) {
			int x = i;
			if (i == m) {
				x = n;
			} else if (i > m) {
				--x;
			}
			printf("%d%c", x, " \n"[i == n]);
		}
	} else {
		while (n % m) {
			--m;
		}
		for (int i = 1; i <= n; ++i) {
			int t = i;
			if (i > m && (i - 1) % m == 0) {
				t += m - 1;
			} else if (i > m) {
				--t;
			}
			printf("%d%c", t, " \n"[i == n]);
		}
	}
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

闲话：这题一开始是 MX-X only 的 T1。

---

## 作者：keatsli (赞：5)

考虑直接构造。

容易发现 $n$ 一定是某一段的最大值，故答案一定是 $n$ 的因数。

如果 $2m>n$，则构造 $\dfrac{n+1}{2}$ 位置是 $n$，其他位置随便填，此时任意一个区间必然包含 $n$，答案为 $n$。

其余情况至少有两个最大值不同的段，考虑现在 $x$ 的倍数只有 $\dfrac{n}{x}$ 个，其中 $x$ 是答案。

若 $x>m$，则必有一段长为 $m$ 的段没有 $x$ 的倍数（因为 $x$ 的倍数只有 $\dfrac{n}{x}$ 个，一共有 $n$ 个元素），故 $x\leq m$。

所以猜想此时答案是 $m$ 以下最大的 $n$ 的因数。

考虑构造：$x,1,\dots,x-1,2x,x+1,\dots,2x-1,3x,\dots$

然后就做完了。

时间复杂度: $O(Tn)$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while(T--){
		int n,m;cin>>n>>m;
		if(m*2>n){
			int cnt=0;
			for(int i=1;i<=n;++i)if(i==(n+1)/2)cout<<n<<" ";else cout<<(++cnt)<<" ";
			cout<<'\n';
			continue;
		}
		int T=1;
		for(int i=m;i>=1;--i)if(n%i==0){T=i;break;}
		int cnt=0;
		for(int i=1;i<=n/T;++i){
			cout<<T*i<<" ";++cnt;
			for(int j=1;j<T&&cnt<n;++j)cout<<(i-1)*T+j<<" ",++cnt;
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：__3E24AC7002AD9292__ (赞：4)

场上秒了。

题意相当于求所有 $[i,i+m-1]$ 的区间最大值的 $\gcd$ 最大。

如果能任选一些 $x_{1\sim s}$ 的话，$\gcd(x_1,x_2,\dots,x_{s-1})\geq\gcd(x_1,x_2,\dots,x_s)$，原因显然。所以我们考虑把每个区间中最大值的下标标记出来，我们让被标记的下标数量最少的时候，$\gcd$ 的最大值必定可以达到最大。

在这之后，我们先要求出标记下标数量的最小值 $s$。不难算出，这个值为 $\lfloor\frac{n}{m}\rfloor$，这个很显然。

于是我们需要先考虑从排列中选 $s$ 个数 $x_1,x_2,\dots,x_s$ 的最大 $\gcd$。发现 $\gcd$ 的值就是 $n$ 最大的 $\leq m$ 的因数。我们令 $\gcd$ 的值为 $t$。

那我们如果需要构造出 $x_1,x_2,\dots,x_s$ 作为被标记的下标对应的值，且知道了 $t$，那我们可以构造出 $x_i=n-(i-1)t$，显然这时 $x$ 的 $\gcd=t$。

考虑构造解，我们让每个 $i\in[1,s]$，使答案 $a_{is}=x_i$，剩余的空位就从大到小填剩余没选的数。枚举区间容易发现，这样一定是对的。

至于 $t$ 取值的原因：因为 $n$ 这个值必定作为某些区间的最大值，故 $t$ 的值是 $n$ 的因数；而 $s$ 为 $\lfloor\frac{n}{m}\rfloor$，不难发现 $t$ 最多为 $\frac{n}{s}$。

```cpp
int n=read(),m=read(),t=m;
queue<int>a,b;
for (int i=1;i<=n;i++){
	if (i%m) a.push(i);
	else b.push(i);
	d[i]=v[i]=0;
}
while (n%t) t--;
for (int i=n,j=1;i>=1&&j<=n/m;i-=t,j++)
	v[i]=1;
for (int i=n;i>=1;i--){
	if (!v[i]){
		d[a.front()]=i;
		a.pop();
	}
	else{
		d[b.front()]=i;
		b.pop();
	}
}
```

---

## 作者：naroto2022 (赞：3)

# P11132 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P11132)

### 思路

首先看到题目，是一道令人不嘻嘻的构造题，于是不嘻嘻地开始想构造方式。

观察题目发现，如果第 $k\times m,k\in\mathbb{N}$ 是区间 $[(k-1)\times m+1,(k+1)\times m-1]$ 的最大值，那么在这个区间中的 $m$ 个区间的最大值都是第 $k\times m$ 个数。

想到一个区间这样的关键点的个数我们是可以构造的，所以我们完全可以求出最大的答案然后构造。即在每个关键点都放答案的倍数。

问题就是答案是啥，首先想到 $n$ 不管在那个区间它都是最大值，所以答案必须是 $n$ 的因数。

又考虑到这样的关键点至少要有 $\lceil\frac{n}{m}\rceil$ 个，所以理想的答案就是 $n$ 的因数中小于等于 $m$ 的最大的那一个。

于是按照上面的答案的倍数排在 $k\times m,k\in\mathbb{N}$ 的构造方式构造即可。

当然还要再特判一种情况，那就是答案为 $n$ 的情况，就是 $2\times m>n$ 的情况，这种情况容易想到只有一个关键点，所以只要把 $n$ 放在最中间的那个位置，那么就是对的。

于是不嘻嘻的构造题就嘻嘻地过了~

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
ll n,m;
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
int main(){
    // freopen("1.in","r",stdin);
    ll T=read();while(T--){
        n=read();m=read();
        if(m*2>n){for(int i=1; i<=n/2; i++) cout<<i<<' ';cout<<n<<' ';for(int i=n/2+2; i<=n; i++) cout<<i-1<<' ';cout<<endl;}
        else{
            ll p;
            for(int i=m; i>=1; i--) if(n%i==0){p=i;break;}
            if(p==1) for(int i=1; i<=n; i++) cout<<i<<' ';
            else{
                m=p;
                for(int i=1; i<=m; i++) cout<<i<<' ';
                for(int i=2; i<=n/m; i++) for(int j=i*m,k=1; k<=m; j--,k++) cout<<j<<' ';
            }
            cout<<endl;
        }
    }
	return 0;
}
```

---

## 作者：wxzzzz (赞：3)

### 思路

因为至少一个区间的最大值为 $n$，所以答案一定是 $n$ 的因数，可以枚举因数 $O(n)$ check。

令当前要 check 的因数为 $x$，对于一个 $b_i=ix\ (1\le i\le \lfloor\cfrac{n}{x}\rfloor)$，若其在答案排列中下标为 $pos_i$，它必须作为所有包含 $pos_i$ 的长度为 $m$ 的区间的最大值，即区间 $[pos_i-m+1,pos_i]$ 的最大值。

现在已经知道如何 check 一个排列，考虑如何构造。

首先 $n$ 肯定放在 $m$，然后按 $b_i$ 从大到小构造一个单增的下标序列。现在相当于要用若干个给定终点的长度为 $2m-1$ 的线段覆盖 $1\sim n$，覆盖的充要条件是中点权值大于区间内其他位置的权值。

显然 $pos_i$ 一定要在合法的基础上尽可能大，这对后面的构造更优。

然后有一个结论：对于一个 $pos_i-pos_{i+1}<m$，它扩展为 $pos_i\gets pos_i+1$ 一定更优。

证明：因为 $pos_i$ 合法，所以有 $\forall j\in[pos_{i+1}+1,pos_i-1],a_j<b_i$若 $pos_i$ 不合法，那么一定是有一个 $>b_i$ 的数从后面移过来了，但如果不更改 $pos_i$，这个数同样无法被 $b_{i\sim 1}$ 覆盖，因为 $b_i$ 是单减的。因此更新 $pos_i$ 一定不劣。

直接贪心地覆盖，最后剩下的堆在序列末尾，剩余不在 $b$ 中的数降序填进所有空位即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m, ans, a[1000005], b[1000005], c[1000005], num[1000005];
bool check(int x) {
    for (int i = 1; i <= n; i++)
        a[i] = 0;
    int t = 0, tt = 0, id = 0, ed, pos = m;
    for (int i = x; i <= n; i += x)
        b[++t] = i, num[t] = 0;
    ed = t;
    for (int i = n; i >= 1; i--)
        if (i % x)
            c[++tt] = i;
    a[m] = b[t];
    for (int i = t - 1; i >= 1; i--) {
        pos += m;
        a[pos] = b[i];
        ed = i;
        if (pos >= n - m + 1) {
            for (int j = i - 1; j >= 1; j--)
                c[++tt] = b[j];
            break;
        }
    }
    for (int i = n; i >= 1; i--)
        if (!a[i])
            a[i] = c[tt--];
    pos = 0;
    for (int i = t; i >= ed; i--) {
        pos += m;
        for (int j = max(pos - m + 1, 1); j <= min(pos + m - 1, n); j++)
            if (a[j] > b[i])
                return 0;
    }
    return pos >= n - m + 1;
}
int main() {
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = n; i >= 1; i--)
            if (!(n % i) && check(i))
                break;
        for (int i = 1; i <= n; i++)
            cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：luqyou (赞：2)

## 思路

貌似跟官方题解不一样？

我们考虑最优情况下，对答案造成贡献的数会被我们放在什么位置。

发现下标为 $m$ 的倍数能够“控制”的数是最多的，所以我们考虑将数填入下标为 $m$ 的倍数的地方。

接下来我们来考虑答案。不难发现 $n$ 一定是对答案有贡献的；其次 $n$ 最多只能完全“控制” $m-1$ 个数。

这就意味着我们可以枚举 $[n-m,n)$ 中的每一个值，将其作为可能的第二小的有贡献的数，计算其与 $n$ 的 $\gcd$ 取 $\max$ 即可。

然后对于剩余的没有填的空位，降序将剩余的数填入即可。

## Main Code

```cpp
for(int i=1;i<=m;i++) if(maxx<__gcd(n,n-i)) maxi=n-i,maxx=__gcd(n,i);
int num=n;
for(int i=m;i<=n;i+=m) a[i]=num,vis[num]=1,num-=maxx;
for(int i=n;i;i--) if(!vis[i]) vec.pb(i);
for(int i=1;i<=n;i++) if(!a[i]) a[i]=vec[z++];
for(int i=1;i<=n;i++) cout<<a[i]<<" ";

---

## 作者：Imerance1018 (赞：2)

居然场切了蓝题。

### Description

[传送门](https://www.luogu.com.cn/problem/P11132)

### Solution

这题有点 CF 的味道（我做的时候是部分分启发正解）。

#### Subtask 1

暴力枚举 $n$ 的全排列即可。（用来对拍，不过 $n=12$ 时就炸了）

#### Subtask 2

通过前面的打表找规律，我们能够发现性质：

1. 对于 $n$ 为不是 3 的奇数，价值必然为 1。我们只需按序输出 1 到 $n$ 即可。
2. 对于 $n$ 为偶数，价值必然为 2。我们先输出 1 和 2，其他每相邻两个数交换位置再输出。

当然对于 $n=3$，价值是 3，要输出`1 3 2`。

#### Subtask 3
此时 $m=n$。

那么我们便想到，这个时候价值也必然等于 1。直接按序输出 1 到 $n$ 即可。
#### Subtask 4
正解部分。

在子任务 3 的基础上，我们可以进一步想：若 $m=n-1$，此时价值就是 $\frac{n}{2}$。那么先输出 1 到 $m$，然后输出 $n$，最后输出其他的数即可。

显然，对于任意 $m > \frac{n}{2}$ 都可以这么做。

那么对于 $m = \frac{n}{2}$ 呢？

显然价值为 $\frac{n}{2}$，可以倒序输出 $\frac{n}{2}$ 到 1,再倒着输出 $n$ 到 $\frac{n}{2} +1$。

以此类推，对于所有 $m \mid n$，都可以把 $n$ 个数分成 $\frac{n}{m}$ 段，对每一段进行倒序输出。

子任务 2 验证了我们的结论。

那么对于 $m \nmid n$，我们不难推出：只需找到最小的 $i$ 大于 $m$，使得 $i \mid n$，然后把 $n$ 个数分成 $\frac{n}{i}$ 段，对每一段进行倒序输出。

完结撒花。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		if(n==m)
		{
			for(int i=1;i<=n;i++)cout<<i<<" ";
			cout<<endl;
			continue;
		}
		else if(m==2)
		{
			if(n==3)cout<<"1 3 2"<<endl;
			else if(n%2==1)
				for(int i=1;i<=n;i++)cout<<i<<" ";
			else
			{
				cout<<"1 2 ";
				for(int i=3;i<=n;i++)
				{
					cout<<i+1<<" ";
					i++;
					cout<<i-1<<" ";
				}
			}
			cout<<endl;
			continue;
		}
        else if(m>n/2)
		{
			for(int i=1;i<m;i++)cout<<i<<" ";
			cout<<n<<" ";
			for(int i=m;i<n;i++)cout<<i<<" ";
			cout<<endl;
			continue;
		}
		if(n%m==0)
		{
			for(int i=1;i<=n/m;i++)
				for(int j=i*m;j>(i-1)*m;j--)cout<<j<<" ";
			cout<<endl;
			continue;
		}
		int tmp=1;
		for(int i=m;i>=2;i--)
		{
			if(n%i!=0)continue;
			tmp=i;
			break;
		}
		for(int i=1;i<=n/tmp;i++)
				for(int j=i*tmp;j>(i-1)*tmp;j--)cout<<j<<" ";
			cout<<endl;
	}
	return 0;
}
``````

---

## 作者：Ad_lqz_ht (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P11132)

## 题目大意
把长度为 $n$ 一个序列的价值定义为：在一个序列中所有长度为 $m$ 的子串的最大值的最大公约数。

找到这个排列的所有排列中价值最大的那个。
## 思路
我们可以分两种情况考虑，对于 $m > \frac n 2$ 的情况，此时序列中间一定有一部分相交，此时，我们可以让 $n$ 位于其相交的部分，此时的任意一段的最大值都是 $n$，最大公约数也只能是 $n$，直接输出即可。

对于另一种情况，我们可以对序列找出 $n$ 以内所有可能的因数，然后找到其中可行的最大的因数 $k$，输出就好了。

我们怎么确定一个最大公约数是可行的，当且仅当这个东西是 $n$ 的因数且不超过 $m$ 。这是因为 $n$ 作为最大的数在每一段一定会出现，所以如果选出的因数不是 $n$ 的约数显然不优（最大公约数是 $1$）。

因此，不难想到，可以找到不超过 $m$ 的 $n$ 的最大的因数，这样可以保证它一定出现了 $n-m+1$ 次，且有一个最优的最大公约数。

输出的时候要注意倒序输出，这样可以保证，在任意一段中，能取到的最大值一定是 $k$ 的倍数。

一个小优化：在寻找最大公约数的过程中，可以仅枚举，不超过 $\sqrt n$ 的部分，然后另一部分通过 $\frac n i$ 直接计算即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m;
signed main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);
    cin >> t;
    while(t--) {
        cin >> n >> m;
        if(m >= (n >> 1) + 1)//第一部分
        {
            for(int i = 1;i <= n >> 1; ++i) cout << i << ' ';//前半
            cout << n;//中间的n
            for(int i = (n >> 1) + 1;i <= n - 1; ++i) cout << ' ' << i << '\n';//后半
            cout << '\n';
        }
        else
        {
            int maxys = 0;
            for(int i = 1; i * i <= n; ++i)//找到最大的可行的约数
                if (n % i == 0)
                {
                    if(i <= m) maxys = max(maxys, i);
                    if(n / i <= m) maxys = max(maxys, n / i);
                }
            for(int i = maxys; i <= n; i += maxys)//分段输出
                for(int j = i; j >= i - maxys + 1; --j)
                    cout << j << ' ';
            cout << '\n';
        }
    }
	return 0;
}
```

## 写在后面
赛事没做出来，我是大采购！

---

## 作者：Qing_que (赞：1)

## 题意
构造一个长度为 $n$ 的排列，使得所有长度为 $m$ 的连续子序列中的最大值的最大公约数最大。

## 思路
不难想到，当 $m$ 大于 $\frac{n}{2}$ 时，所有的连续子序列都可以取到序列的中间位置，因此可以把 $n$ 放在中间，其余位置任意（因为此时所有序列的最大值都为 $n$），最大公约数为 $n$。

对于 $m$ 小于等于 $\frac{n}{2}$ 的情况，最大公约数一定小于 $n$，因此要让最大公约数最大，所有取出的最大值一定要不与 $n$ 互质，因为一定有至少一个最大值为 $n$。那么我们要找到一种方法，使得最后的最大公约数最大。

考虑到最后的最大公约数一定是 $n$ 的一个因数，而在 $1\sim n$ 中一定有若干数存在一个相同的因数，因此只需要找到一个最大的因数，并且它的若干倍都可以在 $n-m+1$ 段中作为最大值存在即可。具体的实现可以参考代码。
## code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
signed main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        if(m >= n/2+1) {
            for(int i = 1;i <= n/2;i++) cout << i << ' ';
            cout << n << ' ';
            for(int i = n/2+1;i <= n-1;i++) cout << i << ' ';
            cout << '\n';
        } else {
            int maxn = 0;
            for(int i = 1;i*i <= n;i++) {
                if(n%i == 0) {
                    if(i <= m) maxn = max(maxn, i);
                    if(n/i <= m) maxn = max(maxn, n/i);
                }
            }
            for(int i = maxn;i <= n;i += maxn) {
                for(int j = i;j >= i-maxn+1;j--) {
                    cout << j << ' '; //这样可以使maxn的倍数都作为最大值出现
                }                     //如 3 2 1 6 5 4，m = 3
            }
            cout << '\n';
        }
    }
	return 0;
}
```

---

## 作者：gcx12012 (赞：1)

### 前言
一道有些一眼的构造题。
### Solution
首先我们设 $mx=\max_{i=1}^n a_i$，显然这个最大价值一定是 $mx$ 的一个因数，因为值为 $mx$ 的数一定存在。然后因为 $a$ 是一个排列，所以 $mx=n$。

然后我们可以把这个 $n$ 的因数求出来，一个一个枚举来构造。假设当前枚举的因数为 $p$，考虑什么样的构造是最优的。

我们考虑把 $1$ 到 $n$ 这些数分成两组，一组是 $p$ 的倍数，另一组不是 $p$ 的倍数。

然后我们从大到小去填这些数，当这个数是 $p$ 的倍数时，它是有益的，而它可以使包含它的没填过数的区间的最大值一定为这个数，反之，我们就不能去填任何一个空区间。

考虑贪心，每次将 $p$ 的倍数隔一个 $m$ 的距离填上，然后将不是 $p$ 的倍数填到非空区间即可。

直接做的话是 $O(\sum nd(n))$ 的，其中 $d(n)$ 为 $n$ 的因数个数，如果害怕超时的话可以写个二分，复杂度变为 $O(\sum n\log_2 d(n))$，实测可以通过。
### Code

```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 1000010
#define For(i,a,b) for(ll i=a;i<=b;i++)
#define Rof(i,a,b) for(ll i=a;i>=b;i--)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<ll,ll>

using namespace std;
bool st;
int fac[N],cnt=0,ans[N],pans[N];
int T,n,m;
bool ed;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool chk(int now){
	For(i,1,n) ans[i]=0;
	int l=n+1,r=n;
	Rof(i,n,1){
		if(i%now==0){
			if(l>1){
				l=max(1,l-m),ans[l]=i;
				if(l<=m) l=1;
			}else{
				while(1){
					if(l>r) return 0;
					if(!ans[r]){
						ans[r]=i;
						break;
					}
					r--;
				}
			}
		}else{
			while(1){
				if(l>r) return 0;
				if(!ans[r]){
					ans[r]=i;
					r--;
					break;
				}
				r--;
			}
		}
		//For(j,1,n) cout<<ans[j]<<' ';
		//cout<<endl;
	}
	For(i,1,n) if(!ans[i]) return 0;
	For(i,1,n) pans[i]=ans[i];
	return 1;
}
void sol(){
	n=read(),m=read();
	if(m==1){
		For(i,1,n) printf("%d ",i);
		printf("\n");
		return;
	}
	cnt=0;
	For(i,1,sqrt(n)){
		if(n%i==0){
			fac[++cnt]=i;
			if(i*i!=n) fac[++cnt]=n/i;
		}
	}
	sort(fac+1,fac+cnt+1);
	int l=1,r=cnt;
	while(l<=r){
		int mid=(l+r)>>1;
		if(chk(fac[mid])) l=mid+1;
		else r=mid-1;
	}
	For(i,1,n) printf("%d ",pans[i]);
	printf("\n");
}

int main()
{
	//fprintf(stderr,"%d",(&ed-&st)/1024/1024);
	T=read();
	while(T--) sol();
	return 0;
}
/*

*/
```

---

## 作者：happybob (赞：1)

首先可以发现答案必然为 $n$ 的因数，不妨考虑每个 $n$ 的因数 $d$，手玩一下最优构造应该形如每个 $d$ 的倍数占领一段长为 $2m-1$ 的区间，并且其余数的放置顺序是容易确定的。直接构造出来之后用单调队列判断权值即可。总复杂度 $O(nd(n))$，可以通过。

代码：


```cpp
array<bool, N> vis, vis2;

inline int calc()
{
	if (*max_element(a.begin() + 1, a.begin() + n + 1) != n || *min_element(a.begin() + 1, a.begin() + n + 1) != 1) return -1;
	int ret = -1;
	deque<int> q;
	for (int i = 1; i <= m; i++)
	{
		while (q.size() && a[i] > a[q.back()]) q.pop_back();
		q.emplace_back(i);
	}
	for (int i = 1; i + m - 1 <= n; i++)
	{
		int maxn = a[q.front()];
		if (ret == -1) ret = maxn;
		else ret = gcd(ret, maxn);
		int j = i + m;
		if (j <= n)
		{
			while (q.size() && a[j] > a[q.back()]) q.pop_back();
			q.emplace_back(j);
		}
		while (q.size() && q.front() <= i) q.pop_front();
	}
	return ret;
}

int main()
{
	//freopen("*.in", "r", stdin);
	//freopen("*.out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; i++) a[i] = i, vis[i] = 0, vis2[i] = 0;
		if (m == 1)
		{
			for (int i = 1; i <= n; i++) cout << i << " ";
			cout << "\n";
			continue;
		}
		for (int x = n; x >= 2; x--)
		{
			if (n % x == 0)
			{
				for (int j = 1; j <= n; j++) vis2[j] = vis[j] = a[j] = 0;
				int y = n, now = n;
				bool tag = 0;
				bool ret = 0;
				for (int j = 1; j <= n; j++)
				{
					if (!vis[j])
					{
						int r = min(n, j + m - 1);
						if (tag) r = j;
						tag = 1;
						if (y<0)
						{
							ret=1;
							break;
						}
						a[r] = y;
						vis2[y] = 1;
						vis[r] = 1;
						y -= x;
						for (int xx = j; xx <= min(n, r + m - 1); xx++)
						{
							if (xx == r) continue;
							while (now > 0 && (vis2[now] || now % x == 0))
							{
								now--;
							}
							a[xx] = now;
							vis[xx] = 1;
							vis2[now] = 1;
						}
					}
				}
				if(ret) continue;
				now = n;
				for (int j = 1; j <= n; j++)
				{
					if (!a[j])
					{
						while (now > 0 && vis2[now])
						{
							now--;
						}
						a[j] = now;
						vis2[now] = 1;
					}
				}
				if (calc() == x)
				{
					for (int j = 1; j <= n; j++) cout << a[j] << " ";
					cout << "\n";
					goto E;
				}
			}
		}
		for (int i = 1; i <= n; i++) cout << i << " ";
		cout << "\n";
		E:;
	}
	return 0;
}
```

---

## 作者：CusetVoidAldehyde (赞：0)

[P11132 epitaxy](https://www.luogu.com.cn/problem/P11132)

看完题，我们很容易想到：如果 $m > \frac{n}{2}$，那么长度为 $m$ 的区间总会覆盖到总区间的一半，只需要在中间位置输出 $n$ 即可：

```cpp
if (m > n / 2) {
  for (int i = 1; i <= n; i++) a[i] = i;
  swap(a[n], a[n / 2 + 1]);
  for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
}
```

当 $m \le \frac{n}{2}$ 的时候呢？我们知道，在最后的 $\gcd$ 式子中，一定会包含 $n$。那么，我们只需要使最后式子中的所有数与 $n$ 不互质即可，即最后式子为：$\gcd(k,2k,3k,\cdots,pk)$，显然，$pk=n$。所以，只需要将这数列分为 $\frac{n}{k}$ 段，并且把每一段倒序输出（目的是保证这长度为 $k$ 的第 $i$ 段的最大值一定是 $ik$）即可。

```cpp
else {
  for (int i = m; i >= 1; i--) {
    if (n % i == 0) {
      for (int j = 1; i * j <= n; j++) {
        reverse(a + i * (j - 1) + 1, a + i * j + 1); //枚举边界
        break;
      }
    }
  }
  for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
}
```

---

## 作者：ni_ju_ge (赞：0)

# P11132 题解
[传送门](https://www.luogu.com.cn/problem/P11132)

## 思路
要使长度为 $m$ 的每个子串中的最大值的最大公因数最大，那么这个公因数应该是 $n$ 的因子（因为 $n$ 一定是最大的数），所以，每个长度为 $m$ 的子串的最大值都要与 $n$ 有相同的公因数，那么，拥有这个公因数的个数应当为 $n-m+1$，故只需要遍历一次 $n$ 的因数查找含有这个因数的 $p_i$ 的个数，并判断是否有 $n-m+1$ 个即可。

其它的需要注意的地方都放在代码里了。
## AC Code

```cpp
#include<iostream>
using namespace std;
int t,n,y;
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n>>m;
		if(m*2>n)//特判最大值都是 n 的情况 
		{
			for(int j=1;j<=n/2;j++)cout<<j<<" ";
			cout<<n<<" ";
			for(int j=n/2+1;j<n;j++)cout<<j<<" ";
		}
		else
		{
			int k=n/m+1;//需要的包含 n 的因子的数的数量 
			if(n%m==0)k--;//若 m 正好是 n 的因子，那么明显只需要 n/m 个区间 
			for(int j=n;j>=1;j--)
			{
				if(n%j==0&&n/j>=k)
				{
					k=j;//求出符合条件的因子最大是多少 
					break;
				}
			}
			for(int j=1;j<=n/k;j++)
			{
				cout<<j*k<<" ";//先输出符合条件的数 
				for(int r=1;r<k;r++)cout<<j*k-r<<" ";//再输出小于它的 k-1 个数
				//这样就能使每 m 个数之中的最大数是符合条件的数 
			}
		}
		cout<<endl;
	}
}
```
注：不要抄 tj

---

## 作者：xixisuper (赞：0)

# P11132 【MX-X5-T4】「GFOI Round 1」epitaxy 题解

昨天下午闲的没事看了眼月赛 J 组，发现最后一题放了一道暴力？来切了并水一发题解。

## 思路

我们称一个长度为 $m$ 的连续子串为**一个窗口**。

注意到至少存在一个窗口会把 $n$ 套住，而这个 $n$ 必然会成为该窗口的价值，所以说最后求最大公约数时必然会把 $n$ 算在内，于是最终的公约数必然会是 $n$ 的约数。

然而我们发现实际上一个数的约数个数是很少的，对于 $n\le 10^6$ 来说，约数个数最多的数也没有超过 $300$ 个，所以我们大可以直接枚举 $n$ 的因数，从大到小枚举，然后判断每个因数是否可以作为最后的公因数。

那么如何检验呢？假设我们当前枚举到的最后的因数是 $d$，那么显然只有 $d,2d,3d,\cdots,n$ 这些 $d$ 的整倍数才能够作为窗口里的价值，我们不妨把它们排成一排，然后把剩下的数插进它们之间的空中。

$$
\underbrace{\cdots\cdot\cdots}_{m-1} d \underbrace{\cdots\cdot\cdots}_{m-1} 2d \underbrace{\cdots\cdot\cdots}_{m-1} 3d \underbrace{\cdots\cdot\cdots}_{m-1}
$$

由于我们对窗口的长度限制为 $m$，所以说如果我们想要往两数之间插数的话，我们最多插入 $m-1$ 个数，同时这 $m-1$ 个数必须小于两边的因数，于是我们便有了一个贪心做法，每次往里面插数，如果发现当前的空里的数已经有 $m-1$ 个了或者是当前放的数已经大于两端的因数了，我们便向后挪一个空，知道没有位置可挪，或者所有数都放完为止。

对于每个空来说，我们可以开一个 `vector` 来维护，由于每个数至多会被放一次，所以单次判断的时间复杂度为 $O(n)$，那么总时间复杂度就是 $O(d(n)\cdot n)$ 了。

## 代码

最后一个点跑了不到 200ms，通过本题绰绰有余。

```cpp
#include <iostream>
#include <vector>
#define ll int
using namespace std;
const ll N=1e6+10;
bool vis[N];
ll n,m;
vector<ll> lin[N];
void solve(){
	cin>>n>>m;
	if(m==1) goto edit;
	for(ll i=n;i>1;i--){
		if(n%i) continue;
		//cout<<i<<":\n";
		for(ll j=1;j<=n;j++)vis[j]=0;
		ll top=0,gt=0;
		lin[0].clear();
		for(ll j=i;j<=n;j+=i){
			vis[j]=1;
			top++;
			lin[top].clear();
		}
		//cout<<top<<"\n";
		for(ll j=1;j<=n;j++){
			if(vis[j]) continue;
			while(j>((gt==0)?i:(gt*i))) gt++;
			if(gt>top) goto failed;
			if(lin[gt].size()==m-1) gt++;
			if(gt>top) goto failed;
			lin[gt].push_back(j);
		}
		for(ll j=0;j<=top;j++){
			ll lz=lin[j].size();
			for(ll k=0;k<lz;k++) cout<<lin[j][k]<<' ';
			if(j<top) cout<<(j+1)*i<<' ';
		}
		cout<<"\n";
		return;
		failed:;
		//cout<<"\n\n";
	}
	edit:;
	for(ll i=1;i<=n;i++) cout<<i<<' ';
	cout<<"\n";
}
ll T;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

这题蓝？

---

显然，如果 $m> \lfloor\dfrac n2\rfloor$，则将 $n$ 放在正中间，其它数随便放，答案为 $n$。

否则，我们假设答案为 $x$，那么任何一段长度为 $m$ 的区间都应当至少包含一个 $x$ 的倍数作为最大值，也就是说 $x\le m$。

将 $1\sim x$ 分为一块，$x+1\sim 2x$ 分为一块，以此类推，显然如果有剩余的不完整的块就会爆掉（一定至少有一个连续段最大值为 $n$），因此要有 $x\mid n$。

之后对于每一块我们分开考虑。

如果这个时候第 $a$ 个块的第一个数**不是** $ax$，那么这个数会比之前所有的数都更大，那么这个时候以这个位置结尾的长度为 $m$ 的块的最大值就会是它，而它不是 $x$ 的倍数。因此，我们直接令第 $a$ 个块的第一个数是 $ax$，块内其余数随便排。

容易发现这样是合法的，于是找到任意一个不超过 $m$ 的 $n$ 的因数作为 $x$ 即可。

~~这么水的题还有蓝？~~

---

## 作者：w9095 (赞：0)

[P11132 【MX-X5-T4】「GFOI Round 1」epitaxy](https://www.luogu.com.cn/problem/P11132)

基于次大值的构造。

考虑到如果最大值和次大值都出现那么结果一定为 $1$。而如果次大值在序列中出现 $2m-1$ 次，则一定会与最大值一起出现，这是不好的。

因此，我们构造把次大值放在序列开头，之后最大值必须要放在前 $m$ 个位置。这中间有 $m-2$ 个空位，我们填上 $n-2\sim n-m-1$，剩下的位置需要填入一个 $1\sim n-m$ 的排列，这是一个完全相同的子问题。

如果我们不把空位填上 $n-2\sim n-m-1$，就是希望能更改答案序列中的值。而这种更改上述构造方式也能做到，所以直接这样构造是没有问题的。另外，也可以把次大值放在序列结尾，但是只是改变一个方向，本质相同。如果不把次大值贴紧开头，与这个构造也是等价的，但变得不好处理。

我们发现答案序列中的数构成等差序列且公差为 $n$ 的约数时才能更新答案，所以我们枚举公差，按照上述方式构造即可。

注意有可能 $m$ 过大，最小值不能出现 $2m-1$ 次，这个时候把最大值放中间就好了。我因为这个边界条件卡了一整场，警示后人。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,m,ans=0;
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld%lld",&n,&m);
	   	if(m>n/2)
	   	   {
	   	   	for(int i=1;i<=n/2;i++)printf("%lld ",1ll*i);
	   	   	printf("%lld ",n);
	   	   	for(int i=n/2+2;i<=n;i++)printf("%lld ",i-1ll);
		   }
	   	else
		   	{
		   	bool flag=1;
			for(int i=m;i>=2;i--)
			   	if(n%i==0)
			   	    {
			   	    long long now=n;
			   	    flag=0;
				   	while(now>0)
				   	    {
				   	    printf("%lld ",now-1);
				   	    for(int j=1;j<=i-2;j++)printf("%lld ",now-1-j);
				   	    printf("%lld ",now);
				   	    now-=i;
						}
					break;
					}
			if(flag)for(int i=1;i<=n;i++)printf("%lld ",i);
		    }
		printf("\n");
	   }
	return 0;
}
```

---

## 作者：cheng2010 (赞：0)

## 思路

首先，这样构造一定是优的：

当 $m >  \frac{n}{2} $ 时：$1,2,\dots,\frac{n}{2},n,\frac{n}{2}+1,\frac{n}{2}+2,\dots,n-1$。

当 $m|n$ 时：$m,1,2,\dots,m-1,\dots,km,(k-1)m+1,\dots,km-1$。

因为这样，每一段长度为 $m$ 的最大值的 $\gcd$ 就是 $m$，显然最优。

此时，正解就出来了，找到 $n$ 小于 $m$ 的最大的因数，再把 $m$ 设为它，用上面的方法即可。

## code
```cpp
#include<bits/stdc++.h>
#define LL p<<1
#define RR p<<1|1
#define dl double
using namespace std;
const int N=1e6+7;
int n,m;
int a[N];
int ans[N];
inline void solve()
{
	scanf("%d %d",&n,&m);
	if(m>n/2)
	{
		for(int i=1;i<=n/2;i++) 
			printf("%d ",i);
		printf("%d ",n);
		for(int i=n/2+1;i<n;i++)
			printf("%d ",i);
		puts("");
		return;
	}
	int mx=0;
	for(int i=1;i*i<=n;i++)
	{
		if(n%i==0)
		{
			int v1=i;
			int v2=n/i;
			if(v1<=m)
			{
				mx=max(mx,v1);
			}
			if(v2<=m)
			{
				mx=max(mx,v2);
			}
		}
	}
	m=mx;
	a[1]=m;
	for(int i=2;i<=m;i++)
	{
		a[i]=i-1;
	}
	int v=0;
	while(1)
	{
		if(v+m>n) break;
		for(int i=1;i<=m;i++)
		{
			ans[++v]=a[i];
			a[i]+=m;
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";
	}
	puts("");
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--) solve();
}
```

## 后记
赛时特判判错了，痛失 AC，┭┮﹏┭┮。

---

## 作者：modfish_ (赞：0)

## 思路
设这 $n-m+1$ 个最大值构成的集合为 $S$。

显然 $n\in S$，故 $\gcd_{i\in S}i \mid n$。设 $\gcd_{i\in S}i=d$。

以下先讨论 $2m\le n$ 的情况。

容易发现，$S$ 中的次大值一定不小于 $n-m$。

证明：

我们有一种方法使得某个数不属于 $S$：将 $n$ 放在第 $m$ 位，则之前的 $m-1$ 位上放的所有数都不在 $S$ 中。之后，除了前 $m$ 个数之外的最大值一定在 $S$ 中，这个就是 $S$ 中的次大值。

前 $m$ 个数至多包含 $n-m+1$ 到 $n$ 之间的数，所以次大值至少是 $n-m$。

设次大值为 $p$，则 $d\mid \gcd(n,p)$，故 $p=n-kd$。由 $n-kd\ge n-m$，得 $kd\le m,d\le m$。

所以 $d$ 不能超过 $m$。而且不难发现，不超过 $m$ 的所有 $d$ 都可以构造出一个合法的排列，具体如下：

将 $1$ 到 $n$ 倒序排列，交换每个 $d$ 的倍数和比它小的最大的模 $d$ 余 $1$ 的数。

证明：

这样构造的序列形如：$(n-d+1,n-1,\dots,n-d+2,n),(n-2d+1,n-d-1,\dots,n-2d+2,n-d),\dots$。这里每 $d$ 位划分了一下。因为 $d\le m$，所以 前 $m-1$ 位不在 $S$ 中，同理，$m+1$ 到 $2m-1$ 位也不在 $S$ 中。所以，$S=\{n,n-d,\dots,2d,d\}$，故 $\gcd_{i\in S}i=d$。

对于 $2m>n$ 的情况，只要把 $n$ 放在中间就行了，答案一定是 $n$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n, m;
		scanf("%d %d", &n, &m);
		if(m > n / 2){
			for(int i = 1; i <= n / 2; i ++) printf("%d ", i);
			printf("%d ", n);
			for(int i = 1; i <= (n - 1) / 2; i ++) printf("%d ", n / 2 + i);
			printf("\n");
			continue;
		}
		int d = 0;
		for(int i = m; i >= 1; i --){
			if(!(n % i)){
				d = i;
				break;
			}
		}
		for(int i = n; i >= 1; i --){
			if(i % d == 1) printf("%d ", i + d - 1);
			else if(i % d == 0) printf("%d ", i - d + 1);
			else printf("%d ", i);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# P11132 解题报告

## 前言

神秘构造题送我上分！

## 思路分析

首先 $n < 2m$ 是平凡的，考虑这样构造，使答案为 $n$：$1,2,3,…,m-1,n,m+1,m+2,m+3,…,n-1$。

具体来说就是将 $n$ 放在数列最中间，使得所有区间的最大值都是 $n$。

考虑 $n \ge 2m$ 的情况。

先打个表：

-  当 $n=9,m=3$ 时，构造数列为：$7,8,9,4,5,6,1,2,3$。

-  当 $n=9,m=2$ 时，构造数列为：$9,8,7,6,5,4,3,2,1$。

- 当 $n=10,m=2$ 时，构造数列为：$9,10,7,8,5,6,3,4,1,2$。

- 当 $n=10,m=3$ 时，构造数列为：$9,10,7,8,5,6,3,4,1,2$。

- 当 $n=10,m=5$ 时，构造数列为：$6,7,8,9,10,5,4,3,2,1$。

- 当 $n=8,m=4$ 时，构造数列为：$5,6,7,8,1,2,3,4$。

应该能看出规律来了。

我们用语言总结一下规律。

首先，答案为不大于 $m$ 的 $n$ 的最大因数。

设最大因数为 $p$。

构造序列形如：$n-p+1,n-p+2,n-p+3,…,n,n-2p+1,n-2p+2,n-2p+3,…,n-3p+1,n-3p+2,n-3p+3,…,3,2,1$。

然后就做完了。

考虑证明构造正确性。

$n < 2m$ 的构造是平凡的，不再赘述。

$n \ge 2m$ 的构造，因为每一段区间中都有 $n-kp$ 作为区间最大值，所以答案一定为 $p$。

只需要证明 $p$ 是最大答案即可。


### 引理1

$p$ 是 $n$ 的因数。

证明考虑反证法。因为区间中最大值都为 $n-kq$。如果 $q$ 不是 $n$ 的因数，则一定存在一个更大的答案 $t$，且 $t$ 是 $n$ 的因数。因为区间中 $n-kq$ 和 $n-kt$ 的数量是相等的。

### 引理2

$p \le m$。

证明很简单。根据引理 $1$，区间中作为最大值的数有 $\frac{n}{p}$ 个，并且这些最大值分布均匀，一定不劣于分布紧密。证明考虑反证法，不再赘述。所以，相邻两个最大值在最优情况中，距离为 $p$，因为相邻两个最大值之间的数不能成为最大值，也就意味着任选相邻的 $m$ 个数，必有至少一个最大值。所以 $p \le m$。

把引理 $1$ 和 引理 $2$ 合并，就得到了我们的结论。

## 代码实现

~~我觉得结论题没必要放代码欸。~~

打标程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[15],b[15],gcd;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i]=i;
	}
	do{
		gcd=0;
		for(int i=1;i<=n;i++){
			int maxn=0;
			for(int j=1;j<=m;j++){
				maxn=max(maxn,a[i+j-1]);
			}
			b[i]=maxn;
		}
		for(int i=1;i<=n;i++){
			gcd=__gcd(gcd,b[i]);
		}
		if(gcd==/*最大值*/){
			for(int i=1;i<=n;i++){
				cout<<a[i]<<' ';
			}
			cout<<'\n';
		}
	}while(next_permutation(a+1,a+1+n));
	return 0;
}
```
AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		ans=0;
		if(m*2>n){
			for(int i=1;i<=n/2;i++){
				cout<<i<<' ';
			}
			cout<<n<<' ';
			for(int i=n/2+2;i<=n;i++){
				cout<<i-1<<' ';
			}
			cout<<'\n';
		}else{
			for(int i=1;i*i<=n;i++){
				if(n%i==0){
					if(i<=m) ans=max(ans,i);
					if(n/i<=m) ans=max(ans,n/i);
				}
			}
			for(int i=n/ans;i>=1;i--){
				for(int j=1;j<=ans;j++){
					cout<<ans*(i-1)+j<<' ';
				}
			}
			cout<<'\n';
		}
	}
	return 0;
}
```

## 后记

要想构造做的好，打表猜想少不了。

---

