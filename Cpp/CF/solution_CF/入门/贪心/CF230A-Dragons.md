# Dragons

## 题目描述

小方在跟龙进行比赛，他要是想进入下一层级，就必须要击败在这一层级上的所有的n条龙。 小方和每一条龙都有一个可以用整数表示的力量值，在每一次战斗中，该次战斗的结果由战斗的双方的力量值所决定。在一开始，小方的力量值是s。

在任意一次战斗中，如果小方的力量值比第i条龙（1<=i<=n）的力量值大，那么小方可以击败这头龙并且获得额外的力量值y(i)，如果小方的力量值不大于这头龙的力量值，那么小方将在这场战斗中死亡。

小方可以以任意的一个顺序和龙进行战斗。请编写程序确定小方是否可以继续进入下一层级的比赛，即击败所有的龙族并且自己没有任何损失。

## 说明/提示

在第一个样例中，小方力量初始值为2，第一条龙的力量值小于2，那么小方将击败他并获得额外的力量值99，此时小方的力量值为2+99=101，大于第二条龙的力量值，小方将击败他，因此小方可以进入下个层级。

在第二个样例中，小方力量初始值为10，小于唯一的一条龙的力量值100，那么小方将无法击败这条龙，因此无法进入下一层级。

感谢@wcy1056935201 提供翻译

## 样例 #1

### 输入

```
2 2
1 99
100 0
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
10 1
100 100
```

### 输出

```
NO
```

# 题解

## 作者：FCB_Yiyang2006✈ (赞：13)

## 1.看这篇题解前需要预知（或掌握）
> ##### (1) 队列及其用用法（包括输入，输出，弹出）
> ##### (2) 堆的概念及STL(priority_queue)
> ##### (3) 结构体的基本概念和写法
> ##### (4) 贪心策略

## 2.进入正题
题目梗概：小方有没有可能不战死，有输出 $YES$ 否则输出 $NO$。

### 思路
贪心策略：从最小的龙打起，攒能量，然后打大龙

实现方式：排序。

这里就用二叉堆来写。

#### 二叉堆
堆分为大根堆和小根堆，是一棵完全二叉树，珂以维护递增或递减的数列。

