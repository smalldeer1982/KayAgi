# Build a Contest

## 题目描述

### 题目大意
有$n$个题，每个题有一个难度$a_i(1\le a_i\le m)$，从左往右加入题，当加入的题中$m$个难度都出现时，输出$1$并把每个难度都删除一道题，否则输出$0$，求输出序列

## 样例 #1

### 输入

```
3 11
2 3 1 2 2 2 3 2 2 3 1
```

### 输出

```
00100000001
```

## 样例 #2

### 输入

```
4 8
4 1 3 3 2 3 3 3
```

### 输出

```
00001000
```

# 题解

## 作者：SOVOS (赞：3)

~~终于啊终于有题解没满我还会的题了~~

本蒟蒻第一篇题解，dalao勿喷

朴素的想法是用数组存每种难度题的个数，每次输入都加一，然后遍历每一种难度看有没有，如果都有，那就输出$1$并且把每一种难度的题数减一，否则输出$0$。

~~这谁都能想到好吧~~
```cpp
#include<cstdio>
using namespace std;
int n,m,nd[100005],ls;
void pt(){
	for(int i=1;i<=m;i++){
		if(!nd[i]){
			printf("0");
			return;
		}
	}
	for(int i=1;i<=m;i++)
		nd[i]--;
	printf("1");
	
}
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&ls);
		nd[ls]++;
		pt();
	}
   return 0;//养成好习惯
}
```

可是$O(nm)$的复杂度那$1m$时间可承受不住，于是聪明的我想出了另一种方法:

用一个变量来存储已有多少种难度，这样就少了判断那个for循环，这样洛谷的~~老年~~电脑就可以在$1s$算出答案了(不要不过审啊)

看注释吧，注释更好理解(~~其实是我不想写字~~)

```cpp
#include<cstdio>
using namespace std;
int n,m,nd[100005],ls,allnd;//n和m在题里面有了，应该都懂
//nd用来存每一种难度的题出现的几次，allnd存现在共有多少种难度的题
void pt(){//用来打印的函数，其实是为了更好退出
	if(allnd<m){//如果现有的难度没有m种
		printf("0");//说明没满，直接输出0
		return;
	}//如果满了，就继续，return就省了一个else
	for(int i=1;i<=m;i++){//把所有难度题减一
		if(nd[i]==1)allnd--;//只剩一个了说明这种难度的题
		nd[i]--;//全被删完了，所以把总难度个数减一
	}
	printf("1");
	
}
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&ls);
		if(!nd[ls])allnd++;//如果这种难度的题目前以前没有还输入了
		nd[ls]++;//  ^  就把已有难度个数加一
		pt();//每次都要输出
	}
}
```
成功AC哈哈哈哈哈

不对，你还没点赞，我还不能笑，快点赞！

---

## 作者：Molina (赞：2)

