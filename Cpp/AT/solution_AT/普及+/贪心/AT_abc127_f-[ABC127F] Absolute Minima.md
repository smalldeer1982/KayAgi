# [ABC127F] Absolute Minima

## 题目描述

有一个函数 $f(x)$ ，初始时 $f(x)=0$

接下来你会对这个函数进行 $Q$ 次以下操作：

- $\texttt{1 a b}$，将 $f(x)$ 替换为 $g(x)=f(x)+|x-a|+b$
- $\texttt{2}$，询问最小的整数 $x$ ，使得  $f(x)$ 取到最小值，以及 $f(x)$ 的最小值

## 说明/提示

$1 \le Q \le 200000,-10^9 \le a,b \le 10^9$ ，保证第一次操作一定是修改操作

## 样例 #1

### 输入

```
4
1 4 2
2
1 1 -8
2```

### 输出

```
4 2
1 -3```

## 样例 #2

### 输入

```
4
1 -1000000000 1000000000
1 -1000000000 1000000000
1 -1000000000 1000000000
2```

### 输出

```
-1000000000 3000000000```

# 题解

## 作者：洛璟 (赞：9)

## Solution:
其实我们在观察题目之后就会发现，绝对值最小为0，那么我们所求的答案，就是求所有绝对值相加最小得几。

如果学过一定的数学知识，就会知道两个数相减所得绝对值映射到几何中就是两个点的距离，我们会发现，对于一条数列上的数来说（题内的所有 $a$ 在经过排序后可以形成一个数列），当 $x$ 取在任意两个数之间时，这两个数对 $x$ 作差，取绝对值的结果一定相同。

