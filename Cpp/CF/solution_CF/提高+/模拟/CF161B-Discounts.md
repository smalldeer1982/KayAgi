# Discounts

## 题目描述

超市进行优惠活动，顾客如果在一架购物车中放上一个凳子，他就可以半价买掉这架购物车里最便宜的商品（一架购物车中只能让一个东西半价）。

现在$\mathrm{Polycarpus}$要用$k$架购物车（容量无限，但不能有空车）装要买的$n$件商品，里面有一些是凳子。$\mathrm{Polycarpus}$希望用最少的钱来买这些东西。

## 说明/提示

在样例$1$中，购物车有$2$架，其中一架装商品$1$（凳子）和$2$（其他），另一架装商品$3$（凳子），这样安排便可以使价格最低。

对于$100\%$的数据，$1\leq n,k\leq 10^3$，$1\leq c_i\leq 10^9$，$1\leq t_i\leq 2$。

## 样例 #1

### 输入

```
3 2
2 1
3 2
3 1
```

### 输出

```
5.5
2 1 2
1 3
```

## 样例 #2

### 输入

```
4 3
4 1
1 2
2 2
3 2
```

### 输出

```
8.0
1 1
2 4 2
1 3
```

# 题解

## 作者：Daidly (赞：11)

这是一道较为麻烦的思维题（码量题），写篇题解来庆祝一下。

## 题目思路

首先，我们要知道，这个“凳子”它的作用是什么？

——让**自己**或者**一个价格比自己低的物品**半价。

设一个凳子价格为 $p$ 元，一个价格比凳子低的物品 $q$ 元，$p>q$，则你认为：$\frac{p}{2}$ 大呢，还是 $\frac{q}{2}$ 大呢？

当然是**让一个凳子半价**节省更多啊！如果你理解到了这里，那么你就成功一半了。

我采用两个结构体来解决这道题：
```cpp
struct node{
    double value;//价格（要用double）
    int num;//标号
};
node a[1005];//凳子
node b[1005];//物品
```
输入，将凳子与物品分开放：
```cpp
int lena=1,lenb=1;
cin>>n>>k;
for(int i=1;i<=n;++i){
	cin>>x>>y;
	if(y==1)a[lena].value=x,a[lena].num=i,lena++;
	else b[lenb].value=x,b[lenb].num=i,lenb++;
}lena--,lenb--;//多记了一个
```
其中，$lena,lenb$分别指凳子和物品的总数量。

将其从大到小排序，便于计算总费用：
```cpp
bool cmp(node p,node q){return p.value>q.value;}
sort(a+1,a+lena+1,cmp);
sort(b+1,b+lenb+1,cmp);
```
然后，通过我们刚才的证明说明先尽可能的把单独一个凳子与一架购物车放在一起：
```cpp
long double ans=0;//这里要用long double
while(t<=k-1&&a[t].value!=0){
	ans+=a[t].value/2;t++;
}
```
接着要确定在剩下那个购物车中的半价情况，是凳子本身还是物品：

```cpp
if(lena>k-1){//当凳子的数量能支持放进每一个购物车中
	if(a[lena].value>b[lenb].value&&b[lenb].value!=0){//这里要判物品是否为零！！！
		b[lenb].value/=2;
	}else{
		a[lena].value/=2;
	}
}
```
现在吧每个凳子和物品的数量都更新完了，就可以加起来算答案了：

```cpp
for(int i=k;i<=lena;++i)ans+=a[i].value;
for(int i=1;i<=lenb;++i)ans+=b[i].value;
cout<<fixed<<setprecision(1)<<ans<<endl;//保留一位小数
```
最后就是统计输出环节，较为复杂，需要知道一个东西：区间 $[l,r]$ 长度为 $r-l+1$。

我分了三类进行讨论：

- $lena<k-1$：凳子的数量不能使每个购物车都有，购物车也不能为空，所以要把物品补充上去（一车放一个就够了）：

凳子：$[1,lena]$；物品：$[lena+1,k-1]$；

剩下的物品都放在一个购物车里面，个数为：$lenb-((k-1)-(lena+1)+1)=lenb-k+1+lena$；

剩下的物品：$[k-lena,lenb]$；

```cpp
for(int i=1;i<=lena;++i)cout<<"1 "<<a[i].num<<endl;
for(int i=lena+1;i<=k-1;++i)cout<<"1 "<<b[i-lena].num<<endl;
int sum=lenb-k+1+lena;
cout<<sum<<" ";
for(int i=k-lena;i<=lenb;++i)cout<<b[i].num<<" ";
```

- $lena=k-1$凳子的数量刚刚能使每个购物车都有，，所以剩下的一个购物车里都是物品：

凳子：$[1,k-1]$；物品：$[1,lenb]$；

