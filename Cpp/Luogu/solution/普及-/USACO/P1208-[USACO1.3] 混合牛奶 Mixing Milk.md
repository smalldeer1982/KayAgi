# [USACO1.3] 混合牛奶 Mixing Milk

## 题目描述

由于乳制品产业利润很低，所以降低原材料（牛奶）价格就变得十分重要。帮助 Marry 乳业找到最优的牛奶采购方案。

Marry 乳业从一些奶农手中采购牛奶，并且每一位奶农为乳制品加工企业提供的价格可能相同。此外，就像每头奶牛每天只能挤出固定数量的奶，每位奶农每天能提供的牛奶数量是一定的。每天 Marry 乳业可以从奶农手中采购到小于或者等于奶农最大产量的整数数量的牛奶。

给出 Marry 乳业每天对牛奶的需求量，还有每位奶农提供的牛奶单价和产量。计算采购足够数量的牛奶所需的最小花费。

注：每天所有奶农的总产量大于 Marry 乳业的需求量。

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据：  
$0 \le n,a_i \le 2 \times 10^6$，$0\le m \le 5000$，$0 \le p_i \le 1000$

题目翻译来自 NOCOW。

USACO Training Section 1.3

## 样例 #1

### 输入

```
100 5
5 20
9 40
3 10
8 80
6 30
```

### 输出

```
630
```

# 题解

## 作者：杨咩咩咩啊 (赞：485)

第一篇题解吖

###  关键词：暴力，排序，AC。


先说下思想，建议看懂的自己做不要看代码，实在不会(~~或者被我这毫无章法的语言恶心到了的~~)再去看看(~~我那丑不拉几的~~)代码吧~  


### 思路：  
1，先按照**单价**排序，**单价小**的在前面； 单价**一样**的就把**产量多**的放前面；（我是用**结构体**做的，排序方便）  

2，当还需要采购时（**n不为零**），我们从**当前还需采购值**开始，挨个**减一**，**总价钱加上当前最小单价**，当这头牛**产量为零**（不能再从它购买时），换一头牛（**数组加一**），直到购买完（**n=0**）为止。

3，输出**总价钱**，等待评测，然后**AC**;

## 下面是代码：

```cpp
/*(^-^)*/
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int n,m,ans;//总需求量，提供的个数，总价；

struct node
{
    int a,b;//牛奶单价和产量
}a[5005];//定义结构体

bool cmp(node a,node b)
{
    if(a.a!=b.a)return a.a<b.a;
    else return a.b>b.b;
}//好我们定义一个判断函数，条件见思路1；

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    	cin>>a[i].a>>a[i].b;
    sort(a+1,a+1+m,cmp);//用刚定义的函数给它排序
    int i=1;
    while(n)//从n开始减起，直达n为零停止
    {
        if(a[i].b!=0)//当这头牛还没购买完
        {
            a[i].b--;//这头牛可购买数减一
            ans+=a[i].a;//总花费加上这头牛的单价（或者说当前最小单价）
            n--;//需求量减一
        }
        else i++;//购买完了换头牛
    }
    cout<<ans;
    return 0;
}
```
审核真好看！~~给过吧QWQ（女生学oi不容易！）~~

---

## 作者：青陌 (赞：130)

第一篇题解（各位帮忙点个赞）
先输入，再用单价进行排序
先用一个tot记录当前数量，如果当前数量小于于等于所求数量，用sum记录当前所用钱数，因为用单价从小到大排了序，所以当当前数量大于所求数量时，此时的总价就是最小的钱数
```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxn=2000000+5;

struct cow{
	int p,a;
	cow(int p=0,int a=0): p(p),a(a){}
}milk[maxn];

/*bool operator<(const cow& u, const cow& v)
{
	return u.p < v.p;
}*/
bool cmp(const cow &a,const cow &b)
{
   return a.p<b.p;
}
int main (){
	int n,m,dj;
	cin>>n>>m;
	for (int i=0;i<m;i++){
		cin>>milk[i].p>>milk[i].a;
	}
	sort(milk,milk+m,cmp);
	int tot=0,sum=0;
	for (int i=0;i<m;i++){
		if (tot+milk[i].a<=n) {
			tot+=milk[i].a;
			sum+=milk[i].p*milk[i].a;
		}
		else {
			sum+=(n-tot)*milk[i].p; 
			break;
		}
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：谬悠 (赞：61)

其实这道题已经有很多题解了，我这种解法其实有很多发了

~~所以我只是来划水的~~

我只是想给大家一些细节上的建议

具体会放在代码中

```cpp
#include<iostream>//之所以我打了那么多头而不用万能头
#include<cstdio>//是因为万能头据说有很多不好的地方
#include<algorithm>//例如传说中要占2mb内存
#include<cstring>//例如有些函数容易出错
#include<cmath>//以及你有些变量名和不知哪里的函数重复导致RE
#include<set>//而且这些头是可以复制粘贴的，不需要额外的时间
#include<string>//竞赛中也不让用万能头
#include<stack>
#include<queue>
using namespace std;
struct bao//开结构体耍子，其实结构体最大的好处就是看着舒服
{//条理清晰，不容易遗忘自己哪些变量是干什么的233
	int dan;//单价
	int shu;//数量
}bei[10000];//数组名字，数据最大5000但只要空间允许开双倍比较舒服，5005这种写法有些时候会莫名RE
bool com(bao x, bao y) {
	return x.dan <= y.dan;//自定义比较函数，由于单价相同并不会有其他影响，所以没必要去判断数量
}
int  num,ans,fei=0,k=0;//需求，牧民数量，所花的钱，一个开关
int main() {
	cin >> num >> ans;
	for (int i = 0; i < ans; i++) {//从零开始，可以使代码更整洁一点
		cin >> bei[i].dan >> bei[i].shu；//直接读入
	}
	sort(bei, bei + ans, com);//如果从一开始这里就会更麻烦，还容易出现少打+1导致RE的情况；
	while (num > 0) {//while挺好用的，注意没有等于号
		if (bei[k].shu <= num) {
			num -= bei[k].shu;//我们还需要的数量在不断减少
			fei +=( bei[k].shu*bei[k].dan);//累加费用
		}
		else {		//到了这里，就是最后一个了，我们不需要那么多牛奶了
			fei += (num*bei[k].dan);//按需求算
			num = 0；
		}
		k+=1;//完成依次访问
	}
	cout << fei;//输出
	return 0;
	//结束了，AC；
	while (1);
}
```


望通过
本灰名蒟蒻第一篇题解//这是第二个号，刚创所以灰名233
QwQ
给个赞鸭

---

## 作者：lili_flyingcutter (赞：29)

#需排序

```cpp
struct n{
    int a;int b;
}t[5002];//结构体
bool cmp(n x,n y)
{return x.a < y.a;
}
int main()
{
    int n,m,i,sum=0;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++)
    scanf("%d%d",&t[i].a,&t[i].b);//输入
    sort(t,t+m,cmp);i=0;//排序
    while(1){
        if(n>t[i].b){sum+=t[i].a*t[i].b;n-=t[i].b;
        }else {sum+=n*t[i].a;break;}i++;//累加
    }printf("%d",sum);输出
}
```

---

## 作者：Z_Ovids (赞：28)

# 这道题我和大家好像都不一样！

### 咳咳，好趴实际上就是一种比较好理解的笨方法，但是在写的时候会有一点容易出现思路不清晰的状况。但是只要一边做一边理解就不会出问题。
首先我们来看看这道题我的思路：

------------

第一：建立变量与变量之间的关系
如图所示：![](https://cdn.luogu.com.cn/upload/pic/65551.png)
OK，我们接着来。

------------

第二步：开始分析题目，首先我们先来看这个题目的要求，是求最小的费用，那么我们很容易就可以想到，我们可以用一个排序，将最小费用的排在前面，因为我们是拿每一个最小费用所对应的数量去叠加，直到超过ALL这个指标。
### 那么问题来了，怎么在排完序后再用他的ＭＯＮＥＹ呢？
上代码：
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int mx=2000000;
int money[mx];
int num[mx];
int xu[mx];
int n,all,cnt=0,tem;
int main(){
	scanf("%d%d",&all,&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&money[i],&num[i]);
		xu[money[i]]=i;
	}
	sort(money+1,money+1+n);
	for(int i=1;i<=n;i++){
    　　　　　　（　　　　　　　　）！！！
		if(cnt<all&&cnt+num[xu[money[i]]]<=all)
		tem+=money[i]*num[xu[money[i]]],
		cnt+=num[xu[money[i]]];
		if(cnt+num[xu[money[i]]]>all)
		tem=tem+money[i]*(all-cnt),cnt=cnt+(all-cnt);
		if(cnt>=all)
		break;	
	}
	else cout<<tem;
	return 0;
}
```
没错，这个ＸＵ就是本题的精髓，我们在循环输入时就可以以数据做下标，然后再来调用，就显得十分方便。
但是用这种方法，要注意一个点，就是代码中的（），那里要加一个特判，来确定重复的ｉ应该怎么处理，这里就不写出来啦，大家也要自己思考哦！

