# Oh Sweet Beaverette

## 题目描述

有一个森林共有 $n$ 棵树，它们各自都有美丽值，要砍掉一些树，也可以不砍。  
要求：  
1. 剩余树的美丽值之和必须最大化；
2. 结果中第一棵和最后一棵树的美丽值必须相同；
3. 森林中必须至少剩下两棵树。

问：需要砍下哪些树才能让剩余树的美丽值之和最大化？

## 样例 #1

### 输入

```
5
1 2 3 1 2
```

### 输出

```
8 1
1 ```

## 样例 #2

### 输入

```
5
1 -2 3 1 -2
```

### 输出

```
5 2
2 5 ```

# 题解

## 作者：AC_love (赞：1)

贪心。

一个显而易见的贪心策略是：先砍掉所有美丽度为负数的树，然后在剩下的美丽度为正数的树种选取。

然而这个显然的贪心策略显然是错的，举个例子：

```
-2 100 1 5 1 -2
```

如果我们把两棵美丽度为 $-2$ 的树砍掉了，那么为了满足第二个条件，我们就必须砍掉美丽度为 $100$ 的树，这波丢了西瓜拣芝麻，实在不划算。

因此我们不能盲目乱砍滥伐，应该考虑怎么才能更优。

我们想到：美丽度为负数的树除非是作为两个端点，不然我们死都不可能会留着这玩意有碍市容，因此我们只要枚举端点，然后砍掉中间所有美丽度为负数的树即可。

我们想到，一段显然越长越好，也就是说针对每个点作为左端点，我们都希望枚举它最靠右的右端点在哪。

对于 Subtask 1，直接暴力枚举每个点作为左端点时的右端点在哪即可，复杂度 $O(n^2)$。

对于 Subtask 2，我们可以用一个 map 来存每个数对应的左端点和右端点的位置，然后用前缀和快速处理这一段的最大子序列和，复杂度 $O(n \log n)$。

实际上不用 map 而用 vector 理论上可以做到 $O(n)$，但是比较麻烦，其实没有必要。

代码实现如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 3e4;
const int inf = 1145141919810ll;

int n, ans = -inf;
int a[N];
int pre[N];
int le, ri;

map <int, int> lef;
map <int, int> rig;

signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> a[i];
		pre[i] = pre[i - 1] + max(a[i], 0ll);
		if(lef[a[i]] == 0)
			lef[a[i]] = i;
		rig[a[i]] = i;
	}
	for(int i = 1; i <= n; i = i + 1)
	{
		int l = lef[a[i]];
		int r = rig[a[i]];
		if(l == r)
			continue;
		if(a[i] >= 0)
		{
			if(pre[r] - pre[l - 1] > ans)
			{
				ans = pre[r] - pre[l - 1];
				le = l, ri = r;
			}
		}
		else
		{
			if(pre[r] - pre[l - 1] + 2ll * a[i] > ans)
			{
				ans = pre[r] - pre[l - 1] + 2ll * a[i];
				le = l, ri = r;
			}
		}
	}
	cout << ans << " ";
	queue <int> q;
	for(int i = 1; i <= le - 1; i = i + 1)
		q.push(i);
	for(int i = le + 1; i <= ri - 1; i = i + 1)
		if(a[i] < 0)
			q.push(i);
	for(int i = ri + 1; i <= n; i = i + 1)
		q.push(i);
	cout << q.size() << "\n";
	while(!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	return 0;
}
```

---

## 作者：zhuweiqi (赞：1)

### 方法一：暴力枚举

时间复杂度：$O(n^3)$

期望得分：$30$ 分

思路：枚举左端点和右端点（即砍完树之后的第一棵树和最后一棵树），如果它们的美丽值不相等则直接跳过，否则就把左端点和右端点的这两棵树以及这个**开**区间内所有美丽值大于零的树都选了，得到一个美丽值总和，如果这个数大于之前得到的最大的数，就更新最大值。输出部分则先找出能得到最大值的那种方案，然后砍倒的树的数量就是位于左端点之前的所有树和位于右端点之后的所有树以及这个**开**区间内所有美丽值小于或者等于零的树，最后依次输出它们即可。注意！题目保证至少有两棵树的美丽值相同，但没说解一定是正数，所以美丽值总和的最大值的初始值要赋值为一个**极小值**并且枚举的区间内的左右端点都必须选上，不能因为它是负数就不选了！另外，记得要开 $64$ 位有符号整型变量来存储这个最大值！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
int a[102]; 
int main(){
	int n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	long long ans=-1e18;
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]!=a[j]) continue;
			long long now=2*a[i];
			for(int k=i+1;k<j;k++) if(a[k]>0) now+=a[k];
			if(now>ans) ans=now; 
		}
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]!=a[j]) continue;
			long long now=2*a[i];
			for(int k=i+1;k<j;k++) if(a[k]>0) now+=a[k];
			if(now==ans){
				int cnt=i-1+n-j;
				for(int k=i+1;k<j;k++) if(a[k]<0) cnt++;
				printf("%lld %d\n",ans,cnt);
				for(int k=1;k<i;k++) printf("%d ",k);
				for(int k=i+1;k<j;k++) if(a[k]<0) printf("%d ",k);
				for(int k=j+1;k<=n;k++) printf("%d ",k);
				return 0;
			}
		}
	}
	return 0;
}
```

