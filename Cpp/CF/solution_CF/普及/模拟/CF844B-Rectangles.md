# Rectangles

## 题目描述

You are given $ n×m $ table. Each cell of the table is colored white or black. Find the number of non-empty sets of cells such that:

1. All cells in a set have the same color.
2. Every two cells in a set share row or column.

## 说明/提示

In the second example, there are six one-element sets. Additionally, there are two two-element sets, the first one consists of the first and the third cells of the first row, the second one consists of the first and the third cells of the second row. To sum up, there are $ 8 $ sets.

## 样例 #1

### 输入

```
1 1
0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3
1 0 1
0 1 0
```

### 输出

```
8
```

# 题解

## 作者：lukelin (赞：3)

我们发现可以计算组合数来解决问题  
先把组合数求出来，然后我们发现，如果一行/一列有k个格子同色  
相当于C1,k + C2,k + C3,k + ... + Ck,k  
于是我们顺便在计算组合数的时候把上面这个序列求出来
让后问题变为求一行/一列有多少个格子颜色为0，有多少个格子颜色为一  
注意单个格子也就是C1,1在行和列各被算了一次，所以要减去多算的部分即n*m

上代码：
```cpp
#include <cstdio>
#include <iostream>
#define ll long long

using namespace std;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

unsigned ll C[102][102];
unsigned ll sum[102];
ll cac_sum[102][2];

int main(){
    ll n = read(), m = read();
    C[1][0] = C[1][1] = 1;
    sum[0] = 0;
    sum[1] = 1;
    for (ll i = 2; i <= 51; ++i){
        C[i][0] = 1;
        sum[i] = 0;
        //cout << C[i][0] << ' ';
        for (ll j = 1; j < i; ++j){
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j], sum[i] += C[i][j];
            //cout << C[i][j] << ' ';
        }
        C[i][i] = 1, ++sum[i];
        //cout << C[i][n] << endl;
    }
    ll tmp, cnt[2];
    unsigned ll ans = 0;
    for (ll i = 0; i < n; ++i){
        cnt[0] = 0, cnt[1] = 0;
        for (ll j = 0; j < m; ++j){
            cin >> tmp;
            ++cac_sum[j][tmp], ++cnt[tmp];
        }
        ans += sum[cnt[0]] + sum[cnt[1]];
    }
    for (ll i = 0; i < m; ++i)
        ans += (sum[cac_sum[i][0]] + sum[cac_sum[i][1]]);
    cout << (ans - (n * m));
    return 0;
}
```

---

## 作者：codeLJH114514 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF844B)

## 题目大意

给出一个仅包含字符零一的矩阵，求**同时**满足如下要求的子点集个数：

- 点集中所有的字符均为零或一。
- 点集中所有的字符均在同一行或同一列。

## 题目分析

我们可以将满足要求的子点集分成三种：

- 单独的一个点，肯定满足要求。
- 字符个数大于一且均在同一列的。
- 字符个数大于一且均在同一行的。

第一种子点集的个数非常好计算，就是 $n \times m$。

对于第二种子点集，考虑枚举列号，对每一列分别计算，再分为全是零的和全是一的。

全是零的和全是一的一样，这里用全是零的举例。

容易发现其实就是这一列中字符全是零且长度大于一的子序列，数量其实就是 $2^c - c - 1$，其中 $c$ 为零的数量。（因为 $2^c$ 就是全是零的子序列个数，因为要去掉空的子序列所以需要减一，因为要去掉长度为一的子序列所以要减去 $c$。）

对于第三种子点集，和第二种计算方法一样，对每一行分别计算即可。

最后将三种子点集的个数累加即可。

时间复杂度 $\mathcal{O}(nm)$，原题数据范围 $1 \le n, m \le 50$ 所以可过。

## 坑点描述

1. 这道题答案十分大，超出了 `int` 的最大值 $2^{31}-1$，所以需要开 `long long`，如果不开 `long long` 你会在第十八个点得到一个负数。
1. 由于精度问题，计算 $2^c$ 时千万不要用 `<cmath>`（或 `<math.h>`）库中的 `pow` 函数，直接用 `1LL << c` 表示 $2^c$ 即可，否则你会在第十八个点 WA 掉。（也不能写成 `1 << c`，因为这样的话就会计算出来一个 `int` 的值。）

~~别问我怎么知道的那么清楚。~~

