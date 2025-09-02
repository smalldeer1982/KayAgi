# Toy Sum

## 题目描述

小克里斯非常热衷玩具积木，然而他的老师想要他好好学习去解决更多的问题，因此老师决定戏弄下克里斯。

现有$s$个积木块在克里斯的玩具箱里，每个积木块拥有$1$~$s$中的唯一编号，克里斯的老师选出一些积木保管（积木组成的集合为$X$），如果克里斯能从剩余的积木中选出一些积木组成的集合$Y$使得下面条件成立，那么老师将会还给他之前拿的积木。  

条件要满足：
$$\sum\limits_{x\in X}(x-1)=\sum\limits_{y\in Y}(s-y)$$

举例来说，考虑当$s=8$的时候老师拿了$1,4,5$号的积木，那么克里斯可以挑取剩下积木中的$3,6$号作为问题的答案。也就是：$(1-1)+(4-1)+(5-1)=(8-3)+(8-6)=7$。  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF405D/06454f577b0ffc63bab3fabb48dbf59919f0ef01.png)

现在克里斯一共有$s=10^6$块积木，请你帮助他完成这个谜题。

## 样例 #1

### 输入

```
3
1 4 5
```

### 输出

```
2
999993 1000000```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
1
1000000 
```

# 题解

## 作者：米奇奇米 (赞：1)

## 题解-CF405D Toy Sum
### $1.1$题目意思
让你求出一个集合$B$使得，$\sum(1..(Ai-1))=\sum(1..(1e6-Bi))$ 并且$A$和$B$没有重复的数字$(Ai,Bi<=S)$

### $2.1$考虑贪心
我们每次对一个$Ai$，匹配 $Bi=S-Ai+1$，但是不是每一个$Bi$都是没有出现过的，对于不能成功匹配的累加个数。然后先$O(n)$扫一遍，处理处不能匹配的个数$gs$。然后我们就很简单$O(S)$扫一遍，对于一个数如果$(i)$以及与他配对$(S-i+1)$都没有在$A$集合中出现过，$gs$每次减去二即可，输出是一边做一边输出的。

### $3.1$代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar

inline int read(){
	int x=0,fl=1;char ch=gc();
	for(;ch<48||ch>57;ch=gc())if(ch=='-')fl=-1;
	for(;48<=ch&&ch<=57;ch=gc())x=(x<<3)+(x<<1)+(ch^48);
	return x*fl;
}
//快读
const int N=1e6+5;
int S,n,x,gs;
bool vis[N];
int main(){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	S=read(),n=read();
	printf("%d\n",n);
    //先输出B集合的大小
	for ( int i=1;i<=n;i++ ) x=read(),vis[x]=1;
	for ( int i=1;i<=S;i++ ) 
		if (vis[i])
			if (vis[S+1-i]) gs++;
        //能配对直接输出
		else cout<<S+1-i<<" ";
	for ( int i=1;i<=S;i++ )
		if (!vis[i] && !vis[S+1-i] && gs) 
			gs-=2,cout<<i<<" "<<S+1-i<<" ";
	return 0;
}
```


---

## 作者：az__eg (赞：0)

比较板子的贪心题目。

题意：

现在有一个 $1$ 到 $10^6$ 的序列，抽取给定 $n<=5\times10^5$ 个元素，每个元素的贡献为 $x-1$，然后你也要抽取，你抽取的元素可以是剩下的元素中的任意几个，你抽取的元素贡献要等于被抽取的，你抽取的元素单个的贡献为 $10^6 - x$。问你怎么构造抽取方案。

解法：

我们发现对于一个被抽取的元素且值为 $x$，假如 $10^6 - x$ 没有被抽取，那么抽取了以后 $x$ 贡献就被抵消了，如果两个都被抽取了，那我们如果抽取一对这样的数，他们的贡献也被抵消了。

难点：

这个题意比较的阴间。

代码：

```cpp
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
const int s = 1e6;
map<int,bool> mp,vis;
int n;
int a[2*s];
int cnt;
int ans[2*s];
int main()
{
	int i,j,l = 1,r = s;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		mp[a[i]] = true;//标记有没有被取过 
	}
	sort(a+1,a+1+n); 
	for(i=1;i<=n;i++)
	{
		if(vis[a[i]] == true)
		{
			continue;
		}
		if(mp[s-a[i]+1] == false)
		{
			ans[++cnt] = s-a[i]+1;//没被取过，那么取掉
		}
		else
		{
  			//一对都被取了，那么只能再找一对
			while(mp[l]==true||mp[r] == true)
			{
				l++;
				r--;
			}
			ans[++cnt] = l;
			ans[++cnt] = r;
			l++;
			r--;
			vis[s-a[i]+1] = true;
		}
	}
	printf("%d\n",cnt);
	for(i=1;i<=cnt;i++)
	{
		printf("%d ",ans[i]);
	}
}
```