### 方法二：优化了一点点的枚举

时间复杂度：$O(n^2)$

期望得分：$30$ 分

我们可以用一个类似前缀和数组一样的东西来优化程序，使我们枚举的效率从三重循环优化到了两重循环，即用一个一维数组 $f$，用 $f_i$ 表示如果把所有在第 $1$ 棵树到第 $i$ 棵树之间的美丽值大于零的树都选了可以获得的美丽值总和是多少，当 $a_i\leq 0$ 时，$f_i=f_{i-1}$，反之 $f_i=f_{i-1}+a_i$，注意 $f$ 数组要开 long long。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
int a[102]; 
long long f[102];
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]<=0) f[i]=f[i-1];
		else f[i]=f[i-1]+a[i];
	}
	long long ans=-1e18;
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]!=a[j]) continue;
			long long now=2*a[i]+f[j-1]-f[i];
			if(now>ans) ans=now; 
		}
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]!=a[j]) continue;
			long long now=2*a[i]+f[j-1]-f[i];
			if(now==ans){
				int cnt=i-1+n-j;
				for(int k=i+1;k<j;k++) if(a[k]<0) cnt++;
				printf("%lld %d\n",ans,cnt);
				for(int k=1;k<i;k++) printf("%d ",k);
				for(int k=i+1;k<j;k++) if(a[k]<0) printf("%d ",k);
				for(int k=j+1;k<=n;k++) printf("%d ",k);
				return 0;
			}
		}
	}
	return 0;
}
```

### 方法三：优化了亿点点的枚举

时间复杂度：$O(n\log n)$

期望得分：$100$ 分

可以发现，我们想要求出最优解就必须要枚举，而我们在枚举的时候因为很多不必要的枚举就浪费了大量的时间，比如说：如果当 $a_i\not =a_j$ 或者当 $a_i=a_j$ 但是存在一个 $k$（$k<i$）并且 $a_k=a_i$ 或者存在一个 $l$（$j<l$）并且 $a_j=a_l$ 时，我们完全不需要枚举这些情况，因为这些情况要么无解，要么肯定不是最优解或者是最优解之一，将来一定会有**至少不比它劣的解**出现，因此，我们需要按树的美丽值的大小（即 $a_i$ 的值）对 $a$ 数组进行排序，并且当 $a_i$ 的值相等时肯定是树的位置越前面的树排在越前面的地方，在此过程中我们需要用结构体同时记录每棵树的美丽值和它原来的位置，然后用一重循环扫过去，找到一对 $i,j$，使得 $a_{i-1}\not = a_i$ 并且 $a_j \not = a_{j+1}$ 并且 $a_i=a_j$ 并且 $i\not =j$（因为题目中说最少留两棵树），它所能获得的美丽值总和最大的值就是 $a_i$ 与 $a_j$ 与把所有在第 $i+1$ 棵树到第 $j-1$ 棵树之间的美丽值大于零的树都选了所得到的美丽值的和的总和，最后，我们就可以得出最优解啦！输出也是同理。上最终代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
struct tree{
	int a,p;
}s[300002];
bool cmp(tree a,tree b){
	if(a.a!=b.a) return a.a<b.a;
	return a.p<b.p;
}
long long f[300002];
int st[300002];
int main(){
	int n=read(),fir=1;
	long long ans=-1e18;
	for(int i=1;i<=n;i++){
		st[i]=read();
		s[i].a=st[i];
		s[i].p=i;
		if(s[i].a<0) f[i]=f[i-1];
		else f[i]=f[i-1]+s[i].a;
	}
	s[n+1].a=1e9+7;
	sort(s+1,s+1+n,cmp);
	for(int i=2;i<=n+1;i++){
		if(s[i].a!=s[i-1].a){
			if(fir!=i-1){
				i--;
				long long now=s[fir].a*2+f[s[i].p-1]-f[s[fir].p];
				if(now>ans) ans=now;
				i++;
			}
			fir=i;
		}
	}
	fir=1;
	for(int i=2;i<=n+1;i++){
		if(s[i].a!=s[i-1].a){
			if(fir!=i-1){
				i--;
				long long now=s[fir].a*2+f[s[i].p-1]-f[s[fir].p];
				if(now==ans){
					int cnt=s[fir].p-1+n-s[i].p;
					for(int j=s[fir].p+1;j<s[i].p;j++) if(st[j]<0) cnt++;
					printf("%lld %d\n",ans,cnt);
					for(int j=1;j<s[fir].p;j++) printf("%d ",j);
					for(int j=s[fir].p+1;j<s[i].p;j++) if(st[j]<0) printf("%d ",j);
					for(int j=s[i].p+1;j<=n;j++) printf("%d ",j);
					return 0;
				}
				i++;
			}
			fir=i;
		}
	}
	return 0;
}
```

