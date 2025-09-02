# MEX Cycle

## 题目描述

Evirir 这只龙有很多朋友。它有 **3** 个朋友！这比普通龙多一个。

你得到了三个整数 $ n $ , $ x $ 和 $ y $ 。有 $ n $ 只龙围成一个圈坐着。龙从 $ 1 $ 到 $ n $ 编号。对于每个 $ i $ ( $ 1 \le i \le n $ )，龙 $ i $ 与龙 $ i - 1 $ 和 $ i + 1 $ 是朋友，其中龙 $ 0 $ 被定义为龙 $ n $ ，龙 $ n + 1 $ 被定义为龙 $ 1 $ 。此外，龙 $ x $ 和龙 $ y $ 也是朋友（如果它们已经是朋友了，这不会改变任何东西）。请注意，所有的友谊都是相互的。

你需要输出 $ n $ 个非负整数 $ a_1, a_2, \ldots, a_n $ ，使得对于每只龙 $ i $ ( $ 1 \le i \le n $ )，以下条件成立：

- 设 $ f_1, f_2, \ldots, f_k $ 是龙 $ i $ 的朋友。那么 $ a_i = \operatorname{mex}(a_{f_1}, a_{f_2}, \ldots, a_{f_k}) $ 。 $ ^{\text{∗}} $

 $ ^{\text{∗}} $ 集合 $ c_1, c_2, \ldots, c_m $ 的最小排除值 (MEX) 被定义为最小的非负整数 $ t $ ，它不在集合 $ c $ 中出现。

## 说明/提示

对于第一个测试用例：

- $ i = 1 $ : 龙 $ 1 $ 的朋友是龙 $ 2, 3, 5 $  $ \operatorname{mex}(a_2, a_3, a_5) = \operatorname{mex}(2, 1, 1) = 0 = a_1 $ ，所以龙 $ 1 $ 的条件满足
- $ i = 2 $ : 龙 $ 2 $ 的朋友是龙 $ 1, 3 $  $ \operatorname{mex}(a_1, a_3) = \operatorname{mex}(0, 1) = 2 = a_2 $ 
- $ i = 3 $ : 龙 $ 3 $ 的朋友是龙 $ 1, 2, 4 $  $ \operatorname{mex}(a_1, a_2, a_4) = \operatorname{mex}(0, 2, 0) = 1 = a_3 $ 
- $ i = 4 $ : 龙 $ 4 $ 的朋友是龙 $ 3, 5 $  $ \operatorname{mex}(a_3, a_5) = \operatorname{mex}(1, 1) = 0 = a_4 $ 
- $ i = 5 $ : 龙 $ 5 $ 的朋友是龙 $ 1, 4 $  $ \operatorname{mex}(a_1, a_4) = \operatorname{mex}(0, 0) = 1 = a_5 $

## 样例 #1

### 输入

```
7
5 1 3
4 2 4
6 3 5
7 3 6
3 2 3
5 1 5
6 2 5```

### 输出

```
0 2 1 0 1
1 2 1 0
1 2 0 1 2 0
0 1 2 0 1 0 1
2 0 1
1 0 2 1 0
0 1 2 0 2 1```

# 题解

## 作者：Misaka屮Mikoto (赞：14)

# CF2049C MEX Cycle
### 解题思路
#### 我们先考虑只有一个环的情况：
当环的长度为偶数时：我们发现只要 $0,1$ 交替就可以构造。
![](https://cdn.luogu.com.cn/upload/image_hosting/kw5u3nq4.png)

当环的长度为奇数时：我们发现只要先随意指定一个节点为 $2$ ，剩下的节点 $0,1$ 交替即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/xg64tnhw.png)

#### 接下来我们观察题目
我们以 $n=7,x=3,y=6$ 为例，
可以得到这样一个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/lbyydra2.png)

