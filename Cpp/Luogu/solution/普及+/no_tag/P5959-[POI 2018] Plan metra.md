# [POI 2018] Plan metra

## 题目描述

有一棵 $n$ 个点的无根树，每条边有一个正整数权值，表示长度，定义两点距离为在树上的最短路径的长度。

已知 $2$ 到 $ n-1$ 每个点在树上与 $1$ 和 $n$ 的距离，请根据这些信息还原出这棵树。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 500000$，$1\le d\le 1000000$，$1\le u,v\le n$，$1\le c\le1000000$。

## 样例 #1

### 输入

```
7
6 6 2 2 1
5 3 5 1 4```

### 输出

```
TAK
1 5 2
5 7 1
5 2 4
7 3 3
1 4 2
1 6 1```

# 题解

## 作者：maruize (赞：6)

少有的构造题

---

**我们可以想象这样一个形状：**

(一条线上挂一堆点)

![](https://cdn.luogu.com.cn/upload/image_hosting/xhp5l56n.png)

(图画的不好)

**首先考虑在线上的点**

要想知道哪些点在线上，只要知道1-n的距离

显然他是
$$ min_{i=1}^n(d(1,i)+d(i,n))$$

因为如果d(1,n)比这个长的话$ d(1,i)+d(i,n)<d(1,n)$的点将无处安放。

**然后考虑剩下的点能不能挂上**

![](https://cdn.luogu.com.cn/upload/image_hosting/y0vu7d6n.png)

$M=d(t,i),X=d(1,t),Y=d(t,n)$

如图，若点i能挂在位置为t的点，则

$A=X+M(1),B=Y+M(2)$

$(1)-(2)$得$A-B=X-Y$。

所以判断一个点i是否能挂在线上，只要判断是否有在线上的点j使

$d(1,i)-d(i,n)=d(1,j)-d(j,n)$。

开个桶存一下即可。

code：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
int n;
void WA(){puts("NIE"),exit(0);}
struct data{int x,y,id;}f[500005];
bool cmp(data a,data b)
	{return a.x+a.y==b.x+b.y?a.x<b.x:a.x+a.y<b.x+b.y;}
bool CMP(data a,data b){return a.x<b.x;}
int ope[10000005],*val=ope+5000000;//桶
//要开够，要不RE|WA|UKE。。。
int fa[500005],v[500005];
signed main(){
	int M=0x3f3f3f3f;
	scanf("%d",&n);//cout<<n<<endl;
	for(int i=1;i<=n;i++)f[i].id=i;
	for(int i=2;i<n;i++)scanf("%d",&f[i].x);
	for(int i=2;i<n;i++)scanf("%d",&f[i].y);
	for(int i=2;i<n;i++)M=min(M,f[i].x+f[i].y);
	f[1]={0,M,1},f[n]={M,0,n};
	
	sort(f+1,f+n+1,cmp);//排序来分隔在线上的和不在的。
	int s;
	val[-M]=1;//往桶里塞进d(1,1)-d(1,n)
	for(s=2;s<=n;s++){
		if(f[s].x+f[s].y==M){//在线上
			if(f[s].x==f[s-1].x)WA();//点间距离!=0
			val[f[s].x-f[s].y]=s;
            //往桶里塞进d(1,s)-d(s,n)
		}
		else break;//不在
	}
	for(int i=s;i<=n;i++){
		int&t=val[f[i].x-f[i].y];
		if(t)fa[i]=t,v[i]=f[i].x-f[t].x;
		else WA();
	}
	puts("TAK");
	for(int i=2;i<s;i++)
		printf("%d %d %d\n",f[i-1].id,f[i].id,f[i].x-f[i-1].x);
	for(int i=s;i<=n;i++)
		printf("%d %d %d\n",f[fa[i]].id,f[i].id,v[i]);
	return 0;
} 

```

结束？

---

然后你光荣的得了80pts。

这是漏了一种情况：

1-n的路径上没有其他点

like this：

![](https://cdn.luogu.com.cn/upload/image_hosting/0u6z2zz7.png)

这时d(1,n)就不是原来的了。

d(1,n)=

$ \ $d(1,i)-d(i,n)$ \ $[ i在“左侧” ]

$ \ $d(i,n)-d(1,i)$ \ $[ i在“右侧” ]



只有对于所有的i，d(1,n)相等才可以。

所以特判一下：

```cpp
bool flag=1;
for(int i=3;i<n;i++)if(abs(f[i].x-f[i].y)!=abs(f[2].x-f[2].y))flag=0;
if(!flag)return;
int M=abs(f[2].x-f[2].y);//M=d(1,n)
if(M==0)return;
puts("TAK");
printf("1 %d %d\n",n,M); 
for(int i=2;i<n;i++){
	//if(f[i].x==f[i].y)return;
	if(f[i].x<f[i].y)printf("1 %d %d\n",i,f[i].x);
	else printf("%d %d %d\n",i,n,f[i].y);
}exit(0);
```

---

## 作者：Arr_ (赞：3)

# 题意
有一棵$n$个点的无根树，每条边有一个正整数权值，表示长度，定义两点距离为在树上的最短路径的长度。

已知$2$到$n-1$每个点在树上与1和n的距离，请根据这些信息还原出这棵树。
$2<=n<=500000$
# 分析
先把$1$到$n$路径上的节点找出来。

这里分两种情况，一种是$1$到$n$有连边。这种情况特判一下就好。

另一种是$1$到$n$没有连边，那么就找出其路径上的点，然后对于其他每个点，很容易找到它可以挂在链上的哪个节点下。

# ↓下方是参考代码
# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

const int N=500005;
const int inf=1000000000;

int n,d1[N],d2[N],cnt,a[N];
bool vis[N];
struct data{int x,y,w;}ans[N];

bool cmp(int x,int y)
{
    return d1[x]<d1[y];
}

bool check(int len)
{
    if (!len) return 0;
    for (int i=2;i<n;i++)
        if (abs(d1[i]-d2[i])!=len) return 0;
    puts("TAK");
    printf("%d %d %d\n",1,n,len);
    for (int i=2;i<n;i++)
        if (d1[i]<d2[i]) printf("%d %d %d\n",1,i,d1[i]);
        else printf("%d %d %d\n",i,n,d2[i]);
    return 1;
}

int main()
{
    scanf("%d",&n);
    if (n==2) {printf("TAK\n1 2 1");return 0;}
    for (int i=2;i<n;i++) scanf("%d",&d1[i]);
    for (int i=2;i<n;i++) scanf("%d",&d2[i]);
    if (check(abs(d1[2]-d2[2]))) return 0;
    int mn=inf;
    for (int i=2;i<n;i++)
        if (d1[i]+d2[i]<mn) mn=d1[i]+d2[i];
    int tot=0;a[++tot]=1;
    for (int i=2;i<n;i++)
        if (d1[i]+d2[i]==mn) a[++tot]=i,vis[i]=1;
    std::sort(a+1,a+tot+1,cmp);
    for (int i=1;i<tot;i++)
        if (d1[a[i]]==d1[a[i+1]]) {puts("NIE");return 0;}
    a[++tot]=n;
    d1[n]=d1[a[2]]+d2[a[2]];
    for (int i=2;i<n;i++)
    {
        if (vis[i]) continue;
        if ((d1[i]+d2[i]-d1[n])%2==1) {puts("NIE");return 0;}
        int dis=(d1[i]+d2[i]-d1[n])/2;
        int l=1,r=tot,p=0;
        while (l<=r)
        {
            int mid=(l+r)/2;
            if (d1[i]-dis==d1[a[mid]]) {p=mid;break;}
            if (d1[i]-dis<d1[a[mid]]) r=mid-1;
            else l=mid+1;
        }
        if (!p) {puts("NIE");return 0;}
        ans[++cnt]=(data){i,a[p],dis};
    }
    for (int i=1;i<tot;i++) ans[++cnt]=(data){a[i],a[i+1],d1[a[i+1]]-d1[a[i]]};
    puts("TAK");
    for (int i=1;i<=cnt;i++) printf("%d %d %d\n",ans[i].x,ans[i].y,ans[i].w);
    return 0;
}
```


---

## 作者：FQ04gty (赞：1)

##### [原题链接](https://www.luogu.com.cn/problem/P5959)

---

此题题意比较简单，思路也比较容易想到。但是我由于细节考虑不够清楚，导致写这一题时花了不少时间。

因此，本文侧重于本题的细节。如果认为写得不够明了，可以参考其他有图的文章。

---

本文中，$dis(i,j)$ 表示 $i$ 到 $j$ 的距离。

对于这棵树上除 $1$ 和 $n$ 外的一个点 $u$，其位置只有一下 $3$ 种情况：

1. 在 $1$ 与 $n$ 的两侧，更严谨的说，满足 $\lvert dis(u,1)-dis(u,n)\rvert=dis(1,n)$，并且与 $1$ 或 $n$ 直接相连。
2. 在 $1$ 与 $n$ 的路径上，即满足 $dis(u,1)+dis(u,n)=dis(1,n)$。
3. 通过第 $2$ 种情况的点与树连接，并且与第 $2$ 种情况的点直接相连。

为什么只有这 $3$ 种情况？

对于第 $1$ 类和第 $3$ 类情况的 $u$，我们考虑，如果一个点要通过其他点与 $1$、$n$ 或者是第 $2$ 种情况的点相连，那么一定存在一种把它们直接相连的方案，而不改变 $dis(u,1)$ 和 $dis(u,n)$。

剩余的情况是显然的。

那么确定 $k=dis(1,n)$ 成为了划分以上 $3$ 种点的关键。

首先，如果 $\lvert dis(u,1)-dis(u,n)\rvert$ 的奇偶性有不同，一定不存在构造方案。因为上面三组方案的奇偶性都与 $k$ 的奇偶性相同。

对于一个合法的 $k$，一定有 $k\geq \max(\lvert dis(u,1)-dis(u,n)\rvert)$，因为除了第 $1$ 类点满足 $k=\lvert dis(u,1)-dis(u,n)\rvert$，其余点都满足 $k>\lvert dis(u,1)-dis(u,n)\rvert$。

类似的，有 $k\leq\min(dis(u,1)+dis(u,n))$。

现在我们已经确定了 $k$ 的范围，为了进一步确定 $k$，我们假设第 $2$ 类点一定存在。

可以知道，$k=\min(dis(u,1)+dis(u,n))$。然后我们要检查每一组满足 $dis(u,1)-dis(u,n)=i$ 的点，当中是否有恰好 $1$ 个点满足 $dis(u,1)+dis(u,n)=k$。找到的这些点都是第 $2$ 类点，我们把它们连在 $1$ 到 $n$ 的路径上，当前组之内的其他点都是第 $3$ 类点。特别的，当 $i=-k$ 或 $i=k$ 时，这些点都是第 $1$ 类点，直接与 $1$ 或 $n$ 相连即可。

同理，对于第 $2$ 类点不存在的情况，我们知道第 $3$ 类点也不存在。那么所有点都是第 $1$ 类点，他们的 $\lvert dis(u,1)-dis(u,n)\rvert$ 一定分别相等且与 $k$ 相等，特判一下即可。

### Code

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int>pii;
const int SIZE=5e5+10,EXTRA=2e6+10,MV=1000000,inf=0x3f3f3f3f;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x*10)+(ch^48),ch=getchar();
    return x;
}
inline int abs(int x){return x>0?x:-x;}
int n,k,least,minn=inf,lst=1,A[SIZE],B[SIZE];
bool spj=true;
vector<int>bin[EXTRA];
inline int f(int x){return A[x]+B[x];}
inline bool cmp(int x,int y){return f(x)<f(y);}
int main()
{
    n=read();
    for(int i=2;i<n;i++)A[i]=read();
    for(int i=2;i<n;i++)B[i]=read();
    k=abs(A[2]-B[2]);
    for(int i=2;i<n;i++)
    {
        if(abs(A[i]-B[i])%2!=abs(k)%2)return printf("NIE"),0;
        least=max(least,abs(A[i]-B[i])),minn=min(minn,A[i]+B[i]);
        bin[A[i]-B[i]+MV].push_back(i);
    }
    for(int i=3;i<n;i++)if(k!=abs(A[i]-B[i])){spj=false;break;}
    if(spj)
    {
        printf("TAK\n%d %d %d\n",1,n,k);
        for(int i=2;i<n;i++)printf("%d %d %d\n",A[i]-B[i]<0?1:n,i,A[i]-B[i]<0?A[i]:B[i]);
        return 0;
    }
    if(minn<least)return printf("NIE"),0;
    k=minn;
    for(int i=-k+1;i<k;i++)if(!bin[i+MV].empty())
    {
        sort(bin[i+MV].begin(),bin[i+MV].end(),cmp);
        if(f(bin[i+MV][0])!=k)return printf("NIE"),0;
        if(bin[i+MV].size()>1&&f(bin[i+MV][1])==k)return printf("NIE"),0;
    }
    printf("TAK\n");
    for(int ths:bin[-k+MV])printf("%d %d %d\n",1,ths,A[ths]);
    for(int ths:bin[k+MV])printf("%d %d %d\n",n,ths,B[ths]);
    for(int i=-k+1;i<k;i++)if(!bin[i+MV].empty())
    {
        printf("%d %d %d\n",lst,bin[i+MV][0],A[bin[i+MV][0]]-A[lst]);
        lst=bin[i+MV][0];
        for(int ths:bin[i+MV])if(ths!=lst)printf("%d %d %d\n",lst,ths,A[ths]-A[lst]);
    }
    printf("%d %d %d\n",lst,n,k-A[lst]);
    return 0;
}
```

---

## 作者：__Ginka__ (赞：0)

### 思路：
树的恢复通过节点之间的距离约束来实现。

树中每一条边的权重可以通过节点之间的距离来推算。
   
#### check 函数
用于检查节点的距离差是否符合树的结构要求

### 树结构构造
使用两个数组的距离信息来推测树的结构。

使用贪心和二分查找来确定树的边。

#### 树的边权重计算：
每条边的权重可以由两点间的距离来确定：

$$
\text{ 边权重 }=\frac{d1_i+d2_i-d1_n}{2}
$$

代码如下（思路解释在上，代码就不放注释了）：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
const int inf=1000000000;
int n,d1[N],d2[N],cnt,a[N];
bool vis[N];
struct hhh
{
    int x,y,w;
}ans[N];
bool cmp(int x,int y)
{
    return d1[x]<d1[y];
}
bool check(int len)
{
    if(!len) return 0;
    for(int i=2;i<n;i++)
        if(abs(d1[i]-d2[i])!=len) return 0;
    cout<<"TAK"<<endl;
    cout<<"1 "<<n<<" "<<len<<endl;
    for(int i=2;i<n;i++)
    {
        if(d1[i]<d2[i]) cout<<"1 "<<i<<" "<<d1[i]<<endl;
        else cout<<i<<" "<<n<<" "<<d2[i]<<endl;
    }
    return 1;
}
int main()
{
    cin>>n;
    if(n==2) 
    {
        cout<<"TAK"<<endl;
        cout<<"1 2 1"<<endl;
        return 0;
	}
    for(int i=2;i<n;i++) cin>>d1[i];
    for(int i=2;i<n;i++) cin>>d2[i];
    if(check(abs(d1[2]-d2[2]))) return 0;
    int mn=inf;
    for(int i=2;i<n;i++) 
        if(d1[i]+d2[i]<mn) mn=d1[i]+d2[i];
    int t=0;
    a[++t]=1;
    for(int i=2;i<n;i++)
        if(d1[i]+d2[i]==mn)
            a[++t]=i,vis[i]=1;
    sort(a+1,a+t+1,cmp);
    for(int i=1;i<t;i++) 
    {
        if(d1[a[i]]==d1[a[i+1]]) 
        {
            cout<<"NIE"<<endl;
            return 0;
        }
    }
    a[++t]=n;
    d1[n]=d1[a[2]]+d2[a[2]];
    for(int i=2;i<n;i++) 
    {
        if(vis[i]) continue;
        if((d1[i]+d2[i]-d1[n])%2==1) 
        {
            cout<<"NIE"<<endl;
            return 0;
        }
        int dis=(d1[i]+d2[i]-d1[n])/2;
        int l=1,r=t,p=0;
        while(l<=r) 
        {
            int mid=(l+r)/2;
            if(d1[i]-dis==d1[a[mid]]) 
            {
                p=mid;
                break;
            }
            if(d1[i]-dis-d1[a[mid]]) r=mid-1;
            else l=mid+1;
        }
        if(!p) 
        {
            cout<<"NIE"<<endl;
            return 0;
        }
        ans[++cnt]={i,a[p],dis};
	}
    for(int i=1;i<t;i++) 
        ans[++cnt]={a[i],a[i+1],d1[a[i+1]]-d1[a[i]]};
    cout<<"TAK"<<endl;
    for(int i=1;i<=cnt;i++)
        cout<<ans[i].x<<" "<<ans[i].y<<" "<<ans[i].w<<endl;
    return 0;
}

```

