# The Union of k-Segments

## 题目描述

```cpp
给你 n 条线段，再给你一个整数 k。如果一个点至
少被 k 条线段覆盖，那么这个点是符合条件的，如果符合条件的点可以不间断的连起来组成
一条条的线段（注：线段中间是不能有断开的），并且要求符合条件的线段数越少越好。 （注：
只有一点也可以）。 换句话说就是让你将覆盖 k 次及 k 次以上所有的区间都找出来，如果两
个区间能够合并，那么输出他们合并的结果，例如：k=1,区间[0-3],[3-5]可以合并成[0-5]，但
是 k=1,区间[0-3][4-5]，是不能合并的，因为他们两个区间没有重叠部分。

## 样例 #1

### 输入

```
3 2
0 5
-3 2
3 8
```

### 输出

```
2
0 2
3 5
```

## 样例 #2

### 输入

```
3 2
0 5
-3 3
3 8
```

### 输出

```
1
0 5
```

# 题解

## 作者：He_Ren (赞：5)

坐标的范围很大，答案又只和坐标的相对大小有关，所以可以离散化然后差分。贪心统计答案

但是发现出了问题，因为差分会把$[1,2]$和$[3,4]$算作$[1,4]$，但实际区间$(1,2)$是没有被覆盖的。有两种方法

## 方法1

差分时分开计算线段左右端点，在当前点先计算左端点，统计答案后再计算右端点，再统计答案

```cpp
const int MAXN = 1e6 + 5;
const int MAXP = MAXN*2;
using namespace std;
 
struct Seg
{
	int l,r;
}a[MAXN],out[MAXN];
int ans=0;
 
int tmp[MAXP],cnt=0;
 
int b[MAXP],c[MAXP];
 
int main(void)
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		a[i] = (Seg){l,r};
		tmp[++cnt]=l; tmp[++cnt]=r;
	}
	
	sort(tmp+1,tmp+cnt+1);
	cnt = unique(tmp+1,tmp+cnt+1)-tmp-1;
	for(int i=1; i<=n; ++i)
	{
		a[i].l = lower_bound(tmp+1,tmp+cnt+1,a[i].l)-tmp;
		a[i].r = lower_bound(tmp+1,tmp+cnt+1,a[i].r)-tmp;
	}
	
	for(int i=1; i<=n; ++i)
	{
		++b[a[i].l];
		--c[a[i].r];
	}
	
	int tot=0;
	bool flag=0;
	for(int i=1; i<=cnt; ++i)
	{
		tot+=b[i];
		if(tot>=m)
		{
			if(!flag)
			{
				out[++ans].l=i;
				flag=1;
			}
		}
		tot+=c[i];
		if(tot<m)
		{
			if(flag)
			{
				out[ans].r=i;
				flag=0;
			}
		}
	}
	printf("%d\n",ans);
	for(int i=1; i<=ans; ++i)
		printf("%d %d\n",tmp[out[i].l],tmp[out[i].r]);
	return 0;
}
```

## 方法2

将每条线段的两端各$0.5$的未被覆盖的部分加入离散化，比如，在计算线段$[1,2]$时，实际上把$0.5,1,2,2.5$加入离散化，然后正常差分就行了。在实现中，将坐标乘$2$，就可以避免小数问题了

```cpp
using namespace std;
const int MAXN = 1e6 + 5;
const int MAXP = MAXN*4;
 
struct Seg
{
	int l,r;
}a[MAXN],ans[MAXN];
int acnt=0;
 
int dsc[MAXP],cnt=0;
int b[MAXP];
 
