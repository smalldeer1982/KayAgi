# 舞踏会 (Ball)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2015ho/tasks/joi2015ho_d

IOI 王国では，王女である JOI 姫の誕生日を祝って舞踏会が開かれることになった．

舞踏会には $ N $ 人の貴族が参加する予定である．$ N $ は奇数である．貴族には $ 1 $ から $ N $ までの番号が付けられている．それぞれの貴族には踊りのうまさという整数が定められており，貴族 $ i $ ($ 1\ \leqq\ i\ \leqq\ N $) の踊りのうまさは $ D_i $ である．

舞踏会では JOI 姫を含む $ N\ +\ 1 $ 人で $ 2 $ 人ずつ組を作って踊る．IOI 王国では，上級者が初級者を補助できるように，伝統的に以下の方法で踊りの組を決定している．

- 最初に，$ N $ 人の貴族が $ 1 $ 列に並ぶ．
- 列に並んでいる貴族が $ 1 $ 人になるまで，以下の操作を繰り返す．
  - 列の先頭から $ 3 $ 人の貴族の踊りのうまさを調べる．
  - その $ 3 $ 人の貴族の中で，最も踊りのうまさが大きい貴族を $ A $ とおく．ただし，複数いる場合は，最も踊りのうまさが大きい貴族の中で，最も番号の小さい貴族 を $ A $ とおく．
  - その $ 3 $ 人の貴族の中で，最も踊りのうまさが小さい貴族を $ B $ とおく．ただし，複数いる場合は，最も踊りのうまさが小さい貴族の中で，最も番号の大きい貴族 を $ B $ とおく．
  - $ A $ と $ B $ が列から抜けて組になる．
  - 残った $ 1 $ 人は列の最後尾に移動する．
- 最終的に残った $ 1 $ 人が JOI 姫と組になる．貴族 $ 1 $ から貴族 $ M $ ($ 1\ \leqq\ M\ \leqq\ N\ -\ 2 $) の $ M $ 人の貴族については，すでに初期状態で列の何番目に並ぶのかが決まっている．残りの $ N\ -\ M $ 人の貴族の並び方は国王が自由に決めることができる．

JOI 姫は踊りを学んだばかりなので，国王は JOI 姫と組になる貴族の踊りのうまさをできるだけ大きくしたいと考えている．JOI 姫と組になる貴族の踊りのうまさとして考えられる最大値を求めよ．

## 说明/提示

### 課題

それぞれの貴族の踊りのうまさと，$ M $ 人の貴族の初期状態で並ぶ場所が与えられたとき，JOI 姫と組になる貴族の踊りのうまさとして考えられる最大値を求めるプログラムを作成せよ．

- - - - - -

### 制限

すべての入力データは以下の条件を満たす．

- $ 3\ \leqq\ N\ \leqq\ 99\,999 $．
- $ N $ は奇数である．
- $ 1\ \leqq\ M\ \leqq\ N\ -\ 2 $．
- $ 1\ \leqq\ D_i\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ i\ \leqq\ N $)．
- $ 1\ \leqq\ P_i\ \leqq\ N $ ($ 1\ \leqq\ i\ \leqq\ M $)．
- $ P_i\ \neq\ P_j $ ($ 1\ \leqq\ i\ <\ j\ \leqq\ M $)．

### 小課題

#### 小課題 1 \[8 点\]

- $ N\ \leqq\ 9 $ を満たす．

#### 小課題 2 \[16 点\]

- $ N\ \leqq\ 19 $ を満たす．

#### 小課題 3 \[44 点\]

- $ N\ \leqq\ 1\,999 $ を満たす．

#### 小課題 4 \[32 点\]

追加の制限はない．

- - - - - -

### Sample Explanation 1

