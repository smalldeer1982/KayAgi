# Make Nonzero Sum (easy version)

## 题目描述

本题目是[CF1753A2](https://www.luogu.com.cn/problem/CF1753A2)的简单版本，不同之处为困难(hard)版本中$a$数组包含$0$。

**题目大意**

给你一个数组 $[a_1,a_2,...a_n]$ ,其中每一项 $a_i$ 都为 $1$ 或 $-1$ ，你需要构造一个划分 $[l_1,r_1],[l_2,r_2],[l_3,r_3],...[l_k,r_k]$ 使得：

- 将每一个区间内的数按照以下方法计算出$s_i=a_{l_i}-a_{l_i+1}+a_{l_i+2}-a_{l_i+3}+...\pm a_{r_i}$

- 对于一个合法的划分，所有的 $s_i$ 之和为 $0$

如果存在这样的划分，输出任何一个，否则输出 `-1` ，代表无解。

称一组区间 $[l_1,r_1],[l_2,r_2],[l_3,r_3],...[l_k,r_k]$ 为数组 $[a_1,a_2,...a_n]$ 的划分当且仅当 $1=l_1\leq r_1,l_2\leq r_2,l_3\leq r_3,...,,l_k\leq r_k = n$ 且对于 $1\leq i \leq k-1$ ,均有 $r_i+1=l_{i+1}$

注意在本题中，你不需要最小化 $k$。

## 样例 #1

### 输入

```
4
4
1 1 1 1
6
-1 1 1 1 1 1
3
1 -1 1
1
1```

### 输出

```
1
1 4
2
1 3
4 6
-1
-1```

# 题解

## 作者：lenlen (赞：17)

### $Problem$

题目大意：给你一个数组 $a$ ，让你把它划分成很多段，第 $i$ 段  $[l_i,r_i]$ 的价值 $s_i=a_{l_i}-a_{l_i+1}+a_{l_i+2}-a_{l_i+3}+...\pm a_{r_i}$ ，满足 $\sum\limits_{i=1}^n s_i=0$ 。

数据范围： $t \leq 1 \times 10^4 , \sum n \leq 2 \times 10^5$ （题目翻译有误，数据范围翻译错了）。

### $Solution$

这个题其实不要考虑太多，因为它可以单独划分，也就是一个数字一段，所以就很简单。

先考虑无解的情况，也就是当 $n$ 为奇数的时候，总和一定为奇数，所以一定不为 $0$。

然后我们可以考虑将 $n$ 个数两两配对， $a_{i×2-1}$ 和 $a_{i×2}$ 配对，一共就有 $2$ 种情况：

- $a_{i×2-1}=a_{i×2}$ ，那么将 $a_{i×2-1}$ 和 $a_{i×2}$ 划分在一组，这样就可以正好消掉。
- $a_{i×2-1}=-a_{i×2}$ ，那么将 $a_{i×2-1}$ 单独划分， $a_{i×2}$ 单独划分，也可以正好消掉。

这样划分必然满足条件，也就不会出现无解了。

### $Code$

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7232;
int a[N],n,t,ans;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        if(n&1) printf("-1\n");
        else 
        {
            ans=n;
            for(int i=1;i<=n;i+=2) if(a[i]==a[i+1]) ans--;//每a[i]==a[i+1]，那么就只会有一组，其他情况都是两组
            printf("%d\n",ans);
            for(int i=1;i<=n;i+=2)
            {
                if(a[i]==a[i+1]) printf("%d %d\n",i,i+1);
                else printf("%d %d\n%d %d\n",i,i,i+1,i+1);
            }
        }
    }
}
```


---

## 作者：liangbowen (赞：5)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1753A1)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16823086.html)

提供一种更加好理解的方法。

## 思路

关键点：**只要凑够就行，不需要区间数量最小**。

首先，每个数是 $-1$ 或 $1$，说明 $n$ 为奇数时，必定无解。

我们看相邻两个数 $a_i$ 与 $a_{i + 1}$：显然有四种可能，$(-1, -1), (-1, 1), (1, -1), (1, 1)$。

其中，$(-1, 1)$ 与 $(1, -1)$ 不需要动，他们的和就是 $0$ 了。我们可以用两个区间 $[i, i]$ 与 $[i + 1, ui + 1]$ 表示。

而 $(-1, -1)$ 与 $(-1, 1)$ 需要通过改变后一个数的符号，和才能是 $0$。所以我们可以用区间 $[i, i + 1]$ 表示。

统计全部区间就完成了。

---

这个办法好处是，特别好想好写。缺点是，加强版还要改一点东西。

但是能过这一题就够啦。

## 代码

```cpp
//赛时代码
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N], l[N], r[N];
void solve()
{
	int n, cur = 0;
	cin >> n;
	if (n & 1)
	{
		for (int i = 1, x; i <= n; i++) cin >> x;
		cout << "-1\n";
		return;
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 2; i <= n; i += 2)
		if (a[i - 1] + a[i] == 0)
		{
			l[++cur] = i - 1, r[cur] = i - 1;
			l[++cur] = i, r[cur] = i;
		}
		else l[++cur] = i - 1, r[cur] = i;
	cout << cur << '\n';
	for (int i = 1; i <= cur; i++) cout << l[i] << ' ' << r[i] << '\n';
}
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Day0 (赞：3)

