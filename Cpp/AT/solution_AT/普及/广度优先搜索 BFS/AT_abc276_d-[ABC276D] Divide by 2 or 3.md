# [ABC276D] Divide by 2 or 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc276/tasks/abc276_d

正整数列 $ A=(a_1,a_2,\ldots,a_N) $ が与えられます。  
 あなたは以下の操作のうち $ 1 $ つを選んで行うことを $ 0 $ 回以上何度でも繰り返せます。

- $ 1\ \leq\ i\ \leq\ N $ かつ $ a_i $ が $ 2 $ の倍数であるような整数 $ i $ を選び、$ a_i $ を $ \frac{a_i}{2} $ に置き換える
- $ 1\ \leq\ i\ \leq\ N $ かつ $ a_i $ が $ 3 $ の倍数であるような整数 $ i $ を選び、$ a_i $ を $ \frac{a_i}{3} $ に置き換える

あなたの目標は $ A $ が $ a_1=a_2=\ldots=a_N $ を満たす状態にすることです。  
 目標を達成するために必要な操作の回数の最小値を求めてください。ただし、どのように操作を行っても目標を達成できない場合、代わりに `-1` と出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

次のように操作をすると $ 3 $ 回で目標を達成でき、これが最小の回数です。 - $ a_i $ が $ 2 $ の倍数であるような整数 $ i $ として $ 2 $ を選び、$ a_2 $ を $ \frac{a_2}{2} $ に置き換える。$ A $ は $ (1,2,3) $ となる。 - $ a_i $ が $ 2 $ の倍数であるような整数 $ i $ として $ 2 $ を選び、$ a_2 $ を $ \frac{a_2}{2} $ に置き換える。$ A $ は $ (1,1,3) $ となる。 - $ a_i $ が $ 3 $ の倍数であるような整数 $ i $ として $ 3 $ を選び、$ a_3 $ を $ \frac{a_3}{3} $ に置き換える。$ A $ は $ (1,1,1) $ となる。

### Sample Explanation 2

どのように操作を行っても目標を達成できません。

## 样例 #1

### 输入

```
3
1 4 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3
2 7 6```

### 输出

```
-1```

## 样例 #3

### 输入

```
6
1 1 1 1 1 1```

### 输出

```
0```

# 题解

## 作者：FFTotoro (赞：8)

本题的目标是通过将数列中的每个数不断除以 $2$ 或 $3$，来使其中每个数相等。

很显然，最终数列里唯一出现的数（记为 $x$），是每个数的因数。这里因为要操作数量最小，所以我们就将 $x$ 设为所有数的最大公约数。

判断一下每个数是否可以通过只除以 $2$ 或 $3$ 来变成 $x$。即，判断每个 $\dfrac{a_i}{x}$ 的质因数分解是否仅包含 $2$ 或 $3$。

- 为什么可以将 $x$ 设为最大公约数而不影响是否有解的判断？

  证明：若将 $x$ 设为最大公约数时无解，则存在 $a_i$ 使得 $\dfrac{a_i}{x}$ 的质因数分解中包含除 $2$ 和 $3$ 以外的其他质因数。如果设 $y$ 为最终数列中出现的唯一的数且合法，那么很显然 $y|x\Rightarrow\left(\dfrac{a_i}{x}\right)\Big|\left(\dfrac{a_i}{y}\right)$，即 $\dfrac{a_i}{y}$ 仍然包含除 $2$ 和 $3$ 以外的质因数，矛盾。
  
  所以，利用最大公约数作为最终答案是正确的解法。
  
放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int n,g,c=0; cin>>n;
  vector<int> a(n);
  for(int i=0;i<n;i++){
    cin>>a[i]; if(!i)g=a[i];
    else g=__gcd(g,a[i]); // 可以使用 __gcd 函数
  }
  for(auto &i:a){
    int x=i/g;
    while(!(x&1))x>>=1,c++;
    while(!(x%3))x/=3,c++;
    if(x>1){cout<<"-1\n"; return 0;} // 还有其他的质因数
  }
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：cjh20090318 (赞：4)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

~~翻译给得很清楚了。~~

## 分析思路

