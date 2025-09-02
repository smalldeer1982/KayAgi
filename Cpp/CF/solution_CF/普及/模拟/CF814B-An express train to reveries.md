# An express train to reveries

## 题目描述

Sengoku still remembers the mysterious "colourful meteoroids" she discovered with Lala-chan when they were little. In particular, one of the nights impressed her deeply, giving her the illusion that all her fancies would be realized.

On that night, Sengoku constructed a permutation $ p_{1},p_{2},...,p_{n} $ of integers from $ 1 $ to $ n $ inclusive, with each integer representing a colour, wishing for the colours to see in the coming meteor outburst. Two incredible outbursts then arrived, each with $ n $ meteorids, colours of which being integer sequences $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ respectively. Meteoroids' colours were also between $ 1 $ and $ n $ inclusive, and the two sequences were not identical, that is, at least one $ i $ ( $ 1<=i<=n $ ) exists, such that $ a_{i}≠b_{i} $ holds.

Well, she almost had it all — each of the sequences $ a $ and $ b $ matched exactly $ n-1 $ elements in Sengoku's permutation. In other words, there is exactly one $ i $ ( $ 1<=i<=n $ ) such that $ a_{i}≠p_{i} $ , and exactly one $ j $ ( $ 1<=j<=n $ ) such that $ b_{j}≠p_{j} $ .

For now, Sengoku is able to recover the actual colour sequences $ a $ and $ b $ through astronomical records, but her wishes have been long forgotten. You are to reconstruct any possible permutation Sengoku could have had on that night.

## 说明/提示

In the first sample, both $ 1,2,5,4,3 $ and $ 1,2,3,4,5 $ are acceptable outputs.

In the second sample, $ 5,4,2,3,1 $ is the only permutation to satisfy the constraints.

## 样例 #1

### 输入

```
5
1 2 3 4 3
1 2 5 4 5
```

### 输出

```
1 2 5 4 3
```

## 样例 #2

### 输入

```
5
4 4 2 3 1
5 4 5 3 1
```

### 输出

```
5 4 2 3 1
```

## 样例 #3

### 输入

```
4
1 1 3 4
1 4 3 4
```

### 输出

```
1 2 3 4
```

# 题解

## 作者：da32s1da (赞：2)

~~输出一个排列~~

很明显，最多只有$2$个数不一样。

分情况讨论

- 若有一个数不一样，那么放完其他数后 没放的那个数就放到不一样的地方。

- 若有两个数不一样，那么只能是
 - 第一个位置放a排列，第二个位置放b排列。
 - 第一个位置放b排列，第二个位置放a排列。



```
#include<cstdio>
const int N=1050;
int a[N],b[N],c[N],vis[N];
int n,opt,wz,wz2;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		if(b[i]!=a[i]){
			if(!wz)wz=i,opt++;
			else wz2=i,opt++;
            //找到不一样的地方
		}
	}
	for(int i=1;i<=n;i++)
	if(i!=wz&&i!=wz2)
	vis[a[i]]=1,c[i]=a[i];
    //其他地方原样放置
	if(opt==1){
		for(int i=1;i<=n;i++)
		if(!vis[i])c[wz]=i;
        //一个地方不同，找到没放的数 放上
	}else{
		if(!vis[a[wz]]&&!vis[b[wz2]])c[wz]=a[wz],c[wz2]=b[wz2];
		else c[wz]=b[wz],c[wz2]=a[wz2];
        //分两种情况特判
	}
	for(int i=1;i<=n;i++)printf("%d ",c[i]);
}
 ```

---

## 作者：狸狸养的敏敏 (赞：1)

题目的意思直接把做法提醒的很清楚了

要构造一个序列P，让他和A，B序列都有一个位置不同，而且A，B之间还至少有一个位置不同

上面那句话，简单整理可以提取出以下信息：

1. A和B相同的部分，一定也是P序列的相同部分
2. A和B之间最多存在2个不同位置

把上述信息的整合再做分析，易得

1. 如果A和B之间存在且仅存在1个不同位置，那么这个位置的数一定是其他位置中没出现的数

2. 如果A和B之间存在且仅存在2个不同位置，那么这两个位置的数一定来自A，B两个序列

关于上述信息的第二条，这两个位置到底是从A取还是从B取还无法确定，但是由于题目要求的序列P是一个排列，那么相同位置出现过的数字不能被挑选到最终的答案中，因此，只需要维护1-n中哪些数字出现过即可

