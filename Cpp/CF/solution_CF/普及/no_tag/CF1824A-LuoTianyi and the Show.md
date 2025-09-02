# LuoTianyi and the Show

## 题目描述

有 $n$ 个人观看一场与 VOCALOID 有关的演出，场地里有一行座位，从左到右标号 $1$ 到 $m$，接下来观众将按顺序以如下三种方式中的一种选择座位：

1. 如果没人坐在座位上，就坐在座位 $m$ 上，否则坐在目前最靠左的人的左边。若座位 $1$ 有人，则离开。
2. 如果没人坐在座位上，就坐在座位 $1$ 上，否则坐在目前最靠右的人的右边。若座位 $m$ 有人，则离开。
3. 如果 $x_i$ 没人则坐在 $x_i$，否则离开。

现在知道每个人选择座位的方式，你可以让人们按照任意顺序入场，求最多找到座位的人数。

## 说明/提示

第一组测试样例中，所有人都想占用座位 $5$，因此只有 $1$ 个人能找到座位。

第二组测试样例中，我们可以让人们按照 $1,2,3,4$ 的顺序入场，那么除了最后一个人以外的人都能找到座位。

在第三组测试样例中，我们可以让人们按照这样的顺序入场：  
让第三个人入场：  

| –   | –   | –   | 3   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第四个人入场：  

| –   | –   | –   | 3   | 4   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第五个人入场：

| –   | –   | –   | 3   | 4   | 5   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第一个人入场：

| –   | –   | 1   | 3   | 4   | 5   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第二个人入场：

| –   | 2   | 1   | 3   | 4   | 5   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

于是 $5$ 个人都找到了座位。

在第五组测试样例中，我们可以让人们按照这样的顺序入场：  
让第四个人入场：

| –   | –   | –   | –   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第三个人入场：

| –   | –   | –   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第六个人入场，由于他选择了第四个座位按照第三种方式入场，但第四个座位已经被占，所以离开：

| –   | –   | –   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第五个人入场：

| –   | –   | 5   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第一个人入场：

| –   | 1   | 5   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- |  

让第二个人入场：

| 2   | 1   | 5   | 3   | 4   | –   |
| --- | --- | --- | --- | --- | --- | 

于是 $5$ 个人找到了座位。

在第七组测试样例中，我们可以让人们按照这样的顺序入场：  
让第三个人入场：

| 3   | –   | –   | –   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第四个人入场：

| 3   | 4   | –   | –   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第五个人入场：

| 3   | 4   | 5   | –   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第六个人入场：

| 3   | 4   | 5   | 6   | –   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第一个人入场：

| 3   | 4   | 5   | 6   | 1   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

让第二个人入场，他以第一种方式选择座位，而座位 $1$ 被占用，所以离开：

| 3   | 4   | 5   | 6   | 1   | –   | –   |
| --- | --- | --- | --- | --- | --- | --- |  

于是 $5$ 个人找到了座位。

## 样例 #1

### 输入

```
10
3 10
5 5 5
4 6
1 -2 -2 1
5 7
-1 -1 4 -2 -2
6 7
5 -2 -2 -2 -2 -2
6 6
-1 1 4 5 -1 4
6 8
-1 -1 -1 3 -1 -2
6 7
5 -1 -2 -2 -2 -2
3 1
-2 -2 1
2 5
5 -2
1 2
-1```

### 输出

```
1
3
5
6
5
5
5
1
2
1```

# 题解

## 作者：PCCP (赞：3)

# CF1824A

### 做法：

对于这道题，我们可以先安排第三种，也就是固定位置的观众先行就坐，再考虑第一和第二种观众，为什么呢？

~~发挥钢四玩家的填线特长，~~ 我们可以发现，在固定位置之间会有一些空开的位置，这些位置是否可以坐人呢？由于我们可以随意地改变观众入场顺序，所以可以先让某个空白区间的左右端点中的一个先入场，再选择第一或第二种观众入场直至空白区间填满，最后再让另一个端点入场，这样就不会有空座位了。

当然，一个固定座位有两人同时要求的话，自然只能坐一个人了。