本人又一次~~一不小心~~拿到了最优解，给大家讲一讲我的做法。

我是先将 $1 \sim n$ 所有的数都进行此操作，将所有数化到不能进行下面两个操作为止，同时判断化最简后的相邻两个值是否相等。

在将所有数化到最简的同时，我们可以求出所有数的最大公约数，如果可以被 $2$ 或 $3$ 整除，那我们就可以反悔 $n$ 次操作。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
using namespace std;
int n,a[1001];
//int b[30],c[19];
//2^29,3^18<10^9
inline int gcd(int x,int y){return y?gcd(y,x%y):x;}
int solve(int x){//进行操作。
	int ret=0;
	while((a[x]&1)==0) a[x]>>=1,++ret;
	while(a[x]%3==0) a[x]/=3,++ret;
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int ans,g=a[1];
	ans=solve(1);
	for(int i=2;i<=n;i++){
		g=gcd(g,a[i]);//求出最大公约数。
		ans+=solve(i);
		if(a[i]!=a[i-1]) return puts("-1"),0;//判断相邻两个数是否相等。
	}
//	g/=a[1];
//	printf("%d\n",g);
	while((g&1)==0) g>>=1,ans-=n;//反悔操作。
	while(g%3==0) g/=3,ans-=n;//同上
	printf("%d\n",ans);
	return 0;
}
```

*谢谢大家！*

---

## 作者：ZZQF5677 (赞：2)

### 解题思路
+ 先找因数。我把最小 $a_i$ 提出来，不断让它除以 $2$ 或者 $3$ 去得到它的因数，若令其中一个因数命名为数 $f$，那么我们再让 $f$ 不断让它除以 $2$ 或者 $3$ 去得到它的因数。这个过程用搜索实现，如下。

```cpp
void yin(long long x) {
  if (mp[x] == 1) {
    return;
  }
  v.push_back(x);
  mp[x] = 1;
  if (x % 2 == 0) {
    yin(x / 2);
  }
  if (x % 3 == 0) {
    yin(x / 3);
  }
  return;
}
```

+ 一些问题：至于我们为什么要找最小的 $a_i$，因为最小的 $a_i$ 因数少些，别的 $a_j$ 也必须用除以 $2$ 或者 $3$ 得到 $a_i$ 其中一个因数（输出结果为 $-1$ 的情况除外），所以减少复杂度。不过数据结构 $v$ 最多储存多少个数呢？大概小于 $200$ 个，即使 $1000$ 个也没关系。（假设 $v$ 长度为 $m$）因为最后的程序总时间复杂度最大为 $O(mn)$。

---

好了，接下来就是判断一个 $a_j$ 如何通过除以 $2$ 或者 $3$ 去得到 $a_i$ 的一个因数。先假设这个因数是 $x$。

假设 $a_j = 180,x = 5$：

不过我不是让 $180$ 去得到 $5$，而是整体除以 $5$；让 $36$ 去得到$1$.。。。

尽量让 $180$ 除以 $3$，不能整除除就除以 $2$，否则这个因数就不行。

于是这个过程就**类似于质因数分解的短除法**了。

让 $36$ 得到 $1$：$180 / 5 = 36,5/5=1$。
1. $36 / 3 = 12$
2. $12 / 3 = 4$
3. $4 / 2 = 2$
4. $2 / 2 = 1$

所以 $180$ 最少通过 $4$ 次得到 $5$。

该过程代码实现：

```cpp

