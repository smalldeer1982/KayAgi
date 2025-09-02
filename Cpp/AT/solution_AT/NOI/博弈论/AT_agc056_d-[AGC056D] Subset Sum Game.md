# [AGC056D] Subset Sum Game

## 题目描述

黑板上写有 $N$ 个整数，其中第 $i$ 个整数为 $A_i$。已知 $N$ 是偶数。同时，给定整数 $L,R$。

Alice 和 Bob 进行一场游戏。两人轮流操作，由 Alice 先手。每一回合，当前玩家从黑板上选择一个数并将其擦去。

经过 $N$ 回合后，游戏结束。此时，设 Alice 擦去的所有整数之和为 $s$。如果 $L \leq s \leq R$，则 Alice 获胜；否则 Bob 获胜。假设双方都采取最优策略，问最终谁会获胜。

## 说明/提示

## 限制条件

- $2 \leq N \leq 5000$
- $N$ 是偶数
- $1 \leq A_i \leq 10^9$
- $0 \leq L \leq R \leq \sum_{1 \leq i \leq N} A_i$
- 所有输入的值均为整数

## 样例解释 1

在本场游戏中，Alice 一定能够获胜。以下是游戏进行的一个例子：
- Alice 擦去 $1$。
- Bob 擦去 $4$。
- Alice 擦去 $5$。
- Bob 擦去 $3$。
此时，Alice 擦去的整数之和为 $6$，满足 $L \leq 6 \leq R$，因此 Alice 获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 5 6
3 1 4 5```

### 输出

```
Alice```

## 样例 #2

### 输入

```
2 2 3
4 1```

### 输出

```
Bob```

## 样例 #3

### 输入

```
30 655 688
42 95 9 13 91 27 99 56 64 15 3 11 5 16 85 3 62 100 64 79 1 70 8 69 70 28 78 4 33 12```

### 输出

```
Bob```

## 样例 #4

### 输入

```
30 792 826
81 60 86 57 5 20 26 13 39 64 89 58 43 98 50 79 58 21 27 68 46 47 45 85 88 5 82 90 74 57```

### 输出

```
Alice```

# 题解

## 作者：joke3579 (赞：16)

## $\text{statement}$

一块黑板上写着 $n$ 个整数。第 $i$ 个整数记作 $a_i$。保证 $n$ 是偶数。此外，给定 $L,R$。

Alice 和 Bob 在玩一个游戏。他们轮流操作，Alice 先手。在每一轮中，玩家需要选择一个写在黑板上的数，并擦掉它。

游戏会在 $n$ 轮后结束。令 $s$ 为 Alice 擦掉的数之和。若 $L \le s \le R$，则 Alice 胜利，反之 Bob 胜利。你需要输出当两方都采取最优策略情况下的赢家。

$2\le n\le 5000,\ 1\le a_i\le 10^9, 0\le L \le R \le \sum_{1\le i\le n} a_i$。

## $\text{solution}$

记 $S = \sum_{1\le i\le n} a_i$，$S_A$ 为 Alice 擦掉的数之和，$S_B$ 为 Bob 擦掉的数之和。  
记一个长为 $m$ 序列 $b_i$ 的邻项差分 $\text{diff }b = (b_2 - b_1) + (b_4 - b_3) + \cdots + (b_m - b_{m-1})$。

首先转化题意。条件 $L \le S_A \le R$ 可以通过整体乘 $2$ 减 $S$ 转化为 $2L - S \le S_A - S_B \le 2R - S$。随后设 $x = S - (L + R)$，整体加 $x$ 后变为 $L - R \le x + S_A - S_B \le R - L$，即 $|x + S_A - S_B| \le R - L$。

因此有转化后的问题：   
给定整数 $x$。两人轮流操作，每次选择一个没有选过的数字 $a_i$。在 Alice 的回合，置 $x=x + a_i$，而在 Bob 的回合置 $x=x - a_i$。最终的分数即为 $x$ 的绝对值。Alice 的目标是最小化这个值，而 Bob 的目标是最大化它。求当两方都采取最优策略情况下的赢家。    

不妨假设 $a_i$ 升序排列。我们断言，最终的分数可以通过如下方式求得：
- 选择整数 $p$，将 $p, p + x, a_1, a_2,\cdots, a_n$ 升序排列得到 $A_i$。令 $p$ 的答案为 $\text{diff }A$ 的值。
- 最终的分数即为所有可能的 $p$ 的答案中的最小值。

容易发现 $p$ 所有对答案有贡献的取值为 $p = a_i$。对于 $p$ 的某一确定取值可以在 $O(n)$ 的时间复杂度内计算答案，取其中最小值作为最终分数即可。   
因此有总时间复杂度 $O(n^2)$ 的算法。

证明：

可以通过如下方式计算分数：Alice 操作后，黑板上剩余 $n-1$ 个整数。将目前可选的 $n-1$ 个整数与目前的 $x$ 一同进行升序排序，得到序列 $b_i$。Bob 操作后的分数即为 $\text{diff }b$。

使用数学归纳法证明该方式的正确性。   
当 $n=2$ 时正确性显然。

假设已经证明了对 Bob 来说 $n=k$ 的情况是成立的，现在需要证明对 Alice 来说 $n=k + 1$ 的情况也是成立的。   
Alice 的目标等价于将其中一个 $a_i$ 更换为 $a_i + x$，使得 Bob 的分值最小。选择 $a_i$ 对应着选择 $p = a_i$，这样的策略肯定能够产生可能得到的分数中最小的值，因此对 Alice 来说 $n=k + 1$ 的情况通过该方式计算是正确的。

假设已经证明了对 Alice 来说 $n=k + 1$ 的情况是成立的，现在需要证明对 Bob 来说 $n=k+2$ 的情况也是成立的。   
我们将 Bob 可选的 $n-1$ 个整数与目前的 $x$ 一同进行升序排序，得到序列 $b_i$。令 $b_s = x$。如果 Bob 在本轮中选择了 $b_t(s \neq t)$，那么 Alice 可以选择 $p=b_t$ 来得到分数 $\text{diff }b$。因此该值是分数的一个上界。    
这个上界是可以取到的。不妨假设 $s$ 是奇数。如果 Bob 在 $s=1$ 时选择 $t=n$，在其余时刻选择 $t = s-1$，最终的分数就是该值。当 $s$ 为偶数的时候类似：当 $s=n$ 时选择 $t=1$，在其余时刻选择 $t =s+1$ 即可。

根据数学归纳法，原断言成立。

总时间复杂度 $O(n^2)$。

$\text{code : }$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
int n, l, r, a[5005], s;
vector<int> ans;

signed main() {
	cin >> n >> l >> r; 
	rep(i,1,n) cin >> a[i], s += a[i]; s -= l + r;
	sort(a + 1, a + 1 + n);
	int ret = LLONG_MAX, now;
	rep(i,1,n) {
		ans.clear(); now = 0;
		rep(j,1,n) if (i != j) ans.emplace_back(a[j]);
		ans.insert(lower_bound(ans.begin(), ans.end(), a[i] + s), a[i] + s);
		for (int i = 0; i < ans.size(); i += 2) now += ans[i + 1] - ans[i];
		ret = min(ret, now);
	} puts(abs(ret) <= r - l ? "Alice" : "Bob");
}
```

