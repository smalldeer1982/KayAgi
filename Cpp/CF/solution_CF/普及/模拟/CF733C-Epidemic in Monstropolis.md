# Epidemic in Monstropolis

## 题目描述

There was an epidemic in Monstropolis and all monsters became sick. To recover, all monsters lined up in queue for an appointment to the only doctor in the city.

Soon, monsters became hungry and began to eat each other.

One monster can eat other monster if its weight is strictly greater than the weight of the monster being eaten, and they stand in the queue next to each other. Monsters eat each other instantly. There are no monsters which are being eaten at the same moment. After the monster $ A $ eats the monster $ B $ , the weight of the monster $ A $ increases by the weight of the eaten monster $ B $ . In result of such eating the length of the queue decreases by one, all monsters after the eaten one step forward so that there is no empty places in the queue again. A monster can eat several monsters one after another. Initially there were $ n $ monsters in the queue, the $ i $ -th of which had weight $ a_{i} $ .

For example, if weights are $ [1,2,2,2,1,2] $ (in order of queue, monsters are numbered from $ 1 $ to $ 6 $ from left to right) then some of the options are:

1. the first monster can't eat the second monster because $ a_{1}=1 $ is not greater than $ a_{2}=2 $ ;
2. the second monster can't eat the third monster because $ a_{2}=2 $ is not greater than $ a_{3}=2 $ ;
3. the second monster can't eat the fifth monster because they are not neighbors;
4. the second monster can eat the first monster, the queue will be transformed to $ [3,2,2,1,2] $ .

After some time, someone said a good joke and all monsters recovered. At that moment there were $ k $ ( $ k<=n $ ) monsters in the queue, the $ j $ -th of which had weight $ b_{j} $ . Both sequences ( $ a $ and $ b $ ) contain the weights of the monsters in the order from the first to the last.

You are required to provide one of the possible orders of eating monsters which led to the current queue, or to determine that this could not happen. Assume that the doctor didn't make any appointments while monsters were eating each other.

## 说明/提示

In the first example, initially there were $ n=6 $ monsters, their weights are $ [1,2,2,2,1,2] $ (in order of queue from the first monster to the last monster). The final queue should be $ [5,5] $ . The following sequence of eatings leads to the final queue:

- the second monster eats the monster to the left (i.e. the first monster), queue becomes $ [3,2,2,1,2] $ ;
- the first monster (note, it was the second on the previous step) eats the monster to the right (i.e. the second monster), queue becomes $ [5,2,1,2] $ ;
- the fourth monster eats the mosnter to the left (i.e. the third monster), queue becomes $ [5,2,3] $ ;
- the finally, the third monster eats the monster to the left (i.e. the second monster), queue becomes $ [5,5] $ .

Note that for each step the output contains numbers of the monsters in their current order in the queue.

## 样例 #1

### 输入

```
6
1 2 2 2 1 2
2
5 5
```

### 输出

```
YES
2 L
1 R
4 L
3 L
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1
15
```

### 输出

```
YES
5 L
4 L
3 L
2 L
```

## 样例 #3

### 输入

```
5
1 1 1 3 3
3
2 1 6
```

### 输出

```
NO```

# 题解

## 作者：Soul_Love (赞：4)

看到这题还没有题解，就想着来一篇。

## 思路

显然，最后只能剩下 $k$ 个数，每一次“吃”的操作都是向左或者向右进行的，而且数字会累加，所以我们考虑把原序列分成 $k$ 段，且第 $i$ 段的数字之和为 $b_i$。然后贪心的想，对于每一段，我们只移动目前最大的那个数，防止稍小的数变大后和最大的数相等，使得他们不能互相吃。

然后就是对于所有 NO 情况的特判，详见代码。

## code