[模板](https://www.luogu.com.cn/problem/P3378)（里面的题解都讲得很好，珂以去康康）

手写堆比较难打，这里用STL来写。

```cpp
priority_queue<int> q;
```

其实我们看到，这在 $c++$ 中就是一个帮我们自动维护的队列。而这样写是默认大根堆，即降序排列。

如果我们需要升序怎么办呢？

我们先来康康大根堆的原型：

```cpp
priority_queue<int,vector<int>,less<int> >
```

我们只用做一处改动，就能让它变成小根堆（升序）——

```cpp
priority_queue<int,vector<int>,greater<int> >
```

库函数：
```cpp
q.push(i)//将i压入单调队列
q.pop()//弹出堆顶（即当前最小或最大数）
q.top()//当前的堆顶
q.empty()//bool类型，判断是否为空
q.size()//大小，即元素个数
```

但显然这道题是需要两个配对的数，一起压入，一起弹出的，但编译器不知道是按哪个排序，所以我们需要自定义优先级，也就是 $struct$ 中的重载运算符。


```cpp
struct node
{
    int x,y;
};
```
这是个普通的结构体。

现在加上这段代码：

```cpp
struct node
{
    int x,y;
    bool operator<(const node A) const
    {
        return x>A.x;
    }
};
```

这就是重载运算符，相当于告诉编译器按什么排序。

```
bool operator<(const node A) const
{
  return x>A.x;
}

```
这一段珂以理解为 $sort$ 中的 $cmp$，升序就用 $>$, 降序用 $<$。

我们现在就珂以定义：
```cpp
priority_queue<node> q;
```

当然，这样写，压入的和堆顶都是一个 $node$ 型结构体。
## 3.上代码
```cpp
#include<bits/stdc++.h>//万能脑袋包括队列及单调队列的所有库函数
using namespace std;
int s,n;
struct node
{
    int x,y;
    bool operator<(const node A) const
    {
        return x>A.x;
    }//重载运算符
};
priority_queue<node> q;
int main()
{
	cin>>s>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		q.push((node){x,y});//压入（自动排序）
	}
	while(!q.empty()) //输出操作
	{
		if(s>q.top().x)
		{
			s+=q.top().y;
		}
		else
		{
			cout<<"NO"<<endl;
			return 0;
		}//战死就结束
		q.pop();//弹出当前
	}
	cout<<"YES"<<endl;//一直没有战死
	return 0;
}
```
(蒟蒻心地善良，珂以直接 $AC$)

## 4.相关推荐

1.各位巨佬不妨自己实现一下重载运算符,升序和降序。

2.会普通 $dijkstra$ 最短路径的巨佬，珂以自己实现一下堆优化。

[堆优化模板](https://www.luogu.com.cn/problem/P4779)

我也写了（输出路径的）堆优化版本，各位巨佬珂以去[康康](https://www.luogu.com.cn/blog/YiYangYY/dijkstra)

## 5.最后

#### 感谢 $CF$ 题库供题，洛谷管理员维护，翻译者的翻译和点赞用户！

因为我比较弱，有些讲得不清楚的地方敬请谅解，可以在评论区提出。

祝各位早日 $AC$ 本题！

---

## 作者：若如初见 (赞：7)

最近在学数据结构，就用二叉排序树写了：  
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
typedef struct node{
	int key,ad;
	struct node *lchild;
	struct node *rchild;
}node, *tree;
tree t;
void ins(tree &bt,tree s){
	if(bt==NULL) bt=s;
	else 
	if(s->key<bt->key)
		ins(bt->lchild,s);
	else ins(bt->rchild,s); 
}    
tree create(tree &root){
	root=NULL;
	int x,a;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&x,&a);
		tree s=(tree)malloc(sizeof(node));
		s->key=x;
		s->ad=a;
		s->lchild=NULL; s->rchild=NULL;
		ins(root,s);
	}
	return root;
}
void LDR(node *t){
	if(t!=NULL){
		LDR(t->lchild);
    	if(t->key<m)
    		m+=t->ad;
    	else{
    		printf("NO");
    		exit(0);
    	}
		LDR(t->rchild);
	}
}
int main(){
	scanf("%d %d",&m,&n);
	create(t);
	LDR(t);
	printf("YES");
	return 0;
}
```


---

## 作者：dinghongyu (赞：6)

## 这题只要会排序的人就应该会做

### 思路：排序然后比较，只要战死就直接结束程序
### 代码：
```cpp
#include <iostream>
using namespace std;
int x[1005],y[1005],s,n;
int main()
{
	cin>>s>>n;
	for (int i=1;i<=n;i++)
	   cin>>x[i]>>y[i];
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n-i;j++)
		{
			if (x[j]>x[j+1])
			{
				swap(x[j],x[j+1]);
				swap(y[j],y[j+1]);
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		if (s>x[i])
		{
			s+=y[i];
			continue;
		}
		else
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：打表大蒟蒻 (赞：4)

这就是道排序的裸题啊
这道题相信只要学过排序的人都能做出来，因此在这里只讲排序的方法：

1.冒泡排序

冒泡排序的基本思想是：对相邻的元素进行两两比较，顺序相反则进行交换，这样，
每一趟会将最小或最大的元素“浮”到顶端，最终达到完全有序。
例如：我们要将身高不等的十个人站在一排，要求他们按照身高由低到高排队，设将 10
个人编号为 0~9 ，相邻的两个人依次比较，如果左边的比右边的人高，则交换两个人的位
置，否则不交换，直到最后两个人，即此时完成了一趟排序。一趟排序后，最高的人已经在
最右边了。

上代码，注意：不是本题的代码！！！
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1001], n;
int main ()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	
	for(int i=1;i<n;i++)   //进行n-1轮冒泡 
		for(int j=1;j<=n-i;j++)   //每次进行n-i次比较 
			if(a[j]>a[j+1]) swap(a[j],a[j+1]);   //相邻元素进行比较，如果大的元素在前面，则交换 
			
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" "; 
	return 0;   
}
```
可是冒泡排序的时间复杂度太高，以至于很有可能TLE，因此，我们引进桶排

3.桶排

桶排序是一种排序算法，实际上并没有进行比较排序，而是借助了数组。
假定有 1-100 个编号的桶（也就是定义一个长度为 100 的整型一维数组），每输入一个
数字·就在对应的桶上插一个小旗（也就是对应下标的桶加 1 次），如果这个数字出现了 n
次就在对应桶上插 n 个小旗，当所有数输入完毕时，只需要从下标 1 开始找那些数字是 1，
如果是 1 就打印 1 次，是 2 就打印 2 次，是多少就打印多少次。

为什么我们没有比较大小就排序出来了呢？因为数组下标本身就是已经排好了，只出现一次数就在对应下标上+1，然后遍历数组中那些大于 0 就行。

缺点：
使用桶排序占用内存很大，如果需要排序的数字是 1，10000 这两个数，也要定10000 个桶。因为必须在 10000 这个桶上插小旗嘛；由于桶的标号只能是整数（数组下只有整数），所以它并不能排序小数，只能排序整数。

优点：
相比冒泡排序，桶排序程序实现更加简单，而且效率也高了很多
继续上代码，也不是本题的代码
```
#include <bits/stdc++.h>
using namespace std;
int a[10001];
int main()
{
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        a[x]++; // 记录 x 出现的次数
    }
    for (int i = 1; i <= 10000; i++) // 从头到尾扫一遍
        for (int j = 1; j <= a[i]; j++) //a[i] 表示 i 出现的次数
            cout << i << ' ' ;
    return 0;
}
```

3.STL快排
要说C++比别的语言好在哪，自然是它拥有丰富的STL库（标准模板库）。STL里有队列，栈，映射等很好用的函数，在此，我介绍sort函数
使用sort其实非常简单，只需sort(a,a+n)就行了，当然，如果数组下标从1开始，得用sort(a+1,a+n+1)。具体解释参考百度[sort函数](https://baike.baidu.com/item/sort函数/11042699?fr=aladdin)
上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1001], n;
int main ()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	
	sort(a+1,a+n+1);
	
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
	return 0;   
}
```
好啦，懂得了以上几种排序方法后，做这道题是不是很简单呢？
#### 看我写得那么认真，不留个赞再走吗？

