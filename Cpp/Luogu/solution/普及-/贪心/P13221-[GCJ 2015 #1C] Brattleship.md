# [GCJ 2015 #1C] Brattleship

## 题目描述

你将和你的小弟弟玩一个简化版的“战舰”游戏。游戏的棋盘是一个有 $R$ 行 $C$ 列的矩形网格。在游戏开始时，你会闭上眼睛，并且直到游戏结束都不会睁开。你的小弟弟会在棋盘上放置一艘 $1 \times W$ 的矩形战舰，且只能**水平**放置。战舰必须完全放在棋盘内，每个船格正好占据棋盘的一个格子，且不能旋转。

游戏的每一回合，你可以指定棋盘上的一个格子，你的小弟弟会告诉你这个格子是否命中（即该格子是否被战舰占据）或未命中。（你的小弟弟不会告诉你命中的是战舰的哪一部分——只会告诉你该格子是否有船。）你有完美的记忆力，能记录下他给你的所有信息。当你已经指出了战舰占据的所有格子时，游戏结束（战舰被击沉），你的得分是你所用的回合数。你的目标是让得分尽可能小。

虽然战舰一旦放置后理论上不应移动，但你知道你的小弟弟会作弊，只要新的位置依然是水平且完全在棋盘内，并且与他之前给你的所有信息一致，他就会随时移动战舰。例如，在一个 $1 \times 4$ 的棋盘上放一艘 $1 \times 2$ 的战舰，他可以最初把船放在最左边的两列。如果你第一次猜 $(1,2)$，他可以偷偷把船移到最右边的两列，并告诉你 $(1,2)$ 是未命中。如果你下一步猜 $(1,3)$，他就不能再说未命中并把船移回原来的位置了，因为那样会和他之前说的 $(1,2)$ 是未命中矛盾。

不仅如此，你知道你的小弟弟会作弊，他也知道你知道。如果你们都采取最优策略（你想让得分最小，他想让得分最大），你**无论如何都能保证**的最小得分是多少？

## 说明/提示

**样例解释**

在第 1 个用例中，棋盘有一行四列，战舰占据一行两列。一种最优策略是你先猜 $(1,2)$：

如果你的小弟弟说命中，那么 $1 \times 2$ 的战舰的另一个格子只能在 $(1,1)$ 或 $(1,3)$，你只需分别猜这两个格子。如果你正好猜中了另一个格子，你的小弟弟会把船移到 $(1,2)$ 依然命中但你猜的那个格子未命中的位置。注意即使你已经命中，小弟弟依然可以移动船，只要不和之前的信息矛盾。

如果你的小弟弟说未命中，那么唯一剩下的可能就是船在 $(1,3)$ 和 $(1,4)$，你只需猜这两个格子。

所以无论小弟弟怎么做，在你猜 $(1,2)$ 后，最多再用两步就能结束，总共三步。

而且三步是最优的，因为你不可能保证用两步完成：无论你第一步猜哪里，小弟弟都可以把船移到剩下的 $1 \times 2$ 区域，并说未命中。你无法在只剩一步的情况下击沉还未被命中的船。

在第 2 个用例中，战舰完全填满棋盘，所以小弟弟只有一种放法。你只需把所有格子都猜一遍。

在第 3 个用例中，小弟弟总能把 $1 \times 1$ 的战舰移到你没猜过的格子，所以你必须把 10 个格子都猜一遍，最后一个才会命中并击沉战舰。

**限制条件**

- $1 \leq W \leq C$。

**小数据范围**

- 时间限制：5 秒。
- $T = 55$。
- $R = 1$。
- $1 \leq C \leq 10$。

**大数据范围**

- 时间限制：10 秒。
- $1 \leq T \leq 100$。
- $1 \leq R \leq 20$。
- $1 \leq C \leq 20$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 4 2
1 7 7
2 5 1```

### 输出

```
Case #1: 3
Case #2: 7
Case #3: 10```

# 题解

## 作者：Batboyh (赞：3)

## 思路

假设只有一行（简化题目）  
- 在 $c \mod w = 0$ 的情况下，我们每隔 $w$ 猜一次，在最坏情况下就能在第 $c / w$ 次将船锁定在最后一段。
- 在 $c \mod w \ne 0$ 的情况下，在第 $c / w$ 次将船锁定在最后时，去判断两侧的格子，这时就需要多判断一次。

对于多行情况，就是要排除其他 $r - 1$ 没有船的行，而每行都需要判断 $c / w$ 次

详见代码

## AC代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(); // 快读

signed main()
{
	int T = read(), tot = 0; // tot 计数
	while (T--)
	{
		int r = read(), c = read(), w = read();
		int s = r * ( c / w); // 对于多行情况，每行要判断 c/w 次，共 r 行，故为 r * ( c / w)，s存储答案
		//在锁定船在哪一行之后，计算船在当前行需要额外判断的次数
		if (c % w == 0) // 能整除，就多判断 w-1 次。因为，每一行都判断了 c/w 次，而船长 w，所以只要再加上 w-1
			s += w - 1;
		else            // 不能整除，就要比能整除的情况多1次
			s += w;
		printf("Case #%lld: %lld\n", ++tot, s); // 按照题目要求输出
	}
	return 0;
}

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
```

---

## 作者：alice_c (赞：2)

## 思路

当 $R=1$ 时，棋盘只有一行，最优策略是通过在棋盘上每隔 $W$ 个格子选择一个位置进行猜测，确保每个战舰肯能在的位置都有一个格子被覆盖，从而最小化未命中次数，共猜测 $\lfloor \frac{C}{W} \rfloor$ 遍。当 $R>1$ 时，直接乘 $R$ 即可。

在我们第一次命中战舰后，至少还需要 $W-1$ 次操作才能胜利，因为我们需要命中战舰所有剩余的部分。

当 $C \bmod W \ne 0$，会有剩余的列，仍然有可能包含战舰的某个部分，因此需要额外进行一次猜测。

## 代码

代码非常简单。

时间复杂度 $O(1)$，~~不知道这道题时间为什么给这么长。~~

```cpp
#include <cstdio>
int t,r,c,w,ans;
int main()
{
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        scanf("%d%d%d",&r,&c,&w);
        ans=r*(c/w);
        ans+=w-1;
        if(c%w) ans++;
        printf("Case #%d: %d\n",i,ans);
    }
}
``````

