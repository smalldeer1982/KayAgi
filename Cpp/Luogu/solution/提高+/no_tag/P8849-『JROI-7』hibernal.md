# 『JROI-7』hibernal

## 题目背景

我也不知为何会想说这个故事，我也确实不太理解小丑和厨师有什么关系，但既然他们此时此刻排列在我的草稿本上【附图】，那我也只能试着说说了。

呃呃，你说的很对，我也确实想不出他们的关系了。

唔，小丑会出现在这里或许多半是因为他的出场总伴着诡异。

但我还是觉得厨师这个角色有趣。

但是，但是，这和【hibernal】有什么关系吗。

啊，还是来说说厨师吧。食材还是让人觉得有趣的。

欸，其实蔬菜能提供比肉类丰富的多的口感，但是似乎大家都不认同我的观点，你呢？

英文字母和汉字之间要加空格，让我检查检查。

【AI绘画】少女，裸背，颈控。

啊，我知道了。这似乎可以是个有趣的故事。唔，写起来可能很花时间，你还是先过了这题再来催我吧 qwq.

最后是不是要说点什么以示礼貌啊。那就祝大家身体健康吧，好耶！

## 题目描述

有 $n$ 个苹果，第 $i$ 个编号为 $i$，其中有恰好 $2$ 个是金苹果。

每次询问可以把 $n$ 个苹果分为两个集合 $S_1,S_2$，要求每个苹果恰好被分到一个集合中。

设 $x$ 为 $S_1$ 中金苹果的个数，$y$ 为 $S_2$ 中金苹果的个数，交互库会返回 $x\times y$ 的值。

请在不超过 $19$ 次询问内求出两个金苹果的编号。

**交互库自适应，即两个金苹果的编号可能会随着询问而改变，但是始终满足所有已经发生过的询问（见样例）。**

## 说明/提示

**样例仅供理解交互过程，可能不符合逻辑。**

【样例解释】

初始的两个金苹果为 $3,5$。

第一次询问，两个集合各有 $1$ 个金苹果，返回 $1$，金苹果的编号不发生改变。

第二次询问，一个集合有 $2$ 个金苹果，另一个集合没有，返回 $0$。接下来两个金苹果从 $3,5$ 变成了 $1,5$，容易发现，虽然金苹果的编号发生了变化，前两个询问的答案仍然是符合的。

回答 $1,5$，答案正确，交互结束。

---
### 数据范围
| 分数 | $n=$ | $T=$ |
| -----------: | -----------: | -----------: |
| $10$ | $2$ | $200$ |
| $10$ | $18$ | $200$ |
| $10$ | $64$ | $200$ |
| $20$ | $512$ | $200$ |
| $50$ | $1000$ | $200$ |
### 计分方式
对于每组测试数据，取 $200$ 组测试中进行询问次数最大的一组，若超过 $19$ 次，计 $0$ 分，否则计满分。

保证正常情况下交互库用时不超过 0.1s。

如果您的输出不合法，将会出现 TLE/WA 等情况。

## 样例 #1

### 输入

```
1
5

1

0

```

### 输出

```


? 3 1 2 3

? 2 2 4

! 1 5```

# 题解

## 作者：Xy_top (赞：7)

一道好题。

观察数据，要求询问次数不超过 $\lceil2\log n\rceil-1$，相当困难。

我刚开始也在想二分，但这个东西并不具有单调性，但这个题具有的特点就是你不仅仅可以询问一个前缀，你还可以询问任意的集合。

首先发现如果能将 $n$ 个苹果分成 $S_1$ $S_2$ 两个长度接近的集合，且 $S_1$ 和 $S_2$ 中各出现了一个金苹果，就可以直接二分然后在 $\lceil2\log n\rceil-2$ 次询问内解决问题了（因为已经分成 $S_1$ $S_2$ 两个长度接近的集合了）。

怎么解决呢？我们假设去分 $S_1$，每次把它分成数量接近的两份 $S_3$ $S_4$，取其中一份。无论取 $S_3$ 还是 $S_4$，剩下的苹果中肯定有一个是金苹果了吧，因为 $S_2$ 中一定有一个金苹果。

随便取一个 $S_3$ 或者 $S_4$，如果得到的答案是 $1$，那么肯定在当前选择的区间中，继续递归，否则就在另一个区间中。

但是我们暂时没有想到合适的方法能够用 $1$ 次询问找到 $S_1$，$S_2$（貌似只有猜可以。

所以我想到了在求 $S_1$，$S_2$ 的过程中找到两个金苹果位置之间的关联。

这里需要用到二进制分组的技巧啦！

从高到低地考虑每一个二进制位，将所有的位置按照这一位二进制位分为两个部分：一是这一位是 $0$，二是这一位是 $1$。

我们来看看能够得到些什么，如果返回 $1$，就说明两个区间内各有一个金苹果，我们就成功了，并且还能够得到两个金苹果当前的二进制位不同。

如果是 $0$ 呢？只能够得到两个金苹果当前的二进制位是相同的。

这样一定能得到一组询问答案是 $1$ 吗？显然可以。如果全是 $0$，那么意味着两个金苹果每一个二进制位都相同，也就是同一个金苹果了，所以肯定有一个二进制位不同啦！

这样就花去了 $\lceil\log n\rceil$ 次询问，得到两个集合，接着再进行 $\lceil\log n\rceil -1$ 次二分，刚刚好能够求出一个金苹果的位置。

那另一个呢？我们不是求出金苹果两个每一个二进制位是否相同了吗？所以也解决了。其实熟练的人看一下就知道了那个是异或值，所以假如知道了 $a\oplus b=c$，那么 $b=a\oplus c$，就这样结束了。

超短代码：

```cpp
#include <iostream>
#define For(i, a, b, j) for (int i = (a); i <= (b); i = (j) )
using namespace std;
int T, n, k, kx;
int x, oplus;
int a[505], b[505];
int find (int l, int r) {
    if (l == r) return b[l];
    int mid = l + r >> 1;
    printf ("? %d ", mid - l + 1);
    For (i, l, mid, i + 1) printf ("%d ", b[i]);
    printf ("\n");
    fflush (stdout);
    scanf ("%d", &x);
    if (x == 1) return find (l, mid);
    return find (mid + 1, r);
}
int main () {
    fflush (stdout);
    scanf ("%d", &T);
    while (T --) {
        oplus = 0;
        fflush (stdout);
        scanf ("%d", &n);
        For (m, 1, n, m << 1) {
            k = 0;
            For (i, 1, n, i + 1) if ( (i & m) == 0) a[++ k] = i;
            printf ("? %d ", k);
            For (i, 1, k, i + 1) printf ("%d ", a[i]);
            printf ("\n");
            fflush (stdout);
            scanf ("%d", &x);
            oplus += x * m;
            if (x == 1) {
                For (i, 1, k, i + 1) b[i] = a[i];
                kx = k;
            }
        }
        int ans = find (1, kx);
        printf ("! %d %d\n", min (ans, ans ^ oplus), max (ans, ans ^ oplus) );
        fflush (stdout);
    }
    return 0;
}
```


