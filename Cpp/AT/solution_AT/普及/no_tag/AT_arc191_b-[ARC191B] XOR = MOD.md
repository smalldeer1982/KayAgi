# [ARC191B] XOR = MOD

## 题目描述

给定正整数 $N, K$。若正整数 $X$ 满足以下条件，则称其为**与 $N$ 兼容的数**：

- $X$ 与 $N$ 的异或值等于 $X$ 除以 $N$ 的余数，即 $X \oplus N = X \bmod N$。

请判断是否存在至少 $K$ 个与 $N$ 兼容的数。若存在，请输出其中第 $K$ 小的数。

给定 $T$ 个测试用例，请分别计算每个用例的答案。

**异或的定义**：非负整数 $A, B$ 的异或 $A \mathrm{XOR} B$ 定义如下：

- $A \mathrm{XOR} B$ 的二进制表示中第 $2^k$（$k \geq 0$）位的值为 $1$，当且仅当 $A$ 和 $B$ 在二进制表示的第 $2^k$ 位中有且仅有一个为 $1$，否则为 $0$。

例如，$3 \mathrm{XOR} 5 = 6$（二进制表示为：$011 \mathrm{XOR} 101 = 110$）。

## 说明/提示

### 约束条件

- $1 \leq T \leq 2 \times 10^5$
- $1 \leq N, K \leq 10^9$
- 输入均为整数

### 样例解释 1

以 $N = 2$ 为例：
- 当 $X = 1$ 时，$X \oplus N = 3$，而 $X \bmod N = 1$，因此 $1$ 不是与 $N$ 兼容的数。
- 当 $X = 2$ 时，$X \oplus N = 0$，而 $X \bmod N = 0$，因此 $2$ 是与 $N$ 兼容的数。
- 当 $X = 3$ 时，$X \oplus N = 1$，而 $X \bmod N = 1$，因此 $3$ 是与 $N$ 兼容的数。

