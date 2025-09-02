# Double Landscape

## 题目描述

[problemUrl]: https://atcoder.jp/contests/keyence2019/tasks/keyence2019_d

$ N $ 行 $ M $ 列のグリッドに，$ 1 $ から $ N\ \times\ M $ までの整数を重複のないように $ 1 $ つずつ書き込むことを考えます． ここで，普通に書き込むのでは面白くないと思った高橋君は，以下の条件を満たすように数を書き込むことにしました．

- $ i $ 行目に書き込まれている値のうち，最大の値は $ A_i $ $ (1\ \leq\ i\ \leq\ N) $
- $ j $ 列目に書き込まれている値のうち，最大の値は $ B_j $ $ (1\ \leq\ j\ \leq\ M) $

高橋君のために，この条件を満たすような書き込み方の個数を $ 10^9\ +\ 7 $ で割ったあまりを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ M\ \leq\ 1000 $
- $ 1\ \leq\ A_i\ \leq\ N\ \times\ M $
- $ 1\ \leq\ B_j\ \leq\ N\ \times\ M $
- $ A_i,\ B_j $ は整数

### Sample Explanation 1

$ (A_1,\ A_2)\ =\ (4,\ 3) $，$ (B_1,\ B_2)\ =\ (3,\ 4) $ であり，この場合は以下の $ 2 $ 通りの書き込み方があります． - $ 1 $ 行 $ 1 $ 列目に $ 1 $，$ 1 $ 行 $ 2 $ 列目に $ 4 $，$ 2 $ 行 $ 1 $ 列目に $ 3 $，$ 2 $ 行 $ 2 $ 列目に $ 2 $ - $ 1 $ 行 $ 1 $ 列目に $ 2 $，$ 1 $ 行 $ 2 $ 列目に $ 4 $，$ 2 $ 行 $ 1 $ 列目に $ 3 $，$ 2 $ 行 $ 2 $ 列目に $ 1 $

### Sample Explanation 2

どのような書き込み方をしても条件を満たすことができないので，$ 0 $ を出力します．

## 样例 #1

### 输入

```
2 2
4 3
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
5 9 7
3 6 9```

### 输出

```
0```

## 样例 #3

### 输入

```
2 2
4 4
4 4```

### 输出

```
0```

## 样例 #4

### 输入

```
14 13
158 167 181 147 178 151 179 182 176 169 180 129 175 168
181 150 178 179 167 180 176 169 182 177 175 159 173```

### 输出

```
343772227```

# 题解

## 作者：Natori (赞：0)

难度建议绿或蓝

# 题意简述

把 $\left[ 1,n \times m \right]$ 中的所有整数**不重复**地写在一个 $n \times  m$ 的网格中，需要遵循以下规则：

- 第 $i(1 \leq i \leq n)$ 行中的最大值是 $a_i$

- 第 $j(1 \leq j \leq m)$ 列中的最大值是 $b_j$

给定数列 $\left\{ a_n \right\}$，$\left\{ b_m \right\}$，求填数的方案数，结果对 $10^9+7$ 取模。

### 数据范围

$1 \leq n,m \leq 1000$，$1 \leq a_i,b_j \leq 1000$，保证 $a_i,b_j$ 是整数。

------------
~~可以直接把题意简述作为翻译~~

# Solution

## 分析

计数题，比较考查思维。

发现如果从大到小填数，由于后面要填的数都比前面已经填好的数小，所以之后不管怎么填都不会影响每一行和每一列的最大值。

下面为方便描述，称一行或一列**被覆盖**，当这一行或列已经填了至少一个数。

设当前已经被覆盖的行数和列数分别为 $nn$ 和 $mm$，记答案为 $ans$，对当前要填的每个数进行分类讨论：

- 有一行**和**一列以它为最大值，此时填的位置固定；

- 有一行**或**一列以它为最大值，此时它只能填在那一行或一列一个被覆盖的位置上，$ans \gets ans \times nn$ 或 $ans \gets ans \times mm$；

- **没有**行和列以它为最大值，此时它只能填在一个行列都被覆盖的位置上，即一个交点上，$ans \gets ans \times (nn \times mm - al)$，其中 $al$ 表示当前**已经**填了多少数。

时间复杂度 $\mathcal{O(nm)}$，可以通过本题。

## 代码

写出来大概 $\text{1.35KB}$，码量不大。

别忘了 $\bmod 10^9+7$，有的地方要开 ```long long```。~~说实话变量名有点奇怪，但没有关系~~

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
inline ll read(){
	ll f=1,x=0;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	return f*x;
}
inline void write(ll x){
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const int N=1010,M=1010;
const ll mod=1e9+7;
int n,m,a[N],b[M];
int cn[N*M],cm[N*M],pn[N*M],pm[N*M];//N*M相当于值域 
ll ans=1,al,nn,mm,val;
int main(){
	memset(pn,-1,sizeof(pn));
	memset(pm,-1,sizeof(pm));
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		cn[a[i]]++;
		pn[a[i]]=i;
	}
	for(int i=1;i<=m;i++){
		b[i]=read();
		cm[b[i]]++;
		pm[b[i]]=i;
	}
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--){
			val=1ll*((i-1)*m+j);//当前要填的数 
			if(pn[val]!=-1&&pm[val]!=-1){
				nn++;
				mm++;
			}
			else if(pn[val]!=-1){
				if(mm==0){
					printf("0");
					return 0;
				}
				(ans*=mm)%=mod;
				nn++;
			}
			else if(pm[val]!=-1){
				if(nn==0){
					printf("0");
					return 0;
				}
				(ans*=nn)%=mod;
				mm++;
			}
			else{
				if(nn*mm-al==0){
					printf("0");
					return 0;
				}
				(ans*=(nn*mm-al))%=mod;
			}
			al++;
		} 
	write(ans);
	return 0;
}
/*
2022.7.28 11:05 started considering
2022.7.28 11:27 started coding
2022.7.28 11:49 finished debugging
*/
```

---

