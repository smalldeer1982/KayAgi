# [EGOI 2025] A String Problem / 一个弦线问题

## 题目描述

Lara 非常喜欢跳蚤市场。上周六，德国最大的跳蚤市场之一——Rheinaue-Flohmarkt 在波恩举办。Lara 一整天都在市场里闲逛、讨价还价，并买下了各种新奇的物品。她带回家中最有趣的东西是一把完全呈圆形的小型竖琴。当她准备弹奏时，发现琴弦的分布非常混乱，根本不是彼此平行的。

更具体地说，圆形琴框上均匀分布着 $2 \cdot N$ 个琴钉。每根琴弦都由两个琴钉固定，每个琴钉正好有一根琴弦连接。

Lara 对竖琴并不十分了解，但她很确定琴弦应该都平行排列。为了解决这个问题，她决定重新装配琴弦。每一步操作中，她可以将某根琴弦的一端从一个琴钉上取下，并重新连接到另一个琴钉。在操作过程中，允许多个琴弦的末端临时连接到同一个琴钉。最终，要求每个琴钉上正好有一根琴弦，并且所有 $N$ 根琴弦都平行。

下图给出了两种所有琴弦都平行的竖琴示例。

![](https://cdn.luogu.com.cn/upload/image_hosting/6rdakys8.png)

由于每次装配都非常耗时，Lara 希望用尽可能少的步骤完成。请帮她找出最少的操作步骤，并给出一种装配方案！

## 说明/提示

### 样例说明

在第一个样例中，给出了一把有五根琴弦的竖琴。第一步，将第 $4$ 根琴弦从琴钉 $8$ 取下，重新连接到 $9$；第二步，将第 $0$ 根琴弦从 $5$ 取下，连接到 $8$；最后一步，将第 $1$ 根琴弦从 $9$ 取下，连接到 $5$。此时每个琴钉上正好有一根琴弦，且所有琴弦都平行。如下图所示：

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/he01kk6p)

下图展示了样例 2、3、4 的初始竖琴状态。

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/cs6iziyp)

- 第 1 个样例满足测试组 4 和 5 的约束。
- 第 2 个样例满足测试组 1、3、4、5 的约束。
- 第 3 个样例满足测试组 2、4、5 的约束。
- 第 4 个样例满足测试组 3、4、5 的约束。

### 约束与评分

* $4 \leq N \leq 100\,000$。
* $0 \leq a_i, b_i \leq 2N - 1$。
* 所有 $a_i$ 和 $b_i$ 互不相同。

你的解答将在一组测试组上进行评测，每组包含若干测试用例。每组得分规则如下：

* 如果你的程序解决了该组所有测试用例，获得 $100\%$ 分数。
* 如果你的程序未能完全解决该组，但每个测试用例输出的 $K$ 都是最优的，则获得 $50\%$ 分数。

判断 $50\%$ 得分时，仅判定你输出的 $K$，可以只输出 $K$ 后直接退出，也可以输出一个无效的操作序列。你的程序仍需在时限内正确结束。

