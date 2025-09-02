# Make Nonzero Sum (hard version)

## 题目描述

This is the hard version of the problem. The difference is that in this version the array contains zeros. You can make hacks only if both versions of the problem are solved.

You are given an array $ [a_1, a_2, \ldots a_n] $ consisting of integers $ -1 $ , $ 0 $ and $ 1 $ . You have to build a partition of this array into the set of segments $ [l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k] $ with the following property:

- Denote the alternating sum of all elements of the $ i $ -th segment as $ s_i $ : $ s_i $ = $ a_{l_i} - a_{l_i+1} + a_{l_i+2} - a_{l_i+3} + \ldots \pm a_{r_i} $ . For example, the alternating sum of elements of segment $ [2, 4] $ in array $ [1, 0, -1, 1, 1] $ equals to $ 0 - (-1) + 1 = 2 $ .
- The sum of $ s_i $ over all segments of partition should be equal to zero.

Note that each $ s_i $ does not have to be equal to zero, this property is about sum of $ s_i $ over all segments of partition.

The set of segments $ [l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k] $ is called a partition of the array $ a $ of length $ n $ if $ 1 = l_1 \le r_1, l_2 \le r_2, \ldots, l_k \le r_k = n $ and $ r_i + 1 = l_{i+1} $ for all $ i = 1, 2, \ldots k-1 $ . In other words, each element of the array must belong to exactly one segment.

You have to build a partition of the given array with properties described above or determine that such partition does not exist.

Note that it is not required to minimize the number of segments in the partition.

## 说明/提示

In the first test case we can build a partition of $ 4 $ segments — each of them will contain only one element of the array equals to $ 0 $ . So the sum will be equal to $ 0 + 0 + 0 + 0 = 0 $ .

In the second test case we can build a partition of $ 4 $ segments. The alternating sum of the first segment will be equal to $ -1 $ , the alternating sum of the second segment will be equal to $ 1 $ , of the third segment — $ 0 - 1 + 0 = -1 $ , of the fourth segment — $ 1 - 0 = 1 $ . The sum will be equal to $ -1 + 1 -1 + 1 = 0 $ .

In the third test case it can be proved that the required partition does not exist.

## 样例 #1

### 输入

```
5
4
0 0 0 0
7
-1 1 0 1 0 1 0
5
0 -1 1 0 1
3
1 0 1
1
1```

### 输出

```
4
1 1
2 2
3 3
4 4
4
1 1
2 2
3 5
6 7
-1
2
1 1
2 3
-1```

# 题解

## 作者：bsTiat (赞：7)

这里提供一种简单的解法。

考虑分段的本质是什么，其实就是给每个元素乘上 $ 1 $ 或 $ -1 $，不能有两个相邻的元素都乘上 $ -1 $。

于是考虑，初始时假设每个元素都乘上了 $ 1 $，现在我们需要将其中一些元素改为乘上 $ -1 $，修改的两个元素不能相邻。

直接贪心地选取即可，从前往后枚举每个元素，判断若当前元素乘上 $ -1 $，元素和的绝对值是否会减小，若减小就操作，然后记录一下，下一个元素不能再乘上 $ -1 $。

贪心的正确性也很好证明，若当前元素乘上 $ -1 $ 后，元素和的绝对值会减小，但是我们不修改当前元素，那么下一个元素最多也只会让元素和的绝对值减小相同的数，所以我们先对当前元素进行修改，一定不会更劣，就做完了。
```cpp
#include<bits/stdc++.h>
# define sum(x,y) (s[y]-s[x-1])
using namespace std;
inline int rd(){
	int f=1,s=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){s=(s<<3)+(s<<1)+(c^48);c=getchar();}
	return s*f;
}
const int N = 2e5;
int t,n,s[N+5],f[N+5],g[N+5],a[N+5];
int main(){
	t=rd();
	while(t--){
		n=rd();int sum=0,cnt=n;
		for(int i=1;i<=n;++i)
			a[i]=rd(),sum+=a[i],g[i]=0;
		
		for(int i=2;i<=n;++i)
			if(abs(sum-2*a[i])<abs(sum)&&!g[i-1])
				g[i]=1,--cnt,sum-=2*a[i];
		if(sum)printf("-1\n");
		else{
			printf("%d\n",cnt);
			g[n+1]=0;
			for(int i=1;i<=n;++i){
				if(g[i])continue;
				if(g[i+1])printf("%d %d\n",i,i+1);
				else printf("%d %d\n",i,i); 
			}	
		}
	}
	return 0;
}
```



