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

• 综合分析与结论：这些题解主要围绕如何高效实现队列的四种操作展开。由于操作中涉及较大数值，不能直接模拟队列。多数题解采用分块思想，将每次插入的数分为一组，通过维护前缀和、使用二分查找来优化查询操作；对于最大值查询，常借助multiset、优先队列或单调队列等数据结构。解决难点的关键在于平衡插入、删除和查询操作的时间复杂度。
- Crosser的题解（5星）
  - 关键亮点：思路清晰，利用一个变量记录删除元素个数，通过multiset维护最大值，结合二分查找实现高效查询，各操作时间复杂度为O(log q)或O(1)，代码简洁明了。
  - 重点代码核心思想：`push`函数实现元素插入并更新相关数据结构；在`main`函数中，根据不同操作类型，分别进行插入、删除、查询第z个元素和查询最大值的操作。
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
- Coffee_zzz的题解（5星）
  - 关键亮点：按测试点逐步分析优化，对不同操作采用合适的数据结构和算法。操作一通过分组建multiset记录每组最后一个数优化最大值查询；操作二通过维护前缀和和组内剩余元素个数，均摊时间复杂度为O(log q)；操作三利用二分查找，总复杂度O(q log q)。
  - 重点代码核心思想：以操作一为例，`insert`函数记录每组元素信息并插入multiset；操作二`pop`函数根据删除数量更新相关信息；操作三`kth`函数通过二分查找确定元素位置。
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
- Milthm的题解（4星）
  - 关键亮点：使用队列记录上升数列的开头和结尾，通过前缀和数组和二分查找优化操作三的查询；利用线段树维护最大值，实现操作四的高效查询，整体时间复杂度O(q log q)。
  - 重点代码核心思想：以操作一为例，插入新的数列区间并更新前缀和与线段树；操作二通过遍历队列更新删除信息；操作三利用二分查找结合前缀和确定元素位置；操作四通过线段树查询最大值。
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
• 最优关键思路或技巧：
  - **分块与前缀和**：将每次插入的数看作一块，维护块的信息及前缀和，能快速定位元素所在块，结合二分查找，优化查询第z个元素的操作。
  - **巧用数据结构**：如使用multiset维护最大值，利用其自动排序和快速查找功能；线段树可高效实现单点修改和区间查询最大值等操作。
  - **延迟删除**：不实际删除元素，而是通过记录删除数量，在查询时进行偏移计算，减少删除操作的时间复杂度。
• 可拓展之处：同类型题常涉及对大量数据的插入、删除和查询操作，类似算法套路包括利用数据结构优化、分块思想、延迟操作等。例如在处理动态区间问题时，可借鉴线段树或树状数组的思路；对于滑动窗口问题，可参考单调队列的应用。
• 推荐题目：
  - [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：基础线段树题目，练习线段树的单点修改和区间查询操作。
  - [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：通过单调队列解决滑动窗口内的最值问题，加深对单调队列的理解。
  - [P2672 推销员](https://www.luogu.com.cn/problem/P2672)：结合优先队列和贪心思想，锻炼综合运用数据结构解决问题的能力。
• 个人心得摘录：
  - Milthm提到赛时因未考虑操作三暴力查找超时，痛失AK，提醒要全面分析各操作的时间复杂度，避免简单暴力解法在大数据下超时。 

---
处理用时：104.40秒