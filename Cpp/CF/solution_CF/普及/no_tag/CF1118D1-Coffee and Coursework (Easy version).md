# Coffee and Coursework (Easy version)

## 题目描述

The only difference between easy and hard versions is the constraints.

Polycarp has to write a coursework. The coursework consists of $ m $ pages.

Polycarp also has $ n $ cups of coffee. The coffee in the $ i $ -th cup has $ a_i $ caffeine in it. Polycarp can drink some cups of coffee (each one no more than once). He can drink cups in any order. Polycarp drinks each cup instantly and completely (i.e. he cannot split any cup into several days).

Surely, courseworks are not usually being written in a single day (in a perfect world of Berland, at least). Some of them require multiple days of hard work.

Let's consider some day of Polycarp's work. Consider Polycarp drinks $ k $ cups of coffee during this day and caffeine dosages of cups Polycarp drink during this day are $ a_{i_1}, a_{i_2}, \dots, a_{i_k} $ . Then the first cup he drinks gives him energy to write $ a_{i_1} $ pages of coursework, the second cup gives him energy to write $ max(0, a_{i_2} - 1) $ pages, the third cup gives him energy to write $ max(0, a_{i_3} - 2) $ pages, ..., the $ k $ -th cup gives him energy to write $ max(0, a_{i_k} - k + 1) $ pages.

If Polycarp doesn't drink coffee during some day, he cannot write coursework at all that day.

Polycarp has to finish his coursework as soon as possible (spend the minimum number of days to do it). Your task is to find out this number of days or say that it is impossible.

## 说明/提示

In the first example Polycarp can drink fourth cup during first day (and write $ 1 $ page), first and second cups during second day (and write $ 2 + (3 - 1) = 4 $ pages), fifth cup during the third day (and write $ 2 $ pages) and third cup during the fourth day (and write $ 1 $ page) so the answer is $ 4 $ . It is obvious that there is no way to write the coursework in three or less days in this test.

In the second example Polycarp can drink third, fourth and second cups during first day (and write $ 4 + (2 - 1) + (3 - 2) = 6 $ pages) and sixth cup during second day (and write $ 4 $ pages) so the answer is $ 2 $ . It is obvious that Polycarp cannot write the whole coursework in one day in this test.

In the third example Polycarp can drink all cups of coffee during first day and write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) + (5 - 4) = 15 $ pages of coursework.

In the fourth example Polycarp cannot drink all cups during first day and should drink one of them during the second day. So during first day he will write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) = 14 $ pages of coursework and during second day he will write $ 5 $ pages of coursework. This is enough to complete it.

In the fifth example Polycarp cannot write the whole coursework at all, even if he will drink one cup of coffee during each day, so the answer is -1.

## 样例 #1

### 输入

```
5 8
2 3 1 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 10
1 3 4 2 1 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 15
5 5 5 5 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
5 16
5 5 5 5 5
```

### 输出

```
2
```

## 样例 #5

### 输入

```
5 26
5 5 5 5 5
```

### 输出

```
-1
```

# 题解

## 作者：yaaaaaan (赞：0)

### 思路

首先观察这道题，答案明显具有二分的特性，所以我们可以用二分来做。

首先给数组从大到小排序，先判 -1 的情况，当每天喝一杯咖啡都肝不完作业，就永远写不完。

