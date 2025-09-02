# [POI 2013] INS-Inspector

## 题目描述

Inspector Byteasar is investigating a crime that took place on the premises of a software development company.

He is trying to establish the chain of events.

Unfortunately, the programmers are rather scatterbrained.

Statements of the kind "Well, when I checked at 14:42,    there were five other programmers logged in on the server."    are the most informative of those that Byteasar could get.

It is known that every programmer came to office at some point    during that day, spent some time in there without going out,    and then left for good, never coming back on the same day.

Byteasar, confused by the programmers' statements, is not sure    if he should rely on them.  In fact, he is wondering whether it is at all    possible that they all tell the truth.  He asks you for help in finding    that out.

一天公司有n个员工和m个员工记录，每个员工只会在连续的一段时间内工作。现在给出m条记录分别是谁写的、什么时候写的以及写的时候除了他还有多少人。求最大的k使得前k条记录互不矛盾


## 说明/提示

一天公司有n个员工和m个员工记录，每个员工只会在连续的一段时间内工作。现在给出m条记录分别是谁写的、什么时候写的以及写的时候除了他还有多少人。求最大的k使得前k条记录互不矛盾


## 样例 #1

### 输入

```
2
3 5
1 1 1
1 2 1
2 3 1
4 1 1
4 2 1
3 3
3 3 0
2 2 0
1 1 0
```

### 输出

```
4
3
```

# 题解

## 作者：huanxiong_2022 (赞：4)

## [P3553 [POI2013] INS-Inspector](https://www.luogu.com.cn/problem/P3553)

**摘要：**

1. 二分 $k$，每次沿时间轴检验前 $mid$ 个是否冲突。
2. 人的记录使他有一个必须存在的时间段。
3. 逐时间点、尽可能使人数最少地满足记录要求，并检查是否使用超过 $n$ 个人。

---

**题意：**

公司有 $n$ 个员工和 $m$ 个记录，每人只会在连续的一段时间内工作。现在给出 $m$ 条记录分别是谁写的、什么时候写的以及写的时候除了他还有多少人。求最大的 $k$ 使得前 $k$ 条记录互不矛盾。

**分析：**

1. 发现 $k$ 似乎无法直接求得，考虑转化为检验前 $k$ 条是否合法。

2. 发现对于第 $i+1$ 条记录，直接检验其与前 $i$ 条是否冲突似乎不好实现，考虑每次检验 $O(m)$ 地遍历全部时间点，因此需要二分 $k$。

3. 如何检验

	1. 由于每个员工工作时间连续，所以将记录整合可以得到每个人必须要工作的区间，后文简称“必要区间”，整合区间可以得到每个时间点至少有多少人，检验记录是否小于最小值。以及是否存在对于同一时刻有不同记录。
    
	2. 通过了前一个检测的所有情况中，每个时间点的记录人数大于等于实际人数，因此若不限制人数一定合法（即每个人只工作于一个时间点）。问题转化为尝试使用不多于 $n$ 个人构造一个合法解。
    
	3. 沿时间轴检验并时刻判断即可，详见下文。个人认为本题难点是检测的思路和具体实现。

4. 检验的实现
	1. 思路：

    	尝试用最优方式满足限制，并记录使用了多少人，看是否超过 $n$。
	2. 预处理：
    
    	每个时间点 $i$ 的记录人数、有多少人的“必要区间”以当前时间开始或结束；即 $cnt_i,bg_i,ed_i$。
    
	3. 实现方案不唯一，部分名称含义如下：
    
		$now$：当前至少要有多少人（由且仅由 $st_i,ed_i$ 决定）。
        
		$used$：已经使用过多少人。
        
		$exl$：有多少人已经完成了必要区间，但是被迫延后下班。
        
		$exr$：有多少人还没到必要区间，但是被迫提前上班。
        
		$fre$：没有写记录的人，他们可以自由安排。
        
		$left$：已经完成了工作，离开公司的人，后续安排与他们无关。
        
		注意，初始时认为上述全部为零；另外，上述名称在表述时逻辑上也视作集合。
        
	4. 每一步的处理方法
    
		处理顺序：$bg_i \rightarrow cnt_i \rightarrow ed_i$。通过变量上的加减、逻辑上的人员调动（即从某一集合移动到另一集合），用 $now,exl,exr$ 拼凑出 $cnt_i$
        
		- 当前点至少有 $bg_i$ 个人开始工作，逻辑上,要把 $exr$ 或者 $fre$ 拿出 $bg_i$ 个转化为 $now$，优先使用 $exr$，不足则增加 $used$。
        
		- $now+exl+exr$ 是当前我们构造的方案的人数，若其小于 $cnt_i$，则需要从 $fre$ 中抽调一些。因为$now$ 是被 $bg_i,ed_i$ 锁定的，所以把抽调的加在 $exr$ 上，逻辑上为要求这些人提前工作。
        
		- 若 $now+exl+exr$ 大于 $cnt_i$，则先弹掉 $exl$，仍多则弹掉 $exr$。
        
		- 在当前时间，有 $ed_i$ 个人可以结束工作，让他们进入 $exl$ 等待后续调度。
        
		- 最后，判断 $used$ 是否超限。把上述步骤循环 $m$ 次即可。