# 题目大意：
[题目链接](https://www.luogu.com.cn/problem/CF1100B)

很好理解题意。

一共有 $ n $ 个题，每个题有一个难度 $ a_i $，从左往右加入题，当加入了 $ m $ 个不同难度的题目时，输出 $ 1 $，并把当前有的每个难度都删除一道题，否则输出 $ 0 $。

输出这个序列。
# 本题思路：
直接**暴力**就行了，十分水的一道黄题，~~虽然我超时了一次~~。

按题目意思输入。这里用一个变量 $ cnt $ 记录当前有多少种不同难度的题目，用一个桶记录每种不同难度的题目的数量。如果当前未出现输入题目难度的题，将 $ cnt $ 加一，并在桶中这种难度的题目数量也加一。

判断，如果 $ cnt $ 已经达到 $ m $，输出 $ 1 $，将已经有的每种题目数量减一，如果减一后这种题目的数量为 $ 0 $ 了，就将 $ cnt $ 减一。反之，就输出 $ 0 $。

然后就做完了，详细解释请见代码。

# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,cnt=0,ton[100005];
int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        if(ton[a]==0)//判断，将cnt加一
            cnt++;
        ton[a]++;//记录桶数组
        if(cnt==m){//若满足情况
            cout<<"1";
            for(int j=1;j<=m;j++){//减去已有题目
                ton[j]--;
                if(ton[j]==0)
        			cnt--;
            }
        }
        else cout<<"0";
    }
    return 0;
}
```

---

## 作者：da32s1da (赞：2)

在此提供一个用queue的方法。

对于**每个数值**开一个queue，对总答案开一个queue。

若一个数值第一次出现，加入答案queue中，否则加入数值queue中。

答案queue的size为n时，符合要求。将其清空后，看一遍1~n的数值queue，若有数，加入答案queue中，数值queue需要pop一下。若没有数，vis变为0。

```
#include<cstdio>
#include<queue>
using namespace std;
const int N=1e5+50;
int n,m,cnt,x,vis[N];
queue<int>a[N],Ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&x);cnt=0;
		if(!vis[x])Ans.push(x),vis[x]=1;
		else a[x].push(x);
		if(Ans.size()==n){
			while(cnt<n){
				x=Ans.front();
				Ans.pop();
				if(!a[x].empty())Ans.push(x),a[x].pop();
				else vis[x]=0;
				cnt++;
			}
		}
		putchar(48+(cnt==n));
	}
}
```

---

## 作者：decoqwq (赞：1)

模拟题目

每次遇到一个新出现的数，种类数$cnt++$

如果$n\leq cnt$，就把每个数出现次数$-1$，然后更新$cnt$即可

时间复杂度看起来不对，但是实际上每一次全部$-1$只会在$n$次以后才出现，时间复杂度$O(n+q)$

不给代码啦

---

## 作者：AzusaCat (赞：0)

直接按照题意模拟，对每一个数开一个桶，再开一个计数器表示当前出现次数不为$0$的题目种类数，当计数器为$m$的之后直接暴力更改桶内的值。  
考虑复杂度为什么是对的，因为每一次修改前都至少有$m$个数被加入，一个数被删除后就不会再产生贡献，所以删除操作最多进行$O(\frac{n}{m})$次，复杂度为$O(n+m)$  
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int times[100005];
int main()
{
    int m,n,cnt=0,x;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        times[x]++;
        if(times[x]==1)cnt++;
        if(cnt==m)
        {
            for(int j=1;j<=m;j++)
            {
                times[j]--;
                if(!times[j])cnt--;
            }
            printf("1");
        }
        else printf("0");
    }
    return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

这道题感觉大家的做法都有点复杂呢……  
这道题其实不必被蓝标签给吓到，仔细思考过后我们发现维护两个东西就行了，即 $tot[i]$ 表示难度为i的题目出现了几次，而 $cnt[i]$ 表示出现了i次的难度题目种数。  
题目说每当所有难度的题目都出现了 $1$ 次就输出 $1$ 并且所有 $tot - 1$，   
也就是说我们只要当前所有难度的题目应该都至少出现了几次，直接模拟就好了：  
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int Len = 2e5 + 5;
int cnt[Len],n,m,tot[Len],a[Len],idx;//idx表示当前所有难度的题目需要出现多少次
int main()
{
	scanf("%d %d",&m,&n);
	for(int i = 1 ; i <= n; i ++) scanf("%d",&a[i]);
	idx = 1;
	for(int i = 1 ; i <= n; i ++)
	{
		tot[a[i]] ++;
		cnt[tot[a[i]]] ++;//为当前出现了tot[a[i]]次的种数+1
		if(cnt[idx] == m) //如果所有难度的题目都出现了
		{
			printf("1");
			idx ++;
		}
		else printf("0");
	}
	return 0;
}
```

---

## 作者：Yyxxxxx (赞：0)

如题，像俄罗斯方块一样，把一个数看成一列，如果出现一次，那就往上叠一小块，如果有一行满了，就消掉。 
![](https://cdn.luogu.com.cn/upload/image_hosting/7rvjp8ha.png?x-oss-process=image/resize,m_lfit,h_1280,w_2000)  
每次叠看一下有没有满一行，有输出$1$，没有输出$0$  
开桶记录每个数出现的次数，再开一个计数器计有几个数出现。    
如果出现的个数满$m$了，每个数的出现次数都减去$1$如果这个时候本数出现次数为$0$了，那计数器要减$1$。  
## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[100005];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}	
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c-48);c=getchar();}
	return x*f;
}
int main()
{
	int m=read(),n=read(),cnt=0,x;
	for(int i=1;i<=n;i++)
	{
		x=read();
		t[x]++;
		if(t[x]==1)cnt++;//只有在从0->1时才会改变计数器
		if(cnt==m)//如果满m
		{
			for(int j=1;j<=m;j++)
			{
				t[j]--;//逐个减一
				if(t[j]==0)cnt--;//有从1->0的就改变计数器
			}
			printf("1");
		}
		else printf("0");
	}
	return 0;
} 
```


---

## 作者：Erusel (赞：0)

直接考虑模拟

开一个vis数组统计每一个数出现的次数

如果之前未出现过，则出现的数的种类+1

当有n种不同的数出现时，暴力删除并统计此时出现数的种类

有人会问：这时间复杂度不是$O(nm)$的吗？难道n方过百万了？

因为只有**n种不同的数出现时**，我们才会暴力修改

普通的加入一个数只要$O(1)$的时间复杂度

暴力修改要$O(n)$的机会才能遇上一次

所以时间复杂度是$O(m)$

```
#include <bits/stdc++.h>

