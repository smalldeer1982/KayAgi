# Wilbur and Points

## 题目描述

威尔伯正在研究一组坐标平面上的 $n$ 个点。这些点坐标的所有分量都是非负整数。更重要的是，如果点 $(x, y)$ 属于这个集合，那么所有满足 $0 \le x' \le x$ 和 $0 \le y' \le y$ 的点 $(x', y')$ 也会在这个集合中。

威尔伯现在想给这些点编号，从 $1$ 到 $n$ 各不相同。为了让编号更加美观，威尔伯设置了一个条件：如果某个点 $(x, y)$ 被分配了编号 $i$，那么所有满足 $x' \ge x$ 且 $y' \ge y$ 的点 $(x', y')$ 的编号不能小于 $i$。例如，对于点集 $(0, 0)$、$(0, 1)$、$(1, 0)$ 和 $(1, 1)$，有两种美观的编号方式，分别是 $1, 2, 3, 4$ 和 $1, 3, 2, 4$。

威尔伯的朋友给他出了一个难题：对于每个点定义一个特殊值 $s(x, y) = y - x$。现在他给了威尔伯一些数 $w_1, w_2, \ldots, w_n$，并要求找到一种美观的编号，使得编号为 $i$ 的点的特殊值满足 $s(x_i, y_i) = y_i - x_i = w_i$。

威尔伯需要你的帮助来解决这个问题。

## 说明/提示

在第一个样例中，点 $(2, 0)$ 获得编号 $3$，点 $(0, 0)$ 编号为 $1$，点 $(1, 0)$ 编号为 $2$，点 $(1, 1)$ 编号为 $5$，点 $(0, 1)$ 编号为 $4$。通过验证，这种编号符合美观条件，并且满足 $y_i - x_i = w_i$。

在第二个样例中，点集中的特殊值为 $0, -1, -2$，而朋友给的序列为 $0, 1, 2$，因此不存在满足条件的解答。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2 0
0 0
1 0
1 1
0 1
0 -1 -2 1 0
```

### 输出

```
YES
0 0
1 0
2 0
0 1
1 1
```

## 样例 #2

### 输入

```
3
1 0
0 0
2 0
0 1 2
```

### 输出

```
NO
```

# 题解

## 作者：liuzhongrui (赞：1)

## 思路

[中文题面](https://www.luogu.com.cn/paste/wc4i2r0j)（仅供参考）

如果有一个整数 $d$，则 $w_i$ 等于 $d$ 与权重等于 $d$ 的给定方块的数量不同，则答案自动为 ```NO```。这可以通过使用 map 检查。$w_i$ 以及方块的权重，并检查 map 是否相同。

时间复杂度为 $O(n\log{n})$。

设 $d$ 为整数，设 $D$ 为所有 $i$ 的集合，以便 $w_i = d$，设 $W$ 是所有特殊点的集合，因此 $(x,y)$ 的权重为 $d$。请注意，$W$ 和 $D$ 具有相同数量的元素。假设我 $1< i_2< ...< i_k$ 是 $D$ 的元素。设 $(a,b) < (c,d)$ 如果 $a < c$ 或 $a = c$ 和 $b < d$。假设 $(x_1,y_1) < (x_2,y_2) < ...< (x_k,y_k)$ 是 $W$ 的元素。请注意，这一点 $(x_j,y_j)$ 必须标注我 $j$ 对于 $1 \le J \le K$。

现在，每个特殊点都被标记了。仍然需要检查这是否是有效的标签。这可以通过采用向量数组来完成。向量 $arr_i$ 将用 $x$ 坐标 $i$ 表示点。这个向量可以很容易地用 $O(n)$ 时间内给出的点来制作，并且由于这些点已经被标记，$arr_{i,j}$ 将表示点 $(i,j)$ 的标签。现在，对于所有点 $(i,j)$，特殊的点 $(i,j + 1)$ 和特殊的点 $(i + 1,j)$ 必须具有大于 $(i,j)$ 的数字。此步骤总共需要 $O(n)$ 时间。

时间复杂度为 $O(n\log{n})$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int main() {
	int n;
	map<int,vector<pair<int,int> > > weights;
	map<int,vector<int> > cnt;
	pair<int,int> ans[N];
	vector<int> diag[N];
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		while (diag[a].size()<=b) diag[a].push_back(0);
		weights[b-a].push_back(make_pair(a,b));
	}
	for (auto& v: weights) {
		sort(v.second.begin(),v.second.end());
	}
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		cnt[a].push_back(i);
	}
	for (auto v: cnt) {
		if (weights.count(v.first)==0 || weights[v.first].size()!=v.second.size()) {
			printf("NO\n");
			return 0;
		}
		for (int i=0; i<v.second.size(); i++) {
			ans[v.second[i]]=weights[v.first][i];
			diag[weights[v.first][i].first][weights[v.first][i].second]=v.second[i];
		}
	}
	for (int i=0; i<N; i++) {
		for (int j=0; j<(int)diag[i].size(); j++) {
			if ((int)diag[i+1].size()>j && diag[i+1][j]<diag[i][j]) {
				printf("NO\n");
				return 0;
			}
			if (j+1<(int)diag[i].size() && diag[i][j]>diag[i][j+1]) {
				printf("NO\n");
				return 0;
			}
		}
	}
	printf("YES\n");
	for (int i=0; i<n; i++) {
		printf("%d %d\n",ans[i].first,ans[i].second);
	}
	return 0;
}
//语言：C++14 (GCC 9)
```


---

## 作者：LJ07 (赞：0)

贪心模拟，当前用过的呈现一个 $x$ 越大，$y$ 越小的态势，每次取一个 $x$ 尽可能小的即可，这样不劣。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n, w[N + 5], r[N + 5], nx[N + 5], mp[N + N + 5];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    memset(r, -1, sizeof r);
    memset(mp, -1, sizeof mp);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        r[y] = max(r[y], x);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    for (int i = 0; i <= N; ++i) {
        r[i] = i - r[i];
        nx[i] = i;
        if (r[i] <= i) {
            mp[i + N] = i;
        }
    }
    vector<pair<int, int> > ans;
    for (int i = 1; i <= n; ++i) {
        int &t = mp[w[i] + N];
        if (~t) {
            ans.emplace_back(t - nx[t], t);
            mp[t] = 0;
            if (t && t - nx[t] > (t - 1) - nx[t - 1]) {
                cout << "NO";
                return 0;
            }
            if (--nx[t] >= r[t]) {
                mp[nx[t] + N] = t;
            }
            t = -1;
        }
        else {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES\n";
    for (auto [x, y] : ans) {
        cout << x << ' ' << y << '\n';
    }
    return 0;
}
```

---