具体细节见代码。


```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1e5+10;
int t,n,m,a[N],st[N];
int k1,k2,k3;
int ans1,ans2,ans3,res;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		memset(a,0,sizeof a);
		memset(st,0,sizeof st);
		k1=k2=k3=res=ans1=ans2=ans3=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]>0){
				if(st[a[i]]==0){
					st[a[i]]=1;
					k3++;//第三种观众的数量
				}
			}
			else if(a[i]==-1){
				k1++;//第一种观众的数量
			}
			else{
				k2++;//第二种观众的数量
			}
		}
		ans1=min(k1+k3,m);//只让第一三种观众入场
		ans2=min(k2+k3,m);//只让第二三种观众入场
		for(int i=1;i<=m;i++){
			st[i]+=st[i-1];//前缀和
		}
		for(int i=1;i<=m;i++){
			if(st[i]-st[i-1]>0){
				ans3=max(ans3,min(k1,i-1-st[i-1])+min(k2,m-i-(st[m]-st[i]))+k3);//枚举从哪个固定位置开始作为分水岭，让第一二种观众向两侧填线
			}
			
		}
		res=max(ans1,max(ans2,ans3));
		printf("%d\n",res);
	}
}
```


---

## 作者：syysongyuyang (赞：2)

## 题目大意

$n$ 个人，$m$ 个座位，每个人有一个权值 $d_i$，$d_i \in [-2\dots m]$。

如果 $d_i>0$，那么 $i$ 进来将坐在 $d_i$ 处。

否则，如果 $d_i=-1$，如果没有人，那么将会坐在 $m$ 处，否则坐在最左边的人的左边。如果座位 $1$ 被占了，那么离开。

如果 $d_i=-2$，如果没有人，那么将会坐在 $1$ 处。否则坐在最右边的人的右边。如果座位 $m$ 被占了，那么离开。

可以任意安排进场的顺序，求最终能让最多多少个人找到座位。

## 解法

我们首先考虑没有 $d_i>0$ 的情况。

定义 $cnt1$ 表示 $d_i>0$ 的数量，$cnt2$ 表示 $d_i=-1$ 的数量，$cnt3$ 表示 $d_i=-2$ 的数量。

容易发现，在这种情况下，答案是 $\min(\max(cnt2,cnt3),m)$。

考虑加入点，我们假设加入到第 $i$ 个点，那么假设前面有 $cnt$ 个点。我们以 $i$ 点作为决策点，那么显然前面可以放最多 $\min(i-cnt-1,cnt2)$ 个，后面最多可以放 $\min (cnt3,m-i-cnt1+cnt+1)$ 个点。

为什么可以这么放呢？考虑放点 $i$ 时，先放 $i$，再依次放前缀中 $d_i>0$ 的点，中间的空缺用  $d_i=-1$ 的点填。这样，我们能填的最大长度就是 $\min(i-cnt-1,cnt2)$。在右边也这么类似地放，右边的最大长度就是 $\min (cnt3,m-i-cnt1+cnt+1)$。

最后和 $\min(cnt2+cnt1,m)$ 以及 $\min(cnt3+cnt1,m)$ 比较一下就行了。

注意：$d_i>0$ 的部分需要去重，可以  `unique`  和  `sort`，或者是维护一个桶打个标记就行了。

时间复杂度：$\Theta(n)$

