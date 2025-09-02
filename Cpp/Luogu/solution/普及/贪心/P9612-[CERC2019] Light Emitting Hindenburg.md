# [CERC2019] Light Emitting Hindenburg

## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Light Emitting Hindenburg](https://contest.felk.cvut.cz/19cerc/solved/hindenburg.pdf)」**

## 题目描述

Lothar 正在组织他朋友的摇滚乐队的音乐会巡演。巡演将于 11 月举行，每天最多有一场音乐会。这次巡演将非常具有代表性，许多音乐家都愿意参加。巡演中的音乐家人数是严格规定的，不能改变。巡演中的每一场音乐会都必须有所有参加巡演的音乐家参加。

对 Lothar 来说，好消息是，候选音乐家的数量至少与巡演中规定的音乐家数量一样多。坏消息是，一个典型的音乐家整个月都没有空，而且各种音乐家的日程安排也大不相同。

很久以前，Lothar 编写了一个计算机调度系统的核心，现在他正在利用它来组织这次巡演。他反复地、有点随机地选择一组指定数量的音乐家，并让系统计算出一个可接受的巡演时间表。该系统取决于一种非常具体的数据格式。音乐家的时间表和巡演时间表用数字编码表示。11 月的日子是按月份的数字标记的：$1, 2, \dots, 30$。

对于一个给定的音乐家来说，每年 11 月的一天都会被分配一个特定的数字编码。如果音乐家当天空闲，则标签为 $L$ 的一天由整数 $2^{30-L}$ 编码。否则，日期将由 $0$ 编码。音乐家的时间表编码是他或她的所有日期编码的总和。

对于一组给定的音乐家来说，每年 11 月的一天都会被分配一个特定的数字编码。如果该组中的所有音乐家当天都空闲，标签为 $L$ 的一天由整数 $2^{30-L}$ 编码。否则，日期将由 $0$ 编码。组的空闲编码是该组所有日期编码的总和。

出于许多其他微妙的原因，Lothar 认为最好的巡演应该是任意一组音乐家，这组的空闲编码是可能的最大值。

## 样例 #1

### 输入

```
5 2
6 15 9 666 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
8 4
13 30 27 20 11 30 19 10
```

### 输出

```
18
```

# 题解

## 作者：codwarm (赞：4)

