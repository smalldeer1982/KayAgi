# Cutting Game

## 题目描述

Alice and Bob were playing a game again. They have a grid of size $ a \times b $ ( $ 1 \le a, b \le 10^9 $ ), on which there are $ n $ chips, with at most one chip in each cell. The cell at the intersection of the $ x $ -th row and the $ y $ -th column has coordinates $ (x, y) $ .

Alice made the first move, and the players took turns. On each move, a player could cut several (but not all) rows or columns from the beginning or end of the remaining grid and earn a point for each chip that was on the cut part of the grid. Each move can be described by the character 'U', 'D', 'L', or 'R' and an integer $ k $ :

- If the character is 'U', then the first $ k $ remaining rows will be cut;
- If the character is 'D', then the last $ k $ remaining rows will be cut;
- If the character is 'L', then the first $ k $ remaining columns will be cut;
- If the character is 'R', then the last $ k $ remaining columns will be cut.

Based on the initial state of the grid and the players' moves, determine the number of points earned by Alice and Bob, respectively.

## 说明/提示

Below is the game from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974F/9f1554443f39a3c1eca0a96dffd50920759ede0a.png)On her turn, Alice cut $ 2 $ rows from the bottom and scored $ 2 $ points, then Bob cut $ 1 $ column from the right and scored one point. Note that if Bob had cut $ 1 $ row from the bottom, he would have also scored $ 1 $ point.

## 样例 #1

### 输入

```
6
4 4 3 2
4 1
3 3
2 4
D 2
R 1
4 4 3 3
4 1
3 2
2 3
D 1
L 1
U 2
3 5 3 2
1 3
2 2
3 3
R 2
R 2
6 4 4 2
1 4
2 3
5 3
1 1
R 1
U 1
9 3 2 1
6 1
3 3
D 8
10 10 2 5
7 5
9 1
R 1
L 2
D 1
U 4
D 1```

### 输出

```
2 1
2 0
0 3
1 1
2 0
0 1```

# 题解

## 作者：MrPython (赞：7)

大家好，我是 STL 带师。

按行和列维护两个 map 套 set。

剪掉某个部分时，在对应 map 中二分出要删除的区间。遍历即将删除的内容，在另一个 map 中同步删除。

```cpp
#include <bits/extc++.h>
using namespace std;
namespace pbds = __gnu_pbds;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    size_t T;
    cin >> T;
    while (T--) {
        ui xh, yh, xl = 1, yl = 1;
        size_t n, m;
        cin >> xh >> yh >> n >> m;
        map<ui, set<ui>> xp, yp;
        while (n--) {
            size_t x, y;
            cin >> x >> y;
            xp[x].emplace(y), yp[y].emplace(x);
        }
        ui sum1 = 0, sum2 = 0;
        for (bool b = 1; m; b = !b, --m) {
            char c;
            ui k;
            cin >> c >> k;
            ui ans = 0;
            if (c == 'D')
                for (auto it = xp.upper_bound(xh -= k); it != xp.end(); it = xp.erase(it))
                    for (auto j : it->second)
                        yp[j].erase(it->first), ++ans;
            else if (c == 'U') {
                auto et = xp.lower_bound(xl += k);
                for (auto it = xp.begin(); it != et; it = xp.erase(it))
                    for (auto j : it->second)
                        yp[j].erase(it->first), ++ans;
            } else if (c == 'R')
                for (auto it = yp.upper_bound(yh -= k); it != yp.end(); it = yp.erase(it))
                    for (auto j : it->second)
                        xp[j].erase(it->first), ++ans;
            else if (c == 'L') {
                auto et = yp.lower_bound(yl += k);
                for (auto it = yp.begin(); it != et; it = yp.erase(it))
                    for (auto j : it->second)
                        xp[j].erase(it->first), ++ans;
            }
            (b ? sum1 : sum2) += ans;
        }
        cout << sum1 << ' ' << sum2 << '\n';
    }
    return 0;
}
```

---

## 作者：Louis_lxy (赞：3)

维护两个数组，一个存按横坐标排序的，一个存纵坐标排序的。我们用双指针维护一下此时剩下的点的头和尾，每次删除找到对应的数组删除头部或尾部的一串即可，注意有可能会在一个数组中删除了，但是另一个会再次删除，此时不能计入总数。

AC 记录：https://www.luogu.com.cn/record/168649659

---

## 作者：DrAlfred (赞：3)

摘要：双指针，二分，数据结构

