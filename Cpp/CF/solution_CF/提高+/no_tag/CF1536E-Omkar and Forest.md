# Omkar and Forest

## 题目描述

Omkar's most recent follower, Ajit, has entered the Holy Forest. Ajit realizes that Omkar's forest is an $ n $ by $ m $ grid ( $ 1 \leq n, m \leq 2000 $ ) of some non-negative integers. Since the forest is blessed by Omkar, it satisfies some special conditions:

1. For any two adjacent (sharing a side) cells, the absolute value of the difference of numbers in them is at most $ 1 $ .
2. If the number in some cell is strictly larger than $ 0 $ , it should be strictly greater than the number in at least one of the cells adjacent to it.

Unfortunately, Ajit is not fully worthy of Omkar's powers yet. He sees each cell as a "0" or a "#". If a cell is labeled as "0", then the number in it must equal $ 0 $ . Otherwise, the number in it can be any nonnegative integer.

Determine how many different assignments of elements exist such that these special conditions are satisfied. Two assignments are considered different if there exists at least one cell such that the numbers written in it in these assignments are different. Since the answer may be enormous, find the answer modulo $ 10^9+7 $ .

## 说明/提示

For the first test case, the two valid assignments are

 $ 0000\\ 0000\\ 0000 $

and

 $ 0000\\ 0010\\ 0000 $

## 样例 #1

### 输入

```
4
3 4
0000
00#0
0000
2 1
#
#
1 2
##
6 29
#############################
#000##0###0##0#0####0####000#
#0#0##00#00##00####0#0###0#0#
#0#0##0#0#0##00###00000##00##
#000##0###0##0#0##0###0##0#0#
#############################```

### 输出

```
2
3
3
319908071```

# 题解

## 作者：一之濑帆波 (赞：7)

