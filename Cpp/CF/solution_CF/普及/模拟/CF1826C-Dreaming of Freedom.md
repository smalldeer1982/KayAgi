# Dreaming of Freedom

## 题目描述

Because to take away a man's freedom of choice, even his freedom to make the wrong choice, is to manipulate him as though he were a puppet and not a person.

— Madeleine L'Engle



There are $ n $ programmers choosing their favorite algorithm amongst $ m $ different choice options. Before the first round, all $ m $ options are available. In each round, every programmer makes a vote for one of the remaining algorithms. After the round, only the algorithms with the maximum number of votes remain. The voting process ends when there is only one option left. Determine whether the voting process can continue indefinitely or no matter how people vote, they will eventually choose a single option after some finite amount of rounds?

## 说明/提示

In the first example, there are $ 8 $ ways people could vote: $ \{1|1|1, 1|1|2, 1|2|1, 1|2|2, 2|1|1, 2|1|2, 2|2|1, 2|2|2\} $ .

In cases $ 1 $ , $ 2 $ , $ 3 $ , and $ 5 $ , the programmers are left with the first algorithm, and in the remaining cases people are left with the second one, so the voting ends in one round in any case.

In the second example, the programmers could always vote $ 1|1|2|2 $ . Both algorithms have the maximum number of votes and remain for the next round, so the voting never ends.

## 样例 #1

### 输入

```
5
3 2
4 2
5 3
1000000 1000000
1 1000000```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：arrow_king (赞：2)

# 题意

$n$ 个程序员要在 $m$ 个算法里选出最受欢迎的算法，每轮投票每个程序员都会在剩下的算法中选择一个。

在第一轮投票前，$m$ 种算法都可以选择；每轮投票后，只保留有最多票数的算法；只剩下一种算法时，选拔结束。请判断无论怎样投票选拔都会结束吗？

# 思路

考虑什么情况下永远无法结束。

如果 $n$ 能够被一个大于 $1$ 小于等于 $m$ 的常数 $k$ 整除，也就是 $n$ 票可以平均分到 $k$ 个选项中，那么就永远无法投完了。反之则一定可以结束。