| 组别 | 分值 | 限制 |
| :-: | :-: | :-: |
| 1 | 14 | 对所有 $i$，第 $i$ 根琴弦固定在琴钉 $2i$ 和 $2i+1$ 上 |
| 2 | 16 | 最多只需 2 步即可完成 |
| 3 | 12 | 保证存在一种解法，使得有一根琴弦固定在琴钉 0 和 1 上 |
| 4 | 28 | $N \leq 1000$ |
| 5 | 30 | 无额外限制 |

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
5
1 5
4 9
6 3
2 7
0 8```

### 输出

```
3
4 8 9
0 5 8
1 9 5```

## 样例 #2

### 输入

```
5
0 1
3 2
4 5
6 7
9 8```

### 输出

```
4
1 3 9
4 9 3
2 5 7
3 7 5```

## 样例 #3

### 输入

```
4
1 4
6 3
5 2
7 0```

### 输出

```
2
0 4 6
1 6 4```

## 样例 #4

### 输入

```
6
3 9
7 5
10 2
0 6
1 11
8 4```

### 输出

```
6
3 6 1
4 1 2
2 2 3
0 3 4
5 4 5
1 5 6```

# 题解

## 作者：rui_er (赞：5)

我们把所有弦按照 $(a_i+b_i)\bmod(2n)$ 的值分为 $2n$ 类，则两条弦平行当且仅当它们属于同一类中。当所有弦平行时，它们的类别都相同，我们称此时 $(a_i+b_i)\bmod(2n)$ 的值为这种方案的“旋转度”。

例如，题面中的这张图，左图的“旋转度”为 $9$，右图的“旋转度”为 $5$：

![](https://cdn.luogu.com.cn/upload/image_hosting/6rdakys8.png)

只有奇数才能成为合法的“旋转度”。若“旋转度”为偶数，会出现样例四的情况，显然不存在合法的方案。

我们大胆地猜测，对于任意一种合法的“旋转度”，最少操作次数为 $(a_i+b_i)\bmod(2n)$ 与“旋转度”不同的弦的个数。我们称这些弦为“不协调弦”，其余弦为“协调弦”。

所有“不协调弦”需要经过至少一次操作才能变为“协调弦”，而合法方案中的所有弦均为“协调弦”，因此最少操作次数一定不少于“不协调弦”的个数。下面构造性地证明这个下界一定能够取到：

- 定义性质 $P$：每个位置恰好连了一条弦。显然，初始状态具有性质 $P$。
- 随意挑选一条“不协调弦”，固定一个端点不变，将另一个端点移动到其他位置，使得这条弦变为“协调弦”。
- 移动到的那个位置恰好有一条弦，且必定为“不协调弦”。这是由初始状态具有性质 $P$ 决定的。移动这个被占据的端点，使得这条弦也变为“协调弦”。
- 不断重复上一步，直到移动到的位置没有弦。此时的状态依然具有性质 $P$，且“不协调弦”的个数严格小于初始状态。
- 不断重复以上所有步骤，直到所有弦均为“协调弦”。“不协调弦”的个数一定可以在有限次重复之后减小至 $0$。容易注意到，每条“不协调弦”恰好被操作一次。

至此我们证明了这一结论，且直接按照以上步骤模拟即可给出构造方案。

我们枚举所有合法的“旋转度”，找出“不协调弦”个数最少的情况，并给出构造即可。

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

const int N = 2e5 + 5;

int n, a[N][2], bel[N], cnt[N], ok[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 0, n - 1) {
        cin >> a[i][0] >> a[i][1];
        bel[a[i][0]] = bel[a[i][1]] = i;
        ++cnt[(a[i][0] + a[i][1]) % (2 * n)];
    }
    int ans = n + 1, rem = -1;
    for(int r = 1; r <= 2 * n; r += 2) {
        if(n - cnt[r] < ans) {
            ans = n - cnt[r];
            rem = r;
        }
    }
    cout << ans << endl;
    rep(i, 0, n - 1) if((a[i][0] + a[i][1]) % (2 * n) == rem) ok[i] = 1;
    rep(i, 0, n - 1) {
        if(!ok[i]) {
            int u = i, c = 0;
            while(true) {
                int pos = (2 * n + rem - a[u][c]) % (2 * n);
                int v = bel[pos];
                cout << u << " " << a[u][c ^ 1] << " " << pos << endl;
                ok[u] = 1;
                bel[pos] = u;
                bel[a[u][c ^ 1]] = -1;
                if(v == -1) break;
                u = v;
                c = a[v][0] == pos ? 1 : 0;
            }
        }
    }
    return 0;
}
```

---

## 作者：Doraeman (赞：4)