## 代码实现：

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<bitset>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int T,n,m;
int a[N],b[N];
inline int read(){
    int s=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') {f=-1;} ch=getchar();}
    while(isdigit(ch)) {s=(s<<1)+(s<<3)+ch-'0'; ch=getchar();}
    return s*f;
}
inline void write(int x){
    int top=0,sta[35];
    while(x) {sta[top++]=x%10,x/=10;}
    while(top) {putchar(sta[--top]+'0');}
}
inline void solve()
{
    n=read(),m=read();
    memset(b,0,sizeof(b));
    int cnt1=0,cnt2=0,cnt3=0,ans=0,cnt=0;
    for (int i=1;i<=n;i++) 
    {
        a[i]=read();
        if (a[i]>0)
        {
            if (!b[a[i]]) cnt1++;
            b[a[i]]=1;
        }
        if (a[i]==-1) cnt2++;
        if (a[i]==-2) cnt3++;
    }   
    if (!cnt1)
    {
        printf("%d\n",min(m,max(cnt2,cnt3)));
        return ;
    }
    ans=max(max(ans,min(cnt1+cnt3,m)),max(ans,min(cnt1+cnt2,m)));
    for (int i=1;i<=m;i++)
    {
        if (b[i])
        {
            ans=max(ans,cnt1+min(cnt2,i-1-cnt)+min(m-i-cnt1+cnt+1,cnt3));
            cnt++;
        }
    }
    printf("%d\n",ans);
}
int main()
{
    T=read();
    while (T--) solve();
    return 0;
}
```



---

## 作者：Pt_crN (赞：2)

首先想到先放 $-1$ 或 $-2$ 大概率不是最优的。所以先确定放一个 $x_i>0$，然后考虑以下操作：

- 如果能找到一个 $x_i$ 使得该位置为在当前情况下放 $-1$ 所在的位置，则放这个 $x_i$。

- 否则放一个 $x_i=-1$。

$x_i=-2$ 的情况同理。

枚举每一个 $x_i>0$，看能放多少个数即可。

当然有时候，先放 $-1$ 或 $-2$ 真的是最优的，特判一下。

code：

```cpp
int n,m,k,e[100007];
void solve(){
	scanf("%d%d",&n,&m);
	int a=0,b=0;
	k=0;
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		if(x==-1)
			a++;
		else if(x==-2)
			b++;
		else
			e[++k]=x;
	}
	sort(e+1,e+k+1);
	k=unique(e+1,e+k+1)-e-1;
	int ans=max(min(a+k,m),min(b+k,m));//先放 -1/-2
	for(int i=1;i<=k;i++)
		ans=max(ans,min(i-1+a,e[i]-1)+min(k-i+b,m-e[i])+1);//当前 xi 左右能放的个数
	printf("%d\n",ans);
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		solve();
}
```

ps：为啥有很多大佬都说 A 难搞？不理解。

---

## 作者：Wuming_Shi (赞：1)

# CF1824A 题解
## 题意
有一排 $m$ 个座位，共有 $n$ 个人。第 $i$ 个人可能有三种选座方式：

若 $x_i=-1$，则坐在当前最靠左的人的左侧（没人则为 $m$，越界就不坐）。\
若 $x_i=-2$，则坐在当前最靠右的人的右侧（没人则为 $1$，越界就不坐）。\
若 $x_i\ge1$，则坐在座位 $x_i$ 上（被占就不坐）。

给定 $x_i$，求构造一种选座顺序，使得最终有座的人最多。输出最大值。

## 思路
考虑枚举第一个人坐在哪，设这个位置为 $p$。注意到，第一种人只能坐在 $p$ 左侧，第二种人只能坐在 $p$ 右侧。考虑分别计算 $p$ 左侧和 $p$ 右侧的贡献。

设第一种人的总人数为 $cnt1$，第二种人的总人数为 $cnt2$，并用前缀和 $sum_i$ 统计出位置 $1$ 至 $i$ 中有几个位置被第三种人选中（觉得绕可以看代码）。

考虑 $p$ 左侧的贡献。容易发现这样一种构造方式：从 $p-1$ 开始一直往左放第一类人，直到碰到能放第三类人的位置。把这个位置放上第三类人，再往左重复以上过程。这样最多能放 $cnt1+sum_{p-1}$ 个人，再对 $p-1$ 取 $\min$（刨去越界的人）即可。

考虑 $p$ 右侧的贡献。类似地，从 $p+1$ 开始交替放第二类人和第三类人，最多能放 $cnt2+sum_{m}-sum_{p}$ 个人，再对 $m-p$ 取 $\min$ 即可。

最后，点 $p$ 的答案即为上述两种情况的贡献加起来再加一（点 $p$ 的贡献）。

循环遍历每个第三类人选择的位置作为 $p$，以及先放一个第一或二类人的情况（$p=m$ 或 $p=1$），答案取其中最大值。

时间复杂度 $O(n)$。

## 代码
[link](https://www.luogu.com.cn/paste/uyylbb79)

---

## 作者：ForgotDream_CHN (赞：1)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17385994.html)

## 题意

有 $n$ 个人、编号为 $1$ 至 $m$ 的 $m$ 个座位与三种坐座位的方式：

1. 坐在最左边的人的左边，当 $1$ 号座位也不为空时就不坐了，当没有人坐在座位上时坐在 $m$ 号座位上；
2. 坐在最右边的人的右边，当 $m$ 号座位也不为空时就不坐了，当没有人坐在座位上时坐在 $1$ 号座位上；
3. 坐在指定编号的座位上，当已经有人坐在这个座位上时就不坐了。

每个人都有一种坐座位的方式，你可以任意指定他们坐座位的顺序，问最多能坐多少个人。

$n,m \le 2 \times 10^5$。

## 思路

为了方便，我们将上边三种坐进去的方式所对应的三种人称为一类人、二类人与三类人。

首先我们先把三类人排个序去个重，这样至少每个三类人都有座位坐，于是我们先把他们安排进去再说。

然后对于一类人与二类人，可以任意指定一个三类人作为锚节点，在保证其他三类人也坐得进去的前提下尽量多的向其左右插入一类人与二类人。可以保证一定存在这样一种插入方式。于是我们可以 $O(n)$ 预处理出每个三类人左右的空位，然后再扫一遍取得最大值。

还有一种情况就是，仍然在保证所有三类人都坐的进去的前提下，只安排一类人或二类人其中一种人的座位，这个可以特判一下。

## 代码

```cpp
int n, m;
std::cin >> n >> m;

