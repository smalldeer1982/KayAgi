# [ABC236F] Spices

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc236/tasks/abc236_f

スパイス屋には、スパイス $ 1 $ 、スパイス $ 2 $、$ \ldots $ 、スパイス $ 2^N-1 $ の $ 2^N-1 $ 種類のスパイスがそれぞれ $ 1 $ 個ずつ売られています。 $ i\ =\ 1,\ 2,\ \ldots,\ 2^N-1 $ について、スパイス $ i $ の値段は $ c_i $ 円です。 高橋君はそれらを好きなだけ買うことができます。

高橋君は帰宅後、買ったスパイスのうち $ 1 $ つ以上を選び、それらを組み合わせてカレーを作る予定です。  
 高橋君がスパイス $ A_1 $ 、スパイス $ A_2 $ 、$ \ldots $、スパイス $ A_k $ の $ k $ 個のスパイスを組み合わせると、完成するカレーの辛さは $ A_1\ \oplus\ A_2\ \oplus\ \cdots\ \oplus\ A_k $ になります。 ここで、$ \oplus $ はビットごとの排他的論理和を表します。

高橋君は、作るカレーの辛さを帰宅後の気分で決めたいので、とりあえず $ 1 $ 以上 $ 2^N-1 $ 以下の任意の整数の辛さのカレーを作れるように、購入するスパイスの組み合わせを決定します。高橋君が支払う金額としてあり得る最小値を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 16 $
- $ 1\ \leq\ c_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

高橋君がスパイス $ 1 $ とスパイス $ 3 $ を買うと、下記の通り、$ 1 $ 以上 $ 3 $ 以下の任意の整数の辛さのカレーを作ることができます。 - 辛さ $ 1 $ のカレーを作るには、スパイス $ 1 $ のみを使い、 - 辛さ $ 2 $ のカレーを作るには、スパイス $ 1 $ とスパイス $ 3 $ を組み合わせ、 - 辛さ $ 3 $ のカレーを作るには、スパイス $ 3 $ のみを使えば良いです。 このとき高橋君が支払う金額は $ c_1\ +\ c_3\ =\ 4\ +\ 3\ =\ 7 $ 円であり、これが高橋君が支払う金額としてあり得る最小値です。

## 样例 #1

### 输入

```
2
4 5 3```

### 输出

```
7```

## 样例 #2

### 输入

```
4
9 7 9 7 10 4 3 9 4 8 10 5 6 3 8```

### 输出

```
15```

# 题解

## 作者：水星湖 (赞：6)

线性基模版题。

按照 $c$ 从小到大排序，每次尝试插入当前数字，如果可以插入答案加上这个数字的代价，否则考虑下一个代价更大的数字。

由下面两条线性基的性质易证上述做法是正确的。

1. 取线性基中若干个数异或起来可以得到原序列中的任何一个数。

2. 线性基内部的数个数唯一，且在保持性质一的前提下，数的个数是最少的。

