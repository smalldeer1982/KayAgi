# Parity and Sum

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$。

每次操作中，你可以选择任意一个数对 $(i,j)$，使得 $a_i$ 和 $a_j$ 奇偶性不同，即 $a_i$ 和 $a_j$ 既不同为奇数也不同为偶数。然后将 $a_i$ 和 $a_j$ 中值较小的那一个的元素的值替换为这两个元素的和，即：

- 如果 $a_i<a_j$，那么将 $a_i$ 替换为 $a_i+a_j$。
- 否则将 $a_j$ 替换为 $a_i+a_j$。

现在需要通过若干次上述操作使得数组 $a$ 中所有元素的奇偶性相同。请你求出最少需要多少次操作。

## 说明/提示

对于所有数据：

- $1\leqslant T\leqslant 10^4$。
- $1\leqslant n\leqslant 2\times10^5$，$\sum n\leqslant 2\times 10^5$。
- $\forall i\in[1,n],1\leqslant a_i\leqslant 10^9$。

Translated by [Eason_AC](/user/112917)。

## 样例 #1

### 输入

```
7
5
1 3 5 7 9
4
4 4 4 4
3
2 3 4
4
3 2 2 8
6
4 3 6 1 2 1
6
3 6 1 2 1 2
5
999999996 999999997 999999998 999999999 1000000000```

### 输出

```
0
0
2
4
3
3
3```

# 题解

## 作者：MorLeaves (赞：2)

## **题意：**

有一个长度为 $n$ 的序列 $\{a_1,a_2 \dots a_n \}$，你需要进行尽可能少的操作，使该序列的所有数的奇偶性相同。

对于一次操作，你可以选择一对 $(i,j)$，若 $a_i<a_j$，则将 $a_i \leftarrow a_i+a_j$；否则 $a_j \leftarrow a_i+a_j$。

求最小的操作次数，使得最后该序列的所有数奇偶性相同。

## **思路：**

首先分析加法的奇偶性，可以知道：

奇数+奇数=偶数；奇数+偶数=奇数；偶数+偶数=偶数。

下面称奇数相加为操作一，奇偶相加为操作二，偶数相加为操作三。

解决本题的一个关键就是如何确定序列最后所有数的奇偶性，我们要么通过操作把所有的奇数变为偶数，要么。我们需要分析三个操作后的结果：

因为最后要使所有数奇偶性相同，所以操作三没有意义；

如果要把所有偶数变为奇数，可以使用操作二，若奇数 $a_i$ 大于 偶数 $a_j$，则进行一次操作二后可以将 $a_j \leftarrow a_i+a_j$ 此时 $a_j$ 变为奇数；若奇数 $a_i$ 小于偶数 $a_j$，进行一次操作二后 $a_i \leftarrow a_i+a_j$，此时 $a_i$ 仍为奇数且一定有 $a_i>a_j$，再进行一次操作即可；

如果要把所有奇数变为偶数，则只有进行操作一才能达成目的，若序列有多个奇数，选择任意两个奇数进行操作一后，最后一定会剩下一个奇数无法继续进行操作变为偶数。

所以得出结论：进行若干次操作后，最后序列的所有数一定都为奇数（忽略初始序列全为偶数的情况）。

我们想要让所有偶数变为奇数，只需使用操作二即可。若奇数 $a_i$ 大于偶数 $a_j$，只需进行一次操作二后将 $a_j$ 变为奇数；反之，需要进行两次操作二后达成目的。因为要尽可能使操作次数最少，所以我们需要选择初始序列中最大的奇数与所有偶数进行操作，操作的大小顺序还要进行决策。

我们发现，在将偶数变为奇数的过程中有时只需进行一次操作，有时需要进行两次操作（也就是 $a_i<a_j$ 的情况），我们把它称为“卡壳”。我们自然希望将偶数从小到大进行操作，中间没有“卡壳”，这样就可以保证对于每个偶数只进行一次操作，答案即为初始序列中偶数的个数；如果出现了“卡壳”，那我们不如直接从最大的偶数开始操作，因为这样可以保证两次操作后的奇数 $a_i$ 一定大于所有偶数（这是因为 $a_i$ 本身已经加上了最大的偶数），这样答案即为初始序列中偶数的个数 + 1 。这样整个问题就解决了。

