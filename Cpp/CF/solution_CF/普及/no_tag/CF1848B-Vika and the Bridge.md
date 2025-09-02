# Vika and the Bridge

## 题目描述

In the summer, Vika likes to visit her country house. There is everything for relaxation: comfortable swings, bicycles, and a river.

There is a wooden bridge over the river, consisting of $ n $ planks. It is quite old and unattractive, so Vika decided to paint it. And in the shed, they just found cans of paint of $ k $ colors.

After painting each plank in one of $ k $ colors, Vika was about to go swinging to take a break from work. However, she realized that the house was on the other side of the river, and the paint had not yet completely dried, so she could not walk on the bridge yet.

In order not to spoil the appearance of the bridge, Vika decided that she would still walk on it, but only stepping on planks of the same color. Otherwise, a small layer of paint on her sole will spoil the plank of another color. Vika also has a little paint left, but it will only be enough to repaint one plank of the bridge.

Now Vika is standing on the ground in front of the first plank. To walk across the bridge, she will choose some planks of the same color (after repainting), which have numbers $ 1 \le i_1 < i_2 < \ldots < i_m \le n $ (planks are numbered from $ 1 $ from left to right). Then Vika will have to cross $ i_1 - 1, i_2 - i_1 - 1, i_3 - i_2 - 1, \ldots, i_m - i_{m-1} - 1, n - i_m $ planks as a result of each of $ m + 1 $ steps.

Since Vika is afraid of falling, she does not want to take too long steps. Help her and tell her the minimum possible maximum number of planks she will have to cross in one step, if she can repaint one (or zero) plank a different color while crossing the bridge.

## 说明/提示

In the first test case, Vika can repaint the plank in the middle in color $ 1 $ and walk across the bridge without stepping over any planks.

In the second test case, Vika can repaint the plank in the middle in color $ 2 $ and walk across the bridge, stepping over only one plank each time.

In the third test case, Vika can repaint the penultimate plank in color $ 2 $ and walk across the bridge, stepping only on planks with numbers $ 2 $ and $ 5 $ . Then Vika will have to step over $ 1 $ , $ 2 $ and $ 1 $ plank each time she steps, so the answer is $ 2 $ .

In the fourth test case, Vika can simply walk across the bridge without repainting it, stepping over two planks each time, walking on planks of color $ 3 $ .

In the fifth test case, Vika can simply walk across the bridge without repainting it, without stepping over any planks.

## 样例 #1

### 输入

```
5
5 2
1 1 2 1 1
7 3
1 2 3 3 3 2 1
6 6
1 2 3 4 5 6
8 4
1 2 3 4 2 3 1 4
3 1
1 1 1```

### 输出

```
0
1
2
2
0```

# 题解

## 作者：wangjingtian1234 (赞：7)

# [洛谷题目](https://www.luogu.com.cn/problem/CF1848B) 

# [CF题目](https://codeforces.com/contest/1848/problem/B)

### 思路分析

一开始认为是二分，写着写着发现 check 函数写不出来（可能是本人比较菜）。

后来想到贪心。共有 $k$ 种颜色，考虑求出每种颜色的木板之间的最大间隔 $a$ 和次大间隔 $b$。为啥要次大值呢，因为可以将一块木板涂成别的颜色，那一定会把最大间隔中间的木板涂成该种颜色，使最大间隔缩小至 $\lfloor a \div 2 \rfloor$。令 $c_i$ 为走第 $i$ 个颜色时，最大那步的大小。显然  $c_i = \max(\lfloor a \div 2 \rfloor,b)$，求 $c_i$ 的最小值即可。

但是需要注意，第 $n + 1$ 块木板要作为所有颜色木板的结束，各种颜色木板的最后一块都应与第 $n + 1$ 块求间隔，将其也作为间隔之一处理。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n, k, a[200010], las[200010], Max[200010], ciMax[200010], Ans;


