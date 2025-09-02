# Big Vova

## 题目描述

Alexander is a well-known programmer. Today he decided to finally go out and play football, but with the first hit he left a dent on the new Rolls-Royce of the wealthy businessman Big Vova. Vladimir has recently opened a store on the popular online marketplace "Zmey-Gorynych", and offers Alex a job: if he shows his programming skills by solving a task, he'll work as a cybersecurity specialist. Otherwise, he'll be delivering some doubtful products for the next two years.

You're given $ n $ positive integers $ a_1, a_2, \dots, a_n $ . Using each of them exactly at once, you're to make such sequence $ b_1, b_2, \dots, b_n $ that sequence $ c_1, c_2, \dots, c_n $ is lexicographically maximal, where $ c_i=GCD(b_1,\dots,b_i) $ - the greatest common divisor of the first $ i $ elements of $ b $ .

Alexander is really afraid of the conditions of this simple task, so he asks you to solve it.

A sequence $ a $ is lexicographically smaller than a sequence $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the sequence $ a $ has a smaller element than the corresponding element in $ b $ .

## 说明/提示

In the first test case of the example, there are only two possible permutations $ b $ — $ [2, 5] $ and $ [5, 2] $ : for the first one $ c=[2, 1] $ , for the second one $ c=[5, 1] $ .

In the third test case of the example, number $ 9 $ should be the first in $ b $ , and $ GCD(9, 3)=3 $ , $ GCD(9, 8)=1 $ , so the second number of $ b $ should be $ 3 $ .

In the seventh test case of the example, first four numbers pairwise have a common divisor (a power of two), but none of them can be the first in the optimal permutation $ b $ .

## 样例 #1

### 输入

```
7
2
2 5
4
1 8 2 3
3
3 8 9
5
64 25 75 100 50
1
42
6
96 128 88 80 52 7
5
2 4 8 16 17```

### 输出

```
5 2 
8 2 1 3 
9 3 8 
100 50 25 75 64 
42 
128 96 80 88 52 7 
17 2 4 8 16```

# 题解

## 作者：wsyhb (赞：7)

UPD：增加了代码部分（突然发现忘记贴代码了，却发现管理员光速审完了这篇题解，麻烦管理员再审一遍）

## 题意简述

给定一个长度为 $n$ 的数列 $a$，要求将其元素**打乱**，得到序列 $b$ ,使得序列 $b$ 的前缀 $GCD$ 序列 $c$ **字典序最大**。

注：$b$ 的前缀 $GCD$ 序列 $c$，即满足 $c_i=GCD(b_1,b_2,\cdots,b_i)$。

数据范围：$n \leq 10^3$，$a_i \leq 10^3$。

## 题意分析 & 解法

打乱数列，意味着你只需要考虑这个数列里**有哪些元素**，而无需考虑原来的顺序。

（也就是将其视为**整数集合**）

字典序的比较方式是**从左到右依次比较，第一个不相同的位置的大小关系即为字典序大小关系**，那么我们可以考虑**贪心**：使得当前数尽量大。

对于第 $1$ 个数，$c_1 =b_1$，显然选择 $a$ 集合中最大的一个数；

对于第 $i$ 个数（$i \geq 2$），$c_i=GCD(b_1,b_2,\cdots,b_i)=GCD(c_{i-1},b_i)$，由于 $c_{i-1}$ 已经确定，我们只需枚举 $a$ 集合中剩下的元素，看哪一个使得 $GCD$ 最大，令它为 $c_i$ 即可。

## 代码实现

我们整理一遍思路：

1. 选取 $a$ 集合中最大的一个数作为 $b_1$，并把这个数从中删除；

2. 接下来依次讨论 $b_2,\cdots,b_n$，设当前讨论到 $b_i$，从 $a$ 集合中选取一个数 $x$ 使得 $GCD(b_{i-1},x)$ 最大，令 $b_i=x$，并把这个数从集合中删除。

注：代码实现时可以不将 $x$ 删除，只需要将**对应位置打上标记**即可。

