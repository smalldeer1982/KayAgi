# [ABC126E] 1 or 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc126/tasks/abc126_e

$ N $ 枚のカードが一列に伏せられており、各カードには整数 $ 1 $ または $ 2 $ が書かれています。

$ i $ 番目のカードに書かれている整数を $ A_i $ とします。

あなたの目的は $ A_1,\ A_2,\ ...,\ A_N $ を当てることです。

次のことが分かっています。

- $ i\ =\ 1,\ 2,\ ...,\ M $ について $ A_{X_i}\ +\ A_{Y_i}\ +\ Z_i $ は偶数である。

あなたは魔法使いです。次の魔法を何度でも使うことができます。

**魔法**: コストを $ 1 $ 払う。カードを $ 1 $ 枚選び、そのカードに書かれた整数 $ A_i $ を知る。

最小で何コスト払えば、$ A_1,\ A_2,\ ...,\ A_N $ 全てを確実に当てることができるでしょうか。

なお、与えられる入力には矛盾がないことが保証されます。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ X_i\ <\ Y_i\ \leq\ N $
- $ 1\ \leq\ Z_i\ \leq\ 100 $
- $ (X_i,\ Y_i) $ の組は互いに異なる。
- 与えられる入力には矛盾がない(すなわち、条件を満たす $ A_1,\ A_2,\ ...,\ A_N $ が存在する)。

### Sample Explanation 1

$ 1 $ 枚目と $ 3 $ 枚目のカードに対してそれぞれ $ 1 $ 回ずつ魔法を使えば、$ A_1,\ A_2,\ A_3 $ 全てを当てることができます。

## 样例 #1

### 输入

```
3 1
1 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
6 5
1 2 1
2 3 2
1 3 3
4 5 4
5 6 5```

### 输出

```
2```

## 样例 #3

### 输入

```
100000 1
1 100000 100```

### 输出

```
99999```

# 题解

## 作者：徐晨轩✅ (赞：5)

# $ \mathtt{Description} $

> 你有 $ n $ 张卡片，每张卡片上有一个数字，这个数字不是 $ 1 $ 就是 $ 2 $。
>
> 你知道：对于每一个 $ i=1,2,\dots,M $，$ A_{X_i}+A_{Y_i}+Z_i $ 是偶数。
>
> **魔法**：翻开一张牌，知道上面的数字是什么。
>
> 问：最少用几次魔法，知道每一张牌上面的数字。

# $ \mathtt{Solution} $

标签：并查集

难度：普及/提高-

分析：因为每张卡片上的数字只能是 $ 1 $ 或者 $ 2 $，所以如果我们知道了 $ A_{X_i} $ 或者 $ A_{Y_i} $，我们就能根据 $ Z_i $ 知道另外一个。用并查集就能轻松解决。（其实根本用不到 $ Z $）

# $ \mathtt{Code} $

```cpp
#include <stdio.h>
int n,m,x,y,z,ans,f[100001];
int find(int x)
{
	if(f[x]!=x)f[x]=find(f[x]);
	return f[x];
}
void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	f[fx]=fy;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		merge(x,y);
	}
	for(int i=1;i<=n;i++)
		if(f[i]==i)
			ans++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Take_A_Single_6 (赞：3)

## 题意概括
给你一个1和2构成的序列，并告诉你其中两个数与另外一个数相加和为偶数，让你求还要知道序列中的几个数才能得到整个序列。

## 解题思路
如果我们知道两个数的奇偶性，那么我们只要知道其中一个数我们就可以知道另一个数。**所以，这些数就被这些奇偶关系联系起来了！**  
接着，我们只要看这个序列被这些奇偶关系分成了几个部分，一个部分只要知道一个数就能知道别的数。显而易见，这是**并查集**。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int q[100005];
int bcj(int f)//并查集路径压缩板子，不会请跳转P3367
{
    if(q[f]==f)return f;
    return q[f]=bcj(q[f]);
}
int main()
{
    int n,m,x,y,z,ans=0;
    cin>>n>>m;
    for(int i=0;i<n;i++)//初始化，序列被分为n个部分
        q[i]=i;
    for(int i=0;i<m;i++)
    {
        cin>>x>>y>>z;
        q[bcj(x--)]=bcj(y--);//注意从0开始
    }
    for(int i=0;i<n;i++)
        if(q[i]==i)//分成的部分数就是答案
            ans++;
    cout<<ans<<endl;//十年AT一场空，不加换行见祖宗！！1
    return 0;
}
```

