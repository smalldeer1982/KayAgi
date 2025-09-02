# A Compatible Pair

## 题目描述

Nian is a monster which lives deep in the oceans. Once a year, it shows up on the land, devouring livestock and even people. In order to keep the monster away, people fill their villages with red colour, light, and cracking noise, all of which frighten the monster out of coming.

Little Tommy has $ n $ lanterns and Big Banban has $ m $ lanterns. Tommy's lanterns have brightness $ a_{1},a_{2},...,a_{n} $ , and Banban's have brightness $ b_{1},b_{2},...,b_{m} $ respectively.

Tommy intends to hide one of his lanterns, then Banban picks one of Tommy's non-hidden lanterns and one of his own lanterns to form a pair. The pair's brightness will be the product of the brightness of two lanterns.

Tommy wants to make the product as small as possible, while Banban tries to make it as large as possible.

You are asked to find the brightness of the chosen pair if both of them choose optimally.

## 说明/提示

In the first example, Tommy will hide $ 20 $ and Banban will choose $ 18 $ from Tommy and $ 14 $ from himself.

In the second example, Tommy will hide $ 3 $ and Banban will choose $ 2 $ from Tommy and $ 1 $ from himself.

## 样例 #1

### 输入

```
2 2
20 18
2 14
```

### 输出

```
252
```

## 样例 #2

### 输入

```
5 3
-1 0 1 2 3
-1 0 1
```

### 输出

```
2
```

# 题解

## 作者：StudyingFather (赞：8)

由于n,m都非常的小（<=50），所以，我们可以简单枚举要删除的元素，然后将剩下的元素两两相乘，就能得到最大值。
```cpp
#include <iostream>
#include <algorithm>
#define INF 0x7fffffffffffffff
using namespace std;
long long a[55],b[55];
int main()
{
 int n,m;
 cin>>n>>m;
 for(int i=1;i<=n;i++)
  cin>>a[i];
 for(int i=1;i<=m;i++)
  cin>>b[i];
 long long res=INF;
 for(int i=1;i<=n;i++)
 {
  long long now=-INF;
  for(int j=1;j<=n;j++)
   if(j!=i)
    for(int k=1;k<=m;k++)
     now=max(now,a[j]*b[k]);
  res=min(res,now);
 }
 cout<<res;
 return 0;
}
```

---

## 作者：asasas (赞：3)

看到数据范围：($n<=50$,$m<=50$)，直接暴力就行了。

