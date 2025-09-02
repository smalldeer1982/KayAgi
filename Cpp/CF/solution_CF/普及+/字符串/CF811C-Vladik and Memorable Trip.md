# Vladik and Memorable Trip

## 题目描述

Vladik often travels by trains. He remembered some of his trips especially well and I would like to tell you about one of these trips:

Vladik is at initial train station, and now $ n $ people (including Vladik) want to get on the train. They are already lined up in some order, and for each of them the city code $ a_{i} $ is known (the code of the city in which they are going to).

Train chief selects some number of disjoint segments of the original sequence of people (covering entire sequence by segments is not necessary). People who are in the same segment will be in the same train carriage. The segments are selected in such way that if at least one person travels to the city $ x $ , then all people who are going to city $ x $ should be in the same railway carriage. This means that they can’t belong to different segments. Note, that all people who travel to the city $ x $ , either go to it and in the same railway carriage, or do not go anywhere at all.

Comfort of a train trip with people on segment from position $ l $ to position $ r $ is equal to XOR of all distinct codes of cities for people on the segment from position $ l $ to position $ r $ . XOR operation also known as exclusive OR.

Total comfort of a train trip is equal to sum of comfort for each segment.

Help Vladik to know maximal possible total comfort.

## 说明/提示

In the first test case best partition into segments is: $ [4,4] $ $ [2,5,2] $ $ [3] $ , answer is calculated as follows: $ 4+(2 $ $ xor $ $ 5)+3=4+7+3=14 $

In the second test case best partition into segments is: $ 5 $ $ 1 $ $ [3] $ $ 1 $ $ 5 $ $ [2,4,2] $ $ 5 $ , answer calculated as follows: $ 3+(2 $ $ xor $ $ 4)=3+6=9 $ .

## 样例 #1

### 输入

```
6
4 4 2 5 2 3
```

### 输出

```
14
```

## 样例 #2

### 输入

```
9
5 1 3 1 5 2 4 2 5
```

### 输出

```
9
```

# 题解

## 作者：hwk0518 (赞：3)

定义变量$g[i][j]$，当区间$[i,j]$合法时，$g[i][j]$为所有在区间$[i,j]$中的不同数异或和；否则$g[i][j]=0$.

定义变量$f[i][j]$，表示所有满足$i<=l<=r<=j$且合法的$[l,r]$中,$g[i][j]$最大是多少。可以用区间$DP$，枚举长度$len$后转移：

$f[i][j]=max(f[i][j-1],f[i+1][j],g[i][j])$

于是设$dp[i]$表示在$[1,i]$中选择若干区间，且最后一个区间的右端点为$i$，所有区间和最大是多少。转移方程为：

$dp[i]=max_{j=0\to i-1}dp[j]+f[j+1][i]$

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=5005;
int n,a[N],f[N][N],dp[N];
int l[N],r[N],cnt[N],used[N];

void init()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
		scanf("%d",&a[i]),++cnt[a[i]];
	for(i=n;i;--i) l[a[i]]=i;
	for(i=1;i<=n;++i) r[a[i]]=i; 
}

void calc(int lpos)
{
	int i,nowri=0,nowcnt=0;
	for(i=5000;~i;--i) used[i]=0;
	int now=0;
	for(i=lpos;i<=n;++i)
		if(!used[a[i]])
		{
			used[a[i]]=1;now^=a[i];
			if(l[a[i]]<lpos) return;
			nowri=max(nowri,r[a[i]]);
			nowcnt+=cnt[a[i]];
			if(nowri-lpos+1==nowcnt) f[lpos][nowri]=now;
		}
}

void work()
{
	int i,j,len,l,r;
	for(i=1;i<=n;++i) calc(i);
	for(len=2;len<=n;++len)
		for(l=1;l<=n-len+1;++l)
		{
			r=l+len-1;
			f[l][r]=max(f[l][r],max(f[l][r-1],f[l+1][r]));
		}
		
	for(i=1;i<=n;++i)
		for(j=0;j<i;++j)
			dp[i]=max(dp[i],dp[j]+f[j+1][i]);
	
	int ans=0;
	for(i=1;i<=n;++i) ans=max(ans,dp[i]);
	printf("%d\n",ans);
}

int main()
{
	init();work();
	return 0;
}

```

---

## 作者：lgx57 (赞：1)

非常简单的 dp。

只需要暴力枚举每一个区间，然后判断合法后直接转移即可。

但是普通的判断合法会 TLE，需要预处理出每一个数在整个数组里的出现次数，然后把一个区间里的数全部插入到 set 中，遍历 set，如果在区间中出现次数等于整个数组中的出现次数，那么下次就不用判断，直接 erase，否则这个区间是不合法的。

另外注意没有区间可以转移时 $dp_i \gets dp_{i-1}$。
```cpp
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) num[a[i]]++,ma=max(ma,a[i]);
	for (int i=1;i<=n;i++){
		for (int _=0;_<=ma;_++) cnt[_]=0;
		int sum=0;
		set<int> s;
		for (int j=i;j>=1;j--){
			bool f=1;
			if (!cnt[a[j]]) sum^=a[j],s.insert(a[j]);
			cnt[a[j]]++;
			vector<int> v;
			for (int x:s){
				if (cnt[x]!=num[x]){
					f=0;//不合法
					break;
				}
				else v.pb(x);
			}
			for (int x:v) s.erase(x);//下次不需要判断
			if (f) dp[i]=max(dp[j-1]+sum,dp[i]);//直接转移
		}
		dp[i]=max(dp[i],dp[i-1]);//没有区间可以转移
	}
	cout<<dp[n];
	return 0;
}
```

---

## 作者：猪小屁 (赞：1)

  看n很小，又是**最优解**，容易想到

------------
~~暴力~~dp

   一开始设计dp[i],以i必须是合法区间的右端点
    
   后来想了想 ，发现合法区间很难找，所以就干脆暴力一点
    
   这个i就从1到n枚举，反正非法状态也转移不过来
    
   就是初始的0，也不会影响最大值
    
   然后方程易得
   
   **dp[i]=max(dp[k])+sum**
   
   因为j它不一定是合法区间右端点，所以我们要记录在j之前的合法值得最大dp值，转移过来
   
   代码如下
   ```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e3+5;
int a[maxn],num[maxn],cnt[maxn];
long long dp[maxn],maxx[maxn];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		num[a[i]]++;
	} 
	for(int i=1;i<=n;i++){
		int no=0;//判断区间[j,i]是否合法 
		int sum=0;
		memset(cnt,0,sizeof(cnt));
		for(int j=i;j>=1;j--){
			if(!cnt[a[j]]){
				no++;//遇到一个新数就把no加 
				sum^=a[j];//有多个数，只算一次异或 
			}
			cnt[a[j]]++;
			if(cnt[a[j]]==num[a[j]]) no--;
			if(!no){
				dp[i]=max(dp[i],maxx[j-1]+sum);//maxx[j]里存的是max(dp[k]),1<=k<=j;
			}
		}
		maxx[i]=max(maxx[i-1],dp[i]);//由i-1前最大dp值和当前dp值取max，注意是i-1，不然只会取到dp[i] 
	}
	printf("%lld\n",maxx[n]);
	return 0;
}
```


---

