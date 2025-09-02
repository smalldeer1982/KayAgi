# Addition Chains

## 题目描述

一个与 $n$ 有关的整数加成序列 $<a_0,a_1,a_2,...,a_m>$ 满足以下四个条件：  
 $1.a_0=1$   
 $2.a_m=n$   
 $3.a_0<a_1<a_2<...<a_{m-1}<a_m$   
 $4.$ 对于每一个 $k(1≤k≤m)$ 都存在有两个整数 $i$ 和 $j(0≤i,j≤k-1,i$ 和 $j$ 可以相等 $)$ ，使得 $a_k=a_i+a_j$   
你的任务是：给定一个整数 $n$ ,找出符合上述四个条件的长度最小的整数加成序列。如果有多个满足要求的答案，只需要输出任意一个解即可。  
举个例子，序列 $<1,2,3,5>$ 和 $<1,2,4,5>$ 均为 $n=5$ 时的解。

## 样例 #1

### 输入

```
5
7
12
15
77
0```

### 输出

```
1 2 4 5
1 2 4 6 7
1 2 4 8 12
1 2 4 5 10 15
1 2 4 8 9 17 34 68 77```

# 题解

## 作者：yqw2486 (赞：49)

**迭代加深+剪枝**
看完题目第一反应求最短路：bfs；看了一眼n=10000，肯定会爆空间。因此考虑dfs，按照dfs去跑会发现暴力dfs可能得不到正确答案；转念一想这不就是dfs形式的bfs吗？这不就是迭代加深？？

快速写完迭代加深后样例数据一发就过了，信心倍增；但是输入10000之后发现它好像不动了。。。。。这样一定会T;

考虑剪枝，不难看出我们需要的序列是单调递增的，枚举i,j得到k；因此如果发现ans[i]+ans[j]>n，那么如果i不变，j往后增一定也大于n；不过这并不会有什么大的改观；

强剪枝：ans[i]<=ans[i-1]*2，也就是说后一项最多是前一项的2倍，如果当前已知ans[k]然后迭代加深的最大深度为maxd，则后面最多还有maxd-k项，也就是说ans[k]*2^k<n则在maxd次之内一定找不到答案。


------------
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
long long n,maxd,ans[N];
bool dfs(int k){
	if(k>maxd)return ans[k-1]==n;
	if(ans[k-1]*((long long)1<<(maxd-k+1))<n)return 0;//最优化剪枝：后面每一项最多是前一项的2倍 
	for(int i=0;i<k;i++)
		for(int j=i;j<k;j++){
			long long t=ans[i]+ans[j];
			if(t>n)break;//可行性剪枝：ans单调递增，如果t>n则后面的j都会大于n； 
			if(t<=ans[k-1])continue; //保证ans单调递增 
			ans[k]=t;
			if(dfs(k+1))return 1;
		}
	return 0;
}
int main(){
	ans[0]=1;
	while(scanf("%lld",&n)&&n){
		printf("1");
		for(maxd=0;;maxd++){
			if(dfs(1)){
				for(int i=1;i<=maxd;i++)
					printf(" %lld",ans[i]);
				printf("\n");
				break;
			}
		}
	}
	return 0;
} 
```


---

## 作者：lew2018 (赞：21)



经过严谨~~玄学~~的分析可以发现m的值都不会太大，而每次枚举两个数的和会造成搜索的分支过多，所以可以采用迭代加深搜索的方式来进行搜索。从小开始限制搜索深度，如果搜索失败就增加深度限制重新搜索，直到找到一组答案。

再来观察下列式子
$a[i] = a[i - 1] + a[j] (1 \leq j \leq i - 1)$ 
我们可以得到一个优化
求长度最小的的整数加成序列，即求m的最小值，也就是需要我们尽快得到数n，所以每次构建的数应当是尽可能大的数，我们可以将搜索顺序改为**从大到小**搜索每一个数，来减少搜索的分支。

```cpp
#include <iostream>
using namespace std;

