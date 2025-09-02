# Petya and Countryside

## 题目描述

Little Petya often travels to his grandmother in the countryside. The grandmother has a large garden, which can be represented as a rectangle $ 1×n $ in size, when viewed from above. This rectangle is divided into $ n $ equal square sections. The garden is very unusual as each of the square sections possesses its own fixed height and due to the newest irrigation system we can create artificial rain above each section.

Creating artificial rain is an expensive operation. That's why we limit ourselves to creating the artificial rain only above one section. At that, the water from each watered section will flow into its neighbouring sections if their height does not exceed the height of the section. That is, for example, the garden can be represented by a $ 1×5 $ rectangle, where the section heights are equal to 4, 2, 3, 3, 2. Then if we create an artificial rain over any of the sections with the height of 3, the water will flow over all the sections, except the ones with the height of 4. See the illustration of this example at the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF66B/9a7bf3e55f07a79a8c55bac4c2b87a72e9e3e5af.png)As Petya is keen on programming, he decided to find such a section that if we create artificial rain above it, the number of watered sections will be maximal. Help him.

## 样例 #1

### 输入

```
1
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 1 2 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
8
1 2 1 1 1 3 3 4
```

### 输出

```
6
```

# 题解

## 作者：StudyingFather (赞：5)

考虑用 $ O(n^2) $ 的枚举来解决这道问题。

每次枚举浇水的位置，向两边扩展，如果无法继续扩展就停止，计算答案即可。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,a[1005],ans; 
int main()
{
 scanf("%d",&n);
 for(int i=1;i<=n;i++)
  scanf("%d",&a[i]);
 for(int i=1;i<=n;i++)
 {
  int l=i,r=i,ln=a[i],rn=a[i];
  while(l>1&&a[l-1]<=ln)
   ln=a[--l];
  while(r<n&&a[r+1]<=rn)
   rn=a[++r];
  ans=max(ans,r-l+1);
 }
 printf("%d\n",ans);
 return 0;
}
```

---

## 作者：chufuzhe (赞：2)

这道题可以枚举每一块地方，再从这个位置向左右两边延伸，直到不能再往下流为止，这样每次延伸的时间复杂度最多会到$O(n)$，总的时间复杂度最多就是$O(n^2)$。

可以先进行预处理，计算出这个位置往左最多能流多少个，往右最多能流多少个。

计算这个位置往左最多能流多少个，就从头开始计算，如果能流到前一个位置，就是前一个位置往左最多能流的个数加一，流不到就是0个。

再计算这个位置往右最多能流多少个，就从头开始计算，如果能流到后一个位置，就是后一个位置往右最多能流的个数加一，流不到就是0个。

然后再打擂台，每个位置能流到的就是往左加上往右的，比较出最多能流到的，时间复杂度就是$O(n)$。

代码：
```cpp
#include<bits/stdc++.h> //头文件
using namespace std;
inline int read() //快读
{
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1005],l[1005],r[1005]; //定义数组，l表示这个位置往左最多能流多少个,r表示这个位置往右最多能流多少个。
int main()
{
    int n,s=0;
    n=read(); //输入
    for(register int i=1;i<=n;i++)
    	a[i]=read();
    l[1]=0; //第一个位置往左没有了，所以往左最多能流0个
	for(register int i=2;i<=n;i++)
		if(a[i-1]<=a[i]) //比较能否流到前一个
			l[i]=l[i-1]+1; //如果能流到前一个位置，就是前一个位置往左最多能流的个数加一，流不到就是0个（数组初始就是0）
	r[n]=0; //和第一个位置一样，最后一个位置往右也最多能流0个
	for(register int i=n-1;i>=1;i--)
		if(a[i+1]<=a[i]) //比较能否流到后一个
			r[i]=r[i+1]+1; //如果能流到后一个位置，就是后一个位置往右最多能流的个数加一，流不到就是0个
	for(register int i=1;i<=n;i++) //打擂台
		s=max(s,l[i]+r[i]+1); //比较
	cout<<s<<endl; //输出
    return 0;
}
```


---

## 作者：monstersqwq (赞：1)

第一眼以为是什么奇怪的模板题，后来又发现是能往两边流（什么神仙题，做不来）。

看到数据范围：$1 \le n \le 1000$，嗯，枚举真香。

思路：枚举每个可能的降雨点向左右伸展，如果高度比上一个大就停止，每次更新答案，最后输出。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
int n,ans=-1,a[1005];
using namespace std;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		int l=i-1,r=i+1;
		while(l>=1&&a[l]<=a[l+1]) l--;
		while(r<=n&&a[r]<=a[r-1]) r++;
		ans=max(ans,r-l-1);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Mikemao666 (赞：1)

这道题看着很唬人，什么水流往低处流、找最大灌溉面积
~~净整物理难题呢~~。然而我们仔细地看一下，就不难发现：本题的关键就在于**求出每一个点的左、右两边（算上自己）的不大于它自身的元素总数**取出最大；画张图来说：![](https://cdn.luogu.com.cn/upload/image_hosting/1txxvpy6.png)

So……看到这$n<=1000$的蒟水数据，第一个想到的肯定是我们的大~~模拟~~搜索了！

这里我用了两个$dfs$,更好理解。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001],n,maxi=-1;
//dfs1遍历左边 
int dfs1(int x,int ans){//x表示当前位置，ans表示元素个数 
	if(x<1)return 0;//如果到边界就直接返回 
	if(a[x-1]<=a[x])ans=dfs1(x-1,ans+1);//如果可以灌溉就dfs下去 
	return ans;//返回答案 
}int dfs2(int x,int ans){//dfs2遍历右边 
	if(x>n)return 0;//同上 
	if(a[x]>=a[x+1])ans=dfs2(x+1,ans+1);
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	a[0]=a[n+1]=2147483647;//边界最大化，以防"水漏出花园" 
	for(int i=1;i<=n;++i){
		//cout<<dfs1(i,0)<<" "<<dfs2(i,0)<<endl;
		maxi=max(maxi,dfs1(i,0)+dfs2(i,0)+1);//+1是因为自身作为起点也算被灌溉 
	}
	printf("%d",maxi);
	return 0;//完结撒世纪末彼岸花❀
}
```

