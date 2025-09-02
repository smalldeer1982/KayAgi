# [ARC168B] Arbitrary Nim

## 题目描述

有 $N$ 堆石子，第 $i$ 堆（$1 \leq i \leq N$）有 $A_i$ 个石子。

你现在可以选择一个正整数 $k$。之后，Alice 和 Bob 会用这些石子堆进行如下游戏：

- 游戏由 Alice 先手，双方轮流进行操作。
- 每一回合，当前玩家选择一个非空的石子堆，从中取走任意数量的石子，数量不少于 $1$ 个且不多于 $k$ 个。

无法进行操作的一方判负，未被判负的一方获胜。

你需要选择一个正整数 $k$，使得 Alice 存在必胜策略。请判断是否存在这样的 $k$。如果存在，判断是否存在使 Alice 必胜的 $k$ 的最大值。如果最大值存在，请输出该最大值。

## 说明/提示

### 限制条件

- $1 \leq N \leq 250000$
- $1 \leq A_i \leq 10^9$
- 输入的所有值均为整数。

### 样例解释 1

例如，当 $k=2$ 时，Alice 存在必胜策略。若选择 $k \geq 3$，Alice 就没有必胜策略，因此答案为 $k=2$。

### 样例解释 2

例如，对于所有 $k=100,200,300,\cdots$，Alice 都存在必胜策略。因此不存在最大值，输出 $-1$。

### 样例解释 3

无论选择怎样的 $k$，Alice 都没有必胜策略。因此输出 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 2 3 4```

### 输出

```
-1```

## 样例 #3

### 输入

```
2
100 100```

### 输出

```
0```

# 题解

## 作者：Creeper_l (赞：5)

原题链接：[ARC168B](https://www.luogu.com.cn/problem/AT_arc168_b)

题意：有 $n$ 堆石子，每堆有 $a_{i}$ 个。每人每次可以取走其中一堆中的 $x(1 \le x \le k)$ 个。求出一个最大的 $k$ 使得先手必胜。无解输出 $0$，$k$ 可以取无限大输出 $-1$。

一个经典 Nim 游戏的结论是：$a_{i}$ 的异或和为 $0$，则先手必败。但是现在限制了一次最多取 $k$ 个，所以我们可以先把每一个 $a_{i}$ 模上 $k+1$，然后这就变成了一个经典博弈。

首先考虑如何判断 $-1$ 的情况。显然，如果当前异或和已经不为 $0$ 了，那么无论 $k$ 取多大，异或值一定不为 $0$，所以 $k$ 可以取无限大。

再来考虑 $0$ 的情况。我们会发现，两个相同的 $a_{i}$ 无论模上多少最终的值都一定相同，即最终的异或和一定为 $0$，所以我们可以先消除掉出现次数为偶数的数（因为异或和为 $0$ 的数对最终的异或值没有影响），如果这时已经没有数了，说明最终的异或和一定为 $0$，则先手必败。

现在就只剩下一些出现次数为奇数的数了，且这些数的异或和为 $0$（否则为上述 $-1$ 的情况）。假设其中的最大值为 $p$，其余值的异或和等于 $q$，那么 $p \oplus  q = 0$。这时将 $k$ 设为 $p-1$，将所有数模上 $p$ 之后，只有 $p$ 变为了 $0$，其余数不变。因为 $p \oplus  q = 0$，所以 $0 \oplus q \ne 0$，所以这时先手必胜，$k$ 取 $p-1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5 + 10;
int n,a[MAXN],k = 0;
set <int> s;
signed main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
		if(s.find(a[i]) != s.end()) s.erase(a[i]);
		else s.insert(a[i]);
		k ^= a[i];
	}
	if(k != 0) cout << "-1";
	else if(s.size() == 0) cout << "0";
	else cout << *--s.end() - 1;
	return 0;
} 
```


---

## 作者：封禁用户 (赞：2)

## 前言：
竟然有如此水的绿题。

## 思路：

这是一道非常经典的 Nim 游戏问题。

首先我们可以先看 $-1$ 的情况。如果先手本来就可以赢的话，那么我们就不用加限制条件（也就是相当于取无限大的 $k$）。

假如先手赢不了的话，那么我们就要考虑加限制条件。所以我们可以先将出现两次的数给消掉，因为这样就可以通过模仿对方的行为来进行消除这两堆。