枚举在$a$集合中要删的元素，然后将$a$和$b$两个集合里的元素两两相乘（注意跳过现在要删的元素），去最大值，再和答案取较小值即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
long long a[10005],b[10005];//注意要开long long
int main(){ 
    cin >> n >> m;
    for (register int i=1;i<=n;i++){
    	cin >> a[i];
    }
    for (register int j=1;j<=m;j++){
    	cin >> b[j];
    }
    long long ans=1e18;
    long long now=-1e18;//最小值的初始最大，最大值的初始最小   for (register int i=1;i<=n;i++){//枚举要删的数
    	for (register int j=1;j<=n;j++){
    		if (i==j) continue ;//相等就跳过
    		for (register int k=1;k<=m;k++){
    			now=max(now,a[j]*b[k]);//取最大值
    		}
    	}
    	ans=min(ans,now);//取最小值
    	now=-1e18;//重新初始化
    }
    cout << ans;
} 
```


---

## 作者：Tweetuzki (赞：2)

其实这题的 $n, m$ 都可以开大到 $10^6$。

我的做法是 $O(n+m)$ 的贪心。

先考虑不拿走元素的情况。那么对答案有贡献的元素只有可能是 $A,B$ 中最大的元素和最小的元素。可以证明。

假设在 $B$ 中挑了一个元素的值为 $k$，那么最终得出的这个值 $y$ 与在 $A$ 中挑出的元素 $x$ 成正比例关系：$y = kx$。

这时候可以分类：

1. 当 $k>0$ 时，$y$ 随 $x$ 的增大而增大。所以当 $x$ 取最大值时，$y$ 才会是最大值。

2. 当 $k=0$ 时，无论 $x$ 取何值，$y$ 的值都为 $0$。此时我们可以当做取了最大值或最小值。

3. 当 $k<0$ 时，$y$ 随 $x$ 的增大而减小。所以当 $x$ 取最小值时，$y$ 才会是最大值。

终上所述，当 $x$ 取最大值或最小值时，$y$ 存在最大值。

所以我们应该挑 $A$ 中最大或最小的元素。$B$ 同理。

那么 $y$ 的最大值为 $\max(Max_A \cdot Max_B, Max_A \cdot Min_B, Min_A \cdot Max_B, Min_A \cdot Min_B)$。

有 $Max_A \cdot Max_B$ 和 $Min_A \cdot Min_B$ 很好想到，那么为什么还要 $Max_A \cdot Min_B$ 和 $Min_A \cdot Max_B$ 呢？

有一组数据：

```plain
3 3
-3 -2 -1
1 2 3
```

显然答案一定是负数，为了使答案最大，这个值的绝对值应该越小。这样，就出现了 $Max_A \cdot Min_B$ 了。

再考虑删除的情况。为了删除后的最大值最小，肯定拿走的数要对答案有贡献，那么就一定是 $Max_A$ 或者 $Min_A$。此时 $Maxer_A$ 和 $Miner_A$ 就分别成为了 $A$ 的最大值和 $A$ 的最小值。再分别拿走 $Max_A$、$Min_A$，并分别用 $Maxer_A$、$Miner_A$ 代替，代入上方公式，取较小值，就是最后答案了。

最大值、次大值、最小值、次小值在输入时就可以求出，不需要再花费 $n log n$ 的排序，也可以节省空间。

时间复杂度仅有 $O(n+m)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long llt;

const llt INF = 0x7F7F7F7F7F7F7F7F;

int n, m;
llt Max1 = -INF, Maxer1 = -INF, Min1 = INF, Miner1 = INF, Max2 = -INF, Min2 = INF;

void init() {
    scanf("%d %d", &n, &m);
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        llt x;
        scanf("%lld", &x);

        if (x > Max1) {
            Maxer1 = Max1;
            Max1 = x;
        } else if (x > Maxer1)
            Maxer1 = x;

        if (x < Min1) {
            Miner1 = Min1;
            Min1 = x;
        } else if (x < Miner1)
            Miner1 = x;
    }

    for (int i = 1; i <= m; ++i) {
        llt x;
        scanf("%lld", &x);

        Min2 = min(Min2, x);
        Max2 = max(Max2, x);
    }

    //拿走值最大的元素
    llt ans1 = max( max(Maxer1 * Max2, Maxer1 * Min2), max(Min1 * Max2, Min1 * Min2) );

    //拿走值最小的元素
    llt ans2 = max( max(Max1 * Max2, Max1 * Min2), max(Miner1 * Max2, Miner1 * Min2) );

    llt ans = min(ans1, ans2);

    printf("%lld\n", ans);
}

int main() {
    init();
    solve();
    return 0;
}
```

---

## 作者：feicheng (赞：1)

## 题意简述
给定两数列 $a,b$，求在 $a$ 中删掉一元素后剩余值与 $b$ 中元素相乘所得最大值的最小值。
## 思路讲解
考虑数据范围 $2\le n,m\le50$，可以思考枚举。

我们可以枚举每次删去的元素，更新答案即可。具体实现请见代码

考虑到 数列的值不超过 $2\times 10^9$，是有可能爆 `int` 的，所以记得开 `long long`。