------------

总结一下，这道题解主要是利用了数组下标的灵活性，并且比较好理解，当然也可以用结构体做，这里不再赘述。萌新第一次发题解，有什么不足望大佬轻拍

------------

~~ＱＶＱ帅气管理求过~~

---

## 作者：煮酒论英雄 (赞：23)

话说回来，这应该是一道很好写的题目了，但有个坑在下没注意到。想想也是，有谁会走到商店门口请人帮他算钱，却告诉人家，自己什么都没买？

###### 切入正题

这一题简单到不敢相信它是普及-，明明很入门OK？

不就是输入后排个序，用个双层循环计算一下价钱就能搞定的事吗？

只要注意一下那个输入两个“0”的极端情况就行了。

在下写程序不容易（~~好吧这题很写的很容~~~~易~~），所以在下悄悄加了一个小错误（一个分号），这题很容易，相信大家应该也不屑抄我的题解了吧~

好了好了，上代码，相信大家都看得懂
```cpp

	#include<bits/stdc++.h>
	using namespace std;
	int n,m,s,t;//s代表钱,t代表数量 
	struct milk//这是一个美味的结构体 
	{
		int jg;//价格 
		int cl;//产量 
	}a[2000000];//数组一定要大！！！ 
	bool cmp(milk a,milk b)//这是一个标准的cmp函数，寓意我要用STL 
	{
		if(a.jg==b.jg)//个人认为这句没必要 
			return a.cl>b.cl;//如果单价相等，产量多的在前（真没必要） 
		return a.jg<b.jg；//便宜的在前 
	}
	int main()
	{
		cin>>n>>m;//输入，没话说 
		if(n==0&&m==0)//事实证明有这种奇葩情况 
		{
			cout<<"0";//不信你删了试试？ 
			return 0;
		}
		for(int i=0;i<m;i++)
			cin>>a[i].jg>>a[i].cl;
		sort(a,a+m,cmp);//上吧，我的STL！！！ 
		for(int i=0;i<m;i++)//相当于拜访每家奶商 
		{
			for(int j=1;j<=a[i].cl;j++)//相当于一瓶瓶（桶桶）拿奶 
			{
				s+=a[i].jg;//加上单价 
				t++;//计数 
				if(t==n)//量够了 
				{
					cout<<s;//输出吧 
					return 0;//结束了，该回家了 
				}
			}
		}
	return 0;//嗯……这句貌似不需要了 
	}

```
我相信（莫名自信）大家都能看懂吧？~~看~~~~懂的举个爪！！~~



---

## 作者：如幻 (赞：21)

 P1208 [USACO1.3]混合牛奶 Mixing Milk
 
 
 
题目描述
由于乳制品产业利润很低，所以降低原材料（牛奶）价格就变得十分重要。帮助Marry乳业找到最优的牛奶采购方案。

Marry乳业从一些奶农手中采购牛奶，并且每一位奶农为乳制品加工企业提供的价格是不同的。此外，就像每头奶牛每天只能挤出固定数量的奶，每位奶农每天能提供的牛奶数量是一定的。每天Marry乳业可以从奶农手中采购到小于或者等于奶农最大产量的整数数量的牛奶。

给出Marry乳业每天对牛奶的需求量，还有每位奶农提供的牛奶单价和产量。计算采购足够数量的牛奶所需的最小花费。

注：每天所有奶农的总产量大于Marry乳业的需求量。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;//n需要牛奶的总数,m提供牛奶的农民个数
int tot=0;//tot记录花的钱
struct node
{
    int a,p;
} a[100010];
int cmp(node x,node y)//结构体比较
{
    return x.p<y.p;
}
int main()
{
    cin>>n>>m;
    for(int i=1; i<=m; i++)
        cin>>a[i].p>>a[i].a;
    sort(a+1,a+m+1,cmp);//sort快排
    for(int i=1; i<=m; i++)
        if(n>0)
        {
            if(n>a[i].a)
            {
                n-=a[i].a;
                tot+=a[i].p*a[i].a;
            }
            else if(n<=a[i].a)//因为最后一个农夫的奶用不完
            {
                tot+=a[i].p*n;//看还需多少奶，这里记录钱必须在n--前，要不然就成负数了
                n-=a[i].a;
            }
        }
    cout<<tot;
}

```

---

## 作者：vegetabird (赞：11)

手写一个堆练练手。。。

算法思路很简单，暴力贪心，每次选单价最小的，直到完成任务

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
#define Runtime int
#define Error main
const int ERROR=0;
using namespace std;
inline void getint(int &_int){                            没有什么用的输入优化
    char ch=_int=0;
    while(!isdigit(ch)){
        ch=getchar();
    }
    while(isdigit(ch)){
        _int=_int*10+ch-48;
        ch=getchar();
    }
}
class source{                                            定义一个类来存奶源
```
public:
```cpp
        inline source(int _price=0,int _amount=0){
            price=_price;
            amount=_amount;
        }
        int price;
        int amount;
        inline bool operator <(source _src){                    为后面的堆服务的重载
            return price<_src.price;
        }
        inline bool operator ==(source _src){
            return price==_src.price;
        }
        inline bool operator >(source _src){
            return price>_src.price;
        }
        inline void operator =(source _src){
            price=_src.price;
            amount=_src.amount;
        }
};
template <class tp>                                模板233333
class heap{
```
public:
```cpp
        inline heap(){
            array.clear();
            _size=0;
        }
        inline void push(tp ele){                        向堆里压一个元素
            array.push_back(ele);
            _size++;
            now=_size;
            next=now/2;
            while(next){
                if(array[now-1]>array[next-1]){
                    break;
                }
                swap(array[now-1],array[next-1]);
                now=next;
                next=now/2;
            }
        }
        inline tp pop(){                                                弹出一个元素
            if(!_size){                                    注意！！如果不判断空堆的话
                tp _ret;                                        会在n=0, m=0（就是第二个点）时RE
                return _ret;
            }
            ret=array[0];
            array[0]=array[_size-1];
            array.pop_back();
            _size--;
            now=1;
            next=find_next();
            while(next<=_size){
                if(array[now-1]<array[next-1]){
                    break;
                }
                swap(array[now-1],array[next-1]);
                now=next;
                next=find_next();
            }
            return ret;
        }
```
private:
```cpp
        inline int find_next(){
            t1=now<<1;
            t2=t1+1;
            if(t1>=_size){
                return t1;
            }
            if(array[t1-1]<array[t2-1]){
                return t1;
            }
            return t2;
        }
        inline void swap(tp &p1,tp &p2){
            temp=p1;
            p1=p2;
            p2=temp;
        }
        vector<tp> array;
        tp ret,temp;
        int now,next,t1,t2,_size;
};
int n,m,cnt,tot;
heap<source> hp;
Runtime Error(){
    getint(n);getint(m);
    int i;
    source tmp;
    for(i=1;i<=m;i++){
        getint(tmp.price);getint(tmp.amount);
        hp.push(tmp);
    }
    while(true){
        tmp=hp.pop();                                                找到当前最便宜的奶源
        if(cnt+tmp.amount<n){
            cnt+=tmp.amount;
            tot+=tmp.amount*tmp.price;
        }else{
            tot+=(n-cnt)*tmp.price;
            cnt+=n-cnt;
            break;
        }
    }
    printf("%d\n",tot);
    return ERROR;
}
```

---

## 作者：Uni_Tune (赞：8)

快排+贪心。

首先对于每种牛奶的单价进行排序，但是每种牛奶的单价和数量都必须交换。

然后用贪心，从单价最小的牛奶开始枚举，如果剩下要买的牛奶大于该牛奶数量，就买下所有这种牛奶。