### 题意描述

给你一个串，串仅由 $1$ 或者 $-1$ 构成，你可以将串划分为很多组，每一组的权值为 $ a_{l_i} - a_{l_i+1} + a_{l_i+2} - a_{l_i+3} + \ldots \pm a_{r_i} $，要求使得所有组的权值之和为 $0$。

### 思路

不难发现，一个长度为 $k$ 的组，一定可以拆成 $\frac{k}{2}$ 个长度为 $2$ 的组（如果 $k$ 为奇数，还有一个长度为 $1$ 的组）。

所以，我们可以将答案变成一些长度为 $1$ 和 $2$ 的组。

假设一开始每个数字构成一组，和为 $\operatorname{sum}$。

如果 $\operatorname{sum} < 0$ 则要让数值为 $-1$ 前面的计算符号转成负号，我们希望合并它和它前面的一个数字组成一组，但是如果前面的数字已经成为长度为 $2$ 的串，则无法合并，反之我们就合并，最终使得 $\operatorname{sum}=0$ 终止。

如果 $\operatorname{sum} > 0$，与前面同样的思路，只是改变的数值由 $-1$ 变成了 $1$ 而已。

你会发现用这种方法还可以过 [CF1753A2](https://www.luogu.com.cn/problem/CF1753A2)，[解释在这 OvO](https://hhdxgd.blog.luogu.org/solution-cf1753a2)。

### code:
代码过长，仅展现核心代码，完整代码见 [此处](https://www.luogu.com.cn/paste/dh8xslfs)：
```cpp
int sum = 0;
n = read();
vector<int> po;
memset(flag, 0, sizeof(flag));

for (int i = 1; i <= n; i++) {
	a[i] = read();
	sum += a[i];
}

if (sum % 2) {
	cout << "-1" << endl;
	continue;
}
sum /= 2;

for (int i = 2; i <= n; i++) {
	if (a[i] == 1 && sum > 0 && !flag[i - 1]) {
		flag[i] = true;
		po.push_back(i);
		sum--;
	}
	if (a[i] == -1 && sum < 0 && !flag[i - 1]) {
		flag[i] = true;
		po.push_back(i);
		sum++;
	}
	if (sum == 0) {
		break;
	}
}

if (sum != 0) {
	cout << "-1" << endl;
	break;
}
int anssum = 0;

for (int i = 1; i <= n; i++) {
	if (flag[i + 1]) {
		continue;
	}
	anssum++;
}

if (sum == 0) {
	cout << anssum << endl;
	for (int i = 1; i <= n; i++) {
		if (flag[i + 1]) {
			continue;
		}
		if (flag[i]) {
			cout << i - 1 << " " << i << endl;
		} else {
			cout << i << " " << i << endl;
		}
	}
}
```

---

## 作者：Strelitzia_ (赞：3)

## 题目大意

给出一个长度为 $n$ 的序列 $\{a_n\}$，对于任意 $a_i$ 有 $a_i=1$ 或 $a_i=-1$。我们可以把整个序列分为 $k$ 个区间，这 $k$ 个区间互相无交集，但完整构成原来的序列。对于第 $i$ 个区间 $[l_i,r_i]$，有 $s_i=a_{l_i}-a_{l_i+1}+a_{l_i+2}-\dots \pm a_{r_i}$，我们需要给出一种分割方案使得 $\displaystyle\sum_{i=1}^{k}s_i=0$。

## 思路

我们先考虑什么情况下无解。

当 $n$ 为奇数时，整个序列必定只能分成 $k_1$ 个偶数个数字构成的区间及 $k_2$ 个奇数个数字构成的区间。因为 $n$ 是奇数，所以 $k_2$ 必定为奇数。

我们先考虑偶数个数字构成的区间。因为每个位置只能 $+1$ 或 $-1$，所以 $+1$ 与 $-1$ 的数量的差必定为偶数，那么最后的 $s_i$ 必定为偶数。同理，我们可以知道奇数个数字构成的区间的 $s_i$ 必定为奇数。

奇数个奇数与偶数个偶数相加必定还是奇数，不可能为 $0$。于是我们知道 $n$ 为奇数的时候无解。

------------
接下来我们考虑 $n=2$ 时如何构造。如果 $a_1=a_2$，那么割成区间 $[1,2]$，于是 $s_1=a_1-a_2=0$。如果 $a_1\ne a_2$，那么有 $a_1=-a_2$，于是把两个数分别分成两个区间 $[1,1]$ 与 $[2,2]$，有 $s_1+s_2=a_1+a_2=0$。

我们发现，$n$ 为偶数时我们可以把它分成 $\dfrac{n}{2}$ 个长度为 $2$ 的序列，用上面的方法构造。因为没有要求 $k$ 最小，所以这种做法是正确的。

代码如下：

```cpp
int t,n,a[N];
signed main(){
	t=read();for(int nowt=1;nowt<=t;nowt++){
		n=read();for(int i=1;i<=n;i++) a[i]=read();
		if(n%2==1){puts("-1");continue;}//判
		if(n==2){
			if(a[1]-a[2]==0){puts("1\n1 2");continue;}
			if(a[1]+a[2]==0){puts("2\n1 1\n2 2");continue;}
			puts("-1");continue;
		}int nowres=0;for(int i=1;i<=n;i+=2){
			if(a[i]-a[i+1]==0) nowres++;
			else nowres+=2;
		}printf("%lld\n",nowres);//先要输出 k
		for(int i=1;i<=n;i+=2){
			if(a[i]-a[i+1]==0) printf("%lld %lld\n",i,i+1);//同一个区间
			else printf("%lld %lld\n%lld %lld\n",i,i,i+1,i+1);//两个区间
		}
	}return Strelitzia_H;
}
```

---

## 作者：Dregen_Yor (赞：1)

### [更好的阅读体验](http://dregen-yor.123ds.tk/index.php/2022/10/24/cf1753a1)。

# 思路

我们考虑让**相邻的两项两两配对**。

因为序列中的每一项都为 $1$ 或 $-1$，如果 $n$ 为奇数的话，无论如何构造，最后一定会剩余一个 $1$ 或 $-1$。这种情况直接输出 $-1$ 即可。

对于 $n$ 为偶数的情况，我们考虑让相邻两项互相配对，若相邻两项相同，可以直接将他们并入一个块中。若相邻两项不同，将他们分别并入两个不同的块中即可。

在一个块中因为会改变运算符，所以相同的两项会直接相互抵消。

不在一个块中会按初始值直接计算进答案中，若相邻两项正负相反，也能恰好抵消。

# 代码如下

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
int t,n,a[200010],ans[200010][2],sum;
signed main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        int k=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            if(a[i]!=0){
                sum++;
            }
        }
        if(sum&1){
            puts("-1");
            continue;
        }
        ans[1][0]=1;
        k=0;
        for(int i=1;i<=n;i+=2){
            k++;
            if(a[i]==a[i+1]){
                ans[k][0]=i;
                ans[k][1]=i+1;
            }
            else{
                ans[k][0]=ans[k][1]=i;
                ans[k+1][0]=ans[k+1][1]=i+1;
                k++;
            }
        }
        printf("%d\n",k);
        for(int i=1;i<=k;i++){
            printf("%d %d\n",ans[i][0],ans[i][1]);
        }
    }
    return 0;
}
```


---

## 作者：SoyTony (赞：1)

（加粗貌似寄了……）

前情提要：本做法可同时解决简单与困难两道题。

首先考虑简单版，也就是只含有 $-1$ 和 $1$ 的情况。

需要知道的第一个信息：分成的子段长度只为 $1$ 或 $2$。

显然长度为 $2k$ 的分成两个偶数段，所得结果不变。长度为 $2k+1$ 的分割成 $2k$ 与 $1$ 两个结果也不变。

第二个信息：存在方案的必要性为起初输入的数列求和是偶数。

将一个数的贡献改变正负，显然会造成大小为 $2$ 的影响，于是起初的和一定为偶数。

设起初和为 $sum$。

我们只要找到 $\dfrac{|sum|}{2}$ 个长度为 $2$ 的段，使得其中第二个数（变号的）与 $sum$ 的正负相同。剩余的全部按照长度为 $1$ 分割即可。

（不难发现，加入 $0$ 之后没有实质上改变。于是也就解决掉困难版）

---

## 作者：Jamison (赞：0)

### 题目大意
给定一个只有 $ -1 $ 和 $1$ 的数组，要将其分成若干个区间 **（区间数量没有限制）**。每个区间按照 $ + $ $- $ $+$ $ -$ 的顺序进行计算，要使每个区间加起来为 $0$。

### 题目思路
既然要结果为 $0$，那么为了方便，我们可以让每一个区间都为 $0$，同理，我们可以让两两一组。

- 当两数相等时，即两数是 $1$，$1$ 或 $-1$，$-1$，那么我们可以直接将两数分到一个区间内，那么此区间和就为 $0$。

- 当两数不相等时，即两数是 $1$，$-1$ 或 $-1$，$1$，那么我们可以直接将两数分别给到一个区间，同样的，这两个区间加起来也为 $0$。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200005],l[200005],r[200005],s;
int main()
{
	cin>>t;
	while(t--)
	{
		s=0;
		memset(l,0,sizeof(l));//记得要清零！！！
		memset(r,0,sizeof(r));
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(n&1) {cout<<-1<<"\n";continue;}
		for(int i=1;i<=n;i+=2)//两两判断
		{
			if(a[i]==a[i+1] ) //第一种情况
			{
				s++;
				l[s]=i,r[s]=i+1;
			}
			else //第二种情况
			{	
				l[s+1]=i,r[s+1]=i;
				l[s+2]=i+1,r[s+2]=i+1;
				s+=2;
			}
		}
		cout<<s<<endl;
		for(int i=1;i<=s;i++) cout<<l[i]<<" "<<r[i]<<endl;
	}
	return 0;
}
```

update 2022.10.27 

解释一下什么时候输出 $-1$，明显如果是奇数，则两两判断后会多出一个 $1$ 或
 $-1$,答案就明显不是 $0$ 了，还是很好理解的。






---

