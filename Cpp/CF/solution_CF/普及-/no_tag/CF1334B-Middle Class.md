# Middle Class

## 题目描述

Many years ago Berland was a small country where only $ n $ people lived. Each person had some savings: the $ i $ -th one had $ a_i $ burles.

The government considered a person as wealthy if he had at least $ x $ burles. To increase the number of wealthy people Berland decided to carry out several reforms. Each reform looked like that:

- the government chooses some subset of people (maybe all of them);
- the government takes all savings from the chosen people and redistributes the savings among the chosen people equally.

For example, consider the savings as list $ [5, 1, 2, 1] $ : if the government chose the $ 1 $ -st and the $ 3 $ -rd persons then it, at first, will take all $ 5 + 2 = 7 $ burles and after that will return $ 3.5 $ burles to the chosen people. As a result, the savings will become $ [3.5, 1, 3.5, 1] $ .

A lot of data was lost from that time, so we don't know how many reforms were implemented and to whom. All we can do is ask you to calculate the maximum possible number of wealthy people after several (maybe zero) reforms.

## 说明/提示

The first test case is described in the statement.

In the second test case, the government, for example, could carry out two reforms: $ [\underline{11}, \underline{9}, 11, 9] \rightarrow [10, 10, \underline{11}, \underline{9}] \rightarrow [10, 10, 10, 10] $ .

In the third test case, the government couldn't make even one person wealthy.

In the fourth test case, the government could choose all people to carry out a reform: $ [\underline{9}, \underline{4}, \underline{9}] \rightarrow [7\frac{1}{3}, 7\frac{1}{3}, 7\frac{1}{3}] $ .

## 样例 #1

### 输入

```
4
4 3
5 1 2 1
4 10
11 9 11 9
2 5
4 3
3 7
9 4 9```

### 输出

```
2
4
0
3```

# 题解

## 作者：Warriors_Cat (赞：4)

### $Description:$

给你 $n$ 个数 $a_i$，你可以经过以下操作任意次：

* 取出这 $n$ 个数中的任意几个数（可以全部），用它们的平均数替换成它们。

问最后最多有多少个数 $\ge x$。

### $Solution:$

考虑贪心，我们将所有数减去 $x$，再排个序，记录下所有数的和 $sum$。如果 $sum \ge 0$ 就直接全部数操作一次就行了。否则，我们把目前最小的数移出这个序列，再判断 $sum$ 的大小。一次类推即可。

具体看代码：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long//偷个懒（
int t, n, m, a[100010], sum;
signed main(){
	scanf("%lld", &t);
	while(t--){
		scanf("%lld%lld", &n, &m);
		for(int i = 1; i <= n; ++i){
			scanf("%lld", a + i);
			a[i] -= m;//先减去那个数
			sum += a[i]; 
		}
		sort(a + 1, a + n + 1);
		bool flag = 0;
		for(int i = 1; i <= n; ++i){
			if(sum >= 0){//若大于等于 0
				printf("%lld\n", n - i + 1);//直接输出
				flag = 1;//标记有输出过
				break;
			}
			sum -= a[i];
		}
		if(!flag) printf("0\n");//如果没有输出过就代表答案为 0
		sum = 0;//注意清零
	}
	return 0;
}
```


---

## 作者：lingfunny (赞：3)

# 题目翻译
有$n$个数，每个数的值为$a_i$，让你选$k$个数，使得这$k$个数的平均值大于$x$，问这个$k$最大是多少。
# 题目分析
考虑贪心。首先求出所有数的平均值，然后每次去掉最小的那个数，这样平均值肯定会上涨。涨到这个平均值大于$x$的时候就可以输出解了。既然要去掉最小的数，可以使用优先队列来维护（在线），或者直接用$sort$（离线），总时间复杂度$O(n\log_2 n)$。$n\le10^5$，可放心食用。

但是这里还有一个要注意的点，由于是要求平均值，所以至少要先把所有数加起来，由于$a_i\le 10^9,n\le10^5$，所以$sum \le 10^{14}$，$long long$安排上。

如果还是不明白的话，可以参考代码的注释
# 代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int t,n;
const int maxn=100005;
priority_queue <long long, vector<long long>, greater<long long> > q;	//优先队列，因为是要去掉最小的，所以要使用greater
long long sum,x;	//sum是当前和，x前面有说
double pj;			//pj 平均
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;sum=0;				//先清空，因为有多组数据
		for(int i=1;i<=n;++i){
			int k;						//读入一个数
			cin>>k;
			sum+=k;						//sum加上
			q.push(k);					//入队
		}
		pj=(double)sum/n;				//先算平均值
		while(pj < x && !q.empty()){
			//如果平均值还小于x，就要再删
			//但是有可能删空了，没得删，所以要加个!q.empty()
			long long out=q.top();		//取出首元素
			sum-=out;--n;				//sum减掉，现在是总共选择少了一个，所以--n，这个n是最后的答案
			pj=1.0*sum/n;				//重新计算平均值，因为sum和n都是longlong类型，要加个类型转换
			q.pop();					//出队
		}
		cout<<n<<endl;					//输出解
		while(!q.empty())				//因为有多组数据，所以要先清空队列
		q.pop();
	}
	return 0;
}
```