long long op = a[i] / x; 
while (op != 1) {
  if (op % 3 == 0) {
    op = op / 3;
    ans++;
  } else if (op % 2 == 0) {
      op = op / 2;
    ans++;
  } else {
      return -1;
  }
}
```

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, a[1005];
vector<long long> v;
map<long long, bool> mp;
void yin(long long x) {
  if (mp[x] == 1) {
    return;
  }
  v.push_back(x);
  mp[x] = 1;
  if (x % 2 == 0) {
    yin(x / 2);
  }
  if (x % 3 == 0) {
    yin(x / 3);
  }
  return;
}
long long check(long long x) {
  if (x == 0) {
    return -1;
  }
  long long ans = 0;
  for (long long i = 1; i <= n; i++) {
    if (a[i] % x != 0) {
      return -1;
    }
    long long op = a[i] / x;  //操作的乘积：比如：
                              /*
                              不过我不是让180去得到5，而是整体除以5；让36去得到1.。。。
                              （类似于质因数分解的短除法）
                              若现在 x = 5。
                              op = 180 / 5 = 36
                              (1)36 / 3 = 12
                              (2)12 / 3 = 4
                              (3)4 / 2 = 2
                              (4)2 / 2 = 1
                              所以 180 最少通过 4 次得到 5。
                              找到的规律 by ZZQF5677。
                              */

    while (op != 1) {
      if (op % 3 == 0) {
        op = op / 3;
        ans++;
      } else if (op % 2 == 0) {
        op = op / 2;
        ans++;
      } else {
        return -1;
      }
    }
  }
  return ans;
}
int main() {
  cin >> n;
  for (long long i = 1; i <= n; i++) {
    cin >> a[i];
  }
  stable_sort(a + 1, a + 1 + n);
  yin(a[1]);
  /*
  for (long long i = 0; i < v.size(); i++) {
    cout << i << " " << v[i] << "\n";
  }
  */
  stable_sort(v.begin(), v.end());

  for (long long i = v.size() - 1; i >= 0; i--) {
    // cout << i << " " << v[i] << "\n";
    long long ans = check(v[i]);
    if (ans != -1) {
      cout << ans << "\n";
      return 0;
    }
  }
  cout << -1 << "\n";
  return 0;
}
```

---

## 作者：Neil_Qian (赞：1)

# [ABC276D] Divide by 2 or 3 题解
你应该知道，对于任意正整数 $P$ 而言，可以有以下结论，即唯一分解定理：

- $P=2^{a_1}\times3^{a_2}\times5^{a_3}\times7^{a_4}\times11^{a_5}\times\dots$
- 该分解是唯一的

那么根据题意，只有 $2^{a_1}$ 和 $3^{a_2}$ 的指数会减少，其它的部分不变。也就是说，如果每个数的其它部分不同，那么最终不可能相同。即无解。

