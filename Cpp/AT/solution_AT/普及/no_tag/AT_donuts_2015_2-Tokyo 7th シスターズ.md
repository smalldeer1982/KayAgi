# Tokyo 7th シスターズ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/donuts-2015/tasks/donuts_2015_2

[![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_donuts_2015_2/74c2b3e1b85ca8314470521a99add6ad2f49176a.png)](http://t7s.jp/)[《东京 7th Sisters》](https://mzh.moegirl.org.cn/%E4%B8%9C%E4%BA%AC_7th_Sisters)是一款集成了偶像育成、音乐节奏和文字冒险三大要素的手机网络社交游戏，可以在 iPhone 和 Android 设备上玩。 您正在考虑某些游戏规格的简化版本。


在这款简化规格的游戏中，可以从众多偶像中选择九个不同的偶像，组成一个单位进行节奏游戏和舞台对战。在这种情况下，游戏中使用的单位的基本能力值由所选偶像的能力值总和决定。

游戏还有一个连击系统，玩家可以通过满足连击要求获得连击奖励。如果一个单位有三个或三个以上的成员满足组合规定的条件，该单位就会获得该组合的奖励。对于每个组合，你都可以提前知道哪些偶像将满足指定条件。

单位的最终能力值是单位的基础能力值加上所有组合奖励的总和。

我们希望通过组合偶像来尽可能提高单位的最终能力值。 找出最大最终能力值。

请注意，本题中的单位组合和组合是简化规格，与《东京 7th Sisters》的规格略有不同。

## 样例 #1

### 输入

```
10 1
100 200 300 400 500 600 700 800 900 1000
1000 3 1 2 3```

### 输出

```
6100```

## 样例 #2

### 输入

```
12 10
1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000
1000 4 1 2 4 7
1000 4 1 9 11 12
1000 4 3 5 8 9
1000 4 6 10 11 12
1000 4 2 4 7 10
1000 4 1 8 9 10
1000 3 1 9 12
1000 4 3 8 11 12
1000 4 1 2 3 4
1000 4 7 8 9 10```

### 输出

```
19000```

## 样例 #3

### 输入

```
13 8
328 781 104 102 132 108 100 102 104 108 168 102 100
184 4 10 11 3 4
190 4 9 6 2 5
282 6 9 1 3 12 10 8
205 8 13 10 1 12 7 2 8 11
122 8 13 5 4 3 8 9 12 10
112 7 11 6 12 8 2 13 5
102 4 4 13 6 12
109 6 7 2 13 1 8 6```

### 输出

```
3239```

# 题解

## 作者：朱梓煊ZZX (赞：1)

### 前言

题面中输入格式 KateX 炸了，是下面这样的。

$$
\begin{array}{llllllll}
N & M & & & & & \\
A_{1} & A_{2} & \ldots & A_{N} & & \\
B_{1} & C_{1} & I_{1,1} & I_{1,2} & \ldots & I_{1, C_{1}} \\
B_{2} & C_{2} & I_{2,1} & I_{2,2} & \ldots & I_{2, C_{2}} \\
: & & & & & & \\
B_{M} & C_{M} & I_{M, 1} & I_{M, 2} & \ldots & I_{M, C_{M}}
\end{array}
$$

## 题意简化

给定 $N$ 个元素，每个元素若选择可获得 $A_i$。有 $M$ 个组合，若选择了 $\geq 3$ 个第 $i$ 组合中的元素，则可以获得 $B_i$。求选择 $9$ 个元素，获得价值的最大值。

## 思路

显然是有回溯的深搜，对于每个元素枚举选或不选的情况，计算每种情况的能力值。

复杂度 $O(2^N \cdot NM)$

## code

```
#include<bits/stdc++.h>
using namespace std;
int N,M,A[20],B[51],C[51];
int I[51][20];
int maxn;
bool f[20];
void dfs(int d,int cnt){
	if(N-d+1+cnt<9) return;//剪枝：以后偶像全选仍达不到9个 
	if(cnt==9){//计算当前方案能力值 
		int ans=0;
		for(int i=1;i<=N;i++){
			if(f[i]) ans+=A[i];
		}
		for(int i=1;i<=M;i++){
			int ok=0;
			for(int j=1;j<=C[i];j++){
				if(f[I[i][j]]) ok++;
			}if(ok>=3) ans+=B[i];
		}
		maxn=max(maxn,ans);
		return;
	}
	dfs(d+1,cnt);//不取该偶像 
	f[d]=true;
	dfs(d+1,cnt+1);//取该偶像 
	f[d]=false;//回溯 
}
int main(){
	cin>>N>>M;
	for(int i=1;i<=N;i++) cin>>A[i];
	for(int i=1;i<=M;i++){
		cin>>B[i]>>C[i];
		for(int j=1;j<=C[i];j++){
			cin>>I[i][j];
		}
	}
	memset(f,false,sizeof(f));
	dfs(1,0);
	cout<<maxn<<endl;
	return 0;
}
```

---

## 作者：joker_opof_qaq (赞：0)

## 题意

给定共 $n$ 个元素，每个元素的价值为 $a_i$，有 $M$ 个组合情况，如果选择了 $\ge 3$ 个第 $i$ 种组合的元素，即可额外获得 $b_i$。求选择 $9$ 个元素可获得的最大值。

## 思路

有回溯的搜索即可。

每个元素仅仅有选和不选两种情况，暴力枚举每种情况即可。

## code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
#include<utility>
#include<set>
#include<bitset>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if (x<0)x=-x,putchar('-');
	if (x>9)write(x/10);
	putchar(x%10+'0');
}
const int N=1e5+10,M=1e3+10;
bool f[20];
int n,m,a[N],b[N],c[N],l[M][M],maxn=-1;
void dfs(int d,int cnt){
	if(n-d+1+cnt<9) return;
	if(cnt==9){
		int ans=0;
		for(int i=1;i<=n;i++){
			if(f[i])ans+=a[i];
		}
		for(int i=1;i<=m;i++){
			int ansc=0;
			for(int j=1;j<=c[i];j++){
				if(f[l[i][j]])ansc++;
			}
			if(ok>=3)ansc+=b[i];
		}
		maxn=max(maxn,ans);
		return;
	}
	dfs(d+1,cnt);
	f[d]=true;
	dfs(d+1,cnt+1); 
	f[d]=false;
}
int main(){
    n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		b[i]=read(),c[i]=read();
		for(int j=1;j<=c[i];j++)l[i][j]=read();
	}
	dfs(1,0);
	cout<<maxn<<endl;
	return 0;
}

```

---

