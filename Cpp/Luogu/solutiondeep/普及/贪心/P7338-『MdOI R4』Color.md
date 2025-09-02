# 题目信息

# 『MdOI R4』Color

## 题目描述

小 M 同学有一张 $2$ 行 $n$ 列的方格纸，一开始所有格子都是白色的。

她决定对一些格子染色，具体地，每次她会选择两个**相邻的（四联通的，也就是有公共边的）白色**格子，其中一个染成红色，另一个染成蓝色。

她的目标是通过**任意次操作**让指定的一些格子变成红色，**对其他格子没有要求**。请你帮她判断一下，能否通过上述操作达成目标呢？

## 说明/提示

【样例解释】

![temp.png](https://i.loli.net/2020/09/27/oCRpYnPAlFk7GuS.png)

上图中左侧为第一组测试数据的一种方案，右侧为第三组测试数据的一种方案，对于第二组测试数据，并没有满足要求的方案。

【数据规模与约定】 

**本题采用捆绑测试**

|子任务编号|$n\le$|特殊性质|$T\le$|分值|
|:-|:-|:-|:-|:-|
|$1$|$3$|无特殊限制|$10$|$10$|
|$2$|$10$|无特殊限制|$10$|$20$|
|$3$|无特殊限制|所有 $1$ 都在同一行|$10$|$1$|
|$4$|无特殊限制|$1$ 不超过 $4$ 个|$10$|$13$|
|$5$|$10^3$|无特殊限制|$10$|$25$|
|$6$|无特殊限制|无特殊限制|$10$|$30$|
|$7$|$16$|无特殊限制|$65536$|$1$|

对于所有数据，满足 $1\le n\le 10^5$，$\sum n\le 2^{20}$。

## 样例 #1

### 输入

```
3
5
01110
10010
5
11000
01100
5
00101
10100
```

### 输出

```
RP
++
RP```

# AI分析结果

### 综合分析与结论

本题的核心是通过贪心策略或二分图匹配来判断是否能够通过染色操作满足目标要求。大多数题解采用了贪心策略，从左到右依次处理每一列，优先选择左侧的格子进行染色，若不行则选择同一列或右侧的格子。这种贪心策略的时间复杂度为 \(O(Tn)\)，能够通过所有测试数据。部分题解还提到了二分图匹配的思路，虽然时间复杂度较高，但在某些情况下也能通过。

### 所选高星题解

#### 1. 作者：yummy (5星)
- **关键亮点**：详细分析了不同子任务的解法，特别是Subtask 6&7的贪心策略，思路清晰，代码简洁。
- **个人心得**：提到了Subtask 7的添加是为了防止假算法通过，同时提醒了直接使用`memset`可能会导致TLE。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char up[100005],down[100005];
bool cup(int x){
	if(up[x]!='0')return 1;
	up[x]='2';return 0;}
bool cdown(int x){
	if(down[x]!='0')return 1;
	down[x]='2';return 0;}
int main(){
	for(scanf("%d",&t);t;t--){
		scanf("%d%s%s",&n,up,down);
		bool flag=1;
		if(up[0]=='1'&&cdown(0)&&cup(1)||down[0]=='1'&&cup(0)&&cdown(1))
			flag=0;
		for(int i=1;i<n;i++)
			if(up[i]=='1'&&cup(i-1)&&cdown(i)&&cup(i+1)||down[i]=='1'&&cdown(i-1)&&cup(i)&&cdown(i+1)){
				flag=0;break;
			}
		if(flag)puts("RP");
		else puts("++");
	}
    return 0;
}
```

#### 2. 作者：cmll02 (4星)
- **关键亮点**：贪心策略的优先级从左到右依次处理，代码实现简洁，逻辑清晰。
- **个人心得**：强调了优先往左染色的正确性，并通过图示说明了贪心策略的合理性。

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
bool p[100005][2],u[100005][2];
int main(){
	int T=read();
	while(T--){
		int n=read();
		for(int i=0;i<2;i++)
			for(int j=0;j<n;j++)
				p[j][i]=read1d(),u[j][i]=p[j][i];
		for(int i=0;i<n;i++){
			if(p[i][0]){
				if(i>0&&u[i-1][0]==0)u[i-1][0]=1;
				else if(u[i][1]==0)u[i][1]=1;
				else if(i<n-1&&u[i+1][0]==0)u[i+1][0]=1;
				else {puts("++");goto qaq;}
			}
			if(p[i][1]){
				if(i>0&&u[i-1][1]==0)u[i-1][1]=1;
				else if(u[i][0]==0)u[i][0]=1;
				else if(i<n-1&&u[i+1][1]==0)u[i+1][1]=1;
				else {puts("++");goto qaq;}
			}
		}
		puts("RP");
		qaq:;
	}
	return 0;
}
```

#### 3. 作者：囧仙 (4星)
- **关键亮点**：贪心策略的证明较为严谨，代码实现简洁，逻辑清晰。
- **个人心得**：通过图示说明了贪心策略的正确性，强调了从左到右处理的合理性。

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN =1e6+3;
char S[MAXN],T[MAXN]; int n;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    dn(qread(),1,TT){
        n=qread(); scanf("%s%s",S+1,T+1);
        S[n+1]=T[n+1]='!';
        up(1,n,i){
            if(S[i]=='1'){ if(S[i-1]=='0') S[i-1]='!';
            else if(T[i]=='0') T[i]='!'; else if(S[i+1]=='0') S[i+1]='!'; else goto no;}
            if(T[i]=='1'){ if(T[i-1]=='0') T[i-1]='!';
            else if(S[i]=='0') S[i]='!'; else if(T[i+1]=='0') T[i+1]='!'; else goto no;}
        }
        puts("RP"); goto yes; no: puts("++"); yes:;
    }
    return 0;
}
```

### 最优关键思路与技巧

1. **贪心策略**：从左到右依次处理每一列，优先选择左侧的格子进行染色，若不行则选择同一列或右侧的格子。这种策略能够保证局部最优，进而达到全局最优。
2. **时间复杂度优化**：贪心策略的时间复杂度为 \(O(Tn)\)，能够通过所有测试数据。
3. **边界处理**：在处理第一列和最后一列时，需要特别注意边界条件，避免数组越界。

### 可拓展之处

- **类似题目**：可以扩展到更大规模的矩阵（如 \(m \times n\)）或更高维度的染色问题。
- **算法套路**：贪心策略在类似的匹配问题中也有广泛应用，如任务调度、资源分配等。

### 推荐题目

1. [P3386 【模板】二分图匹配](https://www.luogu.com.cn/problem/P3386)
2. [P2774 方格取数问题](https://www.luogu.com.cn/problem/P2774)
3. [P2765 魔术球问题](https://www.luogu.com.cn/problem/P2765)

### 个人心得总结

- **调试经历**：直接使用`memset`可能会导致TLE，建议在初始化时手动清空数组。
- **踩坑教训**：在处理边界条件时，需要特别注意数组越界问题，避免程序崩溃。
- **顿悟感想**：贪心策略的优先级选择是关键，优先处理左侧的格子能够有效减少后续处理的复杂度。

---
处理用时：60.33秒