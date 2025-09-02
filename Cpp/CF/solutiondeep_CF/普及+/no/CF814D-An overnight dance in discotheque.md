# 题目信息

# An overnight dance in discotheque

## 题目描述

The crowdedness of the discotheque would never stop our friends from having fun, but a bit more spaciousness won't hurt, will it?

The discotheque can be seen as an infinite $ xy $ -plane, in which there are a total of $ n $ dancers. Once someone starts moving around, they will move only inside their own movement range, which is a circular area $ C_{i} $ described by a center $ (x_{i},y_{i}) $ and a radius $ r_{i} $ . No two ranges' borders have more than one common point, that is for every pair $ (i,j) $ ( $ 1<=i&lt;j<=n $ ) either ranges $ C_{i} $ and $ C_{j} $ are disjoint, or one of them is a subset of the other. Note that it's possible that two ranges' borders share a single common point, but no two dancers have exactly the same ranges.

Tsukihi, being one of them, defines the spaciousness to be the area covered by an odd number of movement ranges of dancers who are moving. An example is shown below, with shaded regions representing the spaciousness if everyone moves at the same time.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814D/5a49565ef74e61d7b40ab12eaa412e67e7b6d97c.png)But no one keeps moving for the whole night after all, so the whole night's time is divided into two halves — before midnight and after midnight. Every dancer moves around in one half, while sitting down with friends in the other. The spaciousness of two halves are calculated separately and their sum should, of course, be as large as possible. The following figure shows an optimal solution to the example above.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814D/8da25989c38168302d4efff7470ec1e71f4e2366.png)By different plans of who dances in the first half and who does in the other, different sums of spaciousness over two halves are achieved. You are to find the largest achievable value of this sum.

## 说明/提示

The first sample corresponds to the illustrations in the legend.

## 样例 #1

### 输入

```
5
2 1 6
0 4 1
2 -1 3
1 -2 1
4 -1 1
```

### 输出

```
138.23007676
```

## 样例 #2

### 输入

```
8
0 0 1
0 0 2
0 0 3
0 0 4
0 0 5
0 0 6
0 0 7
0 0 8
```

### 输出

```
289.02652413
```

# AI分析结果

### 题目翻译
# 迪斯科舞厅的通宵舞会

## 题目描述
迪斯科舞厅的拥挤丝毫不会影响我们朋友们享受欢乐时光，但是，多一些空间也没什么坏处，不是吗？

迪斯科舞厅可以看作是一个无限的 xy 平面，里面总共有 n 个舞者。一旦有人开始移动，他们只会在自己的移动范围内移动，这个移动范围是一个圆形区域 \(C_i\)，由圆心 \((x_i, y_i)\) 和半径 \(r_i\) 描述。任意两个范围的边界最多只有一个公共点，也就是说，对于每一对 \((i, j)\)（\(1 \leq i < j \leq n\)），要么范围 \(C_i\) 和 \(C_j\) 不相交，要么其中一个是另一个的子集。注意，有可能两个范围的边界共享一个公共点，但没有两个舞者的移动范围完全相同。

作为舞者之一的月火，将空间宽敞度定义为正在移动的舞者的移动范围中被奇数个范围覆盖的区域面积。下面展示了一个例子，如果所有人同时移动，阴影区域就代表空间宽敞度。
![示例图1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814D/5a49565ef74e61d7b40ab12eaa412e67e7b6d97c.png)
但毕竟没有人会整晚都在移动，所以一整晚的时间被分为两半——午夜前和午夜后。每个舞者在其中一半时间移动，而在另一半时间和朋友们坐在一起。两个半场的空间宽敞度分别计算，当然，它们的总和应该尽可能大。下图展示了上述例子的一个最优解。
![示例图2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814D/8da25989c38168302d4efff7470ec1e71f4e2366.png)
通过不同的安排，即谁在第一个半场跳舞，谁在另一个半场跳舞，可以得到不同的两个半场空间宽敞度总和。你需要找出这个总和的最大可实现值。