用了一点小技巧，让代码看上去更短

```
#include<bits/stdc++.h>
#define reg register
#define i64 long long
using namespace std;
int read(){int x=0,f=0;char ch=0;while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch))(x*=10)+=(ch^48),ch=getchar();return f?-x:x;}
void Ot(int x){if(x<0)putchar('-'),x=-x;if(x>=10)Ot(x/10);putchar(x%10+48);}
void Print(int x,char til='\n'){Ot(x);putchar(til);}
const int MAXN=1010;
vector<int>G;set<int>st;
int n,sum;
int a[MAXN],b[MAXN],p[MAXN];
bool vis[MAXN];
signed main(){
	n=read();sum=(1+n)*n/2;
	for(reg int i=1;i<=n;i++)a[i]=read();
	for(reg int i=1;i<=n;i++)b[i]=read();
	for(reg int i=1;i<=n;i++){
		if(a[i]!=b[i])G.push_back(i);
		else p[i]=a[i],sum-=a[i],vis[a[i]]=1;
	}
	if(G.size()==2)
		if(vis[a[G[0]]]|vis[b[G[1]]])p[G[0]]=b[G[0]],p[G[1]]=a[G[1]];
		else p[G[0]]=a[G[0]],p[G[1]]=b[G[1]];
	else p[G[0]]=sum;
	for(reg int i=1;i<=n;i++)Print(p[i],' ');
	return 0;
}

```

---

## 作者：龙翔凤翥 (赞：1)

## 分析:
#### 1. a ,b 两个序列中仅有一个数不相同，那么就找出1~n中没有出现过的数填在数不同的位置就行。 
#### 2. a ,b 中有两个数不同，找不同位置对角线上的数，判断是否1~n重复就好。
```cpp
#include<bits/stdc++.h>
#define RN register int 
using namespace std;
int main()
{
    int n;
    int a[2005],b[2005];
    while(~scanf("%d",&n))
    {
        int c[1005],d[1005];
        map<int,int>M;
        for(RN i=1; i<=n; i++)
            scanf("%d",&a[i]);
        for(RN i=1; i<=n; i++)
            scanf("%d",&b[i]);
        int k=0;
        for(int i=1; i<=n; i++)
        {
            if(a[i]==b[i])
            {
                c[i]=a[i];
                M[a[i]]++;//判断哪些数出现过
            }
            else
            {
                d[k++]=i;//判断出现不同数的位置
            }
        }
        if(k==1)//如果只有一处不同，那么只要找到1~n缺失的那个数
        {
            for(RN i=1;i<=n;i++)
            {
                if(M[i]==0)
                	c[d[0]]=i;
            }
        }
        else
        {
            int t1=d[0];
            int t2=d[1];
            //cout<<t1<<" "<<t2<<endl;
            if(M[a[t1]]==0&&M[b[t2]]==0)//避免选的数已经出现在1~n中
            {
                c[t1]=a[t1];
                c[t2]=b[t2];
            }
            else
            {
                c[t1]=b[t1];
                c[t2]=a[t2];
            }

        }
        for(RN i=1; i<=n; i++)
        {
            if(i==1)
                printf("%d",c[i]);
            else
                printf(" %d",c[i]);
        }
        printf("\n");
    }
    return 0;
}

```


---

## 作者：Tx_Lcy (赞：0)

这是一道简单题。
## 思路
首先我们发现，$\verb!a!$ 序列和 $\verb!b!$ 序列至多有两个数不一样，至少有一个数不一样。否则无解，而题目又保证有解，所以题目等于多了一个条件：**$\verb!a!$ 序列和 $\verb!b!$ 序列至多有两个数不一样，至少有一个数不一样。**

