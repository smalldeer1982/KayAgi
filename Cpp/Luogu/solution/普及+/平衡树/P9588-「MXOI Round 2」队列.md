# 「MXOI Round 2」队列

## 题目描述

小 C 有一个队列，他要对这个队列进行 $q$ 次操作。操作共四种，参数分别如下：

$1\ x$：这是第一种操作，表示从队尾依次插入 $1,2,3,\cdots,x$；

$2\ y$：这是第二种操作，表示弹出队头的前 $y$ 个元素；

$3\ z$：这是第三种操作，表示查询队列中的第 $z$ 个元素；

$4$：这是第四种操作，表示查询队列中所有元素的最大值。

你需要帮助他维护这个队列，并对于每个第三种操作和第四种操作，输出查询的答案。

## 说明/提示

#### 【样例解释 #1】

在进行第四次操作后，队列中的元素依次为 $3,4,5,1,2,3,1,2,3,4$。

在进行第七次操作后，队列中的元素依次为 $2,3,1,2,3,4$。

#### 【样例 #2】

见附加文件中的 `queue/queue2.in` 与 `queue/queue2.ans`。

该样例满足测试点 $1$ 的限制。

#### 【样例 #3】

见附加文件中的 `queue/queue3.in` 与 `queue/queue3.ans`。

该样例满足测试点 $4$ 的限制。

#### 【样例 #4】

见附加文件中的 `queue/queue4.in` 与 `queue/queue4.ans`。

该样例满足测试点 $11$ 的限制。

#### 【样例 #5】

见附加文件中的 `queue/queue5.in` 与 `queue/queue5.ans`。

该样例满足测试点 $15$ 的限制。

#### 【样例 #6】

见附加文件中的 `queue/queue6.in` 与 `queue/queue6.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

设 $\sum x$ 表示单个测试点内 $x$ 之和。

对于 $100\%$ 的数据，$1 \le q \le 2\times 10^5$，$1 \le x,y,z \le 10^9$，$0 \le \sum x \le 2\times10^{14}$，保证在进行第二种操作前队列内元素个数不小于 $y$，在进行第三种操作前队列内元素个数不小于 $z$，在进行第四种操作前队列内元素个数大于 $0$。

|测试点编号|$q \le$|$x \le$|$\sum x \le$|特殊性质|
|:---:|:---:|:---:|:---:|:---:|
|$1\sim3$|$500$|$500$|$2\times10^5$|C|
|$4\sim8$|$5000$|$5000$|$2\times10^7$|无|
|$9\sim10$|$2\times10^5$|$10^9$|$2\times10^{14}$|AB|
|$11\sim12$|$2\times10^5$|$10^9$|$2\times10^{14}$|B|
|$13\sim14$|$2\times10^5$|$10^9$|$2\times10^9$|AC|
|$15\sim16$|$2\times10^5$|$10^9$|$2\times10^9$|C|
|$17\sim18$|$2\times10^5$|$500$|$2\times10^7$|无|
|$19$|$2\times10^5$|$10^9$|$2\times10^9$|无|
|$20$|$2\times10^5$|$10^9$|$2\times10^{14}$|无|

特殊性质 A：没有第二种操作。

特殊性质 B：没有第三种操作。

特殊性质 C：没有第四种操作。

## 样例 #1

### 输入

```
0 9
1 5
1 3
2 2
1 4
3 6
3 8
2 4
4
3 3```

### 输出

```
3
2
4
1```

# 题解

## 作者：Crosser (赞：35)

这个和 [另一个普及模拟赛的题](https://www.luogu.com.cn/problem/P7870) 差不多。

我们考虑类似的进行操作，但是这个题多出来了三个更复杂的部分：

- 这是个队列，删除从头删而非从尾删。
- 有最大值操作。
- 有查询第 $x$ 个元素操作。

我们不难逐一解决。

首先对于第一个，我们不会真的删掉，而是通过一个变量 $d$ 记录删掉了多少个，那么如果查询第 $i$ 个元素，真正下标的就是 $d+i$。

对于第二个，我们使用 `std::multiset` 维护即可。注意到算最大值仍然只有右端点有用。考虑删除操作最多只会删除 $q$ 次，所以暴力找就可以了，复杂度依然不会爆掉。

对于第三个，结合上面算出来的 $d$，使用二分即可。

于是所有操作均在 $\mathcal O(\log q)$ 或 $\mathcal O(1)$ 时间内解决。

```cpp
int a[200005], s[200005], n;
multiset<int> ms;

