# Array and Operations

## 题目描述

You are given an array $ a $ of $ n $ integers, and another integer $ k $ such that $ 2k \le n $ .

You have to perform exactly $ k $ operations with this array. In one operation, you have to choose two elements of the array (let them be $ a_i $ and $ a_j $ ; they can be equal or different, but their positions in the array must not be the same), remove them from the array, and add $ \lfloor \frac{a_i}{a_j} \rfloor $ to your score, where $ \lfloor \frac{x}{y} \rfloor $ is the maximum integer not exceeding $ \frac{x}{y} $ .

Initially, your score is $ 0 $ . After you perform exactly $ k $ operations, you add all the remaining elements of the array to the score.

Calculate the minimum possible score you can get.

## 说明/提示

Let's consider the example test.

In the first test case, one way to obtain a score of $ 2 $ is the following one:

1. choose $ a_7 = 1 $ and $ a_4 = 2 $ for the operation; the score becomes $ 0 + \lfloor \frac{1}{2} \rfloor = 0 $ , the array becomes $ [1, 1, 1, 1, 3] $ ;
2. choose $ a_1 = 1 $ and $ a_5 = 3 $ for the operation; the score becomes $ 0 + \lfloor \frac{1}{3} \rfloor = 0 $ , the array becomes $ [1, 1, 1] $ ;
3. choose $ a_1 = 1 $ and $ a_2 = 1 $ for the operation; the score becomes $ 0 + \lfloor \frac{1}{1} \rfloor = 1 $ , the array becomes $ [1] $ ;
4. add the remaining element $ 1 $ to the score, so the resulting score is $ 2 $ .

In the second test case, no matter which operations you choose, the resulting score is $ 16 $ .

In the third test case, one way to obtain a score of $ 0 $ is the following one:

1. choose $ a_1 = 1 $ and $ a_2 = 3 $ for the operation; the score becomes $ 0 + \lfloor \frac{1}{3} \rfloor = 0 $ , the array becomes $ [3, 7] $ ;
2. choose $ a_1 = 3 $ and $ a_2 = 7 $ for the operation; the score becomes $ 0 + \lfloor \frac{3}{7} \rfloor = 0 $ , the array becomes empty;
3. the array is empty, so the score doesn't change anymore.

In the fourth test case, no operations can be performed, so the score is the sum of the elements of the array: $ 4 + 2 = 6 $ .

## 样例 #1

### 输入

```
5
7 3
1 1 1 2 1 3 1
5 1
5 5 5 5 5
4 2
1 3 3 7
2 0
4 2
9 2
1 10 10 1 10 2 7 10 3```

### 输出

```
2
16
0
6
16```

# 题解

## 作者：activeO (赞：4)

## 题意

