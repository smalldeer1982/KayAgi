# Colored Rooks

## 题目描述

Ivan 是一名新手画家。他有 $n$ 种不同颜色的染料。他还确切地知道 $m$ 对能够和谐搭配的颜色对。

Ivan 还喜欢下国际象棋。他有 $5000$ 个车。他想取出 $k$ 个车，将每个车涂成 $n$ 种颜色中的一种，然后把这 $k$ 个车放在一个 $10^{9} \times 10^{9}$ 的棋盘上。

我们称棋盘上的一组车是连通的，如果从任意一个车出发，只通过这组车所在的格子，可以到达这组中的任意其他车。假设车可以“跳过”其他车，也就是说，一个车可以移动到任意与其同行或同列的格子。

Ivan 希望他的车的摆放满足以下条件：

- 对于每种颜色，棋盘上至少有一个这种颜色的车；
- 对于每种颜色，这种颜色的所有车组成的集合是连通的；
- 对于任意两种不同颜色 $a$ 和 $b$，如果且仅如果这两种颜色能够和谐搭配，则颜色 $a$ 和颜色 $b$ 的所有车的集合的并集是连通的。

请你帮助 Ivan 找到一种满足条件的车的摆放方案。

## 说明/提示

下图展示了所有三个样例的车的摆放方式（红色为颜色 $1$，绿色为颜色 $2$，蓝色为颜色 $3$）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1068C/d5a71529d7c75b3fe90cec66590a247efe39ded1.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1068C/b5e2c198dd08597339a7d24496646c3bd24c73c8.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1068C/50d31f17764396607f064d2853878860c84e17d0.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
1 2
2 3
```

### 输出

```
2
3 4
1 4
4
1 2
2 2
2 4
5 4
1
5 1
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
1
1 1
1
1 2
1
1 3
```

## 样例 #3

### 输入

```
3 1
1 3
```

### 输出

```
1
1 1
1
2 2
1
3 1
```

# 题解

## 作者：_6_awa (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1068C)

题目大意：你需要在一块有 $10^9 \times 10^9$ 的格子中放置若干个颜色块，使得相同颜色互相连通或间接连通（两个块在同一个列或同一行），如果有关系的两个颜色也需连通，没有关系的颜色一定不能连通。求方案。

思路分析：可以看到图是非常大的，将每个关系一一判断即可。由题意，相同格子在同一列，它们就是连通的；对于每一对有关系的颜色，就在同一行放置颜色。注意关系是没有传递性的；放置的颜色数至少为 $1$。

```cpp
#include <iostream>
using namespace std;
int n,m,a[105][1005],cnt[1005],w,wr = 1e9;
int main()
{
    cin >> n >> m;
    for(int i = 1,x,y;i <= m;i ++)
    {
        cin >> x >> y,a[x][++cnt[x]] = a[y][++cnt[y]] = ++w;//对于每个关系在同一行放置颜色
    }
    for(int i = 1;i <= n;i ++)
    {
        if(!cnt[i])
        {
            cout << "1\n" << i << " " << wr-- << '\n';//特判没有放置颜色的下标
            continue ;
        }
        cout << cnt[i] << '\n';
        for(int j = 1;j <= cnt[i];j ++)cout << i << " " << a[i][j] << '\n';//输出颜色的位置
    }
}

---

## 作者：skyskyCCC (赞：1)

## 前言。
看到这么个极棒的构造题，调了我一个小时，怎么能不纪念一下呢？

题意：给你 $n$ 种颜色 和 $m$ 个颜色互相协调的关系。两种颜色互相协调就是这两种颜色的车，需要出现在**同一行或者同一列**至少一次。颜色不协调的车就**不能在同一行、不能在同一列**。每种颜色的车**至少**出现一次，输入这些车的坐标。
## 分析。
提供三种做法，两种思路。

- 第一个做法。

首先因为要保证所以颜色的车都出现，则很显然需要构造一个合法的坐标系。考虑所谓联通的情况。因为我们可以随便放车，所以不妨将每个 $\left(i,i\right)$ 看做一个颜色的车辆，此时即为对角线，显然颜色之间不会干扰。然后考虑所谓的协调关系。对于协调关系，我们可以将车放在 $\left(x_i,n+i\right)$ 和 $\left(y_i,n+i\right)$ 这两个地方。为什么呢？因为这样放置，即保证了一种颜色中的车可以到它竖直和水平方向上的任何位置，保证连通，且此时颜色之间相协调，满足题意。因为有 $m$ 组关系，且数据范围如此之小，则肯定远远到不了 $5000$ 的上限。

代码如下，仅供参考：
```
#include<iostream>
#include<vector>
using namespace std;
int n,m,x,y;
vector<int> v[105];
int main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++){
	    v[i].push_back(i);
	}
	for (int i=1;i<=m;i++){
		cin>>x>>y;
	    v[x].push_back(n+i);
		v[y].push_back(n+i);
	}
	for (int i=1;i<=n;i++){
		cout<<v[i].size()<<"\n";
        for(int j=0;j<v[i].size();j++){
            cout<<i<<" "<<v[i][j]<<"\n";
        }
	}
	return 0;
}
```
- 第二和第三种方法。

每种颜色的车占一行，列数一直增加。每次放两种颜色，一种是**当前行的颜色**，另一种是与他**相关联的颜色**，如果当前的行小于所要放的颜色的行，那先存一下放的颜色的列数，等到了要放的那个颜色的行，那么再输出。这里的证明方法很简单，具体的做法可以看代码分析。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
int n,m,x,y;
int sum=1,ans;
vector<int> v[105];
int vis[105][105];
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
        ans=max((int)v[i].size(),1);
        cout<<ans<<"\n";
        if(!v[i].size()){
        	cout<<i<<" "<<(sum++)<<"\n";
            continue;
        }
        for(int j=0;j<v[i].size();j++){
            if(v[i][j]<i){
            	cout<<i<<" "<<vis[v[i][j]][i]<<"\n";
			}
            else{
                vis[i][v[i][j]]=sum;
                cout<<i<<" "<<(sum++)<<"\n";
            }
        }
    }
    return 0;
}
```
同理我们可以由此推出第 $i$ 行只放 $i$ 颜色的棋子，然后第 $i$ 行第 $x_i$ 列放置一个 $i$ 颜色的棋子，使之对应上面某一行的其他颜色的棋子，达到相互和谐且有联通的这个条件。想要保证不同行同列，调整 $x_i$ 即可。划分成块，然后维护即可。代码综合了以上两种做法，可以稍作修正。
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Register_int (赞：1)

首先每种颜色都要出现一次，所以可以先把所有颜色的车放到对角线上，保证不互相干扰。之后对于每一种协调关系 $x_i,y_i$，只要将车放在 $(x_i,n+i)$ 和 $(y_i,n+i)$ 就可以了。容易知道最多使用次数为 $n+2m\le3000<5000$，因此方案合法。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e2 + 10;

int n, m;

vector<int> v[MAXN];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) v[i].push_back(i);
	for (int i = 1, x, y; i <= m; i++) scanf("%d%d", &x, &y), v[x].push_back(n + i), v[y].push_back(n + i);
	for (int i = 1; i <= n; i++) {
		printf("%d\n", v[i].size());
		for (auto x : v[i]) printf("%d %d\n", i, x);
	}
}
```

---

