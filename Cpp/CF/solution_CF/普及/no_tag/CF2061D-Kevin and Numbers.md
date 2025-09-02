# Kevin and Numbers

## 题目描述

Kevin 在黑板上写了一个长度为 $ n $ 的整数序列 $ a $。

Kevin 可以执行任意次数的以下操作：

- 选择黑板上两个满足 $ |x - y| \leq 1 $ 的整数 $ x, y $，将它们删除，并写入一个新整数 $ x + y $。

Kevin 想知道是否可以通过一系列操作将这些整数转换为长度为 $ m $ 的整数序列 $ b $。

两个序列 $ a $ 和 $ b $ 被认为是相同的，当且仅当它们的多重集完全相同。即对于任意数 $ x $，其在 $ a $ 中出现的次数必须等于在 $ b $ 中出现的次数。

## 说明/提示

第一个测试用例中，可以删除 $ 4 $ 和 $ 5 $，并写入 $ 9 $。

第二个测试用例中，无法删除 $ 3 $ 和 $ 6 $。

第三个测试用例中，一种可能的操作路径为：

1. 删除 $ 2 $ 和 $ 2 $，并写入 $ 4 $。此时剩余数字为 $ 1, 2, 4 $。
2. 删除 $ 1 $ 和 $ 2 $，并写入 $ 3 $。此时剩余数字为 $ 3, 4 $。

第四个测试用例中，一种可能的操作路径为：

1. 删除 $ 1 $ 和 $ 1 $，并写入 $ 2 $。此时剩余数字为 $ 2, 3, 3 $。
2. 删除 $ 2 $ 和 $ 3 $，并写入 $ 5 $。此时剩余数字为 $ 3, 5 $。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
2 1
4 5
9
2 1
3 6
9
4 2
1 2 2 2
3 4
4 2
1 1 3 3
3 5
4 2
1 2 3 4
3 5
5 5
1 2 3 4 5
5 4 3 2 1
4 2
1 1 1 1
1 1
4 4
1 1 1 1
1 1 1 2
1 1
1
1000000000```

### 输出

```
Yes
No
Yes
Yes
No
Yes
No
No
No```

# 题解

## 作者：_anll_ (赞：2)

## 思路
如果你的思路是用优先队列维护，即将最小和次小加在一起后再丢进去反复处理的话，可以试试下面这个样例：
```
1
4 2
1 1 2 2
3 3
```

言归正传。$ | x-y | \le 1$ 看起来就很怪，我们从这入手，不难发现如果最后需要构成的数是 $a$，它一定是由两个相邻或相等的数相加得来的。令这两个数中最小的那个数为 $b$，那 $a=b+b$ 或 $a=b+b+1$。整理一下即可从 $a$ 求出 $b$，即 $b=\lfloor \dfrac{a}{2}\rfloor$。那直接拿 map 去存 $A$ 数组里的值，然后用递归去暴力判断即可。

## 代码
赛时代码比较丑提前致歉。
```cpp
#include<map>
#include<queue>
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,t,num[N];
map<int,int> mo;
bool work(int x){
	if(mo[x]) return mo[x]--,1;
	if(!x) return 0;
	if(x%2==0) return work(x/2)&&work(x/2);
	return work(x/2)&&work(x/2+1);
}
void solve(){
	cin>>n>>m;int x,s=0;bool st=1;mo.clear();
	for(int i=1;i<=n;i++){
		cin>>num[i];s+=num[i];
		mo[num[i]]++;
	}
	for(int i=1;i<=m;i++){
		cin>>x;s-=x;
		st&=work(x);
	}
	cout<<(st&&s==0?"yes":"no")<<endl;
}
signed main(){
	ios::sync_with_stdio(false); 
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：2)

