# 题目信息

# Friends and Subsequences

## 题目描述

Mike and !Mike are old childhood rivals, they are opposite in everything they do, except programming. Today they have a problem they cannot solve on their own, but together (with you) — who knows?

Every one of them has an integer sequences $ a $ and $ b $ of length $ n $ . Being given a query of the form of pair of integers $ (l,r) $ , Mike can instantly tell the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/77a91e450d8c58a8cff349889db0f7900b8e3ace.png) while !Mike can instantly tell the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/7594cca965e5cc163cc16e32e5bed1c0ba0fa037.png).

Now suppose a robot (you!) asks them all possible different queries of pairs of integers $ (l,r) $ $ (1<=l<=r<=n) $ (so he will make exactly $ n(n+1)/2 $ queries) and counts how many times their answers coincide, thus for how many pairs ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/72e28ce968021e0cd2b5fe1a6f144994e8f8338b.png) is satisfied.

How many occasions will the robot count?

## 说明/提示

The occasions in the first sample case are:

1\. $ l=4 $ , $ r=4 $ since $ max{2}=min{2} $ .

2\. $ l=4 $ , $ r=5 $ since $ max{2,1}=min{2,3} $ .

There are no occasions in the second sample case since Mike will answer $ 3 $ to any query pair, but !Mike will always answer $ 1 $ .

## 样例 #1

### 输入

```
6
1 2 3 2 1 4
6 7 1 2 3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 3 3
1 1 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 朋友与子序列

## 题目描述
迈克和反迈克是儿时的老对手，除了编程，他们在做任何事时都截然相反。今天，他们遇到了一个靠自己无法解决的问题，但要是一起（加上你）—— 谁知道呢？

他们每个人都有一个长度为 $n$ 的整数序列 $a$ 和 $b$ 。当给出一对整数 $(l,r)$ 形式的查询时，迈克可以立即说出 $\max\limits^r_{i=l}a_i$ 的值，而反迈克可以立即说出 $\min\limits^r_{i=l}b_i$ 的值。

现在假设有一个机器人（也就是你！）向他们提出所有可能不同的整数对 $(l,r)$ 的查询（$1\leq l\leq r\leq n$）（所以他将提出恰好 $n(n + 1)/2$ 次查询），并统计他们的答案一致的次数，即统计满足 $\max\limits^r_{i=l}a_i=\min\limits^r_{i=l}b_i$ 的对数。

机器人会统计到多少次这样的情况呢？

## 说明/提示
第一个样例中的情况如下：
1. $l = 4$，$r = 4$，因为 $\max\{2\}=\min\{2\}$。
2. $l = 4$，$r = 5$，因为 $\max\{2,1\}=\min\{2,3\}$。

第二个样例中没有这样的情况，因为迈克对任何查询对的回答都是 $3$，但反迈克的回答总是 $1$。

## 样例 #1
### 输入
```
6
1 2 3 2 1 4
6 7 1 2 3 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3
3 3 3
1 1 1
```
### 输出
```
0
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路均是利用固定左端点 $l$ 时，$\max\limits^{i}_{k=l}a_k$ 单调不降、$\min\limits^{i}_{k=l}b_k$ 单调不增的性质，通过二分查找满足 $\max\limits^r_{i=l}a_i=\min\limits^r_{i=l}b_i$ 的右端点区间，同时使用 ST 表优化区间最大/最小值的查询。各题解的主要差异在于二分查找的具体实现细节以及代码的风格和优化程度。