int n, m, ans[10005];
bool flag;

void print() {
    for (int i = 1; i < m; i++)
        cout << ans[i] << " ";
    cout << ans[m] << endl;
}

void dfs(int step) {
    if (step == m + 1) {
        if (ans[m] == n) flag = 1;
        return;
    }
    for (int i = step - 1; i >= 1; i--) {
        ans[step] = ans[step - 1] + ans[i];
        int tmp = ans[step];
        for (int j = step + 1; j <= m; j++) tmp *= 2;//剪枝
        if (tmp < n) return;
        dfs(step + 1);
        if (flag) return;
        ans[step] = 0;
    }
}

int main() {
    ans[1] = 1;
    while (cin >> n && n != 0) {
        if (n == 1) {
            cout << 1 << endl;
            continue;
        } 
        flag = 0;
        for (int i = 2; i <= n; i++) {
            m = i;
            dfs(2);
            if (flag) {
                print();
                break;
            }
        }
    }
    return 0;
}
```

---

## 作者：览遍千秋 (赞：15)

## 吐槽

``RemoteJudge``随机A题。。。

最后通过``vjudge``交的。

[提交网址](https://vjudge.net/problem/uva-529)

---

## 小数据规模的解法

``POJ2248``是题面相同，数据规模较小的题目。

我们考虑题目对加成数列的定义，设$a_i$代表加成数列中的第$i$个数。

考虑迭代加深，枚举限制加成数列的长度$m$，由于具有spj，所以只要搜索到一个答案就不停返回然后输出即可。

考虑到在搜索加成数列的第$i$项时，已经求得了第$1$至第$i-1$项，故可以枚举第$1$项至第$i-1$项的所有组合，分别假设为$a_i$并尝试继续搜索。

循环嵌套的外层循环枚举大的数。

显然，为了保证$a_1<a_2<a_{...}<a_i$，外层循环枚举的数的下标从上一次取的外层循环的数$+1$开始。

所以可以得到代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int n,m,ans[10007],t[20007];
bool flag;
void P()
{
    for(register int i=1;i<=m;i++)
    {
        printf("%d ",ans[i]);
    }
    printf("\n");
}
void f(int step,int l)
{
    if(step==m+1)
    {
        if(ans[m]==n) flag=1;
        return;
    }
    for(int i=l;i<step;i++)
    {
        for(int j=1;j<=i;j++)
        {
            ans[step]=ans[i]+ans[j];
            f(step+1,i+1);
            if(flag) return;
            ans[step]=0;
        }
    }
}
void clear()
{
    for(register int i=2;i<=n;i++) t[i]=0;
    flag=0;
}
int main()
{
    ans[1]=1;
    while((~scanf("%d",&n))&&n)
    {
        clear();
        for(register int i=2;i<=n;i++)
        {
            m=i;
            f(2,1);
            if(flag)
            {
                P();
                break;
            }
        }
    }
    return 0;
}
```

可以通过推理得到搜索函数

```cpp
void f(int step,int l)
```

中$l=step-1$，也就是说，符合加成数列的一种情况下，$a_i=a_{i-1}+x$，其中$x$为$a_1,a_2,a_{...},a_{i-1}$中的一个数。

---

## 如何面对UVA中的大数据规模

> 当然是剪枝了
> > 搜索+剪枝是第一生产力！

### 1.优化搜索顺序

显然倒序枚举更有可能得到可行解。

### 2.排除不可行解

我们发现，对于加成数列的要求还有一个，即$a_m=n$

假设当前已经通过枚举得出了$a_i$，正准备搜索第$i+1$个数。

考虑通过当前形势下到第$m$项可以得到的最大值，显然，$$max(a_{i+1})=a_i+a_i=2×a_i$$

$$max(a_{i+2})=a_{i+1}+a_{i+1}=2×a_{i+1}=4×a_i=2^2×a_i$$

