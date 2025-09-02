# Brackets

## 题目描述

A two dimensional array is called a bracket array if each grid contains one of the two possible brackets — "(" or ")". A path through the two dimensional array cells is called monotonous if any two consecutive cells in the path are side-adjacent and each cell of the path is located below or to the right from the previous one.

A two dimensional array whose size equals $ n×m $ is called a correct bracket array, if any string formed by writing out the brackets on some monotonous way from cell $ (1,1) $ to cell $ (n,m) $ forms a correct bracket sequence.

Let's define the operation of comparing two correct bracket arrays of equal size ( $ a $ and $ b $ ) like that. Let's consider a given two dimensional array of priorities ( $ c $ ) — a two dimensional array of same size, containing different integers from $ 1 $ to $ nm $ . Let's find such position $ (i,j) $ in the two dimensional array, that $ a_{i,j}≠b_{i,j} $ . If there are several such positions, let's choose the one where number $ c_{i,j} $ is minimum. If $ a_{i,j}= $ "(", then $ a&lt;b $ , otherwise $ a&gt;b $ . If the position $ (i,j) $ is not found, then the arrays are considered equal.

Your task is to find a $ k $ -th two dimensional correct bracket array. It is guaranteed that for the given sizes of $ n $ and $ m $ there will be no less than $ k $ two dimensional correct bracket arrays.

## 说明/提示

In the first sample exists only one correct two-dimensional bracket array.

In the second and in the third samples two arrays exist.

A bracket sequence is called regular if it is possible to obtain correct arithmetic expression by inserting characters «+» and «1» into this sequence. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

## 样例 #1

### 输入

```
1 2 1
1 2
```

### 输出

```
()
```

## 样例 #2

### 输入

```
2 3 1
1 2 3
4 5 6
```

### 输出

```
(()
())
```

## 样例 #3

### 输入

```
3 2 2
3 6
1 4
2 5
```

### 输出

```
()
)(
()
```

# 题解

## 作者：MyukiyoMekya (赞：3)

注意到要求所有路径都是合法的括号序列，也就是说把 `(`  算为 $+1$ ，`)` 算为 $-1$，那么对于 $(i,j)$ ，$(i-1,j)$ 和 $(i,j-1)$ 的括号和一定是相同的，所以我们可以推出一个重要性质：同一斜对角线的位置相同

```plain
abcde
bcdef
cdefg
defgh
efghi	// 字母相同的括号相同
```

那么很显然，在最终的排名中，这些相同位置中优先级最大的会做出贡献，

然后发现同一斜对角线相同所以直接可以弄成序列问题，比如上面的变成 `abcdefghi` ，填括号使得是个合法的的括号序列，

并且按照上面处理出来的优先级找第 $k$ 大的就行了。

那就直接二分答案序列，记 $p_i$ 为优先级第 $i$ 大的位置，那就先把 $p_1$ 填为 `(` ，然后 dp 算下方案数，加起来有没有大于等于 $k$ ，大于等于了就去确定 $p_2$ ，小于了就把这个位置改为 `)`，然后再去确定 $p_2$ $\cdots$ ，直到都确定完。时间复杂度 $\mathcal O(n^3)$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ALL(x) (x).begin(),(x).end()
#define mem(x,y) memset(x,y,sizeof x)
#define ln std::puts("")
#define pb push_back
#define MP std::make_pair
const int MaxN=205;
const int lim=1e18+5;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
int a[MaxN][MaxN],p[MaxN],t[MaxN],n,m,K,q;
int b[MaxN],f[MaxN][MaxN];
inline void add(int &x,int y){(x+=y)>=lim&&(x=lim);}
inline int calc()
{
	std::mem(f,0);
	f[0][0]=1;
	for(int i=1;i<=q;++i)
	{
		if(b[i]>=0)
			for(int j=1;j<=q;++j)
				add(f[i][j],f[i-1][j-1]);
		if(b[i]<=0)
			for(int j=0;j<q;++j)
				add(f[i][j],f[i-1][j+1]);
	}
	return f[q][0];
}
signed main(void)
{
	read(n,m,K);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			read(a[i][j]);
	{
		std::vector<std::pair<int,int> > dr;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				dr.pb(MP(a[i][j],i+j-1));
		std::sort(ALL(dr));
		reg int cnt=0;
		for(auto i:dr)
			if(!p[i.second])
				p[i.second]=++cnt;
		for(int i=1;i<=cnt;++i)
			t[p[i]]=i;
		for(int i=1;i<=cnt;++i)
			p[i]=t[i];
	}
	q=n+m-1;
	reg int sum=0;
	for(int i=1;i<=q;++i)
	{
		b[p[i]]=1;
		reg int t=calc();
		if(sum+t>=K)
			continue;
		b[p[i]]=-1;
		sum+=t;
	}
	for(int i=1;i<=n;++i,ln)
		for(int j=1;j<=m;++j)
			std::putchar(b[i+j-1]>0?'(':')');
	return 0;
}
```





---