进行完消除以后（以下都在进行消除后的基础之上），我们设最大的一堆为 $p$，那么限制条件就为 $p-1$。因为这样就可以让先手保证最大的那一堆用两步消掉，这样就相当于没有了最大的那一堆。

由于先手赢不了时异或和为 $0$，所以当消除最大的一堆时异或和一定不为 $0$，此时这个时候先手就必赢。

当然还有以个特别的条件，当 $p=0$ 时候，即一堆都没有的情况，先手就必败，输出 $0$ 即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
set<int>s;
long long n,sum=0;
int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(long long i=1,x;i<=n;i++)
	{
		cin >> x;
		sum^=x;
		if(s.find(x)!=s.end())
		{
			s.erase(x);
		}
		else
		{
			s.insert(x);
		}
	}
	if(sum)
	{
		cout << "-1" << endl;
	}
	else if(s.empty())
	{
		cout << "0" << endl;
	}
	else
	{
		cout << *--s.end()-1 << endl; 
	}
	return 0;
}
``````

---

## 作者：roger_yrj (赞：1)

## 题解

这题就是 Nim 游戏加了个限制。

首先看 `-1` 的情况。如果先手本来就能赢，那就不用加限制（相当于取无限大的 $k$）。

然后如果先手赢不了，那就要考虑加限制。我们可以先将出现两次的数给消掉，因为可以通过模仿对方的行为来消除这两堆。

消除后（以下都在消除后的基础上），我们设最大的一堆为 $p$，那么限制就为 $p-1$。因为这样先手就可以保证最大的一堆用两步消掉，这样子相当于没有了最大的一堆。

由于先手赢不了时异或和为 $0$，所以当消除最大的一堆时异或和一定不为 $0$，此时先手必胜。

特别的，当 $p=0$ 时，即一堆都没有的情况，先手必败，输出 `0`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
set<int>s;
int n,maxx,xors;
int main(){
	cin>>n;
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		xors^=x;
		if(s.find(x)!=s.end())s.erase(x);
		else s.insert(x);
	}
	if(xors)cout<<"-1";
	else if(s.empty())cout<<"0";
	else cout<<*--s.end()-1; 
} 
```

~~没错就这么短~~

---

## 作者：_zzzzzzy_ (赞：1)

# 思路
首先这是个博弈论的变形，当所有堆的异或和是 $0$，那么是后手必赢，那我就要考虑限制然后获得胜利，至于先手必赢的方法，显然可以选无限大的 $k$，输出 $-1$。

然后我们来考虑如果在没有限制的时候如果后手必胜，那么先手取一个，后手一定可以再取一个把异或和削成 $0$，那么我们考虑先手取完一个，然后后手取得刚好等于 $k+1$ 一定是最优的，那么就好办了，我们对于最大的，有奇数个的堆给他输出答案就行了，这里的奇数个是指的是这一堆的个数在全部的里面有奇数个，然后最后都是偶数，就一定没办法赢了。

# 代码
```cpp

#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (r); i >= (l); i--)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using i64 = long long;
const int maxn = 1000000;
int a[maxn];
map<int, int> mp;
int mian() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int n, x = 0;
	cin >> n;
	rep(i, 1, n) {
		cin >> a[i];
		x ^= a[i];
		mp[a[i]]++;
	}
	if (x) {
		cout << -1 << "\n";
		return 0;
	}
	while (mp.size()) {
		pair<int, int> u = *(--mp.end());
		mp.erase(--mp.end());
		if (u.second % 2 == 1) {
			cout << u.first - 1 << "\n";
			return 0;
		}
	}
	cout << 0 << "\n";
	return 0;
}
```

---

## 作者：Yang_YL (赞：0)

## 前言
这道题的基础是 [洛谷 P2197](https://www.luogu.com.cn/problem/P2197) ，建议做完这道题再看题解。
## 思路
首先可以想到二分答案，可惜这道题的 $k$ 并不满足单调性，因此，我们考虑 $k$ 的性质。
首先，如果不限制 $k$ 的情况下（可以任意取），先手必胜，那么，$k$ 可以取到无穷大，也就是输出 $-1$。

其次，我们知道，两个相同的数对同一个数取模，结果一样。（~~不会有人不知道这个吧……~~）
我们又知道，一个数异或上他本身，结果是 $0$。
因此，如果每个 $a_i$ 都可以互相抵消，那么，$k$ 取什么值都是先手必胜，输出 $0$。

否则，我们将剩下的数存下来，取最大值为 $x$，其他值的异或和为y，此时 $x \oplus y = 0$（$\oplus =$ 异或）。
但是先手必胜的条件是异或和不等于 $0$，所以，我们让 $k = x - 1$ 使得最终异或和不等于 $0$（$0 \oplus y = y$）。

## 神奇小代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,f;
set<int> st;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		f^=a;
		if(st.find(a)==st.end()) st.insert(a);//无则插入
		else st.erase(a);//有则抵消
	}
	if(f>0) cout<<"-1";//k无穷大
	else if(st.size()==0) cout<<"0";//先手必败
	else cout<<(*(--st.end()))-1;//剩余a[i]中最大的-1
	return 0;
}

```

