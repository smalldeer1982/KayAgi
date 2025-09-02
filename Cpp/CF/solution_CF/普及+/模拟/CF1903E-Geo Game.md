# Geo Game

## 题目描述

This is an interactive problem.

Theofanis and his sister are playing the following game.

They have $ n $ points in a 2D plane and a starting point $ (s_x,s_y) $ . Each player (starting from the first player) chooses one of the $ n $ points that wasn't chosen before and adds to the sum (which is initially $ 0 $ ) the square of the [Euclidean distance](https://en.wikipedia.org/wiki/Euclidean_distance) from the previous point (which is either the starting point or it was chosen by the other person) to the new point (that the current player selected).

The game ends after exactly $ n $ moves (after all the points are chosen). The first player wins if the sum is even in the end. Otherwise, the second player wins.

Theofanis is a very competitive person and he hates losing. Thus, he wants to choose whether he should play first or second. Can you show him, which player to choose, and how he should play to beat his sister?

## 说明/提示

The examples above do not necessarily showcase optimal strategies or the correct player to choose.

In the picture below, you can see the moves that each player made in the first example. The first player is red, and the second player is black.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1903E/f7249992dc1dd05fd5ad17cee8e62de0afd41f95.png)

## 样例 #1

### 输入

```
2
6
4 6
7 6
8 5
2 1
6 2
6 4
3 3

2

5

1
4
1 1
3 2
2 1
3 3
1 2


2

3```

### 输出

```
Second

4

6

3
First
1

4```

# 题解

## 作者：FFTotoro (赞：7)

设博弈过程中依次经过的点的下标为 $p_1,p_2,\ldots,p_n$，表示第 $i$ 个走到的点为 $(x_{p_i},y_{p_i})$（不包括起点）；因为我们只关心最终答案的奇偶性，所以可以将其转化一下（这里将 $(sx,sy)$ 视为 $(x_{p_0},y_{p_0})$）：

$$
\begin{aligned}
L&=\left[\sum\limits_{i=1}^n (x_{p_i}-x_{p_{i-1}})^2+(y_{p_i}-y_{p_{i-1}})^2\right]\bmod 2\\
&=\sum\limits_{i=1}^n \left[(x_{p_i}-x_{p_{i-1}})^2+(y_{p_i}-y_{p_{i-1}})^2\right]\bmod 2\\
&=\sum\limits_{i=1}^n \left[x_{p_i}-x_{p_{i-1}}+y_{p_i}-y_{p_{i-1}}\right]\bmod 2\\
&=(x_{p_n}+y_{p_n}-x_{p_0}-y_{p_0})\bmod 2
\end{aligned}
$$

可见我们只关心**起点和终点的 $x,y$ 坐标之和的奇偶性是否相同**，如果相同那么先手胜，反之亦然。

所以我们把 $n$ 个点的坐标压成 $n$ 个 $0/1$，表示该点的横纵坐标之和的奇偶性（即模 $2$ 意义下的值）。

不妨设起点的奇偶性为 $0$；令 $c_i(i\in\{0,1\})$ 为 $n$ 个 $0/1$ 中 $i$ 的出现次数：

- $c_0\ge c_1$：选择先手，每次如果有 $1$ 就拿 $1$，最后至少会剩一个 $0$（不管是自己拿还是对方拿），可以获胜；

