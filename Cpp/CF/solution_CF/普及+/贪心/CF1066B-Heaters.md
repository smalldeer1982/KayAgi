# Heaters

## 题目描述

## 题意描述：
$Vova$先生的家可以看作一个$n \times 1$的矩形，寒冷的冬天来了，$Vova$先生想让他的家里变得暖和起来。现在我们给你$Vova$先生家的平面图，其中$1$表示这个地方是加热炉，0表示这个地方什么也没有。所有加热器都有一个加热半径$r$,一个位于$a_i$加热器可以加热[$a_i-r+1,a_i+r-1$]的范围。现在，$Vova$先生想让他的整个家都变得暖和，一开始所有的加热器都是关闭的，请你求出$Vova$先生最少要开几个加热器才能使整个家变得暖和

## 样例 #1

### 输入

```
6 2
0 1 1 0 0 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 3
1 0 0 0 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 10
0 0 0 0 0
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
10 3
0 0 1 1 0 1 0 0 0 1
```

### 输出

```
3
```

# 题解

## 作者：wmrqwq (赞：6)

看到其他题解都写的是一个贪心思路，那么我在这里提供一个新的贪心思路。

首先我来提供一组样例，

输入：

```
6 4
1 0 1 1 1 0
```

输出：

```
1
```

对于这个样例，容易看出，我们只需要选择第三个加热器就能使得整个屋子都被加热了，然后我们就可以想一个贪心策略，那就是**先把所有加热器都打开**，然后在从左到右依次判断这个加热器关闭后整个屋子是否依然被加热，如果依然被加热，则可以关掉这个加热器，反之则不能关掉这个加热器。

那么这个时候肯定有人就要问了，正确性呢？

由于判断了整个屋子是否依然被加热的情况，因此若可以使整个屋子被加热，则最后屋子的状态一定均是被加热的，而正因为加上了这个判断，因此选择的加热器也依然是最优的，因此这样贪心一定是正确的。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[1010],b[1010],sum,pd;
void init(long long l,long long r)
{
	pd=0;
	for(int i=l;i<=r;i++)
	{
		b[i]--;
		if(!b[i])
			pd=1;
	}
	if(pd)
	{
		for(int i=l;i<=r;i++)
			b[i]++;
		return ;
	}
	sum--;
}
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==1)
		{
			sum++;
			for(int j=max(1ll,i-m+1);j<=min(n,i+m-1);j++)
				b[j]++;
		}
	}
	for(int i=1;i<=n;i++)
		if(!b[i])
		{
			cout<<-1;
			QwQ;
		}
	for(int i=1;i<=n;i++)
		if(a[i])
			init(max(1ll,i-m+1),min(n,i+m-1));
	cout<<sum;
	QwQ;
}

```

---

## 作者：YB_is_short (赞：6)

一道水水的贪心题

首先先记录每个点左边离它最近的加热炉的位置

然后可以用一个指针表示当前可照亮的点的位置，然后找到离它最远（可以使照亮的距离更远）但可以照亮它后面的点的位置

然后一直这样枚举下去，求出答案

但要注意在求的过程中判断无解情况

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2020
int n,r,a[N];
int main()
{
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i])a[i]=i;else a[i]=a[i-1];
	}
	for(int i=n+1;i<=n+r;i++)a[i]=a[i-1];
	int x=a[r]+r-1,tot=1;
	while(x<n&&tot<N)tot++,x=a[x+r]+r-1;
	if(a[r]==0||tot==N){printf("-1\n");return 0;}
	printf("%d\n",tot);
	return 0;
}
```

---

## 作者：爱滑稽的蒟蒻 (赞：4)

~~说实话我并不是很懂楼上的奆佬在说啥……~~

先看一下题意：

	有一堆加热器，加热器的加热范围是r
    求最少打开几个可以加热整个范围
    
这很显然是一道贪心，既然我们要保证最少，那么我们就需要放的

加热器个数是最优的。

简单来说，我们找到第一个加热器后，最优的方法就是在这个加热器位置

的右边2*r-1处再放一个加热器，这时候每个位置都只有一个加热器在加热

这就满足了最优的条件

那么如果这个位置没有加热器呢？

那只有退一步走，找到这个最优位置左边的第一个加热器就是当前最优的位置

如果找不到，那么就不可能成功，输出-1

