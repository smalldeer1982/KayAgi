# Making Towers

## 题目描述

You have a sequence of $ n $ colored blocks. The color of the $ i $ -th block is $ c_i $ , an integer between $ 1 $ and $ n $ .

You will place the blocks down in sequence on an infinite coordinate grid in the following way.

1. Initially, you place block $ 1 $ at $ (0, 0) $ .
2. For $ 2 \le i \le n $ , if the $ (i - 1) $ -th block is placed at position $ (x, y) $ , then the $ i $ -th block can be placed at one of positions $ (x + 1, y) $ , $ (x - 1, y) $ , $ (x, y + 1) $ (but not at position $ (x, y - 1) $ ), as long no previous block was placed at that position.

A tower is formed by $ s $ blocks such that they are placed at positions $ (x, y), (x, y + 1), \ldots, (x, y + s - 1) $ for some position $ (x, y) $ and integer $ s $ . The size of the tower is $ s $ , the number of blocks in it. A tower of color $ r $  is a tower such that all blocks in it have the color $ r $ .

For each color $ r $ from $ 1 $ to $ n $ , solve the following problem independently:

- Find the maximum size of a tower of color $ r $ that you can form by placing down the blocks according to the rules.

## 说明/提示

In the first test case, one of the possible ways to form a tower of color $ 1 $ and size $ 3 $ is:

- place block $ 1 $ at position $ (0, 0) $ ;
- place block $ 2 $ to the right of block $ 1 $ , at position $ (1, 0) $ ;
- place block $ 3 $ above block $ 2 $ , at position $ (1, 1) $ ;
- place block $ 4 $ to the left of block $ 3 $ , at position $ (0, 1) $ ;
- place block $ 5 $ to the left of block $ 4 $ , at position $ (-1, 1) $ ;
- place block $ 6 $ above block $ 5 $ , at position $ (-1, 2) $ ;
- place block $ 7 $ to the right of block $ 6 $ , at position $ (0, 2) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/ec98c0f164311a4ec7c2c7d82fee7c9f6eae74e7.png)The blocks at positions $ (0, 0) $ , $ (0, 1) $ , and $ (0, 2) $ all have color $ 1 $ , forming an tower of size $ 3 $ .

In the second test case, note that the following placement is not valid, since you are not allowed to place block $ 6 $ under block $ 5 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/39b20d638e1634a0778efb064f52a1e1cffbd150.png)It can be shown that it is impossible to form a tower of color $ 4 $ and size $ 3 $ .

## 样例 #1

### 输入

```
6
7
1 2 3 1 2 3 1
6
4 2 2 2 4 4
1
1
5
5 4 5 3 5
6
3 3 3 1 3 3
8
1 2 3 4 4 3 2 1```

### 输出

```
3 2 2 0 0 0 0 
0 3 0 2 0 0 
1 
0 0 1 1 1 
1 0 4 0 0 0 
2 2 2 2 0 0 0 0```

# 题解

## 作者：cachejtt (赞：6)

## 题意
给你 $n$ 个节点，每个节点有一个颜色 $c_i$，现在把一号节点放在原点位置，后一个点必须放在前一个点的左边、右边或上面，选择一个有节点的位置 $(x,y)$，在该点一直向上走，一直走到顶上的点 $(x,y+s-1)$，则定义该点“塔”的高度为 $s$。当一个塔仅由一种颜色的节点组成时，则称其为一个“单色塔”。

现在你可以按照规则任意排放这些点，求对于一种颜色，其“单色塔”的最高高度是多少？

## 思路
### 性质
考虑一个点可以放在前一个同色点上的充要条件。

可以是“上”的操作叠在其上方；

也可以是“右上左”的操作；

也可以是“右右上左左”的操作；

$\dots$

总之，可以先经过 $k$ 步向右，再向上，再经过 $k$ 步向左将其放置在前一个节点上方。

此时，由于经过了 $2\times k+1$ 步，二者的下标之差一定为奇数。