---

**实现：**

本人采用了 $now,used,exl,exr$ 实现，用 $used \ge n$ 判断不合法，仅在每次结尾判断即可，中间不需要判哪些变量是不是负数，个人认为比较好写。

注意，输入的是“除了他还有多少人”。


---
**Code:**

[Link](https://www.luogu.com.cn/record/125542901)

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10,inf=0x3f3f3f3f;
int T,n,m;
struct Log{int id,time,cnt;};
struct Staff{int bg,ed;};
struct Time{int cnt,bgcnt,edcnt,vis;};

Log g[maxn];
Staff p[maxn];
Time t[maxn];

bool check(int mid)
{
    for(int i=1;i<=n;i++)p[i]={0,0};
    for(int i=1;i<=m;i++)t[i]={0,0,0,0};
    for(int i=1;i<=n;i++)p[i]={inf,-inf};

    for(int i=1;i<=mid;i++)
    {
        //同一时刻的记录发生冲突
        if( t[g[i].time].cnt!=0 && t[g[i].time].cnt!=g[i].cnt)
        {
            return false;
        }
        t[g[i].time].cnt = g[i].cnt;
        t[g[i].time].vis=1;
        p[g[i].id].bg=min(p[g[i].id].bg,g[i].time);
        p[g[i].id].ed=max(p[g[i].id].ed,g[i].time);
    }
    for(int i=1;i<=n;i++)
    {
        if(p[i].bg!=inf)
            t[p[i].bg].bgcnt++,t[p[i].ed].edcnt++;
    }
    int now=0,used=0,exl=0,exr=0;
    //“必要区间”决定的人数
    //使用过的人数
    //可以下班但被迫加班的人数
    //暂时不用上班但是被迫提前的人数
    //即 exl 位于左侧的可拓展人数，exr右侧可拓展
    for(int i=1;i<=m;i++)
    {
        if(!t[i].vis)continue;
        
        now += t[i].bgcnt;

        if(now>t[i].cnt)
            return false;
        //“必要区间”与记录矛盾

        while (t[i].bgcnt--)
        {
            if(exr)exr--;
            else   used++;
        }
        //需要有一些人开始工作，有 exr 就让他开始，没有就新调人来
        //注意这里新增加的 used 是不可以被划分成 exl 的，他们会在结束自己的“必要区间”后加入 exl
        //可以写成 if else 的判断，但是 while 易于理解且不容易错

        if(now+exl+exr<t[i].cnt)
        {
            int d = t[i].cnt-now-exl-exr;
            exr+= d;  used+= d;
        }

        if(now+exl+exr>t[i].cnt)
        {
            int d = now+exl+exr-t[i].cnt;
            while(d--)
            {
                if(exl>0)exl--;
                else exr--;
            }
        }

        now-=t[i].edcnt; exl+=t[i].edcnt;

        if(used>n)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&g[i].time,&g[i].id,&g[i].cnt);
            g[i].cnt++;
        }
        int l=1,r=m;
        while(l<r)
        {
            // printf("l=%d,r=%d  ",l,r);
            int mid=(l+r+1)>>1;
            if(check(mid))l=mid;
            else r=mid-1;
        }
        printf("%d\n",l);
    }
    return 0;
}
```

upd:
2023.09.22 初稿

---

## 作者：litble (赞：3)

# 题目分析

[个人博客](https://blog.csdn.net/litble/article/details/90180250)

首先二分答案，就可以只判断这几条可不可行了。

根据每个人的称述，我们先可以给这些人确定一个大致的“必须存在的区间”，而那些没有称述的人，根据boshi命名法，称其为“**幽灵**”。

假设当前检查的时刻$i$，必须存在的人数为$s_i$。

`nows`：由于“必须存在的区间”，而导致当前时刻至少有多少人存在。

`people`：当前已经被“使用”了的人数。

`ghost`：当前使用了，且其所在区间还在向右延伸的“幽灵”数。

`extend`：已经使用了的非幽灵人中，所在区间依然在向右延伸的人数。

那么检查的大致流程如下：

1. 检查是否有关于同一时刻的矛盾称述，再从左往右检查每个时刻。
2. 检查“必须存在的区间”左端点为当前时刻的非幽灵。因为幽灵的使用更为自由，所以幽灵更应该保留到万不得已的时候用。`ghost`中那些存在区间是当前考虑的时间前缀的后缀的幽灵，可以通过当前时刻出现的非幽灵的存在区间向前延伸来代替，`ghost`减小。
3. 若`nows>s_i`，必不合法。接下来就要让`nows+extend+ghost=s_i`，若左式小了，就添加一些幽灵（同时被使用的人数增加）。若左式大了，由于`ghost`继续往后延伸还可能能被代替，所以先让`extend`中的人停止区间延伸，再让`ghost`中的停止。
4. 检查“必须存在的区间”右端点为当前时刻的非幽灵，他们所在区间可以继续往右延伸，加入`extend`中。
5. 所有时刻检查完后，检查`people`是否超过了人数。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
const int N=100005;
int T,n,m;
int record_p[N],record_t[N],record_s[N],L[N],R[N],s[N],appear[N],disappear[N];

int check(int lim) {
	for(RI i=1;i<=m;++i) s[i]=-1,appear[i]=disappear[i]=0;
	for(RI i=1;i<=n;++i) L[i]=m+1,R[i]=0;
	for(RI i=1;i<=lim;++i) {
		int p=record_p[i],t=record_t[i];
		if(s[t]!=-1&&s[t]!=record_s[i]) return 0;
		s[t]=record_s[i],L[p]=min(L[p],t),R[p]=max(R[p],t);
	}
	int nows=0,people=0,ghost=0,extend=0;
	for(RI i=1;i<=n;++i) if(R[i]) ++appear[L[i]],++disappear[R[i]];
	for(RI i=1;i<=m;++i) {
		if(s[i]==-1) continue;
		nows+=appear[i];
		if(ghost<appear[i]) people+=appear[i]-ghost,ghost=0;
		else ghost-=appear[i];
		if(nows>s[i]) return 0;
		if(nows+ghost+extend<s[i])
			people+=s[i]-nows-ghost-extend,ghost+=s[i]-nows-ghost-extend;
		if(nows+ghost+extend>s[i]) {
			int kl=nows+ghost+extend-s[i];
			if(kl<=extend) extend-=kl;
			else ghost-=kl-extend,extend=0;
		}
		nows-=disappear[i],extend+=disappear[i];
	}
	return people<=n;
}

int main()
{
	T=read();
	while(T--) {
		n=read(),m=read();
		for(RI i=1;i<=m;++i)
			record_t[i]=read(),record_p[i]=read(),record_s[i]=read()+1;
		int l=0,r=m,mid,ans=0;
		while(l<=r) {
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：nofall (赞：2)

### 分析

先二分答案转化成一个判定性问题，这样记录就没有先后之分了。

然后考虑什么情况会出现矛盾

1. 两条记录是同一时刻的，但人数不同。

解决：直接特判

2. 举个例子

小$A$在$x$时刻写过一个记录，又在$y$时刻写了一个记录，小$B$写除了他没有人了。

解决：对每个人记录一下最晚开始时间和最早结束时间当成一条线段，对于每个时间节点，算被几条线段覆盖，线段条数大于当前时间记录的人数时就是无解。

3. 根据记录构造出一种方案，但是会超过n个人的限制的方案

解决：计算出他的最小符合条件的人数，判断是否$<=n$。

code:

```cpp
#include<cstdio>
#define N 100010
#define inf 0x3f3f3f3f
int n, m, t[N], u[N], v[N], mn[N], mx[N], tot[N], st[N], en[N];
inline int read() {
	register int x = 0; register char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline void write(int num) {
	if (num > 9)
		write(num / 10);
	putchar(num % 10 ^ 48);
}
template<class type>
type max(type &a, type &b) {
	return a > b ? a : b;
}
template<class type>
type min(type &a, type &b) {
	return a < b ? a : b;
}
bool check(int M) {
	for (int i = 1; i <= n; i++)
		mn[i] = inf, mx[i] = -inf;
	for (int i = 1; i <= m; i++)
		tot[i] = st[i] = en[i] = 0;
	for (int i = 1; i <= M; i++) {
		mn[u[i]] = min(mn[u[i]], t[i]), mx[u[i]] = max(mx[u[i]], t[i]);
		if (tot[t[i]] and tot[t[i]] != v[i] + 1)
			return false;
		tot[t[i]] = v[i] + 1;
	}
	for (int i = 1; i <= n; i++)
		if (mx[i] != -inf)
			st[mn[i]]++, en[mx[i]]++;
	int total = 0, now = 0, done = 0, notr = 0;
	for (int i = 1; i <= m; i++)
		if (tot[i]) {
			now += st[i];
			if (now > tot[i])
				return false;
			if (st[i] <= notr)
				notr -= st[i];
			else
				total += st[i] - notr, notr = 0;
			if (now + notr + done < tot[i])
				total += tot[i] - now - notr - done, notr = tot[i] - now - done;
			else {
				if (now + notr > tot[i])
					notr = tot[i] - now, done = 0;
				else
					done = tot[i] - now - notr;
			}
			now -= en[i]; done += en[i];
		}
	if (total > n)
		return false;
	return true;
}
int main() {
	int T;
	T = read();
	while (T--) {
		n = read(), m = read();
		for (int i = 1; i <= m; i++)
			t[i] = read(), u[i] = read(), v[i] = read();
		int l = 1, r = m + 1, mid;
		while (l < r) {
			mid = (l + r) >> 1;
			if (check(mid))
				l = mid + 1;
			else
				r = mid;
		}
		write(l - 1), putchar('\n');
	}
	return 0;
}
```

---

## 作者：STDLRZ (赞：1)

这道题很妙。

### $\tt 100~pts$ 做法

首先，一眼二分（问题的解有单调性，前半部分可以，后半部分不可以），将原问题转为判定性问题。

问题被转换为：判断前 $k$ 条信息是否有矛盾。

但是，这个问题还是没有办法做啊。

- **妙点：我们可以先不管那些不确定因素，先考虑确定因素。**

对的，直接考虑是没有办法的，我也无能为力。

但是，如果我们可以将确定因素和不确定因素分开，说不定这个问题就解决了呢？

如果一个人在多个时间点打了卡，因为题目说每一个人的工作时间是连续的，所以我们可以记录他最开始是什么时候打卡的，和他最后是什么时候打卡的，我们就知道他至少要工作的是哪一段时间。

这样，我们就可以将每一个时间点必须工作的人数给记录下来。

如果有记录的信息说，时间点 $t$ 的工作人数为 $x$，但是必须工作的人数比他多的话，这就一定矛盾了，直接 `return 0` 即可。

$\tt OK$，我们知道了必须工作的人和这些人的区间，那我们接下来怎么办呢？

先不要着急，我们来讨论一下。

首先，我们得知当前必须工作的人一定比 $x$（上面的定义）要多（至少等于）。

也就是说，我们还要再加一些人。

我们可以拉一些自由人（那些不目前需要工作的人），来让他们工作。

那我们要先拉哪些人呢？

我们可以先拉那些已经下班的人，强制他们继续工作，这样我们就可以尽量减少人力成本了，不需要新的人过来工作。

但是如果那些已经下班的人彻底下班了呢？

- 我们定义彻底下班的人为，加班的工作也做完了，且在之前的某个时刻**不需要他工作了，让他下班了**的那些人数。

像这些人肯定是不能拉回来的，因为我们知道，每一个人的工作区间是连续的，之前已经有一个时间点他没有工作了，如果把他拉回来工作，证明之前的那个**不需要他的时间点**他又要工作了，那就不满足条件了。

所以，这些人我们不能拉回来叫他们工作，只能让他们回去。

如果把那些没有彻底下班的人全部拉过来还不够，我们就只能让一些人**提前上班了**。

但是，请注意：我们在人数太多的时候可不可以让一些人从提前上班变成不提前上班呢？

此时，我们发现，如果这些人走了，那他们就**只能是自由人**，这些自由人**原本是不需要工作的**（没有必须工作的时间段），只能让他们走，其他的不能走。

为了代码的实现方便，我们将这些自由人和提前上班的人给合并了一下，这个逻辑也是没问题的。当然，如果你非要和提前下班的人合并，也是可以的，但不过有点难写。

所以，我们合并之后，就相当于让提前上班的人走了，且没有办法让他们回来了（因为是自由人嘛，且现在不需要他了，则以后也不能用他了）。

考虑让一些人上班的时候该怎么办。

我们可以在那些提前上班的人里面抽几个出来让他们工作（实际上编号是没有用的，因为我们的编号可以调换，而且我们也不需要知道是谁什么时候上班，只需要知道有几个人要现在上班就可以了）。

但是如果没有提前上班的人呢？我们要叫他起来工作了，~~不能睡懒觉了。~~

为什么前面让自由人和提前上班的人合并没有影响呢？因为我们的编号可以**调换！**

比如说，我们原本是编号为 $3$ 的人是自由人，$1$ 是现在要工作的人，现在 $1,3$ 都提前工作了，我们要抽调一个人出来工作。

假设我们运气非常不好，抽到了编号为 $3$ 的人，但是可能他本来就不需要工作，于是我们让这个人变成编号为 $1$ 的人，剩下一个编号为 $3$ 的人就和那个原本是编号为 $1$ 的人调换，这样就没有问题了。

如果还没有理解可以看看代码中的附说明。

我们总结一下过程：

- 首先，我们定义 `used` 表示已经使用过的人数，`tiq` 表示正在提前上班的人有几个，`yah` 表示还没有彻底下班（还在工作），但是原本已经不需要工作的人有几个，`now` 表示现在必须要工作的人有几个。
- 如果当前的信息中有 $x$ 个人在工作，且 $x$ 比当前必须工作的人要小，证明肯定矛盾（和确定性的东西矛盾了，那不是矛盾是什么？），返回 `0`。
- 否则，我们从提前工作的人里面抽调一些人出来工作，也就是 `--tiq,++now`（因为这些人这个时间必须要工作了嘛，且他们现在也不是提前工作的人了）。
- 如果还不够，那就新增一些人（叫一些人起来干活），直接 `++now` 即可。
- 如果当前干活的总人数（`now+tiq+yah`）比当前信息要少，我们就只能新增一些自由人，让 `tiq+=need,used+=need`（`need` 表示需要的人数，我们已经将 `tiq` 和自由人这两个变量合并了，且正确性在前面已经叙述）。
- 否则，证明人数多了，我们就先让一些原本就要下班的人下班（表示他们彻底下班了），然后 `--yah`；如果已经没有延后下班的人，那就减少一些自由人，让这些自由人自由去，也就是 `--tiq`，直到和当前信息吻合即可。
- 接着，让那些准备在当前节点下班的人进入加班工作组，继续努力工作~~压榨员工~~。至于要不要他们继续工作就看下个时间点了，这个我们前面已经涉及到这部分了，不能重复处理。
- 判断 `used` 是否超过 $n$，如果超过 $n$，证明我们只有 $n$ 的人力但是不够用了，返回 `0`，否则继续新的下一轮即可。

代码：

```cpp
#include<bits/stdc++.h>
#define x0 x_0
#define x1 x_1
#define y0 y_0
#define y1 y_1
#define yn y_n
#define j0 j_0
#define j1 j_1
#define k0 k_0
#define k1 k_1
#define d0 d_0
#define d1 d_1
#define LL long long
#define LD long double
#define ZPB push_back
#define ZPF push_front
using namespace std;
int z,n,m;
struct node{
	int t,id,wrki;
	// t: 当前时间
	// id: 记录者
	// wrki: 当前时间 t 有 wrki 个人正在工作 
};
node info[100010];
// info，展开是 information，表示记录的信息。 
int st[100010],ed[100010],tbg[100010],tfn[100010],twki[100010];
// st[i]: 第 i 个人必须工作时间段的开始时间。
// ed[i]: 第 i 个人必须工作时间段的截止时间。
// tbg[i]: 在第 i 个时间点中，有几个人预计要开始工作。
// tfn[i]: 在第 i 个时间点中，有几个人预计要停止工作。 
// twki[i]: 在第 i 个时间点中，有几个人正在工作。 
bool check(int mid){
	for(int i=1;i<=n;++i) st[i]=1145141919,ed[i]=-1145141919; // 其实只要 st[i]>ed[i] 即可 
	for(int i=1;i<=m;++i) tbg[i]=tfn[i]=twki[i]=0; // 初始化 
	for(int i=1;i<=mid;++i){
		#define t info[i].t
		#define wrki info[i].wrki
		#define id info[i].id
		if(twki[t] && (twki[t]^wrki)) return 0; // 如果同一个时间的信息有矛盾（工作人数记录的不一样），return 0 
		twki[t]=wrki,st[id]=min(st[id],t),ed[id]=max(ed[id],t); // 更新每一个人的必须工作时间段和当前时间 t 有几个人在工作。 
		#undef t
		#undef wrki
		#undef id
	}
	for(int i=1;i<=n;++i)
		if(st[i]^1145141919) ++tbg[st[i]],++tfn[ed[i]]; // 更新 tbg 和 tfn 
	int now=0,tiq=0,yah=0,used=0,x; // 如总结中的定义所述，x 什么都不是，不用管 
	for(int i=1;i<=m;++i){
		if(!twki[i]) continue;
		now+=tbg[i],x=tbg[i]; // 有 tbg[i] 正式加入工作 
		if(now>twki[i]) return 0; // 如上面的文字所述 
		while(x--){
			if(tiq) --tiq; // 优先让那些提前工作的人正式开始工作 
			else ++used; // 如果人数不够那就加人 
		}
		if(now+tiq+yah<twki[i]){ // 1: 人数不够 
			int need=twki[i]-now-tiq-yah;
			tiq+=need,used+=need; // 新加入一些自由人 
		}else{ // 2: 人数不够 
			x=now+tiq+yah-twki[i];
			while(x--){
				if(yah) --yah; // 如果有延迟下班的人，让他们跑路，彻底下班，且以后不再使用到他们 
				else --tiq; // 否则，让一些自由人走，如果我们减去的是那些有必要工作时间段的人，调换一下编号即可 
			}
		}
		yah+=tfn[i],now-=tfn[i]; // 让那些在时间点 i 下班的人延迟下班 
		if(used>n) return 0; // 已经超过使用人数， return 0 
	}
	return 1; // 前 mid 条信息没有问题，return 1 
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>z;
	while(z--){
		cin>>n>>m;
		for(int i=1;i<=m;++i) cin>>info[i].t>>info[i].id>>info[i].wrki,++info[i].wrki;
		int L=1,R=m,ans=0;
		while(L<=R){ // 二分，不用多说，至于为什么 L 可以不是 0，因为第一条信息一定不会出现矛盾（自己应该不会和自己矛盾吧） 
			int mid=(L+R)>>1;
			if(check(mid)) L=mid+1,ans=mid;
			else R=mid-1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
/*
附说明：为什么每一次都有可以调换编号的人呢？不是每一个人都是自由人啊，万一当前没有自由人可以调换怎么办？
我们可以先看作 tiq 里面的所有人目前都是自由人，这样就不用考虑调换编号了。
但是我们在选一些人出来正式开始工作的那个时候又怎么办？
我们就可以让这些自由人和原本要工作的人的编号交换，让他们变成现在要工作的人但是提前上班了的那部分人，
然后把他们给 pop 出去。
因为我们每一次把自由人转为那些有必要工作区间的人时就立马让他加入工作了，所以这是没有问题的。
逻辑上可以理解为这些人原本就是提前上班了的人（不是自由人），但不过我们只是那个时候才更新他的身份而已，
之前没有更新他的身份是因为还不能确定他到底是自由人还是非自由人。 
*/
```

---

## 作者：DYYqwq (赞：0)

### [P3553 [POI2013] INS-Inspector](https://www.luogu.com.cn/problem/P3553)

这又是什么神仙题。。。

这东西必然有单调性，考虑二分。接着思考如何验证。这题的重点在于验证的实现过程。

总体思路：用最优方法放人，看人数与 $n$ 的关系。员工工作时间是连续的，因此我们要算出每个人必须要工作的区间，接着算出每个时间点至少有多少人，与记录的最小值对照，还需判断同一时刻有无不同记录。

首先预处理的时候，对于每一个时间节点 $i$，算出这个时间有多少员工被记录，以及有多少人的必须工作时间以此为开始或是结束。分别对应 $p\_t_i,st_i,nd_i$。

定义一些东西：

- $now\_least$ 表示现在最少需要的人数。
- $Tl$ 加班的人。
- $Tr$ 提前上班的人。
- $used$ 已经使用的人数。这个不能超过 $n$。

具体实现：

目标：拼凑出 $p\_t_i$。

- 当前点至少有 $st_i$ 个人开始工作，逻辑上，我们要拿出一些东西填补空缺。优先使用 $Tr$，$Tr$ 都不够的时候再考虑 $used$。
- 如果发现，我们构造的方案的人数 $< p\_t_i$，则需要从让一些人提前上班。 
- 否则，先弹 $Tl$，否则 $Tr$。
- 在当前时间，以当前时间点为下班时间的人可以先下班，加入  $Tr$，准备继续被压榨。
- 最后，看一眼 $used$ 与 $n$ 的关系。

循环完整个记录列表。

结束。

最后，每次二分的 check 之前必然要清空数组。因为这个虚空调半天。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T , n , m;
struct Recording
{
	int id , time , cnt;
}g[100010];
struct Staff
{
	int st , nd;
}p[100010];
struct Time
{
	int p_t , st , nd; // p_t ---> person for time 
	bool vis;
}t[100010];
void init()
{
//	for(int i = 1 ; i <= n ; i ++) p[i] = {0 , 0};
    for(int i = 1 ; i <= m ; i ++) t[i] = {0 , 0 , 0, 0};
    for(int i = 1 ; i <= n ; i ++) p[i] = {INT_MAX , INT_MIN};
    // 每做一次都要初始化清空数组。 
}
bool check(int mid)
{
	init();
    for(int i = 1 ; i <= mid ; i ++)
    {
        if(t[g[i].time].p_t != 0 && t[g[i].time].p_t != g[i].cnt) return false; // 发生冲突。 
        t[g[i].time].p_t = g[i].cnt , t[g[i].time].vis = true , p[g[i].id] = {min(p[g[i].id].st , g[i].time) , max(p[g[i].id].nd , g[i].time)};
    	// 正规的统计、记录vis以及更新最左与最右。 
	}
    for(int i = 1 ; i <= n ; i ++) if(p[i].st != INT_MAX) t[p[i].st].st ++ , t[p[i].nd].nd ++; //     时间变化了。
    int now_least = 0 , used = 0 , Tl = 0 , Tr = 0; // Tl ---> To left , Tr ---> To right
    for(int i = 1 ; i <= m ; i ++)
    {
        if(!t[i].vis) continue;
        now_least += t[i].st;
        // 产生冲突 again 
        if(now_least > t[i].p_t) return false;
//        if(t[i].st > Tr) Tr = 0 , used += t[i].st - Tr , t[i].st = 0;
//        else Tr -= t[i].st , t[i].st = 0;
		while(t[i].st --)
        {
            if(Tr) Tr --;
            else used ++;
        }
        if(now_least + Tl + Tr < t[i].p_t)
        {
            int dis = t[i].p_t - (now_least + Tl + Tr);
            Tr += dis , used += dis;
            // 提前上班。 
        }
//        if(now_least + Tl + Tr > t[i].p_t)
		else
        {
            int dis = now_least + Tl + Tr - t[i].p_t;
//            if(dis <= Tl) Tl -= dis;
//            else Tl = 0 , Tr -= (dis - Tl);
            while(dis --)
            {
                if(Tl) Tl --;
                else Tr --;
            } 
			// 先弹 Tl , 因为 Tr 实际上价值比 Tl 大。 
			// 十分抱歉，笔者不知为何 if else 判断写的是错的。只好使用更加好理解的 while。时间劣了一点，但是无伤大雅。 
        }
        now_least -= t[i].nd , Tl += t[i].nd; // 不是强制工作，而是备用。 
        if(used > n) return false; // 检查用过的人和 n 的关系。 
    }
    return true;
}
signed main()
{
    scanf("%lld" , &T);
    while(T --)
    {
        scanf("%lld%lld" , &n , &m);
        for(int i = 1 ; i <= m ; i ++) scanf("%lld%lld%lld" , &g[i].time , &g[i].id , &g[i].cnt) , g[i].cnt ++; // +1 是因为输入的是除了他    的人数量。
        int l = 1 , r = m;
        // 正规的二分。 
        while(l < r)
        {
            int mid = (l + r + 1) >> 1;
            if(check(mid)) l = mid;
            else r = mid - 1;
//            printf("l:%lld r:%lld\n" , l , r);
        }
        printf("%lld\n" , l);
    }
    return 0;
}
```

---

## 作者：MerlinLee (赞：0)

二分答案，没有出现过的时刻没有用，可以进行离散化。

首先如果某个时刻出现多个人数，那么肯定矛盾。

然后按时间依次考虑，维护：

$t$：剩余可选人数。

$s$：现在必定有的人数。

$cl$：往左延伸的人数。

$cr$：往右延伸的人数。

如果现在有人必须加入，那么优先踢掉 $cl$ 的人。

如果当前人多了，那么优先让 $cr$ 的人结束工作。

如果最后剩余可选人数非负，则可行。

时间复杂度 $O((n+m)\log m)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
const int BUF=33333333;
int T,n,m,i,e[N][3],l,r,mid,ans,a[N],b[N],c[N],p[N],L[N],R[N];
char Buf[BUF],*buf=Buf;
inline void read(int&a)
{
	for(a=0;*buf<48;buf++);
	while(*buf>47)
	  a=a*10+*buf++-48;
}
inline void umin(int &a,int b)
{
	if(a>b)
	  a=b;
}
inline void umax(int &a,int b)
{
	if(a<b)
	  a=b;
}
bool check(int mid)
{
	int x,y,cnt=0,s=0,cl=0,cr=0;
	for(int i=1;i<=n;i++)
	  L[i]=N,R[i]=0;
	for(int i=1;i<=m;i++)
	  a[i]=0;
	for(int i=1;i<=mid;i++)
	{
		int t=e[i][0];
		x=e[i][1];
		y=e[i][2];
		if(a[t] and a[t]!=y)
		  return 0;
		a[t]=y,umin(L[x],t),umax(R[x],t);
	}
	for(int i=1;i<=m;i++)
	  if(a[i])
	    p[i]=++cnt,a[cnt]=a[i],b[cnt]=c[cnt]=0;
	for(int i=1;i<=n;i++)
	  if(R[i])
	    b[p[L[i]]]++,c[p[R[i]]]++;
	for(int t=n,i=1;i<=cnt;i++)
	{
		s+=b[i];
		if(s>a[i])
		  return 0;
		while(b[i]--)
		  if(cl>0)
		    cl--;
		  else 
		    t--;
	 	while(s+cl+cr<a[i])
		  cl++,t--;
    	while(s+cl+cr>a[i])
		  if(cr>0)
		    cr--;
		  else 
		    cl--;
    	s-=c[i],cr+=c[i];
    	if(t<0)
		  return 0;
	}
	return 1;
}
int main()
{
	for(fread(Buf,1,BUF,stdin),read(T);T--;
	printf("%d\n",ans))
	{
    	read(n),read(m);
    	for(i=1;i<=m;i++)
	  	  read(e[i][0]),read(e[i][1]),read(e[i][2]),e[i][2]++;
    	l=2,r=m,ans=1;
    	while(l<=r)
		  if(check(mid=(l+r)>>1))
		    l=(ans=mid)+1;
		  else 
		    r=mid-1;
  	}
  	return 0;
}
```
撒花。

---