根据性质 1，做法符合题意。根据性质 2，因为个数唯一，所以显然从小到大贪心是最优的。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 5;
int k, n, d[60];
pair<int, int> a[N];
bool ins(int x) {
    for(int i = 32; i >= 0; i--) {
        if(x & (1 << i)) {
            if(d[i]) x ^= d[i];
            else {
                d[i] = x;
                return 1;
            }
        }
    }
    return 0;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k; n = (1 << k) - 1;
    for (int i = 1; i <= n; i++)
        cin >> a[i].first, a[i].second = i;
    sort(a + 1, a + n + 1);
    int ans = 0;
    for(int i = 1; i <= n; i++) 
        if(ins(a[i].second)) 
            ans += a[i].first;
    cout << ans;
    return 0;
}
```

---

## 作者：harmis_yz (赞：4)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/0b5hlxos)。

## 分析

考虑将代价从小到大排序。因为我们要将 $[1,2^n-1]$ 这些数全部凑出来，而线性基刚好是维护这个的，所以直接用线性基板子。如果一个数 $x$ 成功插入，则将代价加上即可。

接下来给出最优性证明。根据线性基的性质，可知在能够凑出 $[1,2^n-1]$ 的情况下，所使用的数的数量是最少的。那么，如果有另一种方案 $S'$ 的代价小于当前方案 $S$ 的代价，对其进行分类讨论：

1. $|S|=|S'|$，由于我们是按照代价从小到大排序，所以数量相同的情况下，一定不存在 $S'$。
2. $|S|>|S'|$，不满足线性基性质。
3. $|S|<|S'|$，既然 $S'$ 选择的数量多且代价更小，那肯定在插入数的时候我们遗漏的一些数。因为 $S'$ 中一定存在下标 $i$，使得 $S'_i<S_i$。那么如果没有遗漏，代价为 $S'_i$ 的数我们应该先插入，不可能先插入了代价为 $S_i$ 的数。所以不满足插入流程。

所以该算法一定能够求解最小代价。时间复杂度 $O(2^nn)$。

## 代码

```cpp
il void solve(){
	n=(1ll<<rd)-1;
	for(re int i=1;i<=n;++i) a[i]={i,rd};
    sort(a+1,a+n+1);
    for(re int i=1;i<=n;++i)
    	if(d.Insert(a[i].x)) ans+=a[i].val;
	printf("%lld\n",ans);
	return ;
}
```

---

## 作者：WaterSun (赞：4)

# 思路

首先对所有的 $c$ 从小到大排序，然后对于每一个值如果之前能凑出就不选，否则就选。

这样做显然是对的。令 $p_1,p_2,\dots,p_{2^n-1}$ 表示将 $c$ 排序之后，对应原来的下标；$S$ 表示选出数的集合；$S'$ 表示最终选出数的集合。可以证明两个问题：

1. 如果 $p_i$ 可以被已选出数凑出，则不需要选 $p_i$。

2. 如果 $p_i$ 不可以被已选出的数凑出，则选 $p_i$ 最优。

---

对于第一个问题，我们总可以选出 $x_1,x_2,\dots,x_k \in S$，使得 $x_1 \oplus x_2 \oplus \dots \oplus x_k = p_i$。

如果 $p_i \in S'$，并且能选出 $p_i,y_1,y_2,\dots,y_q \in S'$，使得 $z = p_i \oplus y_1 \oplus y_2 \oplus \dots \oplus y_q$，那么一定有 $z = x_1 \oplus x_2 \oplus \dots \oplus x_k \oplus y_1 \oplus y_2 \oplus \dots \oplus y_q$。

所以选定 $p_i$ 不是最优的方式。

---

对于第二个问题，显然会存在 $p_i \not\in S'$，并且有 $x_1,x_2,\dots,x_k \in S'$，使得 $x_1 \oplus x_2 \oplus \dots \oplus x_k = p_i$，即 $x_1 = p_i \oplus x_2 \oplus \dots \oplus x_k$，即 $p_i \oplus x_2 \oplus \dots \oplus x_k = x_1$。又因为 $p_i$ 不能被凑出，所以 $x_1,x_2,\dots,x_k$ 中一定有一个元素不在 $S$ 中。

那么，对于所有的 $z \in [1,2^n)$ 都存在 $y_1,y_2,\dots,y_q \in S'$，使得 $y_1 \oplus y_2 \oplus \dots \oplus y_q = z$，这里假令 $x_1 = y_1$。那么有：

$$
z = x_1 \oplus y_2 \oplus y_3 \oplus \dots \oplus y_q = p_i \oplus x_2 \oplus \dots \oplus x_k \oplus y_2 \oplus y_3 \oplus \dots \oplus y_q
$$

所以即使 $S'$ 中没有 $x_1$，但加上 $p_i$ 依旧能使得条件成立。

又因为此时 $S$ 中没有 $x_1$，所以 $c_{p_i} \leq c_{x_1}$，因此选 $p_i$ 更优。

---

但是这个复杂度看似是 $\Theta(m^2)$ 的，其中 $m = 2^n$。但是其实是 $\Theta(nm)$ 的。

不难发现最多选出 $n$ 个数就能将 $[1,2^n)$ 中的所有数凑齐。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 1e5 + 10;
int n,m,ans;
bool vis[N];

struct point{
    int x,id;

    friend bool operator <(const point &a,const point &b){
        return a.x < b.x;
    }
}arr[N];

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

signed main(){
    n = read();
    m = (1ll << n) - 1;
    for (re int i = 1;i <= m;i++){
        arr[i].x = read();
        arr[i].id = i;
    }
    sort(arr + 1,arr + m + 1);
    for (re int i = 1;i <= m;i++){
        if (vis[arr[i].id]) continue;
        ans += arr[i].x;
        vis[arr[i].id] = true;
        for (re int j = 1;j <= m;j++) vis[j ^ arr[i].id] |= vis[j];
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：chengning0909 (赞：3)

# abc 236 f

## 题意

有 $2 ^ N - 1$ 个数字，分别编号为 $1, 2, \dots, 2 ^ N - 1$，想获得编号为 $i$ 的数字需要支付 $c_i$ 的代价。

现在你可以从这些数字中选出一些数，使得你可以通过某些数的编号的异或和来表示出 $[1, 2 ^ N - 1]$ 中的所有数。

请你求出最少需要支付多少代价。

## 思路

贪心。

首先，我们可以想到这样一种做法：

1. 因为想要让支付的代价最少，所以将所有的 $c_i$ 从小到大排序。

2. 如果当前的这个 $i$ 已经被标记过了，那么也就说明当前的 $i$ 可以被别的数凑出来，那么就直接跳过。否则，将 $i$ 和其他已经被标记过的元素取一次异或和所得到的值标记，并标记 $i$，累加和。

那么，时间复杂度是多少呢？

总共有 $2 ^ N - 1$ 个元素，每次枚举被标记过的元素最多需要 $2 ^ N - 1$ 次。

总时间复杂度为 $O(2 ^ {2 \times N})$，肯定会超时。

**但是，真的是这样的吗？**

### 时间复杂度分析

我们将排序后的序列 $c$ 对应的编号记作 $p_1, p_2, \dots, p_{2 ^ N - 1}$，当前选的元素的编号集合为 $S$。

当枚举到第 $i$ 个元素时，若当前通过 $S$ 凑出了 $a_1, a_2, \dots a_k$，并且 $p_i$ 不在 $a_1, a_2, \dots, a_k$ 中，那么如果在 $S$ 中加入 $p_i$，可以得到与 $a_1, a_2, \dots, a_k$ 均不同的 $p_i, p_i \oplus a_1, \dots, p_i \oplus a_k$。

假设 $p_i \oplus a_1$ 在 $a_1, a_2, \dots, a_k$ 中，存在 $x_1, x_2, \dots, x_m \in S$，$x_1 \oplus x_2 \oplus \dots \oplus x_m = p_i \oplus a_1$。

则 $x_1 \oplus x_2 \oplus \dots \oplus x_m \oplus a_1 = p_i \in \{a_1, a_2, \dots, a_k\}$，但是 $p_i \notin \{a_1, a_2, \dots, a_k\}$。

所以每一次往 $S$ 中添加一个元素，$S$ 中的元素数量会变成原来的两倍，而 $S$ 中最后只有 $2 ^ N - 1$ 个元素，也就意味着最多加入 $n$ 个元素。

而加入 $N$ 个元素肯定是可以凑出 $[1, 2 ^ N - 1]$ 的，我们可以直接选择 $1, 2, 4, 8, 16 \dots 2 ^ N - 1$。

那么，时间复杂度为 $O(N \times 2 ^ N)$。

### 贪心最优性证明

我们需要证明这样两个事情：

1. 若当前 $p_i$ 可以被凑出，不选 $p_i$。

2. 若当前不能凑出 $p_i$，选择 $p_i$ 是最优的。

------------

先证明第一点：

令最终选出的数所构成的集合为 $S'$，那么 $\forall z \in \{1, 2, \dots, 2 ^ N - 1\}$，都有 $x_1 \oplus x_2 \oplus \dots \oplus x_m = z(x_1, x_2, \dots, x_m \in S')$。

如果 $x_1, x_2, \dots, x_m$ 中有一个数为 $p_i$，我们不妨令这个数为 $x_1$。

那么 $z = p_i \oplus x_2 \oplus \dots \oplus x_m$。

因为 $p_i$ 可以被凑出，所以 $\exists y_1, y_2, \dots, y_k \in S$，且 $p_i = y_1 \oplus y_2 \oplus \dots \oplus y_k$，则 $z = y_1 \oplus \dots \oplus y_k \oplus x_2 \oplus \dots \oplus x_m$。

所以，可以证明，$z$ 不用 $p_i$ 凑出。

------------

接下来证明第二点：

令 $C(S)$ 表示 $\sum \limits _ {i \in S} c_i$。

假设 $p_i$ 不在 $S'$ 时（$p_i \notin S'$），$C(S')$ 是最优的。

则 $\forall x_1, x_2, \dots, x_m \in S'$，且 $p_i = x_1 \oplus x_2 \oplus \dots \oplus x_m$。

由于当前用 $S$ 中的元素凑不出 $p_i$，那么说明，$x_1, x_2, \dots, x_m$ 中至少有一个元素不属于 $S$，不妨假设这个元素为 $x_1$，也就是 $x_1 \notin S$。

$\forall z \in \{1, 2, \dots, 2 ^ N - 1\}$，$\exists y_1, \dots, y_k \in S'$，且 $z = y_1 \oplus y_2 \oplus \dots \oplus y_k$。

如果 $y_1, y_2, \dots, y_k$ 中有一个为 $x_1$，不妨设 $y_1 = x_1$。

也就是说 $z = x_1 \oplus y_2 \oplus \dots \oplus y_k = p_i \oplus x_2 \oplus \dots \oplus x_m \oplus y_2 \oplus \dots \oplus y_k$。

所以如果集合 $S'$ 中去掉 $x_1$ 并加上 $p_i$ 也是合法的。

因为 $x_1 \notin S$，所以 $C_{x_1} \ge C_{p_i}$，则 $C(S')$ 并不一定是最优的。

---

## 作者：Zheng_iii (赞：2)

今天 **2024 秋令营 Day1** 的 **贪心** 例题，来解释一下这道题贪心的思路。

首先输入一个整数 $n$，表示需要处理的数字数量为 $2^n - 1$，随后输入每个编号的代价，并将代价和编号存储在数组 $a$ 中。接着，对代价进行排序，以便在后续处理中优先选择代价较小的数字。然后，使用一个 $vis$ 数组来标记哪些编号已经被选择，对于每个未选择的编号，选择它并将其代价加入总代价中，同时通过异或操作更新 $vis$ 数组，以标记出可以由当前选择的编号生成的所有编号。最后，程序输出计算得到的最小代价。

**最后上一下代码。**
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn= 1e5+10;
int vis[maxn], n; // vis数组用于记录已选择的编号，n是输入的数字数量
ll ans; // 用于存储最终的最小代价
pair<int,int> a[maxn]; // 数组a存储每个数字的代价和对应的编号

int main() {
    scanf("%d", &n); // 输入n，表示2的n次方
    n = 1 << n; // 计算2^n的值
    for (int i = 1; i < n; i++) {
        scanf("%d", &a[i].first); // 输入代价，存入a数组的first部分
        a[i].second = i; // 将编号存入a数组的second部分
    }
    
    sort(a + 1, a + n); // 按照代价排序，从小到大
    vis[0] = 1; // 初始化vis数组，标记编号0已被选择

    for (int i = 1; i < n; i++) { // 遍历每个数字
        if (vis[a[i].second]) continue; // 如果该编号已被选择，跳过

        ans += a[i].first; // 将当前代价加到总代价中

        for (int j = 0; j < n; j++) { // 更新vis数组
            if (vis[j]) // 如果j编号已被选择
                vis[j ^ a[i].second] = 1; // 将j与当前编号的异或结果标记为已选择
        }
    }

    printf("%lld\n", ans); // 输出最终的最小代价
    return 0;
}
```