int main(void)
{
	int n,d;
	scanf("%d%d",&n,&d);
	for(int i=1; i<=n; ++i) scanf("%d%d",&a[i].l,&a[i].r);
	
	for(int i=1; i<=n; ++i)
	{
		a[i].l*=2; a[i].r*=2;
		dsc[++cnt]=a[i].l; dsc[++cnt]=a[i].r;
		dsc[++cnt]=a[i].l-1; dsc[++cnt]=a[i].r+1;
	}
	sort(dsc+1,dsc+cnt+1);
	cnt = unique(dsc+1,dsc+cnt+1)-dsc-1;
	for(int i=1; i<=n; ++i)
		a[i].l = lower_bound(dsc+1,dsc+cnt+1,a[i].l)-dsc,
		a[i].r = lower_bound(dsc+1,dsc+cnt+1,a[i].r)-dsc;
	
	for(int i=1; i<=n; ++i)
		++b[a[i].l], --b[a[i].r+1];
	
	int now=0;
	bool flag=0;
	for(int i=1; i<=cnt; ++i)
	{
		now+=b[i];
		if(now>=d)
		{
			if(!flag) ans[++acnt].l = dsc[i]/2;
			flag=1;
		}
		if(now<d)
		{
			if(flag) ans[acnt].r = dsc[i-1]/2;
			flag=0;
		}
	}
	printf("%d\n",acnt);
	for(int i=1; i<=acnt; ++i) printf("%d %d\n",ans[i].l,ans[i].r);
	return 0;
}
```


---

## 作者：StranGePants (赞：4)

## Description

给定 $n$ 条线段，符合被至少 $k$ 条线段的点合法，求最少的线段集使得包含所有合法点，并且不包含其他点。


---
## Solution
本题正解是 $\Theta(n\log n)$ 的差分，这里介绍一种常数略大的 $\Theta(n\log n)$ 做法。

考虑一条线段对于一个点何时做贡献，如图（样例 1）
![](https://cdn.luogu.com.cn/upload/image_hosting/npff3c2i.png)
设当前点为 $a$，其右边有 $y$ 个右端点，$x$ 个左端点。

右端点在其右边的可能会包含它，但是如果左端点也在它右边就无法覆盖它，两者数量相减即为它被多少个区间包含。

![](https://cdn.luogu.com.cn/upload/image_hosting/8cdfnmkg.png)

左，右端点比 $a$ 大即为值比它大，可以用离散化+树状数组做到 $\Theta(n\log n)$ 维护。

因为一段答案线段必定结束于 $n$ 条线段中某一条线段的右端点，所以离散化后的答案正确。

如果一个点既处在一条线段的右端点，又存在于一条线段的左端点，此时他是被两条线段包含的，所以统计答案时，右端点的范围为 $[a,cnt]$,左端点的范围为 $[a+1,cnt]$($cnt$为离散化后的元素个数)。

我们发现当出现上图绿色和蓝色线段中间有 $(2,3)$ 的空缺时，不好直接维护中间的个数，所以我们把离散化后的元素乘 2 再减 1，就可以保证空缺的答案正确，且不会与上一个点以及下一个点一起被记入一条答案线段。

![](https://cdn.luogu.com.cn/upload/image_hosting/qf3mkboq.png)

此时新的答案线段的左端点为 5。

## Code:

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int n,k,b[4000005],m,cnt;
int vis[4000005],BIT1[4000005],BIT2[4000005],tot=1,Max=-1;
const int INF=0x3f3f3f3f;
int lowbit(int x)
{
	return x&-x;
}
void update1(int x,int k)
{
	for(int i=x;i<=cnt*2-1;i+=lowbit(i))
	{
		BIT1[i]+=k;
	}
}
int Ans1(int x)//统计左节点
{
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		ans+=BIT1[i];
	}
	return ans;
}
void update2(int x,int k)
{
	for(int i=x;i<=cnt*2-1;i+=lowbit(i))
	{
		BIT2[i]+=k;
	}
}
int Ans2(int x)//统计右节点
{
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		ans+=BIT2[i];
	}
	return ans;
}
struct ren{
	int l,r;
}a[4000005],Ans[4000005];
bool cmp(ren x,ren y)
{
	return x.l==y.l?x.r<y.r:x.l<y.l;
}
int main()
{
	memset(vis,-INF,sizeof(vis));
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].l,&a[i].r);
		b[++m]=a[i].l;
		b[++m]=a[i].r;
	}
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+m);
	cnt=unique(b+1,b+1+m)-b-1;
	for(int i=1;i<=n;i++)
	{
		int x=lower_bound(b+1,b+1+cnt,a[i].l)-b,y=lower_bound(b+1,b+1+cnt,a[i].r)-b;
		x=x*2-1;
		y=y*2-1;
		vis[x]=a[i].l;
		vis[y]=a[i].r;
		a[i].l=x;
		a[i].r=y;
		Max=max(Max,a[i].r);
		update1(a[i].l,1);
		update2(a[i].r,1);
	}
	for(int i=1;i<=cnt*2-1;i++)
	{
		Ans[i].l=Ans[i].r=-INF;
	}
	for(int i=a[1].l;i<=Max;i++)
	{
		int x=Ans2(cnt*2-1)-Ans2(i-1),y=Ans1(cnt*2-1)-Ans1(i);
		if(x-y>=k&&vis[i]!=-INF)
		{
			if(Ans[tot].l==-INF){
				Ans[tot].l=vis[i];
				Ans[tot].r=vis[i];
				while(Ans2(cnt*2-1)-Ans2(i-1)-Ans1(cnt*2-1)+Ans1(i)>=k&&Max)
				{
					if(vis[i]!=-INF)
					{
						Ans[tot].r=vis[i];
					}
					i++;
				}
				i--;
				tot++;
			}
		}
	}
	tot--;//多加了一次，固减去
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)
	{
		printf("%d %d\n",Ans[i].l,Ans[i].r);
	}
	return 0;
}//实际上比差分只慢100ms左右
```



