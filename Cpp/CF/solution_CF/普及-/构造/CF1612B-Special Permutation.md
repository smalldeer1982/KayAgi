# Special Permutation

## 题目描述

A permutation of length $ n $ is an array $ p=[p_1,p_2,\dots, p_n] $ which contains every integer from $ 1 $ to $ n $ (inclusive) exactly once. For example, $ p=[4, 2, 6, 5, 3, 1] $ is a permutation of length $ 6 $ .

You are given three integers $ n $ , $ a $ and $ b $ , where $ n $ is an even number. Print any permutation of length $ n $ that the minimum among all its elements of the left half equals $ a $ and the maximum among all its elements of the right half equals $ b $ . Print -1 if no such permutation exists.

## 样例 #1

### 输入

```
7
6 2 5
6 1 3
6 4 3
4 2 4
10 5 3
2 1 2
2 2 1```

### 输出

```
4 2 6 5 3 1
-1
6 4 5 1 3 2 
3 2 4 1 
-1
1 2 
2 1```

# 题解

## 作者：Jur_Cai (赞：2)

### 题意
构造一个长为 $n$ 的排列，使前 $\frac{n}{2}$ 个数中最小值为 $a$，使后 $\frac{n}{2}$ 个数中最大值为 $b$。
### 分析
由于是排列，每个数只出现一次，所以前半段先填一个 $a$，后半段先填一个$b$，剩下的数从大到小，从前向后填 ( 因为前面要最小值，所以填的剩下的数要尽可能大，后半段同理 )。如果不合法则无解。

直接实现即可。
``` cpp
#include<bits/stdc++.h>
using namespace std;
int ans[105];
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int n,a,b;
		scanf("%d",&n);
		scanf("%d%d",&a,&b);
		int now=n,minn=a,maxn=b;
		ans[1]=a;
		for(int i=2; i<=n/2; i++) {
			while(now==a||now==b) now--;
			ans[i]=now,minn=min(minn,ans[i]),now--;
		}
		ans[n/2+1]=b;
		for(int i=n/2+2; i<=n; i++) {
			while(now==a||now==b) now--;
			ans[i]=now,maxn=max(maxn,ans[i]),now--;
		}
		if(minn!=a||maxn!=b) puts("-1");
		else {
			for(int i=1; i<=n; i++) cout<<ans[i]<<" ";
			cout<<'\n';
		}
	}
}
//可以O(1)直接判断，但赛时为了方便就直接写的O(n)
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15782631.html)

# 题目大意

构造一个长度为 $n$ 的排列 $p$，使得 $p_{[1,{\frac{n}{2}}]}$ 中的最小值为 $a$，使得 $p_{[{\frac{n}{2}} + 1, n]}$ 中的最大值为 $b$。

如果没有合法的排列，输出 $-1$。

# 题目分析

将答案序列存到 $ans$ 数组中，令 $m=\dfrac{n}{2}$。

让 $ans[1]=a,ans[m+1]=b$，随后我们只需要在 $2\sim m$ 和 $m+1\sim n$ 中填入数字即可。

填的时候注意不要重复，可以采取倒序的方式填，如果当前填的数与 $a$ 或 $b$ 相等那么不能填，再将数减一。

最后扫一遍序列，如果 $\min\limits_{i=1}^{m}\{ans[i]\}\neq a,\max\limits_{i=m+1}^n\{ans[i]\}\neq b$ 表示不满条件。

# 代码

```cpp
//2022/1/9

using namespace std;

const int INF=0x3f3f3f3f;

const int ma=105;

int ans[ma];

int T,n,a,b;

inline void solve()
{
	n=read(),a=read(),b=read();
	
	int m=n/2;
	
	mst(ans,0);
	
	ans[1]=a,ans[m+1]=b;
	
	int num=n+1;
	
	for(register int i=1;i<=n;i++)
	{
		if(ans[i]==0)
		{
			num--;
			
			while(num==a || num==b)
			{
				num--;
			}
			
			ans[i]=num;
		}
	}
	
	int minn=INF,maxx=-INF;
	
	for(register int i=1;i<=n;i++)
	{
		if(i<=m)
		{
			minn=min(minn,ans[i]); 
		}
		
		else
		{
			maxx=max(maxx,ans[i]);
		}
	}
	
	if(minn!=a || maxx!=b)
	{
		puts("-1");
	}
	
	else
	{
		blow(ans,1,n," ");
		
		enter();
	}
}