就不多解释了，[题面](https://www.luogu.com.cn/problem/CF1618D)说的很清楚了。

## 思路

很明显这是一道贪心题。~~而且很水~~

我们把 a 数组排序一遍后，最小的那 $ n-2k $ 个元素，最后肯定会剩下来，因为要求最小，会尽量把大元素用 k 次操作消掉。所以就直接把 $ n-2k $ 个最小元素加到 ans 里。然后就是消大元素时，一定要头尾消，因为要尽量避免相同的元素，~~否则第一个样例就会被卡掉~~但是如果还是有相等的元素，就 $ ans \gets ans+1 $ 吧。

## 代码

```cpp
#include <bits/stdc++.h>// 祝大家学习愉快！

#define int long long

using namespace std;

const int maxn=110;
int a[maxn];

signed main(){
	
	int t;
	
	scanf("%lld",&t);
	
	while(t--){
		int n,k,ans=0;
		scanf("%lld %lld",&n,&k);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=n-2*k;i++) ans+=a[i];
		for(int i=n-k+1;i<=n;i++){
			if(a[i]==a[i-k]) ans++;
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

# CF1618D Array and Operations 题解
## 思路
又是一道简单的**贪心**。

我们可以先对数组进行排序，再将数组划分为两部分：
- 第一部分为数组中较小的数，有 $n-2k$ 个。
- 第二部分为数组中较大的数，有 $2k$ 个。

对于第一部分，我们不进行操作，直接加到得分中。

第二部分，我们分成个数相等的两份，让第 $1$ 大的和第 $k+1$ 大的操作，第 $2$ 大的和第 $k+2$ 大的操作...

这样第二部分每一次操作只会有两种可能：
- 第 $m$ 大的比第 $k+m$ 大的大：
    得分加 $0$。

- 第 $m$ 大的和第 $k+m$ 大的一样大：
    得分加 $1$。

所以我们可以循环操作：
自第 $n-2k$ 大的元素起，至 $n-k-1$ 大的元素为止，将得分加上 $\lfloor\frac{n-2k+i}{n-k+i}\rfloor$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int a[105] , n , k , t；
long long cnt;
int main()
{
	cin >> t;
	while(t--)
	{
		scanf("%d%d" , &n , &k);
		for(int i = 0 ; i < n ; i++)
		{
			scanf("%d" , &a[i]);
		}
		cnt = 0;//计数器清零 
		sort(a , a + n);//数组排序 
		for(int i = 0 ; i < n - k * 2 ; i++)
		{
			cnt += a[i];//将涉及不到的数先加入计数器 
		}
		for(int i = n - k * 2 ; i < n - k ; i++)//贪心算法 
		{ 
			if(a[i] == a[i + k])//将差最小的两组数比较 
			{
				cnt++;//如果相等则结果为1，否则为0 
			}
		}
	    printf("%lld\n" , cnt);//大功告成 
	}
	return 0;//圆满结束 
}
```

---

## 作者：huyangmu (赞：2)

这道题要使用贪心的思想。

对于任意的 $a_{i}$ 和 $a_{j}$ 当 $a_{i}\le a_{j}$ 时，贡献的得分只能是 $0$ 或 $1$，所以要让剩下的 $n-2\times k$ 个数贡献的得分尽量少。

所以可以排序，然后计算前 $n-2\times k$ 个数贡献的分数，剩下的数要使 $0$ 分贡献尽量多，所以首尾配对。

### AC Code
```cpp

#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 105;
int T,n,k,a[N],ans;
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T --){
		cin >> n >> k;
		for (int i = 1; i <= n; ++i) cin >> a[i];
		sort (a + 1, a + n + 1);
		ans = 0;
		for (int i = 1; i <= n - 2 * k; ++i) ans += a[i];
		int l = n - 2 * k + 1, r = n - k;
		while (l <= r){
			ans += (a[l] / a[l + k]);
			++l;
		}
		cout << ans << '\n';
	}
	return 0;
}


---

## 作者：YangXiaopei (赞：1)

## Solution

使用贪心。

可以发现，一个数被一个正整数除了之后肯定不会变得更大。

所以，不选的 $n - 2 \times k$ 个数所占比重更高。

那我们要让最小的 $n - 2 \times k$ 加入得分。

那现在就要让 $2 \times k$ 个数两两搭配让得分最小。

可以发现，让小的除以大的更划算。

我们先排序，再让 $a_i$ 和 $a_{i + k}$ 搭配即可。

这样可以让两个数尽量不相等，让得分尽量不加。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int q, n, k, a[105];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> q;
	while(q--){
		cin >> n >> k;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
		}
		sort(a + 1, a + n + 1);
		int sum = 0;
		for(int i = 1; i <= n - 2 * k; i++){
			sum += a[i];
		}
		for(int i = 1, l = n - 2 * k + 1; i <= k; i++, l++){
			sum += a[l] / a[l + k];
		}
		cout << sum << "\n";
	}
	return 0;
}
```

---

## 作者：Tachibana27 (赞：1)

因为在除法运算后结果必然不会比之前的大，所以考虑每一次贪心的选择，让最大的去参与除以运算。

明显先将数组排序，选择后 $2k$ 个数进行首尾配对。

~~由于本蒟蒻过于聪慧，把简单的题想复杂了~~，一开始选择的贪心策略是：选择尽可能大的数做除数，在结果最小的情况下尽可能让被除数大。然后，然后考试没写出来。

考试的时候太急了，其实仔细思考一下，既然已经是最大的数，那么除了除以它本身，结果必然为 $0$，所以只要首尾配对，便一定是最优解。

详见代码

code：

```cpp
%:include<bits/stdc++.h>
#define int long long
inline int read()<%
	int s=0;
	int w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
	for(;ch>='0' and ch<='9';ch=getchar())
		s=s*10+ch-'0';
	return s*w;
%>

void write(int x)<%
	if(x<0)<%
   		putchar('-');
   		x=-x;
	%>
	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
%>//快读快写自动略过
int t;
int a[10086];
signed main()<%
  	//freopen(".in","r",stdin);
  	//freopen(".out","w",stdout);
	t=read();
	while(t--){
			int n;
			int k;
			n=read();
			k=read();
			for(int i=1;i<=n;i++)
				a[i]=read();
			std::sort(a+1,a+1+n);//升序排序
			int ans=0;
			for(int i=1;i<=n-2*k;i++)
				ans+=a[i];//先将前面的，不需要参与除以运算的加起来
			for(int i=n-2*k+1;i<=n-k;i++)
				if(a[i]==a[i+k])//只有相同是相除以为1，其他为0
					ans++;
			
			write(ans);//输出
			puts("");
	}
  	return 0;//撒花
%>
```

---

## 作者：Hyh_111 (赞：0)

## **思路**

很明显这道题要用贪心来做。

用 $k$ 个最大元素做分母使得总分最小。

并且，我们要使剩下元素最小，要选第 $k+1$ 到第 $2k$ 大的元素做分子。

并且此时每个分数的值向下取整只能是 $0,1$ 中的一个，所以我们尽量减少分子和分母相等的分数的数量。于是可以想到头尾配对。

可以构造如下（假设 $a$ 以被从大到小排序）：

$$\frac{a_{k+1}}{a_1},\frac{a_{k+2}}{a_2},\dots, \frac{a_{2 \times k}}{a_k}$$

所以，先从大到小把 $a$ 排序，最终的答案即为：

$$\sum_{i=2 \times k+1}^{n}a_i + \sum_{i=1}^{k} \frac{a_{i+k}}{a_i}$$

## **Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105];

bool cmp(int x,int y)
{
	return x > y;
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n,k;
		cin >> n >> k;
		long long s = 0;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1,a + n + 1,cmp);//从大到小排序
		for (int i = 1; i <= k; i++) s += a[i + k] / a[i];//先求每个分数向下取整的和
		for (int i = 2 * k + 1; i <= n; i++) s += a[i];//再求剩余数的和
		cout << s << endl;
	}
	return 0;
}
```

---

## 作者：猜一猜我是谁 (赞：0)

# 思路
很明显这是一道贪心题。

先把 a 数组排个序，由于要让结果最小，所以取前 $n-2k$ 个数加到 ans 中。最后消掉大的数，为了避免两数相等，我们需要头尾消。

如样例的第一组，$n=7,\ k=3,\ a=\{1,1,1,2,1,3,1\}$，排序后为 $a=\{1,1,1,1,1,2,3\}$。把前 $n-2k=7-2\times3=1$ 个数加到 ans 中，即 $ans=1$。然后头尾消，即 $a[n-2k+1]$ 和 $a[n-k+1]$ 消，$a[n-2k+2]$ 和 $a[n-k+2]$ 消……在这里是 1 和 1 消，1 和 2 消，1 和 3 消，其中 1 和 1 相等，所以最后 $ans=2$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int main()
{
    int t,n,k,ans;
    cin>>t;
    while(t--)
    {
        ans=0;
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);//排序
        for(int i=1;i<=n-2*k;i++) ans+=a[i];
        for(int i=n-k+1;i<=n;i++)//头尾配对
            if(a[i-k]==a[i]) ans++;
        cout<<ans<<endl;
    }
}
```