void Solve()
{
	cin >> n >> k;
	for (int i = 1; i <= k; i++)
	{
		las[i] = 0;
		Max[i] = 0;
		ciMax[i] = 0;	
	}//清零（memset 会 TLE）
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++)
	{
		if (i - las[a[i]] - 1 > Max[a[i]])
		{
			ciMax[a[i]] = Max[a[i]];
			Max[a[i]] = i - las[a[i]] - 1;
		}
		else if (i - las[a[i]] - 1 > ciMax[a[i]]) ciMax[a[i]] = i - las[a[i]] - 1;
		las[a[i]] = i;
	}//求出次大值和最大值
	for (int i = 1; i <= k; i++)
	{
		if (n + 1 - las[i] - 1 > Max[i])
		{
			ciMax[i] = Max[i];
			Max[i] = n + 1 - las[i] - 1;
		}
		else if (n + 1 - las[i] - 1 > ciMax[i]) ciMax[i] = n + 1 - las[i] - 1;
	}//关于第n+1块木板的处理
	for (int i = 1; i <= k; i++)
	{
		Max[i] /= 2;
		Max[i] = max(Max[i], ciMax[i]);
	}//求出最大脚步大小
	Ans = n;
	for (int i = 1; i <= k; i++)
	{
		if (las[i] == 0) continue;
		Ans = min(Ans, Max[i]);
	}//求最小脚步
	cout << Ans << endl;//输出
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	long long T; cin >> T;
	while (T--) Solve();
	return 0;
}
```

Thank you for reading this solution！

---

## 作者：RAINBOW_ddd (赞：5)

## 思路

对于每一个颜色去统计一个 $Max_i$ 为相邻两个颜色间距离的最大值，再统计一个相邻两个颜色间距离的次大值 $SecMax_i$，然后对于每一个颜色去计算其答案由 $\max (SecMax_i,\dfrac{Max_i}{2})$ 来更新即可。

然后最后把每个颜色跑一遍取最大值就可以了。

Tips：要记得最后一个还要跑出去（调了好一会）。

## 代码

```c++
/*
 * @Author:Kaneki
 * @Date:2023-11-04 14:21:38
 * @Last Modified by:Kaneki
 * @Last Modified Time:2023-11-04 14:21:38
 * @Description:Kaneki
*/
#include<bits/stdc++.h>
using namespace std;
int T,N,K,num[200005],pre[200005],Max[200005],SecMax[200005];
int main(){
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>N>>K;
        for(int i=1;i<=N;i++){
            cin>>num[i];
            if(i-pre[num[i]]-1>Max[num[i]])SecMax[num[i]]=Max[num[i]],Max[num[i]]=i-pre[num[i]]-1;//更新最大值
            else if(i-pre[num[i]]-1>SecMax[num[i]])SecMax[num[i]]=i-pre[num[i]]-1;//更新次大值
            pre[num[i]]=i;//记录num[i]颜色上次出现的位置
        }
        int ans=0x7fffffff;
        for(int i=1;i<=K;i++){//考虑每个颜色最后走出去对答案的贡献
            if(N-pre[i]>Max[i])SecMax[i]=Max[i],Max[i]=N-pre[i];
            else if(N-pre[i]>SecMax[i])SecMax[i]=N-pre[i];
        }
        for(int i=1;i<=K;i++){//更新答案
            ans=min(max(SecMax[i],Max[i]/2),ans);
        }
        printf("%d\n",ans);
        for(int i=1;i<=N;i++) pre[i]=0;
        for(int i=1;i<=K;i++) Max[i]=0,SecMax[i]=0;//多测清空
    }
    return 0;
}
```



---

## 作者：HNOIRPplusplus (赞：4)

## 题意

+ 你有一座桥，桥上有一堆各色的木板。
+ 你可以改一块木板的颜色。（不是非要改）
+ 求同一种颜色木板之间最大距离的最小值。

## 思路

首先我们假设某一种木板之间的最大跨度为 $a$，第二大跨度为 $b$。那么如果我们要改一块木板的颜色，应该放在哪里呢？  
显然，应该放在最大跨度的最中间，可以减得最小。那么现在 $a$ 就被我们变成了 $\lfloor \frac{a}{2} \rfloor$。那么现在的最大跨度变成了 $\max(\lfloor \frac{a}{2} \rfloor , b)$。  
好消息是这个算法时空复杂度都是一次的，非常轻松的可以过这个题。

## 代码

```cpp
#include <iostream>

using namespace std;

const int N = 1000005;

int maxx[N]/*最大跨度*/, maxxx[N]/*次大跨度*/;
int last[N]/*每种颜色的最后一个*/, a[N];