int main(void)
{
	T=read();
	
	while(T--)
	{
		solve();
	}
	
	return 0;
}
```

---

## 作者：Terraria (赞：0)

## $\texttt{Introduction}$

构造一个长度为 $n$ 的排列 $p$。记 $m= \dfrac{n}{2}$。

使得 $\min\{p_1,p_2,\cdots,p_m\}=a,\max\{p_{m+1},p_{m+2},\cdots,p_n\}=b$。

保证 $n$ 为偶数。

~~另外洛谷巨大的分数下标什么时候能修一下。~~

## $\texttt{Solution}$

还是记 $m= \dfrac{n}{2}$。

由于题目要求的 $\min\{p_1,p_2,\cdots,p_m\}=a,\max\{p_{m+1},p_{m+2},\cdots,p_n\}=b$，我们不妨先令 $ans_1=a,ans_{m+1}=b$。

由于要使前 $m$ 个数的最小值为 $a$，那么我们要尽量让前 $m-1$ 个数大。同理，我们要让后 $m$ 个数中的其余 $m-1$ 个数尽量小。

又由于题目限制相当于把构造好的数列分成为两个部分，每个部分相互独立，且

- 第一个部分要求 $m-1$ 个数尽量大；

- 第二个部分要求 $m-1$ 个数尽量小；

- 一个部分内的数的位置没有任何影响。

所以我们可以贪心，把 $1 \sim n$ 较大且未填过的数，选 $m-1$ 大的数填入前 $m-1$ 个位置，其余的数填后面的位置。

所以，大致思路出来了：

- 填入 $a,b$；

- 从大到小，按照下标 $1 \sim n$ 的顺序，依次填入未使用过的数；

- 对填写完毕的数组检验。

## $\texttt{Code}$

代码实现有一些小细节：

- 由于在填数中，从大到小减一后可能等于 $a,b$，要判断一下。

- 由于是先自减，再填数，所以初始值要赋值为 $n+1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int ans[109];
void solve(){
	int n,a,b;
	cin>>n>>a>>b;
	memset(ans,0,sizeof(ans));
	ans[1]=a,ans[n/2+1]=b;
	int now=n+1;
	for(int i=1;i<=n;i++){
		if(ans[i]==0){
			now--;
			while(now==a||now==b) now--;
			ans[i]=now;
		}
	}
	int Min=1000,Max=-1000;
	for(int i=1;i<=n;i++){
		if(i<=n/2) Min=min(Min,ans[i]);
		if(i>n/2) Max=max(Max,ans[i]);
	}
	if(Min!=a||Max!=b){
		cout<<"-1"<<endl;
		return ;
	}
	else{
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		cout<<endl;
		return;
	}
}
int main(){
	cin>>T;
	while(T--) solve();
}
```


---

## 作者：miao5 (赞：0)

这道题可以暴力统计来做，时间复杂度 $O(Tn)$。

首先题面说 $a$ 是 $p[1,\frac{n}{2}]$  中最小的数，那么 $a$ 一定在 $p[2,\frac{n}{2}]$ 中，之后我们就需要找到 $\frac{n}{2}-1$ 个比 $a$ 大的数填到 $p[1,\frac{n}{2}]$ 这个区间里面，但是必须排除 $b$，因为 $b$ 是应该在 $p[\frac{n}{2}+1,n]$ 这个区间中的，这个过程可以通过将一个变量从小到大枚举来贪心找较大的数实现。关于后半段同理。

