# [ABC254Ex] Multiply or Divide by 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc254/tasks/abc254_h

$ N $ 個の非負整数からなる多重集合 $ A=\{\ a_1,\ldots,a_N\ \},\ B=\{\ b_1,\ldots,b_N\ \} $ が与えられます。  
あなたは以下の操作を好きな順番で何度でも行えます。

- $ A $ に含まれている非負整数を $ 1 $ つ選び、$ x $ とする。 $ A $ から $ x $ を $ 1 $ つ削除し、代わりに $ 2x $ を $ 1 $ つ追加する。
- $ A $ に含まれている非負整数を $ 1 $ つ選び、$ x $ とする。 $ A $ から $ x $ を $ 1 $ つ削除し、代わりに $ \left\lfloor\ \frac{x}{2}\ \right\rfloor $ を $ 1 $ つ追加する。($ \lfloor\ x\ \rfloor $ は $ x $ を超えない最大の整数)

あなたの目的は $ A $ と $ B $ を(多重集合として)一致させることです。  
目的を達成することが出来るかどうかを判定し、出来る場合は必要な操作回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ a_1\ \leq\ \ldots\ \leq\ a_N\ \leq\ 10^9 $
- $ 0\ \leq\ b_1\ \leq\ \ldots\ \leq\ b_N\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

次のようにして $ 2 $ 回の操作で目的を達成できます。 - $ x=3 $ とし、$ A $ から $ x\,\ (=3) $ を $ 1 $ つ削除し代わりに $ 2x\,\ (=6) $ を $ 1 $ つ追加する。これによって $ A=\{4,5,6\} $ となる。 - $ x=5 $ とし、$ A $ から $ x\,\ (=5) $ を $ 1 $ つ削除し代わりに $ \left\lfloor\ \frac{x}{2}\ \right\rfloor\ \,\ (=2) $ を $ 1 $ つ追加する。これによって $ A=\{2,4,6\} $ となる。

### Sample Explanation 2

$ \{\ 0\ \} $ を $ \{\ 1\ \} $ にすることは出来ません。

## 样例 #1

### 输入

```
3
3 4 5
2 4 6```

### 输出

```
2```

## 样例 #2

### 输入

```
1
0
1```

### 输出

```
-1```

# 题解

## 作者：SDLTF_凌亭风 (赞：7)

下位紫题，赢！

首先，看着是两种操作，其实是一种操作。

看着是只对一个集合操作，其实可以看做对两个集合操作。

对 $A$ 集合进行 $a_i \leftarrow a_i \times 2$，等价于让 $B$ 集合中某一个元素执行 $b_i\leftarrow \lfloor \dfrac{b_i}{2} \rfloor$。

于是全部转为除法操作，直接降为对数级别。

一个可以想到的贪心思路是，每次拿出两个集合的最大值比较，谁大了就对谁做除法，如果两个一样大就把他们消掉。

但也要想到，$B$ 集合事实上是你不能动的。如果在一次比较中 $B$ 集合的最大值是个奇数，那你是无法通过上述操作来使得 $A,B$ 集合相等的，无解。