## 说明/提示
第一个样例对应图例中的插图。

## 样例 #1
### 输入
```
5
2 1 6
0 4 1
2 -1 3
1 -2 1
4 -1 1
```
### 输出
```
138.23007676
```

## 样例 #2
### 输入
```
8
0 0 1
0 0 2
0 0 3
0 0 4
0 0 5
0 0 6
0 0 7
0 0 8
```
### 输出
```
289.02652413
```

### 算法分类
贪心

### 综合分析与结论
本题主要探讨如何将舞者的移动范围（圆形区域）合理分配到两个半场，以使两个半场的空间宽敞度总和最大。各题解主要围绕贪心策略和动态规划展开，核心在于处理圆之间的包含关系，并根据覆盖次数的奇偶性来确定圆的分配方式。

### 所选的题解
- **作者：ljk123（5星）**
  - **关键亮点**：提出简洁且有效的贪心结论，即只将覆盖次数为2的圆放到另一组，并通过详细的分类讨论证明了该结论的正确性，代码实现简洁明了。
  - **个人心得**：无
  - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1006;
int n,cnt=0,f[N],rr[N],head[N];
struct edge{int nxt,to;}e[N];
struct circle{long long x,y,r;}o[N];
double ans=0.00,pai=3.1415926535898;
inline void add(int u,int v){e[++cnt].nxt=head[u],e[cnt].to=v,head[u]=cnt;}
inline int read(){
   int T=0,F=1; char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-') F=-1; ch=getchar();}
   while(ch>='0'&&ch<='9') T=(T<<3)+(T<<1)+(ch-48),ch=getchar();
   return F*T;
}
bool check(int u,int v){
     double t=sqrt((o[u].x-o[v].x)*(o[u].x-o[v].x)+(o[u].y-o[v].y)*(o[u].y-o[v].y));
     return (1.0000*o[v].r>=t+o[u].r);
}
void dfs(int u,int d,long long v){
     if(d==2) v*=-1;
     ans+=v*pai*o[u].r*o[u].r;
     for(int i=head[u];i;i=e[i].nxt) dfs(e[i].to,d+1,-v); 
}
bool cmp(circle u,circle v){return u.r>v.r;}
int main(){
    n=read();
    for(int i=1;i<=n;++i) f[i]=n+1,rr[i]=1e7,o[i].x=read(),o[i].y=read(),o[i].r=read();
    sort(o+1,o+n+1,cmp);
    for(int i=1;i<=n;++i)
        for(int j=1;j<i;++j)
            if(check(i,j)&&o[j].r<rr[i]) f[i]=j,rr[i]=o[j].r;
    for(int i=1;i<=n;++i) add(f[i],i);
    dfs(n+1,0,-1),printf("%.9lf",ans);
    return 0;
} 
```
核心实现思想：先根据圆的半径从大到小排序，构建圆之间的包含关系树（通过`add`函数），然后利用深度优先搜索`dfs`，根据贪心结论计算答案，在`dfs`中根据深度判断是否改变圆面积的贡献符号。

- **作者：皎月半洒花（4星）**
  - **关键亮点**：不仅给出贪心解法，还提供了动态规划解法，并针对不同数据规模选择不同解法。贪心策略直观，动态规划思路清晰，代码注释详细。
  - **个人心得**：认为本题难度不应为黑题，本应是蓝色难度。
  - **核心代码片段 - 贪心**：
```cpp
namespace Greedy{
	inline bool Comp(C A, C B){ return A.r > B.r ; }
	void solve2(){
		sort(base + 1, base + N + 1, Comp) ;
		for (i = 1 ; i <= N ; ++ i) 
			for(j = i + 1 ; j <= N ; ++ j)
				if (check_in(base[i], base[j])) ++ mark[j] ;
		for (i = 1 ; i <= N ; ++ i) 
			if (!mark[i] || (mark[i] & 1)) Ans += get_S(base[i]) ; else Ans -= get_S(base[i]) ;
		printf("%.8lf", Ans) ;  	
	}
}
```
核心实现思想：先按半径从大到小排序，通过`check_in`函数判断圆的包含关系，统计每个圆的覆盖次数`mark`，最后根据贪心策略，对覆盖次数为奇数或无覆盖的圆面积做加法，覆盖次数为偶数的圆面积做减法，得到答案。

  - **核心代码片段 - 动态规划**：
```cpp
namespace DP{
	#define to(k) E[k].to
	struct Edge{
		int next, to ;
	}E[MAXN << 1] ;
	int head[MAXN], cnt ;
	inline void Add(int u, int v){
    	E[++ cnt].to = v, E[cnt].next = head[u], head[u] = cnt ;
    	E[++ cnt].to = u, E[cnt].next = head[v], head[v] = cnt ;
	}
	void do_dp(int u, int faa){
		long long f[2][2] ; memset(f, 0, sizeof(f)) ;
		for (int k = head[u] ; k ; k = E[k].next){
			if (to(k) == faa) continue ;
			do_dp(to(k), u) ;
			for (int ii = 0 ; ii <= 1 ; ++ ii)
				for (int jj = 0 ; jj <= 1 ; ++ jj)
					f[ii][jj] += dp[to(k)][ii][jj] ; 
		}
		for (int ii = 0 ; ii <= 1 ; ++ ii)
			for (int jj = 0 ; jj <= 1 ; ++ jj)
				dp[u][ii][jj] = max(f[ii ^ 1][jj] + (1ll * (ii? -1 : 1) * base[u].r * base[u].r), 
									f[ii][jj ^ 1] + (1ll * (jj? -1 : 1) * base[u].r * base[u].r)) ;
	}
	inline bool Comp(C A, C B){ 
		return A.r > B.r ; }
	void solve1(){
		sort(base + 1, base + N + 1, Comp) ;
		for (i = 1 ; i <= N ; ++ i) 
			for(j = i + 1 ; j <= N ; ++ j)
				if (check_in(base[i], base[j])) 
					if (!fa[j] || base[fa[j]].r > base[i].r) fa[j] = i ;
		for (i = 1 ; i <= N ; ++ i) if (fa[i]) Add(i, fa[i]) ;	
		for (i = 1 ; i <= N ; ++ i)	if (!fa[i]) do_dp(i, 0), Ans += dp[i][0][0] ;
		printf("%.8lf", Ans * Pi) ;  	
	}
}
```
核心实现思想：同样先按半径从大到小排序，构建圆的包含关系树（通过`Add`函数），`do_dp`函数通过动态规划，从下往上更新`dp[u][0/1][0/1]`，表示以点`u`为根的子树分成两堆后，两堆分别高度为偶数/奇数时的最优值，最后汇总所有树的根节点的`dp[i][0][0]`得到答案。

### 最优关键思路或技巧
贪心策略是本题较为简洁高效的解法，通过观察和证明得出只将覆盖次数为2的圆放到另一组的结论，减少了复杂的计算。动态规划则是一种更通用的思路，通过树形结构和状态转移方程来求解最优解。无论是贪心还是动态规划，都需要先处理圆之间的包含关系，将其转化为树形结构，便于后续处理。

### 可拓展之处
同类型题目可能会改变图形形状（如矩形等）或增加限制条件（如舞者移动范围有重叠限制等），但核心思路仍可能围绕贪心或动态规划，通过分析图形之间的关系，根据某种条件进行合理分配。类似算法套路包括处理图形包含、相交关系时构建合适的数据结构（如树），以及根据问题特点设计状态和状态转移方程。

### 推荐洛谷题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：典型的贪心算法题目，通过分析数据之间的关系得出贪心策略。
- [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)：可使用动态规划求解，通过划分阶段和状态转移来解决区间合并问题。
- [P2014 [CTSC1997] 选课](https://www.luogu.com.cn/problem/P2014)：树形动态规划题目，与本题将圆关系转化为树形结构类似，通过在树上进行状态转移求解。 

---
处理用时：103.51秒