最后当无法买下所有这种牛奶的时候，就买所有能买的。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
void sort(int,int);//快排
struct milk
{
    int v;
    int n;
}a[5001];
void sort(int l,int r)
{
    int i,mid,j,t;
    i=l;j=r;
    mid=a[(l+r)/2].v;
    while(i<=j)
    {
        while(a[i].v<mid)
        {
            i++;
        }
        while(a[j].v>mid)
        {
            j--;
        }
        if(i<=j)
        {
            t=a[i].v;
            a[i].v=a[j].v;
            a[j].v=t;
            t=a[i].n;
            a[i].n=a[j].n;
            a[j].n=t;
            i++;
            j--;
        }
    }
    if(l<j) sort(l,j);
    if(i<r) sort(i,r);
}
long long wmilk;
long long ans=0;
int n;
int main()
{
    scanf("%lld%d",&wmilk,&n);
    int i,j,k=0;
    for(i=1;i<=n;i++)
    {
        cin>>a[i].v>>a[i].n;
    }
    sort(1,n);
    while(wmilk>a[k].n)
    {
        ans+=a[k].v*a[k].n;//装入所有
        wmilk=wmilk-a[k].n;
        k++;
    }
    ans+=wmilk*a[k].v;//装入最后的
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Eternalblue (赞：7)

这题个人感觉比较水。


## 直接贪心就OK了啊（巨贪无比）


贪心策略前面的题解说的比我清楚，我就简略说一下吧：

对花费排序，然后从小到大扫一遍

看看数量是否达到标准 超过的话就平掉


## 注意花费(p[i])和数量(a[i])不要搞混……

至于其他的一些问题**请看代码**

···cpp


```cpp
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define rint register int
const int maxn=5001; 
using namespace std;
inline int read(rint ans=0,rint sgn=' ',rint ch=getchar())   //读入优化，就是个板子，大家看看就好
{
    for(;ch<'0' || ch>'9';sgn=ch,ch=getchar());
    for(;ch>='0' && ch<='9';(ans*=10)+=ch-'0',ch=getchar());
    return sgn-'-'?ans:-ans;
}
struct Node{
    int p,a;
    inline bool operator < (const Node &a) const {    //这里是结构体排序，等价于在结构体外写个bool cmp
        return p<a.p;                                                     //然而在sort函数里面因为默认使用<比较，所以定义的是<
    }
}farmer[maxn];
int n,m,sum=0,ans=0,cnt=0;
int main(int argc,char **argv)
{
    n=read();m=read();
    for(rint i=1;i<=m;i++)
    {
        farmer[i].p=read();farmer[i].a=read();     //先花费，后数量！
    }
    sort(farmer+1,farmer+m+1);   //结构体里面写完以后就是这个效果
    while(sum<n)   //sum是个约束条件的计数器
    {
        int tmp=0;cnt++;
        sum+=farmer[cnt].a;
        if(sum>n)    tmp=sum-n,sum=n;   //如果超过的话就平掉
        ans+=farmer[cnt].p*(farmer[cnt].a-tmp);   //保证不会超过
    }
    printf("%d\n",ans);
    //fclose(stdin);fclose(stdout);
    return 0;
}
```
···
就这样吧



---

## 作者：yzx4188 (赞：5)

# 这题压根不用排序

我看到楼上楼下许多神犇们都是用排序的，可这题完全可以不排序：

可以在每一次购买前把所有单价遍历一遍，找出单价最少的，买完后把他的单价提到1000以上就行了（因为单价<=1000）

我用了两个数组p和a来表示单价和每个农夫的最大产量（~~我绝对不会告诉你原因是我不会用数据结构~~）

具体看代码：
```cpp
#include<iostream>
using namespace std;
int n,m,ans;
int p[5050],a[5050];//p是单价，a是每个农夫的最大产量
int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++)
        cin>>p[i]>>a[i];//输入单价和产量
	while(n>0){
		int minp=0;//minp：最低单价
		for(int i=1;i<m;i++)
		    if(p[i]<p[minp])//如果还有更便宜的就选他
			    minp=i; 
		if(n<a[minp]){//如果可购买的比需要的多就直接补足
			ans+=p[minp]*n;//直接补足
			break;//跳出循环
		}
		else{//否则全部都买
			ans+=p[minp]*a[minp];
			p[minp]=1010;//把他的单价提到数据范围外，让它不会再被选中（你被抛弃了）
			n-=a[minp];//减去买到的数量
		}
	} 
	cout<<ans<<endl;
	return false;//撒花
}
```

~~我绝对不会告诉你我用这个代码一次就过了~~

---

## 作者：plazum (赞：4)

这题真是STL的好广告啊……用pair+sort就很方便了……

```cpp

#include<iostream>
#include<algorithm>
using namespace std;
int n,m,ans,i,t;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    pair<int,int> a[m];
    for(;i<m;i++)cin>>a[i].first>>a[i].second;
    sort(a,a+m);
    for(i=0;n>0;i++)t=min(n,a[i].second),n-=t,ans+=t*a[i].first;
    cout<<ans;
    
    return 0;
}

```

---

## 作者：远航之曲 (赞：3)

翻了一下题解，发现还没有这种方法。

这个方法很简单，因为价格的范围在1..1000之内，所以，我们只要在读入数据的时候把相同价格的合并即可，进行计算时，也只需要for i:=0 to 1000 do进行扫描如果有价格为i的牛奶就收购即可，所以不需要排序。理论上效率最高。

[/color]```cpp

#include <iostream>
using namespace std;
int main() {
    int value, n, milk[1002]={0}, money(0);
    cin >> value >> n;                             //读入
    for (int i=0; i<n; ++i) {
        int a, b;
        cin >> a >> b;
        milk[a] += b;                                 //合并
    }
    for (int i=0; i<=1000; ++i) {
        if (value > milk[i]) {                      //能全部收购
            value -= milk[i];
            money += i * milk[i];
        }
        else {
            money += value * i;
            break;
        }
    }
    cout << money << endl;
    return 0;
}

```

---

## 作者：LYOfficial (赞：2)

# 好开心啊，第一次写题解
**我蒟蒻，有些地方不恰当请提**

**别看混合牛奶题面挺长，~~都可以当语文阅读题了~~，但是只要仔细读题，就完全可以当做数学应用题来做~~（本来就是）~~**

### 首先，我们需要定义一个结构体

```c
struct Marry{//定义一个结构体Marry（Marry乳业） 
	int price,noun;//price代表农民i的牛奶单价，
    noun表示农民i一天能卖给Marry的牛奶制造公司的牛奶数量
}a[2000001];
```

### 因为要计算采购足够数量的牛奶所需的最小花费，所以要让价格由小到大进行排序

```c
bool cmp(Marry a,Marry b){//采用升序排序 
	return a.price<b.price;
}
```

## 完整代码如下：

```c
#include<bits/stdc++.h>//万能头，就是好用 
using namespace std;     
struct Marry{//定义一个结构体Marry（Marry乳业） 
	int price,noun;//price代表农民i的牛奶单价，noun表示农民i一天能卖给Marry的牛奶制造公司的牛奶数量
}a[2000001];
long long n,m,ans;//n是需要牛奶的总数；m是提供牛奶的农民个数
bool cmp(Marry a,Marry b){//采用升序排序 
	return a.price<b.price;
}
int main(){
	cin>>n>>m;//输入 
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a[i].price,&a[i].noun);
	}
	sort(a+1,a+m+1,cmp);//按价格由小到大进行排序 
	for(int i=1;i<=m;++i){
		if(n>a[i].noun){ 
			n-=a[i].noun;//如果有余，则全部剪掉 
			ans+=a[i].price*a[i].noun;//计算费用 
		}
		else {
			ans+=a[i].price*(n);//计算费用 
			n=0; 
			break;
		}
	}
	cout<<ans<<endl;//输出 
	return 0;
}
```

嗯嗯，这就是题解，有问题尽管提，但千万别嫌弃，~~我也是AC过的，最少不会让你听取WA声一片~~

---

## 作者：liaokq (赞：2)

# 貌似大家都在用快排啊

## 其实选择排序就能过

**本人亲测**

[就在这里](https://www.luogu.org/record/22235793)

——————————————（切入正题）————————————————

## 思路：排序+贪心

~~其实一开始看到题目时以为是背包，没办法，我太蒟了~~

### 既然是计算最小花费，那么就肯定是优先选择单价最便宜的

~~（貌似这句话是废话）~~

### 那单价一样的怎么办？

答曰：优先选择提供牛奶最多的

### why？

排序结束后，就按照单价从小到大的顺序直接模拟，如果把产量最多的放前面，更省时

## 直接放代码

```cpp
#include<bits/stdc++.h>//万能头（不过楼下好像不推荐）
using namespace std;

long long m,n;
long long p[5001],a[5001];
long long t,tt;
long long sum,ans;
//其实完全没有必要开long long，开了还占内存，但是在内存足够的情况下，更保险

int main()
{
	cin>>m>>n;
    //scanf("%lld%lld",&m,&n);
    //但是用cin也不会超时
	if(m==0)
	{
		cout<<"0"<<endl;
		return 0;
	}
    //这个特判一定要！如果需求为零，干嘛要买
    //我就被坑过QAQ
	for(int i=1;i<=n;i++)cin>>p[i]>>a[i];
	for(int i=1;i<=n;i++)
	{
		t=i;
		for(int j=i+1;j<=n;j++)
		{
			if(p[t]>p[j])t=j;
			if(p[t]==p[j])
			{
				if(a[t]<a[j])t=j;
			}
		}
		if(t!=i)
		{
			tt=p[i];p[i]=p[t];p[t]=tt;
			tt=a[i];a[i]=a[t];a[t]=tt;
		}
	}
    //以上是选择排序
	for(int i=1;i<=n;i++)
	{
		if(sum+a[i]<m)
		{
			sum+=a[i];
			ans=ans+a[i]*p[i];
            //如果买这个还不够的话，全部买掉继续往下找
		}
		  else
		  {
		  	ans=ans+(m-sum)*p[i];
		  	cout<<ans<<endl;
		  	return 0;
            //如果够了，只买自己需要的
            //再完美的结束程序
		  }
	}
}
```


---

## 作者：Atlicd (赞：2)

关键词：  
###贪心，模拟！！！   
啥都不说了，直接看代码
```
#include <algorithm>
//快排需要 
#include <iostream>
#include <utility>
//pair所需要的头文件 
#include <cstdio>
/*
标准化输入输出（scanf和printf）
不会用的同学要常常使用，这个比cin和cout快 
*/
using namespace std;
int n,m;
//n是一共需要多少份牛奶，m是有多少人可以提供牛奶 
//这个n也是实时更新的 
pair < int , int > p[5005];//第一关键字：费用；第二关键字数量
/*
pair是STL中的一个，
有两个参数组成 ，
分别是第一关键字和第二关键字，
这里应用的原因就是：
pair 定义的数组排序按照第一关键字优先排序，
第一关键字相同按照第二关键字排序的特点

就把pair当做一个变量 first，另一个变量是second的结构体就好了，
就是在快速排序排序时可以偷懒少写一个cmp。

pair的调用也很简单，
//eg（例如）pair < int ,int > s ;（要加入分号的 )
s.first 就是第一关键字，
s.second就是第二关键字 
*/
long long sum;
//不用long long可能要爆的 ,sum就是最后要输出的 
int main()
{
    scanf("%d%d",&n,&m);
	//输入输出，记得加取地址符“&” 
    for(int i=0;i<m;++i)
	//循环读入数据，第一关键字是单价，第二关键字是数量 
    scanf("%d%d",&p[i].first,&p[i].second);
    sort(p,p+m);
	//快排，因为用了pair所以不用写cmp排序函数 
    for(int i=0;i<m;++i)
	//排序好了所以从头开始遍历 
    {
	//这里的p[i]方案都是当前没有买奶的单价最便宜的 
	    if(n<=p[i].second)
		//判断如果需要买的奶<=这个奶农卖的最高数量 
	    {
		    sum+=p[i].first*n;
			//sum加上这个人买的单价*剩下的需要购入的牛奶 
			break;
			//因为已经买够了，所以跳出循环 
		}
		/*
		因为如果买够了就会跳出循环，
		所以这里不用在加一个if()判断了
		都是在n>奶农卖的最高数量 
		所以当遇到这个人的时候就会买光他提供的奶
		——因为贪心，
		他买的是当前最便宜的，（sort排序过） 
		*/
		sum+=p[i].first*p[i].second;
		//sum加上买光这个人提供的牛奶的花费 
		n-=p[i].second; 
		/*因为我们的n是实时更新的，
		所以，这个地方n要减去买入的牛奶的数量
		进入下一层循环 
	    */
		}
	printf("%d\n",sum);//最后把答案输出（我个人习惯在最后输出一个换行，并不算错） 
	return ~~(0-0);//撒花结尾 
}
 ```
请大家注意，特别是还不会使用STL 的小伙伴，STL是个好东西，一定要记得使用啊！

---

## 作者：LMB_001 (赞：2)

谁说这道题是背包？明明是贪心好不好！其实弄两个数组，一个单价，一个数量，然后根据单价排序也可以，但是我不想排序，因为p【i】的范围最大才到1000，所以只需要弄一个0到1000的数组，表示价格为p的牛奶的总数量，每次读入，都给a【p】加上数量v，最后用一个for循环从0扫到1000，如果中间牛奶够了，就把它退了。lz转c++一个月了，特弄一个Pascal程序练练手

```cpp
var
 a:array[0..1000]of qword;//害怕加爆了，反正没有负数的可能，就用qword了
 n,i,m,s,p,v:longint;
begin
 readln(n,m);
 fillchar(a,sizeof(a),0);//一开始初始化为0，其实不初始化也可以，因为Pascal是自动挡的车，c++是手动挡的车
 for i:=1 to m do begin
  readln(p,v);//读入单价和数量
  a[p]:=a[p]+v;//每次都给单价为p的单元加上v
 end;
 for i:=0 to 1000 do begin//从0到p扫
  if n=0 then begin write(s);exit;end;//如果现在牛奶够了，就输出，再弹出去
  if a[i]<>0 then如果有i单价的牛奶
   if a[i]>=n then begin
    write(s+n*i);
    exit;
   end//如果单价为i的牛奶数量大于需要的牛奶数量，就直接给输出，弹了
   else begin
    s:=s+i*a[i];
    n:=n-a[i];
   end;//如果单价为i的牛奶数量不够需要的牛奶数量，我们也要买，有多少买多少，记住需要的牛奶总数量要减
 end;
end.
其实原本准备弄一个背包玩玩，谁知道这道贪心题竟然在背包里面鱼目混珠，我太生气了，忍不住题解来一发！谢谢大家，不喜勿喷哦，再次谢谢，一起向省队加油！
```

---

## 作者：sky2001108 (赞：2)
















```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int rn,nn;
int p[5001];  //价格
int n[5001]; //数量
int k=0; //钱
int main()
{
    int i,j,t;
    cin>>rn>>nn; //输入
    for(i=1;i<=nn;i++)
        cin>>p[i]>>n[i];
        for(i=1; i<=nn; i++) //排序
    {
        for(j=nn; j>=i; j--)
            if(p[j]<p[j-1])
            {
                t=p[j-1];
                p[j-1]=p[j];
                p[j]=t;
                t=n[j-1];
                n[j-1]=n[j];
                n[j]=t;
            }
    }
    i=1;
    while(rn>0)//贪心算法
    {
            if(rn>=n[i])
        {
            k=k+n[i]*p[i];
            rn=rn-n[i];
        }
        else
        {
            k=k+rn*p[i];
            rn=0;
        }
        i++;
    }
    cout<<k;
        return 0;
}

```

---

## 作者：a3375948 (赞：2)

看到这题目的时候，我也是想排序来解，后来看到农民的牛奶的单价最多是1000时候，而且每个单价都对应了一个数量，我就想用一个1000大小的数组来存放农民牛奶单价对应的牛奶数量。在求解的时候，只需要遍历一下这个数组，就能解决问题


```cpp
#include <iostream>
using namespace std;
int main(){
    long long n,m,ai,pi[1001]={0},sum=0; 
    int i,price,flag[1001]={0};
    cin>>n>>m;
    for(i=0;i<m;i++){
        cin>>price>>ai;//农民牛奶单价和数量 
        pi[price]+=ai;//用相加是因为可能有相同单价的数量，不然会覆盖值 
        flag[price]=1;//标志这个值是有用的，存在牛奶不要钱的情况 
    }
    for(i=0;i<=1000;i++)
        if(flag[i]){
            n-=pi[i];//需要数量减去农民能提供的数量 
            if(n>0) sum+=(i*pi[i]);//大于0则还没收购完成，可以讲当前单价的全部收购 
            else {n+=pi[i];sum+=(i*n);break;}//小于0或者等于0表示刚好收购够或者收多了，就得恢复原本的数量按剩余量收购 
        }
    cout<<sum;
}

```

---

## 作者：何苗苗 (赞：2)

    
```cpp
#include<stdio.h>
struct milk // 结构体存储牛奶的单价和数量
{
    long  money;
    long  count;
}a[5000]; // 最多有5000个奶农
int main(void)
{
    long rest,sum,price;
    long t,i,j,n,m,p;
    sum=0;
    price=0;
    scanf("%ld%ld",&n,&m);
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&a[i].money,&a[i].count);
    }
    for(i=0;i<m-1;i++)  // 冒泡排序     牛奶的单价、数量 
    {
        for(j=0;j<m-i-1;j++)
        {
            if(a[j].money>a[j+1].money)
            {
                t=a[j].money;
                a[j].money=a[j+1].money;
                a[j+1].money=t; 
                p=a[j].count;
                a[j].count=a[j+1].count;
                a[j+1].count=p; 
            }
        }
    } 
    for(i=0;sum<n;i++)   // 退出循环的时候sum>=n
    {
        sum=sum+a[i].count;
        price=price+a[i].count*a[i].money;    
    }
    if(sum==n)
    {
        printf("%d\n",price);
    }
    else
    {
        rest=sum-n;
        price=price-rest*a[i-1].money;
        printf("%d\n",price);
    }
    return 0;
}
```

---

## 作者：CandyCandyFruit (赞：2)

看到好多奆佬在用结构体排序，本蒟蒻瑟瑟发抖qwq

我刚开始做这道题的时候压根没想到排序

## ~~纯模拟就做完了嘛。~~

**思路：每次循环找到当前牛奶单价最小值，然后统计钱数、删掉这个牛奶的商家，如果牛奶还没有达到需要的数量，那就接着循环。**

AC代码+注释：

```cpp
#include<bits/stdc++.h>//习惯性打万能头（好孩子别学我）
int main()
{
	int n,m,s=0,r,minqwq;
    //n=所需牛奶的数量，m=商店个数，s=钱，r=标记，minqwq=当前最小值；
	scanf("%d%d",&n,&m);
	int a[m],b[m];//个人习惯，a[]=单价，b[]=数量；
	for(int i=0;i<m;i++)
		scanf("%d%d",&a[i],&b[i]);//输入牛奶单价和数量
	while(n>0)//随着已购牛奶数量的增多，需要的牛奶的数量不断减少。当不需要再购买牛奶时，退出循环。
	{
		minqwq=9999;//最小值定义最大
		for(int i=0;i<m;i++)
		    if(a[i]<minqwq)
		        minqwq=a[i];//找到当前最小值
		for(int i=0;i<m;i++)
		    if(a[i]==minqwq)
		    {
		    	r=i;//标记牛奶商家的号码（就相当于你知道这家商店物美价廉，你就记在本子上，下次继续来这家商店买东西）
		    	break;
			}
		if(n>=b[r])//如果需要牛奶的数量大于等于商店里的牛奶数量
		{
			s=s+a[r]*b[r];//记录钱数
			n=n-b[r];//所需牛奶的数量减少
		}
		else
		{
			s=s+n*a[r];//记录钱数
			n=0;//不需要再买牛奶了
		}
		a[r]=99999;//把价格炒到天上去
		b[r]=0;//牛奶卖完了
        //上面两行相当于告诉电脑：这家牛奶店不卖牛奶了，你不能进他的店
	}
	printf("%d",s);//输出总钱数
	return 0;
} 
```

完美结束！万物皆可模拟！~~干嘛非要用结构体呢~~

---

## 作者：cilc3543 (赞：2)

//学长问我为什么写这么多注释……我还是写了……:)



```cpp
#include <cstdio>
const int MAXM = 5001, MAXG = 1001;
int G[MAXG];                                    //每个价格之下的牛奶量。 
int n, m;                                        //n=所需牛奶量，m=供应商数量。 
int main() {
    int cost = 0, j = 0, tmp = 0;                //cost=花费量，j=当前单价，tmp=当前牛奶量。 
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);                    //价格为x的供应商拥有多少牛奶。 
        G[x] += y;    
    }
    while (tmp < n) {
        if (tmp + G[j] <= n) {                    //如果【当前牛奶量】与【当前价格的牛奶量】之和小于或等于所需牛奶量的话，就需要把这个价格的牛奶全买了。 
            tmp += G[j];                        //当然，如果【当前价格的牛奶量】等于0，,tmp+=G[j]无影响，所以不用考虑G[j]=0的情况。 
            cost += j * G[j];                    //j*G[j]为买这个供应商的牛奶的价格。 
        } else {                                //如果【当前牛奶量】与【当前价格的牛奶量】之和大于所需牛奶量的话，只需要买一部分牛奶，达到所需即可。 
            cost += j * (n - tmp);                //这样子的话还需要的牛奶量为(n-tmp)，再乘上价格即可得到所需的价格。 
            tmp = n;                            //此时手中的牛奶量已经达到要求，这样的话tmp=n就可以了，否则会导致死循环。 
        }
        j++;                                    //买完这个供应商之后，单价加1表示买下一个供应商的牛奶。 
    }
    printf("%d", cost);
    return 0;
}
```

---

## 作者：wswhy (赞：2)

这题不难。。。不需要多么精深的算法。。。只要按价格排个序，然后再从便宜的开始比较买的数量够不够，顺便累加一下钱数，数量足够了，就输出价格。。。。就可以了，很简单哦。。。


```cpp
var  
      a,p:array[1..2000000] of longint;  
      n,m,x,i,j,t:longint;  
    begin  
     readln(n,m);  
     for i:=1 to m do  
      readln(p[i],a[i]);  
     for i:=1 to m-1 do  
      for j:=m downto i+1 do  
       if p[j]<p[j-1] then  
       begin  
         t:=a[j];a[j]:=a[j-1];a[j-1]:=t;  
         t:=p[j];p[j]:=p[j-1];p[j-1]:=t;  
        end;  
       x:=0;  
       i:=1;  
       while n>0do  
        begin  
         if a[i]=0 then i:=i+1;  
         a[i]:=a[i]-1;  
         n:=n-1;  
         x:=x+p[i];  
        end;  
       writeln(x);  
     end.  
water题。。。。。。
```

---

## 作者：强力人 (赞：1)

**###很简单的一道题**

首先读入，我这里定义了数据结构struct node，p和a同题目中的pi和ai，

然后用sort将数组按照价格从小到大排序（定义cmp）#**（排序完先输出一遍自己看看对不对）！！**；

然后从第一个开始搜索，n为还需要牛奶的量，ans为总价格；

最后输出，AC

###不要搞混单价和数量！！

AC代码如下


        
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
    int p,a;
};
bool cmp(node x,node y)
{
    return x.p<y.p;
}
struct node b[5010];
int main()
{
    int n,m,ans=0;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&b[i].p,&b[i].a);
    }
    sort(b,b+m,cmp);
    for(int i=0;i<m;i++)
    {
        if(n>=b[i].a)
        {
            ans=ans+b[i].a*b[i].p;
            n=n-b[i].a;
        }
        else
        {
            ans=ans+b[i].p*n;
            break;
        }
    }
    printf("%d",ans); 
}
```

---

## 作者：CreeperK (赞：1)

##此题就是按照价格从小到大排序，然后按顺序从头开始买牛奶。买时用一个变量记录总钱数即可。

一开始我也以为是背包来着……其实就是贪心+排序……


其它都附在代码里了，希望能帮到大家^\_^：

```cpp
#include<cstdio>
#include<algorithm>//sort
using namespace std;
int n,need,m=0;//n是农民数，need是需求量，m是总钱数
struct farmer{
    int p;//价格 
    int num;//奶量 
}f[5001];
int milk_cmp(const farmer &a,const farmer &b){//结构体排序
    return a.p<b.p;
}
int main(){
    scanf("%d%d",&need,&n);
    for(int i=0;i<n;i++)scanf("%d%d",&f[i].p,&f[i].num);//读入
    sort(f,f+n,milk_cmp);
    for(int i=0;i<n;i++){
        if(need-f[i].num<=0){m+=f[i].p*need;break;}//加上花费，退出循环
        else{
            need-=f[i].num;//减去购买量
            m+=f[i].p*f[i].num;//加上花费
        }
    }
    printf("%d",m);//输出
}
```

---

## 作者：night (赞：1)

pair函数的完美演示~

```cpp
#include <iostream>
#include<cstdio> 
#include<algorithm>
using namespace std;
int m,n,num=0,ans=0;
pair<int ,int>a[5005];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
    scanf("%d",&a[i].first);
    scanf("%d",&a[i].second);
    }
    sort(a+1,a+m+1);
    for(int i=1;i<=m;i++){
    if(num+a[i].second>=n)
    {
        ans+=(n-num)*a[i].first;
        break;
    }
    if(num+a[i].second<n){
    num+=a[i].second;
    ans+=a[i].second*a[i].first;
    }
    }
    printf("%d",ans);
}
```

---

## 作者：March (赞：1)

0MS 桶排序过,秒杀快排和sort()

这里的桶每个数字一个 时间复杂度为O(N) ；本题最大价格为1000很适合用桶排序 空间复杂度为O(1000)；

代码：

‘’‘c++

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
/*basic*/const int maxn=2000005, maxm=5000, radix=1001;
/*basic*/int N,M,G[radix]={0};
int main(){
    int cost=0, tmp=0,j=0;
    scanf("%d%d",&N,&M);
    for(int i=0;i<M;i++){
        int v,n;
        scanf("%d%d",&v,&n);
        G[v]+=n;
    }
    while(tmp<N){
        if(tmp+G[j]<=N) tmp+=G[j], cost+=j*G[j];
        else{cost+=(N-tmp)*j, tmp=N;}
        j++;
    }
    printf("%d\n",cost);
    return 0;
}
’‘’
```

