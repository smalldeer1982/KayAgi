# 题目信息

# Ithea Plays With Chtholly

## 题目描述

### 题面描述

**这是一道交互题。**

艾瑟雅想要和珂朵莉玩一个游戏来决定厨房晚上的使用权。

游戏进行 $m$ 个回合，艾瑟雅现在有 $n$ 张白纸，每一个回合，艾瑟雅都会给珂朵莉一个 $\in [1,c]$ 的数字，珂朵莉可以选择一个值 $i$，如果第 $i$ 张纸上没有数字，则珂朵莉会把当前的数字写上去，如果有，那么珂朵莉会把原来的数字替换成当前的数字。

珂朵莉需要在至多 $m$ 回合之后，对于所有 $i(1\le i\le n)$，第 $i$ 张纸都写了数字，并且对于编号大于 $1$ 的纸 $i$，写上的数字均 **大于等于** $i-1$ 张纸上写的数字。

## 说明/提示

对于 $100\%$ 的数据，保证 $n,m\ge 2,1\le c\le 1000$，**保证有 $1\le n\cdot\left\lceil\dfrac{c}{2}\right\rceil\le m\le 1000$**。

## 样例 #1

### 输入

```
2 4 4
2
1
3
```

### 输出

```
1
2
2
```

# AI分析结果

### 题目内容
# Ithea Plays With Chtholly

## 题目描述

### 题面描述
**这是一道交互题。**

艾瑟雅想要和珂朵莉玩一个游戏来决定厨房晚上的使用权。

游戏进行 $m$ 个回合，艾瑟雅现在有 $n$ 张白纸，每一个回合，艾瑟雅都会给珂朵莉一个 $\in [1,c]$ 的数字，珂朵莉可以选择一个值 $i$，如果第 $i$ 张纸上没有数字，则珂朵莉会把当前的数字写上去，如果有，那么珂朵莉会把原来的数字替换成当前的数字。

珂朵莉需要在至多 $m$ 回合之后，对于所有 $i(1\le i\le n)$，第 $i$ 张纸都写了数字，并且对于编号大于 $1$ 的纸 $i$，写上的数字均 **大于等于** $i - 1$ 张纸上写的数字。

## 说明/提示
对于 $100\%$ 的数据，保证 $n,m\ge 2,1\le c\le 1000$，**保证有 $1\le n\cdot\left\lceil\dfrac{c}{2}\right\rceil\le m\le 1000$**。

## 样例 #1
### 输入
```
2 4 4
2
1
3
```
### 输出
```
1
2
2
```
### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是基于给定数字与 $\frac{c}{2}$ 的大小关系，采用不同方向遍历纸张来放置数字，以满足最终纸张上数字非严格单调递增且填满所有纸张的要求。多数题解都给出了构造方法及相应证明，部分题解还提及了交互题输出刷新的要点。不同题解在思路清晰度、代码可读性上存在差异。

### 所选的题解
- **作者：囧仙 (5星)**
    - **关键亮点**：不仅给出构造方法，还详细证明了构造方法的正确性，思路清晰，代码规范。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
const int MAXN =1e3+3;
int n,m,c,t,A[MAXN],f;
int main(){
    scanf("%d%d%d",&n,&m,&c);
    up(1,m,i){
        scanf("%d",&t); if(t<=c/2){
            up(1,n,j) if(!A[j]||A[j]>t){A[j]=t,f=j;break;}
        } else {
            dn(n,1,j) if(!A[j]||A[j]<t){A[j]=t,f=j;break;}
        }
        printf("%d\n",f);
        fflush(stdout);
    }
    return 0;
}
```
    - **核心实现思想**：根据输入数字 $t$ 与 $c/2$ 的大小关系，选择从左往右（$t\leq c/2$）或从右往左（$t > c/2$）遍历数组 $A$ （代表纸张），找到第一个满足条件（为空或数字符合大小关系）的位置，填入数字并输出位置，每次输出后刷新缓冲区。
- **作者：wwwwwza (4星)**
    - **关键亮点**：表述亲切，简化题意清晰，构造方式和证明结论逻辑连贯，代码简洁明了。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,c,x,a[1005];
signed main(){
	cin >>n>>m>>c;
	while(m--){
		cin >>x;
		if(x<=c/2){
			for(int i=1;i<=n;i++){
				if(x<a[i]||a[i]==0){
					a[i]=x;
					cout <<i<<endl;
					break;
				}
			}
		}else{
			for(int i=n;i>=1;i--){
				if(x>a[i]||a[i]==0){
					a[i]=x;
					cout <<i<<endl;
					break;
				}
			}
		}
	}
	return 0;
}
```
    - **核心实现思想**：与囧仙题解类似，根据 $x$ 和 $c/2$ 的大小，从左或从右遍历数组 $a$，找到合适位置更新数字并输出位置，虽未写刷新缓冲区，但逻辑主体完整。
- **作者：JWRuixi (4星)**
    - **关键亮点**：对题意分析到位，证明过程简洁，代码规范且使用了GCC优化指令。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

const int maxn(1005);
int n, m, c, a[maxn], x;

int main () {
	scanf("%d%d%d", &n, &m, &c);
	const int lim = c / 2;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &x);
		if (x <= lim) {
			for (int j = 1; j <= n; j++) if (!a[j] || x < a[j]) {
				a[j] = x;
				printf("%d\n", j);
				fflush(stdout);
				break;
			}
		} else {
			for (int j = n; j; j--) if (!a[j] || a[j] < x) {
				a[j] = x;
				printf("%d\n", j);
				fflush(stdout);
				break;
			}
		}
	}
}
```
    - **核心实现思想**：先定义好相关变量，通过输入获取 $n$、$m$、$c$ 后，在每次循环输入数字 $x$ 时，依据 $x$ 与 $c/2$ 的关系，从左或从右遍历数组 $a$，找到合适位置更新并输出位置，同时每次输出后刷新缓冲区。

### 最优关键思路或技巧
根据数字与 $\frac{c}{2}$ 的大小关系，分方向遍历纸张数组放置数字，巧妙利用题目给定的 $n\cdot\left\lceil\dfrac{c}{2}\right\rceil\le m$ 条件，构造出满足要求的数字序列。这种构造思路是解决本题的关键。

### 可拓展之处
此类题目属于交互题中的构造类型，类似套路是根据题目给定的限制条件和目标，设计一种合理的构造规则。比如在一些需要构造特定序列、矩阵等题目中，可通过分析数据范围、条件关系，找到类似的分类构造方法。

### 洛谷相似题目推荐
 - [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：通过贪心策略构造最优数字序列，与本题构造思路有相似之处。
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：根据数据特点进行分组构造，锻炼构造思维。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：利用贪心思想构造最优排队顺序，与本题在根据条件构造方案上类似。

### 个人心得摘录及总结
部分作者提到交互题中输出后要刷新缓冲区（如使用 `fflush(stdout)`），这是交互题的一个重要注意点，若不刷新可能导致输出结果异常。还有作者提到在输入时使用快读可能会 TLE，说明在处理交互题输入输出时，需要注意输入输出方式对程序性能的影响。 

---
处理用时：62.15秒