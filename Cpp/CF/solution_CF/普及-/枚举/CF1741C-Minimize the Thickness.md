# Minimize the Thickness

## 题目描述

给你一个长度为 $n$ 的数组 $a$，第 $i$ 个元素为 $a_i$。我们可以将 $a$ 分为若干个连续的不为空的子段，但前提条件是每个元素都要在一个子段里，且每个子段里的元素和都必须相等。

例如，我们有一个长度为 $6$ 的数组 $[55,45,30,30,40,100]$，如果我们把这个数组分为 $[55,45]$、$[30,30,40]$ 和 $[100]$ 三个子段的话，那么每个子段里的元素和都为 $100$。

定义若干个子段的厚度为这些子段里元素最多的子段里的元素个数，你的目标就是给定一个长度为 $n$ 的数组，找到一种分割子段的方法，使得分割后所有子段的厚度最小。

## 样例 #1

### 输入

```
4
6
55 45 30 30 40 100
4
10 23 7 13
5
10 55 35 30 65
6
4 1 1 1 1 4```

### 输出

```
3
4
2
3```

# 题解

## 作者：fqEason (赞：5)

### 题意

给定一个序列，把这个序列分成多段，使每段之和相等，求最大段长度的最小值。

### 思路

注意到，$n$ 的数据范围是小于 $2000$，$t$ 小于 $100$，那么考虑一种 $\mathcal O(n^{2}t)$ 的暴力算法： 枚举第一段的长度， 将第一段的和作为基准，判断若以这种基准为每段之和是否可行。取每种可行方案下最大子段长度的最小值。
## Code
```cpp 
#include <bits/stdc++.h>
using namespace std;
int t;
int n;
long long a[2001],b[2001];
int main() {
	cin >> t;
	while(t--) {
		memset(b,0,sizeof(b));
		memset(a,0,sizeof(a));//数组初始化 
		cin >> n;
		for (int i=1; i<=n; i++) cin >> a[i],b[i]=a[i]+b[i-1];//b数组维护前缀和 
		int ans=0x3f3f3f3f; 
		for (int i=1; i<=n; i++) {
			int maxn=i,cnt=0;//统计以前i个数之和为每个段的和的方案下，最大段的长度，maxn是这种方案下最大子段长度，cnt记录当前子段长度 
			long long sum=0;
			for (int j=i+1; j<=n; j++) {//从第i+1个数开始统计，最大段的长度 
				sum+=a[j];
				cnt++;
				if (sum==b[i]) sum=0,maxn=max(maxn,cnt),cnt=0;
				else if (sum>b[i]) {
					sum=-1;
					break;
				}//若此方案不行，则跳出 
			}
			if (sum<b[i]&&sum!=0) continue;//特判第i个数之后全部数之和仍小于前i个数之和情况 
			if (sum!=-1)
				ans=min(maxn,ans);
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：aimcf (赞：3)

$\color{white}{\text{这道题都卡了一个小时，lxy真的越来越菜的咩}}$

结论题。

结论：如果和为 $s$ 的一段区间是满足条件的，且序列的和为 $e$ 的时候，那么一定有 $e\bmod s = 0$，并且 $s$ 一定是 $a$ 序列的某一个前缀。

证明：如果 $e\bmod s \neq 0$，那么无法划分成多段和为 $s$ 的序列。如果 $s$ 不为 $a$ 序列的前缀，那么 $a_1$ 位置就无法被选择，不能划分成多端和为 $s$ 的前缀。

暴力枚举每一个前缀，判断是否符合条件即可。时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 10;
int a[N];

signed main()
{
  int T;
  cin >> T;
  while (T --)
  {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++)
      cin >> a[i];
    int sum = accumulate(a + 1, a + n + 1, 0);
    int qs = 0;
    int result = n;
    for (int i = 1; i <= n; i ++)
    {
      qs += a[i];
      if (sum % qs == 0)
      {
        bool flag = true;
        int qsc = 0;
        for (int j = i + 1; j <= n; j ++)
        {
          qsc += a[j];
          if (qsc == qs)
            qsc = 0;
          else if (qsc > qs)
          {
            flag = false;
            break;
          }
        }
        if (flag)
        {
          int longer = 0;
          int qsc = 0, cnt = 0;
          for (int j = 1; j <= n; j ++)
          {
            cnt ++;
            qsc += a[j];
            longer = max(longer, cnt);
            if (qsc == qs)
            {
              qsc = 0;
              cnt = 0;
            }
          }
          result = min(result, longer);
        }
      }
    }
    cout << result << '\n';
  }
}

```


---

## 作者：szhqwq (赞：3)

