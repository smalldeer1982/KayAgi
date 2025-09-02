# [BalticOI 2015] Editor

## 题目描述

Byteasar 是一名程序员，他正在开发一个革命性的文本编辑器。在这个编辑器中，有两种类型的操作：一种是允许在编辑器中编辑文本的操作，另一种是允许撤销先前执行的操作的操作。这个编辑器的一个创新功能是多级撤销操作。其工作原理如下。

我们说文本编辑操作是一个 0 级操作。一个 i 级的撤销操作（对于 $i = 1, 2, \ldots$）可以撤销最后一个未被撤销的、级别不超过 $i-1$ 的操作。例如，一个 1 级的撤销操作只能撤销编辑操作，而一个 2 级的撤销操作可以撤销编辑操作以及 1 级的撤销操作（但不能撤销更高级别的撤销操作）。

更正式地说，已经执行的每个操作可以处于两种状态：活动或已撤销。设 $X$ 是其中一个操作。刚执行完操作 $X$ 后，它处于活动状态。如果 $X$ 是一个 i 级的撤销操作，我们找到最近的、处于活动状态的、级别不超过 $i-1$ 的操作（记为 $X_1$），并将操作 $X_1$ 的状态更改为已撤销。如果 $X_1$ 也是一个撤销操作，我们必须将 $X_1$ 撤销的操作（记为 $X_2$）的状态更改为活动。我们以相同的方式继续：每当一个撤销操作 $X_j$ 的状态改变时，我们必须也改变 $X_{j+1}$ 的状态（当然，这可能导致进一步操作的状态改变）。

当达到一个编辑操作时，整个状态修改链结束。

为简单起见，编辑器中的当前文本内容将由一个称为编辑器状态的单一整数 $s$ 指定（初始为 $0$）。每个编辑操作指定它产生的编辑器状态。

编辑器状态取决于处于活动状态的最后一个编辑操作。帮助 Byteasar 编写一个程序来跟踪编辑器状态。

让我们看看这个功能的实际应用：下表显示了 Byteasar 执行的一些操作以及每次执行后的编辑器状态。符号 $E_s$ 表示将编辑器状态更改为 $s$ 的编辑操作，而符号 $U_i$ 表示 i 级的撤销操作。

| Operation |  | $\mathrm{E}_1$ | $\mathrm{E}_2$ | $\mathrm{E}_5$ | $\mathrm{U}_1$ | $\mathrm{U}_1$ | $\mathrm{U}_3$ | $\mathrm{E}_4$ | $\mathrm{U}_2$ | $\mathrm{U}_1$ | $\mathrm{U}_1$ | $\mathrm{E}_1$ |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Editor state | 0 | 1 | 2 | 5 | 2 | 1 | 2 | 4 | 2 | 1 | 0 | 1 |

首先，Byteasar 执行了三个编辑操作。编辑器状态从 $0$ 变为 $1$，然后变为 $2$，最后变为 $5$。接下来，他执行了两个 1 级的撤销操作，撤销了操作 $E_5$ 和 $E_2$（将它们的状态更改为已撤销）。因此，编辑器状态恢复为 $1$。接下来的 3 级撤销操作撤销了最后一个 $U_1$ 操作（将其状态更改为已撤销），从而恢复了操作 $E_2$（将其状态改回活动）。结果，编辑器状态再次变为 $2$。操作 $U_2$ 撤销了操作 $E_4$，操作 $U_1$ 再次撤销了恢复的操作 $E_2$，最后一个操作 $U_1$ 撤销了操作 $E_1$，最后的操作是 $E_1$。

## 说明/提示

以下子任务和评测无关，仅供参考。

