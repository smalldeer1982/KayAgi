# [COCI 2015/2016 #6] PUTOVANJE

## 题目描述

$\text{Mislav}$ 最喜欢在森林里度过时光，因为森林里有各种各样的水果，吃了每种水果都能获得一定的饱食度。但他不会使自己的总饱食度超过 $C$。

现在森林里有一条小径，小径旁顺次种了 $N$ 个水果，每个水果都有一个饱食度 $w_i$。$\text{Mislav}$ 可以选择从任意一个水果的位置开始，往第 $N$ 个水果前进。在前进的过程中，如果吃下当前位置的水果，总饱食度不会超过 $C$，他就**一定会吃下该水果**。否则，他就会**跳过该水果**，继续前进。

请问 $\text{Mislav}$ 能吃掉的水果个数最多是多少？

## 说明/提示

**【样例 1 解释】**

如果 $\text{Mislav}$ 决定从第 $1$ 个水果开始吃，那么他可以吃到第 $1$、$2$、$4$ 个水果，一共吃了 $3$ 个。如果他从第 $2$ 种水果开始吃，那么他可以吃到第 $2$、$3$、$4$、$5$ 共 $4$ 个水果。

**【数据范围】**

对于 $100\%$ 的数据，$1\le N\le 1000$，$1\le C\le 10^6$，$1\le w_i\le 1000$。

**【题目来源】**