---

## 作者：Terac (赞：4)

[$\texttt{link}$](https://www.luogu.com.cn/problem/P8849)

这个题很有趣啊。

设答案为 $a,b$，交互次数小于 $19$，是 $2\log_2 n-1$，考虑如何在两次 $\log$ 的询问求出答案。

仔细思考一下，发现可以对每一位是 $1$ 和每一位是 $0$ 的分一组，这样可以求出 $a,b$ 的异或和 $c$。

若 $c$ 的 $k$ 位为 $1$，钦定 $a$ 的第 $k$ 位为 $1$，对于所有 $i\ne k$，将 $\left[1,n\right]$ 中第 $i$ 位和第 $k$ 位均为 $1$ 的数拿出来询问。若返回 $1$，说明 $a$ 的第 $i$ 位是 $1$，否则 $a$ 的第 $i$ 位是 $0$。

求出 $a$ 和 $a \oplus b$ 后，$b$ 也知道了，询问次数恰好是 $2\log_2 n-1$。

---

## 作者：一E孤行 (赞：4)

~~赛时看到交互题，直接开始莽~~

交互题的操作次数往往就是你所需要的询问复杂度，注意到这里的操作次数为 $19$ 次，因此可以得知，我们询问的次数应该是 $2 \log n$。

看到这种复杂度，我们的第一想法是二分，但是二分必须是答案满足单调性的时候才能二分。我们每次询问只能得知一些苹果中是否含有金苹果。具体的，如果我们问的是一个区间，我们并不能通过知道这个区间内是含有两个金苹果还是只有一个，来确定下一个区间应该是哪边，所以我们只能放弃进行二分。

依稀记得，曾经做过一个月赛交互题叫[毒水](https://www.luogu.com.cn/problem/P7824)，成功的教会了我另一种带 $\log$ 的复杂度的处理技巧：二进制分组。

设 $n$ 的最大二进制位是第 $x$ 位，我们把 $0$ 到 $x$ 位分开考虑，把每一位二进制相同的分为一组，这样最多询问 $\log n$ 次。经过这样的询问，我们就能知道两个金苹果的每一位二进制位是相同还是不同。

由于金苹果有 $2$ 个，所以必然存在至少一位二进制两个金苹果是不同的，我们把它固定住，剩下的位置我们把 $0$ 和 $1$ 分到不同的组询问，假设第一个金苹果填的是 $1$，根据询问结果再结合以前得出的该位二进制位是否相同就可以得出两个金苹果该填什么。显然第二次询问也是把所有的二进制都考虑一遍，因此也是 $\log n$ 次，加起来需要的次数可以满足题目需求。


```cpp
int output(vector<int> a) {
    if(a.size()==0 || a.size()==n) return 0;
    printf("? %d ",a.size());
    for(int v:a) printf("%d ",v);
    fflush(stdout);
    int x;
    scanf("%d",&x);
    return x;
}
int getans(int j) {
    vector<int> a;
    for(int i=1;i<=n;i++) if((i>>j)&1) a.push_back(i);
    return output(a);
}
int vis[1005];
int main() {
     int T;
     scanf("%d",&T);
     while(T--) {
        scanf("%d",&n);
        if(n == 2) {
            printf("! 1 2\n");
            fflush(stdout);
            continue;
        }
        int maxp=0;
        while((1<<maxp+1)<=n) maxp++;
        int ans1=0,ans2=0,st=0,num=0;
        for(int i=0;i<=maxp;i++) {
            vis[i]=getans(i);
            if(num==0 && vis[i]==1) num+=(1<<i),st=i;
        }
        ans1=num;
        for(int i=0;i<=maxp;i++) {
            if(i == st) continue;
            if(vis[i] == 0) {
                vector<int> a;
                for(int j=1;j<=n;j++) if(((j&num)==num) && (j>>i&1)) a.push_back(j);
                int x=output(a);
                if(x == 1) ans1|=(1<<i),ans2|=(1<<i);
            } else {
                vector<int> a;
                for(int j=1;j<=n;j++) if(((j&num)==num) && (j>>i&1)) a.push_back(j);
                int x=output(a);
                if(x == 1) ans1|=(1<<i);
				else ans2|=(1<<i);
            }
        }
        if(ans1 > ans2) swap(ans1,ans2);
        printf("! %d %d\n",ans1,ans2);
        fflush(stdout);
     }
    return 0;
}
```

---

## 作者：critnos (赞：3)

如果划分的集合 $S1,S2$ 满足 $S1$ 和 $S2$ 中都恰有一个关键点，那么可以在 $\log(|S1|)$ 的时间找到 $S1$ 中的关键点。

将 $S1$ 均分为两集合 $S3,S4$，查询集合 $S3+S2$ 和 $S4$。若 $S3$ 中存在关键点，那么答案为 $0$；否则为 $2$。在 $S3$ 和 $S4$ 中定位关键点后，将不存在关键点的集合并到 $S2$ 中。

那么考虑求出集合 $S1,S2$ 满足$S1$ 和 $S2$ 中都恰有一个关键点。为了方便，设 $n=2^k$。

第一次操作将编号均分为两部分（$[1,n/2],(n/2,n]$）。取出第一份作为 $S1$，第二份作为 $S2$，进行查询。若满足条件则跳出，否则继续。

第二次操作将编号均分为四部分。取出第一、三份作为 $S1$，剩余的为 $S2$。以此类推。

显然，某次操作后如果仍不满足条件，那么说明两个关键点都在这次操作划分的某一部分中。

那么进行到最后一次操作，划分大小为 $1$，必然能成功地划分。

所以在某次成功地划分后，使用 $\log n$ 的时间找到 $S1$ 中的关键点。在找到这个关键点后，$S2$ 的关键点就存在于某次成功划分中 $S1$ 中的关键点存在部分的相邻位置。

那么 $S2$ 的大小仅为该划分部分的大小。使用 $\log |S2|$ 的时间找到 $S2$ 中的关键点。这里的时间加上划分操作的时间恰为 $\log n$。

---

## 作者：Cocoly1990 (赞：3)

## 约定

记两个金苹果的编号为 $x,y$。文中的 $\log$ 均上取整。

## 从暴力说起

注意到当两个金苹果在一个集合内时，交互库返回 $0$，否则返回 $1$。

我们考虑对于每个 $i$，都询问一次 $S_1=\{i\}$，不难发现我们至多询问 $n-1$ 次即可确定。

## 逐步分解

考虑如果我们知道了两个符合题设的集合 $S_1,S_2$，满足 $x\in S_1$，$y\in S_2$，那么，我们如何在 $2\times \log n$ 次询问内找出金苹果位置。

![1668516818768.png](https://img-kysic-1258722770.file.myqcloud.com/c664979af4c8fd1ea9fa194d3f76e3fa/c8c8760094c32.png)

我们先考虑 $S_1$，不难想到分治解决。具体的，如图所示，可以把他分成两份，分别标做灰和绿，并将 $S_2$ 标做蓝，每次询问绿色和灰色部分的并，若返回 $0$，则递归到绿色部分继续处理，否则递归到灰色部分继续处理。对于 $S_2$ 同理。

## 进一步的

怎么找到上述的集合 $S_1,S_2$ 呢，我们其实只需要构造一种分组方式把两个金苹果分到不同组。

我们考虑一个基本的结论：若 $x\neq y$，那么 $x,y$ 在二进制下至少有一位不同。

这是显然的，所以我们可以考虑进行 $\log n$ 次分组操作，其中第 $i$ 次将二进制下第 $i$ 位为 $0$ 的分到 $S_1$，其余分到 $S_2$。那么，不难发现，至少有一次询问的结果是 $1$。

## 再优化？

现在我们已经做到了 $3\times \log n$ 了，还能不能再优化？

让我们想想还有哪些信息没有用到，没错，我们在寻找集合 $S_1,S_2$ 的过程中只关心回答为 $1$ 的询问，事实上，如果我们考虑分析所有回答，不难发现每次回答的结果其实是 $x,y$ 当前位的异或值！因此我们只需要对较小的 $S_1,S_2$ 分治解决即可，至此，询问次数优化为 $\log n+\log \frac{n}{2}$。

## 证明

通过信息论可以证明 $\log n+\log \frac{n}{2}$ 是本题最坏情况下的询问下界。

---

## 作者：iyaang (赞：3)

[更好的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/16885159.html)

[题目链接](https://www.luogu.com.cn/problem/P8849)

交互题，显然返回值为 $1$ 时在所分的两个组中各一个，否则则在所分的同一个组中。

限制次数的题一般都从数据范围入手，可以发现最大范围 $\log_21000 \approx 9$，再看这个最大操作次数为 $19$ 次，八成就是跑两遍相关的算法了。

考虑二进制拆分，首先将按照二进制每一位上分组，每次单独看一位，将这一位上是 $0$ 的分在一组里面，是 $1$ 的分在一组里面，如果不在同一组中则说明最终答案的两个下标在二进制这一位下不同，询问次数为 $\log_2n$。

由于两个不同的数他们的二进制位上必然有一位不同，我们随便选一个不同的位，然后分成两组二分答案。具体就是始终固定一组，然后找另一组中的答案：将要选出答案的那一组不断二分缩小范围，剩下的放入一组。大致就是下图这么一个过程。

![QQ图片20221120073531.png](https://s2.loli.net/2022/11/20/KhS5pAyxWfIiLUM.png)

因为我们知道了两个答案在二进制位上哪一位相同哪一位不同，就可以直接推出另一个答案了。第一次的分组可以在前面的询问中记录下来一个，后面二分答案询问次数则是严格小于 $\log_2n$ 的。

$Code$
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

namespace LgxTpre
{
    static const int MAX=100010;
    static const int INF=200707070707;

    int T,n,g;
    bool check[20];
    int lis[MAX],l,r,t;

    inline void init()
    {
        memset(check,0,sizeof check);
		memset(lis,0,sizeof lis);
		l=1,r=0;
        cin>>n;
        t=__lg(n);
    }

    inline void Binary_Split()
    {
        for(int k=0;k<=t;++k)
		{
			int cnt=0;
			cout<<"? ";
			for(int i=1;i<=n;++i)
				if(((i>>k)&1)==1) 
					++cnt;
			cout<<cnt<<" ";
			for(int i=1;i<=n;++i)
				if(((i>>k)&1)==1)
					cout<<i<<" ";
			cout<<endl;
			cin>>check[k];
			if(check[k]==1) g=k;
		}
    }
    inline void Binary_Group()
    {
        for(int i=1;i<=n;++i)
			if(((i>>g)&1)==1)
				lis[++r]=i;
		while(l<r)
		{
			int mid=(l+r)>>1,op,cnt=0;
			cout<<"? ";
			for(int i=l;i<=mid;++i)
				++cnt;
			cout<<cnt<<" ";
			for(int i=l;i<=mid;++i)
				cout<<lis[i]<<" ";
			cout<<endl;
			cin>>op;
			if(op==0) l=mid+1;
			else r=mid;
		}
    }
    inline void Find_Answer()
    {
        int x=lis[l],y=x;
		for(int i=0;i<=t;++i)
			if(check[i])
				y=y^(1<<i);
		if(x>y) swap(x,y);
		cout<<"! "<<x<<" "<<y<<endl;
    }

    inline void lmy_forever()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>T;
        while(T--)
        {
            init();
            Binary_Split();
            Binary_Group();
            Find_Answer();
        }
    }
}

signed main()
{
	LgxTpre::lmy_forever();
	return (0-0);
}
```

---

## 作者：Y_ATM_K (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/P8849)

## 分析

首先，看到询问次数不能超过 19 次，$N \le 1000$，可以想到二进制拆分。

于是我们对每个二进制位，询问这一位为 1 的数，若为 1 则说明两个金苹果在这一位上不同，反之同理。这里我们用了 $\lceil \log_2N \rceil$ 次操作。

接下来只需求得一个金苹果的编号，就能求得另一个金苹果的编号。

注意这样一个性质：**两个金苹果编号的二进制表示总有一位不同**。设两个金苹果编号 $x_1,x_2$.

我们找到 $x_1,x_2$ 不同的一位 $w$，令 $x_1$ 在 $w$ 位是 1。再对剩下的二进制位，查询编号在 $w$ 和这一位都为 1 的苹果。

此时，因为 $x_2$ 肯定在另一个集合，所以若结果为 1，则说明 $x_1$ 在这一位是 1，反之，说明 $x_1$ 在这一位是 0。

这里我们用了 $\lceil \log_2N \rceil -1$ 次操作。一共用了 $2\lceil \log_2N \rceil -1 \le 19$ 次操作。

## 代码
```cpp
#include <bits/stdc++.h>
#define N 1005
using namespace std;
int T,n,ed;bool sam[10],w[10];
vector<int> bas[10],tmp;
void query(vector<int> x) {
	int sz=x.size();
	printf("? %d ",sz);
	for(int i=0;i<sz-1;++i) printf("%d ",x[i]);
	printf("%d\n",x[sz-1]);fflush(stdout);
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);ed=log2(n)+1;
		for(int i=0;i<ed;++i) bas[i].clear();
		for(int i=1;i<=n;++i) for(int j=0;j<ed;++j) {
			if((i>>j)&1) bas[j].push_back(i);
		}
		int pos=0;
		for(int i=0,d;i<ed;++i) {
			query(bas[i]);
			scanf("%d",&d);
			sam[i]=d;if(d) pos=i;
		}
		for(int i=0,sz;i<ed;++i) {
			if(i==pos) {w[i]=1;continue;}
			tmp.clear(),sz=bas[pos].size();
			for(int j=0;j<sz;++j) {
				int u=bas[pos][j];
				if((u>>i)&1) tmp.push_back(u);
			}
			if(tmp.empty()) continue;
			query(tmp);
			scanf("%d",&w[i]);
		}
		int res1=0,res2=0;
		for(int i=0;i<ed;++i) {
			res1|=w[i]<<i;
			if(sam[i]^w[i]) res2|=1<<i;
		}
		if(res1>res2) swap(res1,res2);
		printf("! %d %d\n",res1,res2);fflush(stdout);
	}
	return 0;
}
```

---

## 作者：MuelsyseU (赞：2)

考虑一次询问答案为 $1$，意味着得到了两个集合，其中各有一个金苹果。则可以在两个集合内分别二分询问左半区间，如果答案仍为 $1$ 意味着该区间一定有一个金苹果，反之则为另一半，即可将其中一个答案的范围缩小。这样就可在 $2\lfloor\log n\rfloor$ 次询问内解决。

但是查询时很可能出现答案为 $0$，即答案可能均在询问集合中，也可能均在其余部分。那么我们同样必须缩小问题的规模来判断，也就是对这两个集合均分为两半，一次性查询所有集合的左半边（即下图的左半部分）。

![](https://cdn.luogu.com.cn/upload/image_hosting/3w77myfk.png)

容易发现这样最多进行 $\lceil\log n\rceil$ 次，就一定会找到一次答案为 $1$ 的询问，即已经将两个金苹果分别划分在两个集合中，总询问次数为 $O(\log n)$

但是问题是这样极限次数为 $3\lfloor\log n\rfloor$ 级别，不能通过。容易发现，二分过程中需要 $2$ 次询问来将规模缩小一半，但划分过程却只需要 $1$ 次。因此考虑预先尽可能缩减二分的两个集合大小。

容易发现，我们划分的过程中，每次划分意味着之前的询问答案始终为 $0$，也就是下图中每次询问，红色和蓝色部分只有其中一个存在答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/ss14us9b.png)

容易发现，实际上答案可能所在的区间**长度**不断缩小，最后两个答案一定恰好分别在划分出的一个区间的两半中。

因此，可以对所划分出的各个区间继续二分（上图 $4$ 个红色部分），即这些区间中恰有一个包含 $1$ 个金苹果，直至答案缩减为一个区间。此时，即可在 $1$ 次操作内将问题缩小一半的规模。只剩一个区间后，套用二分做法即可。

不妨设 $n=2^t$，划分过程查询了 $k$ 次，则会划分出 $2^k$ 个长度为 $2^{t - k}$ 的红色区间，最后在两个这样的区间内二分，则总查询次数为 $k+k+2(t-k)=2t=2\lfloor\log n\rfloor+1<19$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int T, n, sz, num, tp, cnt;
pair<int, int> a[2005], b[2];
inline int query() {
	sz = 0, ++cnt;
	for (int i = 0; i < num; ++i) sz += (a[i].second - a[i].first + 1) / 2;
	printf("? %d ", sz);
	for (int id = 0; id < num; ++id) {
		sz = a[id].second - a[id].first + 1;
		for (int i = a[id].first; i < a[id].first + sz / 2; ++i) printf("%d ", i);
	}
	cout << endl, fflush(stdout), scanf("%d", &tp);
	return tp;
}
inline int check1(int id, int mid) {
	printf("? %d ", mid), ++cnt;
	for (int i = b[id].first; i < b[id].first + mid; ++i) printf("%d ", i);
	cout << endl, fflush(stdout), scanf("%d", &tp);
	return tp;
}
inline int check(int l, int r) {
	sz = 0, ++cnt;
	for (int i = l; i < r; ++i) sz += (a[i].second - a[i].first + 1) / 2;
	printf("? %d ", sz);
	for (int id = l; id < r; ++id) {
		sz = a[id].second - a[id].first + 1;
		for (int i = a[id].first; i < a[id].first + sz / 2; ++i) printf("%d ", i);
	}
	cout << endl, fflush(stdout), scanf("%d", &tp);
	return tp;
}
inline int find1(int id) {
	int mid, l = 0, r = b[id].second - b[id].first + 1;
	while (l + 1 < r) {
		mid = (l + r) >> 1;
		if (check1(id, mid)) r = mid;
		else l = mid;
	}
	return b[id].first + l;
}
inline int find(int l, int r) {
	int mid;
	while (l + 1 < r) {
		mid = (l + r) >> 1;
		if (check(l, mid)) r = mid;
		else l = mid;
	}
	return l;
}
signed main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n), num = 1;
		//找到答案为 1 的集合  
		a[0] = make_pair(1, n);
		while (!query()) {
			tp = num;
			for (int i = 0; i < num; ++i) {
				sz = a[i].second - a[i].first + 1;
				a[tp++] = make_pair(a[i].first, a[i].first + sz / 2 - 1), a[i].first += sz / 2;
			}
			num = tp;
		}
		//缩减至 1 个区间 
		for (int i = 0; i < num; ++i)
			if (a[i].first >= a[i].second) a[i] = make_pair(0, 0);
		sort(a, a + num);
		int l = 0;
		while (a[l].first == 0) ++l;
		int t = find(l, num);
		sz = a[t].second - a[t].first + 1;
		b[1] = make_pair(a[t].first, a[t].first + sz / 2 - 1), b[0] = make_pair(a[t].first + sz / 2, a[t].second);
		//二分
		int s0 = find1(0), s1 = find1(1);
		if (s0 > s1) swap(s0, s1);
		printf("! %d %d\n", s0, s1), fflush(stdout); 
		//cout << cnt << endl;
	}
	return 0;
}
```


---

## 作者：D2T1 (赞：1)

# 题解 P8849 『JROI-7』hibernal

比较简单但巧妙的交互题。

首先我们考虑分出两个集合，使得一个集合里恰好有一个金苹果。现在就需要把所有下标进行若干次分组，使得任意两个不同下标至少在一次分组中在不同的集合里。很容易想到一个做法：枚举二进制位，把某一位为 $0$ 的数和某一位为 $1$ 的数分开。

这样，我们可以通过至多 $10$ 次查询，获取出两个集合，使得一个集合里恰好有一个金苹果。然后就是通过至多 $9$ 次查询找到具体的两个金苹果的下标。

感觉 $9$ 次操作不是很够怎么办？考虑上述操作还带来了什么信息：两个下标每一个二进制位是否相同。所以我们只要确定了其中一个下标，第二个下标也就随之确定了。那么怎么确定呢？

首先，我们随意选定一个两个下标不同的二进制位（设这一位为第 $k$ 位），则两个下标一定有一个在这一位为 $0$，我们要找到这个下标的具体值。执行：

- 设立 $goal[10]$ 表示现在确定这个下标的二进制位数的值，初始全设为 $-1$ 表示未确定，令 $goal[k]=0$。
- 枚举每个非 $k$ 的二进制位 $i$，令 $goal[i]=1$，查询所有可能为第一个下标的值（即对应二进制位与 $goal$ 中值相同的数），令 $goal[i]=$ 查询结果。
- 枚举完后 $goal$ 数组必定能唯一确定一个数，即为答案下标。另一个金苹果的下标也就得出了。

可以发现，在上述过程中查询数至多为 $9$（$k$ 不查询）。

```cpp
/*
    name: 『JROI-7』hibernal
    id:   P8849
    date: 2022/11/17
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n, isd[10], goal[10], dif;

bool judge(int x){
	for(int i = 0; i <= 9; ++ i){
		if(goal[i] != -1 && ((x >> i) & 1) != goal[i]){
			return false;
		}
	}
	return true;
}

int main(){
	scanf("%d", &t);
	while(t--){
		memset(isd, 0, sizeof(isd));
		memset(goal, -1, sizeof(goal));
		scanf("%d", &n);
		if(n == 2){
			puts("! 1 2");
			fflush(stdout);
			continue;
		}
		for(int i = 9; i >= 0; -- i){
			int cnt = 0;
			for(int j = 1; j <= n; ++ j){
				if((j >> i) & 1){
					++ cnt;
				}
			}
			if(cnt != 0 && cnt != n){
				printf("? %d", cnt);
				for(int j = 1; j <= n; ++ j){
					if((j >> i) & 1){
						printf(" %d", j);
					}
				}
				puts("");
				fflush(stdout);
				scanf("%d", &isd[i]);
				if(isd[i]){
					dif = i;
				}
			}
		}
		goal[dif] = 1;
		for(int i = 9; i >= 0; -- i){
			if(i == dif || (1 << i) > n){
				continue;
			}
			goal[i] = 0;
			int cnt = 0, flg;
			for(int j = 1; j <= n; ++ j){
				if(judge(j)){
					++ cnt;
				}
			}
			if(cnt != 0 && cnt != n){
				printf("? %d", cnt);
				for(int j = 1; j <= n; ++ j){
					if(judge(j)){
						printf(" %d", j);
					}
				}
				puts("");
				fflush(stdout);
				scanf("%d", &flg);
				if(!flg){
					goal[i] = 1;
				}
			}
		}
		int ans1 = 0, ans2 = 0;
		for(int i = 0; i <= 9; ++ i){
			if(goal[i] == -1){
				continue;
			}
			ans1 ^= (1 << i) * goal[i];
			ans2 ^= (1 << i) * (goal[i] ^ isd[i]);
		}
		printf("! %d %d\n", min(ans1, ans2), max(ans1, ans2));
		fflush(stdout);
	}
	return 0;
}

```

---

## 作者：Spouter_27 (赞：1)

考虑一次询问我们能确定什么。

若我们对所有某一二进制位为 $1$ 的数进行一次询问，可得到两个金苹果在这一位上是否相同。 

因为两个不同的数二进制表示至少有一位不同，从低位往高位扫一遍便可以找到任意一位不同的二进制位。我们钦定这一位为 $1$ 的数为 $x$，另一个为 $0$ 数为 $y$。

由于我们已经确定各个二进制位上 $x$ 和 $y$ 是否相同，只要我们能求出 $x$ 的值，$y$ 的值也能被轻松求出。所以接下来的任务就是确定 $x$ 的值。

假设我们已经确定了 $x$ 的某些位是多少，我们要求第 $i$ 位 $x$ 的值。那我们对所有与 $x$ 已经确定的位能匹配上并且第 $i$ 位为 $1$ 的值进行一次询问。因为 $y$ 不可能在我们询问的数中，所以若答案为 $1$，说明 $x$ 的第 $i$ 位也是 $1$ ，否则说明 $x$ 的第 $i$ 位为 $0$。

分析一下询问次数：$2^{10}-1=1023>1000$，所以 $x,y$ 的二进制位数不超过 $10$. 我们需要最多 $10$ 次询问确定 $x,y$ 在不同二进制位的关系，还需要最多 $9$ 次询问确定除去我们钦定的位，其他二进制位上 $x$ 的值。总询问次数 $19$ 次，可以通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const ll N=15;
ll n,a[N],x[N],y[N],sum,T,tmp; 
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		ll d;
		memset(a,0,sizeof(a));
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
		for(int i=0;(1<<i)<=n;i++){
			vector<ll> v;
			for(int j=1;j<=n;j++){
				if(j&(1<<i)){
					v.push_back(j);
				}
			}
			cout<<"? "<<v.size()<<" ";
			for(int j=0;j<v.size();j++){
				cout<<v[j]<<" ";
			}
			cout<<endl;
			cin>>tmp;
			if(tmp==1){
				a[i]=1;d=i;
			}
			cout<<flush;
		}
		x[d]=0,y[d]=1;
		for(int i=0;(1<<i)<=n;i++){
			if(i==d)	continue;
			vector<int> v;
			for(int j=1;j<=n;j++){
				ll flag=1;
				if(!(j&(1<<i)))	continue;
				if(j&(1<<d))	continue;
				for(int k=0;k<i;k++){
					if((j&(1<<k))!=(1<<k)*x[k])	flag=0;
				}
				if(flag)	v.push_back(j);
			}
			if(v.size()==0)	break;
			cout<<"? "<<v.size()<<" ";
			for(int j=0;j<v.size();j++){
				cout<<v[j]<<" ";
			} 
			cout<<endl;
			cin>>tmp;
			if(tmp==0){
				x[i]=0;
			}
			else{
				x[i]=1;
			}
			cout<<flush;
		}
		for(int i=0;(1<<i)<=n;i++){
			if(a[i]==1)	y[i]=!x[i];
			else y[i]=x[i];
		}
		sum=0;
		cout<<"! ";
		for(int i=0;(1<<i)<=n;i++){
			if(x[i]==1)	sum+=(1<<i);
		}
		cout<<sum<<" ";sum=0;
		for(int i=0;(1<<i)<=n;i++){
			if(y[i]==1)	sum+=(1<<i);
		}
		cout<<sum<<endl;
		cout<<flush;
	}
	return 0;
}
/*
exSample:

*/
```


---

## 作者：takanashi_mifuru (赞：1)

我们发现，如果我们找到了一个 $1$，那么就可以二分出其中一个苹果的位置，由此二分出另一个苹果的位置。

我们每次挑出编号在二进制位下第 $x$ 位为 $1$ 的数，放进一个集合里，否则放进另一个集合里，把这个拿出去询问，如果回复是 $1$，那就说明两个苹果不在同一集合，即两个苹果的编号的异或值的第 $x$ 位为 $1$，否则说明两个苹果在同一集合，即两个苹果的编号的异或值的第 $x$ 位为 $0$，跑完 $\log n$ 轮后，把这些位数组起来就能得到这两个苹果编号的异或值。

这样跑一次是 $O\left(\log n\right)$ 的，因为两个苹果的位置不相同，所以一定会出现一个 $1$，根据这个 $1$，我们可以二分出其中一个苹果的位置。

你说诶，你二分一个，还得二分另一个，不成 $O\left(3\log n\right)$ 了？

你有了其中一个苹果的位置和他们的异或值，是不是直接就能求出另一个苹果的位置？

做完了，猜 $2\log n$ 次，卡得很紧，很恶心。

---

## 作者：llingy (赞：1)

[可能更好的阅读体验](https://llingy.ml/posts/2364163512/)

第一次在场上做出月赛交互题。

## 题意简述
在一个长为 $n$ 的数列中，有两个特殊数字，你需要找到这两个数的下标，每次你可以向交互库询问一个集合，如果这个集合中恰好有 $1$ 个特殊数字，交互库返回 $1$，否则交互库返回 $0$。$n\le 1000$，最多向交互库询问 $19$ 次。

## 思路
首先，在值域上是做是不方便的，假如每次询问一个前缀区间，那么必然答案在中间一段才会是 $1$，普通的二分和倍增无法很好处理，而三分法又必须满足严格单调。

考虑到 $19\approx 2\log n$，尝试每一位考虑。二进制分组，对于每一位来说，仅询问该位上是 $0$ 的数字，那么如果交互库返回 $0$，则说明两个数在该位上相同，否则说明两个数在该位上不同。两个数的二进制表示至少有一位是不同的，记不同的位中最高的那位是第 $c$ 位。

记两个数较小的下标为 $x$，较大的下标为 $y$，则 $x$ 的第 $c$ 位必然为 $0$，$y$ 的第 $c$ 位必然为 $1$。现在我们要确定其它位上的值。我们知道两个数在每位上是否相同，所以只需知道一个数即可知道另一个数，此处以 $x$ 为例。对于不是 $c$ 的每个二进制位，仅询问第 $c$ 为上是 $0$ 且这一位上也是 $0$ 的数。$y$ 必然不在这个集合内，所以当返回 $1$ 时，$x$ 这一位是 $0$，否则这一位是 $1$。

记 $k$ 为 $n$ 的二进制数位个数，则需询问 $2k-1$ 次，当 $n=1000$ 时，$k=10$，恰好 $19$ 次。

## Code
注意不能询问大小为 $n$ 和大小为 $0$ 的集合，需要特判，此时答案为 $0$。
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
namespace lly
{
ㅤㅤconstexpr int N=1005;
ㅤㅤint s[N],t=0;
ㅤㅤint choose[N],n;
ㅤㅤinline int ask()
ㅤㅤ{
ㅤㅤㅤㅤif(t==0||t==n) return 0;
ㅤㅤㅤㅤcout<<"? "<<t<<" ";
ㅤㅤㅤㅤfor(int i=1;i<=t;i++) cout<<s[i]<<" ";
ㅤㅤㅤㅤcout<<"\n";
ㅤㅤㅤㅤcout.flush();
ㅤㅤㅤㅤint x;cin>>x;
ㅤㅤㅤㅤreturn x;
ㅤㅤ}
ㅤㅤinline void put(int x,int y)
ㅤㅤ{
ㅤㅤㅤㅤcout<<"! "<<x<<" "<<y<<"\n";
ㅤㅤㅤㅤcout.flush();
ㅤㅤ}
ㅤㅤinline void solve()
ㅤㅤ{
ㅤㅤㅤㅤcin>>n;
ㅤㅤㅤㅤint d=__lg(n);
ㅤㅤㅤㅤmemset(choose,0,sizeof(choose));
ㅤㅤㅤㅤfor(int i=0;i<=d;i++)
ㅤㅤㅤㅤ{
ㅤㅤㅤㅤㅤㅤt=0;
ㅤㅤㅤㅤㅤㅤfor(int j=1;j<=n;j++)if(j&(1<<i))s[++t]=j;
ㅤㅤㅤㅤㅤㅤchoose[i]=ask();
ㅤㅤㅤㅤ}
ㅤㅤㅤㅤint c;
ㅤㅤㅤㅤfor(int i=d;i>=0;i--)if(choose[i]){c=i;break;}
ㅤㅤㅤㅤint x=0,y=0;
ㅤㅤㅤㅤy|=(1<<c);
ㅤㅤㅤㅤfor(int i=d;i>=0;i--)
ㅤㅤㅤㅤ{
ㅤㅤㅤㅤㅤㅤif(i==c)continue;
ㅤㅤㅤㅤㅤㅤt=0;
ㅤㅤㅤㅤㅤㅤfor(int j=1;j<=n;j++) if((j&(1<<i))==0&&(j&(1<<c))==0)s[++t]=j;
ㅤㅤㅤㅤㅤㅤint z=ask();
ㅤㅤㅤㅤㅤㅤif(choose[i]){if(z)y|=1<<i;else x|=1<<i;}
ㅤㅤㅤㅤㅤㅤelse{if(!z)x|=1<<i,y|=1<<i;}
ㅤㅤㅤㅤ}
ㅤㅤㅤㅤput(x,y);
ㅤㅤ}
ㅤㅤinline void work()
ㅤㅤ{
ㅤㅤㅤㅤios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
ㅤㅤㅤㅤint T;cin>>T;
ㅤㅤㅤㅤwhile(T--) solve();
ㅤㅤ}
}
int main()
{
ㅤㅤlly::work();
ㅤㅤreturn 0;
}
```


