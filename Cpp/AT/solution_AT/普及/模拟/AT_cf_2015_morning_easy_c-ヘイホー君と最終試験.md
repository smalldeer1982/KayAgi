# ヘイホー君と最終試験

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-morning-easy/tasks/cf_2015_morning_easy_c

Codefes大学の競技プログラミングの授業では、成績評価のために、$ N $ 回の試験を行うことにしています。 各試験での成績は、$ 0 $ 以上 $ M $ 以下の整数値です。 $ N $ 個の試験成績のうち、上位 $ K $ 個の平均が $ R $ 点以上であれば、めでたく単位が認定されます。 上位 $ K $ 個の平均が $ R $ 点未満の場合には不合格となり、単位は認定されません。

$ N-1 $ 回の試験を終えたヘイホー君は、最終試験に臨もうとしています。 最終試験を除く $ N-1 $ 回の試験におけるヘイホー君の成績は、それぞれ $ S_1 $, $ S_2 $, …, $ S_{N-1} $ 点でした。 ヘイホー君は、最終試験で何点以上取れば単位が認定されるでしょうか？

## 说明/提示

### Sample Explanation 1

ヘイホー君が最終試験で $ 45 $ 点を取った場合、上位 $ 3 $ 個の平均は $ (86+49+45)/3=60 $ となり、単位が認定されます。 もちろん、$ 46 $ 点以上取っても単位は認定されます。 一方、$ 44 $ 点以下の場合には単位が認定されません。

### Sample Explanation 2

最終試験で $ 0 $ 点でも単位が認定されます。

### Sample Explanation 3

残念ながら、最終試験が満点でも単位は認定されません。

### Sample Explanation 4

大きな数が入力されることもあります。オーバーフローに注意しましょう。

## 样例 #1

### 输入

```
5 3 100 60
86
23
49
39```

### 输出

```
45```

## 样例 #2

### 输入

```
5 3 100 60
92
100
95
99```

### 输出

```
0```

## 样例 #3

### 输入

```
5 3 100 60
18
42
29
31```

### 输出

```
-1```

## 样例 #4

### 输入

```
13 10 1000000000 645245296
492014535
611893452
729291030
392019922
293849201
474839528
702912832
341845861
102495671
908590572
812912432
129855439```

### 输出

```
986132796```

# 题解

## 作者：ringlin (赞：5)

看到题解里没有代码：所以就有了这篇题解。
但是要有的还是要有。
## 思路：
看完题目，我们不难想到这就是一道模拟题。
### 模拟思路呢具体如下:   
 1 ，先将输入的考试成绩排序，求总分。然后呢还需要在加的过程中存一个最小值，以便于后期计算 $ ans =\sum_{i = 1}^{k}a_{i}  $。   
 2  ，判断是否参加期末考试，这里可以算出录取的总分，也可以算出被录取的平均分，当然我用的前者。如果，当前总分比录取总分大，那么不用参加期末考试。   
