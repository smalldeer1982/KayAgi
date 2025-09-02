# [ARC002D] ボードゲーム

## 题目描述

高桥君创造了一个游戏。
格状长盘上最左一列为o的阵地，最右一列为x的阵地。
使用随机排列的棋子o和x。
棋子只能一步一步向前走，不能退和斜着走，被对方吃掉的棋子要从棋盘中拿开，另外不能吃掉自己的棋子。
满足以下条件就是胜利：
    a) 把对方的棋子全部吃掉；
    b) 1个自己的棋子到达对方的阵地。
o先走，第一回合不能吃对手也不允许取胜！
为了高桥君获胜，请判断o和x哪个赢。

# 题解

## 作者：basince (赞：3)

首先，如果存在棋子的前方没有别的棋子，那么我们肯定一直让他走，这肯定是最快的。先判掉。

剩下的情况都形如一串 `o` + 一串 `x`。如 `.o.oo.o..xx.xxxx`。

现在游戏就被划分成了若干子游戏。

先假设每个子游戏“相邻”的 `o` 和 `x` 距离都为 $2$，即只存在形如 `?????o.x?????` 的情况。

我们自然不想让对方吃掉，所以会一直拖延到直到不得不送到对方嘴上为止。具体的办法就是只移动不和 `o` 相邻的 `x`、不和 `x` 相邻的 `o`。

但是如果拖延到最后，自己的棋子就会连锁反应被对方全吃掉。如 `.o.xxxxx`，此时 `x` 行动，不难发现 `x` 只能走到对方嘴上，直到被吃光。

所以我们就统计双方能拖延的步数进行比较即可。

下面设该子游戏中 `o` 的数量为 $s_1$，`x` 的数量为 $s_2$。

而对于“相邻”的 `o` 和 `x` 距离不为 $2$ 的情况，我们发现，最右边的 `o` 每往右移动一步，就多出了 $s_1-1$ 步可以拖延，`x` 同理。

那么当“相邻”的 `o` 和 `x` 距离为偶数时，对方走一步，我也走一步，双方能得到的步数是固定的，直到只剩一个 `.` 在中间为止。

而当是奇数时，我们可以归约为 $dis=3$ 的问题，即 `o..x`。

现在问题转化为，有若干二元组 $(a_i,b_i)$，双方每次取一个二元组，A 可以获得 $a_i$ 的步数，B 可以获得 $b_i$ 的步数。双方都想使自己的步数比对方越大越好。

这个问题可以看做，B 先拿走了所有二元组，每次 A 可以抢回来一个，B 可以隐藏一个。这样的话 A 每拿回来一个就得到 $a_i+b_i$ 的分差，A 就会取 $a_i+b_i$ 尽量大的二元组。而 B 为了分差缩小得尽量慢，也会拿 $a_i+b_i$ 尽量大的。这下我们排个序就可以解决了。

```cpp
int main(){
	scanf("%d%d",&n,&m);
	ri O=1e9,X=1e9;
	fo(i,1,n){
		scanf("%s",str+1);
		vector<pii>a;
		fo(j,1,m)if(str[j]!='.')a.pb({j,str[j]=='o'});
		ri ln=a.size();
		if(!a[0].se)X=min(X,a[0].fi-1);
		if(a[ln-1].se)O=min(O,m-a[ln-1].fi);
		fu(j,0,ln-1){
			if(a[j].se&&!a[j+1].se){
				ri l=j,r=j+1;
				while(l&&a[l-1].se)--l;
				while(r<ln-1&&!a[r+1].se)++r;
				fo(k,l,j)sumo+=a[j].fi-a[k].fi-(j-k);
				fo(k,j+1,r)sumx+=a[k].fi-a[j+1].fi-(k-j-1);
				ri d=a[j+1].fi-a[j].fi-1;
				if(d%2==0){
					sumx+=r-j;
					b[++t]=r-l+1;--d;
				}
				sumo+=d/2*(j-l+1);
				sumx+=d/2*(r-j);
				j=r;
			}
		}
	}
	if(O<=m||X<=m){
		printf(O<=X?"o\n":"x\n");
		return 0;
	}
	sort(b+1,b+1+t,[&](ri x,ri y){return x>y;});
	for(ri i=1;i<=t;i+=2)sumo+=b[i];
	printf(sumo>sumx?"o\n":"x\n");
}
```

---

## 作者：HNOIRPplusplus (赞：0)

首先每一行都是可以独立分开考虑的。

对于一方，

- 如果自己有若干棋子满足面前没有敌人的棋子存在，则考虑直接向前走这样的最靠近对方阵地的棋子。

- 没有这样的棋子，那么只能迎着对面的棋子撞上去。

撞上去是有讲究的，一方不能真的走到离对方棋子只有一步的地方，不然就被吃掉了。如果被吃掉了，一方不能在下一步就回吃回去，于是导致自己的前线反而撤退了一个格子。

于是，我们必须要给对手造成一个“无论动哪个棋子都会导致自己被吃”的局面。

此时对手即使有连续多个棋子，为满足“无论动哪个”都会导致自己被吃，所有的连续棋子肯定已经前后叠在一起了。所以此时被吃掉一个棋子仍然会落回到无论动哪个都会被吃的局面，最终的导致自己的防线被攻破。

我们可以把所有棋子中间的间距全部都扫出来，这样就可以求出双方在陷入这个局面之前最多可以走多少步。对距离排序再贪心即可。

```
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2010;

char g[N][N];

signed main() {
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cin >> g[i][j];
    }
  }
  int o = m + 1, x = m + 1;
  int sumo = 0, sumx = 0;
  vector<int> dis;
  for(int i = 1; i <= n; i++) {
    vector<pair<int, char> > a;
    for(int j = 1; j <= m; j++) {
      if(g[i][j] != '.') {
        a.push_back({j, g[i][j]});
      }
    }
    if(a.empty()) {
      continue;
    }
    int len = a.size();
    if(a[0].second == 'x') {
      x = min(x, a[0].first - 1);
    }
    if(a[len - 1].second == 'o') {
      o = min(o, m - a[len - 1].first);
    }
    for(int j = 0; j < len; j++) {
      if(a[j].second == 'o' && a[j + 1].second == 'x') {
        int l = j, r = j + 1;
        while(l && a[l - 1].second == 'o') {
          l--;
        }
        while(r < len - 1 && a[r + 1].second == 'x') {
          r++;
        }
        for(int k = l; k <= j; k++) {
          sumo += a[j].first - (j - k) - a[k].first;
        }
        for(int k = j + 1; k <= r; k++) {
          sumx += a[k].first - a[j + 1].first - (k - j - 1);
        }
        for(int k = 1; k <= a[j + 1].first - a[j].first - 2; k++) {
          sumo += j - l + 1;
          dis.push_back(r - l + 1);
        }
        j = r;
      }
    }
  }
  if(o <= m || x <= m) {
    cout << (x >= o ? "o\n" : "x\n");
    return 0;
  }
  sort(dis.begin(), dis.end());
  reverse(dis.begin(), dis.end());
  for(int i = 1; i < dis.size(); i += 2) {
    sumo -= dis[i];
  }
  cout << (sumx >= sumo ? "x\n" : "o\n");
  return 0;
}
```

---

