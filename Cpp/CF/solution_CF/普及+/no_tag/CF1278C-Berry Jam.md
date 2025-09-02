# Berry Jam

## 题目描述

Karlsson has recently discovered a huge stock of berry jam jars in the basement of the house. More specifically, there were $ 2n $ jars of strawberry and blueberry jam.

All the $ 2n $ jars are arranged in a row. The stairs to the basement are exactly in the middle of that row. So when Karlsson enters the basement, he sees exactly $ n $ jars to his left and $ n $ jars to his right.

For example, the basement might look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278C/241a083326516b3b4ad70c41dd4440502bf9af7a.png)Being the starightforward man he is, he immediately starts eating the jam. In one minute he chooses to empty either the first non-empty jar to his left or the first non-empty jar to his right.

Finally, Karlsson decided that at the end the amount of full strawberry and blueberry jam jars should become the same.

For example, this might be the result:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1278C/ce4aac0a2c1a17ee1f9a579db06c727cd2163ca6.png)He has eaten $ 1 $ jar to his left and then $ 5 $ jars to his right. There remained exactly $ 3 $ full jars of both strawberry and blueberry jam.Jars are numbered from $ 1 $ to $ 2n $ from left to right, so Karlsson initially stands between jars $ n $ and $ n+1 $ .

What is the minimum number of jars Karlsson is required to empty so that an equal number of full strawberry and blueberry jam jars is left?

Your program should answer $ t $ independent test cases.

## 说明/提示

The picture from the statement describes the first test case.

In the second test case the number of strawberry and blueberry jam jars is already equal.

In the third test case Karlsson is required to eat all $ 6 $ jars so that there remain $ 0 $ jars of both jams.

In the fourth test case Karlsson can empty either the second and the third jars or the third and the fourth one. The both scenarios will leave $ 1 $ jar of both jams.

## 样例 #1

### 输入

```
4
6
1 1 1 2 2 1 2 1 2 1 1 2
2
1 2 1 2
3
1 1 1 1 1 1
2
2 1 1 1
```

### 输出

```
6
0
6
2
```

# 题解

## 作者：Wf_yjqd (赞：2)

思路很简单的一道题。

然后和同学 duel 调了半小时。

------------

考虑将两种果酱分别映射成 $1$ 和 $-1$。

若有一段区间和为 $0$，这段区间内两种果酱的个数就相同。

转换问题为最长的前缀与后缀，使得和为 $0$。

考虑求前 $n$ 个的前缀和，和后 $n$ 个的后缀和，用 map 记录其中一个，枚举另一个，维护答案即可。

复杂度 $\operatorname{O}(n\log{n})$。

------------

注意我这种写法需要特殊处理前缀和或后缀和为 $0$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,a[maxn],ans;
map<int,int> mp;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        mp.clear();
        for(int i=1;i<=n*2;i++){
            scanf("%d",&a[i]);
            a[i]=(a[i]==1?-1:1);
        }
        ans=n*2;
        for(int i=1;i<=n;i++){
            a[i]+=a[i-1];
            if(!a[i])
                ans=min(ans,n*2-i);
        }
        a[n*2+1]=0;
        for(int i=n*2;i>=n+1;i--){
            a[i]+=a[i+1];
            mp[a[i]]=i-n-1;
            if(!a[i])
                ans=min(ans,i-1);
            // printf("%d %d Sherry\n",i,a[i]);
        }
        for(int i=n;i>=1;i--)
            if(mp.find(-a[i])!=mp.end())
                ans=min(ans,mp[-a[i]]+n-i);
                // printf("%d %d %d\n",a[i],mp[-a[i]],n-i);
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：Dolphin_ (赞：1)

### 题意
从中间开始向两边删数，直到两边1和2的个数相等。

-------

### 思路
先处理前1~n，f[i]表示1和2两种物品差为i时左边**用**的**最多**个数。再循环后半段，用后面的个数加上后面的差所对应的前面的差去更新答案。这里如果不能理解的话看代码。

