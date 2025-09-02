# [ABC356G] Freestyle

## 题目描述

高桥可以游出 $N$ 种不同的风格。  
当他用第 $i$ 式游泳时，每秒消耗 $A_i$ 体力，每秒前进 $B_i$ 米。

回答 $Q$ 个问题。 第 $i$ 次查询如下：

- 判断是否有可能在总体力消耗不超过 $C_i$ 的情况下前进 $D_i$ 米。如果可能，请找出所需的最少秒数。

在这里，他可以自由组合不同的泳姿，切换泳姿的时间可以忽略不计。  
具体来说，他可以使用以下步骤游泳：

- 选择一个正整数 $m$ ，一个长度为 $m$ 的正实数序列 $t=(t_1,t_2,\dots,t_m)$ ，以及一个长度为 $m$ 的整数序列 $x=(x_1,x_2,\dots,x_m)$ ，其中每个元素都介于 $1$ 和 $N$ 之间（含）。
- 然后，按照 $i=1,2,\dots,m$ 的顺序，以第 $x_i$ 的方式游 $t_i$ 秒。

## 说明/提示

#### 限制因素

- 所有输入值均为整数。
- $1 \le N \le 2 \times 10^5$
- $1 \le A_i, B_i \le 10^9$
- $1 \le Q \le 2 \times 10^5$
- $1 \le C_i, D_i \le 10^9$ 

#### 样例 $1$ 说明

在此输入中，高桥可以用以下四种方式游泳：

- 消耗 $1$ 体力，每秒前进 $2$ 米。
- 消耗 $2$ 体力，每秒前进 $3$ 米。
- 消耗 $3$ 体力，每秒前进 $3$ 米。
- 消耗 $4$ 体力，每秒前进 $4$ 米。

此输入包含五个查询。

- 第一个查询，$C_1=4, D_1=7$ 。
    - 选择 $t=(1,2)$ 和 $x=(2,1)$ 。高桥游泳的过程如下：
        - 在前 $1$ 秒，他消耗了 $2$ 体力，前进了 $3$ 米。
        - 接下来的 $2$ 秒，他消耗了 $2$ 体力，前进了 $4$ 米。
    - 他总共消耗了 $4$ 体力，前进了 $7$ 米。所需的时间为 $3$ 秒，这是最小值。
- 第二个查询，$C_2=7, D_2=7$ 。
    - 选择 $t=(7/4)$ 和 $x=(4)$ 。高桥游程如下：
        - 在最初的 $7/4$ 秒内，他消耗了 $7$ 体力，前进了 $7$ 米。
    - 他总共消耗了 $7$ 体力，前进了 $7$ 米。所需的时间为 $7/4$ 秒，这是最小值。
- 第三个查询，$C_3=49, D_3=100$ 。
    - 无论高桥如何游泳，都不可能在总体力消耗不超过 $49$ 的情况下前进 $100$ 米。
- 第四个查询， $C_4=1000, D_4=500$ 。
    - 选择 $t=(125)$ 和 $x=(4)$ 。高桥游泳的情况如下：
        - 在前 $125$ 秒，他消耗了 $500$ 体力，前进了 $500$ 米。
    - 他总共消耗了 $500$ 体力，前进了 $500$ 米。所需的时间为 $125$ 秒，这是最小值。
- 第五个查询， $C_5=4, D_5=5$ 。
    - 选择 $t=(1/2,1)$ 和 $x=(4,2)$ 。高桥游程如下：
        - 在前 $1/2$ 秒，他消耗了 $2$ 体力，前进了 $2$ 米。
        - 在接下来的 $1$ 秒内，他消耗了 $2$ 点体力，前进了 $3$ 米。
    - 他总共消耗了 $4$ 体力，前进了 $5$ 米。所需的时间为 $3/2$ 秒，这是最短时间。

## 样例 #1

### 输入

```
4
1 2
2 3
3 3
4 4
5
4 7
7 7
49 100
1000 500
4 5```

### 输出

```
3.000000000000000000
1.750000000000000000
-1
125.000000000000000000
1.500000000000000000```

# 题解

## 作者：cancan123456 (赞：8)

方便起见，将 $A=0,B=0$ 作为一个 style 加入题目给出的 $n$ 种 $(A_i,B_i)$ 中。

首先考虑两个 style 的组合，如果存在两个 style $(A_i,B_i),(A_j,B_j)$，那么对于任何实数 $t\in[0,1]$，style $(tA_i+(1-t)A_j,tB_i+(1-t)B_j)$ 是可行的 style，即，如果把 $A$ 作为横坐标，$B$ 作为纵坐标将所有的 style 画在平面上，则这些 style 构成的凸包内都是可行的。