```cpp
for(int i=1;i<=lena;++i)cout<<"1 "<<a[i].num<<endl;
int sum=lenb;cout<<sum<<" ";
for(int i=1;i<=lenb;++i)cout<<b[i].num<<" ";
```

- $lena>k-1$凳子的数量能使每个购物车都有，所以剩下的既有凳子也有物品：

凳子：$[1,k-1]$；物品：$[1,lenb]$；

剩下的凳子和物品都放在一个购物车里面，个数为：$lenb+((lena)-(k)+1)=lenb+lena+k-1$；

剩下的凳子：$[k,lena]$；

```cpp
for(int i=1;i<=k-1;++i)cout<<"1 "<<a[i].num<<endl;
int sum=lenb+lena-k+1;cout<<sum<<" ";
for(int i=k;i<=lena;++i)cout<<a[i].num<<" ";
for(int i=1;i<=lenb;++i)cout<<b[i].num<<" ";
```
## 完整代码

总复杂度应该是 $O(n\log n)$，这道题总的代码也放一下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,x,y,t=1,lena=1,lenb=1;
struct node{double value;int num;};
bool cmp(node p,node q){return p.value>q.value;}
int main(){
	node a[1005];node b[1005];
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>x>>y;
		if(y==1)a[lena].value=x,a[lena].num=i,lena++;
		else b[lenb].value=x,b[lenb].num=i,lenb++;
	}lena--,lenb--;
	sort(a+1,a+lena+1,cmp);
	sort(b+1,b+lenb+1,cmp);
	long double ans=0;
	while(t<=k-1&&a[t].value!=0){
		ans+=a[t].value/2;t++;
	}
	if(lena>k-1){
		if(a[lena].value>b[lenb].value&&b[lenb].value!=0){
			b[lenb].value/=2;
		}else{
			a[lena].value/=2;
		}
	}
	for(int i=k;i<=lena;++i)ans+=a[i].value;
	for(int i=1;i<=lenb;++i)ans+=b[i].value;
	cout<<fixed<<setprecision(1)<<ans<<endl;
	if(lena<k-1){
		for(int i=1;i<=lena;++i)cout<<"1 "<<a[i].num<<endl;
		for(int i=lena+1;i<=k-1;++i)cout<<"1 "<<b[i-lena].num<<endl;
    	int sum=lenb-k+1+lena;cout<<sum<<" ";
        for(int i=k-lena;i<=lenb;++i)cout<<b[i].num<<" ";
	}else if(lena==k-1){
		for(int i=1;i<=lena;++i)cout<<"1 "<<a[i].num<<endl;
		int sum=lenb;cout<<sum<<" ";
        for(int i=1;i<=lenb;++i)cout<<b[i].num<<" ";
	}else{
		for(int i=1;i<=k-1;++i)cout<<"1 "<<a[i].num<<endl;
	    int sum=lenb+lena-k+1;cout<<sum<<" ";
	    for(int i=k;i<=lena;++i)cout<<a[i].num<<" ";
	    for(int i=1;i<=lenb;++i)cout<<b[i].num<<" ";
	}
	return 0;
}
```
如果这篇题解能帮助您理解这道题的话，哪怕只有一点点，也希望您点个赞，支持一下，谢谢啦！

---

## 作者：MY（一名蒟蒻） (赞：4)

[原题传送门](https://www.luogu.com.cn/problem/CF161B)

## 首先讲一下看这一篇题解的好处
1. 题解区较多题解是分点作答，本篇为同时求解
2. 思路清晰，变量名指向明显
3. 讲解明白，码量较小~~且码风好看~~

首先我的代码比较这篇声称[“本题最短题解”](https://www.luogu.com.cn/blog/Liya2304238405/solution-cf161b)的代码，正确性可以保证。至于这位作者的AC代码，是**抄袭**[这一篇](https://zsf--zs---233.blog.luogu.org/solution-cf161b)的，至于他说的：“读者自证不难”，**我认为纯属是因为不会**。

观点仅代表个人观点，希望管理员大大可以撤下该篇题解。由于我只发现这人抄袭这一篇，无法对其进行举报。

以上吐槽是因为我最烦那种省略重点部分的题解。

---
## 正片开始
我们希望尽量省钱，所以尽量每个购物车都有凳子。

那么先想购物车中有凳子的情况。
1. 现在车里这个凳子最便宜，那么省下这个凳子一半的钱；
2. 现在车里有比这个凳子便宜的东西，那么省下不到这个凳子一半的钱（最便宜的东西的半价）。

观察以上两种情况可知，把凳子单独放一辆车一定最优。商家只是想促销凳子。

最终，一种可行的最优购买方案是将最贵的`k-1`个 (或全部，比如当凳子不够时) 凳子单独放，剩下的购物车放其余的所有物品。

时间复杂度为排序的复杂度$\text{O(nlogn)}$，对于不是凳子的物品可以不排序优化常数，但是并不会对总复杂度产生影响。

细节处理会放在代码注释。

## Code
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n,k,tot,cnt,p[1010][1010];
double ans;
struct node {int id; double v;} chair[1010],sold[1010];//tot:chair cnt:not chair
bool cmp(const node &a,const node &b) {return a.v < b.v;}//从大到小排序

int main()
{
//	freopen("work.in","r",stdin); freopen("my.out","w",stdout);
	scanf("%d%d",&n,&k);
	double c;
	for(int i=1,t;i<=n;i++)
	{
		scanf("%lf%d",&c,&t);//分别处理
		if(t == 1) chair[++tot]=(node) {i,c};
		else sold[++cnt]=(node) {i,c};
	}
	sort(chair+1,chair+1+tot,cmp);
	sort(sold+1,sold+1+cnt,cmp);
	int num=tot;
	for(int i=1;i<k && i<=num;i++) {ans+=chair[tot].v*1.0/2.0; p[i][++p[i][0]]=chair[tot--].id;}
	if(num >= k)//装得完k-1
	{//注意这里的!cnt，如果不加的话，结构体内变量有可能初始为0导致答案偏差
		if(!cnt || chair[1].v < sold[1].v) chair[1].v*=1.0/2.0;//不止k-1个凳子的情况可以合并处理
		else sold[1].v*=1.0/2.0;//半价
		for(int i=1;i<=tot;i++) {ans+=chair[i].v; p[k][++p[k][0]]=chair[i].id;}//这里的p数组是第二问的答案数组
		for(int i=1;i<=cnt;i++) {ans+=sold[i].v; p[k][++p[k][0]]=sold[i].id;}//加上剩下的
	}
	else//装不满k-1个
	{
		for(int i=num+1;i<k;i++) {ans+=sold[cnt].v; p[i][++p[i][0]]=sold[cnt--].id;}
		for(int i=1;i<=cnt;i++) {ans+=sold[i].v; p[k][++p[k][0]]=sold[i].id;}
	}
	printf("%.1lf",ans);
	for(int i=1;i<=k;i++)
	{
		printf("\n%d",p[i][0]);
		for(int j=1;j<=p[i][0];j++) printf(" %d",p[i][j]);
	}//输出
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
## $\text{Thank you for your reading!}$
您的点赞和评论是对作者最大的支持！点个赞再走嘛。

---

## 作者：K2sen (赞：2)

## CF161B Discounts

### 题目大意
给你好多商品和购物车，要求购物车必须要填满

等你买的时候，超市这个时候和你说，

你买的凳子，一个凳子能让你买的这个凳子所在的购物车里边价格最小的商品价格减半

然后你想要最省钱，但是你不会怎么摆，问你怎么放商品最省钱.

### 思路

首先，因为一个购物车中有一个凳子，把这个购物车中价格最小的商品的价格减半.

我们把凳子的价格看做$val_d$, 把最小的商品价格看做$val_m$

显然$val_m \leq val_d $, 所以在一个购物车中如果放上一个凳子和一个比凳子价格小的商品肯定不如直接放一个凳子省钱.

那么如果一个购物车中放一个凳子和一个比他价格还要大的商品，那么和在购物车中直接放一个凳子在省钱方面没有什么区别.

所以我们就直接在购物车中放上一个凳子就行了.

然后，如果凳子数>k-1怎么办（因为最后一个购物车要放其他的商品）？？？

这个时候我们如果想要最大化省钱的数，那就要把价格高的商品先放到前边,

这个时候我们就能得出我们sort的方式,, 那就是凳子放到前边，然后凳子中价格较大的放到前边，也就是这个亚子.

```cpp
bool cmp(node a, node b) {
	if (a.deng == b.deng && a.deng == 1) {
		return a.val > b.val;
	} else return a.deng < b.deng;
}
```
然后考虑等字数==k-1的时候

那就是，把凳子都放到购物车中，然后最后一个放上商品.

最后的凳子数==k-1的时候很简单自己想吧.

### code
```cpp
/*
	time:2020.4.25
	Auther:_Destiny
*/
#include <bits/stdc++.h>
#define ll long long
#define N 100010
#define M 1010

