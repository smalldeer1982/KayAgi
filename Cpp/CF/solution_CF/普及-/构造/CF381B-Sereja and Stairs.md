# Sereja and Stairs

## 题目描述

Sereja loves integer sequences very much. He especially likes stairs.

Sequence $ a_{1},a_{2},...,a_{|a|} $ ( $ |a| $ is the length of the sequence) is stairs if there is such index $ i $ $ (1<=i<=|a|) $ , that the following condition is met:

 $ a_{1}&lt;a_{2}&lt;...&lt;a_{i-1}&lt;a_{i}&gt;a_{i+1}&gt;...&gt;a_{|a|-1}&gt;a_{|a|}. $ For example, sequences \[1, 2, 3, 2\] and \[4, 2\] are stairs and sequence \[3, 1, 2\] isn't.

Sereja has $ m $ cards with numbers. He wants to put some cards on the table in a row to get a stair sequence. What maximum number of cards can he put on the table?

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
5
5 4 3 2 1
```

## 样例 #2

### 输入

```
6
1 1 2 2 3 3
```

### 输出

```
5
1 2 3 2 1
```

# 题解

## 作者：csxx601cjy (赞：1)

### 题意分析
输入一个序列，将它分成 $2$ 部分，一个递增序列，一个递减序列（相邻 $2$ 个数字不能相等），求出两个序列最长的长度和，并输出。
### 做题思路
此题应该用贪心法解决。
本题 $b_i\le5000$，数字较小，可以用桶数组输入。桶数组可以计算出每个数字的出现次数，次数 $=1$ 的可以直接输出，次数 $>1$ 的最多输出 $2$ 次（否则有重复），先输出第一次，第二次等一会儿反序输出。记得输出前要先统计个数。并且不要重复输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5001],a1[100001],a2[100001];
//桶，第一次输出，第二次输出
int m,t,cnt1=0,cnt2=0,last;
//个数，临时变量，计数变量，最后一次输出
int main(){
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>t;
		if(a[t]!=2)a[t]++;//统计次数
	}
	for(int i=1;i<=5000;i++)
		if(a[i]>=1)a1[cnt1++]=i,last=i;//记录最后一次输出
	for(int i=1;i<=5000;i++)
		if(a[i]==2)if(i!=last)a2[cnt2++]=i;//判断一下，否则有重复
	cout<<cnt1+cnt2<<endl;//总长度
	for(int i=0;i<cnt1;i++) cout<<a1[i]<<' ';//正序输出
	for(int i=cnt2-1;i>=0;i--) cout<<a2[i]<<' ';//倒序输出
	return 0;
}
```
我讲的这么详细你们应该听得懂吧。

---

## 作者：Didncan_yu (赞：1)

