# [EGOI 2025] Gift Boxes / 礼品盒

## 题目描述

今年的 EGOI 在波恩举办。主办方希望为比赛中的每支队伍最多分发一个礼品盒，每支队伍的编号为 $0$ 到 $T-1$。所有参赛选手排成一排，但他们的顺序是混乱的，因此同一队的成员可能不会站在一起。注意，队伍中一定至少有一支队伍在队列中有多于一名成员。队列中共有 $N$ 个人，第 $i$ 个人属于编号为 $a_i$ 的队伍。问题是：每支队伍最多只能获得一个礼品盒。为了让礼品发放过程顺利进行——即使因此有些队伍无法获得礼品盒——主办方希望在发放过程中**恰好暂停一次**，跳过一段连续的选手，然后再继续发放。换句话说，他们会跳过一个连续区间 $[\ell, r]$ 的选手。

并不要求每支队伍都必须收到礼品盒。然而，主办方希望在不违反“每支队伍至多一个礼品盒”这一前提下，使收到礼品盒的队伍数尽量多，同时要**最小化被跳过的选手数量**。请帮助主办方决定在哪一段暂停以及何时继续发放礼品盒，才能使被跳过的选手尽可能少。

## 说明/提示

第一个样例满足测试组 1、3、5 和 6 的约束。有两种不同的输出：$1\ 1$（对应下划线蓝色线段）和 $4\ 4$（对应红色虚线），如图所示。无论哪种方式，四支队伍都能收到礼品盒，且没有队伍收到多于一个礼品盒。

$\begin{array}{lllll} 1 & \blue 3 & 0 & 2 & \red 3 \end{array}$

第二个样例满足测试组 2、3、4、5 和 6 的约束。同样有两种不同的输出：$0\ 2$ 和 $3\ 5$，如图所示。两种方案下，三支队伍都能收到礼品盒。

$\begin{array}{lllll} \blue 1 & \blue 0 & \blue 2 & \red 2 & \red 1 & \red 0 \end{array}$

第三个样例满足测试组 3、4、5、6 的约束。最优解是三支队伍收到礼品盒，如下所示。下标为 0、1、7 的选手（分别属于队伍 0、2、3）收到礼品盒。这是唯一的可行解。

$\begin{array}{lllllll} 0 & 2 & \blue 0 & \blue 1 & \blue 2 & \blue 1 & \blue 3 & 3 \end{array}$

第四个样例满足测试组 3、5 和 6 的约束。同样有两种不同的输出：$0\ 3$ 和 $1\ 4$，如图所示。两种方案下，恰好两支队伍（队伍 0 和队伍 1）获得礼品盒。队伍 2 没有获得礼品盒，因为这样会导致队伍 0 或 1 获得两个礼品盒，这是严格禁止的。

$\begin{array}{lllllll} \blue 1 & \blue 1 & \blue 2 & \blue 0 & 1 &  0 \end{array}$

$\begin{array}{lllllll}  1 & \red 1 & \red 2 & \red 0 & \red 1 &  0 \end{array}$

第五个样例满足测试组 3、5 和 6 的约束。唯一可行答案是 $2\ 3$，如图所示。所有四支队伍都能收到礼品盒。

$\begin{array}{lllllll} 0 & 1 & \blue 2 & \blue 0 & 3 & 2 \end{array}$

第六个样例满足测试组 3、5 和 6 的约束。最多有五支队伍中的四支能收到礼品盒，如下所示。下标为 0、10、11 和 12 的选手（分别属于队伍 3、4、1、0）收到礼品盒。这是唯一的可行解。

$\begin{array}{lllllll} 3 & \blue 3 & \blue 3 & \blue 1 & \blue 2 & \blue 0 & \blue 3 & \blue 3 & \blue 2 & \blue 1 & 4 & 1 & 0 \end{array}$

### 约束与评分

* $1 \leq T < N \leq 500\,000$
* $0 \leq a_i \leq T-1$

你的解答将在一组测试组上进行评测，每组有若干测试用例。要获得该测试组的分数，你需要通过该测试组的所有测试用例。