#define N 100005

using namespace std;

int n,m;
int vis[N];

int main() 
{
	scanf("%d%d",&n,&m);
	int cnt=0;
	for(int i=0;i<m;i++)
	{
		int x;
		scanf("%d",&x);
		if(!vis[x])cnt++;
		vis[x]++;
		if(cnt==n)
		{
			printf("1");cnt=0;
			for(int j=1;j<=n;j++)
			{
				vis[j]--;
				if(vis[j])cnt++;
			}
		}
		else if(cnt<n)printf("0");
	}
	printf("\n");




	return 0;
}
```

---

## 作者：Dream_It_Possible (赞：0)

不知简单做法，只知线段树。
#### 单点加

没读一个数，单点加一次

#### 区间最小

当[1,n]内没小于1的数，则可创建比赛，反之不能

#### code
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
struct Tree{
    int l, r;
	int mni;
} tr[500020];
int a[100005];
inline void read(int &a)
{
	int k=1; a=0; char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')k=-1; c=getchar();}
	while('0'<=c&&c<='9'){a=a*10+c-'0'; c=getchar();}
	a*=k;
}
void build(int x,int y,int i) 
{

    tr[i].l=x;
    tr[i].r=y;
    if(x==y)
	tr[i].mni=a[x];
    else
    {
        long long mid=(tr[i].l+tr[i].r)/2;
        build(x,mid,i*2);
        build(mid+1,y,i*2+1);
        tr[i].mni=min(tr[2*i].mni,tr[2*i+1].mni);
    }
}
void change(int q,int i) 
{
    if(tr[i].l==q&&tr[i].r==q)
    {
        tr[i].mni++;
    }
    else
    {
        long long mid=(tr[i].l+tr[i].r)/2;
        if (q<=mid)
        {
            change(q,i*2);
        }
        else if(q>mid)
        {
            change(q,i*2+1);
        }
        tr[i].mni=min(tr[2*i].mni,tr[2*i+1].mni);
    }
}
long long find_mni(int l,int r,int u)
{
	if (tr[u].l==l&&tr[u].r==r)
	{
		return tr[u].mni;
	}
	long long mid=(tr[u].l+tr[u].r)/2;
	if (mid>=r)
	{
		return find_mni(l,r,u*2);
	}
	else
	if (mid<l)
	{
		return find_mni(l,r,u*2+1);
	}
	else
	{
		return min(find_mni(l,mid,u*2),find_mni(mid+1,r,u*2+1));
	}
}
int main()
{
	int m,n,i,j,x,zl=0;
	cin>>m>>n; 
	for (i=1;i<=m;i++)
	a[i]=0;
	build (1,m,1);
	for (i=1;i<=n;i++)
	{
		read(x);
		change(x,1);
		//cout<<find_mni(1,m,1)<<endl;
		if (find_mni(1,m,1)>=1+zl)
		{
			cout<<"1";
			zl++;
		}
		else
		{
			cout<<"0";
		}
	}
	return 0;
}
```


---

## 作者：Ousmane_Dembele (赞：0)

暴力模拟就完事了

维护一个数组存目前有多少个i（未被删除），然后cnt维护目前有多少个不同的数，复杂度0（可过）

具体看代码注释

```
#include<iostream>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int cnt;
int a[100001];
int n,m,u;
int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        cin>>u;
        if(!a[u])cnt++;//如果本来没有就加上
        a[u]++;
        if(cnt==m){//全部有了
            cnt=0;
            for(int j=1;j<=m;j++){//一边减一边再统计一遍
                a[j]--;
                if(a[j])cnt++;
            }
            cout<<"1";//输出
        }else cout<<"0";
    }
}

```


---

