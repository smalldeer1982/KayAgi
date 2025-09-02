# 「MCOI-04 / AC6-M09」Heavy Command Cruiser

## 题目背景

这是一个作战部署命令。

我们已经从国家安全局获得了有关敌方重型指挥巡洋舰的部分机密情报。

敌方巡航机的正式名称已被确认为 P-1112 Aigaion。

空中舰队中包含一种 Kottos 中型巡航机负责电子支援，还有一种 Gyges 中型巡航机负责近程防空。

Aigaion，作为指挥机，负责一切与巡航导弹相关的事务。

在获得这些情报之后，我们可以草拟一个摧毁 Aigaion 的计划。

仔细听好了。

Aigaion 只能在机体前部接受空中加油。

多架加油机必须同时处在 Aigaion 前方才能进行加油作业。

当加油机在 Aigaion 前部进行加油时，Aigaion 的雷达探测能力会暂时削弱。

这里就是关键点了。

Aigaion 在进行加油时，其雷达基本完全无法探测在其前方飞行的物体。

如果你们能维持在一个固定航线并在一个特定高度上飞行，你们就能在不被敌军发现的情况下，从空中接近 Aigaion。

所以我们解决掉这只怪物的最佳时机就是它进行空中加油的时候。

Aigaion 的预定航线图也包含在这份情报中。

简报结束后，我们将在机库再次检查航线图。

快去准备吧。

…………

Garuda 队，交战！

$$_{{\frac{\large\text{ACE COMBAT }\Large6}{\tiny{\text{F i r e s\quad O f\quad L i b e r a t i o n}}}}}\\ \text{Mission 09} \\\Large\text{Heavy Command Cruiser}\\\tiny -\ The\ Dead\ Sea\ -$$