时间复杂度：$O(n^2log_{_2}n)$ （求 $GCD$ 单次复杂度为 $O(log_{_2}n)$ ，如果枚举倍数预处理 $GCD$ 数组可以做到 $O(n^2)$）

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e3+5;
int a[max_n];
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",a+i);
		int d=0,id=0;//d是最大值，id是最大值的下标
		for(int i=1;i<=n;++i)
        {
			if(a[i]>d)
            {
                d=a[i];
                id=i;
            }
        }
		printf("%d%c",d,1<n?' ':'\n');
		a[id]=0;//将a[id]赋值为0，即将其删除
		for(int i=2;i<=n;++i)//确定剩下n-1个数
		{
			int max_d=0,id=0;
			for(int j=1;j<=n;++j)
				if(a[j]) 
				{
					int v=gcd(a[j],d);
					if(v>max_d)
                    {
                        max_d=v;
                        id=j;
                    }
				}
			printf("%d%c",a[id],i<n?' ':'\n');
			a[id]=0;
			d=max_d;//d记录上一个数
		}
	}
	return 0;
}
```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1407/B)
题目要求我们重新排列一个整数序列 $a_1,a_2,\dots,a_n$，得到一个新的序列 $b_1,b_2,\dots,b_n$，使序列 $c_1,c_2,\dots,c_n$ 是字典序最大的。其中，$c_i = \gcd({b_1,b_2,\dots,b_n})$，即序列 $b$ 前 $i$ 个元素的最大公约数。

## 思路
要使序列 $c$ 的字典序最大，我们需要在每一步选择**使得当前 $c_i$ 最大的元素。**

每次选择的元素应该使 $c_i$ 尽可能大，且后续选择不会导致 $c_i$ 下降过快。

考虑贪心：

- 首先选择整个序列中最大的数作为 $b_1$，因为这样可以最大化 $c_1$。

- 对于剩下的元素，每次选择使得 $\gcd({b_1,b_2,\dots,b_n})$ 最大的元素。

- 重复这个过程，直到所有元素都被选完。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
// 计算 GCD
int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
int a[1005];
void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	vector<int> b;
	vector<bool> used(n, false);
	int GCD = 0;
	for (int i = 0; i < n; ++i) {
		int maxx = 0;
		int idx = -1;
		// 找到一个未使用的数，使得当前 GCD 最大
		for (int j = 0; j < n; ++j) {
			if (!used[j]) {
				int k = gcd(GCD, a[j]);
				if (k > maxx) {
					maxx = k;
					idx = j;
				}
			}
		}
		// 将该数加入序列 b
		b.push_back(a[idx]);
		used[idx] = true;
		GCD = maxx;
	}
	// 输出结果
	for (int num : b) {
		cout << num << " ";
	}
	cout << "\n";
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn^2 \log n) $，本题中 $\sum{n} \leq 1000$，可以通过本题。

---

## 作者：Nuclear_Fish_cyq (赞：1)

首先注意到一点， $\gcd(a,b,c)=\gcd(\gcd(a,b),c)$，也就是说，$c_i=\gcd(c_{i-1},b_i)$。题目要使 $c$ 的字典序最大，那肯定是前面的数越大越好。那么第一个数肯定就是序列里最大的数，不然因为字典序先看前面的数，必然不是最优的。然后我们就 $O(n)$ 暴力枚举每一个没被选过的数，贪心地选择最优的数，总时间复杂度 $O(Tn^2\log n)$。（注：翻译没有翻译全数据范围，是能过的）

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
//#define mod
//#define range
using namespace std;
int t, n, a[1000], now, maxn, maxi, maxn2, maxi2;
bool flag[1000];
int gcd(int p, int q){
	return q == 0 ? p : gcd(q, p % q);
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	for(int kk = 0; kk < t; kk++){
		cin >> n;
		for(int i = 0; i < n; i++){
			cin >> a[i];
			flag[i] = false;//多测要清空
			if(maxn < a[i]){
				maxn = a[i];
				maxi = i;
			} 
		}
		now = maxn;//贪心地选择第一个数
		flag[maxi] = true;
		cout << maxn;
		for(int i = 1; i < n; i++){
			maxn = 0;
			for(int j = 0; j < n; j++){//贪心 
				if(!flag[j]){//还没被选过 
					if(gcd(a[j], now) > maxn){
						maxn = gcd(a[j], now);
						maxi = j;
					}
				} 
			}
			maxn2 = 0;
			for(int j = 0; j < n; j++){//如果有多个可选解，选字典序最大的 
				if(!flag[j] && gcd(a[j], now) == maxn){
					if(a[j] > maxn2){
						maxn2 = a[j];
						maxi2 = j;
					}
				}
			}
			flag[maxi2] = true;
			cout << " " << maxn2;
			now = maxn;
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：孤芒星河233 (赞：0)

## CF1407B Big Vova

[洛谷题面](https://www.luogu.com.cn/problem/CF1407B)
[CF原题面](https://codeforces.com/problemset/problem/1407/B)

- **题意**
  
  有 $T$ 组数据。对于每组数据，有一个长度为 $n$ 的序列 $a$ ，需要对 $a$ 重新排列得到序列 $b$ 并输出。设 $c_i=\gcd(b_1,b_1\cdots b_n)$ ，你重排后得到的数组 $b$ ,需要满足对应计算出的数组 $c$ 的字典序最大。
  
  数据范围：$T\leq 10^3,n\leq 10^3,1\leq a\leq 10^3$ ，其中所有数据中 $n$ 的和不超过 $10^3$

- **思路**

  首先我们先想想怎么解决 $c$ 数组的计算，很明显可以推出 $c_1=b_1 ,c_{i+1}=\gcd(c_i,b_{i+1})$ ，有点类似于前缀和的思想。
  
  然后我们再思考如何做到字典序最大。根据字典序的判定，我们可以知道 $b_1$ 肯定是原数组 $a$ 中最大的数。然后我们再看下一个数，明显需要在 $a$ 中选出一个使 $c_2=\gcd(c_1,b_2)$ 最大的数。以此类推，**贪心**的思维就体现出来了。
  
  我们在每次选数时枚举一遍 $a_i$ ，时间复杂度为 $O(n^2)$ ，那么最终的时间复杂度就是 $O(Tn^2)$ ，翻译中给的数据明显无法直接这样暴力。但阅读原题面就会发现翻译没有给全，所有数据中的 $n$ 之和不超过 $10^3$ 。于是我们就可以放心大胆打暴力了！
  > It is guaranteed that the sum of n over all test cases does not exceed $10^3$

- **代码**

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  
  const int N=1e3+9;
  int T,n,a[N],maxx,x,c;
  bool use[N];//记录用过的数
  
  int gcd(int a,int b){
      if(b==0) return a;
      return gcd(b,a%b);
  }
  
  int main(){
      scanf("%d",&T);
      while(T--){
          memset(use,0,sizeof(use));
          maxx=c=0;
          scanf("%d",&n);
          for(int i=1;i<=n;i++){
              scanf("%d",&a[i]);
              if(maxx<a[i]) maxx=a[i],c=i;//用c记录下标,maxx记录最大数
          }
          use[c]=1;x=c=a[c];
          printf("%d ",maxx);
          for(int i=1;i<n;i++){
              maxx=0;
              for(int j=1;j<=n;j++){
                  if(!use[j]){
                      int d=gcd(c,a[j]);
                      if(d>maxx) maxx=d,x=j;//x来记录下标
                  }
              }
              c=maxx,use[x]=1;
              printf("%d ",a[x]);
          }
          puts("");
      }
      return 0;
  }
  ```