## **CODE:**

最后奉上带注释的代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
using namespace std;
ll T,n,a[200005],x[200005];
// x 数组用来存储初始序列中的偶数。
int main() {
	scanf("%lld",&T);
	while(T--) {
		scanf("%lld",&n);
		ll maxn=0,s=0,k=0;
		// maxn 存储初始序列中最大的奇数，s 为判断是否“卡壳”的求和器，k 为 x 数组的移动下标。
		for(ll i=1;i<=n;i++) {
			scanf("%lld",&a[i]);
			if (a[i]%2==1) maxn=max(maxn,a[i]);
			else k++,x[k]=a[i];
		}
		if (maxn==0) {
    //若序列中没有奇数，则直接输出 0 。
			printf("0\n");
			continue;
		}
		sort(x+1,x+k+1);//将初始序列中的偶数进行排序。
		s+=maxn; // s 判断当前之和是否会“卡壳”
		bool bo=false;。
		for(ll i=1;i<=k;i++) {
			if (s<=x[i]) {
				bo=true;
				break;
			}
			s+=x[i];
			x[i]=0;//注意多测清空。
		}
		printf("%lld\n",k+bo);
	}
	return 0;//完结撒花！！！
}
```

---

## 作者：wyydom (赞：1)

### 写在前面

本题解使用优先队列写的，如果不会建议先去学习一下

# 题目大意

翻译来源：deepl

给定一个由 $n$ 个正整数组成的数组 $a$。

在一次操作中，你可以选取任意一对索引 $(i,j)$，使得 $a_i$ 和 $a_j$ 具有不同的奇偶性，然后用它们的和替换较小的那个。更正式的说法是如果是 $a_i<a_j$，则用 $a_i+a_j$ 替换 $a_i$；否则，用 $a_i+a_j$ 替换 $a_j$。

求使数组中所有元素具有相同奇偶性所需的最少操作数。

# 思路

关于题目，首先要分开奇数与偶数，由题我们可知：本题应分讨：

- 若全为奇数或偶数

 则可以直接
```
    printf("0\n");  