---

## 作者：Kidd (赞：1)

这是一道部分背包，与01背包不同，他可以只拿一样物品的一部分（废话，滑鸡），而01背包的原则是：要么不取，要么取，且只能取一样。


严格来讲，部分背包更像是一种贪心（贪心原则：排序，最小价值优先取，太多了就退出循环，输出之前的价值+还有多少需求\*退出时的单价），下面的程序已经讲了。


上代码！！























```cpp
var n,m,i,j,t,s:longint;a,b:array[1..100000] of longint;
begin
   readln(n,m);
   for i:=1 to m do
   read(a[i],b[i]);
   for i:=1 to m-1 do
    for j:=i+1 to m do
    if a[i]>a[j] then
    begin
       t:=a[i];a[i]:=a[j];a[j]:=t;
       t:=b[i];b[i]:=b[j];b[j]:=t;
    end;//数据很菜，选排的时间复杂度为5000*5000=25000000，不会爆
   i:=1;
   while (i<=m) and (b[i]<=n) do//循环条件：所有农民没有选择完，再加上第i位农民的产量低于需求
   begin
      s:=s+a[i]*b[i];//把此位农民的牛奶都买光
      dec(n,b[i]);//需求减少
      inc(i);//去扫下一位农民
   end;
   writeln(s+n*a[i]);//由于数据保证牛奶足够，所以……
end.
我只想说，水题，水范围，水数据……
```