然后二分答案，每次对于一个天数 $x$，安排最小值在后，最大值在前，尽量消耗最小值，计算总共的能量，如果能量大于等于 $m$，保存答案，继续寻找有没有更小的答案，否则就往后面寻找更大的答案。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,m,sum,ans;
int a[200001];
bool cmp(int x,int y)
{
	return x>y;
}
bool check(int x)
{
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cnt+=max(a[i]-1LL*ceil(1.0*i/x)+1,1.0*0);
	}
	return cnt>=m;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	sort(a+1,a+n+1,cmp);
	if(sum<m) cout<<-1<<"\n";
	else
	{
		int l=1,r=n;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid)) 
			{
				r=mid-1;
				ans=mid;
			}
			else 
			{
				l=mid+1;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 由于答案具有单调性，所以考虑用二分答案。
- 所以我们可以将数组进行降序排列，**先判断从大到小喝能否完成**，若不能就输出 -1。
- 对于每个 $mid$，**我们尽量先喝效果大的**，这样可以让效果得到最大化。如果发现能量大于等于了 $sum$ 则让右边界 $R=mid$，否则让左边界 $L=mid$。

### 代码：
```
#include<bits/stdc++.h>

using namespace std;

const int N=2*10e5+100;

int n,m,a[N];
int L,R,mid,sum;
bool check(){
	sum=0;
//	cout<<"------------------\nmid="<<mid<<"\n";
	for(int i=1;i<=n;i++){
//		cout<<a[i]<<" "<<i/mid-1<<"=======\n";
		sum+=max(0ll*1.0,a[i]-ceil(1.0*i/mid)+1);
//		cout<<"i="<<i<<"   "<<"sum="<<sum<<"\n";
		if(sum>=m){
			return true;
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(sum<m){
		cout<<"-1\n";
		return 0;
	}
	sort(a+1,a+n+1,greater<int>());
	L=1,R=n;
	while(L<R){
		mid=(L+R)/2;
		if(check()){
			R=mid;
		}
		else{
			L=mid+1;
		}
	}
	cout<<R;
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

简单贪心。

数据范围，$n \le 100$，那么考虑暴力的写法。$O(n^2)$ 的算法，思路是枚举天数，每天都给它加上能量，这样一直做。如果当前做的任务数超过了 $m$，那么就直接输出。若是做完了，这个任务数还未超过 $m$，那么就说明不能完成任务，输出 $-1$。

那么该怎么贪心？

我们可以从大到小排序，因为权值大的咖啡先喝肯定是优于先喝权值小的咖啡的。每次做的时候用个变量累加一下就行了。

**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
int a[1000100];
bool cmp(int x, int y) {return x > y;}
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i ++)
	{
		int xx = 0, yy = 0, zz = 0;
		for(int j = 1;j <= n; j ++)
		{
			zz ++;
			yy += max(a[j] - xx, 0);
			if(zz >= i) zz = 0, xx ++;
		}
		
		if(yy >= m) {cout << i; return 0;}
	}
	cout << -1;
	return 0;
}
```

---

## 作者：信息学carryHarry (赞：0)


### 策略1：
$O(n^2)$ 暴力枚举天数，显然超时。
### 策略2：
先从大到小将权值排序，再二分完成任务的天数（当前 $mid$ 是否能完成 $m$ 个任务），最后若没有可行的 $mid$，就输出 $-1$，时间复杂度 $O(n \log n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=2e5+5;
int n,a[M],k,ans=1e9,m;
bool check(int x)//二分天数
{
	int i=0,j=0,k=0;
	for(int s=1;s<=n;s++){
		k++;
		j+=max(a[s]-i,(long long)0);
		if(k>=x){
			i++;
			k=0;
			
		}
	}
	return j>=m;
}

bool cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		k+=a[i];
	}
	sort(a+1,a+1+n,cmp);
	int lt=1,rt=n;
	while(lt<=rt){
		int mid=(lt+rt)/2;
		if(check(mid)){
			rt=mid-1;
			ans=mid;
		}
		else
			lt=mid+1;
	}
	if(ans==1e9)//是否有解
		cout<<-1;
	else
		cout<<ans;
	return 0;
}

