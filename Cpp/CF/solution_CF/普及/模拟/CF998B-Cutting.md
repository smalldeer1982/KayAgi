# Cutting

## 题目描述

有一个整数序列，其偶数和奇数的数量相同。给定有限的预算，您需要尽可能多地进行切割，使每个结果段具有相同数量的奇数和偶数。

“切割”操作将一个序列分成 $2$ 个连续的段。您可以将每次“切割”看作是序列中两个相邻元素之间的中断。所以在切割之后每个元素恰好属于一个片段。

举个例子，$[4,1,2,3,4,5,4,4,5,5]\to$ 两次“切割”操作 $\to[4,1|2,3,4,5|4,4,5,5]$。在每个切割后的段上，偶数元素的个数应该等于奇数元素的个数。

在元素 $x$ 和元素 $y$ 之间进行一次“切割”操作的价值为 $|x-y|$ 元。请问，在 $B$ 元内，最多可以切割几次？

## 样例 #1

### 输入

```
6 4
1 2 5 10 15 20
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 10
1 3 2 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 100
1 2 3 4 5 6
```

### 输出

```
2
```

# 题解

## 作者：YuanZhizheng (赞：1)

   这题啊，我看到另一篇题解是DP+优先队列之类的，蒟蒻对自底向上的DP实在一窍不通，一开始没有想到，就拿了自顶向下的记忆化搜索过的。

敲DFS大家一定都会吧？

在读入的时候记录一下奇数个数，然后，我们就可以根据在序列中位置不同、到当前位置奇偶数不同、剩余比特币数量不同、切割的次数（dao）不同，来进行DFS。

```
#include<bits/stdc++.h>
using namespace std;
int a[105];
int n,m;
int maxx=0;
void dfs(int pos,int odd,int even,int money,int dao,int sumodd,int sumeven)
{
    if(odd>sumodd||even>sumeven||n-pos+dao<=maxx||pos>=n-1||money<=0||sumodd!=sumeven)//一些剪枝
        return;
    if(pos<n-1)//只用搜到n-1，因为总不能把最后一个数字给切了吧？
    {
        odd+=(a[pos]&1);
        even+=(!(a[pos]&1));
    }
    if(odd==even&&sumodd-odd==sumeven-even&&odd>0&&even>0)//判断是否切割前后的序列奇偶都相同
    {
        if(money>=abs(a[pos]-a[pos+1])&&pos<n-1)
        {
            maxx=max(maxx,dao+1);//如果都符合，就切一刀，然后继续dfs
            dfs(pos+1,0,0,money-abs(a[pos]-a[pos+1]),dao+1,sumodd-odd,sumeven-even);
        }
    }
    dfs(pos+1,odd,even,money,dao,sumodd,sumeven);//也可以选择不在这里切一刀，因为在这切未必是最优解
}
int main()
{
    int sumodd=0;//保存一下奇数数量，保存偶数也行
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
        sumodd+=(a[i]&1);
    }
    if(sumodd<<1==n)//必须让序列奇偶相等才有可能切割
        dfs(1,0,0,m,0,sumodd,n-sumodd);
    printf("%d",maxx);
    return 0;
}
```
当然，上面这是加了一点点剪枝的DFS，只是想让你看看DFS的大概流程，虽然有一点点剪枝，实际上就比最朴素的好一点而已，这一点优化是没用的，还是会TLE。

我在修改了无数次还是T之后，我就不打算进行小优化了，用**记忆化搜索**（不知道为什么一开始没想到）。

**普通DFS之所以复杂度高，是因为很多状态会被搜索非常多次，导致状态多的话，时间消耗非常大，如果让每种状态都只搜索一次，那么可以极大地提高效率。**

对于某一位置，在比特币剩余数量和奇偶数量不同的时候，会分别对应一种唯一状态，所以我们可以开一个记忆数组。
```
int dp[101][51][101][51];//位置，当前位置奇数数量，剩余比特币数量，序列中剩余总的奇数数量
```
偶数数量是不用记录的，因为要保证能切割，必须剩余奇偶数相等，所以我在DFS中加有一个判断语句就是专门判断奇偶数是否相等，这样也算帮我们省去一维。

最极端的状况，也不过是100 * 50 * 100 * 50种情况，全部遍历一遍不过是2.5*10^7种情况，2s的时间绰绰有余。

可能你还会想问一下，为什么序列总的奇数数量那维不开到100？

因为序列最长就是100个数字，一旦总的奇数超过50，就一定不能切割。