---

## 作者：TempestMiku (赞：6)

# [[AGC056D] Subset Sum Game](https://www.luogu.com.cn/problem/AT_agc056_d)

## 一、题目大意：

一块黑板上写着 $n$ 个整数。第 $i$ 个整数记作 $a_i$。保证 $n$ 是偶数。此外，给定 $L,R$。

Alice 和 Bob 在玩一个游戏。他们轮流操作，Alice 先手。在每一轮中，玩家需要选择一个写在黑板上的数，并擦掉它。

游戏会在 $n$ 轮后结束。令 $s$ 为 Alice 擦掉的数之和。若 $L \le s \le R$，则 Alice 胜利，反之 Bob 胜利。你需要输出当两方都采取最优策略情况下的赢家。

## 二、题意转化：

设 $S_a$ 为 Alice 擦掉数的总和，$S_b$ 为 Bob 的擦掉数的总和，设 $S$ 为两所有数的总和。题目要求：
$$L\le S_a\le R$$ 
我们将三边都乘二减去 $S$，变成：

$$2L-S\le 2S_a-S\le 2R-S$$

设 $x$ 为 $S-(L+R)$，整体加上 $x$ 之后变成：
$$L-R\le x+S_a-S_b\le R-L$$
转化一下后变成：
$$|x+S_a-S_b|\le R-L$$

