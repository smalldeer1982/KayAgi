# Chocolate

## 题目描述

## 分割序列

给一个01序列，将之分割成若干段，要求每段恰好只含有1个1，计算分解方案的总数。

## 样例 #1

### 输入

```
3
0 1 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 0 1 0 1
```

### 输出

```
4
```

# 题解

## 作者：hanzif (赞：2)

### 数学题
在每两个1之间都可以插入一个间隔

例如样例：

5

1 0 1 0 1


第一个1在位置1，第二个1在位置3，所以有2种方案，分别是1|01,10|1。同理，第二个1和第三个1也有2种。根据乘法原理，答案为2*2=4。

再例如：

6

1 0 0 1 0 1

第一个1和第二个1间隔为3，因此能插入3种：1|001,10|01,100|1。而第二个1和第三个1有2种，答案为3*2=6。

注意：要开long long

下面贴上代码

```cpp
#include"iostream"
#include"cstdio"
#define f(x,a,b) for(int x=a;x<=b;++x)
using namespace std;
typedef long long ll;
ll t,n,a[105],ans,last;
bool ok;//判断只有0的情况
int main(){
	scanf("%lld",&n);
	last=0;ans=1;//last记录上一个1的位置
	f(i,1,n){
		scanf("%lld",&a[i]);
		if(a[i])ok=1;
		if(a[i]){
			if(last){//如果前面有1
				ans=ans*(i-last);//乘法原理
			} 
			last=i;//记录1的位置
		}
	}
	if(!ok)ans=0;//只有0的情况
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Nosta1enh (赞：1)

要求每一段恰好只有一个 $1$，实际上就是在每相邻两个 $1$ 中任选一个空，从这个空处分割。

每次碰到 $1$ 就统计它与上一个 $1$ 之间有几个间隔（就是在这两个 $1$ 之间分割的方案数），并将结果乘进当前答案中。

结合第二组样例理解：
```
5
1 0 1 0 1
```

第一个 $1$ 与第二个之间有 $2$ 个间隔即 $2$ 种分割方案，第二个与第三个之间同样有 $2$ 种方案，答案即用乘法原理，$2 \times 2 = 4$。


需要注意的是对于全 $0$ 情况的特判。

最后是`AC`代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int one;//记录上一个1出现的位置
bool a[101];//既然只有01，就可以用bool类型存
long long ans=1;//一定注意不能初始化为0
bool all0()//判断是否全0
{
    for(int i=1;i<=n;i++)if(a[i])return 0;
    return 1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(all0())
    {
        cout<<0;
        return 0;
        //如果全0显然一种方案也没有
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]&&one==0)//如果之前没有出现1
        {
            one=i;//标记
            continue;
        }
        if(a[i])
        {
            ans*=(i-one);
            //这一个1和前一个1中间的间隔就是i-one个
            //所以就有i-one种方案
            //乘法原理，乘进ans中
            one=i;//标记
        }
    }
    cout<<ans;
}
```


---

## 作者：HadrianZhang (赞：0)

# 思路

观察样例，很快可以发现：每两个 $1$ 之间，能且仅能切 $1$ 刀，可以切在这两个 $1$ 之间的任意位置。

例：$1$ $0$ $0$ $1$ $0$ $1$

前两个 $1$ 之间可以切 $3$ 刀，后两个 $1$ 之间可以切 $2$ 刀。

根据乘法原理，有 $3 \times 2=6$ 种方案。

因此，每两个 $1$ 之间可以切的刀数之积即为答案。

注意：如果数据中没有 $1$，方案数为 $0$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ans=1;
bool a[105],flag;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(a[i])
		{
			flag=1;
			int pos=i+1;
			for(int j=i+1;j<=n;j++)
				if(a[j])
				{
					pos=j;
					break;
				}
			ans*=pos-i;
		}
	}
	if(!flag) cout<<0;
	else cout<<ans;
	return 0;
}
```

---

## 作者：HIMmeqq (赞：0)

### 1.分析题意

给定一个 $01$ 序列，求将其分割成每段仅包含一个 $1$ 的分割方案总数。

要求每段仅包含一个 $1$，说明在每两个 $1$ 之间必须有且只能有一个分割，那么思路就很明确了。

下面我将配合样例解释思路：

```cpp
5

1 0 1 0 1

1 0|1 0|1

1|0 1 0|1

1 0|1|0 1

1|0 1|0 1
```

不难发现，其实本质上就是一个排列组合的问题：在每两个 $1$ 之间，有几个间隔就是几个方案可以将这两个 $1$ 分割，然后用乘法原理乘起来就行了。

对于上面的情况，就是 $2 \times 2 =4$，所以答案为 $4$。

特别注意：1.特判全部为 $0$ 的情况；2.注意开long long。

### 2.代码
```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while (ch < '0' || ch > '9'){if (ch == '-') f =- 1; ch = getchar();}
	while (ch >= '0' && ch <= '9'){x = x * 10 + ch - 48; ch = getchar();}
	return x * f;
}//函数返回值为读入的第一个整数。


typedef long long ll;
const int maxn = 1e5;

ll a[maxn],tans[maxn],n,ans = 1; 
bool allZero = true;

int main()
{
	n = read();
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
		if(a[i] == 1) allZero = false;
	}
	
	ll index = 0;
	
	for(int i = 1;i <= n;i++)
	{
		if(a[i] == 1 && index == 0)
		{
			index = i;
			continue;
		}
		
		if(a[i] == 1)
		{
			tans[i] = i - index;
			index = i;
		}
	}
	
	for(int i = 1;i <= n;i++)
	{
		if(tans[i])
		{
			ans *= tans[i];
		}
	}
	if(allZero)
	{
		printf("0");
	}else
	{
		printf("%lld",ans);
	}
 	return 0;
}

```

---

## 作者：cdhh (赞：0)

本题的问题是小学的隔板问题，不了解的可以看[这里](http://www.offcn.com/sydw/2020/0121/530402.html)。

假设我们有一个数列 $100100011$，那么肯定只能在两个 $1$ 之间放隔板，隔板该放在哪里呢？让我们来看看。第一个 $1$ 与第二个 $1$ 之间有两个 $0$，有三个位置可放。同理，第二个与第三个之间有 $4$ 个位置可放，最后两个只有 $1$ 处可放。最终的答案就是 $3\times4\times1=12$ 种。

总结一下，我们只需统计相邻两个 $1$ 之间有几个间隔，最终相乘就行。

记得开```long long```，还有可能出现全是 $0$ 的情况。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll n,a[100001],l,f,ans=1; 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]) f++;
		if(a[i]==1){
			if(l) ans*=(i-l);
			l=i;
		}
	}
	if(f>0) cout<<ans;
	else cout<<0;
	return 0;
}

```


---