---
```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=100005;//防止数组越界
int T,f[220000],a[220000],x,n,ans,sum;
int main()
{
	
	scanf("%d",&T);
	while(T--)
	{
		memset(f,128,sizeof f);
		memset(a,0,sizeof a);
		n=0;x=0;sum=0;ans=0;
		scanf("%d",&n);f[P]=0;
		sum=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&x);
			if(x==2) x=-1;
			sum+=x;
			f[sum+P]=max(f[sum+P],i);
			if(sum==0) ans=max(ans,f[sum+P]);//这里很关键，如果不加会被只删右边的hack掉 
		}
		for(int i=1;i<=n;++i) {scanf("%d",&a[i]);if(a[i]==2) a[i]=-1;}
		sum=0;
		for(int i=n;i>=1;--i)
		{
			sum+=a[i];
			ans=max(n-i+1+f[-sum+P],ans);//f[-sum+P]表示的就是和sum对应的前半段的个数，再加上后半段的个数，去更新答案。
		}
		printf("%d\n",2*n-ans);//最后要求的是删掉多少个，用总数减一下。
	}
	return 0;
}

---

## 作者：wuyixiang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1278C)

题目大意：你一开始在第 $n$ 杯果酱与第 $n + 1$ 杯果酱的中间，现在可以往左或者往右吃果酱，问至少要吃掉多少瓶果酱才能使 $1$ 号满瓶果酱与 $2$ 号满瓶果酱数量相等。

分析：很简单，~~于是一不小心就打了只有一点长的的差点超时的代码~~

因为题目是支持 $\mathcal{O}(n)$ 操作的，所以我们可以直接先遍历左边的，计算右边还需要的 $1$ 比 $2$ 多的个数（可能为负数）。这里再一个一个枚举就会超时，所以我们可以用前缀和优化，先进行预处理并用桶记录，访问时直接跳转即可。

注意：因为有可能为负数，所以需要进行下标偏移（另外，数组长度是两倍的 $n$ 的长度，所以只开 $10^5$ 的数组大小会得到一个因为越界而挂分的好成绩）。

### AC Code:

```cpp
#include <iostream>
#include <cstring>
#define int long long
using namespace std;
int n,a[300005],t,b[300005],c[800005],d[300005];
signed main()
{
    cin >> t;
    while(t --)
    {
        cin >> n;
        int fk = 0,fl = 0,sum = 0,ans = 1e9;
        memset(c,0x3f,sizeof(c));
        memset(b,0,sizeof(b));
        memset(d,0,sizeof(d));
        for(int i = 1;i <= 2 * n;i ++)cin >> a[i],sum += (a[i] == 1);
        sum = sum - (2 * n - sum);//计算初始1比2多的个数
        for(int i = n;i >= 1;i --)
        {
            if(a[i] == 1)b[i] = b[i + 1] + 1;
            else b[i] = b[i + 1] - 1;//前缀和O(1)算出结果
        }
        c[400000] = 0;
        for(int i = n + 1;i <= 2 * n;i ++)
        {
            if(a[i] == 1)d[i] = d[i - 1] + 1;
            else d[i] = d[i - 1] - 1;
            c[d[i] + 400000] = min(c[d[i] + 400000],i - n);//下标偏移+记录
        }
        for(int i = 1;i <= n + 1;i ++)//到n+1，因为有可能左边一个都不选的情况
        	ans = min(ans,n + 1 - i + c[sum - b[i] + 400000]);//访问并找最小值
		cout << ans << endl;
    }
}
```

---

## 作者：luan341502 (赞：0)

一眼就能看出做法的题，不过要处理好细节。

考虑计算从左侧开始吃的时候两种果酱的差值，然后统计右侧的差值，如果差值互为相反数，就满足两种果酱数量相等的条件，计入该差值在左侧能取到的最右位置，此时满足答案最小。

另外判断一下全部吃完和吃完左边，右边部分吃完以及吃完右边，左边部分吃完这几种情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int tt;
int n,a[100005],b[100005];
map<int,int> last;
void solve(){
	last.clear();
	cin>>n;
	set<int> s;
	set<int>::iterator it;
	int sum,sum1=0,sum2=0,ans=2*n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==1) sum1++;
		else sum1--;
		if(!sum1) ans=min(ans,2*n-i);
	}
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=n;i;i--){
		if(b[i]==1) sum2++;
		else sum2--;
		if(!sum2) ans=min(ans,n+i-1);
	}
	sum=sum1+sum2;
	if(!sum){
		cout<<"0\n";
		return;
	}
	int x=sum;
	for(int i=n;i;i--){
		if(a[i]==1) x--;
		else x++;
		if(!x){
			ans=n-i+1;
			break;
		}
	}
	x=sum;
	for(int i=1;i<=n;i++){
		if(b[i]==1) x--;
		else x++;
		if(!x){
			ans=min(ans,i);
			break;
		}
	}
	sum=0;
	for(int i=1;i<=n;i++){
		if(a[i]==1) sum--;
		else sum++;
		s.insert(sum);
		last[sum]=i;
	}
	sum=0;
	for(int i=n;i;i--){
		if(b[i]==1) sum++;
		else sum--;
		it=s.find(sum);
		if(it==s.end()) continue;
		else ans=min(ans,i-1+n-last[*it]);
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>tt;while(tt--)solve();
	return 0;
}
```


---

## 作者：YGB_XU (赞：0)

VP时做的题。~~个人感觉比 B 题还容易些~~。看到还没有我这种做法~~而且代码貌似好看一些~~，于是来交一发题解。

我们对于左边和右边两列分别预先处理出两个信息：

