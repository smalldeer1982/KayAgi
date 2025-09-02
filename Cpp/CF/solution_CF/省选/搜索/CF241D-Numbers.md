# Numbers

## 题目描述

You have a sequence of $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=n) $ . You want to remove some integers in such a way that the resulting sequence of integers satisfies the following three conditions:

1. the resulting sequence is not empty;
2. the exclusive or ( $ xor $ operation) of all the integers in the resulting sequence equals $ 0 $ ;
3. if you write all the integers of the resulting sequence (from beginning to the end) in a row in the decimal numeral system and without any spaces, the written number is divisible by $ p $ .

You are given the sequence of $ n $ integers $ a $ and a prime number $ p $ , find a way to satisfy the described conditions.

## 样例 #1

### 输入

```
3 3
1 2 3
```

### 输出

```
Yes
3
1 2 3 
```

## 样例 #2

### 输入

```
3 5
1 2 3
```

### 输出

```
No
```

# 题解

## 作者：iostream (赞：7)

观察发现把一串数字接起来是一个类似随机的事情。

再是由于模数P很小只有 $50000$ 的范围，所以我们可以考虑只选用少量的数字。

经过实践，我发现留下1~24就足够了，这样选取也能使异或和=0的方案足够的多。

最后直接 $2^{24}$ DFS所有子序列即可。

```cpp
#include<set>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<algorithm>
#define pb push_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef double db;
typedef long long ll;

int n,P,m,a[50005],b[32],p[32],u[32];

void dfs(int i,int j,int x,int y)
{
	if(!x&&!y&&j)
	{
		printf("Yes\n%d\n",j);
		for(int k=0; k<j; k++)
			printf("%d ",u[k]);
		exit(0);
	}
	if(i>m)
		return;
	u[j]=p[i];
	dfs(i+1,j+1,x^b[i],b[i]<10?(y*10+b[i])%P:(y*100+b[i])%P);
	dfs(i+1,j,x,y);
}

int main()
{
	scanf("%d%d",&n,&P);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&a[i]);
		if(a[i]<25)b[++m]=a[i],p[m]=i;
	}
	dfs(1,0,0,0);
	puts("No");
	return 0;
}


---

## 作者：cirnovsky (赞：0)

## 题意简述

给你一个 $n$ 的排列和一个整数 $p$，要求留下若干个数字，使得剩下的数字异或为 $0$，并且从左到右串联起来可以被 $p$ 整除，输出任意一组这样的方案。

## 题解

又是一道奇奇怪怪的题。

先打了个暴力的 DFS。

然后通过这个暴力，我大概了解了一个情况：1~24 的排列组成的异或和为零的方案数远大于模数的极值。

也就是说什么呢，我们可以近似把异或和为零的序列模 $p$ 为 0 看作是一个随机事件。

那么我们就可以乱搞了呀，直接抛弃过大的数字（大约理论瞎 bb 了一下这个阈值取了 25，看到楼下 iostream 的题解发现可以取到 24）。

然后又因为这个是一个排列，所以留下来的数为 $S$ 个，即阈值。

于是我们就可以 $\Theta(2^{S})$ 次方暴搜，直接搜出答案。

```cpp
#include <cstdio>
#include <vector>

using namespace std;

int n, p, over, pos[50], ans[50];
vector < int > disc;

int connect(int now, int val, int mod) // 连接数
{
	if (val < 10)	now = now * 10 + val;
	else	now = now * 100 + val;
	return now % mod;
}

void dfs(int now, int siz, int exc, int cnt) // 搜到第几个数字，已选择的数字个数，当前异或和，当前选择的数字连接起来 mod p 的值
{
	if (over)	return ;
	if (siz != 0 && exc == 0 && cnt == 0)
	{
		printf("Yes\n%d\n", siz);
		for (int i = 1; i <= siz; ++i)	printf("%d ", ans[i - 1]);
		over = 1;
		return ;
	}
	if (now == (int)disc.size())	return ;
	ans[siz] = pos[now];
	dfs(now + 1, siz + 1, exc ^ disc[now], connect(cnt, disc[now], p));
	dfs(now + 1, siz, exc, cnt);
}

signed main()
{
	scanf("%d %d", &n, &p);
	disc.push_back(0);
	for (int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		if (x <= 24)
		{
			disc.push_back(x);
			pos[disc.size() - 1] = i;
		}
	}
	dfs(1, 0, 0, 0);
	if (over == 0)	puts("No");
	return 0;
}
```

---

