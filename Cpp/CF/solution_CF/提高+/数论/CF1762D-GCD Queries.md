# GCD Queries

## 题目描述

This is an interactive problem.

There is a secret permutation $ p $ of $ [0,1,2,\ldots,n-1] $ . Your task is to find $ 2 $ indices $ x $ and $ y $ ( $ 1 \leq x, y \leq n $ , possibly $ x=y $ ) such that $ p_x=0 $ or $ p_y=0 $ . In order to find it, you are allowed to ask at most $ 2n $ queries.

In one query, you give two integers $ i $ and $ j $ ( $ 1 \leq i, j \leq n $ , $ i \neq j $ ) and receive the value of $ \gcd(p_i,p_j)^\dagger $ .

Note that the permutation $ p $ is fixed before any queries are made and does not depend on the queries.

 $ ^\dagger $ $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ . Note that $ \gcd(x,0)=\gcd(0,x)=x $ for all positive integers $ x $ .

## 说明/提示

In the first test, the interaction proceeds as follows.

 SolutionJuryExplanation $ \texttt{2} $ There are 2 test cases. $ \texttt{2} $ In the first test case, the hidden permutation is $ [1,0] $ , with length $ 2 $ . $ \texttt{? 1 2} $  $ \texttt{1} $ The solution requests $ \gcd(p_1,p_2) $ , and the jury responds with $ 1 $ . $ \texttt{! 1 2} $  $ \texttt{1} $ The solution knows that either $ p_1=0 $ or $ p_2=0 $ , and prints the answer. Since the output is correct, the jury responds with $ 1 $ and continues to the next test case. $ \texttt{5} $ In the second test case, the hidden permutation is $ [2,4,0,1,3] $ , with length $ 5 $ . $ \texttt{? 1 2} $  $ \texttt{2} $ The solution requests $ \gcd(p_1,p_2) $ , and the jury responds with $ 2 $ . $ \texttt{? 2 3} $  $ \texttt{4} $ The solution requests $ \gcd(p_2,p_3) $ , and the jury responds with $ 4 $ . $ \texttt{! 3 3} $  $ \texttt{1} $ The solution has somehow determined that $ p_3=0 $ , and prints the answer. Since the output is correct, the jury responds with $ 1 $ .Note that the empty lines in the example input and output are for the sake of clarity, and do not occur in the real interaction.

After each test case, make sure to read $ 1 $ or $ -1 $ .

## 样例 #1

### 输入

```
2
2

1

1
5

2

4

1```

### 输出

```
? 1 2

! 1 2


? 1 2

? 2 3

! 3 3```

# 题解

## 作者：Alex_Wei (赞：12)

不会做，哈哈。

询问一个数和其它所有数的 $\gcd$，因为 $\gcd(0, x) = x$，所以最大值一定是它本身。如果这个数大于 $1$，则其所有倍数除以这个数之后递归进入子问题，直到只剩两个数，说明一个是当前数，另一个是 $0$。若第一次询问没有抽到 $1$，则询问次数至多为 $n + \frac n 2 + \frac n 4 + \cdots < 2n$。如果第一次询问抽到 $1$，则需要额外花费 $n$ 次询问，一个解决方法是不断随机直到得到一对 $\gcd > 1$ 的数。不知道能不能过，没写。

正解就非常巧妙了。对于任意三个位置 $a, b, c$，根据 $\gcd(0, x) = x$ 的关键性质：

- 若 $\gcd(a, b) = \gcd(a, c)$，则 $a$ 一定不是 $0$。
- 若 $\gcd(a, b) > \gcd(a, c)$，则 $c$ 一定不是 $0$。
- 若 $\gcd(a, b) < \gcd(a, c)$，则 $b$ 一定不是 $0$。