void push(int w)
{ 
    a[++n] = w;
    s[n] = s[n - 1] + w;
    ms.insert(w);
}
signed main()
{
    int res = 0, id = 1;
    int q = read();
    q = read();
    while (q--)
    {
        int op = read();
        if (op == 1)
        {
            int x = read();
            push(x);
        }
        if (op == 2)
        {
            int y = read();
            res += y;
            while(s[id] <= res && id <= n) {
                ms.erase(ms.find(a[id]));
                id++;
            }
        }
        if (op == 3)
        {
            int z = read() + res;
            int pos = lower_bound(s + 1, s + n + 1, z) - s - 1;
            cout << z - s[pos] << endl;
        }
        if(op == 4)
        {
            cout << *ms.rbegin() << endl;
        }
    }
    return 0;
}
```

---

## 作者：Coffee_zzz (赞：19)

### Task 1~3

模拟，记录队头和队尾每次 $O(x)$ 进行操作一，$O(1)$ 进行操作二和操作三，总复杂度 $O(xq)$。

### Task 4~8

如果还是模拟，操作四的复杂度是 $O(\sum x)$，最劣是 $O(xq)$，总复杂度为 $O(xq^2)$，会超时。

我们考虑如何快速进行操作四。

我们把每次插入的 $x$ 个数分为一组。容易发现，每组中的最大值都是 $x$ 且 $x$ 都在最后一位。也就是说，如果删除操作没有把这组全部删完，那么这组的最大值 $x$ 是不会被删掉的。

我们使用 STL 中的 multiset（可重集），定义一个可重集 $s$，记录还存在的每个组的最后一个数。

每次操作一，我们额外在 $O(\log q)$ 的时间内把 $x$ 插入到 $s$ 中。

每次操作二，我们用 $O(y)$ 的时间把所有删除的元素都扫一遍，如果发现了某个组的最后一个元素 $k$ 被删除，那么就使用可重集中的 $erase$ 函数，在 $s$ 中删除一个 $k$。要注意想要实现只删除一个数，只能使用删除迭代器的方式。如果使用 $erase(k)$ 会把所有为 $k$ 的元素全部删除。

操作三还和之前一样，$O(1)$ 查询。而对于操作四，直接输出 $s$ 的最后一个元素即可。

当然，这些操作也可以用优先队列等实现。

### Task 9~10

没有操作二和操作三，那么在进行操作一的时候，记录一下所有 $x$ 的最大值 $ma$，进行操作四时直接输出 $ma$ 即可。

### Task 11~12

没有操作三，但是 $x$ 的值域飙到了 $10^9$。现在，对于每次操作一，我们不能暴力添加了。

我们考虑，每次添加时，只记录 $x$ 的值，而不把 $x$ 个数全部添加。

我们把每次插入的 $x$ 个数分为一组，开两个数组 $num$ 和 $las$，分别存每一组中原本的元素个数和剩余的元素个数。初始时 $num_i=las_i$。

我们还是开一个可重集 $s$。对于每个操作一，在记录了 $num$ 的值和 $las$ 的值后，把 $x$ 插入到 $s$ 中。

对于每个操作二，我们设队头为 $head$，重复循环直到 $y=0$。

如果 $y \ge las_{head}$，那么这一组的数就被全部删完了，将 $s$ 中的一个 $num_{head}$ 删除，并把 $y$ 设为 $y-las_{head}$，将 $head$ 增加 $1$。

反之，$y \lt las_{head}$，那么只能删除这一组剩下的数中的前 $y$ 个数。我们将 $las_{head}$ 减去 $y$，将 $y$ 设为 $0$，退出循环。

而操作四不变，直接输出 $s$ 的最后一个元素即可。

操作一和操作四的时间复杂度都是 $O(\log q)$，我们分析一下操作二的时间复杂度。

我们知道，循环的重复次数跟是否删完一组有关。只有删完一组才会进行下一次循环，由于每个组只会被删一次，所以总的循环次数不会超过进行操作一的次数加进行操作二的次数，均摊下来时间复杂度为 $O(\log q)$。

每种操作的复杂度都为 $O(\log q)$，总复杂度 $O(q \log q)$，可以通过。

### Task 13~14

我们还是把每次插入的 $x$ 个数分为一组。我们开一个数组 $num$ 来存每一组的元素个数 $x$，再开一个 $num$ 数组的前缀和数组 $sum$。其中 $sum_i=\sum\limits_{j=1}^i num_j$。

对于操作一，我们用 $O(1)$ 的时间记录 $num$ 和 $sum$ 的值。

对于操作三，我们在 $sum$ 数组中二分出第一个大于等于 $z$ 的 $sum_t$，也就是求出第 $z$ 个元素所在的组，而答案显然就是 $z-sum_{t-1}$，复杂度 $O(\log q)$。

总复杂度 $O(q \log q)$，可以通过。

### Task 15~16

我们在 Task 13~14 的基础上考虑操作二的处理方法。

我们可以干脆不处理操作二，只记录当前所有操作二的 $y$ 之和 $d$。

对于每个操作三，我们要查询的可以转化为不删除的队列的第 $d+z$ 个元素。那么我们还是在 $sum$ 数组中二分出第一个大于等于 $d+z$ 的 $sum_t$，输出 $z-sum_{t-1}$ 的值即可。

操作三的复杂度为 $O(\log q)$，其余操作的复杂度为 $O(1)$，总复杂度 $O(q \log q)$。

### Task 17~20

把 Task 11~12 的利用可重集的查询方法和 Task 15~16 的利用二分的查询方法缝合，操作三用二分查询，操作四用可重集查询，每个操作的复杂度都是 $O(\log q)$，总复杂度 $O(q \log q)$。

---

## 作者：Milthm (赞：11)

## P9588 题解



### 前置知识

- 二分

- 队列

- 线段树

### 题目解法



很好想到的是用一个队列，每个元素 $(l,r)$ 记录一个上升数列的开头和结尾，那我们依次分析一下其它操作怎么去做。

- 对于操作 $1$，直接往队尾插入一个 $(1,x)$。

- 对于操作 $2$，我们直接暴力删除，因为队列加入的最多有 $q$ 个元素（注意这里不是题目中的队列），所以怎么删除一共也不会删掉超过 $q$ 个元素，不会超时。

- 对于操作 $3$，暴力找肯定超时（我赛时就是因为没有想到这一点而痛失 AK）。考虑维护一个前缀和数组，因为前缀和肯定是单调的，所以用二分就可以找到对应的元素了。

但问题是，前缀和数组在操作 $2$ 的时候，每删除一遍就要遍历一遍整个数组，肯定会超时。所以我们用一个变量记录所有删掉的元素数量，查询的时候把它加上再查就可以了。

- 对于操作 $4$，容易发现一次插入一个 $(1,x)$，最大值一定是 $x$ 中最大的那个。同时，在修改操作的时候，还需要对最大值进行修改。单点修改，区间查询最大值，这不就是线段树吗（虽然线段树连区间修改都支持）！

所以我们用一个线段树维护这个就可以了。时间复杂度 $O(q \log q)$，可以通过本题。

### AC 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
#define int long long
using namespace std;
int c,Q,h=1,t=0,f[800005],a[1600005],n=400005,del; 
int l[800005],r[800005];
int read(){
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
//以下为单点修改的线段树
void update(int x,int l,int r,int ql,int qr,int k){
	if(ql<=l&&r<=qr){
		a[x]=k;return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)update(x*2,l,mid,ql,qr,k);
	if(qr>mid)update(x*2+1,mid+1,r,ql,qr,k);
	a[x]=max(a[x*2],a[x*2+1]);
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){
		return a[x];
	}
	int mid=(l+r)>>1,sum=0;
	if(ql<=mid)sum=max(sum,query(x*2,l,mid,ql,qr));
	if(qr>mid)sum=max(sum,query(x*2+1,mid+1,r,ql,qr));
	return sum;
}
//线段树结束（单点修改的线段树挺短的）
signed main(){
	cin>>c>>Q;
	while(Q--){
		int op,x;
		op=read();
		if(op==1)x=read(),l[++t]=1,r[t]=x,update(1,1,n,t,t,x),f[t]=f[t-1]+x;//记得更新前缀和和线段树
		else if(op==2){
			x=read();int cnt=0;
			for(int i=h;i<=t;++i){
				cnt+=r[i]-l[i]+1;
				if(cnt>=x){
					cnt-=r[i]-l[i]+1;
					l[i]+=x-cnt;del+=x-cnt;
					if(l[i]>r[i])update(1,1,n,i,i,0),++h;//注意在删掉一个 r 的时候也清一下线段树
					break;
				}
				del+=r[i]-l[i]+1;r[i]=l[i]=0;++h;//更新
				update(1,1,n,i,i,0);//清空
			}
		}
		else if(op==3){
			x=read();
			int qwq=lower_bound(f+h,f+t+1,del+x)-f;//二分
			printf("%lld\n",del+x-f[qwq-1]);
		}
		else{
			printf("%lld\n",query(1,1,n,h,t));
		}
	}
	return 0;
}

```


---

## 作者：shinzanmono (赞：11)

我们考虑转化问题，将所有操作变为一个长度为 $q$ 的数组。

令 $s_i$ 表示这个数组的前缀和。

对于操作一，实质上是把第 $i$ 个位置上的数变为 $x$。

对于操作二，实质上是找出最大的 $i$ 满足 $s_i<y$，然后区间赋 $0$，然后修改 $i+1$。

对于操作三，实质上是找出最大的 $i$ 满足 $s_i<z$，然后在 $i+1$ 里求值。

对于操作四，试着上找到当前所有在数组里的右端点的最大值，可以用 `multiset` 维护。

单点修改，区间修改，求前缀和，这显然可以用线段树解决。找到最大的 $i$ 满足 $s_i<y$ 显然可以用二分解决。

这样的解法是 $O(n\log^2n)$，可以通过此题。

---

## 作者：佬头 (赞：9)

## Description