综上，与 $2$ 兼容的数中第 $1$ 小的正整数是 $2$，第 $2$ 小的正整数是 $3$。因此第一个测试用例的答案为 $2$，第二个测试用例的答案为 $3$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
2 1
2 2
1 7
20250126 191```

### 输出

```
2
3
-1
20381694```

# 题解

## 作者：ARIS2_0 (赞：3)

前序：[小 S 的 ARC191 参赛记-1（即 ARC191A 题解）](https://www.luogu.com.cn/article/yib7ydbv)

切掉了 A 后，小 S 十分愉快地开了 B。

---

### 大致题意

给定 $n,k$，求第 $k$ 大的 满足 $x\bmod n=x\oplus n$ 的 $x$，无解输出 $-1$，多测。

---

小 S 看到这道题也是十分兴奋啊，想了一下立马口胡了个结论：

- 当 $x<n$ 或 $x$ 二进制下的最高位高于 $n$ 二进制下的最高位时，没有一个 $x$ 满足条件。

因为这是题解不是赛时，所以小 S 还是要证一下的。

首先，$x<n$ 时，原式变为 $x=x\oplus n$，很明显当且仅当 $n=0$ 时成立，而 $n$ 显然不能为 $0$。

其次，如果 $x$ 二进制下的最高位高于 $n$ 二进制下的最高位时，那么有 $x\oplus n>n$（因为 $x$ 二进制下的最高位会被保留），而 $x\bmod n<n$，所以原式不成立。

那么，因为 $x\ge n$ 且 $x$ 的二进制下的最高位不高于 $n$ 二进制下的最高位时，所以有 $n\le x<2\times n$，则 $x\bmod n=x-n$。

那也就是说，如果 $n$ 在二进制下某位是 $1$，则 **$x$ 在二进制下这位也必须是 $1$**，不然无法实现 $x-n=x\oplus n$。

小 S 高兴的不得了，因为他发现，这意味着 $x$ 在二进制下，可以自由变化的那些位置，**恰好就是 $n$ 的二进制下不大于最高位的、值为 $0$ 的位数**。设这样的位数有 $sum$ 个，则有 $2^{sum}$ 个不同的 $x$。

至于如何计算第 $k$ 大的 $x$，将 $k-1$ 二进制拆分之后一位位填到 $sum$ 个自由位上去就可以了。

于是小 S 愉快地无伤通过了此题，真是与 ARC189B 的 -10 截然不同的结局啊。

也许，这就是小 S 每天殷切地对着卫星许愿的原因吧。

**S.A.T.E.L.L.I.T.E.**

（但是小 S 还是被 C 的神秘结论创飞了）

### Code

```cpp
#include<algorithm>
#include<bitset>
#include<deque>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector> 
#include<chrono>
#include<random>
#include<tuple>
#include<unordered_map>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,maxn=1e6+10;
namespace ARIS2_0{
    void solve(){
        int n,k;cin>>n>>k;
        vector<int>v;
        for(int i=0;(1ll<<i)<=n;i++){
            if(!((n>>i)&1))v.push_back(i);
        }
        if(k>(1ll<<(v.size()))){
            cout<<"-1\n";
            return;
        }
        int ans=n;
        k--;
        for(int i=0;i<v.size();i++){
            if((k>>i)&1){
                k-=(1ll<<i);
                ans+=(1ll<<(v[i]));
            }
        }
        cout<<ans<<"\n";
    }
}
signed main(){
    //freopen("data.in","r",stdin);
    //freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
    while(t--)ARIS2_0::solve();
	return 0;
}
/*
clang++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,-stack_size -Wl,512000000
*/
```

---

## 作者：tuget (赞：1)

容易发现，因为 $x \bmod  n <n$，所以 $x \oplus n <n$，故 $x < 2n$。当 $x < n$ 时，有 $x = x \oplus n$，当且仅当 $n=0$，所以 $n \le x <2n$，即 $x - n = x\oplus n$，所以有 $ x \operatorname{and} n=x $。

把 $n$ 拆位，取出为 $0$ 的位置，对于这些位置，无论填 $0,1$ 都构成合法的 $x$，对于第 $k$ 大的 $x$ 显然就是把 $k-1$ 拆位后相应的填到 $n$ 为 $0$ 的位置上。$k > 2^z$ 时直接输出 ```-1```，$z$ 为 $n$ 二进制最高位以下 $0$ 的个数。

挺抽象，详见代码：

```
int n,k,num[36],m,z,p[36],ans;
int main()
{
	int i,T=read();
	while(T--)
	{
		n=read(),k=read();
		for(m=z=0;n;++m,n>>=1){
			num[m]=n&1;
			if(num[m]==0)p[z++]=m;
		}
		--m;
		if(k>(1<<z)){puts("-1");continue;}--k;
		for(i=0;k;++i,k>>=1)num[p[i]]=k&1;
		ans=0;int mul=1;
		for(i=0;i<=m;++i)ans+=num[i]*mul,mul*=2;
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：Drifty (赞：1)

### Solution

对于一个对 $(X, N)$，我们考虑什么时候它们是相容的（这里的**相容**是从英文题面中的 **compatible** 翻译过来的，即满足 $X\bmod N=X\oplus N$）。

- 当 $X < N$ 时，$X\bmod N = X$，因此想要满足 $X\oplus N = X\bmod N = X$，$N$ 必须是 $0$ 这是矛盾的。
- 当 $X \ge 2N$ 时，$X$ 在二进制上一定比 $N$ 高一位，因此 $X\oplus N \ge N$ 又因为 $X\bmod N < N$ 所以矛盾。

因此 $N \le X < 2N$。

此时 $X\bmod N = X - N$，原题目等价于 $X - N = X \oplus N$。

我们会发现，对于每二进制位，只有 $0 - 1 \neq 0 \oplus 1$ 因此合法的 $(X, N)$ 中不能出现这样的位。

回到本题，实际上等价于在所有 $N$ 最高位 $1$ 后的 $0$ 都可以换成 $1$ 的前提下的第 $K$ 大，这就很好做了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);
    int T;
    i64 n, k;
    for (cin >> T; T --; ) {
        cin >> n >> k; k --;
        bitset <32> tmp(n);
        int p = 0, cnt = 0;
        for (p = 31; ~p; p --) if (tmp[p]) break;
        for (int i = 0; i < p; i ++) if (tmp[i] == 0) cnt ++;
        i64 mmax = 1ll << cnt;
        if (k >= mmax) {cout << -1 << '\n'; continue;}
        bitset <32> j(k);
        int cur = 0;
        for (int i = 0; i < p; i ++) if (tmp[i] == 0) tmp[i] = j[cur ++];
        cout << tmp.to_ulong() << '\n';
    }
    return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

## 思路
阅读前提：取模优先级强于加减优先级强于异或优先级。

显然根据运算定义有 $x-y\le x\ \text{XOR}\ y\le x+y$
$$
\because X\ \text{XOR}\ N=X\bmod N\\
\therefore X=X\bmod N\ \text{XOR}\ N\\
\because X\bmod N<N\\
\therefore X<2N\\
$$
显然 $X\ge N$，所以 $N\le X<2N$，$X\bmod N=X-N$。

综上，$X-N=X\ \text{XOR}\ N$。

容易发现 $X-N=X\ \text{XOR}\ N$ 当且仅当 $N$ 为 $1$ 的二进制位上，$X$ 也全为 $1$。只有这样才能使每一位 $N_i=1$ 异或的时候都变为 $0$。

而反过来，$X$ 可以自由决定一个二进制位当且仅当 $N$ 在此位上为 $0$ **且 $N$ 大于这一位表示的数字**。

令满足这个条件的二进制位有 $M$ 个，则合法的 $X$ 有 $2^M$ 个。若要寻找其中第 $K$ 大者，有一种巧妙的方法：\
$K\leftarrow K-1$，然后把 $K$ 对应的二进制位依次填进 $X$ 未确定的位中（未确定的最低位填最低位，未确定的第二位填第二位，以此类推）。

时间复杂度 $O(T\log N)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,ans;
vector<int>v;
int main(){
	scanf("%d",&T);
	while(T --){
		ans = 0;
		v.clear();
		scanf("%d%d",&n,&k);
		for(int i = 0;i <= 30;i ++) if(n >= (1 << i) && !(n & (1 << i))) v.push_back(i);//n 为 0 的位为未确定的位
		if(k > (1 << v.size())){
			printf("-1\n");
			continue;
		}
		k --;
		for(int i = 0;i < v.size();i ++){
			if(k & 1) ans += (1ll << v[i]);//k-1 在此位为 1，未确定对应位也为 1
			k >>= 1;//下一位
		}
		printf("%d\n",ans + n);//确定的位和为 n
	}
	return 0;
}
```

---

## 作者：zhangzheng2026 (赞：0)

本文其实不用同余一类的符号。  
我们考虑一下 $n$ 确定时，$x$ 的取值范围。  
- 当 $x<n$ 时：  
$$x=x\bmod n=x\oplus n$$  
得到 $n=0$，不成立。  
- 当 $x\ge n$ 时：
$$n>x\bmod n=x\oplus n\ge x-n$$  
$$n>x-n$$  
$$x<2n$$  
得到 $n\le x<2n$。  
所以 $x\bmod n=x-n$。  
然后有 $x-n=x\oplus n$，即 $n$ 二进制中一位上为一时，$x$ 在此位上的数字也为一。  
设 $x$ 的最高位表示的数为 $y$，如果 $x$ 的有效位数大于 $n$ 的有效位数，$y>n$，$x-y\ge n$，$x>2n$，不成立，所以 $x$ 的有效位数一定等于 $n$ 的有效位数。  
那么设 $n$ 的二进制有 $m$ 位为零，总方案数就为 $2^m$ 种。  
如果 $k\le 2^m$，就把 $k-1$ 转化为二进制填入 $n$ 的二进制中为零的数位上即可。  
代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k,a[35],num;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>k,num=0;
		int x=n,now=0;
		while(x)
		{
			if(x%2==0) a[++num]=now;
			now++,x/=2;
		}
		if(k>(1<<num))
		{
			cout<<-1<<'\n';
			continue;
		}
		x=k-1,now=1;
		while(x)
		{
			if(x%2) n+=(1<<a[now]);
			now++,x/=2;
		}
		cout<<n<<'\n';
	}
	return 0;
}
```

---

## 作者：complexly (赞：0)

先观察式子。

$$
x \bmod n = x \oplus n
$$

有

1. 如果 $x < n$ 那么式子退化为 $x = x \oplus n$ ， 仅当 $n = 0$ 时满足。
2. 如果 $x \ge 2n$ 那么有 $n \oplus x > n$ 因为 $x$ 最高位一定比 $n$ 的最高位高，但显然 $x \bmod n < n$ ，所以 $x \bmod n \ne x \oplus n$。

综上 $n \le x < 2n$ ，原式变为 $x - n = x \oplus n$ 。

其实就是说 $n \in x$ （在 $n$ 的二进制位上为 $1$ 的位置在 $x$ 上也为 $1$ ）， 很好证。

所以先给k减1，枚举 $n$ 的二进制位 ， 如果为 $1$ 那么必须是 $1$ ， 否则就是 $k$ 的这一位 （前面 $n$ 上有几个 $0$ 就是 $k$ 的第几位）。

注意 $x$ 的最高位不能大于 $n$ 的最高位（不然 $n \oplus x > n$ ）。

主要代码。

```
void work(){
    cin >> n >> k , k --;
    int dg = 0 , ans = 0;
    f(i , 0 , 31){
        if(1 << i > n)break;
        if((n>>i)&1)ans |= (1 << i);
        else ans |= ((k>>dg)&1)<<i , dg ++;
    }
    cout << ((1<<dg)>k?ans:-1) << "\n";
}
```

什么？你说主函数？

```
signed main(){
    int T = 1;
    cin >> T;
    while(T --)work();
}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_arc191_b 题解

## 思路

$x \bmod n$，可以看成是进行多次 $x \leftarrow x-n$，直到 $x < n$。

先考虑 $x < n$ 的情况，$x \oplus n = x \bmod n$ 即可转化为 $x \oplus n = x$，把每一位拆开，若对应位为 $0$，则 $x$ 可以为 $0$ 或 $1$，若对应位为 $1$，则 $x$ 无解，意思就是如果 $n$ 对应的二进制数出现了 $1$ 则无解，那么，很显然，$x < n$ 的情况不存在。

然后就要考虑 $x \ge n$ 的情况了。

若 $x$ 的二进制数的最高位的 $1$ 的位置比 $n$ 的大，则这种情况一定不合题意。因为这样 $x \oplus n$ 的结果的最高位的 $1$ 肯定是由 $x$ 提供的，那么 $x \oplus n > n$，而 $x \bmod n < n$，显然，无法找出一个 $x$ 满足上述条件。

于是将 $x$ 锁定在 $n \le x < 2n$ 这个范围内，不难发现，在这个限制下，$x \bmod n = x - n$，于是问题转化成了 $x \oplus n = x - n$。

先考虑 $x-n$ 造成某一位 $0-1$ 借位的情况，出现借位，则这一位 $0$ 变成 $1$，依次向更高位走，经过若干位 $0$ 也变成 $1$ 之后，找到第一个 $1$，将其变为 $0$，刚走过的这些位由于借位都会改变，那么在异或运算中体现出来就是这几个位全是 $1$，而我们只是让最低那一位减掉 $1$，这显然矛盾。

所以不会出现借位的情况，也就是说，对应位 $x$ 为 $0$ 时，$n$ 一定不为 $1$。换句话说，对应位 $n$ 为 $1$，$x$ 一定为 $1$。

那么对应位 $n=0$ 的情况呢，$x=0$ 或 $x=1$ 皆可，因为 $1 - 0 = 1 \oplus 0$，且 $0 - 0 = 0 \oplus 0$。

于是将 $n$ 每个 $1$ 的二进制位拿走，留下 $0$，对应位的 $x$ 任意填。设 $n$ 的二进制位中 $0$ 的个数为 $t$，那么一共有 $2^t$ 种结果，若 $2^t < k$，则无解。

将其看作一个 $t$ 位二进制数 $g$，那么，$g$ 从 $0$ 到 $2^t-1$ 依次枚举，就是解从小到大依次枚举，那么，将 $k$ 的二进制位分解，对应位填入原来的 $n$ 中，形成新的二进制数，就是第 $k$ 大的解。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
typedef pair<int,int> pii;

int T,n,k,cnt0;
vector<int> bit;

signed main() {
    scanf("%lld",&T);
    while (T--) {
        bit.clear(); cnt0=0;
        scanf("%lld %lld",&n,&k);
        while (n) bit.emplace_back(n&1),n>>=1;
        _iter(it,bit) if (!(*it)) cnt0++;
        if ((1<<cnt0)<k) {
            puts("-1");
            continue;
        }
        k--;
        vector<int> ans;
        _iter(it,bit) {
            if (*it) ans.emplace_back(*it);
            else {
                ans.emplace_back(k&1);
                k>>=1;
            }
        }
        int res=0;
        while (!ans.empty()) res=res<<1|ans.back(),ans.pop_back();
        printf("%lld\n",res);
    }
    return 0;
}

/*
1001101001111111000001110 n 20250126
       *        *****
1001101101111111111111110 x 20381694
0000000100000000111110000 n%x 131568
*/
```

---

## 作者：linjunye (赞：0)

### 题意

定义 $x$ 与 $n$ 相容满足：$x$ 与 $n$ 的异或和等于 $x$ 除以 $n$ 的余数。

给定 $n$ 和 $k$，求第 $k$ 小的和 $n$ 相容的数。

### 做法

先不管第 $k$ 小，先找相容时的性质。

那么题目转化为：$a\oplus b=a\bmod b$，已知 $b$，求 $a$。

下面用 $10$ 步来分析。

第一步：$b$ 的位数不能大于 $a$ 的位数。因为如果这样，会导致等式左边大于 $a$，右边等于 $a$，等式不成立。

第二步：$b\le a$。这一步不好理解。考虑用反证法：如果 $b>a$，则等式右边为 $a$，解方程 $a\oplus b=a$，可解得 $b=0$。因为 $a\ge 1$（数据范围），所以 $b\le a$。

第三步：$a$ 可以等于 $b$，且这时候的 $a$ 是最小解。这一步证明较简单，可以尝试证明一下，这里不再阐述。

第四步：$a\bmod b\le\min\{a,b\}$。这一步是根据取模的性质推出的。证明时，可以从 $a\le b$ 与 $a>b$ 进行分类讨论，最终合并即可得出这一步结论。这里不再阐述。

第五步：$a\bmod b <a$。这其实是第四步的推广。从第二步得出 $a\ge b$，所以 $a\bmod b$ 的结果不可能不小于 $a$。

第六步：$a$ 的位数不能大于 $b$ 的位数，则 $a$ 的位数等于 $b$ 的位数。这里不要被第五步所干扰，考虑反证法：首先我们可以发现 $a\bmod b<b$（这一步基本不用证明），所以 $a\bmod b$ 的位数必然不会大于 $b$ 的位数。但此时，$a$ 的位数大于 $b$ 的位数（反证），则 $a\oplus b$ 的位数也必然大于 $b$ 的位数，并不等于 $a\bmod b$ 的位数。所以，$a$ 的位数不能大于 $b$ 的位数。

第七步：因为 $a$ 的位数等于 $b$ 的位数，所以 $b\le a<2b$。$b\le a$ 是第二步的结论，$a<2b$ 才是这一步要证明的。我们发现，$2b$ 在二进制下，就相当于在 $b$ 后面加上 $1$ 个 $0$。这会使 $b$ 的位数增大一位，所以不能取到 $2b$ 即以上的数。

第八步：$a\bmod b=a-b$。这里可以通过一个性质来证明：$a\bmod b=a-kb$。首先因为 $a\ge b$，所以 $k\ge 1$；然后发现当 $k\ge2$ 时 $a<2b$ 不成立，当 $k=1$ 时恰好成立。带入得 $a\bmod b=a-b$。

第九步：$a\oplus b=a-b$。这一步比较好证明，因为等式的左边等于右边，所以 $a\oplus b=a\bmod b=a-b$。

第十步：$b$ 是 $a$ 的子集（就是 $b$ 的所有含 $1$ 的位，$a$ 也都要含；$b$ 中含 $0$ 的位，$a$ 可含可不含）。可以用反证法证明：如果 $b$ 不是 $a$ 的子集，则 $b$ 的有一位是 $1$，而 $a$ 的这一位是 $0$。那么，$a\oplus b$ 就不是 $a-b$ 了，因为 $a-b$ 的那一位开始就要借位减法了，导致后面的位不相等。

然后就结束了。因为我们知道 $b$ 是 $a$ 的子集，所以 $b$ 中含 $1$ 的位，$a$ 也要含；$b$ 中含 $0$ 的位，就是决定 $a$ 的关键。

假设 $b$ 中含 $cnt$ 个 $0$（不含前导零），则一共有 $2^{cnt}$ 种 $a$。因为 $b$ 中含 $1$ 的，$a$ 也要含，所以这些不是决定 $a$ 种数的关键。

最后对 $k$ 二进制拆分，然后在 $b$ 中往上叠加即可，具体细节见代码。

所以这种题虽然一开始感觉很不好做，但是只要一点点推理，一点点思考，终能得出正解。

### 代码

知道思路后，还是比较好写的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010;
const int mod=998244353;
int T;
int n,k;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		k--;
		int cnt=0;
		int siz=0;
		while((1ll<<siz-1)<=n)siz++;//数b的位数，可以自行玩几个数思考
		siz--;
		for(int i=0;i<siz;i++)cnt+=!((n>>i)&1);
//		cout<<cnt<<"\n";
		if(k>(1ll<<cnt)-1)cout<<"-1\n";//特判
		else{
//			下面的过程可能比较抽象，若还是不懂，可以自行手玩小数据思考^_^
			int tot=0;
			int ans=n;
			for(int i=0;i<siz;i++){
				if(!((n>>i)&1)){//b的这一位是0
					if((k>>tot)&1){//k的这一位是1，可以往上叠
						ans|=(1ll<<i);//将这一位设为1（位运算优化）
					}
					tot++;
				}
			}
			cout<<ans<<"\n";
		}
	}
	return 0;
}
/*
下面是比赛中的思考痕迹，可以参考 https://atcoder.jp/contests/arc191/submissions/62132799
a xor b = a mod b
已知b,求a

1.b的位数不能>a的位数
2.b<=a，则a>=b
3.a可以=b，且是最小解
4.a mod b <= min(a,b)
5.因为a>=b,所以 a mod b < a
6.a的位数不能>b的位数，则a位数=b位数
7.因为a位数=b位数，所以b<=a<2b
8.a mod b=a-b
9.a xor b = a - b
10.b 是 a 的子集
*/
```

---

## 作者：wfc284 (赞：0)

~~打表~~注意到符合条件的 $x$ 必定是 $n$ 在二进制下的位数相同的超集。  

**证明：**  
我们首先有 $x=(x \  {\text {mod}} \ n) \oplus n \le (x \  {\text {mod}} \ n) + n < 2n$，且若 $x < n$，则有 $x \oplus n = x$，即 $n=0$，显然不成立。  
令 $x=an+b$，其中 $0 \le b < n$。条件转化成：$b = x \oplus n$。根据上面的分析，一定有 $a=1$。即 $x = n+b$。  
我们进行分类：
- $x$ 是 $n$ 的超集时，有 $x \oplus n = x - n = b$，显然成立。
- $x$ 不是 $n$ 的超集时，记使得 $x$ 在第 $c$ 位（$2^c$）为 $0$，$n$ 在第 $c$ 位为 $1$ 的所有 $c$ 构成的集合为 $S$。有 $x \oplus n = x-n + \sum_{c \in S}2 \cdot 2^c=b + \sum_{c \in S}2 \cdot 2^c \ne b$（拆位的角度看是显然的）。故不成立。

综上，符合条件的 $x$ 必定是 $n$ 在二进制下的位数相同的超集。

然后就可以乱写了，将 $k$ 拆一拆，拼进 $n$ 的【空隙】（即为 $0$ 的位）就行。具体见代码。

时间复杂度 $O(T \log V)$，$V$ 为值域。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
#define int long long
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
#define multi_cases 1

namespace Traveller {
	
	int n, k;
	
	void main() {
		scanf("%lld%lld", &n, &k);
		int len = 0;
		for(; 1 << len <= n; ++len) ;
		
		int bit = 0;
		for(int i = 0; i < len; ++i)
			if((n >> i & 1) ^ 1) ++bit; 
		if(1 << bit < k) return puts("-1"), void();
		
		--k;
		int ans = 0;
		for(int i = len-1; i >= 0; --i)
			if(n & 1 << i) ans |= 1 << i;
			else ans |= (k >> --bit & 1) << i;
		printf("%lld\n", ans);
	}
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller::main();
	return 0;
}

```

---

