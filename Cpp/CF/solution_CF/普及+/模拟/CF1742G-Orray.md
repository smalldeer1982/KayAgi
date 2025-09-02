# Orray

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

Let's define the prefix OR array $ b $ as the array $ b_i = a_1~\mathsf{OR}~a_2~\mathsf{OR}~\dots~\mathsf{OR}~a_i $ , where $ \mathsf{OR} $ represents the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). In other words, the array $ b $ is formed by computing the $ \mathsf{OR} $ of every prefix of $ a $ .

You are asked to rearrange the elements of the array $ a $ in such a way that its prefix OR array is lexicographically maximum.

An array $ x $ is lexicographically greater than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i > y_i $ .

## 样例 #1

### 输入

```
5
4
1 2 4 8
7
5 1 2 3 4 5 5
2
1 101
6
2 3 4 2 3 4
8
1 4 2 3 4 5 7 1```

### 输出

```
8 4 2 1 
5 2 1 3 4 5 5 
101 1 
4 3 2 2 3 4 
7 1 4 2 3 4 5 1```

# 题解

## 作者：沉石鱼惊旋 (赞：13)

### 题目翻译

我们定义前缀或的意思是 $or_i=or_{i-1} \operatorname{or} a_i$。

重排数组 $a$，使得它的前缀或数组的字典序最大。

### 题目思路

通过观察和思考可得，第一位一定放 $\max\limits_{1\leq i\leq n}\{a_i\}$ 才能让第一位最大，接着保证字典序最大。

那么我们考虑，对于之后每一位的答案，我们都去和前面的进行比较，看看哪一个才是这一位该放的最大的答案。这一点是很容易想到的。

那么这只是 $\mathcal O(n^2)$，很显然是会超时的。

我们考虑到，一个 `int` 类型只有 $32$ 位，那么我们只要知道这 $32$ 位能不能放上 $1$ 即可。

也就是说，如果这 $32$ 位都决策完了，我们不用继续找，后面没用过的可以直接输出。

所以我们只要判断当前操作下来的答案，和上一步操作的答案是否相同，若相同即可结束。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{	
	vector<int>ans;
	int n,maxx=-1,id;
	cin>>n;
	int a[n+1];
	int tmp[n+1];
	bool f[n+1]={};
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		tmp[i]=a[i];
		if(a[i]>maxx)
		{
			maxx=a[i];
			id=i;
		}
	}
	f[id]=1;
	ans.push_back(maxx);
	int last=maxx;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			tmp[j]|=maxx;
		}
		last=maxx;
		maxx=0;
		for(int j=1;j<=n;j++)
		{
			if(!f[j])
			{
				if(tmp[j]>maxx)
				{
					maxx=tmp[j];
					id=j;
				}
			}
		}
		f[id]=1;
		ans.push_back(a[id]);
		if(maxx==last)
		{
			for(int j=1;j<=n;j++)
			{
				if(!f[j])
				{
					ans.push_back(a[j]);
				}
			}
			break;
		}
	}
	for(int i:ans)
	{
		cout<<i<<" ";
	}
	cout<<endl;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		solve();
	}
	return 0;
}
```

[链接](https://codeforces.com/contest/1742/submission/186537251)

---

## 作者：Larry76 (赞：12)

## 题目描述:
给你一个序列 $A$，要求将 $A$ 重新排序，使得序列 $A$ 的前缀或和序列 $B$ 的字典序最大。
## 题目分析：
这道题我们首先考虑一个性质，就是前缀或和序列 $B$ 总是存在一个位置 $j$，使得 $j$ 前面形成的子序列单调递增，$j$ 及其后面形成的子序列保持不变。

此时，我们根据上面的性质，不难得出如下结论：
1. $j$ 前面的序列我们只需要保证它们或起来是不断变大的就行
2. $j$ 后面的序列我们可以随便乱放，因为此时它们不改变或起来的值。

那么，这个神奇的位置 $j$ 应该为多少呢，根据上述结论，我们不难看出，$j$ 的最大值应为 $\lceil \lg a_{\max} \rceil$，这一条结论的证明是显然的，理由如下：

因为算术操作“按位或”是没有进位的，且保证两个数按位或起来一定大于等于原先的两个数，故两个数按位或起来，其结果的二进制位数取决于两个数中较长的那个数的位数。并且，我们无法找出一个二进制位数比另个一大但数值比另一个小的两个数。所以我们可以证明，序列 $A$ 中的最大值 $a_{\max}$ 的二进制位数，就是我们要找的 $j$ 的最大值。

然后就是对于 $b_1$ 的讨论了，如果我们想要保证其字典序最大，则我们就需要保证 $0 \operatorname{or} a_i$ 最大。我们运用大眼观察法，不难看出，$b_1$ 的值为 $a_{\max}$。

根据上述内容，我们不难得出以下贪心算法：
1. 对原数组进行降序排序，将降序排序后的最大值（也就是 $a_1$ ）直接加入答案中。
2. 循环 $\lceil \lg a_{\max} \rceil$ 次，每次遍历序列 $A$，将此时 $(now \operatorname{or} a_i)_{\max}$ 中的 $a_{\max}$ 加入答案，并将 $a_{\max}$ 删除（也就是标记为已使用）。
3. 将剩下还没有删除的 $a_i$ 直接加入到答案中。

此时，我们不难看出，该方法的时间复杂度为 $O(n\lg a)$，可以通过此题。

## 代码实现：
```cpp
#include <bits/stdc++.h>
#define dbg(x) cerr<<#x<<": "<<x<<endl;
#define int long long
#define MAX_SIZE (int)2e5
using namespace std;