所以，只要让所有的 $a_2$ 和 $a_3$ 变成一个相同的数即可。也就是让它们变成一个最小值，满足它比所有的数都小且是最小的，很容易想到，变成它们的最小值即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1002],x,min2=1e9,min3=1e9,ans,pos,c2,c3;//注意次数的初值
int main(){
	scanf("%d",&n);//输入
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	x=a[1];
	while(x%2==0)x/=2;
	while(x%3==0)x/=3;
	pos=x;//计算标准值
	for(int i=1;i<=n;i++){
		x=a[i],c2=c3=0;//注意每次更新
		while(x%2==0)x/=2,c2++;//计算次数
		while(x%3==0)x/=3,c3++;
		if(x!=pos){printf("-1\n");return 0;}//其它质因子不同，无解
		min2=min(min2,c2),min3=min(min3,c3);//找到最小的次数
	}
	for(int i=1;i<=n;i++){
		x=a[i],c2=c3=0;
		while(x%2==0)x/=2,c2++;
		while(x%3==0)x/=3,c3++;
		ans+=c2-min2+c3-min3;//计算次数
	}
	return printf("%d\n",ans),0;//输出
}
```

---

## 作者：__vector__ (赞：1)

## 做法  
想一想除法操作的本质。  

对于一个数除以 $2$，就是使这个数的因数 $2$ 的数量减一。  
举个简单的例子，$8$ 分解之后有 $3$ 个 因数 $2$。将其除以 $2$ 之后，变成 $4$，只有 $2$ 个因数 $2$ 了。  

除以 $3$ 同理。  

而所有数相等，实际上就是所有数的每种因数的数量**分别相等**。  

而现在只能让每个数的因数 $2$ 或 因数 $3$ 的数量减少。  

所以最后操作完的时候，如果取最优值，那么最终所有数的每种因数数量，都是这种因数在所有数之中出现次数的最小值。  

所以先记录下因数 $2$ 或 $3$ 在所有数中出现的最少次数，记为 $com_2,com_3$。  

设第 $i$ 个数出现了 ${cnt2}_{i} $ 次因数 $2$，${cnt3}_{i}$ 次因数 $3$。   

答案就是 $\sum_{i=1}^{n} ({cnt2}_{i} - com_2 + {cnt3}_{i} - com_3)$。  

那无解怎么判定？  

如果两个数因数 $2,3$ 出现的次数不同，可以通过一些操作来调整成相同。  

但是如果还出现了别的因数呢？  

如果还出现了别的因数，那么这个因数必须在所有的数中出现次数相同，否则无解，因为无法调整。  

最后复杂度，扫一遍，扫的过程中每个数计算对数次。    
### Code  
```cpp  
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int n;
int a[maxn];
struct Cnt
{
	int tw,thr,els;
}cnt[maxn];
int main()
{
	scanf("%d",&n);
	int es=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		while(a[i]!=1)
		{
			if(a[i]%2 && a[i]%3 && es!=0 && a[i]!=es)
			{
				printf("-1\n");
				return 0;
			}
			if(a[i]%2&&a[i]%3)
			{
				es=a[i];
				cnt[i].els++;
				break;
			}
			if(a[i]%2==0)
			{
				a[i]/=2;
				cnt[i].tw++;
			}
			if(a[i]%3==0)
			{
				a[i]/=3;
				cnt[i].thr++;
			}
		}
	}
	for(int i=1;i<n;i++)
	{
		if(cnt[i].els!=cnt[i+1].els)
		{
			printf("-1");
			return 0;
		}
	}
	int common2=1e9,common3=1e9;
	for(int i=1;i<=n;i++)
	{
		common2=min(common2,cnt[i].tw);
		common3=min(common3,cnt[i].thr);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=cnt[i].tw-common2;
		ans+=cnt[i].thr-common3;
	}
	printf("%d",ans);
	return 0;
}  
```

---

## 作者：FstAutoMaton (赞：0)

题意就是给你一串数，问你是否能在将每个数除以若干次 $2$ 或 $3$ 后将其变为一样。

那么我们可以知道，想变为相同的数那必然是它们的公因数，否则否则总会有几个数无法变成那个数（因为题目说只能除以 $2$ 或 $3$）。

那么我们可以先让所有的数都除以它们的最大公因数，然后进行操作。
因为只能除以 $2$ 或 $3$，所以能除以 $3$ 就除以 $3$，否则就除以 $2$，直到它变为 $1$，最后在操作时统计一下次数即可。

PS：由于可能会无解，所以在既不能整除 $3$ 也不能整除 $2$ 时要特判。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;

const int kMaxn = 1e3 + 5;
int n, sum, a[kMaxn];

void work(int x) {
  bool l = 0;
  for (; x != 1; x % 3 == 0 ? x /= 3 : x /= 2) {
    l |= min(x % 2, x % 3);
    sum++;
  }
  sum = l ? -1000000000 : sum;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int s = __gcd(a[1], a[2]);
  for (int i = 3; i <= n; i++) {
    s = __gcd(s, a[i]);
  }
  for (int i = 1; i <= n; i++) {
    a[i] /= s;
    work(a[i]);
  }
  cout << max(-1, sum);
  return 0;
}
```


---

## 作者：code_hyx (赞：0)