---

## 作者：5G信号塔报装 (赞：0)

有一个长度为 $n$ 的序列，对其重新排序，构造新数组 $c$，$c_i = gcd(a_1, a_2, ..., a_i)$，并且使得 $c$ 的字典序最小。

**思路：跑 $n$ 次，暴力枚举，每次求出当前的数值。**

Code (Think Twice, Code Once)

```cpp
// AC：https://vjudge.net/solution/28988538 
// AC：https://www.luogu.com.cn/record/44586885

# include <bits/stdc++.h>
using namespace std;

int arr[100005], status[100005];

int mygcd(int i, int j) {
	return __gcd(i, j);
}

signed main() {
	int q;
	scanf("%d", &q);
	while (q--) 
	{
	int n;
	scanf("%d", &n);
	memset(status, 0, sizeof(status));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	int now = 0;
	for (int i = 1; i <= n; i++) {
		int max0 = 0;
		int pos = -1;
		for (int j = 1; j <= n; j++) {
			int tmp = mygcd(arr[j], now);
			if (tmp > max0 && !status[j]) {
				max0 = tmp;
				pos = j;
			}
		}
		now = max0;
		status[pos] = 1;
		printf("%d ", arr[pos]);
	}
	puts("");
	}
	return 0;
} 
```

---

## 作者：onglu (赞：0)

