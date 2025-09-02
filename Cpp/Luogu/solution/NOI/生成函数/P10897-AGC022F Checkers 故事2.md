# AGC022F Checkers 故事2

## 题目背景

>『长存不灭的过去，逐渐消逝的未来』
>
>以某种事物作为代价，以某种代价作为契机……？
>
>"I'm not crazy, my reality is just different to yours."
>
>黄沙卷狂风，庭迹一如故。

## 题目描述

令 $x=40^{76^{93}}$，平面上有 $n$ 个点，第 $i$ 个点的坐标为 $(x^i,0)$。

进行 $m$ 次操作，每次操作选择两点 $A$ 和 $B$，将 $A$ 绕 $B$ 顺时针旋转 $60°$ 并删去 $B$。

求最后剩下的所有点的重心有多少种可能的位置，对 $998244353$  取模。

$2 \le n\le 407693$，$1\le m\le n-1$。

## 说明/提示

本题只有一个 Subtask，只有通过了全部数据点才能得分。

```
哪 怕 梦想  再 虚 妄
无 论 希望  多 渺 茫
悲 伤 痛苦 和  绝 望 别怕
没 关 系的 都  一 样

忘 掉 虚妄  的 梦 想
放 弃 渺茫  的 希 望
快 乐 美好 的  景 象 我们
再 来 一次 怎  么 样
```

## 样例 #1

### 输入

```
3 2```

### 输出

```
12```

## 样例 #2

### 输入

```
4 3```

### 输出

```
60```

## 样例 #3

### 输入

```
22 21```

### 输出

```
478037653```

## 样例 #4

### 输入

```
407693 333333```

### 输出

```
971291318```

# 题解

## 作者：隔壁泞2的如心 (赞：17)

将点的坐标用复数表示，设六次单位根 $\omega=\frac{1+\sqrt{3}i}{2},\omega^6=1$，则对坐标为 $a,b$ 的点进行一次操作，相当于删去这两个点，然后添加一个坐标为 $\omega a+(1-\omega b)=\omega a+\omega^{-1}b$ 的新点。而取重心相当于所有点坐标的加和。由于每个点的坐标在向最终结果转化的过程中都只会乘上或除以 $\omega$，所以最终结果相当于是 $\sum \omega^{a_i}x^i$，其中 $0 \le a_i \le 5$。由于 $x$ 很大，所以只要有一个 $x^i$ 前的系数不同，最终的位置也就不同了。

现在我们要讨论一下哪些系数组合可能存在。把操作视为二元运算，根据操作过程建出二叉表达式树，叶子节点表示一开始的 $x^i$，非叶子节点是运算符，那么由于这道题操作总共是 $m$ 次，实际上会出现 $n-m$ 棵根节点重合的二叉树，它们组成了一个二叉森林（

定义二叉森林里一个节点的“位置”为复数 $\omega^{a-b}$（其中 $a$ 为此节点及其祖先中左儿子的数量，$b$ 为此节点及其祖先中右儿子的数量），那么每一个点的位置都只有 $6$ 种情况，对应着六个不同的六次单位根。设所有 $x$ 前的系数共有 $l_i$ 个 $\omega^i$，若数列 $l_i$ 确定，那么它对应的二叉森林的叶子结点位置集合也就确定了。现在我们设 $r_i$ 为这个二叉森林在 $\omega^i$ 位置上的非叶子节点数量，那么 $l_i$ 要想合法，它就得有至少一个对应的合法 $r_i$。由于：

- 每一个非叶子都会在其左边和右边各有恰好一个对应的儿子

- 除了 $n-m$ 个在 $1$ 位置的根节点的每一个节点都会存在一个在左边或是右边的父亲

我们可以列出一个 $r_i$ 的方程组：

$$\begin{cases}
r_5+r_1=r_0+l_0-(n-m) \\
r_0+r_2=r_1+l_1 \\
r_1+r_3=r_2+l_2 \\
r_2+r_4=r_3+l_3 \\
r_3+r_5=r_4+l_4 \\
r_4+r_0=r_5+l_5 \\
\end{cases}$$

我们要求一组 $r_i$ 的正整数解。这些方程并非线性无关，所以它们不总是有解，这样我们就可以推导出 $l_i$ 要满足下列关系：

$$l_0-l_3-(n-m)=l_2-l_5=l_4-l_1$$

如果 $l_i$ 满足上述限制，那么就可以解出 $r_i$ 满足：


$$\begin{cases}
r_0+r_3=l_1+l_2 \\
r_1+r_4=l_0+l_1-(n-m) \\
r_2+r_5=l_0+l_2-(n-m)\\
\end{cases}$$

满足上面三条的 $r_i$，只要再满足最初的六条式子的任一条，那么方程就成功解出，但这并不一定意味着我们能成功将这些点连成二叉森林……我们再找一些其他的限制：

- 由于森林里的每一棵树在 $1$ 位置都有至少一个点，所以 $r_0+l_0\ge n-m$

- 至少有一棵树的根节点不是叶子，所以 $r_0\ge 1$

现在的这些限制，就足以让 $r_i$ 和 $l_i$ 一定能连成二叉森林了！我们来看看新加的两条限制对 $l_i$ 的影响，其实经过分析，只要 $l_1+l_2\ge 1$ 就行（

不过现在问题来了，满足 $l_i$ 限制的系数数量可咋求呢？

问题可以被转化为三角形网格上的随机游走问题，$x^i$ 前的系数就是第 $i$ 步的方向，$l_i$ 的意思就是“向着 $i$ 次单位根的方向共走了 $l_i$ 步”，那么上述的限制其实就是“最终停留在了位置 $(n-m)$，且离开过实数轴”。