---

## 作者：zjhzs666 (赞：2)

# 题意
共 $t$ 组数据，每次给定长度为 $n$ 的数组以及正整数 $x$，我们可以将该数组内的数进行任意次交换，每次可以从数组中选取任意一些数然后用它们的平均数代替，求最终有多少个数大于等于 $x$。



# 思路
题目需要我们让最终大于等于 $x$ 的数尽可能多，因此，我们应当让较大的数尽量去与较小的数去配对，以达到最优，所以我们可以对数组进行排序，但是如果我们选择的较大的那些数与较小的那些数的平均数比 $x$ 小该怎么办呢？很简单，只需要就较小的一些数删除即可，那么这样的话，核心思路就出来啦，只需要贪心选择元素，如果加入这个元素将使平均数小于 $x$ 的话那么就不选择它，直接输出。



# 代码



```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[100001],i;
long long s;
bool cmp(int x,int y){
	return x>y;
} 
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		for(i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1,cmp);//从大到小排序
		for(i=1;i<=n;i++){
			if(s+a[i]>=x*i)s+=a[i];//可以拿加入s
			else break;不能拿直接退出
		}
		cout<<i-1<<endl;//第i个不可取，所以可取的数有i-1个
	} 
	return 0;
}
```



---

## 作者：AutumnKite (赞：1)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

假设我们已经知道了答案 $s$，考虑如何判断是否合法。

我们需要让 $s$ 个人的钱数 $\ge x$，那么我们的最优策略一定是选择最大的 $s$ 个人，然后对这 $s$ 个人进行一次操作，如果得到的平均值 $\ge x$ 则符合条件，否则一定不可以。

那么我们只要将所有数从大到小排序以后，枚举答案 $s$ 进行判断即可。

### 代码

```cpp
const int N = 100005;

int n, x, a[N];

void solve() {
	read(n), read(x);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	std::sort(a + 1, a + 1 + n);
	std::reverse(a + 1, a + 1 + n);
	long long sum = 0;
	for (int i = 1; i <= n; ++i) {
		sum += a[i];
		if (sum < 1ll * x * i) {
			print(i - 1);
			return;
		}
	}
	print(n);
}
```

---

## 作者：lmndiscyhyzdxss (赞：0)

## 题目大意
 $ T $ 组数据。
 
每组数据给定 $ n $ 和 $ x $，和一个数组 $ a_i $。

对这个数组可以做任意次变换，每次变换可以从 $ a $ 中选一些数，将他们变成平均数。

求最多可以有多少个数大于等于 $ x $。
## 题目分析
先排序，记录下所有数的和 $ h $。如果 $ sum\geq i \times m $ 即剩下的数的平均数比 $ m $ 大，就直接把剩余数操作一次就行了。否则，我们把目前最小的数移出这个序列，重复判断即可。