---

## 作者：xunhuanyihao (赞：3)

### CF612D The Union of k-Segments
一道练习离散化的好题。本题解适合离散化并不熟练的同学观看。
#### Step1：暴力 + 差分
首先我们可以想到一个非常暴力的解法：对于每条线段，采用差分思想，差分数组左端点加一，（右端点 $+1$ ）减一，然后对每个坐标 $\ge -1 \times 10^9,\le 1 \times 10^9$ 的点，给差分数组做一遍前缀和判断被覆盖的区间是否有 $k$ 个，如果有就加入到答案中。时间复杂度 $O(n + V)$，$V$ 为线段值域。
#### Step2：差分 + 优化
我们发现，差分数组的前缀和只会在每个左端点，右端点加一处改变，所以我们可以枚举每个左端点和右端点加一，并计算前缀和，看看是否 $\ge k$，如果是则加入答案，这题就做完了。而在具体实现中我们可以将每个端点排序，方便统计答案。
#### Step3：离散化
我们发现如果只这样做，差分数组会爆（坐标最大为 $1 \times 10^9$ 且会是负数），解决方法就是离散化，可以使用 map，也可以将每个点的坐标改成他在端点排序后的排名，再进行差分运算。在实现中，我们发现这样的话，右端点加一就很难直接用差分加了，我们可以这样考虑：差分中直接让右端点减一，当枚举到这个右端点时，如果做完前缀和发现被覆盖个数小于 $k$ 了，说明这个点是最后一个满足的，往后 $+1$ 就不满足了，直接将这个点当成答案线段的右端点即可。
时间复杂度 $O(n \log n)$。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
int n, k, p[N << 1], cnt, c1[N << 1], c2[N << 1], tot;
pii a[N], ans[N];
int main() {    
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        int l, r; scanf("%d%d", &l, &r);
        p[++cnt] = l, p[++cnt] = r;
        a[i] = {l, r};
    }
    sort(p + 1, p + cnt + 1);
    for (int i = 1; i <= n; i++) {
        auto &[l, r] = a[i];
        l = lower_bound(p + 1, p + cnt + 1, l) - p;
        r = lower_bound(p + 1, p + cnt + 1, r) - p;
    }
    for (int i = 1; i <= n; i++) {
        c1[a[i].first]++;
        c2[a[i].second]--;
    }
    int now = 0;
    bool flag = false;
    for (int i = 1; i <= cnt; i++) {
        now += c1[i];
        if (now >= k && !flag) ans[++tot].first = i, flag = true;
        now += c2[i];
        if (now < k && flag) ans[tot].second = i, flag = false;
    }
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++) printf("%d %d\n", p[ans[i].first], p[ans[i].second]);
    return 0;
}
```

---

## 作者：djh233 (赞：3)

**题意：**

给定 $n$ 条在数轴上线段，第 $i$ 条线段起点为 $l_i$ ，终点为 $r_i$ ，问所有被不少于 $k$ 条线段覆盖的区域。

**数据范围：** $1\le k\le n\le 10^6 , -10^9\le l\le r\le 10^9$ 。

**做法：**

统计出所有点的位置并由小到大排序，使用map套一个vector储存每个点被当过多少次起点和终点的信息，然后从左到右遍历每一个线段的端点。

对于每一个端点：
- 先遍历一遍它作为起点的信息，然后统计到目前为止没有匹配终点的起点的个数 $tot$ ，如果统计之前 $tot<k$ 并且统计之后 $tot\ge k$ ，那么把 $lst$ 设为该点的位置。
- 再遍历一遍它作为终点的信息，然后更改到目前为止没有匹配终点的起点的个数 $tot$，如果统计之前 $tot\ge k$ 并且统计之后 $tot<k$ ，那么说明从 $lst$ 到当前位置 $pos$ 的所有点被至少 $k$ 条线段覆盖，那么就直接将其存到答案里。

这题还有很多细节需要注意，我就在一个细节上卡了很久。如果有多个重复的点，那么只统计一次该点对 $tot$ 的影响即可，若多次统计会导致 $tot$ 算错，然后就锅了。

**时间复杂度：** $O(n\log_2n)$ 。

$Code:$

```cpp