---

## 作者：huangyuze114514 (赞：1)

### 思路
由题得战舰只会占一行 $W$ 列而不会占多行，所以我们需要遍历每一行来找到战舰的位置。因为战舰长 $W$，因此我们只需每 $W$ 个格子查询一次就能找到战舰的位置，即查询 $\left\lfloor\dfrac{C}{W}\right\rfloor$ 次。又因为有 $R$ 行，所以要遍历 $R×\left\lfloor\dfrac{C}{W}\right\rfloor$ 次。

在得知战舰的位置后，需要 $W-1$ 次来遍历其他格子。但如果 $W$ 无法整除 $C$，那么还要再多遍历一次来确认位置。

综上，如果 $C$ 除以 $W$ 没有余数，答案为 $R×\left\lfloor\dfrac{C}{W}\right\rfloor+W-1$，否则为$R×\left\lfloor\dfrac{C}{W}\right\rfloor+W$。
### 代码如下

```cpp
#include<iostream>
using namespace std;
int main(){
	int t,r,c,w;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>r>>c>>w;
		int ans=r*(c/w)+w-1;
		if(c%w)ans++;
		cout<<"Case #"<<i<<": "<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：RN_GH (赞：1)

一看到博弈论就来劲了！！！

[AC record](https://www.luogu.com.cn/record/225488894)
# 一、问题描述

给定 $R\times C$ 的网格和长度为 $W$ 的战舰，战舰水平放置且不重叠。每次猜测一个格子，会返回命中或未命中。求在最坏情况下确定战舰位置所需的最小猜测次数。

# 二、算法思路
分块策略：将每行分为长度为 $W$ 的块（最后一块可能不足）。

每行需要 $\lceil \frac{C}{W} \rceil$ 次扫描确定战舰所在块。

共R行，所以需要 $R \times \lfloor \frac{C}{W} \rfloor$ 次基础扫描。

精确定位：确定具体位置需要额外 $W-1$ 次猜测。

因为最坏情况下需要逐个检查块内的 $W$ 个位置。

边界处理：当 $C$ 不是 $W$ 的整数倍时。

最后余数部分需要额外一次猜测（战舰可能跨两个块）。

写作代码就是：
```cpp
min_guesses = R * (C / W) + (W - 1) + (C % W != 0 ? 1 : 0)
```
# 四、AC代码


```cpp
#include <bits/stdc++.h>
using namespace std;