注意：不开 long long 会爆炸的还要记得清零 $ h $。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,a[100010],h,p;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n>>m,h=0,p=0;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),h+=a[i]; 
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
		{
			if(h>=(n-i+1)*m){cout<<n-i+1<<endl,p=1;break;}
			h-=a[i];
		}
		if(p==0)cout<<0<<endl;
	}
	return 0;
}
```

---

## 作者：happy_zero (赞：0)

这道题是一道简单的贪心。首先任意次操作其实可以合并成一次操作：如果几次操作的平均值均大于等于 $x$，则这些数合在一起的平均数也一定是大于等于 $x$ 的。在这一次操作中，肯定是在平均数大于等于 $x$ 的前提下，选的数越多越好，刚开始可以选所有数，如果平均数大于 $x$ 就直接输出，否则舍弃当前选中最小的数（这样会使平均数变高）直至平均数大于等于 $x$，这个操作可以用优先队列维护。注意，由于本身大于等于 $x$ 的数一定被选择，所以选的个数便是答案：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
double a[N];
priority_queue <int, vector <int>, greater <int> > q;
signed main(){
	int T;
	cin >> T;
	while (T--)
	{
		while (!q.empty()) q.pop();
		int n, x, sum = 0;
		cin >> n >> x;
		for (int i = 1; i <= n; i++)
			cin >> a[i], sum += a[i], q.push(a[i]);
		int ans = 0;
		for (int i = n; i >= 1; i--)
		{
			if (sum * 1.0 / i >= x)
			{
				ans = i;
				break;
			}
			sum -= q.top();
			q.pop();
		}	
		cout << ans << endl;
	}
	return 0;
}

```


---

## 作者：xrdrsp (赞：0)

这是本人的 $006$ 个题解。

本题是一个贪心题。

不需要暴力每种选择，只要知道何时能通过求平均得到最大的富人数就行。

可以从大到小排序，然后从前往后枚举。具体见注释。

说明：`reverse()` 的功能是求倒序。允许字符串、数组等。

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

// 注意 long long
long long a[N];
long long n, x;
long long T;

int main() {
    cin >> T;
    while (T--) {
        scanf("%lld%lld", &n, &x);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);		// 读入。
        }
        sort(a + 1, a + n + 1);			// 排序。
        reverse(a + 1, a + n + 1);		// 倒序。
        long long sum = 0;
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            sum += a[i];				// 求和，主要用来判断是否能通过取平均使这些人都变成富人
            if (sum >= x * i) {			// 判断。如果较大的 i 个的财富总和大于平均数总和（i.e. 还能继续求平均使富人变多），就更新 ans。
                ans = i;
            }
        }
        printf("%lld\n", ans);			// 输出。
    }
    return 0;
}
```

---

## 作者：syzf2222 (赞：0)

可以发现变换之后总和不变。

若有$ans$个数变换后大于等于$x$，

则变换前其和大于等于$ans* x$。

最大化$ans$，即将$a_i$从大到小排序，从前往后取。

一直取到不能去，就是答案。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+10;
int t,n,x,a[maxn];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
inline int cmp(int x,int y){return x>y;}
signed main(){
	t=read();
	while(t--){
		n=read();x=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		sort(a+1,a+1+n,cmp);
		int sum=0,ans=0;
		for(int i=1;i<=n;i++){
			sum+=a[i];
			if(sum<i*x)break;
			ans=i;
		}
		printf("%lld\n",ans);
	} 
	return 0;
}
```
希望能有所帮助。

---

## 作者：寒鸽儿 (赞：0)

因为要平均分配 , 所以选择加入原先拥有钱数尽可能多的人一定是最优的。  

因此对钱数排序 , 然后从左往右扫过去 , 看看平均值是否还大于等于 $x$ , 最后一次满足平均值大于等于 $x$ 的人数即为最大总人数。  

复杂度 $\mathcal{O(n \log n)}$   

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define repp(i,a,b) for(int i=a;i<(b);++i)
#define perr(i,a,b) for(int i=a;i>(b);--i)
#define pb push_back
#define rz resize
#define VI vector<int>
#define VL vector<long long>
#define VD vector<double>

using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, maxn = 12345;
const ll linf = 0x3f3f3f3f3f3f3f3f;