于是就可以快乐的拿 $O(n\log n)$ 的做法水一道紫题啦！

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int n, cnt = 0; cin >> n;
	priority_queue<int> A, B;
	for(int i = 1, t; i <= n; ++ i) cin >> t, A.push(t);
	for(int i = 1, t; i <= n; ++ i) cin >> t, B.push(t);
	while(A.size()) {
		auto u = A.top(), v = B.top(); A.pop(), B.pop();
		if(u > v) u >>= 1, A.push(u), B.push(v), ++ cnt;
		else if(u < v) (v & 1) ? (cout << -1, exit(0)) : (v >>= 1, A.push(u), B.push(v), ++ cnt, void(0));
	}
	cout << cnt;
}
```

---

## 作者：under_the_time (赞：5)

## 前言

某网校讲了这个题，并且发现还可以交题解，所以来写一发。

## 题意

给定两个大小均为 $n$ 的数组 $A$ 和 $B$，有两种操作： $x\leftarrow \lfloor\dfrac{x}{2}\rfloor$ 和 $x\leftarrow x\times 2$，求对 $A$ 进行这两种操作，使 $A$ 和 $B$ 数组中相同元素出现次数相同的最少操作次数，若无解则输出 $-1$。

## 解题思路

可以发现，对于将 $A$ 数组中的 $A_i$ 进行操作一，等价于将 $B$ 数组中的 $B_j$ 进行操作二，前提是 $B_j$ 为偶数。其中 $1\le i,j\le n$。

于是我们便可以把对于 $A$ 数组执行的操作一转化为对于 $B$ 数组的操作二。

所以我们使用贪心算法。考虑两个数组的最大值 $a$ 与 $b$ 的贪心策略：

- 若 $a=b$，则可以直接消去；
- 若 $a<b$，说明 $b$ 大于 $A$ 中的所有元素，则对 $b$ 执行操作二，因为对 $B$ 数组执行的操作二由操作一转化而来，一个整数乘以 $2$ 总是会变成偶数，**如果 $b$ 为奇数则无解**；
- 若 $a>b$，说明 $a$ 大于 $B$ 中的所有元素，则对 $a$ 执行操作二。

这个过程可以用优先队列进行维护。每个数至多只会操作 $\log V$ 遍，时间复杂度 $O(n\log n\log V)$，其中 $V$ 为 $A$ 和 $B$ 数组中的最大值。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n,ans; 
priority_queue<int> A,B; // 分别维护a与b数组的最大值
int main() {
    scanf("%d",&n);
    for (int i = 1,x;i <= n;i ++) {
        scanf("%d",&x);
        A.push(x);
    }
    for (int i = 1,x;i <= n;i ++) {
        scanf("%d",&x);
        B.push(x);
    }
    while (n > 0) {
        int a = A.top(), b = B.top();
        A.pop(); B.pop();
        if (a == b) { n --; continue; } // 情况一，可以消去一个元素
        ans ++; // 累计答案
        if (a < b) { // 情况二
            if (b & 1) { printf("-1"); return 0; } // 判断b为奇数时的无解
            A.push(a); B.push(b / 2); // 对b进行操作二
        }
        if (a > b) { // 情况三
            A.push(a / 2); // 对a进行操作二
            B.push(b);
        }
    }
    printf("%d",ans);
    return 0;
}
```