[cf 传送门](https://codeforces.com/problemset/problem/381/B)  
[原题传送门](https://www.luogu.com.cn/problem/CF381B)

### 思路分析

此题可以使用贪心算法解决，因为取与不取不会影响后面。

对于 $a$ 数组，可以将其分成两部分：$a_1$ 到 $a_i$ 为单调递增，$a_i$ 到 $a_n$ 为单调递减。那么，$a_1$ 和 $a_n$要尽可能小，$a_i$ 尽可能大（所以 $a_i$ 一定是 $b$ 数组中最大的数）。

同时也可以得出：在 $a_1$ 到 $a_i$ 中每个数互不相同。$a_i$ 到 $a_n$ 同理。

所以说：$a$ 数组中不超过 $2$ 个数同时相同。而对于 $a_i$，一定只出现一次（因为两个部分重叠了），否则对于第二个样例会出现如下现象：
```
6
1 2 3 3 2 1
```
### 具体操作

使用 $val_i$ 表示 $a$ 数组中 $i$ 的个数。

- 如果 $val_i + 1 > 2$，那么不将该数放入 $a$ 数组。
- 否则表示将该数放入 $a$ 数组，$val_i$ 增加 $1$，$ans$ 增加 $1$。
- $a_i$ 只能在 $a$ 数组中出现一次，要特判。

### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read();
inline void write(long long n);
int n,ans,kr[5001],q;//这种方法只需要开一个5000大小的数组就可以了
int main(){
	n=read();
	for(int i=1,a1;i<=n;i++){
		a1=read();
		q=max(a1,q);
		if(kr[a1]<=1){
			kr[a1]++;
			ans++;
		}
	}
	if(kr[q]==2)ans--;
	write(ans);
	putchar('\n');
	for(int i=1;i<=q;i++){
		if(kr[i]>0){
			kr[i]--;
			write(i);
			putchar(' ');
		}
	}
	for(int i=q-1;i>=1;i--){
		if(kr[i]>0){
			kr[i]--;
			write(i);
			putchar(' ');
		}
	}
	return 0;
}
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void write(long long n){
	if(n<0){putchar('-');n=-n;}
	if(n>9){write(n/10);}
	putchar(n%10+'0');
}
```

---

## 作者：zhuweiqi (赞：1)

本题很显然是一道贪心算法的题目，如果我们要使得 $a$ 序列尽可能地长，那就必须让 $a_1$ 和 $a_{|a|}$ 尽可能地小，$a_i$ 尽可能地大，这样我们就可以在中间放入更多的数，序列 $a$ 自然就变得长了，另外，由于本题 $b_i$ 的范围非常的小，所以我们可以使用桶标记来优化时间复杂度（注意选数的时候不要重复选！）。上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n;
}
int a[100005];
int b[5005];
int main(){
	int n=read(),ans=0,maxs=1;
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[a[i]]++;
		if(a[i]>maxs) maxs=a[i];
	}
	for(int i=1;i<=maxs;i++){
		if(b[i]>0){
			ans++;
			b[i]--;
		}
	}
	for(int i=maxs-1;i>=1;i--) if(b[i]>0) ans++;
	for(int i=1;i<=maxs;i++) b[i]=0;
	for(int i=1;i<=n;i++) b[a[i]]++;
	printf("%d\n",ans);
	for(int i=1;i<=maxs;i++){
		if(b[i]>0){
			printf("%d ",i);
			b[i]--;
		}
	}
	for(int i=maxs-1;i>=1;i--) if(b[i]>0) printf("%d ",i);
	return 0;
}
```

---

## 作者：11514zbs (赞：0)

看到题目，我们可以发现一个数字最多只能出现 $2$ 次，所以我们可以用桶来存储它们出现的次数，出现的第 $1$ 遍从小到大，第 $2$ 遍从大到小，这样既满足题目要求的大小顺序，也符合我们所发现的“最多只能出现 $2$ 次”的规律，代码很好写，时间复杂度 $O(\max(b_i))$ 。

```cpp
#include <cstdio>
int n, a[5005], b[100005], c[100005], minn = 5005, maxx, sum, j;
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &b[i]);
        a[b[i]]++;
        if (minn > b[i])
        {
        	minn = b[i];
		}
		if (maxx < b[i])
		{
			maxx = b[i];
		}
    }
    for (int i = minn; i <= maxx; i++)
    {
    	if (a[i])
    	{
    		a[i]--;
    		sum++;
    		c[j++] = i;
		}
	}
	for (int i = maxx; i >= minn; i--)
    {
    	if (a[i] && (i != maxx)) // 这里有个坑，如果最大值也出现了 2 次以上，就只算 1 次
    	{
    		a[i]--;
    		sum++;
    		c[j++] = i;
		}
	}
	printf("%d\n", sum);
	for (int i = 0; i < j; i++)
    {
    	printf("%d ", c[i]);
	}
    return 0;
}

```

最后有一个坑点，如果最大值也出现了 $2$ 次以上，我们只能算 $1$ 次。

> 我讲的这么详细你们应该听得懂吧。

 ~~本蒟蒻的第一篇题解awa~~

---

## 作者：littlebug (赞：0)

## Solution

先确定 $a_i$ 为 $b$ 中的最大值，把它放在中间。

因为题目要求严格小于或严格大于，因此同一个数最多被使用 $2$ 次（最大值左边一次，最大值右边一次），所以开一个桶，对于每一个数判断一下，如果只有 $1$ 个那么放在左边（或者右边也可以），如果有 $\ge 2$ 个则在左右两边各放一个即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
//#define int long long
#define pb emplace_back
using namespace std;

const int MAXN=1e5+5;
int n,b[MAXN],cnt[MAXN];
vector <int> v1,v2;

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;++i) cin>>b[i],++cnt[b[i]];

    bool flag=0;
    for(int i=5000;i>=1;--i)
    {
        if(!cnt[i]) continue;
        if(flag)
        {
            v1.pb(i);
            if(cnt[i]>=2) v2.pb(i);
        }
        else v1.pb(i),flag=1;
    }

    reverse(v1.begin(),v1.end());

    cout<<v1.size()+v2.size()<<'\n';
    for(int i:v1) cout<<i<<' ';
    for(int i:v2) cout<<i<<' ';

    return 0;
}
```

---

## 作者：WizeBug (赞：0)

[CF 传送门](https://codeforces.com/problemset/problem/381/B)

[洛谷传送门](https://www.luogu.com.cn/problem/CF381B)
## 题意概括
一个有 $n$ 个元素的序列 $b$，取其中的一些元素重新排列，使新序列成为一个先升序再降序且相邻两元素不相等的序列，该新序列中的元素要尽可能的多。输出该新序列最多可以有几个元素以及该新序列。
## 解题思路
由题意可知，新序列先升序再降序且相邻两元素不相等，故新序列中每个数最多出现两次（在最大值左侧出现一次，最大值右边出现一次），但是最大值最多只能出现一次，所以我们可以把多余的的元素“屏蔽”（将其赋值为 0）。

这就是主要的部分，其余的看代码吧！
## 代码实现
[AC 记录](https://codeforces.com/contest/381/submission/277855803)
```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(int x,int y){
	return x>y;
}
int main(){
	ios::sync_with_stdio(0);  cin.tie(0);   cout.tie(0);
	int m;
	cin>>m;
	int b[m+1],ans=m,maxx=0;// ans 记录剩余元素数量，maxx 记录最大值。
	for(int i=1;i<=m;i++){
		cin>>b[i];
		maxx=max(maxx,b[i]);
	}
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++){
		if(b[i]==b[i+2])
			b[i]=0,ans--;//将多余的元素屏蔽。
		if(b[i]==maxx){//屏蔽多余的最大值。
			for(int j=i+1;j<=m;j++)//只能留一个，其余全部屏蔽。
				b[j]=0,ans--;//不要忘记更新元素数量。
			break;
		}
	}
	cout<<ans<<'\n';
	sort(b+1,b+m+1,cmp);//从大到小排序，将屏蔽的元素（被赋值为 0 的元素）移至序列的最后。
	for(int i=ans;i>=1;i--){//升序输出。
		if(b[i]!=b[i-1]){//若有两个一样的，先输出其中一个。
			cout<<b[i]<<' ';
			b[i]=0;//将输出过的元素屏蔽，方便降序输出。
		}
	}
	for(int i=1;i<=ans;i++){//降序输出。
		if(b[i]!=0)//将输出过的跳过。
			cout<<b[i]<<' ';
	}
	return 0;
}
```

---

## 作者：__O_w_O__ (赞：0)

看到题目的第一眼，就可以想到：要想达到最优解，很明显最大的数字必须选，这样才能使得序列的长度最长。

对于其他的不是最大值的数字，它们只能在序列 $a$ 中出现 $1$ 次或 $2$ 次，$2$ 次的情况是出现在最大值左边和最大值的右边，$1$ 次的情况自然就是这个数只出现了一次。

观察到 $a_i$ 的值的范围很小，自然而然地可以想到用桶来解决问题。

值得注意的是，最大值只能在序列 $a$ 中出现一次，不然这个方案就是不合法的。

剩下的细节看代码吧。

[通过记录](https://codeforces.com/contest/381/submission/277270818)

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100010;
int a[N], cnt[N];
vector<int> v;
int main() {
	int n;
	scanf("%d", &n);
	int mx = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		cnt[a[i]]++;
		mx = max(mx, a[i]);
	}
	for (int i = 1; i <= mx; i++) {
		if (cnt[i]) cnt[i]--, v.push_back(i);
	}
	for (int i = mx - 1; i >= 1; i--) {
		if (cnt[i]) v.push_back(i);
	}
	printf("%d\n", (int) v.size());
	reverse(v.begin(), v.end());//这里注意要翻转vector，因为上面插入元素的时候是倒过来插入的
	for (auto x : v) {
		printf("%d ", x);
	}
	return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

## 题意概括
给定 $m$ 个元素的序列 $b$ ，取若干 $b$ 中的元素组成新序列 $a$ 使得 $a_1<a_2<a_3<\dotsc<a_{i-1}<a_i>a_{i+1}>\dotsc>a_{|a|-1}>a_{|a|}$ 且 $a_{|a|}$ 尽可能大。
## 思路分析
题目中要使 $a_{|a|}$ 尽可能大，简单来说就是使序列 $a$ 的长度尽可能长。因此，这道题使用贪心算法解决。  
首先，根据题意，$a_{1}$ 至 $a_{i}$ 单调递增，$a_{i}$ 至 $a_{|a|}$ 单调递减，同时，$a_{1}$ 至 $a_{i}$ 的所有元素都不相同，$a_{i}$ 至 $a_{|a|}$ 同理，但是序列 $a$ 中可以有相同元素，即 $a_{1}$ 至 $a_{i}$ 与 $a_{i}$ 至 $a_{|a|}$ 间可以有相同元素，但要注意，不能有两个 $a_{i}$。  
要使 $a$ 的长度尽可能长，$a_{1}$ 与 $a_{|a|}$ 要尽可能小，$a_{i}$ 尽可能大，这样才能在中间容下更多的元素。  
本题数据较小，且涉及是否重复的问题，所以使用桶排序。
## AC Code
讲了这么多，来康康代码吧！  
别看代码长得奇形怪状，但是他还是可以AC的。
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,b[100005],t[50005],ans[100005],ansi=0,r;
int main(){
    cin>>m;
    for (int i=1;i<=m;i++){
        cin>>b[i];
        t[b[i]]++;  //桶排序
    }
    for (int i=1;i<=5000;i++){  //a[1]至a[i]从小到大填
        if (t[i]>0){
            ans[ansi++]=i;  //记录答案
            t[i]--;  //减少剩余数量
        }
    }
    r=ans[ansi-1];  a[i+1]至a[n]的最大值不会超过a[i]
    for (int i=r-1;i>=1;i--){  //a[i+1]至a[n]从大到小填
        if (t[i]>0){
            t[i]--;  //减少剩余数量
            ans[ansi++]=i;  //记录答案
        }
    }
    cout<<ansi<<'\n';  //输出长度  记得换行
    for (int i=0;i<=ansi-1;i++) cout<<ans[i]<<' ';  //输出序列a，空格隔开
    return 0;
}
```

