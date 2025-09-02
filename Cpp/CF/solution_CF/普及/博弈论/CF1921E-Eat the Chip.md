# Eat the Chip

## 题目描述

Alice 和 Bob 正在一个棋盘上玩游戏。棋盘有 $h$ 行，从上到下编号，有 $w$ 列，从左到右编号。两位玩家各有一个棋子。最开始，Alice 的棋子位于坐标 $(x_a, y_a)$（第 $x_a$ 行，第 $y_a$ 列），Bob 的棋子位于 $(x_b, y_b)$。保证两枚棋子的初始位置不会重合。两位玩家轮流行动，Alice 先手。

在她的回合，Alice 可以将她的棋子移动到正下方、左下方或右下方的相邻格子。Bob 则可以将他的棋子移动到正上方、左上方或右上方的相邻格子。棋子不能移动到棋盘之外。

更具体地说，如果 Alice 的回合开始时她在 $(x_a, y_a)$，她可以将棋子移动到 $(x_a + 1, y_a)$、$(x_a + 1, y_a - 1)$ 或 $(x_a + 1, y_a + 1)$。Bob 的回合，如果他在 $(x_b, y_b)$，他可以将棋子移动到 $(x_b - 1, y_b)$、$(x_b - 1, y_b - 1)$ 或 $(x_b - 1, y_b + 1)$。新的棋子坐标 $(x', y')$ 必须满足 $1 \le x' \le h$ 且 $1 \le y' \le w$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921E/132ee8f6414f793fc5ccbac975e03978861ca953.png) 示例游戏状态。Alice 用白色棋子，Bob 用黑色棋子。箭头表示可能的移动。若某位玩家将棋子移动到对方棋子所在的格子，则立即获胜。如果某位玩家无法行动（Alice 到达最后一行，即 $x_a = h$，Bob 到达第一行，即 $x_b = 1$），则游戏立即以平局结束。

如果双方都采取最优策略，游戏结果会如何？

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
12
6 5 2 2 5 3
4 1 2 1 4 1
1 4 1 3 1 1
5 5 1 4 5 2
4 4 1 1 4 4
10 10 1 6 10 8
10 10 2 6 10 7
10 10 9 1 8 1
10 10 8 1 10 2
10 10 1 1 2 1
10 10 1 3 4 1
10 10 3 1 1 1```

### 输出

```
Alice
Bob
Draw
Draw
Draw
Alice
Draw
Draw
Bob
Alice
Alice
Draw```

# 题解

## 作者：Double_Light (赞：7)

首先发现如果 $A$ 棋子在 $B$ 下面或者与 $B$ 在同一行那么必定平局。

假设有一方赢了，那么这颗棋子一定最后落在了与另一颗棋子同一行的位置，所以可以得到当游戏开始时如果 $c-a$ 为奇数时 Alice 有可能赢，当 $c-a$ 为偶数时 Bob 有可能赢。

假设现在 Alice 有可能赢且不会输，而 Bob 没有可能赢且有可能输，显然 Bob 会尽量做到平局。如果 Bob 与 Alice 初始列位置相差不超过 $1$，Alice 可以先用一步调整到与 Bob 同一列，然后一直保持与 Bob 同一列，所以最后一定赢。

否则如果 $B$ 比 $A$ 在棋盘上更靠左，Bob 一定会向左边跑；如果更靠右，则一定会往右边跑。此时如果 Bob 会被抓住，那么一定是碰到了棋盘边界，然后不能向两边移动而被 Alice 抓住。此时要求 $A$ 距离边界不超过 $A$ 在与 $B$ 同一行及以前的可以走的总共步数，也就是 $\dfrac{c-a+1}{2}$。

Bob 赢的情况同理可得，不再详述。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int T;
int n,m;
int a,b,c,d;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m>>a>>b>>c>>d;
		if(a>=c)cout<<"Draw\n";
		else if((c-a)%2==1){
			if(abs(b-d)<=1)cout<<"Alice\n";
			else if(b>d&&b-1<=(c-a)/2+1)cout<<"Alice\n";
			else if(b<d&&(m-b)<=(c-a)/2+1)cout<<"Alice\n";
			else cout<<"Draw\n";
		}
		else if((c-a)%2==0){
			if(b==d)cout<<"Bob\n";
			else if(d>b&&d-1<=(c-a)/2)cout<<"Bob\n";
			else if(d<b&&(m-d)<=(c-a)/2)cout<<"Bob\n";
			else cout<<"Draw\n";
		}
	}
	return 0;
} 
```