---

## 作者：血色黄昏 (赞：1)

py题解，新鲜的~

作为一道数据范围不大于1000的水题，可以看出不需要想一些奇奇怪怪的思路去达到时间最优解，$n^2$的暴力绝对能过，毕竟小花也说过，$n^2$的暴力基本上啥都能维护~

所以说，此题只需要枚举每一个节点，统计一下每个节点所能到达的节点数量就行了，时间复杂度为$O(n^2)$，跑得也很快。

下面送上此题python的代码

```python
def tot(i):  # 计算每个位置能扩展到的节点数
    global l  # 导入全局变量l
    ans = 0  # 记录节点数
    q = i  # 记录下标
    bo = 0  # 判断计算过几次i这个点
    if i != 0:  # 如果不是第一位就可以往前判断
        bo += 1  # 每次都会算一遍节点本身
        while True:  # 一直循环 
            ans += 1  # 能扩展到的节点多一个
            q -= 1  # 往前扩展
            if q == 0 or l[q] < l[q - 1]:  # 如果是第一个节点或者不符合条件了
                ans += 1  # 加上自身节点
                break  # break掉
    if i != len(l) - 1:  # 不是最后一位往后判断，同上
        bo += 1
        q = i
        while True:
            ans += 1
            q += 1
            print(q, len(l) - 2)
            if q == len(l) - 2 or l[q] < l[q + 1]:
                ans += 1
                break
    if bo == 2:  # 如果自身计算了两次就将答案减一，可以证明不会有bo=0的情况
        ans -= 1
    return ans  # 返回ans


n = int(input())  # 输入n
l = input().split()  # 输入数组
if len(l) == 1:  # 只有一个元素时特判，直接返回1
    print(1)
else:
    for i in range(n):  # string转int
        l[i] = int(l[i])
    maxn = -1  # 记录最大值
    for i in range(n):  # 从0枚举到n-1
        maxn = max(maxn, tot(i))  # 每次更新最大值
    print(maxn)  # 输出
```

祝大家暑假快乐

---

## 作者：peppaking8 (赞：1)

## 思路
$$\texttt{Solution 1}$$
$$O(n^2)$$

首先，我们可以进行**枚举**。考虑进行 DFS，对于每个节点，枚举左边和右边最多能到达哪里，这是深搜的模板题。

对于每个节点的枚举是 $O(n)$ 的效率，一共有 $n$ 个节点，故时间复杂度 $O(n^2)$。可以通过 $n\le 1000$ 的数据点。

但是，有没有更优秀的算法呢？

$$\texttt{Solution 2}$$
$$O(n)$$

想一想，优化时间的一个常见方法是**用空间换时间**。显然第一种除了初始数组，空间复杂度为 $O(1)$。所以我们考虑**动态规划**。