---

## 作者：a18981826590 (赞：0)

# [Sereja and Stairs](https://www.luogu.com.cn/problem/CF381B)
## 题意简述
其实题目的意思就是从给定的序列中取尽可能多的元素，其中相同的元素个数 $\le 2$，最大的元素有且仅有 $1$ 个；用这些元素构造一个单峰序列。求这个单峰序列的长度并构造这个单峰序列。
## 解题思路
这道题可以用**贪心**的思想，找到一个符合条件的元素就将其加入到结果中，因为是否取不会影响后面的操作，所以贪心是对的。

为了使结果长度最大，取的元素最多，就应该使峰顶 $a_{i}$ 尽可能大，$a_{1}$ 和 $a_{n}$ 尽可能小。
同时因为每个元素最多可以取 $2$ 个，所以除峰顶外能取 $2$ 个就取 $2$ 个，能取 $1$ 个就取 $1$ 个，出现了且未超过 $2$ 个就把它加入答案。

可以用数组记录每个元素的出现次数，求得长度，再先递增，再递减地输出这些元素。

注意每种元素最多取 $2$ 个，峰顶有且仅有 $1$ 个，相同的元素要在峰顶异侧。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5010],b,c,m,n;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>b;
		if(a[b]<2){
			a[b]++;
			m++;
			c=max(b,c);
		}
	}
	if(a[c]>1) m--;
	cout<<m<<endl;
	for(int i=1;i<c;i++){
		if(a[i]){
			cout<<i<<' ';
			a[i]--;
		}
	}
	cout<<c<<' ';
	for(int i=c-1;i>=1;i--){
		if(a[i]){
			cout<<i<<' ';
			a[i]--;
		}
	}
	return 0;
}
```

---

## 作者：shiziyu111 (赞：0)

## 题目蒟（巨）意
把一个长度为 $n$ 的序列 $a$ 组成一个严格升序再严格降序的序列。

此时，有些数字可能会被抛弃，因此需要输出 $a$ 的长度最大的方案。
## 分析
由于我们要输出最大方案，所以，我们需要把升序和降序的序列的数字之差尽量小。

我们可以将 $a$ 存入记录个数的数组 $b$，再从 $1$ 到最高处挨个存入，这样就造好了升序序列，再从比上一个序列的最后一个点（即最高点）低的下一个点向 $1$ 再次存入，就可以了。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;	
int m,ans,a[100005],b[5005],answers[100005],maxx;
int main()
{

	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
		b[a[i]]++;
	}
	for(int i=1;i<=5000;i++)
	{
		if(b[i]>=1)
		{
			b[i]--;
			ans++;
			answers[ans]=i;			
			maxx=i;
		}
	}
	for(int i=maxx-1;i>=1;i--)
	{
		if(b[i]>=1)
		{
			b[i]--;
			ans++;
			answers[ans]=i;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)
	{
		cout<<answers[i]<<" ";
	}
	return 0;
}
```