```  

- 否则应当用奇数+偶数

此时生成应全为奇数（奇数与偶数生成奇数）。

为使生成的数尽可能大（防止后面出现本可以直接替换的偶数无法被替换），我们应当使用最大的奇数与最小的偶数来组成一个 $(i,j)$。

如果最大奇数小于最小偶数，为使后面的所有偶数均可被奇数替代（即使此次运算意义最大），我们可以直接使最大奇数与最大偶数形成一个 $(i,j)$
否则可以直接替换.

**实现方式：优先队列**


    #include <bits/stdc++.h>  
    using namespace std;  
    
    //大奇+小偶->奇数  
    
    priority_queue<int> q1;  //存放奇数（大根堆）  
    priority_queue<int, vector<int>, greater<int> > q2;  //存放偶数（小根堆）  
    
    int n, m, c, a, b, ans, ma;  
    
    void pu(int a) {  //输入  
      if (a % 2 == 1) {  
        q1.push(a);  
        return;  
      }  
      if (ma < a) ma = a;  
      q2.push(a);  
      return;  
    }  
    void clear() {  
      while (!q1.empty()) q1.pop();  //使q1为空  
      while (!q2.empty()) q2.pop();  //使q2为空  
      return;  
    }  
    void tdo(int q11, int q22) {  
      if (q11 > q22) {  
        q2.pop();  
        q1.push(q11 + q22);  
      } else {  
        q1.push(q11 + ma);  //加最大偶数  
        ans +=  q2.size();  //因为此时对于q2中任意一个数，都小于q11+ma，则可以直接+q2.size();  
        clear();        //使q2为空，减少运算量  
      }  
      ans++;  
      return;  
    }  
    
    int main() {  
      scanf("%d", &m);  
      for (int z = 1; z <= m; z++) {  
        scanf("%d", &n);  
        //初始化  
        ans = 0;  
        clear();  
        //输入  
        for (int i = 1; i <= n; i++) {  
          scanf("%d", &a);  
          pu(a);  
        }  
        //全为奇数或全为偶数  
        if (q1.empty() || q2.empty()) {  
          printf("0\n");  
          continue;  
        }  
        //运算直到q2为空  
        while (!q2.empty()) tdo(q1.top(), q2.top());  
        //输出结果  
        printf("%d\n", ans);  
      }  
      return 0;  
    }  



#### 鸣谢
感谢[@qifan_maker](https://www.luogu.com.cn/user/706607) 
为本文的latex格式设置做出了巨大贡献

---

## 作者：donnieguo (赞：1)

## 思路

首先如果所有的数奇偶性都相同，那么直接输出 $0$ 即可，因为不需要任何操作。

其次我们需要知道，如果有两个奇偶性不同的数，那么它们加起来的和一定是奇数，所以我们只可能将所有的数全部都变成奇数。

这里考虑贪心。

记这个序列中最大的奇数为 $k$，然后将 $k$ 与每一个偶数进行比较，记当前遍历到的偶数为 $t$，则：

- 若 $k > t$，那么将 $k$ 加上 $t$；

- 若 $k < t$，那么将最大的偶数与 $k$ 进行 $1$ 次操作，使 $k$ 成为 $\max(a_1,a_2,\cdots,a_n)$。当然，这种情况最多出现 $1$ 次。

最后的答案就是这个序列中偶数的数量，如果出现了第二种情况 $+1$ 即可。

### 实现需要注意的地方

- 需要对所有的偶数排序。有人肯定会问，为什么？

  考虑如下数据：

  ```
  5
  5 10 2 2 2
  ```

  很显然，如果不排序的话答案是 $5$，但实际上答案是 $4$。

  原因就是有可能没排序时会出现第二种情况，排序后没有出现。也就是说排完序后的答案一定更优。

- **记得开 `long long`。**

时间复杂度 $\Theta(n \log n)$，瓶颈在排序。

## AC code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define N 200010
#define int long long
using namespace std;

int T, n;
int a[N];
vector <int> v;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--)
	{
		v.clear();
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		int maxn = -1;
		for (int i = 1; i <= n; i++)
		{
			if (!(a[i] % 2)) v.push_back(a[i]);
			else maxn = max(maxn, a[i]);
		}
		sort(v.begin(), v.end());
		int sz = v.size(), flag = 0;
		if (!sz || maxn == -1) {cout << 0 << '\n'; continue;}
		for (int i = 0; i < sz; i++)
		{
			if (v[i] < maxn) maxn += v[i];
			else flag = 1;
		}
		cout << sz + flag << '\n';
	}
	return 0;
}
```

---

## 作者：UniGravity (赞：1)

## Solution CF1993B Parity and Sum
标签：贪心

由于奇数加偶数等于奇数，所以除了一开始全为偶数的情况，最后的结果必定是全为奇数。

那么贪心的想，设 $x$ 为当前最大的奇数，则对于一个偶数 $a_i$ 必定与 $x$ 进行操作。

若 $a_i<x$，则进行一次操作。由于每个偶数至少操作一次，发现这样肯定不劣。我们想让这样的操作仅可能多，对 $a$ 从小到大排序，依次处理。这样 $x$ 会随着操作越来越大。

对于剩余的 $a_i>x$，发现只要进行两次操作就可以把其变为奇数。可以想到拉出剩余的最大的 $a_i$ 进行操作，这样就可以尽可能增大 $x$，使得其他小于 $a_i$ 的数只需一次操作。