| 测试组 | 分值 | 限制条件 |
| :-: | :-: | :-: |
| 1 | 8 | $N = T + 1$，即只有一支队伍会出现两次 |
| 2 | 11 | $N = 2 \cdot T$，且每支队伍在前半部分和后半部分各出现一次 |
| 3 | 14 | $1 \leq T < N \leq 500$ |
| 4 | 21 | $N = 2 \cdot T$，且每支队伍均出现两次 |
| 5 | 22 | $1 \leq T < N \leq 5\,000$ |
| 6 | 24 | 无额外限制 |

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4 5
1 3 0 2 3```

### 输出

```
1 1```

## 样例 #2

### 输入

```
3 6
1 0 2 2 1 0```

### 输出

```
0 2```

## 样例 #3

### 输入

```
4 8
0 2 0 1 2 1 3 3```

### 输出

```
2 6```

## 样例 #4

### 输入

```
3 6
1 1 2 0 1 0```

### 输出

```
0 3```

## 样例 #5

### 输入

```
4 6
0 1 2 0 3 2```

### 输出

```
2 3```

## 样例 #6

### 输入

```
5 13
3 3 3 1 2 0 3 3 2 1 4 1 0```

### 输出

```
1 9```

# 题解

## 作者：rui_er (赞：5)

注意到：若一支队伍的人数大于等于 $3$，则除第一个人与最后一个人以外，其他人必定会被跳过。这是因为只能跳过一段区间，如果一个中间位置的人没被跳过，那么要么她前面的所有人都没有被跳过，要么她后面的所有人都没有被跳过，这样的话必定有与她同队的人也获得奖品，这个队伍就获得至少两个奖品了。

对于区间 $I_1=[l_1,r_1],I_2=[l_2,r_2]$，我们定义：

$$
\operatorname{merge}(I_1,I_2)=[\min\{l_1,l_2\},\max\{r_1,r_2\}]
$$

即为删掉 $I_1,I_2$ 所有元素所需的最短区间。

根据上面的结论，每个至少 $3$ 个人的队伍都有一段必须要删除的区间，将它们 $\operatorname{merge}$ 起来就得到了整体中必须要删除的区间 $[ql,qr]$。

把 $[ql,qr]$ 的人都删除，剩余序列中每个队伍的人数都不超过 $2$。考虑对每个位置 $l$，求出最小的 $r$，使得删除 $[l,r]$ 之后每个队伍的人数都不超过 $1$，可以双指针维护。对于求出的每个 $[l,r]$，实际需要删除的区间为 $\operatorname{merge}([ql,qr],[l,r])$，在所有这些区间中取最短的即为答案。

时间复杂度 $O(n)$。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(y < x) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 5e5 + 5;

int t, n, a[N], cnt[N], rem[N];
vector<int> vec[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> t >> n;
    rep(i, 0, n - 1) cin >> a[i];
    rep(i, 0, n - 1) vec[a[i]].push_back(i);
    int ql = n, qr = -1;
    rep(i, 0, t - 1) {
        int tot = vec[i].size();
        if(tot > 2) {
            int ul = vec[i][1], ur = vec[i][tot - 2];
            chkmin(ql, ul);
            chkmax(qr, ur);
        }
    }
    rep(i, ql, qr) a[i] = -1;
    rep(i, 0, n - 1) if(a[i] != -1) ++cnt[a[i]];
    int l = 0, r = -1, now = 0, ansl = -1, ansr = n;
    rep(i, 0, t - 1) if((rem[i] = cnt[i]) <= 1) ++now;
    while(l < n) {
        while(r + 1 < n && now < t) {
            ++r;
            if(a[r] != -1 && rem[a[r]]-- == 2) ++now;
        }
        if(now < t) break;
        int ul = min(l, ql), ur = max(r, qr);
        if(ur - ul + 1 < ansr - ansl + 1) {
            ansl = ul;
            ansr = ur;
        }
        if(a[l] != -1 && ++rem[a[l]] == 2) --now;
        ++l;
    }
    cout << ansl << " " << ansr << endl;
    return 0;
}
```

---

## 作者：ljy_luogu (赞：2)

显然最靠左或最靠右的第一个出现两次的数肯定会被删掉，记为 $s$ 和 $e$，那么 $s$ 到 $e$ 就都会被删掉，接下来就是处理两边没被删掉但出现两次的数。

考虑双指针，让左指针指向最左端，右指针指向 $e$，表示删除左右指针中间的数，如果左指针右移多出来的数出现了两次，就右移右指针直到这个数被删除，如果右指针右侧没有这个数了，就停止移动并输出答案，在这个过程中记录左右指针距离的最小值和最小值时左右指针的位置即可。