讲一个不用 $\text{gcd}$ 的做法。  
首先，要证明一个结论：只要有解，那么把每个数都除到不能除为止，一定就是相等的。  
可以使用反证法。如果结果不相等，那一定任意两个数之间都没有 $2$ 和 $3$ 的公因数，要么互质，要么公因数是其他数。那少除几次可以吗？少除一次相当于又乘回来一个 $2$ 或 $3$，但这两个数都是质数，根本不能提供其他公因子，怎么也搞不成相等，所以，与假设矛盾。  
那么，什么情况可以减少次数呢？那就是所有的数都有公共的 $2$ 或 $3$。每出现一个公共因子 $2$，所有的数都少除一次 $2$。每出现一个公共因子 $3$，所有的数都少除一次 $3$。而公因子 $2$ 的个数就是含因子 $2$ 最少的数因子 $2$ 的个数，公因子 $3$ 的个数就是含因子 $3$ 最少的数因子 $3$ 的个数。  
算出每个数有多少个因子 $2$ 和因子 $3$ 即可，与其他因数没有任何关系。最后，验证一遍，到底是不是变成了相等。  
代码:
```
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],min2=0x3f3f3f3f,min3=0x3f3f3f3f,ans2,ans3;
struct countt
{
	int two;
	int three;
};
countt ct[1005];
int get_two(int x)
{
	int cnt=0;
	while(1)
	{
		if(x%2!=0)break;
		else x/=2;
		cnt++;
	}
	return cnt;
}
int get_three(int x)
{
	int cnt=0;
	while(1)
	{
		if(x%3!=0)break;
		else x/=3;
		cnt++;
	}
	return cnt;
}
bool check()
{
	for(int i=1;i<=n-1;i++)
	{
		if(a[i]!=a[i+1])return false;
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		ct[i].two=get_two(a[i]);
		ct[i].three=get_three(a[i]);
		min2=min(min2,ct[i].two);
		min3=min(min3,ct[i].three);
	}
	for(int i=1;i<=n;i++)
	{
		ans2+=ct[i].two-min2;
		ans3+=ct[i].three-min3;
		for(int j=1;j<=ct[i].two-min2;j++)
		{
			a[i]=a[i]/2;
		}
		for(int j=1;j<=ct[i].three-min3;j++)
		{
			a[i]=a[i]/3;
		}
	}
	if(!check())cout<<-1;
	else
	{
		cout<<ans2+ans3;
	}
    return 0;
}
```


---

## 作者：Orange_qwq (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc276_d) && [AT 传送门](https://atcoder.jp/contests/abc276/tasks/abc276_d) 

## 思路

先考虑有解情况。

显然，最优方案就是将数列 $a$ 全都变成它们的最大公约数，这样操作的次数才能尽可能少。

于是我们先求出 $\gcd \{a_1, a_2, \cdots,a_n \}$，然后一个数一个数地除以 $2$ 和 $3$，直到不是 $2$ 或 $3$ 的倍数。

那无解呢？

继续上一步，除完之后，再将这个数除以他们的最大公约数，如果得到的数不是 $1$，就说明他还有其他的因数，所以无解。

## $\texttt{AC Code}$

赛时代码，可能写得稍微繁琐。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, g, ans, a[1010];
int gcd(int x, int y) {
	return y == 0 ? x : gcd(y, x % y);
} // 手写 gcd
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), g = gcd(g, a[i]); // 找最大公约数
	for (int i = 1; i <= n; ++i) 
		if (a[i] % 2 && a[i] % 3 && a[i] != g) return puts("-1"), 0; // 先筛掉一遍，如果还有其他因数就无解
	for (int i = 1; i <= n; ++i) {
		a[i] /= g;
		if (a[i] % 2 && a[i] % 3 && a[i] != 1) return puts("-1"), 0; // 又筛一遍
		int j = 2;
		while (a[i] % j == 0) ++ans, a[i] /= j;
		if (a[i] != 1) {
			j = 3;
			while (a[i] % j == 0) ++ans, a[i] /= j;
		}
		if (a[i] == 2 || a[i] == 3) ans++;
		else if (a[i] > 1) return puts("-1"), 0; // 又双筛一遍
	}
	printf("%d", ans);
}
```


---

## 作者：sunzz3183 (赞：0)

# [ABC276D] Divide by 2 or 3 题解

## 题意

每次操作选择一个能被 $2$ 或 $3$ 整除的数，并将他除以 $2$ 或 $3$。

问将所有数变成相等的最小操作数，无解输出 $-1$。

## 分析

我们先把每个数给不断除以 $2$ 和 $3$，直到不能除为止，那么现在的数组一定每个数都不是 $2$ 和 $3$ 的倍数。那么现在，如果这些数字相同，就一定有解，因为现在每个数字，同时乘 $2$ 或 $3$ ，所有的数字不变。如果不同，那么数字无论怎么乘 $2$ 或 $3$ ，都会有不同的因子，使数字不同。

所以我们得到下面的代码：

```cpp
for(int i=1;i<=n;i++){
	b[i]=a[i];
	while(b[i]%2==0)b[i]/=2;
	while(b[i]%3==0)b[i]/=3;
}
```
```cpp
for(int i=1;i<n;i++)
	if(b[i]!=b[i+1])return -1;
