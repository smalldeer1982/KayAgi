# [JOIG 2025] カードゲーム 4 / Card Game 4

## 题目描述

有 $N$ 张卡牌，编号为 $1$ 到 $N$，卡牌 $i(1\le i\le N)$ 上写有一个整数 $A_i$。

现在需要从 $N$ 张卡牌中选择 $K$ 张；对于一种选择，你的得分按照如下的方式进行计算：

- 如果选择的卡牌上写有的整数奇偶性两两相同，那么分数为你选择的所有卡牌上写有的整数之和；
- 否则分数为 $0$。

请求出你能获得的最大得分。

## 说明/提示

#### 【样例解释 #1】

只有一种选择方案，即选择所有的卡牌；由于选择的卡牌上写有的整数均为奇数，故得分为 $1+1+1+1+1=5$。

该样例满足所有子任务的限制。

#### 【样例解释 #2】

无论你如何选择 $K=4$ 张卡牌，你的得分都是 $0$。

该样例满足子任务 $2,4$ 的限制。

#### 【样例解释 #3】

- 其中一种方案为选择卡牌 $1,2,6$，由于选择的卡牌上写有的整数均为奇数，得分为 $3+7+5=15$，但不是最优的；
- 最优方案为选择卡牌 $2,3,5$，由于选择的卡牌上写有的整数均为奇数，得分为 $7+9+7=23$。

该样例满足子任务 $3,4$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $4$ 的限制。

#### 【数据范围】

- $1\le N\le 10^5$；
- $1\le K\le N$；
- $1\le A_i\le 10^9(1\le i\le N)$。

#### 【子任务】

1. （$30$ 分）$N=K$；
2. （$25$ 分）$A_i\le 2(1\le i\le N)$；
3. （$20$ 分）$A_i$ 均为奇数 $(1\le i\le N)$；
4. （$25$ 分）无附加限制。

## 样例 #1

### 输入

```
5 5
1 1 1 1 1```

### 输出

```
5```

## 样例 #2

### 输入

```
6 4
1 2 1 1 2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
7 3
3 7 9 1 7 5 3```

### 输出

```
23```

## 样例 #4

### 输入

```
10 3
23 19 21 20 22 18 22 22 24 27```

### 输出

```
71```

# 题解

## 作者：封禁用户 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P11723)

简单题。开两个数组 $even$ 和 $odd$ 分别存储所有偶数/奇数卡牌上的整数，然后对于每个数 $A_i$，如果它是偶数就存到 $even$ 数组，否则就存到 $odd$ 数组。因为是求最大得分，所以把两个数组从大到小排序，如果偶数超过 $K$ 个，就取前 $K$ 个求和，奇数同理，如果超过 $K$ 个就取前 $K$ 个求和，然后输出偶数和与奇数和的最大值。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
using LL = long long;

const int N = 1e5 + 5;
LL cur, even[N], cnt, odd[N];

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        LL x;
        cin >> x;
        if (!(x % 2)) even[++cur] = x;
        else odd[++cnt] = x;
    }
    sort(even + 1, even + 1 + cur, greater<LL>());
    sort(odd + 1, odd + 1 + cnt, greater<LL>());
    LL esum = 0, osum = 0;
    if (cur >= k)
    {
        for (int i = 1; i <= k; i++)
            esum += even[i];
    }
    if (cnt >= k)
    {
        for (int i = 1; i <= k; i++)
            osum += odd[i];
    }
    cout << max(esum, osum);
    return 0;
}
```

---

## 作者：jzl_1210 (赞：2)

这题还是挺简单的，很容易想到解法。

~~话说时间限制怎么那么长。~~

# 分析
首先，整数奇偶性两两相同简单来说就是选的数都是奇数或者都是偶数。所以，我们先算出两种情况最高各能得到多少分，然后再选出最大的一种就可以了。

当然的，如果奇数或偶数的数量不足 $k$ 个，它们所能得到的最高分数为 $0$。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;//注意会超范围
int n, k, a[100005], jis, ous;
LL ji_sum, ou_sum;
bool cmp(int t1, int t2){
	return t1 > t2;
}
int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1;i <= n;i++){
    	scanf("%d", &a[i]);
    	if(a[i] & 1) jis++;//计算奇数和偶数的个数
    	else ous++;
	}
	sort(a + 1, a + n + 1, cmp);//这里要从大到小排序，方便计算
	if(jis < k){//特殊情况
		ji_sum = 0;
	} else{
		for(int i = 1, cnt = 0;i <= n && cnt < k;i++){
			if(a[i] & 1){//计算都是奇数最多能得到的分
				ji_sum += a[i], cnt++;
			}
		}
	}
	if(ous < k){
		ou_sum = 0;
	} else{
		for(int i = 1, cnt = 0;i <= n && cnt < k;i++){
			if((a[i] & 1) ^ 1){//计算都是偶数最多能得到的分
				ou_sum += a[i], cnt++;
			}
		}
	}
	if(ji_sum > ou_sum){//输出
		printf("%lld", ji_sum);
	} else{
		printf("%lld", ou_sum);
	}
	return 0;
}

```

