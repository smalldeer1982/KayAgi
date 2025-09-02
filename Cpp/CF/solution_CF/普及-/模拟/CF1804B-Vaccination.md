# Vaccination

## 题目描述

#### 题目大意

Ethan 经营一个疫苗接种站，帮助人们抵御季节性流感。他分析历史数据，以便开发出最佳的疫苗使用策略。

假设有 $n$ 个病人在特定的一天来到诊所，第 $i$ 个病人在时刻 $t_i$ 来。我们知道这些病人中的每一个都可以被要求等待不超过 $w$ 个时间点。这意味着第 $i$ 个病人可以在时刻 $t_i,t_i+1,…,t_i+w$ 接种疫苗。

疫苗以包装形式出现，每个包装包含 $k$ 剂量。每个病人需要恰好一剂量。包装是存放在一个特殊冰箱里的。如果一个包装被取出并打开，它便不能再放回去。疫苗在冰箱外的寿命为 $d$ 个时间点。因此，如果此包装是在时刻 $x$ 被取出且打开，其剂量可用于在时刻 $x,x+1,…,x+d$ 接种疫苗。在时刻 $x+d+1$，这个包装剩余的未使用剂量全部被扔掉。

假设接种站有足够的工作人员在任意时刻进行任意数量的操作。那么接种所有 $n$ 个病人所需的最少疫苗包装数是多少？

## 样例 #1

### 输入

```
5
6 3 5 3
1 2 3 10 11 18
6 4 0 0
3 3 3 3 3 4
9 10 2 2
0 1 2 3 4 5 6 7 8
3 10 3 6
10 20 30
5 5 4 4
0 2 4 6 8```

### 输出

```
2
3
2
3
1```

# 题解

## 作者：lichenzhen (赞：3)

## 题目大意
有 $n$ 个人来医院接种疫苗，给出每个人到来的时间 $t_i$ 每个人最多等待 $w$ 个时间点，有若干包疫苗在冰箱里，每包疫苗有 $k$ 剂量，其中每人恰好需要 $1$ 剂量。每包疫苗在冰箱外最多存放 $d$ 个时间点。接种所有 $n$ 个人所需的最少疫苗包装数是多少。

## 题目解法
读懂题目，理解题意，主要处理的就是在什么情况下需要从冰箱里拿出新的 $1$ 包疫苗。

认真思考一下，主要有以下两种情况需要冰箱里拿出新的 $1$ 包疫苗：

- 当前这包疫苗已经用完了；
- 当前这包疫苗从冰箱里拿出来的时间超过了 $d$ 个时间点，要将剩余的全都扔掉。

我们把当前这包疫苗第一个使用的人的编号存到一个名为 $f$ 的变量里，如果此时这个人的到来的时间减去第 $f$ 个人到来的时间大于了疫苗在冰箱外的最大时间加上每人的最大等待时间，这包疫苗就会失效，从当前人开始往后的人就需要使用新的疫苗。

如果当前人减去 $f$ 大于等于一包疫苗的剂量 $k$，就说明当前这包疫苗用完了，就需要重新开一包新的疫苗。

这样就能解决这个问题了，加上一些小细节的处理就可以 AC 了。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,d,w,t[1000001];
void solve(){
	cin>>n>>k>>d>>w;
	for(int i=1;i<=n;i++) cin>>t[i];
	int ans=1,first=1;
	for(int i=1;i<=n;i++){
		if(t[i]-t[first]>d+w){//情况2
			ans++;
			first=i;
		}
		if(i-first>=k){//情况1
			ans++;
			first=i;
		}
	}
	cout<<ans<<endl;
} 
int main()
{
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0; 
}
```

---

## 作者：York佑佑 (赞：1)

## 题意
有 $n$ 个病人来到诊所，第 $i$ 个病人在时刻 $t_i$ 来。第 $i$ 个病人可以在时刻 $t_i,t_i+1,…,t_i+w$ 接种疫苗。

每个包装包含 $k$ 剂量。疫苗活性为 $d$ 个时间点。这个包装剩余的未使用剂量全部被扔掉。求接种所有 $n$ 个病人所需的最少疫苗包装数是多少。
## 分析
本题暴力枚举即可。

我们计算每一个时间点，记录疫苗的个数和上一个时间点。疫苗在以下两种情况需要增加：
- 来的人数超过剩余的疫苗数量
```cpp
j-num+1>k 
//j:遍历每个时间点，num：当前时间点
```
- 疫苗取出时间超过 $d+w$ 个时间点，导致失去活性
```cpp
t[j]-t[num]>d+w
```
如果满足两种条件中的一种，则**增加疫苗包数**和**更新时间点**。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t[200010],T,n,k,d,w;
int main()
{    
    cin>>T;
    while(T--)
	{
    	cin>>n>>k>>d>>w;
    	int ans=1,num=0;//别忘了初始化 
    	for(int j=0;j<n;j++)
		{
    		cin>>t[j];
			if(j-num+1>k||//来的人数超过剩余的疫苗数量
			t[j]-t[num]>d+w)//疫苗失去活性 
				ans++,num=j;//增加疫苗包数、更新时间点。
		}
		cout<<ans<<endl;
	}
	return 0;
}
```





---

## 作者：Peaceful_Evening (赞：1)

## 题目大意：
有 $n$ 个人前来医院接种疫苗，每个人接种 $1$ 剂疫苗，可以在 $w$ 个时间点内接种疫苗，一包疫苗中有 $k$ 剂疫苗，若取出疫苗，每剂疫苗活性为 $d$ 个时间点，超过时间则疫苗报废。问需要多少包疫苗。

## 思路分析：
两种情况下需要增加一包疫苗：

第一种情况，来的人数超过一包疫苗中剩余疫苗数量。