using namespace std;
int n, k, ds;
struct node {
	double val;
	int ma, deng;
}pro[M];

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ (48)), ch = getchar();
	return f ? -s : s;
}

bool cmp(node a, node b) {
	if (a.deng == b.deng && a.deng == 1) {
		return a.val > b.val;
	} else return a.deng < b.deng;
}

int main() {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) {
		pro[i].val = read(), pro[i].deng = read();
		if (pro[i].deng == 1) ds++;
		pro[i].ma = i;
	}
	sort(pro + 1, pro + n + 1, cmp);
	if (ds > k - 1) {
		double ans = 0;
		for (int i = 1; i <= k - 1; i++)
			ans += pro[i].val / 2;
		double minn = 1e9;
		for (int i = k; i <= n; i++) {
			ans += pro[i].val;
			minn = min(minn, pro[i].val);
		}
		ans -= minn; ans += minn / 2;
		printf("%.1lf\n", ans);
		for (int i = 1; i <= k - 1; i++)
			printf("1 %d\n", pro[i].ma);
		printf("%d ", n - k + 1);
		for (int i = k; i <= n; i++) 
			printf("%d ", pro[i].ma);
	} else if (ds == k - 1) {
		double ans = 0;
		for (int i = 1; i <= k - 1; i++)
			ans += pro[i].val / 2;
		for (int i = k; i <= n; i++)
			ans += pro[i].val;
		printf("%.1lf\n", ans);
		for (int i = 1; i <= k - 1; i++)
			printf("1 %d\n", pro[i].ma);
		printf("%d ", n - k + 1);
		for (int i = k; i <= n; i++) 
			printf("%d ", pro[i].ma);
	} else {
		double ans = 0;
		for (int i = 1; i <= ds; i++)
			ans += pro[i].val / 2;
		for (int i = ds + 1; i <= n; i++)
			ans += pro[i].val;
		printf("%.1lf\n", ans);
		for (int i = 1; i <= ds; i++)
			printf("1 %d\n", pro[i].ma);
		for (int i = ds + 1; i <= k - 1; i++)
			printf("1 %d\n", pro[i].ma);
		printf("%d ", n - k + 1);
		for (int i = k; i <= n; i++)
			printf("%d ", pro[i].ma);
	}
}
/*
5 2
3 1
3 2
2 1
2 2
4 1
*/
```

---

## 作者：_Album_ (赞：2)


Upd：由于书写时一时粗心，将Blog地址放成了localhost。麻烦管理员重新审核

[更好的阅读](https://payphone-x.github.io/2019/10/16/CF161B/)

-------------

### 题目分析

我们先只考虑单个凳子的情况，显然，一个凳子只能让自己或者一个价格比自己低的东西半价。

而题目中让我们最小化价格，即让省下的钱最多。因此，我们尽量多的让一个凳子单独在一个购物车中。

显然，这个最大值为$k - 1$。因为你还要留出一辆购物车来存储其他的物品。

但这还不够。如果凳子的数量小于$k - 1$的话，我们就把所有的凳子半价，然后原价买下其他商品即可

剩下的见代码注释。

-----------

### Code[Accetped]

```Cpp
#include <bits/stdc++.h>