---

## 作者：z_yq (赞：0)

本题其实就是贪心，你可以发现 $b_i$ 特别的小，所以我们可以放到一个桶里，我们知道，他就是要求一个从小到大到小的构造，于是我们在桶里面从小到大的遍历，再从大到小遍历即可。详见代码。

### Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e5+9;
ll n,b[N],book[N];vector<ll>a;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>b[i],book[b[i]]++; //放入桶
	for(int i=1;i<=5000;i++)
		if(book[i])
			book[i]--,a.push_back(i); //遍历
	for(int i=4999;i>=1;i--)
		if(book[i] && i!=a[a.size()-1])
			book[i]--,a.push_back(i); // 遍历
	cout<<a.size()<<endl;
	for(int i=0;i<a.size();i++)
		cout<<a[i]<<' ';
	return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# 题意

> 给定 $m$ 个元素的序列 $b$ 。
>
> 取若干 $b$ 中元素组成新序列 $a$ 使得 $a_1<a_2<a_3<\dotsc<a_{i-1}<a_i>a_{i+1}>\dotsc>a_{|a|-1}>a_{|a|}$。
>
> 给出一种使得 $|a|$ 最大的方案。

# 分析

考虑贪心。

先从小到大取数，然后再从大到小取。

关注到值域很小（$b_i\leq5\times10^3$），考虑用桶维护每个数出现的次数。

