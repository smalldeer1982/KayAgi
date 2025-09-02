# Salem and Sticks

## 题目描述

## 题目概述
$Salem$ 给了你 $n$ 个木棍，它们的长度分别为 $a_1,a_2,\cdot \cdot \cdot a_n$。

对于每一根木棍，你可以把它的长度变为任意整数（即收缩或者拉伸）。把一根木棍的长度 $a$ 变为 $b$ 将花费 $|a-b|$ 的价格。

如果说一根木棍对于整数 $t$ 是好的，则需要满足要求 $|a_i - t| \leq 1$。

现在 $Salem$ 让你去改变一些木棍的长度（可能全部或不改变），使所有木棍对于整数 $t$ 是好的，并让花费的价格尽可能小，$t$ 的值不是固定的值，您可以让它成为任意正整数。

现在请你输出 $t$ 的值和最小花费的价格。如果有多种情况，请输出任意一个。

## 说明/提示

对于第一个样例，我们可以把长度为 $1$ 的木棍变成 $2$，长度为 $10$ 的木棍变成 $4$，将花费 $|1-2|+|10-4|=1+6=7$ 的价格，最终长度 $[2,4,4]$ 是适合 $t=3$ 的。

对于第二个样例，我们不需要作出任何改变，所有木棍对于 $t=2$ 都是好的。

## 样例 #1

### 输入

```
3
10 1 4
```

### 输出

```
3 7
```

## 样例 #2

### 输入

```
5
1 1 2 2 3
```

### 输出

```
2 0
```

# 题解

## 作者：Refined_heart (赞：4)

搬运加完善官方题解……

官方题解给出的方法是暴力枚举每一个t，并计算它的价值，其中，若$|ai-t|<=1$的话，则是有效的解。

于是，我们暴力枚举100个t并计算价值，我的函数是这样的：

```cpp
for(register ll i=1;i<=100;i++){
		sum=0;
		for(register ll j=1;j<=n;j++){
			// i+1 i i-1
			sum=sum+(min(min(abs(a[j]-i-1),abs(a[j]-i)),abs(a[j]-i+1)));
		}
		if(minn.l>sum){
			minn.t=i;
			minn.l=sum;
		}
	}
```
minn开了一个结构体，大概储存最小的价值和t.

注意sum加的地方，算出三种情况的价值，分别是t+1,t-1,t，然后sum加上最小的，注意用cmath库取绝对值。

完整代码如下(跑的不是很快):

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#define ll long long
using namespace std;
struct node{
	ll l,t;
}minn;
ll sum=0,a[1010];
int main(){
	minn.l=100000;
	ll n;
	cin>>n;
	for(register ll i=1;i<=n;i++)
	  cin>>a[i];
	for(register ll i=1;i<=100;i++){
		sum=0;
		for(register ll j=1;j<=n;j++){
			// i+1 i i-1
			sum=sum+(min(min(abs(a[j]-i-1),abs(a[j]-i)),abs(a[j]-i+1)));
		}
		if(minn.l>sum){
			minn.t=i;
			minn.l=sum;
		}
	}
	cout<<minn.t<<" "<<minn.l<<endl;
	return 0;
}
```

程序不足的地方还请各位指教。

---

## 作者：Lovely_Elaina (赞：3)

一眼丁真，鉴定为暴力。

暴力枚举 $t$，题目要求 $|a_i-t|\le 1$，也就是要使得 $t-1\le a_i \le t+1$。

那么易得，最优修改方案为：

$\begin{cases} t-1 &a_i< t-1  \\\\ t+1 &a_i>t+1 \\\\  \text{不变} &t-1\le a_i \le t+1 \end{cases}$

```cpp
#include<iostream>
#include <bits/stdc++.h>
#define min(a,b) (a<b?a:b)
#define endl '\n'
using namespace std;
const int N = 105;

inline int read(){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}

int a[N],t,mi;