你需要维护一个[**队列**](https://www.luogu.com.cn/problem/P9588)，操作共四种，参数分别如下：
1. 从队尾依次插入 $1,2,3,\cdots,x$；
2. 弹出队头的前 $k$ 个元素；
3. 查询队列中的第 $k$ 个元素；
4. 查询队列中所有元素的最大值。

维护队列的同时对于每个操作三和操作四，输出查询的答案。

## Solution
对于**操作一**，由于 $\sum x\le2\times10^{14}$，所以考虑直接使用 $x$ 代表整个序列插入，时间复杂度 $\mathcal{O}(1)$。

对于**操作二**和**操作三**，首先可以想到遍历整个队列，同时维护一个前缀和 $sum$ 表示目前遍历到第 $sum$ 个元素，当 $k\le sum+x$ 时，输出 $k-sum$，时间复杂度 $\mathcal{O}(n^2)$（$n$ 表示操作一的数量，下同），当然还需要一点标记和特判，但这不是重点。

由于我们每次都要取一个前缀和，因此我们可以在进行操作一的同时求一下 $x$ 的**前缀和** $sum$，然后在前缀和上进行**二分**。维护一个 $p$ 表示一共弹出过 $p$ 个元素。对于操作二便直接更新 $p\gets p+k$，时间复杂度 $\mathcal{O}(1)$；而对于操作三我们只需要在前缀和数组中二分出第一个大于等于 $p+k$ 的下标，计为 $i$，输出 $p+k-sum_{i-1}$，时间复杂度 $\mathcal{O}(\log n)$。

对于**操作四**，很显然可以维护一个关于 $x$ 的**单调递减队列**（在 $x$ 所代表的序列中 $x$ 一定为整个序列的最大值并且在序列的末尾）。由于操作二的弹出操作，则需要同时对队列中的每一个 $x_i$，我们要记录下它的 $sum_i$，当 $sum_i\le p$ 时，则将 $x_i$ 和 $sum_i$ 一并弹出。最后输出队列中的第一个元素，总时间复杂度 $\mathcal{O}(n)$。

总时间复杂度为 $\mathcal{O}(q+m\log n)$（$m$ 表示操作三的数量）。

## Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200005;
int q, que[N], front, back, rt, x;
long long id[N], sum[N], p;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	q = (read(), read());
	for(int i = 1; i <= q; ++ i){
		int x = read();
		if(x == 1){
			x = read();
			sum[rt] = sum[rt ++] + x;
			while(front <= back && que[back] <= x) back --;
			que[++ back] = x;
			id[back] = sum[rt];
		}
		else if(x == 2) p += read();
		else if(x == 3){
			x = read();
			write(p + x - sum[lower_bound(sum + 1, sum + rt, p + x) - sum - 1]), puts("");
		}
		else if(x == 4){
			while(front <= back && id[front] <= p) ++ front;
			write(que[front]), puts("");
		}
	}
	return 0;
}
```

其实也可以再稍微优化掉一个数组 $id$，用单调队列直接维护前缀和数组 $sum$ 的下标，这里设为 $i$，$x_i$ 就是 $sum_i-sum_{i-1}$。 

---

## 作者：XiaoQuQu (赞：8)

观察一下发现不用存整个队列，实际有用的信息就只有至多 $q$ 个二元组 $(st,v)$ 表示有从 $st$ 到 $v$ 这些数字。

考虑我们怎么对这四种操作维护这个信息，发现删除操作不必真的进行在我们的二元组上，而是可以维护一个偏移量 $d$，表示对于任何给定的操作数 $x$，实际的操作数应该为 $d+x$。

对于 $3$ 操作，可以考虑在我们维护的这个二元组序列上二分，维护二元组的时候同时维护一个个数的前缀和 $s$，二分一个最大的 $k$ 使得 $s_k<x$，其中这里的 $x$ 是偏移后的 $x$，最终答案就是 $x-s_k$。

对于 $4$ 操作，可以维护一个 `multiset`，每次插入新的二元组时将右端点插入这个集合 $S$ 中，在 $2$ 操作时，从上一个有效的二元组 $i$（即没有完全被偏移量 $d$ 覆盖的二元组，也就是 $s_i> d$）开始到目前删除的二元组 $j$，将二元组 $i\cdots j$ 的右端点全部从 `multiset` 中删除即可。

可能需要开 `long long`，这里使用了 `define int long long`。

```cpp
const int MAXN = 2e5 + 5;
int c, n, s[MAXN], del, stt, tot;
multiset<int> st;
struct _node {
	int v, st;
} q[MAXN];

void delone(int x) {
	auto it = st.find(x);
	if (it == st.end()) return;
	st.erase(it);
}

void insert(int x) {
	q[++tot] = {x, 0};
	s[tot] = s[tot - 1] + x;
	st.insert(x);
}

void pop(int x) {
	x += del; del = x;
	int l = 1, r = tot, ans = 0;
	while (l <= r) {
		if (s[mid] < x) ans = mid, l = mid + 1;
		else r = mid - 1;		
	}
	for (int i = stt + 1; i <= ans; ++i) delone(q[i].v);
	x -= s[ans], q[ans + 1].st = x;
	if (q[ans + 1].st == q[ans + 1].v) delone(q[ans + 1].v), ++ans;
	stt = ans;
}

