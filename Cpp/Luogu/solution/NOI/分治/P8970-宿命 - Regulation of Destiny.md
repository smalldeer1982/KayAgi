# 宿命 | Regulation of Destiny

## 题目背景

压抑是有实质的，从躯壳到内脏，密不透风地包裹，药物仅仅像缝隙里挤进去的一滴水，浇不灭深幽的火焰。

时间治愈不了一切，它只把泥泞日复一日地堆积。她的眼睛没有焦点，偶尔仿佛睡梦中惊醒，喊我的名字。

街道乱糟糟，各家店铺放着音乐，公交车轮胎碾过柏油路，小孩打闹，玻璃瓶砸碎，电瓶车相撞……但我清楚地听见自己的呼吸声。后视镜里，我又一次看到她没有焦点的眼神，裹住眼球的眼泪，水的表面张力“嗒”的一声失效。


撕开雨天，潜入他乡，所向往的尽头是天堂。

浅蓝天光，云层泛紫，微弱的灯光嵌进夕阳。
 
----
 
 
 “…你知道吗，所谓的力量，其实，就是心中的执念。”
 
 “执念？”
 
 “是啊…就是，必须要做的事，必须守护的人，必须…”
 
 “实现的心愿。”
 
 “那么…你心中有这样的执念吗？”
 
 “呃……有啊！我的执念，就是保护姐姐！”
 
 “傻小子，想保护你姐，等下辈子再说吧”
 


## 题目描述

A 国为了防御 B 国的进攻，准备兴建一系列防御措施。

A 国有 $n$ 艘恒星级战舰，这些战舰无论如何都是要被保护的。为了节省材料，总司令用了 $n-1$ 条双向加速通道将这些战舰连接了起来。每个战舰有两个属性 $a_i,b_i$，分别代表战舰的人口数，科技程度。

在每艘战舰上有两种防御措施可以选择。你可以选择建设其中的一种，也可以选择不建设，但不能两种都建设。

在 $i$ 号战舰上建设 I 类防御措施需要 $a_i$ 的金钱，可以保护 $i$ 号战舰本身和与其直接相连的战舰。

在 $i$ 号战舰上建设 II 类防御措施需要 $b_i$ 的金钱，可以保护 $i$ 号战舰本身以及所有与 $i$ 号战舰的距离**恰好**为 $r$ 的战舰。

定义战舰 $u$ 和战舰 $v$ 的距离为从 $u$ 到 $v$ 需要经过最少多少条加速通道。

现在，请你求出保护所有战舰需要的最少金钱。

## 说明/提示

**【样例解释 \#1】**

在 $1$ 号战舰上建设任意一种防御措施，所花金钱为 $1$。

---

**【样例解释 \#2】**

在 $1$ 号战舰上建设 I 类防御措施，所花金钱为 $2$。

---

**【样例解释 \#3】**

在 $1,2$ 号战舰上各建设一个 II 类防御措施，所花金钱为 $2$。

------------

**【数据范围】**

**本题采用捆绑测试且使用子任务依赖。**

| 子任务编号 | $n \le$ | $r \le$ | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| 1 | $10$ | $5$ | 5 |
| 2 | $200$ | $1$ | 5 |
| 3 | $20$ | $7$ | 10 |
| 4 | $100$ | $2$ | 8 |
| 5 | $100$ | $4$ | 11 |
| 6 | $100$ | $5$ | 8 |
| 7 | $200$ | $6$ | 34 |
| 8 | $200$ | $7$ | 19 |

对于 $100\%$ 的数据，$1 \le n \le 200$，$1 \le r \le 7$，$1 \le a_i, b_i \le {10}^9$，$1 \le u, v \le n$，保证任意两艘战舰可以通过若干条加速通道到达。

## 样例 #1

### 输入

```
1 1
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
1 2
1 3
2 1
111111 1111111
3 45
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 2
1 2
1 3
2 4
3 1
2 1
1 1
1 2
```

### 输出

```
2
```

# 题解

## 作者：AC_CSP (赞：18)

### $\text{Part 1}$

首先考虑暴力。预处理每个点之间的距离，然后枚举每个点的三种状态，最后进行判断。这样的时间复杂度是 $\mathcal{O}(n3^n)$。期望得分 $7\text{pts}$。

### $\text{Part 2}$

