# Before Exam

## 题目描述

Vasya is about to take his first university exam in about several minutes. And it's not just some ordinary exam, it's on mathematical analysis. Of course, right now Vasya can only think of one thing: what the result of his talk with the examiner will be...

To prepare for the exam, one has to study proofs of $ n $ theorems. It is known that there will be $ k $ examination cards on the exam and each card contains ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF119B/a79102df34bfb4ac36a7e7ca20435b44cb7b516b.png) distinct theorems. Besides, no theorem is mentioned in more than one card (that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF119B/eaf3adf2c359f646a89e2e39756bfd54a8c45754.png) theorems won't be mentioned in any card). During the exam several students may get the same card.

We do not know the exact way theorems are distributed by cards, however the students that took the exam before Vasya told him what theorems their cards contained. Vasya evaluates his level of proficiency in the $ i $ -th theorem by some number $ a_{i} $ . The level of proficiency in some card is the average of the levels of proficiency in the theorems that are included in the card. Now Vasya wants to know the minimally and maximally possible levels of his proficiency in the card he gets on the exam. Vasya wants to determine it by the data he has collected from other students. Unfortunately, Vasya has no time left to do the math and he asked you to help him.

## 说明/提示

Let's analyze the first sample. Vasya's proficiency in the cards whose content he already knows equals $ 6 $ and $ 15.5 $ correspondingly. The three theorems that are left are only enough to make one exam card. If we consider all possible variants of theorems included in the card we can see that in the best case scenario Vasya gets the card that contains theorems $ 4 $ and $ 7 $ (his proficiency would equal $ 15.5 $ ) and in the worst case scenario he gets theorems $ 3 $ and $ 5 $ (his proficiency would equal $ 5 $ ).

The $ ⌊\ x⌋ $ operation denotes taking integer part of real number $ x $ (rounding down).

## 样例 #1

### 输入

```
7 3
7 15 0 19 10 5 12
2
1 6
7 4
```

### 输出

```
5.0000000000 15.5000000000```

## 样例 #2

### 输入

```
4 2
10 8 1 17
2
2 3
3 2
```

### 输出

```
4.5000000000 13.5000000000```

# 题解

## 作者：dxy2020 (赞：2)

# 前言

这题其实挺水的，水一篇题解

# 总体思路

熟练度的最大值是已知卡片中的熟练度的最大值和未出现在卡片中的定理组成的新卡片中的熟练度的最大值中更大的。由于已知卡片的熟练度已知，只要将未出现的卡片排序，取熟练度最大的$\lfloor \frac{n}{k} \rfloor$ 个即可。

最小值同理。