---

## 作者：我是小何子啊 (赞：2)

**前置芝士：**
并查集 P3367 【模板】并查集

**思路：**
这题可以用并查集来做。

为什么？

我们可以推理一下：有一些数，只由1和2组成，**如果我们知道其中的两个数和的奇偶性，那我们是不是只知道这其中一个数就能推出这两个数分别是几**。我们可以用并查集来记录两个数的关系，以此来递推，把有关系的组成一个“家庭”，这些有关系的只用知道其中一个数就能知道整个家庭中别的数。到时候只有计算有多少个家庭和多少个没有关系的数即可。

代码：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e6+5;
int n,m,a,b,c,ans,f[N],vis[N];
inline int read(){//快读
    int x=0,f=0;
	char ch=getchar();
    while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return f?-x:x;
}
int find(int x){//查找这个大家庭的祖父
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i) f[i]=i;
	for(int i=1;i<=m;++i){
		a=read(),b=read(),c=read();
		f[find(b)]=f[find(a)];//a和b有关系，把a和b组成一个家庭
	}
	for(int i=1;i<=n;++i){
		int k=find(i);
		if(!vis[k]){//没有标记，说明还不确定它的关系，++ans
			++ans;
			vis[k]=1;//标记我们已经知道它是什么数了
		}
	}
	printf("%d",ans);//输出
	return 0;
}
```


---

## 作者：龙潜月十五 (赞：1)

## 一、前言

这是一道 **并查集** 裸题，但是它的难度主要在它的 **思维含量** 上，也就是说我们是怎么想到用并查集来做的。

## 二、题意

有一个长度为 $n$ 的数列，序列中 **只有 $1$ 和 $2$**。你不知道数列具体内容，但是你知道 $m$ 组关系，第 $i$ 组关系为 $a_{x_i}+a_{y_i}+z_i \equiv 0 \ (mod \ 2)$。在知道这些关系后，问你 **最少** 要确定多少个数列中的数才能确定整个数列。

## 三、思路

显然一眼看过去以为会是什么数学题，绝不会和并查集挂上钩。但是我们深入思考一下会发现：每一组的关系，实际上告诉我们的是 $a_{x_i}$ 和 $a_{y_i}$ 的关系，与 $z_i$ 无关。

什么意思呢？我们举个例子，就拿样例二来说：

| $x_i$ | $y_i$ | $z_i$ |
| :----------: | :----------: | :----------: |
| $1$ | $2$ | $1$ |
| $2$ | $3$ | $2$ |
| $1$ | $3$ | $3$ |
| $4$ | $5$ | $4$ |
| $5$ | $6$ | $5$ |

通过第一个关系，我们可以知道
$a_1+a_2+1$ 是个偶数，而 $1$ 是个奇数，说明 $a_1+a_2$ 也是个奇数，而因为数列中 **只有 $1$ 和 $2$**，那么说明 $a_1$ 和 $a_2$ 中肯定有一个是 $1$，有一个是 $2$，**只需要确定其中一个就能确定另一个**。

通过第二个关系，我们可以知道 $a_2+a_3+2$ 是偶数，而 $2$ 是个偶数，说明 $a_2+a_3$ 是个偶数。因此 $a_1$ 和 $a_2$ 要么都是 $1$，要么都是 $2$，也是**只需要确定其中一个就能确定另一个**。

因此，我们得出结论：**无论 $z_i$ 是多少，我们通过一个关系，都可以确定 $a_{x_i}$ 和 $a_{y_i}$ 的关系，只要知道其中一个就可以知道其他与它有关的所有数字**。于是我们就可以知道这道题要用 **并查集** 来做。

用并查集维护每个 $a_{x_i}$ 和 $a_{y_i}$ 的关系，最后统计一下 **联通块的个数** 就是答案了。

## 四、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int fa[1000000],ans,maxn,n,m,x,y,z,b[1000000];

int find(int x)
{
	if(x==fa[x])
		return x;
	return fa[x]=find(fa[x]);
}

void con(int x,int y)
{
	x=find(x),y=find(y);
	if(x!=y)
		fa[x]=y;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		con(x,y);
	}
	for(int i=1;i<=n;i++)
		b[find(i)]=1;
	for(int i=1;i<=n;i++)
		if(b[i])
			ans++;
	printf("%d\n",ans);
}
```

