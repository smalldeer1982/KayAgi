# [ICPC 2018 WF] Triangles

## 题目描述

在你去北京的旅行中，你带了很多谜题书，其中很多都包含类似以下的挑战：在图 I.1 中可以找到多少个三角形？

![](https://cdn.luogu.com.cn/upload/image_hosting/7jipp6ud.png)

图 I.1：样例输入 2 的插图。

虽然这些谜题让你一时感兴趣，但你很快就对它们感到厌倦，转而开始思考如何用算法来解决它们。谁知道呢，也许这样的题目会在今年的比赛中出现。好吧，猜猜看？今天是你的幸运日！

## 说明/提示

时间限制：6 秒，内存限制：1024 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 3
x---x
 \ /
  x
 / \
x   x
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 10
x   x---x---x   x
     \ /   / \
  x   x---x   x   x
     / \ / \   \
x   x---x---x---x
   /   / \   \ / \
  x---x---x---x---x
```

### 输出

```
12
```

# 题解

## 作者：eipai10 (赞：6)

个人感觉不到黑。

首先，简化问题，只考虑 $\triangle$ 的数量，然后反转一下，再统计一遍。

对于一个三角形，可以把它的三边理解为从一个顶点延伸出的两个长度相等的边以及两条边另一端点的连线。

由此，再次简化问题，我们统计顶点在作为右下顶点时按上述方法能构成的三角形个数，从左到右，从上到下处理。对于每个点 $(x,y)$ 统计下列数据：

$1.L(x,y):$ 从 $(x,y)$ 往左最多能延伸多远；

$2.U(x,y):$ 从 $(x,y)$ 往左上方最多能延伸多远；

$3.D(x,y):$ 从 $(x,y)$ 往右上方最多能延伸多远。

这三个值可以快速求出。有了这三个值之后，就可以对 $(x,y)$ 进行求解了。考虑从 $(x,y)$ 延伸的两条边距离可取任意正整数 $i\in[1,min(L(x,y),U(x,y))]$ 若满足 $D(x-i,y)\geq i$ 则意味着此处有一个右下顶点为 $(x,y)$ 长为 $i$ 的三角形。

然后就 TLE 了，因为时间复杂度 $O(n^3)$ 。

考虑用 BIT 维护满足 $D(x-i,y)\geq i$ 的点的个数：

考虑点 $(x,y)$ 最多能贡献给几个点，显然 $\forall i,1\leq i\leq D(x,y)$ 
满足 
$D((x+i)-i,y)=D(x,y)\geq i$ 。所以， $(x,y)$ 对 $\forall i,x+1\leq i\leq D(x,y)$ 有一的贡献，所以插分：处理 $(x,y)$ 时，在 $(x,y)$ 加一，在 $(x+D(x,y)+1)$ 的位置减一。

怎么维护在哪里减一？
创一个 vector 数组，记录到 $(x,y)$ 之后时没有贡献的点，处理完以 $(x,y)$ 为右下顶点的三角形的贡献后，将 vector 数组里的位置减一。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T> using V = vector<T>;
using LL = long long;
const int NN = 1.2E4 + 5;
int R, C, B[NN];
void M(int k, int d){for(; k; k -= k & (-k)) B[k] += d;}
int Q(int k){
	int res = 0;
	for(; k <= (C + 1) / 2; k += k & (-k)) res += B[k];
	return res;
}
using VI = V<int>;
LL solve(V<string> &G){
	V<VI> U(2 * R, VI(2 * C)), D(U), T(2 * C);
	auto pd = [&](int a, int b){return G[a][b] != ' ';};
	LL ans = 0; 
	for(int r = 1; r < 2 * R; r += 2){
		int mx = 0;
		for(int c = pd(r, 1) ? 1 : 3, k = 1, l = 0; c < 2 * C; c += 4, ++k){
			int &u =  U[r][c], &d = D[r][c];
			u = pd(r - 1, c - 1) ? U[r - 2][c - 2] + 1 : 0,
			d = pd(r - 1, c + 1) ? D[r - 2][c + 2] + 1 : 0,
			l = pd(r, c - 1) ? l + 1 : 0, ans += Q(k - min(u, l)),
			M(k, 1), T[k + d].push_back(k), mx = max(mx, k + d);
			while(!T[k].empty()) M(T[k].back(), -1), T[k].pop_back(); 
		}
		for(int i = C / 2 + 1; i <= mx; ++i) while(!T[i].empty())
			M(T[i].back(), -1), T[i].pop_back();	
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> R >> C, cin.ignore();
	V<string> G(2 * R, string(2 * C + 2, ' '));
	for(int i = 1; i < 2 * R; ++i){
		string s;
		getline(cin, s), copy(begin(s), end(s), begin(G[i]) + 1); 
	}
	LL ans = solve(G);
	reverse(begin(G) + 1, end(G)), ans += solve(G);
	return printf("%lld", ans), 0; 
}
```


---