signed main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    double c1 = clock();
#endif
    //============================================
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        int a[MAX_SIZE] = {};

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        sort(a + 1, a + 1 + n, [](int a, int b) {
            return a > b;
        });
        vector <int> ans;
        unsigned long long now = a[1];
        ans.push_back(a[1]);
        a[1] = -1;

        for (int i = 30; i >= 1; i--) {
            unsigned long long maxnow = now;
            int nowpos = 1;

            for (int j = 2; j <= n; j++) {
                if (maxnow < (now | a[j]) && a[j] != -1) {
                    nowpos = j;
                    maxnow = now | a[j];
                }
            }

            if (a[nowpos] != -1) {
                now = maxnow;
                ans.push_back(a[nowpos]);
                a[nowpos] = -1;
            }
        }

        for (int i = 2; i <= n; i++)
            if (a[i] != -1)
                ans.push_back(a[i]);

        for (auto v : ans)
            cout << v << ' ';

        cout << endl;
    }

    //============================================
#ifdef LOCAL
    double c2 = clock();
    cerr << "Used Time: " << c2 - c1 << "ms" << endl;

    if (c2 - c1 > 1000)
        cerr << "Warning!! Time Limit Exceeded!!" << endl;

    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：4)

# Orray

## 题面

给定一个数列 $a$，要求对 $a$ 重排，使得重排后数组 $b$ 字典序最大。

这里 $b_i = a_1 \operatorname{or} a_2 \operatorname{or} \dots \operatorname{or} a_i$，其中 $\operatorname{or}$ 表示二进制按位或操作。

$t$ 组数据，保证 $1 \leq t \leq 100$，$1 \leq \sum n \leq 2 \times 10^5$，$0 \leq a_i \leq 10^9$。

## 思路

我们考虑 $\operatorname{or}$ 操作的特殊性质。一个位置无论原来是 $0$ 还是 $1$，只要 $\operatorname{or}$ 上一个 $1$，那么它就是 $1$ 了。我们知道 $a_i$ 变成二进制数最多有 $32$ 位。

**结论**

我们又知道，把 $a$ 中所有数字 $\operatorname{or}$ 起来就是 $b_i$ 的最大值了。但事实上，我们只需要对最多 $32$ 个数字进行 $\operatorname{or}$ 操作就可以得到这个最大值。最劣的情况就是我们需要 $32$ 个数字，即每个数字对应最大值上的一个位置的 $1$ 而其他位置都是 $0$。或者说我们在二进制下把最大值从前往后遍历，如果发现第 $i$ 位为 $1$，那么就选择一个第 $i$ 位为 $1$ 的 $a$ 值。然后我们最多只需要对每一位找一个数字，即一共找 $32$ 个数字即可。

我们再看到 $b$ 数组。我们可以知道 $b$ 数组有一个分界点 $k$。在 $[1,k]$ 中 $b_i$ 单调不降，$[k+1,n]$ 中每一个 $b_i$ 都相同。结合上面的我们可以知道 $k≤32$。