--------------------------------------------------------
# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
using namespace std;
const int N=105;
const double eps=1e-6;
int n,k,q,m;
int a[N],b[N];
bool vis[N];
double minans=100,maxans=0;
inline void in (int &x){  
	int f=1;x=0;char c=getchar();
	while (c>'9'||c<'0'){if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x*=f;
}
signed main(){
	in (n);in (k);
	m=n/k; 
	for (int i=1;i<=n;++i){//读入a数组 
		in (a[i]);
	}
	int x,sum;
	in (q);
	for (int i=1;i<=q;++i){//已参加考试的q个同学所用试卷的最大和最小熟练程度 
		sum=0;
		for (int j=1;j<=m;++j){
			in (x);
			vis[x]=1;
			sum+=a[x];
		}
		minans=min (minans,sum*1./m);
		maxans=max (maxans,sum*1./m);
	}
	int tot=0;
	for (int i=1;i<=n;++i)
		if (!vis[i]) b[++tot]=a[i]; //未在试卷中出现的定理  
	sort (b+1,b+1+tot);//从小到大排序 
	if (tot>=m&&n-tot<k*m){//剩下的定理还能组卷 
		sum=0;
		for (int i=1;i<=m;++i){
			sum+=b[i];//选最小的m个定理组卷 
		}
		minans=min (minans,	sum*1./m);
		sum=0;
		for (int i=tot;i>tot-m;--i){
			sum+=b[i];//选最大的 m 个定理组卷  
		} 
		maxans=max (maxans,sum*1./m); 
	}
	printf ("%.10lf %.10lf\n",minans,maxans);
	return 0;
}

```


---

## 作者：zsyyyy (赞：1)

# CF119B 1900 贪心+模拟

## 题意

一名考生需要学习 $n$ 个定理。有 $k$ 张卡片。考试时，每个定理会被写到 $k$ 张卡片中的至多一张上，每张卡片上会写下 $\lfloor\frac{n}{k}\rfloor$ 个互不相同的定理（换言之，有 $n-\lfloor\frac{n}{k}\rfloor$ 个定理没有被考到）。在考试时，每名学生会拿到一张卡片。不同的学生可能拿到同一张卡片。

我们不知道每个定理被写到了哪张卡片上，不过排在 Vasya 之前的考生都向他透露了他们拿到的卡片上的定理。Vasya 估计他对第 i 个定理的熟练度为 $a_{i}$。他对一张卡片的熟练度为他对卡片上所有定理的熟练度的平均值。Vasya 想通过从其他考生处取得的数据计算他对他拿到的卡片的熟练度有可能达到的最小值与最大值。不幸的是，Vasya 没时间了，只能让您帮他。

第一行，两个正整数 $n$、$k$（$1≤k≤n≤100$），表示定理数量与卡片数量。

第二行，n 个非负整数 $a_{1}$，$a_{2}$，···，$a_{n}$，其中 $a_{i}$（$0≤a_{i}≤100$） 表示 Vasya 对第 i 个定理的熟练度。

第三行，一个非负整数 $q$（$0≤q≤100$），表示排在 Vasya 之前的考生数量。

接下来 $q$ 行，每行 $\lfloor\frac{n}{k}\rfloor$ 个 $1$、$n$ 之间的互不相同的整数，表示一名考生拿到的卡片上的定理的编号。两名考生拿到的定理要么没有交集，要么完全一样（顺序可能不同）。

输出两个实数，分别表示 Vasya 对他的卡片的熟练度的可能的最小值和最大值，绝对或相对误差不超过 $10^{-6}$。
 
 
## 思路

显然，熟练度的最小值只可能是：已知卡片中的熟练度的最小值和未出现在卡片中的定理组成的新卡片中的熟练度的最小值中更小的那个。已知卡片中的熟练度的最小值是显然的，对于未知卡片中的熟练度的最小值，因为我们希望最小值最小且定理最多只能写在一张卡片上，所以可以用未出现在已知卡片中的熟练度最小的 $\lfloor\frac{n}{k}\rfloor$ 个定理组成一张新的卡片。

最大值也是同理的。

注意，因为有 $n-\lfloor\frac{n}{k}\rfloor$ 个定理没有被考到，所以如果去掉已知卡片中的所有定理，剩余的定理不足 $\lfloor\frac{n}{k}\rfloor$，那么一定无法再组成新的卡片了。


## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=105;
int n,k,a[MAXN],q,sum,x,minn=LONG_LONG_MAX,maxx,aa[MAXN],cnt;
bool book[MAXN];
double ans1,ans2;
signed main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
	scanf("%lld",&q);
	for(int i=1;i<=q;i++)
	{
		sum=0;
		for(int j=1;j<=(n/k);j++)
		{
			scanf("%lld",&x);
			book[x]=1;
			sum+=a[x];
		}
		minn=min(minn,sum);
		maxx=max(maxx,sum);
	}
	for(int i=1;i<=n;i++)
	{
		if(!book[i])  aa[++cnt]=a[i]; //统计未出现在卡片中的定理
	}
	if(cnt<=(n-k*(n/k))) //无法再组成新的卡片的情况
	{
		ans1=minn/(n/k*1.0);
		ans2=maxx/(n/k*1.0);
		printf("%.10lf %.10lf\n",ans1,ans2);
		return 0;
	}
	sort(aa+1,aa+cnt+1);
	sum=0;
	for(int i=1;i<=(n/k);i++)  sum+=aa[i]; 
    //未出现在卡片中的定理的熟练度最小值
	minn=min(minn,sum);
	sum=0;
	for(int i=cnt;i>=cnt-(n/k)+1;i--)  sum+=aa[i]; 
    //未出现在卡片中的定理的熟练度最大值
	maxx=max(maxx,sum);
	ans1=minn/(n/k*1.0);
	ans2=maxx/(n/k*1.0);
	printf("%.10lf %.10lf\n",ans1,ans2);
	return 0;
}
```



---

## 作者：_lxy_ (赞：1)

### 题意

略

### 分析

由于已经强制配好了 $q$ 张卡片，那么现在为了让熟练度最大，就将剩下的定理中熟练度最大的 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个定理配成一张卡片，此时熟练度的最大值就是这 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个定理熟练度的平均数和已配好卡片平均数的最大值。同理，最小熟练度就是剩下定理中熟练度最小的 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个定理的平均数和已配好卡片平均数的最小值。

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int MAXN=107;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x*10)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
template<class T1,class T2>inline T1 qmin(const T1 &x,const T2 &y){return x<y?x:y;}
template<class T1,class T2>inline T1 qmax(const T1 &x,const T2 &y){return x>y?x:y;}
int n,k,q;vector<int>a,c;
int b[MAXN][MAXN];
bitset<MAXN>vis;vector<int>tmp;
int mx,mn=2139062143;
map<vector<int>,bool>mp;
int main()
{
	qread(n,k);int i,j;a.resize(n+1);for(i=1;i<=n;i++) qread(a[i]);qread(q);
	int m=n/k,cnt=0; // cnt表示已配好的卡片数
	for(i=0;i<q;i++) 
	{
		int sum=0;tmp.clear();
		for(j=0;j<m;j++) qread(b[i][j]),vis[b[i][j]]=true,sum+=a[b[i][j]],tmp.push_back(b[i][j]);
		sort(tmp.begin(),tmp.end());if(!mp[tmp]) mp[tmp]=true,cnt++; // 由于前q张可能有重复，所以用map记一下去重
		mx=qmax(mx,sum);mn=qmin(mn,sum);
	}
	for(i=1;i<=n;i++) if(!vis[i]) c.push_back(a[i]); // 剩余的定理的平均数
	int t=0;
	if(c.size()>=m&&k-cnt>0)
	{
		sort(c.begin(),c.end(),greater<int>());for(i=0;i<m;i++) t+=c[i];mx=qmax(mx,t); // 最大值
		t=0;sort(c.begin(),c.end());for(i=0;i<m;i++) t+=c[i];mn=qmin(mn,t); //最小值
	}
	printf("%.10lf %.10lf\n",mn/1.0/m,mx/1.0/m);
	// system("pause");
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 思路
极其简单的贪心。

记录每组卡片的熟练度，再将剩下未出现过的定理按熟练度排序，取排序后数组前 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个定理和后 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个定理组成新的两组，再求每组熟练度的最大值和最小值即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 100 + 5;

int n, k, q, num, used;
int a[maxn], vis[maxn];
double ans1, ans2 = 2147483647;
inline int read() {
	int ret = 0, f = 1;char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -f;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		ret = ret * 10 + ch - '0';
		ch = getchar();
	}
	return ret * f;
}