---

## 作者：xiaozeyu (赞：0)

换一种方式理解题目：

![](https://cdn.luogu.com.cn/upload/image_hosting/jcn6v6zk.png)

小C有一个数字集，包含了从1到S的自然数

他有一天突然想到一个问题：从这S个数中取出n个，

设为A_i（1<=i<=n，i∈N），能否再在剩余的数中取出m个，设为B_i（1<=i<=m，i∈N），

使得∑1^n（Ai-1）=∑1^m（S-Bi）成立。



------------

先把这些当做一一配对来看：

Ai-1=S-Bi

Ai+Bi=S+1

Bi=S-Ai+1

假如S=10

那组合出来就可以是2+9,3+8,4+7

于是可以求每一个S-Ai+1

但实际上并不能全部这样

其他的就可以从1-s 直接遍历

------------


# 解法 1

从N入手


```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,s,num;
int a[N],vis[N],p[N],ans[N];
int read(){
	int res=0,fl=1;
	char c=getchar();
	while(c<48||c>57){
		if(c=='-')fl=-1;
		c=getchar();
	}while(c>=48&&c<=57)res=res*10+c-48,c=getchar();
	return res*fl;
}
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+48);
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	cin>>s>>n;
	for(int i=1;i<=n;i++) 
	{
		a[i]=read();//scanf("%d",&a[i]);
		p[a[i]]=1;
	}
	for(int i=1,j=1;i<=n;i++)
	{
		if(vis[a[i]]) continue;
		if(!p[s-a[i]+1]) ans[++num]=s-a[i]+1;
		else
		{
			while(p[j]||p[s-j+1])
			{
				j++;
			}
			vis[s-a[i]+1]=1;
			ans[++num]=j;
			ans[++num]=s-j+1;
			j++;
		}
	}
	cout<<num<<endl;
	for(int i=1;i<=num;i++) 
		write(ans[i]),putchar(32);//printf("%d ",ans[i]);
}
```



------------

# 解法 2

直接遍历s


```cpp
#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000005
int i,j,n,num,S,p[N],vis[N],a[N],ans[N];
int fast(){
	int res=0,fl=1;
	char c=getchar();
	while(c<48||c>57){
		if(c=='-')fl=-1;
		c=getchar();
	}while(c>=48&&c<=57)res=res*10+c-48,c=getchar();
	return res*fl;
}
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+48);
}
int main()
{
	S=fast();
	n=fast();
	for(i=1;i<=n;i++)a[i]=fast(),p[a[i]]=1;
	for(i=1,j=1;i<=n;i++){
		if(vis[a[i]])continue;
		if(!p[S-a[i]+1])ans[++num]=S-a[i]+1;
			else{
				while(p[j]||p[S-j+1])j++;
				ans[++num]=j,ans[++num]=S-j+1;
				vis[S-a[i]+1]=1;j++;
			}
	}write(num);putchar(10);
	for(i=1;i<=num;i++)write(ans[i]),putchar(32);
}
```



---

## 作者：Limit (赞：0)

刚看见的时候貌似是一道很难做的题...题面十分的玄学,不能重选的要求也十分难搞...

但是,可以发现N<=5e5从中可以不难发现一旦不能直接取时便会一定有一对正好和为1e6-1

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxS=1000005;
int a[maxS],b[maxS],answer[maxS],S,N;
bool boo[maxS];
int main()
{
    S=1000000;
	scanf("%d",&N);
	int i;
	for(i=1;i<=N;i++)
	{
		scanf("%d",&a[i]);
		boo[a[i]]=1;//不能选了
	}
	int cnt=0;
	int full=0;//成对不能选的个数
	for(i=1;i<=N;i++)
	if(!boo[S-a[i]+1])//直接取
	{
		answer[++cnt]=S-a[i]+1;
		boo[S-a[i]+1]=1;
	}
	else
	full++;
	full/=2;//计算了两次..
	for(i=1;i<=(S+1)/2;i++)
	if(!boo[i]&&!boo[S-i+1])//成对可以取的
	{
		if(!full)break;//不需要了
		full--;
		answer[++cnt]=i;
		answer[++cnt]=S-i+1;
	}
	printf("%d\n",cnt);//输出个数
	for(i=1;i<=cnt;i++)
	printf("%d ",answer[i]);//输出序列
	return 0;
}
```
算是一道小清新的构造题....吧...

---