![](https://cdn.luogu.com.cn/upload/image_hosting/zejidndn.png)

（但是我开不了 4 个 Subtask，所以就放在一起测了。）

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
11
1
2
5
-1
-1
-3
4
-2
-1
-1
1```

### 输出

```
1
2
5
2
1
2
4
2
1
0
1```

# 题解

## 作者：DaiRuiChen007 (赞：6)

# P4732 题解

[Problem Link](https://www.luogu.com.cn/problem/P4732)

## **题目大意**

> 给定一个变量 $x$，初始为 $0$，依次进行 $n$ 种操作，每次操作有一个优先级 $p_i$，操作有如下两种：
>
> - 令 $x\gets v$，对于所有的赋值操作，$p_i=0$。
> - 找到此前第一个未被撤销的操作 $j$ 满足 $p_j<p_i$，可以撤销某个撤销操作，此时重新加入被 $j$ 撤销的操作。
>
> 每次操作后输出 $x$。
>
> 数据范围 $n\le 3\times 10^5$。

## **思路分析**

考虑前 $i-1$ 个操作中未被撤销的，注意到对于两个操作 $j,k$，若 $p_j>p_k,j<k$，则此次操作必然不可能直接撤销 $j$，因此所有可能被 $i$ 直接撤销的操作构成一个单调栈。

考虑撤销栈顶 $p_j$，然后考虑前 $i$ 个操作构成的单调栈，显然 $(j,i]$ 中不会有操作被加入这个单调栈中，因为这些操作都满足 $p_j\ge p_i$，因此新的单调栈和 $j-1$ 时刻的单调栈相同，只需要加入 $i$ 操作。

用主席树维护单调栈即可。

时间复杂度 $\mathcal O(n\log n)$。

## **代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+5,INF=1e9;
class SegmentTree {
    private:
        struct Node {
            int ls,rs,min;
            Node() { ls=0,rs=0,min=INF; }
        }    tr[MAXN*20];
        inline void pushup(int p) { tr[p].min=std::min(tr[tr[p].ls].min,tr[tr[p].rs].min); }
        int siz;
    public:
        inline void Insert(int u,int v,int l,int r,int q,int &p) {
            p=++siz;
            if(l==r) return tr[p].min=min(v,tr[q].min),void();
            int mid=(l+r)>>1;
            if(u<=mid) tr[p].rs=tr[q].rs,Insert(u,v,l,mid,tr[q].ls,tr[p].ls);
            else tr[p].ls=tr[q].ls,Insert(u,v,mid+1,r,tr[q].rs,tr[p].rs);
            pushup(p);
        }
        inline int Query(int u,int l,int r,int p) {
            if(l==r) return l;
            int mid=(l+r)>>1;
            if(tr[tr[p].rs].min<u) return Query(u,mid+1,r,tr[p].rs);
            return Query(u,l,mid,tr[p].ls);
        }
}    TR;
int a[MAXN],rt[MAXN],val[MAXN];
signed main() {
    freopen("edit.in","r",stdin);
    freopen("edit.out","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
        if(a[i]>0) val[i]=a[i],TR.Insert(i,0,1,n,rt[i-1],rt[i]);
        else {
            int t=TR.Query(-a[i],1,n,rt[i-1]);
            TR.Insert(i,-a[i],1,n,rt[t-1],rt[i]);
            val[i]=val[t-1];
        }
        printf("%d\n",val[i]);
    }
    return 0;
}
```

---

## 作者：DaydreamWarrior (赞：4)

[还算可爱的阅读体验](https://rainlycoris.github.io/#/post/36)

## 分析

设第 $i$ 次撤销操作要撤销的是 $j$，那么 $i$ 到 $j$ 的操作中不存在优先级比 $j$ 小的，所以 $j$ 到 $i$ 的操作不会在没撤销 $i$ 的情况下被撤销。

考虑可持久化线段树，维护操作的优先级，撤销操作 $i$ 直接继承 $j-1$ 的线段树，查询 $j$ 直接线段树上二分。

## 代码

```cpp
const int N = 300005;
class segtree{
    private:
        struct{int l,r,v;} tr[N*30];
        int root[N],idx;

        void pushup(int u){tr[u].v = min(tr[tr[u].l].v,tr[tr[u].r].v);}
    public:
        segtree(){tr[0].v=1e9;}
        int& operator [](const int &x){return root[x];}
        void modify(int &u,int l,int r,int p,int v){
            tr[++idx] = tr[u];
            u = idx;
            if(l==r){
                tr[u].v = v;
                return;
            }
            int mid = (l+r)>>1;
            if(p<=mid)
                modify(tr[u].l,l,mid,p,v);
            else
                modify(tr[u].r,mid+1,r,p,v);
            pushup(u);
        }

        int query(int u,int l,int r,int p){
            if(l==r)
                return l;
            int mid = (l+r)>>1;
            if(!tr[u].r||tr[tr[u].r].v>=p)
                return query(tr[u].l,l,mid,p);
            return query(tr[u].r,mid+1,r,p);
        }
}tr;
int ans[N];
int n;

int main(){
    n = in;
    for(int k=1;k<=n;k++){
        int x = in;
        if(x>0){
            tr[k] = tr[k-1];
            ans[k] = x;
            tr.modify(tr[k],1,n,k,0);
        }
        else{
            int p = tr.query(tr[k-1],1,n,-x);
            tr[k] = tr[p-1];
            ans[k] = ans[p-1];
            tr.modify(tr[k],1,n,k,-x);
        }
        out(ans[k],'\n');
    }
    return 0;
}
```

---

## 作者：dgdyrkst (赞：1)

## 思路
首先可以发现的是一个撤销操作，无论它优先级多大，它能够撤销的操作都是一定的。

可以画个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ksbjca7u.png)

打钩是处于活跃状态。

丑陋的但是我们可以看到，如果最后一个操作它不被撤销，那么前面的 $-3$ 操作就不可能被撤销，再次推广，能被撤销的应该只有第 $2$ 个和第 $6$ 个这么两个操作。

然后就发现当前局面维护一个单调栈，在上面二分就可以了。

再来处理撤销操作的影响。

发现若 $i$ 操作撤销了 $j$ 操作，相当于在 $j-1$ 时刻后直接加入 $i$ 操作而忽略其他操作。

有点玄乎，我们再拿图来。

最后一个操作撤销了第三个操作，如上分析可知能被撤销的只有第 $2$ 个和第 $6$ 个操作，中间完全可以忽略。

感性理解就是中间的要么是单调栈里没有，要么撤销完了，要么优先级太高不能撤销。

这样就好了，使用可持久化数据结构维护就行了。

但是我太菜不会主席树啊，那要怎么办？

直接建树维护可持久化栈。

这里不过多赘述，可以出门左转 [P6182](https://www.luogu.com.cn/problem/P6182)。

然后在上面简单倍增一下就好了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,a[N],minn[N][30],f[N][30],ans[N],tim[N],now,tot;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (!now)now=++tot,ans[tot]=a[i],tim[i]=now;
		else
		{
			if (a[i]>0)f[++tot][0]=now,now=tot,ans[now]=a[i],tim[i]=now,minn[now][0]=0;
			else
			{
				for (int j=29;j>=0;j--)if (minn[now][j]>=-a[i])now=f[now][j];
				if (minn[now][0]>=-a[i])now=f[now][0];
				f[++tot][0]=tim[now-1],tim[i]=tot,now=tot,ans[now]=ans[f[now][0]],minn[now][0]=-a[i];
			}
		}
		for (int i=1;(1<<i)<=n;i++)f[now][i]=f[f[now][i-1]][i-1],minn[now][i]=min(minn[now][i-1],minn[f[now][i-1]][i-1]);
		printf("%d\n",ans[now]);
	}
	return 0;
}
```


---