std::vector<int> x(n), a;
int lcnt = 0, rcnt = 0;
for (int i = 0; i < n; i++) {
  std::cin >> x[i];
  if (x[i] > 0) {
    a.push_back(x[i]);
  } else if (x[i] == -1) {
    lcnt++;
  } else if (x[i] == -2) {
    rcnt++;
  }
}

if (a.empty()) {
  std::cout << std::min(m, std::max(lcnt, rcnt)) << "\n";
  return;
}

std::sort(a.begin(), a.end());
a.erase(std::unique(a.begin(), a.end()), a.end());
n = a.size();

std::vector<int> l(n), r(n);
int max = std::min(m - n, std::max(lcnt, rcnt));
for (int i = 0; i < n; i++) {
  l[i] = a[i] - i - 1;
  r[i] = m - a[i] - (n - i - 1);
  max = std::max(max, std::min(lcnt, l[i]) + std::min(rcnt, r[i]));
}

int ans = n + max;
std::cout << ans << "\n";
```

---

## 作者：2021sunzishan (赞：0)

~~哇，cf 都开始整洛天依了呢~~~

## 题目大意：
有 $n$ 个人和 $m$ 个座位，有的人位置固定，剩下的人要么坐在最左边的人右边，要么坐在最右边的人左边。问最多能有多少个人坐上座位。
## 思路：
这道题应该算是个思维题。

首先我们想到，将座位固定的人先安排上。因为可以任意安排入场顺序，所以可以保证这几个固定座位之间的空隙我们能填满。

然后就是如何分配剩下的座位了。

我们可以枚举第一个进场的固定座位的人。这样，他的左边和右边将剩下的两类的 座位已经划分好了。我们在所有答案当中取一个最大值，就是最终的答案。

以上就是本题的思路了。如果还是不懂，就看代码吧。

**切勿抄袭！！！**

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int s[100005],t;
inline int read(){//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	t=read();
	while(t--){
		memset(s,0,sizeof(s));
		n=read(),m=read();
		int cnt=0,m1=0,m2=0;
		for(int i=1;i<=n;i++){
			int x=read();
			if(x>0){
				if(!s[x])cnt++;
				s[x]=1;
			}
			if(x==-1)
				m1++;
			if(x==-2)
				m2++;
		}
		n=cnt;
		for(int i=1;i<=m;i++)//s[i]表示1~i当中有几个固定座位的人
			s[i]+=s[i-1];
		int ans=max(min(n+m1,m),min(n+m2,m));//特殊情况，要 特判
		for(int i=1;i<=m;i++){
			if(s[i]-s[i-1]>0){
				int k1=min(i-1-s[i-1],m1),k2=min(m-i-(s[m]-s[i]),m2);
           //k1表示这个人左边能坐多少人，k2表示右边
				ans=max(ans,k1+k2+n);//取最大值
			}
		}
		printf("%d\n",ans);//最后输出
	}
	return 0;
}
```
完结~

