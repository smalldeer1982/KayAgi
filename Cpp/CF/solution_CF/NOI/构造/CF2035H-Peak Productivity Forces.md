# Peak Productivity Forces

## 题目描述

我们处在巅峰状态，来解决一个复杂的难题。

现有两组长度为 $n$ 的排列 $a$ 和 $b$。

你可以对排列 $a$ 进行如下操作：

1. 选择一个索引 $i$（$1 \le i \le n$）。
2. 将 $a_1, a_2, \ldots, a_{i-1}$ 按循环右移一位。如果选择了 $i = 1$，则这一部分不存在，因此无需移动。
3. 将 $a_{i + 1}, a_{i + 2}, \ldots, a_n$ 按循环右移一位。如果选择了 $i = n$，则这一部分不存在，因此也无需移动。

执行操作后，排列会从 $a_1, a_2, \ldots, a_{i-1}, a_i, a_{i+1}, \ldots, a_n$ 变成 $a_{i-1}, a_1, \ldots, a_{i-2}, a_i, a_n, a_{i+1}, \ldots, a_{n-1}$。

以下是长度为 $7$ 的单位排列 $[1, 2, 3, 4, 5, 6, 7]$ 的一些操作示例：

- 选择 $i = 3$，排列变为 $[2, 1, 3, 7, 4, 5, 6]$。
- 选择 $i = 1$，排列变为 $[1, 7, 2, 3, 4, 5, 6]$。
- 选择 $i = 7$，排列变为 $[6, 1, 2, 3, 4, 5, 7]$。

注意，第 $i$ 个位置的元素不发生位置变化。请尝试在最多 $2n$ 次操作中，使排列 $a$ 转换为排列 $b$。如果无法实现转换，请输出 $-1$。不需要最小化操作次数。已知如果可以转换，则在不超过 $2n$ 次操作内即可实现。

$^{\text{∗}}$ 长度为 $n$ 的排列是指包含 $1$ 到 $n$ 的任意顺序且互不重复的 $n$ 个整数组成的数组。例如，$[2, 3, 1, 5, 4]$ 是一个排列，但 $[1, 2, 2]$ 不是（因为 $2$ 重复出现），$[1, 3, 4]$ 也不是（因为缺少 $2$ 且多了 $4$）。

## 说明/提示

在第一个测试用例中，$a$ 已经等于 $b$，因此不需要操作。

在第二个测试用例中，可以证明 $a$ 无法变为 $b$。

在第三个测试用例中，经过两次操作后，$a$ 变成了与 $b$ 相同的排列。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
1
1
2
1 2
2 1
3
2 1 3
3 2 1
8
7 8 3 5 4 6 1 2
2 1 6 4 5 3 8 7```

### 输出

```
0