---

## 作者：精神小伙！ (赞：0)

## 思路

这道题要用贪心来解决。

首先将 $ a $ 数组排序，将 $ n - 2k $ 个最小的数直接加到得分里。

接下来消较大的数，首尾配对，只要两数相等就把得分加一。

## 代码

```cpp
#include<iostream>
#include<algorithm>
int n,k;
int a[100010];
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int ans=0;
		cin>>n>>k;
		for(int i=1;i<=n;++i)
			cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=1;i<=n-2*k;++i)
		    ans+=a[i];
		for(int i=n-k+1;i<=n;++i)
			if(a[i]==a[i-k]) ans++;//首尾配对 
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：生灵灭 (赞：0)

 ### 思路 
其实挺简单的。

一道贪心。先给数组排序，小的 ($n-2k$) 个数全部加到得分里，大的 $2k$ 个数首尾配对就行了。


 ### 代码 
 
 ```cpp
 #include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<vector>
#include<cstdio>
#include<stack>
#include<queue>
const int N=1e5+1;
const int inf=0x3f3f3f3f;
using namespace std;
int t,n,k,a[101];
int main(){
    cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i]; 
		sort(a+1,a+n+1);//排序。
		int ans=0;//ans统计得分。
		for(int i=1;i<=n-2*k;i++){
			ans+=a[i];//先把(n-2k)个数加到得分里。
		}
		for(int i=n-2*k+1;i<=n-k;i++){
			int t=i+k;//首尾配对。
			if(a[i]==a[t]){
			    ans++;	//相等就加一。
			}
			
		}
		cout<<ans<<endl;//输出得分。
	}    
	return 0;
}
 ```
 

---

## 作者：doctorliu (赞：0)

## 题目描述
给出一个含有 $n$ 个数字的数组，要求进行 $k$ 次操作，其中每次操作你可以：
- 选择两个数 $a_1,a_2$ 并将它们删去
- 将 $\lfloor \frac{a_1}{a_2} \rfloor$ 加入答案中（向下取整）

求最小答案值。
## 解题思路
贪心法。经过观察可以发现，消除最大的 $2k$ 个数可以使答案最小，而且每次操作中如果选定两个不同的数，其最优结果应为 $0$ （想要结果最小显然我们应该用小数除以大数），若两数相同，结果为 $1$。

所以具体做法就是每次都选择不同的两个 $[n-2k+1,n]$ 区间内的数 $a_1,a_2$ 消除即可，如果已经无法找到不相同的 $a_1,a_2$，则令 $ans+1$，最后把 $[1,n-2k]$ 的数加上即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110];
int main()
{
	int t; scanf("%d",&t);
	while(t--)
	{
		int n,k,ans=0; scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		int pos=n,fp;
		for(int i=1;i<=k;i++)
		{
			while(!a[pos]) pos--;
			for(int j=pos;j>n-2*k;j--)
			if(a[j]!=a[pos]) {a[j]=a[pos]=0;break;}
			if(a[pos]){ans+=k;break;}
		}
		for(int i=1;i<=n-2*k;i++) ans+=a[i];
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：InversionShadow (赞：0)

显然对 $a$ 排序从小到大。

贪心地思考，最后要把 $n-2k$ 个数加入答案，那么就要让这 $n-2k$ 个数最小。

所以现在问题变成了：后 $2k$ 个数互相除，前 $n-2k$ 个直接加。

那么怎么让 $2k$ 个数相除后结果最小呢？

两个数做操作的贡献是 $\left\lfloor\dfrac{a_i}{a_j}\right\rfloor$，那么让他最小，尽量满足 $a_i\le a_j$。

还是考虑贪心，让 $a_i$ 除以 $a_{i+k}$ 向下取整。如样例 $3$：`1 3 3 7`，这个时候不能将 $1$ 除以 $7$ 加上 $3$ 除以 $3$，而是让 $1$ 除以 $3$ 加上 $3$ 除以 $7$。如果按照最小的除以最大的可能会出现两个数相等的情况，这样答案就会偏大，而让 $a_i$ 除以 $a_{i+k}$ 则尽量减少了两个数相等的情况，所以显然优。

当然**具体的严谨的**证明我不会证，如有需要，请参考其他大佬的题解 /bx。

```cpp
void solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1, cmp);
  sum= 0;
  for (int i = n; i > k * 2; i--) {
    sum += a[i];
  }
  for (int i = 1, l = 1, r = k + 1; i <= k; i++, l++, r++) {
    sum += a[r] / a[l];
  }
  cout << sum << endl;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑贪心。

