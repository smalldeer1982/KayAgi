# Cow and Haybales

## 题目描述

有n个数，你每次可以选择相邻的两个数i和j，使ai-1，aj+1，你的目的是经过d此操作后，使得a1最大。

## 样例 #1

### 输入

```
3
4 5
1 0 3 2
2 2
100 1
1 8
0```

### 输出

```
3
101
0```

# 题解

## 作者：yxy666 (赞：1)

题意：给我们 $n$ 个数，我们每一步可以让 $a[i]+1$,$a[i+1]-1$，问我们操作 $d$ 步后 $a[1]$ 最大是多少。一共有 $T$ 组数据。

我们先来看一下数字
```
10 1 10 10 
```

对于这样一组数字，我们会发现，从 $a[2]$ 移走 $1$ 到 $a[1]$ 只需要$1$步，而从$a[3]$移走 $1$ 到 $a[1]$ 需要$2$步，从 $a[n]$ 移走 $1$ 需要 $n-1$ 步。贪心的想法，我们肯定是离 $a[1]$ 越近，那么就先移它啊。

$code$ :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
int n,d,t,a[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读
int main(){
	t=read();
	while(t--){
		n=read();d=read();
		for(int i=1;i<=n;i++)a[i]=read();
		int j=2;
		while(d>=j-1){//如果距离还够移一个1，那么就继续移
			if(a[j])a[j]--,d-=(j-1),a[1]++;//还没移光，继续移
			else j++;//最左边的取没了，往右移一格
			if(j>n)break; 
		}
		printf("%d\n",a[1]);
	}
	return 0;
}
```


---

## 作者：Reanap (赞：1)

这道题的贪心比较的显然，我们想要把1号草堆的草堆得尽可能的多，那么我们就要把右边的草堆尽可能往左边移。

经观察，我们发现把第$i$个草堆的草移一堆到一号草堆的代价为$i -1$,那么我们发现，无论移哪个位置的草对答案的贡献都是一样的，而移越靠左的草堆花费最小，因此我们尽可能地去移靠左的草堆。模拟一遍即可。

细节见代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 105;
int T , n , d;
int a[MAXN];
int main() {
	scanf("%d" , &T);
	while(T -- > 0) {
		scanf("%d %d" , &n , &d);
		for (int i = 1; i <= n; ++i) {
			scanf("%d" , &a[i]);
		}
		int ans = a[1];
		for (int i = 2; i <= n; ++i) {
			if(a[i] * (i - 1) <= d) {
				d -= a[i] * (i - 1);
				ans += a[i];
			}
			else {
				ans += d / (i - 1);
				break;
			}
		}
		printf("%d\n" , ans);
	}
	return 0;
}

```

---

## 作者：sycqwq (赞：1)

关于这一题...是入门的贪心

既然是贪心，那该怎么贪呢：

观察题目，就是将相邻的两个数一个减1，一个加1，使第一个数最大，那我们就要让离1最近的移到1。

注意：是先把一个数移到第一个数，再移下一个。

代码：
```cpp
#include<bits/stdc++.h>
#define inf 2147283647
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,d,a[105]={0};
        cin>>n>>d;
        for(int j=1;j<=n;j++)
            cin>>a[j];
        int t=2;//t就是现在要移第几个数
        while(d>0&&t<=n)//如果没移完所有得数并且时间没用完就继续移
        {
            if(a[t]>0)//没移完，就继续移
            {
                
                ++a[1];//一个+1，一个-1
                --a[t];
                int m=t-1;//m为要移几天，就等于位置-1
                d-=m;//减去天数
                if(d<0)//特判，d<0的话，就代表移不了，前面移了，所以要-1
                    --a[1];
            }
            else//否则，移下一个
                ++t;
        }
        cout<<a[1]<<endl;
    }
    return 0;
}
```

---

## 作者：1qaz234567pzy (赞：0)

我们稍稍一研究就会发现，把 $a_2$ 的 $1$ 个干草堆移到 $a_1$ 需要 $1$ 次操作，而 $a_3$ 的 $1$ 个干草堆移到 $a_1$ 需要 $2$ 次操作，为了尽可能多的移到 $a_1$ 去，我们优先让离 $a_1$ 近的移动到 $a_1$ 就可以了。


代码如下：

```cpp
#include<bits/stdc++.h>
using  namespace std;
short t;
short n,d;
short aa[105];
int main()
{
    cin>>t;
    for(int qq=1;qq<=t;qq++)
    {
        cin>>n>>d;
        for(int qqq=1;qqq<=n;qqq++)
        {
            cin>>aa[qqq];
        }
        for(int ww=2;ww<=n;ww++)//移动干草堆
        {
            if(d<ww-1)//没有足够的操作次数了
            {
                break;
            }
            else if(d>=aa[ww]*(ww-1))
            {
                aa[1]+=aa[ww];
                d-=aa[ww]*(ww-1);
            }
            else
            {
                while(d>=(ww-1))
                {
                    aa[1]++;
                    d-=(ww-1);
                }
                
            }
        }
        cout<<aa[1]<<endl;
    }


    return 0;
}
```


---

## 作者：asas111 (赞：0)

## 思路
这题需要用到贪心，数据范围较小，直接模拟就行了

具体思路：每次找到离 $a_{1}$ 最近的草堆，把它移到 $a_{1}$。

证明：如果不选最近的草堆，选其他距离更远的草堆只会使 $a_{1}$ 的草堆数量更少，而不会增多。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int n,d,a[109]={},k=2;
		cin>>n>>d;
		for(int i=1;i<=n;i++)cin>>a[i];
		while(d>=k-1){
			if(a[k]>0)a[1]++,a[k]--,d-=k-1;//模拟移动草堆
			else k++;
			if(k>n)break;//防止越界
		}
		cout<<a[1]<<" ";
	}
	return 0;
}
```


---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，把越靠左的草堆移动到 $1$ 号草堆的步数越少。所以为了使 $1$ 号草堆最大，我们应该尽量移动靠左的草堆。所以，可以遍历 $d$ 次，如果草堆不为 $0$，就向左移动一个。如果遍历完一次但没有可移动的，就提前结束遍历。
## 代码
```python
a=int(input())
for b in range(a):
    c,d=map(int,input().split())
    e=list(map(int,input().split()))
    for f in range(d):
        h=0
        for g in range(1,c):
            if e[g]>0:
                e[g-1]+=1
                e[g]-=1
                h=1
                break
        if h==0:
            break
    print(e[0])