---

## 作者：KID2695 (赞：6)

很容易发现当两个棋子之间没有空行的时候，下一步就会绝对结果，所以这时候两个棋子的位置就很重要，你可以通过计算得到这一时刻两个棋子能到达的区间，但请注意，此时该先走的棋子可以再走一步，所以需要将可以到达的区间扩大一次。

然后如果先走的棋子能到的区间能够完全覆盖后走的棋子能到的区间的话，先手就赢了，否则后手一定没法赢，最优就是平局。

对于这个时刻的时候谁是先手，可以通过两个棋子之间相隔的空行数量的奇偶性来得到。

特别的，如果两个棋子在同一行，或者 Alice 的棋子在 Bob 棋子的上方的话是平局。

核心代码：

```cpp
while(t--){
  iread();
  int n=iread();
  x=iread();
  y=iread();
  x_=iread();
  y_=iread();
  if(x_<=x){
    puts("Draw");
    continue;
  }
  if((x_-x-1)&1){
    int qwe=(x_-x)>>1;
    int R=y+qwe,L=y-qwe;
    L=max(1,L);
    R=min(n,R);
    int r=y_+qwe,l=y_-qwe;
    l=max(1,l);
    r=min(n,r);
    if(L<l||r<R) puts("Draw");
    else puts("Bob");
  }
  else {
    int qwe=(x_-x-1)>>1;
    int R=y+qwe+1,L=y-qwe-1;
    L=max(1,L);
    R=min(n,R);
    int r=y_+qwe,l=y_-qwe;
    l=max(1,l);
    r=min(n,r);
    if(l<L||R<r) puts("Draw");
    else puts("Alice");
  }
}
```

---

## 作者：LiaoYF (赞：5)

## 做法
首先是 $x_a>x_b$ 的时候，Alice 在 Bob 下方，不可能会相遇，输出 `Draw`。

然后考虑会相遇的情况，每次不管是 Alice 还是 Bob 移动，$x_b-x_a$ 都会减小 $1$，所以能计算出来需要多少步两人到同一横排。如果 $x_b=x_a$ 时是 Alice 移动，那么就是 Alice 吃 Bob ，Bob 移动的情况也一样。