这个时候，我们将题意转化完成了：

给定整数 $x$，Alice 操作是选择一个数 $a_i$ 使 $x=x+a_i$，Bob操作是选择一个数 $a_i$，使 $x=x-a_i$，Alice 想使 $x$ 尽量小，Bob 想使 $x$ 尽量大，在最优策略下问谁能赢。

## 三、思路

Alice 想使 $x$ 尽量小，又因为是 $+S_a$，所以选择绝对值小的数。

Bob 想使 $x$ 尽量大，又因为是 $-S_b$，所以也选择绝对值小的数。

将 $a$ 数组升序排列之后，当 $x=0$ 时，我们发现按上面两行所说应该是

$$(a_1-a_2)+(a_3-a_4)+\dots+(a_{n-1}-a_n)$$

但是因为转化后的题意让你求的是绝对值大小，而 $(a_1-a_2)$ 这样的是小数减去大数，结果是负数，我们将它称为**下界**，即绝对值里面的最小值（负数），我们将它相反一下得到**上界**，即一个临项差分形式：

$$(a_2-a_1)+(a_4-a_3)+\dots+(a_{n}-a_{n+1})$$

但是当 $x\ne 0$ 时，我们如果这样想是错误的：单独算出临项差分后，在加个 $x$。因为临项差分是将 $a$ 数组升序排列之后取的结果，如果你单独加 $x$ 的话，那就是默认是 Alice 取的了，但是实际上 Bob 也能取，那么怎么判断是 Alice 取还是 Bob 取呢？