双指针反着跑即让左指针指向 $s$，右指针指向最右端，并不断左移也可以，细节和正着跑一样。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,s,e,l,r,ansl,ansr,len=INT_MAX;
int cnt1[500010],cnt2[500010],cnt[500010],a[500010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cnt1[a[i]]++;
        if(cnt1[a[i]]==2){
            s=i;
            cnt1[a[i]]--;
            break;
        }
    }
    for(int i=n;i>=1;i--){
        cnt2[a[i]]++;
        if(cnt2[a[i]]==2){
            e=i;
            cnt2[a[i]]--;
            break;
        }
    }
    l=1,r=e;
    while(l<=s){
        if(r-l+1<len){
            len=r-l+1;
            ansl=l;
            ansr=r;
        }
        while(cnt2[a[l]]==1&&r<=n){
            r++;
            cnt2[a[r]]--;
        }
        if(r>n){
            break;
        }
        cnt2[a[l]]++;
        l++;
    }
    //正着跑
    /*l=s,r=n;
    while(e<=r){
        if(r-l+1<len){
            len=r-l+1;
            ansl=l;
            ansr=r;
        }
        while(cnt1[a[r]]==1&&l>=1){
            l--;
            cnt1[a[l]]--;
        }
        if(l<1){
            break;
        }
        cnt1[a[r]]++;
        r--;
    }*/
    //反着跑
    cout<<ansl-1<<' '<<ansr-1;

    return 0;
}