int main() {
  int t;
  cin >> t;
  while(t--) {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
      int dis = i - last[a[i]] - 1;
      if(dis > maxxx[a[i]]) {
        maxx[a[i]] = maxxx[a[i]];
        maxxx[a[i]] = dis;
      } else if(dis > maxx[a[i]]) {
        maxx[a[i]] = dis;
      }
      last[a[i]] = i;
    }
    for(int i = 1; i <= m; i++) { // 别忘了最后还有一步路要回到家里面
      int dis = n - last[i];
      if(dis > maxxx[i]) {
        maxx[i] = maxxx[i];
        maxxx[i] = dis;
      } else if(dis > maxx[i]) {
        maxx[i] = dis;
      }
    }
    int ans = 1145141919; // 好看的最大值
    for(int i = 1; i <= m; i++) {
      ans = min(ans, max(maxx[i], maxxx[i] / 2));
    }
    cout << ans << '\n';
    for(int i = 1; i <= m; i++) {
      last[i] = maxx[i] = maxxx[i] = 0; // 多测要清空
    }
  }
}
// CF1848 B
```

## 总结

这是一道比较简单的题。稍微在维护最大和次大跨度上面花一点功夫，注意一下细节，这个题就可以拿下了。

[AC on Luogu](/record/116368184) [AC on CF with 280ms and 15664KB](https://codeforces.com/problemset/submission/1848/214436834)

---

## 作者：Coffee_zzz (赞：3)

### 分析

发现两个不同颜色的木板之间没有关联，那我们用像链式前向星的方式存储每个木板的前一个相同颜色的木板的位置，然后一次枚举每种颜色。

对于每种颜色，我们设这种颜色的木板的数量为 $m$，位置分别为 $s_1,s_2,s_3,\cdots,s_m$，则 Vika 走这种颜色每一步跨过的木板数分别为 $s_1-1,s_2-s_1-1,s_3-s_2-1,\cdots,s_m-s_{m-1}-1,n-s_m$。我们设其中最大值为 $p$，次大值为 $q$，由于我们要使 Vika 一步尽可能小，步子最大的地方重新刷一下颜色，此时 $p$ 变成了 $\lfloor \dfrac{p}{2}\rfloor$，于是我们比较 $\lfloor \dfrac{p}{2}\rfloor$ 和 $q$ 的大小关系，走这种颜色的最大步就为 $\max(\lfloor \dfrac{p}{2}\rfloor,q)$，输出所有颜色中 $\max(\lfloor \dfrac{p}{2}\rfloor,q)$ 的最小值即可。

### 代码

```c++
void solve(){
	n=read(),k=read();
	int ans=1e9;
	for(int i=1;i<=n;i++) head[i]=nxt[i]=0;
	for(int i=1;i<=n;i++){
		c[i]=read();
		nxt[i]=head[c[i]];
		head[c[i]]=i;
	}
	for(int p=1;p<=k;p++){
		if(!head[p]) continue;
		int ma1=n-head[p],ma2=0,l;
		for(int i=head[p];i;i=nxt[i]){
			l=i-nxt[i]-1;
			if(l>ma1) ma2=ma1,ma1=l;
			else if(l>ma2) ma2=l;
		}
		ans=min(ans,max(ma1/2,ma2));
	}
	cout<<ans<<endl;
}
```

---

## 作者：technopolis_2085 (赞：2)

分析：

由于答案为最大值最小，所以可以想到二分答案。

首先，预处理出如下数组：

$beg_i$ 表示第 $i$ 种颜色第一次出现的地方。

$en_i$ 表示第 $i$ 种颜色最后一次出现的地方。

$lst_i$ 表示第 $a_i$ 种颜色在第 $i$ 位置前出现的最后一个位置。

$mxd_i$ 表示第 $i$ 种颜色中两个都为第 $i$ 种颜色的地板之间的距离的最大值。

$mxd2_i$ 表示第 $i$ 种颜色中两个都为第 $i$ 种颜色的地板之间的距离的次大值。



------------

当我们二分到一个答案 $x$ 时：

我们遍历一遍每一种颜色，假设当前的颜色为 $i$。

我们发现，更改颜色只会在两个都为第 $i$ 种颜色的地板中距离最大的两块地板中的中间。

所以，最大距离变为 $mxd_i$ 除以 $2$ 的值和 $mxd2_i$ 中的最大值。

当存在一种颜色 $i$，使得最大距离小于等于 $x$ 时，当前二分的答案符合要求。

至于为什么要存 $mxd2_i$，因为当你改完了 $mxd_i$ 之后，存在一种可能性，即 $mxd_i$ 除以 $2$ 小于等于 $x$，但是 $mxd2_i$ 大于 $x$，这样是不合法的。

由于本题为多次测试，记得清空数组。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+10;
int a[maxn];
int appear[maxn];
int n,k;

int lst[maxn];
int beg[maxn],en[maxn];
int mx_d[maxn],mx_d2[maxn];
map<int,int> mp;//col place

bool check(int x){
	for (int i=1;i<=k;i++){
		int num=mx_d[i];
		if (num/2<=x&&mx_d2[i]<=x) return true;
	}
	
	return false;
} 

int main(){
	int T;
	scanf("%d",&T);
	
	while (T--){
		scanf("%d%d",&n,&k);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]),appear[a[i]]=1;
		
		
		for (int i=1;i<=k;i++){
			mp[i]=0;
			beg[i]=en[i]=0;
			mx_d[i]=mx_d2[i]=0;
		}
		
		for (int i=1;i<=n;i++){
			if (beg[a[i]]==0){
				beg[a[i]]=i;
			}
		}
		
		for (int i=n;i>=1;i--){
		//	if (appear[a[i]]==0) continue;
			if (en[a[i]]==0){
				en[a[i]]=i;
			}
		}
		
		for (int i=1;i<=n;i++){
		//	if (appear[a[i]]==0) continue;
			if (mp[a[i]]==0){
				lst[i]=i;
				mp[a[i]]=i;
			}else{
				lst[i]=mp[a[i]];
				mp[a[i]]=i;
			}
			
			if (i-lst[i]-1>mx_d[a[i]]){
				mx_d2[a[i]]=mx_d[a[i]];
				mx_d[a[i]]=i-lst[i]-1; 
			}else if (i-lst[i]-1>mx_d2[a[i]]) mx_d2[a[i]]=i-lst[i]-1;
		}
		
		for (int i=1;i<=k;i++){
		//	if (appear[i]==0) continue;
			if (beg[i]-1>mx_d[i]){
				mx_d2[i]=mx_d[i];
				mx_d[i]=beg[i]-1; 
			}else if (beg[i]-1>mx_d2[i]) mx_d2[i]=beg[i]-1;
			
			
			if (n-en[i]>mx_d[i]){
				mx_d2[i]=mx_d[i];
				mx_d[i]=n-en[i]; 
			}else if (n-en[i]>mx_d2[i]) mx_d2[i]=n-en[i];
		}
		
		int l=0,r=n;
		int ans=r;
		while (l<=r){
			int mid=(l+r)/2;
			
			if (check(mid)){
				ans=mid;
				r=mid-1;
			}else l=mid+1;
		}
		
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Jasper08 (赞：1)

枚举每种颜色跳跃的最大距离 $max$ 和次大距离 $max'$，若增加一块颜色为 $i$ 的木板，则该种颜色的最大距离变为 $\max\left\{\left\lfloor \dfrac{max}{2} \right\rfloor,max'\right\}$。取最小值即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 2e5+10;

int t, n, k, ans, c[N];
int last[N], Max[N][2];

int main() {
	scanf("%d", &t);
	while (t -- ) {
		scanf("%d%d", &n, &k); ans = (int)1e9;
		for (int i = 1; i <= k; ++i) last[i] = 0, Max[i][0] = Max[i][1] = -1;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &c[i]);
			if (i-last[c[i]]-1 >= Max[c[i]][0]) Max[c[i]][1] = Max[c[i]][0], Max[c[i]][0] = i-last[c[i]]-1;
			else if (i-last[c[i]]-1 > Max[c[i]][1]) Max[c[i]][1] = i-last[c[i]]-1;
			last[c[i]] = i;
		}
		
		for (int i = 1; i <= k; ++i) {
			if (n-last[i] >= Max[i][0]) Max[i][1] = Max[i][0], Max[i][0] = n-last[i];
			else if (n-last[i] > Max[i][1]) Max[i][1] = n-last[i];
			if (Max[i][0] == -1) continue;
			ans = min(ans, max(Max[i][0]/2, Max[i][1])); 
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：ENJOY_AK (赞：0)

## 思路

注意看，只有一次改变颜色，不要再苦苦打二分了！

贪心地去求答案，对于每一种颜色记录两个点之间的距离的最大值和次大值，然后把最大值的那段区间的中点颜色更改成当前颜色。令最大值为 $maxx$，次大值为 $max2$。则所有 $\max(\lfloor \dfrac{maxx}{2} \rfloor,max2)$ 的 $\min$ 即为最优解。

记得处理到 $n+1$ 号点的距离，该算法的时间复杂度为 $O(n)$。

## 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define endl "\n"

const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll t, m, n, a[N], maxx[N], pre[N], max2[N], ans;
int main() {
    cin>>t;
    for(int j=1;j<=t;++j) {
        ans=INF;
        cin>>n>>m;
        for(int i=1;i<=m;++i)    pre[i]=maxx[i]=max2[i]=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            if(i-pre[a[i]]-1>maxx[a[i]]){
                max2[a[i]]=maxx[a[i]];
                maxx[a[i]]=i-pre[a[i]]-1;
            }
            else
                if(i-pre[a[i]]-1>max2[a[i]])
                    max2[a[i]]=i-pre[a[i]] - 1;
            pre[a[i]]=i;
        }
        for(int i=1;i<=m;++i){
            if(n-pre[i]>maxx[i]){
                max2[i]=maxx[i];
                maxx[i]=n-pre[i];
            }
            else
                if(n-pre[i]>max2[i])max2[i]=n-pre[i];
            ans=min(max(maxx[i] / 2, max2[i]), ans);
        }
        cout<<ans<<endl;
    }
}

```