---

## 作者：Eric1030 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P11723)

## 思路
这道题不太难，我们来讲一下思路。

首先我们把数据输入进来，如果 $A_i$ 是奇数，那么 $cntj$ 就加 $1$，$j_{cntj}$ 设为 $A_i$，如果是偶数，那么 $cnto$ 就加 $1$，$o_{cnto}$ 设为 $A_i$，然后把 $j$ 和 $o$ 数组从大到小排序，如果 $cntj$ 和 $cnto$ 都小于 $K$，就输出 $0$，结束程序。如果 $cntj\ge K$ 但 $cnto<K$，就输出 $j$ 数组前 $K$ 项的和。如果 $cnto\ge K$ 但 $cntj<K$，就输出 $o$ 数组前 $K$ 项的和。否则求 $j$ 和 $o$ 数组的前 $K$ 项，取最大值。

由于在之前 $j$ 和 $o$ 数组都已经从大到小排完序了，所以在求和时直接求就可以了，求出来的和一定是最大的。

## [AC](https://www.luogu.com.cn/record/202775161) 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, a[100005], cntj, cnto, j[100005], o[100005], sumj, sumo;//a[i]小于等于10的九次方，用sumj和shuo来求和容易爆int，所以用long long
int main()
{
	//输入数据
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		if (a[i] % 2 == 0)//如果a[i]是偶数
		{
			cnto++;//偶数个数+1
			o[cnto] = a[i];//把a[i]存到o数组中
		}
		else//a[i]是奇数
		{
			cntj++;//奇数个数+1
			j[cntj] = a[i];//把a[i]存到j数组中
		}
	}
	if (cnto < m && cntj < m)//奇偶性相同数量都比m小，也就是无法满足第一条要求
	{
		cout << 0;//输出0
		return 0;
	}
	sort(j + 1, j + 1 + cntj, greater<int>());//把存奇数的数组从大到小排序
	for (int i = 1;i <= m;i++)
	{
		sumj += j[i];//求j数组前m个数的和的最大值
	}
	sort(o + 1, o + 1 + cnto, greater<int>());//把存偶数的数组从大到小排序
	for (int i = 1;i <= m;i++)
	{
		sumo += o[i];//求o数组前m个数的和的最大值
	}
	if (cnto < m && cntj >= m)//只有奇数满足第一条要求
	{
		cout << sumj;//输出奇数和
	}
	else if (cntj < m && cnto >= m)//只有偶数满足第一条要求
	{
		cout << sumo;//输出偶数和
	}
	else if(cnto >= m && cntj >= m)//奇数偶数都满足第一条要求
	{
		cout << max(sumo, sumj);//输出奇数和最大值和偶数和最大值的最大值
	}
	return 0;
}
```

---

## 作者：dg114514 (赞：1)

水题。\
可以存储两个数组，一个存奇数，一个存偶数。降序排序然后看选 $k$ 个奇数大还是选 $k$ 个偶数大即可。（如果这两个都不足 $k$ 个，输出 `0`。）\
复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N=5e5+5;
int a[N],b[N],ca,cb,sa,sumb;
signed main(){
	int n,k,x;
	cin>>n>>k;
	while(n--) cin>>x,(x&1)?a[++ca]=x:b[++cb]=x;
	sort(a+1,a+ca+1,greater<int>());
	sort(b+1,b+cb+1,greater<int>());
	if(ca<k&&cb<k) puts("0"),exit(0);
	if(ca>=k)
		for(int i=1;i<=min(ca,k);i++)
			sa+=a[i];
	if(cb>=k)
		for(int i=1;i<=min(cb,k);i++)
			sumb+=b[i];
	cout<<max(sa,sumb);
	return 0;
}
```

---

## 作者：Bearbrother18 (赞：1)

