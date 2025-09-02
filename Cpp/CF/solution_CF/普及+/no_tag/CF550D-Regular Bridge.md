# Regular Bridge

## 题目描述

An undirected graph is called  $ k $ -regular, if the degrees of all its vertices are equal $ k $ . An edge of a connected graph is called a bridge, if after removing it the graph is being split into two connected components.

Build a connected undirected $ k $ -regular graph containing at least one bridge, or else state that such graph doesn't exist.

## 说明/提示

In the sample from the statement there is a suitable graph consisting of two vertices, connected by a single edge.

## 样例 #1

### 输入

```
1
```

### 输出

```
YES
2 1
1 2
```

# 题解

## 作者：Caro23333 (赞：6)

首先考虑把桥扔掉，原图变为两个联通块，其中每个联通块中有一个点度数为k-1,其他的点度数为k。下面考虑构造其中一个联通块。

不妨令该联通块点数为n。
注意到当k为偶数时，这一个联通块中的总度数应该是nk-1，是一个奇数，而由于是无向图，每条边对总度数的贡献是2，总度数应该是偶数，产生矛盾。从而k为偶数时是无解的。

k为奇数时，令n=2k-1，并且将所有点列成三排：第一排和第二排分别有k-1个点，第三排有一个。第三排与第二排之间两两连边，第二排与第一排之间两两连边，再令第一排中第2t-1与第2t个连边（1<=t<=(k-1)/2）。不难发现这样一来第二排与第一排每个点的度数是k，第三排一个点度数为k-1，符合我们的需求。另一个联通块类似即可，不要忘记将两个联通块中度数为k-1的点相连作为桥。

复杂度是O(k^2)的，可以通过；代码简单，略去。

---

## 作者：YCS_GG (赞：4)

首先是$k$是偶数的时候一定会有一个欧拉回路，所以显然不成立

当$k$是奇数的时候可以如下构造

先把桥拆掉，剩下的两个连通块可以是完全对称的连通块

每一个联通块里有一个度数为$k-1$的点用来连桥

为了达到这个目的，新建$k-1$个点用来连这个点，记作$V_1$

这新建的$k-1$个点现在各需要$k-1$条连边，再新建$k-1$个点，记作$V_2$

让$V_1$中每个点都向$V_2$中每个点连边，此时$V_2$中每个点还需要$1$条连边，因为$k-1$是偶数，所以每两个点连边即可

![当k=5的时候的一个连通块](https://cdn.luogu.com.cn/upload/image_hosting/0fcbwfja.png)
当$k=5$的时候一个连通块

```cpp
#include <iostream>
using namespace std;
int k;
struct RevEdge {
    int u, v;
    RevEdge(int a, int b) {
        u = a;
        v = b;
    }
};
int n, m;
ostream &operator<<(ostream &os, const RevEdge e) {
    os << e.u << " " << e.v << endl;
    os << e.u + n / 2 << " " << e.v + n / 2;
    return os;
}
int main() {
    cin >> k;
    if (!(k & 1)) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    n = 4 * k - 2;
    m = n * k / 2;
    cout << n << " " << m << endl;
    cout << 1 << " " << n / 2 + 1 << endl;
    for (int i = 2; i <= k; i++) {
        cout << RevEdge(1, i) << endl;
    }
    for (int i = 2; i <= k; i++) {
        for (int j = k + 1; j <= 2 * k - 1; j++) {
            cout << RevEdge(i, j)<<endl;
        }
    }
    for (int j = k + 1; j <= 2 * k - 1;j+=2){
        cout << RevEdge(j, j + 1) << endl;
    }
    return 0;
}
```


---

## 作者：Aftglw (赞：1)

题目要求必须有桥，于是便从桥入手构造。

显然，由桥分割出来的两个子图是对称的，所以在这里我们只考虑一半。

$k=1$ 的情况跳过了，$k=2$ 的情况搞了半天没搞出来，先放着不管，先看看 $k=3$ 的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/vtixhj0s.png)

如图，我们为了先满足桥端点的度数达到 $k$ ，于是便在 A 的另一边接上 C，D 两个结点，但此时 C，D 的又不满足度数为 $k$ 的限制了，所以我们需要再加入**辅助点**。

添加**两个**辅助点 E，F（为什么是两个等会再说）。

为了不破坏 A 的度数，我们将 E，F 与 C，D分别连边。