- 测评信息：[R126761219 记录详情](https://www.luogu.com.cn/record/126761219)

---

## 作者：Tsawke (赞：5)

# [[ABC254Ex] Multiply or Divide by 2](https://www.luogu.com.cn/problem/AT_abc254_h) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC254Ex)

## 题面

给定大小为 $ n $ 的集合 $ A $ 和 $ B $，你可以对集合 $ A $ 中的元素 $ a_i $ 进行两种操作，分别为 $ a_i \leftarrow \lfloor \dfrac{a_i}{2} \rfloor $，和 $ a_i \leftarrow a_i \times 2 $。你需要操作集合 $ A $ 直至集合 $ A, B $ 完全相同。求最小操作次数，若无解输出 `-1`。

## Solution

感觉这题的难度感觉完全不够 Ex，也完全不够紫，说这是 D 题我都信。。。

首先考虑转化两种操作，不难想到可以认为是在二进制中，前者即为右移一位，后者为左移一位。或者说前者是在二进制的末尾追加一个 $ 0 $，后者则是在二进制的末尾去掉一个数（可以为 $ 1 $ 也可以为 $ 0 $）。然后发现，这样的操作即缩小又放大没什么好性质，于是考虑转化。可以想到，对于将 $ A $ 集合中某个元素末尾追加一个 $ 0 $，可以转化为在 $ B $ 集合中某个元素末尾去掉一个 $ 0 $，同时注意这里去掉的只能为 $ 0 $.

综上我们题意转化为了，操作可以在 $ A $ 集合中去掉末尾一个属，也可以在 $ B $ 集合中去掉末尾一个 $ 0 $。于是想到维护两个优先队列，每次在两个集合中各取一个最大值，令其为 $ x, y $，若 $ x = y $，那么这两个数显然可以直接消除。若 $ x \gt y $，那么显然 $ x $ 会大于 $ y $ 中所有的数，而我们的操作又只能缩小一个数，不能增大，所以为了达到目标，一定需要对 $ x $ 进行一个缩小的操作，即 $ x \leftarrow \lfloor \dfrac{x}{2} \rfloor $，于是进行这个操作，$ ans \leftarrow ans + 1 $，然后把剩下的值丢回优先队列。若 $ x \lt y $，我们显然也要将 $ y $ 缩小，而此时我们还有个限制，对 $ B $ 集合的操作只能去掉 $ 0 $，所以如果这个值最后一位为 $ 1 $ 那么显然无解，反之进行对应操作即可。

思路明显且代码实现极为简单。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N;
ll ans(0);
priority_queue < int, vector < int >, less < int > > a, b;

int main(){
    N = read();
    for(int i = 1; i <= N; ++i)a.push(read());
    for(int i = 1; i <= N; ++i)b.push(read());
    while(!a.empty() && !b.empty()){
        int x = a.top(), y = b.top(); a.pop(), b.pop();
        if(x > y)a.push(x >> 1), b.push(y), ++ans;
        else if(x < y){
            if(y & 1)printf("-1\n"), exit(0);
            else a.push(x), b.push(y >> 1), ++ans;
        }
    }printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_06 初稿

---

## 作者：CoderMeow (赞：4)

# [ABC254Ex] Multiply or Divide by 2  题解

## 题意

给定集合 $A$ 和 $B$，一次操作为选定某个元素 $a_i$ 并进行 $a_i\leftarrow\lfloor\frac{a_i}{2}\rfloor$ 或 $a_i\leftarrow2a_i$。求让 $A=B$ 的最小操作次数。

## 转化

注意到原先的操作方式是不对称的，且两种操作有增有减，这里考虑将其中 $a_i\leftarrow2a_i$ 操作变为与其等价的 $b_i\leftarrow\frac{b_i}{2}$ 操作，注意这里不能有下取整即仅能对 $B$ 中的偶数进行操作，操作中的 $b_i$ 由 $a_i\times2$ 得到，必为偶数。同时，$a_i\leftarrow\lfloor\frac{a_i}{2}\rfloor$ 不应受限。

## 操作

既然已经统一了减小操作的定义，那么该如何进行操作呢？

在转化后的操作中只减不增，因此要考虑将两个集合中的大数缩小。具体操作如下：
每一次操作找出二集合分别的最大值 $a$ 和 $b$。于是有如下三种情况：

- $a=b$ 这两个数的匹配已经完成，从集合中删除；
- $a<b$ 易得 $a$ 为两个集合的最大值，又因为操作只能够减小，因此进行一次操作 $a_i\leftarrow\lfloor\frac{a_i}{2}\rfloor$；
- $a>b$ 同理需要 $b_i\leftarrow\frac{b_i}{2}$，又由于 $B$ 中操作的受限，若 $b$ 为奇数则其再无可能减小至与 $A$ 中任意元素相等，判定为无解。

## 实现

$A$ 与 $B$ 中始终要对当前最大值进行查询或修改后再取最大值，考虑优先队列实现。

代码如下。

```cpp
# include <cstdio>
# include <queue>
# include <vector>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    priority_queue<int> A, B;
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        A.push(a);
    }
    for (int i = 0; i < n; ++i) {
        int b;
        scanf("%d", &b);
        B.push(b);
    }

    int answer = 0;
    while (!A.empty()) {  // 操作直至两个集合被清空，也即所有元素相等
        if (A.top() < B.top()) {  // A 最大值小于 B 最大值
            if (B.top() % 2) {  // 若奇数，无解
                printf("-1");
                return 0;
            } else {  // 反之，对 b 进行 /2 操作
                int temp = B.top();
                B.pop();
                B.push(temp / 2);
            }
        } else if (A.top() > B.top()) {  // A 最大值大于 B 最大值，不受限制
            int temp = A.top();
            A.pop();
            A.push(temp / 2);
        } else {  // 二者最大值已经匹配，从集合中删除
            A.pop();
            B.pop();
            continue;  // 这一修改不是操作，不算在操作次数内
        }

        answer += 1;
    }

    printf("%d", answer);

    return 0;
}

```

---

## 作者：CleverRaccoon (赞：3)

## 前言

第一篇紫题题解。

## 题意

给定长度为 $n$ 的 $A$ 数组和 $B$ 数组，通过 $a_i\gets a_i\times2$ 和 $a_i\gets \lfloor\frac{a_i}{2}\rfloor$ 两种操作，求要使 $A=B$ 最少的操作次数，如果无法使 $A=B$，那么就输出 `-1`。

## 思路

要求最小的操作次数，那么可以使用优先队列来快速找到 $A$ 和 $B$ 的最大值（分别记为 $a$ 和 $b$）。

（优先队列使用 STL 中的 `priority_queue`。）

另外，发现 $a_i\gets a_i\times2$

有以下几种情况：

1. $a=b$：直接消去这两个元素即可。

2. $a<b$：$b\gets b\div 2$，这时有无解情况的判断：

除法可以向下取整，因此不存在该情况。但如果需要进行乘法时，会发现如果要达到的那个数是奇数，就是无解的情况。

3. $a>b$：$a\gets a\div 2$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100010],b[100010],ans;
priority_queue<int> qa,qb;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],qa.push(a[i]);
	for(int i=1;i<=n;i++)cin>>b[i],qb.push(b[i]);
	while(!qa.empty()){
		// 取最大值
     		int at=qa.top();
		qa.pop();
		int bt=qb.top();
		qb.pop();
		if(at==bt)continue;	// 消去
		if(at<bt){
			if(bt&1){	// 无解
				puts("-1");
				return 0;
			}
			qa.push(at);
			qb.push(bt>>1);
		}
		if(at>bt){
			qa.push(at>>1);
			qb.push(bt);
		}
		++ans;	// 记录答案
	}
	cout<<ans<<endl;
	return 0;
}

