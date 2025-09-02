# Strange List

## 题目描述

You have given an array $ a $ of length $ n $ and an integer $ x $ to a brand new robot. What the robot does is the following: it iterates over the elements of the array, let the current element be $ q $ . If $ q $ is divisible by $ x $ , the robot adds $ x $ copies of the integer $ \frac{q}{x} $ to the end of the array, and moves on to the next element. Note that the newly added elements could be processed by the robot later. Otherwise, if $ q $ is not divisible by $ x $ , the robot shuts down.

Please determine the sum of all values of the array at the end of the process.

## 说明/提示

In the first test case the array initially consists of a single element $ [12] $ , and $ x=2 $ . After the robot processes the first element, the array becomes $ [12, 6, 6] $ . Then the robot processes the second element, and the array becomes $ [12, 6, 6, 3, 3] $ . After the robot processes the next element, the array becomes $ [12, 6, 6, 3, 3, 3, 3] $ , and then the robot shuts down, since it encounters an element that is not divisible by $ x = 2 $ . The sum of the elements in the resulting array is equal to $ 36 $ .

In the second test case the array initially contains integers $ [4, 6, 8, 2] $ , and $ x=2 $ . The resulting array in this case looks like $  [4, 6, 8, 2, 2, 2, 3, 3, 4, 4, 1, 1, 1, 1, 1, 1] $ .

## 样例 #1

### 输入

```
2
1 2
12
4 2
4 6 8 2```

### 输出

```
36
44```

# 题解

## 作者：fanfansann (赞：5)

# B - Strange List
给你一个数组和整数 $x$ ，一个指针，会遍历整个数列，对于当前的数组 $q$ ，如果 $q$ 能被 $x$ 整除，则在数列的末尾加上 $x$ 份 $\cfrac{q}{x}$，当指针遇见不能被 $x$ 整除的时候就退出，指针就不会再动了。求最后的总价值。价值定义为最后整个数列的值的和。

$1 \leq a_i \leq 10^9,1 \leq t \leq 100,2 \leq x \leq 10^9,1 \leq n \leq 10^5$。

**Solution**

首先第一步还是分析性质。

我们发现 $q$ 能被 $x$ 整除，那么在数列的末尾加上 $x$ 份 $\cfrac{q}{x}$，对答案的贡献实际上就是 $x\times \cfrac{q}{x}=q$。这是解题的关键。我们发现不论是第一次还是第 $n$ 次，对答案的贡献都是 $q$，这样我们就不用暴力地按照题意模拟求总价值，而是直接加上 $q$ 即可。我们发现任何一个数，哪怕本来能被 $x$ 整除，但是把除数放到最后末尾，指针指向的时候，总有一次，会被除尽，也就是指针暂停，末尾不会再增加数字，可以开始计算最终的答案了。也就是一旦除出来的数不能被 $x$ 整除了，就 `break` 退出了。因为我们要每次加上 $q$ ，所以我们不能改变原数组，而我们需要一直除，来判断是否能继续被 $x$ 整除，所以我们可以把数组 $a$ `copy` 到数组 $b$。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 7, mod = 1e9 + 7;
typedef long long ll;
int n, m, t, x;
int a[N], b[N];
ll ans;
ll sum;