下面上AC代码
```
#include<bits/stdc++.h>
using namespace std;
int a[105];
int n,m;
int dp[101][51][101][51];
int dfs(int pos,int odd,int even,int money,int dao,int sumodd,int sumeven)
{
    if(dp[pos][odd][money][sumodd]!=-1)
        return dp[pos][odd][money][sumodd];
    if(odd>sumodd||even>sumeven||pos>=n-1||money<=0||sumodd!=sumeven||pos>=n-1)
        return dao;
    if(pos<n-1)
    {
        odd+=(a[pos]&1);
        even+=(!(a[pos]&1));
    }
    int p=dao,q=dao;
    if(odd==even&&sumodd-odd==sumeven-even&&odd>0&&even>0)
    {
        if(money>=abs(a[pos]-a[pos+1])&&pos<n-1)
        {
            p=dfs(pos+1,0,0,money-abs(a[pos]-a[pos+1]),dao+1,sumodd-odd,sumeven-even);
        }
    }
    q=dfs(pos+1,odd,even,money,dao,sumodd,sumeven);
    return dp[pos][odd][money][sumodd]=max(p,q);
}
int main()
{
    //freopen("ans.txt","r",stdin);
    memset(dp,-1,sizeof(dp));
    int sumodd=0;
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
        sumodd+=(a[i]&1);
    }
    int maxx=0;
    if(sumodd<<1==n)
        maxx=dfs(1,0,0,m,0,sumodd,sumodd);
    printf("%d",maxx);
    return 0;
}
```
这样，时间可以降到几十ms就完成。当然我也承认，这样牺牲了比较大的空间复杂度。

如果有更好的记忆化搜索优化，无论是时间还是空间，都欢迎你提出！

（2020.04.08第一次修改，将开头“对DP实在一窍不通，一开始没有想到，就拿了另外一种解法”改为“对自底向上的DP实在一窍不通，一开始没有想到，就拿了自顶向下的记忆化搜索”。）

---

## 作者：quanjun (赞：1)

#### 题目描述
有很多东西是可以被切割的，比如——树、纸张或者绳子。在这道题目里面你需要切割一个整数序列。  
现在告诉你一个整数序列，在这个整数序列里面有一些数，它们可能是奇数，也可能是偶数。  
给你一个固定的预算（因为切割是有成本的），你需要尽可能多地将这个整数序列切分成一系列连续子序列，  
使得每一个连续子序列中的 奇数元素的个数 和 偶数元素的个数 相同。  
比如，给你一个整数序列 [4,1,2,3,4,5,4,4,5,5] ，你可以将其切割两次变成   
[4,1 | 2,3,4,5 | 4,4,5,5] 。其中，[4,1] 、 [2,3,4,5] 以及 [4,4,5,5] 这三个连续子序列中包含的奇数个数等于偶数个数。  
如果你要将第 i 个元素和第 i+1 个元素之间切一刀，我们假设第 i 个元素对应的数值为 x ，第 j 个元素对应的数值为 y ，那么你需要消耗 |x-y| 个比特币。  
（|x-y| 表示 x-y 的差的绝对值）。  
而你的预算只有 B 个比特币，所以你需要计算一下在最多消耗 B 个比特币的情况下，你最多可以切几次。  
#### 输入格式
输入的第一行包含两个整数 n （2<=n<=100）和 B（1<=B<=100），分别表示整数序列中元素的个数和你最多可用的比特币的数量。  
输入的第二行包含 n 个整数，用于表示整数序列中的元素：a1,a2,……,an（1<=ai<=100）。   
#### 输出格式
输出一个整数，用于表示在最多消耗 B 个比特币的情况下，你最多可以切几刀，使得每一个切出来的连续子序列中包含相同的奇偶元素。  
#### 样例输入1
```
6 4
1 2 5 10 15 20
```
#### 样例输出1
```
1
```
#### 样例输入2
```
4 10
1 3 2 4
```
#### 样例输出2
```
0
```
#### 样例输入3
```
6 100
1 2 3 4 5 6
```
#### 样例输出3
```
2
```
#### 样例解释
对于样例1，我们可以在 2 和 5 之间切割一刀，消耗 3 个比特币；  
对于样例2，我们无法切割；  
对于样例3，我们可以在 2 和 3 之间 以及 4 和 5 之间切割一刀，消耗 1+1=2 个比特币。  