```

end.


---

## 作者：lemon2021 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc254_h)
## 前言
此题虽然是紫题，但只是个“纸老虎”，简易分析 $+$ 优先队列模拟，轻松水过！
## 题目大意
给定大小为 $n$ 的集合 $A$ 和 $B$，你可以对集合 $A$ 中的元素 $a_i$ 进行两种操作，分别为：$a_i=\lfloor\frac{a_i}{2}\rfloor$ 与  $a_i=a_i\times2$ 你需要操作集合 $A$ 直至集合，$A$，$B$ 完全相同。求最小操作次数，若无解则输出 $-1$。
## 样例解释
```
样例1：
3
3 4 5
2 4 6
```
解释：

$\lfloor\frac{5}{2}\rfloor=2\longrightarrow sum=1$

$4=4\longrightarrow$ 不用操作

$3\times2=6\longrightarrow sum=2$

```
样例2：
1
0
1
```
解释：

$0$ 无论如何操作也变不成 $1$，则无解，输出 $-1$。
## 思路
我们每次在两个集合未处理完成的数据中找到最大值 $maxa$ 和 $maxb$。若 $maxa=maxb$，则不用处理，直接跳过。若 $maxa<maxb$，我们可以把 $a_i\times2$ 转换成 $b_i\div2$，若 $b_i$ 不为 $2$ 的倍数，那么 $a_i$ 永远不能变成 $b_i$，则无解，输出 $-1$。若 $maxa>maxb$，就直接 $a_i\div2$。
## 方法
每次操作都要找集合最大值，```sort``` 和普通的找最大值的方法显然太慢，肯定要超时，所以我们考虑使用优先队列 ```priority_queue```，STL  大法好！
## AC 代码
```
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100001;
int n,sum;
int maxa,maxb;
int a[MAXN];
int b[MAXN];
priority_queue<int> Q_a;//STL大法好(默认大根堆) 
priority_queue<int> Q_b;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		Q_a.push(a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		cin >> b[i];
		Q_b.push(b[i]);
	}
	while( !Q_a.empty() || !Q_b.empty() )
	{
	  maxa = Q_a.top();
		maxb = Q_b.top();
		if(maxa == maxb)
		{
			Q_a.pop();
  		Q_b.pop();
			continue;//不用处理，直接跳过 
		}
		if(maxa < maxb)
		{
			if(maxb%2 == 1)//若b[i]不为2的倍数，那么a[i]永远不能变成b[i]，则无解 
			{
				cout<<"-1"<<endl;//无解则输出-1 
				return 0;
			}
			Q_a.pop();
			Q_a.push(maxa);
 		  Q_b.pop();
			Q_b.push(maxb/2);
		}
		if(maxa > maxb)
		{
			Q_a.pop();
			Q_a.push(maxa/2);
			Q_b.pop();
			Q_b.push(maxb);
		}
		sum++;
	}
	cout<<sum<<endl;
	return 0;
}
```



---

## 作者：Lyu_echo (赞：2)

## 题意

给定大小为 $n$ 的两个集合 $A,B$。

可以对集合 $n$ 中任意元素 $a_i$ 进行如下操作：

- $a_i \leftarrow \lfloor \frac{a_i}{2} \rfloor$
- $a_i \leftarrow a_i \times 2$

问使得 $A = B$ 的最小操作次数，或报告无解。

## 解题思路

考虑操作次数最小，我们不妨令 $a =\operatorname{max}_A, b= \operatorname{max}_B$。

讨论 $a,b$ 两数的情况。

- 若 $a > b$，则 $a$ 大于集合 $B$ 中所有元素，考虑操作 1。

- 若 $a < b$，则 $b$ 大于集合 $A$ 中所有元素，考虑操作 2。

- 若 $a=b$，消去两数。

讨论无解情况。

我们发现， 照上述，进行一次操作 2，等同于 $b \leftarrow \lfloor \frac{b_i}{2} \rfloor$，当且仅当 $b \in \{n \ |\ n = 2k \ |\ k \in \mathcal{Z}\  \}$ 。

否则，可以证明，操作无解。

## 代码实现

使用优先队列（堆）动态维护集合最大值。

```cpp
int solve() {
    std :: priority_queue<int> A,B;
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        A.push(a);
    }
    for (int i = 1; i <= n; i++) {
    	int b;
       	cin >> b;
        B.push(b);
    }

    while (!A.empty()) {
        int a = A.top();
        A.pop();
        int b = B.top();
        B.pop();

        if (a > b) { //情况1，a > b。
            a >>= 1; //考虑操作1
            A.push(a);
            B.push(b);
            ans++;
        }
        else if (a < b) { //情况2，a < b。
            if (b & 1) return -1; //判断无解情况
            b >>= 1; //考虑操作2
            A.push(a);
            B.push(b); 
            ans++;
        }
        else if (a == b) { //情况3，a = b。
            continue; //消除两数
        }
    }
    return ans;
}
```

总体时间复杂度 $n\operatorname{log} n$。

---

## 作者：Coffee_zzz (赞：1)

首先显然可以把 $a_i \leftarrow a_i \times 2$ 转化为当 $b_j$ 为偶数时 $b_j \leftarrow \dfrac {b_j} 2$。

考虑用大根堆维护集合 $A$ 和 $B$，设 $A$ 中最大的元素为 $x$，$B$ 中最大的元素为 $y$：

- 若 $x>y$，则目前没有数可以和 $x$ 匹配，需要对 $x$ 进行一次操作，使 $x\leftarrow \dfrac x 2$。
- 若 $x<y$：
  - 若 $y$ 为奇数，则必然没有数可以与 $y$ 匹配，无解；
  - 若 $y$ 为偶数，则目前没有数可以和 $y$ 匹配，需要对 $y$ 进行一次操作，使 $y\leftarrow \dfrac y 2$。
- 若 $x=y$，则将 $x$ 与 $y$ 匹配，同时删除 $x$ 和 $y$ 即可。

一直进行上面的操作直至发现无解或集合中所有元素被删除即可。

时间复杂度 $\mathcal O(n \log n \log V)$。

```cpp
#include <bits/stdc++.h>