最后注意一下最大数不能重复选取。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 5003

int cnt[maxn];
vector<int> ans;

int main()
{
    int n;
    cin>>n;
    for(int i=1, t;i<=n;i++)
        cin>>t, cnt[t]++;
    for(int i=1;i<maxn;i++)
        if(cnt[i]) cnt[ans.emplace_back(i)]--;
    for(int i=maxn;i;i--)
        if(cnt[i]&&i!=ans.back()) ans.emplace_back(i);
    cout<<ans.size()<<'\n';
    for(auto i:ans) cout<<i<<' ';    
}
```

---

## 作者：xiaoyang111 (赞：0)

### 思路

题意很清楚了，就是在原序列里面选尽量多的数，使得这些数随便拼凑能够构成一个单峰序列。输出任意一个组成后的单峰序列。

把这个序列拆成三部分看，一边是递增的，中间是只有一个最大值，一边是递减的。

左半部分因为是小于号，所以数不能相同。其实数可以随便选，然后从小到大排序就可以了。

右半部分根左半部分一样，只不过如果左半部分把这个数选完了，这个就不能选了。选完从大到小排序就可以了。

最后我们来看中间。我们就在选左半部分和右半部分的时候不要选最大值，让中间就只有一个最大值就可以了。因为左半部分和右半部分如果选了一个最大值，中间啥也不能填，就不能不一样了。

### 代码

因为是桶记录，所以本来就有序，不需要排序。对于右半部分，倒着扫就可以了。

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int V=5000+5;
int tot[V];
int main(){
	int n;
	cin >> n;
	int t,mx=0;
	for (int i=1;i<=n;++i){
		scanf("%d",&t);
		mx=max(mx,t);
		++tot[t];
	}
	vector<int> ans;
	for (int i=0;i<mx;++i){
		if (tot[i]!=0){
			--tot[i];
			ans.emplace_back(i);
		}
	}
	ans.emplace_back(mx);
	for (int i=mx-1;i>=0;--i){
		if (tot[i]!=0){
			--tot[i];
			ans.emplace_back(i);
		}
	}
	cout<<ans.size()<<endl;
	for (int &t:ans){
		printf("%d ",t);
	}
	return 0;
}
```

