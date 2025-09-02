# Chips

## 题目描述

Gerald plays the following game. He has a checkered field of size $ n×n $ cells, where $ m $ various cells are banned. Before the game, he has to put a few chips on some border (but not corner) board cells. Then for $ n-1 $ minutes, Gerald every minute moves each chip into an adjacent cell. He moves each chip from its original edge to the opposite edge. Gerald loses in this game in each of the three cases:

- At least one of the chips at least once fell to the banned cell.
- At least once two chips were on the same cell.
- At least once two chips swapped in a minute (for example, if you stand two chips on two opposite border cells of a row with even length, this situation happens in the middle of the row).

In that case he loses and earns $ 0 $ points. When nothing like that happened, he wins and earns the number of points equal to the number of chips he managed to put on the board. Help Gerald earn the most points.

## 说明/提示

In the first test the answer equals zero as we can't put chips into the corner cells.

In the second sample we can place one chip into either cell (1, 2), or cell (3, 2), or cell (2, 1), or cell (2, 3). We cannot place two chips.

In the third sample we can only place one chip into either cell (2, 1), or cell (2, 4).

## 样例 #1

### 输入

```
3 1
2 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 3
3 1
3 2
3 3
```

### 输出

```
1
```

# 题解

## 作者：miraculously (赞：5)

分析：

这题要将不在角上的芯片用 $n-1$ 步走到对面，显然，这个芯片前面不能有障碍，不然至少要 $n+1$ 步，还有一个细节，因为所有芯片是同时移动的，如果两个可以移动到终点的芯片在中间相遇了，那么答案减一。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,n,m,ans;
bool a[1001],b[1001];//a，b分别记录行列是否有阻碍
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		a[x]=1;
		b[y]=1;
	}
	for(int i=2;i<n;i++)
	ans+=(!a[i])+(!b[i]);//如果行没阻碍，那答案+1，列同理
	if((n&1)&&(!a[(n>>1)+1])&&(!b[(n>>1)+1]))//处理相遇的
	ans--;
	cout<<ans;
}
```


---

## 作者：zhangqiuyanAFOon2024 (赞：3)

这道题看起来很简单，实际上，它一点也不难。

### 思路

我们先把障碍记录一下，然后把符合的都摆上去。

~~好像做完了。~~

事实上，会存在一种情况，那就是——相遇。

那就减一。

而且，这种情况只有当 $n$ 为奇数，且棋子需要经过中间行和中间列的时候才会发生。

否则，如果相遇，那么选一个棋子把它放到另一边即可。

### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int x[N],y[N],sx[N],sy[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>x[i]>>y[i],sx[x[i]]++,sy[y[i]]++;//记录
	int cnt=0;
	for(int i=2;i<n;i++)
		if(sx[i]==0) cnt++;
	for(int i=2;i<n;i++)
		if(sy[i]==0) cnt++;//全都放
	if((n&1)&&!sx[n/2+1]&&!sy[n/2+1]) cnt--;//相遇减一
	cout<<cnt;
}
```

---

## 作者：wuyixiang (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF333B)

翻译：你可以将 $a$ 块芯片放在 $n \times n$ 的棋盘的四边上，每一分钟它们都会往对面移动一格，期间不能有两块芯片相撞也不能有芯片撞上障碍物，直到 $n - 1$ 分钟后它们都移动到对面，问 $a$ 的最大值。（洛谷翻译加上自己的一些理解）

思路分析：看起来是不是很简单？（但是确实很简单）

首先，两块芯片是肯定不能在棋盘的对面的相对位置的，这样两块芯片就会撞向一起；一块芯片所在的一行（或一列）也不能有障碍物，否则它也会撞上。至于其它的似乎都可以放置了。

于是你就会错在第二个测试点。这时候再次看一下代码：如果一个芯片的横坐标和另一个芯片的纵坐标相同，它们就会撞在一起。所以对于这种情况，答案要减去 $1$。这里要注意：只有棋盘边长为奇数且芯片在正中间时才可以判断这样的情况，因为芯片可以放置在一边和对边上（都是相通的），就能避免相撞的发生。

于是代码就出来了。

