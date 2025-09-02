# Winding polygonal line

## 题目描述

Vasya 在平面上有 $n$ 个不同的点 $A_1, A_2, \ldots, A_n$。任意三点不共线。他希望将这些点按某种顺序排列为 $A_{p_1}, A_{p_2}, \ldots, A_{p_n}$，其中 $p_1, p_2, \ldots, p_n$ 是 $1$ 到 $n$ 的某个排列。

随后，他将在这些点上画一条有向折线，依次从每个点连向下一个点。也就是说，对于所有 $1 \leq i \leq n-1$，他会从点 $A_{p_i}$ 画一条有向线段到点 $A_{p_{i+1}}$。他希望这条折线满足以下两个条件：

- 折线不自交，即任意两条非相邻的线段没有公共点。
- 折线是“绕行”的。

Vasya 有一个长度为 $n-2$ 的字符串 $s$，由字母 "L" 或 "R" 组成。我们称一条有向折线为“绕行”的，如果其第 $i$ 次转弯是左转当且仅当 $s_i = $ "L"，右转当且仅当 $s_i = $ "R"。更正式地说：第 $i$ 次转弯发生在点 $A_{p_{i+1}}$，此时有向线段从 $A_{p_i}$ 到 $A_{p_{i+1}}$，再从 $A_{p_{i+1}}$ 到 $A_{p_{i+2}}$。设 $\overrightarrow{v_1} = \overrightarrow{A_{p_i}A_{p_{i+1}}}$，$\overrightarrow{v_2} = \overrightarrow{A_{p_{i+1}}A_{p_{i+2}}}$。如果将 $\overrightarrow{v_1}$ 逆时针旋转最小角度后与 $\overrightarrow{v_2}$ 方向一致，则称第 $i$ 次转弯为左转，否则为右转。为了更好地理解，请参考以下关于转弯的示意图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1158D/d5299b6f90549459cc8717af240386941199ff67.png)  
上图为左转示例。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1158D/a11fbd8181dcd2ab10ca7331a2bf5db3787c2cdb.png)  
上图为右转示例。

现在给定 $A_1, A_2, \ldots, A_n$ 的坐标和字符串 $s$，请你找到一个 $1$ 到 $n$ 的排列 $p_1, p_2, \ldots, p_n$，使得 Vasya 画出的折线满足上述两个条件。

## 说明/提示

下图为第 1 组样例的折线：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1158D/d2411e0ea8639f748eaeabd4798b3f5ad7d71d3c.png)  
可以看到，这条折线不自交且为绕行折线，因为在点 $2$ 处为左转。

下图为第 2 组样例的折线：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1158D/905963ceb06b1d6041871a65036c396bc8d6cd07.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 1
3 1
1 3
L
```

### 输出

```
1 2 3```

## 样例 #2

### 输入

```
6
1 0
0 1
0 2
-1 0
-1 -1
2 1
RLLR
```

### 输出

```
6 1 3 4 2 5
```

# 题解

## 作者：AThousandSuns (赞：9)

其实就是个纯构造题！

先随便找凸包上的一个点作为起点。（不需要建出凸包，可以直接选横坐标最小的）

然后第 $i$ 次加入一个点，如果 $s_i$ 是 L，就找最右边的点，否则找最左边的点。最后一次就把剩下那个点加进去就好了。

这样是一定合法解。

正确性证明？以 L 为例，既然选的是最右边的点，所以剩下的所有点都在 $p_i$ 和这个最右的点的连线的左边。所以是一定可以找到一个往左拐的折线（而且一定是往左拐的），而且不会自交（不会绕到这条折线的右边去）。

时间复杂度 $O(n^2)$。（应该可以做到 $O(n\log n)$ 吧？感觉可以再弄个凸包或者半平面交这类的东西优化一下）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=100010;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,x[maxn],y[maxn],p[maxn];
char s[maxn];
bool vis[maxn];
inline ll cross(int x1,int y1,int x2,int y2){
	return 1ll*x1*y2-1ll*x2*y1;
}
inline ll cross(int i,int j,int k){
	return cross(x[j]-x[i],y[j]-y[i],x[k]-x[i],y[k]-y[i]);
}
int main(){
	n=read();
	FOR(i,1,n){
		x[i]=read(),y[i]=read();
		if(!p[1] || x[i]<x[p[1]]) p[1]=i; 
	}
	scanf("%s",s+1);
	vis[p[1]]=true;
	FOR(i,1,n-2){
		FOR(j,1,n){
			if(vis[j]) continue;
			if(!p[i+1] || s[i]=='L' && cross(p[i],j,p[i+1])>0 || s[i]=='R' && cross(p[i],j,p[i+1])<0) p[i+1]=j;
		}
		vis[p[i+1]]=true;
	}
	FOR(i,1,n-1) printf("%d ",p[i]);
	FOR(i,1,n) if(!vis[i]) printf("%d\n",i);
}
```

---