## 分析

此题我们采用模拟的手段。维护一个前缀和，枚举第一段的长度，再依次向后匹配，直至匹配成功，求每段长度的最大值，再在能够匹配成功的方案中取最大值的最小值即可。

代码时间复杂度为 $O(t n^2)$，并不会超时。

AC code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e3 + 10;

int n,res = INT_MAX;
int a[N];
int s[N];

signed main() {
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	int t;
	cin >> t;
	while (t --) {
		cin >> n;
		memset(s,0,sizeof s);
		for (int i = 1; i <= n; i ++ ) {
			cin >> a[i];
			s[i] = s[i - 1] + a[i];
		}
		res = INT_MAX;
		for (int i = 1; i <= n; i ++ ) {
			int L = i,len = 0,cnt = 0;
			bool flag = false;
			for (int j = i + 1; j <= n; j ++ ) {
				len ++;
				cnt += a[j];
				if (cnt == s[i]) {
					L = max(L,len);
					len = 0;
					cnt = 0;
				} else if (cnt > s[i]) {
					flag = true;
					break;
				}
			}
			if (cnt && cnt < s[i]) continue;
			if (!flag) res = min(res,L);
		}
		cout << res << endl;
	}
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题其实就是暴力，首先你要保证是 $a$ 的子串，那么我们就会发现其实第一个串一定从 $1$ 开始，那么我们就统计出 $1\sim i$ 的和再往后面看是否满足即可（记录下厚度），最后若合法判断答案是否更新。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,res=INT_MAX;
int a[2010];
int main(){
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		s=0;
		for(int i=1;i<=n;i++) {
			s+=a[i];// 求和
			int sum=0,cnt=0,l=i+1; //sum存厚度，l存上一个串的尾下标好计算厚度
			bool f=0;
			for(int j=i+1;j<=n;j++) {
				sum+=a[j];
				if(sum>s) {// 不满足
					f=1;
					break;
				}
				if(sum==s) {
					cnt=max(cnt,j-l+1);// 找下一个串
					sum=0;
					l=j+1;
					continue;
				}
			}
			if(!f&&l==n+1) res=min(max(cnt,i),res); // 判断是否满足并更新答案
		}
		cout<<res<<endl;
		res=INT_MAX;
	}
	return false;
}
```


---

## 作者：qwq___qaq (赞：1)

### 前言

为什么我对二分如此执着?在连续两场的 CF 的 C 都用了比正解复杂的二分。（好像本题还比标准复杂度更劣？

### 正文

看见本题与求和有关，于是考虑前缀和维护区间和。

然后我们可以枚举一个 $i$ 用来固定区间元素的和：$\sum\limits_{t=1}^ia_t=s_i$.注意到对于同一个和，如果长度 $len$ 可行，那么对于 $len'>len$，也一定是可行的。

于是考虑二分，考虑 `check` 函数：固定了所有元素的和 $s$，对于左端点 $l$，我们在区间长度 $\le len$ 并且右端点 $\le n$ 时，如果存在 $a_{l+t-1}-a_{l-1}=s$，那么 $l\gets l+t$，查询下一个区间，如果 $l>n$ 那么 $len$ 就可行，如果中途某一次没有找到合适的 $t$ 就是不可行的。

时间复杂度 $O(n^2\log n)$，空间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[2005];
inline bool check(int x,int s){
	int t=1;
	while(t<=n){
		bool p=1;
		for(int i=1;i<=x&&t+i-1<=n;++i)
			if(a[t+i-1]-a[t-1]==s){
				t+=i;
				p=0;
				break;
			}
		if(p)
			return 0;
	}
	return 1;
}
int main(){
	cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			a[i]+=a[i-1];
		}
		int ans=n;
		for(int i=1;i<=n;++i){
			int l=i,r=n;
			while(l<r){
				int mid=l+r>>1;
				if(check(mid,a[i]))
					r=mid;
				else
					l=mid+1;
			}
			ans=min(ans,r);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：asasas (赞：1)

赛时 $40\text{min}$ 时切了这题不过吃了发罚时还是太菜了/dk 

## 题目大意：


给定一个序列，要求将这个序列划分成不同的子段，**每段的和相等**，现定义**厚度**为:**某个序列划分的方案中，子段长度的最大值**，求所有厚度中的**最小值**。若无划分方案，则输出 $-1$。

一开始看到题目可能会想到二分答案（最大值最小嘛）。可是再仔细看看题目给的数据范围：

$n\le 2\times 10^3$。

所以暴力 $n^2$ 即可，跑得飞快。

具体做法见代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define r register
#define int long long
int a[200005];
signed main(){
    int t;
    cin >> t;
    while(t--){
    	int n;
    	cin >> n;
    	for (register int i=1;i<=n;i++) cin >> a[i];
    	int ans=1e9,sum=0;
    	for (register int i=1;i<=n;i++){
    		sum+=a[i];//枚举i,将前i个数的总和算出来
    		int now=0,ok=0,len=i,l=0;//ok标记，now每段的和，len是厚度，l是每段的长度 
            
            //注意！一开始len要等于i否则你就会吃一发罚时/dk
    		for (register int j=i+1;j<=n;j++){
    			l++;//每段长度累加
    			if (now+a[j]==sum) now=0,len=max(len,l),l=0;//可以划分一段，就重新开始
				else if (now+a[j]<sum) now+=a[j];//可以加就加
    			else if (now+a[j]>sum){//拼不到sum，直接退出
    				ok=1;
    				break;
    			}
    		}
    		if (now==sum) now=0,len=max(len,l);//出来还要特判一下now
    		if (ok==0&&now==0) ans=min(ans,len);
    	}
    	if (ans==1e9) cout << n << endl;
		else cout << ans << endl;//输出，ans若为最大值即无解
    }
    return 0;
}
```