- 连续取到第 $i$ 瓶果酱后**已取走的**两种果酱的差值（即草莓数减去蓝莓数），在代码中左右两列分别对应过程量 `nl` 与 `nr`。
- 对于某差值（意义同上），记录其出现时取走果酱数的**最小值**，在代码中左右两列分别对应数组 `fl` 与 `fr`。

随后我们枚举左边一列有可能出现的所有差值，并算出其相应的右边一列的差值（通过预处理原先总体的差值），用两侧差值对应取走最小果酱数（即上述信息 $2$）来更新答案。此外还需注意这个差值**可能为负数**，因此对差值数组下标统一加上一个最大值。

详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int NR=2e5+5;
int l[NR],r[NR],fl[NR*2+5],fr[NR*2+5]; 

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		memset(fl,0,sizeof(fl));
		memset(fr,0,sizeof(fr));
		int n;
		scanf("%d",&n);
		for(int i=n;i>=1;i--) scanf("%d",&l[i]);//注意输入顺序
		for(int i=1;i<=n;i++) scanf("%d",&r[i]);
		int sum=0,nl=0,nr=0;//用sum记录总体差值
		for(int i=1;i<=n;i++){
			if(l[i]==1){
				nl++;
				sum++;
			}else{
				nl--;
				sum--;
			}
			if(r[i]==1){
				nr++;
				sum++;
			}else{
				nr--;
				sum--;
			}
			if(!fl[nl+NR]) fl[nl+NR]=i;//如果此差值第一次出现，则记录当前取走果酱数
			if(!fr[nr+NR]) fr[nr+NR]=i;
		}
		if(sum==0){
			printf("0\n");
			continue;
		}
		int ans=2e9;
		for(int i=-n;i<=n;i++){//枚举左侧所有可能出现的差值
			int j=sum-i;//计算右侧对应差值
			if(fl[i+NR]&&i==sum) ans=min(ans,fl[i+NR]);//特殊处理仅取走左侧时所取走果酱数
			if(fr[j+NR]&&j==sum) ans=min(ans,fr[j+NR]);//右侧同上
			if(!fl[i+NR]||!fr[j+NR]) continue;
			ans=min(ans,fl[i+NR]+fr[j+NR]);
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：Lily_White (赞：0)

有点坑的一个题目。摆在 D 题可能会好一点（不过这场 B 也较难一些）。

先讲一个常见的~~我的~~错误思路：

> 把 $2$ 看作 $-1$。二分剩下的草莓和蓝莓罐头的数量 $t$，维护前缀和数组 $pre$，在判定 $x$ 时，若 $pre_{i+2n-2x-1}-pre_{i-1}=0$，就看作通过判定。

事实证明，这个做法连第二个点也过不去。

那么，错在哪儿呢？

二分的前提是答案具有单调性，也就是说，如果$x$作为答案成立，那么比 $x$ 大的数都应该成立。

但是本题中，选取某一特定长度的段可行，并不代表选择比它长度更长的段一定可行，也并不代表选择比它长度更短的段一定不可行。

~~（Hack数据我也给不出来）~~

~~（要是给出来我场上就 A 了）~~

下面是正确的做法：

仍然把 $2$ 看做 $-1$。从 $n+1$ 位开始，维护一个 `map` 表示右侧变化值与最远位置的映射。再暴力看左侧变化值，当两个值之和是全数列之和时就可以了。

代码如下：
```cpp
/*
ID: yzshang1
LANG: C++11
TASK:
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int (i) = 1; (i) <= (int)n; (i)++)
#define rep(i, n) for (int (i) = 0; (i) < (int)n; (i)++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
const int N = 200020;
int n, a[N], cnt;

int main() {
	int T; cin >> T;
	while (T--) {
		memset(a, 0, sizeof(a));
	//	memset(pre, 0, sizeof(pre));
	//	memset(minr, INF, sizeof(minr));
		cnt = 0;
		cin >> n;
		repn(i, 2 * n) {
			int x;
			cin >> x;
			if (x == 2) x = -1;
			a[i] = x;
			cnt += a[i];
		}	
		if (cnt == 0)  {
			cout << 0  << endl;
			continue;
		}
//		cerr << "CNT = " << cnt << endl;
		int change = 0;
		map <int, int> r; 
		int ans = INF;
		for (int i = n + 1; i <= 2 * n; i++)  {
			change += a[i];
			if (r[change] == 0)r[change] = i;
//			cerr << "ASSIGNED " << i << " TO r[" << change << "]" << endl; 
		}
		if (r.count(cnt)) ans = r[cnt] - n;
		change = 0;
		for (int i = n; i >= 1; i--) {
			change += a[i];
//			cerr << change << endl;
			if (change == cnt) ans = min(ans, n - i + 1);
			if (r.count(cnt - change) && (r[cnt - change] - i + 1) % 2 == 0)
				ans = min(ans, r[cnt - change] - i + 1);
		}
		cout << ans << endl;
	}
	return 0;
}
```




---