我们用两次询问确定一个位置不是 $0$，直到候选集合只剩两个数。询问次数 $2n - 4$，可以通过。[代码](https://codeforces.com/contest/1762/submission/185406440)。

第一种思路和第二种思路究竟差在哪里？前者在 $n\geq 4$ 时可以确定 $0$ 的位置，没有利用好题目只要返回两个可能为 $0$ 的位置的性质。后者巧妙利用了题目要求，但无法确定 $0$ 的位置。

---

## 作者：NoirCube1 (赞：4)

### Preface

比较神仙的交互题，居然自己胡出来了。

不是很建议拿到题直接往题解区冲，这种题做一道少一道。

### Solution

下面简称 $\gcd(p_i,p_j)$ 为 $\text{zyf}(i,j)$。

这个限制看起来就像每两步询问就可以检验一个数是否为 $0$，或者直接判断其不为 $0$。但是直接下手有些困难，我们显然需要找到一些性质。

考虑到对于一个排列中元素都不相同，根据这个性质，如果 $p_i=0$，那么一定满足 $\text{zyf}(i,j)\not =\text{zyf}(i,k)$，反过来 $p_i\not =0$ 的充分条件是 $\text{zyf}(i,j) = \text{zyf}(i,k)$。

这一条看起来很有用，但是过于狭隘，不一定存在 $\text{zyf}(i,j)=\text{zyf}(i,k)$，而这又不是必要条件。考虑到这种情况已经需要询问 $2$ 次，我们不妨继续在 $\text{zyf}(i,j)$ 和 $\text{zyf}(i,k)$ 的大小关系上做文章。

于是考虑 $\text{zyf}(i,j)\not =\text{zyf}(i,k)$，此时发现没法判定 $p_i$，但是当 $p_i=0$ 的时候肯定 $j,k$ 都不为 $0$，如果 $p_i \not = 0$ 的时候就说明 $\text{zyf}(i,j)$ 和 $\text{zyf}(i,k)$ 是 $p_i$ 的两个**不同**的因数。

不妨设 $\text{zyf}(i,j)<\text{zyf}(i,k)$，那么即使最劣情况下 $\text{zyf}(i,k)=p_i$，无法判定 $p_k$，也可以判定 $p_j$，因为 $\gcd(p_j,p_i)\not= p_i\not=\gcd(p_i,0)$，所以 $p_j\not=0$。

在以上观察之后我们发现，任意的询问 $\text{zyf}(a,b)$ 和 $\text{zyf}(a,c)$ 都可以对满足 $x\in\{a,b,c\}$ 的 $x$ 进行判定其 $p_x\not=0$。于是我们发现只需要判定 $n-2$ 次就一定可以得到可能为 $0$ 的两个元素。

### Implementation

啊啊啊，$\mathcal O(n)$ 实现这玩意写挂了，所以我写了一个堆。毕竟交互题比较传统题更难调试一些。

```cpp
#include <bits/stdc++.h>
using namespace std;
int solve();
signed main() { int t; cin >> t; while (t--) solve(); return 0; }
int _gcd(int x, int y) { 
    cout << "? " << x << " " << y << endl;
    int r; cin >> r; return r;
}
int TESTIFY(int i, int j, int k) {
    int A = _gcd(i, k), B = _gcd(j, k);
    if(A == B) return k;
    if(A < B) return i;
    return j;
}
int solve() {
    int n;
    cin >> n;
    if(n == 2) {
        puts("! 1 2"); int x; cin >> x;
        return 0;
    }
    priority_queue<int> q;
    for(int i = 1; i <= n; i++) q.push(i);
    while(q.size() != 2) {
        int x = q.top(); q.pop();
        int y = q.top(); q.pop();
        int z = q.top(); q.pop();
        int w = TESTIFY(x, y, z);
        if(x != w) q.push(x);
        if(y != w) q.push(y);
        if(z != w) q.push(z);
    }
    cout << "! " << q.top() << ' ';
    q.pop();
    cout << q.top() << endl;
    int x; cin >> x;
    if(x == -1) return puts("WA");
    //This line will be never executed.
    return 0;
}
```

时间复杂度 $\mathcal O(n\log n)$。

---

## 作者：junee (赞：3)

# CF1762D 题解

## 题目分析

非常妙的题！

首先需要清楚一点 $\gcd(a,0)=\gcd(0,a)=a$。

考虑对三个数 $a,b,c$ 询问，每次询问 $\gcd(a,b),\gcd(a,c)$。

此时会出现三种情况：

- $\gcd(a,b) = \gcd(a,c)$，则 $a \neq 0$。

- $\gcd(a,b) < \gcd(a,c)$，则 $b \neq 0$。

- $\gcd(a,b) > \gcd(a,c)$，则 $c \neq 0$。

发现我们每进行两次询问都会确定一个位置不是 0。最后当只剩下两个位置时，直接输出即可，总询问次数 $2n-4$。

## Code

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
#include<queue>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
int T,n,ans;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		queue<int>q;
		for(int i=1;i<=n;i++)q.push(i);
		while(q.size()>2){
			int a=q.front();q.pop();
			int b=q.front();q.pop();
			int c=q.front();q.pop();
			int gab,gac;
			cout<<"? "<<a<<' '<<b<<'\n';
			cin>>gab;
			cout<<"? "<<a<<' '<<c<<'\n';
			cin>>gac;
			if(gab==gac){
				q.push(b),q.push(c);
			}
			else if(gab>gac){
				q.push(a),q.push(b);
			}
			else{
				q.push(a),q.push(c);
			}
		}
		cout<<"! "<<q.front()<<' ';q.pop();
		cout<<q.front()<<'\n';q.pop();
		cin>>ans;
	}
	return 0;
}

