# Grid Game

## 题目描述

这是一个交互题。

你有一个 $n$ 行 $m$ 列的网格。你需要用 $1$ 到 $n \cdot m$ 的不重复整数填满每个格子。

填好网格后，你将与交互器在这个网格上进行一场游戏。双方轮流选择一个尚未被选中的格子，交互器先手。

在第一回合，交互器可以选择网格中的任意一个格子。之后，每次选择的格子必须与之前已被选中的某个格子正交相邻。如果两个格子有公共边，则称它们正交相邻。游戏持续到所有格子都被选中为止。

你的目标是让你所选格子中的数字之和严格小于交互器所选格子中的数字之和。

## 说明/提示

注意，这只是一个示例游戏，不一定代表双方的最优策略。

首先，我们用 $1$ 到 $16$ 的不重复整数如下填充一个 $4 \times 4$ 的网格：

$2$  $3$  $4$  $10$  
$12$  $6$  $11$  $15$  
$5$  $13$  $16$  $8$  
$9$  $7$  $1$  $14$  

接下来，游戏开始。

1. 交互器首先选择 $(3, 4)$，即数字 $8$。此时可以选择任意格子。从下一步开始，每次选择的格子都必须与已选格子相邻。
2. 我们选择 $(2, 4)$，即数字 $15$，与 $(3, 4)$ 相邻。
3. 交互器选择 $(4, 4)$，即数字 $14$，与 $(3, 4)$ 相邻。
4. 我们选择 $(4, 3)$，即数字 $1$，与 $(4, 4)$ 相邻。
5. $\ldots$
6. 依此类推，直到所有数字都被选中。

最终，我们选择的数字为 $[15, 1, 16, 5, 4, 2, 11, 13]$，交互器选择的数字为 $[8, 14, 7, 9, 10, 3, 6, 12]$。我们所选数字之和为 $67$，小于交互器所选数字之和 $69$，因此我们赢得了这场游戏。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
4 4




3 4

4 4

4 2

4 1

1 4

1 2

2 2

2 1```

### 输出

```
2 3 4 10
12 6 11 15
5 13 16 8
9 7 1 14

2 4

4 3

3 3

3 1

1 3

1 1

2 3