int main(){
    mi = 100000;

    int n = read();

    for(int i = 1; i <= n; i++)
        a[i] = read();

    for(int k = 1; k <= 1000; k++){
        int sum = 0;
        for(int i = 1; i <= n; i++){
            if(k-1 <= a[i] && a[i] <= k+1){
                continue;
            }
            sum += (a[i]<k-1?k-1-a[i]:a[i]-(k+1));
        }
        if(sum < mi){
            mi = sum;
            t = k;
        }
    }

    printf("%d %d\n",t,mi);

	return 0;
}
```

---

## 作者：_Haoomff_ (赞：3)

作为一道暴力题，我们一定要尊重它的存在，乖乖地打暴力吧，毕竟数据那么小，两层循环也就 $1000 \times 1000$，不会超时。

输入完后，遍历数组，分三种情况：
+ 当 $a_i<t$ 时，将 $a_i$ 的值改为 $t-1$。
+ 当 $a_i=t$ 时，$a_i$ 的值不变。
+ 当 $a_i>t$ 时，将 $a_i$ 的值改为 $t+1$。

依上模拟即可，代码就不放了，别的题解代码也挺详细的了。

~~主要原因是：不做黄及以下题目，所以没打。~~

---

## 作者：hsfzLZH1 (赞：2)

## 题目大意

有一个有 $n$ 个数字的数列 $a_i$ ，一个元素 $a_i$ 被称为是对 $t$ 合法的当且仅当 $|a_i-t|\le 1$ 。你可以任意增长或剪短木棍。现在你需要确定一个 $t$ ，然后对木棍的长度进行修改，使所有元素都是对 $t$ 合法的，且木棍长度的变化总量最小。输出这个 $t$ 和此时木棍长度的变化总量。

$1\le n\le 1000,1\le a_i\le 100$ 

## 解题思路

观察到 $t$ 与 $a_i$ 的关系是不好确定的。观察到数据范围比较小， $t$ 的范围是可以确定在 $[1,100]$ 的。考虑枚举 $t$ ，利用贪心的思想，若 $a_i$ 合法，则不做任何修改；若 $a_i$ 不合法且小于 $t$ ，将 $a_i$ 修改为 $t-1$ ；若 $a_i$ 不合法且大于 $t$ ，将 $a_i$ 修改为 $t+1$ 。

得出结论：对每个 $t$ ，木棍长度的变化总量为 $\sum_{i=1}^n max\{|a_i-t|-1,0\}$ 。

时间复杂度 $O(n\times max\{a_i\})$ 。空间复杂度 $O(n)$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1010;
typedef long long ll;
int n,a[maxn],t,nww,ans=2e9;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=1;i<=100;i++)
	{
		nww=0;
		for(int j=1;j<=n;j++)nww+=max(0,abs(a[j]-i)-1);
		if(nww<ans)ans=nww,t=i;
	}
	printf("%d %d\n",t,ans);
	return 0; 
}
```

---

## 作者：Rachel_in (赞：2)

对于此题我们可以发现a数组的数值范围很小且t必定在此范围中。故我们可以大力枚举t的取值，然后再扫一遍a数组，记录答案。

代码如下


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],t,ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	ans=0x7fffff;
	for(int i=1;i<=100;i++)
	{
		int k=0,kk=0;
		for(int j=1;j<=n;j++)
		{
			k=min(abs(a[j]-(i+1)),min(abs(a[j]-(i)),abs(a[j]-(i-1))));//记录最小值
			kk+=k;//累加			
		}
		if(kk<ans)//更新答案
		{
			ans=kk;
			t=i;
		}
	}
	printf("%d %d\n",t,ans);
	return 0;
}
```

---

## 作者：ssSSSss_sunhaojia (赞：1)

[**原题传送门**](https://www.luogu.com.cn/problem/CF1105A)
# 题面：
给定 $n$ 个数，要求找出一个 $t$，使得把 $n$ 个数中每一个数变得与 $t$ 至多相差 $1$ 后，变化总量最小。
# 思路：
可以暴力枚举 $t$，对于每一个 $t$，遍历一遍这 $n$ 个数，求出每个数的变化量，最后求出变化总量，更新最小值。
# 代码：
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
typedef long long LL;
LL n, a[1100], sum, mis = 1e14, miid; 
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
    cin >> n; 
    for(re int i = 1; i <= n; i ++) cin >> a[i]; 
    for(re int t = 1; t <= 1000; t ++) {
        sum = 0; 
        for(re int j = 1; j <= n; j ++) {
           if(a[j] > t) sum += a[j] - (t + 1); 
           if(a[j] < t) sum += (t - 1) - a[j]; 
        }
        if(sum < mis) mis = sum, miid = t;
    }
    cout << miid << " " << mis;
    return 0; 
}

```

---