```


---

## 作者：Helium_Ship (赞：0)

有个很显然的贪心，对于大的 $a_i$ 我们需要优先喝，因为当小的 $a_i$ 减至 $\le0$ 时，就不会使答案更劣，而我们这个贪心跟最终的答案有关，所以我们可以考虑直接二分答案，再使用贪心 $O(n)$ 判是否可行，总时间复杂度为 $O(n\log(n))$。

提示：二分里写的 $l<r$ 最后还需判那个长度为 $1$ 的区间。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200010];
bool ansflag;
inline bool check(int x){
	int ans=0,cnt=0,tmp=1;
	bool flag=1;
	while (ans<m&&flag){
		for (int i=1;i<=x;i++){
			ans+=a[tmp]-cnt,tmp++;
			if (a[tmp]-cnt<=0||tmp>n){
				flag=0;
				break;
			}
		}
		cnt++;
	}
	return ans>=m;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ansflag=1;
	cin>>n>>m;
	for (int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,greater<int>());
	int l=1,r=n;
	while (l<r){
		int mid=(l+r)/2;
		if (check(mid)){
			ansflag=0;
			r=mid;
		}
		else l=mid+1;
	}
	if (ansflag&&!check(r))cout<<"-1";
	else cout<<r;
	return 0;
}
```

---

## 作者：櫻尘ིོི༹ (赞：0)

**Part 1 思路**

有题目可以推得，每天喝下的第 $n$ 杯咖啡会加速任务 $\max(0,a_i-n+1)$，又因为每天可以喝任意多杯咖啡，所以在   $a_i\leq n-1$ 时，对任务没有任何加速。

所以我们需要尽可能多的让每天喝的咖啡加速更多，同时每一杯咖啡都存在一个损失，但这个损失是由每天喝的顺序而定的。由此，我们可以知道，我们所要做的事情就是让加速越多的咖啡所产生的损失越少。

**Part 2 过程**

首先，将每一杯咖啡的加速排序，从大到小。

接着，二分答案天数。

最后，查看总加速是否超过作业总数。

**Part 3 Code**
 ```cpp
#include <bits/stdc++.h>
#define MAXN 200005
#define int long long
using namespace std;
int n,m;
int sum;
int s[MAXN];
int cmp(int a,int b){
	return a>b;
}
inline bool check(int x){
	int num=1,num1=0;
	int nsum=sum;
	while(num<=n){
		if(num+x-1<=n){
			if(s[num+x-1]>=num1){
				nsum-=num1*x;
				num+=x;
				num1++;
			}else{
				int i;
				for(i=num;i<=num+x-1;i++){
					if(s[i]>num1)nsum-=num1;
					else break;
				}
				for(;i<=n;i++)nsum-=s[i];
				break;
			}
		}else{
			if(s[n]>=num1){
				nsum-=(n-num+1)*num1;
				num=n;
			}else{
				int i;
				for(i=num;i<=n;i++){
					if(s[i]>num1)nsum-=num1;
					else break;
				}
				for(;i<=n;i++)nsum-=s[i];
			}
			break;
		}
	}
	if(nsum>=m)return true;
	return false;
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		sum+=s[i];
	}
	sort(s+1,s+n+1,cmp);
	if(sum<m){
		puts("-1");
		return 0;
	}
	int l=1,r=n,ans=0;;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```





---

## 作者：EDqwq (赞：0)

这题居然还没有题解，那我来一篇。

显然，我们可以枚举天数，对于一个天数，我们把这些能量按大小，一个一个分配给每一天，这样造成的“损失”是最小的，如果所有都跑完了，仍然没有大于 $m$ ，那么显然无解。

具体就是，排序原数组，对于一个天数，把最大的那几个分配给不减的，小一点的分配给减一，以此类推。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n,m;
int a[1000010];
int all;

bool cmp(int x,int y){
	return x > y;
}

signed main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i ++)a[i] = read(),all += a[i];
	sort(a + 1,a + n + 1,cmp);
	for(int i = 1;i <= n;i ++){
		int le = 0;
		int now = 0;
		int num = 0;
		for(int j = 1;j <= n;j ++){
			num ++;
			now += max(a[j] - le,0ll);
			if(num >= i)num = 0,le ++;
		}
		if(now >= m){
			cout<<i;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

---