3 2```

# 题解

## 作者：_lmh_ (赞：14)

可以说这道题并不算难，但细节特别多。本题解是基于赛时做法写的，可能会有一些多余的步骤。

### Part 1：$2 \nmid nm$

使用第一个构造：骨牌。

将两个相差为 $1$ 的数拼成一个骨牌，如果对方选择了一个数就立即选择另外一个，这样最多损失 $1$。

注意到电脑会比你多进行一轮，你就可以把最大的 $nm$ 丢给电脑，剩下的拼成骨牌，就可以轻松获得胜利。

![](https://cdn.luogu.com.cn/upload/image_hosting/0vcygqs5.png)

具体解法如图，每个红框是一个骨牌。

### Part 2：$\min(n,m)=4$

现在不能靠 AI 多余的步骤获得优势了，我们该怎么办？

很难不发现第二个构造：陷阱。玩过斗兽棋的人应该很熟悉这个构造：一个贴墙的 T 型，中间放很小的数，边缘放很大的数，由于每次选择的数必须和之前选过的相邻，所以 AI 最终会被迫选很大的数，把中间很小的数让给自己。

（实际上，具体实现时可以对每个骨牌或者陷阱开 `set`，然后当 AI 选择其中之一的时候立即选择剩余最小的那个，易证这样的选择一定合法。）

不妨假设 $n=4$，手玩一下可以找到 $m=4$ 和 $m=5$ 的构造。

![](https://cdn.luogu.com.cn/upload/image_hosting/ox2qzdy4.png)

注：这里隐去了部分数字，陷阱里面填数的细节留到最后一部分说明。

然后你也很容易想到对于 $m \ge 6$ 的情况可以把最右边的陷阱往右拉两格然后中间用骨牌天上，于是我们就解决了 $n=4$ 的情况。

### Part 3：$\min(n,m)=5$

显然我们只需找到 $n=5,m=6$ 的构造，如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/h0tbor3c.png)

### Part 4：$\min(n,m) \ge 6$

不妨设 $2 \mid m$。

![](https://cdn.luogu.com.cn/upload/image_hosting/as3c2z38.png)

如下为 $n=m=6$ 的构造，如果 $n$ 更大的话在底下添上几行骨牌即可。

官方题解里面的方法是把 $n=5,m=6$ 的构造最下面两个陷阱换成骨牌，这样写起来方便很多，推荐使用这种方法。

### Part 5：正确性证明

注意到我们绝大多数构造都只有四组陷阱。

感性理解一下，你陷阱中间肯定放 $1 \sim 4$，外边肯定放 $nm-11 \sim nm$。

注意到 AI 可能从陷阱中间开始，所以如果它吃到了比较小的 ~~jiangly~~ 奖励那么外面的数也得比较小，不然他会拉开很大的差距。

所以四个陷阱可以 $1,nm-11,nm-10,nm-9$，以此类推。

计算一下收益和损失。

首先我们会损失掉最值钱的陷阱——这里 AI 从中间的奖励开始，我们获得旁边三个惩罚最小和最大的两个，这个损失是 $nm - 5$。

同时每个骨牌我们都会损失 1 点，总共 $\frac{nm}{2}-8$。

收益自然是三个大陷阱，我们获得中间的奖励和最大的惩罚，AI 吃掉中间两个（全部考虑最坏情况），收益为 $3nm - 33$。

所以收益减去惩罚为 $1.5nm - 20$，由于 $nm \ge 16$ 所以显然可以通过。

六个陷阱的构造可以通过类似的方法证明。（实际上你也可以把上面两个陷阱换成骨牌）

```cpp
//不要抄这个代码！！！赛时写的特别烂！！！
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007;
bool REVERSE;
ll DIFF;
ll T,n,m,chosen[107],board[12][12],dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},id[12][12],nS;
struct node{ll x,y;};
bool operator <(const node& a,const node& b){return board[a.x][a.y]<board[b.x][b.y];}
set<node> st[107];
pair<ll,ll> pos[107];
ll get(ll x){return (x&1)?x+1:x-1;}
void setnum(ll x,ll y,ll k){board[x][y]=k;pos[k]=make_pair(x,y);}
void output(){
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j) cout<<board[i][j]<<' ';cout<<endl;
	}
}
void buildTrp(int d,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
	setnum(x1,y1,d);
	setnum(x2,y2,n*m-(DIFF-d)*3+1);
	setnum(x3,y3,n*m-(DIFF-d)*3+2);
	setnum(x4,y4,n*m-(DIFF-d)*3+3);
	id[x1][y1]=id[x2][y2]=id[x3][y3]=id[x4][y4]=d;
	st[d].clear();
	st[d].insert((node){x1,y1});
	st[d].insert((node){x2,y2});
	st[d].insert((node){x3,y3});
	st[d].insert((node){x4,y4});
}
void buildDmino(int d,int x1,int y1,int x2,int y2){
	setnum(x1,y1,d*2-DIFF);
	setnum(x2,y2,d*2-DIFF+1);
	id[x1][y1]=id[x2][y2]=d;
	st[d].clear();
	st[d].insert((node){x1,y1});
	st[d].insert((node){x2,y2});
}
void buildTrap(int d,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
	if (REVERSE) buildTrp(d,y1,x1,y2,x2,y3,x3,y4,x4);
	else buildTrp(d,x1,y1,x2,y2,x3,y3,x4,y4);
}
void buildDomino(int d,int x1,int y1,int x2,int y2){
	if (REVERSE) buildDmino(d,y1,x1,y2,x2);
	else buildDmino(d,x1,y1,x2,y2);
}
pair<ll,ll> getnxt(ll x,ll y){
	ll d=id[x][y];
	st[d].erase(st[d].find((node){x,y}));
	auto it=st[d].begin();
	ll tx=it->x,ty=it->y;
	st[d].erase(st[d].begin());
	return make_pair(tx,ty);
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;REVERSE=0;DIFF=5;
		for (int i=1;i<=n*m+1;++i) chosen[i]=0;
		if ((n*m)&1){
			chosen[n*m+1]=1;
			int k=0;
			for (int i=1;i<=n;++i){
				if (i&1) for (int j=1;j<=m;++j) setnum(i,j,++k);
				else for (int j=m;j;--j) setnum(i,j,++k);
//				cout<<endl;
			}
			output();
			k=(n*m)/2;
			int x,y,o;
			while(k--){
				cin>>x>>y;
				chosen[o=board[x][y]]=1;
				if (!chosen[get(o)]){
					o=get(o);
					chosen[o]=1;
					cout<<pos[o].first<<' '<<pos[o].second<<endl;
					continue;
				}
				else{
					o=0;
					for (int i=1;i<=n;++i) for (int j=1;j<=m;++j) if (!chosen[board[i][j]]){
						for (int k=0;k<4;++k){
							int ii=i+dx[k],jj=j+dy[k];
							if (ii>=1&&ii<=n&&jj>=1&&jj<=m&&chosen[board[ii][jj]]){
								o=board[i][j];break;
							}
						}
						if (o) break;
					}
					chosen[o]=1;
					cout<<pos[o].first<<' '<<pos[o].second<<endl;
				}
			}
			cin>>x>>y;
		}
		else{
			nS=4;
			if (n==4){
				if (m%2){
					buildTrap(1,2,1,1,1,2,2,3,1);
					buildTrap(2,1,3,1,2,1,4,2,3);
					buildTrap(3,4,2,4,1,4,3,3,2);
					buildTrap(4,2,m,2,m-1,1,m,3,m);
					for (int i=5;i<m;i+=2) buildDomino(++nS,1,i,1,i+1);
					for (int i=4;i<m-1;i+=2) buildDomino(++nS,2,i,2,i+1);
					for (int i=3;i<m;i+=2) buildDomino(++nS,3,i,3,i+1);
					for (int i=4;i<m;i+=2) buildDomino(++nS,4,i,4,i+1);
				}
				else{
					buildTrap(1,2,1,1,1,2,2,3,1);
					buildTrap(2,1,3,1,2,1,4,2,3);
					buildTrap(3,4,2,4,1,4,3,3,2);
					buildTrap(4,3,m,3,m-1,2,m,4,m);
					for (int i=5;i<m;i+=2) buildDomino(++nS,1,i,1,i+1);
					for (int i=4;i<m;i+=2) buildDomino(++nS,2,i,2,i+1);
					for (int i=3;i<m-1;i+=2) buildDomino(++nS,3,i,3,i+1);
					for (int i=4;i<m;i+=2) buildDomino(++nS,4,i,4,i+1);
				}
			}
			else if (m==4){
				swap(n,m);REVERSE=1;
				if (m%2){
					buildTrap(1,2,1,1,1,2,2,3,1);
					buildTrap(2,1,3,1,2,1,4,2,3);
					buildTrap(3,4,2,4,1,4,3,3,2);
					buildTrap(4,2,m,2,m-1,1,m,3,m);
					for (int i=5;i<m;i+=2) buildDomino(++nS,1,i,1,i+1);
					for (int i=4;i<m-1;i+=2) buildDomino(++nS,2,i,2,i+1);
					for (int i=3;i<m;i+=2) buildDomino(++nS,3,i,3,i+1);
					for (int i=4;i<m;i+=2) buildDomino(++nS,4,i,4,i+1);
				}
				else{
					buildTrap(1,2,1,1,1,2,2,3,1);
					buildTrap(2,1,3,1,2,1,4,2,3);
					buildTrap(3,4,2,4,1,4,3,3,2);
					buildTrap(4,3,m,3,m-1,2,m,4,m);
					for (int i=5;i<m;i+=2) buildDomino(++nS,1,i,1,i+1);
					for (int i=4;i<m;i+=2) buildDomino(++nS,2,i,2,i+1);
					for (int i=3;i<m-1;i+=2) buildDomino(++nS,3,i,3,i+1);
					for (int i=4;i<m;i+=2) buildDomino(++nS,4,i,4,i+1);
				}
				swap(n,m);
			}
			else if (m%2==0){
				if (n==5){
					assert(m>=6);
					nS=6;DIFF=7;
					buildTrap(1,1,2,1,1,1,3,2,2);
					buildTrap(2,5,2,5,1,5,3,4,2);
					buildTrap(3,3,1,2,1,4,1,3,2);
					buildTrap(4,1,m-1,1,m-2,1,m,2,m-1);
					buildTrap(5,5,m-1,5,m-2,5,m,4,m-1);
					buildTrap(6,3,m,2,m,4,m,3,m-1);
					for (int i=4;i<m-3;i+=2){
						buildDomino(++nS,1,i,1,i+1);
						buildDomino(++nS,5,i,5,i+1);
					}
					for (int i=3;i<m-2;i+=2){
						buildDomino(++nS,2,i,2,i+1);
						buildDomino(++nS,3,i,3,i+1);
						buildDomino(++nS,4,i,4,i+1);
					}
				}
				else{
					buildTrap(1,2,1,1,1,3,1,2,2);
					buildTrap(2,5,1,4,1,6,1,5,2);
					buildTrap(3,2,m,1,m,3,m,2,m-1);
					buildTrap(4,5,m,4,m,6,m,5,m-1);
					for (int i=2;i<m;i+=2){
						buildDomino(++nS,1,i,1,i+1);
						buildDomino(++nS,3,i,3,i+1);
						buildDomino(++nS,4,i,4,i+1);
						buildDomino(++nS,6,i,6,i+1);
					}
					for (int i=3;i<m-1;i+=2){
						buildDomino(++nS,2,i,2,i+1);
						buildDomino(++nS,5,i,5,i+1);
					}
					for (int j=7;j<=n;++j) for (int i=1;i<m;i+=2) buildDomino(++nS,j,i,j,i+1);
				}
			}
			else if (n%2==0){
				swap(n,m);REVERSE=1;
				if (n==5){
					assert(m>=6);
					nS=6;DIFF=7;
					buildTrap(1,1,2,1,1,1,3,2,2);
					buildTrap(2,5,2,5,1,5,3,4,2);
					buildTrap(3,3,1,2,1,4,1,3,2);
					buildTrap(4,1,m-1,1,m-2,1,m,2,m-1);
					buildTrap(5,5,m-1,5,m-2,5,m,4,m-1);
					buildTrap(6,3,m,2,m,4,m,3,m-1);
					for (int i=4;i<m-3;i+=2){
						buildDomino(++nS,1,i,1,i+1);
						buildDomino(++nS,5,i,5,i+1);
					}
					for (int i=3;i<m-2;i+=2){
						buildDomino(++nS,2,i,2,i+1);
						buildDomino(++nS,3,i,3,i+1);
						buildDomino(++nS,4,i,4,i+1);
					}
				}
				else{
					buildTrap(1,2,1,1,1,3,1,2,2);
					buildTrap(2,5,1,4,1,6,1,5,2);
					buildTrap(3,2,m,1,m,3,m,2,m-1);
					buildTrap(4,5,m,4,m,6,m,5,m-1);
					for (int i=2;i<m;i+=2){
						buildDomino(++nS,1,i,1,i+1);
						buildDomino(++nS,3,i,3,i+1);
						buildDomino(++nS,4,i,4,i+1);
						buildDomino(++nS,6,i,6,i+1);
					}
					for (int i=3;i<m-1;i+=2){
						buildDomino(++nS,2,i,2,i+1);
						buildDomino(++nS,5,i,5,i+1);
					}
					for (int j=7;j<=n;++j) for (int i=1;i<m;i+=2) buildDomino(++nS,j,i,j,i+1);
				}
				swap(n,m);
			}
			else return -1;
			output();
			ll k=n*m/2;
			while(k--){
				ll x,y;
				cin>>x>>y;
				auto p=getnxt(x,y);
				cout<<p.first<<' '<<p.second<<'\n';
			}
		}
	}
	return 0;
}
```

`Matrix67` 的科普书《浴缸里的惊叹》中博弈论章节第九个问题正是该题 $n=m=8$ 的情况。

赛时把 $\min(n,m)$ 等于五和大于五分类也正是因为书中用的是 Part 4 的构造，不适用于 $\min(n,m)=5$ 的情况。

---

## 作者：xzCyanBrad (赞：2)

视频题解。

![](bilibili:BV1PQtUe6Ejv)

[上面视频崩了的话到 B 站看](https://www.bilibili.com/video/BV1PQtUe6Ejv/)

---