```

然后，他要求最少次数，我们考虑，我们不能使数字乘 $2$ 或 $3$，但是可以除以 $2$ 或 $3$，并且要使每个数字相等，我们进行贪心。用 $e$ 和 $s$ 数组，来记录当前数有多少个为 $2$ 和 $3$ 的质因子。我们用 $x$ 来表示除完后相同的数字（即任意一个 $b_i$），那么相同的数字就是 $x \times \min e \times \min s$。

那么除的次数就是除掉的数的总数，为 $\sum_{i=1}^n (e_i-\min e+s_i-\min s)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=1e5+5,inf=0x3f3f3f3f;
int n,a[N],b[N],e[N],s[N];
int solve(){
	for(int i=1;i<n;i++)
		if(b[i]!=b[i+1])return -1;
	int mine=inf,mins=inf,ans=0;
	for(int i=1;i<=n;i++)mine=min(mine,e[i]),mins=min(mins,s[i]);
	for(int i=1;i<=n;i++)ans+=e[i]-mine+s[i]-mins;
	return ans;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++){
		b[i]=a[i];
		while(b[i]%2==0)b[i]/=2,e[i]++;
		while(b[i]%3==0)b[i]/=3,s[i]++;
	}
	printf("%lld",solve());
	return 0;
}		
```


---

## 作者：MoyunAllgorithm (赞：0)

在题解的基础上对错解举出了反例qwq。

**题意**

给你数组 $A$，你要进行至少 $0$ 次操作（每次二选一）：

1. 选择一个元素 $a_i$ 满足 $a_i$ 是 $2$ 的倍数。将它除以 $2$。

2. 选择一个元素 $a_i$ 满足 $a_i$ 是 $3$ 的倍数。将它除以 $3$。

直到让该数组所有值相同。输出最小的操作数或判断无解。

**分析**

设最后的数组元素的值是 $k$，那么原数组的每一个元素都可以表示为

$a_i=k \times 2^x \times 3^y(x,y \ge 0)$。

只要我们求出 $k$，就能解决这个问题了。

**如何求出 $k$？**

你可能会想到：把每个数都尽可能地除以 $2$ 和 $3$，取剩下的。但这个方法是错的，例如 $a=\{28,42\}$，如果直接除掉，那么会变成 $\{7,7\}$。但是，我们显然可以找到一个**更优的** $k=14$ ~~（我不会告诉你们比赛时我因为这么写吃了一次罚时）~~。

事实上，我们想到：我们不一定要让所有元素都把自己所有是 $2$ 和 $3$ 的因数除掉。如果 $a$ 数组的最大公约数中包含了 $2$ 或 $3$，那么我们完全可以保留它们，因为这不会影响数组所有值相同。

因此，我们可以设 $k$ 为 $\gcd(a_1,a_2,\cdots,a_N)$。
之后，我们设 $rest_i = \dfrac{a_i}{k}$。如果 $rest_i$ 包含除了 $1,2,3$ 以外的其它质因数，那么是无解的；否则，我们需要进行 $rest_i$ 分解质因数后 $2$ 的个数与 $3$ 的个数之和次操作。