**题目译自 [COCI 2015-2016](https://hsin.hr/coci/archive/2015_2016/) [CONTEST #6](https://hsin.hr/coci/archive/2015_2016/contest6_tasks.pdf) T2 PUTOVANJE**。

**本题分值按 COCI 原题设置，满分 $80$**。

## 样例 #1

### 输入

```
5 5
3 1 2 1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
7 5
1 5 4 3 2 1 1```

### 输出

```
3```

## 样例 #3

### 输入

```
5 10
3 2 5 4 3```

### 输出

```
3```

# 题解

## 作者：超级玛丽王子 (赞：10)

这道题目教会了我们什么呢？**学会看数据范围**

一开始做这题没看数据范围搞了个 $O(N\log N)$ 的二分做法（后面会简单讲），写完才发现数据范围写的清清楚楚：$N\le10^3$。

于是依照题意乖乖的写 $O(N^2)$。开一个数组记录“饱食度”，并枚举起点。依照题意找出对应的终点，算出能吃到的果子数量。最后算出每一次吃到的果子数量中的最大值即可。

粗略计算：这个算法的复杂度在最坏情况下是 $O\left(\dfrac{N(N+1)}{2}\right)=O(N^2)$，最优情况是 $O(N)$。均摊一下可能是 $O(N\log N)$ 或者 $O(N\sqrt N)$ 之类的，根本不需要二分（枯了）（

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,c,w[1050];
int ans,cur,curr; 
int main(void) {
	cin>>n>>c;
	for(int i=0;i<n;++i) cin>>w[i];
	for(int st=0;st<n;++st) {
		cur=curr=0;
		for(int pos=st;pos<n;++pos) {
			if(curr+w[pos]<=c) cur++,curr+=w[pos];
		}
		ans=max(ans,cur);
	}
	cout<<ans<<endl;
}
```

至于二分的做法是维护一个前缀和，枚举起点，然后在前缀和上二分查找相应的终点。这个做法是稳定的 $O(N\log N)$，如果数据开到 $10^6$ 就必须要这样做了。

---

## 作者：Sky_exe (赞：7)

此题考点：**暴力枚举**

按照题意，我们可以直接暴力枚举每一种情况，最后取最优解即可。

考虑时间复杂度和范围，不会超时。
## **_AC Code：_**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100001],n,sum=0,c,ans=0,maxn;//由题目得~
int main()
{
    cin>>n>>c;
    for(int i=1;i<=n;i++) cin>>a[i];//输入
    for(int i=1;i<=n;i++)
    {
        sum=0,maxn=0;
        for(int j=i;j<=n;j++)//遍历
        {
            if(sum+a[j] <= c)//判断是否可以吃
            {   
                sum+=a[j];//饱食度
                maxn++;//数量增加
            }
        }
        ans = max(maxn,ans);//选取最优解
    }
    cout<<ans<<endl;//输出
    return 0;
}//完结撒花~
```



---

## 作者：ForeverCC (赞：5)

每次枚举起点，然后遍历数组，如果当前总饱食度加上当前位置的水果的饱食度不会超过 C，加上这个饱食度，更新吃下的水果数量的最大值。最后输出即可。

因为 $n<=10^3$  ，所以 $n^2$ 的算法就能过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,ans=-1e9,a[1005];
int main() {
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		int sum=0,cnt=0;
		for(int j=i;j<=n;j++){
			if(sum+a[j]<=c)
				sum+=a[j],cnt++;
			ans=max(ans,cnt);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：永动姬 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P7798)


### 分析时间

由于数据规模很小，所以上暴力即可，~~除了暴力一时也没想到好的~~

### 代码时间 

```cpp
#include<bits/stdc++.h>//万能头，可以帮你省去其他头文件 
using namespace std;
int n,c;
int a[1234];//数组要开够 
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);//一个能加速cin,cout的东东，或许有用 
	cin>>n>>c;//输入 
	int maxn=-10;//把maxn赋值为一个负数，这样才能更新最大值 
	for(int i=1;i<=n;i++){//朴实地输入 
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){//开始暴力 
		int tmp=0,ans=0; 
		for(int j=i;j<=n;j++){
			if(tmp+a[j]<=c){//能吃就吃 
				tmp+=a[j];ans++; 
			}
			maxn=max(maxn,ans);//更新最大值 
		}
	}
	cout<<maxn<<' ';//输出最大值 
	return 0;//好习惯 
}

```




---

## 作者：我从不碰电脑 (赞：0)

**题目分析**

枚举每个出发点然后向下遍历，本题可以直接暴力。

增加一个优化时间的代码：`if(b==c) break;`

假如饱食度和极限饱食度 `c` 一样了，接下来的食物必定一个也不吃，所以这种情况直接跳过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,c,a[1002],b,maxx=0,sum; 
int main(){
    cin>>n>>c;
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=1; i<=n; i++) //遍历起点
    {
        sum = 0;
        b = 0;
        for(int j=i; j<=n; j++) //遍历之后的路
        {
            if( b+a[j]<=c )
            {
                b+=a[j];
                sum++;
            }
            if( b==c ) break;
        }
        maxx=max( maxx,sum );
    }
    cout<<maxx;
    return 0;
}
```


---

## 作者：Sya_Resory (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P7798)

由于 $n \le 10^3$，$O(n^2)$ 的算法可以通过，因此考虑直接模拟。

模拟时，每次枚举开始的位置，按题意模拟算出当前开始位置所对应的答案，最后更新答案。

具体细节见代码。

```cpp
#include <cstdio>

int n,C,w[1005]; // 见题面
int ans; // 最终答案

int main() {
    scanf("%d%d",&n,&C);
    for(int i = 1;i <= n;i ++) scanf("%d",w + i); // 输入
    for(int i = 1;i <= n;i ++) { // 枚举开始位置
        int cur_ans = 0,cur_w = 0; // 定义当前开始位置对应的答案，以及模拟过程中所需要的“当前饱食度”
        for(int j = i;j <= n;j ++) // 一个一个模拟
            if(cur_w + w[j] <= C) cur_w += w[j],cur_ans ++; // 如果能吃掉就更新数据
        if(cur_ans > ans) ans = cur_ans; // 更新最终答案
    }
    printf("%d\n",ans); // 输出
    return 0; // 好习惯
}
```

---

## 作者：lanretE (赞：0)

根据题意，由于数组范围极小，枚举起点即可，定义 $ans$ 记录答案，如果发现更大可接受果子数量则更新。

注意给 $ans$ 赋上极小值。

### AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
int w[1010];//饱食度 
int main(){
	int n,c,ans=-1e9;
	cin>>n>>c;
	for(int i=1;i<=n;++i) cin>>w[i];
	//枚举起点
	for(int i=1;i<=n;++i){
		int cnt=0,now_w=0;//分别为果子数量和现有饱食度
		for(int j=i;j<=n;++j){
			if(now_w+w[j]<=c){
				now_w+=w[j]; cnt++;
			} 
		} 
		ans=max(cnt,ans);
	}
	cout<<ans<<endl;	
   	return 0;//养成好习惯
} 
```


---

## 作者：little_cindy (赞：0)

此题考察算法： $\colorbox{#E74C3C}{\color{white}枚举，暴力}$。

## 思路
这一题不愧是红题，一看数据范围：
> $1\le N\le10^3,1\le C\le10^6$
我们可以知道，只有一下几种复杂度满足条件（按复杂度排序）：
- $O(N)$
- $O(N\log_2N)$
- $O(C)$
- $O(N\log_2C)$
- $O(N^2)$
- $O(C\log_2N)$
- $O(C\log_2C)$

带 $\log$ 的就别想了，入门题哪来这么麻烦。一重循环又不够，所以，我们这个答案的时间复杂度必须是 $O(N^2)$。说明我们需要两层循环 $N$，第一层枚举起点 $i$，第二层枚举以点 $i$ 为起点，最多可以吃几个水果，取最大值即可。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,tmp,cnt;//n为水果个数，m为总饱食度的最大值，ans为答案，tmp负责在枚举时统计当前吃了的水果的总饱食度，cnt负责在枚举时统计当前吃了的水果的总个数
int w[1005];//每个水果的饱食度
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>w[i];
	}
	for(int i=1;i<n;i++){//枚举起点i
		for(int j=i;j<=n;j++){//处理当前节点j
    		if(tmp+w[j]<=m){
    			tmp+=w[j];//累加
    			cnt++;//记录
			}
		}
		ans=max(ans,cnt);//取最大值
		cnt=tmp=0;//清0
	}
	cout<<ans;
	return 0;
}
```

### update time 1:2021-8-9
按照管理员的建议修改（洛谷的管理真有耐心）

---

## 作者：Beep_Monkey (赞：0)

这道题是一个大暴力，枚举每个点到 $n$ 能吃到的水果数，然后更新 $ans$ 的值即可。

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,a[1005],sum,ans=-1e9,t;
int main(){
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){//暴力
		t=sum=0;
		for(int j=i;j<=n;j++){
			if(t+a[j]<=c) sum++,t+=a[j];
		}
		ans=max(ans,sum);
	}
	printf("%d",ans);
	return 0;
} 
```


---