算出来两个棋子能走到的最小的 $y$ 和最大的 $y$，如果吃的那一方包含了被吃的那一方，就胜利，否则被吃的一方可以跑掉，输出 `Draw`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,m,xa,ya,xb,yb;
        cin>>n>>m>>xa>>ya>>xb>>yb;
        if(xa<=xb){
            int k=xb-xa;
            if(k%2==1){//Alice可能会赢
                int ka=(k+1)/2,kb=(k-1)/2;
                int la=max(1ll,(ya-ka)),ra=min(m,(ya+ka));
                int lb=max(1ll,(yb-kb)),rb=min(m,(yb+kb));
                if(la<=lb&&ra>=rb){
                    cout<<"Alice\n";
                }else{
                    cout<<"Draw\n";
                }
            }else{//Bob可能会赢
                int ka=(k)/2,kb=(k)/2;
                int la=max(1ll,(ya-ka)),ra=min(m,(ya+ka));
                int lb=max(1ll,(yb-kb)),rb=min(m,(yb+kb));
                if(lb<=la&&rb>=ra){
                    cout<<"Bob\n";
                }else{
                    cout<<"Draw\n";
                }
            }
        }else{
            cout<<"Draw\n";
        }
    }
    return 0;
}
```

---

## 作者：yyrwlj (赞：4)

## 题意简述

爱丽丝和鲍勃在一个 $n \times m$ 的棋盘上下棋，两人各有一枚棋子在棋盘上。

两人由爱丽丝开始轮流行动，爱丽丝每次行动能将自己的棋子向左下、正下或右下移动，鲍勃每次行动能将自己的棋子向左上、正上或右上移动。注意不能将棋子移出棋盘外。

当有玩家将自己的棋子移到对方棋子的位置上时，该玩家获胜。若有玩家无法移动自己的棋子，那么游戏立即以平局结束。

两人都绝顶聪明，求出谁会获胜或告知平局。

## 思路

不妨设最开始两人的棋子都在同一列上，很显然若棋子行坐标之差为偶数，则先手必败。

证明：首先爱丽丝移到哪一列，鲍勃都可以跟上，最后行坐标之差为 $2$ 时，爱丽丝移动后，鲍勃就可以移动到爱丽丝的位置上了。

那么再推广到不同列，因为两人绝顶聪明，所以知道自己若在同一列必然会输的一方，肯定会尽可能地躲避另一方，追求平局。在同一列必然会赢的一方也肯定会尽量追。

我们发现，能不能追到无路可躲（到棋盘边缘）的时候不是那么好求。

但是行数最多只有 $10^6$，所以循环模拟即可。

具体实现时会有很多细节需要注意，接下来看代码。

## Code

```cpp
#include <iostream>
using namespace std;
void work()
{
    int n, m, xa, ya, xb, yb;
    scanf("%d%d%d%d%d%d", &n, &m, &xa, &ya, &xb, &yb);
    if (xa > xb) //如果鲍勃已经在爱丽丝上方，那就肯定平局。
    {
        puts("Draw");
        return;
    }
    int xc = xb - xa;
    if (ya == yb)
    {
        if (xc & 1)
            puts("Alice");
        else
            puts("Bob");
        return;
    }
    if (xc & 1) // 爱丽丝追鲍勃
    {
        while (xa < xb)
        {
            if (yb < ya) // 往鲍勃的方向追
                ya --;
            else if (yb > ya)
                ya ++;
            else		// 如果已经在同一列
            {
                puts("Alice");
                return;
            }
            xa ++;
            if (xa == xb && ya == yb)
            {
                puts("Alice");
                return;
            }
            if (yb < ya && yb > 1) // 往反方向躲
                yb --;
            else if (yb > ya && yb < m)
                yb ++;
            xb --;
            if (xa == xb && ya == yb)
            {
                puts("Alice");
                return;
            }
        }
        puts("Draw");
    }
    else 	// 爱丽丝躲鲍勃
    {
        while (xa < xb)
        {
            if (yb < ya)
            {
                if (ya < m)
                    ya ++;
            }
            else if (ya < yb)
            {
                if (1 < ya)
                    ya --;
            }
            else
            {
                if (xb - xa <= 1)
                    puts("Draw");
                else
                    puts("Bob");
                return;
            }
            xa ++;
            if (xa == xb && ya == yb)
            {
                puts("Bob");
                return;
            }
            if (yb < ya)
                yb ++;
            else
                yb --;
            xb --;
            if (xa == xb && ya == yb)
            {
                puts("Bob");
                return;
            }
        }
        puts("Draw");
    }
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```

---

## 作者：_std_O2 (赞：1)

# Eat the Chip
## 特殊情况
 
我们发现如果 Alice 和 Bob 在**同一列**，且他们的列差 $(y_{a}-y_{b})$ 为奇数则 Alice 赢，否则 Bob 赢（他们下模仿棋）。

如列差为 $3$，则 Alice 可以走 $2$ 步，Bob 可以只以走 $1$ 步。
 
当然如 $(y_{a}<y_{b})$ 则平局。
## 一般情况:
Alice 靠近左边界她就会靠往左边界走（避免 Bob 和她下模仿棋）反之就向右边走。则 Bob 也会向 Alice 的方向靠。
 
如果 Bob 到达左边界或右边界时 Alice 在他同一列或者左边或右边右边一列时且 $(y_{a}-y_{b})$ 为偶数则 Bob 赢（模仿棋）反之 Alice 赢。

------------

如果 Bob 到边界时 Alice 已经在他下方是则平局。


## code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	long long  h,w,ya,yb,xa,xb;
	cin>>T;
	long long xd;
	long long step;
	for(int i=1;i<=T;i++){
		cin>>h>>w>>ya>>xa>>yb>>xb;
		xd=yb-ya;
		step=xd/2;
		if(xd<=0){
			cout<<"Draw"<<endl;
		}	
		else if(xd%2==0){
			if((xa<xb&&xb-1<=step)||(xa>xb&&w-(xb)<=step)||xa==xb){
				cout<<"Bob"<<endl;
			}
			else cout<<"Draw"<<endl;
		}
		else if(xd%2==1){
			step=(xd/2)+1;
			if((xa<xb&&w-(xa)<=step)||(xa>xb&&xa-1<=step)||xa==xb||xa==xb-1||xa==xb+1){
				cout<<"Alice"<<endl;
			}
			else cout<<"Draw"<<endl;
		}

	}
}
```
求过QwQ

---

## 作者：yuyc (赞：1)

### 题意
给定一个 $h \times w$ 的棋盘以及白棋坐标 $(x_a,y_a)$ 和黑棋坐标 $(x_b,y_b)$。

白棋每次只能往正下、右下、左下方向移动一格，黑棋每次只能往正上、右上、左上方向移动一格，不能超过边界。

在移动棋子后覆盖对方的棋子一方获胜，如果有一方无法移动（如白棋走到了下边界），则平局。

问如果双方采取最优策略，比赛的结果。

### 解析

首先，如果白棋在黑棋下面或与其处在同一行，即 $x_a\ge x_b$，则必定平局，因为题目保证两棋子起始坐标不同且白棋无法往上走，黑棋无法往下走，两棋子必定越走越远。

其次，注意到白棋先手，这意味着两棋子起始坐标的纵向距离的奇偶性决定了谁是猎人，谁是猎物。

当 $x_b - x_a$ 为奇数时，能在某次移动后使得两棋子 $x$ 坐标一致的必定是白棋，这意味着黑棋不可能赢，故白棋是猎人，黑棋是猎物。

此时：

对于白棋，它要追，它要做的就是尽可能缩小两棋子之间 $y$ 坐标的差值；

对于黑棋，它要跑，它要做的就是尽可能扩大两棋子之间 $y$ 坐标的差值。

故如果白棋在黑棋的左边，白棋必定往右下走，黑棋必定往右上走。

此时：

令白棋能走的步数为 $stepa=\lfloor(x_b-x_a+1)/2\rfloor $，黑棋能走的步数为 $stepb=\lfloor(x_b-x_a)/2\rfloor$

黑棋往右上走，只能走 $run=\min(stepb,w-y_b)$ 步，走完之后就不能走或者到达右边界只能往正上走了。因为两棋子前 $run$ 步分别往右下走和往右上走，$y$ 坐标差值并不会变化。只有当黑棋只能往正上走或者不能走的时候，白棋的移动才真正缩小两棋子 $y$ 坐标的差值。

所以，我们可以求得白棋最多可以将两棋子之间的 $y$ 坐标的差值缩小 $stepa-run$ 格。

故如果 $stepa - run \ge y_b - y_a$，白棋胜，否则平局。

白棋在黑棋右边以及 $x_b-x_a$ 为偶数的情况同理，这里不再赘述，请读者自行推导。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		int h,w,xa,ya,xb,yb;
		cin>>h>>w>>xa>>ya>>xb>>yb;
		if(xa >= xb){
			cout<<"Draw\n";
			continue;
		}
		int stepa = (xb - xa + 1) / 2,stepb = (xb - xa) / 2;
		if((xb - xa) & 1){ //Alice追，Bob跑
			if(ya < yb){
				int run = min(w - yb,stepb); //往右跑run格
				if(stepa - run >= yb - ya) cout<<"Alice\n";
				else cout<<"Draw\n";
			}else{
				int run = min(yb - 1,stepb); //往左跑run格
				if(stepa - run >= ya - yb) cout<<"Alice\n";
				else cout<<"Draw\n";
			}
		}else{
			if(ya < yb){ //Bob追，Alice跑
				int run = min(ya - 1,stepa); //往左跑run格
				if(stepb - run >= yb - ya) cout<<"Bob\n";
				else cout<<"Draw\n";
			}else{
				int run = min(w - ya,stepa); //往右跑run格
				if(stepb - run >= ya - yb) cout<<"Bob\n";
				else cout<<"Draw\n";
			}
		}
	}
	return 0;
}
```



---

## 作者：nyC20 (赞：1)

# 题目翻译
Alice 和 Bob 两个人在下棋，这种棋的规则是：

1.棋子的初始位置已经给出，两个人轮流移动自己的棋子，Alice 每一次移动可以让自己的棋子向正下方、左下方或右下方移动，Bob 可以让自己的棋子向正上方、左上方或右上方移动。

2.游戏结束一定满足以下两种情况之一：第一种：如果 Alice 的棋子走到了棋盘的最下方或者 Bob 的棋子走到了棋盘的最上方，则为平局。第二种：如果 Alice 的棋子走到了 Bob 的棋子所在的位置，则是 Alice 赢，反之 Bob 赢。

# 思路
首先特判平局情况，如果 Alice 的棋子在 Bob 的棋子的下面，则必定为平局。接下来计算出 Alice 的棋子和 Bob 的棋子的垂直距离，用两个棋子初始位置的 $x$ 值相减，即需要移动多少轮棋子才能使得两个棋子的 $x$ 轴相等，因为整局游戏只有这一次机会可以决出胜负。然后分别算出两个棋子能到达的最远左端点和最远右端点，即两个棋子能到达的区间。如果一个人的区间能完全覆盖另一个人的区间，那么就代表后者不管怎样走前者都可以把他的棋子吃掉，那么前者赢。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, h, w, xa, xb, ya, yb, f, la, lb, ra, rb;
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d%d",&w,&h,&xa,&ya,&xb,&yb);
		if(xa>xb)printf("Draw\n");//特判，Alice在Bob下面的情况 
		else {
			f=xb-xa;//两个棋子的距离 
			if(f%2==0){//走棋次数是偶数，即Bob有可能吃掉Alice 
				la=max(1,ya-f/2);//Alice的左端点 
				ra=min(h,ya+f/2);//Alice的右端点 
				lb=max(1,yb-f/2);//Bob的左端点 
				rb=min(h,yb+f/2);//Bob的右端点 
				if(lb<=la&&rb>=ra)printf("Bob\n");
				else printf("Draw\n");//吃不掉，只能走到底，平局 
			}
			else {//反之Alice有可能吃掉Bob 
				la=max(1,ya-(f+1)/2);//同上，但是因为Alice先手，所以Alice能比Bob多走一步 
				ra=min(h,ya+(f+1)/2);
				lb=max(1,yb-(f-1)/2);
				rb=min(h,yb+(f-1)/2);
				if(la<=lb&&ra>=rb)printf("Alice\n");
				else printf("Draw\n");
			}
		}
	}
	return 0;
}
```