看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	while(c<'0'||c>'9') {if(c=='-') f=1;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(f) x=-x;
	return x;
}//快读 
inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}//快写 
int a[maxn];
bool flag[maxn];//标记数组，表示这个位置是否放了加热器 
int main()
{
	int n=read(),r=read();
	for(int i=1;i<=n;i++)
	a[i]=read();
	int ans=0;
	int num=0;
	for(int i=r;;)
	{
		if(a[i]) {ans++;flag[i]=1;if(i+r-1>=n) break;i=i+2*r-1;continue;}//如果当前最优位置有加热器，就直接取 
		while(!a[i]&&i&&!flag[i])//如果没有，就往左找 
		i--;
		if(flag[i]||i==0) {puts("-1");return 0;}//如果找完后找到的位置已经放过加热器了或者根本就没有加热器，那么就不可能成功 
		ans++;flag[i]=1;if(i+r-1>=n) break;i=i+2*r-1;//找到了，就执行一样的操作 
	}
	write(ans);//输出结果 
}
```


写题解不易，看了就顺手点个赞吧~

---

## 作者：_xbn (赞：3)

考虑贪心，在读入时我们可以先预处理出每个加热器向左和向右能加热的最远

距离，接着，我们模拟一个贪心的人的选择，对于一个点能被多个加热器

加热，我们选择离他最远的能加热它的加热器，这样能让最多的加热器空闲，

即最少的加热器工作。

最后，如果第一个加热器不能加热第一个点或最后一个加热器不能加热最后

一个点，则判为无解。

贴上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20002;
int n,m,p,q,t,k,a[N],b[N],c[N],d[N],ans,sum,tot,cnt,f[N];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==1)
		{
			m++;
			c[m]=i-k+1;
			d[m]=i+k-1;
		}
	}
	if(c[1]>1||m==0||d[m]<n)
	{
		cout<<"-1"<<endl;
		return 0;
	}
	p=1;
	while(c[p]<=1)p++;
	ans=1;
	for(int i=p-1;i<=m;i++)
	{
		int j=i+1;
		if(d[i]>=n)
		{
			cout<<ans<<endl;
			return 0;
		}
		if(c[j]>=d[i]+2)
		{
			cout<<"-1";
			return 0;
		}
		while(c[j]<=d[i]+1)
		{
			
			if(d[j]>=n)
			{
				cout<<ans+1<<endl;
				return 0;
			}
			j++;
		}
		ans++;
		i=j-2;
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：JohnJoeZhu (赞：2)

$\text{Fixed in 2021}$：$N$年以后才发现**wtcl**，更正了代码，请放心食用。

### 水题警告，前方高能
先说明，这就是一道简单的贪心题 ~~（为什么是green）~~
### 怎么贪
为了使每一格都被暖气覆盖，且打开加热器数量最少，那我们可以想

尽可能使打开的加热器发挥最大作用（加热最多的格子）

那么，为了满足以上条件，我们又可以想

对于每一个需要加热的格子，尽可能选择里它右侧最远的加热器，迫不得已时再选择左边的加热器，才可以使加热器发挥最大作用

什么条件下不可以实现呢？

如果过程中有一个点无法被加热，那么就结束代码……
### 代码实现
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,r,a[1010],ans=0;
bool vis[1010];
int main()
{
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        if(vis[i]==0)//需要加热 
        {
            for(int j=min(n,r+i-1);j>=max(1,i-r+1);j--)
                if(a[j]==1)
                {
                    ans++;
                    for(int k=max(1,j-r+1);k<=min(j+r-1,n);k++)
                        vis[k]=1;//已加热 
                    break;//完成加热，退出循环 
                }
            if(vis[i]==0) //无法加热 
            {
                printf("-1");
                return 0;//代码再见 
            }
        }
    printf("%d",ans);
    return 0;
}
```
因为本题较为简单，所以……

实在是易于理解，我也就不想选择太多的优化了

错误原因：加热器自己不开是没有办法加热自己的位置的

---

## 作者：ztz11 (赞：2)

### 还是很水

因为我们要尽可能少，所以我们要用贪心的思想

我们从最左边开始扫，扫到一个没有被加热的点，我们就以这个点为起点向右扫，扫到能加热他的离他最远的一个加热器打开  

