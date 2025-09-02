# 觅光 | Searching for Hope (hard ver.)

## 题目背景

**这是本题的困难版本。两个版本在 $\bm{100 \%}$ 数据范围的唯一区别是关于 $\bm{n}$ 的限制。此版本中 $\bm{n \le {10}^6}$。**

---

有梦中所向往的地方，也有现实中可望不可触及的远方。

我们正等待无数次的希望，新的纪元，生命不曾奏响终章。

顷刻间颠覆中的一切，天空坠落到海底，死死卡住呼吸者的全部。羽翼裹满刺骨的海水，悲伤到从此遗忘呼吸的意义。

明明与空气只隔着毫厘，却不想再尝试去呼吸。我开始明白，悲伤到了极点，也许不会流泪

神明借着生的名义，捏造出灰暗的真理。



泪水模糊眼眶，身躯坠进天空，泛白的天光，不得已照亮这一日的希望。

## 题目描述

现在有一棵 $n$ 个节点的有根二叉树。

凡人与神明在这棵树上进行一个游戏。凡人需要从根投下若干个球，每个球带 $1$ 单位正电荷或带 $1$ 单位负电荷。

树上每一个点有容量，第 $i$ 个点可以容纳 $c_i$ 个球。初始每一个点容纳的球数为 $0$。我们称一个点被充满当且仅当它容纳的球的个数等于它的容量。

每一次一个球下落到一个点时：

- 如果该点没有孩子节点或者所有孩子节点上都已经充满球，则停止，该点容纳的球的个数 $+1$；
- 如果该点恰有一个孩子节点未充满，则向那个孩子下落；
- 如果有 $2$ 个孩子节点均未充满：
	- 如果左侧子树中所有球的电荷代数和大于右侧子树所有球的电荷代数和，则如果当前球带正电则向右下落，否则向左下落；
   - 如果左侧子树中所有球的电荷代数和小于右侧子树所有球的电荷代数和，则如果当前球带正电则向左下落，否则向右下落；
   - 如果左侧子树中所有球的电荷代数和等于右侧子树所有球的电荷代数和，则由神明决定向哪个方向下落。

其中，电荷代数和指的是正电荷的数量减去负电荷的数量。

在游戏开始前，双方约定目标点 $u$。在一个回合中，凡人选择这次投下的球的电性，神明按上述规则控制球的下落过程。当 $u$ 被充满时，游戏结束。

凡人希望游戏回合数尽量少，神明希望游戏回合数尽量多。假设双方足够聪明。

对所有：$1\leq u\leq n$，求游戏轮数 $r_u$。

## 说明/提示

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n \le$ | 分值 |
| :----------: | :----------: | :----------: |
| 4 | ${10}^5$ | 33 |
| 5 | ${10}^6$ | 67 |

对于 $100\%$ 的数据，$2 \le n \le {10}^6$，满足树是以 $1$ 为根的二叉树，$1 \le f_i < i$，$1 \le c_i \le {10}^{12}$。

---

**【提示】**

本题最大 I/O 量达到 20 MiB，请注意 I/O 效率。

## 样例 #1

### 输入

```
5
1 1 2 2
1 1 1 1 1
```

### 输出

```
5 4 2 3 3```

# 题解

## 作者：Sol1 (赞：17)

