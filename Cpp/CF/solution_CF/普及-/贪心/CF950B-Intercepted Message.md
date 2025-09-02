# Intercepted Message

## 题目描述

Hacker Zhorik wants to decipher two secret messages he intercepted yesterday. Yeah message is a sequence of encrypted blocks, each of them consists of several bytes of information.

Zhorik knows that each of the messages is an archive containing one or more files. Zhorik knows how each of these archives was transferred through the network: if an archive consists of $ k $ files of sizes $ l_{1},l_{2},...,l_{k} $ bytes, then the $ i $ -th file is split to one or more blocks $ b_{i,1},b_{i,2},...,b_{i,mi} $ (here the total length of the blocks $ b_{i,1}+b_{i,2}+...+b_{i,mi} $ is equal to the length of the file $ l_{i} $ ), and after that all blocks are transferred through the network, maintaining the order of files in the archive.

Zhorik thinks that the two messages contain the same archive, because their total lengths are equal. However, each file can be split in blocks in different ways in the two messages.

You are given the lengths of blocks in each of the two messages. Help Zhorik to determine what is the maximum number of files could be in the archive, if the Zhorik's assumption is correct.

## 说明/提示

In the first example the maximum number of files in the archive is 3. For example, it is possible that in the archive are three files of sizes $ 2+5=7 $ , $ 15=3+1+11=8+2+4+1 $ and $ 4+4=8 $ .

In the second example it is possible that the archive contains two files of sizes $ 1 $ and $ 110=10+100=100+10 $ . Note that the order of files is kept while transferring archives through the network, so we can't say that there are three files of sizes $ 1 $ , $ 10 $ and $ 100 $ .

In the third example the only possibility is that the archive contains a single file of size $ 4 $ .

## 样例 #1

### 输入

```
7 6
2 5 3 1 11 4 4
7 8 2 4 1 8
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3
1 10 100
1 100 10
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 4
4
1 1 1 1
```

### 输出

```
1
```

# 题解

## 作者：Kdlyh (赞：3)

## 维护两个前缀和+双指针查找即可 
这道题我做的时候看的标签居然是贪心。。。也是无语了(希望管理大大改下标$签）
1. 根据题意得，既然想要求最多可以分成几段每一段满足第一个数组的第q段元素之和,第二个数组的第q段元素之和相等。那么首先需要维护一个前缀和来存条件中的q段元素之和。
1. 然后在用四个指针，$l_i$和$i$ ：$i$指向第一个数组的从$l_i$开始以$i$结尾的前缀和，$l_j$和$j$同理。

1. 然后$i$和$j$从1开始每次查找，如果第一个数组的$i-l_i$的前缀和$=$第二个数组的$j-lj$的前缀和，就满足了条件，答案$+1$。如果$i-l_i$的前缀和$<j-l_j$的前缀和，那就让$i++$，让$i+1-l_i$的前缀和再与$j-l_j$的前缀和比较，$j-l_j$的前缀和$<i-l_i$的前缀和的情况同理。

大概思路就是这些了，下面给出代码实现方便理解~~请忽略快读和快输~~
```cpp
#include<cstdio>
#include<cctype>
inline int max(int a,int b){
    return a>b?a:b;
}
inline int read(int &x){
    x=0;char ch=0;int sign=1;
    do{ch=getchar();if(ch=='-')sign=-1;}while(!isdigit(ch));
    do{x=x*10+ch-48;ch=getchar();}while(isdigit(ch));
    x*=sign;
}
inline void out(int x){
    if(x<0){
        x=-x;
        putchar('-');
    }
    if(x>9){
        out(x/10);
    }
    putchar(x%10+'0');
}
int n,m,a1[1000010],a2[1000010],dp1[1000010],dp2[1000010];
int main(){
    read(n);read(m);
    for(register int i=1;i<=n;i++){
        read(a1[i]);
        if(i==1)dp1[1]=a1[1];
        else dp1[i]=dp1[i-1]+a1[i];
    }
    for(register int i=1;i<=m;i++){
        read(a2[i]);
        if(i==1)dp2[1]=a2[1];
        else dp2[i]=dp2[i-1]+a2[i];
    }
    int i=1,j=1,li=0,lj=0,ans=0;
    while(i<=n&&j<=m){
        if(i==li)i=li+1;
        if(j==lj)j=lj+1;
        if(dp1[i]-dp1[li]==dp2[j]-dp2[lj]){
            ans++;li=i,lj=j;
        }else{
            if(dp1[i]-dp1[li]>dp2[j]-dp2[lj]){
                j++;
            }
            if(dp1[i]-dp1[li]<dp2[j]-dp2[lj]){
                i++;
            }
        }
    }
    out(ans-1);
    return 0;
}
```

---

## 作者：信守天下 (赞：2)

## [CF传送门](http://codeforces.com/contest/950/problem/B)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF950B)
## 想法:贪心
因为如果他们第$f$段相等，设$x$ , $y$为第$f$段结束时的下标

则$a[1]$ ~ $a[x]$ = $b[1]$ ~ $b[y]$

因为在第$f$段前的段都相等，第$f$段也相等

所以要找相等段，只需要找到两个下标$x$和$y$，使$a[1]$ ~ $a[x]$ = $b[1]$ ~ $b[y]$

$a[1]$ ~ $a[x]$ 和 $b[1]$ ~ $b[y]$都是数组中连续的一段，所以可以用前缀和优化
## $code$
~~~cpp
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
int a[kMaxN], b[kMaxN], n, m, ans, j = 1;
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];       //第一个数组
    a[i] += a[i - 1];  //第一个前缀和
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];       //第二个数组
    b[i] += b[i - 1];  //第二个前缀和
  }
  for (int i = 1; i <= n; i++) {     //第一个数组的下标
    while (j <= m && a[i] > b[j]) {  //没有找到在第二个数组匹配的下标
      j++;                           //下标移动
    }
    ans += (a[i] == b[j] /*两端相等*/ && j <= m /*在数组中*/);
    /*两个都成立时表达式会返回true,否则返回false,运算时会自动类型转换成1和0*/
  }
  cout << ans;
  return 0;
}
~~~