---

## 作者：YH_Eternally (赞：1)

## 题意
给你一个长度为 $n$ 的数组 $a$，将 $a$ 分为若干个连续的不为空的子段，但前提条件是每个元素都要在一个子段里，且每个子段里的元素和都必须相等。

每个子段的厚度为这些子段里元素最多的子段里的元素个数，找到一种分割子段的方法，使得分割后所有子段的厚度最小。

## 思路
递归搜索第一部分的长度。

由于每个元素只能属于一个段，所以找到第一段的和后，我们实际上也找到了所有其他部分的和。

然后就可以枚举其他子段。当找到一个比原来的答案大的值时，更新答案。第一个答案初始化为 $n$。

## 代码
``` cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, a[2005], ans;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = 0;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return f ? x : -x;
}

inline int dfs(int now, int s) {//搜索第一段的长度
	if(now == n) return 0;//递归边界
	int ct = 0;
	for(int i = now + 1; i <= n; i ++) {
		ct += a[i - 1];
		if(ct > s) return n;//递归边界
		if(s == ct) return max(i - now, dfs(i, s));
	}
	return n;
}

int main() {
	t = read();
	while(t --) {
		n = read();
		for(int i = 0; i < n; i ++) a[i] = read();
		ans = n;//答案初始化
		int s = 0;
		for(int i = 1; i < n; i ++) {
			s += a[i - 1];
			ans = min(ans, dfs(0, s));//尝试更新答案
		}
		printf("%d\n", ans);
	}
    return 0;
}
```

---

## 作者：Symbolize (赞：0)

# 思路
如果能够分段，那么每段的值一定是原数组所有数的和的因数。

所以用变量 $sum$ 记录所有数的和，在暴力枚举因数。