---

## 作者：云浅知处 (赞：3)

这题真的不难。
***
思路：让小方先打那些力量值比较小的、比较好打的龙。等他的力量值攒得够多了，再去打那些不好打的龙。

需要注意的是题中说的是**大于**，而不是**大于等于**。

所以，这题实际上考的只有一个点：**排序**。

下面介绍几种常见的排序方法。
***
$1.$最简单：冒泡排序，时间复杂度为 $O(n^2)$。

它的工作原理如下：

1. 比较数组中相邻的两个元素。如果第一个比第二个大，就交换他们两个。
1. 对每一对相邻元素做同样的工作，从开始第一对到结尾的最后一对。在这一点，最后的元素应该会是最大的数。
1. 针对所有的元素重复以上的步骤，除了最后一个。
1. 持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。

代码实现：
```cpp
void bubble_sort(int array[],int len){
	int i,j;
	for(i=0;i<len-1;i++){//对所有元素进行以下操作
		for(j=0;j<len-1-i;j++){//将第一个元素与后面的元素一一比较
			if(array[j]>array[j+1]){//如果前一个元素大于后一个元素
				swap(array[j],array[j+1]);//将这两个元素交换
			}
		}
	}
}

```
***
$2.$较常用：插入排序，最坏情况下时间复杂度 $O(n^2)$。

