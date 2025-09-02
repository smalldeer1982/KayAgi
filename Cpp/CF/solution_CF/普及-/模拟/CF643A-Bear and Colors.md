# Bear and Colors

## 题目描述

Bear Limak has $ n $ colored balls, arranged in one long row. Balls are numbered $ 1 $ through $ n $ , from left to right. There are $ n $ possible colors, also numbered $ 1 $ through $ n $ . The $ i $ -th ball has color $ t_{i} $ .

For a fixed interval (set of consecutive elements) of balls we can define a dominant color. It's a color occurring the biggest number of times in the interval. In case of a tie between some colors, the one with the smallest number (index) is chosen as dominant.

There are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643A/e72cbeaa17cceea137ec85134680a8c41a08d995.png) non-empty intervals in total. For each color, your task is to count the number of intervals in which this color is dominant.

## 说明/提示

In the first sample, color $ 2 $ is dominant in three intervals:

- An interval $ [2,2] $ contains one ball. This ball's color is $ 2 $ so it's clearly a dominant color.
- An interval $ [4,4] $ contains one ball, with color $ 2 $ again.
- An interval $ [2,4] $ contains two balls of color $ 2 $ and one ball of color $ 1 $ .

There are $ 7 $ more intervals and color $ 1 $ is dominant in all of them.

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
7 3 0 0 
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
6 0 0 
```

# 题解

## 作者：OMITW (赞：0)

# 思路推导

理解题目后养成好习惯，先看数据范围。$ 1 \le n \le 5000 $。没问题了，这题用 $ O(n^2) $ 的时间可以跑过。

然后仔细阅读题面。找一个区间，这个区间内出现次数最多的为主要颜色，如果有两个相同，则是编号小的。

那我们就可以每次从 $ i+1 $ 开始枚举到 $ n $，然后先找最大的，如果相同就选编号最小的。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5001],bj[5001],sum[5001],id;
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)bj[j]=0;
		id=0;
		for(int j=i;j<=n;++j)
		{
			++bj[a[j]];
			if(bj[a[j]]>bj[id])id=a[j];
			else if(bj[a[j]]==bj[id])id=id<a[j]?id:a[j];
			++sum[id];
		}
	}
	for(int i=1;i<=n;++i)
		printf("%d ",sum[i]);
	return 0;
}
```

---

## 作者：lizulong (赞：0)

## 题意
有 $n$ 个球，每个球有颜色 $a_i$，对于一个区间里的球，定义该区间的**统治颜色**为出现最多的颜色，如有多种方案则令颜色编号小的作为**统治颜色**。

现在对于每种颜色，输出其作为统治颜色的**区间数**。
## 思路
暴力枚举区间统计每种颜色出现的数量，而加入一种颜色后最大值只会从之前的最大值和这种颜色中取到，总时间复杂度 $O(n^2)$。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[5005],b[5005],c[5005];
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加快cin和cout
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        memset(b,0,sizeof(b));//每次清空b数组 
        b[a[i]]++,c[a[i]]++;
        int k=a[i];
        for(int j=i+1;j<=n;j++){
            b[a[j]]++;
            if(b[a[j]]>b[k] || b[a[j]]==b[k] && a[j]<k) k=a[j];
            c[k]++;
        }
    }
    for(int i=1;i<=n;i++){//输出 
        cout<<c[i];
        if(i==n)cout<<"\n";
        else cout<< " ";
	} 
    return 0;
}
```


---

## 作者：Zouzhuoxuan (赞：0)

# CF643A Bear and Colors 题解
### [Luogu 题目传送门](https://www.luogu.com.cn/problem/CF643A) / [Codeforces 题目传送门](https://codeforces.com/problemset/problem/643/A)
### [博客观感更好](https://www.luogu.com.cn/blog/800322/cf643a-bear-and-colors-ti-xie)
----------------
## 一、题意简述

有 $n$ 个球，定义一个区间的“主要颜色”为这个区间内出现次数最多的颜色，一共有 $\dfrac{n(n+1)}2$ 个区间，要你求每种颜色成为“主要颜色”的次数。

$n\le 5000$。

## 二、题目与算法分析

我们会马上想出一个十分暴力的做法：枚举每个区间，计算出这个区间的主要颜色，累加即可。这样子的做法是 $O(n^3)$ 的，不能通过，我们考虑优化。

发现一个区间有 $l,r$ 两端，所以我们可以枚举 $l,r$，这样子的时间复杂度是 $O(n^2)$ 的，可以通过。那我们要通过什么方式计算区间内的“主要颜色”呢？

容易发现，我们可以将计算“主要颜色”的循环放在枚举端点的位置， $r$ 循环 $1\to n$，$j$ 循环 $i \to 1$，在 $j$ 循环内可以计算“主要颜色”。详见代码。

## 三、完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 5005
using namespace std;
int a[N],t[N],ans[N];
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); 
	int n,i,j,maxn,id;
    cin>>n;
    for(i=1;i<=n;i++) cin>>a[i];
    for(i=1;i<=n;i++)
	{
        maxn=0,id=0;
        memset(t,0,sizeof(t)); //清空记录数组 
        for(j=i;j;j--)
		{
            t[a[j]]++; //记录这个颜色 
            if(t[a[j]]>maxn||t[a[j]]==maxn&&a[j]<id) maxn=t[a[j]],id=a[j]; //将这个颜色定义为"主要颜色" 
            ans[id]++;
        }
    } 
    for(i=1;i<=n;i++) cout<<ans[i]<<" ";
    return 0;
}
```

