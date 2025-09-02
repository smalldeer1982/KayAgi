# [USACO18JAN] Lifeguards B

## 题目背景

本题翻译来自 deepseek-v3。

## 题目描述

Farmer John 为他的奶牛们开设了一个游泳池，认为这将帮助它们放松并产更多的奶。

为了确保安全，他雇佣了 $N$ 头奶牛作为救生员，每头奶牛的班次覆盖一天中的某个连续时间段。为简单起见，游泳池每天从时间 $t=0$ 开放到时间 $t=1000$，因此每个班次可以用两个整数描述，分别表示奶牛开始和结束其班次的时间。例如，一头救生员从时间 $t=4$ 开始到时间 $t=7$ 结束，覆盖了 $3$ 个单位的时间（注意端点表示时间点）。

不幸的是，Farmer John 多雇佣了 $1$ 名救生员，超出了他的资金支持范围。鉴于他必须解雇恰好 $1$ 名救生员，剩下的救生员的班次能够覆盖的最长时间是多少？如果至少有一名救生员在场，则某个时间段被视为被覆盖。

## 样例 #1

### 输入

```
3
5 9
1 4
3 7```

### 输出

```
7```

# 题解

## 作者：qw1234321 (赞：18)

### 题内话

同 [P1696](https://www.luogu.com.cn/problem/P1696)，又是一道简单的暴力水题。

第一层循环枚举被解雇的奶牛的编号，第二层循环枚举除了被解雇的奶牛，其他奶牛的工作时间，第三重循环从从工作时间的左端点枚举到右端点，打个标记，再把所有打上了标记的时间点的个数都统计一下，答案就是统计出的结果里面的最大值。

详见代码：


```cpp
#include<iostream>
using namespace std;

int n, ans = -1e7;
struct node{
	int x, y;
}a[105];
bool vis[10005];

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
    	cin >> a[i].x >> a[i].y;
	}
	for (int i = 1; i <= n; i++){
		int cnt = 0;
		for (int j = 0; j <= 1000; j++) vis[j] = 0;
		for (int j = 1; j <= n; j++){
			if (j == i) continue;
			for (int k = a[j].x; k < a[j].y; k++){
				vis[k] = 1;
			}
		}
		for (int j = 0; j <= 1000; j++) if (vis[j]) cnt++;
		ans = max(ans, cnt);
	}
	cout << ans;
    return 0;
}
```

---

## 作者：sdsshwt (赞：6)

# P1697 [USACO18JAN] Lifeguards B 题解
暴力，一头一头试是否解雇，选出最大值。
### 注意：在计数时，算段时间，每头比原来点相减少一！！！
#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a[1005],b[1005],ma=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=n;i++){
		int t[10005]={},s=0;
		for(int j=1;j<=n;j++){
			if(j!=i){
				for(int i=a[j];i<b[j];i++){
					t[i]=1;
				}
			}
		}
		for(int i=0;i<=10000;i++){
			if(t[i])s++;
		}
		ma=max(ma,s);
	}
	cout<<ma;
	return 0;
}
```

---

## 作者：Tjaweiof (赞：4)

# P1697 题解
[题目传送门](https://www.luogu.com.cn/problem/P1697)

## 题意描述
农场主约翰为他的奶牛们开了一个游泳池，他认为这样可以帮助它们放松，从而产更多的牛奶。为了确保安全，他雇佣了 $N$ 头牛作为救生员，每头牛都有一个轮班，覆盖白天的一段连续时间。为简单起见，游泳池每天从时间 $t=0$ 开始，一直开放到时间 $t=1000$，因此每次轮班可以用两个整数来描述，给出了一头奶牛开始和结束轮班的时间。例如，一名救生员从时间 $t=4$ 开始，到时间 $t=7$ 结束，覆盖了三个时间单位（注意，端点是一个时间点）。不幸的是，农夫约翰雇佣的救生员比他所能负担的还要多。因此他必须解雇一名救生员，那么剩余救生员的轮班最多可以覆盖多少时间？如果至少有一名救生员在场，则认为这一段时间被覆盖了。

## 思路
枚举每一个奶牛，求出如果这个奶牛被解雇了会多几段未被覆盖的时间，取最小值，然后用原来能够覆盖的时间减去这个最小值就行了。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[101], b[101], t[1001], res, nmin = 0x3f3f3f3f, cnt;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i] >> b[i];
        for (int j = a[i]; j < b[i]; j++){
            if (!t[j]){
                res++;
            }
            t[j]++;
        }
    }
    for (int i = 1; i <= n; i++){
        cnt = 0;
        for (int j = a[i]; j < b[i]; j++){
            if (t[j] == 1){
                cnt++;
            }
        }
        nmin = min(nmin, cnt);
    }
    cout << res - nmin;
    return 0;
}

```

---

## 作者：Jin_Yichen (赞：2)