```c
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100100],z[100100],L[100100],R[100100],b[100100],k;
inline int read()
{
	int k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
struct abc
{
	int x;
	char g;
}ans[100100];//储存答案 
inline int work(int l,int r,int e)
{
	while(l<r)//每一段最后必须只剩下一个数 
	{
		int maxx=-999999999,ff=0;
		for(int i=l;i<=r;i++) maxx=max(maxx,a[i]);//找最大值 
		for(int i=l;i<=r;i++)
		{
			if(a[i]==maxx)
			{
				if(i>l&&a[i]>a[i-1])//向左吃 
				{
					ans[++k]=(abc){i-R[e-1]+e-1,'L'};//前面的段已经处理完了，所以前面只剩e-1个数了，下同 
					a[i-1]+=a[i];
					for(int j=i;j<r;j++) a[j]=a[j+1];//整体移动，下同 
					r--;//注意是右端点移动，不然i不准确，下同 
					ff=1;
					break;
				}
				if(i<r&&a[i]>a[i+1])//向右吃 
				{
					ans[++k]=(abc){i-R[e-1]+e-1,'R'};
					a[i]+=a[i+1];
					for(int j=i+1;j<r;j++) a[j]=a[j+1];
					r--;
					ff=1;
					break;
				}
			}
		}
		if(!ff) return 0;//如果无法移动 
	}
	return 1;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		z[i]=z[i-1]+a[i];//前缀和 
	}
	m=read();
	for(int i=1;i<=m;i++) b[i]=read();
	for(int i=1;i<=m;i++)
	{
		int f=0;
		L[i]=R[i-1]+1;//处理每段的左右端点 
		for(int j=L[i];j<=n;j++)
		{
			if(z[j]-z[R[i-1]]>b[i]||j==n&&z[j]-z[R[i-1]]<b[i])//如果无法放进这个段中或者最后一个数放进去也还不行 
			{
				printf("NO");
				return 0;
			}
			else if(z[j]-z[R[i-1]]==b[i])
			{
				f=1;
				R[i]=j;
				break;
			}
		}
		if(!f)//如果已经没有数来分进这个段中 
		{
			printf("NO");
			return 0;
		}
	}
	if(R[m]!=n)//如果分完段后还有数没有被分进段里 
	{
		printf("NO");
		return 0;
	}
	for(int i=1;i<=m;i++)
	{
		if(!work(L[i],R[i],i))//对于每个段单独处理 
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES\n");
	for(int i=1;i<=k;i++) printf("%d %c\n",ans[i].x,ans[i].g);
	return 0;
}
```


---

## 作者：Darling_ZX (赞：3)

## 分析题意：
读题后易得，题意无非是将 $a$ 数组分为连续的 $k$ 段，其中第 $i$ 段的元素和等于 $b_i$，此后在每段中构造操作序列。
## 解决代码部分：
分析完题意后，不要着急，分模块写，想清楚自己的思路，同时也方便调试。
### 1.预处理读入部分：
读入部分没什么好说的，定义 $asum$,$bsum$ 判断无解情况。

以下为部分代码：
```cpp
n=read();
for(int i=1;i<=n;i++){
	a[i]=read();
	asum+=a[i];
}
m=read();
for(int i=1;i<=m;i++){
	b[i]=read();
	bsum+=b[i];
}
if(asum!=bsum){ //如果两数组元素和不相等 则无解情况
	puts("NO");
	return 0;
}
```
### 2.将 $a_i$ 分为 $k$ 段：
注意一些细节处理，此处变量多，写时要想清楚。有两类无解情况：1.一段区间内元素值全相同，无法吃；2.无法分完，没有完全匹配。

以下为部分代码：
```cpp
int now=1,nowsum=0,nowmaxx=0,maxxid,pd=a[1],o=1; 
//now记录当前分到了哪一段 nowsum记录当前段中元素和
//nowmaxx记录当前段中区间最值 maxxid记录区间最值位置
//pd表示段中第一个元素 o记录是否区间内数都相同
for(int i=1;i<=n;i++){
	if(nowsum>b[now]){
		puts("NO");return 0;
	}
	nowsum+=a[i];
	if(a[i]>nowmaxx){
		nowmaxx=a[i];
		maxxid=i;
	}
	if(a[i]!=pd)o=0;
	if(nowsum==b[now]){
		ans[now].id=i;
		ans[now].maxx=maxxid;
		if(o==1&&(i-ans[now-1].id)!=1){
			puts("NO");
			return 0;
		}
		now++;
		nowsum=0;
		nowmaxx=0;
		pd=a[i+1];
		o=1;
	}
}
if(now!=m+1){
	puts("NO");
	return 0;
}
else{
	puts("YES");
}
```
### 3.输出
注意判断情况，输出时注意判断位置已经改变。因为最大值只记录第一位，所以可以将一段中左边先全吃了。
可有一种特殊情况，如：
```cpp
4
2 2 2 1
1
7
```
此时左边没有的吃，右边又吃不了，我们就得将最大值一步步往右移后将右边全吃了后在吃完左边。

以下为部分代码：

```cpp
for(int i=1;i<=m;i++){
	int flag=0;
	int nm=ans[i].maxx-ans[i-1].id;
	for(int j=ans[i].maxx;j>ans[i-1].id+1;j--){
		printf("%d L\n",i-1+j-ans[i-1].id);
	}
	while(a[ans[i].maxx+1]==a[ans[i-1].id+1]&&a[ans[i].maxx+1]==a[ans[i].maxx]&&(ans[i].maxx+1)<=ans[i].id){
		flag=1;
		ans[i].maxx++;
	}
	if(flag==1){
		for(int j=ans[i].maxx;j<ans[i].id;j++){
			printf("%d R\n",ans[i].maxx-ans[i-1].id+i-1);
		}
		for(int j=ans[i].maxx;j>ans[i-1].id+1;j--){
			printf("%d L\n",i-1+j-ans[i-1].id);
		}
	}
	else{
		for(int j=ans[i].maxx+1;j<=ans[i].id;j++){
			printf("%d R\n",i);
		}
	}
}
```
完结。

