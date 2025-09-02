# [ABC321F] #(subset sum = K) with Add and Erase

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc321/tasks/abc321_f

箱を用意します。最初、箱は空です。  
この箱に対して、以下の $ 2 $ 種類の操作を合計 $ Q $ 個、入力で与えられた順に施します。

> \+ $ x $

タイプ $ 1 $ : 箱の中に整数 $ x $ の書かれたボールを $ 1 $ つ追加する。

> \- $ x $

タイプ $ 2 $ : 箱の中にある、整数 $ x $ の書かれたボールを $ 1 $ つ取り除く。  
**但し、取り除く前の時点で箱の中に整数 $ x $ が書かれたボールが含まれることが保証されます。**

各操作後の箱に関して、以下の問題を解いてください。

> 箱からボールをいくつか取り出して、ボールに書かれた整数の総和を $ K $ とする方法の総数を $ 998244353 $ で割った余りを求めてください。  
> 但し、箱の中に入っている全てのボールは区別可能です。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ Q\ \le\ 5000 $
- $ 1\ \le\ K\ \le\ 5000 $
- タイプ $ 1 $ の操作に関して、 $ 1\ \le\ x\ \le\ 5000 $
- 全ての操作は問題文中の条件を満たす。

### Sample Explanation 1

この入力には、操作が $ 15 $ 個含まれます。 最後の操作の後、箱の中に入ったボールは $ (5,10,1,3,1,7,4) $ となります。 総和を $ 10 $ にする方法は以下の $ 5 $ 通りです。 - $ 5+1+3+1 $ ( $ 1,3,4,5 $ 番目のボールを取り出す ) - $ 5+1+4 $ ( $ 1,3,7 $ 番目のボールを取り出す ) - $ 5+1+4 $ ( $ 1,5,7 $ 番目のボールを取り出す ) - $ 10 $ ( $ 2 $ 番目のボールを取り出す ) - $ 3+7 $ ( $ 4,6 $ 番目のボールを取り出す )

## 样例 #1

### 输入

```
15 10
+ 5
+ 2
+ 3
- 2
+ 5
+ 10
- 3
+ 1
+ 3
+ 3
- 5
+ 1
+ 7
+ 4
- 3```

### 输出

```
0
0
1
0
1
2
2
2
2
2
1
3
5
8
5```

# 题解

## 作者：Genius_Star (赞：12)

### 题意：

有一个箱子，每次可以向里面添加或拿走一个数，问每次操作后，任选箱子里的数加在一起，和等于 $k$ 的方法数是多少？

### 思路：

~~可惜赛时没开 F，真的很简单……~~

注意到 $q$ 和 $k$ 都很小，只有 $5000$，说明 $O(q \times k)$ 可过。

因为涉及到计数问题，考虑动态规划，定义 $dp_i$ 为和等于 $i$ 的方案数，初始状态为 $dp_0=1$。

对于每次添加的数，状态转移方程为 $i \ge x,dp_i \to dp_i + dp_{i-x}$，就是说 $i$ 的方案数可以从 $i-x$ 转移过来（因为可以加上 $x$），而且注意，要倒序枚举 $i$，正序的话方案数会多计算。

对于每次减去的数，状态转移方程为 $i \ge x,dp_i \to dp_i - dp_{i-x}$，就是说，在 $i-x$ 这个数这里，没有 $x$ 的话，是加不到 $i$ 那里去的，所以要减去 $dp_{i-x}$（有重复的 $x$ 也是一样的，只会将其中一个 $x$ 的贡献减掉）。

对于每次询问之后，输出 $dp_k$ 即可。