#define ll long long
#define I inline
#define N 100001

using namespace std;

int n , k;

struct Node{
    long double val;    //题目要求输出一位小数，因此要开long double
    int num;
    int str;
}node[N];

int cnt;
long double ans_num;

bool cmp(Node a , Node b){      
    if(a.str == b.str == 1){       //如果他们都是凳子，就把价值大的放在前边。
        return a.val > b.val;
    }                           
    else{                       //否则，将凳子放在前边
        return a.str < b.str;
    }
}

pair<int  , int > ans[N];

int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> node[i].val >> node[i].str;
        node[i].val *= 1.0;
        node[i].num = i;
        if(node[i].str == 1){
            cnt ++;     //记录凳子的数量
        }
    }
    sort(node + 1 , node + 1 + n , cmp);
    if(cnt > k - 1){        //分类讨论，当凳子数量大于购物车数量-1时
        for(int i = 1; i <= k - 1; i ++){
            node[i].val /= 2;
            ans_num += node[i].val;
            ans[i] = make_pair(1 , node[i].num);
        }
        long double minn = 0x3f3f3f3f;
        for(int i = k; i <= n; i ++){
            ans_num += node[i].val;
            if(node[i].val < minn){
                minn = node[i].val;
            }
        }
        ans_num -= minn;
        ans_num += minn / 2;
        cout << fixed << setprecision(1) << ans_num << "\n";
        for(int i = 1; i <= k - 1; i ++){
            cout << ans[i].first << " " << ans[i].second << "\n";
        }
        cout << n - k + 1 << " ";
        for(int i = k; i <= n; i ++){
            cout << node[i].num << " ";
        }
        puts("");
    }
    else if(cnt == k - 1){  //当凳子数量等于购物车数量-1时
        for(int i = 1; i <= k - 1; i ++){
            node[i].val /= 2;
            ans_num += node[i].val;
            ans[i] = make_pair(1 , node[i].num);
        }
        for(int i = k; i <= n; i ++){
            ans_num += node[i].val;
        }
        cout << fixed << setprecision(1) << ans_num << "\n";
        for(int i = 1; i <= k - 1; i ++){
            cout << ans[i].first << " " << ans[i].second << "\n";
        }
        cout << n - k + 1 << " ";
        for(int i = k; i <= n; i ++){
            cout << node[i].num << " ";
        }
        puts("");
    }
    else{   //当凳子数量小于购物车数量-1时
        for(int i = 1; i <= cnt; i ++){
            node[i].val /= 2;
            ans_num += node[i].val;
            ans[i] = make_pair(1 , node[i].num);
        }
        for(int i = cnt + 1; i <= n; i ++){
            ans_num += node[i].val;
        }
        cout << fixed << setprecision(1) << ans_num << "\n";
        for(int i = 1; i <= cnt; i ++){
            cout << ans[i].first << " " << ans[i].second << "\n";
        }
        for(int i = cnt + 1; i <= k - 1; i ++){
            cout << 1 << " " << node[i].num << "\n";
        }
        cout << n - k + 1 << " ";
        for(int i = k; i <= n; i ++){
            cout << node[i].num << " ";
        }
        puts("");
    }
    return 0;
}
```

---------------------

# THE END

---

## 作者：幽灵特工 (赞：2)

# 本题最短题解！！！

### 小学生秒懂系列

[欢迎进入blog查看你的小学生秒懂系列都更新了啥](https://www.luogu.com.cn/blog/Liya2304238405/#type=%E9%A2%98%E8%A7%A3)



本题虽然是蓝题，但是我认为凡是了解贪心思想的都可以吊打本题。~~（如果没有掉到陷阱的话）~~

## 贪心思路

    k辆凤凰牌购物车，只留一辆凤凰牌购物车装非凳子货物，其他k-1辆凤凰牌购物车全部装最贵的凳子，且每辆凤凰牌购物车只装一个。
    
   非形式化证明如下：

------------

   
   - 尽可能多给每辆凤凰牌购物车都配备最先进的凳子：对于其他$k-1$辆凤凰牌购物车，如果没有装凳子，那么享受不到任何优惠，不如给这辆凤凰牌购物车装个凳子。所以应该尽可能满足所有凤凰牌购物车里都有凳子。当凳子数量小于k时会不能满足，楼下的题解都考虑了这种细节~~非常合理~~，但事实上可以省略这次判断，代码内会说明。
   
   - $k-1$辆凤凰牌购物车装且只装一个最贵的凳子（价格记为$A$）：假设装了一个凳子和其他商品或凳子（价格记为$B$）. 情况$1$，$B$比原来的凳子便宜，那么优惠了$B/2$；情况$2$，$B$贵了，那么优惠了$A/2$，情况$2$时$B$不可能是凳子（上文题设）；情况$3$，$A=B$，优惠$A/2$。再来看不装$B$的情况$0$，优惠$A/2$。所以无论装不装$B$，最多只能优惠$A/2$。所以可以当作没有装$B$。这样就与把$B$装在之前“只留一辆”凤凰牌购物车里优惠一样。
   
   
   - $k-1$辆凤凰牌购物车里，装的凳子越贵优惠越多。虽然这是一篇小学生秒懂题解但我觉得这个也不用详细证明了。
   
 下面上计算总价的代码！
 
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,dz=0,qt=0;
double dengzi[1005],qita[1005],ans=0.0;//凳子，其他，答案（总价格） 
bool cmp(double a,double b){return a>b;}
int main()
{
    cin>>n>>k;
    int a,b;
    for(int i=0;i<n;i++){
    	cin>>a>>b;
    	if(b==1)dengzi[dz++]=a;
		else qita[qt++]=a;
	}
	sort(dengzi,dengzi+dz,cmp);//降序，降序，一定要降序！ 
	sort(qita,qita+qt);
	for(int i=0;i<k-1;i++)ans+=dengzi[i]/2.0;//不管凳子数量与k-1的关系 ，都算前k-1贵的凳子半价（凳子少了就会是0元） 
	for(int i=k-1;i<dz;i++)ans+=dengzi[i];//多的凳子原价，除了…… 
	for(int i=0;i<qt;i++)ans+=qita[i];//所有其他商品原价，除了…… 
	if(dz>=k)ans-=min(qita[0],dengzi[dz-1])/2.0;//除了最后一辆车里与凳子同装的最便宜的那个！ 
	cout<<fixed<<setprecision(1)<<ans<<endl;//以上是输出价格	 
    return 0;
}
```