---

## 作者：Che_001 (赞：0)

## 题意

给定一个序列，从 $0$ 号点开始往后跳，每次只能跳到与前一个点颜色相同的点，有一次改变颜色的机会，求路径上最长的一次跳跃的距离的最小值。

## Solution

赛时一眼二分，然后写着写着发现根本没必要二分，因为只有一次改变颜色的机会。

贪心地去求答案，对于每一种颜色记录两个点之间的距离的最大值和次大值，然后把最大值的那段区间的中点颜色更改成当前颜色。令最大值为 $max$，次大值为 $sec$。则 $\min(\lfloor \dfrac{max}{2} \rfloor,sec)$ 即为最优解。

记得处理到终点即第 $n+1$ 号点的距离。

时间复杂度为 $\mathcal{O}(n)$。

## code

```cpp
#include<bits/stdc++.h>
inline int read()
{
	long long res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
int val[200010];
int ans[200010][3];
void solve()
{
	int n=read(),k=read(),res=0x3f3f3f3f;
	memset(ans,0,sizeof ans);
	for(int i=1;i<=n;i++)
		val[i]=read();
	for(int i=1;i<=n;i++)
	{
		if(i-ans[val[i]][0]>=ans[val[i]][1])
			std::swap(ans[val[i]][1],ans[val[i]][2]),ans[val[i]][1]=i-ans[val[i]][0];
		else if(i-ans[val[i]][0]>=ans[val[i]][2])
			ans[val[i]][2]=i-ans[val[i]][0];
		ans[val[i]][0]=i;
	}
	for(int i=1;i<=k;i++)
	{
		if(n+1-ans[i][0]>=ans[i][1])
			std::swap(ans[i][1],ans[i][2]),ans[i][1]=n+1-ans[i][0];
		else if(n+1-ans[i][0]>=ans[i][2])
			ans[i][2]=n+1-ans[i][0];
		ans[i][1]--,ans[i][2]--;
	//	std::cout<<i<<" "<<ans[i][0]<<" "<<ans[i][1]<<" "<<ans[i][2]<<std::endl;
		res=std::min(res,std::max((int)(ans[i][1]/2),ans[i][2]));
	}
	printf("%d\n",res);
	return ;
}
int main(int argc,const char *argv[])
{
	int T=read();
	while(T--)
		solve();
	return 0;
}
```