将整个数组按照大小从小到大排序。并将第 $1$ 到 $k$ 个数作为除数，将第 $k+1$ 到 $2k$ 作为被除数，按照位置一一对应。

如果您学过排序不等式，那么接下来的贪心的证明都是易证。

---
如果将后面的某一个数和除数调换，那么操作结果和保留下来的数的结果都不减，这是显然的。

---

如果将后面的某一个数和被除数调换。这里设 $x$ 为被除数，$y$ 为被调换的数，$q$ 为除数，有 $x>y$，否则两者相等调换没有意义。

则原来的结果为：$\dfrac{x}{q}+y$。

后来为：$\dfrac{y}{q}+x$。

两式相除，得到：$\dfrac{x+qy}{qx+y}$。

由于 $x<y$，则当 $q=1$ 时 $\dfrac{x+qy}{qx+y}=1$，两式相等。

否则 $\dfrac{x+qy}{qx+y}<1$，前者，也就是 $\dfrac{x}{q}+y$ 较小。

---
最后是按顺序一一对应，这个的推导和上面差不多，这里就简单写一下。

$x$ 和 $y$ 为被除数,$q$ 和 $p$ 为除数，有 $x>y$ 和 $q>p$，否则其中任意两者相等调换没有意义。

原来为：$\dfrac{x}{q}+\dfrac{y}{p}$，后来为：$\dfrac{y}{p}+\dfrac{x}{q}$。