### 所选的题解
- **作者：Eroded (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，标准的二分 + ST 表解法，对二分的边界处理得当。
    - **重点代码**：
```cpp
int qmax(int l,int r){//ST表取a的(l,r)中最大值
    if(l == r) return f1[l][0];
	int k = log2(r - l + 1);
	return max(f1[l][k],f1[r - (1 << k) + 1][k]);
}
int qmin(int l,int r){//ST表取b的(l,r)中最小值
    if(l == r) return f2[l][0];
	int k = log2(r - l + 1);
	return min(f2[l][k],f2[r - (1 << k) + 1][k]);
}
int ql(int i){//二分左端点
	int l = i,r = n;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(qmax(i,mid) < qmin(i,mid)) l = mid + 1;
		else r = mid - 1;
	}
	if(l <= n && qmax(i,l) == qmin(i,l)) return l;
	return 0;
}
int qr(int i){//二分右端点
	int l = i,r = n;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(qmax(i,mid) > qmin(i,mid)) r = mid - 1;
		else l = mid + 1;
	}
	if(r > 0 && qmax(i,r) == qmin(i,r)) return r;
	return 0;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i = 1;i <= n;i++){
		cin>>f1[i][0];
	}
	for(int i = 1;i <= n;i++){
		cin>>f2[i][0];
	}
	for(int j = 1;j <= 21;j++){//预处理ST表
		for(int i = 1;i + (1 << j) - 1 <= n;i++){
			f1[i][j] = max(f1[i][j - 1],f1[i + (1 << (j - 1))][j - 1]);
		}
	}
    for(int j = 1;j <= 21;j++){//同上
		for(int i = 1;i + (1 << j) - 1 <= n;i++){
			f2[i][j] = min(f2[i][j - 1],f2[i + (1 << (j - 1))][j - 1]);
		}
	}
	for(int i = 1;i <= n;i++){
		int l = ql(i),r = qr(i);
		if(l == 0) continue;
		if(r == 0) continue;
		if(l > r) swap(l,r);
		sum += (r - l + 1);
	}
	cout<<sum;
	return 0;
}
```
    - **核心实现思想**：通过 `qmax` 和 `qmin` 函数利用 ST 表快速获取区间最大最小值。`ql` 和 `qr` 函数分别二分查找满足条件的左端点和右端点，最后在 `main` 函数中枚举左端点，统计满足条件的区间数量。
- **作者：henrytb (4星)**
    - **关键亮点**：提供了一种防止二分写挂的方法，在二分区间较小时采用暴力查找，减少二分边界处理的细节，方便考场调试。
    - **个人心得**：二分容易写挂，在 $l$ 与 $r$ 距离很小时跳出二分暴力查找可减少细节考虑。
    - **重点代码**：
```cpp
signed main() {
    scanf("%lld",&n);
    rep(i,1,n) scanf("%lld",&a[i]),mx[i][0]=a[i];
    rep(i,1,n) scanf("%lld",&b[i]),mn[i][0]=b[i];
    rep(j,1,21) {
        rep(i,1,n) {
            if(i+(1<<(j-1))-1>n) mx[i][j]=mx[i][j-1];
            else mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
        }
    }
    rep(j,1,21) {
        rep(i,1,n) {
            if(i+(1<<(j-1))-1>n) mn[i][j]=mn[i][j-1];
            else mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
        }
    }
    int ans=0;
    rep(i,1,n) {
        int l=i,r=n;
        int rr=0,ll=0;
        while(r-l>5) {
            int mid=(l+r)>>1;
            int lg=log2(mid-i+1);
            int mxx=max(mx[i][lg],mx[mid-(1<<lg)+1][lg]);
            int mnn=min(mn[i][lg],mn[mid-(1<<lg)+1][lg]);
            if(mxx>mnn) r=mid;
            else l=mid;
        }
        per(j,r,l) {
            int lg=log2(j-i+1);
            int mxx=max(mx[i][lg],mx[j-(1<<lg)+1][lg]);
            int mnn=min(mn[i][lg],mn[j-(1<<lg)+1][lg]);
            if(mxx==mnn) {rr=j;break;}
        }
        l=i,r=n;
        while(r-l>5) {
            int mid=(l+r)>>1;
            int lg=log2(mid-i+1);
            int mxx=max(mx[i][lg],mx[mid-(1<<lg)+1][lg]);
            int mnn=min(mn[i][lg],mn[mid-(1<<lg)+1][lg]);
            if(mxx>=mnn) r=mid;
            else l=mid;
        }
        rep(j,l,r) {
            int lg=log2(j-i+1);
            int mxx=max(mx[i][lg],mx[j-(1<<lg)+1][lg]);
            int mnn=min(mn[i][lg],mn[j-(1<<lg)+1][lg]);
            if(mxx==mnn) {ll=j;break;}
        }
        if(ll&&rr) ans+=(rr-ll+1);
    }
    printf("%lld",ans);
	return 0;
}
```
    - **核心实现思想**：先预处理 ST 表，然后在枚举左端点 $i$ 时，通过二分和暴力结合的方式查找满足条件的右端点区间，统计满足条件的区间数量。
- **作者：一只书虫仔 (4星)**
    - **关键亮点**：思路阐述清晰，将问题转化为固定左界找满足条件的区间，通过二分查找区间左右端点，代码结构清晰。
    - **重点代码**：
```cpp
int Max (int l, int r) {
	if (l > r) swap(l, r);
	int k = log2(r - l + 1);
	return max(dpa[l][k], dpa[r - (1 << k) + 1][k]);
}

int Min (int l, int r) {
	if (l > r) swap(l, r);
	int k = log2(r - l + 1);
	return min(dpb[l][k], dpb[r - (1 << k) + 1][k]);
}

int binsearch_l (int l, int r, int n) {
	int left = l;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (Max(left, mid) < Min(left, mid)) l = mid + 1;
		else r = mid - 1;
	}
	if (l <= n && Max(left, l) == Min(left, l)) return l;
	else return 0;
}

int binsearch_r (int l, int r, int n) {
	int left = l;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (Max(left, mid) > Min(left, mid)) r = mid - 1;
		else l = mid + 1;
	}
	if (r >= 1 && Max(left, r) == Min(left, r)) return r;
	else return 0;
}

signed main () {
	int n;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for (int i = 1; i <= n; i++) dpa[i][0] = a[i];
	for (int i = 1; i <= n; i++) dpb[i][0] = b[i];
	for (int k = 1; (1 << k) <= n; k++)
		for (int i = 1; i + (1 << k) - 1 <= n; i++)
			dpa[i][k] = max(dpa[i][k - 1], dpa[i + (1 << (k - 1))][k - 1]);
	for (int k = 1; (1 << k) <= n; k++)
		for (int i = 1; i + (1 << k) - 1 <= n; i++)
			dpb[i][k] = min(dpb[i][k - 1], dpb[i + (1 << (k - 1))][k - 1]);
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int l = binsearch_l(i, n, n);
		int r = binsearch_r(i, n, n);
		if (l!= 0 && r!= 0) {
			if (l > r) swap(l, r);
			int ans = (r - l + 1);
			cnt += ans; 
		}
	} 
	printf("%lld", cnt);
	return 0;
}
```
    - **核心实现思想**：通过 `Max` 和 `Min` 函数利用 ST 表获取区间最值，`binsearch_l` 和 `binsearch_r` 分别二分查找满足条件的左端点和右端点，在 `main` 函数中枚举左端点并统计满足条件的区间数量。

### 最优关键思路或技巧
利用固定左端点时区间最大最小值的单调性进行二分查找，同时使用 ST 表优化区间最值查询，将时间复杂度从 $O(n^2)$ 降低到 $O(n \log n)$。

### 拓展
此类题目属于区间最值与计数结合的问题，常见套路是挖掘区间最值的单调性，结合二分查找和合适的数据结构（如 ST 表、线段树等）优化查询。类似题目有：
- [洛谷 P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)：基础的 ST 表区间最值查询模板题，可巩固 ST 表的实现。
- [洛谷 P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：涉及滑动窗口内的最值问题，可使用单调队列解决，与本题有类似的区间最值思考方向。
- [洛谷 P2880 [USACO07MAR]Face The Right Way G](https://www.luogu.com.cn/problem/P2880)：通过分析操作的单调性，利用前缀和优化求解，同样是挖掘数据性质优化算法的类型。 

---
处理用时：116.09秒