---

## 作者：Unnamed114514 (赞：0)

[博弈论相关](https://www.luogu.com.cn/article/00mwsr77)

首先异或起来不为 $0$ 的时候答案是 $\infty$。

否则找到最大的出现次数为奇数的数 $mx$，答案就是 $mx-1$。

从两个方面证明它是正确的：

- 最优性：如果取比 $mx-1$ 大的数，因为 $>mx$ 的数出现次数都是偶数，而你取比 $mx-1$ 大的数，那么就指挥修改这些出现次数是偶数的数，并不会改变异或值。

- 可行性：注意到 $mx$ 会变为 $0$，而比 $mx$ 小的数都模上 $mx$ 不会改变，由上文知比 $mx$ 大的数改变后不影响异或值，所以异或值就会变成 $mx$，先手必胜。

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc168_b)
## 思路
这道题本质上是一道 Nim 游戏。

对于 $-1$ 的情况，其实就是不用限定 $k$ 先手就有必胜策略。此时，$k$ 可以设为 $∞$，所以不存在合法的最大的 $k$。

对于 $0$ 的情况，其实就是无论怎样限定 $k$，先手都无必胜策略。此时，先手无论如何怎么选，后手都一定能模仿先手走，这样先手就无必胜策略。

接下来就是其他的情况了。Nim 游戏的核心就是将先手转化为后手，使得先手始终能模仿后手。首先，对于一个数 $x$，若有 $x$ 颗石子的堆数为偶数，则后手一定能模仿先手，所以先将满足上述条件的堆数去掉。因为要找到最大的 $k$，所以可以将剩余的石头堆数中选一个含有最多石子的堆数，将其分为两个部分（可以供先、后手共取 $2$ 次）。我们把这个含有最多石子的堆数所含有的石子个数设为 $y$，因为要使 $k$ 最大，同时又要将上述的那一堆分为两个部分，所以 $k$ 取 $y - 1$ 满足所有条件。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 250005, M = 1e9 + 5;

int n, cnt;
int a[N];
bool vis[M];

int main()
{
	scanf("%d", &n);
	int res = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		res ^= a[i]; // Nim 游戏模板
		if (vis[a[i]])
		{
			cnt--;
			vis[a[i]] = false;
	    }
		else
		{
			cnt++;
			vis[a[i]] = true;
	    }
	}
	if (res) // 判断 -1
	{
		puts("-1");
		return 0;
	}
	if (!cnt) // 判断 0
	{
		puts("0");
		return 0;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!vis[a[i]]) continue;
		ans = max(ans, a[i]); // 在可选的堆数中找最大
	}
	printf("%d\n", ans - 1);
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

Nim 游戏扩展，回想 $[1,k]$ 这样的 Nim 游戏的必胜策略：令 $\text{SG}(x) = x \bmod (k+1)$，则 $f=\text{SG}(a_1) \oplus \cdots \oplus \text{SG}(a_n) = 0$ 是必败情况。

考虑从上到下枚举 $k$ 的暴力做法，当最初情况，即 $k+1 \ge \max(a_i)$ 的时候，如果 $f$ 已经非 $0$，那么输出 `-1`。

否则，当某一刻，$f$ 不是 $0$ 的时候，输出此时的 $k$，如果到最后还没输出，那么答案就是 $0$。

考虑加速这个过程，考虑到答案应该是，到输出之前，无论对于哪个 $k$，$f$ 都是 $0$，考虑 $\bmod$ 操作只会影响较大的元素，那么考虑排完序后的 $a_n$，根据模 $k+1$ 后是否被影响，可以分为前 $x$ 个元素和 后 $n - x$ 个元素，如果前 $x$ 个此时 $f$ 不为 $0$，那么 $k+1=a_{x+1}$ 会导致 $a_{x+1}$ 变为  $0$，此时就可能对最后的 $f$ 造成影响。如此这般循环考虑即可。

