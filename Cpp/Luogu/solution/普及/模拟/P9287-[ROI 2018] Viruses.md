# [ROI 2018] Viruses

## 题目背景

译自 [ROI 2018 Day1](https://neerc.ifmo.ru/school/archive/2017-2018.html) T2. [Вирусы](https://neerc.ifmo.ru/school/archive/2017-2018/ru-olymp-roi-2018-day1.pdf) ([Viruses](https://codeforces.com/gym/102147/problem/D))。

## 题目描述

现在有 $n$ 只细胞与 $n$ 个病毒，$i$ 号细胞的初始病毒的序号也为 $i$，每个细胞心中对每位病毒都有一定的易感染度。

细胞之间可以互相攻击，如果细胞甲攻击了细胞乙，且乙「对甲现在的病毒的易感染度」比「对自家病毒的易感染度」高，那么乙就会被甲的病毒感染（成为甲的病毒的细胞）。

细胞们可以任意安排攻击顺序。当且仅当没有细胞可以被任意一名病毒感染时，游戏宣告结束。

如果存在一种攻击顺序，使得病毒 $i$ 最终拥有一只或以上的细胞，那么我们则称病毒 $i$ 为「可行的病毒」。
如果对于任意一种攻击顺序，都使得病毒 $i$ 最终拥有一只或以上的细胞，那么我们则称病毒 $i$ 为「稳定的病毒」。

现在病毒们想知道，有多少个可行的病毒与稳定的病毒。

## 说明/提示

对于所有的数据，$1 \leq n \leq 500$。

| 子任务编号 | $n$ | $p$ |
| :-----------: | :-----------: | :-----------: |
| $1$ | $1 \leq n \leq 5$ | $p = 1$ |
| $2$ | $1 \leq n \leq 500$ | $p = 1$ |
| $3$ | $1 \leq n \leq 5$ | $p = 1,2$ |
| $4$ | $1 \leq n \leq 50$ | $p = 1,2$ |
| $5$ | $1 \leq n \leq 500$ | $p = 1,2$ |

## 样例 #1

### 输入

```
2
1 2
2 1
1```

### 输出

```
2
1 2```

## 样例 #2

### 输入

```
4
3 2 4 1
1 4 2 3
3 1 2 4
1 4 2 3
1```

### 输出

```
1
3```

## 样例 #3

### 输入

```
4
3 2 4 1
1 4 2 3
3 1 2 4
1 4 2 3
2```

### 输出

```
3
1 3 4```

# 题解

## 作者：2huk (赞：4)

注意到，这是一道假扮成 OI 题的语文阅读理解题。

## 题意

有 $n$ 个细胞和 $n$ 种病毒，编号均 $1 \sim n$。

每个时刻每个细胞都会感染恰好一个病毒。令当前细胞 $i$ 中感染的病毒编号为 $c_i$。最开始第 $i$ 个细胞感染的病毒是 $i$，即 $c_i = i$。

在每个细胞心目中都有对每个病毒的能力的排名。即给定一个 $n \times n$ 的矩阵 $a$，其中 $a_{i, j}$ 表示在第 $i$ 个细胞心目中，病毒 $j$ 是**第几强**的。例如若 $a_{1,1}=2,a_{1,2}=1,a_{1,3}=3$ 则表示细胞 $1$ 认为病毒 $2$ 最强，病毒 $1$ 其次，病毒 $3$ 最菜。

细胞会互相攻击。当细胞 $i$ 攻击细胞 $j$ 时，如果 $a_{j,c_i} > a_{j,c_j}$，则细胞 $j$ 将会感染病毒 $c_i$，即 $c_j \gets c_i$。即当细胞 $j$ 认为 $i$ 的病毒更强时，它会放弃自己现有的病毒，而感染更强的。

细胞们可以任意安排攻击顺序。当且仅当没有细胞可以被任意一名病毒感染时，游戏宣告结束。显然游戏的最终局面（$c_1\dots c_n$）可能不唯一。

我们定义在某个游戏的最终局面里，一个病毒是「牛的」，**这个病毒没有灭绝**，即存在至少一个细胞感染了这个病毒。

你需要解决两个问题：

- 求哪些病毒是「稳定的」。一个病毒是稳定的，当且仅当这个病毒在**所有**游戏的最终局面里都是牛的。
- 求哪些病毒是「可行的」。一个病毒是稳定的，当且仅当这个病毒在**至少一种**游戏的最终局面里是牛的。

## Part.1 「稳定的病毒」

考虑求解哪些病毒是「稳定的」。

我们断言病毒 $i$ 是「稳定的」当且仅当 $a_{i, 1} = i$，即细胞 $i$ 认为病毒 $i$ 是最强的。

我们考虑题目中描述的能够发生感染的条件：

> 当细胞 $i$ 攻击细胞 $j$ 时，……，当细胞 $j$ 认为 $i$ 的病毒更强时，它会放弃自己现有的病毒，而感染更强的。

我们知道细胞 $i$ 最开始感染的是病毒 $i$，所以细胞 $i$ 最开始感染的就是它认为的最强的病毒。而接下来的感染过程如果能够发生，就代表感染源是一种（细胞 $i$ 认为的）更强的病毒。显然这矛盾。

## Part.2 「可行的病毒」

考虑求解哪些病毒是「可行的」。

首先以 $\mathcal O(n)$ 的复杂度枚举 $i$，表示我们要**判断病毒 $i$ 是否「可行」**。

根据题目描述，如果病毒 $i$ 可行，那么当游戏结束时它一定存在于某个细胞内。不妨再以 $\mathcal O(n)$ 的复杂度枚举 $j$ 表示判断是否存在一种游戏的最终局面，使得**细胞 $j$ 感染了病毒 $i$**。如果不存在这样的 $j$ 则病毒 $i$ 不是「可行的」。

游戏结束的条件是不存在任何一对细胞可以攻击。那么如果病毒 $k$ 满足它在细胞 $i$ 心中比病毒 $j$ 要强（即 $a_{i, k} < a_{i, j}$），而且存在一个细胞 $l$（$l \ne i$） 感染了病毒 $k$，那么当前游戏是不能结束的。因为细胞 $l$ 还可以攻击细胞 $j$。

这给我们的启发是，只有在当前局面里，细胞 $i$ 心目中比病毒 $j$ 强的病毒都**灭绝**（即不存在任何一个细胞感染这个病毒）时，游戏才会在此时结束。而此时结束就满足了我们的设想：细胞 $j$ 感染了病毒 $i$。

所以我们现在要判断是否每个（在细菌 $j$ 心目中）比病毒 $i$ 强的病毒 $k$ 都存在至少一种方案灭绝。

如何把病毒 $k$ 灭绝？我们知道（在细菌 $j$ 心目中）比病毒 $i$ 弱的病毒存在是没有影响的，所以我们可以用这些病毒把病毒 $k$ 灭绝。

把病毒 $k$ 灭绝还需要满足一个条件，就是杀它的病毒（在细菌 $k$ 心目中）要比病毒 $k$ 强。因此我们把满足上个条件的病毒标记，然后枚举（在细菌 $k$ 心目中）比病毒 $k$ 强即可。

## 代码

```cpp
int n, p, a[N][N], b[N][N];
// a[i][j] 表示在细菌 i 心目中第 j 强的病毒
// b[i][j] 表示在细菌 i 心目中第 j 个病毒的排名
bool st[N];		// 把在细菌 j 心目中比病毒 i 强的病毒标记

signed main() {
	cin >> n;
	
	for (int i = 1; i <= n; ++ i )
		for (int j = 1; j <= n; ++ j ) {
			cin >> a[i][j];
			b[i][a[i][j]] = j;
		}
	
	vector<int> res;
	cin >> p;
	if (p == 1) {
		for (int i = 1; i <= n; ++ i )
			if (a[i][1] == i) res.push_back(i);
	} else {
		for (int i = 1; i <= n; ++ i ) {		// 判断病毒 i 能否活下来
			bool Alive = false;			// 判断病毒 i 能否在任意一个细菌 j 中活下来
			for (int j = 1; j <= n && !Alive; ++ j )
				if (b[j][i] <= b[j][j]) {				// 首先它要比细菌 j 中最初的病毒（病毒 j）要强，不然没机会
					memset(st, 0, sizeof st);
					
					for (int k = 1; k < b[j][i]; ++ k ) {
						st[a[j][k]] = true;		// 把在细菌 j 心目中比病毒 i 强的病毒标记
					}
					
					bool all_destroyed = true;		// 判断在细菌 j 心目中比病毒 i 强的病毒标记是否都灭绝
					for (int k = 1; k < b[j][i] && all_destroyed; ++ k ) {
						int x = a[j][k];		// 取出一个在细菌 j 心目中比病毒 i 强的病毒
						
						bool ok = false;		// 判断是否存在一个没有标记的病毒，且在细菌 x 心目中比病毒 x 强
						for (int l = 1; l < b[x][x] && !ok; ++ l )
							if (!st[a[x][l]]) ok = true;
						
						if (!ok) all_destroyed = false;
					}
					
					if (all_destroyed) Alive = true;
				}
			
			if (Alive) res.push_back(i);
		}
	}
	
	cout << res.size() << '\n';
	for (int v : res) cout << v << ' ';
	
	return 0;
}
```

---

## 作者：Y_QWQ_Y (赞：4)

个人认为，这题完全跟模拟没关系，只要充分理解题意，然后分两种情况讨论，最后再枚举即可。
### 分类讨论
1. 对于 $p$ 为 $1$ 的时候，只有不会被感染的细胞的病毒才是 $\lceil$ 稳定的病毒 $\rfloor$，所以输出所有对本身病毒易感染度最高的病毒即可。

2. 对于 $p$ 为 $2$ 的情况，我们令病毒 $i$ 攻击细胞 $j$，再枚举 $j$ 的可能病毒 $k$。对于 $k$，病毒 $k$ 必须可以感染细胞 $j$。对于所有满足条件的 $k$，记 $i$ 的易感染度最低的 $k$ 的易感染度为 $minx_{i,j}$，记 $t_i$ 为最大的 $minx_{i,x},1\le x\le n$。对于任意 ${i,j}(1\le i,j \le n)$，如果病毒 $i$ 可以感染细胞 $j$，且病毒 $j$ 的所有可感染细胞的最大易感染度低于细胞 $j$ 对病毒 $i$ 的易感染度，则病毒 $i$ 可以通过感染 $j$ 来感染所有病毒 $j$ 可以感染的细胞，那么病毒 $i$ 就是 $\lceil$ 可行的病毒 $\rfloor$。

### 代码部分

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, v[505][505], p, cnt, ans[505], f[505][505], t[505];
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n;
    //因为没有给出具体的易感染度，只有相对值，所以用 f[i][j] 记录细胞 i 对病毒 j 的易感染度优先级。
	for (int i = 1; i <= n; ++ i)for (int j = 1; j <= n; ++ j){cin >> v[i][j];f[i][v[i][j]] = j;}
	cin >> p;
    //稳定的病毒，按分类讨论中的结论统计即可。
	if (p == 1)
	{
		for (int i = 1; i <= n; ++ i)if (v[i][1] == i)ans[++ cnt] = i;
		cout << cnt << '\n';
		for (int i = 1; i <= cnt; ++ i)cout << ans[i] << ' ';
		return 0;
	}
	for (int i = 1; i <= n; ++ i)
	{
		t[i] = n;
		for (int j = 1; j <= n; ++ j)
		{
            //优先级越大易感染度越小，最小的优先级易感染度最大。
			int ma = 0;
			for (int k = 1; k <= n; ++ k)if (f[j][k] <= f[j][j] && ma < f[i][k])ma = f[i][k];
			t[i] = min (ma, t[i]);
		}
	}
	for (int i = 1; i <= n; ++ i)for (int j = 1; j <= n; ++ j)if (t[j] >= f[j][i] && f[j][i] <= f[j][j])//按分类讨论的结论判定即可
	{
		ans[++ cnt] = i;
		break;
	}
	cout << cnt << '\n';
	for (int i = 1; i <= cnt; ++ i)cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：WhisperingWillow (赞：3)

简单题。

$p = 1$ 的情况是平凡的，我们找到 $a_{i ,1} = i$ 的个数即可。

我们枚举每个病毒 $i$ 并判断其是否合法：

选择 $x$ 作为最后留下来的在哪个细胞里。

$p_{i,j}$ 表示 $i$ 细胞 $j$ 在第几个位置。

显然要把 $a_{x, j \in [1,p_{x, i})}$ 的数全部替换成其他数，我们枚举每个数 $j$，判断前 $< p_{j , j}$ 的数是否全部包含 $a_{x, j \in [1,p_{x, i})}$  即可。

```
#include<bits/stdc++.h>
using namespace std;
const int N = 500 + 88;
int l[N], r[N] , p[N] , f[N] ,id[N];
int a[N][N];
int pos[N][N]; 
signed main(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; ++ i){
		for(int j = 1; j <= n; ++ j){
			cin >> a[i][j];
			pos[i][a[i][j]] = j;
		} 
		id[i] = i;
	}
	int p;
	cin >> p;
	if(p == 1){
		vector<int> v; 
		for(int i = 1; i <= n; ++ i){
			if(a[i][1] == i) v . push_back(i);
		}
		cout << v.size() << '\n';
		for(auto i : v) cout << i << ' ';
	}
	else{
		vector<int> v; 
		vector<int> s;
		for(int i = 1; i <= n; ++ i){
			//留下来的病毒种类
			sort(id + 1, id + n + 1 , [&](int x , int y){
				return pos[x][i] < pos[y][i];
			});//retrun pos[i][] 
			bool flg = 0;
			for(int T = 1; T <= n && !flg; ++ T){
				int j = id[T];
				if(pos[j][i] > pos[j][j]) continue;
				//保证 i 能占领 j
				//遍历 j  比 i 靠前的点，这些点不能是'稳定'的。
				vector<bool> p(n + 3);
				s.clear();
				for(int l = 1; l < pos[j][i]; ++ l){
					s . push_back(a[j][l]);
					p[a[j][l]] = 1;
				} 
				bool fg = 1;
				for(auto l : s){
					int ans = 0;
					for(int t = 1; t <= pos[l][l]; ++ t){
						if(!p[a[l][t]]){
							ans = 1;
							break;
						}
						//你再怎么入侵，必须都能入侵就入侵。
						//然而是你操控的。
						//因为这样，所以你先攻陷这些细胞。
						//他们就无法攻击。
						//剩下的无论怎么攻击影响不到 j。
						//目的就达到了。 
					}
					if(!ans){
						fg = 0;
						break;
					}
				}
			//	cout << i << ' ' << j << ' '<< fg << '\n';				
				if(fg) flg = 1;
			}  //选中细胞，并判断 
			if(flg) v . push_back(i); 
		}
		cout << v.size() << '\n';
		for(auto i : v) cout << i << ' ';
	}
	return 0;
}
```

---

## 作者：Drifty (赞：3)

#### 观前贴士：本人语文水品极差，看思路时记得配合代码食用

~~话说这题面写的好糊害的某人看了好久~~


分开考虑。

- $p=1$ 时非常简单，对于病毒 $i$，当且仅当其最容易感染的细胞为第 $i$ 个细胞时，该病毒才是稳定的病毒。

  下面给出代码：
  ```cpp
  if(p==1)
  {
	  for(int i=0;i^n;i++)
		if(s[i][0]==i)ans[tot++]=i+1;
  }
  ```
- $p=2$ 时，对于任意一对病毒和细胞 $(i,j)$，如果病毒 $i$ 可以保证感染 $j$ 号细胞，那么所有能在 $j$ 号细胞里感染度比 $i$ 小的病毒都可以被别的病毒取代。

  我们考虑每个细胞最多被攻击一次的情况（除了带有病毒 $i$ 的细胞 $j$）。如果同一个细胞受到两次攻击，我们可以忽略第一次，具体证明可以自行思考~~（懒得写，其实很明显的）~~。此时总复杂度为 $O(n^4)$，还是太慢。
  
  **怎么办？**
  
  桶操作优化！
  
  这样就可以实现按照细胞 $j$ 中强度递减的顺序处理病毒了 awa。复杂度就来到了 $O(n^3)$，优雅过掉。
  
  
  下面给出代码：
  
  ```cpp
  else
    {
		for(int i=0;i^n;i++)
        {
			t[i]=n;
			for(int j=0;j^n;j++)
            {
				int cur=0;
				for(int k=0;k^n;k++)
					if(g[j][k]<=g[j][j]&&g[i][k]>cur)cur=g[i][k];
				if(cur<t[i])t[i]=cur;
			}
		}
		for(int i=0;i^n;i++)
			for(int j=0;j^n;j++)
				if(g[j][i]<=g[j][j]&&t[j]>=g[j][i]){ans[tot++]=i+1;break;}
	}
  ```



### AC 代码：~~（我知道你们都在等这个~~
```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T & ret)
{
    ret=0;int f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
    while (ch>='0'&&ch<='9') ret=ret*10+(ch^48),ch=getchar();
    ret*=f;
}
using namespace std;
#define N 514
int s[N][N],g[N][N],t[N],tot,ans[N];
int main()
{
	int n,p;
	scanf("%d",&n);
	for(int i=0;i^n;i++)
		for(int j=0;j^n;j++)
            {read(s[i][j]);s[i][j]--;g[i][s[i][j]]=j;}
	scanf("%d",&p);
	if(p==1)
    {
		for(int i=0;i^n;i++)
			if(s[i][0]==i)ans[tot++]=i+1;
	}
    else
    {
		for(int i=0;i^n;i++)
        {
			t[i]=n;
			for(int j=0;j^n;j++)
            {
				int cur=0;
				for(int k=0;k^n;k++)
					if(g[j][k]<=g[j][j]&&g[i][k]>cur)cur=g[i][k];
				if(cur<t[i])t[i]=cur;
			}
		}
		for(int i=0;i^n;i++)
			for(int j=0;j^n;j++)
				if(g[j][i]<=g[j][j]&&t[j]>=g[j][i]){ans[tot++]=i+1;break;}
	}
	printf("%d\n",tot);
	for(int i=0;i^tot;i++)printf("%d ",ans[i]);
	return 0;
}
```

  

---

## 作者：liuhl_weifang (赞：2)

如果一个病毒是稳定的，那就说明没有任何病毒能攻击它。这也就意味着在 $i$ 号细胞的心中，$i$ 号病毒的「易感染度」是最高的。转化成代码就是这样的：

```cpp
for (int i=1;i<=n;i++) if(c[i][1]==i) ok[i] = true;
```

如果一个病毒是可行的，这就比较麻烦了。考虑到每个细胞最多被感染一次（否则前几次感染就没有意义了），所以可以来分析这个“可行的”病毒最后在那个宿主上停留了下来。

假设“可行的”病毒 $i$ 在 $j$ 细胞上面停下了。由于此时游戏已经结束，所以不能存在病毒能够杀死 $i$。这意味着能杀死 $i$ 的病毒被第三者杀死了。因此暴力枚举 $i,j$，然后判断是否满足条件即可。

附上小常数 $\Theta(n^4)$ AC 代码：

```cpp
#include <bits/stdc++.h>
#define FAST ios::sync_with_stdio(false);cin.tie(0)
using namespace std;
/*
可行的 = 稳定的： 
7
1 7 4 5 3 6 2
2 6 1 5 4 7 3
5 2 6 7 1 4 3
1 4 6 7 5 3 2
5 2 1 6 7 4 3
2 3 1 4 6 7 5
1 3 6 4 5 7 2

样例： 
4
3 2 4 1
1 4 2 3
3 1 2 4
1 4 2 3

比较好的样例： 
7
6 5 7 1 4 2 3
2 4 1 5 7 3 6
2 4 6 3 7 1 5
3 1 6 2 7 4 5
1 5 6 7 4 3 2
6 3 1 2 7 4 5
1 2 4 5 7 3 6
*/
int n,p;
int c[510][510];
int r[510][510];
bool ok[510];

signed main()
{
//	freopen("virus.in","r",stdin);
//	freopen("virus.out","w",stdout);
	cin >> n;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			cin >> c[i][j];
			r[i][c[i][j]] = j;
		}
	}
	cin >> p;
	if(p==1){
		for (int i=1;i<=n;i++) if(c[i][1]==i) ok[i] = true;
	}
	else{
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++){
				//i 能否在游戏结束时感染 j？（这也意味着 i 是可行的） 
				if(r[j][i]>r[j][j]) continue;//i 本来就无法感染 j
				//i 能在游戏结束的时候感染 j，意味着 "能感染 j" 且 "能感染 i" 的病毒都被干掉了
				//这些病毒应该是 c[j][1]~c[j][r[j][i]-1] (危险阵营) 
				//它们可以被哪些病毒干掉呢？ 
				//当然是 c[j][r[j][i]]~c[j][n] 这些病毒啦！(安全阵营) 
				int N = r[j][i];
				bool flag = true;
				for (int k=1;k<=N-1;k++){
					//检查这个病毒能不能被干掉
					bool kill = false;
					int val = c[j][k];
					for (int q=N;q<=n;q++){
						if(r[val][c[j][q]]<r[val][val]){
							kill = true;
							break;
						}
					}
					if(!kill){
						flag = false;
						break;
					}
				}
				if(flag){
					ok[i] = true;
					break;
				}
			}
		}
	}
	int cnt = 0;
	for (int i=1;i<=n;i++) cnt += ok[i];
	cout << cnt << "\n";
	for (int i=1;i<=n;i++) if(ok[i]) cout << i << " ";
	return 0;
}
```

当然我们肯定不会止步于此。优化一下枚举顺序，加上 `bitset`，时间复杂度就变成了超级棒的 $\Theta(\dfrac{n^3}{w})$。

```cpp
#include <bits/stdc++.h>
#define FAST ios::sync_with_stdio(false);cin.tie(0)
using namespace std;
/*
可行的 = 稳定的： 
7
1 7 4 5 3 6 2
2 6 1 5 4 7 3
5 2 6 7 1 4 3
1 4 6 7 5 3 2
5 2 1 6 7 4 3
2 3 1 4 6 7 5
1 3 6 4 5 7 2

样例： 
4
3 2 4 1
1 4 2 3
3 1 2 4
1 4 2 3

比较好的样例： 
7
6 5 7 1 4 2 3
2 4 1 5 7 3 6
2 4 6 3 7 1 5
3 1 6 2 7 4 5
1 5 6 7 4 3 2
6 3 1 2 7 4 5
1 2 4 5 7 3 6
*/
int n,p;
int c[510][510];
int r[510][510];
bool ok[510];
bitset<510> b[510];

signed main()
{
//	freopen("virus.in","r",stdin);
//	freopen("virus.out","w",stdout);
	cin >> n;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			cin >> c[i][j];
			r[i][c[i][j]] = j;
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			//i 能否击败 j？
			if(r[j][i]<=r[j][j]) b[i][j] = 1;
		}
	}
	cin >> p;
	if(p==1){
		for (int i=1;i<=n;i++) if(c[i][1]==i) ok[i] = true;
	}
	else{
		for (int j=1;j<=n;j++){
			bitset<510> qwq;
			for (int i=n;i>=1;i--){
				qwq |= b[c[j][i]];
				if(qwq.count()==n) ok[c[j][i]] = true;
			}
		}
	}
	int cnt = 0;
	for (int i=1;i<=n;i++) cnt += ok[i];
	cout << cnt << "\n";
	for (int i=1;i<=n;i++) if(ok[i]) cout << i << " ";
	return 0;
}
```

---

## 作者：ztksc07 (赞：2)

# P9287 [ROI 2018] Viruses 题解

## 题意分析

这个题面比较抽象。

简单来说就是有 $n$ 个病毒和 $n$ 个细胞，病毒 $i$ 开始都在细胞 $j$ 里面。每个细胞都有针对每个病毒的易感染程度，病毒可以攻击其他细胞，如果目标细胞所存在病毒的对于目标细胞的易感程度小于攻击病毒对于目标细胞的易感染程度，那么目标细胞就会被攻击病毒感染。让你求有多少能在攻击中可能活下来的病毒和一定活下来的病毒。

~~感觉分析完更抽象了。~~

## 思路详解

乍一看没有思路，其实这题就是一个模拟。

### Problem 1：稳定的病毒

这个问题很简单，只要病毒 $i$ 初始所在的老家细胞 $i$ 所对应病毒 $i$ 的易感程度最高，那么这个病毒就永远不可能会被移除。

### Problem 2：可行的病毒

这个问题就比较棘手了，需要模拟。

我们让每个 $i$ 病毒攻击 $j$ 细胞，枚举 $j$ 细胞中可能存在的病毒 $k$，如果 $i$ 病毒的易感程度大于存在的 $k$ 病毒那么就可将其感染。如果病毒 $i$ 能通过感染 $k$ 的方式感染本不可以感染的细胞 $j$，那么其就是可行的病毒。

时间复杂度 $O(n^3)$，因为 $n$ 不大于 $500$，所以可以通过。

## 通过代码

```cpp
#include<iostream>
#include<cstdio> 
using namespace std;
const int maxn=510;
int n,p,cnt;
int v[maxn][maxn],f[maxn][maxn],t[maxn];
int ans[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&v[i][j]);
			f[i][v[i][j]]=j;
		}
	}
	scanf("%d",&p);
	if(p==1){
		for(int i=1;i<=n;i++){
			if(v[i][1]==i) ans[++cnt]=i;
		}
	}else{
		for(int i=1;i<=n;i++){
			t[i]=n;
			for(int j=1;j<=n;j++){
				int maxx=0;
				for(int k=1;k<=n;k++){
					if(f[j][k]<=f[j][j]) maxx=max(f[i][k],maxx); 
				}
				t[i]=min(maxx,t[i]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(f[j][i]<=f[j][j]&&t[j]>=f[j][i]){
					ans[++cnt]=i;
					break;
				}
			}
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++){
		printf("%d ",ans[i]);
	}
	return 0;
} 
```

---

## 作者：ln001 (赞：1)

建议升绿。

$a$ 即为读入数组。

对于 $p$ 为 $1$ 的情况，显然答案是有多少个 $i$ 满足 $a_{i, 1} = i$。

记 $b_i$ 为 $a_{i,j} = i$ 中的 $j$。

对于 $p$ 为 $2$ 的情况。我们枚举细胞 $x$，发现 $a_{i,1}$ 到 $a_{i,b_{i} - 1}$ 的病毒都可以入侵该细胞，且越靠前优先级越高。

题中并没有定义两个病毒的攻击，所以我们称病毒 $a$ 能攻击掉病毒 $b$ ，指 $a$ 在 $b$ 的初始细胞（编号为 $b$ 的细胞）中的优先级更高。直观的理解就是偷家了。

游戏结束的条件是没有一个细胞可以被入侵，因此如果我们想让 $y$ 病毒入侵细胞 $x$，需要让优先级更高的病毒（集合为 $T$ ）都被弄死。这个过程是具有单调性的，即如果优先级偏高的病毒都不能入侵该细胞，那优先级第的病毒更没有可能入侵成功了。所以集合 $T$ 也指已经具备通过占领 $x$ 细胞成为可行病毒的病毒。

考虑什么情况下能把他们全部弄死。设不能入侵细胞 $x$ 的病毒集合 $S$，需要满足所有 $T$ 中的病毒都能被 $S$ 中的病毒攻击。

接下来证明，前文已经说到，$T$ 集合中的病毒必须死亡。有两种方式，除了上文提到的被 $S$ 集合中的元素弄死，还可以让他们互相攻击。但这种方式是不优秀的。假设新来了一个病毒 $k$，满足只有 $T$ 集合中的元素才能杀死他，则说明对于编号为 $k$ 的细胞，$a_{k,1}$ 到 $a_{k,b_{k} - 1}$ 中的每一个元素与 $T$ 集合一一对应。前文说到可行性满足单调性，因此 $T$ 集合一定能通过一些手段全部死亡，那我们不妨让病毒 $k$ 直接呆在细胞 $k$ 中好了。根本不需要操作。

复杂度是三次方级别，有 bitset 优化，稳过。

```cpp
ll n;
ll a[N][N];
ll b[N];
ll p;
bool ok[N]; //合法
namespace sub1
{
void sov()
{
    vector<ll> ans;
    f(i, 1, n) if (b[i] == 1) ans.push_back(i);
    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << " ";
}
} // namespace sub1
bitset<N> c[N], all;
vector<ll> ans;
signed main()
{
    csf;
    cin >> n;
    f(i, 1, n)
    {
        all[i] = 1; //构造全集
        f(j, 1, n)
        {
            cin >> a[i][j];
            if (a[i][j] == i)
                b[i] = j;
            if (b[i] == 0)
            {
                c[i][a[i][j]] = 1;
            }
        }
    }
    cin >> p;
    if (p == 1)
    {
        sub1::sov();
        return 0;
    }
    f(i, 1, n) //枚举细胞
    {
        bitset<N> nd = all;
        f(j, 1, b[i])
        {
            ll k = a[i][j]; //枚举病毒
            ok[k] = 1;
            auto tmp = nd & c[k]; //能够杀死病毒k的病毒集合与未出现在前缀的病毒的交，如果仍有元素，说明存在外部势力来绞杀k，优先级低的病毒仍有占领该细胞的希望。
            if (!tmp.count())
                goto nxt;
            nd[k] = 0;
        }
    nxt:; //跳出非法情况用的
    }
    f(i, 1, n) if (ok[i]) ans.push_back(i);
    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << " ";
    return 0;
}
```

---

