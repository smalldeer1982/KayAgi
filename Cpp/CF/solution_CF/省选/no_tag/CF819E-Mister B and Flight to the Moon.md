# Mister B and Flight to the Moon

## 题目描述

为了飞往月球， B 先生需要解决以下问题。

有一个含有 $n$ 个节点的无向完全图。您需要用几个含三条或四条边的环来覆盖它，使每条边正好被两个循环覆盖。

为了更快前往月球， B 先生向你求助。

## 样例 #1

### 输入

```
3
```

### 输出

```
2
3 1 2 3
3 1 2 3
```

## 样例 #2

### 输入

```
5
```

### 输出

```
6
3 5 4 2
3 3 1 5
4 4 5 2 3
4 4 3 2 1
3 4 2 1
3 3 1 5
```

# 题解

## 作者：9AC8E2 (赞：5)

>给定 $n$ 个点的无向完全图,要求使用若干三元环和四元环覆盖这个图,使得每条边恰好被覆盖两次.

考虑数学归纳法.假设已经求出 $n-2$ 个点的无向完全图的覆盖方案,考虑向图中加入两个点 $s,t$ 会发生什么.

考虑加入了什么边:
1. $\forall i\in[1,n-2],\exists s\leftrightarrow i$
2. $\forall i\in[1,n-2],\exists i\leftrightarrow t$
3. $s\leftrightarrow t$


### 若 $n$ 为奇数

将 $[2, n-2]$ 中的所有点分为 $(2,3),(4,5),...,(n-3,n-2)$,对与所有二元组 $(i-1,i)$ 使用四元环 $(s,i-1,t,i)$ 覆盖边 $s\leftrightarrow i-1,s\leftrightarrow i,t\leftrightarrow i-1,t\leftrightarrow i$ 两次

最后使用三元环 $(s,1,t)$ 对 $s\leftrightarrow 1,t\leftrightarrow 1$覆盖两次.

### 若 $n$ 为偶数

使用上面提到的方法覆盖 $[3,n-2]$ 中所有点与 $s,t$ 的连边.

最后使用三元环 $(s,1,t),(s,2,t)$ 与四元环 $(s,1,t,2)$ 覆盖 $s\leftrightarrow 1,s\leftrightarrow 2,t\leftrightarrow 1,t\leftrightarrow 2,s\leftrightarrow t$.

```
int n;
vector<vector<int> >ans;
inline void print(vector<int>x){ans.push_back(x);}
inline void print_f(vector<int>x)
{
	printf("%d ",x.size());
	for(int i:x)printf("%d ",i);
	printf("\n");
}

int main()
{
	read(n);
	if(n&1)
	{
		print({1,2,3});
		print({1,2,3});
		for(int i=5;i<=n;i+=2)
		{
			int s=i-1,t=i;
			print({s,1,t});
			print({s,1,t});
			for(int j=3;j<i;j+=2)
				print({s,j-1,t,j}),
				print({s,j-1,t,j});
		}
	}
	else
	{
		print({1,2,3});
		print({1,2,4});
		print({3,4,1});
		print({3,4,2});
		for(int i=6;i<=n;i+=2)
		{
			int s=i-1,t=i;
			print({s,1,t});
			print({s,2,t});
			print({s,1,t,2});
			for(int j=4;j<i;j+=2)
				print({s,j-1,t,j}),
				print({s,j-1,t,j});
		}
	}
	printf("%d\n",ans.size());
	for(auto i:ans)
		print_f(i);
	return 0;
}
```

---

## 作者：cosf (赞：3)

## [CF819E](https://codeforces.com/problemset/problem/819/E) [B 先生飞去月球](https://www.luogu.com.cn/problem/CF819E)

## 思路

这道题要求给一个构造，并没有要求环数最少。没有这个限制，我们可以想到用递推来解决问题。

经过推导，可以发现 $n$ 个点的情形很难从 $n-1$ 个点的情形转移过来，但是 $n-2$ 是可以的。而且，当 $n=3, 4$ 时很容易得到构造：

$n=3: \{1, 2, 3\}, \{1, 2, 3\}$

$n=4: \{1, 2, 3\}, \{2, 3, 4\}, \{3, 4, 1\}, \{4, 1, 2\}$

那么，如何从 $n$ 转移到 $n+2$ 呢？这个时候，相当于给原来的图增上两个点。令原来的点为 $1$ 到 $n$，新加的为 $n+1$ 和 $n+2$。

由于 $a_1$ 到 $a_n$ 之间每一条边都已经存在于两个环上了，所以新加的环上不能有这些边。

容易想到的一个构造是 $\{i, n + 1, i + 1, n + 2\}$，其中 $i$ 为 $1$ 到 $n-1$ 的每一个点。除此之外，还需要两个环，$\{1, n + 1, n + 2\}$ 以及 $\{n, n + 1, n + 2\}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/47e2cvof.png)

如图，不同的环用了不同的颜色。

根据这个思路，我们就有了构造方案。环的数量也非常的好求（就一个等差数列），这里就不详细展开了。

当 $n$ 为奇数时，环数为 $\frac{(n+1)(n-1)}{4}$。当 $n$ 为偶数时，环数为 $\frac{(n+2)(n-2)}{4}+1$。

## 代码

```cpp
int main()
{
    int n;
    cin >> n;
    if (n & 1)
    {
        cout << (n + 1) * (n - 1) / 4 << endl;
        cout << Triple{1, 2, 3} << Triple{1, 2, 3};
        for (int i = 5; i <= n; i += 2)
        {
            for (int j = 1; j < i - 2; j++)
            {
                cout << Quadraple{j, i, j + 1, i - 1};
            }
            cout << Triple{1, i - 1, i} << Triple{i - 2, i - 1, i};
        }
    }
    else
    {
        cout << ((n + 2) * (n - 2) + 4) / 4 << endl;
        cout << Triple{1, 2, 3} << Triple{2, 3, 4} << Triple{3, 4, 1} << Triple{4, 1, 2};
        for (int i = 6; i <= n; i += 2)
        {
            for (int j = 1; j < i - 2; j++)
            {
                cout << Quadraple{j, i, j + 1, i - 1};
            }
            cout << Triple{1, i - 1, i} << Triple{i - 2, i - 1, i};
        }
    }
}

```


---

## 作者：xcyle (赞：2)

样例给出了 $n=3$ 和 $n=5$，手玩不难发现 $n=4$ 可以由三个长度为 $4$ 的环拼成

考虑先把这些东西分成若干个 $n=3$ 或 $n=4$，然后拼完全二分图以合并两个块。

考虑如何构造一个完全二分图，设左部点数$a$，右部点数 $b$：
- 若 $a$ 为偶数或 $b$ 为偶数，容易构造，只需要将偶数那边分成若干个点对，每个独自去连另一边的东西
- 若 $a$ 和 $b$ 都是奇数，显然我们可以合理安排合并顺序使得其中一个是 $3$，设为 $a,b,c$。那么将另一个奇数堆的其中一个位置 $p$ 连 $p-a-b$，$p-b-c$，$p-a-c$，最后再来一个 $a-b-c$。这样就可以转化为另一堆是偶数的问题了

[提交记录](https://codeforces.com/contest/819/submission/118519598)

---