之后我们来考虑无解判定，我们可以维护一个前半段最小值和后半段最大值，最后判断相等就可以了。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int ans[105];
int n,a,b;
bool check(int k){
	if(k==a||k==b) return true;
	else return false;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(ans,0,sizeof(ans));
		cin>>n>>a>>b;
		int k=n;
		int mx=b;
		int mn=a;
		ans[1]=a;
		for(int i=2;i<=n/2;i++){
			while(check(k)) k--;
			ans[i]=k;
			mn=min(mn,k);
			k--;
		}
		ans[n/2+1]=b;
		for(int i=n/2+2;i<=n;i++){
			while(check(k)) k--;
			ans[i]=k;
			mx=max(mx,k);
			k--;
		}
		if(mx!=b||mn!=a) cout<<-1<<endl;
		else{
			for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
			cout<<endl;
		}
	}
}
```

---

## 作者：Aiopr_2378 (赞：0)

### 题目大意：

构造一个长度为 $n$ 的序列 $p$，使得 $p_{[1,{\frac{n}{2}}]}$ 中的最小值为 $a$，使得 $p_{[{\frac{n}{2}} + 1, n]}$ 中的最大值为 $b$。

如果没有合法的序列，输出 $-1$。

### 思路分析：

对于每一个独立的询问，题目中要求前 $\frac{n}{2}$ 个数最小为 $a$，后 $\frac{n}{2}$ 个数最大为 $b$。

那我们就可以在前 $\frac{n}{2}$ 个数中，依次找到未使用的最大数，然后使用；在后 $\frac{n}{2}$ 个数中，依次找到未使用的最小的数，然后使用。如果这样操作后，数组与题目相悖，则无解。

但是要注意，$a$ 和 $b$ 是要分别放在两边的哦~

建议设一个数组，标记一个数是否被使用过，这样可以降低思维难度。

若不明白可以看看参考代码哈

### 参考代码：

以下代码仅供参考

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int t,n,a,b,ans[105];
bool vis[105];
int main(){
    cin>>t;
    while(t--){
        cin>>n>>a>>b;
        int cnt=1;
        ans[1]=a;
        memset(vis,0,sizeof(vis));
        vis[a]=vis[b]=1;
        for(int i=n;cnt<n/2;i--){
            if(vis[i]==0){
                ans[++cnt]=i;
                vis[i]=1;
            }
        }
        ans[++cnt]=b;
        for(int i=1;cnt<n;i++){
            if(vis[i]==0){
                ans[++cnt]=i;
                vis[i]=1;
            }
        }
        bool k=1;
        for(int i=1;i<=n/2;i++){
            if(k&&ans[i]<a){
                cout<<-1;
                k=0;
            }
        }
        for(int i=n/2+1;i<=n;i++){
            if(k&&ans[i]>b){
                cout<<-1;
                k=0;
            }
        }
        if(k){
            for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：BFSDFS123 (赞：0)

**题目大意**

让你构造一个长度为 $n$ 的排列，要求：

- $[1,\dfrac{n}{2}]$ 中的所有数都大于等于 $a$。

- $[\dfrac{n}{2}+1,n]$ 中的所有数都小于等于 $b$。

**题解**

本质上是一道思维题，适合数竞的同学们练手，也适合初学构造题的同学们。

我们发现，只要把小于 $a$ 的放到右面，大于 $b$ 的放到左面，$a$ 放到左面，$b$ 放到右面。剩下的数就可以随便放了。

在判断一下是否成立就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> Zuo;
vector<int> You;
int flag[110];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		You.clear();
		Zuo.clear();
		memset(flag,0,sizeof(flag));
		int n,a,b;
		scanf("%d%d%d",&n,&a,&b);
//		if(a+b<n)
//		{
//			puts("-1");
//			continue;
//		}
		for(int i=1;i<a;i++)
		{
			You.push_back(i);
		}
		for(int i=n;i>b;i--)
		{
			Zuo.push_back(i);
		}
		int Zuol=Zuo.size();
		int Youl=You.size();
		bool S=false;
		if(a>b) swap(a,b),S=true;
		for(int i=a;i<=b;i++)
		{
			if(Zuol<(n/2))
			{
				Zuo.push_back(i);
				Zuol++;
				continue;
			}
			if(Youl<(n/2))
			{
				You.push_back(i);
				Youl++; 
			}
		}
		if(S) swap(a,b);
		vector<int> ans;
		ans.clear();
		for(auto i:Zuo) ans.push_back(i);
		for(auto i:You) ans.push_back(i);
		for(auto i:ans)
		{
			//cout<<i<<" ";
			flag[i]++;
		}
		bool ded=false;
		if(ans.size()!=n) ded=true;
		for(int i=1;i<=n;i++)
		{
			if(flag[i]==0)
			{
				ded=true;
				break;
			}
		}
		bool Has1=false,Has2=false;
		bool dow1=false,dow2=false;
		for(auto i:Zuo)
		{
			if(i==a)
			{
				Has1=true;
				//puts("G");
			}
			if(i<a)
			{
				dow1=true;
				break;
			}
		}
		for(auto i:You)
		{
			if(i==b)
			{
				Has2=true;
			//	puts("G");
			}
			if(i>b)
			{
				dow2=true;
				break;
			}
		}
		//if(!Has1 || !Has2)cout<<"KO"<<endl;
		if(!Has1 || !Has2) ded=true;
		if(dow1 || dow2) ded=true;
		if(ded) puts("-1");
		else
		{
			for(auto i:ans)
			{
				printf("%d ",i);
			}
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1612B Special Permutation 题解

## 题目大意

给定三个整数 $n$ ， $a$ ， $b$，让你求出 $1 \sim n$ 的一种全排列满足：该排列的左半部分的最小值是 $a$，右半部分的最大值是 $b$，无解时输出 "-1" 。 ( 保证 $n$ 是偶数 )

## 思路分析

显然：$a$ 在左半部分，$b$ 在右半部分。

因为 $a$ 是左半部分的最小值，所以所有小于 $a$ 的数都在右半部分。

同理，所有大于 $b$ 的部分都在左半部分。

剩余在区间 $(a,b)$ 的数，我们让较小的一些放在左半部分，较大的一些放在右半部分。

任何时候如果已经访问过已取走的数，那么直接输出无解信息。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> fnt,bck;
//fnt是排列的左半部分，bck是排列的右半部分 
bool vis[101];//vis保存是否选过 
inline void solve(int n,int a,int b) {
	int m=n>>1;
	memset(vis,false,sizeof(vis));
	fnt.clear();
	bck.clear();
	//将a,b分别放进排列的左半部分和右半部分里面 
	fnt.push_back(a);
	bck.push_back(b);
	vis[a]=vis[b]=true;
	for(register int i=1;bck.size()<m&&i<a;++i) {
		//把小于a的放进后半部分 
		bck.push_back(i);
		if(vis[i]) {
			//如果这个数已经选过就直接输出无解信息 
			puts("-1");
			return ;
		}
		vis[i]=true;
	}
	for(register int i=n;fnt.size()<m&&i>b;--i) {
		//把大于b的放进右半部分 
		fnt.push_back(i);
		if(vis[i]) {
			//如果这个数已经选过就直接输出无解信息 
			puts("-1");
			return ;
		}
		vis[i]=true;
	}
	for(register int i=a+1;fnt.size()<m;++i) {
		//将(a,b)中较小的放进左半部分 
		fnt.push_back(i);
		if(vis[i]) {
			//如果这个数已经选过就直接输出无解信息 
			puts("-1");
			return ;
		}
		vis[i]=true;
	}
	for(register int i=b-1;bck.size()<m;--i) {
		//将(a,b)中较大的放进右半部分 
		bck.push_back(i);
		if(vis[i]) {
			//如果这个数已经选过就直接输出无解信息 
			puts("-1");
			return ;
		}
		vis[i]=true;
	}
	if(fnt.size()!=m||bck.size()!=m) {
		//如果前后部分不是各恰好一半，直接无解
		puts("-1");
		return ;
	}
	//输出 
	for(register auto i:fnt) printf("%d ",i);
	for(register auto i:bck) printf("%d ",i);
	putchar('\n');
	return ;
}
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int n,a,b;
		scanf("%d%d%d",&n,&a,&b);
		solve(n,a,b);
	}
	return 0;
}
```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1612B)


题意：给定 $n,a,b$，要求构造一个长度为 $n$ 的排列（$1 \sim n$ 每个数出现一次），排列的左半部分最小值为 $a$，右半部分最大值为 $b$，有解输出任意一组，无解输出 $-1$，保证 $n$ 为偶数。

考虑贪心，左半部分需要最小值为 $a$，那就从 $a+1$ 开始往后填即可。右半部分需要最大值为 $b$，那就从 $b-1$ 开始往后填。

注意同一个数字不能反复使用，因此扫过去的时候要记录一下每个数是否被访问过。如果任一部分填不满就无解。

时间复杂度 $O(tn)$。

---

