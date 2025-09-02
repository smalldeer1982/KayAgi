# [NWRRC 2021] Day Streak

## 题目描述

最近，著名的竞赛编程网站 Deltaforces 在用户资料中增加了许多新的可视化信息。特别地，新增了“最大连续天数”——即连续若干天每天至少解决一道题的最大天数。你觉得你资料中的最大连续天数并不能准确反映你的训练努力。因此，你产生了一个想法——如果你可以更改资料中的时区，是否能提升你的最大连续天数？

我们将这个设定形式化如下。假设你总共解决了 $n$ 道题，第 $i$ 道题是在时间 $a_i$ 被解决的。共有 $m$ 个时区，编号从 $0$ 到 $m-1$。默认时区为 $0$。如果你选择将时区更改为 $t$，那么所有题目的时间戳都会增加 $t$：即第 $i$ 道题的时间变为 $a_i + t$，对所有 $i$ 都成立。

在时间 $x$ 解决的问题被认为是在第 $\lfloor \frac{x}{m} \rfloor$ 天解决的。这里 $\lfloor v \rfloor$ 表示不超过 $v$ 的最大整数。

为了展示最大连续天数，Deltaforces 会找到一组 $l$ 和 $r$，使得你在第 $l, l+1, \ldots, r$ 天中每天至少解决了一道题，并且 $r-l+1$ 尽可能大。此时你的最大连续天数就是 $r-l+1$。

请你通过选择一个合适的时区，使你的最大连续天数最大，并输出最大连续天数以及对应的时区。

## 说明/提示

在第一个样例测试中，当你选择时区 $2$ 时，你的题目时间戳变为 $2$、$5$、$10$ 和 $26$。这意味着这些题目分别被认为是在第 $0$、$0$、$1$ 和 $2$ 天解决的，也就是一个 $3$ 天的连续天数。时区 $3$、$4$ 和 $5$ 也能得到相同的答案。

在第二个样例测试中，选择时区 $5$ 后，你的题目时间戳变为 $37$ 和 $40$，对应第 $3$ 天和第 $4$ 天。时区 $6$ 和 $7$ 也可以。

在第三个样例测试中，只有一个时区，你的最大连续天数就是 $5$。

在第四个样例测试中，你在很短的时间内解决了很多题，但最大连续天数也只能是 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
4 10
0 3 8 24
2 10
32 35
10 1
0 1 3 4 5 6 7 10 11 12
10 24
0 1 3 4 5 6 7 10 11 12
8 24
26 71 101 147 181 201 244 268```

### 输出

```
3 2
2 5
5 0
2 12
4 15```

# 题解

## 作者：Phobia (赞：0)

注意到由于 $0\le t<m$, $\lfloor\frac{a_i+t}{m}\rfloor$ 至多变化一次，因此不妨按顺序枚举对应变化的 $t$，此时若开一颗线段树维护有连续做题的天数的最大值，只需对线段树操作 $\mathcal{O}\left(n\right)$ 次。

综上，时空复杂度均为 $\mathcal{O}\left(\sum n\log\frac{\max{a_i}}{m}\right)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

int read()
{
    int res = 0, f = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        f = (ch == '-');
    for (; isdigit(ch); ch = getchar())
        res = (res << 3) + (res << 1) + (ch & 15);
    return f ? -res : res;
}

const int N = 2e5 + 5, S = N * 40;

int n, m, a[N];

struct node
{
    int ans, llen, rlen;
    bool flg;
    node operator+(const node& rhs)
    {
        return (node) {
            max({ ans, rhs.ans, rlen + rhs.llen }),
            llen + (flg) * rhs.llen,
            rhs.rlen + (rhs.flg) * rlen,
            flg && rhs.flg
        };
    }
} T[S];

int ls[S], rs[S], rt, tot;

map<int, int> day;

map<int, vector<int>> zone;

void update(int& u, int l, int r, int x, int v)
{
    if (!u)
        u = ++tot, ls[u] = rs[u] = 0, T[u] = (node) { 0, 0, 0, 0 };
    if (l == r)
    {
        if (day[x] += v)
            T[u] = (node) { 1, 1, 1, 1 };
        else
            T[u] = (node) { 0, 0, 0, 0 };
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid)
        update(ls[u], l, mid, x, v);
    else if (mid < x)
        update(rs[u], mid + 1, r, x, v);
    T[u] = T[ls[u]] + T[rs[u]];
}

int main()
{
    int tt = read();
    while (tt--)
    {
        n = read(), m = read();
    
        rt = tot = 0, day.clear(), zone.clear();

        zone[0] = vector<int>();

        for (int i = 1; i <= n; ++i)
        {
            a[i] = read();
            zone[(a[i] / m + 1) * m - a[i]].push_back(i);
            a[i] /= m;
        }
        for (int i = 1; i <= n; ++i)
            update(rt, 0, 1e9, a[i], 1);
        int ans1 = 0, ans2 = 0;
        for (auto it : zone)
        {
            for (auto jt : it.second)
            {
                update(rt, 0, 1e9, a[jt], -1);
                update(rt, 0, 1e9, a[jt] + 1, 1);
            }
            if (T[rt].ans > ans1)
                ans1 = T[rt].ans, ans2 = it.first;
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}
```