3  ，需要参加期末考试，在这里我们还要分两种情况：
注意，因为参加了期末考试所以，需要，在总分中，提前减掉刚才存的最小值即  $ \quad ans= ans-cnt  $。  
然后便是下面的两步：
 第一种，如果期末考试满分的话，都达不到分数线，就输出 -1 ，
 第二种，输出考试分数。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=0,k,m,r,cnt=1e9,a[100005];
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	std::ios::sync_with_stdio;//优化
	cin>>n>>k>>m>>r;
	for(int i=1;i<=n-1;i++){
		cin>>a[i];
	}
	sort(a+1,a+n,cmp);
	for(int i=1;i<=k;i++){
		ans+=a[i];//前K次考试成绩的总分
		cnt=min(cnt,a[i]);//存的最小值
	}
	int g=r*k;//计算录取总分
	if(ans>=g){
		cout<<0<<endl;
		return 0;
	}//如果当前分数>录取分数，就不用参加期末考试
	int l=m-cnt;//如果参加期末考试，需要减去最小的一次考试成绩
	if(l+ans<g){//如果期末考试满分都比录取总分小，那么就输出-1；
		cout<<-1<<endl;
		return 0; 
	}
	else{//否则输出期末考试成绩
		cout<<g-ans+cnt<<endl;
		return 0;
	} 
}
```


---

## 作者：nbtngnllmd (赞：3)

## 题意：

已知会进行 $n$ 场考试，其中会给出前 $n-1$ 场考试成绩，每场考试成绩上限为 $0-m$，如果分数最高的前 $k$ 场考试平均分数达到了 $r$，输出 $0$；如果没有达到，就要参加期末考试。如果考试成绩能够达到平均分，则输出需要的最小分数，反之则输出 $-1$。

------------
## 情况分析：
用 $score$ 代表前 $k$ 场分数相加。

大致上分为 $3$ 种情况：

$1$：首先分数最高的前 $k$ 场考试平均分已经达到了 $r$，可以直接输出 $0$。

$2$：前 $k$ 场没有达到平均分，把前 $k$ 场分数最低的值赋给 $sum$，此时总分数减去 $sum$，如果期末考试分数合法且达到平均分 $r$，输出 $r\times k-score$。

$3$：如果不合法的话，直接输出 $-1$。

------------

## 代码思路：
首先输出前 $n-1$ 场成绩，输出后从小到大排列，然后从分数最大的一场开始，直到 最小的一场成绩，如果大于等于 $r\times k$，输出 $0$。

如果不到，就把分数最高的前 $k$ 场中最小的数值弹出，总分数减去该数值；如合法的最大成绩加上现在的总成绩大于等于 $r\times k$，输出最小值 $r\times k-score$，反之输出 $-1$。

------------

## 代码实现：

------------
```cpp
//记得开long long
#include<bits/stdc++.h>

using namespace std;

long long a[100010];
//bool cmp(long long x,long long y){
//   return x>y;
//}

int main(){
    long long n,k,m,r,score = 0,di;cin>>n>>k>>m>>r;
    for(int i = 1 ; i < n ; i++ ) cin>>a[i];
    sort(a+1,a+n);//sort(a+1,a+1+n,cmp);定义一个cmp函数也可以
    for(int i = n - 1 ; i >= n - k  ; i-- ) {
        score+=a[i];//sort从小到大排序，所以如果选取分数最高的前k场要从n-1开始枚举，一直到n-k
    }
    if(score >= r * k)  {//分数已经达到了要求的r*k,不用score/k防止小数
        cout<<"0"<<endl;
        return 0;
    }
    else {
      sum = a[n-k] ;//sum 代表着前k场分数最高中的最低分
      score-=di;
      if(m+score>=r*k) cout<<r*k-score<<endl;
      else cout<<"-1"<<endl; 
    }
    return 0;
}
```




---

## 作者：Ja50nY0un9_as_AgNO3 (赞：1)

题目给了你一个长为 $N\bold{-1}$ 的数列，其中每个数都不超过 $M$。

现在要添加一个数（同样不超过 $M$），使得整个数列里最大的 $K$ 个数的平均值不小于 $R$。求添加的数的最小值。

我们直接模拟。

首先，为了找出目前最大的 $K$ 个数，我们就要对数组进行排序。从小到大排序以后，前 $K$ 个数就是目前最大的 $K$ 个数。接下来分类讨论。

如果前 $K$ 个数的平均值都超过了 $R$，那么不管我们添加的这个数是多少，平均值都不可能小于 $R$，输出 $0$ 退出程序就好。

接下来，因为题目要的是前 $K$ 个数，而我们添加的那一个也在这 $K$ 个之内，所以我们要在排序后解这个方程： $\dfrac{\sum\limits_{i=1}^{K-1}a_i+a_N}{K}=r$，其中 $a_N$ 就是我们添加的那个数。

化简可得 $a_N=R\times K-\sum\limits_{i=1}^{K}a_i-a_K$，模拟求出即可。因为 $a_N\le M$ 的限制，如果它超过了 $M$，我们要报告无解。否则输出即可。

关于 $K=N$ 的情况如何处理？因为全局数组初值为 $0$，相当于没有考第 $N$ 次，所以其实可以忽略，不需要特判。

最后一个问题是，部分数据点 $M\times K$ 超过了 $2^{32}$，要开 `long long`。否则，#4，#48，#54 等测试点就会 WA。被以上测试点卡掉的时候请记得检查一下变量类型。

接下来是代码。~~专程来看这个的请出门左转陶片见。~~

```cpp
# include <iostream>
# include <algorithm>
using namespace std;
long long a[101];