---

## 作者：某某x (赞：2)

貌似楼上都是用双指针，然后本菜鸡就写一个不用双指针的贪心吧。

假设它们的第q段相等，那么显然前q段都是相等的。假设x，y分别是a和b第q段的最后一个元素的下标，那么a[1] + ..+ a[x] == b[1] + ...+ b[y]。因为每一段都是连续的，所以前缀和肯定是相等的。

得到前面的东西之后，我们其实就可以对整体来考虑啦，你要找的第q段不就是相当于找两个下标x，y，让a[x] == b[y]吗。

可能代码好理解一点0.0，表达水平比较差0.0

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _rep(n,m,i) for (register int i = (n); i <= (m); ++i)
const int N = 1e5+5;
int a[N], b[N], n, m;
int main() {
  scanf("%d %d", &n, &m);
  _rep(1, n, i) scanf("%d", a+i), a[i] += a[i-1];
  _rep(1, m, i) scanf("%d", b+i), b[i] += b[i-1];
  int j = 1, ans = 0;
  _rep(1, n, i) {
    while(j <= m && a[i] > b[j]) j++;//a[i]>b[j],那我们就让j增加，这样才可能让a[i]==b[j]
    ans += (a[i]==b[j]&&j<=m);//判断是否相等
  }
  cout << ans << endl;
}
```


---

## 作者：Wi_Fi (赞：1)

分类说要贪心、前缀和，可是似乎只需要双指针？

基本思路：使用双指针 $x$ 和 $y$，并分别使用变量 $s1$ 和 $s2$ 统计数组累加和。

- 如果 $s1 < s2$，那么将 $x$ 右移，将 $s1$ 的值加上 $a_x$，使得 $s1$ 和 $s2$ 更接近。

- 同理，如果 $s1 > s2$，那么将 $y$ 右移，将 $s2$ 的值加上 $a_y$，使得 $s1$ 和 $s2$ 更接近。

- 如果 $s1 = s2$，那么找到了符合题目描述的区间，则将答案加 $1$，将 $x$ 和 $y$ 均右移，将 $s1$ 的值加上 $a_x$，将 $s2$ 的值加上 $a_y$，寻找下一个符合题目描述的区间。

容易写出代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
int a[N],b[N],i,n,m,x=1,y=1,s1,s2,ans;
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=m;i++)cin>>b[i];
	while(x<=n&&y<=m)
	{
		if(s1==0&&s2==0)s1+=a[x],s2+=b[y];
		if(s1==s2)ans++,x++,y++,s1+=a[x],s2+=b[y];
		if(s1<s2)x++,s1+=a[x];
		if(s1>s2)y++,s2+=b[y];
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：fls233666 (赞：0)

首先可以考虑**贪心**算法。

可以用两个指针同时扫两个数组。我们记此时两个数组的数字和分别为 $s_a$ 和 $s_b$，有如下操作：

1. 如果 $s_a<s_b$，扫数组 $a$ 的指针移动，让 $s_a$ 增加；
2. 如果 $s_a>s_b$，扫数组 $b$ 的指针移动，让 $s_b$ 增加；
3. 如果 $s_a=s_b$，找到一个划分点，答案增加 $1$，把 $s_a$ 和 $s_b$ 清空，两个指针同时移动，加入新的值。

可以证明，以上的贪心思路是正确的。

于是剩下的就是代码实现的问题了，下面是代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;
const int mxn = 1e5+5;
int n,m,a[mxn],b[mxn],cnt,s_a,s_b;
int main(){

	scanf("%d%d",&n,&m);
	for(rgt i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(rgt i=1;i<=m;i++)
		scanf("%d",&b[i]);
        //读入数据
        
	int ia=1,ib=1;
	s_a=a[1];
	s_b=b[1];
        //初始化双指针和s_a,s_b
    
	while(ia<=n||ib<=m){
		if(s_a>s_b){
			ib++;
			s_b+=b[ib]; 
		} 
		if(s_a<s_b){
			ia++;
			s_a+=a[ia];
		}
		if(s_a==s_b){
			cnt++;
			ia++;
			ib++;
			s_a=a[ia];
			s_b=b[ib];
		}
	}   //依照上述测量贪心解决问题
    
	printf("%d",cnt);  //输出答案
	return 0;
}
```