如果想要把 $x$ 的贡献加进去，我们需要将某个 $a_i$ **替换**成 $a_i+x$ 后升序排列，再用差分求出答案，将每个 $a_i$ 都试过之后，得到的最小答案即为最终结果，判断一下是否满足
 $|x+S_a-S_b|\le R-L$ 就行了。
 
 差分形式能是一个序列的**最优策略**，替换之后升序的序列用差分形式也是最优策略，而单独加 $x$ 却不一定是。
 
 因为我们计算临项差分插入元素，又循环枚举 $a_i$，所以时间复杂度 $n^2$。
 
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
int n,l,r,Tempestissimo(LONG_LONG_MAX);
int x(0);
const int N=5005;
int a[N],b[N];
int cnt1,cnt2;
vector<int> q;
// priority_queue<int,vector<int>,greater<int>> q;
signed main(void){
    n=read(),l=read(),r=read();
    for(register int i=1;i<=n;i++){
        a[i]=read();
        x+=a[i];
    }
    x-=(l+r);
    sort(a+1,a+n+1);
    for(register int i=1;i<=n;i++){
        int cnt=0;
        q.clear();
        for(register int j=1;j<=n;j++){
            if(i==j) continue;
            q.push_back(a[j]);
        }
        int ans=0;
        q.insert(lower_bound(q.begin(),q.end(),a[i]+x),a[i]+x);
        bool flag=true;
        for(register int j=0;j<n;j+=2){
            ans+=(q[j+1]-q[j]);
        }
        Tempestissimo=min(Tempestissimo,ans);
    }
    if(abs(Tempestissimo)<=r-l){
        puts("Alice");
    }
    else{
        puts("Bob");
    }
    return 0;
}
```



---

## 作者：Ratio_Y (赞：5)

蒟蒻首篇黑题题解。

---


## 思路
看到 Alice 和 Bob 就知道是博弈论的题了。

我们发现，$n$ 为偶数时没有什么突破口。那么尝试考虑 $n$ 为奇数，Alice 赢，Bob 先行动的情况，那么此时主动权就来到了 Bob 手上，他每次行动后，Alice 会有一个最优策略来应对 Bob 的行动。

这样的话，整个数列会被分成若干个数对和一个剩余的数。不难发现，数列中相邻的两个数配对是 Alice 赢的最好策略。那么也就是说，Alice 的最优策略是选与 Bob 配对的另一个数（当然是在 Bob 使用最优策略的前提下）。

那么现在的局面是，Bob 具有主动权（先手），但最后剩余的数是 Alice 决定的，因此我们可以枚举最后剩余的数，这样 Alice 所选数之和的上下边界就确定了，因而可以得出在该情况下，Alice 是否必胜的结论。

解法方面，分别求出奇数位和偶数位上的和，枚举每次最后剩余的数，由于它可能会影响数位上的数的变化，我们对于每类数位要开两个变量，在这里先统称为 A 与 B，表示奇数位和与偶数位和，那么显然 SumAlice 只能取到这个范围内的值，因此若 $l\le A$ 并且 $B\le r$，那么 Alice 是必胜的。

现在已经得到了 $n$ 为奇数，Bob 先手的做法。迁移到 $n$ 为偶数上，我们只要先排去 Alice 先手的那一步不就可以了吗。所以先枚举 Alice 先手所选的数（当然超过 $r$ 的数选了就直接寄了，这时候结束枚举就行了），再枚举最后剩下的那个数，求出奇偶数位上值的和，按上述方法判断即可，这里判断要加上开始枚举的 Alice 首选的那个值。复杂度是 $\mathcal{O(n^2)}$ 的，$n\le 5000$，显然能过。

还有，注意 $a_i$ 的值域是 $10^9$ 级别的，计算和的时候要开 `long long`。

## Code：
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Ratio=0;
const int N=5005;
int T,n;
ll l,r,a[N],b[N];
namespace Wisadel
{
	short main()
	{
		scanf("%d",&T);
		while(T--)
		{
			scanf("%d%lld%lld",&n,&l,&r);
			bool Alicewin=0;
			for(int i=1;i<=n;i++) scanf("%d",&a[i]);
			sort(a+1,a+1+n);
			for(int i=1;i<=n;i++)
			{// 先枚举 Alice 首选
				if(a[i]>r) break;
				ll jied=a[i],oued=a[i],ji=0,ou=0;
				// 分别表示枚举过和未枚举的奇偶数位之和，这里提前就把 a[i] 加上了
				// 这里枚举与否取决于最下面循环的进行程度，感性理解一下
				for(int j=1;j<=n;j++)
					if(i!=j) b[(j>i?j-1:j)]=a[j];
				for(int j=1;j<n;j++)
					if(j&1) ji+=b[j];
					else ou+=b[j];
				for(int j=1;j<n;j++)
				{// 枚举最后剩下的数
					if(j&1) ji-=b[j];
					else ou-=b[j];
					if(l<=jied+ou&&oued+ji<=r)
					{
						Alicewin=1;
						break;
					}
					if(j&1) jied+=b[j];
					else oued+=b[j];
				}
				if(Alicewin) break;
			}
			if(Alicewin) printf("Alice\n");
			else printf("Bob\n");
		}
		return Ratio;
	}
}
int main(){return Wisadel::main();}
```
## 部分细节
代码中有一句 `if(l<=jied+ou&&oued+ji<=r)`，赛时调了好一会才改出来。这样写的原因是：我们无论抽走哪一个数，都会使之后的数发生整体的数位奇偶变化，我们开始求得的奇偶数位上数之和其实一直是反的。但是手搓几组数据就会发现，无论如何，二者上下界关系没有变。

完结撒花~

---

## 作者：EuphoricStar (赞：4)

考虑若 $n$ 是奇数怎么做。枚举 Alice 第一次选的数 $a_i$，然后考虑把剩下的数两两结成一个匹配，若 Bob 选了其中一个，Alice 就选另一个。容易发现排序后奇数位和它右边的偶数位匹配最优。那么设奇数位的和为 $A$，偶数位的和为 $B$，此时 Alice 获胜当且仅当 $L \le A + a_i \land B + a_i \le R$。