插入排序分为直接插入排序与折半插入排序两种，这里只讲直接插入排序。

“插入排序将数列划分为“已排序的”和“未排序的”两部分，每次从“未排序的”元素中选择一个插入到“已排序的”元素中的正确位置。”

[$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\text{——OI Wiki}$](https://oi-wiki.org/basic/insertion-sort/)

代码实现：
```cpp
void isort(int a[], int n){
    for(int i=2;i<=n;i++){
        int key=a[i];
        int j=i-1;
        while(j>0&&a[j]>key){
            a[j+1]=a[j];//寻找合适的插入位置
            j--;
        }
        a[j+1]=key;
    }
}
```
***
$3.$计数排序——空间换时间。时间复杂度为 $O(n+w)$ ，快于任意其他的比较方法。其中 $w$ 是待排序数据的值域大小。

计数排序一般有以下几个步骤：

1. 计算每个数出现的次数
1. 求出每个数出现的次数的前缀和
1. 求出前缀和之后，我们再利用这个前缀和，从右至左依次求出每个元素的排名

代码实现：
```cpp
void CSort(int data[],int n){
    int i,j,count,tmp;
    int *data_sort=new int[n]//定义动态数组data_sort。
    for(i=0;i<n;i++)//初始化动态数组。data_sort
        data_sort[i]=0;
    for(i=0;i<n;i++){
        count=0;
        for(j=0;j<n;j++)//扫描这个数组。
            if(data[j]<data[i])//统计出比data[i]值小的元素的个数。
                count++;
        while(data_sort[count]!=0)//对于那些相等但不是0的数据，应向后移一位。当数据等于0时，数组data_sort中已经被初始化为0，不受影响。
        //注意此处应使用while循环，如果使用if条件判断，那么超过一定数量的重复值后会少一个元素，而多一个0！
                count++;
        data_sort[count]=data[i];//把这个数存放到动态数组data_p中相应的那个位置。
    }
        //下面的代码用于检查当有多个数相同时的情况。
    i=0,j=n;
    while(i<j){
        if(data_sort[i]==0){
            tmp=i-1;
            data_sort[i]=data_sort[temp];
        }
        i++;
    }
    for(i=0;i<n;i++)//把排序完的数据再放回到数组data中。
        data[i]=data_sort[i];
    delete[] data_sort;//释放动态数组data_sort所占的空间。
}//这个代码其实可以简化到很短很短，不过为了更易懂，我还是把长的打出来了。
```
***
$4.$最最最常用：STL标准库中的 $\text{sort}$ 归并排序，它使用了分治的思想，时间复杂度为 $O(n\log n)$。

此排序只有短短的一行：
```cpp
sort(a,a+n);
```
其中 $a$ 是数组名，$n$ 是数组大小。

如果你勤奋好学，想要了解 $\text{sort}$ 的工作原理，请往下读。如果你很懒，可以直接背下上面的模版，跳过下面的叙述，直接往后读。

$\text{sort}$的工作原理就像这句话：

>如何对一个数组进行排序？答：把它分成两半，再把左边右边分别排序。至于怎么把左边右边分别排序，请重读这句话。

[$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\text{——OI Wiki}$](https://oi-wiki.org)

它的工作方式有$3$步：

1. 将数列分为两部分。
1. 递归地将这两个子序列排序。
1. 合并这两个子序列。

至于代码，就不贴了。毕竟一个$\text{sort}$就完事了。
***
$5.$快速排序：名副其实，非常快。一般情况下时间复杂度为 $O(n\log n)$，最坏情况下时间复杂度为 $O(n^2)$。

实际上，我们可以使用 $\text{Median of Medians}$ 算法减少时间复杂度，使得最坏情况下时间复杂度为 $O(n\log n)$。

快排的代码可以看[$\text{P1177\small\ 快速排序}$](https://www.luogu.com.cn/problem/P1177)
***
最后，是本题的代码：
```cpp
#include<bits/stdc++.h>//万能头棒棒哒
using namespace std;
int main(){
	int x[1005],y[1005],n,k;//k是小方力量值，数组x是龙的力量值，数组y是打败每条龙可以获得的力量值，n是龙的数量。
	cin>>k>>n;//输入小方力量值，龙的数量
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];//输入每条龙的力量值与击败每条龙可获得的力量值
	}
	for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i;j++){
            if(x[j]>x[j+1]){//如果前一条龙的力量值大于后一条龙的力量值
                swap(x[j],x[j+1]);//交换两条龙的力量值的位置
                swap(y[j],y[j+1]);//把这击败两条龙所能获得的力量值也一并交换
            }
        }
    }//冒泡排序，将每条龙的力量值排序，由于击败每条龙可以获得的力量值与每条龙的要一一对应，所以这两个要一起交换位置
    for(int i=1;i<=n;i++){//从力量值最小的龙开始打
    	if(k>x[i]){k+=y[i];}//如果赢了，就获得y[i]点力量值
    	else{//如果输了
    		cout<<"NO";//输出"NO"
    		return 0;//结束程序
    	}
    }
    cout<<"YES";//如果程序一直没有结束，也就是小方一直没有输，撑到了最后，就输出"YES"
    return 0;//完结撒花
}
```
***
$\Huge\color{red}\text{共创文明洛谷，拒绝Ctrl+C!!!}$

---

## 作者：YUYGFGG (赞：1)

用贪心的策略，每次打最小的龙

这里用会自动排序的set实现。具体见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct dr{
	int x,y;//龙的结构体
};
class drcmp{//比较函数类
	public:
        bool operator()(const dr& a,const dr& b){
            return a.x<=b.x;//注意，要<=，不是<
        }
};
set<dr,drcmp> a;//存龙的信息的set，使用自定义比较函数类
int main(){
	int f,n;
	cin>>f>>n;
	dr tmp;
	for(int i=1;i<=n;i++){
		cin>>tmp.x>>tmp.y;//输入临时变量在插入
		a.insert(tmp);
	}
	set<dr>::iterator it=a.begin();//定义指向开头（最小）的迭代器
	for(;it!=a.end();it++){
		if(f>(*it).x) f+=(*it).y;//现有力量值足够，加上额外获得的（访问iterator指向的元素要加*）
		else{//不能，输出，结束
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;//能进入下一层
	return 0;
}
```


---

## 作者：Karry5307 (赞：0)

## 贪心水题
首先考虑两条龙，这两条龙的hp为$p_x$和$p_y$,小方的hp为$k$，那么，如果$k>max(p_x,p_y)$,那么$k>p_x$且$k>p_y$，即$k>min(p_x,p_y)$。

但是$k<=max(p_x,p_y)$时，假设$k>p_x$或$k>p_y$，那么$k>min(p_x,p_y)$。

如果什么都打不到，直接输出$NO$就可以了。

那么，对于所有龙中的任意两条都有这个规律，所以我们可以让小方打hp尽量小的龙，攒了hp再打hp大的龙。所以说我们可以以龙的hp排序。

但是，题目中说在任意一次战斗中，如果小方的力量值比第i条龙$(1<=i<=n)$的力量值**大**，那么小方可以击败这头龙并且获得额外的力量值$y_i$。所以，要判断小方当前的hp是否**大于**龙的hp，而不是**大于等于**。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
struct dragon{
	ll hp,get;
};
ll cnt,tot;
dragon d[100001];
inline bool cmp(dragon a,dragon b)
{
	return a.hp<b.hp;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>tot>>cnt;
	for(register int i=0;i<cnt;i++)
	{
		cin>>d[i].hp>>d[i].get;
	}
	sort(d,d+cnt,cmp);
	for(register int i=0;i<cnt;i++)
	{
		if(tot<=d[i].hp)
		{
			cout<<"NO"<<endl;
			return 0;
		}
		else
		{
			tot+=d[i].get;
		}
	}
	cout<<"YES"<<endl;
}
```

---