既然这样我们就可以开始分类讨论了，我们首先可以确定所有 $a_i=b_i$ 的位置的 $p_i$。**若只有一个数不一样**，我们直接把剩下的那个数放上去即可。**若有两个数不一样，我们要再次分类**，分四种情况，具体看代码。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=2e5+10;
int a[N],b[N],n;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n;
    for (rint i=1;i<=n;++i) cin>>a[i];
    for (rint i=1;i<=n;++i) cin>>b[i];
    set<int>s;vector<int>q;
    for (rint i=1;i<=n;++i) s.insert(i);
    for (rint i=1;i<=n;++i)
    	if (a[i]==b[i]) s.erase(a[i]);
    	else q.push_back(i);
	if (s.size()==1){
    	for (rint i=1;i<=n;++i)
    	    if (a[i]==b[i]) cout<<a[i]<<' ';
    	    else cout<<(*s.begin())<<' ';
    	return cout<<'\n',0;
	}else{
		if (a[q[0]]==(*s.begin()) && b[q[1]]==(*(++s.begin()))){
			a[q[0]]=(*s.begin()),a[q[1]]=(*(++s.begin()));
		    for (rint i=1;i<=n;++i) cout<<a[i]<<' ';
		    cout<<'\n';
		}//第一种情况，前面的 a 等于剩下小的那个数，后面的 b 等于剩下大的那个数，后面以此类推
                else if (a[q[1]]==(*s.begin()) && b[q[0]]==(*(++s.begin()))){
			a[q[1]]=(*s.begin()),a[q[0]]=(*(++s.begin()));
		    for (rint i=1;i<=n;++i) cout<<a[i]<<' ';
		    cout<<'\n';
		}else if (b[q[1]]==(*s.begin()) && a[q[0]]==(*(++s.begin()))){
			b[q[1]]=(*s.begin()),b[q[0]]=(*(++s.begin()));
		    for (rint i=1;i<=n;++i) cout<<b[i]<<' ';
		    cout<<'\n';
		}else if (b[q[0]]==(*s.begin()) && a[q[1]]==(*(++s.begin()))){
			b[q[0]]=(*s.begin()),b[q[1]]=(*(++s.begin()));
		    for (rint i=1;i<=n;++i) cout<<b[i]<<' ';
		    cout<<'\n';
		}
	}
    return 0;
}
```

---

## 作者：happybob (赞：0)

注意本题输出的是排列而非序列！

考虑分类讨论，设 $c$ 表示 $\sum_{i=1}^n [a_i \neq b_i]$，即 $a_i \neq b_i$ 的 $i$ 的个数，$ans_i$ 表示答案。

若 $c = 1$，那么对于 $a_i = b_i$，则 $ans_i = a_i$，对于唯一一个 $a_i \neq b_i$，只需要从 $1$ 到 $n$ 循环，找到一个 $cnt_j$ 为 $0$ 的 $j$，那么 $ans_i = j$，$cnt_i$ 表示 $i$ 在答案排列中出现次数。

若 $c = 2$，那么对于 $a_i = b_i$，则 $ans_i = a_i$，对于两个  $a_i \neq b_i$，设这两个 $i$ 分别为 $x$ 和 $y$，分别测试 $ans_x = a_x$ 或 $ans_x = b_x$，找出可行解即可。

代码：

```cpp
#pragma GCC optimize("-Ofast")
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1005;

int n, a[N], b[N], cnt, cnts[N], ans[N];