```
还没有 python 题解，希望管理员通过！

---

## 作者：fangyicheng1216 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1307A)

# 思路

这道题要用到贪心。

具体贪心思想就是：假设有一个 $a_i$，那么它距离 $a_1$ 越近，它把它自己所有的数运送过去要花费的次数就越少，所以我们优先选择离 $a_1$ 近的。

第 $a_i$ 个数要运送一个 $1$ 去到 $a_1$ 需要花费次数是 $i-1$ 次。

所以我们可以从 $a_2$ 开始枚举，直到把 $d$ 用完，或者枚举到 $n$ 就可以结束了，最后直接输出在枚举过程中算得的 $ans$。

这道题的题目翻译有一个点没有说清楚，就是 $a_i-1$ 这个操作的实现当且仅当 $a_i \gt 0$。

# 代码（有亿些无用部分，请自行忽略）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){//快读 
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        f=ch!='-';
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return f?x:-x;
}
inline void write(int x){//快写 
    if(x>=10) write(x/10);
    putchar(x%10+48);
}
inline int quickPower(int a,int b){//忽略它 
	int ans=1,base=a;
	while(b>0){
		if(b&1)
			ans*=base;
        base*=base;
		b>>=1;
	}
	return ans;
}
int n,m,dp[10005];
inline void ZeroOnePack(int c,int w){//忽略它 
	for(int j=m;j>=w;j--){
		dp[j]=max(dp[j],dp[j-w]+c);
	}
}
inline void CompletePack(int c,int w){//忽略它 
	for(int j=w;j<=m;j++){
		dp[j]=max(dp[j],dp[j-w]+c);
	}
}
inline void MultiplePack(int c,int w,int p){//忽略它 
	if(p*w>=m){
		CompletePack(c,w);
		return ;
	}
	int k=1;
	while(k<p){
		ZeroOnePack(k*c,k*w);
		p-=k;
		k*=2;
	}
	ZeroOnePack(c*p,w*p);
}
int a[105],T,d;
signed main(){
	T=read();
	while(T--){//枚举T组数据 
		int ans=0;
		n=read(),d=read();
		for(int i=1;i<=n;i++) a[i]=read();
		//普通的输入 
		ans=a[1];//ans一定要赋值a[1] 
		int i=2;
		while(d>0&&i<=n){//开始枚举 
			if(a[i]*(i-1)>d){//当时间不够运完时 
				ans+=d/(i-1);
				d=0;
			}
			else{//当时间够运完时 
				d-=a[i]*(i-1);
				ans+=a[i];
			}
			i++;//i一定要+1 
		}
		write(ans);
		puts("");//输出并换行 
	}
	return 0;
}
```


---

## 作者：Fislett (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1307A)