相除得到：$\dfrac{px+qy}{qx+py}$，根据之前的条件，得到该式比 $1$ 小，推出前者较小。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,k,a[105],ans;
bool cmd(int a,int b){
	return a>b;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);ans=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		sort(a+1,a+n+1,cmd);
		for(int i=1;i<=k;i++){
			ans+=a[i+k]/a[i];
		}
		for(int i=2*k+1;i<=n;i++){
			ans+=a[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：tmp_get_zip_diff (赞：0)

首先我们的 $\lfloor \frac{a_i}{a_j} \rfloor$ 不是 $0$ 就是 $1$，因此我们要让其他的 $n-2k$ 个数尽量小，所以我们先排序再取出前 $n-2k$ 个，接下来考虑剩下的：

- 剩下的贪心策略为：不断地选 $\lfloor \frac{a_i}{a_{i+k}} \rfloor$；
- 证明：处理只可能是 $0$ 或 $1$，那么 $1$ 的情况只可能靠前，即如果组成有 $1$，只可能 $a_{n-2k+1}$ 的出现超过一半，由于排过序，那么剩下的不是 $a_{n-2k+1}$ 的都会贡献为 $0$，这种情况后面的几个会为 $0$，否则没有一种出现过一半，那么对于任意一个 $i$，都有 $a_i <a_{i+k}$，那么每个都会被算成 $0$，证毕。

代码就很好写了：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5+5;
int n,k,a[N];

void Work()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=1;i<=n-2*k;i++)
		ans+=a[i];
	for(int i=n-2*k+1;i+k<=n;i++)
		ans+=(int)(a[i]/a[i+k]);
	cout<<ans<<"\n";
	return ;
}

signed main()
{
	int T;
	cin>>T;
	while(T--)
		Work();
	return 0;
}
```

---