## B. Big Vova  
### 题目大意  
给定一个长度为$n$数列，要求对这个数列指定顺序，使得这个数列的每一个前缀$GCD$组成的新序列字典序最大。  
$n \leq 1000$  
$a[i] \leq 1000$  

### 思路  
~~比赛的时候因为想到好几个假算法疯狂WA。~~  
思路很好想到，因为要字典序最大，所以越在前面的$GCD$肯定越大。  
那么第一个数就直接被确定了，必须是序列中最大的数，否则必然不优。  

那么剩下的数该怎么填呢？  
既然已经有了第一个数了， 相当于我们已经有了前前缀$GCD$，那么我们只需要在剩下的未被使用的序列中找到一个数使得前缀$GCD$和当前这个数的$GCD$最大即可。  
直接暴力查找，时间复杂度为$O(n^2log(n))$  

### 代码  
```cpp
#include <bits/stdc++.h>

using namespace std;

int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}
int n, a[1009], vis[1009];
int gcd(int a, int b){
	return (b == 0)? a : gcd(b, a % b);
}
void work(){
	int t = 0, maxn = 0;
	memset(vis, 0, sizeof(vis));
	n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
		maxn = max(maxn, a[i]);
	}
	while(1){
		int maxn1 = 0, f = 0;
		for(int j = 1; j <= n; j++)if(!vis[j] && a[j] % maxn == 0){
			vis[j] = 1;f = 1;
			printf("%d ",a[j]);
		}
		for(int j = 1; j <= n; j++)if(!vis[j]){
			if(gcd(maxn, a[j]) > maxn1){
				maxn1 = gcd(maxn, a[j]);
				f = 1;
			}
		}
		maxn = maxn1;
		if(!f)break;
	}
	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			printf("%d ",a[i]);
		}
	}
	printf("\n");
}
int main()
{
	int Case = read();
	while(Case--)work();
	return 0;
}

```

---

## 作者：引领天下 (赞：0)

首先对于 $c_1$，没有任何人能限制他的发挥，故选择直接放上最大的 $a$。

然后枚举 $i$ 从 $2$ 到 $n$，暴力找跟当前的 $GCD(c_1,\dots,c_{i-1})$ 的 $\gcd$ 最大的 $a_j$，作为答案即可。但需要判断，不可重复选择。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1005];
bool u[1005];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(register int i=1;i<=n;i++)scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        int d=a[n];
        printf("%d ",a[n]),u[n]=1;
        for(register int i=2;i<=n;i++){
            int mxd=0,ans;
            for(register int j=n-1;j>=1;j--)if(!u[j]&&__gcd(a[j],d)>mxd)mxd=__gcd(a[j],d),ans=j;
            u[ans]=1,printf("%d ",a[ans]),d=__gcd(d,a[ans]);//选择了a[ans]，标记为选过，并更新gcd
        }
        puts("");memset(u,0,sizeof(u));
    }
    return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

首先 $c_1 = b_1$ , 故 $b_1 = \max_{k \in[1,n]}\{a_k\}$ 满足字典序最大。  
由
$$
\gcd(b_1 , b_2 , \cdots , b_k) = \gcd(\gcd(b_1 , b_2 , \cdots , b_{k-1}) , b_k)
$$  
所以维护以下前缀的gcd , 每次贪心扫一遍取与当前前缀的 $\gcd$ 最大的未取的数据即可。  
复杂度$\mathcal{O(n^2 \log a)}$  
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1234;
int a[maxn] , ans[maxn], vis[maxn];

int find(int pre, int color , int n) {
    int mx = -1;
    for(int i = 1; i <= n; ++i)
        if(vis[i] != color) {
            if(mx == -1 || __gcd(pre, a[mx]) < __gcd(pre, a[i])) {
                mx = i;
            }
        }
    vis[mx] = color;
    return mx;
}

int main() {
    int tests;
    cin >> tests;
    for(int tst = 1; tst <= tests; ++tst) {
        int n , pi = -1;
        scanf("%d" , &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d" , a + i);
            if(pi == -1 || a[i] > a[pi]) pi = i;
        }
        ans[1] = a[pi]; vis[pi] = tst;
        int pre = ans[1];
        for(int i = 2; i <= n; ++i) {
            ans[i] = a[find(pre , tst , n)];
            pre = __gcd(pre , ans[i]);
        }
        for(int i = 1; i < n; ++i) printf("%d ", ans[i]);
        printf("%d\n" , ans[n]);
    }
    return 0;
}
```

---