### 做法
先离线下来操作，开一个 $ans$ 数组代表每一个颜色的答案，用 $las$ 数组记录上一个该颜色的位置，那么每次读入 $c_i$ 时，只需和上一个该颜色的位置作差即可。若差为奇数，更新答案。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
int t,n,c,ans[100005],las[100005]; 
int main(){
  std::ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    memset(ans,0,sizeof(ans));
    memset(las,0,sizeof(las));
    cin>>n;
    rep(i,1,n){
      cin>>c;
      if(las[c]==0 || (i-las[c])%2==1){
        ans[c]++;
        las[c]=i;
      }
    }
    rep(i,1,n)cout<<ans[i]<<" ";
    cout<<"\n";
  }
  return 0;
}
```

---

## 作者：ExplodingKonjac (赞：5)

**[原题链接](https://www.luogu.com.cn/problem/CF1706B)**

## 题目分析

题意：你站在一个无限大的网格中，初始时在 $(0,0)$，并将 $(0,0)$ 涂上颜色 $c_1$。你要游走 $n$ 次，第 $i$ 次游走可以前往 $(x+1,y),(x-1,y),(x,y+1)$，要求目的地不能已经被涂色，并且在那个位置涂上颜色 $c_{i+1}$。一个“塔”是指 $x$ 相同，$y$ 连续的一段相同颜色格子，对于每个 $i$ 求出颜色 $i$ 的塔的可能最高高度。

题目说了各颜色独立求答案，所以只考虑一个颜色 $x$。假设我已经堆出来了一个 $x$ 颜色的塔，那么我如果想让下一个 $x$ 也堆在塔上，我只能绕一个弯再回来，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/nrdrf2yl.png)

显然，想让这个弯能恰好绕回来，充要条件是两个 $x$ 之间隔的数量为偶数，也就是说，这两个 $x$ 的位置奇偶性不同。

所以可以 dp，设 $f_{c,0/1}$ 表示当前颜色为 $c$ 的塔，最顶端的标号奇偶性为 $0/1$，所能达到的最高高度。显然可以得到转移 $f_{c,x}\gets f_{c,\lnot x}+1$，其中 $\lnot x$ 指 $x$ 取反。那么对于颜色 $i$ 的最终答案就是 $\max\{f_{i,0},f_{i,1}\}$ 了。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

int T,n,a[100005],f[100005][2];
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n;
		for(int i=1;i<=n;i++) qin>>a[i];
		for(int i=1;i<=n;i++) f[i][0]=f[i][1]=0;
		for(int i=1;i<=n;i++) f[a[i]][i&1]=max(f[a[i]][i&1],f[a[i]][!(i&1)]+1);
		for(int i=1;i<=n;i++) qout.writesp(max(f[i][0],f[i][1]));
		qout<<'\n';
	}
	return 0;
}
```


---

## 作者：Jeremiahy (赞：3)

### 题意

给定 $n$ 个方块，每个方块有一个颜色 $c_i$，第一个方块在原点，第 $i$ 个方块可放置在第 $i-1$ 个方块的左面、右面或者上面。对于每个颜色输出能建成的最高的塔（塔指一列上连续的同一颜色方块，高度即为数量）。

# 分析

首先，对于一串连续的同一颜色，自然是一直往上垒，越垒越高，通过分析样例，我们还发现一个规律：两个同一颜色方块之间间隔的方块数量是 $2$ 的倍数时，这两个方块可垒到一起。

这怎么解释呢？如果间隔 $0$ 个方块，显然成立；间隔两个方块时，我们可以在当前的基础上，在右面放一个，再在右面的上面放一个，再在右面的上面的左面放一个——这就相当于在原方块上面放了一个。依次类推，对于更大的 $2$ 的倍数，我们也可以采用这种向右垒的方法，所以这个规律是正确的。