感谢来自上一篇题解的大佬 [rui_er](https://www.luogu.com.cn/user/122461) 的指教！

## 弦的平行
观察题目给出的两个圆形示例。  
在这两个圆形中，所有共 $2N$ 个琴钉连接的 $N$ 条弦线都互相平行。

### 规律
试试在图中找找规律，可以发现：**在这个顺时针均匀编号的圆中，两条弦线的左右端点的编号（设其为第 $1$ 条弦 $a_1,b_1$，第 $2$ 条弦 $a_2,b_2$），如果满足 $(a_1+b_1)\equiv(a_2+b_2)\pmod{2N}$，且 $\big((a_1+b_1)\bmod(2N)\big)$ 为奇数，那么这两条线平行。**

注：如果 $\big((a_1+b_1)\bmod(2N)\big)$ 是偶数，就会出现自测样例 $4$ 的情况。  
简洁地说，调整后必然会存在恰好 $2$ 条弦，它们各自的两个端点相邻，这时它们各自的端点编号之和就都是奇数，那么其它的也必须是奇数（因为模 $2N$（偶数）同余）。

### 表示方法
为了方便表示，规定 $F(x,y)=(x+y)\bmod(2N)$。 

## 规律应用
此时我们可以设第 $i$ 条弦有一个“弦值” $D_i=F(a_i,b_i)$。  
我们的终极目标就是**通过移动弦的端点使所有 $D_i$ 相等（这样它们就都平行了）。**

此处用到**贪心策略**，步骤如下。

1. 求出所有 $D_i$。
2. 统计这些 $D_i$ 的出现次数。
3. 求出出现次数**最多的 $D_i$**，规定这个 $D_i$ 为“最好值”，用 $best$ 记录。
   如果出现多个 $D_i$ 出现次数相同且都是最多，那么任意选择 $1$ 个 $D_i$ 作为 $best$ 值。
4. 把其它所有 $D_i\not=best$ 的弦都进行挪动操作，使其符合 $D_i=best$。这些弦都要挪动恰好一次，**所以要最大化 $best$，这样一来挪动的弦的数量就会尽可能小，即 $K$ 尽可能小。**

### 细节：特殊判断
根据上文内容，所有 $D_i$ 最后都要被调整为奇数，所以 $best$ 也必须是奇数。  
那么，对于类似自测样例 $4$ 的情况，所有 $D_i$ 初始都是偶数，就需要特别规定 $best$ 为某个奇数（例如 $1$）。

## 求 $K$ 的值
循环检查，从 $1$ 至 $N$，如果 $D_i\not=best$，就说明这条弦需要被挪动，$K$ 增加 $1$。最后求出 $K$，输出。
### 求 $K$ 的 $50$ 分代码
注：题目的 SPJ 疑似与题面描述不符，这份代码可能被误判为 $0$ 分（这份部分分代码没有错误，因为它参与到了之后的 AC 代码中）。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;

int n, maxi;
struct Wire{
    int x, y, sum = 0, id;
}a[N];
map <int, int> p;

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i].x >> a[i].y;
        a[i].sum = (a[i].x + a[i].y) % (n*2);
        if(a[i].sum % 2) 
            p[a[i].sum]++,
            maxi = max(maxi, p[a[i].sum]);
        a[i].id = i;
    }
    
    int best;
    for(int i=0; i<n; i++)
    	if(p[a[i].sum] == maxi) 
	    best = a[i].sum;
    if(best % 2 == 0) best = 1; // 特判 

    int k = 0;
    for(int i=0; i<n; i++)
        if(a[i].sum != best) k++;
    cout << k;
}
```

## 模拟：挪弦与挪弦顺序
这部分内容，要求我们必须要找到**正确的挪弦顺序**，否则不可能 AC。

规定已知 $x$ 时，$x'$ 能使其满足 $F(x,x')=best$。  
反推可以得到 $x'=(best+2N-x)\bmod{(2N)}$。 

规定 $ok(x)=1$ 表示 $x$ 已经找到了其对应的 $x'$，$ok(x)=0$ 则表示没有找到。

以下两种顺序被验证是错误的，**但这是一种思维的过程**。~~如果各位大佬觉得浪费时间~~也可以直接跳到结论。

### 一、先看 $a$ 再看 $b$
先来考虑一种最简朴的挪动顺序：从 $1$ 到 $N$ 遍历，如果当前的 $D_i=best$，不用继续考虑。  
反之，需要考虑挪动这条弦。

先考虑 $a$，如果 $ok(a)=ok(a')=0$，就将 $a$ 和 $a'$ 连在一起，并直接考虑下一条弦。

**这种考虑顺序被证明是错误的**，可以参考第 $4$ 个自测样例。  
```
6
3 9
7 5
10 2
0 6
1 11
8 4
```
假设这组样例的 $best=1$，那么这种顺序会导致考虑编号为 $5$ 的弦（```1 11```）时出现 $ok(1)=ok(0)=1,ok(11)=ok(2)=1$ 的情况，即都已经被连过了，无法继续考虑。

以下是这种考虑顺序对应的代码（为缩短文章长度，仅展示部分代码，不含求 $K$ 部分）。
```cpp
for(int i=0; i<n; i++){
    if(a[i].sum == best)
    	continue;
        	
    // x连接y 变成 x连接xx 或 y连接yy 
    int x = a[i].x, y = a[i].y;
    int xx = (best+n*2 - x) % (n*2),
        yy = (best+n*2 - y) % (n*2);
        		
    if(!ok[xx]){ // 优先考虑：如果x连接xx可以 
        ok[x] = ok[xx] = 1;
        cout << i << ' ' << y << ' ' << xx << '\n';
    }
    else if(!ok[yy]){ // 否则如果y连接yy可以
      	ok[y] = ok[yy] = 1;
      	cout << i << ' ' << x << ' ' << yy << '\n';
    }
}
```

如果将这份代码加入求 $K$ 的部分，测试自测样例 $4$，会得到如下结果。
```
6
0 9 10
1 5 6
2 10 11
3 6 1
5 4 5
```
是的，面对编号为 $4$ 的弦出现的前文提到的矛盾情况，**我们的考虑顺序无法处理，所以没有输出**。

### 二、dfs 确定连接顺序
开头同理。

在接下来的处理中，首先进入一层 ```dfs(i)```，如果 $ok(a_i)=ok({a_i}')=0$，可以将它们更新为 $1$，即连接，并进入下一层 dfs ```dfs(i+1)```。  
如果 $i=n$，输出答案，退出。

**如果遇到刚才提到的“都被连接”的问题，再返回**（改进部分）。

显然这个写法~~是正确的~~，**但必然超时**。

以下给出 dfs 部分的代码，如果补全可以得到 $30$ 分，其余测试点会超时。
```cpp
void dfs(int i){
	if(i == n){
		for(int i=1; i<=cnt; i++)
			cout << ans[i].id << ' ' << ans[i].s1 << ' ' << ans[i].s2 << '\n';
		exit(0);
	}
	if(a[i].sum == best)
		dfs(i + 1);
		
	int x = a[i].x, 
		y = a[i].y;
		
	int tx = match(x),
		ty = match(y);
    
	if(!ok[x] && !ok[tx]){
		ok[x] = ok[tx] = 1;
		ans[++cnt].id = i, 
		ans[cnt].s1 = y, ans[cnt].s2 = tx;
		// cout << ans[cnt].id << ' ' << ans[cnt].s1 << ' ' << ans[cnt].s2 << '\n';
		dfs(i + 1);
		ok[x] = ok[tx] = 0;
		--cnt;
	}
	if(!ok[y] && !ok[ty]){
		ok[y] = ok[ty] = 1;
		ans[++cnt].id = i, 
		ans[cnt].s1 = x, ans[cnt].s2 = ty;
        // cout << ans[cnt].id << ' ' << ans[cnt].s1 << ' ' << ans[cnt].s2 << '\n';
		dfs(i + 1);
		ok[y] = ok[ty] = 0;
		--cnt;
	}
	return;
}
```

### 三、“集体考虑”（正确顺序）
在尝试了两种错误顺序之后，我们终于迎来了**正确**的部分。

我们的第 $1$ 种考虑顺序虽然无法 AC，但是可以得到 $30$ 分并通过第 $1\sim3$ 自测点，所以我们不妨来观察第 $4$ 自测点的输出，并分析其考虑顺序。
```
6
3 6 1
4 1 2
2 2 3
0 3 4
5 4 5
1 5 6
```
看这个输出，我们可以发现规律：**$2\sim (K-1)$ 行中，第 $i$ 行的第三个数等于第 $i+1$ 行的第二个数。**

注意：输出的各行顺序是可以调整的，所以我们发现的规律不一定是正确思路。  
**但这个规律也确实是一个可以尝试并且能够 AC 的代码（经尝试确认）。**

## AC 思路结论
详细解释这个顺序。

定义“集体”：如果若干条弦只需要相互交换端点位置，就可以让这些弦的 $D=best$，那么就认为这些弦时一个集体。  
显然，总共 $K$ 条 $D\not=best$ 的弦，可以被划分为至少 $1$ 个集体。

### 解释定义
我将使用自测样例解释“集体”。

自测样例 $1,3,4$ 中，所有 $K$ 根需要被挪动的弦在同一个集体。  
自测样例 $2$ 中，如果第 $0$ 根弦不动，那第 $1,4$ 根弦是同一个集体，第 $2,3$ 根弦是同一个集体。**此时出现了 $2$ 个集体**。

### 大致思路
从任意一根弦出发，如果这根弦的 $D\not=best$，就**通过挪动，将这根弦以及它的集体全部符合 $D=best$**，然后再去考虑其他集体的其他弦（如果只有 $1$ 个集体，就完成了题目全部要求；如果有多个集体，就要考虑各个集体）。

### 具体步骤
1. 首先任意考虑一根弦（设其端点为 $(a_1,a_2)$），调整 $a_1$ 这个端点，让这根弦的端点变成 $(a_2,{a_2}')$，成功。
2. **如果 ${a_2}'$ 位置原来有一根弦**（设其端点为 $({a_2}',a_3)$），调整 ${a_2}'$ 这个端点，让这根弦的端点变成 $(a_3,{a_3}')$，成功。
3. 重复第 $2$ 步，让端点为 $({a_{i-1}}',a_i)$ 的弦变成 $(a_i,{a_i}')$，让所有弦都成功。
4. 反之，对应第 $2$ 步，**如果 ${a_{i-1}}'$ 挪到的 ${a_i}'$ 位置原来没有弦**，就说明**不需要再调整 ${a_i}'$ 位置之前连接的弦了**，这个循环模拟就暂时中断了，也就是说明**这个集体都已经符合 $D=best$**。所以退出当前循环，去**寻找下一个集体**，即**回到第 $1$ 步**。

### 处理集体考虑完毕的情况
观察自测样例 $2$。
```
5
0 1
3 2
4 5
6 7
9 8
```
可以使用 $pos(i)$ 记录第 $i$ 个位置连接的弦的编号。  
$pos(i)=-1$ 表示这个位置不连接任何弦。

按照思路 $best=1\ or\ 3\ or\ 5\ or\ 7\ or\ 9$。不妨设 $best=7$。  
如果按照刚才提到的顺序，模拟其过程。  
$$
a_1 = 0, a_2 = 1\\
\therefore pos(a_1) = -1
$$
$$
{a_2}' = 6, a_3 = 7\\
\therefore pos({a_2}') = pos(a_2)\\
$$
$$
{a_3}' = 0, a_4 = 1\\
\therefore pos({a_3}') = -1
$$
最后得到：$pos({a_3}')=-1$ 说明 ${a_3}'$ 现在不连接任何弦，无需继续考虑。  
也说明**这个集体已经全部符合 $D=best$**，退出循环，**去考虑下一个集体**。对于本测试点，所有集合都考虑完毕。

现在，我们只需要**将刚才这个循环模拟、判断集体是否考虑完毕的过程编写成代码**就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;

int n, maxi, k, best, a[N][2], d[N];
map <int, int> t, pos;
map <int, bool> ok;

int match(int x){ // 已知x, 求x' 
	return (best + n*2 - x) % (n*2);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

    cin >> n;
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y;
        a[i][0] = x, a[i][1] = y;
        pos[x] = pos[y] = i; // 所在绳子的编号 
        
        d[i] = (x + y) % (n*2); 
        if(d[i] % 2) 
            t[d[i]]++,
            maxi = max(maxi, t[d[i]]);
    }
    
    for(int i=0; i<n; i++){
    	if(t[d[i]] == maxi) 
			best = d[i];
    }
	if(best % 2 == 0) best = 1;

    for(int i=0; i<n; i++)
        if(d[i] != best) k++;
        else ok[i] = 1;
    cout << k << '\n';

    // 这部分很复杂, 很重要
    for(int i=0; i<n; i++){
    	if(!ok[i]){ // 如果第i根绳子及其集体没有被考虑. 
    		 int s = i, o = 0;
    		 // 接下来一直考虑第s根绳子. 
    		 while(1){ // 集体考虑完毕时退出.
    		 	int u = a[s][o];
    		 	int v = match(u);
    		 	int s2 = pos[v]; // v原来在s2绳子上
    		 	// 第s1根绳子的非u端连到v上去.
    		 	cout << s << ' ' << a[s][o^1] << ' ' << v << '\n';
    		 	ok[s] = 1; // u所在的s绳子ok了. 
    		 	
    		 	pos[v] = s; // v点现在和u都在s上, u <-> v.
    		 	pos[a[s][o^1]] = -1; // u所在的s绳子的原端点o^1现在没有绳子.
    		 	
    		 	// v点原来没有任何绳子, 当前集体考虑完毕, 结束.
    		 	if(s2 == -1) break; 
    		 	
    		 	s = s2; // v原来在s2绳子上, 现在去继续考虑s2.
    		 	if(a[s2][0] == v) o = 1;
    		 	if(a[s2][1] == v) o = 0; // else.
			 }
		}
    }
    return 0;
}
```

