# League of Leesins

## 题目描述

Bob is an avid fan of the video game "League of Leesins", and today he celebrates as the League of Leesins World Championship comes to an end!

The tournament consisted of $ n $ ( $ n \ge 5 $ ) teams around the world. Before the tournament starts, Bob has made a prediction of the rankings of each team, from $ 1 $ -st to $ n $ -th. After the final, he compared the prediction with the actual result and found out that the $ i $ -th team according to his prediction ended up at the $ p_i $ -th position ( $ 1 \le p_i \le n $ , all $ p_i $ are unique). In other words, $ p $ is a permutation of $ 1, 2, \dots, n $ .

As Bob's favorite League player is the famous "3ga", he decided to write down every $ 3 $ consecutive elements of the permutation $ p $ . Formally, Bob created an array $ q $ of $ n-2 $ triples, where $ q_i = (p_i, p_{i+1}, p_{i+2}) $ for each $ 1 \le i \le n-2 $ . Bob was very proud of his array, so he showed it to his friend Alice.

After learning of Bob's array, Alice declared that she could retrieve the permutation $ p $ even if Bob rearranges the elements of $ q $ and the elements within each triple. Of course, Bob did not believe in such magic, so he did just the same as above to see Alice's respond.

For example, if $ n = 5 $ and $ p = [1, 4, 2, 3, 5] $ , then the original array $ q $ will be $ [(1, 4, 2), (4, 2, 3), (2, 3, 5)] $ . Bob can then rearrange the numbers within each triple and the positions of the triples to get $ [(4, 3, 2), (2, 3, 5), (4, 1, 2)] $ . Note that $ [(1, 4, 2), (4, 2, 2), (3, 3, 5)] $ is not a valid rearrangement of $ q $ , as Bob is not allowed to swap numbers belong to different triples.

As Alice's friend, you know for sure that Alice was just trying to show off, so you decided to save her some face by giving her any permutation $ p $ that is consistent with the array $ q $ she was given.

## 样例 #1

### 输入

```
5
4 3 2
2 3 5
4 1 2
```

### 输出

```
1 4 2 3 5 
```

# 题解

## 作者：postpone (赞：2)

既然都是三元组，那么统计三元组数组中，所有数字出现的次数，出现一次的肯定在首或者尾。

找一个满足上述要求的作为开头。同理，第二个数应该只出现两次，且它所在的一个三元组要包含开头。

从第三个位置开始，每个位置 $i$ 都可以从位置 $i-2$ 所在的所有三元组中，唯一没确定的数得到——因为 $i$ 之前的位置都确定了。

拿示例来说：

```
5
4 3 2
2 3 5
4 1 2
```

1. 发现 $1$ 只出现一次，把它放到开头。

1. 看 $1$ 所在的三元组，$2$ 出现了三次，$4$ 出现了两次，那么 $4$ 就放在第二个。

1. 第三个位置就是 $1$ 所在的三元组中，没确定的数，那就是 $4$。

1. 第四个位置来源于包含 $4$ 的所有三元组中没确定的数，发现是 $3$。往后的推导同理。

因为每个数至多出现三次，所以复杂度仍可视作线性，代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    vector<array<int, 3>> q(n - 2);
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> q[i][j];
            q[i][j]--;
        }
    }

    vector a(n, vector<int>());
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < 3; j++) {
            a[q[i][j]].push_back(i);
        }
    }

    vector<int> p(n);
    vector<bool> used(n);

    for (int i = 0; i < n; i++) {
        if (a[i].size() == 1) {
            p[0] = i;
            used[p[0]] = true;
            break;
        }
    }

    for (auto i : a[p[0]]) {
        for (int j = 0; j < 3; j++) {
            if (a[q[i][j]].size() == 2) {
                p[1] = q[i][j];
                break;
            }
        }
        used[p[1]] = true;
    }
    for (int i = 2; i < n; i++) {
        for (auto j : a[p[i - 2]]) {
            for (int k = 0; k < 3; k++) {
                if (not used[q[j][k]]) {
                    p[i] = q[j][k];
                }
            }
        }
        used[p[i]] = true;
    }
    for (auto i : p) {
        cout << i + 1 << " ";
    }

    return 0;
}
```

---

## 作者：alan1118 (赞：1)

看到我们般的其他同学都是用拓扑 AC 的，但是我觉得完全不需要用到图论，这里我提供一个我的想法，灵感来自 [CF1095D](https://www.luogu.com.cn/problem/CF1095D)，那道题是“两元组”，而这道题是“三元组”，但思路是相同的。

## 思路

可以先举个例子：

当 $n=8$，我们可以画出图：

![pic](https://cdn.luogu.com.cn/upload/image_hosting/sggps6sf.png)

这样我们就会发现，$p_1,p_n$ 只会被记录一次，$p_2,p_{n-1}$ 只会被记录 $2$ 次，而且 $p_1,p_2$ 一定在同一个三元组，$p_{n-1},p_n$ 一定在同一个三元组。

那么我们就可以记下每个数出现的次数，这样就可以恢复出 $p_1$ 和 $p_2$ 了，那 $p_1,p_2$ 所在的三元组剩下的那一个就是 $p_3$，确定了 $p_2$ 和 $p_3$ 后，那在$p_2,p_3$ 所在的三元组的另外一个就是 $p_4$。这样以此类推，最后就能得到完整的 $p$ 了。

## Code
``` cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 5;