接着，很容易发现这是一个树形 $\text{DP}$。为了方便我们把它看成一棵有根树。而由于一个点选什么对它的 $r$ 级祖先都是有贡献的，同时 $1\le r\le 7$，所以我们可以考虑加上一个状压 $\text{DP}$。

不妨设 $f(i,S,T)$ 表示以 $i$ 为根的子树有 $S$ 集合的贡献，需要 $T$ 集合的贡献的最小价值。其中 $S,T$ 是两个 $r$ 位二进制数。

我们对当前节点的 $S,T$ 进行枚举，再对当前儿子的 $S,T$ 进行枚举，最后合并为新的 $S,T$。

图中是 $r=3$ 的情况。其中 $x,y$ 表示 $u$ 节点的 $S,T$，$z,w$ 表示 $v$ 节点的 $S,T$，$s,t$ 表示合并出来的 $S,T$。

![](https://cdn.luogu.com.cn/upload/image_hosting/54jns4bf.png)

我们发现，在合并过程中，$v$ 的状态会发生错位现象，所以我们要进行分类讨论。

于是我们可以得到下表：

| $y_1$ | $z_1$ | $s_0t_1$ |
| :----------: | :----------: | :----------: |
| $0$ | $0$ | $00$ |
| $0$ | $1$ | $10$ |
| $1$ | $0$ | $01$ |
| $1$ | $1$ | $10$ |

| $x_3\color{red}w_4$ | $w_3$ | $s_3t_4$ |
| :----------: | :----------: | :----------: |
| $00$ | $0$ | $00$ |
| $00$ | $1$ | $\color{red}{01}$ |
| $10$ | $0$ | $10$ |
| $10$ | $1$ | $10$ |

| $x_iy_{i+1}$ | $z_{i+1}w_i$ | $s_it_{i+1}$ |
| :----------: | :----------: | :----------: |
| $00$ | $00$ | $00$ |
| $00$ | $01$ | $01$ |
| $00$ | $10$ | $10$ |
| $00$ | $11$ | $11$ |
| $01$ | $00$ | $01$ |
| $01$ | $01$ | $01$ |
| $01$ | $10$ | $10$ |
| $01$ | $11$ | $11$ |
| $10$ | $00$ | $10$ |
| $10$ | $01$ | $10$ |
| $10$ | $10$ | $10$ |
| $10$ | $11$ | $10$ |
| $11$ | $00$ | $11$ |
| $11$ | $01$ | $11$ |
| $11$ | $10$ | $10$ |
| $11$ | $11$ | $10$ |

上文中红色的状态是不必要或不合法的。

时间复杂度 $\mathcal{O}(n16^r)$，期望得分 $43\text{pts}$。

如果特判 $r=1$ 的情况，进行 $\mathcal{O}(n)$ 的 $\text{DP}$，可以拿到 $49\text{pts}$。

### $\text{Part 3}$

考虑进行优化。我们现在是枚举两个状态合并为一个状态，不妨枚举一个状态拆为两个状态。这样我们就可以进行预处理。

于是得到下表：

| $y_1$ | $z_1$ | $t_1$ |
| :----------: | :----------: | :----------: |
| $0$ | $0/1$ | $0$ |
| $1$ | $1$ | $0$ |
| $1$ | $0$ | $1$ |

| $x_3$ | $w_3$ | $s_3$ |
| :----------: | :----------: | :----------: |
| $0$ | $0$ | $0$ |
| $1$ | $0/1$ | $1$ |

| $x_iy_{i+1}$ | $z_{i+1}w_i$ | $s_it_{i+1}$ |
| :----------: | :----------: | :----------: |
| $00$ | $00$ | $00$ |
| $01$ | $00/01$ | $01$ |
| $00/01$ | $01$ | $01$ |
| $10$ | $00/01$ | $10$ |
| $00/01$ | $10$ | $10$ |
| $10/11$ | $10/11$ | $10$ |
| $11$ | $00/01$ | $11$ |
| $00/01$ | $11$ | $11$ |

不妨枚举所有的可能性，这样的复杂度是 $\mathcal{O}(n8^r)$ 的，期望得分 $81\text{pts}$。

### $\text{Part 4}$

继续进行优化。我们发现 $01$ 的限制比 $00$ 更加严格，因此将状态合并。

优化前：

| $x_iy_{i+1}$ | $z_{i+1}w_i$ | $s_it_{i+1}$ |
| :----------: | :----------: | :----------: |
| $01$ | $00/01$ | $01$ |
| $00/01$ | $01$ | $01$ |

优化后：

| $x_iy_{i+1}$ | $z_{i+1}w_i$ | $s_it_{i+1}$ |
| :----------: | :----------: | :----------: |
| $00/01$ | $00/01$ | $01$ |

这样的时间复杂度是 $\mathcal{O}(n7^r)$，期望得分 $100\text{pts}$。

### $\text{Code:}$

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(2)
const int N=2e3+7;
const int M=2e3+7;
const int R=7;
const long long LONGLONG_INF=0x3f3f3f3f3f3f3f3f;
constexpr int _7[R+1]={1,7,49,343,2401,16807,117649,823543};
constexpr int _5[R+1]={1,5,25,125,625,3125,15625,78125};
constexpr int _first[7]={0,1,2,1,4,3,1};
constexpr int _second[7]={0,1,1,2,4,1,3};
constexpr int _result[7]={0,1,2,2,2,3,3};
constexpr int __first[6][2]={{0,0},{0,1},{1,0},{1,1},{1,0},{1,1}};
constexpr int __second[6][2]={{2,0},{2,1},{1,0},{1,1},{0,0},{0,1}};
constexpr int __result[6][2]={{0,0},{0,1},{0,0},{0,1},{1,0},{1,1}};
int n,m,r,a[N],b[N];
int _h[N],cnt;
int mp[_7[R-1]*6/*<<1*/][2];int mpdown[_7[R-1]*6/*<<1*/];
int upu[1<<R<<R/*<<1*/];int downu[_5[R-1]*6/*<<1*/];
int upv[1<<R<<R/*<<1*/];int downv[_5[R-1]*6/*<<1*/];
int from[_5[R-1]*6*6/*<<1*/][3];int common[_5[R-1]*6*6/*<<1*/];bool vis[_5[R-1]*6*6/*<<1*/];
int tot,tot2;
long long minu[_5[R-1]*4/*<<1*/],minv[_5[R-1]*6/*<<1*/];
struct edge{
    int nxt,v;
}_e[M<<1];
inline void add_edge(int u,int v){
    _e[++cnt].nxt=_h[u],_e[cnt].v=v;
    _h[u]=cnt;
}
inline long long min(const long long &a,const long long &b){
	return a<b?a:b;
} 
long long f[N][1<<R<<R/*<<1*/],ans=LONGLONG_INF;
inline void init(){
	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<_7[r-1];k++){
				int st=i*_7[r-1]*2+j*_7[r-1]+k;//tmp=10,i=0,j=1,k=3;
				for(int p=0;p<r-1;p++){
					mp[st][0]+=_first[k/_7[p]%7]*_5[p];//+1
					mp[st][1]+=_second[k/_7[p]%7]*_5[p];//+2
				}
				mp[st][0]+=(__first[i*2+j][0]*_5[r-1]*2+__first[i*2+j][1]*_5[r-1]);
				mp[st][1]+=(__second[i*2+j][0]*_5[r-1]*2+__second[i*2+j][1]*_5[r-1]);
			}
		}
	}
	memset(downu,-1,sizeof downu);
	memset(downv,-1,sizeof downv);
	for(int i=0;i<(1<<r<<r);i++){
		for(int j=0;j<r-1;j++){
			int tmp1=(i>>j>>r)&1,tmp2=(i>>j>>1)&1;
			if(tmp1==0&&tmp2==1) upu[i]+=_5[j];
			if(tmp1==1&&tmp2==0) upu[i]+=2*_5[j];
			if(tmp1==1&&tmp2==1) upu[i]+=3*_5[j];
			tmp1=(i>>j>>r>>1)&1,tmp2=(i>>j)&1;
			if(tmp1==0&&tmp2==1) upv[i]+=_5[j];
			if(tmp1==1&&tmp2==0) upv[i]+=2*_5[j];
			if(tmp1==1&&tmp2==1) upv[i]+=3*_5[j];
		}
		upu[i]+=((i<<1>>r>>r)&1)*_5[r-1]+(i&1)*_5[r-1]*2;
		upv[i]+=((i>>r)&1)*_5[r-1]*2+((i<<1>>r)&1)*_5[r-1];
		downu[upu[i]]=i;
		downv[upv[i]]=i;
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<_5[r-1];k++){
				bool flag=0;bool flag2=0;
				int st=i*_5[r-1]*2+j*_5[r-1]+k;
				if(i==2) from[++tot][0]=st,from[tot][1]=st-_5[r-1]*4,from[tot][2]=st-_5[r-1]*2;
				if(j==1) flag2=1;
				for(int p=0;p<r-1;p++){
					//if(from[tot][0]==st&&(k/_5[p]%5==1||k/_5[p]%5==4)) ;
					if(k/_5[p]%5==1) from[++tot][0]=st,from[tot][1]=st-_5[p],from[tot][2]=st,flag=1;
					if(k/_5[p]%5==4) from[++tot][0]=st,from[tot][1]=st-_5[p]-_5[p],from[tot][2]=st-_5[p];
				}
				if(from[tot][0]!=st||flag||(i!=2&&st==0)) common[++tot2]=st;
				if(flag2) vis[st]=1;
			}
		}
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<_7[r-1];k++){
				int st=i*_7[r-1]*2+j*_7[r-1]+k;
				for(int p=0;p<r-1;p++)
					mpdown[st]+=_result[k/_7[p]%7]*_5[p];
				mpdown[st]+=__result[i*2+j][0]*_5[r-1]*2+__result[i*2+j][1]*_5[r-1];
				mpdown[st]=downu[mpdown[st]];
			}
		}
	}
}
inline void first(int u){
    f[u][1]=0;
    f[u][1<<r]=a[u];
    f[u][1<<r>>1<<r]=min(f[u][1<<r>>1<<r],(long long)b[u]);
}
inline void work(int u,int v){
	memset(minu,0x3f,sizeof minu);
	memset(minv,0x3f,sizeof minv);
	for(int i=1;i<=tot2;i++){
		if(~downu[common[i]]) minu[common[i]]=min(minu[common[i]],f[u][downu[common[i]]]);
		if(~downv[common[i]]) minv[common[i]]=min(minv[common[i]],f[v][downv[common[i]]]);
	}
	for(int i=1;i<=tot;i++){
		if(from[i][0]<_5[r-1]*4)			
			minu[from[i][0]]=min(minu[from[i][1]],minu[from[i][2]]);
		minv[from[i][0]]=min(minv[from[i][1]],minv[from[i][2]]);
		if(vis[from[i][0]]) minv[from[i][0]]=min(minv[from[i][0]],minv[from[i][0]-_5[r-1]]);
	}
}
inline void solve(int u,int v){
	memset(f[u],0x3f,sizeof f[u]);
	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<_7[r-1];k++){
				int tmp=i*_7[r-1]*2+j*_7[r-1]+k;
				int st=mpdown[tmp];
				f[u][st]=min(f[u][st],minu[mp[tmp][0]]+minv[mp[tmp][1]]);
				//if(f[u][st]!=LONGLONG_INF)
				//	printf("u:%d tmp:%d upu[st]:%d st:%d f[u][st]:%d mp[tmp][0]:%d mp[tmp][1]:%d minu[mp[tmp][0]]:%d O:%d minv[mp[tmp][1]]:%d O:%d\n",u,tmp,upu[st],st,f[u][st],mp[tmp][0],mp[tmp][1],minu[mp[tmp][0]],downu[mp[tmp][0]],minv[mp[tmp][1]],downv[mp[tmp][1]]);
			}
		}
	} 
}
inline void dfs(int u,int fa){
    first(u);
    for(int ___=_h[u];___;___=_e[___].nxt){
        int v=_e[___].v;if(v==fa) continue;
        dfs(v,u);work(u,v);solve(u,v);
    }
}
inline void answer(){
    for(int i=0;i<(1<<r);i++) if(ans>f[1][i<<r]) ans=f[1][i<<r];
    printf("%lld\n",ans);
}
int main(){
	memset(f,0x3f,sizeof f);
    scanf("%d%d",&n,&r);
    for(int i=1;i<n;i++){
        int u,v;scanf("%d%d",&u,&v);
        add_edge(u,v);add_edge(v,u);
    }
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
    init();dfs(1,0);answer();
    return 0;
}
```


---

## 作者：隔壁泞2的如心 (赞：12)

这道题的两种覆盖分别是覆盖相【邻】的点和覆盖【跃】过一定距离的点，所以我愿称它为“树上 $\mathsf{linyue}$ 数点”（

首先这个数据范围肯定是状压 $dp$，我们可以设计出一个很显然的状态：$dp_{i,j,s1,s2}$，其中 $j$ 为 $0$ 或 $1$，表示这个点本身是否被覆盖；$s1,s2$ 是两个长为 $r$ 的 01 串，第 $k$ 位表示第 $i$ 个点向下和向上距离为 $k$ 的点是否被覆盖好了，而 $dp$ 数组就存储在这个状态下的花费最小值。

想要实现从儿子到父亲的转移是容易的，但是合并两个兄弟就很难办。将 $dp_{i1,j1,s11,s12}$ 和 $dp_{i2,j2,s21,s22}$ 合并的状态是：

$$dp_{fa,j1 \lor j2,(s11 \lor s22)\land(s12 \lor s21),s12 \lor s22}$$

直接转移需要枚举两边的所有状态，复杂度 $O(n2^{4r})$，显然过不去……

进一步发掘转移性质，由于 $s1,s2$ 的转移只涉及位运算，我们将它们每位分开考虑，我们将 $s11$、$s12$、$s21$、$s22$ 合并后的 $s1$、$s2$ 的同一位之间的对应关系列成表：

| * | $00$ | $01$ | $10$ | $11$ |
| :-----------: | :-----------: | :-----------: | :-----------: |:-----------: |
| $00$ | $00$ | $01$ | $00$ | $11$ |
| $01$ | $01$ | $11$ | $01$ | $11$ |
| $10$ | $00$ | $01$ | $10$ |$11$ |
| $11$ | $11$ | $11$ | $11$ |$11$ |

横轴是将 $s11$、$s12$ 的某一位连着写到一起，纵轴是将 $s21$、$s22$ 的这一位连着写到一起，中间就是将合并后的 $s1$、$s2$ 的这一位连着写到一起。

进一步阅读题面，发现这不是一道计数题，而是一道最优化题，也就是说，我们可以让“$0$”表示 “任意状态” 而非 “未被覆盖”，最后的答案不会有变化！这样的话，我们转移时，可以先枚举合并后的结果，然后不需要让两个孩子的状态恰好合并为此结果，只要保证它们合并之后不会比目标多出某个位置上的 $1$ 就可以。这样可以大大优化复杂度！

若目标状态的 $s1$、$s2$ 的某一位连起来写是下面的可能，那么只需要考虑 $s11$、$s12$、$s21$、$s22$ 的这一位连起来写的结果在下列的状态即可。

* $00$ ： $0000$

* $01$ ： $0001$、$0100$

* $10$ ： $1010$

* $01$ ： $1100$、$0011$、$0101$

这样的转移一共有 $r$ 位，每位只需要枚举上面的 $7$ 种情况，因此复杂度是是$O(n7^r)$，经过亿些卡常就可以通过此题了！

~~所以这题其实好像没有只会 $O(n8^r)$ 不会正解的可能啊，所以也没必要卡常卡这么夸张吧（~~

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define int long long
#define set(x,y,z) x[(i)]|=(y<<(r-1-j)),x[(i)]|=(z<<(r+1+j))
#define upd(a,b) a=min((a),(b));
using namespace std;
int n,r,mv,a[205],b[205],dp[205][65534],cl[999999],cr[999999],cm[999999];
vector<int> l[205];
void dfs(int now,int fa){
	for(int i=0;i<(1<<r);i++)dp[now][i]=0;
	int fis=0;
	for(int ii=0;ii<=l[now].size();ii++){
		int i=l[now][ii];
		if(i==fa)continue;
		dfs(i,now);
		if(fis==0){
			fis=1;
			for(int j=0;j<(1<<(r*2+1));j++){
				dp[now][j]=dp[i][j];
			}
			continue;
		}
		int pas[65535];
		for(int j=0;j<(1<<(r*2+1));j++){
			pas[j]=dp[now][j];dp[now][j]=0x0101010101010101ll;
		}
		for(int j=0,*pm=cm,*pl=cl,*pr=cr;j<mv;j++,pm++,pl++,pr++){
			upd(dp[now][*pm],pas[*pl]+dp[i][*pr]);
			upd(dp[now][(*pm)|(1<<r)],min(pas[(*pl)|(1<<r)]+dp[i][*pr],pas[*pl]+dp[i][(*pr)|(1<<r)]));
		}
	}
	int ca=(1<<(r))|(1<<(r-1))|(1<<(r+1)),cb=(1)|(1<<(r))|(1<<(r*2));
	int pas[65535];
	for(int j=0;j<(1<<(r*2+1));j++){
		pas[j]=dp[now][j];dp[now][j]=0x0101010101010101ll;
	}
	for(int i=0;i<(1<<(r*2+1));i++){
		upd(dp[now][i|ca],pas[i]+a[now]);
		upd(dp[now][i|cb],pas[i]+b[now]);
		upd(dp[now][i],pas[i]);
	}
	for(int j=0;j<(1<<(r*2+1));j++){
		pas[j]=dp[now][j];dp[now][j]=0x0101010101010101ll;
	}
	for(int i=0;i<(1<<(r*2+1));i++){
		if(i&1){
			dp[now][i>>1ll]=pas[i];
		}
	}
	for(int j=0;j<=r*2;j++){
		for(int h=0;h<(1<<(r*2));h++){
			upd(dp[now][h],dp[now][h|(1<<j)]);
		}
	}
}
signed main(){
	memset(dp,1,sizeof(dp));
	scanf("%lld%lld",&n,&r);
	for(int i=1;i<n;i++){
		int in1,in2;
		scanf("%lld%lld",&in1,&in2);
		l[in1].push_back(in2);l[in2].push_back(in1);
	}
	for(int i=1;i<=n;i++)scanf("%lld %lld",a+i,b+i);
	mv=1;for(int i=1;i<=r;i++)mv*=7;
	for(int i=0;i<mv;i++){
		for(int j=0,nv=i;j<r;j++,nv/=7){
			switch(nv%7){
				case 0:{set(cl,0,0);set(cr,0,0);set(cm,0,0);break;}
				case 1:{set(cl,0,0);set(cr,0,1);set(cm,0,1);break;}
				case 2:{set(cl,0,1);set(cr,0,0);set(cm,0,1);break;}
				case 3:{set(cl,1,0);set(cr,1,0);set(cm,1,0);break;}
				case 4:{set(cl,0,0);set(cr,1,1);set(cm,1,1);break;}
				case 5:{set(cl,1,1);set(cr,0,0);set(cm,1,1);break;}
				case 6:{set(cl,0,1);set(cr,0,1);set(cm,1,1);break;}
			}
		}
	}
	dfs(1,0);
	printf("%lld\n",dp[1][(1<<r)-1]);
}
```