初期状態では $ 3 $ 人の貴族の並ぶ場所がすでに決まっている． !\[\](https://img.atcoder.jp/joi2015ho/d-1.png)括弧内の数字は踊りのうまさを表す．左端が列の先頭である． 例えば，先頭から順に貴族 $ 5 $，貴族 $ 1 $，貴族 $ 4 $，貴族 $ 6 $，貴族 $ 2 $，貴族 $ 3 $，貴族 $ 7 $ という順番に並んだ場合を考える． !\[\](https://img.atcoder.jp/joi2015ho/d-2.png)すべての貴族が並んだあとの配置 この場合，以下のように列が変化していく． - 列の先頭の $ 3 $ 人の貴族 (貴族 $ 5 $，貴族 $ 1 $，貴族 $ 4 $) 中で，最も踊りのうまさが大きい貴族 $ 4 $ と最も踊りのうまさが小さい貴族 $ 5 $ が組になり，残った貴族 $ 1 $ が最後尾に移動する． - 次に，列の先頭の $ 3 $ 人の貴族 (貴族 $ 6 $，貴族 $ 2 $，貴族 $ 3 $) の中で，最も踊りのうまさが大きい貴族は貴族 $ 6 $ と貴族 $ 3 $ の $ 2 $ 人であり，このうち番号の小さい貴族は貴族 $ 3 $ である．また，列の先頭の $ 3 $ 人の貴族のうち最も踊りのうまさが小さい貴族は貴族 $ 2 $ である．貴族 $ 3 $ と貴族 $ 2 $ が組になり，残った貴族 $ 6 $ が最後尾に移動する． - 次に，列の先頭の $ 3 $ 人の貴族 (貴族 $ 7 $，貴族 $ 1 $，貴族 $ 6 $) の中で，最も踊りのうまさが大きい貴族 $ 7 $ と最も踊りのうまさが小さい貴族 $ 1 $ が組になり，残った貴族 $ 6 $ が最後尾に移動する． - 最終的に貴族 $ 6 $ が残り，JOI 姫と組になる．貴族 $ 6 $ の踊りのうまさは $ 8 $ である．この値が JOI 姫と組になる貴族の踊りのうまさとして考えられる最大値である． !\[\](https://img.atcoder.jp/joi2015ho/d-3.png)列の変化の様子 - - - - - -

### Sample Explanation 2

どのような順番で並んでも，貴族 $ 2 $ と JOI 姫が組になる． - - - - - -

## 样例 #1

### 输入

```
7 3
5 2
5 5
8 6
6
2
8
9```

### 输出

```
8```

## 样例 #2

### 输入

```
3 1
5 3
5
5```

### 输出

```
5```

## 样例 #3

### 输入

```
7 2
32 4
27 6
37
41
41
30
27```

### 输出

```
37```

# 题解

## 作者：WAAutoMaton (赞：3)

[由于latex原因，本文在我的博客上阅读体验可能更好（逃](https://waautomaton.tk/2018/08/07/loj-2727-%E9%A2%98%E8%A7%A3/)

#### 题解

&emsp;&emsp;又是一道不看题解想不出来...看完题解感觉好简单的题....好吧这次没题解看了，看的是标程...  
&emsp;&emsp;首先二分答案mid，以下称熟练度大于等于i的位置为“满足条件”，否则为“不满足条件”。  
&emsp;&emsp;统计熟练度满足条件的 **自由** 贵族数量，记为cnt。  
&emsp;&emsp;设数组$f_i$表示若要使得第i个位置最终满足条件，所需要的自由贵族数量，可得  
![](https://cdn.luogu.com.cn/upload/pic/44444.png)  
&emsp;&emsp;设当前序列为l~r，则$f_{r+1}$应由$f_l,f_{l+1},f_{l+2}$转移得到。由题意可知，要使新数满足条件，原来的3个数中至少要有2个满足条件，因此新数的f值为原来3个f值中较小的2个的和，然后我们就可以$O(n)$暴力模拟求得最后剩下的那个数的f值，即为要使答案满足条件所需的最少自由贵族数量，与之前算出的cnt比较即可。具体细节可见代码及注释

#### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

template <size_t _I_Buffer_Size = 1 << 23, size_t _O_Buffer_Size = 1 << 23>
struct IO_Tp
{
    //这是读入优化板子，为了阅读体验此部分内容省略。
};
 IO_Tp<> IO;
const int maxn = 100000;
const int inf =INT_MAX/5;
int a[2 * maxn + 10], f[2 * maxn + 10], g[2 * maxn + 10];
int n, m;
int merge(int a,int b,int c)
{
	int x[3]={a,b,c};
	sort(x,x+3);
	return x[0]+x[1];
}
bool check(int mid)
{
    int cnt = 0;
    for (int i = m+1; i <= n; ++i) //统计cnt
        if (a[i] >= mid)
            ++cnt; 
	for(int i=1; i<=n; ++i) { //初始化f数组
		if (g[i]==-1)
			f[i]=1;
		else if (g[i]>=mid)
			f[i]=0;
		else
			f[i]=inf;
	}
	int l=1,r=n;
	while(l<r) { //暴力计算出最终f值
		int t=merge(f[l],f[l+1],f[l+2]);	
		if (t>inf) t=inf;
		l+=3;
		f[++r]=t;
	}
	return f[l]<=cnt; //将f值与cnt比较
}
int main()
{
    iopen();
    IO >> n >> m;
    memset(g, -1, sizeof(g));
    int mxa = 0;
    for (int i = 1; i <= m; ++i) {
        int p;
        IO >> a[i] >> p;
        g[p] = a[i];
    }
    for (int i = m + 1; i <= n; ++i) {
        IO >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        mxa = max(mxa, a[i]);
    }
    int l = 0, r = mxa;
    while (l < r) {//二分答案
        int mid = (l + r + 1) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
	IO<<l<<'\n';
    return 0;
}

---

## 作者：_Fontainebleau_ (赞：2)

### 题意

[原题题面 $\leftarrow\text{Click here.}$ ](https://www.luogu.com.cn/problem/AT2435)

### 做法

我们可以试着将原题中一条线上的选拔过程，拔高成  **三叉树**，便于理解。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dc0m6q4p.png)

它的根就是最后的答案。是不是稍微清晰了一些？

这道题要我们求最大值，显然想到 **二分**，但是最后的答案好像不具单调性啊，怎么办？这里又是一个很巧妙的转换。我们二分 $mid$，然后统计让当前点 $x$ **大于等于** $mid$ 所需的自由点（就是后面 $m+1\sim{n}$ 的可自由摆放的贵族的数量）个数 $f_x$ 就可以了。$f_x$ 显然等于 $f_{x-1},f_{x-2},f_{x-3}$ 中最小两个的和（这里是把整个过程压回平面，节点自下往上自左往右一层层按顺序编号）。然后看最后的根需要的 $\ge{mid}$ 自由点个数和实际个数谁大谁小即可。复杂度是 $O(n)$ 的。外面套个二分，就是 $O(n\log{n})$。

注意上文的加粗的 **大于等于** 是保证单调性的关键。因为每次我都包含了这样往后一个区间，只要区间里有答案，那就可以，直到推到答案跑出区间，就不行了。具体如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8r5y9ojg.png)

其中 $\color{purple}\text{purple}$ 部分表示合法答案，$\color{red}\text{red}$ 表示二分时合法的区间，$\color{grey}\text{grey}$ 表示二分时不和法的区间。容易发现，此时答案具有单调性。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f;
int n,m;
int a[400005],b[400005],f[400005];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline int calc(int x,int y,int z)
{
	return x+y+z-max(x,max(y,z));
}
inline bool check(int x)
{
	int cnt=0,l=1,r=n;
	for(int i=m+1;i<=n;i++)	if(a[i]>=x)	cnt++;
	for(int i=1;i<=n;i++)
	{
		if(!b[i])	f[i]=1;
		else if(b[i]>=x)f[i]=0;
		else	f[i]=inf;
	}
	while(l<r)
	{
		int vl=calc(f[l],f[l+1],f[l+2]);
		if(vl>inf)	vl=inf;
		l+=3,f[++r]=vl;
	}
	return f[r]<=cnt;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		a[i]=read();int x=read();
		b[x]=a[i];
	}
	for(int i=m+1;i<=n;i++)	a[i]=read();
	int l=1,r=1e9,ans;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))	ans=mid,l=mid+1;
		else	r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```



---

