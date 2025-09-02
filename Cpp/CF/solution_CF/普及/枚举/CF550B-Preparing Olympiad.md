# Preparing Olympiad

## 题目描述

You have $ n $ problems. You have estimated the difficulty of the $ i $ -th one as integer $ c_{i} $ . Now you want to prepare a problemset for a contest, using some of the problems you've made.

A problemset for the contest must consist of at least two problems. You think that the total difficulty of the problems of the contest must be at least $ l $ and at most $ r $ . Also, you think that the difference between difficulties of the easiest and the hardest of the chosen problems must be at least $ x $ .

Find the number of ways to choose a problemset for the contest.

## 说明/提示

In the first example two sets are suitable, one consisting of the second and third problem, another one consisting of all three problems.

In the second example, two sets of problems are suitable — the set of problems with difficulties 10 and 30 as well as the set of problems with difficulties 20 and 30.

In the third example any set consisting of one problem of difficulty 10 and one problem of difficulty 20 is suitable.

## 样例 #1

### 输入

```
3 5 6 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 40 50 10
10 20 30 25
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 25 35 10
10 10 20 10 20
```

### 输出

```
6
```

# 题解

## 作者：Z_M__ (赞：7)

因为 $n \le 15$ , 所以可以枚举所有方案（包括不合法的），每一位数只有选与不选两个情况，所以所有方案数则为 $2^n$ ,再将判断一下那些方案合法，统计到答案即可。

```cpp#include <bits/stdc++.h>
using namespace std;
const int MAXN = 15 + 10;
int n, L, R, X, l, r, ans;
int a[MAXN];
int main ()
{
    ios :: sync_with_stdio (0), cin.tie (0);
    cin >> n >> L >> R >> X;
    for (int i = 1; i <= n; i++)
    	cin >> a[i];
    sort (a + 1, a + n + 1); // 排序一下让统计方案中的最大值和最小值方便一点
    for (int i = 0; i <= (1 << n) - 1; i++) // 枚举所有方案
    {
    	int minn = n, maxn = 1, sum = 0;
    	for (int j = 0; (1 << j) <= i; j++) // 将方案的二进制拆开
    	{
    		if ((1 << j) & i)
    		{
    			minn = min (minn, j + 1);
    			maxn = max (maxn, j + 1);
    			sum += a[j + 1];
    		}
    	}
    	if (sum >= L && sum <= R && a[maxn] - a[minn] >= X) // 判断该方案是否合法
    		ans++;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：ChrisWangZi (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF550B)

与这道题相近的题目是：[P2036 [COCI2008-2009#2] PERKET](https://www.luogu.com.cn/problem/P2036)
（大家可以看一下这道题）

题目大概就是：给定 $n$ 个数，从中选出一些数，保证这些数之和在 $[l,r]$的范围里，并且最大数和最小数的差大于等于 $x$ 。

## 思路：

一上来，就想到了二进制枚举。

（枚举每个数的“选”和“不选”）

再加上 $1 \le n \le 15$ 的数据范围，（$2^{15} \approx 30000$）这道题就用枚举 $+$ dfs 。

## $AC$代码:

```cpp
#include<iostream>
using namespace std;
int c[20];
int ans;
int n,l,r,x;
void dfs(int k/*已做过选择的数量(不一定选中)*/,int dif/*难度和*/,int minn/*最小难度*/,int maxn/*最大难度*/,int cnt/*已选中的课程数量*/){
	if(k==n){
		if(dif>=l&&dif<=r&&maxn-minn>=x&&cnt!=0){//判断该选课是否合法 
			ans++;
		}
		return;
	}
	dfs(k+1,dif+c[k+1],min(minn,c[k+1]),max(maxn,c[k+1]),cnt+1);//选 
	dfs(k+1,dif,minn,maxn,cnt);//不选 
}
int main(){
	scanf("%d%d%d%d",&n,&l,&r,&x);
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
	}
	dfs(0,0,1e6+1,0,0);
	cout<<ans;
	return 0;
}

```

~~点个赞再走呗~~

---

## 作者：_xbn (赞：4)

分析：

题目要求我们选几个题，那么每个题就有选和不选两种状态，看到 $n$ 很小，那我们就可以枚举出每一种状态，再判断每一种状态是否合法。将合法状态加入答案即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100002;	
int n,l,r,x,a[N];
ll ans;
int main()
{
	cin >>n>>l>>r>>x;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=0;i<(1<<n);i++)
	{
		int k=1,mn=2e9,mx=0,sum=0;
		for(int j=i;j;j=j/2)
		{
			if(j&1)
			{
				mn = min(mn,a[k]);
				mx = max(mx,a[k]);
				sum += a[k];
			}
			k++;
		}
		if(mx-mn>=x&&sum>=l&&sum<=r)ans++;
	}
	cout << ans <<endl;
}

```



