# Koala and Lights

## 题目描述

有 $n$ 盏灯泡，给定初始状态，第 $i$ 盏灯泡会在 $b_i,b_i+a_i,b_i+2 \times a_i$ 等时刻变成相反的状态，求在某一个时刻亮灯数的最大值。

## 样例 #1

### 输入

```
3
101
3 3
3 2
3 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1111
3 4
5 2
3 1
3 2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
6
011100
5 3
5 5
2 4
3 5
4 2
1 5
```

### 输出

```
6
```

# 题解

## 作者：wmrqwq (赞：3)

# 原题链接

[CF1209B Koala and Lights](https://www.luogu.com.cn/problem/CF1209B)

# 题目简述

现在有 $n$ 盏灯，每盏灯会分别在 $b_i$，$a_i+b_i$，$a_i \times 2 + b_i$ 等时刻变成与现在相反的状态（开灯变为关灯，关灯变为开灯），现在需要求出在某一时刻亮灯数的最大值。

# 解题思路

因为 $0 \le a_i$，$b_i \le 5$，所以这道题可以不用计算周期，只需要根据题意模拟，根据题意不难得出：如果这个时刻要比 $b_i$ 大并且这个时刻减去 $b_i$ 能是 $a_i$ 的倍数，那么就改变这个灯的状态，最后统计亮着的灯的数量的最大值即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0;
long long n,a[100010],b[100010],c[100010],sum[100010],maxn;
string s;
int main()
{
	cin>>n>>s;//输入灯的数量和每盏灯的状态
	for(int i=1;i<=n;i++)
		if(s[i-1]=='1')
			c[i]=1;//将灯的状态由字符转化为数字
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++)//枚举n盏灯
		for(int j=0;j<=100000;j++)//枚举到1e6
		{
			if(j>=b[i] && (j-b[i])%a[i]==0)
				c[i]=!c[i];	//将灯转化为与现在相反的状态
			sum[j]+=c[i];//如果灯亮了，那么就将sum[j]加上1
		}
	for(int i=0;i<=100000;++i)//枚举到1e6
		maxn=max(maxn,sum[i]);//取最大值
	cout<<maxn;//输出最大值
	QwQ;//华丽的结束
}
```

---

## 作者：wsk_1202 (赞：3)

题意：$n$ 盏灯，第 $i$ 盏灯会在 $b_{i},b_{i}+a_{i},b_{i}+2* a_{i}$ 等时刻转换状态（开变关，关变开）。求一个时刻最多会有多少盏灯亮着。

比赛时看到这个题，马上想到直接模拟。数据还是比较水的，所以我也没有计算周期，直接枚举到某个比较大的时刻，暴力计算，取 $max$ .

看来还是可以过的...

代码

```cpp
#include <cstdio>
using namespace std;
inline int max(int x,int y){return x>y?x:y;}
int n,a[102],b[102],vis[102],tm[102],ans,maxn;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%1d",&vis[i]),maxn+=vis[i];//先计算初始状态亮着的灯。  （关于输入可以使用scanf的格式化输入）
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	for(int k=0;k<=1000000;k++)//枚举时刻，1e6足矣
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			if(k>=b[i]&&(k-b[i])%a[i]==0)vis[i]^=1;//如果满足条件，改变状态
			ans+=vis[i];
		}
		maxn=max(maxn,ans);//取max
	}
	printf("%d\n",maxn);//输出
	return 0;
}
```

---

## 作者：York佑佑 (赞：1)

## 题意

有 $n$ 盏灯泡，给定初始状态，第 $i$ 盏灯泡会在 $b_i,b_i+a_i,b_i+2 \times a_i$ 等时刻变成相反的状态，求在某一个时刻亮灯数的最大值。
## 分析
每盏灯开关的状态周期不等，故不能用周期问题来解决本题。那本题的算法很明显就是**模拟**了。我们将每一时刻的亮灯数求出，其中涉及到一盏灯是否要变成相反的状态。

一盏灯变成相反的状态需要满足 $2$ 种条件：
- 这个时刻比 $b_i$ 大（否则该灯的周期未开始，故不变）。
- 这个时刻减去 $b_i$ 是 $a_i$ 的倍数（否则没轮到这一周期，故不变）。

若上述条件都满足，就改变该灯的状态。模拟完之后，求出所有时刻亮灯的最大值即可 AC。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,a[N],b[N],light[N],ans[N],maxx;
string str;
int main()
{
	cin>>n>>str;
	for(int i=0;i<n;i++)
		light[i+1]=str[i]-'0';//字符转数字，不解释 
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++)
		for(int j=0;j<=100010;j++)
		{
			if(j>=b[i]&&!(j-b[i])%a[i])//如果这个时刻比b[i]大并且这个时刻减去b[i]是a[i]的倍数
				light[i]=!light[i];	//通过逻辑非将灯的状态改变 
			ans[j]+=light[i];//答案计数，将这一时刻开着的灯记录 
		}
	for(int i=0;i<=100010;i++)
		maxx=max(maxx,ans[i])//计算最大值 
	cout<<maxx;
	return 0;
}
```


---

## 作者：sz_wsy (赞：1)


#### [CF1209B 题目传送门](https://www.luogu.com.cn/problem/CF1209B)

### 题目大意
- 有 $n$ 盏灯和每盏灯的初始状态（亮或不亮），第 $i$ 盏灯会在 $b_i+k\times a_i(0\le k)$ 时刻变成**相反的状态**，求某一个时刻亮灯数的最大值。
- 数据范围：$1\le n \le 100$，$1\le a_i,b_i \le 5$。

### 算法分析
可以发现，题目中所有灯中**每时刻亮的数量**是有规律可循的~~当然没必要找规律~~。因为数据范围不大，故此可以用暴力枚举，即枚举 $0\sim 10^5+7$ 就差不多了。