inline int read()
{
	register char ch(getchar());
	register int x(0);
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++)
	{
		b[i] = read();
		cnt += a[i] != b[i];
	}
	if (cnt == 1)
	{
		for (int i = 1; i <= n; i++)
		{
			if (a[i] == b[i]) ans[i] = a[i], cnts[a[i]]++;
		}
		for (int i = 1; i <= n; i++)
		{
			if (a[i] != b[i])
			{
				for (int j = 1; j <= n; j++)
				{
					if (!cnts[j])
					{
						ans[i] = j;
						break;
					}
				}
			}
		}
	}	
	else if (cnt == 2)
	{
		bool f = false;
		for (register int i = 1; i <= n; i++)
		{
			if (a[i] == b[i]) ans[i] = a[i], cnts[a[i]]++;
		}
		for (register int i = 1; i <= n; i++)
		{
			if (a[i] != b[i])
			{
				if (!cnts[a[i]])
				{
					ans[i] = a[i];
					cnts[a[i]]++;
				}
				else
				{
					if (!cnts[b[i]])
					{
						ans[i] = b[i];
						cnts[b[i]]++;
					}
					else
					{
						for (int j = i - 1; j >= 1; j--)
						{
							if (a[j] != b[j])
							{
								if (ans[j] == a[j])
								{
									cnts[a[j]]--;
									ans[j] = b[j];
								}
								else ans[j] = a[j], cnts[b[j]]--;
								break;
							}
						}
						if (!cnts[b[i]])
						{
							ans[i] = b[i];
							cnts[b[i]]++;
						}
						else if (!cnts[a[i]])
						{
							ans[i] = a[i];
							cnts[a[i]]++;
						}
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}
```


---

## 作者：wz441135118 (赞：0)

思维好题。

保证一定有解大大降低了代码难度。

显然最多有两个位置不同不然根据鸽巢原理一定存在一个序列不同位置超过一个。

然后大力分类讨论：

- 仅有一个位置不同。此时其余位置就是排列中对应位置。否则一定存在一个序列不合法（要不一个序列超过一个要不一个序列没有）。然后将没有用过的那个数丢到这个位置即可。
- 有两个位置不同。此时其余位置也是排列中对应位置，分析过程类似。构造方案就枚举某个序列中相同的位置，也就两种情况。

时间复杂度 $O(n)$。

***code:***

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1005
#define For(i,x,y)for(i=x;i<=(y);i++)
int vis[N];
int a[N],b[N],c[N];
int main()
{
	int n,i,x,y;
	x=y=0;
	cin>>n;
	For(i,1,n)cin>>a[i];
	For(i,1,n)
	{
		cin>>b[i];
		if(a[i]!=b[i])if(x)y=i;
		else x=i;
	}
	For(i,1,n)
	if(i!=x&&i!=y)c[i]=a[i],vis[a[i]]=1;
	if(!y)
	For(i,1,n)
	if(!vis[i])
	{
		c[x]=i;
		break;
	}
	else;else
	{
		if(!vis[a[x]]&&!vis[b[y]])c[x]=a[x],c[y]=b[y];
		else c[y]=a[y],c[x]=b[x];
	}
	For(i,1,n)cout<<c[i]<<' ';
	return 0;
}
```

---

## 作者：tongziyu (赞：0)

## 题目大意
题目的意思描述中已经说的很明确了，在这里提醒一句，要求构造的 $p$ 是**排列**而不是**序列**，意味着 $p$ 中的数字**不能重复**，没仔细读题的后果见下：
![](https://cdn.luogu.com.cn/upload/image_hosting/w3ggpg3v.png)


------------

## 解法及思路
由于构造的排列 $p$ 需要与两个给出的序列有且仅有一个元素不同，因此我们可以容易地得到，给出的两个序列至多只有两个元素不同。

为方便，我们令给出的两个序列分别为 $a$ 和 $b$。首先我们遍历一下 $a$，$b$ 两个序列，利用一个变量 $cnt$ 统计两序列不同元素的数量，并且把这些元素在序列中的位置用一个 $flag$ 数组标记下来（如果你愿意，其实也可以不用）。在遍历的过程中，我们同时构造排列 $p$。对于排列 $p$ 的第 $i$ 个元素，如果 $a[i]=b[i]$ ，那么由于 $a$，$b$ 两序列本身不完全相同，且排列 $p$ 分别对于 $a$，$b$ 两序列只有一个元素不同，因此可得 $p[i]=a[i]=b[i]$。同时我们将每个数字是否已在排列 $p$ 中出现过用一个 $used$ 数组记录。


遍历完后我们要分**两种情况**进行处理:

### 第一种情况：$cnt=1$ 即两序列只有一个元素不同。
这种情况只需要再遍历一遍 $a$，$b$ 两序列，找到不同元素所在的位置 $i$，然后将$p$排列的这个位置用一个**既不等于 $a[i]$，又不等于 $b[i]$，还没有在排列 $p$ 中出现过**的元素补上即可。

### 第二种情况：$cnt=2$ 即两序列有两个元素不同。
这种情况就相对较为麻烦。还需要遍历一遍 $a$，$b$ 两序列，当我们找到第一个不同元素所在的位置 $t1$ 时，我们先用 $a[t1]$ 将 $p$ 的该位置补上；之后当我们找到第二个不同元素所在的位置 $t2$ 时，再用 $b[t2]$ 将 $p[t2]$ 补上，然后停止遍历。但是这样做**可能会造成元素的重复**，与题意不符。因此我们还需要再遍历一遍 $p$，如果其中元素出现重复，就将 $p[t1]$ 取 $b[t1]$，$p[t2]$ 取  $a[t2]$。这样就可以达到**去重**的目的。

接下来只需要输出 $p$ 即可。

## Code:
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std; 
const int N=1001;
long long a[N],b[N],p[N];
long long n,cnt,x,t1,t2;
bool flag[N],used[N];
int main()
{
    scanf("%d",&n);
    for (register int i=1; i<=n; i++)
	{
		scanf("%d",&a[i]);
    } 
    for (register int i=1; i<=n; i++)
	{
    	scanf("%d",&b[i]);
    } 
    for (register int i=1; i<=n; i++)
	{
        if (a[i]==b[i])
		{
		 	p[i]=a[i];
		} //如果两序列某位置上的数字相同，就在构造序列的该位置放相同的数字 
        else
		{
            flag[i]=1;//数字不同的位置打好标记 
            cnt++;//统计两序列数字不同位置的个数 
        }
    }
    for (register int i=1; i<=n; i++)
	{
		if (!flag[i])
		{
	 		used[p[i]]=1;
		}
	}//标记某数字是否使用过 
    for (register int i=1; i<=n; i++)
	{
        if (flag[i])//找到数字不同的位置，分类执行操作 
		{
			if(cnt==1)
			{
				for (register int j=1; j<=n; j++)
			 	{
                	if (j!=a[i] && j!=b[i] && used[j]!=1)//当只有一个位置不同时，需要取一个没出现在a,b两序列和p排列中的数字
					{
                   	  	p[i]=j;
                  	  	break;
               		}
            	}
            	break;
			}
			else//否则继续分类讨论 
			{
				if (x==0)//如果此前没有遇到过数字不同的位置 
	            {
	                p[i]=a[i];
	                x=1; 
	                t1=i;//记录下当前位置 
	            }
	            else
	            {
	                p[i]=b[i];
					t2=i;//记录位置 
	                break; //第二次取完后可直接退出 
	            }
			}
        }
    }
    if(cnt==2) //当两序列有两个上的数字不同时，通过以上方法构造出的序列可能有重复，需要去重。 
	{
		for (register int i=1; i<=n; ++i)  
		{
			for(register int j=1; j<i; ++j) 
			{
				if(p[i]==p[j]) 
				{
					if(x==1)
					{
						p[t1]=b[t1];
						p[t2]=a[t2];
						break;
					}
					else 
					{
						p[t1]=a[t1];
						p[t2]=b[t2];
						break;
					}
				}
			}
		}
	} 
  
    for (register int i=1; i<=n; i++)
	{
    	printf("%d ",p[i]);
    }
    return 0; 
}

```


---

## 作者：mot1ve (赞：0)

恐成此题最丑最长代码。。

不过思路极其简单，分类讨论就行了。代码里见。

```
//两个序列一样的元素是不动的
#include<bits/stdc++.h>
using namespace std;
int temp,temp1,temp2,x,y,cnt,n;
int a[1010],b[1010];
map<int,bool> mapp;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
	}
	for(int i=1;i<=n;i++)//分类讨论，只有一个不同的还是有两个 
	{
		if(a[i]!=b[i])
		cnt++;
		if(a[i]==b[i])
		mapp[a[i]]=1;//如果两个数一样一定存在于生成的序列中 
	}
	if(cnt==1)//只有一个不同，不同的位置补上不重复的就行 
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=b[i])//找到这个不同的位置了 
			{
				mapp[a[i]]=1;
				mapp[b[i]]=1;//这两个数不能选。 
				temp=i;
				for(int j=1;j<=n;j++)
				{
					if(!mapp[j])//如果这个数没出现过，这个位置就输出这个数
					{
						x=j;
						break;
					} 
				}
				break;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(i==temp)
			printf("%d ",x);
			else printf("%d ",a[i]);
		}
		return 0;
	}
	else if(cnt==2)
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=b[i])
			{
				temp1=i;//第一个位置不同的地方
				if(!mapp[a[i]])//选生成序列里没出现过的数 
				{
					x=a[i];
					mapp[a[i]]=1;
					break;
				}
				else if(!mapp[b[i]])
				{
					x=b[i];
					mapp[b[i]]=1;
					break;
				}
			}
		}
		for(int i=temp1+1;i<=n;i++)
		{
			if(a[i]!=b[i])
			{
				temp2=i;
				if(!mapp[a[i]])
				{
					y=a[i];
					break;
				}
				else if(!mapp[b[i]])
				{
					y=b[i];
					break;
				}
			} 
		}
		if(y==0)//y没得可选了，第一次重新选，选跟b一样的不选跟a一样的 
		{
			x=b[temp1];
			y=a[temp2];
		} 
		for(int i=1;i<=n;i++)
		{
			if(i==temp1)
			printf("%d ",x);
			else if(i==temp2)
			printf("%d ",y);
			else printf("%d ",a[i]);
		}
		return 0;
	} 
	return 0;
} 
```

---