那么循环内的判断显然就是下标从 $1$ 到 $n$ 用一个变量挨个累加如果当前和与目前所枚举的 $sum$ 的因数相同，清空累加数组，直至全部累加完，判断是否刚好分完。若中间累加函数大于了目前枚举的 $sum$ 的因数，说明一定不行了，枚举下一个因数。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
using namespace std;
int t,n,sum,a[N];
int solve(int x)
{
	int sum=0,l=0,res=LONG_LONG_MIN;  
	rep1(i,1,n)
	{
		sum+=a[i];
		++l;  
		if(sum==x)
		{
			res=max(res,l); 
			l=sum=0; 
		}
		else if(sum>x) return 0; 
	}
	return res;
}
void getans()
{	
	cin>>n;
	sum=0;
	rep1(i,1,n)
	{
		cin>>a[i]; 
		sum+=a[i];//累加和
	}
	int ans=LONG_LONG_MAX;
	rep1(i,1,sqrt(sum))//素筛
	{
		if(sum%i==0)//是否为因数
		{//因为是素筛，所以有两个因数，i与sum/i 
			int res=solve(i);//判断第一个因数
			if(res) ans=min(res,ans); //取最小值 
			res=solve(sum/i);//判断第二个因数
			if(res) ans=min(res,ans); //取最小值 
		}
	}
	cout<<ans<<endl;//输出 
	return;
}
signed main()
{
// 	freopen("C.in","r",stdin);
// 	freopen("C.out","w",stdout); 
	cin>>t;
	while(t--) getans();//循环要答案
	return 0;
}
```

---

## 作者：As_Snow (赞：0)

### 思路
看这数据范围（$n\le 2000,t\le 100$），很容易想出暴力的思路。

我们去枚举第一段的长度，求出第一段的和，再以此为基准去看方案是否可行，然后对于每一个可行的方案，去找到一个最小的最大字段和。

### Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e3+23;
const int inf = 1e9+7;
int T,n,ans,a[N];
bool ok;
void solve(){
	cin>>n;ans=inf;
	for(int i=1;i<=n;i++)
		cin>>a[i],a[i]+=a[i-1];
	for(int l=1,cnt;l<=n&&l<ans;l++){
		ok=1,cnt=l;
		int i,j;
		for(i=l+1,j=l;i<=n&&ok;i++){
			if(a[i]-a[j]>a[l])ok=0;
			if(a[i]-a[j]==a[l])cnt=max(cnt,i-j),j=i;
		}
		if(j!=n&&a[n]-a[j]!=a[l])ok=0;
		if(ok)ans=min(ans,cnt);
	}
	cout<<ans<<endl;
}
signed main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：smallpeter (赞：0)

div3的c还是挺水滴，题目翻译非常简洁明了，可以直接去看。

# 解题思路

本人在考场上只想出来一种解法，另一种解法是在比赛结束后想出来的（本质上没啥区别）

## 1、枚举前缀

不难发现第一段的左端点一定为 1，那么我们就可以枚举第一段的长度，也就是枚举前缀。注意到 $a_i\ge1$，也就是说确定了每个区间的和以后划分方式是唯一的（这也是第二种解法的基础）。 

## 2、枚举区间和

第二种思路是枚举区间的和，原理跟上一种做法差不多就不再啰嗦。

# 代码

第一种枚举前缀的思路的代码

```
#include<bits/stdc++.h>
using namespace std;
 
#define LL long long
 
const LL N=2e3+10,INF=1e9;
 
LL t,n,a[N];
 
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(LL i=1;i<=n;i++) scanf("%lld",&a[i]);
		LL sum=0,anss=INF;
		for(LL i=1;i<=n;i++){
			sum+=a[i];
			bool bl=true;
			LL sumx=0,sz=0,ans=i;
			for(LL j=i+1;j<=n;j++){
				sumx+=a[j];
				sz++;
				if(sumx>sum){
					bl=false;
					break;
				}
				if(sumx==sum){
					sumx=0;
					ans=max(ans,sz);
					sz=0;
				}
				if(j==n&&sumx!=0){
					bl=false;
				}
			}
			if(bl==true){
				anss=min(anss,ans);
			}
		}
		printf("%lld\n",anss);
	}
}
```


------------

第二种枚举区间和的代码

```
#include<bits/stdc++.h>
using namespace std;
 
#define LL long long
 
const LL N=2e3+10,INF=1e9;
 
