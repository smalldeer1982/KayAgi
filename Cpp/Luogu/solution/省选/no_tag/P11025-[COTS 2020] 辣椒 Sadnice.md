# [COTS 2020] 辣椒 Sadnice

## 题目背景

译自 [Izborne Pripreme 2020 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2020/) D1T3。$\texttt{3s,0.5G}$。

## 题目描述

花园里种了辣椒。花园可以被描述为一张 $(N+1)\times (M+1)$ 的网格图，其中辣椒被种在格点上。她还用 $[(N+1)\times (M+1)-1]$ 条绳索连接相邻的格点，使得任意两株辣椒都能通过绳索互相到达。换句话说，绳索构成了这个网格图的生成树上的边。

定义两棵辣椒**连通**，当且仅当它们通过绳索直接或间接相连。

晚上有人要来搞破坏。破坏者会在水平方向或者竖直方向划一刀，将划过的绳索全部切断。切断后，辣椒植株会被分成几个连通块。**破坏者会让连通块的数量尽量多。**

怎么安排绳索，才能使得被切断后连通块的数量最小？

## 说明/提示


#### 评分方式

若你输出的解是最优解，得该测试点的满分。

否则，按照如下方式计算得分倍数：

$$K=0.75\times \max\left\{\left(\frac{A-1}{B-1}\right)^4,1-\left(1-\frac{1}{(B-A)^2}\right)^6\right\}$$

其中 $A$ 为最优的答案，$B$ 为你构造方案的答案。

你将获得 $K$ 倍测试点得分的分数。子任务得分为子任务内测试点得分最小值。

例如，样例 $1$ 输出得满分。样例 $2$ 输出得 $75\%$ 的分数。

#### 数据范围

对于 $100\%$ 的数据，保证 $1\le N\le M\le 1\, 000$。


| 子任务编号 | $N,M\le $ | 特殊性质 | 得分 |  
| :--: | :--: | :--: | :--: |
| $ 1 $    | $1\,000$ | A |$ 15 $   | 
| $ 2 $    | $1\,000$ | B |$ 15 $   |  
| $ 3 $    | $3$ |  |$ 5 $   |  
| $ 4 $    | $10$ || $ 10 $   |
| $ 5 $    | $100$ | | $ 20 $   |
| $ 6 $    | $1\, 000$ || $ 35 $   |

- 特殊性质 A：$N=M$。
- 特殊性质 B：$2N=M$。


## 样例 #1

### 输入

```
2 2```

### 输出

```
o--o  o
|     |
o  o--o
|     |
o--o--o```

## 样例 #2

### 输入

```
2 2```

### 输出

```
o--o--o
|
o  o--o
|     |
o--o--o```

# 题解

## 作者：FFTotoro (赞：2)

Izborne Pripreme 最喜欢出的组合构造。下文中使用了[官方题解](https://hsin.hr/pripreme2020/)内的部分图片。

由于绳索形成了该网格图的一个生成树，每切断一条边连通块的个数就会 $+1$，所以最后我们只需要让被切断的边最少。

试图求出答案的一个下界：总共有 $(NM+N+M)$ 条边，有 $N$ 行和 $M$ 列可以被选择切断，根据基础的不等式知识，下界为 $L=\left\lceil\dfrac{NM+N+M}{N+M}\right\rceil=\left\lceil\dfrac{NM}{N+M}\right\rceil+1$。下面我们提出一种构造，使得对于所有 $N\le M$，这个下界都可以被取到。

首先考虑一个基本结构：令辣椒的行、列编号**从 $0$ 开始**，对于编号为偶数的行，将整行横着连起来，对于最右边的一列（即第 $M$ 列），将整列竖着连起来，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yb9h1az8.png)

接着考虑将奇数行的辣椒向上 / 下 / 右连边以形成生成树，由于每一“行”（这里带引号的“行”指绳索的行）最多放 $(L-1)$ 个竖向绳索，所以我们对于每一“行”都放 $(L-1)$ 条绳索，并且为了让横向绳索不至于重叠过多，这些竖向绳索需要尽量“错开”放置，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/akw13hqk.png)

即对于奇数行，从上一个奇数行往上 / 下连边的最后一列往后一列开始，向上依次连 $(L-1)$ 条边，接着向下连 $(L-1)$ 条边，如果到 $(M-1)$ 列了就回到第 $0$ 列继续……对于其他没有往上 / 下连边的就直接往右连，这样连通性是可以保证的。特别的，如果最后一行是奇数行，那么显然不能往下连，此时直接往右连即可。