---

## 作者：raozf (赞：0)

## 思路：
先考虑暴力。

枚举首尾相同的树，对于每一对相同的树，计算：保留这两棵树及他们之间所有的、吸引力为正的树后，总吸引力是多少。


对于 $i$ 和 $j$ 之间的树，如果他们的吸引力为正，计入答案；否则，将他们加入砍伐列表。


同时，将 $i$ 之前和 $j$ 之后的所有树的编号加入砍伐列表。

更新最优解时，要把砍伐列表更新。

可以发现，时间复杂度为 $O(n ^ 2)$，会超时。

## 优化：

预处理，用 `map` 统计每种吸引力对应的所有树的位置，然后遍历每种吸引力，利用前缀和来快速计算区间和，从而将时间复杂度优化到 $O(n)$。

## Code:

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 3e5 + 3;

int n;

int a[kMaxN], s[kMaxN];

unordered_map <int, vector<int>> mp;

int cut[kMaxN], cnt = 0;

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + (a[i] > 0? a[i] : 0);
        mp[a[i]].push_back(i);
    }
    int maxn = -1e12;
    for (auto &i : mp) {
        vector<int>& ls = i.second;
        if (ls.size() < 2) continue;
        int first = ls[0];
        for (int j = 1; j < ls.size(); ++j) {
            int last = ls[j];
            int sum = a[first] + a[last] + s[last - 1] - s[first];
            if (sum > maxn) {
                maxn = sum;
//              memset (cut, 0, sizeof cut);
                cnt = 0; // 清空 
                for (int k = 1; k < first; ++k) cut[++cnt] = k;
                for (int k = first + 1; k < last; ++k) {
                    if (a[k] <= 0) cut[++cnt] = k;
                }
                for (int k = last + 1; k <= n; ++k) cut[++cnt] = k;
            }
        }
    }

    cout << maxn << " " << cnt << "\n";
    for (int i = 1; i <= cnt; i++) {
        cout << cut[i] << " ";
    }
    cout << "\n";
    return 0;
}
```

---

## 作者：qusia_MC (赞：0)

## 分析
$n$ 棵树，砍去一些，首尾美丽要一样，求这些数美丽和的最大值。

------------
以下我们设第 $i$ 棵树的美丽度为 $a_i$。
## 思路
不难想到：

- 贪心思路：很容易想到，就是把 $a_i$ 为负数的全都砍了。但是这样有几个反例：

   首先：
   
   ```-2 99999999 1 1 -2```

   这个数据按照贪心应该要把两个 $-2$ 砍了，但是这样就要被迫把 $a_i$ 为 $99999999$ 的神圣树砍了，这就不行了。

   再就是：
   
   ```-1 1 -1```
   
   砍了的话就不能有两颗一样的。

- $O(n^3)$ 思路：这个是能过得（我不知道这么简单为什么是黄）先 $O(n^2)$ 找两个相同的数，再 $O(n)$ 累加。这么简单就不打了，是个人就会。但是这个最多能得 30 分就算你牛。

- $O(n^2)$ 思路：提前 $O(1)$ 前缀和处理，再 $O(n^2)$ 找相同的数，再累加。这个前缀和思路有点思维含量（但不多），稍微打一下。这个大概能得 50 分左右把。
   ```
   int a[10010];//数组
   int zhui[10010];//前缀和
   for(int i=1;i<=n;i++)
   {
   cin>>a[i];
   if(a[i]<0)zhui[i]=zhui[i-1];//小于0则不累加，有损   市容。
   else zhui[i]=zhui[i-1]+a[i];//否则加上，市容rp++
   }
   ```

- $O(n \log n)$ 思路：拷贝数组，排序，前缀和 map 维护。这里不打了，其他题解都有。这个应该能对，具体请参考其他人的题解。

- $O(n)$ 思路：这也是今天的重点，可以省去排序。在输入的时候直接一个 map 直接统计就可以了。这样还要注意优化，因为 $1\sim n$ 的循环大概要打 $3\sim 4$ 次，可能在数据极限可能炸（第十九个测试点就是这样的）。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,pair<int,int>> mp;

signed main()
{
int ans=-1e18,ans2,ans_ID,ans_ID2;
    int n;
    cin>>n;
    int zhui[n+1],a[n+1];
  //直接开30万的long long在c++上炸了。所以要这么才行。
    for(int i=1;i<=n;++i)
      //切记！++i比i++快。都用++i
    {
        scanf("%lld",&a[i]);//快速输入
        if(a[i]>=0)
        {
        	zhui[i]=zhui[i-1]+a[i];
		}
        else
        {
        	zhui[i]=zhui[i-1];
		}
        if(mp[a[i]].first==0)mp[a[i]].first=i;
        mp[a[i]].second=i;//统计
    }
    for(int i=1;i<=n;++i)
    {
		if(mp[a[i]].first!=mp[a[i]].second
           &&i!=mp[a[i]].second)
       //&&后面的那些可以将时间复杂度÷2，避免算两次。
		{
			if(ans<=zhui[mp[a[i]].second-1]-
			zhui[mp[a[i]].first]+//中间的
			a[i]*2)//左右端点单独加上
			{
				ans=zhui[mp[a[i]].second-1]-
			    zhui[mp[a[i]].first]+a[i]*2;
				ans_ID=mp[a[i]].first;
				ans_ID2=mp[a[i]].second;
			}
		}
	}
	int cnt=0;
	for(int i=ans_ID+1;i<=ans_ID2-1;++i)//前后的无论是啥都要删，我们就直接累加中间的就OK
	{
	    if(i<ans_ID||i>ans_ID2)cnt++;
	    else if(a[i]<0&&i!=ans_ID&&i!=ans_ID2)cnt++;
	}
	cout<<ans<<" "<<ans_ID-1+(n-ans_ID2)+cnt<<endl;
  //后面一串公式就是要删的个数，等于左右的数目+中间是负数的（有损市容）
	for(int i=1;i<=n;++i)
	{    if(i>=ans_ID&&i<=ans_ID2&&!(a[i]<0&&i!=ans_ID&&i!=ans_ID2));//不删
	    else printf("%lld ",i);//删
	}
    return 0;
}
```