---

## 作者：czh___ (赞：0)

### 题目大意：
棋盘上白棋先手，黑棋后手。白棋子只能向下三个位置，黑棋子只能向上三个位置，谁先走到对方棋子位置就获胜。两个棋子起点一定不相同。
### 题解
分析：显然问题是有规律性的，如果白棋子在下而黑棋子在上，那么一定平局。

继续分析：易知：如果两个棋子行数差距为奇数先手赢，偶数后手赢。

以奇数行差距为例，后手玩家为避免被吃掉，走棋时一定要尽可能远离白棋。

1. 如果起始两个棋子列数差为 $1$ 或者 $0$，那么白棋先走可以始终保持在黑棋正上方，黑棋必败。

2. 列数差大于等于 $2$，此时黑棋走棋趋势为加大这个列数差，白棋一定减少这个列数差。如果棋盘无限大，那么必然平局。但是棋盘不是无限大，黑棋每逃离一次，白棋追赶一次，两个棋子行数差会减少 $2$。以此为判定条件，问题可解。

温馨提示：初始时两个棋子列数差也要考虑进去。为方便阅读，代码没有进行公式化简。

### 代码

```cpp
#include<iostream>
using namespace std;
int t,n,m,a,b,c,d;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m>>a>>b>>c>>d;
        if(a>=c)
            cout<<"Draw\n";
        else if((c-a)%2==0){
            if(b-d>=1&&(b-d)-1+m-b>=(c-a)/2||d-b>=1&&d-b-1+b-1>=(c-a)/2)
               cout<<"Draw\n";
            else
                cout<<"Bob\n";
        }
        else{
            if(d-b>=2&&d-b-2+m-d>=(c-a)/2||b-d>=2&&b-d-2+d-1>=(c-a)/2)
                cout<<"Draw\n";
            else
                cout<<"Alice\n";
        }
    }
    return 0;
}
```