bool cmp(long long x, long long y){
    return x > y;
}

int main(){
    long long n, k, m, r;
    cin >> n >> k >> m >> r;
    for(int i = 1; i < n; i++)
        cin >> a[i];
    //注意，这里是输入 n - 1 个
    //虽然输入 n 个也莫名地能过
    sort(a + 1, a + n + 1, cmp);
    long long sum = 0;
    for(int i = 1; i <= k; i++)
        sum += a[i];
    //取前 k 个
    if(sum >= k * r){
        //已经到了 r
        cout << 0 << endl;
        return 0;
    }
    sum -= a[k];
    //取前 k - 1 个
    long long ans = k * r - sum;
    if(ans > m)
        cout << -1 << endl;
    else
        cout << ans << endl;
    return 0;
}
```

---

## 作者：jimmyfj (赞：1)

思路 : 将 $n - 1$ 个的成绩进行排序，统计前 $k$ 个大的成绩之和。如果得出的前 $k$ 个大的成绩之和的平均分大于等于分数线 $R$，输出 `0`；否则求期末考试至少考多少分才能使前 $k$ 个大的成绩之和的平均分至少等于 $R$ 并输出。（ **注意 :** 如果得出的要达到的期末考试分数大于实际卷子的满分，只输出 `-1` ）。

参考代码如下 :
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

ll n, k, m, r;
ll s[1001], sum, u;


int main () {
    scanf("%lld %lld %lld %lld", &n, &k, &m, &r);
    for (ll i = 1; i < n; i ++) {
        scanf("%lld", &s[i]);//输入n-1个的成绩
    }
    n -= 1;
    sort(s + 1, s + n + 1);
    for (ll i = n; i >= n - k + 1; i --) {
        sum += s[i];
        u = s[i];
    }
    ll score = r * k;//因为求平均分的时候可能会除不尽,所以直接乘上k个r
    if (sum < score) {//判断是否达到分数线
        ll last = score - sum + u;
        if (last > m) printf("-1\n");//判断是否会超过实际卷子的满分
        else printf("%lld\n", last);
        return 0;
    }
    printf("0\n");
    return 0;
}
```


---

## 作者：BZHZS (赞：1)

这道题还是比较简单的，只需要根据题意模拟即可。

值得注意的是，这道题的翻译太简单了，导致“如果达不到则输出 $-1$ ”和“前 $K$ 次测试是指分数高的前 $K$ 次”这两点没有体现出来。

这道题还有一个小技巧， 为了方便不处理小数， 我们可以设 $F = R \times K$ ，最后只要比较总的分数和 $F$ 的大小即可。

所以， 我们可以很快发现这道题可以分 $3$ 种情况讨论：

1. 前 $K - 1$ 次考试的总成绩已经大于 $K$，这时期末考试考 $0$ 分也能达标。
2. 就算期末考试考 $M$ 分， 前 $K$ 次的总成绩也小于 $F$ ， 输出 $-1$ 。
3. 若以上 $2$ 种情况均不符合，设 $S$ 为前 $K - 1$ 次考试分数和， 期末考试考 $F - S$ 分即可。

代码实现
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1010;
ll n, k, m, r, s, f;
ll a[N];

bool cmp(ll x, ll y)
{
    return x > y;
}