若 $n$ 是偶数，仍然考虑沿用上面的做法，把数结成匹配做。仍然枚举 Alice 第一次选的数，和这个数匹配的数，那么剩下的数仍然奇数位匹配右边偶数位最优。若 Bob 选了这个数匹配的数，Alice 可以新开一个匹配，否则 Alice 选 Bob 选的数匹配的数即可。

需要枚举 Alice 第一次选的数和这个数匹配的数，复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/agc056/submissions/46151567)

----

题外话：这题被放到了 NOIP 模拟赛 T1，但是 Alice 的获胜条件是 $s \notin [L, R]$。

---

## 作者：Union_of_Britain (赞：2)

比较简易和感性（？)的理解。

枚举 Alice 最先选的一个值，剩下的选的顺序应该是：

$$(\text {Bob}-\text{Alice})-(\text {Bob}-\text{Alice})-\dots -(\text {Bob}-\text{Alice})-\text{Bob}$$

这样的序列对其分组，一个括号里面是一组。

考虑这样的组，是 Bob 具有主动权，即 Bob 先选。而 Bob 的想法，一定是一直让他变大，或者一直变小，而 Alice 以组内另一个东西来应对。

先尝试考察这个组的性质。设有 $x\le y\le z\le w$。那么，把 $(x,w)$ 和 $(y,z)$ 这样分组，一定不优于 $(x,y)$ 和 $(z,w)$。原因是 $|x-w|+|y-z|\ge |x-y|+|z-w|$，由于 Bob 有主动权，所以说 Bob 可以使 Alice 变化的幅度就越大，这样是不利于 Alice 控制其范围的（因为 Bob 的目的就是一直变大或者一直变小）。所以，分组的策略一定是把待分组的东西排序（设排序后为 $\{a_i\}$），选 $(a_1,a_2),(a_3,a_4),(a_5,a_6)\dots$

还有最后一个的问题。发现上面的过程没有给出最后一个 Bob 留下来的是啥；这样看来，最后一个（Alice 留给）Bob 选的是由 Alice 决定的，由于数据范围 $n\le 5000$，不妨枚举 Bob 最后选的。

还有一个问题，Bob 有没有可能不听 Alice 的，要在半途去选 Alice 留给他最后一个选的？不可能。Bob 总是要选这个东西，而半途去选会导致丧失至少一组的主动权而使得 Bob 丢失自己的策略（至少变得不优）。在最后再做不会影响 Bob 的策略，是不劣的。

那么枚举 Alice 第一个选的和留给 Bob 的最后一个是什么即可，分组可以在枚举第一个选的的时候处理奇偶前后缀和然后 $O(1)$ 得到。如果 Bob 选 $a_2,a_4,\dots$ 或者 $a_1,a_3,\dots$ 的情况 Alice 都满足条件，就找到 Alice 的必胜策略了。

时间复杂度 $O(n^2\log n)$，瓶颈是排序，精细实现是 $O(n^2)$。

讲个笑话，这个题在模拟赛出过弱化版，然后我们的同学思考会不会 Alice 欺骗 Bob 或者 Bob 欺骗 Alice，迷惑他的策略，然后自己一波拿下，直接赢赢赢。最后发现，你赢赢赢，最后是输光光。