-1
2
1 3
7
3 4 5 1 2 1 1```

# 题解

## 作者：Milmon (赞：3)

## Statement

给定两个长度为 $n$ 的排列 $a, b$，你可以进行若干次如下操作：

- 选择 $1 \leq i \leq n$。
- 若 $1 < i$，令 $a_1, a_2, \cdots, a_{i - 1}$ 循环右移。
- 若 $i < n$，令 $a_{i + 1}, a_{i + 2}, \cdots, a_n$ 循环右移。

你需要构造一个操作序列使得 $a$ 变为 $b$ 或报告无解。你需要保证操作次数不超过 $2n$，可以证明若有解，一定存在操作次数不超过 $2n$ 的方案。

数据范围：数据组数 $T \leq 5 \times 10^4$，$1 \leq n \leq 5 \times 10^5$，$\sum n \leq 5 \times 10^5$。

## Solution

容易转化为将一个排列 $p$ 排序。考虑从大到小将数依次插入排列的开头，也就是说，排列总是以 $x, x + 1, \cdots, n$ 开头。

每次找到下一个数 $x$ 的位置 $i$，对 $i + 1$ 进行一次操作。容易发现这样可以把 $x$ 移动到开头，但是当 $i = n$ 时无法进行操作。此时只需要找到 $x - 1$ 的位置 $j$ 并对 $j + 1$ 进行一次操作，再对 $x$ 的新位置 $i'$ 分类讨论：

- 若 $x$ 在最后一个位置上，那么对 $1$ 进行一次操作，此时 $x$ 插入到 $x - 1$ 之后，完成要求。
- 若 $x$ 不在最后一个位置上，那么对 $i' + 1$ 进行一次操作，此时 $x$ 插入到 $x - 1$ 之前，但是此时 $x, x - 1$ 的顺序反了。

按照上述方案，可以得到一个 $n$ 在结尾，排列大体按照顺序，但是存在一些相邻的位置产生交换。此时已经使用了至多 $n + 1$ 次操作，我们需要在 $n - 1$ 次操作内完成最终调整。

对 $n$ 进行 $n - 1$ 次操作，此时排列不变。考虑如下调整：当一次对 $n$ 的操作之前，若 $p_{n - 1} = p_{n - 2} - 1$（即 $n - 1, n - 2$ 两个位置需要调整），就将此次操作改为对 $n - 1$ 操作。例如：$[6, 1, 2, 3, 5, 4, 7] \to [5, 6, 1, 2, 3, 4, 7] \to [4, 5, 6, 1, 2, 3, 7]$ 完成了调整。

于是我们找到了不超过 $2n$ 次操作的方案，暴力维护时间复杂度 $\Theta(n^2)$，不可接受。

考虑优化，注意到一次操作前后，对于大部分的值 $i$ 所在位置 $p$ 减去当前总操作次数不会改变，只有三个位置会改变，于是对值 $i$ 维护 $v_i$ 表示当前位置减去总操作次数，每次操作就只需要修改三个值。为了快速求一个位置的值，还需要维护 $v_i$ 表示当前第 $i +$ 总操作次数个位置上的值。于是我们可以 $\Theta(1)$ 进行一次操作、查询一个位置的值、查询一个值的位置。总时间复杂度 $\Theta(n)$。

## Solution (English)

It is easy to transform the problem into sorting a permutation $p$. Consider inserting the numbers in descending order at the beginning of the permutation, meaning that the permutation always starts with $x, x + 1, \cdots, n$.

Each time, find the position $i$ of the next number $x$ and perform an operation on $i + 1$. It is easy to see that this can move $x$ to the front, but when $i = n$, no operation can be performed. At this point, we only need to find the position $j$ of $x - 1$ and perform an operation on $j + 1$. Then, we classify the discussion for the new position $i'$ of $x$:

- If $x$ is in the last position, then perform an operation on $1$. At this point, $x$ is inserted after $x - 1$, completing the requirement.
- If $x$ is not in the last position, then perform an operation on $i' + 1$. At this point, $x$ is inserted before $x - 1$, but the order of $x$ and $x - 1$ is reversed.

Following the above scheme, we can achieve a sequence ending with $n$, where the permutation is generally in order, but some adjacent positions have been swapped. At this point, at most $n + 1$ operations have been used, and we need to complete the final adjustment within $n - 1$ operations.

Performing $n - 1$ operations on $n$ keeps the permutation unchanged. Consider the following adjustment: before performing an operation on $n$, if $p_{n - 1} = p_{n - 2} - 1$ (i.e., the positions $n - 1$ and $n - 2$ need adjustment), change this operation to operate on $n - 1$. For example: $[6, 1, 2, 3, 5, 4, 7] \to [5, 6, 1, 2, 3, 4, 7] \to [4, 5, 6, 1, 2, 3, 7]$, completing the adjustment.

Thus, we have found a solution that requires no more than $2n$ operations, while the brute-force maintenance has a time complexity of $\Theta(n^2)$, which is unacceptable.

Consider optimization. Noting that before and after an operation, for most values $i$, the position $p$ minus the current total number of operations does not change, only three positions will change. Thus, we maintain $v_i$ for value $i$, indicating the current position minus the total number of operations, so each operation only needs to modify three values. To quickly obtain the value at a position, we also need to maintain $v_i$, which indicates the value at the current position for the $i$-th total operation. Therefore, we can perform an operation, query the value at a position, and query the position of a value in $\Theta(1)$. The total time complexity is $\Theta(n)$.

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[500001],b[500001],pos[500001];
vector<int> ops;

struct{
    int n,p[500001],v[1500001],tag;
    inline void init(int _n){
        n=_n,tag=0;
        for(int i=1;i<=n;i++)pos[b[i]]=i;
        for(int i=1;i<=n;i++)p[pos[a[i]]]=i,v[i+n*2]=pos[a[i]];
    }
    inline int &get(int x){
        return v[x+n*2-tag];
    }
    inline int find(int x){
        return p[x]+tag;
    }
    inline void force(int x,int y){
        get(y)=x,p[x]=y-tag;
    }
    inline void operate(int x){
        ops.push_back(x);
        int l=x>1?get(x-1):0,m=get(x),r=get(n);
        tag++,x>1?force(l,1):void(),force(m,x),x<n?force(r,x+1):void();
    }
}_;

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",a+i);
        for(int i=1;i<=n;i++)scanf("%d",b+i);
        ops.clear();
        _.init(n);
        for(int i=n;i>=1;i--){
            int pos=_.find(i);
            if(pos<n)_.operate(pos+1);
            else if(i>1){
                _.operate(_.find(i-1)+1);
                pos=_.find(i);
                _.operate(pos<n?pos+1:1);
                if(i<n)i--;
            }
            else _.operate(1);
        }
        for(int i=1;i<n-1;i++){
            if(i!=n-1&&_.get(n-2)==_.get(n-1)+1)_.operate(n-1),i++;
            _.operate(n);
        }
        if(_.get(1)!=1)_.operate(n);
        bool flag=true;
        for(int i=1;i<=n;i++)flag&=_.get(i)==i;
        if(!flag){
            puts("-1");
            continue;
        }
        int m=(int)ops.size();
        printf("%d\n",m);
        for(int i=0;i<m;i++)
            printf("%d%c",ops[i]," \n"[i==m-1]);
    }
    return 0;
}
```