---

## 作者：司徒冰雨 (赞：1)

一道比较典型的贪心题目，按单价从小到大把奶农进行排序，然后进行收购，直到满足要求后跳出。

，，，



```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
struct data
{
    int dp;//单价
    int a;//产量
}nm[5001];
int N,M,pr;
int zy(struct data a,struct data b) //重载小于号，按单价排序
{
    return a.dp<b.dp;
}
int main()
{
    int i,j;
    scanf("%d%d",&M,&N);
    if(M==0&&N==0)
    {
        printf("0");
        return 0;
    }
    for(i=1;i<=N;i++)
    {
        scanf("%d%d",&nm[i].dp,&nm[i].a);
    }
    sort(nm+1,nm+N+1,zy); //排序
    for(i=1;i<=N;i++)
    {
        if(M>=nm[i].a)
        {
            pr+=nm[i].a*nm[i].dp;
            M-=nm[i].a;
        }
        else
        {
            pr+=M*nm[i].dp;
            break;
        }
    }
    printf("%d",pr);
    return 0;
}
，，，
```

---

## 作者：Rika (赞：1)

这个应该算是先桶排再贪心？因为价格在1000-，桶排的数组开小一些就够了，一个桶的价格区间是1，读入数据的时候就跟着排序，最后从小到大贪心就可以了。