[CF2061D](https://www.luogu.com.cn/problem/CF2061D)

## Statement

给定两个可重集 $a,b$，每次可以选择 $x,y$ 的下标且 $\left|{a_x - a_y}\right| \leq 1$，将这两个数合并成 $a_x + a_y$，求 $a$ 是否可变化成 $b$。

## Solution

$a,b$ 集合的和不同，一定无解。

操作可以转换成选择相同或相差 $1$ 的两个数，将其修改成它们的和，即两个数转化成一个数。

对于 $a$ 中的最大值 $a_{posa}$ 和 $b$ 中的最大值 $b_{posb}$：

- 如果说 $a_{posa} > b_{posb}$，无解。

- 如果说 $a_{posa} = b_{posb}$，没有影响。

- 如果说 $a_{posa} < b_{posb}$，则 $b_{posb}$ 一定是 $\lfloor{\frac{a_{posa}}{2}}\rfloor + \lceil{\frac{a_{posa}}{2}}\rceil$ 合成的。

用 multiset 维护这样的操作即可。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MAXN = 2e5 + 10;
int T, n, m, A[MAXN], B[MAXN], Sum;
multiset <int> sA, sB;
vector <string> Vec;

signed main() {
    cin.tie (0) -> sync_with_stdio (0);
    cout.tie (0) -> sync_with_stdio (0);
    cin >> T;
    while (T --) {
        cin >> n >> m;
        sA.clear(), sB.clear(), Sum = 0;
        for (int i = 1; i <= n; i ++)
            cin >> A[i], Sum += A[i];
        for (int i = 1; i <= m; i ++)
            cin >> B[i], Sum -= B[i];
        if (Sum) {
            Vec.push_back ("No");
            continue;
        }
        for (int i = 1; i <= n; i ++) sA.insert (A[i]);
        for (int i = 1; i <= m; i ++) sB.insert (B[i]);
        bool flag = true;
        while (!sA.empty() || !sB.empty()) {
            int xVal = *sA.rbegin(), yVal = *sB.rbegin();
            if (xVal == yVal) {
                auto itx = sA.find (xVal), ity = sB.find (yVal);
                sA.erase (itx), sB.erase (ity);
            }
            if (xVal < yVal) {
                auto ity = sB.find (yVal);
                sB.erase (ity);
                sB.insert (yVal >> 1), sB.insert ((yVal + 1) >> 1);
            }
            if (xVal > yVal) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            Vec.push_back ("No");
            continue;
        }
        if (sA.empty() && sB.empty())
            Vec.push_back ("Yes");
        else
            Vec.push_back ("No");
    }
    for (string Ans : Vec)
        cout << Ans << "\n";
    return 0;
}
```

---

## 作者：postpone (赞：2)

要把 $a$ 变成 $b$，其实是一个不断找数的过程，找 $a$ 中是否直接有，或者能通过题目中的变换获得，关键在于这个“找”要怎么实现。

我赛时的实现比较抽象，用 $\texttt{std::map}$ 存 $a$ 数组，然后写了个递归查找：对于要找的数 $x$，如果 $a$ 中直接有现成的，就返回真；如果 $a$ 已经空了，或者 $a$ 中最小的数都比 $x$ 大，那肯定没办法找到了，返回假；其余情况，就继续递归下去。

就该方法而言，完全可以用 $\texttt{std::multiset}$ 代替 $\texttt{std::map}$，代码如下。

```cpp
void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> b(m);
    multiset<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.insert(x);
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    auto Find = [&](auto &&self, int x) -> bool {
        if (a.contains(x)) {
            a.extract(x);
            return true;
        } else if (a.empty() or *a.begin() > x) {
            return false;
        }
        if (x % 2 == 0) {
            return self(self, x / 2) and self(self, x / 2);
        } else {
            return self(self, x / 2) and self(self, x / 2 + 1);
        }
    };

    bool ok = true;
    for (auto x : b) {
        ok &= Find(Find, x);
    }
    ok &= a.empty();
    cout << (ok ? "Yes" : "No") << "\n";
}
```

其实有更好的思路，无法直接找到时，不用递归下去继续找 $a$ 中的数，而是在 $b$ 中加入新的数，这样就不用递归了。具体可以参考[哥哥的代码](https://codeforces.com/contest/2061/submission/302057147)。

---

## 作者：yvbf (赞：1)

![](bilibili:BV1MuwverEdQ?t=1070)

---

## 作者：xhxxwcr (赞：0)

### 题意

有合并这个操作，当且仅当两数之差小于 $1$ 时可以合并，问能否通过此操作将数组 $a$ 转化成数组 $b$。

### 解法

很明显，这道题只有合并和拆分两种解法，由于答案数组不一定有序，所以我们可以用优先队列维护操作。

那现在就可以考虑合并和拆分两种方法：

1. 合并：这是题目中的方法，也是我一开始想到的方法，通过小根堆维护最小值和次小值，当最小值与答案序列最小值相同时同时取出队列，否则合并最小和次小值加入队列。

   但是这样做有一个问题，本来 $x$ 和 $x + 1$ 存在， 可以合成在数组 $b$ 中的 $y$，但是由于 $x + 1$不为最小值，数组 $b$ 中也不存在 $2x$，就会导致答案错误。如果要处理这个问题，需要 $dp$ 分类讨论，较麻烦，于是考虑拆分。

2. 拆分：这是题目方法的逆运用，将 $b$ 数组的数拆分，直到拆出 $a$ 中的元素。

   这个方法解决合并不唯一的问题，由于一个元素要么为奇数要么为偶数，为了拆出两数之差小于 $1$ 的组合，当奇数时只存在 $x$ 与 $x + 1$，偶数时只存在 $x$ 和 $x$。方案唯一，就不存在问题。

代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
priority_queue <int> q;
priority_queue <int> p;
signed main(){
	int t;
	cin >> t;
	while(t--){
		while(!q.empty()) q.pop();
        while(!p.empty()) p.pop();
		int n,m;
		cin >> n >> m;
		while(n--) {int x;cin >> x;p.push(x);}
        while(m--) {int x;cin >> x;q.push(x);}
        while(!q.empty() && !p.empty()){
            while(p.top() == q.top() && !q.empty() && !p.empty()){
                q.pop();
                p.pop();
            }
            if(!(!q.empty() && !p.empty())) break;
            if(q.top() < p.top() || q.size() >= p.size()) break;
            int x = q.top(),a,b;
            a = x / 2,b = x - a;
            q.pop();
            q.push(a);
            q.push(b);
        }
        if(q.empty() && p.empty()) cout << "Yes\n";
        else cout << "No\n";
	}
}
```