### 声明


---

由于本蒟蒻太蒟，所以只会使用暴力，不喜勿喷。

### 思路


---

由题可得因为选择卡牌如果奇偶性不同就会输出 $0$，所以我们要求最大值就要保证奇偶性相同。

那么我们在输入数据时可以分别用两个变量记录输入的奇数的总数和偶数的数量。

然后进行判断：

1. 奇数总数和偶数都小于选择张数时，就必然打破奇偶相同的前提，所以只能输出 $0$。
1. 奇数总数大于选择张数并且偶数总数小于选择张数时，易得选择奇数可得最大值。
1. 偶数总数大于选择张数并且奇数总数小于选择张数时，易得选择偶数可得最大值。
2. 奇数和偶数都大于选择张数时，易得选择奇数总值和偶数总值中更大的一方求最大值。

接着就是如何求最大得分的问题了，不难想到我们可以用两个数组分别存下奇数和偶数，用 sort 从小到大将奇数和偶数分别排列，计算最大值时从后向前累加选择张数个数即可。（当然也可以直接从大到小排列，从前到后累加，~~但蒟蒻忘了咋打代码了所以选择绕了一圈~~）。

最后在这里展出代码，~~马蜂不正不喜勿喷~~。

### 代码


---


```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long//不开long long见祖宗

int n,k,cnt,res,ans,js,os;
int a[1000005],b[1000005],c[1000005];

signed main (){
	cin >> n >> k;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		if(a[i]%2==0){
			cnt++;//记录偶数数量
			b[cnt]=a[i];//存偶数
		}
		else if(a[i]%2!=0){
			res++;//记录奇数数量
			c[res]=a[i];//存奇数
		}
	}
	sort(b+1,b+1+cnt);//从小到大排序偶数
	sort(c+1,c+1+res);//从小到大排序奇数
	if(cnt>=k&&res>=k){
    int lk=k;
		for(int i=cnt; i>=1; i--){//从后向前累加
			if(k==0){
				break;
			}
			js+=b[i];
			k--;//每取一个数选择数量减一
		}
		k=lk;
		for(int i=res; i>=1; i--){
			if(k==0){
				break;
			}
			os+=c[i];
			k--;
		}//情况4
		ans=max(os,js);//取更大的一方
		cout << ans;
	}
	else if(cnt>=k&&res<k){
		for(int i=cnt; i>=1; i--){
			if(k==0){
				break;
			}
			js+=b[i];
			k--;
		}
		cout << js;
	}//情况3
	else if(cnt<k&&res>=k){
		for(int i=res; i>=1; i--){
			if(k==0){
				break;
			}
			os+=c[i];
			k--;
		}
		cout << os;
	}//情况2
	else{
		cout << 0;
	}//情况1
	
	return 0;//好习惯
}
```

### 提示


---

不开龙龙见祖宗！不开龙龙见祖宗！不开龙龙见祖宗！

重要的事情说三遍！

---

## 作者：Camellia_Spoil (赞：1)

# 题意
给你一个长度为 $n$ 的序列，你要在其中选择恰好 $k$ 个数，满足这些数奇偶性相同，得分为这些数之和，求最大得分。

# 分析
一道简单题。首先我们先将原数组分为一个奇数数组和一个偶数数组，即将原数组里的奇数提出来放进一个数组 $x$ 里，偶数提出来放进一个数组 $y$ 里。

然后特判奇数和偶数的个数是否大于等于 $k$，如果都小于，则直接输出 $0$，否则的话再贪心对 $x$ 和 $y$ 数组降序排序，计算出前 $k$ 个数的和，然后比较输出最大值即可。最后记得判断其中一种大于，另外一种小于的情况。

# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
inline long long read()
{
	long  long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,k,a[111111];
int x[111111],y[111111];
int cmp(int a,int b)
{
    return a>b;
}
signed main(){
    n=read();k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    int j=0,lj=0,o=0,lo=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]%2==0) x[++lo]=a[i];
        else y[++lj]=a[i];
    }
    sort(x+1,x+lo+1,cmp);
    sort(y+1,y+lj+1,cmp);
    if(lo<k&&lj<k)
    {
        printf("0");
        return 0;
    }
    if(lo>=k&&lj>=k)
    {
        for(int i=1;i<=k;i++) o+=x[i];
        for(int i=1;i<=k;i++) j+=y[i];
        printf("%lld\n",max(o,j));
        return 0;
    }
    if(lo>=k)
    {
        for(int i=1;i<=k;i++) o+=x[i];
        printf("%lld\n",o);
        return 0;
    }
    else
    {
        for(int i=1;i<=k;i++) j+=y[i];
        printf("%lld\n",j);
        return 0;
    }
	return 0;
}