#include <bits/stdc++.h>
#define pii pair<int,int>

using namespace std;

map<int,vector<int> > mmp;
int point[1000010];
pii ans[1000010];

void solve()
{
    int n,k,cnt=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        mmp[l].push_back(1); mmp[r].push_back(2);
        point[++cnt]=l; point[++cnt]=r;
    }
    sort(point+1,point+cnt+1);

    int tot=0,lst=-1e9;
    int jishu=0;
    for(int i=1;i<=cnt;i++)
    {
        if(i!=1 && point[i-1]==point[i]) continue;

        int lst_tot=tot;
        int dian=point[i];

        for(int j=0;j<mmp[dian].size();j++)
            if(mmp[dian][j]==1) tot++;
        
        if(lst_tot<k && tot>=k) lst=dian;
        lst_tot=tot;

        for(int j=0;j<mmp[dian].size();j++)
            if(mmp[dian][j]==2) tot--;

        if(lst_tot>=k && tot<k)
        {
            ans[++jishu].first=lst;
            ans[jishu].second=dian;
        }
    }

    printf("%d\n",jishu);
    for(int i=1;i<=jishu;i++) printf("%d %d\n",ans[i].first,ans[i].second);
}

int main()
{
    solve();
    return 0;
}

```


---

## 作者：detect (赞：2)

还没人写题解，那我来一波~

```
给你 n 条线段，再给你一个整数 k。如果一个点至
少被 k 条线段覆盖，那么这个点是符合条件的，如果符合条件的点可以不间断的连起来组成
一条条的线段（注：线段中间是不能有断开的），并且要求符合条件的线段数越少越好。 （注：
只有一点也可以）。 换句话说就是让你将覆盖 k 次及 k 次以上所有的区间都找出来，如果两
个区间能够合并，那么输出他们合并的结果，例如：k=1,区间[0-3],[3-5]可以合并成[0-5]，但
是 k=1,区间[0-3][4-5]，是不能合并的，因为他们两个区间没有重叠部分。
【输入格式】
第一行输入整数 n 和 k（1≤k≤n≤10^6），分别表示 n 条线段和 k 值。
接下来 n 行，每行输入整数 li，ri（-10^9≤li≤ri≤10^9），分别表示第 i 条线段的起点和
终点。这些线段可以相互重叠和交叉。
【输出格式】
第一行输入整数 m ，表示最小的区间数。
接下来 m 行，每行输入整数 aj，bj（aj≤bj），分别表示第 j 段区间的起始和末尾。输出
必须按照从小到大（从左到右）的顺序。
【输入输出样例】
样例输入 1 1 样例输入 2 2
3 2
0 5
-3 2
3 8
3 2
0 5
-3 3
3 8
样例输出 1 1 样例输出 2 2
2
0 2
3 5
1
0 5