画图解释：
![](https://cdn.luogu.com.cn/upload/image_hosting/ie63ocwo.png)

我们可以得出，$|x-a|$+$|x-b|$就是$ab$的长度，也就印证了上面的话。

同样的，我们也可以发现， $x$ 在 $a$ 的左边或者 $b$ 的右边，只会让答案变大，因此，我们可以知道，当有 $cnt$ 个 $a$ 时，若 $cnt$为偶数，则当 $x$ 取为 $a_{cnt/2}$时答案最小。反之则为 $a_{cnt/2+1}$时最小，可以轻易证明。

那么问题来了，如何求这个数呢？动态第 $k$ 位数问题，如果每一次作一次sort，复杂度爆炸。

那么对于处理这个问题，有一个东西可以用来处理，那就是对顶堆。

对于对顶堆，我们首先得学会优先队列。

那么接下来我们来讲对顶堆。

我们观察一个有序的升序数组，可以发现，中位数前面的数均小于中位数，中位数后面的数均大于中位数，那么我们可以想像把一个数组切成两段，前面的数塞入大根堆，后面的数塞入一个小根堆，那么显然，两个堆的其中一个堆顶一定是中位数。

但是我为了方便，因此我选择让大根堆，即中位数之前的数组成的堆，的堆顶为中位数，即让大根堆的长度永远保持比小根堆更大，同时由于中位数前的数字必然比中位数后面更大，因此我也加了一个“swap”。

我们又犯愁了：所有 $f(x)$ 的和怎么算？对于每一个 $a$ 都一个一个计算过去？当然，这会造成大面积TLE。

考虑到减数或者被减数均为上面求出来的中位数，因此我们不难想到，我们可以进行一个区间的操作，计算出大根堆中的区间和，再用区间长度乘上我们前面求出的中位数，减去，或者被减去这个区间的和，那么也就能够算出来当前的 $f(x)$ 了。

其他的细节可以结合代码一同看，也可以自己手动模拟对顶堆，拿几个小的数据模拟可能效果会更好些。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int, vector<int>, greater<int> > q;
priority_queue<int> p;
int n, ans, tmpp, tmp, cnt;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
signed main()
{
    n = read();
    for (register int i = 1;i <= n;++i)
    {
        int x, y, z;
        x = read();
        if (x == 1)
        {
            y = read();
            z = read();
            p.push(y);
            tmpp += y;
            ans += z;
            if (p.size() - 1 > q.size())//如果大根堆的数字数量多于一半以上了，就要把多余的扔进小根堆保证大根堆堆顶为中位数
            {
                int t = p.top();
                p.pop();
                q.push(t);
                tmpp -= t;
                tmp += t;
            }
            if (!q.empty() && p.top() > q.top())//保证大根堆中所有数小于小根堆中的数
            {
                int a = p.top();
                int b = q.top();
                q.pop();
                p.pop();
                q.push(a);
                p.push(b);
                tmpp = tmpp - a + b;
                tmp = tmp + a - b;
            }
        }
        else
        {
            int x = p.top();
            int y = (p.size() * x) - tmpp + (tmp - q.size() * x) + ans;
            printf("%lld %lld\n", x, y);
        }
    }
    return 0;
}
```


---

## 作者：fengenrong (赞：3)

### 题意

现有一个函数 $f(x)$，它最初是一个常数函数 $f(x)=0$。

现在要求按顺序处理 $Q$ 个查询。有两种查询，更新查询和评估查询，如下所示：

+ 更新查询：给出两个整数 $a$，$b$；令 $g(x)=f(x)+|x-a|+b$，并将 $f(x)$ 替换为 $g(x)$。

+ 求值查询: 输出使 $f(x)$ 最小化的 $x$，以及 $f(x)$ 的最小值。如果有多个这样的 $x$ 值，请选择最小值。

可以证明，求值查询中要输出的值始终是整数，因此要求将这些值打印为不带小数点的整数。

### 思路

首先，我们不难发现其实题目就是让我们求 $|x-a_1|+b_1+|x-a_2|+b_2+…+|x-a_n|+b_n$ 的值最小。我们利用数轴可以发现，不管是任何情况，我们只需要满足 $x$ 的值为 $a_1$，$a_2$，$a_3…a_n$ 中的中位数就行了。

我们可以使用对顶堆，用一个大顶堆和一个小顶堆动态维护中位数。我们在插入的时候只需要满足数据个数是偶数，那我们要在大根堆中新插入一个数，否则放入小根堆中。插入完之后，我们再对堆进行维护，实现了 $O(n \log n)$ 的时间复杂度，符合题目。

### 代码
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int, vector<int>, greater<int> > small;//小根堆
priority_queue<int, vector<int>, less<int> > big;//大根堆
int q;
int sum;
int a[2000005], cnt;
int ans = 0;
signed main() {
    cin >> q;
    int op;
    while (q--) {
        scanf("%lld", &op);
        if (op == 1) {//更新查询
            int b;
            scanf("%lld%lld", &a[++cnt], &b);
            sum += b;
            if (cnt % 2 == 1) {
                big.push(a[cnt]);//放入大根堆
            } else {
                small.push(a[cnt]);//放入小根堆
            }
            int Y = big.top();//记录原本的中位数
            while ((small.size()) && (small.top() < big.top())) {//维护堆
                int x = big.top(), y = small.top();//将两个堆顶互换
                big.pop();
                small.pop();
                big.push(y);
                small.push(x);
            }
            if (Y == big.top()) {//中位数没发生改变
                ans += abs(a[cnt] - Y);//直接加上当前的b
            } else if (cnt % 2 == 1) {
                ans += abs(big.top() - Y);//加上两个中位数的差
            } else if (cnt % 2 == 0) {
                ans += abs(a[cnt] - Y);//直接加上当前的b
            }
        } else {//求值查询
            printf("%lld %lld\n", big.top(), ans + sum);
        }
    }
    return 0;
}
```

---

## 作者：chenxia25 (赞：3)

刚看完题还想着用 geogebra 放几个 $a$ 上去看函数长啥样。然后画完才发现脑抽了……这不就是昨天做的那个 APIO2015 那题吗？

发现 $b$ 的影响单独算，任意时刻设 $a$ 的序列为 $A$，那么 $f(i)=\sum |x-A_i|$，那不就是取 $A$ 的中位数吗？两个 `set` 维护一下就好了。

上帝不要惩罚我做水题/kk

---

## 作者：_zexal_ (赞：2)

## 思路
完全不需要堆，考虑离线做法，这样一来，每一次进行删除操作时，答案区间无非只有三种情况，不变，向左，向右。这部分使用判断，显然复杂度为 $O(1)$，然后离线做法删除的时候顺带删除就好。总的复杂度为 $O(n \log n)$，完全可以通过此题。

---

## 作者：cosf (赞：1)

## [ABC127F](https://www.luogu.com.cn/problem/AT_abc127_f)

显然，每时每刻，我们可以把 $f$ 化为以下形式：

$$
f(x) = C + \sum_{i=1}^k|x-a_i|, (a_i \le a_{i + 1}\forall i \lt k)
$$

根据我们小学学过的知识，当 $x$ 取 $a_{\lfloor\frac{k}{2}\rfloor}$ 时是最优的。

稍微证一下，假设当前的 $x$ 左边有 $l$ 个 $a_i$，右边有 $r$ 个$a_i$（$l \lt r$），则你让 $x$ 向右走一点（距离为 $x'$）并且不越过任意一个 $a_i$，则 $f(x)$ 会减少 $(r - l)x'$，显然比之前的要优。反过来也是一样，所以就证完了。

至于怎么计算，维护一下左边的点的和 $\sigma_l$ 和右边点的和 $\sigma_r$，以及左边点的个数 $c_l$ 和右边点的个数 $c_r(c_r \le c_l \le c_r + 1)$，和左边点最大的那个 $m_l$，则 $f(x) = C + \sigma_r - \sigma_l + m_l(c_l - c_r)$。

至于怎么维护两边的点，开两个堆，使它们的大小差在 $1$ 以内即可。

## 代码

```cpp
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

using ll = long long;

priority_queue<ll> sl; // 左边的点
priority_queue<ll, vector<ll>, greater<ll>> sr; // 右边的点
ll ml = 0, mr = 0; // 左边的和，右边的和

ll sb = 0;

int main()
{
    int o = 0;
    int n;
    cin >> n;
    while (n--)
    {
        int op;
        cin >> op;
        if (op == 2)
        {
            cout << sl.top() << ' ' << (mr - ml) + (sl.top() * (int)(sl.size() - sr.size())) + sb << endl;
        }
        else
        {
            ll a, b;
            cin >> a >> b;
            sb += b;
            if (!sr.size() || a <= sr.top())
            {
                sl.push(a);
                ml += a;
                while ((int)sl.size() > sr.size() + 1)
                {
                    ml -= sl.top();
                    mr += sl.top();
                    sr.push(sl.top());
                    sl.pop();
                }
            }
            else
            {
                sr.push(a);
                mr += a;
                while ((int)sl.size() < sr.size())
                {
                    mr -= sr.top();
                    ml += sr.top();
                    sl.push(sr.top());
                    sr.pop();
                }
            }
        }
    }
    return 0;
}

```


---

## 作者：DerrickLo (赞：1)

容易想到 $b$ 是无关紧要的，用一个变量维护一下和就行了。

然后发现这个式子是多个绝对值相加，那么 $x$ 取他们的中位数就是最优的，注意当个数为 $2n$ 时要取第 $n$ 小的数。

接着就会发现添加一个数时很好维护目前的中位数和 $f(x)$ 最小值，删除一个数也很好维护。

然后开个 `multiset` 就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int q,op,a,b,sum,pp;
multiset<int>st;
multiset<int>::iterator mid;
signed main(){
	cin>>q;
	while(q--){
		cin>>op;
		if(op==1){
			cin>>a>>b;
			st.insert(a);
			pp+=b;
			if(st.size()==1){
				mid=st.begin();
				continue;
			}
			if(a>=(*mid)){
				if(st.size()%2==0){
					sum+=a-(*mid);
				}
				else mid++,sum+=a-(*mid);
			}
			else{
				if(st.size()%2==0)sum+=(*mid)-a,mid--;
				else sum+=(*mid)-a;
			}
		}
		else{
			cout<<(*mid)<<" "<<sum+pp<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

## 分析

不难想到题目相当于要求 $\displaystyle\sum_{i=1}^n|x-a_i|+\displaystyle\sum_{i=1}^nb_i$，所以 $b$ 可以撇开来最后再加上，关键是处理绝对值。

用绝对值几何意义感性理解一下 $|x-a|$ 就是数轴上 $x$ 和 $a$ 的距离。那么 $\displaystyle\sum_{i=1}^n|x-a_i|$ 可以理解为数轴上 $x$ 与很多 $a_i$ 的距离之和。那么不难想到 $x$ 应该是类似这样的情况，如图。![image](https://cdn.luogu.com.cn/upload/image_hosting/aauy0r3e.png)

黑点代表 $a_i$ 们，只要 $x$ 在红线段上 $\displaystyle\sum_{i=1}^n|x-a_i|$ 都能取到最小值（若黑点有奇数个，红线段就是一个点，也就是最中间的点）。所以可以把绝对值打开，会发现只要 $x$ 在红线段上，打开绝对值后 $x$ 可以被消元，整个值变成右侧黑点距离和减左侧黑点距离和。综上，只需要动态维护 $a$ 的中位数的位置以及相关的值就可以解决该问题。

经过分析，问题可以变成中位数模板。用两个堆（priority_queue）分别维护左侧与右侧黑点，记录堆内数字和，就能推出输出，并且这几个东西也是很好维护的。

然后就是一些细节问题。我们要保证大根堆的存数数量小于所有数的一半，否则正确性难以保证（我写的是以大根堆顶为中位数，如果两堆数量不平衡，堆顶就不是中位数）。另外还需要保证大根堆的所有数大于小根堆的，这样才是分别存 $a$ 的两部分。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
priority_queue<int,vector<int>,greater<int>/**/> pb;
priority_queue<int> pf;
signed main()
{
	int q,add=0,sumf=0,sumb=0;
	cin>>q;
	while(q--)
	{
		int opt,a,b;
		cin>>opt;
		if(opt==1)
		{
			cin>>a>>b;
			add+=b;
			pf.push(a);
			sumf+=a;
			if(pf.size()>pb.size()+1)
			{
				int t1=pf.top();
				pf.pop();
				pb.push(t1);
				sumf-=t1;
				sumb+=t1;
			}
			if(!pb.empty()&&pf.top()>pb.top())
			{
				int t1=pf.top(),t2=pb.top();
				pf.pop();pb.pop();
				pb.push(t1);pf.push(t2);
				sumf-=t1;
				sumf+=t2;
				sumb+=t1;
				sumb-=t2;
			}
		}
		else
		{
			int ans1=pf.top();
			int ans2=ans1*(pf.size()-pb.size())+sumb-sumf;
			cout<<ans1<<' '<<ans2+add<<endl;
		}
	}
	return 0;
}

---

## 作者：jr_zch (赞：1)

题意：动态求一个函数的最小值


解法：比较敏感的人可以发现，$b$ 相当于一个常数，在过程中累加起来即可，那么剩余部分就是 $|x - a|$ 学过初中数学的都知道，可以用绝对值的几何意义解决，即：使该函数最小的 $x$ 为所有 $a$ 的中位数。对于中位数，可以用对顶堆来解决，但是不好理解。

我使用的方法是 `splay` 平衡树，在 `pushup` 函数维护 `size` 时顺手维护一下该子树的 `sum` 即可。

注意：
* 最后查询 `kth` 时要访问的是第 `(dfn-1)/2+1` 个元素。
* 记得开 `long long`。

`AC` 代码：

```c++
#include <stdio.h>
#define int long long

const int maxn=2e5+7;
int n,cnt,x,root,op,add,dfn,mid,a,b;
int dat[maxn],siz[maxn],f[maxn],s[maxn][2],sum[maxn];

void link(int u,bool d,int v){
    s[u][d]=v,f[v]=u;
    return ;
}

void pushup(int u){
    siz[u]=1,sum[u]=sum[s[u][0]]+sum[s[u][1]]+dat[u];
    if(s[u][0]) siz[u]+=siz[s[u][0]];
    if(s[u][1]) siz[u]+=siz[s[u][1]];
    return ;
}

void rotation(int now){
    int u=f[now],v=f[u];
    bool d=s[u][0]==now;
    link(u,d^1,s[now][d]),link(now,d,u),link(v,s[v][1]==u,now);
    pushup(u),pushup(now);
    return ;
}

void splay(int now,int top){
    while(f[now]!=top){
        int u=f[now],v=f[u];
        if(v!=top){
            if((s[u][0]==now)==(s[v][0]==u)) rotation(u); 
            else rotation(now); 
        }
        rotation(now);
    }
    if(top==0) root=now;
}

int find(int x){
    int now=root,d;
    while(now){
        if(x==dat[now]){
            splay(now,0);
            return now;
        }
        d=x>dat[now];
        if(s[now][d]) now=s[now][d];
        else break;
    }
    return -1;
}

int merge(int l,int r){
    if(!l||!r) return l+r;
    while(s[l][1]) l=s[l][1];
    splay(l,0),link(l,1,r),pushup(l);
    return l;
}

void insert(int x){
    int now=root,d;
    while(now){
        d=x>dat[now];
        if(s[now][d]) now=s[now][d];
        else break;
    }
    dat[++cnt]=x,siz[cnt]=1;
    if(now) link(now,d,cnt),pushup(now);
    splay(cnt,0);
    return ;
}

void delet(int x){
    int now=find(x);
    if(now==-1) return ;
    splay(now,0);
    f[s[now][0]]=f[s[now][1]]=0;
    root=merge(s[now][0],s[now][1]);
    return ;
}

int count(int x){
    int now=root,t=0;
    while(now){
        if(dat[now]<x) t+=siz[s[now][0]]+1,now=s[now][1];
        else now=s[now][0];
    }
    return t;
}

int kth(int x){
    int now=root,t;
    while(now){
        t=siz[s[now][0]]+1;
        if(x==t) break;
        if(x>t) x-=t,now=s[now][1];
        else now=s[now][0];
    }
    if(now) splay(now,0);
    return now;
}

int pre(int x){
	int now=root,p=0;
	while(now){
		if(dat[now]<x) p=now,now=s[now][1];
		else now=s[now][0];
	}
	if(p) splay(p,0);
	return p;
}

int nxt(int x){
	int now=root,p=0;
	while(now){
		if(dat[now]>x) p=now,now=s[now][0];
		else now=s[now][1];
	}
	if(p) splay(p,0);
	return p;
}

signed main(){
    scanf("%lld",&n);
    while(n--){
    	scanf("%lld",&op);
    	if(op==1) scanf("%lld%lld",&a,&b),dfn++,add+=b,insert(a);
    	else mid=kth((dfn-1)/2+1),printf("%lld %lld\n",dat[mid],siz[s[mid][0]]*dat[mid]-sum[s[mid][0]]+sum[s[mid][1]]-siz[s[mid][1]]*dat[mid]+add);
	}
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

# 基本思路
首先，在经过一系列操作之后，$f(x)$ 大概长这样：

$$
f(x)=|x-a_1|+|x-a_2|+...+|x-a_k|+b_1+b_2+...+b_k
$$

显然后面的部分是定值，那么前面最小值是多少？

我们根据绝对值的定义，可以将 $a_i$ 看作是数轴上的点，然后希望距离之和最小。

这个最小的情况，如果有奇数个点，那么最优值是排名在中间的点。

如果有偶数个点，则中间两个点中间这一段任意一点都是最优的。

证明刘汝佳的书《训练指南》上有，网上也有很多资料，不再推导。

知道这一点后，我们发现最优解就是所有 $a_i$ 的中位数。

# 维护方法

我们可以用一个平衡树来维护，关于求值的问题，可以利用 FHQ Treap 的分裂操作。

我们注意到：对于绝对值 $|x-a_i|$，如果需要取相反数，则 $x\leq a_i$，否则反之。

利用分裂分成两个部分，我们可以顺带维护出平衡树每个子树的权值总和，分开之后可以很简单的计算了。


```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
struct node
{
    LL lc,rc,sz,pri,val,sum;
}t[200005];
LL m,op,a,b,cnt,rt,tot;
void pushup(LL rt)
{
    if(rt)
    {
        t[rt].sz=t[t[rt].lc].sz+t[t[rt].rc].sz+1;
        t[rt].sum=t[t[rt].lc].sum+t[t[rt].rc].sum+t[rt].val;
    }
}
void split(LL rt,LL &lrt,LL &rrt,LL x)
{
    if(rt==0)lrt=rrt=0;
    else if(t[rt].val<=x)lrt=rt,split(t[rt].rc,t[rt].rc,rrt,x);
    else rrt=rt,split(t[rt].lc,lrt,t[rt].lc,x);
    pushup(rt);
}
void merge(LL &rt,LL lrt,LL rrt)
{
    if(lrt==0||rrt==0)rt=lrt+rrt;
    else if(t[lrt].pri<t[rrt].pri) rt=lrt,merge(t[rt].rc,t[rt].rc,rrt);
    else rt=rrt,merge(t[rt].lc,lrt,t[rt].lc);
    pushup(rt);
}
void ins(LL &rt,LL x)
{
    LL rt1,rt2;
    t[++tot]={0,0,1,rand(),x,x};
    split(rt,rt1,rt2,x),merge(rt1,rt1,tot),merge(rt,rt1,rt2);
    pushup(rt);
}
LL kth(LL &rt,LL x)
{
    if(t[rt].sz<x)return -1;
    if(x<=t[t[rt].lc].sz)return kth(t[rt].lc,x);
    if(x==t[t[rt].lc].sz+1)return t[rt].val;
    return kth(t[rt].rc,x-t[t[rt].lc].sz-1);
}
LL calc(LL x)
{   
    LL rt1,rt2,ans;
    split(rt,rt1,rt2,x);
    ans=t[rt1].sz*x-t[rt1].sum+t[rt2].sum-t[rt2].sz*x;
    merge(rt,rt1,rt2);
    pushup(rt);
    return ans;
}

int main()
{
    srand(time(0));
    scanf("%lld",&m);
    while(m--)
    {
        scanf("%lld",&op);
        if(op==1)
        {
            scanf("%lld%lld",&a,&b);
            cnt+=b;     
            ins(rt,a);   
        }
        else 
        {
            LL k=kth(rt,(t[rt].sz+1)/2);
            cout<<k<<" "<<cnt+calc(k)<<endl;
        }
    }
}
```



---

## 作者：迟暮天复明 (赞：1)

有一个函数 $f(x)$，两种操作。

1. 将 $f(x)$ 变为 $f(x)+\left|x-a\right|+b$。
2. 求 $f(x)$ 的最小值点。如有多个，取横坐标最小的一个。

-----
通过初中数学知识可以发现，当 $x$ 取到所有 $a$ 的中位数时 $f(x)$ 有最小值。假设已经进行了 $2n-1$ 次操作 $1$，每个 $a$ 从小到大分别为 $a_1,a_2,\ldots,a_{2n-1}$，则 $x=a_n$ 时  $ f(x)=(a_n-a_1)+(a_n-a_2)+\ldots +(a_n-a_{n-1})+(a_{n+1}-a_n)+\ldots+(a_{2n-1}-a_n)+\sum b=\sum_{i=n+1}^{2n+1}a_i-\sum_{i=1}^{n-1}a_i+\sum b $。操作次数为偶数时类似。所以我们要维护以下三个东西：

+ 中位数；

+ 比中位数大的数字总和；

+ 比中位数小的数字总和。

于是考虑用两个堆来维护。开一个大根堆存小于中位数的数，开一个小根堆存大于中位数的数。则为了使中位数有多个时取最小的，应该让大根堆堆顶存储当前的中位数。这样大根堆中的元素个数一定大于等于小根堆中的元素个数。

考虑如何插入。如果当前的数据个数是偶数，那我们要在大根堆中新插入一个数。明显的，我要插入的数一定是小根堆堆顶和当前插入的数的最小值，并将剩下那个数放入小根堆中，这样才能保证满足原有性质。如果数据个数是偶数，类似的，取大根堆堆顶和当前数的较大值放入小根堆，剩下那个放入大根堆。

这样我们就可以 $O(n\log n)$ 维护中位数了。计算两个总和就很简单了，在数据出入堆时顺便对总和进行修改即可。

[Code](https://atcoder.jp/contests/abc127/submissions/31454143)

---