**（贪心的正确性在于这个加热器离他最远且能将它加热，如果选更近的则不更优，选更远的就加热不了他了）**  

然后将该加热器能加热的范围内的点打标记，继续扫下去即可

最坏时间复杂度$O(N^2)$

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rii register int i
#define rij register int j
using namespace std;
int n,r,jz[4005],jrq[4005],bj[4005],ans;
int main()
{
	int cnt=0;
	scanf("%d%d",&n,&r);
	for(rii=1;i<=n;i++)
	{
		scanf("%d",&jz[i]);
		if(jz[i]==1)
		{
			cnt++;
			jrq[cnt]=i;
		}
	}
	for(rii=1;i<=n;i++)
	{
		if(bj[i]==0)
		{
			int wz=0;
			for(rij=1;j<=r;j++)
			{
				if(i+j-1<=n)
				{
					if(jz[i+j-1]==1)
					{
						wz=max(wz,i+j-1);
					}
				}
				if(i-j+1>=1)
				{
					if(jz[i-j+1]==1)
					{
						wz=max(wz,i-j+1);
					}
				}
			}
			for(rij=1;j<=r;j++)
			{
				if(wz-j+1>0)
				{
					bj[wz-j+1]=1;
				}
				bj[wz+j-1]=1;
			}
			ans++;
			if(wz==0)
			{
				printf("-1");
				return 0;
			}
		}
	}
	printf("%d",ans);
}
```

---

## 作者：星落云川 (赞：1)

这是道贪心题，本质上和 [P1325 雷达安装](https://www.luogu.com.cn/problem/P1325) 是极其相似的。只不过在细节处理上稍有不同。
  
题目要求最少打开几个加热器才能使房间全部加热，我们自然尝试用贪心的方法解决本题。  
  
每个加热器的加热半径 $r$ 都是相同的，对于房间内每个坐标 $i$ 而言，其若要被加热，则在区间 [$i-r+1$,$i+r-1$] 内必须打开至少一个加热器。对于房间内的每个坐标，我们可以求出其被加热时，需放置加热器位置的左右区间，并用结构体存储。  
  
现在，对于房间内的每个坐标而言，其都对应了一个区间。我们的任务就是用最少的点来使每个区间内都包含了至少一个点。本题即转变为经典的区间取点问题，即可利用贪心思想解决。  
  
需要注意的是，P1325 中的雷达可以随意布置在任何位置，但本题中加热器的坐标是给定的。因此，我们在选择加热器时必须从右区间向左搜索，找到的第一个加热器就是要打开的加热器。如果搜索完毕后没有找到加热器，就说明该区间内没有点，自然无法加热整个房间。  
  
另外一点需要注意的是，不同于 P1325，房间的大小是有限的，以起始坐标为1，则任何一点的坐标都在区间 [1,$n$] 内。在上文中，我们计算各点所需加热器的区间范围是可能超出房间大小的，在后续搜索过程中就有可能导致数组越界，酿成悲剧。
  
最后奉上代码，很丑，见笑(っ﹏-) .｡
```cpp
#include<iostream>
#include<stdlib.h>
#include<algorithm>
using namespace std;
typedef struct anode
{
	int l, r;
}aNode;
bool cmp( aNode x, aNode y )
{
	if( x.r != y.r ) return x.r < y.r;
	else return x.l > y.l;
}
aNode a[1005]={};
int room[1005]={};
int main()
{
	int n, r, flag=1, now=-1, ans=1;
	cin >> n >> r;
	for( int i=1; i<=n; i++ ){
		cin >> room[i];
		a[i].r = i+r-1 < n ? i+r-1 : n; //该点被加热时 加热器能够放到的最右坐标
		a[i].l = i-r+1 > 1 ? i-r+1 : 1; //最左坐标
	}
	sort( a+1, a+n+1, cmp ); //转换为区间取点问题
	for( int i=a[1].r; i>=a[1].l; i-- )
		if( room[i] == 1 ){ //区间取点问题 第一个点必须给右边界最小的区间
			now = i;
			break;
		}
	if( now == -1 ) flag=0; //第一个区间都满足不了 还加热个鬼
	for( int i=1; i<=n && flag; i++ ){
		if( a[i].l > now ){ //要开新的加热器了
			ans++;
			flag = 0; //万一找不到新加热器就说明加热整个房子不可能
			for( int loc=a[i].r; loc>=a[i].l; loc-- )
				if( room[loc] == 1 ){
					flag = 1;
					now = loc;
					break;
				}
		}
	}
	if( flag ) cout<< ans << endl;
	else cout << "-1" << endl;
	system("pause");
	return 0;
}
```


---

## 作者：zhou_ziyi (赞：1)

### Solution

很显然是一道贪心的题目。

我们预处理得到每个点左边离它最近的加热炉的位置，然后可以用一个指针表示当前可照亮的点的位置，然后找到离它最远但可以照亮它。

后面的点的位置，然后一直这样暴力枚举下去，用 $tot$ 进行记录，最后输出 $tot$ 及答案。

但要注意在求的过程中判断无解情况。

### Code
```cpp
#include <cstdio>
using namespace std;
const int MAXN = 2005;
int n, r, a[MAXN];
int main() {
    scanf("%d %d", &n, &r);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), a[i] = a[i] ? i : a[i - 1];
    for (int i = n + 1; i <= n + r; i++)
        a[i] = a[i - 1];
    int x = a[r] + r - 1, tot = 1;
    while (x < n && tot < MAXN)
        tot++, x = a[x + r] + r - 1;
    if (!a[r] || tot == MAXN) {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", tot);
    return 0;
}
```



---

## 作者：ckk11288 (赞：1)

**贪心**

一道适合练手和增强信心的绿题，本蒟蒻没看题解就切了，可以说是里程碑了。

这里我的**贪心策略**是：先排好序，把加热范围更广的由小到大排序，其次把左端点从小到大排序。接着用循环进行贪心：简单来说就是在能与上一个加热器“完美配合”的情况下选择加热范围更广的，那么所需的加热器也会更少。

代码有注释，放心食用。

**Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r,x[1001],ans,cnt,vis[1010101],v[1001];//vis数组判断该点是否已经被加热，v数组判断这个加热器是否已经打开了
struct node{
	int l,r;//l左端点，r右端点
}a[1001];
bool cmp(node aa,node bb)
{
	if(aa.r!=bb.r)return aa.r<bb.r;
	return aa.l<bb.l;
}//排序方法，上文有说明
int main()
{
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x[i]);
		if(x[i]==1)//有加热器
		{
			a[++cnt].l=i-r+1;
			a[cnt].r=i+r-1;//依照题意存入左端点和右端点
		}
	}
	sort(a+1,a+1+cnt,cmp);//排序
	for(int i=1;i<=n;i++)
	{
		if(vis[i])continue;//这个地方已经被加热了
		ans++;//新增一个加热器
		int k=0,maxn=0;
		for(int j=1;j<=cnt;j++)
		{
			if(!v[j]&&a[j].r>maxn&&a[j].l<=i)//选择能不留空隙的，范围最广的加热器。
			{
				k=j;
				maxn=a[j].r;//选择它
			}
		}
		v[k]=1;//选出适合的加热器
		for(int j=a[k].l;j<=a[k].r;j++)
		{
			vis[j]=1;//将它能加热的一段标记为1，即已加热
		}
	}
	for(int i=1;i<=n;i++)
	if(vis[i]==0)
	{
		cout<<-1;
		exit(0);
	}//若无法加热整个家，输出-1
	printf("%d",ans);//否则输出答案
	return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

## 贪心 + 模拟（双指针优化）

首先，从左至右找到第一个加热炉（或者是第一个没有被加热的点）。

以它再向右找，直到找到了第二个加热炉位置，计数器加一，并把它打开，一直往返贪心即可。

时间复杂度 $O(nlogn)$，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, r;
int a[N], b[N], m, ans;
int main(){
  cin >> n >> r;
  for(int i = 1;i <= n;i++){
    cin >> a[i];
    if(a[i]){
      b[m++] = i;
    }
  }
  int i = 1, j = 0;
  while(i <= n){
    int p = -1;
    for(int k = j;k < m && b[k] - r + 1 <= i; k++){
      if(i <= b[k] + r - 1){
        p = k;
      }
    }
    if(p == -1){
      cout << -1 << endl;
      return 0;
    }
    i = b[p] + r;
    j = p + 1;
    ans++;
  }
  cout << ans;
  return 0;
}

```
直接切掉！！

---