第二种情况，疫苗取出时间超过 $d+w$ 个时间点。

## 满分代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200002];
int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
    	int n,k,d,w;
    	cin>>n>>k>>d>>w;
    	long long sum=1,num=0;//sum代表疫苗要用多少包，num用来更新时间。
    	for(int j=0;j<n;j++){
    		cin>>a[j];
			if(j-num+1>k||a[j]-a[num]>d+w){//判断疫苗是否不足或者失去活性
				sum++,num=j;
			}
		}
		cout<<sum<<'\n';
	}
	return 0;
}
```


---

## 作者：szh_AK_all (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1804B)

## 题意加分析
一共有 $n$ 个病人来看病，每个病人都需要 $1$ 剂量。但每个包装的剂量是有限的，所以要用到多个包装。要求出最少需要多少包装（每个包装的剂量为 $k$）。

既然是“最少”，那么我们要让每个包装尽量用完。也就是，如果第 $i$ 个包装还可以用，就不要用第 $i+1$ 个包装。那什么情况下不可以用呢？一、当已用时间超出了药的寿命加上病人最大的等待时间时，这箱药便不能再用了；二、如果这箱药用完了，也只能用另一箱了。

我们用变量 $zh$ 来记录药的箱数，用 $f$ 来记录第一个使用第 $zh$ 箱药的病人。如果这箱药还可以用，那么让下一个病人进来，否则，更新 $zh$，将 $f$ 改为这位病人的号码（第 $n$ 为病人的号码为 $n$）。最后输出 $zh$ 即可。

## Code
```c
#include<iostream>
using namespace std;
int a[200005];
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,k,d,w;
        cin>>n>>k>>d>>w;
        int zh=1,f=1;
        for(int j=1;j<=n;j++)
        {
            cin>>a[j];
            if((j-f>=k)||((a[j]-a[f])>d+w))
            zh++,f=j;
        }
        cout<<zh<<endl;
    }
    return 0;
}
```


---

## 作者：FSHYLHX (赞：0)

# 题目大意
有 $n$ 个患者要接种疫苗，每个患者最多能等 $w$ 分钟，每包疫苗有 $k$ 个针头，如果拆封，则每个针头的活性为 $d$ 分钟。若不考虑其他因素，问最少要拆封几包疫苗。
# 思路分析
枚举每个人来的时间，并且记录要拆封的这一包疫苗第一个人使用的时间，分类两种情况：如果当前的人到来的时间大于等待的时长和疫苗的活性时长的和，则需要重新拆封一袋疫苗；如果使用的人数大于每袋疫苗的针头数，则也需要重新拆封一袋疫苗，最终输出即可。
# 代码实现
```
#include<bits/stdc++.h>
using namespace std;
int i,j,k,m,n,ans,sum,t,d,w;
int a[200005]; 
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&n,&k,&d,&w);
		for(int i=1; i<=n; i++) scanf("%d",&a[i]);
		ans = 0, sum = 1;
		for(int i=1; i<=n; i++){
			if(a[i] - a[sum] > d + w || i - sum + 1 > k){
				ans++;
				sum = i;
			}
		}
		printf("%d\n", ans+1);
	}
	return 0; 
}
```


---

## 作者：Loser_Syx (赞：0)

## 思路

对于每组数据，肯定至少要使用一袋的疫苗，接下来我们遍历一下数组，由于一袋疫苗的活性是 $d$ 个时间单位的，而且每个人都可以等候 $w$ 个时间单位，那么当第一个开始那袋疫苗的那个人到现在那个人的到来的时间的差 $> w + d$ 时，或者一开始的那个人和现在的人中间隔的人相隔超过 $k$ 人，就得开一袋新的疫苗，更新一开始的人的坐标。

~~多测别忘换行。~~

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define int long long
const int infty = 1e9;
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
#define debug puts("QAQ")
inline int read(){
	register int x = 0, s = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') s = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x * s;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9) write(x / 10);
	putchar((x % 10) + '0');
}
int a[1919810];
signed main(){
	int T = read();
	while(T--){
		int n = read(), k = read(), d = read(), w = read();
		f(i, 1, n, 1){
			a[i] = read();
		}
		int sum = 1, last = 1;
		f(i, 1, n, 1){
		    bool flag = 1;
		    while(i <= n && a[i] - a[last] <= w + d && i - last + 1 <= k){
		        if(i == n){
		            flag = 0;
		        }
		        i++;
		    }
		    if(flag){
		        sum++;
			    last = i;
		    }
		}
		write(sum);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：mark0575 (赞：0)

## 题目大意：

伊森经营着一家疫苗店。在这一天来了 $N$ 个患者。每个患者最多等待 $W$ 分钟。一袋疫苗有 $K$ 包小疫苗，每个患者只需要一包小疫苗。每包疫苗有 $D$ 分钟的活性，超过 $D$ 分钟一整袋疫苗都没用了。现在问我们一共需要多少包疫苗？

## 解题思路：

我们可以设一个变量 $la$，用来表示这一包疫苗第一个使用的人的编号。接下来从 $la+1$ 开始，一个一个往下枚举，直到两人相差的时间大于每人的等待时间加上一包疫苗的活性时间（也就是 $D+W$），给总结果加上 $1$，并更新 $la$。

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+100;
int t;
int a[N];
int main()
{
	cin>>t;
	while(t--)
	{
		int n,k,d,w;
		cin>>n>>k>>d>>w;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		int ans=1;//至少用一包
		int la=1;//这包第一个使用的人
		for(int i=1;i<=n;i++)
		{
			if(a[i]-a[la]>d+w||i-la+1>k)//判断一袋疫苗够不够用
			{
				ans++;//疫苗总数加1
				la=i;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}

```


---