```cpp
#include <iostream>
using namespace std;
int n,m,c[1005],d[1005],r,w,q;
int main()
{
    cin >> n >> m;
    w = n / 2 + 1;
    for(int i = 1,x,y;i <= m;i ++)cin >> x >> y,c[x] = d[y] = 1;//标记：这一行和这一列不能有芯片
    for(int i = 2;i < n;i ++)if(!c[i])r ++;//算芯片可以放置的个数
    for(int i = 2;i < n;i ++)if(!d[i])r ++;
    if(n % 2 && !c[w] && !d[w])q = 1;//q判断芯片在正中间相撞的情况
    cout << r - q;//输出
}

---

## 作者：heyZZZ (赞：1)

[原题](https://codeforces.com/problemset/problem/333/B)[传送门](https://www.luogu.com.cn/problem/CF333B)

## 题目大意：

有一个 $n \times n$ 的棋盘，$m$ 个格子是障碍物，然后移动芯片使它们返回到初始对边位置，不能经过障碍物、重叠或交换位置。问最多可以放置多少个芯片完成游戏。

## 思路：
本题直接按题意**模拟**即可：

1. **使用桶记录障碍**，$a_i$ 代表第 $i$ 行的芯片个数，同理 $b_i$ 代表第 $i$ 列的芯片个数。

2. 如果第 $i$ 行或第 $j$ 没有芯片，$cnt+1$。

3. 如果相遇，就是 $n$ 为奇数且中间行且列有值，$cnt-1$。


下面是样例 $3$ 的解释：

||列1|列2|列3|列4|
|:-:|:-:|:-:|:-:|:-:|
|**行1**|无芯片|可放芯片|可放芯片|无芯片|
|**行2**|**放芯片**|______|______|**放芯片**|
|**行3**|障碍物|障碍物|障碍物|可放芯片|
|**行4**|无芯片|可放芯片|可放芯片|无芯片|

行2的两个芯片可以连通，$cnt=1$。

没有相遇情况，输出 $1$。

## 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,a[100005],b[100005],cnt;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        a[x]++,b[y]++;
        //a[i] 是行，b[i] 是列。
    }
    for(int i=2;i<n;i++) cnt+=(!a[i])+(!b[i]); //不懂？看下面↓
    // a[i] 如果是空的，cnt+1。
    // b[i] 如果是空的，cnt+1。
    cout<<cnt-((n%2==1)&&!a[n/2+1]&&!b[n/2+1]);
    //如果相遇答案 -1。
    return 0;
}
```
括号的意思：如果括号里面的的表达式为 $true$ ，返回 $1$ ，否则返回 $0$。

---

## 作者：XL4453 (赞：1)

### 解题思路：

由于只能移动 $n-1$，所以一旦前面有障碍物一定不能在规定时间内到达对面，这是显然的。

对于不能交换，结合上面一条，可以得出一条对边只能放一个。

最后是不能重合，发现如果某不在对边上两个点到四个边框的第二短距离（由于这个点在一个边框上，最短的一定是 $0$）不相等，那个一定不可能在中间相遇。

而相等时，在绝大多数情况下都可以通过移动到对边来使得其不在中间相遇（可以结合 $4\times4$ 的格子理解，这种情况下是可以放满的，四个点分别放在 $(3,1)$，$(1,2)$，$(4,3)$，$(2,4)$）。

但是当恰好在中间时就无法作出相应的调整，只能将答案减一（结合 $3\times3$ 理解，这种情况下只能放一个）。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int x[10005],n,m,ans,y[10005],a,b;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		x[a]=1;y[b]=1;
	}
	for(int i=2;i<n;i++){
		if(x[i]==0)ans++;
		if(y[i]==0)ans++;
	}
	if(((n&1)==1)&&(x[(n+1)/2]==0&&y[(n+1)/2]==0))ans--;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：zdq20110120 (赞：0)

## [原题戳这里](https://www.luogu.com.cn/problem/CF333B)

### 题目大意
给定一个 $n \times n$ 的棋盘，其中有 $m$ 个格子是禁止的。将芯片放在四条边上（不能是角上），然后移动芯片使它们返回到初始对边位置，不能经过禁止的格子、重叠或交换位置。问最多可以放置多少个芯片完成游戏。

### 解题思路：
- 由于只能移动 $n - 1$ 步，所以只能直线走过去，当前面有障碍物时是一定到达不了的。
- 对于不能交换的情况，结合上面的一点，可以推出一条对边中只能有一个芯片。
- 因为所有芯片都要在同一时间开始运动，当两个芯片在中间相遇时，答案要 $-1$。

### 代码实现
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e3 + 5;
bool a[maxn], b[maxn];
ll x, y, n, m, ans;
int main() {
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		a[x] = b[y] = 1;
	}
	for (int i = 2; i < n; i++) {
		ans += (!a[i]) + (!b[i]);
	}
	if ((n & 1) and (!a[(n >> 1) + 1]) and (!b[(n >> 1) + 1])) {
		ans--;
	}
	cout << ans;
}

```

---