至于输出方案，由于题目说输出任意即可，那么用寥寥$5$行即可。给出思路：

```
根据题意可知易得
容易证明显然成立
稍加思考不证自明
不如留作读者练习
```
ok，感谢大家阅读我的题解，我是幽灵特工，我们下期见！


---

## 作者：XL4453 (赞：1)


诈骗题，包括但不限于优惠是诈骗以及题目难度是诈骗。评个黄差不多了吧。

---
### 解题思路：

这种优惠方法最诈骗的地方在这里：假设现在有一个装了一个凳子的购物车，如果往里面放一个其他物品：如果这个物品的价值比这个凳子大，那么自然优惠不到它，如果这个物品的价值没有这个等凳子大，那么优惠掉的价格显然是变小了的。

顺着这个思路往下想，考虑尽量将所有的凳子单独放一个购物车，如果不能就把所有的堆到一个购物车里。

所以把所有的物品按照是否为凳子为第一关键字从小到大（是凳子在前面），价值为第二关键字从大到小排序。然后直接从前往后取，一开始的 $k-1$ 个单独放，最后一个塞满。

需要注意的是如果最后一个里有凳子需要在最后一个购物车里找一个价值最小的优惠一下。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct str{
	int ch,id,val;
	bool operator <(const str a)const{
		if(ch==a.ch)return val>a.val;
		else return ch<a.ch;//1-1 2-0
	}
}t[1003];
int n,k;
double ans;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&t[i].val,&t[i].ch);
		t[i].id=i;
	}
	sort(t+1,t+n+1);
	for(int i=1;i<=k-1;i++)ans+=(t[i].ch==1?0.5:1)*t[i].val;
	for(int i=k;i<=n;i++)ans+=t[i].val;
	if(t[k].ch==1){
		int minx=2147483647;
		for(int i=k;i<=n;i++)
		minx=min(minx,t[i].val);
		ans=ans-0.5*minx;
	}
	printf("%.1f\n",ans);
	for(int i=1;i<=k-1;i++)printf("1 %d\n",t[i].id);
	printf("%d",n-k+1);
	for(int i=k;i<=n;i++)printf(" %d",t[i].id);
	printf("\n");
	return 0;
}
```

---

## 作者：yu__xuan (赞：1)

### 题目
[CF161B Discounts](https://www.luogu.org/problem/CF161B)

### 思路
贪心。很显然对于一个板凳（价格为`c`）所能使我们最多少花费$\frac{c}{2}$的金钱。

原因如下：

* 一个凳子可以半价买掉这架购物车里最便宜的商品

* 如果你将一件价格比该板凳大的商品与板凳放在一起没有贡献。

* 如果你将一件价格比该板凳小的商品与板凳放在一起贡献减小。

贪心策略：将板凳中价格前$k-1$大的单独放一辆购物车，板凳不够就用商品即可。

### $Code$
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#include<iomanip>
#define min(a,b) a<b?a:b

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

inline void write(int x) {
	if(x<0) putchar('-'),write(-x);
	else {
		if(x/10) write(x/10);
		putchar(x%10+'0');
	}
}

int n,k;
struct dx {
	int w,type,num;
	friend bool operator <(dx x,dx y) {
		if(x.type==y.type) return x.w>y.w;
		return x.type<y.type;
	}//板凳比其他商品的优先级要高，价格高的比价格低的优先级要高。
}a[1001];

int main() {
	read(n),read(k);
	for(int i=1;i<=n;++i) {
		read(a[i].w),read(a[i].type);a[i].num=i;
	}
	std::sort(a+1,a+n+1);//排序,如此排序后将做法转化为了将k-1间商品单独放一辆购物车，剩余商品放入最后一辆购物车。 
	double cost=0;bool f=0;
	int minn=0x7fffffff; 
	for(int i=1;i<=n;++i) {
		if(i<=k-1) {
			if(a[i].type==1) cost+=a[i].w*1.0/2.0;
			else cost+=a[i].w*1.0;
		}else {
			cost+=a[i].w*1.0;
			minn=min(minn,a[i].w); 
			if(a[i].type==1) f=1;//如果剩余商品中有个板凳的话要价格减半。 
		}
	}
	if(f) cost-=minn*1.0/2.0;
	std::cout<<std::fixed<<std::setprecision(1)<<cost<<'\n';//注意保留一位小数 
	for(int i=1;i<=k-1;++i) {
		printf("1 %d\n",a[i].num);
	}
	printf("%d ",n-k+1);
	for(int i=k;i<=n;++i) {
		printf("%d ",a[i].num);
	}
	puts("");
	return 0;
}
```