---

## 作者：船酱魔王 (赞：0)

### 题意回顾

给定一棵未知结构的边带正整数权树 $ 2 \sim n-1 $ 到 $ 1,n $ 的距离，求出这棵树的结构。

$ 2 \le n \le 500000 $。

### 分析

$ 1 $ 和 $ n $ 之间有唯一的一条路径。

#### 当 $ 1, n $ 之间不存在直接连边时

把每个点到 $ 1,n $ 的距离相加，距离为最小值的所有点即为路径上的点，考虑按照这些点到 $ 1 $ 的距离排序，顺次连接即为 $ 1 $ 到 $ n $ 之间的链（若有重则此情况不成立）。

此时，对于每个点 $ u $，必然能找到链上的点 $ v $，使得 $ u $ 到 $ v $ 的路径均不在链上。可以根据 $ \operatorname{dis}\{u,1\}-\operatorname{dis}\{u,n\}=\operatorname{dis}\{v,1\}-\operatorname{dis}\{v,n\} $ 得到 $ v $ 的位置，然后 $ u,v $ 连一条边即可。注意边权如果算出来小数要舍弃这种情况。

#### 当 $ 1,n $ 之间存在直接连边时

因为 $ u,1,n $ 必然在一条简单路径（顺序不定）上且 $ u $ 不在 $ 1, n $ 之间，所以可以算出 $ \operatorname{dis}\{1,n\}=|\operatorname{dis}\{u,1\}-\operatorname{dis}\{u,n\}| $，此时考虑 $ \operatorname{dis}\{u,1\} $ 与 $ \operatorname{dis}\{u,n\} $ 的大小关系，判断 $ u $ 与 $ 1 $ 还是 $ n $ 连边即可。