- $c_0<c_1$：选择后手，每次有 $0$ 就拿 $0$，最后一定没有 $0$，可以获胜。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,sx,sy; cin>>n>>sx>>sy;
    int a=sx+sy&1;
    set<int> s[2];
    for(int i=0;i<n;i++){
      int x,y; cin>>x>>y;
      s[x+y&1].emplace(i+1);
    } // 存点
    auto f=[&](int x){
      if(s[x].empty())x=!x;
      cout<<*s[x].begin()<<endl;
      s[x].erase(s[x].begin());
    }; // 向交互库输出一个点
    auto g=[&](){
      int x; cin>>x;
      if(s[0].find(x)!=s[0].end())s[0].erase(x);
      else s[1].erase(x);
    }; // 从交互库读取一个点
    if(s[a].size()>=s[!a].size()){ // 先手必胜
      cout<<"First"<<endl;
      if(n&1){ // 最后是自己出
        for(int i=0;i<n-1;i++)
          if(i&1)g();
          else f(!a);
        f(a);
      }
      else{ // 最后是对方出
        for(int i=0;i<n;i++)
          if(i&1)g();
          else f(!a);
      }
    }
    else{ // 后手必胜
      cout<<"Second"<<endl;
      for(int i=0;i<n;i++)
        if(i&1)f(a);
        else g();
    }
  }
  return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：2)

这题看上去花里胡哨的其实非常简单。

本质上只需要关注每一条线段的 $\Delta x$ 和 $\Delta y$ 的奇偶性就可以了。

将所有整点按坐标 $(x,y)$ 分为两类：$x\equiv y\pmod 2$ 为第零类，否则为第一类。

注意到前后两个点类型相同的话对答案的奇偶性没有影响，否则一定会会使答案的奇偶性发生改变。

因此，**答案的奇偶性由最后一个点的类型唯一确定。**

更进一步地说，最后一个点的类型若与起点相同，则先手胜；不同，则后手胜。

因此假设我们已经分配好了先后手，那么先手为了使得自己需要的类型（与起点相同的类型）出现在最后，一定要在之前尽可能放另一类型的点；后手反之亦然。

设与起点类型相同的点个数为 $c_0$，不同的点个数为 $c_1$。

若 $c_0\geq c_1$，简单模拟归纳可得先手必胜；

否则后手必胜。选完先后手后根据以上策略模拟即可。