[code](https://codeforces.com/contest/1993/submission/274375782)

---

## 作者：GeXiaoWei (赞：1)

# Parity and Sum
## 解析
本题考察贪心，难度在橙题左右。

根据小学内容：奇数加奇数等于偶数，偶数加偶数等于偶数，奇数加偶数等于奇数可知，如果给定的数列 $a$ 不是全为偶数，最后一定会全变为奇数。

考虑贪心，首先找出最大奇数与最大偶数，让最大奇数每次与最小偶数进行操作。如果是小于，只需要操作一次。否则需要进行两次。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,a[400005],ans,ma,maxx,cnt,pd;
int main(){
    scanf("%lld",&t);
	while(t--){
	    scanf("%lld",&n);ans=ma=maxx=cnt=pd=0;
	    for(int i=1;i<=n;i++){
	        scanf("%lld",&a[i]);
	        if(a[i]%2==0) cnt++,maxx=max(maxx,a[i]);
	    }
	    sort(a+1,a+n+1);
	    for(int i=n;i;i--){
	        if(a[i]&1){
	            pd=i,ma=a[i];
	            break;
	    	}
		}
	    if(!pd){
	        printf("0\n");
	        continue;
	    }
	    for(int i=1;i<=n;i++){
	        if(a[i]%2==0){
	            if(a[i]<ma) ma=max(ma+a[i],ma),ans++;
	            else ans+=2,ma=max(ma,ma+ maxx);
	        }
	    }
		printf("%lld\n",ans);
	}
    return 0;
}
```

---

## 作者：tzzl3035 (赞：0)

# 1993B 题解
### 题目大意
有 $t$ 组数据，每组给出一个正整数 $n$ 和 $n$ 个正整数 $a_i$。定义一次操作为选择两个奇偶性不同的正整数 $a_i$ 和 $a_j$，若 $a_i < a_j$，则将 $a_i$ 替换为 $a_i + a_j$，否则将 $a_j$ 替换为 $a_i + a_j$。问至少通过几次操作能让数组中每一个正整数奇偶性相同。
### 大致思路
奇数与偶数相加得奇数，所以，若数组中皆是偶数，结果为 $0$，否则排序数组后不断将偶数加上数组中最大的奇数并将结果加一，若该奇数比偶数小，则将该奇数加上数组中最大的数并将结果再加一即可。
### 核心代码
```cpp
void solve() {
  // 输入
  int n;
  std::cin >> n;
  std::vector<long long> a(n+3);
  for(int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  std::sort(a.begin()+1, a.begin()+n+1); // 排序
  // 找出最大的奇数
  int ind = 0;
  for(int i = n; i >= 1; --i) {
    if(a[i] & 1) {
      ind = i;
      break;
    }
  }
  // 若数组全是偶数，结果为 0
  if(ind == 0) {
    std::cout << 0 << '\n';
    return;
  }
  // 统计答案
  long long omin = a[ind], ans = 0;
  for(int i = 1; i <= n; ++i) {
    if(a[i] % 2 == 0) {
      if(a[i] <= omin) ++ans, omin = std::max(omin, a[i] + omin);
      else {
        ans += 2;
        omin += a[n];
      }
    }
  }
  // 输出
  std::cout << ans << '\n';
}

```
### [RESULT](https://codeforces.com/contest/1993/submission/274383739)

---

## 作者：myyyIisq2R (赞：0)

要通过序列原数加和替换的方式使整个序列的奇偶性相同。容易想到奇 $+$ 偶 $=$ 奇，所以最终目标必然是将所有偶数换成奇数。

最少次数一定是每一个偶数都 **只用一次操作** 就能被换掉，那什么情况下不能只用一次？当所有序列中的奇数都比这个偶数小的时候。这时就需要有一个奇数先和这个偶数加一下，变成一个更大的奇数，再换掉这个偶数。我们一定要求这样的“转换操作”次数尽可能少，那么贪心地处理，每次让当前序列中**最大的奇数**和**最大的偶数**进行这样的“转换操作”，就能使每一次“转换”效益最大化。
```cpp
int T = read();
while(T--)
{
	int n = read();
	int cnt1{},cnt2{};
	int maxj = -INT_MAX;
	vector<int>o;
	for(int i{1};i<=n;i++) 
	{
		a[i] = read();
		if(a[i] & 1) cnt1++,maxj = max(maxj,a[i]);
		else cnt2++,o.push_back(a[i]);
	}
	if(cnt1 == 0 || cnt2 == 0) {writeln(0);continue;}
	sort(o.begin(),o.end());
	int ans{};
	for(int i:o)
	{
		if(i < maxj) ans++,maxj = i+maxj;
		else 
			maxj+=o.at(o.size()-1),o.pop_back(),ans+=2;
	}
//		writeln(maxj);
	writeln(ans);
}
```

---

## 作者：Heldivis (赞：0)

## CF1993B Parity and Sum

考虑对于两个奇偶不同的数相加，显然和为奇数。所以只要不是开始就是全为偶数，最终结果一定全为奇数。

那么就有一个很直接的思路：选取最大的奇数，按照一定顺序，操作序列并更新最大奇数。

考虑对于一个奇数 $m$ 和偶数 $a$，想要把 $a$ 变成奇数的情况为（箭头表示一次操作）：

- $a > m\quad(m, a)\to(m+a, a)\to (m+a,m+2a)$
- $a < m\quad(m, a)\to(m, a + m)$

所以，每次选取小于 $m$ 的整数。这些数一定是对 $m$ 有一次贡献、对答案有一次贡献。如果实在没有，那么选取最大数，这样可以让 $m$ 尽可能大，以减少两次操作的机会。

代码：

```cpp
void Main() {
  n = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
  bool all_same = true;
  for (int i = 2; i <= n; ++i)
    all_same = all_same && (a[i] % 2 == a[i - 1] % 2);
  if (all_same) return void(puts("0"));
  maxx = 0, ans = 0;
  for (int i = 1; i <= n; ++i)
    if (a[i] % 2) maxx = max(maxx, a[i]);
  multiset<ll> s;
  for (int i = 1; i <= n; ++i)
    if (a[i] % 2 == 0) s.insert(a[i]);
  while (s.size()) {
    auto it = s.begin();
    if (*it < maxx)
      ans++, maxx += *it;
    else
      it = --s.end(), ans += 2, maxx += *it * 2;
    s.erase(it);
  }
  printf("%lld\n", ans);
}
```

---

## 作者：yanlikun (赞：0)

# 思路
很显然的，只要出现了奇数，那么整个序列最终必然全部变为奇数。那么，我们每次选用最大的奇数同最小的偶数进行操作，每次将一个偶数变为奇数至多需要两次操作。同时，我们也需要同另一种情况比较：用最大的奇数同最大的偶数操作，至多用偶数数量 $+1$ 次，至少用偶数数量次。选取两种情况中较少的一个即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
ll b[200005];
int main()
{
	cin>>t;
	while(t--)
	{
		int n;
		ll maxa=0,ans=0,sumb=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			ll x;
			cin>>x;
			if(x%2==1)
				maxa=max(maxa,x);
			else
				b[++sumb]=x;
		}
		if(sumb==0||maxa==0)
		{
			cout<<"0\n";
			continue;
		}
		sort(b+1,b+sumb+1);
		for(int i=1;i<=sumb;i++)
		{
			if(maxa>1e9)
			{
				ans+=sumb-i+1;
				break;
			}
			if(maxa<b[i])
				maxa+=b[i]*2,ans+=2;
			else
				maxa+=b[i],ans++;
		}
		cout<<min(ans,sumb+1)<<"\n";
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
显然，每次操作永远不会减少奇数的个数，所以除非最开始全偶数，否则最终一定要变成全奇数。所以，我们可以把偶数从小到大排序，用最大的奇数去不断“吞并”最小的偶数，如果可以吞并完，则答案是偶数的个数；否则就要让最大的偶数给最大的奇数加一次，再加回去变成奇数就行啦。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, s;
ll a[200005], maxo, maxe;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n, s = maxo = maxe = 0;
		for (int i = 0; i < n; ++ i) {
			cin >> a[i];
			if (a[i] & 1)
				maxo = max (maxo, a[i]);
			else
				maxe = max (maxe, a[i]), ++ s;
		}
		if (! maxo || ! maxe)
			cout << "0\n";
		else {
			sort (a, a + n);
			for (int i = 0; i < n; ++ i)
				if (! (a[i] & 1) && a[i] < maxo)
					maxo += a[i];
			cout << s + (maxo < maxe) << '\n';
		}
	}
	return 0;
}
```

---