[link](https://codeforces.com/contest/1536/problem/E)

考虑钦定哪些 `#` 为 $0$，那么剩下的 `#` 的权值也就确定了，为最近的 $0$ 到它的距离。

为什么确定了 $0$ 的位置整张图就确定了？

假设有一个权值为正的 `#`，相邻的点的权值集合 $S$。

- $|S|=1$ 时，权值是确定的；
- $|S|>1$ 时，
  - $\max S-\min S\le2$，能够得到 `#` 确定的值，且只有一个；
  - 否则，无论 `#` 值为多少，整张图都不满足相邻点权值差不超过 $1$ 的要求。

设 `#` 个数为 $cnt$，所以答案为 $2^{cnt}-[cnt=nm]$，注意没有 `0` 的情况。

**code**

```cpp
#include <bits/stdc++.h>

using i64 = long long;

const int P = 1e9 + 7;

int main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);

    int cases;
    std::cin >> cases;
    while (cases--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::string> a(n);
        int ans = 1;
        bool zero = false;
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            for (int j = 0; j < m; ++j) {
                if (a[i][j] == '0') zero = true;
                else ans = (i64) ans * 2 % P;
            }
        }
        if (!zero) ans = (ans + P - 1) % P;
        std::cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：shinkuu (赞：2)

很强的题。

结论：每个非 $0$ 点的值一定是它到最近的 $0$ 的距离。

证明：记该点值为 $x$，上文距离为 $d$。考虑反证。

- 若 $x>d$。

考虑该点到 $0$ 的最短路。记路径上的点到该点的距离为 $d'$，值为 $x'$。则 $x'$ 最小能取到 $x-d'$。而与 $0$ 相邻的点最小只能取到 $x-(d-1)=x-d+1>1$。不符合条件。

- 若 $x<d$。

则一定有一个与它相邻的点值为 $x-1$，再与这个点相邻的一定有一个 $x-2$。以此类推。则一定有一个与该点距离为 $x$ 的点为 $0$。不符合条件。

综上，结论得证。

所以先钦定若干个未知的点为 $0$，剩下便以确定。

还有 corner case：$0$ 的数量 $=0$ 时无解。考虑最小值的四周不会有比它更小的数即可。

综上，答案即为 $2^{cnt}-[cnt=n\times m]$。其中 $cnt$ 为初始非 $0$ 点个数。

code：

```cpp
int n,m;
char s[N];
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	int cnt=0;
	rep(i,1,n){
		scanf("%s",s+1);
		rep(j,1,m){
			cnt+=s[j]=='#';
		}
	}
	printf("%d\n",qpow(2,cnt)-(cnt==n*m));
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Cutest_Junior (赞：2)

## 题解 CF1536E 【Omkar and Forest】

### 题意

+ 一个 $n\times m$ 的方格图；
+ 其中一部分格子必须填 $0$，其它格子必须填非负整数；
+ 两个格子相邻当且仅当两个格子有公共边；
+ 任意两个相邻的格子上的数的绝对差不超过 $1$；
+ 任意有正整数的格子 $(x1,y1)$，必须存在一个和它相邻的另一个格子 $(x2,y2)$，使 $(x1,y1)$ 上的数大于 $(x2,y2)$ 上的数；
+ 求有多少种不同的填数法；
+ 多组数据，$n,m\le2\times10^3$。

### 做法

对于每个可以填非负整数的格子，设共有 $k$ 个，可以填 $0$ 或填正整数。选其中一部分填 $0$，另一部分填正整数，有 $2^k$ 种选法，每种选法贡献独立。

对于每个原来就是 $0$ 或选后是 $0$ 的格子，它们周围不是 $0$ 的格子只能填 $1$，因为只能填非负整数，且已经不能填 $0$，填的数字如果大于 $1$，与 与它相邻有 $0$ 的格子 的绝对差就大于 $1$。

同理可填出 $2,3,4,\dots$。

发现每种选法的贡献都只有 $1$，所有答案就是选法的总数，特判全图原来没有填 $0$ 个字的情况。

### 代码

```cpp
#include <cstdio>

using namespace std;

const int mod = 1e9 + 7;

const int N = 2e3 + 5;

char s[N];

void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%s", s);
		for (int j = 0; j < m; ++j) {
			cnt += (s[j] == '#');
		}
	}
	int ans = 1;
	for (int i = 1; i <= cnt; ++i) {
		ans = (ans << 1) % mod;
	}
	printf("%d\n", ans - (cnt == n * m));
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}
```

---

## 作者：LinkWish (赞：2)

此题解基本基本为官方题解的翻译，其中一些证明与现有题解不同。

首先我们不妨确定哪些 ```#``` 为 $0$，可以证明，在所有 $0$ 的位置确定时，有且仅有一种方案去填其他的 ```#```。

我们可以对于所有的 $0$ 做一个多源 BFS，每一个非 $0$ 格子的值即为到最近的 $0$ 的距离，且只有这一种构造的方式合法，证明如下：

首先证明相邻两个格子值的差不超过 $1$。如果相邻两个格子的差超过了 $1$，那么值较大的那个格子的值显然可以通过值小的格子的值加一更新。

其次一个格子周围显然至少有一个格子的值小于它，因为在 BFS 的过程中它一定是从一个格子走来的。

最后证明只有这一种合法构造方式。如果一个格子的值小于离它最近的 $0$ 的距离，那么他周围就不会有值比它小的格子；如果强制令一个他周围的格子比它小，那么这个格子的周围也不会有值比它小的格子，如此循环，最后至少会令一个原本值不应该为 $0$ 的格子权值等于了 $0$。如果一个格子的值大于离它最近的 $0$ 的距离，那么他与相邻格子值的差至少有一个大于 $1$，如果强制令相邻的差大于 $1$ 的格子值加一，那么像上面一样，最终会令原本的一些值为 $1$ 的格子的值变为了 $2$。

因为每个 ```#``` 的状态相互独立，所以设 ```#``` 的个数为 $x$，那么答案即为 $2^x$。特殊地，当 $x=nm$ 时，答案为 $2^x-1$，因为此时有一种情况是所有的 ```#``` 都不为 $0$ ，但这时没有初始的 $0$，因此这种情况不存在。

程序只给出主体部分，主要是前面一部分的模板有一些影响观感，而且给出主体已经能够辅助理解。

```cpp
//Linkwish's code
const int N=2005,mod=1e9+7;
int n,m;
char mp[N][N];
inline void solve(){
	read(n),read(m);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	int cnt=0,ans=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]=='#')cnt++;
	for(int i=1;i<=cnt;i++)ans=ans*2%mod;
	writeln((ans-(cnt==n*m)+mod)%mod);
}
```


---

## 作者：创世游戏科技 (赞：1)

# Omkar and Forest

## 题目大意

给定 $n,m$ 和一个 $n$ 行 $m$ 列、仅包含字符 `0 #` 的网格。  
你需要向网格上每个位置都分配一个非负整数，满足
- 任意两个相邻的格子，差的绝对值不超过 $1$。
- 这个格子不是周围中最小的。  

求方案总数。

## 思路分析

如果我们把填 $0$ 的位置确定了之后，那么根据题意，与四个相邻的格子只能填 $1$。

- 如果填 $0$ 的话，这时候与其他情况冲突，因为我们前面已经确定了填 $0$ 的位置。
- 如果填比 $1$ 大的数的话，此时差的绝对值超过 $1$，与前文题设矛盾。

所以 $0$ 周围的只能填 $1$，同理 $1$ 周围的格子只能填 $2$，也就是说，如果 $0$ 的位置已经确定了，那么剩下的格子都只能填一个非 $0$ 的**确定的数**。

那么每个未确定的格子只有两种填法，一种是填 $0$，另外一种情况是填一个确定的数。

此时如果有 $m$ 个格子不确定，那么最终应该有 $ 2^m $ 种情况。

注意一种特殊情况，如果所有格子都不确定，那么总有一种情况全填确定的非 $0$ 的数，根据题设二，这时总能找到一个最小的数，这种情况是不合法的，需要减 $1$。


```
21112212321221212332123321112
10002101210110101221012210001
10102100100110012210101210101
10102101010110012100000110012
10002101210110101101110110101
21112212321221212212221221212
```

样例的一种合法填法。

## 参考实现


```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int T;
int qpow(int base,int ret){
    int ans=1;
    while(ret){
        if(ret&1)ans=ans*base,ans%=mod;
        base=base*base%mod;
        ret/=2;
    }
    return ans;
}
signed main(){
    cin>>T;
    while(T--){
        int n,m,sum=0;cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                char x;cin>>x;
                sum+=(x=='#');
            }
        }
        cout<<(qpow(2,sum)-(sum==n*m))<<endl;
    }
    return 0;
}
```

---

## 作者：liujiaxi123456 (赞：0)

### 思路：

**本文主要为作者本身的思考过程，包含一定的作者自身的方向判断、试错等不完全必要的部分，若你只想知道如何解决此题，请跳过“思路”部分，转到“题解”部分。但我希望对于那些愿意阅读作者思考过程的读者，能够收获一些解决相关问题的技巧与思考方向。**

这种相差 1 问题，之前做过一个[类似的](https://www.luogu.com.cn/problem/AT_arc063_c)。

那题的思想是每个点的点权是一个连续区间，放在这里似乎仍然适用。

- P.S. 实际上此题并不适用。

考虑通过类似最短路的方式 DP 求解。

但是首先的问题是不知道 DP 的终止态。

很显然，如果按行/列 DP 需要记录的后效性非常巨大，无法记录，所以 DP 的顺序仍然只能考虑类似最短路的转移顺序。

注意到还有一个条件没有分析，**由于此时我们完全没有思路，而此题有解，所以这个条件大概率提供的是好的性质而非限制。**

来分析这个条件：

- 放在图上，可以大致理解为每个非 0 点都有至少一条入边。

- 所以我们可以发现，对于一个紧挨 0 点的非 0 点，它的值必然为 1。

- 而对于任意一个非 0 点，假设它可填，则它的值一定为周围最小的值 + 1。

  - 假设一个点周围的权值为 $a\le b\le c\le d$。
 
  - 若 $d-a=0 $，则显然只能填 $a+1 $。
 
  - 若 $d-a=1 $，则仍然只能填 $a+1 $。
 
  - 若 $d-a=2 $，则仍然只能填 $a+1 $。
 
  - 若 $d-a\ge 3$，则显然无解。

- 所以，假设现在确定了图中哪些点填 0，则方案数等价于合法性。

来分析一下合法性：

- 想办法找出一个图合法的冲要条件。

- 考虑从不合法入手。

  - 发现对于一个被一圈 0 包围，且内部没有 0 的图，其必然是合法的。
 
    - 因为在内部会形成一圈 1，再形成一圈 2...
   
  - 若被 0 包围，且内部有 0，仍然是合法的。
 
    - 跟上面的差不多。
   
  - 若有部分是矩形边界，则似乎仍然是合法的。
 
    - 仍然是一圈一圈的靠拢。

  - 观察样例可以发现，若没有为 0 的点，则是不合法的。
 
- 所以，只有全不是 0 时不合法。

所以，令 $cnt $ 表示 '#' 的个数，则 $ans = 2^{cnt} - [cnt=nm] $。

### 题解：

0 确定后可以确定所有位置，方案数转成合法性。

只有全不为 0 时非法。

直接统计答案即可，令 $cnt $ 表示 '#' 的个数，则 $ans = 2^{cnt} - [cnt=nm] $。

### Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MOD = 1e9+7;

namespace Josh_zmf {
	
	int N, M;

	inline ll pow(ll a, int b) {
		ll c = 1;
		while(b) {
			if(b&1)	c = c*a %MOD;
			a = a*a %MOD, b >>= 1;
		}
		return c;
	}

	inline int main() {
		cin>> N>> M;
		int cnt = 0;
		for(int i=1; i<=N; i++) {
			static string s; cin>> s, s = ' ' + s;
			for(int j=1; j<=M; j++) {
				if(s[j] == '#')	cnt++;
			}
		}
		// printf("cnt:%d\n", cnt);
		cout<< pow(2, cnt) - (cnt==N*M)<< '\n';
		return 0;
	}

}

int main() {
	int T; cin>> T;
	while(T--)	Josh_zmf::main();
	return 0;
}

```

### 结语：

都看到这里了，点个赞在走吧。

---