### 问题分析
这道题目涉及的算法是“DP”+“贪心”，可以用 dp+sort 或者 dp+heap 来做。  
首先我们假设 n 个元素的坐标从 1 到 n ，他们分别对应 a[1] 到 a[n] 。   
然后我们开一个输出 cc[] ，cc[i] 用于表示从 a[1] 到 a[i] 这 i 个数中奇数个数减去偶数个数之差。  
那么对于 1 到 n-1 范围内的 i ，如果 cc[i] == 0 ，那么它这个位置就是可以切割的，切割的成本是 abs(a[i+1]-a[i]) 。
#### dp+sort解法：  
我们将 1 到 n-1 范围内的所有满足 cc[i]==0 条件的 i 对应的 abs(a[i+1]-a[i]) 放入一个数组中，然后将这个数组从小到大排序，每次取出一个数计数器cnt++，同时B减去这个数，直到B不够用为止；
#### dp+heap（堆）解法：  
我们首先构造一个最小堆（可以用 priority_queue 模拟），然后将 1 到 n-1 范围内的所有满足 cc[i]==0 条件的 i 对应的 abs(a[i+1]-a[i]) 放入最小堆中1，然后每次从最小堆中取出堆顶元素，计数器cnt++，同时B减去这个数，直到B不够用为止。  

1、下面的代码演示了 dp+sort 的操作：  
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n, B, cnt, a[maxn], cc[maxn];
vector<int> vec;

int main() {
    cin >> n >> B;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        cc[i] = cc[i-1] + (a[i] % 2 ? 1 : -1);
    }
    for (int i = 1; i < n; i ++) if (!cc[i]) vec.push_back(abs(a[i+1]-a[i]));
    sort(vec.begin(), vec.end());
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); it ++) {
        if (*it > B) break;
        B -= *it;
        cnt ++;
    }
    cout << cnt << endl;
    return 0;
}
```

2、下面的代码演示了 dp+heap 的操作：
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n, B, cnt, a[maxn], cc[maxn];
priority_queue<int, vector<int>, greater<int> > que;

int main() {
    cin >> n >> B;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        cc[i] = cc[i-1] + (a[i] % 2 ? 1 : -1);
    }
    for (int i = 1; i < n; i ++) if (!cc[i]) que.push(abs(a[i+1]-a[i]));
    while (!que.empty()) {
        int u = que.top();
        que.pop();
        if (u > B) break;
        B -= u;
        cnt ++;
    }
    cout << cnt << endl;
    return 0;
}
```


---

## 作者：yaaaaaan (赞：0)

### 思路
因为奇数跟偶数的个数是固定的，所以每次切割都是互相独立的。所以可以预处理每次可以切割的序列。然后从小到大根据代价排序，依次切割，直到钱花完，输出次数。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,k,old,bb;
int a[100001];
int b[100001];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>bb;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++)
	{
		if(a[i]%2==0) old++;
		else old--;
		if(old==0) b[++k]=abs(a[i]-a[i+1]);
	}
	sort(b+1,b+k+1);
	for(int i=1;i<=k;i++)
	{
		bb-=b[i];
		if(bb<0)
		{
			cout<<i-1<<"\n";
			return 0;
		}
	}
	cout<<k<<"\n";
	return 0;
}
/*
a+b=a^b+a&b
 */
```

---

## 作者：enyyyyyyy (赞：0)

用模拟、贪心的思路来解。先对奇、偶数进行特判，在放入一个专门存绝对值的书组，进行 `sort`，在从 $0$ 开始枚举答案，如果小于 $b$，用 $b$ 减掉，如果减不了了，就输出。
```cpp

#include <bits/stdc++.h>
#define ll long long
#define lint __int128
using namespace std;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline void print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll b,j,k,n,s,a[1000005],c[1000005];
int main(){	
	n=read(),b=read();
	for(ll i=1;i<=n;i++) a[i]=read();
	for(ll i=1;i<n;i++){
		if(a[i]%2) k++;
		else k--;
		if(!k)
			c[j++]=abs(a[i]-a[i+1]);
	}
	sort(c,c+j);
	ll i=0;
	for(;i<j&&c[i]<=b;i++)
		b-=c[i];
	print(i);
	return 0;
}
```


---

## 作者：Dream__Sky (赞：0)

这道题可以用贪心的思路来解。

我们可以把所有可以切割的点先存下来，然后花费更少的先切割，直到用完所有的钱。

那我们如何保证这是对的呢？

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wq9r8pwx.png)

我们可以把大区间分成小区间来看，$1$ 号区间肯定满足条件（题目有说），那如果 $3$ 号区间满足条件，$2$ 号一定也满足，反之同理。再把 $2$ 号也可以分成小区间，如果 $4$ 号可以，$5$ 号就一定也可以。也就是说，无论怎么分割，只要当前的点是满足条件的，那么剩下的几个区间一定也满足。说明了切割的顺序对答案没有影响。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[100001],b[100001],cnt,daan;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	int sum1=0,sum2=0;
	for(int i=1;i<n;i++)//坑点，最后一个点不能分割
	{
		if(a[i]%2==1) sum1++;
		else sum2++;
		if(sum2==sum1) b[++cnt]=abs(a[i+1]-a[i]);//把所有可以的点的代价存下来
	 } 
	 
	 sort(b+1,b+1+cnt);//贪心
	 
	 for(int i=1;i<=cnt;i++)
	 {
	 	if(k>=b[i]) daan++,k-=b[i];
	 	else break;
	 }
	 cout<<daan;
	return 0;
}

```


