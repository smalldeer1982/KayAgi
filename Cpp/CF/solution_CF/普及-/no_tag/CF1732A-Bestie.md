# Bestie

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \ldots, a_n $ . Friends asked you to make the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of all numbers in the array equal to $ 1 $ . In one operation, you can do the following:

- Select an arbitrary index in the array $ 1 \leq i \leq n $ ;
- Make $ a_i = \gcd(a_i, i) $ , where $ \gcd(x, y) $ denotes the GCD of integers $ x $ and $ y $ . The cost of such an operation is $ n - i + 1 $ .

You need to find the minimum total cost of operations we need to perform so that the GCD of the all array numbers becomes equal to $ 1 $ .

## 说明/提示

In the first test case, the GCD of the entire array is already equal to $ 1 $ , so there is no need to perform operations.

In the second test case, select $ i = 1 $ . After this operation, $ a_1 = \gcd(2, 1) = 1 $ . The cost of this operation is $ 1 $ .

In the third test case, you can select $ i = 1 $ , after that the array $ a $ will be equal to $ [1, 4] $ . The GCD of this array is $ 1 $ , and the total cost is $ 2 $ .

In the fourth test case, you can select $ i = 2 $ , after that the array $ a $ will be equal to $ [3, 2, 9] $ . The GCD of this array is $ 1 $ , and the total cost is $ 2 $ .

In the sixth test case, you can select $ i = 4 $ and $ i = 5 $ , after that the array $ a $ will be equal to $ [120, 60, 80, 4, 5] $ . The GCD of this array is $ 1 $ , and the total cost is $ 3 $ .

## 样例 #1

### 输入

```
9
1
1
1
2
2
2 4
3
3 6 9
4
5 10 15 20
5
120 60 80 40 80
6
150 90 180 120 60 30
6
2 4 6 9 12 18
6
30 60 90 120 125 125```

### 输出

```
0
1
2
2
1
3
3
0
1```

# 题解

## 作者：dyx2021 (赞：5)

### [题目传送门](https://www.luogu.com.cn/problem/CF1732A)  
~~这道题考试的时候想了一个多小时，考完以后5分钟就打完了，哭死~~

## 言归正传

### 1.题目大意
这题目有多组数据，对于每组数据，题目给定了一个长度为 $n$ 的数组，要通过最少的次数，使得这 $n$ 个数的 $\operatorname{gcd}$ (最大公约数)为 $1$，并给出修改一次的费用为 $n-i+1$，让我们求最小费用。

### 2.思路
这题看到样例，思考一下就能发现有一个结论：$0\leq ans \leq 3$，因为我们可以发现只要有答案是 $ > 3 $ 时，都可以将 $ a_{n-1} $ 和 $ a_n $ 进行两次 $\operatorname{gcd}$，使 $ a_{n-1} $ 和 $ a_n $ 分别变为 $n-1$ 和 $n$，因为 $\operatorname{gcd}(n-1,n)$ 一定为 $1$，所以可证得 $0\leq ans \leq 3$。因此我们只需要求出 $\{1,2,\ldots ,n\}$ 的最大公约数，再枚举一下从 $\{n-2,n\}$ 的数，计算其 $i$ 与 最大公约数的 $\operatorname{gcd}$，若其值为 $1$，则更新ans的值（ 因为无论如何有且仅有当 $ n=\{n-2,n\}$ 时的花费 ans$ \leq 3$)。   