---

## 作者：Walter_Fang (赞：1)

贪心好题。题意不再赘述。

### 思路
将 $c$ 数组升序排序，并依次判断每个数 $x$。若 $x$ 可被已被取的数字异或得出，则不取 $x$，否则比取。

### 正确性证明
若 $x$ 可被已取的数异或得出，那么显然不用取。若不可被异或得出，则之后定存在取的 $y$ 使得组合出 $x$ 必要取 $y$，故取 $x$ 定不劣。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=(1<<16)+10;
ll t,n,i,j,ans,a[N],p[N],f[N];
int main(){
	cin>>t;n=(1<<t)-1;f[0]=1;
	for(i=1;i<=n;i++)cin>>a[i],p[i]=i;
	stable_sort(p+1,p+1+n,[](int x,int y){return a[x]<a[y];});
	for(i=1;i<=n;i++)
		if(!f[p[i]]){
			ans+=a[p[i]];
			for(j=0;j<=n;j++)f[j^p[i]]|=f[j];
		}
	cout<<ans;
}
```

---

## 作者：xuyiyang (赞：1)

### Solution
贪心。按 $c_i$ 从小到大排序，如果当前数 $p_i$ 能被之前的表示出，则不选，否则一定选。以下是证明。$\\$
令现在已选的数集合为 $S$。若一个数能被之前表示出来，那么显然一定不优。若不能表示 $p_i$，则一定要在后选出 $x_{1 \sim t}$ 使得 $x \cup S$ 可以表示出 $p_i$，而我们已经将代价由小到大排序，所以选择 $x$ 一定不如选 $p_i$。贪心正确性得证。$\\$
对于维护可以表示出数的集合 $A$，每次将 $A$ 中与 $p_i$ 异或的结果加入 $A$。于是加入一次是 $\mathcal O(2^n)$ 的。以下证明最多加入 $n$ 个数即可表示完 $1 \sim 2^n-1$。$\\$
首先，对于 $A$ 中一个数 $q$，则 $p_i \operatorname{xor} q \not \in A$。考虑反证，若在 $A$ 中，由于异或运算的性质，$p_i$ 可以被 $S$ 表示出，矛盾。所以每次 $A$ 集合元素数量翻倍，即最多加入 $n$ 个数。$\\$
综上，我们以 $\mathcal O(n2^n)$ 解决了该问题。

```cpp
void mian() {
	scanf("%d", &n);
	for (int i = 1; i < 1 << n; i ++ ) scanf("%d", &c[i]), p[i] = i;
	sort(p + 1, p + (1 << n), [](int x, int y) { return c[x] < c[y]; });
	buc[0] = 1; LL res = 0;
	for (int i = 1; i < 1 << n; i ++ ) {
		if (!buc[p[i]]) {
			res += c[p[i]];
			for (int j = 0; j < 1 << n; j ++ ) buc[j ^ p[i]] |= buc[j];
		}
	} printf("%lld\n", res); return void();
}
```

---

