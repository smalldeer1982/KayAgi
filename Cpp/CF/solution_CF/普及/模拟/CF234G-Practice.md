# Practice

## 题目描述

本题需要文件读入读出。

输入文件：`input.txt`。

输出文件：`output.txt`。


现在有 $n$ 个人进行比赛（编号从 $1$ 到 $n$），每次把这 $n$ 个人不遗漏地分成两队进行比赛。

请构造一种比赛方式，使得比赛次数尽可能少，并且每两个人之间都在不同队比赛过。

## 样例 #1

### 输入

```
2
```

### 输出

```
1
1 1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
2
2 1 2
1 1
```

# 题解

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 CF234G Practice](https://www.luogu.com.cn/problem/CF234G)

## 解题思路

设 $k$ 人需要 $p_k$ 次比赛，下一场比赛将分成 $i$ 人和 $k-i$ 人。

显然这 $i$ 人和 $k-i$ 人相互独立，不需要额外的比赛，所以 $p_k=\max(p_i,p_{k-i})+1$。显然当 $i=k-i=\frac{n}{2}$，即两队人数均匀时，获得最优解。

每次比赛都至多让两半人相互独立，所以至少需要 $k=\left\lceil\log_2 n\right\rceil=\left\lfloor\log_2 (n-1)\right\rfloor+1$ 场比赛。

注意到，任意两个不同的非负整数，至少有一位二进制不同，所以不妨根据第 $j$ 位二进制进行分组。（$0\le j<k$）

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1005;
int a[N];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin>>n;
	int k=__lg(n-1)+1;
	cout<<k<<'\n';
	for(int j=0;j<k;j++)
	{
		int ans=0;
		for(int i=0;i<n;i++)
		{
			if(!(i>>j&1))ans++;
		}
		cout<<ans<<' ';
		for(int i=0;i<n;i++)
		{
			if(!(i>>j&1))cout<<i+1<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：crazy_boy (赞：2)

这道题其实挺难想的，我最开始想的是 $n-1$ 的构造方式，再加上好损友的亿点提示（关键部分没听他的），接着是 $\dfrac{n}{2}$ 的构造，最后才是正解 $\lceil \log _2 n \rceil$。

[题目传送门](https://www.luogu.com.cn/problem/CF234G)

## 思路

首先，最简单的思路就是，$n-1$ 轮，每个人和其他没有和他比过赛的人比赛。

很明显，这不是最优的。

接着，考虑优化。（中间 $\dfrac{n}{2}$ 的想法忘了咋搞了就不说了）

可以先让 $n$ 个人分成两队比赛，然后对内再进行比赛，以此类推。

我们可以把比赛过程想象成一棵树。这里用 $n=10$ 举例。

![](https://cdn.luogu.com.cn/upload/image_hosting/0lxko5cg.png)

第一种情况可以这么分，那么第一场比赛就是 $[1,5]$ 和 $[6,10]$ 打。

接着，$[1,5]$ 和 $[6,10]$ 要在内部进行比赛。

![](https://cdn.luogu.com.cn/upload/image_hosting/sqbqikof.png)

那么，很关键的一步，$[1,2]$ 和 $[3,5]$ 要在内部打，$[6,7]$ 和 $[8,10]$ 要在内部打。那，我们可以将 $[1,2]$ 和 $[6,7]$ 分到一队，$[3,5]$ 和 $[8,10]$ 分到另一队，这时候，虽然有些人会重复打，但是我们把两场比赛合并为了一场，简化了操作数量。

也就是说，他们实际上各打各的，互不干扰，只不过名义上是一支队伍罢了。

接着继续分，我就不过于详细的解释了。

![](https://cdn.luogu.com.cn/upload/image_hosting/hjmxs379.png)

也就是说，我们可以构造一个长度为 $n$ 的线段树，每次输出其叶子节点中的左节点即可。

在程序实现上，不需要真的构建出一个线段树，只需要维护其全部叶子节点即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void FASTIN();
struct range
{
    int l,r;
    int root;//0 左节点 1 右节点
}f[1010],t[1010];
void play(int n)
{
    int ans=0,cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(f[i].l==f[i].r) continue;
        int mid=(f[i].l+f[i].r)>>1;//分成左右两个部分，也就是内部继续对打
        cnt++;
        t[cnt].l=f[i].l,t[cnt].r=mid,t[cnt].root=0;
        cnt++;
        t[cnt].l=mid+1,t[cnt].r=f[i].r,t[cnt].root=1;
        ans+=mid-f[i].l+1;
    }
    for(int i=1;i<=cnt;i++) f[i]=t[i];cout<<endl;
    cout<<ans<<" ";
    bool flag=0;
    for(int i=1;i<=cnt;i++)
    {
        if(!f[i].root)
        {
            for(int j=f[i].l;j<=f[i].r;j++) cout<<j<<" ";
        }
        if(f[i].l!=f[i].r) flag=1;
    }
    cout<<endl;
    if(flag) play(cnt);
}
void run()
{
    int n,ans=0;
    cin>>n;
    while((1<<ans)<n) ans++;
    cout<<ans<<endl;
    f[1].l=1,f[1].r=n;
    play(1);
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    FASTIN();
    int t=1;
    // cin>>t;
    while(t--) run();
    system("pause");
    return 0;
}
void FASTIN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
```

---

## 作者：MattL (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF234G) & [原题链接](http://codeforces.com/problemset/problem/234/G)

标签：构造。

---

**解题：**

首先，看到“两队”，直接想到二进制。

我们把每个人的编号转成二进制，那么每次选那一位为 $1$（$0$ 也行）。

显而易见，比赛次数就为 $\left\lceil\log_2 n\right\rceil$。

**最后注意文件读写！！！**。

注意看懂输出格式。

---

**代码：**

上代码：


```cpp
#include <bits/stdc++.h>
using namespace std;


long long n,cnt,ans;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin>>n;
    while((1<<ans)<n)//求向上取整的log，方法有很多，选你喜欢的
        ans++;
    cout<<ans<<endl;
    for(int u=0;u<ans;u++)
    {
        cnt=0;
        for(int i=1;i<=n;i++)
            cnt+=bool(i&(1<<u));//先算一遍有几个人
        cout<<cnt<<' ';
        for(int i=1;i<=n;i++)
            if(i&(1<<u))//这位为1
                cout<<i<<' ';//直接输出
        cout<<endl;
    }

    return 0;
}
```

---

## 作者：longStone (赞：0)

# CF234G Practice 题解

## 观察

假设有 $5$ 个人要练习，那么可以按如下方式进行分组：

![](https://cdn.luogu.com.cn/upload/image_hosting/s550cljt.png)

很明显，对于一群没有互相比过赛的人，将他们平分到两队是最好的选择。

同时，发现同一个时间需要分队比赛的可能不止一组，例如图中第二次比赛的 $1,2$ 和 $4$，第二队 $3$ 和 $5$ 组在一起，分到一场比赛。

## 思路

初始有一群人 $[1,n]$，每次找一遍人数不为 $1$ 的人群并平分到两队直到所有人群都只剩一个人（一群人代表他们没有互相进行过比赛）。

## 代码

```c++
#include "bits/stdc++.h"
using namespace std;
int n, m, ans[1005], tot;
queue<pair<int,int>> q;
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> n;
    while(pow(2,m) < n)	m++;
    cout << m << '\n';
    q.push(make_pair(1,n));
    while(!q.empty())
    {
        pair<int,int> x = q.front();
        q.pop();
        if(x.first == 1 && x.second != n)//一轮结束
        {
            cout << tot << ' ';
            for(int i = 1;i <= tot;i++)	cout << ans[i] << ' ';
            cout << '\n';
            tot = 0;
            memset(ans,0,sizeof(ans));
        }
        for(int i = x.first;i <= (x.first + x.second) / 2;i++)	ans[++tot] = i;
        if(x.second - x.first == 0)	continue;
        q.push(make_pair(x.first,(x.first + x.second) / 2));
        q.push(make_pair((x.first + x.second) / 2 + 1,x.second));
    }
    return 0;
}
```

---

## 作者：Mrkn_chenyx12 (赞：0)

## 解题思路

如果我们把一个人的分队情况看作一个二进制串，每次分队看作一个二进制位，那么显然一组合法的解就是使得不存在两个人的分队情况是同一个二进制串。

那么，显然地，最小的比赛次数就是 $\lceil\log_2n\rceil$。而一种简单且可行的做法，对于每个人，直接以这个人的编号的二进制的后 $\lceil\log_2n\rceil$ 位作为这个二进制串，可以得知它们一定两两不同。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[1024];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    int cnt, k = ceil(log2(n));
    printf("%d\n", k);
    for (int i = 0; i < k; i++) {
        cnt = 0;
        for (int j = 1; j <= n; j++) {
            if (j & (1 << i)) a[++cnt] = j;
        }
        printf("%d ", cnt);
        for (int j = 1; j <= cnt; j++) printf("%d ", a[j]);
        puts("");
    }
    return 0;
}
```

---

## 作者：Error_Eric (赞：0)

楼下的题解太巧妙了，我来一个正常的（

抽象成图论：

给定点集，试以此点集构造最少的二分图，使得连接这些二分图图的边之后可以形成完全图。

显然欲使 $[1,n]$ 内的点完全联通，应先使 $[1,i],[i+1,n]$ 内点完全联通，然后构造左边为 $[1,i]$ 右边为 $[i+1,n]$ 的二分图。

好像线段树啊对不对,$[1,n]$ 为根节点，$[i,i]$ 为叶子节点，$[i,k][k+1,j] (i<k<j)$ 为 $[i,j]$ 的子节点。

没学过线段树的都知道，线段树每个非叶子节点分成尽量相等的时候深度最浅，为 $\lceil \log_2n\rceil$ 。

因此本题输出所有线段树的左儿子即可。

没有必要真的构建一个线段树。

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<queue>
using namespace std;
#define rei register int
#define il inline
#define pii pair<int,int> 
il const void readln(int &I){
    I=0;char C=getchar();
    while(!isdigit(C))C=getchar();
    while( isdigit(C))I=I*10+C-'0',C=getchar();
}
int n,res;bool v;
queue<pii>q;
queue<bool>vq;//是不是左儿子
pii o;
int len(pii p){//线段长度
    return p.second-p.first+1;
}
#define sub1 make_pair(o.first,(o.first+o.second)/2)//lson
#define sub2 make_pair((o.first+o.second)/2+1,o.second)//rson
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    readln(n);
    while((1<<res)<n)res++;
    printf("%d",res);
    q.push(make_pair(1,n)),vq.push(0);
    while(!q.empty()){
        o=q.front();q.pop();
        v=vq.front();vq.pop();
        if(o.first==1){//输出统计的左儿子总长度
            if(v)printf("\n%d ",res);
            res=0;
        }
        if(v==1) 
            for(rei i=o.first;i<=o.second;i++)
                printf("%d ",i);
        if(len(o)!=1)
            q.push(sub1),vq.push(1),res+=len(sub1),
            //统计左儿子长度
            q.push(sub2),vq.push(0);
        
    }
}
```

---

