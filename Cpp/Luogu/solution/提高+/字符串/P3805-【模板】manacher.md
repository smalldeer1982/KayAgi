# 【模板】manacher

## 题目描述

给出一个只由小写英文字符 $\texttt a,\texttt b,\texttt c,\ldots\texttt y,\texttt z$ 组成的字符串 $S$ ,求 $S$ 中最长回文串的长度 。

字符串长度为 $n$。

## 说明/提示

$1\le n\le 1.1\times 10^7$。

## 样例 #1

### 输入

```
aaa```

### 输出

```
3```

# 题解

## 作者：谁是鸽王 (赞：1362)

## 题解 P3805 【【模板】manacher算法】

### **UPD20220319**:改进排版
### **UPD20190927**:重置代码，规范边界
### **UPD20190712**:删除了一些愤怒的话语，精炼了语言，添加了$LaTex$。


看到个别教程，我猜他们大都是自己 **背** 的模板。不知所云。
对于manacher的核心根本就没有说明，只是对于核心的代码进行强调。到头来必须自己领悟。

------------

**我们先看两个字符串：**

`ABCCBA`

`ABCDCBA`

显然这两字符串是回文的

然而两个串的对称中心的特性不同，第一个串，它的对称中心在两个C中间，然而第二个串，它的对称中心就是D。这样我们如果要记录回文串的对称中心，就显得复杂了。

为了解决这个问题，把两种情况统一起来，我们就在字母之间插入隔板，这样两个问题就统一了，因为所有的对称中心都会有个字符与之对应。像这样

`~|A|B|C|C|B|A|	`

(注意到我们这里还插入了一个“～”，原因在代码里说明，不了解这里没有任何关系)

 **manacher为什么有如此优秀的复杂度呢？让我用文字说明一下**

- 对于一个回文串，有且仅有一个对称中心。且叫它**回文对称中心**。
- 在一个回文串**内**，任选一段区间 _X_ ，一定存在关于"回文对称中心"对称的一个区间 _Y_ ，且把这个区间 _Y_ 叫做关于区间 _X_ 的对称区间。
- 区间和对称区间一定全等。(你都是对称的怎么可能不全等)
- 若一个区间的对称区间是回文串，这个区间必定是一个回文串。在大的回文串内，它们回文半径相等。
- 然而我们通过确定关系预先得到的回文半径，它的数值，必定**小于等于**这个位置真实的回文串半径。

因此，我们若记录以每个位置为中心的回文串半径，当我们通过另一个回文中心将这个原先的中心点对称过去时，就可以确定对称过去的那个点的回文半径了。

考虑"另一个回文中心"如何确定，就是那个极大回文串的回文中心，也就是边界顶着右边我们已知的最远位置的，最长的回文串。

然而，考虑到，我们只能确认我们已知的回文串内的对称关系和回文半径等量关系，关于这个极大回文串右侧的世界，我们一无所知。

记录这些数据到p数组。同时记录一个mid，一个r，分别代表 **已经确定的右侧最靠右的回文串的对称中心和右边界**。

那么，当我们扫描到一个新的字符时，怎么先确定它的部分回文半径呢？

若当前扫描到的位置为i，若mid<=i<=r，则我们可以找到它的一个对称点。这个点的位置是多少？是**$mid×2-i$**。我们现在对其推导一下。

---



设：这个新点位置为$i$，它关于$mid$对称的点为$j$，将整个字符串看做以下标0位置为原点的数轴，我们由中点公式可得：

$(i+j)/2=mid$
方程两边同时乘以二, 得：

$i + j=2*mid $
移项得：
$ j=2*mid-i$