**枚举**

所以我们可以通过枚举来确定前 $32$ 个 $a_i$ 的值。每次我们选择一个 $a_i$ 使得 $b_{i-1}\operatorname{or}a_i>b_{i-1}$ 并且尽可能让 $b_{i-1}\operatorname{or}a_i$ 最大，这样就能保证字典序最大。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=2e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,p,T,a[N],ans,vis[N];
queue<int > q;

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int sum=0;
	for(int i=1;i<=max(32ll,n);i++){
		int mxid=0;
		for(int j=1;j<=n;j++){
			if(vis[j])continue;
			if((sum|a[j])>(sum|a[mxid]))mxid=j;
		}
		if(!mxid)break;
		vis[mxid]=i;
		sum|=a[mxid];
		q.push(mxid);
	}
	while(q.size()){
		cout<<a[q.front()]<<' ';
		q.pop();
	}
	
	for(int i=1;i<=n;i++){
		if(!vis[i])cout<<a[i]<<' ';
	}
	cout<<endl;
	
	for(int i=1;i<=n;i++)vis[i]=0;
}
signed main(){
	cin>>T;
	while(T--)solve();
	return 0;
}

```




---

## 作者：Allanljx (赞：1)

## 思路
考虑或的性质：$a|b>a$ 当且仅当 $b$ 的某一位是 $1$ 且 $a$ 的这一位是 $0$，因此最多 $\log_2(\max\limits_{1\leq i\leq n} a_i)$ 次就会使前缀或和达到最大值。所以考虑枚举前 $31$ 个数，后面的数就可以随便放了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int a[200005];
int bk[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int now=0;
		for(int i=min(31ll,n);i>=1;i--)
		{
			int maxn=0,xb;
			for(int j=1;j<=n;j++)
			{
				if((now|a[j])>maxn&&!bk[j])
				{
					maxn=now|a[j];
					xb=j;
				}
			}
			now|=maxn,bk[xb]=1;
			cout<<a[xb]<<' ';
		}
		for(int i=1;i<=n;i++)
		{
			if(!bk[i]) cout<<a[i]<<' ';
		}
		cout<<endl;
		for(int i=1;i<=n;i++) bk[i]=0;
	}
}
```

---

## 作者：一扶苏一 (赞：1)

## CF1742G Orray

### Description

给定一个数列 $a$，要求对 $a$ 重排，使得重排后 $a$ 的前缀或和数组 $b$ 字典序最大。

这里前缀或和的定义是：$b_i = a_1 \operatorname{or} a_2 \operatorname{or} \dots \operatorname{or} a_i$，其中 $\operatorname{or}$ 表示二进制按位异或操作。

$t$ 组数据，保证 $1 \leq t \leq 100$，$1 \leq \sum n \leq 2 \times 10^5$，$0 \leq a_i \leq 10^9$。

### Analysis

首先考虑暴力怎么做：

为了保证字典序最大，$b_1$ 一定是 $a$ 中最大的数，然后依次确定 $b_2, b_3, \dots b_n$。想要确定 $b_i$，只需要枚举还没有选择的 $a_j$，使得 $b_i = b_{i - 1} \operatorname{or} a_j$ 最大 即可。

考虑一个显然的结论：一定存在一个 $j$，使得 $b_1 < b_2 < b_3 < \dots < b_j = b_{j + 1} = b_{j + 2} = \dots = b_n$。这就是说，$b$ 数列的前半部分一定互不相同，后半部分一定相同，证明留做习题。

考虑如果 $b_i > b_{i - 1}$，那么 $b_i$ 的二进制一定比 $b_{i - 1}$ 多至少一个 $1$（因为 $b_i$ 是由 $b_{i - 1}$ 或另一个数得到，$b_{i - 1}$ 在二进制下 $1$ 的位置在 $b_i$ 中一定也是 $1$）。而 $b_i$ 二进制只有 $\lceil\log_2 a\rceil = 30$ 位，所以 $b_i > b_{i - 1}$ 的位置最多只有 $30$ 个，结合上一段中的结论，这样的位置只会出现在 $b$ 的前 $30$ 位。

所以只需要通过第一段中的暴力方法确定 $b$ 中前三十位的位置，剩余位置均与 $b_{30}$ 相同。

