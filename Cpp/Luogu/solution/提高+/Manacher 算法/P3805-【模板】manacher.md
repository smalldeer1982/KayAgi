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

## 作者：谁是鸽王 (赞：1516)

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

## 作者：Nemlit (赞：231)

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

## 作者：zcysky (赞：53)

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

## 作者：skydogli (赞：50)

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

## 作者：Eason_cyx (赞：41)

### 算法介绍

Manacher，是一种用于求解字符串中最长回文串的算法。它可以在 $O(n)$ 的时间里求出以每一个字符为中心的回文串最大长度。

### 算法流程

下记 $p_i$ 为以第 $i$ 个字符为中心的回文串最大长度。**例如，`ababa` 的长度是 $3$。**

下面所说的“暴力计算”均指如下代码（假设当前在 $i$，需要暴力计算 $p_i$）：

```cpp
while(s[i+p[i]] == s[i-p[i]]) p[i]++;
```

-----

首先处理一个问题：有些回文串长度是偶数，有些是奇数。奇数可以枚举中心点；但是偶数不行！为了解决这个问题，我们可以在所有字符之间插入一个 `#`，这样偶回文串就被我们转换成了奇回文串了。

考虑当前需要求出 $p_i$。我们可以记录一个 $r$，用来表示在所有 $1 \le j < i$ 的 $j$ 中，以 $j$ 为中心点的回文串的右端点中，最右的那一个。记这个 $r$ 为右端点的回文串的中心点为 $j'$。此时我们需要进行分类讨论：

1. $r>i$

此时我们可以得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tqaxivi2.png)

这个图是什么意思？我们首先可以找到 $i$ 以 $j'$ 为对称中心的对称点 $i'=j'\times2-i$。然后，因为这一整个是一个回文串，所以对应地，$i'$ 下面那一段（指那一段子串）和 $i$ 下面那一段一定也相同。所以在这种情况下，$p_i=p_{i'}$，可以直接得出！

但是！情况不一定总是这么好。在 $r>i$ 的情况中，还有另外一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/l2fuf8jg.png)

如图，当 $p_{i'}$ 很大的时候，这一段可能超出了整个大回文串，当这个子串对称到以 $i$ 为中心的这边时，右端点超过了 $r$，而超出的部分我们一无所知！在这种情况下，我们不能保证 $i$ 的回文长度一定有这么长，只能保证从 $i$ 到 $r$ 这一段一定回文。所以，在这种情况下，我们可以令 $p_i=r-i$，然后**暴力向外计算** $p_i$ 的最终值。稍后我们会说明这样是对的。

这样，$r>i$ 的情况暂时被我们解决了。

在每次更新完 $p_i$ 后，注意要实时更新 $r$ 和 $j'$，用来计算后面的答案。

2. $r<i$

此时的情况如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/prjk7o9g.png)

此时可以很清晰地看出，没有任何可以使用的信息，所以只能暴力计算 $p_i$ 了。此时也需要更新 $r$。

遍历 $1 \sim n$ 重复如上过程，即可得到所有 $p_i$。因为在计算之前在字符串中还插入了一些 `#`，所以最终答案其实就是 $\max p_i-1$。

### 正确性证明

首先正确性是显然的。

对于复杂度，我们可以感性理解一下：在上面的三种情况中，第一种是 $O(1)$ 的；后两种都在不断地将 $r$ 向后推，而一共只有 $n$ 个位置；所以总的时间复杂度就是 $O(n)$。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int p[30000005], mx, id;
//注意：本题数据范围较大，要注意数组大小
//代码中 mx 即为讲解中的 r，id 为讲解中的 j'
int main() {
	string s = "##";
	char c; while(cin >> c) s += c, s += "#";
    //插入 #；为防止越界，在最前面也插一个 #
	int n = s.size(); s = ' ' + s;
	for(int i = 1;i <= n;i++) {
		p[i] = mx > i ? min(p[id*2-i], mx-i) : 1; //三目运算符，分别对应三种情况
		while(s[i + p[i]] == s[i - p[i]]) p[i]++; //暴力计算 p[i]
		if(i + p[i] > mx) mx = i + p[i], id = i; //更新右端点 r
	} int ans = 0; for(int i = 1;i <= n;i++) ans = max(ans, p[i]-1);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：6)

### 简介

Manacher 可以做到时间复杂度 $O(n)$ 求最长回文子串及相关问题。

Manacher 的思想是利用前面求出的东西加速后面的计算。它产生的原因主要是因为回文串的特殊性：如果求出了 $i-1$ 处的最长回文半径，那么这个回文串有可能延伸到 $i$ 后面，可以帮助 $i$ 的计算。

### 算法流程

首先，奇回文和偶回文不好处理，我们在每两个字符间加上 `#`，这样所有回文串都是奇回文了。