---

## 作者：gyyyyx (赞：0)

妙啊~

[题面](https://www.luogu.com.cn/problem/P8849)

首先交互题先看限制的交互次数和数据范围。

$19$ 次，$n\leq 1000$，明示 $2\log_2n-1$。

带 $\log$，题目中又有查找的，容易联想到二分。

但这题二分显然不可行。

想到可以按二进制位来询问。

具体的，我们可以先进行 $\log_2n$ 次操作，第 $i$ 次将 $[1,n]$ 中**第 $i$ 位不同**的数放入不同的集合。

也就是 $n=5$ 时会这样询问：

```
? 4 1 3 5
? 2 2 3
? 2 4 5
```

设金苹果编号分别为 $a,b$，这样操作完后就可以知道 $a\oplus b$ 的值（每一位中**相同为 $0$，不同为 $1$**）。

之后我们发现因为 $a,b$ 不同，因此二进制中一定**至少有一位不同**。

我们找到这一位 $w$（其实就是任意找一位使 $a,b$ 的这一位不同），那么将苹果分成两组，两组肯定**分别**包含两个金苹果。

我们可以在某一组中按二进制一位一位的枚举，也是就第 $i$ 次将 这一组中**第 $i$ 位不同**的数放入不同的集合（其实是和之前一样的操作，不过多了一步分组）。

但这样的话最坏情况会询问 $2\lceil\log_21000\rceil=20$ 次。

我们已经知道第 $w$ 位一定不同，那么枚举到第 $w$ 位的时候可以跳过，也就是次数少了一次，也就能过了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,res,w,ans;
vector <int> vec;
inline void ASK(int &x){
	printf("? %d",vec.size());fflush(stdout);
	for(int j(0);j<vec.size();++j) printf(" %d",vec[j]);puts("");fflush(stdout);
	scanf("%d",&x);fflush(stdout);
}
int main(){
	scanf("%d",&T);fflush(stdout);
	while(T--){
		scanf("%d",&n);fflush(stdout);
		res=0;for(int i(0),x;i<10;++i){
			for(int j(1);j<=n;++j) if(j>>i&1) vec.push_back(j);
			if(!vec.size())break;ASK(x);res|=x<<i;if(x)w=i;vec.clear();
		}
		ans=1<<w;for(int i(0),x;i<10;++i){
			if(!(i^w)) continue;
			for(int j(1);j<=n;++j) if((j>>w)&(j>>i)&1) vec.push_back(j);
			if(!vec.size())break;ASK(x);ans|=x<<i;vec.clear();
		}ans=min(ans,ans^res);
		printf("! %d %d\n",ans,ans^res);fflush(stdout);
	}
	return 0;
}
```

完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：Echoternity (赞：0)

因为考虑到有 $n\leq 1000$ 的话，还明确规定了 $19$ 次，我们可以很容易发现 $2^{10}=1024$，那我们大胆猜测这道题可以在 $2\log_2 n$ 的时间内解决，就往位运算或者二分那个方面想。

对于主题库那道题得到两个集合的异或以及 $\text{CodeForces}$ 上得到一个集合里的异或，实际上求得的都是同一个东西——两个特殊点是否**同时**在你选取的集合中。这是显然的，可以自证。

那么我们考虑二分，查找 $[1,\frac{n}{2}],[1,\frac{n}{2^2}],\cdots,[1,\frac{n}{2^r}]$，这样可以得到其中一个点所在的位置，然后把整个序列划分成两部分分别二分，这样的话，时间复杂度是不会超过 $2\log_2 n$ 的。

具体来讲，是如下操作：

我们钦定一个二进制位 $r$ （从 $n$ 的最高位向下枚举），然后每一次把 $x \operatorname{and} 2^r=1$ 的 $x$ 都提出来组成集合（即二进制位 $r$ 为 $1$ 的所有数），直到找到某一位 $r$ 使得两个特殊点不在同一个集合里，从这一位开始，我们可以二分得到集合答案。

我们先枚举左集合得到第一个特殊点记作 $resf$，也就是二分 $[0,2^r-1]$ 区间，这是左集合的答案，用同样的方法得到右集合答案，二分 $[2^r,2^{r+1}-1]$ 区间，得到第二个特殊点记为 $ress$。

现在我们的情况是，用了 $\mathcal O(\log_2 n)$ 的时间获得了 $resf,ress$ 在 $r$ 位以下的答案，现在考虑向上推进。注意到，我们每一次向上推一位，都会得到两个相同的答案记作 $resf',ress'$，他们与原答案的不同在于 $r+1$ 位的不同，这样的话，我们需要在这两者中判断，这是简单的，直接询问某一个，得到信息，如果是，则当前的 $resf,ress$ 就是答案，否则 $resf+2^{r+1},ress+2^{r+1}$ **可能**是答案，并向 $r+2$ 位推进。

两道题的思路是一样的。

``` c++
// ----- Eternally question-----
// Problem: P8849 『JROI-7』hibernal
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8849
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by: Eternity
// Time: 2022-11-12 15:47:21
// ----- Endless solution-------

#include<bits/stdc++.h>
#define re register
typedef long long ll;
template<class T>
inline void read(T &x)
{
	x=0;
	char ch=getchar(),t=0;
	while(ch<'0'||ch>'9') t|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	if(t) x=-x;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1){ read(x),read(x1...); }
template<class T>
inline void write(T x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
template<>
inline void write(bool x){ std::cout<<x; }
template<>
inline void write(char c){ putchar(c); }
template<>
inline void write(char *s){ while(*s!='\0') putchar(*s++); }
template<>
inline void write(const char *s){ while(*s!='\0') putchar(*s++); }
template<class T,class ...T1>
inline void write(T x,T1 ...x1){ write(x),write(x1...); }
template<class T>
inline bool checkMax(T &x,T y){ return x<y?x=y,1:0; }
template<class T>
inline bool checkMin(T &x,T y){ return x>y?x=y,1:0; }
const int MAXN=(1<<10)+10;
int Test,N,Cnt;
inline bool ask(std::vector<int>vec)
{
	if(vec.empty()||(int)vec.size()==N) return 0;
	if(++Cnt>19) assert(0);
	std::cout<<"? "<<vec.size()<<' ';
	for(int x:vec) std::cout<<x<<' ';
	std::cout<<std::endl;
	int type;
	std::cin>>type;
	return type;
}
int main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
	std::cout.tie(0)->sync_with_stdio(false),std::cin.tie(0);
	read(Test);
	while(Test--)
	{
		read(N);
		int l=std::log2(N),r,type;
		Cnt=0;
		for(r=l;r>=0;--r)
		{
			std::vector<int>vec;
			for(int i=1;i<=N;++i)
				if(i&(1<<r)) vec.push_back(i);
			if(ask(vec)) break;
		}
		// std::cout<<r<<'\n';
		int ql=0,qr=(1<<r)-1,ress;
		while(ql<qr)
		{
			int mid=(ql+qr)>>1;
			std::vector<int>vec;
			for (int i=1;i<=N;++i)
				if((i&((1<<(r+1))-1))>=ql&&(i&((1<<(r+1))-1))<=mid) vec.push_back(i);
			if(ask(vec)) qr=mid;
			else ql=mid+1;
		}
		ress=ql;
		// std::cout<<"Done "<<ress<<'\n';
		ql=(1<<r),qr=(1<<(r+1))-1;int resf;
		while(ql<qr)
		{
			int mid=(ql+qr)>>1;
			std::vector<int>vec;
			for(int i=1;i<=N;++i)
				if((i&((1<<(r+1))-1))>=ql&&(i&((1<<(r+1))-1))<=mid) vec.push_back(i);
			if(ask(vec)) qr=mid;
			else ql=mid+1;
		}
		resf=ql;
		// puts("done");
		// std::cout<<ress<<' '<<resf<<std::endl;
		for(r=r+1;r<=l;++r)
		{
			std::cout<<"? 1 "<<ress<<std::endl;
			std::cin>>type;
			if(!type) ress+=(1<<r),resf+=(1<<r);
			else break;
		}
		std::cout<<"! "<<ress<<" "<<resf<<std::endl;
	}
	return 0;
}
/*

*/
```

---

## 作者：cyffff (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8849)
## 题意
$n$ 个物品，每个物品有编号，有且仅有两个特殊物品。每次询问你可以将物品划分为两堆，交互库会告诉你两堆里特殊物品的数量的乘积。

你需要用不超过 $19$ 次询问求出这两个特殊物品的编号。多组数据。

$n\le1000$，$T\le200$
## 思路
不同于官方题解的做法。

设答案为 $x,y$。

考虑对于每一位 $i$，将编号第 $i$ 位为 $0$ 的放到 $S_0$，其余放到 $S_1$，查询 $S_0,S_1$，可以得到 $x,y$ 这一位是否相同。换个说法，我们通过 $\log n$ 次询问得到了 $x\text{ xor }y$。

指定一位 $w$，$x,y$ 在第 $w$ 位不同，不妨指定 $x$ 第 $w$ 位为 $1$。对于每一位 $i\ne w$，把编号第 $i$ 位为 $1$ 且第 $w$ 位为 $1$ 的放到 $S_0$，其余放到 $S_1$，查询 $S_0,S_1$。通过这次询问，我们可以求出 $x$ 这一位是否为 $1$，回答为 $0$ 时，$x$ 在 $S_1$ 中，说明其第 $i$ 位为 $0$，反之同理。这里有 $\log n-1$ 次询问。

综上，我们通过 $2\log n-1$ 次询问求出了 $x$ 和 $x\text{ xor }y$，输出时要注意 $x<y$。

时间复杂度 $O(Tn\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e3+10;
inline int query(vector<int>qry){
	printf("? %d ",qry.size());
	for(auto k:qry)
		printf("%d ",k);
	puts("");
	fflush(stdout);
	int x;
	scanf("%d",&x);
	return x;
}
int T;
int main(){
	scanf("%d",&T);
	while(T--){
		int n,xt=0,p,x=0;
		scanf("%d",&n);
		for(int i=0;(1<<i)<=n;i++){
			vector<int>a;
			a.clear();
			for(int j=1;j<=n;j++)
				if(j&(1<<i))
					a.push_back(j);
			if(!a.size()||a.size()==n) continue;
			int tmp=query(a);
			if(tmp) xt|=1<<i,p=i;
		}
		x|=1<<p;
		for(int i=0;(1<<i)<=n;i++){
			if(i==p) continue;
			vector<int>a;
			a.clear();
			for(int j=1;j<=n;j++)
				if((j&(1<<i))&&(j&(1<<p)))
					a.push_back(j);
			int tmp;
			if(!a.size()||a.size()==n) tmp=0;
			else tmp=query(a);
			x|=tmp<<i;
		}
		if((xt^x)<x) x=xt^x;
		printf("! %d %d\n",x,xt^x);
		fflush(stdout);
	}
	flush();
}
```
再见 qwq~

---