---

## 作者：elbissoPtImaerD (赞：0)

没啥意思的博弈论。

考虑 Nim 博弈：若异或和不为 $0$ 相当于没有 $k$ 的限制，答案是 $-1$。

否则，考虑两堆具有相同个数的石子：后手只需复制先手操作。故这两堆石子没有贡献。

那我们只需考虑石子个数出现次数为奇数的那些堆石子。

不难发现只需令 $k$ 等于这些石子的最大值 $-1$ 即可。  
因为如此 A 可以通过消除石子最多的那堆逆转胜负态，且 $k$ 对后续操作无影响。

```cpp
il void Solve()
{
  int n;
  rd(n);
  ve<int>a(n);
  int s=0;
  sd map<int,int>h;
  for(int&x:a) rd(x),s^=x,++h[x];
  if(s) return wrt(-1),void();
  int ans=0;
  for(auto[x,y]:h) if(y&1) cx(ans,x-1);
  wrt(ans);
  return;
}
```
[$\color{green}{\checkmark}$](https://atcoder.jp/contests/arc168/submissions/48980572)

---

## 作者：CrTsIr400 (赞：0)

# ARC168B 题解

其实这东西我考场算是没切，最后十几分钟和同学交流了一下才得到结论。只知道结论还不够，我后来思考了一下得到了更简单的推理。

另外，此题实际上比主题库很多绿色的博弈论要难，所以虽然是 1200 的难度，但是最好是绿起步。

首先 nim 游戏有个很显然的结论，异或和为 $0$ 先手必败，这里不作赘述。

然后假设 $k$ 给定让我判断先手是否必胜，那么也可以根据博弈思想搞搞。

每个人最多取 $k$ 个，无疑就是巴什博弈的模型，无论你先手选了多少后手都可以做到取过的石子数为 $(k+1)$ 的倍数，这是一种最优方案。

于是每个人最多取 $k$ 个的情形下，所有石子数量取模 $(k+1)$ 跑一遍异或和，不为 $0$ 即先手必胜。

---

此时我们会判定答案了，但是还不会算答案，暴力一个个枚举太慢（考试时候就栽在这里），怎么办呢？

首先先给 $a$ 数组排序，若 $k\ge a[n]$ 时候就跟没这个限制一样，异或和要不为 $0$ 你就输出 `-1` 得了。

再观察一下，发现 $k$ 最好取 $a[i]-1$，因为刚好可以把这个 $a[i]$ 变成 $0$。但是此时一个个枚举 $a[i]$、即使去重，也太慢了。

既然研究取模这个运算已经是非常困难了，而异或这个运算却有很多性质。

我们肯定不能做什么拆位、结合律之类的操作，就朴素地发现，一个元素在 $a$ 序列中出现偶数次，那么肯定是没用的，出现奇数次就相当于出现了一次。而且这样处理过的 $a$ 序列是不重复的，肯定异或和为 $0$（不为 $0$ 就输出 $-1$）。

处理完 $a$ 序列后，考虑把 $k$ 取为 最大的那个数 $-1$，那么最大那个数就变成了 $0$，其它的不变，那么最终的异或和肯定不能等于 $0$。

于是这个题就很简单结束了。

---

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
I n,a,s;set<I>m;
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	fo(i,1,n){
		cin>>a;s^=a;
		if(m.find(a)!=m.end())m.erase(a);
		else m.insert(a);}
	if(s)puts("-1");
	else printf("%d\n",m.size()?(*m.rbegin()-1):0);
	return 0;}