考虑运算量：每组数据会进行 $\min(n, 30)$ 次枚举，每次枚举 $O(n)$，最坏情况下枚举了 $30 \Sigma n$ 次 $a_j$，可以接受。

### Code

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

typedef long long int ll;

const int maxn = 200005;

int a[maxn];
bool op[maxn];
std::vector<int> Ans;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T, n;
  for (std::cin >> T; T; --T) {
    Ans.clear();
    std::cin >> n;
    for (int i = 1; i <= n; ++i) op[i] = false;
    for (int i = 1; i <= n; ++i) {
      std::cin >> a[i];
    }
    int ans = 0;
    for (int i = 1, lim = std::min(n, 30); i <= lim; ++i) {
      int tans = ans, pos = 0;
      for (int i = 1; i <= n; ++i) if (op[i] == false) {
        if ((ans | a[i]) >= tans) {
          pos = i; tans = ans | a[i];
        }
      }
      ans = tans;
      op[pos] = true;
      Ans.push_back(pos);
    }
    for (int i = 1; i <= n; ++i) if (op[i] == false) Ans.push_back(i);
    for (auto &&u : Ans) {
      std::cout << a[u] << ' ';
    }
    std::cout << '\n';
  }
}
```

---

## 作者：野生林登万 (赞：1)

[阅读体验并不更优且没有LaTeX的个人博客](http://autoac.vus.tax/index.php/2022/10/20/cf1742g/)
## 思路
首先读题:题目要求使得操作后的数组的字典序最大，换而言之，**每次操作后的数字一定要最大**（根据字典序的定义可知），那么这相当于是一个“贪心”，因为答案的每次操作必定是当前状态的最优解。那么我们可以把重新排列 $ a $ 数组看做改变添加 $ a_i $ 的顺序，使得每次当前的 $ b_i = a_i~\mathsf{OR}~b_{i-1}~ $ 最大。

题目中让我们用"按位或"进行操作，那么咱就想到把每一个 $ a_i $ 二进制化！如  $ 7 = (111)_2 $  和 $ 11 = (1011)_2 $，然后我们就可以操作起来了。在添加第一个数的时候，每个数对答案的贡献都等于它本身（任意一个数对 $ 0 $ 按位或都等于它们自己），那么第一次一定是添加最大的数。那么第二次每个数的贡献是多少呢？

因为对答案的贡献是以“按位或”计算的，所以在位上“重复”的贡献是**无效**的。比如 $ (1011)_2 $ 已经添加进了答案，第一位( $ 2^0 $ )和第二位( $ 2^1 $ )都已经被占有了，此时再加入$ (111)_2 $，它的第一、二位（和为 $ 3 $）就无法产生贡献，但是因为第三位（ $ 2^2 $ ）还没有被占用，他依然可以带来贡献 $ 2^2 = 4 $ 的贡献。

所以，我们可以在每次添加答案后，计算当前答案添加进去对后续答案贡献的影响。添加 $ a_x $ 的影响对于每一个 $ a_i $ 是 $ a_i~\mathsf{AND}~a_x~ $，这意味着，在 $ a_i $ 和 $ a_x $ 相同的位上，再添加 $ a_i $ 已经无法添加贡献了。最后，如上文所说，我们就每次贪心地枚举每一个 $ a_i $，每次选取能造成贡献最大的那一个。另外不用担心重复选取的情况，因为它 $ a_x $ 的贡献已经减去 $ a_x~\mathsf{OR}~a_x~ $ 了，是不会有任何贡献的。

等等...在 $ n = 2 \times 10^5 $ 和 $ a_i = 10^9$ 的范围内它不会TLE吗？的确不会。因为我们是按位操作的，对于统计的答案 $ b_i $ 来说，$ 10^9 $ 最多只有 $ 2^{30} $ 的 $ 30 $ 位（ $ 2^{30} = 1073741824 $ ），所以顶多进行 $ 30 $ 次操作就可以手动跳出循环（因为此时每个数的贡献都为 $ 0 $ ）。剩下的数字无法造成任何贡献，我们直接顺序（或者按照您喜欢的方式）输出即可。（感谢指出错误：循环的上界与 $ n $ 无关，而是与 $ a_i $ 的最大值有关）

另外，在证明循环最多只持续 $ 30 $ 次后，直接按照题意以贪心的思路打模拟也是可以过的，在这里不多做讨论了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
struct lb{
	int v,orgv;
	bool used;
}l[200006];
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i = 1;i <= n;i++){
			cin>>l[i].v;
			l[i].orgv = l[i].v;
			l[i].used = 0;//多组输入记得清空used
		}
		for(int i = 1;i <= n;i++){
			int maxv = 0,maxpos = 0;
			for(int pos = 1;pos <= n;pos++){
				if(l[pos].v > maxv){
					maxv = l[pos].v;
					maxpos = pos;
				}
			}
			for(int pos = 1;pos <= n;pos++){
				l[pos].v -= (l[pos].v & maxv);
			}
			if(maxv == 0){
				break;
			}
			l[maxpos].used = 1;
			cout<<l[maxpos].orgv<<" ";
		}
		for(int i = 1;i <= n;i++){
			if(l[i].used == 0){
				cout<<l[i].orgv<<" ";
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：ZhaoV1 (赞：0)

# CF1742G Orray

### 题目解析

众所周知，按位或的运算法则是在二进制中，两个二进制数同一位不为 $0$ 则为 $1$，同为 $0$ 则为 $0$。（也可以理解为同一位有 $1$ 则为 $1$，无 $1$ 则为 $0$）

这道题目考的是构造。题目要使从 $a_{1}$ 到任意 $a_{i}$ 这个前缀所有数的按位或运算结果最大，所以先用贪心的思维，我们每次放入一个数后，这个前缀的按位或结果应当最大。那么我们的思路就是：每一次维护一个使得当前前缀按位或结果最大的一个值 $a_{index}$ 并输出，直到没有能使得前缀按位或结果增大的值的时候，就将剩余的数全部输出。

Code
------------

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int num;
int a[200005];
bool b[200005];//表示下标i是否被访问过 

void solve(){
	cin >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	sort(a+1,a+1+n,greater<int>());//由大到小 降序 

	int res = a[1];
	cout << a[1] << " ";
	b[1] = true;
	while(1){
		int index = 0;
		int temp = res;
		for(int i=1;i<=n;i++){
			if(!b[i] && (res|a[i]) > temp){//此处(res|a[i])切记要加括号！！ 
				temp = res|a[i];
				index = i;
			}
		}
		if(index){
			res = temp;
			b[index] = true;
			cout << a[index] << " ";
		}else break;
	}
	for(int i=1;i<=n;i++) if(!b[i]) cout << a[i] << " ";
	cout << '\n';
	for(int i=1;i<=n;i++) b[i] = false;//初始化 
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

做这道题之前，首先要知道一个性质：$a \operatorname{or} b \geq a$。那么，我们就能得出一个结论：经过一定顺序的排列，最多经过 $\lceil \log_2^{a_{\max}} \rceil$ 个数就能让前缀或的值达到最大值。

我们不妨令有一个位置 $i$，$b_1,b_2,\dots,b_{i - 1}$ 单调递增，而 $b_i = b_{i + 1} = \dots = b_n$。

那么，根据上面的结论，我们可知 $i$ 的最大值一定为 $\lceil \log_2^{a_{\max}} \rceil$。

因此，我们可以从 $1$ 到 $30$ 枚举（因为 $0 \leq a_i \leq 10^9$，所以，$\lceil \log_2^{a_{\max}} \rceil = 30$），每一次选出能使或值变得最大的一个数排在重拍后的 $a$ 数组的前面（排在上一次选出的数的后面）。

但是，我们选的时候有可能有剩下的数，那该怎么办呢？由于，我们参考的是重拍后的 $a$ 的前缀或和。既然这时的或和已经到了最大值，根据或的性质，后面无论怎么加数改它都不会变了。

其实，我们可以直接选出第一位的数，显而易见的是，第一位一定是为：$a_{\max}$。因为，$0 \operatorname{or} a_{\max}$ 是最大的。

我们来分析一下时间复杂度为：$\Theta(30NT)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10;
int T,n,idx,res;
int arr[N],ans[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int cmp(int a,int b){
	return a > b;
}

int main(){
	T = read();
	while (T--){
		idx = res = 0;
		n = read();
		for (re int i = 1;i <= n;i++) arr[i] = read();
		sort(arr + 1,arr + 1 + n,cmp);//排序便于找最大值 
		ans[++idx] = res = arr[1];//直接确定第一位 
		arr[1] = -1;//把取过的数标记为 -1 
		for (re int i = 1;i <= 31;i++){
			int Max = res;
			int id = -1;
			for (re int j = 1;j <= n;j++){//暴力枚举 
				if (~arr[j]){//如果取过了便不能再取了 
					if (Max < (res | arr[j])){//判断新的值是否能超过之前的最大值 
						Max = res | arr[j];//是，更新 
						id = j;//更新位置 
					}
				}
			}
			if (~id){//如果有数被取出过 
				res = Max;//更新当前的或值 
				ans[++idx] = arr[id];//添加到答案数组中 
				arr[id] = -1;//记得标记 
			}
			else break;//直接提前结束 
		}
		for (re int i = 1;i <= idx;i++) printf("%d ",ans[i]);//先输出被取出过的 
		for (re int i = 1;i <= n;i++){
			if (~arr[i]) printf("%d ",arr[i]);//把没选出过的输出出来 
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16829092.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1742G)
## 思路
大抵算是一道位运算入门题？

首先为了使 $b_i$ 的字典序最大，我们注意到 $b_1=a_1$，所以 $a_1$ 必然是序列中最大的那个数。

接下来考虑贪心，设当前已经填了 $k$ 个数，此时的或和为 $a$，则我们从大往小扫，若 $maxx$ 的第 $i$ 位为 $0$，则接下来我们最好凑出 $1$ 来，因为 $2^i>\sum_{j=1}^{i-1} 2^j$，如果实在凑不出来则 $\verb!skip!$，如此贪心即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=2e5+10;
int a[N],b[N],c[N],n,vis[N],k;
vector<int>q[50];
inline void chk(int &maxx,int id){
    int mxp=0,maxn=maxx;
    for (auto i:q[id]){
        if (vis[i]) continue;
        if ((a[i]|maxx)>maxn) maxn=(a[i]|maxx),mxp=i;
    }
    if (!mxp) return;
    c[++k]=a[mxp];vis[mxp]=1;
    maxx|=a[mxp];
    return;
}
inline void chk(int x){for (int i=30;~i;--i) if (a[x]&(1<<i)) q[i].push_back(x);}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while (t--){
        int maxx=0,mxp;cin>>n;
        for (int i=30;~i;--i) q[i].clear();k=0;
        for (int i=1;i<=n;++i) vis[i]=0;
        for (int i=1;i<=n;++i){
            cin>>a[i],chk(i);
            if (a[i]>maxx) maxx=a[i],mxp=i;
        }
        vis[mxp]=1;c[++k]=maxx;
        for (int i=30;~i;--i)
            if (!(maxx&(1<<i)) && q[i].size()) chk(maxx,i);
        for (int i=1;i<=k;++i) cout<<c[i]<<' ';
        for (int i=1;i<=n;++i) if (!vis[i]) cout<<a[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
```


