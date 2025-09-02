# 题目信息

# Powering the Hero (hard version)

## 题目描述

This is a hard version of the problem. It differs from the easy one only by constraints on $ n $ and $ t $ .

There is a deck of $ n $ cards, each of which is characterized by its power. There are two types of cards:

- a hero card, the power of such a card is always equal to $ 0 $ ;
- a bonus card, the power of such a card is always positive.

You can do the following with the deck:

- take a card from the top of the deck;
- if this card is a bonus card, you can put it on top of your bonus deck or discard;
- if this card is a hero card, then the power of the top card from your bonus deck is added to his power (if it is not empty), after that the hero is added to your army, and the used bonus discards.

Your task is to use such actions to gather an army with the maximum possible total power.

## 说明/提示

In the first sample, you can take bonuses $ 1 $ and $ 2 $ . Both hero cards will receive $ 3 $ power. If you take all the bonuses, one of them will remain unused.

In the second sample, the hero's card on top of the deck cannot be powered up, and the rest can be powered up with $ 2 $ and $ 3 $ bonuses and get $ 6 $ total power.

In the fourth sample, you can take bonuses $ 1 $ , $ 2 $ , $ 3 $ , $ 5 $ and skip the bonus $ 6 $ , then the hero $ 4 $ will be enhanced with a bonus $ 3 $ by $ 5 $ , and the hero $ 7 $ with a bonus $ 5 $ by $ 4 $ . $ 4+5=9 $ .

## 样例 #1

### 输入

```
5
5
3 3 3 0 0
6
0 3 3 0 0 3
7
1 2 3 0 4 5 0
7
1 2 5 0 4 3 0
5
3 1 0 0 4```

### 输出

```
6
6
8
9
4```

# AI分析结果

### 题目内容
# 助力英雄（困难版本）

## 题目描述
这是该问题的困难版本。它与简单版本的区别仅在于对 $n$ 和 $t$ 的约束条件。

有一副包含 $n$ 张牌的牌堆，每张牌都有其对应的力量值。牌分为两种类型：
- 英雄牌，此类牌的力量值始终为 $0$；
- 加成牌，此类牌的力量值始终为正数。

你可以对牌堆执行以下操作：
- 从牌堆顶部取出一张牌；
- 如果这张牌是加成牌，你可以将其放在你的加成牌堆顶部或丢弃；
- 如果这张牌是英雄牌，那么你的加成牌堆顶部牌的力量值会加到该英雄牌上（若加成牌堆不为空），之后该英雄牌加入你的军队，并且所使用的加成牌被丢弃。

你的任务是通过这些操作组建一支总力量值最大的军队。

## 说明/提示
在第一个样例中，你可以选取加成牌 $1$ 和 $2$ 。两张英雄牌都将获得 $3$ 点力量值。如果选取所有加成牌，其中一张将不会被使用。

在第二个样例中，牌堆顶部的英雄牌无法获得力量加成，其余英雄牌可以通过加成牌 $2$ 和 $3$ 获得加成，总力量值为 $6$ 。

在第四个样例中，你可以选取加成牌 $1$ 、$2$ 、$3$ 、$5$ 并跳过加成牌 $6$ ，然后英雄牌 $4$ 将通过加成牌 $3$ 获得 $5$ 点加成，英雄牌 $7$ 通过加成牌 $5$ 获得 $4$ 点加成。$4 + 5 = 9$ 。

## 样例 #1
### 输入
```
5
5
3 3 3 0 0
6
0 3 3 0 0 3
7
1 2 3 0 4 5 0
7
1 2 5 0 4 3 0
5
3 1 0 0 4```
### 输出
```
6
6
8
9
4```

### 算法分类
贪心

### 题解综合分析与结论
所有题解思路基本一致，均基于贪心策略，核心思想为每个英雄牌尽量获取前面未使用过的加成牌中的最大值。实现上都采用优先队列（大根堆）来维护加成牌，每次遇到英雄牌时，若优先队列非空，就取出队首（即当前最大加成值）累加到答案中，并将队首元素出队；遇到加成牌则将其加入优先队列。不同题解在代码风格、细节处理及注释详细程度上有差异。

### 所选的题解
 - **作者：_Haoomff_ (赞：3)**
    - **星级**：4星
    - **关键亮点**：代码简洁明了，逻辑清晰，直接在输入时进行判断处理，利用`priority_queue`实现核心逻辑。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll t,n,ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(;t--;){
		priority_queue<ll> q;
		ans=0;
		cin>>n;
		for(;n--;){
			int a;
			cin>>a;
			if(a==0){
				if(!q.empty()){
					ans+=q.top();
					q.pop();
				}
			}//这里的括号不加会出问题
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```
核心实现思想：输入每个数时判断是否为0（即是否为英雄牌），若是且优先队列非空，则累加队首值并出队；否则将数加入优先队列。
 - **作者：szhqwq (赞：1)**
    - **星级**：4星
    - **关键亮点**：分析了本题与简单版本数据范围的差异，明确指出使用优先队列（大根堆）解决问题的思路。
    - **重点代码**：无（未给出具体代码，仅阐述思路）
 - **作者：lfxxx (赞：0)**
    - **星级**：4星
    - **关键亮点**：先阐述贪心策略的原理，即每个英雄取前面最大未取的附加牌，然后用堆来实现该策略，代码结构清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
void work(){
    int ans=0;
    priority_queue<int> s;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x==0&&s.size()>0){
            ans+=s.top();
            s.pop();
        }
        else{
            s.push(x);
        }
    }
    cout<<ans<<'\n';
}
signed main(){
    cin>>T;
    while(T--) work(); 
}
```
核心实现思想：通过`work`函数实现核心逻辑，输入每个数判断是否为0，为0且堆非空则累加堆顶值并出堆，否则将数入堆。

### 最优关键思路或技巧
利用优先队列（大根堆）这种数据结构，高效维护当前可用加成牌中的最大值，每次遇到英雄牌时能快速获取最大加成值，符合贪心策略，时间复杂度为 $O(n\log n)$，相比于暴力寻找最大值的 $O(n^2)$ 有显著优化。

### 可拓展思路
同类型题通常围绕贪心策略，结合不同的数据结构考察。例如给定一系列任务，每个任务有完成时间和收益，在规定时间内完成任务获取最大收益等。类似算法套路是先分析问题性质，确定贪心策略，再根据具体操作（如动态获取最值、插入删除等）选择合适的数据结构（如堆、平衡树等）来实现。

### 洛谷推荐题目
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过合理分组实现贪心策略，与本题类似，需根据数据特点选择合适方法。
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及贪心策略与博弈思想，与本题一样需分析如何获取最优值。
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对数据排序实现贪心，和本题利用数据结构辅助贪心实现的思路类似。

### 个人心得摘录与总结
作者 _Haoomff_ 提到代码中括号不加会出问题，强调了代码细节的重要性，在条件判断嵌套时，括号的正确使用能避免逻辑错误。作者 Loser_Syx 提醒优先队列从大到小排序初始化的正确方式，避免因初始化错误导致结果错误，反映了对数据结构特性准确掌握的必要性。 

---
处理用时：52.56秒