---

## 作者：Day0 (赞：5)

建议先看 [这篇题解](https://afotle.blog.luogu.org/solution-cf1753a1)。

考场以为 $\operatorname{A1}$ 和 $\operatorname{A2}$ 只差了一点数据范围，交了 $\operatorname{A1}$ 的代码就过了。

考后发现，差点不是数据范围，而是串可能由 $1,-1,0$（多了 $0$）三种元素构成。

但是上面那篇题解说的方法也是能过的，因为使用这种方法，可以忽略 $0$ 的存在。这种方法中，$0$ 默认前面的符号为正号，而我们只希望 $-1$ 或者 $1$ 前面数字的符号为正号，而 $0$ 我们不会去改变符号，所以一定是正号，这种获取的情况也一样是最优的。

---

## 作者：Alex_Wei (赞：5)

如果序列和为奇数，即不为 $0$ 的数的个数为奇数，显然无解。

考虑两个不为 $0$ 的数 $a_x, a_y$，满足 $a_{x + 1} \sim a_{y - 1}$ 都是 $0$。

- 如果 $a_x + a_y = 0$，可以分成 $[x, y - 1]$ 和 $[y, y]$。

- 否则 $a_x = a_y$。若 $x + 1 = y$ 则分成 $[x, y]$，否则分成 $[x, y - 2]$ 和 $[y - 1, y]$。

我们将 $[x, y]$ 分成了若干段，它们的权值之和为 $0$。将第 $2k + 1$ 个不为 $0$ 的数和第 $2k + 2$ 个不为 $0$ 的数像这样配对，剩下来没有被覆盖的所有数均为 $0$，容易得到一组分段方案。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1753/submission/177541721)。

---

## 作者：asasas (赞：4)

