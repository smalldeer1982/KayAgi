# 流星雨 Meteor

## 题目背景

> 星の流れる夜に
星光流动的夜裡\
北風が通りを吹き抜け
北风穿越过街道\
待ち人から便りはなく
所盼之人音讯全无\
明くる日を描くだけ
单单描画翌日之像\
星は願いを乗せて
繁星承载祈愿\
あの空を静かに散り行き
宁静漫步夜空\
——じょん / 初音ミク《メテオ》

题外话：现在你看到的是这个题目修改后的版本，其初始版本不太可做（各种方面），有兴趣的可以看看原先出的 [二维版本](https://www.luogu.com.cn/paste/2074cza5)。

## 题目描述

现在你坐在观星台的监视屏幕前，这是一个 $n\times n$ 的屏幕，这个屏幕的信号转换算法相当老旧，所以不在整像素点上的流星将被暂时忽略直到它出现在整点上。正是流星雨爆发的时候，你调整屏幕使得流星雨像是瀑布一样向正下飞去。

恰好共有 $n$ 颗流星。为了方便，我们给流星依次标号，并以左下角为原点，将屏幕看作平面直角坐标系的第一象限。对第 $i$ 颗流星，有一个一开始能够被监测到的起点，$(x_i,y_i)$（是整点，此时是第 $0$ 时刻）；也有一个平行于 $y$ 轴且向下做匀速直线运动的速度，用 $(v_i,t_i)$ 表示每 $t_i$ 秒运动 $v_i$ 个像素。**此外，我们保证 $x_i=i$**。同时每个流星还有一个权值 $a_i$ 表示它的神秘学参数。

繁星承载着祈愿，但同时彗星在古代被称作灾难的象征，为了提前预知，你找来了魔法师来占卜。你为他锁定了 $Q$ 次观星台的镜头，找出可能的灾厄。镜头拍出的画面是一个会调整大小的矩形。为了让他提前准备，你需要确定他至少要对屏幕上的流星施法几次，这和流星的神秘学参数相关，也就是：

- 在某一时刻 $T_j$，确定当前纵坐标在某个区间内，且落在整点上的流星的权值 $a_i$ 的和；

由于法师过来还需要一会儿，所以允许你把问题离线。

## 说明/提示

以下是数据范围。

| Subtask | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $n,Q\leq 5000$ | $10$ |
| $2$ | 均匀随机生成 $t_i$ | $20$ |
| $3$ | 保证 $T_j$ 均匀随机生成，$a_i=1$ | $25$ |
| $4$ | 无特殊性质；依赖前三个子任务 | $45$ |

对于所有的数据，保证 $n\leq  10^5,Q\leq3\times 10^5 $，且 $0\leq v_i<n$，$1\leq t_i,T_j,l_j,r_j\leq n$，**以及 $v_i,t_i$ 互质**，$1\leq a_i\leq 10^9$。

## 样例 #1

### 输入

```
5 5
4 3 1 10
4 1 1 8
1 1 2 6
5 0 1 8
3 1 2 10
2 1 3
4 4 4
3 1 5
2 1 2
1 3 4
```

### 输出

```
18
0
16
18
8
```

# 题解

## 作者：Comentropy (赞：5)

这里是 [流星雨 Meteor](https://www.luogu.com.cn/problem/T605001?contestId=235738) 的出题人题解。

这道题的部分分就不单独说了，因为正解会有部分能用上。

## 题意

给定一些直线，解析式形如 $y_i=b_i-\dfrac{p_i}{q_i} x$，询问 $x=x_0$ 时，$y_i\in[l,r]\cap\N$ 的直线 $i$ 的权值和。其中 $x_0,l,r,b_i\in[1,n]\cap \N$。

## 分析

题目中保证了 $v_i,t_i$ 互质，也就是直线斜率 $\dfrac{p_i}{q_i}$ 是一个最简分数（这其实是为了方便造数据）。

询问首先可以差分成求前缀和，然后是一个显然的根号分治：

先考虑直线对询问做贡献：斜率分母是 $q_i$ 时，$y_i$ 是整数的位置 $x_0$ 只有 $O(\dfrac{n}{q_i})$ 个。于是我们把 $q_i>\sqrt{n}$ 的部分单独拉出来考虑。满足这个条件的直线都可以直接暴力算出 $q_i$ 的倍数处的值。排一下序，和询问做双指针，就可以 $O(n\sqrt{n})$ 地得到这部分的答案。

以及，类似地，在 $y$ 轴上也有这种限制：如果说斜率分子为 $p_i$，那么其最多过 $\dfrac{b_i}{p_i}$ 轮就会跌出询问区间，于是这一部分也可以像上面一样，单独提出来做。这两部分由于值域不大，使用桶排即可做到时空 $O(n\sqrt{n}+q)$。

随后发现，其它类型的直线难以再应用上面的做法。

考虑某个斜率分母 $q_i$ 剩下的直线对倍数处询问的贡献（也可以看成是把询问拆到因子处）。注意，由于我们上面的两步，现在有很重要的性质：$p_i\leq \sqrt{n}$ 以及 $q_i\leq \sqrt{n}$。后者意味着我们的操作其实可以和值域相关了。（以及单独而不是均摊地与 $Q$ 相关）。以下分析时间的时候，记 $C_i$ 表示斜率分母为 $i$ 处的直线条数，$Q_i$ 表示倍数处的询问个数。

现在我们不用关心斜率分母，可以简单认为直线的斜率就是整数 $-p_j$。

在分母为 $i(1\leq i\leq\sqrt{n})$ 的处理：考虑把 $B_i$ 条直线分为一块，这些直线的交点个数是 $O(B_i^2)$ 的，把它们按横坐标排序，就可以维护它们的相对大小，然后和询问在横坐标上做双指针，询问的时候就可以二分出位置进行查询。维护相对大小的一步，就是在交点处交换其顺序；特别地，对于多线共交点的情况，是一个区间 `reverse`。操作总数和交点总数显然同阶。块内的操作复杂度是：$O(B_i^2+Q_i\log B_i)$。

诶？那交点排序怎么办呢？交点横坐标形如 $x_0=\dfrac{\Delta{b}}{\Delta{k}}$，而其中 $\Delta{k}=p_i-p_j$，是两个 $\leq \sqrt{n}$ 的非负整数的差。那么，把交点化为带分数，其分数部分就只有至多 $O(n)$ 种。纵坐标同理。于是仍然可以使用基数排序做到 $O(n)$（其实已经变成了桶排序）。以下进行复杂度分析：

对于这部分的处理：$O(\dfrac{C_i}{B_i}\cdot (n+B_i^2)+Q_i\cdot \dfrac{C_i}{B_i}\log{B_i})$。值得一提里面的 $O(n)$，你为了不让它成为瓶颈项，可能需要凑够很多数再做基排。而且即使凑不够，由于只会处理 $1\leq i\leq \sqrt{n}$，一共只有根号次，也不会成为瓶颈，可以认为和 $O(B_i^2)$ 同阶，暂时略去。于是式子就是：$O(C_iB_i + Q_i\cdot \dfrac{C_i}{B_i}\log{B_i})$，取 $B_i=\sqrt{Q_i\log{C_i}}$（后面那个 $\log$ 下面 $B_i$ 和 $C_i$ 没区别，所以写成 $C_i$） 就可以取到 $O(C_i\sqrt{Q_i\log{C_i}})$。

然后 $Q_i\approx Q,\sum{C_i}=n$，总复杂度就是 $O(n\sqrt{Q\log{n}})$。但是，实际做的时候，需要权衡各方面的常数（主要是基排常数有点大），所以块长取到 $\sqrt{Q}$ 左右比较优秀。


实现相当优秀的快排做法或许可以通过。轻微卡常，轻喷。

[Code Link](https://www.luogu.com.cn/paste/hu190kan).

---

## 作者：XZhuRen (赞：0)

卡卡卡卡卡卡卡常数。

不是很好想的题，一开始想歪了就很难做出来了。

看到取整点有效，先来个无脑根号分治，阈值 $B$，则问题转化为 $t_i,v_i\le B$ 部分的问题。

一个个确定交点不可取，但是对于 $t_i$ 一定只能枚举，现考虑令更大的线段代替小的，查询大的线段的答案时直接查询了前缀答案。

考虑线段的集合，交点较多，直接对其分块，块长为 $b$，则现在每个集合 $\mathcal{O}(b^2)$ 个交点。

考虑集合不能直接分出，则现在最多有 $\mathcal{O}(\frac{n}{b}+B)$ 个集合，直接维护交点，在相交后重排有关点即可，树状数组维护答案。

分块部分分析可得，但是容易被 $v_i\le B$ 的无用条件误导。

---

关于时间复杂度：

$t,v>B$ 部分基排可做到 $\mathcal{O}(q\sqrt{\frac{n}{B}})$，快速排序则多一个对数。

查询为 $\mathcal{O}(\log n)$。

小的部分：

共 $\mathcal{O}(B+\frac{n}{b})$ 个块，每个块需要动态处理 $\mathcal{O}(b^2)$ 个交点。

处理交点时（离线下来）基数排序则做到 $\mathcal{O}(nb)$，其他排序多一个对数。

查询为 $\mathcal{O}(q(B+\frac{n}{b})\log b)$ 的，复杂度大头在上面。

基数排序做法复杂度为 $\mathcal{O}((n+q)\sqrt{n\log n})$，其他复杂度做法为 $\mathcal{O}((n+q)\sqrt{n}\log n)$，懒人实现了后面的算法，没有用基排。

---

很好的分块题。

某些实现可能需要卡常技巧，这里给一个卡常前的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pri pair<int,ll1>
#define mkp make_pair
typedef long long ll1;
const int N=1e5+5;
const int M=3e5+5;
const ll1 inf=1e16+9;
const int MaxB=1005;
ll1 Ans[M];
int n,q;
vector<pri>brs[N];
int xs[N];ll1 sms[N];
struct Qrys{int l,r,id;};
vector<Qrys>aq[N];
struct lines{int v,t,y;ll1 w;bool operator <(const lines&o)const{return t<o.t;}}lns[N];
int tl=0,B;
void init(){
	scanf("%d%d",&n,&q);
	B=sqrt(4*n);
	for(int i=1,y,v,t,w;i<=n;i++){
		scanf("%d%d%d%d",&y,&v,&t,&w);
		y=n-y+1;
		if(max(t,v)>B)
			for(int nwy=y+v,nwt=t;nwy<=n&&nwt<=n;nwt+=t,nwy+=v)
				brs[nwt].emplace_back(mkp(nwy,w));
		else lns[++tl]=((lines){v,t,y,w});
	}
	for(int t=1;t<=n;t++){
		int tot=0;
		sort(brs[t].begin(),brs[t].end());
		for(auto [x,w]:brs[t]){
			if(xs[tot]!=x){++tot;xs[tot]=x,sms[tot]=0;}
			sms[tot]+=w;
		}
		for(int i=tot-1;i>0;i--)sms[i]+=sms[i+1];
		brs[t].clear();for(int i=1;i<=tot;i++)brs[t].emplace_back(mkp(xs[i],sms[i]));
		brs[t].emplace_back(mkp(n+1,0));
	}
	for(int id=1,T,l,r;id<=q;id++){
		scanf("%d%d%d",&T,&l,&r);
		l=n-l+1,r=n-r+1;swap(l,r);
		Ans[id]+=(lower_bound(brs[T].begin(),brs[T].end(),mkp(l,0ll))->second)-(upper_bound(brs[T].begin(),brs[T].end(),mkp(r,inf))->second);
		aq[T].emplace_back((Qrys){l,r,id});
	}
}
int tot=0;
namespace BIT{
#define lowbit(x) (x&-x)
	ll1 bit[N];
	void clear(){for(int i=1;i<=tot;i++)bit[i]=0;}
	void add(int x,ll1 y){for(;x<=tot;x+=lowbit(x))bit[x]+=y;}
	ll1 qry(int x){ll1 res=0;for(;x>0;x-=lowbit(x))res+=bit[x];return res;}
#undef lowbit
}
namespace block{
	int tb;
	int L[N],R[N];
	int bel[N];
	int Ts[N];
	void build(){
		sort(lns+1,lns+1+tl);
		L[tb=0]=-B;lns[0].t=Ts[0]-1;
		for(int i=1;i<=tl;i++){
			if(L[tb]+B<=i||lns[i].t!=Ts[tb])
				L[++tb]=i,Ts[tb]=lns[i].t;
			R[tb]=i,bel[i]=tb;
		}
	}
	int pos[N],tmp[N],p[N];
	vector<int>pnts[N];
	int stk[N],top=0;
	int poss[N];
	bool cmp(int x,int y){return tmp[x]<tmp[y];}
	bool cmpp(int x,int y){return pos[x]<pos[y];}
	ll1 getans(int x,int y){
		int res=0,l=1,r=tot;
		while(l<=r){
			int mid=(l+r)>>1;
			if(lns[p[mid]].v*x+lns[p[mid]].y<=y)res=mid,l=mid+1;
			else r=mid-1;
		}
		return BIT::qry(res);
	}
	void solve(int o){
		int lim=n/Ts[o]+1;
		tot=R[o]-L[o]+1;
		for(int i=1;i<=lim;i++)pnts[i].clear();
		for(int i=L[o];i<R[o];i++){
			for(int j=i+1;j<=R[o];j++){
				if(lns[i].v==lns[j].v)continue;
				int tx=1+(1.0*(1.0*lns[j].y-lns[i].y)/(lns[i].v-lns[j].v));
				if(tx<2||tx>lim)continue;
				pnts[tx].emplace_back(i),pnts[tx].emplace_back(j);
			}
		}
		for(int i=L[o];i<=R[o];i++){tmp[i]=lns[i].v+lns[i].y;p[i-L[o]+1]=i;}
		sort(p+1,p+1+tot,cmp);//按照初始的纵坐标排序
		BIT::clear();
		for(int i=1;i<=tot;i++){
			pos[p[i]]=i;
			BIT::add(i,lns[p[i]].w);
		}
		for(int nwt=Ts[o],nw=1;nwt<=n;nw++,nwt+=Ts[o]){
			{
				sort(pnts[nw].begin(),pnts[nw].end(),cmpp);
				stk[top=0]=0;
				for(auto x:pnts[nw])if(stk[top]!=x){//去重
					stk[++top]=x;poss[top]=pos[x];
					tmp[x]=lns[x].v*nw+lns[x].y;//重新计算纵坐标
					BIT::add(pos[x],-lns[x].w);
				}
				sort(stk+1,stk+1+top,cmp);
				for(int i=1;i<=top;i++){
					p[poss[i]]=stk[i];
					pos[stk[i]]=poss[i];
					BIT::add(pos[stk[i]],lns[stk[i]].w);
				}
			}
			for(auto [lt,rt,id]:aq[nwt])
				Ans[id]+=getans(nw,rt)-getans(nw,lt-1);
		}
	}
}
void work(){
	block::build();
	for(int o=1;o<=block::tb;o++)block::solve(o);
	for(int id=1;id<=q;id++)printf("%lld\n",Ans[id]);
}
int main(){
	init();
	work();
	return 0;
}

```

---

## 作者：dream10 (赞：0)

## Solution

对于一个流星，会出现在 $(t,y-v),(2t,y-2v)\dots$。

对于一个询问可以拆成两个前缀和询问。

那么简单的思路就是把一个流星拆成很多时刻的流星，然后每个时刻进行计算。

这在 $v > \sqrt{n}$ 或 $t > \sqrt{n}$ 的时候都是不多，复杂度应当是 $O(n\sqrt{n}\log n)$ 左右。

接着就考虑 $v,t\le \sqrt{n}$ 的情况。

对于一个集合，可以维护交点并且在时间增加的时候维护对应顺序，那么在维护 $a$ 的前缀和，那么询问只需要二分即可。集合大小是 $C$ 那么复杂度大概是 $O(C^2 \log (n)+q)$。于是就可以对应分组，每一组做这个东西，那么最多只会做 $\sqrt{n}+n/C$ 组，这样复杂度就是足够快的。

## Code

进行调块长，实验得到 $Bv=Bt=210,B=400$ 比较好。

https://www.luogu.com.cn/record/222122607

## Conclusion

算是很好的根号分治题了吧，我场上只想到根据大小来分治，但是两个 $\sqrt{n}$ 级别的东西相乘还是不够，于是我写下了这个随机化[代码](https://www.luogu.com.cn/record/221682682)。

实际上就是原来每个时刻进行的暴力，和暴力维护交点的暴力拼在一起。

## Reference

基本复述 Comentropy 题解。

---

