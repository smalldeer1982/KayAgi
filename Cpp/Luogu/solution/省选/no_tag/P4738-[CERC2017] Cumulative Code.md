# [CERC2017] Cumulative Code

## 题目描述

如你所知，树是一个由 $n$ 个节点和 $n - 1$ 条无向边组成的图，其中任意两个节点之间有且仅有一条路径。在标记树中，每个节点都用 $1$ 到 $n$ 之间的不同整数标记。标记树的 Prüfer 码是与该树相关联的唯一序列，通过不断从树中移除节点直到只剩下两个节点来生成。更确切地说，在每一步中，我们移除标号最小的叶子，并将其邻居的标号附加到代码的末尾。回忆一下，叶子是一个只有一个邻居的节点。因此，标记树的 Prüfer 码是一个长度为 $n - 2$ 的整数序列。可以证明，原始树可以很容易地从其 Prüfer 码重建。深度为 $k$ 的完全二叉树，记为 $C_k$，是一个有 $2^k - 1$ 个节点的标记树，其中对于所有 $j < 2^{k-1}$，节点 $j$ 连接到节点 $2j$ 和 $2j + 1$。记 $C_k$ 的 Prüfer 码为 $p_1,p_2,..., p_{2^k-3}$。由于 $C_k$ 的 Prüfer 码可能很长，你不需要输出它。相反，你需要回答关于代码中某些元素和的 $n$ 个问题。每个问题由三个整数组成：$a, d$ 和 $m$。答案是 $C_k$ 的 Prüfer 码元素 $p_a, p_{a+d}, p_{a+2d},..., p_{a+(m-1)d}$ 的和。

## 说明/提示