---

## 作者：happy_zero (赞：0)

我们可以先用一重循环枚举右端点 $i$，接下来从 $i$ 到 1 枚举左端点 $j$，开一个数组 $sum$ 记录每种颜色出现的次数，在枚举 $j$ 的同时取最大值即可，具体实现见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[5005];
int sum[5005];
int ans[5005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        int maxn=0,tx;//maxn用于记录次数，tx记录次数最多的编号
        memset(sum,0,sizeof(sum));//记得清零！
        for(int j=i;j>=1;j--){
            sum[a[j]]++;
            if(sum[a[j]]>maxn||sum[a[j]]==maxn&&a[j]<tx){取最大值，如果值相同则取编号小的那个
                maxn=sum[a[j]];
                tx=a[j];
            }
            ans[tx]++;//次数最多的ans[tx]++
        }
        
    } 
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<" ";
    return 0;
}
```


---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
Limak 有 $n$ 个球，从左到右编号依次为 $1 \dots n$。同时又有 $n$ 种颜色，从编号依次为 $1 \dots n$。第 $i$ 个球的编号为 $t_i$。

对于球中每一个固定的段（含有连续元素的集合），可以定义一个**主要颜色**，即此段中出现次数最多的颜色。在可以有多种主要颜色的情况下，选择编号最小的。

现有 $\dfrac{n(n + 1)}{2}$ 个不为空的段。对于每个颜色，你需要输出此颜色作为主要颜色的次数。

$n\le 5000$
## $\text{Solution}$
本来还觉得可能得想想，看到数据范围笑了。  
直接开桶 $n^2$ 暴力扫一遍即可。  
## $\text{Description}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5050;
#define ll long long
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
int bac[N],a[N],res,ans[N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=n;i++) a[i]=read();
  for(int l=1;l<=n;l++){
    memset(bac,0,sizeof(bac));
    for(int r=l;r<=n;r++){
      int o=a[r];
      ++bac[o];
      if(bac[o]>bac[res]||(bac[o]==bac[res]&&o<res)) res=o;
      ans[res]++;
    }
  }
  for(int i=1;i<=n;i++) printf("%d ",ans[i]);
  return 0;
}
/*
*/

```


---

## 作者：yangzd (赞：0)

# 题目大意：

有 $n$ 个球，每个球有一个颜色 $c[i]$，对于一个区间里的球，定义该区间的统治颜色为出现次数最多的颜色，如果有多种颜色出现次数都是最多的则选择颜色编号小的那个座位统治颜色，现在对于每种颜色，输出其作为统治颜色的区间数。

# 分析：

暴力枚举区间统计每种颜色出现的数量，注意到加入了一种颜色后最大值只会从之前的最大值和这种颜色中取到，故每次更新最大值是 $O(1)$ 的，总时间复杂度 $O(n^2)$。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,c[5005],num[5005],ans[5005];

signed main()
{
	ios::sync_with_stdio(0);
	
	memset(num,0,sizeof(num));
    memset(ans,0,sizeof(ans));
	
    cin >> n;
    
    for(long long i=1; i<=n; i++)
    	cin >> c[i];
    
    for(long long i=1; i<=n; i++)
    {
        memset(num,0,sizeof(num));
        
        num[c[i]]++;
		ans[c[i]]++;
		
        long long maxn=c[i];
        
        for(long long j=i+1; j<=n; j++)
        {
            num[c[j]]++;
            
            if(num[c[j]]>num[maxn] || num[c[j]]==num[maxn] && c[j]<maxn)
				maxn=c[j];
				
            ans[maxn]++;
        }
    }
    
    for(long long i=1; i<=n; i++)
    {
        cout << ans[i];
        
        if (i==n)
        	cout << endl;
        	
        else
        	cout << " ";
    } 
    
    return 0;
}
```

---

## 作者：N_z_ (赞：0)

## 思路
考虑枚举区间，因为我们只需要知道区间最大值，所以我们维护当前区间最大值和每种颜色的数量，并且每次将区间向右扩张，扩张一个就判断它是否是区间最大值，具体实现见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5001],b[5001],c[5001];
int main()
{
    int n;
    cin>>n;
    for(int x=1;x<=n;x++)
    cin>>a[x];
    for(int l=1;l<=n;l++)
    {
        memset(b,0,sizeof(b));
        int nowmax=1;
        for(int r=l;r<=n;r++)
        {
            b[a[r]]++;
            if(b[a[r]]>b[nowmax]||(b[a[r]]==b[nowmax]&&a[r]<nowmax))nowmax=a[r];
            c[nowmax]++;
        }
    }
    for(int x=1;x<=n;x++)
    cout<<c[x]<<' ';
}
```

---