>#include <iostream>
```cpp
#include<cstdio>
using namespace std;
int main() {
    int price[1001] = { 0 };
    int need, farmer, fee=0;
    cin >> need >> farmer;
    for (int i = 0; i < farmer; i++) {
        int a, b;
        cin >> a >> b;
        price[a] += b;
    }
    for (int i = 0; i <= 1000; i++) {
        if (need > price[i]) {
            need -= price[i];
            fee += price[i] * i;
        }
        else if (need > 0) {
            fee += need*i;
            need = 0;
        }
        else if (need == 0) {
            break;
        }
    }
    cout << fee;
    return 0;
}
```

---

## 作者：飞翔 (赞：1)

翻了一下题解，发现我的算法已经有人写了。。。

设f[i]表示单价为i的牛奶的产量，就可以节省排序的时间。最后一个0到1000的循环贪心就行了。

```pascal
var
  f:array[0..1001]of longint;
    i,n,m,ans,a,b:longint;
begin
  fillchar(f,sizeof(f),0);
  readln(m,n);
    for i:=1 to n do
    begin
      readln(a,b);
        f[a]:=f[a]+b;
    end;
    ans:=0;
    for i:=0 to 1000 do
      if m>f[i] then begin ans:=ans+f[i]*i;m:=m-f[i]; end
                            else begin ans:=ans+m*i;break; end;
    write(ans);
end.
```
注意如果已经买完了牛奶一定要退出！


---

## 作者：何昊燊1046 (赞：1)

```cpp
// 这是Pascal解法；
var n,m,i,j,s,w:longint;
    a,b:array[1..100000] of longint;
begin
  readln(n,m); //读入需要的牛奶数和提供牛奶的奶农的人数；
  for i:=1 to m do readln(a[i],b[i]);  //输入各奶农牛奶的单价和数量；
  for i:=1 to m-1 do
    for j:=i+1 to m do
      if a[i]>a[j] then
        begin
          w:=a[i];a[i]:=a[j];a[j]:=w;
          w:=b[i];b[i]:=b[j];b[j]:=w;
        end;  //把单价和数量从小到大排序，确保Marry的牛奶制造公司用最小费用拿到所需的牛奶；
  for j:=1 to m do if b[j]>n then begin s:=s+a[j]*n;break;end else begin s:=s+a[j]*b[j];n:=n-b[j];end;  //判断第j个奶农所提供的牛奶是否多于需要的牛奶数，如果第j个奶农所提供的牛奶少于或等于需要的牛奶数，就直接用a[i]*b[i](也就是全部买下)，然后用原来所需要的牛奶数减去已购买的牛奶数，求出还需要购买的牛奶数；如果第j个奶农所提供的牛奶多于需要的牛奶数，就用n*a[i](也就是只卖需要的牛奶)，然后退出循环；
  writeln(s); //输出；
end.
```

---

## 作者：pgz123 (赞：1)

```cpp
//这里是pascal的做法
var p,a:array[1..10000] of longint; n,i,k,m,j,t:longint; //首先定义变量是必须的了
begin
  readln(n,m);//按照题目输入需要牛奶的总数和提供牛奶的农民个数
  for i:=1 to m do read(p[i],a[i]); //再输入P[i] 和 A[i]
  for i:=1 to m-1 do  //以小到大排序P[i]和A[i]，以确保Marry的牛奶制造公司拿到所需的牛奶所要的最小费用
    for j:=i+1 to m do
    if p[i]>p[j] then
    begin
      t:=p[i];
      p[i]:=p[j];
      p[j]:=t;
      t:=a[i];
      a[i]:=a[j];
      a[j]:=t;
    end;
  for i:=1 to m do//循环
  begin
    if n-a[i]>=0 then begin n:=n-a[i]; k:=k+a[i]*p[i]; end //如果需要牛奶的总数减去农民 i 一天能卖给Marry的牛奶制造公司的牛奶数量大于等于0（也就是说该公司可以把该农民的牛奶全购了）就买下了农民的所有牛奶并且给k加上所需的费用
     else begin k:=k+p[i]*n; n:=0; end;//否则就买公司目前所需要的牛奶并给k加上所需的费用，n=0
    if n=0 then break;//就是说如果Marry的牛奶制造公司已经拿到所需的牛奶就直接退出循环
  end;
  writeln(k);//输出Marry的牛奶制造公司拿到所需的牛奶所要的最小费用
end.
```

---