我们用 $s_i$ 表示这盏灯的状态（亮或不亮），$t_i$ 表示  $i$ 时刻共有几盏灯亮着。最后取 $t$ 数组的最大值。详细解释见代码。
### 代码呈现
```cpp
#include <iostream>
using namespace std;

int n;
int s[114],a,b;
int t[100007];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%1d",&s[i]); //读入技巧：s[i]只接受1个单位长度的内容，本题中即0或1 
	}
	for(int i=1;i<=n;i++){
		scanf("%d %d",&a,&b);
		for(int j=0;j<100007;j++){
			if(j>=b && (j-b)%a==0){ //j>=b 是为防止负数取模出BUG 
				s[i]=1-s[i]; //该时刻第i盏灯状态取反
			}
			t[j]+=s[i];  //等价于 t[j]+=(s[i]==1 ? 1:0);
		}
	}
	int ans=-1;	
	for(int i=0;i<100007;i++){
		ans=max(ans,t[i]);	   //取某一时刻亮的数量的最大值 
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：HEzzz (赞：0)

[题目跳转键](https://www.luogu.com.cn/problem/CF1209B)

这道题非常简单，首先呢我们知道每一盏灯泡的开灯周期都不一样，因此这道题不能用周期来解决，一般我们在解决周期问题时如果发生这种情况我们可以采取**模拟**这个算法来解决问题。

知道是**模拟**后，我们还要知道每一盏灯的周期规律，即 $y_i+x_i \times q$，注意这里的 $q$ 是自然数。知道这些，代码也非常简单。

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl;
int n,x[110],y[110],cnt[100010],ans;//cnt[i]表示第i时间这一刻有多少盏灯泡亮着的
char c[110];
int main() 
{
	cin>>n>>(c+1);
	_rep(i,1,n) cin>>x[i]>>y[i];
	_rep(i,1,n)
	{
		_rep(j,0,100000)//枚举时间
		{
			if(j>=y[i]&&(j-y[i])%x[i]==0) //如果j这个时间满足等于 y[i]+x[i]*q 的则要把这盏灯泡变成相反的状态
  				c[i]=(c[i]=='0'?'1':'0');//变成相反的状态
			if(c[i]=='1') cnt[j]++;//更新
		}
	}
	_rep(i,0,100000) ans=max(ans,cnt[i]);//求最多同时亮起灯泡的数量
	cout<<ans;
	return 0;
}
```


---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1209B)

这道题让我们计算出某一时刻灯亮的最大数目。

那我们可以直接枚举每一时刻，看看在这一时刻有多少灯亮着。

但是我们不用太在意循环的次数，多枚举几次就行了，但是为了防止超时，我们还是算一下时间复杂度。

现在我们来计算一下时间复杂度：

首先，每次循环时间我们假定他的时间复杂度为 $O(K)$，$K$ 为一个常数。

然后我们每次检测 $n$ 个灯是否亮着就是 $O(n)$ 级别的复杂度。

综合起来，我们的时间复杂度就是 $O(Kn)$，那我们知道 $1s$ 大概能评测 $1\times 10^8$ 的数据。所以我们就大概估计出来了 $K$ 的取值范围。

经过一些简单的解法后，我们求出来 $K$ 的最大值应当是 $1\times10^6$（这里我开的 $2\times 10^6$ 竟然没有超时）。

你还可以优化一下，就是如果现在最大值是 $n$（即 $n$ 个灯全部亮着），我们直接退出就可以了，因为肯定无法比这个数值再大了。

还有一点就是取反了，这里我推荐使用 ``!`` 来取反，这样就不用写 ``if`` 了。

最后就是 ``scanf`` 输入的问题了，读入 ``%c`` 需要在前面上空格。

---

# AC代码

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int n,a[1005],b[1005];
int light[1005];
char x;
int ans; 
int tot(){
	int total=0;
	for(int i=1;i<=n;i++)if(light[i])total++;
	return total;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf(" %c",&x);
		light[i]=bool(x-'0');
	}
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	for(int i=0;i<=200000;i++){
		for(int j=1;j<=n;j++){
			if(i>=b[j]&&(i-b[j])%a[j]==0){//这里的判断需要注意一下。
				light[j]=!light[j];
			}
		}
		ans=max(ans,tot());
		if(ans==n)break;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：BlackPanda (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF1209B)**

------------
### 题意：
有 $n$ 盏灯泡，给定初始状态，第 $i$ 盏灯泡会在 $b_i, b_i+a_i, b_i+2 \times a_i$ 等时刻变成相反的状态，求在某一个时刻亮灯数的最大值。

------------
### 思路：
模拟题，数据规模较小，直接暴力枚举即可。

可以枚举每盏灯在 $10^5$ 时刻之前的所有状态，如果循环变量比 $b_i$ 大并且循环变量减去 $b_i$ 能被 $a_i$ 整除（是 $a_i$ 的倍数），就改变此盏灯的状态，最后统计亮灯数的最大值即可。

------------
### code：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5;

int n;
int v[105];
int a[105],b[105]; 
int sum[maxn+5],ans;

int main(){
	cin >> n;
	for(int i=1;i<=n;i++)scanf("%1d",&v[i]);	//读入技巧
	for(int i=1;i<=n;i++){
		cin >> a[i] >> b[i];
		for(int j=0;j<=maxn;j++){
			if(j>=b[i] && (j-b[i])%a[i] == 0){
				v[i]^=1;
			}	
			sum[j]+=v[i];
		}
	}
	for(int i=0;i<=maxn;++i){
		ans=max(ans,sum[i]);
	}
	cout << ans;
	return 0;
}


```

---