[传送门：https://www.luogu.com.cn/problem/CF1974F](https://www.luogu.com.cn/problem/CF1974F)

好题。

## 题意

给定一个 $a \times b$ 的网格，上面有 $n$ 个位置两两不同的棋子。有两个人轮流进行 $m$ 次操作。每个操作分为四种类型：

- `U k` 删除当前棋盘最上面 $k$ 行；
- `D k` 删除当前棋盘最下面 $k$ 行；
- `L k` 删除当前棋盘最左面 $k$ 列；
- `R k` 删除当前棋盘最右面 $k$ 列。

保证每次操作后，棋盘不会被删除完。每次操作之后玩家获得的分数为删除的区域中棋子的个数，问最终两人的得分。

## 分析思路

注意到 $a, b$ 很大，但是最终我们最多删除的棋子只有 $n$ 个。考虑在不劣于 $O\left(n \log n\right)$ 的时间复杂度内解决此问题。

很容易地，我们可以维护四个变量 $rl, rr, cl, cr$，分别表示当前行的上下界，列的上下界。我们以 `U` 操作为例，将问题拆分成两个子问题来解决。

我们可以发现 `U k` 操作删除的行的范围为 $[rl, rl + k)$，下文所说的 `删除范围` 即指这一范围。下文所说的 `有效行` 指有棋子的行。

### I. 找到在删除范围内的有效行有哪些

注意到本质不同的有效行不超过 $n$ 个，考虑在这一点上做文章。

我们可以维护有序队列 $rows$，表示现在还存在于棋盘上的有效行有哪些。初始我们可以用 $O\left(n \log n\right)$ 的时间复杂度处理出这个队列。

对于 `U k` 操作，我们只要每次检查队首是否在删除范围内，如果是的话即取出队首进行进一步操作即可。

这一步对于**所有 $m$ 个操作**的总时间复杂度为 $O\left(n\right)$。

### II. 统计真正的删除的棋子个数

我们考虑定义 $row_i$ 表示**在第 $i$ 行上**的所有棋子的列所构成的集合。

设我们在上一部分中所取出的队首行为 $x$。我们的任务变为统计 $row_x$ 中**值**在 $[cl, cr]$ 范围内的数的个数。我们考虑二分，对于每一行，可以在 $O\left(\log n \right)$ 的时间复杂度内得到答案。最终累积答案即可。

对于 `D, L, R` 操作，类似地可以得到快速的统计方法，不再赘述。

最终的时间复杂度为 $O\left(n \log n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, a, b, n, m, x, y, k;
inline void solve(void) {
    cin >> a >> b >> n >> m;
    std::deque<int> rows, cols;
    map<int, vector<int>> row, col;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        row[x].push_back(y);
        col[y].push_back(x);
    }
    int rl = 1, rr = a, cl = 1, cr = b;
    for (auto &p : row) {
        rows.push_back(p.first);
        sort(p.second.begin(), p.second.end());
    }
    for (auto &p : col) {
        cols.push_back(p.first);
        sort(p.second.begin(), p.second.end());
    }
    // v 中值在 [l, r] 以内的有多少
    auto count = [&](vector<int> &v, int l, int r) -> int {
        if (l > r) return 0;
        auto L = lower_bound(v.begin(), v.end(), l);
        auto R = upper_bound(v.begin(), v.end(), r);
        return R - L;
    };
    char opt;
    int p1 = 0, p2 = 0;
    for (int i = 1, cur; i <= m; i++) {
        cin >> opt >> k, cur = 0;
        if (opt == 'U') {
            while (!rows.empty() && rows.front() < rl + k) {
                x = rows.front(), rows.pop_front();
                cur += count(row[x], cl, cr);
            }
            rl += k;
        } else if (opt == 'D') {
            while (!rows.empty() && rows.back() > rr - k) {
                x = rows.back(), rows.pop_back();
                cur += count(row[x], cl, cr);
            }
            rr -= k;
        } else if (opt == 'L') {
            while (!cols.empty() && cols.front() < cl + k) {
                x = cols.front(), cols.pop_front();
                cur += count(col[x], rl, rr);
            }
            cl += k;
        } else {
            while (!cols.empty() && cols.back() > cr - k) {
                x = cols.back(), cols.pop_back();
                cur += count(col[x], rl, rr);
            }
            cr -= k;
        }
        i & 1 ? p1 += cur : p2 += cur;
    }
    cout << p1 << ' ' << p2 << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：Genshin_ZFYX (赞：1)

这题哪里需要优先队列（或 set）和 map？会结构体和排序就能轻松解决。

——送给同机房的 Grow2011 和 lihongqian__int128，以及其他题解。

$a,b$ 好大，数组装不下。怎么办？我们只能从 $n,m$ 入手。分别用两个结构体数组存每个点，第一个按 $x$ 升序排序，第二个按 $y$ 升序排序。

用四个变量记录目前当前棋盘的上、下、左、右界。再用四个指针依次记录上、下、左、右删到第几个了，每次删除都将对应的指针往前/后推，如果当前棋子在棋盘上就将得分加一。

注意上指针不能超过下指针，左指针不能超过右指针。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
const int N=2e5+5;
int n,m,u,d,l,r,k1,k2,k3,k4,scr[5];
struct node{
	int x,y;
}a1[N],a2[N];
bool cmp1(node a,node b){return a.x<b.x;}
bool cmp2(node a,node b){return a.y<b.y;}
bool cunzai(int x,int y)
{
	return x>=u&&x<=d&&y>=l&&y<=r;
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;cin>>t;
    while(t--)
    {
		cin>>d>>r>>n>>m;
    	scr[0]=scr[1]=0;
    	k1=k3=1;k2=k4=n;
    	u=l=1;
    	for(int i=1;i<=n;i++)
    	{
    		cin>>a1[i].x>>a1[i].y;
    		a2[i]=a1[i];
		}
		sort(a1+1,a1+n+1,cmp1);
		sort(a2+1,a2+n+1,cmp2);
		for(int i=1;i<=m;i++)
		{
			char c;int k,cnt=0;
			cin>>c>>k;
			if(c=='U')
			{
				for(;a1[k1].x<u+k&&k1<=k2;k1++)
					if(cunzai(a1[k1].x,a1[k1].y))
						cnt++;
				u+=k;
			}
			if(c=='D')
			{
				for(;a1[k2].x>d-k&&k1<=k2;k2--)
					if(cunzai(a1[k2].x,a1[k2].y))
						cnt++;
				d-=k;
			}
			if(c=='L')
			{
				for(;a2[k3].y<l+k&&k3<=k4;k3++)
					if(cunzai(a2[k3].x,a2[k3].y))
						cnt++;
				l+=k;
			}
			if(c=='R')
			{
				for(;a2[k4].y>r-k&&k3<=k4;k4--)
					if(cunzai(a2[k4].x,a2[k4].y))
						cnt++;
				r-=k;
			}
			scr[i%2]+=cnt;
		}
		cout<<scr[1]<<" "<<scr[0]<<'\n';
	}
	return 0;
}
```

---

## 作者：Austin0116 (赞：1)

# 分析

一道模拟题。可以先将 $x_i$ 与 $y_i$ 分别以 $x_i$ 优先及 $y_i$ 优先的两个顺序分别插入到两个 set 中。当一次操作后，我们可以从两个 set 中的其中一个的头或尾寻找元素，将答案加 $1$，并将这个元素在两个集合中都删除。最后输出答案。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m,k,kk,a,b,l,r,u,d,x,y,p,sum[2];
char c;
set<pair<int,int>> s1,s2;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		s1.clear();//多测清空
		s2.clear(); 
		cin>>n>>m>>k>>kk;
		for(int i=1;i<=k;i++){
			cin>>a>>b;
			s1.insert({a,b});
			s2.insert({b,a});//分别以不同的优先级插入set中
		}
		l=u=1;
		p=sum[0]=sum[1]=0;
		r=m;
		d=n;
		while(kk--){
			cin>>c>>a;
			if(c=='U'){
				while(!s1.empty()&&(*s1.begin()).first<u+a){
					x=(*s1.begin()).first;
					y=(*s1.begin()).second;
					s1.erase({x,y});//在两个set中删除元素
					s2.erase({y,x});
					sum[p]++;//将答案加1
				}
				u+=a;//统计删除到哪了
			}
			else if(c=='D'){
				while(!s1.empty()){
					auto o=prev(s1.end());
					if((*o).first<=d-a) break;
					x=(*o).first;
					y=(*o).second;
					s1.erase({x,y});
					s2.erase({y,x});
					sum[p]++;
				}
				d-=a;
			}
			else if(c=='L'){
				while(!s2.empty()&&(*s2.begin()).first<l+a){
					x=(*s2.begin()).first;
					y=(*s2.begin()).second;
					s1.erase({y,x});
					s2.erase({x,y});
					sum[p]++;
				}
				l+=a;
			}
			else{
				while(!s2.empty()){
					auto o=prev(s2.end());
					if((*o).first<=r-a) break;
					x=(*o).first;
					y=(*o).second;
					s1.erase({y,x});
					s2.erase({x,y});
					sum[p]++;
				}
				r-=a;
			}
			p^=1;//变更操作人
		}
		cout<<sum[0]<<' '<<sum[1]<<'\n';//输出答案
	}
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：1)

以横坐标正序，横坐标倒序，纵坐标正序和纵坐标倒序分别对于所有点建立优先队列。

对于询问，这里以 `U` 操作为例，首先可以计算出新的矩形上边界，然后就可以在优先队列中得到横坐标在被截取范围内的所有点。然后，只需要判断该点的纵坐标是否在当前未被截去的纵坐标范围内即可。

笔者实现的时候用了 map 维护每个点是否被取走，实现方式是类似的。因为每个点只会被取到四次，总时间复杂度为 $O(n\log n)$。

[提交记录](https://codeforces.com/contest/1974/submission/261994710)

---

## 作者：yingjingxu_NaS2O3 (赞：0)

## 分析

核心算法：双指针。

将读入的点按照横坐标、纵坐标排序，分别存入 $ls$、$cs$ 数组中。

考虑使用四个变量维护剩余棋盘的四条边，记上界、下界、左界、右界分别为 $u$、$d$、$l$、$r$，则

- 每执行一次操作 $1$（删除上面 $k$ 行），令

$$u \gets u+k$$

- 每执行一次操作 $2$（删除下面 $k$ 行），令

$$d \gets d-k$$

- 每执行一次操作 $3$（删除左边 $k$ 行），令

$$l \gets l+k$$

- 每执行一次操作 $4$（删除右边 $k$ 行），令

$$r \gets r-k$$

分别在 $ls$、$cs$ 中查找点 $i$ 使得 $x_i \in [u,d]$ 且 $y_i \in [l,r]$。

由于轮流进行，则

$$sum_t \gets tmp$$

其中 $t=(i+1) \bmod 2$，$tmp$ 为本轮中获得的分数。

### Time limit exceeded on test 6

我们考虑使用 set 维护排序过程。

将一个点的横纵坐标组合成一个 pair，利用 set 对点集排序，则可得到如下代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,a,b,n,m;
int u,d,l,r;
set<pair<int,int> > _Ls,_Cs; // Line Set (x is priority) | Column Set (y is priority)
bool bein(const pair<int,int> &p,int pu,int pd,int pl,int pr)
{
	int x=p.first;
	int y=p.second;
	return x>=pu&&x<=pd&&y>=pl&&y<=pr;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld",&a,&b,&n,&m);
		d=a;
		r=b;
		u=l=1;
		_Ls.clear();
		_Cs.clear();
		for(int i=1;i<=n;i++)
		{
			int x,y;
			scanf("%lld%lld",&x,&y);
			_Ls.insert(make_pair(x,y)); // x is priority
			_Cs.insert(make_pair(x,y)); // y is priority
		}
		int sum[2]={0,0};
		for(int i=1;i<=m;i++)
		{
			char op;
			int k;
			cin>>op;
			scanf("%lld",&k);
			int tmp=0;
			switch(op)
			{
				case 'U':
					for(auto i:_Ls)
						if(bein(i,u,u+k-1,l,r))
							tmp++;
					u+=k;
					break;
				case 'D':
					for(auto i:_Ls)
						if(bein(i,d-k+1,d,l,r))
							tmp++;
					d-=k;
					break;
				case 'L':
					for(auto i:_Cs)
						if(bein(i,u,d,l,l+k-1))
							tmp++;
					l+=k;
					break;
				default:
					for(auto i:_Cs)
						if(bein(i,u,d,r-k+1,r))
							tmp++;
					r-=k;
					break;
			}
			sum[(i+1)%2]+=tmp;
		}
		printf("%lld %lld\n",sum[0],sum[1]);
	}
	return 0;
}
```

注意到 set 的插入、查询复杂度均为 $O(\log n)$，总时间复杂度为 $O(mn\log n)$，所以此代码无法通过本题。

### Time limit exceeded on test 7

我们注意到此处的排序并没有修改，所以可以直接排序，而不需要使用 set。

对 $cs$ 的排序以纵坐标为关键字，需要写比较函数，但是我们也可以引入 lambda 表达式。详情请见[这篇](https://www.luogu.com.cn/article/l86yn4aw)。

我们可以这样排序：

```cpp
sort(_Cs+1,_Cs+1+n,[&](pair<int,int> x,pair<int,int> y){return x.second<y.second;});
```

由此，我们可以得到如下代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,a,b,n,m;
int u,d,l,r;
pair<int,int> _Ls[200005],_Cs[200005];
bool bein(const pair<int,int> &p,int pu,int pd,int pl,int pr)
{
	int x=p.first;
	int y=p.second;
	return x>=pu&&x<=pd&&y>=pl&&y<=pr;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld",&a,&b,&n,&m);
		d=a;
		r=b;
		u=l=1;
		for(int i=1;i<=n;i++)
		{
			int x,y;
			scanf("%lld%lld",&x,&y);
			_Ls[i]=make_pair(x,y); // x is priority
			_Cs[i]=make_pair(x,y); // y is priority
		}
		sort(_Ls+1,_Ls+1+n);
		sort(_Cs+1,_Cs+1+n,[&](pair<int,int> x,pair<int,int> y){return x.second<y.second;});
		int sum[2]={0,0};
		for(int i=1;i<=m;i++)
		{
			char op;
			int k;
			cin>>op;
			scanf("%lld",&k);
			int tmp=0;
			switch(op)
			{
				case 'U':
					for(int i=1;i<=n;i++)
						if(bein(_Ls[i],u,u+k-1,l,r))
							tmp++;
					u+=k;
					break;
				case 'D':
					for(int i=1;i<=n;i++)
						if(bein(_Ls[i],d-k+1,d,l,r))
							tmp++;
					d-=k;
					break;
				case 'L':
					for(int i=1;i<=n;i++)
						if(bein(_Cs[i],u,d,l,l+k-1))
							tmp++;
					l+=k;
					break;
				default:
					for(int i=1;i<=n;i++)
						if(bein(_Cs[i],u,d,r-k+1,r))
							tmp++;
					r-=k;
					break;
			}
			sum[(i+1)%2]+=tmp;
		}
		printf("%lld %lld\n",sum[0],sum[1]);
	}
	return 0;
}
```

我们注意到每一次都需要遍历 $ls$ 或 $cs$，时间复杂度为 $O(mn)$，仍然无法通过本题。

### Accepted

不妨考虑优化遍历过程。

利用指针 $ku$、$kd$、$kl$、$kr$ 记录左右界，每次删除时将对应指针移动，遍历时只需遍历 $[ku,kd]$ 或 $[kl,kr]$，将时间复杂度优化至 $O(m+n)$，可以通过本题。

## 最终代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,a,b,n,m;
int u,d,l,r;
pair<int,int> _Ls[200005],_Cs[200005];
bool bein(const pair<int,int> &p,int pu,int pd,int pl,int pr)
{
	int x=p.first;
	int y=p.second;
	return x>=pu&&x<=pd&&y>=pl&&y<=pr;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld",&a,&b,&n,&m);
		d=a;
		r=b;
		u=l=1;
		for(int i=1;i<=n;i++)
		{
			int x,y;
			scanf("%lld%lld",&x,&y);
			_Ls[i]=make_pair(x,y); // x is priority
			_Cs[i]=make_pair(x,y); // y is priority
		}
		sort(_Ls+1,_Ls+1+n);
		sort(_Cs+1,_Cs+1+n,[&](pair<int,int> x,pair<int,int> y){return x.second<y.second;});
		int sum[2]={0,0};
		int ku=1,kd=n,kl=1,kr=n;
		for(int i=1;i<=m;i++)
		{
			char op;
			int k;
			cin>>op;
			scanf("%lld",&k);
			int tmp=0;
			switch(op)
			{
				case 'U':
					for(;_Ls[ku].first<u+k&&ku<=kd;ku++)
						if(bein(_Ls[ku],u,d,l,r))
							tmp++;
					u+=k;
					break;
				case 'D':
					for(;_Ls[kd].first>d-k&&ku<=kd;kd--)
						if(bein(_Ls[kd],u,d,l,r))
							tmp++;
					d-=k;
					break;
				case 'L':
					for(;_Cs[kl].second<l+k&&kl<=kr;kl++)
						if(bein(_Cs[kl],u,d,l,r))
							tmp++;
					l+=k;
					break;
				default:
					for(;_Cs[kr].second>r-k&&kl<=kr;kr--)
						if(bein(_Cs[kr],u,d,l,r))
							tmp++;
					r-=k;
					break;
			}
			sum[(i+1)%2]+=tmp;
		}
		printf("%lld %lld\n",sum[0],sum[1]);
	}
	return 0;
}
```

---

## 作者：lgx57 (赞：0)

纯纯搞笑题。

把每一次操作后剩下的矩阵存下来（$x$ 左右端点，$y$ 左右端点），然后对每一个棋子计算它的贡献，显然可以二分出它最后出现在哪里，那么这个棋子就算当时删矩阵的那个人，即后面一个


```cpp
const int N=2e5+5;
int x[N],y[N];
struct node{
	int lx,rx,ly,ry;
}p[N];
bool check(int id,int num){
	return x[id]<=p[num].rx&&x[id]>=p[num].lx&&y[id]<=p[num].ry&&y[id]>=p[num].ly;
}//是否在剩下的矩阵中
void sol(){
	int a,b,n,m;
	cin>>a>>b>>n>>m;
	for (int i=1;i<=n;i++) cin>>x[i]>>y[i];
	int lx=1,ly=1,rx=a,ry=b;
	for (int i=1;i<=m;i++){
		char c;
		int k;
		cin>>c>>k;
		if (c=='U') lx+=k;
		if (c=='D') rx-=k;
		if (c=='L') ly+=k;
		if (c=='R') ry-=k;
		p[i]={lx,rx,ly,ry};//存下剩下的矩阵
	}
	int ans1=0,ans2=0;
	for (int i=1;i<=n;i++){
		int L=1,R=m,Ans=-1;
		while (L<=R){
			int mid=(L+R)>>1;
			if (check(i,mid)) Ans=mid+1,/*一定要在这里 +1!!!*/L=mid+1;
			else R=mid-1;
		}
		if (Ans!=m+1){
			if (Ans&1) ans1++;
			else ans2++;
		}
	}
	cout<<ans1<<' '<<ans2<<endl;
}
```

二分时注意 $Ans$ 要 $+1$，原因上面已经解释了。

---

## 作者：liyp (赞：0)

## 题目简述
[题目传送门](https://www.luogu.com.cn/problem/CF1974F)  
~~没有给输入说明的题目真的难理解。~~

### 题意
一个 $a \times b$ 的网格上，有 $n$ 个位置不同的棋子。两个人在进行轮流操作，每次可以选择从上往下 $k$ 行、从下往上 $k$ 行、从左往右 $k$ 列或从右往左 $k$ 列进行删除，每个人的得分就是他每次操作删掉的棋子数量总和。

### 补充的输入格式
第一行输入 $T$，指数据总数。

对于每一个数据，第一行输入 $4$ 个整数 $a$，$b$，$n$，$m$，分别指网格的行、列、棋子的数量以及操作的数量。

接下来 $n$ 行，每行两个整数 $x_i$，$y_i$，指第 $i$ 个棋子的行数和列数。

接下来 $m$ 行，每行一个字符 $c_i$ 和一个整数 $k_i$，代表每次操作的类型和被操作的行或列的数量。

## 解题过程

我们可以定义一个结构体，用来记录每个棋子的行数、列数和编号。
```cpp
struct code {
	int x; //棋子所在的行数
	int y; //棋子所在的列数
	int n; //棋子的编号
};
```
然后开两个这样结构体的数组。
```cpp
code h[MAXN], l[MAXN];
```
每个棋子都会被记录进这两个数组。

我们让 $h$ 数组按照 $x$ 坐标从小到大排序，$l$ 数组按照 $y$ 坐标从小到大排序，然后维护四个指针，分别代表 $h$ 数组的开头、$h$ 数组的结尾、$l$ 数组的开头、$l$ 数组的结尾。
```cpp
hposl = 1; hposr = n;
lposl = 1; lposr = n;
```
每当输入 $U$ 指令时，$hposl$ 就开始向后移动，把这一次操作删掉的棋子踢出 $h$ 数组。

每当输入 $D$ 指令时，$hposr$ 就开始向前移动，把这一次操作删掉的棋子踢出 $h$ 数组。

每当输入 $L$ 指令时，$lposl$ 就开始向后移动，把这一次操作删掉的棋子踢出 $l$ 数组。

每当输入 $R$ 指令时，$lposr$ 就开始向前移动，把这一次操作删掉的棋子踢出 $l$ 数组。

然后每一次踢出时，都要将它加入答案。

但是这可能会造成棋子重复删除，因此我们还需要开一个状态数组 $f$，用于记录这个棋子曾经有没有被计入答案。

完成了！

## 完整代码
```cpp
#include <bits/stdc++.h>
#define LL long long
#define FR q.front()
using namespace std;
const int MAXN = 2e5 + 10;
int a[MAXN], ans1 = 0, ans2 = 0;
int f[MAXN];
struct code {
	int x; //棋子所在的行数
	int y; //棋子所在的列数
	int n; //棋子的编号
};
code h[MAXN], l[MAXN];
bool cmp1(code x, code y) {
	return x.x < y.x;
}
bool cmp2(code x, code y) {
	return x.y < y.y;
}
void score(int x) {
	if (x % 2) {
		ans1++;
	}
	else ans2++;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T;
	int a, b, n, m;
	int x, y; char c;
	cin >> T;
	while (T--) {
		memset(f, 0, sizeof(f));
		int l1 = 0, l2 = 0;
		int hs, hx, ls, lx;
		int hposl, hposr, lposl, lposr;
		cin >> a >> b >> n >> m; ans1 = 0, ans2 = 0;
		hposl = 1; hposr = n;
		lposl = 1; lposr = n;
		hs = 1, hx = a, ls = 1, lx = b;
		for (int i = 1; i <= n; i++) {
			cin >> x >> y;
			h[i].n = i;
			h[i].x = x;
			h[i].y = y;

			l[i].n = i;
			l[i].x = x;
			l[i].y = y;
		}
		sort(h + 1, h + 1 + n, cmp1);
		sort(l + 1, l + 1 + n, cmp2);
		for (int i = 1; i <= m;i++) {
			cin >> c >> x;
			if (c == 'U') {
				hs += x;
				while (hposl <= hposr) {
					if (h[hposl].x < hs) {
						if (f[h[hposl].n] == 0) {
							f[h[hposl].n] = 1;
							score(i);
						}
						hposl++;
						
					}
					else break;
				}
			}
			if (c == 'D') {
				hx -= x;
				while (hposl <= hposr) {
					if (h[hposr].x > hx) {
						if (f[h[hposr].n] == 0) {
							f[h[hposr].n] = 1;
							score(i);
						}
						hposr--;
						
					}
					else break;
				}
			}
			if (c == 'L') {
				ls += x;
				while (lposl <= lposr) {
					if (l[lposl].y < ls) {
						if (f[l[lposl].n] == 0) {
							f[l[lposl].n] = 1;
							score(i);
						}
						lposl++;
						
					}
					else break;
				}
			}
			if (c == 'R') {
				lx -= x;
				while (lposl <= lposr) {
					if (l[lposr].y > lx) {
						if (f[l[lposr].n] == 0) {
							f[l[lposr].n] = 1;
							score(i);
						}
						lposr--;
						
					}
					else break;
				}
			}
			
		}
		cout << ans1 << " " << ans2<<endl;
	}
	return 0;
}


```

---

## 作者：Grow2011 (赞：0)

# 题目大意：

有一个 $a\times b$ 的网格和 $N$ 个棋子，两个玩家轮流操作，每次删掉一个方向的 $k$ 行（列），问两个玩家删除的棋盘上分别有多少个棋子。

# 题目解析：

发现 $a,b$ 的范围奇大无比，明显不能直接模拟，只能对棋子进行操作。

我们没必要真的删棋盘，只要定义一下棋盘的左上角位置与右下角位置就可以了。

然而问题还是没解决，我们发现 $n$ 也不小，不能每个操作都遍历一遍所有棋子。

我们知道，每次操作只对一个方向有影响，我们可以考虑定义四个优先队列，分别为四个方向从前到后进行排序，每次只用取出在该队列内且在被删除的范围之内的点就行了，这样就可以把时间复杂度降到 $O(n\log n)$ 的级别了。

但这样仍旧存在问题，因为四个优先队列不能做到同时删除一个点，所以要对每个点都打上标记，遇到这个点时直接 pop 掉就行了。

# AC Code:

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int t,a,b,n,m,k,ansa,ansb,f1,f2,f3,f4,x,y;
char c;
map<pair<int,int>,bool>mp;
struct node1{//上 
	int x,y;
	bool operator<(const node1 &a)const{
		return x>a.x;
	}
}u1[200005];
priority_queue<node1>q1;
struct node2{//下 
	int x,y;
	bool operator<(const node2 &a)const{
		return x<a.x;
	}
};
priority_queue<node2>q2;
struct node3{//左 
	int x,y;
	bool operator<(const node3 &a)const{
		return y>a.y;
	}
};
priority_queue<node3>q3;
struct node4{//右 
	int x,y;
	bool operator<(const node4 &a)const{
		return y<a.y;
	}
};
priority_queue<node4>q4;
signed main(){
	cin >> t;
	while(t--){
		cin >> a >> b >> n >> m;
		mp.clear();
		while(!q1.empty())q1.pop();
		while(!q2.empty())q2.pop();
		while(!q3.empty())q3.pop();
		while(!q4.empty())q4.pop();
		ansa = ansb = 0;
		f1 = f2 = 1;
		f3 = a;
		f4 = b;
		for(int i = 1;i<=n;i++)cin >> u1[i].x >> u1[i].y;
		for(int i = 1;i<=n;i++)q1.push(u1[i]);
		for(int i = 1;i<=n;i++)q2.push({u1[i].x,u1[i].y});
		for(int i = 1;i<=n;i++)q3.push({u1[i].x,u1[i].y});
		for(int i = 1;i<=n;i++)q4.push({u1[i].x,u1[i].y});
		for(int i = 1;i<=m;i++){
			cin >> c >> k;
			if(c=='U'){
				f1+=k;
				while(!q1.empty()&&q1.top().x<f1){
					x = q1.top().x;
					y = q1.top().y;
					if(mp[{x,y}]==0){
						if(i%2)ansa++;
						else ansb++;
						mp[{x,y}] = 1;
					}
					q1.pop();
				}
			}
			if(c=='D'){
				f3-=k;
				while(!q2.empty()&&q2.top().x>f3){
					x = q2.top().x;
					y = q2.top().y;
					if(mp[{x,y}]==0){
						if(i%2)ansa++;
						else ansb++;
						mp[{x,y}] = 1;
					}
					q2.pop();
				}
			}
			if(c=='L'){
				f2+=k;
				while(!q3.empty()&&q3.top().y<f2){
					x = q3.top().x;
					y = q3.top().y;
					if(mp[{x,y}]==0){
						if(i%2)ansa++;
						else ansb++;
						mp[{x,y}] = 1;
					}
					q3.pop();
				}
			}
			if(c=='R'){
				f4-=k;
				while(!q4.empty()&&q4.top().y>f4){
					x = q4.top().x;
					y = q4.top().y;
					if(mp[{x,y}]==0){
						if(i%2)ansa++;
						else ansb++;
						mp[{x,y}] = 1;
					}
					q4.pop();
				}
			}
		}
		cout << ansa << " " << ansb << "\n";
	}
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：0)

# CF1974F Cutting Game题解

首先，想到二维前缀和，发现时空都爆了。考虑别的方法。

用四个不同排序方式堆存每个点的位置，排序方式分别为：按横坐标从小到大、按横坐标从大到小、按纵坐标从小到大、按纵坐标从大到小。

对于每次操作（下以操作 ```U``` 举例）：

维护剩余区间的上界，每次将上界下移，将按横坐标从小到大排序的堆内横坐标小于此时上界的点弹出，并记录答案。但存在一个点被多次计入答案，使用 ```map``` 记录每个点是否被删除过，若删除过，就不计入答案。

时间复杂度：$\Theta(T\times(n+m)\times\log n)$。

注意：**多测清空！！！**

代码：

```cpp
#include <bits/stdc++.h>
#define mk make_pair
using namespace std ;
int t , u , v , n , m , x , y ;
map <pair <int , int> , bool> mp , cl ;
struct node
{
	int x , y ;
	bool operator < (const node &_a) const
	{
		return x < _a.x ;
	}
} ;
priority_queue <node> b , d , cle ;
struct nodf
{
	int x , y ;
	bool operator < (const nodf &_a) const
	{
		return x > _a.x ;
	}
} ;
priority_queue <nodf> a , c , clea ;
char ch ;
void _main()
{
	a = c = clea , b = d = cle ;
	mp = cl ;
	cin >> u >> v >> n >> m ;
	while(n--)
	{
		cin >> x >> y ;
		a.push({x , y}) , b.push({x , y}) , c.push({y , x}) , d.push({y , x}) ;
	}
	int ll = 1 , lr = u , rl = 1 , rr = v ;
	int a1 = 0 , a2 = 0 ;
	for(int i = 1 ; i <= m ; i++)
	{
		int ans = 0 ;
		cin >> ch >> x ;
		if(ch == 'U')
		{
			ll += x ;
			while(!a.empty() && a.top().x < ll)
			{
				if(!mp.count(mk(a.top().x , a.top().y)) && a.top().y <= rr && a.top().y >= rl)	ans++ , mp[mk(a.top().x , a.top().y)] = 1 ;
				a.pop() ;
			}
		}
		if(ch == 'D')
		{
			lr -= x ;
			while(!b.empty() && b.top().x > lr)
			{
				if(!mp.count(mk(b.top().x , b.top().y)) && b.top().y <= rr && b.top().y >= rl)	ans++ , mp[mk(b.top().x , b.top().y)] = 1 ;
				b.pop() ;
			}
		}
		if(ch == 'L')
		{
			rl += x ;
			while(!c.empty() && c.top().x < rl)
			{
				if(!mp.count(mk(c.top().y , c.top().x)) && c.top().y <= lr && c.top().y >= ll)	ans++ , mp[mk(c.top().y , c.top().x)] = 1 ;
				c.pop() ;
			}
		}
		if(ch == 'R')
		{
			rr -= x ;
			while(!d.empty() && d.top().x > rr)
			{
				if(!mp.count(mk(d.top().y , d.top().x)) && d.top().y <= lr && d.top().y >= ll)	ans++ , mp[mk(d.top().y , d.top().x)] = 1 ;
				d.pop() ;
			}
		}
		if(i & 1)	a1 += ans ;
		else	a2 += ans ;
	}
	cout << a1 << ' ' << a2 << '\n' ;
	return ;
}
int main()
{
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	cin >> t ;
	while(t--)	_main() ;
	return 0 ;
}
```

---

