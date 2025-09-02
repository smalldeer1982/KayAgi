# [ARC132C] Almost Sorted

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc132/tasks/arc132_c

$ 1,\dots,\ n $ と $ -1 $ からなる数列 $ a_1,\dots,a_n $ と整数 $ d $ が与えられます。 以下の条件を満たす数列 $ p_1,\dots,p_n $ はいくつありますか？ 答えを $ 998244353 $ で割ったあまりを出力してください。

- $ p_1,\dots,p_n $ は $ 1,\dots,\ n $ の順列
- $ i=1,\dots,n $ について、 $ a_i\neq\ -1 $ ならば $ a_i=p_i $ （つまり、$ a_1,\dots,a_n $ の $ -1 $ の項を適切に置き換えることで $ p_1,\dots,p_n $ に書き換えできる）
- $ i=1,\dots,n $ について、 $ |p_i\ -\ i|\le\ d $

## 说明/提示

### 制約

- $ 1\ \le\ d\ \le\ 5 $
- $ d\ <\ n\ \le\ 500 $
- $ 1\le\ a_i\ \le\ n $ または $ a_i=-1 $
- $ a_i\neq\ -1 $ ならば $ |a_i-i|\le\ d $
- $ i\neq\ j $ かつ $ a_i,\ a_j\ \neq\ -1 $ ならば $ a_i\neq\ a_j $
- 入力はすべて整数

### Sample Explanation 1

$ (3,2,1,4) $ と $ (3,4,1,2) $ が条件を満たします。

### Sample Explanation 2

$ -1 $ を置き換えて得られる $ 1,2,3,4,5 $ の順列は $ (2,3,4,5,1) $ のみです。 この順列は、$ 5 $ 項目が条件を満たさないため、答えは $ 0 $ です。

### Sample Explanation 3

$ 998244353 $ で割ったあまりを出力してください。

## 样例 #1

### 输入

```
4 2
3 -1 1 -1```

### 输出

```
2```

## 样例 #2

### 输入

```
5 1
2 3 4 5 -1```

### 输出

```
0```

## 样例 #3

### 输入

```
16 5
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1```

### 输出

```
794673086```

# 题解

## 作者：Obviathy (赞：13)

## Solution

本人太菜了，以至于不看标签不知道这是状压。

定义 $f_{i,S}$ 记录到第 $i$ 个位置时，它可以填的数与下标的差值的集合的答案。

我们发现这个差值的绝对值不超过 $d$，$d \le 5$ 所以最多只有 $11$ 种，状态压缩必然可行。

现在考虑如何转移。

首先我们枚举位置 $i$ 和集合 $S$。这里的集合 $S$ 指的是上一个位置，即 $i-1$ 时填的数的集合。

然后我们枚举该位置上能填的数：考虑枚举差值：
- 因为保证 $p$ 是一个排列，所以第 $i$ 个位置选的数一定不能在集合 $S$ 中存在；
- 需要保证现在选的数时可以选到的，即要么这个位置随意填数，要么这个位置本来就是要填的数；
- 保证不能越界。

满足以上条件之后，就可以进行状态转移了。方程为：
```cpp
f[i][(j | (1<<(d+k))) >> 1] = (f[i][(j | (1<<(d+k))) >> 1]+f[i-1][j])%mod
```
解释一下:

现在我们要对第 $i$ 个阶段进行决策，它的答案取决于我们所枚举的上一个阶段与那个集合对应的状态即 $f_{i-1,S}$（代码中用`j`）。

我们刚才枚举了一些差值，从中的到了一些合法的差值，这些差值在 $i-1$ 时没用过，现在要用了，所以就位运算把那一位变成 $1$（基本的操作了）。又因为我们的集合 $S$ 是 $i-1$ 的，所以对于现在的阶段 $i$，其每一个差值都要减小 $1$，那么右移一下即可。

## AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 505,mod = 998244353;
int n,d;
int a[N],f[N][2000];
int main(){
	cin >> n >> d;
	for(int i = 1;i <= n;i ++)cin >> a[i];
	f[0][0] = 1;
	for(int i = 1;i <= n;i ++)
		for(int j = 0;j < 1<<(d+d+1);j ++){
			if(!f[i-1][j])continue;
			for(int k = -d;k <= d;k ++)
				if((j>>(d+k)&1) == 0 && (a[i] == -1 || a[i] == k+i) && k+i <= n && k+i >= 1)f[i][(j | (1<<(d+k))) >> 1] = (f[i][(j | (1<<(d+k))) >> 1]+f[i-1][j])%mod;
		}
	cout << f[n][(1<<d)-1] << endl;
	return 0;
} 
```

---

## 作者：cjh20090318 (赞：5)

做这道题的时候注意到了同名题目 [CF1730F Almost Sorted](https://www.luogu.com.cn/problem/CF1730F)，没想到都是状压 DP。

## 题意

参见[题意翻译](https://www.luogu.com.cn/problem/AT_arc132_c)。

## 分析

$d \le 5$ 的数据范围非常小，很容易想到状压。

设 $f_{i,S}$ 表示前 $i$ 个数 $[i-d,i+d]$ 的占用情况（不包含已经确定的）为 $S$ 时的方案数。

如果第 $i$ 个数已经确定，那么直接从 $i-1$ 的状态进行转移。

否则就枚举每一个可能的位置，再从上一个进行转移即可。

因为不好描述具体实现就看代码吧，时间复杂度 $O(nd2^d)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cmath>
using namespace std;
const int mod=998244353;
int n,d,a[505],p[505];
int f[505][1<<11];
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(~a[i]){
			p[a[i]]=i;
			if(abs(a[i]-i)>d) return puts("0"),0; //已经确定的不符合条件直接判无解。
		}
	}
	**f=1;
	for(int i=1,mS=1<<(d<<1|1);i<=n;i++)
		if(p[i])for(int S=0;S<mS;++S){
			bool fl=1;
			for(int j=-d;j<=d;j++)if((i+j<1||i+j>n||~a[i+j])&&((S>>(j+d))&1)){fl=0;break;}//判断是否有被占用的不合法位置。
			if(fl)
				f[i][S]=(f[i-1][(S<<1)&(mS-1)]+f[i-1][(S<<1|1)&(mS-1)]);//从上一个状态转移，有两种情况。
		}
		else for(int S=0;S<mS;++S){
			bool fl=1;
			for(int j=-d;j<=d;j++)if((i+j<1||i+j>n||~a[i+j])&&((S>>(j+d))&1)){fl=0;break;}
			if(fl)for(int j=-d;j<=d;j++)if((S>>(j+d))&1)
				f[i][S]=(f[i][S]+(long long)f[i-1][((S^(1<<(j+d)))<<1)&(mS-1)]+f[i-1][((S^(1<<(j+d)))<<1|1)&(mS-1)])%mod;
		}
	int ans=0;
	for(int S=0,mS=1<<(d<<1|1);S<mS;++S)ans=(ans+f[n][S])%mod;//将所有情况求和。
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：3)

萌萌状压题。

显然要以 $i$ 前缀长度为阶段。

由于要求是个排列，我们就需要知道当前位之前有哪些数是填过的。

看到 $d$ 很小，那不难想到设计状态：$f_{i,S}$ 为 $i$ 前缀，$[i-d,i+d]\cap[1,n]$ 中整数是否被填的状态为 $S$ 的方案数。

转移自然是枚举当前位要填什么，然后将影响更新状态 $S$ 即可。

初值 $f_{0,0}=1$，答案是 $f_{n,2^d-1}$。

细节看代码：

```cpp
const int N=503,B=1<<11|3,_B=B^3,p=998244353;
il void Add(int&x,int y){return (x+=y)<p||(x-=p),void();}
bool*MS;
int n,m,a[N],f[N][B];
bool*MT;
void Solve()
{
  rd(n,m),**f=1;
  for(int i=1;i<=n;++i) rd(a[i]);
  for(int i=1;i<=n;++i) for(int j=0;j<1<<(m<<1|1);++j)
    if(~a[i])
      if(sd abs(a[i]-i)>m) return wrt(0),void();
      else j>>m-i+a[i]&1||(Add(f[i][(j|1<<m-i+a[i])>>1],f[i-1][j]),7);
    else
      for(int k=sd max(1,i-m);k<=sd min(n,i+m);++k) j>>m-i+k&1||(Add(f[i][(j|1<<m-i+k)>>1],f[i-1][j]),7);
  wrt(f[n][(1<<m)-1]);
  return;
}
```

---

## 作者：intel_core (赞：2)

注意到 $d\le 5$，所以每个位置替换 $-1$ 的选择数量最多只有 $11$ 种。

所以我们直接状压维护对于每个 $i$，$[i-5,i+5]$ 内的数的出现情况。

具体来讲，令 $f_{i,S}$ 表示选到了第 $i$ 个，$S$ 代表 $[i-5,i+5]$ 内的数的出现情况。

每次转移把 $S$ 右移一位，再把新加进来的数算进 $S$ 里，碰到 $-1$ 枚举转移即可。

复杂度 $O(2^{2d+1}n)$。

---