int guess(int R, int C, int W) {
	// 每行需要的基本猜测次数：将列分成W长度的块
	int perRow = C / W;
	
	// 基础公式：行数×每行块数 + (战舰长度-1)
	int result = R * perRow + (W - 1);
	
	// 处理不能整除的情况：需要额外一次猜测
	if (C % W != 0) {
		result += 1;
	}
	return result;
}

int main() {
	int T;
	cin >> T;
	
	for (int t = 1; t <= T; ++t) {
		int R, C, W;
		cin >> R >> C >> W;
		cout << "Case #" << t << ": " << guess(R, C, W) << endl;
	}
	return 0;
}
```

---

## 作者：Stardust_Mirage (赞：1)

### 题目
[link](https://www.luogu.com.cn/problem/P13221)

### 解题思路
博弈论。

**分类讨论：**

 $W$ 表示战舰长度，棋盘为 $R$ 行 $C$ 列。

先考虑最简单的情况
-  $W = 1$ ：战舰占据一个点，必须猜所有点才能击沉战舰。答案为 $ R × C$ 。

-  $W = C$ ：战舰占满一行。先在前  $R-1$  行各猜一个点，然后在最后一行猜所有  $C$  个点。答案为  $R-1+W$ 。

再思考将问题转换到全局。由于弟弟采用最优策略且说的话不会矛盾，考虑如何用尽量少的次数，使弟弟无法将战舰继续移动。
-  $1 < W < C$ ：

    -  $R = 1$ ：将一行分为若干段，每段长度不超过 $ W$ ，总共有 $\left \lceil \frac{C}{W}  \right \rceil $ 段。先猜  $W$ ,  $2W$   $\dots$   $kW$ 的点，其中 $k< \left \lfloor \frac{C-1}{W}  \right \rfloor $ ，共猜  $\left \lfloor \frac{C-1}{W}  \right \rfloor $  次，若 $W \mid  C$ ,则将最后一段猜完即可找出。
 否则在最后两段从 $\left \lfloor  \frac{C}{W}   \right \rfloor \times W $ 的位置向两边猜，答案为  $\left \lfloor \frac{C-1}{W}  \right \rfloor +W$ 。

   -  $R > 1$ ：前  $R-1$  行每行猜 $W$  , $2W$ $\dots$ $kW$ ，其中 $k< \left \lfloor \frac{C}{W}  \right \rfloor $ ，以确保战舰被放到最后一行，共猜 $(R-1)\times\left \lfloor \frac{C}{W}  \right \rfloor$  个点。最后一行按  $R=1 $ 的策略处理。答案为 $(R-1)\times \left \lfloor \frac{C}{W}  \right \rfloor+\left \lfloor \frac{C-1}{W}  \right \rfloor +W$。
 
时间复杂度   $  \mathcal{O}(1) $ 。


### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main() {
    cin >> t; 
    for (int i = 1, r, c, w; i <= t; i++) {
        cin >> r >> c >> w;
        int ans;
        if (w == 1) {
            // 战舰宽度为1：必须猜所有格子
            ans = r * c;
        }
        else if (w == c) {
            // 战舰占满一行：前r-1行每行猜一次，最后一行猜所有格子
            ans = (r - 1) + w;
        }
        else {
            if (r == 1) {
                // 单行情况：先定位段，再在段内猜
                ans = (c - 1) / w + w;
            }
            else {
                // 多行情况：
                // 前r-1行每行猜 c/w 个点
                // 最后一行按单行处理
                ans = (r - 1) * (c / w) + (c - 1) / w + w;
            }
        }
        cout << "Case #" << i << ": " << ans << endl;
    }
    return 0;
}
```

---

## 作者：hezhiran (赞：1)