我们记录现在已知回文子串的最大右端点 $R$，和它对应的回文中心 $C$（为了最大限度利用已知条件）。假设第 $x$ 位的最长回文半径为 $p_x$。

假设现在处理到第 $i$ 位。我们有两种情况：

- 若 $i>R$，这时已有的条件无法帮助处理，暴力扩展即可。

- 若 $i\le R$，我们发现，$i'$ 的回文区域是我们已经求过的，于是我们就可以加速处理，放一张图：\
![](https://cdn.luogu.com.cn/upload/image_hosting/je325rbw.png)\
我们需要分三种情况考虑：

  - 若 $i'$ 的回文区域在 $[L,R]$ 内：\
  ![](https://cdn.luogu.com.cn/upload/image_hosting/i17wforc.png)\
  这时因为回文串翻转后还是回文串，而 $i'$ 已经无法扩展了，于是 $p_i=p_{i'}$。

  - 若 $i'$ 的回文区域超过了 $L$：\
  ![](https://cdn.luogu.com.cn/upload/image_hosting/pjpun92f.png)\
  这时，显然 $3$ 为 $1$ 的反转，而 $4$ 又为 $3$ 的反转，所以 $4$ 和 $1$ 相同。\
  但是 $2$ 一定不与 $1$ 的反转相同（否则 $[L,R]$ 可以扩展），也就是说 $2$ 一定不与 $4$ 的反转相同，那么 $i$ 只能扩展到 $R$，即 $p_i=R-i+1$。
 
  - 若 $i'$ 的回文区域左端点刚好为 $L$：\
  ![](https://cdn.luogu.com.cn/upload/image_hosting/lafk4cmc.png)\
  此时 $2$ 是否等于 $4$ 的反转未知，于是还是需要暴力扩展。
 
至此，Manacher 的流程已讲解完毕。但我们一定有一个疑问：算法中有这么多暴力扩展，为什么复杂度还是 $O(n)$ 呢？

### 时间复杂度

使 Manacher 复杂度正确的东西主要是这个 $R$：显然，它只增不减。但只有这一点还不够，我们需要说明每次操作要么是 $R$ 加一，要么复杂度为 $O(1)$。我们对于每种情况考虑：

- 若 $i>R$，显然扩展会使 $R$ 增加。

- 若 $i\le R$：前两种情况显然复杂度为 $O(1)$。对于第三种情况：若无法扩展，则复杂度为 $O(1)$；若可以扩展，则会使 $R$ 增加。

于是总复杂度为 $O(n)$。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[22000002],mi,r,an,le;
char s[11000002],t[22000002];
signed main(){
	ios::sync_with_stdio(0);
	scanf("%s",s+1),le=strlen(s+1);
	t[++n]='$',t[++n]='#';
	for(int i=1;i<=le;i++)
		t[++n]=s[i],t[++n]='#';
	t[++n]='!';
	for(int i=2;i<n;i++){
		if(i<=r)p[i]=min(p[2*mi-i],r-i+1);
		else p[i]=1;
		while(t[i-p[i]]==t[i+p[i]])p[i]++;
		if(i+p[i]>r)mi=i,r=i+p[i]-1;
		an=max(an,p[i]);
	}
    printf("%d",an-1);
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：3)

manacher 算法通常用来在 $O(n)$ 时间复杂度内求解字符串最长回文子串 / 以串内一点为中心的最长回文半径问题。

---

一些前置定义：

+ **回文串**：定义一个长度为 $n$ 下标从 $1$ 开始的字符串 $s$ 是回文的，当且仅当 $\forall i\in[1,n]\cap\mathbb{N_+},s_i=s_{n-i+1}$。
+ **回文子串**：定义串 $t$ 是串 $s$ 的回文子串，当且仅当 $t$ 为回文串，且 $t$ 为 $s$ 的子串。
+ **最长回文子串**：定义一个长度为 $n$ 的字符串的最长回文子串，为其所有回文子串中长度最长的子串。
+ **最长回文半径**：定义一个长度为 $n$ 下标从 $1$ 开始的字符串 $s$ 在 $i$ 位置的最长回文半径 $j$ 是最大的整数满足 $\forall k\in[0,j),(s_{i+k}=s_{i-k})\land (i+k\le n)\land (i-k\ge 1)$。
+ **回文中心**：定义一个长度为 $n$ 下标从 $1$ 开始的回文串 $s$ 的回文中心：若 $n$ 为奇数则 $s$ 串的回文中心位于 $\frac{n+1}2$，否则回文中心位于 $\frac n2$ 和 $\frac n2+1$ 两位置之间。

------

问题求解：

> 给定一个长度为 $n$ 的字符串 $s$，求其最长回文子串的长度。
>
> Data Range: $1\le n\le 1.1\times 10^7$。

算法流程：

这里认为 $s$ 串下标从 $1$ 开始。

设 $p_i$ 表示 $i$ 位置处最长回文半径的长度。由于存在长度为偶数的回文串，此时回文中心位于两字符之间，为了方便处理，在这里对原字符串进行一次特殊的操作：即将原字符串中任意两字符之间，以及头尾两处均添加一个特殊字符（例如：`$`）。此时字符串长度由 $n$ 变为 $2n+1$，原来的每一个长度为偶数的回文串均变为由特殊字符为回文中心的回文串。例如：串 `abcbaab` 变为 `$a$b$c$b$a$a$b$`，此时串 `abcba` 变为 `$a$b$c$b$a$`，以 `c` 字符为回文中心；串 `baab` 变为 `$b$a$a$b$`，以两个 `a` 字符之间的 `$` 为回文中心。

然后考虑求解 $p$ 数组。首先思考怎么暴力求解。很容易想到对于字符串的每一个 $i$ 都暴力向左向右扩展直到左右两侧的字符不相同为止。期望跑的很快，但是很明显可以被形如 `aa....a` 的字符串给卡到 $O(n^2)$。这样做很多判断的信息都被浪费掉重新又判断了一遍，因此考虑类似于 kmp，利用这些信息优化计算 $p$ 数组的时间复杂度。

从左往右按顺序依次枚举每一个 $i$。假设当前已经处理了 $p_1,p_2,\ldots,p_{i-1}$ 要计算 $p_i$ 的值。我们记录 `r` 和 `nowmid` 两个信息分别表示以 $1\sim i-1$ 为回文中心时，回文中心可以覆盖到的下标最大的点下标最大是多少（`r`）以及此时回文中心的下标是多少（`nowmid`）。

然后分类讨论 $i$ 和 `r` 之间的关系：

**1. $i>r$**

直接暴力扩展更新答案即可。

**2. $i\le r$**

考虑如何快速的计算 $p_i$ 的值：此时已经计算得到存在一个以 `nowmid` 为回文中心的回文串，其回文半径覆盖的下标最大的点下标为 `r`，那么同样可以直接计算出覆盖的下标最小的点下标为 `l`。此时容易对称的计算 $i$ 关于 `nowmid` 对称的点下标为 $j$，则此时已经计算出以 $j$ 点为中心的回文半径长度，直接用 $p_j$ 的值更新 $p_i$ 即可。

但是若此时 $p_i$ 的值超过了当前回文串半径 `r`，那么超过的部分由于不在回文串内不能保证回文，因此只能将 $p_i$ 更新到 $r-i+1$，然后继续暴力扩展。同样的，若 $p_i$ 的值恰好为 $r-i+1$，那么也不能保证为最长回文串，也需要继续暴力扩展。有一个简单的写法是更新完 $p_i$ 的值之后直接暴力扩展（容易发现剩下不能扩展的情况暴力扩展的时间复杂度为 $O(1)$）。计算完 $p_i$ 后，更新 `r` 和 `nowmid` 的值即可。

代码实现：

```cpp
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
        t[i * 2] = s[i], t[i * 2 + 1] = '$';
    t[1] = '$';
    n = n * 2 + 1;
    for (int i = 1; i <= n; ++i)
        s[i] = t[i];
    int r = 0, nowmid = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i < r)
            p[i] = min(p[2 * nowmid - i], r - i);
        else
            p[i] = 1;
        while (i + p[i] <= n && i - p[i] >= 1 && s[i + p[i]] == s[i - p[i]])
            ++p[i];
        if (p[i] + i > r)
            r = i + p[i], nowmid = i;
    }
    cout << *max_element(p + 1, p + n + 1) - 1 << '\n';
    return 0;
}
```

时间复杂度分析：

很显然除了暴力更新的部分以外时间复杂度都是 $O(n)$，而暴力更新部分最多扩展 $n$ 次（扩展之后 `r` 会变大，但是 `r` 不会变小，最多从 $1$ 变到 $n$），因此总时间复杂度为 $O(n)$。空间复杂度也为 $O(n)$，可以通过。

---

## 作者：wangkelin123 (赞：2)

## 题目简介
求字符串中最长回文串的长度。
## 题目分析
### 算法介绍
‌Manacher 算法（马拉车算法）‌是一种用于在线性时间内找到字符串中最长回文子串的高效算法。该算法由 Glenn Manacher 在 1975 年提出，其核心思想是利用已经计算出的回文信息来减少重复计算，通过中心扩散法和对称性质优化算法效率‌。
### 算法步骤
1. 预处理‌：在原字符串的每个字符之间插入一个特殊字符（如 `#`），并在字符串的开始和结束处各添加一个特殊字符。这样做是为了避免边界问题，并使得回文串既可以是奇数长度也可以是偶数长度。

2. 定义数组 $pal$：定义一个数组 $pal$，其中 $pal_i$ 表示以第 $i$ 个字符为中心的最大回文半径（不包括中心字符本身）。

3. 动态规划‌：初始化两个变量 $pos$ 和 $maxr$，其中 $pos$ 表示当前回文中心的位置，$maxr$ 表示当前回文右边界的位置。遍历预处理后的字符串，对于每个位置 $i$：
$$pal_i = \begin{cases} \min(pal_{2\times pos-i},maxr-i+1) & i<maxr \\ 1 & i\ge maxr \end{cases}$$
4. 扩展回文串：左边为 $a_{i-pal_i}$（$a$ 为预处理后的字符串），右边为 $a_{i+pal_i}$，判断是否相等。若相等，则 $pal_i\gets pal_i+1$，否则跳出 while 循环。

5. 更新 $pos$ 和 $maxr$ 的值，如果 $i + pal_i > maxr$，则 $maxr\gets i+pal[i]-1$，且 $pos\gets i$。

6. 查找最长回文子串‌：在遍历过程中，记录下最大的 $pal_i$ 值及其对应的索引，最后根据这个索引找到最长回文子串‌。
### 正确性证明
- 预处理。

![](https://cdn.luogu.com.cn/upload/image_hosting/wf55hrfi.png)

我们可以发现，用这种方法使得偶数长度的有了中点，而奇数长度的还是有中点。

**但这是为什么呢？**

由图可知，`#` 的数量总是比字母的数量多 $1$，于是就有 $len=x+(x+1)=2x+1$（$x$ 为字母的长度），所以总长 $len$ 必为奇数，也就都有中点了。
- 主要函数部分

核心算法：
![](https://cdn.luogu.com.cn/upload/image_hosting/ob7v2wto.png)
但如果这个（图片中）大回文串前**还有一个** $c$，那么前面一个回文串会比后面那个长度多 $2$，但**这种情况只会出现在大回文串的开头与结尾**，故仅需使用右端点减本回文串中点（这里所有记录的都是回文串**半径**长）即可。

大前提：此回文串包括在大回文串中。

若不是，即可先设半径为 $1$，再扩大回文串规模，然后更新右端点与中点。

最后更新**最大回文串长度**的值。此时我们会惊奇地发现，当前回文串长度正好等于**加工后的回文串半径减一**（如图）。
![](https://cdn.luogu.com.cn/upload/image_hosting/b8w5zjja.png)

最后一问：为何时间复杂度不是 $O(N^2)$？

因为每次执行 while 循环时右端点必会更新，在回文字符串内扩展是不可能的（之前必已赋值完毕，不可能遗漏）。

最终时间复杂度 $O(N)$。

注意：因为 $pal$ 数组是存加工了的字符串，所以**数组长度乘二**。

### 主要代码实现
- 预处理
```cpp
string Get(string s){//用于加工字符串
	string t="$#";
	for(int i=0;i<s.size();i++){
		t+=s[i];
		t+="#";//每两个字符间都嵌一个‘#’
	}
	t+="@";//左右两边都再加一个不相同的字符
	return t;
}
```
- 主要函数部分
```cpp
void Mana(string s){
	s=Get(s);//调用 Get 加工
	int len=s.size();
	int maxr=0,pos=0;//maxr 表右端点,pos 表中点（最右边回文字符串的）
	for(int i=1;i<len;i++){
		if(i<maxr) pal[i]=min(pal[2*pos-i],1LL*(maxr-i+1));
		else pal[i]=1;//赋初值
		while(s[i+pal[i]]==s[i-pal[i]]) pal[i]++;//扩展
		if(pal[i]+i-1>=maxr){
			maxr=pal[i]+i-1;
			pos=i;
		}//更新
		if(ans<pal[i]-1) ans=pal[i]-1;//记录答案
	}
}
```
### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1.1e7+5;
string s;
ll pal[2*N],ans;
string Get(string s){
	string t="$#";
	for(int i=0;i<s.size();i++){
		t+=s[i];
		t+="#";
	}
	t+="@";
	return t;
}
void Mana(string s){
	s=Get(s);
	int len=s.size();
	int maxr=0,pos=0;
	for(int i=1;i<len;i++){
		if(i<maxr) pal[i]=min(pal[2*pos-i],1LL*(maxr-i+1));
		else pal[i]=1;
		while(s[i+pal[i]]==s[i-pal[i]]) pal[i]++;
		if(pal[i]+i-1>=maxr){
			maxr=pal[i]+i-1;
			pos=i;
		}
		if(ans<pal[i]-1) ans=pal[i]-1;
	}
}
int main(){
	cin>>s;
	Mana(s);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：__xxy_free_ioi__ (赞：2)

# 题解：P3805 【模板】manacher

~~真是有意思的算法捏，呵呵~~

## 解法

很容易能想到 $O(n^2)$ 的算法，就是选取一个位置 $i$ 向两边扩展即可。

首先，我们需要对数据做一个小小的改变，因为一个回文串的对称中心不一定是整数，所以我们要想办法将其变成整数。所以，我们可以把它的每两个字符中间加上一个相同的特殊字符（这里指原串中不会出现的字符），例如，$aaa$ 可以变成 $aAaAa$，这样，对称中心就一定是在一个整数位上了。但是，我们还要处理一个边界问题，解决方法是将原串前加一个特殊字符，比如，$aaa$ 要变成 $BaAaAa$，这个其实是为了防止越界。

为了方便，我们设 $rad_i$ 为以 $i$ 为**对称中心的最长回文半径**，$l$、$r$ 和 $mid$ 分别为已知的最靠右的回文串的左右边界与它的对称中心。

我们发现，在 $O(n^2)$ 的算法中，有许多扩展是**不必要**的，对此，我们开始分类讨论。

### 情况 1：$i \le r$

我们设 $j$ 为 $i$ 在对称中心为 $mid$ 的情况下的对称点。把字符串位置设想成一个数轴，那么 $(i+j) \div 2 = mid$，所以 $j$ 的位置为 $2 \times mid - i$。

因为 $[l,r]$ 是回文的，所以区间 $[j-rad_j,j+rad_j]$ 和区间 $[i-rad_i,i+rad_i]$ 是相等的，又因为 $[j-rad_j,j+rad_j]$ 是回文串，所以 $[i-rad_i,i+rad_i]$ 是回文串，所以，我们知道，$rad_i$ 是可以取到 $rad_j$ 的。但是，这一切的前提都建立在 $i+rad_j \le r$ 的前提下的，若 $i+rad_j > r$，那么，我们就不能保证 $rad_i = rad_j$，所以只能取到 $r-i+1$。

综上，$rad_i= \min(rad_j, r-i+1)$。然后，暴力扩展即可。

### 情况 2：$i > r$

这种情况我们只能由 $rad_i = 1$ 开始一步步扩展。

由此，我们就以 $O(n)$ 的复杂度完成了题目。

### 时间复杂度

让我们来看看它的时间复杂度为啥是 $O(n)$ 的（相信这个地方难倒了许多人）。但实际上也很好想，因为：

1. **暴力扩展次数有限**：$r$ 只能被扩展 $n$ 次。
2. **非暴力扩展复杂度低**：只有 $O(1)$ 的复杂度。

所以，总的复杂度是 $O(n)+O(n)=O(n)$ 的。

## 代码

```
#include <bits/stdc++.h>

using namespace std;

const int N = 1.1e7 + 5;

int n, res;
int rad[2 * N];
char s[2 * N], c;

void read() {
	s[0] = 'B';
	while (cin >> c) s[++n] = 'A', s[++n] = c;
	s[++n] = 'A';
}

int main() {
	read();
	int mid = 0, r = 0;
	for (int i = 1; i <= n; i++) {
        int j = 2 * mid - i;
		if (r < i) rad[i] = 1;
		else rad[i] = min(rad[j], r - i + 1);
		while (s[i - rad[i]] == s[i + rad[i]]) rad[i]++;
		res = max(res, rad[i] - 1);
		if (i + rad[i] - 1 > r) {
			r = i + rad[i] - 1;
			mid = i;
		}
	}
	cout << res;
    return 0;
}
```

---

## 作者：Astraios (赞：2)

# 题解

## 【模板】manacher 算法

## 算法简介

Manacher 算法，又称为马拉车算法，是一种用于查找字符串中最长回文子串的高效算法。它由 Manacher 在 1975 年提出，能够在 $O(N)$ 的时间复杂度和空间复杂度内解决问题。

## 算法思想

算法的核心在于通过特殊字符的插入，将偶数长度和奇数长度的回文子串统一处理。

那么，推导与实现过程如下：

首先，有一个小技巧：

对于字符串 $s$，用一个 $s$ 中不存在的字符把 $s$ 中的字符隔开：

例如 $\texttt {aba} \rightarrow \texttt {￥a￥b￥a￥}$。

原串最长回文子串长度等于新串最长回文子串长度的一半。

PS：接下来出现的 $s$ 若无特殊说明均为插入字符后得到的新串。

##### 算法详解：

manacher 算法需要维护[最大回文半径](https://cn.bing.com/search?q=%E6%9C%80%E5%A4%A7%E5%9B%9E%E6%96%87%E5%8D%8A%E5%BE%84\&form=ANNTH1\&refig=6816ec9f4db642c3b1b6a65f0f93a410\&pc=CNNDDB)。

最大回文半径：从 $s_i$ 出发能拓展的字符数，记作：$p_i$。

我们从左向右依次计算 $p_i$。\
假设要计算 $p_i$，则此时应已经计算了 $p_1,p_2,p_3,\dots,p_{i-1}$。\
为了计算 $p_i$，在枚举 $i$ 的过程中，我们要维护使得 $R$ 最大的区间 $[L,R]$。

其中 $\begin{cases}
 L=M-p_M+1 & (M<i) \\
 R=M+p_M-1 & (M<i)
\end{cases}$

接下来开始分类讨论：

$i>R$ 时，令 $p_i=1$，并暴力向两边扩展。

![](https://cdn.luogu.com.cn/upload/image_hosting/xhupfzr4.png)

$i \le R$ 时，找到 $i$ 关于 $M$ 的对称点 $k$：

若 $p_k$ 对应的回文区间不包含 $L$，令 $p_i=p_{2M-i}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3wnljgr1.png)

若 $p_k$ 对应的回文区间包含 $L$，令 $p_i=p_{R-i+1}$ 并继续暴力扩展。

![](https://cdn.luogu.com.cn/upload/image_hosting/1xji6bcm.png)

再看回 $p_k$ 对应的回文区间不包含 $L$ 的情况：

若 $p_k$ 对应的回文区间不包含 $L$，则 $L<k-p_k+1$，又 $L=2M-R$ 且 $k=2M-i$，则 $(2M-R)<(2M-i)-p_{2M-i}+1$，化简得 $p_{2M-i}<R-i+1$。

然后是 $p_k$ 对应的回文区间包含 $L$ 的情况：

若 $p_k$ 对应的回文区间包含 $L$，则 $L \ge k-p_k+1$，又 $L=2M-R$ 且 $k=2M-i$，则 $(2M-R) \ge (2M-i)-p_{2M-i}+1$，化简得 $p_{2M-i} \ge R-i+1$。

所以经过观察总结可得

$i>R$ 时，令 $p_i=1$，并暴力向两边扩展。

$i \le R$ 时，令 $p_i = \min (p_{2M-i},R-i+1)$，并暴力向两边扩展。

## 正确性证明

时间复杂度为何是 $O(N)$ 呢？

因为每次在更新右端点时，$i+p_i$ 必然会超过原来的且小于 $n$，即呈递增趋势，不会重复更新。所以最多只会更新 $O(N)$ 次，那么总的时间复杂度就是 $O(N)$ 了。

## Code

接下来就是最美的代码实现了！！！

算法部分：

```cpp
int manacher(string s)
{
	int M=0,R=0;
	for(int i=1;i<=n;i++)
	{
		if(i>R) p[i]=1;
		else p[i]=min(p[2*M-i],R-i+1);//分类讨论
		while(i-p[i]>=1&&i+p[i]<=n&&s[i-p[i]]==s[i+p[i]]) p[i]++;//暴力拓展
		if(i+p[i]-1>R) M=i,R=i+p[i]-1;//更新
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,p[i]);
	return ans-1;
}
```

本题代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s,S;
int p[30000005],n;
int manacher(string s)
{
	int M=0,R=0;
	for(int i=1;i<=n;i++)
	{
		if(i>R) p[i]=1;
		else p[i]=min(p[2*M-i],R-i+1);
		while(i-p[i]>=1&&i+p[i]<=n&&s[i-p[i]]==s[i+p[i]]) p[i]++;
		if(i+p[i]-1>R) M=i,R=i+p[i]-1;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,p[i]);
	return ans-1;
}
signed main()
{
	cin>>S;
	s+=' ';
	for(int i=0;i<S.size();i++) s+='$',s+=S[i];
	s+='$';
	n=s.size()-1;
	cout<<manacher(s);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：2)

[link](https://www.luogu.com.cn/blog/556362/post-xue-xi-bi-ji-manacher)

作用是找到字符串的最长回文子串。

## 算法介绍

### 处理

注意回文串有下列情况：

- `aba`：中间是 `b`，从中间的 `b` 向两侧扩展。

- `abba`：中间是 `bb`，从中间的 `bb` 向两侧扩展。

注意这两种情况是本质上不同的情况。

怎么办呢？

考虑在 `bb` 中间插入一个异于字符串中字符的字符，比如 `#`，这样第二种情况就是从 `#` 开始扩展的。

观察发现：这种情况下回文子串一定是以 `#` 开头和结尾的，那么原串字符的数量就是求得字符的数量除以 $2$ 下取整。

### 求解

[板子](https://www.luogu.com.cn/problem/P3805)

上面讲了处理技术，接下来讲一讲求解技术。

可以考虑 $O(n)$ 枚举中点，然后 $O(n)$ 向两边扩展。时间复杂度 $O(n^2)$。

然后我们发现这个向两边扩展是有单调性的，所以可以考虑二分，复杂度 $O(n\log n)$。

但是模板题是 $10^7$ 级别的，所以我们需要 $O(n)$，还不够！

***

考虑继续优化。

下文记从 $i$ 扩展出来单边最大长度为 $p_i$，即回文串为 $[i-p_i,i+p_i]$。

注意上述做法每个位置的求解之间都是独立的，我们可以考虑用 $i$ 前面已经求出来的信息求解 $i$。

- 如果前面 $\nexists j,i\in[j-p_j,j+p_j]$。那么前面的答案都对后面的求解没有帮助，此时 $i$ 独立求解。

- 如果前面 $\exists j,i\in[j-p_j,j+p_j]$。那么前面的答案可以对后面的有一定帮助。贪心地，要让影响最大，显然应该是取已经求解好的 $j$ 中 $p_j+j$ 最大的那个 $j$。

记 $i$ 关于 $j$ 的对称点为 $i'$，对 $i'$ 进行讨论：

- $i'-p_{i'}>j-p_j$：即此时 $i'$ 的区间完全被 $j$ 包含，并且没有覆盖到端点，那么有 $s_{i-p_i-1}=s_{i'+p_{i'}+1}\ne s_{i'-p_{i'}-1}=s_{i+p_i+1}$。那么 $p_i$ 只能等于 $p_{i'}$，不能继续向外扩展。

- $i'-p_{i'}\le j-p_j$：上面的证明已经发现了， $i'-p_{i'}-1$ 必须在 $j$ 的区间之内，否则的话 $i$ 的等号就不能传递给 $i'$，所以此时 $p_i\gets j+p_j-i$，然后再往两边扩展。

## 正确性证明

注意此时对每个 $i$ 都存在往两边扩展的可能。那为什么复杂度是正确的呢？

注意到前面提到过的 $\max\{j+p_j\}$ 了吗？为什么一定要强调 $\max$ 呢？

注意到 $\max$ 肯定是依次递增的，而且 $\le n$，所以 $\max$ 只会更新 $O(n)$ 次。而且每次 $i$ 向外扩展都会超出 $\max\{j+p_j\}$ 的范围，会更新这个 $\max$，所以总的复杂度其实是 $O(n)$ 的。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=2.2e7+5;
string s,t;
int n,R,Rpos,p[N],ans=0;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>s,n=s.size()*2+1;
	t+=' ';
	for(auto c:s) t+='#',t+=c;
	t+='#';
	for(int i=1;i<=n;++i){
		if(i<=R) p[i]=min(R-i,p[2*Rpos-i]);
		else p[i]=0;
		while(i+p[i]+1<=n&&i-p[i]-1>=1&&t[i+p[i]+1]==t[i-p[i]-1]) ++p[i];
		if(i+p[i]>R) R=i+p[i],Rpos=i;
	}
	for(int i=1;i<=n;++i) ans=max(ans,p[i]);
	cout<<ans<<endl;
	return 0;
}
```

## 例题

- [拉拉队排练](https://www.luogu.com.cn/problem/P1659)

题意：求原串中最长的 $k$ 个奇数回文串的长度的积（$\bmod 19930726$）。

出题人已经很良心了，字符串都强制是奇数了，所以不需要加 `#`。

观察到回文串相关，所以我们先求出 $p$。

$k$ 是 $10^9$，所以不能暴力。

可以考虑贪心，把 $p$ 降序排序，这样处理的时候就可以先把 $[1,i-1]$ 的 $p$ 全部剃成 $p_i$。这个时候 $p_i$ 就有 $i$ 个，所以说就在把 $p_i$ 剃成 $p_{i+1}$ 的时候每次乘上 $p_i^i$ 即可。

$p=0$ 也要计算！

- [最长双回文串](https://www.luogu.com.cn/problem/P4555)

题意：“双回文串”定义为由两个回文串拼成的字符串，求最长双回文串。

manacher 之后求出 $p$，注意两个位置 $i,j(i<j)$ 合并当且仅当 $j-p_{j}\le i+p_i$，此时双回文串的区间为 $[i-p_i,j+(j-(i+p_i+1))]$，区间长度就是 $j+(j-(i+p_i+1))-(i-p_i)+1=2(j-i)$。

因为还要除以 $2$，所以其实就是 $j-i$。那么我们倒枚，把 $j-p_j$ 放到值域树状数组里面，每次查询 $\le i+p_i$ 中的 $j$ 的最大值。

- [EPALIN](https://www.luogu.com.cn/problem/SP4103)

题意：在字符串末尾添加最少的字符使得原串变成回文串。

问题等价于求原串的最长后缀回文串。

于是 manacher 求出所有的 $i+p_i=n$ 的东西中 $i-p_i$ 的最小值即可。

所以为什么是紫题？

- [神奇项链](https://new.bzoj.org:88/p/P3790)

题意：可以合并两个回文串，最长公共前后缀会被删去，求得到目标串的最少合并次数。

挺好的一道题目，区间覆盖转化确实挺妙。

manacher 之后对 $[i-p_i,i+p_i]$ 跑个区间覆盖即可，这个玩意可以贪心处理。

注意转化后是区间覆盖，原题是合并，所以答案应该是区间数量 $-1$。

---

## 作者：Motonic_queues (赞：2)

## 算法简介
Manacher 在 $1975$ 年发明了一个算法，可以在 $O(n)$ 的时间复杂度内寻找一个字符串的所有回文串，因此这种算法以他的名字冠名（中文谐音马拉车）。

## 算法思想
主要是靠回文串的“对称”性质，优化大量不必要的计算，先来看个例子：  

对于一个字符串，如果我们要找到它的全部长度为奇数的回文字串，可能会用这样的朴素算法：  
1. 遍历字符串   
2. 对于当前位置 $i$，以其为对称轴向两侧“扩展”，像这样：
```cpp
int cnt=1;
while(i-cnt&&s[i+cnt]==s[i-cnt])++cnt;
```
这样可以确定：以 $i$ 为中心的最长的回文字串的“半径”为 `cnt`。我们称这个值为 _回文半径_，用一个 `p` 数组存下来。   
但不难看出来，面对极端情况（字符串只含一种字符），复杂度为 $O(n^2)$。  

怎么优化呢？  
首先我们可以注意到：因为我们是按顺序遍历的，也就是说，**一个位置的答案确定好之后就不会发生改变了**。  
考虑到这点，可能我们在优化时要尽可能利用过去得到的答案。  

那么如果我们正在考虑 $i$，在什么情况下，计算 $p_i$ 要用到 $p_j$ 的值呢？  
这时我们就能注意到了：如果 $i$ 和 $j$ 是一个回文串 $s^*$ 中对称的位置，那么，以 $j$ 为中心的最长回文字串中**属于 $s^*$ 的部分**一定也属于以 $i$ 为中心的最长回文字串中，事实上，这正是 Manacher 的核心思路。  

关于实现方式，有一个巧妙的方法：因为这个优化只有在 $i$ 被一个回文字串包括时才有意义，所以我们只有维护“右端点最靠右的回文串”的必要，如此一来，我们就可以设计出下面的算法流程：  
1. 设 $C$ 为 $s^*$ 的中心位置，$R$ 为 $s^*$ 的回文半径。初始化两个为 $0$。
2. 遍历字符串
3. 找到 $i$ 在 $s^*$ 中的对称位置 $2\times C-i$，我们称之为 $i_m$。
4. 倘若 $i_m$ 有意义（即大于 $0$ ），将 $p_i$ 赋成 $\min\{p_{i_m},R-i\}$。
5. 直接从 $p_i$ 开始扩展。
6. 如果扩展完得到的 $i+p_i$ 大于 $R$，用 $i$ 和 $p_i$ 替换 $C$ 和 $R$。

这个时候可能会有点怪，因为还是扩展了，但让我们仔细思考一下什么时候才会扩展。  
很显然，如果扩展完没有更新 $C+R$，事实上，根本就不会发生扩展。  
反证法：  
如果能扩展，且最终没有更新 $R$，则至少以 $i$ 为中心的最长回文字串会包含 $i-p_{i_m}-1$ 和 $i+p_{i_m}+1$。  
而这两个字符分别与 $i_m+1$ 和 $i_m-1$ 相等，如果前二者是相等的，则后二者也相等，但以 $i_m$ 为中心的最长回文字串没有包含后二者，出现矛盾，假设不成立。  

这样一来，每次扩展一定会把 $C+R$ 往前推，但这个值很显然不会超过 $n$，所以扩展的次数也不会超过 $n$ 次，再算上遍历，总的复杂度还是 $O(n)$。

如果你按照这个思路去写代码并提交，肯定无法 AC，因为我最开始的例子就只考虑的长度为奇数的回文子串，不过，要考虑长度为偶数的情况，有一个巧妙的方式：  
在每个字符之间插入一个 _罕见的_ 字符，比如 “#”，也就是代表两两字符之间的空位，再加入一头一尾两个不同的哨兵字符，就能处理全部的情况了（而且这样得到的最大回文半径直接就是真实的回文长度）。

## Talk is cheap,show me the code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=3e7+5;
string s,t;
int l;
int p[N],C,R,ans;

void dl(){    //调整字符串
	t="^#";
	for(int i=0;i<l;i++)t+=s[i],t+='#';
	t+='$';
	l=t.size();
}

void solve(){  //获得 p 数组
	for(int i=1;i<l-1;i++){
		int mirri=2*C-i;
		if(i<R)p[i]=max(0,min(R-i,p[mirri]));
		int cnt=0;
		while(t[i+p[i]+1]==t[i-p[i]-1])p[i]++,cnt++;
		if(i+p[i]>R)C=i,R=p[i]+i;
		ans=max(ans,p[i]);
	}
}

int main(){
	cin>>s;
	l=s.size();
	dl();
	solve();
	cout<<ans;
	return 0;
}
```

---

