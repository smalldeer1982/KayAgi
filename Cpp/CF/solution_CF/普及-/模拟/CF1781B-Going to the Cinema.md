# Going to the Cinema

## 题目描述

A company of $ n $ people is planning a visit to the cinema. Every person can either go to the cinema or not. That depends on how many other people will go. Specifically, every person $ i $ said: "I want to go to the cinema if and only if at least $ a_i $ other people will go, not counting myself". That means that person $ i $ will become sad if:

- they go to the cinema, and strictly less than $ a_i $ other people go; or
- they don't go to the cinema, and at least $ a_i $ other people go.

In how many ways can a set of people going to the cinema be chosen so that nobody becomes sad?

## 说明/提示

In the first test case, both people want to go to the cinema if and only if the other person goes. There are two valid options: either both people go, or neither of them goes. However, if just one of them goes, both will be sad.

In the second test case, everyone has to go to the cinema. In any other case, someone will be sad.

In the third test case, there are three valid options: person number $ 2 $ goes to the cinema; or persons with indices $ 2, 3, 4, 7 $ go; or all eight people go.

## 样例 #1

### 输入

```
4
2
1 1
7
0 1 2 3 4 5 6
8
6 0 3 3 6 7 2 7
5
3 0 0 3 3```

### 输出

```
2
1
3
2```

# 题解

## 作者：roger_yrj (赞：3)

## 题目大意

有 $n$ 个人要去看电影，第 $i$ 个人有一个要求 $a_i$，你要从 $n$ 个人中选出 $x$ 个人，满足：

- 当第 $i$ 没被选时，$a_i>x$。（不然个个都去了不带他会生气）
- 当第 $i$ 被选时，$a_i<x$。（不然去了没人陪也会生气）

求方案数。

## 解题思路

### 分析题目

稍微分析一些题目就会发现：

- 要求一样的人总是会**一起去**。
- 当 $a_i<a_j$ 且第 $j$ 个人去了，那第 $i$ 肯定也会去。换句话说就是**当一个人要去，那条件比他低的人都要去**。

根据特性一，我们可以想到把所有条件相同的放一起，也就是统计每个条件的人数。

比如第三个样例：
```
6 0 3 3 6 7 2 7
```
可以转化成：

$
\def\arraystretch{1.2}
\begin{array}{|c|c|c|c|c|c|c|c|c|} \hline
条件 & 0 & 1 & 2 & 3 & 4 & 5 & 6 & 7 \\ \hline
人数 & 1 & 0 & 1 & 2 & 0 & 0 & 2 & 2 \\ \hline
\end{array}
$

设此数组为数组 $b$。

然后根据特性二，我们可以想到用**前缀和**。

设 $sum_i = \sum_{j=0}^i b_j$。

### 解题方法

数据范围总是能提示我们：

$ \sum n≤2×10^5 $

这告诉我们时间复杂度是 $O(n)$ 的。

我们考虑用**枚举人数**的方法。

假设我们选了 $i$ 个人，则条件 $\le i$ 的人都**不**满足**不去**的要求 $(a_i>x)$，即要去的人数为 $sum_{i}$。

所以人数 $i$ 合法的条件一：$i=sum_{i}$。

但是，此时条件等于 $i$ 的人就说话了：“如果你带我去的话，我就**不**满足**去**的要求 $(a_i<x)$，那我就生气了！”。

这样我们就遇到了一个尴尬的情况，对于条件等于 $i$ 的人，不能带他去，也不能不带他去。所以想要人数 $i$ 合法，必须不能有这种尴尬的人。

因此人数 $i$ 合法的条件二：$b_i=0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,a[N],b[N],sum[N],ans; 
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		ans=0;
		for(int i=0;i<=n;i++)b[i]=sum[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			b[a[i]]++;
		}
		sum[0]=b[0];
		for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i];
		for(int i=0;i<=n;i++)if(sum[i]==i&&b[i]==0)ans++;
		printf("%d\n",ans);
	}
}
```
这么简短的代码不会有人看不懂吧……

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意

一个公司打算去看电影，有 $n$ 个人可以去，但每个人都有要求，他们说：“如果至少有 $a_i$ 个人去，且这些人中不包括我，我会去看电影。”

那么求看电影的人的方案数。

### 题目分析

1. 看完题首先想到最简单的暴力。枚举计划去的人数，然后看有多少人去，如相等，方案数 $+1$。

注意一个细节：判定方案是否合法时要记得判定是否 $a_i$ 等于该方案人数。

#### code:

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5+5;
int cnt[N], T, n, ans, a[N];
int main()
{
	cin >> T;
	while(T--)
	{
		cin >> n;
		ans = 0;
		for(int i = 1;i <= n;i++)
		{
			cin >> a[i];
			cnt[a[i]] = true;
		}
		for(int i = 0;i <= n;i++)
		{
			int flag = 0;
			for(int j = 1;j <= n;j++)
			{
				if(a[j] <= i)
					flag++;
			}
			if(flag == i && cnt[i] == false)
				ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
```