---

## 作者：FeiDing (赞：0)

$\color{white}{\text{蒟蒻第一篇题解}}$

我们可以先定义：

1. 一类人从左边进，挨着遇到的第一个人坐下。
2. 二类人从右边进，挨着遇到的第一个人坐下。
3. 三类人坐在第 $k$ 个座位上，如果那个座位有人了，离开。

很明显，有以下几个结论：

+ 只要三类人人数不大于 $m$，就能把他们全安排下。
+ 如果第一个入座的人是一类人，那二类人就可以退票了(第 $m$ 个座位被占了)，反之亦然。

所以我们可以先让一个三类人入座，把所有座位分为两部分，左边在让所有三类人入座的基础上再让一类人入座，右边在让所有三类人入座的基础上再让二类人入座。枚举这个把所有座位分成两部分的特殊三类人即可。

当然还得特判以下两种情况：

1. 只坐一、三类人。不坐二类人。
2. 只坐二、三类人。不坐一类人。

理论存在，代码如下：

```cpp
#include<cstring>
#include<iostream>
using namespace std;
int t,n,m,way1,way2,cnt,ans;
int way3[100002],ji[100002],s[100002];
int main(){
	cin>>t;
	while(t--){
		cnt=0;//三类人数 
		ans=0;
		way1=way2=0;//一、二类人数 
		memset(ji,0,sizeof(ji));
		memset(s,0,sizeof(s));
		cin>>n>>m;
		for(int i=1;i<=n;++i){
			int k;
			cin>>k;
			switch(k){
				case -1:
					++way1;
					break;
				case -2:
					++way2;
					break;
				default:
					if(!ji[k]){//去重，如果重复那也只能坐一个人 
						ji[k]=1;//有点类似计数排序
						++cnt;
					}
			}
		}
		for(int i=1;i<=m;++i){//前缀和 
			s[i]=s[i-1]+ji[i];
		}
		ans=min(max(way1,way2)+cnt,m);//特判
		for(int i=1;i<=m;++i){
			if(ji[i]){
				ans=max(ans,cnt+min(i-1-s[i-1]/*编号小于i的空座数量，可以让一类人入座*/,way1)+min(m-i-(s[m]-s[i])/*编号小于i的空座数量，可以让二类人入座*/,way2));
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：WaterSun (赞：0)

# 思路

首先，我们需要确定每一种方案的第一个人，那么，可以分为三种情况（其中 $a$ 为 $x_i = -1$ 的数量，$b$ 为 $x_i = -2$ 的数量，$len$ 为原序列 $x$ 中权值大于 $0$ 的序列排序并离散化的数量）：

1. 选择 $x_i = -1$ 的人开始。那么，会在 $m$ 点坐下，那么，对于所有 $x_i = -2$ 的人都没有位置坐。想象一下他们坐下的顺序，如果当前 $x_i = -1$，并且有一个 $x_j = m - i$（即当前需要选择的位置），那么，显然优先选择 $j$ 坐。所以，此贡献为 $\min(m,a + len)$。

2. 选择 $x_i = -2$ 的人开始，同理，贡献为 $\min(m,b + len)$。

3. 选择 $x_i > 0$ 的人开始，那么，能够在 $x_i$ 左边坐下的人，要么 $x_j < x_i$ 要么是 $-1$；右边同理。所以，对于左边的答案 $A$ 是 $\min(a + i,a_i - 1)$，右边的答案 $B$ 同理 $b + len - i - 1$。该位置的贡献是 $A + 1 + B$。

在这里，我们排序并且离散化的意义是，使第 $3$ 中情况中，快速得出 $x_j < x_i$ 和 $x_k > x_i$ 的数量。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int T,n,m;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	T = read();
	while (T--){
		int a = 0,b = 0,ans = 0;
		vector<int> t,arr;
		n = read();
		m = read();
		for (re int i = 1;i <= n;i++){
			int x;
			x = read();
			if (x == -1) a++;
			else if (x == -2) b++;
			else t.push_back(x);
		}
		int len = t.size();
		sort(t.begin(),t.end());
		for (re int i = 0;i < len;i++){
			if (!i) arr.push_back(t[i]);
			else if (t[i] != t[i - 1]) arr.push_back(t[i]);
		}//排序 + 离散化 
		len = arr.size();
		for (int i = 0;i < len;i++){
			int A = 0,B = 0;
			if (a + i <= arr[i] - 1) A = a + i;
			else A = arr[i] - 1;
			if (b + len - i - 1 <= m - arr[i]) B = b + len - i - 1;
			else B = m - arr[i];
			ans = max(ans,A + 1 + B);
		}
		printf("%d\n",max({ans,min(m,a + len),min(m,b + len)}));//3 种情况取最大值 
	}
	return 0;
}
```