---

## 作者：C_Zn (赞：1)

[题目传送门](http://codeforces.com/problemset/problem/161/B)
### 题意
你要去买  $n$ 个东西，你有 $k$ 个购物车，然而买的东西有两种，为凳子和铅笔，如果这个购物车里面有凳子，那么里面最便宜的物品打五折。

### 解题方法
我们的目标就是让打折的钱数尽量多，然而我们发现如果有凳子，打折的价格只会是价格小于等于这个凳子价格的，那么我们就把前 $k-1$大的凳子单独拿出来打折，剩下的放在最后的购物车里面，当然如果凳子数小于等于$k-1$，把后面的慢慢放满就可以了

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int num,pos;
};
node a[20001];
node b[20001];
struct trans
{
	int tot;
	int s[2001];
}ans[2001];
int tot1,tot2;
bool comp(node x,node y)
{
	return x.num>y.num;
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int x,zkt;
		scanf("%d%d",&x,&zkt);
		if(zkt==1)
		{
			tot1++;
			a[tot1].num=x;
			a[tot1].pos=i;
		}
		else
		{
			tot2++;
			b[tot2].num=x;
			b[tot2].pos=i;
		}
	}
	sort(a+1,a+tot1+1,comp);
	double anstot=0;
	for(int i=1;i<=min(k-1,tot1);i++)
	{
		ans[i].tot++;
		ans[i].s[ans[i].tot]=a[i].pos;
		anstot+=a[i].num*0.5;
	}
	if(tot1<=k-1)
	{
		for(int i=1;i<=tot2;i++)
		{
			anstot+=b[i].num;
			ans[min(tot1+i,k)].tot++;
			ans[min(tot1+i,k)].s[ans[min(tot1+i,k)].tot]=b[i].pos;
		}
	}
	else
	{
		int minn=1e9;
		for(int i=k;i<=tot1;i++)
		{
			anstot+=a[i].num;
			ans[k].tot++;
			ans[k].s[ans[k].tot]=a[i].pos;
			minn=min(a[i].num,minn);
		}
		for(int i=1;i<=tot2;i++)
		{
			anstot+=b[i].num;
			ans[k].tot++;
			ans[k].s[ans[k].tot]=b[i].pos;
			minn=min(b[i].num,minn);
		}
		anstot-=minn*0.5;
	}
	printf("%.1lf\n",anstot);
	for(int i=1;i<=k;i++,puts(""))
	{
		cout<<ans[i].tot<<" ";
		for(int j=1;j<=ans[i].tot;j++)
		  cout<<ans[i].s[j]<<" ";
	}
	return 0;
}
```


---

## 作者：Liuhy2996 (赞：0)

## 思路
注意到把凳子与其他物品放一起一定不会优惠更多，所以 $k-1$ 个凳子单独一个购物车，其他放一起。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,mn=1e18;
double sum;
vector<int>ans[200005];
struct node{
	int c,t,pos;
}a[200005];
bool cmp(node x,node y){
	if(x.t!=y.t) return x.t<y.t;
	return x.c>y.c;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i].c>>a[i].t,a[i].pos=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<k;++i){
		if(a[i].t==1) sum+=a[i].c/2.0;
		else sum+=a[i].c;
		ans[i].push_back(a[i].pos);
	}
	for(int i=k;i<=n;++i){
		ans[k].push_back(a[i].pos);
		sum+=a[i].c;
		mn=min(mn,a[i].c);
	}
	if(a[k].t==1) sum-=mn/2.0;
	printf("%.1f\n",sum);
	for(int i=1;i<=k;++i){
		cout<<ans[i].size()<<' ';
		for(int j:ans[i]) cout<<j<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：water_tomato (赞：0)

[博客版本](https://code.watertomato.com/cf161b-discounts-%e9%a2%98%e8%a7%a3/)

## 解析

[题目链接](https://www.luogu.com.cn/problem/CF161B) 题意很清晰了。

我们考虑凳子的折扣情况。由于凳子本身也是一个物品，那么如果存在一个比凳子贵的物品在购物车中，那么打折的是凳子，如果有一个比凳子便宜的物品在购物车中——那还不如给凳子打折呢！合着这个商场就是给凳子打折而已。

因此，由于凳子的打折情况最优就是给自己打折，那么我们将凳子按照价格排序，对于前 $k-1$ 辆购物车，每辆购物车都放一辆凳子，然后剩下的东西全塞最后一辆车里。

在凳子不够的时候再特判一下就好了，详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1005;
struct node{
	int c,t,id;
}a[N];
int n,k,cnt;
double ans;
inline bool cmp(node i,node j){//先类型，再单价
	if(i.t!=j.t) return i.t<j.t;
	return i.c>j.c;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].c,&a[i].t);
		a[i].id=i;
		if(a[i].t==1) cnt++;
		ans+=a[i].c;
	}
	sort(a+1,a+1+n,cmp);
	if(cnt>=k-1){//凳子够前 k-1 辆车
		for(int i=1;i<=k-1;i++) ans-=0.5*a[i].c;
		if(cnt>=k)//够不够最后一辆车
			ans-=min(a[cnt].c,a[n].c)*0.5;//凳子和其他商品中最便宜的一个也要打折
	}
	else{//凳子不够
		for(int i=1;i<=cnt;i++){
			ans-=0.5*a[i].c;
		}
	}
	printf("%.1lf\n",ans);
	for(int i=1;i<=k-1;i++){
		printf("1 %d\n",a[i].id);
	}
	printf("%d ",n-k+1);
	for(int i=k;i<=n;i++)
		printf("%d ",a[i].id);
	return 0;
}
```