对于每个节点，设它左边能浇灌的最远节点与其的距离为 $f_i$，右边则为 $g_i$。那么最终的答案就是 $\text{max}\{f_i+g_i\}+1$。

那么 $f_i$ 怎么求呢？如果 $a_i\ge a_{i-1}$，那么 $f_i=f_{i-1}+1$；否则，$f_i=0$。

综上，我们用 $O(n)$ 的效率处理了 $f$ 数组，同理可以处理 $g$ 数组，然后统计答案的复杂度 $O(n)$，所以总体时间复杂度是 $O(n)$，非常优秀！

有没有更优化的算法呢？即使有，也没有必要研究了，因为单单是输入就已经耗费 $O(n)$ 的时间复杂度了。

## 代码

下面给出 $\texttt{Solution 2}$ 的代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n;
int a[N];
int f[N],g[N];
int ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[1]=0;//因为没有定义 a0，所以要初始化f1。
	for(int i=2;i<=n;i++){
		if(a[i]>=a[i-1]) f[i]=f[i-1]+1;
		else f[i]=0;
	}
	g[n]=0;//同理，g数组的处理方式相反
	for(int i=n-1;i>=1;i--){
		if(a[i]>=a[i+1]) g[i]=g[i+1]+1;
		else g[i]=0;
	}
	for(int i=1;i<=n;i++) ans=max(ans,f[i]+g[i]);
    //统计答案
	printf("%d\n",ans+1);
    return 0;//点个赞再走呀~
}
```

---

## 作者：AllanPan (赞：0)

由于数据相对比较小，而且是一维情况，因此完全可以暴力枚举。

这题唯一需要注意的要点就是搜索的起始点、终止点，以及去重的过程，其它的便无需赘述。

上代码：
```cpp
#include <iostream>
using namespace std;

int main()
{
    int n;
    int height[1001], maxsize = 1;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> height[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int count = 1;
        int j = i;
        while (height[j-1] <= height[j] && j >= 2) // 注意范围
        {
            count++;
            j--;
        } // 左端计数
        j = i;
        while (height[j+1] <= height[j] && j <= n-1) // 注意范围
        {
            count++;
            j++;
        } // 右端计数
        maxsize = max(maxsize, count);
    }
    cout << maxsize;
    return 0;
}
```
p.s. 这题居然有80个测试点(

---

## 作者：oimaster (赞：0)

按照题面模拟即可。我们可以枚举 Petya 要在哪个地方浇水，然后内部再计算可以交到多少个格子。最后比较即可。

下面主要讲代码：

```cpp
int maxv=0; //这是比较的结果，默认初值为 0
for(int i=1;i<=n;++i){ //i 是我们枚举到的位置
	int tot=1; //tot 是这个位置可以灌到多少格子
	int j=i-1; //j 是模拟水流的变量，首先我们要让水往左流
	while(j>=1&&a[j]<=a[j+1]){ //当还能往左边流时
		++tot;
		--j; //再往左一格
	}
	j=i+1; //然后我们模拟水向右流
	while(j<=n&&a[j]<=a[j-1]){ //当还能向右边流时
		++tot;
		++j; //与上面类似，再往右一格
	}
	maxv=max(maxv,tot); //进行比较
}
cout<<maxv<<endl;
```

时间复杂度，玩循环 $n$，内循环 $n$。复杂度为 $\text{O}(n^2)$，可以通过。

---

## 作者：qfpjm (赞：0)

# 题意

- 有一个人浇水，就是高处的水会往低处流，所流到的位置则不需要浇水，求最少的浇水次数。

# 题解

- 枚举浇水的位置，向两边扩展，直到无法继续扩展，计算答案即可。

# 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, ans = -1, a[1005];

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i ++)
	{
		cin>>a[i];
	}
	for(int i = 1; i <= n; i ++)
	{
		int l = i - 1,r = i + 1;
		while(l >= 1 && a[l] <= a[l + 1])
		{
			l --;
		}
		while(r <= n && a[r] <= a[r - 1])
		{
			r ++;
		}
		ans=max(ans,r - l - 1);
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Allanljx (赞：0)

## 题意
 $Little Petya$ 需要给花园浇水。每块地有一个高度。他会选择一块地方浇水，如果与这块地相邻的区域的高度小于等于这块地的高度，水就可以流过去，直到不能流为止。求他一次最多可以浇灌多少块地。
## 思路
因为 $n<=1000$ ，暴力枚举每个位置，再向两边延伸，复杂度是 $O(n^2)$ ，可以过。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int main()
{
    int n,sum=1,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
	}
	for(int i=1;i<=n;i++)//枚举每个位置
	{
		for(int j=i-1;j>0;j--)//向左找
		{
			if(a[j]<=a[j+1])//可以流过去
			{
				sum++;
			}
			else break;//不可以流过去
		}
		for(int j=i+1;j<=n;j++)//向右找
		{
			if(a[j]<=a[j-1])//可以流过去
			{
				sum++;
			}
			else break;//不可以流过去
		}
		ans=max(ans,sum);//取最大值
		if(ans==n) break;//剪枝
		sum=1;
	}
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Real_Create (赞：0)

看到题就觉得是 $O(n)$ 的。

然后看题解都是 $O(n^2)$。

所以过来水个题解力！

如果一个地方是最优解，它至少应该大于等于它两边的。

所以我们可以记一下他左边的第一个峰，第一个比右边高的，分别记为 $last$ $lasts$。

然后挨个比较。

扔代码

```
#include<bits/stdc++.h>
using namespace std;
int a[1005],n,last,lasts,maxn,s;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>a[i-1])
		{
			maxn=max(maxn,s+i-last-1);
			last=i;
			s=last-lasts;
		}
		if(a[i]<a[i-1])
		{
			lasts=i-1;
		}
	}
	maxn=max(maxn,s+n-last);
	cout<<maxn;
	return 0;
}