上述方法的时间复杂度是 $ O (T \times n ^ 2) $ 的，还是有点慢，那么如何优化？

2. 我们考虑到内层循环是枚举 $a$ 数组中有多少个 $\le i$ 的数，所以可以开个桶，并用前缀和计算，就可以 $O(1)$ 求出。

#### code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5+5;
int cnt[N], s[N], T, n, ans, a;
int main()
{
	cin >> T;
	while(T--)
	{
		cin >> n;
		ans = 0;
		for(int i = 0;i <= n;i++)
			cnt[i] = s[i] = 0;
		for(int i = 1;i <= n;i++)
		{
			cin >> a;
			cnt[a]++;
		}
		s[0] = cnt[0];
		for(int i = 1;i <= n;i++)
			s[i] = s[i-1] + cnt[i];
		for(int i = 0;i <= n;i++)
			if(s[i] == i && cnt[i] == 0)
				ans++;
		cout << ans << endl;
	}
	return 0;
}
```

这样，程序就优化到了 $O(T \times m)$ 的时间效率。

但是，前缀和的预处理还是有点慢，我们再来思考一下能不能使程序更快一点。

我们仔细观察后会发现：

- 如果 $i$ 要去电影院，那么所有满足 $a_j = a_i$ 的 $j$ 都会去电影院。
- 同理，如果 $i$ 不去电影院，那么所有满足 $a_j = a_i$ 的 $j$ 都不会去电影院。

于是，我们只需要枚举所有不同的 $a_i$ 就可以了。而且，我们可以先将 $a$ 数组排序，就省去了处理前缀和和桶排的时间了。

#### code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int T, n, a[N], ans;
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		for(int i = 1;i <= n;i++)
			scanf("%d", &a[i]);
		a[n+1] = N;
		sort(a + 1, a + 1 + n);
		ans = 0;
		a[1] ? ans++ : 1;
		for(int i = 1;i <= n;i++)
			(a[i] != a[i+1] && i < a[i+1] && i > a[i]) ? ans++ : 1 ;
		printf("%d\n", ans);
	}
	return 0;
}
```

此程序可能不是最优解，但足足跑到了78ms！

---

## 作者：wangxinyi2010 (赞：1)

**题目大意**
------------
一个有 ```n``` 个人的公司计划去看电影，每个人要么去要么不去。对于第 ```i``` 个人，如果除了他有大于等于  ```a_i``` 个人去，那么他就必须去。反之，他就必须不去。
   
求看电影的方案数。

**题目分析**
------------
我们先来分析一下计划去的总人数（这里把它称作 ```j```）与第 ```i``` 个人的选择之间的关系：

- 如果 ```j<a_i``` 且他去电影院，那么 ```j-1<a_i```，矛盾，所以他必须不去。

- 如果 ```j=a_i``` 且他去电影院，那么 ```j-1<a_i```，矛盾；如果他不去电影院，那么 ```j=a_i```，同样矛盾，所以这种情况不可能存在。

- 如果 ```j>a_i``` 且他去电影院，那么 ```j-1>=a_i```，成立。

所以，这道题的做法已经显而易见了：把 ```a_i``` 从小到大排序，再从 ```0``` 与 ```n``` 之间找到不等于所有 ```a_i``` 的 ```j```，如果这个数与小于这个数的 ```a_i``` 的个数相同，则 ```ans++```。

为了快速找到小于 ```j``` 的 ```a_i``` 的个数，我用了一个整型数组 ```b``` 来表示 ```a_i``` 与 ```i``` 的对应关系（与数组 ```a``` 相反）（多个相等的 ```a_i``` 取最大的 ```i```），又用 ```now``` 来存储小于 ```j``` 的最大 ```a[i]``` 在 ```b``` 中对应的数，就是我们想求的小于 ```j``` 的 ```a_i``` 的个数。