---

## 作者：Sue_Shallow (赞：0)

### Discounts

>  超市打折，如果购物车里有至少一个凳子，则可半价购买购物车里最便宜的一个物品。
>
>  现在你要购买$n$个物品，其中一些是凳子。你有$K$个购物车，求一个最优的购买方案，使得花费的价格最少。
>
> $k \leq n \leq 10 ^ 5$

[Codeforces 161B](https://codeforces.com/problemset/problem/161/B)

贪心策略：对于所有的凳子，最好的情况是独占一个购物车。因此最好的决断是对于所有的凳子，使其尽量独占一个购物车，如果不能使所有的凳子独占一个购物车（K - 1 < 凳子数），则将所有的凳子按降序排序之后从前往后填充，然后将剩下的凳子和非凳子的物品都放到最后一个购物车当中。

策略非常简单，但是写起来很麻烦，需要分类讨论$K - 1$和凳子数的关系，很是烦人，建议大家写一写，很能锻炼码力的。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std ;
typedef long long LL ;
const int MAXN = 1010 ;
const int MAXM = 1010 ;
const int INF = 0x7fffffff ;
int N, K, C_T, O_T ;
double Ans ;
struct NODE {
	int C, T, ID ;
}	E[MAXN], Chair[MAXN], Othe[MAXN] ;

inline int Read() {
	int X = 0, F = 1 ; char ch = getchar() ;
	while (ch > '9' || ch < '0') F = (ch == '-' ? - 1 : 1), ch = getchar() ;
	while (ch >= '0' && ch <= '9') X=(X<<1)+(X<<3)+(ch^48), ch = getchar() ;
	return X * F ;
}

inline bool CMP(NODE A, NODE B) {
	return A.C > B.C ;
}

int main() {
	N = Read() ; K = Read() ;
	for (int i = 1 ; i <= N ; i ++)
		E[i].C = Read(), E[i].T = Read(), E[i].ID = i ;
	for (int i = 1 ; i <= N ; i ++)
		if (E[i].T == 1) Chair[++ C_T] = E[i] ;
	for (int i = 1 ; i <= N ; i ++)
		if (E[i].T == 2) Othe[++ O_T] = E[i] ;
	sort(Chair + 1, Chair + C_T + 1, CMP) ;
	if (C_T > K - 1) {
		for (int i = 1 ; i <= K - 1 ; i ++)
			Ans += (double) Chair[i].C / 2 ;
		int Min = INF ;
		for (int i = 1 ; i <= O_T ; i ++)
			Ans += Othe[i].C, Min = min(Min, Othe[i].C) ;
		for (int i = K ; i <= C_T ; i ++)
			Ans += Chair[i].C, Min = min(Min, Chair[i].C) ;
		Ans -= (double) Min / 2 ;

	}
	if (C_T <= K - 1) {
		for (int i = 1 ; i <= C_T ; i ++)
			Ans += (double) Chair[i].C / 2 ;
		for (int i = 1 ; i <= O_T ; i ++)
			Ans += Othe[i].C ;
	}
	printf("%.1lf\n", Ans) ;
	if (C_T >= K - 1) {
		for (int i = 1 ; i <= K - 1 ; i ++)
			cout << "1 " << Chair[i].ID << endl ;
		cout << O_T + C_T - K + 1 << " " ;
		for (int i = K ; i <= C_T ; i ++)
			cout << Chair[i].ID << " " ;
		for (int i = 1 ; i <= O_T ; i ++)
			cout << Othe[i].ID << " " ;
		cout << endl ;
	}
	if (C_T < K - 1) {
		for (int i = 1 ; i <= C_T ; i ++)
			cout << "1 " << Chair[i].ID << endl ;
		for (int i = 1 ; i <= K - C_T - 1 ; i ++)
			cout << "1 " << Othe[i].ID << endl ;
		cout << O_T - K + C_T + 1 << " " ;
		for (int i = K - C_T ; i <= O_T ; i ++)
			cout << Othe[i].ID << " " ;
	}
	return 0 ;
}

```

---

