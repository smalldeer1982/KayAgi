# [POI 2014] KLO-Bricks

## 题目描述

现在你有 $k$ 种颜色的砖块，已知每种颜色砖块的数量，问是否有一种方案可以将砖块放成一排并且第一块和最后一块砖块的颜色为 $p,q$ 且相邻的砖块颜色不同，如果没有合法方案则输出 $0$。

## 说明/提示

$1 \leq k \leq 1e6,1\leq p,q \leq k$。

其中保证砖块总数量之和不超过 $1e6$。

## 样例 #1

### 输入

```
3 3 1
2 3 3
```

### 输出

```
3 2 1 3 2 3 2 1
```

# 题解

## 作者：枫林晚 (赞：12)

# 全网唯一 一篇O(n)题解+bzoj/luogu最优解

(截止2018.10.31)

这个题看大家都是优先队列，然后直接贪心放置。

还有用权值线段树来模拟堆过的%%%。

其实不用带logn也可以过的。

 

大家的方法是从左往右扫过去的。

对于这种插空排序的问题，还有一种考虑方法就是每个种类每个种类来考虑。

好处是，前面放过的种类放完了，和当前第i种永远不会产生冲突。

这就是我的大方向思路。

 

### 一、先不考虑端点固定的情况。

其实，不一定要先放最多的。

顺序可以随便。

假设放到完了前i种，那么，一共有sum[i]个。

对于后面的n-i种来说，前i种的方法对后面没有影响。

所以，肯定前i种放法中，选择相邻的情况最少的方案咯！

怎样凑出这个方案？

放完了前i种，设还剩下k个相邻位置。

1.对于第i种，肯定先插那k个位置中。这样每次相邻的-1,已经最优。

2.如果i种还剩下，那就从前面开始插空（不能和1中放的相邻）。这样相邻的数量不增不减。已经最优。

3.如果还剩下，那没有办法了。为了之后好处理，我们都把这些剩下的都放在末尾。

这样，不管你是数量较多的，还是数量较少的，

较多的，可以放在一起，由后面的再插空隔开。

较少的，就隔开之前相邻的。

 

至于怎么插空？

用一个最普通的链表就可以维护。

当然，我们每次要维护3中，开始连续的那一串的起始位置。方便下次直接访问。

 

 

 

### 二、有固定点呢？

两个端点比较麻烦。

所以我们就先放端点好了。

放的方法和上面差不多。

先放p，再放q

如果p的数量大于等于q。

那么放q的时候，直接插空，然后无论如何留下一个放末尾。

如果p的数量小于q。

那么放q的时候，插完空，直接往后放完即可。

（注意的是，这样的话有一个情况，就是在最后一个和倒数第二个之间还要插一个，后面放的时候特判一下）

 

然后放剩下k-2种。

按照刚才的策略即可。注意不能放在1前面，以及最后一个后面。

 

由于策略一直是最优的。

所以放完了之后，还有相邻元素，那就无解了。

 

### 三、一些细节

1.可能有两个端点颜色相同的情况。特判即可。bzoj上还有端点相同，且这个颜色只有一个的数据。。。。

2.刚才“二”中说的那个注意事项。

3.乱七八糟的各种边界情况和+1-1等等。

画个示意图就好理解了。

 

代码：

全程链表，所以复杂度线性。

（其实应该还有很多常数优化空间2333）

（这个题输入输出优化都很有用，输出优化快了400ms？？？）

```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
#define reg register int
#define il inline
#define numb (ch^'0')
using namespace std;
typedef long long ll;
const int N=1000000+5;
int nxt[N],id[N];//nxt后继，id颜色编号 
int tot;
int k,p,q;
int a[N];
il void rd(int &x){
	char ch;x=0;
	while(!isdigit(ch=getchar()));
	for(x=numb;isdigit(ch=getchar());x=x*10+numb);
}
il void prin(int x){
	if(x/10) prin(x/10);
	putchar(x%10+'0');
}
il void upda(int o,int to,int d){//初始化链表元素 
	nxt[o]=to;id[o]=d;
} 
int main(){
	rd(k);rd(p);rd(q);
	for(reg i=1;i<=k;++i)rd(a[i]);
	if(p==q&&a[p]==1){//特判一个点 
		if(k>1) printf("0");
		else printf("%d",p);
		return 0;
	}
	int las=0;
	for(reg i=1;i<=a[p];++i){//放p 
		upda(++tot,0,p);
		if(las) nxt[las]=tot;las=tot;
	}
	las=1;
	int pos=0;//pos是每一次最后的连续一部分同种相邻颜色的起始位置 
	if(p!=q){//放q 
		int i;
		for(i=1;i<=a[q]-1&&las<=a[p];++i){
			upda(++tot,nxt[las],q);
			nxt[las]=tot;++las;	
		}
		if(a[p]>=a[q]){
			nxt[a[p]]=++tot;
			upda(tot,0,q);
			pos=a[q];
		}
		else{
			pos=tot;
			while(i<=a[q]){
				nxt[tot]=tot+1;
				upda(++tot,0,q);
				++i;
			}
		}
	}
	else{
		pos=1;
	}
	int nd=tot;//末尾的编号 
	for(reg i=1;i<=k;++i){//放其他的 
		if(i==p||i==q) continue;
		int tmp=a[i];
		while(a[i]&&nxt[pos]!=nd){//插后面的空 
			upda(++tot,nxt[pos],i);
			nxt[pos]=tot;
			a[i]--;++pos;
		}
		if(a[i]&&nxt[pos]==nd&&id[pos]==q){//细节2 
			upda(++tot,nxt[pos],i);
			nxt[pos]=tot;
			pos=tot;//warning!!!
			a[i]--;
		}
		if(a[i]){//从前面插空 
			int now=1;//start from a[p]
			while(a[i]&&id[nxt[now]]!=i&&nxt[now]!=nd){
				upda(++tot,nxt[now],i);
				int to=nxt[now];
				nxt[now]=tot;
				now=to;
				a[i]--;
			}
			if(a[i]){//如果还有剩余 
				int las=pos;
				if(id[pos]!=i) pos=tot+1;//warning!!! tot+1
				while(a[i]){
					upda(++tot,nxt[las],i);
					nxt[las]=tot;
					las=tot;
					a[i]--;
				}
			}
		}
	}
	for(reg i=1;i!=nd;i=nxt[i]){//判断不合法 
		if(id[i]==id[nxt[i]]){
			printf("0");return 0;
		}
	}
	for(reg i=1;i!=nd;i=nxt[i]){
		prin(id[i]);putchar(' ');
	}prin(id[nd]);
	return 0;
}

```