```


------------

第一眼差分，但数据范围到了1e9，不好处理，因为段与段之间没用，可以压缩，使用扫描线。

具体做法：用vector存储左右端位置，排序，然后扫一遍，如果是左端点则cnt++，如果是右端点则cnt--，如果cnt==k就用ans数组保存答案，因为只要次数到了k，且在次数再到k之前必定>=k。

更多细节看代码：

------------
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int getint(){//必须用读优
int summ=0,f=1;
char ch;
for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
if(ch=='-')
{
    f=-1;
    ch=getchar();
}
for(;isdigit(ch);ch=getchar())
    summ=(summ<<3)+(summ<<1)+ch-48;
return summ*f;
}
int n,m,k;
vector < pair<int,int > > v;//pair自动按一二关键字顺序排序
vector < int > ans;//记录答案
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		x=getint();
		y=getint();
		v.push_back(make_pair(x,0));
		v.push_back(make_pair(y,1));
	}
	sort(v.begin(),v.end());
	int cnt=0;
	for(int i=0;i<v.size();i++)
	{
		if(v[i].second==0)
		{
			cnt++;
			if(cnt==k) ans.push_back(v[i].first);//刚刚到
		}		
		else{
			if(cnt==k) ans.push_back(v[i].first);//退回k-1
			cnt--;
		}
	}
	cout<<(ans.size())/2<<endl;
	for(int i=0;i<(ans.size())/2;i++)
	{
		cout<<ans[i*2]<<" "<<ans[i*2+1]<<endl;//按顺序输出，自动解决合并问题
	}
	return 0;
} 
```


---

## 作者：hxhhxh (赞：1)

## 大意

给定数轴上的 $ n $ 条线段和一个整数 $ k $ ，求所有被至少 $ k $ 条线段同时覆盖的所有极长的线段。

## 思路

将 $ 2n $ 个端点从左到右排序，然后从左到右扫一遍，途中需要记录当前层数。

每遇到一个左端点，将当前层数`++`；如果正好加到 $ k $ 层，将它记录为新的极长的线段的左端点。

每遇到一个右端点，将当前层数`--`；如果减之前正好只剩 $ k $ 层，新增一条左端点为记录值，右端点为当前值的答案线段。

