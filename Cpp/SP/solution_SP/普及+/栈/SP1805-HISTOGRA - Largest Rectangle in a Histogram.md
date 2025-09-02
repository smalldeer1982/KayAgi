# HISTOGRA - Largest Rectangle in a Histogram

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP1805/b9567e3483620f1fe679470ac44083eae9842e79.png)

如图所示，在一条水平线上有  $n$ 个宽为  $1$ 的矩形，求包含于这些矩形的最大子矩形面积（图中的阴影部分的面积即所求答案）。

## 样例 #1

### 输入

```
7 2 1 4 5 1 3 3
4 1000 1000 1000 1000
0```

### 输出

```
8
4000```

# 题解

## 作者：冒泡ioa (赞：39)

>部分内容来自李煜东所著《算法竞赛进阶指南》


如果说这道题矩形的高度是递增的，估计就是一道普及难度的题了吧。  
我们可以尝试以每个矩形的高度作为最终矩形的高度，并将宽度扩展到右边界，答案取最大值。  

简单归简单，不过这也给了我们一个启发，如果是递增的我们就放着不管，以后来处理。如果说下一个高度更小，那么用它所构成的矩形的高度不可能超过它自己，而后面的矩形想要和前面的矩形拼接的话，高度也不能超过它。  
这样子的话，我们就可以用上面的方法更新比当前矩形高的矩形的答案再将它们合并。

这就是**单调栈**算法，时间复杂度 $ O(N) $  
借助单调性处理问题的思想在于**及时排除不可能的选项，保持策略集合的高度有效性和秩序性**  

就这拿道题举例，我们建立一个栈，用来保存若干个矩形，这些矩形的高度是**单调递增**的，或者说，我们期望他是**单调递增**的。  
我们从左到右读入矩形：  
如果当前矩形比栈顶矩形高，即满足**单调递增**，进栈。  
否则不断去除栈顶，直至栈空或栈顶高度低于当前矩形。在此过程中，我们累计被弹出的矩形的宽度和（用于计算答案与合并），用高度×累计宽度更新答案。而后，将一个宽度为累计宽度，高度为当前矩形的矩形入栈。  
结束，将剩余矩形弹出，和上面一样更新答案；


## 代码
```c++
#include<iostream>
#include<cstdio>
#include<cstring> 
#include<algorithm>
using namespace std;
int n,p;
int a[100010];
int s[100010],w[100010];
long long ans;

int main()
{
    while(cin>>n&&n)
    {
        ans=0; p=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        a[n+1]=0;
        for(int i=1;i<=n+1;i++)
        {
            if(a[i]>s[p]) s[++p]=a[i],w[p]=1;
            else{
                int width=0;
                while(s[p]>a[i])
                {
                    width+=w[p];
                    ans=max(ans,(long long)width*s[p]);
                    p--;
                }
                s[++p]=a[i],w[p]=width+1;
            }
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：蓬萊山輝夜 (赞：34)

# 单调栈定义：
单调栈——就是栈内元素单调递增或者单调递减的栈，单调栈只能在栈顶操作。

# 性质：
     1. 单调栈里的元素具有单调性
     2. 元素加入栈前，会在栈顶端把破坏栈单调性的元素都删除
     3. 使用单调栈可以找到元素向左遍历第一个比他小的元素，也可以找到元素向左遍历第一个比他大的元素。
     4. 单调栈的维护是 O(n) 级的时间复杂度，因为所有元素只会进入栈一次，并且出栈后再也不会进栈了。

## 举个栗子 ^ _ ^

一个小小的单调****增****栈（）
```
for(int i=1;i<=len;i++)
{
	while( top > 0 && a[stack[top]] > a[i] )  top--;
	a[++top]=i;
}
```


## 来干道题

### POJ2559

![](https://img-blog.csdnimg.cn/20190715211109447.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzE5ODI5NTk1,size_16,color_FFFFFF,t_70)
 ~~dick~~

![](https://img-blog.csdnimg.cn/20190715211121758.png)

拿到这道题，我们分析可得：用暴力大法直接枚举R、L、H~i~的时间复杂度是O(n^3^)优化计算区间最小值H~i~可使时间复杂度降为O(n^2^)

但是，O(n^2^)的算法时间复杂度==是绝对会超时滴ck(dick)==！！！

![](https://img-blog.csdnimg.cn/20190715211623356.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzE5ODI5NTk1,size_16,color_FFFFFF,t_70)

所以我们需要用新的算法，新的数据结构
于是我们引出单调栈，如图：

![](https://img-blog.csdnimg.cn/20190715212258179.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzE5ODI5NTk1,size_16,color_FFFFFF,t_70)

![](https://img-blog.csdnimg.cn/20190715212336426.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzE5ODI5NTk1,size_16,color_FFFFFF,t_70)

*==借助单调性处理问题的思想在于及时排除不可能的选项，保持策略集合的高度有效性和秩序性！==*

### 题解
下面是AC代码(请勿抄袭)

```
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
 
using namespace std;

int n,p;
long long int ans;
int a[100010],s[100010],w[100010];

void machen(void)
{
	while( scanf("%lld",&n) && n)
	{
        ans=0; p=0;
        
        for(int i=1;i<=n;i++) 
			scanf("%d",&a[i]);
        a[n+1]=0;
        
        for(int i=1;i<=n+1;i++)
        {
            if(a[i]>s[p])
            {
            	s[++p]=a[i];
				w[p]=1;
            }
				
				
            else
			{
                int len=0;
                
                while(s[p]>a[i])
                {
                    len+=w[p];
                    ans=max(ans,(long long)len * s[p]);
                    p--;
                }
                s[++p]=a[i],w[p]=len+1;
            }
            
        }
        cout<<ans<<endl;
	}
}

//#define LLSS
int main()
{

	#ifdef LLSS
		freopen("file.in","r",stdin);
		freopen("file.out","w",stdout);
	#endif

	machen();
	
	#ifdef LLSS
		fclose(stdin);
		fclose(stdout);
	#endif

	return 0;
}