![](https://cdn.luogu.com.cn/upload/image_hosting/0xt87jqh.png)

## 题目描述

在平面上给定一棵有根树，树根为 $1$，根的深度为 $0$。

对于深度为 $x$ 的节点，其 **纵坐标** 为 $n-x+1$。

对于一个节点的所有子节点，**从左到右按照编号升序排列**。每条边都是一条 **连接两个点的线段**。

每一个叶子节点都有一条 **平行于 $y$ 轴且向 $y$ 轴负方向无限延伸的射线**，根节点有一条 **平行于 $y$ 轴且向 $y$ 轴正方向无限延伸的射线**。

每个线段或射线带一个权值。

**任意两条线段或射线只在树的节点处相交。**

如果你不理解这个树是怎么画的，可以阅读样例 1 解释。

给定 $q$ 组 $u,v$，你现在要从点 $u$ 开始在平面上自由移动，但是你不能经过除 $u,v$ 以外的任何一个点，且每经过一条线段或射线就会产生其对应的权值的代价。

你的目标是移动到点 $v$，你需要求出移动过程产生的最小代价。

## 说明/提示

idea：Sol1，solution：dengyaotriangle & Sol1 & Guoyh，code：Sol1，data：Sol1

对于 $100\%$ 的数据，满足 $1\leq n\leq 5\times 10^5$，$1\leq q\leq 5\times 10^6$，$1\leq f_i<i$，$1\leq w_i,w_1,d_{u}\leq 2\times 10^3$，$0\leq s\leq10^9$。

---

「魂归大海……」

「你可以休息了……」

「安息吧。」

## 样例 #1

### 输入

```
30 10000 20051130
1 1
2 1
3 1
4 1
5 1
6 1
7 1
7 1
9 1
9 1
11 1
11 1
12 1
13 1
13 1
14 1
17 1
18 1
19 1
20 1
21 1
19 1
23 1
22 1
22 1
25 1
25 1
28 1
29 1
1
1 1 1 1 1 1 1 1```

### 输出

```
2 6362```

# 题解

## 作者：MEKHANE (赞：3)

定义 $L_{x}$ 表示 $x \rightarrow f_x$ 的左边的平面，$R_x$ 同理。

首先我们考虑直击题目最核心的性质：给的是一颗树，而非图。联想到子树相关的 $dp$ 不难发现，对于 $L_x$ 而言，其到达 $R_x$ 仅有三种形式：

1.经过 $x \rightarrow f_x$。

2.经过子树中的若干平面。

3.先经过 $L_{f_x}$ 的左平面再经 $R_{f_x}$ 再到达 $R_x$。

那么发现前两部分是独立的子树 $dp$（也可以理解为 floyd 松弛一部分边），可以 $\mathcal O(n)$ 做，这里给出 dp 式子：$w_{x}=min({w_{x},sum_{y \in son_x}w_y})$。

然后再处理第三部分（原因是第三部分部分路径依赖于前两部分），同样的有：$w_x=min(w_x,sum_{y \in son_{f_x}/x} w_x+w_{f_x})$。（类似换根 dp ）。

处理出这一部分后，我们再次发掘 $u \rightarrow v$ 路径的性质，也只有若干种情况，但是有一个共同的性质：一定会经过与 lca 相交的平面。

那么我们就可以处理 $L_x/R_x$ 到若干级祖先的 $L_{anc}/R_{anc}$ 的最短路，然后合并一下即可。

关于如何处理：

1.首先距离信息是一个半群，满足结合律（进一步的，可以写成矩阵的形式），所以可以进行倍增，复杂度 $\mathcal O(n \log n+q \log n)$，卡常后可通过本题，代码给的是这个实现。

2.我们也可以先 $O(1)$ 求 LCA，仿照长链求 $k$ 级祖先的方式，及先跳最大一步，在对应的长链上维护不超长链长度的向上 $k$ 步的合并信息，直接合并即可。但对于链内，我们还需要 $O(1)$ 求区间半群，做法有：猫树（预处理长链对于某个断点的前缀/后缀合并信息，然后询问时可以 $O(1)$ 查分治树 LCA，也可以写成线段树，然后两个点的编号 xor 求 clz），sqrt tree。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define per(i,j,k) for(int i=j;i>=k;i--)
using namespace std;
const int N=5e5+5;
int n,q,s,ans,lans,fa[N],fb[N],fc[N],fd[N],hd[N],nxt[N],pr[N],sum[N],mi[N],dep[N],f[N][19];
long long ans1;
struct ss{int x,y,z,w;}g[N][19];
struct ss1{int x,y;};
ss1 mul(const ss1 &x,const ss &y){return {min(x.x+y.x,x.y+y.z),min(x.x+y.y,x.y+y.w)};}
ss mul(const ss &x,const ss &y){return {min(x.x+y.x,x.y+y.z),min(x.x+y.y,x.y+y.w),min(x.z+y.x,x.w+y.z),min(x.z+y.y,x.w+y.w)};}
namespace sj{
    unsigned z1,z2,z3,z4,b;
    unsigned rand_(){
        b=((z1<<6)^z1)>>13,z1=((z1&4294967294U)<<18)^b,b=((z2<<2)^z2)>>27,z2=((z2&4294967288U)<<2)^b;
        b=((z3<<13)^z3)>>21,z3=((z3&4294967280U)<<7)^b,b=((z4<<3)^z4)>>12,z4=((z4&4294967168U)<<13)^b;
        return (z1^z2^z3^z4);
    }
}
void srand(unsigned x){using namespace sj; z1=x,z2=(~x)^0x233333333U,z3=x^0x1234598766U,z4=(~x)+51;}
int read(){
    using namespace sj;
    int a=rand_()&32767,b=rand_()&32767;
    return a*32768+b;
}
int js(int x,int y){
    if(x==y) return 0;
    if(dep[x]<dep[y]) swap(x,y);
    ss1 dx={0,0},dy={0,0}; int jl=dep[x]-dep[y];
    if(jl>0){
        jl--;
        per(i,18,0) if((jl>>i)&1) dx=mul(dx,g[x][i]),x=f[x][i];
        if(fa[x]==y) return min(dx.x,dx.y);
        dx=mul(dx,g[x][0]),x=fa[x];
    }
    per(i,18,0) if(f[x][i]!=f[y][i]) dx=mul(dx,g[x][i]),x=f[x][i],dy=mul(dy,g[y][i]),y=f[y][i];
    if(x>y) swap(x,y),swap(dx,dy);
    int ans=dx.y+dy.x+sum[pr[y]]-sum[x];
    dx=mul(dx,g[x][0]),dy=mul(dy,g[y][0]);
    return min(ans,dx.x+dy.y+mi[fa[x]]);
}  
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>q>>s,srand(s);
    rep(i,2,n) cin>>fa[i]>>fb[i];
    per(i,n,2){
        if(hd[fa[i]]) pr[hd[fa[i]]]=i;
        nxt[i]=hd[fa[i]],hd[fa[i]]=i;
    }cin>>fb[1];
    rep(i,1,n) if(!hd[i]) cin>>fc[i];
    per(i,n,1) if(hd[i]){
        int lst=0;
        for(int j=hd[i];j;lst=j,j=nxt[j]) sum[j]=sum[pr[j]]+min(fb[j],fc[j]);
        fc[i]=sum[lst];
    }mi[1]=fb[1];
    rep(i,2,n){
        dep[i]=dep[fa[i]]+1,f[i][0]=fa[i]; int dq=min(fb[fa[i]],fc[fa[i]]);
        g[i][0]={sum[pr[i]],fc[fa[i]]-sum[pr[i]],sum[i],fc[fa[i]]-sum[i]};
        g[i][0].x=min(g[i][0].x,g[i][0].y+dq),g[i][0].y=min(g[i][0].y,g[i][0].x+dq);
        g[i][0].z=min(g[i][0].z,g[i][0].w+dq),g[i][0].w=min(g[i][0].w,g[i][0].z+dq);
        mi[i]=min({mi[fa[i]]+g[i][0].x+g[i][0].w,fb[i],fc[i]});
    }
    rep(j,1,18) rep(i,1,n) if(dep[i]>=(1<<j)) f[i][j]=f[f[i][j-1]][j-1],g[i][j]=mul(g[i][j-1],g[f[i][j-1]][j-1]);
    while(q--){int x=(read()^lans)%n+1,y=(read()^lans)%n+1; lans=js(x,y),ans^=lans,ans1+=lans;}
    cout<<ans<<" "<<ans1;
}
```




---