注意：同位置先处理左端点。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
queue<pair<int,int> > ans;
pair<int,int>a[2000006];
int main(){
	cin>>n>>k;
	for (int i=1,j,k;i<=n;i++){
		scanf("%d %d",&j,&k);
		a[i*2-1]=(pair<int,int>){j,0};
		a[i*2]=(pair<int,int>){k,1};
	}
	sort(a+1,a+n*2+1);
	for(int i=1,l=0;i<=n*2;i++){
		pair<int,int>nw=a[i];
		if(nw.second==1){
			if(t==k) ans.push((pair<int,int>){l,nw.first});
			t--;
		}
		else{
			t++;
			if(t==k) l=nw.first;
		}
	}
	cout<<ans.size()<<endl;
	while(!ans.empty()){
		printf("%d %d\n",ans.front().first,ans.front().second);
		ans.pop();
	}
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[The Union of k-Segments](https://www.luogu.com.cn/problem/CF612D)
## 分析
我们用一个结构体储存两个参数：位置与是否为区间末。然后对于每个区间，直接存储首尾两个节点就好了，然后按照位置排序，再从前往后枚举这 $2 \times n$ 个点，并定义一个 $\texttt{step}$ 表示当前层数，如果为头，则 $\texttt{step} $ 增加 $1$；如果为末，则 $\texttt{step}$ 减少 $1$，同时定义一个 $l$ 表示如果当前 $\texttt{step}$ 刚好等于 $k$ 的时候，这个区间的左端点在哪里，然后存储答案。

然后就没了，复杂度是排序的 $n \log n$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int id;
	int flag;
}a[2000010];
int tot;
int n,k;
bool cmp(node tx,node ty)
{
	if(tx.id!=ty.id)
		return tx.id<ty.id;
	return tx.flag<ty.flag;
}
node ans[2000010];
int num;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int t1,t2;
		scanf("%d%d",&t1,&t2);
		a[++tot].id=t1;
		a[++tot].id=t2;
		a[tot].flag=1;
	}
	n*=2;
	sort(a+1,a+n+1,cmp);
	int step=0,l=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].flag==0)
		{
			step++;
			if(step==k)l=a[i].id;
		}
		else
		{
			if(step==k)ans[++num]=(node){l,a[i].id};
			step--;
		}
	}
	printf("%d\n",num);
	for(int i=1;i<=num;i++)
		printf("%d %d\n",ans[i].id,ans[i].flag);
	return 0;
}
```


---

## 作者：linyihdfj (赞：0)

## D.The Union of k-Segments ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16419311.html)
### 题目描述： ###
[原题面](https://codeforces.com/contest/612/problem/D)
### 题目分析： ###
我们发现：只要我们知道了每个位置被覆盖了多少次那么从前到后扫一遍就能得到最后的答案。

这其实就相当于多次修改一次查询，那么使用差分与前缀和就能 $O(n)$ 的时间内维护这些地方的信息，要注意的是因为区间范围很大所以需要进行离散化后操作。

但是这样就会出现一个问题，假设 $a_i$ 被覆盖了 $k$ 次，$a_{i+1}$ 也被覆盖了 $k$ 次，但是不代表 $[i,i+1]$ 被覆盖了 $k$ 次。这样也很好办那就在两个点之间插入一个新点，可以将位置设为 $\frac{l+r}{2}$，这样只有这个点被覆盖了 $k$ 次扫的时候才会将下一个点统计入当前的区间，所以就很好地解决了这个问题。

因为浮点数不好处理，所以可以考虑将位置全部乘二，这样最后再除回来，因为被临时加入的点不可能成为我们答案区间的左端点或右端点，所以不用考虑其他情况。
### 代码详解： ###

```
#include<bits/stdc++.h>
using namespace std;
const long long MAXN = 2e6+5;
const long long INF = 1e18+5;
struct node{
	long long l,r;
	node(){}
	node(long long _l,long long _r){
		l = _l,r = _r;
	}
}a[MAXN];
long long b[4 * MAXN],cnt,sum[4 * MAXN];
vector<node> ans;
int main(){
	long long n,k;
	scanf("%lld%lld",&n,&k);
	for(long long i=1; i<=n; i++){
		scanf("%lld%lld",&a[i].l,&a[i].r);
		b[++cnt] = a[i].l * 2;
		b[++cnt] = a[i].r * 2;
		b[++cnt] = a[i].l * 2 - 1;
		b[++cnt] = a[i].r * 2 + 1;
	}
	sort(b+1,b+cnt+1);
	long long sz_b = unique(b+1,b+cnt+1) - b - 1;
	for(int i=1; i<=n; i++){
		a[i].l = lower_bound(b+1,b+sz_b+1,a[i].l * 2) - b;
		a[i].r = lower_bound(b+1,b+sz_b+1,a[i].r * 2) - b;
	}
	for(long long i=1; i<=n; i++){
		sum[a[i].l] ++;
		sum[a[i].r + 1] --;   //因为这个值肯定是有就是 a[i].r + 0.5 的位置，所以直接加没问题 
	}
	for(long long i=1; i<=sz_b; i++){
		sum[i] += sum[i-1];
	}
	long long l= -INF,r = -INF;
	for(long long i=1; i<=sz_b; i++){
		if(sum[i] < k){
			if(l!=-INF && r!=-INF)
				ans.push_back(node(l,r));
			l = -INF;
			r = -INF;
		}
		else if(sum[i] >= k){
			if(l == -INF){
				l = b[i]/2;  //先乘 2 这里还原回去要除二 
			}
			r = b[i]/2;
		}
	}
	cout<<ans.size()<<endl;
	for(long long i = 0; i<ans.size(); i++){
		printf("%lld %lld\n",ans[i].l,ans[i].r);
	}
	return 0;
}