int main()
{
    scanf("%d%d%d%d", &n, &k, &m, &r);
    for (int i = 1; i < n; i++)
        scanf("%d", &a[i]);

    sort(a + 1, a + n, cmp);//分数从大到小进行排序

    for (int i = 1; i < k; i++)
        s += a[i];//记录前k - 1次考试的总成绩
    f = r * k;
    if (s + a[k] >= f)//按照分析进行讨论
        puts("0");
    else if (s + m < f)
        puts("-1");
    else
        printf("%lld\n", f - s);

    return 0;
}
```




---

## 作者：Escapism (赞：1)

挺棒的模拟题。预计评黄。

# 题意&翻译

这题的翻译存在严重不足，甚至会**影响做题**。

要补充的有几点：

- 所谓的**前 $K$ 次考试**，是指**分数前 $K$ 位**，并非考试顺序。

- 输出 $0$ 表示不用考期末考就被录取了；输出 $-1$ 表示期末考无论考多少分都不能被录取；否则输出可以被录取的情况下期末考的最低分。

# 思路

可以分为几种情况：

- 期末考前已被录取

- 期末考要考，可能被录取，但需要达到一定分数。

- 期末考考到多少都无法被录取。

## 第一种情况

对 $N - 1$ 次考试分数进行一次排序，选出最高的 $K$ 次，求平均数，若大于 $R$ 输出 $0$,退出程序即可。

## 第二种和第三种情况

若第一种情况不满足，就进入第二种和第三种情况。

首先，进入第二种和第三种情况的原因是由于分数前 $K$ 次考试总分不足，因而**期末考必然是进入这分数最高的 $K$ 次测试之中的**。

显然，在这 $K$ 次考试中的最低分会被期末考替代。设考试最低分为 $S_{K}$,那么期末考的分数就是 $S_K + (R \times K - \sum\limits_{i=1}^KS_i)$。

若期末考的分数小于 $M$,就说明这个分是可以被达到的，输出分数。

若大于 $M$,就说明分数不可达到，输出 $-1$。

## 第四种情况

值得一提的是，数据范围中提到：$K \le N$。

这就意味着，在 $K = N$ 的情况下，$S_{K}$ 有可能是不确定的。因此在这种情况下，期末考分数计算方法不能和前三种相同。但期末考分数计算方法比前面更简单：$N \times R - \sum\limits_{i=1}^{N-1}S_i$。

若期末考的分数小于 $M$,就说明这个分是可以被达到的，输出分数。

若大于 $M$,就说明分数不可达到，输出 $-1$。

# 代码

代码太丑了，就不放了。

---

## 作者：InversionShadow (赞：0)

## AT_cf_2015_morning_easy_c ヘイホー君と最終試験 题解

本题解参考 @Ja50nY0un9 神犇的程序。

### 题意：

给定 $n-1$ 个数，每个数不超过 $m$，表示一共进行 $n-1$ 次考试。现在要添加一个数（不超过 $m$），使得整个数列里最大的 $k$ 个数的平均值不小于 $r$。求添加的数的最小值。

### 思路：

直接模拟。

首先，先对输入的数从大到小排序，将前 $k$ 个数的和加到 $sum$ 里。这里需要判断，如果 $sum$ 大于 $k\times r$，表示前 $k$ 个数已经大于合格成绩了，就不要进行期末考试了，输出 ```0``` 即可。否则将 $sum$ 减去前 $k$ 个数中最小的数（即 $a_k$），得到剩下的成绩，再用及格的最低成绩（即 $r\times k$) 减去 $sum$，得到题目要求的数，**注意：如果最后得到的数大于 $m$，则输出 ```-1```，表示不合法，并且数据要开 ```long long```**。

### Code:

```cpp
#include <bits/stdc++.h>
#define int long long   // 要开 long long

using namespace std;

int n, m, k, r, a[10000001];

bool cmp(int i, int j) {
  return i > j;
}

signed main() {
  cin >> n >> k >> m >> r;
  for (int i = 1; i <= n - 1; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1, cmp);   // 从大到小排序
  int sum = 0;
  for (int i = 1; i <= k; i++) {   // 前 k 项之和
    sum += a[i];
  }
  if (sum >= r * k) {         // 判断是否进行期末考试
    cout << "0" << endl;
    return 0;
  }
  sum -= a[k];              // 减去前 k 项中最小的 
  int ans = k * r - sum;       
  if (ans > m) {
    cout << "-1" << endl; 
  } else {
    cout << ans << endl;
  }
  return 0;
}