我们能够把这个图拆分成两个环：
![](https://cdn.luogu.com.cn/upload/image_hosting/8p2cmeaj.png)
将重合部分的 $id=3,id=6$ 的环分别赋值为 $1,0$ 其余的部分按照上面所说的方法构造即可。

---

## 作者：zhangzirui66 (赞：2)

做过最有意思的构造题。

假设没有 $x$ 和 $y$ 影响思维，这道题就变得比较好做。

- 偶数，则以 $n = 6$ 为例，可以构造如下：
```
0 1 0 1 0 1
```
容易发现是 $0,1,0,1\dots$ 如此循环

- 奇数类似，循环后加一个 $2$，刚好满足，以 $n = 7$ 为例：
```
0 1 0 1 0 1 2
```

难点在于 $x,y$，但不用慌，找一下规律。

## 奇数
- 如果 $a_x$ 和 $a_y$ 目前都是 $0$ 或 $1$，并且 $x$ 与 $n$ 相邻（$y$ 也可以，下文同），即为 $1$ 或 $n - 1$，交换 $a_x$ 和 $a_n$ 即可。
- 否则 $a_x$ 设为 $2$。

## 偶数
类似，但由于没有元素 $2$，无需判断，只要 $a_x$ 和 $a_y$ 目前都是 $0$ 或 $1$，就将 $a_x$ 设为 $2$。

上述东西都很好理解，拿出草稿纸举个例子就能明白。

给出代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, x, y, a[200005];
int main(){
    cin >> t;
    while(t --){
        cin >> n >> x >> y;
        if(n & 1){
            for(int i = 2; i <= n; i += 2) a[i - 1] = 0, a[i] = 1; a[n] = 2;
            if(a[x] == 0 && a[y] == 0){
                if(x == n - 1 || x == 1) swap(a[x], a[n]);
                else a[x] = 2;
            }
            if(a[x] == 1 && a[y] == 1){
                if(x == n - 1 || x == 1) swap(a[x], a[n]);
                else a[x] = 2;
            }
        }
        else{
            for(int i = 1; i <= n; i += 2) a[i] = 0, a[i + 1] = 1;
            if(a[x] == 0 && a[y] == 0){
                a[x] = 2;
            }
            if(a[x] == 1 && a[y] == 1){
                a[x] = 2;
            }
        }
        for(int i = 1; i <= n; i ++) cout << a[i] << " ";
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：Ambrose0321 (赞：1)

思路：
---

**先不考虑 x 和 y**，很明显当有偶数条龙时答案是 $0$ 和 $1$ 循环，奇数条时答案只需要增加一个 $2$ 即可。

**接下来考虑 x 和 y**，记编号为 $i$ 的龙答案为 $c_i$，那么如果 $c_x \ne c_y$，答案就和之前是一样的。否则，$c_x = c_y$，如果 $x$ 和 $n$ 相邻（$x = 1$）且 $n$ 是奇数，就交换 $c_x$ 和 $c_n$。否则直接将 $c_x$ 变成 $2$ 即可。


AC code:
---


```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int N = 200001;
int _, n, x, y, t, c[N], f[N];
bool cnt;
int main() {
	scanf("%d", &_);
	for (; _--; ) {
		scanf("%d%d%d", &n, &x, &y);
		for (int i = 1; i <= n; i++)
			c[i] = 0;
		c[1] = 0;
		for (int i = 2; i < n; i++)
			c[i] = c[i - 1] ^ 1;
		c[n] = (n & 1) + 1;
		if (c[x] == c[y]) {
			if (x == 1 && n & 1)
				swap(c[x], c[n]);
			else
				c[x] = 2;
		}
		for (int i = 1; i <= n; i++)
			printf("%d ", c[i]);
		puts("");
	}
}
```
希望能过审 qwq。

---

## 作者：Sakura_Emilia (赞：1)

# Solution

一道分类讨论的构造题。题目要求对于每一个位置，都是相对于它所有朋友的 MEX。最直接的想法就是分类讨论。

对总的人数 $n$ 以及特殊的 $x$ 和 $y$ 的差值的奇偶性进行分类讨论。

通过样例可以观察到这样的一个特点：只需要 $0$、$1$、$2$ 这三个数字就足以构造。

当 $n$ 为偶数时，可以构造一个由 $0$、$1$ 交替所形成的环。如果此时 $x$ 和 $y$ 的差值刚好是奇数，也就是这对特殊的链接两端刚好是不同数字，不会对原本的构造方案产生影响；

当 $n$ 为偶数但 $x$ 和 $y$ 的差值是偶数时，这对特殊的链接两端是相同的数字，只需要让特殊链接的一端记为 $2$ 即可；

当 $n$ 为奇数时，令第一个数字为 $2$，后面的偶数个数字由 $0$、$1$ 交替。这时候的讨论就要麻烦一点了。首先特殊处理，如果特殊链接有一端为第一个点，无需特殊处理；特殊链接两端均不为第一个特殊值 $2$ 时，如果 $x$ 和 $y$ 的差值刚好是奇数，也无需特殊处理；但如果 $x$ 和 $y$ 的差值是偶数，特殊链接的两端是相同的数字，处理稍微麻烦一点。

注意到本身需要构造的是一个环，无所谓哪个点是起点。而当如果特殊链接有一端为第一个值为 $2$ 的特殊点时，处理比较容易。因此，在这种情况下，相当于旋转环，令特殊链接的端点，也就是 $x$ 点的值为 $2$，后面的就是由 $0$、$1$ 交替的环。

在代码实现上，就是以 $x$ 点为分界点，前后 $0$、$1$ 交替的规则相反。其余具体的细节参考下面的代码实现。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
#define el else
#define wl while
#define rt return
#define il inline
#define br cout << endl;
using namespace std;

int T, n, x, y, t;

il void solve() {
    cin >> n >> x >> y;
    if(n % 2 == 0) {
        if((y - x) % 2 == 1) {
            for(int i = 1; i <= n; i++)
                if(i % 2 == 0)
                    cout << 0 << ' ';
                el
                    cout << 1 << ' ';
            br
        } el {
            for(int i = 1; i <= n; i++)
                if(i == x) {
                    cout << 2 << ' ';
                } el {
                    if(i % 2 == 0)
                        cout << 0 << ' ';
                    el
                        cout << 1 << ' ';
                }
            br
        }
    } el {
        if(x == 1 or y - x == 1 or (y - x) % 2 == 1) {
            cout << 2 << ' ';
            for(int i = 2; i <= n; i++)
                if(i % 2 == 0)
                    cout << 0 << ' ';
                el
                    cout << 1 << ' ';
            br
        } el {
            if(x % 2 == 0) {
                for(int i = 1; i <= n; i++)
                    if(i == x)
                        cout << 2 << ' ';
                    el if(i < x) {
                        if(i % 2 == 0)
                            cout << 0 << ' ';
                        el
                            cout << 1 << ' ';
                    } el {
                        if(i % 2 == 1)
                            cout << 0 << ' ';
                        el
                            cout << 1 << ' ';
                    }
                br
            } el {
                for(int i = 1; i <= n; i++)
                    if(i == x)
                        cout << 2 << ' ';
                    el if(i < x) {
                        if(i % 2 == 1)
                            cout << 0 << ' ';
                        el
                            cout << 1 << ' ';
                    } el {
                        if(i % 2 == 0)
                            cout << 0 << ' ';
                        el
                            cout << 1 << ' ';
                    }
                br
            }
        }
    }
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    wl(T--)
        solve();

    rt 0;
}
```

---

## 作者：Hanggoash (赞：1)

# CF2049C 题解

关于 MEX 的构造题

## 题意

有一个 $n$ 元环，每个元素都和它的相邻元素是“朋友”。此外，额外给定一组 $x,y$，$x$ 和 $y$ 彼此也是 “朋友”。

求一种给 $n$ 个元素填数的方案，使得对于任意一个 $i\in[1,n]$，填在 $i$ 这个位置的数 $a_i$，是它所有“朋友”的数组成的集合的 MEX。

## 分析

从样例可以初步推测，我们填数用到的 $a$ 并不会很大，只需要尝试在 $0,1,2,3...$ 交替填就好了。

### 首先考虑不存在 $x,y$ 限制的情况：

#### $n$ 为偶数

这种情况很简单，不难想到随便选一个起点，一直按照 $0,1$ 交替填就行。

#### $n$ 为奇数

由于多了一个位置出来，我们发现刚刚的填数方案行不通了，这时候想一想是否能先钦定一个位置为 $2$，然后剩下没填的坑只有偶数个了，回到了偶数情况，于是我们往后按照 $0,1$ 交替填即可。

发现在最后和 $2$ 这个位置相邻的一定是一个 $1$ 和一个 $0$，是合法的，所以这种构造成立。

### 考虑  $x,y$

如果说引入 $x,y$，相当于多了一条限制，需要去思考如何小幅度地修改，使得方案合法。

#### $n$ 为偶数

如果 $a_x$ 和 $a_y$ 是不相同的，那这条多出的限制对于原来的构造实际上没有影响，所以仍然成立。

如果 $a_x$ 和 $a_y$ 相同，我们任意把其中一个修改为 $2$ 即可。修改后检查一下，发现满足条件。

#### $n$ 为奇数

首先还是有：$a_x$ 和 $a_y$ 不相同，不需要做任何修改，即使这里多了一个为 $2$ 的数。

然后如果 $a_x$ 和 $a_y$ 相同呢？这里赛时想了各种天马行空的构造，加了一堆特判，最后可能还是有 corner case 没判全，遗憾离场。

然而大可不必这样大费周折，只需要在构造的时候把 没有解决的情况 化归到 已经解决的情况上 即可。

这种情况的独特之处就在于：$2$ 这个数是独一无二的，整个问题又是建立在环的意义下，所以我们不妨把所有的数同时顺时针移动，直到 $2$ 旋转到 $x$ 或者 $y$ 的位置，这样就一定能保证 $x$ 和 $y$ 处填的数不同，那么这样的构造就是合法的了。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int T,n,x,y;
const int N=2e5+10;
int a[N];
int get(int t)
{
    return t==n?1:t+1;
}
inline void solve()
{
    cin>>n>>x>>y;
    if(n%2==0)
    {
        for(int i=1;i<=n;++i)a[i]=i%2;
        if(a[x]==a[y])a[y]=2;
    }
    else
    {
        a[x]=2;
        for(int i=get(x),w=0,cnt=1;cnt<=n-1;i=get(i),w^=1,++cnt)a[i]=w;
    }
    for(int i=1;i<=n;++i)cout<<a[i]<<" ";
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--)
    {
        solve();
    }
}
```

---

## 作者：WaterM (赞：0)

一道诈骗题。  
首先考虑没有 $x,y$。$n$ 偶数，$0,1$ 相间填；$n$ 奇数，最后一个数改为 $2$ 即可。  
再想想如果有了 $x,y$ 如何。如果 $a_x\ne a_y$，啥都不用动。否则，把 $a_x$ 改为 $2$ 即可。当然，如果 $a_x$ 与 $a_n$ 相邻，交换他俩就好。  
做完了。
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 2e5+2;
	
	int n, x, y;
	int a[N];
	
	void main() {
		scanf("%d%d%d", &n, &x, &y);
		if(n & 1) {
			for(int i = 1; i < n; ++i) a[i] = (i & 1) ^ 1;
			a[n] = 2;
			if(a[x] == a[y]) {
				if(x == n-1 || x == 1) swap(a[x], a[n]);
				else a[x] = 2;
			}
		}
		else {
			for(int i = 1; i <= n; ++i) a[i] = (i & 1) ^ 1;
			if(a[x] == a[y]) a[x] = 2;
		}
		
		for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
		puts("");
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}
```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF2049C)

## 题意

你有一个长度为 $n$ 的环，其中 $n$ 连向 $1$。还有一条额外边由 $x$ 连向 $y$。要求构造一个长度为 $n$ 的序列，使得 $a_i=\text{mex}_{(i,v)}\{a_v\}$，其中 $(i,v)$ 表示 $i$ 和 $v$ 由直接连边。

## 思路

首先考虑没有 $(x,y)$ 的情况：

- 若 $n$ 为偶数，显然可以 $0,1,0,1\dots$ 交替放，因为 $\text{mex}\{0,0\}=1,\text{mex}\{1,1\}=0$。
- 若 $n$ 为奇数，如果按照前面的思路放，则会出现一个连着的 $0,0$。考虑将第 $n$ 位的 $0$ 改为 $2$，就满足条件了。

将 $a_x,a_y$ 的原值进行分类讨论。

显然若 $a_x,a_y$ 一个是 $0$，一个是 $1$，则不需要改变。

否则如果两个数全为 $0$ 或 $1$，将其中一个修改为 $2$ 即可。

简单画图即可证明。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using DB = double;

const int kMaxN = 2e5 + 5;

int t, n, x, y, a[kMaxN], ans;

void pr(bool pr) { cout << (pr ? "YES" : "NO") << '\n'; }

int main() {
  for (cin >> t; t; t--, ans = 0) {
    cin >> n >> x >> y;
    for (int i = 1; i <= (n / 2) * 2; i++) {
      a[i] = (i & 1) ? 0 : 1;
    }
    (n & 1) && (a[n] = 2);
    if (x + 1 == y || x == 1 && y == n) {   
      for (int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
      }
      continue;
    }
    if (n & 1 ^ 1) {
      if (a[x] == 0 && a[y] == 0 || a[x] == 1 && a[y] == 1) {
        a[x] = 2;
      }
    } else {
      if (a[x] == 0 && a[y] == 0) {
        if (x == 1) {
          a[1] = 2, a[n] = 0;
        } else {
          a[x] = 2;
        }
      } else if (a[x] == 1 && a[y] == 1) {
        if (y == n - 1) {
          a[n] = 1, a[n - 1] = 2;
        } else {
          a[x] = 2;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " \n"[i == n];
    }
  }
  return 0;
}
```

---