故由递推可得

$$max(a_m)=2^{m-i}×a_i$$

所以在进行对$i+1$个数的搜索前，计算一下$max(a_m)$是否可以达到$n$，如果达不到则无需进行下一步的搜索。

---

## 代码和细节

code:

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int n,m,ans[10007];
bool flag;
void P()
{
	for(register int i=1;i<m;i++)
	{
		printf("%d ",ans[i]);
	}
	printf("%d\n",ans[m]);
}
void f(int step,int l)
{
	if(step==m+1)
	{
		if(ans[m]==n) flag=1;
		return;
	}//如果找到答案，表示出来，开始返回
	for(int i=step-1;i>=l;i--)//倒序枚举
	{
		for(int j=i;j>=1;j--)
		{
			ans[step]=ans[i]+ans[j];
			int fff=ans[step];
			for(int lll=step+1;lll<=m;lll++) fff*=2;
			if(fff<n) break;//排除不可行解
			f(step+1,i+1);//继续搜索
			if(flag) return;
			ans[step]=0;//回溯
		}
	}
}
void clear()//多组数据，需要清空
{
	flag=0;
}
int main()//主函数
{
	ans[1]=1;//第一个数必定是1
	while((~scanf("%d",&n))&&n)
	{
		if(n==1)//特判只要一个的情况
		{
			printf("1\n");
			continue;
		}
		clear();
		for(register int i=2;i<=n;i++)//不是1的时候至少要两项，最多要n项
		{
			m=i;
			f(2,1);//搜索
			if(flag)//如果长度限制为m时有解
			{
				P();//输出
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：Akaina (赞：4)

### Addition Chains

**迭代加深+剪枝**

因为这道题要求的是满足条件的最小深度，所以用迭代加深会更可做一些

这道题还有一个显然的**贪心性质**，每一个数一定等于上一个数加上  之前的数(可以是上一个数)，否则的话如果是两个上一个数之前的数相加，那么上一个数就可以得到了，不需要多占一个地方。

可行性剪枝：数列每增加一个数，这个数的大小最大是在上一个数的基础上*2，如果剩下的长度中每个数都达到最大值，但最后一个数任然小于n则返回

优化搜索顺序：倒序枚举，因为这样能够更快地到达n（这道题是一道典型的优化搜索顺序题）

小细节：这道题特别坑的一个点是针对每组数据，行尾不能有空格   ~~**真的玄学坑**~~

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
ll a[10010],dep,n;
int pd=0;
void dfs(ll step)
{
    if((a[step]*(1<<(dep-step)))<n)return;
    if(step==dep)
    {
        if(a[step]==n)pd=1;
        return;
    }
    for(ll i=step;i>=1;i--)
    {
        a[step+1]=a[i]+a[step];
        dfs(step+1);
        if(pd)return;
        a[step+1]=0;
    }
}
void solve()
{
    a[1]=1;
    for(ll i=1;i<=n;i++)
    {
        dep=i;
        dfs(1);
        if(pd)return ;
    }
}
int main()
{
    while(scanf("%lld",&n))
    {
        if(n==0)break;
        memset(a,0,sizeof(a));
        dep=0;pd=0;
        solve();
        for(ll i=1;i<dep;i++)printf("%lld ",a[i]);
        printf("%d\n",a[dep]);
    }
    return 0;
}
```



---

## 作者：lx_zjk (赞：4)

# UVA529 【Addition Chains】
好像是~~垃圾~~一本通里的题目，前置知识:**迭代加深搜索** 不懂的可以看我博客
内附迭代加深的模板

首先 先看题目 发现是 **UVA**的题目，立刻反应到，输出要有格式，这也是我交了那么多次没A的理由

然后 看数据范围 $1$ $to$ $10000$ ，然后仔细观察这个数列 易发现这个数列~~不简单~~必须符合一个规律，就是$f[n] \leq 2 * f[n-1]$,至于证明，可以发现等比数列$1$  $2$ $4$ $... 2^n$的和为$2*2^n-1$,那么如果要不重不漏的组合出所有数，则下一位为$2 * 2 ^n$ 这样即可以作为一个剪枝

还有几个剪枝写在$code$里，如果不懂可以私我

$O2$不开 $0 ms$ 复杂度可以接受
# code

```
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;

inline ll read() {
    ll f = 1, x = 0;char ch;
    do {ch = getchar();if (ch == '-')f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0';ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
}

const int MAX_N = 1e4 + 5;

int n, a[MAX_N], maxdepth;

bool dfs (int depth,int maxdepth)
{
    if (a[depth - 1] > n) return false;

    if (depth == maxdepth ) return a[depth - 1] == n; 
	//前面提到的剪枝
    if (a[depth-1]*((ll)1<<(maxdepth - depth))<n)return false;

    bool st[MAX_N] = {0};
    //枚举顺序 从大到小 这样使搜索树上端的分叉减小
    for(int i = depth - 1; i >= 0; i -- )
    {
        for(int j = i; j >= 0; j -- )
        {
            int s = a[i] + a[j];
            //保证序列严格递增 且不大于n 而且保证其未被搜索到过 减掉冗余信息
            if (s > n || s <= a[depth - 1] || st[s]) continue;
            a[depth] = s;
            st[s] = true;
            if (dfs (depth + 1, maxdepth)) return true;
        }
    }
    return false;
}

int main ()
{
    a[0] = 1;
    while (cin >> n, n)
    {
        maxdepth  = 1;
        while (!dfs(1, maxdepth)) maxdepth ++ ;
        cout<<a[0];
        for (int i = 1; i < maxdepth; i ++ ) cout<<" "<<a[i];
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Eismcs (赞：4)

明显一道搜索，剪枝也很好想。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,ff=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return ff*x;
}
int n,p,a[10005];
bool bfs;
void dfs(int i){
	if(i==p){
		if(a[p]==n)bfs=1;
		//成立则结束 
		return;
	}
	for(int k=i;k;k--){
		//因为i是新元素，所以要和其他元素相加，求出下一个元素 
		a[i+1]=a[i]+a[k];
		//a[i+1]为下一个数列元素 
		int x=a[i+1];
		for(int ff=i+2;ff<=p;ff++)x=1ll*x*2;
		//一个剪枝，a[i+1]为此数列最大元素，目前数列最大仅能到x，即是不断自己加自己 
		if(x<n)break;
		//如果最大都达不到n那就不搜 
		dfs(i+1);
		//搜索 
		if(bfs)return;
		//如果成立，直接返回 
	}
}
int main(){
	n=read();
	while(n){
		a[1]=1;
		if(n==1){
			printf("1\n");
			n=read();
			continue;
		}
		for(int i=2;i<=n;i++){
			//枚举数列的个数 
			p=i;bfs=0;
			//bfs为判断是否成立 
			dfs(1);
			if(bfs){
				for(int j=1;j<=i;j++){
					printf("%d ",a[j]);
				}
				printf("\n");
				break;
			}
		}
		n=read();
	}
	return 0;
}
```

---

## 作者：珈乐唯毒 (赞：2)

代码思路：

本题我们不知道m是多少，甚至连m的上限也不清楚。

对于枚举次数不明确的题目，我们可以使用迭代加深搜索(IDA)的思路。对这道题目而言，我们可以先从m=2开始尝试(前提是n!=1)，如果m=2不行，再尝试m=3，这样一步步增加m。

上~~AC~~代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[10000005],m;
bool dfs(int x){
	if(x==m){
		if(a[x]==n){
			for(int i=1;i<m;i++)printf("%d ",a[i]);
			printf("%d",a[m]);
			return true;
		}
		return false;
	}
	for(int i=1;i<=x;i++){
		for(int j=i;j<=x;j++){
			a[x+1]=a[i]+a[j];
			if(dfs(x+1))return true;
		}
	}
	return false;
}
int main(){
	cin>>n;
	while(n!=0){
		a[1]=1;
		if(n==1)printf("1");
		for(m=2;m<=n;m++)if(dfs(1))break;
		cin>>n;
		if(n!=0)printf("\n");
	}
	return 0;
} 
```

然后你就爆了~~（毕竟AC被划掉了呢）~~

本道题的n会到10000，这样写是肯定会爆的了。

因此考虑剪枝

剪枝1：
我们可以从大到小来枚举a[i]+a[j]这样会快一些
剪枝2：
考虑当前值是不是过大，如果当前值每次只加一都会大于n，就return false
剪枝3：
考虑当前值是不是过小，如果当前值每次乘二都会小于n，就return false
剪枝4：
如果已经有了答案，就return true

上真正的AC代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,a[10000005],m;
bool p;
bool dfs(long long x){
	if(p==1)return true;//剪枝4
	if(a[x]<<(m-x)<n)return false//剪枝2;
	if(a[x]+m-x>n)return false;//剪枝1
	if(x==m){
		if(a[x]==n){
			for(int i=1;i<m;i++)printf("%d ",a[i]);
			printf("%d",a[m]);
			p=1;
			return true;
		}
		return false;
	}
	for(int i=x;i>=1;i--){
		for(int j=x;j>=i;j--){//剪枝3
			a[x+1]=a[i]+a[j];
			if(a[x+1]<=a[x])break;
			if(dfs(x+1))return true;
		}
	}
	return false;
}
int main(){
	cin>>n;
	while(n!=0){
		p=0;
		a[1]=1;
		if(n==1)printf("1");
		for(m=2;m<=n;m++)if(dfs(1))break;
		cin>>n;
		printf("\n");//注意格式，最后会多空一行，但是每一组数据最后不能多一个空格
	}
	return 0;//完结撒花
} 
```


---

## 作者：_CHO (赞：2)

## 大爆搜+剪枝

这题与[NOI1999 生日蛋糕](https://www.luogu.com.cn/problem/P1731)思路差不多，总的思路就是大爆搜，看似是不可能过的，但事实上又能过，~~太玄学了~~

相信看到这题都能想到思路是搜索，因为$n$的范围很小$(n<=10000)$,所以我们的一个思路是枚举每一个数字，直到找到答案为止。

下面来说一说各种剪枝以及优化

### $round 1$
这题搜索思路多样，个人认为dfs好想也好写。因为保证对每个$n$都有解，所以朴素的dfs是能没有问题的，不过在统计数字的个数时需要特意去操作。而iddfs则可以在搜索的过程中限定出数字的个数，且不会对时间复杂度造成影响，比较推荐。~~反正都是$O($玄学$)$，有什么关系~~
### $round 2$ 
首先是枚举顺序的的问题，楼上的部分题解建议从大到小枚举，因为最先枚举的数字越大越容易快速接近答案。但是我实测从大到小、从小到大两种枚举方法，差别不大，甚至从小到大枚举会更快一些。
### $round 3$
可行性剪，枝因为题目要求序列是递增的，所以我们枚举到某一层时，如果这一层的数字比上一层的小，$cut$
### $round 4$
可行性剪枝，序列递增，当枚举到某一层时，如果接下来的每一层都比上一层的数字大$1$，最后都比$n$大，$cut$
### $round 5$
可行性剪枝，我们知道，如果一个大的数由两个比它小的数相加得到，那么这个大的数不会大于较小的两个数中较大的那个数的二倍。由这个性质我们可以推得：当枚举到某一层时，如果接下来的每一层的数字都是上一层的数字的二倍，最后都比$n$小，$cut$
### $round 6$
以上的剪枝以及优化足以过掉该题的数据了，~~其实是我想不出来更好的剪枝了~~

以下是代码
```cpp
#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
int n,d,ans[30];
void print(){
	for(int i=0;i<d;++i) printf("%d ",ans[i]);
	printf("%d\n",ans[d]);
}

bool iddfs(int deep){
	if(deep==d){
		if(ans[d]==n) return true;
		return false;
	}
	if(ans[deep]<=ans[deep-1]) return false;   //剪枝3
	if(ans[deep]+d-deep>n) return false;     //剪枝4
	if(ans[deep]*(1<<(d-deep)) <n) return false;   //剪枝5
	for(int i=0;i<=deep;++i){
		for(int j=i;j<=deep;++j){
			ans[deep+1]=ans[i]+ans[j];
			if(iddfs(deep+1))return true;
		}
	}
	return false;
}
int main(){
	ans[0] = 1;
	while(scanf("%d",&n)&&n){
		for(d=0;true;++d){
			if(iddfs(0)) break;
		}
		print();
	}
	return 0;
} 
```


完结，撒花！

---

## 作者：BriMon (赞：2)

这题和poj 2248一样；
我们考虑搜索；

依次搜索一位k， 枚举之前的i， j， 把a[i] + a[j] 加到a[k]的位置上， 然后接着搜索；

剪枝：尽量从达到小枚举i，j让序列的数尽快逼近n；

为了不重复搜索，用一个bool数组存a[i] + a[j] 是否已经被搜过；

然后因为答案的深度很小， 所以一发迭代加深；

这样差不多A了；

代码在博客里 ：http://www.cnblogs.com/zZh-Brim/p/8977282.html

这道题真的坑， 把数据范围有100改到1000



~~（顺便推广一下博客）~~

---

## 作者：Naruto_steven (赞：2)

此题是搜索，深搜+剪枝


------------
二话不说，先上代码：
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int n,ans[100];
bool finish;//记录状态
void dfs(int x,int deep){
    if(finish) return ;
    if(x==deep) { if(ans[x]==n)finish=1; return; }
    for(int i=0;i<=x;i++){
        for(int j=i;j<=x;j++) if(ans[i]+ans[j]>ans[x]&&ans[i]+ans[j]<=n){//剪枝 
                int sum=ans[i]+ans[j];
                for(int k=x+2;k<=deep;k++) sum<<=1;//sum *= 2;当前为x; sum存于x+1; 
                if(sum<n) continue;//如果接下来一直是最大策略还是不能达到n，剪枝 
                ans[x+1]=ans[i]+ans[j];
                dfs(x+1,deep);
                if(finish) return ;
        }
    }
}
int main(){
    while(scanf("%d",&n),n){
        memset(ans,0,sizeof(ans));
        ans[finish=0]=1;//直接在此初始化
        int tmp=n,deep=0; 
        while(tmp>>=1) deep++;//求出最大深度； 
        while(!finish) dfs(0,deep++);
        cout<<ans[0];
        for(int i=1;i<deep;i++) cout<<" "<<ans[i];
        cout<<endl; 
    }
    return 0;
}
```
然后开始讲解思路：


------------
如果我们的答案数组ans和传参的x即ans[x]==n且x已经达到最大深度,任务结束，将finish修改为1   


------------

几个剪枝点:    
1、如果枚举时ans[i]+ans[j]（随意两个数）和大于ans[x]，我们才继续；   
2、还要满足ans[i]+ans[j]<=n,如果都大于n了，就不需搜索了。  
3、由于我们一直按照最大策略枚举，如果还未能达到n，可以剪枝了。


------------
### 牵扯到一点位运算，因为比较快，即>>和<<;
# 坑点：
最后不能留空格，所以
```cpp
cout<<ans[0];
for(int i=1;i<deep;i++) cout<<" "<<ans[i];
```
输出操作要稍微修改一下

---

