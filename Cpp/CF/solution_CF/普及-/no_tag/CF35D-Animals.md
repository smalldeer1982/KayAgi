# Animals

## 题目描述

Once upon a time DravDe, an outstanding person famous for his professional achievements (as you must remember, he works in a warehouse storing Ogudar-Olok, a magical but non-alcoholic drink) came home after a hard day. That day he had to drink 9875 boxes of the drink and, having come home, he went to bed at once.

DravDe dreamt about managing a successful farm. He dreamt that every day one animal came to him and asked him to let it settle there. However, DravDe, being unimaginably kind, could send the animal away and it went, rejected. There were exactly $ n $ days in DravDe’s dream and the animal that came on the $ i $ -th day, ate exactly $ c_{i} $ tons of food daily starting from day $ i $ . But if one day the animal could not get the food it needed, it got really sad. At the very beginning of the dream there were exactly $ X $ tons of food on the farm.

DravDe woke up terrified...

When he retold the dream to you, he couldn’t remember how many animals were on the farm by the end of the $ n $ -th day any more, but he did remember that nobody got sad (as it was a happy farm) and that there was the maximum possible amount of the animals. That’s the number he wants you to find out.

It should be noticed that the animals arrived in the morning and DravDe only started to feed them in the afternoon, so that if an animal willing to join them is rejected, it can’t eat any farm food. But if the animal does join the farm, it eats daily from that day to the $ n $ -th.

## 说明/提示

Note to the first example: DravDe leaves the second and the third animal on the farm. The second animal will eat one ton of food on the second day and one ton on the third day. The third animal will eat one ton of food on the third day.

## 样例 #1

### 输入

```
3 4
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 6
1 1 1
```

### 输出

```
3
```

# 题解

## 作者：WCG2025 (赞：4)

赶来为CF~~水题~~写题解了


------------

这个翻译是真正的有问题，这道题的意思是：

有某类动物，可以在农场中待n天，如果它是第i天来的话，从第i天到第n天每天要吃的食物为a[i]，这些动物可以中途来，不可以中途走，问最多能容纳多少只动物

其实这道题分析好后，有两种做法

动态规划：

先预处理出动物如果第i天来，那么这只动物一共要吃的粮食的总数。

设dp[x]为剩余粮食为x时所能容纳的最大动物数（就是一个01背包）
可推出方程式dp[x]=max(dp[x],dp[x-ani[i]]+1)
```cpp
#include<iostream>
#include<cstdio>
#include<fstream>
using namespace std;

int ani[1005];
int dp[100005];
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,x;
    cin>>n>>x;
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&ani[i]);
        ani[i]*=(n-i+1);
    }
    for(int i=1;i<=n;i++)
    for(int j=x;j>=ani[i];j--)//01背包倒着写，完全背包顺着写
    dp[j]=max(dp[j],dp[j-ani[i]]+1);
    cout<<dp[x]<<endl;
    return 0;
}
```
贪心：
预处理也是相同的，只是添加一个sort排序，从小的开始选，累加就行了
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int n;
int k;
int a[1000000];
int cnt=1;
int ans;
int main()
{
    freopen("input.txt","r",stdin);
  	freopen("output.txt","w",stdout);
    n=read();
    k=read();	
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        a[i]=a[i]*(n-i+1);//n-i+1是剩余天数，处理后的a[i]
    }//即为第i天来的动物所需要的粮食
    sort(a+1,a+n+1);
    while(k-a[cnt]>=0&&cnt<=n)//从小的开始选
    {
        ans++;
        k-=a[cnt++];
    }
    printf("%d",ans);
    return 0;
} 
```
PS：加了文件输入输出操作是因为CF这道题的要求，不是故意坑你们

---

## 作者：BigJoker (赞：3)

# 0x00 分析

我们首先来分析一下此题，这道题可以用贪心也可以用背包做。但是不管用哪一种做法，都需要分析出每一件物品的成本，不难算出第 $i$ 件物品的成本就是 $(n-i+1)×c_i$，然后价值不需要多说，就是 $1$，然后贪心或者背包即可，当然在这里，贪心明显要简单的多。

# 0x01 贪心

因为成本都是一样的，所以我们可以使用贪心来解决。首先按照我们所定义的成本进行从小到大的排序，接着我们使用一层循环，来枚举每件物品，只要我们还放得下，那么就放进去，如果放不下了，那肯定后面的也放不下，所以输出答案即可。

# 0x02 代码

```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dep(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
const int N=1e2+5;
int n,x,ans,c[N];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&x);
	rep(i,1,n){
		scanf("%d",&c[i]);
		c[i]=c[i]*(n-i+1);
	}
	sort(c+1,c+1+n);
	rep(i,1,n)
		if(x>=c[i]) ans++,x-=c[i];
		else break;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：_StarBird_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF35D)