```

---

## 作者：MSqwq (赞：1)

有趣的交互题  

------------

题解：   
思考如果进行 $n-1$ 次循环，每次循环询问两次，就可以把一个数筛掉，那么 $2n-2$ 次询问一定可以找出来。   
如果你随便挑三个数出来，比如 $x,y,z$，进行询问，设 $op1 = ask(x,y)$，$op2 = ask(x,z)$。  
那么如果 $op1 = op2$ 是不是一定说明 $x$ 不为 $0$，因为如果是 $0$ ，那么 $op1 = y$，$op2 = z$ 但实际上 $y \ne z$，所以可以把 $x$ 丢掉。  
第二种情况 $op1 \ne op2$，再根据大小分类如果 $op1 < op2$，那么 $y$ 一定不为 $0$，就把它筛掉，因为和 $0$ 操作一定是本身，不会小于本身，同理如果 $op1 > op2$ 那么 $z$ 就一定不为 $0$，筛掉它。  
然后就完了。很简单的思维。可能很多人（包括我）最开始想的是每次找第一个数去和剩下的数比，每次把最大的那些留下，就可以筛掉一些，但最坏的情况就是第一个选到的数是 $1$ 就 GG 了，目前我还没想到怎么去避免这个问题，反正用上面那个是一定对的。   
代码：  
```
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}

void ask(int x,int y){cout<<"? "<<x<<" "<<y<<endl;}
void ans(int x,int y){cout<<"! "<<x<<" "<<y<<endl;}

void solve()
{
	int n;cin>>n;
	vector<int>v;
	for(int i=1;i<=n;i++)v.push_back(i);
	while(v.size()>2)
	{
		int a=v.back();v.pop_back();int b=v.back();v.pop_back();int c=v.back();v.pop_back();
		ask(a,b);int op1;cin>>op1;ask(a,c);int op2;cin>>op2;
		if(op1==op2)v.push_back(b),v.push_back(c);
		else 
		{
			if(op1<op2)v.push_back(a),v.push_back(c);
			else v.push_back(a),v.push_back(b);
		}
	}
	ans(v[0],v[1]);int x;cin>>x;
}

int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}
```


---

## 作者：strcmp (赞：0)

一开始去想找出一个大于 $\frac{n}{2}$ 的元素，有点想歪了。

这题正解是非常简洁的。

我们发现我们只需要 $x,\,y$ 中有一个是 $0$ 就行了，这点比较奇怪，咱肯定是要去利用它的。

那不妨去考虑维护两个变量 $u,\,v$，代表当前可能是 $0$ 的两个位置（只是假设，我们要用多的信息去排除）。初始令 $u = 1 ,\, v = 2$。

枚举 $w \in [3,\,n)$，然后考虑求出 $\gcd(p_u,\,p_w)$ 和 $\gcd(p_v,\,p_w)$。

- $\gcd(p_u,\,p_w) = \gcd(p_v,\,p_w)$，则 $p_w$ 必然不是 $0$，否则根据 $\gcd(p_u,\,0) = p_u,\,\gcd(p_v,\,0) = p_v,\,p_u \ne p_v$ 导出矛盾。

- $\gcd(p_u,\,p_w) < \gcd(p_v,\,p_w)$，则 $p_u$ 必然不是 $0$，否则 $\gcd(0,\,p_w) = p_w \ge \gcd(p_v,\,p_w)$。

- $\gcd(p_u,\,p_w) > \gcd(p_v,\,p_w)$，$p_v$ 必然不是 $0$，同理。

于是我们用两次询问就能排除一个数，询问次数 $2n - 4$，可以通过。

很妙啊。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
using namespace std;
using ld = double;
typedef long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 2e5 + 10, mod = 1e9 + 7;
const ll inf = 1145141919810520L; 
int T, n;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		if (n == 1) puts("! 1 1"), fflush(stdout);
		else if (n == 2) puts("! 1 2"), fflush(stdout);
		else {
			int u = 1, v = 2, w = 3, a, b;
			while (u <= n && v <= n && w <= n) {
				printf("? %d %d\n", u, w); fflush(stdout); scanf("%d", &a);
				printf("? %d %d\n", v, w); fflush(stdout); scanf("%d", &b);
				if (a == b) w = max({ u, v, w }) + 1;
				else if (a < b) u = w, w = max({ u, v, w }) + 1;
				else v = w, w = max({ u, v, w }) + 1;
			}
			printf("! %d %d\n", u, v); fflush(stdout); 
		}
		scanf("%*d");
	}
	return 0;
}
```