VI a;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tests;
	cin>>tests;
	while(tests--) {
		int n, x;
		cin >> n >> x;
		a.assign(n+2, 0);
		rep(i,1,n) cin >> a[i];
		sort(&a[1], &a[n + 1], [&](int ai, int bi){ return ai > bi; });
		unsigned long long sum = 0;
		rep(i,1,n) {
			sum += a[i];
			if(sum / i < x) {
				cout << i - 1 << endl;
				break;
			}
			if(i == n) cout << n << endl;
		}
	}
	return 0;
}
```


---

## 作者：Histone (赞：0)

蒟蒻的方法果然和大佬们的不一样……

但是思想还是贪心

首先对输入进来的数据排序，由大到小

然后我们设置两个指针扫数据

一个在最末端，一个在 $i$ 位置 ( $a_i < x$ )

向前扫，用后面的来补前面的

来一组数据，大家就明白了

```cpp
5 3
1 1 2 3 6
```

第一次操作后

```cpp
5 3
1 1 3 3 5
```

第二次操作后

```cpp
5 3
1 3 3 3 3
```

最后就是统计答案了

上代码~

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;

inline int read(){
	re int ans = 0;re bool f = 1;re char ch = getchar();
	while(ch<'0'||ch>'9'){if (ch=='-')f = 0;ch = getchar();}
	while(ch>='0'&&ch<='9'){
		ans = (ans<<3)+(ans<<1)+(ch^48);
		ch = getchar();
	}
	return f?ans:~(ans-1);
}
const double ep = 1e-5;
double num[100005];
bool cm(double a,double b){
	return a<b;
}
signed main(void){
	int t = read();
	while(t--){
		memset(num,0,sizeof(num));
		int n = read(),k = read(),x = 0;
		for(re int i=1;i<=n;++i)
			num[i] = (double)(read()-k);
		sort(num+1,num+n+1,cm);
		for(re int i=1;i<=n;++i){
			if(num[i]>=0){
				x = i;
				break;
			}
		}
		if(x==0){
			printf("0\n");
			continue;
		}
		for(re int i=x-1,j=n;i>=1&&j>=1&&num[j]>=0.0;){
			if(num[j]+num[i]>=0.0){
				num[j]+=num[i];
				num[i]=0.0;
				i--;
				if(fabs(num[j]-0.0)<=ep)j--;
			}
			else{
				num[i]+=num[j];
				num[j] = 0.0;
				j--;
				if(fabs(num[i]-0.0)<=ep)i--;
			}
			
		}
		for(re int i=1;i<=n;++i){
			if(num[i]>=0.0){
				x = i;
				break;
			}
			
		}
		printf("%lld\n",n-x+1);
	}
}
/*
3
4 5
1 2 3 4 
10 2
1 1 1 1 1 2 2 2 2 2
7 3
1 3 4 3 1 4 4 
*/
```

[这里](http://47.102.209.15/index.php/archives/21/) 阅读体验更加 

---

## 作者：Aehnuwx (赞：0)

大力猜结论的贪心题。

先把 $a$ 数组升序排序一下。

弄两个预处理数组。$rich[i]$ 表示**排序后**前 $i$ 个人中富人的个数，$s[i]$ 表示**排序后**后 $i$ 个人钱数的后缀和。

于是枚举 $i=0,1,\cdots,n-1$，判断后 $(n-i)$ 个人平均分财产后的富人数量与当前的富人数量哪一个大。就这样一直打擂台下去就能找到最大化的富人数量了。

感性理解一下...这个贪心方法似乎是对的...

似乎我的做法跟别人的很不一样...不要 fst 錒(

Code:

记得开`long long`。

```cpp
#include <bits/stdc++.h>
#define ll long long
const char* chk[]={"NO","YES"};
using namespace std;
const int maxN=100005;
int n,x,a[maxN],rich[maxN];
ll s[maxN];
void solve();
int main() {
    int t;scanf("%d",&t);
    for (;t;t--) solve();
    return 0;
}
void solve() {
    memset(rich,0,sizeof rich);
    memset(s,0,sizeof s);
    // 多组数据，记得清空数组
    scanf("%d%d",&n,&x);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++) rich[i]+=a[i]>=x;
    for (int i=n;i;i--) s[i]=s[i+1]+a[i];
    // 预处理 rich[] 和 s[] 数组
    //printf("s[1]=%d\n",s[1]);
    int ans=rich[n];
    for (int i=0;i<n;i++) {
        double get=1.0*s[i+1]/(n-i);
        // get 表示后 (n-i) 个人总财产的平均数
        //printf("get=%lf\n",get);
        int now=rich[i];
        if (get>=x) now+=n-i;
        ans=max(ans,now); // 打擂台找最大化的富人数
        //printf("now=%d\nans=%d\n",now,ans);
    }
    printf("%d\n",ans);
}

```


---

