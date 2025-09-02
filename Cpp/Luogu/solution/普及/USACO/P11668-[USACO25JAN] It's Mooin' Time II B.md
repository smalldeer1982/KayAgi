# [USACO25JAN] It's Mooin' Time II B

## 题目描述

Farmer John 正在试图向 Elsie 描述他最喜欢的 USACO 竞赛，但她很难理解为什么他这么喜欢它。他说「竞赛中我最喜欢的部分是 Bessie 说 『现在是哞哞时间』并在整个竞赛中一直哞哞叫」。

Elsie 仍然不理解，所以 Farmer John 将竞赛以文本文件形式下载，并试图解释他的意思。竞赛被定义为一个包含 $N$（$1\le N\le 10^6$）个整数的数组 $a_1, a_2, \dots, a_N$（$1\le a_i\le N$）。Farmer John 定义哞叫为一个包含三个整数的数组，其中第二个整数等于第三个整数，但不等于第一个整数。一种哞叫被称为在竞赛中发生，如果可以从数组中移除整数，直到只剩下这一哞叫。

由于 Bessie 据称「在整个竞赛中一直哞哞叫」，请帮助 Elsie 计算竞赛中发生的不同哞叫的数量！两种哞叫是不同的，如果它们并非由相同的整数以相同的顺序组成。

## 说明/提示

### 样例解释

竞赛包含三种不同的哞叫："1 4 4"，"2 4 4" 和 "3 4 4"。

### 子任务

- 测试点 2-4：$N\le 10^2$。
- 测试点 5-7：$N\le 10^4$。
- 测试点 8-11：没有额外限制。

## 样例 #1

### 输入

```
6
1 2 3 4 4 4```

### 输出

```
3```

# 题解

## 作者：wanganze (赞：5)

### 题意
竞赛被定义为一个包含 $N$（$1\le N\le 10^6$）个整数的数组 $a_1, a_2, \dots, a_N$（$1\le a_i\le N$）。Farmer John 定义哞叫为一个包含三个整数的数组，其中第二个整数等于第三个整数，但不等于第一个整数。一种哞叫被称为在竞赛中发生，如果可以从数组中移除整数，直到只剩下这一哞叫。

由于 Bessie 据称「在整个竞赛中一直哞哞叫」，请帮助 Elsie 计算竞赛中发生的不同哞叫的数量！两种哞叫是不同的，如果它们并非由相同的整数以相同的顺序组成。

即给定一个序列，求有多少个“ABB”子序列。

### 思路
进行预处理，求出前 $i$ 个字符中出现的不同元素数 $s_i$，顺便记录元素 $a_i$ 第一次出现的位置。

我们从后往前扫，遇到出现两次的整数“ B ”就根据前面出现过的“ A ”种类数，计算后两个整数为“ B ”的方案数。由于取的是最后两个“ B ”，所以一定会包含所有的可能。注意排除“ BBB ”，即“ B ”如果首次出现在最后两个“ B ”之前，要排除掉。

### 实现