```

需要注意数组大小开四倍，因为一个区间对应拆出来了四个点

---

## 作者：寒冰大大 (赞：0)

题解貌似没有用我这种方式来搞差分的，来交一波

这道题的难度就是平常我们处理[1,2]与[3,4]+1的时候，得到的结果一般要求是[1,4]都加上1，但是这个显然不行，解决的办法就是每个点分成两份，分后的点前面那个处理+差分后面处理-差分

比如 现在[1,2]+1我们的处理的方法就是

先把每个点分成两份

1 1' 2 2'

然后1这个点+1，2'这个点-1
同时这样处理还有个好处，比如我们让4号点+1，这样4 4'分别会+1和-1，扫描的过程中直接被抵消了（相当于没做，但是你不能忽略，下面说原因）

1 3 
4 5
2 4


比如这里的4如果忽略的话，那么程序就会根据差分数组得出4只被覆盖一次。

这点处理完了后，就可以按照一般差分的思路来做了


```cpp
#include<touwenjian.h>

using namespace std;

int p[4002000];
int c[8000200];
int tot,n,m,cnt;

struct que{
    int l,r;
}q[2002000];

que ans[2002000];

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int i,j;
    for(i=1;i<=n;i++) cin>>q[i].l>>q[i].r,p[++tot]=q[i].l,p[++tot]=q[i].r;
    sort(p+1,p+tot+1);
    tot=unique(p+1,p+tot+1)-p-1;
    for(i=1;i<=n;i++)
    {
        int l,r;
        l=lower_bound(p+1,p+tot+1,q[i].l)-p;
        r=lower_bound(p+1,p+tot+1,q[i].r)-p;
        l=l*2-1;
        r=r*2;
        c[l]++; c[r]--;
    }
    int st,ed;
    int tmp=0,bj=0,lok=1;
    i=1;
    que t;
    i=1;
    while(i<=tot*2)
    {
        tmp+=c[i];
        if(tmp>=m) cnt++,ans[cnt].l=(i+1)/2,bj=1;
        while(tmp>=m&&i<=tot*2)
        {
            i++;
            tmp+=c[i];
        }
        if(bj)
        {
            ans[cnt].r=(i+1)/2;
            bj=0;
        }
        i++;
    }
    cout<<cnt<<endl;
    for(i=1;i<=cnt;i++)
    {
        cout<<p[ans[i].l]<<" "<<p[ans[i].r]<<endl;
    }
    return 0;
}


```


---

## 作者：HMZHMZHMZ (赞：0)

### 题意

给定 $ n $ 条线段，求有多少个区间至少被 $ k $ 条线段覆盖。

### 思路

如果一个点被覆盖了 $ k $ 次及以上，我们可以这么认为，这个点的左边有 $ \ge k $ 条线段的左端点，并且右端点全都在该点的右边。

所以我们只需要将每一个端点都拿出来，排序，每次遇见左端点便加一，遇见右端点便减一，然后判断值是否等于 $ k $ 即可。

时间复杂度 $ O( n ) $。

### 代码

```cpp

#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb(x) push_back(x)
using namespace std;
const int N=1e6+10;
struct node{
	int x,typ;
}a[N<<1]; 
ll ans;
vector<node> v;
int n,m,T,cnt,sum,lst;
inline int read(){
	int s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
inline bool cmp(node a,node b){
	//这里判断a.typ<b.typ是因为有可能有两条线段端点重合
   //先减后加的话会将这一个点与前面的区间分离
	return a.x==b.x?a.typ<b.typ:a.x<b.x;
}
int main(){
	n=read(),m=read();
	for(register int i=1,l,r;i<=n;++i){
		a[++cnt]=(node){read(),0};//0表示左端点
		a[++cnt]=(node){read(),1};//1表示右端点
	}
	sort(a+1,a+cnt+1,cmp);
	for(register int i=1;i<=cnt;++i){
		if(a[i].typ==1){
			if(sum==m) v.push_back((node){lst,a[i].x});
			--sum;
		}else{
			++sum;
			if(sum==m) lst=a[i].x;
		}
	}
	printf("%d\n",v.size());
	for(register int i=0;i<v.size();++i) printf("%d%d\n",v[i].x,v[i].typ);
	return 0;
}

```

---