[算法 1-3](https://www.luogu.com.cn/blog/CFA-44/search-for-hope-easy-solution)

## 算法 4

使用启发式合并快速计算，对每一个点维护所有子树内的点当前的答案。

然后每次合并，小的子树全部 $\times 2$（暴力），大的子树部分 $\times 2$（暴力）部分整体加（打 tag），set 暴力实现为 $O(n\log^2n)$，期望得分 33。

## 算法 5

（感谢 E_Space 神仙！）

回到算法 3，考虑直接优化这个递推过程。

注意到，对于 $u$，如果 $f_u$ 的另一个子树（设为 $v$）满了，且 $f_{f_u}$ 的另一个子树（设为 $w$）的大小小于 $v$ 子树大小的两倍，则 $w$ 一定满了。于是我们可以把 $v$ 和 $w$ 缩起来。

具体来说，我们维护一棵辅助树 $T'$（记原树为 $T$），树上每一个点有一个二元组 $(l,s)$，代表触发这个点的另一个子树填满至少需要 $l$ 的大小，触发以后填满的所有子树大小总和为 $s$，将它向上第一个无法触发填满的点设为它在 $T'$ 上的父亲。

计算答案时，如果不能触发，则加倍，在 $T$ 上向上跳；否则在 $T'$ 上向上跳。考虑到每在 $T$ 上跳一次答案加倍，每在 $T'$ 上跳一次所在子树大小加倍，于是总复杂度 $O(n\log nc)$，期望得分 100。

---

## 作者：ღꦿ࿐ (赞：5)

因为这里是 1C 的题解不是 2C 的题解，所以就不在叙述博弈的策略与方法了，继续摆出 1C 的结论： 一直向树的上方跳，令目前的答案为 $x$，另一棵子树的大小是 $a$， 则 $x\gets x+\min\{x,a\}$。

考虑使用数据结构优化这个过程。

---
### $O(n\log n\log |V|)$ 

将 $\min $ 分开， $x \gets 2x (x < a) \ , \ x\gets x+a(x\geq a)$，发现前面那种情况 $x$ 会倍增，所以最多发生 $\log V$ 次，需要特殊处理，其它都是直接加上。 

dfs 整棵树的时候用数据结构维护这个操作序列：

$a_1\dots a_n$， 我们需要找到第一个下标 $p>i$ 满足 
$$ (x+\sum_{j=i+1}^{p-1} a_j) < a_p$$

即 
$$a_p-\sum_{j=1}^{p-1} a_j> x-\sum_{j=1}^i a_j$$ 

使用线段树维护左边的值，需要支持区间加，二分。

可以在线段树上二分单次 $O(\log n)$ 解决，总复杂度是 $O(n\log n\log |V|)$，可以过 $10^5$。 

线段树可以维护 “区间加，区间最值”，也可以维护“单点修改，前缀和最值” 。

基于后一种可并的信息 ， 可以用倍增维护向上 $2^k$ 跳层中不会触发翻倍的最大值，可以做到小常数的 $O(n\log n\log |V|)$，场上很多人都卡过去了 $10^6$。


---

### $O(n\log |V|)$ 

跳 $\log$ 次的复杂度是扔不掉了，考虑优化跳的过程：

倍增时很多路径段本身是整体的 ，但是被拆成了很多个路径段，每个路径都被拆成了 $\log$ 个，是不优秀的，考虑把这个跳的整段性展现出来，用一种类似并查集路径压缩的思想 ：

最初每个点的父亲是自己，如果它一定不会触发父亲的翻倍就把它和父亲压缩到一起，这样每一步都会跳到某段较长的一定不会触发翻倍的段的顶端。

具体实现： 

对于每个点维护这个不触发倍增较长段的阈值 $l$，顶端 $t$，跳到顶端后需要加的值 $a$，加入一个新的点后，如果 $l+a\geq l_t$，也就是说不触发这个段一定就不会触发上面的段，所以直接连向它上面段的断顶，继续直到段顶满足 $l+a < l_t$。

每经过一个这样的段， $l$ 的值至少翻倍（$l+a\geq2l$），所以最多经过 $\log |V|$ 个这样的段，直接跳就行了，复杂度 $O(n\log |V|)$。

---


部分代码：

```cpp

struct element {
    int limit , addtion , target ;
};  
vector< element >  Q ; 
void dfs(int x) {
    if(!x) return ; 
    int p = (int) Q.size( ) - 1 ;
    ans[x] = siz[x] ; 
    int cnt = 0 ; 
    while(p > 0) {
        auto [limit,addtion,target] = Q[p] ; 
            ++cnt ; 
        if(ans[x] >= limit) {
            ans[x] += addtion ;
            p = target ;
            continue; 
        }
        ans[x] <<= 1; 
        p -- ; 
    }
    if(son[x][0])    
    {
        if(son[x][1]) {
        auto nw = (element) {siz[son[x][1]],siz[son[x][1]],(int) Q.size( ) - 1} ;
        while(nw.limit+nw.addtion >= Q[nw.target].limit) nw.addtion += Q[nw.target].addtion , nw.target = Q[nw.target].target ;
        Q.push_back(nw);    
        }
        dfs(son[x][0]) ; 
        if(son[x][1]) Q.pop_back ( ) ;
    }
    if(son[x][1]) {
        if(son[x][0]) {
        auto nw = (element) {siz[son[x][0]],siz[son[x][0]],(int) Q.size( ) - 1} ;
        while(nw.limit+nw.addtion >= Q[nw.target].limit) nw.addtion += Q[nw.target].addtion , nw.target = Q[nw.target].target ;
        Q.push_back(nw);
        }
        dfs(son[x][1]) ; 
        if(son[x][0]) Q.pop_back ( ) ; 
    }    
}
```


--- 


于 1 月 25 日排在最优解第二。

[完整代码](https://www.luogu.com.cn/paste/ugievsew)


收录于[《超级无敌神仙炫酷无敌原神大王好题》](https://dreamerkk.blog.luogu.org/good-probs) 。



---

## 作者：Wuyanru (赞：2)

一个有趣题，看了题解不会证复杂度，结果被教练搞出另一个做法。

题目链接：[hard ver.](https://www.luogu.com.cn/problem/P8968)。

## 题意

现在有棵 $ n $ 个节点的有根二叉树，第 $ i $ 个点有一个容量 $ c_i $。两个人 A 和 B 在上面做游戏。

A 每一次会从这棵树的根（$ 1 $ 号点）上投下一个球，每一个球都带一单位正电荷或负电荷。

每当一颗球下落到一个点时：

1. 若该点左右两棵子树都满了，则这颗球停留在这个节点；
2. 否则这个子树恰有一棵子树未满，则这颗球向那棵子树移动；
3. 若两棵次数的电荷代数和不等，则按照电荷吸引规则移动；
4. 否则由 B 选择移动方向。

若一个点 $ u $ 被填满，则游戏结束。

A 想要投下小球个数尽可能少，B 想要尽可能多。

两个人都绝对聪明，对于每一个 $ u=1\sim n $，输出最终的游戏局数。

$ 1\le c_i\le 10^{12} $。

$ 1\le n\le 10^6 $。

## 题解

### easy ver.

通常遇到这种题，我们需要先寻找两个人的最优决策。

首先我们发现，若在某一时刻轮到 B 决策小球走向，那么 B 一定会让小球走到离点 $ u $ 即可能远的那棵子树。

而 A 在选择电荷的时候，一定是尽可能减少 B 的决策（因为让 B 决策对 A 来说一定不会更优）。

所以可以得到结论，A 的最优决策之一，是一直投正电荷；B 的最优决策，是一直将小球向离目标更远的地方放。

知道两人的决策，我们再来想如何统计答案。

对于点 $ u $，我们想要知道的是，多少个球投下之后，点 $ u $ 这个子树内共被投进 $ siz_u $ 个球。

当 $ u=1 $ 时，答案显然，所以我们设 $ p=fa_u $，$ v $ 为 $ p $ 的另一个儿子。

容易发现，当第一个小球进入子树 $ p $ 时，B 一定会让这个小球到 $ v $；第二个小球一定会到 $ u $，以此类推。

小球的去向会在 $ v,u $ 两棵子树内交替，直到 $ u $ 子树内有 $ siz_u $ 个小球或 $ v $ 子树已经被填满。

那么这个问题就转化成：多少个球投下之后，$ p $ 这个子树内共被投进 $ \min(2siz_u,siz_u+siz_v) $ 个球。

容易发现，这些问题都是：多少个球投下之后，点 $ nod $ 这个子树内共有 $ num $ 个球的形式。

而这个问题容易以如上递归的形式，在 $ O(n) $ 的复杂度内被解决。

具体的，设当前我们需要 $ x $ 个小球，当前子树兄弟的 $ siz $ 为 $ a $，则令 $ x\gets x+\min(x,a) $ 即可。

所以我们这样就可以做到 $ O(n^2) $ 的复杂度，并通过 easy ver.。

### hard ver.

首先使用平衡树进行启发式合并可以~~很复杂地~~做到 $ O(n\log ^2n) $ 的复杂度，这里就不仔细说了。

重新观察上面的式子：$ x\gets x+\min(x,a) $。

不难发现这样一些规律：

1. 如果有 $ a\ge x $，那么 $ x\gets 2x $，这样 $ x $ 就会翻倍，这种情况做多会出现 $ \log na $ 次；
2. 如果有 $ a<x$，那么 $ x\gets x+a $，如果有多个 $ a $ 都满足条件，那么他们可以快速计算贡献。

使用 $ st_{i,j} $ 表示，$ i $ 点的所有祖宗中，最深的，满足兄弟的 $ siz\ge 2^j $ 的是哪一个祖宗（不存在则为 $ 1 $）。

当我们计算 $ p $ 点中需要有 $ x $ 个球的答案时：

1. 若 $ p $ 的兄弟的 $ siz\ge x $，则 $ x\gets 2x ,p\gets f_p$；

2. 否则 $ v\gets \left\lfloor\log_2x\right\rfloor $，取 $ p'=st_{p,v} $，我们可以快速计算 $ p\sim p' $ 这一段贡献。

   并且我们发现 $ p' $ 兄弟的 $ siz$（设为 $ S $）有：$ S>2^v $。

   令 $ x\gets x+pre_p-pre_{p'},p\gets p' $ 即可。

   其中 $ pre_p $ 表示 $ pre_{f_p}+p $ 的兄弟的 $ siz $，即兄弟 $ siz $ 的祖先和。

   而我们下一步会令 $ x\gets x+\min(x,S)\ge x+\dfrac{1}{2}x=\dfrac{3}{2}x $。

所以，每当我们向上跳一次，$ x $ 就会变为原来的至少 $ \dfrac{3}{2} $ 倍。

所以时间复杂度为 $ O(n\log na) $，其中 $ \log $ 的底数为 $ 1.5 $。

## 代码

```c++
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3fll
using namespace std;
using ll=long long;
inline ll lread()
{
	ll s=0,w=1;char ch;
	while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int st[1000001][62];
ll bro[1000001];
ll siz[1000001];
ll pre[1000001];
int f[1000001];
ll c[1000001];
int n;
inline int get(ll val)
{
	int ans=-1;
	for(int i=32;i;i>>=1) if(1ll<<(ans+i)<=val) ans+=i;
	return ans;
}
inline void update(ll &val,int &ans)
{
	while(val>=(1ll<<(ans+1))) ans++;
}
inline ll get(int p)
{
	ll val=siz[p];int w=get(val);
	while(p!=1)
	{
		if(val<=bro[p])
		{
			val*=2,w++,p=f[p];
			continue;
		}
		int &num=st[p][w];
		val+=pre[p]-pre[num];
		p=st[p][w];
		if(val>=bro[p]) val+=bro[p],p=f[p];
		update(val,w);
	}
	return val;
}
int main()
{
	n=lread(),bro[1]=inf;
	for(int i=0;i<=61;i++) st[1][i]=1;
	for(int i=2;i<=n;i++) f[i]=lread();
	for(int i=1;i<=n;i++) c[i]=siz[i]=lread();
	for(int i=n;i;i--) siz[f[i]]+=siz[i];
	for(int i=2;i<=n;i++)
	{
		bro[i]=siz[f[i]]-c[f[i]]-siz[i];
		pre[i]=pre[f[i]]+bro[i];
		for(int j=0;j<=60;j++)
		{
			if(bro[i]<=(1ll<<j)) st[i][j]=st[f[i]][j];
			else st[i][j]=i;
		}
	}
	for(int i=1;i<=n;i++) printf("%lld ",get(i));
	return 0;
}
```

感谢观看！

---

## 作者：yyyyxh (赞：2)

博弈论的部分前人之述备矣，称包含目标点 $u$ 的那颗子树为目标子树，结论就是只要非目标子树容量充足，后手可以至少将一半的球扔到非目标子树里去。而且只要先手只扔正电球就可以达到这个下界。

现在我们考虑数据结构的部分，维护子树内所有点的答案，那么相当于对于一部分值 $\times 2$，一部分值 $+a$。树套树/树上启发式合并都可以 $O(n\log^2n)$ 维护，但比较难写。

注意到对于一个点 $\times 2$ 操作最多有 $O(\log \sum c_i)$ 次，相当于我们每次可以暴力枚举子树中答案最小的若干个数 $\times 2$，剩下的东西打加法 tag。

考虑一种更清新的数据结构可并堆。每次 `pop` 出所有 $\leq a$ 的数，给剩下的数打加法 tag，然后把 `pop` 出来的数 $\times 2$ 塞回去。复杂度依然两个 $\log$。

注意到 $f(x)=x+\min(x,a)$ 关于 $x$ 是单调的，我们对可并堆中所有值进行 $x\leftarrow f(x)$ 不会改变相对大小关系也就不会改变堆的结构。于是我们只需要在堆结构中 `dfs` 出所有 $\leq x$ 的元素，再给堆删去这些元素形成的森林的所有的根打 tag。复杂度 $O(n\log \sum c_i)$，足以通过此题。

```cpp
//read()
const int N=1000003;
typedef long long ll;
int n,rk;
int a[N],ft[N];
bool cnt[N];
ll seq[N],c[N],f[N],tg[N];
int lc[N],rc[N],rt[N];
int ch[N][2],d[N];
void proc(int p,ll v){tg[p]+=v;f[p]+=v;}
void pushdown(int p){
	if(tg[p]){
		if(lc[p]) proc(lc[p],tg[p]);
		if(rc[p]) proc(rc[p],tg[p]);
		tg[p]=0;
	}
}
int merge(int x,int y){
	if(!x||!y) return x|y;
	if(f[x]>f[y]) swap(x,y);
	pushdown(x);
	rc[x]=merge(rc[x],y);
	if(d[lc[x]]<d[rc[x]]) swap(lc[x],rc[x]);
	d[x]=d[rc[x]]+1;
	return x;
}
void upd(int p,ll v){
	if(f[p]<v) f[p]<<=1;
	else return proc(p,v);
	pushdown(p);
	if(lc[p]) upd(lc[p],v);
	if(rc[p]) upd(rc[p],v);
}
void dfs(int u){
	if(ch[u][0]) dfs(ch[u][0]);
	if(ch[u][1]) dfs(ch[u][1]);
	f[u]=(c[u]+=c[ch[u][0]]+c[ch[u][1]]);rt[u]=u;
	if(ch[u][0]){
		upd(rt[ch[u][0]],c[ch[u][1]]);
		rt[u]=merge(rt[u],rt[ch[u][0]]);
	}
	if(ch[u][1]){
		upd(rt[ch[u][1]],c[ch[u][0]]);
		rt[u]=merge(rt[u],rt[ch[u][1]]);
	}
}
void push(int p){
	pushdown(p);
	if(lc[p]) push(lc[p]);
	if(rc[p]) push(rc[p]);
}
int main(){
	n=read();
	for(int i=2;i<=n;++i){
		int p=read();
		if(ch[p][0]) ch[p][1]=i;
		else ch[p][0]=i;
	}
	for(int i=1;i<=n;++i) c[i]=read<ll>();
	dfs(1);push(rt[1]);
	for(int i=1;i<=n;++i) printf("%lld ",f[i]);
	putchar('\n');
	return 0;
}
```

---

## 作者：pigstd (赞：2)

卡 log 题。

显然的暴力是：对于每个点往上跳，维护答案，一开始是他的子树的 $c$ 的和（下称为 $sz$），然后对于每个点，如果它的父亲有两个儿子，就把当前答案 $ans$ 加上 $\min(ans,sz_{\text{另外一个儿子}})$。

$n\log ^2n$ 做法：注意到 $sz_{\text{另外一个儿子}}< ans$ 的情况只会出现 $\log$ 次，因为每出现一次，$ans$ 就会 $\times 2$，用倍增找到第一个比当前 $ans$ 大的，然后暴力跳一次，这样一直下去。

$n\log n\log\log n$ 做法：对于一个点，以及所有可能的当前的 $ans$，能让它乘 $2$ 的祖先最多只有 $\log$ 个，然后暴力维护，暴力二分。没实现过，感觉说不定也能过。

$n\log n$ 做法：考虑以 $2$ 为底分块（$2^i\sim 2^{i+1}-1$ 一块），然后对于当前的 $ans$ 以及它所在的块 $i$，那么所有在第 $i-1$ 块之前的都可以直接加上去，然后找到第一个不在这里的，然后暴力更新答案，这样 $ans$ 所在的块至少 $+1$。

[代码实现](https://www.luogu.com.cn/record/100571553)，需要用一些[小技巧](https://www.luogu.com.cn/blog/pigstd/ka-chang-xiao-ji-qiao)来卡常。

---

## 作者：louisliang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8968)

简要复述 easy ver. 带给我们的信息（因为这是 hard ver.，所以不提供详细证明）：一个关键的结论是我们应当投入相同电荷的小球，这样对方选择的机会最小，显然是对我们有利的。记 $i$ 的答案为 $ans_i$，初始 $ans_i \gets s_i$，然后每一层的另一个节点 $y$ 带来的贡献有 $ans_i \gets ans_i+min(ans_i,s_y)$。

所以每次只有两个操作 $\times 2$ 或加 $s_y$。显然 $\times 2$ 的总操作次数是 $O(n\log V)$ 次的，可以暴力乘，剩下的打 tag。又有 $ans_i<sz_y<ans_j$，则 $2ans_i<ans_j+sz_y$，所以操作后子树内的元素相对顺序是不变的。

具体来说每个节点维护一个小根堆，设一个节点的两个子节点为 $x,y$（$s_x>s_y$）。子树 $y$ 都是 $\times 2$ 直接暴力，子树 $x$ 中将 $>s_y$ 的找出来 $\times 2$，注意这里不能直接 ```pop```，观察到这些数组成一个包含根的连通块，直接暴力从根往下遍历就好了，时间复杂度 $O(n\log V + n\log n)$。

Code：
```cpp
const int N = 1e6 + 10;
int n, rt[N], ls[N], rs[N], dst[N], ch[N][2], fa[N], st[N], nd[N];
long long val[N], laz[N], s[N];
inline void pd(const int &x){
	if(laz[x])
		val[ls[x]] += laz[x], val[rs[x]] += laz[x], laz[ls[x]] += laz[x], laz[rs[x]] += laz[x], laz[x] = 0;
}
inline int merge(int x, int y){
	if(!x || !y)
		return x | y;
	if(val[x] > val[y])
		swap(x, y);
	pd(x);
	rs[x] = merge(rs[x], y);
	if(dst[rs[x]] > dst[ls[x]])
		swap(ls[x], rs[x]);
	dst[x] = dst[rs[x]] + 1;
	return x;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i = 2; i <= n; i++){
		cin >> fa[i];
		if(ch[fa[i]][0])
			ch[fa[i]][1] = i;
		else
			ch[fa[i]][0] = i;
	}
	for(int i = 1; i <= n; i++)
		cin >> s[i];
	for(int i = n; i; i--){
		if(fa[i])
			s[fa[i]] += s[i];
		val[i] = s[i];
		if(s[ch[i][0]] < s[ch[i][1]])
			swap(ch[i][0], ch[i][1]);
		if(!ch[i][1])
			rt[i] = merge(i, rt[ch[i][0]]);
		else{
			st[st[0] = 1] = rt[ch[i][1]];
			while(st[0]){
				int x = st[st[0]--];
				val[x] *= 2;
				pd(x);
				if(ls[x])
					st[++st[0]] = ls[x];
				if(rs[x])
					st[++st[0]] = rs[x];
			}
			if(rt[ch[i][0]])
				st[st[0] = 1] = rt[ch[i][0]];
			nd[nd[0] = 1] = i;
			while(st[0]){
				int x = st[st[0]--];
				if(val[x] < s[ch[i][1]]){
					nd[++nd[0]] = x, val[x] = (val[x] << 1) - s[ch[i][1]];
					pd(x);
					if(ls[x])
						st[++st[0]] = ls[x];
					if(rs[x])
						st[++st[0]] = rs[x];
				}
			}
			val[rt[ch[i][0]]] += s[ch[i][1]], laz[rt[ch[i][0]]] += s[ch[i][1]];
			rt[i] = merge(merge(rt[ch[i][1]], i), rt[ch[i][0]]);
		}
	}
	st[st[0] = 1] = rt[1];
	while(st[0]){
		int x = st[st[0]--];
		pd(x);
		if(ls[x])
			st[++st[0]] = ls[x];
		if(rs[x])
			st[++st[0]] = rs[x];
	}
	for(int i = 1; i <= n; i++)
		cout << val[i] << " ";
}
```

---