---

## 作者：UniGravity (赞：0)

### Solution CF2061D Kevin and Numbers

妙妙题。

第一眼看这个似乎不太好做，因为每次选择合并哪两个会对后面产生影响。

但是我们发现 $|x-y|=1$ 有一个特殊的性质，就是确定了合并后的 $x+y$ 就能倒退出唯一的 $x,y$。

利用这个性质，考虑倒着变成每次选择 $b$ 中一个数分裂成两个。

大力 STL 维护，每次找 $b$ 中最大的数，如果其出现数量比 $a$ 中的出现数量小无解，因为已经是最大的数了。遇到多余的 $1$ 无法分解和匹配时也是无解。

时间复杂度 $O(n\log n)$。

---

## 作者：Kendieer (赞：0)

原题：[**\[CodeForces\]**](https://codeforces.com/contest/2061/problem/D)、[**\[洛谷\]**](/problem/CF2061D)。

---

## 思路构筑

如果这题按照题意模拟，由于只要存在 $|x-y| \le 1$ 就可以合并，会发现有很多种分支情况，这不利于我们去解题。

不妨我们逆向思维一下，将结果数组 $b$ 中的元素拆分出来。拆分后按照需求取走 $a$ 数组中相应的元素即可。

代码实现上，我们将 $a$ 中的所有元素数量维护起来，然后用大根堆维护 $b$ 中的元素，如果堆顶元素 $x$ 在 $a$ 中不存在则拆分成 $\lfloor \frac{x}{2}\rfloor$ 和 $x-\lfloor \frac{x}{2}\rfloor$，继续放入堆。

这里需要剪一下枝，不然容易卡常，若当前堆大小大于 $a$ 剩余数字的数量，则直接输出 `No` 即可。（自己思考一下为什么）

## Code

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i,a,b) for(ll i = (a);i < (b);i++)
#define repr(i,a,b) for(ll i = (b) - 1;i>= (a);i--)
#define elif else if
#define Code_by_Kendieer return 0
typedef long long ll;
typedef unsigned long long ull;
const ll inf = 0x3f7f7f7f7f7f7f7f;

ll qread();
char readChar();
void qwrite(ll x,int t = 10);

const int maxn = 2e5 + 7;
const int mod = 998244353;
struct Node {};
map<ll,int> cnt;
priority_queue<ll,vector<ll>> pq;

void solve(){
    cnt.clear();
    pq = priority_queue<ll>();
    int n = qread(),m = qread();
    int rst = n;
    rep(i,0,n) cnt[qread()]++;
    rep(i,0,m) pq.push(qread());
    while(pq.size()){
        ll loc = pq.top();
        pq.pop();
        if (cnt[loc]) cnt[loc]--,rst--;
        else {
            if (loc > 1){
                pq.push(loc/2);
                pq.push(loc - loc/2);
            } else {
                cout << "No" << endl;
                return;
            }
        }
        if (pq.size() > rst){
            cout << "No" << endl;
            return;
        }
    }
    if (rst) cout << "No" << endl;
    else cout << "Yes" << endl;
}

int main(){
    // cin.tie(0),cout.tie(0);
    // ios::sync_with_stdio(0);
    int n = 1;
    n = qread();
    while(n--) solve();
    Code_by_Kendieer;
}

// =====================================================
ll qread(){
    ll r = 0,s = 1,ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    if (ch == '-') ch = getchar(),s = -1;
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0',ch = getchar();
    return r * s;
}
char readChar(){
    int ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    return ch;
}
void qwrite(ll x,int t){
    if (x<0) putchar('-'),x=-x;
    if (x>=t) qwrite(x/t,t);
    putchar(x%t<10?'0'+x%t:'A'-10+x%t);
}
// =====================================================
```

---