---

## 作者：_frog (赞：0)

# CF998B Cutting 题解
## 题意简述
+ 有一长度为 $n$ 的整数序列 $a_1,a_2,\cdots,a_n$，满足序列中奇数和偶数的数量相同。
+ 定义第 $k$ 次“切割”为在已有的 $k$ 个序列中选择一个，设此序列为 $a_l,a_{l+1},\cdots,a_r$，然后选择一个元素 $a_i(l\le i<r)$，在 $a_i$ 与 $a_{i+1}$ 间进行分割，形成两个新序列 $a_l,a_{l+1},\cdots,a_i$ 与 $a_{i+1},a_{i+2},\cdots,a_r$。分割代价为 $\left\vert a_{i+1}-a_i\right\vert$。
+ 一次“切割”可以进行当且仅当分割后两个新序列都满足以下性质：新序列中奇、偶数数量相同。
+ 在保证分割代价总和不超过预算 $B$ 的条件下，“切割”次数要尽可能多。求最多的“切割”次数。
+ $2\le n\le 100$，$1\le B\le 100$，$1\le a_i\le 100$。


## 题目分析
对一个奇、偶数数量相同的序列进行“切割”，只要满足前一个新序列中奇、偶数数量相同，则后一个新序列中奇、偶数数量必然相同。

如果一个序列可被分为多段序列，且这些序列奇、偶数数量都相同，那么这个序列中奇、偶数数量必然相同。

而对于一个序列 $a_l,a_{l+1},\cdots,a_r$，只要满足 $a_1,a_2,\cdots,a_r$ 奇、偶数数量相同，且 $a_1,a_2,\cdots,a_{l-1}$ 奇、偶数数量也相同，那么 $a_l,a_{l+1},\cdots,a_r$ 奇、偶数数量必然相同。

所以**如果序列 $a_1,a_2,\cdots,a_i$ 奇、偶数数量相同，那么无论前面“切割”了几次，在 $a_i$ 与 $a_{i+1}$ 间总可以“切割”**。如图：（绿色竖线表示之前的“切割”，蓝色竖线表示现在的“切割”）

![](https://cdn.luogu.com.cn/upload/image_hosting/lcdorc8s.png)

得出结论：**“切割”顺序不重要**。

所以就可以预处理出所有可以“切割”的点，并计算每次“切割”的代价。

要保证“切割”次数要尽可能多，就得把“切割”代价从小到大排序，再从小到大进行“切割”。

流程：
1. 输入。（$O(n)$）
2. 预处理及排序。（$O(n+n\log n)=O(n\log n)$）
3. 模拟“切割”。（$O(n)$）
4. 输出。（$O(1)$）

时间复杂度：$O(n\log n)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
	ll nov = 1, dat = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			nov = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		dat = (dat << 3) + (dat << 1) + (c & 15);
		c = getchar();
	}
	return dat * nov;
}

void write(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x < 10) {
		putchar(x + '0');
	} else {
		write(x / 10);
		putchar(x % 10 + '0');
	}
}
ll a[110], now, ans, n, b;//now 表示目前奇数比偶数多多少个
vector<ll>cutting;//用 vector 保存“切割”代价

int main() {
	//1.输入
	n = read(), b = read();
	for (ll i = 1; i <= n; i++) {
		a[i] = read();
	}
	//2.预处理
	for (ll i = 1; i < n; i++) { //a[n] 后面无法“切割”
		if (a[i] % 2 == 1) { //a[i] 是奇数
			now++;
		} else { //a[i] 是偶数
			now--;
		}
		if (now == 0) { //奇数、偶数数量相等
			cutting.push_back(llabs(a[i + 1] - a[i]));//可以“切割”
		}
	}
	sort(cutting.begin(), cutting.end()); //根据“切割”代价从小到大排序
	//vector.end() 迭代器指向最后一个元素的下一位
	//3.模拟“切割”
	for (ll i = 0; i < cutting.size(); i++) {
		if (b >= cutting[i]) { //还可以进行“切割”
			b -= cutting[i];
			ans++;
		} else { //预算不足
			break;
		}
	}
	//4.输出
	write(ans);
	return 0;
}
```

---