```

---

## 作者：chen_zhe (赞：2)

这是 [官方题解](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/l70s4gf8) 的 AI 翻译。

---

### EGOI 2025 官方题解 - Giftboxes (礼品盒)

**任务作者：Anja Dožić**

**2025 年 7 月 16 日**

#### 问题描述

组织者正在向选手们分发礼品盒，并希望每个队伍都能收到一个。现在有 $T$ 个队伍和 $N$ 名选手在排队领取礼物。问题在于，队伍中的女孩们在队列中是混合排列的，所以来自同一队伍的女孩可能不会站在一起，而且队列中可能有多名来自同一队伍的女孩。组织者必须暂停一次分发流程，让一些女孩不领取礼品盒直接通过。我们的目标是最大化收到礼品盒的队伍数量，同时要避免将超过一个礼品盒发给同一个队伍（对于每个队伍，我们最多只能给其中一名选手发放礼品盒，其他选手则必须跳过）。

#### 子任务 1: $N = T + 1$

在这个子任务中，只有一个队伍有两名成员在队列中，其余所有队伍都恰好只有一名成员。

此时，我们有可能让每个队伍都得到礼物。要做到这一点，我们只需让那个出现两次的队伍中的一名队员通过即可。这是因为，当我们从数组中移除那一名队员后，剩下的数组中将包含所有不同的元素（因为所有其他队员都来自不同的队伍）。

为了找到那个出现两次的队伍，我们可以遍历给定的数组，并在每个元素首次出现时对其进行标记。这可以通过维护一个单独的布尔值数组 $b$ 来实现，其中一旦数字 $i$ 出现，就将 $b[i]$ 的值改为 `true`。如果在遍历时发现 $b[i]$ 已经为 `true`，那就意味着 $i$ 已经在数组中出现过一次，我们现在找到了它的第二次出现。因此，我们可以输出该队员的索引两次（即开始和结束索引相同），以表示移除这位队员。

#### 子任务 2: $N = 2 \cdot T$ 且每个队伍在队列的每一半中各出现一次

在这个子任务中，我们同样可以让每个队伍都得到礼物。实现方式是选择队列的一半，并让这一半的所有人全部通过。这个策略是正确的，因为题目保证了每个队伍在队列的每一半中都恰好出现一次。所以，如果我们移除一半的队员，剩下的一半将恰好包含从 $0$ 到 $T-1$ 的所有队伍的各一名成员。因此，输出 $1$ 和 $N/2$ 或者 $N/2 + 1$ 和 $N$ 即可解决这个子任务。

#### 子任务 3: $T, N < 500$

这个子任务可以通过遍历所有可能的暂停区间并选择最优解来解决。具体来说，解法如下：

遍历暂停区间所有可能的起点和终点。对于一个特定的区间，我们需要检查移除该区间后，数组剩余部分是否由不同的数字组成。这可以使用与第一个子任务类似的策略来完成。最后，我们输出满足条件的那个最短的区间。

请注意，该解法的时间复杂度是 $O(N^3)$，这对于此子任务的数据范围是足够快的，但对于其余的子任务来说则太慢了。

---

#### 子任务 4: $N = 2 \cdot T$ 且每个队伍恰好出现两次

在这个子任务中，问题可以归结为找到一个包含所有元素至少一次的最短子数组。这个思路是充分的，因为如果所有元素都出现两次，我们必须为每个队伍移除其中一次出现，才能满足条件。

这个最短子数组可以用双指针方法找到。开始时，左指针指向第一个元素，而右指针指向最后一个第一次出现的元素所在的位置。这样，这两个指针之间的子数组就至少包含每个元素一次（因为它包含了每个元素的第一次出现）。

现在，我们需要移动指针，同时确保它们之间的数组始终满足这个条件。可以按以下方式进行：

在每一轮中，首先将左指针向右移动一位。这样，我们就从子数组中移除了一个元素的第一次出现。由于我们要求子数组必须包含所有元素，我们需要确保它现在能包含被移除元素的第二次出现。这可以通过向右移动右指针，直到子数组包含被移除元素的第二次出现为止。

在每一轮结束时，我们计算所构造子数组的长度。这个过程一直持续到左指针到达某个元素的第二次出现位置。最后，选择所有合法子数组中最短的一个。

#### 子任务 5: $T, N \le 5000$

在这个子任务中，我们的目标是将子任务 3 的时间复杂度从 $O(N^3)$ 优化到 $O(N^2)$。为此，我们需要加速对子数组是否满足条件的检查。

首先，计算每个元素出现的总次数。然后，我们再次遍历所有子数组。我们先固定子数组的起点，然后遍历所有可能的终点。在此过程中，我们可以维护一个数组 $b$，其中 $b[i]$ 是第 $i$ 个元素在当前子数组中的出现次数。同时，维护一个计数器 $c$，记录在子数组之外出现超过一次的元素的数量。对于一个元素 $i$，当它在子数组外的出现次数大于 $1$ 时，就属于这种情况，这精确地发生在它的总出现次数与 $b[i]$ 的差大于 $1$ 时。一个子数组满足条件当且仅当 $c=0$。当我们把子数组的终点向右移动一位时，$b$ 和 $c$ 均可在常数时间内更新。最后，选择满足条件的最短子数组。

#### 子任务 6: 无额外限制

对于完整解法，需要以下观察：如果一个元素出现超过两次，那么它第一次和最后一次出现之间的每一次出现，都必定在我们想要移除的子数组中。

首先，为什么这是正确的？让我们假设有一个元素出现了两次以上，并且存在一次既非首次也非末次出现，但它不在我们选择的移除子数组中。这个被移除的子数组必须完全位于该元素出现的左侧或右侧。如果它在左侧，那么我们知道该元素的最后一次出现以及我们正在讨论的这一次出现，都将位于移除所选子数组后剩下的部分中。这意味着任务的条件没有被满足。如果它在右侧，我们会得到一个类似的矛盾。

我们将这些出现（既非首次也非末次的出现）称为“中间出现”。利用这个观察，我们可以通过以下方式压缩给定的数组：我们将移除由所有元素中第一次和最后一次“中间出现”所界定的子数组，因为我们知道这些数字必定在最终选择的移除区间内。

现在，我们将完整任务简化为了一个带有两个附加约束的子任务 4：

1.  元素最多出现两次，所以可能有些元素只出现一次。
2.  我们必须将被移除的元素（即所有“中间出现”）包含在最终选择的子数组中。

---

由于在选择子数组时可以忽略那些最多出现一次的元素，我们可以使用类似于子任务 4 的算法，然后将找到的区间与我们已经移除的（包含所有“中间出现”的）区间进行合并。

---

## 作者：DengDuck (赞：1)

這題顯然可以雙指針，分析一下兩個單調性。

首先，我們固定左端點 $L$，我們假設知道最大的 $R$ 使得存在 $x$ 的出現次數 $cnt_x>1$，那麼 $R$ 變小跳過的元素更少，$cnt_x$ 不可能變小，所以 $(L,R)$ 永遠也不會合法，因此存在一個節點 $R$ 使得 $r\leq R$ 的 $(L,r)$ 都不合法，$r>R$ 的 $(L,r)$ 都合法。

其次，對於 $L'>L$，我們嘗試證明對應的 $R'$ 滿足 $R'>R$。

考慮對於 $(L,R)$，存在 $cnt_x>1$，那麼對於 $(L',R)$ 元素只會變多，$cnt_x$ 不可能變小，所以 $(L',R)$ 肯定不合法，也就是 $R'>R$。

所以我們就證明了直接雙指針就可以了，具體的，我們枚舉 $L$，記錄一個指針 $R$，用一個桶記錄元素出現次數並判斷 $(L,R)$ 是否合法，不合法則移動 $R\gets R+1$。

時間複雜度為 $\mathcal O(n)$，注意代碼求解過程中 $L$ 和 $R$ 表示的是實際的 $L-1$ 和 $R+1$，而且下標以 $1$ 開始。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int T,n,A[N],Ans,C[N],L,R;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T>>n;
	for(int i=1;i<=n;i++)cin>>A[i];
	int t=n+1;
	while(1<t&&C[A[t-1]]==0)t--,C[A[t]]++;
	Ans=n-t+1,L=0,R=t;
	for(int i=1;i<n;i++)
	{
		C[A[i]]++;
		while(t<=n&&(t<=i||C[A[i]]==2))C[A[t]]--,t++;
		if(C[A[i]]==2)break;
		int K=i+n-t+1;
		if(K>Ans)Ans=K,L=i,R=t;
	}
	cout<<L<<' '<<R-2<<endl;
}
```