---

## 作者：baka24 (赞：0)

考虑 $0$ 与其他数做 $\gcd$ 有什么性质，对于 $(x,y)=a,(x,z)=b$：
- 任何数与 $0$ 做 $\gcd$ 的答案都是这个数本身，所以当 $a=b$ 时，因为 $y\ne z$ 所以 $x\ne 0$。
- 任何数的 $\gcd$ 小于这个数本身，所以当 $a>b$ 时，$z$ 一定不为 $0$，因为如果 $z$ 为 $0$，那么 $b=x$，但 $(x,y)\le x$，所以 $a$ 不能 $>b$。对于 $a<b$ 的情况同理。

我们发现每次可以排除一个数不为 $0$，所以用一个 `set` 储存符合条件的数，每次去掉一个，直到剩下两个输出即可。

#### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
set<int>st;
void slv(){
    cin>>n;st.clear();
    for(int i=1;i<=n;i++)st.insert(i);
    while(st.size()>=3){
        auto tmp=st.begin();
        int a1=(*tmp),a2,a3;tmp++;
        a2=(*tmp);tmp++;
        a3=(*tmp);
        printf("? %d %d",a1,a2);cout<<endl;
        int ans1;cin>>ans1;
        printf("? %d %d",a2,a3);cout<<endl;
        int ans2;cin>>ans2;
        if(ans1==ans2)st.erase(a2);
        else if(ans1>ans2)st.erase(a3);
        else st.erase(a1);
    }
    printf("! %d %d",*st.begin(),*st.rbegin());cout<<endl;
    cin>>n;
}
signed main(){
	int _;cin>>_;while(_--)
	slv();
    return 0;
} 	
```

---

## 作者：Siegerkranz_2735 (赞：0)

# 注意事项
一个数和 $0$ 的公约数是其本身。
# 做法
不难注意到题目最终所求是“$0$ 在哪两个位置中”而不是 $0$ 具体在哪里。这说明很有可能数很多的时候可以排除一些位置，而到只剩两个位置时就进行不下去了。

受此启发，我们来看看只剩三个数的情况。
设三个数是 $a,b,c,\gcd(a,b)=x,\gcd(b,c)=y$，那么

- $a=0\Rightarrow b=x\Rightarrow \gcd(b,c)=\gcd(x,c)=y\Rightarrow y\mid x\Rightarrow x\ge y$

- $b=0\Rightarrow a=x,c=y$，由于这是一个排列，所以 $x\neq y$

- $c=0\Rightarrow\dots \Rightarrow x\le y$ 

那么:
$$x<y\Rightarrow a\neq0$$
$$x=y\Rightarrow b\neq 0$$
$$x>y\Rightarrow c\neq0$$

原序列中，问题是一样的。只要一个个排除即可。
# 提示
输出完了答案记得读入那个“$1$”。

记得特判 $n<3$ 的情况。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int __t,n,__no_use;
    cin>>__t;
    while(__t--){
        cin>>n;
        if(n==1)cout<<"! 1 1"<<endl;
        else if(n==2)cout<<"! 1 2"<<endl;
        else{
            int a=1,b=2,c=3,x,y;
            for(int i=4;i<=n+1;i++){
                cout<<"? "<<a<<' '<<b<<endl;
                cin>>x;
                cout<<"? "<<b<<' '<<c<<endl;
                cin>>y;
                if(x>y)c=i;
                if(x==y)b=i;
                if(x<y)a=i;
            }
            if(a>n)cout<<"! "<<b<<' '<<c<<endl;
            if(b>n)cout<<"! "<<a<<' '<<c<<endl;
            if(c>n)cout<<"! "<<a<<' '<<b<<endl;
        }   
        cin>>__no_use;
    }
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

维护集合 $S$，保证 $0$ 所在的位置在 $S$ 中，初始 $S=\{1,2,3,\dots,n\}$,

我们的目的是从 $S$ 中删去一些元素，直到 $|S|\le 2$。

当 $|S|>2$，从 $S$ 中任选出三个位置 $x,y,z$，分别询问 $\gcd(a_x,a_y)$ 和 $\gcd(a_x,a_z)$：

- 若 $\gcd(a_x,a_y)=\gcd(a_x,a_z)$，因为 $a_y\ne a_z$，所以 $a_x\ne 0$，可以从 $S$ 中删去 $x$；
- 若 $\gcd(a_x,a_y)<\gcd(a_x,a_z)$，因为 $\gcd(a_x,a_z)\le a_x$，所以 $\gcd(a_x,a_y)<a_x$，则 $a_y\ne 0$，可以从 $S$ 中删去 $y$；
- 若 $\gcd(a_x,a_y)>\gcd(a_x,a_z)$，因为 $\gcd(a_x,a_y)\le a_x$，所以 $\gcd(a_x,a_z)<a_x$，则 $a_z\ne 0$，可以从 $S$ 中删去 $z$。

于是询问两次就可以删去一个数，要令 $|S|=2$ 只需删去 $n-2$ 个数，$2n-4$ 次询问可以通过。

```cpp
#include <cstdio>
int T, n;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        int i = 1, j = 2, k = 3;
        for (int o = 1, x, y; o <= n - 2; ++o)
        {
            printf("? %d %d\n", i, j), fflush(stdout), scanf("%d", &x);
            printf("? %d %d\n", i, k), fflush(stdout), scanf("%d", &y);
            if (x == y)
                i = j, j = k, ++k;
            else if (x < y)
                j = k, ++k;
            else
                ++k;
        }
        printf("! %d %d\n", i, j), fflush(stdout), scanf("%*d");
    }
    return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

