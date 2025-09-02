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

### 综合分析与结论
这些题解主要围绕如何高效实现队列的四种操作展开。由于数据规模较大，直接模拟会超时，所以需采用优化策略。常见思路包括用数组或数据结构记录插入的数段，通过前缀和与二分查找实现操作三，用multiset、优先队列或单调队列维护最大值实现操作四，用变量记录删除数量以优化操作二。

### 所选的题解
- **作者：Crosser (5星)**
    - **关键亮点**：思路清晰，代码简洁。通过一个变量 `d` 记录删除元素个数，用 `std::multiset` 维护最大值，利用二分查找实现查询第 `i` 个元素，所有操作均在 $\mathcal O(\log q)$ 或 $\mathcal O(1)$ 时间内完成。
    - **重点代码核心思想**：`push` 函数实现元素插入并更新相关数据结构。在 `main` 函数中，根据不同操作类型调用相应逻辑。如操作二更新 `res` 并处理 `multiset`；操作三通过二分查找确定元素位置；操作四直接输出 `multiset` 中的最大值。
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
- **作者：Coffee_zzz (4星)**
    - **关键亮点**：分任务讨论解法，对不同数据范围和操作特点提出针对性策略。如针对操作四，利用 `multiset` 维护每组插入数段的最后一个数来快速获取最大值。操作二通过扫描删除元素并更新 `multiset`，操作三通过前缀和二分查找实现。
    - **重点代码核心思想**：在不同任务实现中，操作一插入数段并维护相关数据结构；操作二根据删除数量更新队列状态和 `multiset`；操作三利用前缀和二分查找输出结果；操作四直接输出 `multiset` 最后一个元素。
```cpp
// 以Task 11 - 12的代码实现为例
// 定义数组和multiset
int num[200005], las[200005];
multiset<int> s;
// 操作一实现
void insert(int x) {
    num[++tot] = x;
    las[tot] = x;
    s.insert(x);
}
// 操作二实现
void pop(int x) {
    int head = 1;
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
// 操作四实现
int mxx() {
    auto it = s.end();
    --it;
    return *it;
}
```
- **作者：Milthm (4星)**
    - **关键亮点**：采用线段树维护区间最大值，用数组记录插入的上升数列开头和结尾，通过前缀和与二分查找实现操作三。在操作二删除时，通过记录删除元素数量避免重复遍历前缀和数组。
    - **重点代码核心思想**：线段树部分实现单点修改和区间查询最大值。在 `main` 函数中，操作一插入数列并更新前缀和与线段树；操作二删除元素并更新相关数据；操作三通过二分查找前缀和确定元素位置；操作四通过线段树查询最大值。
```cpp
// 线段树单点修改
void update(int x,int l,int r,int ql,int qr,int k){
	if(ql<=l&&r<=qr){
		a[x]=k;return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)update(x*2,l,mid,ql,qr,k);
	if(qr>mid)update(x*2+1,mid+1,r,ql,qr,k);
	a[x]=max(a[x*2],a[x*2+1]);
}
// 线段树区间查询最大值
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){
		return a[x];
	}
	int mid=(l+r)>>1,sum=0;
	if(ql<=mid)sum=max(sum,query(x*2,l,mid,ql,qr));
	if(qr>mid)sum=max(sum,query(x*2+1,mid+1,r,ql,qr));
	return sum;
}
signed main(){
    cin>>c>>Q;
    while(Q--){
        int op,x;
        op=read();
        if(op==1)x=read(),l[++t]=1,r[t]=x,update(1,1,n,t,t,x),f[t]=f[t-1]+x;
        else if(op==2){
            x=read();int cnt=0;
            for(int i=h;i<=t;++i){
                cnt+=r[i]-l[i]+1;
                if(cnt>=x){
                    cnt-=r[i]-l[i]+1;
                    l[i]+=x-cnt;del+=x-cnt;
                    if(l[i]>r[i])update(1,1,n,i,i,0),++h;
                    break;
                }
                del+=r[i]-l[i]+1;r[i]=l[i]=0;++h;
                update(1,1,n,i,i,0);
            }
        }
        else if(op==3){
            x=read();
            int qwq=lower_bound(f+h,f+t+1,del+x)-f;
            printf("%lld\n",del+x-f[qwq-1]);
        }
        else{
            printf("%lld\n",query(1,1,n,h,t));
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- **数据结构选择**：使用 `std::multiset` 维护最大值，利用其自动排序和快速查找特性。如 `Crosser` 的题解，通过 `multiset` 插入和删除元素实现操作四的高效查询。
- **前缀和与二分**：通过记录插入数段的前缀和，利用二分查找确定操作三中元素的位置。这一方法在多数题解中都有体现，如 `Coffee_zzz`、`Milthm` 等。
- **延迟删除**：用变量记录删除元素个数，而非实际删除队列中的元素，减少操作二的时间复杂度。如 `Crosser` 用变量 `d` 记录删除数量，在操作三查询时进行偏移处理。

### 可拓展之处
同类型题常考察对队列、栈等数据结构的操作维护，结合前缀和、二分查找、优先队列等算法优化。类似算法套路包括：
 - **维护区间信息**：如本题用线段树、`multiset` 等维护区间最大值等信息，可拓展到其他区间统计问题。
 - **延迟操作**：对于删除等操作，通过记录偏移量或标记，延迟实际操作，优化时间复杂度。

### 相似知识点洛谷题目
 - **P1803 凌乱的yyy / 线段覆盖**：涉及区间问题，可通过排序和贪心算法解决，与本题维护队列区间信息有相似之处。
 - **P3834 【模板】可持久化线段树 2（主席树）**：考察线段树和可持久化数据结构，与本题使用线段树维护信息思路相关。
 - **P1168 中位数**：需要维护数据集合的中位数，可使用优先队列等数据结构实现，与本题维护最大值类似。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：53.60秒