**~~喜闻乐见的~~AC CODE**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1005;
int N;
int a[MAXN];
int cnt2[MAXN],cnt3[MAXN];
int gcd(int x,int y)
{
	if(x%y==0) return y;
	return gcd(y,x%y);
}
int di;
int x;
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",&a[i]);
	di=a[1];
	for(int i=2;i<=N;i++) di=gcd(di,a[i]);
	int ans=0;
	for(int i=1;i<=N;i++)
	{
		if(a[i]%di)
		{
			puts("-1");
			return 0;
		}
		int rest=a[i]/di;
		int cnt=0;
		while(rest%2==0)
		{
			rest/=2;
			cnt++;
		}
		while(rest%3==0)
		{
			rest/=3;
			cnt++;
		}
		if(rest!=1)
		{
			puts ("-1");
			return 0;
		}
		ans+=cnt;
	}
	printf("%lld\n",ans);
	return 0;
}
```
考场代码略显潦草qwq




---

## 作者：FReQuenter (赞：0)

## 思路

显然，最后如果可行的话，每个数一定都会为所有数的 $\gcd$。

于是，我们可以搜索每一个数通过除以 $2$ 或除以 $3$ 能否达到 $\gcd$，如果有一个数不可以，就直接输出 $-1$。如果所有数都可以达成，答案就是每个数除以到 $\gcd$ 的最短步数之和。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1005],n,g;
pair<int,bool> dfs(int x){
  pair<int,bool> ans={0x3f3f3f3f,0},tmp={-1,0};
  if(x==g) return {0,1};//边界，已经搜索到了gcd，可行
  if(x%2==0) tmp=dfs(x/2);//除以 2 的分支
  if(tmp.second) ans.first=min(ans.first,tmp.first),ans.second=tmp.second;//如果可行，准备返回答案，答案先暂存，最后取max
  if(x%3==0) tmp=dfs(x/3);//除以 3 的分支
  if(tmp.second) ans.first=min(ans.first,tmp.first),ans.second=tmp.second;//如果可行，准备返回答案，答案先暂存，最后取max
  ans.first++;//往下除的一步加上
  return ans;
}
signed main(){
	cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i],g=__gcd(a[i],g);//求gcd
  int sum=0;
  for(int i=1;i<=n;i++){
    pair<int,bool> p=dfs(a[i]);
    if(p.second) sum+=p.first;
    //dfs返回一个pair(达成步数，是否可达成)
    else{
      cout<<-1;
      return 0;
      //不可行
    }//cout<<p.first<<' ';
  }
  cout<<sum;
	return 0;
}
```

---

## 作者：Y2y7m (赞：0)

发现他们最后要变成的数是所有数的最大公约数，把最大公约数求出来，设其为 $g$。

设 $a_i$ 除以 $g$ 的值为 $b_i$，如果 $b_i$ 含有除 $2$ 的倍数和 $3$ 的倍数以外的的因子，则无解，否则计算出因子 $2$ 和 $3$ 的个数，加入答案即可。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
int n;
int a[1010];
int gcd(int x,int y)
{
	if(y==0)
		return x;
	return gcd(y,x%y);
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int g=0;
	for(int i=1;i<=n;i++)
	{
		g=gcd(g,a[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int t=a[i]/g;
		int cnt2=0,cnt3=0;
		while(t%2==0)
		{
			t/=2;
			cnt2++;
		}
		while(t%3==0)
		{
			t/=3;
			cnt3++;
		}
		if(t!=1)
		{
			cout<<-1<<endl;
			return 0;
		}
		ans+=cnt2+cnt3;
	}
	cout<<ans<<endl;
	return 0;
}

```

好奇怪，为什么 $n\leq 1000$ 啊。

---

## 作者：JiaY19 (赞：0)

### 题意

每次选择一个能被 $2$ 或 $3$ 整除的数，并将他除以 $2$ 或 $3$。

问将所有数变成相等的最小方案数，无解输出 $-1$。

### 思路

考虑首先求出所有数的 $\text{gcd}$，也就是我们最后所有数相等的数。

如何将每一个数来变成 $\text{gcd}$。

我们只需要判断这个数与 $\text{gcd}$ 的商是否为只包含质因子 $2,3$。

若不是，那么即为无解。

否则，直接计算步骤即可。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N = 1000010;
 
int n , m , a[N];
 
inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}
 
inline int calc(int x)
{
    int res = 0;
    while(x % 2 == 0)
        res++, x /= 2;
    while(x % 3 == 0)
        res++, x /= 3;
    return res;
}
 
inline bool check(int x)
{
    while (x % 2 == 0) x /= 2;
    while (x % 3 == 0) x /= 3;
    return x == 1;
}
 
signed main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    int x = a[1] , ans = 0;
    for (int i = 1; i <= n;i++)
        x = __gcd(x , a[i]);
    for (int i = 1; i <= n;i++)
    {
        if(a[i] % x != 0 || !check(a[i] / x))
            puts("-1"), exit(0);
        ans += calc(a[i] / x);
    }
    cout << ans << endl;
    return 0;
}
```

---