在具体的程序实现中，因为最后输出顺序是按颜色编号，所以需要用 $ans$ 数组记录大小。我们只需要统计出一个 $last$ 数组来存该颜色上一次出现的位置，为 $0$ 说明没出现过，直接让 $ans_i$ 加 $1$ 即可，否则判断是否符合上述规律，符合就让 $ans_i$ 加 $1$。

另外，由于 $ans_i$ 能否加 $1$ 只与 $c_i$ 上一次出现的位置有关系，所以我们对于 $c$ 数组也不必开了，直接读入 $c$ 即可，节省空间（~~然鹅对于 250 MB 的空间限制来说节省 0.76 MB 并没有任何卵用~~）。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, c, ans[200010], last[200010];
signed main(){
	ios::sync_with_stdio(false);//关闭与 stdio 的同步来提速
	cin >> t;
	while (t--) {
		memset(ans, 0, sizeof(ans));
		memset(last, 0, sizeof(last));//每次注意初始化 ans 和 last
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> c;
			if (!last[c] || (i - last[c] - 1) % 2 == 0)//可以往上垒
				ans[c]++;
			last[c] = i;//记录位置
		}
		for (int i = 1; i <= n; i++)
			cout << ans[i] << ' ';
		cout << "\n";
	}
	return 0;
}

```



---

## 作者：No_Rest (赞：1)

## 题目分析

我们可以发现只要两个相同颜色的方块相差偶数个方块，那他们就可以像下~~表~~图往上垒。~~怕图崩了，所以用表 qwq~~

| - | - | - | - |
| -----------: | -----------: |  -----------: |  -----------: |
| $2n$ | $2n-1$ | $2n-2$ | $...$ |
| $1$ | $2$ | $3$ | $...$ |

证明：
假设一共有 $k$ 列，而每列有 $2$ 个数，那么一定差 $2k$ 个数。因为$2k$ 一定为偶数，所以只要两个相同颜色的方块相差偶数个方块，那他们就可以往上垒。

发现这个以后就可以轻松的写代码啦。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, x, cnt[200005], a[200005];//cnt数组记录能垒多高，a数组记录该颜色最后出现的位置
signed main(){
	scanf("%d", &t);
	while (t--){
		memset(cnt, 0, sizeof(cnt));//记得清零
		memset(a, 0, sizeof(a));
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%d", &x);//这里不用开数组
			if(!a[x] || (i - a[x] - 1) % 2 == 0){//如果已经出现过这个颜色，且距离上一个同色的差2倍（记得-1）
				cnt[x]++;//计数器加1
			}
			a[x] = i;//记录该颜色最后出现的位置
		}
		for(int i = 1; i <= n; i++){
			printf("%d ", cnt[i]);
		}
		printf("\n");//记得换行
	}
	return 0;//好习惯
}
```

---

## 作者：Locklink (赞：1)

题中说**独立地**求出每一个颜色的答案，这是一个至关重要的信息。

我们很容易发现，如果一个颜色的方块距离上一个相同颜色的方块中间相隔偶数个方块，那么它们可以接在一起。

比如 `1 2 3 4 5 6 7 1`，两个 `1` 之间隔了 $6$ 个方块，那么我们可以这样摆放：
```
1765
1234
```

如果距离上一个相同颜色的方块中间相隔了奇数个方块，将其忽略即可。

单次询问 $O(N)$ 扫一遍即可。


```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
	int T;
	cin>>T;
	while(T--){
		int n,a,ans[200000]={},x[200000]={},sum[200000]={};
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a;
			if((i-x[a])%2==1||!x[a]){
				x[a]=i;
				sum[a]++;
				ans[a]=max(ans[a],sum[a]);
			}
		}
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
}
```

---

## 作者：OIer_ACMer (赞：0)

~~为啥普及减还这么难？！~~

------------
注：本题由于主要是找规律，注重读者自己思考，所以笔者在这里不会过多解释证明和原理，望周知！

------------
## 大致思路：
这道题是一道找规律的题目，尽管它上面写着是个 DP，但是跟 DP 啥关系都没有，主要是找到是答案的情况。