---

## 作者：zhuweiqi (赞：0)

我们先不考虑怎么算最大天数，先考虑从第 $i$ 道题目做起最多做到第几道题目，显然答案具有单调性，可以用双指针解决。至于具体方法，我们可以考虑满足第 $i$ 道题目与第 $i+1$ 道题目在同一天或者相邻两天的时区区间，对此进行分类讨论：（声明：在本篇题解中，时区为原定义时区 $+1$）

- 若 $a_{i+1}-a_i\geq 2m$，时区区间为空集。

- 若 $a_{i+1}-a_i\leq m$，时区区间为全集 $[1,m]$。

- 若 $a_i$ 和 $a_{i+1}$ 原本就在相邻两天，则时区区间为使得这两道题目都不过夜（过夜指一道题目现在推迟到了第二天做），或者这两道题目都过夜。

- 若 $a_i$ 和 $a_{i+1}$ 原本中间隔了一天，则时区区间为使得题目 $i$ 过夜且题目 $i+1$ 不过夜。

将第三条和第四条综合一下，代码如下：

```cpp
s[i].l=(m-a[i]%m)%m+1;s[i].r=m-a[i+1]%m;
```

若 $l\leq r$，时区区间为 $[l,r]$；否则，时区区间为 $[1,r]\cup [l,m]$。

然后我们判断一个区间 $[l,r]$ 的时区区间是否有交集的办法，就是开一个线段树，支持区间加操作，区间求最大值，看最大值是否和区间长度相等。由于 $m$ 很大，我们需要动态开点。此外，由于本题需要求出具体时区，维护线段树的区间最大值的时候还要顺带记录最大值的位置。

注意双指针的坑点（导致作者交了 $30$ 发 WA 的罪魁祸首）：由于一般维护双指针是维护到第一个不合法的位置，而这个位置贡献已经算上去了，所以需要减掉。另外初始化 $ans=\{1,1\}$（二元对）。

至此来到本题最后一步，根据题目区间求天数。也是和第一步类似，分别讨论第一道题目和最后第一道题目过夜不过夜的情况就可以了，区间查询的时候调整到特定时区，特别注意第一道题目过夜且最后一道题目不过夜的情况！