---

## 作者：Arcturus1350 (赞：0)

先吐槽一番：本宝宝好久没写过题解了。。。
首先我们想一个贪心策咯。
就是我们预处理出前缀和，然后一边扫过去，记录一个l1,l2和一个n1,n2。
分别表示我们现在第一个数组切到l1,上一次切是在n1处。l2,n2是表示第二个数组。
如果$ans1[l1]-ans1[n1]$ $=$ $ans2[l2]-ans2[n2]$ 就切一刀。（具体见代码）。
否则，如果$ans1[l1]-ans1[n1]$ $>$ $ans2[l2]-ans2[n2]$ 就把l2++。反之，l1++
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int m,n;//长度
int x[1000010];
int y[1000010];//储存序列
int anx[1000010];//前缀和
int any[1000010];
int l1=1,n1;//如上所说，
int l2=1,n2;//初始化，l1,l2均为一。n1,n2因为没切过，所以均为0；
int ans;//记录答案
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x[i]);
		anx[i]=anx[i-1]+x[i];
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&y[i]);
		any[i]=any[i-1]+y[i];
	}//输入并处理前缀和。
	while(l1<=n&&l2<=m)//判断有没有切完整个序列。
	{
//		printf("%d %d %d %d %d %d\n",l1,n1,l2,n2,(anx[l1]-anx[n1]),(any[l2]-any[n2]));
		if((anx[l1]-anx[n1])>(any[l2]-any[n2])) l2++;
		else if((anx[l1]-anx[n1])<(any[l2]-any[n2])) l1++;//如上所说。
		else if((anx[l1]-anx[n1])==(any[l2]-any[n2]))
		{
			n1=l1;n2=l2;//第一个序列从l1切，第二个从l2切，更新n1,n2;
			ans++;//答案+1；
			l1++;//然后继续向后扫。
			l2++;
		}
	}
	printf("%d",ans);//输出答案
	return 0;//程序拜拜~
}
//样例在此
/*
7 6
2 5 3 1 11 4 4
7 8 2 4 1 8

3

3 3
1 10 100
1 100 10

2

1 4
4
1 1 1 1

1
*/
```
如果对大家有帮助的话，希望大家留言支持呦~

---