## 最终代码

```cpp
#include <iostream>
#include <cmath>
#define int int64_t
#define maxn 64
using namespace std;
int n, m;
char c[maxn][maxn];
int ans;
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> c[i][j];
    for (int i = 1; i <= n; i++) {
        int cnt0 = 0, cnt1 = 0;
        for (int j = 1; j <= m; j++)
            if (c[i][j] == '0')
                cnt0 += 1;
            else
                cnt1 += 1;
        ans += (1LL << cnt0) - cnt0 - 1, ans += (1LL << cnt1) - cnt1 - 1;
    }
    for (int i = 1; i <= m; i++) {
        int cnt0 = 0, cnt1 = 0;
        for (int j = 1; j <= n; j++)
            if (c[j][i] == '0')
                cnt0 += 1;
            else
                cnt1 += 1;
        ans += (1LL << cnt0) - cnt0 - 1, ans += (1LL << cnt1) - cnt1 - 1;
    }
    cout << ans + n * m;
    return 0;
}
```
运行时间：$165$ 毫秒。

如有错误欢迎在评论区指出，如果对您有用就太好了。

---

## 作者：Jsxts_ (赞：2)

# 题解 CF844B Rectangles
[传送门](https://www.luogu.com.cn/problem/CF844B)
## 题意
给一个 $n\times m$ 的01矩阵，求有多少子点集满足：

1、点全是0或点全是1

2、点都在同一行或同一列上

## 题解

首先由条件2我们可以想到对于每行每列统计答案再求和，而条件1告诉我们要01分开统计。

对于每一行或每一列全选0的情况，每个0可以选或不选，答案为 $2^x-1$，$x$ 代表0的个数，减1是因为全都不选是不行的。全选1也一样。

如果这一行只选了一个，就会与其他情况重复，所以答案最后要减 $n\times m$，具体为什么可以自己推一下。

记得开 long long。
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int o_r[60],o_c[60],l_r[60],l_c[60];//r代表行，c代表列
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= n;i ++ ) {
		for (int j = 1;j <= m;j ++ ) {
			int x;
			scanf("%d",&x);
			if (x == 0) o_r[i] ++, o_c[j] ++; //统计个数
			else l_r[i] ++, l_c[j] ++;
		}
	}
	long long ans = 0;
	for (int i = 1;i <= n;i ++ ) ans += (1ll << o_r[i])-1 + (1ll << l_r[i])-1;//每行统计答案 
	for (int i = 1;i <= m;i ++ ) ans += (1ll << o_c[i])-1 + (1ll << l_c[i])-1;//每列统计答案
	printf("%lld",ans-n*m);//去重 
	return 0;
}
```

Time：571ms

---

## 作者：InfSauf (赞：0)

由题，给出一个 $n \times m$ 的 $01$ 矩阵,求满足都是 $0$ 或 $1$ 都在同一行或同一列上的点集个数。

因为是点集，所以两个点之间不需要连续，例如样例2：
```
Input:
2 3
1 0 1
0 1 0
```
这里面的 $1$ 和 $0$ 就不是连续的。

首先我们可以统计每一行和每一列的 $1$ 和 $0$ 的个数，然后计算满足要求的点集个数。

根据集合的知识，我们可以知道，一个集合 $A$ 的真子集个数就是 $2^{card(A)-1}$ 其中， $card(A)$ 表示这个集合 $A$ 中所含元素个数。

利用这一点，我们可以算出满足条件的点集个数，但是我们发现，在算每一行和每一列的时候，以每个点为点集的个数算了两次，所以在最后我们需要从计算出的点集数中减去这个 $01$ 矩阵大小。

于是就有了这样的代码。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 60;
int n, m, sum;
int a[N][N];
signed main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	for(int i = 1; i <= n; i++){
		int x = 0, y = 0;
		for(int j = 1; j <= m; j++){
			if(a[i][j] == 1)x++;
			else y++; 
		}
		sum += pow(2, x) - 1;
		sum += pow(2, y) - 1;
		//x = 0, y = 0;	
	}
	for(int i = 1; i <= m; i++){
		int x = 0, y = 0;
		for(int j = 1; j <= n; j++){
			if(a[j][i] == 1)x++;
			else y++; 
		}
		sum += pow(2, x) - 1;
		sum += pow(2, y) - 1;
		//x = 0, y = 0;	
	}
	cout << sum - n * m;
}
```
但是我们发现提交这个代码会得到#18 WA 因为pow函数的精度不够，所以我们可以自己用 long long 写一个快速幂来计算 $2^n$ 的值。