如果你真的连中点公式都不知道的话...[传送门](https://baike.baidu.com/item/%E4%B8%AD%E7%82%B9%E5%85%AC%E5%BC%8F/5978287?fr=aladdin)

就是这样很简单的推导过程，个别题解直接摆出结论 ，不给出推导，甚至要求学习者自己"找规律" 。我真是不敢苟同。不要说很简单很显然，看manacher题解的人难道全都是高手？

希望大家以后发表题解要严谨一点，至少自己没有真正理解就不要发题解，让人觉得manacher是难以学习的算法。至少当我在学习的时候，是一头雾水。

---



所以，拓展一个新点时，我们不必从这个点左右两边第一个位置开始向两边拓展，可以预先确定一部分回文串。就是因为这个，manacher的复杂度是线性的。(记得看代码注释)

-  若扩展一个新的关于该字符的回文半径，可以先确定一部分P[i]。

-  且我们知道，我们能确定的范围，其右侧不得大于r，即：p[i]+i-1<=r 移项得：p[i] <= r-i+1

故此，要取一个min 这里给出代码:
	
```cpp
	P[i]=min(P[mid*2-i],r-i+1) 
```

最终答案是

```cpp
	P(max)-1
```

> 假设原串某个最长回文串长度为`L`，在新串里的长度将会是`2L+1`，回文半径将会是`L+1`，而`L+1=P(max)`那么答案就是`P(max)-1`了

讲到这里，应该十分清楚了。

```cpp
//@winlere
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=11000002;
char data[maxn<<1];
int p[maxn<<1],cnt,ans;
inline void qr(){
      char c=getchar();
      data[0]='~',data[cnt=1]='|';
      while(c<'a'||c>'z') c=getchar();
      while(c>='a'&&c<='z') data[++cnt]=c,data[++cnt]='|',c=getchar();
}
int main(){
      qr();
      for(int t=1,r=0,mid=0;t<=cnt;++t){
	    if(t<=r) p[t]=min(p[(mid<<1)-t],r-t+1);
	    while(data[t-p[t]]==data[t+p[t]]) ++p[t];
	    //暴力拓展左右两侧,当t-p[t]==0时，由于data[0]是'~'，自动停止。故不会下标溢出。
	    //假若我这里成功暴力扩展了，就意味着到时候r会单调递增，所以manacher是线性的。
	    if(p[t]+t>r) r=p[t]+t-1,mid=t;
	    //更新mid和r,保持r是最右的才能保证我们提前确定的部分回文半径尽量多。
	    if(p[t]>ans) ans=p[t];
      }
      printf("%d\n",ans-1);
      return 0;
}


```

祝大家学习愉快。

---


2022:博主现在在上海某~~一流~~大学CS专业就读, 每次打开洛谷总能看见这篇题解或赞增加; 或来了一两句不友善的评论。其实我都能理解，这篇题解最初发布于2018年，四年之久，我相信OI题解的环境发生了好的变化，再也看不到四年前互联网上屎一样的教程了。但是我决定将当年说的那些话保留下来，一个是保存我青春的回忆，另一个是希望让大家在有时枯燥的OI生活中找到一个对线的对象。



---

## 作者：codesonic (赞：514)

考虑判断回文的方法

1.暴力

最朴素的暴力

举出该字符串的所有子串，判断其是否回文，时间复杂度是$O(n^3)$的

2.改进第一种，仍然是暴力

所有的回文串都是对称的。长度为奇数回文串以最中间字符的位置为对称轴左右对称，而长度为偶数的回文串的对称轴在中间两个字符之间的空隙。可以遍历这些对称轴，在每个对称轴上同时向左和向右扩展，直到左右两边的字符不同或者到达边界。

时间复杂度$O(n^2)$

3.manacher算法

首先我们可以先查看第二种方法有哪些缺点

1）回文串长度的奇偶性造成了对称轴的位置可能在某字符上，也可能在两个字符之间的空隙处，第二种方法要对两种情况分别处理

那么manacher对此的优化是这样的

在每两个字符中间插入另一个字符，如'#'。

也就是说，原来的字符串是这样的

 ![](https://cdn.luogu.com.cn/upload/pic/7882.png) 

现在的字符串是这样的（为了不越界以及方便，a[0]设置为‘#’）

 ![](https://cdn.luogu.com.cn/upload/pic/7883.png) 

那么这个缺点解决了

2）会出现很多子串被重复多次访问，时间效率大幅降低。

这里比较难理解

用一个辅助数组hw表示每个点能够扩展出的回文长度

我们从s[1]遍历到s[strlen(s)]，循环变量为i

我们先设置一个辅助变量maxright，表示已经触及到的最右边的字符

另外还要设置一个辅助变量mid，表示包含maxright的回文串的对称轴所在的位置

也就是这样：

 ![](https://cdn.luogu.com.cn/upload/pic/7884.png) 

当i在maxright左边且在mid右边时：

设i关于mid的对称点为j，显然hw[i]一定不会小于hw[j]。（对称）

我们没必要保存j，j可以通过计算得出，为：

$(mid<<1)-i$,可以尝试自己算

那么我们就设置hw[i]=hw[j]然后继续尝试扩展，这样就可以较快地求出hw[i]，然后更新maxright和mid

当i在maxright右边时，我们无法得知关于hw[i]的信息，只好从1开始遍历，然后更新maxright和mid

这样就是这个算法的全部了，如果认真读了是不会太难的，实在不行可以百度。

而该算法的时间复杂度和空间复杂度都是线性的

小结：manacher就是利用回文对称的性质，来简化求以一个字符为对称轴的最大的回文长度。别看这简化不大，当数据很大时，这样求的速度会快很多。

下面是代码：

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#define maxn 51000100
using namespace std;
int n,hw[maxn],ans;
char a[maxn],s[maxn<<1];
void manacher()
{
    int maxright=0,mid;
    for(int i=1;i<n;i++)
    {
        if(i<maxright)
            hw[i]=min(hw[(mid<<1)-i],hw[mid]+mid-i);
        else
            hw[i]=1;
        for(;s[i+hw[i]]==s[i-hw[i]];++hw[i]);
        if(hw[i]+i>maxright)
        {
            maxright=hw[i]+i;
            mid=i;
        }
    }
}
void change()
{
    s[0]=s[1]='#';
    for(int i=0;i<n;i++)
    {
        s[i*2+2]=a[i];
        s[i*2+3]='#';
    }
    n=n*2+2;
    s[n]=0;
}
int main()
{
    scanf("%s",a);
    n=strlen(a);
    change();
    manacher();
    ans=1;
    for(int i=0;i<n;i++)
        ans=max(ans,hw[i]);
    printf("%d",ans-1);
    return 0; 
}
```

如果哪里有问题可以在评论提出，谢谢orz

---

## 作者：Nemlit (赞：203)

重拾$manacher$，真切感受到了他的妙处

首先，考虑到回文串分奇数和偶数两种情况，需要分类讨论，所以我们可以考虑在所有字符之间插入一个没有用过的符号'#'

然后边界问题不好处理，所以可以在字符串的开头加上一些奇怪的符号'~'

接下来就是$manacher$的正文部分了

我们定义$p_i$表示以i为对称中心，能拓展的回文数量

发现我们可以$O(N^2)$的暴力做法：一直向外拓展，直到不匹配

在定义$mr$表示我们经过的，最靠右边的点，在记录一个$mid$表示这个最靠右的点是由哪一个对称轴转移过来的

然后发现，对于每一个$i$，我们没有必要都去拓展，我们分几种情况讨论：

## $Case1: mid<i<mr$ 

由于$[mid - mr, mid + mr]$是回文的，设$j$为$i$以$mid$为中心的对称点，根据对称性那么我们有：$[j-p_j, j+p_j]=[i-p_i, i+p_i]$ 

但是当$i+p_i>mr$时，我们无法保证上述情况相等（设$mr$以$ mid$为中心的对称点为$x$，因为$j-p_j<x$，所以无法保证相等，详见下图）![](https://cdn.luogu.com.cn/upload/image_hosting/hmjc4gc3.png) 所以对于$Case1$，我们可以直接让$p[i]=min(p[j], mr - i + 1)$，然后暴力拓展即可 

## $Case2:i<mr$ 

这个时候我们不能求出i的对称点，直接暴力拓展即可


由于$mr$和$ mid$，不断右移，所以复杂度线性 

## $Code:$

```
#include<bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for(int i = s; i <= t; ++ i)
#define maxn 22000005
int n, m, cnt, p[maxn], mid, mr, Ans;
char c[maxn], s[maxn];
void build() {
	scanf("%s", c + 1), n = strlen(c + 1), s[++ cnt] = '~', s[++ cnt] = '#';
	rep(i, 1, n) s[++ cnt] = c[i], s[++ cnt] = '#';
	s[++ cnt] = '!';
}
void solve() {
	rep(i, 2, cnt - 1) {
		if(i <= mr) p[i] = min(p[mid * 2 - i], mr - i + 1);
		else p[i] = 1;
		while(s[i - p[i]] == s[i + p[i]]) ++ p[i];
		if(i + p[i] > mr) mr = i + p[i] - 1, mid = i;
		Ans = max(Ans, p[i]);
	}
	printf("%d", Ans - 1);
}
int main() { return build(), solve(), 0; }
```

---

## 作者：FREEH (赞：99)

# Manacher总结
### 【用途】
- 求一个字符串中有多少个回文**子串**。

### 【算法过程】

#### 1. 预处理

- 由于回文串分为偶回文串和奇回文串，奇偶判断起来比较麻烦，因此我们可以在字符串的首、尾以及各个字符之间添加一些“神奇”字符（不妨使用$），但是要注意字符串的首添加的字符**必须**区别于各个字符之间的字符。
- 不难发现，修改后的字符串都变成了奇字符串。
- **以下Manacher算法的所有处理都是基于修改后的字符串**。

#### 2. Manacher算法的主体
- 定义数组p[i]表示以字符i为回文中心的最长回文串的半径，不难发现，p[i]-1就是字符串中最长回文串的长度（因为要去除$）。
- 定义mx和mid，表示目前找到的回文串的右端的最右是mx，中心是mid。
- ![1](https://cdn.luogu.com.cn/upload/pic/25258.png)
- 如上图所示，id是j~mx的回文中心，因此以i的对称点为回文中心的字符串=以i为回文中心的字符串，因此p[i]可以是p[j]。但是由于超过mx的部分（即右红边部分）**不能保证**必定等于左红边的部分，所以p[i]不能超过i~mx的长度。因此
```cpp
p[i]=min(mx-i,p[mid*2-i])
```
- 接下来，我们就要**暴力**统计右侧 “不能保证” 的部分，即最右黑边的右侧是否满足回文性质（具体看代码）。
- 最后更新一下mx即可。

### 【时空复杂度】
- Manacher算法的时间复杂度为$O(n)$（这里就不作证明了），因此是解决回文问题的利器。

### 【参考程序】
```cpp
#include<cstdio>
#include<cstring>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
char s[32000005],st[32000005];
int p[32000005];
int change()
{
    int len=strlen(st);
    int j=2;
    s[0]='^';
    s[1]='$';
    for (int i=0;i<len;i++)
    {
        s[j++]=st[i];
        s[j++]='$';
    }
    s[j]='&';
    return j;
}
int Manacher()
{
    int len=change(),mid=1,mx=1,ans=-1;
    for (int i=1;i<len;i++)
    {
        if (i<mx)
            p[i]=min(mx-i,p[mid*2-i]);
        else
            p[i]=1;
        while (s[i-p[i]]==s[i+p[i]])
            p[i]++;
        if (mx<i+p[i])
        {
            mid=i;
            mx=i+p[i];
        }
        ans=max(ans,p[i]-1);
    }
    return ans;
}
int main()
{
    scanf("%s",st);
    printf("%d",Manacher());
}
```

---

## 作者：zcysky (赞：50)

这题是manacher的裸题，当然你用邻接表实现PAM（回文自动机）也是可以的。

因为PAM的复杂度也是正确的，所以造数据的时候没有卡PAM

（但是你裸的数组PAM是过不去的啦！）

manacher算法，就是在字符之间插入特殊字符避免奇偶分类讨论

然后利用之前的已有的回文信息计算回文半径。

```cpp
#include<bits/stdc++.h>
#define N 31000010
using namespace std;
int n,p[N],ans;
char s[N],str[N];
void manachar(){
    int mx=0,id;
    for(int i=n;str[i]!=0;i++)str[i]=0;
    for(int i=1;i<n;i++){
        if(mx>i)p[i]=min(p[2*id-i],p[id]+id-i);
        else p[i]=1;
        for (;str[i+p[i]]==str[i-p[i]];++p[i]);
        if (p[i]+i>mx){mx=p[i]+i;id=i;}
    }
}
void init(){
    str[0]='#';str[1]='#';
    for(int i=0;i<n;i++)str[(i<<1)+2]=s[i],str[(i<<1)+3]='#';
    n=(n<<1)+2;str[n]=0;
}
int main(){
    scanf("%s",s);
    n=strlen(s);init();manachar();
    ans=0;
    for(int i=0;i<n;i++)ans=max(ans,p[i]);
    printf("%d\n",ans-1);
    
}
```

---

## 作者：skydogli (赞：44)

大家好，这是一篇乱搞的题解。

因为CSP考前心态很崩，所以不想复习一堆边界的马拉车，于是开始思考如何乱搞实现相似的功能，最后决定使用字符串算法的万金油:哈希！

做法十分暴力，直接正着求一遍哈希值再反着求哈希值，然后枚举对称轴再二分长度即可，复杂度$O(nlogn)$

满怀信心交上去——直接全T。初始代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ULL unsigned long long
#define MN 11000005
const ULL w=131;
ULL Hash1[MN],Hash2[MN],pw[MN];
char ch[MN];
ULL gethash1(int l,int r){
	return Hash1[r]-Hash1[l-1]*pw[r-l+1];
}
ULL gethash2(int l,int r){
	return Hash2[l]-Hash2[r+1]*pw[r-l+1];
}
int main(){
	scanf("%s",ch+1);
	int n=strlen(ch+1);
	pw[0]=1;
	for(int i=1;i<=n;++i){
		pw[i]=pw[i-1]*w;
		Hash1[i]=Hash1[i-1]*w+(ULL)ch[i];
//		cerr<<i<<": pw:"<<pw[i]<<" Hash1:"<<Hash1[i]<<endl;
	}
	int ans=0;
	for(int i=n;i;--i){
		Hash2[i]=Hash2[i+1]*w+ch[i];
		int r=min(n-i+1,i-1)+1,l=0;
		while(l+1<r){
			int mid=(l+r)>>1;
//			cerr<<"hash1 "<<i-mid<<" "<<i-1<<" "<<gethash1(i-mid,i-1)<<endl;
//			cerr<<"hash2 "<<i<<" "<<i+mid-1<<" "<<gethash2(i,i+mid-1)<<endl;
			if(gethash1(i-mid,i-1)==gethash2(i,i+mid-1)) l=mid;
				else r=mid;
		}
//		cerr<<i<<": "<<l<<endl;
		ans=max(ans,l*2);
		r=min(n-i,i-1)+1,l=0;
		while(l+1<r){
			int mid=(l+r)>>1;
			if(gethash1(i-mid,i-1)==gethash2(i+1,i+mid)) l=mid;
				else r=mid;
		}
		ans=max(ans,l*2+1);
	}
	printf("%d",ans);
}
```
万念俱灰，打算下个数据检验一下正确性，发现答案只有11？？？那窝加点剪枝是不是过了啊，于是加一个，如果这个中间点拓展到当前答案的长度都不合法就不二分了，然后过了。。。



```cpp
#include<bits/stdc++.h>
using namespace std;
#define ULL unsigned long long//选择自然溢出减小常数
#define MN 11000005
const ULL w=131;
ULL Hash1[MN],Hash2[MN],pw[MN];
char ch[MN];
ULL gethash1(int l,int r){
	return Hash1[r]-Hash1[l-1]*pw[r-l+1];
}
ULL gethash2(int l,int r){
	return Hash2[l]-Hash2[r+1]*pw[r-l+1];
}
int main(){
	scanf("%s",ch+1);
	int n=strlen(ch+1);
	pw[0]=1;
	for(int i=1;i<=n;++i){
		pw[i]=pw[i-1]*w;
		Hash1[i]=Hash1[i-1]*w+(ULL)ch[i];
	}
	int ans=0;
	for(int i=n;i;--i){
		Hash2[i]=Hash2[i+1]*w+ch[i];//正反各搞一下哈希值
		int r=min(n-i+1,i-1)+1,l=ans/2-1;
		if(l<=0||gethash1(i-l,i-1)==gethash2(i,i+l-1)){
			while(l+1<r){
				int mid=(l+r)>>1;//二分回文的长度
				if(gethash1(i-mid,i-1)==gethash2(i,i+mid-1)) l=mid;
					else r=mid;
			}
			ans=max(ans,l*2);
		}
		r=min(n-i,i-1)+1,l=ans/2-1;
		if(l<=0||gethash1(i-l,i-1)==gethash2(i+1,i+l)){//判断哈希值是否相同
			while(l+1<r){
				int mid=(l+r)>>1;
				if(gethash1(i-mid,i-1)==gethash2(i+1,i+mid)) l=mid;
					else r=mid;
			}
			ans=max(ans,l*2+1);//统计答案
		}
	}
	printf("%d",ans);
}
```

等等，仔细研究这个贪心策略，如果答案不变，则是$O(n)$级别的判断，且答案的拓展也只是$O(n)$级别的，那么把二分删掉，答案每增大一次的复杂度变为$O(1)$,其复杂度就是$O(n)$。虽然码量稍大，但毕竟比较无脑，在忘了马拉车时是个不错的补救方案。

下面给出最后的$O(n)$代码（因为这题神奇的数据，所以有时比上面的还慢。。。）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ULL unsigned long long
#define MN 11000005
const ULL w=131;
ULL Hash1[MN],Hash2[MN],pw[MN];
int n;
char ch[MN];
ULL gethash1(int l,int r){
	return Hash1[r]-Hash1[l-1]*pw[r-l+1];
}
ULL gethash2(int l,int r){
	return Hash2[l]-Hash2[r+1]*pw[r-l+1];
}
inline void chkmax(int &a,int b){
	if(a<b) a=b;
}
int main(){
//	freopen("3805.in","r",stdin);
//	freopen("3805.out","w",stdout);
	scanf("%s",ch+1);
	n=strlen(ch+1);
	pw[0]=1;
	for(int i=1;i<=n;++i){
		pw[i]=pw[i-1]*w;
		Hash1[i]=Hash1[i-1]*w+(ULL)ch[i];
	}
	int ans=0;
	for(int i=n;i;--i){
		Hash2[i]=Hash2[i+1]*w+ch[i];
		int l=ans/2+1;
		while(i-l>0&&i+l-1<=n&&(l<0||gethash1(i-l,i-1)==gethash2(i,i+l-1))){
			chkmax(ans,l<<1);
			l++;
		}
		l=ans/2;
		while(i-l>0&&i+l<=n&&(l<0||gethash1(i-l,i)==gethash2(i,i+l))){
			chkmax(ans,l<<1|1);//暴力扩大答案，没想到吧。。。
			l++;
		}	
	}
	printf("%d",ans);
}
```

---

## 作者：Lstdo (赞：43)

[推销博客](https://blog.csdn.net/luositing/article/details/93363447)


##  写在前面
$manacher$比想象中好理解得多

至少它给了我学习字符串的信心

##  能干啥

$manacher$，中文马拉车（您别说，这名字还挺形象），主要用于计算字符串每一个位置为对称中心的回文串长度（等价于个数） 

包括偶回文，即长度为偶数的回文串

##  算法流程
考虑下面的问题：给一个字符串，求最长回文子串

**我会暴力！**

枚举判断$O(n^3)$

**我会优化！**

考虑到以$c$为中心，$acb$不是回文串，左右怎么接都不是回文串

所以可以枚举中间点（偶回文判断一下即可），然后向两边拓展

复杂度$O(n^2)$

**我会玄学！**

$O(n^2)$还不够 ~~不符合字符串算法均为线性复杂度公理~~

在此基础上继续优化

我们记录$maxr$为目前找到的回文串右端点的最右的位置 $pos$为这个回文串的对称中心

开一个数组$p_i$表示回文半径（和其他文章不同，本文回文半径指一个端点到中心的距离，即直接相减）

回文串最本质的特征是什么？左右关于中心对称。

如果一个回文串对称中心的一侧有另一个回文子串，那么对称过去也有一个相同长度的回文子串

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190622213153968.jpg)
黄色部分完全一致，**这就是manacher的核心**


（先不考虑偶回文）



① $i<maxr$(取不取等于无所谓)

设$j,i$关于$pos$对称 即$j=pos*2-i$

根据上面的推导，令$p_i=p_j$即可

当然如果$j$为中心的最长回文左端点越界了
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190622213455534.jpg)
那就不能保证上面的性质（实际上可以保证不成立），所以要和$j-maxl$(即$maxr-i$)取$min$。

$j$越界时还需要让$i$继续拓展。当然为了~~刷短代码~~减少讨论，都拓展一下好了 

②$i \geq maxr$

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190622213904305.jpg)
啥都不能保证，直接暴力扩展

综上：

 

 1. 如果$i<maxr$,按上述条件更新$p_i$
 2. 暴力拓展
 3. 更新$maxr$和$pos$

然后……对，没了，就三行。

这就是$manacher$的全过程，复杂度$O(n)$，后面有证明

##  实现

上面没有讨论偶回文，主要是转化过程比较难看，容易使人丧失信心。

其实也不难。只需要在字符两两之间加一个字符,如‘#'；然后首尾也加上‘#’，再在开头加一个标识符防止越界。注意要和之前的不同，如‘@’

这样偶回文可以看做中心是‘#’的回文

普及T1模拟水平

这样处理后，所有回文串左右端点都是‘#’，然后就可以跑了

##  证明
什么？不是只改了一个地方吗？怎么变$O(n)$了？

回顾整个流程，真正暴力拓展的时候要么$j$左端点越界，要么$i$越界($j$左端点没越界时，根据反证法，$i$实际上无法拓展)

$j$左端点越界时，$i$右端点出生点就在$maxr$，再拓展就超出去了

也就是说，每次暴力拓展，都意味着$maxr$更新，而$maxr$只会往右跑

换一个角度，实际上暴力拓展是把$maxr$推到最右边，次数是$O(n)$的

所以总复杂度是$O(n)$的

##  代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 1000005
using namespace std;
char s[MAXN],ss[MAXN];
int pos,maxr;
int p[MAXN];
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for (int i=1;i<=n;i++) ss[i<<1]=s[i],ss[(i<<1)|1]='#';
	n=(n<<1)|1,ss[0]='@',ss[1]='#';
	strcpy(s,ss);
	for (int i=1;i<=n;i++)
	{
		if (i<maxr)	p[i]=min(p[(pos<<1)-i],maxr-i);
		while (s[i-p[i]-1]==s[i+p[i]+1]) ++p[i];
		if (i+p[i]>maxr) maxr=i+p[i],pos=i;
	}
	return 0;
}
```
由于所有位置为中心的最长回文串左右端点都是‘#’

回文串长度$len_i= \frac {2p_i+1-1}{2} = p_i$

然后用来搞事情就可以了

本题中就是所有$p_i$的最大值


---

## 作者：bztMinamoto (赞：18)

打广告->[这里](https://www.cnblogs.com/bztMinamoto/p/9628247.html)

# 前言

Manacher（也叫马拉车）是一种用于在线性时间内找出字符串中最长回文子串的算法

# 算法

一般的查找回文串的算法是枚举中心，然后往两侧拓展，看最多拓展出多远。最坏情况下$O(n^2)$

然而Manacher能够充分利用回文的性质

首先，回文分为奇回文（比如$aba$）和偶回文（比如$abba$），如果分开来讨论会很麻烦。

于是我们在原串的首尾以及每两个字符之间各插入一个原串中没有出现过的字符。比如$abbbac$，变成$\%a\%b\%b\%b\%a\%c\%$

那么这样的话，上面的$aba$变成$\%a\%b\%a\%$，$abba$变成$\%a\%b\%b\%a\%$，都变成了奇回文

我们定义$p[i]$为以$i$为中心的回文串的最长半径，比如串$\%a\%b\%a\%$，其中$b$为第四个字符，则$p[4]=4$（因为以他为中心的最长回文串是$\%a\%b\%a\%$，而这个回文串的半径为4）

那么我们原串中以这个位置为中心的最长回文串长度就是$p[i]-1$（一个要去掉$\%$，然后半径的话要防止中心被多算一次）

那么现在的问题就是怎么快速求出$p[i]$了

我们假设$pos$是一个已经记录的值，$R$为以$pos$为中心的回文串的最长右边界，然后现在要求$p[i]$

$j$是$i$关于$pos$的对称点，也就是说$j=2*pos-i$

那么这个时候分为两种情况

1.$j$的最长回文没有跳出$L$

![](https://i.loli.net/2018/09/11/5b97757086976.png)

因为$[L...R]$是一个回文串，所以$i$的回文和$j$的回文相同，即$p[i]=p[j]$

2.$j$的最长回文越过了$L$

![](https://i.loli.net/2018/09/11/5b977570bcaa6.png)

如果在这种情况下，$j$的最长回文就不一定是$i$的最长回文了。然后黄色那块肯定还是满足条件的

所以综上，$p[i]=min(p[2*pos-1],R-i)$

然后剩下的那部分怎么办？暴力直接算

我没口胡，真的

# 时间复杂度

时间复杂度是$O(n)$的

为啥嘞？

如果$p[i]$能直接求肯定是$O(1)$的

然后如果需要上暴力那么每一次都能让$R$严格右移

因为串长只有$O(n)$，所以暴力次数最多$O(n)$

上板子吧，板子抄的zzk大爷的
```
//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
const int N=1.1e7+5;
int p[2*N];char s[N],now[N*2];
inline bool is(char c){return c!='\n'&&c!=EOF;}
inline void read(char *s){
    int len=0;char ch;while(is(ch=getc())) s[++len]=ch;s[++len]=0;
}
int manacher(char *s){
    int len=strlen(s+1);
    for(int i=1;i<=len;++i) now[2*i-1]='%',now[2*i]=s[i];
    now[len=len*2+1]='%';
    int pos=0,R=0;
    for(int i=1;i<=len;++i){
        if(i<R) p[i]=min(p[2*pos-i],R-i);else p[i]=1;
        while(i-p[i]>=1&&i+p[i]<=len&&now[i-p[i]]==now[i+p[i]]) ++p[i];
        if(i+p[i]>R) pos=i,R=i+p[i];
    }
    int mx=0;
    for(int i=1;i<=len;++i) cmax(mx,p[i]-1);
    return mx;
}
int main(){
//	freopen("testdata.in","r",stdin);
    read(s);
    printf("%d\n",manacher(s));
    return 0;
}
```
[P4555 [国家集训队]最长双回文串](https://www.luogu.org/problemnew/show/P4555)

首先双回文串肯定是拼接而成的

那么我们就记录一下每一个字符分别作为回文串的最左端（最右端）时，对应的中心最左（最右）在哪里

然后就可以通过拼接得到双回文串了
```
//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
const int N=1e5+5;
int p[2*N];char s[N],now[N*2];int L[N<<1],R[N<<1],len,ans;
void manacher(char *s){
	len=strlen(s+1);
	for(int i=1;i<=len;++i) now[2*i-1]='%',now[2*i]=s[i];
	now[len=len*2+1]='%';
	int pos=0,R=0;
	for(int i=1;i<=len;++i){
		if(i<R) p[i]=min(p[2*pos-i],R-i);else p[i]=1;
		while(i-p[i]>=1&&i+p[i]<=len&&now[i-p[i]]==now[i+p[i]]) ++p[i];
		if(i+p[i]>R) pos=i,R=i+p[i];
	}
}
int main(){
//	freopen("testdata.in","r",stdin);
	scanf("%s",s+1);
	manacher(s);
	for(int i=1,pos=1;i<=len;++i)
	for(;pos<=i+p[i]-1;++pos) L[pos]=i;
	for(int i=len,pos=len;i;--i)
	for(;pos>=i-p[i]+1;--pos) R[pos]=i;
	for(int i=1;i<=len;++i) cmax(ans,R[i]-L[i]);
	printf("%d\n",ans);
	return 0;
}
```
[P1659 [国家集训队]拉拉队排练](https://www.luogu.org/problemnew/show/P1659)

因为题目要求的是奇数回文，所以连$\%$都没必要加了，直接上manacher就好了

然后因为一个半径为$n$的回文串存在，那么$n-1$,$n-2$的回文串也必定存在

所以要开一个桶存一下前缀和

然后还要用一下快速幂

然后就差不多了
```
//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N=1e6+5,mod=19930726;
char s[N];int p[N],c[N],n;ll ans=1,sum=0,k;
inline ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1) (res*=a)%=mod;
		(a*=a)%=mod,b>>=1;
	}
	return res;
}
int main(){
//	freopen("testdata.in","r",stdin);
	scanf("%d%lld",&n,&k);
	scanf("%s",s+1);
	for(int i=1,pos=0,R=0;i<=n;++i){
		p[i]=i<R?min(p[2*pos-i],R-i):1;
		while(i-p[i]>=1&&i+p[i]<=n&&s[i-p[i]]==s[i+p[i]]) ++p[i];
		if(i+p[i]-1>R) pos=i,R=i+p[i]-1;
		++c[2*p[i]-1];
	}
	(n&1)?0:(--n);
	for(int i=n;i;i-=2){
		sum+=c[i];
		if(sum>k){(ans*=qpow(i,k))%=mod;break;}
		(ans*=qpow(i,sum))%=mod,k-=sum;
	}
	printf("%lld\n",sum<k?-1:ans);
	return 0;
}
```

---

## 作者：Lskkkno1 (赞：14)

## manacher 算法小结

### 前言

 感觉 $manacher$ 和 $kmp$ 算法的主要想法差不多

 都是用之前匹配过的信息去做后面的事情, 这样才不会浪费之前的操作

 一个回文串可以进行快速匹配当然会有一些**优秀的性质**

### 从性质入手

 关于 **中点*mid*** 回文 *(性质 1)* ~~废话~~

 那么 **在一个回文串中**, 两个关于中点对称的点, **在这个回文串内** 回文长度就是相等的 *(要点 1)*

 从左往右遍历字符串, 我们想办法找到当前位置可以匹配的, 已经处理完的 **对称位置** *(步骤 1)*

 我们此时根据之前的处理完的位置 得到了当前位置的一个较长的 **回文半径**, 但可能这不是这个点的 **最长回文半径**, 仍然需要继续往后扩大 **回文半径** *(步骤 2)*

 那么问题来了, 我们应该找哪一个点作为*(要点 1)*中的 "这个回文串" 呢?

 我们选取 **回文串右端点** 最往右的的回文串作为 "这个回文串", 并记录 **中点*mid*** 这样就可以最大利用之前匹配的信息 *(步骤 3)*

 最右的端点最多往右移动 *n* 次, 所以算法复杂度是 $O(n)$ 的 *(性质 2)*

 特别的, 长度为偶数的回文串没有 **整数的回文中点**, 我们需要倍长原串

### 具体要点操作

 #### 1. 利用之前信息得到当前位置的回文半径

 $r[cur] = min(r[2*cur-mid],\ right_{max} - i)$
 
 不能超过当前处理完的右端点(*cur* 其实相当于 *i* 啦)

 #### 2. 往右继续扩大回文半径

 $if(s[cur-r[cur]-1]==s[cur+r[cur]+1])\ ++r[cur]$ 
 
 我这个是闭区间的回文, 所以要 +1 / -1

 #### 3.更新答案

 发现倍长后的右端点 **闭区间的回文半径** 就是答案 (感性理解)

### Code

 看 *dalao* 们写的都是开区间的回文, 那我就贴一个闭区间的回文吧...

 ~~代码很丑~~

 [$\color {DeepSkyBlue} {Code}$](https://www.luogu.org/paste/sj83wyld)

---

## 作者：iostream (赞：13)

首先这个题是manacher的模板题，所以我们显然可以用回文自动机来做它，然而直接写一个回文自动机，其由于转移边使用二维数组存储，空间复杂度是 $O(|S|\times 26)$。

注意到这些边的总数是 $O(n)$ 的，使用哈希表存储即可。

```cpp
#include<cstdio>

const int maxn = 11000005;

int ans;
char s[maxn];

struct PAM {
	int te, head[1 << 20], nxt[maxn], fr[maxn], pt[maxn];
	
	void add(int a, int b, int c)
	{
		int key = a * 27 + b;
		nxt[++te] = head[key & 1048575];
		head[key & 1048575] = te;
		fr[te] = key;
		pt[te] = c;
	}
	
	int find(int a, int b)
	{
		int key = a * 27 + b;
		for(int i = head[key & 1048575]; i; i = nxt[i])
			if(fr[i] == key)
				return pt[i];
		return 0;
	}
	
	int tot, lst, tail, len[maxn], fail[maxn];
	char str[maxn];
	
//	int ch[maxn][26];
	
	void init()
	{
		fail[1] = 0;
		fail[2] = 1;
		str[0] = -1;
		len[1] = -1;
		len[2] = 0;
		tot = 2;
		lst = 1;
	}
	
	int jump(int x)
	{
		for(; str[tail] ^ str[tail - len[x] - 1]; x = fail[x]);
		return x;
	}
	
	void Extend(char ct)
	{
		str[++tail] = ct;
		int p = jump(lst);
		int ch = find(p, ct - 'a');
		if(!ch)
		{
			int q = ++tot;
			len[q] = len[p] + 2;
			if(len[q] > ans) ans = len[q];
			fail[q] = (p > 1 ? find(jump(fail[p]), ct - 'a') : 2);
			add(p, ct - 'a', ch = q);
		}
		lst = ch;
	}
}T;

int main()
{
	T.init();
	scanf("%s", s);
	for(int i = 0; s[i]; i ++) T.Extend(s[i]);
	printf("%d", ans);
	return 0;
}


---

## 作者：zzr8178541919 (赞：6)


参见了第一位大佬写的题解，使我从一个从未听闻Manacher算法的蒟蒻，到现在对这个神奇的算法有了一定的了解。

以下就是我对Manacher算法的一些个人的感受，补充以及总结。

#### 首先对于一个回文串有两种情况
### 1.abba
### 2.ababa
第一种情况的对称轴在中间，第二种情况的对称轴在a字符上。

我想排除这样的干扰，我就要对原图做点手脚
### 就像这样：
### ~|a|b|b|a|。
从而把两种情况并成了一种情况。这个步骤可以在读入是处理出来

##  _ _ _ _ _ _ _ __ _ _  __1.definition_ _ _ _ _ _ _ _ _ _ 
#### Manacher算法主要处理的是回文字符串的长度问题。它可以在线性的复杂度范围内处理出一个字符串中最长的回文子串，真是一个妙不可言的算法。见识了Manacher算法后，我感受到了信息学的博大精深以及其无穷的乐趣！\(^o^)/~

##  _ _ _ _ _ _ _ _ _ _ _ _2.thought_ _ _ _ _ _ _ _ _ _ _ _ 
#### Manacher算法主要就是几个步骤，它最主要的一步就是枚举每一个点的回文串时，它可以先“吸取先前的经验”，获得一个初始长度，这就使得Manacher算法不用在枚举这方面花费大量的时间，从而达到很快的效果。

##  _ _ _ _ _ _ _ _ _ _ _3.explanation_ _ _ _ _ _ _ _ _ _ 
#### Manacher算法主要使针对回文串的一些性质而得出的高效的算法。
####  对于一个回文串，肯定是有一个对称轴的，那么这个对称轴就具有了很多的性质。
#### 1.这个回文串关于中间的对称轴是左右对称的。
#### 2.我们令对称轴为x，假设在长度范围内，那么(x-len)的字符串区间和(x+len)的字符串区间也是对称的。也就是说在一个回文串内，任选一段区间 X ，一定存在关于"回文对称中心"对称的一个区。
#### 3.若一个区间的对称区间是回文串，这个区间必定是一个回文串。在大的回文串内，它们回文半径相等。（引自楼顶大佬）

我们求最长的回文串是通过枚举的方式得到的。从左往右扫一遍，从而得到最长的长度。

我们定义一个数组len[i]表示以i为中心的最长的回文串的长度是多少。

现在我们再结合前面的结论，我们假设现在有一个较长的回文串，我们已知它的对称轴，可以把它表示成————x————-，（即以x为中心的一个回文串.

假设我们已经处理完了左半边的最长回文串的长度

可以把回文串转化成 ------yyyyy------x-------z-------;

，我们现在想要求出len[z]的值，（假设z和中间的y关于x对称），那么根据回文串的性质，两边要满足对称的关系，那么我们可以直接确定右边的部分情况。

右边肯定和左边一样，就能转化为----yyyyy------x----yyyyy----------。
很好，这样我们相当于是不用费脑就知道了右边至少回文长度为5（由前面的性质3可以确定）

在这基础上，我们在向外扩展，就省掉了前面没有必要的操作。
在这期间，我们可以用mid和r来维护。

### mid和r
同时记录一个mid，一个r，分别代表 已经确定的右侧最靠右的回文串的对称中心和右边界。
### 重要结论：
### 保持r是最右的才能保证我们提前确定的部分回文半径尽量多。（想一想，为什么？\(^o^)/~）

这样Manacher算法就彻底地完成了！！！

如果你没有看懂没有关系，因为真正的主角还没登场！

### 真正精彩的部分在代码哦\(^o^)/~

### 相信你看完了代码，会对Manacher算法有更深的了解
！！！

# 前方高能！！！
##  CODE：


```cpp


//Manacher算法总结： 
//Manacher算法用来处理字符串中的回文字符串
//它可以很快地求出一个字符串中最大的回文串的长度。 
#include<\(^o^)/~>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
//每一个字符数组都有其自己的含义 
const int maxn=11000005;
//解释一下: 
char data[maxn<<1]; //这是data的字符串数组，包括处理后的字符串 
int p[maxn<<1];//p[i]记录了以i这个节点作为回文中心的回文串的最长的长度 
int cnt;//cnt是字符串数组的长度 
int ans;//ans是最终的答案，需要通过p[]数组更新 
inline void read()
{
    char c=getchar();//一个一个字符地读入 
    data[0]='~';
    //初始状态赋值为‘~ ’ 
    cnt=1;
	data[cnt]='|';//在最前面先插一个板子。 
    while(c<'a' || c>'z') 
	c=getchar();//输入字符 
    while(c>='a' && c<='z')
	{
		data[++cnt]=c;//现将这个字符读入 
		data[++cnt]='|';//边读就边吧‘| ’插入进去，便于之后的求值 
		c=getchar();
	} //这里是读入字符串的部分 
}
int main()
{
	read();//读入加处理 
	//读完了字符串，同时也预处理了，插入了很多板子。
	//接下来将要进入manacher算法的核心部分 
	int r=0;
	int mid=0;//先把r和mid赋值初始值都是0； 
	for(int i=1;i<=cnt;i++)
	{
		//现在进入manacher的算法流程，i从1到cnt枚举的是每一个回文中心 
		//因为我们处理的时候已经插了板子，于是在两个数之间的和在某一个字符上的
		//回文子串就都能考虑到 
		//p[i]肯定要从一个初始值开始判断。 
		if(i<=r)
		{
			p[i]=min(p[(mid<<1)-i],r-i+1);
		}
		//r是当前的右区间 
		//(mid<<1)的意思就是mid*2。
		//我们这样得到了一个p[i],可以保证在这段p[i]的长度中一定是回文的
		//但有可能回文的长度更大，这就需要我们去枚举 
		while(data[i-p[i]]==data[i+p[i]]) 
		++p[i]; 
		//这里是一个暴力枚举的过程。
		//从中间向外展开，看以i为回文中心的回文字符串最大的长度 
		if(p[i]+i>r) 
		{
			r=p[i]+i-1;
			mid=i;
		}//这里是更新的操作，我们更新回文到达的地方 以及mid 
		if(p[i]>ans) 
		ans=p[i];//把答案更新 
	}
	printf("%d\n",ans-1);
	return 0;
} 
```


---

## 作者：Gralerfics (赞：6)

## Question Description
```
	给出一个只由小写英文字符 a, b, c... y, z 组成的字符串S, 求S中最长回文串的长度.
```
---
### Manacher Algorithm
#### Step 1
		考虑一个回文串S', 它可能具有奇数长度或偶数长度. Manacher算法需要回文串具有奇数长度. 所以我们可以用'#'将读入串S的每个字符分隔:
        		abbabcacba ---> ##a#b#b#a#b#c#a#c#b#a#
		这样就保证了我们需要的字串长度都是奇数.
        
        回文串的中间字符记作中心, 其 ceil( S.length / 2 ) 的值记作回文半径.

```cpp
	scanf("%s", t);
    m = strlen(t);
    
    a[0] = a[1] = '#';
    for (int i = 1; i <= m; i++) {
        a[ ( i << 1 ) ] = t[i - 1];
        a[ ( i << 1 ) + 1 ] = '#';
    }
    n = ( m << 1 ) + 2;
```

#### Step 2
		接下来我们考虑回文串S', 令其中心为 mid, 回文半径为 r0.
        
        由回文串的对称性, 显然有:
        		S'[mid + x] = S'[mid - x] (0 ≤ x < r0).
        
        那么我们再设 r[x] 为S中以x为中心的最长回文子串的回文半径, 则有:
        		r[mid + x] = r[mid - x] (0 ≤ x < r0).
#### Step 3
        考虑从左向右遍历 i, 递推出 r[i].
        记录当前已求得的回文子串右端最远延伸到的位置 maxright ( maxright 的左侧即为我们的已知区域 ) , 和该回文子串的回文中心 mid.
        
		对于每个 i:
        
        	1. 先判断 i 是否在 maxright 的范围内, 若在则进行 '2.', 若 i  已超出maxright, 则进行 '3.'.
            
            2. i 在 maxright 范围内, r[ ( mid << 1 ) - i ] 即为 i 关于当前 mid 的对称点处的最长回文子串回文半径长度, r[i] 就可以以 r[ (mid << 1) - i ] 为基数开始扩展.
            但此时, 若 r[ ( mid << 1 ) - i ] 超过了 r[mid] + mid - i ( 即 i 到 maxright 的距离 ), 就只能将 r[i] 赋值为 r[mid] + mid - i, 因为以 i 为中心, r[ ( mid << 1 ) - i ] 为回文半径的子串右端此时已超过 maxright, 即已超过已知范围, 而不能确定 r[i] 实际上能否达到该长度.
            故 r[i] = min( r[ ( mid << 1 ) - i ], r[mid] + mid - i );
            并进行 '4.'.
            
            3. i 超出 maxright, 不能利用对称性, 故 r[i] = 1, 进行 '4.'.
            
            4. 以当前 i 和 r[i] 开始暴力向外拓展至求得 r[i] 最终结果. 并将其右端与 maxright 比较, 更新 maxright.
            
		至此算法完成, 答案即为最大的 r[i].

### Source
```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#define min(x, y) (x < y)? x : y
using namespace std;

char t[11000005], a[11000005];
int n, m, r[23000000], ans = 0;

int main() {
    scanf("%s", t);
    m = strlen(t);

    a[0] = a[1] = '#';
    for (int i = 1; i <= m; i++) {
        a[ ( i << 1 ) ] = t[i - 1];
        a[ ( i << 1 ) + 1 ] = '#';
    }
    n = ( m << 1 ) + 2;
    
    int mid = 1, maxright = 1;
    r[1] = 1;
    for (int i = 2 ; i<n ; i++) {
        if (i < maxright) r[i]=min(r[ ( mid << 1 ) - i], r[mid] + mid - i); else r[i] = 1;
        while (a[i - r[i]] == a[i + r[i]]) r[i]++;
        if (i + r[i] > maxright) {
            maxright = i + r[i];
            mid = i;
        }
        if (r[i] > ans)ans = r[i];
    }
    
    printf("%d\n", ans - 1);
    
    return 0;
}

```


---

## 作者：小蒟蒻皮皮鱼 (赞：5)

本题解同步发布于[个人博客](https://www.cnblogs.com/lcezych/p/11912746.html)

## Manacher

manacher是一种$O(n)$求最长回文子串的算法，俗称马拉车~~（滑稽）~~

直接步入正题

首先可以知道的是：每一个回文串都有自己的对称中心，相应的也有自己的最大延伸长度（可以称之为“半径”）

我们设$rad[i]$表示以$i$为中心的回文子串的半径，那么只需要知道所有的$rad[i]$就可以求出最长回文子串了

从$1$到$n$枚举$i$，求解$rad[i]$

设当前已经求到了$rad[k]$，设前$k-1$个数中$rad[i]+i$（即右端点）最大的数为$mid$，令$r=mid+rad[mid]$

那么可以证明一个点$i$关于$mid$的对称点是$2\times mid-i$（两点距离公式）

opt1：如果$k\leq r$ 

![1574412665820](https://cdn.luogu.com.cn/upload/image_hosting/zur5xca7.png)

方便起见，令$j=2\times mid-k$

1.若$j-rad[j]>mid-rad[mid]$，即以$j$点为中心的最长回文子串的左端点在以$mid$为中心的最长回文子串的左端点右边，则$rad[i]$可以直接由$rad[j]$转移过来（因为$2\times mid-r$~$mid$和$mid$~$r$是对称的，所以$k$的半径和$j$的半径是一样的），即$rad[i]=rad[j]$

2.若$j-rad[j]\leq mid-rad[mid]$，则$rad[k]$至少是$r-k$。接下来再暴力延伸，顺便更新$mid$和$r$

opt2：如果$k>r$

直接暴力延伸，顺便更新$mid$和$r$

可以发现每次暴力延伸的时候，暴力延伸多少，$r$也会变化多少，且$r$是递增的且不超过$n$的数

关于复杂度：

由于每一个字符最多只会被遍历一次，所以复杂度是$O(n)$的

实现细节：

1.由于长度为偶数的回文串对称中心并不能实际找到，所以在两个字符之间插入#。这样不会影响答案，并且可以解决这个问题

2.对于不同情况的相似之处可以合并到一起来降低码量，如op1.1的直接转移和opt1.2的转移等

3.不要忘了更新$mid$和$r$

4.注意下标

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char cString[22000005];
int iRad[22000005];
int iLen,iAns;

void read()
{
	char c = getchar();
	cString[0] = '|', cString[++iLen] = '#';
	while(c < 'a' || c > 'z') c = getchar();
	while(c >= 'a'&& c <= 'z') cString[++iLen] = c, cString[++iLen] = '#', c = getchar();
}

int main()
{
	read();//读入 
	for(int i = 1, mid = 0, r = 0; i <= iLen; i++)
	{
		if(i <= r) iRad[i] = min(iRad[mid * 2 - i], r - i + 1);//opt1
		while(cString[i - iRad[i]] == cString[i + iRad[i]]) ++iRad[i];//opt1.2,opt2 尝试暴力延伸 
		if(i + iRad[i] > r) r = i + iRad[i] - 1, mid = i;//更新mid和r 
		if(iRad[i] > iAns) iAns = iRad[i];//更新答案 
	}
	printf("%d", iAns-1);
}
```



---

## 作者：殇雪 (赞：3)

Manacher算法

我们把一个回文串中最左或最右位置的字符与其对称轴的距离称为回文半径。Manacher定义了一个回文半径数组RL，用RL[i]表示以第i个字符为对称轴的回文串的回文半径。我们一般对字符串从左往右处理，因此这里定义RL[i]为第i个字符为对称轴的回文串的最右一个字符与字符i的距离。对于上面插入分隔符之后的两个串，可以得到RL数组：


char:    # a # b # a #

RL :    1 2 1 4 1 2 1

RL-1:    0 1 0 3 0 1 0

i :    0 1 2 3 4 5 6


char:    # a # b # b # a #

RL :    1 2 1 2 5 2 1 2 1

RL-1:    0 1 0 1 4 1 0 1 0

i :    0 1 2 3 4 5 6 7 8

上面我们还求了一下RL[i]-1。通过观察可以发现，RL[i]-1的值，正是在原本那个没有插入过分隔符的串中，以位置i为对称轴的最长回文串的长度。那么只要我们求出了RL数组，就能得到最长回文子串的长度。


于是问题变成了，怎样高效地求的RL数组。基本思路是利用回文串的对称性，扩展回文串。

1）当i在MaxRight的左边

我们知道，图中两个红色块之间（包括红色块）的串是回文的；并且以i为对称轴的回文串，是与红色块间的回文串有所重叠的。我们找到i关于pos的对称位置j，这个j对应的RL[j]我们是已经算过的。根据回文串的对称性，以i为对称轴的回文串和以j为对称轴的回文串，有一部分是相同的。这里又有两种细分的情况。


以j为对称轴的回文串比较短，短到像下图这样


这时我们知道RL[i]至少不会小于RL[j]，并且已经知道了部分的以i为中心的回文串，于是可以令RL[i]=RL[j]。但是以i为对称轴的回文串可能实际上更长，因此我们试着以i为对称轴，继续往左右两边扩展，直到左右两边字符不同，或者到达边界。


由于对称性，有：


step 1: 令RL[i]=min(RL[2\*pos-i], MaxRight-i)

step 2: 以i为中心扩展回文串，直到左右两边字符不同，或者到达边界。

step 3: 更新MaxRight和pos


2）当i在MaxRight的右边

暴力更新

 

```cpp
    #pragma GCC optimize("-O2")
    #include<bits/stdc++.h>
    #define N 320007
    using namespace std;
    int tot,len,mr,pos,ml,p[N];
    char ch[N],s[N];
    int main () {
        s[0]='$';
        freopen("mcf.in","r",stdin);
        while(scanf("%s",ch)!=EOF) {
            len=strlen(ch);tot=0;
            for (int i=0;i<len;i++)
             s[++tot]='#',s[++tot]=ch[i];
            s[++tot]='#'; s[++tot]=21;
             mr=pos=ml=0;
            for (int i=1;i<tot;i++) {
                if (i<mr) p[i]=min(p[pos*2-i],mr-i);
                else p[i]=1;
                while (s[i+p[i]]==s[i-p[i]]) p[i]++;
                if (i+p[i]>mr)  mr=i+p[i],pos=i;
                ml=max(ml,p[i]-1);
            }
            printf("%d\n",ml);
        }
    }

```

---

## 作者：混沌 (赞：3)

原本用的cin结果最后一个点t了，用了scanf果然过了。。。。。。。。。

附代码+简略解析






```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=11000000;
int num;
char t[maxn];//原字符串
char l[maxn<<1];//新字符串
int len[maxn<<1];
void neww(){
    l[0]='$';//防止过界
    num=num*2+3;//num始终字符总个数
    for(int i=1;i<=num-2;i=i+2){
        l[i]='#';
        l[i+1]=t[i/2];
    }
    l[num-1]='@'; 
}
int k(){
    int mx=0,ans=0,po=0;//mx:当前最长子回文串的右端点的最大值 po为mx对应回文串的中点
    for(int i=1;i<=num-1;i++){
        if(i<mx){//判断i点是否被此回文串包含
            len[i]=min(mx-i,len[2*po-i]);//  2*po-i  为i关于po的对称点，因为在i点前，所以此点len值为已知
        } 
        else{
            if(l[i]=='#') len[i]=1;
            if(l[i]!='#') len[i]=2;
        }
        while(l[i-len[i]]==l[i+len[i]]){
            len[i]++;
        }
        if(mx<i+len[i]-1){//更新
            mx=i+len[i]-1;
            po=i;
        }
        ans=max(ans,len[i]-1);
    }
    return ans;
}
int main(){
    scanf("%s",t);
    num=strlen(t);
    neww();
    printf("%d",k()); 
    return 0;
}
```

---

## 作者：3493441984zz (赞：2)

# 回文自动机

虽然过不去这个题目。。。但是没有回文自动机的模板题，拿这个题练练手也阔以$qwq$


------------
[安利我的回文自动机日报](https://www.luogu.org/blog/zhouzhuo/qiang-shi-tu-xie-hui-wen-zi-dong-ji)

这个题目的话不要太模板

我们需要求出最长的回文串的长度，而我们知道，回文自动机的每个节点都代表一个回文串，日报里提及了

并且每个点我们都存了长度$len$，那么我们在新建节点的时候对新的回文串长度取$max$即可

接下来是美滋滋的代码时间~~~(只能得到$75$分，就把$75$分当做满分呗$qwq$)

~~~cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#define N 11000007
using namespace std;
int n,last,cnt=1,ans;
int len[N],ch[N][26],fail[N];
char s[N];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	s[0]='#';
	fail[0]=1,len[1]=-1;
	for(int i=1;i<=n;++i)
	{
		int j;
		while(s[i]!=s[i-len[last]-1])
			last=fail[last];
		if(!ch[last][s[i]-'a'])
		{
			int now=++cnt;
			len[now]=len[last]+2;
			ans=max(ans,len[now]);
			j=fail[last];
			while(s[i]!=s[i-len[j]-1])
				j=fail[j];
			fail[now]=ch[j][s[i]-'a'];
			ch[last][s[i]-'a']=now;
		}
		last=ch[last][s[i]-'a'];
	}
	printf("%d",ans);
	return 0;
}
~~~

---

## 作者：傅思维666 (赞：1)

## 这是一篇：

## 详解Manacher算法的博客

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11930356.html)

# Manacher算法详解

版权声明：部分内容及图片参考自[简书]( https://www.jianshu.com/ )。

---

本篇随笔详解一下信息学奥林匹克竞赛中字符串问题的一种较为常用的算法——$Manacher$算法。也被戏称为“马拉车算法”。这种算法常被应用于求解**最长回文子串长度**的问题。对于字符串的基本处理及最长回文子串概念的相关知识，属于基础语法和概念知识的范畴。本随笔作为一篇探讨算法本身的随笔，不再对此进行过多介绍，请有需要的读者自行查阅相关资料。

---

### 例题及分析

——$POJ\,\,3974\,\, Palindrome$

[POJ链接]( http://poj.org/problem?id=3974 )

[题解博客链接]()

**题目大意：**给定一个长度为$N$的字符串，求其最长回文子串长度。

**题目分析：**算法：哈希+二分（复杂度为$O(NlogN)$）,$Manacher$算法，（复杂度$O(N)$）。

#### 哈希+二分

我们可以用$O(N)$的时间处理出字符串的每个前缀的哈希值，这样，我们就可以通过**子串哈希**求出每一个子串的哈希值。根据回文串的性质，我们可以枚举每一个数为中心，用$O(logN)$的时间求出最长的回文子串，然后取最大值即可（总时间复杂度为$O(NlogN)$）.

#### $Manacher$算法

————

---

## Manacher算法的相关概念

这里需要先提一嘴的是，为了方便处理，在进行$Manacher$算法前，我们输入的字符串需要被处理成中间“夹带”字符串的形式。即：假如我们输入的字符串为：$aabba$，就会被处理成$\#a\#a\#b\#b\#a\#$。

### 1、最大回文半径

上图理解：

![]( https://upload-images.jianshu.io/upload_images/12738509-29660a214405b83b?imageMogr2/auto-orient/strip|imageView2/2/w/519/format/webp )

所谓最大回文半径，可以这样理解：就是针对于每一个位置（注意，这里的#号也算是位置！），我们向两侧扩展，求出以这个位置为中心的最长回文子串，那么这个位置的最大回文半径就是这个最长回文子串的长度的一半（因为是半径）。

这里需要注意：如果是奇数回文子串的话，这个最大回文半径还需要加上这个中心位置本身！

### 2、最右回文右边界

我们已经知道，对于每个位置，都可以求出一个最大回文半径。（即便这个最大回文半径就是1），那么，对于每个位置扩展出来的最大回文子串，都有一个右边界（这个应该很好理解）。那么，对于当前已经枚举的所有位置中，得出的最右侧的右边界就是这个回文子串的“最右回文右边界”（这是一个顾名思义进行理解的过程）。

还是上图理解：

![]( https://upload-images.jianshu.io/upload_images/12738509-37438e9ddb6c4ccd?imageMogr2/auto-orient/strip|imageView2/2/w/288/format/webp )

### 3、最右回文右边界的对称中心

就是上面讲过的“最右回文右边界”的对称中心（emm...）

继续上图理解：

![]( https://upload-images.jianshu.io/upload_images/12738509-8ae101de5e70fce7?imageMogr2/auto-orient/strip|imageView2/2/w/259/format/webp )

---

## Manacher算法的实现原理

因为$Manacher$算法的时间复杂度是线性的（$O(N)$），所以我们在思考其实现原理的时候也需要考虑如何线性地扫描求解一个最长回文子串的问题。

假设现在已经扫描到某一个位置，那么这个位置对应的最右回文右边界和其对称中心都是已知的。那么现在我们要继续往下遍历，就会出现这么几种情况：

第一种：**下一个位置$i$的位置在最右回文右边界左侧，且在其对称中心右侧。**

那么根据当前的最右回文右边界的对称中心（有了最右回文右边界和其对称中心，我们就可以知道这个回文子串究竟是哪部分），我们就可以把这个位置$i$关于这个对称中心做对称，当然，这个对称之后的位置（通过计算可得是$mid\times 2-i$）的最长回文半径是不会大于当前位置的最大回文半径的，那么就把当前位置的最大回文半径更新成对称位置的回文半径。然后继续尝试扩展，看看能不能更大，持续更新最右回文右边界和其对称中心。

第二种：**下一个位置$i$的位置在最右回文右边界右侧**。

这种情况我们就无能为力了，因为对称过去已经超出了我们已知的范围，这个时候就需要从1开始遍历，更新最右回文右边界，和其对称中心。

总的来说，$Manacher$算法的精髓就在于对“扩展”最长回文子串的一种别致的思考。这种简化看似平平无奇（甚至我第一次看还觉得比二分慢），但是在数据量较大的情况下堪称利器。

---

## Manacher算法的代码实现

下面给出另一道模板题：

[洛谷 P3805]( https://www.luogu.com.cn/problem/P3805 )

（裸的马拉车）

的代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxl=51000100;
char a[maxl];
int rad[maxl];
char s[maxl<<1];
int len,ans=1;
void init()
{
    s[0]=s[1]='#';
    for(int i=0;i<len;i++)
    {
        s[i*2+2]=a[i];
        s[i*2+3]='#';
    }
    len=len*2+2;
}
void manacher()
{
    int mr=0,mid;
    for(int i=1;i<len;i++)//线性枚举
    {
        if(i<mr)
            rad[i]=min(rad[(mid<<1)-i],rad[mid]+mid-i);//如果是第一种情况，那么先给rad[i]赋上此时合法最大值。
        else
            rad[i]=1;//如果是第二种情况，什么也不知道，只能赋1
        for(;s[i+rad[i]]==s[i-rad[i]];rad[i]++)
            if(i+rad[i]>mr)//开始进行扩展，逐一增加rad[i]，同时更新最右回文右边界和其对称中心
            {
                mr=i+rad[i];
                mid=i;
            }
    }
}
int main()
{
    scanf("%s",a);
    len=strlen(a);
    init();//预处理部分，将原串处理成中间夹带'#'的串，便于操作。
    manacher();//开始拉车...
    for(int i=0;i<len;i++)
        ans=max(ans,rad[i]);//更新答案。
    printf("%d\n",ans-1);//注意，答案要减去1.
    return 0;
}
```



---

## 作者：WjNaG (赞：1)


### 题目描述：
给出一个只由小写英文字符a,b,c...y,z组成的字符串S,求S中最长回文串的长度.字符串长度为n

字符串长度len <= 11000000

### 题解：
用处:O(n)时间复杂度查最长回文子串

建议先看一遍代码
```cpp
#include <iostream>  
#include <cstring>
#include <algorithm>  
using namespace std;

char s[1000]; //原数组
char s_new[2000]; //插入分隔字符后的新数组
int p[2000]; //Palindrome，记录每个位置的最长回文

int Init(){ //插入分隔字符#
    int len = strlen(s);
    s_new[0] = '$';
    s_new[1] = '#';
    int j = 2;

    for (int i = 0; i < len; i++){
        s_new[j++] = s[i];
        s_new[j++] = '#';
    }

    s_new[j] = '\0';  //字符串结束
    return j;  // 返回 s_new 的长度
}

int Manacher(){
    int len = Init();  //取得新字符串长度并完成向 s_new 的转换
    int max_len = -1;  //最长回文长度

    int mid;
    int mx = 0; //mx->range

    for (int i = 1; i < len; i++){
        if (i < mx)
            p[i] = min(p[2 * mid - i], mx - i);
        else
            p[i] = 1;

        //往两端扩展，判断是否为回文
        while (s_new[i - p[i]] == s_new[i + p[i]])  // 不需边界判断，因为左有'$',右有'\0'
            p[i]++;

        //每走一步i，都要和mx比较，希望mx尽可能的远，这样才能更有机会执行 if(i < mx)这句代码，从而提高效率
        if (mx < i + p[i]){
            mid = i;
            mx = i + p[i];
        }

        max_len = max(max_len, p[i] - 1);
    }

    return max_len;
}

int main(){
        scanf("%s", s);
        printf("%d\n", Manacher());
    }
    return 0;
}
```
由于回文串的中点可能在字符上也可能在字符中间，所以我们用`'#’`占满字符中间的位置
```cpp
int Init(){ //插入分隔字符#
    int len = strlen(s);
    s_new[0] = '$';
    s_new[1] = '#';
    int j = 2;

    for (int i = 0; i < len; i++){
        s_new[j++] = s[i];
        s_new[j++] = '#';
    }

    s_new[j] = '\0';  //字符串结束
    return j;  // 返回 s_new 的长度
}
```

然后就很难理解了

我们从s[1]遍历到s[s_new.size]，循环变量为i；
设置一个辅助变量mx,表示已经触及到的最右边的字符,还要设置一个辅助变量mid，表示包含maxright的回文串的中点所在的位置。
我们可以计算出在这个回文串中i的对称点是`2 * mid - i`

如果i<mx,可以先把p[i]更新为
```cpp
p[i] = min(p[2 * mid - i], mx - i);
```
mx-i就是i到mx的距离
由于i的回文串可能会扩展到mx的右边，我们还要再加上这部分
而当i>mx时，我们无法得知关于p[i]的信息，只好从1开始遍历
```cpp
 //往两端扩展，判断是否为回文
        while (s_new[i - p[i]] == s_new[i + p[i]])  // 不需边界判断，因为左有'$',右有'\0'
            p[i]++;
```

最后再更新mx和 max_len就可以了
```cpp
 //每走一步i，都要和mx比较，希望mx尽可能的远，这样才能更有机会执行 if(i < mx)这句代码，从而提高效率
        if (mx < i + p[i]){
            mid = i;
            mx = i + p[i];
        }
        
 max_len = max(max_len, p[i] - 1);
```


如果没看懂，再推荐一篇不错的题解[传送门](https://kaispace.com.cn/index.php/archives/483/)


#### 写作时间：
2019-7-25

---

## 作者：G我就是菜G (赞：1)

### Manache

用于查找字符串中最长回文子串

由于字符串长度为奇数和偶数的情况考虑起来不同

我们在每个字符之间插入一个 $#$ 字符，以保证每次判断回文字符串的长度都为奇数

同时第 $0$ 个位置也令其为 $#$ 防止越界的情况

### 做法

1. $change$

在每两个字符之间插入 $#$ 

```cpp
void change()
{
    s[0]=s[1]='#';
    for (int i=0;i<len;i++)
    {
        s[i*2+2]=a[i];
        s[i*2+3]='#';
    }
    len=len*2+2;
    s[len]=0;
}
```

2. $Manache$

定义 $maxr$ 为当前可以扩展到的最右边节点，$mid$ 为包含 $s[maxr]$ 的回文串的中间位置

**当 $i$ 在 $mid$ 和 $maxr$ 中间时**

![](https://cdn.luogu.com.cn/upload/pic/59595.png)

显然有 $maxl=mid\times 2-maxr$

则能保证 $sum[i] \ge min(sum[maxl+maxr-i],sum[mid]-(i-mid))$

即 $sum[i] \ge min(sum[mid\times 2-i],sum[mid]+mid-i)$

然后向外扩展同时更新 $sum[i],mid$ 和 $maxr$ 就行了

**当 $i$ 在 $maxr$ 右边时**

由于我们不知道其对应点的信息

就从左右长度为1开始向外扩展，更新 $sum[i],mid$ 和 $maxr$

**显然 $i$ 不可能在 $mid$ 左边**
```cpp
void manache()
{
    int maxr=0,mid;
    for(int i=1;i<len;i++)
    {
        if (i<maxr) sum[i]=min(sum[(mid<<1)-i],sum[mid]+mid-i);
        else sum[i]=1;
        for (;s[i+sum[i]]==s[i-sum[i]];sum[i]++);
        if (sum[i]+i>maxr)
        {
            maxr=sum[i]+i;
            mid=i;
        }
    }
}
```

### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans,sum[22000010],len;
char a[22000010],s[22000010];

void manache()
{
    int maxr=0,mid;
    for(int i=1;i<len;i++)
    {
        if (i<maxr) sum[i]=min(sum[(mid<<1)-i],sum[mid]+mid-i);
        else sum[i]=1;
        for (;s[i+sum[i]]==s[i-sum[i]];sum[i]++);
        if (sum[i]+i>maxr)
        {
            maxr=sum[i]+i;
            mid=i;
        }
    }
}

void change()
{
    s[0]=s[1]='#';
    for (int i=0;i<len;i++)
    {
        s[i*2+2]=a[i];
        s[i*2+3]='#';
    }
    len=len*2+2;
    s[len]=0;
}

int main()
{
    scanf("%s",a);
    len=strlen(a);
    change();
    manache();
    ans=1;
    for (int i=0;i<len;i++)
        ans=max(ans,sum[i]);
    printf("%d\n",ans-1);
    return 0;
}
```

---

## 作者：ちゆき (赞：1)

# Manacher算法


这个马拉车算法Manacher's Algorithm是用来查找一个字符串的最

长回文子串的线性方法，由一个叫Manacher的人在1975年发明的，

这个方法的最大贡献是在于将时间复杂度提升到了线性，这是非常

了不起的。对于回文串想必大家都不陌生，就是正读反读都一样的

字符串，比如 "bob", "level", "noon" 等等，那么如何在一个字

符串中找出最长回文子串呢，可以以每一个字符为中心，向两边寻

找回文子串，在遍历完整个数组后，就可以找到最长的回文子串。

但是这个方法的时间复杂度为O(n*n)，并不是很高效，下面我们来

看时间复杂度为O(n)的马拉车算法。
    
    

由于回文串的长度可奇可偶，比如"bob"是奇数形式的回

文，"noon"就是偶数形式的回文，马拉车算法的第一步是预处理，

做法是在每一个字符的左右都加上一个特殊字符，比如加上'#'，

那么

```cpp
bob    -->    #b#o#b#

noon    -->    #n#o#o#n# 
```

这样做的好处是不论原字符串是奇数还是偶数个，处理之后得到的

字符串的个数都是奇数个，这样就不用分情况讨论了，而可以一起

搞定。接下来我们还需要和处理后的字符串t等长的数组p，其中p[ 

i ]表示以t[ i ]字符为中心的回文子串的半径，若p[ i ] = 1，

则该回文子串就是t[ i ]本身，那么我们来看一个简单的例子：

```cpp
# 1 # 2 # 2 # 1 # 2 # 2 # 
1 2 1 2 5 2 1 6 1 2 3 2 1
```

为啥我们关心回文子串的半径呢？看上面那个例子，以中间的 '1' 

为中心的回文子串 "#2#2#1#2#2#" 的半径是6，而为添加井号的回

文子串为 "22122"，长度是5，为半径减1。这是个普遍的规律么？

我们再看看之前的那个 "#b#o#b#"，我们很容易看出来以中间的 

'o' 为中心的回文串的半径是4，而 "bob"的长度是3，符合规律。

再来看偶数个的情况"noon"，添加井号后的回文串为 

"#n#o#o#n#"，以最中间的 '#' 为中心的回文串的半径是5，而 

"noon" 的长度是4，完美符合规律。所以我们只要找到了最大的半

径，就知道最长的回文子串的字符个数了。只知道长度无法确定子

串，我们还需要知道子串的起始位置。   



我们还是先来看中间的 '1' 在字符串 "#1#2#2#1#2#2#" 中的位置

是7，而半径是6，貌似7-6=1，刚好就是回文子串 "22122" 在原串 

"122122" 中的起始位置1。那么我们再来验证下 "bob"，"o" 在 

"#b#o#b#" 中的位置是3，但是半径是4，这一减成负的了，肯定不

对。所以我们应该至少把中心位置向后移动一位，才能为0啊，那

么我们就需要在前面增加一个字符，这个字符不能是井号，也不能

是s中可能出现的字符，所以我们暂且就用美元号吧，毕竟是博主

最爱的东西嘛。这样都不相同的话就不会改变p值了，那么末尾要

不要对应的也添加呢，其实不用的，不用加的原因是字符串的结尾

标识为'\0'，等于默认加过了。那此时 "o" 在 "$#b#o#b#" 中的

位置是4，半径是4，一减就是0了，貌似没啥问题。我们再来验证

一下那个数字串，中间的 '1' 在字符串 "$#1#2#2#1#2#2#" 中的

位置是8，而半径是6，这一减就是2了，而我们需要的是1，所以我

们要除以2。之前的 "bob" 因为相减已经是0了，除以2还是0，没

有问题。再来验证一下 "noon"，中间的 '#' 在字符串 

"$#n#o#o#n#" 中的位置是5，半径也是5，相减并除以2还是0，完

美。可以任意试试其他的例子，都是符合这个规律的，最长子串的

长度是半径减1，起始位置是中间位置减去半径再除以2。


那么下面我们就来看如何求p数组，需要新增两个辅助变量mx和

id，其中id为能延伸到最右端的位置的那个回文子串的中心点位

置，mx是回文串能延伸到的最右端的位置，这个算法的最核心的一

行如下：
```cpp
p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
```
拆开：
```cpp
if(mx>i)
	p[i]=min(p[2*id-i],mx-i);
else
	p[i]=1;
```

当 mx - i > P[ j ] 的时候，以S[ j ]为中心的回文子串包含在

以S[ id ]为中心的回文子串中，由于 i 和 j 对称，以S[ i ]为

中心的回文子串必然包含在以S[ id ]为中心的回文子串中，所以

必有 P[ i ] = P[ j ]，见下图：



![](https://img2018.cnblogs.com/blog/391947/201809/391947-20180916233749134-798948486.png)


当 P[j] >= mx - i 的时候，以S[j]为中心的回文子串不一定完全

包含于以S[id]为中心的回文子串中，但是基于对称性可知，下图

中两个绿框所包围的部分是相同的，也就是说以S[i]为中心的回文

子串，其向右至少会扩张到mx的位置，也就是说 P[i] = mx - i。

至于mx之后的部分是否对称，就只能老老实实去匹配了。

![](https://img2018.cnblogs.com/blog/391947/201809/391947-20180916233809298-960515229.png)


对于 mx <= i 的情况，无法对 P[i]做更多的假设，只能P[i] = 

1，然后再去匹配了。

 

参见如下实现代码：


```cpp
#include <vector>
#include <iostream>
#include <string>

using namespace std;

string Manacher(string s) {
    // Insert '#'
    string t = "$#";
    for (int i = 0; i < s.size(); ++i) {
        t += s[i];
        t += "#";
    }
    // Process t
    vector<int> p(t.size(), 0);
    int mx = 0, id = 0, resLen = 0, resCenter = 0;
    for (int i = 1; i < t.size(); ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        if (resLen < p[i]) {
            resLen = p[i];
            resCenter = i;
        }
    }
    return s.substr((resCenter - resLen) / 2, resLen - 1);
}

int main() {
    string s1;
    scanf("%s",s1);
    cout<<Manacher(s1)<<endl;//输出最长的回文子串(不是长度哦)
    return 0;
}
```
###### ~~转载？~~

---

## 作者：leozhang (赞：1)

先安利一发自己的博客，博客里的讲解是有图的：

https://blog.csdn.net/lleozhang/article/details/82763761

manacher是很简单的字符串回文算法，作用是O（n）求出一个字符串的最长回文子串

下面给出这一算法的详解

首先，我们设原字符串是aaabba，很显然，这个字符串最长的回文子串长度为4

那么我们就要思考一种算法来计算出这个长度

于是manacher横空出世

首先，我们知道，一个回文子串一定有一个对称轴（或者你叫对称中心？），所以正常来讲，如果想O（n）求出最长回文子串，我们只需枚举每个对称轴，然后O（1）递推即可

可是现在就产生了一个问题：如果原字符串是上面说的那样，那...对称轴是在ab中间的啊，这怎么找出来啊

所以manacher需要一个操作，即在所有中间的位置插入一个'#'之类的无用字符，这样我们就可以忽略掉对称轴在两个字符中间的情况，只考虑对称轴落在字符上的情况即可

所以我们记p[i]表示以i为回文中心，回文半径为p[i]

然后我们考虑递推

怎么推？

我们记录一个maxp，表示在i之前所有的回文中心中，回文右端点最远在哪，记p0表示这个最远的右端点所对应的回文中心

接下来，我们考虑如何用这个东西维护p[i]

这是需要分类讨论的，即：

①：

若i<maxp，有：

p[i]=min(p[2*p0-i],p[p0]+p0-i);

这一点是显而易见的：如果i<maxp，那么我们显然可以找出一个j，使j与i关于p0对称，于是j=2*p0-i

而根据对称性，j周围的字符一定和i周围的字符相同，所以p[i]可以由p[j]来更新

，由于对称性，所以i右侧一部分和j左侧一部分相同，同时i左侧一部分和j右侧一部分相同，同时根据j的对称性，j左右两侧相同，故i左右两侧相同，为回文。

至于另一个也很好理解，就是从i到maxp的一段，假设他整个都能构成回文。这一值和刚才对称求出的一个值取最小值才能保证结果的合理性。

②：i>=maxp

没什么办法，暴力吧..

接下来谈谈暴力：

其实无论是情况①还是情况②都需要暴力，因为我们无法保证①求出的是最大值，我们只能保证①求出的是一个可能的合法答案

所以我们需要暴力从p[i]的已有值开始向下跳，跳到不能跳为止即可

剩下的就是代码了

比较好写

（ps：代码是不和题解里某位dalao代码很像？是的！就是和他学的模板！）

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
char a[51000005];
char s[102000005];
int p[51000005];
int maxp,p0,l;
int ans=1;
void manacher()
{
	for(int i=1;i<l;i++)
	{
		if(i<maxp)
		{
			int j=(p0<<1)-i;
			p[i]=min(p[j],p[p0]+p0-i);
		}else
		{
			p[i]=1;
		}
		while(s[i-p[i]]==s[i+p[i]])
		{
			p[i]++;
		}
		if(i+p[i]>maxp)
		{
			p0=i;
			maxp=i+p[i];
		}
	}
}
int main()
{
	scanf("%s",a+1);
	l=strlen(a+1);
	p[1]=1;
	s[0]=s[1]='#';
	for(int i=1;i<=l;i++)
	{
		s[2*i]=a[i];
		s[2*i+1]='#';
	}
	l=(l<<1)+2;
	s[l]='0';
	manacher();
	for(int i=1;i<=l;i++)
	{
		ans=max(ans,p[i]-1);
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：arfa (赞：1)

> ## $Manacher$

据说这是一种$O(n)$的方fa,所以就凑来看一看。

没想到$TLE$一大片(其实还有$RE$)。

各路大佬已经把思路讲的很清楚了,这里来给$Pascal$选手一些$fuli$。

```pascal
// luogu-judger-enable-o2 //最好开着
Uses math;

var
    len:array[-10..31000007] of longint; //注意不要开一千万
    s:array[-10..31000007] of char; //千万不要用ansistring
    i,right,ans,mid,Slen,Tlen:longint;
    t:ansistring; //读入可以用

begin
    readln(t);
    Tlen:=length(t);
    s[0]:='1'; s[1]:='2'; inc(Slen); //能的话,最好像我这样子打(坑点)
    for i:=1 to Tlen do
    begin
        inc(Slen,2); //能的话,最好像我这样子打(坑点)
        s[Slen-1]:=t[i]; //能的话,最好像我这样子打(坑点)
        s[Slen]:='2'; //能的话,最好像我这样子打(坑点)
    end;
    inc(Slen); s[Slen]:='3'; //能的话,最好像我这样子打(坑点)

    right:=0; mid:=0; ans:=0; //全是零
    for i:=1 to Slen do //从1到len,谢谢
    begin
        if (i<right) then
            len[i]:=min(right-i,len[mid*2-i]); //*2不要打位运算,有玄学优先级
        while (s[i+len[i]+1]=s[i-len[i]-1]) do //不用特判,但是要+1 or -1
            inc(len[i]);
        if right<i+len[i] then
        begin
            right:=i+len[i];
            mid:=i;
        end;
        ans:=max(ans,len[i]);
    end;
    writeln(ans);
end.

```

博主留了一个坑点,大家自己找一下(~~所以最好不要抄标~~)。


---

## 作者：多多poi、blink (赞：1)

# Manacher算法
问题：对于1个字符序列，我们如何求得它得最长回文子序列

	     容易想到，枚举它所有的子序列，然后依次判·断，但是显然我们不能接受这种方
         法的时间复杂度；
         实际上我们有一种叫Manacher的算法，俗称马拉车算法，它可以在O(N)的时间里
         解决这个问题
## Manacher算法流程
首先，容易知道，当字符个数为奇数时，回文对称中心也会是一个字符，这样我们便容易得到回文中心的坐标(将这个字符序列看成一个以是s[0]为原点的数轴)
	
    	如：ABABA(假设我们是从s[1]开始存储字符的)
   那么它的对称中心坐标显然是3，最长回文半径也是3，如果字符个数为偶数呢，为方便
   操作，我们常常向原序列中插入一些不影响结果的相同字符(隔板)，将原序列转化为一个便于操作的序列
   		
        	如：ABBA  我们向这个序列中插入｜；
            
       就变成了:  ~|A|B|B|A|^(下面再说为什么两边混入了奇怪的东西)
       
    它的对称中心坐标显然是5，最长回文半径也为5，由于我们并不知道所给数据是奇数还是
    偶数，所以我们无论奇偶，都给原序列插入隔板(包括两端之外)，
    这样一来，如果原序列是偶数，那么我们插入的隔板数就是奇数；如果原序列是奇数，
    那么我们插入的隔板数就是偶数，
    
    	而显然：奇数+偶数=奇数；
    这样我们就将原序列变成了我们想要的序列，现在我们维护下面几个东西：
    	mid：已扫描序列中最长回文序列对称中心坐标
        	r：已扫描序列的右边界坐标
       	rt[i]：以i为对称中心的最长回文半径
    设r关于mid的对称点坐标为l，i关于mid对称点坐标为j。
那么，当i<r时，必然有rt[i]>=rt[j],因为他们关于mid对称，取>是因为我们不知道r外面是什么情况，所以我们更新rt[i]时要保证它没有超出r，

		即是：rt[i]=min(r-i，r[mid*2-i])；
        
  如果i第一次访问到r，那么不妨先给rt[i]赋值为1，再次它也有一个吧，然后我们就尝试去看看r外面的世界
  
  	即是：while(b[i]-rt[i]==b[i]+rt[i])
    	rt[i]++;//以i为中心同时向两边拓展，若相同则rt[i]+1，
        		//这也是为什么两端会混入奇怪的东西；
 当i走向外面的世界时，如果i+rt[i]>r;
 	
    	更新：mid=i，r=i+rt[i];
 最后答案为max(rt[1]，rt[2]....，rt[n])-1(假设n为处理之后字符的长度)
 
##  上代码：
 
 ```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=11000005;
char a[inf<<2],b[inf<<2];
int rt[inf<<2];
int insert()
{
	int len=strlen(a);
	int j=2;
	b[0]='~';
	b[1]='｜';
	for(int i=0;i<len;i++)
	{
		b[j++]=a[i];
		b[j++]='｜';
	}
	b[j]='^';
	return j;
}
void manacher()
{
	int len=insert(),mid=1,r=1,ans=-1;
	for(int i=1;i<len;i++)
	{
		if(i<r)
			rt[i]=min(r-i,rt[mid*2-i]);
		else rt[i]=1;
		while(b[i-rt[i]]==b[i+rt[i]]) rt[i]++;
		if(r<i+rt[i])
		{
			mid=i;
			r=i+rt[i];
		}
		ans=max(ans,rt[i]-1);
	}
	printf("%d",ans);
}
int main()
{
	scanf("%s",a);
	manacher();
	return 0;
}
```


---

## 作者：Sangber (赞：0)

----
[$$\large{\color{CornflowerBlue}{\mathfrak{Blog}}}$$](https://www.cnblogs.com/zsbzsb/p/11625906.html)

----

### 前言
这是一道模板题~~但我还是来写题解了~~  

----
### 解法
首先根据题目大（biao）意（ti），这是一道 $\texttt{Manacher}$ 模板题。  
在这里我就不多做赘述了，感兴趣的可以去看我博客（见上方）

----
### 参考代码
我就只把 $AC$ 代码放一下，仅供参考
```cpp
/*--------------------------------
--Author: The Ace Bee-------------
--Blog: www.cnblogs.com/zsbzsb----
--This code is made by The Ace Bee
--------------------------------*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#define rg register
#define clr(x, y) memset(x, y, sizeof x)
using namespace std;
template < typename T > inline void read(T& s) {
	s = 0; int f = 0; char c = getchar();
	while (!isdigit(c)) f |= (c == '-'), c = getchar();
	while (isdigit(c)) s = s * 10 + (c ^ 48), c = getchar();
	s = f ? -s : s;
}

const int _(11000010);

int n, f[_ << 1];
char s[_ << 1], tmp[_];

inline int manacher() {
	int n = strlen(s + 1);
	for (rg int i = 1; i <= n; ++i) tmp[i] = s[i];
	for (rg int i = 1, j = 0; i <= n; ++i) s[++j] = '`', s[++j] = tmp[i];
	s[0] = s[n * 2 + 1] = '`', n = n * 2 + 1;
	int mx = 0, mid;
	for (rg int i = 1; i <= n; ++i) {
		f[i] = i < mx ? min(mx - i, f[mid * 2 - i]) : 0;
		while (s[i - f[i] - 1] == s[i + f[i] + 1]) ++f[i];
		if (i + f[i] > mx) mx = i + f[i], mid = i;
	}
	int res = 0;
	for (rg int i = 1; i <= n; ++i) res = max(res, f[i]);
	return res;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
#endif
	scanf("%s", s + 1);
	printf("%d\n", manacher());
	return 0;
}
```
**完结撒花 $qwq$**

---

