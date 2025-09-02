# Rebellion

## 题目描述

You have an array $ a $ of size $ n $ consisting only of zeroes and ones. You can do the following operation:

- choose two indices $ 1 \le i , j \le n $ , $ i \ne j $ ,
- add $ a_{i} $ to $ a_{j} $ ,
- remove $ a_{i} $ from $ a $ .

Note that elements of $ a $ can become bigger than $ 1 $ after performing some operations. Also note that $ n $ becomes $ 1 $ less after the operation.

What is the minimum number of operations needed to make $ a $ non-decreasing, i. e. that each element is not less than the previous element?

## 说明/提示

In the first test case, $ a $ is already non-decreasing, so you don't need to do any operations and the answer is $ 0 $ .

In the second test case, you can perform an operation for $ i = 1 $ and $ j = 5 $ , so $ a $ will be equal to $ [0, 0, 1, 2] $ and it becomes non-decreasing.

In the third test case, you can perform an operation for $ i = 2 $ and $ j = 1 $ , so $ a $ will be equal to $ [1] $ and it becomes non-decreasing.

## 样例 #1

### 输入

```
4
8
0 0 1 1 1 1 1 1
5
1 0 0 1 1
2
1 0
11
1 1 0 0 1 0 0 1 1 1 0```

### 输出

```
0
1
1
3```

# 题解

## 作者：lenlen (赞：13)

### $Problem$

题目大意：给你一个序列，一次操作可以将一个点删除并且加到另一个点上，求变成不降序列的最小操作次数。

数据范围： $t \leq 10^4,\sum n \leq 2 \times 10^5$。

### $Solution$

最小的操作次数，又是不降序列，可以想到是把原序列变成 $000 \cdots 111$。

考虑最优的转移方法，即删除前面一个 $1$ 补到最后一个 $0$，若序列为目标序列，输出答案即可。

若删除 $0$ 肯定不优，因为我们按上述方法一次操作可以将 $0$ 变为 $1$，其实等价于删除 $0$，而且还删除了一个阻碍我们到达目标状态的 $1$。

删除 $1$ 补到其他的 $1$ 上肯定不优，理由同上。

### $Code$

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7232;
int t,n,m;
int a[N],ans;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        int l=1,r=n;ans=0;
        while(l<r)
        {
            while(!a[l]&&l<r) ++l;
            while(a[r]&&r>l) --r;
            if(l>=r) break;
            a[l]=0;a[r]=1;ans++;
        }
        printf("%d\n",ans);
    }
}
```


---

## 作者：1qaz234Q (赞：4)

### 题意简述
输入 $t$，表示有 $t$ 组数据。对于每组数据，输入 $n$，表示序列 $a$ 的长度，然后输入序列 $a$。每次操作从 $a$ 中选取 $a_i$ 和 $a_j$，让 $a_j$ 加上 $a_i$，接着把 $a_i$ 删除。求让 $a$ 成为不降序列的最小操作次数。
### 题目分析
因为要使操作次数最小，所以我们只需要让 $a$ 中的数加到 $1$，就可以了，没必要加到更大的数。因为要使 $a$ 成为不降序列，所以我们操作后 $0$ 会排在前面，$1$ 会排在后面。

我们可以定义的一个变量 $cnt$ 来储存 $a$ 中的 $0$ 的个数。每次输入 $a$ 中的数后并且当前的数为 $0$，就让 $cnt$ 加上 $1$。

然后循环枚举 $a$ 中第 $1$ 个到第 $cnt$ 个数，如果这个数为 $1$ 即这个数需要删除，就让答案加上 $1$。最后输出答案。

时间复杂度为 $O(tn)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
bool a[N];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        int cnt=0;//a中的0的个数
        int ans=0;//让a成为不降序列的最小操作次数
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(!a[i]){//如果当前的数为0
                cnt++;
            }
        }
        for(int i=1;i<=cnt;i++){
            if(a[i]){//如果这个数需要删除
                ans++;
            }
        }
        cout<<ans<<endl;
    }
    
}
```

---

## 作者：Huhu12346 (赞：1)

题目大意：给定一个 $01$ 数组，每一次操作可以任意选择下标 $i$，$j$，使得 $a_j\mathrel{+}=a_i$ 并删掉 $a_i$，问最少多少次操作之后可以使得数组是非严格单调递增的。