首先，我们根据洛谷给出的图片可以发现：**只有当一个色块距离上一个色块的距离为奇数时，该种色块的高度才能加** $1$。例如：当距离为 $1$ 时，可以直接放在上一相同色块的上面，来满足题目要求的一横条全是一种颜色；当距离为 $3$ 时，可以左、上、右，或者右、上、左这样放置色块（至于为啥不能是偶数个距离，那是**因为题目要求只能走上、左、有三种操作，不能跨过去，因此偶数个就不行**），第三块色块就可以放在上一相同色块的上面。

具体实现我大致说一下：

1. 我们定义 $dp$ 数组为上一个访问的位置，$height$ 数组为每个色块的高度，$vis$ 数组表示是否放过该颜色，至于 $a$ 数组我不再多说。

2. 首先我们判断若该色块未被访问过，则令该色块的上一个相同色块位置为它自己，同时将初始高度赋值为 $1$。

3. 若该色块被访问过，即该色块不是第一次出现，则记录当前位置，接着判断如果该位置与上一个位置的距离为奇数，则高度加 $1$，并将 $dp[a[i]]$ 赋值为当前位置。

4. 遍历完成后将该色块标记为已访问。

5. 循环输出 $height$ 数组中存着的各个高度。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, a[100009], height[100009], dp[100009], vis[100009];
int main()
{
    int t;
    t = read();
    while (t--)
    {
        n = read();
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            height[i] = 0;
            dp[i] = 0;
            vis[i] = 0;
        }
        for (int i = 1; i <= n; i++)
        {
            if (vis[a[i]] == 0) 
            {
                dp[a[i]] = i; 
                height[a[i]] = 1;  
            }
            else 
            {
                int temp = i;                   
                if ((temp - dp[a[i]]) % 2 != 0) 
                {
                    height[a[i]]++;       
                    dp[a[i]] = temp;
                }
            }
            vis[a[i]] = 1; 
        }
        for (int i = 1; i <= n; i++) 
        {
            cout << height[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122552197)

---

## 作者：ZHANGyutao123 (赞：0)

# Making Towers题解
[传送门](https://www.luogu.com.cn/problem/CF1706B)

## 题意

给定一个序列 $\{c_n\}$，将这个序列中的数按照一定的规则放在二维平面上构造出一个图形。称其中一条由 $s$ 个颜色相同的节点组成的线段为一个颜色 $r$ 的塔。求每种颜色的塔中最长的线段长度。

## 思路

对于题目要求的塔，我们需要考虑以下两个条件：

1. 塔中的节点颜色必须全部相同。
2. 塔的所有节点都在同一条水平线上（即 $y$ 坐标相同）。

因此，我们只需统计每种颜色在平面上的分布情况，然后对于每种颜色，如何去找到存在的所有塔的长度。

首先考虑简单的暴力方法，如果我们枚举每个节点作为一条塔的起点后，依次往上寻找塔的结束位置，那么时间复杂度为 $O(n^2)$，无法通过此题。因此，我们需要寻找更加高效的算法。

题目要求我们求出每种颜色的塔中最长的线段长度，考虑一下题目的性质，如果在一条塔中存在某一个位置，使得它之前和之后的颜色都与其不同，那么这个位置就是该塔的一个断点，且在该断点左边和右边存在的最长塔长度是相等的。

因此，我们只需要遍历所有的方块，对于每种颜色，记录它最近一次出现的位置 $pos$ 和当前的距离 $dis$，如果 $dis$ 是奇数（因为塔的高度必须是偶数），那么说明该颜色的最近两个方块组成了一条新的塔，那么我们就可以更新这种颜色的最大塔高了。

## 具体实现

定义一个数组 `last_pos` 来记录每种颜色最近一次出现的位置，还需要定义一个数组 `cnt` 来统计每种颜色当前的最大塔高（即当前的塔高）。遍历每个方块时，如果这个方块还没有同色方块或者它前面的同色方块到它的距离为奇数，那么就更新该颜色的最大塔高。最后输出所有颜色的最大塔高即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 2;
int T, n, color, cnt[MAXN], last_pos[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        // 初始化数组
        memset(cnt, 0, sizeof(cnt));
        memset(last_pos, 0, sizeof(last_pos));
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> color;
            // 如果找不到同色方块或者上一个同色方块距离当前方块的距离为偶数，则更新答案
            if (!last_pos[color] || (i - last_pos[color] - 1) % 2 == 0)
                cnt[color]++;
            last_pos[color] = i; // 更新位置
        }
        for (int i = 1; i <= n; i++)
            cout << cnt[i] << ' '; // 输出最终答案
        cout << "\n";
    }
    return 0;
}
```


---

## 作者：_Only_this (赞：0)

### CF1706B Making Towers

------------

给定走路过程中每一步给脚下方格染的颜色，每一次只能往上、往左、往右走，求每个颜色能摞起的最大高度。

不懂题意的看例子：（借用一下你谷的图）

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/ec98c0f164311a4ec7c2c7d82fee7c9f6eae74e7.png)

对于红色，可摞起的最大高度为3。

这题唯一需要注意的就是关于时间复杂度的问题，此题 $1\leq n\leq10^5$，因此每次对于每个颜色来处理是不行的，$O(n^2)$ 会超时，所以要线型 $O(n)$ 处理。

根据题意，很显然，每个颜色之间的距离为奇数时才能摞成一列，因此，可以用一个数组来记录当前颜色上一次出现的位置，以此来求每段相同颜色间的距离。

注意，

因为 $1\leq t\leq 10^4$，所以每次重置数组的时候不能直接用 memset 函数，这样会直接导致超时。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int T,n;
int a[maxn],pos[maxn],ans[maxn];
void Init(){
	for(int i=1;i<=n;i++)
		ans[i]=pos[i]=0;
	return ;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		Init();
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),ans[a[i]]=1;
		for(int i=1;i<=n;i++){
			if(!pos[a[i]])	pos[a[i]]=i;
			else
				if(i-pos[a[i]]&1)
					ans[a[i]]++,pos[a[i]]=i;
		}
		for(int i=1;i<=n;i++)
			printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```

完结，散花(～￣▽￣)～

---

## 作者：Burnling (赞：0)

### 题意简述

- 你有 $n$ 块有颜色的积木。第 $i$ 块积木的颜色为 $c_i(1\leq c_i \leq n)$ 。

- 你可以按照下面的步骤在一个直角坐标系中搭积木（无视重力）：

  - 首先，将第 $1$ 块积木放在 $(0,0)$ 的位置上。
  - 对于第 $i(2\leq i \leq n)$ 块积木，它可以被放置在上一块积木的左侧、右侧或上面（只要该位置没有放过积木）。

- 一个塔是由 $s$ 个竖直摞起来的同色方块构成的，其高度为 $s$。

- 对于 $r \in [1,n]$ ，解决下面的互相独立的问题：

  找到颜色 $r$ 的方块能形成的最高的塔。

### 题目分析

既然要求颜色 $r$ 的方块能搭成的最高的塔，那就要这种颜色的积木尽可能地竖直摞在一起。

由于每种颜色的处理是互相独立的，所以就想到将这些积木按照颜色序号排序并拢后分别处理。

但在摞的过程中积木之间的相对位置编号也很重要，所以最终的排序方案就是：以颜色编号为第一关键字，以积木编号为第二关键字进行排序。

接下来考虑这些积木应该怎么摞能使高度最高。

容易想到，一个积木并不是一定有机会落在某个方块上的。

换言之，能竖直摞在一起的两个方块一定会满足一定的关系。

设上面的方块编号为 $a$，下面的方块的编号为 $b$，如果他们两个能摞在一起，那么一定有 $a=b+1+2k(k\in\mathbb{N})$。

从上面的式子进一步思考，我们能得到一个很关键的结论：奇数编号的积木一定与偶数编号的积木上下相邻。

更进一步，**放置奇数（偶数）编号的积木后，塔的高度变化一定是某个先前放过的偶数（奇数）编号的积木高度加一得到的**。

到了这里，最终算法应该已经出现了：

1. 排序积木。

2. 对每一种颜色的积木，分别统计奇数编号积木高度最大值 $m_1$ 和偶数编号积木高度最大值 $m_2$。

3. 如果该积木的编号为奇数，那么用 $m_2+1$ 尝试更新 $ans$ ，再用 $ans$ 尝试更新 $m_1$；

   如果该积木的编号为偶数，那么用 $m_1+1$ 尝试更新 $ans$ ，再用 $ans$ 尝试更新 $m_2$。

4. 统计结果并输出。



### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5;

struct Block{
    int col;
    int id;
    Block(){};
    Block(int col,int id):col(col),id(id){};
    friend bool operator < (Block A,Block B){
        if(A.col != B.col) return A.col < B.col;
        return A.id < B.id;
    }
}B[maxN];

int dp[maxN];
int ans[maxN];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int N;
        scanf("%d",&N);
        memset(ans,0,sizeof(ans));
        for(int i = 1;i<=N;i++){
            int c;
            scanf("%d",&c);
            B[i] = Block(c,i);
        }
        sort(B+1,B+1+N);
        B[0] = Block(0,0);
        int oddMax = 0;
        int evenMax = 0;
        for(int i = 1;i<=N;i++){
            if(B[i].col != B[i-1].col){
                oddMax = 0;
                evenMax = 0;
            }
            dp[i] = 1;
            int p = B[i].id;
            if(p & 1){
                dp[i] = max(dp[i],evenMax+1);
                oddMax = max(oddMax,dp[i]);
            } else{
                dp[i] = max(dp[i],oddMax+1);
                evenMax = max(evenMax,dp[i]);
            }
            ans[B[i].col] = max(ans[B[i].col],dp[i]);
        }
        for(int i = 1;i<=N;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：tzyt (赞：0)

题目链接[（CF](https://codeforces.com/problemset/problem/1706/B)，[洛谷）](https://www.luogu.com.cn/problem/CF1706B) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1706/)中观看。

## 思路 
观察题面上给第一个样例提供的图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/ec98c0f164311a4ec7c2c7d82fee7c9f6eae74e7.png)

可以发现，如果我们要让某种颜色形成一个塔，除非多个相同颜色在 $c$ 数组中挨在一起，可以直接向上排布。就一定需要在排布该颜色后，向两侧放一些其他颜色，然后又往相反方向放置，最后使得两个颜色相同的块在一条直线上，大概是下面这样：

```
 ⬆->->->A
 ⬆<-<-<-A<-<-<-⬆
         A->->->⬆
         1 2 ... z
```

其中， $A$ 表示一个颜色的塔，而箭头表示放置颜色块的路径。

观察发现，在放置两个 $A$ 之间，需要放置偶数个其他颜色块，下面是解释：

假设第一个 $A$ 的位置是 $(x, y)$，并且我们往右侧放置的其他颜色块的数量是（也可以是左侧） $z$。

那么为了把第二个 $A$ 搞到 $(x, y + 1)$ 上，就需要在 $(x + 1, y) \sim (x + z, y)$ 和 $(x + 1, y + 1) \sim (x + z, y + 1)$ 这些位置上放置颜色块，共计 $2z$ 个块，因此是偶数（直接网上堆的话是 $0$ 个，也是偶数）。

这就意味着，假设有两个相同的颜色块 $A$ 和 $B$，它们在 $c$ 数组中的位置分别是 $i$ 和 $j$。只有 $\lvert i - j \rvert$ 为奇数时，才可能把 $A$ 叠到 $B$ 上面，或是 $B$ 叠到 $A$ 上。

并且，只有 $i$ 和 $j$ 的奇偶性不同，$\lvert i - j \rvert$ 才可能为奇数。

然后就可以使用 dp 的方法来解决这个题目，我们对每种颜色都重复一遍相同的 dp 过程（其实更像是递推）。设 $dp_i$ 为 $c$ 数组中，使用 $i$ 个该颜色的块最高能垒成多高的塔。

那么 $dp_i$ 就可以从 $dp_{0 \sim i - 1}$ 中转移而来（ $+1$ ），并且如前面所说 $dp_i$ 和 $dp_{0 \sim i - 1}$ 的奇偶性应该不同。

同时，我们需要找的是，最近的奇偶性不同的块，要不然可能造成浪费，或者是在前面已经放过的位置又放了一个块。

## 代码

```cpp
//author: tzyt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int c[n + 1];
        vector<int> cpos[n + 1], ans(n + 1);
        set<int> unqc; // 储存所有不同的颜色
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
            cpos[c[i]].push_back(i);
            unqc.insert(c[i]);
        }
        int dp[n + 1];
        for (int cur : unqc) {
            fill(dp, dp + cpos[cur].size(), 1); 
            // 不管怎样，只要有块，总能垒成高度为 1 的塔
            int mx = 1;
            // dp[0 ~ cpos[cur].size()] 中最大的
            int lstod = -1, lstev = -1;
            // 最近的奇数位置和偶数位置，-1 为初始值
            cpos[cur][0] & 1 ? lstod = 0 : lstev = 0;
            // 判断第一个的奇偶性
            for (int i = 1; i < cpos[cur].size(); i++) {
                int lst = cpos[cur][i] & 1 ? lstev : lstod;
                if (lst != -1) 
                    dp[i] = dp[lst] + 1;
                // lst 为第一个奇偶性不同的位置
                mx = max(dp[i], mx);
                cpos[cur][i] & 1 ? lstod = i : lstev = i;
                // 更新最近的奇数位置和偶数位置
            }
            ans[cur] = mx;
        }

        for (int i = 1; i <= n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1S94y1Q7zs)

### 2 思路

我们可以发现，在 $(x,y)$ 和 $(x,y+1)$ 的色块，对应到序列里的位置**之差**肯定是奇数。

因为，在序列上，这两个色块之间，有偶数个其它色块。

所以，对于每个颜色 $r$，这道题变成了：

设长度为 $k$ 的单调上升的序列 $p$，满足对于所有的 $i$ 都有 $c_{p_i}=r$ 且 $p$ 序列相邻两数奇偶性都不同。请找出最大的 $k$。

我们可以发现，设颜色 $r$ 有 $cnt$ 个，分别**依次**在序列的 $x_1,x_2,…,x_{cnt}$ 的位置。那么，答案就是相邻两数奇偶性不同的对数加 $1$。

使用 `vector` 存储每个颜色的位置，计算即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define max_n 100000
int t;
int n;
vector<int>a[max_n+2];
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1706B_1.in","r",stdin);
	freopen("CF1706B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)a[i].clear();
		for(int i=1,x;i<=n;++i){
			scanf("%d",&x);
			a[x].push_back(i);
		}
		for(int i=1;i<=n;++i){
			ans=1;
			/*
			for(int l=0,len=a[i].size();l<=len-2;){
				for(int r=l+1;r<len;++r){
					if((a[i][r]-a[i][l])&1){
						++ans;
						printf("l=%d r=%d\n",l,r);
						vis[l]=vis[r]=true;
						l=r;
						break;
					}
					if(r==len-1){
						l=r;
						break;
					}
				}
			}*/
			for(int j=0,len=a[i].size();j<=len-2;++j){
				if((a[i][j+1]-a[i][j])&1)++ans;
			}
			if(!a[i].size())printf("0 ");
			else printf("%d ",ans);
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80265620)

By **dengziyue**

---

