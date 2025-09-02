# Darius' Wisdom

## 题目描述

大流士一世正在建造 $ n $ 根石柱，每根石柱由一个底座和不超过两个铭文块构成。

在每次操作中，大流士可以选择两根石柱 $ u $ 和 $ v $，只要这两根石柱的铭文数量差恰好为 $ 1 $，就可以将一个铭文从较多的一根转移到较少的一根。可以保证至少有一根石柱含有正好 $ 1 $ 个铭文。

为使得石柱看起来更美观，大流士希望这些石柱的铭文数量按不减顺序排列。为了减少工人们的辛劳，他希望你制定一个操作序列，最多使用 $ n $ 次操作实现这一目标，不需要优化操作次数。

## 说明/提示

以下是几个测试用例的样例状态：

- 第一个测试用例：
  - 初始状态：$ 0, 2, 0, 1 $
  - 第一次操作后：$ 0, 1, 0, 2 $
  - 第二次操作后：$ 0, 0, 1, 2 $

- 第二个测试用例：
  - 初始状态：$ 1, 2, 0 $
  - 第一次操作后：$ 0, 2, 1 $
  - 第二次操作后：$ 0, 1, 2 $

- 在第三个测试用例中，石柱的铭文数量已经是按升序排列的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
4
0 2 0 1
3
1 2 0
6
0 1 1 2 2 2```

### 输出

```
2
2 4
2 3
2
3 1
2 3
0```

# 题解

## 作者：__little__Cabbage__ (赞：4)

## Solution

设 $c_i$ 为数字 $i$ 的出现次数。

因为 $3$ 个数的时候 $0$ 与 $2$ 不好操作，所以考虑先把一个数归位，把问题转化为 $2$ 个数。

先把 $0$ 归位。考虑在一个 $0$ 本来该在的位置上（$1 \sim c_0$）可能出现三种情况：

- $0$：已经合法了，跳过。
- $1$：拿后面一个 $0$ 与其交换即可，需要 $1$ 步操作。
- $2$：这时候比较麻烦，需要先用一个 $1$ 把 $2$ 换出来，再用 $0$ 换掉 $1$，需要 $2$ 步操作。

然后计算一下在最坏情况下需要几步才能将 $0$ 归位，也就是在本该为 $0$ 的位置全都是 $2$，但由于一共只有 $n$ 个数，如果 $2$ 太多了那 $0$ 一定会变少，$0$ 太多了 $2$ 一定会变少，所以它是有一个制衡点的，也就是 $c_0 = c_1 + c_2$ 的时候，所以最大操作次数为 $2 \times \min(c_0,c_1+c_2)$，但实际上因为不可能没有 $1$，所以还是要小一点点的。

由于 $0$ 都归位了，那剩下的就好办了，没对不合法的 $1,2$ 依次交换即可，操作次数为 $\min(c_1,c_2)$。

所以最大总操作次数为 $2 \times \min(c_0,c_1+c_2) + \min(c_1,c_2)$，由于先操作 $0$ 和先操作 $2$ 是同理的，所以我们不妨假设 $c_0 < c_2$，那么操作次数就变为 $2 \times c_0 + \min(c_1,c_2)$ 了，可以发现它是 $\le c_0 + \max(c_1,c_2) + \min(c1,c2)$ 的（因为 $c_0 < c_2$ 嘛），也就是 $\le n$ 的。

于是分讨 $c_0$ 与 $c_2$ 的大小关系即可，但神奇的是，直接将 $0$ 归位也可以 AC。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

#define int long long
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rpe(i,a,b) for(int i=(a);i>=(b);--i)
#define pii pair <int,int>
#define mp make_pair
#define st first
#define nd second
#define pb emplace_back

using namespace std;

const int MAXN=2e5+5;
int n,a[MAXN],c0,c1,c2;
vector <pii> v;

il void opt(int x,int y) {swap(a[x],a[y]),v.pb(x,y);}

il void solve(int __Ti)
{
    vector<pii>().swap(v);

    cin>>n;
    c0=c1=c2=0;
    rep(i,1,n) cin>>a[i],a[i]==0 ? ++c0 : a[i]==1 ? ++c1 : ++c2;

    if(c0<=c2)
    {
        int j=c0+1;
        rep(i,1,c0)
        {
            while(a[j]!=0) ++j;
            a[i]==1 && (opt(i,j),1);
        }

        int p=-1;
        rep(i,c0+1,n) a[i]==1 && (p=i);
        rep(i,1,c0)
        {
            while(a[j]!=0) ++j;
            a[i]==2 && (opt(i,p),opt(i,j),p=j,1);
        }

        int i=c0+1; j=c0+c1+1;
        while(i<c0+c1+1 && j<n+1)
        {
            if(a[i]==2 && a[j]==1) opt(i,j);
            a[i]==1 && (++i);
            a[j]==2 && (++j);
        }
    }

    else
    {
        int j=1;
        rep(i,c0+c1+1,n)
        {
            while(a[j]!=2) ++j;
            a[i]==1 && (opt(i,j),1);
        }

        int p=-1;
        rep(i,1,c0+c1) a[i]==1 && (p=i);
        rep(i,c0+c1+1,n)
        {
            while(a[j]!=2) ++j;
            a[i]==0 && (opt(i,p),opt(i,j),p=j,1);
        }

        int i=1; j=c0+1;
        while(i<c0+1 && j<c0+c1+1)
        {
            if(a[i]==1 && a[j]==0) opt(i,j);
            a[i]==0 && (++i);
            a[j]==1 && (++j);
        }
    }

    cout<<v.size()<<'\n';
    for(auto i:v) cout<<i.st<<' '<<i.nd<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    int __T; cin>>__T; rep(__Ti,1,__T) solve(__Ti);
    return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

比 C 简单。考虑用 set 来维护当前所有 $0,1,2$ 的位置。每一次找到最后一个 $0$ 和最前一个 $1$（需要满足最后一个 $0$ 在最前一个 $1$ 后面）或最后一个 $2$ 和最前一个 $1$（需要满足最后一个 $2$ 在最前一个 $1$ 后面）交换。容易证明该策略正确。判断当前数组是否有序可以维护当前所有出现过的不同数字，然后用 set 找到当前数字最前和最后的位置就行了。

时间复杂度为 $O(n\log n)$，自带大常数（雾

```cpp
int a[N];
void run() {
    int T = read(), ca = 1;
    while (T--) {
        int n = read();
        for (int i = 1; i <= n; ++i)
            a[i] = read();
        set<int> buc[3];
        for (int i = 1; i <= n; ++i)
            if (a[i] == 0) buc[0].insert(i);
            else if (a[i] == 1) buc[1].insert(i);
            else buc[2].insert(i);
        auto chk = [&](void) {
            int cnt = 0;
            vector<int> id;
            for (int i = 0; i < 3; ++i)
                if (buc[i].size()) ++cnt, id.eb(i);
            if (cnt == 1) return 1;
            else if (cnt == 2) {
                if (*buc[id[0]].rbegin() < *buc[id[1]].begin()) return 1;
                return 0;
            } else {
                if (*buc[0].rbegin() < *buc[1].begin() && *buc[1].rbegin() < *buc[2].begin()) return 1;
                return 0;
            }
        };
        vector<pair<int, int>> op;
        while (!chk()) {
            if (buc[0].size() && buc[1].size()) {
                int x = *buc[0].rbegin(), y = *buc[1].begin();
                if (x > y) {
                    op.eb(x, y);
                    buc[0].erase(x);
                    buc[1].erase(y);
                    buc[0].insert(y);
                    buc[1].insert(x);
                }
            }
            if (chk()) break;
            if (buc[1].size() && buc[2].size()) {
                int x = *buc[1].rbegin(), y = *buc[2].begin();
                if (x > y) {
                    op.eb(x, y);
                    buc[1].erase(x);
                    buc[2].erase(y);
                    buc[1].insert(y);
                    buc[2].insert(x);
                }
            }
        }
        cout << op.size() << '\n';
        for (auto &[x, y] : op)
            cout << x << ' ' << y << '\n';
    }
}
```

---

## 作者：wfc284 (赞：0)

总次数不超过 $n$，因此平均每一步就要有一个元素归位。  
已归位的当然不用管。

定义【$x$ 在 $y$ 位】表示原串中一个 $x$ 在目标串一个 $y$ 的位置。
又有每一次操作要动 $1$，我们先考虑将【$1$ 在 $0$ 位，$0$ 在 $1$ 位】和【$1$ 在 $2$ 位，$2$ 在 $1$ 位】的数操作。即：花一步操作将一个 $0$ 或一个 $2$ 归位。  

经过这些操作，一定只会有【$0$ 在 $2$ 位，$2$ 在 $0$ 位】的数。我们先花一步【启动】一下，将中间一个 $1$ 和一个【$0$ 在 $2$ 位】交换一下，就可以重复上面的过程。最后，我们将 $1$ 和一个 $0$ 或一个 $2$ 交换即可。  
我们虽然【启动】时损失了一步，但是在最后我们一步归位了两个数，故平均还是每步有一个元素归位。  

维护的话，用 `set` 啥的乱维护一下，$2 \times 10^5$ 的数据随便过。

---