```

---

## 作者：coderJerry (赞：1)

看到奇偶性相同，不难想到将 $n$ 个数拆成奇数和偶数部分。这题不难，分好类理清思路即可。

如果奇数个数和偶数个数都比 $k$ 小的话，说明要选的 $k$ 个数里必定有若干数和其他数奇偶性不同，输出 $0$。

如果奇数个数或偶数个数只有一个不小于 $k$ 的话，取个数不小于 $k$ 的那组数前 $k$ 大的数的和即为答案。

如果奇数个数和偶数个数均不小于 $k$ 的话，分别取奇数和偶数组的前 $k$ 大的数加和取最大值即可。

细节：```long long```。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,x=0,y=0,ans=0,s1=0,s2=0,a[100010],b[100010],c[100010];
bool cmp(int x,int y){return x>y;}
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]%2==0){x++;b[x]=a[i];}
        else{y++;c[y]=a[i];}
    }
    if(k>max(x,y)) cout<<"0\n";
    else{
        sort(b+1,b+x+1,cmp);
        sort(c+1,c+y+1,cmp);
        if(x>=k) for(int i=1;i<=k;i++) s1+=b[i];
        if(y>=k) for(int i=1;i<=k;i++) s2+=c[i];
        cout<<max(s1,s2);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

考虑贪心，将奇数存到一个数组里，再将偶数存到另一个数组里，然后分别排序，最后计算两个数组中前 $k$ 大数的和中较大的那一个。

## 实现：
可以直接用数组，我用的是优先队列存。注意开 long long。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[100005],t1,t2,ans1,ans2;
priority_queue<int,vector<int>,less<int>> b,c;
bool cmp(int x,int y){return x>y;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(register int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]&1)b.push(a[i]);
		else c.push(a[i]);
	}
	if(b.size()<k&&c.size()<k){
		cout<<0;
		return 0;
	}else{
		if(b.size()>=k){
			for(register int i=1;i<=k;i++){
				ans1+=b.top();
				b.pop();
			}
		}
		if(c.size()>=k){
			for(register int i=1;i<=k;i++){
				ans2+=c.top();
				c.pop();
			}
		}
		cout<<max(ans1,ans2);	
	}
	return 0;
}

```

---

## 作者：jcf666 (赞：0)

# 题目大意
选择 $K$ 张奇偶性相同的卡牌使其累加和最大。
# 解题思路
可以把这 $N$ 张牌进行分组处理，分成奇数和偶数两堆，进行贪心选取。将这两堆中的卡牌按倒序排序，优先取数值大的卡牌，进行累加后比较这两堆卡牌所得答案，输出最大的那个答案。注意也有输出为 $0$ 的情况，这就是因为奇数和偶数这两堆中的卡牌数量都小于 $K$。