```cpp
// Problem: [AGC056D] Subset Sum Game
// Platform: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc056_d
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Author:British Union
// Long live UOB and koala
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e3+5;
int n,L,R,a[maxn],s1[maxn],s2[maxn],h1[maxn],h2[maxn],b[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>L>>R;
	for(int i=1;i<=n;i++)cin>>a[i];
	bool ck=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(j<i)b[j]=a[j];
			else if(j>i)b[j-1]=a[j];
		}
		sort(b+1,b+n);
		for(int j=1;j<=n-1;j++){
			s1[j]=s1[j-1]+(j%2)*b[j];
			s2[j]=s2[j-1]+(1-j%2)*b[j];
		}
		for(int j=n-1;j>=1;j--){
			h1[j]=h1[j+1]+(j%2)*b[j];
			h2[j]=h2[j+1]+(1-j%2)*b[j];
		}
		for(int j=1;j<=n-1;j++){
			int A=a[i]+s1[j-1]+h2[j+1],B=a[i]+s2[j-1]+h1[j+1];
			if(L<=A&&L<=B&&A<=R&&B<=R){
				ck=1;break;
			}
		}
		if(ck)break;
	}
	if(ck)cout<<"Alice"<<endl;
	else cout<<"Bob"<<endl;
	return 0;
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/vzob7js0.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

---

## 作者：Felix72 (赞：1)

如果 Bob 先手呢？

我们发现，Bob 如果有先手优势，可以通过如下方法逼 Alice 选出理论下界：

> 把 $2k$ 个数先排序，再按顺序两两分组 $(a_1, a_2), (a_3, a_4), \dots, (a_{2k - 1}, a_{2k})$。每次选没有人选过的数中的最大值。

这样无论 Alice 怎么选，最大只能选出 $\sum_{i = 1}^{2k} a_i[i \bmod 2 = 1]$。

同理，Bob 也可以逼 Alice 选出理论下界。如果选出上界、选出下界两种极端情况中有一种不合法，那么 Alice 就无力回天了。否则 Alice 随便赢，设这样的 $2k$ 个数为**优势数组**。

Alice 先手的最优策略，我们通过刚才的分析可见一斑。假设 Alice 先选了一个元素，那么还剩 $n - 1$ 个元素。假如我们能在 $n - 1$ 个元素中选出 $n - 2$ 个元素形成优势数组，那么 Alice 稳赢，因为只需做到每一组 $(a_{2i - 1}, a_{2i})$ 中恰好选出一个数就能处在上下界之间了。

如果选不出来呢？Bob 就可以像刚才一样逼上下界。举个例子：现在还剩 $n - 1$ 个数，从小到大排序 $b_1, b_2, \dots, b_{n - 1}$，不管 $b_{n - 1}$，把剩下的数两两分组，此时 Bob 先手，如果 Alice 打死不选 $b_{n - 1}$，那么 Bob 可以像上文一样逼上界；如果 Alice 选了，那么这个结果只会比上界还要大（$b_{n - 1}$ 是最大数），而因为没有优势数组，这个上界不合法，Alice 就输了。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc056_d)

**题目大意**

> 给定 $a_1\sim a_n$，两个人 A 和 B 轮流取数，最终如果 A 取出的数总和 $\in[L,R]$ 就胜利，问谁有必胜策略。
>
> 数据范围：$n\le 5000$，$n$ 为偶数。

**思路分析**

先考虑 $n$ 是奇数怎么做，那么枚举 A 第一次取出的数，剩下的就变成一个 B 先取的问题。

先考虑 B 能把取出的数最小化到什么程度，我们发现 A 可以选定一组匹配，B 选其中的某个元素，A 就选其匹配点，那么 A 最终能得到每组匹配中较小的数。

为了最大化这个数，A 肯定会把排序后相邻的元素结成匹配，即得到的最小值就是排序后奇数位上的值，这个和 $\ge L$ 时合法。

如果 B 想要最大化取出的数，那么 A 依然会选定匹配并取出每组匹配中较大的数，此时 A 的最优方案依然是把排序后相邻的元素结成匹配，得到排序后偶数位上的值，总和 $\le R$ 时合法。

回到原问题。

此时枚举 A 第一步的操作，那么会剩余奇数个元素并轮到 B 先手。

A 依然考虑把元素进行匹配，但是此时两两匹配后会在剩余一个元素在最后一次操作给 B。

并且这个元素也是由 A 控制的，枚举这个元素后再判定排序后奇数位和偶数位上的和是否合法即可。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5005;
ll L,R,a[MAXN],b[MAXN];
signed main() {
	int n;
	scanf("%d%lld%lld",&n,&L,&R);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) if(i^j) b[j-(j>i)]=a[j];
		array <ll,2> sl{0,0},sr{0,0};
		for(int j=1;j<n;++j) sr[j&1]+=b[j];
		for(int j=1;j<n;++j) {
			sr[j&1]-=b[j];
			if(L<=sl[1]+sr[0]+a[i]&&sl[0]+sr[1]+a[i]<=R) return puts("Alice"),0;
			sl[j&1]+=b[j];
		}
	}
	puts("Bob");
	return 0;
}
```

---

