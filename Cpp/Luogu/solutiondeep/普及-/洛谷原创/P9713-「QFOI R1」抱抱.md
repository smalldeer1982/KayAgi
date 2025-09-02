# 题目信息

# 「QFOI R1」抱抱

## 题目描述

小 R 是一个可爱的女孩子，她希望跟大家抱抱，顺便给大家分蛋糕吃。

蛋糕是一个大小为 $a\times b\times c$ 的长方体，其中每个单位正方体都被赋予了一个坐标 $(x,y,z)$（$1\le x\le a,1\le y\le b,1\le z\le c$）。

共进行 $m$ 次切蛋糕操作，每次按如下三种方式之一切分：

1. 切出 $x\le k$ 的部分分给大家。
2. 切出 $y\le k$ 的部分分给大家。
3. 切出 $z\le k$ 的部分分给大家。

由于她自己也想吃蛋糕，她希望知道在每次切蛋糕后，还剩下多少体积没有分给大家。

## 说明/提示

**样例 $1$ 解释**

第一次切蛋糕，将所有 $x\le 2$ 的部分切掉，剩余的单位正方体有 $(3,1,1),(3,1,2),(3,1,3),(3,2,1),(3,2,2),(3,2,3),(3,3,1),(3,3,2),(3,3,3)$ 共 $9$ 个。

第二次切蛋糕，将所有 $y\le 1$ 的部分切掉，剩余的单位正方体有 $(3,2,1),(3,2,2),(3,2,3),(3,3,1),(3,3,2),(3,3,3)$ 共 $6$ 个。

---

**样例 $2$ 解释**

第四次切蛋糕没有任何作用，因为第二次切蛋糕时 $y\le 654321$ 的部分已经被切掉，此时已经不存在 $y\le 111111$ 的单位正方体。

注意每次操作中的参数 $k$ 是初始时决定的绝对坐标，不会随着操作的进行而改变。

---

**数据范围**

本题共 $20$ 个测试点，每个测试点 $5$ 分。

对于全部数据，保证 $1\le a,b,c\le 10^6$，$1\le m\le 2\times 10^5$，$op\in\{1,2,3\}$，若 $op=1$ 则 $1\le k\le a$，若 $op=2$ 则 $1\le k\le b$，若 $op=3$ 则 $1\le k\le c$。

- 对于测试点 $1\sim 5$：保证 $a,b,c,m\le 100$。
- 对于测试点 $6\sim 10$：保证 $b=c=1$，$op=1$。
- 对于测试点 $11\sim 15$：保证 $c=1$，$op\in\{1,2\}$。
- 对于测试点 $16\sim 20$：无特殊限制。

## 样例 #1

### 输入

```
3 3 3 2
1 2
2 1```

### 输出

```
9
6```

## 样例 #2

### 输入

```
1000000 1000000 1000000 6
1 123456
2 654321
3 233333
2 111111
1 333333
3 1000000```

### 输出

```
876544000000000000
303002853376000000
232302288589217792
232302288589217792
176680542935560631
0
```

# AI分析结果

• 综合分析与结论：这些题解的核心思路均基于每次操作后剩余蛋糕仍为长方体这一特性。通过记录每次操作在不同维度（x、y、z 方向）上的切割参数最大值，进而计算每次操作后剩余长方体的体积。算法要点在于维护各维度切割的最大参数值，难点在于理解每次操作中的参数 k 是绝对坐标，需避免重复计算已切除部分。多数题解思路清晰，代码实现差异不大，主要区别在于变量命名和代码简洁度。

所选的题解：
  - 作者：rui_er (5星)
    - 关键亮点：代码简洁明了，使用标准库函数和自定义函数，逻辑清晰，变量命名规范，易读性强。
    - 重点代码及核心实现思想：
```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int a, b, c, m, x, y, z;

int main() {
    for(scanf("%d%d%d%d", &a, &b, &c, &m); m; m--) {
        int op, k;
        scanf("%d%d", &op, &k);
        if(op == 1) chkmax(x, k);
        else if(op == 2) chkmax(y, k);
        else chkmax(z, k);
        printf("%lld\n", 1LL * (a - x) * (b - y) * (c - z));
    }
    return 0;
}
```
核心实现思想为每次读入操作和参数 k，根据操作类型更新对应维度的最大切割值（x、y 或 z），然后通过剩余长方体的长、宽、高计算并输出剩余体积。

  - 作者：hjqhs (4星)
    - 关键亮点：代码简洁，直接记录每次操作在各维度的最大值，使用常见的头文件和命名空间，易于理解。
    - 重点代码及核心实现思想：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,m;
int mx,my,mz;
signed main(){
	cin>>a>>b>>c>>m;
	for(int i=1;i<=m;++i){
		int op,k;
		cin>>op>>k;
		if(op==1)mx=max(mx,k);
		if(op==2)my=max(my,k);
		if(op==3)mz=max(mz,k);
		cout<<(a-mx)*(b-my)*(c-mz)<<'\n';
	}
	return 0;
} 
```
核心实现思想与 rui_er 的类似，通过 `max` 函数更新各维度最大切割值（mx、my、mz），再计算并输出剩余体积。

  - 作者：PineappleSummer (4星)
    - 关键亮点：思路阐述清晰，通过明确各维度剩余部分的计算方式，使读者更易理解代码逻辑。
    - 重点代码及核心实现思想：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,b,c,mx,my,mz;
int m;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>a>>b>>c>>m;
	while(m--)
	{
		int op;
		ll k;
		cin>>op>>k;
		if(op==1) mx=max(mx,k);
		else if(op==2) my=max(my,k);
		else mz=max(mz,k);
		cout<<(ll)(a-mx)*(b-my)*(c-mz)<<'\n';
	}
    return 0;
}
```
核心实现思想同样是在每次操作时更新各维度最大切割值（mx、my、mz），进而计算并输出剩余体积。

最优关键思路或技巧：利用每次操作后剩余蛋糕为长方体的特点，维护各维度切割参数的最大值，避免重复计算已切除部分，简化计算过程。

可拓展之处：此类题目属于模拟与几何结合的类型，类似套路可应用于其他涉及空间物体切割、合并后求剩余体积或其他属性的题目。例如在更高维度空间中，或切割操作更为复杂的场景下，同样可尝试通过记录关键参数来简化计算。

推荐洛谷题目：
1. P1031 [NOIP2002 提高组] 均分纸牌：涉及简单模拟和数学思维，与本题类似在于通过模拟操作来解决问题。
2. P1162 填涂颜色：结合图形模拟与边界处理，与本题在空间处理的思维方式上有相似之处。
3. P1260 动态统计：通过线段树等数据结构维护数据，与本题维护关键参数以简化计算的思路类似。

个人心得：无。 

---
处理用时：35.59秒