时间复杂度为：$O(q \times k)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=5050,mod=998244353;
ll read(){
	ll x;
	scanf("%lld",&x);
	return x;
}
void write(ll x){
	printf("%lld",x);
}
char op;
ll q,x,k;
ll dp[N];
int main(){
	q=read(),k=read();
	dp[0]=1;
	while(q--){
		cin>>op;
		x=read();
		if(op=='+'){
			for(int i=k;i>=x;i--)
			  dp[i]=(dp[i]+dp[i-x])%mod;
		} 
		else if(op=='-'){
			for(int i=x;i<=k;i++)
			  dp[i]=(dp[i]-dp[i-x]+mod)%mod;
		}
		write(dp[k]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Register_int (赞：12)

AtCoder 出的什么神秘题目。

首先这玩意严格强于普通 0/1 背包求方案，所以 $\log$ 做法啥的可以别看了。

考虑往里面插入一个元素 $x$，实际上就是 $dp_i\leftarrow dp_i+dp_{i-x}$，这个转移显然是线性的。我们可以发现，加入顺序不会影响方案统计，所以删除元素时倒着把方案减掉即可。时间复杂度 $O(nm)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;
const int MAXN = 5e3 + 10;

int n, m; ll dp[MAXN];

char opt[2]; int k;

int main() {
	for (scanf("%d%d", &n, &m), *dp = 1; n--;) {
		scanf("%s%d", opt, &k);
		if (*opt == '+') for (int i = m; i >= k; i--) dp[i] = (dp[i] + dp[i - k]) % mod;
		else for (int i = k; i <= m; i++) dp[i] = (dp[i] - dp[i - k] + mod) % mod;
		printf("%lld\n", dp[m]);
	}
}
```

---

## 作者：不知名用户 (赞：8)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc321_f)。

注意取模！注意取模！注意取模！我吃了一罚。

题意：给一个箱子，有 $Q$ 次操作，每次可以从中取出或放入带数字的球，其数字为 $x$。求在每次操作后有多少种方案取出一些球使得这些球上面的数字和为 $K(K\le5000)$。（区分球不区分顺序，也就是说两种方案不同当且仅当一个球在一个方案取了另一个没取）

如果只有放入操作，那么就是 01 背包求方案数的板题，设 $f_i$ 表示凑出 $i$ 的方案数，从大到小执行 `f[i] += f[i-x]` 即可。

如果在放入之后立即删除，由于放入是从大到小更新，后更新的要先撤销，所以从小到大执行 `f[i] -= f[i-x]` 即可。

那么不是立即删除呢？我们也可以这样做。因为只要箱子里的球相同，那么 `f` 数组相同（从数组的实际意义出发易知），我们就可以“认为”删除的是最后插入的。

核心代码（注意取模！注意取模！注意取模！）：

```cpp
if(op=='+')
	for(i=k;i>=x;i--)
		f[i] = (f[i] + f[i-x]) % mod;
else
	for(i=x;i<=k;i++)
		f[i] = (f[i] - f[i-x] + mod) % mod;
```

[AC Code](https://atcoder.jp/contests/abc321/submissions/45843990)。

---

## 作者：Drimpossible (赞：3)

## 题意：
给定 $k,q(1 \leq k,q \leq 5000)$，一共有 $q$ 次操作，每次操作是加入或删除集合里的一个数 $x$（开始是空集），对于每次操作，回答当前集合内的数凑出 $k$ 的方案数（保证不会在集合为空的时候删数）

## 思路：
看到凑出 $k$ 的方案数，我们想到背包 DP。又因为数据范围只有 $5000$，我们考虑用 $O(qk)$ 的时间复杂度来解决这个问题。

设 $dp_i$ 表示能凑出 $i$ 的方案数，初始时 $dp_0 = 1$，然后我们分情况 DP

1. 若当前为 $+$，那么 $x$ 只会对大于 $x$ 的 $i$ 的 $dp$ 值产生影响，就用类似 $01$ 背包的方法倒着枚举 $i$ 加上原来的 $dp_{i-x}$ 
2. 若当前为 $-$，那么 $x$ 同样也只会对大于 $x$ 的 $i$ 的 $dp$ 值产生影响，但是这里我们应该正着枚举 $i$。因为我们要减去的是在去掉了一个 $x$ 之后的方案数，应该先把小的减掉 $x$ 产生的贡献再向大的递推，这样我们计算的就是在去掉 $x$ 之后的方案数了

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
typedef pair<int,int> pii;
inline int read(){
	int s=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		s=(s<<1)+(s<<3)+(c^48);
		c=getchar();
	}
	return s*f;
}
const int N=5005;
const int mod=998244353;
int q,k,x,dp[N];
multiset<int>s;
void add(int &x,int y){
	x+=y;
	if(x>mod)x-=mod;
}
void del(int &x,int y){
	x-=y;
	if(x<0)x+=mod;
}//取模的加减函数
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	q=read(),k=read();
	char op;
	dp[0]=1;
	for(int i=1;i<=q;i++){
		cin>>op;x=read();
		if(op=='+'){
			for(int j=k;j>=x;j--)
				add(dp[j],dp[j-x]);
			cout<<dp[k]<<endl;
		}
		else {
			for(int j=x;j<=k;j++)
				del(dp[j],dp[j-x]);
			cout<<dp[k]<<endl;
		}
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
/**/

```


---

## 作者：liyujia (赞：2)

### 题意

有一个可重集合 $S$，初始为空。每次往 $S$ 中增添或删除一个元素，求在每次操作后 $S$ 的和为 $K$ 的子集的个数。不同位置元素构成相同集合视为不同子集。

操作次数，不超过 $5000$，$K$ 和操作中的元素均不超过 $5000$，保证操作合法。

### 解法

这十分甚至九分地像一个生成函数的形式，把它写出来，则答案的生成函数为

$$\prod_{i\in S} (1+x^i)$$

它的 $x^K$ 项系数就是答案。$x^{K+1}$ 以上的系数显然可以忽略。

赛时妄想用 NTT 直接求能过，浪费 25min，外加一发罚时，警钟长鸣，不要低估 NTT 等的常数。

你发现这个东西多乘上一个元素 $a$ 是容易处理的，直接暴力乘到原多项式中，就是 $O(K)$ 的。

然后考虑删去元素 $a$ 是该怎么处理。

设删去 $a$ 后的多项式为 $A$，则对于原多项式 $B$，有：

$$A+x^aA=B$$

放到每一项系数中，就有

$$B_i=A_i+A_{i-a}$$

其中 $A_i,B_i$ 分别表示 $A,B$ 中 $x^i$ 项的系数。

显然有 $A_i=B_i-A_{i-a}$，直接从小到大每项处理即可。

时间复杂度 $O(QK)$，其中 $Q$ 是操作个数。

### 代码

极度舒适。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#pragma GCC optimize(2)
using namespace std;
const int mod = 998244353;
int a[5005], k, q;//a[i] 是多项式的系数
int main(){
	cin >> q >> k;
	a[0] = 1;
	while(q--){
		char op;
		int x;
		cin >> op >> x;
		if(op == '+')
			for(int i = 5000; i >= x; i--)	
				(a[i] += a[i - x]) %= mod;
		else
			for(int i = x; i <= 5000; i++)
				(a[i] += mod - a[i - x]) %= mod;
		//注意顺序，一正一反
		cout << a[k] << endl;
	}
	return 0;
}
```

---

## 作者：min_inf (赞：2)

可以离线，考虑大力线段树分治。

用一个栈记录在每个节点做背包时的修改，回溯时回退即可。

时间复杂度 $O(qk \log q)$，可能写得不好会过不了，没怎么卡常跑到了 1.7s。

```cpp
namespace KnownError_{
    using ui = unsigned int;
    using ll = long long;
    using ull = unsigned long long;
    stack<pair<int*,int>>stk;
    void ass(int &x,int y){
        stk.push({&x,x});
        x=y;
    }
    void rb(){
        auto x=stk.top();
        stk.pop();
        *x.first=x.second;
    }
    const int mod = 998244353;
    const int N = 5005;
    int q,k;
    stack<int> st[N];
    vector<int> vec[N<<1];
    int f[N];
    void add(int u,int L,int R,int l,int r,int x){
        if(r<L||R<l)return;
        if(l<=L&&R<=r){
            vec[u].push_back(x);
            return;
        }
        int M=L+R>>1,ls=M<<1,rs=M<<1|1;
        add(ls,L,M,l,r,x);
        add(rs,M+1,R,l,r,x);
    }
    void dfs(int u,int L,int R){
        int pre=stk.size();
        for(auto x:vec[u])
            for(int i=k;i>=x;--i)
                ass(f[i],(f[i]+f[i-x])%mod);
        if(L==R)cout<<f[k]<<'\n';
        else{
            int M=L+R>>1,ls=M<<1,rs=M<<1|1;
            dfs(ls,L,M);
            dfs(rs,M+1,R);
        }
        while(stk.size()>pre)rb();
    }
    void main(){
        cin>>q>>k;
        for(int i=1;i<=q;++i){
            char op;
            int x;
            cin>>op>>x;
            if(op=='+')st[x].push(i);
            else{
                int l=st[x].top();
                st[x].pop();
                add(1,1,q,l,i-1,x);
            }
        }
        for(int i=1;i<=k;++i){
            while(!st[i].empty()){
                int l=st[i].top();
                st[i].pop();
                add(1,1,q,l,q,i);
            }
        }
        f[0]=1;
        dfs(1,1,q);
    }
}
```


---

## 作者：sunzz3183 (赞：2)

# [ABC321F] #(subset sum = K) with Add and Erase 题解

## 题意

我们有一个盒子，最初是空的。  

让我们按照输入中给出的顺序，总共执行以下两种类型的 $Q$ 个操作。

`+ x`

输入 $1$：在盒子里放一个写有整数 $x$ 的球。

`- x`

输入 $2$：从盒子里取出一个写有整数 $x$ 的球。 

**保证在操作前盒子里有一个写有整数 $x$ 的球**。

对于每次操作后的盒子，请解决以下问题。

> 求从盒子中拾取若干个球，使写在球上的整数之和为 $K$ 的方案数，对 $998244353$ 取模。

> 盒子中的所有球都是不同的。

## 分析

退背包裸题。

考虑令 $f_i$ 表示选总体积为 $i$ 的物品的方案数。

对于空背包有 $f_0=1,f_{1\dots m}=0$ 。

往背包添加一个体积为 $v$ 的物品：

```cpp
for(i=m;i>=v;i--)f[i]+=f[i-v];
```

则反过来，从背包删除一个体积为 v 的物品：

```cpp
for(i=v;i<=m;i++)f[i]-=f[i-v];
```

添加与删除的时间复杂度均为 $O(m)$。

总时间复杂度 $O(qm)$（即题目中的 $O(qk)$）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=5002,mod=998244353;
int q,k,f[N];
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    q=read();k=read();
    f[0]=1;
    while(q--){
        char s[2];
        scanf("%s",s);
        int x=read();
        if(s[0]=='+')
            for(int i=k;i>=x;i--)
                (f[i]+=f[i-x])%=mod;
        else
            for(int i=x;i<=k;i++)
                (f[i]+=mod-f[i-x])%=mod;
        printf("%lld\n",f[k]);
    }
    return 0;
}
```

---

## 作者：szhqwq (赞：1)

## $\tt{Solution}$

考虑 dp。

设 $dp_i$ 表示凑出数字 $i$ 的方案数。

每当有球加进盒子里来，令 $x$ 为球上写的数字，为了使答案无后效性，从后往前更新状态：$dp_i \gets dp_i + dp_{i - x}$。

每当有球从盒子里出去，则从前往后更新状态：$dp_i \gets dp_i - dp_{i - x}$。

**注意：球从盒子里出去时的转移为了防止负数的出现，需要加上模数。**

[Link](https://atcoder.jp/contests/abc321/submissions/45883795)

---

## 作者：Xy_top (赞：1)

水题，加数是个背包，下面考虑减数。

对于 $f_i$，现在删除 $x$，我们希望把里面用了 $x$ 的方案抠出来怎么办呢？这一部分的方案显然是不用 $x$（或者说少用一个 $x$）拼成 $f_{i-x}$ 的方案对吧。

然后问题来了，少用一个 $x$ 的 $f_{i-x}$ 怎么求呢？也很简单，顺次循环从 $x\cdots n$ 求即可，其中 $f_1\cdots f_{x-1}$ 这些少不少用是没关系的。

代码（没取模吃了一发太可惜了）：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
#define re return
#define mp make_pair
#define pb push_back
#define pf push_front
#define pi pair <int, int>
using namespace std;
int q, k;
char c;
int x;
int f[5005], g[5005];
const int mod = 998244353;
void solve () {
	cin >> q >> k;
	f[0] = 1;
	while (q --) {
		cin >> c >> x;
		if (c == '+') foR (i, 5000, x) f[i] = (f[i] + f[i - x]) % mod;
		else For (i, x, 5000) {
			f[i] -= f[i - x];
			f[i] += mod;
			f[i] %= mod;
		}
		cout << f[k] << '\n';
	}
}
signed main () {
	ios :: sync_with_stdio (false);
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}

```


---

## 作者：Zi_Gao (赞：1)

## 前言

现场发明了个“可撤销背包”记录一下。

## 正文

### 0x00 题目分析

实现一个维护一个可重集，每次可能加入或删除一个元素，求当前有多少子集元素和为 $k$，无非就是一个 01 背包带了一个删除嘛。这里需要读者会使用正常一维的 01 背包。

考虑简单的要删除的元素是上一次添加的，那么按照加入元素跑背包的方式反着跑一次，加上的值反着减回去，这里不理解的可以等会看看代码，还原出原来的背包。现在考虑删除的元素不是上一次加入的元素，不妨想加入元素操作具有交换律，无论这个元素在哪个时候加入都可以默认为最后加入的。还是一样反转跑个背包就行。

### 0x01 代码实现

由于加入元素要倒序枚举，那么若加入的元素是 $x$，会倒序影响 $dp$ 背包数组中 $\left[x,k\right]$ 区间的值，对于每一个 $dp_i\leftarrow dp_i+dp_{i-k}$。那么还原直接正着一次还原出来原来的值，$dp_i\leftarrow dp_i-dp_{i-k}$，这里正确性是因为，在还原更大的 $i$ 时较小的 $i$ 已经被还原，而 $\left[0,k\right)$ 以开始没有变化就是对的。

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

long long dp[5010];
const long long mod=998244353;

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register char c;
    register int i,j,x;
    int q=read();
    int k=read();
    dp[0]=1;
    while(q--){
        loop:c=getchar();
        if(c!='-'&&c!='+') goto loop;
        x=read();
        if(c=='-')//正着枚举减回去
            for(i=0;i+x<=k;++i) (dp[i+x]+=mod-dp[i])%=mod;
        else//倒序枚举跑背包
            for(i=k;i>=x;--i) (dp[i]+=dp[i-x])%=mod;
        print(dp[k]);puts("");
    }
    

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

可撤销背包板子。

首先问题是用当前所拥有的数的集合凑出 $x$ 的方案数。

这个问题明显可以背包解决，即 $dp_j \leftarrow dp_j + dp_{j - a_i}$。

但是，此问题中物品有可能会被删除，即变为了一个动态的问题，如果直接暴力计算时间复杂度为 $\Theta(qn^2)$。

那么，我们转化一下思路，如果我们使每一次变化的数 $x$ 都假令为 $a$ 中的最后一个元素。因为 0-1 背包对于数的先后顺序无关，所以此假令不会影响答案。

然后，再想一下 0-1 背包的板子，我们已经假令 $x$ 为 $a$ 中最后一位元素，如果 $a$ 的大小为 $m$，那么我们在枚举 $i$ 时，当 $i$ 在 $[1,m)$ 范围内时，此时更新的 DP 数组与原 DP 数组的值不变。

因此，我们只需要考虑 $x$ 带来的贡献，我们将两种操作分开考虑。

## Part 1 添加操作

因为是在 0-1 背包里面取出最后一个元素，所以与 0-1 背包相同。

```cpp
for (re int i = n;i >= x;i--) dp[i] = Add(dp[i],dp[i - x]);
```

## Part 2 删除操作

因为是删除，所以枚举的顺序也不同。

设想如果按照正常 0-1 背包的顺序枚举，当此时删除 $2$ 时，如果能删除 $dp_9$ 就会被 $dp_7$ 所影响，但如果 $a$ 中只有一个 $2$，显然 $dp_9$ 无法取到。

那么当倒序循环时，$dp_9$ 会在 $dp_7$ 之后计算到。

```cpp
for (re int i = x;i <= n;i++) dp[i] = Sub(dp[i],dp[i - x]);
```

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 5010,mod = 998244353;
int q,n;
int dp[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int Add(int a,int b){
	return (a + b) % mod;
}

inline int Sub(int a,int b){
	return ((a - b) % mod + mod) % mod;
}

signed main(){
	dp[0] = 1;
	q = read();
	n = read();
	while (q--){
		int x;
		char op[10];
		scanf("%s",op);
		x = read();
		if (op[0] == '+'){
			for (re int i = n;i >= x;i--) dp[i] = Add(dp[i],dp[i - x]);
		}
		else{
			for (re int i = x;i <= n;i++) dp[i] = Sub(dp[i],dp[i - x]);
		}
		printf("%lld\n",dp[n]);
	}
	return 0;
}
```

---

## 作者：CarroT5656 (赞：0)

**题目大意**

让你维护一个数列，有 $q$ 次操作，每次增/删一个数。每次操作完，让你求出有多少个不同的选数方案，使得其和恰好为 $k$。答案对 $998244353$ 取模。

**解法分析**

你考虑如果序列是不变的，该怎么处理。

显然就是一个很板的 01 背包，可以在 $O(nk)$ 的时间复杂度求出。

令 $f_i$ 表示和恰好为 $i$ 的方案数。

那么你在每次加入一个数的时候，显然因为你前面的若干个数都已经处理过了。
所以你只需要额外 $O(k)$ 的时间，就可以将这个数插入。

删除也是同理。你只需要减掉这个数对答案的贡献即可。

时间复杂度为 $O(qk)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
#define N 5005
ll q,k,t,dp[N]={1};
char op;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>q>>k;
	for(ll i=1;i<=q;i++){
		cin>>op>>t;
		if(op=='+'){
			for(ll i=k;i>=t;i--) (dp[i]+=dp[i-t])%=mod;
		}
		else{
			for(ll i=t;i<=k;i++) dp[i]=(dp[i]-dp[i-t]+mod)%mod;
		}
		printf("%lld\n",dp[k]);
	}
	return 0;
}
```

---

## 作者：Cindy_Li (赞：0)

可撤销背包的模板题。

如果没有减操作就是 $01$ 背包，众所周知转移方程是 $f[i]=f[i]+f[i-v]$。

考虑减操作，对于一个重量 $i$，不选物品 $v$ 的方案数是什么呢？

发现我们只需要把选 $v$ 的方案去掉就好，那么转移方程就是 $f[i]=f[i]-f[i-v]$。

于是就做完了。

注意取模变正等等问题。

--------

关于循环顺序：

- 加操作应该用“$i-v$ 不含 $v$”更新，倒序循环。
- 减操作也要用“$i-v$ 不含 $v$”更新，正序循环（先去掉前面的 $v$）。

--------

code:

```c++
f[0]=1;
rep(i,q){
	cin>>op>>x;
	if(op=='+')
		for(int j=k;j>=x;j--) f[j]=pls(f[j],f[j-x]);
	else for(int j=x;j<=k;j++) f[j]=mns(f[j],f[j-x]);
	printf("%d\n",f[k]);
}
```

附比较漂亮的取模运算：

```c++
inline int pls(int a,int b){
	return (a+b>=mod?a+b-mod:a+b);
}
inline int mns(int a,int b){
	return (a-b<0?a-b+mod:a-b);
}
```

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

有一个箱子，有两种操作，往里加球或者拿球出来，你需要求出每次操作后取出箱子里的一些球（不是真正取出）使和恰好为 $K$ 的方案数量。

## 解题思路

看到 $Q\times K = 2.5\times10^7$ 的时候就可以考虑暴力背包了。

对于加球，正着跑背包。

对于减球，倒着跑背包（这个叫退背包，参考消失之物那道题）。

输出数组第 $K$ 项即可。

[提交记录](https://atcoder.jp/contests/abc321/submissions/45857943)


---

## 作者：Meteor_ (赞：0)

# AT_abc321_f [ABC321F] #(subset sum = K) with Add and Erase 题解

## 题目大意

现在有一个空箱子。给你两个数 $Q, K$，然后给你 $Q$ 行，每一行代表一个操作：

- $+ x$，即向箱子里加一个权值为 $x$ 的小球。

- $- x$，即从箱子里把权值为 $x$ 的小球拿一个出来。保证合法，即箱子里一定有权值为 $x$ 的小球。

每一次操作后你都需要输出存在多少种拿球的方案，使得你拿出的所有球的权值和为 $K$。答案对 $998244353$ 取模。

$1 \le Q, K, x \le 5000$


## 题解

如果不是动态的话，明显是普通的 0-1 背包问题。

考虑怎么让 0-1 背包变得动态。

我们发现这其实就是一个加减物品的操作。

加物品非常简单，就是再在原基础上跑一遍 dp。

```cpp
            for(int i = 5000; i >= x; -- i)
                if(dp[i - x])
                    dp[i] = (dp[i] + dp[i - x]) % mod;
```

减物品其实也不难。就相当于跑了一遍**反着的加物品**。换句话说，就是你要在原有的方案上，减去这个物品贡献的方案。

```cpp
            for(int i = x; i <= 5000; ++ i)
                if(dp[i - x])
                    dp[i] = (dp[i] - dp[i - x] + mod) % mod;
```

注意一些细节。加物品需要从大往小枚举，防止算重，和普通 0-1 背包一样。而减物品需要为了防止算重需要从小到大枚举。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define M 5005
#define mod 998244353

using namespace std;

int Q, K, dp[M], x;
char ch;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> Q >> K;
    dp[0] = 1;
    for(int i = 1; i <= Q; ++ i) {
        cin >> ch >> x;
        if(ch == '+') {
            for(int i = 5000; i >= x; -- i)
                if(dp[i - x])
                    dp[i] = (dp[i] + dp[i - x]) % mod;
        }
        else
            for(int i = x; i <= 5000; ++ i)
                if(dp[i - x])
                    dp[i] = (dp[i] - dp[i - x] + mod) % mod;
        cout << dp[K] << '\n';
    }
}
```

---

## 作者：happybob (赞：0)

这不可撤销背包板子吗。

设 $f_i$ 表示凑出 $i$ 方案数。

加的时候加一下，删的时候减一下，注意两个循环顺序不一样，具体可以看代码理解。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 5e5 + 5, MOD = 998244353; // Remember to change

int n, k, q, t, a[N];
int dp[N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	set<int> v;
	cin >> t >> k;
	dp[0] = 1;
	while (t--)
	{
		char op;
		cin >> op;
		if (op == '+')
		{
			int x;
			cin >> x;
			v.insert(x);
			for (int i = k; i >= x; i--)
			{
				dp[i] += dp[i - x];
				dp[i] %= MOD;
			}
		}
		else
		{
			int x;
			cin >> x;
			v.erase(x);
			for (int i = x; i <= k; i++)
			{
				dp[i] -= dp[i - x];
				dp[i] %= MOD;
				dp[i] += MOD;
				dp[i] %= MOD;
			}
		}
		cout << dp[k] << "\n";
	}
	return 0;
}


```


---

## 作者：FReQuenter (赞：0)

我们考虑加入一个数字 $x$ 会产生什么影响：所有当前已经可以达成的数值再往上加 $x$ 也都可以获得。

一样的道理，删除的时候只需要将所有可以达成的数 $i$ 减去达成 $i-x$ 的方案数就可以了。

注意加入需要倒序循环，不然的话就会无限加 $x$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int q,k,f[5005];
void add(int x){
    for(int i=k;i>=x;i--) f[i]+=f[i-x],f[i]%=mod;
}
void del(int x){
    for(int i=x;i<=k;i++) f[i]-=f[i-x],f[i]+=mod,f[i]%=mod;
}
signed main(){
    f[0]=1;
    cin>>q>>k;
    while(q--){
        char c;
        int x;
        cin>>c>>x;
        if(c=='+') add(x);
        else del(x);
        cout<<f[k]<<endl;
    }
}
```

---

## 作者：Loser_Syx (赞：0)

典题。

题面说白了就是维护一个可撤销背包。

如果是 `+` 操作，就需要倒序枚举数去累加答案，$f_i \rightarrow f_i + f_{i-x}$。

如果是 `-` 操作，就需要考虑撤销掉操作，也就是把 `+` 操作反着写，变成正序枚举删除答案，$f_i \rightarrow f_i - f_{i-x}$。

注意边界 $f_0 = 1$ 和取模。

[代码](https://atcoder.jp/contests/abc321/submissions/45879724)。

---

## 作者：incra (赞：0)

第一做出 F 题欸。~~E，F 顺序错了 awa。~~
### [题目链接](https://www.luogu.com.cn/problem/AT_abc321_f)
### 题意
略。
### 题解
考虑没有 `-` 的情况，我们只需要用 01 背包就能解决了。

接下来考虑 `-` 的情况。

其实稍加思考就能发现，`-` 操作就是撤销前面对应的 `+` 操作，思路就讲完了。

注意一维数组 DP 时，撤销和添加循环方向是相反的。
### 代码
```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
const int N = 5010,MOD = 998244353;
int q,n;
LL f[N];
int main () {
	cin >> q >> n;
	f[0] = 1;
	while (q--) {
		char op;
		int x;
		cin >> op >> x;
		if (op == '+') {
			for (int i = n;i >= x;i--) f[i] = (f[i] + f[i - x]) % MOD;
		}
		else {
			for (int i = x;i <= n;i++) f[i] = ((f[i] - f[i - x]) % MOD + MOD) % MOD;
		}
		cout << f[n] << endl;
	}
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# 思路

简单动态规划，$dp_i$ 指当前操作后取和为 $i$ 的球的方案数，每次输出 $dp_K$ 即可。

需要注意的是对于每次 `+ x` 操作，计算 $dp$ 数组时要倒着循环。 

时间复杂度：$O(QK)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[5010];
int main(){
	long long q,k; scanf("%lld %lld",&q,&k);
    dp[0]=1;
	for(int i=1;i<=q;i++){
		char c;
		long long x;
		scanf("%c",&c);
		while(c!='+'&&c!='-')scanf("%c",&c);
		scanf("%lld",&x);
		if(c=='+')
			for(long long j=5004;j>=x;j--)
				dp[j]=(dp[j]+dp[j-x]+998244353)%998244353;
		else
			for(long long j=x;j<=5004;j++)
				dp[j]=(dp[j]-dp[j-x]+998244353)%998244353;
		printf("%lld\n",dp[k]);
	}
    return 0;
}
```

---