拜拜！

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
这是一题博弈论。我们可以先想一下特殊情况：

- Bob 只能向上走，Alice 只能想向下走，所以如果 Bob 在 Alice 上面，双方不可能吃掉对方，平局，应输出 `Draw`。
- Alice 和 Bob 的横向距离大于他们的纵向距离，即便他们向中间靠，但也不能吃掉对方。注意这里可能有负数。


接下来算双方的最远和最近的横向坐标，如果在同一垂直直线上且相距奇数个构造单位，Bob 的包含了 Alice 的，就胜利，否则平局。反之，如果在同一垂直直线上且相距奇数个构造单位，Alice 的包含了 Bob 的，就胜利，否则平局。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;ll T,xa,xb,ya,yb,n,m;
const ll N=1;//因为上面变量是long long 类型，为了比较时不报错，就搞一个这个
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;
        cin>>xa>>ya>>xb>>yb;
        if(xa>xb||abs(ya-yb)>abs(xa-xb)){cout<<"Draw"<<endl;continue;}//特判
        else{
            if((xb-xa)%2==1){
                ll a1=(xb-xa+1)/2,a2=(xb-xa-1)/2;
                ll ta_max=max(N,(ya-a1)),ta_min=min(m,(ya+a1)),tb_max=max(N,(yb-a2)),tb_min=min(m,(yb+a2));
                if(ta_max<=tb_max&&ta_min>=tb_min){
                    cout<<"Alice"<<endl;//
                }else{
                    cout<<"Draw"<<endl;
                }
            }else{//和上面基本一样，只不过胜利对象和奇偶计算方式不同
                ll a=(xb-xa)/2;
                ll ta_max=max(N,(ya-a)),ta_min=min(m,(ya+a)),tb_max=max(N,(yb-a)),tb_min=min(m,(yb+a));
                if(tb_max<=ta_max&&tb_min>=ta_min){
                    cout<<"Bob"<<endl;
                }else{
                    cout<<"Draw"<<endl;
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1921E)

这题是老师给我们出的比赛中见到的，就过来做了。

~~我本来想出了正解，结果因为老师的数据出锅导致被吞掉 75 分……~~

首先，如果 Alice 在 Bob 的下方，显然他们谁也吃不到谁，所以直接输出平局。

其次，如果 Alice 和 Bob 的横向距离超过他们的纵向距离（即 $|y_a - y_b| > |x_a - x_b|$），那么即使他们都往中间靠，也还是会互相错过，也是平局。

现在特殊情况都考虑完了，开始模拟 Alice 和 Bob 的操作。

首先，如果 Alice 和 Bob 的纵向距离是偶数，那么 Bob 必不会输。因为每次都是往前 $1$ 格，偶数轮后 Alice 和 Bob 在同一行，而 Bob 是后手，所以只有 Bob 可能进入对方的格子。那么现在，Alice 是不会赢的，所以她必须尽力逃离 Bob。

如果 Alice 和 Bob 在同一列上，那么无论 Alice 往哪边走， Bob 总能继续和她在同一列上，所以 Alice 是必输的。

反之，Alice 需要逃命直到没法逃为止，而 Bob 需要在和 Alice 错过之前抓住她。

刚开始时，Alice 的最好方案是往 Bob 的反方向跑（即如果 Bob 在她的右边她就往左边跑，反之亦然），跑到棋盘边缘后沿着边缘走。而 Bob 需要和 Alice 跑同样方向，才有可能抓到 Alice。

第一个部分是 Alice 往边缘跑，此时 Bob 永远会跟她相差至少 $1$ 格的横向距离，所以如果这个过程结束后 Bob 在 Alice 上方，他们就错过了，判定平局。

第二个部分是 Alice 沿着边缘走。我们找到 Alice 什么时候会和 Bob 在同一行，然后看看 Bob 能不能到达 Alice 到时候所在的位置，如果能就输出 Bob 赢，否则是平局。

然后还有第二种初始情况，就是 Alice 和 Bob 的纵向距离为奇数。同理，此时 Alice 是必不输的。

如果 Alice 要走第一步，那么肯定要往 Bob 的方向走。如果 Bob 在她的正下方就直接往下走。

此时，把 Alice 和 Bob 的位置水平翻转再对调，你就会发现：这不是和第一种情况一样吗？只是 Alice 变成了 Bob，Bob 变成了 Alice。

接下来的部分直接复制第一种情况就好了，只是如果新的 Bob 抓住了新的 Alice，就相当于原本的 Alice 抓住了原本的 Bob，此时是 Alice 胜。

下面是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, h, w, xa, xb, ya, yb;
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%d%d%d%d%d%d", &h, &w, &xa, &ya, &xb, &yb);
		if (xa >= xb || abs(ya - yb) > abs(xa - xb)){puts("Draw"); continue;}//特判平局
		if ((xb - xa) % 2 == 0){//纵向距离为偶数
			if (ya == yb){puts("Bob"); continue;}//如果在同一列上就是Bob赢
			else if (ya < yb){
				int k = yb - ya, k2 = ya - 1;
				ya = 1, yb = k + 1;
				xa += k2, xb -= k2;
			}
			else{
				int k = ya - yb, k2 = w - ya;
				ya = w, yb = w - k;
				xa += k2, xb -= k2;
			}//Alice逃到边缘
			if (xa > xb || (xa == xb && ya != yb)){puts("Draw"); continue;}//错过输出平局
			int k = (xb - xa) / 2;
			xa += k, xb -= k;
			if (yb < ya) yb += k;
			else yb -= k;
			if (yb < 1) yb = 1; if (yb > w) yb = w;
			if (xa == xb && ya == yb){puts("Bob"); continue;}
			else puts("Draw");//判断最终结果
		}
		else{
			if (ya == yb) xa++;
			else if (ya < yb) xa++, ya++;
			else xa++, ya--;//让Alice走第一步
			xa = h + 1 - xa, xb = h + 1 - xb;
			swap(xa, xb); swap(ya, yb);//进行调整，两人互换
//------------------------接下来都是复制上文的内容-----------------------
			if (ya == yb){puts("Alice"); continue;}
			else if (ya < yb){
				int k = yb - ya, k2 = ya - 1;
				ya = 1, yb = k + 1;
				xa += k2, xb -= k2;
			}
			else{
				int k = ya - yb, k2 = w - ya;
				ya = w, yb = w - k;
				xa += k2, xb -= k2;
			}
			if (xa > xb || (xa == xb && ya != yb)){puts("Draw"); continue;}
			int k = (xb - xa) / 2;
			xa += k, xb -= k;
			if (yb < ya) yb += k;
			else yb -= k;
			if (yb < 1) yb = 1; if (yb > w) yb = w;
			if (xa == xb && ya == yb){puts("Alice"); continue;}
			else puts("Draw");
		}
	}
	return 0;
}
```

---

## 作者：mountain_climber (赞：0)

### [题面链接](https://www.luogu.com.cn/problem/CF1921E)

### 思路

首先发现纵向他们一定是在接近的，考虑在相遇之前的一步（在同一行之前）是谁踏出的谁就可能获胜，那么这个人就会选择一开始去追另外一个人，另外一个人则会选择逃跑，如果追的那个人的横向覆盖范围可以覆盖另一个人的横向覆盖范围，那么他一定可以追上（获胜）。直接堆判断即可，注意细节。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,h,w,xa,xb,ya,yb;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);
	cin>>t;
	while(t--){
		cin>>h>>w>>xa>>ya>>xb>>yb;
		if(xa>=xb){
			cout<<"Draw"<<endl;
			continue;
		}
		else{
			int k=(xb-xa)/2,kk=(xb-xa)/2+1;
			if((xb-xa)%2){
				if(max(1,ya-kk)<=max(1,yb-k)&&min(w,ya+kk)>=min(w,yb+k))
					cout<<"Alice"<<endl;
				else
					cout<<"Draw"<<endl;
			}
			else{
				if(max(1,yb-k)<=max(1,ya-k)&&min(w,yb+k)>=min(w,ya+k))
					cout<<"Bob"<<endl;
				else
					cout<<"Draw"<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 题目大意

现在有两个人在玩一个游戏，第一个人的棋子在 $(x_a,y_a)$ 处，第二个人的棋子在 $(x_b,y_b)$ 处。

第一个人的棋子只能走到：

$$(x_a+1,y_a),(x_a+1,y_a-1),(x_a+1,y_a+1)$$

第二个人的棋子只能走到：

$$(x_b-1,y_b),(x_b-1,y_b-1),(x_b-1,y_b+1)$$

注意：两个棋子走边界的时候就走不动了。

如果某一个人的棋子走到了另一个棋子所在的位置那么另一个人就输掉了游戏。

如果两个人都走不到对方的位置，那么就是平局。

### 思路

这道题我们发现两个棋子之间 $x$ 坐标的距离决定着到底是谁吃谁。

如果是偶数则一定是先手吃后手，如果是奇数则一定是后手吃先手。

然后如果是先手吃后手的情况下，分三种情况讨论：

1. 如果后手在先手左边则后手一定一直往左边走，如果碰到边界就一直往前走，先手也一定往左边走，如果碰到边界就一直往前走，然后如果先手能走到最左边的位置比后手能走到最左边的位置要更靠左的话，后手就输了，否则就是平局。

2. 如果先手在后手右边跟后手在先手左边同理。

3. 如果先手跟后手在同一列则先手胜利。

如果是后手吃先手，跟先手吃后手同理。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define ll long long
#define ex exit(0)
#define _endl_ puts("");
#define inl inline
#define null NULL
#define pll pair<ll,ll>
#define mkp make_pair
using namespace std;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll t;
	cin >> t;
	while (t--) {
		ll h, w, xa, xb, ya, yb;
		cin >> h >> w >> xa >> ya >> xb >> yb;
		if (xa >= xb) {
			cout << "Draw\n";
			continue;
		}
		ll len = xb - xa - 1;
		if (len % 2 == 0) {
			if (yb == ya) {
				cout << "Alice\n";
				continue;
			}
			if (yb > ya) {
				ll bzuiyou = min(w, yb + len / 2);
				ll azuiyou = min(w, ya + len / 2 + 1);
				if (azuiyou >= bzuiyou) {
					cout << "Alice\n";
					continue;
				}
				cout << "Draw\n";
			} else {
				ll bzuizuo = max(1ll, yb - len / 2);
				ll azuizuo = max(1ll, ya - len / 2 - 1);
				if (azuizuo <= bzuizuo) {
					cout << "Alice\n";
					continue;
				}
				cout << "Draw\n";
			}
		} else {
			if (yb == ya) {
				cout << "Bob\n";
				continue;
			}
			if (yb < ya) {
				ll bzuiyou = min(w, yb + len / 2 + 1);
				ll azuiyou = min(w, ya + len / 2 + 1);
				if (bzuiyou >= azuiyou) {
					cout << "Bob\n";
					continue;
				}
				cout << "Draw\n";
			} else {
				ll bzuizuo = max(1ll, yb - len / 2 - 1);
				ll azuizuo = max(1ll, ya - len / 2 - 1);
				if (bzuizuo <= azuizuo) {
					cout << "Bob\n";
					continue;
				}
				cout << "Draw\n";
			}
		}
	}
	return 0;
}
~~~

---