在上面的第一个例子中，当构造 $C_3$ 的 Prüfer 码时，节点按以下顺序被移除：$4, 5, 2, 1, 6$。因此，$C_3$ 的 Prüfer 码是 $2, 2, 1, 3, 3$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 5
1 1 1
2 1 1
3 1 1
4 1 1
5 1 1```

### 输出

```
2
2
1
3
3```

## 样例 #2

### 输入

```
4 4
2 1 5
4 4 3
4 8 1
10 3 2```

### 输出

```
18
15
5
13```

## 样例 #3

### 输入

```
7 1
1 1 125```

### 输出

```
4031```

# 题解

## 作者：ix35 (赞：3)

考虑一个子满二叉树的 Prufer 序列情况，不难发现如果递归到此时根有父亲，那么必须把子树中其他点剥完才能轮到这个点，而左边的点编号小，所以是**左->右->中**的顺序；而如果根没有父亲（这表示这个点在根结点往右的链上），那么剥完左边后可以直接删掉根，所以是**左->中->右**的顺序。

但是如果直接递归是 $O(2^n)$ 的，有点离谱，但是由于大小相等的子树都是长得一样的，所以可以通过一部分预处理来进行平衡规划。

我们事先预处理出大小不超过 $2^d$ 的满二叉树的 Prufer 序列中一个等差数列下标的求和，然后递归时只要当前子树大小不超过 $2^d$ 就使用预处理结果（由于一个子树编号连续，所以只需要通过预处理信息线性变换就可以得到想要的结果）。

时间复杂度为 $O(q(2^d+2^{n-d}))$，取 $d=\dfrac{n}{2}$，复杂度为 $O(q2^{n/2})$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=100010;
int k,q,a,b,c,tot,tot2,num[MAXN][2],num2[MAXN][2];
ll ans,sum[MAXN][2],sum2[MAXN][2];
void dfs1 (int d,int a,int b,int c,int dd) {
	if (d>k-15) {return;}
	dfs1(d+1,a*2,b*2,a,b);
	dfs1(d+1,a*2,b*2+1,a,b);
	tot++;
	num[tot][0]=c,num[tot][1]=dd;
	return;
}
void dfs1p5 (int d,int a,int b,int c,int dd,int flg) {
	if (d>k-15) {return;}
	if (flg) {
		dfs1p5(d+1,a*2,b*2,a,b,1);
		dfs1p5(d+1,a*2,b*2+1,a,b,1);
		tot2++;
		num2[tot2][0]=c,num2[tot2][1]=dd;
		return;
	}
	dfs1p5(d+1,a*2,b*2,a,b,1);
	tot2++;
	num2[tot2][0]=2*a,num2[tot2][1]=2*b+1;
	dfs1p5(d+1,a*2,b*2+1,a,b,0);
	return;
}
bool chk (int x) {
	return (a<=x&&x<=c&&(c-x)%b==0);
}
void dfs2 (int x,int d,int flg) {
	if (d>k) {return;}
	if (flg) {
		if (d<=15&&d+1<=k) {
			dfs2(2*x,d+1,1);
			if (chk(1)) {ans+=x;}
			a--,c--;
			dfs2(2*x+1,d+1,1);
			if (chk(1)) {ans+=x;}
			a--,c--;
			return;
		} else if (d>15) {
			int l,r,siz=(1<<(k-15))-2;
			if (a>0) {l=max(a-b,0);}
			else {l=0;}
			if (c>siz) {r=((c-siz)%b==0?siz:siz+(c-siz)%b-b);}
			else {r=c;}
			if (r>0&&l<r) {ans+=1ll*x*(sum[r][0]-sum[l][0])+sum[r][1]-sum[l][1];}
			a-=siz,c-=siz;
			return;
		}
	} else {
		if (d<=15&&d+1<=k) {
			dfs2(2*x,d+1,1);
			if (chk(1)) {ans+=x;}
			a--,c--;
			if (chk(1)) {ans+=2*x+1;}
			a--,c--;
			dfs2(2*x+1,d+1,0);
			return;
		} else if (d>15) {
			int l,r,siz=(1<<(k-15))-3;
			if (a>0) {l=max(a-b,0);}
			else {l=0;}
			if (c>siz) {r=((c-siz)%b==0?siz:siz+(c-siz)%b-b);}
			else {r=c;}
			if (r>0&&l<r) {ans+=1ll*x*(sum2[r][0]-sum2[l][0])+sum2[r][1]-sum2[l][1];}
			a-=siz,c-=siz;
			return;
		}
	}
}
int main () {
	scanf("%d%d",&k,&q);
	dfs1(1,1,0,0,0);
	dfs1p5(1,1,0,0,0,0);
	for (int i=1;i<=q;i++) {
		scanf("%d%d%d",&a,&b,&c);
		c=a+(c-1)*b;
		for (int i=1;i<=tot;i++) {
			sum[i][0]=(i>=b?sum[i-b][0]:0)+num[i][0];
			sum[i][1]=(i>=b?sum[i-b][1]:0)+num[i][1];
			sum2[i][0]=(i>=b?sum2[i-b][0]:0)+num2[i][0];
			sum2[i][1]=(i>=b?sum2[i-b][1]:0)+num2[i][1];
		}
		ans=0;
		dfs2(1,1,0);
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：Leasier (赞：2)

~~这题在 NKOJ 上有一个更响亮的名字——弗斯。~~

- **看到这种题不一定需要把表打出来找规律。**

------------

堆式二叉树的性质是很好的，考虑如何**递归**表出 prufer 序：

- 假设我们考虑到一个高度为 $h$ 的子树，树根编号为 $id$。我们记其 prufer 序为 $P(op = 0/1, h, id)$，$op = 0$ 表示子树树根到父亲的边已被割断，$op = 1$ 反之。
- 当 $op = 0$，可以发现我们会先删完左子树，再删掉根，接着递归下去删右子树。即 $P(0, h, id) = P(1, h - 1, id \times 2) + [id \times 2 + 1] + P(0, h - 1, id \times 2 + 1)$。
- 当 $op = 1$，可以发现我们会先删完右子树，再删完右子树，最后删根。即 $P(1, h, id) = P(1, h - 1, id \times 2) + P(1, h - 1, id \times 2 + 1) + [\displaystyle\lfloor \frac{id}{2} \rfloor]$。

但暴力预处理 $P(0, k, 1)$ 显然是不好的。

由于每次询问的 $d$ 不同，我们单独考虑每个询问，则一个自然的想法是经典的**分层优化**：

- 设定阈值 $2 \leq S \leq k$。
- 预处理 $P(0, S, id), P(1, S - 1, id \times 2), P(1, S - 1, id \times 2 + 1)$ 的等差数列前缀和关于 $id$ 的线性表达式。
- 查询时递归到 $h = S$ 就利用预处理信息回答。

回答询问时差分一下转化为两个前缀询问，处理出所需前缀和信息即可。

时间复杂度为 $O(q(2^S + 2^{k - S}))$，当 $S = \frac{k}{2}$ 时取最优时间复杂度为 $O(q 2^{\frac{k}{2}})$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int mid, mid_size, len0 = 0, len1 = 0, len2 = 0;
int pid0[32767], cid0[32767], pid1[16387], cid1[16387], pid2[16387], cid2[16387], sum01[32767], sum02[32767], sum11[16387], sum12[16387], sum21[16387], sum22[16387];

inline int max(int a, int b){
	return a > b ? a : b;
}

void get_prufer(int op, int n, int pid, int cid, int &len, int pre_id[], int cur_id[]){
	if (op == 0){
		if (n == 2){
			len++;
			pre_id[len] = pid;
			cur_id[len] = cid;
			return;
		}
		get_prufer(1, n - 1, pid * 2, cid * 2, len, pre_id, cur_id);
		len++;
		pre_id[len] = pid * 2;
		cur_id[len] = cid * 2 + 1;
		get_prufer(0, n - 1, pid * 2, cid * 2 + 1, len, pre_id, cur_id);
	} else {
		if (n > 1){
			get_prufer(1, n - 1, pid * 2, cid * 2, len, pre_id, cur_id);
			get_prufer(1, n - 1, pid * 2, cid * 2 + 1, len, pre_id, cur_id);
		}
		len++;
		pre_id[len] = pid / 2;
		cur_id[len] = cid / 2;
	}
}

inline int min(int a, int b){
	return a < b ? a : b;
	
}

ll f(int op, int depth, int n, int m, int k, int id){
	if (m <= 0) return 0;
	int end = n + k * (m - 1);
	ll ans;
	if (op == 0){
		if (depth == mid){
			ans = (ll)sum01[end] * id + sum02[end];
		} else {
			int cur_size = (1 << (depth - 1)) - 1;
			if (end <= cur_size){
				ans = f(1, depth - 1, n, m, k, id * 2);
			} else {
				ans = 0;
				if (n <= cur_size) ans += f(1, depth - 1, n, (cur_size - n) / k + 1, k, id * 2);
				end -= cur_size + 1;
				if (end % k == 0) ans += id * 2 + 1;
				if (end >= 1) ans += f(0, depth - 1, (end - 1) % k + 1, (end - 1) / k + 1, k, id * 2 + 1);
			}
		}
	} else {
		if (depth == mid){
			if (end <= mid_size){
				ans = (ll)sum11[end] * id + sum12[end];
			} else {
				ans = 0;
				if (n <= mid_size){
					int end_ = (mid_size - n) / k * k + n;
					ans += (ll)sum11[end_] * id + sum12[end_];
				}
				end -= mid_size;
				if (end <= mid_size){
					ans += (ll)sum21[end] * id + sum22[end];
				} else {
					ans += id / 2;
					if (k - 1 <= mid_size){
						end -= k;
						ans += (ll)sum21[end] * id + sum22[end];
					}
				}
			}
		} else {
			int cur_size = (1 << (depth - 1)) - 1;
			if (end <= cur_size){
				ans = f(1, depth - 1, n, m, k, id * 2);
			} else {
				ans = 0;
				if (n <= cur_size) ans += f(1, depth - 1, n, (cur_size - n) / k + 1, k, id * 2);
				end -= cur_size;
				if (end <= cur_size){
					ans += f(1, depth - 1, (end - 1) % k + 1, (end - 1) / k + 1, k, id * 2 + 1);
				} else {
					ans += id / 2;
					if (k - 1 <= cur_size){
						end -= k;
						ans += f(1, depth - 1, (end - 1) % k + 1, (end - 1) / k + 1, k, id * 2 + 1);
					}
				}
			}
		}
	}
	return ans;
}

int main(){
	int k, q;
	scanf("%d %d", &k, &q);
	mid = max(k / 2, 2);
	mid_size = (1 << (mid - 1)) - 1;
	get_prufer(0, mid, 1, 0, len0, pid0, cid0);
	get_prufer(1, mid - 1, 2, 0, len1, pid1, cid1);
	get_prufer(1, mid - 1, 2, 1, len2, pid2, cid2);
	for (int i = 1; i <= q; i++){
		int a, d, m, r;
		scanf("%d %d %d", &a, &d, &m);
		r = (a - 1) % d + 1;
		for (int j = 1; j <= len0; j++){
			sum01[j] = pid0[j];
			sum02[j] = cid0[j];
			if (j >= d){
				sum01[j] += sum01[j - d];
				sum02[j] += sum02[j - d];
			}
		}
		for (int j = 1; j <= len1; j++){
			sum11[j] = pid1[j];
			sum12[j] = cid1[j];
			if (j >= d){
				sum11[j] += sum11[j - d];
				sum12[j] += sum12[j - d];
			}
		}
		for (int j = 1; j <= len2; j++){
			sum21[j] = pid2[j];
			sum22[j] = cid2[j];
			if (j >= d){
				sum21[j] += sum21[j - d];
				sum22[j] += sum22[j - d];
			}
		}
		printf("%lld\n", f(0, k, r, m + (a - 1) / d, d, 1) - f(0, k, r, (a - 1) / d, d, 1));
	}
	return 0;
}
```

---