说实话，这道暂无评定的题可以评红了，因为暴力可过……
## 思路
分三层循环暴力枚举：第一层枚举解雇奶牛的编号；第二层循环枚举其他奶牛；第三层循环计算这只奶牛的工作时间，把时间范围内的位置都做个标记，再统计一下共有几个做了标记的点，最后在所有答案中取最大值，就是最终答案。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=-INT_MAX,l[105],r[105];
bool vis[1005]= {false};//标记数组
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d%d",&l[i],&r[i]);//工作时间左右端点
	for(int i=1; i<=n; i++) {
		int maxcover=0;
		memset(vis,false,sizeof vis);//初始化标记数组
		for(int j=1; j<=n; j++) {
			if(j==i)continue;//当前奶牛不计算
			for(int k=l[j]; k<r[j]; k++)
				vis[k]=true;
			//在这只奶牛工作时间内的时间点都做好标记
		}
		for(int j=0; j<=1000; j++)
			if(vis[j])maxcover++;//求有多少个标记点
		ans=max(ans,maxcover);//更新答案
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：xu_zhihao (赞：2)

### 题目理解：
  - 这道题纯纯就是一个暴力题，数据范围非常的小，每一次只用枚举删除其中一个区间就行了。
  
### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int l[100010];
int r[100010];
map<int,int>mp;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>l[i]>>r[i];
	}
	int mx=0;
	for(int i=0;i<n;i++)
	{
		int flag[1010];
		memset(flag,0,sizeof(flag));
		for(int j=0;j<n;j++)
		{
			if(i==j)
			{
				continue;
			}
			for(int k=l[j];k<r[j];k++)
			{
				flag[k]=1;
			}
		}
		int cnt=0;
		for(int j=0;j<=1010;j++)
		{
			if(flag[j]==1)
			{
				cnt++;
			}
		}
		mx=max(mx,cnt);
	}
	cout<<mx;
}
```


---

## 作者：nkrqzjc_zzz (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/P1697)

------------
### 题外话：


哦！第一次写红题的题解呢。

题面其他大佬那里有，我就主要讲讲我的思路和代码实现。

------------

### 思路

因为 $n\leq100$ 很明显可以随便暴力。

模拟 $1$ 到 $n$ 个救生员被解雇的情况，因为 $0\leq t\leq1000$。所以可以用一种类似有桶的方法，开一个大小为 $1000$ 的数组，每次将一个人的区间全部加上去。

这里我用了一个函数，叫 ```fill```。它的作用是将某个数组内的区间赋上同一个值，这个函数的用法类似 ```sort```，前两个参数代表你需要改变的区间，后一个数字是这个区间内的数需要赋什么值。

好水呀！感觉都没什么可以说的了。（管理员辛苦了！）

那么，我们就看代码吧。

------------

### 代码

```cpp
#include<bits/stdc++.h> 
int n,a,b[102],c[102],d[1002],dn;//变量和数组定义主函数外面，自动清零 
main(){
	scanf("%d",&n);//输入用scanf要比cout快一点点，但是对输入类型要求很严格，如：int——%d、char——%c 
	for(int i=1;i<=n;i++)scanf("%d%d",&b[i],&c[i]); 
	for(int i=1;i<=n;i++){
		memset(d,0,sizeof d);dn=0;//初始化清零 
		for(int j=1;j<=n;j++){
			if(j==i)continue;
			std::fill(d+b[j],d+c[j],1);//这个函数是对d+b[j]到d+c[j]-1的区间全部赋值为1 
		}
		for(int j=0;j<=1000;j++)if(d[j])dn++;//记录答案 
		a=a>dn?a:dn;//可以等价替换a=max(a,dn)，找到最大的答案 
	}
	printf("%d",a);//输出答案 
}
```


---

## 作者：_little_Cabbage_ (赞：2)

# P1697 [USACO18JAN] Lifeguards B 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p1697)~~

这是一道暴力水题。

我们可以从 $1$ 到 $n$ 枚举，假设第 $i$ 头牛被解雇了，然后用一个标记数组 $f$ 统计那些没被解雇的奶牛，他们的工作总时间是多少，取每种情况的工作总时间的最大值就行了。

这里有一个坑，我没读题，从每个奶牛的左端点枚举到了右端点，但实际上应该枚举到右端点 $-1$。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int l,r;
}a[110];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].l,&a[i].r);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		bool f[1010]={false};
		for(int j=1;j<=n;j++)
		{
			if(i==j)
			{
				continue;
			}
			for(int b=a[j].l;b<a[j].r;b++)//坑点
			{
				f[b]=true;
			}
		}
		int cnt=0;
		for(int j=0;j<=1000;j++)
		{
			if(f[j]==true)
			{
				cnt++;
			}
		}
		ans=max(ans,cnt);
	}
	cout<<ans;
}
```
[AC 记录](https://www.luogu.com.cn/record/142325388)

---