**记得开 long long。**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long LL;
int a[N],b[N],c[N],s[N];
LL res;
int main()
{
	int n;
	cin>>n;
	for(int i = 1; i <= n; i ++) scanf("%d",&a[i]);
	for(int i = 1; i <= n; i ++)
		if(!c[a[i]]) c[a[i]] = i,s[i] = s[i - 1] + 1;
		else s[i] = s[i - 1];
	for(int i = n; i >= 1; i --)
		if(++ b[a[i]] == 2) res += s[i - 1] - (c[a[i]] < i);
	cout<<res<<endl;
	return 0;
}
```
复杂度 $O(n)$，可以通过。

---

## 作者：_xdd_ (赞：3)

首先容易想到，如果一个数出现两次，那么答案就增加这个数字前面与他不同的数字的种类，比如样例 #1 中，因为数字 $4$ 出现了大于两次，答案就为 $4$ 前面的数字种类 $3$ 种，计数可以使用桶计数实现。

以上算法如果直接倒着遍历，复杂度是 $\mathcal{O}(n^2)$ 的，会 TLE。

复杂度的瓶颈在于找到两个相同数字后的向前的查找，定义 $sum_i$ 为截止第 $i$ 位前面的数字种类，这里用前缀和实现，如果发现了新的数字，就把这个位置设为 $1$，其他位置设为 $0$，做一个前缀和，查找到两个相同数字后，就 $ans\leftarrow ans+sum_{i-1}$。

最后，因为会出现 `1 1 1` 这样三个数字相同的情况，因为前面我们给每个数字做了计数，遍历数列里每个数字，对于某个数字，如果出现了 $3$ 次及以上，那么他肯定至少有一个类似上面的错解，$ans\leftarrow ans-1$。


```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define maxn 1000000+5
#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int n,a[maxn],cnt[maxn],sum[maxn],ans;
bool flag[maxn];
signed main(){
    cin >> n;
    //预处理
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(flag[a[i]]==0){
            sum[i]++;
        }
        flag[a[i]]=1;
        sum[i]+=sum[i-1];
    }
    //找解
    for(int i=n;i>=1;i--){
        cnt[a[i]]++;
        if(cnt[a[i]]==2){
            ans+=sum[i-1];
        }
    }
    //最后检查错解
    for(int i=1;i<=n;i++){
        if(cnt[i]>=3){
            ans--;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Asaha_Akina (赞：2)

算法标签
---
- 贪心
- 前缀和

题目大意
---

给定长度为 $n$ 的序列 $S$ ，问在 $S$ 中有多少种不同的三元组 $(t_1, t_2, t_3)$ 使得 $t_1 \neq t_2 = t_3$ ，且 $\{t_1, t_2, t_3\}$ 为 $S$ 的连续或非连续子序列。\
若两个三元组中有任何一个元素不同，则两个三元组不同。

思路分析
---
由于 $t_2 = t_3$，出现次数大于等于 $2$ 次的数字才有可能作为 $t_2$ 和 $t_3$ 从而组成符合题意的三元组，我们可以通过记录每一个数字的出现次数来找出有重复的数字，让这些重复出现过的数字组成集合 $A$。\
另外考虑一种贪心的思想：对于任意 $a \in A$ ，选取 $S$ 中倒数第二个和最后一个 $a$ 作为 $t_2, t_3$ 时向前处理即可获得此情况下的全部合法三元组；因为 $\{t_1, t_2, t_3\}$ 为 $S$ 的子序列和题意里合法三元组的构造条件，这样的贪心是正确的。这样一来，我们只需记录 $a$ 在 $S$ 中出现时的索引次大值 $i$（$a$ 在 $S$ 中倒数第二次出现时的索引）和索引最大值 $j$（$a$ 在 $S$ 中最后出现时的索引），即可处理出 $a$ 对于答案的最大贡献值 $d_a$。\
而贡献值 $d_a$ ，即为区间 $[1, i - 1]$ 中的最长不重复子序列长度，也就是此区间内不同数字的个数。我们通过引入前缀和数列 $prefixSum$ 来解决此问题，只需要在读入数字时对每个数字第一次出现时的位置 $pos$ ，令 $prefixSum[pos] = 1$，再从头处理 $prefixSum$ 数组，这时有：
$$d_a = prefixSum[i] - 1$$
其中 $-1$是为了防止 $a$ 本身被错误地算入答案中，如对于以下案例，如果不减去 $1$ 就会错误计算 $d_5$ 的值：
$$S = \{1,2,5,3,4,5,5\}$$
$$prefixSum[5] = 5 \,\, {\color{red}\neq} \,\, d_5 = 4$$
最后，设答案为 $ans$ ，有：
$$ans = \sum_{a \in A} d_a $$
输出 $ans$ 即可。
$$ 时间复杂度\,\,\,O(n)$$

参考代码
---

```cpp
//C++
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    //输入输出加速
    int total;
    cin >> total;
    //输入序列长度
    vector<int> count (total, 0);
    //记录每个数字的出现次数
    vector<int> posiA (total, -1);
    vector<int> posiB (total, -1);
    //以上用于记录每个数字最后两次出现时的位置（索引）
    vector<int> a;
    //记录重复出现过的数字（出现次数 >= 2)
    int prefixSum[1000020];
    memset(prefixSum, 0, sizeof(prefixSum));
    //引入前缀和数组prefixSum
    for (int i = 0; i < total; i++) {
        int input;
        cin >> input;
        //输入序列中第 i 个数字
        count[input]++;
        //第 i 个数字出现次数 + 1
        if (count[input] == 1) {
            posiA[input] = i;
            prefixSum[i] = 1;
            //如果首次出现, prefixSum[i]设置为 1
        } else if (count[input] == 2) {
            posiB[input] = i;
            a.push_back(input);
            //如果数字重复出现，填入集合 A
        } else if (count[input] >= 3) {
            posiA[input] = posiB[input];
            posiB[input] = i;
            //如果出现次数多于2次，记录最后两次出现的位置
        }
    }
    for (int i = 1; i < total; i++) {
        prefixSum[i] = prefixSum[i - 1] + prefixSum[i];
    }
    //处理前缀和数组
    int ans(0);
    for (int i : a) {
        ans += prefixSum[posiA[i]] - 1;
    }
    //求出答案
    cout << ans;
    //输出
    return 0;
}
```
**除夕快乐！新年快乐！**

---

## 作者：nbhs23a28 (赞：2)

本题是道典型的带贪心思想的桶标记题。

根据题意，“在竞赛中发生的哞叫”即原数组中满足 $a_i \ne a_j$ 且 $a_j=a_k$ $(1 \le i<j<k \le N)$ 的三元子序列，而要求的则是不同的这样的三元子序列个数。

看到这样的描述，第一时间我们想到的就是贪心。具体来说，我们可以先找到相等的两数 $a_j$ 和 $a_k$，再向前寻找 $a_i$。在此过程中，很容易发现在 $a_j$ 值一定时，当 $j$ 越大，$i$ 的范围也越大，从而在 $j$ 达到可达的最大值时，此 $a_j$ 值下满足条件的子序列总数就是 $a_1$ 至 $a_{j-1}$ 中不同值的数量（去除 $a_j$ 自身的值），而此时的 $j$ 不正是原数组中倒数第 $2$ 个值为 $a_j$ 的数吗？

再看本题数据范围，$N \le10^6$ 限制了时间复杂度要为线性，而 $1 \le a_i \le N$ 这个性质透露给我们一个信息：可以把数装进计数桶里，像[计数排序](https://oi.wiki/basic/counting-sort/)那样。

综上，我们得到了解决本题的思路方向：以桶标记的方式在线性时间内求得数组中每个重复值倒数第 $2$ 次出现的位置 $j$ 和此时 $a_1$ 至 $a_{j-1}$ 中不同值的数量（去除 $a_j$ 自身的值）。考虑到同时查找难以线性达成，所以可以先线性查找 $j$，再对这些位置做标记线性地动态维护不同值个数即可。

以上描述可能有些抽象，下面呈上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000010],cnt[1000010],cntt;//cntt:不同数的数量（动态更新）;cnt数组：下标对应数数量（动态更新）
int pl[1000010];//贪心地标记每个位置是否可以对答案产生贡献
long long ans;
int main()
{cin>>n;
 for(int i=1;i<=n;i++)
  cin>>a[i];
 for(int i=n;i>=1;i--)
 {cnt[a[i]]++;
  if(cnt[a[i]]==2)
  pl[i]=a[i];
 }
 for(int i=1;i<=n;i++) cnt[i]=0;
 for(int i=1;i<=n;i++)
 {if(pl[i]!=0)
  {ans+=cntt;
   if(cnt[pl[i]]!=0)
   ans--;
  }
  if(cnt[a[i]]==0) cntt++;
  cnt[a[i]]++;
 }
 cout<<ans;
}
```

---

## 作者：CaFeO4 (赞：1)

考虑枚举最后的那两个相同的数，假设其为 $a$，显然对于 $a$ 来说，其贡献的答案就是倒数第二个 $a$ 前面所有与 $a$ 不同的数的个数。

用一个桶记录一下即可，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t,p) for(int i = s;i <= t;i += p)
#define drep(i,s,t,p) for(int i = s;i >= t;i -= p)
#ifdef LOCAL
  auto I = freopen("in.in","r",stdin),O = freopen("out.out","w",stdout);
#else
  auto I = stdin,O = stdout;
#endif
using ll = long long;using ull = unsigned long long;
using db = double;using ldb = long double;
const int N = 1e6 + 10;
int n,a[N],tot[N],ct[N];
bitset<N> vis;
signed main(){
  cin.tie(nullptr)->sync_with_stdio(false);
  cin>>n;rep(i,1,n,1) cin>>a[i];
  ll ans = 0;
  rep(i,1,n,1) tot[i] = tot[i-1] + (!ct[a[i]]++);
  memset(ct,0,sizeof ct);
  drep(i,n,1,1){
    if(ct[a[i]] == 1) ans += tot[i] - 1;
    ct[a[i]]++;
  }
  cout<<ans<<'\n';
}
```

---

## 作者：InfiniteRobin (赞：1)

## 题目大意

定义一种哞叫包含三个整数：$a,b,c$，且 $a \ne b=c $，而且这个哞叫是给定序列的子序列（不一定连续）。

问给定的长度为 $n$ 的序列 $d$ 中有多少种哞叫？

## 分析

注意到 $b=c$，可以是突破口。

问题转化为：找到两个相同的数的位置以及统计区间内不同数字的个数。

不妨设 $d_i=d_j$ 且 $i<j$。

那么这对数对答案的贡献就是区间 $[1,i-1]$ 中不同数字的个数，并且由于 $a \ne b$，所以若该区间内还有等于 $d_i$ 的数，不要忘记减一。

此外有一个小策略：由于我们想要区间 $[1,i-1]$ 中不同数字的个数尽量大，我们可以让 $i,j$ 尽量大。

具体实现的话，我们可以记录每个数字出现的位置，统计不同数字的个数即可。

时间复杂度：$O(n+w)$，$w$ 为值域。

---

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
//   原数列  统计不同数字个数 
int n,a[N],cnt[N];
//记录位置 
vector <int> pos[N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt[i]=cnt[i-1];
		//如果这个数第一次出现，个数加 1 
		if(pos[a[i]].size()==0) cnt[i]++;
		pos[a[i]].push_back(i);
	}
	
	long long ans=0;
	for(int i=1;i<=N-2;i++){
		//这个数一共出现几次 
		int o=pos[i].size();
		if(o<2) continue; //<2 无贡献 
		int p=pos[i][o-2]; //记录最大的位置 
		if(p==1) continue; //如果在最左边没有贡献 
		//cout<<p<<" ";
		if(o>=3) ans+=(cnt[p-1]-1); //如果这个数也被记到种数内，别忘记-1 
		else ans+=cnt[p-1]; //否则正常算 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：LionBlaze (赞：1)

考虑每个数字 $m$ 可以形成多少种不同的 $\text{moo}$。

显然，如果后面有至少两个数字 $o$，则可以形成 $\text{moo}$。

而前面的 $m$ 一定比后面的不劣，因为各个数字的数量单调不增。

所以我们考虑使用一个数组 $f_{i,j}$ 表示位置 $\ge i$ 的数字 $j$ 的数量。

于是我们发现空间复杂度为 $\Theta(N^2)$，无法承受。

考虑类似背包的滚动数组。

首先从后往前扫一遍，得到 $f_{1,x}$，也就是权值数组。

同时维护一个变量 $\text{cnt}$，表示位置 $\ge i$ 的出现次数 $\ge 2$ 的字母的数量，其中 $i$ 是滚动数组过程中当前的 $i$。

由于 $\text{moo}$ 中 $m$ 不能等于 $o$，所以位置为 $i$ 时答案为 $\text{cnt}-f_{i,m}$。

如何维护 $f$？显然从前往后扫，只需要把对应数字出现次数 $-1$ 即可。

如何维护 $\text{cnt}$？初始值直接从 $f$ 中获取，如果维护 $f$ 过程中把某个 $2$ 减到了 $1$，则 $\text{cnt} \gets \text{cnt}-1$。

赛时抽象代码。

```cpp
﻿#include <cstdio>

using namespace std;

int  krnlntos[1000005];
int  ntoskrnl[1000005];
bool snrlntok[1000005];
bool ntslrnko[1000005];

void sotnlnrk(int Int, int iNt, long long &longlong)
{
	int first = ntoskrnl[Int];
	int second = ntoskrnl[Int] += iNt;
	if (first < 2 && second >= 2) longlong++;
	if (first >= 2 && second < 2) longlong--;
	if (second >= 2) snrlntok[Int] = true;
	else snrlntok[Int] = false;
}

int main()
{
	int n;
	scanf("%d", &n);
	long long notsknrl = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", krnlntos + i);
		sotnlnrk(krnlntos[i], 1, notsknrl);
	}
	long long nlkrosnt = 0;
	for (int i = 1; i <= n; i++)
	{
		sotnlnrk(krnlntos[i], -1, notsknrl);
		if (ntslrnko[krnlntos[i]]) continue;
		ntslrnko[krnlntos[i]] = true;
		nlkrosnt += notsknrl - snrlntok[krnlntos[i]];
	}
	printf("%lld\n", nlkrosnt);
	return 0;
}
```

------

娱乐·闲话：

> 声明：我只公开了这一部分代码，我认为没有人可以从代码中推测出来 USACO 题目。况且我当时想的也不是正解，发完才想到正解。

![](https://s21.ax1x.com/2025/02/04/pEZbvKx.png)

![](https://s21.ax1x.com/2025/02/04/pEZbXx1.png)

![](https://s21.ax1x.com/2025/02/04/pEZbO2R.png)

---

## 作者：lkjlkjlkj2012 (赞：0)

### 思路
首先，由于一个哞叫是形如 $i,j,j$ ，其中 $i \ne j$ 。所以可以想到对于每一种叫声，计算它最后两次出现的位置中靠前的那个，记为 $la_i$ 。再记录每个位置之前出现了几种不同的叫声，记为 $dif_i$ 。就可以 $O(n)$ 统计答案啦！要注意的是，哞叫的定义中要求 $i \ne j$ ，所以可以对每一种叫声，记录 $la_i$ 前是否出现了第 $i$ 种叫声，有就需要在最终答案中减去 $1$ 。
### 代码

```cpp
// Problem: Problem 2. It's Mooin' Time II
// Contest: USACO - USACO 2025 January Contest, Bronze
// URL: https://usaco.org/index.php?page=viewproblem&cpid=1456
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
int n, a[1000005];
int cnt[1000005], la[1000005];
bool t[1000005];
int dif[1000005], cct[1000005];
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n; i >= 1; i--) {
    cnt[a[i]]++;
    if (cnt[a[i]] == 2) la[a[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    dif[i] = dif[i - 1];
    if (!t[a[i]]) dif[i]++;
    t[a[i]] = true;
    if (i < la[a[i]]) cct[a[i]] = 1;
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += dif[la[i] - 1] - cct[i];
    // cout << dif[i] << " " << la[i] << endl;
  }
  cout << ans << endl;
  return 0;
}
```

---