**AC 代码**
-----------
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int t,n,a[200005],b[200005];
int main(){
	cin>>t;//数据组数
	for(int i=1;i<=t;i++){
		cin>>n;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));//一定要清空！
		for(int j=0;j<n;j++) cin>>a[j];
		sort(a,a+n);
		for(int j=0;j<n;j++) b[a[j]]=j+1;
		int now=0,ans=0;
		for(int j=0;j<=n;j++){
			if(b[j]!=0) now=b[j];
			else if(j==now) ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
最高用时 623ms。

---

## 作者：HTensor (赞：0)

题目有一个性质，一旦去的人数确定，去的人员也就确定了。

将人员按照满意度排序。倘若有 $i$ 个人前往，则不包括自己，满意度小于等于 $i - 1$ 的人一定会前往。检查所有符合条件的人是否为 $i$ 个即可。

但考虑特殊情况，如果此时（按满意度升序）第一个不前往的人满意度刚好等于 $i$，如果他不去，则会变的沮丧。若去，则去的人数至少为 $i+1$ 个，均不满足题意。

枚举去的人数，然后二分判断即可。

```cpp
#include <bits/stdc++.h>
#define d(x) cerr << #x << " => " << x << endl
#define dd(x) cerr << #x << endl
#define D cerr << "Passed [" << __FUNCTION__ << "] on line " << __LINE__ << endl
#define ms(x) memset(x, 0, sizeof x)
#define int long long

template<typename T> std::istream& operator>>(std::istream& is, std::vector<T>& v) { for (auto& i : v) is >> i; return is; }
template<typename T> std::ostream& operator<<(std::ostream& os, std::vector<T>& v) { for (auto& i : v) os << i << " "; return os; }
template<typename T> auto dbug(const std::initializer_list<T>& a) { for (auto& i : a) std::cout << i << " "; std::cout << "\n"; }

using namespace std;

const int inf = 0x3f3f3f3f3f3f3f3f;

int rd() {
	int f = 1, val = 0; char ch = getchar();
	while(!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while(isdigit(ch)) val = val * 10 + ch - '0', ch = getchar();
	return f * val;
}

void solve() {
	int n = rd();
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) a[i] = rd();
	sort(a.begin() + 1, a.end());
	int ans = 0;
	for(int i = 0; i <= n; i++) {
		if(upper_bound(a.begin() + 1, a.end(), i - 1) - a.begin() - 1 == i) {
			if(upper_bound(a.begin() + 1, a.end(), i - 1) == a.end()) 
				++ans; 
			else if(*(upper_bound(a.begin() + 1, a.end(), i - 1)) != i) ++ans;
		}
	}
	printf("%lld\n", ans);
}

signed main() {
	int T = rd();
	while(T--) solve();
	return 0;
} 	
```

---

## 作者：DANIEL_x_ (赞：0)

## 思路分析：
这个题有两个特点。

1. 如果 $a_k<a_j$ 并且 $j$ 要去看，那么 $k$ 也要去。

2. 一样的人一定会一起去。

第一个特点想到前缀和。

第二个特点想到把所有要求一样的人统计一下。

通过暴力枚举，如果有 $i$ 个人不去，就有 $flg_i=0$，所以是 $i=sum_i$。

如果一个人要求有 $i$ 个人要去，则会有 $flg_i=0$。

## code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int T,a[maxn],b[maxn],sum[maxn],n,ans; 
int main(){
	cin>>T;
	while(T--){
    cin>>n,ans=0;
		for(int i=0;i<=n;i++) b[i]=sum[i]=0;
		for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]++;
		sum[0]=b[0];
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+b[i];
		for(int i=0;i<=n;i++)
        	if(sum[i]==i&&b[i]==0)
            	ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

## 题意

一共有 $n$ 个人想要去电影院，每个人去电影院的条件都是至少要有 $a_i$ 个人（不算他自己）陪他一起去电影院。问去电影院的人数有几种可能。

## 思路

通过简要分析题意，不难发现两点：

+ 两个 $a_i$ 如果相等，那么就会一起去。

+ 如果第 $i$ 个人去了，并且 $a_i>a_j$，那么第 $j$ 个人也一定会去。

根据第一点，可以想到统计每种 $a_i$ 有多少个，也就是下标计数（ `js[a[i]]++;` ）。比如说读入了 $5$，$js_5\gets js_5+1$。

再根据第二点，不难想到部分和。

统计了部分和，我们可以枚举选几个人。

如果我们选了 $i$ 个人，那么去的条件人数小于 $i$ 的人都必须去，要去的人数应该等于 $ans_i$（前缀和数组）。所以第一个条件是：$ans_i=i$

但是明显的，去的条件人数大于 $i$ 的人直接不去，去的条件人数小于 $i$ 的人必须去，那么去的条件人数等于 $i$ 的人要不要去呢？我们不能让他去，也不能不让他去，为了避免这种量子力学情况，应该进行判断。所以第二个条件也出来了：$js_i=0$。

那么怎么做已经很明显了，人数从 $0$ 到 $n$ 循环，判断每个数是否负责上面的两个条件，如果都符合可能就加一种。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,sum;
int a[200010],js[200010],ans[200010];
int main(){
	scanf("%d",&t);
	while(t--){
		sum=0;
		scanf("%d",&n);
		for(int i=0;i<=n+1;i++)js[i]=ans[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			js[a[i]]++;
		}
		ans[0]=js[0];
		for(int i=1;i<=n;i++)ans[i]=ans[i-1]+js[i];
		for(int i=0;i<=n;i++)if(ans[i]==i&&js[i]==0)sum++;
		printf("%d\n",sum);
	}
	return 0;
}
```

---

## 作者：ZM____ML (赞：0)

# 题目大意
一个公司有 $n$ 个人可以去看电影，但每个人都有各自的要求，第 $i$ 个人的要求是：如果除我之外至少有 $a_i$ 个人去，我就会去看电影。

那么求看电影的人的方案数。

# 题意分析
对题意进行分析，可以看出有以下两个特点：

1. 要求一样的人会一起去。

1. 当一个人去了，那要求比他低的都要去，也就是 $a_i < a_j$ 且 $j$ 去了，那么 $i$ 也要去。

那么根据第一个特点，可以把所有要求一样的人统计在一起。

而根据第二个特点，可以想到前缀和。

令 $ sum_i = \sum_{j = 0}^{i} b_j $。

预处理结束之后，我们可以通过枚举的方法，假设有 $i$ 个人不去，那么要去的人就有 $sum_i$ 名，所以第一个条件就是 $i = sum_i$。

而一个人如果要求人数等于 $i$ 时，那么不能带他去，也不能不带他去，所以又有了第二个条件 $b_i = 0$。

## 思路明确，给出代码
```c
#include<cstdio>
#include<cstring>
using namespace std;
const int N=2e5+5;
inline int read(){      //快读模板 
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int T,a[N],b[N],sum[N]; 
int main(){
	T=read();
	while(T--){
		int n=read(),ans=0;
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		memset(sum,0,sizeof sum);//虽然可以不清，但是是个好习惯，不然多组数据不清空。。。 
		for(int i=0;i<=n;i++)b[i]=sum[i]=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			b[a[i]]++;
		}
		sum[0]=b[0];
		for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i];
		for(int i=0;i<=n;i++)if(sum[i]==i&&b[i]==0)ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：thomas_zjl (赞：0)

1. 题目大意。

   一个公司打算去野营，有 $n$ 个人可以去，但第 $i$ 人都有每个人的要求：

   > 1. 参加野营的人数在 $a_i$ 以下，那么第 $i$ 个人不会去。
   > 2. 参加野营的人数在 $a_i$ 以上，那么第 $i$ 个人一定要去。 

   那么求参加野营的人的方案数。

2. 解题方法。

   通过对题目的解读，我们可以得出如下性质。

   1. 不难发现，如果第 $i$ 个人要去，那么与他要求一样的人 $(a_i = a_j)$ 也会去。

   2. 同理，如果第 $i$ 个人不去，那么与他要求一样的人 $(a_i = a_j)$ 也不会去。

   3. 我们还可以发现，如果第 $i$ 个人要去，那么比他要求低 $(a_i > a_j)$ 的人都会去。

   4. 同理，如果第 $i$ 个人不去，那么比他要求高 $(a_i < a_j)$ 的人都不会去。

   根据上述的四条性质，我们可以先将数组进行排序。

   从 $1$ 到 $n$ 遍历数组。

   如果 $a_i \not= a_{i+1}$ 。

   那么代表第 $i$ 个人和第 $i+1$ 个人的要求不同。

   如果要一种新的方案，那么要第 $i$ 个人参加且第 $i+1$ 个人不参加。

   结合题意。即可得出当 $i < a_{i+1}$ 且 $i > a_i$ 时，就可以有一种新的方案。

   注意，当 $a_1 \not= 0$ 的时候，那么一个人都不去也是一种方案1。

   全部都去一定是一种可行的方案。

3. 代码。

   ```cpp
   #include<bits/stdc++.h>
   using namespace std;
   int t;
   int n;
   int a[200005];
   int main(){
       ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
       cin>>t;
       while(t--){
           cin>>n;
           for(int i=1;i<=n;i++){
               cin>>a[i];
           }
           a[n+1]=INT_MAX;//让第 n+1 位等于一个很大的数 (x>n) , 可以顺便在循环中加上全部都去的一个方案。
           //同理，可以在 0 位上放一个很小的数 (x<0) , 可以顺便在循环中加上 a[1]=0 的一个方案。
           sort(a+1,a+1+n);
           int ans=0;
           if(a[1]!=0){
               ans++;
           }//特判。
           for(int i=1;i<=n;i++){
               if(a[i]!=a[i+1]){
                   if(i<a[i+1]&&i>a[i]){
                       ans++;
                   }
               }
           }
           //核心代码。
           cout<<ans<<'\n';
       }
       return 0;
   }
   ```

   

---