---

## 作者：zyh_helen (赞：1)

_我们处在巅峰状态，来解决一道复杂的难题。_

 ---
 ---

#### 大思路

首先我们发现我们把这两个排列复合一下，就相当于个一个排列排序了。

然后乍看这个题非常难以入手（实则确实难以入手），考虑将操作形象化一下，我们每次相当于连续进行下面两个操作：
- 把最后面的数移到某个数后面；
- 把那个数前面的数移到最前面。

一般这种同时有两个操作的可以先只考虑其中一个，发现只考虑第一个操作并不好操作（因为换到中间的很容易被再次换走）。

我们考虑第二个操作，发现和选择排序的过程非常相似，就是从大到小把每个数放到第一个位置即可，并且，因为每次找到的数都在我们维护的排好序的段的后面，所以第二个操作并不会影响到我们排好序的段，这样我们有了一个很棒的大思路。

我们发现这样做的问题在于如果我们要找的数的位置在最后一个地方，我们没有办法把它挪到最前面（因为我们每次是操作那个数的位置后面的一个数）。

---

#### 难点

我们灵光一现，注意到如果直接把最后一个数移到第二个位置（对第一个数进行操作），最后操作出来的序列会具有某些特征，即不存在 $i,j,k$ 满足 $a_i>a_j$ 且 $a_i>a_k$（其实这个结论不完全正确，有一个小细节最后再说）。

然后我们还有 $n$ 次左右的操作机会，好好利用一下这个性质，我们再次从 $n-1$ 开始倒着枚举一下所有数，如果这个数在第 $n-1$ 个位置我们就操作 $n$，否则其就在第 $n-2$ 个位置我们操作 $n-1$，注意到这两个操作对后面都没有影响，相当于对前 $n-1$ 个数又进行了一次选择排序。

这样子理论操作次数是 $2n-1$，完成了这道题。

---

#### 一些细节

- 注意到我们第一次选择排序的时候必须保证最后一个数是 $n$，这样子第一次操作如果 $n$ 在最后面就要操作两次把它换到最前面；

- 还是注意到第一次选择排序的时候必须保证最后一个数是 $n$，第二次操作的时候如果 $n-1$ 在最后面不能直接把它换到第二个位置（会导致最后一个数变成 $n-1$），还需要再操作一次第三个位置（把 $n$ 和 $n-1$ 换过来）；

- 注意到我们第一次选择排序的时候如果碰到连着两个数都在最后面我们都换到第二个数去，就不能维持我们所需要的性质（第一个数大于第二个数且第一个数大于第三个数），这个时候我们需要先对最后一个位置操作再对第一个位置操作，可以使得这两个数都调到最前面去（可以自行手模一下）；

- 注意到如果我们前面两个细节都被满足的情况下操作次数是 $2n+1$ 的，这个时候我们略微修改一下第一个细节的操作位置即可。

---

#### 实现

在维护操作的时候需要用平衡树，因为作者非常的~~可爱~~唐氏，不会打平衡树一个平衡树调了两个晚上。

---

#### 代码