![](https://cdn.luogu.com.cn/upload/image_hosting/wdtx26bs.png)

此时 C，D 的度数刚好为 $k$ 不用管了，但 E，F 却又不满足度数限制了。没关系，只需在 E，F 之间连一条边即可（所以才要**偶数**个辅助点，奇数个就会有某一个辅助点度数差 1 ）。

于是我们就构造出了 $k=3$ 的一组解。

![](https://cdn.luogu.com.cn/upload/image_hosting/rc5s30b5.png)

为了找到普遍构造规律，在再多试几组数据。

来看 $k=5$ 的情况，前面的内容与 $k=3$ 的情况大致相同，直接来到建立两个辅助点之后。

![](https://cdn.luogu.com.cn/upload/image_hosting/6983l3mc.png)

但此时，我们发现红色的点还尚未满足度数限制，我们考虑在这些点之间两两连边。

或许你可能会想到再来 $2a(a\in \mathbb{N})$ 个辅助点不就行了吗？

但这样的话你就无法确定最终图中点的个数，甚至空间开不下。后面我会证明只需两个辅助点即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/s3espxe3.png)

这样就行了。

接下来寻找普遍规律，假设现在要求度数为 $k$ 。

在桥的一侧接上 $k-1$ 个点，这样我们就满足了桥端点的度数限制。然后再加上两个辅助点，那么我们构造的图一共就有 $(k+2)\cdot2$ 个点，整个图的总度数也就为 $(k+2)\cdot2\cdot k$ ，又因为每条边会带来两个度数，于是共有 $(k+2)\cdot k$ 条边。

由于桥端点和辅助点的限制已经得到满足，我们现在只需考虑在这 $k-1$ 点（也就是在 $k=5$ 的例子中所红色框内的这些点）之间的连边。

![](https://cdn.luogu.com.cn/upload/image_hosting/edk90agu.png)

对于这 $k-1$ 个点而言，每个点都已经和桥端点、两个辅助点连边，所以此时度数为 $3$ ，还需连出 $k-3$ 条边。

能与之相连的点只能在这 $k-1$ 个点中的除自己以外的 $k-2$ 个点中（因为辅助点和桥端点的度数都已达到 $k$ 了），而 $k-2>k-3$ 所以可以连完 $k-3$ 条边。（这也就证明了为什么只用两个辅助点就够了）

同时，为了保证这 $k-1$ 个点中，每个点的度数都能增加到 $k$，必须保证 $k-1$ 为偶数（才能成对连边），也就说明了只有 $k$ 为奇数时才有解。

具体实现可以从完全图中删边达成。

注意 $k=1$ 的情况需特判。

```cpp
#include <bits/stdc++.h>
#define re register
//#define int long long
#define mp(a,b) make_pair(a,b)
#define inf 0x3f3f3f
using namespace std;
inline int read()
{
	re int x=0,f=1;
	re char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}
	return x*f;
}
const int N=250,P=998244353;
int k;
bool vis[N][N];
inline void del(int u,int v)//这里保证了u<v，所以只用删单向的
{
	vis[u][v]=0;//删除边u->v
	vis[u+k+2][v+k+2]=0;//删的同时对称地将另一个子图的边也删掉
}
signed main()
{
	memset(vis,1,sizeof(vis));//完全图
	k=read();
	if(!(k&1)) return puts("NO"),0;
	puts("YES");
	if(k==1) return printf("2 1\n1 2"),0;
	int n=(k+2)*2,m=(k+2)*k;
	printf("%d %d\n",n,m);
	del(1,k+1),del(1,k+2);//1为桥端点，k+1、k+2为辅助点
	for(re int i=2;i<k;i+=2) del(i,i+1);
   	//以下为输出
	for(re int i=1;i<=n;++i)
	{
		if(i<=k+2)
		{
			for(re int j=i+1;j<=k+2;++j)
				if(vis[i][j])
					printf("%d %d\n",i,j);
		}
		else
		{
			for(re int j=i+1;j<=n;++j)
				if(vis[i][j])
					printf("%d %d\n",i,j);
		}
	}
	printf("%d %d",1,1+k+2);//最后连上两个桥端点
	return 0;
}
```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF550D)

比较简单。

考虑桥边的两个端点，它们分别在两个不同的连通块中，并且与另外 $k-1$ 个点相连。对于这个联通块，只有一个度数为 $k-1$ 的点，剩下的点度数都为 $k$，那么度数和形如 $nk-1$，而无向图度数和必然是偶数，因此 $k$ 必须是奇数。

然后考虑相连的那 $k-1$ 个点，它们每个点还要再跟 $k-1$ 个点相连。如果是两排 $k-1$ 个点两两相连的话，那么跟桥的端点连接的那排点已经满足条件了，另一排点的度数均为 $k-1$，需要每个度数加 $1$。注意到 $k-1$ 为偶数，那么这 $k-1$ 个点两两为一对，可以分出 $\dfrac{k-1}{2}$ 对，每对之间连边即可。

另外一边可以对称地构造，这样就全部满足条件了。

这样每一个联通块都有 $2(k-1)+1=2k-1$ 个点，图的总点数就是 $4k-2$。而总边数就是 $2(\dfrac{k-1}{2}+(k-1)^2+k-1)+1=2k^2-k$。

时间复杂度 $O(k^2)$。

---

## 作者：__LiChangChao__ (赞：0)

## 题意

题意翻译给的很清楚了，但是在翻译中没有提到输出格式第一行要输出点数和边数。
## 前置

首先题目要求**存在一个桥**。

那我们首先得知道什么是桥？

![](https://cdn.luogu.com.cn/upload/image_hosting/jn1hazz0.png)

在上面的图中，若我们将 $2$ 和 $3$ 之间的边去掉，那么 ${0,1,2,4,5}$ 和 $3$ 将会构成两个连通块，所以 $2$ 和 $3$ 之间的边就是一个桥。

## 思路

在前面我们提到了桥的概念，在本题中，要求存在一个桥，那么考虑做一个**轴对称**，先考虑桥一边的半张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/64fx740o.png)

这是一个桥。

由于题目要求每个点的度数（连的边的数量）为 $k$，现在点 $1$ 已经连着一个桥了，那么还需要为它连上 $k-1$ 个点，以 $k=3$ 为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/cfbzsth2.png)

然而我们又发现 $3,4$ 的度数又为 $1$ 了，怎么办？连成一棵二叉树？

显然不现实。

那么我们加上几个辅助点试一试？那加几个呢？加一个试试？

![](https://cdn.luogu.com.cn/upload/image_hosting/9hneush6.png)

那这个辅助点的度数又为 $2$，不可行。

那么两个呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/e6rvtpv6.png)

每个点的度数都为 $3$，可以了！我们构造出了一组 $k=3$ 的解（的一半）。

但这只是 $k=3$ 的特例，那么 $k=5$ 的情况呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/c7fn7v05.png)