总结：

注意处理排序插空问题的两个大方法：

1.从左到右扫描。期间往往用数据结构维护。

2.分类别，同一个类别一起考虑。往往用到对插入的物品排序（当然本题不用）

---

## 作者：ydnhaha (赞：8)

[题面]( https://www.luogu.org/paste/ov7unuup)

题外话1：洛谷上POI的翻译怎么老出锅。。。无解要输出$0$。。。

题外话2：先%一发下面颜神的带权线段树233

$1->n$一遍扫过去，贪心地将数量最多的砖块先放下去，然后用数量少的砖块来“切”它们(感性理解一下233)，可以结构体重载运算符+优先队列实现。每次放置时更新一个$noww$记录上一块砖的颜色，如果会放重就再取一种来放(这里注意判队列是否为空)。但是如果好几种砖数目一样先放那种呢？先放与结尾颜色相同的，还是那个思路，用与结尾颜色不同的来“切”它们。

注意细节quq
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int outp[1000009];
int n,b,e,rd,tot,noww;
struct a{int col,num;};
bool operator <(a x,a y)
{
    return (x.num==y.num)?x.col!=e:x.num<y.num;
}
priority_queue<a> qs;
int main ()
{
    scanf("%d%d%d",&n,&b,&e);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&rd);
        tot+=rd;
        if(i==b) rd--;
        if(i==e) rd--;
        if(rd>0) qs.push((a){i,rd});
        else if(rd<0) {printf("0");return 0;}
    }
    outp[1]=b,noww=b;
    for(int i=2;i<tot;i++)
    {
        a tn=qs.top();qs.pop();
        int ttp=tn.col,tmp=tn.num;
        if(ttp==noww)
            if(!qs.empty())
            {
                a tm=qs.top();qs.pop();
                int tpp=tm.col,tep=tm.num;
                outp[i]=tpp;
                noww=tpp;
                if(tep>1)
                    qs.push((a){tpp,tep-1});
                qs.push(tn);
                continue ;
            }
            else
            {
                printf("0");
                return 0;
            }
        noww=ttp;
        outp[i]=ttp;
        if(tmp>1)
            qs.push((a){ttp,tmp-1});
    }
    outp[tot]=e;
    for(int i=1;i<tot;i++)
        if(outp[i]==outp[i+1]||!outp[i])
        {
            printf("0");
            return 0;
        }
    for(int i=1;i<=tot;i++)
    {
        printf("%d",outp[i]);
        if(i!=tot)
            printf(" ");
    }
    return 0;
}
```

---

## 作者：Hoks (赞：7)

## 前言
[传送门](https://www.luogu.com.cn/blog/Hok/p3566-xie-ti-bao-gao)，个人博客内食用更佳哦！[题目链接](https://www.luogu.com.cn/problem/P3566)

先膜拜一下神犇枫林晚的神仙题解，本题解是优先队列做法捏。
## 题意
题意在题面里已经有了，但是有坑，在此感谢一下@ydnhaha 的题解，感谢他提示的无解要输出 $0$。
## 思路分析
首先看一眼肯定是**贪心**，贪心怎么贪捏，就是用小的把大的隔开（用第六感的得出的）。

那为何不用小的隔开小的呢，易得如果小的把小的隔开了之后，还有剩余的砖能给大的隔完，那小的隔开大的也肯定能行，所以对于任何的情况我们都用小的隔开大的就行了（下面会给具体证明捏）。

那小的和大的如何排序捏。因为是每次操作完都要放回去重新排序，所以自然而然的想到了**优先队列**来每次插入后自动排序。（说实话太久没写了重载炸了好几次。）
## 证明
设按砖的数量从小到大排列的砖的数量分别为 $a_1,a_2\ldots a_n$，颜色分别为 $id_1,id_2\ldots id_n$。

假设一个最劣情况，即为 $a_n=\sum_{i=1}^{n-1}$ 但是结尾不为 $id_n$， 开头不为 $id_1$。

若我用小的隔开大的，那么结果即为 $id_1,id_n\ldots id_2,id_n\ldots id_{n-1},id_n$ 最后刚好用小的将大的隔完。

但若我用小的隔开小的，那么前面便又一堆 $id_1,id_2$ ($a_1$ 个)，$id_2,id_3$ ($a_2-a_1$ 个)，$id_3,id_4$ ($a_3-a_2+a_1$ 个) $\ldots$ 最后到了 $id_{n-1},id_n$ 时便只能排列 $a_{n-1}-a_{n-2}+a_{n-3}-a_{n-4}\ldots$ 个，又因为这里面有将近一半的项是减，所以这个值肯定小于 $\sum_{i=1}^{n-1}$ 即为 $a_n$ 也就是还有剩下的砖没被隔开完，没法排列了。

对于相同的一种**最劣**极端情况，用小的隔开大的可以成功，而小的隔开小的不行，自然要选择小的隔开小的了。

## AC 代码
终于到愉快的上代码环节了(^▽^)。

（对了强调一个要点，开头和结尾时可能相同的，所以第 $23$ 和第 $24$ 行是不能用正常 if 的方式合并的捏。~~有个蠢货在这个地方卡了自己好几次~~。）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,b,e,tot,now;
int ans[1000010];
struct node{int id,x;};
bool operator <(node x,node y){return (x.x==y.x)?x.id!=e:x.x<y.x;}
priority_queue<node> q;
int read()//传统技艺快读
{
  char c=getchar();int x=0;
  while(!isdigit(c)) c=getchar();
  while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
  return x;
}
signed main()
{
  n=read(),b=read(),e=read();
  for(int i=1,x;i<=n;i++)
  {
    x=read();
    tot+=x;
    if(i==b) x--;
    if(i==e) x--;
    //就是上面两行，千万不能正常合并，因为b和e可能相等
    if(x>0) q.push((node){i,x});
    else if(x<0){printf("0");return 0;}
  }
  ans[1]=b,now=b;
  for(int i=2;i<tot;i++)
  {
    node t=q.top();q.pop();
    if(t.id==now)//如果最上面的一块砖的颜色和前一个一样
      if(!q.empty())//如果序列中还有砖
      {
        node t1=q.top();q.pop();//拿出另一种颜色的砖放上
        ans[i]=now=t1.id;
        if(t1.x>1) q.push((node){t1.id,t1.x-1});
        q.push(t);
        continue ;
      }
      else{printf("0");return 0;}//拿不出不同颜色的砖了，自然意味着不行了
     now=ans[i]=t.id;
     if(t.x>1) q.push((node){t.id,t.x-1});
  }
  ans[tot]=e;
  for(int i=1;i<tot;i++)
    if(ans[i]==ans[i+1]||!ans[i])//重新扫一遍有没有不符合的情况
    {
      printf("0");
      return 0;
    }
  for(int i=1;i<=tot;i++)
  {
    printf("%d",ans[i]);
    if(i!=tot) printf(" ");
  }
  return 0;
}
```
完结撒花 (^▽^)！！！