[简单版](https://www.luogu.com.cn/problem/CF1753A1)

在赛时写这题的我,想说: 这就是一个诈骗题!!!!


这题相对于简单版 最大的难点就是在处理0上，但两者实际的处理方法是一样的，所以我们先讲简单版。


简单版题目大意:

给出了一个只有 $1$ 和 $-1$ 的序列，要求我们划分出若干个区间，每个区间内的元素按照在**这段区间里的下标,奇不变偶变**的方式求出和,求所有区间的和是否能为 $0$ ，如果无解输出 $-1$，否则输出所有区间的左,右端点。

首先可以知道，在区间长度为奇数时，无解。
因为在这种情况下,无论如何构造，一定会多出来一个数，所以无解。

由于这题没有对答案有限制，只要符合要求就行，所以我们**将区间长度往小了想,只对每两个数进行讨论**。于是有两种情况:

- $a_i=a_{i+1}$ ,此时把这两个数放到一个区间即可,及$\left [ i,i+1 \right ] $ 。

- $a_i\ne a_{i+1}$ ,此时这两个数单独放即可,及区间$\left [ i,i \right ] $ 和 $\left [ i+1,i+1 \right ] $ 。 

至此,简单版就讲完了。

那这题对于简单版难在哪呢?**序列里不只有 $1$ , $-1$ 了，还有 $0$ 。** 这导致这题码量相对于简单版大大增加,但思想仍然是一样的,但在处理时要特别注意中间的 $0$ 导致的数所在区间的下标奇偶性的变化。

详情见代码吧:

```cpp
#include <bits/stdc++.h>
using namespace std;
int wz[200005],n,a[200005],b[200005],x[200005],L[200005],R[200005];
int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int cnt=0,ok=0,len=0;
		for (register int i=1;i<=n;i++){
			cin >> a[i];
			if (a[i]!=0) b[++cnt]=a[i],wz[cnt]=i;//记录每个非0位置的信息
		}
        if (cnt%2==1){
        	cout << -1 << endl;//无解
        	continue ;
		}
		for (register int i=1;i<=cnt;i+=2){
			if (b[i]!=b[i+1]){//第二种情况
				for (register int j=wz[i-1]+1;j<=wz[i+1];j++){
					L[++len]=R[len]=j;//每段单独分
				}
			}
			else {
				if (wz[i]+1==wz[i+1]) L[++len]=wz[i-1]+1,R[len]=wz[i+1];//相邻就直接分,注意要从上个非0位置+1开始
				else {
					for (register int j=wz[i-1]+1;j<=wz[i];j++) L[++len]=R[len]=j;//i之前全部单独分
					for (register int j=wz[i]+1;j<=wz[i+1]-2;j++) L[++len]=R[len]=j;
					L[++len]=wz[i+1]-1,R[len]=wz[i+1];//给第i+1个非零位置前留下一个0使它在区间里的长度变为偶数
				}
			}
		}
		if (R[len]<n){
			L[len+1]=R[len]+1,R[len+1]=n;
			len++;//可能最后一个非零数后面还有,单独再开一段
		}
		cout << len << '\n';
		for (register int i=1;i<=len;i++) cout << L[i] << ' ' << R[i] << endl;
	}
}
```


---

## 作者：Cat_King (赞：1)

考虑极端情况：假设数组中每一个数字都分成单独的一段，那么 $\sum^{k}_{i=1}s_i$ 即为原数组之和。

如果把其中一个数 $a_i$ 与上一个数 $a_{i-1}$ 合并在同一个区间（$i \neq 1$），那么 $a_i$ **将会取反，且上一个数不变**。

又可根据题意得到：**相邻的两个数不能同时取反**。因此上述中的区间合并没有任何限制（但不能把第一个数往前合并，原因显而易见）。

由此可将问题转化为：可以将序列中的任意（第一个数除外）不相邻的数取反，问如何使序列之和为 $0$。

可以很轻易的得出：每把一个 $1$ 取反成 $-1$，$s_i$ 之和就会减少 $2$、每把一个 $-1$ 取反成 $1$，$s_i$ 之和就会增加 $2$。

因此，只要序列之和为奇数，必然无解。反之必然有解。

若序列之和为偶数，则分情况看待：若序列之和为正数，则只将 $1$ 取反为 $-1$；若序列之和为负数，则只将 $-1$ 取反为 $1$。

于是贪心寻找，从第二个数开始依次往后找，只要找到了 上一个数未被取反 且 符合序列之和的正负 的（非 $0$）数，就将其取反。直到序列之和为 $0$ 时停止。 

输出也很简单，将取反的数与上一个数合并为一个区间就行了。

代码：

```cpp
#include<cstdio>
int T,n,tot,sum;
int a[200005],b[200005];
int main(){
	scanf("%d",&T);
	while(T--){
		sum=tot=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) b[i]=0; 
		for(int i=1;i<=n;i++) scanf("%d",a+i),sum+=a[i];
		if(sum&1){
			puts("-1");
			continue;
		}
		for(int i=2;i<=n;i++){
			if(!sum) break;
			if(a[i]==(sum>0?1:-1)&&(!b[i-1]))
				sum-=2*(sum>0?1:-1),b[i]=1,tot++;
		}
		printf("%d\n",n-tot);
		for(int i=1;i<=n;i++)
			if(b[i+1]&&i+1<=n) printf("%d %d\n",i,i+1),i++;
			else printf("%d %d\n",i,i);
	}
	return 0;
} 
```

---

## 作者：lizhous (赞：1)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1753A2)

[本家传送门](http://codeforces.com/problemset/problem/1753/A2)

## 分析
为了方便表述，在本题解中，我们定义 $a$ 取反为 $-a$。

我们发现，一个区间中奇数位置的符号是一致的，所以若划分的区间长度大于 $2$，我们可以把它分为若干长度为 $2$ 的区间（若长度为奇数则最后一个区间长 $1$）。因为奇偶性不变，所以此时不会对结果有影响。所以我们钦定最后结果不存在长度超过 $2$ 的区间。

同时我们发现，给整个区间取反每个数取反不会影响结果。这样操作相当于对整个过程取反，因为 $0$ 取反为 $0$，所以结果不会变。

方便分析，我们把初始序列和调整为负。若初始序列和为正，则把整个区间取反每个数取反。

我们先把每个数单独划为区间，此时结果为序列和，接下来考虑合并。合并 $0$ 是没有意义的，所以我们只合并 $1$。我们发现每次合并对序列和的影响只会是 $±2$，而只有 $+2$ 对答案有利。所以对于每个数，若它与下一个数合并对答案有利，我们就贪心的合并，注意跳过下一个数，直到序列和到 $0$ 停止。若序列和无法为 $0$，则无解。由于只有 $-1,0,1$，所以这样贪心显然是对的。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define int long long
int t, n, sum, cnt, cnta, cntb;
int a[1000001];
bool f[1000001], flag;
signed main() {
	scanf("%lld", &t);
	while (t--) {
		cnt = cnta = cntb = 0;
		sum = 0; //init
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &a[i]);
			sum += a[i]; //序列和
			f[i] = true; //它是否合并了下一个数，初始没有
			if (a[i] == 1) cnta++; //记录1和-1出现的次数
			else if (a[i] == -1) cntb++;
		}
		if (cnta > cntb) { //和为正数，取反
			swap(cnta, cntb);
			sum = -sum;
			for (int i = 1; i <= n; i++) {
				if (a[i] == 1) a[i] = -1;
				else if (a[i] == -1) a[i] = 1;
			}
		}
		for (int i = 2; i <= n; i++) {
			if (sum >= 0) { //注意要>=，因为最终和可能为1，也是无解的
				continue;
			}
			if (a[i] == -1 && f[i - 1] == true) { //对答案有利
				f[i] = false; //合并
				sum += 2; //更新序列和
			}
		}
		if (sum != 0) { //不为0，无解
			printf("-1\n");
			continue;
		}
		for (int i = 1; i <= n; i++) {
			if (f[i] == true) { //记录有多少个区间
				cnt++;
			}
		}
		printf("%lld\n", cnt); //输出
		for (int i = 1; i <= n; i++) {
			if (f[i] == true) {
				if (i != 1) {
					printf("%lld\n", i - 1);
				}
				printf("%lld ", i);
			}
		}
		printf("%lld\n", n);
	}
}
```

---

## 作者：TimeLimitExceed (赞：1)

考虑对于某一个元素，不同的划分方法只会改变它对于最终答案的贡献的正负，并不会改变贡献的奇偶性，所以说若所有元素的和为奇数，那么就一定无解。

这道题的序列中的元素有 $0,1,-1$，我们把相邻的两个不为 $0$ 的数先分为一组（一定一共有偶数个非零的数字），固定左边界，右边界不断往右扩展，直到找到第二个不为 $0$ 的数字，现在我们只需要想办法让这个区间的贡献为 $0$ 即可。

先计算这个区间的贡献，若贡献已经为 $0$ 那就直接使用这个区间。

下面考虑贡献不为 $0$ 时如何分类讨论，

这个区间最右边的元素一定非 $0$，若这个区间长度为偶数，那最后一个元素计算贡献的时候就会取反，把最后一个元素单独拿出来作为一段，这样就一定能和前面的区间的答案抵消，整个区间的贡献就是 $0$ 了。

若区间长度为奇数，我们再分类一下，若区间的第一个元素非 $0$，就直接把它单独作为一段，后面部分的贡献就会取反，这样就一定能和前面的区间的答案抵消，整个区间的贡献也是 $0$。

若区间长度为奇数，同时区间的第一个元素为 $0$，就把这个 $0$ 单独作为一段，后面的按照区间长度为偶数的方法处理即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,sum,lst1,a[N];
vector<pair<int,int>>ans;
void Main()
{
	cin>>n;
	lst1=sum=0;
	for(int i=1;i<=n;++i)cin>>a[i],sum+=a[i];
	if(sum&1)return cout<<"-1\n",void(0);
	ans.clear();
	for(int i=1,lst=1,f1=-1;i<=n;++i)
	{
		if(a[i]==0)continue;
		lst1=i;
		if(f1==-1){f1=i;continue;}
		if((((f1-lst+1)&1)?a[f1]:-a[f1])+(((i-lst+1)&1)?a[i]:-a[i])==0)
		{
			ans.emplace_back(make_pair(lst,i));
			lst=i+1;
			f1=-1;
			continue;
		}
		if((~(i-lst+1))&1)
		{
			ans.emplace_back(make_pair(lst,i-1));
			ans.emplace_back(make_pair(i,i));
			lst=i+1;
			f1=-1;
			continue;
		}
		if((i-lst+1)&1)
		{
			if(a[lst])
			{
				ans.emplace_back(make_pair(lst,lst));
				ans.emplace_back(make_pair(lst+1,i));
				lst=i+1;
				f1=-1;
				continue;
			}
			else
			{
				ans.emplace_back(make_pair(lst,lst));
				++lst;
				--i;
				continue;
			}
		}
	}
	if(lst1!=n)ans.emplace_back(lst1+1,n);
	cout<<ans.size()<<'\n';
	for(auto x:ans)cout<<x.first<<' '<<x.second<<'\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T=1;
	cin>>T;
	while(T--)Main();
	return 0;
}
```