注意到 $k$ 一定是 $n$ 的因数（非 $1$），且小于等于 $m$，所以我们可以寻找 $n$ 最小的非 $1$ 因数。这个过程可以 $\mathcal O\left(\sqrt{n}\right)$ 实现。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t;
ll n,m;
il ll minn(ll x) {
	for(int i=2;i*i<=x;i++) if(x%i==0) return i;
	return x;
}
int main() {
	t=read();
	while(t--) {
		n=read(),m=read();
		if(n==1||m==1) {
			printf("YES\n");
			continue;
		}
		if(minn(n)<=m) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}

```

---

## 作者：Neilchenyinuo (赞：1)


## 题目大意

判断所有选了的算法的人数能不能相同。

## Solution
情况分为 $3$ 种：

1. 当 $n=1$ 或 $m=1$ 时，只能有一票或者一个算法，很明显人数不相同。

2. 当 $m \geq n$ 时，只要 $n$ 个人选不同的算法就会一直投票。

3. 否则判断 $n$ 能不能分解出一个小于 $m$ 的质因数。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t; 
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        if(n==1||m==1)//当 n = 1 或 m = 1 时
        {
            cout<<"YES\n";
            continue;
        }
        if(m>=n)//当 m >= n 时
        {
            cout<<"NO\n";
            continue;
        }
        bool vis=0;
        for(int i=2;i*i<=n;i++)
        {
            if(n%i==0&&m>=i)//判断 n 能不能分解出一个小于 m 的质因数
            {
                cout<<"NO\n";
                vis=1;
                break;
            }
        }
        if(vis==0)
            cout<<"YES\n";
    } 
    return 0;
} 
```


---

## 作者：Scrolling_Ball (赞：1)

这道题的题意就是判断所有选了的算法的人数能不能相同嘛。

情况分为 $3$ 种：

1. 我们可以知道，当 $n=1$ 或者说 $m=1$ 的时候，显然只能选到一个算法所以人数肯定不会相同。

1. 当 $n\le m$ 的时候，我们可以让 $n$ 个人都选不同的算法，这样的话是肯定可以让人数相同的。

1. 判断一下 $n$ 能不能分解出来一个比 $m$ 小的质数。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m;
int main()
{
    cin >> t;
    while(t -- )
    {
        cin >> n >> m;
        if(n == 1 || m == 1)
        {
            puts("yEs");//题意是不能持平输出 Yes，能持平输出 No
            continue;
        }
        if(n <= m)
        {
            puts("nO");
            continue;
        }
        bool f = 0;
        for(int i = 2; i <= n / i; i ++ )
            if(n % i == 0 && m >= i)
            {
                puts("No");
                f = 1;
                break;
            }
        if(f == 0)puts("yeS");
    }
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

首先，当 $n=1$ 时，是一定只能剩下一个。

若 $m\ge n$ 时，显然每个人选择 $n$ 个，所以就会无限循环。

接下来，考虑 $n$ 个人，$m$ 个算法，那么，若 $m\mid n$，就会仍然剩下 $m$ 个。

从这个结论开始，我们就可以考虑枚举 $\le m$ 的 $n$ 的非 $1$ 的因数，因为 $\forall i\le \sqrt{n},i\le \dfrac{n}{i}$，所以我们只需要枚举到 $\sqrt{n}$ 即可，若存在这样的情况，就会无限循环。否则，最多剩下 $n\bmod m<m$ 个，最后就会只剩下一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		if(n==1){
			puts("YES");
			continue;
		}
		if(m>=n){
			puts("NO");
			continue;
		}
		bool flg=1;
		for(int i=2;i<=n/i&&i<=m;++i)
			if(n%i==0){
				flg=0;
				puts("NO");
				break;
			}
		if(flg)
			puts("YES");
	}
	return 0;
}
```

---

## 作者：Register_int (赞：0)

根据题目描述可以得知，将这 $n$ 个人分成 $1<k\le m$ 个人数相等的组即可满足条件，直接判断 $n$ 的最小质因数是否 $\le m$，用线性筛预处理。

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 1e6 + 10;
 
int p[MAXN], f[MAXN], tot; bool vis[MAXN];
 
inline 
void init(int n) {
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) p[++tot] = f[i] = i;
		for (int j = 1; j <= tot; j++) {
			if (i * p[j] > n) break;
			vis[i * p[j]] = 1, f[i * p[j]] = p[j];
			if (i % p[j] == 0) break;
		}
	}
}
 
int t, n, m;
 
int main() {
	for (scanf("%d", &t), init(1e6); t--;) {
		scanf("%d%d", &n, &m), puts(f[n] == 1 || f[n] > m ? "YES" : "NO");
	}
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

一般情况下，当 $n$ 为 $m$ 的倍数时，可以无限进行下去。

所以题目就转化成了问 $n$ 的最小的大于 $1$ 的因数是否 $\le m$。

（二）

AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,p,n,m;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		if(n==1||m==1){
			puts("YES");
			continue;
		}//特判
		p=n;
		for(int i=2;i*i<=n;i++)
			if(n%i==0){
				p=i;
				break;
			}
		if(p<=m)puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：winter2020 (赞：0)

根据题意，如果多个算法同时为最大值时，这些算法均会保留。

那么我们找到一个 $n$ 的因数 $x$，并满足 $2 \leq x \leq m$ 即可。具体可以在第一轮时选择 $x$ 个算法，然后一直平均分配票数，投票就永远不会结束。

如果找不到一个 $x$，则不能平均分配最大投票数，每一轮必然有一些算法被淘汰，若干轮后一定会结束投票。

直接筛因数即可。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;

int main() {
    int T;
    cin >> T;
    while (T -- ) {
        cin >> n >> m;
        int mx = 0;
        for (int i = 1; i * i <= n && i <= m; i ++ ) {
            if (n % i == 0) mx = i;
            if (n % i == 0 && n / i <= m) mx = max(mx, n / i);
        }
        if (mx != 1) puts("No");
        else puts("Yes");
    }
    return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

**【题目分析】**

结论：要想最终保留 $\ge 2$ 种算法，必须满足 $2 \sim m$ 中有任意一个数 $x$ 满足 $n \bmod x = 0$。

我们发现一轮结束后会立即开启下一轮，而下一轮 $n$ 不变，$m$ 变小，与之前的状态重合。又因为当且仅当人数被算法数量整除时可以留下这些算法，所以上面的结论得证。

算法：分解因数，判断 $2 \sim m$ 内是否有数字是 $n$ 的因数，复杂度 $O(T\sqrt n)$。

**【赛时代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m,a[1000005];
int main(){
	cin >> t;
	while(t --){
		bool flag = 0;
		cin >> n >> m;
		if(n <= m && n != 1){
			flag = 1;
			cout << "NO\n";
			continue;
		}
		for(int i = 2;i*i <= n;i ++){
			if(i > m) break;
			if(n % i == 0){
				flag = 1;
				cout << "NO\n";
				break;
			}
		}
		if(flag == 0) cout << "YES\n"; 
	}
 
	return 0;
}
 
 ```