int q[N][5];
vector<int> v[N];
int ans[N];
bool vis[N];

int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n-2; i++)
		for(int j = 1; j <= 3; j++)
		{
			cin >> q[i][j];
			v[q[i][j]].push_back(i);
		}
	for(int i = 1; i <= n; i++)
		if(v[i].size() == 1)
		{
			ans[1] = i, vis[i] = true;
			for(auto j:v[i])
				for(int l = 1; l <= 3; l++)
					if(v[q[j][l]].size() == 2)
						ans[2] = q[j][l], vis[q[j][l]] = true;
			break;
		}
    for(int i = 3; i <= n; i++)
		for(auto j:v[ans[i-2]])
		{
			for(int l = 1; l <= 3; l++)
				if(!vis[q[j][l]])
					ans[i] = q[j][l], vis[q[j][l]] = true;
			if(ans[i]) break;
		}
	for(int i = 1; i <= n; i++) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：1)

很套路的题目  
显然要把所有三元组串成一串,那么就考虑把数字作为结点,三元组代表的关系作为边建图。  
当然这只是方便思考。  
实际上,我们发现这样做的话在所有三元组中处在原序列的两头的标号只出现一次,或者说度数为1。出现在原序列第2个和倒数第二个的标号出现两次,度数为2。中间的点度数为3。  
已知链的两个点$... a,b $,下一个点是什么。  
考虑包含b的所有三元组(至多3个),显然下一个点是包含$a,b$的一个三元组中的另外一个。  
那么像深搜一样就能把链给搞出来了。  
```cpp
#include <iostream>
#include <vector>
#define pb push_back

using namespace std;

const int N = 123456;

struct tre{
	int a, b, c;
	tre() {}
	tre(int A, int B, int C): a(A), b(B), c(C) {}
	bool exi(int t) { return a == t || b == t || c == t; }
	int minu(int x, int y) { return a ^ b ^ c ^ x ^ y; }
};
vector<tre> v[N];
vector<int> ans;
int vis[N];

void make(int pre, int now) {
	ans.pb(now);
	for(int i = 0; i < v[now].size(); ++i)
		if(v[now][i].exi(pre)) {
			int tmp = v[now][i].minu(now, pre);
			if(vis[tmp]) continue;
			vis[tmp] = 1;
			make(now, tmp);
			return;	
		}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, a, b, c, d11 = -1, d12 = -1, d21 = -1, d22 = -1;
	cin >> n;
	for(int i = 1; i < n - 1; ++i) {
		cin >> a >> b >> c;
		tre tmp(a, b, c);
		v[a].pb(tmp);
		v[b].pb(tmp);
		v[c].pb(tmp);
	}
	for(int i = 1; i <= n; ++i) {
		if(v[i].size() == 1) {
			if(~d11) d12 = i;
			else d11 = i;
		} else if(v[i].size() == 2) {
			if(~d21) d22 = i;
			else d21 = i;
		}
	}
	ans.pb(d11);
	if(v[d11][0].exi(d21)) {
		vis[d11] = vis[d21] = 1;
		make(d11, d21);
	} else {
		vis[d11] = vis[d22] = 1;
		make(d11, d22);
	}
	for(int i = 0; i < ans.size(); ++i) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}
```

---

