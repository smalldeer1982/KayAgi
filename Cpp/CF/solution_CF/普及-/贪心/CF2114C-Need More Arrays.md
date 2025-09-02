# Need More Arrays

## 题目描述

给定一个数组 $ a $ 包含 $ n $ 个整数。数组按非递减顺序排序，即对于所有 $ 1 \le i < n $，满足 $ a_i \le a_{i + 1} $。

你可以从数组中移除任意数量的元素（包括不移除任何元素），且不移除的元素顺序保持不变。移除元素后，将按照以下规则生成新数组：

- $ a_1 $ 被写入一个新数组；
- 如果 $ a_1 + 1 < a_2 $，则 $ a_2 $ 被写入一个新数组；否则，$ a_2 $ 被写入与 $ a_1 $ 相同的数组；
- 如果 $ a_2 + 1 < a_3 $，则 $ a_3 $ 被写入一个新数组；否则，$ a_3 $ 被写入与 $ a_2 $ 相同的数组；
- $ \cdots $

例如，如果 $ a=[1, 2, 4, 6] $，则：

- $ a_1 = 1 $ 被写入一个新数组，生成数组：$ [1] $；
- $ a_1 + 1 = 2 $，因此 $ a_2 = 2 $ 被添加到现有数组，生成数组：$ [1, 2] $；
- $ a_2 + 1 = 3 $，因此 $ a_3 = 4 $ 被写入一个新数组，生成数组：$ [1, 2] $ 和 $ [4] $；
- $ a_3 + 1 = 5 $，因此 $ a_4 = 6 $ 被写入一个新数组，生成数组：$ [1, 2] $、$ [4] $ 和 $ [6] $。

你的任务是通过移除元素，使得上述算法生成的数组数量尽可能多。如果移除所有元素，则不会生成任何新数组。

## 说明/提示

在第一个例子中，你可以移除 $ a_3 $ 和 $ a_5 $，得到 $ a=[1, 2, 4, 6] $，生成数组的过程如题目描述所示。

在第二个例子中，你需要移除 $ a_2 $，得到 $ a = [1, 3] $，然后生成数组 $ [1] $ 和 $ [3] $。

在第三个例子中，不需要移除任何元素；对于 $ a = [1, 2, 2, 4] $，将生成数组 $ [1, 2, 2] $ 和 $ [4] $。

## 样例 #1

### 输入

```
6
6
1 2 3 4 5 6
3
1 2 3
4
1 2 2 4
1
2
3
1 4 8
2
1 1```

### 输出

```
3
2
2
1
3
1```

# 题解

## 作者：XsIeEiKcEk (赞：3)

### 解法

题目标签：**贪心**。

记录前值，然后依次遍历，直到找到一个数比前值 $+1$ 大，就代表会出现一个新的数组，中间那些都是没用的，再将前值更新为此值。直到遍历结束。

**注意**：上方算法要依据题目中一个条件：`数组按非递减顺序排序`。

### CODE：
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,a[200001];
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        int now=a[1],sum=1;//记录前值、数组数
        for(int i=2;i<=n;i++)
            if(a[i]>now+1)now=a[i],sum++;//更新
        cout<<sum<<'\n';
    }
    return 0;
}
```

---

## 作者：zxChicken4088 (赞：2)

# 题意概括：

有 $t$ 组样例，每个样例给定一个有 $n$ 个元素的数组 $a$，$a_i\le a_{i+1}(i\in\N\cap[1,n))$。

现在让你在 $a$ 删去若干个元素，设删去了 $x$ 个元素，使得有尽量多的 $a_i+1<a_{i+1}(i\in\N\cap[1,n-x))$。

# 题目分析：

根据 $a$ 的**不下降性**，可推断出使用**贪心**算法。

我们可以用一个变量记录新数组的第一个元素的值，叫做 $first$，初始设为 $a_1$。
遍历 $i=2\sim n$，如果 $first+1<a_i$，那么就会产生一个新数组，并将 $first$ 更新为 $a_i$。最后输出数组的个数即可。

该算法复杂度约为 $O(tn)$，能通过本题。
# 完整代码：

```cpp
#include <iostream>
//#include <iomanip>
//#include <algorithm>
//#include <cmath>
//#include <climits>
//#include <cctype>
//#define int long long
#define fup(c, st, ed, f) for (int (c) = (st); (c) <= (ed); (c) += (f))
#define fdn(c, st, ed, f) for (int (c) = (st); (c) >= (ed); (c) -= (f))
#define FASTIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//#define save(x) fixed << setprecision(x)
using namespace std;
using ll = long long;
const int MAXN = 2e5 + 5;
//个人习惯