最后是代码（动态开点线段树和分类讨论加起来 3KB 也挺正常了）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+2;
int num,a[N];
struct pro{
	int l,r;
}s[N];
struct node{
	int x,sq,L,R,l,r,add;
}t[N<<5];
void pd(int u){
	if(!t[u].l){
		t[u].l=++num;
		t[num].L=t[u].L;
		t[num].R=t[u].L+t[u].R>>1;
		t[num].sq=t[num].L;
	}
	t[t[u].l].x+=t[u].add;
	t[t[u].l].add+=t[u].add;
	if(!t[u].r){
		t[u].r=++num;
		t[num].L=(t[u].L+t[u].R>>1)+1;
		t[num].R=t[u].R;
		t[num].sq=t[num].L;
	}
	t[t[u].r].x+=t[u].add;
	t[t[u].r].add+=t[u].add;
	t[u].add=0;
	return;
}
void query(int u,int x,int y,int z){
	if(x<=t[u].L && t[u].R<=y){
		t[u].x+=z;
		t[u].add+=z;
		return;
	}
	pd(u);
	int mid=t[u].L+t[u].R>>1;
	if(x<=mid) query(t[u].l,x,y,z);
	if(mid<y) query(t[u].r,x,y,z);
	if(t[t[u].l].x>t[t[u].r].x) t[u].x=t[t[u].l].x,t[u].sq=t[t[u].l].sq;
	else t[u].x=t[t[u].r].x,t[u].sq=t[t[u].r].sq;
	return;
}
pii ask(int u,int x,int y){
	if(x<=t[u].L && t[u].R<=y) return {t[u].x,t[u].sq};
	pd(u);
	pii ans={-1,-1},tmp={-1,-1};
	int mid=t[u].L+t[u].R>>1;
	if(x<=mid) ans=ask(t[u].l,x,y);
	if(mid<y) tmp=ask(t[u].r,x,y);
	if(t[t[u].l].x>t[t[u].r].x) t[u].x=t[t[u].l].x,t[u].sq=t[t[u].l].sq;
	else t[u].x=t[t[u].r].x,t[u].sq=t[t[u].r].sq;
	if(ans.first>tmp.first) return ans;
	else return tmp;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,m,rp=0;pii ans={1,1};
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		num=1;
		t[1].L=1,t[1].R=m,t[1].sq=1;
		for(int i=1;i<n;i++){
			if(a[i+1]-a[i]<=m) s[i].l=1,s[i].r=m;
			else if(a[i+1]-a[i]>=2*m) s[i].l=s[i].r=0;
			else s[i].l=(m-a[i]%m)%m+1,s[i].r=m-a[i+1]%m;
		}
		s[n].l=s[n].r=0;
		for(int i=1;i<n;i++){
			int l=s[i-1].l,r=s[i-1].r;
			if(l){
				if(l<=r) query(1,l,r,-1);
				else {query(1,l,m,-1);query(1,1,r,-1);}
			}
			while(rp<n && ask(1,1,m).first==rp-i+1){
				rp++;
				l=s[rp].l,r=s[rp].r;
				if(l){
					if(l<=r) query(1,l,r,1);
					else {query(1,l,m,1);query(1,1,r,1);}
				}
			}
			l=s[rp].l,r=s[rp].r;
			if(l){
				if(l<=r) query(1,l,r,-1);
				else {query(1,l,m,-1);query(1,1,r,-1);}
			}
			pii tmp;
			if(a[rp]%m && m-a[rp]%m+1<=m-a[i]%m){
				tmp=ask(1,m-a[rp]%m+1,m-a[i]%m);
				if(tmp.first==rp-i && (a[rp]+tmp.second-1)/m-(a[i]+tmp.second-1)/m+1>ans.first) ans={(a[rp]+tmp.second-1)/m-(a[i]+tmp.second-1)/m+1,tmp.second};
			}
			tmp=ask(1,1,m-a[i]%m);
			if(tmp.first==rp-i && (a[rp]+tmp.second-1)/m-(a[i]+tmp.second-1)/m+1>ans.first) ans={(a[rp]+tmp.second-1)/m-(a[i]+tmp.second-1)/m+1,tmp.second};
			if(a[rp]%m){
				tmp=ask(1,m-a[rp]%m+1,m);
				if(tmp.first==rp-i && (a[rp]+tmp.second-1)/m-(a[i]+tmp.second-1)/m+1>ans.first) ans={(a[rp]+tmp.second-1)/m-(a[i]+tmp.second-1)/m+1,tmp.second};
			}
			tmp=ask(1,1,m);
			if(tmp.first==rp-i && (a[rp]+tmp.second-1)/m-(a[i]+tmp.second-1)/m+1>ans.first) ans={(a[rp]+tmp.second-1)/m-(a[i]+tmp.second-1)/m+1,tmp.second};
			l=s[rp].l,r=s[rp].r;
			if(l){
				if(l<=r) query(1,l,r,1);
				else {query(1,l,m,1);query(1,1,r,1);}
			}
		}
		cout<<ans.first<<" "<<ans.second-1<<"\n";
		for(int i=1;i<=num;i++) t[i].add=t[i].l=t[i].r=t[i].x=t[i].L=t[i].R=0;
	}
	return 0;
}
```

---