## 作者：fkcufk (赞：0)


[题目传送门](https://www.luogu.com.cn/problem/CF1105A)

推荐在我的博客里阅读，效果更好哦。

解析：

由于本题的数据范围很小，我们可以直接暴力枚举 $t$。每次都遍历一遍 $a$ 数组，不会超时。

最后输出 $t$ 和 $mn$ 即可。

代码：
```cpp
#include<bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
using namespace std;
const int inf=INT_MAX;
int n,m;
int mn=inf;
int a[1005],t;
int main(){
	fast; // 加速
    cin>>n; // 输入
    for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=1005;i++){ // 遍历
		int k1=0;
		for(int j=1;j<=n;j++){
			if(a[j]<i) k1+=abs(i-1-a[j]);
			else if(a[j]>i) k1+=abs(i+1-a[j]);
		}
		if(k1<mn) t=i,mn=k1;
	}
	cout<<t<<' '<<mn; // 输出
	return 0;
}
```


---

## 作者：__Tonycyt__ (赞：0)

这题一看 $\color{#FFFFFF}\colorbox{#F39C11}{普及-}$，~~蒟蒻吓呆了~~感觉不会用太多高级算法吧，于是蒟蒻打了个暴力枚举。  
将 $t\in[1,100]$ 逐个枚举，就出答案了。具体见代码。  
### code
```cpp
//----------初始化----------
#include<bits/stdc++.h>
using namespace std;
#define abs(m) m>=0?m:-m;
//----------输入输出优化----------
inline long long read(){//读入优化
	long long f=1,x=0;
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

inline void write(long long x){//输出优化
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
    putchar(x%10+'0');
}
//----------变量----------
struct node{long long l,t;}QwQ;
long long sum=0,a[1005],n;
//----------主函数----------
int main(){
	QwQ.l=100000,n=read();//初始化
	for(long long i=1;i<=n;i++) a[i]=read();
	for(long long i=1;i<=100;i++){
		sum=0;//sum重新赋值
		for(long long j=1;j<=n;j++) sum=sum+(min(min(abs(a[j]-i-1),abs(a[j]-i)),abs(a[j]-i+1)));//计算价值
		if(QwQ.l>sum) QwQ.t=i,QwQ.l=sum;//如果价值比之前的都要小就替换
	}
	write(QwQ.t),putchar(' '),write(QwQ.l);
	return 0;//勿忘return 0;
}
```

---

## 作者：guozhetao (赞：0)

## 题意
给定 $n$ 个数 $a_i(1 \leq a_i \leq 10^3,1 \leq i \leq n)$，求出 $t$ 并改变每一个 $a_i$，使得每一个 $|t - a_i| \leq 1$。
## 思路
首先，因为 $1 \leq a_i \leq 10^3$，所以 $1 \leq t \leq 10^3$，否则必然有一种方法找到一个更优的 $t$。我们可以枚举 $t$。

接着，我们求每一个 $t$ 对应的花费 $ans$。显然，因为要让 $|t - a_i| \leq 1$，所以：

- 当 $|t - a_i| \leq 1$ 时，$ans$ 不需要改动。
- 否则，我们只需要让  $|t - a_i| = 1$ 即可，无需让 $a_i = t$。因此 $ans \gets ans + |t - a_i| - 1$ 即可。

## 代码

[AC 记录](https://www.luogu.com.cn/record/108153519)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],ans1 = 0,ans2 = 1e9;
int find(int t) {
	int ans = 0;
	for(int i = 1;i <= n;i++) {
		if(abs(a[i] - t) > 1) ans += abs(a[i] - t) - 1;
	}
	return ans;
}
int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	for(int t = 1;t <= 1000;t++) {
		if(find(t) < ans2) ans1 = t,ans2 = find(t);
	}
	printf("%d %d",ans1,ans2);
}
```


---

## 作者：FP·荷兰猪 (赞：0)

题意见题面。

本题的数据范围很小，n和a[i]都只到1000，直接双重循环搜一遍就可以了，详见代码：
```cpp
#include <iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int i,a[n+1],maxv;
	maxv=-1;
	for (i=1;i<=n;i++)
	{
		cin>>a[i];
		maxv=max(a[i],maxv);//maxv为枚举t的上限，即n个数的最大值
	}
	int cnt,ans,ii;
	ans=2147480000;
	for (i=1;i<=maxv;i++)//i用来枚举t的值
	{
		cnt=0;//cnt表示t=i时要花的最小价格
		for (int j=1;j<=n;j++)
		{
			if (a[j]-i>1)
			{
				cnt+=a[j]-i-1;//需要花钱把a[i]缩小
			}
			else if (i-a[j]>1)
			{
				cnt+=i-a[j]-1;//需要花钱把a[i]变大
			}
		}
		if (cnt<ans)
		{
			ii=i;//记录下标
		}
		ans=min(ans,cnt);
	}
	cout<<ii<<" "<<ans<<endl;
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

按题意暴力  
记录一下序列中的最大最小值，从最小枚举到最大，看看哪个数字得到的答案最小  
有一个需要注意的地方：我这里用的是abs(a[i]-t)-1表示花费，但是当a[i]==t的时候，花费应该是0，所以需要特判一下
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int a[N];

int main(void)
{
    rg int n = fast_IO::read(), minn = 100, maxn = 0, ans1 = 0, ans2 = 1e9;
    for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read(), minn = fast_IO::min(minn, a[i]), maxn = fast_IO::max(maxn, a[i]);
    for (rg int t = minn; t <= maxn; ++t)
    {
        rg int sum = 0;
        for (rg int i = 1; i <= n; ++i)
            if (abs(a[i] - t) > 1)sum += abs(a[i] - t) - 1;
        if (sum < ans2)ans1 = t, ans2 = sum;
    }
    printf("%d %d", ans1, ans2);
    return 0;
}

```

---

## 作者：一扶苏一 (赞：0)

## Solution

扯一句这场cf好鬼啊……五个题有四个暴力……剩下一个还是套路题……

由于 $a$ 极小，我们考虑直接枚举 $t$，然后求最小代价即可。时间复杂度 $O(\max\{a_i\}~\times~n)$

## Code

```cpp
#include <cstdio>


const int maxn = 1010;

int n;
int MU[maxn];

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (int i = 1; i <= n; ++i) qr(MU[i]);
	int ans = 0, tans = 1 << 30;
	for (int i = 1; i <= 100; ++i) {
		int s = 0;
		for (int j = 1; j <= n; ++j) s += std::min(abs(MU[j] - i), std::min(abs(MU[j] - i + 1), abs(MU[j] - i - 1)));
		if (s < tans) ans = i, tans = s;
	}
	qw(ans, ' ', true); qw(tans, '\n', true);
	return 0;
}```

---

## 作者：dunko (赞：0)

## **题目**
[Click here](https://www.luogu.org/problemnew/show/CF1105A)
## **思路**
看完题，n<=1000，当然是暴力啊，还要说什么吗？    
a[i]<=100,直接枚举a数组的最小值到最大值。比较修改大小，记录答案。
## **代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1111],ans1,ans2=1<<30,l=1<<30,r;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        l=min(l,a[i]);
        r=max(r,a[i]);//l为a数组中最小值，r为a数组中最大值
    }
    for(int i=l;i<=r;i++){//从l到r枚举
        int tot=0;
        for(int j=1;j<=n;j++){
            int x=min(abs(i-a[j]),min(abs(i-a[j]-1),abs(i-a[j]+1)));
            //加上修改的值，就是a[j]+1，a[j]-1,a[j]这三者中与当前枚举的答案的最小差值
            tot+=x;
        }
        if(tot<ans2) ans1=i,ans2=tot;//比较，记录
    }
    printf("%d %d\n",ans1,ans2);//输出
    return 0;
}
```

---

## 作者：vocaloid (赞：0)

枚举。枚举最终长度，计算花费，记录答案即可。

非常水，标准的 $\text{div.2 A}$ 题难度。

```cpp
#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
int n,a[MAXN],minx=2e9,maxn,ans,mincost=2e9;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		minx=min(minx,a[i]);
		maxn=max(maxn,a[i]);
	}
	for(int i=minx;i<=maxn;i++)
	{
		int sum=0;
		for(int j=1;j<=n;j++)
		{
			if(a[j]>i) sum+=a[j]-(i+1);
			else if(a[j]<i) sum+=(i-1)-a[j];
		}
		if(sum<mincost)
		{
			mincost=sum;
			ans=i;
		}
	}
	printf("%d %d\n",ans,mincost);
	return 0;
}
```

---