---

## 作者：panxz2009 (赞：2)

挑战最唐做法。

使得题中要求成立当且仅当 $n$ 根线 $(a_i,b_i)$ 满足 $(a_i+b_i) \bmod m$ 相等，且这个值必须为奇数。那么最小操作次数即为 $n$ 减去 $(a_i+b_i) \bmod m$ 的最多出现次数 $mx$。理由是一根线不可能两头都移动，否则可以通过调整得到更优决策。

方案的构造考虑使用搜索的形式实现。从 $0$ 到 $n-1$ 遍历线，如果该线还未被确定下来，那么动它的 $a_i$，使 $a_i$ 变为 $b_i$ 在最终答案的配对点，然后再动配对点上其余线，以此类推，直到连到一个没有线连上去的点。如果碰到已被强制固定的线，说明动 $a_i$ 不合理。那么只能动 $b_i$，然后再跑一遍同理的搜索即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define PII pair <int, int>
using namespace std;
int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();} 
	while(ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
ll read_ll() {
	ll x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();} 
	while(ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
const int mod[2] = {1000000007, 998244353};
const int maxn = 1e5 + 10, maxm = 25010, md = mod[1], delta = 20000, inf = 0x3f3f3f3f;
const ll ll_inf = 1e18;
const int B = 300;
const double eps = 1e-10;
void chkmax(ll &x, ll y) {if(x < y) x = y;}
void chkmin(ll &x, ll y) {if(x > y) x = y;}
void fix(ll &x, ll y) {x += y; if(x >= md) x -= md;}
int n, buc[maxn << 1], m, bin[maxn << 1];
bool vis[maxn];
struct node {
	int a, b;
	int aa, bb;
}t[maxn];
vector <int> vec;
pair <int, int> opt[maxn];
bool dfs(int x, int op) {
	if(x == n + 1) return true;
	if(vis[x]) return false;
	vis[x] = 1;
	vec.push_back(x);
	int u, v;
	if(op == t[x].a) u = t[x].a, v = t[x].aa;
	else u = t[x].b, v = t[x].bb;
	bin[u] = n + 1;
	opt[x] = {u, v};
	if(!dfs(bin[v], v)) return false;
	bin[v] = x;
	return true;
}
void solve() {
	n = read();
	m = n << 1;
	for(int i = 0; i < n; i++) {
		t[i].a = read(), t[i].b = read();
		buc[(t[i].a + t[i].b) % m]++;
		bin[t[i].a] = bin[t[i].b] = i;
	}
	int mx = 0, k = 1;
	for(int i = 1; i < m; i += 2) {
		if(mx < buc[i]) {
			mx = buc[i];
			k = i;
		}
	}
	printf("%d\n", n - mx);
	for(int i = 0; i < n; i++) {
		t[i].aa = (k - t[i].b >= 0 ? k - t[i].b : m + k - t[i].b);
		t[i].bb = (k - t[i].a >= 0 ? k - t[i].a : m + k - t[i].a);
	}
	for(int i = 0; i < n; i++) {
		if(t[i].aa == t[i].a) continue;
		if(!vis[i]) {
			bool flg = dfs(i, t[i].a);
			if(!flg) {
				for(auto x : vec) vis[x] = 0;
				flg = dfs(i, t[i].b);
			}
		}
	}
	for(int i = 0; i < n; i++) {
		if(t[i].aa ^ t[i].a) printf("%d %d %d\n", i, opt[i].first, opt[i].second);
	}
}
signed main() {
	int T = 1;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Hughpig (赞：1)

考虑两条弦 $i$ 和 $j$ 满足什么条件才会平行。两条平行的弦可以看作一条弦的一端沿顺时针方向在圆周上移动若干单位，另一端沿逆时针方向移动相同单位。因此，两条平行的弦满足 $(a_i+b_i)\mod (2n)$ 和 $(a_j+b_j)\mod (2n)$ 相等。

我们记一条弦的方向为其 $(a_i+b_i)\mod (2n)$ 的值。平行的弦的方向都相同。因此我们可以统计每条弦的方向，然后挑某个有尽量多的弦在的方向，按这个方向调整其他弦。

因为初始时每个琴钉都只连了一根弦，因此可以考虑这样的调整策略：随便选择一根方向不对的弦，选择一端进行调整。而如果调整后的琴钉上还有其他琴弦可以继续调整，直到没有方向不对的琴弦为止。

容易发现，每条需要调整的琴弦只需要调整一次。因此总调整次数即为 $n$ 减去初始时最多的平行的琴弦数量。

对于具体的调整步骤可以用 DFS 按上述策略进行调整。

::::info[代码]
```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define up(l,r,i) for(int i=(l);i<=(r);++i)

constexpr int N=2e5+7;

ll n,m,maxpos=1,a[N],b[N],cnt[N],id[N];
bool vis[N];

void dfs(int u,int p){
	if(vis[u])return;
	vis[u]=1;
	int q=(maxpos-p+m)%m;
	cout<<u<<' '<<(p==a[u]?b[u]:a[u])<<' '<<q<<'\n';
	dfs(id[q],q==b[id[q]]?a[id[q]]:b[id[q]]);
}

int main(){
	cin>>n;m=n*2;
	up(0,n-1,i){
		cin>>a[i]>>b[i],id[a[i]]=id[b[i]]=i;
		if((a[i]+b[i])&1)++cnt[(a[i]+b[i])%m];
	}
	up(0,m-1,i)if(cnt[i]>cnt[maxpos])maxpos=i;
	cout<<n-cnt[maxpos]<<'\n';
	up(0,n-1,i)if((a[i]+b[i])%m!=maxpos)dfs(i,a[i]);
}
```
::::

---

