# 题目信息

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

# AI分析结果

• 综合分析与结论：
    - 这些题解主要围绕如何高效实现队列的四种操作展开。由于操作涉及大数据量，不能直接暴力模拟。常见思路是将每次插入的数分组处理，通过维护前缀和、使用二分查找、借助特定数据结构（如multiset、优先队列、线段树等）来优化操作。
    - 操作1：通常采用记录每组插入数的相关信息（如长度、位置等）而非实际插入大量数据的方式，时间复杂度多为O(1)或O(log q)。
    - 操作2：部分题解通过维护删除偏移量（如记录删除总数）避免实际删除操作，部分通过二分查找确定删除区间，时间复杂度多为O(1)或O(log q)。
    - 操作3：利用前缀和数组结合二分查找确定查询元素所在组及位置，时间复杂度为O(log q)。
    - 操作4：使用multiset、优先队列或线段树等数据结构维护最大值，时间复杂度为O(1)或O(log q)。
    - 整体时间复杂度多为O(q log q)以满足数据范围要求。

所选的题解：
  - 作者：Crosser (5星)
    - 关键亮点：思路清晰简洁，针对每种操作难点提出有效解决方法。利用变量记录删除数量，用std::multiset维护最大值，结合二分查找实现查询操作，各操作时间复杂度控制在O(log q)或O(1)。
    - 重点代码及核心实现思想：
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
核心实现思想：push函数处理操作1，将数据插入数组并更新前缀和与multiset。操作2通过更新res记录删除数，遍历数组更新multiset。操作3利用二分查找前缀和确定元素位置。操作4直接输出multiset中的最大值。

  - 作者：Coffee_zzz (4星)
    - 关键亮点：分任务逐步分析，从简单模拟到针对不同数据范围和操作特点优化。利用multiset记录每组最大值，通过维护数组记录每组元素信息，各操作时间复杂度均为O(log q)。
    - 重点代码及核心实现思想：以Task 11 - 12的代码片段为例
```cpp
// 记录每一组中原本的元素个数和剩余的元素个数
int num[MAXN], las[MAXN];
multiset<int> s; 

// 操作1
void insert(int x) {
    num[++tot] = x;
    las[tot] = x;
    s.insert(x);
}

// 操作2
void pop(int x) {
    while (x > 0) {
        if (x >= las[head]) {
            x -= las[head];
            s.erase(s.find(num[head]));
            head++;
        } else {
            las[head] -= x;
            x = 0;
        }
    }
}

// 操作4
int mxx() {
    auto it = s.end(); --it;
    return *it;
}
```
核心实现思想：操作1记录每组元素信息并插入multiset。操作2循环处理删除，根据剩余删除数与当前组剩余元素数的关系更新multiset和数组。操作4输出multiset中的最大值。

  - 作者：Milthm (4星)
    - 关键亮点：使用线段树维护最大值，通过队列记录每组插入数的开头和结尾，利用前缀和数组与二分查找实现查询操作，时间复杂度为O(q log q)。
    - 重点代码及核心实现思想：
```cpp
// 以下为单点修改的线段树
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
// 线段树结束

signed main(){
    //...
    while(Q--){
        int op,x;
        op = read();
        if(op == 1) x = read(), l[++t] = 1, r[t] = x, update(1, 1, n, t, t, x), f[t] = f[t - 1] + x;
        else if(op == 2){
            //...
        }
        else if(op == 3){
            x = read();
            int qwq = lower_bound(f + h, f + t + 1, del + x) - f;
            printf("%lld\n", del + x - f[qwq - 1]);
        }
        else{
            printf("%lld\n", query(1, 1, n, h, t));
        }
    }
    //...
}
```
核心实现思想：线段树部分实现单点修改和区间查询最大值功能。主函数中操作1插入数据并更新线段树和前缀和数组。操作3利用二分查找前缀和确定元素位置。操作4通过线段树查询最大值。

最优关键思路或技巧：
  - **分组处理插入数据**：避免直接插入大量数据，通过记录每组插入数的特征（如长度、最大值等）简化操作。
  - **维护前缀和与二分查找**：利用前缀和数组的单调性，通过二分查找高效定位元素位置，优化操作3的时间复杂度。
  - **巧用数据结构**：如使用multiset、优先队列维护最大值，线段树实现区间操作和维护最大值，提高操作效率。

可拓展之处：同类型题常涉及对大量数据的序列操作维护，类似算法套路包括利用数据结构（如平衡树、并查集等）优化操作，通过前缀和、差分等技巧处理区间问题。

推荐题目：
  - [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：基础线段树题目，用于熟悉线段树的区间修改和查询操作。
  - [P1801 黑匣子](https://www.luogu.com.cn/problem/P1801)：结合优先队列等数据结构维护动态数据集合，与本题维护队列操作有相似之处。
  - [P2234 [HNOI2002]营业额统计](https://www.luogu.com.cn/problem/P2234)：可使用平衡树或multiset等数据结构维护数据，与本题利用数据结构优化操作的思路类似。

个人心得：
  - 作者Milthm提到赛时因未考虑操作3的优化而痛失AK，强调了对操作时间复杂度分析和优化的重要性。在解决此类问题时，要全面考虑各操作在不同数据规模下的效率，避免因某一操作的低效率导致整体算法超时。 

---
处理用时：107.28秒