打好代码后不要着急交，看一下数据范围，$A_i \le 10^9$，且 $K \le N \le 10^5$，这代表最后的答案最大可以达到 $10^{14}$，会超过 $2^{31}-1$，所以你懂的。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,odd[10000005],even[10000005],a[10000005],ans,tmp;//不要忘记开long long!!!
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]&1)odd[++odd[0]]=a[i];
		else even[++even[0]]=a[i];
	}
	sort(odd+1,odd+1+odd[0],greater<>());
	sort(even+1,even+1+even[0],greater<>());
	if(odd[0]>=k){
		for(int i=1;i<=k;i++)tmp+=odd[i];
		ans=max(ans,tmp);
	}
	if(even[0]>=k){
		tmp=0;
		for(int i=1;i<=k;i++)tmp+=even[i];
		ans=max(ans,tmp);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Dollartree (赞：0)

### 解题思路
1. 首先，选择的卡牌上写有的整数奇偶性两两相同，说明选择的数一定全是奇数或全是偶数。

2. 所以我们可以将奇数和偶数分别存在两个优先队列中，并利用优先队列求出前 $K$ 个最大的数。

3. 最后在全是奇数或全是偶数的答案之中取最大值即可。

### 注意事项

1. 要开 longlong，因为 $1\le N\le 10^5$，$1\le K\le N$，$1\le A_i\le 10^9(1\le i\le N)$。

2. 如果奇数（偶数）不足 $K$ 个，则奇数（偶数）的答案为 $0$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
priority_queue<long long> odd,even;//开longlong 
int main(){
    int n,k,x;
    cin>>n>>k;
    for(int i=1;i<=n;++i)
    {
    	cin>>x;
    	if(x%2)
    	{
    		even.push(x);//分别扔进优先队列中 
		}
		else
		{
			odd.push(x);
		}
	}
    long long oddmax=0;
    if(odd.size()>=k)//判断个数是否大于等于k 
    {
    	for(int i=1;i<=k;++i)
    	{
    		oddmax+=odd.top();
    		odd.pop();
		}
	}
    long long evenmax=0;
    if(even.size()>=k)
    {
    	for(int i=1;i<=k;++i)
    	{
    		evenmax+=even.top();
    		even.pop();
		}
	}    
    cout<<max(evenmax,oddmax); 
}
```

---

## 作者：Soviet_Onion (赞：0)

## P11723 [JOIG 2025] Card Game 4 题解
### Solution
贪心。

首先开两个大根堆，然后读入序列。如果是奇数，就把它扔进记录奇数的堆里；如果是偶数就扔进记录偶数的堆里。

读入后进行处理。如果符合条件，我们肯定优先选择最大的分数。如果记录奇数的堆的大小不小于 $K$，就取出前 $K$ 个值；对于偶数的堆也是如此。最后答案取较大值即可。

其中，堆可以使用 C++ 自带的 priority_queue 实现。

时间复杂度 $O(N\log N)$。
### [AC Code](https://www.luogu.com.cn/record/202926859)
```cpp
#include<iostream>
#include<queue>
#define ll long long
using namespace std;
const int N=1e5+10;
priority_queue<int>odd,even;
int a[N],n,k;
ll ans1,ans2;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]&1) odd.push(a[i]);
		else even.push(a[i]);
	}
	if(odd.size()>=k){
		for(int i=1;i<=k;i++){
			ans1+=odd.top();
			odd.pop();
		}
	}
	if(even.size()>=k){
		for(int i=1;i<=k;i++){
			ans2+=even.top();
			even.pop();
		}
	}
	cout<<max(ans1,ans2)<<endl;
	return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11723)

# 题目分析

选出的数奇偶性两两相等，意味着只能全部选奇数或全部选偶数。因此可以将原数列的奇数和偶数分别挑出来存在两个数组中，分别对两个数组从大到小排序并分别算出前 $k$ 大的奇数之和和前 $k$ 大的偶数之和分别记为 $s_1$ 和 $s_2$。需要特别注意的是若奇数数列（或偶数数列）总长度小于 $k$，则 $s_1$（或 $s_2$）要设为 $0$，然后输出 $\max(s_1,s_2)$ 即可。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000001],o[1000001],e[1000001],h1=0,h2=0,anso=0,anse=0,lo=0,le=0;
int cmp(int a,int b){
	return a>b;
}
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]%2==1){
			o[h1++]=a[i];
			lo++;
		}
		else{
			e[h2++]=a[i];
			le++;
		}
	}
	sort(o,o+h1,cmp);
	sort(e,e+h2,cmp);
	for(int i=0;i<k;i++){
		anso+=o[i];
		anse+=e[i];
	}
	if(lo<k){
		anso=0;
	}
	if(le<k){
		anse=0;
	}
	cout<<max(anso,anse);
	return 0;
}
```

---

## 作者：LG086 (赞：0)

让你在 $n$ 个数中选 $k$ 个，计算最大分数。

注意到如果选择的整数**奇偶性都相同**，那么分数为它们的和。所以要想**有分数**，首先想到保证选择的数字**都是奇数**或**都是偶数**。而要**分数最大**，就想到把数字都排序一次，选前 $k$ 个最大的奇数或偶数。那么如何判断选奇数好还是选偶数好？两种情况都试一遍再比个大小就行了。当然，如果选不了 $k$ 个奇偶性相同的数字，那么答案直接清零。

做完了。

示例代码：

```
stable_sort(a+1,a+1+n);//排序
int now=1,K=k;ll cnt=0;
while(now>=0){
    for(int i = n;i >= 1 and K;i --)
        if(a[i]%2==now)cnt+=a[i],K--;//计算数字和
    if(K)cnt=0;//选不了 k 个数字就清零
    ans=max(ans,cnt);//比大小
    K=k,now--,cnt=0;
}
```

---