int kth(int x) {
	x += del;
	int l = 1, r = tot, ans = 0;
	while (l <= r) {
		if (s[mid] < x) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	x -= s[ans];
	return x;
}

int mxx() {
	auto it = st.end(); --it;
	return *it;
}

void work() {
	cin >> c >> n;
	for (int i = 1; i <= n; ++i) {
		int opt, x; cin >> opt;
		if (opt == 1) cin >> x, insert(x);
		if (opt == 2) cin >> x, pop(x);
		if (opt == 3) cin >> x, cout << kth(x) << endl;
		if (opt == 4) cout << mxx() << endl;
	}
}
```


---

## 作者：MornStar (赞：7)

# P9588 队列题解
~~大模拟~~
## 题目

[P9588](https://www.luogu.com.cn/problem/P9588)

## 思路
注意到第一种操作的 $\sum{x}$ 太大，肯定不能直接装。但是操作次数较小，所以可以合并成一块再塞到队列里面。

塞进去的块需要维护三个信息：长度，第几个入队，已经弹出几个数。

接下来我们一个一个操作分析。

为了方便与快速，我使用的数组模拟队列。

#### 操作一
照着上面说的直接塞进去就行了。

#### 操作二
使用前缀和 $sum_i$ 记录到第 $i$ 个块位置总共入队了多少个数。

同时记录已经出队了多少个数，假设把这些数再塞回去，用前缀和数组辅助，就可以二分求出这个操作会删除到第几个块第几个数。

示意图：
![](https://cdn.luogu.com.cn/upload/image_hosting/zb1sbqry.png)

找到第一个前缀和大于已删除与待删除区间长度之和的块就行。

同时将队列的右端点设为这个块，并且修改这个块已经弹出了几个数（为已删除与待删除区间长度之和减去这个块前一个块的前缀和）。

#### 操作三

跟操作二差不多，只是把删除改成了输出结果而已。

有一个小细节，如果查询到的位置在这个块前一个块的末尾，要输出前一个块的长度而不是 $0$。

#### 操作四

维护最大值，因为一个块里的最大值等于这个块的长度，且最大值是最后出队的元素，所以变成了维护还未出队的块的长度最大值。

使用优先队列记录，优先队列里面的结构体记录着这个块的长度，第几个入队的信息，并以长度为关键值排序。

操作是看队首是否还在原队列里（即入队编号大于等于目前左端点），如果在，就输出。否则弹出队首，继续判断。

最多只会出入队列 $2\times 10^5$ 次，时间完全足够。

合起来就是本题的程序了。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct block{
	long long len,num,now;
};
struct node{
	long long len,num;
	friend bool operator<(node a,node b){
		if(a.len!=b.len)	return a.len<b.len;
		return a.num>b.num;
	}
};
block q[200005];
priority_queue<node>heap;
long long c,n,cnt,l=1,erase_now,sum[200005];
int main(){
	cin>>c>>n;
	for(int i=1,opt;i<=n;i++){
		cin>>opt;
		if(opt==1){
			long long x;
			cin>>x;
			++cnt;
			q[cnt]={x,cnt,0};
			heap.push({x,cnt});
			sum[cnt]=sum[cnt-1]+x;
		}else if(opt==2){
			long long y;
			cin>>y;
			int pos=upper_bound(sum+l,sum+cnt+1,erase_now+y)-sum;//找第一个大于
			l=pos;
			erase_now+=y;
		}else if(opt==3){
			long long z;
			cin>>z;
			int pos=upper_bound(sum+l,sum+cnt+1,erase_now+z)-sum-1;//找最后一个小于
			cout<<(erase_now+z-sum[pos]==0?q[pos].len:erase_now+z-sum[pos])<<'\n';//小细节
		}else{
			while(1){
				if(heap.top().num<l)	heap.pop();
				else{
					cout<<heap.top().len<<'\n';
					break;
				}
			}
		}
	}
}
```
均摊复杂度 $O(q\log q)$，可以通过。



---

## 作者：_determination_ (赞：5)

前排提醒：这是一篇平衡树题解

最近在练平衡树，突然发现了这道题。感觉质量很好。

如果给每个数都开节点是肯定要寄的。发现插入和删除操作都是对一个或多个区间进行操作。所以我们可以只记左右端点。这样每次操作只会多出一个节点，时间空间均可以承受。笔者使用 `FHQ-Treap` 进行维护。

## 操作 1：

直接新建一个节点并与原树合并即可。

```cpp
void ins(int l,int r)
{
    root=merge(root,new_node(l,r));
}
```

## 操作二

删除前面的节点，我们一般将树分裂成两半并舍去左半。分裂原则为区间长度。即区间的 `r` 比 `y` 小或相等的时候扔进左子树。

我们发现我们删少了一些东西，所以要补回来。我们裂出右树的最左边的节点，该节点显然包含第 `y` 个树。去除改节点并用新节点替换即可。

```cpp
void del(int x)
{
    int L,R=0,M;
    split_s(root,x,L,R);//区间的r比y小或相等的时候扔进左子树L
    int sy=x-t[L].cnt;
    if(sy==0)
    {
        root=R;
    }else{
        split_k(R,1,M,R);//R树中最左侧的节点会存储在M中
        root=merge(new_node(t[M].l+sy,t[M].r),R);
    }
}
```

## 操作三

查询元素类似删除。但是要把树复原。

```cpp
void get(int x)
{
    int L,R,M;
    split_s(root,x,L,R);
    int sy=x-t[L].cnt;
    if(sy==0)
    {
        split_k(L,t[L].siz-1,L,M);
        cout << t[M].r << endl;
        root=merge(merge(L,M),R);
    }else{
        split_k(R,1,M,R);
        cout << t[M].l+sy-1 << endl;
        root=merge(L,merge(M,R));
    }
}
```

## 操作四

在节点上额外维护最大值即可。

```cpp
cout << t[root].max << endl;
```

完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("IAKIOI")
#define inf (int)1e18
using namespace std;
struct Treap{
    int ls,rs;
    int l,r;
    int cnt;//所管辖区间的大小
    int siz;//所管辖区间的节点数量
    int key;
    int max;//维护区间最大值
}t[200010];
int tot,root;
mt19937 rnd(time(0));
int new_node(int l,int r)
{
    tot++;
    t[tot].ls=t[tot].rs=0;
    t[tot].l=l;
    t[tot].r=r;
    t[tot].key=rnd();
    t[tot].siz=1;
    t[tot].cnt=r-l+1;
    t[tot].max=r;
    return tot;
}
void pu(int x)
{
    t[x].siz=t[t[x].ls].siz+t[t[x].rs].siz+1;
    t[x].cnt=t[t[x].ls].cnt+t[t[x].rs].cnt+t[x].r-t[x].l+1;
    t[x].max=max(max(t[t[x].ls].max,t[t[x].rs].max),t[x].r);
}
void split_k(int x,int val,int &l,int &r)
{
    if(!x)
    {
        l=r=0;
        return;
    }
    if(t[t[x].ls].siz+1<=val)
    {
        l=x;
        split_k(t[x].rs,val-t[t[x].ls].siz-1,t[x].rs,r);
        pu(x);
    }else{
        r=x;
        split_k(t[x].ls,val,l,t[x].ls);
        pu(x);
    }
}
void split_s(int x,int val,int &l,int &r)
{
    if(!x)
    {
        l=r=0;
        return;
    }
    if(t[t[x].ls].cnt+t[x].r-t[x].l+1<=val)
    {
        l=x;
        split_s(t[x].rs,val-(t[t[x].ls].cnt+t[x].r-t[x].l+1),t[x].rs,r);
        pu(x);
    }else{
        r=x;
        split_s(t[x].ls,val,l,t[x].ls);
        pu(x);
    }
}
int merge(int l,int r)
{
    if(!l||!r)
    {
        return l+r;
    }
    if(t[l].key<t[r].key)
    {
        t[l].rs=merge(t[l].rs,r);
        pu(l);
        return l;
    }else{
        t[r].ls=merge(l,t[r].ls);
        pu(r);
        return r;
    }
}
void ins(int l,int r)
{
    root=merge(root,new_node(l,r));
}
void del(int x)
{
    int L,R=0,M;
    split_s(root,x,L,R);
    int sy=x-t[L].cnt;
    if(sy==0)
    {
        root=R;
    }else{
        split_k(R,1,M,R);
        root=merge(new_node(t[M].l+sy,t[M].r),R);
    }
}
void get(int x)
{
    int L,R,M;
    split_s(root,x,L,R);
    int sy=x-t[L].cnt;
    if(sy==0)
    {
        split_k(L,t[L].siz-1,L,M);
        cout << t[M].r << endl;
        root=merge(merge(L,M),R);
    }else{
        split_k(R,1,M,R);
        cout << t[M].l+sy-1 << endl;
        root=merge(L,merge(M,R));
    }
}
signed main()
{
    int c,q;
    cin >> c >> q;
    while(q--)
    {
        int op,x;
        cin >> op;
        if(op==1)
        {
            cin >> x;
            ins(1,x);
        }else if(op==2)
        {
            cin >> x;
            del(x);
        }else if(op==3)
        {
            cin >> x;
            get(x);
        }else{
            cout << t[root].max << endl;
        }
    }
	return 0;
}
```

---

## 作者：myzzym (赞：5)

对于操作一，我们可以弄一个 $a$ 数组记录输入的块（为了方便表达，一次插入的数表示为块），只有这样记录才能不爆炸好吧。

对于操作二，我们如何在块里面删除数呢？我们就用一个变量 $t$ 记录一共弹出了多少个元素，然后弄个 $b$ 数组记录 $a$ 数组的前缀和，当 $t\ge b_{i}$ 时，说明 $a_{i}$ 已经被删除掉了，因为是先弹前面再弹后面，所以我们可以弄个变量 $m$ 来记录已经弹到哪里了，这样就不会重复弹出。

对于操作三，我们可以二分求出第 $z$ 个元素，$b_{i}-t$ 就是第 $i$ 个块的最后一个数是队列中的第几个元素。

对于操作四，我们先找一个特性：只要一个块没有彻底弹出，那么块里最大的数就没有弹出。所以我们可以用单调队列来维护。

时间复杂度是 $O(q\log q)$。

代码如下（代码的变量和上文说的不一定一样）：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=1e18;
ll p,op,x,a[200005],n=1,m,b[200005],sum;
deque<ll>q;
signed main(){
	scanf("%lld%lld",&p,&p);
	while(p--){
		scanf("%lld",&op);
		if(op==1){
			scanf("%lld",&x);
			a[++m]=x,b[m]=b[m-1]+x,b[m+1]=inf;
			while(!q.empty()&&a[q.back()]<x)
				q.pop_back();
			q.push_back(m);
		}
		if(op==2){
			scanf("%lld",&x);
			sum+=x;
			while(sum>=b[n])
				n++;
			while(!q.empty()&&q.front()<n)
				q.pop_front(); 
		}
		if(op==3){
			scanf("%lld",&x);
			int l=n-1,r=m;
			while(l+1<r){
				int mid=l+r>>1;
				if(b[mid]-sum>=x)
					r=mid;
				else
					l=mid;
			}
			printf("%lld\n",x-b[r-1]+sum);
		}
		if(op==4)
			printf("%lld\n",a[q.front()]);
	}
	
	return 0;
}
```


---

## 作者：Crsuh2er0 (赞：3)

平板电视大法好！

## Solution

首先考虑没有 2 操作的情况。

不难发现，我们可以对插入的所有 $x$ 求**前缀和**，然后通过对前缀和进行**二分**得到 3 操作的结果。由于每次只在末尾插入，因此每次插入计算前缀和为 $O(1)$。

考虑实现 2 操作，发现弹出队首 $y$ 个元素等同于将前缀和**整体减去 $y$**。因此，我们可以用**单指针**的加法来代替这个操作，将单指针整体加上 $y$，其他操作时考虑单指针的影响，时间复杂度 $O(1)$。

最终考虑实现 4 操作，发现我们需要一个**支持删除元素**的优先队列。STL 中的 priority_queue 不支持删除，因此我们考虑使用 pb_ds 库中的优先队列来实现此操作。

（若不了解 pb_ds，请查看 [OI-Wiki 上的 pb_ds 页面](https://oi-wiki.org/lang/pb-ds/)。）

具体实现则为：在操作 1 时记录插入元素的迭代器，每次插入时间复杂度 $O(1)$。操作 2 时从堆中删除元素，每次删除时间复杂度均摊 $Θ(\log q)$。

最终时间复杂度 $O(q\log q)$。

代码：
```cpp
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define dbg(x) cerr << #x" = " << (x) << endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
typedef long long LL;
typedef pair<int,int> pii;
#define MAXN 200020
int c,q,li = 1,ri = 1;
LL base,s[MAXN];
__gnu_pbds::priority_queue<int>::point_iterator id[MAXN];
__gnu_pbds::priority_queue<int, less<int>, pairing_heap_tag> pq;

int main(){
    #ifndef ONLINE_JUDGE
    freopen("D.in","r",stdin);
    #else
    cin.tie(0) -> ios::sync_with_stdio(0);
    #endif
    cin>>c>>q;
    for(int i = 1,l,r,mid,ans,opt,x;i <= q;i++){
        //dbg(i);
        cin>>opt;
        if(opt != 4) cin>>x;
        switch (opt){
        case 1:
            s[ri] = s[ri - 1] + x;
            id[ri] = pq.push(x);
            ri++;
            break;
        case 2:
            base += x;
            for(;s[li] <= base && li < ri;li++){
                pq.erase(id[li]);
            }
            break;
        case 3:
            l = li,r = ri,mid,ans = r;
            while(l <= r){
                mid = (l + r) / 2;
                if(s[mid] >= base + x) ans = mid,r = mid - 1;
                else l = mid + 1;
            }
            cout<<x + base - s[ans - 1]<<'\n';
            break;
        case 4:
            cout<<pq.top()<<'\n';
            break;
        }
    }
    return 0;
}
```

另附：__gnu_pbds::priority_queue(pairing_heap_tag) 与 multiset、map 用时对比

[__gnu_pbds::priority_queue(pairing_heap_tag)  442ms](https://www.luogu.com.cn/record/123043797)

[map 598ms](https://www.luogu.com.cn/record/123043774)

[multiset 669ms](https://www.luogu.com.cn/record/123043776)

---

## 作者：w9095 (赞：2)

[P9588 队列](https://www.luogu.com.cn/problem/P9588)

考虑转化问题，将原问题转化为一个长度为 $q$ 的序列。序列中 $x$ 表示一段 $1\sim x$ 的区间。

#### 操作 $1$

每次增加时，输入 $x$，在数组末尾添加一个元素 $x$，并记录时间 $t$ 和前缀和 $s$。时间表示这个元素在第 $t$ 个增加操作增加。由于操作 $4$ 需要求最大值，考虑维护一个单调队列，并执行一次单调队列队尾入队操作，权值为 $x$，时间为 $t$。

#### 操作 $2$

维护一个 $now$ 表示现在已经删除了多少元素，维护一个 $l$ 表示删除之后序列剩余的元素所处的区间的时间。输入 $x$，令 $now$ 增加 $x$，并逐步向后比较 $now$ 与前缀和 $s$ 的值。若大于，说明这一段已经被删除，右移 $l$。

#### 操作 $3$

考虑在原序列上二分。由于有删除，所以查询当前的 $x$ 元素实际上就是查询历史第 $x+now$ 个元素。二分，找到第一个大于 $x+now$ 的前缀和 $s$，则这个值必然落在这个区间中。利用 $s$ 与 $x+now$ 的差值求出所查询的元素离段尾的距离，然后由段尾元素推回来即可。

#### 操作 $4$

考虑单调队列。所有时间小于 $l$ 的元素都需要出队，因为它们已经被删除。然后取队首，就是最大值。

时间复杂度 $O(n\log n)$，瓶颈是操作 $3$。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct val
{
	long long v,t;
}que[300000];
long long c,q,op,x,t,l=1,now,a[300000],s[300000],ql=1,qr=0;
void add()
{
	scanf("%lld",&x);
	a[++t]=x,s[t]=s[t-1]+x;
	while(x>=que[qr].v&&ql<=qr)qr--;
	que[++qr].v=x,que[qr].t=t;
}

void del()
{
	scanf("%lld",&x);
	now+=x;
	while(now>=s[l]&&l<=t)l++;
}

void getnum()
{
	scanf("%lld",&x);
	x+=now;
	long long bl=l,br=t;
	while(bl<br)
	   {
	   	long long mid=(bl+br)/2;
	   	if(x<=s[mid])br=mid;
	   	else bl=mid+1;
	   }
	printf("%lld\n",a[br]-s[br]+x);
}

void getmax()
{
	while(que[ql].t<l&&ql<=qr)ql++;
	printf("%lld\n",que[ql].v);
}

int main()
{
	scanf("%lld%lld",&c,&q);
	for(int i=1;i<=q;i++)
	    {
	    	scanf("%lld",&op);
	    	if(op==1)add();
	    	else if(op==2)del();
	    	else if(op==3)getnum();
	    	else if(op==4)getmax();
	    }
	return 0;
}
```


---

## 作者：流光萤影 (赞：1)

## 前言：

**本题解使用语言：C++14 (GCC 9) O2。**

## 正文：

**思路**：

官方题解是堆加二分，这里提供一个**单调队列**、**前缀和**加**二分**的思路。

用双端队列 $y$ 维护单调队列，即维护队列中的最大值；用数组 $h$ 记录前缀和，即记录当前队列中的元素数量；用变量 $now$ 维护当前队首下标。

对于 $op = 1$，需要维护一次单调队列、记录新的前缀和。

对于 $op = 2$，二分查找并对前缀和进行维护。

对于 $op = 3$，二分查找并输出。

对于 $op = 4$，输出 $y$ 的首项。

------------

**AC 代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> q[200005];
deque<pair<int,int>> y;
int t,op,cnt,now = 1,c;
long long h[200005],x;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> c;
    for(cin >> t;t;--t)
    {
        cin >> op;
        if(op == 1)
        {
            cin >> x;
            q[++cnt] = make_pair(0,x);
            while(y.size() && y.back().second <= x) y.pop_back();
            y.emplace_back(make_pair(cnt,x)),h[cnt] = h[cnt-1]+x;
        }
        else if(op == 2)
        {
            cin >> x,x += h[now-1];
            now = upper_bound(h+now,h+cnt+1,x)-h;
            x -= h[now-1],h[now-1] += x;
            q[now].second -= x,q[now].first += x;
        }
        else if(op == 3)
        {
            cin >> x,x += h[now-1];
            c = lower_bound(h+now,h+cnt+1,x)-h;
            x -= h[c-1];
            cout << x+q[c].first << "\n";
        }
        else
        {
            while(y.front().first < now) y.pop_front();
            cout << y.front().second << "\n";
        }
    }
    return 0;
}
```

---

## 作者：zct_sky (赞：1)

### Solution
-----
~~题目都提示我们要用队列了。~~

准确来说是单调队列。

由于每次 $1$ 操作插入一个 $[1,x]$ 的区间，$2$ 操作又会弹出一部分区间，所以可以使用单调队列。

用单调队列维护 $x$ 中的最大值，所以 $4$ 操作就解决了。

然后考虑如何判断某一区间是否被**完全弹出**，以此来解决单调队列的“滑动窗口”问题。

考虑维护一个前缀和数组 $sumx$，来记录 $1$ 操作的 $x$ 前缀和。 

再使用一个变量来记录 $2$ 操作的 $y$ 总和，记为 $sy$。

显然，我们只需找出 $sumx$ 数组中第一个**大于** $sy$ 的位置，此位置之前的区间都被**完全弹出**，就可以更新单调队列了。

那么 $1,2$ 操作也就解决了。

操作 $3$ 的查询第 $z$ 个位置，可以先找到 $sumx$ 数组中第一个**大于等于** $sy+z$ 的位置 $k$，答案即为 $sy+z-sumx_{k-1}$。

至于如何查询，可以使用 STL 自带的 `lower_bound` 和 `upper_bound` 函数。

最终复杂度为 $\mathcal{O}(Q \log k)$ （$k$ 为 $sumx$ 大小，即 $1$ 询问次数）。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;

}
const int Q=2e5+7;
int c,q;
ll s[Q],sy,tot;
struct que{
	ll tim,val;
}qwq[Q];
ll l=1,r;
int main(){
	c=read();q=read();
	for(int i=1;i<=q;i++){
		int op=read();
		if(op==1){
			int x=read();
			++tot;
			s[tot]=s[tot-1]+x;
			while(l<=r&&qwq[r].val<=x)r--;
			qwq[++r].val=x;
			qwq[r].tim=tot;
		}else if(op==2){
			int y=read();
			sy+=y;
			ll k=upper_bound(s+1,s+1+tot,sy)-s;
			while(l<=r&&qwq[l].tim<k)l++;
		}else if(op==3){
			int z=read();
			ll k=lower_bound(s+1,s+1+tot,z+sy)-s;
			printf("%lld\n",z+sy-s[k-1]);
		}else{
			printf("%lld\n",qwq[l].val);
		}
	}
	return 0;
}
```

---

## 作者：liaoz123 (赞：1)

提供一个线段树解法。

我们维护一个队列和线段树，队列内维护每次操作 1 加入的数。线段树维护区间最值和区间和。那么我们设置一个计数器 $cnt$，表示进行过几次操作 1，再维护一个游标 $s$，记录目前队列中第一个序列中的第一个数，初始为 $1$，操作 4 直接查全局最值，操作 3 可以在线段树内递归查询第 $x$ 个数，有点类似区间第 $k$ 小的那类操作。

```cpp
#include<bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
#define mid (l+r>>1)
#define int long long
using namespace std;
const int N=2e5+5;
typedef long long ll;
int c,s,qq,ma,t[N<<2],nn,cnt,n;
ll ss[N<<2];
void change(int k,int l,int r,int x,int val){
	if(l>x||r<x)return;
	if(l==r){
		t[k]=val;
		ss[k]=(ll)val;
		return;
	}
	change(ls,l,mid,x,val);
	change(rs,mid+1,r,x,val);
	t[k]=max(t[ls],t[rs]);
	ss[k]=ss[ls]+ss[rs];
}
int query(int k,int l,int r,ll sum){
	if(l==r)return sum;
	ll dis=ss[k<<1];
	if(dis>=sum)return query(ls,l,mid,sum);
	else return query(rs,mid+1,r,sum-dis);
}
queue<ll> q;
signed main(){
	scanf("%lld%lld",&c,&qq);
	s=1;n=qq;
	while(qq--){
		int op,x;scanf("%lld",&op);
		if(op==4){
			printf("%lld\n",t[1]);
			continue;
		}
		scanf("%lld",&x);
		if(op==1){
			q.push(x);
			cnt++;
			change(1,1,n,cnt,x);
		//cout<<op<<" "<<x<<endl;
		}
		if(op==2){
			while(!q.empty()&&x){
				int u=q.front();
				if(x+s-1<u){
					s=x+s;
					break;
				}
				else{
					q.pop();
					x-=u-s+1;
					s=1;nn++;
					change(1,1,n,nn,0);
				}
			}
		}
		if(op==3){
			int u=q.front();
			if(u-s+1>=x)printf("%lld\n",x+s-1);
			else printf("%lld\n",query(1,1,n,x+s-1));
		}
	}
	return 0;
}
```


---

## 作者：rainygame (赞：1)

比较简单的一道题，有一种不配放 pjT4 的感觉。

首先，我们肯定不能直接建一个队列来维护（$x \le 10^9$），所以我们考虑只建一个 `deque<pair<int, int>>` （命名为 $\alpha$）来代替，一个 `pair<int, int>` 表示一个 $1\sim x$ 的“块”。其中第一个 `int` 表示插入的 $x$ 是多少，第二个 `int` 表示还剩下多少个（毕竟不太可能每次都恰好的删完一个 $1 \sim x$ 的“块”）。

那么删除就比较简单了，从前往后遍历每个“块”，然后直接删。对于删不完的“块”，就把它的 `second` 减去一部分即可。

对于操作 $3$，考虑暴力查询。从前往后枚举 $\alpha$ 所有的“块”查询即可，注意需要特判一下在第一个“块”的情况。

对于操作 $4$，我们可以维护一个 `multiset`，每次插入时就把 $x$ 给加上，删除时如果可以把这个块删完，就把 $x$ 给删去。因为 $x$ 始终是最后删除的，所以这种方法是正确的。注意删除的时候只删一个，所以需要用 `st.erase(st.find(x))` 的方法进行删除。

75pts 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int c, q, opt, x, now, maxn;
deque<pair<int, int>> que;
multiset<int, greater<int>> st;

int uread(){
	int x(0);
	char ch;
	while ((ch = getchar()) < 48);
	do{
		x = (x << 1) + (x << 3) + (ch ^ 48);
	}while ((ch = getchar()) > 47);
	return x;
}

signed main(){
    c = uread();
    q = uread();
    while (q--){
    	opt = uread();
    	if (opt ^ 4) x = uread();
    	if (opt == 1){
    		que.push_back(make_pair(x, x));
    		st.insert(x);
		}else if (opt == 2){
			while (true){
				if (que.front().second <= x){
					x -= que.front().second;
					st.erase(st.find(que.front().first));
					que.pop_front();
				}else{
					que.front().second -= x;
					break;
				}
			}
		}else if (opt == 3){
			if (que.front().second >= x){
				printf("%d\n", x+que.front().first-que.front().second);
				continue;
			}
			for (auto i: que){
				if (i.second < x) x -= i.second;
				else{
					printf("%d\n", x);
					break;
				}
			}
		}else printf("%d\n", *st.begin());
	}

    return 0;
}
```

我们分析一下前面的时间复杂度：

- 操作 $1$ 复杂度瓶颈为插入集合，复杂度为 $O(\log q)$。
- 操作 $2$ 复杂度瓶颈为删除，但是实际上因为删除完之后便不会再删除那个“块”，所以可以把它直接算到操作 $1$ 的复杂度上。
- 操作 $3$ 复杂度瓶颈为当前的队列大小，因为查询之后还可以再次查询，所以复杂度最坏为 $O(q)$。
- 操作 $4$ 复杂度为 $O(1)$。


我们发现，是操作 $3$ 让我们无法通过，所以考虑优化操作 $3$。

我们想到二分，如果没有删除操作，那么我们可以记录每个块加入进来之后又多少个数，很容易发现这个是单调递增的，因此可以直接用 `lower_bound` 找到那个“块”，注意还需要特判在第一个“块”的情况。

但是现在有了删除，怎么办呢？

我们考虑再建立一个 `deque`，只不过这个把 $\alpha$ 的 `second` 的意义改成了这个“块”之前（包括这个“块”）插入过的数的数量（删除了的也需要算上）。然后再统计一个 $k$ 表示一共删除过多少个数。这样我们就可以二分了。

我们可以假设它前面删除的东西又回来了。我们可以用 $z+k$ 来二分，这样就可以快速的定位到那个块了，然后再结合 `first` 可以直接算出答案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int c, q, opt, x;
deque<pair<int, int>> que;
multiset<int, greater<int>> st;
long long as, ds;

struct Node{
	int first;
	long long val;
	bool operator<(long long b)const{
		return val < b;
	}
};
deque<Node> dq;

signed main(){
//	freopen("queue2.in", "r", stdin);
//	freopen("queue2.out", "w", stdout);
	
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	
    cin >> c >> q;
    while (q--){
    	cin >> opt;
    	if (opt ^ 4) cin >> x;
    	if (opt == 1){
    		que.push_back(make_pair(x, x));
    		st.insert(x);
    		as += x;
    		dq.push_back({x, as});
		}else if (opt == 2){
			ds += x;
			while (true){
				if (que.front().second <= x){
					x -= que.front().second;
					st.erase(st.find(que.front().first));
					que.pop_front();
					dq.pop_front();
				}else{
					que.front().second -= x;
					break;
				}
			}
		}else if (opt == 3){
			if (que.front().second >= x){
				cout << x+que.front().first-que.front().second << '\n';
				continue;
			}
			auto it(lower_bound(dq.begin(), dq.end(), x+ds));
			cout << it->first-(it->val-(x+ds)) << '\n';
		}else cout << *st.begin() << '\n';
	}

    return 0;
}
```


---

## 作者：Lantrol (赞：1)

退役选手兼验题人来水篇题解。

总体思路就是维护每次添加的 $x$ 在展开后的数组中所在的位置。

对于操作 $1$，新加入一个 $x$，记录位置。

对于操作 $2$，由于删除数字并不方便，我们维护一个指针 $p$，它表示在展开后的数组中，前 $p$ 个数字被删掉了。

对于操作 $3$，直接二分出 $(z+p)$ 是在第几次操作 $1$ 中被添加进数组的，然后做个差分即可。

对于操作 $4$，另外维护一个优先队列，每次操作 $1$ 的时候，也将 $x$ 及其展开后的位置用结构体封装然后压入队列，需要查询当前最大值的时候，取出队头元素，判断该元素所在的位置是否被删除了，如果被删除则把队头删掉，然后再取出队头元素，直到队头元素所在位置合法，此时输出即可。

由于二分和优先队列的存在，操作 $1,3,4$ 的时间复杂度均为 $O(\log q)$，操作 $2$ 的时间复杂度为 $O(1)$。整份代码的时间复杂度为 $O(q\log q)$，可以通过。

记得开 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ioc ios::sync_with_stdio(0)
using namespace std;
const int MAXN=2e5+5;
struct node{
	int val,id;
	friend bool operator<(const node &xx,const node &yy){
		return xx.val<yy.val;
	}
};
priority_queue<node> qq;
int n,sum[MAXN],val[MAXN],lft,rt;
int c,q;
signed main(){
    cin>>c>>q;
    while(q--){
    	int op,x;
    	cin>>op;
    	if(op==1){
    		cin>>x;
    		val[++n]=x;
    		sum[n]=sum[n-1]+val[n];
    		rt=sum[n];
    		qq.push(node{x,sum[n]});
		}
		else if(op==2){
			cin>>x;
			lft+=x;
			assert(sum[n]>=lft);
		}
		else if(op==3){
			cin>>x;
			x+=lft;
			int pw=lower_bound(sum+1,sum+n+1,x)-sum;
			cout<<x-sum[pw-1]<<"\n";
		}
		if(op==4){
				if(qq.empty()){
					cout<<"0\n";continue;
				}			
			while(1){
				node now=qq.top();
				if(now.id<=lft) qq.pop();
				else{
					cout<<now.val<<"\n";break;
				}
			}
		}
	}
}
```


---

## 作者：二叉苹果树 (赞：1)

对于第 3 种操作，通过还原完整队列查询队列中的第 $z$ 个数。

对于第 4 种操作，通过 multiset 维护并查询最大值。

为了进行上述的两种操作，我们需要统计每次插入的 $x$ 的前缀和 $s$，维护包括左右还在队列中的 $x$ 的 multiset，以及记录删除操作到了第 $p$ 个区间的第 $f$ 个数。这些内容将在第 1 种和第 2 种操作中同时完成。

还注意到对于每个插入的区间 $\{1, 2, \dots, x\}$，我们只需要关心 $x$ 的值，因为 $x$ 决定了区间的长度和性质。

对于第 1 种操作，在插入区间的同时，统计前缀和并且将 $x$ 插入 multiset 中。

对于第 2 种操作，我们不能逐个数地来暴力删除，而是考虑每次删除整个区间或部分区间，时间复杂度为 $\mathcal{O} \left(q \log q\right)$，可以接受。在删除 $y$ 个数的同时，我们也需要统计 $\delta = \Sigma y$，以便于在第 3 种操作中，直接忽略删除操作，在完整的队列中查询第 $z + \delta$ 个数。

```cpp
#include <bits/stdc++.h>

unsigned long long d, x;
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    unsigned int c, q, op, p = 1, f = 1;
    std::multiset<int> st;
    std::vector<long long> s{0};
    std::cin >> c >> q;
    while (q--)
    {
        std::cin >> op;
        switch(op)
        {
            case 1:
            {
                std::cin >> x;
                s.push_back(s.back() + x);
                st.insert(x);
                break;
            }
            case 2:
            {
                std::cin >> x;
                d += x;
                while (s[p] - s[p - 1] - (f - 1) <= x)
                {
                    st.erase(st.find(s[p] - s[p - 1]));
                    x -= s[p] - s[p - 1] - (f - 1);
                    p++, f = 1;
                }
                f += x;
                break;
            }
            case 3:
            {
                std::cin >> x;
                x += d;
                int t = std::lower_bound(s.begin(), s.end(), x) - s.begin() - 1;
                std::cout << x - s[t] << '\n';
                break;
            }
            default:
                std::cout << *st.rbegin() << '\n';
        }
    }
    return 0;
}
```




---

## 作者：qzhwlzy (赞：0)

### 题目大意

维护一个队列，支持以下操作：

1. 从队尾插入 $1,2,\ldots,x$；
2. 从队首删除 $x$ 个元素；
3. 查询队列中第 $x$ 个元素；
4. 查询队列中元素的最大值。

### 思路

对于操作 $1$，我们发现要插入的数很多，所以我们不妨插入 $x$ 来代替 $1,2,\ldots,x$，接下来我们考虑其他操作的实现。

对于操作 $2$，我们只要记下删除了多少元素即可，不妨记作 $del$。那么在操作 $3$ 中，我们只需要找到队列中第 $del+x$ 个元素即可。对于这一点，我们可以求队列中元素的前缀和并二分实现。

对于操作 $4$，我们可以用单调队列维护队列中元素的最大值。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#define maxn 200005
#define ll long long
using namespace std;
int id,T,opt,x,cnt,q[maxn],head=0,tail=-1,pos=0; ll del=0,a[maxn],pre[maxn];
int main(){
	scanf("%d%d",&id,&T); while(T--){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d",&x); a[++cnt]=x; pre[cnt]=pre[cnt-1]+a[cnt];
			while(head<=tail&&a[cnt]>=a[q[tail]]) tail--; q[++tail]=cnt;
		}else if(opt==2){
			scanf("%d",&x); del+=x; while(pos<cnt&&pre[pos+1]<=del) pos++;
		}else if(opt==3){
			scanf("%d",&x); ll fnd=del+x; int l=0,r=cnt,mid,ans;
			while(l<=r){mid=(l+r)>>1; if(pre[mid]<fnd) ans=mid,l=mid+1; else r=mid-1;}
			printf("%lld\n",fnd-pre[ans]);
		}else{
			while(head<=tail&&q[head]<=pos) head++; printf("%lld\n",a[q[head]]);
		}
	} return 0;
}
```

---

## 作者：紊莫 (赞：0)

赛时做法。  

## Part 1 题意简述  

题意那么清楚还要什么简述？

## Part 2 思路分析

第一个操作，发现 $x$ 很大，所以不能暴力插入，比较可取的方法是每次插入一段连续的数字。  

第二个操作，直接暴力枚举每一段即可，如果当前段的长度小于 $y$，那么就将 $y$ 减去当前段的长度为止，否则就将当前段的左端点加上 $y$。  

为什么可以暴力？因为删除操作至多只有 $q$ 次，而且肯定远远不到，每个元素被删除之后就不再需要统计了。

第三个操作，这个操作不同于第二个，如果坚持暴力做法就会导致可能出现以下情况：  

1.插入一大堆数据  
2.查询一大堆数据

每次查询都需要遍历一遍前面的一大堆数据，果断 TLE。  

比较好想的做法是二分这个位置，因为越往后，数字越多，满足单调性。  

但是有一个问题，我需要统计每一组元素数量的前缀和，这一点不难做到，插入时更新即可，但是删除时岂不是又要更新所有元素？对此，可以采用一个懒标记，每个点的原始前缀和减去懒标记才是真正的答案。  

第四个操作，注意到一个点，最大值只可能是每一段的右端点产生，我们不妨把这些端点加入一个 multiset 中（STL 相关用法请自行搜索），每次取出最大值即可。  

## Part 3 代码

[赛时 AC 代码（2.13KB）](https://www.luogu.com.cn/paste/215r8z7f)

---

## 作者：One_JuRuo (赞：0)

## 思路

观察发现 $x$，$y$，$z$ 都可以很大，所以如果直接用队列老老实实地操作，肯定过不了。

因为每次加入都是 $1,2,3,\cdots x$ 所以这段是连续的，所以我们考虑一段一段的存入队列，记录每一段的左右端点。

操作 $2$ 的删除，就一段一段地删除，如果删不完一段，就改这一段的左端点。

操作 $3$ 的查询可以记录每段的长度的前缀和（如果用操作 $2$ 的办法的话就会 TLE）。

操作 $4$ 的最大值只可能出现在每段的 $x$，考虑用 multiset 存 $x$，但是不知道为什么我的 multiset 炸了，改成 map 和 set 才对。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{long long l,r;}dl[200005];
long long c,q,op,x,he,ta,len[200005];
set<long long>s;
map<long long ,int>m;
int main()
{
	scanf("%lld%lld",&c,&q);
	while(q--)
	{
		scanf("%lld",&op);
		if(op==1) scanf("%lld",&x),dl[++ta].l=1,dl[ta].r=x,s.insert(x),m[x]++,len[ta]=dl[ta].r+len[ta-1];
		else if(op==2)
		{
			scanf("%lld",&x);
			while(x>=dl[he+1].r-dl[he+1].l+1){x-=dl[he+1].r-dl[he+1].l+1,++he;if(m[dl[he].r]==1) s.erase(dl[he].r);m[dl[he].r]--;}
			if(x) dl[he+1].l+=x;
		}
		else if(op==3)
		{
			scanf("%lld",&x);
			x+=len[he]+dl[he+1].l-1;
			long long l=he,r=ta,mid,ansp;
			while(l<=r)
			{
				mid=l+r>>1;
				if(x>len[mid]) ansp=mid,l=mid+1;
				else r=mid-1;
			}
			printf("%lld\n",x-len[ansp]);
		}
		else
		{
			auto i=s.end();--i;
			printf("%lld\n",*i);
		}
	}
	return 0;
}
```

---

## 作者：Mikran (赞：0)

# 队列 题解

昨天在比赛看见了此题，就口胡了，今天上午就写了此题。

操作一，我们可以用一个三元组 $(l,r,len)$ 存一下。比如 $x=5$，三元组为 $(1,5,5)$。

操作二，我们可以**二分**出一个**它**和**它前面的所有**三元组的 $len$ 之和小于 $y$ 的三元组，删除这些三元组。

操作三，与操作二差不多。

操作四，所有三元组的 $r$ 的最大值，用一个线段树维护。

***

把操作二拿出来单独说说。

现在有一个问题，怎么快速得到 $len$ 的前缀和？

想到线段树，线段树存每个三元组的 $len$，直接询问即可。

那怎么删除呢，其实我们并不用去改变三元组，直接在线段树上把 $len$ 改为 $0$ 就行了。

最后，对于多出来的，单独弄一下即可（这里要修改一下三元组）。

***

$q$ 次操作，最多增加 $q$ 个三元组，还有个二分，所以复杂度是 $O(q\log^2 q)$。

细节比较多，上代码。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<iterator>
#include<vector>
#define Genshin_Impact_starts ios::sync_with_stdio(false)
#define int long long
#define F first
#define S second
#define eps 1e-6
#define RE register
#define IN inline
#define ls k<<1
#define rs k<<1|1
#define For(i,s,t) for(register int i=s;i<=t;i++)
#define rFor(i,s,t) for(register int i=s;i>=t;i--)
#define eFor(i,u) for(register int i=head[u];i;i=nxt[i])
using namespace std;
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
void swap(int &a,int &b){a=a^b,b=a^b,a=a^b;}
const int N=3e5+100,inf=1e9+10;
int c,q,tot;
struct stree{//线段树
	int sum[N*4],ma[N*4],L[N*4],R[N*4],lazy[N*4];
	void pushup(int k){
		sum[k]=sum[ls]+sum[rs];
		ma[k]=max(ma[ls],ma[rs]);
	}
	void pushdown(int k,int l,int r){
		if(lazy[k]==-1)return;
		int mid=l+r>>1;
		sum[ls]=lazy[k]*(mid-l+1);
		sum[rs]=lazy[k]*(r-mid);
		ma[ls]=lazy[k];
		ma[rs]=lazy[k];
		lazy[rs]=lazy[k];
		lazy[ls]=lazy[k];
		lazy[k]=-1;
	}
	void build(int k,int l,int r){
		sum[k]=0,ma[k]=0,L[k]=l,R[k]=r,lazy[k]=-1;
		if(l==r)return;
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(k);
	}
	void update(int k,int x,int y,int v){
		int l=L[k],r=R[k];
		if(x<=l&&r<=y){
			sum[k]=v*(r-l+1);
			ma[k]=v;
			lazy[k]=v;
			return;
		}
		int mid=l+r>>1;
		pushdown(k,l,r);
		if(x<=mid)update(ls,x,y,v);
		if(y>mid)update(rs,x,y,v);
		pushup(k);
	}
	int asksum(int k,int x,int y){
		int l=L[k],r=R[k];
		if(x<=l&&r<=y)return sum[k];
		int mid=l+r>>1,res=0;
		pushdown(k,l,r);
		if(x<=mid)res+=asksum(ls,x,y);
		if(y>mid)res+=asksum(rs,x,y);
		return res;
	}
	int askmax(int k,int x,int y){
		int l=L[k],r=R[k];
		if(x<=l&&r<=y)return ma[k];
		int mid=l+r>>1,res=0;
		pushdown(k,l,r);
		if(x<=mid)res=max(res,askmax(ls,x,y));
		if(y>mid)res=max(res,askmax(rs,x,y));
		return res;
	}
}T1,T2;//T1维护前缀和 T2维护最大值
struct node{
	int l,r,len;
};
vector<node>s;//存三元组
signed main(){
    Genshin_Impact_starts;
    cin.tie(0),cout.tie(0);
	cin>>c>>q;
	T1.build(1,0,q),T2.build(1,0,q);
    //线段树从0开始建是为了防止越界
	For(t,1,q){
		int op,x;
		cin>>op;
		if(op==1){
            cin>>x;
			++tot;
			s.push_back({1,x,x});
			T1.update(1,tot,tot,x);
			T2.update(1,tot,tot,x);
		}
		else if(op==2){
			cin>>x;
			int l=1,r=tot;		
			while(l<r){
				int mid=l+r>>1;
				if(T1.asksum(1,0,mid)>=x)r=mid;
				else l=mid+1;
			}
			int res=T1.asksum(1,0,l);
			if(T1.asksum(1,l-1,l-1)==0)//特判 这个三元组是第一个
				if(res==x){//要全部删除
					T1.update(1,0,l,0);
					T2.update(1,0,l,0);
				}
				else{
					s[l-1].l=s[l-1].l+x;
					s[l-1].len=s[l-1].r-s[l-1].l+1;
					T1.update(1,l,l,s[l-1].len);
				}				
			else
				if(res==x){//要全部删除
					T1.update(1,0,l,0);
					T2.update(1,0,l,0);
				}
				else{
					int re=x-T1.asksum(1,0,l-1);
					T1.update(1,0,l-1,0);//删除前面的
					T2.update(1,0,l-1,0);//删除前面的
                    //单独弄多出来的
					s[l-1].l=s[l-1].l+re;
					s[l-1].len=s[l-1].r-s[l-1].l+1;
					T1.update(1,l,l,s[l-1].len);					
				}
		}
		else if(op==3){//类似操作二
            cin>>x;
			int l=1,r=tot;
			while(l<r){
				int mid=l+r>>1;
				if(T1.asksum(1,0,mid)>=x)r=mid;
				else l=mid+1;
			}
			if(T1.asksum(1,l-1,l-1)==0)//特判 这个三元组是第一个
                cout<<s[l-1].l+x-1<<endl;
			else{
				int res=x-T1.asksum(1,0,l-1);
				cout<<res<<endl;
			}
			
		}
		else cout<<T2.askmax(1,0,q)<<endl;
	}
}

```



---