int T, a[MAXN];

inline void work()
{
	int n; cin >> n;
	fup (i, 1, n, 1) cin >> a[i];
	int first = a[1], ans = 1;//注意 ans 初始为 1，因为 a[1] 一定会被写入一个新数组。
	fup (i, 2, n, 1)
	{
		if(first + 1 < a[i])
		{
			first = a[i];
			++ans;
		}
	}
	cout << ans << '\n';
}

signed main()
{
	for (cin >> T; T; T--) work();//处理多组样例 
	return 0;
}

```

[AC 记录](https://codeforces.com/contest/2114/submission/323344692)。

---

## 作者：c_legg (赞：1)

hehe，咕值掉了，来写题解。

## 题意

给定一个长为 $n$ 的数组 $a$，且当 $i\in\mathbb{Z}\cap[1,n-1]$ 时，$a_i\le a_{i+1}$，即数组有序。

现在要你删去 $a$ 中的若干个元素，再把 $a$ 分成若干段使得对于每个 $i,j\in\mathbb{Z}\cap[1,n-1]$，$a_i$ 和 $a_j$ 在两个不同的段里当且仅当 $a_i$ 和 $a_j$ 相差超过 $1$，问你最多可以分成多少段。

## 思路

先去重，可以证明相同元素对答案没有影响，去重后数组为 $b$。

然后考虑 DP，用数组 $\text{dp}_{i,j}$ 表示到 $i$ 为止最多分的段数，$j\in[0,1]$ 表示是否保留 $a_i$。

可以轻易地得到代码（状态转移）：

``` cpp
dp[i][1]=max(dp[i-1][0], b[i-1]==b[i]-1 ? max(dp[i-2][0], dp[i-2][1]) : dp[i-1][1])+1;
// 运用贪心做了一个判断
dp[i][0]=max(dp[i-1][0], dp[i-1][1]);
```

而边界为：

``` cpp
dp[1][0]=0, dp[1][1]=1;
```

## 代码

``` cpp
#include <bits/stdc++.h>
typedef long long ll;
#define one(x) ((ll)(1e##x))
using namespace std;
typedef pair<int, int> pii;

int t;

int n, m;

int a[300000], b[300000];

int dp[300000][2];

void slove() {
    cin>>n;
    fill(dp[0], dp[0]+201000, 0);
    fill(dp[1], dp[1]+201000, 0);
    m=0;
    int ans(-1);
    for(int i(1); i<=n; i++) cin>>a[i];
    for(int i(1); i<=n; i++) {
        if(a[i]!=b[m]) b[++m]=a[i];
    }
    dp[1][0]=0, dp[1][1]=1;
    for(int i(2); i<=m; i++) {
        dp[i][1]=max(dp[i-1][0], b[i-1]==b[i]-1 ? max(dp[i-2][0], dp[i-2][1]) : dp[i-1][1])+1;
        dp[i][0]=max(dp[i-1][0], dp[i-1][1]);
    }
    for(int i(1); i<=n; i++) {
        ans=max(ans, max(dp[i][1], dp[i][0]));
    }
    cout<<ans<<"\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    cin>>t;
    
    while(t--) slove();
    return 0;
}
```

---

## 作者：happy_lmn (赞：0)

### TOPIC:

通过选择性移除元素，将原递增数组分割成尽可能多的连续数字段（每个段内相邻元素差值 $≤1$），最终目标是最大化段的数量。

### SOLUTION:

一道经典贪心。目的是通过合理的选择性移除元素将原始递增数组分割成尽可能多的连续数字段，其中每个数字段需要满足段内相邻元素的差值不超过 $1$（即 $|a_{i+1}-a_i| ≤ 1$）。

考虑从数组的第一个元素开始，向后遍历数组，只要当前元素与前一个元素的差值不超过 $1$ 就继续扩展当前段，当遇到第一个不满足条件的元素时就结束当前段并开始新的段。确保了每个段尽可能包含最多的连续元素，从而为后续创建更多段留出空间，通过这种局部最优的选择最终能够得到全局最优解。

### CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i=0;i<n;i++) cin >> a[i];
        int res=1,i=0;
        while(i<n)
        {
            int j=i+1;
            while(j<n&&a[j]<=a[i]+1) j++;
            if(j<n) res++;
            i=j;
        }
        cout << res << endl;
    }
    return 0;
}
```

---

## 作者：Gaochenxi103_QWQ (赞：0)