[完结撒花！](https://codeforces.com/contest/381/submission/267638458)

---

## 作者：ylinxin2010 (赞：0)

## CF381B题解

**题目翻译：**

有一个序列：$b_1, b_2, b_3 ... b_{\left|b\right|}(\left|b\right|\text{{\small 为序列}}b\text{\small的长度})$，请你从中选取一些构造一个序列为：$a_1<a_2<a_3<...<a_i>a_{i+1}>a_{i+2}>...>a_{\left|a\right|-1}>a_{\left|a\right|}$。

先输入一个 $m(1 \leq m \leq 10^5)$ 然后接下来一行有 $m$ 个 $b_i$ 为序列。

**本题思路：**

1. 先输入再排序。

2. 记录上一个数，并且记录此数是否被使用过。

3. 循环两遍，求出答案数量并输出序列。

接下来——上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int x=0,f=1;
	char ch=getchar();
   	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
   	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
    return x*f;
}
void write(int x)
{
	if(x<0)
		putchar('-'), x=-x;
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
	return ;
}
int main()
{
	cin.tie(0);
	cout.tie(0);
    int n=read(), a[100005], c=1, last=-1, v[100005]={0}, ans=0;
    for(int i=1;i<=n;i++)
        a[i]=read();
    sort(a+1, a+n+1);
    for(int i=1;i<=n;i++)
        if(last<a[i])
            ans++, last=a[i], v[i]=1;
    for(int i=n;i>=1;i--)
    	if(last>a[i]&&!v[i])
    		ans++, last=a[i];
    write(ans), putchar('\n'), memset(v, 0, sizeof(v)), last=-1; 
    for(int i=1;i<=n;i++)
        if(last<a[i])
            write(a[i]), putchar(' '), last=a[i], v[i]=1;
    for(int i=n;i>=1;i--)
    	if(last>a[i]&&!v[i])
    		write(a[i]), putchar(' '), last=a[i];
	return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

在序列 $b$ 中拿一些数组成山峰序列 $a$，使之长度最大。

## 解法

设 $a$ 长度为 $n$，给 $b$ 从小到大排序。

呃，题面只说了要 $a_1<a_2<\dots<a_i>a_{i+1}>\dots>a_n$，但是没有说 $i$ 是多少诶。

所以看到第一个样例，是不是直接把数组从小到大排序，再取其中**不重复**的数组成一个上升序列，让 $i=n$ 就行了咩？


```cpp
#include <bits/stdc++.h>
using namespace std;

int m,b[100001],a[100001],n;

signed main()
{
	scanf("%d",&m);
	for(int i = 1;i <= m;i++) scanf("%d",&b[i]);
	sort(b + 1,b + m + 1);
	for(int i = 1;i <= m;i++){if(b[i] != b[i - 1]) a[++n] = b[i];}
    printf("%d\n",n);
    for(int i = 1;i <= n;i++) printf("%d ",a[i]);
	return 0;
}
```

呃，好像第二个样例就错了。

于是又发现， $b$ 里面有些数因为在组成上升序列时用过同样的数，所以并没有被使用过。所以我们用一个 $is$ 数组存每个数有没有用过，还没用过就再接在 $a$ 后面组成下降数列，即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int m,b[100001],a[100001],n;
bool is[100001];

signed main()
{
	scanf("%d",&m);
	for(int i = 1;i <= m;i++) scanf("%d",&b[i]);
	sort(b + 1,b + m + 1);//排序
	for(int i = 1;i <= m;i++) if(b[i] != b[i - 1]){a[++n] = b[i];is[i] = true;}//不重复的数
	for(int i = m;i >= 1;i--) if(!is[i] && a[n] != b[i]) a[++n] = b[i];//没用过且不重复
    printf("%d\n",n);
    for(int i = 1;i <= n;i++) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：WJX114514 (赞：0)

#### 我们先理解题意，大致意思是：
给你一个序列让你组成一个中间有一个数，左侧递增右侧递减的数列。
#### 从这道题的题意来看，大概思路是：
1. 我们要将最大值设为中间的数，然后左右两端尽可能的小。
2. 跑两遍循环，分别为左边的递增边的递减。
3. 还有，因为一个数可以出现很多次，我们需要一个 vis 数组来存储此位置是否被使用过。
4. 最后，我采用的是开两个 vector 来存储左边的上升，和右边的下降。
#### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010];
bool vis[100010];
vector<int> up;//上升部分 
vector<int> down;//下降部分 
int main(){
	int m;
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	sort(a+1,a+m+1);
	down.push_back(a[m]);
	vis[m]=true;
	for(int i=m-1;i>=1;i--){
		if(a[i]<a[i+1]){
			down.push_back(a[i]);
			vis[i]=true;
		}
	}
	int top=0;
	for(int i=1;i<=m;i++){
		if(vis[i]!=true&&a[i]>top&&a[i]<a[m]){
			vis[i]=true;
			top=a[i];
			up.push_back(a[i]);
		}
	}
	cout<<up.size()+down.size()<<endl;
	for(int i=0;i<up.size();i++){
		cout<<up[i]<<" ";
	}
	for(int i=0;i<down.size();i++){
		cout<<down[i]<<" ";
	}
	return 0;
}
```
代码较为丑陋，仅供参考。\
完结撒花。

---

## 作者：Little_Cabbage (赞：0)

> 涉及知识点：构造。

# 解题思路

题目要求 $a$ 的长度要最长，所以需要 $a_1\sim a_i$ 和 $a_i \sim a_{|a|}$ 最长，于是直接构造一个单调递增和单调递减的序列即可。

由于数据较小，可利用桶通过此题。

注意：

- $a_1\sim a_{i-1}$ 与 $a_{i + 1} \sim a_{|a|}$ 中可以有重复的元元素，但不能有两个 $a_i$。


# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll __int128
#define db double
#define ldb long double
#define vo void
#define endl '\n'
#define il inline
#define re register
#define ve vector
#define p_q priority_queue
#define PII pair<int, int>
#define u_m unordered_map
#define bt bitset

using namespace std;

//#define O2 1
#ifdef O2
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
#endif

struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
	char buf[MAXSIZE], *p1, *p2;
	char pbuf[MAXSIZE], *pp;
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	
	~IO() {
		fwrite(pbuf, 1, pp - pbuf, stdout);
	}
	char gc() {
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}
	
	bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	
	template <class T>
	void read(T &x) {
		double tmp = 1;
		bool sign = 0;
		x = 0;
		char ch = gc();
		while (!isdigit(ch)) {
			if (ch == '-') sign = 1;
			ch = gc();
		}
		while (isdigit(ch)) {
			x = x * 10 + (ch - '0');
			ch = gc();
		}
		if (ch == '.') {
			ch = gc();
			while (isdigit(ch)) {
				tmp /= 10.0, x += tmp * (ch - '0');
				ch = gc();
			}
		}
		if (sign) x = -x;
	}
	
	void read(char *s) {
		char ch = gc();
		for (; blank(ch); ch = gc());
		for (; !blank(ch); ch = gc()) * s++ = ch;
		*s = 0;
	}
	
	void read(char &c) {
		for (c = gc(); blank(c); c = gc());
	}
	
	void push(const char &c) {
		if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
		*pp++ = c;
	}
	
	template <class T>
	void write(T x) {
		if (x < 0) x = -x, push('-');
		static T sta[35];
		T top = 0;
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x);
		while (top) push(sta[--top] + '0');
	}
	
	template <class T>
	void write(T x, char lastChar) {
		write(x), push(lastChar);
	}
} io;

namespace COMB {
	int fact[200000];
	int Triangle[1010][1010];
	void Fact(int n, int mod) {
		fact[0] = 1;
		for (int i = 1; i <= n; i ++ ) fact[i] = ((fact[i - 1]) % mod * (i % mod)) % mod;
	}
	void Pascal_s_triangle(int n, int mod) {
		for (int i = 0; i <= n; i ++ ) Triangle[i][0] = 1;
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= i; j ++ )
				Triangle[i][j] = (Triangle[i - 1][j] + Triangle[i - 1][j - 1]) % mod;
	}
	int pw(int x, int y, int mod) {
		int res = 1;
		while (y) {
			if (y & 1) res = ((res % mod) * (x % mod)) % mod;
			x = (x % mod) * (x % mod) % mod;
			y >>= 1;
		}
		return res;
	}
	int pw(int x, int y) {
		int res = 1;
		while (y) {
			if (y & 1) res *= x;
			x *= x;
			y >>= 1;
		}
		return res;
	}
	int GCD(int x, int y, int mod) {
		return __gcd(x, y) % mod;
	}
	int LCM(int x, int y, int mod) {
		return (((x % mod) * (y % mod)) % mod / (GCD(x, y, mod) % mod)) % mod;
	}
	int C(int n, int m, int mod) {
		if (m > n || m < 0) return 0;
		return fact[n] * pw(fact[m], mod - 2, mod) % mod * pw(fact[n - m], mod - 2, mod) % mod;
	}
	int Ask_triangle(int x, int y) {
		return Triangle[x][y];
	}
}
using namespace COMB;

//#define fre 1
#define IOS 1
//#define multitest 1

const int N = 4e6 + 10;
const int M = 4e5 + 10;
const int inf = 1e12;
const int Mod = 1e9 + 9;

namespace zla {
	int n, a[N], t[N], ans[N], len;
	
	il void Init() {
		cin >> n;
		for (int i = 1; i <= n; i ++ ) {
			cin >> a[i];
			t[a[i]] ++;
		}
	}
	
	il void Solve() {
		for (int i = 1; i <= 5000; i ++ ) {
			if (t[i]) {
				ans[++ len] = i;
				t[i] --;
			}
		}
		int T = ans[len - 1];
		for (int i = T; i >= 1; i -- )
			if (t[i]) {
				ans[++ len] = i;
				t[i] --;
			}
		cout << len << endl;
		for (int i = 1; i <= len; i ++ ) cout << ans[i] << " ";
	}
	
	il void main() {
		Init();
		Solve();
	}
}

signed main() {
	int T;
#ifdef IOS
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
#ifdef fre
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
#ifdef multitest
	cin >> T;
#else
	T = 1;
#endif
	while (T--) zla::main();
	return 0;
}
```

---