#define ll long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;


void solve(){
	int n,x,y,ans=0;
	pq <int> a,b;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x,a.push(x);
	for(int i=1;i<=n;i++) cin>>y,b.push(y);
	while(a.size()){
		x=a.top(),y=b.top();
		if(x<y){
			if(y&1) cout<<-1<<endl,exit(0);
			else b.pop(),b.push(y/2),ans++;
		}
		else if(x>y) a.pop(),a.push(x/2),ans++;
		else a.pop(),b.pop();
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Limitless_lmw (赞：1)

### 题目大意

给定两个集合 $A,B$，每次操作可以使 $A$ 中的一个元素除以 $2$ 向下取整或乘 $2$，问最少要几次操作使 $A,B$ 中的元素完全一样，无解输出 `-1`。

### 解法

我们可以把操作巧妙地转化一下：把 $A_i \times 2$ 转化为 $B_j \div 2$，然后讨论以下情况：

设 $A_0=\max\limits_{i=1}^{n}\{a_i\},B_0=\max\limits_{i=1}^{n}\{b_i\}$

- $A_0=B_0$，那么我们消掉这两项。

- $A_0<B_0$，我们判断 $2|B_0$ 是否成立，成立将 $B_0\div2$，否则输出无解（次数 $+1$）。

- $A_0>B_0$，我们把 $A_0\div2$（向下取整）（次数 $+1$）。

最后输出总次数即可，时间复杂度 $O(n\log n)$。

### 一些问题

$Q1:$ 为什么当 $B_0>A_0$ 时，若 $2\nmid B_0$，则输出无解？

$A1:$ 因为 $B_0$ 比 $A_0$ 大，所以 $B_0$ 比任意一个 $A_i$ 都大，而它有需要由一个 $A_i \times 2$ 得到，一个数乘上 $2$ 一定是偶数，所以如果 $B_0$ 是奇数，那么显然无解。

$Q2:$ 那为什么当 $B_0<A_0$ 时，若 $2\nmid A_0$，是 $\div2$ 向下取整？

$A2:$ 首先，$B_0\div 2$ 实际上不是我们对 $B_0$ 操作，而是对一个 $A_i\times 2$ 操作的转化。所以 $\lfloor A_0\div 2\rfloor$ 与 $B_0 \div 2$ 是有本质区别的。

---

建议降蓝。

---

## 作者：S__X (赞：0)

打篇题解巩固一下。

## 题意
给你两个集合 $A$ 和 $B$，对于任意 $A$ 集合中的元素，我们可以进行  $2$ 种操作：$a_i\gets \left\lfloor\frac{a_i}{2}\right\rfloor$ 或 $a_i\gets 2\times a_i$。问最少要多少次才能使 $A$ 和 $B$ 中的元素相等。

## 分析
首先我们可以令 $a=\max_A$，$b=\max_B$。

- 若 $a=b$ 则可以消去 $2$ 数。之后继续寻找 $A$ 和 $B$ 中最大的元素。
- 若 $a<b$ 则说明 $b$ 大于 $A$ 中全部的元素。$a\gets 2\times a$ 等价于 $b\gets \frac{b}{2}$，当且仅当 $b$ 为 $2$ 的倍数。
- 若 $a>b$ 则说明 $a$ 大于 $B$ 中全部的元素。使 $a\gets \left\lfloor\frac{a}{2}\right\rfloor$。

最后输出操作次数即可。

### 注意

要使 $a_i\gets \left\lfloor\frac{a_i}{2}\right\rfloor$ 等于 $a_i\gets 2\times a_i$，就必须使 $a$ 为 $2$ 的倍数。如果不是，则无解 。

## 代码实现
这里用优先队列维护 $A$ 和 $B$ 的最大值。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ans;
priority_queue<int> A, B;//构建优先队列
int main() {
	cin>>n;
	//存储
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		A.push(a);
	}
	for (int i = 0; i < n; ++i) {
		int b;
		cin >> b;
		B.push(b);
	}
	while (!A.empty()) {
		if (A.top() < B.top()) {
			if (B.top() % 2) {//判断是否无解
				printf("-1");
				return 0;
			} else {
				int t = B.top();
				B.pop();
				B.push(t / 2);
			}
		} else if (A.top() > B.top()) {
			int temp = A.top();
			A.pop();
			A.push(temp / 2);
		} else {
			A.pop();
			B.pop();
			continue;
		}
		ans += 1;//计数
	}
	cout << ans << endl;
	return 0;
}


```

---