发现可以用分类讨论来进行解决这个东西。

当我们给出 $x,y,z$ 三个数的时候，我们向他询问 $\gcd(x,y)$ 和 $\gcd(x,z)$ 他会给出几种类型。

当 $\gcd(x,y)=\gcd(x,z)$ 时 $x$ 一定是不等于零的，因为这是一个排列 $y$ 和 $z$ 一定不是相等的。

当 $\gcd(x,y)<\gcd(x,z)$ 时 $y$ 一定不等于零，因为 $\gcd(x,z)\le x$ 是显然成立的，然而 $y$ 等于零等式就变成了 $x<\gcd(x,z)$ 显然不成立。

当 $\gcd(x,y)>\gcd(x,z)$ 时 $z$ 一定不等于零。

最后两次询问就可以确定一个数是不是零，在 $2n$ 的范围以内，可以通过了。



---

## 作者：User_Authorized (赞：0)

## 题面
给定一个长度为 $n$ 的排列 $0, 1, \cdots, n - 1$。可以进行最多 $2n$ 次询问，每次询问给出两个下标 $i, j$，交互器会返回 $\gcd(p_i, p_j)$。询问以后，需要输出两个下标 $x, y$，满足 $p_x = 0 \lor p_y = 0$。特别地，$\gcd(0, x) = x$。

## 题解
观察次数限制，我们需要用不多于 $2$ 次询问判断出一个数是否为 $0$，考虑到排列中元素互不相通的性质，所以有 $p_k = 0 \Rightarrow \gcd(p_i, p_k) \neq \gcd(p_j, p_k)$。转化一下，可以得出 $\gcd(p_i, p_k) = \gcd(p_j, p_k) \Rightarrow p_k \neq 0$，但是显然这种判断方法不能保证每 $2$ 次询问便筛出一个元素。考虑在对于三个下标 $a, b, c$，获得了 $\gcd(p_a, p_b), \gcd(p_a, p_c)$ 两个值的情况下，如何推导出更多信息。

发现 $\gcd(p_a, p_b) \le x, \gcd(p_a, 0) = p_a$，所以可以推出

