# Swap and Flip

## 题目描述

[problemUrl]: https://atcoder.jp/contests/keyence2020/tasks/keyence2020_d

$ N $ 枚のカードがあり、$ 1,\ 2,\ ...,\ N $ の番号がついています。 カード $ i $ ($ 1\ \leq\ i\ \leq\ N $) の片方の面には赤い文字で整数 $ A_i $ が、 もう片方の面には青い文字で整数 $ B_i $ が書かれています。 最初、これらのカードは赤い文字が書かれた面を表にして 左から右に番号順に一列に並んでいます。

以下の操作を繰り返すことで、カードの表側の面に書かれた整数の列が左から右に広義単調増加となる （すなわち、各 $ i $ ($ 1\ \leq\ i\ \leq\ N\ -\ 1 $) に対して、左から $ i\ +\ 1 $ 枚目のカードの表側の面に書かれた整数が $ i $ 枚目のカードの表側の面に書かれた整数以上である） ようにすることが可能かどうか判定してください。 さらに、可能である場合、必要な操作の回数の最小値を求めてください。

- 整数 $ i $ ($ 1\ \leq\ i\ \leq\ N\ -\ 1 $) を一つ選ぶ。 左から $ i $ 番目のカードと $ i\ +\ 1 $ 番目のカードの位置を入れ替え、さらにこれら $ 2 $ 枚のカードを裏返す。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 18 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 50 $ ($ 1\ \leq\ i\ \leq\ N $)
- 入力値はすべて整数である。

### Sample Explanation 1

$ i\ =\ 1 $ として操作を $ 1 $ 回行うと、 カードの表側の面に書かれた整数の列は $ [2,\ 3,\ 3] $ となり、単調増加となります。

### Sample Explanation 2

何回操作を行っても、 カードの表側の面に書かれた整数の列は $ [2,\ 1] $ のままであり、これは単調増加ではありません。

### Sample Explanation 3

操作を行う必要がない場合もあります。

## 样例 #1

### 输入

```
3
3 4 3
3 2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
2
2 1
1 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 2 3 4
5 6 7 8```

### 输出

```
0```

## 样例 #4

### 输入

```
5
28 15 22 43 31
20 22 43 33 32```

### 输出

```
-1```

## 样例 #5

### 输入

```
5
4 46 6 38 43
33 15 18 27 37```

### 输出

```
3```

# 题解

## 作者：cosf (赞：0)

观察一下性质。可以发现，第 $i$ 张卡片如果最后朝上的是 $B$ 面，则它所在位置的奇偶性必然和原先不同。

因此，我们枚举哪些牌最后是 $B$ 面朝上的（必定有偶数张），所以，我们希望能算出最后第 $i$ 张牌的位置 $p_i$，然后模拟冒泡即可算出所需的步数。

怎么算 $p_i$ 呢？可以通过两次排序算出。首先，若某两张牌朝上的数字不同，则小的一定在前。否则，要分奇偶性。

考虑一堆朝上数字一样的数，先判断最后他们位置中奇偶性是否能对上，然后对于同一种奇偶性的，按照开始的位置排即可。

时间复杂度 $O(2^nn^2)$。具体实现见代码。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

#define MAXN 25
#define INF 0x3ffff3ff
#define popcount __builtin_popcount

int n;

int a[MAXN][2];
int p[MAXN];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i][i & 1]; // 这样分奇偶性更方便
        p[i] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i][(i ^ 1) & 1];
    }
    int res = INF;
    for (int s = 0; s < (1 << n); s++)
    {
        if (popcount(s) & 1)
        {
            continue;
        }
        sort(p + 1, p + n + 1, [s](int x, int y) { // 第一次排序
            int vx = a[x][(x ^ (s >> (x - 1))) & 1];
            int vy = a[y][(y ^ (s >> (y - 1))) & 1];
            if (vx != vy)
            {
                return vx < vy;
            }
            else
                {
                return x < y;
            }
        });
        int l = 1;
        bool ok = true;
        for (int r = 1; r <= n; r = l)
        {
            int c[2] = {}, d[2] = {};
            while (l <= n && a[p[l]][(p[l] ^ (s >> (p[l] - 1))) & 1] == a[p[r]][(p[r] ^ (s >> (p[r] - 1))) & 1])
            {
                c[(p[l] ^ (s >> (p[l] - 1))) & 1]++;
                d[l & 1]++;
                l++;
            }
            if (c[0] != d[0] || c[1] != d[1]) // 判断奇偶性的数量是否对上
                {
                ok = false;
                break;
            }
            queue<int> q[2] = {queue<int>(), queue<int>()};
            for (int i = r; i < l; i++)
            {
                q[(p[i] ^ (s >> (p[i] - 1))) & 1].push(p[i]);
            }
            for (int i = r; i < l; i++) // 二次排序
            {
                p[i] = q[i & 1].front();
                q[i & 1].pop();
            }
        }
        if (ok)
        {
            int cr = 0; // 模拟冒泡
            for (int i = n; i > 1; i--)
            {
                for (int j = 1; j < i; j++)
                {
                    if (p[j] == i)
                    {
                        cr++;
                        swap(p[j], p[j + 1]);
                    }
                }
            }
            res = min(res, cr);
        }
    }
    if (res != INF)
    {
        cout << res << endl;
    }
    else
        {
        cout << -1 << endl;
    }
    return 0;
}

```

---

## 作者：封禁用户 (赞：0)

### 题意

一张牌有正反两面，都有数字，有操作交换相邻两张卡牌，交换的时候两张牌都会翻转，问最少操作次数使得卡牌满足数字非降，$n \le 18$
### 分析

 $n \le 18$ 明示状压，首先要看什么样的序列是合法的
我们以 0 1 表示卡牌相对于初始状态是否翻转

1.1的数量为偶数，自己模拟一下就懂了  
2.卡牌移动的距离和卡牌在那个位置上的正反是有关系的，奇数距离肯定是反面，偶数是正面

我们可以暴力枚举每张卡牌的 01 状态,一共   $2^n$ 种状态，然后以以上条件判断合法后进行匹配，显然原序列每张牌和最左边一张可以匹配上的牌匹配是最优的，得出卡牌交换后每个序号所在的位置后，逆序数就是最小交换次数
复杂度 $O(2^n*n^2)$ 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define F first
#define S second
#define mkp make_pair
#define pii pair<int,int>
typedef long long ll;
const int inf=0x3f3f3f3f;
const int maxn=2e5+5;
pair<int,int>pre[maxn],after[maxn];
int n;
int vis[maxn],a[maxn],b[maxn],p[maxn];
int solve(int s){
	int cnt=0;
	for(int i=0;i<n;i++)vis[i]=0;
	for(int i=0;i<n;i++){
		if((s>>i)&(1)){
			cnt++;
			pre[i]=mkp(b[i],1);
			after[i]=pre[i];
		}
		else {
			pre[i]=mkp(a[i],0);
			after[i]=pre[i];
		}
	}
	if(cnt&1)return inf;
	cnt=0;
	sort(after,after+n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(after[j].first==pre[i].first&&((abs(i-j)%2)==pre[i].second)&&vis[j]==0){
				vis[j]=1,cnt++,p[i]=j;
				break;
			}
		}
	}
	if(cnt!=n)return inf;
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(p[j]<p[i])ans++;
		}
	}

	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	for(int i=0;i<n;i++)scanf("%d",&b[i]);
	int ans=inf;
	for(int i=0;i<1<<n;i++){
		ans=min(ans,solve(i));
	}
	printf("%d\n",ans==inf?-1:ans);
}



---