```


---

## 作者：LiteratureCollege (赞：0)

我们枚举每一个点，再取最大值。对于每一个点，都向左和向右分别尝试，比如向左，如果能流动，就继续向左尝试（但要注意这里不要向右，向左就一路向左，向右就一路向右。因为如果你是向左流来的，那么你右边的就必定有水，不用再尝试）

这里我们可以使用两个while循环分别尝试向左或向右。顺便一提，数组需要初始化为无穷大。

一看就懂的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define re return
#define itn int
inline ll in()
{
	ll s=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		s*=10;
		s+=c-'0';
		c=getchar();
	}
	return s*f;
}
int n,zjy,a[1416],gy;
int main()
{
	cin>>n;
	memset(a,0x3f,sizeof(a));//记得初始化 
	for(int i=1;i<=n;i++)
	{
		a[i]=in();
	}
	for(int i=1;i<=n;i++)
	{
		gy=1;//这里的1是枚举的格子本身 
		int x=i,xx=i;//x代表向左尝试时的位置（就是最左边的水的位置），xx代表向右尝试时的位置 （就是最右边的水的位置） 
		while(x>=1)//边界条件 
		{
			if(a[x-1]<=a[x])//如果他左边的这个格子高度小于等于他本身的高度 
			{
				gy++;//能到达的格子数加一 
				x--;//水向左移动一格 
			}
			else
			{
				break;
			}
		}
		while(xx<=n)//同上 
		{
			if(a[xx+1]<=a[xx])
			{
				gy++;
				xx++;
			}
			else
			{
				break;
			}
		}
		zjy=max(zjy,gy);//取最大值 
	}
	cout<<zjy;//输出 
	return 0;
}
/*
zjy
*/
```


---

## 作者：听取MLE声一片 (赞：0)

一道非常简单的模拟题目。

众所周知，模拟是一个非常好的算法（骗分大法好），显然这道题是一道模拟题目。

问题是求他一次最多可以浇灌多少块地，我们可以使用最朴素的方法——遍历每一个点，又因为数据范围为 `1000` 我们可以放心地用 $n^2$ 方法。

然后是核心的是处理计数：

```
		int s=1;
		for(int j=i-1;j>=1;j--){
			if(a[j+1]<a[j])
				break;
			s++;
		}
		for(int j=i+1;j<=n;j++){
			if(a[j-1]<a[j])
				break;
			s++;
		}
		ans=max(ans,s);
```

如果与这块地相邻的区域的高度**小于等于**这块地的高度，水就可以流过去，直到不能流为止，我们只需要顺着来一遍就。

最后，题目中只能有一点水，不存在有很多水溢出来的情况。

```
#include<bits/stdc++.h>
using namespace std;
int n,a[1001],ans; 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		int s=1;
		for(int j=i-1;j>=1;j--){
			if(a[j+1]<a[j])
				break;
			s++;
		}
		for(int j=i+1;j<=n;j++){
			if(a[j-1]<a[j])
				break;
			s++;
		}
		ans=max(ans,s);
	}
	cout<<ans;
	return 0;
}

```

谢谢大家！

---