```cpp
void work(int x){
	int x1, x2, x3;
	if(x > 2){
		split(rt, x - 1, x1, x2);
		split(x1, x - 2, x1, x3);
		rt = merge(merge(x3, x1), x2);
	}
	if(x < n - 1){
		split(rt, n - 1, x1, x2);
		split(x1, x, x1, x3);
		rt = merge(x1, merge(x2, x3));
	}
	ans.push_back(x);
}
signed main(){
	int T;
	cin >> T;
	while(T--){
		cin >> n;
		for(int i = 1;i <= n;i++)scanf("%d", a + i);
		cnt = rt = 0;
		for(int i = 1;i <= n;i++){
			int x;
			scanf("%d", &x);
			b[x] = i;
		}
		for(int i = 1;i <= n;i++)a[i] = b[a[i]];
		if(n <= 2){
			if(a[1] == 1)printf("0\n");
			else printf("-1\n");
			continue;
		}
		ans.clear();
		for(int i = 1;i <= n;i++)addnew();
		for(int i = 1;i <= n;i++)rt = merge(rt, a[i]);
		int st = n;
		if(a[n] == n){
			if(a[n - 2] == n - 1 && n >= 4)work(n - 2);
			else if(a[n - 1] == n - 1 && n >= 4){
				work(n);
				work(1);
				st = n - 2;
			}
			else work(1);
		}
		for(int i = st;i;i--){
			int x = ask(i);
			if(x < n)work(x + 1);
			else {
				if(i == 1){
					work(1);
					continue;
				}
				int xx = ask(i - 1);
				if(xx != n - 1){
					work(1);
					if(i == n - 1)work(3);
				}
				else {
					work(n);
					work(1);
					i--;
				}
			}
		}
		for(int i = n - 1;i;i--){
			if(ask(i) == n - 1)work(n);
			else work(n - 1);
		}
		cout << ans.size() << endl;
		for(int x : ans)printf("%d ", x);
		putchar('\n');
	}
	return 0;
}

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2035H)

**题目大意**

> 给定两个 $n$ 阶排列 $a,b$，每次操作可以选择一个 $i$，然后把 $a[1,i-1],a[i+1,n]$ 分别向右循环移位一位，构造一组 $2n$ 次操作以内使得 $a=b$ 的操作序列。
>
> 数据范围：$n\le 5\times 10^5$。

**思路分析**

很显然可以转成给 $a$ 排序的问题。

这种用循环移位还原排列的问题，可以维护一个 $[x,x+1,\dots,n]$ 的子串在序列开头，然后每次把 $x-1$ 放到序列开头。

如果 $x-1$ 的位置 $p<n$，那么直接操作 $p+1$ 即可。

否则我们先把 $x-2$ 放到开头，如果此时依然有 $p=n$，那么我们操作位置 $1$ 就能让开头变成 $[x-2,x-1]$，否则我们操作 $p+1$，此时开头变为 $[x-1,x-2]$。

那么我们按照这个方式构造到 $x=1$，此时整个排列几乎有序，只有若干个 $x$ 使得 $a_{x+1}=x,a_x=x+1$。

考虑如何复原这部分，保证 $a_n=n$，然后不断操作位置 $n$，那么 $a[1,n-1]$ 会不断循环移位 $n-1$ 次。

如果 $a_{n-2}=a_{n-1}+1$，那么此时改为操作 $n-1$ 和 $n$ 即可交换这两个元素。

用上述方式还原排列，由于我们要保证 $a_n=n$，因此第一部分至多操作 $n+1$ 次，第二部分操作 $n-1$ 次，总次数 $\le 2n$。

然后我们需要一个数据结构支持快速维护上述操作，注意到每次操作实际上会把绝大部分元素向右循环移位，只会单点修改 $\mathcal O(1)$ 个位置，因此维护一个支持循环移位的数组即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
int n,A[MAXN],B[MAXN],z[MAXN];
struct arr {
	int tg,p[MAXN],a[MAXN*3];
	void init() { tg=0,fill(p+1,p+n+1,0),fill(a+1,a+3*n+1,0); }
	inline int operator [](int i) { return a[i+2*n-tg]; }
	inline int operator ()(int x) { return p[x]+tg; }
	inline void set(int i,int x) { p[x]=i-tg,a[i+2*n-tg]=x; }
}	a;
void opr(int i) {
	int l=(i>1?a[i-1]:0),x=a[i],r=(i<n?a[n]:0);
	++a.tg,a.set(i,x),cout<<i<<" ";
	if(l) a.set(1,l);
	if(r) a.set(i+1,r);
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;++i) cin>>A[i];
	for(int i=1;i<=n;++i) cin>>B[i],z[B[i]]=i;
	if(n==1) return cout<<"0\n\n",void();
	if(n==2) return cout<<(A[1]==B[1]?"0\n\n":"-1\n"),void();
	for(int i=1;i<=n;++i) a.set(i,z[A[i]]);
	if(a(n)<n) cout<<2*n-1<<"\n",opr(a(n)+1);
	else cout<<2*n<<"\n",opr(1),opr(3);
	for(int x=n-1;x>=1;--x) {
		int p=a(x);
		if(p<n) opr(p+1);
		else if(x==1) opr(1);
		else opr(a(x-1)+1),opr(a(x)==n?1:a(x)+1),--x;
	}
	for(int i=1;i<n;opr(n),++i) if(i<n-1&&a[n-2]==a[n-1]+1) opr(n-1),++i;
	cout<<"\n",a.init();
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