$$\gcd(p_a, p_c) < \gcd(p_a, p_b) \Rightarrow p_c \neq 0$$

证明考虑利用上述不等式推导

$$\gcd(p_a, p_c) < \gcd(p_a, p_b) \Rightarrow \gcd(p_a, p_c) < \gcd(p_a, p_b) \le p_a = \gcd(p_a, 0) \Rightarrow p_c \neq 0$$

对称地，可以得出

$$\gcd(p_a, p_b) < \gcd(p_a, p_c) \Rightarrow p_b \neq 0$$

综上，我们可以得出结论：

- $\gcd(p_a, p_b) = \gcd(p_a, p_c) \Rightarrow a \neq 0$
- $\gcd(p_a, p_b) < \gcd(p_a, p_c) \Rightarrow p_b \neq 0$
- $\gcd(p_a, p_c) < \gcd(p_a, p_b) \Rightarrow p_c \neq 0$

所以我们对于任意三个下标 $a, b, c$，询问出 $\gcd(p_a, p_b), \gcd(p_a, p_c)$ 两个值，一定可以排除一个下标对应的元素，最多需要排除 $n - 2$ 次。最多共询问 $2\left(n - 2\right)$ 次，可以通过本题。

## Code
```cpp
//Codeforces - 1762D
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        if (N == 2) {
            std::cout << "! 1 2" << std::endl;

            valueType result;

            std::cin >> result;

            if (result == -1)
                return 0;

            continue;
        }

        ValueVector source(N);

        std::iota(source.begin(), source.end(), 1);

        while (source.size() >= 3) {
            std::cout << "? " << source[0] << ' ' << source[1] << std::endl;

            valueType result_0_1;

            std::cin >> result_0_1;

            std::cout << "? " << source[0] << ' ' << source[2] << std::endl;

            valueType result_0_2;

            std::cin >> result_0_2;

            if (result_0_1 == result_0_2) {
                source.erase(source.begin());
            } else if(result_0_1 > result_0_2) {
                source.erase(source.begin() + 2);
            } else {
                source.erase(source.begin() + 1);
            }
        }

        std::cout << "! " << source.front() << ' ' << source.back() << std::endl;

        valueType result;

        std::cin >> result;

        if (result == -1)
            return 0;
    }

    return 0;
}
```

---

## 作者：koobee (赞：0)

本人的第一道交互题，考场最后三分钟调出来了（复制的东西没改，警示后人）。

题意：交互题，$p$ 是一个 $[0,1,...,n-1]$ 的排列，至多可做 $2n$ 次询问，每次询问包含两个正整数 $i$，$j$，会给出的回复是 $gcd(p_i,p_j)$,最终要求出0的位置（只要锁定某两个数中必有一个为 $0$ 即可）

先尝试一下：如果知道 $gcd(a,b)$ 和 $gcd(a,c)$，会的到什么？

猜：会排除一个数为 $0$ 的可能；

证：讨论他们的大小关系。

1. $gcd(a,b)>gcd(a,c)$ 此时可得出，若 $c=0$,
$gcd(a,c)=a$，$gcd(a,b)<a$,矛盾，因此 $c$ 不为 $0$。

2. $gcd(a,b)=gcd(a,c)$,此时若 $a=0$ 则 $gcd(a,b)=b$，$gcd(a,c)=c$,可推出 $b=c$，矛盾， 因此 $c$ 不为 $0$。

3. $gcd(a,b)>gcd(a,c)$ 原理同第一种情况，$b$ 不为 $0$。

证毕。