[通过记录](https://www.luogu.com.cn/record/224842740)

## 题意

有一个行数为 $r$，列数为 $c$ 的棋盘，其中有一个 $1 \times w$ 的军舰，你可以指定一个坐标 ，你的小弟弟会告诉你那里有没有军舰，但是只要可以，他会在不与之前的条件矛盾的情况下将军舰移开，两人都已最优策略进行，求指出所有军舰所在地所需最小回合数。

## 思路

让我们来观察一下这个图：~~（有点抽象）~~

![](https://cdn.luogu.com.cn/upload/image_hosting/9qtz49xy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$r$ 为 $1$，$c$ 为 $4$，$w$ 为 $2$，当我们指向 $(1,2)$，$(1,1)$ 和 $(1,2)$ 为军舰时，小弟弟会将军舰移至 $(1,3)$ 和 $(1,4)$，第二回合我们指向 $(1,3)$，小弟弟无法移动，此时回合数刚好为 $\lfloor c / w \rfloor$，我们将这个值乘上 $r$ 就是每一行的情况之和，最后，这个值还要加上找到所有战舰的回合数，即 $w$，但是，此时如果 $w$ 整除 $c$，说明在 $\lfloor c / w \rfloor$ 中我们已经找到了一个有军舰的位置，我们就还要减 $1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int t;
int tj[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin >> t;
	for(int q = 1; q <= t; q++){
		int r, c, w; cin >> r >> c >> w;
		cout << "Case #" << q << ": " <<  (c / w) * r + w - (c % w == 0) << '\n';
	}
	return 0;
}
```

---

## 作者：zybgml (赞：1)

题目链接：[P13221 [GCJ 2015 #1C] Brattleship](https://www.luogu.com.cn/problem/P13221)

---
这题代码不长，主要靠 **博弈论** 模拟找规律。我们来一步一步推导： 

## 推导过程
我们设有棋盘有 $r$ 行，$c$ 列，战舰宽为 $w$。
### 击中战舰所需回合数的推导 
1.在 $r=1$ 的情况下（如下图），我们至少需要 $c/w$ 个回合才能**击中**战舰。
![](https://cdn.luogu.com.cn/upload/image_hosting/r03gsqgl.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/w3wdr3lg.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/6zwmdf6q.png)

### 击沉战舰所需回合数的推导
而**击沉**的推导较为复杂，我们需要分类讨论：
- 如果 $c\bmod w=0$ 说明我们是在第 $c$ 列**击中**战舰，弟弟无法犯规，我们只需在再用 $w-1$ 个回合即可将弟弟的战舰**击沉**。（如上图）
- 反之说明我们在击中战舰后，弟弟还有犯规的用来移动战舰的空间，必须在击中战舰的下一列再消耗一回合防止弟弟犯规，所以我们共需要 $w$ 回合才能将弟弟的战舰**击沉**。（如下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/6vu7spga.png)

## 总结推导公式
2.在多行的情况下，我们需要用 $r\times\lfloor c\div w\rfloor$  回合才能**击中**战舰，如果 $c\bmod w=0$ 需要 $w-1$ 个回合将弟弟的战舰**击沉**，如果 $c\bmod w\ne0$ 需要 $w$ 个回合将弟弟的战舰**击沉**。

终于推导出公式了！  
代码实现也十分简单：

## 详细代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;//t表示测试用例数
int r,c,w;//r,c,w分别表示棋盘的行数,列数和战舰的宽度.
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>r>>c>>w;
        int ans;//ans代表答案
        ans=(c/w)*r;//计算击中战舰所需回合
        if(c%w==0) ans+=w-1;
        else ans+=w;//计算击沉战舰所需回合
        cout<<"Case #"<<i<<": "<<ans<<endl;
        //注意输出格式
    }
    return 0;
}
```

---

## 作者：tujiaqi12 (赞：0)

## 思路
大体思路：先通过几个回合使得战舰无法移动，同时得到战舰的位置。接着再用几个回合访问船所在的位置。

若 $c$ 是 $w$ 的倍数，可以访问每一排的第 $w,2w,3w…r$ 个格子，再用 $w - 1$ 次机会访问船所在的位置。

若 $c$ 不是 $w$ 的倍数，与上面的情况的唯一差别是需要用 $w$ 次机会访问船所在的位置。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t,r,c,w;
int main(){
	scanf("%lld",&t);
	for(ll i = 1;i <= t;i++){
		scanf("%lld%lld%lld",&r,&c,&w);
		if(c % w){
			printf("Case #%lld: %lld\n",i,(c / w) * r + w);//不整除 
		}
		else{
			printf("Case #%lld: %lld\n",i,(c / w) * r + (w - 1));//整除
		}
	}
	return 0;
}
```

---

## 作者：yangdezuo (赞：0)

## 解析
### 题目大意
计算在最优策略下，玩家保证能够击沉战舰所需的最小步数。

游戏规则是战舰水平放置在网格的某一行，玩家每次猜一个格子，弟弟会告知是否命中，且弟弟可以作弊移动战舰，只要移动后的位置与之前的所有回答一致。玩家和弟弟都采取最优策略，玩家希望最小化步数，弟弟希望最大化步数。

### 分析
我们需要从两个角度切入：
1. **确定战舰所在的行**：玩家需要在所有行上进行系统性的猜测，以定位战舰在哪一行。最优策略是在每一行上按战舰宽度 $W$ 的间隔进行猜测，直到在某一行的某个位置命中。最坏情况下，需要扫描所有行，每行需要猜测 $\left\lfloor \frac{C}{W} \right\rfloor$ 次。
2. **在确定行后击沉战舰**：一旦在某一行的位置 $x$ 命中，战舰必须覆盖 $x$。此时，需要进一步确定战舰的具体位置。已知战舰宽度为 $W$，且覆盖 $x$，则战舰可能的位置有 $W$ 种。玩家需要继续猜测，最坏情况下需要额外 $W$ 步，但可以通过公式优化为 $(W - 1)$ 步，若列数 $C$ 不能被 $W$ 整除，则还需额外一步。

### 总结
综合上述两部分，总步数计算公式为：
- 基本步数：$\left\lfloor \frac{C}{W} \right\rfloor \times R + (W - 1)$。
- 额外步数：若列数 $C$ 不能被 $W$ 整除，则额外加一步。


## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,r,c,w,ans;
signed main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>t;
    for(int o=1;o<=t;o++){
        cin>>r>>c>>w;
        ans=(c/w)*r+(w-1);
        if(c%w!=0) ans++;//c 不能被 w 整除
        cout<<"Case #"<<o<<": "<<ans<<'\n';
    }
}
```

---

## 作者：Chenxuhang_play (赞：0)

记第 $i$ 行，第 $j$ 列的格子记为 $(i,j)$。

当 $R=1$ 时，显然可以有一种最优算法：从 $(1,1)$ 开始，每 $W$ 个格子遍历一次，即遍历格子 $(1,W),(1,2W),\dots,(1,\left\lfloor\dfrac{C}{W}\right\rfloor\times W)$），最坏情况下遍历 $\left\lfloor\dfrac{C}{W}\right\rfloor$ 次，找到了战舰的位置后还需要 $W$ 次遍历战舰的所有格子。若 $C$ 是 $W$ 的倍数，则会少用一次遍历（不用判断战舰是在左侧还是右侧）。

可以由此推出当 $R>1$ 时需要遍历的格子次数，若 $C$ 是 $W$ 的倍数：$R\times\left\lfloor\dfrac{C}{W}\right\rfloor+W-1$。若 $C$ 不是 $W$ 的倍数，则需要遍历 $R\times\left\lfloor\dfrac{C}{W}\right\rfloor+W$ 次。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long t,a,b,c;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>a>>b>>c;
		if(b%c==0) cout<<"Case #"<<i<<": "<<a*(b/c)+c-1<<endl;
		else cout<<"Case #"<<i<<": "<<a*(b/c)+c<<endl;
	}
	return 0;
}
```

---

## 作者：_____1__2___ (赞：0)

# 题解：P13221 [GCJ 2015 #1C] Brattleship

这道题可以拆分来理解，对于每一行，战舰最多可以覆盖一行的数量就是 $\left \lfloor \frac{c}{w}  \right \rfloor  $。那么对于r列，就会有 $r \cdot \left \lfloor \frac{c}{w}  \right \rfloor$ 种。

当他找到可能后，还需要 $w-1$ 次确认，如果行数除不尽小船长度，那么应该在增加一次确认。

故代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int i=1;i<=T;i++) {
		int r,w,c;
		cin >> r >> c >> w;
		int line=c/w;
		int ans=r*line+w-1;
		if (c%w) line++;
		cout << "Case #" << i << ": " << ans << '\n';
	}
	return 0;
}
```

---