---

## 作者：mumuxiao20111101 (赞：0)

# 题解：P13339 \[EGOI 2025] 礼品盒

## 思路：

我们需要找到一个连续区间 $l,r$ 跳过，使得剩下的前缀 $0,l-1$ 和后缀 $r+1,N-1$ 中，每支队伍最多出现一次，且前缀和后缀的队伍集合互不相交。目标是在最大化获得礼品盒的队伍数的前提下，最小化跳过的选手数量（说白了就是 $r-l+1$ 最小）。

当然了，暴力一定过不了，可以使用双指针，维护一个左指针 $j$，确保区间 $0,i$ 中没有重复队伍。从右向左遍历序列，再维护一个右指针 $k$，确保区间 $i,N-1$ 中没有重复队伍。

对于有效后缀起始位置，可以预处理一个数组 $nv$ 其中 $nv_k$ 表示从位置 $k$ 开始，满足后缀 $r+1,N-1$ 无重复的最小 $r$。

最后，枚举所有可能的前缀结束位置，包括前缀为空的情况（$i=-1$），对于每个有效的前缀结束位置 $i$，计算必须跳过的位置 $R$（即前缀中所有队伍最后出现位置的最大值），然后利用 $nv$ 找到最小的 $r$ 使得后缀有效，并计算总队伍数和跳过区间长度，更新最优解。

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T, N;
	cin >> T >> N;
	vector<int> a(N);
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	
	vector<int> la(T, -1);
	for (int i = 0; i < N; i++) {
		la[a[i]] = i;
	}
	
	vector<bool> pv(N, false);
	vector<int> lo(T, -1);
	int j = 0;
	for (int i = 0; i < N; i++) {
		if (lo[a[i]] != -1) {
			j = max(j, lo[a[i]] + 1);
		}
		lo[a[i]] = i;
		pv[i] = (j == 0);
	}
	
	vector<bool> sv(N + 1, false);
	sv[N] = true;
	vector<int> no(T, N);
	int k = N;
	for (int i = N - 1; i >= 0; i--) {
		k = min(k, no[a[i]]);
		if (k >= N) {
			sv[i] = true;
		} else {
			sv[i] = false;
		}
		no[a[i]] = i;
	}
	
	vector<int> nv(N, 1000000000);
	if (N - 1 >= 0) {
		if (sv[N - 1 + 1]) {
			nv[N - 1] = N - 1;
		} else {
			nv[N - 1] = 1000000000;
		}
		for (int kk = N - 2; kk >= 0; kk--) {
			if (sv[kk + 1]) {
				nv[kk] = kk;
			} else {
				nv[kk] = nv[kk + 1];
			}
		}
	}
	
	int R = 0;
	int bt = -1;
	int bl = 1000000000;
	int al = -1, ar = -1;
	
	if (N > 0) {
		int r = nv[0];
		if (r < 1000000000) {
			int t = 0;
			if (r < N - 1) {
				t = (N - 1 - r);
			}
			int l = r + 1;
			if (t > bt || (t == bt && l < bl)) {
				bt = t;
				bl = l;
				al = 0;
				ar = r;
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		R = max(R, la[a[i]]);
		if (!pv[i]) {
			continue;
		}
		int r;
		if (R < N) {
			r = nv[R];
		} else {
			r = 1000000000;
		}
		if (r >= 1000000000) {
			continue;
		}
		int d = i + 1;
		int t;
		if (r < N - 1) {
			t = d + (N - 1 - r);
		} else {
			t = d;
		}
		int l = r - i;
		if (t > bt || (t == bt && l < bl)) {
			bt = t;
			bl = l;
			al = i + 1;
			ar = r;
		}
	}
	
	cout << al << " " << ar << endl;
	
	return 0;
}
```

---