这样，每做 $2$ 次询问就能会排除一个数为 $0$ 的可能，最后会做 $2n-4$ 次询问，做法可行。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e4+5;
int t, n, a[N], f[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n == 2){
			cout<<"? 1 2"<<endl;
			int x;
			cin>>x;
			cout<<"! 1 2"<<endl;
			cin>>x;
			if(x == -1) return 0;
			continue;
		}
		memset(f, 0, sizeof(f));
		int a=1, b=2, c=3;
		while(a <= n && b <= n && c <= n){
			//cout<<a<<" "<<b<<" "<<c<<endl;
			int x, y;
			cout<<"? "<<a<<" "<<b<<endl;
			cin>>x;
			cout<<"? "<<a<<" "<<c<<endl;
			cin>>y;
			if(x > y){
				f[c] = 1;
				while(c <= n && (f[c] || (c == a || c == b))) c++;
			}
			if(x < y){
				f[b] = 1;
				while(b <= n && (f[b] || (b == a || c == b))) b++;
			}
			if(x == y){
				f[a] = 1;
				while(a <= n && (f[a] || (c == a || a == b))) a++;
			}
		}
		if(a > n) cout<<"! "<<b<<" "<<c<<endl;
		if(b > n) cout<<"! "<<a<<" "<<c<<endl;
		if(c > n) cout<<"! "<<a<<" "<<b<<endl;
		int x;
		cin>>x;
		if(x == -1) return 0;
	}
	return 0;
}
```


---

## 作者：_H17_ (赞：0)

## 题目分析

思维脑筋急转弯，你会做吗？

考虑每次随便乱选 $3$ 个数，分别记为 $a,b,c$。

求 $\gcd(a,b),\gcd(a,c)$，然后进行比较操作。

需要利用的性质 $\gcd(0,x)=x$，同时 $\gcd(0,x)>\gcd(x,y)(y>0)$。

然后我们进行分类讨论：

1. 相等：显然如果 $a=0$ 的话，两个值分别是 $b,c$，它们显然不等，所以排除 $a$。

2. 前者小：显然如果 $b=0$ 前者是 $a$，后者一定比 $a$ 小，所以排除 $b$。

3. 后者小：同上，排除 $c$。

我们使用了 $2$ 次比较去掉一个数，一共 $n$ 个数，最后要去到 $2$，所以去掉 $n-2$ 个数，也就是 $2(n-2)$ 次操作，符合要求。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,res1,res2;
void Main(){
    cin>>n;
    priority_queue<int>q;
    for(int i=1;i<=n;i++)
        q.push(i);
    while(q.size()>2){
        int top1,top2,top3;
        top1=q.top(),q.pop();
        top2=q.top(),q.pop();
        top3=q.top(),q.pop();
        cout<<"? "<<top1<<' '<<top2<<endl;
        cin>>res1;
        cout<<"? "<<top1<<' '<<top3<<endl;
        cin>>res2;
        if(res1==res2)
            q.push(top2),q.push(top3);
        else if(res1<res2)
            q.push(top1),q.push(top3);
        else
            q.push(top1),q.push(top2);
    }
    cout<<"! "<<q.top()<<' ';
    q.pop();
    cout<<q.top()<<endl;
    cin>>res1;
    assert(res1==1);
    return;
}
int main(){
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

---

## 作者：cmk666 (赞：0)

[题目传送门](/problem/CF1762D)

由于询问数的上限为 $2n$，这启示我们用两次询问来排除一个不可能为 $0$ 的位置。

我们可以考虑询问 $x=\gcd(p_a,p_b)$ 和 $y=\gcd(p_a,p_c)$：

- 若 $x=y$，那么 $p_a$ 不可能是 $0$（反之 $x=p_b=y=p_c$，但 $p_b\ne p_c$，矛盾）；
- 若 $x<y$，那么 $p_b$ 不可能是 $0$（反之 $x=p_a<y$，但 $y=\gcd(p_a,p_c)\le p_a$，矛盾）；
- 若 $x>y$，那么 $p_c$ 不可能是 $0$（反之 $x>y=p_a$，但 $x=\gcd(p_a,p_b)\le p_a$，矛盾）。

因此无论结果如何，都能排除一个位置。

于是一直做直到最后只剩 $2$ 个可行位置并回答即可，询问次数为 $2n-4$。

核心代码如下：
```cpp
inline int ask(int x, int y) { /* 询问 x,y */ }
inline void ans(int x, int y) { /* 回答 x,y */ }
int n, x, y, l; vector < int > v;
inline void work()
{
	read(n), v.clear();
	For(i, 1, n) v.push_back(i);
	while ( ( l = v.size() ) > 2 ) // 根据上面的方法排除可行位置
	{
		x = ask(v[l - 1], v[l - 2]), y = ask(v[l - 1], v[l - 3]);
		if ( x == y ) v.erase(v.begin() + l - 1);
		if ( x < y ) v.erase(v.begin() + l - 2);
		if ( x > y ) v.erase(v.begin() + l - 3);
	}
	ans(v[0], v[1]);
}
int main() { int t; read(t); For(tt, 1, t) work(); return 0; }
```

---