这题的主要思路其实就是[贪心] 。(https://baike.baidu.com/item/%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95/5411800)

由于移动的次数限制，所以根据贪心的算法，我们发现，无论是哪个数，能给    $a[1]$ 做的贡献都是一样的，但花费不一样，肯定是离 $a[1]$ 越近，效率越高啊！所以我们写代码时尽量先从左往右向 $a[1]$ 移。

最后，通过模拟，就可找出答案。

# 代码：
```c
#include <bits/stdc++.h>
using namespace std;
int t; //t表示组数
int main()
{
	cin >> t;
	while (t --)
	{
		int ans, n, d, a[101]; //ans记录答案, n是个数，d是次数 
		cin >> n >> d;
		cin >> a[1];
		ans = a[1]; //初始化答案
		for (int i = 2; i <= n; i ++) //切记，从2开始！！！
			cin >> a[i]; //输入 
		for (int i = 2; i <= n; i ++) //i表示当前移动到的位置
		{
			if (d < i - 1) break; //如果一个都换不了，直接break 
			if (d >= a[i] * (i - 1)) ans += a[i], d -= a[i] * (i - 1); //更新答案
			else ans += d / (i - 1), d -= d / (i - 1) * (i - 1); //同样的更新 
		}
		cout << ans << endl; //输出 
	}
	return 0; //打完收工，回家 
} 
```
这是本蒟蒻的第一篇题解，请大家多多关照。

---

## 作者：zbk233 (赞：0)

首先，想要让 $a_1$ 加一，那么就需要让 $a_2,a_3,a_4,...,a_n$ 中的其中一个大于零的数减一。

证明：假设要让 $a_1$ 加一，$a_x$ 减一。

那么我们的操作应该是 $a_1$ 加一，$a_2$ 减一，$a_2$ 加一，$a_3$ 减一，···，$a_{x-1}$ 加一，$a_x$ 减一。

化简一下就得 $a_1$ 加一，$a_x$ 减一。

要使经过 $d$ 次操作后 $a_1$ 最大，就要用到贪心的思想。要尽量挑选与 $a_1$ 位置接近的使操作次数最少，那么就应挑选 $a_2,a_3,a_4,...,a_n$ 中的第一个大于零的数。

```cpp
#include <iostream>
using namespace std;
int a[105];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t, n, d;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		cin >> n >> d;
		for (int j = 1; j <= n; j++)
		{
			cin >> a[j];
		}
		for (int j = 2; j <= n; j++)
		{
			while (d >= (j - 1) && a[j]--)
			{
				d -= (j - 1);
				a[1]++;
			}
			if (d <= 0)
			{
				break;
			}
		}
		cout << a[1] << '\n';
	}
	return 0;
}
```


---

## 作者：YYen (赞：0)

### 思路：贪心
目标是在有限次操作内，把 $ a_{2} $ ， $ a_{3} $ ， ...  ， $ a_{n} $ 的数搬运到 $ a_{1} $ ，尽量使 $ a_{1} $ 尽可能大。

易知， $ a_{2} $ 搬运到 $ a_{1} $ 每次成本是 $ 1 $ ， $ a_{3} $ 搬运到 $ a_{1} $ 每次成本是 $ 2 $ ， $ a_{4} $ 搬运到 $ a_{1} $ 每次成本是 $ 3 $ ，如此类推。所以妥妥是一个贪心，为了让 $ a_{1} $ 尽可能大，必定是**优先搬运成本更小的**。

### 代码
数据很弱，代码暴力模拟就可以，略。

---

## 作者：流绪 (赞：0)

### 贪心+模拟！

已知一个序列，对于序列中每个大于 0 的值，你可以让他 -1，然后让他相邻大的一个数 +1，这样做消耗 1 的时间，求在 d 时间内，序列的第一个数最大能是多少？

我们可以发现如果 ai>0，那么它可以花 i-1 的时间，使 a1+1。所以我们可以贪心的从花费时间少的地方开始，也就是从 a2 开始，在 d>=i-1 时,让 a1+1,ai-1，直到 d<i-1 结束。

下面是 AC 代码,细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
int a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--)
	{
		int n,d;
		cin >> n >> d;
		for(int i=1;i<=n;i++)
			cin >> a[i];
		int sum = a[1];
		for(int i=2;d>0&&i<=n;i++)
		{
			int flag = 0;
			while(a[i]>=1&&d>=i-1&&i<=n)//若d够用且情况合法
			{
				sum++;第一个位置变大
				d-=i-1;消耗时间
				a[i]--;ai减小
		//		cout << i << " " <<sum<<endl ;
			}
		} 
		cout << sum << endl;
	 } 
	return 0; 
}  
```


---