[题目传送门~](https://www.luogu.com.cn/problem/P9612)
## 题目大意
求从 $n$ 个数中取 $k$ 个数做**与运算**的最大值。
## 题目分析
阅读题面，可以知道本题与二进制运算有关，又根据题意，需要求出 $k$ 个数做与运算的最大值，可以想到**贪心**的思路：从大到小枚举二进制位，若有大于等于 $k$ 个数在当前二进制位上为 $1$，则将当前二进制位对应的权值加入答案，并在二进制位为 $1$ 的数上打上标记，之后遍历时只有上次被打上标记的数才能参与运算（没有标记的数说明不在最大值中）。

贪心思路的证明：从大到小枚举二进制位，若当前二进制位可行，则必选当前位置。因为若不选当前位置，比当前位更低的二进制位的和不可能比当前位置大。

具体见代码，注释很清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, k, a[N], maxn, cnt;
bool vis[N];
int main()
{
	scanf("%d%d",&n, &k);
	for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
	memset(vis,1,sizeof vis);
	for (int i = 30;i >= 1;i--) //从大到小枚举第i位
	{
		cnt = 0;
		for (int j = 1;j <= n;j++) 
							//指a[j]的第i位是否等于1
			if (vis[j] && (a[j] >> (i - 1) & 1)) //满足条件
				cnt++; //记录个数
		if (cnt < k) continue; //不及k则退出
		for (int j = 1;j <= n;j++)
			if (!(vis[j] && (a[j] >> (i - 1) & 1))) //将不满足条件的数打上0
				vis[j] = 0;
		maxn += (int)pow(2,i-1); //累加结果
	}
	cout << maxn;
	return 0;
}
```


---

## 作者：MithrilSword_XIV (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9612)

[更好的阅读体验](https://www.cnblogs.com/MithrilSwordXIV/p/18003407)

## 题目大意

这个题目简化一下就是求 $n$ 个数中取 $k$ 个数按位与的最大值。

## 思路

很容易想到贪心。

题中说道输入的数在二进制下最多 $29$ 位，所以我们从 $29$ 开始遍历二进制位，如果当前位有大于等于 $k$ 个 $1$，那么标记一下这些数，可以发现剩下的比当前位低的二进制位和无法大于当前位，所以必选当前位。最后再遍历时只需要考虑这些打过标记的数即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define MAX 200005
#define int long long
using namespace std;
int n,k,a[MAX],cnt,ans,tmp;
bool pd[MAX];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    memset(pd,1,sizeof(pd));
    for(int i=29;i>=0;i--){
        cnt=0;
        for(int j=1;j<=n;j++){
            tmp=(a[j]>>i)&1;//取出a[i]在二进制下的第i位
            if(pd[j]&&tmp)cnt++;
        }
        if(cnt>=k){
            for(int j=1;j<=n;j++){
                tmp=(a[j]>>i)&1;
                if(pd[j]&&!tmp)pd[j]=0;
            }
            ans+=(1<<i);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：catorlove (赞：1)

# P9612题解
## 题意
给你 $n$ 个数，选出 $k$ 个数，让它们的做与运算值最大。

## 思路
从大到小枚举二进制每一位，看看这位有没有大于等于有  $k$ 位的值为 $1$，有则选择，并累加，无则枚举下一位。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],n,k,sum,ans;
bool f[200005];//是否可选
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1<<29;i;i>>=1)
	{
		sum=0;//1的个数 
		for(int j=1;j<=n;j++)
		{
			if(!f[j]&&a[j]&i)//没选且是1 
				sum++;
		}
		if(sum<k)//1的个数 < k 
			continue;
		ans+=i;
		for(int j=1;j<=n;j++)
		{
			if(!f[j]&&!(a[j]&i))
				f[j]=1;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：allqpsi (赞：1)

### 题意：

在一个 $n$ 个数数组中选择 $k$ 个数，让其按位与值最大。

### 思路：

这道题，其实是一个贪心思路。从高依次往低推 $2^{i}$，如果第 $i$ 位可拿，则必定拿第 $i$ 位。以后的 $2^{i}$ 是否可选，就在那些在拿此更高位基础上的数中选。

则，我们可以用一个数组标记，如果第 $i$ 个数还可以选，就将它标记为对，否则为错。一开始，所有的数都为对。后面一有 $2^{i}$ 可选，则把不含有 $2^{i}$ 的数标记为错。以后就不将这些数算上。

### 美丽又动人的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,vi[200005],poww,a,ans=0;
bool use[200005];
int main(){
	memset(use,true,sizeof(use));
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>vi[i];
	}
	poww=pow(2,30);
	for(int i=29;i>=0;i--){
		poww/=2;
		a=0;
		for(int j=1;j<=n;j++){
			if(use[j]&&vi[j]&poww){
				a++;
			}
		}
		if(a>=k){
			ans+=poww;
			for(int j=1;j<=n;j++){
				if(use[j]&&!(vi[j]&poww)){
					use[j]=false;
				}
			}
		}
	}
	cout<<ans;
}
```


---

## 作者：翟翟 (赞：1)

题意：从 $n$ 个书中选出 $k$ 个数，使它们的与值最大。

从大到小枚举二进制每一位（一定最优），看看这位有没有 $k$ 个为 $1$，为 $1$ 的标记，判断更低位就从高位满足的里面选。

## Code
```
#include<cstdio>
const int N=2e5+1;
int n,k,a[N],ans;
bool t[N];//用来标记，0表示可以选
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=1<<29;i;i>>=1){
		int s=0;
		for(int j=1;j<=n;++j)
			if(!t[j]&&a[j]&i)++s;
		if(s>=k){
			ans+=i;//这位可以凑出k个
			for(int j=1;j<=n;++j)
				if(!t[j]&&!(a[j]&i))
					t[j]=1;//这个数这位不是1，舍去
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：_Supernova (赞：1)

## 一、题目大意。

------------
给你 $n$ 个数，你从里面选出 $k$ 个数，是他们相与起来的值最大。

------------
## 二、思路分析。

------------
在二进制下，假设 $a$ 有一位是 $1$（前面都是 $0$），而 $b$ 的那一位是 $0$，且前面没有 $1$，那么无论 $b$ 的后面是多少，$a$ 永远大于 $b$。

------------

所以，从最开始的一位检查，如果能找到 $k$ 个数，这 $k$ 个数这一位是 $1$，那么这 $k$ 个数一定有构成最优解的潜质。所以就不断地这么从前往后找。

------------
那么，我们只需要：从第一位开始检索，统计这一位是 $1$ 的个数！

------------

## 三、代码。

------------
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
#define ll long long
const int maxn=2e5+7;

int a[maxn],sc[maxn],n,k;

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=31;i>=0;--i){
        int cnt=0;
        for(int j=1;j<=n;++j)
            if(sc[j]==0&&((a[j]>>i)&1))
                cnt++;
        if(cnt<k) continue;
        else{
            for(int j=1;j<=n;++j)
                if(sc[j]==0&&((a[j]>>i)&1)==0)//如果能凑够k个数，而这个数这一位不是1
                    sc[j]=1;//放弃了这个数
        }
    }
    int ans=-1;
    for(int i=1;i<=n;++i)
        if(!sc[i]) ans&=a[i];
    printf("%d\n",ans);
    return 0;
}


```



------------
## 四、致谢。

------------
感谢朋友“云南老”对我的指导！感谢审核员的辛苦审核！


---

## 作者：tomby_gz (赞：1)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/blog/tomby-gz-2011/solution-p9612)

## 题目意思

[题目](https://www.luogu.com.cn/problem/P9612)比较长，但是基本可以用一句话概括：在 $N$ 个数里面选 $K$ 个数，求它们做按位与运算的最大值。

## 题目分析

既然是与运算，那么可以从二进制逐一查看每个位，开一个标记数组，如果当前的数据没被标记过，那么就检查当前的数是否与当前检查的位按位与的值为 $1$。如果为 $1$，则把可以加入的数加一，接着判断以下当前方案是否可行，也就是是否 $sum \ge k$。

而如果成立，就说明这是一个可行的方案，就将答案加上这个数，然后将所有这个位不是 $1$ 的数都打上标记（证明都不可行）。

这其实就是一个贪心的思路。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+4;
const int T=1<<29;
ll n,k,cnt,a[N];
bool vis[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=T;i;i>>=1){
		ll sum=0;
		for(int j=1;j<=n;j++){
			if(!vis[j]&&a[j]&i){
				sum++;
			}
		}
		if(sum>=k){
			cnt+=i;
			for(int j=1;j<=n;j++){
				if(!vis[j]&&!(a[j]&i)){
					vis[j]=true;
				}
			}
		}
	}
	cout<<cnt;
}
```


---

## 作者：Flaw_Owl (赞：0)

# P9612 [CERC2019] Light Emitting Hindenburg 题解

**原题链接**：[P9612 [CERC2019] Light Emitting Hindenburg](https://www.luogu.com.cn/problem/P9612)

**TAG**：ICPC | 2019 | 贪心 | 位运算

## 题目分析

题目的关键是看懂这一句：

> 如果音乐家当天空闲，则标签为 $L$ 的一天由整数 $2^{30 - L}$ 编码。否则，日期将由 $0$ 编码。组成的空闲编码是该组所有日期编码的总和。

这里其实就是二进制编码。$2^{30 - L}$ 换成二进制也就是除了第 $30 - L$ 位为 $1$ 之外其他都为 $0$。最后把结果相加就会形成一个二进制串。

加上下面的题目要求，我们可以将题目抽象成：**从 $N$ 个数种选择 $K$ 个，使得其与运算的结果最大**。

题目的 $N$ 最大是 $2 \times 10^5$，暴力解法不适合。“选择”+“结果最大”，看上去很像**动态规划**。但是在动态规划之前，我们先考虑 **贪心** 是否可行。

朴素地思考一下：这 $K$ 个数与运算的结果，只要有一个数某一位为 $0$，整体结果在这一位上就是 $0$，所以**最好它们都为 $1$ 的位数越多越好**；而这些位数，**最好在更大的位上**，即越靠近 $29$（最大位）越好。所以我们可以制定贪心的策略：**枚举每一位，如果当前位至少有 $K$ 个为 $1$，就选择当前位为 $1$ 的数**。

如何统计答案？无需将选好的数保存下来再与运算。由于我们是枚举每一位，并且根据当前位是否有足够的 $1$ 来判断，选择当前位为 $1$ 的数。——那么我们选了这些数，其实也就相当于**选了这一位**，最后的答案这一位一定是 $1$。直接令 `ans += (1 << i)` 即可，其中 `i` 是当前位。

### 你也许会有的疑问

如果对位运算或这种表示方法不熟悉，也许会有下面的问题：

#### 如果我最后选出来的数不足 $K$ 个怎么办？

这里的“选择这些数”，其实更准确的说法是**这些数对答案有贡献**，它们并不等同于我们最后选了哪些数。——实际上，我们也**只关心最后的答案**，如果选择的数对答案没有贡献，那选谁都一样；同理的，如果有大于 $K$ 个数在这一位都是 $1$，那选谁最后答案都是加上 $2^k$，选谁也都一样。

#### 这个贪心策略一定是正确的吗？

考虑一种极端情况，对于下面三个二进制数，我们从上到下依次编号为 ABC。

```cpp
A:0111
B:1111
C:1000
```

有朋友考虑的是：仅仅因为数 A 的第 $3$ 位是 $0$ 就不选择它，但它其它位都是 $1$，而数 $C$ 虽然第 $3$ 位是 $0$，但它其它位都是 $0$。——这样的贪心策略，能否保证准确性？

简单地计算得知，数 A 与 数 B 与运算的结果是 $(0111)_2 = 7$，数 C 与 数 B 与运算的结果是 $(1000)_2 = 8$。——贪心策略正确。

对二进制不熟悉的话可能会陷入这样的混乱。希望上面的这个例子能帮助到你：其实就是 $2^i > 2^i - 1$ 的问题。

## AC 代码

```cpp
#include <iostream>
#include <cctype>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 2e5 + 5;

int N, K;
int ans;

int a[maxN];
bool check[maxN];

int main()
{
    N = read();
    K = read();
    for (int i = 1; i <= N; i++)
    {
        a[i] = read();
        check[i] = true;
    }

    for (int i = 29; i >= 0; i--)
    {
        int cnt = 0;

        for (int j = 1; j <= N; j++)
        {
            int temp = (a[j] >> i) & 1; // 第 i 位是否为 1
            if (check[j] && temp)
                cnt++;
        }
        if (cnt >= K)
        {
            for (int j = 1; j <= N; j++)
            {
                int temp = (a[j] >> i) & 1;
                if (check[j] && !temp)
                    check[j] = false;
            }

            ans += (1 << i);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：wangjue233 (赞：0)

# Solution
[题目传送门](https://www.luogu.com.cn/problem/P9612)
***
## 题目分析
题目要求我们从所有音乐家的日程中选择 $k$ 个人，使得他们的共同空闲时间的编码和最大。每个音乐家的日程是用一个整数编码表示的，第 $l$ 天空闲的编码是 $2^{30-l}$。
***
## 解题思路
   这道题是一个位运算和贪心的问题。从最高位开始（$2^{29}$，$L=1$）检查所有音乐家，统计有多少音乐家在这一天是空闲的。如果空闲的音乐家数量大于或等于 $k$，则说明我们可以选择这一天作为巡演的一天。所有在这一天不空闲的音乐家将被排除在接下来的选择之外。因为我们已经选择了这一天，再选择其他天就会和这天冲突。这样，我们就能保证选择的每一天都是所有选定音乐家的共同空闲时间。
 
   这个过程需要从高位向低位进行，每次都确保选择的音乐家集合在该位都是空闲的。因为每选择个日期，都会有一些音乐家在其他日期不再可用，我们需要用一个 $vis$ 数组来标记哪些音乐家在当前选择之后还是可用的。
***
## AC Code:
```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int maxn = 200000 + 10; //加10是为了防止下标越界导致RE
int a[maxn];
bool vis[maxn]; //vis[i] 表示在第 i 个音乐家在当前选择之后可/不可用
int main(){
    int n, k; cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        vis[i] = true; //初始化vis数组，也可以用memset代替
    }
    int ans = 0;
    for(int i = 29; i >= 0; i--){
        int val = 1 << i;
        int cnt = 0;
        for(int j = 1; j <= n; j++){
            if(vis[j] && (a[j] & val)){ //如果音乐家j在这一位上空闲，并且是可选的，那么cnt++
                cnt++;
            }
        }
        if(cnt >= k){
            ans += val;
            for(int j = 1; j <= n; j++){
                if((a[j] & val) == 0){ //如果音乐家j在这一位上不空闲，那么他不再可用，将vis[j]设置为false
                    vis[j] = false;
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
```
时间复杂度：$O(n \log v)$，$n$ 表示音乐家的数量，$v$ 表示日程编码的最大值。因为我们需要遍历每一位和所有音乐家的编码。 [AC记录](https://www.luogu.com.cn/record/133148642)。

2023.11.04 修改了不应过多使用粗体的问题以及不应滥用 $\LaTeX$ 的问题。望通过。

---

## 作者：违规用户名U1075140 (赞：0)

## 题意

求 $n$个数中取 $k$ 个数作按位与运算的最大值。

## 思路

明显贪心。根据二进制位从高到低进行搜索，如果当前位有 $\ge k$ 个数值为1，那么对这些数标记，因为可证 $2^n>2^{n-1}+2^{n-2}+\dots+2^0$，这里就不再赘述。然后如果当前标记的数正好有 $k$ 个，则直接输出这 $k$ 个数的按位与。否则从当前位继续往下筛，如果这些有标记的数中有 $\ge k$ 个当前位为1的就去除其他数的标记，重复此过程直到恰好有 $k$ 个数有标记或者所有数位都筛完，最后输出结果。

---

## 作者：drinktowind (赞：0)

# 题意
给你 $n$ 个数，选出 $k$ 个数，让它们的做与运算值最大。
# 思路
从大到小枚举二进制每一位，看看这位有没有大于等于 $k$ 个为 $1$ ，有则选择，并累加，无则选择枚举下一位。
``` 
#include<bits/stdc++.h>
using namespace std;
int a[200010],n,k,sum,ans;
bool f[200010];//可以选 
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1<<29;i;i>>=1)
	{
		sum=0;//1的个数 
		for(int j=1;j<=n;j++)
		{
			if(!f[j]&&a[j]&i)//如果这里没被选过而且是1 
				sum++;
		}
		if(sum<k)//1的个数不足k 
			continue;
		ans+=i;//累加 
		for(int j=1;j<=n;j++)
		{
			if(!f[j]&&!(a[j]&i))
				f[j]=1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_Emperorpenguin_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9612)

## 题意简述

给定 $n$ 个数，从中选出 $k$ 个数，使这些数的按位与的值最大。

## 思路

从二进制的最高位枚举到最低位，如果超过 $k$ 个数的第 $i$ 位二进制为 $1$,则必选这一位。因为从高位到低位枚举，$2^i$ 一定比 $2^j(j<i)$ 更大。

若选了第 $i$ 位，则将答案变量 ```ans``` 加上 $2^{i-1}$ 即可。

最后输出 ```ans```。

时间复杂度为 $O(n)$。常数较大，但足以通过本题。

---