观察到上面往右连的绳索也是尽量错开的，又由于 $N\le M$，于是经过计算得出横向绳索的答案并不会超过下界，而竖向绳索的答案根据上面的构造必然不会超过下界。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n,m,k; cin>>n>>m,k=(n*m-1)/(n+m)+1;
  // 这里 k 为上文所述的 (L - 1)
  vector s(n<<1|1,string(m*3+1,32));
  for(int i=0;i<=n;i++)
    for(int j=0;j<=m;j++)
      s[i<<1][j*3]='o';
  auto connect=[&](int x,int y,int op){
    if(op)s[(x<<1)+op][y*3]='|';
    else s[x<<1][y*3+1]=s[x<<1][y*3+2]='-';
    /* 连边：
     * op = 0 表示向右连
     * op = 1 表示向下连
     * op = -1 表示向上连
     */
  };
  for(int i=0;i<=n;i++){
    if(i&1){
      for(int j=0;j<m;j++){
        int x=((i-1)*k+j)%m;
        if(j<k)connect(i,x,-1);
        else if(j<k<<1&&i<n)connect(i,x,1);
        else connect(i,x,0);
      }
    }
    else for(int j=0;j<m;j++)
      connect(i,j,0);
    if(i<n)connect(i,m,1);
  }
  for(auto r:s)cout<<r<<'\n';
  return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P11025)

**题目大意**

> 给定 $(n+1)\times (m+1)$ 的网格图，构造一棵生成树，使得任意切掉某一行或某一列的边后，剩余连通块数量最大值最小。
>
> 数据范围：$n,m\le 1000$。

**思路分析**

先考虑答案至少为 $\left\lceil \dfrac{(n+1)(m+1)-1}{n+m}\right\rceil=\left\lceil \dfrac{nm}{n+m}\right\rceil+1$，不妨记 $k=\left\lceil \dfrac{nm}{n+m}\right\rceil$。

看到 $+1$ 我们可以想到对最后一行一列的点全部连起来，只要考虑剩余的 $n\times m$ 个点。

我们观察发现：如果每个点都在他右边和下面的点中恰好选一个点相连，那么一定可以生成树，这是因为一个环一定要有一个拐点同时向右和向下连边。

那么我们只要让每一行向下的边数和每一列向右的边数尽可能平均即可。

可以对每一行都选 $k$ 条边向下，为了让每一列剩余向右的边数量尽可能平均，我们在第 $i$ 行取 $[ik\bmod n,(i+1)k\bmod n)$ 范围内的边向下即可。

容易证明这个构造的答案就是 $k+1$。

时间复杂度 $\mathcal O(nm)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1005;
bool f[MAXN][MAXN];
signed main() {
	ios::sync_with_stdio(false);
	int n,m; cin>>n>>m;
	int k=(n*m-1)/(n+m)+1;
	for(int i=0,j=0;i<n;++i) for(int o=0;o<k;++o) f[i][j]=true,j=(j+1)%m;
	for(int i=0;i<n;++i) {
		for(int j=0;j<m;++j) cout<<"o"<<(f[i][j]?"  ":"--");
		cout<<"o\n";
		for(int j=0;j<m;++j) cout<<(f[i][j]?"|":" ")<<"  ";
		cout<<"|\n";
	}
	for(int i=0;i<m;++i) cout<<"o--";
	cout<<"o\n";
	return 0;
}
```

---

## 作者：UniGravity (赞：1)

首先由于最后的结果是生成树，因此连通块数即为切断的边数加一。

考虑假设有 $a$ 条竖边，$b$ 条横边，有 $a+b=(n+1)(m+1)-1=nm+n+m$。由于破坏者会每次选择切掉更多的边，分别对于横边和竖边均匀分配（先假设这是可以被构造到的），此时切断边数为 $\max\left(\left\lceil\frac an\right\rceil,\left\lceil\frac bm\right\rceil\right)$。

枚举后假设我们找到了最优的一组 $a,b$，考虑如下图方式调整：

![](https://cdn.luogu.com.cn/upload/image_hosting/81pt8gu0.png)

我们知道连接两列之间横向边需要被删掉几条，只需轮流选择哪一行的将其重新向上定向即可。不难发现此时图仍然连通。

```cpp
const int N=1005;
int n,m,a,b;
bool dw[N][N],rt[N][N];

signed main(){
    n=read(),m=read();
    int res=0x3f3f3f3f;
    forto(i,1,(n+1)*(m+1)){
        int a1=i,b1=n*m+n+m-a1;
        if(a1<n||b1<m)continue;
        int v=max((a1-1)/n,(b1-1)/m)+1;
        if(v<res)res=v,a=a1,b=b1;
    }
    cerr<<a<<' '<<b<<' '<<res<<'\n';     
    a=((a-1)/n+1)*n,b=((b-1)/m+1)*m;
    cerr<<a/n<<' '<<b/m<<'\n';
    forto(i,1,n)dw[i][1]=1;
    forto(i,1,n+1)forto(j,1,m)rt[i][j]=1;
    int id=1;
    forto(j,2,m+1){
        int cnt=n+1-b/m;
        while(cnt--){
            dw[id][j]=1,rt[id+1][j-1]=0;
            id++;if(id>n)id=1;
        }
    }
    forto(i,1,n+1){
        forto(j,1,m+1){
            printf("o");
            if(j>m)continue;
            printf(rt[i][j]?"--":"  ");
        }
        printf("\n");
        if(i>n)continue;
        forto(j,1,m+1){
            printf(dw[i][j]?"|":" ");
            if(j>m)continue;
            printf("  ");
        }
        printf("\n");
    }
    return 0;
}
```

---