[在博客中食用更佳](https://www.luogu.com.cn/blog/jch2008/solution-cf35d)

------------

**关于翻译**

这题翻译就离谱，真正题意是你有一个容量为 $X$ 的背包和 $n$ 个物品，在第 $i$ 每个物品的体积为 $c_i\times(n-i+1)$，问你最多能装几个物品，翻译实在是过于生草

**做法**

转化成背包后，因为每个物品的收益一样（都为1），所以显然每次贪心选择成本最低的物品。算出成本后排序即可。

切 水 题 の 快 乐
```cpp
#include<bits/stdc++.h>
#define MAXN 110
using namespace std;
int n,x,c[MAXN];
int main()
{
	freopen("input.txt","r",stdin); //非反作弊 CF里这道题要求加这玩意 不加会炸 
	freopen("output.txt","w",stdout);
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;++i) scanf("%d",&c[i]),c[i]*=(n-i+1); //体积 
	sort(c+1,c+n+1); //从小到大排序 
	int ans=0; 
	for(int i=1;i<=n;++i)
		if (x>=c[i]) ++ans,x-=c[i]; //贪心选择 
		else break;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：LLGZ (赞：2)

#### 01背包模板  
~~大水题~~

可以中途来，不可以中途走。所以要提前计算好第i天动物来时的所需粮食总数$s[i]=s[i]*(n-i+1)$

由此得状态转移方程$f[j]=max(f[j],f[j-s[i]]+1)$

#### 注意：要加freopen,不然会RE
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int f[100005];
int s[1005];
int n,x;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    cin>>n>>x;
    
    for(int i = 1;i <= n;i++)
    {
        cin>>s[i];
        
        s[i] =s[i] * (n-i+1);//初始化
    }
    
    for(int i = 1;i <= n;i++)
    for(int j = x;j >= s[i];j --)
	f[j] = max(f[j] , f[j-s[i]]+1);//直接套01背包模板
	
    cout<<f[x]<<endl; 
    return 0;
}
```




---

## 作者：partychicken (赞：1)

## ~~无耻地用别人代码写题解~~

na！贪心嘛。。。

第一眼一看还以为是dp，结果仔细一看，每只动物消耗的食物都是确定的。这样我们就可以把消耗排序，然后挨个取就OJBK了

管理员大大，求不变屎名

```
#include<cstdio>
#include<algorithm>

using namespace std;

int n, k, ans, cnt;
int a[110];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i] *= n - i + 1;
  }
  sort(a + 1, a + 1 + n);
  while (k - a[cnt + 1] >= 0 && cnt + 1 <= n) {
    ans++;
    k -= a[++cnt];
  }
  printf("%d\n", ans);
}
```

---

## 作者：szkzyc (赞：0)

这道题一看就是个标准的贪心问题，但是坑非常多，现在就来整理一下这些容易犯错误的点。

+ 1.一定要加上文件输入输出！
+ 2.不能拿到每天的吃草量就贪心，应该算出这几天一共吃的。
+ 3.这点与题目中的一致，动物来了以后就再也不能走了！

主要思路就是计算在这一天如果动物来了会在这 $n$ 天吃的粮食后再排序，利用贪心思想从吃的最少的开始枚举直到粮食不够了为止。

### AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n, x, cnt, a[100005];
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout); //千万要加这两行 
    cin >> n >> x;
    for(int i = 1; i <= n; i++) {
    	cin >> a[i];
    	a[i] *= (n - i + 1); //计算这n天要吃的粮食 
	}
	sort(a + 1, a + n + 1); //利用sort快速排序 
	for(int i = 1; i <= n; i++){
		if(x < a[i]) break; //如果粮食不够了，跳出循环 
		else x -= a[i]; //否则就减去目前这只动物吃的食物 
		cnt++; //动物个数加一 
	}
	cout << cnt << endl;
	return 0;
}

```
### ---end---


---

## 作者：Daidly (赞：0)

- 统计每一个动物的后续天数，然后计算出这个动物后续所有的消耗。

- 然后排序，因为要取最多的。

- 从小开始枚举，一旦超出总数（粮草用尽）就退出。

- 每次统计`ans`个数，并把总粮草数减去粮草消耗数。

- 最后输出`ans`值。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,sum,ans,a[105];
int main(){
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>n>>sum;
	for(int i=0;i<n;++i){
        cin>>a[i];
        a[i]*=n-i;
    }sort(a,a+n);
    for(int i=0;i<n;++i){
    	if(sum-a[i]<0)break;
        ans++;
        sum-=a[i];
    }cout<<ans;
	return 0;
}
```

---

## 作者：伟大的王夫子 (赞：0)

先宣传一下[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)

简单贪心

因为一个动物吃的量是一定的，所以我们将其吃的量排个序，在从小到大去选。可以证明，这样选的个数是最多的

最后提醒一下必须加文件输入输出。刚开始还因为这个WA了

输入文件：input.txt 

输出文件: output.txt

~~太坑人了~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[101];
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n >> m;
	for (register int i = 1; i <= n; ++i) {
		//读入
		int x;
		cin >> x;
		a[i] = (n - i + 1) * x;//总共吃的粮食 
	}
	sort(a + 1, a + n + 1);//贪心思想，从少的开始选
	int cnt = 0;
	for (register int i = 1; i <= n; ++i) {
		if (m >= a[cnt + 1]) {//如果还可以选 
			m -= a[++cnt];
		} else break;
	} 
	cout << cnt;
}
```

---