---

## 作者：_Violet_Evergarden (赞：2)

## 简要题意:

将一序列进行合并，使其合并成另一个序列。

## 警示后人：

1：合并不可以合并相同的。

2：注意判断 NO 的情况时，是否将第一个序列合并完。

3：在输出时注意要更新下标。

## 举例：
```
5
2 2 2 1 3
1
7 3
```
## 思路：

第一序列的块为第二序列数所对应第一序列相加的数相加相等的区间。

此处举上文的例子 $2 2 2 1$ 为一个块， $3$ 单独为一个块。

先判断 NO 的情况，然后再找到每一个第二序列对应第一序列的块中的最大值的下标。
（若有相同最大值则找到保证左右中有可以合并的值的下标）

举上文的例，此时要取最右边的 $2$ 来进行合并。

相信各位大佬已经明白该如何码代码了。

此处附上代码，不喜勿喷。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int k;
int a[1001];//第一个序列 
int b[1001];//第二个序列 
int flag[10001];//用来判断是否在块内有不同的数 
int p;//前缀的加数 
int o=1;//在b序列的第几个数
int f;//判断是否是块的第一个数 
int x[10001];//每个块的右端点 
int main()
{
	cin>>n;
	for(int i = 1;i<=n ;i++){
		cin>>a[i];
	}
	cin>>k;
	for(int i = 1;i<=k ;i++){
		cin>>b[i];
	}
	for(int i = 1;i<=n ;i++){
		p+=a[i];
		if(a[i] !=a[i-1]&&f!=0&&flag[o]==0){ //注意不可以是块第一个数，所以要判f是否等与0 
			flag[o]=1;
		}
		if(p==b[o]){
			if(flag[o]==0&&f==1){
				cout<<"NO";
				return 0;
			}
			else{
				f=0;
				p=0;
				x[o]=i;
				o++;
				continue;
			}
		}
		if(p>b[o]){
			cout<<"NO";
			return 0;
		}
		f=1;	
	}
	if(o!=k+1){
		cout<<"NO"<<endl;
		return 0;
	}
	x[0]=0;
	if(p==0){
		cout<<"YES"<<endl;
	}
	if(p!=0){
		cout<<"NO"<<endl;
		return 0;
	}
	for(int i = 1; i<=k; i++){
		int s = 0;//最大值的值 
		int xia;//最大值的下标 
		int fl = 0;//用作判断是否最大值的下标左右有小于最大值的数 
		//注意x[i-1]+1才是这个块的第一个数 
		for(int pp= x[i-1]+1; pp<=x[i]; pp++){
			if(a[pp]>s){ 
				s=a[pp];
				xia=pp;
				if(pp==x[i-1]+1){
					fl=1;
					continue;
				}
				if(pp!=x[i-1]+1){
					fl=0;
				}
			}
			if(a[pp]<s){
				fl=0;
			}
			if(fl==1&&a[pp]==s){
				xia=pp;
			}
		}
		if(a[xia]>a[xia-1] && xia!=x[i-1]+1){
			for(int u = xia;u>x[i-1]+1 ;u--){
				cout<<i-1+u-x[i-1]<<" "<<"L"<<endl;//简单用下标来推导出现在下标 
			}
			for(int u = xia; u<x[i]; u++){
				cout<<i<<" "<<"R"<<endl;//简单用下标来推导出现在下标 
			}
		}
		else{
			for(int u = xia; u<x[i]; u++){
				cout<<xia-x[i-1]+i-1<<" "<<"R"<<endl;//简单用下标来推导出现在下标 
			}
			for(int u = xia; u>x[i-1]+1; u--){
				cout<<i-1+u-x[i-1]<<" "<<"L"<<endl;//简单用下标来推导出现在下标 
			}
		}
	}
	return 0;
}
```



---

## 作者：liuzhongrui (赞：0)

## 思路

解决问题的关键观察是注意到 $b_1$ 是 $a$ 的某个前缀的元素的并集（怪物们相继吃掉彼此，直到只剩下一个），如果移除这个前缀和 $b$ 的第一个元素，那么对于新的数组 $a$ 和 $b$，这个条件仍然成立。

没有这样的前缀使 $b_i$ 的总和等于前缀和或前缀和包含相等的元素，且其大小大于 $1$，输出 ```NO```。

现在考虑某个前缀，目标是找到一系列步骤，使得最终只剩下一个怪物。

以下是一种解决方案。

找到这样的 $i$，使得前缀中 $a_i$ 是最大的，并且 $a_{i - 1}$ 或 $a_{i + 1}$ 严格小于 $a_i$。

吃掉任何可能的相邻怪物，如果只剩下一个怪物，则移动到下段，如果所有重量变得相等，则输出 ```NO```。

现在我们需要计算每一步中怪物的真实位置。

**注意：万万不能在计算的时候立即输出它们，因为之后可能会出现 ```NO``` 的答案。**



---

