# 题目信息

# [ABC391E] Hierarchical Majority Vote

## 题目描述

对于一个长度为 $3^n$ 的 01 字符串 $B = B_1B_2\dots B_{3^n}$，定义一种操作获得长度为 $3^{n-1}$ 的 01 字符串 $C = C_1C_2\dots C_{3^{n-1}}$：

+ 对于 $i = 1,2,\dots,3^{n-1}$，令 $C_i$ 为 $B_{3i}$、$B_{3i-1}$、$B_{3i-2}$ 中出现次数最多的字符。

现给定一个长度为 $3^N$ 的 01 字符串 $A = A_1A_2\dots A_{3^N}$。设 $A'=A'_1$ 是通过 $N$ 次上述操作后得到的长度为 $1$ 的字符串。

请求出最少改变 $A$ 中多少个元素（$0$ 变 $1$，$1$ 变 $0$），以改变 $A'_1$ 。

## 说明/提示

$1 \le N \le 13$，$A$ 为长度为 $3^N$ 的 01 字符串。

## 样例 #1

### 输入

```
2

010011101```

### 输出

```
1```

## 样例 #2

### 输入

```
1

000```

### 输出

```
2```

# AI分析结果

### 题目内容重写

#### 题目描述

对于一个长度为 $3^n$ 的 01 字符串 $B = B_1B_2\dots B_{3^n}$，定义一种操作获得长度为 $3^{n-1}$ 的 01 字符串 $C = C_1C_2\dots C_{3^{n-1}}$：

+ 对于 $i = 1,2,\dots,3^{n-1}$，令 $C_i$ 为 $B_{3i}$、$B_{3i-1}$、$B_{3i-2}$ 中出现次数最多的字符。

现给定一个长度为 $3^N$ 的 01 字符串 $A = A_1A_2\dots A_{3^N}$。设 $A'=A'_1$ 是通过 $N$ 次上述操作后得到的长度为 $1$ 的字符串。

请求出最少改变 $A$ 中多少个元素（$0$ 变 $1$，$1$ 变 $0$），以改变 $A'_1$ 。

#### 说明/提示

$1 \le N \le 13$，$A$ 为长度为 $3^N$ 的 01 字符串。

#### 样例 #1

##### 输入

```
2

010011101
```

##### 输出

```
1
```

#### 样例 #2

##### 输入

```
1

000
```

##### 输出

```
2
```

### 题解分析与结论

#### 综合分析

本题的核心是通过递归或动态规划的方式，模拟字符串的压缩过程，并计算改变最终结果所需的最小修改次数。大多数题解采用了树形DP或分治的思路，通过维护每个节点的值和修改代价，逐步推导出最终结果。

#### 最优思路与技巧

1. **树形DP**：将字符串的压缩过程视为一棵三叉树，每个节点的值由其三个子节点的多数值决定。通过递归计算每个节点的修改代价，最终得到根节点的修改代价。
2. **分治策略**：将字符串分成三部分，分别递归处理，最后根据三部分的结果决定当前节点的值和修改代价。
3. **动态规划**：通过维护每个节点的值和修改代价，逐步推导出最终结果。关键点在于如何根据子节点的值计算当前节点的修改代价。

#### 推荐题目

1. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040) - 考察树形DP的应用。
2. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880) - 考察分治和动态规划的结合。
3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063) - 考察动态规划在区间问题中的应用。

### 精选题解

#### 题解1：gesong (5星)

**关键亮点**：
- 使用树形DP的思路，清晰地将问题转化为三叉树的节点值计算。
- 通过分类讨论子节点的值，简洁地推导出当前节点的修改代价。