注意到，对于一个 style $(A,B)$，如果 $A'\ge A,B'\le B$，那么 style $(A',B')$ 也是合法的，对应在平面上，就是一个点右下的所有点都是合法的。

那么满足这两个条件的所有 style 是所有 style 的上凸壳的一部分中，只保留 $B_i$ 单调增加的部分的下方。

这么说可能比较抽象，举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/mrblr1qh.png)

$O,A,B,C,D,E$ 都是给出的 style，所有可行 style 是图中折线的下方。

上凸壳包含 $O,A,B,D,E$，因为 $E$ 在 $D$ 的右下方，所以被扔掉了。

不会求上凸壳的可以查看 [P2742](https://www.luogu.com.cn/problem/P2742) 的[题解区](https://www.luogu.com.cn/problem/solution/P2742)并学习 Jarvis 算法。

现在我们求出了所有可行 style，考虑一个询问 $(C,D)$，容易发现能够在**恰好** $t$ 秒内游完全程，等价于 $\left(\dfrac Ct,\dfrac Dt\right)$ 是一个可行 style。

将所有正实数 $t$ 对应的 $\left(\dfrac Ct,\dfrac Dt\right)$ 画在平面上，发现这是一条过原点的射线，如果要求速度最快，等价于 $B$ 最大，即找到这条斜率为 $\dfrac DC$ 过原点的射线与可行域边界的交点，可以用极角排序或者二分解决，注意特判无解。

```cpp
#include <cstdio>
#include <map>
using namespace std;
typedef long long ll;
const int N = 200005;
map < ll, ll > mp;
struct Style {
	ll A, B;
	void read() {
		scanf("%lld %lld", &A, &B);
	}
	void write(char c = '\n') {
		printf("%lld %lld%c", A, B, c);
	}
} style[N];
double f[N];
ll A(int i) {
	return style[i].A;
}
ll B(int i) {
	return style[i].B;
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		ll A, B;
		scanf("%lld %lld", &A, &B);
		if (mp.count(A) == 0) {
			mp[A] = B;
		} else {
			mp[A] = max(mp[A], B);
		}
	}
	int cnt = 1;
	style[1].A = 0;
	style[1].B = 0;
	for (pair < ll, ll > p : mp) {
		ll A = p.first, B = p.second;
		while (cnt >= 2 && (A - style[cnt - 1].A) * (style[cnt].B - style[cnt - 1].B) <= (style[cnt].A - style[cnt - 1].A) * (B - style[cnt - 1].B)) {
			cnt--;
		}
		cnt++;
		style[cnt].A = A;
		style[cnt].B = B;
	}
	n = cnt;
	cnt = 1;
	for (int i = 2; i <= n; i++) {
		if (style[i].B > style[cnt].B) {
			cnt++;
			style[cnt] = style[i];
		}
	}
	n = cnt;
	int q;
	scanf("%d", &q);
	for (ll C, D; q != 0; q--) {
		scanf("%lld %lld", &C, &D);
		if (B(2) * C < D * A(2)) {
			printf("-1\n");
			continue;
		}
		int ans = n, l = 1, r = n - 1;
		// P(ans), P(ans + 1)
		while (l <= r) {
			int mid = (l + r) / 2;
			if (B(mid + 1) * C < D * A(mid + 1)) {
				ans = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		double t;
		if (ans == n) {
			t = 1.0 * B(n) / D;
		} else {
			t = 1.0 * (A(ans + 1) * B(ans) - A(ans) * B(ans + 1)) / (C * B(ans) + D * A(ans + 1) - C * B(ans + 1) - D * A(ans));
		}
		printf("%.12lf\n", 1.0 / t);
	}
	return 0;
}
```

---

## 作者：PTqwq (赞：1)

是一道好的凸包题。

首先考虑两种 style：$(A_1, B_1)$ 和 $(A_2, B_2)$，我们可以混合这两种 style 人造合成一种别的可行的 style，设比例为 $t(0 \leq t \leq 1)$，那么新的 style 为 $(A_1t + A_2(1 - t), B_1t + B_2(1 - t))$。

然后考虑一件事，如果我们用了 $t$ 秒，消耗了 $C$ 点，运动了 $D$ 米，那么就意味着存在 $\left(\dfrac{C}{t}, \dfrac{D}{t}\right)$ 这种 style，为什么可以这样做？其实很简单，就是把方案中的 style 按比例混合了。

然后来看两种 style 混合之后可以得到哪些 style，把式子改写一下就可以变成 $(A_2 + t(A_1 - A_2), B_2 + t(B_1 - B_2))$，不难发现其实这些点恰好是线段 $(A_1, B_1), (A_2, B_2)$ 上的点。

那我们其实把这 $n$ 个点建凸包，然后发现其实下凸壳没用，方案都会被上凸壳偏序，所以只留上凸壳，然后就是上凸壳最后斜率 $< 0$ 的部分也没必要留，删掉之后直接过最后一个点作往右的直线即可。而显然可以用的 style 就是这个凸包及其下面的点。

然后目标变成求一个过 $(0, 0)$ 的射线与一个上凸包的交点，交点有且仅有一个，而满足条件的点其实是直线及其上面的点，并且要求纵坐标最大，容易在凸包上二分求出答案。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

namespace PTqwq {

int readqwq() {
    int x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

ll readllqwq() {
    ll x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

const int N = 2e5 + 10;

int n, siz;
pair<ll, ll> a[N];
vector<pair<ll, ll>> C;

void solve() {
    ll c = readllqwq();
    ll d = readllqwq();

    if (siz <= 1) {
        printf("-1\n");
        return;
    }
    if (C[1].first * d > c * C[1].second) {
        printf("-1\n");
        return;
    }

    int L = 1, R = siz - 1, pos = siz;
    while (L <= R) {
        int mid = (L + R) / 2;
        if (C[mid].first * d > c * C[mid].second) {
            pos = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }

    long double ans;
    if (pos == siz) {
        ans = (1.0 * d) / (1.0 * C[siz - 1].second);
    } else {
        long double curk = (1.0 * (C[pos].second - C[pos - 1].second)) / 
                        (1.0 * (C[pos].first - C[pos - 1].first));
        long double curb = (1.0 * C[pos].second) - (1.0 * C[pos].first) * curk;
        long double curw = (1.0 * d) / (1.0 * c);
        ans = (-curb) / (curk - curw);
        ans = (1.0 * c) / ans;
    }
    printf("%.9Lf\n", ans);
}

void Solve() {
    n = readqwq();
    for (int i = 1; i <= n; ++ i) {
        ll x = readllqwq();
        ll y = readllqwq();
        a[i] = make_pair(x, y);
    }

    sort(a + 1, a + 1 + n);
    C.push_back(make_pair(0, 0));
    siz = 1;
    for (int i = 1; i <= n; ++ i) {
        ll x = a[i].first, y = a[i].second;
        if (i < n && a[i + 1].first == a[i].first) {
            continue;
        }
        while (siz >= 2) {
            if ((y - C[siz - 1].second) * (C[siz - 1].first - C[siz - 2].first) >=
                (C[siz - 1].second - C[siz - 2].second) * (x - C[siz - 1].first)) {
                C.pop_back();
                siz --;
            } else {
                break;
            }
        }
        siz ++;
        C.push_back(a[i]);
    }
    while (siz >= 2) {
        if (C[siz - 1].second <= C[siz - 2].second) {
            C.pop_back();
            siz --;
        } else {
            break;
        }
    }

    int q = readqwq();
    for (int i = 1; i <= q; ++ i) {
        solve();
    }
}

}

int main() {
    PTqwq::Solve();

    return 0;
}
```

---

## 作者：王华 (赞：1)

首先先考虑只给出两个向量的情况，单位时间内，在图上两个向量能组成的向量在其端点的连线上，推广到两个以上的情况，就成了点到线段或者一片区域内所有点连线覆盖的所有区域，并且容易说明最终的区域恰好在这些向量端点和原点构成的凸包内(包括凸包上)。



![](https://cdn.luogu.com.cn/upload/image_hosting/gy724eq9.png)



不妨以 $A$ 为平面直角坐标系原点，$H$ 为目标点，横轴代表距离，纵轴代表耐力，若直线 $AH$ 和凸包有两个交点，那么必然最终会到达的点是 $H$ 点。

简单证明：首先不可能在 $H$ 的上方，若落到了 $HI$ 上，则可以选择 $AJ$ 方向的向量代替并调整，更优。

那么做法就很显然了，首先判断和凸包有没有交点，只需和斜率最大和最小的点比较，再去二分这个交点并算出距离。

说几个容易错的点：不能按照极角排序来处理凸包；要特判凸包横坐标相等的情况；特判当凸包最上面或者最下面一条边和所求直线重合的情况。

---