[for reference only.](https://codeforces.com/contest/1903/submission/235115833)

---

## 作者：AlicX (赞：1)

## Soluition 

考虑将两个点之间的距离的平方展开：$(x1-x2)^2+(y1-y2)^2=x1^2+2\times x1\times x2+x2^2+y1^2+2 \times y1 \times y2+y2^2$。

不难发现 $2 \times x1 \times x2+2 \times y1 \times y2$ 不影响奇偶性，扔掉即可。

于是影响的结果的只有 $x1^2+y1^2+x2^2+y2^2$。

考虑路途中间的点（即不是起点和终点的点）会被计算**两次**。所以第 $i$ 个点对答案实际的贡献为 $2 \times(x_i^2+y_i^2)$，也不影响奇偶性，可以忽略。

所以影响答案的点只有**起点和终点**。

不妨设 $cnt_0$ 为偶数点的数量，$cnt_1$ 为奇数点的数量，$p1$ 为先手可以走的步数，$p2$ 为后手走的步数。

起点是已知的，终点的奇偶性分情况讨论一下：

1. 起点是奇数：若是先手，则需要将偶数点走完，即判断 $cnt_0$ 是否小于 $p1$ 即可；若是后手，则需要将奇数点走完，即判断 $cnt_1$ 时候小于 $p2$ 即可。但是若 $cnt_0=p1$，就需要通过 $n$ 的奇偶性判断：若 $n$ 是偶数，显然先手走更优，因为最后一步是后手走的，而先手只需要将偶数点提前走完即可；否则后手更优，原因上同。
2. 起点是偶数：若是先手，则需要将奇数点走完，即判断 $cnt_1$ 是否小于 $p1$ 即可；若是后手，则需要将偶数点走完，即判断 $cnt_0$ 时候小于 $p2$ 即可。但是若 $cnt_1=p1$，就需要通过 $n$ 的奇偶性判断：若 $n$ 是偶数，显然先手走更优，因为最后一步是后手走的，而先手只需要将奇数点提前走完即可；否则后手更优，原因上同。

然后模拟过程输出即可。

给出分类讨论的关键代码：

```cpp
x=sx*sx+sy*sy; 
int p1=(n+1)/2,p2=n-p1,p;  
if(x&1){ 
	if(cnt[0]<p1) puts("First"),fflush(stdout),p=0,flg=true; 
	else if(cnt[1]<p2) puts("Second"),fflush(stdout),p=1,flg=false; 
	else{ 
		if(n%2==0) puts("First"),fflush(stdout),p=0,flg=true; 
		else puts("Second"),fflush(stdout),p=1,flg=false; 
	} 
} else if(x%2==0){ 
	if(cnt[1]<p1) puts("First"),fflush(stdout),p=1,flg=true; 
	else if(cnt[0]<p2) puts("Second"),fflush(stdout),p=0,flg=false; 
	else{ 
		if(n%2==0) puts("First"),fflush(stdout),p=1,flg=true; 
		else puts("Second"),fflush(stdout),p=0,flg=false; 
	} 
} 
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
在平面上有 $n$ 个整点，且另有一个点为起点，先手玩家和后手玩家依次选点，与上轮对手选的点（第一轮的话，则和起点连）连条路径。如果这 $n$ 条路径的平方和为偶数，则先手胜；否则后手胜。又是个博弈问题。
## 分析
考虑什么时候会改变答案的奇偶，显然可以根据 $x \oplus y$ 的奇偶性分组，在组内进行跳跃不会改变，只有当组间跳跃的时候才会改变。

打表观察先手什么时候必胜，其中：$u$ 是当前获胜目标为奇或偶，$v$ 是位于哪一组，$a$，$b$ 代表两组还剩多少，$st$ 代表当前答案的奇偶性。

就下来就是使劲位运算，看不懂自己模拟一下。
```cpp
int dfs(int u, int v, int a, int b, int st) {
	if (a == 0 && b == 0) return (u == st);
	if (a == 0) {
		if (v == 0) return !dfs(u ^ 1, v ^ 1, a, b - 1, st ^ 1);
		else return !dfs(u ^ 1, v, a, b - 1, st);
	}
	if (b == 0) {
		if (v == 0) return !dfs(u ^ 1, v, a - 1, b, st);
		else return !dfs(u ^ 1, v ^ 1, a - 1, b, st ^ 1);
	}
	if (v == 0) {
		if (dfs(u ^ 1, v ^ 1, a, b - 1, st ^ 1) && dfs(u ^ 1, v, a - 1, b, st)) return 0;
		return 1;
	}
	else {
		if (dfs(u ^ 1, v ^ 1, a - 1, b, st ^ 1) && dfs(u ^ 1, v, a, b - 1, st)) return 0;
		return 1;
	}
}
 
void work() {
	rep (i, 0, 20) {
		rep (j, 0, 20) {
			if (dfs(0, 0, i, j, 0)) {
				cout << i << " " << j << "\n";
			}
			// cout << i << " " << j << " " << dfs(0, 0, i, j, 0) << " " << dfs(0, 1, i, j, 0) << "\n";
		}
	}
	
}
```

根据表，发现只要先手位于的组元素数量大于等于另一组就必胜， 否则必败。

其实这时候就可以根据必胜或必败态转移了。

发现不管选择先手还是后手，只要一直跳一开始元素数量较少的那一组就行了，不明白的用手纸笔自己画一下。

```cpp
void work() {
    int n, sx, sy, st;
    cin >> n >> sx >> sy;
    if ((sx ^ sy) & 1) st = 0;
    else st = 1;
    set<int> a, b;
    rep (i, 1, n) {
    	int x, y;
    	cin >> x >> y;
    	if ((x ^ y) & 1) a.insert(i);
    	else b.insert(i);
    }
    if ((st == 0 && a.size() >= b.size()) || (st == 1 && b.size() >= a.size())) {
    	if (b.size() > a.size() || (a.size() == b.size() && st == 1)) swap(a, b);
    	cout << "First" << endl;
    	rep (i, 1, n) {
    		if (i & 1) {
    			if (b.size()) {
					cout << *prev(b.end()) << endl;
					b.erase(prev(b.end()));
				}
				else {
					cout << *prev(a.end()) << endl;
					a.erase(prev(a.end()));
				}
    		}
    		else {
    			int id;
    			cin >> id;
    			if (a.size() && a.find(id) != a.end()) {
    				a.erase(a.find(id));
    			}
    			else {
    				b.erase(b.find(id));
    			}
    		}
    	}
    } 
    else {
    	if (b.size() >= a.size()) swap(a, b);
    	cout << "Second" << endl;
    	rep (i, 1, n) {
    		if (!(i & 1)) {
    			if (b.size()) {
					cout << *prev(b.end()) << endl;
					b.erase(prev(b.end()));
				}
				else {
					cout << *prev(a.end()) << endl;
					a.erase(prev(a.end()));
				}
    		}
    		else {
    			int id;
    			cin >> id;
    			if (a.size() && a.find(id) != a.end()) {
    				a.erase(a.find(id));
    			}
    			else {
    				b.erase(b.find(id));
    			}
    		}
    	}
    }
}
```

---

## 作者：mountain_climber (赞：0)

~~学过初中数学的人都应该能做出来~~

前提芝士：

本题中两点距离公式为：

$$d(P_{1}(x_{1},y_{1}),P_{2}(x_{2},y_{2}))=\sqrt{(x_{1}-x_{2})^2+(y_{1}-y_{2})^2}$$

说白题目问的是这个：

假设我们选的点为 $a_{1},a_{2},a_{3}\ldots,a_{n+1}$，其中 $a_{1}$ 就是起始点。那么距离的平方的和就是：

$$\sum_{i=1}^{n} d(a_{i},a_{i+1})^2$$
$$\sum_{i=1}^{n} \sqrt{(x_{i}-x_{i+1})^2+(y_{i}-y_{i+1})^2}^2$$
$$\sum_{i=1}^{n} (x_{i}-x_{i+1})^2+(y_{i}-y_{i+1})^2$$

然后题目是想知道这个玩意的奇偶性，所以也就是：

$$\sum_{i=1}^{n} (x_{i}-x_{i+1})^2+(y_{i}-y_{i+1})^2 \bmod 2$$

观察发现这个的奇偶性等同于（去平方）：

$$\sum_{i=1}^{n} (x_{i}-x_{i+1})+(y_{i}-y_{i+1}) \bmod 2$$
$$\sum_{i=1}^{n} (x_{i}+y_{i})-(x_{i+1}+y_{i+1}) \bmod 2$$
$$(x_{1}+y_{1})-(x_{n+1}+y_{n+1}) \bmod 2$$

因为 $(x_{1}+y_{1})$ 是已知的，所以我们只需要考虑 $(x_{n+1}+y_{n+1})$ 的奇偶性即可。

如果 $(x_{n+1}+y_{n+1})$ 与 $(x_{1}+y_{1})$ 奇偶性相同则先手胜，否则后手胜。

设 $(x_{1}+y_{1})$ 奇偶性为 $P$，也就是说只要先手最后取到奇偶性为 $P$ 的点就赢，后手反之。

再考虑设，奇偶性为 $P$ 的可选点有 $c_{1}$ 个，不为 $P$ 的可选点有 $c_{2}$ 个。

思考一下发现：

当 $c_{1}\geq c_{2}$ 时，先手必胜，只要一直取奇偶性不为 $P$ 的点，就可以保证后手最后取不到奇偶性不为 $P$ 的点，从而获胜。

当 $c_{1}\le c_{2}$ 时，后手必胜，只要一直取奇偶性为 $P$ 的点，就可以保证先手最后取不到奇偶性为 $P$ 的点，从而获胜。

[记录，没有代码~](https://www.luogu.com.cn/record/140275571)

---