## 作者：guobaipeng0 (赞：1)


```cpp
//pascal做法，贪心
var a,b:array[1..5005] of longint;
  m,s,n,i:longint;
procedure qsort(l,r:longint);   //快排小到大
var i,j,x,y:longint;
begin
  i:=l;j:=r;x:=a[(l+r) div 2];   //x取中间值
  repeat
    while a[i]<x do inc(i);    
    //搜索，如果这个数比中间值小的话就继续，直到找到比中间值大的数
    while x<a[j] do dec(j);
   //和上面相反，如果这个数比中间值大就继续，直到找到比中间值小的数
    if i<=j then
   //这里交换，条件是大的数在数列的左边，小的在数列右边才行
    begin
      y:=a[i];a[i]:=a[j];a[j]:=y;
      y:=b[i];b[i]:=b[j];b[j]:=y;
      inc(i); dec(j);//继续搜索，没有这一行和下一行会死循环，永不停止
    end;
  until i>j;
  if l<j then qsort(l,j);
  //这里和下一行都是判断，如果还有一段没有搜索过，就搜索那一段
  if i<r then qsort(i,r);
end;
begin
  readln(m,n);  //输入
  for i:=1 to n do readln(a[i],b[i]);   //输入单价和产量
  qsort(1,n);    //快排
  for i:=1 to n do
  begin
    m:=m-b[i];   //减去产量，得出剩下需要多少
    s:=s+a[i]*b[i];   //计算价格
    if m<=0 then begin s:=s-(0-m)*a[i]; break; end;
    //有时会不用那么多，减回价格里的多出的牛奶的价格
  end;
  writeln(s);    //输出价格
end.
```

---

## 作者：邓晓蓝 (赞：1)





```cpp
//简单的贪心，按单价从小到大排序
var xq,n,i,ss,s,a,j:longint;
    jq,sl:array[0..50000] of longint;
begin
  readln(xq,n);
  for i:=1 to n do
    readln(jq[i],sl[i]);
  for i:=1 to n-1 do
    for j:=i+1 to n do
      if jq[i]>jq[j] then
        begin
          a:=jq[i];jq[i]:=jq[j];jq[j]:=a;
          a:=sl[i];sl[i]:=sl[j];sl[j]:=a;
        end;
  for i:=1 to n do
    if s+sl[i]<=xq then begin s:=s+sl[i];ss:=ss+jq[i]*sl[i];end else begin ss:=ss+(xq-s)*jq[i];break;end;
  writeln(ss);
end.
```

---

## 作者：hfctf0210 (赞：1)

弱爆了的题目，纯贪心

按单价从小到大排序，然后进行贪心。

代码：

```cpp
#include<iostream>    
using namespace std;   
int n,m,v[5001],w[5001];  
void read()  
{  
    cin>>n>>m;  
    for(int i=1;i<=m;i++)  
    cin>>v[i]>>w[i];  
}  
void sort()  
{  
    for(int i=1;i<m;i++)  
    for(int j=i+1;j<=m;j++)  
    if(v[i]>v[j])  
    {  
        swap(v[i],v[j]);  
        swap(w[i],w[j]);  
    }  
}  
int tanxin()  
{  
    int i,ans=0;  
    for(i=1;i<=m;i++)  
    {  
        if(n>=w[i])  
        {  
            n-=w[i];  
            ans+=v[i]*w[i];  
        }  
        else{  
            ans+=n*v[i];  
            return ans;  
        }  
    }  
    return ans;  
}  
int main()  
{  
    read();  
    sort();  
    cout<<tanxin();  
    return 0;  
}
```

---

## 作者：枍暮77 (赞：1)

这道题其实很简单，甚至用不到快排，反正洛谷不超时。。。。。。把牛奶的单价排一下序，从小到大一个个去试，用简单的while循环就可以实现。。。。。。

下面是Pascal的程序

```delphi
 var
  a,p:array[1..2000000] of longint;
  n,m,x,i,j,t:longint;
begin
 readln(n,m);
 for i:=1 to m do
  readln(p[i],a[i]);//读入
 for i:=1 to m-1 do
  for j:=m downto i+1 do
   if p[j]<p[j-1] then
   begin
     t:=a[j];a[j]:=a[j-1];a[j-1]:=t;
     t:=p[j];p[j]:=p[j-1];p[j-1]:=t;
    end;//冒泡。。。
   x:=0;
   i:=1;
   while n>0do
    begin
     if a[i]=0 then i:=i+1;
     a[i]:=a[i]-1;
     n:=n-1;
     x:=x+p[i];
    end;
   writeln(x);//输出
 end.
```

---

## 作者：19917628707a (赞：1)


import java.util.*;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner cin = new Scanner(System.in);
		int need = cin.nextInt();// 商家需量
		int n = cin.nextInt();// 提供牛奶的农门数目
		int a[][] = new int[n][2];// 每一个农门提供的牛奶价格和能提供的最大量
		for (int i = 0; i < n; i++) {
			a[i][0] = cin.nextInt();// 价格
			a[i][1] = cin.nextInt();// 量
		}

		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (a[j][0] > a[j + 1][0]) {
					int temp = a[j][0];

					a[j][0] = a[j + 1][0];
					a[j + 1][0] = temp;
					temp = a[j][1];
					a[j][1] = a[j + 1][1];
					a[j + 1][1] = temp;
				}

			}
		}
		int money=0;//公司需要花费的最小金额
		int temp1=0;
		for(int i=0;i<n;i++) {
			need=need-a[i][1];
			if(need>=0) {
				money=money+a[i][0]*a[i][1];
			}
			else {
				money=money+(need+a[i][1])*a[i][0];
				break;
			}
			
		}
		
		/*
		 * for(int i=0;i<n;i++) {
			System.out.println(a[i][0]+" "+a[i][1]);
		}
		 */
		System.out.print(money);

	}

}


---

## 作者：非洲王八 (赞：0)

# **蒟蒻的第一发题解，做的不好请见谅**

简单分析一下，这道题其实很简单

### **主要思路：既然要总价最小，就先在单价最小的奶农那里买**
废话少说，上代码
```c
#include<bits/stdc++.h>
using namespace std;
struct node{
	int price;
	int num;   //定义结构体代表牛奶，每个奶农的牛奶都有单价和数量两种属性 
};
node milk[5005];
int cmp(node x,node y)
{
	return x.price<y.price;
}
//cmp过程 
int main()
{
	int m,n,money=0;   //定义需要牛奶数，奶农数和总价 
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>milk[i].price>>milk[i].num;
	}
	sort(milk+1,milk+1+m,cmp);   //按照牛奶的单价从小到大排序 
	for(int i=1;;i++)
	{
		if(n<=milk[i].num)
		{
			money=money+(milk[i].price*n);    //如果还需要的牛奶数小于这位奶农的奶量（雾）则按需要的牛奶数计数 
			break;
		}
		n=n-milk[i].num;   //计算还需要多少牛奶 
		money=money+(milk[i].price*milk[i].num); 
	}
	cout<<money;
	return 0;
}
```



---

## 作者：Jelly_Goat (赞：0)

其实根本没有一楼dalao描述的那么麻烦......  
### 一楼dalao其实吧，采用了一种纯属模拟的方式。  
### 下面是我的大跃进思想
但是一个个地做减法是不是太慢了？~~(大跃进思想)~~  
于是我们是不是可以直接进行一个大跨步式的方法  
### 你的奶我直接全都要了？
敲一个伪代码理解一下
```cpp
while (当前需要奶量)
{
    if (奶农的提供量<=现在的需求量)
    {
        现在的需求量-奶农的提供量
        你的money-奶农的提供量*奶农的单价
        换一个奶农//这个的提供量已经=0
    }
    else
    {
        你的money-剩余需求量*奶农的单价
        需求量=0
    }
}
```
然后这个算法的优势就是**大跃进**  
让一个奶农不用分批次给你送牛奶（n--）  
**直接一步到位，多快好省**  
然后贴上~~高清打码~~的代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long int lli;
lli n,m,sum;
struct nainong{
	lli dj,num;
	void input(){cin>>this->dj>>this->num;}
}milk[5001],*now=&milk[1];
bool cmp(const nainong &a,const nainong &b)
{
	if (a.dj!=b.dj)return a.dj<b.dj;
	else return a.num>b.num;
}

