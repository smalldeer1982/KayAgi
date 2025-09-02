# 题目信息

# [ARC171B] Chmax

## 题目描述

对于一个 $1$ 到 $N$ 的排列 $P=(P_1,P_2,\cdots,P_N)$，如下定义 $F(P)$：

- 初始序列 $B=(1,2,\cdots,N)$。只要有一个整数 $i$ 令 $B_i<P_{B_i}$ 存在，就进行下面的操作：
    - 找到最小的满足 $B_j<P_{B_j}$ 的整数 $j$，则将 $B_j$ 替换为 $P_{B_j}$。
  
  将 $F(P)$ 定义为这一过程结束时的 $B$（可以证明这个过程会在有限步数后终止）。

给你一个长度为 $N$ 的序列 $A=(A_1,A_2,\cdots,A_N)$，请问有多少个 $1$ 到 $N$ 的排列 $P$ 满足 $F(P) = A$？答案对 $998244353$ 取模。

## 说明/提示

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq N$
- 所有的输入都是整数。

## 样例 #1

### 输入

```
4

3 3 3 4```

### 输出

```
1```

## 样例 #2

### 输入

```
4

2 2 4 3```

### 输出

```
0```

## 样例 #3

### 输入

```
8

6 6 8 4 5 6 8 8```

### 输出

```
18```

# AI分析结果

### 题解综合分析与结论
这些题解的核心思路都是将问题转化为图论问题，通过对图的性质分析来确定排列 $P$ 的限制条件，进而计算满足 $F(P) = A$ 的排列个数。

#### 思路对比
- **建图分析**：多数题解都将 $i$ 到 $P_i$ 连边构建有向图，由于 $P$ 是排列，图由若干环组成。通过分析图中边和点的性质，确定 $A$ 序列对应的图的合法条件。
- **无解判断**：普遍认为存在 $A_i < i$ 或存在 $A_i\ne i$ 但 $A_j = i$ 等情况时无解。
- **计数方法**：确定部分位置的 $P$ 值唯一后，计算剩余位置的排列方案数，通常采用乘法原理，统计可选择的元素个数并累乘。

#### 算法要点对比
- **标记与统计**：使用数组标记元素的出现情况、入度、出度等信息，统计未使用的元素个数。
- **顺序处理**：从前往后或从后往前遍历序列，逐步确定每个位置的取值和可选择的方案数。

#### 解决难点对比
- **确定唯一边**：分析出 $A_i$ 相同的点在图中的连边关系，确定部分边是唯一的。
- **处理自由点**：找出对答案有贡献的“自由点”（如 $A_i = i$ 的点），并确定其取值范围和选择方案。

#### 评分
- **rui_er**：4星。思路清晰，代码简洁，直接明了地实现了核心逻辑。
- **是青白呀**：4星。详细解释了建图和分析的过程，代码规范，注释丰富。
- **GI录像机**：3星。通过打表猜测结论并证明，思路有一定创新性，但代码实现稍显复杂。

### 所选题解
- **rui_er（4星）**
    - **关键亮点**：思路简洁直接，代码实现高效，通过简单的数组标记和遍历完成计数。
- **是青白呀（4星）**
    - **关键亮点**：对建图和推理过程解释详细，便于理解，代码结构清晰。

### 重点代码
#### rui_er 的核心代码
```cpp
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)

typedef Modint<998244353> mint;

int n, a[N], lst[N], vis[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    per(i, n, 1) {
    	if(a[i] < i) {
    		cout << 0 << endl;
    		return 0;
    	}
    	if(lst[a[i]]) vis[lst[a[i]]] = 1;
    	else if(i != a[i]) {
    		cout << 0 << endl;
    		return 0;
    	}
    	lst[a[i]] = i;
    }
    mint cnt = 0, ans = 1;
    rep(i, 1, n) {
	    cnt += !vis[i];
    	if(i == a[i]) {
	    	ans *= cnt;
	    	--cnt;
	    }
    }
    cout << ans << endl;
    return 0;
}
```
**核心实现思想**：先从后往前遍历 $A$ 序列，判断无解情况并标记部分位置。然后从前往后遍历，统计未使用的元素个数，对于 $A_i = i$ 的位置，将可选择的方案数乘入答案并更新计数。

#### 是青白呀的核心代码
```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) lson[x]
#define rs(x) rson[x]
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
const int N=2e5+5,mo=998244353,inf=1e18+7;
typedef long long ll;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,a[N],nxt[N],ans=1;
bool st[N],endp[N],la[N];
signed main(){
	read(n);
	rep(i,1,n)
	    read(a[i]),endp[a[i]]=1;
	rep(i,1,n){
		if(endp[i]&&a[i]!=i){
			printf("0");
			return 0;
		}
		if(a[i]<i){
			printf("0");
			return 0;
		}
		if(!la[a[i]])la[a[i]]=1,st[i]=1;
	}
	int cnt=0;
	rep(i,1,n){
		if(st[i])cnt++;
		if(a[i]==i)ans=ans*cnt%mo,cnt--;
	}
	printf("%lld\n",ans);
	return 0;
}
```
**核心实现思想**：先读取输入，标记每个值是否为终点。然后判断无解情况，标记首次出现的元素。最后从前往后遍历，统计未使用的元素个数，对于 $A_i = i$ 的位置，将可选择的方案数乘入答案并更新计数。

### 最优关键思路或技巧
- **图论建模**：将排列问题转化为图论问题，通过分析图的性质确定排列的限制条件，使问题更直观。
- **分类讨论**：明确无解情况和有解时各位置的取值规则，简化问题的处理过程。
- **乘法原理计数**：在确定部分位置取值唯一后，通过统计可选择的元素个数，利用乘法原理计算排列方案数。

### 可拓展之处
同类型题或类似算法套路包括：
- **排列组合与图论结合**：涉及排列的限制条件和图的性质分析的问题，如计算满足特定条件的图的生成树个数。
- **计数问题的优化**：在计算排列方案数时，可考虑使用组合数学的方法或动态规划进行优化。

### 推荐洛谷题目
1. [P1087 FBI树](https://www.luogu.com.cn/problem/P1087)：考察递归和图论的基本思想。
2. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：涉及图的遍历和状态转移。
3. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：需要分析图的性质并进行计数。

### 个人心得摘录与总结
- **OldDriverTree**：赛时因为没特判 $A_{A_i}>A_i$ 的情况罚了11发还没调出来。总结是在解题时要全面考虑各种边界情况，对特殊情况进行仔细分析和特判，避免因细节问题导致错误。

---
处理用时：51.96秒