本文同时在知乎以及博客园发布~

---

## 作者：SoyTony (赞：1)

前情提要：本做法可同时解决简单与困难两道题。

首先考虑简单版，也就是只含有 $-1$ 和 $1$ 的情况。

需要知道的第一个信息：分成的子段长度只为 $1$ 或 $2$。

显然长度为 $2k$ 的分成两个偶数段，所得结果不变。长度为 $2k+1$ 的分割成 $2k$ 与 $1$ 两个结果也不变。

第二个信息：存在方案的必要性为起初输入的数列求和是偶数。

将一个数的贡献改变正负，显然会造成大小为 $2$ 的影响，于是起初的和一定为偶数。

设起初和为 $sum$。

我们只要找到 $\dfrac{|sum|}{2}$ 个长度为 $2$ 的段，使得其中第二个数（变号的）与 $sum$ 的正负相同。剩余的全部按照长度为 $1$ 分割即可。

不难发现在此做法中，加入 $0$ 之后没有实质上改变。


---

## 作者：_22222222_ (赞：0)

不知道为什么我脑子抽了没从 `easy version` 的代码改改而是直接重写，

然后浪费了半个小时，~~可能真的是脑子抽了吧......~~

#### 题面

[link](https://www.luogu.com.cn/problem/CF1753A1)

和 `easy version` 不同的是，

这道题在 $a$ 数组中会有 $0$ 出现。 

#### solution

首先我们考虑沿用 `easy version` 的做法。

首先先判个无解，发现无解的情况是和 `easy version` 相同的。

即，如果 $\sum \limits^{n}_{i=1}a_i \equiv 1 \pmod 2$，则无解。

在 `easy version` 中，我的构造方式是：

对于相邻的两个数字，

如果这两个数字异号，那么考虑将这两个数分在两组里；

否则将这两个数分在同一组里。

用栈模拟上述过程即可完成构造。

仍旧考虑对于 $1$ 和 $-1$ 采用上述构造，

考虑 $0$ 加入产生的影响：

首先如果两个**删掉所有 $0$ 以后的相邻**元素异号：

并不用对于中间可能存在的 $0$ 特殊处理，

如果存在，只需要将这一段 $0$ 单独分一组即可，显然这一段对于最终和的贡献是 $0$。

然后考虑同号的情况：

这个时候，我们考虑要把后一个元素扔到一个组的第偶数位置进行变号处理。

考虑用一个 $0$ 当做占位符，然后将这个占位符之前的元素和占位符之后的元素分组即可。

(当然如果真的不存在 $0$ 那就是 `easy version` 的情况了。)

同样，用栈模拟上述过程即可完成构造。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int o=222222;
#define pii pair<int,int>
int n,a[o],ans,flag;
vector<pii>d;
void in() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
}
void work(){
	flag=-1;int sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i];
	}
	if(sum&1)return;
	flag=1;int cnt=0,last=0;
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			cnt++;continue;
		}
		else{
			if(!q.empty()){
				if(a[q.front()]==a[i]){//gouzaoxiangfanshu
					if(cnt){
						d.push_back({q.front(),i-2});
						d.push_back({i-1,i});
						q.pop();
					}
					else{
						d.push_back({q.front(),i});
						q.pop();
					}
				}
				else{//gouzaoxiangdeng
					if(cnt){
						d.push_back({q.back(),i-1});
						d.push_back({i,i});
						q.pop();
					}
					else{
						d.push_back({q.front(),q.front()});
						d.push_back({i,i});
						q.pop();
					}
				}
			}
			else {
				if(cnt)d.push_back({last+1,i-1});
				q.push(i);
			}
			cnt=0,last=i;
		}
	}
	if(cnt)d.push_back({last+1,n});
	ans=d.size();
}
void out(){
	if(flag<0)puts("-1");
	else {
		printf("%d\n",ans);
		for(auto i:d){
			printf("%d %d\n",i.first,i.second);
		}
	}
}
void reset(){
	for(int i=1;i<=n;i++) {
		a[i]=0;
	}
	ans=0,flag=-1;
	d.clear();
}
int main(){
	int T;cin>>T;
	while(T--){
		in();work();out();reset();
	}
	return 0;
}
```

好像没在洛谷上 `A` 掉，那还是发个 `Codeforces` 上的 [`AC` 记录](https://codeforces.com/contest/1754/submission/177580079)吧。


---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16825240.html)

[题目传送门](http://codeforces.com/problemset/problem/1753/A2)

给定一个长度为 $n$ 的，仅由 $-1$，$0$ 或 $1$ 组成的序列 $a$。你需要把它划分成若干个连续段，设这些连续段分别为 $[l_1,r_1],[l_2,r_2],\dots,[l_k,r_k]$，那么这样划分的代价是
$$\sum_{i=1}^k\sum_{j=l_i}^{r_i}(-1)^{j-l_i}a_i$$
现在你需要确定任意一种划分方式让总代价为零，或者报告无解。  
### 题目解析
显然 $1$ 和 $-1$ 个数为奇数的时候肯定无解。  
这样只需要保证相邻的两个非零数字都可以消掉就可以了。  

如果相邻的两个非零数字不一样，那么只需要这两个都是正的，显然这两个都作为一个新的区间的开头即可。  
如果相邻的两个非零数字一样，那么这两个就要一正一负。如果前面的一个是正的，那么后面的一个就是负的。这样就有两种可能：如果两个相邻，那么就直接分到一组，否则就前面的作为一组的第一个、后面的作为一组的第二个。


非常丑的赛时代码
```cpp
int n,a[maxn],p[maxn],cnt;
struct JTZ{
	int l,r;
}ans[maxn]; int tmp;
void work(){
	n=read(); cnt=0; int i; for(i=1;i<=n;i++){ a[i]=read(); if(a[i]) p[++cnt]=i; }
	if(cnt&1){ puts("-1"); return; } tmp=0;
	if(cnt==0){
		pc('1'),pc('\n');
		pc('1'),pc(' '),print(n),pc('\n');
		return;
	}
	if(p[1]>1) tmp++,ans[tmp].l=1,ans[tmp].r=p[1]-1;
	for(i=1;i<=cnt;i+=2){
		if(i>1&&p[i-1]<p[i]-1){ tmp++,ans[tmp].l=p[i-1]+1,ans[tmp].r=p[i]-1; }
		if(a[p[i]]==a[p[i+1]]){
			if(p[i]+1==p[i+1]){
				tmp++; ans[tmp].l=p[i]; ans[tmp].r=p[i+1];
			}
			else{
				tmp++; ans[tmp].l=p[i]; ans[tmp].r=p[i+1]-2;
				tmp++; ans[tmp].l=p[i+1]-1; ans[tmp].r=p[i+1];
			}
		} else {
			if(p[i]+1==p[i+1]){
				tmp++; ans[tmp].l=p[i]; ans[tmp].r=p[i];
				tmp++; ans[tmp].l=p[i+1]; ans[tmp].r=p[i+1];
			} else {
				tmp++; ans[tmp].l=p[i]; ans[tmp].r=p[i+1]-1;
				tmp++; ans[tmp].l=p[i+1]; ans[tmp].r=p[i+1];
			}
		}
	}
	if(p[cnt]!=n){
		tmp++; ans[tmp].l=p[cnt]+1; ans[tmp].r=n;
	}
	print(tmp),pc('\n');
	for(i=1;i<=tmp;i++) print(ans[i].l),pc(' '),print(ans[i].r),pc('\n');
}
```

---

## 作者：ryanright (赞：0)

大家都写的是把数字两两配对的做法，那我就来讲另外一种思路。

首先，我们把偶数位上的数字取相反数，这样问题就变成了：把这个数列中的一些区间全部取相反数，使得总和为 $0$。为了方便讨论，如果原来的和为正数，就把整个数列再次取反，使得和为负数。

其次，不难发现，我们反转的区间一定是从偶数位开始，从偶数位结束。因为如果从奇数位开始，则整个区间的和其实是不变的；如果在奇数位结束，就会导致下一位开始的区间取反。

那我们就先考虑最小的区间，就一个偶数位。对于每个偶数位，如果是 $-1$ 就选择反转，因为我们现在的和小了，需要反转 $-1$ 使其变成 $1$，才能使和增大。

好了，如果我们已经处理完了所有的偶数位，但是和还是不够 $0$ 呢？此时我们可以考虑把前面反转的位连起来，这样还是可以满足偶数位开始，偶数位结束的性质。我们看看这两位中间的数字之和是否小于 $0$，如果小于 $0$ 就把这两位连起来，使他们成为一个区间，这样中间的数字也可以得到反转，增大数列和。末尾的区间也需要考虑（即最后一个反转的偶数位到末尾），因为这个区间很特殊，不需要偶数位结束。但是开头就不用考虑，因为 $1$ 是奇数，不能作为反转区间的开头。

好了，现在只剩下了最后一个问题：判断解的存在。注意到，每次我们反转一个区间，都是把 $-1$ 反转成 $1$，这样操作每次会使和增加 $2$。如果我们一开始的和压根就不是偶数，那么无论我们如何反转，都是不可能使和为 $0$ 的。

代码奉上（easy version 也可以用）：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int a[200005], n;
bool b[200005];//反转标记
void print() {
    int ans = 1;
    for (int i = 1; i < n; i++)
        if (b[i] != b[i + 1])
            ans++;
    printf("%d\n", ans);
    int lst = 1;
    for (int i = 2; i <= n; i++)
        if (b[i] != b[i - 1]) {
            printf("%d %d\n", lst, i - 1);
            lst = i;
        }
    printf("%d %d\n", lst, n);
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(b, 0, sizeof(b));
        int tot = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {//预处理
            scanf("%d", &a[i]);
            if (!(i & 1))
                a[i] = -a[i];
            tot += a[i];
        }
        if (!tot) {
            print();
            continue;
        }
        if (tot > 0) {
            for (int i = 1; i <= n; i++)
                a[i] = -a[i];
            tot = -tot;
        }
        if ((-tot) & 1) {//判断无解
            puts("-1");
            continue;
        }
        for (int i = 2; i <= n; i += 2)//反转偶数位
            if (a[i] <= 0) {
                b[i] = 1;
                tot -= a[i] + a[i];
                if (!tot)
                    break;
            }
        if (!tot) {
            print();
            continue;
        }
        int l = 0;
        for (int i = 2; i <= n; i += 2)
            if (b[i]) {
                l = i;
                break;
            }
        while (l) {
            int r = 0;
            for (int i = l + 2; i <= n; i += 2)
                if (b[i]) {
                    r = i;
                    break;
                }
            if (!r)
                break;
            int sum = 0;
            for (int i = l + 1; i < r; i++)
                sum += a[i];
            if (sum <= 0) {//连起来
                for (int i = l + 1; i < r; i++)
                    b[i] = 1;
                tot -= sum + sum;
            }
            if (!tot)
                break;
            l = r;
        }
        if (tot) {//别忘了末尾区间！
            int sum = 0;
            for (int i = l + 1; i <= n; i++)
                sum += a[i];
            if (sum <= 0) {
                for (int i = l + 1; i <= n; i++)
                    b[i] = 1;
                tot -= sum + sum;
            }
        }
        if (tot)
            puts("-1");
        else
            print();
    }
}
```

---