---

## 作者：mlvx (赞：5)

### 题意

给你 $n$ 种颜色的砖块，开头必须是 $p$，结尾必须是 $q$，相邻的不能同色，给出构造方案，无解输出 $0$。

### 分析

首先我们肯定要把每种颜色的数量搞的平均一点。

每次放当前可使用的数量最多的颜色，可以把数量搞的平均一些。

那如果最后倒数第二个只剩 $q$ 了怎么办？

我们可以把 $q$ 在前面优先放，这样就不会出现上面的情况了。

可以搞一个优先队列，第一关键字为砖块数量（大的排前面），第二关键字为是否等于 $q$（等于 $q$ 的排前面）。

然后每次取出前两个元素。

如果前一个颜色和当前数量最多的颜色相同，那就使用第二多的颜色，反之则使用最多的颜色。

注意处理下 $n=1$ 的情况。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,cnt=1,sum,st,en,ans[1000100];
struct node{int num,color;};
bool operator<(node a,node b){return a.num==b.num?(a.color!=en):(a.num<b.num);}
priority_queue<node>q;
int main(){
	cin>>n>>st>>en;
	if(n==1)return cin>>x,cout<<(st==1&&en==1&&x==1),0;
	for(int i=1;i<=n;i++){
		cin>>x,sum+=x,i==st&&--x,i==en&&--x;
		if(x<0)return putchar('0'),0;
		else q.push({x,i});
	}ans[1]=st,ans[sum]=en;
	while(q.top().num){
		node a,b;a=q.top(),q.pop(),b=q.top(),q.pop();
		if(ans[cnt]==a.color&&ans[cnt+2]==b.color||ans[cnt]==b.color&&ans[cnt+2]==a.color)return putchar('0'),0;
		if(ans[cnt]==a.color)q.push({a.num,a.color}),q.push({b.num-1,b.color}),ans[cnt+1]=b.color;
		else q.push({a.num-1,a.color}),q.push({b.num,b.color}),ans[cnt+1]=a.color;
		++cnt;
	}for(int i=1;i<=sum;i++)cout<<ans[i],i==sum||(putchar(' '),1);
	return 0;
}
```

---

## 作者：luchenxi2012 (赞：3)

# P3566 [POI2014] KLO-Bricks 题解
## 题意
[题目传送门](https://www.luogu.com.cn/problem/P3566)

给定一些砖块和他们的数量，求把所有砖块排成一排，且相邻两砖块两两不同的任意一个合法方案。其中，一行的头和尾已经确定。
## 思路
用贪心策略，每次先取数量最多的那种砖块。

可是要是最后一个砖块与倒数第二个重合了呢？

于是，在有两种相同数量砖块的前提下，优先选与最后一个给定砖块种类相同的那种砖块。

要是在这种情况下都不合法，就直接结束了。

所以考虑使用优先队列。

每次都取前两个，若第一个不行就取第二个。$ans_{sum}=ans_{sum-1}$ 的情况最后再判。
## 代码
```cpp
#include <cstdio>
#include <queue>
using namespace std;
int k, P, Q, x, sum;
int ans[1000001];
struct node {
	int col, num;
	bool operator < (const node &a) const {
		if (num == a.num) return a.col == Q; // 与最后一个颜色相同的优先选
		return num < a.num; // 数量多的优先选
	}
};
int main() {
	scanf("%d%d%d", &k, &P, &Q);
	if (k == 1) // 一定要特判！
		return scanf("%d", &x),
			   printf("%d", x == 1 && P == 1 && Q == 1), 0;
	priority_queue <node> q;
	for (int i = 1; i <= k; i++) {
		scanf("%d", &x);
		sum += x; // 求总和
		if (i == P) x--; // 用掉了一个
		if (i == Q) x--; // 用掉了一个
		if (x < 0) // 没有足够砖块，肯定不行
			return printf("0"), 0;
		if (x) q.push({i, x});
	}
	ans[1] = P, ans[sum] = Q;
	for (int i = 2; i < sum; i++) {
		node x = {0, 0};
		node y = {0, 0};
		if (!q.empty())
			x = q.top(),
			q.pop();
		if (!q.empty())
			y = q.top(),
			q.pop();
		if (x.col == ans[i - 1]) { // 第一个不合法
			if (!y.num) // 只有一种砖块了，不行
				return printf("0"), 0;
			ans[i] = y.col, y.num--; // 用砖块
		} else {
			if (!x.num)
				return printf("0"), 0;
			ans[i] = x.col, x.num--;
		}
		if (x.num) q.push(x); // 重新进队列
		if (y.num) q.push(y); // 重新进队列
	}
	if (ans[sum - 1] == ans[sum])
		return printf("0"), 0; // 特判
	for (int i = 1; i < sum; i++)
		printf("%d ", ans[i]);
	printf("%d", ans[sum]); // 坑输出格式
	return 0;
}
```

---

## 作者：Last_Reincarnation (赞：3)

快$CPS$了， 一个一般学校的一般$Oier$很虚，感觉自己很菜， 好不容易写拉一道好的贪心题（写了好长时间啊），要发个题解。

这题见过好多遍了，也有好多人讲过， 自己认为很好写，然后一直没写，一些才发现原来有一点不好写（是我的代码能力太差了。。）

本题是一个练习代码能力和细节处理的好题

进入正题

1.贪心策略 ：在保证相邻两个颜色不同时，先放多的，若一样多，则放与末尾颜色相同的。（正确性感性理解一下）

变量
```cpp
int k, s, t, n, pre;//k为颜色数，s为第一个块颜色，t为最后一个块的颜色， n为总块数， pre为前一个快的颜色;
int ans[maxn];//记录答案;
bool flag;//代码中会解释用途;