**核心代码**：
```cpp
pii dfs(int l,int r){
	if (l==r) return {a[l],1};
	pii x=dfs(l,l+(r-l+1)/3-1),y=dfs(l+(r-l+1)/3,l+(r-l+1)/3*2-1),z=dfs(l+(r-l+1)/3*2,r);
	int cnt[2]={0,0};
	cnt[x.first]++,cnt[y.first]++,cnt[z.first]++;
	if (cnt[0]==3){
		int b[]={x.second,y.second,z.second};
		sort(b,b+3);
		return {0,b[0]+b[1]};
	}
	else if (cnt[1]==3){
		int b[]={x.second,y.second,z.second};
		sort(b,b+3);
		return {1,b[0]+b[1]};
	}
	else if (cnt[0]==2){
		int ans=1e18;
		if (x.first==0) ans=min(ans,x.second);
		if (y.first==0) ans=min(ans,y.second);
		if (z.first==0) ans=min(ans,z.second);
		return {0,ans};
	}
	else if (cnt[1]==2){
		int ans=1e18;
		if (x.first==1) ans=min(ans,x.second);
		if (y.first==1) ans=min(ans,y.second);
		if (z.first==1) ans=min(ans,z.second);
		return {1,ans};
	}
}
```

#### 题解2：Awsdkl (4星)

**关键亮点**：
- 将问题转化为三叉树的节点值计算，通过递归处理子节点。
- 通过分类讨论子节点的值，简洁地推导出当前节点的修改代价。

**核心代码**：
```cpp
int dfs(int p, int l, int r)
{
	if(l == r)
	{
		f[p] = 1;
		return s[r] - '0';
	}
	int lp = ++cnt, mp = ++cnt, rp = ++cnt;
	int len = (r - l + 1);
	int lpv = dfs(lp, l, 			l+len/3-1);
	int mpv = dfs(mp, l+len/3, 		l+len/3*2-1);
	int rpv = dfs(rp, l+len/3*2, 	r);
	int cnt0 = 0, cnt1 = 0;
	if(lpv == 0) cnt0++; else cnt1++;
	if(mpv == 0) cnt0++; else cnt1++;
	if(rpv == 0) cnt0++; else cnt1++;
	int nowv = cnt0 > cnt1 ? 0 : 1;
	f[p] = 0x3f3f3f3f;
	if((nowv == 0 && cnt1 == 1) || (nowv == 1 && cnt0 == 1))
	{
		if(lpv == nowv) f[p] = min(f[p], f[lp]);
		if(mpv == nowv) f[p] = min(f[p], f[mp]);
		if(rpv == nowv) f[p] = min(f[p], f[rp]);
	}
	else
	{
		f[p] = min(f[p], f[lp] + f[mp]);
		f[p] = min(f[p], f[lp] + f[rp]);
		f[p] = min(f[p], f[mp] + f[rp]);
	}
	return nowv;
}
```

#### 题解3：chenxi2009 (4星)

**关键亮点**：
- 使用递推的方式，逐步计算每个节点的值和修改代价。
- 通过分类讨论子节点的值，简洁地推导出当前节点的修改代价。

**核心代码**：
```cpp
for(int i = n - 1;~i;i --){
	for(int j = 1;j <= p[i];j ++){
		int cnt = (f[i + 1][3 * j - 2] == '0') + (f[i + 1][3 * j - 1] == '0') + (f[i + 1][3 * j] == '0');
		int a = g[i + 1][3 * j - 2],b = g[i + 1][3 * j - 1],c = g[i + 1][3 * j];
		if(cnt == 0) f[i][j] = '1',g[i][j] = a + b + c - max(a,b,c);
		else if(cnt == 1){
			f[i][j] = '1';
			if(f[i + 1][3 * j - 2] == '0') g[i][j] = min(b,c);
			else if(f[i + 1][3 * j - 1] == '0') g[i][j] = min(a,c);
			else g[i][j] = min(a,b);
		}
		else if(cnt == 2){
			f[i][j] = '0';
			if(f[i + 1][3 * j - 2] == '1') g[i][j] = min(b,c);
			else if(f[i + 1][3 * j - 1] == '1') g[i][j] = min(a,c);
			else g[i][j] = min(a,b);
		}
		else f[i][j] = '0',g[i][j] = a + b + c - max(a,b,c);
	}
}
```

---
处理用时：64.92秒