——其实这个结论还是很理所当然的，你想要是初始所有点位置一样也就是说 $x=1$ 而不是 $40^{76^{93}}$，那么不管咋操作重心位置都是 $1$，也就是说所有系数的和一定是 $n-m$（

现在我们只要解决停留位置的问题，然后减掉一个组合数就可以。我们先考虑位置的实数部分的变化，枚举有多少步是平行于实数轴走的，那么剩下的步数的虚部的安排方案就一共有 $C_{n-i}^{\frac{n-i}{2}}$ 种。

我们可以写出答案的表达式：

  $$[x^{n-m}]\sum_{i=0}^{n}C_{n-i}^{\frac{n-i}{2}}C_{n}^{i}(x+\frac{1}{x})^i(\sqrt{x}+\dfrac{1}{\sqrt{x}})^{n-i}$$
  
设 
$$F(x)=x^n\sum_{i=0}^{n}C_{n-i}^{\frac{n-i}{2}}C_{n}^{i}(\dfrac{x^2-2}x)^i$$

则 $F(\sqrt{x}+\dfrac{1}{\sqrt{x}})$ 就是答案。由于我们只要求一项，所以 $F(x)$ 的每一项对答案的贡献都是一个组合数。而求 $F(x)$ 本身相当于一个右复合 $\dfrac{x^2-2}x$，直接分治复合就可以，也可以用[这里的方法](https://www.luogu.com.cn/blog/Fly37510/FUHE-ERCIFENSHI)做到 $O(n\log n)$。

这是验题人代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define LL int
using namespace std;
const int N=2.1e6+11,p=998244353;
LL frc[N],inv[N],r[N],q[N],f1[N],a1[N],c[N],b[N],k1;
vector<LL>g[N];
inline LL add(LL x,LL y){return x+y>=p?x+y-p:x+y;}
inline LL cmb(LL x,LL y){return x<y||y<0?0:1ll*frc[x]*inv[y]%p*inv[x-y]%p;}
inline LL rd(){
	register LL i=0,j=1;char g=getchar();
	while(g>57||g<48){if(g=='-')j=-1;g=getchar();}
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i*j;}
inline LL ksm(LL x,LL y){
	register LL k=1,l=x;
	while(y){if(y&1)k=k*1ll*l%p;l=l*1ll*l%p,y>>=1;}
	return k;
}
inline void bter(){
	for(LL i=0;i<k1;i++)r[i]=(r[i>>1]>>1)|(i&1?k1>>1:0);}
inline void ntt(LL *f,bool m){
	register LL i,j,k,l,h;
	for(i=0;i<k1;i++)
		if(i<r[i])swap(f[i],f[r[i]]);
	for(i=1;i<k1;i<<=1){
		l=ksm(m?3:332748118,(p-1)/(i<<1));
		for(j=q[0]=1;j<i;j++)q[j]=q[j-1]*1ll*l%p;
		for(j=0;j<k1;j+=i<<1)
			for(h=j;h<j+i;h++)
				k=q[h-j]*1ll*f[h+i]%p,f[h+i]=add(f[h],p-k),f[h]=add(f[h],k);}
	if(!m)for(LL i=0,k=ksm(k1,p-2);i<k1;i++)f[i]=1ll*f[i]*k%p;
}
inline void dntt(LL x,LL y,LL z){
	if(y==z){g[x].push_back(a1[y]);return;}
	register LL i,s1,s2,k,j,mid=y+z>>1;
	dntt(x<<1,y,mid);dntt((x<<1)+1,mid+1,z);
	for(k1=1;k1<z-y+1<<1;k1<<=1);bter();
	for(i=0;i<k1;i++)c[i]=b[i]=0;
	for(i=0,s1=g[(x<<1)+1].size();i<s1;i++)c[i]=g[(x<<1)+1][i];
	for(i=mid-y+1<<1,j=1;i>=0;i-=2,j=add(p-j,p-j))b[i]=1ll*cmb(mid-y+1,i>>1)*j%p;
	ntt(b,1);ntt(c,1);
	for(i=0;i<k1;i++)b[i]=1ll*b[i]*c[i]%p;ntt(b,0);
	for(i=0,s2=g[x<<1].size();i<s2;i++)j=z-y+i-(s2>>1),b[j]=add(b[j],g[x<<1][i]);
	for(i=0;i<=z-y<<1;i++)g[x].push_back(b[i]);
}
int main()
{
	register LL i,j,k,ans=0,n=rd(),m=rd();
	for(i=frc[0]=1;i<=n<<1;i++)frc[i]=1ll*frc[i-1]*i%p;
	for(--i,inv[i]=ksm(frc[i],p-2);i;i--)inv[i-1]=1ll*inv[i]*i%p;
	for(i=(n&1);i<=n;i+=2)a1[i]=1ll*frc[n]*inv[i]%p*inv[n-i>>1]%p*inv[n-i>>1]%p;
	dntt(1,0,n);
	for(i=0;i<=n<<1;i+=2)ans=add(ans,1ll*g[1][i]*cmb(i,n-m+(i>>1))%p);
	if(!(m&1))ans=add(ans,p-cmb(n,m/2));
	printf("%d\n",ans);
	return 0;
}
```
特殊奖励 1：你可能遇到这题会想去回顾原版 Checkers，故此奖励的获得条件为：```于比赛期间提交 AGC022F 的 AC 代码。```

---