struct Node{
	int col, id;//这个结构体没啥用，可以用一个变量代替。。;
}a[maxn];
```


处理 一样多的 且 一样多的中有与末尾颜色一样的 
```cpp
struct note{
	int now, w;//now颜色， w个数;
	friend bool operator < (note a, note b){
		if (a.w != b.w) return a.w < b.w; //大根堆应为小于号
		if (a.now == t) return false;//t为末尾颜色
		return true;
	}
};

priority_queue<note>Q;

```

快读
```cpp
int f_;
char ch_;
template <class T>
	inline T read (T &x_){
		x_ = 0, f_ = 1, ch_ = getchar();
		while (ch_ > '9' || ch_ < '0'){if (ch_ == '-') f_ = -1; ch_ = getchar();}
		while (ch_ >= '0' && ch_ <= '9') x_ = (x_ << 3) + (x_ << 1) + ch_ - 48, ch_ = getchar();
		return x_*f_;
	}
```

激动人心的时候（这么长时间，终于有代码啦）

$code$
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 1e6 + 10;

int k, s, t, n, cnt, pre;
int ans[maxn];
bool flag;

struct Node{
	int col, id;
}a[maxn];

struct note{
	int now, w;
	friend bool operator < (note a, note b){
		if (a.w != b.w) return a.w < b.w;
		if (a.now == t) return false;
		return true;
	}
};

priority_queue<note>Q;

int f_;
char ch_;
template <class T>
	inline T read (T &x_){
		x_ = 0, f_ = 1, ch_ = getchar();
		while (ch_ > '9' || ch_ < '0'){if (ch_ == '-') f_ = -1; ch_ = getchar();}
		while (ch_ >= '0' && ch_ <= '9') x_ = (x_ << 3) + (x_ << 1) + ch_ - 48, ch_ = getchar();
		return x_*f_;
	}

int main(){
	read(k);
	read(s);
	read(t);
	for (register int i = 1;i <= k; ++i){
		read(a[i].col);
		a[i].id = i;
		n += a[i].col;
		if (a[i].id == s) a[i].col--;
		if (a[i].id == t) a[i].col--;
		if (a[i].col < 0) {printf("0"); return 0;}//题意要求，因为Bitie could have made a mistake，所以他会当块数没有他记忆中的多， 则跳出;
		Q.push((note){i, a[i].col}); 
	}
	pre = s;//从第二个块开始，前一个块为s;
	ans[1] = s;
	ans[n] = t;	
	note top, tmp;
	for (register int i = 2;i < n; ++i){
		top = Q.top();
		Q.pop();
		flag = false;
		if (top.now == pre){//这里是重点，若与前一个颜色相同则用tmp记录堆顶
			flag = true;
			tmp = top;
			if (!Q.empty()) 
				top = Q.top();//若第二堆顶有则放它，否则就会把两个一样的放在一起，然后跳出即可
			else {
				printf("0"); 
				return 0;
			}
			Q.pop();
		}
		pre = ans[i] = top.now;
		if (top.w > 1) 
			Q.push((note){top.now, top.w - 1});
		if (flag) 
			Q.push(tmp);//若flag为一，则把原来堆顶放回去
	}
	if (ans[n-1] == ans[n]) {
		printf("0"); 
		return 0;
	}
	for (register int i = 1;i <= n; ++i){
		if (i != n)
			printf("%d ",ans[i]);
		else printf("%d", ans[i]);
	}
	return 0;
}

最后记住pus("0")不行，因为它自带换行，因为忘记啦， 所以提交时60pt好几次

```
最后祝大家$oi$路上越走越顺