LL t,n,a[N];
 
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(LL i=1;i<=n;i++) scanf("%lld",&a[i]);
		LL sum=0;
		for(LL i=1;i<=n;i++) sum+=a[i];
		LL ans=INF;
		for(LL i=1;i<=n;i++){
			if(sum%i!=0) continue;
			LL x=sum/i;
			LL sumx=0,xx=0,anss=0;
			bool bl=true;
			for(LL i=1;i<=n;i++){
				sumx+=a[i];
				xx++;
				if(sumx==x){
					anss=max(anss,xx);
					xx=0;
					sumx=0;
				}
				if(sumx>x){
					bl=false;
					break;
				}
			}
			if(bl==true) ans=min(ans,anss);
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：TammyZhao (赞：0)

# 题解

- 难度大概黄。

- 看似是一道 dp 题，实际上看看数据范围就知道可以采取比较暴力的做法。

- 考虑枚举第一段的长度，然后判断后面的数是否能组成合法的划分情况，最后去个 $\max$ 即可。

- 因为 $\sum n\leq 2000$，所以 $O(Tn^2)$ 可过。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n, a[2005];

int main()
{
	cin >> T;
	while (T --)
	{
		cin >> n;
		for (int i = 1 ; i <= n ; i ++)
		{
			cin >> a[i];
		}
		int sum = 0, Ans = INT_MAX;
		for (int i = 1 ; i <= n ; i ++)
		{
			sum += a[i];
			int cnt = 0, ans = i, last = i;
			for (int j = i + 1 ; j <= n ; j ++)
			{
				cnt += a[j];
				if (cnt == sum)
				{
					ans = max(ans, j - last);
					last = j;
					cnt = 0;
				}
			}
			if (!cnt)
			{
				Ans = min(Ans, ans);
			}
		}
		cout << Ans << endl;
	}
	return 0;
}
```


---

## 作者：LiaoYF (赞：0)

## 题意
把一个数组分成和相等的几段，要求最长的一段长度最短。
## 做法
直接**暴力**枚举分成几段。如果能分成 $i$ 段的话，那么全部元素的和 $sum$ 一定是整除 $i$ 的，不能整除的话就说明这种分法不行。并不存在无解的情况，因为最差就是所有元素分成 $1$ 分。
## Code
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[2005];
int main(){
    int t;
    cin>>t;
    while(t--){
        int anss=2000;//最小厚度
        int n;
        cin>>n;
        int sum=0;//所有元素的和
        for(int i=1;i<=n;i++){
            cin>>a[i];
            sum+=a[i];
        }
        for(int i=n;i>=1;i--){//枚举分成几份
            if(sum%i!=0){//不能整除
                continue;
            }
            int x=sum/i;//每份的大小
            int y=0,ans=0,cnt=0,flag=1;
            for(int i=1;i<=n;i++){
                y+=a[i];
                cnt++;
                //cout<<y<<" "<<cnt<<"\n";
                if(y==x){//已经分完一整份
                    y=0;
                    ans=max(ans,cnt);//当前的厚度
                    cnt=0;
                }else if(y>x){
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                //cout<<i<<" "<<ans<<"\n";
                anss=min(anss,ans);
            }
        }
        cout<<anss<<"\n";
    }
    return 0;
}
```
[record](https://codeforces.com/contest/1741/submission/176948058)

---

## 作者：zfx_VeXl6 (赞：0)

考虑暴力枚举。

枚举第一段的长度，如果把第一段的和做为每段的和可行，就更新答案。

代码如下（思路都在代码里）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int t, n, as;
ll a[2001], k; //k表示a数组中前i个数的和，即枚举到的每段的和
int main()
{
    cin >> t;
    while (t--)
    {
        k = 0;
        as = INF; //多组数据初始化
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
        {
            k += a[i];
            ll sm = 0; //sm(sum)表示当前段的累加和
            int ct = 0, mx = i; //ct(count)为当前段的长度；mx(max)为每段的最大长度，开始时为i
            for (int j = i + 1; j <= n; j++)
            {
                sm += a[j];
                ct++;
                if (sm > k) //若以k为每段和不行就退出
                {
                    mx = -1;
                    break;
                }
                if (sm == k) //若可以，更新以k为每段和时每段长度的最大值
                {
                    mx = max(mx, ct);
                    ct = 0;
                    sm = 0;
                }
            }
            if (!((sm && sm < k) || mx == -1)) //特判最后一段及以k为每段和不行的情况，统计答案
                as = min(as, mx);
        }
        cout << as << '\n';
    }
    return 0;
}
```

---

## 作者：ImposterAnYu (赞：0)

# 解析
因为每个子段都要求是连续的，所以我们可以直接枚举第一个子段的长度。先计算出第一个子段的元素和，接下来每找到一个元素，就将其加入当前子段中。如果当前子段的元素和刚好是第一个子段的元素和的话，就可以新增一个空的子段，这样剩下的元素就不会被丢到前面的子段里去了。

但是……如果当前子段的元素和超过了第一个子段的元素和呢？很简单，因为我们必须严格保证所有的子段的元素和都相等，所以很明显，这种情况是不合法的，应该直接 `break`，舍弃掉这种情况。

最后扯句废话：不可能出现数据无解的情况，因为在最坏情况下可以直接将整个数组分为一个字段，此时你的答案为 $n$（（（
# AC code
```c++
#include<bits/stdc++.h>
#define int1 int
#define N 2005
using namespace std;
int1 t,n,i,j,ans,s,d,w,k,a[N];
int1 read(){
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
	t = read();
	while(t--){
		n = read();
		for(i = 1; i <= n; i++){
			a[i] = read();
		}
		ans = 114514,d = 0;//ans 为最小的厚度，d 为第 1 个子段的元素和
		for(i = 1; i <= n; i++){
			w = s = 0,d += a[i],k = 0;//w 为当前子段的元素和，s 为当前分法的厚度，k 为上一个子段的最后一个元素的下标
			for(j = 1; j <= n; j++){
				if(w + a[j] <= d){//如果把新元素加进来时元素和还没超过第 1 个子段的元素和
					w += a[j];
					if(w == d){//如果刚好达到
						w = 0,s = max(s,j - k),k = j;//元素和清 0，统计厚度
					}
				}else{//否则可以直接退出了（因为在这种情况下一定分不下去）
					break;
				}
			}
			if(k == n){//如果刚好分完，
				ans = min(ans,s);//就统计答案
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