```



是用数组模拟栈 <_> 






转自我的CSDN博客（ID： 多々良 小傘）：https://blog.csdn.net/qq_19829595/article/details/96019508
________________________________

---

## 作者：___new2zy___ (赞：28)

## 题解 SP1805 【HISTOGRA - Largest Rectangle in a Histogram】

题目传送门：：

https://www.luogu.org/problemnew/show/SP1805#sub

**原题**：poj 2559

===================分割线===================

本人感想：**真是一道好题**~~~！！！

本题是**单调栈**好题哦！~~（老师语）~~

===========================================

#### 题面~~（人性）~~翻译：：

给定从左到右多个矩形，已知这此矩形的宽度都为1，长度不完全相等。

这些矩形相连排成一排，求在这些矩形包括的范围内能得到的面积最大的矩形，输出该面积。

**所求矩形可以横跨多个矩形**，但不能超出原有矩形所确定的范围。


===========================================

## **算法分析&&具体操作：**

对于此题，我们需要**从左向右求出每个矩形向右能够扩展到的最大连续宽度**

**能够扩展的条件**：**矩形高度大于等于当前矩形高度**

那么我们求完之后算出面积取 max 即可

显然朴素算法是不行的，我们需要用到**单调栈**

（听说DP也可以，只是很慢，可能不过）

准确的说是：

**单调栈维护从起点矩形到当前矩形的高度递增序列**

如果**当前矩形高于栈顶矩形**，我们就一直将栈中元素弹出，**直到遇到低于当前点的矩形**，**以此来维护栈的递增性**，显然**此时的点最远可以扩展到当前栈元素的位置top-1**，即我们找到了**当前点的扩展边界**，同时**把弹出的矩形合并再压入栈**。

建立一个单调（递增）栈，所有元素各进栈和出栈一次。**每个元素出栈的时候更新最大的矩形面积**。

设栈内的矩形为一个二元组（h, w），h表示矩形的高度，w表示矩形的宽度。

如何**入栈并更新**呢？

① 如果**当前元素比栈顶元素大或者栈为空**，则直接压栈（h，1）；

② 如果**当前元素小于等于栈顶元素**，则**出栈合并矩形**，**直到当前元素大于栈顶元素或者栈为空时**，**合并矩形**（h,sum_width）**入栈**。

③在出栈的过程中**更新最大面积和累积宽度**

那么重复上述①~③操作，我们可以线性O(n)求出每一组数据的解

### **注意事项：**

单调栈要维护两个信息，一个是**高度**，另一个是**宽度**（便于计算矩形面积）

同时令H[n+1]=0，以保证所有矩形全部弹出栈
（最后没有矩形剩余在栈中）

**~~分析到此结束~~**

下面上代码~~~（code里也有解释）


===========================================

    #include<iostream>
    #include<cstdio>
    #include<cmath>
    #include<algorithm>
    using namespace std;
    typedef long long ll;
    const int inf=1e9+7;
    inline ll read()
    {
  	    ll p=0,f=1;char c=getchar();
  	    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
  	    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
  	    return 1ll*f*p;}
    struct rect
    {
	    ll h,w;//定义矩形(rectangle)高度h,宽度w
    };
    ll n,H[200050],ans;
    void Monotone_stack_solve()//单调栈算法
    {
    	ans=0;
	    rect S[100050]={(rect){0,0}};
	    //数组模拟矩形的高度单调栈
	    int top=0;//栈顶 
	    H[n+1]=0;
	    //保证第n+1个矩形高度为0,能保证扫描1~n矩形结束后栈内没有剩余矩形 
	    for(int i=1;i<=n+1;i++)//1~n+1个矩形扫描一遍 
	        {
	    	    if(H[i]>S[top].h)
			    //如果当前矩形高于栈顶直接入栈,宽度为1(符合高度单调递增性质)
	    	       S[++top]=((rect){H[i],1});
			    else//否则就持续弹出栈顶矩形合并 
			       {
			   	    ll width=0;//弹出的栈顶矩形合并总宽度 
			   	    while(S[top].h>H[i])//不满足高度单调递增继续弹出 
			   	          {
			   	      	    width+=S[top].w;//累计宽度 
			   	      	    ans=max(ans,1ll*width*S[top].h);//面积取max 
			   	      	    //更新面积(长乘宽)
			   	      	    top--;//弹出堆顶矩形
					         }
			   	    S[++top]=((rect){H[i],width+1});
			   	    //把合并好的新矩形入栈(高为H[i],宽为width+1)
			       }
		    }
	    printf("%lld\n",ans); 
    }
    int main()
    {
        while(1)//多组数据
              {
          	    n=read();
          	    if(!n)break;
          	    memset(H,0,sizeof(H));
          	    //初始化
          	    for(int i=1;i<=n;i++)//读入每个矩形高度 
			          H[i]=read();
          	    Monotone_stack_solve();//单调栈算法求解 
		      }
  	   return 0;
    }

===========================================

没啦~~~感谢阅读>=<

希望大家好好理解一下本题，这题还是比较经典的**单调栈**（Monotone_stack）听说紫书上也有

最后推广一下我的博客：

https://www.luogu.org/blog/new2zy/

拜拜~~~




---

## 作者：MoonPie (赞：17)

大家都是用单调栈做的，我用一个类似递推的算法AC了

闲话不多说，这里来和大家分享一下。


------------

### 算法核心：

对于求包括第i个矩形的最大面积，可以分为两个部分：i的左边、i的右边

分别用L[i]和R[i]来存第i个矩形往左最多能到的下标和往右最多能到的下标

对于L[i],可以先初始化L[i]=i，

然后用一次for循环更新数组L：

如果L[i]-1的高度>=i的高度（L[i]需要更新）,则L[i]=L[L[i]-1]。更新，直到不满足要求或L[i]越界。

同理，可以算出数组R （请读者自行思考）

最后，答案即 $max(h[i]*(R[i]-L[i]+1))$

------------

### 关于时间复杂度：

计算L和R数组时，只要某个下标被算在了某个L[i],R[i]中，

就不会被再次计算，所以，每一个下标只被包含（计算）了一次

所以，该算法的时间复杂度为 $O(n)$ , 不比单调栈慢

------------


代码比较简单：

```
#include <bits/stdc++.h>
using namespace std;
const int N=100000+15;
long long n,h[N],L[N],R[N];
int main(){
	while(1){
		scanf("%d",&n);
		if(n==0) break;
		for(int i=1;i<=n;i++) scanf("%d",&h[i]);
		for(int i=1;i<=n;i++) L[i]=R[i]=i;  //初始化 
		for(int i=1;i<=n;i++){
			while(L[i]-1>=1 && h[L[i]-1]>=h[i]) L[i]=L[L[i]-1];
		}
		for(int i=n;i>=1;i--){
			while(R[i]+1<=n && h[R[i]+1]>=h[i]) R[i]=R[R[i]+1];
		}
		long long ans=0;
		for(int i=1;i<=n;i++) ans=max(ans,h[i]*(R[i]-L[i]+1));
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：zi小眼聚光 (赞：11)

## 笛卡尔树
这么好的一道题为啥没人写笛卡尔树呢qwq

笛卡尔树是一颗二叉树，它既满足二叉搜索树的性质，又满足堆的性质。
即对于一个序列，笛卡尔树的中序遍历是原序列，而序列中较小（大）的元素一定是较大（小）元素的祖先，下图就是一棵笛卡尔树（小根）：

![一棵笛卡尔树](https://cdn.luogu.com.cn/upload/image_hosting/awvear5j.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

#### 笛卡尔树的构造

我们用增量法构造笛卡尔树，时间复杂度为**O(n)**

按照原序列的顺序依次加入点，由于二叉搜索树的性质，新加入的点一定在树的最右链上，由于最右链的点权值是单调的，所以我们用单调栈来维护最右链，每加入一个点，就在栈中找到第一个比它大（小）的点x，作为它的父亲，栈中x后面的第一个点作为它的左儿子，最后把当前点压栈。

由于单调性，树的根节点一定是单调栈中第一个元素

构造代码：

```cpp
scanf("%lld",&a[i]);
while(tp&&a[stk[tp]]>=a[i])ls[i]=stk[tp--];
fa[ls[i]]=i;
fa[i]=stk[tp];
if(fa[i])rs[fa[i]]=i;
stk[++tp]=i;
```

### 本题题解

我们维护一个小根堆，一个点的子树一定是它周围的比它大的点，那么答案就是max{siz[i]*h[i]}


代码：

```cpp
#include <cstdio>//sp1805
#include <iostream>
#include <cstring>
#define N 100005
#define int long long
using namespace std;
int n,a[N],ans,fa[N],ls[N],rs[N],siz[N];
int stk[N],tp;
void print(int x){
  if(ls[x])print(ls[x]);
  printf("%d %d %d\n",x,ls[x],rs[x]);
  if(rs[x])print(rs[x]);
}
void dfs(int x){
  if(ls[x])dfs(ls[x]);
  if(rs[x])dfs(rs[x]);
  siz[x]=siz[ls[x]]+siz[rs[x]]+1;
  ans=max(ans,a[x]*siz[x]);
}
signed main(){
  while(scanf("%lld",&n)!=EOF&&n){
    memset(fa,0,sizeof(fa));
    memset(ls,0,sizeof(ls));
    memset(rs,0,sizeof(rs));
    memset(siz,0,sizeof(siz));
    tp=0;ans=0;
    for(int i=1;i<=n;++i){
      scanf("%lld",&a[i]);
      while(tp&&a[stk[tp]]>=a[i])ls[i]=stk[tp--];
      fa[ls[i]]=i;
      fa[i]=stk[tp];
      if(fa[i])rs[fa[i]]=i;
      stk[++tp]=i;
    }
    // print(stk[1]);
    dfs(stk[1]);
    printf("%lld\n",ans);
  }
  return 1;
}
/*
11
9 3 7 1 8 12 10 20 15 18 5
*/
/*
7
2 1 4 5 1 3 3
*/

```



---

## 作者：zyzzyzzyzzyz (赞：7)

# 单调栈的好题

[题目链接](https://www.luogu.org/problemnew/show/SP1805)

**题目是求最大矩形面积**

------

### 1.BF思路

可以想到最后大矩形的上边界一定是某个小矩形的顶

那么我们就枚举每一个小矩形,

将其顶作为限制条件尽可能地向两边扩展

复杂度$O(n^2)$

------

### 2.单调栈做法
![](https://img2018.cnblogs.com/blog/1511953/201812/1511953-20181215093805470-1760391592.png)




如图,黑色为最终要求的矩形

**我们可以维护一个单调递增栈**
![](https://img2018.cnblogs.com/blog/1511953/201812/1511953-20181215093519905-968161074.png)



如上图:(从黄色的矩形(Y)向右扩展,假设左边所有矩形递增)

​	①:此时右边的矩形高于左边矩形,不影响黄色矩形继续向右扩展,可以加入单调栈

​	②:此时右边的矩形低于左边的矩形,那么以左边的矩形为最大高度的矩形不能向右扩展,于是可以向左统计答	案.又因为从左往右已经是单调递增,那么可以直接统计答案,同时将此矩形退栈.以此类推,直到栈顶元素的高度小于新加入的矩形的高度.
![](https://img2018.cnblogs.com/blog/1511953/201812/1511953-20181215093545115-718636570.png)



如图,最右边的矩形加入时会将左侧的两个矩形退栈,并相应地计算这两个矩形的答案.然后这两个矩形的上部(红棕色部分)可以舍弃,因为它们不会再产生任何贡献.需要注意的是,在退栈时,还要将退栈元素的宽度加起来,再赋值给新加入的矩形,那么此时最右边的矩形实际上代表图中的所有蓝色部分.当以后有更矮的矩形进栈且需要将蓝色部分退栈时,统计答案就可以直接 $hight\times width$ .

**这样做的正确性在于:当该矩形退栈时,其左边的第一个元素(即栈中在它以下的第一个元素)是第一个比它矮的;其右边的矩形一定比它矮(不然就不需要退栈了)**



### 3.代码

```cpp
#include<bits/stdc++.h>
#define R register int
using namespace std;
int n,h[100006],wid[100006],s[100006],top;
long long ans;//注意要开longlong
int main()
{
    while(cin>>n)
    {
        if(n==0)return 0;
        memset(s,0,sizeof(s));
        memset(h,0,sizeof(h));
        memset(wid,0,sizeof(wid));
        top=0;ans=0;//记得清零!!!
        for(R i=1;i<=n;i++)
            cin>>h[i];
        h[++n]=0;//加入一个高度为0的点,可以在最后统计答案,不会遗漏
        for(R i=1;i<=n;i++)
        {
            int width=0;
            while(top&&h[s[top]]>h[i])
            {
                width+=wid[top];
                ans=max(ans,(long long)width*h[s[top]]);
                top--;
            }
            s[++top]=i;
            wid[top]=width+1;
        }
        cout<<ans<<endl;
    }
}

```

---

## 作者：mol茶蛋糕 (赞：6)

这道题用到了**单调栈**的知识  

简单想想，如果矩形是一个单调递增的序列，那么O(n)就可以解决问题（即一次线性处理），而这道题，就可以看成是多个单调增序列。  

而相邻两个序列之间的关系就是两个序列间的最矮的一个，处理后一个序列时把前面的比那个两序列中间最矮的高出的一截删去也没有影响（因为把前面的那个看成单调增序列处理了之后，就需要维持后一个序列的单调性，而且前面那一个已经被记录了最值，所以就可以不要了）。  

还需要一直记录一下宽度wide，来求得面积。  

最后增加一个高度为0的矩形，用来处理剩余的矩形。

复杂度是O(n)。


~~~
#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;
long long hig[100005];
stack<long long>h;
stack<long long>w;
int main()
{
	long long n;
	while(~scanf("%lld",&n))
	{
		long long ans=0;
		if(n==0)	
			return 0;
		memset(hig,0,sizeof hig);
		while(!h.empty())
			h.pop();
		while(!w.empty())
			w.pop();	
		for(long long i=1;i<=n;i++)
			scanf("%lld",&hig[i]);
		hig[n+1]=0;
		h.push(0);
		for(long long i=1;i<=n+1;i++)
		{
			if(h.top()<hig[i])		//维持一个单调递增的序列 
				h.push(hig[i]),w.push(1);
			else
			{
				long long wide=0;
				while(h.top()>hig[i])		//使这一个高度可以找到尽量最前面
				{
					wide+=w.top();		//因为是单调增，所以直接加就行 
					ans=max((long long)ans,(long long)wide*h.top());
					w.pop(),h.pop();
				}
				h.push(hig[i]),w.push(wide+1);		//w.push进去 这一个高度可以跑到的最前面一共的宽度再加上这一块单独的矩形的宽度
			}
		}
		printf("%lld\n",ans);
	}
}
~~~

---

## 作者：linwenqi (赞：4)

### 题解:
这是一道经典题，可以用多种方法解答。
比如：单调栈，直接暴力，ST表，笛卡尔树。
我讲一下**直接暴力**的方法。（其他的方法参考我的博客https://blog.csdn.net/linwenqidbk/article/details/96617124 ）


我们可以设left[i]表示最左一直比它高的位置，right[i]则同理。

求法看看这里：

```cpp
while(left[i] - 1 >= 1 && h[left[i] - 1] >= h[i]){
	left[i] = left[left[i] - 1];
}
```

相信你能理解（这是不是很暴力？）其实均摊复杂度只有O(n);注意求left[i],从前往后枚举，right[i]从后往前枚举就好了。

### AC代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 100005;
long long a[N];
int l[N];
int r[N]; 
int main(){
	int n, i;
	while(1){
		scanf("%d", &n);
		if(n == 0) break;
		for(i = 1; i <= n; i++){
			scanf("%lld", &a[i]);
			l[i] = i;
			r[i] = i; 
		}
		for(i = 1; i <= n; i++){
			while(l[i] - 1 >= 1 && a[l[i] - 1] >= a[i]){
				l[i] = l[l[i] - 1];
			}
		}
		for(i = n; i >= 1; i--){
			while(r[i] + 1 <= n && a[r[i] + 1] >= a[i]){
				r[i] = r[r[i] + 1];
			}
		}
		long long ans = -1;
		for(i = 1; i <= n; i++){
			ans = max(ans, (r[i] - l[i] + 1) * a[i]);
		}
		printf("%lld\n", ans);  
	}
	return 0;
}

```


---

## 作者：pipiispig (赞：4)

###这样一个单调栈的好题竟然没人用stl来做（滑稽），然而本蒟蒻即使知道算法还是被卡了2个小时，QWQ,脑洞模拟的灾难。
```#include<iostream>
#include<cstdio>
#include<stack>
#include<cstring>
using namespace std;
inline long long read(){
	long long x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return f*x;
}//很伤心呢，看错范围了，最初没改成long long 类型的，爆了几次才发现QWQ
struct node{
	int h,w;
};//一个存高度，一个存宽度。
long long s[100100],ans=0;
int main(){//短的出乎我的意料。
	while(1){
		int n=read();
		if(n==0)return 0;
		for(int i=1;i<=n;i++){
			s[i]=read();
		}
		stack<node>st;
		s[n+1]=0;
		for(int i=1;i<=n+1;i++){
			long long W=0;
			while(!st.empty()&&s[i]<st.top().h){//单调栈！单调递增！
				W=W+st.top().w;
				ans=max(ans,W*st.top().h);
				st.pop();
			}
			st.push((node){s[i],W+1});
		}
		cout<<ans<<endl;
		ans=0;
	}
}```

---

## 作者：ShineEternal (赞：2)

# 写在前面：如想获得更佳阅读效果，请点击[这里](https://blog.csdn.net/kkkksc03/article/details/85011535)，如有任何疑惑，欢迎私信作者！

# 题目链接：https://www.luogu.org/problemnew/show/SP1805

# 分析：

![在这里插入图片描述](https://cdn.luogu.com.cn/upload/pic/46201.png)
我们可以用一个单调栈由低到高来存储它的高度，并用数组对每个高度记录一下它前面（包括它自己）一共有多少个比它高的，可以看做它的左宽。

按顺序考虑每个高度h，如果h大于栈顶元素，则入栈，此时它大于左面全部的元素，并且将它的宽度初始为1。

否则，将栈内元素出栈，直到满足上面的条件。出栈时，我们要将出栈元素对之后问题的影响全部考虑进行处理，才能保证做法的正确性。

对于每个高度，它的作用无非两个：

1、以自己作高，向外扩展        

2、以别人作高，自己被扩展

由于我们数组中已经记录了某个高度的左宽，所以我们只需要考虑它能不能向右扩展，如果能，能扩展多少？

首先，对于第一个出栈的元素来说，它的右宽一定是0。

然而对于第二个，它的右边有刚才出栈的元素，而且刚才出栈元素的总宽中所涉及的元素一定可以被自己扩展，所以自己的右宽为刚才出栈元素的总宽。

同理可知，第三个出栈元素的右宽为第二个出栈元素的总宽。依次类推。

而当h大于栈顶元素时，h的左宽应该是上次出栈元素的总宽+1（自己），然后入栈。

最后时，将所有元素出栈，即可将所有情况考虑。


# 代码.~~吹泡泡~~cpp
```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
struct ben
{
    long long h,w;
}a[100005];
long long n,h[200005],ans;
void ddz()
{
    ans=0;
    int top=0;
    h[n+1]=0;
    for(int i=1;i<=n+1;i++)
    {
       	if(h[i]>a[top].h)
       	{
       		a[++top].h=h[i];
       		a[top].w=1;
       	}
    	else
        {
            long long qaq=0;
            while(a[top].h>h[i])
            {
                qaq+=a[top].w;
                ans=fmax(ans,qaq*a[top].h);
                top--;
            }
            a[++top].h=h[i];
            a[top].w=qaq+1;
        }
    }
    printf("%lld\n",ans); 
}
int main()
{
    while(1)
    {
        scanf("%lld",&n); 
        if(n==0)
			break;
        memset(h,0,sizeof(h));
        for(int i=1;i<=n;i++)
            scanf("%lld",&h[i]);
        ddz();
    }
   	return 0;
}
额，和楼下一位大佬的代码很像啊
```



---

## 作者：Drug (赞：2)

从左到右维护一个高度递增的栈并且记录每个元素的宽度，弹出一个元素的时候用它更新答案。

为什么呢

因为所有可能成为答案的矩形它的四条边都无法再向四周扩散。每一个给定的矩形宽度都为一，所以我们不妨从左到右遍历一遍整个矩形图。假设第一个矩形高是5，那么包含它的可能成为答案的矩形的高度一定是5(显然)，那么第一个矩形的右面有多少个连续不断的高于第一个矩形矩形就决定了包含它的可能答案(tot)。如果遇到小于5的一个矩形，就弹出栈中元素，由此合并出可能的答案。最后枚举答案求出最大值即可。
```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<cstdlib> 
#include<string>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
const int N = 100005;
struct Drug
{
	int height;
	int count;
};
Drug stack[N];
ll top, h, n, ans, tot, tmp;//tmp存宽度，tot存可能的矩形面积 
int main()
{
	while(scanf("%d", &n) != EOF && n)
	{
		top = 0;
		ans = 0;
		for(int i = 1; i <= n; i++)
		{
			scanf("%d", &h);
			tmp = 0;
			while(top > 0 && stack[top - 1].height >= h)//维护单调栈 
			{
				tot = stack[top - 1].height * (stack[top - 1].count + tmp);
				if (tot > ans) ans = tot;
				tmp += stack[top - 1].count;
				--top;
			}
			stack[top].height = h;
			stack[top].count = 1 + tmp;
			++top;
		}
		tmp = 0;
		while (top > 0)//出栈 
		{
			tot = stack[top - 1].height * (stack[top - 1].count + tmp);
			ans = max(tot, ans);
			tmp += stack[top - 1].count;
			--top;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：luyan (赞：1)

题目：
如图所示，在一条水平线上有n个宽为1的矩形，求包含于这些矩形的最大子矩形面积（图中的阴影部分的面积即所求答案）。

输入格式：

   有多组测试数据，每组数据占一行。输入零时读入结束。
   
   每行开头为一个数字n（1<=n<=100000）,接下来在同一行给出n个数字h1h2...hn（0<=hi<=1000000000）表示每个矩形的高度。

输出格式：

   对于每组数据，输出最大子矩阵面积，一组数据输出一行。


做法一：我们预处理出每一个矩形可以最多向左右延伸的终点
 
l，r数组分别代表第i个矩形最多可以向左右扩展的矩形位置，也就是找到第一个比它矮的矩形，核心代码就是那个while循环。
预处理出来这两个数组之后我们就可以总结答案。
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long read(){
	char s;
	long long f=1,x=0;
	s=getchar();
	while(s<'0'||s>'9'){
		if(s=='-')f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9'){
		x*=10;
		x+=s-'0';
		s=getchar();
	}
	return x*f;
}
int n;
long long l[1000010],r[1000010];
long long h[1000010];
int main(){
	while(1){
		n=read();
		if(n==0)return 0;
		memset(h,0,sizeof(h));
		memset(l,0,sizeof(l));
		memset(r,0,sizeof(r));
		for(int i=1;i<=n;i++){
			h[i]=read();
		}
		for(int i=1;i<=n;i++){
			l[i]=i;
			while(l[i]-1>=0&&h[l[i]-1]>=h[i]){
				l[i]=l[l[i]-1];
			}
		}
		for(int i=n;i>0;i--){
			r[i]=i;
			while(r[i]+1<=n&&h[r[i]+1]>=h[i]){
				r[i]=r[r[i]+1];
			}
		}
		long long ans=0;
		for(int i=1;i<=n;i++){
			ans=max(ans,h[i]*(r[i]-l[i]+1));
		}
		cout<<ans<<endl;
	}
} 
```



做法二：我们可以用单调栈来更快地找到法一中的左右延伸的终点

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;
long long read(){
	char s;
	long long f=1,x=0;
	s=getchar();
	while(s<'0'||s>'9'){
		if(s=='-')f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9'){
		x*=10;
		x+=s-'0';
		s=getchar();
	}
	return x*f;
}
long long n;
long long ans=0;
long long st[1000010];
long long h[1000010];
long long w[1000010];
int main(){
	while(1){
		n=read();
		if(n==0)return 0;
		memset(h,0,sizeof(h));
		int top=-1;
		ans=0;
		for(int i=1;i<=n;i++){
			h[i]=read();
		}
		h[n+1]=0;
		for(int i=1;i<=n+1;i++){
			if(top==-1||h[st[top]]<=h[i]){
				st[++top]=i;
				w[st[top]]=1;
			}
			else{
				long long wide=0;
				while(top>=0&&h[st[top]]>h[i]){
					wide+=w[st[top]];
					ans=max(ans,wide*h[st[top]]);
					top--;
				}
				st[++top]=i;
				w[st[top]]=wide+1;
			}
		}
		cout<<ans<<endl;
	}
}
```
做法三：笛卡尔树
1.介绍一下笛卡尔树
笛卡尔树的每一个节点都有两个值，val与key。val是原数组的值，key是下标
笛卡尔树有两个特点：1.任意一颗子树的中序遍历结果表示数组的一段区间
									2.笛卡尔树的val值满足大（小）根堆的性质

首先关于建树：
我们用一个stack来记录**最右端的一条链**中的节点。
这个栈是一个单调栈，我们从左向右遍历每一个节点。
有以下几条规则：1.由于第一个特点（任意一颗子树的中序遍历结果表示数组的一段区间），我们每新加入一个节点它目前只能有左儿子，且只能作为右儿子或者根节点。

具体步骤如下：1.在栈中找到第一个val值小于（这道题维护的是小根堆）的节点，把该节点以下的节点均踢出栈。2.这个新加节点就是它的右儿子，如果有被踢出的节点，则最后一个被踢出的就是新加节点的左二子。由于STL中的栈很难记录被踢出的上一个元素，所以我们用一个数组来维护一个栈。3.将这个新节点入栈

核心代码：
```
void build(){
	memset(st,0,sizeof(st));
	int top=-1;
	int k;
	for(int i=1;i<=n;i++){
		k=top;
		while(k>=0&&t[st[k]].val>=t[i].val)k--;
		if(k!=-1){//如果还有元素，也就是它有父亲节点
			t[st[k]].rs=i;		
			t[i].fa=st[k];	
		}
		if(k<top){//如果有儿子
			t[i].ls=st[k+1];
			t[st[k+1]].fa=i;
		}
		st[++k]=i;//入栈
		top=k;
	}
	root=st[0];
}
```
以下为完整代码：
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
long long read(){
	char s;
	long long x=0,f=1;
	s=getchar();
	while(s<'0'||s>'9'){
		if(s=='-')f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9'){
		x*=10;
		x+=s-'0';
		s=getchar();
	}
	return x*f;
}
int n;
struct tree{
	int key;
	long long val;
	int ls,rs,fa;
	long long size;
}t[500050];
long long st[500050];
int root=0;
void build(){
	memset(st,0,sizeof(st));
	int top=-1;
	int k;
	for(int i=1;i<=n;i++){
		k=top;
		while(k>=0&&t[st[k]].val>=t[i].val)k--;
		if(k!=-1){
			t[st[k]].rs=i;		
			t[i].fa=st[k];	
		}
		if(k<top){
			t[i].ls=st[k+1];
			t[st[k+1]].fa=i;
		}
		st[++k]=i;
		top=k;
	}
	root=st[0];
}
long long ans=-1;
void dfs(int rt){
	if(t[rt].ls!=-1){
		dfs(t[rt].ls);
		t[rt].size+=t[t[rt].ls].size;
	}
	if(t[rt].rs!=-1){
		dfs(t[rt].rs);
		t[rt].size+=t[t[rt].rs].size;
	}
	ans=max(ans,t[rt].size*t[rt].val);
	return;
}
int main(){
	while(1){
		n=read();
		if(n==0)return 0;
		ans=-1;
		for(int i=1;i<=n;i++){
			t[i].val=read();
			t[i].key=i;
			t[i].ls=t[i].rs=-1;
			t[i].size=1;
			t[i].fa=-1;
		} 
		build();
		dfs(root);
		cout<<ans<<endl;
	}
}
```


---

## 作者：风浔凌 (赞：1)

一个单调栈的题目~~

~~本来想用线段树维护区间最小值，但是感觉......~~

主体思路是依次遍历每个的高度，然后以它的高度为标准向左右拓展......

具体的看代码好了......有注释的。

其实这个题本来是绿题的......~~但是...咳咳......现在变成了一个蓝题.......~~所以.......它应该并不是特别难
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
#define N 100010
using namespace std;
int L[N],R[N],st[N],h[N];
int n;
int main(){
     while(true){
     //输入
        scanf("%d",&n);
        if(n==0) break;
        for(int i=0;i<n;i++) scanf("%d",&h[i]);
        int t=0;
        //向左边拓展
        for(int i=0;i<n;i++){
             while(t&&h[st[t-1]]>=h[i]) t--;
             //因为我们要维护栈里面元素的单调性
             //所以要将所有栈里面大于当前元素的全部弹出
             //注意当t=0的时候就不能拓展了
             if(t==0)   
			    L[i]=-1;
                //这个是现在栈里面就只有一个元素
                //那么向左拓展是拓展不了的
             else  
			    L[i]=st[t-1];
                //否则就加入当前元素
             st[t++]=i;
             //哦，对了，这里提醒一点，栈里面存的应该是序号
        }
        t=0;
        //开始向右边拓展，但是这个操作其实和倒着向左拓展是一样的
        //所以我们倒着向左拓展
        //操作同上，只有不小于自己高度才可以拓展
        for(int i=n-1;i>=0;i--){
             while(t&&h[st[t-1]]>=h[i]) t--;
             if(t==0) 
                R[i]=n;
            else 
                R[i]=st[t-1];
                //因为是倒着拓展，所以同理将i的R边界添加
             st[t++]=i;
        }
        //最后来统计矩形面积
        ll ans=0;
        for(int i=0;i<n;i++){
            ans=max(ans,(ll)h[i]*(R[i]-L[i]-1));
            //手动模拟一下就知道为什么这里要减一了......
            //本来区间的长度应该是r-l+1但是因为左右两边都多算了一个
            //所以再减2之后就是r-l-1
            //统计最大值
        }
        printf("%lld\n",ans);
     }
     return 0;
}
```

---

## 作者：Rye_Catcher (赞：1)

- 题目链接：     https://www.luogu.org/problemnew/show/SP1805
  http://poj.org/problem?id=2559
  
- 思路：

   ## 单调栈
   
   首先如果所有矩形的高度是单调递增的，即新加入的矩形比上一个高,那么把加进来直至加完，这是我们就把分别每个矩形的高度看做是最大子矩形的高度，分别向左右拓展求得最大面积。
   
   然而矩形的高度不一定是递增的，如果新加入的矩形比上一个小，那么之前**这些矩形的高度对于后面的计算就没用了**。我们就在这时候把比这个新加的矩形高的部分全部删掉，这样就能保持矩形都是单调递增的。
   
   具体实现的方法简单说就是将之前比这高的矩形弹出栈知道遇到比新矩形低的矩形，同时累计他们的宽度之和，乘以这个更矮矩形的高度来更新答案。最后再按这个方法把所有矩形弹出去来更新答案。
   
- 小技巧：

   - 将a[n+1]设为0保证最后能将所有矩形弹出去（想想为什么）
- 代码：

```
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cctype>
#define ll long long  
using namespace std;
const int maxn=100010;
int a[maxn],w[maxn],s[maxn];//w记录宽度
ll ans;
int n;
template <class T>inline void read(T &x){
	x=0;char c;int neg=0;
	while(!isdigit(c=getchar()))neg=c=='-';
	x=c-48;
	while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
	x=neg?-x:x;
	return ;
}  
inline void solve(){
	int p;
	a[n+1]=p=0;//这样最后能将所有矩形弹出栈
	for(register int i=1;i<=n+1;i++){
		if(a[i]>s[p]){
			s[++p]=a[i];
			w[p]=1;
		}
		else {
			int wid=0;
			while(s[p]>a[i]){
				wid+=w[p];
				ans=max(ans,(ll)wid*s[p]);
				p--;
			}
			s[++p]=a[i],w[p]=wid+1;
		}
	}
	cout<<ans<<endl;
	return;
}
int main()
{
	while(scanf("%d",&n)!=EOF){
	    if(!n)break;
		ans=0;
		for(register int i=1;i<=n;i++){
		  read(a[i]);
		}
		solve();
	}
	return 0;
}
```
  

---

## 作者：霍士弘 (赞：0)

## 前置知识：单调栈
单调栈是一种特殊的栈，栈内的元素一定是有序的，这方便我们维护一些信息。  
单调栈可以在 $O(n)$ 的时间内求出一个序列中每个数前面/后面第一个比它小/大的数字的**位置**。
如果不会单调栈的话，可以去[这道题](https://www.luogu.com.cn/problem/P5788)的题解区里学习。  
## 观察性质
首先观察一波题目性质：  
### 性质1
令每个小矩形的高度为 $h_1,h_2,\ldots,h_n$。    
如果取 $[l,r]$ 里面的所有小矩形拼成一个大矩形，则面积为 $\min_{l \leq j \leq r}\{ h_j\} \times (r - l + 1)$。  
答案就是最大化这个东西。  
### 性质2
然后假设我们选出来了一个最大矩形，设它的左端点为 $L$，右端点为 $R$，矩形高度为 $H$。  
则必有 $h_{L-1} < H$，$h_{R+1} < H$  
证明考虑反证法，假设 $h_{L-1} \geq H$，这个矩形还可以扩展成一个宽度更宽的矩形，则这个“最大矩形”矛盾。  
右边同理。  
### 性质3
最大矩形一定填满了至少一个小矩形，且小矩形的高度一定是答案矩形这个区间中最小的。  
考虑反证，如果连最矮的都填不满的话，更高的肯定填不满，所以可以通过填满最小高度的矩形可以得到更大的面积，所以与最大矩形矛盾。  
综合以上性质，我们就可以得到这道题目的解法了。  
## 解法
首先，对于每一个小矩形，它向左右延伸，最多只能延伸到第一个比它小的地方的前一个矩形。  
所以，我们可以利用单调栈 $O(n)$ 求出每个小矩形前面和后面**第一个**比它**小**的矩形的**位置**。然后对于每个矩形延伸出来的答案取最大值即可。  
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#define maxn 100000
#define ll long long
using namespace std;
ll read()
{
	char c = getchar();
	ll s = 0,w = 1;
	while(c < '0' || c > '9')
	{
		if(c == '-') w = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		s = (s * 10) + (c - '0');
		c = getchar();
	}
	return w * s;
}
int n;
ll a[maxn + 10];
ll fl[maxn + 10];//fl[i] 为i前面第一个比它小的位置
ll fr[maxn + 10];//fr[i] 为i后面第一个比它小的位置
ll s[maxn + 10];
int tot = 0;
void push(int x)
{
	s[++tot] = x;
}
void pop()
{
	s[tot] = -1;
	tot--;
}
ll top()
{
	return s[tot];
}
bool empty()
{
	return tot == 0 ? true : false;
}
void clear()
{
	tot = 0;
	memset(s,0,sizeof(s));
}
void print()
{
	if(empty()) 
	{
		cout<<"empty"<<endl;
		return ;
	}else
	{
		for(int i = 1;i <= tot;i++)
		{
			cout<<s[i]<<' ';
		}
		cout<<endl;
	}
	
}
ll labs(ll x)
{
	return x < 0 ? -x : x;
}
ll lmax(ll a,ll b)
{
	return a >= b ? a : b;
}
int main()
{
	n = read();
	while(n != 0)
	{
		ll ans = -1;
		clear();
		memset(a,0,sizeof(a));
		for(int i = 1;i <= n;i++)
		{
			a[i] = read();
		}
	//	a[0] = -1,a[n + 1] = -1;
		for(int i = n;i >= 1;i--)
		{
		//	print();
			if(empty())
			{
				fr[i] = 0;
				push(i);
			}else if(a[i] > a[top()])
			{
				fr[i] = top();
				push(i);
			}else if(a[i] <= a[top()])
			{
				while(!empty() && a[i] <= a[top()])
				{
					pop();
				}
				if(empty())
				{
					fr[i] = 0;
				}else
				{
					fr[i] = top();
				}
				push(i);
			}
		}
		clear();
		for(int i = 1;i <= n;i++)
		{
			if(empty())
			{
				fl[i] = 0;
				push(i);
			}else if(a[i] > a[top()])
			{
				fl[i] = top();
				push(i);
			}else
			{
				while(!empty() && a[i] <= a[top()])
				{
					pop();
				}
				if(empty())
				{
					fl[i] = 0;
				}else
				{
					fl[i] = top();
				}
				push(i);
			}
		}
		for(int i = 1;i <= n;i++)
		{
			if(a[i] == 0) ans = lmax(ans,0);
			ll widthl,widthr,width;
			if(fl[i] == 0)
			{
				widthl = labs(i - 1);
				widthr = labs(fr[i] - i) - 1;
			}
			if(fr[i] == 0)
			{
				widthr = labs(n - i);	
				widthl = labs(fl[i] - i) - 1;	
			}
			if(fl[i] != 0 && fr[i] != 0)
			{
				widthl = labs(fl[i] - i) - 1;
				widthr = labs(fr[i] - i) - 1;
			}
			width = widthl + widthr + 1;
			ll squ = (ll)width * (ll)a[i];
			ans = max(ans,squ);
		//	cout<<fl[i]<<' '<<fr[i]<<' '<<squ<<endl;
		}
		cout<<ans<<endl;
		n = read();
	}
}
```  
~~代码很丑，别介意~~

---

## 作者：ViXpop (赞：0)

### 单调栈模板题

其实这题和[P2422 良好的感觉](https://www.luogu.org/problem/P2422)的思路是比较相近的（起码我的对于两题的做法是差不多的）

我们先把题意转化成通俗易懂的语言

##### 这题就是想让我们对于一串数，求出最大的子序列的元素个数与子序列中最小的数的乘积

转化题意之后，本蒟蒻的第一反应就是单调栈

我们假设每一个数的权值（也就是高度）为$h_i$

然后对于每个数维护两个数组：$l_i$和$r_i$，这两个数组代表当前数在哪一个区间内是最小值

维护两个数组之后，答案就可以枚举每一个点，求出最大的$(r_i-l_i+1)*h_i$

而单调栈的用途就是维护$l_i$和$r_i$数组，在这到题中，我们需要维护一个单调递增的栈

我们拿一组简单的数据来模拟一下这组过程：$3,1,6,4,5,2$

刚开始的时候，栈为空，每个数的$l_i$和$r_i$均为$i$（下文用($l,r$）表示一个数字的$l_i$和$r_i$数组)

首先$3$进栈，状态为($1,1$)

接着要进栈的是$1$，状态为($2,2$)，因为$1<3$，而我们需要的是单调递增栈，所以将$3$弹出栈，同时将$1$的状态更新为（$1,2$）

然后要进栈的是$6$，$6>1$，直接进栈，状态为（$3,3$）

接下来是$4$，$4<6$，将栈中所有大于$4$的元素全部弹出后更新4的状态，这里$4$的状态更新为（$3,4$）

以此类推，最后这一串数字的状态为$3$（$1,1$），$1$（$1,2$），$6$（$3,3$）,$4$（$3,4$），$5$（$5,5$），$2$（$3,6$）

有的神犇看到这里也许会问：你推出来的最终状态怎么和我推的不一样啊

我会告诉你：因为~~你是神犇所以你是对的~~这里我只维护了$l_i$数组，每跑一遍维护过程是只能维护一个数组的，还需要倒着跑一遍去维护另外一个数组

特别的，我们需要给$h_0$和$h_{n+1}$赋值为$-1$，以便于最后将所有元素全部弹出栈统计最终状态

两个数组维护完之后直接求出最大答案输出即可

#### 接下来本蒟蒻放上自己的丑陋的代码供大家参考

```
#include <bits/stdc++.h>
#define mem(i,j) memset(i,j,sizeof(i))
#define int long long
using namespace std;
inline int read(){
    int res=0,f=1;char ch=' ';
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
    return res*f;
}
const int N=1e5+5;
int n,h[N],top,st[N],l[N],r[N],ans;
void init(){
	mem(h,0);mem(st,0);
	top=0;ans=0;
}
#undef int
int main() {
	while(scanf("%lld",&n)&&n){
		init();
		for(register int i=1;i<=n;i++)h[i]=read();
		h[n+1]=h[0]=-1;//先给h[0]和h[n+1]赋值为-1
		for(register int i=1;i<=n+1;i++){
			if(!top||h[st[top]]<h[i]){
            st[++top]=i,l[i]=i;
            continue;
        }
			while(top&&h[st[top]]>=h[i])l[i]=l[st[top--]];
			st[++top]=i;
		}//维护左端点
		top=0;mem(st,0);
		for(register int i=n;i>=0;i--){
			if(!top||h[st[top]]<h[i]){
        	st[++top]=i,r[i]=i;
          continue;
        }
			while(top&&h[st[top]]>=h[i])r[i]=r[st[top--]];
			st[++top]=i;
		}//维护右端点
		for(register int i=1;i<=n;i++)
        ans=max(ans,(r[i]-l[i]+1)*h[i]);
		printf("%lld\n",ans);
	}
    return 0;
}
```


---

## 作者：mcqueen (赞：0)

### 的确，这是一道 _单调栈_ 的模板题，然而，我们可以用RMQ来解决。

考虑一种分治的做法:

对于每个区间，我们若是找出这个区间中最小值的下标，那么，该下标可以延伸的**最大宽度**即为这整个区间。

然后，我们将这个区间从找到的最小值的**下标**分开，分成左右两个区间，在依次进行同样的运算，这样，我们就可以得到所有下标能够延伸的**最大宽度**。

运用基于**倍增**的ST表可以做到O(nlogn)预处理，O(1)查询任意区间的**最小值下标**。

这样，题目就解决了。

另外本题数据范围较大，要开**long long**。

**代码：**

```cpp
#include<bits/stdc++.h>
#define ll long long
const int N=1e5+5;
using namespace std;
namespace rmq
{
	int dp[20][N],n,Log[N];
	void hello_World()
	{
		Log[1]=0;
		for(int i=2;i<N;i++)
		Log[i]=Log[i>>1]+1;
	}//预处理所有数的log。
	void InIt(int a[],int tot)
	{
		n=tot;
		for(int i=0;i<n;i++)
		dp[0][i]=i;
		
		for(int i=1;i<18;i++)
		for(int j=0;j<n;j++)
		{
			if(a[dp[i-1][j]]<=a[dp[i-1][j+(1<<(i-1))]])
			dp[i][j]=dp[i-1][j];
			else dp[i][j]=dp[i-1][j+(1<<(i-1))];
		}
	}
 //预处理ST表，dp[i][j]表示从j开始（包括j）2^i个元素中最小元素的下标
	
    int query(int l,int r,int a[])
	{
		int k=Log[r-l+1];
		if(a[dp[k][l]]<=a[dp[k][r-(1<<k)+1]])
		return dp[k][l];
		return dp[k][r-(1<<k)+1];
        //查找区间[l,r]中最小元素的下标
	}
}
int n,a[N],w[N];
inline void chmax(ll &x,ll y){x=x>y?x:y;}
void dfs(int l,int r)
{
	
	if(r<l)return;
	int t=rmq::query(l,r,a);
	w[t]=(r-l+1);
	dfs(l,t-1);//往左区间分治
	dfs(t+1,r);//往右区间分治
}
void work()
{
	for(int i=0;i<n;i++)
	scanf("%d",a+i);
	
	rmq::InIt(a,n);//初始化
	dfs(0,n-1);//分治
	ll ans=0;
	
	for(int i=0;i<n;i++)
	chmax(ans,(ll)w[i]*a[i]);//答案为高度×宽度
	printf("%lld\n",ans);
}
int main()
{
	rmq::hello_World();
	while((scanf("%d",&n)==1)&&n)work();
	return 0;
}
```

另外，本题也可以用**笛卡尔树**做，感兴趣的同学可以百度一下。


---

## 作者：Azuree (赞：0)

[查看原题请戳这里](https://www.luogu.org/problemnew/show/SP1805)  
我们用单调栈来维护每一个小矩形的左侧和右侧第一个比它低的矩形的位置。为什么要维护这个呢？根据木桶原理，每一个大矩形的高度是由其高度最小的矩形的高度决定的，所以我们要去记录第一个比当前矩形小的矩形的位置。
ps：别忘了初始化qwq……  
附一下代码：  
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 0x7fffffff
#define re register
#define pie 3.1415926

using namespace std;

int read()
{
	register int x = 0,f = 1;register char ch;
	ch = getchar();
	while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
	while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}

int n,t,q,l[100005],r[100005],sta[100005],p;

struct build{
	int x,h;
}b[100005];

void init1(int k)
{
	if(p == 0)
	{
		sta[++p] = k;
		return ;
	}
	if(b[k].h >= b[sta[p]].h)
	{
		sta[++p] = k;
		return ;
	}
	while(b[sta[p]].h > b[k].h && p) 
	{
		l[sta[p]] = k;
		p --;
	}
	sta[++p] = k;
}

void init2(int k)
{
	if(p == 0)
	{
		sta[++p] = k;
		return ;
	}
	if(b[k].h >= b[sta[p]].h)
	{
		sta[++p] = k;
		return ;
	}
	while(b[sta[p]].h > b[k].h && p)
	{
		r[sta[p]] = k;
		p --;
	}
	sta[++p] = k;
}

ll ans;

int main()
{
	n = read();
	while(n != 0)
	{
		ans = 0;
		memset(b,0,sizeof(b));
		for(int i = 1; i <= n; i++)
		{
			b[i].h = read();
			b[i].x = i;
		}
		p = 0;
		for(int i = 1; i <= n + 1; i++) init1(i);
		p = 0;
		for(int i = n; i >= 0; i--) init2(i);
		for(int i = 1; i <= n; i++)
		{
			ans = max(ans,1LL * (l[i] - r[i] - 1) * b[i].h);
		}
		printf("%lld\n",ans);
		n = read();
	}
    return 0;
}
```

---

## 作者：xy_xw_for_2024 (赞：0)

暨总分之后的另一篇题解。。。
~~其实我觉得吧，这道题把难度评高了一点，但我看到大家都这样评我也只好这样评了~~  
这道题就是很难想，也很难实现而已。。。。。。~~（为什么没有二维的？？）~~   

想深入了解的请[戳](https://blog.csdn.net/qq_43890190/article/details/84873267)  
大致想法就是以每一栋建筑作为最矮的建筑的最大面积  
是不是有点拗口？我们接着看，  
我们用一个栈，依次push进去每一栋建筑的高度，然后可以把TA大致分为3种情况：  
（当前建筑记作r，高度记作h，栈记作s）  
1、s.top().h>r.h;  
2、s.top().h=r.h;  
3、s.top().h<r.h;  
针对这三种情况，我们可以得到：  
1、重复取出s里面的元素，直到满足3；  
2、不做处理  
3、s.push(r)  
为什么呢？我在代码里给大家解释
```
#include<cstdio>
#include<stack>
#include<iostream>
using namespace std;
inline void read(int &x) {
    x=0;
    int f=1;
    char s=getchar();
    while(s<'0'||s>'9') {
        if(s=='-')
            f=-1;
        s=getchar();
    }
    while(s>='0'&&s<='9') {
        x=x*10+s-48;
        s=getchar();
    }
    x*=f;
}
inline void pr(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9)
        pr(x/10);
    putchar(x%10+48);
}//快读快输不解释
struct node {
	int id,h;
}r,o;
int dp[100005],n,ans;
inline int getans(int f[]) {
	int maxn=0;
	stack<node>s;//栈用来储存建筑
	f[n+1]=0;//因为要把每一栋建筑都计算一遍，才能得到答案，如果没有这一步把栈里的元素都pop出去，
             //就不能完整的计算出所有矩形的面积
	for(int i=1;i<n+2;i++) {
		r.h=f[i];
		r.id=i;
		if(s.empty()||r.h>s.top().h)//当TA是空的时候或者当前建筑的高度比栈顶的建筑高，说明
                                    //这座建筑的右边还有可以发展的空间，广告牌的面积还可以更大
			s.push(r);//直接push
		else if(r.h<s.top().h) {//如果TA的高比栈顶的还要矮，说明以栈顶为最矮的建筑左右两边都
                                //到底了
			while(!s.empty()&&r.h<s.top().h) {//就用一个while计算已经到底的建筑的面积
				o=s.top();
				s.pop();
				maxn=max(maxn,(i-o.id)*o.h);//更新最大值
				r.id=o.id;//这里更新之后就可以得出该建筑向左边的最长的距离
			}
			s.push(r);
		}
	}
	return maxn;
}
int main() {
	read(n);
	for(int i=1;i<=n;i++)
		read(dp[i]);//读入部分
	ans=max(ans,getans(dp));//计算答案
	pr(ans);
}
```
~~其实都是我从我的博客上copy的~~  
我的[博客](https://me.csdn.net/qq_43890190)  
求关注，~~求过~~

---

## 作者：_自动AC机_ (赞：0)

### 题目大意
- 这道题让求直方图中最大的矩形，刚开始想用DP，可是想了很久没想到状态转移方程，就选了个下面讲的思路来做。

### 思路

- 先遍历数组，每找到一个局部最大值，然后向前遍历所有的值，算出共同的矩形面积，每次对比并且保留最大值。

我可能是史无前例的在这道题上用了Vector（动态数组）。（所以就别说解法重复）

### 代码
```cpp
#include <bits/stdc++.h>   //万能库不解释
using namespace std;
int n,temp;
vector<int>vct;   //vector定义
int cal(){
    int res=0;
    for(int i=0;i<vct.size();++i){
        if(i+1<vct.size()&&vct[i]<=vct[i+1]) continue; //不符合要求时
        int minn=vct[i];
        for (int j=i;j>=0;--j) {
            minn=min(minn, vct[j]);
            int area=minn*(i-j+1);   //计算最大矩形大小
            res=max(res,area);   //res存的是答案
        }
    }
    return res;
}
int main(){
    while(cin>>n&&n){   //意思是当没读到文件结尾而且读入的数不为0
        for(int i=0;i<n;i++){
        	cin>>temp;
        	vct.push_back(temp);   //把输入进去的东西放入vector
        } 
        cout<<cal()<<endl;   //输出计算出的结果
    }
}
```

---

## 作者：Sakura_nameless (赞：0)


思路： 
1.我们可以先建立一个单调上升的栈 
2.从左到右枚举每一个矩形，如果下一个矩形的高比前一个矮，则不断出栈，直到满足单调上升。 
3.每出栈一个元素，则累计一次宽度，并用他的高度乘上累计的宽度，求出面积。 
4.枚举结束后，把剩余的元素全部弹出，同时做步骤3

```c
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>

#define maxx 100005


using namespace std;

long long a[maxx],n,t,s,z[maxx],sum,tot,m_s,code,w[maxx];

int main()
{
    while(scanf("%lld",&n)) 
    {
    if(n==0)break;
    for(int i=0;i<=maxx-1;i++) 
    {
        a[i]=0;
        z[i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);        
    }
    a[n+1]=0;
    for (int i=1;i<=n+1;i++)
    {
        if(z[sum]<=a[i]) 
        {
            sum++;
            z[sum]=a[i];
            w[sum]=1;
        }
        else 
        {
            while (z[sum]>a[i])
            {   
                code=z[sum];
                z[sum]=0;
                tot=w[sum]+tot;     
                m_s=max(code*tot,m_s);  
                w[sum]=0;   
                sum--;
            }
            sum++;
            z[sum]=a[i];
            w[sum]=1+tot;
            tot=0;
        }

    } 
    printf("%lld\n",m_s);
    m_s=0;
    }
}
```
转自自己的博客https://blog.csdn.net/SSLGZ_CJX/article/details/81710465

---

## 作者：Seanq (赞：0)

**SP1805 HISTOGRA - Largest Rectangle in a Histogram题解**  
一道单调栈的题~  
题目描述：  
T组数据，每组数据输入一个n,再输入n个正整数，（记得开long long，我就是这里被坑了），求极大子矩阵  
思路：  
单调栈存左边第一个小于自己与右边第一个小于自己的编号，再用H[i]*(r[i]-l[i]-1),再更新答案    
std:  
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n;
long long a[1000001];//数字
long long b[1000001];//左最小编号
long long c[1000001];//右最小编号
long long ans=0;//答案
int main()
{
	while(scanf("%d",&n)!=EOF&&n)//多组数据（坑）
	{
		stack<int> l;
		stack<int> r;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		ans=0;
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		a[n+1]=0;
		for(int i=1;i<=n;i++)//单调栈做左
		{
			while(l.size()&&a[l.top()]>=a[i]) l.pop();//出栈
			if(l.empty()) b[i]=0;//更新
			else b[i]=l.top();
			l.push(i);//入栈
		}
		for(int i=n;i>=1;i--)//右
		{
			while(r.size()&&a[r.top()]>=a[i]) r.pop();//出栈
			if(r.empty()) c[i]=n+1;//更新
			else c[i]=r.top();
			r.push(i);//入栈
		}
		for(int i=1;i<=n;i++)//找最大值
		{
			long long sum=a[i];
			sum*=(c[i]-b[i]-1);
			ans=max(ans,sum);
		} 
		printf("%lld\n",ans);//输出
	}
	return 0;//结束啦！！！
} 
```


---