## 五、后记

这题之前模拟赛就做过，不过现在才看到。

此题的思维转换非常的妙，故写下记录。

---

## 作者：LLGZ (赞：1)

### 翻译和分析

输入$n,m$

输入$n$个数，
$n$个数中只有1和2

这时你肯定不知道哪个数是1哪个数是2,

所以再输入$m$个提示，
每个提示有三个数$x,y,z$。

$x+y+z$为偶数,所以x和y的关系就知道了

所以
在每次提示时要把他们放到一个集合里，需要合并两个集合

（这里就要用到一个数据结构**并查集**，相信刷到这个题的OIer肯定已经熟练掌握了并查集，这里不再多讲，想做题的可以[戳这里](https://www.luogu.com.cn/training/3065)）

当你看到这里的时候应该已经懂了，**并查集模板题**

只不过多了个↓
```cpp
void mer(int x,int y)
{
	if(find(x)!=find(y))
	f[find(x)]=find(y);
}
```
也就是合并并查集

最后检查并未合并过的个数$++sum$即可

贴上代码
```cpp
#include<iostream>
using namespace std;

int n,m;
int f[1000010];
int sum;
bool biaoji[1000010];
int find(int x)
{
	if(x==f[x])
	return x;
	
	return f[x]=find(f[x]);//小小的路径压缩
}

void mer(int x,int y)
{
	if(find(x)!=find(y))//头子不是同一个就合并
	f[find(x)]=find(y);
}
int main()
{
	cin>>n>>m;
	
	for(int i=1;i<=n;i++)
	f[i]=i;
	
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		mer(x,y);//合并合并
	}
	
	for(int i=1;i<=n;i++)
	{
       if(!biaoji[find(i)])
       {
       	biaoji[f[i]]=1;
       	sum++;
       }
	}
	
	cout<<sum <<endl;//岛国传统QAQ
	return 0;
}
```




---

## 作者：Warriors_Cat (赞：0)

## 题解 AT4756 【[ABC126E] 1 or 2】

### $Description:$

有 $n$ 个数，它们非 $1$ 即 $2$，给你 $m$ 个提示，每个提示告诉你两个数加上 $z$ 后为偶数，问你至少要知道几个数才能知道所有数。

### $Solution:$

这道题最初还以为是道构造题，其实它是一道裸的并查集。

由于我们知道 $A_{X_i}+A_{Y_i}+Z$，所以我们知道这两个数的关系。

于是我们把它们放到一个集合里，也就相当于并查集的合并。

有 $m$ 次操作就进行 $m$ 次合并。

最后，如果知道一个集合里的某个数，那这个集合里面的所有数就都知道了，因为这几个数非 $1$ 即 $2$。

于是统计集合数量即可。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, x, y, z, f[100010], ans;
bool vis[100010];
inline int anc(int x){
	if(x == f[x]) return x;
	return f[x] = anc(f[x]);
}//路径压缩并查集
inline void Union(int x, int y){
	int fx = anc(x), fy = anc(y);
	if(fx != fy) f[fx] = fy;
	return;
}//合并
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) f[i] = i;
	for(int i = 1; i <= m; ++i){
		scanf("%d%d%d", &x, &y, &z);
		Union(x, y);
	}
	for(int i = 1; i <= n; ++i){
		if(!vis[anc(i)]){
			vis[f[i]] = 1;
			ans++;
		}
	}//统计数量
	printf("%d\n", ans);//输出，记得 AT 题要换行
	return 0;
}
```
## End

---