还没理解吗，放个图理解一下
#### ①当$\{n-2,n\}$中有序号 $i$ 能使所有数的最大公约数与 $i$ 的 $\operatorname{gcd}$ 为 $1$ 时，则更新 $ans$。
![](https://cdn.luogu.com.cn/upload/image_hosting/vkr8riaa.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

#### ②当$\{n-2,n\}$中没有符合要求的 $i$ 值时，则最小值为$3$。
![](https://cdn.luogu.com.cn/upload/image_hosting/zkaul5f3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
### 3.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
int a[1000001];
int num[100001],res[100001];
int read()
{
  int e=0,f=1;
  char ch=getchar();
  while(ch<'0'||ch>'9')
    {
      if(ch=='-') f=-1;
      ch=getchar();
    }
  while(ch>='0'&&ch<='9')
    {
      e=e*10+ch-'0';
      ch=getchar();
    }
  return e*f;
}
int gcd(int a,int b)
{
  while(b^=a^=b^=a%=b);//位运算求最大公约数
  return a;
}
int main()
{
  T=read();
  while(T--)
    {
      n=read();
      for(int i=1;i<=n;i++)
        {
          a[i]=read();
        }
      int sum=a[1];
      for(int i=2;i<=n;i++)
        {
          sum=gcd(sum,a[i]);//计算所有数的最大公约数
        }
      if(sum==1)
        {
          cout<<"0"<<endl;
          continue;
        }
      int ans=n;
      int i;
      if(n<=3) i=2;
      else i=n-2;
      for(;i<=n;i++)
        {
          if(gcd(sum,i)==1)
            {
              ans=n-i+1;//更新答案
              //cout<<ans<<endl;
            }
        }
      cout<<min(ans,3)<<endl;
    }
  return 0;
}

```
码风不好，不喜勿喷。

### 4.细节
1. 在判断所有数的最大公约数时可以特判直接为 $1$ 时情况；
2. 在枚举区间时要注意 $n-2$ 可能为负数，会读到负数下标，会出现RE（~~我是不会告诉你我在这卡了几次~~）。

## 完结撒花！！！

---

## 作者：GalwayGirl (赞：4)

~~这个A题我还想得挺久的~~

## Sloution
因为操作的费用为 $n-i+1$，所以要最小化贡献肯定是从后面开始操作，然后可以想到最坏情况，因为 $\operatorname{gcd}(n,n-1)=1$，所以 $\operatorname{gcd}(\operatorname{gcd}(n,a_n),\operatorname{gcd}(n-1,a_{n-1}))$ 肯定也等于 $1$，所以就只用考虑 $4$ 种情况。

- 一开始所有数列的最大公因数就为 $1$，费用为 $0$ 。
- 进行操作 $\operatorname{gcd}(n,a_n)$ 后最大公因数为 $1$ ,费用为 $1$ 。
- 进行操作 $\operatorname{gcd}(n-1,a_{n-1})$ 后最大公因数为 $1$ ,费用为 $2$ 。
- 同时进行决策 $2$ 和 决策 $3$，费用为 $3$ 。

$ACcode$
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N=31;
    int t,n;
    long long a[N];
    int gcd(long long a,long long b){
        if(!b)return a;
        return gcd(b,a%b);
    }
    int main(){
        scanf("%d",&t);
        while(t--){
            scanf("%d",&n);
            for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
            long long yin=a[1];
            for(int i=2;i<=n;i++)yin=gcd(yin,a[i]);
            if(yin==1){
                printf("0\n");
                continue;
            }
            if(gcd(yin,gcd(n,a[n]))==1){
                printf("1\n");
                continue;
            }
            if(gcd(yin,gcd(n-1,a[n-1]))==1){
                printf("2\n");
                continue;
            }
            printf("3\n");
        }
        return 0;
    }
```


---

## 作者：kimidonatsu (赞：1)

# CF1732A Bestie 题解

对于题目我们需要知道一个重要前导知识：对于任意的 $n$，$\gcd{(n, n - 1)} = 1$ 。

而且我们不难发现，选择 $i = n$ 和 $i = n - 1$ 是 cost 最低的操作。

从样例入手，再联系到上面的几条重要结论可以推导出最小费用必定 $\leq 3$。

这里，我们设 $G$ 为数组中所有数字的 $\gcd$ 来进行分类讨论：

1. 如果 $G = 1$，那么无需操作，答案为 $0$。
2. 否则尝试如下操作：
	1. 尝试进行 $i = n$ 的操作，如果 $\gcd{(G, n)} = 1$，那么答案是 $1$。
    2. 否则尝试 $i = n - 1$ 的操作，如果 $\gcd{(G, n - 1)} = 1$，那么答案是 $2$。
3. 否则答案是 $3$，因为 $\gcd{(n, n - 1, G)} = 1$。

由上我们不难写出代码：

```cpp
#include <bits/stdc++.h>

int read();
void write(int x);

void solve() {
    int n = read();
    std::vector<int> a(n + 5);
    for (int i = 1; i <= n; i++)
        a[i] = read();

    int g = a[1];
    for (int i = 2; i <= n; i++)
        g = std::__gcd(g, a[i]);
    
    if (g == 1) {
        puts("0");
        return;
    } else {
        if (std::__gcd(g, std::__gcd(a[n], n)) == 1) {
            puts("1");
            return;
        } else {
            if (std::__gcd(g, std::__gcd(a[n - 1], n - 1)) == 1) {
                puts("2");
                return;
            } else {
                puts("3");
                return;
            }
        }
    }
}

int main() {
    int T = read();
    while (T--) {
        solve();
    }
    return 0;
}

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

```


---

## 作者：玄学OIER荷蒻 (赞：1)

## 题目简述:

- 有一个长度为 $n$ 的序列 $a$。
- 定义一次操作是选择一个位置 $i(1≤i≤n)$，把 $a_i$ 修改为 $\gcd(a_i,i)$，这样一次操作的费用是 $n-i+1$。

## 题目分析:
看了这道题，发现 $t$ 很大，而 $n$ 很小。\
$n$ 实在是太小了，所以时间很充裕。\
所以，最暴力的想法是枚举每一种可能性。\
总体时间复杂度 $O(2^n \times n \log n)$，显然会超时。\
但是，仔细想想，发现如果我们选择操作第 $n$ 和第 $n-1$ 项，那么这两项操作完必然一个是 $n$ 的因数，一个是 $n-1$ 的因数，那么它们必然互质，也就是说所有数字的总 $gcd$ 是1，而进行这两次操作的代价为3，也就是说答案最大就是3。\
然后我们再按不同情况分类:
1. n=1，这时如果 $a_1$ 直接就是1就满足题意了，否则要操作1次，代价为1。
2. n=2 此时，如果 $\gcd(a_1,a_2)=1$ 那么直接满足题意，也就是0，否则如果 $\gcd(a_1,\gcd(a_2,2))=1$ 那么修改1次，代价为1，否则，因为 $\gcd(1,a_1)=1$ 恒成立，所以只需要一次操作，代价为2。
3. 我们用 $smgcd$ 来表示 $1$ ~ $n-2$ 的gcd,然后有以下四种情况:
    1. $\gcd(smgcd,a_{n-1},a_n)=1$ 此时不需要进行任何操作，直接输出0。
    2. $\gcd(smgcd,a_{n-1},a_n,n)=1$ 这时只需要一次操作，也就是操作最后一项，直接输出1。
    3. $\gcd(smgcd,a_{n-1},a_n,n-1)=1$ 这时也只需要一次操作，但是是倒数第二项，此时应该输出2。
    4. 上述三种情况都不成立，直接输出3。
## 代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
int llt[30];
int gcd(int a,int b){
    if (b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    int t;
    cin>>t;
    while (t--){
        int n;
        cin>>n;
        for (int i=1;i<=n;i++) cin>>llt[i];
        if (n==1){
            if (llt[1]==1) cout<<0<<endl;
            else cout<<1<<endl;
            continue;
        }
        else if (n==2){
            if (gcd(llt[1],llt[2])==1) cout<<0<<endl;
            else if (gcd(llt[1],gcd(llt[2],2))==1) cout<<1<<endl;
            else cout<<2<<endl;
            continue;
        }
        int sumcd=0;
        for (int i=1;i<=n-2;i++) sumcd=gcd(llt[i],sumcd);
        if (gcd(sumcd,gcd(llt[n],llt[n-1]))==1) cout<<0<<endl;
        else if (gcd(sumcd,gcd(gcd(llt[n],n),llt[n-1]))==1) cout<<1<<endl;
        else if (gcd(sumcd,gcd(llt[n],gcd(llt[n-1],n-1)))==1) cout<<2<<endl;
        else cout<<3<<endl;
    }
    return 0;
}
```


---

## 作者：Patients (赞：1)

### 你只需要找规律：

$\gcd(i,i+1)=1$。

对于所有的答案而言，可以选 $ n $ 与 $ n-1 $，代价为 $ 3 $，所以答案一定不能超过 $ 3 $。

- 当答案为 $ 0 $ 时，全部的最小公因数为 $ 1 $。

- 当答案为 $ 1 $ 时，只能选 $ n $。

- 当答案为 $ 2 $ 时，只能选 $ n-1 $。

- 剩余答案均为 $ 3 $。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 25
int T;
int n,a[maxn]; 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int sum=a[1];
		for(int i=2;i<=n;i++) sum=__gcd(sum,a[i]);
		if(sum==1)
		{
			cout<<0<<'\n';
			continue ;
		}
		if(__gcd(sum,__gcd(n,a[n]))==1)
		{
			cout<<1<<'\n';
			continue ;
		}
		if(__gcd(sum,__gcd(n-1,a[n-1]))==1)
		{
			cout<<2<<'\n';
			continue ;
		}
		cout<<3<<'\n';
	}
	return 0;
}
```


---

## 作者：Usada_Pekora (赞：1)

给出两个显而易见的结论。

$\gcd(i,i+1) = 1$，同时他们的因数的 $\gcd$ 也是 $1$。

$\gcd(a_i,i)$ 的结果一定是 $i$ 的因数。

所以我们一定有一个答案 $3$：对 $n,n-1$ 这两个位置操作即可，此时 $\gcd(a_n,a_{n-1})=1$。

考虑枚举使得答案小于 $3$ 的方案（也就两种）即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[25], ans, n;
inline bool check() {
	int res = a[1];
	for (int i = 2; i <= n; i++) {
		res = __gcd(res, a[i]);
	}
	return res == 1;
}
signed main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		int pre1 = a[n], pre2 = a[n - 1];
		if (check()) {
			cout << 0 << endl;
			continue;
		} 
		a[n] = __gcd(a[n], n);
		if (check()) {
			cout << 1 << endl;
			continue;
		}
		a[n] = pre1, a[n - 1] = __gcd(a[n - 1], n - 1);
		if (check()) {
			cout << 2 << endl;
			continue;
		}
		cout << 3 << endl;
	}
	return 0;
}
```


---

## 作者：JOKER_chu (赞：0)

此题解的有两处参考了第四篇题解。

大家想必都看了题吧，当看到 $\gcd$ 的时候就要写出函数：

```cpp
int gcd(int a, int b){
	return !b ? a : gcd(b, a % b);
}
```
或使用 STL 中的  `__gcd(a, b);`  用哪一种都行，再看题目求的是啥，~~蒟蒻~~作者帮大家整理出了简化版部分题意： 

**有一个长度为 $n$ 的数组，一次操作是选择一个位置将 $a_i$ 改为  $\gcd(a_i , i)$，代价是 $n - i + 1$，求最小代价将数组的公共最大公约数改为 $1$。**

不难想出数组合法状态为 $\gcd(a_1 \sim a_n) = 1$，每次枚举数组后两个数就行，观察后发现此题考察了对最大公约数的理解与运用。

解法很简单，分类讨论即可 ：

答案为零时：原数组最大公约数为 $1$ 。

答案为一时：只能对最后一项进行操作。

答案为二时：对倒数第二项进行操作。

答案为一或者二时可以使用一个 for 循环求出，否则答案为三。

最后根据结论写出代码： 

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, a[10005];

int gcd(int a, int b){// 最大公约数 
	return !b ? a : gcd(b, a % b);
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){// n 组数据 
		cin >> m >> a[1];
		int gdc = a[1];
		for(int j = 2; j <= m; j++){
			cin >> a[j];
			gdc = gcd(a[j], gdc);// 统计初始数组的最大公约数 
		}
		if(gdc == 1){
			cout << 0 << endl;// 无需修改 
			continue;
		}
		int ans	= m;
		if(m <= 3){// 分为两类讨论 
			for(int j = 2; j <= m; j++){// 数组长度 <= 3 
				if(gcd(j, gdc) == 1){
					ans = m - j + 1;
				}
			}
		}else{
			for(int j = m - 2; j <= m; j++){// 数组长度 > 3 
				if(gcd(j, gdc) == 1){
					ans = m - j + 1;// ans更新 
				}
			}
		}
		if(ans > 3){
			cout << 3 << endl; // 此处参考了第四篇题解答案不大于三的结论 
		}else{
			cout << ans << endl;
		}
	}
	return 0;// 好习惯
}
```
**~~完~~**

---