---

## 作者：きりと (赞：2)

### 题目大意

见中文翻译。

### 解题思路

看了一圈发现题解区大佬们怎么都会一堆AK方法![q](https://xn--9zr.tk/wq)。像我这种彩笔就只会直接暴搜，泪目了。

然而AK做法似乎没什么用，比开了O2的无卡常暴搜慢了一半……

~~哦复杂度本来就是一样的，那没事了。~~

对于每一道题目，考虑挑或不挑，一遍扫下来判一下是否符合题设条件， 更新 $ans$ 就彳亍了。

时间复杂度 $O(2^n)$，随便过。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define forr(i,l,r) for(int i=l;i<=r;i++)
#define ffor(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
const int inf=1e9+7;
int a[16],ans;
int n,l,r,x;
void dfs(int p,int s,int maxn,int minn)
{
    if(p>n)
    {
        if(maxn-minn>=x&&s>=l&&s<=r)
        {
            ans++;
        }
        return ;
    }
    dfs(p+1,s+a[p],max(maxn,a[p]),min(minn,a[p]));
    dfs(p+1,s,maxn,minn);
}
signed main()
{
    cin>>n>>l>>r>>x;
    forr(i,1,n)
    {
        cin>>a[i];
    }
    dfs(1,0,0,inf);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：joy2010WonderMaker (赞：0)

这道题评蓝不太合适，黄最多了。

### 题目分析

首先 $n$ 只有15，可以直接暴力枚举所有的方案。

我们可以开一个数组来记录选择过了的数，这样在判断是否合法的时候，就可以直接进行模拟，时间复杂度是 $O(2^nn)$ 的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,x,c[16],rec[16],pos,ans;
void dfs(int ls){//暴力枚举
	if(pos>=2){
		int sum=0,maxn=0,minn=1000005;
		for(int i=1;i<=pos;i++)
			sum+=c[rec[i]],maxn=max(maxn,c[rec[i]]),minn=min(minn,c[rec[i]]);
		if(sum>=l&&sum<=r&&maxn-minn>=x)
			ans++;
	}
	for(int i=ls+1;i<=n;i++)
		rec[++pos]=i,dfs(i),pos--;//记录
}
int main(){
	scanf("%d%d%d%d",&n,&l,&r,&x);
	for(int i=1;i<=n;i++)
		scanf("%d",c+i);
	dfs(0);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：FReQuenter (赞：0)

## 思路：

首先观察数据范围，$n\leq15$，可以二进制穷举每一个 $c_i$ 是否被选择。

关于如何二进制穷举：相当于实现一个二进制数，每次将其加一，然后对于它的每一个二进制位，如果它是 $0$ ，就不选；否则就选。

关于对每一个状态的检查：可以用一个 `vector` 把选中的 $c_i$ 全部选进来，然后依据题意检查当前 `vector` 是否合法即可，合法就将答案加一。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[20],b[20];
signed main(){
	int n,l,r,x,ans=0;
	cin>>n>>l>>r>>x;
	for(int i=1;i<=n;i++) cin>>c[i];
	while(!b[0]){//边界条件，相当于当 b[0]==1 时这个二进制数>2的n次方。
		int k=n;
		while(b[k]) b[k--]=0;
		b[k]=1;
		//枚举状态，相当于b表示的是一个二进制数，每次加1
		vector<int> v;
		for(int i=1;i<=n;i++) if(b[i]) v.push_back(c[i]);
		sort(v.begin(),v.end());
		//排序更方便
		int sum=0;
		for(auto nx:v) sum+=nx;
		if(v.size()) if(abs(v[0]-v[v.size()-1])>=x&&sum>=l&&sum<=r) ans++;
	}
	cout<<ans;
}
```

---

## 作者：€€£ (赞：0)

我不仅想讲讲做法，更想讲讲我做这道题的过程，希望各位能以我为耻，不要犯白痴错误。

首先，我看到题目蓝，直接开始想多项式时间的 DP，然后自闭。

然后，我看到 $n \le 15$，便想到了可以状压记录一种组合方案的最大值，最小值，总和，做一个状压 DP 即可；

然后我开始码，妄图一遍过但是挂的很惨，发现是我的只选择一个数的预处理出错，于是火速改好过了第一个小样例直接交 WA 飞；

此时我的主要部分是这样的

```cpp
for(i=1;i<=n;i++)
{
	scanf("%lld",&b[i]);
	j=(1<<i-1);
	a[j][0]=b[i];
	a[j][1]=b[i];
	a[j][2]=b[i];
}
for(i=1;i<(1<<n);i++)
{
	j=lowbit(i);
	a[i][0]=a[i^j][0]+a[j][0];
	a[i][1]=std::min(a[i^j][1],a[j][1]);
	a[i][2]=std::max(a[i^j][2],a[j][2]);
}
```

后面发现这个代码在算到只有一个数的时候也会出错……

于是更改后通过了此题，但是罚时拉满

希望各位能以这位菜鸡为戒

```cpp
# include <stdio.h>
# include <algorithm>
# define int long long
# define lowbit(x) (x&(-x))
int a[100010][3];
int b[110];
signed main()
{
	int i,j,n,m,l,r,x;
	scanf("%lld%lld%lld%lld",&n,&l,&r,&x);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
		j=(1<<i-1);
		a[j][0]=b[i];
		a[j][1]=b[i];
		a[j][2]=b[i];
	}
	for(i=1;i<(1<<n);i++)
	{
		j=lowbit(i);
		if(a[i][0])
			continue;
		a[i][0]=a[i^j][0]+a[j][0];
		a[i][1]=std::min(a[i^j][1],a[j][1]);
		a[i][2]=std::max(a[i^j][2],a[j][2]);
	}
	int anss=0;
	for(i=1;i<(1<<n);i++)
	{
		if(l<=a[i][0] && a[i][0]<=r && (a[i][2]-a[i][1])>=x)
			anss++;
	}
	printf("%lld",anss);
	return 0;
}
//其中a[i][0]表示和，a[i][1]表示最小值，a[i][2]表示最大值
```

---

## 作者：LYR_ (赞：0)

### 和楼上大佬思路一致，因为 $1<=n<=15$,所以$01$枚举$dfs$即可。
### 但与楼上不一样的是，我在$dfs$中做了优化：
- 每次 $dfs$ 时将所选题目难度值相加，用 $sum$ 记录。
- 每次 $dfs$ 用 $maxn$ 记录比较已知 $maxn$ 与所选题目难度值。
- $minn$ 与 $maxn$ 记录相反 。
------
$Code$:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=20;
int a[N];
int n,l,r,x;
int ans;
bool check(int sum,int c) { // 判断选出的题目是否符合要求
        if(sum<l || sum>r) return false;
        if(c<x) return false;
        return true;
}
void dfs(int p,int sum,int maxn,int minn) {
        if(p==n+1) {
            if(check(sum,maxn-minn)) ans++;// 符合要求则方案数加1
            return ;// 返回 千万不要忘记
        }
        dfs(p+1,sum+a[p],max(maxn,a[p]),min(minn,a[p])); // 选这个题目
        dfs(p+1,sum,maxn,minn);// 不选
}
int main() {
        cin>>n>>l>>r>>x;
        for(int i=1;i<=n;i++) cin>>a[i];
        dfs(1,0,0,INT_MAX);// 分别记录下标、所选题目难度值之和、最大难度值、最小难度值
        cout<<ans<<endl;
        return 0;
}
```

---

## 作者：灵光一闪 (赞：0)

~~我是这题的第一个题解！作弊党请戳这：~~[代码](https://www.luogu.org/paste/bv5dkjg8)~~注释都删了（我好不好？~~

咳咳咳，谈正事，这题我竟然一遍A了，说明了什么？这题其实细心点就能A

# 讲解区：
这题我瞥一眼就明白了一件事：01枚举就能过！因为n太小了！

好像也没什么好讲的了，然后细节看代码
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#include<string>
#include<map>
using namespace std;
int num[20];
int n,l,r,m;
string s;
int ans;
map <string,bool> mp;//用于判断是否这样取过
bool checker(string s)//这就是我们伟大的checker！
{
    int tep=0;
    int check[20]={0};
    for(int i=0;i<s.size();i++)
        if(s[i]=='1')
            check[tep++]=num[i];//把数组转换一下
    sort(check,check+tep);      //快排
    if((check[tep-1]-check[0])<m)//判断
        return false;
    int q=0;
    for(int i=0;i<tep;i++)
        q+=check[i];
    if(q<l||q>r)		//是不是太难或太简单了
        return false;
    return true;//如果前面都没有return false就return true
}
void dg(string str,int x=0)
{
    if(checker(str)&&mp[str]!=true)//如果取过了就不需要加1了
    {
        ans++;
        mp[str]=true;
    }
    if(x==str.size())//递归到头了
        return;
    dg(str,x+1);//在第x个的时候不取
    str[x]='1';
    dg(str,x+1);//在第x个的时候取
    
//如果有不明白str的变化情况的小伙伴们就在草稿纸上算一下
//实在看不懂就私信我哟
}
int main()
{
    string s="";
    cin>>n>>l>>r>>m;//输入
    for(int i=0;i<n;i++)
    {
        cin>>num[i];
        s=s+'0';//有多少位就加多少个0
    }
    dg(s);//递归
    cout<<ans;
    return 0;
}
```

---

