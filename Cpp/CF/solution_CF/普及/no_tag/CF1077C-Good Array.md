# Good Array

## 题目描述

一个序列是好的当且仅当有一个数是其它所有数的和，比如$a=[1,3,3,7]$中$7=1+3+3$，所以这个序列是好的。

给你长度为$n$的序列$a$，你的任务是输出所有的$j$使得去掉$a_j$后的序列是好的。

举例，$a=[8,3,5,2]$，答案是$1$和$4$

- 如果你去掉$a_1$，剩下$[3,5,2]$，是好的
- 如果你去掉$a_4$，剩下$[8,3,5]$，是好的

你需要**独立地**检查所有项。比方说你去掉这个数，然后检查剩下的序列是否是好的，然后再放回去。

## 样例 #1

### 输入

```
5
2 5 1 2 2
```

### 输出

```
3
4 1 5```

## 样例 #2

### 输入

```
4
8 3 5 2
```

### 输出

```
2
1 4 
```

## 样例 #3

### 输入

```
5
2 1 2 4 3
```

### 输出

```
0

```

# 题解

## 作者：Yaha (赞：4)

### map

我们取掉$i$，剩下的序列为好的，等价于存在一个$j$使得：

$S_n-a_i-a_j=a_j$

整理得：$a_j=\frac {S_n-a_i}{2}$

所以只要剩下的序列中存在值为$\frac {S_n-a_i}{2}$的数，取掉$i$后就是一个好序列了

题目太善良，导致用普通数组会炸空间，所以我们用map来存序列中是否存在某个数。

```cpp
#include<bits/stdc++.h>
#define in long long
using namespace std;
const int amou=2e6+90;
in a[amou],s;
map<in,int> M;
vector<int> V;
int n;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		s+=a[i];
		M[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if((s-a[i])%2) continue;//排除不能整除的情况
		M[a[i]]--;//取掉i
		if(M[(s-a[i])/2]>0) V.push_back(i);
		M[a[i]]++;//放回i
	}
	printf("%d\n",V.size());
	for(int i=0;i<V.size();i++) printf("%d ",V[i]);
	return 0;
}
```


---

## 作者：Dilute (赞：3)

## [在本人博客食用更佳](http://dilute.coding.me/2018/11/17/Solutions/Solution-CF1077C)

显然，我们可以发现一个序列是“好的”当且仅当这个序列中的最大值等于这个序列中的其他数之和相加，所以我们只需要保证序列单调递减，同时维护一下这个序列里面元素之和我们就可以$O(1)$判断一个序列是不是“好的”序列（$a_1 = Sum - a_1$）

由于题目要求求出去掉哪些元素之后，这个序列会变为一个“好的”序列，所以我们只需要把原序列排序之后再按照刚刚说过的办法$O(1)$判断，只需要吧把原序列之中的$Sum$减去我们需要去掉的元素即可

还有一点需要注意，我们需要特判去掉第一个的情况，这样删去后最大值就是原先的次大数，即$a_2$

上代码QwQ

```cpp
// Sooke bless me.
// LJC00118 bless me.
#include<bits/stdc++.h>

#define INF 2147483647
#define ll long long

int Inp(){
	char c = getchar();
	int Neg = 1;
	while(c < '0' || c > '9'){
		if(c == '-')
			Neg = -1;
		c = getchar();
	}
	int Sum = 0;
	while(c >= '0' && c <= '9'){
		Sum = ((Sum << 3) + (Sum << 1)) + c - '0';
		c = getchar();
	}
	return Neg * Sum;
}

struct Node{
	ll x;
	int k;
}s[200010];

bool Cmp(Node a, Node b){
	return a.x > b.x;
}

int Ans[200010];

int main(){
	int n = Inp();
	ll Sum = 0;
	for(int i = 1; i <= n; i++){
		s[i].x = Inp();
		Sum += s[i].x;
		s[i].k = i;
	}
	std::sort(s + 1, s + n + 1, Cmp);
	int Cnt = 0;
	if(Sum - s[1].x - s[2].x == s[2].x) // 特判去掉1的情况
		Ans[++Cnt] = s[1].k;
	for(int i = 2; i <= n; i++){
		if(Sum - s[1].x - s[i].x == s[1].x)
			Ans[++Cnt] = s[i].k;
	}
	printf("%d\n", Cnt);
	for(int i = 1; i <= Cnt; i++)
		printf("%d ", Ans[i]);
}

```

---

## 作者：vocaloid (赞：2)

枚举。枚举删除每个数是否可行，先将数组排序，可以发现如果删除的数不是最大的数，那么和只可能为最大的数，所以判断总和 $sum$ 在减去最大的数和当前枚举的数后是否等于最大的数，等于则记录答案。