漏判本情况可得 $ 80 $ 分。

### 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
const int N = 5e5 + 5;
int n;
int ft[N];
int gt[N];
map<int, int> mp;
int main() {
    scanf("%d", &n);
    if(n == 2) {
        puts("TAK\n1 2 114514");
        return 0;
    }
    for(int i = 2; i < n; i++) scanf("%d", &ft[i]);
    for(int i = 2; i < n; i++) scanf("%d", &gt[i]);
    int t = 0;
    for(int i = 2; i < n; i++) {
        int r = abs(ft[i] - gt[i]);
        if(!r) {
            t = 0;
            break;
        } else if(t && t != r) {
            t = 0;
            break;
        } else t = r;
    }
    if(t != 0) {
        puts("TAK");
        printf("1 %d %d\n", n, t);
        for(int i = 2; i < n; i++) {
            if(ft[i] < gt[i]) printf("%d %d %d\n", 1, i, ft[i]);
            else printf("%d %d %d\n", i, n, gt[i]);
        }
        return 0;
    }
    int mds = 1e9 + 5;
    for(int i = 2; i < n; i++) mds = min(mds, ft[i] + gt[i]);
    for(int i = 2; i < n; i++) {
        if(mds != ft[i] + gt[i]) {
            if((ft[i] + gt[i] - mds) % 2) {
                puts("NIE");
                return 0;
            }
            continue;
        }
        if(mp.find(ft[i]) != mp.end()) {
            puts("NIE");
            return 0;
        } mp[ft[i]] = i;
    }
    mp[0] = 1;
    mp[mds] = n;
    for(int i = 2; i < n; i++) {
        if(ft[i] + gt[i] == mds) continue;
        int mdis = (ft[i] + gt[i] - mds) / 2;
        ft[i] -= mdis, gt[i] = mdis;
        if(mp.find(ft[i]) == mp.end()) {
            puts("NIE");
            return 0;
        }
    }
    mp.erase(0);
    puts("TAK");
    int pnt, val;
    val = 0;
    pnt = 1;
    for(map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
        printf("%d %d %d\n", pnt, (it -> second), (it -> first) - val);
        gt[it -> second] = -1;
        val = it -> first;
        pnt = it -> second;
    }
    mp[0] = 1;
    for(int i = 2; i < n; i++) {
        if(gt[i] != -1) {
            printf("%d %d %d\n", i, mp[ft[i]], gt[i]);
        }
    }
    return 0;
}
```

---