---

## 作者：Geoyster (赞：0)

## CF1824A LuoTianyi and the Show

#### 题目大意

将 $n$ 名观众排在长度为 $m$ 的座位上。观众有三种入座习惯：

1. 坐在最靠左的那个人左边，若最左边的人的位置序号为 $1$ 则不入坐，若无人入座则坐在 $m$ 处

2. 坐在最靠右的那个人右边，若最右边的人的位置序号为 $m$ 则不入坐，若无人入座则坐在 $1$ 处

3. 入座指定位置，若该位置有人则不入坐

求按一定顺序入座后最多能入座多少人。

#### 思路

第三种人无法入座显然就是目标座位重复数。贪心地考虑前两种人，可知使最后的座位尽量连续可能存在最优解。

因为前两种人相当于从中心向两边扩展，那么考虑枚举中心点作为起点，即第三种人的位置。一旦决定了定点作为起点，就让前两种人向两边扩张，如遇到第三种人的指定位置，则优先让第三种人入座，然后继续扩张，到边界剩余的即无法入座的个数。

注意特殊情况：从最左或最右开始也可能存在最优解

#### 具体实现

 _（由于数据范围小，故随便找了个可行解，可能存在更优的实现）_ 
 
分别统计前两种人数量为 $Lcnt,Rcnt$
 
第三种人去重可以先把他们插入 ```set```

然后用前缀和 $sum_i$ 记 $[1,i]$ 的第三种人数

记第三种人的位置集合为 $S$，则求

$\sum_{i \in S}{\min(Lcnt,i-sum_i)+\min(Rcnt,m-i-sum_m+sum_i)}$

特殊地，

$ans=\max(ans,\min(Lcnt,m-sum_m))$

$ans=\max(ans,\min(Rcnt,m-sum_m))$

#### AC Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,x[100005],lcnt,rcnt,res,chs;
int sum[100005];
set<int> s;
set<int>::iterator it;
signed main(){
	scanf("%lld",&t);
	while(t--){
		memset(x,0,sizeof x);
		memset(sum,0,sizeof sum);
		s.clear();
		lcnt=rcnt=res=chs=0;
		scanf("%lld %lld",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%lld",&x[i]);
			if(x[i]==-1) lcnt++;
			else if(x[i]==-2) rcnt++;
			else {
				s.insert(x[i]);	
				sum[x[i]]=1;
			}
		}
		for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
		res=s.size();
		for(it=s.begin();it!=s.end();it++){
			int tmp=*it;
			chs=max(chs,min(lcnt,tmp-sum[tmp])+min(rcnt,m-tmp-sum[m]+sum[tmp]));
		}
		chs=max(chs,min(m-sum[m],rcnt));
		chs=max(chs,min(m-sum[m],lcnt));
		printf("%lld\n",res+chs);
	}
	return 0;
} 
```

---