```

### 珍爱生命，远离抄袭！


---

## 作者：Fozz_1024 (赞：0)

## 思路：

根据题意模拟。

为避免精度问题，我们可直接将 $k\times r$ 作为前 $k$ 次考试的录取指标，将 $n-1$ 次考试按分数从高到低排序，取前 $k$ 次考试的总分存进 $sum$，然后根据 $sum$ 和指标的关系分情况：

若 $n-1$ 次考试的前 $k$ 场考试已经符合要求，则无论第 $n$ 考试成绩如何，都一定会被录取，直接输出 $0$。

若前 $k$ 场考试总分没有达到指标，则最后一次考试的成绩必定大于 $n-1$ 次考试中前 $k$ 场考试成绩最低的一场。将最低一场的成绩减去，指标减去此时的总分，即为第 $n$ 场考试的最小成绩。

若最小成绩小于分数上限 $m$，说明还有机会被录取，直接输出这个成绩。
否则说明没有机会，输出 $-1$。

## 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

long long n,k,m,r,s[110],sum;//记得开long long 
inline bool cmp(const long long &a,const long long &b)
{
	return a>b;//自定义从大到小 
}

int main()
{
    scanf ("%lld%lld%lld%lld",&n,&k,&m,&r);
    for (int i=1;i<n;i++)
    {
    	scanf ("%lld",&s[i]);
    }
    
    sort(s+1,s+n,cmp);//将n-1场考试成绩排序 
    
    for (int i=1;i<=k;i++)
    {
    	sum+=s[i];//记录前k次的总分 
    }
    
    if(sum>=k*r)//已经满足，输出0 
    {
    	printf("0\n");
    }
    else
    {
    	if(k*r-(sum-s[k])<=m)//如果最小成绩小于分数上限 ，仍有机会被录取 
    	{
    		printf("%lld\n",k*r-(sum-s[k]));//输出此成绩 
    	}
    	else//否则没有机会被录取 
    	{
    		printf("-1\n");
    	}
    }
    
	return 0;
}
```


---

## 作者：hyc1026 (赞：0)

## 题意（题目描述）

在 Codefes 的编程课上有 $N$ 次考试，考试满分为 $M$。

将 $N$ 次考试中较高的 $K$ 次的分数取平均得到 $A$，如果 $A\ge R$，你会被录取，否则你不会被录取。

现在你已经进行了 $N-1$ 次考试，分数分别为 $S_1,S_2,\cdots,S_{N-1}$，请问你在第 $N$ 次考试时至少需要拿到多少分才能保证自己被录取？输出最少需要得到的分数。如果在考试前已经被录取，输出 $0$，如果无论这次考的多高都无法被录取，输出 $-1$。

## 思路

首先我们需要将这 $N-1$ 个分数排序，将较高的 $K-1$ 次考试分数的和设为 $sum$。

此时我们将 $R\times K$ 设为 $flag$，意为这 $K$ 次考试必须要达到的总分。

此时分情况讨论：

- 如果 $sum$ 加上第 $K$ 高的分数要比 $flag$ 高，那么这次无论考多低都不会影响录取与否，输出 $0$。

- 如果 $sum$ 加上 $M$ 还比 $flag$ 低，意味着这次考满分也不可能被录取，输出 $-1$。

- 均不满足意味着有可能但不一定被录取，此时输出 $flag-sum$，意为离录取线还差多少分，也就是这次最低需要考的分数。

## AC Code:

只放了核心代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[110];

bool cmp(int x,int y)
{
    return x > y;
}

signed main()
{
    int n,k,m,r;
    cin >> n >> k >> m >> r;
    int sum = 0;
    for(int i=1; i<n; i++)
    	cin >> a[i];
    sort(a+1,a+n,cmp);
    for(int i=1; i<k; i++)
    	sum += a[i];
    int flag = r * k;
    if(sum + a[k] >= flag) cout << 0 << endl;
    else if(sum + m < flag) cout << -1 << endl;
    else cout << flag - sum << endl;
}
```

---