时间复杂度$O(n^2m)$，可以通过本题
## 代码实现（附注释）
```cpp
/*If you are full of hope,you will be invincible*/
#include <bits/stdc++.h>
#define ri register int
typedef long long ll;
std::mt19937 hpy(time(nullptr));
constexpr int inf(0x3f3f3f3f),N(100);
ll Mx,ans = 9223372036854775807,a[N],b[N];
int n,m;
int main(int argc,const char *argv[]){
	std::cin >> n >> m;
	for(ri i = 1;i <= n;++i) std::cin >> a[i];
	for(ri i = 1;i <= m;++i) std::cin >> b[i];
	for(ri i = 1;i <= n;++i) {//枚举要删除的元素
		Mx = -9223372036854775807;//此轮的最大值
		for(ri j = 1;j <= n;++j) {
			if(j == i) continue;
			for(ri k = 1;k <= m;++k)  
            Mx = std::max(Mx,a[j]*b[k]);
		}
		ans = std::min(Mx,ans);//总体最大值取min
	}
	std::cout << ans;
	return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
有两个数列 $A$ 和 $B$，$A$ 数列里面有 $n$ 个元素，$B$ 数列里面有 $m$ 个元素，现在请从 $A$ 数列中删除一个数，使得 $A$ 数列中剩下的任意一个元素与 $B$ 数列中任意一个元素相乘得到的所有 $m(n-1)$ 个值的最大值最小，求出这个最小值。

**数据范围：$1\leqslant n,m\leqslant 50,-10^9\leqslant A_i,B_i\leqslant 10^9$。**
## Solution
数据范围这么小，我们为什么不直接枚举呢？

首先枚举在 $A$ 数列中删除的数，然后枚举所有相乘得到的 $m(n-1)$ 个值，求得最大值，再取最小，最后直接输出就好了。

**提醒：这道题目相乘得到的结果可能很大，需要开 $\texttt{long long}$！**
## Code
```cpp
int n, m;
ll a[57], b[57], ans = 0x3f3f3f3f3f3f3f3f;

int main() {
	getint(n), getint(m);
	_for(i, 1, n)	getll(a[i]);
	_for(i, 1, m)	getll(b[i]);
	_for(k, 1, n) {
		ll maxi = -0x3f3f3f3f3f3f3f3f;
		_for(i, 1, n)
			_for(j, 1, m)
				if(i != k)
					maxi = max(maxi, a[i] * b[j]);
		ans = min(ans, maxi);
	}
	writell(ans);
	return 0;
}
```

---

## 作者：happybob (赞：1)

其实原本是想用贪心去做的，但是因为涉及到负数乘法，麻烦一些，只好暴力了

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

bool cmp(int x, int y)
{
    return x > y;
}

bool cmp2(int x, int y)
{
    return x < y;
}

long long a[55], b[55];

int main()
{
    long long n, m, cnt = 0, cnt2 = 0, max = -0x7fffffffffffffff, ans = 0x7fffffffffffffff;//无穷大和无穷小
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++)
    {
        max = -0x7fffffffffffffff;
        for(int j = 1; j <= n; j++)
        {
            if(i != j)
            {
                for(int x = 1; x <= m; x++)
                {
                    max = a[j] * b[x] > max ? a[j] * b[x] : max;
                }
            }
        }
        ans = max < ans ? max : ans;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Soshine_溯闪 (赞：0)

我**第三次**传题解。   
~~温馨提示：这题提交出结果很慢，请不要砸电脑。~~   
映入眼帘的是 $n$ 和 $m$ 都小于 50 。    
**暴力枚举**。     
# 整体思路  
几层循环，每层枚举什么？
1. 第一层循环枚举在 $a$ 数组中删哪个数。    
2. 第二层循环枚举 $a$ 数组，只要这个数不是枚举的那个要删的数 ,就有第三层枚举。    
3. 第三层循环枚举 $b$ 数组。   

怎么处理答案？    
1. 这题要求的是最大的最少，那就先将每删一个数情况下的的最大值。    
2. 求出最大值后，在跟 $ans$ 数组打擂台，看哪个小。    

# 这题真的很水，直接上程序
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
const long long maxn=51,inf=1e18+1;
long long n,m,a[maxn],b[maxn],ans; 		//定义 
int main(){
	cin>>n>>m;
	ans=inf;		//将ans定义为无限大 
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int j=1;j<=m;j++) cin>>b[j];		//读入和处理 
	for(int i=1;i<=n;i++){
		long long mx=-inf;		//将mx定义为无限小 
		for(int j=1;j<=n;j++){
			if(i!=j){		//如果不是一个数 
				for(int k=1;k<=m;k++){
					long long pd=a[j]*b[k];		//相乘 
					mx=max(pd,mx);		//求最大值 
				}
			}
		}
		ans=min(mx,ans);		//最小值 
	}
	cout<<ans<<endl; 	//愉快输出 
	return 0;		//完美AC 
}
```
如果有什么 $bug$ ,请在聊天区说一下。      
跪求管理员给过。      
求大家点个赞！
我们有 **圆** 再见！

---