思路：其实，对于 $01$ 数列，非严格单调递增就是使得后面的数是 $1$ 就行了，没必要说还要加到 $2$ 去，模拟一下就会知道，其实就是看有多少数字是错位的，也就是不满足单调递增顺序的。

如下：

1.先将数据输入，并用 sort 进行排序：
```cpp
cin>>t;
while(t--)
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)	
	{
		cin>>a[i];
		b[i]=a[i];
    	}
		sort(a+1,a+n+1);
 }
```
2.定义 $cnt$ ，并循环判断错位:
```cpp
for(int i=1;i<=n;i++)
{
	if(a[i]!=b[i])
	{
		cnt++;
	}
}
```
3.最后，输出 $cnt/2$ 即可。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500050],b[500050],t;
int main()
{
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)	
		{
			cin>>a[i];
			b[i]=a[i];
		}
		sort(a+1,a+n+1);
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=b[i])
			{
				cnt++;
			}
		}	
		cout<<cnt/2<<endl;
	}
	return 0;
}
```

---

## 作者：Scorilon (赞：1)

给定一个长度为 $n$ 的序列，只包含 $0$ 和 $1$。

给定一个操作，每次选择一个 $i$ 和一个 $j$，$a_j+=a_i$，删去 $a_i$。

求使其变成不降序列的最小操作次数。

我们可以发现，因为是不下降序列，所以我们只要保证每一项小于或等于前一项即可，那么我们就没有必要令某一项 $>1$，因此，考虑将每一个在前面的 $1$ 往后填补后面的 $0$，形成一个类似于 $0,0,0,\dots,1,1,1$ 的序列。

最坏时间复杂度是 $O(n)$。

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int t;
int n;
int a[100005];

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		int ans=0,l=1;//l用于记录下一个1的位置
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=n;i>=1;i--) {
			if(a[i]) continue;
			for(int j=l;j<=i;j++) {
				if(a[j]) {
					l=j;
					break;
				}
			}
			if(!a[l]) break;
			a[l]=0;
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：1)

如果删去一个 $0$，对其它数没有影响。如果删去一个 $1$，可以填补后面的 $0$。

枚举最终 $0$ 前缀对应的原序列前缀 $p$，则需要删去 $a_1\sim a_p$ 所有的 $1$，并删去没有被前面删去的 $1$ 填补的后面的 $0$。设 $s$ 为 $a$ 的前缀和，即 $s_p + \max(0, (n - p) - (s_n - s_p) - s_p)$。

对 $p\in [0, n]$ 求最小值即可。[代码](https://codeforces.com/contest/1746/submission/176411627)。

---

## 作者：tanghg (赞：1)

思维题，很好玩。

## 题目翻译：

有一个零一数组，你可以进行下面的三种操作：

1. 选定 $i$ 和 $j$。 
2. $a_j$ 加上 $a_i$，然后删除 $a_i$
3. 删除 $a_i$

问： 最少多少次 $2,3$ 号操作可以使这个零一数组变成一个不下降数组。

## 思路：

可以想到，最好的思路就是

$\underbrace{0,0,0,\cdots ,0,0,}_A \underbrace{1,1,1,\cdots ,1,1,1}_B$


A 为 $0$ 的数量，B 为 $1$ 的数量。

但是，现实可能是参差不齐的零一混杂，怎么办呢，“挪”吧。

从头过一遍，先统计所有 $0$ 的数量。

然后统计 第 $i$ 个数字之前所有 $1$ 的数量（包括 $i$），然后每碰到一个 $0$ 就让 $0$ 的数量减 $1$， 等什么时候平衡了也就说明“空“（也就是 $0$   的位置） 都被填上了。

相当于每碰到一个 $1$ 就把它放到最后面的第一个“空”上， 重复这个动作，直到变成上方的那个图。

不理解的可以自己画个图看看。

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MAXN=1e5+5;
ll t,n,a[MAXN];
int main(){
    cin>>t;
    for (int i = 1; i <=t ; ++i) {
        scanf("%lld",&n);
        ll num0=0,num1=0;
        bool f= false;
        for (int j = 1; j <=n ; ++j) {
            scanf("%lld",&a[j]);
            if(!a[j]){
                ++num0;
            }
        }
        for (int j = 1; j <=n ; ++j) {
            if(a[j]){
                ++num1;
            }else if(!a[j]){
                --num0;
            }
            if(num0==num1){
                f= true;
                printf("%lld\n",num0);
                break;
            }
        }
        if(!f){
            printf("0\n");
        }
    }
    return 0;
}
````

---

## 作者：waters__god (赞：0)

## 题目描述
给你 $t$ 个 $01$ 数列，可以把一个元素删除并把它加到另一个元素上，让你分别求出使它们变成不降数列的最小操作次数。
## 思路
最简单的思路就是：把数列变成 $000...111$ 这样的数列。
那么如何将数列变成这样的数列呢？

第一种情况是：把前面的 $1$ 补到后面的 $0$ 上，删除前面的 $1$，这样是最优的。第二种情况是：删除 $0$，这样不优，因为第一种情况其实和这种情况是等价的，而且还把前面的 $1$ 顺便删除了。第三种情况是：删除 $1$ 补到后面的 $1$ 上，这样同样不优，因为这样还是会出现多余操作的情况，比如有这样一个数列：$100101$，将第一个 $1$ 补到后面的 $1$ 上，则数列变为 $00102$,不如第一种情况 $00111$ 优异。

根据上面的推论，就可以开始写代码了。

## 代码
```c++