最后额外判断一遍删去最大的数的情况，即 $sum$ 在减去最大数和次大数的情况下是否与次大数相同即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct Node
{
	int val,id;
	friend bool operator < (const Node &x,const Node &y)
	{
		return x.val<y.val;
	}
}a[200005];
int n,ans[200005],tot;
ll sum;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].val);
		sum+=a[i].val;
		a[i].id=i;
	}
	sort(a+1,a+n+1);
	sum-=a[n].val;
	for(int i=1;i<n;i++) if(sum-a[i].val==a[n].val) ans[++tot]=a[i].id;
	if(sum-a[n-1].val==a[n-1].val) ans[++tot]=a[n].id;
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Luo_gu_ykc (赞：0)

## 题目大意

给定一个长度为 $n$ 的序列 $a$，要求输出 $j$，使得去掉 $a_j$ 后序列中的一个数是其他数之和。

## 思路

去掉 $a_j$ 后序列中的一个数是其他数之和，这个数是其他数之和，所以说这个数应该是去掉 $a_j$ 后序列里最大的才有可能是其他数之和，那么暴力做法，枚举 $j$ 的每一种可能，再看是否满足条件即可。

- 判断是否满足条件

求和，如果去掉 $a_j$ 和当前最大的数后的值等于当前最大的数，就满足条件。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long // 不开 long long 见祖宗
const int N = 2e5 + 5;
int n, ans[N], tmp, sum;
struct node{
	int x, cnt;
	bool operator < (const node & i) const { // 重载运算符排序
		return x < i.x; 
	}
}a[N];
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i].x;
		a[i].cnt = i;
		sum += a[i].x; // 总和
	}
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; i++){
		if(i != n){ // i == n 时需要特判，因为a[n]是最大的，去掉后，最大的数应该是a[n - 1]
			if(a[n].x == sum - a[n].x - a[i].x){ // 满足条件
				ans[++tmp] = a[i].cnt;
			} 
		} else {
			if(a[n - 1].x == sum - a[n].x - a[n - 1].x){ 
				ans[++tmp] = a[n].cnt;
			}
		}
	}
	cout << tmp << "\n";
	for(int i = 1; i <= tmp; i++){
		cout << ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：zbk233 (赞：0)

## 解题思路

思维题，这题事实上只有黄题难度，还是挺水的。

因为 $a$ 数组去掉 $a_i$ 后剩下的数组是一个好的数组，所以剩下的那个好的数组的数字之和一定是 $sum-a_i$。

而由题意可得，一个好的数组中其中的一个元素必定是除这个元素以外的数字之和。

那么如果一个数组为好的数组，其中必定有一个元素为 $\frac{sum-a_i}{2}$，而除了这个元素以外的数字之和也为 $\frac{sum-a_i}{2}$。

判断删去 $a_i$ 后的数组是不是好的就可以简化为判断剩下的数组内是否有 $a_j=\frac{sum-a_i}{2}(i\neq j)$。

而对于这个过程，因为 $1\le a_i\le 10^6$，范围不大，所以可以使用桶，可以用 $O(1)$ 的时间复杂度判断数组内是否有一个数。

## 参考代码

```cpp
#include<iostream>
using namespace std;
int a[200005];
int t[1000005];
int b[200005];
long long n,sum,q,len;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		t[a[i]]++;
		sum+=a[i];
	}
	for(int i=1;i<=n;i++){
		q=sum-a[i];
		if(q&1||q>=2000010) continue;
		q>>=1;
		if((a[i]==q&&t[q]>1)||(a[i]!=q&&t[q])) b[++len]=i;
	}
	cout<<len<<'\n';
	for(int i=1;i<=len;i++){
		cout<<b[i]<<' ';
	}
	return 0;
}
```


---

## 作者：Z_M__ (赞：0)

由于一个序列是好的，当且仅当有一个数是其它所有数的和，所以这个数必定是当前序列中最大的数。

所以只要模拟题意，将每个数从序列中去掉，设剩下序列中最大的数为$rem$，$tot$为剩下序列中除$rem$的和，若$rem=tot$时将这个数的下标记录到答案

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10;
int n, sum, cnt, ans[MAXN];
struct node {
	int mark, val;
	bool operator < (const node& x) const
	{
		return val < x.val;
	}
} a[MAXN];
signed main ()
{
	ios :: sync_with_stdio (0), cin.tie (0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i].val, a[i].mark = i;
	sort (a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		sum += a[i].val;
	for (int i = 1; i <= n; i++)
	{
		int top, rem;
		if (i == n) top = n - 1;
		else top = n;
        rem = a[top].val;
		int tot = sum - a[i].val - a[top].val;
		if (tot == rem)
			ans[++cnt] = a[i].mark;
	}
	cout << cnt << endl;
	for (int i = 1; i <= cnt; i++)
		cout << ans[i] << ' ';
	return 0;
}

```

---

## 作者：JohnVictor (赞：0)

没人写 $O(n+max a_i)$ 的做法啊qwq。

注意到这题的数据范围，$a_i \le 10^6$，所以可以开一个桶记录每个数字出现的次数。

之后开始判断：记录一个和 `sum`，枚举 $i$，判断 `sum-a[i]` 是否能拆成两半，一半只有一个数，且两半的和相等。

那么，就一定要满足，`sum` 的一半在 $a_i$ 的最大值范围内，并且 `sum` 是偶数。然后将 `sum` 除以 $2$，判断桶里面是否有这个数。注意需要特判：桶里面可能有 `sum/2` 但是那个数恰好是 `a[i]`，这时候需要那个数的个数不小于 $2$ 才行。

这里当然可以用 `map`，不过稍微有点大材小用，还多了一个 `log`。（CF赛制千万别用 `unordered_map`，会挂）

上代码，蛮短的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum[1000010],a[200010],b[200010],ans;
long long tot;
int main(){
	std::ios::sync_with_stdio(false);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],++sum[a[i]],tot+=a[i];
	for(int i=1;i<=n;i++){
		long long curr=tot-a[i];
		if((curr<=2000010)&&(curr%2==0)){
        //这里一定要是最大值的两倍，这样才能除以2之后在范围内，我就这样WA了一次
        //map的做法就是这里直接装到map里面，这样就不用判断大小了；不判断大小直接访问肯定会RE的
			curr>>=1;
			if(curr!=a[i]&&sum[curr]>=1)b[++ans]=i;
			else if (sum[curr]>=2)b[++ans]=i;
            //这里就是前面提到的特判，如果被用过的话这个数要有两个
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)cout<<b[i]<<" ";
	return 0;
}
```

~~CF恶评题好多啊，改黄吧。~~

---

## 作者：YuanZhizheng (赞：0)

别看这题是提高+的难度就怕了。

其实就是一个简简单单的想法题。

我们可以这样理解题目，有一个序列，每次操作我们删去其中一个元素，然后得到一个新的序列。

这个新序列的元素，我们可以分为一个元素x和其他元素，如果其他元素的和恰好等于元素x的值，那么这个新序列就是完美序列。

之后恢复成删除前的原序列。

题目需要我们记录下有多少次操作可以得到完美序列，并且记录下删除元素的下标。

**思路**：

1.这道题的重点是求和。求和得到的值才是需要我们记录的。所以我们可以先记录原序列的元素总和sum。

2.接着我们遍历序列，用sum-第i个元素的值得到的就是新序列的元素总和了。

3.新序列的特点是：如果其他元素的和恰好等于元素x的值，那么这个新序列就是完美序列。所以，新序列的和必然是元素x的两倍。

简单来说，如果这个新序列是一个完美序列，那么新序列元素和的一半sum/2，必然是新序列中的某个元素。

没错，至此判断条件已经得到了，所以你也会写了吧？

**特别注意**：这题的sum/2最高可以达到10^11的数量级，所以我们用map或者对sum/2进行特判。

好了，直接上代码。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[200005];
map<ll,ll>mp;
vector<int>ve;
int main()
{
    int i,j,n;
    cin>>n;
    ll summ=0;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        mp[a[i]]++;//记录元素x
        summ+=a[i];//求和
    }
    for(i=1;i<=n;i++)
    {
      ll sum=summ-a[i];
      /*
      也可以在这里写：
      if(sum/2>1000000)continue;
      这样子就可以不用map而用普通数组了。
      如果不特判就用普通数组的话，在下面是会有数组越界的！
      */
      mp[a[i]]--;
      if(sum%2==0&&mp[sum/2]>0)//新序列元素总和必然是x的两倍
            ve.push_back(i);
      mp[a[i]]++;
    }
    n=ve.size();
    cout<<n<<'\n';
    for(i=0;i<n;i++)
        printf("%d ",ve[i]);
    return 0;
}
```

---

## 作者：little_sun (赞：0)

# 题解 CF1077C 【Good Array】
* 个人觉得这题比B还水
* 先排下序，扫一遍$1-n$
* 对于每个数$i$，如果$i \neq n$，则当$\sum_{j=1}^na[j]-a[i]=2*a[n]$时满足条件
* 不然要是$i = n$的话，当$(\sum_{j=1}^na[j])-a[n]=2*a[n-1]$时满足条件
* 判断一下就好了

```cpp
# include <bits/stdc++.h>

# define ll long long

struct p
{
    int id;
    ll x;
};

p a[200001];

int cmp(p x, p y){return x.x < y.x;}

std::vector<int> vec;

int main()
{
    int n;
    ll sum = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i].x), a[i].id = i, sum += a[i].x;
    std::sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; i++)
    {
        if(i != n)//情况1
        {
            if(sum - a[n].x - a[i].x == a[n].x)
                vec.push_back(a[i].id);
        }
        else //情况2
        {
            if (sum - a[n - 1].x - a[i].x == a[n - 1].x)
                vec.push_back(a[i].id);
        }
    }
    if(vec.size())
    {
        printf("%d\n", vec.size());
        for(int i = 0; i < vec.size(); i++)
            printf("%d ", vec[i]);
    }
    else    
        printf("0");
    return 0;
}
```


---