int main()
{
    scanf("%d", &t);
    while(t -- ) {
        ll ans = 0;
        scanf("%d%d", &n, &x);
        for(int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i]);
            b[i] = a[i];
            ans += a[i];
        }
        bool flag = 0;
        while(true) {
            for(int i = 1; i <= n; ++ i) {
                if(b[i] % x) {
                    flag = 1;
                    break;
                }
                ans += a[i], b[i] /= x;
            }
            if(flag) break;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

```

---

## 作者：vectorwyx (赞：2)

（本篇博客同步于[CSDN](https://blog.csdn.net/vectorwyx/article/details/112260203)）

如果 $x|q$，设 $t=\frac{q}{x}$，那么 $q$ 会分裂成 $x$ 个 $t$。而如果 $x|t$，那么这 $x$ 个 $t$ 又会分裂出 $x^{2}$ 个 $\frac{t}{x}$……很显然这是一个有终点的循环，每循环一次就会多出 $x^{k}$ 个 $\frac{q}{x^{k}}$。我们把当前循环中 $q$ 分裂出的 $x^{k}$ 个数看做 一个整体，每次循环都会使得数组里的元素和增加 $q$。同时，由于 $q\le 10^{9}$，所以循环次数为 $O(\log_{x}{q})$，这是一个上界为 $30$ 的数，直接模拟这个循环即可。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e5+5;
int a[N],cnt[N];

void work(){
	int n=read(),x=read();
	ll ans=0;
	fo(i,1,n) a[i]=read(),cnt[i]=0,ans+=a[i];
	fo(i,1,n){
		int t=a[i];
		while(t%x==0){
			t/=x;
			cnt[i]++;
		}
	}
	int flag=1;
	while(flag){
		fo(i,1,n){
			if(cnt[i]) cnt[i]--,ans+=a[i];
			else{
				flag=0;
				break;
			}
		}
	}
	printf("%lld\n",ans);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 思路
~~千万别暴力！~~

题目给了 $x$ 个整数 $\frac{q}{x}$，知道怎么约分的应该知道它的值为 $q$，所以不用按题目描述里那样把这一大串数一个一个添加到数组的末尾，可以用一个数组复制原数组的值进行运算（就是保存 $q$ 的值），原数组只需要模拟过程即可。

## 代码
```cpp
#include<iostream>
using namespace std;
#define int long long//不开 long long 见祖宗
void solve(){
	int n,x,ans=0,a[1000050],b[1000050];//定义
	bool p=true;//标记用
	cin>>n>>x;//输入
	for(int i=1;i<=n;i++){
		cin>>a[i];//输入
		b[i]=a[i];//复制
		ans+=a[i];//计算和
	}
	while(p==true){
		for(int i=1;i<=n;i++){//循环遍历
			if(b[i]%x){//不满足条件
				p=false;//更新标记的值
				break;//退出循环
			}
			else{
				ans+=a[i];//计算总和
				b[i]/=x;//分掉
			}
		}
	}
	cout<<ans<<endl;//输出
	return;//结束
}
signed main(){
    int T;
    cin>>T;
    while(T--){//T组数据
		solve();//调用
	}
    return 0;
}
```

---

## 作者：Amm_awa (赞：0)

[$\color{red}\fbox{\text{洛谷链接}}$](https://www.luogu.com.cn/problem/CF1471B)

[$\color{red}\fbox{\text{ CF 链接}}$](https://codeforces.com/contest/1471/problem/B)

## 分析
1. 题目中说：如果 $x \bmod q = 0$， 那么在数组末尾添加 $x$ 个 $\frac{q}{x}$，就是 $x \times \frac{q}{x}$，也就是将答案增加 $q$。
2. 数组扫完一遍时要回到开头，当 $x \bmod q \neq 0$ 时要 ```break```，并终止操作
3. 用一个二维数组 $a_{n2}$，其中 $a_{n0}$ 表示数组初始内容，$a_{n1}$ 表示数组当前内容。
4. 每个数在输入时也要计入答案总和里。
5. 要用 ```long long``` 存储答案。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,x,ans;//开 long long
int a[100005][2];//a[i][0] 表示数组初始内容，a[i][1] 表示数组现在的数据
inline int read()
{
    register int x=0,f=1;
    register char ch=getchar();
    while(!isdigit(ch))if(ch=='-')f=-1,ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}
inline void solve()
{
    register int i;
    register bool fl=0;//记录何时结束
    while(1)
    {
        for(i=1;i<=n;i++)
        {
            if(a[i][1]%x)
            //当 x 能整除现在的数组元素时，跳出循环
            {fl=1;break;}//记录 flag 为真，跳出循环
            ans+=a[i][0];//答案加上 a 数组初始数据
            a[i][1]/=x;
        }
        if(fl){break;}//跳出循环
    }
    cout<<ans<<'\n';
}
inline void readNum()
{
    register int i;
    t=read();
    while(t--)
    {
        n=read(),x=read();
        ans=0;
        for(i=1;i<=n;i++)
            {a[i][0]=read(),a[i][1]=a[i][0],ans+=a[i][0];}
      	     //输入 a[i][0],a[i][1]为数组当前数值
        solve();
    }
}
signed main()
{
    readNum();
    return 0;
}
```

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1471B)

这道题目让我们找到所有的数如果满足 $num[i] \bmod x=0$，我们的答案就要增加 $x$ 个 $\displaystyle \frac {num[i]} x$ 就可以了，我们发现总和不就是加上了 $num[i]$ 这个数了吗？我们就不用一个一个统计了。

不过这里第一次都是需要统计一遍的，这个可以在输入时统计。

我们用一个数组记录然后每次除以 $x$ 就可以了。

这里记得每次要重置答案。（非常重要！）

