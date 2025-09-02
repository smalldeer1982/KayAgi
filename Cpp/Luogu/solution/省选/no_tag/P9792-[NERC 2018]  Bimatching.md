# [NERC 2018]  Bimatching

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) B 题。

## 题目描述

你与一些好友一起举办了一个舞会！

在这个舞会上，有 $n$ 位男性和 $m$ 位女性，本来舞蹈的形式是一男一女跳的，但是由于男性紧缺，你并不能让所有女性都有一个男性舞伴，于是你发明了一种新的舞蹈形式：一个男性，搭配两个女舞伴。

当然，每个女性在挑选舞伴时，都会对那些男性舞伴做出评价，如果评价是 $1$，说明这位女性愿意和这位男性一起跳舞，只有当两位女性都愿意和那位男性跳舞时，才能成为一对舞伴。

你作为一个组织者，自然要为大家着想，你需要求出能凑出的最多的舞伴对数，**每个舞伴不能重叠**。

## 说明/提示

数据保证 $1 \leq t \leq 20$，$1 \leq n, m$ 且 $n + m \leq 150$。

下图是对样例一和样例二的解释，其中加粗部分表示其中的一种可行方案。

样例一：

![](https://cdn.luogu.com.cn/upload/image_hosting/9dfwv4dr.png)

样例二：

![](https://cdn.luogu.com.cn/upload/image_hosting/woscpjcn.png)

## 样例 #1

### 输入

```
2
2 3
111
111
3 4
0110
1100
0011```

### 输出

```
1
2```

## 样例 #2

### 输入

```
1
3 6
001100
111111
001100```

### 输出

```
2```

# 题解

## 作者：henryhu2006 (赞：1)

二分图匹配，但是一个左部点要恰好匹配两个右部点，求最大匹配。

多测，$\sum (n+m)\le 150$。

## 建图
将左部点（男）拆点成 $x,x'$，对于一条边 $(x,y)$，$(x,y)$ 和 $(x',y)$ 都连边，并连接 $(x,x')$。答案即为一般图最大匹配 $-n$。

证明是容易的。如果一个左部点没有匹配成组，则 $(x,x')$ 必然匹配；如果一个左部点匹配成组，那么一定处于两对匹配，且两个 $y$ 不同。

## 一般图最大匹配
带花树是不好的。由于此题只需要求最大匹配的大小，无需构造方案，且 $n+m$ 不是很大，我们可以使用 [Tutte 矩阵](https://oi-wiki.org/graph/graph-matching/general-match/#%E5%89%8D%E7%BD%AE%E7%9F%A5%E8%AF%86tutte-%E7%9F%A9%E9%98%B5) 来做。

以下参考 OI-Wiki。

具体来讲，对于每条边有个变量，设为 $x_{u,v}$。Tutte 矩阵是 $n\times n$ 的。

- 对于位置 $(i,j)$，$i<j$，如果存在边 $(i,j)$，则值为 $x_{i,j}$。
- 对于位置 $(j,i)$，$i<j$，如果存在边 $(i,j)$，则值为 $-x_{i,j}$。
- 否则为 $0$。

这个矩阵的秩是偶数，且最大匹配即为秩的一半。

变量不好处理，可以每个变量随机权值，可以证明错误率 $<\dfrac{n}{p}$，其中 $n$ 为点数，$p$ 为大质数，取 $10^9+7$ 即可。

于是直接高斯消元。

```cpp
int T,n,m,a[N][N];
mt19937_64 rnd(time(0));
char s[N];
void add(int u,int v){
	int w=rnd()%mod;
	a[u][v]=w,a[v][u]=mod-w;
}
int chk(int x){
	if(x>=mod) x-=mod; return x;
}
void solve(){
	memset(a,0,sizeof(a)),cin>>n>>m;
	for(int i=1;i<=n;++i) add(i,n+i);
	for(int i=1;i<=n;++i){
		scanf("%s",s+1);
		for(int j=1;j<=m;++j)
			if(s[j]=='1') add(i,2*n+j),add(i+n,2*n+j);
	}
	int res=0; m+=2*n;
	for(int i=1;i<=m;++i){
		if(!a[i][i]){
			int r=0;
			for(int j=i+1;j<=m;++j)
				if(a[j][i]){r=j; break;}
			if(!r) continue;
			swap(a[i],a[r]);
		}
		++res;
		for(int j=i+1;j<=m;++j){
			int v=1ll*a[j][i]*ksm(a[i][i],mod-2)%mod;
			for(int k=i;k<=m;++k)
				a[j][k]=chk(a[j][k]-1ll*v*a[i][k]%mod+mod); 
		}
	}
	printf("%d\n",res/2-n);
}
```

---