```



---

## 作者：hejianxing (赞：0)

[link](https://www.luogu.com.cn/problem/AT_arc168_b)

考场不会。wtcl

感谢 [2020wjn](https://www.luogu.com.cn/user/554868) 讲解。

# 题解

博弈论基础。

考虑 $k$ 固定的情况。经典地有每堆的 $sg$ 函数为 $a_i\bmod (k+1)$，整个游戏的 $sg$ 值为每堆石子的 $sg$ 值的异或和。Alice 必胜当且仅当 $sg$ 异或和不为 $0$。

首先假设 $k=a_{max}$，那么若当前的 $sg$ 异或和大于 $0$，Alice 在 $k=a_{max}$ 时必胜，那么显然 $\forall k\ge a_{max}$ 都有 Alice 必胜，输出 `-1`。

于是现在有 $sg$ 异或和为 $0$。

考虑从大往小缩小 $k$。当 $k\gets k-1$ 时，$a_{max}$ 的 $sg$ 值会变为 $0$。那么若 $a_{max}$ 有偶数个，整个游戏的 $sg$ 异或和仍为 $0$ 不会改变，否则会变成正整数。$a_{max}$ 有偶数个，整个游戏的 $sg$ 值不变，那么可以忽略这若干堆石子，此时 $a_{max}$ 改变，继续枚举。否则当 $k=a_{max}-1$ 时 $sg$ 值会改变，此时 Alice 必胜，有 $k_{max}=a_{max}-1$，输出这个值即可。

最后若找不到一个满足条件的 $k$，Alice 必败，输出 `0`。

# 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 250005;
int n, a[N];
int main() {
    scanf("%d", &n);
    int sum = 0;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sum ^= a[i];
    if (sum) {
        printf("-1");
        return 0;
    }
    sort(a + 1, a + n + 1);
    for (int i = n, cnt = 0; i >= 0; i--) {
        if (a[i] != a[i + 1]) {
            if (cnt & 1) {
                printf("%d", a[i + 1] - 1);
                return 0;
            }
            cnt = 0;
        }
        cnt++;
    }
    printf("0");
    return 0;
}
```

# 启示

- 多次博弈大胆考虑 $sg$ 函数

---

## 作者：Skeleton_Huo (赞：0)

# [ARC168B] Arbitrary Nim 题解

#### 废话
~~每次看题解都会感叹以前总结的一些作题技巧怎么又没用上。~~

我会将思路历程尽量将清楚。

## 正文

首先应该解决 $k$ 给定时的问题，这样才最有可能得到足够的分析素材。

给定 $k$ 后，就是一个十分朴素的限定了拿物品数量的 Nim 游戏，列个表找规律，就会发现 $SG(a_i) = a_i \bmod (k+1)$，十分简单。为了表述方便，我们用 $l$ 表示 $k + 1$。

因此问题变成了：求最大的 $l$，使得 $(a_1 \bmod l) \oplus (a_2 \bmod l) \oplus \dots \oplus (a_n \bmod l) \neq 0$。

这个式子是位运算和算数运算的混合，数学的变式可能不好使。但拿到这个式子，我们应该会想去动一动 $l$，看看整体的结果会怎么变。

我们发现，当 $l$ 充分大时，我们的式子相当于 $a_1 \oplus a_2 \oplus \dots \oplus a_n$，也就是说，如果它已经非 $0$ 了，那么 $l$ 无论取什么值，结果都一样，依据题意，可以直接输出 `-1`。

于是我们只需要考虑 $a_1 \oplus a_2 \oplus \dots \oplus a_n = 0$，的情况即可，一下子简化了许多。

此时我们知道它们是若干数字的异或和，并且结果是 $0$，我们也许能想到，对于 $a$ 中相同的元素，无论 $l$ 取什么，它们都是能直接消掉的，这样就能简化问题了。基于这个思路，我们引入一个计数器，$cnt(v)$ 表示 $a$ 中 $v$ 出现的次数。

考虑简单点的情况，如果所有 $cnt(v)$ 都是偶数，显然原不等式是无解的，输出 `0`。

如果有奇数呢？我们先将能两两抵消的先消掉，$l$ 显然只会对剩下的数，也就是出现奇数次的数产生影响。由小到大扩大影响，观察现象。

记最大的使得 $cnt(v)$ 为奇数的 $v$ 为 $m$，如果 $l > m$，也就是没有影响，此时原式为 $0$，不可取。我们再尝试让 $l$ 影响最大的那个数，取 $l = m$，假设原式除了 $m$ 的部分记为 $x$，那么有 $x \oplus m = 0$，即 $x = m$，由于 $m \neq 0$，所以 $x \neq 0$，此时 $m$ 没了，原式的值变为 $x \neq 0$，因此 $l = m$ 记为一个解，并且为最大解。

因此 $k = m - 1$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2.5e5 + 10;

int n;
set<int> s;

int main() {
  cin >> n;
  
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    sum ^= a;
    if (s.count(a)) s.erase(a);
    else s.insert(a);
  }

  if (sum != 0) cout << "-1";
  else if (s.empty()) cout << "0";
  else cout << *s.rbegin() - 1;

  return 0;
}
```

---