$AK ioi$


日拱一卒，功不唐捐！！！


---

## 作者：封禁用户 (赞：3)

首先不考虑左端点和右端点的话，一个显然的贪心思路就是，每次取除了上次取的之外剩下最多的，这样会让取得更均匀，在有解的情况下一定不会出现相邻重复的现象，如果中途发现没法取了那就说明无解。

但是要是有了左右端点咋办？我们先在最左边把左端点填上，然后在按照上面的步骤贪心。但是这就会造成一个问题就是填到最右面的时候，和右端点产生冲突了，这样就会很尴尬。为了避免这种情况，我们应该贪心的把剩下的右端点砖块尽量填在最左边（先用完），这样就不会冲突了。

这个模拟我是拿权值线段树实现的，当然大概也可以拿堆什么的维护（不过感觉堆不太好修改，因为我们为了避免取到上一个填的，就暂时把上一个的个数设为-inf，而且还要修改填完了的个数~~反正一直以来我的堆都是拿线段树写的线段树大法好~~）

哦，对了，一定要注意左右端点相同的情况，貌似这题10个测试点中有6个都是左右端点相同的，被这个坑了半天……

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define inf -1234567890
using namespace std;
char buf[100000000];int ptr=0;
inline char get_char(){
	ptr++;return(buf[ptr-1]);
}
#define getchar get_char
inline int get(){
	int n;char c;while((c=getchar())||1)if(c>='0'&&c<='9')break;
	n=c-'0';while((c=getchar())||1){
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
}
typedef struct _n{//线段树
	int left;int right;int maxn;int pos;
}node;node memchi[3000001];int gn=1;
int ints[1000001];
inline void up(int tree){
	int ls=memchi[tree].left,rs=memchi[tree].right;
	if(memchi[ls].maxn>memchi[rs].maxn){
		memchi[tree].maxn=memchi[ls].maxn;memchi[tree].pos=memchi[ls].pos;
	}else{
		memchi[tree].maxn=memchi[rs].maxn;memchi[tree].pos=memchi[rs].pos;
	}
}
int build(int l,int r){//建树
	int tree=gn;gn++;
	if(l==r){
		memchi[tree].maxn=ints[l];memchi[tree].pos=l;
	}else{
		int mid=(l+r)>>1;memchi[tree].left=build(l,mid);
		memchi[tree].right=build(mid+1,r);up(tree);
	}return(tree);
}
int pt,num;
void setpt(int l,int r,int tree){//点修改
	if(l==r){
		memchi[tree].maxn=num;return;
	}int mid=(l+r)>>1;
	if(pt<=mid)setpt(l,mid,memchi[tree].left);
	else setpt(mid+1,r,memchi[tree].right);up(tree);
}
int ans[1000001];//答案
void print(int num){
	if(num>=10)print(num/10);putchar(num%10+'0');
}
int main(){
	fread(buf,1,100000000,stdin);
	int n=get(),l=get(),r=get();int sum=0;
	for(register int i=1;i<=n;i++){
		ints[i]=get();sum+=ints[i];if(!ints[i])ints[i]=inf;
	}
	if(l==r){//特判左右端点相同可能造成的无解情况
		if(ints[l]<2){
			cout<<0;return(0);
		}
		if(sum==2){
			cout<<0;return(0);
		}
	}sum--;
	ints[r]--;if(!ints[r])ints[r]=inf;int ptr=0;
	int root=build(1,n);int lst=l,lbd=ints[l];
	ans[ptr]=l;ptr++;sum--;
	if(l==r){//如果左右端点相同的话，因为我是用ints[r]直接看右端点还剩了多少个，所以左边填了一个后应该把这个再减1，不加这个的话只能得40分
    
		ints[l]--;if(ints[l]==0)ints[l]=inf;
	}
	while(sum){
		if(ints[r]>0&&lst!=r){//如果右端点没用完的话且能填上，就填右端点，因为我们要尽量的先用完右端点
        
			ans[ptr]=r;ptr++;
			pt=lst,num=lbd-1;if(num==0)num=inf;setpt(1,n,root);
			lst=r;lbd=ints[r];sum--;ints[r]--;if(ints[r]==0)ints[r]=inf;
		}else{
			pt=lst;num=inf;setpt(1,n,root);
			int me=memchi[root].pos,dat=memchi[root].maxn;
			if(dat==inf){//填不了了就无解
				cout<<0;return(0);
			}
			ans[ptr]=me;ptr++;sum--;
			pt=lst;num=lbd-1;if(num==0)num=inf;setpt(1,n,root);
			lst=me;lbd=dat; 
		}
	}
	for(register int i=0;i<ptr;i++){
		print(ans[i]);putchar(' ');
	}print(r);
	return(0);
}
```

---

## 作者：xiaoxiaoxia (赞：1)

# [[POI2014] KLO-Bricks](https://www.luogu.com.cn/problem/P3566)

## 题目大意：
给你每种颜色的砖块数量，相同颜色的砖块不能放在一起，两头颜色已经确定，构造一种方案，或者输出无解。

## 思路概述：
首先这道题我们不妨先思考一个特殊的情况，就是如果它每种颜色的砖块数量都是一样的，那么肯定是 $123123123$ 这样子循环，所以为了变成这个样子，我们就需要将这些砖块给他抹掉。那么思路就变得清晰了，就是每次去颜色最多的方块放上去。但是因为结尾的方块会影响，所以呢如果有同样多数量的，优先取后面的。然后因为每次都要取最大值的，所以可以使用优先队列维护。然后格式一定要注意，千万注意。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[1000009];
int n,b,e,tot,now;
struct node
{
	int col,num;
};
bool operator <(node x,node y)
{
    return (x.num==y.num)?x.col!=e:x.num<y.num;
}
priority_queue<node> que;
int main ()
{
    cin>>n>>b>>e;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        tot+=x;
        if(i==b) 
			x--;
        if(i==e) 
			x--;
        if(x>0) 
			que.push((node){i,x});
        else if(x<0) 
		{
			cout<<0<<endl;
			return 0;
		}
    }
    ans[1]=b;
	now=b;
    for(int i=2;i<tot;i++)
    {
        node tn=que.top();
		que.pop();
        int top=tn.col,tmp=tn.num;
        if(top==now)
        {
			if(!que.empty())
            {
                node noww=que.top();
				que.pop();
                int tpp=noww.col,tep=noww.num;
                ans[i]=tpp;
                now=tpp;
                if(tep>1)
                    que.push((node){tpp,tep-1});
                que.push(tn);
                continue ;
            }
            else
            {
                printf("0");
                return 0;
            }			
		}
        now=top;
        ans[i]=top;
        if(tmp>1)
            que.push((node){top,tmp-1});
    }
    ans[tot]=e;
    for(int i=1;i<tot;i++)
    {
		if(ans[i]==ans[i+1]||!ans[i])
        {
            cout<<0<<endl;
            return 0;
        }		
	}
    for(int i=1;i<=tot;i++)
    {
        cout<<ans[i];
        if(i!=tot)
            cout<<" "<<endl;//这个格式坑了我，导致WA40
    }
    return 0;
}
```

---

## 作者：littleqwq (赞：1)

# P3566 [POI2014] KLO-Bricks 题解

### 大致意思：

现在有 $n$ 种颜色的砖块，第一个必须放第 $p$ 种颜色，最后一定得放第 $q$ 种颜色，剩余中间的需要自己构造，使得每相邻两个砖块的颜色不相等，有解随便输出任意一种，无解则输出 $0$。

### 大致思路：

这是一道很好的贪心构造题，最优的方案，肯定就是先放最少最多，用最多的来分隔少的，因为这样最多的可以放置的更为均匀，以达到我们实现最优方案的目的，不然会导致多的前面放的过少，后面聚在一堆，实现出来的代码显示的是无解。当然如果当前最多的颜色与前面一项相等，那么我们要取一二大的，以此类推。

而我们知道了，想要实现此方法需要一边运行放颜色，一边排序，如果直接用用排序函数，占用时间太大，肯定会超时，那么我们就可以用到优先队列，它是可以边运行边排序的。

我们可以用变量 $s$，记录总砖块数，接着通过循环实现放砖块：

- 当前最多的砖块他的下标与前面相等，那么我可以用 $t$ 记录最多砖块的数量，把它从队列中移除，找到第二多的砖块，将这个砖块的数量减 $1$。

- 当前最多的砖块他的下标与前面不相等，直接用此砖块，将这个砖块的数量减 $1$。

当然，在过程中我们还要判断，本种砖块数是否大于 $0$，和此时队列里还有没有砖块，如果没有砖块，则无解。

### 代码实现：

```
#include<bits/stdc++.h>
using namespace std;
int n,p,y,s;
int ar[1000005];
bool f;
struct node{
	int x;
	int id;
}a[1000005];
bool operator <(node l,node r){
    if (l.x != r.x) return l.x<r.x;
	if (l.id == y) return 0;
    if (r.id == y) return 1;
    return 0; 
}
priority_queue<node> q;

int main(){
	cin>>n>>p>>y;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;
		if(i==p) a[i].x--;
		if(i==y) a[i].x--;
		s+=a[i].x;
		a[i].id=i;
		q.push(node{a[i].x,i});
	}

	int u=p;
	ar[s+2]=y;
	for(int i=2;i<=s+1;i++){
		node t=q.top();q.pop();
		if(t.x>0) t=t;
        else{
            f=1;
            break;
        }
		if(t.id!=u&&t.x>0){
			ar[i]=t.id;
			q.push(node{t.x-1,t.id});
			u=ar[i];
		}else if(q.size()&&t.x>0){
			node v=q.top();
			q.pop();
			ar[i]=v.id;
			q.push(node{v.x-1,v.id});
			q.push(node{t.x,t.id});
			u=ar[i];
		}else if(!q.size()){
			f=1;
			break;//不加 RE，我找了两位大佬才调出来
		}
	}
	if(f){
		cout<<"0";
		return 0;
	}
	for(int i=1;i<=s+1;i++){
		if(ar[i]==ar[i+1]){
			f=1;
		}
	}
	if(f){
		cout<<"0";
		return 0;
	}
	cout<<p<<" ";
	for(int i=2;i<=s+1;i++){
		cout<<ar[i]<<" ";
	}
	cout<<ar[s+2];
	return 0;
}
```

这样这道题就结束啦！

---

## 作者：Loser_Syx (赞：1)

考虑贪心。

由于本题中开头结尾 $p,q$ 被固定，仅需填从 $2 \sim n-1$ 中的数。

然后就有一个简单的贪心策略，使用数据结构维护当前最大数量，每次填数，看数量最大的那个东西是否与前面填的一致，如果不一致的话直接填，一致就只能换次大的去填了。

但是发现光这么贪存在某些谬误，例如可能会输出末尾两个数一样的，例如输出 `1 2 1 3 1 2 3 1 2 3 3`，显然这种情况下是存在正解为 `1 3 2 1 3 2 1 3 2 1 3` 等的，于是贪心条件需要再加一条：考虑同等数量的不同的数，优先使用 $q$ 进行填充，这样可以保证如果存在有解 $q$ 一定不是最后一个被填的。

然后做完了，`spj` 不知道写的什么烂东西。

```cpp
int n, x, y;
struct node {
	int first, second;
	bool operator < (const node &a) const {
		if (a.first == first) return second != y;
		return first < a.first;
	}
};
priority_queue<node> q;
int ans[1010101];
signed main() {
	n = read(), x = read(), y = read();
	for (int i = 1; i <= n; ++i) {
		int a = read();
		if (i == x) --a;
		if (i == y) --a;
		if (a < 0) return printf("0"), 0;
		q.push({a, i});
	}
	ans[1] = x;
	int len = 1;
	int last = x;
	while (!q.empty()) {
		auto tp = q.top();
		q.pop();
		if (q.size() && tp.second == last) {
			auto tp2 = q.top();
			q.pop();
			ans[++len] = tp2.second;
			tp2.first--;
			last = tp2.second;
			if (tp2.first) q.push(tp2);
			q.push(tp);
		} else if (q.size() && tp.second != y && tp.first == q.top().first && q.top().second != last && q.top().second == y) {
			auto tp2 = q.top();
			q.pop();
			last = tp2.second;
			ans[++len] = tp2.second;
			tp2.first--;
			if (tp2.first) q.push(tp2);
			q.push(tp);
		} else if (tp.second == last) {
			return printf("0"), 0;
		} else {
			tp.first--;
			ans[++len] = tp.second;
			if (tp.first) q.push(tp);
			last = tp.second;
		}
	}
	if (last == y) return printf("0"), 0;
	ans[++len] = y;
	for (int i = 1; i <= len; ++i) {
	    if (i != len) write(ans[i], ' ');
	    else printf("%lld", ans[i]);
	}
	return 0;
}
```

---

## 作者：dunko (赞：1)

## **简单说两句**

多久没写过题解了呢...    

blog还要边上的**h^ovny**指点呢。

## 题目

[???](<https://www.luogu.org/problem/P3566>)

## 思路

简单想到这是一个**贪心**。    

每次取当前数目**最多**的那个数，将它放在当前位上。

如果有多个数目相同的数，那优先取最后一个数。（很明显，避免重复）

那这就好做了。数目可以用**堆**来维护。

 （结构体还真是个恶心的东西呢。莫名RE...）

无解的情况有好多处理的方法，就不说了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+7;
inline int read(){
	int x=0,f=1;char C=getchar();
	while(!isdigit(C)) {if(C=='-') f=-1;C=getchar();}
	while(isdigit(C)) x=(x<<1)+(x<<3)+C-'0',C=getchar();
	return x*f;
}
int ans[maxn],n,S,T,tot,a[maxn],last;
struct node{
	int id,x;
	bool operator < (const node &t) const {
		return x<(t.x)||((x==t.x)&&t.id==T);
	}
}A;
priority_queue<node>que;
int main(){
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),last=ans[1]=S=read(),T=read();
	for(int i=1;i<=n;i++) tot+=(a[i]=read());
	a[S]--,a[T]--; ans[tot]=T;
	for(int i=1;i<=n;i++) que.push((node){i,a[i]});
	for(int i=2;i<tot;i++){
		bool F=0;
		node u=que.top(); que.pop();
		if(u.id==last) F=1,A=u,u=que.top(),que.pop();
//		printf("%d %d\n",u.id,u.x);
		if(F){
			if(u.id==A.id) {cout<<0;return 0;}
			else que.push(A);
		}
		ans[i]=u.id; u.x--;if(u.x>0) que.push(u); last=u.id;
	}
	int F=1;
	for(int i=2;i<=tot;i++) if(ans[i]==ans[i-1]) F=0;
	if(F){
		printf("%d",ans[1]);
		for(int i=2;i<=tot;i++) printf(" %d",ans[i]);
	} else cout<<F;
	return 0;
}
```

时间一久了，码风都变了呢。

希望能过，再%一下Venus大佬。

谢谢观看。



---

## 作者：123zbk (赞：0)

**题意简述**：

有 $k$ 种砖块，给定第一和最后一个砖块的颜色，问是否有一种排法满足相邻砖块颜色不同。

**主体思路**：

贪心的思路显然。为了保证相邻砖块颜色不同，一定是先放颜色数量最多的砖块，如果和上一个颜色相同就将颜色第二多的砖块拿出来。同时，为了避免和最后一个块颜色相同，在有多种砖块颜色相同时，优先放和最后一个块颜色相同的砖块。

最后，如果放块的中途只剩下一种颜色或者倒数第二块和最后一个块颜色相同则无解，反之则有解。

用优先队列维护即可，注意特判一些情况。

**code**:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,s,t,lst,sum,a[N],ans[N];
struct node
{
    int w,id;
    bool operator <(const node &ret) const{
        if(w==ret.w){
            return id!=t;
        }
        return w<ret.w;
    }
};
priority_queue <node> q;
int main()
{
    //freopen("data.in","r",stdin);
    cin>>n>>s>>t;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    if(s==t and a[s]==1){
        printf("%d\n",(n==1)?s:0);
        exit(0);
    }
    for(int i=1;i<=n;i++){
        sum+=a[i];
        a[i]-=((i==s)+(i==t));
        if(a[i]<0) return printf("0"),0;
        if(a[i]){
            q.push({a[i],i});
        }
    }
    ans[1]=s,ans[sum]=t,lst=s;
    for(int i=2;i<sum;i++){
        node u=q.top();
        int w=u.w,id=u.id;
        q.pop();
        if(id==lst){
            if(q.empty()){
                printf("0");
                exit(0);
            }
            else{
                node v=q.top();
                int w2=v.w,id2=v.id;
                q.pop();
                ans[i]=id2;
                w2--;
                if(w2){
                    q.push({w2,id2});
                }
                q.push({w,id});
                lst=id2;
            }
        }
        else{
            ans[i]=id;
            w--;
            if(w){
                q.push({w,id});
            }
            lst=id;
        }
    }
    if(ans[sum-1]==ans[sum]) printf("0");
    else{
        for(int i=1;i<=sum;i++){
            printf("%d",ans[i]);
            if(i!=sum) printf(" ");
        }
    }
    return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
考虑贪心放颜色，既然我们希望摆放方案尽可能有解，那么每次摆放优先摆放数量最多的一种颜色，那么这样就可以使剩下的颜色数量更均匀，就越有可能成功。

那么继续思考，如果最多的颜色与前一种已经摆放的颜色冲突了怎么办，所以每次再取出次大的一种颜色，就可解决。

还有一种情况，如果最大的与次大的相等呢，那么优先摆放结尾颜色的，这样就可有效避免倒数第二格与末尾的冲突。

最后就是特判无解的情况了。
### Code:
```cpp
#include<bits/stdc++.h>
#define N 10000005
using namespace std; 
int n,st,nd,t,sum,ans[N];
struct node{
	int color,num;
};
priority_queue<node> q;
bool operator <(node x,node y){
	return x.num<y.num or (x.num==y.num and x.color!=nd);
}
int main(){
	cin>>n>>st>>nd;
	if(n==1){
		cin>>t;
		cout<<(st==nd and t==1 and nd==1);//特判 
		return 0;
	}
	for(int i=1;i<=n;i++){
		cin>>t;
		sum+=t;
		if(i==nd) t--;
		if(i==st) t--;
		if(t<0){
			cout<<0;
			return 0;
		}
		if(t)q.push({i,t});
	}
	ans[1]=st,ans[sum]=nd;
	for(int i=2;i<sum;i++){
		node x={0,0},y={0,0};
		if(!q.empty()){
			x=q.top();
			q.pop();
		}
		if(!q.empty()){
			y=q.top();
			q.pop();
		}
		if(x.color==ans[i-1]){
			if(!y.num){
				cout<<0;
				return 0;
			}
			y.num--;
			ans[i]=y.color;
		}
		else{
			if(!x.num){
				cout<<0;
				return 0;
			}
			x.num--;
			ans[i]=x.color;
		}
		if(x.num)q.push(x);
		if(y.num)q.push(y);
	}
	if(ans[sum]==ans[sum-1]){
		cout<<0;
		return 0;
	} 
	for(int i=1;i<=sum;i++){
		cout<<ans[i];
		if(i!=sum) cout<<' ';//特坑格式 
	}
 	return 0;
} 
```

---

## 作者：mystic_qwq (赞：0)

给出一些颜色的砖块的数量。要求首位必须为 $p$ 颜色，末位必须为 $q$ 颜色。请给出一种方案使得能放完所有方块，且相邻两个方块颜色不同。

考虑贪心。每次先尽量选剩余数量最大的颜色，如果与前一位相同，则选次大的颜色。而我们可以发现若最大的和次大的都选不了的话（也就是当前位和最后一个方块选的颜色刚好是当前的最大和次大），则不存在一种合法的方案。感性理解：因为假设你选了第三大的，后面最大和次大还得填，第三大肯定先填完因为最大和次大都要匹配。

对于 $n=1$ 的情形特判一下：当且仅当 首尾颜色一样且给出数量为 $1$ 时，是合法的。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e7;
int n,bg,ed;
struct node{
  int c,x;
  bool operator<(const node&a)const{
    if(x!=a.x) return x<a.x;
    return c!=ed;
  }
};
int res[N];
priority_queue<node> q;
int main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>bg>>ed;
  if(n==1) {
    cin>>n;
    int res=n==1&&bg==1&&ed==1;
    cout<<res;
    return 0;
  }
  int S=0;
  for(int i=1;i<=n;++i){
    int x; cin>>x;
    S+=x;
    if(i==bg) --x;
    if(i==ed) --x;
    q.push({i,x});
  }
  res[1]=bg,res[S]=ed;
  int p=1;
  for(node x,y;q.size()&&q.top().x;++p){
    x=q.top(),q.pop();
    if(q.size()){
      y=q.top(),q.pop();
      if(x.c==res[p]&&y.c==res[p+2]) return (cout<<0),0;
      if(y.c==res[p]&&x.c==res[p+2]) return (cout<<0),0;
      if(res[p]==x.c) q.push({x.c,x.x}),q.push({y.c,y.x-1}),res[p+1]=y.c;
      else q.push({y.c,y.x}),q.push({x.c,x.x-1}),res[p+1]=x.c;
    }
    else {
      if(x.c==res[p]) return (cout<<0),0;
      q.push({x.c,x.x-1});
      res[p+1]=x.c;
    }
  }
  for(int i=1;i<=S;++i){
    cout<<res[i];
    if(i!=S) cout<<' ';
  }
  return 0;
}

```

---