---
# AC代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
#define ll long long
const int N=2e5+10;
ll ans;//应该需要开long long
int t,n,x,num[N],now[N],k;
bool whether_break;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&x);
		ans=0;whether_break=0;//记得赋初值
		for(int i=1;i<=n;i++){
			scanf("%d",&num[i]);
			now[i]=num[i];
			ans+=num[i];
		}
		while(1){// 暴力枚举每次循环
			for(int i=1;i<=n;i++){
				if(now[i]%x!=0){
					whether_break=1;
					break;
				}
				ans+=num[i];now[i]/=x;
			}
			if(whether_break)break;//跳出
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1471B) & [CF链接](http://codeforces.com/problemset/problem/1471/B)

## 思路分析：

暴力枚举可能往后添加元素时越界爆栈，所以就要用一些简单的数学方法。

首先如果当前的 $q$ 满足要求，添加 $x$ 个 $\frac{q}{x}$ 对答案的贡献其实就是 $q$。例如：当前数是 $4$，$x=2$，第一次 $4$ 会贡献出 $2$ 个 $2$ 和为$4$，这 $2$ 个 $2$ 又分别会贡献出 $2$ 个 $1$ 和为 $2\times2=4$。所以无论运算多少次，每一次对答案贡献都为一开始的 $a_i$。只需要用一个数组模拟过程，另一个数组记录初始的 $a_i$。

## 代码：

```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,x,a[100010],b[100010];//a数组计算，b数组存初始值
long long ans;//不开long long见祖宗
void slove(){
	int i=1;//数组下标
	while(1){
		if(a[i]%x==0){//如果满足要求
			ans+=b[i];//记录答案
			a[i]/=x;//除
		}else{
			return;//否则结束
		}
		i=(i+1)%(n+1);//循环访问数组，每次取模防止爆int
	}
	return;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		ans=0;
		cin>>n>>x;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			ans+=a[i];//记录初始答案
			b[i]=a[i];//b存初始值
		}
		slove();
		cout<<ans<<endl;//输出答案
	}
	return 0;
}
```

---

## 作者：lmndiscyhyzdxss (赞：0)

## 题目
您将一个长度为 $ n $ 的数组 $ a $ 和一个整数 $ x $ 给了机器人。机器人的操作将会遵循以下原则：对于数组的元素进行迭代，当前的元素为 $q$。如果 $ q $ 被 $x$ 整除，那么机器人会将 $ x $ 个整数 $ \frac{q}{x} $ 添加到数组的末尾，然后移到下一个元素。否则，机器人停止工作。
请在机器人停止工作时确定数组所有值的总和。
## 分析
如果 $ q $ 能被 $ x $ 整除，则加上的 $ x\times\frac{q}{x} $ 的 $ x $ 和 $ \frac{1}{x} $ 互相抵消，总和还是 $ q $。反之，如果不能整除，就直接标记并退出，因为每次要加上 $ q $，我们需要多开一个数组来进行操作，记得初始化。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,t,h,p,a[100010],b[100010];
int main()
{
    cin>>t;
    for(int z=1;z<=t;z++)
	{
        cin>>n>>m,h=0,p=0;//初始化
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]),b[i]=a[i],h+=a[i];
        while(p==0)
		{
            for(int i=1;i<=n;i++)
			{
                if(b[i]%m!=0){p=1;break;}//判断
                h+=a[i],b[i]/=m;//进行操作
            }
        }
        cout<<h<<endl;
    }
    return 0;
}
```

---

## 作者：ckk11288 (赞：0)

首先我没有注意到数据规模，后来才发现范围很大。

在这之前我打了一个暴力模拟的代码，不知不觉就 RE 了,按照题目的数据规模不想想其他办法是无法解决的。

所以我的同学为我提供了灵感：仔细一算不难发现，我们每次都是把当前数 $q$ “分裂”成 $x$ 个 $q/x$ ，然而最终加到答案里的就是 $x×q/x$ 即 $q$。那么就不需要一个一个把数加到数组后面了，我们只需要长度为 $n$ 的数组进行运算，但需要把原数组里的数用另一个数组存下，即存下 $q$。方便运算（详见代码）。

**Code**
```cpp
#include<bits/stdc++.h> 
using namespace std;
int t,v[1000001]; //v数组用来复制
int a[1000001];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int n,x,flag=0;//flag判断是否可以结束
		long long ans=0;//记得开long long
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			v[i]=a[i];ans+=a[i];//复制，并把原数组的值提前加到答案中
		}
		while(!flag)
		{
			for(int i=1;i<=n;i++)
			{
				if(v[i]%x!=0)//可以退出
				{
					flag=1;
					break;//退出循环，后面的不能再计算了
				}
				ans+=a[i];//加上原数组，即x个新数的总值
			    v[i]/=x;//分裂操作，按题意模拟
			}
		}
		printf("%lld\n",ans);//输出，注意long long是lld
	}
    return 0;
}

```

---