于是有了下面的代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 60;
int n, m, sum;
int a[N][N];
int ksm(int a, int b){
	int s = 1;
	while(b){
		if(b & 1)
			s = s * a;
		a = a * a;
		b >>= 1;	
	}
	return s;
}
signed main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	for(int i = 1; i <= n; i++){
		int x = 0, y = 0;
		for(int j = 1; j <= m; j++){
			if(a[i][j] == 1)x++;
			else y++; 
		}
		sum += ksm(2, x) - 1;
		sum += ksm(2, y) - 1;
		//x = 0, y = 0;	
	}
	for(int i = 1; i <= m; i++){
		int x = 0, y = 0;
		for(int j = 1; j <= n; j++){
			if(a[j][i] == 1)x++;
			else y++; 
		}
		sum += ksm(2, x) - 1;
		sum += ksm(2, y) - 1;
		//x = 0, y = 0;	
	}
	cout << sum - n * m;
}
```


---

## 作者：Tomato_Ya (赞：0)

## 题意
给一个 $01$ 矩阵，求有多少子点集满足：

- 点全是 $0$ 或点全是 $1$。 

- 点都在同一行或同一列上。

## 思路
首先我们要注意一点：题目中让求的子点集可以不相连，例如样例二：
```
2 3
1 0 1
0 1 0
```
其中除了六个单独一个点成一个子点集，还有第一行两个 $1$ 和第二行两个 $0$ 也算两个子点集。

所以计算中间不相连，也可以成为子点集。

那我们的思路就简单多了，循环枚举每一行和每一列，分别求出来每一行每一列 $0$ 和 $1$ 的个数。

当求出 $0$ 或 $1$ 的数量后，不难发现，这一行或者一列子点集的个数就是 $2^n-1$，其中 $n$ 是 $0$ 或 $1$ 的数量。   

我们把每一行每一列的子点集数都相加，就求出答案了。

### 注意

我们上面算每一行的子点集数包含单独一个点成一个子点集的数量，当算每一列时，也包含单独一个点成一个子点集的数量，也就是我们算了两遍。

所以我们需要让子点集总数减去一遍，也就是减去 $n\times m$。

还有记得开 ```long long```，算 $2^n-1$ 时 ```int``` 会炸。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, a[55][55], s;
int sum(int n){ //计算子点集数量
    return pow(2, n) - 1;
}
signed main(){
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; i ++)
      for(int j = 1; j <= m; j ++)
        scanf("%lld", &a[i][j]);
    for(int i = 1; i <= n; i ++){
        int t1 = 0, t2 = 0;
        for(int j = 1; j <= m; j ++){
            if(a[i][j] == 0)t1 ++;
            else t2 ++;    
        } //计算每一行0和1的数量
        if(t1 != 0)s += sum(t1);
        if(t2 != 0)s += sum(t2);
    }
    for(int j = 1; j <= m; j ++){
        int t1 = 0, t2 = 0;
        for(int i = 1; i <= n; i ++){
            if(a[i][j] == 0)t1 ++;
            else t2 ++;
        } //计算每一列0和1的数量
        if(t1 != 0)s += sum(t1);
        if(t2 != 0)s += sum(t2);
    }
    printf("%lld", s - n * m); //去掉重复部分
    return 0;
}
```


---

## 作者：泠小毒 (赞：0)

# Rectangles

给一个01矩阵，求有多少子点集满足：

1、点全是0或点全是1

2、点都在同一行或同一列上

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190428/)

## 解法

很简单啊=-=，统计出每行每列0和1的数量，然后就是手推一下公式

发现是组合数求和，直接(1<<x)即可

tips：不开long long见祖宗

## ac代码
考试的时候写的代码，丑的要死，勿喷qwq

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,a[100],b[100];
long long ans;
int main()
{
	cin >> n >> m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin >> x;
			if(x)a[i]++,b[j]++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		ans+=(1ll<<a[i])+(1ll<<(m-a[i]))-2;
	}
	for(int i=1;i<=m;i++)
	{
		ans+=(1ll<<b[i])+(1ll<<(n-b[i]))-2;
	}
	cout << ans-n*m << endl;
	return 0;
}
```

---