删除给定的数组，使得 $a_i+1<a_{i+1}$ 尽可能多。
假定一个 $a_i$ 为操作后的 $a_1$。那么显而易见的，将它设为 $k$ 在后面满足 $a_i-k>1$ 的数量统计下来，每次找到一个，将新的 $k$ 赋值为它。

那么显然越往前的点做起始点所得到的结果一定大于其后面与它做差大于 $1$ 的点做起始点的结果，因为其后面与它做差大于 $1$ 的点统计在其的答案里面。

则只需求得以 $a_1$ 为起始点和 $a_1$ 后面值之比 $a_1$ 大 $1$ 大点的值求最大值即可。

核心代码。
```cpp
int f(int s)
{
    int now=a[s];
    int k=1;
    for(int i=s+1;i<=n;i++)
    {
        if(a[i]>now+1)
        {
            now=a[i];
            k++;
        }
    }
    return k;
}
……

int s=-1;
for(int i=1;i<=n;i++)
{
    cin>>a[i];
    if(a[i]==a[1]+1 && s!=-1)s=i;
}
if(s==-1) cout<<f(1)<<"\n";
else cout<<max(f(1),f(s))<<"\n";
```

---

## 作者：_Star_Universe_ (赞：0)

### 思路
~~看完其他题解后~~应该算一道比较简单的贪心题。

注意到题目说了**数组按非递减顺序排列**，因此我们可以直接进行遍历。因为对于每个 $i$ 只有在 $a_i+1<a_{i+1}$ 时才会产生产生一个新数组，所以如果 $a_i+1 \ge a_{i+1}$ 时就直接删除 $a_{i+1}$。

反之如果 $a_i+1<a_{i+1}$ 则需保留 $a_{i+1}$，这样会使得之后我们判断 $a_{i+1}+1<a_{i+2}$ 时，如果此条件满足了，对答案的贡献能再加 $1$。如果删除 $a_{i+1}$ 会使得这个 $1$ 的贡献被漏掉，显然不是最合理的删除方式。

upd：其实第一段讲的有些片面，应该是从一个值 $a_i$ 开始向后取，直到我们找到 $a_k>a_i+1$，这时留下中间的元素就没用了，直接将它们删掉即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int t,n,a[N];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        int sub=0,ans=1;
        for(int i=1;i<n;i++){
            if(a[i]>a[sub]+1){
                a[sub]=a[i];
                ans++;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
感谢 @[XsIeEiKcEk](https://www.luogu.com.cn/user/1617786) 和 @[wurang](https://www.luogu.com.cn/user/836786) 的题解对我创作本文的帮助，如有侵权请联系我删除文章。

---

## 作者：wurang (赞：0)

贪心小水题，由于 $a$ 数组不下降，所以如果 $a_i + 1 \geq a_{i+1}$，不会产生新数组，那么直接删除 $a_{i+1}$。

如果会产生贡献，显然应该保留，使其生成新数组。原因很简单，如果 $a_{i+1} + 1 \geq a_{i+2}$，保留 $a_{i+1}$，那么此时数组末尾是 $a_{i+1}$，产生了 $1$ 的贡献。如果不保留 $a_{i+1}$，就算 $a_{i} + 1 \leq a_{i+2}$，此时数组末尾是 $a_{i+2}$，只产生了 $1$ 的贡献，显然不优。

$pre$ 在此处表示数组末尾的数的下标

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int t, n, ans, pre;
int a[200005];

signed main()
{
    cin >> t;
    while(t--)
    {
        ans = 1, pre = 1; // 第一个直接选
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 2; i <= n; i++)
        {
            if(a[pre] + 1 < a[i])
            {
                pre = i;
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：TLE_qwq (赞：0)

### 解题思路
要使子数组数量最多，应尽可能让相邻保留元素的差大于 1。采用贪心策略：
- **排序数组**：确保数组有序。
- **遍历数组**：维护当前子数组的最后一个元素。
   - 如果当前元素与前一个元素的差大于 1，则新开子数组，计数增加，并更新最后一个元素。
   - 不然就跳过，继续检查后续元素。
### 解决代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int res = 0;
    int l = -2; 
    for (int i = 0; i < n; ) {
        if (i == 0) {
            res++;
            l = a[i];
            i++;
        } else {
            if (a[i] > l + 1) {
                res++;
                l = a[i];
                i++;
            } else {
                int j = i;
                while (j < n && a[j] <= l + 1) {
                    j++;
                }
                if (j < n) {
                    res++;
                    l = a[j];
                    i = j + 1;
                } else {
                    break;
                }
            }
        }
    }
    
    cout << res << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---