可以发现，$3,4,5,6$ 的度数为 $3$，那要再加点吗？

只需要两个点就够了！

显然，对于位于中间的 $3,4,5,6$ 来说，它们还需要 $k-2-1=k-3$ 条边，而中间点一共有 $k-1$ 个，除去自己还有 $k-1-1=k-2$ 个，而 $k-2>k-3$，所以只需要在中间点之间连上边就可以满足条件了。

同时，值得注意的是，为了满足条件，$k-1$ 个点至少要两两配对，所以 $k-1$ 为偶数，则 $k$ 只能是奇数。

由于上述中有 $k-2$，所以 $k=1$ 需要特判。

但在输出中要计算点数和边数，这个又怎么算呢？

每一边都有 $2$ 个辅助点， $k-1$ 个中间点，$1$ 个桥的端点，一共 $k-1+2+1=k+2$ 个点，则全图一共有 $(k+2)\times 2$ 个点。

每个点度数都为 $k$，则全图度数为 $(k+2)\times 2\times k$，每条边对度数的贡献是 $2$，则全图边数为 $\frac{(k+2)\times 2\times k}{2}=k\times(k+2)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
int du[505];//记录度数
int main(){
	scanf("%d",&k);
   if(k==1)return printf("YES\n2 1\n1 2"),0;//特判
	if(k%2==0)return puts("NO"),0;//不成立
	int k1=k-1;//计算半边的中间点数
	puts("YES");
	printf("%d %d\n",2*(k+2),(k+2)*k);//计算点数和边数
	for(int i=1;i<=2*(k+2);i++)du[i]=3;
	for(int b=0;b<=1;b++){
		for(int i=1;i<=k1;i++){
			printf("%d %d\n",i+(k1+3)*b,(b+1)*(k1+3)-2);//连接辅助点一
			printf("%d %d\n",i+(k1+3)*b,(b+1)*(k1+3)-1);//连接辅助点二
			printf("%d %d\n",i+(k1+3)*b,(b+1)*(k1+3));//连接桥
			for(int j=i+1;j<=k1&&du[i+(k1+3)*b]<k;j++){
				if((i%2==0||j!=i+1)&&j!=i&&du[j+(k1+3)*b]<k)printf("%d %d\n",i+(k1+3)*b,j+(k1+3)*b),du[i+(k1+3)*b]++,du[j+(k1+3)*b]++;//连接其它中间点
			}
		}
		printf("%d %d\n",(b+1)*(k1+3)-2,(b+1)*(k1+3)-1);//为辅助点连边
	}
	printf("%d %d",k1+3,2*k1+6);//连接桥
}

```

---