---

题外话：

“泥泞”、“执念”，很容易让我联想到“迷乱的心灵之泽，执念的重生之翼”；看完《流浪地球2》后，我也发觉所谓“执念”真的很能触动我，从很久之前开始；再加上如本题解开头的神秘谐音梗，所以这题还是对我很有特殊的意义的。

结果不知道咋的，明明没什么难点的题我却一直卡住，没有什么思路，导致“做出此题”都快成我的执念了（

现在我已经退役 $4$ 个月了，突然想起来“树上 $\mathsf{linyue}$ 数点”这个梗，然后一推直接就推完了——深深地感觉到自己曾经有多小丑。不过，这也算是加深了这题对我的重要程度（

---

“我相信，所谓的力量，其实，就是心中的执念。”

---

## 作者：251Sec (赞：1)

有一个简单的暴力 DP，$f(u,x,y)$ 代表 $u$ 的子树里和它距离为 $x$ 的点需要一个点来覆盖它，子树里选的点可以覆盖子树外距离它为 $y$ 的点，的最小代价。$x$ 和 $y$ 都是集合。转移的时候需要作一个类似卷积的操作，复杂度 $O(n16^r)$。[代码](https://www.luogu.com.cn/paste/5no4z4xg)。

类比 FWT，我们考虑将恰好的维转化为子集或超集的维来减少转移。重新令 $f(u,x,y)$ 代表 $u$ 的子树里和它距离为 $x$ 的 **子集** 的点需要一个点来覆盖它，子树里选的点可以覆盖子树外距离它为 $y$ 的 **超集** 的点的最小代价。

考虑转移的每一位，例如在某一位上有转移 $f(u,0,1)+f(v,0,1) \rightarrow f(u,0,1)$ 和 $f(u,1,1)+f(v,1,1) \rightarrow f(u,0,1)$，则前者是无用的，因为它完全被后者所包含。这样做之后剩余的有效转移只有 $7$ 种，复杂度 $O(n7^r)$，经过卡常之后洗把脸选个良辰吉日交可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int S = 260 * 260 * sizeof(ll);
int n, r;
vector<int> e[205];
ll a[205], b[205];
ll f[205][260][260], g[260][260];
void chkmin(ll &x, ll y) { x = min(x, y); }
int xu[800005], yu[800005], xv[800005], yv[800005], pC;
void Prework(int x, int a, int b, int c, int d) {
	if (x == r + 1) {
		if ((b >> r & 1) || (d >> r & 1)) return;
		xu[++pC] = a, yu[pC] = b, xv[pC] = c, yv[pC] = d;
		return;
	}
	if (x == r) {
		Prework(x + 1, a << 1 | 0, b << 1 | 0, c << 1 | 0, d << 1 | 0);
		Prework(x + 1, a << 1 | 0, b << 1 | 1, c << 1 | 0, d << 1 | 0);
		Prework(x + 1, a << 1 | 0, b << 1 | 0, c << 1 | 0, d << 1 | 1);
	}
	else {
		Prework(x + 1, a << 1 | 0, b << 1 | 0, c << 1 | 0, d << 1 | 0);
		Prework(x + 1, a << 1 | 1, b << 1 | 1, c << 1 | 1, d << 1 | 1);
		Prework(x + 1, a << 1 | 0, b << 1 | 1, c << 1 | 1, d << 1 | 0);
		Prework(x + 1, a << 1 | 1, b << 1 | 0, c << 1 | 0, d << 1 | 1);
		Prework(x + 1, a << 1 | 1, b << 1 | 0, c << 1 | 1, d << 1 | 0);
		Prework(x + 1, a << 1 | 1, b << 1 | 0, c << 1 | 1, d << 1 | 1);
		Prework(x + 1, a << 1 | 1, b << 1 | 1, c << 1 | 1, d << 1 | 0);
	}
}
void Upd(int u) {
	for (int i = 0; i < r + 1; i++) {
		for (int x = 0; x < (1 << (r + 1)); x += 2) {
			if (x >> i & 1) continue;
			for (int y = 0; y < (1 << r); y++) {
				chkmin(f[u][x | (1 << i)][y], f[u][x][y]);
			}
		}
	}
	for (int i = 0; i < r + 1; i++) {
		for (int y = (1 << r) - 1; y >= 0; y--) {
			if (!(y >> i & 1)) continue;
			for (int x = 0; x < (1 << (r + 1)); x += 2) {
				chkmin(f[u][x][y ^ (1 << i)], f[u][x][y]);
			}
		}
	}
}
void DFS(int u, int fa) {
	memset(f[u], 0x3f, S);
	for (int x = 0; x < (1 << (r + 1)); x++) f[u][x][0] = 0;
	for (int v : e[u]) {
		if (v == fa) continue;
		DFS(v, u);
		memcpy(g, f[u], S), memset(f[u], 0x3f, S);
		for (int i = 1; i <= pC; i++) {
			chkmin(f[u][(xu[i] & ~yv[i]) | (xv[i] & ~yu[i])][yu[i] | yv[i]], g[xu[i]][yu[i]] + f[v][xv[i]][yv[i]]);
		}
		Upd(u);
	}
	memcpy(g, f[u], S), memset(f[u], 0x3f, S);
	for (int x = 0; x < (1 << (r + 1)); x += 2) {
		for (int y = 0; y < (1 << r); y++) {
			chkmin(f[u][x | !(y & 1)][y], g[x][y]);
			chkmin(f[u][x & ~2][y | 2], g[x][y] + a[u]);
			chkmin(f[u][x & ~(1 << r)][y | (1 << r)], g[x][y] + b[u]);
		}
	}
	memcpy(g, f[u], S), memset(f[u], 0x3f, S);
	for (int x = 0; x < (1 << r); x++) {
			for (int y = 0; y < (1 << (r + 1)); y++) {
			chkmin(f[u][x << 1][y >> 1], g[x][y]);
		}
	}
	Upd(u);
}
int main() {
	scanf("%d%d", &n, &r);
	Prework(0, 0, 0, 0, 0);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) scanf("%lld%lld", a + i, b + i);
	DFS(1, 0);
	ll ans = 1e18;
	for (int y = 0; y < (1 << (r + 1)); y++) ans = min(ans, f[1][0][y]);
	printf("%lld\n", ans);
	return 0;
}
```

---