---

## 作者：y_kx_b (赞：0)

Preface：这场是名副其实的阴间场，A>B>C，然后我 C 还花了半个小时/kk

题意：$n$ 名程序员给 $m$ 个算法投票，每次投完后只会留下有最多票数的算法。如果只剩一个算法了，那么投票进程终止。问是否对于所有投票方式，投票进程都会终止。

仅给出 $n,m$，多测，$T\leqslant10^5$，$n,m\leqslant10^6$。

---
问题转化为问存不存在一种投票方式使投票进程永远不会终止。

投票进程永远不会终止，那么意味着最后 $m$（$m > 1$）个算法都会可以拥有相同的票数，也就是说，$n \bmod m = 0$。

然后发现，每一轮结束后 $m$ 可以取的范围是一个区间。可以设想如下情境：有 $n$ 个球装进 $m$ 个盒子里，求装有最大球数的盒子的数量的取值范围。

比较容易想到找出一个 $h$ 使得有最多恰好装了 $h$ 个球盒子数量（前提是其他盒子不能达到 $h$）。那么数量最大值就是 $\lfloor\frac nh\rfloor$，当然要有 $m-\lfloor\frac nh\rfloor\geqslant[n \bmod h\not=0]$（当球有剩余时得有空位放剩下的 $n\bmod h$ 个球）。 显然 $h$ 定义域连续，且随着 $h$ 升高数量最大值是减小的，那么我们只需找到一个最小的合法 $h$ 即可。

比较容易想到 $h\geqslant \lceil\frac nm\rceil$，取等时每个盒子装的不是 $h$ 个球就是 $h-1$ 个球。显然，如果再把 $h$ 减少 $1$，其他盒子里的球数量就会超过 $h$。

那么我们成功算出来了 $m$ 再一轮操作之后的取值区间是 $\left[1, \left\lfloor\dfrac n{\lceil\frac nm\rceil}\right\rfloor\right]$，我们只需判断这个区间内是否有 $n$ 的非 $1$ 因子就行。时间复杂度 $O(T\sqrt{n})$。


```
	int n = read(), m = read();
	int h = (n + m - 1) / m;//ceil(n / m)
	int w = n / h;//m\in[1,w]
    
	int i = 2;
	for(; i <= n / i && i <= w; i++) if(n % i == 0) return 0;
	if(i > n / i && n > 1 && n <= w) return puts("NO");
    return puts("YES");
```

---