#include<bits/stdc++.h>//万能头
using namespace std;
int t,n,a[100001],ans;
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        int l=1,r=n;
        ans=0;
        while(l<r)//进行删除&累计操作
        {
            while(!a[l]&&l<r) ++l;
            while(a[r]&&r>l) --r;
            if(l>=r) break;
            a[l]=0;a[r]=1;ans++;
        }
        cout<<ans<<'\n';
    }
}
```

点个赞再走吧~

---

## 作者：Lemon_zqp (赞：0)

### 思路
题目要求最小的操作次数，又是不降序列，可以想到是把原序列变成 $000⋯111$，输入时判断有多少个 $0$，这个个数就是目标序列最后一个 $0$ 的下标，那么我们只要判断原本是 $1$ 的位置是不是 $1$，也就是从最后一个 $0$ 的下标加一开始遍历到末尾，看看有几个不是 $1$ 的数，输出个数即可。

### 代码
```
#include<bits/stdc++.h>
using namespace std;

int a[100005];

int main()
{
    int t, zero_num = 0, ans = 0;
    cin >> t;
    for(int i = 1; i <= t; i++)
    {
        int n;
        cin >> n;
        for(int j = 1; j <= n; j++)
        {
            cin >> a[j];
            if(a[j] == 0)
            {
                zero_num++;
            }
        }
        for(int j = zero_num + 1; j <= n; j++)
        {
            if(a[j] != 1)
            {
                ans++;
            }
        }
        cout << ans << endl;
        ans = 0;//初始化
        memset(a, 0, sizeof(a));
        zero_num = 0;
    }
    
    return 0;
}
```


---

## 作者：Steve_xh (赞：0)

# 题面
[题目传送门](https://www.luogu.com.cn/problem/CF1746B)

**题目大意：**
给出 $n$ 段只包含 $0$ 和 $1$ 的序列，每次操作可以将其中一个数加上另一个数，并将另外那个数删除（变成 $0$），求最少要多少次操作可以将这段序列变成递增序列。

# 思路
首先我们得知道题目要求我们最终的序列长什么样。通过测试我们能得知最终序列的最优解就是将原序列排序，也就是说最终序列一定长这样：

$$000...111...$$

其中 $0$ 和 $1$ 的数量不定。最终的 $0$ 都会在前面，那我们就统计 $0$ 的个数，再判断应有的 $1$ 的位置有多少个 $0$，这样就能知道有多少个 $0$ 不在自己的位置上，就操作一次把 $1$ 移到这个位置，最后不断累加统计就能得出最终答案了。

# 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10005];
int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1,t,sum0=0,ans=0;i<=n;i++){
        sum0=ans=0;
        cin>>t;
        for(int j=1;j<=t;j++)
            cin>>a[j],sum0+=(a[j]==0);
        for(int j=sum0+1;j<=n;j++)
            ans+=(a[j]!=1);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：xq_z (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1746B)


# 思路


对于有多组操作的题，可以用这样的代码：


```cpp
int T;
cin>>T;
while(T--){
	//操作
}
```

因为数组只有 $0$ 或 $1$，所以排序完了的数组一定是 $0$ 在前，$1$ 在后的，所以我们先统计 $0$ 的个数。这时，统计的 $0$ 个数就是我们排序完最后一个 $0$ 的位置，后面就全是 $1$ 了。我们再从这个位置的后一个开始遍历是不是 $1$，如果这个数不是 $1$，所需要操作的次数就 $+1$。


最后输出这个操作的次数就行了。


# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10005];
int main(){
    int T;
    cin>>T;
    while(T--){
        int n,ans=0,sum_z=0;	
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(a[i]==0) sum_z++;	//统计0的个数
        }
        for(int i=sum_z+1;i<=n;i++){
            if(a[i]!=1) ans++;	//不是1就操作数加1
        }
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：__Tonycyt__ (赞：0)

## 题目大意  
题意说的不是很直接。  
给你一个 $01$ 序列，每一次操作可以将一个数删除并且加到另一个数上，求变成不降序列的最小操作次数。    
## 解决方法
~~可以求个导，让导数恒非负。~~  
作者上来就想的是 `std::vector`，发现能做。  
### 具体讲一下：  
这个序列最后可以变成 $000\cdots111$。  

1. 删除 $0$，反而不如删除前面一个 $1$ 补到最后一个 $0$，因为后者相当于删除一个 $0$ 以及去掉一个阻碍的 $1$。  
1. 删除 $1$ 补在 $1$ 上面也不好，理由和上面一样。  
1. 删除后面一个 $1$ 补到前面一个 $0$，反而增加了阻碍不降序列的数字个数。  
1. 删除前面一个 $1$ 补到最后一个 $0$，最优方案。

然后~~0pts~~AC了……  
## AC代码  
### 无毒放心使用。
```cpp
//----------前置预处理----------
#include<cstdio>
#include<vector>
using namespace std;
//----------输入输出速度优化----------
inline int read(){//读优
	int f=1,x=0;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar(); 
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

inline void write(int x){//写优
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
    putchar(x%10+'0');
}
//----------变量定义----------
vector<int> a(200010);//开vector注意数据范围
int t,n,m,ans,l,r;
//----------主函数----------
int main(){
	t=read();
    while(t--){
    	n=read();
        for(int i=1;i<=n;i++) a[i]=read();
        l=1;
		r=n;
		ans=0;
        while(l<r){
            while(!a[l] && l<r) ++l;
            while(a[r] && r>l) --r;
            if(l>=r) break;
            a[l]=0;
			a[r]=1;
			ans++;
        }
        write(ans);
        putchar('\n');
    }
    return 0;//勿忘return 0;
}
```

---

## 作者：BEST_CAT (赞：0)

# CF1746B Rebellion 题解：

## 题意：
给你一个序列，一次操作可以将一个点删除并且加到另一个点上，求变成不降序列的最小操作次数。

## 思路：

要求不降，并且要最小操作次数，就把序列变为 $0000......1111$ 即可。

于是我们可以不断将最考左的 $1$ 加到最靠右的 $0$ 上，直到最靠右的 $0$ 在最靠左的 $1$ 的左边，就表明已经将序列变为 $0000......1111$ 了。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005],l,r,ans,k1[100005],k2[100005],s1,s2;//k1,k2统计1和0出现的位置,s1,s2为1和0的数量
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		s1=s2=ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]){
				k1[++s1]=i;//统计1
			}
			else{
				k2[++s2]=i;//统计0
			}
		}
		if(!s1||!s2){//特判
			printf("0\n");
			continue;
		}
		l=1;//找最左1
		r=s2;//找最右0
		while(k1[l]<k2[r]&&l<=s1&&r>=1){//最右0在最左1右边，1和0都还有就继续
			ans++;
			l++;
			r--;
		}
		cout<<ans;
	}
	return 0;
}

```


---

## 作者：alm_crax (赞：0)

## [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1746B)

## [CF原题传送门](https://codeforces.com/problemset/problem/1746/B)

## 思路
首先，题目说明该序列仅由 $0$ 和 $1$ 组成，要用最少操作次数使序列不下降，不难发现最终的序列为 $0\cdots0,1\cdots1$（ $0$ 和 $1$ 的个数都可以为 $0$ 个）。

那么，知道了初始和最终状态，就很好实现了。

只需要不断将最左的 $1$ 加到最右的 $0$ 上，直到最右的 $0$ 在最左的 $1$ 的左边，就说明已经是最终状态了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005],l,r,ans,k1[100005],k2[100005],s1,s2;
//k1,k2分别统计1和0出现的位置
//s1,s2分别为1和0的数量
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		s1=s2=ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i])
			{
				k1[++s1]=i;//统计1的位置
			}
			else
			{
				k2[++s2]=i;//统计0的位置
			}
		}
		if(!s1||!s2)//特判，没有1或0的情况
		{
			printf("0\n");
			continue;
		}
		//下面是将最左1加到最右0(不实际加，只是思路)
		l=1;//用来找最左1的位置
		r=s2;//同上，找最右0
		while(k1[l]<k2[r]&&l<=s1&&r>=1)
		//最右0在最左1右边，1和0都还有就继续
		{
			ans++;
			l++;
			r--;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Colorful_Unicorn (赞：0)

## 思路
这题我们不难发现，答案最终会变为 $0,0,0,......1,1,1$ 这样的形式。

因为最终所有的 $1$ 都将到序列最后去（我们在删除时肯定优先删除 $1$ 因为我们肯定是让大的越少越好），于是我们可以统计出在这串序列中 $1$ 的个数也就是最终在在前面连续是一的个数。再将本来就在前面的数中是 $1$ 的统计出来，两个数相减即可。

# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int kMaxN=1e5+5;
int n,m,a[kMaxN],flag,ans[kMaxN],cnt;
int main()
{
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		cin >> m;
		for (int j=1;j<=m;j++)
			cin >> a[j];
		for (int j=1;j<=m;j++)//统计出在这串序列中1的个数
		{
			if (a[j]==1)
				flag++;
		}
		for (int j=m-flag+1;j<=m;j++)//统计出在这串序列中本来就在前面的1的个数
		{
			if (a[j]==1)
				cnt++;
		}
		ans[i]=flag-cnt;//相减即是答案
		flag=0;  //记得清零
		cnt=0;
	}
	for (int i=1;i<=n;i++)
		cout << ans[i] << "\n";
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 分析
我们不难发现，因为这是不下降序列，所以我们只需要保证每一项小于等于前一项就可以啦。因此，我们将每一个在前面的 $1$ 往后填补后面的 $0$，形成一个类似于 $000\dots111$ 的序列即可。
## CODE
```cpp
#include<bits/stdc++.h>

using namespace std;

int t;
int n;
int a[200000];

int ans;
int s;

int main() 
{
	cin>>t;
	while(t--) 
	{
		ans=0;
		s=1;
		
		cin>>n;
		for(int i=1;i<=n;i++) 
		{
			cin>>a[i];
		}
		
		for(int i=n;i>=1;i--) 
		{
			if(a[i]==0) 
			{
				for(int j=s;j<=i;j++) 
				{
					if(a[j]==1) 
					{
						s=j;
						break;
					}
				}
							
				if(a[s]==0) 
				{
					break;
				}
				
				a[s]=0;
				ans++;
			}
		}
		
		cout<<ans<<endl;
	}
	
	return 0;
}
```


---

## 作者：scpchangyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1746B)

### [思路]

不下降序列只需要保证每一项都小于等于前一项。所以将每一个 $1$ 往后填补 $0$，形成类似于 $000 \dots 111$ 的序列就 $\verb!done!$ 了。

### [代码]

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<ctime>
#include<string>
#include<cstring>
using namespace std;
int t,n,a[200010],ans,p;
int main() 
{
	scanf("%d",&t);
	for(int o=1;o<=t;o++)
	{
		scanf("%d",&n);
		ans=0,p=1;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=n;i>=1;i--){
			if(a[i]==0){
				for(int j=p;j<=i;j++){
					if(a[j]==1){
						p=j;
						break;
					}
				}
				ans++;
				if(a[p]==0)break;
				a[p]=0;
			}
		}
		cout<<ans-1<<'\n';
	}
	return 0;
}
```

---