---

## 作者：Meteor_ (赞：0)

# CF1848B Vika and the Bridge 题解

## 题目大意

~~给个题目传送门吧，感觉题意已经很清楚了~~

[题目传送门](https://www.luogu.com.cn/problem/CF1848B)

## 分析

（~~我不会告诉你我第一眼看过去是二分~~）

因为我们只能改一块木板的颜色，所以可以考虑贪心。大概算了下复杂度，也没有问题。

## 题解

我们要去求每种颜色最大距离的最小值，那我们可以先去求每种颜色的最大值。

求完以后，直接将每种颜色的最大值减半，就是我们的最远距离 $\dots$ 了吗？

并不是，因为有可能最大值减半后，这个新的值比原来的次大值小，那么最远距离就成了次大值。所以我们一开始也要求出每种颜色的次大值。最后将每种颜色最大值的一半与次大值取较大的一个，也就是这个颜色的最远距离，再取所有颜色的最远距离的最小值，就是答案啦。

~~好多最值，自己差点绕进去 qwq~~

时间复杂度： $O(n + m)$

## 代码

```cpp
#include <bits/stdc++.h>
#define M 200005

using namespace std;

int T, m, n, c[M], maxn[M], pre[M], ci_maxn[M], ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    for(int t = 1; t <= T; ++ t) {
        ans = INT_MAX;
        cin >> n >> m;
        for(int i = 1; i <= m; ++ i)    
            pre[i] = maxn[i] = ci_maxn[i] = 0;
        for(int i = 1; i <= n; ++ i) {
            cin >> c[i];
            if(i - pre[c[i]] - 1 > maxn[c[i]]) {
                ci_maxn[c[i]] = maxn[c[i]];
                maxn[c[i]] = i - pre[c[i]] - 1;
            }
            else
                if(i - pre[c[i]] - 1 > ci_maxn[c[i]])
                    ci_maxn[c[i]] = i - pre[c[i]] - 1;
            pre[c[i]] = i;
        }
        for(int i = 1; i <= m; ++ i) {
            if(n - pre[i] > maxn[i]) {
                ci_maxn[i] = maxn[i];
                maxn[i] = n - pre[i];
            }
            else
                if(n - pre[i] > ci_maxn[i])
                    ci_maxn[i] = n - pre[i];
            ans = min(max(maxn[i] / 2, ci_maxn[i]), ans);
        }
        cout << ans << '\n';
    }
}
```

---

## 作者：Leaper_lyc (赞：0)

## 题目简意
有一座桥，桥上由多个木板组成，木板上有颜色，可能相同可能不同，可以修改一块木板的颜色（不是非要改），求同种颜色木板之间**最大**距离的**最小值**。

## 分析
假设我们已经知道了同种木板之间的最大距离 $x$，和次大距离 $y$，那么显然把最大距离中间的一块木板改变颜色就可以最小化答案，接下来的最大距离就是：
$
\max\{\lfloor {x\over 2} \rfloor,y\}
$。

那我们只要把最大值于次大值给预处理出来就行了。

于是就有了代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

#define maxn 1000005

int semax[maxn], frmax[maxn];
// 次大值semax,最大值frmax.
int last[maxn];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t, n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        // 这边有点类似于次短路的求法
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            int dist = i - last[x] - 1;
            if (dist > frmax[x]) {
                semax[x] = frmax[x];
                frmax[x] = dist;
            } else if (dist > semax[x]) {
                semax[x] = dist;
            }
            last[x] = i;
        }
        for (int i = 1; i <= m; i++) {
            int dist = n - last[i];
            if (dist > frmax[i]) {
                semax[i] = frmax[i];
                frmax[i] = dist;
            } else if (dist > semax[i]) {
                semax[i] = dist;
            }
        }
        int ans = (1 << 30);
        for (int i = 1; i <= m; i++) {
            ans = min(ans, max(semax[i], frmax[i] >> 1));
        }
        cout << ans << '\n';
        for (int i = 1; i <= m; i++) {
            last[i] = semax[i] = frmax[i] = 0;
        }
    }
}
```

---

## 作者：sz_jinzikai (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1848B) &[CF 传送门](https://codeforces.com/problemset/problem/1848/B)
# 思路
首先，我们设两块颜色都为 $i$ 的木板间的距离的最大值为 $first_i$，次大值为 $second_i$，我们可以在这两块距离为 $first_i$ 的木板的正中间改变一块木板的颜色，这样就能让 $first_i$ 分成 $\lfloor\frac{first_i}{2}\rfloor$ 和 $\lceil\frac{first_i}{2}\rceil$ 两部分，当前颜色的最大间隔距离就会变成 $\max(\lfloor\frac{first_i}{2}\rfloor,second_i)$。最后，我们再将这几种颜色的最大间隔距离取一个最小值就得到了答案
# 代码
```cpp
# include <bits/stdc++.h> //万能头 
using namespace std;
int t, n, k, a[200005], minx, first[200005], second[200005], last[200005], x; //定义变量，作用看下面：
/*
t：数据组数
n：木板数量
k：颜色数量
a：每块木板上的颜色
minx：答案
first：表示当前颜色的最大间隔
second：表示当前颜色的次大间隔
last：记录上一个同一颜色的位置
x：记录当前节点和上一个同一颜色节点的距离
*/
int main () { //定义主函数
	cin >> t; //输入数据组数
	while (t --) { //多组数据的经典写法
		cin >> n >> k; //输入木板数量和颜色数量
		minx = 1e9; //给答案赋一个最大值
		for (int i = 1; i <= k; ++ i)
			last[i] = first[i] = second[i] = 0; //多组数据别忘了清空数组
		for (int i = 1; i <= n; ++ i) {
			cin >> a[i]; //输入每块木板上的颜色
			x = i - last[a[i]] - 1; //记算当前节点和上一个同一颜色节点的距离
			if (x > first[a[i]]) { //如果当前距离大于当前最大值
				second[a[i]] = first[a[i]]; //更新次大值
				first[a[i]] = x; // 更新最大值，顺序不能反
			} else if (x > second[a[i]]) //如果当前距离大于当前最次值
				second[a[i]] = x; //更新次大值
			last[a[i]] = i; //更新上一个同一颜色的位置
		}
		for (int i = 1; i <= k; ++ i) { //最后还有最重要的一步——走出桥
			x = n - last[i]; //记算桥对岸和最后一个这一颜色的节点的距离
			if (x > first[i]) { //如果当前距离大于当前最大值
				second[i] = first[i]; //更新次大值
				first[i] = x; // 更新最大值，顺序不能反
			} else if (x > second[i]) //如果当前距离大于当前最次值
				second[i] = x; //更新次大值
		}
		for (int i = 1; i <= k; ++ i)
			minx = min (minx, max (first[i] / 2, second[i])); //更新当前答案
		cout << minx << '\n'; //输出答案
	}
	return 0; //结束程序
}
```

---

## 作者：xiazha (赞：0)

### 思路
推理题。枚举每个出现过的颜色，最小化当前颜色的最大跳跃次数，先将当前颜色的第一大的间距 $maxn$ 和第二大间距 $maxn1$ 求出来，而修改其中一个木板的长度显然是将最大间距的那一段的中点修改成当前枚举的颜色，这样间距就变成了 $maxn\div 2$，但由于除以了 $2$，那么 $maxn\div 2$ 就不一定是最大的了，所以当前枚举的颜色最大跳跃次数是 $\max(maxn\div 2,maxn1)$。然后答案就是取每个颜色需要跳跃次数中的最小值。



------------


### 代码
```
#include<bits/stdc++.h>
using namespace std;
int tt,n,k,c[200002],b[200002],t[200002],cnt,minn;
vector<int> g[200002];
int main()
{
	cin>>tt;
	for(int w=1;w<=tt;w++)
	{
		cnt=0,minn=2100000000;
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++) g[i].clear();
		for(int i=1;i<=n;i++) 
		{
			scanf("%d",&c[i]);
			g[c[i]].push_back(i);
			if(t[c[i]]!=w) t[c[i]]=w,b[++cnt]=c[i];
		}
		if(cnt==1)
		{
			cout<<"0\n";
			continue;
		}
		for(int i=1;i<=cnt;i++)
		{
			int p=0,maxn=0,maxn1=0;
			for(int j=0;j<g[b[i]].size();j++)
			{
				int l=g[b[i]][j];
				int c=l-p-1;p=l;
				if(c>maxn) maxn1=maxn,maxn=c;
				else if(c>maxn1) maxn1=c;
			}
			int c=n-p;
			if(c>maxn) maxn1=maxn,maxn=c;
			else if(c>maxn1) maxn1=c;
			minn=min(minn,max(maxn/2,maxn1));
		}
		cout<<minn<<"\n";
	}
	return 0;
}
```


---