bool cmp(int a, int b) {
	return a > b;
}

signed main() {
	n = read(), k = read();
	for (int i = 1;i <= n;i++) a[i] = read();
	q = read();
	num = floor(n / k);
	double cnt;
	for (int i = 1;i <= q;i++) {
		cnt = 0;
		for (int j = 1;j <= num;j++) {
			int x;x = read();
			cnt += a[x];
			vis[x] = 1;
		}
		ans2 = min(ans2, cnt / num);
		ans1 = max(ans1, cnt / num);
	}
	for (int i = 1;i <= n;i++) if (vis[i]) a[i] = 2147483647, used++;
	sort(a + 1, a + 1 + n, cmp);
	cnt = 0;
//	cout << num << '\n';
//	for (int i = 1;i <= n;i++) {
//		cout << a[i] << " ";
//	}
//	cout << '\n';
	if (n - used >= num) {
		for (int i = used + 1;i <= used + 1 + num;i++) cnt += a[i];
		ans1 = max(ans1, cnt / num);
		cnt = 0;
		for (int i = n - num + 1;i <= n;i++) cnt += a[i];
		ans2 = min(ans2, cnt / num);
	}
	printf("%.6llf %.6llf", ans2, ans1);
	return 0;
} 
```
一些细节地方处理一下就好了，注意特判不能组成新的卡片的情况。

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF119B](https://www.luogu.com.cn/problem/CF119B)

# 思路

由题知，现在已经有 $q$ 个定理被配对，我们要让熟练度最大，就要让剩下中最大熟练度
的 $\lfloor \frac{n}{k} \rfloor$ 个定理，那么此时的熟练度就是这 $\lfloor \frac{n}{k} \rfloor$ 个定理熟练度的平均数和已经配好平均数的最大值。最小值是同理的。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
long long n,k;
long long a[MAXN];
long long q,sum,x,maxx,cnt;
long long ans[MAXN];
bool book[MAXN];
double ans1,ans2;
int main() {
	cin>>n>>k;
	for(int i=1; i<=n; i++){
		cin>>a[i];
	}
	cin>>q;
	for(int i=1; i<=q; i++) {
		sum=0;
		for(int j=1; j<=(n/k); j++) {
			cin>>x;
			book[x]=1;
			sum+=a[x];
		}
		minn=min(minn,sum);
		maxx=max(maxx,sum);
	}
	for(int i=1; i<=n; i++) {
		if(!book[i]){
			ans[++cnt]=a[i];	
		}
	}
	if(cnt<=(n-k*(n/k))) {
		ans1=minn/(n/k*1.0);
		ans2=maxx/(n/k*1.0);
		cout<<fixed<<setprecision(10)<<ans1<<" "<<fixed<<setprecision(10)<<ans2<<endl;
		return 0;
	}
	sort(ans+1,ans+cnt+1);
	sum=0;
	for(int i=1; i<=(n/k); i++){
		sum+=ans[i];	
	}
	minn=min(minn,sum);
	sum=0;
	for(int i=cnt; i>=cnt-(n/k)+1; i--){
		sum+=ans[i];
	}
	maxx=max(maxx,sum);
	ans1=minn/(n/k*1.0);
	ans2=maxx/(n/k*1.0);
	cout<<fixed<<setprecision(10)<<ans1<<" "<<fixed<<setprecision(10)<<ans2<<endl;
	return 0;
}
```


---