---

## 作者：_shine_ (赞：0)

显而易见可以发现的是：在一段区间中，要使得这个区间中的和最大，绝对要把负数给删掉。

根据这个思路，则开始思考怎样能找到一个总值最高的一段。第一想法就是在整个数列中排除掉那些负数的东西，但这只局限与区间内部。（即设左端点为 $l$，右端点为 $r$，要删去的负数下标 $x$ 必定为 $l<x<r$）

```-1 100000 1 1 -1```

例如上面这个的数据，一眼就发现肯定是选择 $-1$ 这段区间。所以说既然跑第一次很难知道整段的答案，那不妨就先跑一次算出整个序列中的区间最大值，随后在第二次时找到最大答案的方案进行输出就好了。

但由于 $n\le 3\times 10^5$，所以显然不能在循环时找到区间总值以及区间负数和，所以采用前缀和的形式预先处理出来再进行计算。

注意开 ```long long```
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn=3e5+10;
map<int,int>p;
int n,num,now_ans=LONG_LONG_MIN;
int a[maxn],b[maxn],c[maxn];
vector<int>ans;
void out_puts(int u){
    printf("%lld %lld\n",u,ans.size());
    for(int i=0;i<ans.size();++i)printf("%lld ",ans[i]);
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;++i){scanf("%lld",&a[i]);b[i]=b[i-1]+a[i];p[a[i]]=max(p[a[i]],i);if(a[i]<0)c[i]=c[i-1]+a[i];else c[i]=c[i-1];}
    for(int i=1;i<=n;++i){if(p[a[i]]==i)continue;now_ans=max(now_ans,b[p[a[i]]]-b[i-1]-(c[p[a[i]]-1]-c[i]));}
    for(int i=1;i<=n;++i){if(p[a[i]]==i)continue;if(now_ans==b[p[a[i]]]-b[i-1]-(c[p[a[i]]-1]-c[i])){num=0;for(int j=1;j<=n;++j){if(j<i || j>p[a[i]] || (a[j]<0 && j!=i && j!=p[a[i]])){ans.push_back(j);num+=a[j];}}out_puts(b[n]-num);return 0;}}
    return 0;
}
```


---