int main()
{
	cin>>n>>m;
	for (register int i=1;i<=m;i++)
	{
		milk[i].input();
	}
	sort(milk+1,milk+m+1,cmp);
	while (n)//当任务还没有完成的时候
	{
	    if (now->num<=n)//如果这个奶农产出的奶不够用
	    {
	        n-=now->num;//减掉这个奶农的产量(我全都要了qwq)
	        sum+=(now->dj)*(now->num);//加上这个奶农的要价
	        now++;//移动到下一个位置(or——奶农qwq)
	    }
	    else//奶农产出的奶量不足(任务即将完成)
	    {
	        sum+=(now->dj)*n;//买到最后的奶
	        n=0;//任务完成
	    }
	}
	cout<<sum;
	return 0;
}
```
然后呢，看看两个代码之间的差距：  
![](https://cdn.luogu.com.cn/upload/pic/52566.png)  
(十分建议@chen_zhe 数据加强卡一下，逃qwq)

---

## 作者：_谦退_ (赞：0)

好了，这是本蒟蒻第二次FA♂题解了

# 一开始提交总~~TM~~有一个点RE

#### 我还以为我数组开的不够大，结果看了一下数据范围

## 0<=N<=2,000,00

心想我数组开的足够大了呀为啥会RE，无法理解

直到后来我下载了我RE那个点的数据

## 这是输入

![](https://cdn.luogu.com.cn/upload/pic/46435.png)

## 这是输出

![](https://cdn.luogu.com.cn/upload/pic/46436.png)

# 。。。。。。
# ~~WTF~~这是什么鬼，故意坑我的吧

## 还好，这道题没有那种USACO那种神坑输入的格式，要你多组数据用0 0结尾

### 好了，二话不多说，上代码！！
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k=1;
struct node
{
	int v;
	int w;
}r[100000001];
int ans=0;
bool cmp(node a,node b)
{
	return a.v<b.v;
}
int main()
{
	cin>>m>>n;
	if(m==0&&n==0)
	{
		cout<<"0";
		return 0;
	}//辛酸都是泪
	for(int i=1;i<=n;i++)
	  cin>>r[i].v>>r[i].w;
	sort(r+1,r+n+1,cmp);//结构体排序
	for(int i=1;;i++)
	{
		if(r[k].w==0)
		{
			k++;
			continue;
		}
		if(m==1)
		{
			ans+=r[k].v;
			break;
		}
		m--;
		r[k].w--;
		ans+=r[k].v;
	}
	cout<<ans;
	return 0;//结束
}
```

---

## 作者：woshigui (赞：0)

```python
n=input().split()
N=int(n[0])
M=int(n[1])
a=[]
for i in range(M):
    n=input().split()
    a.append([int(n[0]),int(n[1])])
a.sort(key=lambda x:x[0])
#list的每个元素还是个list，所以排序时候按照每个元素的
#第一个的大小进行排序
sum=0
shengyu=N
for i in a:
    if shengyu-i[1]<=0:
        sum+=shengyu*i[0]#用shengyu这个变量是容易冒
        break
    else:
        sum+=i[0]*i[1]
        shengyu-=i[1]
print(sum)
```
python输入麻烦的一点就是全都是字符串且只按行读，所以需要处理


---

## 作者：attack_shane (赞：0)

混合牛奶是一道非常经典的题，大多数人都是写结构体来标准地去完成，对于我——一个偷懒的刷题者：给大家看个宝贝：


```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
inline long long read(){
    char c;long long x=0;
    c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}
```
以上快读，无需理睬。
```cpp
int main(){
    long long n=read(),k=read(),p[5050],s=0,i;//s用于记录结果，i记录过程，p记录数据，n、k不多作冗述。
    for(i=0;i<k;i++)p[i]=read()*10000000+read();//由输入我们可以看出，第i+1个农民牛奶单价为p[i]/10000000，第i+1个农民牛奶数量为p[i]%10000000。
    sort(p,p+k);
    i=0;
    while(n){
        if(n>=(p[i++]%10000000))s+=(p[i-1]/10000000)*(p[i-1]%10000000),n-=p[i-1]%10000000;
        else s+=(p[i-1]/10000000)*n,n=0;//按之前说的进行贪心。
    }
    cout<<s<<endl;//输出结果。
    return 0;
}
以状态压缩，根据数据范围放大价格，使价格优先，普普通通的一次sort排序，再出结果。
```

---

## 作者：TURX (赞：0)

>这道题可以用排序来写。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,fee=0; // n是需要牛奶的总数，m是提供牛奶的农民个数
struct data {
    int p; // 单价
    int a; // 数量
} d[5000]; // 定义结构体存储单价和数量
bool cmp(data lhs, data rhs) { // 自定义比较函数
    return lhs.p < rhs.p; // 返回比较
}
int main() {
    ios::sync_with_stdio(false); // iostream 快过 cstdio 的函数
    cin>>n>>m; // 输入
    for(int t=0;t<m;t++) cin>>d[t].p>>d[t].a; // 输入 第 2 到 M+1 行:每行二个整数:Pi（单价） 和 Ai（数量）。
    sort(d,d+m,cmp); // stl_algo.h: sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)，故此处__comp为自定义比较函数，按返回值进行排序
    for(int t=0;t<m;t++) {
        if(n>=d[t].a) // 数量未到达要求
        {
            fee+=d[t].a*d[t].p; // 计算费用
            n-=d[t].a; // 已经完成，减少数量要求
        }
        else // 已到达数量要求
        {
            fee+=d[t].p*n; // 最后计算费用
            break; // 跳出
        }
    }
    cout<<fee<<endl; // 输出费用
}
```

---

## 作者：xun薰 (赞：0)

贪心 每次选择单价低的...说背包的是什么鬼....

注意long long

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,mk,now=1;
long long ans;
struct Milk{
    int v,w; 
}m[5002];
bool cmp(Milk a,Milk b){
    return a.v<b.v;
}
int main(){
    scanf("%d%d",&n,&mk);
    for(int i=1;i<=mk;i++)scanf("%d%d",&m[i].v,&m[i].w);
    sort(m+1,m+mk+1,cmp);
    while(n){
        int k=min(n,m[now].w);
        ans+=(1LL*k*m[now].v);
        n-=k;
        now++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：hl666 (赞：0)

```cpp
  var n,j,m,i,temp,money:longint;
     a,p:array[1..5005] of longint;
   begin
   readln(m,n);
   if (m=0) and (n=0) then writeln(0);
   for i:=1 to n do
   readln(a[i],p[i]);
   for i:=1 to n-1 do
    for j:=i to n do
    if a[i]>a[j] then 
   begin temp:=a[i];
         a[i]:=a[j];
         a[j]:=temp;  
         temp:=p[i]; 
         p[i]:=p[j];      
         p[j]:=temp;  end;
   for i:=1 to n do
   begin if p[i]>=m  then
   begin    money:=money+m*a[i];
            writeln(money);
            exit;  end
                     else 
   begin    m:=m-p[i];
            money:=money+p[i]*a[i];  end;
    end;
  end.
//先排序，再进行贪心

//如果需要的大于单价最小的就全部买来，小于等于就买所需的。

```

---

## 作者：amstar (赞：0)

贪心，找单价最小的就可以。


sum 记录当前已经买了多少牛奶，如果下一个奶农的牛奶总量+sum大于需要的，加上剩余的，小于等于就全买了。






```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 5005;
struct milk{
    int w,v;    //分别是单价，多少 
}t[N];
int n,m,ans,sum;
bool cmp(milk a,milk b)
{
    return a.w < b.w;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&t[i].w,&t[i].v);
    sort(t+1,t+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        if(t[i].v+sum > m)
        {
            ans += (m-sum)*t[i].w;
            break;
        }
        ans += t[i].w*t[i].v;
        sum += t[i].v;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：睡在墙上的猫 (赞：0)

如果好了就退出，然后就没啥了

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct niu
{
    int m,n;//m是一个牛奶多少钱，n是多少个牛奶 
}; 
int cmp(const niu &a,const niu &b)
{
    if (a.m<b.m) return 1;
    else return 0;
}
int main()
{
    niu c[5010];
    int i,u,v,sum=0;
    cin>>u>>v;
    for (i=1;i<=v;i++)
    {
        cin>>c[i].m>>c[i].n;
    }
    sort(c+1,c+v+1,cmp);
    for (i=1;i<=v;i++)
    {
         if (u<c[i].n) c[i].n=u;//重点
         sum+=c[i].m*c[i].n;
         u-=c[i].n;
         if (u==0) break;
    }
    cout<<sum;
    return 0;
}

```

---

