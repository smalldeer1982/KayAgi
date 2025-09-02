# Slice to Survive

## 题目描述

决斗者 Mouf 和 Fouad 进入了一个 $n \times m$ 的网格竞技场！

Fouad 的怪物初始位于单元格 $(a, b)$，其中行编号为 $1$ 到 $n$，列编号为 $1$ 到 $m$。

Mouf 和 Fouad 将持续决斗，直到网格仅剩一个单元格。

每个回合包含以下操作：
- Mouf 首先沿某行或列将网格切割成两部分，丢弃不包含 Fouad 怪物的部分。注意网格必须至少有两个单元格，否则游戏已经结束。
- 之后，在同一回合内，Fouad 将他的怪物移动到剩余网格中的任意单元格（可以保持原位）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2109B/d9a546edc6ef92fbb46a660c06ce426416f6bdbc.png) 第四个测试案例的可视化图示。

Mouf 希望最小化回合数，而 Fouad 希望最大化回合数。如果双方都采取最优策略，这场史诗级决斗将持续多少回合？

## 说明/提示

在第一个测试案例中，一种可能的决斗序列如下：
- 第 1 回合：Mouf 沿第 1 行和第 2 行之间的水平线切割网格，移除下半部分，留下 $1 \times 2$ 的网格。
- 第 1 回合：Fouad 的怪物位于单元格 $(1,1)$。
- 第 2 回合：Mouf 再次切割 $1 \times 2$ 网格，移除一列，最终隔离出单元格 $(1,1)$。

决斗在 $2$ 回合内完成。

在第四个测试案例中，一种可能的决斗序列如下：
- 第 1 回合：Mouf 沿第 2 列和第 3 列之间的垂直线切割网格，将其分为 $2 \times 2$ 和 $2 \times 5$ 两部分，然后移除 $2 \times 5$ 部分。
- 第 1 回合：Fouad 将怪物移动到单元格 $(1,1)$。
- 此后，决斗过程与第一个测试案例类似——再用两个回合将 $2 \times 2$ 网格缩减为 $1 \times 1$ 单元格。

总计，决斗在 $3$ 回合内完成。

可以参考题目描述中提到的图片来查看第四个测试案例的图示。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2 2 1 1
3 3 2 2
2 7 1 4
2 7 2 2
8 9 4 6
9 9 5 5
2 20 2 11
22 99 20 70```

### 输出

```
2
4
4
3
6
8
6
10```

# 题解

## 作者：john_01 (赞：3)

## 题目大意如下：

在一个 $ n \times m $ 的网格中，Fouad 的怪物起始位于位置 $ (a, b) $。

游戏规则是：

- 每一轮分为两个步骤：
  1. **`Mouf` 先行动**：他可以沿着一行或一列将当前的网格切成两半，并**丢弃不包含怪物的那一半**。注意，每次切割后必须保证剩下的部分至少还有两个格子（否则游戏结束）。
  2. **`Fouad` 接着行动**：他可以将怪物移动到剩余部分中的任意一个格子（包括原来的位置）。

目标：
- **`Mouf` 想让游戏尽可能快地结束**（即让剩下的格子只剩一个的速度最快）；
- **`Fouad` 想让游戏尽可能持续更久**（即延缓只剩一个格子的到来）。

问题：
- 当两人均采取最优策略时，这个游戏将持续多少轮？

---

简单来说：两人轮流操作，`Mouf`每次缩小区块，`Fouad`每次选择怪物新位置以尽量延长游戏。问最终游戏能进行几轮。

## 思路：
1. 考虑到在每一轮操作中，`Mouf`先切割使轮次最小（**即通过切割使怪兽所在位置距离边界最近**），`Fouad`后移动使轮次最大（**即通过移动使怪兽所在位置距离边界最远**）。
  
2. 将情况分为两类：  
  - 先切割行：通过切割**将怪兽留在距离边界较近的一边**。

    再切割列：此时`Fouad`已经通过移动将怪兽移动到距离边界最远的位置，因此**计算对于所有列的切割次数**。
  
  - 先切割列，再切割行，与上面的情况相反。
4. 最后对两种情况的轮次数取较小值 `+1`（第一次切割的次数）。


```cpp
#include <bits/stdc++.h> 
using namespace std;

void solve() {
	int n,m,a,b;
	cin>>n>>m>>a>>b;
    // 由于此处需要求可以二分的次数，因此需要向上取整
	int tol_col=ceil(log2(m)),tol_row=ceil(log2(n));
	int f_col=ceil(log2(min(m-b+1,b))),f_row=ceil(log2(min(n-a+1,a)));
	cout<<min(tol_col+f_row,tol_row+f_col)+1<<endl;
}

int main() {
	ios::sync_with_stdio(0);
	int T = 1;
	cin >> T;
	while (T--) solve();
}
```

---

## 作者：114514xxx (赞：0)

## 思路
我们可以注意到每次现将最多的行或列进行删除肯定是最优的。因此我们可以分类讨论先删除行还是列，并据此计算答案。

因为 Fouad 可以到未被删除的的任意区域，所以到中间肯定是最划算的，所以我们抓住 Fouad 就类似一个二分的过程，这个过程对于行和列是分别独立的。

因此我们就可以得到答案即为 $
\log_2n+\log_2{\min\{m-b+1,b\}}$ 或$
\log_2m+\log_2{\min\{n-a+1,a\}}$，对这两个答案取最小值即可，注意最后的答案要加 $1$，因为第一次删除也要计算。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+25;
const int inf=2e9;
int n,m,a,b;
inline void solve(){
    cin>>n>>m>>a>>b;
    int ans1=ceil(log2(m))+ceil(log2(min(n-a+1,a)));
    int ans2=ceil(log2(n))+ceil(log2(min(m-b+1,b)));
    cout<<min(ans1,ans2)+1<<'\n';
}
signed main(){
    srand(time(0));
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}

```

---

## 作者：chenbs (赞：0)

注意到，Mouf 第一次可以留下尽可能少的区域。而第二次及以后的操作时，最多只能切掉一半，证明如下。

不妨考虑切行的情况，设一共有 $n$ 行，Mouf 将它切为了 $x$ 行的部分和 $n-x$ 的部分。$\max \{x, n-x\} \ge \lceil \frac n 2 \rceil$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a,b;
int calc(int x, int y) {
	int cnt=0;
	while(x>1) x=(x>>1)+(x&1), cnt++;
	while(y>1) y=(y>>1)+(y&1), cnt++;
	return cnt;
}
int main(){
	cin>>t;
	while(t--) {
		cin>>n>>m>>a>>b;
		cout<<min({calc(a,m), calc(n-a+1,m), calc(n,b), calc(n,m-b+1)})+1<<'\n';
	}
	return 0;
}
```

---