---

## 作者：xyzqwq (赞：0)

其实这是一个诈骗题（）


**题意分析**

考虑或的性质，两个数相或，同位若全 0 为 0，否则为 1，所以充分多个数相或，最终会把每一位都变成 1。

而当或和全为 1 后，再怎么或，或和都不会再变了。

这样的性质就提醒了我们，只要不断地或，在或上很少的数字（最差情况下不超过 30）后，或和就不会再变。

于是很容易想出思路：每次找出与当前和或值最大的数，直到或和为所有数的或和。

**核心代码**

```cpp
map<int,int>mp;
void work(){
	mp.clear();
	cin>>n;
	int sum=0,maxx=0,mi=1;
	for(int i=1;i<=n;i++){
		cin>>a[i],sum=sum|a[i],maxx=max(maxx,a[i]);
		if(maxx==a[i]) mi=i;
	}
	int x=maxx;
	mp[mi]=1;
	cout<<maxx<<" ";
	while(x!=sum){
		maxx=0,mi=1;
		for(int i=1;i<=n;i++){
			if(((x|a[i])>maxx)&&!mp[i]) maxx=x|a[i],mi=i;
		}
		mp[mi]=1;
		cout<<a[mi]<<" ";
		x=maxx;
	}
	for(int i=1;i<=n;i++){
		if(!mp[i]) cout<<a[i]<<" ";
	}	
	cout<<endl;
}
```

---

